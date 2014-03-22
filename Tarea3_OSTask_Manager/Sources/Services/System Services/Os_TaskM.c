/******************************************************************************
*   Filename:   Os_TaskM.c 
*
*   Description:
*
*
*   Revision History:
*
*   Date          #Change       Author     
*   MM-DD-YY      Number:       Initials   Description of change
*   -----------   -----------   --------   ------------------------------------
*   
******************************************************************************/

/******************************************************************************
*   Include Files
******************************************************************************/ 
#include "typedefs.h"
#include "Os_TaskM.h"
/******************************************************************************
*   Local Macro Definitions
******************************************************************************/ 

/******************************************************************************
*   Local Type Definitions
******************************************************************************/

/******************************************************************************
*   Local Function Declarations
******************************************************************************/ 

/******************************************************************************
*   Global Variable Definitions
******************************************************************************/

/******************************************************************************
*   Static Variable Definitions
******************************************************************************/

/******************************************************************************
*   Global and Static Function Definitions
******************************************************************************/ 

/*****************************************************************************************************                                                                        
*   Function: ActivateTask(TaskType taskID)
*
*   Description: This API service moves the task identified by the input
*   taskID from the SUSPENDED state to the READY state if
*   no error occurred, and put the task into the priority buffer
*   queue tail
*
*   Caveats:
*****************************************************************************************************/
TaskStateType ActivateTask(TaskType taskID){

}

/*****************************************************************************************************                                                                        
*   Function: TerminateTask(void)
*
*   Description: This function terminates the task that invoked the service,
*   transferring it from the RUNNING to the SUSPENDED state, and move the task out
*   of the priority buffer queue
*
*   Caveats:
*****************************************************************************************************/

TaskStateType TerminateTask (void){

}

/*****************************************************************************************************                                                                        
*   Function: TaskStateType GetTaskID(TaskRefType taskIDRef)
*
*   Description: This service provides the application with the identifier of the
*   task that is presently running. It is intended to be used in hook
*   routines and library functions to check the task from which it
*   was invoked
*   Caveats:
*****************************************************************************************************/

TaskStateType GetTaskID(TaskRefType taskIDRef){

}

/*****************************************************************************************************                                                                        
*   Function: TaskStateType GetTaskState(TaskType taskID, TaskStateRefType stateRef)
*
*   Description: This service identifies the current state of the task identified
*   by the taskID parameter and places this value into the
*   variable referenced by stateRef
*   Caveats:
*****************************************************************************************************/

TaskStateType GetTaskState(TaskType taskID, TaskStateRefType stateRef){

}