/* bsw_bswm_can_config_h_v3-0-0                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/BSWM/CANCONFIG/HEADER                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_BSWM_CAN_CONFIG_H
#define BSW_BSWM_CAN_CONFIG_H

#include <comm/bsw_comm.h>
#include "../../ComM/inc/bsw_comm_config.h"
#include "../cfg/BswM_Can_Cfg.h"
/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Built-in functions Set */
#define BSW_BSWM_CAN_FUNC_TXERR_NOTIFY           (BSW_BSWM_CAN_CFG_FNC_TXERR_NTFY)

#define BSW_BSWM_CAN_RGSTCHK                     (BSW_BSWM_CAN_CFG_RGSTCHK)

/* Channel -> Network handle conversion macro     */
#define BSW_BSWM_CAN_NETWORK_HANDLE(ch)        (BSW_COMM_BUS_TYPE_OFFSET(CAN) + (ch))

/* Macro to get the bus sleep enable/disable for each channel       */
/* The argument ch is a relative channel number in the CAN protocol    */
#define BSW_BSWM_CAN_BUSSLEEP_USE(ch)          (BSW_BSWM_CAN_BUSSLEEP_USE_0(ch))
#define BSW_BSWM_CAN_BUSSLEEP_USE_0(ch)        ((BSW_BSWM_CAN_NETWORK_HANDLE(ch) == 0U)  ? BSW_COMM_SLPWKUP_USE(0)  : BSW_BSWM_CAN_BUSSLEEP_USE_1(ch))
#define BSW_BSWM_CAN_BUSSLEEP_USE_1(ch)        ((BSW_BSWM_CAN_NETWORK_HANDLE(ch) == 1U)  ? BSW_COMM_SLPWKUP_USE(1)  : BSW_BSWM_CAN_BUSSLEEP_USE_2(ch))
#define BSW_BSWM_CAN_BUSSLEEP_USE_2(ch)        ((BSW_BSWM_CAN_NETWORK_HANDLE(ch) == 2U)  ? BSW_COMM_SLPWKUP_USE(2)  : BSW_BSWM_CAN_BUSSLEEP_USE_3(ch))
#define BSW_BSWM_CAN_BUSSLEEP_USE_3(ch)        ((BSW_BSWM_CAN_NETWORK_HANDLE(ch) == 3U)  ? BSW_COMM_SLPWKUP_USE(3)  : BSW_BSWM_CAN_BUSSLEEP_USE_4(ch))
#define BSW_BSWM_CAN_BUSSLEEP_USE_4(ch)        ((BSW_BSWM_CAN_NETWORK_HANDLE(ch) == 4U)  ? BSW_COMM_SLPWKUP_USE(4)  : BSW_BSWM_CAN_BUSSLEEP_USE_5(ch))
#define BSW_BSWM_CAN_BUSSLEEP_USE_5(ch)        ((BSW_BSWM_CAN_NETWORK_HANDLE(ch) == 5U)  ? BSW_COMM_SLPWKUP_USE(5)  : BSW_BSWM_CAN_BUSSLEEP_USE_6(ch))
#define BSW_BSWM_CAN_BUSSLEEP_USE_6(ch)        ((BSW_BSWM_CAN_NETWORK_HANDLE(ch) == 6U)  ? BSW_COMM_SLPWKUP_USE(6)  : BSW_BSWM_CAN_BUSSLEEP_USE_7(ch))
#define BSW_BSWM_CAN_BUSSLEEP_USE_7(ch)        ((BSW_BSWM_CAN_NETWORK_HANDLE(ch) == 7U)  ? BSW_COMM_SLPWKUP_USE(7)  : BSW_BSWM_CAN_BUSSLEEP_USE_8(ch))
#define BSW_BSWM_CAN_BUSSLEEP_USE_8(ch)        ((BSW_BSWM_CAN_NETWORK_HANDLE(ch) == 8U)  ? BSW_COMM_SLPWKUP_USE(8)  : BSW_BSWM_CAN_BUSSLEEP_USE_9(ch))
#define BSW_BSWM_CAN_BUSSLEEP_USE_9(ch)        ((BSW_BSWM_CAN_NETWORK_HANDLE(ch) == 9U)  ? BSW_COMM_SLPWKUP_USE(9)  : BSW_BSWM_CAN_BUSSLEEP_USE_10(ch))
#define BSW_BSWM_CAN_BUSSLEEP_USE_10(ch)       ((BSW_BSWM_CAN_NETWORK_HANDLE(ch) == 10U) ? BSW_COMM_SLPWKUP_USE(10) : BSW_BSWM_CAN_BUSSLEEP_USE_11(ch))
#define BSW_BSWM_CAN_BUSSLEEP_USE_11(ch)       ((BSW_BSWM_CAN_NETWORK_HANDLE(ch) == 11U) ? BSW_COMM_SLPWKUP_USE(11) : BSW_BSWM_CAN_BUSSLEEP_USE_12(ch))
#define BSW_BSWM_CAN_BUSSLEEP_USE_12(ch)       ((BSW_BSWM_CAN_NETWORK_HANDLE(ch) == 12U) ? BSW_COMM_SLPWKUP_USE(12) : BSW_BSWM_CAN_BUSSLEEP_USE_13(ch))
#define BSW_BSWM_CAN_BUSSLEEP_USE_13(ch)       ((BSW_BSWM_CAN_NETWORK_HANDLE(ch) == 13U) ? BSW_COMM_SLPWKUP_USE(13) : BSW_BSWM_CAN_BUSSLEEP_USE_14(ch))
#define BSW_BSWM_CAN_BUSSLEEP_USE_14(ch)       ((BSW_BSWM_CAN_NETWORK_HANDLE(ch) == 14U) ? BSW_COMM_SLPWKUP_USE(14) : BSW_BSWM_CAN_BUSSLEEP_USE_15(ch))
#define BSW_BSWM_CAN_BUSSLEEP_USE_15(ch)       ((BSW_BSWM_CAN_NETWORK_HANDLE(ch) == 15U) ? BSW_COMM_SLPWKUP_USE(15) : BSW_BSWM_CAN_BUSSLEEP_USE_16(ch))
#define BSW_BSWM_CAN_BUSSLEEP_USE_16(ch)       ((BSW_BSWM_CAN_NETWORK_HANDLE(ch) == 16U) ? BSW_COMM_SLPWKUP_USE(16) : BSW_BSWM_CAN_BUSSLEEP_USE_17(ch))
#define BSW_BSWM_CAN_BUSSLEEP_USE_17(ch)       ((BSW_BSWM_CAN_NETWORK_HANDLE(ch) == 17U) ? BSW_COMM_SLPWKUP_USE(17) : BSW_BSWM_CAN_BUSSLEEP_USE_18(ch))
#define BSW_BSWM_CAN_BUSSLEEP_USE_18(ch)       ((BSW_BSWM_CAN_NETWORK_HANDLE(ch) == 18U) ? BSW_COMM_SLPWKUP_USE(18) : BSW_BSWM_CAN_BUSSLEEP_USE_19(ch))
#define BSW_BSWM_CAN_BUSSLEEP_USE_19(ch)       ((BSW_BSWM_CAN_NETWORK_HANDLE(ch) == 19U) ? BSW_COMM_SLPWKUP_USE(19) : BSW_BSWM_CAN_BUSSLEEP_USE_20(ch))
#define BSW_BSWM_CAN_BUSSLEEP_USE_20(ch)       ((BSW_BSWM_CAN_NETWORK_HANDLE(ch) == 20U) ? BSW_COMM_SLPWKUP_USE(20) : BSW_BSWM_CAN_BUSSLEEP_USE_21(ch))
#define BSW_BSWM_CAN_BUSSLEEP_USE_21(ch)       ((BSW_BSWM_CAN_NETWORK_HANDLE(ch) == 21U) ? BSW_COMM_SLPWKUP_USE(21) : BSW_BSWM_CAN_BUSSLEEP_USE_22(ch))
#define BSW_BSWM_CAN_BUSSLEEP_USE_22(ch)       ((BSW_BSWM_CAN_NETWORK_HANDLE(ch) == 22U) ? BSW_COMM_SLPWKUP_USE(22) : BSW_BSWM_CAN_BUSSLEEP_USE_23(ch))
#define BSW_BSWM_CAN_BUSSLEEP_USE_23(ch)       ((BSW_BSWM_CAN_NETWORK_HANDLE(ch) == 23U) ? BSW_COMM_SLPWKUP_USE(23) : BSW_BSWM_CAN_BUSSLEEP_USE_24(ch))
#define BSW_BSWM_CAN_BUSSLEEP_USE_24(ch)       ((BSW_BSWM_CAN_NETWORK_HANDLE(ch) == 24U) ? BSW_COMM_SLPWKUP_USE(24) : BSW_BSWM_CAN_BUSSLEEP_USE_25(ch))
#define BSW_BSWM_CAN_BUSSLEEP_USE_25(ch)       ((BSW_BSWM_CAN_NETWORK_HANDLE(ch) == 25U) ? BSW_COMM_SLPWKUP_USE(25) : BSW_BSWM_CAN_BUSSLEEP_USE_26(ch))
#define BSW_BSWM_CAN_BUSSLEEP_USE_26(ch)       ((BSW_BSWM_CAN_NETWORK_HANDLE(ch) == 26U) ? BSW_COMM_SLPWKUP_USE(26) : BSW_BSWM_CAN_BUSSLEEP_USE_27(ch))
#define BSW_BSWM_CAN_BUSSLEEP_USE_27(ch)       ((BSW_BSWM_CAN_NETWORK_HANDLE(ch) == 27U) ? BSW_COMM_SLPWKUP_USE(27) : BSW_BSWM_CAN_BUSSLEEP_USE_28(ch))
#define BSW_BSWM_CAN_BUSSLEEP_USE_28(ch)       ((BSW_BSWM_CAN_NETWORK_HANDLE(ch) == 28U) ? BSW_COMM_SLPWKUP_USE(28) : BSW_BSWM_CAN_BUSSLEEP_USE_29(ch))
#define BSW_BSWM_CAN_BUSSLEEP_USE_29(ch)       ((BSW_BSWM_CAN_NETWORK_HANDLE(ch) == 29U) ? BSW_COMM_SLPWKUP_USE(29) : BSW_BSWM_CAN_BUSSLEEP_USE_30(ch))
#define BSW_BSWM_CAN_BUSSLEEP_USE_30(ch)       ((BSW_BSWM_CAN_NETWORK_HANDLE(ch) == 30U) ? BSW_COMM_SLPWKUP_USE(30) : BSW_BSWM_CAN_BUSSLEEP_USE_31(ch))
#define BSW_BSWM_CAN_BUSSLEEP_USE_31(ch)       ((BSW_BSWM_CAN_NETWORK_HANDLE(ch) == 31U) ? BSW_COMM_SLPWKUP_USE(31) : BSW_NOUSE )

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* BSW_BSWM_CAN_CONFIG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v2-0-0          :2021/12/02                                             */
/*  v3-0-0          :2024/11/13                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
