/******************************************************************************
*   Filename:   Os_Task.c 
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
*   03-29-14       10            SPA        OS Dispatcher and OSEK functions
*   03-29-14       11            JMR        Fix Issues found in OS Dispatcher and OSEK functions
******************************************************************************/

/******************************************************************************
*   Include Files
******************************************************************************/ 
#include <mc9s12xep100.h>
#include "Os_Task.h"
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
*   Function: Task_1ms
*
*   Description: Scheduler task callback function 1ms
*
*   Caveats: Non Reentrant
*****************************************************************************************************/
TASK (Task_1ms)
{
  u16 index;
  Status_Type Error_Result = E_OK;
  PORTA_PA0= 1;
  
  for (index=0;index<500;index++){
  }
  PORTA_PA0= 0;
  Error_Result=TerminateTask();
}

/*****************************************************************************************************                                                                        
*   Function: Task_4ms
*
*   Description: Scheduler task callback function 4ms
*
*   Caveats: Non Reentrant
*****************************************************************************************************/
TASK (Task_4ms)
{
  u16 index;
  Status_Type Error_Result = E_OK;
  PORTA_PA1= 1;
  for (index=0;index<600;index++){
  }
  PORTA_PA1= 0;
  Error_Result=TerminateTask();
}

/*****************************************************************************************************                                                                        
*   Function: Task_8ms
*
*   Description: Scheduler task callback function 8ms
*
*   Caveats: Non Reentrant
*****************************************************************************************************/
TASK (Task_8ms)
{
  u16 index;
  Status_Type Error_Result = E_OK;
  PORTA_PA2= 1;
  for (index=0;index<100;index++){
  }
  PORTA_PA2= 0;
  Error_Result=TerminateTask();
}

/*****************************************************************************************************                                                                        
*   Function: Task_16ms
*
*   Description: Scheduler task callback function 16ms
*
*   Caveats: Non Reentrant
*****************************************************************************************************/
TASK (Task_16ms)
{
  u16 index;
  Status_Type Error_Result = E_OK;
  PORTA_PA3= 1;   
  for (index=0;index<300;index++){
  }
  PORTA_PA3= 0;
  TerminateTask();
}

/*****************************************************************************************************                                                                        
*   Function: Task_32ms
*
*   Description: Scheduler task callback function 32ms
*
*   Caveats: Non Reentrant
*****************************************************************************************************/
TASK (Task_32ms)
{
  u16 index;
  Status_Type Error_Result = E_OK;
  PORTB_PB0= 1;
  for (index=0;index<1000;index++){
  }
  PORTB_PB0= 0;
  Error_Result=TerminateTask();
}

/*****************************************************************************************************                                                                        
*   Function: Task_64ms
*
*   Description: Scheduler task callback function 64ms
*
*   Caveats: Non Reentrant
*****************************************************************************************************/
TASK (Task_64ms)
{
  u16 index;
  Status_Type Error_Result = E_OK;
  PORTB_PB1= 1;
  for (index=0;index<700;index++){
  }
  PORTB_PB1= 0;
  Error_Result=TerminateTask();
}


