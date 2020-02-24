#include <stdlib.h>

#include "multilevelQueueScheduler.h"

/* createSchedule
 * input: none
 * output: a schedule
 *
 * Creates and return a schedule struct.
 */
schedule* createSchedule( ) {
    /* TODO: initialize data in schedule */

    return NULL; /* TODO: Replace with your return value */
}

/* isScheduleUnfinished
 * input: a schedule
 * output: bool (true or false)
 *
 * Check if there are any processes still in the queues.
 * Return TRUE if there is.  Otherwise false.
 */
bool isScheduleUnfinished( schedule *ps ) {
    /* TODO: check if there are any process still in a queue.  Return TRUE if there is. */

    return false; /* TODO: Replace with your return value */
}

/* addNewProcessToSchedule
 * input: a schedule, a string, an int, a priority
 * output: void
 *
 * Create a new process with the provided name, runtime, and priority.
 * Add that process to the appropriate queue
 */
void addNewProcessToSchedule( schedule *ps, char *processName, int runtime, priority p ) {
    /* TODO: complete this function.
    The functions "initializeProcessData" in processSimulator.c will be useful in completing this. */
}

/* simulateNextTimeStep
 * input: a schedule
 * output: a string
 *
 * Use the schedule to determine the next process to run.
 * If process being run starts a new process it will return a string.
 * This function should just return this string.
 */
char* simulateNextTimeStep( schedule *ps ) {
    /* TODO: complete this function.
    The function "runProcessForOneTimeStep", "promoteProcess", and "freeProcessData"
    in processSimulator.c will be useful in completing this. */

    return NULL; /* TODO: Replace with your return value */
}

/* freeSchedule
 * input: a schedule
 * output: none
 *
 * Free all of the memory associated with the schedule.
 */
void freeSchedule( schedule *ps ) {
    /* TODO: free any data associated with the schedule.
    the function "freeQueue" in queue.c will be useful in completing this.
    You may also want to call "freeProcessData" for any processes still left in your queues */
}
