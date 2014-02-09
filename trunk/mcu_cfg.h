/****************************************************************************************************/
/**

\file       mcu_cfg.h
\brief      S12XE/S12XS CPU and PLL initialization prototypes and definitions
\author     TEAM
\version    1.0
\date       8/2/2014
*/
/****************************************************************************************************/

/****************************************************************************************************/

#ifndef __MCU_CFG_H
#define __MCU_CFG_H

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Variable types and common definitions */
  #include "typedefs.h"   


/*****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs
*****************************************************************************************************/

/** Select XTAL and BUS Clock frequency in KHz */

/** BUS clock frequency */
	#define CNF_BUS_FREQ_KHZ        48000u       
/** Xtal frequency */ 
	#define CNF_XTAL_FREQ_KHZ       4000u
		/* Other options: */
	/* #define  CNF_XTAL_FREQ_KHZ  16000u   */ 

/*By default, PLL clock is selected as a source clock, if the user
want to use XTAL as a source clock, this define need to be removed*/
#define CNF_BUSCLK_SOURCE

/*If CNF_BUSCLK_SOURCE is not defined, XTAL will be selected
  as a clock source*/
#ifndef CNF_BUSCLK_SOURCE 
  #define CNF_XTAL_SOURCE
#endif

#endif /* __MCU_CFG_H */

/*******************************************************************************/