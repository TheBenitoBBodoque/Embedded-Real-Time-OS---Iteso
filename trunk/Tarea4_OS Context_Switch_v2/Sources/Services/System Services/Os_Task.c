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
 /*JEBA Test */
static Task_Performance OS_TaskPerformance[5];

static u8 UartIndx;

static u8 initbuffer=0;
u8 gRotaBit_counter;
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
  PORTB_PB0= 1;
  
  for (index=0;index<500;index++){
   }
  PORTB_PB0= 0;
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
  PORTB_PB1= 1;
  
  for (index=0;index<700;index++){
  }
 /* if(!initbuffer)
  {
    
    for (index=0;index<5;index++)
    {
        OS_TaskPerformance[index].UartID = 'J';
        OS_TaskPerformance[index].MaxData = 'E';
        OS_TaskPerformance[index].MinData = 'B';
        OS_TaskPerformance[index].MeanData = 'A';
        OS_TaskPerformance[index].EndData = '1';
        OS_TaskPerformance[index].CReturn = '\n';
    }  
    initbuffer=0x01;
  } */
  PORTB_PB1= 0;
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
  PORTB_PB2= 1;
  for (index=0;index<100;index++){
  }
  PORTB_PB2= 0;
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
  PORTB_PB3= 1;   
  for (index=0;index<300;index++){
  }
  PORTB_PB3= 0;
 Error_Result=TerminateTask();
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
  PORTB_PB4= 1;
  for (index=0;index<1000;index++){
  }
  PORTB_PB4= 0;
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
  PORTB_PB5= 1;
  for (index=0;index<700;index++){
  }
  PORTB_PB5= 0;
  Error_Result=TerminateTask();
}

/*****************************************************************************************************                                                                        
*   Function: Timed_Task1
*
*   Description: Timer event periodic task callback function 100ms
*
*   Caveats: Non Reentrant
*****************************************************************************************************/
TASK (Task_100ms){
  PORTB_PB6= 1;
  
  PORTA_PA4= ~PORTA_PA4;
  if(gRotaBit_counter==4){
     gRotaBit_counter=0;
  }
  gRotaBit_counter++;
  PORTB_PB6= 0;
  
}

/*****************************************************************************************************                                                                        
*   Function: Timed_Task2
*
*   Description: Timer event periodic task callback function 200ms
*
*   Caveats: Non Reentrant
*****************************************************************************************************/
TASK (Task_200ms){
 u16 index;
 
 Status_Type Error_Result = E_OK;
  
  PORTB_PB7= 1;
  
  /*if(UartIndx < 4)
  {    
      UartIndx++;
  }else
  {
      UartIndx=0;
      vfnSCI_WriteBufferTx(SCI_CH0, &OS_TaskPerformance[0],sizeof(OS_TaskPerformance));
  }  */
  for (index=0;index<700;index++){
  }
  PORTB_PB7= 0;
  //Error_Result=TerminateTask();
}


