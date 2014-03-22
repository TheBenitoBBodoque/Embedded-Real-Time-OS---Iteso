#ifndef __OS_TYPES_H
#define __OS_TYPES_H
/******************************************************************************
*   Filename:   Os_Types.h
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
******************************************************************************/

/******************************************************************************
*   Include Files
******************************************************************************/
#include "typedefs.h"
/******************************************************************************
*   Macro Definitions  
******************************************************************************/
typedef u16 SchM_TaskOffsetType;
typedef u16 SchM_TaskMaskType;

#ifndef TASK
#define TASK(taskID) void taskID(void)
#endif

#define DeclareTask(taskID) extern TASK(taskID)

/******************************************************************************
*   Type Definitions
******************************************************************************/
/* Identifies a task, commonly associated with the TaskID */
typedef u16 TaskType;

/* Identifies a task state */
typedef u8 TaskStateType;

/* Reference to a variable of type TaskType */
typedef TaskType* TaskRefType;

/* Reference to a variable of type TaskStateType */
typedef TaskStateType* TaskStateRefType;


typedef enum
{
   TASK_1MS = 0,
   TASK_4MS,
   TASK_8MS,
   TASK_16MS,
   TASK_32MS,
   TASK_64MS
}SchM_TaskID;

typedef struct
{
  SchM_TaskID         TaskID;
  SchM_TaskMaskType   Mask;
  SchM_TaskOffsetType Offset;
  void(*SchM_TaskCallback)(void) ;
}SchM_Task_type;





/******************************************************************************
*   External Variables
******************************************************************************/
 
/******************************************************************************
*   Global Function Prototypes  
******************************************************************************/
#endif /*__OS_TYPES_H*/
