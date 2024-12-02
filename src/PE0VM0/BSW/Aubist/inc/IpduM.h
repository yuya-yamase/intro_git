/* ipdum_h_v2-0-0                                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | IPDUM/HEADER                                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_IPDUM_AR_H
#define BSW_IPDUM_AR_H

#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>
#include <ComStack_Types.h>
#include <ipdum/bsw_ipdum_public.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Vendor ID */
#define IPDUM_VENDOR_ID                    (BSW_IPDUM_VENDOR_ID)

/* Module ID */
#define IPDUM_MODULE_ID                    (BSW_IPDUM_MODULE_ID)

/* AUTOSAR Release Version */
#define IPDUM_AR_RELEASE_MAJOR_VERSION     (BSW_IPDUM_AR_RELEASE_MAJOR_VERSION)
#define IPDUM_AR_RELEASE_MINOR_VERSION     (BSW_IPDUM_AR_RELEASE_MINOR_VERSION)
#define IPDUM_AR_RELEASE_REVISION_VERSION  (BSW_IPDUM_AR_RELEASE_REVISION_VERSION)

/* Vendor Specification Version */
#define IPDUM_SW_MAJOR_VERSION             (BSW_IPDUM_SW_MAJOR_VERSION)
#define IPDUM_SW_MINOR_VERSION             (BSW_IPDUM_SW_MINOR_VERSION)
#define IPDUM_SW_PATCH_VERSION             (BSW_IPDUM_SW_PATCH_VERSION)

/* Function */
#define IpduM_Transmit                     (bsw_ipdum_trx_Transmit)
#define IpduM_CancelTransmit               (bsw_ipdum_trx_CancelTransmit)
#define IpduM_MainFunctionTx               (bsw_ipdum_st_MainFunctionTx)
#define IpduM_MainFunctionRx               (bsw_ipdum_st_MainFunctionRx)
#define IpduM_Init                         (bsw_ipdum_st_Init)
#define IpduM_DeInit                       (bsw_ipdum_st_shutdown)
#define IpduM_GetVersionInfo               (bsw_ipdum_st_GetVersionInfo)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
#define IpduM_ConfigType               Bsw_IpduM_ConfigType

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif  /* BSW_IPDUM_AR_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2018/11/13                                             */
/*  v2-0-0          :2021/05/24                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
