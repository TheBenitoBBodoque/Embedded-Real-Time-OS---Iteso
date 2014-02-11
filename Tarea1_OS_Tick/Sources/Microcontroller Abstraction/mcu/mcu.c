/******************************************************************************
*   Filename:   mcu.c 
*
*   Description: S12XE/S12XS CPU and PLL initialization
*
*
*   Revision History: This driver was developed by TEAM 4, some code from 
*                     Abraham Tezmol was used. 
*                             
*   Date          #Change       Author
*   MM-DD-YY      Number:       Initials   Description of change
*   -----------   -----------   --------   ------------------------------------
*   02-10-14       00            JMR         Initial release
******************************************************************************/


/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Own headers */
/** PLL prototypes and definitions */
#include "mcu.h"

/** Used modules */

/* -- Variables --------------------------------------------------------*/

/* Global variable that holds status of Clock */
u16 mcal_mcu_gu16ClockGlobalStatus;

/* Loss of Lock counter */
u16 mcal_mcu_u16PLL_Loss_of_Lock_Counter;

/* Actual Bus frequency value */
u32 mcal_mcu_gu32BusFrequency;

/****************************************************************************************************/
/**
* \brief    Initialized the clock source, it depends of the configuration defined by the user.
*           CNF_BUSCLK_SOURCE or CNF_XTAL_SOURCE in the mcu_cfg.h file. 
* \author   Jose Miguel Reyes, Sergio Pineda, Esteban Bernardo
* \param    None. 
* \return   void
* \details  \b Reentrancy Non Reentrant  
* \details  \b Sync/Async Synchronous     
*/
/***************************************************************************************************/
void Mcu_Init(void)
{                 
    #ifdef CNF_XTAL_SOURCE
        Mcu_InitClock();   
    #endif
    
    #ifdef CNF_BUSCLK_SOURCE
        Mcu_DistributePllClock();   
    #endif
}

/****************************************************************************************************/
/**
* \brief    Selects XTAL as clock source.
* \author   Jose Miguel Reyes, Sergio Pineda, Esteban Bernardo
* \param    None. 
* \return   void
* \details  \b Reentrancy Non Reentrant  
* \details  \b Sync/Async Synchronous     
*/
/***************************************************************************************************/
void Mcu_InitClock(void)
{
    /* Select XTAL as clock source */
    CLKSEL_PLLSEL = 0u;
    /* update global status variable */                                   
    mcal_mcu_gu16ClockGlobalStatus = CLOCK_STATUS_XTAL_SELECTED;
    /* update bus frequency variable with XTAL frequency value */

    mcal_mcu_gu32BusFrequency = ((u32)CNF_XTAL_FREQ_KHZ*500u);    

  
}

/****************************************************************************************************/
/**
* \brief    Initialize and distribute the PLL as clock source.
* \author   Jose Miguel Reyes, Sergio Pineda, Esteban Bernardo
* \param    None. 
* \return   void
* \details  \b Reentrancy Non Reentrant  
* \details  \b Sync/Async Synchronous     
*/
/***************************************************************************************************/
void Mcu_DistributePllClock(void){

    /* Disable the PLL */
    PLLCTL_PLLON = 0u;
    /* update global status variable */                                   
    mcal_mcu_gu16ClockGlobalStatus = CLOCK_STATUS_PLL_OFF;
    
    /* Set PLL synthesizer register */
    SYNR_SYNDIV = CNF_SYNR_VALUE;         
    /* Set PLL divider register */  
    REFDV_REFDIV = CNF_REFDV_VALUE;         
    /* Configure PLL filter for optimal stability and lock time */
    REFDV_REFFRQ = CNF_REFFRQ_VALUE;        
    /* Set Postdiv value,  */
    POSTDIV_POSTDIV = CNF_POSTDIV_VALUE;                
    /* Configure VCO gain for optimal stability and lock time */
    SYNR_VCOFRQ = CNF_VCOFRQ_VALUE;         
    /* Clock Monitor Enable. This is required to enter Self Clock Mode */
    PLLCTL_CME = 1u;                     
    /* Self Clock Mode Enable, If CME & SCME are both asserted and the Clock Monitor
    in the oscillator block detects a loss of clock, Self Clock Mode will be entred */
    PLLCTL_SCME = 1u;                    
    /* Clear Self Clock Mode Interrupt Flag */                                                                          
    CRGFLG_SCMIF = 1u;                   
    /* Interrupt will be requested whenever SCMIF(Self Clock Mode Interrupt Flag) is set */ 
    CRGINT_SCMIE = 1u; 
    
    /* PLL enabled */
    PLLCTL_PLLON = 1u;                   
    
    /* Initialize PLL Loss-of-clock event counter */    
    mcal_mcu_u16PLL_Loss_of_Lock_Counter = 0u;            
    /* Wait until the PLL is within the desired frequency */
    while(!CRGFLG_LOCK)
    {}
    /* Initialize Global status variable to default value */                                   
    mcal_mcu_gu16ClockGlobalStatus = CLOCK_STATUS_PLL_OK;        
    /* Clear IPLL Lock Interrupt Flag */
    CRGFLG_LOCKIF = 1u;                  
    /* Interrupt will be requested whenever LOCKIF(IPLL Lock Interrupt Flag)is set */        
    CRGINT_LOCKIE = 1u;

    /* Select PLL as clock source */
    CLKSEL_PLLSEL = 1u;
    
    /* update global status variable */                                   
    mcal_mcu_gu16ClockGlobalStatus = CLOCK_STATUS_PLL_SELECTED;
    
    /* update bus frequency variable with PLL frequency value */
    mcal_mcu_gu32BusFrequency = ACTUAL_BUS_FREQ;

}

/*******************************************************************************/
/**
* \brief    Clock monitor Interrup Service routine.
* \author   Abraham Tezmol
* \param    void
* \return   void
* \todo
*
*           COMPLIES REQUIREMENT 0.2,0.4,0.5,0.6,0.7
*/
#pragma CODE_SEG __NEAR_SEG NON_BANKED
void interrupt vfnPll_Clock_Monitor_Isr(void)
{     
        /* Verify that IPLL Lock Interrupt Flag caused the interrupt */
        if (CRGFLG_LOCKIF == 1u)
        {
            /* Clear IPLL Lock Interrupt Flag */  
            CRGFLG_LOCKIF = 1u;
            /* Update Loss-of-Lock event counter */
            mcal_mcu_u16PLL_Loss_of_Lock_Counter++;
            if (mcal_mcu_u16PLL_Loss_of_Lock_Counter >= 5u)
            {
                /* Set mcal_mcu_gu16ClockGlobalStatus to its appropriate status */
                mcal_mcu_gu16ClockGlobalStatus = CLOCK_STATUS_PLL_LOCK_ERROR;
                /* Configure all I/O to their default values */
                
                /* If we reach Loss-of-Lock 5 consecutive times, get into an infinite loop */
                for (;;){}
            }
        }
        else
        {        
            /* Verify that Self Clock Mode Interrupt flag caused the interrupt */
            if (CRGFLG_SCMIF == 1u)
            {
                /* Clear Self Clock Mode Interrupt Flag */
                CRGFLG_SCMIF = 1u;
                /* Set mcal_mcu_gu16ClockGlobalStatus to its appropriate status */ 
                mcal_mcu_gu16ClockGlobalStatus = CLOCK_STATUS_SCM_ERROR;        
                /* If we reach SCM condition, get into an infinite loop */
                for (;;){}                
            }
        } 
}
#pragma CODE_SEG DEFAULT    
/*******************************************************************************/