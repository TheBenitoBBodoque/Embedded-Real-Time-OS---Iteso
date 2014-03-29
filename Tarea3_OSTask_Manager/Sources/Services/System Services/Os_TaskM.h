#ifndef __OS_TASKM_H_
#define __OS_TASKM_H_
/******************************************************************************
*   Filename:   Os_TaskM.h
*
*   Description:  
*
*
*   Revision history:
*
*   Date          CP#           Author     
*   MM-DD-YY      XXXXX:1       Initials   Description of change
*   -----------   -----------   --------   ------------------------------------
*   03-29-14       10            SPA        OS Dispatcher and OSEK functions
*   03-29-14       11            JMR        Fix Issues found in OS Dispatcher and OSEK functions
******************************************************************************/
#include "Os_Task.h"

/******************************************************************************
*   Macro Definitions  
******************************************************************************/


/******************************************************************************
*   Type Definitions
******************************************************************************/

/******************************************************************************
*   External Variables
******************************************************************************/
 
/******************************************************************************
*   Global Function Prototypes  
******************************************************************************/

extern Status_Type ActivateTask(TaskType taskID);
extern Status_Type TerminateTask (void);
extern Status_Type GetTaskID(TaskRefType taskIDRef);
extern Status_Type GetTaskState(TaskType taskID, TaskStateRefType stateRef);
extern void Dispatcher(void);

#endif /*__OS_TASKM_H_*/
