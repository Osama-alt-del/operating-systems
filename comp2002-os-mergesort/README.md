## Project Number/Title 

* Authors: Osama Abd-Alghany, Jying Ming Foo, Willard Gorma
* StudentIDs: a1885358, a1956733, a1863235 (respectively)
* Group name: OS Group58

## Overview

This program sorts a randomly generated array of integers using a multi-threaded merge sort. It splits the work across threads to the cutoff level the user sets, once the cutoff is reached, each thread sorts its own chunk, and the sorted pieces are then merged back together. The aim is for the parallel version to run at least twice as fast as the single-threaded version (cutoff 0) on large arrays.

## Manifest

- Makefile: a shortcut for building the program by storing compile command.
  
- mergesort.c: This file contains the functions: my_mergesort, merge, parallel_mergesort, buildArgs.
  1. my_mergesort() is the recursive function that does the divide part: it finds the midpoint, calls itself on the left half and the right half, and only then calls   merge()
  2. merge() takes two already sorted arrays and combines them into 1 sorted array, using B as a scratch placeand memcpy to copy the result back into A.
  3. parallel_mergesort() creates threads (2 children per call) until the level reaches the cutoff, and at that point calls my_mergesort() for the serial sort. When the children finish, it merges their halves.
  4. buildArgs puts the start (left), end (right) and level of the tree into a struct argument, allocated with malloc, and returns a pointer to it. This single pointer gets passed onto the thread and gets freed by parallel_mergeosrt later.
  
- mergesort.h: header file provided with the assignment that declares the global arrays A and B, the cutoff variable and struct argument; not modified.
- README: The brief information of what this program does.
- test-mergesort.c: The file which tests parallel_mergesort() directly. It tests correctness to check if sorting worked then checks how long the sorting took.

## Building the project

1. A C compiler (gcc) and make has to be installed in VSC. 
2. Open the terminal in the folder containing Makefile and mergesort.c. 
3. Check the makefile, look for the gcc line and whether it includes -pthread.
4. An executable called test-mergesort should be produced in the same folder.
5. To run the result, have a look at "Features and usage” in the README .

## Features and usage

Summarise the main features of your program. It is also appropriate to
instruct the user how to use your program.

## Testing

1. I used the same seed on purpose
This is because I wanted the differences in timing come from the cutoff and not from lucky or unlucky data.  The same seed gives the same array every run.

2. The results:  Benchmark: n = 100,000,000, seed = 1234, 12 cores, 3 runs per cutoff

Cutoff | Threads sorting | Run times (s)       | Median (s) | Speedup
-------|-----------------|---------------------|------------|--------
  0    |        1        | 12.88, 15.46, 13.00 |   13.00    |  1.00x
  1    |        2        |  7.05,  9.30,  6.98 |    7.05    |  1.84x
  2    |        4        |  4.52,  5.08,  5.01 |    5.01    |  2.59x
  3    |        8        |  3.55,  3.51,  3.55 |    3.55    |  3.66x
  4    |       16        |  3.22,  3.35,  3.30 |    3.30    |  3.94x
  5    |       32        |  3.24,  3.27,  3.29 |    3.27    |  3.98x
  6    |       64        |  3.34,  3.39,  3.36 |    3.36    |  3.87x

I decided to use a median because they were sometimes outlier, such as the 15.46s run and the 9.30s run at cutoff 1, with only VSC running. The 2x requirement is met from cutoff-level of 2 and upwards.

To clarify, the speedup is the cutoff-0 median divided by that row’s median, example: 1.84x for cutoff 1 (13.00 ÷ 7.05).

3. Occasional slow outliers
Most runs of the same setting are precise, but some came out much slower. Examples: the serial run that took 15.46s against about 12.9s, and cutoff 1 taking about 9.3s in roughly 1 run in 4, against about 7.0s. They are around the same slow value, which may indicate a pattern. An earlier quiet session had cutoff 5 at about 2.64s, while the latest session gave about 3.27s, with the serial time barely changing.

They were stuff that were suspected and ruled out:
- The browser (the slow runs happened even with it closed)
- Warm-up after idle (Added 60-second pause, but outliers appeared anyways)
- Leftover state between runs (every run is a fresh process, with a newly generated array)

So to resolve this:
Each setting three times was ran 3 times, the median was picked (so one slow run can’t distort a row), and all the tests were done in a single session so every row was measured under the same conditions.

4. Test Passed for other seeds
Other seeds were checked separately for correctness. Seeds 1, 42, 999 and 2026 passed at sizes up to 5,000.

## Known Bugs

-

## Reflection and Self Assessment

Discuss the issues you encountered during development and testing. What
problems did you have? What did you have to research and learn on your own?
What kinds of errors did you get? How did you fix them?

What parts of the project did you find challenging? Is there anything that
finally "clicked" for you in the process of working on this project? How well
did the development and testing process go for you?

## Sources Used

If you used any sources outside of the textbook, you should list them here. 
If you looked something up on stackoverflow.com or you use help from AI, and 
fail to cite it in this section, it will be considered plagiarism and dealt 
with accordingly. So be safe CITE!