/* ldcom_h_v3-0-0                                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | LDCOM/HEADER                                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef BSW_LDCOM_AR_H
#define BSW_LDCOM_AR_H

#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>

#include <ComStack_Types.h>

#include <ldcom/bsw_ldcom_public.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Vendor ID */
#define LDCOM_VENDOR_ID                    (BSW_LDCOM_VENDOR_ID)

/* Module ID */
#define LDCOM_MODULE_ID                    (BSW_LDCOM_MODULE_ID)

/* AUTOSAR Release Version */
#define LDCOM_AR_RELEASE_MAJOR_VERSION     (BSW_LDCOM_AR_RELEASE_MAJOR_VERSION)
#define LDCOM_AR_RELEASE_MINOR_VERSION     (BSW_LDCOM_AR_RELEASE_MINOR_VERSION)
#define LDCOM_AR_RELEASE_REVISION_VERSION  (BSW_LDCOM_AR_RELEASE_REVISION_VERSION)

/* Vendor Specification Version */
#define LDCOM_SW_MAJOR_VERSION             (BSW_LDCOM_SW_MAJOR_VERSION)
#define LDCOM_SW_MINOR_VERSION             (BSW_LDCOM_SW_MINOR_VERSION)
#define LDCOM_SW_PATCH_VERSION             (BSW_LDCOM_SW_PATCH_VERSION)

/* Function */
#define LdCom_Init                         (bsw_ldcom_st_Init)
#define LdCom_DeInit                       (bsw_ldcom_st_DeInit)
#define LdCom_Transmit                     (bsw_ldcom_tx_Transmit)
#define LdCom_CancelTransmit               (bsw_ldcom_tx_CancelTransmit)
#define LdCom_GetVersionInfo               (bsw_ldcom_st_GetVersionInfo)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* Initialization Data */
#define LdCom_ConfigType               Bsw_LdCom_ConfigType

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif  /* BSW_LDCOM_AR_H */


/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/05/16                                             */
/*  v1-0-1          :2018/02/09                                             */
/*  v1-1-0          :2018/12/13                                             */
/*  v1-2-0          :2019/11/06                                             */
/*  v2-0-0          :2021/05/24                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
