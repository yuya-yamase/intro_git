/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  F-Spo Manager                                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef FSPOMGR_CFG_H
#define FSPOMGR_CFG_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define FSPOMGR_CFG_H_MAJOR                      (1)
#define FSPOMGR_CFG_H_MINOR                      (0)
#define FSPOMGR_CFG_H_PATCH                      (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include File                                                                                                                     */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"

#include "veh_opemd.h"

#include "g_monitor.h"
#include "hmigmon.h"

#include "fspo_cmn.h"
#include "oilpress.h"
#include "oiltemp.h"

#include "fspomgr.h"
#include "fsposnsr.h"
#include "alert.h"
#include "calibration.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define FSPO_ITEM_MAX                            (4U)                                /* Number of item                               */

/* FSPO Enabled State */
#define FSPOMGR_OILPRSS_IS_SUPD                  (0x01U)                             /* Oil pressure                                 */
#define FSPOMGR_OILTEMP_IS_SUPD                  (0x01U)                             /* Oil temperature                              */
#define FSPOMGR_GMNTR_IS_SUPD                    (0x02U)                             /* G-Moniter                                    */

#define FSPOMGR_OILPRE_WRN_WRN_ON                   (ALERT_REQ_P_OILPRE_WRN_WRN_ON)
#define FSPOMGR_OILPRE_WRN_WRN_FLSH                 (ALERT_REQ_P_OILPRE_WRN_WRN_FLSH)
#define FSPOMGR_OILPRE_WRN_WRN_OFF                  (ALERT_REQ_P_OILPRE_WRN_WRN_OFF)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define u1_FSPOMGR_IG_ISON()                     (u1_g_VehopemdIgnOn())              /* IG state                                     */
#define u1_FSPOMGR_OILPRSWRN_ISON()              (u1_g_AlertReqByCh((U2)ALERT_CH_P_OILPRE_WRN)) /* Oil pressure Warning state            */
#define u2_FSPOMGR_GET_SIGSTS()                  (u2_g_FsposnsrGetSigSts())          /* fail state                                   */
#define vd_FSPOMGR_SNSR_BON()                    (vd_g_FsposnsrBon())                /* Fsposnsr BON   event function                */
#define vd_FSPOMGR_SNSR_WKUP()                   (vd_g_FsposnsrWkup())               /* Fsposnsr WKUP  event function                */
#define vd_FSPOMGR_SNSR_IGON()                   (vd_g_FsposnsrIgon())               /* Fsposnsr IGON  event function                */
#define vd_FSPOMGR_SNSR_IGOFF()                  (vd_g_FsposnsrIgoff())              /* Fsposnsr IGOFF event function                */
#define vd_FSPOMGR_CMN_BON()                     (vd_g_FspocmnBon())                 /* Fspocmn  BON   event function                */
#define vd_FSPOMGR_CMN_WKUP()                    (vd_g_FspocmnWkup())                /* Fspocmn  WKUP  event function                */
#define vd_FSPOMGR_CMN_SIGUPDT()                 (vd_g_FspocmnSigupdt())             /* Fspocmn  Update      function                */
#define vd_FSPOMGR_CMN_IGON()                    (vd_g_FspocmnIgon())                /* Fspocmn  IGON  event function                */
#define vd_FSPOMGR_CMN_IGOFF()                   (vd_g_FspocmnIgoff())               /* Fspocmn  IGOFF event function                */
#define u1_FSPOMGR_GET_FSPO_SUPD()               ((U1)(FSPOMGR_OILPRSS_IS_SUPD | FSPOMGR_OILTEMP_IS_SUPD | FSPOMGR_GMNTR_IS_SUPD))
                                                                                     /* FSPO Support Info                            */
#define u1_FSPOMGR_GET_FSPO_NOSUPD()             ((U1)(FSPOMGR_OILPRSS_IS_SUPD | FSPOMGR_OILTEMP_IS_SUPD))
                                                                                     /* FSPO No Support Info                         */
/* MCU CONST IF*/
#define u1_FSPOMGR_CALIB_BRAND                   (u1_CALIB_MCUID0024_BRAND)          /* Mcu Const brand  info                        */
#define u1_FSPOMGR_CALIB_SPORTS                  (u1_CALIB_MCUID0025_SPORTS)         /* Mcu Const sports info                        */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    void (* const       fp_vd_BONFUNC)(void);                                        /*  BON  event function address                 */
    void (* const       fp_vd_WKUPFUNC)(void);                                       /*  WKUP event function address                 */
    void (* const       fp_vd_INCFUNC)(const ST_FSPOSNSR_INCARG* stp_a_INCARG);      /*  Cumulative function address                 */
    void (* const       fp_vd_TRSFUNC)(U2 u2_a_evtbit, U2 u2_a_sigfail);             /*  State transition function address           */
    void (* const       fp_vd_UPDTFUNC)(void);                                       /*  Update function address                     */
    U1                  u1_supd_msk;                                                 /*  Effective judgment mask                     */
}ST_FSPO_ITEMCFG;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const ST_FSPO_ITEMCFG st_sp_FSPO_ITEMCFG[FSPO_ITEM_MAX]= {
    /*  BON event function          WKUP event function         Cumulative function     State transition function   Update function                 Effective judgment mask     */
    {   &vd_g_GmntrInit,            &vd_g_GmntrInit,            &vd_g_GmntrInc,         &vd_g_GmntrTrnsit,          &vd_g_GmntrUpdt,                (U1)FSPOMGR_GMNTR_IS_SUPD   },
    {   &vd_g_HmiGmonBonInitial,    &vd_g_HmiGmonWkupInitial,   vdp_PTR_NA,             vdp_PTR_NA,                 &vd_g_HmiGmonPeakHoldMainTask,  (U1)FSPOMGR_GMNTR_IS_SUPD   },
    {   &vd_g_OilPrssInit,          &vd_g_OilPrssInit,          &vd_g_OilPrssInc,       &vd_g_OilPrssTrnsit,        &vd_g_OilPrssUpdt,              (U1)FSPOMGR_OILPRSS_IS_SUPD },
    {   &vd_g_OilTmpInit,           &vd_g_OilTmpInit,           &vd_g_OilTmpInc,        &vd_g_OilTmpTrnsit,         &vd_g_OilTmpUpdt,               (U1)FSPOMGR_OILTEMP_IS_SUPD }
 };

#endif      /* FSPOMGR_PRM */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  fspomgr.c                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/
