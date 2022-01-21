# Implementation of scheduling algorithms

# Assignments

## Completing this project will require writing the following C files:
	schedule_fcfs.c
	schedule_sjf.c
	schedule_rr.c
	schedule_priority.c
	schedule_priority_rr.c

## The supporting files invoke the appropriate scheduling algorithm. 

## For example, to build the FCFS scheduler, enter

```sh
// which builds the fcfs executable file.
make fcfs
```

# My notes

## CPU.h
#### Simulate the CPU:
- Contains the function *run*, this function simulate the execution of a task by the CPU (read the task from the memory and execute it)

## list.h
#### Simulate the memory
- Contains the struct *node* who is a linked list (each node will represent a cell in the memory).
#### Simulate the memory operations
- Contains the functions *insert*, *delete* and *traverse*.

## schedulers.h
#### Functionality of the OS:
- Contains the functions *add* and *schedule*. The first permit to simulate the loading of the processes in the memory and the second permit to simulate the scheduling of the execution of the tasks.
- The function *add* use the memory operation *insert* to insert the tasks in the memory.
- The function *schedule* use the CPU *run* function, the memory opration *delete* and *traverse* to read and to delete a task on the memory.
- To schedule, we will select a task in the memory depending on the scheduling algorithm, execute it and remove it from the memory when the executing will be completed succesfully.

## driver.c
#### Simulate the OS:
- Loading the tasks in the memory in calling the function *add*
- Schedule the execution in calling the function *schedule*

# Overview
![Image](https://github.com/pythonbrad/scheduling_algorithm/blob/master/overview.png)
