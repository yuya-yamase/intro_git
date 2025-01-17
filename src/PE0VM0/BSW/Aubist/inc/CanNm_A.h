/* cannm_a_v2-0-0                                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CANNM/A/HEADER                                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_CANNM_A_AR_H
#define BSW_CANNM_A_AR_H

#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>
#include <ComStack_Types.h>
#include <NmStack_Types.h>
#include <CanNm.h>
#include <cannm/bsw_cannm_a_public.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define    CANNM_A_NWST_RING_STABLE         (BSW_CANNM_A_NWST_RING_STABLE)       /* Network Status : Stable                        */
#define    CANNM_A_NWST_BUS_ERROR           (BSW_CANNM_A_NWST_BUS_ERROR)         /* Network Status : Busoff                        */
#define    CANNM_A_NWST_NM_ACTIVE           (BSW_CANNM_A_NWST_NM_ACTIVE)         /* Network Status : NMActive                      */
#define    CANNM_A_NWST_LIMP_HOME           (BSW_CANNM_A_NWST_LIMP_HOME)         /* Network Status : NMLimpHome                    */
#define    CANNM_A_NWST_BUS_SLEEP           (BSW_CANNM_A_NWST_BUS_SLEEP)         /* Network Status : NMBusSleep                    */
#define    CANNM_A_NWST_WAIT_BUS_SLEEP      (BSW_CANNM_A_NWST_WAIT_BUS_SLEEP)    /* Network Status : NMTwbsNormal or NMTwbsLimpHome */
#define    CANNM_A_NWST_TXRINGDATA_ALLOWED  (BSW_CANNM_A_NWST_TXRINGDATA_ALLOWED)/* Network Status : Access Disable for Data Field on Ring Message */
#define    CANNM_A_NWST_BUS_SLEEP_IND       (BSW_CANNM_A_NWST_BUS_SLEEP_IND)     /* Network Status : Sleep.ind=1                   */
#define    CANNM_A_NWST_ALL_OFF             (BSW_CANNM_A_NWST_ALL_OFF)           /* Network Status : All Off                       */

/*------------------------------------------*/
/* Unit: CONTROL(getstatus)                 */
/*------------------------------------------*/
/* Function */
#define    CanNmA_GetNetworkStatus       (bsw_cannm_a_ctrl_GetNwStatus)

/*------------------------------------------*/
/* Unit: OSEK-NM(oseklibch)                 */
/*------------------------------------------*/
/* Function */
#define    CanNmA_GetTxCount             (bsw_cannm_a_oseknm_GetTxCount)
#define    CanNmA_GetRxCount             (bsw_cannm_a_oseknm_GetRxCount)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
#define    CanNmA_NetworkStatusType  Bsw_CanNmA_NetworkStatusType
/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* BSW_CANNM_A_AR_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/02/22                                             */
/*  v1-1-0          :2020/04/15                                             */
/*  v2-0-0          :2021/06/22                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
