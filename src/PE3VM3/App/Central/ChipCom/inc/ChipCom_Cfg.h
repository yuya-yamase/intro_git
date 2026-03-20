/* ChipCom_Cfg_h_v1_0_0                                                     */
/****************************************************************************/
/* Copyright (C) 2025 Denso Co.,Ltd. All rights reserved.                   */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | ChipCom_Cfg/HEADER                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef CHIPCOM_CFG_H
#define CHIPCOM_CFG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/* Data ID (Handle) */
#define SIGNAL_CHIPCOM_BUS_CDT1S01_SEQCDT1S01                   (0U)
#define SIGNAL_CHIPCOM_BUS_CSS1S01_MCUSLEEPINFO                 (1U)
#define SIGNAL_CHIPCOM_BUS_CDT1S02_SEQCDT1S02                   (2U)
#define SIGNAL_CHIPCOM_BUS_OBC1S01_OBCTXMODEREQ                 (3U)
#define SIGNAL_CHIPCOM_BUS_CDT1S10_SEQCDT1S10                   (4U)
#define SIGNAL_CHIPCOM_BUS_CEN1S10_SAILDATARSTRES               (5U)
#define SIGNAL_CHIPCOM_BUS_CDT1M01_SEQCDT1M01                   (6U)
#define SIGNAL_CHIPCOM_BUS_OBC1M01_OBCTXMODENOTIF               (7U)
#define SIGNAL_CHIPCOM_BUS_CDT1M02_SEQCDT1M02                   (8U)
#define SIGNAL_CHIPCOM_BUS_CSS1M01_CANWKUPSLP                   (9U)
#define SIGNAL_CHIPCOM_BUS_ETH1M01_DOIPCOMPWR                   (10U)
#define SIGNAL_CHIPCOM_BUS_ETH1M01_REGACCESSFAILURE             (11U)
#define SIGNAL_CHIPCOM_BUS_ETH1M01_MAC                          (12U)
#define SIGNAL_CHIPCOM_BUS_ETH1M01_ETHSWTLINK                   (13U)
#define SIGNAL_CHIPCOM_BUS_ETH1M01_ETHSWMIBINFO                 (14U)
#define SIGNAL_CHIPCOM_BUS_ETH1M01_ETHSWTSQI                    (15U)
#define SIGNAL_CHIPCOM_BUS_ETH1M01_ETHSWTTRAFFICOVR             (16U)
#define SIGNAL_CHIPCOM_BUS_ETH1M01_ETHSWTMCUINFO                (17U)
#define SIGNAL_CHIPCOM_BUS_VIS1M01_UTC                          (18U)
#define SIGNAL_CHIPCOM_BUS_VIS1M01_ODD                          (19U)
#define SIGNAL_CHIPCOM_BUS_VIS1M01_VBAT                         (20U)
#define SIGNAL_CHIPCOM_BUS_VIS1M01_TRIPCNT                      (21U)
#define SIGNAL_CHIPCOM_BUS_VIS1M01_SPD                          (22U)
#define SIGNAL_CHIPCOM_BUS_VIS1M01_RDYSYS                       (23U)
#define SIGNAL_CHIPCOM_BUS_VIS1M01_VPWRBASICSTATE               (24U)
#define SIGNAL_CHIPCOM_BUS_VIS1M01_VPWRSPCIALSTATE              (25U)
#define SIGNAL_CHIPCOM_BUS_VIS1M01_VPWRSPCIALSTATETRANSFLG      (26U)
#define SIGNAL_CHIPCOM_BUS_VIS1M01_OTAREPROG                    (27U)
#define SIGNAL_CHIPCOM_BUS_VIS1M01_VPWRSTATUS                   (28U)
#define SIGNAL_CHIPCOM_BUS_VIS1M01_CENTERRLYOFF                 (29U)
#define SIGNAL_CHIPCOM_BUS_VIS1M01_VIN                          (30U)
#define SIGNAL_CHIPCOM_BUS_VIS1M01_COMPWRSTATUS                 (31U)
#define SIGNAL_CHIPCOM_BUS_VIS1M01_SAILRESET                    (32U)
#define SIGNAL_CHIPCOM_BUS_CDT1M03_SEQCDT1M03                   (33U)
#define SIGNAL_CHIPCOM_BUS_ETH1M03_ETHSWTRESET                  (34U)
#define SIGNAL_CHIPCOM_BUS_CDT1M10_SEQCDT1M10                   (35U)
#define SIGNAL_CHIPCOM_BUS_CEN1M10_SAILDATARSTREQ               (36U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define CHIPCOM_START_SEC_VAR_CLEARED_32
#include <ChipCom_MemMap.h>
#define CHIPCOM_STOP_SEC_VAR_CLEARED_32
#include <ChipCom_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define CHIPCOM_START_SEC_CONFIG_DATA_32
#include <ChipCom_MemMap.h>
#define CHIPCOM_STOP_SEC_CONFIG_DATA_32
#include <ChipCom_MemMap.h>

#endif /* CHIPCOM_CFG_H */

/**** End of File ***********************************************************/
