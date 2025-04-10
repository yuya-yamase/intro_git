/* bsw_bswm_cs_connector_c_v3-0-0                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
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
/*  v3-0-0          :2024/09/04                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
