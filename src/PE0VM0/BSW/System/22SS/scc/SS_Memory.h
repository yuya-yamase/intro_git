/*****************************************************************************
 *  Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_Memory.h
 * [Module]			Memory
 * [Function]		Memory
 * [Notes]			None
 ****************************************************************************/

#ifndef SS_MEMORY_H
#define SS_MEMORY_H

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <SS_Internal.h>

/*----------------------------------------------------------------------------
 *		Symbols
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *		Externs
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *		Prototypes
 *--------------------------------------------------------------------------*/
uint32 *SS_Memory_copy(uint32 *ptDestAddr, uint32 *ptSrcAddr, uint32 u4Size);
uint32 *SS_Memory_set(uint32 *ptAddr, uint32 u4Data, uint32 u4Size);

void SS_Memory_scan(volatile uint32 *ptStartAddr, uint32 u4Size);
void SS_Memory_writeScan(volatile uint32 *ptStartAddr, uint32 u4Size);

#if (SS_USE_PRISTACKCHECK == STD_ON)
void SS_Memory_checkPriStack(void);
#endif /* (SS_USE_PRISTACKCHECK == STD_ON) */

#endif /* SS_MEMORY_H */
/**** End of File ***********************************************************/
