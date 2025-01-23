/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Oem eXtention of CAN Config Header                                                                                               */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  WARNING :                                                                                                                        */
/*  oxcan_syspwr.h is included in oxcan.h                                                                                            */
/*  DO NOT include this file in any file even though this configuration header is public.                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef OXCAN_SYSPWR_H
#define OXCAN_SYSPWR_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_SYSPWR_H_MAJOR                     (1U)
#define OXCAN_SYSPWR_H_MINOR                     (0U)
#define OXCAN_SYSPWR_H_PATCH                     (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_SYS_BAT                            (0x0001U)    /* Battery-ON                                                   */
#define OXCAN_SYS_ACC                            (0x0002U)    /* Accesory-ON                                                  */
#define OXCAN_SYS_IGP                            (0x0004U)    /* Ignition"P"-ON                                               */
#define OXCAN_SYS_PBA                            (0x0008U)    /* +BA-ON                                                       */
#define OXCAN_SYS_IGR                            (0x0010U)    /* Ignition"R"-ON            IG voltage >= 7 volt               */

#define OXCAN_SYS_VCAN                           (0x80000000U)  /* VCAN BUS                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* 2nd parameter "u2_a_SYS_CHK" of u1_g_oXCANRxStat                                                                                  */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* System Condition for COM_NO_RX   */
#define OXCAN_RX_SYS_NRX_BAT                     (OXCAN_SYS_BAT)
#define OXCAN_RX_SYS_NRX_ACC                     (OXCAN_SYS_ACC)
#define OXCAN_RX_SYS_NRX_IGP                     (OXCAN_SYS_IGP)
#define OXCAN_RX_SYS_NRX_PBA                     (OXCAN_SYS_PBA)
#define OXCAN_RX_SYS_NRX_IGR                     (OXCAN_SYS_IGR)

#define OXCAN_RX_SYS_NRX_VDC                     (0x0040U)    /* Vehicle Drive Control-ON  IG voltage >= 10.5 volt and ST-OFF */
#define OXCAN_RX_SYS_NRX_PTC                     (0x0080U)    /* Power-train Control-ON    IG voltage >= 10.5 volt and IGP-ON */

#define OXCAN_RX_SYS_NRX_CHK                     (0x00ffU)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* System Condition for COM_TIMEOUT */
#define OXCAN_RX_SYS_TOE_BAT                     (0x0100U)    /* Battery-ON                                                   */
#define OXCAN_RX_SYS_TOE_ACC                     (0x0200U)    /* Accesory-ON                                                  */
#define OXCAN_RX_SYS_TOE_IGP                     (0x0400U)    /* Ignition"P"-ON                                               */
#define OXCAN_RX_SYS_TOE_PBA                     (0x0800U)    /* +BA-ON                                                       */
#define OXCAN_RX_SYS_TOE_IGR                     (0x1000U)    /* Ignition"R"-ON            IG voltage >= 7 volt               */

#define OXCAN_RX_SYS_TOE_VDC                     (0x4000U)    /* Vehicle Drive Control-ON  IG voltage >= 10.5 volt and ST-OFF */
#define OXCAN_RX_SYS_TOE_PTC                     (0x8000U)    /* Power-train Control-ON    IG voltage >= 10.5 volt and IGP-ON */

#define OXCAN_RX_SYS_TOE_CHK                     (0xff00U)

#define OXCAN_RX_SYS_NRX_XGR                     (0x00c0U)
#define OXCAN_RX_SYS_TOE_XGR                     (0xc000U)
#define OXCAN_RX_SYS_CHK_XGR                     (0xc0c0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_RX_SYS_LSB_TOE                     (8U)

#define OXCAN_RX_NUM_POM                         (6U)
/* #define OXCAN_RX_POM_ACC                      (0U) */
/* #define OXCAN_RX_POM_IGP                      (1U) */
/* #define OXCAN_RX_POM_PBA                      (2U) */
/* #define OXCAN_RX_POM_IGR                      (3U) */
/* #define OXCAN_RX_POM_VDC                      (4U) */
/* #define OXCAN_RX_POM_PTC                      (5U) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_OPEMD_NUM_CHK                      (6U)

#define OXCAN_OPEMD_CHK_NM_AWK                   (0U)
#define OXCAN_OPEMD_CHK_ACC_ON                   (1U)
#define OXCAN_OPEMD_CHK_IGP_ON                   (2U)
#define OXCAN_OPEMD_CHK_PBA_ON                   (3U)
#define OXCAN_OPEMD_CHK_IGR_ON                   (4U)
#define OXCAN_OPEMD_CHK_VCAN_ON                  (5U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((BSWM_CS_SYSSTAT_BAT   != OXCAN_SYS_BAT) || \
     (BSWM_CS_SYSSTAT_ACC   != OXCAN_SYS_ACC) || \
     (BSWM_CS_SYSSTAT_IG    != OXCAN_SYS_IGP) || \
     (BSWM_CS_SYSSTAT_USER1 != OXCAN_SYS_PBA) || \
     (BSWM_CS_SYSSTAT_USER2 != OXCAN_SYS_IGR))
#error "oxcan.c : OXCAN_SYS_XXX shall be compatible with BSWM_CS_SYSSTAT_XXX."
#endif

#if ((OXCAN_RX_SYS_TOE_BAT != (OXCAN_RX_SYS_NRX_BAT << OXCAN_RX_SYS_LSB_TOE)) || \
     (OXCAN_RX_SYS_TOE_ACC != (OXCAN_RX_SYS_NRX_ACC << OXCAN_RX_SYS_LSB_TOE)) || \
     (OXCAN_RX_SYS_TOE_IGP != (OXCAN_RX_SYS_NRX_IGP << OXCAN_RX_SYS_LSB_TOE)) || \
     (OXCAN_RX_SYS_TOE_PBA != (OXCAN_RX_SYS_NRX_PBA << OXCAN_RX_SYS_LSB_TOE)) || \
     (OXCAN_RX_SYS_TOE_IGR != (OXCAN_RX_SYS_NRX_IGR << OXCAN_RX_SYS_LSB_TOE)) || \
     (OXCAN_RX_SYS_TOE_VDC != (OXCAN_RX_SYS_NRX_VDC << OXCAN_RX_SYS_LSB_TOE)) || \
     (OXCAN_RX_SYS_TOE_PTC != (OXCAN_RX_SYS_NRX_PTC << OXCAN_RX_SYS_LSB_TOE)))
#error "oxcan_rx.c : OXCAN_RX_SYS_TOE_XXX shall be equal to (OXCAN_RX_SYS_NRX_XXX << 8)."
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif /* OXCAN_SYSPWR_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see  oxcan_cfg.c and oxcan_rx_cfg.c                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/
