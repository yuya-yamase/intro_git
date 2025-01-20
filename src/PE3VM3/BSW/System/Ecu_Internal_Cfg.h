/*****************************************************************************
 *	Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		Ecu_Internal_Cfg.h
 * [Module]			Configuration
 * [Function]		Configuration of Ecu Sample internal
 * [Revision]		1.00
 * [Notes]			Customize file
 ****************************************************************************/

#ifndef ECU_INTERNAL_CFG_H
#define ECU_INTERNAL_CFG_H

#include <SS_Internal_Cfg.h>

/*----------------------------------------------------------------------------
 *		Symbols
 *--------------------------------------------------------------------------*/
/* ターゲットデバイス情報 */
#define ECU_U2A16        (0U)
#define ECU_U2A8         (1U)
#define ECU_U2A6         (2U)
#define ECU_RCARS4       (3U)
#define ECU_TARGETDEVICE (ECU_U2A16)

#define ECU_USE               (1U)
#define ECU_NOT_USE           (0U)
#define ECU_USE_RAMECCDESTROY (ECU_USE)

/* ベクタアドレス Ecu_Int_Vector_asm.850で使用 */

/*  ECU_VMはコマンドラインオプションで、VM毎に与える */
#if defined(ECU_VM0)
#define ECU_INT_u4VECTOR_ADDRESS_0 (0x00060000UL)

#elif defined(ECU_VM1)
#define ECU_INT_u4VECTOR_ADDRESS_0 (0x00200000UL)

#elif defined(ECU_VM2)
#define ECU_INT_u4VECTOR_ADDRESS_0 (0x00400000UL)

#elif defined(ECU_VM3)
#define ECU_INT_u4VECTOR_ADDRESS_0 (0x00600000UL)

#else
#define ECU_INT_u4VECTOR_ADDRESS_0 (0x00020000UL)

#if (SS_USE_CORE_COUNT >= 2u)
#define ECU_INT_u4VECTOR_ADDRESS_1 (0x00000000UL)

#endif
#if (SS_USE_CORE_COUNT >= 3u)
#define ECU_INT_u4VECTOR_ADDRESS_2 (0x00800000UL)

#endif
#if (SS_USE_CORE_COUNT >= 4u)
#define ECU_INT_u4VECTOR_ADDRESS_3 (0x00C00000UL)

#endif
#endif



#endif /* ECU_INTERNAL_CFG_H */
