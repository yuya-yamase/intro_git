/* bswm_can_h_v2-1-0                                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSWM/CAN/HEADER                                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_BSWM_CAN_AR_H
#define BSW_BSWM_CAN_AR_H

#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>
#include <ComStack_Types.h>
#include <BswM_CS.h>
#include <bswm_can/bsw_bswm_can_public.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/*------------------------------*/
/* Unit:status                  */
/*------------------------------*/
/* Function */
#define BswM_Can_CbkDetectEdge           (bsw_bswm_can_st_CbkDetectEdge)

/*------------------------------*/
/* Unit:ctrl                    */
/*------------------------------*/
/* Driver Initialization Status */
#define BSWM_CAN_DRVSTS_OK               (BSW_BSWM_CAN_DRVSTS_OK)
#define BSWM_CAN_DRVSTS_INITNG           (BSW_BSWM_CAN_DRVSTS_INITNG)
#define BSWM_CAN_DRVSTS_REGFAIL          (BSW_BSWM_CAN_DRVSTS_REGFAIL)
#define BSWM_CAN_DRVSTS_UNUSEDREGFAIL    (BSW_BSWM_CAN_DRVSTS_UNUSEDREGFAIL)

/* Channel Fail Status          */
#define BSWM_CAN_CHFAILST_NONE           (BSW_BSWM_CAN_CHFAILST_NONE)
#define BSWM_CAN_CHFAILST_BUSOFF         (BSW_BSWM_CAN_CHFAILST_BUSOFF)
#define BSWM_CAN_CHFAILST_SNDLOCK        (BSW_BSWM_CAN_CHFAILST_SNDLOCK)
#define BSWM_CAN_CHFAILST_RCVLOCK        (BSW_BSWM_CAN_CHFAILST_RCVLOCK)
#define BSWM_CAN_CHFAILST_REGCHECK       (BSW_BSWM_CAN_CHFAILST_REGCHECK)
#define BSWM_CAN_CHFAILST_UNUSEDREGCHK   (BSW_BSWM_CAN_CHFAILST_UNUSEDREGCHK)
#define BSWM_CAN_CHFAILST_MPU            (BSW_BSWM_CAN_CHFAILST_MPU)
#define BSWM_CAN_CHFAILST_INITNG         (BSW_BSWM_CAN_CHFAILST_INITNG)
#define BSWM_CAN_CHFAILST_USER           (BSW_BSWM_CAN_CHFAILST_USER)
#define BSWM_CAN_CHFAILST_ERROR_PASSIVE  (BSW_BSWM_CAN_CHFAILST_ERROR_PASSIVE)
#define BSWM_CAN_CHFAILST_NMTXTIMEOUT    (BSW_BSWM_CAN_CHFAILST_NMTXTIMEOUT)

/* Controller Error Status      */
#define BSWM_CAN_CTRERRST_NONE           (BSW_BSWM_CAN_CTRERRST_NONE)
#define BSWM_CAN_CTRERRST_BUSOFF         (BSW_BSWM_CAN_CTRERRST_BUSOFF)
#define BSWM_CAN_CTRERRST_PASSIVE        (BSW_BSWM_CAN_CTRERRST_PASSIVE)

/* Function */
#define BswM_Can_CbkInitDrvIndication    (bsw_bswm_can_ctrl_CbkInitDrvInd)
#define BswM_Can_CbkPreControlRx         (bsw_bswm_can_ctrl_CbkPreCtrlRx)
#define BswM_Can_CbkPreControlTx         (bsw_bswm_can_ctrl_CbkPreCtrlTx)
#define BswM_Can_GetChFailStatus         (bsw_bswm_can_ctrl_GetChFailStat)
#define BswM_Can_GetControllerErrStatus  (bsw_bswm_can_ctrl_GetCtrErrStat)

/*------------------------------*/
/* Unit:backup                  */
/*------------------------------*/
/* BackupData Size(MAX)         */
#define BSWM_CAN_BACKUPDATASIZE          (BSW_BSWM_CAN_BACKUPDATASIZE)

/* Function */
#define BswM_Can_SetBackupData           (bsw_bswm_can_bkup_SetBackupData)
#define BswM_Can_GetBackupData           (bsw_bswm_can_bkup_GetBackupData)

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

#endif /* BSW_BSWM_CAN_AR_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/03/23                                             */
/*  v1-0-1          :2018/02/23                                             */
/*  v1-1-0          :2018/12/17                                             */
/*  v2-0-0          :2021/05/31                                             */
/*  v2-1-0          :2022/09/15                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
