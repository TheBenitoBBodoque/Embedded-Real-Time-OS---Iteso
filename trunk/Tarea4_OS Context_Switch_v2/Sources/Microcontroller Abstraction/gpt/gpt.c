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


/******************************************************************************
*   Include Files
******************************************************************************/

/** Own headers */
/* Periodic Interrupt Timer routines prototypes */
#include <hidef.h> 
#include    "gpt.h"
#include    "int_vectors.h"
/******************************************************************************
*   Local Macro Definitions
******************************************************************************/

/******************************************************************************
*   Local Type Definitions
******************************************************************************/

/******************************************************************************
*   Local Function Declarations
******************************************************************************/
void Pit_Channel0_callback(void);
void Pit_Channel1_callback(void);
void Pit_Channel2_callback(void);
void Pit_Channel3_callback(void);

/******************************************************************************
*   Global Variable Definitions
******************************************************************************/
u8 gInterruptFlag;

extern UINT16     CCR_ContextSaving_u16;
extern UINT16       D_ContextSaving_u16;
extern UINT16      IX_ContextSaving_u16;
extern UINT16      IY_ContextSaving_u16;
extern UINT16      PC_ContextSaving_u16;
extern UINT8     PPAGE_ContextSaving_u8;
extern UINT16      SP_ContextSaving_u16;

/******************************************************************************
*   Static Variable Definitions
******************************************************************************/

/******************************************************************************
*   Global and Static Function Definitions
******************************************************************************/

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
                        PITMTLD1               = 0xFF;
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
                        PITMTLD1               = 0xFF;
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
                        PITMTLD1               = 0xFF;
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
                        PITMTLD1               = 0xFF;
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
* \author   Anonymous
* \param    void
* \return   void
* \todo
*/
/***************************************************************************************************/
#pragma CODE_SEG __NEAR_SEG NON_BANKED

void interrupt  vfnPIT_Channel0_Isr( void  )
{
   //DisableAllInterrupts(); 
    __asm
    {
          SEI
          PULD                            ; (CCR) Pull stack into the CPU Register D
          STD     CCR_ContextSaving_u16   ; Store the CPU Register D value in fixed memory
          PULD                            ; (D || BA) Pull the stack into the CPU Register D
          STD     D_ContextSaving_u16     ; Store the CPU Register D value in fixed memory
          PULD                            ; (IX) Pull the stack into the CPU Register D
          STD     IY_ContextSaving_u16    ; Store the CPU Register D value in fixed memory
          PULD                            ; (IY) Pull the stack into the CPU Register D
          STD     IX_ContextSaving_u16    ; Store the CPU Register D value in fixed memory
          PULD                            ; (PC) Pull the stack into the CPU Register D
          STD     PC_ContextSaving_u16    ; Store the CPU Register D value in fixed memory
          PULA                            ; (P_PAGE) Pull the stack into the CPU Register D
          STAA    PPAGE_ContextSaving_u8  ; Store the CPU Register A value in fixed memory

          STS     SP_ContextSaving_u16    ; (SP) Store Stack Pointer in fixed memory
          CLI
    } 
    __asm{
    
    }
    //PORTB_PB0= ~PORTB_PB0;
    gInterruptFlag=1;
    if(TaskExecuted_ID == 0xFFFF)
    {
        BackgroundControlBlock.BackgroundContextSave.CCR_TaskContext_u16 = CCR_ContextSaving_u16;
        BackgroundControlBlock.BackgroundContextSave.D_TaskContext_u16 = D_ContextSaving_u16;
        BackgroundControlBlock.BackgroundContextSave.X_TaskContext_u16 = IX_ContextSaving_u16;
        BackgroundControlBlock.BackgroundContextSave.Y_TaskContext_u16 = IY_ContextSaving_u16;
        BackgroundControlBlock.BackgroundContextSave.PC_TaskContext_u16 = PC_ContextSaving_u16;
        BackgroundControlBlock.BackgroundContextSave.PPAGE_TaskContext_u16 = PPAGE_ContextSaving_u8;
        BackgroundControlBlock.BackgroundContextSave.SP_TaskContext_u16 = SP_ContextSaving_u16;
        BackgroundControlBlock.BackgroundInterrupted = TASK_PREEMPTED;
    }
    else
    {
        TaskControlBlock[TaskExecuted_ID].Task_ContextSave.CCR_TaskContext_u16     = CCR_ContextSaving_u16;
        TaskControlBlock[TaskExecuted_ID].Task_ContextSave.D_TaskContext_u16       = D_ContextSaving_u16;
        TaskControlBlock[TaskExecuted_ID].Task_ContextSave.X_TaskContext_u16       = IX_ContextSaving_u16;
        TaskControlBlock[TaskExecuted_ID].Task_ContextSave.Y_TaskContext_u16       = IY_ContextSaving_u16;
        TaskControlBlock[TaskExecuted_ID].Task_ContextSave.PC_TaskContext_u16      = PC_ContextSaving_u16;
        TaskControlBlock[TaskExecuted_ID].Task_ContextSave.PPAGE_TaskContext_u16   = PPAGE_ContextSaving_u8;
        TaskControlBlock[TaskExecuted_ID].Task_ContextSave.SP_TaskContext_u16      = SP_ContextSaving_u16;
        TaskControlBlock[TaskExecuted_ID].Task_Interrupted                         = TASK_PREEMPTED;
    }
    //EnableAllInterrupts();
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
    gInterruptFlag=0;
    /* Call Dispatcher at the end of the interruption */
     __asm
    {
         MOVW @Dispatcher, 2, -sp;
         RTS
    }
}

void interrupt  vfnPIT_Channel1_Isr( void  )
{  
    //DisableAllInterrupts();
       __asm
    {
          SEI
          PULD                            ; (CCR) Pull stack into the CPU Register D
          STD     CCR_ContextSaving_u16   ; Store the CPU Register D value in fixed memory
          PULD                            ; (D || BA) Pull the stack into the CPU Register D
          STD     D_ContextSaving_u16     ; Store the CPU Register D value in fixed memory
          PULD                            ; (IX) Pull the stack into the CPU Register D
          STD     IY_ContextSaving_u16    ; Store the CPU Register D value in fixed memory
          PULD                            ; (IY) Pull the stack into the CPU Register D
          STD     IX_ContextSaving_u16    ; Store the CPU Register D value in fixed memory
          PULD                            ; (PC) Pull the stack into the CPU Register D
          STD     PC_ContextSaving_u16    ; Store the CPU Register D value in fixed memory
          PULA                            ; (P_PAGE) Pull the stack into the CPU Register D
          STAA    PPAGE_ContextSaving_u8  ; Store the CPU Register A value in fixed memory

          STS     SP_ContextSaving_u16    ; (SP) Store Stack Pointer in fixed memory
          CLI
    }
    //gInterruptFlag=1;

    if(TaskExecuted_ID == 0xFFFF)
    {
        BackgroundControlBlock.BackgroundContextSave.CCR_TaskContext_u16 = CCR_ContextSaving_u16;
        BackgroundControlBlock.BackgroundContextSave.D_TaskContext_u16 = D_ContextSaving_u16;
        BackgroundControlBlock.BackgroundContextSave.X_TaskContext_u16 = IX_ContextSaving_u16;
        BackgroundControlBlock.BackgroundContextSave.Y_TaskContext_u16 = IY_ContextSaving_u16;
        BackgroundControlBlock.BackgroundContextSave.PC_TaskContext_u16 = PC_ContextSaving_u16;
        BackgroundControlBlock.BackgroundContextSave.PPAGE_TaskContext_u16 = PPAGE_ContextSaving_u8;
        BackgroundControlBlock.BackgroundContextSave.SP_TaskContext_u16 = SP_ContextSaving_u16;
        BackgroundControlBlock.BackgroundInterrupted = TASK_PREEMPTED;
    }
    else
    {
        TaskControlBlock[TaskExecuted_ID].Task_ContextSave.CCR_TaskContext_u16     = CCR_ContextSaving_u16;
        TaskControlBlock[TaskExecuted_ID].Task_ContextSave.D_TaskContext_u16       = D_ContextSaving_u16;
        TaskControlBlock[TaskExecuted_ID].Task_ContextSave.X_TaskContext_u16       = IX_ContextSaving_u16;
        TaskControlBlock[TaskExecuted_ID].Task_ContextSave.Y_TaskContext_u16       = IY_ContextSaving_u16;
        TaskControlBlock[TaskExecuted_ID].Task_ContextSave.PC_TaskContext_u16      = PC_ContextSaving_u16;
        TaskControlBlock[TaskExecuted_ID].Task_ContextSave.PPAGE_TaskContext_u16   = PPAGE_ContextSaving_u8;
        TaskControlBlock[TaskExecuted_ID].Task_ContextSave.SP_TaskContext_u16      = SP_ContextSaving_u16;
        TaskControlBlock[TaskExecuted_ID].Task_Interrupted                         = TASK_PREEMPTED;
    }
    //EnableAllInterrupts();
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
              __asm
    {
         MOVW @Dispatcher, 2, -sp;
         RTS
    }
}

void interrupt  vfnPIT_Channel2_Isr( void  )
{
//TaskRefType TaskRunning;
//u16 task;
    //DisableAllInterrupts(); 
    __asm
    {
          SEI
          PULD                            ; (CCR) Pull stack into the CPU Register D
          STD     CCR_ContextSaving_u16   ; Store the CPU Register D value in fixed memory
          PULD                            ; (D || BA) Pull the stack into the CPU Register D
          STD     D_ContextSaving_u16     ; Store the CPU Register D value in fixed memory
          PULD                            ; (IX) Pull the stack into the CPU Register D
          STD     IY_ContextSaving_u16    ; Store the CPU Register D value in fixed memory
          PULD                            ; (IY) Pull the stack into the CPU Register D
          STD     IX_ContextSaving_u16    ; Store the CPU Register D value in fixed memory
          PULD                            ; (PC) Pull the stack into the CPU Register D
          STD     PC_ContextSaving_u16    ; Store the CPU Register D value in fixed memory
          PULA                            ; (P_PAGE) Pull the stack into the CPU Register D
          STAA    PPAGE_ContextSaving_u8  ; Store the CPU Register A value in fixed memory

          STS     SP_ContextSaving_u16    ; (SP) Store Stack Pointer in fixed memory
          CLI
    }
    //gInterruptFlag=1;
    
    if(TaskExecuted_ID == 0xFFFF)
    {
        BackgroundControlBlock.BackgroundContextSave.CCR_TaskContext_u16 = CCR_ContextSaving_u16;
        BackgroundControlBlock.BackgroundContextSave.D_TaskContext_u16 = D_ContextSaving_u16;
        BackgroundControlBlock.BackgroundContextSave.X_TaskContext_u16 = IX_ContextSaving_u16;
        BackgroundControlBlock.BackgroundContextSave.Y_TaskContext_u16 = IY_ContextSaving_u16;
        BackgroundControlBlock.BackgroundContextSave.PC_TaskContext_u16 = PC_ContextSaving_u16;
        BackgroundControlBlock.BackgroundContextSave.PPAGE_TaskContext_u16 = PPAGE_ContextSaving_u8;
        BackgroundControlBlock.BackgroundContextSave.SP_TaskContext_u16 = SP_ContextSaving_u16;
        BackgroundControlBlock.BackgroundInterrupted = TASK_PREEMPTED;
    }
    else
    {
        TaskControlBlock[TaskExecuted_ID].Task_ContextSave.CCR_TaskContext_u16     = CCR_ContextSaving_u16;
        TaskControlBlock[TaskExecuted_ID].Task_ContextSave.D_TaskContext_u16       = D_ContextSaving_u16;
        TaskControlBlock[TaskExecuted_ID].Task_ContextSave.X_TaskContext_u16       = IX_ContextSaving_u16;
        TaskControlBlock[TaskExecuted_ID].Task_ContextSave.Y_TaskContext_u16       = IY_ContextSaving_u16;
        TaskControlBlock[TaskExecuted_ID].Task_ContextSave.PC_TaskContext_u16      = PC_ContextSaving_u16;
        TaskControlBlock[TaskExecuted_ID].Task_ContextSave.PPAGE_TaskContext_u16   = PPAGE_ContextSaving_u8;
        TaskControlBlock[TaskExecuted_ID].Task_ContextSave.SP_TaskContext_u16      = SP_ContextSaving_u16;
        TaskControlBlock[TaskExecuted_ID].Task_Interrupted                         = TASK_PREEMPTED;
    }
    //EnableAllInterrupts();
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
    
    __asm
    {
         MOVW @Dispatcher, 2, -sp;
         RTS
    }
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
