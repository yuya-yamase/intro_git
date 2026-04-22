/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Diagnosis on Can for MET/HUD based on AUBIST/DEM, DCM                                                                            */
/*  Connect AUBIST <--> oXDoCan header                                                                                               */
/*===================================================================================================================================*/

#ifndef OXDOCAN_AUBIF_H
#define OXDOCAN_AUBIF_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDOCAN_AUBIF_H_MAJOR                    (1U)
#define OXDOCAN_AUBIF_H_MINOR                    (0U)
#define OXDOCAN_AUBIF_H_PATCH                    (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "oxdocan_oem.h"
#include "Dcm.h"
#include "Dem.h"
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDC_DTC_EVM_S14                         (0x01U)
#define OXDC_DTC_EVM_MSK                         (0x02U)

#define OXDC_SECURITY_ID01                       (1U)
#define OXDC_SECURITY_ID02                       (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* ---------------------------------------------------------- */
/* inc/Platform_Types.h                                       */
/* ---------------------------------------------------------- */
/* typedef unsigned char                   boolean;           */
/* typedef unsigned char                   uint8;             */
/* typedef unsigned short                  uint16;            */
/* typedef unsigned long                   uint32;            */
/* typedef unsigned long long              uint64;            */
/* typedef signed char                     sint8;             */
/* typedef signed short                    sint16;            */
/* typedef signed long                     sint32;            */
/* typedef signed long long                sint64;            */

/* typedef unsigned long                   uint8_least;       */
/* typedef unsigned long                   uint16_least;      */
/* typedef unsigned long                   uint32_least;      */
/* typedef signed long                     sint8_least;       */
/* typedef signed long                     sint16_least;      */
/* typedef signed long                     sint32_least;      */

/* typedef float                           float32;           */
/* typedef double                          float64;           */

/* ---------------------------------------------------------- */
/* inc/Std_Types.h                                            */
/* ---------------------------------------------------------- */
/* typedef uint8                           Std_ReturnType;    */

/* ---------------------------------------------------------- */
/* inc/Dcm_Types.h                                            */
/* ---------------------------------------------------------- */
/* typedef uint8                   Dcm_CommunicationModeType; */
/*                                                            */
/* #define DCM_ENABLE_RX_TX_NORM               (0x00U)        */
/* #define DCM_ENABLE_RX_DISABLE_TX_NORM       (0x01U)        */
/* #define DCM_DISABLE_RX_ENABLE_TX_NORM       (0x02U)        */
/* #define DCM_DISABLE_RX_TX_NORMAL            (0x03U)        */
/* #define DCM_ENABLE_RX_TX_NM                 (0x04U)        */
/* #define DCM_ENABLE_RX_DISABLE_TX_NM         (0x05U)        */
/* #define DCM_DISABLE_RX_ENABLE_TX_NM         (0x06U)        */
/* #define DCM_DISABLE_RX_TX_NM                (0x07U)        */
/* #define DCM_ENABLE_RX_TX_NORM_NM            (0x08U)        */
/* #define DCM_ENABLE_RX_DISABLE_TX_NORM_NM    (0x09U)        */
/* #define DCM_DISABLE_RX_ENABLE_TX_NORM_NM    (0x0AU)        */
/* #define DCM_DISABLE_RX_TX_NORM_NM           (0x0BU)        */

/* typedef uint8                   Dcm_ReturnReadMemoryType;  */
/* typedef uint8                   Dcm_OpStatusType;          */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*--- session -----------------------------------------------------------------------------------------------------------------------*/
void    vd_g_oXDoCANAubIfComTREOvrrd(const uint8 u1_a_COM_CH, const uint8 u1_a_MODE);

uint8   u1_g_oXDoCANAubIfRpgToAct(uint8 * u1_a_errcode);
uint8   u1_g_oXDoCANAubIfRpgToRun(uint8 OpStatus);
#if ( OXDC_FUNC_RPG_RESET == OXDC_USE )
void    vd_g_oXDoCANAubIfRpgSwReset(void);
#endif /* ( OXDC_FUNC_RPG_RESET == OXDC_USE ) */

void    vd_g_oXDoCANCfgSesChange(const uint8 u1_a_OLD, const uint8 u1_a_NEW);

uint8   u1_g_oXDoCANComCtrlChk(uint8 * u1_ap_err);

/*--- dtc ---------------------------------------------------------------------------------------------------------------------------*/
uint8   u1_g_oXDoCANAubIfDtcNvmWrStat(const uint16 u2_a_BID);
void    vd_g_oXDoCANAubIfDtcNvmWrBlock(const uint16 u2_a_BID, const uint8 * u1_ap_SRC);
uint8   u1_g_oXDoCANAubIfTripcnt(uint8 * u1_ap_tripcnt);
uint8   u1_g_oXDoCANAubIfOdo(uint8 * u1_ap_odo);
uint8   u1_g_oXDoCANAubIfGmt(uint8 * u1_ap_gmt);
uint8   u1_g_oXDoCANAubIfNmWkf(uint8 * u1_ap_wkf);
uint8   u1_g_oXDoCANAubIfNmSngf(uint8 * u1_ap_sngf);
uint8   u1_g_oXDoCANAubIfEcuWkf(uint8 * u1_ap_wkf);
uint8   u1_g_oXDoCANAubIfEcuSngf(uint8 * u1_ap_sngf);
uint8   u1_g_oXDoCANAubIfNmGblWkf(uint8 * u1_ap_wkf);
uint8   u1_g_oXDoCANAubIfNmGblSngf(uint8 * u1_ap_sngf);

/* DtcEvm : Diagnosis Trouble Code / EVent Mask Control */
void    vd_g_oXDoCANAubIfDtcEvmAct(const uint8 u1_a_EVM);                           /* SID 0x14, 0x85           */
void    vd_g_oXDoCANAubIfDtcEvmDeAct(const uint8 u1_a_EVM);                         /* SID 0x14, 0x85           */

uint8   u1_g_oXDoCANAubIfDtcUdmDel(const uint16 DTCOrigin);
void    vd_g_oXDoCANAubIfUdmEvStsChg(const uint16 u2_a_EVID, const uint8 u1_a_OLD, const uint8 u1_a_NEW);
/*--- security access ---------------------------------------------------------------------------------------------------------------*/
uint8   u1_g_oXDoCANAubIfSaSeed(const uint8 u1_a_ID, const Dcm_OpStatusType OpStatus, uint8 * u1_ap_seed, uint8 * u1_ap_err);  /* SID 0x27 Security Access */
uint8   u1_g_oXDoCANAubIfSaKeyOk(const uint8 u1_a_ID, const uint8 * u1_ap_KEY, uint8 * u1_ap_err);                             /* SID 0x27 Security Access */

uint8   u1_g_oXDoCANAubIfRoeNvmGetErrSt(const uint16 u2_a_BID);
void    vd_g_oXDoCANAubIfRoeNvmWrBlock(const uint16 u2_a_BID);
uint8   u1_g_oXDoCANAubIfRoeChkDidSup(const uint8 *u1_ap_DID);
uint8   u1_g_oXDoCANAubIfRoeChkServToRes(Dcm_NegativeResponseCodeType *u1_ap_ErrorCode);

void    vd_g_oXDoCANAubIfStoreReqData(const uint8 *u1_ap_REQ, const uint32 u4_a_LEN);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif /* OXDOCAN_AUBIF_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  each c files                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/
