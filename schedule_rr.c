#include "schedulers.h"
#include "list.h"
#include "cpu.h"
#include <malloc.h>
#include <string.h>

struct node* memory;

void schedule()
{    
    int nb_task = 0;
    
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
    
    // Current total execution time
    int ctet = 0;
    
    // Number of round robbin
    int nrr = 0;
    
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
            if (curr_memory->task->burst > QUANTUM) {
            	slice_time = QUANTUM;
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
                
                // We evaluate the waiting time
            	cwt = ctet - nrr * QUANTUM;
            
            	// We evaluate the turn-around time
            	ctt = ctet + slice_time;
            	
            	// We evaluate the response time
				crt = ctt - cwt;
				
				// We evaluate the total waiting time
				twt = twt + cwt;
				
				// We evaluate the total turn-around time
				ttt = ttt + ctt;
				
				// We evaluate the total response time
				trt = trt + crt;
				
				// We count the number of task
				nb_task++;
            
                // We print his waiting time        	
				printf("%s Wt: %i Tt: %i Rt: %i Nrr: %i\n", curr_memory->task->name, cwt, ctt, crt, nrr);
            }
            
            // We evaluate the current total execution time
            ctet = ctet + slice_time;
            
            // We go to the next
            curr_memory = curr_memory->next;
        }
        
        // We evaluate the number of round robbin
        nrr = nrr + 1;  
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

