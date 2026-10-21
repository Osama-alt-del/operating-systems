## Project Number/Title 

* Authors: Osama Abd-Alghany, Jying Ming Foo, Willard Gorman
* StudentIDs: a1885358, a1956733, a1863235 (respectively)
* Group name: OS Group58

## Overview

This program sorts a randomly generated array of integers using a multi-threaded merge sort. It splits the work across threads to the cutoff level the user sets, once the cutoff is reached, each thread sorts its own chunk, and the sorted pieces are then merged back together. The aim is for the parallel version to run at least twice as fast as the single-threaded version (cutoff 0) on large arrays.

## Manifest

- Makefile: a shortcut for building the program by storing compile command.
  
- mergesort.c: This file contains the functions: my_mergesort, merge, parallel_mergesort, buildArgs.
  1. my_mergesort() is the recursive function that does the divide part: it finds the midpoint, calls itself on the left half and the right half, and only then calls merge().
  2. merge() takes two already sorted arrays and combines them into 1 sorted array, using B as a scratch place and memcpy to copy the result back into A.
  3. parallel_mergesort() creates threads (2 children per call) until the level reaches the cutoff, and at that point calls my_mergesort() for the serial sort. When the children finish, it merges their halves.
  4. buildArgs puts the start (left), end (right) and level of the tree into a struct argument, allocated with malloc, and returns a pointer to it. This single pointer gets passed onto the thread and gets freed by parallel_mergesort later.
  
- mergesort.h: header file provided with the assignment that declares the global arrays A and B, the cutoff variable and struct argument; not modified.
- README: The brief information of what this program does.
- test-mergesort.c: The file which tests parallel_mergesort() directly. It tests correctness to check if sorting worked then checks how long the sorting took.

## Building the project

1. A C compiler (gcc) and make has to be installed on the system. 
2. Open the terminal in comp2002-os-mergesort, the folder containing Makefile and mergesort.c. 
3. Run the command "make" in the terminal. An executable called test-mergesort should appear in the same folder.
4. To run the result, have a look at "Features and usage” in the README .

## Features and usage

To use the program, ensure that you are in the comp2002-os-mergesort folder and running the terminal inside it. Then write the line ./test-mergesort 100000 2 123 to running the program (settings: 100000 element, cutoff-level 2, random_seed 123). To change the settings: ./test-mergesort <num of elements> <cutoff level> <randomseed>. The output should look something like: "Sorting 100000 elements took 0.00 seconds".

## Testing

1. I used the same seed on purpose
This is because I wanted the differences in timing come from the cutoff and not from lucky or unlucky data.  The same seed gives the same array every run.

2. The results (Jying Ming's laptop):  Benchmark: n = 100,000,000, seed = 1234, 12 logical CPUs (reported by nproc), 3 runs per cutoff

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

These factors were suspected and ruled out:
- The browser (the slow runs happened even with it closed)
- Warm-up after idle (Added 60-second pause, but outliers appeared anyways)
- Leftover state between runs (every run is a fresh process, with a newly generated array)

So to resolve this:
Each setting was ran 3 times, the median was picked (so one slow run can’t distort a row), and all the tests were done in a single session so every row was measured under the same conditions.

4. Test Passed for other seeds
Other seeds were checked separately for correctness. Seeds 1, 42, 999 and 2026 passed at sizes up to 5,000.

5. The program passed Gradescope's Basic Execution Test, Parallel Execution Test and Medium Input Test. 

6. My machine met the x2 speedup requirement but it could differ from Gradescope's hardware.

## Known Bugs

None were found in the testing as described above.

- If pthread_create fails (for example because of an extreme cutoff), the program prints an error and exits instead of recovering.
- A very large cutoff creates thousands of threads and can run the system out of resources.
- It needs about 800 MB of RAM at 100 million elements, because of the two arrays.

These are considered as potential design limits more than bugs, running it on a different laptop with insufficient RAM (apps running in the background) could cause errors.

## Reflection and Self Assessment

After writing my own merge sort on LeetCode, moving it into this assignment meant converting the code from C++ to C. I couldn’t use functions like push_back, so I had to write into the existing arrays A and B by index instead. The transition took a while: I had to look up the C syntax, read the header file to see what was already provided, and learn the memory functions malloc and memcpy.

When it came to benchmarking, I ran each setting 3 times so I wouldn’t blindly trust the first value, and outliers showed up. They were usually easy to spot, because two of the values would be close together and the third would be the odd one out. I ruled out my open browser tabs, since I closed them all, and a slow start after idle, since I waited 60 seconds before running. I think the slow runs may have been background tasks that happened to run alongside my program at random moments, but I didn’t test this.

Next time I would check the Task Manager during runs to see what else is using the CPU, and do more than 3 runs per setting. With only 3, I can’t tell whether the odd value is a rare slow run or part of a second group of results. For cutoff 1, where I ran many more, about a quarter of the runs fell into a slower group (around 9.3s instead of around 7.0s), so more runs would likely show this at the other cutoffs too.

## Sources Used

To understand merge sort:
- Merge sort in 3 minutes - https://www.youtube.com/watch?v=4VqmGXwpLqc

To practice merge sort code:
- LeetCode Problem 88 - Merge Sorted Array - https://leetcode.com/problems/merge-sorted-array/description/
- LeetCode Problem 912 - Sort an Array - https://leetcode.com/problems/sort-an-array/description/

AI assistance (Claude, claude.ai): used to explain concepts and check my understanding. It explained why merge sort needs array B, how pthread_create and pthread_join work, what the cutoff level does, how to read the test driver and my benchmark results, and how to combine Git branches. I adjusted my own merge sort from LeetCode into C. When I asked how to replace push_back, Claude showed an example of a merge loop writing into B by index, and I used it to rewrite those lines. It also gave feedback on drafts of this README.