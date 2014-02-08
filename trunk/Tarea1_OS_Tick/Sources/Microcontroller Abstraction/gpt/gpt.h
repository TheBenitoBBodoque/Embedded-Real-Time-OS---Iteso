/****************************************************************************************************/
/**
\file       gpt.h
\brief      Periodic Interrupt Timer initialization and low-level functions and prototypes
\author     TEAM
\version    1.0
\date       08/Feb/2014
*/
/****************************************************************************************************/
#ifndef __GPT_H        /*prevent duplicated includes*/
#define __GPT_H

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Core Modules */
/** Configuration Options */
  #include    "gpt_cfg.h"
/** S12X derivative information */
  #include  <mc9s12xep100.h>  
/** Variable types and common definitions */
  #include    "typedefs.h"

/** Used Modules */
/** Clock definitions and prototypes*/
  #include    "mcu.h"

/*****************************************************************************************************
* Declaration of module wide TYPES
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of  VARIABLEs - 
*****************************************************************************************************/

/* vfnPIT0_Callback, function to be called upon timeout of PIT channel 0 */
extern tCallbackFunction vfnPIT0_Callback;

/*****************************************************************************************************
* Definition of module wide MACROS / #DEFINE-CONSTANTS 
*****************************************************************************************************/

/** Periodic Interrupt Timer definitions */
#define    PIT_MICROTIMER_PERIOD            1000000
#define    PIT_TARGET_FREQ                  2000

/** Periodic Interrupt Timer macros */
#define    PIT_MICROTIMER_DIV               ( UINT8 ) ( ( gu32BusFrequency / PIT_MICROTIMER_PERIOD ) - 1 )
#define    PIT_VALUE                        ( ( PIT_MICROTIMER_PERIOD / PIT_TARGET_FREQ ) - 1 )

#define    PIT_MICROTIMER_PERIOD1           200000
#define    PIT_TARGET_FREQ1                 100000

#define    PIT_MICROTIMER1_DIV              ( UINT8 ) ( ( gu32BusFrequency / PIT_MICROTIMER_PERIOD1 ) - 1 )
#define    PIT_VALUE1                       ( ( PIT_MICROTIMER_PERIOD1 / PIT_TARGET_FREQ1 ) - 1 )

/*****************************************************************************************************
* Declaration of module wide FUNCTIONS
*****************************************************************************************************/

/** PIT Low level initialization */
void vfnPIT0_Init(tCallbackFunction  Callback);

/** PIT Low level Start procedure */
void vfnPIT0_Start(void);

/** PIT Low level Stop procedure */
void vfnPIT_Stop(void);

/** PIT Channel 0 ISR --> Main CPU  */
#pragma CODE_SEG __NEAR_SEG NON_BANKED
	void interrupt  vfnPIT_Channel0_Isr( void  );
#pragma CODE_SEG DEFAULT

/*******************************************************************************/

#endif /* __GPT_H */