/* bswm_cs_connector_cfg_h_v2-0-0                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSWM/CS/CONNECTOR/CFG/HEADER                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_BSWM_CS_CONNECTOR_CFG_H
#define BSW_BSWM_CS_CONNECTOR_CFG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "oxcan_aubif.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Dem API Name */
#define BSW_BSWM_CS_CFG_FN_DEM_REP            (bsw_bswm_cs_DemErrorReport_dummy)

/* BswM API Name */
#define BSW_BSWM_CS_CFG_FN_BSWM_COMM          (bsw_bswm_cs_BswMComMCrntMode_dummy)
#define BSW_BSWM_CS_CFG_FN_BSWM_COMMPNC       (bsw_bswm_cs_BswMComMCrntPnc_dummy)
#define BSW_BSWM_CS_CFG_FN_BSWM_COMMCHP       (bsw_bswm_cs_BswMComMCrntChPnc_dummy)

/* Dcm API Name */
#define BSW_BSWM_CS_CFG_FN_DCM_NOCOM          (bsw_bswm_cs_DcmNoComMode_dummy)
#define BSW_BSWM_CS_CFG_FN_DCM_SILCOM         (bsw_bswm_cs_DcmSilentComMode_dummy)
#define BSW_BSWM_CS_CFG_FN_DCM_FULCOM         (bsw_bswm_cs_DcmFullComMode_dummy)
#define BSW_BSWM_CS_CFG_FN_DCM_SOR            (bsw_bswm_cs_DcmStartOfRecept_dummy)
#define BSW_BSWM_CS_CFG_FN_DCM_CPRXD          (bsw_bswm_cs_DcmCopyRxData_dummy)
#define BSW_BSWM_CS_CFG_FN_DCM_CPTXD          (bsw_bswm_cs_DcmCopyTxData_dummy)
#define BSW_BSWM_CS_CFG_FN_DCM_TPRXIN         (bsw_bswm_cs_DcmTpRxIndication_dummy)
#define BSW_BSWM_CS_CFG_FN_DCM_TPTXCN         (bsw_bswm_cs_DcmTpTxConfirm_dummy)
#define BSW_BSWM_CS_CFG_FN_DCM_TXCN           (bsw_bswm_cs_DcmTxConfirm_dummy)

/* EcuM API Name */
#define BSW_BSWM_CS_CFG_FN_ECUM_SWUE          (Aubist_UsrSetWakeupEvent)


/* BSWM/CDD API Name */
#define BSW_BSWM_CS_CFG_FN_CDD1INIT
#define BSW_BSWM_CS_CFG_FN_CDD1DEINIT
#define BSW_BSWM_CS_CFG_FN_CDD1PRDEINIT
#define BSW_BSWM_CS_CFG_FN_CDD1WKUP
#define BSW_BSWM_CS_CFG_FN_CDD1SLP
#define BSW_BSWM_CS_CFG_FN_CDD1RESET
#define BSW_BSWM_CS_CFG_FN_CDD1HIGHIN
#define BSW_BSWM_CS_CFG_FN_CDD1HIGHOUT
#define BSW_BSWM_CS_CFG_FN_CDD1MIDIN
#define BSW_BSWM_CS_CFG_FN_CDD1MIDCTRL
#define BSW_BSWM_CS_CFG_FN_CDD1MIDOUT
#define BSW_BSWM_CS_CFG_FN_CDD1INTDRV
#define BSW_BSWM_CS_CFG_FN_CDD1UDIPDUST
#define BSW_BSWM_CS_CFG_FN_CDD1CHKAWK

#define BSW_BSWM_CS_CFG_FN_CDD2INIT
#define BSW_BSWM_CS_CFG_FN_CDD2DEINIT
#define BSW_BSWM_CS_CFG_FN_CDD2PRDEINIT
#define BSW_BSWM_CS_CFG_FN_CDD2WKUP
#define BSW_BSWM_CS_CFG_FN_CDD2SLP
#define BSW_BSWM_CS_CFG_FN_CDD2RESET
#define BSW_BSWM_CS_CFG_FN_CDD2HIGHIN
#define BSW_BSWM_CS_CFG_FN_CDD2HIGHOUT
#define BSW_BSWM_CS_CFG_FN_CDD2MIDIN
#define BSW_BSWM_CS_CFG_FN_CDD2MIDCTRL
#define BSW_BSWM_CS_CFG_FN_CDD2MIDOUT
#define BSW_BSWM_CS_CFG_FN_CDD2INTDRV
#define BSW_BSWM_CS_CFG_FN_CDD2UDIPDUST
#define BSW_BSWM_CS_CFG_FN_CDD2CHKAWK


/* CDDSM API Name */
#define BSW_BSWM_CS_CFG_FN_CDD1SM_RQCM
#define BSW_BSWM_CS_CFG_FN_CDD2SM_RQCM
#define BSW_BSWM_CS_CFG_FN_CDD1SM_GTCM
#define BSW_BSWM_CS_CFG_FN_CDD2SM_GTCM


/* CDD Upper(PduR) API Name */
#define BSW_BSWM_CS_CFG_FN_CDD1UP_TRGT
#define BSW_BSWM_CS_CFG_FN_CDD1UP_TC
#define BSW_BSWM_CS_CFG_FN_CDD1UP_RI
#define BSW_BSWM_CS_CFG_FN_CDD1UP_SOR
#define BSW_BSWM_CS_CFG_FN_CDD1UP_CPRX
#define BSW_BSWM_CS_CFG_FN_CDD1UP_CPTX
#define BSW_BSWM_CS_CFG_FN_CDD1UP_TPRI
#define BSW_BSWM_CS_CFG_FN_CDD1UP_TPTC
#define BSW_BSWM_CS_CFG_FN_CDD2UP_TRGT
#define BSW_BSWM_CS_CFG_FN_CDD2UP_TC
#define BSW_BSWM_CS_CFG_FN_CDD2UP_RI
#define BSW_BSWM_CS_CFG_FN_CDD2UP_SOR
#define BSW_BSWM_CS_CFG_FN_CDD2UP_CPRX
#define BSW_BSWM_CS_CFG_FN_CDD2UP_CPTX
#define BSW_BSWM_CS_CFG_FN_CDD2UP_TPRI
#define BSW_BSWM_CS_CFG_FN_CDD2UP_TPTC


/* CDD Lower(PduR) API Name */
/* CDDIf */
#define BSW_BSWM_CS_CFG_FN_CDD1IF_TX
#define BSW_BSWM_CS_CFG_FN_CDD1IF_CTX
#define BSW_BSWM_CS_CFG_FN_CDD1IF_GITX
#define BSW_BSWM_CS_CFG_FN_CDD1IF_GIRX
#define BSW_BSWM_CS_CFG_FN_CDD2IF_TX
#define BSW_BSWM_CS_CFG_FN_CDD2IF_CTX
#define BSW_BSWM_CS_CFG_FN_CDD2IF_GITX
#define BSW_BSWM_CS_CFG_FN_CDD2IF_GIRX
/* CDDTp */
#define BSW_BSWM_CS_CFG_FN_CDD1TP_TX
#define BSW_BSWM_CS_CFG_FN_CDD1TP_CTX
#define BSW_BSWM_CS_CFG_FN_CDD1TP_CRX
#define BSW_BSWM_CS_CFG_FN_CDD1TP_GITX
#define BSW_BSWM_CS_CFG_FN_CDD1TP_GIRX
#define BSW_BSWM_CS_CFG_FN_CDD2TP_TX
#define BSW_BSWM_CS_CFG_FN_CDD2TP_CTX
#define BSW_BSWM_CS_CFG_FN_CDD2TP_CRX
#define BSW_BSWM_CS_CFG_FN_CDD2TP_GITX
#define BSW_BSWM_CS_CFG_FN_CDD2TP_GIRX


/* GenericNm API Name */
#define BSW_BSWM_CS_CFG_FN_CDD1NM_PSTU
#define BSW_BSWM_CS_CFG_FN_CDD1NM_NREQ
#define BSW_BSWM_CS_CFG_FN_CDD1NM_NRLS
#define BSW_BSWM_CS_CFG_FN_CDD1NM_DCOM
#define BSW_BSWM_CS_CFG_FN_CDD1NM_ECOM
#define BSW_BSWM_CS_CFG_FN_CDD1NM_GST

#define BSW_BSWM_CS_CFG_FN_CDD2NM_PSTU
#define BSW_BSWM_CS_CFG_FN_CDD2NM_NREQ
#define BSW_BSWM_CS_CFG_FN_CDD2NM_NRLS
#define BSW_BSWM_CS_CFG_FN_CDD2NM_DCOM
#define BSW_BSWM_CS_CFG_FN_CDD2NM_ECOM
#define BSW_BSWM_CS_CFG_FN_CDD2NM_GST

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

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#endif /* BSW_BSWM_CS_CONNECTOR_CFG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/03/23                                             */
/*  v1-1-0          :2018/09/17                                             */
/*  v2-0-0          :2021/02/25                                             */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-2                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
