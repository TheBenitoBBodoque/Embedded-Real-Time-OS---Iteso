                              /****************************************************************************************************/
/**
@addtogroup Gpt
@{
\file       gpt_cfg.c
\brief      PWM configuration file.
\author     TEAM
\version    1.0
\date       08/Feb/2014
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Port function prototypes definitions */
 #include "gpt_cfg.h"

/*****************************************************************************************************
* Definition of  VARIABLEs - 
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs 
*****************************************************************************************************/
/** Static configuration array for PWM Channels Specific Parameters 
- Channel
- Enable/Disable
- Duty Cycle
- Period
- Class
- Aligment
- PWM Clock
- Resolution  If the resolution is selected as 16 bits, the pair channel configuration are going to be ignored
- PWM Counter
*/                     
const Pwm_ChannelConfigType Pwm_ChannelConfigType_initial[] = 
{ 

  // Channel 0
  {
   CHANNEL_0,
   PWM_ENABLE,
   30U,
   50U,
   PWM_CLASS_A,
   PWM_LEFT,
   PWM_CLOCK_S,
   PWM_8BITS,    
  },
  // Channel 1
  {
   CHANNEL_1,
   PWM_ENABLE,
   40U,
   10U,
   PWM_CLASS_B,
   PWM_LEFT,
   PWM_CLOCK_S,
   PWM_8BITS,  
  },
  // Channel 2  
  {
   CHANNEL_2,
   PWM_ENABLE,
   70U,
   20U,
   PWM_CLASS_C,
   PWM_LEFT,
   PWM_CLOCK_S,
   PWM_8BITS, 
  },
  // Channel 3  
  {
   CHANNEL_3,
   PWM_ENABLE,
   90U,
   100U,
   PWM_CLASS_D,
   PWM_LEFT,
   PWM_CLOCK_S,
   PWM_8BITS,
  },
  // Channel 4  
  {
   CHANNEL_4,
   PWM_ENABLE,
   90U,
   100U,
   PWM_CLASS_D,
   PWM_LEFT,
   PWM_CLOCK_S,
   PWM_8BITS, 
  },
  // Channel 5  
  {
   CHANNEL_5,
   PWM_ENABLE,
   90U,
   100U,
   PWM_CLASS_D,
   PWM_LEFT,
   PWM_CLOCK_S,
   PWM_8BITS, 
  },
  // Channel 6  
  /*{
   CHANNEL_6,
   PWM_ENABLE,
   90U,
   100U,
   PWM_CLASS_D,
   PWM_LEFT,
   PWM_CLOCK_S,
   PWM_8BITS, 
  },*/
  // Channel 7  
  {
   CHANNEL_7,
   PWM_ENABLE,
   85U,
   300U,
   PWM_CLASS_A,
   PWM_LEFT,
   PWM_CLOCK_S,
   PWM_16BITS,
  } 
};
  
/** Static configuration for PWM Module 
- Size of configuration array
- Bus Clock Prescale for clock A
- Bus Clock Prescale for clock B
- Prescale for clock SA
- Prescale for clock SB
- Pointer to configuration array element  
*/
const Pwm_ConfigType Pwm_ConfigType_initial[] = 
{ 
  { 
    sizeof(Pwm_ChannelConfigType_initial)  / sizeof(Pwm_ChannelConfigType_initial[0]),
    PRESCALE_A_2,
    PRESCALE_B_2,
    0x0F,
    0xFF,
    Pwm_ChannelConfigType_initial   
  }
};                                      


const size_t Pwm_ConfigType_initial_size = sizeof(Pwm_ConfigType_initial)/sizeof(Pwm_ConfigType_initial[0]); 
/*****************************************************************************************************
* Code of module wide FUNCTIONS
*****************************************************************************************************/


/****************************************************************************************************/
/**
* \brief    Checks if PWM channel configuration exists.
* \author   Alejandro Guerena, Jose Miguel Reyes, Sergio Pineda
* \param    Pwm_ChannelType ChannelNumber - Numeric identifier of a PWM channel.
* \return   UINT8 - 1 - Channel configuration does exist, 0 - Channel configuration does not exist
* \details  \b Reentrancy Non Reentrant  
* \details  \b Sync/Async Synchronous     
*/
  
/***************************************************************************************************/

UINT8 Pwm_ValidateChannel(Pwm_ChannelType ChannelNumber) 
{

    UINT8 i,j,k;
    
    k = sizeof(Pwm_ConfigType_initial);
    
    for(j = 0; j<(Pwm_ConfigType_initial_size); j++) 
    {    
        for(i = 0; i<Pwm_ConfigType_initial[j].numPwm_ChannelConfig; i++) 
        {         
            if(Pwm_ConfigType_initial[j].ptr_Pwm_ChannelConfig[i].Pwm_Channel == ChannelNumber) 
                return TRUE; 
        }                  
    }                 

    return FALSE;
}

/**************************************************************************************************/

/**
@} 
*/


  






