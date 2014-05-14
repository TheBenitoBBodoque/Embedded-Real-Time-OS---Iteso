/******************************************************************************
*   Filename:   mem.c 
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


/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Memory function prototypes definitions */
#include "mem.h"


/*****************************************************************************************************
* Definition of  VARIABLEs - 
*****************************************************************************************************/

/* RAM memory variables for page/bank manipulation*/
#pragma DATA_SEG __RPAGE_SEG HEAP
u8	mcal_mem_InitMem;
#pragma DATA_SEG DEFAULT

MemHandlerType mcal_mem_MemHandler;
Mem_SizeType   mcal_mem_TotalMemSizeBytes;

/*****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs 
*****************************************************************************************************/

/*****************************************************************************************************
* Code of module wide FUNCTIONS
*****************************************************************************************************/

/****************************************************************************************************/
/**
* \brief    RAM Memory for Dynamic Memory Allocation - Initialization
* \author   Alejandro Guerena, Jose Miguel Reyes, Sergio Pineda
* \param    void
* \return   void
* \todo     
*/
void Mem_Init(void)
{
    
    u16 i = 0;
    
    
    
    /* Head initial address pointer */
    mcal_mem_MemHandler.memStart = &mcal_mem_InitMem;
    /* Define Heap Memory Size */
    mcal_mem_TotalMemSizeBytes = (CNF_NO_OF_RAM_PAGES * CNF_PAGE_SIZE) - 1;
    /* Define Heap End Address */
    mcal_mem_MemHandler.memEnd = mcal_mem_TotalMemSizeBytes + mcal_mem_MemHandler.memStart;
    /* Current address points to heap's start address */        
    mcal_mem_MemHandler.currAddr = mcal_mem_MemHandler.memStart;
   

    /* Set initial values of Heap memory */
    for(i=0;i < mcal_mem_TotalMemSizeBytes;i++) 
    {
        *mcal_mem_MemHandler.currAddr = 0x00;
        mcal_mem_MemHandler.currAddr++;
    }
    
    /* Memory is empty */
    mcal_mem_MemHandler.memFull = FALSE; 
    /* Current address points to Heap's start address */
    mcal_mem_MemHandler.currAddr = mcal_mem_MemHandler.memStart;
      
}


/****************************************************************************************************/
/**
* \brief    Dynamic Memory Allocation function.
* \author   Alejandro Guerena, Jose Miguel Reyes, Sergio Pineda
* \param    Mem_SizeType size - Size of memory bytes to allocate. 
* \return   Mem_ReturnType - Returns a pointer to the allocated memory, or NULL if the request fails. 
* \todo     
*/
Mem_ReturnType Mem_Alloc(Mem_SizeType memSize)
{       
 
    
    Mem_ReturnType returnpointer;
    
    /*To perform alignment of 16 bits*/
    if(memSize%2==1){
       memSize+=1;
    }
    
    /* Checks for valid allocationr request. Valid if there is memory space to allocate bytes*/
    if( (mcal_mem_MemHandler.memEnd  - mcal_mem_MemHandler.currAddr+1) < memSize) 
    {      
        returnpointer = NULL;            
    } 
    else 
    {   
        /* Pointer to the initial address for allocated memory */
        returnpointer = mcal_mem_MemHandler.currAddr;
        /* Update currentAddress pointer to the next address avaliable */
        mcal_mem_MemHandler.currAddr = mcal_mem_MemHandler.currAddr + memSize;
    }
    
    /* Determine if memory is full */     
    mcal_mem_MemHandler.memFull = (mcal_mem_MemHandler.memEnd <= mcal_mem_MemHandler.currAddr) ? TRUE : FALSE;
         
    return returnpointer;        

}


/****************************************************************************************************/
/**
* \brief    Test function for Dynamic Memory Allocation. 
* \author   Alejandro Guerena, Jose Miguel Reyes, Sergio Pineda
* \param    void                                            
* \return   void
* \todo     
*/
void Test_Memory(void) 
{
    
    u8 i;
    Mem_Uint8PtrType var8bits,var8bits2,var8bits3,var8bits4;
    //Mem_Uint16PtrType var16bits;
    //Mem_Uint32PtrType var32bits;   

    /* Allocate n bytes */
    var8bits   = (u8 * __far) Mem_Alloc(8192);
    var8bits2  = (u8 * __far) Mem_Alloc(8190);
    var8bits3  = (u8 * __far) Mem_Alloc(2);
    var8bits4  = (u8 * __far) Mem_Alloc(1); 
    
    /* Write information to allocated memory */
    for(i=0;i<8;i++) 
    {
        *var8bits = i;
        var8bits++;
        *var8bits2=i;
        *var8bits3=i;
        *var8bits4=i;     
              
    }
      

}

/***************************************************************************************************/

/**
@} 
*/


  