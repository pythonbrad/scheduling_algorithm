#include "schedulers.h"
#include "list.h"
#include "cpu.h"
#include <malloc.h>
#include <string.h>

struct node* memory;

void schedule()
{
    int time_quantum = 10;
    
    // Task slice time
    int slice_time;
    
    // cell in the memory
    struct node *curr_memory;
    
    // We show the tasks
    traverse(memory);
    
    // We execute all the tasks inside
    while (memory != NULL) {
        curr_memory = memory;
        
        //traverse(memory);
        
        while (curr_memory != NULL)
        {
            // We evaluate the slice time
            if (curr_memory->task->burst > time_quantum) {
            	slice_time = time_quantum;
            } else {
            	slice_time = curr_memory->task->burst;
            }
            
            // We run the task in the current position in the memory
            run(curr_memory->task, slice_time);
            
            // We update the burst time
            curr_memory->task->burst -= slice_time;
            
            if (curr_memory->task->burst == 0) {
                // We delete the completely executed task
                delete(&memory, curr_memory->task);
            }
            
            // We go to the next
            curr_memory = curr_memory->next;
        }
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

