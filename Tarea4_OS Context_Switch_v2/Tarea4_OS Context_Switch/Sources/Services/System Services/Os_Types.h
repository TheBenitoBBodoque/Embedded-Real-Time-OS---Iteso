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
*   03-29-14       10            SPA        OS Dispatcher and OSEK functions
*   03-29-14       11            JMR        Fix Issues found in OS Dispatcher and OSEK functions
******************************************************************************/

/******************************************************************************
*   Include Files
******************************************************************************/
#include "typedefs.h"
/******************************************************************************
*   Macro Definitions  
******************************************************************************/

#ifndef TASK
#define TASK(taskID) void taskID(void)
#endif

#define DeclareTask(taskID) extern TASK(taskID)

/******************************************************************************
*   Type Definitions
******************************************************************************/
/* Identifies a task state */
typedef u8 TaskStateType;

/* Identifies a task, commonly associated with the TaskID */
typedef u16 TaskType;

/* Reference to a variable of type TaskOffsetType */
typedef u16 TaskOffsetType;

/* Reference to a variable of type TaskMaskType */
typedef u16 TaskMaskType;

/* Reference to a variable of type TaskStackSize */
typedef u16 TaskStackSize;

/* Reference to a variable of type TaskRelDeadline */
typedef u16 TaskRelDeadline;

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
   TASK_64MS,
   MAX_NUM_TASK
}TaskID;

typedef enum
{
   PRIORITY_0 = 0,
   PRIORITY_1,
   PRIORITY_2,
   PRIORITY_3,
   PRIORITY_4,
   PRIORITY_5,
   MAX_PRIORITY
}TaskPriority;

typedef enum
{
   E_OK = 0,
   E_OS_ACCESS,
   E_OS_CALLEVEL,
   E_OS_ID,
   E_OS_LIMIT,
   E_OS_NOFUNC,
   E_OS_RESOURCE,
   E_OS_STATE,
   E_OS_VALUE
}Status_Type;

typedef enum 
{
   SUSPENDED = 0,
   READY,
   RUNNING
}TaskStates;

typedef struct
{
  u16 StartAddress;
  u16 EndAddress;
}StackInformation;

typedef struct
{
  u16 Relative;
  u16 Absolute;
}TaskDeadline;

typedef struct
{
  u16   CCR_TaskContext_u16;
  u16     D_TaskContext_u16;
  u16     X_TaskContext_u16;
  u16     Y_TaskContext_u16;
  u16    PC_TaskContext_u16;
  u16 PPAGE_TaskContext_u16;
  u16    SP_TaskContext_u16;
}TaskContextSave;

typedef enum
{
    TASK_NOPREEMPTED = 0,
    TASK_PREEMPTED
}TaskInterrupted;

typedef struct
{
    TaskContextSave BackgroundContextSave;
    TaskInterrupted BackgroundInterrupted;
}Background_Control_Block;

typedef struct
{
  TaskID              Task_ID;
  TaskPriority        Task_Priority;
  TaskStates          Task_State;
  StackInformation    Stack_Information;
  TaskDeadline        Task_Deadline;
  TaskContextSave     Task_ContextSave;
  TaskInterrupted     Task_Interrupted;
}Task_Control_Block;

typedef struct
{
  TaskID              Task_ID;
  TaskPriority        Task_Priority;
  TaskMaskType        Mask;
  TaskOffsetType      Offset;
  TaskStackSize       Size;
  TaskRelDeadline     RelDeadline;
  void(*TaskCallback)(void);
}Task_Descriptor;

typedef struct
{       
    u8      UartID;
    u8      MaxData;
    u8      MinData;
    u8      MeanData;
    u8      EndData;
    u8      CReturn;    
}Task_Performance;
/******************************************************************************
*   External Variables
******************************************************************************/
 
/******************************************************************************
*   Global Function Prototypes  
******************************************************************************/
#endif /*__OS_TYPES_H*/
