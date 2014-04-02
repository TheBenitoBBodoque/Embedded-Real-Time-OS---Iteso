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

/******************************************************************************
*   Static Variable Definitions
******************************************************************************/
 static u8 SchM_OSTickEnabled;
 static u8 SchM_OSTickCounter;
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
    /*Enable notification*/
    Gpt_EnableNotification(CHANNEL_0);
    /* Initialize Dispacher Array Vector */
    for(index_a=0U;index_a < MAX_PRIORITY;index_a++)
    {
      for(index_b=0U;index_b < CNF_MAXTASKQUEUE;index_b++)
      {
         DispacherArray[index_a][index_b] = 0xFFFF;            
      }
    }
    
    TaskControlBlock = ((Task_Control_Block *__far)Mem_Alloc((MAX_NUM_TASK*sizeof(Task_Control_Block))));
    for(index_ControlBlock=0U;index_ControlBlock < MAX_NUM_TASK;index_ControlBlock++)
    {
      TaskControlBlock[index_ControlBlock].Task_ID                        = TaskConfigInitial->ptr_Task[index_ControlBlock].Task_ID;
      TaskControlBlock[index_ControlBlock].Task_Priority                  = TaskConfigInitial->ptr_Task[index_ControlBlock].Task_Priority;
      TaskControlBlock[index_ControlBlock].Task_State                     = SUSPENDED;
      TaskControlBlock[index_ControlBlock].Stack_Information.StartAddress = 0U;
      TaskControlBlock[index_ControlBlock].Stack_Information.EndAddress   = 0U;
      TaskControlBlock[index_ControlBlock].Task_Deadline.Relative         = 0U;
      TaskControlBlock[index_ControlBlock].Task_Deadline.Absolute         = 0U; 
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
    /* ERROR: Ostick flag was not disabled  */ 
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
   
   if(SchM_SchedulerEnabled)
   {
     if(SchM_OSTickEnabled)
     {
      PORTB_PB3= 1;
           
      Dispatcher();  
      /*Wait for the next OS Tick to enable it*/
      SchM_OSTickEnabled = SCHM_OSTICK_DISABLED;
      PORTB_PB3= 0;
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
           TaskControlBlock[TaskExecuted_ID].Task_State = RUNNING;
            
           TaskConfigInitial->ptr_Task[TaskExecuted_ID].TaskCallback();
           NoTaskExecuted = FALSE;
       }
    }
    while((IndexPriority != 0U)&&(NoTaskExecuted));
    if((IndexPriority == 0U) && (!NoTaskExecuted))
    {
       DispatcherDone = TRUE;
    }
    else
    {
       IndexPriority = MAX_PRIORITY;
    }
  }
}

