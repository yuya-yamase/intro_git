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
#define OXDC_SECURITY_ID03                       (3U)
#define OXDC_SECURITY_ID04                       (4U)
#define OXDC_SECURITY_ID05                       (5U)
#define OXDC_SECURITY_ID06                       (6U)
#define OXDC_SECURITY_ID07                       (7U)
#define OXDC_SECURITY_ID08                       (8U)
#define OXDC_SECURITY_ID09                       (9U)
#define OXDC_SECURITY_ID10                       (10U)
#define OXDC_SECURITY_ID11                       (11U)
#define OXDC_SECURITY_ID12                       (12U)
#define OXDC_SECURITY_ID13                       (13U)
#define OXDC_SECURITY_ID14                       (14U)
#define OXDC_SECURITY_ID15                       (15U)
#define OXDC_SECURITY_ID16                       (16U)
#define OXDC_SECURITY_ID17                       (17U)
#define OXDC_SECURITY_ID18                       (18U)
#define OXDC_SECURITY_ID19                       (19U)
#define OXDC_SECURITY_ID20                       (20U)
#define OXDC_SECURITY_ID21                       (21U)
#define OXDC_SECURITY_ID22                       (22U)
#define OXDC_SECURITY_ID23                       (23U)
#define OXDC_SECURITY_ID24                       (24U)
#define OXDC_SECURITY_ID25                       (25U)
#define OXDC_SECURITY_ID26                       (26U)
#define OXDC_SECURITY_ID27                       (27U)
#define OXDC_SECURITY_ID28                       (28U)
#define OXDC_SECURITY_ID29                       (29U)
#define OXDC_SECURITY_ID30                       (30U)
#define OXDC_SECURITY_ID31                       (31U)
#define OXDC_SECURITY_ID32                       (32U)
#define OXDC_SECURITY_ID33                       (33U)
#define OXDC_SECURITY_ID34                       (34U)
#define OXDC_SECURITY_ID35                       (35U)
#define OXDC_SECURITY_ID36                       (36U)
#define OXDC_SECURITY_ID37                       (37U)
#define OXDC_SECURITY_ID38                       (38U)
#define OXDC_SECURITY_ID39                       (39U)
#define OXDC_SECURITY_ID40                       (40U)
#define OXDC_SECURITY_ID41                       (41U)
#define OXDC_SECURITY_ID42                       (42U)
#define OXDC_SECURITY_ID43                       (43U)
#define OXDC_SECURITY_ID44                       (44U)
#define OXDC_SECURITY_ID45                       (45U)
#define OXDC_SECURITY_ID46                       (46U)
#define OXDC_SECURITY_ID47                       (47U)
#define OXDC_SECURITY_ID48                       (48U)
#define OXDC_SECURITY_ID49                       (49U)
#define OXDC_SECURITY_ID50                       (50U)
#define OXDC_SECURITY_ID51                       (51U)
#define OXDC_SECURITY_ID52                       (52U)
#define OXDC_SECURITY_ID53                       (53U)
#define OXDC_SECURITY_ID54                       (54U)
#define OXDC_SECURITY_ID55                       (55U)
#define OXDC_SECURITY_ID56                       (56U)
#define OXDC_SECURITY_ID57                       (57U)
#define OXDC_SECURITY_ID58                       (58U)
#define OXDC_SECURITY_ID59                       (59U)
#define OXDC_SECURITY_ID60                       (60U)
#define OXDC_SECURITY_ID61                       (61U)
#define OXDC_SECURITY_ID62                       (62U)
#define OXDC_SECURITY_ID63                       (63U)

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
#ifdef OXDC_FUNC_RPG_RESET
void    vd_g_oXDoCANAubIfRpgSwReset(void);
#endif

void    vd_g_oXDoCANCfgSesChange(const uint8 u1_a_OLD, const uint8 u1_a_NEW);
#if(OXDC_SID10_NR_22_USE == OXDC_USE)
uint8   u1_g_oXDoCANSessionChangeChk(const uint8 u1_a_SUB);
#endif

#if(OXDC_SID28_NR_22_USE == OXDC_USE)
uint8   u1_g_oXDoCANComCtrlChk(uint8 * u1_ap_err);
#endif

/*--- dtc ---------------------------------------------------------------------------------------------------------------------------*/
uint8   u1_g_oXDoCANAubIfDtcNvmWrStat(const uint16 u2_a_BID);
void    vd_g_oXDoCANAubIfDtcNvmWrBlock(const uint16 u2_a_BID, const uint8 * u1_ap_SRC);
#if (DEM_READFUNC_MONITORDATA_SUPPORT == STD_ON)
uint8   u1_g_oXDoCANAubIfTripcnt(uint8 * u1_ap_tripcnt, Dem_MonitorDataType u4_a_mon);
uint8   u1_g_oXDoCANAubIfOdo(uint8 * u1_ap_odo, Dem_MonitorDataType u4_a_mon);
uint8   u1_g_oXDoCANAubIfGmt(uint8 * u1_ap_gmt, Dem_MonitorDataType u4_a_mon);
uint8   u1_g_oXDoCANAubIfNmWkf(uint8 * u1_ap_wkf, Dem_MonitorDataType u4_a_mon);
uint8   u1_g_oXDoCANAubIfNmSngf(uint8 * u1_ap_sngf, Dem_MonitorDataType u4_a_mon);
uint8   u1_g_oXDoCANAubIfEcuWkf(uint8 * u1_ap_wkf, Dem_MonitorDataType u4_a_mon);
uint8   u1_g_oXDoCANAubIfEcuSngf(uint8 * u1_ap_sngf, Dem_MonitorDataType u4_a_mon);
uint8   u1_g_oXDoCANAubIfNmGblWkf(uint8 * u1_ap_wkf, Dem_MonitorDataType u4_a_mon);
uint8   u1_g_oXDoCANAubIfNmGblSngf(uint8 * u1_ap_sngf, Dem_MonitorDataType u4_a_mon);
uint8   u1_g_oXDoCANAubIfMaCanId(uint8 * u1_ap_canid, Dem_MonitorDataType u4_a_mon);
uint8   u1_g_oXDoCANAubIfMacUVHst(uint8 * u1_ap_macuv, Dem_MonitorDataType u4_a_mon);
#else
uint8   u1_g_oXDoCANAubIfTripcnt(uint8 * u1_ap_tripcnt);
uint8   u1_g_oXDoCANAubIfOdo(uint8 * u1_ap_odo);
uint8   u1_g_oXDoCANAubIfGmt(uint8 * u1_ap_gmt);
uint8   u1_g_oXDoCANAubIfNmWkf(uint8 * u1_ap_wkf);
uint8   u1_g_oXDoCANAubIfNmSngf(uint8 * u1_ap_sngf);
uint8   u1_g_oXDoCANAubIfEcuWkf(uint8 * u1_ap_wkf);
uint8   u1_g_oXDoCANAubIfEcuSngf(uint8 * u1_ap_sngf);
uint8   u1_g_oXDoCANAubIfNmGblWkf(uint8 * u1_ap_wkf);
uint8   u1_g_oXDoCANAubIfNmGblSngf(uint8 * u1_ap_sngf);
#endif

/* DtcEvm : Diagnosis Trouble Code / EVent Mask Control */
void    vd_g_oXDoCANAubIfDtcEvmAct(const uint8 u1_a_EVM);                           /* SID 0x14, 0x85           */
void    vd_g_oXDoCANAubIfDtcEvmDeAct(const uint8 u1_a_EVM);                         /* SID 0x14, 0x85           */

#if(OXDC_SID85_NR_22_USE == OXDC_USE)
uint8   u1_g_oXDoCANCtrlDTCChk(void);
#endif
#if(OXDC_SID14_NR_22_USE == OXDC_USE)
uint8   u1_g_oXDoCANClearDTCChk(void);
#endif
uint8   u1_g_oXDoCANAubIfDtcUdmDel(const uint16 DTCOrigin);
void    vd_g_oXDoCANAubIfUdmEvStsChg(const uint16 u2_a_EVID, const uint8 u1_a_OLD, const uint8 u1_a_NEW);
/*--- security access ---------------------------------------------------------------------------------------------------------------*/
uint8   u1_g_oXDoCANAubIfSaSeed(const uint8 u1_a_ID, const Dcm_OpStatusType OpStatus, uint8 * u1_ap_seed, uint8 * u1_ap_err);  /* SID 0x27 Security Access */
uint8   u1_g_oXDoCANAubIfSaKeyOk(const uint8 u1_a_ID, const uint8 * u1_ap_KEY, uint8 * u1_ap_err);                             /* SID 0x27 Security Access */

#if(OXDC_SID86_USE == OXDC_USE)
uint8   u1_g_oXDoCANAubIfRoeNvmGetErrSt(const uint16 u2_a_BID);
void    vd_g_oXDoCANAubIfRoeNvmWrBlock(const uint16 u2_a_BID);
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif /* OXDOCAN_AUBIF_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  each c files                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/
