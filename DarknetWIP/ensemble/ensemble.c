/* sscc : C CODE OF SORTED EQUATIONS ensemble - INLINE MODE */

/* AUXILIARY DECLARATIONS */

#ifndef STRLEN
#define STRLEN 81
#endif
#define _COND(A,B,C) ((A)?(B):(C))
#ifdef TRACE_ACTION
#include <stdio.h>
#endif
#ifndef NULL
#define NULL ((char*)0)
#endif

#ifndef __EXEC_STATUS_H_LOADED
#define __EXEC_STATUS_H_LOADED

typedef struct {
unsigned int start:1;
unsigned int kill:1;
unsigned int active:1;
unsigned int suspended:1;
unsigned int prev_active:1;
unsigned int prev_suspended:1;
unsigned int exec_index;
unsigned int task_exec_index;
void (*pStart)();
void (*pRet)();
} __ExecStatus;

#endif
#define __ResetExecStatus(status) {\
   status.prev_active = status.active; \
   status.prev_suspended = status.suspended; \
   status.start = status.kill = status.active = status.suspended = 0; }
#define __DSZ(V) (--(V)<=0)
#define BASIC_TYPES_DEFINED
typedef int boolean;
typedef int integer;
typedef char* string;
#define _true 1
#define _false 0
#define __ensemble_GENERIC_TEST(TEST) return TEST;
typedef void (*__ensemble_APF)();
static __ensemble_APF *__ensemble_PActionArray;

#include "ensemble.h"

/* EXTERN DECLARATIONS */

#ifndef _NO_EXTERN_DEFINITIONS
#ifndef _NO_FUNCTION_DEFINITIONS
#ifndef _inTrainBounds_DEFINED
#ifndef inTrainBounds
extern integer inTrainBounds(integer ,float);
#endif
#endif
#ifndef _getSeen_DEFINED
#ifndef getSeen
extern float getSeen(integer);
#endif
#endif
#ifndef _maxEpochs_DEFINED
#ifndef maxEpochs
extern integer maxEpochs(integer);
#endif
#endif
#ifndef _getTrainSamples_DEFINED
#ifndef getTrainSamples
extern integer getTrainSamples();
#endif
#endif
#endif
#ifndef _NO_PROCEDURE_DEFINITIONS
#ifndef _tryBackup_DEFINED
#ifndef tryBackup
extern void tryBackup();
#endif
#endif
#ifndef _predictInput_DEFINED
#ifndef predictInput
extern void predictInput();
#endif
#endif
#ifndef _userInput_DEFINED
#ifndef userInput
extern void userInput();
#endif
#endif
#endif
#endif

/* INITIALIZED CONSTANTS */

/* MEMORY ALLOCATION */

static char __ensemble_V0[STRLEN];


/* INPUT FUNCTIONS */


/* ACTIONS */

/* PREDEFINED ACTIONS */

/* PRESENT SIGNAL TESTS */

/* OUTPUT ACTIONS */

/* ASSIGNMENTS */

/* PROCEDURE CALLS */

#define __ensemble_A1 \
userInput()
#define __ensemble_A2 \
predictInput()

/* CONDITIONS */

/* DECREMENTS */

/* START ACTIONS */

/* KILL ACTIONS */

/* SUSPEND ACTIONS */

/* ACTIVATE ACTIONS */

/* WRITE ARGS ACTIONS */

/* RESET ACTIONS */

#define __ensemble_A3 \


/* ACTION SEQUENCES */

/* FUNCTIONS RETURNING NUMBER OF EXEC */

int ensemble_number_of_execs () {
return (0);
}


/* AUTOMATON (STATE ACTION-TREES) */



static void __ensemble__reset_input () {
}

/* REDEFINABLE BIT TYPE */

#ifndef __SSC_BIT_TYPE_DEFINED
typedef char __SSC_BIT_TYPE;
#endif

/* REGISTER VARIABLES */

static __SSC_BIT_TYPE __ensemble_R[3] = {_true,
 _false,
 _false};

/* AUTOMATON ENGINE */

int ensemble () {
/* AUXILIARY VARIABLES */

static __SSC_BIT_TYPE E[6];
E[0] = !(_true);
if (__ensemble_R[0]) {
__ensemble_A3;
#ifdef TRACE_ACTION
fprintf(stderr, "__ensemble_A3\n");
#endif
}
E[1] = __ensemble_R[2]&&!(__ensemble_R[0]);
if (E[1]) {
__ensemble_A2;
#ifdef TRACE_ACTION
fprintf(stderr, "__ensemble_A2\n");
#endif
}
E[2] = __ensemble_R[0]||E[1];
E[3] = __ensemble_R[1]&&!(__ensemble_R[0]);
if (E[3]) {
__ensemble_A1;
#ifdef TRACE_ACTION
fprintf(stderr, "__ensemble_A1\n");
#endif
}
E[4] = E[2]||E[3];
E[5] = __ensemble_R[1]||__ensemble_R[2];
__ensemble_R[0] = !(_true);
__ensemble_R[1] = E[2];
__ensemble_R[2] = E[3];
__ensemble__reset_input();
return E[4];
}

/* AUTOMATON RESET */

int ensemble_reset () {
__ensemble_R[0] = _true;
__ensemble_R[1] = _false;
__ensemble_R[2] = _false;
__ensemble__reset_input();
return 0;
}
