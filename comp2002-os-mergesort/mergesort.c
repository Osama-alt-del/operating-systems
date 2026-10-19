// This file implements parallel mergesort

#include <stdio.h>
#include <string.h> // for memcpy
#include <stdlib.h> // for malloc
#include "mergesort.h"

// this function will be called by mergesort() and also by parallel_mergesort()
void merge(int leftstart, int leftend, int rightstart, int rightend){
    // A is array needing sort
    // B is temp array

	int i = leftstart;    // pointer into left half
    int j = rightstart;    // pointer into right half
    int k = leftstart;    // pointer into current index to be written in B

    // Compare left value and right value, decide order to go into B
    while (i <= leftend && j <= rightend) {
        // left value (i) < right value (j), so left is smaller, take i
        if (A[i] <= A[j]) {
            B[k] = A[i];
            i++;

        } else {
        // left value (i) > right value (j), so right is smaller, take j
            B[k] = A[j];
            j++;
        }

        // move forward temp array (b) pointer, next empty space to fill
        k++;
    }
    
    // Incase one half is finished while the other still has values left
    while (i <= leftend)  { B[k++] = A[i++]; }
    while (j <= rightend) { B[k++] = A[j++]; }

    // copy sorted values in B back into A
    memcpy(A + leftstart, B + leftstart, (rightend - leftstart + 1) * sizeof(int));

    // memcpy(dest, src, num_bytes)
    // destination: A + leftstart
    // source: B + leftstart
    // num_bytes = size of array (num of elements x bytes per int)
}

// this function will be called by parallel_mergesort() as its base case. 
void my_mergesort(int left, int right){

    // base case (both pointers meet)
    if (left >= right) return;
    
    // find mid point 
    int mid = left + (right - left)/2;

    // splits array into half until last layer
    my_mergesort(left, mid);
    my_mergesort(mid+1, right);

    // merge array together recursively
    merge(left, mid, mid+1, right);
}

// this function will be called by the testing program
void * parallel_mergesort(void *arg){

    // unpack the argument
    // (don't free it here: whoever built it frees it - the test program
    // frees the top-level one, and each parent frees its children's)
    struct argument *a = (struct argument *) arg;
    int left = a->left;
    int right = a->right;
    int level = a->level;

    // base case: reached the cutoff level (or nothing to split),
    // so stop making threads and sort this range with a single thread
    if (level >= cutoff || left >= right) {
        my_mergesort(left, right);
        return NULL;
    }

    // find mid point
    int mid = left + (right - left)/2;

    // build the arguments for the two halves, one level further down
    struct argument *leftArg = buildArgs(left, mid, level + 1);
    struct argument *rightArg = buildArgs(mid + 1, right, level + 1);

    // "recurse" by creating two threads that each run parallel_mergesort()
    // on one half - this is the indirect recursion through pthread_create()
    pthread_t leftThread, rightThread;
    if (pthread_create(&leftThread, NULL, parallel_mergesort, leftArg) != 0 ||
        pthread_create(&rightThread, NULL, parallel_mergesort, rightArg) != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    // wait for both halves to finish sorting before merging them
    pthread_join(leftThread, NULL);
    pthread_join(rightThread, NULL);

    // threads are done with their arguments, so free them
    free(leftArg);
    free(rightArg);

    // merge the two sorted halves together
    merge(left, mid, mid + 1, right);

	return NULL;
}

/* we build the argument for the parallel_mergesort function. */
struct argument * buildArgs(int left, int right, int level){

    // allocate on the heap so the struct outlives this call
    // (the caller frees it once the thread using it has been joined)
    struct argument *arg = malloc(sizeof(struct argument));
    if (arg == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    arg->left = left;
    arg->right = right;
    arg->level = level;

    return arg;
}