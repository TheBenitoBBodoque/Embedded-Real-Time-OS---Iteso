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
#include "SchM_Tasks.h"

/******************************************************************************
*   Macro Definitions  
******************************************************************************/

/* Task mask definition */
#define MASK_1MS   ((u16)(0x0001)) /* 0000 0001 */
#define MASK_4MS   ((u16)(0x0007)) /* 0000 0111 */
#define MASK_8MS   ((u16)(0x000F)) /* 0000 1111 */
#define MASK_16MS  ((u16)(0x001F)) /* 0001 1111 */
#define MASK_32MS  ((u16)(0x003F)) /* 0011 1111 */
#define MASK_64MS  ((u16)(0x007F)) /* 0111 1111 */

/* Task mask offset */
#define OFFSET_00  ((u16)(0))
#define OFFSET_01  ((u16)(1))
#define OFFSET_03  ((u16)(3))
#define OFFSET_05  ((u16)(5))
#define OFFSET_07  ((u16)(7))
#define OFFSET_11  ((u16)(11))
#define OFFSET_13  ((u16)(13))

/* Defines to be used for the OS tick and Scheduler flags*/
#define SCHM_OSTICK_ENABLED     (1u)
#define SCHEDULER_ENABLED       (1u)
#define SCHM_OSTICK_DISABLED    (0u)
#define SCHEDULER_DISABLED      (0u)

/******************************************************************************
*   Type Definitions
******************************************************************************/
typedef struct
{
   SchM_TaskID SchM_TaskNumberConfig;
   const SchM_Task_type *ptr_SchM_Task;  
}SchM_TaskConfigType;

/******************************************************************************
*   External Variables
******************************************************************************/
extern const SchM_TaskConfigType SchM_TaskConfigInitial[]; 
/******************************************************************************
*   Global Function Prototypes  
******************************************************************************/

#endif /*__SCHM_CFG_H*/
