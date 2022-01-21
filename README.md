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
	make fcfs
```
	which builds the fcfs executable file.

# My notes

## CPU.h
###	Contains the function *run*, this function simulate the execution of a task by the CPU (read the task from the memory and execute it)

## schedulers.h
### Contains the functions *add* and *schedule*. The first permit to simulate the loading of the processes in the memory and the second permit to simulate the scheduling of the execution of the tasks.

## driver.c
### Simulate the OS:
- Loading the tasks in the memory in calling the function *add*
- Schedule the execution in calling the function *schedule*

# Overview
![Image](https://github.com/pythonbrad/scheduling_algorithm/blob/master/overview.png)