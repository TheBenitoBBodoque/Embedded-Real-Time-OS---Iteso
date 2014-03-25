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
*
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
