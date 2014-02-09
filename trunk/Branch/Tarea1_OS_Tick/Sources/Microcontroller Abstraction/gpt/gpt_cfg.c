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
/** Static configuration array for GPT Channels Specific Parameters 
- Channel
- Timeout in microseconds (uS)
- Interrupt Enable/Disable
- Microtimer base 0 or Microtimer base 1
- Channel Enabled/Disabled
*/                     
const Gpt_ChannelConfigType Gpt_ChannelConfigType_initial[] = 
{ 

  // Channel 0
  {
   CHANNEL_0,
   GPT_MICROTIMER0,
   Gpt_Channel0_callback,    
  },
  // Channel 1
  {
   CHANNEL_1,
   GPT_MICROTIMER0,
   Gpt_Channel1_callback,    
  },
  // Channel 2  
  {
   CHANNEL_2,
   GPT_MICROTIMER0,
   Gpt_Channel2_callback,    
  },
  // Channel 3  
  {
   CHANNEL_3,
   GPT_MICROTIMER0,
   Gpt_Channel3_callback,    
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
const Gpt_ConfigType Gpt_ConfigType_initial[] = 
{ 
  { 
    sizeof(Gpt_ChannelConfigType_initial)  / sizeof(Gpt_ChannelConfigType_initial[0]),
    GPT_ON,
    GPT_FRZ_ENABLE,
    Gpt_ChannelConfigType_initial   
  }
};                                      


const size_t Gpt_ConfigType_initial_size = sizeof(Gpt_ConfigType_initial)/sizeof(Gpt_ConfigType_initial[0]); 
/*****************************************************************************************************
* Code of module wide FUNCTIONS
*****************************************************************************************************/


/**************************************************************************************************/

/**
@} 
*/


  






