/****************************************************************************************************/
/**
\file       gpt.c
\brief      Periodic Interrupt Timer initialization and low-level functions and prototypes
\author     TEAM
\version    1.0
\date       08/Feb/2014
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Own headers */
/* Periodic Interrupt Timer routines prototypes */
#include    "gpt.h"

/*****************************************************************************************************
* Definition of  VARIABLEs - 
*****************************************************************************************************/

void Gpt_Channel0_callback(void);
void Gpt_Channel1_callback(void);
void Gpt_Channel2_callback(void);
void Gpt_Channel3_callback(void);

/*****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs 
*****************************************************************************************************/

/*****************************************************************************************************
* Code of module wide FUNCTIONS
*****************************************************************************************************/

/****************************************************************************************************/
/**
* \brief    Service for PWM initialization.
* \author   Alejandro Guerena, Jose Miguel Reyes, Sergio Pineda
* \param    ConfigPtr - Pointer to structure containing the Pwm' initialization data. 
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
    PITCFLMT_PITFRZ = ConfigPtr->Gpt_Freeze_Enable;
    
    /* Enable/Disable Periodic Interrupt Timer Module*/
    PITCFLMT_PITE =  ConfigPtr->Gpt_Module_Enable;  

    /* Configuration of GPT Channel Registers*/                      
    for(i=0;i<ConfigPtr->Gpt_NumOfChannelConfig;i++) 
    {
            // 16 bits- Resolution 
            switch(ConfigPtr->ptr_Gpt_ChannelConfig[i].Gpt_Channel) 
            {  
                case CHANNEL_0:
                    
                    /* 16-bit timer 0 counts with micro time base selected (time base 0 or time base 1) */
                    PITMUX_PMUX0           = ConfigPtr->ptr_Gpt_ChannelConfig[i].Gpt_MicroTimer;
                    
                    /* Precalculated PIT microtimer (8-bit time base divider) Configured to update the values in 
                    microseconds */
                    
                    if(ConfigPtr->ptr_Gpt_ChannelConfig[i].Gpt_MicroTimer == GPT_MICROTIMER0){
                        PITMTLD0               = PIT_MICROTIMER_DIV;
                    }else{  
                        PITMTLD1               = PIT_MICROTIMER_DIV;
                    }
                                          
                    break;        
                case CHANNEL_1:

                    /* 16-bit timer 0 counts with micro time base selected (time base 0 or time base 1) */
                    PITMUX_PMUX1           = ConfigPtr->ptr_Gpt_ChannelConfig[i].Gpt_MicroTimer;
                    
                    /* Precalculated PIT microtimer (8-bit time base divider) Configured to update the values in 
                    microseconds */
                    
                    if(ConfigPtr->ptr_Gpt_ChannelConfig[i].Gpt_MicroTimer == GPT_MICROTIMER0){
                        PITMTLD0               = PIT_MICROTIMER_DIV;
                    }else{  
                        PITMTLD1               = PIT_MICROTIMER_DIV;
                    }
                                               
                    break;       
                case CHANNEL_2:
                    
                    /* 16-bit timer 0 counts with micro time base selected (time base 0 or time base 1) */
                    PITMUX_PMUX2           = ConfigPtr->ptr_Gpt_ChannelConfig[i].Gpt_MicroTimer;
                    
                    /* Precalculated PIT microtimer (8-bit time base divider) Configured to update the values in 
                    microseconds */
                    
                    if(ConfigPtr->ptr_Gpt_ChannelConfig[i].Gpt_MicroTimer == GPT_MICROTIMER0){
                        PITMTLD0               = PIT_MICROTIMER_DIV;
                    }else{  
                        PITMTLD1               = PIT_MICROTIMER_DIV;
                    }
                                               
                    break;        
                case CHANNEL_3:
                    
                    /* 16-bit timer 0 counts with micro time base selected (time base 0 or time base 1) */
                    PITMUX_PMUX3           = ConfigPtr->ptr_Gpt_ChannelConfig[i].Gpt_MicroTimer;
                             
                    /* Precalculated PIT microtimer (8-bit time base divider) Configured to update the values in 
                    microseconds */
                    
                    if(ConfigPtr->ptr_Gpt_ChannelConfig[i].Gpt_MicroTimer == GPT_MICROTIMER0){
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
* \brief    Service for PWM initialization.
* \author   Alejandro Guerena, Jose Miguel Reyes, Sergio Pineda
* \param    ConfigPtr - Pointer to structure containing the Pwm' initialization data. 
* \return   void
* \details  \b Reentrancy Non Reentrant  
* \details  \b Sync/Async Synchronous     
*/
  
/***************************************************************************************************/
void Gpt_StartTimer(Gpt_ChannelType Channel, Gpt_ValueType Value )   
{ 
    // 16 bits- Resolution 
            switch(Channel) 
            {  
                case CHANNEL_0:                    
                    /* Clear PTI interrupt flag */
                    PITTF_PTF0             = 1u;
                    
                    
                    if(Gpt_ConfigType_initial->ptr_Gpt_ChannelConfig[0].Gpt_MicroTimer == GPT_MICROTIMER0){
                    /* Load 8-bit microtimer load register 0 into the 8-bit micro timer down-counter 0 */
                        PITCFLMT_PFLMT0     = 1u;
                    }else{
                    /* Load 8-bit microtimer load register 1 into the 8-bit micro timer down-counter 1 */  
                        PITCFLMT_PFLMT1     = 1u;
                    }
                    
                    /* TimeOut value in microseconds  */
                    PITLD0                 = Value;
                    
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
                    
                     if(Gpt_ConfigType_initial->ptr_Gpt_ChannelConfig[1].Gpt_MicroTimer == GPT_MICROTIMER0){
                    /* Load 8-bit microtimer load register 0 into the 8-bit micro timer down-counter 0 */
                        PITCFLMT_PFLMT0     = 1u;
                    }else{
                    /* Load 8-bit microtimer load register 1 into the 8-bit micro timer down-counter 1 */  
                        PITCFLMT_PFLMT1     = 1u;
                    }
                    
                    /* TimeOut value in microseconds  */
                    PITLD1                 = Value;

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
  
                    if(Gpt_ConfigType_initial->ptr_Gpt_ChannelConfig[2].Gpt_MicroTimer == GPT_MICROTIMER0){
                    /* Load 8-bit microtimer load register 0 into the 8-bit micro timer down-counter 0 */
                        PITCFLMT_PFLMT0     = 1u;
                    }else{
                    /* Load 8-bit microtimer load register 1 into the 8-bit micro timer down-counter 1 */  
                        PITCFLMT_PFLMT1     = 1u;
                    }
                    
                    /* TimeOut value in microseconds  */
                    PITLD2                 = Value;
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
                       
                    if(Gpt_ConfigType_initial->ptr_Gpt_ChannelConfig[3].Gpt_MicroTimer == GPT_MICROTIMER0){
                    /* Load 8-bit microtimer load register 0 into the 8-bit micro timer down-counter 0 */
                        PITCFLMT_PFLMT0     = 1u;
                    }else{
                    /* Load 8-bit microtimer load register 1 into the 8-bit micro timer down-counter 1 */  
                        PITCFLMT_PFLMT1     = 1u;
                    }  
                    
                    /* TimeOut value in microseconds  */
                    PITLD3                 = Value;
                    
                    /* Enables PIT channel 0 */
                    PITCE_PCE3             = 1u;                        
                    /* Interrupt of PIT channel 0 is enabled */
                    PITINTE_PINTE3         = 1u;
                                               
                    break;
            }        
  
}

void Gpt_StopTimer(Gpt_ChannelType Channel) {
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

void Gpt_EnableNotification( Gpt_ChannelType Channel ) { 
            switch(Channel) 
            {  
                case CHANNEL_0:                    
                    /* Enables PIT interrupt channel 0 */
                    PITINTE_PINTE0         = 1u;                       
                    break;                            
                case CHANNEL_1:
                    
                    /* Enables PIT interrupt channel 1 */
                    PITINTE_PINTE1         = 1u;                                                   
                    break;       
                case CHANNEL_2:
                    
                    /* Enables PIT interrupt channel 2 */
                    PITINTE_PINTE2         = 1u;                        
                    break;        
                case CHANNEL_3:
                
                    /* Enables PIT interrupt channel 3 */
                    PITINTE_PINTE3         = 1u;                                                  
                    break;
            }

}

void Gpt_DisableNotification( Gpt_ChannelType Channel ) { 
            switch(Channel) 
            {  
                case CHANNEL_0:                    
                    /* Enables PIT interrupt channel 0 */
                    PITINTE_PINTE0         = 0u;                       
                    break;                            
                case CHANNEL_1:
                    
                    /* Enables PIT interrupt channel 1 */
                    PITINTE_PINTE1         = 0u;                                                   
                    break;       
                case CHANNEL_2:
                    
                    /* Enables PIT interrupt channel 2 */
                    PITINTE_PINTE2         = 0u;                        
                    break;        
                case CHANNEL_3:
                
                    /* Enables PIT interrupt channel 3 */
                    PITINTE_PINTE3         = 0u;                                                  
                    break;
            }

}

void Gpt_Channel0_callback(void){

 DDRA_DDRA0 = 1;
 PORTA_PA0 = ~PORTA_PA0;

}

void Gpt_Channel1_callback(void){
 DDRA_DDRA1 = 1;
 PORTA_PA1 = ~PORTA_PA1;
}

void Gpt_Channel2_callback(void){
 DDRA_DDRA2 = 1;
 PORTA_PA2 = ~PORTA_PA2;
}

void Gpt_Channel3_callback(void){
 DDRA_DDRA3 = 1;
 PORTA_PA3 = ~PORTA_PA3;
}

/***************************************************************************************************/
/**
* \author   Abraham Tezmol
* \param    void
* \return   void
* \todo
*/
#pragma CODE_SEG __NEAR_SEG NON_BANKED

void interrupt  vfnPIT_Channel0_Isr( void  )
{
    /* Verify that Real Time Interrupt caused the interrupt */
    if( PITTF_PTF0 == 1u )
    {
        /*call callback function, if initialized*/
        if( Gpt_ConfigType_initial->ptr_Gpt_ChannelConfig[0].Gpt_Channel_Callback != NULL )
        {
            Gpt_Channel0_callback();
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
        if(Gpt_ConfigType_initial->ptr_Gpt_ChannelConfig[1].Gpt_Channel_Callback != NULL )
        {
            Gpt_Channel1_callback();
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
        if( Gpt_ConfigType_initial->ptr_Gpt_ChannelConfig[2].Gpt_Channel_Callback != NULL )
        {
            Gpt_Channel2_callback();
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
        if( Gpt_ConfigType_initial->ptr_Gpt_ChannelConfig[3].Gpt_Channel_Callback != NULL )
        {
            Gpt_Channel3_callback();
        }
    }
    /* Clear the real time interrupt flag */
    PITTF_PTF3 = 1u;
}
#pragma CODE_SEG DEFAULT
/*******************************************************************************/
