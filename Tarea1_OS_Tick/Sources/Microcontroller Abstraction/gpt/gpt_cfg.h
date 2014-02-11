/******************************************************************************
*   Filename:   gpt_cfg.c 
*
*   Description: Gpt Configuration types, macros and functions prototypes.
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


#ifndef __GPT_CFG_H
#define __GPT_CFG_H

/*****************************************************************************************************
* Include files
*****************************************************************************************************/  

/** Core modules */
/** Configuration Options */
#include "mcu_cfg.h"
/** MCU derivative information */
#include <mc9s12xep100.h>
/** Variable types and common definitions */
#include "typedefs.h"
#include "stddef.h"
/** Used modules */

/*****************************************************************************************************
* Declaration of module wide TYPEs 
*****************************************************************************************************/

/** Definition of the timeout of a GPT channel. Range: 0-65535*/
typedef u16 Gpt_ValueType;

/** Numeric identifier of a GPT channel */
typedef u8  Gpt_ChannelType; 

/** Definition type for enabling/disabling the interrupt*/
typedef enum 
{
    GPT_INT_DISABLE = 0,
    GPT_INT_ENABLE
} Gpt_InterruptEnable;

/** Definition type for the microtimer base selection of a GPT channel*/
typedef enum 
{
    GPT_MICROTIMER0 = 0,
    GPT_MICROTIMER1
} Gpt_MicroTimerBase;

/** Definition type for the enable/disable for a GPT channel*/
typedef enum 
{
    GPT_CHANNEL_DISABLE = 0,
    GPT_CHANNEL_ENABLE
} Gpt_ChannelEnable;

/** Definition type for the enable/disable for a GPT module*/
typedef enum 
{
    GPT_OFF = 0,
    GPT_ON
} Gpt_ModuleEnable;

/** Definition type for the enable/disable for a GPT module*/
typedef enum 
{
    GPT_FRZ_DISABLE = 0,
    GPT_FRZ_ENABLE
} Gpt_Freeze;

/**
\struct     Gpt_ChannelConfigType
\brief      This is the type of data structure containing the initialization data for each GPT Channels.
            - Gpt_Channel            -> Symbolic name of a gpt channel.
            - Gpt_MicroTimer         -> Period of a gpt channel.
            - Gpt_Channel_Callback   -> To register the callback to the channel. 
*/
typedef struct 
{
    Gpt_ChannelType       Gpt_Channel;
    Gpt_MicroTimerBase    Gpt_MicroTimer;
    tCallbackFunction     Gpt_Channel_Callback;
} Gpt_ChannelConfigType;

/**
\struct     Gpt_ConfigType
\brief      This is the type of data structure containing the initialization data for the GPT driver.
            - Gpt_NumOfChannelConfig   -> Number of channels config types.
            - Gpt_Module_Enable       -> Defines if the module is enabled/disabled.
            - *ptr_Gpt_ChannelConfig -> Pointer to Gpt_ChannelConfig Types.
*/
typedef struct 
{
    Gpt_ChannelType              Gpt_NumOfChannelConfig;
    Gpt_ModuleEnable             Gpt_Module_Enable;
    Gpt_Freeze                   Gpt_Freeze_Enable;  
    const Gpt_ChannelConfigType *ptr_Gpt_ChannelConfig;  
} Gpt_ConfigType;  

/*****************************************************************************************************
* Definition of module wide VARIABLES
*****************************************************************************************************/

extern const Gpt_ConfigType Gpt_ConfigType_initial[];
extern const size_t Gpt_ConfigType_initial_size;
/*****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs 
*****************************************************************************************************/

#define CHANNEL_0               0
#define CHANNEL_1               1
#define CHANNEL_2               2
#define CHANNEL_3               3
#define MAX_NUMBER_OF_CHANNELS  4


/*****************************************************************************************************
* Declaration of module wide callback FUNCTIONS
*****************************************************************************************************/
 extern void Gpt_Channel0_callback(void);
 extern void Gpt_Channel1_callback(void);
 extern void Gpt_Channel2_callback(void);
 extern void Gpt_Channel3_callback(void);
 
/**************************************************************************************************/

#endif /* __GPT_CFG_H */

/**
@} 
*/