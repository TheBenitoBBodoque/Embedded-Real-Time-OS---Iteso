#ifndef __OS_TASKCFG_H
#define __OS_TASKCFG_H
/******************************************************************************
*   Filename:   Os_TaskCfg.h
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
*   03-29-14       12            EBA        Fix more issues
******************************************************************************/

/******************************************************************************
*   Include Files
******************************************************************************/
#include "Os_Types.h"

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

#define CNF_MAXTASKQUEUE ((u16)(5))
/******************************************************************************
*   Type Definitions
******************************************************************************/
typedef struct
{
   TaskID TaskNumberConfig;
   const Task_Descriptor *ptr_Task;  
}TaskConfigType;

/******************************************************************************
*   External Variables
******************************************************************************/
extern const TaskConfigType TaskConfigInitial[];
extern u16 DispacherArray[MAX_PRIORITY][CNF_MAXTASKQUEUE];
extern Task_Control_Block *__far TaskControlBlock;
extern Background_Control_Block BackgroundControlBlock;
/******************************************************************************
*   Global Function Prototypes  
******************************************************************************/

#endif /*__OS_TASKCFG_H*/
