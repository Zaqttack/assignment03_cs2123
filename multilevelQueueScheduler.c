#include <stdlib.h>
#include <string.h>

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
    // printf("a. entering isScheduleUnfinished\n");

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
    queueType qt = (queueType)malloc(sizeof(process) + sizeof(processData));
    // qt->data = (processData*)malloc(sizeof(processData));

    processData *pData = initializeProcessData(processName);
    qt->data = pData;

    // printf("Name: %s\n", qt->data->name);

    // memcpy(qt->data, pData, sizeof(processData));
    memset(qt->processName, 0, 21);
    memcpy((qt->processName), processName, 20);

    qt->pry = p;
    qt->timeSteps = runtime;
    qt->atHead = 0;
    qt->timeStepsTaken = 0;
    qt->addedToBackground = ps->totalTimeSteps;

    if(p == BACKGROUND)
        enqueue(ps->background, qt);
    else
        enqueue(ps->foreground, qt);
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
    char * newProcessName = NULL;
    ps->totalTimeSteps++;

    while(ps->totalTimeSteps - getNext(ps->background)->addedToBackground > 50) {
        queueType qt = dequeue(ps->background);
        enqueue(ps->foreground, qt);
        promoteProcess(qt->processName, qt->data);
    }

    if(!isEmpty(ps->foreground)) {
        getNext(ps->foreground)->timeStepsTaken++;
        getNext(ps->foreground)->atHead++;
        newProcessName = runProcessForOneTimeStep(
            getNext(ps->foreground)->processName, 
            (getNext(ps->foreground)->data));

        if(getNext(ps->foreground)->timeStepsTaken >= getNext(ps->foreground)->timeSteps) {
            queueType qt = dequeue(ps->foreground);
            freeProcessData(qt->data);
            free(qt);
        }
        else if(getNext(ps->foreground)->atHead == 5) {
            getNext(ps->foreground)->atHead = 0;
            enqueue(ps->foreground, dequeue(ps->foreground));
        }
    }
    else {
        if(getNext(ps->background)->timeStepsTaken >= getNext(ps->background)->timeSteps) {
            queueType qt = dequeue(ps->background);
            freeProcessData(qt->data);
            free(qt);
        }
        else {
            getNext(ps->background)->timeStepsTaken++;
            newProcessName = runProcessForOneTimeStep(
                getNext(ps->background)->processName, 
                (getNext(ps->background)->data));
        }
    }

    return newProcessName; /* TODO: Replace with your return value */
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
    free(ps);
}
