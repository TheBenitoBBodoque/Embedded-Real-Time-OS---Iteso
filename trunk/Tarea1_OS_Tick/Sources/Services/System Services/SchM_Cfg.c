/******************************************************************************
*   Filename:   SchM_Cfg.c 
*
*   Description:
*
*
*   Revision History:
*
*   Date          CP#           Author     
*   MM-DD-YY      XXXXX:1       Initials   Description of change
*   -----------   -----------   --------   ------------------------------------
*   03-01-14       02            SPA        OS Task Initial Release
******************************************************************************/

/******************************************************************************
*   Include Files
******************************************************************************/ 
#include <mc9s12xep100.h>
#include "SchM_Cfg.h"
#include "SchM_Tasks.h"
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
const SchM_Task_type SchM_TaskInitial[]=
{
  {
    TASK_1MS,
    0,
    0,
    SchM_Task_1ms,
  },
  {
    TASK_4MS,
    4,
    0,
    SchM_Task_4ms,
  },
  {
    TASK_8MS,
    8,
    0,
    SchM_Task_8ms,
  }
};

const SchM_TaskConfigType SchM_TaskConfigInitial[]=
{
  {
    sizeof(SchM_TaskInitial)/sizeof(SchM_TaskInitial[0]), 
    SchM_TaskInitial
  }
};
/******************************************************************************
*   Static Variable Definitions
******************************************************************************/

/******************************************************************************
*   Global and Static Function Definitions
******************************************************************************/ 
