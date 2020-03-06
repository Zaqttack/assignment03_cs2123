#ifndef _process_h
#define _process_h
#include <stdio.h>

#include "multilevelQueueScheduler.h"

typedef struct processData
{
    char name[21];
    char TLN[4];
    int heap[30];
}  processData;

/* struct process (only accessed in student written code)
 *
 * The data associated with a specific process.
 * At minimum you need to track the process name,
 * and the number of cycles process still needs to run.
 *
 * Hint: It may help to store how many time steps happened before
 * a process was added to the schedule.
 */
typedef struct process
{
    //TODO: Put the data for your process here!
    char *processName;
    processData data;
    int timeSteps;
    priority pry;
    int atHead;
    int timeStepsTaken;
    int addedToBackground;
}  process;

#endif