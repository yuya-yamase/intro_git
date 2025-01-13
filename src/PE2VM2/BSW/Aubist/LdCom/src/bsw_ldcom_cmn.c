/* bsw_ldcom_cmn_c_v3-0-0                                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/LDCOM/CMN/CODE                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>
#include "../inc/bsw_ldcom_MemMap.h"
#include <bswm_cs/bsw_bswm_cs.h>
#include <comm/bsw_comm.h>
#include "../../ComM/inc/bsw_comm_config.h"
#include "../../BswM_CS/inc/bsw_bswm_cs_config.h"

#if( BSW_BSWM_CS_FUNC_LDCOM == BSW_USE )
#include <ComStack_Types.h>
#include <ldcom/bsw_ldcom.h>

#include "../LdCom/cfg/LdCom_Cfg.h"
#include "../inc/bsw_ldcom_cmn.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define BSW_LDCOM_CMN_DUMMY_NUM     (1U)

#if (BSW_LDCOM_CFG_IF_RX_REG_NUM > 0U)
#define BSW_LDCOM_CMN_IF_RX_TABLE   (&bsw_ldcom_stHandleIdInfoIfRxTbl[0])
#else
#define BSW_LDCOM_CMN_IF_RX_TABLE   (&bsw_ldcom_stDummyIfRxTbl[0])
#endif

#if (BSW_LDCOM_CFG_IF_TX_REG_NUM > 0U)
#define BSW_LDCOM_CMN_IF_TX_TABLE   (&bsw_ldcom_stHandleIdInfoIfTxTbl[0])
#else
#define BSW_LDCOM_CMN_IF_TX_TABLE   (&bsw_ldcom_stDummyIfTxTbl[0])
#endif

#if (BSW_LDCOM_CFG_TP_RX_REG_NUM > 0U)
#define BSW_LDCOM_CMN_TP_RX_TABLE   (&bsw_ldcom_stHandleIdInfoTpRxTbl[0])
#else
#define BSW_LDCOM_CMN_TP_RX_TABLE   (&bsw_ldcom_stDummyTpRxTbl[0])
#endif

#if (BSW_LDCOM_CFG_TP_TX_REG_NUM > 0U)
#define BSW_LDCOM_CMN_TP_TX_TABLE   (&bsw_ldcom_stHandleIdInfoTpTxTbl[0])
#else
#define BSW_LDCOM_CMN_TP_TX_TABLE   (&bsw_ldcom_stDummyTpTxTbl[0])
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
/* HandleID information [common unit] */
BswConst PduIdType bsw_ldcom_u2HandleIdNum = (PduIdType)(BSW_LDCOM_HANDLE_ID_REG_NUM);

/* Dummy information individual table */
/* bsw_ldcom_stDummyIfRxTbl */
#if ( BSW_LDCOM_CFG_IF_RX_REG_NUM == 0U )
static BswConst Bsw_LdCom_HandleIdInfoIfRxType bsw_ldcom_stDummyIfRxTbl[BSW_LDCOM_CMN_DUMMY_NUM] =
{
    {
        &bsw_ldcom_rx_dmy_CbkRxInd               /* Cbk Dummy RxIndication */
    }
};
#endif /* BSW_LDCOM_CFG_IF_RX_REG_NUM == 0 */

/* bsw_ldcom_stDummyIfTxTbl */
#if ( BSW_LDCOM_CFG_IF_TX_REG_NUM == 0U )
static BswConst Bsw_LdCom_HandleIdInfoIfTxType bsw_ldcom_stDummyIfTxTbl[BSW_LDCOM_CMN_DUMMY_NUM] =
{
    {
        &bsw_ldcom_CbkTriggerTransmit_dummy,           /* Cbk Dummy TriggerTransmit */
        &bsw_ldcom_CbkTxConfirmation_dummy             /* Cbk Dummy TxConfirmation */
    }
};
#endif /* BSW_LDCOM_CFG_IF_TX_REG_NUM == 0 */

/* bsw_ldcom_stDummyTpRxTbl */
#if ( BSW_LDCOM_CFG_TP_RX_REG_NUM == 0U )
static BswConst Bsw_LdCom_HandleIdInfoTpRxType bsw_ldcom_stDummyTpRxTbl[BSW_LDCOM_CMN_DUMMY_NUM] =
{
    {
        &bsw_ldcom_rx_dmy_CbkStartOfRx,          /* Cbk Dummy StartOfReception */
        &bsw_ldcom_rx_dmy_CbkCopyRxData,         /* Cbk Dummy CopyRxData */
        &bsw_ldcom_rx_dmy_CbkTpRxInd             /* Cbk Dummy TpRxIndication */
    }
};
#endif /* BSW_LDCOM_CFG_TP_RX_REG_NUM == 0 */

/* bsw_ldcom_stDummyTpTxTbl */
#if ( BSW_LDCOM_CFG_TP_TX_REG_NUM == 0U )
static BswConst Bsw_LdCom_HandleIdInfoTpTxType bsw_ldcom_stDummyTpTxTbl[BSW_LDCOM_CMN_DUMMY_NUM] =
{
    {
        &bsw_ldcom_tx_dmy_CbkCopyTxData,         /* Cbk Dummy CopyTxData */
        &bsw_ldcom_tx_dmy_CbkTpTxConf            /* Cbk Dummy TpTxConfirmation */
    }
};
#endif  /* BSW_LDCOM_CFG_TP_TX_REG_NUM == 0 */

/* Constant of routing destination information from the information individual table getting */
BswConst Bsw_LdCom_HandleIdInfoIfRxType* BswConst bsw_ldcom_ptIfRxRoutingInfo = BSW_LDCOM_CMN_IF_RX_TABLE;
BswConst Bsw_LdCom_HandleIdInfoIfTxType* BswConst bsw_ldcom_ptIfTxRoutingInfo = BSW_LDCOM_CMN_IF_TX_TABLE;
BswConst Bsw_LdCom_HandleIdInfoTpRxType* BswConst bsw_ldcom_ptTpRxRoutingInfo = BSW_LDCOM_CMN_TP_RX_TABLE;
BswConst Bsw_LdCom_HandleIdInfoTpTxType* BswConst bsw_ldcom_ptTpTxRoutingInfo = BSW_LDCOM_CMN_TP_TX_TABLE;

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/

#endif  /* BSW_BSWM_CS_FUNC_LDCOM == BSW_USE */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-1-0          :2018/12/13                                             */
/*  v2-0-0          :2021/12/02                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
