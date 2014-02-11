/******************************************************************************
*   Filename:   main.c 
*
*   Description: main.c
*
*
*   Revision History:
*
*                             
*   Date          #Change       Author
*   MM-DD-YY      Number:       Initials   Description of change
*   -----------   -----------   --------   ------------------------------------
*   02-10-14       00            SPA         Initial release
******************************************************************************/

/******************************************************************************
*   Include Files
******************************************************************************/ 
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include "mcu.h"
#include "gpt.h"

/******************************************************************************
*   Local Macro Definitions
******************************************************************************/ 

/******************************************************************************
*   Local Type Definitions
******************************************************************************/

/******************************************************************************
*   Local Function Declarations
******************************************************************************/ 
void pin_toggle(void);
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
*   Function: main()
*
*   Description: what I can say about it, it just the tipical main
*
*   Caveats:
*****************************************************************************************************/
void main(void) 
{
  /*Disable interrupts to start the MCU configuration*/  
  DisableInterrupts;
  /* Intilialize the interupt vector base address for default location */
  IVBR = 0xFFu;
    
  Mcu_Init();
  /** Port A, Channel 0 */
  
  //vfnPIT0_Init(pin_toggle);
  Gpt_Init(&Gpt_ConfigType_initial[0]);
  
  EnableInterrupts;
  
  ///vfnPIT0_Start();
  Gpt_StartTimer(CHANNEL_0, 500u);
  Gpt_StartTimer(CHANNEL_1, 10000u);
  Gpt_StartTimer(CHANNEL_2, 20000u);
  Gpt_StartTimer(CHANNEL_3, 30000u);
  Gpt_DisableNotification(CHANNEL_1);
  Gpt_StopTimer(CHANNEL_2);
  Gpt_DisableNotification(CHANNEL_3);
  
  for(;;) 
  {
    _FEED_COP(); /* feeds the dog */
  } 
  /* loop forever */
  /* please make sure that you never leave main */
}

void pin_toggle(void){

 DDRA_DDRA0 = 1;
 PORTA_PA0 = ~PORTA_PA0;
}