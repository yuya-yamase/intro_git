/* 1.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Diagnosis on Can for Toyota MET/HUD based on AUBIST/DEM, DCM                                                                     */
/*  SID 0xBA ECU Shipping Inspection                                                                                                 */
/*===================================================================================================================================*/

#ifndef TYDOCAN_MET_ESI_CFG_H
#define TYDOCAN_MET_ESI_CFG_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDOCAN_MET_ESI_CFG_H_MAJOR              (1)
#define TYDOCAN_MET_ESI_CFG_H_MINOR              (1)
#define TYDOCAN_MET_ESI_CFG_H_PATCH              (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "tydocan_sal.h"
#include "oxdocan_saif.h"
#include "tydocan_util.h"
#include "tydocan_nvmif.h"
#include "tydocan_met_esi.h"

/* #include "lcom_spi_dsal.h" */

#include "es_inspect.h"
#include "esi_iotest.h"
#include "esi_memtest.h"
#include "esi_nvmr.h"

#include "odo_km.h"
#include "odo_nvmif.h"
#include "tripcom.h"
#include "locale.h"
#include "unitconvrt.h"

#include "nvmc_mgr.h"

#include "vardef.h"
#include "product.h"

#include "thblnkr.h"

/* Fcl */
#include "int_drv.h"
#include "r_typedefs.h"
#include "fcl_cfg.h"
#include "fcl_ctrl.h"
#include "r_fcl_types.h"
#include "r_fcl.h"
#include "target.h"
#include "fcl_descriptor.h"
#include "fcl_user.h"

#include "wdg_m.h"
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_MET_ESI_TRX_B0                      (0U)
#define TYDC_MET_ESI_TRX_B1                      (1U)
#define TYDC_MET_ESI_TRX_B2                      (2U)
#define TYDC_MET_ESI_TRX_B3                      (3U)
#define TYDC_MET_ESI_TRX_B4                      (4U)
#define TYDC_MET_ESI_TRX_B5                      (5U)
#define TYDC_MET_ESI_TRX_B6                      (6U)
#define TYDC_MET_ESI_TRX_B7                      (7U)

#define TYDC_MET_ESI_LSB_B3                      (24U)
#define TYDC_MET_ESI_LSB_B2                      (16U)
#define TYDC_MET_ESI_LSB_B1                      (8U)

#define TYDC_MET_ESI_ANS_11                      (0x51U)
#define TYDC_MET_ESI_ANS_22                      (0x62U)
#define TYDC_MET_ESI_ANS_2E                      (0x6EU)
#define TYDC_MET_ESI_ANS_2F                      (0x6FU)
#define TYDC_MET_ESI_ANS_AB                      (0xEBU)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_MET_ESI_VER_B00_OP_3                (0U)
#define TYDC_MET_ESI_VER_B01_OP_2                (1U)
#define TYDC_MET_ESI_VER_B02_OP_1                (2U)
#define TYDC_MET_ESI_VER_B03_OP_0                (3U)
#define TYDC_MET_ESI_VER_B04_D1_0                (4U)
/* #define TYDC_MET_ESI_VER_B05_D1_1                (5U) */
#define TYDC_MET_ESI_VER_B06_GF_0                (6U)
#define TYDC_MET_ESI_VER_B07_GF_1                (7U)
#define TYDC_MET_ESI_VER_B08_GF_2                (8U)
/* #define TYDC_MET_ESI_VER_B09_GF_3                (9U) */
#define TYDC_MET_ESI_VER_B10_DEV                 (10U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_MET_ESI_NVM_RES_PAS                 (0xF5U)
#define TYDC_MET_ESI_NVM_RES_FAI                 (0xFAU)
#define TYDC_MET_ESI_NVM_RES_RUN                 (0xF0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_MET_ESI_NUM_MEM                     (0x45U)

#define TYDC_MET_ESI_MEM_FS_MA_CA                (0x02U)  /* Fuel Sensor A/D 10 bits / Main : Power Calbirated */
#define TYDC_MET_ESI_MEM_FS_MA_PS                (0x03U)  /* Fuel Sensor A/D 10 bits / Main : Power Supply     */
#define TYDC_MET_ESI_MEM_FS_MA_RA                (0x04U)  /* Fuel sensor A/D 10 bits / Main : rolling averaged */
#define TYDC_MET_ESI_MEM_UB_DIM                  (0x06U)  /* User Button A/D 10 bits        : Dimmer           */
#define TYDC_MET_ESI_MEM_FU_LI                   (0x0EU)  /* Fuel Lid Digital Input Hi/Low                     */
#define TYDC_MET_ESI_MEM_FLAS_PS                 (0x13U)  /* Flasher Power Supply A/D 10 bits                  */
#define TYDC_MET_ESI_MEM_TUR_FL                  (0x14U)  /* TURN A/D 10 bits               : Front Left       */
#define TYDC_MET_ESI_MEM_TUR_FR                  (0x15U)  /* TURN A/D 10 bits               : Front Right      */
#define TYDC_MET_ESI_MEM_TUR_RL                  (0x16U)  /* TURN A/D 10 bits               : Rear  Left       */
#define TYDC_MET_ESI_MEM_TUR_RR                  (0x17U)  /* TURN A/D 10 bits               : Rear  Right      */
#define TYDC_MET_ESI_MEM_UB_STE_1                (0x18U)  /* User Button A/D 10 bits        : Steering Switch  */
#define TYDC_MET_ESI_MEM_UB_STE_2                (0x19U)  /* User Button A/D 10 bits        : Steering Switch  */
#define TYDC_MET_ESI_MEM_FS_SU_CA                (0x22U)  /* Fuel Sensor A/D 10 bits / Sub  : Power Calbirated */
#define TYDC_MET_ESI_MEM_FS_SU_BA                (0x23U)  /* Fuel Sensor A/D 10 bits / Sub  : Power Supply     */
#define TYDC_MET_ESI_MEM_CXPI_RX                 (0x31U)  /* CXPI Receive Check                                */
#define TYDC_MET_ESI_MEM_SWB_MONI                (0x39U)  /* SWB voltage Monitor                               */
#define TYDC_MET_ESI_MEM_STOP_LAMP               (0x3AU)  /* STOP LAMP                                         */
#define TYDC_MET_ESI_MEM_INTP3                   (0x3FU)  /* INTP3 Digital Input Hi/Low                        */
#define TYDC_MET_ESI_MEM_OT_CHK                  (0x40U)  /* Odo/Trip Check                                    */
#define TYDC_MET_ESI_MEM_RCAR_TEMP               (0x41U)  /* R-Car Temperature                                 */
#define TYDC_MET_ESI_MEM_WTSW                    (0x42U)  /* WTSW                                              */
#define TYDC_MET_ESI_MEM_HUD_SW                  (0x43U)  /* HUD_SW                                            */
#define TYDC_MET_ESI_MEM_BRAKE_PAD               (0x44U)  /* BRAKE PAD                                         */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_MET_ESI_ETHR_RW_NB_RX               (3U)
#define TYDC_MET_ESI_ETHR_RW_OK                  (0x55U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* NvM Read/Write by Identifier */
#define TYDC_MET_ESI_NVM_0000                    (0x0000U)
#define TYDC_MET_ESI_NVM_0005                    (0x0005U)
#define TYDC_MET_ESI_NVM_0006                    (0x0006U)
#define TYDC_MET_ESI_NVM_0007                    (0x0007U)
#define TYDC_MET_ESI_NVM_0008                    (0x0008U)
#define TYDC_MET_ESI_NVM_0009                    (0x0009U)
#define TYDC_MET_ESI_NVM_000A                    (0x000AU)
#define TYDC_MET_ESI_NVM_000B                    (0x000BU)
#define TYDC_MET_ESI_NVM_000C                    (0x000CU)
#define TYDC_MET_ESI_NVM_000D                    (0x000DU)
#define TYDC_MET_ESI_NVM_000E                    (0x000EU)
#define TYDC_MET_ESI_NVM_000F                    (0x000FU)
#define TYDC_MET_ESI_NVM_0010                    (0x0010U)
#define TYDC_MET_ESI_NVM_0011                    (0x0011U)
#define TYDC_MET_ESI_NVM_0012                    (0x0012U)
#define TYDC_MET_ESI_NVM_0013                    (0x0013U)
#define TYDC_MET_ESI_NVM_0014                    (0x0014U)
#define TYDC_MET_ESI_NVM_0015                    (0x0015U)
#define TYDC_MET_ESI_NVM_0016                    (0x0016U)
#define TYDC_MET_ESI_NVM_0017                    (0x0017U)
#define TYDC_MET_ESI_NVM_0018                    (0x0018U)
#define TYDC_MET_ESI_NVM_0019                    (0x0019U)
#define TYDC_MET_ESI_NVM_001A                    (0x001AU)
#define TYDC_MET_ESI_NVM_001B                    (0x001BU)
#define TYDC_MET_ESI_NVM_001C                    (0x001CU)
#define TYDC_MET_ESI_NVM_001D                    (0x001DU)
#define TYDC_MET_ESI_NVM_001E                    (0x001EU)
#define TYDC_MET_ESI_NVM_001F                    (0x001FU)
#define TYDC_MET_ESI_NVM_0020                    (0x0020U)
#define TYDC_MET_ESI_NVM_0021                    (0x0021U)
#define TYDC_MET_ESI_NVM_0022                    (0x0022U)
#define TYDC_MET_ESI_NVM_0023                    (0x0023U)
#define TYDC_MET_ESI_NVM_0024                    (0x0024U)
#define TYDC_MET_ESI_NVM_0025                    (0x0025U)
#define TYDC_MET_ESI_NVM_0026                    (0x0026U)

#define TYDC_MET_ESI_NVM_NUM                     (0x0027U)

#define TYDC_MET_ESI_NVM_0100                    (0x0100U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void      vd_g_TyDoCANMetEsi_ClrNVMWoDTF(void);
U1        u1_g_TyDoCANMetEsi_ReadStsNVMWoDTF(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern U2 ( * const fp_gp_u2_TYDC_ESI_MEM[TYDC_MET_ESI_NUM_MEM])(void);
#endif      /* TYDOCAN_MET_ESI_CFG_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  tydocan_met_esi.c                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
