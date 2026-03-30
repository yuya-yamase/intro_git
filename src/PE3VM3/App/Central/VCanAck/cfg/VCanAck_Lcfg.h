/* VCanAck_Lcfg_h_v1_0_0                                                    */
/****************************************************************************/
/* Copyright (C) 2025 Denso Co.,Ltd. All rights reserved.                   */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | VCanAck_Lcfg/HEADER                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef VCANACK_LCFG_H
#define VCANACK_LCFG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "ehvm_cfg_pe3_vm0.h"
#include "Std_Types.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define VCANACK_CFG_RX_VCC_CH_NUM               (3U)
#define VCANACK_CFG_RX_VCC_CH0                  (EHVM_RX_VCCID_VCCBUFFER_12_VM0_TOOTHERVM)
#define VCANACK_CFG_RX_VCC_CH1                  (EHVM_RX_VCCID_VCCBUFFER_13_VM1_TOVM3)
#define VCANACK_CFG_RX_VCC_CH2                  (EHVM_RX_VCCID_VCCBUFFER_14_VM2_TOVM3)
#define VCANACK_CFG_TX_VCC_CH                   (EHVM_TX_VCCID_VCCBUFFER_15_VM3_TOVM1_2)
#define VCANACK_CFG_RX_LIMIT                    (5U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define VCANACK_START_SEC_VAR_CLEARED_32
#include <VCanAck_MemMap.h>
#define VCANACK_STOP_SEC_VAR_CLEARED_32
#include <VCanAck_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define VCANACK_START_SEC_CONFIG_DATA_32
#include <VCanAck_MemMap.h>

/* Number of Rx vcc channel */ 
extern const uint16 cu2VCanAck_RxVccChNum;

/* Rx vcc channels */
extern const uint32 cu4VCanAck_RxVccChTbl[VCANACK_CFG_RX_VCC_CH_NUM];

/* Tx vcc channel */
extern const uint32 cu4VCanAck_TxVccCh;

/* Rx limit */
extern const uint16 cu2VCanAck_RxLimit;

#define VCANACK_STOP_SEC_CONFIG_DATA_32
#include <VCanAck_MemMap.h>

#endif /* VCANACK_LCFG_H */

/**** End of File ***********************************************************/
