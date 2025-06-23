/* canif_pbcfg_c_v3-0-0                                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CANIF/PBCFG/CODE                                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>
#include "../inc/bsw_canif_MemMap.h"
#include <ComStack_Types.h>

#include <bswm_cs/bsw_bswm_cs.h>
#include <comm/bsw_comm.h>
#include "../../ComM/inc/bsw_comm_config.h"
#include "../../BswM_CS/inc/bsw_bswm_cs_config.h"
#if (BSW_BSWM_CS_FUNC_CANIF == BSW_USE)

#include <canif/bsw_canif.h>

#include "../inc/bsw_canif_st.h"
#include "../inc/bsw_canif_tx.h"
#include "../inc/bsw_canif_rx.h"
#include "../inc/bsw_canif_fs.h"
#include "CanIf_Cfg.h"
#include "../inc/bsw_canif_config.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

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
/******************************************/
/*                                        */
/* Tx L-PDU Table                         */
/*                                        */
/******************************************/
#if(BSW_CANIF_TXPDURPDUNUM != 0U)
BswConst Bsw_CanIf_TxPduTblType bsw_canif_stTxPduRPduTbl[BSW_CANIF_TXPDURPDUNUM] =
{
   /* CAN ID      , Channel             , Extend   , Send Queue                 */
     { 0x40000121UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE000 }  /* [0] AVN1S38_Tx_CDC_VCAN_BUS */
    ,{ 0x40000126UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE001 }  /* [1] AVN1S34_Tx_CDC_VCAN_BUS */
    ,{ 0x40000141UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE002 }  /* [2] AVN1SG7_Tx_CDC_VCAN_BUS */
    ,{ 0x4000014CUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE003 }  /* [3] AVN1S71_Tx_CDC_VCAN_BUS */
    ,{ 0x4000017FUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE004 }  /* [4] AVN1S32_Tx_CDC_VCAN_BUS */
    ,{ 0x40000185UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE005 }  /* [5] AVN1SD4_Tx_CDC_VCAN_BUS */
    ,{ 0x400001A1UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE006 }  /* [6] AVN1SD6_Tx_CDC_VCAN_BUS */
    ,{ 0x400001A2UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE006 }  /* [7] AVN1SD7_Tx_CDC_VCAN_BUS */
    ,{ 0x400001A3UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE006 }  /* [8] AVN1SF6_Tx_CDC_VCAN_BUS */
    ,{ 0x400001A5UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE006 }  /* [9] AVN1SF4_Tx_CDC_VCAN_BUS */
    ,{ 0x400001A7UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE006 }  /* [10] AVN1SF5_Tx_CDC_VCAN_BUS */
    ,{ 0x400001A8UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE006 }  /* [11] AVN1SE9_Tx_CDC_VCAN_BUS */
    ,{ 0x400001A9UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE006 }  /* [12] AVN1SF1_Tx_CDC_VCAN_BUS */
    ,{ 0x400001ABUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE006 }  /* [13] AVN1SF2_Tx_CDC_VCAN_BUS */
    ,{ 0x400001ACUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE006 }  /* [14] AVN1SF3_Tx_CDC_VCAN_BUS */
    ,{ 0x400001ADUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE006 }  /* [15] AVN1SE3_Tx_CDC_VCAN_BUS */
    ,{ 0x400001AEUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE006 }  /* [16] AVN1SE8_Tx_CDC_VCAN_BUS */
    ,{ 0x400001AFUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE006 }  /* [17] AVN1SE4_Tx_CDC_VCAN_BUS */
    ,{ 0x400001B0UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE006 }  /* [18] AVN1SE5_Tx_CDC_VCAN_BUS */
    ,{ 0x400001B3UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE006 }  /* [19] AVN1SE6_Tx_CDC_VCAN_BUS */
    ,{ 0x400001B4UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE006 }  /* [20] AVN1SE7_Tx_CDC_VCAN_BUS */
    ,{ 0x400001B5UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE006 }  /* [21] AVN1SE2_Tx_CDC_VCAN_BUS */
    ,{ 0x400001B7UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE006 }  /* [22] AVN1SE1_Tx_CDC_VCAN_BUS */
    ,{ 0x400001B8UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE006 }  /* [23] AVN1SD8_Tx_CDC_VCAN_BUS */
    ,{ 0x400001B9UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE006 }  /* [24] AVN1SD9_Tx_CDC_VCAN_BUS */
    ,{ 0x400001BDUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE007 }  /* [25] AVN1S52_Tx_CDC_VCAN_BUS */
    ,{ 0x400001ECUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE008 }  /* [26] AVN1SA6_Tx_CDC_VCAN_BUS */
    ,{ 0x400001F2UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE009 }  /* [27] AVN1SB9_Tx_CDC_VCAN_BUS */
    ,{ 0x400001FCUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE010 }  /* [28] AVN1S40_Tx_CDC_VCAN_BUS */
    ,{ 0x400001FDUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE010 }  /* [29] AVN1S41_Tx_CDC_VCAN_BUS */
    ,{ 0x400001FEUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE010 }  /* [30] AVN1S42_Tx_CDC_VCAN_BUS */
    ,{ 0x400001FFUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE010 }  /* [31] AVN1S43_Tx_CDC_VCAN_BUS */
    ,{ 0x400002AAUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE011 }  /* [32] AVN1S73_Tx_CDC_VCAN_BUS */
    ,{ 0x400002D2UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE012 }  /* [33] AVN1SB7_Tx_CDC_VCAN_BUS */
    ,{ 0x400002D3UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE013 }  /* [34] AVN1SB8_Tx_CDC_VCAN_BUS */
    ,{ 0x400002D4UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE012 }  /* [35] AVN1SC1_Tx_CDC_VCAN_BUS */
    ,{ 0x400002D5UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE012 }  /* [36] AVN1SC2_Tx_CDC_VCAN_BUS */
    ,{ 0x400002D6UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE012 }  /* [37] AVN1SC3_Tx_CDC_VCAN_BUS */
    ,{ 0x400002D7UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE012 }  /* [38] AVN1SC4_Tx_CDC_VCAN_BUS */
    ,{ 0x400002DFUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE012 }  /* [39] AVN1SC5_Tx_CDC_VCAN_BUS */
    ,{ 0x400002E0UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE014 }  /* [40] AVN1SC6_Tx_CDC_VCAN_BUS */
    ,{ 0x400002E1UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE014 }  /* [41] AVN1SC7_Tx_CDC_VCAN_BUS */
    ,{ 0x400002E2UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE014 }  /* [42] AVN1SC8_Tx_CDC_VCAN_BUS */
    ,{ 0x400002E3UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE015 }  /* [43] AVN1SH1_Tx_CDC_VCAN_BUS */
    ,{ 0x400002EFUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE014 }  /* [44] AVN1SC9_Tx_CDC_VCAN_BUS */
    ,{ 0x400002F0UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE014 }  /* [45] AVN1SD1_Tx_CDC_VCAN_BUS */
    ,{ 0x400002F2UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE014 }  /* [46] AVN1SD2_Tx_CDC_VCAN_BUS */
    ,{ 0x400002F5UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE014 }  /* [47] AVN1SD3_Tx_CDC_VCAN_BUS */
    ,{ 0x400002F6UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE016 }  /* [48] AVN1SD5_Tx_CDC_VCAN_BUS */
    ,{ 0x400002F7UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE015 }  /* [49] AVN1SF7_Tx_CDC_VCAN_BUS */
    ,{ 0x400002F8UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE014 }  /* [50] AVN1SF8_Tx_CDC_VCAN_BUS */
    ,{ 0x400002FAUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE014 }  /* [51] AVN1SF9_Tx_CDC_VCAN_BUS */
    ,{ 0x4000030EUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE017 }  /* [52] AVN1S67_Tx_CDC_VCAN_BUS */
    ,{ 0x4000030FUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE017 }  /* [53] AVN1S68_Tx_CDC_VCAN_BUS */
    ,{ 0x40000313UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE017 }  /* [54] AVN1SB2_Tx_CDC_VCAN_BUS */
    ,{ 0x40000315UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE018 }  /* [55] MET1S33_Tx_CDC_VCAN_BUS */
    ,{ 0x4000031AUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE017 }  /* [56] AVN1S30_Tx_CDC_VCAN_BUS */
    ,{ 0x4000031DUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE017 }  /* [57] AVN1SA1_Tx_CDC_VCAN_BUS */
    ,{ 0x40000322UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE019 }  /* [58] AVN1SG4_Tx_CDC_VCAN_BUS */
    ,{ 0x4000033AUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE020 }  /* [59] AVN1SG3_Tx_CDC_VCAN_BUS */
    ,{ 0x40000345UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE021 }  /* [60] AVN1S94_Tx_CDC_VCAN_BUS */
    ,{ 0x40000346UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE021 }  /* [61] AVN1S95_Tx_CDC_VCAN_BUS */
    ,{ 0x40000351UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE021 }  /* [62] CDC1S04_Tx_CDC_VCAN_BUS */
    ,{ 0x4000035AUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE022 }  /* [63] AVN1SA7_Tx_CDC_VCAN_BUS */
    ,{ 0x4000035BUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE022 }  /* [64] AVN1S62_Tx_CDC_VCAN_BUS */
    ,{ 0x40000384UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE023 }  /* [65] AVN1S01_Tx_CDC_VCAN_BUS */
    ,{ 0x40000386UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE023 }  /* [66] AVN1S03_Tx_CDC_VCAN_BUS */
    ,{ 0x40000387UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE024 }  /* [67] AVN1S05_Tx_CDC_VCAN_BUS */
    ,{ 0x40000388UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE024 }  /* [68] AVN1S06_Tx_CDC_VCAN_BUS */
    ,{ 0x40000389UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE024 }  /* [69] AVN1S08_Tx_CDC_VCAN_BUS */
    ,{ 0x4000038EUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE024 }  /* [70] AVN1S04_Tx_CDC_VCAN_BUS */
    ,{ 0x4000038FUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE024 }  /* [71] AVN1S07_Tx_CDC_VCAN_BUS */
    ,{ 0x400003A6UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE025 }  /* [72] AVN1S46_Tx_CDC_VCAN_BUS */
    ,{ 0x400003A7UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE025 }  /* [73] AVN1S47_Tx_CDC_VCAN_BUS */
    ,{ 0x400003A8UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE025 }  /* [74] AVN1S70_Tx_CDC_VCAN_BUS */
    ,{ 0x400003C0UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE026 }  /* [75] AVN1S99_Tx_CDC_VCAN_BUS */
    ,{ 0x400003C2UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE027 }  /* [76] AVN1SA9_Tx_CDC_VCAN_BUS */
    ,{ 0x400003C4UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE027 }  /* [77] AVN1S78_Tx_CDC_VCAN_BUS */
    ,{ 0x400003C9UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE027 }  /* [78] AVN1S63_Tx_CDC_VCAN_BUS */
    ,{ 0x400003D0UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE027 }  /* [79] AVN1S76_Tx_CDC_VCAN_BUS */
    ,{ 0x400003D9UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE027 }  /* [80] AVN1S97_Tx_CDC_VCAN_BUS */
    ,{ 0x400003E4UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE028 }  /* [81] AVN1S98_Tx_CDC_VCAN_BUS */
    ,{ 0x400003E6UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE029 }  /* [82] AVN1S11_Tx_CDC_VCAN_BUS */
    ,{ 0x400003F1UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE029 }  /* [83] AVN1SA8_Tx_CDC_VCAN_BUS */
    ,{ 0x400003FDUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE028 }  /* [84] AVN1S77_Tx_CDC_VCAN_BUS */
    ,{ 0x4000040EUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE030 }  /* [85] AVN1SB1_Tx_CDC_VCAN_BUS */
    ,{ 0x4000042EUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE031 }  /* [86] AVN1S33_Tx_CDC_VCAN_BUS */
    ,{ 0x40000434UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE032 }  /* [87] AVN1S20_Tx_CDC_VCAN_BUS */
    ,{ 0x40000435UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE032 }  /* [88] AVN1S21_Tx_CDC_VCAN_BUS */
    ,{ 0x40000436UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE032 }  /* [89] AVN1S22_Tx_CDC_VCAN_BUS */
    ,{ 0x40000437UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE032 }  /* [90] AVN1S23_Tx_CDC_VCAN_BUS */
    ,{ 0x4000043EUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE033 }  /* [91] AVN1SG5_Tx_CDC_VCAN_BUS */
    ,{ 0x40000490UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE034 }  /* [92] AVN1S64_Tx_CDC_VCAN_BUS */
    ,{ 0x40000515UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE035 }  /* [93] AVN1SB3_Tx_CDC_VCAN_BUS */
    ,{ 0x4000051AUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE036 }  /* [94] AVN1SB4_Tx_CDC_VCAN_BUS */
    ,{ 0x4000051BUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE036 }  /* [95] AVN1SB5_Tx_CDC_VCAN_BUS */
    ,{ 0x4000051DUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE035 }  /* [96] AVN1S44_Tx_CDC_VCAN_BUS */
    ,{ 0x4000051FUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE035 }  /* [97] AVN1S65_Tx_CDC_VCAN_BUS */
    ,{ 0x40000521UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE037 }  /* [98] AVN1S69_Tx_CDC_VCAN_BUS */
    ,{ 0x4000052AUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE038 }  /* [99] AVN1S66_Tx_CDC_VCAN_BUS */
    ,{ 0x4000058AUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE039 }  /* [100] AVN1S39_Tx_CDC_VCAN_BUS */
    ,{ 0x4000060CUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE040 }  /* [101] AVN1SG6_Tx_CDC_VCAN_BUS */
};

#if(BSW_CANIF_CFG_METADATA_USE == BSW_CANIF_USE)
BswConst BswU4 bsw_canif_stTxPduRMskTbl[BSW_CANIF_TXPDURPDUNUM] =
{
   /* CAN-ID Mask */
};
#endif /* (BSW_CANIF_CFG_METADATA_USE == BSW_CANIF_USE) */
#endif /* (BSW_CANIF_TXPDURPDUNUM != 0U) */

#if(BSW_CANIF_TXCANNMPDUNUM != 0U)
BswConst Bsw_CanIf_TxPduTblType bsw_canif_stTxCanNmPduTbl[BSW_CANIF_TXCANNMPDUNUM] =
{
   /* CAN ID      , Channel             , Extend   , Send Queue                 */
     { 0x0000047EUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE000 }  /* [0] CDC1N02_Tx_CDC_VCAN_BUS */
};

#if(BSW_CANIF_CFG_METADATA_USE == BSW_CANIF_USE)
BswConst BswU4 bsw_canif_stTxCanNmMskTbl[BSW_CANIF_TXCANNMPDUNUM] =
{
   /* CAN-ID Mask */
};
#endif /* (BSW_CANIF_CFG_METADATA_USE == BSW_CANIF_USE) */
#endif /* (BSW_CANIF_TXCANNMPDUNUM != 0U) */

#if(BSW_CANIF_TXCANTPPDUNUM != 0U)
BswConst Bsw_CanIf_TxPduTblType bsw_canif_stTxCanTpPduTbl[BSW_CANIF_TXCANTPPDUNUM] =
{
   /* CAN ID      , Channel             , Extend   , Send Queue                 */
     { 0x98DAE01CUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE000 }  /* [0] Nsdu_TX_TxNPdu_Diag_Physical_Service */
    ,{ 0x98DAE11CUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE000 }  /* [1] Nsdu_TX_TxNPdu_Diag_Physical_Remote */
    ,{ 0xD8DAE01CUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE000 }  /* [2] Nsdu_TX_TxNPdu_Diag_Physical_FD_Service */
    ,{ 0xD8DAE11CUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE000 }  /* [3] Nsdu_TX_TxNPdu_Diag_Physical_FD_Remote */
};

#if(BSW_CANIF_CFG_METADATA_USE == BSW_CANIF_USE)
BswConst BswU4 bsw_canif_stTxCanTpMskTbl[BSW_CANIF_TXCANTPPDUNUM] =
{
   /* CAN-ID Mask */
};
#endif /* (BSW_CANIF_CFG_METADATA_USE == BSW_CANIF_USE) */
#endif /* (BSW_CANIF_TXCANTPPDUNUM != 0U) */

#if(BSW_CANIF_TXCDD1PDUNUM != 0U)
BswConst Bsw_CanIf_TxPduTblType bsw_canif_stTxCdd1PduTbl[BSW_CANIF_TXCDD1PDUNUM] =
{
   /* CAN ID      , Channel             , Extend   , Send Queue                 */
};

#if(BSW_CANIF_CFG_METADATA_USE == BSW_CANIF_USE)
BswConst BswU4 bsw_canif_stTxCdd1MskTbl[BSW_CANIF_TXCDD1PDUNUM] =
{
   /* CAN-ID Mask */
};
#endif /* (BSW_CANIF_CFG_METADATA_USE == BSW_CANIF_USE) */
#endif /* (BSW_CANIF_TXCDD1PDUNUM != 0U) */

#if(BSW_CANIF_TXCDD2PDUNUM != 0U)
BswConst Bsw_CanIf_TxPduTblType bsw_canif_stTxCdd2PduTbl[BSW_CANIF_TXCDD2PDUNUM] =
{
   /* CAN ID      , Channel             , Extend   , Send Queue                 */
};

#if(BSW_CANIF_CFG_METADATA_USE == BSW_CANIF_USE)
BswConst BswU4 bsw_canif_stTxCdd2MskTbl[BSW_CANIF_TXCDD2PDUNUM] =
{
   /* CAN-ID Mask */
};
#endif /* (BSW_CANIF_CFG_METADATA_USE == BSW_CANIF_USE) */
#endif /* (BSW_CANIF_TXCDD2PDUNUM != 0U) */

#if(BSW_CANIF_TXXCPPDUNUM != 0U)
BswConst Bsw_CanIf_TxPduTblType bsw_canif_stTxXcpPduTbl[BSW_CANIF_TXXCPPDUNUM] =
{
   /* CAN ID      , Channel             , Extend   , Send Queue                 */
};

#if(BSW_CANIF_CFG_METADATA_USE == BSW_CANIF_USE)
BswConst BswU4 bsw_canif_stTxXcpMskTbl[BSW_CANIF_TXXCPPDUNUM] =
{
   /* CAN-ID Mask */
};
#endif /* (BSW_CANIF_CFG_METADATA_USE == BSW_CANIF_USE) */
#endif /* (BSW_CANIF_TXXCPPDUNUM != 0U) */

/******************************************/
/*                                        */
/* Rx L-PDU Table                         */
/*                                        */
/******************************************/

#if(BSW_CANIF_RXPDURPDUNUM != 0U)
/* PduR Rx PDU ID Table */
BswConst Bsw_CanIf_RxPduTblType bsw_canif_stRxPduRPduTbl[BSW_CANIF_RXPDURPDUNUM] =
{
   /* CAN-ID      , DLC       , Channel             , Extend     */
     { 0x400004ACUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [0] ABG1D50_Rx_CDC_VCAN_BUS */
    ,{ 0x000004BCUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [1] ABG1D51_Rx_CDC_VCAN_BUS */
    ,{ 0x400003B1UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [2] ABG1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x400001D8UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [3] ABG1S04_Rx_CDC_VCAN_BUS */
    ,{ 0x400001D6UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [4] ABG1S09_Rx_CDC_VCAN_BUS */
    ,{ 0x400004B8UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [5] ACN1D50_Rx_CDC_VCAN_BUS */
    ,{ 0x400003A1UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [6] ACN1S03_Rx_CDC_VCAN_BUS */
    ,{ 0x40000381UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [7] ACN1S04_Rx_CDC_VCAN_BUS */
    ,{ 0x40000382UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [8] ACN1S05_Rx_CDC_VCAN_BUS */
    ,{ 0x400003B0UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [9] ACN1S07_Rx_CDC_VCAN_BUS */
    ,{ 0x40000407UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [10] ACN1S15_Rx_CDC_VCAN_BUS */
    ,{ 0x40000408UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [11] ACN1S16_Rx_CDC_VCAN_BUS */
    ,{ 0x40000354UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [12] ACN1S22_Rx_CDC_VCAN_BUS */
    ,{ 0x40000255UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [13] ACN1S25_Rx_CDC_VCAN_BUS */
    ,{ 0x40000506UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [14] ACN1S29_Rx_CDC_VCAN_BUS */
    ,{ 0x40000594UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [15] ADC1S06_Rx_CDC_VCAN_BUS */
    ,{ 0x40000207UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [16] ADC1S13_Rx_CDC_VCAN_BUS */
    ,{ 0x40000208UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [17] ADC1S14_Rx_CDC_VCAN_BUS */
    ,{ 0x40000209UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [18] ADC1S15_Rx_CDC_VCAN_BUS */
    ,{ 0x4000020AUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [19] ADC1S17_Rx_CDC_VCAN_BUS */
    ,{ 0x40000613UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [20] ADC1S19_Rx_CDC_VCAN_BUS */
    ,{ 0x400001C7UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [21] ADC1S20_Rx_CDC_VCAN_BUS */
    ,{ 0x4000020BUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [22] ADC1S23_Rx_CDC_VCAN_BUS */
    ,{ 0x40000144UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [23] ADC1S27_Rx_CDC_VCAN_BUS */
    ,{ 0x40000349UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [24] ADC1S30_Rx_CDC_VCAN_BUS */
    ,{ 0x400001C0UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [25] ADC1S31_Rx_CDC_VCAN_BUS */
    ,{ 0x40000247UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [26] ADU1S02_Rx_CDC_VCAN_BUS */
    ,{ 0x400001F5UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [27] ADU1S03_Rx_CDC_VCAN_BUS */
    ,{ 0x400001F0UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [28] ADU1S05_Rx_CDC_VCAN_BUS */
    ,{ 0x4000022EUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [29] ADU1S06_Rx_CDC_VCAN_BUS */
    ,{ 0x4000020EUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [30] ADU1S07_Rx_CDC_VCAN_BUS */
    ,{ 0x40000161UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [31] ADU1S18_Rx_CDC_VCAN_BUS */
    ,{ 0x40000162UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [32] ADU1S19_Rx_CDC_VCAN_BUS */
    ,{ 0x40000163UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [33] ADU1S20_Rx_CDC_VCAN_BUS */
    ,{ 0x40000166UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [34] ADU1S21_Rx_CDC_VCAN_BUS */
    ,{ 0x40000167UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [35] ADU1S22_Rx_CDC_VCAN_BUS */
    ,{ 0x40000168UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [36] ADU1S23_Rx_CDC_VCAN_BUS */
    ,{ 0x40000169UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [37] ADU1S24_Rx_CDC_VCAN_BUS */
    ,{ 0x4000016AUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [38] ADU1S25_Rx_CDC_VCAN_BUS */
    ,{ 0x4000016BUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [39] ADU1S26_Rx_CDC_VCAN_BUS */
    ,{ 0x4000016CUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [40] ADU1S27_Rx_CDC_VCAN_BUS */
    ,{ 0x4000016DUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [41] ADU1S28_Rx_CDC_VCAN_BUS */
    ,{ 0x40000072UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [42] ARS1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x400001DDUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [43] ARS1S90_Rx_CDC_VCAN_BUS */
    ,{ 0x40000214UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [44] BAT1E41_Rx_CDC_VCAN_BUS */
    ,{ 0x4000016EUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [45] BAT1E45_Rx_CDC_VCAN_BUS */
    ,{ 0x4000026EUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [46] BAT1ED1_Rx_CDC_VCAN_BUS */
    ,{ 0x400001BAUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [47] BAT1ED5_Rx_CDC_VCAN_BUS */
    ,{ 0x400001EFUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [48] BAT1EDA_Rx_CDC_VCAN_BUS */
    ,{ 0x40000272UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [49] BAT1EDB_Rx_CDC_VCAN_BUS */
    ,{ 0x400003E5UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [50] BAT1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x40000124UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [51] BAT1S08_Rx_CDC_VCAN_BUS */
    ,{ 0x40000155UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [52] BAT1S11_Rx_CDC_VCAN_BUS */
    ,{ 0x40000279UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [53] BAT2ED2_Rx_CDC_VCAN_BUS */
    ,{ 0x40000379UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [54] BCC1S05_Rx_CDC_VCAN_BUS */
    ,{ 0x400003F3UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [55] BCC1S06_Rx_CDC_VCAN_BUS */
    ,{ 0x4000038BUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [56] BDB1F01_Rx_CDC_VCAN_BUS */
    ,{ 0x4000038DUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [57] BDB1F02_Rx_CDC_VCAN_BUS */
    ,{ 0x400001F4UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [58] BDB1F03_Rx_CDC_VCAN_BUS */
    ,{ 0x400001CFUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [59] BDB1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x40000621UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [60] BDB1S02_Rx_CDC_VCAN_BUS */
    ,{ 0x40000622UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [61] BDB1S03_Rx_CDC_VCAN_BUS */
    ,{ 0x40000623UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [62] BDB1S04_Rx_CDC_VCAN_BUS */
    ,{ 0x40000380UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [63] BDB1S05_Rx_CDC_VCAN_BUS */
    ,{ 0x40000624UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [64] BDB1S08_Rx_CDC_VCAN_BUS */
    ,{ 0x40000626UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [65] BDB1S10_Rx_CDC_VCAN_BUS */
    ,{ 0x4000062CUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [66] BDB1S13_Rx_CDC_VCAN_BUS */
    ,{ 0x400003FCUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [67] BDB1S19_Rx_CDC_VCAN_BUS */
    ,{ 0x40000306UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [68] BDB1S25_Rx_CDC_VCAN_BUS */
    ,{ 0x40000305UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [69] BDB1S26_Rx_CDC_VCAN_BUS */
    ,{ 0x40000629UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [70] BDB1S27_Rx_CDC_VCAN_BUS */
    ,{ 0x4000062AUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [71] BDB1S28_Rx_CDC_VCAN_BUS */
    ,{ 0x40000397UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [72] BDB1S29_Rx_CDC_VCAN_BUS */
    ,{ 0x400003B5UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [73] BDB1S35_Rx_CDC_VCAN_BUS */
    ,{ 0x400003B8UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [74] BDB1S36_Rx_CDC_VCAN_BUS */
    ,{ 0x400004B9UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [75] BDC1D00_Rx_CDC_VCAN_BUS */
    ,{ 0x400004BAUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [76] BDC1D01_Rx_CDC_VCAN_BUS */
    ,{ 0x40000312UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [77] BDC1S13_Rx_CDC_VCAN_BUS */
    ,{ 0x40000320UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [78] BDC1S14_Rx_CDC_VCAN_BUS */
    ,{ 0x4000032AUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [79] BDC1S16_Rx_CDC_VCAN_BUS */
    ,{ 0x40000186UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [80] BDC1S30_Rx_CDC_VCAN_BUS */
    ,{ 0x400001D2UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [81] BDC1S33_Rx_CDC_VCAN_BUS */
    ,{ 0x4000009CUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [82] BDC1S40_Rx_CDC_VCAN_BUS */
    ,{ 0x40000148UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [83] BDC1S41_Rx_CDC_VCAN_BUS */
    ,{ 0x400001D3UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [84] BDC1S46_Rx_CDC_VCAN_BUS */
    ,{ 0x40000337UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [85] BDC1S48_Rx_CDC_VCAN_BUS */
    ,{ 0x40000013UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [86] BDC1S52_Rx_CDC_VCAN_BUS */
    ,{ 0x4000001BUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [87] BDC1S60_Rx_CDC_VCAN_BUS */
    ,{ 0x400001E3UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [88] BDC1S81_Rx_CDC_VCAN_BUS */
    ,{ 0x40000150UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [89] BDC1S82_Rx_CDC_VCAN_BUS */
    ,{ 0x40000367UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [90] BDC1S83_Rx_CDC_VCAN_BUS */
    ,{ 0x400001A0UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [91] BDC1S87_Rx_CDC_VCAN_BUS */
    ,{ 0x4000036CUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [92] BDC1S89_Rx_CDC_VCAN_BUS */
    ,{ 0x400001E4UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [93] BDC1S91_Rx_CDC_VCAN_BUS */
    ,{ 0x40000355UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [94] BDC1S97_Rx_CDC_VCAN_BUS */
    ,{ 0x40000358UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [95] BDC1S98_Rx_CDC_VCAN_BUS */
    ,{ 0x4000035DUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [96] BDC1S99_Rx_CDC_VCAN_BUS */
    ,{ 0x400001A4UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [97] BDC1SA0_Rx_CDC_VCAN_BUS */
    ,{ 0x4000035FUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [98] BDC1SA1_Rx_CDC_VCAN_BUS */
    ,{ 0x40000393UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [99] BDC1SC1_Rx_CDC_VCAN_BUS */
    ,{ 0x40000395UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [100] BDC1SC2_Rx_CDC_VCAN_BUS */
    ,{ 0x40000396UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [101] BDC1SC3_Rx_CDC_VCAN_BUS */
    ,{ 0x4000039AUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [102] BDC1SC4_Rx_CDC_VCAN_BUS */
    ,{ 0x4000039BUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [103] BDC1SC5_Rx_CDC_VCAN_BUS */
    ,{ 0x4000039DUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [104] BDC1SC6_Rx_CDC_VCAN_BUS */
    ,{ 0x4000039EUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [105] BDC1SC7_Rx_CDC_VCAN_BUS */
    ,{ 0x4000039FUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [106] BDC1SC8_Rx_CDC_VCAN_BUS */
    ,{ 0x400003A5UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [107] BDC1SC9_Rx_CDC_VCAN_BUS */
    ,{ 0x400003ACUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [108] BDC1SD1_Rx_CDC_VCAN_BUS */
    ,{ 0x400003AEUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [109] BDC1SD2_Rx_CDC_VCAN_BUS */
    ,{ 0x400003B2UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [110] BDC1SD3_Rx_CDC_VCAN_BUS */
    ,{ 0x400003B3UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [111] BDC1SD4_Rx_CDC_VCAN_BUS */
    ,{ 0x400003B9UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [112] BDC1SD5_Rx_CDC_VCAN_BUS */
    ,{ 0x400003BCUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [113] BDC1SD6_Rx_CDC_VCAN_BUS */
    ,{ 0x400003C6UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [114] BDC1SD7_Rx_CDC_VCAN_BUS */
    ,{ 0x400003C7UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [115] BDC1SD8_Rx_CDC_VCAN_BUS */
    ,{ 0x400003CDUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [116] BDC1SD9_Rx_CDC_VCAN_BUS */
    ,{ 0x400003D3UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [117] BDC1SE1_Rx_CDC_VCAN_BUS */
    ,{ 0x400003D6UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [118] BDC1SE2_Rx_CDC_VCAN_BUS */
    ,{ 0x400003DDUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [119] BDC1SE3_Rx_CDC_VCAN_BUS */
    ,{ 0x400003E1UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [120] BDC1SE4_Rx_CDC_VCAN_BUS */
    ,{ 0x400003EBUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [121] BDC1SE5_Rx_CDC_VCAN_BUS */
    ,{ 0x400003EFUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [122] BDC1SE6_Rx_CDC_VCAN_BUS */
    ,{ 0x400003F5UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [123] BDC1SE7_Rx_CDC_VCAN_BUS */
    ,{ 0x40000423UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [124] BDC1SE8_Rx_CDC_VCAN_BUS */
    ,{ 0x40000429UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [125] BDC1SE9_Rx_CDC_VCAN_BUS */
    ,{ 0x40000430UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [126] BDC1SF1_Rx_CDC_VCAN_BUS */
    ,{ 0x40000480UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [127] BDC1SF2_Rx_CDC_VCAN_BUS */
    ,{ 0x40000484UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [128] BDC1SF3_Rx_CDC_VCAN_BUS */
    ,{ 0x40000491UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [129] BDC1SF4_Rx_CDC_VCAN_BUS */
    ,{ 0x4000034EUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [130] BDC1SF5_Rx_CDC_VCAN_BUS */
    ,{ 0x40000497UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [131] BDC1SF6_Rx_CDC_VCAN_BUS */
    ,{ 0x40000526UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [132] BDC1SG4_Rx_CDC_VCAN_BUS */
    ,{ 0x4000052BUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [133] BDC1SG6_Rx_CDC_VCAN_BUS */
    ,{ 0x4000052CUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [134] BDC1SG7_Rx_CDC_VCAN_BUS */
    ,{ 0x40000530UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [135] BDC1SG8_Rx_CDC_VCAN_BUS */
    ,{ 0x40000531UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [136] BDC1SG9_Rx_CDC_VCAN_BUS */
    ,{ 0x40000534UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [137] BDC1SH3_Rx_CDC_VCAN_BUS */
    ,{ 0x40000535UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [138] BDC1SH4_Rx_CDC_VCAN_BUS */
    ,{ 0x40000537UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [139] BDC1SH5_Rx_CDC_VCAN_BUS */
    ,{ 0x40000538UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [140] BDC1SH6_Rx_CDC_VCAN_BUS */
    ,{ 0x400002B3UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [141] BDC1SH8_Rx_CDC_VCAN_BUS */
    ,{ 0x400003CEUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [142] BDC1SI0_Rx_CDC_VCAN_BUS */
    ,{ 0x400003E8UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [143] BDC1SI1_Rx_CDC_VCAN_BUS */
    ,{ 0x400003E9UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [144] BDC1SI2_Rx_CDC_VCAN_BUS */
    ,{ 0x400003F4UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [145] BDC1SI3_Rx_CDC_VCAN_BUS */
    ,{ 0x4000031EUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [146] BDC1SI4_Rx_CDC_VCAN_BUS */
    ,{ 0x4000031FUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [147] BDC1SI5_Rx_CDC_VCAN_BUS */
    ,{ 0x40000321UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [148] BDC1SI6_Rx_CDC_VCAN_BUS */
    ,{ 0x40000508UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [149] BDC1SI7_Rx_CDC_VCAN_BUS */
    ,{ 0x4000050BUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [150] BDC1SI8_Rx_CDC_VCAN_BUS */
    ,{ 0x4000050CUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [151] BDC1SI9_Rx_CDC_VCAN_BUS */
    ,{ 0x4000050EUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [152] BDC1SJ0_Rx_CDC_VCAN_BUS */
    ,{ 0x40000485UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [153] BDC1SJ1_Rx_CDC_VCAN_BUS */
    ,{ 0x4000050DUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [154] BDC1SJ2_Rx_CDC_VCAN_BUS */
    ,{ 0x40000536UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [155] BDC1SJ3_Rx_CDC_VCAN_BUS */
    ,{ 0x40000361UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [156] BDC1SJ4_Rx_CDC_VCAN_BUS */
    ,{ 0x40000378UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [157] BDC1SJ5_Rx_CDC_VCAN_BUS */
    ,{ 0x400003C3UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [158] BDC1SJ6_Rx_CDC_VCAN_BUS */
    ,{ 0x400003F2UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [159] BDC1SJ7_Rx_CDC_VCAN_BUS */
    ,{ 0x4000043CUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [160] BDC1SJ8_Rx_CDC_VCAN_BUS */
    ,{ 0x40000610UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [161] BDC1SV1_Rx_CDC_VCAN_BUS */
    ,{ 0x40000602UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [162] BDC1SV2_Rx_CDC_VCAN_BUS */
    ,{ 0x40000596UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [163] BDC1SV3_Rx_CDC_VCAN_BUS */
    ,{ 0x4000037BUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [164] BDF3S01_Rx_CDC_VCAN_BUS */
    ,{ 0x4000018DUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [165] BDF3S02_Rx_CDC_VCAN_BUS */
    ,{ 0x4000019AUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [166] BDR3S02_Rx_CDC_VCAN_BUS */
    ,{ 0x400003CBUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [167] BKD1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x400003ABUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [168] BKD1S02_Rx_CDC_VCAN_BUS */
    ,{ 0x400003F6UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [169] BSR1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x40000235UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [170] BSR1S02_Rx_CDC_VCAN_BUS */
    ,{ 0x400002AFUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [171] BSR1S03_Rx_CDC_VCAN_BUS */
    ,{ 0x40000333UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [172] CDC1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x400001D9UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [173] CMB1S03_Rx_CDC_VCAN_BUS */
    ,{ 0x400002F3UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [174] CMB1S04_Rx_CDC_VCAN_BUS */
    ,{ 0x400000A9UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [175] CSR1G10_Rx_CDC_VCAN_BUS */
    ,{ 0x4000043AUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [176] CSR1S04_Rx_CDC_VCAN_BUS */
    ,{ 0x400003DBUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [177] CSR1S07_Rx_CDC_VCAN_BUS */
    ,{ 0x400003DCUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [178] CSR1S08_Rx_CDC_VCAN_BUS */
    ,{ 0x40000438UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [179] DCM1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x4000034FUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [180] DCM1S03_Rx_CDC_VCAN_BUS */
    ,{ 0x40000363UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [181] DCM1S04_Rx_CDC_VCAN_BUS */
    ,{ 0x40000348UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [182] DCM1S08_Rx_CDC_VCAN_BUS */
    ,{ 0x4000027DUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [183] DDM1S00_Rx_CDC_VCAN_BUS */
    ,{ 0x4000012BUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [184] DDM1S09_Rx_CDC_VCAN_BUS */
    ,{ 0x400000B8UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [185] DDM1S12_Rx_CDC_VCAN_BUS */
    ,{ 0x400002EEUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [186] DDM1S16_Rx_CDC_VCAN_BUS */
    ,{ 0x400001D7UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [187] DDM1S17_Rx_CDC_VCAN_BUS */
    ,{ 0x400002DAUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [188] DDM1S20_Rx_CDC_VCAN_BUS */
    ,{ 0x40000219UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [189] DDM1S32_Rx_CDC_VCAN_BUS */
    ,{ 0x400002E5UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [190] DDM1S35_Rx_CDC_VCAN_BUS */
    ,{ 0x40000158UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [191] DDM1S77_Rx_CDC_VCAN_BUS */
    ,{ 0x40000282UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [192] DDM1SFH_Rx_CDC_VCAN_BUS */
    ,{ 0x40000528UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [193] DKY1S26_Rx_CDC_VCAN_BUS */
    ,{ 0x400003BEUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [194] DRL1S03_Rx_CDC_VCAN_BUS */
    ,{ 0x400003AFUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [195] DRR1S03_Rx_CDC_VCAN_BUS */
    ,{ 0x40000285UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [196] DS11S27_Rx_CDC_VCAN_BUS */
    ,{ 0x40000317UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [197] DS11S37_Rx_CDC_VCAN_BUS */
    ,{ 0x40000608UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [198] DS11S40_Rx_CDC_VCAN_BUS */
    ,{ 0x40000411UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [199] DS12F02_Rx_CDC_VCAN_BUS */
    ,{ 0x40000412UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [200] DS12F03_Rx_CDC_VCAN_BUS */
    ,{ 0x400003F0UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [201] DST1S02_Rx_CDC_VCAN_BUS */
    ,{ 0x400004A0UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [202] EBU1D01_Rx_CDC_VCAN_BUS */
    ,{ 0x400003BFUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [203] ECT1G01_Rx_CDC_VCAN_BUS */
    ,{ 0x400002A1UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [204] ECT1G92_Rx_CDC_VCAN_BUS */
    ,{ 0x40000401UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [205] ECT1S93_Rx_CDC_VCAN_BUS */
    ,{ 0x400001BCUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [206] EHV1E96_Rx_CDC_VCAN_BUS */
    ,{ 0x4000007EUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [207] EHV1F02_Rx_CDC_VCAN_BUS */
    ,{ 0x400000A5UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [208] EHV1F04_Rx_CDC_VCAN_BUS */
    ,{ 0x40000128UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [209] EHV1G30_Rx_CDC_VCAN_BUS */
    ,{ 0x400002A7UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [210] EHV1G70_Rx_CDC_VCAN_BUS */
    ,{ 0x400002A8UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [211] EHV1G71_Rx_CDC_VCAN_BUS */
    ,{ 0x400001D0UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [212] EHV1S23_Rx_CDC_VCAN_BUS */
    ,{ 0x4000042FUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [213] EHV1S26_Rx_CDC_VCAN_BUS */
    ,{ 0x40000325UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [214] EHV1S31_Rx_CDC_VCAN_BUS */
    ,{ 0x400003B6UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [215] EHV1S90_Rx_CDC_VCAN_BUS */
    ,{ 0x40000421UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [216] EHV1S94_Rx_CDC_VCAN_BUS */
    ,{ 0x4000040BUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [217] EHV1S95_Rx_CDC_VCAN_BUS */
    ,{ 0x400001FAUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [218] EHV1S96_Rx_CDC_VCAN_BUS */
    ,{ 0x4000042BUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [219] EHV1S97_Rx_CDC_VCAN_BUS */
    ,{ 0x400002DEUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [220] EHV1S99_Rx_CDC_VCAN_BUS */
    ,{ 0x400002EBUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [221] EHV1SL2_Rx_CDC_VCAN_BUS */
    ,{ 0x400000A6UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [222] EHV2G02_Rx_CDC_VCAN_BUS */
    ,{ 0x40000075UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [223] EHV2G10_Rx_CDC_VCAN_BUS */
    ,{ 0x400000A1UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [224] EHV2G20_Rx_CDC_VCAN_BUS */
    ,{ 0x40000335UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [225] EIM1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x400005F3UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [226] ENG1C01_Rx_CDC_VCAN_BUS */
    ,{ 0x400005F4UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [227] ENG1C02_Rx_CDC_VCAN_BUS */
    ,{ 0x40000499UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [228] ENG1D51_Rx_CDC_VCAN_BUS */
    ,{ 0x4000049AUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [229] ENG1D52_Rx_CDC_VCAN_BUS */
    ,{ 0x4000049BUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [230] ENG1D53_Rx_CDC_VCAN_BUS */
    ,{ 0x4000049DUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [231] ENG1D55_Rx_CDC_VCAN_BUS */
    ,{ 0x400004A8UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [232] ENG1D56_Rx_CDC_VCAN_BUS */
    ,{ 0x400004AEUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [233] ENG1D59_Rx_CDC_VCAN_BUS */
    ,{ 0x400004AFUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [234] ENG1D60_Rx_CDC_VCAN_BUS */
    ,{ 0x400000A4UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [235] ENG1G03_Rx_CDC_VCAN_BUS */
    ,{ 0x400001C5UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [236] ENG1G13_Rx_CDC_VCAN_BUS */
    ,{ 0x4000051EUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [237] ENG1G90_Rx_CDC_VCAN_BUS */
    ,{ 0x400000FCUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [238] ENG1G92_Rx_CDC_VCAN_BUS */
    ,{ 0x40000592UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [239] ENG1S51_Rx_CDC_VCAN_BUS */
    ,{ 0x40000589UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [240] ENG1S60_Rx_CDC_VCAN_BUS */
    ,{ 0x40000583UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [241] ENG1S99_Rx_CDC_VCAN_BUS */
    ,{ 0x400004A3UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [242] EPS1D50_Rx_CDC_VCAN_BUS */
    ,{ 0x40000062UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [243] EPS1S11_Rx_CDC_VCAN_BUS */
    ,{ 0x400001CAUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [244] EPS1S90_Rx_CDC_VCAN_BUS */
    ,{ 0x400005F6UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [245] FCM1C01_Rx_CDC_VCAN_BUS */
    ,{ 0x400005F1UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [246] FCM1C03_Rx_CDC_VCAN_BUS */
    ,{ 0x40000489UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [247] FCM1S10_Rx_CDC_VCAN_BUS */
    ,{ 0x4000048BUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [248] FCM1S12_Rx_CDC_VCAN_BUS */
    ,{ 0x40000251UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [249] FCM1S39_Rx_CDC_VCAN_BUS */
    ,{ 0x40000252UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [250] FCM1S40_Rx_CDC_VCAN_BUS */
    ,{ 0x40000261UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [251] FCM1S41_Rx_CDC_VCAN_BUS */
    ,{ 0x40000274UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [252] FCM1S49_Rx_CDC_VCAN_BUS */
    ,{ 0x40000275UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [253] FCM1S51_Rx_CDC_VCAN_BUS */
    ,{ 0x40000276UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [254] FCM1S52_Rx_CDC_VCAN_BUS */
    ,{ 0x4000027CUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [255] FCM1S58_Rx_CDC_VCAN_BUS */
    ,{ 0x4000028AUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [256] FCM1S66_Rx_CDC_VCAN_BUS */
    ,{ 0x4000025AUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [257] FCM1S70_Rx_CDC_VCAN_BUS */
    ,{ 0x40000159UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [258] FCM1S76_Rx_CDC_VCAN_BUS */
    ,{ 0x4000015AUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [259] FCM1S78_Rx_CDC_VCAN_BUS */
    ,{ 0x40000100UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [260] FCM1S79_Rx_CDC_VCAN_BUS */
    ,{ 0x4000020FUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [261] FCM1S88_Rx_CDC_VCAN_BUS */
    ,{ 0x400001B2UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [262] FCM1S90_Rx_CDC_VCAN_BUS */
    ,{ 0x40000259UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [263] FCM1S92_Rx_CDC_VCAN_BUS */
    ,{ 0x400000A8UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [264] FCM1S95_Rx_CDC_VCAN_BUS */
    ,{ 0x40000115UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [265] FWD1S10_Rx_CDC_VCAN_BUS */
    ,{ 0x40000633UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [266] IDT1S02_Rx_CDC_VCAN_BUS */
    ,{ 0x400003FBUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [267] IDT1S07_Rx_CDC_VCAN_BUS */
    ,{ 0x4000014BUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [268] IDT1S08_Rx_CDC_VCAN_BUS */
    ,{ 0x40000532UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [269] IDT1S15_Rx_CDC_VCAN_BUS */
    ,{ 0x400005ADUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [270] IMS1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x4000043BUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [271] IPA1S05_Rx_CDC_VCAN_BUS */
    ,{ 0x4000036BUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [272] ITS1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x400003DEUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [273] ITS1S04_Rx_CDC_VCAN_BUS */
    ,{ 0x40000314UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [274] ITS1S05_Rx_CDC_VCAN_BUS */
    ,{ 0x4000027BUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [275] ITS1S08_Rx_CDC_VCAN_BUS */
    ,{ 0x40000494UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [276] LVN1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x40000611UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [277] MET1S02_Rx_CDC_VCAN_BUS */
    ,{ 0x40000524UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [278] MET1S38_Rx_CDC_VCAN_BUS */
    ,{ 0x400001DCUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [279] MET1S47_Rx_CDC_VCAN_BUS */
    ,{ 0x400001F7UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [280] MET1S55_Rx_CDC_VCAN_BUS */
    ,{ 0x40000049UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [281] MGC1F13_Rx_CDC_VCAN_BUS */
    ,{ 0x400001CCUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [282] PDC1G01_Rx_CDC_VCAN_BUS */
    ,{ 0x40000507UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [283] PDC1G02_Rx_CDC_VCAN_BUS */
    ,{ 0x400002F4UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [284] PDS1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x40000295UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [285] PLG1G15_Rx_CDC_VCAN_BUS */
    ,{ 0x40000296UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [286] PLG1G16_Rx_CDC_VCAN_BUS */
    ,{ 0x40000422UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [287] PLG1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x40000432UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [288] PLG1S06_Rx_CDC_VCAN_BUS */
    ,{ 0x400002A6UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [289] PLG1S20_Rx_CDC_VCAN_BUS */
    ,{ 0x40000204UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [290] PLG1S21_Rx_CDC_VCAN_BUS */
    ,{ 0x400001D1UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [291] PMN1G03_Rx_CDC_VCAN_BUS */
    ,{ 0x40000403UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [292] PST1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x40000405UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [293] PST1S02_Rx_CDC_VCAN_BUS */
    ,{ 0x4000014DUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [294] RCP1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x40000230UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [295] RCP1S02_Rx_CDC_VCAN_BUS */
    ,{ 0x4000014FUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [296] RCP1S03_Rx_CDC_VCAN_BUS */
    ,{ 0x400002C6UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [297] RCP1S04_Rx_CDC_VCAN_BUS */
    ,{ 0x400002C7UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [298] RCP1S05_Rx_CDC_VCAN_BUS */
    ,{ 0x400002C8UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [299] RCP1S06_Rx_CDC_VCAN_BUS */
    ,{ 0x400003CAUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [300] RSE1G20_Rx_CDC_VCAN_BUS */
    ,{ 0x4000032FUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [301] RSE1G24_Rx_CDC_VCAN_BUS */
    ,{ 0x40000336UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [302] RSE1G25_Rx_CDC_VCAN_BUS */
    ,{ 0x4000034DUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [303] RSE1G26_Rx_CDC_VCAN_BUS */
    ,{ 0x400003C8UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [304] RSE1S02_Rx_CDC_VCAN_BUS */
    ,{ 0x40000328UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [305] RST1S03_Rx_CDC_VCAN_BUS */
    ,{ 0x400001DBUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [306] SBW1G02_Rx_CDC_VCAN_BUS */
    ,{ 0x40000439UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [307] SCN1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x40000375UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [308] SCN1S02_Rx_CDC_VCAN_BUS */
    ,{ 0x400004A9UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [309] SCS1D50_Rx_CDC_VCAN_BUS */
    ,{ 0x4000010BUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [310] SCS1S10_Rx_CDC_VCAN_BUS */
    ,{ 0x400002FDUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [311] SCS1S11_Rx_CDC_VCAN_BUS */
    ,{ 0x400002FEUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [312] SCS1S14_Rx_CDC_VCAN_BUS */
    ,{ 0x4000040CUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [313] SOL1S02_Rx_CDC_VCAN_BUS */
    ,{ 0x4000040DUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [314] SOL1S03_Rx_CDC_VCAN_BUS */
    ,{ 0x400001EBUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [315] SOL1S04_Rx_CDC_VCAN_BUS */
    ,{ 0x400001EAUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [316] SOL1S05_Rx_CDC_VCAN_BUS */
    ,{ 0x400001BBUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [317] SOL1S06_Rx_CDC_VCAN_BUS */
    ,{ 0x40000495UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [318] TPM1S02_Rx_CDC_VCAN_BUS */
    ,{ 0x40000496UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [319] TPM1S03_Rx_CDC_VCAN_BUS */
    ,{ 0x40000347UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [320] TPM1S04_Rx_CDC_VCAN_BUS */
    ,{ 0x4000034CUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [321] TPM1S05_Rx_CDC_VCAN_BUS */
    ,{ 0x40000417UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [322] TPM1S06_Rx_CDC_VCAN_BUS */
    ,{ 0x4000036FUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [323] TPM1S07_Rx_CDC_VCAN_BUS */
    ,{ 0x40000418UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [324] TPM1S08_Rx_CDC_VCAN_BUS */
    ,{ 0x40000426UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [325] TPM1S09_Rx_CDC_VCAN_BUS */
    ,{ 0x40000428UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [326] TPM1S10_Rx_CDC_VCAN_BUS */
    ,{ 0x4000042AUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [327] TPM1S11_Rx_CDC_VCAN_BUS */
    ,{ 0x4000042CUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [328] TPM1S12_Rx_CDC_VCAN_BUS */
    ,{ 0x400002A0UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [329] TRA1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x400000A0UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [330] TRA1S02_Rx_CDC_VCAN_BUS */
    ,{ 0x400003E7UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [331] UCB1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x40000318UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [332] VAS1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x400004A4UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [333] VGR1D50_Rx_CDC_VCAN_BUS */
    ,{ 0x400004A1UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [334] VSC1D51_Rx_CDC_VCAN_BUS */
    ,{ 0x4000006AUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [335] VSC1F01_Rx_CDC_VCAN_BUS */
    ,{ 0x40000069UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [336] VSC1G12_Rx_CDC_VCAN_BUS */
    ,{ 0x4000009EUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [337] VSC1G13_Rx_CDC_VCAN_BUS */
    ,{ 0x400000B7UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [338] VSC1G14_Rx_CDC_VCAN_BUS */
    ,{ 0x40000262UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [339] VSC1G96_Rx_CDC_VCAN_BUS */
    ,{ 0x40000601UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [340] VUM1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x400002F9UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [341] WIP1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x4000027EUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [342] YGW1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x4000037FUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [343] ZN11S02_Rx_CDC_VCAN_BUS */
    ,{ 0x4000038AUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [344] ZN11S03_Rx_CDC_VCAN_BUS */
    ,{ 0x40000086UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [345] ZN11S08_Rx_CDC_VCAN_BUS */
    ,{ 0x400001DEUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [346] ZN11S14_Rx_CDC_VCAN_BUS */
    ,{ 0x400001DFUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [347] ZN11S17_Rx_CDC_VCAN_BUS */
    ,{ 0x40000368UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [348] ZN11S19_Rx_CDC_VCAN_BUS */
    ,{ 0x40000398UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [349] ZN11S25_Rx_CDC_VCAN_BUS */
    ,{ 0x4000036AUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [350] ZN11S26_Rx_CDC_VCAN_BUS */
    ,{ 0x4000039CUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [351] ZN11S32_Rx_CDC_VCAN_BUS */
    ,{ 0x40000500UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [352] ZN11S38_Rx_CDC_VCAN_BUS */
    ,{ 0x4000036EUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [353] ZN11S60_Rx_CDC_VCAN_BUS */
    ,{ 0x4000033FUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [354] ZN11S63_Rx_CDC_VCAN_BUS */
    ,{ 0x400003D2UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [355] ZN11S64_Rx_CDC_VCAN_BUS */
    ,{ 0x400003F9UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [356] ZN11S65_Rx_CDC_VCAN_BUS */
    ,{ 0x40000400UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [357] ZN11S66_Rx_CDC_VCAN_BUS */
    ,{ 0x40000404UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [358] ZN11S67_Rx_CDC_VCAN_BUS */
    ,{ 0x40000350UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [359] ZN11SF6_Rx_CDC_VCAN_BUS */
    ,{ 0x40000352UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [360] ZN11SF7_Rx_CDC_VCAN_BUS */
    ,{ 0x40000353UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [361] ZN11SF8_Rx_CDC_VCAN_BUS */
    ,{ 0x400003BBUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [362] ZN11SF9_Rx_CDC_VCAN_BUS */
    ,{ 0x400001E1UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [363] ZN21S05_Rx_CDC_VCAN_BUS */
    ,{ 0x40000390UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [364] ZN21S13_Rx_CDC_VCAN_BUS */
    ,{ 0x400001BEUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [365] ZN21S28_Rx_CDC_VCAN_BUS */
    ,{ 0x400001CEUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [366] ZN21S52_Rx_CDC_VCAN_BUS */
    ,{ 0x400003A9UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [367] ZN21S72_Rx_CDC_VCAN_BUS */
};

#if(BSW_CANIF_CFG_CANID_MASK_TYPE == BSW_CANIF_MASK_RXMSG)
/* PduR Rx Msg CAN ID Mask Table */
BswConst BswU4 bsw_canif_stRxPduRMskTbl[BSW_CANIF_RXPDURPDUNUM] =
{
   /* CAN-ID Mask */
};
#endif /* (BSW_CANIF_CFG_CANID_MASK_TYPE == BSW_CANIF_MASK_RXMSG) */
#endif

#if(BSW_CANIF_RXCANNMPDUNUM != 0U)
/* CanNm Rx PDU ID Table */
BswConst Bsw_CanIf_RxPduTblType bsw_canif_stRxCanNmPduTbl[BSW_CANIF_RXCANNMPDUNUM] =
{
   /* CAN-ID      , DLC       , Channel             , Extend     */
     { 0x00000442UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [0] CDC1N00_Rx_CDC_VCAN_BUS */
    ,{ 0x0000047DUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [1] CDC1N01_Rx_CDC_VCAN_BUS */
    ,{ 0x0000047FUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [2] CDC1N03_Rx_CDC_VCAN_BUS */
};

#if(BSW_CANIF_CFG_CANID_MASK_TYPE == BSW_CANIF_MASK_RXMSG)
/* CanNm Rx Msg CAN ID Mask Table */
BswConst BswU4 bsw_canif_stRxCanNmMskTbl[BSW_CANIF_RXCANNMPDUNUM] =
{
   /* CAN-ID Mask */
};
#endif /* (BSW_CANIF_CFG_CANID_MASK_TYPE == BSW_CANIF_MASK_RXMSG) */
#endif

#if(BSW_CANIF_RXCANTPPDUNUM != 0U)
/* CanTp Rx PDU ID Table */
BswConst Bsw_CanIf_RxPduTblType bsw_canif_stRxCanTpPduTbl[BSW_CANIF_RXCANTPPDUNUM] =
{
   /* CAN-ID      , DLC       , Channel             , Extend     */
     { 0x98DA1CE0UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [0] Nsdu_RX_RxNPdu_Diag_Physical_Service */
    ,{ 0x98DBEFE0UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [1] Nsdu_RX_RxNPdu_Diag_Functional_Service */
    ,{ 0x98DA1CE1UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [2] Nsdu_RX_RxNPdu_Diag_Physical_Remote */
    ,{ 0x98DBEFE1UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [3] Nsdu_RX_RxNPdu_Diag_Functional_Remote */
    ,{ 0xD8DA1CE0UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [4] Nsdu_RX_RxNPdu_Diag_Physical_FD_Service */
    ,{ 0xD8DBEFE0UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [5] Nsdu_RX_RxNPdu_Diag_Functional_FD_Service */
    ,{ 0xD8DA1CE1UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [6] Nsdu_RX_RxNPdu_Diag_Physical_FD_Remote */
    ,{ 0xD8DBEFE1UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [7] Nsdu_RX_RxNPdu_Diag_Functional_FD_Remote */
};

#if(BSW_CANIF_CFG_CANID_MASK_TYPE == BSW_CANIF_MASK_RXMSG)
/* CanTp Rx Msg CAN ID Mask Table */
BswConst BswU4 bsw_canif_stRxCanTpMskTbl[BSW_CANIF_RXCANTPPDUNUM] =
{
   /* CAN-ID Mask */
};
#endif /* (BSW_CANIF_CFG_CANID_MASK_TYPE == BSW_CANIF_MASK_RXMSG) */
#endif

#if(BSW_CANIF_RXCDD1PDUNUM != 0U)
/* CDD1 Rx PDU ID Table */
BswConst Bsw_CanIf_RxPduTblType bsw_canif_stRxCdd1PduTbl[BSW_CANIF_RXCDD1PDUNUM] =
{
   /* CAN-ID      , DLC       , Channel             , Extend     */
};

#if(BSW_CANIF_CFG_CANID_MASK_TYPE == BSW_CANIF_MASK_RXMSG)
/* CDD1 Rx Msg CAN ID Mask Table */
BswConst BswU4 bsw_canif_stRxCdd1MskTbl[BSW_CANIF_RXCDD1PDUNUM] =
{
   /* CAN-ID Mask */
};
#endif /* (BSW_CANIF_CFG_CANID_MASK_TYPE == BSW_CANIF_MASK_RXMSG) */
#endif

#if(BSW_CANIF_RXCDD2PDUNUM != 0U)
/* CDD2 Rx PDU ID Table */
BswConst Bsw_CanIf_RxPduTblType bsw_canif_stRxCdd2PduTbl[BSW_CANIF_RXCDD2PDUNUM] =
{
   /* CAN-ID      , DLC       , Channel             , Extend     */
};

#if(BSW_CANIF_CFG_CANID_MASK_TYPE == BSW_CANIF_MASK_RXMSG)
/* CDD2 Rx Msg CAN ID Mask Table */
BswConst BswU4 bsw_canif_stRxCdd2MskTbl[BSW_CANIF_RXCDD2PDUNUM] =
{
   /* CAN-ID Mask */
};
#endif /* (BSW_CANIF_CFG_CANID_MASK_TYPE == BSW_CANIF_MASK_RXMSG) */
#endif

#if(BSW_CANIF_RXXCPPDUNUM != 0U)
/* Xcp Rx PDU ID Table */
BswConst Bsw_CanIf_RxPduTblType bsw_canif_stRxXcpPduTbl[BSW_CANIF_RXXCPPDUNUM] =
{
   /* CAN-ID      , DLC       , Channel             , Extend     */
};

#if(BSW_CANIF_CFG_CANID_MASK_TYPE == BSW_CANIF_MASK_RXMSG)
/* XCP Rx Msg CAN ID Mask Table */
BswConst BswU4 bsw_canif_stRxXcpMskTbl[BSW_CANIF_RXXCPPDUNUM] =
{
   /* CAN-ID Mask */
};
#endif /* (BSW_CANIF_CFG_CANID_MASK_TYPE == BSW_CANIF_MASK_RXMSG) */
#endif

/******************************************/
/*                                        */
/* Tx Rx Setting                          */
/*                                        */
/******************************************/
#if((BSW_CANIF_TXPDURPDUNUM + BSW_CANIF_RXPDURPDUNUM) != 0U)
BswConst BswU1 bsw_canif_u1MsgInfo[BSW_CANIF_TXPDURPDUNUM + BSW_CANIF_RXPDURPDUNUM] =
{
     (BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [0] AVN1S38_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [1] AVN1S34_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [2] AVN1SG7_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [3] AVN1S71_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [4] AVN1S32_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [5] AVN1SD4_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [6] AVN1SD6_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [7] AVN1SD7_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [8] AVN1SF6_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [9] AVN1SF4_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [10] AVN1SF5_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [11] AVN1SE9_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [12] AVN1SF1_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [13] AVN1SF2_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [14] AVN1SF3_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [15] AVN1SE3_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [16] AVN1SE8_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [17] AVN1SE4_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [18] AVN1SE5_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [19] AVN1SE6_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [20] AVN1SE7_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [21] AVN1SE2_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [22] AVN1SE1_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [23] AVN1SD8_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [24] AVN1SD9_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [25] AVN1S52_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [26] AVN1SA6_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [27] AVN1SB9_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [28] AVN1S40_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [29] AVN1S41_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [30] AVN1S42_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [31] AVN1S43_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [32] AVN1S73_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [33] AVN1SB7_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [34] AVN1SB8_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [35] AVN1SC1_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [36] AVN1SC2_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [37] AVN1SC3_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [38] AVN1SC4_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [39] AVN1SC5_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [40] AVN1SC6_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [41] AVN1SC7_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [42] AVN1SC8_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [43] AVN1SH1_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [44] AVN1SC9_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [45] AVN1SD1_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [46] AVN1SD2_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [47] AVN1SD3_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [48] AVN1SD5_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [49] AVN1SF7_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [50] AVN1SF8_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [51] AVN1SF9_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [52] AVN1S67_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [53] AVN1S68_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [54] AVN1SB2_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [55] MET1S33_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [56] AVN1S30_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [57] AVN1SA1_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [58] AVN1SG4_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [59] AVN1SG3_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [60] AVN1S94_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [61] AVN1S95_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [62] CDC1S04_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [63] AVN1SA7_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [64] AVN1S62_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [65] AVN1S01_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [66] AVN1S03_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [67] AVN1S05_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [68] AVN1S06_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [69] AVN1S08_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [70] AVN1S04_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [71] AVN1S07_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [72] AVN1S46_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [73] AVN1S47_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [74] AVN1S70_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [75] AVN1S99_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [76] AVN1SA9_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [77] AVN1S78_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [78] AVN1S63_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [79] AVN1S76_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [80] AVN1S97_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [81] AVN1S98_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [82] AVN1S11_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [83] AVN1SA8_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [84] AVN1S77_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [85] AVN1SB1_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [86] AVN1S33_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [87] AVN1S20_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [88] AVN1S21_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [89] AVN1S22_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [90] AVN1S23_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [91] AVN1SG5_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [92] AVN1S64_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [93] AVN1SB3_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [94] AVN1SB4_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [95] AVN1SB5_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [96] AVN1S44_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [97] AVN1S65_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [98] AVN1S69_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [99] AVN1S66_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [100] AVN1S39_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [101] AVN1SG6_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [102] ABG1D50_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [103] ABG1D51_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [104] ABG1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [105] ABG1S04_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [106] ABG1S09_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [107] ACN1D50_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [108] ACN1S03_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [109] ACN1S04_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [110] ACN1S05_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [111] ACN1S07_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [112] ACN1S15_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [113] ACN1S16_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [114] ACN1S22_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [115] ACN1S25_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [116] ACN1S29_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [117] ADC1S06_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [118] ADC1S13_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [119] ADC1S14_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [120] ADC1S15_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [121] ADC1S17_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [122] ADC1S19_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [123] ADC1S20_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [124] ADC1S23_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [125] ADC1S27_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [126] ADC1S30_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [127] ADC1S31_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [128] ADU1S02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [129] ADU1S03_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [130] ADU1S05_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [131] ADU1S06_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [132] ADU1S07_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [133] ADU1S18_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [134] ADU1S19_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [135] ADU1S20_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [136] ADU1S21_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [137] ADU1S22_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [138] ADU1S23_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [139] ADU1S24_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [140] ADU1S25_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [141] ADU1S26_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [142] ADU1S27_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [143] ADU1S28_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [144] ARS1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [145] ARS1S90_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [146] BAT1E41_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [147] BAT1E45_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [148] BAT1ED1_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [149] BAT1ED5_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [150] BAT1EDA_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [151] BAT1EDB_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [152] BAT1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [153] BAT1S08_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [154] BAT1S11_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [155] BAT2ED2_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [156] BCC1S05_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [157] BCC1S06_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [158] BDB1F01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [159] BDB1F02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [160] BDB1F03_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [161] BDB1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [162] BDB1S02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [163] BDB1S03_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [164] BDB1S04_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [165] BDB1S05_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [166] BDB1S08_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [167] BDB1S10_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [168] BDB1S13_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [169] BDB1S19_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [170] BDB1S25_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [171] BDB1S26_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [172] BDB1S27_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [173] BDB1S28_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [174] BDB1S29_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [175] BDB1S35_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [176] BDB1S36_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [177] BDC1D00_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [178] BDC1D01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [179] BDC1S13_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [180] BDC1S14_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [181] BDC1S16_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [182] BDC1S30_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [183] BDC1S33_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [184] BDC1S40_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [185] BDC1S41_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [186] BDC1S46_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [187] BDC1S48_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [188] BDC1S52_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [189] BDC1S60_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [190] BDC1S81_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [191] BDC1S82_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [192] BDC1S83_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [193] BDC1S87_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [194] BDC1S89_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [195] BDC1S91_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [196] BDC1S97_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [197] BDC1S98_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [198] BDC1S99_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [199] BDC1SA0_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [200] BDC1SA1_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [201] BDC1SC1_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [202] BDC1SC2_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [203] BDC1SC3_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [204] BDC1SC4_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [205] BDC1SC5_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [206] BDC1SC6_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [207] BDC1SC7_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [208] BDC1SC8_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [209] BDC1SC9_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [210] BDC1SD1_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [211] BDC1SD2_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [212] BDC1SD3_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [213] BDC1SD4_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [214] BDC1SD5_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [215] BDC1SD6_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [216] BDC1SD7_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [217] BDC1SD8_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [218] BDC1SD9_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [219] BDC1SE1_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [220] BDC1SE2_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [221] BDC1SE3_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [222] BDC1SE4_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [223] BDC1SE5_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [224] BDC1SE6_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [225] BDC1SE7_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [226] BDC1SE8_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [227] BDC1SE9_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [228] BDC1SF1_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [229] BDC1SF2_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [230] BDC1SF3_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [231] BDC1SF4_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [232] BDC1SF5_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [233] BDC1SF6_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [234] BDC1SG4_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [235] BDC1SG6_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [236] BDC1SG7_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [237] BDC1SG8_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [238] BDC1SG9_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [239] BDC1SH3_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [240] BDC1SH4_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [241] BDC1SH5_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [242] BDC1SH6_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [243] BDC1SH8_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [244] BDC1SI0_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [245] BDC1SI1_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [246] BDC1SI2_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [247] BDC1SI3_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [248] BDC1SI4_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [249] BDC1SI5_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [250] BDC1SI6_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [251] BDC1SI7_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [252] BDC1SI8_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [253] BDC1SI9_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [254] BDC1SJ0_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [255] BDC1SJ1_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [256] BDC1SJ2_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [257] BDC1SJ3_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [258] BDC1SJ4_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [259] BDC1SJ5_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [260] BDC1SJ6_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [261] BDC1SJ7_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [262] BDC1SJ8_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [263] BDC1SV1_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [264] BDC1SV2_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [265] BDC1SV3_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [266] BDF3S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [267] BDF3S02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [268] BDR3S02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [269] BKD1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [270] BKD1S02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [271] BSR1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [272] BSR1S02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [273] BSR1S03_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [274] CDC1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [275] CMB1S03_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [276] CMB1S04_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [277] CSR1G10_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [278] CSR1S04_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [279] CSR1S07_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [280] CSR1S08_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [281] DCM1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [282] DCM1S03_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [283] DCM1S04_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [284] DCM1S08_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [285] DDM1S00_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [286] DDM1S09_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [287] DDM1S12_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [288] DDM1S16_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [289] DDM1S17_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [290] DDM1S20_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [291] DDM1S32_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [292] DDM1S35_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [293] DDM1S77_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [294] DDM1SFH_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [295] DKY1S26_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [296] DRL1S03_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [297] DRR1S03_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [298] DS11S27_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [299] DS11S37_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [300] DS11S40_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [301] DS12F02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [302] DS12F03_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [303] DST1S02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [304] EBU1D01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [305] ECT1G01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [306] ECT1G92_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [307] ECT1S93_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [308] EHV1E96_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [309] EHV1F02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [310] EHV1F04_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [311] EHV1G30_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [312] EHV1G70_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [313] EHV1G71_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [314] EHV1S23_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [315] EHV1S26_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [316] EHV1S31_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [317] EHV1S90_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [318] EHV1S94_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [319] EHV1S95_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [320] EHV1S96_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [321] EHV1S97_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [322] EHV1S99_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [323] EHV1SL2_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [324] EHV2G02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [325] EHV2G10_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [326] EHV2G20_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [327] EIM1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [328] ENG1C01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [329] ENG1C02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [330] ENG1D51_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [331] ENG1D52_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [332] ENG1D53_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [333] ENG1D55_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [334] ENG1D56_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [335] ENG1D59_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [336] ENG1D60_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [337] ENG1G03_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [338] ENG1G13_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [339] ENG1G90_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [340] ENG1G92_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [341] ENG1S51_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [342] ENG1S60_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [343] ENG1S99_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [344] EPS1D50_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [345] EPS1S11_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [346] EPS1S90_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [347] FCM1C01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [348] FCM1C03_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [349] FCM1S10_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [350] FCM1S12_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [351] FCM1S39_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [352] FCM1S40_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [353] FCM1S41_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [354] FCM1S49_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [355] FCM1S51_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [356] FCM1S52_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [357] FCM1S58_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [358] FCM1S66_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [359] FCM1S70_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [360] FCM1S76_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [361] FCM1S78_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [362] FCM1S79_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [363] FCM1S88_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [364] FCM1S90_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [365] FCM1S92_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [366] FCM1S95_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [367] FWD1S10_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [368] IDT1S02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [369] IDT1S07_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [370] IDT1S08_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [371] IDT1S15_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [372] IMS1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [373] IPA1S05_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [374] ITS1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [375] ITS1S04_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [376] ITS1S05_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [377] ITS1S08_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [378] LVN1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [379] MET1S02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [380] MET1S38_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [381] MET1S47_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [382] MET1S55_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [383] MGC1F13_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [384] PDC1G01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [385] PDC1G02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [386] PDS1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [387] PLG1G15_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [388] PLG1G16_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [389] PLG1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [390] PLG1S06_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [391] PLG1S20_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [392] PLG1S21_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [393] PMN1G03_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [394] PST1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [395] PST1S02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [396] RCP1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [397] RCP1S02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [398] RCP1S03_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [399] RCP1S04_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [400] RCP1S05_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [401] RCP1S06_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [402] RSE1G20_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [403] RSE1G24_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [404] RSE1G25_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [405] RSE1G26_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [406] RSE1S02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [407] RST1S03_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [408] SBW1G02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [409] SCN1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [410] SCN1S02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [411] SCS1D50_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [412] SCS1S10_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [413] SCS1S11_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [414] SCS1S14_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [415] SOL1S02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [416] SOL1S03_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [417] SOL1S04_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [418] SOL1S05_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [419] SOL1S06_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [420] TPM1S02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [421] TPM1S03_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [422] TPM1S04_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [423] TPM1S05_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [424] TPM1S06_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [425] TPM1S07_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [426] TPM1S08_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [427] TPM1S09_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [428] TPM1S10_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [429] TPM1S11_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [430] TPM1S12_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [431] TRA1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [432] TRA1S02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [433] UCB1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [434] VAS1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [435] VGR1D50_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [436] VSC1D51_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [437] VSC1F01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [438] VSC1G12_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [439] VSC1G13_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [440] VSC1G14_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [441] VSC1G96_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [442] VUM1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [443] WIP1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [444] YGW1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [445] ZN11S02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [446] ZN11S03_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [447] ZN11S08_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [448] ZN11S14_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [449] ZN11S17_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [450] ZN11S19_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [451] ZN11S25_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [452] ZN11S26_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [453] ZN11S32_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [454] ZN11S38_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [455] ZN11S60_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [456] ZN11S63_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [457] ZN11S64_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [458] ZN11S65_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [459] ZN11S66_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [460] ZN11S67_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [461] ZN11SF6_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [462] ZN11SF7_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [463] ZN11SF8_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [464] ZN11SF9_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [465] ZN21S05_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [466] ZN21S13_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [467] ZN21S28_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [468] ZN21S52_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [469] ZN21S72_Rx_CDC_VCAN_BUS */
};
#endif

#if (BSW_CANIF_CHKSUM_PTN2_USE == BSW_USE)
#if (BSW_CANIF_CFG_TX_SUMMSG_NUM != 0U)
BswConst Bsw_CanIf_SumInfoType bsw_canif_fs_stSum2TxInfo[BSW_CANIF_CFG_TX_SUMMSG_NUM] =
{
};
#endif /* (BSW_CANIF_CFG_TX_SUMMSG_NUM != 0U) */
#if (BSW_CANIF_CFG_RX_SUMMSG_NUM != 0U)
BswConst Bsw_CanIf_SumInfoType bsw_canif_fs_stSum2RxInfo[BSW_CANIF_CFG_RX_SUMMSG_NUM] =
{
};
#endif /* (BSW_CANIF_CFG_RX_SUMMSG_NUM != 0U) */
#endif /* (BSW_CANIF_CHKSUM_PTN2_USE == BSW_USE) */


#if (BSW_CANIF_PKTCAN_EXTA2_USE == BSW_USE)
#if (BSW_CANIF_TXPDURPDUNUM != 0U)
BswConst BswU1 bsw_canif_tx_u1AvcLanPriTbl[BSW_CANIF_TXPDURPDUNUM] = {
};
#endif /* (BSW_CANIF_TXPDURPDUNUM != 0U) */
#endif /* (BSW_CANIF_PKTCAN_EXTA2_USE == BSW_USE) */


#if ( (BSW_CANIF_PKTCAN_EXTA1_USE == BSW_USE) || (BSW_CANIF_PKTCAN_EXTA2_USE == BSW_USE) || (BSW_CANIF_PKTCAN_EXTB_USE == BSW_USE) )
#if((BSW_CANIF_TXPDURPDUNUM + BSW_CANIF_RXPDURPDUNUM) != 0U)
BswConst BswU1 bsw_canif_u1MsgIdTbl[BSW_CANIF_TXPDURPDUNUM + BSW_CANIF_RXPDURPDUNUM] = {
};
#endif /* (BSW_CANIF_TXPDURPDUNUM != 0U) */
#endif /* ( (BSW_CANIF_PKTCAN_EXTA1_USE == BSW_USE) || (BSW_CANIF_PKTCAN_EXTA2_USE == BSW_USE) || (BSW_CANIF_PKTCAN_EXTB_USE == BSW_USE) ) */

#endif /* (BSW_BSWM_CS_FUNC_CANIF == BSW_USE) */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/10/10                                             */
/*  v1-1-0          :2018/12/12                                             */
/*  v2-0-0          :2021/02/12                                             */
/*  v3-0-0          :2024/10/03                                             */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-3-z0003                                        */
/*  BSW plug-in        :v3-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
