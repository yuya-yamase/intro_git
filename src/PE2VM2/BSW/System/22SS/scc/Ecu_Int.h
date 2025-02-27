/*****************************************************************************
 *  Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		Ecu_Int.h
 * [Module]			Int
 * [Function]		Int
 * [Notes]			None
 ****************************************************************************/

#ifndef ECU_INT_H
#define ECU_INT_H

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <Ecu_Internal.h>

/*----------------------------------------------------------------------------
 *		Types
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *		Symbols
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *		Prototypes
 *--------------------------------------------------------------------------*/
void Ecu_Int_performReset(void);
// void Ecu_Int_destroyRamEcc(void);
// void Ecu_Int_enableEcc(void);
// void Ecu_Int_initPeri(void);

#if 0u
void Ecu_Int_enableCAT1ISR(void);
#endif
void Ecu_Int_initGuard(void);

void Ecu_Int_syncp(void);
/*
    public method, but not decleared, because of just for ASM
    void Ecu_Int_init(void);
*/

#define Ecu_Int_refreshMcu()

#endif /* ECU_INT_H */
