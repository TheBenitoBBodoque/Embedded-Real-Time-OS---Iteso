/******************************************************************************
*   Filename:   mem.h 
*
*   Description: S12XE/S12XS CPU and PLL initialization
*
*
*   Revision History: This driver was developed by TEAM 4
*                             
*   Date          #Change       Author
*   MM-DD-YY      Number:       Initials   Description of change
*   -----------   -----------   --------   ------------------------------------
*   03-29-14       11            JMR        Fix Issues found in OS Dispatcher and OSEK functions
******************************************************************************/

#ifndef __MEM_H
#define __MEM_H

/*****************************************************************************************************
* Include files
*****************************************************************************************************/  

/** Core modules */
/** MCU derivative information */
#include "derivative.h"      /* derivative-specific definitions */
/** Variable types and common definitions */
#include "typedefs.h"

/** Used modules */

/*****************************************************************************************************
* Declaration of module wide TYPEs 
*****************************************************************************************************/

typedef	void  *__far	Mem_ReturnType;
typedef	u8    *__far	Mem_Uint8PtrType;
typedef	u16   *__far	Mem_Uint16PtrType;
typedef	u32   *__far	Mem_Uint32PtrType;
typedef	u16           Mem_SizeType;


/**
\struct     MemHandlerType
\brief      MemHandlerType Struct for RAM Memory Dynamic Allocation Area (Heap)
            - memStart -> Heap start address.
            - memEnd   -> Heap final address.
            - currAddr -> Heap current address.
            - memFull  -> Memory full indicator.
*/ 
typedef struct {
	  Mem_Uint8PtrType	memStart;
    Mem_Uint8PtrType	memEnd;
    Mem_Uint8PtrType	currAddr;
    u8              	memFull;

} MemHandlerType;	



/*****************************************************************************************************
* Definition of module wide VARIABLES
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs 
*****************************************************************************************************/

/* Banks/Pages reserved for RAM Dynamic Memory Allocation */
#define CNF_NO_OF_RAM_PAGES 4
/* RAM's pages size (4k bytes) */
#define CNF_PAGE_SIZE       0x1000

/*****************************************************************************************************
* Declaration of module wide FUNCTIONS
*****************************************************************************************************/

/* RAM Memory Initialization */
extern void Mem_Init(void);
/* RAM Dynamic Memory Allocation routine */
extern Mem_ReturnType Mem_Alloc(Mem_SizeType memSize);
/* Test fucntion for Dynamic Memory Allocation */
extern void Test_Memory(void); 

/**************************************************************************************************/

#endif /* __MEM_H */

/**
@} 
*/