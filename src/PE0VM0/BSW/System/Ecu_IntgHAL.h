/*****************************************************************************
 *  Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		Ecu_IntgHAL.h
 * [Module]			Int
 * [Function]		Int
 * [Notes]			None
 ****************************************************************************/

#ifndef ECU_INTGHAL_H
#define ECU_INTGHAL_H

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <Ecu_Internal.h>
#include <Ecu_Intg.h>

/*----------------------------------------------------------------------------
 *		Types
 *--------------------------------------------------------------------------*/
typedef struct
{
    uint32 u4WUF0_A0;
    uint32 u4WUF0_A1;
    uint32 u4WUF0_A2;

} Ecu_IntgHAL_WufType;

/*----------------------------------------------------------------------------
 *		Symbols
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *		Prototypes
 *--------------------------------------------------------------------------*/
Ecu_Intg_BootCauseType Ecu_IntgHAL_getBootCause(void);
Std_ReturnType         Ecu_IntgHAL_getWUF(Ecu_IntgHAL_WufType *ptWUF);
void                   Ecu_IntgHAL_enableFpu(void);
boolean                Ecu_IntgHAL_isImmShutdown(void);

void  Ecu_IntgHAL_setIntLevelMask(uint8 u1PriorityLevel);
uint8 Ecu_IntgHAL_getIntLevelMask(void);

void Ecu_IntgHAL_clearRAMV(void);

void Ecu_IntgHAL_performSoftReset(void);
void Ecu_IntgHAL_performHardReset(void);

#endif /* ECU_INTGHAL_H */
