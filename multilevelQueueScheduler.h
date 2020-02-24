#ifndef _multilevelQueueScheduler_h
#define _multilevelQueueScheduler_h
#include <stdlib.h>
#include <stdbool.h>

#include "process.h"
#include "queue.h"
#include "processSimulator.h"

typedef enum priority { FOREGROUND, BACKGROUND } priority;

/* struct schedule (only accessed in student written code)
 *
 * Data related to the order the processes should be scheduled in.
 * At minimum it should store the FOREGROUND and BACKGROUND queues.
 *
 * Hint: It may also help to track the number of time steps that have been processed so far.
 */
typedef struct schedule
{
    //TODO: Put the data for your schedule program here!
}  schedule;

schedule* createSchedule( );
bool isScheduleUnfinished( schedule *ps );
void addNewProcessToSchedule( schedule *ps, char *processName, int runtime, priority p );
char* simulateNextTimeStep( schedule *ps );
void freeSchedule( schedule *ps );

#endif
