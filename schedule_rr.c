#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "task.h"
#include "cpu.h"

// Initialize the list
struct node *procList = NULL;

// add a task to the list 
void add(char *name, int priority, int burst, int tid) {
    struct task *newTask = malloc(sizeof(struct task));
    newTask->name = name;
    newTask->tid = tid;
    newTask->priority = priority;
    newTask->burst = burst;
    
    // printf("List: %p\n", newTask);
    // printf("List: %p\n", head);

    insert(&procList, newTask);
}

// invoke the scheduler (FCFS)
void schedule() {
    struct node *temp;

    // Keep looping through the tasks until all are done
    do {
        temp = procList;

        while (temp != NULL) {
            if (temp->task->burst > QUANTUM) {
                run(temp->task, QUANTUM);
                temp->task->burst -= QUANTUM;
            }
            else {
                run(temp->task, temp->task->burst);
                temp->task->burst = 0;
                delete(&procList, temp->task);
            }

            temp = temp->next;
        }
        
    } while (procList != NULL);
}