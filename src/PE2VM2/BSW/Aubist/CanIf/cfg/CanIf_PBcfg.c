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
     { 0x40000384UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE001 }  /* [0] AVN1S01_Tx_VCAN_VCC_1_BUS */
    ,{ 0x40000386UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE001 }  /* [1] AVN1S03_Tx_VCAN_VCC_1_BUS */
    ,{ 0x4000038EUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE000 }  /* [2] AVN1S04_Tx_VCAN_VCC_1_BUS */
    ,{ 0x40000387UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE000 }  /* [3] AVN1S05_Tx_VCAN_VCC_1_BUS */
    ,{ 0x40000388UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE000 }  /* [4] AVN1S06_Tx_VCAN_VCC_1_BUS */
    ,{ 0x4000038FUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE003 }  /* [5] AVN1S07_Tx_VCAN_VCC_1_BUS */
    ,{ 0x40000389UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE003 }  /* [6] AVN1S08_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400003E6UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE001 }  /* [7] AVN1S11_Tx_VCAN_VCC_1_BUS */
    ,{ 0x40000434UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE003 }  /* [8] AVN1S20_Tx_VCAN_VCC_1_BUS */
    ,{ 0x40000435UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE003 }  /* [9] AVN1S21_Tx_VCAN_VCC_1_BUS */
    ,{ 0x40000436UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE003 }  /* [10] AVN1S22_Tx_VCAN_VCC_1_BUS */
    ,{ 0x40000437UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE003 }  /* [11] AVN1S23_Tx_VCAN_VCC_1_BUS */
    ,{ 0x4000031AUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE003 }  /* [12] AVN1S30_Tx_VCAN_VCC_1_BUS */
    ,{ 0x40000121UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE003 }  /* [13] AVN1S38_Tx_VCAN_VCC_1_BUS */
    ,{ 0x4000058AUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE000 }  /* [14] AVN1S39_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400001FCUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE000 }  /* [15] AVN1S40_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400001FDUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE000 }  /* [16] AVN1S41_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400001FEUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE000 }  /* [17] AVN1S42_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400001FFUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE000 }  /* [18] AVN1S43_Tx_VCAN_VCC_1_BUS */
    ,{ 0x4000051DUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE003 }  /* [19] AVN1S44_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400001BDUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE003 }  /* [20] AVN1S52_Tx_VCAN_VCC_1_BUS */
    ,{ 0x4000035BUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE000 }  /* [21] AVN1S62_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400003C9UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE003 }  /* [22] AVN1S63_Tx_VCAN_VCC_1_BUS */
    ,{ 0x40000490UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE003 }  /* [23] AVN1S64_Tx_VCAN_VCC_1_BUS */
    ,{ 0x4000051FUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE003 }  /* [24] AVN1S65_Tx_VCAN_VCC_1_BUS */
    ,{ 0x4000052AUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE003 }  /* [25] AVN1S66_Tx_VCAN_VCC_1_BUS */
    ,{ 0x4000030EUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE003 }  /* [26] AVN1S67_Tx_VCAN_VCC_1_BUS */
    ,{ 0x4000030FUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE003 }  /* [27] AVN1S68_Tx_VCAN_VCC_1_BUS */
    ,{ 0x40000521UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE000 }  /* [28] AVN1S69_Tx_VCAN_VCC_1_BUS */
    ,{ 0x4000014CUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE005 }  /* [29] AVN1S71_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400002AAUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE000 }  /* [30] AVN1S73_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400003C4UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE003 }  /* [31] AVN1S78_Tx_VCAN_VCC_1_BUS */
    ,{ 0x40000345UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE005 }  /* [32] AVN1S94_Tx_VCAN_VCC_1_BUS */
    ,{ 0x40000346UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE005 }  /* [33] AVN1S95_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400003D9UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE001 }  /* [34] AVN1S97_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400003E4UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE003 }  /* [35] AVN1S98_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400003C0UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE005 }  /* [36] AVN1S99_Tx_VCAN_VCC_1_BUS */
    ,{ 0x4000031DUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE003 }  /* [37] AVN1SA1_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400001ECUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE003 }  /* [38] AVN1SA6_Tx_VCAN_VCC_1_BUS */
    ,{ 0x4000035AUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE004 }  /* [39] AVN1SA7_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400003F1UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE002 }  /* [40] AVN1SA8_Tx_VCAN_VCC_1_BUS */
    ,{ 0x4000040EUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE001 }  /* [41] AVN1SB1_Tx_VCAN_VCC_1_BUS */
    ,{ 0x40000313UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE003 }  /* [42] AVN1SB2_Tx_VCAN_VCC_1_BUS */
    ,{ 0x40000515UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE004 }  /* [43] AVN1SB3_Tx_VCAN_VCC_1_BUS */
    ,{ 0x4000051AUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE001 }  /* [44] AVN1SB4_Tx_VCAN_VCC_1_BUS */
    ,{ 0x4000051BUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE001 }  /* [45] AVN1SB5_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400002D2UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE005 }  /* [46] AVN1SB7_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400001F2UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE005 }  /* [47] AVN1SB9_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400002D4UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE007 }  /* [48] AVN1SC1_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400002D5UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE007 }  /* [49] AVN1SC2_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400002D6UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE007 }  /* [50] AVN1SC3_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400002D7UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE007 }  /* [51] AVN1SC4_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400002DFUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE007 }  /* [52] AVN1SC5_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400002E0UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE007 }  /* [53] AVN1SC6_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400002E1UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE007 }  /* [54] AVN1SC7_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400002E2UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE007 }  /* [55] AVN1SC8_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400002EFUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE007 }  /* [56] AVN1SC9_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400002F0UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE007 }  /* [57] AVN1SD1_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400002F2UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE007 }  /* [58] AVN1SD2_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400002F5UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE007 }  /* [59] AVN1SD3_Tx_VCAN_VCC_1_BUS */
    ,{ 0x40000185UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE006 }  /* [60] AVN1SD4_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400002F6UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE003 }  /* [61] AVN1SD5_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400001A1UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE001 }  /* [62] AVN1SD6_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400001A2UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE001 }  /* [63] AVN1SD7_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400001B8UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE001 }  /* [64] AVN1SD8_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400001B9UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE001 }  /* [65] AVN1SD9_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400001B7UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE001 }  /* [66] AVN1SE1_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400001B5UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE001 }  /* [67] AVN1SE2_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400001ADUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE001 }  /* [68] AVN1SE3_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400001AFUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE001 }  /* [69] AVN1SE4_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400001B0UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE001 }  /* [70] AVN1SE5_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400001B3UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE001 }  /* [71] AVN1SE6_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400001B4UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE001 }  /* [72] AVN1SE7_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400001AEUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE001 }  /* [73] AVN1SE8_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400001A8UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE001 }  /* [74] AVN1SE9_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400001A9UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE001 }  /* [75] AVN1SF1_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400001ABUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE001 }  /* [76] AVN1SF2_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400001ACUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE001 }  /* [77] AVN1SF3_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400001A5UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE001 }  /* [78] AVN1SF4_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400001A7UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE001 }  /* [79] AVN1SF5_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400002F7UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE001 }  /* [80] AVN1SF7_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400002F8UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE006 }  /* [81] AVN1SF8_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400002FAUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE006 }  /* [82] AVN1SF9_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400002FBUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE005 }  /* [83] AVN1SG1_Tx_VCAN_VCC_1_BUS */
    ,{ 0x4000033AUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE006 }  /* [84] AVN1SG3_Tx_VCAN_VCC_1_BUS */
    ,{ 0x4000043EUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE006 }  /* [85] AVN1SG5_Tx_VCAN_VCC_1_BUS */
    ,{ 0x4000060CUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE001 }  /* [86] AVN1SG6_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400002E3UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE001 }  /* [87] AVN1SH1_Tx_VCAN_VCC_1_BUS */
    ,{ 0x40000427UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE005 }  /* [88] DMS1S02_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400003EAUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE000 }  /* [89] MET1S27_Tx_VCAN_VCC_1_BUS */
    ,{ 0x4000037EUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE000 }  /* [90] MET1S28_Tx_VCAN_VCC_1_BUS */
    ,{ 0x40000529UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE000 }  /* [91] MET1S43_Tx_VCAN_VCC_1_BUS */
    ,{ 0x40000357UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE001 }  /* [92] MET1S70_Tx_VCAN_VCC_1_BUS */
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
     { 0x400004ACUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [0] ABG1D50_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400004BCUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [1] ABG1D51_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003B1UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [2] ABG1S01_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400001D8UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [3] ABG1S04_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400004B8UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [4] ACN1D50_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003A1UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [5] ACN1S03_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000381UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [6] ACN1S04_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000382UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [7] ACN1S05_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003B0UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [8] ACN1S07_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000407UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [9] ACN1S15_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000408UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [10] ACN1S16_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000354UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [11] ACN1S22_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000255UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [12] ACN1S25_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000506UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [13] ACN1S29_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000594UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [14] ADC1S06_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000207UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [15] ADC1S13_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000208UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [16] ADC1S14_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000020AUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [17] ADC1S17_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000613UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [18] ADC1S19_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400001C7UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [19] ADC1S20_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000020BUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [20] ADC1S23_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400001C0UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [21] ADC1S31_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000247UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [22] ADU1S02_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000020EUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [23] ADU1S07_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000161UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [24] ADU1S18_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000162UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [25] ADU1S19_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000163UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [26] ADU1S20_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000166UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [27] ADU1S21_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000167UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [28] ADU1S22_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000168UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [29] ADU1S23_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000169UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [30] ADU1S24_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000016AUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [31] ADU1S25_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000016BUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [32] ADU1S26_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000016CUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [33] ADU1S27_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000016DUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [34] ADU1S28_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000214UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [35] BAT1E41_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000016EUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [36] BAT1E45_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003E5UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [37] BAT1S01_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000124UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [38] BAT1S08_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000379UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [39] BCC1S05_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003F3UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [40] BCC1S06_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000038BUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [41] BDB1F01_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400001F4UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [42] BDB1F03_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400001CFUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [43] BDB1S01_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000624UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [44] BDB1S08_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000626UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [45] BDB1S10_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003FCUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [46] BDB1S19_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000306UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [47] BDB1S25_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000305UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [48] BDB1S26_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000629UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [49] BDB1S27_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000062AUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [50] BDB1S28_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000397UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [51] BDB1S29_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003B5UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [52] BDB1S35_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003B8UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [53] BDB1S36_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000320UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [54] BDC1S14_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000032AUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [55] BDC1S16_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000037CUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [56] BDC1S22_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000186UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [57] BDC1S30_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000148UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [58] BDC1S41_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000337UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [59] BDC1S48_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400001E3UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [60] BDC1S81_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000367UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [61] BDC1S83_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000355UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [62] BDC1S97_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000358UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [63] BDC1S98_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000035DUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [64] BDC1S99_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400001A4UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [65] BDC1SA0_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000035FUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [66] BDC1SA1_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000393UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [67] BDC1SC1_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000395UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [68] BDC1SC2_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000396UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [69] BDC1SC3_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000039AUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [70] BDC1SC4_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000039BUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [71] BDC1SC5_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000039DUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [72] BDC1SC6_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000039EUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [73] BDC1SC7_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000039FUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [74] BDC1SC8_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003A5UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [75] BDC1SC9_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003ACUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [76] BDC1SD1_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003AEUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [77] BDC1SD2_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003B2UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [78] BDC1SD3_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003B3UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [79] BDC1SD4_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003B9UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [80] BDC1SD5_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003BCUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [81] BDC1SD6_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003C6UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [82] BDC1SD7_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003C7UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [83] BDC1SD8_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003CDUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [84] BDC1SD9_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003D3UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [85] BDC1SE1_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003D6UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [86] BDC1SE2_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003DDUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [87] BDC1SE3_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003E1UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [88] BDC1SE4_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003EBUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [89] BDC1SE5_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003EFUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [90] BDC1SE6_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003F5UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [91] BDC1SE7_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000423UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [92] BDC1SE8_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000429UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [93] BDC1SE9_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000430UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [94] BDC1SF1_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000480UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [95] BDC1SF2_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000484UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [96] BDC1SF3_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000491UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [97] BDC1SF4_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000497UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [98] BDC1SF6_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000526UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [99] BDC1SG4_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000052BUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [100] BDC1SG6_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000052CUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [101] BDC1SG7_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000530UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [102] BDC1SG8_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000531UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [103] BDC1SG9_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000534UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [104] BDC1SH3_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000535UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [105] BDC1SH4_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000537UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [106] BDC1SH5_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000538UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [107] BDC1SH6_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400002B3UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [108] BDC1SH8_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000037BUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [109] BDF3S01_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000018DUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [110] BDF3S02_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000019AUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [111] BDR3S02_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003F6UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [112] BSR1S01_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000235UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [113] BSR1S02_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400002AFUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [114] BSR1S03_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400001D9UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [115] CMB1S03_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400002F3UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [116] CMB1S04_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000043AUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [117] CSR1S04_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003DBUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [118] CSR1S07_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000438UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [119] DCM1S01_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000034FUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [120] DCM1S03_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000363UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [121] DCM1S04_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400002EEUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [122] DDM1S16_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400002DAUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [123] DDM1S20_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000219UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [124] DDM1S32_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400002E5UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [125] DDM1S35_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000281UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [126] DDM1SFG_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000282UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [127] DDM1SFH_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000528UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [128] DKY1S26_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000285UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [129] DS11S27_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000317UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [130] DS11S37_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000608UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [131] DS11S40_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000411UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [132] DS12F02_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000412UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [133] DS12F03_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003F0UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [134] DST1S02_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400004A0UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [135] EBU1D01_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003BFUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [136] ECT1G01_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400001BCUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [137] EHV1E96_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400002A7UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [138] EHV1G70_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400002A8UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [139] EHV1G71_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400001D0UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [140] EHV1S23_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000042FUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [141] EHV1S26_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000325UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [142] EHV1S31_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000040BUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [143] EHV1S95_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000042BUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [144] EHV1S97_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400002EBUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [145] EHV1SL2_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000335UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [146] EIM1S01_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400001C5UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [147] ENG1G13_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000051EUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [148] ENG1G90_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000589UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [149] ENG1S60_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400005F1UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [150] FCM1C03_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000489UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [151] FCM1S10_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000048BUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [152] FCM1S12_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000251UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [153] FCM1S39_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000261UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [154] FCM1S41_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000275UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [155] FCM1S51_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000276UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [156] FCM1S52_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000028AUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [157] FCM1S66_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000025AUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [158] FCM1S70_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000100UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [159] FCM1S79_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000020FUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [160] FCM1S88_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400001B2UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [161] FCM1S90_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003FBUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [162] IDT1S07_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000014BUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [163] IDT1S08_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000532UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [164] IDT1S15_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000043BUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [165] IPA1S05_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003DEUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [166] ITS1S04_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000027BUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [167] ITS1S08_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000173UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [168] LRS1S01_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000179UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [169] LRS1S03_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000017AUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [170] LRS1S04_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000494UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [171] LVN1S01_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000315UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [172] MET1S33_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000524UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [173] MET1S38_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400001DCUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [174] MET1S47_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400001F7UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [175] MET1S55_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400001CCUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [176] PDC1G01_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000507UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [177] PDC1G02_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000295UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [178] PLG1G15_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000296UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [179] PLG1G16_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000422UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [180] PLG1S01_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000432UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [181] PLG1S06_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400002A6UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [182] PLG1S20_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000204UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [183] PLG1S21_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000403UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [184] PST1S01_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000405UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [185] PST1S02_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000014DUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [186] RCP1S01_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000230UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [187] RCP1S02_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000014FUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [188] RCP1S03_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000182UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [189] RRS1S01_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000189UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [190] RRS1S03_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000018CUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [191] RRS1S04_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000032FUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [192] RSE1G24_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000336UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [193] RSE1G25_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000034DUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [194] RSE1G26_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000385UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [195] RSE1G29_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003C8UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [196] RSE1S02_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000328UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [197] RST1S03_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000439UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [198] SCN1S01_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400002FDUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [199] SCS1S11_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400002FEUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [200] SCS1S14_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000040CUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [201] SOL1S02_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000040DUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [202] SOL1S03_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400001EBUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [203] SOL1S04_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400001EAUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [204] SOL1S05_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000495UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [205] TPM1S02_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000496UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [206] TPM1S03_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000347UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [207] TPM1S04_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000034CUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [208] TPM1S05_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000417UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [209] TPM1S06_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000418UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [210] TPM1S08_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000426UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [211] TPM1S09_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000428UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [212] TPM1S10_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000042AUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [213] TPM1S11_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000042CUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [214] TPM1S12_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400002A0UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [215] TRA1S01_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400000A0UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [216] TRA1S02_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003E7UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [217] UCB1S01_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000009EUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [218] VSC1G13_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400000B7UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [219] VSC1G14_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400002F9UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [220] WIP1S01_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000027EUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [221] YGW1S01_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000086UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [222] ZN11S08_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400001DEUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [223] ZN11S14_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000368UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [224] ZN11S19_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000398UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [225] ZN11S25_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000036AUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [226] ZN11S26_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000039CUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [227] ZN11S32_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000036EUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [228] ZN11S60_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000033FUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [229] ZN11S63_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003D2UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [230] ZN11S64_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003F9UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [231] ZN11S65_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000400UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [232] ZN11S66_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000404UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [233] ZN11S67_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000350UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [234] ZN11SF6_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000352UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [235] ZN11SF7_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000353UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [236] ZN11SF8_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003BBUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [237] ZN11SF9_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000390UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [238] ZN21S13_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400001BEUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [239] ZN21S28_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003A9UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [240] ZN21S72_Rx_VCAN_VCC_1_BUS */
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
     (BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [0] AVN1S01_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [1] AVN1S03_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [2] AVN1S04_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [3] AVN1S05_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [4] AVN1S06_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [5] AVN1S07_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [6] AVN1S08_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [7] AVN1S11_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [8] AVN1S20_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [9] AVN1S21_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [10] AVN1S22_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [11] AVN1S23_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [12] AVN1S30_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [13] AVN1S38_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [14] AVN1S39_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [15] AVN1S40_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [16] AVN1S41_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [17] AVN1S42_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [18] AVN1S43_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [19] AVN1S44_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [20] AVN1S52_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [21] AVN1S62_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [22] AVN1S63_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [23] AVN1S64_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [24] AVN1S65_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [25] AVN1S66_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [26] AVN1S67_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [27] AVN1S68_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [28] AVN1S69_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [29] AVN1S71_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [30] AVN1S73_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [31] AVN1S78_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [32] AVN1S94_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [33] AVN1S95_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [34] AVN1S97_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [35] AVN1S98_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [36] AVN1S99_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [37] AVN1SA1_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [38] AVN1SA6_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [39] AVN1SA7_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [40] AVN1SA8_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [41] AVN1SB1_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [42] AVN1SB2_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [43] AVN1SB3_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [44] AVN1SB4_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [45] AVN1SB5_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [46] AVN1SB7_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [47] AVN1SB9_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [48] AVN1SC1_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [49] AVN1SC2_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [50] AVN1SC3_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [51] AVN1SC4_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [52] AVN1SC5_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [53] AVN1SC6_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [54] AVN1SC7_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [55] AVN1SC8_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [56] AVN1SC9_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [57] AVN1SD1_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [58] AVN1SD2_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [59] AVN1SD3_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [60] AVN1SD4_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [61] AVN1SD5_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [62] AVN1SD6_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [63] AVN1SD7_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [64] AVN1SD8_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [65] AVN1SD9_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [66] AVN1SE1_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [67] AVN1SE2_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [68] AVN1SE3_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [69] AVN1SE4_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [70] AVN1SE5_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [71] AVN1SE6_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [72] AVN1SE7_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [73] AVN1SE8_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [74] AVN1SE9_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [75] AVN1SF1_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [76] AVN1SF2_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [77] AVN1SF3_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [78] AVN1SF4_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [79] AVN1SF5_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [80] AVN1SF7_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [81] AVN1SF8_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [82] AVN1SF9_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [83] AVN1SG1_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [84] AVN1SG3_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [85] AVN1SG5_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [86] AVN1SG6_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [87] AVN1SH1_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [88] DMS1S02_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [89] MET1S27_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [90] MET1S28_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [91] MET1S43_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [92] MET1S70_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [93] ABG1D50_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [94] ABG1D51_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [95] ABG1S01_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [96] ABG1S04_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [97] ACN1D50_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [98] ACN1S03_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [99] ACN1S04_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [100] ACN1S05_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [101] ACN1S07_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [102] ACN1S15_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [103] ACN1S16_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [104] ACN1S22_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [105] ACN1S25_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [106] ACN1S29_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [107] ADC1S06_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [108] ADC1S13_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [109] ADC1S14_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [110] ADC1S17_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [111] ADC1S19_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [112] ADC1S20_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [113] ADC1S23_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [114] ADC1S31_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [115] ADU1S02_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [116] ADU1S07_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [117] ADU1S18_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [118] ADU1S19_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [119] ADU1S20_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [120] ADU1S21_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [121] ADU1S22_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [122] ADU1S23_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [123] ADU1S24_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [124] ADU1S25_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [125] ADU1S26_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [126] ADU1S27_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [127] ADU1S28_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [128] BAT1E41_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [129] BAT1E45_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [130] BAT1S01_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [131] BAT1S08_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [132] BCC1S05_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [133] BCC1S06_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [134] BDB1F01_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [135] BDB1F03_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [136] BDB1S01_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [137] BDB1S08_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [138] BDB1S10_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [139] BDB1S19_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [140] BDB1S25_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [141] BDB1S26_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [142] BDB1S27_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [143] BDB1S28_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [144] BDB1S29_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [145] BDB1S35_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [146] BDB1S36_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [147] BDC1S14_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [148] BDC1S16_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [149] BDC1S22_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [150] BDC1S30_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [151] BDC1S41_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [152] BDC1S48_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [153] BDC1S81_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [154] BDC1S83_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [155] BDC1S97_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [156] BDC1S98_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [157] BDC1S99_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [158] BDC1SA0_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [159] BDC1SA1_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [160] BDC1SC1_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [161] BDC1SC2_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [162] BDC1SC3_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [163] BDC1SC4_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [164] BDC1SC5_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [165] BDC1SC6_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [166] BDC1SC7_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [167] BDC1SC8_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [168] BDC1SC9_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [169] BDC1SD1_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [170] BDC1SD2_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [171] BDC1SD3_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [172] BDC1SD4_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [173] BDC1SD5_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [174] BDC1SD6_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [175] BDC1SD7_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [176] BDC1SD8_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [177] BDC1SD9_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [178] BDC1SE1_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [179] BDC1SE2_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [180] BDC1SE3_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [181] BDC1SE4_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [182] BDC1SE5_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [183] BDC1SE6_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [184] BDC1SE7_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [185] BDC1SE8_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [186] BDC1SE9_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [187] BDC1SF1_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [188] BDC1SF2_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [189] BDC1SF3_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [190] BDC1SF4_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [191] BDC1SF6_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [192] BDC1SG4_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [193] BDC1SG6_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [194] BDC1SG7_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [195] BDC1SG8_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [196] BDC1SG9_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [197] BDC1SH3_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [198] BDC1SH4_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [199] BDC1SH5_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [200] BDC1SH6_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [201] BDC1SH8_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [202] BDF3S01_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [203] BDF3S02_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [204] BDR3S02_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [205] BSR1S01_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [206] BSR1S02_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [207] BSR1S03_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [208] CMB1S03_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [209] CMB1S04_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [210] CSR1S04_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [211] CSR1S07_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [212] DCM1S01_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [213] DCM1S03_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [214] DCM1S04_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [215] DDM1S16_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [216] DDM1S20_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [217] DDM1S32_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [218] DDM1S35_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [219] DDM1SFG_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [220] DDM1SFH_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [221] DKY1S26_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [222] DS11S27_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [223] DS11S37_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [224] DS11S40_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [225] DS12F02_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [226] DS12F03_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [227] DST1S02_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [228] EBU1D01_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [229] ECT1G01_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [230] EHV1E96_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [231] EHV1G70_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [232] EHV1G71_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [233] EHV1S23_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [234] EHV1S26_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [235] EHV1S31_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [236] EHV1S95_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [237] EHV1S97_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [238] EHV1SL2_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [239] EIM1S01_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [240] ENG1G13_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [241] ENG1G90_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [242] ENG1S60_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [243] FCM1C03_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [244] FCM1S10_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [245] FCM1S12_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [246] FCM1S39_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [247] FCM1S41_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [248] FCM1S51_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [249] FCM1S52_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [250] FCM1S66_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [251] FCM1S70_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [252] FCM1S79_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [253] FCM1S88_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [254] FCM1S90_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [255] IDT1S07_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [256] IDT1S08_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [257] IDT1S15_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [258] IPA1S05_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [259] ITS1S04_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [260] ITS1S08_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [261] LRS1S01_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [262] LRS1S03_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [263] LRS1S04_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [264] LVN1S01_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [265] MET1S33_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [266] MET1S38_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [267] MET1S47_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [268] MET1S55_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [269] PDC1G01_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [270] PDC1G02_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [271] PLG1G15_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [272] PLG1G16_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [273] PLG1S01_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [274] PLG1S06_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [275] PLG1S20_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [276] PLG1S21_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [277] PST1S01_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [278] PST1S02_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [279] RCP1S01_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [280] RCP1S02_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [281] RCP1S03_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [282] RRS1S01_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [283] RRS1S03_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [284] RRS1S04_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [285] RSE1G24_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [286] RSE1G25_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [287] RSE1G26_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [288] RSE1G29_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [289] RSE1S02_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [290] RST1S03_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [291] SCN1S01_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [292] SCS1S11_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [293] SCS1S14_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [294] SOL1S02_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [295] SOL1S03_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [296] SOL1S04_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [297] SOL1S05_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [298] TPM1S02_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [299] TPM1S03_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [300] TPM1S04_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [301] TPM1S05_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [302] TPM1S06_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [303] TPM1S08_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [304] TPM1S09_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [305] TPM1S10_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [306] TPM1S11_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [307] TPM1S12_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [308] TRA1S01_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [309] TRA1S02_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [310] UCB1S01_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [311] VSC1G13_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [312] VSC1G14_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [313] WIP1S01_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [314] YGW1S01_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [315] ZN11S08_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [316] ZN11S14_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [317] ZN11S19_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [318] ZN11S25_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [319] ZN11S26_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [320] ZN11S32_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [321] ZN11S60_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [322] ZN11S63_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [323] ZN11S64_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [324] ZN11S65_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [325] ZN11S66_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [326] ZN11S67_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [327] ZN11SF6_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [328] ZN11SF7_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [329] ZN11SF8_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [330] ZN11SF9_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [331] ZN21S13_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [332] ZN21S28_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [333] ZN21S72_Rx_VCAN_VCC_1_BUS */
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


#if ( (BSW_CANIF_PKTCAN_EXTA1_USE == BSW_USE) || (BSW_CANIF_PKTCAN_EXTA2_USE == BSW_USE) )
#if((BSW_CANIF_TXPDURPDUNUM + BSW_CANIF_RXPDURPDUNUM) != 0U)
BswConst BswU1 bsw_canif_u1MsgIdTbl[BSW_CANIF_TXPDURPDUNUM + BSW_CANIF_RXPDURPDUNUM] = {
};
#endif /* (BSW_CANIF_TXPDURPDUNUM != 0U) */
#endif /* ( (BSW_CANIF_PKTCAN_EXTA1_USE == BSW_USE) || (BSW_CANIF_PKTCAN_EXTA2_USE == BSW_USE) ) */

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
