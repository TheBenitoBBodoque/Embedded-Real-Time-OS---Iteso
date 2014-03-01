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
*   02-11-14       01            SPA         Fix notification enable and disable.
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
typedef u16 Pit_ValueType;

/** Numeric identifier of a GPT channel */
typedef u8  Pit_ChannelType; 

/** Definition type for enabling/disabling the interrupt*/
typedef enum 
{
    PIT_INT_DISABLE = 0,
    PIT_INT_ENABLE
} Pit_InterruptEnable;

/** Definition type for the microtimer base selection of a GPT channel*/
typedef enum 
{
    PIT_MICROTIMER0 = 0,
    PIT_MICROTIMER1
} Pit_MicroTimerBase;

/** Definition type for the enable/disable for a GPT channel*/
typedef enum 
{
    PIT_CHANNEL_DISABLE = 0,
    PIT_CHANNEL_ENABLE
} Pit_ChannelEnable;

/** Definition type for the enable/disable for a PIT module*/
typedef enum 
{
    PIT_OFF = 0,
    PIT_ON
} Pit_ModuleEnable;

/** Definition type for the enable/disable for a PIT module*/
typedef enum 
{
    PIT_FRZ_DISABLE = 0,
    PIT_FRZ_ENABLE
} Pit_Freeze;

/** Definition type for the enable/disable notification*/
typedef enum
{
    GPT_NOTIFICATION_DISABLE = 0,
    GPT_NOTIFICATION_ENABLE
} Gpt_Notification_type;


/**
\struct     Gpt_ChannelConfigType
\brief      This is the type of data structure containing the initialization data for each GPT Channels.
            - Pit_Channel            -> Symbolic name of a pit channel.
            - Pit_MicroTimer         -> Period of a pit channel.
            - Pit_Channel_Callback   -> To register the callback to the channel. 
*/
typedef struct 
{
    Pit_ChannelType       Pit_Channel;
    Pit_MicroTimerBase    Pit_MicroTimer;
    tCallbackFunction     Pit_Channel_Callback;
} Pit_ChannelConfigType;

/**
\struct     Gpt_ConfigType
\brief      This is the type of data structure containing the initialization data for the GPT driver.
            - Gpt_NumOfChannelConfig   -> Number of channels config types.
            - Gpt_Module_Enable       -> Defines if the module is enabled/disabled.
            - *ptr_Gpt_ChannelConfig -> Pointer to Gpt_ChannelConfig Types.
*/
typedef struct 
{
    Pit_ChannelType              Pit_NumOfChannelConfig;
    Pit_ModuleEnable             Pit_Module_Enable;
    Pit_Freeze                   Pit_Freeze_Enable;  
    const Pit_ChannelConfigType *ptr_Pit_ChannelConfig;  
} Gpt_ConfigType;  

/*****************************************************************************************************
* Definition of module wide VARIABLES
*****************************************************************************************************/

extern const Gpt_ConfigType Gpt_ConfigType_initial[];
extern Gpt_Notification_type Gpt_Notification[];
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

 extern void Pit_Channel0_callback(void);
 extern void Pit_Channel1_callback(void);
 extern void Pit_Channel2_callback(void);
 extern void Pit_Channel3_callback(void);

 
/**************************************************************************************************/

#endif /* __GPT_CFG_H */

/**
@} 
*/