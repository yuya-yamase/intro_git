/* bsw_comm_config_h_v3-0-0                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/COMM/CONFIG/HEADER                                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_COMM_CONFIG_H
#define BSW_COMM_CONFIG_H

#include <bswm_cs/bsw_bswm_cs.h>
#include "../cfg/ComM_Cfg.h"
/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define BSW_COMM_CHNUM                (BSW_COMM_CFG_CHNUM)
#define BSW_COMM_OFFSET_NOUSE         (0U)

#define BSW_COMM_BUSTYPE(ch)          (BSW_COMM_CFG_BUS_TYPE_##ch)
#define BSW_COMM_SLPWKUP_USE(ch)      ((BSW_COMM_CFG_NM_ACT_TYPE_##ch == BSW_COMM_NM_ACT_TYPE_BSSLP) ? BSW_USE : BSW_NOUSE)

/* Used/unused get macro for each bus type */
/* The argument type should be set according to the protocol type */
/* -------------------------------------------- */
/* Protocols         | Setting value            */
/* -------------------------------------------- */
/* Can                | CAN                     */
/* Ethernet           | ETH                     */
/* Lin                | LIN                     */
/* -------------------------------------------- */
#define BSW_COMM_BUS_TYPE_USE(type)     (BSW_COMM_BUS_TYPE_USE_##type)

/* Macro to get network handle start position for each bus type */
/* The argument type should be set according to the protocol type */
/* -------------------------------------------- */
/* Protocols         | Setting value            */
/* -------------------------------------------- */
/* Can                | CAN                     */
/* Ethernet           | ETH                     */
/* Lin                | LIN                     */
/* -------------------------------------------- */
#define BSW_COMM_BUS_TYPE_OFFSET(type)  (BSW_COMM_BUS_TYPE_OFFSET_##type)

#if (BSW_COMM_BUSTYPE(0) == BSW_COMM_BUS_TYPE_CAN)
#define BSW_COMM_BUS_TYPE_USE_CAN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_CAN     (0U)
#elif (BSW_COMM_BUSTYPE(1) == BSW_COMM_BUS_TYPE_CAN)
#define BSW_COMM_BUS_TYPE_USE_CAN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_CAN     (1U)
#elif (BSW_COMM_BUSTYPE(2) == BSW_COMM_BUS_TYPE_CAN)
#define BSW_COMM_BUS_TYPE_USE_CAN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_CAN     (2U)
#elif (BSW_COMM_BUSTYPE(3) == BSW_COMM_BUS_TYPE_CAN)
#define BSW_COMM_BUS_TYPE_USE_CAN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_CAN     (3U)
#elif (BSW_COMM_BUSTYPE(4) == BSW_COMM_BUS_TYPE_CAN)
#define BSW_COMM_BUS_TYPE_USE_CAN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_CAN     (4U)
#elif (BSW_COMM_BUSTYPE(5) == BSW_COMM_BUS_TYPE_CAN)
#define BSW_COMM_BUS_TYPE_USE_CAN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_CAN     (5U)
#elif (BSW_COMM_BUSTYPE(6) == BSW_COMM_BUS_TYPE_CAN)
#define BSW_COMM_BUS_TYPE_USE_CAN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_CAN     (6U)
#elif (BSW_COMM_BUSTYPE(7) == BSW_COMM_BUS_TYPE_CAN)
#define BSW_COMM_BUS_TYPE_USE_CAN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_CAN     (7U)
#elif (BSW_COMM_BUSTYPE(8) == BSW_COMM_BUS_TYPE_CAN)
#define BSW_COMM_BUS_TYPE_USE_CAN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_CAN     (8U)
#elif (BSW_COMM_BUSTYPE(9) == BSW_COMM_BUS_TYPE_CAN)
#define BSW_COMM_BUS_TYPE_USE_CAN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_CAN     (9U)
#elif (BSW_COMM_BUSTYPE(10) == BSW_COMM_BUS_TYPE_CAN)
#define BSW_COMM_BUS_TYPE_USE_CAN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_CAN     (10U)
#elif (BSW_COMM_BUSTYPE(11) == BSW_COMM_BUS_TYPE_CAN)
#define BSW_COMM_BUS_TYPE_USE_CAN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_CAN     (11U)
#elif (BSW_COMM_BUSTYPE(12) == BSW_COMM_BUS_TYPE_CAN)
#define BSW_COMM_BUS_TYPE_USE_CAN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_CAN     (12U)
#elif (BSW_COMM_BUSTYPE(13) == BSW_COMM_BUS_TYPE_CAN)
#define BSW_COMM_BUS_TYPE_USE_CAN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_CAN     (13U)
#elif (BSW_COMM_BUSTYPE(14) == BSW_COMM_BUS_TYPE_CAN)
#define BSW_COMM_BUS_TYPE_USE_CAN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_CAN     (14U)
#elif (BSW_COMM_BUSTYPE(15) == BSW_COMM_BUS_TYPE_CAN)
#define BSW_COMM_BUS_TYPE_USE_CAN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_CAN     (15U)
#elif (BSW_COMM_BUSTYPE(16) == BSW_COMM_BUS_TYPE_CAN)
#define BSW_COMM_BUS_TYPE_USE_CAN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_CAN     (16U)
#elif (BSW_COMM_BUSTYPE(17) == BSW_COMM_BUS_TYPE_CAN)
#define BSW_COMM_BUS_TYPE_USE_CAN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_CAN     (17U)
#elif (BSW_COMM_BUSTYPE(18) == BSW_COMM_BUS_TYPE_CAN)
#define BSW_COMM_BUS_TYPE_USE_CAN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_CAN     (18U)
#elif (BSW_COMM_BUSTYPE(19) == BSW_COMM_BUS_TYPE_CAN)
#define BSW_COMM_BUS_TYPE_USE_CAN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_CAN     (19U)
#elif (BSW_COMM_BUSTYPE(20) == BSW_COMM_BUS_TYPE_CAN)
#define BSW_COMM_BUS_TYPE_USE_CAN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_CAN     (20U)
#elif (BSW_COMM_BUSTYPE(21) == BSW_COMM_BUS_TYPE_CAN)
#define BSW_COMM_BUS_TYPE_USE_CAN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_CAN     (21U)
#elif (BSW_COMM_BUSTYPE(22) == BSW_COMM_BUS_TYPE_CAN)
#define BSW_COMM_BUS_TYPE_USE_CAN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_CAN     (22U)
#elif (BSW_COMM_BUSTYPE(23) == BSW_COMM_BUS_TYPE_CAN)
#define BSW_COMM_BUS_TYPE_USE_CAN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_CAN     (23U)
#elif (BSW_COMM_BUSTYPE(24) == BSW_COMM_BUS_TYPE_CAN)
#define BSW_COMM_BUS_TYPE_USE_CAN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_CAN     (24U)
#elif (BSW_COMM_BUSTYPE(25) == BSW_COMM_BUS_TYPE_CAN)
#define BSW_COMM_BUS_TYPE_USE_CAN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_CAN     (25U)
#elif (BSW_COMM_BUSTYPE(26) == BSW_COMM_BUS_TYPE_CAN)
#define BSW_COMM_BUS_TYPE_USE_CAN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_CAN     (26U)
#elif (BSW_COMM_BUSTYPE(27) == BSW_COMM_BUS_TYPE_CAN)
#define BSW_COMM_BUS_TYPE_USE_CAN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_CAN     (27U)
#elif (BSW_COMM_BUSTYPE(28) == BSW_COMM_BUS_TYPE_CAN)
#define BSW_COMM_BUS_TYPE_USE_CAN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_CAN     (28U)
#elif (BSW_COMM_BUSTYPE(29) == BSW_COMM_BUS_TYPE_CAN)
#define BSW_COMM_BUS_TYPE_USE_CAN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_CAN     (29U)
#elif (BSW_COMM_BUSTYPE(30) == BSW_COMM_BUS_TYPE_CAN)
#define BSW_COMM_BUS_TYPE_USE_CAN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_CAN     (30U)
#elif (BSW_COMM_BUSTYPE(31) == BSW_COMM_BUS_TYPE_CAN)
#define BSW_COMM_BUS_TYPE_USE_CAN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_CAN     (31U)
#else
#define BSW_COMM_BUS_TYPE_USE_CAN        (BSW_NOUSE)
#define BSW_COMM_BUS_TYPE_OFFSET_CAN     (BSW_COMM_OFFSET_NOUSE)
#endif

#if (BSW_COMM_BUSTYPE(0) == BSW_COMM_BUS_TYPE_ETH)
#define BSW_COMM_BUS_TYPE_USE_ETH        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_ETH     (0U)
#elif (BSW_COMM_BUSTYPE(1) == BSW_COMM_BUS_TYPE_ETH)
#define BSW_COMM_BUS_TYPE_USE_ETH        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_ETH     (1U)
#elif (BSW_COMM_BUSTYPE(2) == BSW_COMM_BUS_TYPE_ETH)
#define BSW_COMM_BUS_TYPE_USE_ETH        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_ETH     (2U)
#elif (BSW_COMM_BUSTYPE(3) == BSW_COMM_BUS_TYPE_ETH)
#define BSW_COMM_BUS_TYPE_USE_ETH        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_ETH     (3U)
#elif (BSW_COMM_BUSTYPE(4) == BSW_COMM_BUS_TYPE_ETH)
#define BSW_COMM_BUS_TYPE_USE_ETH        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_ETH     (4U)
#elif (BSW_COMM_BUSTYPE(5) == BSW_COMM_BUS_TYPE_ETH)
#define BSW_COMM_BUS_TYPE_USE_ETH        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_ETH     (5U)
#elif (BSW_COMM_BUSTYPE(6) == BSW_COMM_BUS_TYPE_ETH)
#define BSW_COMM_BUS_TYPE_USE_ETH        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_ETH     (6U)
#elif (BSW_COMM_BUSTYPE(7) == BSW_COMM_BUS_TYPE_ETH)
#define BSW_COMM_BUS_TYPE_USE_ETH        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_ETH     (7U)
#elif (BSW_COMM_BUSTYPE(8) == BSW_COMM_BUS_TYPE_ETH)
#define BSW_COMM_BUS_TYPE_USE_ETH        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_ETH     (8U)
#elif (BSW_COMM_BUSTYPE(9) == BSW_COMM_BUS_TYPE_ETH)
#define BSW_COMM_BUS_TYPE_USE_ETH        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_ETH     (9U)
#elif (BSW_COMM_BUSTYPE(10) == BSW_COMM_BUS_TYPE_ETH)
#define BSW_COMM_BUS_TYPE_USE_ETH        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_ETH     (10U)
#elif (BSW_COMM_BUSTYPE(11) == BSW_COMM_BUS_TYPE_ETH)
#define BSW_COMM_BUS_TYPE_USE_ETH        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_ETH     (11U)
#elif (BSW_COMM_BUSTYPE(12) == BSW_COMM_BUS_TYPE_ETH)
#define BSW_COMM_BUS_TYPE_USE_ETH        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_ETH     (12U)
#elif (BSW_COMM_BUSTYPE(13) == BSW_COMM_BUS_TYPE_ETH)
#define BSW_COMM_BUS_TYPE_USE_ETH        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_ETH     (13U)
#elif (BSW_COMM_BUSTYPE(14) == BSW_COMM_BUS_TYPE_ETH)
#define BSW_COMM_BUS_TYPE_USE_ETH        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_ETH     (14U)
#elif (BSW_COMM_BUSTYPE(15) == BSW_COMM_BUS_TYPE_ETH)
#define BSW_COMM_BUS_TYPE_USE_ETH        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_ETH     (15U)
#elif (BSW_COMM_BUSTYPE(16) == BSW_COMM_BUS_TYPE_ETH)
#define BSW_COMM_BUS_TYPE_USE_ETH        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_ETH     (16U)
#elif (BSW_COMM_BUSTYPE(17) == BSW_COMM_BUS_TYPE_ETH)
#define BSW_COMM_BUS_TYPE_USE_ETH        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_ETH     (17U)
#elif (BSW_COMM_BUSTYPE(18) == BSW_COMM_BUS_TYPE_ETH)
#define BSW_COMM_BUS_TYPE_USE_ETH        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_ETH     (18U)
#elif (BSW_COMM_BUSTYPE(19) == BSW_COMM_BUS_TYPE_ETH)
#define BSW_COMM_BUS_TYPE_USE_ETH        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_ETH     (19U)
#elif (BSW_COMM_BUSTYPE(20) == BSW_COMM_BUS_TYPE_ETH)
#define BSW_COMM_BUS_TYPE_USE_ETH        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_ETH     (20U)
#elif (BSW_COMM_BUSTYPE(21) == BSW_COMM_BUS_TYPE_ETH)
#define BSW_COMM_BUS_TYPE_USE_ETH        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_ETH     (21U)
#elif (BSW_COMM_BUSTYPE(22) == BSW_COMM_BUS_TYPE_ETH)
#define BSW_COMM_BUS_TYPE_USE_ETH        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_ETH     (22U)
#elif (BSW_COMM_BUSTYPE(23) == BSW_COMM_BUS_TYPE_ETH)
#define BSW_COMM_BUS_TYPE_USE_ETH        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_ETH     (23U)
#elif (BSW_COMM_BUSTYPE(24) == BSW_COMM_BUS_TYPE_ETH)
#define BSW_COMM_BUS_TYPE_USE_ETH        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_ETH     (24U)
#elif (BSW_COMM_BUSTYPE(25) == BSW_COMM_BUS_TYPE_ETH)
#define BSW_COMM_BUS_TYPE_USE_ETH        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_ETH     (25U)
#elif (BSW_COMM_BUSTYPE(26) == BSW_COMM_BUS_TYPE_ETH)
#define BSW_COMM_BUS_TYPE_USE_ETH        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_ETH     (26U)
#elif (BSW_COMM_BUSTYPE(27) == BSW_COMM_BUS_TYPE_ETH)
#define BSW_COMM_BUS_TYPE_USE_ETH        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_ETH     (27U)
#elif (BSW_COMM_BUSTYPE(28) == BSW_COMM_BUS_TYPE_ETH)
#define BSW_COMM_BUS_TYPE_USE_ETH        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_ETH     (28U)
#elif (BSW_COMM_BUSTYPE(29) == BSW_COMM_BUS_TYPE_ETH)
#define BSW_COMM_BUS_TYPE_USE_ETH        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_ETH     (29U)
#elif (BSW_COMM_BUSTYPE(30) == BSW_COMM_BUS_TYPE_ETH)
#define BSW_COMM_BUS_TYPE_USE_ETH        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_ETH     (30U)
#elif (BSW_COMM_BUSTYPE(31) == BSW_COMM_BUS_TYPE_ETH)
#define BSW_COMM_BUS_TYPE_USE_ETH        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_ETH     (31U)
#else
#define BSW_COMM_BUS_TYPE_USE_ETH        (BSW_NOUSE)
#define BSW_COMM_BUS_TYPE_OFFSET_ETH     (BSW_COMM_OFFSET_NOUSE)
#endif

#if (BSW_COMM_BUSTYPE(0) == BSW_COMM_BUS_TYPE_LIN)
#define BSW_COMM_BUS_TYPE_USE_LIN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_LIN     (0U)
#elif (BSW_COMM_BUSTYPE(1) == BSW_COMM_BUS_TYPE_LIN)
#define BSW_COMM_BUS_TYPE_USE_LIN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_LIN     (1U)
#elif (BSW_COMM_BUSTYPE(2) == BSW_COMM_BUS_TYPE_LIN)
#define BSW_COMM_BUS_TYPE_USE_LIN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_LIN     (2U)
#elif (BSW_COMM_BUSTYPE(3) == BSW_COMM_BUS_TYPE_LIN)
#define BSW_COMM_BUS_TYPE_USE_LIN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_LIN     (3U)
#elif (BSW_COMM_BUSTYPE(4) == BSW_COMM_BUS_TYPE_LIN)
#define BSW_COMM_BUS_TYPE_USE_LIN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_LIN     (4U)
#elif (BSW_COMM_BUSTYPE(5) == BSW_COMM_BUS_TYPE_LIN)
#define BSW_COMM_BUS_TYPE_USE_LIN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_LIN     (5U)
#elif (BSW_COMM_BUSTYPE(6) == BSW_COMM_BUS_TYPE_LIN)
#define BSW_COMM_BUS_TYPE_USE_LIN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_LIN     (6U)
#elif (BSW_COMM_BUSTYPE(7) == BSW_COMM_BUS_TYPE_LIN)
#define BSW_COMM_BUS_TYPE_USE_LIN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_LIN     (7U)
#elif (BSW_COMM_BUSTYPE(8) == BSW_COMM_BUS_TYPE_LIN)
#define BSW_COMM_BUS_TYPE_USE_LIN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_LIN     (8U)
#elif (BSW_COMM_BUSTYPE(9) == BSW_COMM_BUS_TYPE_LIN)
#define BSW_COMM_BUS_TYPE_USE_LIN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_LIN     (9U)
#elif (BSW_COMM_BUSTYPE(10) == BSW_COMM_BUS_TYPE_LIN)
#define BSW_COMM_BUS_TYPE_USE_LIN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_LIN     (10U)
#elif (BSW_COMM_BUSTYPE(11) == BSW_COMM_BUS_TYPE_LIN)
#define BSW_COMM_BUS_TYPE_USE_LIN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_LIN     (11U)
#elif (BSW_COMM_BUSTYPE(12) == BSW_COMM_BUS_TYPE_LIN)
#define BSW_COMM_BUS_TYPE_USE_LIN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_LIN     (12U)
#elif (BSW_COMM_BUSTYPE(13) == BSW_COMM_BUS_TYPE_LIN)
#define BSW_COMM_BUS_TYPE_USE_LIN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_LIN     (13U)
#elif (BSW_COMM_BUSTYPE(14) == BSW_COMM_BUS_TYPE_LIN)
#define BSW_COMM_BUS_TYPE_USE_LIN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_LIN     (14U)
#elif (BSW_COMM_BUSTYPE(15) == BSW_COMM_BUS_TYPE_LIN)
#define BSW_COMM_BUS_TYPE_USE_LIN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_LIN     (15U)
#elif (BSW_COMM_BUSTYPE(16) == BSW_COMM_BUS_TYPE_LIN)
#define BSW_COMM_BUS_TYPE_USE_LIN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_LIN     (16U)
#elif (BSW_COMM_BUSTYPE(17) == BSW_COMM_BUS_TYPE_LIN)
#define BSW_COMM_BUS_TYPE_USE_LIN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_LIN     (17U)
#elif (BSW_COMM_BUSTYPE(18) == BSW_COMM_BUS_TYPE_LIN)
#define BSW_COMM_BUS_TYPE_USE_LIN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_LIN     (18U)
#elif (BSW_COMM_BUSTYPE(19) == BSW_COMM_BUS_TYPE_LIN)
#define BSW_COMM_BUS_TYPE_USE_LIN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_LIN     (19U)
#elif (BSW_COMM_BUSTYPE(20) == BSW_COMM_BUS_TYPE_LIN)
#define BSW_COMM_BUS_TYPE_USE_LIN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_LIN     (20U)
#elif (BSW_COMM_BUSTYPE(21) == BSW_COMM_BUS_TYPE_LIN)
#define BSW_COMM_BUS_TYPE_USE_LIN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_LIN     (21U)
#elif (BSW_COMM_BUSTYPE(22) == BSW_COMM_BUS_TYPE_LIN)
#define BSW_COMM_BUS_TYPE_USE_LIN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_LIN     (22U)
#elif (BSW_COMM_BUSTYPE(23) == BSW_COMM_BUS_TYPE_LIN)
#define BSW_COMM_BUS_TYPE_USE_LIN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_LIN     (23U)
#elif (BSW_COMM_BUSTYPE(24) == BSW_COMM_BUS_TYPE_LIN)
#define BSW_COMM_BUS_TYPE_USE_LIN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_LIN     (24U)
#elif (BSW_COMM_BUSTYPE(25) == BSW_COMM_BUS_TYPE_LIN)
#define BSW_COMM_BUS_TYPE_USE_LIN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_LIN     (25U)
#elif (BSW_COMM_BUSTYPE(26) == BSW_COMM_BUS_TYPE_LIN)
#define BSW_COMM_BUS_TYPE_USE_LIN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_LIN     (26U)
#elif (BSW_COMM_BUSTYPE(27) == BSW_COMM_BUS_TYPE_LIN)
#define BSW_COMM_BUS_TYPE_USE_LIN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_LIN     (27U)
#elif (BSW_COMM_BUSTYPE(28) == BSW_COMM_BUS_TYPE_LIN)
#define BSW_COMM_BUS_TYPE_USE_LIN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_LIN     (28U)
#elif (BSW_COMM_BUSTYPE(29) == BSW_COMM_BUS_TYPE_LIN)
#define BSW_COMM_BUS_TYPE_USE_LIN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_LIN     (29U)
#elif (BSW_COMM_BUSTYPE(30) == BSW_COMM_BUS_TYPE_LIN)
#define BSW_COMM_BUS_TYPE_USE_LIN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_LIN     (30U)
#elif (BSW_COMM_BUSTYPE(31) == BSW_COMM_BUS_TYPE_LIN)
#define BSW_COMM_BUS_TYPE_USE_LIN        (BSW_USE)
#define BSW_COMM_BUS_TYPE_OFFSET_LIN     (31U)
#else
#define BSW_COMM_BUS_TYPE_USE_LIN        (BSW_NOUSE)
#define BSW_COMM_BUS_TYPE_OFFSET_LIN     (BSW_COMM_OFFSET_NOUSE)
#endif

/* Macro for getting the network handle count for each bus type */
/* The argument type should be set according to the protocol type */
/* -------------------------------------------- */
/* Protocols         | Setting value            */
/* -------------------------------------------- */
/* Can                | CAN                     */
/* Ethernet           | ETH                     */
/* Lin                | LIN                     */
/* -------------------------------------------- */
#define BSW_COMM_BUS_TYPE_CHNUM(type)           (BSW_COMM_BUS_TYPE_CHNUM_0_3(type) + BSW_COMM_BUS_TYPE_CHNUM_4_7(type) + BSW_COMM_BUS_TYPE_CHNUM_8_11(type) + BSW_COMM_BUS_TYPE_CHNUM_12_15(type) \
                                               + BSW_COMM_BUS_TYPE_CHNUM_16_19(type) + BSW_COMM_BUS_TYPE_CHNUM_20_23(type) + BSW_COMM_BUS_TYPE_CHNUM_24_27(type) + BSW_COMM_BUS_TYPE_CHNUM_28_31(type) )
#define BSW_COMM_BUS_TYPE_CHNUM_CH(ch,type)     ((BSW_COMM_BUSTYPE(ch)  == BSW_COMM_BUS_TYPE_##type) ? 1U  : 0U)
#define BSW_COMM_BUS_TYPE_CHNUM_0_3(type)       (BSW_COMM_BUS_TYPE_CHNUM_CH(0,type) + BSW_COMM_BUS_TYPE_CHNUM_CH(1,type) + BSW_COMM_BUS_TYPE_CHNUM_CH(2,type) + BSW_COMM_BUS_TYPE_CHNUM_CH(3,type))
#define BSW_COMM_BUS_TYPE_CHNUM_4_7(type)       (BSW_COMM_BUS_TYPE_CHNUM_CH(4,type) + BSW_COMM_BUS_TYPE_CHNUM_CH(5,type) + BSW_COMM_BUS_TYPE_CHNUM_CH(6,type) + BSW_COMM_BUS_TYPE_CHNUM_CH(7,type))
#define BSW_COMM_BUS_TYPE_CHNUM_8_11(type)      (BSW_COMM_BUS_TYPE_CHNUM_CH(8,type) + BSW_COMM_BUS_TYPE_CHNUM_CH(9,type) + BSW_COMM_BUS_TYPE_CHNUM_CH(10,type)+ BSW_COMM_BUS_TYPE_CHNUM_CH(11,type))
#define BSW_COMM_BUS_TYPE_CHNUM_12_15(type)     (BSW_COMM_BUS_TYPE_CHNUM_CH(12,type)+ BSW_COMM_BUS_TYPE_CHNUM_CH(13,type)+ BSW_COMM_BUS_TYPE_CHNUM_CH(14,type)+ BSW_COMM_BUS_TYPE_CHNUM_CH(15,type))
#define BSW_COMM_BUS_TYPE_CHNUM_16_19(type)     (BSW_COMM_BUS_TYPE_CHNUM_CH(16,type)+ BSW_COMM_BUS_TYPE_CHNUM_CH(17,type)+ BSW_COMM_BUS_TYPE_CHNUM_CH(18,type)+ BSW_COMM_BUS_TYPE_CHNUM_CH(19,type))
#define BSW_COMM_BUS_TYPE_CHNUM_20_23(type)     (BSW_COMM_BUS_TYPE_CHNUM_CH(20,type)+ BSW_COMM_BUS_TYPE_CHNUM_CH(21,type)+ BSW_COMM_BUS_TYPE_CHNUM_CH(22,type)+ BSW_COMM_BUS_TYPE_CHNUM_CH(23,type))
#define BSW_COMM_BUS_TYPE_CHNUM_24_27(type)     (BSW_COMM_BUS_TYPE_CHNUM_CH(24,type)+ BSW_COMM_BUS_TYPE_CHNUM_CH(25,type)+ BSW_COMM_BUS_TYPE_CHNUM_CH(26,type)+ BSW_COMM_BUS_TYPE_CHNUM_CH(27,type))
#define BSW_COMM_BUS_TYPE_CHNUM_28_31(type)     (BSW_COMM_BUS_TYPE_CHNUM_CH(28,type)+ BSW_COMM_BUS_TYPE_CHNUM_CH(29,type)+ BSW_COMM_BUS_TYPE_CHNUM_CH(30,type)+ BSW_COMM_BUS_TYPE_CHNUM_CH(31,type))


/* MS->Tick conversion macro */
#define BSW_COMM_u2MILSEC_RUP             BSW_BSWM_CS_u2MS2TICK_RUP_MID

/* Use/not use PNC function */
#define BSW_COMM_PNC_FUNC                (BSW_COMM_CFG_PNC)

/* Channel -> Network handle conversion macro */
#define BSW_COMM_NETWORK(type, ch)       (BSW_COMM_BUS_TYPE_OFFSET(type) + (ch))

/* Channel attribute getting macro for protocol   */
/* type   :Protocol type               */
/* ------------------------------------ */
/*  Protocols       | Setting value     */
/* ------------------------------------ */
/*  Can              | CAN              */
/*  Ethernet         | ETH              */
/*  Lin              | LIN              */
/* ------------------------------------ */
/* ch: Relative channel number for each protocol */
#define BSW_COMM_CH_ATTRBT(type, ch)     BSW_COMM_CH_ATTRBT_0(type, ch)
#define BSW_COMM_CH_ATTRBT_0(type, ch)   ((BSW_COMM_NETWORK(type, ch) == 0U)  ? BSW_COMM_CFG_CH_ATTRIBUTE_0  : BSW_COMM_CH_ATTRBT_1(type, ch))
#define BSW_COMM_CH_ATTRBT_1(type, ch)   ((BSW_COMM_NETWORK(type, ch) == 1U)  ? BSW_COMM_CFG_CH_ATTRIBUTE_1  : BSW_COMM_CH_ATTRBT_2(type, ch))
#define BSW_COMM_CH_ATTRBT_2(type, ch)   ((BSW_COMM_NETWORK(type, ch) == 2U)  ? BSW_COMM_CFG_CH_ATTRIBUTE_2  : BSW_COMM_CH_ATTRBT_3(type, ch))
#define BSW_COMM_CH_ATTRBT_3(type, ch)   ((BSW_COMM_NETWORK(type, ch) == 3U)  ? BSW_COMM_CFG_CH_ATTRIBUTE_3  : BSW_COMM_CH_ATTRBT_4(type, ch))
#define BSW_COMM_CH_ATTRBT_4(type, ch)   ((BSW_COMM_NETWORK(type, ch) == 4U)  ? BSW_COMM_CFG_CH_ATTRIBUTE_4  : BSW_COMM_CH_ATTRBT_5(type, ch))
#define BSW_COMM_CH_ATTRBT_5(type, ch)   ((BSW_COMM_NETWORK(type, ch) == 5U)  ? BSW_COMM_CFG_CH_ATTRIBUTE_5  : BSW_COMM_CH_ATTRBT_6(type, ch))
#define BSW_COMM_CH_ATTRBT_6(type, ch)   ((BSW_COMM_NETWORK(type, ch) == 6U)  ? BSW_COMM_CFG_CH_ATTRIBUTE_6  : BSW_COMM_CH_ATTRBT_7(type, ch))
#define BSW_COMM_CH_ATTRBT_7(type, ch)   ((BSW_COMM_NETWORK(type, ch) == 7U)  ? BSW_COMM_CFG_CH_ATTRIBUTE_7  : BSW_COMM_CH_ATTRBT_8(type, ch))
#define BSW_COMM_CH_ATTRBT_8(type, ch)   ((BSW_COMM_NETWORK(type, ch) == 8U)  ? BSW_COMM_CFG_CH_ATTRIBUTE_8  : BSW_COMM_CH_ATTRBT_9(type, ch))
#define BSW_COMM_CH_ATTRBT_9(type, ch)   ((BSW_COMM_NETWORK(type, ch) == 9U)  ? BSW_COMM_CFG_CH_ATTRIBUTE_9  : BSW_COMM_CH_ATTRBT_10(type, ch))
#define BSW_COMM_CH_ATTRBT_10(type, ch)  ((BSW_COMM_NETWORK(type, ch) == 10U) ? BSW_COMM_CFG_CH_ATTRIBUTE_10 : BSW_COMM_CH_ATTRBT_11(type, ch))
#define BSW_COMM_CH_ATTRBT_11(type, ch)  ((BSW_COMM_NETWORK(type, ch) == 11U) ? BSW_COMM_CFG_CH_ATTRIBUTE_11 : BSW_COMM_CH_ATTRBT_12(type, ch))
#define BSW_COMM_CH_ATTRBT_12(type, ch)  ((BSW_COMM_NETWORK(type, ch) == 12U) ? BSW_COMM_CFG_CH_ATTRIBUTE_12 : BSW_COMM_CH_ATTRBT_13(type, ch))
#define BSW_COMM_CH_ATTRBT_13(type, ch)  ((BSW_COMM_NETWORK(type, ch) == 13U) ? BSW_COMM_CFG_CH_ATTRIBUTE_13 : BSW_COMM_CH_ATTRBT_14(type, ch))
#define BSW_COMM_CH_ATTRBT_14(type, ch)  ((BSW_COMM_NETWORK(type, ch) == 14U) ? BSW_COMM_CFG_CH_ATTRIBUTE_14 : BSW_COMM_CH_ATTRBT_15(type, ch))
#define BSW_COMM_CH_ATTRBT_15(type, ch)  ((BSW_COMM_NETWORK(type, ch) == 15U) ? BSW_COMM_CFG_CH_ATTRIBUTE_15 : BSW_COMM_CH_ATTRBT_16(type, ch))
#define BSW_COMM_CH_ATTRBT_16(type, ch)  ((BSW_COMM_NETWORK(type, ch) == 16U) ? BSW_COMM_CFG_CH_ATTRIBUTE_16 : BSW_COMM_CH_ATTRBT_17(type, ch))
#define BSW_COMM_CH_ATTRBT_17(type, ch)  ((BSW_COMM_NETWORK(type, ch) == 17U) ? BSW_COMM_CFG_CH_ATTRIBUTE_17 : BSW_COMM_CH_ATTRBT_18(type, ch))
#define BSW_COMM_CH_ATTRBT_18(type, ch)  ((BSW_COMM_NETWORK(type, ch) == 18U) ? BSW_COMM_CFG_CH_ATTRIBUTE_18 : BSW_COMM_CH_ATTRBT_19(type, ch))
#define BSW_COMM_CH_ATTRBT_19(type, ch)  ((BSW_COMM_NETWORK(type, ch) == 19U) ? BSW_COMM_CFG_CH_ATTRIBUTE_19 : BSW_COMM_CH_ATTRBT_20(type, ch))
#define BSW_COMM_CH_ATTRBT_20(type, ch)  ((BSW_COMM_NETWORK(type, ch) == 20U) ? BSW_COMM_CFG_CH_ATTRIBUTE_20 : BSW_COMM_CH_ATTRBT_21(type, ch))
#define BSW_COMM_CH_ATTRBT_21(type, ch)  ((BSW_COMM_NETWORK(type, ch) == 21U) ? BSW_COMM_CFG_CH_ATTRIBUTE_21 : BSW_COMM_CH_ATTRBT_22(type, ch))
#define BSW_COMM_CH_ATTRBT_22(type, ch)  ((BSW_COMM_NETWORK(type, ch) == 22U) ? BSW_COMM_CFG_CH_ATTRIBUTE_22 : BSW_COMM_CH_ATTRBT_23(type, ch))
#define BSW_COMM_CH_ATTRBT_23(type, ch)  ((BSW_COMM_NETWORK(type, ch) == 23U) ? BSW_COMM_CFG_CH_ATTRIBUTE_23 : BSW_COMM_CH_ATTRBT_24(type, ch))
#define BSW_COMM_CH_ATTRBT_24(type, ch)  ((BSW_COMM_NETWORK(type, ch) == 24U) ? BSW_COMM_CFG_CH_ATTRIBUTE_24 : BSW_COMM_CH_ATTRBT_25(type, ch))
#define BSW_COMM_CH_ATTRBT_25(type, ch)  ((BSW_COMM_NETWORK(type, ch) == 25U) ? BSW_COMM_CFG_CH_ATTRIBUTE_25 : BSW_COMM_CH_ATTRBT_26(type, ch))
#define BSW_COMM_CH_ATTRBT_26(type, ch)  ((BSW_COMM_NETWORK(type, ch) == 26U) ? BSW_COMM_CFG_CH_ATTRIBUTE_26 : BSW_COMM_CH_ATTRBT_27(type, ch))
#define BSW_COMM_CH_ATTRBT_27(type, ch)  ((BSW_COMM_NETWORK(type, ch) == 27U) ? BSW_COMM_CFG_CH_ATTRIBUTE_27 : BSW_COMM_CH_ATTRBT_28(type, ch))
#define BSW_COMM_CH_ATTRBT_28(type, ch)  ((BSW_COMM_NETWORK(type, ch) == 28U) ? BSW_COMM_CFG_CH_ATTRIBUTE_28 : BSW_COMM_CH_ATTRBT_29(type, ch))
#define BSW_COMM_CH_ATTRBT_29(type, ch)  ((BSW_COMM_NETWORK(type, ch) == 29U) ? BSW_COMM_CFG_CH_ATTRIBUTE_29 : BSW_COMM_CH_ATTRBT_30(type, ch))
#define BSW_COMM_CH_ATTRBT_30(type, ch)  ((BSW_COMM_NETWORK(type, ch) == 30U) ? BSW_COMM_CFG_CH_ATTRIBUTE_30 : BSW_COMM_CH_ATTRBT_31(type, ch))
#define BSW_COMM_CH_ATTRBT_31(type, ch)  ((BSW_COMM_NETWORK(type, ch) == 31U) ? BSW_COMM_CFG_CH_ATTRIBUTE_31 : BSW_COMM_CH_ATTRBT_PHYSICAL)

#if ( BSW_COMM_CFG_CHNUM > 0U )
#if ( BSW_COMM_CFG_CH_PNCNUM_0 > 0U )
#define BSW_COMM_CH_PNCNUM_0         BSW_COMM_CFG_CH_PNCNUM_0
#define BSW_COMM_CH_PNAWKPW_NUM_0    (BSW_COMM_CH_PNCNUM_0 << 1U)
#else
#define BSW_COMM_CH_PNCNUM_0         BSW_COMM_PNCNUM_NONE
#define BSW_COMM_CH_PNAWKPW_NUM_0    BSW_COMM_PNCNUM_NONE
#endif
#endif
#if ( BSW_COMM_CFG_CHNUM > 1U )
#if ( BSW_COMM_CFG_CH_PNCNUM_1 > 0U )
#define BSW_COMM_CH_PNCNUM_1         BSW_COMM_CFG_CH_PNCNUM_1
#define BSW_COMM_CH_PNAWKPW_NUM_1    (BSW_COMM_CH_PNCNUM_1 << 1U)
#else
#define BSW_COMM_CH_PNCNUM_1         BSW_COMM_PNCNUM_NONE
#define BSW_COMM_CH_PNAWKPW_NUM_1    BSW_COMM_PNCNUM_NONE
#endif
#endif
#if ( BSW_COMM_CFG_CHNUM > 2U )
#if ( BSW_COMM_CFG_CH_PNCNUM_2 > 0U )
#define BSW_COMM_CH_PNCNUM_2         BSW_COMM_CFG_CH_PNCNUM_2
#define BSW_COMM_CH_PNAWKPW_NUM_2    (BSW_COMM_CH_PNCNUM_2 << 1U)
#else
#define BSW_COMM_CH_PNCNUM_2         BSW_COMM_PNCNUM_NONE
#define BSW_COMM_CH_PNAWKPW_NUM_2    BSW_COMM_PNCNUM_NONE
#endif
#endif
#if ( BSW_COMM_CFG_CHNUM > 3U )
#if ( BSW_COMM_CFG_CH_PNCNUM_3 > 0U )
#define BSW_COMM_CH_PNCNUM_3         BSW_COMM_CFG_CH_PNCNUM_3
#define BSW_COMM_CH_PNAWKPW_NUM_3    (BSW_COMM_CH_PNCNUM_3 << 1U)
#else
#define BSW_COMM_CH_PNCNUM_3         BSW_COMM_PNCNUM_NONE
#define BSW_COMM_CH_PNAWKPW_NUM_3    BSW_COMM_PNCNUM_NONE
#endif
#endif
#if ( BSW_COMM_CFG_CHNUM > 4U )
#if ( BSW_COMM_CFG_CH_PNCNUM_4 > 0U )
#define BSW_COMM_CH_PNCNUM_4         BSW_COMM_CFG_CH_PNCNUM_4
#define BSW_COMM_CH_PNAWKPW_NUM_4    (BSW_COMM_CH_PNCNUM_4 << 1U)
#else
#define BSW_COMM_CH_PNCNUM_4         BSW_COMM_PNCNUM_NONE
#define BSW_COMM_CH_PNAWKPW_NUM_4    BSW_COMM_PNCNUM_NONE
#endif
#endif
#if ( BSW_COMM_CFG_CHNUM > 5U )
#if ( BSW_COMM_CFG_CH_PNCNUM_5 > 0U )
#define BSW_COMM_CH_PNCNUM_5         BSW_COMM_CFG_CH_PNCNUM_5
#define BSW_COMM_CH_PNAWKPW_NUM_5    (BSW_COMM_CH_PNCNUM_5 << 1U)
#else
#define BSW_COMM_CH_PNCNUM_5         BSW_COMM_PNCNUM_NONE
#define BSW_COMM_CH_PNAWKPW_NUM_5    BSW_COMM_PNCNUM_NONE
#endif
#endif
#if ( BSW_COMM_CFG_CHNUM > 6U )
#if ( BSW_COMM_CFG_CH_PNCNUM_6 > 0U )
#define BSW_COMM_CH_PNCNUM_6         BSW_COMM_CFG_CH_PNCNUM_6
#define BSW_COMM_CH_PNAWKPW_NUM_6    (BSW_COMM_CH_PNCNUM_6 << 1U)
#else
#define BSW_COMM_CH_PNCNUM_6         BSW_COMM_PNCNUM_NONE
#define BSW_COMM_CH_PNAWKPW_NUM_6    BSW_COMM_PNCNUM_NONE
#endif
#endif
#if ( BSW_COMM_CFG_CHNUM > 7U )
#if ( BSW_COMM_CFG_CH_PNCNUM_7 > 0U )
#define BSW_COMM_CH_PNCNUM_7         BSW_COMM_CFG_CH_PNCNUM_7
#define BSW_COMM_CH_PNAWKPW_NUM_7    (BSW_COMM_CH_PNCNUM_7 << 1U)
#else
#define BSW_COMM_CH_PNCNUM_7         BSW_COMM_PNCNUM_NONE
#define BSW_COMM_CH_PNAWKPW_NUM_7    BSW_COMM_PNCNUM_NONE
#endif
#endif
#if ( BSW_COMM_CFG_CHNUM > 8U )
#if ( BSW_COMM_CFG_CH_PNCNUM_8 > 0U )
#define BSW_COMM_CH_PNCNUM_8         BSW_COMM_CFG_CH_PNCNUM_8
#define BSW_COMM_CH_PNAWKPW_NUM_8    (BSW_COMM_CH_PNCNUM_8 << 1U)
#else
#define BSW_COMM_CH_PNCNUM_8         BSW_COMM_PNCNUM_NONE
#define BSW_COMM_CH_PNAWKPW_NUM_8    BSW_COMM_PNCNUM_NONE
#endif
#endif
#if ( BSW_COMM_CFG_CHNUM > 9U )
#if ( BSW_COMM_CFG_CH_PNCNUM_9 > 0U )
#define BSW_COMM_CH_PNCNUM_9         BSW_COMM_CFG_CH_PNCNUM_9
#define BSW_COMM_CH_PNAWKPW_NUM_9    (BSW_COMM_CH_PNCNUM_9 << 1U)
#else
#define BSW_COMM_CH_PNCNUM_9         BSW_COMM_PNCNUM_NONE
#define BSW_COMM_CH_PNAWKPW_NUM_9    BSW_COMM_PNCNUM_NONE
#endif
#endif
#if ( BSW_COMM_CFG_CHNUM > 10U )
#if ( BSW_COMM_CFG_CH_PNCNUM_10 > 0U )
#define BSW_COMM_CH_PNCNUM_10        BSW_COMM_CFG_CH_PNCNUM_10
#define BSW_COMM_CH_PNAWKPW_NUM_10   (BSW_COMM_CH_PNCNUM_10 << 1U)
#else
#define BSW_COMM_CH_PNCNUM_10        BSW_COMM_PNCNUM_NONE
#define BSW_COMM_CH_PNAWKPW_NUM_10   BSW_COMM_PNCNUM_NONE
#endif
#endif
#if ( BSW_COMM_CFG_CHNUM > 11U )
#if ( BSW_COMM_CFG_CH_PNCNUM_11 > 0U )
#define BSW_COMM_CH_PNCNUM_11        BSW_COMM_CFG_CH_PNCNUM_11
#define BSW_COMM_CH_PNAWKPW_NUM_11   (BSW_COMM_CH_PNCNUM_11 << 1U)
#else
#define BSW_COMM_CH_PNCNUM_11        BSW_COMM_PNCNUM_NONE
#define BSW_COMM_CH_PNAWKPW_NUM_11   BSW_COMM_PNCNUM_NONE
#endif
#endif
#if ( BSW_COMM_CFG_CHNUM > 12U )
#if ( BSW_COMM_CFG_CH_PNCNUM_12 > 0U )
#define BSW_COMM_CH_PNCNUM_12        BSW_COMM_CFG_CH_PNCNUM_12
#define BSW_COMM_CH_PNAWKPW_NUM_12   (BSW_COMM_CH_PNCNUM_12 << 1U)
#else
#define BSW_COMM_CH_PNCNUM_12        BSW_COMM_PNCNUM_NONE
#define BSW_COMM_CH_PNAWKPW_NUM_12   BSW_COMM_PNCNUM_NONE
#endif
#endif
#if ( BSW_COMM_CFG_CHNUM > 13U )
#if ( BSW_COMM_CFG_CH_PNCNUM_13 > 0U )
#define BSW_COMM_CH_PNCNUM_13        BSW_COMM_CFG_CH_PNCNUM_13
#define BSW_COMM_CH_PNAWKPW_NUM_13   (BSW_COMM_CH_PNCNUM_13 << 1U)
#else
#define BSW_COMM_CH_PNCNUM_13        BSW_COMM_PNCNUM_NONE
#define BSW_COMM_CH_PNAWKPW_NUM_13   BSW_COMM_PNCNUM_NONE
#endif
#endif
#if ( BSW_COMM_CFG_CHNUM > 14U )
#if ( BSW_COMM_CFG_CH_PNCNUM_14 > 0U )
#define BSW_COMM_CH_PNCNUM_14        BSW_COMM_CFG_CH_PNCNUM_14
#define BSW_COMM_CH_PNAWKPW_NUM_14   (BSW_COMM_CH_PNCNUM_14 << 1U)
#else
#define BSW_COMM_CH_PNCNUM_14        BSW_COMM_PNCNUM_NONE
#define BSW_COMM_CH_PNAWKPW_NUM_14   BSW_COMM_PNCNUM_NONE
#endif
#endif
#if ( BSW_COMM_CFG_CHNUM > 15U )
#if ( BSW_COMM_CFG_CH_PNCNUM_15 > 0U )
#define BSW_COMM_CH_PNCNUM_15        BSW_COMM_CFG_CH_PNCNUM_15
#define BSW_COMM_CH_PNAWKPW_NUM_15   (BSW_COMM_CH_PNCNUM_15 << 1U)
#else
#define BSW_COMM_CH_PNCNUM_15        BSW_COMM_PNCNUM_NONE
#define BSW_COMM_CH_PNAWKPW_NUM_15   BSW_COMM_PNCNUM_NONE
#endif
#endif
#if ( BSW_COMM_CFG_CHNUM > 16U )
#if ( BSW_COMM_CFG_CH_PNCNUM_16 > 0U )
#define BSW_COMM_CH_PNCNUM_16        BSW_COMM_CFG_CH_PNCNUM_16
#define BSW_COMM_CH_PNAWKPW_NUM_16   (BSW_COMM_CH_PNCNUM_16 << 1U)
#else
#define BSW_COMM_CH_PNCNUM_16        BSW_COMM_PNCNUM_NONE
#define BSW_COMM_CH_PNAWKPW_NUM_16   BSW_COMM_PNCNUM_NONE
#endif
#endif
#if ( BSW_COMM_CFG_CHNUM > 17U )
#if ( BSW_COMM_CFG_CH_PNCNUM_17 > 0U )
#define BSW_COMM_CH_PNCNUM_17        BSW_COMM_CFG_CH_PNCNUM_17
#define BSW_COMM_CH_PNAWKPW_NUM_17   (BSW_COMM_CH_PNCNUM_17 << 1U)
#else
#define BSW_COMM_CH_PNCNUM_17        BSW_COMM_PNCNUM_NONE
#define BSW_COMM_CH_PNAWKPW_NUM_17   BSW_COMM_PNCNUM_NONE
#endif
#endif
#if ( BSW_COMM_CFG_CHNUM > 18U )
#if ( BSW_COMM_CFG_CH_PNCNUM_18 > 0U )
#define BSW_COMM_CH_PNCNUM_18        BSW_COMM_CFG_CH_PNCNUM_18
#define BSW_COMM_CH_PNAWKPW_NUM_18   (BSW_COMM_CH_PNCNUM_18 << 1U)
#else
#define BSW_COMM_CH_PNCNUM_18        BSW_COMM_PNCNUM_NONE
#define BSW_COMM_CH_PNAWKPW_NUM_18   BSW_COMM_PNCNUM_NONE
#endif
#endif
#if ( BSW_COMM_CFG_CHNUM > 19U )
#if ( BSW_COMM_CFG_CH_PNCNUM_19 > 0U )
#define BSW_COMM_CH_PNCNUM_19        BSW_COMM_CFG_CH_PNCNUM_19
#define BSW_COMM_CH_PNAWKPW_NUM_19   (BSW_COMM_CH_PNCNUM_19 << 1U)
#else
#define BSW_COMM_CH_PNCNUM_19        BSW_COMM_PNCNUM_NONE
#define BSW_COMM_CH_PNAWKPW_NUM_19   BSW_COMM_PNCNUM_NONE
#endif
#endif
#if ( BSW_COMM_CFG_CHNUM > 20U )
#if ( BSW_COMM_CFG_CH_PNCNUM_20 > 0U )
#define BSW_COMM_CH_PNCNUM_20        BSW_COMM_CFG_CH_PNCNUM_20
#define BSW_COMM_CH_PNAWKPW_NUM_20   (BSW_COMM_CH_PNCNUM_20 << 1U)
#else
#define BSW_COMM_CH_PNCNUM_20        BSW_COMM_PNCNUM_NONE
#define BSW_COMM_CH_PNAWKPW_NUM_20   BSW_COMM_PNCNUM_NONE
#endif
#endif
#if ( BSW_COMM_CFG_CHNUM > 21U )
#if ( BSW_COMM_CFG_CH_PNCNUM_21 > 0U )
#define BSW_COMM_CH_PNCNUM_21        BSW_COMM_CFG_CH_PNCNUM_21
#define BSW_COMM_CH_PNAWKPW_NUM_21   (BSW_COMM_CH_PNCNUM_21 << 1U)
#else
#define BSW_COMM_CH_PNCNUM_21        BSW_COMM_PNCNUM_NONE
#define BSW_COMM_CH_PNAWKPW_NUM_21   BSW_COMM_PNCNUM_NONE
#endif
#endif
#if ( BSW_COMM_CFG_CHNUM > 22U )
#if ( BSW_COMM_CFG_CH_PNCNUM_22 > 0U )
#define BSW_COMM_CH_PNCNUM_22        BSW_COMM_CFG_CH_PNCNUM_22
#define BSW_COMM_CH_PNAWKPW_NUM_22   (BSW_COMM_CH_PNCNUM_22 << 1U)
#else
#define BSW_COMM_CH_PNCNUM_22        BSW_COMM_PNCNUM_NONE
#define BSW_COMM_CH_PNAWKPW_NUM_22   BSW_COMM_PNCNUM_NONE
#endif
#endif
#if ( BSW_COMM_CFG_CHNUM > 23U )
#if ( BSW_COMM_CFG_CH_PNCNUM_23 > 0U )
#define BSW_COMM_CH_PNCNUM_23        BSW_COMM_CFG_CH_PNCNUM_23
#define BSW_COMM_CH_PNAWKPW_NUM_23   (BSW_COMM_CH_PNCNUM_23 << 1U)
#else
#define BSW_COMM_CH_PNCNUM_23        BSW_COMM_PNCNUM_NONE
#define BSW_COMM_CH_PNAWKPW_NUM_23   BSW_COMM_PNCNUM_NONE
#endif
#endif
#if ( BSW_COMM_CFG_CHNUM > 24U )
#if ( BSW_COMM_CFG_CH_PNCNUM_24 > 0U )
#define BSW_COMM_CH_PNCNUM_24        BSW_COMM_CFG_CH_PNCNUM_24
#define BSW_COMM_CH_PNAWKPW_NUM_24   (BSW_COMM_CH_PNCNUM_24 << 1U)
#else
#define BSW_COMM_CH_PNCNUM_24        BSW_COMM_PNCNUM_NONE
#define BSW_COMM_CH_PNAWKPW_NUM_24   BSW_COMM_PNCNUM_NONE
#endif
#endif
#if ( BSW_COMM_CFG_CHNUM > 25U )
#if ( BSW_COMM_CFG_CH_PNCNUM_25 > 0U )
#define BSW_COMM_CH_PNCNUM_25        BSW_COMM_CFG_CH_PNCNUM_25
#define BSW_COMM_CH_PNAWKPW_NUM_25   (BSW_COMM_CH_PNCNUM_25 << 1U)
#else
#define BSW_COMM_CH_PNCNUM_25        BSW_COMM_PNCNUM_NONE
#define BSW_COMM_CH_PNAWKPW_NUM_25   BSW_COMM_PNCNUM_NONE
#endif
#endif
#if ( BSW_COMM_CFG_CHNUM > 26U )
#if ( BSW_COMM_CFG_CH_PNCNUM_26 > 0U )
#define BSW_COMM_CH_PNCNUM_26        BSW_COMM_CFG_CH_PNCNUM_26
#define BSW_COMM_CH_PNAWKPW_NUM_26   (BSW_COMM_CH_PNCNUM_26 << 1U)
#else
#define BSW_COMM_CH_PNCNUM_26        BSW_COMM_PNCNUM_NONE
#define BSW_COMM_CH_PNAWKPW_NUM_26   BSW_COMM_PNCNUM_NONE
#endif
#endif
#if ( BSW_COMM_CFG_CHNUM > 27U )
#if ( BSW_COMM_CFG_CH_PNCNUM_27 > 0U )
#define BSW_COMM_CH_PNCNUM_27        BSW_COMM_CFG_CH_PNCNUM_27
#define BSW_COMM_CH_PNAWKPW_NUM_27   (BSW_COMM_CH_PNCNUM_27 << 1U)
#else
#define BSW_COMM_CH_PNCNUM_27        BSW_COMM_PNCNUM_NONE
#define BSW_COMM_CH_PNAWKPW_NUM_27   BSW_COMM_PNCNUM_NONE
#endif
#endif
#if ( BSW_COMM_CFG_CHNUM > 28U )
#if ( BSW_COMM_CFG_CH_PNCNUM_28 > 0U )
#define BSW_COMM_CH_PNCNUM_28        BSW_COMM_CFG_CH_PNCNUM_28
#define BSW_COMM_CH_PNAWKPW_NUM_28   (BSW_COMM_CH_PNCNUM_28 << 1U)
#else
#define BSW_COMM_CH_PNCNUM_28        BSW_COMM_PNCNUM_NONE
#define BSW_COMM_CH_PNAWKPW_NUM_28   BSW_COMM_PNCNUM_NONE
#endif
#endif
#if ( BSW_COMM_CFG_CHNUM > 29U )
#if ( BSW_COMM_CFG_CH_PNCNUM_29 > 0U )
#define BSW_COMM_CH_PNCNUM_29        BSW_COMM_CFG_CH_PNCNUM_29
#define BSW_COMM_CH_PNAWKPW_NUM_29   (BSW_COMM_CH_PNCNUM_29 << 1U)
#else
#define BSW_COMM_CH_PNCNUM_29        BSW_COMM_PNCNUM_NONE
#define BSW_COMM_CH_PNAWKPW_NUM_29   BSW_COMM_PNCNUM_NONE
#endif
#endif
#if ( BSW_COMM_CFG_CHNUM > 30U )
#if ( BSW_COMM_CFG_CH_PNCNUM_30 > 0U )
#define BSW_COMM_CH_PNCNUM_30        BSW_COMM_CFG_CH_PNCNUM_30
#define BSW_COMM_CH_PNAWKPW_NUM_30   (BSW_COMM_CH_PNCNUM_30 << 1U)
#else
#define BSW_COMM_CH_PNCNUM_30        BSW_COMM_PNCNUM_NONE
#define BSW_COMM_CH_PNAWKPW_NUM_30   BSW_COMM_PNCNUM_NONE
#endif
#endif
#if ( BSW_COMM_CFG_CHNUM > 31U )
#if ( BSW_COMM_CFG_CH_PNCNUM_31 > 0U )
#define BSW_COMM_CH_PNCNUM_31        BSW_COMM_CFG_CH_PNCNUM_31
#define BSW_COMM_CH_PNAWKPW_NUM_31   (BSW_COMM_CH_PNCNUM_31 << 1U)
#else
#define BSW_COMM_CH_PNCNUM_31        BSW_COMM_PNCNUM_NONE
#define BSW_COMM_CH_PNAWKPW_NUM_31   BSW_COMM_PNCNUM_NONE
#endif
#endif

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

#endif /* BSW_COMM_CONFIG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/09/08                                             */
/*  v1-1-0          :2018/07/02                                             */
/*  v2-0-0          :2021/12/02                                             */
/*  v2-1-0          :2022/06/09                                             */
/*  v3-0-0          :2024/11/14                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
