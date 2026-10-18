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

This section should tell the user how to build your code.  If you are
delivering a library, where does it need to be installed, or how do you use
it? Is this an executable, if so, how can a user get up to speed as fast as
possible?

## Features and usage

Summarise the main features of your program. It is also appropriate to
instruct the user how to use your program.

## Testing

This section should detail how you tested your code. Simply stating "I ran
it a few times and it seems to work" is not sufficient. Your testing needs
to be detailed here.

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
