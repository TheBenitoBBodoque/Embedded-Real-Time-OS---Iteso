                     /****************************************************************************************************/
/**
@addtogroup Pwm
@{
\file       gpt_cfg.h
\brief      Pwm Configuration types, macros and functions prototypes.
\author     TEAM
\version    1.0
\date       04/10/2013
*/
/****************************************************************************************************/

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

/** Definition of the duty cycle of a PWM channel*/
typedef UINT16 Pwm_DutyCycleType;
/** Numeric identifier of a PWM channel */
typedef UINT8  Pwm_ChannelType;  
/** Definition of the period of a PWM channel */
typedef UINT16 Pwm_PeriodType;
/** Definition of the counter of a PWM channel */
typedef UINT16* Pwm_CounterType;

/** Definition type for ClockA Divider */
typedef enum 
{
  PRESCALE_A_0 = 0,
  PRESCALE_A_2,
  PRESCALE_A_4,
  PRESCALE_A_8,
  PRESCALE_A_16,
  PRESCALE_A_32,
  PRESCALE_A_64,
  PRESCALE_A_128
}Pwm_AClockDividerType;

/** Definition type for ClockB Divider */
typedef enum 
{
  PRESCALE_B_0 = 0,
  PRESCALE_B_2,
  PRESCALE_B_4,
  PRESCALE_B_8,
  PRESCALE_B_16,
  PRESCALE_B_32,
  PRESCALE_B_64,
  PRESCALE_B_128
}Pwm_BClockDividerType;

/** Definition type for ClockSA Divider */
typedef UINT8 Pwm_SAClockDividerType;
/** Definition type for ClockSB Divider */
typedef UINT8 Pwm_SBClockDividerType;

/** Definition type for enabling/disabling a port*/
typedef enum 
{
    PWM_DISABLE = 0,
    PWM_ENABLE
} Pwm_EnableType;

/** Definition type for the aligment of a PWM channel*/
typedef enum 
{
    PWM_LEFT = 0,
    PWM_CENTER
} Pwm_AligmentType;

/** Definition type for the clock used for a PWM channel*/
typedef enum 
{
    PWM_CLOCK = 0,
    PWM_CLOCK_S
} Pwm_ClockType;

/** Definition type for the output state of a PWM channel */
typedef enum 
{
    PWM_LOW = 0,
    PWM_HIGH
} Pwm_OutputStateType;

/** Definition type for the Polarity of a PWM channel. Is related with Pwm Class value*/
typedef enum 
{
    PWM_POLARITY_LOW = 0,
    PWM_POLARITY_HIGH
} Pwm_PolarityType;

/** Definition of the type of edge notification of a PWM channel */
typedef enum 
{
	PWM_FALLING_EDGE = PWM_LOW,
	PWM_RISING_EDGE =  PWM_HIGH,
	PWM_BOTH_EDGES
} Pwm_EdgeNotificationType;

/** Definition of the class of a PWM channel. Class A, B, C, D supported */
typedef enum 
{
    PWM_CLASS_A = 0,
    PWM_CLASS_B,
    PWM_CLASS_C,
    PWM_CLASS_D
} Pwm_ClassType;
  
/** Definition of the Resolution of PWM channels  */
typedef enum 
{
    PWM_8BITS = 0,
    PWM_16BITS
} Pwm_ResolutionType;

/**
\struct     Pwm_ChannelConfigType
\brief      This is the type of data structure containing the initialization data for each PWM Channels.
            - Pwm_Channel     -> Symbolic name of a wpm channel.
            - Pwm_Enable      -> Enable/Disable pwm channel option.
            - Pwm_DutyCycle   -> Duty cycle of a pwm channel.
            - Pwm_Period      -> Period of a pwm channel.
            - Pwm_Class       -> Class of a pwm channel.
            - Pwm_Aligment    -> Aligment of a pwm channel.
            - Pwm_Clock       -> Clock used for a pwm channel.
            - Pwm_Resolution  -> Resolution for a pwm channel.
*/
typedef struct 
{
    Pwm_ChannelType       Pwm_Channel;
    Pwm_EnableType        Pwm_Enable;
    Pwm_DutyCycleType     Pwm_DutyCycle;
    Pwm_PeriodType        Pwm_Period;
    Pwm_ClassType         Pwm_Class;
    Pwm_AligmentType      Pwm_Aligment;
    Pwm_ClockType         Pwm_Clock;
    Pwm_ResolutionType    Pwm_Resolution; 
} Pwm_ChannelConfigType;

/**
\struct     Pwm_ConfigType
\brief      This is the type of data structure containing the initialization data for the PWM driver.
            - numPwm_ChannelConfig   -> Number of channels config types.
            - Pwm_AClockDivider      -> Clock A Divider
            - Pwm_BClockDivider      -> Clock B Divider
            - Pwm_SAClockDivider     -> Clock SA Divider
            - Pwm_SBClockDivider     -> Clock SB Divider
            - *ptr_Pwm_ChannelConfig -> Pointer to Pwm_ChannelConfig Types.
*/
typedef struct 
{
    UINT8                        numPwm_ChannelConfig;
    Pwm_AClockDividerType        Pwm_AClockDivider;
    Pwm_BClockDividerType        Pwm_BClockDivider;
    Pwm_SAClockDividerType       Pwm_SAClockDivider;
    Pwm_SBClockDividerType       Pwm_SBClockDivider;  
    const Pwm_ChannelConfigType *ptr_Pwm_ChannelConfig;  
} Pwm_ConfigType;  

/*****************************************************************************************************
* Definition of module wide VARIABLES
*****************************************************************************************************/

extern const Pwm_ConfigType Pwm_ConfigType_initial[];
extern const size_t Pwm_ConfigType_initial_size;
/*****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs 
*****************************************************************************************************/

#define CHANNEL_0 0
#define CHANNEL_1 1
#define CHANNEL_2 2
#define CHANNEL_3 3
#define CHANNEL_4 4
#define CHANNEL_5 5
#define CHANNEL_6 6
#define CHANNEL_7 7
#define MAX_NUMBER_OF_CHANNELS 8

#define CHANNEL_01 1
#define CHANNEL_23 3
#define CHANNEL_45 5
#define CHANNEL_67 7 

/*****************************************************************************************************
* Declaration of module wide FUNCTIONS
*****************************************************************************************************/

/* Checks if PWM channel configuration exists */
UINT8 Pwm_ValidateChannel(Pwm_ChannelType ChannelNumber);
 
/**************************************************************************************************/

#endif /* __GPT_CFG_H */

/**
@} 
*/