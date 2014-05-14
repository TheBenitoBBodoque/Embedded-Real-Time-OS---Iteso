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
#include "SchM.h"
#include "int_vectors.h"


/******************************************************************************
*   Local Macro Definitions
******************************************************************************/ 
#define Init_Interrupt_Vector()  IVBR = 0xFFu
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
*   Function: main()
*
*   Description: what I can say about it, it just the tipical main
*
*   Caveats:
*****************************************************************************************************/
void main(void) 
{
  /*Disable interrupts to start the MCU configuration*/  
  DisableAllInterrupts();
  /* Intilialize the interupt vector base address for default location */
  Init_Interrupt_Vector();
    
  Mcu_Init();
  DDRA =0xFF;
  DDRB =0xFF;
  	/* SCI Initialization */
  vfnSCI_Init(&SCI_config[0]);
  
  EnableAllInterrupts();
  
  SchM_Init(TaskConfigInitial);
  /* Loop Forever and ever */
  SchM_Start();
}
