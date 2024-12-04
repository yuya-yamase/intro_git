/*****************************************************************************
 *	Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 *【ファイル名】	Ecu_Arb_Cfg.h
 *【モジュール名】	Arbitration
 *【機能】
 *【備考】
 ****************************************************************************/
#ifndef ECU_ARB_CFG_H
#define ECU_ARB_CFG_H

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <Ecu_Arb.h>

/*----------------------------------------------------------------------------
 *		置換シンボル定義
 *--------------------------------------------------------------------------*/
/*  ECU_VMはコマンドラインオプションで、VM毎に与える */

#define ECU_ARB_SLAVE_VM_NUM       ((ehvm_uint32_t)3U) /* スレーブVM数 */
#define ECU_ARB_READY_SLEEP_PERIOD (10UL)              /* Ready Sleep周回数 */
#define ECU_ARB_SLEEP_PERIOD       (20UL)              /* Sleep異常判定周回数 */

#define ECU_ARB_MASTER_VCCID ECU_VCCID0

#define VMm (0UL)
#define VMx (1UL)

#if defined(ECU_VM0)
#define ECU_MY_VCCID  ECU_VCCID0
#define ECU_MY_VM     VMm
#define VAL_u4WUF0_A0 (0x00000002UL) /* 管理VMWUFビット番号 A0 BIT01 */
#define VAL_u4WUF0_A1 (0x00000000UL)
#define VAL_u4WUF0_A2 (0x00000080UL) /* TAUJ3_0WUFビット番号 A2 BIT07 */

#elif defined(ECU_VM1)
#define ECU_MY_VM     VMx
#define ECU_MY_VCCID  ECU_VCCID1
#define VAL_u4WUF0_A0 (0x00000004UL) /* A0 BIT02 */
#define VAL_u4WUF0_A1 (0x00000000UL)
#define VAL_u4WUF0_A2 (0x00000000UL)

#elif defined(ECU_VM2)
#define ECU_MY_VM     VMx
#define ECU_MY_VCCID  ECU_VCCID2
#define VAL_u4WUF0_A0 (0x00000008UL) /* A0 BIT03 */
#define VAL_u4WUF0_A1 (0x00000000UL)
#define VAL_u4WUF0_A2 (0x00000000UL)

#elif defined(ECU_VM3)
#define ECU_MY_VM     VMx
#define ECU_MY_VCCID  ECU_VCCID3
#define VAL_u4WUF0_A0 (0x00000010UL) /* A0 BIT04*/
#define VAL_u4WUF0_A1 (0x00000000UL)
#define VAL_u4WUF0_A2 (0x00000000UL)
#else
#error given ECU_VM is not declared
#endif

/*----------------------------------------------------------------------------
 *		プロトタイプ宣言
 *--------------------------------------------------------------------------*/

#endif /* ECU_ARB_CFG_H */
