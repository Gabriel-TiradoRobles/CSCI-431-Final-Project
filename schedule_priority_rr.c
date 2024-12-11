#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "task.h"
#include "cpu.h"

#define MIN_PRIORITY 1
#define MAX_PRIORITY 10

// Initialize the list
struct node *prioProcLists[MAX_PRIORITY] = {NULL};

struct node* pickNextTask(struct node *task);

struct node *pickPrioProcList(int prioNum);

// add a task to the list 
void add(char *name, int priority, int burst, int tid) {
    struct task *newTask = malloc(sizeof(struct task));
    newTask->name = name;
    newTask->tid = tid;
    newTask->priority = priority;
    newTask->burst = burst;

    insert(&prioProcLists[priority - 1], newTask);
}

// invoke the scheduler (Priority RR)
void schedule() {
    struct node *temp;

    for (int currPrio = 0; currPrio < MAX_PRIORITY - 1; currPrio++)
    {
        do {
            temp = prioProcLists[currPrio];

            while (temp != NULL) {
                if (temp->task->burst > QUANTUM) {
                    run(temp->task, QUANTUM);
                    temp->task->burst -= QUANTUM;
                }
                else {
                    run(temp->task, temp->task->burst);
                    temp->task->burst = 0;
                    delete(&prioProcLists[currPrio], temp->task);
                }

                temp = temp->next;
            }
        } while (prioProcLists[currPrio] != NULL);
    }
}