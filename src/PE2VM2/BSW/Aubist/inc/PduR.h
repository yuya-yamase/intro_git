/* pdur_h_v3-0-0                                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | PDUR/HEADER                                               */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_PDUR_AR_H
#define BSW_PDUR_AR_H

#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>

#include <ComStack_Types.h>
#include <pdur/bsw_pdur_public.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Component Identifier */
/* Upper */
#define PDUR_UPCOMP_COM                   (BSW_PDUR_UPCOMP_COM)
#define PDUR_UPCOMP_DCM                   (BSW_PDUR_UPCOMP_DCM)
#define PDUR_UPCOMP_LDCOM                 (BSW_PDUR_UPCOMP_LDCOM)
#define PDUR_UPCOMP_CDD1                  (BSW_PDUR_UPCOMP_CDD1)
#define PDUR_UPCOMP_CDD2                  (BSW_PDUR_UPCOMP_CDD2)

/* Lower */
#define PDUR_LOCOMP_IF                    (BSW_PDUR_LOCOMP_IF)
#define PDUR_LOCOMP_TP                    (BSW_PDUR_LOCOMP_TP)
#define PDUR_LOCOMP_CAN                   (BSW_PDUR_LOCOMP_CAN)
#define PDUR_LOCOMP_LIN                   (BSW_PDUR_LOCOMP_LIN)
#define PDUR_LOCOMP_SOAD                  (BSW_PDUR_LOCOMP_SOAD)
#define PDUR_LOCOMP_DOIP                  (BSW_PDUR_LOCOMP_DOIP)

#define PDUR_LOCOMP_CANIF                 (BSW_PDUR_LOCOMP_CANIF)
#define PDUR_LOCOMP_CANTP                 (BSW_PDUR_LOCOMP_CANTP)
#define PDUR_LOCOMP_LINIF                 (BSW_PDUR_LOCOMP_LINIF)
#define PDUR_LOCOMP_LINTP                 (BSW_PDUR_LOCOMP_LINTP)
#define PDUR_LOCOMP_SOADIF                (BSW_PDUR_LOCOMP_SOADIF)
#define PDUR_LOCOMP_SOADTP                (BSW_PDUR_LOCOMP_SOADTP)
#define PDUR_LOCOMP_DOIPIF                (BSW_PDUR_LOCOMP_DOIPIF)
#define PDUR_LOCOMP_DOIPTP                (BSW_PDUR_LOCOMP_DOIPTP)
#define PDUR_LOCOMP_CANNM                 (BSW_PDUR_LOCOMP_CANNM)
#define PDUR_LOCOMP_CANCDD1               (BSW_PDUR_LOCOMP_CANCDD1)
#define PDUR_LOCOMP_CANCDD2               (BSW_PDUR_LOCOMP_CANCDD2)
#define PDUR_LOCOMP_LINNM                 (BSW_PDUR_LOCOMP_LINNM)
#define PDUR_LOCOMP_LINCDD1               (BSW_PDUR_LOCOMP_LINCDD1)
#define PDUR_LOCOMP_LINCDD2               (BSW_PDUR_LOCOMP_LINCDD2)
#define PDUR_LOCOMP_UDPNM                 (BSW_PDUR_LOCOMP_UDPNM)
#define PDUR_LOCOMP_ETHCDD1               (BSW_PDUR_LOCOMP_ETHCDD1)
#define PDUR_LOCOMP_ETHCDD2               (BSW_PDUR_LOCOMP_ETHCDD2)
#define PDUR_LOCOMP_XCP                   (BSW_PDUR_LOCOMP_XCP)

/* Component Identifier for SecOC */
/* Lower */
#define PDUR_COMPID_CANIF                 (BSW_PDUR_COMPID_CANIF)
#define PDUR_COMPID_CANTP                 (BSW_PDUR_COMPID_CANTP)
#define PDUR_COMPID_LINIF                 (BSW_PDUR_COMPID_LINIF)
#define PDUR_COMPID_LINTP                 (BSW_PDUR_COMPID_LINTP)
#define PDUR_COMPID_SOADIF                (BSW_PDUR_COMPID_SOADIF)
#define PDUR_COMPID_SOADTP                (BSW_PDUR_COMPID_SOADTP)
#define PDUR_COMPID_DOIPIF                (BSW_PDUR_COMPID_DOIPIF)
#define PDUR_COMPID_DOIPTP                (BSW_PDUR_COMPID_DOIPTP)

/* Upper */
#define PDUR_COMPID_COM                   (BSW_PDUR_COMPID_COM)
#define PDUR_COMPID_DCM                   (BSW_PDUR_COMPID_DCM)
#define PDUR_COMPID_LDCOM                 (BSW_PDUR_COMPID_LDCOM)
#define PDUR_COMPID_CDD1                  (BSW_PDUR_COMPID_CDD1)
#define PDUR_COMPID_CDD2                  (BSW_PDUR_COMPID_CDD2)

/* Component Identifier Offset */
#define PDUR_COMPID_UPOFFSET              (BSW_PDUR_COMPID_UPOFFSET)

/* PDU ID */
#define PDUR_COMP_MASK                    (BSW_PDUR_COMP_MASK)
#define PDUR_ID_MASK                      (BSW_PDUR_ID_MASK)
#define PDUR_INVALID_PDU_ID               (BSW_PDUR_INVALID_PDU_ID)

/* Frame ID */
#define PDUR_INVALID_FRAME_ID             (BSW_PDUR_INVALID_FRAME_ID)

/* PDUR State */
#define PDUR_UNINIT                       (BSW_PDUR_UNINIT)
#define PDUR_ONLINE                       (BSW_PDUR_ONLINE)

/* Return Value (Extend) */
#define PDUR_BUSY                         (BSW_PDUR_BUSY)

/* SecOC Component Identifier */
#define PDUR_LOCOMP_SECOCIF               (BSW_PDUR_LOCOMP_SECOCIF)
#define PDUR_LOCOMP_SECOCTP               (BSW_PDUR_LOCOMP_SECOCTP)

/* Vendor ID */
#define PDUR_VENDOR_ID                    (BSW_PDUR_VENDOR_ID)

/* Module ID */
#define PDUR_MODULE_ID                    (BSW_PDUR_MODULE_ID)

/* AUTOSAR Release Version */
#define PDUR_AR_RELEASE_MAJOR_VERSION     (BSW_PDUR_AR_RELEASE_MAJOR_VERSION)
#define PDUR_AR_RELEASE_MINOR_VERSION     (BSW_PDUR_AR_RELEASE_MINOR_VERSION)
#define PDUR_AR_RELEASE_REVISION_VERSION  (BSW_PDUR_AR_RELEASE_REVISION_VERSION)

/* Vendor Specification Version */
#define PDUR_SW_MAJOR_VERSION             (BSW_PDUR_SW_MAJOR_VERSION)
#define PDUR_SW_MINOR_VERSION             (BSW_PDUR_SW_MINOR_VERSION)
#define PDUR_SW_PATCH_VERSION             (BSW_PDUR_SW_PATCH_VERSION)

/* Function */
#define PduR_Init                         (bsw_pdur_st_Init)
#define PduR_DeInit                       (bsw_pdur_st_DeInit)
#define PduR_GetVersionInfo               (bsw_pdur_st_GetVersionInfo)
#define PduR_GetConfigurationId           (bsw_pdur_st_GetConfigurationId)
#define PduR_EnableRouting                (bsw_pdur_ctrl_EnableRouting)
#define PduR_DisableRouting               (bsw_pdur_ctrl_DisableRouting)
#define PduR_GetTxId                      (bsw_pdur_rt_GetTxId)
#define PduR_GetCurrentRxId               (bsw_pdur_rt_GetCurrentRxId)
#define PduR_GetIpduId                    (bsw_pdur_inf_GetIpduId)
#define PduR_GetLpduId                    (bsw_pdur_inf_GetLpduId)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
#define PduR_PBConfigType             Bsw_PduR_PBConfigType
#define PduR_PBConfigIdType           Bsw_PduR_PBConfigIdType
#define PduR_RoutingPathGroupIdType   Bsw_PduR_RoutingPathGroupIdType
#define PduR_StateType                Bsw_PduR_StateType
#define PduR_TxModeType               Bsw_PduR_TxModeType

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* BSW_PDUR_AR_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/02/22                                             */
/*  v2-0-0          :2021/05/24                                             */
/*  v3-0-0          :2024/09/04                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
