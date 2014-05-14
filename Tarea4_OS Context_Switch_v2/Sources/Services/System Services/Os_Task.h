#ifndef __OS_TASK_H
#define __OS_TASK_H
/******************************************************************************
*   Filename:   Os_Task.h
*
*   Description:  
*
*
*   Revision history:
*
*   Date          CP#           Author     
*   MM-DD-YY      XXXXX:1       Initials   Description of change
*   -----------   -----------   --------   ------------------------------------
*   03-01-14       02            SPA        OS Task Initial Release
*   03-29-14       10            SPA        OS Dispatcher and OSEK functions
*   03-29-14       11            JMR        Fix Issues found in OS Dispatcher and OSEK functions
******************************************************************************/

/******************************************************************************
*   Include Files
******************************************************************************/
#include "Os_TaskCfg.h"
#include "Os_TaskM.h"
#include  "serial.h"
/******************************************************************************
*   Macro Definitions  
******************************************************************************/

/******************************************************************************
*   Type Definitions
******************************************************************************/

/******************************************************************************
*   External Variables
******************************************************************************/
extern u8 gRotaBit_counter;
/******************************************************************************
*   Global Function Prototypes  
******************************************************************************/
DeclareTask(Task_1ms);
DeclareTask(Task_4ms);
DeclareTask(Task_8ms);
DeclareTask(Task_16ms);
DeclareTask(Task_32ms);
DeclareTask(Task_64ms);
DeclareTask(Task_100ms);
DeclareTask(Task_200ms);

#endif /*__OS_TASK_H*/
