#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "task.h"
#include "cpu.h"

// Initialize the list
struct node *procList = NULL;

struct node* pickNextTask(struct node *task);

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

// invoke the scheduler (SJF)
void schedule() {
    struct node *temp;
    temp = procList;

    while (temp != NULL) {
        struct node *toRun = pickNextTask(temp);

        run(toRun->task, toRun->task->burst);
        toRun->task->burst -= toRun->task->burst;

        delete(&procList, toRun->task);
        temp = procList;
    }
}

// Determine which task to run next. Based on shortest job first
struct node* pickNextTask(struct node *task) {
    struct node *shortestTask = NULL;

    while (task != NULL) {
        if (shortestTask == NULL) {
            shortestTask = task;
        }
        else if (task->task->burst < shortestTask->task->burst) {
            shortestTask = task;
        }
        task = task->next;
    }

    return shortestTask;
}