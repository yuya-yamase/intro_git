/* bsw_bswm_cs_connector_c_v2-0-0                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/BSWMCS/CONNECTOR/CODE                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>
#include <cs/bsw_cs_system_memmap_pre.h>
#include <ComStack_Types.h>

#include <bswm_cs/bsw_bswm_cs.h>
#include <comm/bsw_comm.h>
#include "../../ComM/inc/bsw_comm_config.h"
#include "../inc/bsw_bswm_cs_config.h"
#include <nm/bsw_nmstack_types.h>
#include <cs/bsw_cs_system_memmap_post.h>

#include "../cfg/BswM_CS_Connector_Cfg.h"

#include <cs/bsw_cs_system_memmap_pre.h>
#include "../inc/bsw_bswm_cs_connector.h"
#include "../cfg/BswM_CS_Cfg.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* User defined function */
/* BswM API Name */
#define bsw_bswm_cs_UBswMComMCrntMode       (BSW_BSWM_CS_CFG_FN_BSWM_COMM)
#define bsw_bswm_cs_UBswMComMCrntPnMode     (BSW_BSWM_CS_CFG_FN_BSWM_COMMPNC)
#define bsw_bswm_cs_UBswMComMCrntChPnMd     (BSW_BSWM_CS_CFG_FN_BSWM_COMMCHP)

/* EcuM API Name */
#define bsw_bswm_cs_UEcuM_SetWakeupEv       (BSW_BSWM_CS_CFG_FN_ECUM_SWUE)

/* Dem API Name */
#define bsw_bswm_cs_UDemErrorReport         (BSW_BSWM_CS_CFG_FN_DEM_REP)

/* BSWM/CDD API Name */
#define bsw_bswm_cs_UBswMCdd1_Init          (BSW_BSWM_CS_CFG_FN_CDD1INIT)
#define bsw_bswm_cs_UBswMCdd1_DeInit        (BSW_BSWM_CS_CFG_FN_CDD1DEINIT)
#define bsw_bswm_cs_UBswMCdd1_PDeInit       (BSW_BSWM_CS_CFG_FN_CDD1PRDEINIT)
#define bsw_bswm_cs_UBswMCdd1_Wakeup        (BSW_BSWM_CS_CFG_FN_CDD1WKUP)
#define bsw_bswm_cs_UBswMCdd1_Sleep         (BSW_BSWM_CS_CFG_FN_CDD1SLP)
#define bsw_bswm_cs_UBswMCdd1_Reset         (BSW_BSWM_CS_CFG_FN_CDD1RESET)
#define bsw_bswm_cs_UBswMCdd1_HighIn        (BSW_BSWM_CS_CFG_FN_CDD1HIGHIN)
#define bsw_bswm_cs_UBswMCdd1_HighOut       (BSW_BSWM_CS_CFG_FN_CDD1HIGHOUT)
#define bsw_bswm_cs_UBswMCdd1_MidIn         (BSW_BSWM_CS_CFG_FN_CDD1MIDIN)
#define bsw_bswm_cs_UBswMCdd1_MidCtrl       (BSW_BSWM_CS_CFG_FN_CDD1MIDCTRL)
#define bsw_bswm_cs_UBswMCdd1_MidOut        (BSW_BSWM_CS_CFG_FN_CDD1MIDOUT)
#define bsw_bswm_cs_UBswMCdd1_InitDrvr      (BSW_BSWM_CS_CFG_FN_CDD1INTDRV)
#define bsw_bswm_cs_UBswMCdd1_UpdPDUSt      (BSW_BSWM_CS_CFG_FN_CDD1UDIPDUST)
#define bsw_bswm_cs_UBswMCdd1_ChkAwake      (BSW_BSWM_CS_CFG_FN_CDD1CHKAWK)

#define bsw_bswm_cs_UBswMCdd2_Init          (BSW_BSWM_CS_CFG_FN_CDD2INIT)
#define bsw_bswm_cs_UBswMCdd2_DeInit        (BSW_BSWM_CS_CFG_FN_CDD2DEINIT)
#define bsw_bswm_cs_UBswMCdd2_PDeInit       (BSW_BSWM_CS_CFG_FN_CDD2PRDEINIT)
#define bsw_bswm_cs_UBswMCdd2_Wakeup        (BSW_BSWM_CS_CFG_FN_CDD2WKUP)
#define bsw_bswm_cs_UBswMCdd2_Sleep         (BSW_BSWM_CS_CFG_FN_CDD2SLP)
#define bsw_bswm_cs_UBswMCdd2_Reset         (BSW_BSWM_CS_CFG_FN_CDD2RESET)
#define bsw_bswm_cs_UBswMCdd2_HighIn        (BSW_BSWM_CS_CFG_FN_CDD2HIGHIN)
#define bsw_bswm_cs_UBswMCdd2_HighOut       (BSW_BSWM_CS_CFG_FN_CDD2HIGHOUT)
#define bsw_bswm_cs_UBswMCdd2_MidIn         (BSW_BSWM_CS_CFG_FN_CDD2MIDIN)
#define bsw_bswm_cs_UBswMCdd2_MidCtrl       (BSW_BSWM_CS_CFG_FN_CDD2MIDCTRL)
#define bsw_bswm_cs_UBswMCdd2_MidOut        (BSW_BSWM_CS_CFG_FN_CDD2MIDOUT)
#define bsw_bswm_cs_UBswMCdd2_InitDrvr      (BSW_BSWM_CS_CFG_FN_CDD2INTDRV)
#define bsw_bswm_cs_UBswMCdd2_UpdPDUSt      (BSW_BSWM_CS_CFG_FN_CDD2UDIPDUST)
#define bsw_bswm_cs_UBswMCdd2_ChkAwake      (BSW_BSWM_CS_CFG_FN_CDD2CHKAWK)

/* CDDSM API Name */
#define bsw_bswm_cs_UCdd1SM_ReqComMode     (BSW_BSWM_CS_CFG_FN_CDD1SM_RQCM)
#define bsw_bswm_cs_UCdd1SM_GetComMode     (BSW_BSWM_CS_CFG_FN_CDD1SM_GTCM)
#define bsw_bswm_cs_UCdd2SM_ReqComMode     (BSW_BSWM_CS_CFG_FN_CDD2SM_RQCM)
#define bsw_bswm_cs_UCdd2SM_GetComMode     (BSW_BSWM_CS_CFG_FN_CDD2SM_GTCM)

/* CDD Upper(PduR) API Name */
#define bsw_bswm_cs_UCdd1Up_TriggerTx      (BSW_BSWM_CS_CFG_FN_CDD1UP_TRGT)
#define bsw_bswm_cs_UCdd1Up_TxConf         (BSW_BSWM_CS_CFG_FN_CDD1UP_TC)
#define bsw_bswm_cs_UCdd1Up_RxInd          (BSW_BSWM_CS_CFG_FN_CDD1UP_RI)
#define bsw_bswm_cs_UCdd1Up_StartOfRx      (BSW_BSWM_CS_CFG_FN_CDD1UP_SOR)
#define bsw_bswm_cs_UCdd1Up_CopyRxData     (BSW_BSWM_CS_CFG_FN_CDD1UP_CPRX)
#define bsw_bswm_cs_UCdd1Up_CopyTxData     (BSW_BSWM_CS_CFG_FN_CDD1UP_CPTX)
#define bsw_bswm_cs_UCdd1Up_TpRxInd        (BSW_BSWM_CS_CFG_FN_CDD1UP_TPRI)
#define bsw_bswm_cs_UCdd1Up_TpTxConf       (BSW_BSWM_CS_CFG_FN_CDD1UP_TPTC)

#define bsw_bswm_cs_UCdd2Up_TriggerTx      (BSW_BSWM_CS_CFG_FN_CDD2UP_TRGT)
#define bsw_bswm_cs_UCdd2Up_TxConf         (BSW_BSWM_CS_CFG_FN_CDD2UP_TC)
#define bsw_bswm_cs_UCdd2Up_RxInd          (BSW_BSWM_CS_CFG_FN_CDD2UP_RI)
#define bsw_bswm_cs_UCdd2Up_StartOfRx      (BSW_BSWM_CS_CFG_FN_CDD2UP_SOR)
#define bsw_bswm_cs_UCdd2Up_CopyRxData     (BSW_BSWM_CS_CFG_FN_CDD2UP_CPRX)
#define bsw_bswm_cs_UCdd2Up_CopyTxData     (BSW_BSWM_CS_CFG_FN_CDD2UP_CPTX)
#define bsw_bswm_cs_UCdd2Up_TpRxInd        (BSW_BSWM_CS_CFG_FN_CDD2UP_TPRI)
#define bsw_bswm_cs_UCdd2Up_TpTxConf       (BSW_BSWM_CS_CFG_FN_CDD2UP_TPTC)

/* CDD Lower(PduR) API Name */
/* CDDIf */
#define bsw_bswm_cs_UCdd1If_Transmit       (BSW_BSWM_CS_CFG_FN_CDD1IF_TX)
#define bsw_bswm_cs_UCdd1If_CancelTx       (BSW_BSWM_CS_CFG_FN_CDD1IF_CTX)
#define bsw_bswm_cs_UCdd1If_GetIdTx        (BSW_BSWM_CS_CFG_FN_CDD1IF_GITX)
#define bsw_bswm_cs_UCdd1If_GetIdRx        (BSW_BSWM_CS_CFG_FN_CDD1IF_GIRX)
#define bsw_bswm_cs_UCdd2If_Transmit       (BSW_BSWM_CS_CFG_FN_CDD2IF_TX)
#define bsw_bswm_cs_UCdd2If_CancelTx       (BSW_BSWM_CS_CFG_FN_CDD2IF_CTX)
#define bsw_bswm_cs_UCdd2If_GetIdTx        (BSW_BSWM_CS_CFG_FN_CDD2IF_GITX)
#define bsw_bswm_cs_UCdd2If_GetIdRx        (BSW_BSWM_CS_CFG_FN_CDD2IF_GIRX)
/* CDDTp */
#define bsw_bswm_cs_UCdd1Tp_Transmit       (BSW_BSWM_CS_CFG_FN_CDD1TP_TX)
#define bsw_bswm_cs_UCdd1Tp_CancelTx       (BSW_BSWM_CS_CFG_FN_CDD1TP_CTX)
#define bsw_bswm_cs_UCdd1Tp_CancelRx       (BSW_BSWM_CS_CFG_FN_CDD1TP_CRX)
#define bsw_bswm_cs_UCdd1Tp_GetIdTx        (BSW_BSWM_CS_CFG_FN_CDD1TP_GITX)
#define bsw_bswm_cs_UCdd1Tp_GetIdRx        (BSW_BSWM_CS_CFG_FN_CDD1TP_GIRX)
#define bsw_bswm_cs_UCdd2Tp_Transmit       (BSW_BSWM_CS_CFG_FN_CDD2TP_TX)
#define bsw_bswm_cs_UCdd2Tp_CancelTx       (BSW_BSWM_CS_CFG_FN_CDD2TP_CTX)
#define bsw_bswm_cs_UCdd2Tp_CancelRx       (BSW_BSWM_CS_CFG_FN_CDD2TP_CRX)
#define bsw_bswm_cs_UCdd2Tp_GetIdTx        (BSW_BSWM_CS_CFG_FN_CDD2TP_GITX)
#define bsw_bswm_cs_UCdd2Tp_GetIdRx        (BSW_BSWM_CS_CFG_FN_CDD2TP_GIRX)

/* GenericNm API Name */
#define bsw_bswm_cs_UCdd1Nm_PassiveStUp    (BSW_BSWM_CS_CFG_FN_CDD1NM_PSTU)
#define bsw_bswm_cs_UCdd1Nm_NetworkReq     (BSW_BSWM_CS_CFG_FN_CDD1NM_NREQ)
#define bsw_bswm_cs_UCdd1Nm_NetworkRel     (BSW_BSWM_CS_CFG_FN_CDD1NM_NRLS)
#define bsw_bswm_cs_UCdd1Nm_DisableComm    (BSW_BSWM_CS_CFG_FN_CDD1NM_DCOM)
#define bsw_bswm_cs_UCdd1Nm_EnableComm     (BSW_BSWM_CS_CFG_FN_CDD1NM_ECOM)
#define bsw_bswm_cs_UCdd1Nm_GetState       (BSW_BSWM_CS_CFG_FN_CDD1NM_GST)

#define bsw_bswm_cs_UCdd2Nm_PassiveStUp    (BSW_BSWM_CS_CFG_FN_CDD2NM_PSTU)
#define bsw_bswm_cs_UCdd2Nm_NetworkReq     (BSW_BSWM_CS_CFG_FN_CDD2NM_NREQ)
#define bsw_bswm_cs_UCdd2Nm_NetworkRel     (BSW_BSWM_CS_CFG_FN_CDD2NM_NRLS)
#define bsw_bswm_cs_UCdd2Nm_DisableComm    (BSW_BSWM_CS_CFG_FN_CDD2NM_DCOM)
#define bsw_bswm_cs_UCdd2Nm_EnableComm     (BSW_BSWM_CS_CFG_FN_CDD2NM_ECOM)
#define bsw_bswm_cs_UCdd2Nm_GetState       (BSW_BSWM_CS_CFG_FN_CDD2NM_GST)

/* Dcm API Name */
#define bsw_bswm_cs_UDcm_NoCom              (BSW_BSWM_CS_CFG_FN_DCM_NOCOM)
#define bsw_bswm_cs_UDcm_SilentCom          (BSW_BSWM_CS_CFG_FN_DCM_SILCOM)
#define bsw_bswm_cs_UDcm_FullCom            (BSW_BSWM_CS_CFG_FN_DCM_FULCOM)

/* Dcm API Name */
#define bsw_bswm_cs_UDcm_StartOfRx          (BSW_BSWM_CS_CFG_FN_DCM_SOR)
#define bsw_bswm_cs_UDcm_CopyRxData         (BSW_BSWM_CS_CFG_FN_DCM_CPRXD)
#define bsw_bswm_cs_UDcm_CopyTxData         (BSW_BSWM_CS_CFG_FN_DCM_CPTXD)
#define bsw_bswm_cs_UDcm_TpRxInd            (BSW_BSWM_CS_CFG_FN_DCM_TPRXIN)
#define bsw_bswm_cs_UDcm_TpTxConf           (BSW_BSWM_CS_CFG_FN_DCM_TPTXCN)
#define bsw_bswm_cs_UDcm_TxConf             (BSW_BSWM_CS_CFG_FN_DCM_TXCN)

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
#if ( BSW_BSWM_CS_FUNC_COMM == BSW_USE )
/* BswM API Function Table */
BswConst Bsw_BswmCS_BswMFuncTblType  bsw_bswm_cs_cnct_BswM_Func = {
    &bsw_bswm_cs_UBswMComMCrntMode
   ,&bsw_bswm_cs_UBswMComMCrntPnMode
   ,&bsw_bswm_cs_UBswMComMCrntChPnMd
};

/* Dcm API Function Table */
BswConst Bsw_BswmCS_DcmComMFuncTblType   bsw_bswm_cs_cnct_Dcm_ComM_Func = {
    &bsw_bswm_cs_UDcm_NoCom
   ,&bsw_bswm_cs_UDcm_SilentCom
   ,&bsw_bswm_cs_UDcm_FullCom
};
#endif /* ( BSW_BSWM_CS_FUNC_COMM == BSW_USE ) */

#if ( BSW_BSWM_CS_FUNC_BSWMCS == BSW_USE )
/* EcuM API Function Table */
BswConst   Bsw_BswmCS_EcuMFuncTblType  bsw_bswm_cs_cnct_EcuM_Func = {
    &bsw_bswm_cs_UEcuM_SetWakeupEv
};

/* Dem API Function Table */
BswConst Bsw_BswmCS_DemFuncTblType   bsw_bswm_cs_cnct_Dem_Func = {
    &bsw_bswm_cs_UDemErrorReport
};
#endif /* ( BSW_BSWM_CS_FUNC_BSWMCS == BSW_USE ) */

/* CDD Upper(PduR) API Function Table */
#if (BSW_BSWM_CS_FUNC_UPPERCDD1 == BSW_USE)
BswConst   Bsw_BswmCS_CddUpFuncTblType bsw_bswm_cs_cnct_Cdd1UpFuncTbl =
{
     &bsw_bswm_cs_UCdd1Up_TriggerTx
    ,&bsw_bswm_cs_UCdd1Up_TxConf
    ,&bsw_bswm_cs_UCdd1Up_RxInd
    ,&bsw_bswm_cs_UCdd1Up_StartOfRx
    ,&bsw_bswm_cs_UCdd1Up_CopyRxData
    ,&bsw_bswm_cs_UCdd1Up_CopyTxData
    ,&bsw_bswm_cs_UCdd1Up_TpRxInd
    ,&bsw_bswm_cs_UCdd1Up_TpTxConf
};
#endif /* (BSW_BSWM_CS_FUNC_UPPERCDD1 == BSW_USE) */

#if (BSW_BSWM_CS_FUNC_UPPERCDD2 == BSW_USE)
BswConst   Bsw_BswmCS_CddUpFuncTblType bsw_bswm_cs_cnct_Cdd2UpFuncTbl =
{
     &bsw_bswm_cs_UCdd2Up_TriggerTx
    ,&bsw_bswm_cs_UCdd2Up_TxConf
    ,&bsw_bswm_cs_UCdd2Up_RxInd
    ,&bsw_bswm_cs_UCdd2Up_StartOfRx
    ,&bsw_bswm_cs_UCdd2Up_CopyRxData
    ,&bsw_bswm_cs_UCdd2Up_CopyTxData
    ,&bsw_bswm_cs_UCdd2Up_TpRxInd
    ,&bsw_bswm_cs_UCdd2Up_TpTxConf
};
#endif /* (BSW_BSWM_CS_FUNC_UPPERCDD2 == BSW_USE) */

#if ( BSW_BSWM_CS_FUNC_CDD1 == BSW_USE )
/* BSWM/CDD API Function Table */
BswConst   Bsw_BswmCS_BswMCddFuncTblType  bsw_bswm_cs_cnct_BswMCdd1_Func = {
     &bsw_bswm_cs_UBswMCdd1_Init
    ,&bsw_bswm_cs_UBswMCdd1_DeInit
    ,&bsw_bswm_cs_UBswMCdd1_PDeInit
    ,&bsw_bswm_cs_UBswMCdd1_Wakeup
    ,&bsw_bswm_cs_UBswMCdd1_Sleep
    ,&bsw_bswm_cs_UBswMCdd1_Reset
    ,&bsw_bswm_cs_UBswMCdd1_HighIn
    ,&bsw_bswm_cs_UBswMCdd1_HighOut
    ,&bsw_bswm_cs_UBswMCdd1_MidIn
    ,&bsw_bswm_cs_UBswMCdd1_MidCtrl
    ,&bsw_bswm_cs_UBswMCdd1_MidOut
    ,&bsw_bswm_cs_UBswMCdd1_InitDrvr
    ,&bsw_bswm_cs_UBswMCdd1_UpdPDUSt
    ,&bsw_bswm_cs_UBswMCdd1_ChkAwake
};

/* CDDSM API Function Table */
BswConst Bsw_BswmCS_CddSMFuncTblType bsw_bswm_cs_cnct_Cdd1SM_Func = {
     &bsw_bswm_cs_UCdd1SM_ReqComMode
    ,&bsw_bswm_cs_UCdd1SM_GetComMode
};

/* CDDIF API Function Table */
BswConst   Bsw_BswmCS_CddIfFuncTblType bsw_bswm_cs_cnct_Cdd1If_Func =
{
     &bsw_bswm_cs_UCdd1If_Transmit
    ,&bsw_bswm_cs_UCdd1If_CancelTx
    ,&bsw_bswm_cs_UCdd1If_GetIdTx
    ,&bsw_bswm_cs_UCdd1If_GetIdRx
};

/* GenericNm API Function Table */
BswConst Bsw_BswmCS_CddNmFuncTblType bsw_bswm_cs_cnct_Cdd1NmFuncTbl = 
{
     &bsw_bswm_cs_UCdd1Nm_PassiveStUp
    ,&bsw_bswm_cs_UCdd1Nm_NetworkReq
    ,&bsw_bswm_cs_UCdd1Nm_NetworkRel
    ,&bsw_bswm_cs_UCdd1Nm_DisableComm
    ,&bsw_bswm_cs_UCdd1Nm_EnableComm
    ,&bsw_bswm_cs_UCdd1Nm_GetState
};
#endif /* (BSW_BSWM_CS_FUNC_CDD1 == BSW_USE) */

#if ( BSW_BSWM_CS_FUNC_CDD2 == BSW_USE )
/* BSWM/CDD API Function Table */
BswConst   Bsw_BswmCS_BswMCddFuncTblType  bsw_bswm_cs_cnct_BswMCdd2_Func = {
     &bsw_bswm_cs_UBswMCdd2_Init
    ,&bsw_bswm_cs_UBswMCdd2_DeInit
    ,&bsw_bswm_cs_UBswMCdd2_PDeInit
    ,&bsw_bswm_cs_UBswMCdd2_Wakeup
    ,&bsw_bswm_cs_UBswMCdd2_Sleep
    ,&bsw_bswm_cs_UBswMCdd2_Reset
    ,&bsw_bswm_cs_UBswMCdd2_HighIn
    ,&bsw_bswm_cs_UBswMCdd2_HighOut
    ,&bsw_bswm_cs_UBswMCdd2_MidIn
    ,&bsw_bswm_cs_UBswMCdd2_MidCtrl
    ,&bsw_bswm_cs_UBswMCdd2_MidOut
    ,&bsw_bswm_cs_UBswMCdd2_InitDrvr
    ,&bsw_bswm_cs_UBswMCdd2_UpdPDUSt
    ,&bsw_bswm_cs_UBswMCdd2_ChkAwake
};

/* CDDSM API Function Table */
BswConst Bsw_BswmCS_CddSMFuncTblType bsw_bswm_cs_cnct_Cdd2SM_Func = {
     &bsw_bswm_cs_UCdd2SM_ReqComMode
    ,&bsw_bswm_cs_UCdd2SM_GetComMode
};

/* CDDIF API Function Table */
BswConst   Bsw_BswmCS_CddIfFuncTblType bsw_bswm_cs_cnct_Cdd2If_Func =
{
     &bsw_bswm_cs_UCdd2If_Transmit
    ,&bsw_bswm_cs_UCdd2If_CancelTx
    ,&bsw_bswm_cs_UCdd2If_GetIdTx
    ,&bsw_bswm_cs_UCdd2If_GetIdRx
};

/* GenericNm API Function Table */
BswConst Bsw_BswmCS_CddNmFuncTblType bsw_bswm_cs_cnct_Cdd2NmFuncTbl = 
{
     &bsw_bswm_cs_UCdd2Nm_PassiveStUp
    ,&bsw_bswm_cs_UCdd2Nm_NetworkReq
    ,&bsw_bswm_cs_UCdd2Nm_NetworkRel
    ,&bsw_bswm_cs_UCdd2Nm_DisableComm
    ,&bsw_bswm_cs_UCdd2Nm_EnableComm
    ,&bsw_bswm_cs_UCdd2Nm_GetState
};
#endif /* (BSW_BSWM_CS_FUNC_CDD2 == BSW_USE) */

/* CDDTp API Function Table */
#if (BSW_BSWM_CS_FUNC_CDD1TP == BSW_USE)
BswConst   Bsw_BswmCS_CddTpFuncTblType bsw_bswm_cs_cnct_Cdd1Tp_Func =
{
     &bsw_bswm_cs_UCdd1Tp_Transmit
    ,&bsw_bswm_cs_UCdd1Tp_CancelTx
    ,&bsw_bswm_cs_UCdd1Tp_CancelRx
    ,&bsw_bswm_cs_UCdd1Tp_GetIdTx
    ,&bsw_bswm_cs_UCdd1Tp_GetIdRx
};
#endif /* (BSW_BSWM_CS_FUNC_CDD1TP == BSW_USE) */

#if (BSW_BSWM_CS_FUNC_CDD2TP == BSW_USE)
BswConst   Bsw_BswmCS_CddTpFuncTblType bsw_bswm_cs_cnct_Cdd2Tp_Func =
{
     &bsw_bswm_cs_UCdd2Tp_Transmit
    ,&bsw_bswm_cs_UCdd2Tp_CancelTx
    ,&bsw_bswm_cs_UCdd2Tp_CancelRx
    ,&bsw_bswm_cs_UCdd2Tp_GetIdTx
    ,&bsw_bswm_cs_UCdd2Tp_GetIdRx
};
#endif /* (BSW_BSWM_CS_FUNC_CDD2TP == BSW_USE) */

#if ( (BSW_BSWM_CS_FUNC_PDUR == BSW_USE) && (BSW_BSWM_CS_FUNC_DCM == BSW_USE) )
BswConst Bsw_BswmCS_DcmPduRFuncTblType   bsw_bswm_cs_cnct_Dcm_PduR_Func = {
    &bsw_bswm_cs_UDcm_StartOfRx
   ,&bsw_bswm_cs_UDcm_CopyRxData
   ,&bsw_bswm_cs_UDcm_CopyTxData
   ,&bsw_bswm_cs_UDcm_TpRxInd
   ,&bsw_bswm_cs_UDcm_TpTxConf
   ,&bsw_bswm_cs_UDcm_TxConf
};
#endif /* ( (BSW_BSWM_CS_FUNC_PDUR == BSW_USE) && (BSW_BSWM_CS_FUNC_DCM == BSW_USE) ) */


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#include <cs/bsw_cs_system_memmap_post.h>

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/10/16                                             */
/*  v1-0-1          :2018/01/30                                             */
/*  v1-1-0          :2019/01/16                                             */
/*  v2-0-0          :2021/12/02                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
