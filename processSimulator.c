#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "processSimulator.h"

void authentication( char *pName, processData* pData );
void startProcess( char *pName, processData *pData );

static int time = 0;
static int nameNum = 0;

/* initializeProcessData
 * input: the process name
 * output: initialized data for the process
 *
 * Initialize the data for a process.
 * Call this when a process is first added to your queue
 */
processData* initializeProcessData( char *processName ){
    processData* pData = (processData*)malloc(sizeof(processData));
    char temp[21];
    char intStr[3];
    char *priorityName;
    int i;

    if( pData==NULL ){
        fprintf(stderr, "initializeProcessData: Unable to allocate data.");
        exit(-1);
    }
    for(i=0; i<21; i++)
        pData->name[i] = 0;
    strncpy( pData->name, processName, 20 );

    //printf("%s\n",processName);
    sscanf( processName, "%*[^|]|%20s", temp );
    sscanf( temp, "%3[^|]|%20s", pData->TLN, temp );
    for( i=0; i<=4; i++ ){
        //printf("%s\n",temp);
        sscanf( temp, "%2[^|]|%20s", intStr, temp );
        sscanf( intStr, "%d", &pData->heap[i] );
    }
    while( i<=26 ){
        pData->heap[i]=0;
        i++;
    }
    pData->heap[6] = pData->heap[2];
    pData->heap[7] = processName[0]=='B';

    pData->heap[8]=pData->heap[4];

    pData->heap[1] = max(pData->heap[1]/powInt(2,abs(pData->heap[7]-1)),1);

    if( pData->heap[7] ){
        priorityName = "BACKGROUND";
    }
    else{
        priorityName = "FOREGROUND";
    }

    printf( "Process data created: %s-%d (%s for %d cycles)\n\n", pData->TLN, pData->heap[0], priorityName, pData->heap[1] );

    return pData;
}

/* runProcessForOneTimeStep
 * input: the process name and the process data
 * output: a string
 *
 * Simulates the given process for one time step.
 * If it starts another process it will return that process's name, otherwise it returns NULL.
 */
char* runProcessForOneTimeStep( char *pName, processData *pData ){
    char *ret = NULL;

    printf( "%4d - Running process: %s-%d\n", time, pData->TLN, pData->heap[0] );
    authentication( pName, pData );

    pData->heap[5]++;
    //printf( "heap[5]: %d\n", pData->heap[5] );
    pData->heap[6]--;

    if( pData->heap[6]==0 && pData->heap[3]>1 ){
        ret = (char *)malloc(21);
        startProcess(ret, pData);
        pData->heap[6] = pData->heap[2];
    }

    time++;
    return ret;
}

/* promoteProcess
 * input: the process name and the process data
 * output: a string
 *
 * Prints out message saying a BACKGROUND process is being promoted to FOREGROUND
 */
void promoteProcess( char *pName, processData *pData ){
    authentication( pName, pData );
    printf( "Process promoted: %s-%d (still needs to run for %d cycles)\n\n", pData->TLN, pData->heap[0], pData->heap[1]-pData->heap[5] );
}

/* freeProcessData
 * input: the process name
 * output: initialized data for the process
 *
 * Initialize the data for a process.
 * Call this when a process is first added to your queue
 */
void freeProcessData( processData* pData ){
    printf( "Process data deleted: %s-%d (ran for %d cycles)\n", pData->TLN, pData->heap[0], pData->heap[5] );
    if( pData->heap[1]>pData->heap[5] ){
        printf( "Deleted with %d cycles left to do!\n", pData->heap[1]-pData->heap[5] );
    }
    if( pData->heap[5]>pData->heap[1] ){
        printf( "Run for %d cycles more cycles than was required!\n", pData->heap[5]-pData->heap[1] );
    }
    printf( "\n" );
    free(pData);
}

/************************ Code below this point is internal use only ************************/

/* startProcess
 * FOR INTERNAL USE ONLY
 */
void startProcess( char *pName, processData *pData ){
    char temp[7][4];
    int i;

    if( pData->heap[3]%2==1 && pData->name[0]=='F' )
        strcpy(temp[0],"B");
    else if( pData->heap[3]%2==1 && pData->name[0]=='B' )
        strcpy(temp[0],"F");
    else{
        temp[0][0] = pData->name[0];
        temp[0][1] = '\0';
    }

    strcpy( temp[1], pData->TLN );

    nameNum++;
    sprintf( temp[2], "%d", (nameNum)%100 );
    sprintf( temp[3], "%d", pData->heap[1] );

    sprintf( temp[4], "%d", pData->heap[2] );
    sprintf( temp[5], "%d", max(pData->heap[3]/2,1) );

    sprintf( temp[6], "%d", pData->heap[9] );

    strcpy( pName, "" );
    for( i=0; i<6; i++ ){
        strcat( pName, temp[i] );
        strcat( pName, "|" );
    }
    strcat( pName, temp[i] );
    pData->heap[8]++;
    pData->heap[9]+=pData->heap[1]/pData->heap[2];
}

/* authentication
 * FOR INTERNAL USE ONLY
 */
void authentication( char *pName, processData *pData ){
    if( pName==NULL || pData->name==NULL || strcmp(pName, pData->name) ){
        fprintf(stderr, "pName: %s || pData->name: %s :: \n", pName, pData->name);
        fprintf(stderr, "Authentication failed - process data was corrupted!\n");
    }
}

/* max
 * FOR INTERNAL USE ONLY
 */
int max( int a, int b ){
    if(a>b)
        return a;
    else
        return b;
}

/* powInt
 * FOR INTERNAL USE ONLY
 */
int powInt( int a, int b ){
    int product = 1;
    while( b>0 ){
        product*=a;
        b--;
    }
    return product;
}