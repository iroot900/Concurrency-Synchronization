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

Tested on Mac Pro, single thread is actullay faster, which is not a surprise since pthread is user-level thread. 
