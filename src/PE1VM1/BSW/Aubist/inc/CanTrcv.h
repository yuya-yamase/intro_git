/* cantrcv_h_v3-0-0                                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CANTRCV/HEADER                                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_CANTRCV_AR_H
#define BSW_CANTRCV_AR_H

#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>
#include <ComStack_Types.h>
#include <Can_GeneralTypes.h>
#include <cantrcv/bsw_cantrcv_public.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Vendor ID */
#define CANTRCV_VENDOR_ID                    (BSW_CANTRCV_VENDOR_ID)

/* Module ID */
#define CANTRCV_MODULE_ID                    (BSW_CANTRCV_MODULE_ID)

/* AUTOSAR Release Version */
#define CANTRCV_AR_RELEASE_MAJOR_VERSION     (BSW_CANTRCV_AR_RELEASE_MAJOR_VERSION)
#define CANTRCV_AR_RELEASE_MINOR_VERSION     (BSW_CANTRCV_AR_RELEASE_MINOR_VERSION)
#define CANTRCV_AR_RELEASE_REVISION_VERSION  (BSW_CANTRCV_AR_RELEASE_REVISION_VERSION)

/* Vendor Specification Version */
#define CANTRCV_SW_MAJOR_VERSION             (BSW_CANTRCV_SW_MAJOR_VERSION)
#define CANTRCV_SW_MINOR_VERSION             (BSW_CANTRCV_SW_MINOR_VERSION)
#define CANTRCV_SW_PATCH_VERSION             (BSW_CANTRCV_SW_PATCH_VERSION)

/* Function */
#define CanTrcv_Init                         (bsw_cantrcv_st_Init)
#define CanTrcv_DeInit                       (bsw_cantrcv_st_DeInit)
#define CanTrcv_SetOpMode                    (bsw_cantrcv_st_SetOpMode)
#define CanTrcv_GetOpMode                    (bsw_cantrcv_st_GetOpMode)
#define CanTrcv_GetBusWuReason               (bsw_cantrcv_st_GetBusWuReason)
#define CanTrcv_GetVersionInfo               (bsw_cantrcv_st_GetVersionInfo)
#define CanTrcv_SetWakeupMode                (bsw_cantrcv_st_SetWakeupMode)
#define CanTrcv_GetTrcvSystemData            (bsw_cantrcv_st_GetTrcvSystemData)
#define CanTrcv_ClearTrcvWufFlag             (bsw_cantrcv_st_ClearTrcvWufFlag)
#define CanTrcv_ReadTrcvTimeoutFlag          (bsw_cantrcv_st_ReadTrcvTimeoutFlag)
#define CanTrcv_ClearTrcvTimeoutFlag         (bsw_cantrcv_st_ClearTrcvTimeoutFlg)
#define CanTrcv_ReadTrcvSilenceFlag          (bsw_cantrcv_st_ReadTrcvSilenceFlag)
#define CanTrcv_CheckWakeup                  (bsw_cantrcv_st_CheckWakeup)
#define CanTrcv_SetPNActivationState         (bsw_cantrcv_st_SetPNActivationStat)
#define CanTrcv_CheckWakeFlag                (bsw_cantrcv_st_CheckWakeFlag)
#define CanTrcv_MainFunction                 (bsw_cantrcv_st_MainFunction)
#define CanTrcv_MainFunctionDiagnostics      (bsw_cantrcv_st_MainFunctionDiag)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
#define CanTrcv_PNActivationType          Bsw_CanTrcv_PNActivationType
#define CanTrcv_TrcvFlagStateType         Bsw_CanTrcv_TrcvFlagStateType

#define CanTrcv_ConfigType                Bsw_CanTrcv_ConfigType

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* BSW_CANTRCV_AR_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/02/22                                             */
/*  v1-1-0          :2018/11/20                                             */
/*  v2-0-0          :2021/06/04                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
