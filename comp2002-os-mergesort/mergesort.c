/**
 * This file implements parallel mergesort.
 */

#include <stdio.h>
#include <string.h> /* for memcpy */
#include <stdlib.h> /* for malloc */
#include "mergesort.h"

/* this function will be called by mergesort() and also by parallel_mergesort(). */
void merge(int leftstart, int leftend, int rightstart, int rightend){
	int i = leftstart;    // pointer into left half
    int j = rightstart;    // pointer into right half
    int k = leftstart;    // pointer into where you're writing in B (same range as the merge)

	// A is array needing sort
    // B is temp array

    while (i <= leftend && j <= rightend) {
        if (A[i] <= A[j]) {
            B[k] = A[i];     // this replaces "push_back"
            i++;
        } else {
            B[k] = A[j];
            j++;
        }
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

/* this function will be called by parallel_mergesort() as its base case. */
void my_mergesort(int left, int right){
    // base case
    if (left >= right) return;

    int mid = left + (right - left)/2;

    my_mergesort(left, mid);
    my_mergesort(mid+1, right);
    merge(left, mid, mid+1, right);
}

/* this function will be called by the testing program. */
void * parallel_mergesort(void *arg){
		return NULL;
}

/* we build the argument for the parallel_mergesort function. */
struct argument * buildArgs(int left, int right, int level){
		return NULL;
}

