#include "schedulers.h"
#include "list.h"
#include "cpu.h"
#include <malloc.h>
#include <string.h>

struct node* memory;

// This function sort the tasks by order of burst time
void sort() {
    // Cells in the memory
    struct node *memory_a;
    struct node *memory_b;
    Task* tmp;

    for (memory_a=memory; memory_a != NULL; memory_a = memory_a->next) {
    	for (memory_b=memory; memory_b != NULL; memory_b = memory_b->next) {
    	    if (memory_a->task->burst < memory_b->task->burst) {
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
       
        // We delete the task executed
        delete(&memory, selected_task);
    }
}

void add(char *name, int priority, int burst)
{
    static int tid = 0;
    
    // We create a memory if not already created
    if (memory == NULL)
    	malloc(sizeof(struct node));
    
    // We create the memory
    Task *new_task = malloc(sizeof(Task));
    new_task->tid = tid++;
    new_task->name = strdup(name);
    new_task->priority = priority;
    new_task->burst = burst;
    
    // We insert the task in the memory
    insert(&memory, new_task);
}

