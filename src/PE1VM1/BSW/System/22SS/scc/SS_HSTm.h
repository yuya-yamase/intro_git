/*****************************************************************************
 *	Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_HSTm.h
 * [Module]			HSTm
 * [Function]		Hard Sleep Timer
 * [Notes]			None
 ****************************************************************************/

#ifndef SS_HSTM_H
#define SS_HSTM_H

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <SS_Internal.h>

/*----------------------------------------------------------------------------
 *		Prototypes
 *--------------------------------------------------------------------------*/
#if (SS_USE_SLEEP == STD_ON)
void    SS_HSTm_start(uint32 u4RegTime);
void    SS_HSTm_stop(void);
uint32  SS_HSTm_getTime(uint32 u4AlarmPeriodCnt);
boolean SS_HSTm_isExpired(void);
void    SS_HSTm_reload(uint32 u4AlarmPeriodCnt);
uint32  SS_HSTm_convLsbRealToReg(uint32 u4RealTime);
uint32  SS_HSTm_convLsbRegToReal(uint32 u4RegTime);
#endif /* (SS_USE_SLEEP == STD_ON) */

#endif /* SS_HSTM_H */
