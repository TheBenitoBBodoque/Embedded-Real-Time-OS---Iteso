/******************************************************************************
*   Filename:   gpt_cfg.c 
*
*   Description: GPT configuration file.
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


Gpt_Notification_type Gpt_Notification[MAX_NUMBER_OF_CHANNELS] = 
{
  GPT_NOTIFICATION_DISABLE,
  GPT_NOTIFICATION_DISABLE,
  GPT_NOTIFICATION_DISABLE,
  GPT_NOTIFICATION_DISABLE
};
  


/** Static configuration array for GPT Channels Specific Parameters 
- Channel
- Timeout in microseconds (uS)
- Interrupt Enable/Disable
- Microtimer base 0 or Microtimer base 1
- Channel Enabled/Disabled
*/                     
const Pit_ChannelConfigType Gpt_ChannelConfigType_initial[] = 
{ 

  // Channel 0
  {
   CHANNEL_0,
   PIT_MICROTIMER0,
   SchM_OsTick,    
  },
  // Channel 1
  {
   CHANNEL_1,
   PIT_MICROTIMER1,
   Task_100ms,    
  },
    // Channel 2
  {
   CHANNEL_2,
   PIT_MICROTIMER1,
   Task_200ms,    
  },
    // Channel 3
  {
   CHANNEL_3,
   PIT_MICROTIMER1,
   NULL,    
  }
};
  
/** Static configuration for GPT Module 
- Size of configuration array
- Gpt Module ON/OFF
- Freeze Enable/Disable
- Pointer to configuration array element  
*/
const Gpt_ConfigType Gpt_ConfigType_initial[] = 
{ 
  { 
    sizeof(Gpt_ChannelConfigType_initial)  / sizeof(Gpt_ChannelConfigType_initial[0]),
    PIT_ON,
    PIT_FRZ_ENABLE,
    Gpt_ChannelConfigType_initial   
  }
};                                      

/*****************************************************************************************************
* Code of module wide FUNCTIONS
*****************************************************************************************************/


/**************************************************************************************************/

/**
@} 
*/


  






