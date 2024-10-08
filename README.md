**Assignment #1: OS Scheduler**
Implement a simple OS scheduler using CPP. The scheduler’s task is to receive a set of processes and their details and then decide the order of executing these processes
based on the chosen algorithm. Finally, the scheduler will output the order of process execution, in addition to some stats about each of the processes.The scheduling algorithm chosen for this assignment will be a slightly modifed version Shortest
Remaining Time (SRT) algorithm. In the assignment, we make a slight modification such that we give more priority to the process that arrived later, which is the opposite of
what we learned in class. In the case where processes have the same remaining time and arrival time, we choose the process that had its name listed first in the input file.
**Assignment #2: Threading**
Implement a multi-threaded program CPP. The project is a multithreaded Merge Sort algorithm. The program will create T worker threads that will operate on an array
to sort it using the well-known Merge Sort algorithm Each The program will read an input (TH) which is the threshold that will be used to calculate the global variables r program should have at least three global shared variables to report the statistics of files When any of the threads starts executing, it will print its number (0 to T-1), and then the range in the
array that it is operating on, and will keep updating the global variables as it goes. Finally, when all threads are done, the main should print the statistics of the entire array. You should write two versions of the program: The first one doesn’t consider race conditions, and the other one is thread-safe.
