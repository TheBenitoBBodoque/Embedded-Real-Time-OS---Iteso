#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include "mcu.h"
#include "gpt.h"

void pin_toggle(void);

void main(void) {
  /* put your own code here */
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
  
  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}

void pin_toggle(void){

 DDRA_DDRA0 = 1;
 PORTA_PA0 = ~PORTA_PA0;
}