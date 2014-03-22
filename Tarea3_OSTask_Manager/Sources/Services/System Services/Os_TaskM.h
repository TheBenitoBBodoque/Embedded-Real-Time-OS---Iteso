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

extern TaskStateType ActivateTask(TaskType taskID);
extern TaskStateType TerminateTask (void);
extern TaskStateType GetTaskID(TaskRefType taskIDRef);
extern TaskStateType GetTaskState(TaskType taskID, TaskStateRefType stateRef);

#endif /*__OS_TASKM_H_*/
