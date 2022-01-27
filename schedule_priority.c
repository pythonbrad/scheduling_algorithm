#include "schedulers.h"
#include "list.h"
#include "cpu.h"
#include <malloc.h>
#include <string.h>

struct node* memory;

// This function sort the tasks by order of priority
void sort() {
    // Cells in the memory
    struct node *memory_a;
    struct node *memory_b;
    Task* tmp;

    for (memory_a=memory; memory_a != NULL; memory_a = memory_a->next) {
    	for (memory_b=memory; memory_b != NULL; memory_b = memory_b->next) {
    	    if (memory_a->task->priority > memory_b->task->priority) {
    	        tmp = memory_a->task;
    	        memory_a->task = memory_b->task;
    	        memory_b->task = tmp;
    	    }
    	}
    }
}

// This function select and return the task to execute
Task *pickNextTask() {
    // We verify if the memory is empty
    if (memory == NULL) {
    	return NULL;
    } else {
        // return the first element
        return memory->task;
    }
}

void schedule()
{
    Task *selected_task;
    
    int nb_task = 0;
    
    // Previous burst time
    int prev_burst = 0;
    
    // Current waiting time
    int cwt = 0;
    
    // Total waiting time
    int twt = 0;
    
    // Current turn-around time
    int ctt = 0;
    
    // Total turn-around time
    int ttt = 0;
    
    // Current response time
    int crt = 0;
    
    // Total response time
    int trt = 0;
    
    // We show the tasks
    traverse(memory);
    
    // We sort the tasks
    sort();
    
    while (1) {
        // We select and run a task
        selected_task = pickNextTask();
        
        // We verify if a task is got
        if (selected_task == NULL)
            break;
            
        run(selected_task, selected_task->burst);
        
        // We evaluate the waiting time
        cwt = cwt + prev_burst;
        
        // We evaluate the turn-around time
        ctt = cwt + selected_task->burst;
        
        // We evaluate the response time
        crt = ctt - cwt;
        
        printf("%s Wt: %i Tt: %i Rt: %i\n", selected_task->name, cwt, ctt, crt);
        
        // We update the previous burst time
        prev_burst = selected_task->burst;
        
        // We delete the task executed
        delete(&memory, selected_task);
        
        // We count the number of task
        nb_task++;
        
        // We evaluate the total waiting time
        twt = twt + cwt;
        
        // We evaluate the total turn-around time
        ttt = ttt + ctt;
        
        // We evaluate the total response time
        trt = trt + crt;
    }
    
    printf("Avg Wt = %.2f\n", 1.0 * twt / nb_task);
    printf("Avg Tt = %.2f\n", 1.0 * ttt / nb_task);
    printf("Avg Rt = %.2f\n", 1.0 * trt / nb_task);
}

void add(char *name, int priority, int burst)
{
    static int tid = 0;
    
    // We create the memory
    Task *new_task = malloc(sizeof(Task));
    new_task->tid = tid++;
    new_task->name = strdup(name);
    new_task->priority = priority;
    new_task->burst = burst;
    
    // We insert the task in the memory
    insert(&memory, new_task);
}

