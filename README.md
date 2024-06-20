# CPU_Scheduler
An implementation of various CPU scheduling algorithms in C++. The algorithms included are First Come First Serve (FCFS), Round Robin (RR),Shortest Job First Scheduling (SJF), Priority Scheduling.

## Table of Contents
- [CPU-Scheduling-Algorithms](#cpu-scheduling-algorithms)
  - [Algorithms](#algorithms)
    - [First Come First Serve (FCFS)](#first-come-first-serve-fcfs)
    - [Shortest Job First Scheduling (SJF)](#shortest-job-first-sjf)
    - [Priority Scheduling](#priority-scheduling-ps)
    - [Round Robin with varying time quantum (RR)](#round-robin-with-varying-time-quantum-rr)
  - [Installation](#installation)
  - [Input Format](#input-format)
  - [Contributor](#contributor)

## Algorithms

### First Come First Serve (FCFS)
- First Come First Served (FCFS) is a scheduling algorithm in which the process that arrives first is executed first. It is a simple and easy-to-understand algorithm, but it can lead to poor performance if there are processes with long burst times. This algorithm does not have any mechanism for prioritizing processes, so it is considered a non-preemptive algorithm. In FCFS scheduling, the process that arrives first is executed first, regardless of its burst time or priority. This can lead to poor performance, as longer running processes will block shorter ones from being executed. It is commonly used in batch systems where the order of the processes is important.

### Shortest Job First Scheduling(SJF)
-Shortest Job First (SJF) is a scheduling algorithm that selects the process with the shortest burst time next. This can be preemptive (Shortest Remaining Time First, SRTF) or non-preemptive.
-This is both Preemptive and Non-Preemptive type of algorithms. In case of preemptive if a new process starts with a shorter remaining time than the current process then the current process is interrupted and it is again sent to ready queue for execution and the new process is executed.

### Priority Scheduling
-Priority Scheduling is a preemptive or non-preemptive scheduling algorithm where each process is assigned a priority. The CPU is allocated to the process with the highest priority (the lowest numerical value if priorities are numerical). If two processes have the same priority, they are scheduled according to their arrival order.
-Priority Scheduling enables efficient resource allocation by allocating CPU time to the most important or time-sensitive tasks first, potentially improving overall system throughput and performance.

### Round Robin with varying time quantum (RR)
- Round Robin (RR) with variable quantum is a scheduling algorithm that uses a time-sharing approach to divide CPU time among processes. In this version of RR, the quantum (time slice) is not fixed and can be adjusted depending on the requirements of the processes. This allows processes with shorter burst times to be given smaller quanta and vice versa.

- The algorithm works by maintaining a queue of processes, where each process is given a quantum of time to execute on the CPU. When a process's quantum expires, it is moved to the back of the queue, and the next process in the queue is given a quantum of time to execute.

- The variable quantum allows the algorithm to be more efficient as it allows the CPU to spend more time on shorter processes and less time on longer ones. This can help to minimize the average waiting time for processes. Additionally, it also helps to avoid the issue of starvation, which occurs when a process with a long burst time prevents other processes from executing.

- Note that during each call to the scheduler, the complete ready list has to be traversed.
## Installation
1- Clone the repository

2- Install g++ compiler and make
```bash
sudo apt-get install g++ make
```
3- Compile the code using `make` command

4- Run the executable file


## Contributor

- [Pragyan Pandey](https://github.com/C0MPL3XALPHA)
