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
     { 0x400001DCUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE000 }  /* [0] MET1S47_Tx_CDC_VCAN_BUS */
    ,{ 0x400001F6UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE000 }  /* [1] MET1S01_Tx_CDC_VCAN_BUS */
    ,{ 0x400001F7UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE001 }  /* [2] MET1S55_Tx_CDC_VCAN_BUS */
    ,{ 0x4000024DUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE002 }  /* [3] MET1S44_Tx_CDC_VCAN_BUS */
    ,{ 0x4000030DUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE003 }  /* [4] MET1S52_Tx_CDC_VCAN_BUS */
    ,{ 0x40000333UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE004 }  /* [5] CDC1S01_Tx_CDC_VCAN_BUS */
    ,{ 0x40000334UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE005 }  /* [6] CDC1S03_Tx_CDC_VCAN_BUS */
    ,{ 0x40000357UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE004 }  /* [7] MET1S70_Tx_CDC_VCAN_BUS */
    ,{ 0x4000037EUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE005 }  /* [8] MET1S28_Tx_CDC_VCAN_BUS */
    ,{ 0x400003EAUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE004 }  /* [9] MET1S27_Tx_CDC_VCAN_BUS */
    ,{ 0x400003ECUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE004 }  /* [10] MET1S29_Tx_CDC_VCAN_BUS */
    ,{ 0x400003EEUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE003 }  /* [11] MET1S30_Tx_CDC_VCAN_BUS */
    ,{ 0x400003F7UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE003 }  /* [12] HUD1S01_Tx_CDC_VCAN_BUS */
    ,{ 0x4000041AUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE006 }  /* [13] MET1S62_Tx_CDC_VCAN_BUS */
    ,{ 0x40000427UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE006 }  /* [14] DMS1S02_Tx_CDC_VCAN_BUS */
    ,{ 0x40000524UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE007 }  /* [15] MET1S38_Tx_CDC_VCAN_BUS */
    ,{ 0x40000527UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE008 }  /* [16] MET1S41_Tx_CDC_VCAN_BUS */
    ,{ 0x40000529UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE009 }  /* [17] MET1S43_Tx_CDC_VCAN_BUS */
    ,{ 0x4000056DUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE009 }  /* [18] CDC1N02_Tx_CDC_VCAN_BUS */
    ,{ 0x4000058DUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE007 }  /* [19] MET1S25_Tx_CDC_VCAN_BUS */
    ,{ 0x40000611UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE010 }  /* [20] MET1S02_Tx_CDC_VCAN_BUS */
    ,{ 0x40000614UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE010 }  /* [21] MET1S10_Tx_CDC_VCAN_BUS */
    ,{ 0x40000615UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE010 }  /* [22] MET1S11_Tx_CDC_VCAN_BUS */
    ,{ 0xD8008000UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE011 }  /* [23] QSEV_Tx_CANFD_VCC_1_BUS */
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
     { 0x0000047DUL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE000 }  /* [0] VME1N99_Tx_CDC_VCAN_BUS */
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
     { 0x98DAE017UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE000 }  /* [0] Nsdu_TX_TxNPdu_Diag_Physical_Service */
    ,{ 0x98DAE117UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE000 }  /* [1] Nsdu_TX_TxNPdu_Diag_Physical_Remote */
    ,{ 0xD8DAE017UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE000 }  /* [2] Nsdu_TX_TxNPdu_Diag_Physical_FD_Service */
    ,{ 0xD8DAE117UL, (BswU1)BSW_CANIF_CH0,  (BswU1)0U, (BswU2)BSW_CANIF_SNDREQ_QUE000 }  /* [3] Nsdu_TX_TxNPdu_Diag_Physical_FD_Remote */
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
    ,{ 0x400001D6UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [3] ABG1S09_Rx_CDC_VCAN_BUS */
    ,{ 0x400004B8UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [4] ACN1D50_Rx_CDC_VCAN_BUS */
    ,{ 0x400003A1UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [5] ACN1S03_Rx_CDC_VCAN_BUS */
    ,{ 0x40000381UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [6] ACN1S04_Rx_CDC_VCAN_BUS */
    ,{ 0x40000407UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [7] ACN1S15_Rx_CDC_VCAN_BUS */
    ,{ 0x40000255UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [8] ACN1S25_Rx_CDC_VCAN_BUS */
    ,{ 0x40000506UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [9] ACN1S29_Rx_CDC_VCAN_BUS */
    ,{ 0x400001F1UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [10] ADC1S08_Rx_CDC_VCAN_BUS */
    ,{ 0x40000143UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [11] ADC1S10_Rx_CDC_VCAN_BUS */
    ,{ 0x4000017EUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [12] ADC1S11_Rx_CDC_VCAN_BUS */
    ,{ 0x40000203UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [13] ADC1S12_Rx_CDC_VCAN_BUS */
    ,{ 0x40000207UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [14] ADC1S13_Rx_CDC_VCAN_BUS */
    ,{ 0x40000208UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [15] ADC1S14_Rx_CDC_VCAN_BUS */
    ,{ 0x40000209UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [16] ADC1S15_Rx_CDC_VCAN_BUS */
    ,{ 0x40000180UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [17] ADC1S16_Rx_CDC_VCAN_BUS */
    ,{ 0x4000020AUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [18] ADC1S17_Rx_CDC_VCAN_BUS */
    ,{ 0x40000144UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [19] ADC1S27_Rx_CDC_VCAN_BUS */
    ,{ 0x400001C0UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [20] ADC1S31_Rx_CDC_VCAN_BUS */
    ,{ 0x400001F5UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [21] ADU1S03_Rx_CDC_VCAN_BUS */
    ,{ 0x400001F0UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [22] ADU1S05_Rx_CDC_VCAN_BUS */
    ,{ 0x4000022EUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [23] ADU1S06_Rx_CDC_VCAN_BUS */
    ,{ 0x4000020EUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [24] ADU1S07_Rx_CDC_VCAN_BUS */
    ,{ 0x40000072UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [25] ARS1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x400001DDUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [26] ARS1S90_Rx_CDC_VCAN_BUS */
    ,{ 0x4000016EUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [27] BAT1E45_Rx_CDC_VCAN_BUS */
    ,{ 0x400001EFUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [28] BAT1EDA_Rx_CDC_VCAN_BUS */
    ,{ 0x400003E5UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [29] BAT1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x40000124UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [30] BAT1S08_Rx_CDC_VCAN_BUS */
    ,{ 0x40000279UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [31] BAT2ED2_Rx_CDC_VCAN_BUS */
    ,{ 0x400003F3UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [32] BCC1S06_Rx_CDC_VCAN_BUS */
    ,{ 0x4000038BUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [33] BDB1F01_Rx_CDC_VCAN_BUS */
    ,{ 0x4000038DUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [34] BDB1F02_Rx_CDC_VCAN_BUS */
    ,{ 0x400001F4UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [35] BDB1F03_Rx_CDC_VCAN_BUS */
    ,{ 0x400001CFUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [36] BDB1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x40000621UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [37] BDB1S02_Rx_CDC_VCAN_BUS */
    ,{ 0x40000622UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [38] BDB1S03_Rx_CDC_VCAN_BUS */
    ,{ 0x40000623UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [39] BDB1S04_Rx_CDC_VCAN_BUS */
    ,{ 0x40000380UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [40] BDB1S05_Rx_CDC_VCAN_BUS */
    ,{ 0x40000624UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [41] BDB1S08_Rx_CDC_VCAN_BUS */
    ,{ 0x40000626UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [42] BDB1S10_Rx_CDC_VCAN_BUS */
    ,{ 0x4000062CUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [43] BDB1S13_Rx_CDC_VCAN_BUS */
    ,{ 0x400003FCUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [44] BDB1S19_Rx_CDC_VCAN_BUS */
    ,{ 0x40000629UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [45] BDB1S27_Rx_CDC_VCAN_BUS */
    ,{ 0x4000062AUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [46] BDB1S28_Rx_CDC_VCAN_BUS */
    ,{ 0x40000397UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [47] BDB1S29_Rx_CDC_VCAN_BUS */
    ,{ 0x400003B8UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [48] BDB1S36_Rx_CDC_VCAN_BUS */
    ,{ 0x40000312UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [49] BDC1S13_Rx_CDC_VCAN_BUS */
    ,{ 0x40000140UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [50] BDC1S23_Rx_CDC_VCAN_BUS */
    ,{ 0x400001D2UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [51] BDC1S33_Rx_CDC_VCAN_BUS */
    ,{ 0x40000148UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [52] BDC1S41_Rx_CDC_VCAN_BUS */
    ,{ 0x40000364UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [53] BDC1S45_Rx_CDC_VCAN_BUS */
    ,{ 0x400001D3UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [54] BDC1S46_Rx_CDC_VCAN_BUS */
    ,{ 0x40000337UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [55] BDC1S48_Rx_CDC_VCAN_BUS */
    ,{ 0x40000013UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [56] BDC1S52_Rx_CDC_VCAN_BUS */
    ,{ 0x4000001BUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [57] BDC1S60_Rx_CDC_VCAN_BUS */
    ,{ 0x40000341UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [58] BDC1S74_Rx_CDC_VCAN_BUS */
    ,{ 0x400001E3UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [59] BDC1S81_Rx_CDC_VCAN_BUS */
    ,{ 0x400001E4UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [60] BDC1S91_Rx_CDC_VCAN_BUS */
    ,{ 0x40000355UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [61] BDC1S97_Rx_CDC_VCAN_BUS */
    ,{ 0x40000358UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [62] BDC1S98_Rx_CDC_VCAN_BUS */
    ,{ 0x4000035DUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [63] BDC1S99_Rx_CDC_VCAN_BUS */
    ,{ 0x40000393UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [64] BDC1SC1_Rx_CDC_VCAN_BUS */
    ,{ 0x40000395UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [65] BDC1SC2_Rx_CDC_VCAN_BUS */
    ,{ 0x40000396UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [66] BDC1SC3_Rx_CDC_VCAN_BUS */
    ,{ 0x4000039AUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [67] BDC1SC4_Rx_CDC_VCAN_BUS */
    ,{ 0x4000039BUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [68] BDC1SC5_Rx_CDC_VCAN_BUS */
    ,{ 0x4000039DUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [69] BDC1SC6_Rx_CDC_VCAN_BUS */
    ,{ 0x4000039EUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [70] BDC1SC7_Rx_CDC_VCAN_BUS */
    ,{ 0x4000039FUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [71] BDC1SC8_Rx_CDC_VCAN_BUS */
    ,{ 0x400003A5UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [72] BDC1SC9_Rx_CDC_VCAN_BUS */
    ,{ 0x400003ACUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [73] BDC1SD1_Rx_CDC_VCAN_BUS */
    ,{ 0x400003AEUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [74] BDC1SD2_Rx_CDC_VCAN_BUS */
    ,{ 0x400003B2UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [75] BDC1SD3_Rx_CDC_VCAN_BUS */
    ,{ 0x400003B3UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [76] BDC1SD4_Rx_CDC_VCAN_BUS */
    ,{ 0x400003B9UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [77] BDC1SD5_Rx_CDC_VCAN_BUS */
    ,{ 0x400003BCUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [78] BDC1SD6_Rx_CDC_VCAN_BUS */
    ,{ 0x400003C6UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [79] BDC1SD7_Rx_CDC_VCAN_BUS */
    ,{ 0x400003C7UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [80] BDC1SD8_Rx_CDC_VCAN_BUS */
    ,{ 0x400003CDUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [81] BDC1SD9_Rx_CDC_VCAN_BUS */
    ,{ 0x400003D3UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [82] BDC1SE1_Rx_CDC_VCAN_BUS */
    ,{ 0x400003D6UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [83] BDC1SE2_Rx_CDC_VCAN_BUS */
    ,{ 0x400003DDUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [84] BDC1SE3_Rx_CDC_VCAN_BUS */
    ,{ 0x400003E1UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [85] BDC1SE4_Rx_CDC_VCAN_BUS */
    ,{ 0x400003EBUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [86] BDC1SE5_Rx_CDC_VCAN_BUS */
    ,{ 0x400003EFUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [87] BDC1SE6_Rx_CDC_VCAN_BUS */
    ,{ 0x400003F5UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [88] BDC1SE7_Rx_CDC_VCAN_BUS */
    ,{ 0x40000534UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [89] BDC1SH3_Rx_CDC_VCAN_BUS */
    ,{ 0x400002B3UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [90] BDC1SH8_Rx_CDC_VCAN_BUS */
    ,{ 0x400003E8UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [91] BDC1SI1_Rx_CDC_VCAN_BUS */
    ,{ 0x400003E9UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [92] BDC1SI2_Rx_CDC_VCAN_BUS */
    ,{ 0x400003F4UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [93] BDC1SI3_Rx_CDC_VCAN_BUS */
    ,{ 0x4000031EUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [94] BDC1SI4_Rx_CDC_VCAN_BUS */
    ,{ 0x4000031FUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [95] BDC1SI5_Rx_CDC_VCAN_BUS */
    ,{ 0x40000321UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [96] BDC1SI6_Rx_CDC_VCAN_BUS */
    ,{ 0x40000508UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [97] BDC1SI7_Rx_CDC_VCAN_BUS */
    ,{ 0x4000050BUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [98] BDC1SI8_Rx_CDC_VCAN_BUS */
    ,{ 0x4000050CUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [99] BDC1SI9_Rx_CDC_VCAN_BUS */
    ,{ 0x4000050EUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [100] BDC1SJ0_Rx_CDC_VCAN_BUS */
    ,{ 0x40000485UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [101] BDC1SJ1_Rx_CDC_VCAN_BUS */
    ,{ 0x4000050DUL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [102] BDC1SJ2_Rx_CDC_VCAN_BUS */
    ,{ 0x40000378UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [103] BDC1SJ5_Rx_CDC_VCAN_BUS */
    ,{ 0x40000610UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [104] BDC1SV1_Rx_CDC_VCAN_BUS */
    ,{ 0x40000602UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [105] BDC1SV2_Rx_CDC_VCAN_BUS */
    ,{ 0x40000596UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [106] BDC1SV3_Rx_CDC_VCAN_BUS */
    ,{ 0x4000037BUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [107] BDF3S01_Rx_CDC_VCAN_BUS */
    ,{ 0x4000018DUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [108] BDF3S02_Rx_CDC_VCAN_BUS */
    ,{ 0x4000019AUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [109] BDR3S02_Rx_CDC_VCAN_BUS */
    ,{ 0x400003CBUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [110] BKD1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x400003ABUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [111] BKD1S02_Rx_CDC_VCAN_BUS */
    ,{ 0x400003F6UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [112] BSR1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x40000235UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [113] BSR1S02_Rx_CDC_VCAN_BUS */
    ,{ 0x400002AFUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [114] BSR1S03_Rx_CDC_VCAN_BUS */
    ,{ 0x400001D9UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [115] CMB1S03_Rx_CDC_VCAN_BUS */
    ,{ 0x400002F3UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [116] CMB1S04_Rx_CDC_VCAN_BUS */
    ,{ 0x400000A9UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [117] CSR1G10_Rx_CDC_VCAN_BUS */
    ,{ 0x4000043AUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [118] CSR1S04_Rx_CDC_VCAN_BUS */
    ,{ 0x400003DBUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [119] CSR1S07_Rx_CDC_VCAN_BUS */
    ,{ 0x400003DCUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [120] CSR1S08_Rx_CDC_VCAN_BUS */
    ,{ 0x4000027DUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [121] DDM1S00_Rx_CDC_VCAN_BUS */
    ,{ 0x4000012BUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [122] DDM1S09_Rx_CDC_VCAN_BUS */
    ,{ 0x400000B8UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [123] DDM1S12_Rx_CDC_VCAN_BUS */
    ,{ 0x400002EEUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [124] DDM1S16_Rx_CDC_VCAN_BUS */
    ,{ 0x400001D7UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [125] DDM1S17_Rx_CDC_VCAN_BUS */
    ,{ 0x40000219UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [126] DDM1S32_Rx_CDC_VCAN_BUS */
    ,{ 0x400002E5UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [127] DDM1S35_Rx_CDC_VCAN_BUS */
    ,{ 0x40000528UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [128] DKY1S26_Rx_CDC_VCAN_BUS */
    ,{ 0x40000122UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [129] DMC1S08_Rx_CDC_VCAN_BUS */
    ,{ 0x40000285UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [130] DS11S27_Rx_CDC_VCAN_BUS */
    ,{ 0x40000317UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [131] DS11S37_Rx_CDC_VCAN_BUS */
    ,{ 0x40000608UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [132] DS11S40_Rx_CDC_VCAN_BUS */
    ,{ 0x40000411UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [133] DS12F02_Rx_CDC_VCAN_BUS */
    ,{ 0x40000412UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [134] DS12F03_Rx_CDC_VCAN_BUS */
    ,{ 0x400003F0UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [135] DST1S02_Rx_CDC_VCAN_BUS */
    ,{ 0x400004A0UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [136] EBU1D01_Rx_CDC_VCAN_BUS */
    ,{ 0x400003BFUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [137] ECT1G01_Rx_CDC_VCAN_BUS */
    ,{ 0x400002A1UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [138] ECT1G92_Rx_CDC_VCAN_BUS */
    ,{ 0x400003D4UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [139] ECT1S80_Rx_CDC_VCAN_BUS */
    ,{ 0x40000401UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [140] ECT1S93_Rx_CDC_VCAN_BUS */
    ,{ 0x400001BCUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [141] EHV1E96_Rx_CDC_VCAN_BUS */
    ,{ 0x4000007EUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [142] EHV1F02_Rx_CDC_VCAN_BUS */
    ,{ 0x400000A5UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [143] EHV1F04_Rx_CDC_VCAN_BUS */
    ,{ 0x40000128UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [144] EHV1G30_Rx_CDC_VCAN_BUS */
    ,{ 0x400001D0UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [145] EHV1S23_Rx_CDC_VCAN_BUS */
    ,{ 0x4000042FUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [146] EHV1S26_Rx_CDC_VCAN_BUS */
    ,{ 0x40000325UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [147] EHV1S31_Rx_CDC_VCAN_BUS */
    ,{ 0x400003B6UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [148] EHV1S90_Rx_CDC_VCAN_BUS */
    ,{ 0x40000421UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [149] EHV1S94_Rx_CDC_VCAN_BUS */
    ,{ 0x4000040BUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [150] EHV1S95_Rx_CDC_VCAN_BUS */
    ,{ 0x400001FAUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [151] EHV1S96_Rx_CDC_VCAN_BUS */
    ,{ 0x4000042BUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [152] EHV1S97_Rx_CDC_VCAN_BUS */
    ,{ 0x400002DEUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [153] EHV1S99_Rx_CDC_VCAN_BUS */
    ,{ 0x400000A6UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [154] EHV2G02_Rx_CDC_VCAN_BUS */
    ,{ 0x40000075UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [155] EHV2G10_Rx_CDC_VCAN_BUS */
    ,{ 0x400000A1UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [156] EHV2G20_Rx_CDC_VCAN_BUS */
    ,{ 0x40000202UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [157] EHV2G70_Rx_CDC_VCAN_BUS */
    ,{ 0x40000335UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [158] EIM1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x400005F3UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [159] ENG1C01_Rx_CDC_VCAN_BUS */
    ,{ 0x400005F4UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [160] ENG1C02_Rx_CDC_VCAN_BUS */
    ,{ 0x40000499UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [161] ENG1D51_Rx_CDC_VCAN_BUS */
    ,{ 0x4000049AUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [162] ENG1D52_Rx_CDC_VCAN_BUS */
    ,{ 0x4000049BUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [163] ENG1D53_Rx_CDC_VCAN_BUS */
    ,{ 0x4000049DUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [164] ENG1D55_Rx_CDC_VCAN_BUS */
    ,{ 0x400004A8UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [165] ENG1D56_Rx_CDC_VCAN_BUS */
    ,{ 0x400004AEUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [166] ENG1D59_Rx_CDC_VCAN_BUS */
    ,{ 0x400004AFUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [167] ENG1D60_Rx_CDC_VCAN_BUS */
    ,{ 0x400000A4UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [168] ENG1G03_Rx_CDC_VCAN_BUS */
    ,{ 0x400000A3UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [169] ENG1G17_Rx_CDC_VCAN_BUS */
    ,{ 0x4000051EUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [170] ENG1G90_Rx_CDC_VCAN_BUS */
    ,{ 0x400000FCUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [171] ENG1G92_Rx_CDC_VCAN_BUS */
    ,{ 0x40000589UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [172] ENG1S60_Rx_CDC_VCAN_BUS */
    ,{ 0x40000583UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [173] ENG1S99_Rx_CDC_VCAN_BUS */
    ,{ 0x400004A3UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [174] EPS1D50_Rx_CDC_VCAN_BUS */
    ,{ 0x40000062UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [175] EPS1S11_Rx_CDC_VCAN_BUS */
    ,{ 0x400001CAUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [176] EPS1S90_Rx_CDC_VCAN_BUS */
    ,{ 0x400005F6UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [177] FCM1C01_Rx_CDC_VCAN_BUS */
    ,{ 0x40000489UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [178] FCM1S10_Rx_CDC_VCAN_BUS */
    ,{ 0x4000048BUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [179] FCM1S12_Rx_CDC_VCAN_BUS */
    ,{ 0x40000251UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [180] FCM1S39_Rx_CDC_VCAN_BUS */
    ,{ 0x40000252UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [181] FCM1S40_Rx_CDC_VCAN_BUS */
    ,{ 0x40000261UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [182] FCM1S41_Rx_CDC_VCAN_BUS */
    ,{ 0x40000274UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [183] FCM1S49_Rx_CDC_VCAN_BUS */
    ,{ 0x40000275UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [184] FCM1S51_Rx_CDC_VCAN_BUS */
    ,{ 0x40000276UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [185] FCM1S52_Rx_CDC_VCAN_BUS */
    ,{ 0x4000027CUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [186] FCM1S58_Rx_CDC_VCAN_BUS */
    ,{ 0x4000025AUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [187] FCM1S70_Rx_CDC_VCAN_BUS */
    ,{ 0x40000159UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [188] FCM1S76_Rx_CDC_VCAN_BUS */
    ,{ 0x4000015AUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [189] FCM1S78_Rx_CDC_VCAN_BUS */
    ,{ 0x40000100UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [190] FCM1S79_Rx_CDC_VCAN_BUS */
    ,{ 0x400001B2UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [191] FCM1S90_Rx_CDC_VCAN_BUS */
    ,{ 0x40000259UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [192] FCM1S92_Rx_CDC_VCAN_BUS */
    ,{ 0x400000A8UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [193] FCM1S95_Rx_CDC_VCAN_BUS */
    ,{ 0x40000115UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [194] FWD1S10_Rx_CDC_VCAN_BUS */
    ,{ 0x40000633UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [195] IDT1S02_Rx_CDC_VCAN_BUS */
    ,{ 0x400003FBUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [196] IDT1S07_Rx_CDC_VCAN_BUS */
    ,{ 0x40000532UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [197] IDT1S15_Rx_CDC_VCAN_BUS */
    ,{ 0x400005ADUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [198] IMS1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x4000043BUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [199] IPA1S05_Rx_CDC_VCAN_BUS */
    ,{ 0x4000036BUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [200] ITS1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x400003DEUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [201] ITS1S04_Rx_CDC_VCAN_BUS */
    ,{ 0x40000314UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [202] ITS1S05_Rx_CDC_VCAN_BUS */
    ,{ 0x40000494UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [203] LVN1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x40000315UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [204] MET1S33_Rx_CDC_VCAN_BUS */
    ,{ 0x40000049UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [205] MGC1F13_Rx_CDC_VCAN_BUS */
    ,{ 0x400003BDUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [206] PCN1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x400001CCUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [207] PDC1G01_Rx_CDC_VCAN_BUS */
    ,{ 0x40000507UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [208] PDC1G02_Rx_CDC_VCAN_BUS */
    ,{ 0x400002F4UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [209] PDS1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x40000295UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [210] PLG1G15_Rx_CDC_VCAN_BUS */
    ,{ 0x40000296UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [211] PLG1G16_Rx_CDC_VCAN_BUS */
    ,{ 0x40000422UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [212] PLG1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x40000432UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [213] PLG1S06_Rx_CDC_VCAN_BUS */
    ,{ 0x400002A6UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [214] PLG1S20_Rx_CDC_VCAN_BUS */
    ,{ 0x40000204UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [215] PLG1S21_Rx_CDC_VCAN_BUS */
    ,{ 0x400001D1UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [216] PMN1G03_Rx_CDC_VCAN_BUS */
    ,{ 0x40000403UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [217] PST1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x40000230UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [218] RCP1S02_Rx_CDC_VCAN_BUS */
    ,{ 0x4000014FUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [219] RCP1S03_Rx_CDC_VCAN_BUS */
    ,{ 0x400002C6UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [220] RCP1S04_Rx_CDC_VCAN_BUS */
    ,{ 0x400002C7UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [221] RCP1S05_Rx_CDC_VCAN_BUS */
    ,{ 0x400002C8UL, (BswU1)64U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [222] RCP1S06_Rx_CDC_VCAN_BUS */
    ,{ 0x400003CAUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [223] RSE1G20_Rx_CDC_VCAN_BUS */
    ,{ 0x4000032FUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [224] RSE1G24_Rx_CDC_VCAN_BUS */
    ,{ 0x40000336UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [225] RSE1G25_Rx_CDC_VCAN_BUS */
    ,{ 0x4000034DUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [226] RSE1G26_Rx_CDC_VCAN_BUS */
    ,{ 0x400003C8UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [227] RSE1S02_Rx_CDC_VCAN_BUS */
    ,{ 0x400001DBUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [228] SBW1G02_Rx_CDC_VCAN_BUS */
    ,{ 0x40000439UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [229] SCN1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x40000375UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [230] SCN1S02_Rx_CDC_VCAN_BUS */
    ,{ 0x400002FDUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [231] SCS1S11_Rx_CDC_VCAN_BUS */
    ,{ 0x400002FEUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [232] SCS1S14_Rx_CDC_VCAN_BUS */
    ,{ 0x4000040CUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [233] SOL1S02_Rx_CDC_VCAN_BUS */
    ,{ 0x400001BBUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [234] SOL1S06_Rx_CDC_VCAN_BUS */
    ,{ 0x40000495UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [235] TPM1S02_Rx_CDC_VCAN_BUS */
    ,{ 0x40000496UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [236] TPM1S03_Rx_CDC_VCAN_BUS */
    ,{ 0x40000347UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [237] TPM1S04_Rx_CDC_VCAN_BUS */
    ,{ 0x4000034CUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [238] TPM1S05_Rx_CDC_VCAN_BUS */
    ,{ 0x4000036FUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [239] TPM1S07_Rx_CDC_VCAN_BUS */
    ,{ 0x400002A0UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [240] TRA1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x400003E7UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [241] UCB1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x40000318UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [242] VAS1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x400004A4UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [243] VGR1D50_Rx_CDC_VCAN_BUS */
    ,{ 0x400004A1UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [244] VSC1D51_Rx_CDC_VCAN_BUS */
    ,{ 0x4000006AUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [245] VSC1F01_Rx_CDC_VCAN_BUS */
    ,{ 0x40000069UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [246] VSC1G12_Rx_CDC_VCAN_BUS */
    ,{ 0x4000009EUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [247] VSC1G13_Rx_CDC_VCAN_BUS */
    ,{ 0x400000B7UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [248] VSC1G14_Rx_CDC_VCAN_BUS */
    ,{ 0x40000262UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [249] VSC1G96_Rx_CDC_VCAN_BUS */
    ,{ 0x40000601UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [250] VUM1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x400002F9UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [251] WIP1S01_Rx_CDC_VCAN_BUS */
    ,{ 0x4000037FUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [252] ZN11S02_Rx_CDC_VCAN_BUS */
    ,{ 0x4000038AUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [253] ZN11S03_Rx_CDC_VCAN_BUS */
    ,{ 0x40000086UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [254] ZN11S08_Rx_CDC_VCAN_BUS */
    ,{ 0x400001DEUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [255] ZN11S14_Rx_CDC_VCAN_BUS */
    ,{ 0x400001DFUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [256] ZN11S17_Rx_CDC_VCAN_BUS */
    ,{ 0x40000368UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [257] ZN11S19_Rx_CDC_VCAN_BUS */
    ,{ 0x4000036AUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [258] ZN11S26_Rx_CDC_VCAN_BUS */
    ,{ 0x40000500UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [259] ZN11S38_Rx_CDC_VCAN_BUS */
    ,{ 0x4000036EUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [260] ZN11S60_Rx_CDC_VCAN_BUS */
    ,{ 0x4000033FUL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [261] ZN11S63_Rx_CDC_VCAN_BUS */
    ,{ 0x400003D2UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [262] ZN11S64_Rx_CDC_VCAN_BUS */
    ,{ 0x400003F9UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [263] ZN11S65_Rx_CDC_VCAN_BUS */
    ,{ 0x40000400UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [264] ZN11S66_Rx_CDC_VCAN_BUS */
    ,{ 0x40000404UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [265] ZN11S67_Rx_CDC_VCAN_BUS */
    ,{ 0x400001E1UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [266] ZN21S05_Rx_CDC_VCAN_BUS */
    ,{ 0x40000390UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [267] ZN21S13_Rx_CDC_VCAN_BUS */
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
     { 0x00000442UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [0] CDC1N01_Rx_CDC_VCAN_BUS */
    ,{ 0x0000047EUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [1] VIV1N99_Rx_CDC_VCAN_BUS */
    ,{ 0x0000047FUL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [2] VCE1N99_Rx_CDC_VCAN_BUS */
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
     { 0x98DA17E0UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [0] Nsdu_RX_RxNPdu_Diag_Physical_Service */
    ,{ 0x98DBEFE0UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [1] Nsdu_RX_RxNPdu_Diag_Functional_Service */
    ,{ 0x98DA17E1UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [2] Nsdu_RX_RxNPdu_Diag_Physical_Remote */
    ,{ 0x98DBEFE1UL, (BswU1) 8U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [3] Nsdu_RX_RxNPdu_Diag_Functional_Remote */
    ,{ 0xD8DA17E0UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [4] Nsdu_RX_RxNPdu_Diag_Physical_FD_Service */
    ,{ 0xD8DBEFE0UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [5] Nsdu_RX_RxNPdu_Diag_Functional_FD_Service */
    ,{ 0xD8DA17E1UL, (BswU1)32U, (BswU1)BSW_CANIF_CH0,  (BswU2)0U }  /* [6] Nsdu_RX_RxNPdu_Diag_Physical_FD_Remote */
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
     (BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [0] MET1S47_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [1] MET1S01_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [2] MET1S55_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [3] MET1S44_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [4] MET1S52_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [5] CDC1S01_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [6] CDC1S03_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [7] MET1S70_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [8] MET1S28_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [9] MET1S27_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [10] MET1S29_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [11] MET1S30_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [12] HUD1S01_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [13] MET1S62_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [14] DMS1S02_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [15] MET1S38_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [16] MET1S41_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [17] MET1S43_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [18] CDC1N02_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [19] MET1S25_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [20] MET1S02_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [21] MET1S10_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [22] MET1S11_Tx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [23] QSEV_Tx_CANFD_VCC_1_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [24] ABG1D50_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [25] ABG1D51_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [26] ABG1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [27] ABG1S09_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [28] ACN1D50_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [29] ACN1S03_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [30] ACN1S04_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [31] ACN1S15_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [32] ACN1S25_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [33] ACN1S29_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [34] ADC1S08_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [35] ADC1S10_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [36] ADC1S11_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [37] ADC1S12_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [38] ADC1S13_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [39] ADC1S14_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [40] ADC1S15_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [41] ADC1S16_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [42] ADC1S17_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [43] ADC1S27_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [44] ADC1S31_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [45] ADU1S03_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [46] ADU1S05_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [47] ADU1S06_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [48] ADU1S07_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [49] ARS1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [50] ARS1S90_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [51] BAT1E45_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [52] BAT1EDA_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [53] BAT1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [54] BAT1S08_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [55] BAT2ED2_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [56] BCC1S06_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [57] BDB1F01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [58] BDB1F02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [59] BDB1F03_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [60] BDB1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [61] BDB1S02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [62] BDB1S03_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [63] BDB1S04_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [64] BDB1S05_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [65] BDB1S08_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [66] BDB1S10_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [67] BDB1S13_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [68] BDB1S19_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [69] BDB1S27_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [70] BDB1S28_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [71] BDB1S29_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [72] BDB1S36_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [73] BDC1S13_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [74] BDC1S23_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [75] BDC1S33_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [76] BDC1S41_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [77] BDC1S45_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [78] BDC1S46_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [79] BDC1S48_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [80] BDC1S52_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [81] BDC1S60_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [82] BDC1S74_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [83] BDC1S81_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [84] BDC1S91_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [85] BDC1S97_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [86] BDC1S98_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [87] BDC1S99_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [88] BDC1SC1_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [89] BDC1SC2_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [90] BDC1SC3_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [91] BDC1SC4_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [92] BDC1SC5_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [93] BDC1SC6_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [94] BDC1SC7_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [95] BDC1SC8_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [96] BDC1SC9_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [97] BDC1SD1_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [98] BDC1SD2_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [99] BDC1SD3_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [100] BDC1SD4_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [101] BDC1SD5_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [102] BDC1SD6_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [103] BDC1SD7_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [104] BDC1SD8_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [105] BDC1SD9_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [106] BDC1SE1_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [107] BDC1SE2_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [108] BDC1SE3_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [109] BDC1SE4_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [110] BDC1SE5_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [111] BDC1SE6_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [112] BDC1SE7_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [113] BDC1SH3_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [114] BDC1SH8_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [115] BDC1SI1_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [116] BDC1SI2_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [117] BDC1SI3_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [118] BDC1SI4_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [119] BDC1SI5_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [120] BDC1SI6_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [121] BDC1SI7_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [122] BDC1SI8_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [123] BDC1SI9_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [124] BDC1SJ0_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [125] BDC1SJ1_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [126] BDC1SJ2_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [127] BDC1SJ5_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [128] BDC1SV1_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [129] BDC1SV2_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [130] BDC1SV3_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [131] BDF3S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [132] BDF3S02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [133] BDR3S02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [134] BKD1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [135] BKD1S02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [136] BSR1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [137] BSR1S02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [138] BSR1S03_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [139] CMB1S03_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [140] CMB1S04_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [141] CSR1G10_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [142] CSR1S04_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [143] CSR1S07_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [144] CSR1S08_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [145] DDM1S00_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [146] DDM1S09_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [147] DDM1S12_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [148] DDM1S16_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [149] DDM1S17_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [150] DDM1S32_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [151] DDM1S35_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [152] DKY1S26_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [153] DMC1S08_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [154] DS11S27_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [155] DS11S37_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [156] DS11S40_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [157] DS12F02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [158] DS12F03_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [159] DST1S02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [160] EBU1D01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [161] ECT1G01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [162] ECT1G92_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [163] ECT1S80_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [164] ECT1S93_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [165] EHV1E96_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [166] EHV1F02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [167] EHV1F04_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [168] EHV1G30_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [169] EHV1S23_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [170] EHV1S26_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [171] EHV1S31_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [172] EHV1S90_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [173] EHV1S94_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [174] EHV1S95_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [175] EHV1S96_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [176] EHV1S97_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [177] EHV1S99_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [178] EHV2G02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [179] EHV2G10_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [180] EHV2G20_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [181] EHV2G70_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [182] EIM1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [183] ENG1C01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [184] ENG1C02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [185] ENG1D51_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [186] ENG1D52_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [187] ENG1D53_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [188] ENG1D55_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [189] ENG1D56_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [190] ENG1D59_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [191] ENG1D60_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [192] ENG1G03_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [193] ENG1G17_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [194] ENG1G90_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [195] ENG1G92_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [196] ENG1S60_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [197] ENG1S99_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [198] EPS1D50_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [199] EPS1S11_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [200] EPS1S90_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [201] FCM1C01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [202] FCM1S10_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [203] FCM1S12_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [204] FCM1S39_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [205] FCM1S40_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [206] FCM1S41_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [207] FCM1S49_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [208] FCM1S51_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [209] FCM1S52_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [210] FCM1S58_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [211] FCM1S70_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [212] FCM1S76_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [213] FCM1S78_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [214] FCM1S79_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [215] FCM1S90_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [216] FCM1S92_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [217] FCM1S95_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [218] FWD1S10_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [219] IDT1S02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [220] IDT1S07_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [221] IDT1S15_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [222] IMS1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [223] IPA1S05_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [224] ITS1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [225] ITS1S04_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [226] ITS1S05_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [227] LVN1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [228] MET1S33_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [229] MGC1F13_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [230] PCN1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [231] PDC1G01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [232] PDC1G02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [233] PDS1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [234] PLG1G15_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [235] PLG1G16_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [236] PLG1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [237] PLG1S06_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [238] PLG1S20_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [239] PLG1S21_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [240] PMN1G03_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [241] PST1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [242] RCP1S02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [243] RCP1S03_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [244] RCP1S04_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [245] RCP1S05_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [246] RCP1S06_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [247] RSE1G20_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [248] RSE1G24_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [249] RSE1G25_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [250] RSE1G26_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [251] RSE1S02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [252] SBW1G02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [253] SCN1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [254] SCN1S02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [255] SCS1S11_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [256] SCS1S14_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [257] SOL1S02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [258] SOL1S06_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [259] TPM1S02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [260] TPM1S03_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [261] TPM1S04_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [262] TPM1S05_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [263] TPM1S07_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [264] TRA1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [265] UCB1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [266] VAS1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [267] VGR1D50_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [268] VSC1D51_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [269] VSC1F01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [270] VSC1G12_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [271] VSC1G13_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [272] VSC1G14_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [273] VSC1G96_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [274] VUM1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [275] WIP1S01_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [276] ZN11S02_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [277] ZN11S03_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [278] ZN11S08_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [279] ZN11S14_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [280] ZN11S17_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [281] ZN11S19_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [282] ZN11S26_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [283] ZN11S38_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [284] ZN11S60_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [285] ZN11S63_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [286] ZN11S64_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [287] ZN11S65_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [288] ZN11S66_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [289] ZN11S67_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [290] ZN21S05_Rx_CDC_VCAN_BUS */
    ,(BswU1)( BSW_CANIF_CHECKSUM_NOUSE | BSW_CANIF_NMMSG_NOUSE | BSW_CANIF_MSGID_NOUSE | BSW_CANIF_AVCLAN_NOUSE | BSW_CANIF_PRETRXMSG_NOUSE )  /* [291] ZN21S13_Rx_CDC_VCAN_BUS */
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
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v3-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
