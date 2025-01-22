/* ldcom_pbcfg_c_v3-0-0                                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | LDCOM/PBCFG/CODE                                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>
#include "LdCom_Connector_Cfg.h"
#include "../inc/bsw_ldcom_MemMap.h"
#include <bswm_cs/bsw_bswm_cs.h>
#include <comm/bsw_comm.h>
#include "../../ComM/inc/bsw_comm_config.h"
#include "../../BswM_CS/inc/bsw_bswm_cs_config.h"

#if( BSW_BSWM_CS_FUNC_LDCOM == BSW_USE )
#include <ComStack_Types.h>
#include <ldcom/bsw_ldcom.h>

#include "LdCom_Cfg.h"
#include "../inc/bsw_ldcom_cmn.h"

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

#if ( BSW_LDCOM_HANDLE_ID_REG_NUM > 0U )

/****************************************************************************/
/* Table Name    | bsw_ldcom_stHandleIdInfoComTbl                           */
/* Description   | HandleID information [common unit] Table                 */
/* Member        | u2HandleType   : HandleID Type                           */
/*               |                  [IF or TP + RECEIVE or SEND]            */
/*               | u2IndvIndex    : Index by HandleID Type individual unit  */
/*               | u2PduRHandleID : PduR HandleID[I-PduID]                  */
/* Notes         | None                                                     */
/****************************************************************************/
BswConst Bsw_LdCom_HandleIdInfoComType bsw_ldcom_stHandleIdInfoComTbl[BSW_LDCOM_HANDLE_ID_REG_NUM] =
{
};  /* bsw_ldcom_stHandleIdInfoComTbl */

#endif  /* BSW_LDCOM_HANDLE_ID_REG_NUM > 0 */


#if ( BSW_LDCOM_CFG_IF_RX_REG_NUM > 0U )

/****************************************************************************/
/* Table Name    | bsw_ldcom_stHandleIdInfoIfRxTbl                          */
/* Description   | HandleID information [individual unit[IF_RX]] Table      */
/* Member        | ptRxIndFunc     : RxIndication Func Address of UpLayer   */
/* Notes         | None                                                     */
/****************************************************************************/
BswConst Bsw_LdCom_HandleIdInfoIfRxType bsw_ldcom_stHandleIdInfoIfRxTbl[BSW_LDCOM_CFG_IF_RX_REG_NUM] =
{
};  /* bsw_ldcom_stHandleIdInfoIfRxTbl */

#endif  /* BSW_LDCOM_CFG_IF_RX_REG_NUM > 0 */


#if ( BSW_LDCOM_CFG_IF_TX_REG_NUM > 0U )

/****************************************************************************/
/* Table Name    | bsw_ldcom_stHandleIdInfoIfTxTbl                          */
/* Description   | HandleID information [individual unit[IF_TX]] Table      */
/* Member        | ptTrgTrnsFunc   : TriggerTransmit Func Address of UpLayer*/
/*               | ptTxConfFunc    : TxConfirmation Func Address of UpLayer */
/* Notes         | None                                                     */
/****************************************************************************/
BswConst Bsw_LdCom_HandleIdInfoIfTxType bsw_ldcom_stHandleIdInfoIfTxTbl[BSW_LDCOM_CFG_IF_TX_REG_NUM] =
{
};  /* bsw_ldcom_stHandleIdInfoIfTxTbl */

#endif  /* BSW_LDCOM_CFG_IF_TX_REG_NUM > 0 */


#if ( BSW_LDCOM_CFG_TP_RX_REG_NUM > 0U )

/****************************************************************************/
/* Table Name    | bsw_ldcom_stHandleIdInfoTpRxTbl                          */
/* Description   | HandleID information [individual unit[TP_RX]] Table      */
/* Member        | ptStrRecpFunc  : StartOfReception Func Address of UpLayer*/
/*               | ptRxDataFunc   : CopyRxData Func Address of UpLayer      */
/*               | ptTpRxIndFunc  : TpRxIndication Func Address of UpLayer  */
/* Notes         | None                                                     */
/****************************************************************************/
BswConst Bsw_LdCom_HandleIdInfoTpRxType bsw_ldcom_stHandleIdInfoTpRxTbl[BSW_LDCOM_CFG_TP_RX_REG_NUM] =
{
};  /* bsw_ldcom_stHandleIdInfoTpRxTbl */

#endif  /* BSW_LDCOM_CFG_TP_RX_REG_NUM > 0 */


#if ( BSW_LDCOM_CFG_TP_TX_REG_NUM > 0U )

/****************************************************************************/
/* Table Name    | bsw_ldcom_stHandleIdInfoTpTxTbl                          */
/* Description   | HandleID information [individual unit[TP_TX]] Table      */
/* Member        | ptTxDataFunc   : CopyTxData Func Address of UpLayer      */
/*               | ptTpTxConfFunc : TpTxConfirmation Func Address of UpLayer*/
/* Notes         | None                                                     */
/****************************************************************************/
BswConst Bsw_LdCom_HandleIdInfoTpTxType bsw_ldcom_stHandleIdInfoTpTxTbl[BSW_LDCOM_CFG_TP_TX_REG_NUM] =
{
};  /* bsw_ldcom_stHandleIdInfoTpTxTbl */

#endif  /* BSW_LDCOM_CFG_TP_TX_REG_NUM > 0 */

#endif  /* BSW_BSWM_CS_FUNC_LDCOM == BSW_USE */

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/10/17                                             */
/*  v1-1-0          :2018/12/13                                             */
/*  v2-0-0          :2021/02/12                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-2                                              */
/*  BSW plug-in        :v3-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
