/*****************************************************************************
 *  Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		Ecu_CtgOs.h
 * [Module]			CtgOs
 * [Function]		Cyclic Trigger for OS
 * [Notes]			None
 ****************************************************************************/

#ifndef ECU_CTGOS_H
#define ECU_CTGOS_H

/*----------------------------------------------------------------------------
 *		Symbols
 *--------------------------------------------------------------------------*/
#define ECU_CTGOS_OSTM0 ((uint8)0U)
#define ECU_CTGOS_OSTM1 ((uint8)1U)
#define ECU_CTGOS_OSTM2 ((uint8)2U)
#define ECU_CTGOS_OSTM3 ((uint8)3U)
#define ECU_CTGOS_OSTM4 ((uint8)4U)
#define ECU_CTGOS_OSTM5 ((uint8)5U)
#define ECU_CTGOS_OSTM6 ((uint8)6U)
#define ECU_CTGOS_OSTM7 ((uint8)7U)
#define ECU_CTGOS_OSTM8 ((uint8)8U)
#define ECU_CTGOS_OSTM9 ((uint8)9U)

/*  ECU_VMはコマンドラインオプションで、VM毎に与える */
/* 自VMで使用するOSTMを選択 */
#if defined(ECU_VM0)
#define ECU_CTGOS_TMRES_OWNVM ECU_CTGOS_OSTM5

#elif defined(ECU_VM1)
#define ECU_CTGOS_TMRES_OWNVM ECU_CTGOS_OSTM6

#elif defined(ECU_VM2)
#define ECU_CTGOS_TMRES_OWNVM ECU_CTGOS_OSTM8

#elif defined(ECU_VM3)
#define ECU_CTGOS_TMRES_OWNVM ECU_CTGOS_OSTM2

#else

#endif

/*----------------------------------------------------------------------------
 *		Prototypes
 *--------------------------------------------------------------------------*/
void Ecu_CtgOs_start(uint8 u1TMResNo);
void Ecu_CtgOs_stop(uint8 u1TMResNo);
void Ecu_CtgOs_syncp(void);

#endif /* ECU_CTGOS_H */
