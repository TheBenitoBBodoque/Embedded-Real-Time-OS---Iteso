/******************************************************************************
*   Filename:   gpt.c 
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
*   02-11-14       01            SPA         Fix notification enable and disable.
******************************************************************************/


/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Own headers */
/* Periodic Interrupt Timer routines prototypes */
#include    "gpt.h"

/*****************************************************************************************************
* Definition of  VARIABLEs - 
*****************************************************************************************************/

void Pit_Channel0_callback(void);
void Pit_Channel1_callback(void);
void Pit_Channel2_callback(void);
void Pit_Channel3_callback(void);

/*****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs 
*****************************************************************************************************/

/*****************************************************************************************************
* Code of module wide FUNCTIONS
*****************************************************************************************************/


/****************************************************************************************************/
/**
* \brief    Service for GPT initialization.
* \author   Jose Miguel Reyes, Sergio Pineda, Esteban Bernardo
* \param    ConfigPtr - Pointer to structure containing the Gpt initialization data. 
* \return   void
* \details  \b Reentrancy Non Reentrant  
* \details  \b Sync/Async Synchronous     
*/
/***************************************************************************************************/
void Gpt_Init(const Gpt_ConfigType *ConfigPtr)    
{
    
    u8 i;
   
    /* GPT Module Configuration */
    
    /* PIT counter freeze while in Freeze mode */
    PITCFLMT_PITFRZ = ConfigPtr->Pit_Freeze_Enable;
    
    /* Enable/Disable Periodic Interrupt Timer Module*/
    PITCFLMT_PITE =  ConfigPtr->Pit_Module_Enable;  

    /* Configuration of GPT Channel Registers*/                      
    for(i=0;i<ConfigPtr->Pit_NumOfChannelConfig;i++) 
    {
            // 16 bits- Resolution 
            switch(ConfigPtr->ptr_Pit_ChannelConfig[i].Pit_Channel) 
            {  
                case CHANNEL_0:
                    
                    /* 16-bit timer 0 counts with micro time base selected (time base 0 or time base 1) */
                    PITMUX_PMUX0           = ConfigPtr->ptr_Pit_ChannelConfig[i].Pit_MicroTimer;
                    
                    /* Precalculated PIT microtimer (8-bit time base divider) Configured to update the values in 
                    microseconds */
                    
                    if(ConfigPtr->ptr_Pit_ChannelConfig[i].Pit_MicroTimer == PIT_MICROTIMER0){
                        PITMTLD0               = PIT_MICROTIMER_DIV;
                    }else{  
                        PITMTLD1               = PIT_MICROTIMER_DIV;
                    }
                                          
                    break;        
                case CHANNEL_1:

                    /* 16-bit timer 0 counts with micro time base selected (time base 0 or time base 1) */
                    PITMUX_PMUX1           = ConfigPtr->ptr_Pit_ChannelConfig[i].Pit_MicroTimer;
                    
                    /* Precalculated PIT microtimer (8-bit time base divider) Configured to update the values in 
                    microseconds */
                    
                    if(ConfigPtr->ptr_Pit_ChannelConfig[i].Pit_MicroTimer == PIT_MICROTIMER0){
                        PITMTLD0               = PIT_MICROTIMER_DIV;
                    }else{  
                        PITMTLD1               = PIT_MICROTIMER_DIV;
                    }
                                               
                    break;       
                case CHANNEL_2:
                    
                    /* 16-bit timer 0 counts with micro time base selected (time base 0 or time base 1) */
                    PITMUX_PMUX2           = ConfigPtr->ptr_Pit_ChannelConfig[i].Pit_MicroTimer;
                    
                    /* Precalculated PIT microtimer (8-bit time base divider) Configured to update the values in 
                    microseconds */
                    
                    if(ConfigPtr->ptr_Pit_ChannelConfig[i].Pit_MicroTimer == PIT_MICROTIMER0){
                        PITMTLD0               = PIT_MICROTIMER_DIV;
                    }else{  
                        PITMTLD1               = PIT_MICROTIMER_DIV;
                    }
                                               
                    break;        
                case CHANNEL_3:
                    
                    /* 16-bit timer 0 counts with micro time base selected (time base 0 or time base 1) */
                    PITMUX_PMUX3           = ConfigPtr->ptr_Pit_ChannelConfig[i].Pit_MicroTimer;
                             
                    /* Precalculated PIT microtimer (8-bit time base divider) Configured to update the values in 
                    microseconds */
                    
                    if(ConfigPtr->ptr_Pit_ChannelConfig[i].Pit_MicroTimer == PIT_MICROTIMER0){
                        PITMTLD0               = PIT_MICROTIMER_DIV;
                    }else{  
                        PITMTLD1               = PIT_MICROTIMER_DIV;
                    } 
                                               
                    break;
            }        
    }
  
}

/****************************************************************************************************/
/**
* \brief    Starst/Run the GPT timer desired in the parameters .
* \author   Esteban Bernardo, Jose Miguel Reyes, Sergio Pineda
* \param    Channel - Channel to be started.
*           Value   - Value of the timeout in microseconds (Range: 0-65535).  
* \return   void
* \details  \b Reentrancy Non Reentrant  
* \details  \b Sync/Async Synchronous     
*/ 
/***************************************************************************************************/
void Gpt_StartTimer(Pit_ChannelType Channel, Pit_ValueType Value )   
{ 
    // 16 bits- Resolution 
            switch(Channel) 
            {  
                case CHANNEL_0:                    
                    /* Clear PTI interrupt flag */
                    PITTF_PTF0             = 1u;
                    
                    
                    if(Gpt_ConfigType_initial->ptr_Pit_ChannelConfig[0].Pit_MicroTimer == PIT_MICROTIMER0){
                    /* Load 8-bit microtimer load register 0 into the 8-bit micro timer down-counter 0 */
                        PITCFLMT_PFLMT0     = 1u;
                    }else{
                    /* Load 8-bit microtimer load register 1 into the 8-bit micro timer down-counter 1 */  
                        PITCFLMT_PFLMT1     = 1u;
                    }
                    
                    /* TimeOut value in microseconds  */
                    PITLD0                 = (Value-1);
                    
                    /* Load 16-bit timer load register 0 into the 16-bit timer down-counter 0 */
                    PITFLT_PFLT0        = 1u;
                    /* Enables PIT channel 0 */
                    PITCE_PCE0             = 1u;                        
                    /* Interrupt of PIT channel 0 is enabled */
                    PITINTE_PINTE0         = 1u;
                    
                    break;
                            
                case CHANNEL_1:
                    /* Clear PTI interrupt flag */
                    PITTF_PTF1             = 1u;
                    
                     if(Gpt_ConfigType_initial->ptr_Pit_ChannelConfig[1].Pit_MicroTimer == PIT_MICROTIMER0){
                    /* Load 8-bit microtimer load register 0 into the 8-bit micro timer down-counter 0 */
                        PITCFLMT_PFLMT0     = 1u;
                    }else{
                    /* Load 8-bit microtimer load register 1 into the 8-bit micro timer down-counter 1 */  
                        PITCFLMT_PFLMT1     = 1u;
                    }
                    
                    /* TimeOut value in microseconds  */
                    PITLD1                 = (Value-1);

                    /* Load 16-bit timer load register 0 into the 16-bit timer down-counter 0 */
                    PITFLT_PFLT1        = 1u;
                    /* Enables PIT channel 0 */
                    PITCE_PCE1             = 1u;                        
                    /* Interrupt of PIT channel 0 is enabled */
                    PITINTE_PINTE1         = 1u;
                                               
                    break;       
                case CHANNEL_2:
                    /* Clear PTI interrupt flag */
                    PITTF_PTF2             = 1u;
  
                    if(Gpt_ConfigType_initial->ptr_Pit_ChannelConfig[2].Pit_MicroTimer == PIT_MICROTIMER0){
                    /* Load 8-bit microtimer load register 0 into the 8-bit micro timer down-counter 0 */
                        PITCFLMT_PFLMT0     = 1u;
                    }else{
                    /* Load 8-bit microtimer load register 1 into the 8-bit micro timer down-counter 1 */  
                        PITCFLMT_PFLMT1     = 1u;
                    }
                    
                    /* TimeOut value in microseconds  */
                    PITLD2                 = (Value-1);
                    /* Load 16-bit timer load register 0 into the 16-bit timer down-counter 0 */
                    PITFLT_PFLT2        = 1u;
                    /* Enables PIT channel 0 */
                    PITCE_PCE2             = 1u;                        
                    /* Interrupt of PIT channel 0 is enabled */
                    PITINTE_PINTE2         = 1u;
                                               
                    break;        
                case CHANNEL_3:
                    /* Clear PTI interrupt flag */
                    PITTF_PTF3             = 1u;
                       
                    if(Gpt_ConfigType_initial->ptr_Pit_ChannelConfig[3].Pit_MicroTimer == PIT_MICROTIMER0){
                    /* Load 8-bit microtimer load register 0 into the 8-bit micro timer down-counter 0 */
                        PITCFLMT_PFLMT0     = 1u;
                    }else{
                    /* Load 8-bit microtimer load register 1 into the 8-bit micro timer down-counter 1 */  
                        PITCFLMT_PFLMT1     = 1u;
                    }  
                    
                    /* TimeOut value in microseconds  */
                    PITLD3                 = (Value-1);
                    
                    /* Enables PIT channel 0 */
                    PITCE_PCE3             = 1u;                        
                    /* Interrupt of PIT channel 0 is enabled */
                    PITINTE_PINTE3         = 1u;
                                               
                    break;
            }        
  
}

/****************************************************************************************************/
/**
* \brief    Stops the GPT channel desired in the parameters .
* \author   Esteban Bernardo, Jose Miguel Reyes, Sergio Pineda
* \param    Channel - Channel to be stopped.  
* \return   void
* \details  \b Reentrancy Non Reentrant  
* \details  \b Sync/Async Synchronous     
*/
/***************************************************************************************************/

void Gpt_StopTimer(Pit_ChannelType Channel) {
    // 16 bits- Resolution 
            switch(Channel) 
            {  
                case CHANNEL_0:                    
                    /* Enables PIT channel 0 */
                    PITCE_PCE0             = 0u;                        
                    break;                            
                case CHANNEL_1:
                    
                    /* Enables PIT channel 0 */
                    PITCE_PCE1             = 0u;                                                   
                    break;       
                case CHANNEL_2:
                    
                    /* Enables PIT channel 0 */
                    PITCE_PCE2             = 0u;                        
                    break;        
                case CHANNEL_3:
                
                    /* Enables PIT channel 0 */
                    PITCE_PCE3             = 0u;                                                  
                    break;
            }

}

/****************************************************************************************************/
/**
* \brief    Enable the GPT channel notification once an interruption is present.
* \author   Esteban Bernardo, Jose Miguel Reyes, Sergio Pineda
* \param    Channel - Channel to be configured for the notification.  
* \return   void
* \details  \b Reentrancy Non Reentrant  
* \details  \b Sync/Async Synchronous     
*/
/***************************************************************************************************/

void Gpt_EnableNotification( Pit_ChannelType Channel ) { 
            switch(Channel) 
            {  
                case CHANNEL_0:                    
                    /* Enables PIT notification channel 0 */
                    Gpt_Notification[0]          = GPT_NOTIFICATION_ENABLE ;                      
                    break;                            
                case CHANNEL_1:
                    
                    /* Enables PIT notification channel 1 */
                    Gpt_Notification[1]         = GPT_NOTIFICATION_ENABLE;                                                 
                    break;       
                case CHANNEL_2:
                    
                    /* Enables PIT notification channel 2 */
                    Gpt_Notification[2]         = GPT_NOTIFICATION_ENABLE;                       
                    break;        
                case CHANNEL_3:
                    /* Enables PIT notification channel 3 */
                    Gpt_Notification[3]         = GPT_NOTIFICATION_ENABLE;
                    break;
                default:
                    break;
            }

}

/***************************************************************************************************/
/**
* \brief    Disable the GPT channel notification.
* \author   Esteban Bernardo, Jose Miguel Reyes, Sergio Pineda
* \param    Channel - Channel to be configured for the notification.  
* \return   void
* \details  \b Reentrancy Non Reentrant  
* \details  \b Sync/Async Synchronous     
*/  
/***************************************************************************************************/
void Gpt_DisableNotification( Pit_ChannelType Channel ) { 
            switch(Channel) 
            {  
                case CHANNEL_0:                    
                    /* Enables PIT notification channel 0 */
                    Gpt_Notification[0]          = GPT_NOTIFICATION_DISABLE ;                      
                    break;                            
                case CHANNEL_1:
                    
                    /* Enables PIT notification channel 1 */
                    Gpt_Notification[1]         = GPT_NOTIFICATION_DISABLE;                                                 
                    break;       
                case CHANNEL_2:
                    
                    /* Enables PIT notification channel 2 */
                    Gpt_Notification[2]         = GPT_NOTIFICATION_DISABLE;                       
                    break;        
                case CHANNEL_3:
                    /* Enables PIT notification channel 3 */
                    Gpt_Notification[3]         = GPT_NOTIFICATION_DISABLE;
                    break;
                default:
                    break;
            }

}

/***************************************************************************************************/
/**
* \brief    Callback handled once an interrupt is generated by Channel 0.
* \author   Esteban Bernardo, Jose Miguel Reyes, Sergio Pineda
* \param    None  
* \return   void
* \details  \b Reentrancy Non Reentrant  
* \details  \b Sync/Async Synchronous     
*/ 
/***************************************************************************************************/
void SchM_OsTick(void){

 DDRA_DDRA0 = 1;
 PORTA_PA0 = ~PORTA_PA0;
}


/***************************************************************************************************/
/**
* \author   Anonymous
* \param    void
* \return   void
* \todo
*/
/***************************************************************************************************/
#pragma CODE_SEG __NEAR_SEG NON_BANKED

void interrupt  vfnPIT_Channel0_Isr( void  )
{
    /* Verify that Real Time Interrupt caused the interrupt */
    if( PITTF_PTF0 == 1u )
    {
        /*call callback function, if initialized*/
        if((Gpt_ConfigType_initial->ptr_Pit_ChannelConfig[0].Pit_Channel_Callback != NULL ) && (Gpt_Notification[0] == GPT_NOTIFICATION_ENABLE))
        {
            Gpt_ConfigType_initial->ptr_Pit_ChannelConfig[0].Pit_Channel_Callback();
        }
    }
    /* Clear the real time interrupt flag */
    PITTF_PTF0 = 1u;
}

void interrupt  vfnPIT_Channel1_Isr( void  )
{
    /* Verify that Real Time Interrupt caused the interrupt */
    if( PITTF_PTF1 == 1u )
    {
        /*call callback function, if initialized*/
        if((Gpt_ConfigType_initial->ptr_Pit_ChannelConfig[1].Pit_Channel_Callback != NULL ) && (Gpt_Notification[1] == GPT_NOTIFICATION_ENABLE))
        {
            Gpt_ConfigType_initial->ptr_Pit_ChannelConfig[1].Pit_Channel_Callback();
        }
    }
    /* Clear the real time interrupt flag */
    PITTF_PTF1 = 1u;
}

void interrupt  vfnPIT_Channel2_Isr( void  )
{
    /* Verify that Real Time Interrupt caused the interrupt */
    if( PITTF_PTF2 == 1u )
    {
        /*call callback function, if initialized*/
        if((Gpt_ConfigType_initial->ptr_Pit_ChannelConfig[2].Pit_Channel_Callback != NULL ) && (Gpt_Notification[2] == GPT_NOTIFICATION_ENABLE))
        {
            Gpt_ConfigType_initial->ptr_Pit_ChannelConfig[2].Pit_Channel_Callback();
        }
    }
    /* Clear the real time interrupt flag */
    PITTF_PTF2 = 1u;
}

void interrupt  vfnPIT_Channel3_Isr( void  )
{
    /* Verify that Real Time Interrupt caused the interrupt */
    if( PITTF_PTF3 == 1u )
    {
        /*call callback function, if initialized*/
        if((Gpt_ConfigType_initial->ptr_Pit_ChannelConfig[3].Pit_Channel_Callback != NULL ) && (Gpt_Notification[3] == GPT_NOTIFICATION_ENABLE))
        {
            Gpt_ConfigType_initial->ptr_Pit_ChannelConfig[3].Pit_Channel_Callback();
        }
    }
    /* Clear the real time interrupt flag */
    PITTF_PTF3 = 1u;
}
#pragma CODE_SEG DEFAULT
/*******************************************************************************/
