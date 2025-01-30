/* 1.0.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Diagnosis on Can for Toyota MET/HUD based on AUBIST/DEM, DCM                                                                     */
/*  NM Diag  Detection of abnormal global-ecu (Detection of excessive wakeup and sleep ng continuation)                              */
/*===================================================================================================================================*/

#ifndef TYDOCAN_DTC_NMGBL_CFG_H
#define TYDOCAN_DTC_NMGBL_CFG_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDOCAN_DTC_NMGBL_CFG_H_MAJOR           (1U)
#define TYDOCAN_DTC_NMGBL_CFG_H_MINOR           (0U)
#define TYDOCAN_DTC_NMGBL_CFG_H_PATCH           (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "CS_Can.h"

#include "date_clk.h"

#include "memfill_u1.h"
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_DTC_NMGBL_WKF_NUM                  (10U)
#define TYDC_DTC_NMGBL_WKF_SIZE                 (18U)
#define TYDC_DTC_NMGBL_SNGF_NUM                 (5U)
#define TYDC_DTC_NMGBL_SNGF_SIZE                (12U)

#define OXDC_DATA_REA_ANS_NB_AC04               (TYDC_DTC_NMGBL_WKF_SIZE * TYDC_DTC_NMGBL_WKF_NUM)      /* Factor of NM Wakeup  */
#define OXDC_DATA_REA_ANS_NB_AC05               (TYDC_DTC_NMGBL_SNGF_SIZE * TYDC_DTC_NMGBL_SNGF_NUM)    /* Factor of Sleep NG   */

#define TYDC_DTC_NMGBL_RXMON_NONE               (0U)    /* Reception monitoring : Do not monitor */
#define TYDC_DTC_NMGBL_RXMON_WK                 (1U)    /* Reception monitoring : Monitoring for excessive wakeup */
#define TYDC_DTC_NMGBL_RXMON_SNG                (2U)    /* Reception monitoring : Monitoring for sleep ng continuation */

#define TYDC_DTC_NMGBL_CID_NUM                  (3U)
#define TYDC_DTC_NMGBL_CID_NM                   (0U)
#define TYDC_DTC_NMGBL_CID_DI                   (1U)
#define TYDC_DTC_NMGBL_CID_CTL                  (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define u1_g_TyDoCANDtcNmGblCfgNmRun()          (u1_g_oXCANRxEnabled(u1_g_TYDC_DTC_NMGBL_COM_CH))
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void    vd_g_TyDoCANDtcNmGblWkInit(const U1 u1_a_BR_INIT);      /* u1_a_BR_INIT : TRUE = Backup-RAM is initialzied, FALSE = Not */
void    vd_g_TyDoCANDtcNmGblSngInit(const U1 u1_a_BR_INIT);     /* u1_a_BR_INIT : TRUE = Backup-RAM is initialzied, FALSE = Not */
void    vd_g_TyDoCANDtcNmGblWkMainTask(void);
void    vd_g_TyDoCANDtcNmGblSngMainTask(void);

void    vd_g_TyDoCANDtcNmGblSetMonitorMode(const U1 u1_a_MODE);
U1      u1_g_TyDoCANDtcNmGblGetMonitorMode(void);
U1      u1_g_TyDoCANDtcNmGblGetNmLast(U4 * u4_ap_cid);
U1      u1_g_TyDoCANDtcNmGblGetCidByCnt(const U1 u1_a_TYPE, const U1 u1_a_CNT, U4 * u4_ap_cid);
U1      u1_g_TyDoCANDtcNmGblGetRcvOrdr(const U1 u1_a_TYPE);
void    vd_g_TyDoCANDtcNmGblCanidClear(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_g_TyDoCANDtcNmGblCfgWkmAct(const U1 u1_a_RUN);       /* u1_a_RUN : TRUE = Detection processing is on going, FALSE = Not */
                                                                /* TRUE : Wake-up monitor can be activated, FALSE : Not */
U1      u1_g_TyDoCANDtcNmGblCfgWkmReAct(void);                  /* TRUE : Reactibate after abnormality detection, FALSE : Not */
U1      u1_g_TyDoCANDtcNmGblCfgStopWkfRec(void);                /* TRUE : Stop the factor information recording process, FALSE : Not */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern const U1             u1_g_TYDC_DTC_NMGBL_COM_CH;
extern const U1             u1_g_TYDC_DTC_NMGBL_CANIF_CH;
extern const U1             u1_g_TYDC_DTC_NMGBL_REC_CH_BIT;

extern const U4             u4_g_TYDC_DTC_NMGBL_WKM_TOUT;
extern const U2             u2_g_TYDC_DTC_NMGBL_WKC_THRSH;
extern const U4             u4_g_TYDC_DTC_NMGBL_TERM_LMT;

extern const U1             u1_g_TYDC_DTC_NMGBL_DCT_CH;

extern const U4             u4_g_TYDC_DTC_NMGBL_SLM_TOUT;
#endif      /* TYDOCAN_DTC_NMGBL_CFG_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see tydocan_dtc_nmgbl.c, tydocan_dtc_nmgbl_wk.c and tydocan_dtc_nmgbl_sl.c                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
