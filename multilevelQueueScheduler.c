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
    schedule *ps = (schedule*)malloc(sizeof(schedule));
    ps->foreground = createQueue();
    ps->background = createQueue();
    ps->totalTimeSteps = 0;

    return ps; /* TODO: Replace with your return value */
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

    return !isEmpty(ps->foreground) || !isEmpty(ps->background); /* TODO: Replace with your return value */
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
    processData *proc;
    proc = initializeProcessData(processName);

    ps->background->qFront->qt->processName = processName;
    ps->background->qFront->qt->data = *proc;
    ps->background->qFront->qt->pry = p;
    ps->background->qFront->qt->timeSteps = runtime;
    ps->background->qFront->qt->atHead = 0;
    ps->background->qFront->qt->timeStepsTaken = 0;
    ps->background->qFront->qt->addedToBackground = ps->totalTimeSteps;
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
    queueType qt;
    ps->totalTimeSteps++;
    if(ps->totalTimeSteps - ps->background->qFront->qt->addedToBackground > 50)
        enqueue(ps->foreground, dequeue(ps->background));

    if(!isEmpty(ps->foreground)) {
        runProcessForOneTimeStep(ps->foreground->qFront->qt->processName, &ps->foreground->qFront->qt->data);
        ps->foreground->qFront->qt->timeStepsTaken++;
        ps->foreground->qFront->qt->atHead++;

        if(ps->foreground->qFront->qt->timeStepsTaken >= ps->foreground->qFront->qt->timeSteps) {
            /*
            queueType qt was created so that after dequeue'ing occured the processData could be
            freed before the dequeued element was freed 
            */
            qt = dequeue(ps->foreground);
            freeProcessData(&ps->foreground->qFront->qt->data);
            free(qt);
        }
        else if(ps->foreground->qFront->qt->atHead == 5) {
            ps->foreground->qFront->qt->atHead = 0;
            enqueue(ps->foreground, dequeue(ps->foreground));
        }
    }
    else {
        if(ps->background->qFront->qt->timeStepsTaken >= ps->background->qFront->qt->timeSteps) {
            qt = dequeue(ps->background);
            freeProcessData(&ps->background->qFront->qt->data);
            free(qt);
        }
        else {
            runProcessForOneTimeStep(ps->background->qFront->qt->processName, &ps->background->qFront->qt->data);
        }
    }

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
    queueType qt;

    while(!isEmpty(ps->foreground)) {
        qt = dequeue(ps->foreground);
        freeProcessData(&ps->foreground->qFront->qt->data);
        free(qt);
    }
    while(!isEmpty(ps->background)) {
        qt = dequeue(ps->background);
        freeProcessData(&ps->background->qFront->qt->data);
        free(qt);
    }
    freeQueue(ps->foreground);
    freeQueue(ps->background);
    freeSchedule(ps);
}
