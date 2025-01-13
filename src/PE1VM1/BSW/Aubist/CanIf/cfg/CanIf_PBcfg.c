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
     { 0x40000435UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE000 }  /* [0] AVN1S21_Tx_VCAN_VCC_1_BUS */
    ,{ 0x40000436UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE000 }  /* [1] AVN1S22_Tx_VCAN_VCC_1_BUS */
    ,{ 0x40000437UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE000 }  /* [2] AVN1S23_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400001ECUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE000 }  /* [3] AVN1SA6_Tx_VCAN_VCC_1_BUS */
    ,{ 0x40000515UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE001 }  /* [4] AVN1SB3_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400002D2UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE002 }  /* [5] AVN1SB7_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400002F6UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE000 }  /* [6] AVN1SD5_Tx_VCAN_VCC_1_BUS */
    ,{ 0x4000060CUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE005 }  /* [7] AVN1SG6_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400002E3UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE005 }  /* [8] AVN1SH1_Tx_VCAN_VCC_1_BUS */
    ,{ 0x4000056DUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE004 }  /* [9] CDC1N02_Tx_VCAN_VCC_1_BUS */
    ,{ 0x40000333UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE005 }  /* [10] CDC1S01_Tx_VCAN_VCC_1_BUS */
    ,{ 0x40000334UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE001 }  /* [11] CDC1S03_Tx_VCAN_VCC_1_BUS */
    ,{ 0x40000427UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE002 }  /* [12] DMS1S02_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400003F7UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE002 }  /* [13] HUD1S01_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400001F6UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE002 }  /* [14] MET1S01_Tx_VCAN_VCC_1_BUS */
    ,{ 0x40000611UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE002 }  /* [15] MET1S02_Tx_VCAN_VCC_1_BUS */
    ,{ 0x40000618UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE000 }  /* [16] MET1S03_Tx_VCAN_VCC_1_BUS */
    ,{ 0x40000614UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE002 }  /* [17] MET1S10_Tx_VCAN_VCC_1_BUS */
    ,{ 0x40000615UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE002 }  /* [18] MET1S11_Tx_VCAN_VCC_1_BUS */
    ,{ 0x4000058DUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE002 }  /* [19] MET1S25_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400003EAUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE004 }  /* [20] MET1S27_Tx_VCAN_VCC_1_BUS */
    ,{ 0x4000037EUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE004 }  /* [21] MET1S28_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400003ECUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE004 }  /* [22] MET1S29_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400003EEUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE002 }  /* [23] MET1S30_Tx_VCAN_VCC_1_BUS */
    ,{ 0x40000315UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE002 }  /* [24] MET1S33_Tx_VCAN_VCC_1_BUS */
    ,{ 0x40000524UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE003 }  /* [25] MET1S38_Tx_VCAN_VCC_1_BUS */
    ,{ 0x40000527UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE000 }  /* [26] MET1S41_Tx_VCAN_VCC_1_BUS */
    ,{ 0x40000529UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE004 }  /* [27] MET1S43_Tx_VCAN_VCC_1_BUS */
    ,{ 0x4000024DUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE005 }  /* [28] MET1S44_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400001DCUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE002 }  /* [29] MET1S47_Tx_VCAN_VCC_1_BUS */
    ,{ 0x4000030DUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE002 }  /* [30] MET1S52_Tx_VCAN_VCC_1_BUS */
    ,{ 0x400001F7UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE001 }  /* [31] MET1S55_Tx_VCAN_VCC_1_BUS */
    ,{ 0x4000041AUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE002 }  /* [32] MET1S62_Tx_VCAN_VCC_1_BUS */
    ,{ 0x40000357UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE005 }  /* [33] MET1S70_Tx_VCAN_VCC_1_BUS */
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
    ,{ 0x400004B8UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [3] ACN1D50_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003A1UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [4] ACN1S03_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000381UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [5] ACN1S04_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003B0UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [6] ACN1S07_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000407UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [7] ACN1S15_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000255UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [8] ACN1S25_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000506UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [9] ACN1S29_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400001F1UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [10] ADC1S08_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000143UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [11] ADC1S10_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000017EUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [12] ADC1S11_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000203UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [13] ADC1S12_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000207UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [14] ADC1S13_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000208UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [15] ADC1S14_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000209UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [16] ADC1S15_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000180UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [17] ADC1S16_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000020AUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [18] ADC1S17_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400001C0UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [19] ADC1S31_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000020EUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [20] ADU1S07_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000072UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [21] ARS1S01_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400001DDUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [22] ARS1S90_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000016EUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [23] BAT1E45_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003E5UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [24] BAT1S01_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000124UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [25] BAT1S08_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000155UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [26] BAT1S11_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003F3UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [27] BCC1S06_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000038BUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [28] BDB1F01_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000038DUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [29] BDB1F02_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400001F4UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [30] BDB1F03_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400001CFUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [31] BDB1S01_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000621UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [32] BDB1S02_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000622UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [33] BDB1S03_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000623UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [34] BDB1S04_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000380UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [35] BDB1S05_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000624UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [36] BDB1S08_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000626UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [37] BDB1S10_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000062CUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [38] BDB1S13_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000629UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [39] BDB1S27_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000062AUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [40] BDB1S28_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000397UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [41] BDB1S29_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003B8UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [42] BDB1S36_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000312UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [43] BDC1S13_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000037CUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [44] BDC1S22_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000140UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [45] BDC1S23_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400001D2UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [46] BDC1S33_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000148UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [47] BDC1S41_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000364UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [48] BDC1S45_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400001D3UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [49] BDC1S46_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000337UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [50] BDC1S48_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000013UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [51] BDC1S52_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000001BUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [52] BDC1S60_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000341UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [53] BDC1S74_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400001E3UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [54] BDC1S81_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400002B3UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [55] BDC1SH8_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000485UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [56] BDC1SZ1_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000043CUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [57] BDC1SZ3_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000486UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [58] BDC1SZ5_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000037BUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [59] BDF3S01_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000018DUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [60] BDF3S02_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000019AUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [61] BDR3S02_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003CBUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [62] BKD1S01_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003ABUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [63] BKD1S02_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003F6UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [64] BSR1S01_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000235UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [65] BSR1S02_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400002AFUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [66] BSR1S03_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400001D9UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [67] CMB1S03_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400002F3UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [68] CMB1S04_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400000A9UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [69] CSR1G10_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000043AUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [70] CSR1S04_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003DBUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [71] CSR1S07_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003DCUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [72] CSR1S08_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400000B8UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [73] DDM1S12_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400002EEUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [74] DDM1S16_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400001D7UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [75] DDM1S17_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000219UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [76] DDM1S32_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400002E5UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [77] DDM1S35_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000281UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [78] DDM1SFG_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000282UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [79] DDM1SFH_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000528UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [80] DKY1S26_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000122UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [81] DMC1S08_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003BEUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [82] DRL1S03_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003AFUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [83] DRR1S03_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000285UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [84] DS11S27_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000317UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [85] DS11S37_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000608UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [86] DS11S40_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000411UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [87] DS12F02_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000412UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [88] DS12F03_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003F0UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [89] DST1S02_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400004A0UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [90] EBU1D01_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003BFUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [91] ECT1G01_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400002A1UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [92] ECT1G92_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003D4UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [93] ECT1S80_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000401UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [94] ECT1S93_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400001BCUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [95] EHV1E96_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400000A5UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [96] EHV1F04_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000128UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [97] EHV1G30_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400001D0UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [98] EHV1S23_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000042FUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [99] EHV1S26_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000325UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [100] EHV1S31_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003B6UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [101] EHV1S90_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000421UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [102] EHV1S94_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000040BUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [103] EHV1S95_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400001FAUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [104] EHV1S96_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000042BUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [105] EHV1S97_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400002DEUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [106] EHV1S99_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400000A6UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [107] EHV2G02_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000202UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [108] EHV2G70_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000335UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [109] EIM1S01_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400000A4UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [110] ENG1G03_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400001C5UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [111] ENG1G13_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400000A3UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [112] ENG1G17_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000051EUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [113] ENG1G90_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400000FCUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [114] ENG1G92_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000589UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [115] ENG1S60_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000583UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [116] ENG1S99_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000062UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [117] EPS1S11_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400001CAUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [118] EPS1S90_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000489UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [119] FCM1S10_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000048BUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [120] FCM1S12_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000251UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [121] FCM1S39_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000252UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [122] FCM1S40_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000261UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [123] FCM1S41_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000275UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [124] FCM1S51_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000276UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [125] FCM1S52_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000027CUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [126] FCM1S58_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000025AUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [127] FCM1S70_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000015AUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [128] FCM1S78_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000100UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [129] FCM1S79_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400001B2UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [130] FCM1S90_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000259UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [131] FCM1S92_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000115UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [132] FWD1S10_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000633UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [133] IDT1S02_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003FBUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [134] IDT1S07_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000532UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [135] IDT1S15_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000043BUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [136] IPA1S05_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000036BUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [137] ITS1S01_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003DEUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [138] ITS1S04_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000314UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [139] ITS1S05_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000173UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [140] LRS1S01_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000179UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [141] LRS1S03_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000017AUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [142] LRS1S04_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000494UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [143] LVN1S01_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003BDUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [144] PCN1S01_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400001CCUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [145] PDC1G01_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000507UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [146] PDC1G02_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400002F4UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [147] PDS1S01_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000295UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [148] PLG1G15_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000296UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [149] PLG1G16_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000422UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [150] PLG1S01_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000431UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [151] PLG1S05_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000432UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [152] PLG1S06_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400002A6UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [153] PLG1S20_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000204UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [154] PLG1S21_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400001D1UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [155] PMN1G03_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000403UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [156] PST1S01_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000230UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [157] RCP1S02_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000014FUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [158] RCP1S03_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000182UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [159] RRS1S01_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000189UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [160] RRS1S03_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000018CUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [161] RRS1S04_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003CAUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [162] RSE1G20_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000032FUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [163] RSE1G24_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000336UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [164] RSE1G25_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000034DUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [165] RSE1G26_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000385UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [166] RSE1G29_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003C8UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [167] RSE1S02_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400001DBUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [168] SBW1G02_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000439UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [169] SCN1S01_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000375UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [170] SCN1S02_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400002FDUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [171] SCS1S11_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400002FEUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [172] SCS1S14_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000040CUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [173] SOL1S02_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400001BBUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [174] SOL1S06_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000495UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [175] TPM1S02_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000496UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [176] TPM1S03_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000347UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [177] TPM1S04_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000034CUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [178] TPM1S05_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000036FUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [179] TPM1S07_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400002A0UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [180] TRA1S01_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003E7UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [181] UCB1S01_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000318UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [182] VAS1S01_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000006AUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [183] VSC1F01_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000069UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [184] VSC1G12_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000009EUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [185] VSC1G13_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400000B7UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [186] VSC1G14_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000262UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [187] VSC1G96_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000601UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [188] VUM1S01_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400002F9UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [189] WIP1S01_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000037FUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [190] ZN11S02_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000038AUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [191] ZN11S03_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000086UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [192] ZN11S08_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400001DFUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [193] ZN11S17_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000368UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [194] ZN11S19_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000036AUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [195] ZN11S26_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000039CUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [196] ZN11S32_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000500UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [197] ZN11S38_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000036EUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [198] ZN11S60_Rx_VCAN_VCC_1_BUS */
    ,{ 0x4000033FUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [199] ZN11S63_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003D2UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [200] ZN11S64_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003F9UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [201] ZN11S65_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000400UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [202] ZN11S66_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000404UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [203] ZN11S67_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003C3UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [204] ZN11SC6_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000350UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [205] ZN11SF6_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000352UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [206] ZN11SF7_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400001E1UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [207] ZN21S05_Rx_VCAN_VCC_1_BUS */
    ,{ 0x40000390UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [208] ZN21S13_Rx_VCAN_VCC_1_BUS */
    ,{ 0x400003A9UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [209] ZN21S72_Rx_VCAN_VCC_1_BUS */
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
     (BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [0] AVN1S21_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [1] AVN1S22_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [2] AVN1S23_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [3] AVN1SA6_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [4] AVN1SB3_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [5] AVN1SB7_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [6] AVN1SD5_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [7] AVN1SG6_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [8] AVN1SH1_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [9] CDC1N02_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [10] CDC1S01_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [11] CDC1S03_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [12] DMS1S02_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [13] HUD1S01_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [14] MET1S01_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [15] MET1S02_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [16] MET1S03_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [17] MET1S10_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [18] MET1S11_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [19] MET1S25_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [20] MET1S27_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [21] MET1S28_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [22] MET1S29_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [23] MET1S30_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [24] MET1S33_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [25] MET1S38_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [26] MET1S41_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [27] MET1S43_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [28] MET1S44_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [29] MET1S47_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [30] MET1S52_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [31] MET1S55_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [32] MET1S62_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [33] MET1S70_Tx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [34] ABG1D50_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [35] ABG1D51_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [36] ABG1S01_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [37] ACN1D50_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [38] ACN1S03_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [39] ACN1S04_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [40] ACN1S07_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [41] ACN1S15_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [42] ACN1S25_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [43] ACN1S29_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [44] ADC1S08_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [45] ADC1S10_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [46] ADC1S11_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [47] ADC1S12_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [48] ADC1S13_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [49] ADC1S14_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [50] ADC1S15_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [51] ADC1S16_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [52] ADC1S17_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [53] ADC1S31_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [54] ADU1S07_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [55] ARS1S01_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [56] ARS1S90_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [57] BAT1E45_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [58] BAT1S01_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [59] BAT1S08_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [60] BAT1S11_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [61] BCC1S06_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [62] BDB1F01_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [63] BDB1F02_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [64] BDB1F03_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [65] BDB1S01_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [66] BDB1S02_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [67] BDB1S03_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [68] BDB1S04_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [69] BDB1S05_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [70] BDB1S08_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [71] BDB1S10_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [72] BDB1S13_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [73] BDB1S27_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [74] BDB1S28_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [75] BDB1S29_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [76] BDB1S36_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [77] BDC1S13_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [78] BDC1S22_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [79] BDC1S23_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [80] BDC1S33_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [81] BDC1S41_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [82] BDC1S45_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [83] BDC1S46_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [84] BDC1S48_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [85] BDC1S52_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [86] BDC1S60_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [87] BDC1S74_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [88] BDC1S81_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [89] BDC1SH8_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [90] BDC1SZ1_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [91] BDC1SZ3_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [92] BDC1SZ5_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [93] BDF3S01_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [94] BDF3S02_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [95] BDR3S02_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [96] BKD1S01_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [97] BKD1S02_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [98] BSR1S01_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [99] BSR1S02_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [100] BSR1S03_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [101] CMB1S03_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [102] CMB1S04_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [103] CSR1G10_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [104] CSR1S04_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [105] CSR1S07_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [106] CSR1S08_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [107] DDM1S12_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [108] DDM1S16_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [109] DDM1S17_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [110] DDM1S32_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [111] DDM1S35_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [112] DDM1SFG_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [113] DDM1SFH_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [114] DKY1S26_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [115] DMC1S08_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [116] DRL1S03_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [117] DRR1S03_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [118] DS11S27_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [119] DS11S37_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [120] DS11S40_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [121] DS12F02_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [122] DS12F03_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [123] DST1S02_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [124] EBU1D01_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [125] ECT1G01_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [126] ECT1G92_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [127] ECT1S80_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [128] ECT1S93_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [129] EHV1E96_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [130] EHV1F04_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [131] EHV1G30_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [132] EHV1S23_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [133] EHV1S26_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [134] EHV1S31_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [135] EHV1S90_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [136] EHV1S94_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [137] EHV1S95_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [138] EHV1S96_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [139] EHV1S97_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [140] EHV1S99_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [141] EHV2G02_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [142] EHV2G70_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [143] EIM1S01_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [144] ENG1G03_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [145] ENG1G13_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [146] ENG1G17_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [147] ENG1G90_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [148] ENG1G92_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [149] ENG1S60_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [150] ENG1S99_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [151] EPS1S11_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [152] EPS1S90_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [153] FCM1S10_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [154] FCM1S12_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [155] FCM1S39_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [156] FCM1S40_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [157] FCM1S41_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [158] FCM1S51_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [159] FCM1S52_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [160] FCM1S58_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [161] FCM1S70_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [162] FCM1S78_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [163] FCM1S79_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [164] FCM1S90_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [165] FCM1S92_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [166] FWD1S10_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [167] IDT1S02_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [168] IDT1S07_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [169] IDT1S15_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [170] IPA1S05_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [171] ITS1S01_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [172] ITS1S04_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [173] ITS1S05_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [174] LRS1S01_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [175] LRS1S03_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [176] LRS1S04_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [177] LVN1S01_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [178] PCN1S01_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [179] PDC1G01_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [180] PDC1G02_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [181] PDS1S01_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [182] PLG1G15_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [183] PLG1G16_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [184] PLG1S01_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [185] PLG1S05_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [186] PLG1S06_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [187] PLG1S20_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [188] PLG1S21_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [189] PMN1G03_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [190] PST1S01_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [191] RCP1S02_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [192] RCP1S03_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [193] RRS1S01_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [194] RRS1S03_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [195] RRS1S04_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [196] RSE1G20_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [197] RSE1G24_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [198] RSE1G25_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [199] RSE1G26_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [200] RSE1G29_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [201] RSE1S02_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [202] SBW1G02_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [203] SCN1S01_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [204] SCN1S02_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [205] SCS1S11_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [206] SCS1S14_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [207] SOL1S02_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [208] SOL1S06_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [209] TPM1S02_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [210] TPM1S03_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [211] TPM1S04_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [212] TPM1S05_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [213] TPM1S07_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [214] TRA1S01_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [215] UCB1S01_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [216] VAS1S01_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [217] VSC1F01_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [218] VSC1G12_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [219] VSC1G13_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [220] VSC1G14_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [221] VSC1G96_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [222] VUM1S01_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [223] WIP1S01_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [224] ZN11S02_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [225] ZN11S03_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [226] ZN11S08_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [227] ZN11S17_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [228] ZN11S19_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [229] ZN11S26_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [230] ZN11S32_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [231] ZN11S38_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [232] ZN11S60_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [233] ZN11S63_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [234] ZN11S64_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [235] ZN11S65_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [236] ZN11S66_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [237] ZN11S67_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [238] ZN11SC6_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [239] ZN11SF6_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [240] ZN11SF7_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [241] ZN21S05_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [242] ZN21S13_Rx_VCAN_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [243] ZN21S72_Rx_VCAN_VCC_1_BUS */
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
