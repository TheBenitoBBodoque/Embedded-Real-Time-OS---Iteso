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
  DDRA_DDRA0 = 1;
  vfnPIT0_Init(pin_toggle);
  EnableInterrupts;
  
  vfnPIT0_Start();

  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}

void pin_toggle(void){


 PORTA_PA0 = ~PORTA_PA0;
}