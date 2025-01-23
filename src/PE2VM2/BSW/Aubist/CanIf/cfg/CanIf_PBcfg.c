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
    ,{ 0x400001A2UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE007 }  /* [7] AVN1SD7_Tx_CDC_VCAN_BUS */
    ,{ 0x400001A3UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE007 }  /* [8] AVN1SF6_Tx_CDC_VCAN_BUS */
    ,{ 0x400001A5UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE007 }  /* [9] AVN1SF4_Tx_CDC_VCAN_BUS */
    ,{ 0x400001A7UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE007 }  /* [10] AVN1SF5_Tx_CDC_VCAN_BUS */
    ,{ 0x400001A8UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE007 }  /* [11] AVN1SE9_Tx_CDC_VCAN_BUS */
    ,{ 0x400001A9UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE007 }  /* [12] AVN1SF1_Tx_CDC_VCAN_BUS */
    ,{ 0x400001ABUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE007 }  /* [13] AVN1SF2_Tx_CDC_VCAN_BUS */
    ,{ 0x400001ACUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE007 }  /* [14] AVN1SF3_Tx_CDC_VCAN_BUS */
    ,{ 0x400001ADUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE007 }  /* [15] AVN1SE3_Tx_CDC_VCAN_BUS */
    ,{ 0x400001AEUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE007 }  /* [16] AVN1SE8_Tx_CDC_VCAN_BUS */
    ,{ 0x400001AFUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE007 }  /* [17] AVN1SE4_Tx_CDC_VCAN_BUS */
    ,{ 0x400001B0UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE007 }  /* [18] AVN1SE5_Tx_CDC_VCAN_BUS */
    ,{ 0x400001B3UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE007 }  /* [19] AVN1SE6_Tx_CDC_VCAN_BUS */
    ,{ 0x400001B4UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE007 }  /* [20] AVN1SE7_Tx_CDC_VCAN_BUS */
    ,{ 0x400001B5UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE007 }  /* [21] AVN1SE2_Tx_CDC_VCAN_BUS */
    ,{ 0x400001B7UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE007 }  /* [22] AVN1SE1_Tx_CDC_VCAN_BUS */
    ,{ 0x400001B8UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE007 }  /* [23] AVN1SD8_Tx_CDC_VCAN_BUS */
    ,{ 0x400001B9UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE007 }  /* [24] AVN1SD9_Tx_CDC_VCAN_BUS */
    ,{ 0x400001BDUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE007 }  /* [25] AVN1S52_Tx_CDC_VCAN_BUS */
    ,{ 0x400001ECUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE008 }  /* [26] AVN1SA6_Tx_CDC_VCAN_BUS */
    ,{ 0x400001F2UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE009 }  /* [27] AVN1SB9_Tx_CDC_VCAN_BUS */
    ,{ 0x400001FCUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE010 }  /* [28] AVN1S40_Tx_CDC_VCAN_BUS */
    ,{ 0x400001FDUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE011 }  /* [29] AVN1S41_Tx_CDC_VCAN_BUS */
    ,{ 0x400001FEUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE011 }  /* [30] AVN1S42_Tx_CDC_VCAN_BUS */
    ,{ 0x400001FFUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE011 }  /* [31] AVN1S43_Tx_CDC_VCAN_BUS */
    ,{ 0x400002AAUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE011 }  /* [32] AVN1S73_Tx_CDC_VCAN_BUS */
    ,{ 0x400002D2UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE012 }  /* [33] AVN1SB7_Tx_CDC_VCAN_BUS */
    ,{ 0x400002D3UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE013 }  /* [34] AVN1SB8_Tx_CDC_VCAN_BUS */
    ,{ 0x400002D4UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE013 }  /* [35] AVN1SC1_Tx_CDC_VCAN_BUS */
    ,{ 0x400002D5UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE013 }  /* [36] AVN1SC2_Tx_CDC_VCAN_BUS */
    ,{ 0x400002D6UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE013 }  /* [37] AVN1SC3_Tx_CDC_VCAN_BUS */
    ,{ 0x400002D7UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE013 }  /* [38] AVN1SC4_Tx_CDC_VCAN_BUS */
    ,{ 0x400002DFUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE013 }  /* [39] AVN1SC5_Tx_CDC_VCAN_BUS */
    ,{ 0x400002E0UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE014 }  /* [40] AVN1SC6_Tx_CDC_VCAN_BUS */
    ,{ 0x400002E1UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE015 }  /* [41] AVN1SC7_Tx_CDC_VCAN_BUS */
    ,{ 0x400002E2UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE015 }  /* [42] AVN1SC8_Tx_CDC_VCAN_BUS */
    ,{ 0x400002E3UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE015 }  /* [43] AVN1SH1_Tx_CDC_VCAN_BUS */
    ,{ 0x400002E7UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE016 }  /* [44] AVN1SG8_Tx_CDC_VCAN_BUS */
    ,{ 0x400002E8UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE017 }  /* [45] AVN1SG9_Tx_CDC_VCAN_BUS */
    ,{ 0x400002EFUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE015 }  /* [46] AVN1SC9_Tx_CDC_VCAN_BUS */
    ,{ 0x400002F0UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE015 }  /* [47] AVN1SD1_Tx_CDC_VCAN_BUS */
    ,{ 0x400002F2UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE015 }  /* [48] AVN1SD2_Tx_CDC_VCAN_BUS */
    ,{ 0x400002F5UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE015 }  /* [49] AVN1SD3_Tx_CDC_VCAN_BUS */
    ,{ 0x400002F6UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE017 }  /* [50] AVN1SD5_Tx_CDC_VCAN_BUS */
    ,{ 0x400002F7UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE016 }  /* [51] AVN1SF7_Tx_CDC_VCAN_BUS */
    ,{ 0x400002F8UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE015 }  /* [52] AVN1SF8_Tx_CDC_VCAN_BUS */
    ,{ 0x400002FAUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE015 }  /* [53] AVN1SF9_Tx_CDC_VCAN_BUS */
    ,{ 0x400002FBUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE015 }  /* [54] AVN1SG1_Tx_CDC_VCAN_BUS */
    ,{ 0x4000030EUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE017 }  /* [55] AVN1S67_Tx_CDC_VCAN_BUS */
    ,{ 0x4000030FUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE018 }  /* [56] AVN1S68_Tx_CDC_VCAN_BUS */
    ,{ 0x40000313UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE018 }  /* [57] AVN1SB2_Tx_CDC_VCAN_BUS */
    ,{ 0x4000031AUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE018 }  /* [58] AVN1S30_Tx_CDC_VCAN_BUS */
    ,{ 0x4000031DUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE018 }  /* [59] AVN1SA1_Tx_CDC_VCAN_BUS */
    ,{ 0x40000322UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE018 }  /* [60] AVN1SG4_Tx_CDC_VCAN_BUS */
    ,{ 0x4000033AUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE019 }  /* [61] AVN1SG3_Tx_CDC_VCAN_BUS */
    ,{ 0x40000345UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE020 }  /* [62] AVN1S94_Tx_CDC_VCAN_BUS */
    ,{ 0x40000346UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE021 }  /* [63] AVN1S95_Tx_CDC_VCAN_BUS */
    ,{ 0x4000034EUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE021 }  /* [64] AVN1S61_Tx_CDC_VCAN_BUS */
    ,{ 0x4000035AUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE022 }  /* [65] AVN1SA7_Tx_CDC_VCAN_BUS */
    ,{ 0x4000035BUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE022 }  /* [66] AVN1S62_Tx_CDC_VCAN_BUS */
    ,{ 0x40000384UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE023 }  /* [67] AVN1S01_Tx_CDC_VCAN_BUS */
    ,{ 0x40000386UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE024 }  /* [68] AVN1S03_Tx_CDC_VCAN_BUS */
    ,{ 0x40000387UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE024 }  /* [69] AVN1S05_Tx_CDC_VCAN_BUS */
    ,{ 0x40000388UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE024 }  /* [70] AVN1S06_Tx_CDC_VCAN_BUS */
    ,{ 0x40000389UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE024 }  /* [71] AVN1S08_Tx_CDC_VCAN_BUS */
    ,{ 0x4000038EUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE024 }  /* [72] AVN1S04_Tx_CDC_VCAN_BUS */
    ,{ 0x4000038FUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE025 }  /* [73] AVN1S07_Tx_CDC_VCAN_BUS */
    ,{ 0x400003A6UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE025 }  /* [74] AVN1S46_Tx_CDC_VCAN_BUS */
    ,{ 0x400003A7UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE026 }  /* [75] AVN1S47_Tx_CDC_VCAN_BUS */
    ,{ 0x400003A8UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE026 }  /* [76] AVN1S70_Tx_CDC_VCAN_BUS */
    ,{ 0x400003C0UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE026 }  /* [77] AVN1S99_Tx_CDC_VCAN_BUS */
    ,{ 0x400003C2UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE027 }  /* [78] AVN1SA9_Tx_CDC_VCAN_BUS */
    ,{ 0x400003C4UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE028 }  /* [79] AVN1S78_Tx_CDC_VCAN_BUS */
    ,{ 0x400003C9UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE028 }  /* [80] AVN1S63_Tx_CDC_VCAN_BUS */
    ,{ 0x400003D0UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE028 }  /* [81] AVN1S76_Tx_CDC_VCAN_BUS */
    ,{ 0x400003D9UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE028 }  /* [82] AVN1S97_Tx_CDC_VCAN_BUS */
    ,{ 0x400003E4UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE029 }  /* [83] AVN1S98_Tx_CDC_VCAN_BUS */
    ,{ 0x400003E6UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE030 }  /* [84] AVN1S11_Tx_CDC_VCAN_BUS */
    ,{ 0x400003F1UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE031 }  /* [85] AVN1SA8_Tx_CDC_VCAN_BUS */
    ,{ 0x400003F2UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE031 }  /* [86] AVN1SB6_Tx_CDC_VCAN_BUS */
    ,{ 0x400003FDUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE030 }  /* [87] AVN1S77_Tx_CDC_VCAN_BUS */
    ,{ 0x4000040EUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE031 }  /* [88] AVN1SB1_Tx_CDC_VCAN_BUS */
    ,{ 0x4000042EUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE032 }  /* [89] AVN1S33_Tx_CDC_VCAN_BUS */
    ,{ 0x40000434UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE033 }  /* [90] AVN1S20_Tx_CDC_VCAN_BUS */
    ,{ 0x40000435UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE034 }  /* [91] AVN1S21_Tx_CDC_VCAN_BUS */
    ,{ 0x40000436UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE034 }  /* [92] AVN1S22_Tx_CDC_VCAN_BUS */
    ,{ 0x40000437UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE034 }  /* [93] AVN1S23_Tx_CDC_VCAN_BUS */
    ,{ 0x4000043EUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE034 }  /* [94] AVN1SG5_Tx_CDC_VCAN_BUS */
    ,{ 0x40000490UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE035 }  /* [95] AVN1S64_Tx_CDC_VCAN_BUS */
    ,{ 0x40000515UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE036 }  /* [96] AVN1SB3_Tx_CDC_VCAN_BUS */
    ,{ 0x4000051AUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE037 }  /* [97] AVN1SB4_Tx_CDC_VCAN_BUS */
    ,{ 0x4000051BUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE038 }  /* [98] AVN1SB5_Tx_CDC_VCAN_BUS */
    ,{ 0x4000051DUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE037 }  /* [99] AVN1S44_Tx_CDC_VCAN_BUS */
    ,{ 0x4000051FUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE037 }  /* [100] AVN1S65_Tx_CDC_VCAN_BUS */
    ,{ 0x40000521UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE038 }  /* [101] AVN1S69_Tx_CDC_VCAN_BUS */
    ,{ 0x4000052AUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE039 }  /* [102] AVN1S66_Tx_CDC_VCAN_BUS */
    ,{ 0x4000058AUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE040 }  /* [103] AVN1S39_Tx_CDC_VCAN_BUS */
    ,{ 0x4000060CUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE041 }  /* [104] AVN1SG6_Tx_CDC_VCAN_BUS */
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
    ,{ 0x400004BCUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [1] ABG1D51_Rx_CDC_VCAN_BUS */
    ,{ 0x400003B1UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [2] ABG1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x400001D8UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [3] ABG1S04_Rx_CDC_VCAN_BUS */
    ,{ 0x400001D6UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [4] ABG1S09_Rx_CDC_VCAN_BUS */
    ,{ 0x400004B8UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [5] ACN1D50_Rx_CDC_VCAN_BUS */
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
    ,{ 0x4000020AUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [18] ADC1S17_Rx_CDC_VCAN_BUS */
    ,{ 0x40000613UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [19] ADC1S19_Rx_CDC_VCAN_BUS */
    ,{ 0x400001C7UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [20] ADC1S20_Rx_CDC_VCAN_BUS */
    ,{ 0x4000020BUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [21] ADC1S23_Rx_CDC_VCAN_BUS */
    ,{ 0x40000144UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [22] ADC1S27_Rx_CDC_VCAN_BUS */
    ,{ 0x400001C0UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [23] ADC1S31_Rx_CDC_VCAN_BUS */
    ,{ 0x40000247UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [24] ADU1S02_Rx_CDC_VCAN_BUS */
    ,{ 0x400001F5UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [25] ADU1S03_Rx_CDC_VCAN_BUS */
    ,{ 0x400001F0UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [26] ADU1S05_Rx_CDC_VCAN_BUS */
    ,{ 0x4000022EUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [27] ADU1S06_Rx_CDC_VCAN_BUS */
    ,{ 0x4000020EUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [28] ADU1S07_Rx_CDC_VCAN_BUS */
    ,{ 0x40000161UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [29] ADU1S18_Rx_CDC_VCAN_BUS */
    ,{ 0x40000162UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [30] ADU1S19_Rx_CDC_VCAN_BUS */
    ,{ 0x40000163UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [31] ADU1S20_Rx_CDC_VCAN_BUS */
    ,{ 0x40000166UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [32] ADU1S21_Rx_CDC_VCAN_BUS */
    ,{ 0x40000167UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [33] ADU1S22_Rx_CDC_VCAN_BUS */
    ,{ 0x40000168UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [34] ADU1S23_Rx_CDC_VCAN_BUS */
    ,{ 0x40000169UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [35] ADU1S24_Rx_CDC_VCAN_BUS */
    ,{ 0x4000016AUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [36] ADU1S25_Rx_CDC_VCAN_BUS */
    ,{ 0x4000016BUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [37] ADU1S26_Rx_CDC_VCAN_BUS */
    ,{ 0x4000016CUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [38] ADU1S27_Rx_CDC_VCAN_BUS */
    ,{ 0x4000016DUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [39] ADU1S28_Rx_CDC_VCAN_BUS */
    ,{ 0x40000214UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [40] BAT1E41_Rx_CDC_VCAN_BUS */
    ,{ 0x4000016EUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [41] BAT1E45_Rx_CDC_VCAN_BUS */
    ,{ 0x4000026EUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [42] BAT1ED1_Rx_CDC_VCAN_BUS */
    ,{ 0x400000F3UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [43] BAT1ED4_Rx_CDC_VCAN_BUS */
    ,{ 0x400001BAUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [44] BAT1ED5_Rx_CDC_VCAN_BUS */
    ,{ 0x400001EFUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [45] BAT1EDA_Rx_CDC_VCAN_BUS */
    ,{ 0x40000272UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [46] BAT1EDB_Rx_CDC_VCAN_BUS */
    ,{ 0x400003E5UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [47] BAT1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x40000124UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [48] BAT1S08_Rx_CDC_VCAN_BUS */
    ,{ 0x40000279UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [49] BAT2ED2_Rx_CDC_VCAN_BUS */
    ,{ 0x40000379UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [50] BCC1S05_Rx_CDC_VCAN_BUS */
    ,{ 0x400003F3UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [51] BCC1S06_Rx_CDC_VCAN_BUS */
    ,{ 0x4000038BUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [52] BDB1F01_Rx_CDC_VCAN_BUS */
    ,{ 0x400001F4UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [53] BDB1F03_Rx_CDC_VCAN_BUS */
    ,{ 0x400001CFUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [54] BDB1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x40000624UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [55] BDB1S08_Rx_CDC_VCAN_BUS */
    ,{ 0x40000626UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [56] BDB1S10_Rx_CDC_VCAN_BUS */
    ,{ 0x400003FCUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [57] BDB1S19_Rx_CDC_VCAN_BUS */
    ,{ 0x40000306UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [58] BDB1S25_Rx_CDC_VCAN_BUS */
    ,{ 0x40000305UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [59] BDB1S26_Rx_CDC_VCAN_BUS */
    ,{ 0x40000629UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [60] BDB1S27_Rx_CDC_VCAN_BUS */
    ,{ 0x4000062AUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [61] BDB1S28_Rx_CDC_VCAN_BUS */
    ,{ 0x40000397UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [62] BDB1S29_Rx_CDC_VCAN_BUS */
    ,{ 0x400003B5UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [63] BDB1S35_Rx_CDC_VCAN_BUS */
    ,{ 0x400003B8UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [64] BDB1S36_Rx_CDC_VCAN_BUS */
    ,{ 0x40000320UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [65] BDC1S14_Rx_CDC_VCAN_BUS */
    ,{ 0x4000032AUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [66] BDC1S16_Rx_CDC_VCAN_BUS */
    ,{ 0x4000037CUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [67] BDC1S22_Rx_CDC_VCAN_BUS */
    ,{ 0x40000186UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [68] BDC1S30_Rx_CDC_VCAN_BUS */
    ,{ 0x40000148UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [69] BDC1S41_Rx_CDC_VCAN_BUS */
    ,{ 0x40000337UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [70] BDC1S48_Rx_CDC_VCAN_BUS */
    ,{ 0x400001E3UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [71] BDC1S81_Rx_CDC_VCAN_BUS */
    ,{ 0x40000367UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [72] BDC1S83_Rx_CDC_VCAN_BUS */
    ,{ 0x40000355UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [73] BDC1S97_Rx_CDC_VCAN_BUS */
    ,{ 0x40000358UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [74] BDC1S98_Rx_CDC_VCAN_BUS */
    ,{ 0x4000035DUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [75] BDC1S99_Rx_CDC_VCAN_BUS */
    ,{ 0x400001A4UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [76] BDC1SA0_Rx_CDC_VCAN_BUS */
    ,{ 0x4000035FUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [77] BDC1SA1_Rx_CDC_VCAN_BUS */
    ,{ 0x40000393UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [78] BDC1SC1_Rx_CDC_VCAN_BUS */
    ,{ 0x40000395UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [79] BDC1SC2_Rx_CDC_VCAN_BUS */
    ,{ 0x40000396UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [80] BDC1SC3_Rx_CDC_VCAN_BUS */
    ,{ 0x4000039AUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [81] BDC1SC4_Rx_CDC_VCAN_BUS */
    ,{ 0x4000039BUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [82] BDC1SC5_Rx_CDC_VCAN_BUS */
    ,{ 0x4000039DUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [83] BDC1SC6_Rx_CDC_VCAN_BUS */
    ,{ 0x4000039EUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [84] BDC1SC7_Rx_CDC_VCAN_BUS */
    ,{ 0x4000039FUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [85] BDC1SC8_Rx_CDC_VCAN_BUS */
    ,{ 0x400003A5UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [86] BDC1SC9_Rx_CDC_VCAN_BUS */
    ,{ 0x400003ACUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [87] BDC1SD1_Rx_CDC_VCAN_BUS */
    ,{ 0x400003AEUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [88] BDC1SD2_Rx_CDC_VCAN_BUS */
    ,{ 0x400003B2UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [89] BDC1SD3_Rx_CDC_VCAN_BUS */
    ,{ 0x400003B3UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [90] BDC1SD4_Rx_CDC_VCAN_BUS */
    ,{ 0x400003B9UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [91] BDC1SD5_Rx_CDC_VCAN_BUS */
    ,{ 0x400003BCUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [92] BDC1SD6_Rx_CDC_VCAN_BUS */
    ,{ 0x400003C6UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [93] BDC1SD7_Rx_CDC_VCAN_BUS */
    ,{ 0x400003C7UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [94] BDC1SD8_Rx_CDC_VCAN_BUS */
    ,{ 0x400003CDUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [95] BDC1SD9_Rx_CDC_VCAN_BUS */
    ,{ 0x400003D3UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [96] BDC1SE1_Rx_CDC_VCAN_BUS */
    ,{ 0x400003D6UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [97] BDC1SE2_Rx_CDC_VCAN_BUS */
    ,{ 0x400003DDUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [98] BDC1SE3_Rx_CDC_VCAN_BUS */
    ,{ 0x400003E1UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [99] BDC1SE4_Rx_CDC_VCAN_BUS */
    ,{ 0x400003EBUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [100] BDC1SE5_Rx_CDC_VCAN_BUS */
    ,{ 0x400003EFUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [101] BDC1SE6_Rx_CDC_VCAN_BUS */
    ,{ 0x400003F5UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [102] BDC1SE7_Rx_CDC_VCAN_BUS */
    ,{ 0x40000423UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [103] BDC1SE8_Rx_CDC_VCAN_BUS */
    ,{ 0x40000429UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [104] BDC1SE9_Rx_CDC_VCAN_BUS */
    ,{ 0x40000430UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [105] BDC1SF1_Rx_CDC_VCAN_BUS */
    ,{ 0x40000480UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [106] BDC1SF2_Rx_CDC_VCAN_BUS */
    ,{ 0x40000484UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [107] BDC1SF3_Rx_CDC_VCAN_BUS */
    ,{ 0x40000491UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [108] BDC1SF4_Rx_CDC_VCAN_BUS */
    ,{ 0x40000497UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [109] BDC1SF6_Rx_CDC_VCAN_BUS */
    ,{ 0x40000526UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [110] BDC1SG4_Rx_CDC_VCAN_BUS */
    ,{ 0x4000052BUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [111] BDC1SG6_Rx_CDC_VCAN_BUS */
    ,{ 0x4000052CUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [112] BDC1SG7_Rx_CDC_VCAN_BUS */
    ,{ 0x40000530UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [113] BDC1SG8_Rx_CDC_VCAN_BUS */
    ,{ 0x40000531UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [114] BDC1SG9_Rx_CDC_VCAN_BUS */
    ,{ 0x40000534UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [115] BDC1SH3_Rx_CDC_VCAN_BUS */
    ,{ 0x40000535UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [116] BDC1SH4_Rx_CDC_VCAN_BUS */
    ,{ 0x40000537UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [117] BDC1SH5_Rx_CDC_VCAN_BUS */
    ,{ 0x40000538UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [118] BDC1SH6_Rx_CDC_VCAN_BUS */
    ,{ 0x400002B3UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [119] BDC1SH8_Rx_CDC_VCAN_BUS */
    ,{ 0x4000037BUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [120] BDF3S01_Rx_CDC_VCAN_BUS */
    ,{ 0x4000018DUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [121] BDF3S02_Rx_CDC_VCAN_BUS */
    ,{ 0x4000019AUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [122] BDR3S02_Rx_CDC_VCAN_BUS */
    ,{ 0x400003F6UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [123] BSR1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x40000235UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [124] BSR1S02_Rx_CDC_VCAN_BUS */
    ,{ 0x400002AFUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [125] BSR1S03_Rx_CDC_VCAN_BUS */
    ,{ 0x400001D9UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [126] CMB1S03_Rx_CDC_VCAN_BUS */
    ,{ 0x400002F3UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [127] CMB1S04_Rx_CDC_VCAN_BUS */
    ,{ 0x4000043AUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [128] CSR1S04_Rx_CDC_VCAN_BUS */
    ,{ 0x400003DBUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [129] CSR1S07_Rx_CDC_VCAN_BUS */
    ,{ 0x40000438UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [130] DCM1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x4000034FUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [131] DCM1S03_Rx_CDC_VCAN_BUS */
    ,{ 0x40000363UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [132] DCM1S04_Rx_CDC_VCAN_BUS */
    ,{ 0x4000027DUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [133] DDM1S00_Rx_CDC_VCAN_BUS */
    ,{ 0x4000012BUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [134] DDM1S09_Rx_CDC_VCAN_BUS */
    ,{ 0x400002EEUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [135] DDM1S16_Rx_CDC_VCAN_BUS */
    ,{ 0x400002DAUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [136] DDM1S20_Rx_CDC_VCAN_BUS */
    ,{ 0x40000219UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [137] DDM1S32_Rx_CDC_VCAN_BUS */
    ,{ 0x400002E5UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [138] DDM1S35_Rx_CDC_VCAN_BUS */
    ,{ 0x40000281UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [139] DDM1SFG_Rx_CDC_VCAN_BUS */
    ,{ 0x40000282UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [140] DDM1SFH_Rx_CDC_VCAN_BUS */
    ,{ 0x40000528UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [141] DKY1S26_Rx_CDC_VCAN_BUS */
    ,{ 0x40000285UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [142] DS11S27_Rx_CDC_VCAN_BUS */
    ,{ 0x40000317UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [143] DS11S37_Rx_CDC_VCAN_BUS */
    ,{ 0x40000608UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [144] DS11S40_Rx_CDC_VCAN_BUS */
    ,{ 0x40000411UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [145] DS12F02_Rx_CDC_VCAN_BUS */
    ,{ 0x40000412UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [146] DS12F03_Rx_CDC_VCAN_BUS */
    ,{ 0x400003F0UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [147] DST1S02_Rx_CDC_VCAN_BUS */
    ,{ 0x400004A0UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [148] EBU1D01_Rx_CDC_VCAN_BUS */
    ,{ 0x400003BFUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [149] ECT1G01_Rx_CDC_VCAN_BUS */
    ,{ 0x400001BCUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [150] EHV1E96_Rx_CDC_VCAN_BUS */
    ,{ 0x4000007EUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [151] EHV1F02_Rx_CDC_VCAN_BUS */
    ,{ 0x400002A7UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [152] EHV1G70_Rx_CDC_VCAN_BUS */
    ,{ 0x400002A8UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [153] EHV1G71_Rx_CDC_VCAN_BUS */
    ,{ 0x400001D0UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [154] EHV1S23_Rx_CDC_VCAN_BUS */
    ,{ 0x4000042FUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [155] EHV1S26_Rx_CDC_VCAN_BUS */
    ,{ 0x40000325UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [156] EHV1S31_Rx_CDC_VCAN_BUS */
    ,{ 0x4000040BUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [157] EHV1S95_Rx_CDC_VCAN_BUS */
    ,{ 0x4000042BUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [158] EHV1S97_Rx_CDC_VCAN_BUS */
    ,{ 0x400002EBUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [159] EHV1SL2_Rx_CDC_VCAN_BUS */
    ,{ 0x40000075UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [160] EHV2G10_Rx_CDC_VCAN_BUS */
    ,{ 0x400000A1UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [161] EHV2G20_Rx_CDC_VCAN_BUS */
    ,{ 0x40000335UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [162] EIM1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x400005F3UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [163] ENG1C01_Rx_CDC_VCAN_BUS */
    ,{ 0x400005F4UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [164] ENG1C02_Rx_CDC_VCAN_BUS */
    ,{ 0x40000499UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [165] ENG1D51_Rx_CDC_VCAN_BUS */
    ,{ 0x4000049AUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [166] ENG1D52_Rx_CDC_VCAN_BUS */
    ,{ 0x4000049BUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [167] ENG1D53_Rx_CDC_VCAN_BUS */
    ,{ 0x4000049DUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [168] ENG1D55_Rx_CDC_VCAN_BUS */
    ,{ 0x400004A8UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [169] ENG1D56_Rx_CDC_VCAN_BUS */
    ,{ 0x400004AEUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [170] ENG1D59_Rx_CDC_VCAN_BUS */
    ,{ 0x400004AFUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [171] ENG1D60_Rx_CDC_VCAN_BUS */
    ,{ 0x400001C5UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [172] ENG1G13_Rx_CDC_VCAN_BUS */
    ,{ 0x4000051EUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [173] ENG1G90_Rx_CDC_VCAN_BUS */
    ,{ 0x40000589UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [174] ENG1S60_Rx_CDC_VCAN_BUS */
    ,{ 0x400004A3UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [175] EPS1D50_Rx_CDC_VCAN_BUS */
    ,{ 0x400005F6UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [176] FCM1C01_Rx_CDC_VCAN_BUS */
    ,{ 0x400005F1UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [177] FCM1C03_Rx_CDC_VCAN_BUS */
    ,{ 0x40000489UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [178] FCM1S10_Rx_CDC_VCAN_BUS */
    ,{ 0x4000048BUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [179] FCM1S12_Rx_CDC_VCAN_BUS */
    ,{ 0x40000251UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [180] FCM1S39_Rx_CDC_VCAN_BUS */
    ,{ 0x40000261UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [181] FCM1S41_Rx_CDC_VCAN_BUS */
    ,{ 0x40000274UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [182] FCM1S49_Rx_CDC_VCAN_BUS */
    ,{ 0x40000275UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [183] FCM1S51_Rx_CDC_VCAN_BUS */
    ,{ 0x40000276UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [184] FCM1S52_Rx_CDC_VCAN_BUS */
    ,{ 0x4000028AUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [185] FCM1S66_Rx_CDC_VCAN_BUS */
    ,{ 0x4000025AUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [186] FCM1S70_Rx_CDC_VCAN_BUS */
    ,{ 0x40000159UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [187] FCM1S76_Rx_CDC_VCAN_BUS */
    ,{ 0x40000100UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [188] FCM1S79_Rx_CDC_VCAN_BUS */
    ,{ 0x4000020FUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [189] FCM1S88_Rx_CDC_VCAN_BUS */
    ,{ 0x400001B2UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [190] FCM1S90_Rx_CDC_VCAN_BUS */
    ,{ 0x400000A8UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [191] FCM1S95_Rx_CDC_VCAN_BUS */
    ,{ 0x400003FBUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [192] IDT1S07_Rx_CDC_VCAN_BUS */
    ,{ 0x4000014BUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [193] IDT1S08_Rx_CDC_VCAN_BUS */
    ,{ 0x40000532UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [194] IDT1S15_Rx_CDC_VCAN_BUS */
    ,{ 0x4000043BUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [195] IPA1S05_Rx_CDC_VCAN_BUS */
    ,{ 0x400003DEUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [196] ITS1S04_Rx_CDC_VCAN_BUS */
    ,{ 0x4000027BUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [197] ITS1S08_Rx_CDC_VCAN_BUS */
    ,{ 0x40000173UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [198] LRS1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x40000179UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [199] LRS1S03_Rx_CDC_VCAN_BUS */
    ,{ 0x4000017AUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [200] LRS1S04_Rx_CDC_VCAN_BUS */
    ,{ 0x40000494UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [201] LVN1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x40000315UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [202] MET1S33_Rx_CDC_VCAN_BUS */
    ,{ 0x40000524UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [203] MET1S38_Rx_CDC_VCAN_BUS */
    ,{ 0x400001DCUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [204] MET1S47_Rx_CDC_VCAN_BUS */
    ,{ 0x400001F7UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [205] MET1S55_Rx_CDC_VCAN_BUS */
    ,{ 0x40000049UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [206] MGC1F13_Rx_CDC_VCAN_BUS */
    ,{ 0x400001CCUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [207] PDC1G01_Rx_CDC_VCAN_BUS */
    ,{ 0x40000507UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [208] PDC1G02_Rx_CDC_VCAN_BUS */
    ,{ 0x40000295UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [209] PLG1G15_Rx_CDC_VCAN_BUS */
    ,{ 0x40000296UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [210] PLG1G16_Rx_CDC_VCAN_BUS */
    ,{ 0x40000422UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [211] PLG1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x40000432UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [212] PLG1S06_Rx_CDC_VCAN_BUS */
    ,{ 0x400002A6UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [213] PLG1S20_Rx_CDC_VCAN_BUS */
    ,{ 0x40000204UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [214] PLG1S21_Rx_CDC_VCAN_BUS */
    ,{ 0x40000403UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [215] PST1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x40000405UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [216] PST1S02_Rx_CDC_VCAN_BUS */
    ,{ 0x400002B2UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [217] PWC1S41_Rx_CDC_VCAN_BUS */
    ,{ 0x4000014DUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [218] RCP1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x40000230UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [219] RCP1S02_Rx_CDC_VCAN_BUS */
    ,{ 0x4000014FUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [220] RCP1S03_Rx_CDC_VCAN_BUS */
    ,{ 0x40000182UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [221] RRS1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x40000189UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [222] RRS1S03_Rx_CDC_VCAN_BUS */
    ,{ 0x4000018CUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [223] RRS1S04_Rx_CDC_VCAN_BUS */
    ,{ 0x4000032FUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [224] RSE1G24_Rx_CDC_VCAN_BUS */
    ,{ 0x40000336UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [225] RSE1G25_Rx_CDC_VCAN_BUS */
    ,{ 0x4000034DUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [226] RSE1G26_Rx_CDC_VCAN_BUS */
    ,{ 0x40000385UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [227] RSE1G29_Rx_CDC_VCAN_BUS */
    ,{ 0x400003C8UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [228] RSE1S02_Rx_CDC_VCAN_BUS */
    ,{ 0x40000328UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [229] RST1S03_Rx_CDC_VCAN_BUS */
    ,{ 0x40000439UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [230] SCN1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x4000010BUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [231] SCS1S10_Rx_CDC_VCAN_BUS */
    ,{ 0x400002FDUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [232] SCS1S11_Rx_CDC_VCAN_BUS */
    ,{ 0x400002FEUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [233] SCS1S14_Rx_CDC_VCAN_BUS */
    ,{ 0x4000040CUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [234] SOL1S02_Rx_CDC_VCAN_BUS */
    ,{ 0x4000040DUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [235] SOL1S03_Rx_CDC_VCAN_BUS */
    ,{ 0x400001EBUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [236] SOL1S04_Rx_CDC_VCAN_BUS */
    ,{ 0x400001EAUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [237] SOL1S05_Rx_CDC_VCAN_BUS */
    ,{ 0x40000495UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [238] TPM1S02_Rx_CDC_VCAN_BUS */
    ,{ 0x40000496UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [239] TPM1S03_Rx_CDC_VCAN_BUS */
    ,{ 0x40000347UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [240] TPM1S04_Rx_CDC_VCAN_BUS */
    ,{ 0x4000034CUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [241] TPM1S05_Rx_CDC_VCAN_BUS */
    ,{ 0x40000417UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [242] TPM1S06_Rx_CDC_VCAN_BUS */
    ,{ 0x40000418UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [243] TPM1S08_Rx_CDC_VCAN_BUS */
    ,{ 0x40000426UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [244] TPM1S09_Rx_CDC_VCAN_BUS */
    ,{ 0x40000428UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [245] TPM1S10_Rx_CDC_VCAN_BUS */
    ,{ 0x4000042AUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [246] TPM1S11_Rx_CDC_VCAN_BUS */
    ,{ 0x4000042CUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [247] TPM1S12_Rx_CDC_VCAN_BUS */
    ,{ 0x400002A0UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [248] TRA1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x400000A0UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [249] TRA1S02_Rx_CDC_VCAN_BUS */
    ,{ 0x400003E7UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [250] UCB1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x400004A4UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [251] VGR1D50_Rx_CDC_VCAN_BUS */
    ,{ 0x400004A1UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [252] VSC1D51_Rx_CDC_VCAN_BUS */
    ,{ 0x4000009EUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [253] VSC1G13_Rx_CDC_VCAN_BUS */
    ,{ 0x400000B7UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [254] VSC1G14_Rx_CDC_VCAN_BUS */
    ,{ 0x400002F9UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [255] WIP1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x4000027EUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [256] YGW1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x40000086UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [257] ZN11S08_Rx_CDC_VCAN_BUS */
    ,{ 0x400001DEUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [258] ZN11S14_Rx_CDC_VCAN_BUS */
    ,{ 0x40000368UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [259] ZN11S19_Rx_CDC_VCAN_BUS */
    ,{ 0x40000398UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [260] ZN11S25_Rx_CDC_VCAN_BUS */
    ,{ 0x4000036AUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [261] ZN11S26_Rx_CDC_VCAN_BUS */
    ,{ 0x4000039CUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [262] ZN11S32_Rx_CDC_VCAN_BUS */
    ,{ 0x4000036EUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [263] ZN11S60_Rx_CDC_VCAN_BUS */
    ,{ 0x4000033FUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [264] ZN11S63_Rx_CDC_VCAN_BUS */
    ,{ 0x400003D2UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [265] ZN11S64_Rx_CDC_VCAN_BUS */
    ,{ 0x400003F9UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [266] ZN11S65_Rx_CDC_VCAN_BUS */
    ,{ 0x40000400UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [267] ZN11S66_Rx_CDC_VCAN_BUS */
    ,{ 0x40000404UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [268] ZN11S67_Rx_CDC_VCAN_BUS */
    ,{ 0x40000350UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [269] ZN11SF6_Rx_CDC_VCAN_BUS */
    ,{ 0x40000352UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [270] ZN11SF7_Rx_CDC_VCAN_BUS */
    ,{ 0x40000353UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [271] ZN11SF8_Rx_CDC_VCAN_BUS */
    ,{ 0x400003BBUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [272] ZN11SF9_Rx_CDC_VCAN_BUS */
    ,{ 0x40000390UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [273] ZN21S13_Rx_CDC_VCAN_BUS */
    ,{ 0x400001BEUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [274] ZN21S28_Rx_CDC_VCAN_BUS */
    ,{ 0x400003A9UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [275] ZN21S72_Rx_CDC_VCAN_BUS */
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
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [44] AVN1SG8_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [45] AVN1SG9_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [46] AVN1SC9_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [47] AVN1SD1_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [48] AVN1SD2_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [49] AVN1SD3_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [50] AVN1SD5_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [51] AVN1SF7_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [52] AVN1SF8_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [53] AVN1SF9_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [54] AVN1SG1_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [55] AVN1S67_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [56] AVN1S68_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [57] AVN1SB2_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [58] AVN1S30_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [59] AVN1SA1_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [60] AVN1SG4_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [61] AVN1SG3_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [62] AVN1S94_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [63] AVN1S95_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [64] AVN1S61_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [65] AVN1SA7_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [66] AVN1S62_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [67] AVN1S01_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [68] AVN1S03_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [69] AVN1S05_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [70] AVN1S06_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [71] AVN1S08_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [72] AVN1S04_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [73] AVN1S07_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [74] AVN1S46_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [75] AVN1S47_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [76] AVN1S70_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [77] AVN1S99_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [78] AVN1SA9_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [79] AVN1S78_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [80] AVN1S63_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [81] AVN1S76_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [82] AVN1S97_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [83] AVN1S98_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [84] AVN1S11_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [85] AVN1SA8_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [86] AVN1SB6_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [87] AVN1S77_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [88] AVN1SB1_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [89] AVN1S33_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [90] AVN1S20_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [91] AVN1S21_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [92] AVN1S22_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [93] AVN1S23_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [94] AVN1SG5_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [95] AVN1S64_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [96] AVN1SB3_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [97] AVN1SB4_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [98] AVN1SB5_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [99] AVN1S44_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [100] AVN1S65_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [101] AVN1S69_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [102] AVN1S66_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [103] AVN1S39_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [104] AVN1SG6_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [105] ABG1D50_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [106] ABG1D51_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [107] ABG1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [108] ABG1S04_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [109] ABG1S09_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [110] ACN1D50_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [111] ACN1S03_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [112] ACN1S04_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [113] ACN1S05_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [114] ACN1S07_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [115] ACN1S15_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [116] ACN1S16_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [117] ACN1S22_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [118] ACN1S25_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [119] ACN1S29_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [120] ADC1S06_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [121] ADC1S13_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [122] ADC1S14_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [123] ADC1S17_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [124] ADC1S19_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [125] ADC1S20_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [126] ADC1S23_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [127] ADC1S27_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [128] ADC1S31_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [129] ADU1S02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [130] ADU1S03_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [131] ADU1S05_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [132] ADU1S06_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [133] ADU1S07_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [134] ADU1S18_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [135] ADU1S19_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [136] ADU1S20_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [137] ADU1S21_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [138] ADU1S22_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [139] ADU1S23_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [140] ADU1S24_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [141] ADU1S25_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [142] ADU1S26_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [143] ADU1S27_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [144] ADU1S28_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [145] BAT1E41_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [146] BAT1E45_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [147] BAT1ED1_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [148] BAT1ED4_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [149] BAT1ED5_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [150] BAT1EDA_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [151] BAT1EDB_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [152] BAT1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [153] BAT1S08_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [154] BAT2ED2_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [155] BCC1S05_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [156] BCC1S06_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [157] BDB1F01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [158] BDB1F03_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [159] BDB1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [160] BDB1S08_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [161] BDB1S10_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [162] BDB1S19_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [163] BDB1S25_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [164] BDB1S26_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [165] BDB1S27_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [166] BDB1S28_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [167] BDB1S29_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [168] BDB1S35_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [169] BDB1S36_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [170] BDC1S14_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [171] BDC1S16_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [172] BDC1S22_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [173] BDC1S30_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [174] BDC1S41_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [175] BDC1S48_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [176] BDC1S81_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [177] BDC1S83_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [178] BDC1S97_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [179] BDC1S98_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [180] BDC1S99_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [181] BDC1SA0_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [182] BDC1SA1_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [183] BDC1SC1_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [184] BDC1SC2_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [185] BDC1SC3_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [186] BDC1SC4_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [187] BDC1SC5_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [188] BDC1SC6_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [189] BDC1SC7_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [190] BDC1SC8_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [191] BDC1SC9_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [192] BDC1SD1_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [193] BDC1SD2_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [194] BDC1SD3_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [195] BDC1SD4_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [196] BDC1SD5_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [197] BDC1SD6_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [198] BDC1SD7_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [199] BDC1SD8_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [200] BDC1SD9_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [201] BDC1SE1_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [202] BDC1SE2_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [203] BDC1SE3_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [204] BDC1SE4_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [205] BDC1SE5_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [206] BDC1SE6_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [207] BDC1SE7_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [208] BDC1SE8_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [209] BDC1SE9_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [210] BDC1SF1_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [211] BDC1SF2_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [212] BDC1SF3_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [213] BDC1SF4_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [214] BDC1SF6_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [215] BDC1SG4_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [216] BDC1SG6_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [217] BDC1SG7_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [218] BDC1SG8_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [219] BDC1SG9_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [220] BDC1SH3_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [221] BDC1SH4_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [222] BDC1SH5_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [223] BDC1SH6_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [224] BDC1SH8_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [225] BDF3S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [226] BDF3S02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [227] BDR3S02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [228] BSR1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [229] BSR1S02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [230] BSR1S03_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [231] CMB1S03_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [232] CMB1S04_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [233] CSR1S04_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [234] CSR1S07_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [235] DCM1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [236] DCM1S03_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [237] DCM1S04_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [238] DDM1S00_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [239] DDM1S09_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [240] DDM1S16_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [241] DDM1S20_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [242] DDM1S32_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [243] DDM1S35_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [244] DDM1SFG_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [245] DDM1SFH_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [246] DKY1S26_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [247] DS11S27_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [248] DS11S37_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [249] DS11S40_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [250] DS12F02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [251] DS12F03_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [252] DST1S02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [253] EBU1D01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [254] ECT1G01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [255] EHV1E96_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [256] EHV1F02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [257] EHV1G70_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [258] EHV1G71_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [259] EHV1S23_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [260] EHV1S26_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [261] EHV1S31_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [262] EHV1S95_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [263] EHV1S97_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [264] EHV1SL2_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [265] EHV2G10_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [266] EHV2G20_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [267] EIM1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [268] ENG1C01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [269] ENG1C02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [270] ENG1D51_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [271] ENG1D52_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [272] ENG1D53_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [273] ENG1D55_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [274] ENG1D56_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [275] ENG1D59_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [276] ENG1D60_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [277] ENG1G13_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [278] ENG1G90_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [279] ENG1S60_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [280] EPS1D50_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [281] FCM1C01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [282] FCM1C03_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [283] FCM1S10_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [284] FCM1S12_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [285] FCM1S39_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [286] FCM1S41_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [287] FCM1S49_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [288] FCM1S51_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [289] FCM1S52_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [290] FCM1S66_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [291] FCM1S70_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [292] FCM1S76_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [293] FCM1S79_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [294] FCM1S88_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [295] FCM1S90_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [296] FCM1S95_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [297] IDT1S07_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [298] IDT1S08_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [299] IDT1S15_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [300] IPA1S05_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [301] ITS1S04_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [302] ITS1S08_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [303] LRS1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [304] LRS1S03_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [305] LRS1S04_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [306] LVN1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [307] MET1S33_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [308] MET1S38_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [309] MET1S47_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [310] MET1S55_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [311] MGC1F13_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [312] PDC1G01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [313] PDC1G02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [314] PLG1G15_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [315] PLG1G16_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [316] PLG1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [317] PLG1S06_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [318] PLG1S20_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [319] PLG1S21_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [320] PST1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [321] PST1S02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [322] PWC1S41_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [323] RCP1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [324] RCP1S02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [325] RCP1S03_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [326] RRS1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [327] RRS1S03_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [328] RRS1S04_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [329] RSE1G24_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [330] RSE1G25_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [331] RSE1G26_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [332] RSE1G29_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [333] RSE1S02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [334] RST1S03_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [335] SCN1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [336] SCS1S10_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [337] SCS1S11_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [338] SCS1S14_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [339] SOL1S02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [340] SOL1S03_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [341] SOL1S04_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [342] SOL1S05_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [343] TPM1S02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [344] TPM1S03_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [345] TPM1S04_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [346] TPM1S05_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [347] TPM1S06_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [348] TPM1S08_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [349] TPM1S09_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [350] TPM1S10_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [351] TPM1S11_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [352] TPM1S12_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [353] TRA1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [354] TRA1S02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [355] UCB1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [356] VGR1D50_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [357] VSC1D51_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [358] VSC1G13_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [359] VSC1G14_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [360] WIP1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [361] YGW1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [362] ZN11S08_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [363] ZN11S14_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [364] ZN11S19_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [365] ZN11S25_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [366] ZN11S26_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [367] ZN11S32_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [368] ZN11S60_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [369] ZN11S63_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [370] ZN11S64_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [371] ZN11S65_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [372] ZN11S66_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [373] ZN11S67_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [374] ZN11SF6_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [375] ZN11SF7_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [376] ZN11SF8_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [377] ZN11SF9_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [378] ZN21S13_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [379] ZN21S28_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [380] ZN21S72_Rx_CDC_VCAN_BUS */
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
/*  Framework          :v2-0-2                                              */
/*  BSW plug-in        :v3-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
