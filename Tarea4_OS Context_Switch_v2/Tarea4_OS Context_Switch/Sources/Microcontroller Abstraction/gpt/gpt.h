/******************************************************************************
*   Filename:   gpt.h 
*
*   Description: Periodic Interrupt Timer initialization and low-level functions and prototypes
*
*
*   Revision History: This driver was developed by TEAM 4.
*                    
*                             
*   Date          #Change       Author
*   MM-DD-YY      Number:       Initials   Description of change
*   -----------   -----------   --------   ------------------------------------
*   02-10-14       00            JMR         Initial release
******************************************************************************/

#ifndef __GPT_H        /*prevent duplicated includes*/
#define __GPT_H

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Core Modules */
/** S12X derivative information */
  #include  <mc9s12xep100.h>  
/** Variable types and common definitions */
  #include    "typedefs.h"
/** Configuration Options */
  #include    "gpt_cfg.h"
  
/* Scheduler OS Tick */ 
  #include    "SchM.h"
/** Used Modules */
/** Clock definitions and prototypes*/
  #include    "mcu.h"

/*****************************************************************************************************
* Declaration of module wide TYPES
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of  VARIABLEs - 
*****************************************************************************************************/
extern u8 gInterrupt_PIT_flag;
/*****************************************************************************************************
* Definition of module wide MACROS / #DEFINE-CONSTANTS 
*****************************************************************************************************/

/** Periodic Interrupt Timer definitions */
#define    PIT_MICROTIMER_PERIOD            1000000
#define    PIT_TARGET_FREQ                  2000

/** Periodic Interrupt Timer macros */
#define    PIT_MICROTIMER_DIV               ( u8 ) ( ( mcal_mcu_gu32BusFrequency / PIT_MICROTIMER_PERIOD ) - 1 )
#define    PIT_VALUE                        ( ( PIT_MICROTIMER_PERIOD / PIT_TARGET_FREQ ) - 1 )


/*****************************************************************************************************
* Declaration of module wide FUNCTIONS
*****************************************************************************************************/

 extern void Gpt_Init( const Gpt_ConfigType* ConfigPtr );
 extern void Gpt_StartTimer( Pit_ChannelType Channel, Pit_ValueType Value ) ;
 extern void Gpt_StopTimer( Pit_ChannelType Channel ) ;
 extern void Gpt_EnableNotification( Pit_ChannelType Channel ) ;
 extern void Gpt_DisableNotification( Pit_ChannelType Channel ) ;

/** PIT Channel 0 ISR --> Main CPU  */
#pragma CODE_SEG __NEAR_SEG NON_BANKED
	void interrupt  vfnPIT_Channel0_Isr( void  );
	void interrupt  vfnPIT_Channel1_Isr( void  );
	void interrupt  vfnPIT_Channel2_Isr( void  );
	void interrupt  vfnPIT_Channel3_Isr( void  );
#pragma CODE_SEG DEFAULT

/*******************************************************************************/

#endif /* __GPT_H */