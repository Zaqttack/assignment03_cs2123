#ifndef _processSimulator_h
#define _processSimulator_h
#include <stdlib.h>
#include <stdbool.h>

#include "process.h"

processData* initializeProcessData( char *processName );
char* runProcessForOneTimeStep( char *pName, processData* pData );
void freeProcessData( processData* pData );
void promoteProcess( char *pName, processData *pData );

int max( int a, int b );
int powInt( int a, int b );

#endif
