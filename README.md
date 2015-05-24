# Concurrency-Synchronization

In this repository are some classic problems/solutions regarding multi-thread, with an application on Matrix Multiplication:

Reader-Writer Problem: Mutex Solution / RWLOCK Solution

Consumer-Producer Problem:  Semaphore Solution / Monitor Solution

Deadlock illustration



Multithreaded-Matrix-Multiplication:

options:

-h : printout help

-s : number of threads, default 2 (recommned value as the same number of machine's processors)

-t : size of matrix,deafult 5000x5000

Tested on Mac Pro, single thread is actullay faster for default setting. (My understanding is that pthread is a user level thread, so many of them share the same kernel thread which actually do the work.)
