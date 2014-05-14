/******************************************************************************
*   Filename:   SchM.c 
*
*   Description:
*
*
*   Revision History:
*
*   Date          #Change       Author     
*   MM-DD-YY      Number:       Initials   Description of change
*   -----------   -----------   --------   ------------------------------------
*   03-01-14       02            SPA        OS Task Initial Release
*   03-29-14       11            JMR        Fix Issues found in OS Dispatcher and OSEK functions
******************************************************************************/

/******************************************************************************
*   Include Files
******************************************************************************/
#include <hidef.h> 
#include <mc9s12xep100.h>
#include "SchM.h"
#include "gpt.h"
#include "mem.h"
#include "int_vectors.h"

/******************************************************************************
*   Local Macro Definitions
******************************************************************************/ 

/******************************************************************************
*   Local Type Definitions
******************************************************************************/

/******************************************************************************
*   Local Function Declarations
******************************************************************************/ 

/******************************************************************************
*   Global Variable Definitions
******************************************************************************/
 u16     CCR_ContextRestore_u16;
 u16       D_ContextRestore_u16;
 u16      IX_ContextRestore_u16;
 u16      IY_ContextRestore_u16;
 u16      PC_ContextRestore_u16;
 u8     PPAGE_ContextRestore_u8;
 u16      SP_ContextRestore_u16;
 u8 gInterrupt_PIT_flag;
/******************************************************************************
*   Static Variable Definitions
******************************************************************************/
 static u8 SchM_OSTickEnabled;
 static u16 SchM_OSTickCounter;
 static u8 SchM_SchedulerEnabled;

/******************************************************************************
*   Global and Static Function Definitions
******************************************************************************/ 

/*****************************************************************************************************                                                                        
*   Function: SchM_Init(SchM_TaskConfigType *SchM_Config)
*
*   Description: Scheduler Initialization
*
*   Caveats:
*****************************************************************************************************/
void SchM_Init(const TaskConfigType *SchM_Config)
{	

	/*Initialize timer configuration for the OS tick*/
	Gpt_Init(&Gpt_ConfigType_initial[0]);
	
	/*Initialize memory driver for TCB allocation*/
	Mem_Init();
	
  /* Initialize Ostick and Scheduler flags */
	SchM_OSTickEnabled = SCHM_OSTICK_DISABLED;
	SchM_SchedulerEnabled =  SCHEDULER_ENABLED;
	SchM_OSTickCounter = 0;	 
}


/*****************************************************************************************************                                                                        
*   Function: SchM_Init
*
*   Description: Scheduler De-initialization
*
*   Caveats:
*****************************************************************************************************/
void SchM_DeInit(void)
{
	/* Disable the Scheduler flag */
  SchM_SchedulerEnabled =  SCHEDULER_DISABLED;	
}


/*****************************************************************************************************                                                                        
*   Function: SchM_Start
*
*   Description: Starts the scheduler
*
*   Caveats:
*****************************************************************************************************/
void SchM_Start(void)
{
    u16 index_a; 
    u16 index_b;
    u16 index_ControlBlock;
    /*Start the timer for the OS tick*/
    Gpt_StartTimer(CHANNEL_0, 500u);
    Gpt_StartTimer(CHANNEL_1, 20000u);
    Gpt_StartTimer(CHANNEL_2, 40000u);
    /*Enable notification*/
    Gpt_EnableNotification(CHANNEL_0);
    Gpt_EnableNotification(CHANNEL_1);
    Gpt_EnableNotification(CHANNEL_2);
    
    /* Initialize Dispacher Array Vector */
    for(index_a=0U;index_a < MAX_PRIORITY;index_a++)
    {
      for(index_b=0U;index_b < CNF_MAXTASKQUEUE;index_b++)
      {
         DispacherArray[index_a][index_b] = 0xFFFF;            
      }
    }
    
    BackgroundControlBlock.BackgroundContextSave.CCR_TaskContext_u16   = 0U;
    BackgroundControlBlock.BackgroundContextSave.D_TaskContext_u16     = 0U;
    BackgroundControlBlock.BackgroundContextSave.X_TaskContext_u16     = 0U;
    BackgroundControlBlock.BackgroundContextSave.Y_TaskContext_u16     = 0U;
    BackgroundControlBlock.BackgroundContextSave.PC_TaskContext_u16    = 0U;
    BackgroundControlBlock.BackgroundContextSave.PPAGE_TaskContext_u16 = 0U;
    BackgroundControlBlock.BackgroundContextSave.SP_TaskContext_u16    = 0U;
    BackgroundControlBlock.BackgroundInterrupted                       = TASK_NOPREEMPTED;

    TaskControlBlock = ((Task_Control_Block *__far)Mem_Alloc((MAX_NUM_TASK*sizeof(Task_Control_Block))));
    for(index_ControlBlock=0U;index_ControlBlock < MAX_NUM_TASK;index_ControlBlock++)
    {
      TaskControlBlock[index_ControlBlock].Task_ID                                  = TaskConfigInitial->ptr_Task[index_ControlBlock].Task_ID;
      TaskControlBlock[index_ControlBlock].Task_Priority                            = TaskConfigInitial->ptr_Task[index_ControlBlock].Task_Priority;
      TaskControlBlock[index_ControlBlock].Task_State                               = SUSPENDED;
      TaskControlBlock[index_ControlBlock].Stack_Information.StartAddress           = 0U;
      TaskControlBlock[index_ControlBlock].Stack_Information.EndAddress             = 0U;
      TaskControlBlock[index_ControlBlock].Task_Deadline.Relative                   = 0U;
      TaskControlBlock[index_ControlBlock].Task_Deadline.Absolute                   = 0U;
      TaskControlBlock[index_ControlBlock].Task_ContextSave.CCR_TaskContext_u16     = 0U;
      TaskControlBlock[index_ControlBlock].Task_ContextSave.D_TaskContext_u16       = 0U;
      TaskControlBlock[index_ControlBlock].Task_ContextSave.X_TaskContext_u16       = 0U;
      TaskControlBlock[index_ControlBlock].Task_ContextSave.Y_TaskContext_u16       = 0U;
      TaskControlBlock[index_ControlBlock].Task_ContextSave.PC_TaskContext_u16      = 0U;
      TaskControlBlock[index_ControlBlock].Task_ContextSave.PPAGE_TaskContext_u16   = 0U;
      TaskControlBlock[index_ControlBlock].Task_ContextSave.SP_TaskContext_u16      = 0U;
      TaskControlBlock[index_ControlBlock].Task_Interrupted                         = TASK_NOPREEMPTED;
      TaskControlBlock[index_ControlBlock].Task_Mode                                = PERIODIC;
    }
    
    while(1)
    {
      SchM_Background();
      _FEED_COP();
    }

}

/*****************************************************************************************************                                                                        
*   Function: SchM_OsTick
*
*   Description: Callback handled once an interrupt is generated by Channel 0.
*
*   Caveats: Non Reentrant
*****************************************************************************************************/
void SchM_OsTick(void)
{
  u8 Task_Index = 0;
  Status_Type StatusErrorResult = E_OK;

 if(!SchM_OSTickEnabled)
  {
    SchM_OSTickEnabled = SCHM_OSTICK_ENABLED;
    for(Task_Index=0;Task_Index < TaskConfigInitial[0U].TaskNumberConfig;Task_Index++)
    {
       if((SchM_OSTickCounter & TaskConfigInitial->ptr_Task[Task_Index].Mask) == 
           TaskConfigInitial->ptr_Task[Task_Index].Offset)
       {
         StatusErrorResult = ActivateTask(((TaskType)TaskConfigInitial->ptr_Task[Task_Index].Task_ID));
       }
    }
  }
  else
  {
     /*ERROR: Ostick flag was not disabled*/   
  }
   
  SchM_OSTickCounter ++;
  PORTB_PB2= ~PORTB_PB2;
  

}

/*****************************************************************************************************                                                                        
*   Function: SchM_Background
*
*   Description: BackGround Task
*
*   Caveats: Non Reentrant
*****************************************************************************************************/
void SchM_Background(void)
{
   
  /* if(gInterrupt_PIT_flag & 0x01){
     gInterrupt_PIT_flag &=0xFE;
     Gpt_ConfigType_initial->ptr_Pit_ChannelConfig[0].Pit_Channel_Callback();
   }
   if(gInterrupt_PIT_flag & 0x02){
     gInterrupt_PIT_flag &=0xFD;
     Gpt_ConfigType_initial->ptr_Pit_ChannelConfig[1].Pit_Channel_Callback();
   }
   if(gInterrupt_PIT_flag & 0x04){
     gInterrupt_PIT_flag &=0xFB;
     Gpt_ConfigType_initial->ptr_Pit_ChannelConfig[2].Pit_Channel_Callback();
   }
   if(gInterrupt_PIT_flag & 0x08){
     gInterrupt_PIT_flag &=0xF7;
     Gpt_ConfigType_initial->ptr_Pit_ChannelConfig[3].Pit_Channel_Callback();
   }*/
   
   switch(gRotaBit_counter){
      
        case 1:
          PORTA_PA0 = 1;
          PORTA_PA1 = 0;
          PORTA_PA2 = 0;
          PORTA_PA3 = 0;
        break;
        case 2:
          PORTA_PA0 = 0;
          PORTA_PA1 = 1;
          PORTA_PA2 = 0;
          PORTA_PA3 = 0;
        break;
        case 3:
          PORTA_PA0 = 0;
          PORTA_PA1 = 0;
          PORTA_PA2 = 1;
          PORTA_PA3 = 0;
        break;
        case 4:
          PORTA_PA0 = 0;
          PORTA_PA1 = 0;
          PORTA_PA2 = 0;
          PORTA_PA3 = 1;
        break;
        default:
          PORTA_PA0 = 0;
          PORTA_PA1 = 0;
          PORTA_PA2 = 0;
          PORTA_PA3 = 0;
        break;   
   }
   if(SchM_SchedulerEnabled)
   {
     if(SchM_OSTickEnabled)
     {
      /*Wait for the next OS Tick to enable it*/
      SchM_OSTickEnabled = SCHM_OSTICK_DISABLED;
      //PORTB_PB3= 0;
     }
     else
     {
        /*For future purposes*/
     }
   } 
   else
   {
     /*Scheduler is not enabled*/
   }
   _FEED_COP();
}

/*****************************************************************************************************                                                                        
*   Function: Dispatcher
*
*   Description: Only run on Background task
*
*   Caveats: Non Reentrant
*****************************************************************************************************/
void Dispatcher(void)
{
    u16 IndexPriority = MAX_PRIORITY;
    u16 NoTaskExecuted = TRUE;
    u16 DispatcherDone = FALSE;

    while(!DispatcherDone)
    {
        do
        {
            IndexPriority--;
            if(DispacherArray[IndexPriority][0U] != 0xFFFF)
            {
                TaskExecuted_ID = DispacherArray[IndexPriority][0U];
                if(TaskControlBlock[TaskExecuted_ID].Task_Interrupted == TASK_PREEMPTED)
                {
                    DisableAllInterrupts();
                    /* Return Context to the Interrupted Task */
                    TaskControlBlock[TaskExecuted_ID].Task_Interrupted = TASK_NOPREEMPTED;
                    PPAGE_ContextRestore_u8  =  TaskControlBlock[TaskExecuted_ID].Task_ContextSave.PPAGE_TaskContext_u16;
                    PC_ContextRestore_u16    =  TaskControlBlock[TaskExecuted_ID].Task_ContextSave.PC_TaskContext_u16;
                    IY_ContextRestore_u16    =  TaskControlBlock[TaskExecuted_ID].Task_ContextSave.X_TaskContext_u16;
                    IX_ContextRestore_u16    =  TaskControlBlock[TaskExecuted_ID].Task_ContextSave.Y_TaskContext_u16;
                    D_ContextRestore_u16     =  TaskControlBlock[TaskExecuted_ID].Task_ContextSave.D_TaskContext_u16;
                    CCR_ContextRestore_u16   =  TaskControlBlock[TaskExecuted_ID].Task_ContextSave.CCR_TaskContext_u16;
                    SP_ContextRestore_u16    =  TaskControlBlock[TaskExecuted_ID].Task_ContextSave.SP_TaskContext_u16;
                    __asm
                    {
                        LDS    SP_ContextRestore_u16             ; (SP) Load from fixed memory location to SP
                        LDAA   PPAGE_ContextRestore_u8           ; (P_PAGE) Load from a fixed memory location to Register A
                        PSHA                                    ; Push the CPU Register A value into the Stack
                        LDD    PC_ContextRestore_u16             ; (PC) Load from a fixed memory location to Register D
                        PSHD                                    ; Push the CPU Register D value into the Stack
                        LDD    IX_ContextRestore_u16             ; (IY) Load from a fixed memory location to Register D
                        PSHD                                    ; Push the CPU Register D value into the Stack
                        LDD    IY_ContextRestore_u16             ; (IX) Load from a fixed memory location to Register D
                        PSHD                                    ; Push the CPU Register D value into the Stack
                        LDD    D_ContextRestore_u16              ; (D || BA) Load from a fixed memory location to Register D
                        PSHD                                    ; Push the CPU Register D value into the Stack
                        LDD    CCR_ContextRestore_u16            ; (CCR) Load from a fixed memory location to Register D
                        PSHD                                    ; Push the CPU Register D value into the Stack
                    }
                    EnableAllInterrupts();
                    asm(RTI);
                }
                else
                {
                    TaskControlBlock[TaskExecuted_ID].Task_State = RUNNING;
                    TaskConfigInitial->ptr_Task[TaskExecuted_ID].TaskCallback();
                    NoTaskExecuted = FALSE;
                }
            }
        }
        while((IndexPriority != 0U)&&(NoTaskExecuted));
        if((IndexPriority == 0U) && (NoTaskExecuted))
        {
            DispatcherDone = TRUE;
        }
        else
        {
            IndexPriority = MAX_PRIORITY;
            NoTaskExecuted = TRUE;
        }
    }
    if(BackgroundControlBlock.BackgroundInterrupted == TASK_PREEMPTED)
    {
        DisableAllInterrupts();
        BackgroundControlBlock.BackgroundInterrupted = TASK_NOPREEMPTED;
        PPAGE_ContextRestore_u8  =  BackgroundControlBlock.BackgroundContextSave.PPAGE_TaskContext_u16;
        PC_ContextRestore_u16    =  BackgroundControlBlock.BackgroundContextSave.PC_TaskContext_u16;
        IY_ContextRestore_u16    =  BackgroundControlBlock.BackgroundContextSave.X_TaskContext_u16;
        IX_ContextRestore_u16    =  BackgroundControlBlock.BackgroundContextSave.Y_TaskContext_u16;
        D_ContextRestore_u16     =  BackgroundControlBlock.BackgroundContextSave.D_TaskContext_u16;
        CCR_ContextRestore_u16   =  BackgroundControlBlock.BackgroundContextSave.CCR_TaskContext_u16;
        SP_ContextRestore_u16   =   BackgroundControlBlock.BackgroundContextSave.SP_TaskContext_u16;
        __asm
        {
            LDS    SP_ContextRestore_u16             ; (SP) Load from fixed memory location to SP
            LDAA   PPAGE_ContextRestore_u8           ; (P_PAGE) Load from a fixed memory location to Register A
            PSHA                                    ; Push the CPU Register A value into the Stack
            LDD    PC_ContextRestore_u16             ; (PC) Load from a fixed memory location to Register D
            PSHD                                    ; Push the CPU Register D value into the Stack
            LDD    IY_ContextRestore_u16             ; (IY) Load from a fixed memory location to Register D
            PSHD                                    ; Push the CPU Register D value into the Stack
            LDD    IX_ContextRestore_u16             ; (IX) Load from a fixed memory location to Register D
            PSHD                                    ; Push the CPU Register D value into the Stack
            LDD    D_ContextRestore_u16              ; (D || BA) Load from a fixed memory location to Register D
            PSHD                                    ; Push the CPU Register D value into the Stack
            LDD    CCR_ContextRestore_u16            ; (CCR) Load from a fixed memory location to Register D
            PSHD                                    ; Push the CPU Register D value into the Stack
        }
        EnableAllInterrupts();
        asm(RTI);
    }
    else
    {

    }
}

