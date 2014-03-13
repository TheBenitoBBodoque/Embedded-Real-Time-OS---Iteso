/******************************************************************************
*   Filename:   SchM_Task.c 
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
#include "SchM_Tasks.h"
#include "SchM_Types.h"
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
*   Function: SchM_Task_1ms
*
*   Description: Scheduler task callback function 1ms
*
*   Caveats: Non Reentrant
*****************************************************************************************************/
void SchM_Task_1ms(void)
{
  u16 index;
  PORTA_PA0= 1;
  
  for (index=0;index<500;index++){
  }
  PORTA_PA0= 0;
}

/*****************************************************************************************************                                                                        
*   Function: SchM_Task_4ms
*
*   Description: Scheduler task callback function 4ms
*
*   Caveats: Non Reentrant
*****************************************************************************************************/
void SchM_Task_4ms(void)
{
  u16 index;
  PORTA_PA1= 1;
  for (index=0;index<600;index++){
  }
  PORTA_PA1= 0;
}

/*****************************************************************************************************                                                                        
*   Function: SchM_Task_8ms
*
*   Description: Scheduler task callback function 8ms
*
*   Caveats: Non Reentrant
*****************************************************************************************************/
void SchM_Task_8ms(void)
{
  u16 index;
  PORTA_PA2= 1;
  for (index=0;index<100;index++){
  }
  PORTA_PA2= 0;
}

/*****************************************************************************************************                                                                        
*   Function: SchM_Task_16ms
*
*   Description: Scheduler task callback function 16ms
*
*   Caveats: Non Reentrant
*****************************************************************************************************/
void SchM_Task_16ms(void)
{
  u16 index;
  PORTA_PA3= 1;   
  for (index=0;index<300;index++){
  }
  PORTA_PA3= 0;
}

/*****************************************************************************************************                                                                        
*   Function: SchM_Task_32ms
*
*   Description: Scheduler task callback function 32ms
*
*   Caveats: Non Reentrant
*****************************************************************************************************/
void SchM_Task_32ms(void)
{
  u16 index;
  PORTB_PB0= 1;
  for (index=0;index<1000;index++){
  }
  PORTB_PB0= 0;
}

/*****************************************************************************************************                                                                        
*   Function: SchM_Task_64ms
*
*   Description: Scheduler task callback function 64ms
*
*   Caveats: Non Reentrant
*****************************************************************************************************/
void SchM_Task_64ms(void)
{
  u16 index;
  PORTB_PB1= 1;
  for (index=0;index<700;index++){
  }
  PORTB_PB1= 0;
}


