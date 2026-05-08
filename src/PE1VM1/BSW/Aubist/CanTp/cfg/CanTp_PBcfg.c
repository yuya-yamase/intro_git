/* cantp_pbcfg_c_v3-0-0                                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CANTP/PBCFG/CODE                                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>
#include "../inc/bsw_cantp_MemMap.h"

#include <bswm_cs/bsw_bswm_cs.h>
#include <comm/bsw_comm.h>
#include "../../ComM/inc/bsw_comm_config.h"
#include "../../BswM_CS/inc/bsw_bswm_cs_config.h"

#if( BSW_BSWM_CS_FUNC_CANTP == BSW_USE )
#include <cantp/bsw_cantp.h>
#include <pdur/bsw_pdur.h>

#include "./CanTp_Cfg.h"
#include "../inc/bsw_cantp_cmn.h"

#include "../inc/bsw_cantp_config.h"

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

/*==================================================================*/
/* RxNSdu Configuration Table                                       */
/*==================================================================*/
BswConst Bsw_CanTp_RxNSduCfgType bsw_cantp_stRxNSduCfgTbl[BSW_CANTP_RXNSDUNUM] =
{
    /*========== User define Area [Start] ==========*/
    {                                                       /* [0] NSduName:Nsdu_RX_RxNSdu_Diag_Physical_Service*/
        (uint16)0U                                          /* RxNSdu Config Table Index            */
       ,(uint8)0U                                           /* Parent Connection Channel Id         */
       ,(uint8)0U                                           /* Extend                               */

       ,(uint16)(BSW_PDUR_LOCOMP_CANTP | 0x0004U)           /* NSduId                               */
       ,(uint16)(BSW_PDUR_LOCOMP_CANTP | 0x0004U)           /* NPduId                               */
       ,(uint16)(BSW_PDUR_LOCOMP_CANTP | 0x0000U)           /* FC NPduId                            */
       ,(uint16)(BSW_PDUR_LOCOMP_CANTP | 0x0004U)           /* PduR RxIndication Id                 */
       ,(uint16)(BSW_PDUR_LOCOMP_CANTP | 0x0000U)           /* CanIf PduId                          */

       ,(uint8)BSW_CANTP_NORMALFIXED                        /* Addressing Format                    */
       ,(uint8)BSW_CANTP_PHYSICAL                           /* TaType                               */
       ,(uint8)0U                                           /* NTa                                  */
       ,(uint8)0U                                           /* NSa                                  */

       ,BSW_CANTP_u2MS2MAINFUNC_CYCLE(1000U)                /* N_Ar(MainFunction cycle count)       */
       ,BSW_CANTP_u2MS2MAINFUNC_CYCLE(1000U)                /* N_Cr(MainFunction cycle count)       */

       ,(uint8)0U                                           /* BlockSize                            */
       ,(uint8)0U                                           /* STmin                                */
       ,(uint16)0U                                          /* WFTmax                               */
       ,(uint8)BSW_CANTP_ON                                 /* SF/FF/CF RX PaddingActivation        */
       ,(uint8)BSW_CANTP_ON                                 /* FC Tx PaddingActivation              */
       ,(uint8)0U                                           /* NAe                                  */
       ,(uint8)0U                                           /* Priority                             */
    }
   ,{                                                       /* [1] NSduName:Nsdu_RX_RxNSdu_Diag_Functional_Service*/
        (uint16)1U                                          /* RxNSdu Config Table Index            */
       ,(uint8)1U                                           /* Parent Connection Channel Id         */
       ,(uint8)0U                                           /* Extend                               */

       ,(uint16)(BSW_PDUR_LOCOMP_CANTP | 0x0005U)           /* NSduId                               */
       ,(uint16)(BSW_PDUR_LOCOMP_CANTP | 0x0005U)           /* NPduId                               */
       ,(uint16)(0xFFFFU)                                   /* FC NPduId                            */
       ,(uint16)(BSW_PDUR_LOCOMP_CANTP | 0x0005U)           /* PduR RxIndication Id                 */
       ,(uint16)(0xFFFFU)                                   /* CanIf PduId                          */

       ,(uint8)BSW_CANTP_NORMALFIXED                        /* Addressing Format                    */
       ,(uint8)BSW_CANTP_FUNCTIONAL                         /* TaType                               */
       ,(uint8)0U                                           /* NTa                                  */
       ,(uint8)0U                                           /* NSa                                  */

       ,BSW_CANTP_u2MS2MAINFUNC_CYCLE(0U)                   /* N_Ar(MainFunction cycle count)       */
       ,BSW_CANTP_u2MS2MAINFUNC_CYCLE(0U)                   /* N_Cr(MainFunction cycle count)       */

       ,(uint8)0U                                           /* BlockSize                            */
       ,(uint8)0U                                           /* STmin                                */
       ,(uint16)0U                                          /* WFTmax                               */
       ,(uint8)BSW_CANTP_ON                                 /* SF/FF/CF RX PaddingActivation        */
       ,(uint8)BSW_CANTP_OFF                                /* FC Tx PaddingActivation              */
       ,(uint8)0U                                           /* NAe                                  */
       ,(uint8)0U                                           /* Priority                             */
    }
   ,{                                                       /* [2] NSduName:Nsdu_RX_RxNSdu_Diag_Physical_Remote*/
        (uint16)2U                                          /* RxNSdu Config Table Index            */
       ,(uint8)2U                                           /* Parent Connection Channel Id         */
       ,(uint8)0U                                           /* Extend                               */

       ,(uint16)(BSW_PDUR_LOCOMP_CANTP | 0x0006U)           /* NSduId                               */
       ,(uint16)(BSW_PDUR_LOCOMP_CANTP | 0x0006U)           /* NPduId                               */
       ,(uint16)(BSW_PDUR_LOCOMP_CANTP | 0x0001U)           /* FC NPduId                            */
       ,(uint16)(BSW_PDUR_LOCOMP_CANTP | 0x0006U)           /* PduR RxIndication Id                 */
       ,(uint16)(BSW_PDUR_LOCOMP_CANTP | 0x0001U)           /* CanIf PduId                          */

       ,(uint8)BSW_CANTP_NORMALFIXED                        /* Addressing Format                    */
       ,(uint8)BSW_CANTP_PHYSICAL                           /* TaType                               */
       ,(uint8)0U                                           /* NTa                                  */
       ,(uint8)0U                                           /* NSa                                  */

       ,BSW_CANTP_u2MS2MAINFUNC_CYCLE(1000U)                /* N_Ar(MainFunction cycle count)       */
       ,BSW_CANTP_u2MS2MAINFUNC_CYCLE(1000U)                /* N_Cr(MainFunction cycle count)       */

       ,(uint8)0U                                           /* BlockSize                            */
       ,(uint8)0U                                           /* STmin                                */
       ,(uint16)0U                                          /* WFTmax                               */
       ,(uint8)BSW_CANTP_ON                                 /* SF/FF/CF RX PaddingActivation        */
       ,(uint8)BSW_CANTP_ON                                 /* FC Tx PaddingActivation              */
       ,(uint8)0U                                           /* NAe                                  */
       ,(uint8)0U                                           /* Priority                             */
    }
   ,{                                                       /* [3] NSduName:Nsdu_RX_RxNSdu_Diag_Functional_Remote*/
        (uint16)3U                                          /* RxNSdu Config Table Index            */
       ,(uint8)3U                                           /* Parent Connection Channel Id         */
       ,(uint8)0U                                           /* Extend                               */

       ,(uint16)(BSW_PDUR_LOCOMP_CANTP | 0x0007U)           /* NSduId                               */
       ,(uint16)(BSW_PDUR_LOCOMP_CANTP | 0x0007U)           /* NPduId                               */
       ,(uint16)(0xFFFFU)                                   /* FC NPduId                            */
       ,(uint16)(BSW_PDUR_LOCOMP_CANTP | 0x0007U)           /* PduR RxIndication Id                 */
       ,(uint16)(0xFFFFU)                                   /* CanIf PduId                          */

       ,(uint8)BSW_CANTP_NORMALFIXED                        /* Addressing Format                    */
       ,(uint8)BSW_CANTP_FUNCTIONAL                         /* TaType                               */
       ,(uint8)0U                                           /* NTa                                  */
       ,(uint8)0U                                           /* NSa                                  */

       ,BSW_CANTP_u2MS2MAINFUNC_CYCLE(0U)                   /* N_Ar(MainFunction cycle count)       */
       ,BSW_CANTP_u2MS2MAINFUNC_CYCLE(0U)                   /* N_Cr(MainFunction cycle count)       */

       ,(uint8)0U                                           /* BlockSize                            */
       ,(uint8)0U                                           /* STmin                                */
       ,(uint16)0U                                          /* WFTmax                               */
       ,(uint8)BSW_CANTP_ON                                 /* SF/FF/CF RX PaddingActivation        */
       ,(uint8)BSW_CANTP_OFF                                /* FC Tx PaddingActivation              */
       ,(uint8)0U                                           /* NAe                                  */
       ,(uint8)0U                                           /* Priority                             */
    }
   ,{                                                       /* [4] NSduName:Nsdu_RX_RxNSdu_Diag_Physical_FD_Service*/
        (uint16)4U                                          /* RxNSdu Config Table Index            */
       ,(uint8)4U                                           /* Parent Connection Channel Id         */
       ,(uint8)0U                                           /* Extend                               */

       ,(uint16)(BSW_PDUR_LOCOMP_CANTP | 0x0008U)           /* NSduId                               */
       ,(uint16)(BSW_PDUR_LOCOMP_CANTP | 0x0008U)           /* NPduId                               */
       ,(uint16)(BSW_PDUR_LOCOMP_CANTP | 0x0002U)           /* FC NPduId                            */
       ,(uint16)(BSW_PDUR_LOCOMP_CANTP | 0x0008U)           /* PduR RxIndication Id                 */
       ,(uint16)(BSW_PDUR_LOCOMP_CANTP | 0x0002U)           /* CanIf PduId                          */

       ,(uint8)BSW_CANTP_NORMALFIXED                        /* Addressing Format                    */
       ,(uint8)BSW_CANTP_PHYSICAL                           /* TaType                               */
       ,(uint8)0U                                           /* NTa                                  */
       ,(uint8)0U                                           /* NSa                                  */

       ,BSW_CANTP_u2MS2MAINFUNC_CYCLE(1000U)                /* N_Ar(MainFunction cycle count)       */
       ,BSW_CANTP_u2MS2MAINFUNC_CYCLE(1000U)                /* N_Cr(MainFunction cycle count)       */

       ,(uint8)0U                                           /* BlockSize                            */
       ,(uint8)0U                                           /* STmin                                */
       ,(uint16)0U                                          /* WFTmax                               */
       ,(uint8)BSW_CANTP_ON                                 /* SF/FF/CF RX PaddingActivation        */
       ,(uint8)BSW_CANTP_ON                                 /* FC Tx PaddingActivation              */
       ,(uint8)0U                                           /* NAe                                  */
       ,(uint8)0U                                           /* Priority                             */
    }
   ,{                                                       /* [5] NSduName:Nsdu_RX_RxNSdu_Diag_Functional_FD_Service*/
        (uint16)5U                                          /* RxNSdu Config Table Index            */
       ,(uint8)5U                                           /* Parent Connection Channel Id         */
       ,(uint8)0U                                           /* Extend                               */

       ,(uint16)(BSW_PDUR_LOCOMP_CANTP | 0x0009U)           /* NSduId                               */
       ,(uint16)(BSW_PDUR_LOCOMP_CANTP | 0x0009U)           /* NPduId                               */
       ,(uint16)(0xFFFFU)                                   /* FC NPduId                            */
       ,(uint16)(BSW_PDUR_LOCOMP_CANTP | 0x0009U)           /* PduR RxIndication Id                 */
       ,(uint16)(0xFFFFU)                                   /* CanIf PduId                          */

       ,(uint8)BSW_CANTP_NORMALFIXED                        /* Addressing Format                    */
       ,(uint8)BSW_CANTP_FUNCTIONAL                         /* TaType                               */
       ,(uint8)0U                                           /* NTa                                  */
       ,(uint8)0U                                           /* NSa                                  */

       ,BSW_CANTP_u2MS2MAINFUNC_CYCLE(0U)                   /* N_Ar(MainFunction cycle count)       */
       ,BSW_CANTP_u2MS2MAINFUNC_CYCLE(0U)                   /* N_Cr(MainFunction cycle count)       */

       ,(uint8)0U                                           /* BlockSize                            */
       ,(uint8)0U                                           /* STmin                                */
       ,(uint16)0U                                          /* WFTmax                               */
       ,(uint8)BSW_CANTP_ON                                 /* SF/FF/CF RX PaddingActivation        */
       ,(uint8)BSW_CANTP_OFF                                /* FC Tx PaddingActivation              */
       ,(uint8)0U                                           /* NAe                                  */
       ,(uint8)0U                                           /* Priority                             */
    }
   ,{                                                       /* [6] NSduName:Nsdu_RX_RxNSdu_Diag_Physical_FD_Remote*/
        (uint16)6U                                          /* RxNSdu Config Table Index            */
       ,(uint8)6U                                           /* Parent Connection Channel Id         */
       ,(uint8)0U                                           /* Extend                               */

       ,(uint16)(BSW_PDUR_LOCOMP_CANTP | 0x000AU)           /* NSduId                               */
       ,(uint16)(BSW_PDUR_LOCOMP_CANTP | 0x000AU)           /* NPduId                               */
       ,(uint16)(BSW_PDUR_LOCOMP_CANTP | 0x0003U)           /* FC NPduId                            */
       ,(uint16)(BSW_PDUR_LOCOMP_CANTP | 0x000AU)           /* PduR RxIndication Id                 */
       ,(uint16)(BSW_PDUR_LOCOMP_CANTP | 0x0003U)           /* CanIf PduId                          */

       ,(uint8)BSW_CANTP_NORMALFIXED                        /* Addressing Format                    */
       ,(uint8)BSW_CANTP_PHYSICAL                           /* TaType                               */
       ,(uint8)0U                                           /* NTa                                  */
       ,(uint8)0U                                           /* NSa                                  */

       ,BSW_CANTP_u2MS2MAINFUNC_CYCLE(1000U)                /* N_Ar(MainFunction cycle count)       */
       ,BSW_CANTP_u2MS2MAINFUNC_CYCLE(1000U)                /* N_Cr(MainFunction cycle count)       */

       ,(uint8)0U                                           /* BlockSize                            */
       ,(uint8)0U                                           /* STmin                                */
       ,(uint16)0U                                          /* WFTmax                               */
       ,(uint8)BSW_CANTP_ON                                 /* SF/FF/CF RX PaddingActivation        */
       ,(uint8)BSW_CANTP_ON                                 /* FC Tx PaddingActivation              */
       ,(uint8)0U                                           /* NAe                                  */
       ,(uint8)0U                                           /* Priority                             */
    }
   ,{                                                       /* [7] NSduName:Nsdu_RX_RxNSdu_Diag_Functional_FD_Remote*/
        (uint16)7U                                          /* RxNSdu Config Table Index            */
       ,(uint8)7U                                           /* Parent Connection Channel Id         */
       ,(uint8)0U                                           /* Extend                               */

       ,(uint16)(BSW_PDUR_LOCOMP_CANTP | 0x000BU)           /* NSduId                               */
       ,(uint16)(BSW_PDUR_LOCOMP_CANTP | 0x000BU)           /* NPduId                               */
       ,(uint16)(0xFFFFU)                                   /* FC NPduId                            */
       ,(uint16)(BSW_PDUR_LOCOMP_CANTP | 0x000BU)           /* PduR RxIndication Id                 */
       ,(uint16)(0xFFFFU)                                   /* CanIf PduId                          */

       ,(uint8)BSW_CANTP_NORMALFIXED                        /* Addressing Format                    */
       ,(uint8)BSW_CANTP_FUNCTIONAL                         /* TaType                               */
       ,(uint8)0U                                           /* NTa                                  */
       ,(uint8)0U                                           /* NSa                                  */

       ,BSW_CANTP_u2MS2MAINFUNC_CYCLE(0U)                   /* N_Ar(MainFunction cycle count)       */
       ,BSW_CANTP_u2MS2MAINFUNC_CYCLE(0U)                   /* N_Cr(MainFunction cycle count)       */

       ,(uint8)0U                                           /* BlockSize                            */
       ,(uint8)0U                                           /* STmin                                */
       ,(uint16)0U                                          /* WFTmax                               */
       ,(uint8)BSW_CANTP_ON                                 /* SF/FF/CF RX PaddingActivation        */
       ,(uint8)BSW_CANTP_OFF                                /* FC Tx PaddingActivation              */
       ,(uint8)0U                                           /* NAe                                  */
       ,(uint8)0U                                           /* Priority                             */
    }
    /*========== User define Area [End] ============*/
};

#if( BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE )
BswConst Bsw_CanTp_RxNSduParamType bsw_cantp_stRxNSduParamTbl[BSW_CANTP_CFG_RXPARAMPTNNUM] =
{
    /*========== User define Area [Start] ==========*/
    /*========== User define Area [End] ============*/
};
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */

/*==================================================================*/
/* TxNSdu Configuration Table                                       */
/*==================================================================*/
BswConst Bsw_CanTp_TxNSduCfgType bsw_cantp_stTxNSduCfgTbl[BSW_CANTP_TXNSDUNUM] =
{
    /*========== User define Area [Start] ==========*/
    {                                                       /* [0] NSduName:Nsdu_TX_TxNSdu_Diag_Physical_Service*/
        (uint16)0U                                          /* TxNSdu Config Table Index            */
       ,(uint8)0U                                           /* Parent Connection Channel Id         */
       ,(uint8)0U                                           /* Extend                               */

       ,(uint16)(BSW_PDUR_LOCOMP_CANTP | 0x0000U)           /* NSduId                               */
       ,(uint16)(BSW_PDUR_LOCOMP_CANTP | 0x0000U)           /* NPduId                               */
       ,(uint16)(BSW_PDUR_LOCOMP_CANTP | 0x0004U)           /* FC NPduId                            */
       ,(uint16)(BSW_PDUR_LOCOMP_CANTP | 0x0000U)           /* PduR TxConfirmation Id               */
       ,(uint16)(BSW_PDUR_LOCOMP_CANTP | 0x0000U)           /* CanIf PduId                          */

       ,(uint8)BSW_CANTP_NORMALFIXED                        /* Addressing Format                    */
       ,(uint8)BSW_CANTP_PHYSICAL                           /* TaType                               */
       ,(uint8)0U                                           /* NTa                                  */
       ,(uint8)0U                                           /* NSa                                  */

       ,BSW_CANTP_u2MS2MAINFUNC_CYCLE(1000U)                /* N_As(MainFunction cycle count)       */
       ,BSW_CANTP_u2MS2MAINFUNC_CYCLE(1000U)                /* N_Bs(MainFunction cycle count)       */

       ,(uint8)8U                                           /* Transmit NPdu Length                 */
       ,(uint8)BSW_CANTP_FALSE                              /* Transmit Cancel                      */
       ,(uint8)BSW_CANTP_TX_INCOMPLETE                      /* New Msg Rx Handling In Last Msg Tx   */
       ,(uint8)BSW_CANTP_ON                                 /* SF/FF/CF TX PaddingActivation        */
       ,(uint8)BSW_CANTP_ON                                 /* FC Rx PaddingActivation              */
       ,(uint8)0U                                           /* NAe                                  */
       ,(uint8)0U                                           /* Priority                             */
       ,(uint8)0U                                           /* Extend                               */
    }
   ,{                                                       /* [1] NSduName:Nsdu_TX_TxNSdu_Diag_Physical_Remote*/
        (uint16)1U                                          /* TxNSdu Config Table Index            */
       ,(uint8)2U                                           /* Parent Connection Channel Id         */
       ,(uint8)0U                                           /* Extend                               */

       ,(uint16)(BSW_PDUR_LOCOMP_CANTP | 0x0001U)           /* NSduId                               */
       ,(uint16)(BSW_PDUR_LOCOMP_CANTP | 0x0001U)           /* NPduId                               */
       ,(uint16)(BSW_PDUR_LOCOMP_CANTP | 0x0006U)           /* FC NPduId                            */
       ,(uint16)(BSW_PDUR_LOCOMP_CANTP | 0x0001U)           /* PduR TxConfirmation Id               */
       ,(uint16)(BSW_PDUR_LOCOMP_CANTP | 0x0001U)           /* CanIf PduId                          */

       ,(uint8)BSW_CANTP_NORMALFIXED                        /* Addressing Format                    */
       ,(uint8)BSW_CANTP_PHYSICAL                           /* TaType                               */
       ,(uint8)0U                                           /* NTa                                  */
       ,(uint8)0U                                           /* NSa                                  */

       ,BSW_CANTP_u2MS2MAINFUNC_CYCLE(1000U)                /* N_As(MainFunction cycle count)       */
       ,BSW_CANTP_u2MS2MAINFUNC_CYCLE(1000U)                /* N_Bs(MainFunction cycle count)       */

       ,(uint8)8U                                           /* Transmit NPdu Length                 */
       ,(uint8)BSW_CANTP_FALSE                              /* Transmit Cancel                      */
       ,(uint8)BSW_CANTP_TX_INCOMPLETE                      /* New Msg Rx Handling In Last Msg Tx   */
       ,(uint8)BSW_CANTP_ON                                 /* SF/FF/CF TX PaddingActivation        */
       ,(uint8)BSW_CANTP_ON                                 /* FC Rx PaddingActivation              */
       ,(uint8)0U                                           /* NAe                                  */
       ,(uint8)0U                                           /* Priority                             */
       ,(uint8)0U                                           /* Extend                               */
    }
   ,{                                                       /* [2] NSduName:Nsdu_TX_TxNSdu_Diag_Physical_FD_Service*/
        (uint16)2U                                          /* TxNSdu Config Table Index            */
       ,(uint8)4U                                           /* Parent Connection Channel Id         */
       ,(uint8)0U                                           /* Extend                               */

       ,(uint16)(BSW_PDUR_LOCOMP_CANTP | 0x0002U)           /* NSduId                               */
       ,(uint16)(BSW_PDUR_LOCOMP_CANTP | 0x0002U)           /* NPduId                               */
       ,(uint16)(BSW_PDUR_LOCOMP_CANTP | 0x0008U)           /* FC NPduId                            */
       ,(uint16)(BSW_PDUR_LOCOMP_CANTP | 0x0002U)           /* PduR TxConfirmation Id               */
       ,(uint16)(BSW_PDUR_LOCOMP_CANTP | 0x0002U)           /* CanIf PduId                          */

       ,(uint8)BSW_CANTP_NORMALFIXED                        /* Addressing Format                    */
       ,(uint8)BSW_CANTP_PHYSICAL                           /* TaType                               */
       ,(uint8)0U                                           /* NTa                                  */
       ,(uint8)0U                                           /* NSa                                  */

       ,BSW_CANTP_u2MS2MAINFUNC_CYCLE(1000U)                /* N_As(MainFunction cycle count)       */
       ,BSW_CANTP_u2MS2MAINFUNC_CYCLE(1000U)                /* N_Bs(MainFunction cycle count)       */

       ,(uint8)32U                                          /* Transmit NPdu Length                 */
       ,(uint8)BSW_CANTP_FALSE                              /* Transmit Cancel                      */
       ,(uint8)BSW_CANTP_TX_INCOMPLETE                      /* New Msg Rx Handling In Last Msg Tx   */
       ,(uint8)BSW_CANTP_ON                                 /* SF/FF/CF TX PaddingActivation        */
       ,(uint8)BSW_CANTP_ON                                 /* FC Rx PaddingActivation              */
       ,(uint8)0U                                           /* NAe                                  */
       ,(uint8)0U                                           /* Priority                             */
       ,(uint8)0U                                           /* Extend                               */
    }
   ,{                                                       /* [3] NSduName:Nsdu_TX_TxNSdu_Diag_Physical_FD_Remote*/
        (uint16)3U                                          /* TxNSdu Config Table Index            */
       ,(uint8)6U                                           /* Parent Connection Channel Id         */
       ,(uint8)0U                                           /* Extend                               */

       ,(uint16)(BSW_PDUR_LOCOMP_CANTP | 0x0003U)           /* NSduId                               */
       ,(uint16)(BSW_PDUR_LOCOMP_CANTP | 0x0003U)           /* NPduId                               */
       ,(uint16)(BSW_PDUR_LOCOMP_CANTP | 0x000AU)           /* FC NPduId                            */
       ,(uint16)(BSW_PDUR_LOCOMP_CANTP | 0x0003U)           /* PduR TxConfirmation Id               */
       ,(uint16)(BSW_PDUR_LOCOMP_CANTP | 0x0003U)           /* CanIf PduId                          */

       ,(uint8)BSW_CANTP_NORMALFIXED                        /* Addressing Format                    */
       ,(uint8)BSW_CANTP_PHYSICAL                           /* TaType                               */
       ,(uint8)0U                                           /* NTa                                  */
       ,(uint8)0U                                           /* NSa                                  */

       ,BSW_CANTP_u2MS2MAINFUNC_CYCLE(1000U)                /* N_As(MainFunction cycle count)       */
       ,BSW_CANTP_u2MS2MAINFUNC_CYCLE(1000U)                /* N_Bs(MainFunction cycle count)       */

       ,(uint8)32U                                          /* Transmit NPdu Length                 */
       ,(uint8)BSW_CANTP_FALSE                              /* Transmit Cancel                      */
       ,(uint8)BSW_CANTP_TX_INCOMPLETE                      /* New Msg Rx Handling In Last Msg Tx   */
       ,(uint8)BSW_CANTP_ON                                 /* SF/FF/CF TX PaddingActivation        */
       ,(uint8)BSW_CANTP_ON                                 /* FC Rx PaddingActivation              */
       ,(uint8)0U                                           /* NAe                                  */
       ,(uint8)0U                                           /* Priority                             */
       ,(uint8)0U                                           /* Extend                               */
    }
    /*========== User define Area [End] ============*/
};

#if( BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE )
BswConst Bsw_CanTp_TxNSduParamType bsw_cantp_stTxNSduParamTbl[BSW_CANTP_CFG_TXPARAMPTNNUM] =
{
    /*========== User define Area [Start] ==========*/
    /*========== User define Area [End] ============*/
};
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#endif /* BSW_BSWM_CS_FUNC_CANTP == BSW_USE */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/09/25                                             */
/*  v1-1-0          :2018/12/13                                             */
/*  v1-2-0          :2019/12/10                                             */
/*  v2-0-0          :2021/09/07                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v3-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
