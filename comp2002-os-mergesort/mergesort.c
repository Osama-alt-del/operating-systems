// This file implements parallel mergesort

#include <stdio.h>
#include <string.h> // for memcpy
#include <stdlib.h> // for malloc
#include "mergesort.h"

// this function will be called by mergesort() and also by parallel_mergesort()
void merge(int leftstart, int leftend, int rightstart, int rightend){
	int i = leftstart;    // pointer into left half
    int j = rightstart;    // pointer into right half
    int k = leftstart;    // pointer into where you're writing in B (same range as the merge)

	// A is array needing sort
    // B is temp array

    // Compare values from left-side and right-side
    while (i <= leftend && j <= rightend) {
        // Left value > right value, take i
        if (A[i] <= A[j]) {
            B[k] = A[i];
            i++;

        } else {
        // Right value > left value, take j
            B[k] = A[j];
            j++;
        }

        // regardless increment temp array pointer
        k++;
    }
    
    // copy any remaining elements from whichever half 
    while (i <= leftend)  { B[k++] = A[i++]; }
    while (j <= rightend) { B[k++] = A[j++]; }

    // copy merged range back into A
    memcpy(A + leftstart, B + leftstart, (rightend - leftstart + 1) * sizeof(int));

    // memcpy(dest, src, num_bytes)
    // destination: A + leftstart
    // source: B + leftstart
    // num_bytes = size of array (num of elements)
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