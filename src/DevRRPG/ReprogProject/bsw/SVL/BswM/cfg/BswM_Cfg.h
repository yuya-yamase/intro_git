/* BswM_Cfg_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | BswM/Cfg/HEADER                                             */
/******************************************************************************/
#ifndef BSWM_CFG_H
#define BSWM_CFG_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <BswM.h>

#include <CanSM_BswM.h>
#if (REPROG_CFG_ETH_USE == STD_ON)
#include <EthSM.h>
#endif
#if (REPROG_CFG_CXPI_USE == STD_ON)
#include <CxpiTp/CxpiCdd_Tp_RxCfg.h>
#endif


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define BSWM_CFG_INITVAL_REWRITE    (BSWM_MODE_REWRITE_NONE)
#define BSWM_CFG_INITVAL_SESSION    (BSWM_MODE_SESSION_DEF)
#define BSWM_CFG_INITVAL_SECURITY   (BSWM_MODE_SECURITY_LOCK)
#if (REPROG_CFG_SBL_TYPE_DOWNLOAD == STD_ON)
 #define BSWM_CFG_INITVAL_FLS_PRG   (BSWM_MODE_FLS_PRG_NOTREADY)
#else
 #define BSWM_CFG_INITVAL_FLS_PRG   (BSWM_MODE_FLS_PRG_READY)
#endif
#define BSWM_CFG_INITVAL_ECU_RESET  (BSWM_MODE_ECU_RESET_NONE)
#define BSWM_CFG_INITVAL_FINISH     (BSWM_MODE_FINISH_NONE)
#define BSWM_CFG_INITVAL_MAIN_ERR   (BSWM_MODE_MAIN_ERR_NONE)
#define BSWM_CFG_INITVAL_USR_RESET  (BSWM_MODE_USR_RESET_NONE)
#define BSWM_CFG_INITVAL_USR_SLEEP  (BSWM_MODE_USR_SLEEP_NONE)
#define BSWM_CFG_INITVAL_ACC        (BSWM_MODE_ACC_NONE)
#define BSWM_CFG_INITVAL_IG         (BSWM_MODE_IG_NONE)
#define BSWM_CFG_INITVAL_CANSM      (CANSM_BSWM_NO_COMMUNICATION)
#if (REPROG_CFG_ETH_USE == STD_ON)
#define BSWM_CFG_INITVAL_ETHSM      (ETHSM_STATE_OFFLINE)
#define BSWM_CFG_INITVAL_ETHSENDRCV (BSWM_MODE_ETH_SENDRCV_NONE)
#endif

#define BSWM_CFG_FINISHTYPE_1       (BSWM_FINISHTYPE_USR_RESET)
#define BSWM_CFG_FINISHTYPE_2       (BSWM_FINISHTYPE_USR_SLEEP)
#define BSWM_CFG_FINISHTYPE_3       (BSWM_FINISHTYPE_ECU_RESET)
#define BSWM_CFG_FINISHTYPE_4       (BSWM_FINISHTYPE_MAIN_ERR)
#define BSWM_CFG_FINISHTYPE_5       (BSWM_FINISHTYPE_ERROR)
#define BSWM_CFG_FINISHTYPE_6       (BSWM_FINISHTYPE_ACCOFF)
#define BSWM_CFG_FINISHTYPE_7       (BSWM_FINISHTYPE_IGOFF)

#if (REPROG_CFG_CXPI_USE == STD_ON)
#define BSWM_CFG_CXPISM_NETWORKID      (0U)
#define BSWM_CFG_CXPI_PDUID_NUM        (2U)
#define BSWM_CFG_CXPISM_NAD_0          (BSWM_UCFG_CXPISM_NAD_PHYSICAL)
#define BSWM_CFG_CXPISM_NAD_1          (0x7EU)
#define BSWM_CFG_CXPISM_IPDUID_0       (CXPICDD_TP_RX_CFG_PDU_0)
#define BSWM_CFG_CXPISM_IPDUID_1       (CXPICDD_TP_RX_CFG_PDU_1)
#define BSWM_CFG_CXPISM_CONTROLLERID   (0U)
#endif


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/


#endif /* BSWM_CFG_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

