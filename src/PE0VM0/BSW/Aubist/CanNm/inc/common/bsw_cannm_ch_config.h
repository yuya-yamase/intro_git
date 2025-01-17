/* bsw_cannm_ch_config_h_v2-0-0                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANNM/CH/CONFIG/HEADER                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#ifndef BSW_CANNM_CH_CONFIG_H
#define BSW_CANNM_CH_CONFIG_H

#include <comm/bsw_comm.h>
#include "../../../ComM/inc/bsw_comm_config.h"
#include "../../cfg/common/CanNm_Ch_Cfg.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define BSW_CANNM_OFFSET_NONE               (0U)
#define BSW_CANNM_NM_TYPE(ch)               (BSW_CANNM_CFG_NM_TYPE_CH##ch)

/* Channel -> Network handle conversion macro     */
#define BSW_CANNM_NETWORK_HANDLE(ch)        (BSW_COMM_BUS_TYPE_OFFSET(CAN) + (ch))

/* Used/unused acquisition macro for each NM type */
/* The argument type should be set according to the NM type         */
/* -------------------------------------------- */
/* NM Type             | Setting value                  */
/* -------------------------------------------- */
/* Can Nm/A           | A                       */
/* CanNm              | A2                      */
/* Can Nm/B           | B                       */
/* Can Nm/C2          | C2                      */
/* Can Nm/E           | E                       */
/* Can Nm/X           | X                       */
/* Can Nm/Y           | Y                       */
/* NM without NM           | Z                       */
/* None               | NONE                    */
/* -------------------------------------------- */
#define BSW_CANNM_NM_TYPE_USE(type)         (BSW_CANNM_NM_TYPE_USE_0(type))
#define BSW_CANNM_NM_TYPE_USE_0(type)       ((BSW_CANNM_NM_TYPE(0)   == BSW_CANNM_NMTYPE_##type) ? BSW_USE : BSW_CANNM_NM_TYPE_USE_1(type))
#define BSW_CANNM_NM_TYPE_USE_1(type)       ((BSW_CANNM_NM_TYPE(1)   == BSW_CANNM_NMTYPE_##type) ? BSW_USE : BSW_CANNM_NM_TYPE_USE_2(type))
#define BSW_CANNM_NM_TYPE_USE_2(type)       ((BSW_CANNM_NM_TYPE(2)   == BSW_CANNM_NMTYPE_##type) ? BSW_USE : BSW_CANNM_NM_TYPE_USE_3(type))
#define BSW_CANNM_NM_TYPE_USE_3(type)       ((BSW_CANNM_NM_TYPE(3)   == BSW_CANNM_NMTYPE_##type) ? BSW_USE : BSW_CANNM_NM_TYPE_USE_4(type))
#define BSW_CANNM_NM_TYPE_USE_4(type)       ((BSW_CANNM_NM_TYPE(4)   == BSW_CANNM_NMTYPE_##type) ? BSW_USE : BSW_CANNM_NM_TYPE_USE_5(type))
#define BSW_CANNM_NM_TYPE_USE_5(type)       ((BSW_CANNM_NM_TYPE(5)   == BSW_CANNM_NMTYPE_##type) ? BSW_USE : BSW_CANNM_NM_TYPE_USE_6(type))
#define BSW_CANNM_NM_TYPE_USE_6(type)       ((BSW_CANNM_NM_TYPE(6)   == BSW_CANNM_NMTYPE_##type) ? BSW_USE : BSW_CANNM_NM_TYPE_USE_7(type))
#define BSW_CANNM_NM_TYPE_USE_7(type)       ((BSW_CANNM_NM_TYPE(7)   == BSW_CANNM_NMTYPE_##type) ? BSW_USE : BSW_CANNM_NM_TYPE_USE_8(type))
#define BSW_CANNM_NM_TYPE_USE_8(type)       ((BSW_CANNM_NM_TYPE(8)   == BSW_CANNM_NMTYPE_##type) ? BSW_USE : BSW_CANNM_NM_TYPE_USE_9(type))
#define BSW_CANNM_NM_TYPE_USE_9(type)       ((BSW_CANNM_NM_TYPE(9)   == BSW_CANNM_NMTYPE_##type) ? BSW_USE : BSW_CANNM_NM_TYPE_USE_10(type))
#define BSW_CANNM_NM_TYPE_USE_10(type)      ((BSW_CANNM_NM_TYPE(10)  == BSW_CANNM_NMTYPE_##type) ? BSW_USE : BSW_CANNM_NM_TYPE_USE_11(type))
#define BSW_CANNM_NM_TYPE_USE_11(type)      ((BSW_CANNM_NM_TYPE(11)  == BSW_CANNM_NMTYPE_##type) ? BSW_USE : BSW_CANNM_NM_TYPE_USE_12(type))
#define BSW_CANNM_NM_TYPE_USE_12(type)      ((BSW_CANNM_NM_TYPE(12)  == BSW_CANNM_NMTYPE_##type) ? BSW_USE : BSW_CANNM_NM_TYPE_USE_13(type))
#define BSW_CANNM_NM_TYPE_USE_13(type)      ((BSW_CANNM_NM_TYPE(13)  == BSW_CANNM_NMTYPE_##type) ? BSW_USE : BSW_CANNM_NM_TYPE_USE_14(type))
#define BSW_CANNM_NM_TYPE_USE_14(type)      ((BSW_CANNM_NM_TYPE(14)  == BSW_CANNM_NMTYPE_##type) ? BSW_USE : BSW_CANNM_NM_TYPE_USE_15(type))
#define BSW_CANNM_NM_TYPE_USE_15(type)      ((BSW_CANNM_NM_TYPE(15)  == BSW_CANNM_NMTYPE_##type) ? BSW_USE : BSW_CANNM_NM_TYPE_USE_16(type))
#define BSW_CANNM_NM_TYPE_USE_16(type)      ((BSW_CANNM_NM_TYPE(16)  == BSW_CANNM_NMTYPE_##type) ? BSW_USE : BSW_CANNM_NM_TYPE_USE_17(type))
#define BSW_CANNM_NM_TYPE_USE_17(type)      ((BSW_CANNM_NM_TYPE(17)  == BSW_CANNM_NMTYPE_##type) ? BSW_USE : BSW_CANNM_NM_TYPE_USE_18(type))
#define BSW_CANNM_NM_TYPE_USE_18(type)      ((BSW_CANNM_NM_TYPE(18)  == BSW_CANNM_NMTYPE_##type) ? BSW_USE : BSW_CANNM_NM_TYPE_USE_19(type))
#define BSW_CANNM_NM_TYPE_USE_19(type)      ((BSW_CANNM_NM_TYPE(19)  == BSW_CANNM_NMTYPE_##type) ? BSW_USE : BSW_CANNM_NM_TYPE_USE_20(type))
#define BSW_CANNM_NM_TYPE_USE_20(type)      ((BSW_CANNM_NM_TYPE(20)  == BSW_CANNM_NMTYPE_##type) ? BSW_USE : BSW_CANNM_NM_TYPE_USE_21(type))
#define BSW_CANNM_NM_TYPE_USE_21(type)      ((BSW_CANNM_NM_TYPE(21)  == BSW_CANNM_NMTYPE_##type) ? BSW_USE : BSW_CANNM_NM_TYPE_USE_22(type))
#define BSW_CANNM_NM_TYPE_USE_22(type)      ((BSW_CANNM_NM_TYPE(22)  == BSW_CANNM_NMTYPE_##type) ? BSW_USE : BSW_CANNM_NM_TYPE_USE_23(type))
#define BSW_CANNM_NM_TYPE_USE_23(type)      ((BSW_CANNM_NM_TYPE(23)  == BSW_CANNM_NMTYPE_##type) ? BSW_USE : BSW_CANNM_NM_TYPE_USE_24(type))
#define BSW_CANNM_NM_TYPE_USE_24(type)      ((BSW_CANNM_NM_TYPE(24)  == BSW_CANNM_NMTYPE_##type) ? BSW_USE : BSW_CANNM_NM_TYPE_USE_25(type))
#define BSW_CANNM_NM_TYPE_USE_25(type)      ((BSW_CANNM_NM_TYPE(25)  == BSW_CANNM_NMTYPE_##type) ? BSW_USE : BSW_CANNM_NM_TYPE_USE_26(type))
#define BSW_CANNM_NM_TYPE_USE_26(type)      ((BSW_CANNM_NM_TYPE(26)  == BSW_CANNM_NMTYPE_##type) ? BSW_USE : BSW_CANNM_NM_TYPE_USE_27(type))
#define BSW_CANNM_NM_TYPE_USE_27(type)      ((BSW_CANNM_NM_TYPE(27)  == BSW_CANNM_NMTYPE_##type) ? BSW_USE : BSW_CANNM_NM_TYPE_USE_28(type))
#define BSW_CANNM_NM_TYPE_USE_28(type)      ((BSW_CANNM_NM_TYPE(28)  == BSW_CANNM_NMTYPE_##type) ? BSW_USE : BSW_CANNM_NM_TYPE_USE_29(type))
#define BSW_CANNM_NM_TYPE_USE_29(type)      ((BSW_CANNM_NM_TYPE(29)  == BSW_CANNM_NMTYPE_##type) ? BSW_USE : BSW_CANNM_NM_TYPE_USE_30(type))
#define BSW_CANNM_NM_TYPE_USE_30(type)      ((BSW_CANNM_NM_TYPE(30)  == BSW_CANNM_NMTYPE_##type) ? BSW_USE : BSW_CANNM_NM_TYPE_USE_31(type))
#define BSW_CANNM_NM_TYPE_USE_31(type)      ((BSW_CANNM_NM_TYPE(31)  == BSW_CANNM_NMTYPE_##type) ? BSW_USE : BSW_NOUSE)

#if ( BSW_CANNM_NM_TYPE_USE(A) == BSW_USE )
#define BSW_CANNM_NM_TYPE_USE_A     (BSW_USE)
#else
#define BSW_CANNM_NM_TYPE_USE_A     (BSW_NOUSE)
#endif

#if ( BSW_CANNM_NM_TYPE_USE(A2) == BSW_USE )
#define BSW_CANNM_NM_TYPE_USE_A2    (BSW_USE)
#else
#define BSW_CANNM_NM_TYPE_USE_A2    (BSW_NOUSE)
#endif

#if ( BSW_CANNM_NM_TYPE_USE(B) == BSW_USE )
#define BSW_CANNM_NM_TYPE_USE_B     (BSW_USE)
#else
#define BSW_CANNM_NM_TYPE_USE_B     (BSW_NOUSE)
#endif

#if ( BSW_CANNM_NM_TYPE_USE(C2) == BSW_USE )
#define BSW_CANNM_NM_TYPE_USE_C2    (BSW_USE)
#else
#define BSW_CANNM_NM_TYPE_USE_C2    (BSW_NOUSE)
#endif

#if ( BSW_CANNM_NM_TYPE_USE(E) == BSW_USE )
#define BSW_CANNM_NM_TYPE_USE_E     (BSW_USE)
#else
#define BSW_CANNM_NM_TYPE_USE_E     (BSW_NOUSE)
#endif

#if ( BSW_CANNM_NM_TYPE_USE(X) == BSW_USE )
#define BSW_CANNM_NM_TYPE_USE_X     (BSW_USE)
#else
#define BSW_CANNM_NM_TYPE_USE_X     (BSW_NOUSE)
#endif

#if ( BSW_CANNM_NM_TYPE_USE(Y) == BSW_USE )
#define BSW_CANNM_NM_TYPE_USE_Y     (BSW_USE)
#else
#define BSW_CANNM_NM_TYPE_USE_Y     (BSW_NOUSE)
#endif

#if ( BSW_CANNM_NM_TYPE_USE(Z) == BSW_USE )
#define BSW_CANNM_NM_TYPE_USE_Z     (BSW_USE)
#else
#define BSW_CANNM_NM_TYPE_USE_Z     (BSW_NOUSE)
#endif

/* Macro for obtaining the network handle start position for each NM type */
/* The argument type should be set according to the NM type         */
/* -------------------------------------------- */
/* NM Type             | Setting value                  */
/* -------------------------------------------- */
/* Can Nm/A           | A                       */
/* CanNm              | A2                      */
/* Can Nm/B           | B                       */
/* Can Nm/C2          | C2                      */
/* Can Nm/E           | E                       */
/* Can Nm/X           | X                       */
/* Can Nm/Y           | Y                       */
/* NM without NM           | Z                       */
/* None               | NONE                    */
/* -------------------------------------------- */
#define BSW_CANNM_NM_TYPE_OFFSET(type)      (BSW_CANNM_NM_TYPE_OFFSET_0(type))
#define BSW_CANNM_NM_TYPE_OFFSET_0(type)    ((BSW_CANNM_NM_TYPE(0)   == BSW_CANNM_NMTYPE_##type) ? 0U   : BSW_CANNM_NM_TYPE_OFFSET_1(type))
#define BSW_CANNM_NM_TYPE_OFFSET_1(type)    ((BSW_CANNM_NM_TYPE(1)   == BSW_CANNM_NMTYPE_##type) ? 1U   : BSW_CANNM_NM_TYPE_OFFSET_2(type))
#define BSW_CANNM_NM_TYPE_OFFSET_2(type)    ((BSW_CANNM_NM_TYPE(2)   == BSW_CANNM_NMTYPE_##type) ? 2U   : BSW_CANNM_NM_TYPE_OFFSET_3(type))
#define BSW_CANNM_NM_TYPE_OFFSET_3(type)    ((BSW_CANNM_NM_TYPE(3)   == BSW_CANNM_NMTYPE_##type) ? 3U   : BSW_CANNM_NM_TYPE_OFFSET_4(type))
#define BSW_CANNM_NM_TYPE_OFFSET_4(type)    ((BSW_CANNM_NM_TYPE(4)   == BSW_CANNM_NMTYPE_##type) ? 4U   : BSW_CANNM_NM_TYPE_OFFSET_5(type))
#define BSW_CANNM_NM_TYPE_OFFSET_5(type)    ((BSW_CANNM_NM_TYPE(5)   == BSW_CANNM_NMTYPE_##type) ? 5U   : BSW_CANNM_NM_TYPE_OFFSET_6(type))
#define BSW_CANNM_NM_TYPE_OFFSET_6(type)    ((BSW_CANNM_NM_TYPE(6)   == BSW_CANNM_NMTYPE_##type) ? 6U   : BSW_CANNM_NM_TYPE_OFFSET_7(type))
#define BSW_CANNM_NM_TYPE_OFFSET_7(type)    ((BSW_CANNM_NM_TYPE(7)   == BSW_CANNM_NMTYPE_##type) ? 7U   : BSW_CANNM_NM_TYPE_OFFSET_8(type))
#define BSW_CANNM_NM_TYPE_OFFSET_8(type)    ((BSW_CANNM_NM_TYPE(8)   == BSW_CANNM_NMTYPE_##type) ? 8U   : BSW_CANNM_NM_TYPE_OFFSET_9(type))
#define BSW_CANNM_NM_TYPE_OFFSET_9(type)    ((BSW_CANNM_NM_TYPE(9)   == BSW_CANNM_NMTYPE_##type) ? 9U   : BSW_CANNM_NM_TYPE_OFFSET_10(type))
#define BSW_CANNM_NM_TYPE_OFFSET_10(type)   ((BSW_CANNM_NM_TYPE(10)  == BSW_CANNM_NMTYPE_##type) ? 10U  : BSW_CANNM_NM_TYPE_OFFSET_11(type))
#define BSW_CANNM_NM_TYPE_OFFSET_11(type)   ((BSW_CANNM_NM_TYPE(11)  == BSW_CANNM_NMTYPE_##type) ? 11U  : BSW_CANNM_NM_TYPE_OFFSET_12(type))
#define BSW_CANNM_NM_TYPE_OFFSET_12(type)   ((BSW_CANNM_NM_TYPE(12)  == BSW_CANNM_NMTYPE_##type) ? 12U  : BSW_CANNM_NM_TYPE_OFFSET_13(type))
#define BSW_CANNM_NM_TYPE_OFFSET_13(type)   ((BSW_CANNM_NM_TYPE(13)  == BSW_CANNM_NMTYPE_##type) ? 13U  : BSW_CANNM_NM_TYPE_OFFSET_14(type))
#define BSW_CANNM_NM_TYPE_OFFSET_14(type)   ((BSW_CANNM_NM_TYPE(14)  == BSW_CANNM_NMTYPE_##type) ? 14U  : BSW_CANNM_NM_TYPE_OFFSET_15(type))
#define BSW_CANNM_NM_TYPE_OFFSET_15(type)   ((BSW_CANNM_NM_TYPE(15)  == BSW_CANNM_NMTYPE_##type) ? 15U  : BSW_CANNM_NM_TYPE_OFFSET_16(type))
#define BSW_CANNM_NM_TYPE_OFFSET_16(type)   ((BSW_CANNM_NM_TYPE(16)  == BSW_CANNM_NMTYPE_##type) ? 16U  : BSW_CANNM_NM_TYPE_OFFSET_17(type))
#define BSW_CANNM_NM_TYPE_OFFSET_17(type)   ((BSW_CANNM_NM_TYPE(17)  == BSW_CANNM_NMTYPE_##type) ? 17U  : BSW_CANNM_NM_TYPE_OFFSET_18(type))
#define BSW_CANNM_NM_TYPE_OFFSET_18(type)   ((BSW_CANNM_NM_TYPE(18)  == BSW_CANNM_NMTYPE_##type) ? 18U  : BSW_CANNM_NM_TYPE_OFFSET_19(type))
#define BSW_CANNM_NM_TYPE_OFFSET_19(type)   ((BSW_CANNM_NM_TYPE(19)  == BSW_CANNM_NMTYPE_##type) ? 19U  : BSW_CANNM_NM_TYPE_OFFSET_20(type))
#define BSW_CANNM_NM_TYPE_OFFSET_20(type)   ((BSW_CANNM_NM_TYPE(20)  == BSW_CANNM_NMTYPE_##type) ? 20U  : BSW_CANNM_NM_TYPE_OFFSET_21(type))
#define BSW_CANNM_NM_TYPE_OFFSET_21(type)   ((BSW_CANNM_NM_TYPE(21)  == BSW_CANNM_NMTYPE_##type) ? 21U  : BSW_CANNM_NM_TYPE_OFFSET_22(type))
#define BSW_CANNM_NM_TYPE_OFFSET_22(type)   ((BSW_CANNM_NM_TYPE(22)  == BSW_CANNM_NMTYPE_##type) ? 22U  : BSW_CANNM_NM_TYPE_OFFSET_23(type))
#define BSW_CANNM_NM_TYPE_OFFSET_23(type)   ((BSW_CANNM_NM_TYPE(23)  == BSW_CANNM_NMTYPE_##type) ? 23U  : BSW_CANNM_NM_TYPE_OFFSET_24(type))
#define BSW_CANNM_NM_TYPE_OFFSET_24(type)   ((BSW_CANNM_NM_TYPE(24)  == BSW_CANNM_NMTYPE_##type) ? 24U  : BSW_CANNM_NM_TYPE_OFFSET_25(type))
#define BSW_CANNM_NM_TYPE_OFFSET_25(type)   ((BSW_CANNM_NM_TYPE(25)  == BSW_CANNM_NMTYPE_##type) ? 25U  : BSW_CANNM_NM_TYPE_OFFSET_26(type))
#define BSW_CANNM_NM_TYPE_OFFSET_26(type)   ((BSW_CANNM_NM_TYPE(26)  == BSW_CANNM_NMTYPE_##type) ? 26U  : BSW_CANNM_NM_TYPE_OFFSET_27(type))
#define BSW_CANNM_NM_TYPE_OFFSET_27(type)   ((BSW_CANNM_NM_TYPE(27)  == BSW_CANNM_NMTYPE_##type) ? 27U  : BSW_CANNM_NM_TYPE_OFFSET_28(type))
#define BSW_CANNM_NM_TYPE_OFFSET_28(type)   ((BSW_CANNM_NM_TYPE(28)  == BSW_CANNM_NMTYPE_##type) ? 28U  : BSW_CANNM_NM_TYPE_OFFSET_29(type))
#define BSW_CANNM_NM_TYPE_OFFSET_29(type)   ((BSW_CANNM_NM_TYPE(29)  == BSW_CANNM_NMTYPE_##type) ? 29U  : BSW_CANNM_NM_TYPE_OFFSET_30(type))
#define BSW_CANNM_NM_TYPE_OFFSET_30(type)   ((BSW_CANNM_NM_TYPE(30)  == BSW_CANNM_NMTYPE_##type) ? 30U  : BSW_CANNM_NM_TYPE_OFFSET_31(type))
#define BSW_CANNM_NM_TYPE_OFFSET_31(type)   ((BSW_CANNM_NM_TYPE(31)  == BSW_CANNM_NMTYPE_##type) ? 31U  : BSW_CANNM_OFFSET_NONE)

/* Macro for getting the network handle count for each bus type */
/* The argument type should be set according to the protocol type */
/* -------------------------------------------- */
/* Protocols         | Setting value                  */
/* -------------------------------------------- */
/* Can Nm/A           | A                       */
/* CanNm              | A2                      */
/* Can Nm/B           | B                       */
/* Can Nm/C2          | C2                      */
/* Can Nm/E           | E                       */
/* Can Nm/X           | X                       */
/* Can Nm/Y           | Y                       */
/* NM without NM           | Z                       */
/* None               | NONE                    */
/* -------------------------------------------- */
#define BSW_CANNM_NM_TYPE_CHNUM(type)       (BSW_CANNM_NM_TYPE_CHNUM_0_3(type) + BSW_CANNM_NM_TYPE_CHNUM_4_7(type) + BSW_CANNM_NM_TYPE_CHNUM_8_11(type) + BSW_CANNM_NM_TYPE_CHNUM_12_15(type)\
                                           + BSW_CANNM_NM_TYPE_CHNUM_16_19(type) + BSW_CANNM_NM_TYPE_CHNUM_20_23(type) + BSW_CANNM_NM_TYPE_CHNUM_24_27(type) + BSW_CANNM_NM_TYPE_CHNUM_28_31(type))
#define BSW_CANNM_NM_TYPE_CHNUM_CH(ch,type) ((BSW_CANNM_NM_TYPE(ch)  == BSW_CANNM_NMTYPE_##type) ? 1U  : 0U)
#define BSW_CANNM_NM_TYPE_CHNUM_0_3(type)   (BSW_CANNM_NM_TYPE_CHNUM_CH(0,type) + BSW_CANNM_NM_TYPE_CHNUM_CH(1,type) + BSW_CANNM_NM_TYPE_CHNUM_CH(2,type) + BSW_CANNM_NM_TYPE_CHNUM_CH(3,type))
#define BSW_CANNM_NM_TYPE_CHNUM_4_7(type)   (BSW_CANNM_NM_TYPE_CHNUM_CH(4,type) + BSW_CANNM_NM_TYPE_CHNUM_CH(5,type) + BSW_CANNM_NM_TYPE_CHNUM_CH(6,type) + BSW_CANNM_NM_TYPE_CHNUM_CH(7,type))
#define BSW_CANNM_NM_TYPE_CHNUM_8_11(type)  (BSW_CANNM_NM_TYPE_CHNUM_CH(8,type) + BSW_CANNM_NM_TYPE_CHNUM_CH(9,type) + BSW_CANNM_NM_TYPE_CHNUM_CH(10,type) + BSW_CANNM_NM_TYPE_CHNUM_CH(11,type))
#define BSW_CANNM_NM_TYPE_CHNUM_12_15(type) (BSW_CANNM_NM_TYPE_CHNUM_CH(12,type) + BSW_CANNM_NM_TYPE_CHNUM_CH(13,type) + BSW_CANNM_NM_TYPE_CHNUM_CH(14,type) + BSW_CANNM_NM_TYPE_CHNUM_CH(15,type))
#define BSW_CANNM_NM_TYPE_CHNUM_16_19(type) (BSW_CANNM_NM_TYPE_CHNUM_CH(16,type) + BSW_CANNM_NM_TYPE_CHNUM_CH(17,type) + BSW_CANNM_NM_TYPE_CHNUM_CH(18,type) + BSW_CANNM_NM_TYPE_CHNUM_CH(19,type))
#define BSW_CANNM_NM_TYPE_CHNUM_20_23(type) (BSW_CANNM_NM_TYPE_CHNUM_CH(20,type) + BSW_CANNM_NM_TYPE_CHNUM_CH(21,type) + BSW_CANNM_NM_TYPE_CHNUM_CH(22,type) + BSW_CANNM_NM_TYPE_CHNUM_CH(23,type))
#define BSW_CANNM_NM_TYPE_CHNUM_24_27(type) (BSW_CANNM_NM_TYPE_CHNUM_CH(24,type) + BSW_CANNM_NM_TYPE_CHNUM_CH(25,type) + BSW_CANNM_NM_TYPE_CHNUM_CH(26,type) + BSW_CANNM_NM_TYPE_CHNUM_CH(27,type))
#define BSW_CANNM_NM_TYPE_CHNUM_28_31(type) (BSW_CANNM_NM_TYPE_CHNUM_CH(28,type) + BSW_CANNM_NM_TYPE_CHNUM_CH(29,type) + BSW_CANNM_NM_TYPE_CHNUM_CH(30,type) + BSW_CANNM_NM_TYPE_CHNUM_CH(31,type))

/* Macro to get the bus sleep enable/disable for each channel       */
/* The argument ch is a relative channel number in the CAN protocol    */
#define BSW_CANNM_BUSSLEEP_USE(ch)          (BSW_CANNM_BUSSLEEP_USE_0(ch))
#define BSW_CANNM_BUSSLEEP_USE_0(ch)        ((BSW_CANNM_NETWORK_HANDLE(ch) == 0U)  ? BSW_COMM_SLPWKUP_USE(0)  : BSW_CANNM_BUSSLEEP_USE_1(ch))
#define BSW_CANNM_BUSSLEEP_USE_1(ch)        ((BSW_CANNM_NETWORK_HANDLE(ch) == 1U)  ? BSW_COMM_SLPWKUP_USE(1)  : BSW_CANNM_BUSSLEEP_USE_2(ch))
#define BSW_CANNM_BUSSLEEP_USE_2(ch)        ((BSW_CANNM_NETWORK_HANDLE(ch) == 2U)  ? BSW_COMM_SLPWKUP_USE(2)  : BSW_CANNM_BUSSLEEP_USE_3(ch))
#define BSW_CANNM_BUSSLEEP_USE_3(ch)        ((BSW_CANNM_NETWORK_HANDLE(ch) == 3U)  ? BSW_COMM_SLPWKUP_USE(3)  : BSW_CANNM_BUSSLEEP_USE_4(ch))
#define BSW_CANNM_BUSSLEEP_USE_4(ch)        ((BSW_CANNM_NETWORK_HANDLE(ch) == 4U)  ? BSW_COMM_SLPWKUP_USE(4)  : BSW_CANNM_BUSSLEEP_USE_5(ch))
#define BSW_CANNM_BUSSLEEP_USE_5(ch)        ((BSW_CANNM_NETWORK_HANDLE(ch) == 5U)  ? BSW_COMM_SLPWKUP_USE(5)  : BSW_CANNM_BUSSLEEP_USE_6(ch))
#define BSW_CANNM_BUSSLEEP_USE_6(ch)        ((BSW_CANNM_NETWORK_HANDLE(ch) == 6U)  ? BSW_COMM_SLPWKUP_USE(6)  : BSW_CANNM_BUSSLEEP_USE_7(ch))
#define BSW_CANNM_BUSSLEEP_USE_7(ch)        ((BSW_CANNM_NETWORK_HANDLE(ch) == 7U)  ? BSW_COMM_SLPWKUP_USE(7)  : BSW_CANNM_BUSSLEEP_USE_8(ch))
#define BSW_CANNM_BUSSLEEP_USE_8(ch)        ((BSW_CANNM_NETWORK_HANDLE(ch) == 8U)  ? BSW_COMM_SLPWKUP_USE(8)  : BSW_CANNM_BUSSLEEP_USE_9(ch))
#define BSW_CANNM_BUSSLEEP_USE_9(ch)        ((BSW_CANNM_NETWORK_HANDLE(ch) == 9U)  ? BSW_COMM_SLPWKUP_USE(9)  : BSW_CANNM_BUSSLEEP_USE_10(ch))
#define BSW_CANNM_BUSSLEEP_USE_10(ch)       ((BSW_CANNM_NETWORK_HANDLE(ch) == 10U) ? BSW_COMM_SLPWKUP_USE(10) : BSW_CANNM_BUSSLEEP_USE_11(ch))
#define BSW_CANNM_BUSSLEEP_USE_11(ch)       ((BSW_CANNM_NETWORK_HANDLE(ch) == 11U) ? BSW_COMM_SLPWKUP_USE(11) : BSW_CANNM_BUSSLEEP_USE_12(ch))
#define BSW_CANNM_BUSSLEEP_USE_12(ch)       ((BSW_CANNM_NETWORK_HANDLE(ch) == 12U) ? BSW_COMM_SLPWKUP_USE(12) : BSW_CANNM_BUSSLEEP_USE_13(ch))
#define BSW_CANNM_BUSSLEEP_USE_13(ch)       ((BSW_CANNM_NETWORK_HANDLE(ch) == 13U) ? BSW_COMM_SLPWKUP_USE(13) : BSW_CANNM_BUSSLEEP_USE_14(ch))
#define BSW_CANNM_BUSSLEEP_USE_14(ch)       ((BSW_CANNM_NETWORK_HANDLE(ch) == 14U) ? BSW_COMM_SLPWKUP_USE(14) : BSW_CANNM_BUSSLEEP_USE_15(ch))
#define BSW_CANNM_BUSSLEEP_USE_15(ch)       ((BSW_CANNM_NETWORK_HANDLE(ch) == 15U) ? BSW_COMM_SLPWKUP_USE(15) : BSW_CANNM_BUSSLEEP_USE_16(ch))
#define BSW_CANNM_BUSSLEEP_USE_16(ch)       ((BSW_CANNM_NETWORK_HANDLE(ch) == 16U) ? BSW_COMM_SLPWKUP_USE(16) : BSW_CANNM_BUSSLEEP_USE_17(ch))
#define BSW_CANNM_BUSSLEEP_USE_17(ch)       ((BSW_CANNM_NETWORK_HANDLE(ch) == 17U) ? BSW_COMM_SLPWKUP_USE(17) : BSW_CANNM_BUSSLEEP_USE_18(ch))
#define BSW_CANNM_BUSSLEEP_USE_18(ch)       ((BSW_CANNM_NETWORK_HANDLE(ch) == 18U) ? BSW_COMM_SLPWKUP_USE(18) : BSW_CANNM_BUSSLEEP_USE_19(ch))
#define BSW_CANNM_BUSSLEEP_USE_19(ch)       ((BSW_CANNM_NETWORK_HANDLE(ch) == 19U) ? BSW_COMM_SLPWKUP_USE(19) : BSW_CANNM_BUSSLEEP_USE_20(ch))
#define BSW_CANNM_BUSSLEEP_USE_20(ch)       ((BSW_CANNM_NETWORK_HANDLE(ch) == 20U) ? BSW_COMM_SLPWKUP_USE(20) : BSW_CANNM_BUSSLEEP_USE_21(ch))
#define BSW_CANNM_BUSSLEEP_USE_21(ch)       ((BSW_CANNM_NETWORK_HANDLE(ch) == 21U) ? BSW_COMM_SLPWKUP_USE(21) : BSW_CANNM_BUSSLEEP_USE_22(ch))
#define BSW_CANNM_BUSSLEEP_USE_22(ch)       ((BSW_CANNM_NETWORK_HANDLE(ch) == 22U) ? BSW_COMM_SLPWKUP_USE(22) : BSW_CANNM_BUSSLEEP_USE_23(ch))
#define BSW_CANNM_BUSSLEEP_USE_23(ch)       ((BSW_CANNM_NETWORK_HANDLE(ch) == 23U) ? BSW_COMM_SLPWKUP_USE(23) : BSW_CANNM_BUSSLEEP_USE_24(ch))
#define BSW_CANNM_BUSSLEEP_USE_24(ch)       ((BSW_CANNM_NETWORK_HANDLE(ch) == 24U) ? BSW_COMM_SLPWKUP_USE(24) : BSW_CANNM_BUSSLEEP_USE_25(ch))
#define BSW_CANNM_BUSSLEEP_USE_25(ch)       ((BSW_CANNM_NETWORK_HANDLE(ch) == 25U) ? BSW_COMM_SLPWKUP_USE(25) : BSW_CANNM_BUSSLEEP_USE_26(ch))
#define BSW_CANNM_BUSSLEEP_USE_26(ch)       ((BSW_CANNM_NETWORK_HANDLE(ch) == 26U) ? BSW_COMM_SLPWKUP_USE(26) : BSW_CANNM_BUSSLEEP_USE_27(ch))
#define BSW_CANNM_BUSSLEEP_USE_27(ch)       ((BSW_CANNM_NETWORK_HANDLE(ch) == 27U) ? BSW_COMM_SLPWKUP_USE(27) : BSW_CANNM_BUSSLEEP_USE_28(ch))
#define BSW_CANNM_BUSSLEEP_USE_28(ch)       ((BSW_CANNM_NETWORK_HANDLE(ch) == 28U) ? BSW_COMM_SLPWKUP_USE(28) : BSW_CANNM_BUSSLEEP_USE_29(ch))
#define BSW_CANNM_BUSSLEEP_USE_29(ch)       ((BSW_CANNM_NETWORK_HANDLE(ch) == 29U) ? BSW_COMM_SLPWKUP_USE(29) : BSW_CANNM_BUSSLEEP_USE_30(ch))
#define BSW_CANNM_BUSSLEEP_USE_30(ch)       ((BSW_CANNM_NETWORK_HANDLE(ch) == 30U) ? BSW_COMM_SLPWKUP_USE(30) : BSW_CANNM_BUSSLEEP_USE_31(ch))
#define BSW_CANNM_BUSSLEEP_USE_31(ch)       ((BSW_CANNM_NETWORK_HANDLE(ch) == 31U) ? BSW_COMM_SLPWKUP_USE(31) : BSW_NOUSE )

/* Use/unuse macro for NM message notification function */
#define BSW_CANNM_COMIF_USE         (BSW_CANNM_COMIF_USE_0)
#define BSW_CANNM_COMIF_USE_0       ((BSW_CANNM_CFG_COMIF_CH0  == BSW_USE) ? BSW_USE : BSW_CANNM_COMIF_USE_1)
#define BSW_CANNM_COMIF_USE_1       ((BSW_CANNM_CFG_COMIF_CH1  == BSW_USE) ? BSW_USE : BSW_CANNM_COMIF_USE_2)
#define BSW_CANNM_COMIF_USE_2       ((BSW_CANNM_CFG_COMIF_CH2  == BSW_USE) ? BSW_USE : BSW_CANNM_COMIF_USE_3)
#define BSW_CANNM_COMIF_USE_3       ((BSW_CANNM_CFG_COMIF_CH3  == BSW_USE) ? BSW_USE : BSW_CANNM_COMIF_USE_4)
#define BSW_CANNM_COMIF_USE_4       ((BSW_CANNM_CFG_COMIF_CH4  == BSW_USE) ? BSW_USE : BSW_CANNM_COMIF_USE_5)
#define BSW_CANNM_COMIF_USE_5       ((BSW_CANNM_CFG_COMIF_CH5  == BSW_USE) ? BSW_USE : BSW_CANNM_COMIF_USE_6)
#define BSW_CANNM_COMIF_USE_6       ((BSW_CANNM_CFG_COMIF_CH6  == BSW_USE) ? BSW_USE : BSW_CANNM_COMIF_USE_7)
#define BSW_CANNM_COMIF_USE_7       ((BSW_CANNM_CFG_COMIF_CH7  == BSW_USE) ? BSW_USE : BSW_CANNM_COMIF_USE_8)
#define BSW_CANNM_COMIF_USE_8       ((BSW_CANNM_CFG_COMIF_CH8  == BSW_USE) ? BSW_USE : BSW_CANNM_COMIF_USE_9)
#define BSW_CANNM_COMIF_USE_9       ((BSW_CANNM_CFG_COMIF_CH9  == BSW_USE) ? BSW_USE : BSW_CANNM_COMIF_USE_10)
#define BSW_CANNM_COMIF_USE_10      ((BSW_CANNM_CFG_COMIF_CH10 == BSW_USE) ? BSW_USE : BSW_CANNM_COMIF_USE_11)
#define BSW_CANNM_COMIF_USE_11      ((BSW_CANNM_CFG_COMIF_CH11 == BSW_USE) ? BSW_USE : BSW_CANNM_COMIF_USE_12)
#define BSW_CANNM_COMIF_USE_12      ((BSW_CANNM_CFG_COMIF_CH12 == BSW_USE) ? BSW_USE : BSW_CANNM_COMIF_USE_13)
#define BSW_CANNM_COMIF_USE_13      ((BSW_CANNM_CFG_COMIF_CH13 == BSW_USE) ? BSW_USE : BSW_CANNM_COMIF_USE_14)
#define BSW_CANNM_COMIF_USE_14      ((BSW_CANNM_CFG_COMIF_CH14 == BSW_USE) ? BSW_USE : BSW_CANNM_COMIF_USE_15)
#define BSW_CANNM_COMIF_USE_15      ((BSW_CANNM_CFG_COMIF_CH15 == BSW_USE) ? BSW_USE : BSW_CANNM_COMIF_USE_16)
#define BSW_CANNM_COMIF_USE_16      ((BSW_CANNM_CFG_COMIF_CH16 == BSW_USE) ? BSW_USE : BSW_CANNM_COMIF_USE_17)
#define BSW_CANNM_COMIF_USE_17      ((BSW_CANNM_CFG_COMIF_CH17 == BSW_USE) ? BSW_USE : BSW_CANNM_COMIF_USE_18)
#define BSW_CANNM_COMIF_USE_18      ((BSW_CANNM_CFG_COMIF_CH18 == BSW_USE) ? BSW_USE : BSW_CANNM_COMIF_USE_19)
#define BSW_CANNM_COMIF_USE_19      ((BSW_CANNM_CFG_COMIF_CH19 == BSW_USE) ? BSW_USE : BSW_CANNM_COMIF_USE_20)
#define BSW_CANNM_COMIF_USE_20      ((BSW_CANNM_CFG_COMIF_CH20 == BSW_USE) ? BSW_USE : BSW_CANNM_COMIF_USE_21)
#define BSW_CANNM_COMIF_USE_21      ((BSW_CANNM_CFG_COMIF_CH21 == BSW_USE) ? BSW_USE : BSW_CANNM_COMIF_USE_22)
#define BSW_CANNM_COMIF_USE_22      ((BSW_CANNM_CFG_COMIF_CH22 == BSW_USE) ? BSW_USE : BSW_CANNM_COMIF_USE_23)
#define BSW_CANNM_COMIF_USE_23      ((BSW_CANNM_CFG_COMIF_CH23 == BSW_USE) ? BSW_USE : BSW_CANNM_COMIF_USE_24)
#define BSW_CANNM_COMIF_USE_24      ((BSW_CANNM_CFG_COMIF_CH24 == BSW_USE) ? BSW_USE : BSW_CANNM_COMIF_USE_25)
#define BSW_CANNM_COMIF_USE_25      ((BSW_CANNM_CFG_COMIF_CH25 == BSW_USE) ? BSW_USE : BSW_CANNM_COMIF_USE_26)
#define BSW_CANNM_COMIF_USE_26      ((BSW_CANNM_CFG_COMIF_CH26 == BSW_USE) ? BSW_USE : BSW_CANNM_COMIF_USE_27)
#define BSW_CANNM_COMIF_USE_27      ((BSW_CANNM_CFG_COMIF_CH27 == BSW_USE) ? BSW_USE : BSW_CANNM_COMIF_USE_28)
#define BSW_CANNM_COMIF_USE_28      ((BSW_CANNM_CFG_COMIF_CH28 == BSW_USE) ? BSW_USE : BSW_CANNM_COMIF_USE_29)
#define BSW_CANNM_COMIF_USE_29      ((BSW_CANNM_CFG_COMIF_CH29 == BSW_USE) ? BSW_USE : BSW_CANNM_COMIF_USE_30)
#define BSW_CANNM_COMIF_USE_30      ((BSW_CANNM_CFG_COMIF_CH30 == BSW_USE) ? BSW_USE : BSW_CANNM_COMIF_USE_31)
#define BSW_CANNM_COMIF_USE_31      ((BSW_CANNM_CFG_COMIF_CH31 == BSW_USE) ? BSW_USE : BSW_NOUSE)

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

#endif /* BSW_CANNM_CH_CONFIG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/04/27                                             */
/*  v1-0-1          :2018/09/18                                             */
/*  v1-1-0          :2018/12/13                                             */
/*  v1-2-0          :2019/07/15                                             */
/*  v2-0-0          :2021/12/02                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
