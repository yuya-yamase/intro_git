/* bswm_cs_connector_cfg_h_v3-0-0                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
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
/*  v3-0-0          :2024/09/04                                             */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-3-z0003                                        */
/*  BSW plug-in        :v3-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
