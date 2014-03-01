#ifndef __SCHM_CFG_H
#define __SCHM_CFG_H
/******************************************************************************
*   Filename:   SchM_Cfg.h
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
#include "SchM_Types.h"

/******************************************************************************
*   Macro Definitions  
******************************************************************************/


/******************************************************************************
*   Type Definitions
******************************************************************************/
typedef enum
{
   TASK_1MS = 0,
   TASK_4MS,
   TASK_8MS,
   TASK_16MS
}SchM_TaskNumberType;

typedef struct
{
  SchM_TaskNumberType SchM_TaskNumber;
  u16 Mask;
  u16 Offset;
  void (*callback_function) (void);
}SchM_Task_type;

typedef struct
{
   SchM_TaskNumberType SchM_TaskNumber;
   const SchM_Task_type *ptr_SchM_Task;  
}SchM_TaskConfigType;
/******************************************************************************
*   External Variables
******************************************************************************/
 
/******************************************************************************
*   Global Function Prototypes  
******************************************************************************/

#endif /*__SCHM_CFG_H*/
