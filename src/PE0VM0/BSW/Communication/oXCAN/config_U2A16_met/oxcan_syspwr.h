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
#define OXCAN_SYS_PAR                            (0x0001U)   /* Parking                               */
#define OXCAN_SYS_RID                            (0x0002U)   /* Riding                                */
#define OXCAN_SYS_PON                            (0x0004U)   /* PowerOnNormal                         */
#define OXCAN_SYS_POE                            (0x0008U)   /* PowerOnEmergency                      */

#define OXCAN_SYS_PAR_HV                         (0x0010U)   /* ParkingHighVoltage                    */
#define OXCAN_SYS_PAR_HVHC                       (0x0020U)   /* ParkingHighVoltageAndHeatConditioning */
#define OXCAN_SYS_CHK                            (0x0040U)   /* Checking                              */
#define OXCAN_SYS_PDM                            (0x0080U)   /* Pre-Delivery mode                     */
#define OXCAN_SYS_OTA1                           (0x0100U)   /* OTA Special status No.1               */
#define OXCAN_SYS_OTA2                           (0x0200U)   /* OTA Special status No.2               */
#define OXCAN_SYS_OTA3                           (0x0400U)   /* OTA Special status No.3               */
#define OXCAN_SYS_OTA4                           (0x0800U)   /* OTA Special status No.4               */
#define OXCAN_SYS_WRP                            (0x1000U)   /* Wired reprogramming                   */
#define OXCAN_SYS_EDS                            (0x2000U)   /* Emergency driving stop                */
#define OXCAN_SYS_PAO                            (0x4000U)   /* Power all off                         */

#define OXCAN_SYS_VCAN                           (0x80000000U)  /* VCAN BUS                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* 2nd parameter "u2_a_SYS_CHK" of u1_g_oXCANRxStat                                                                                  */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* System Condition for COM_NO_RX   */
#define OXCAN_RX_SYS_NRX_PAR                     (OXCAN_SYS_PAR)
#define OXCAN_RX_SYS_NRX_RID                     (OXCAN_SYS_RID)
#define OXCAN_RX_SYS_NRX_PON                     (OXCAN_SYS_PON)
#define OXCAN_RX_SYS_NRX_POE                     (OXCAN_SYS_POE)

#define OXCAN_RX_SYS_NRX_PAR_HV                  (OXCAN_SYS_PAR_HV)
#define OXCAN_RX_SYS_NRX_PAR_HVHC                (OXCAN_SYS_PAR_HVHC)
#define OXCAN_RX_SYS_NRX_CHK                     (OXCAN_SYS_CHK)


#define OXCAN_RX_SYS_NRX_VDC                     (0x0040U)    /* Vehicle Drive Control-ON  IG voltage >= 10.5 volt and ST-OFF */
#define OXCAN_RX_SYS_NRX_PTC                     (0x0080U)    /* Power-train Control-ON    IG voltage >= 10.5 volt and IGP-ON */

#define OXCAN_RX_SYS_NRX_ALLSTS                  (0x00ffU)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* System Condition for COM_TIMEOUT */
#define OXCAN_RX_SYS_TOE_PAR                     (0x0100U)    /* Parking-ON                      */
#define OXCAN_RX_SYS_TOE_RID                     (0x0200U)    /* Riding-ON                       */
#define OXCAN_RX_SYS_TOE_PON                     (0x0400U)    /* PowerOnNormal-ON                */
#define OXCAN_RX_SYS_TOE_POE                     (0x0800U)    /* PowerOnEmergency-ON             */

#define OXCAN_RX_SYS_TOE_PAR_HV                  (0x1000U)    /* ParkingHighVoltage -ON          */
#define OXCAN_RX_SYS_TOE_PAR_HVHC                (0x2000U)    /* ParkingHighVoltageAndHeatConditioning-ON */
#define OXCAN_RX_SYS_TOE_CHK                     (0x4000U)    /* Checking-ON                     */

#define OXCAN_RX_SYS_TOE_VDC                     (0x4000U)    /* Vehicle Drive Control-ON  IG voltage >= 10.5 volt and ST-OFF */
#define OXCAN_RX_SYS_TOE_PTC                     (0x8000U)    /* Power-train Control-ON    IG voltage >= 10.5 volt and IGP-ON */

#define OXCAN_RX_SYS_TOE_ALLSTS                  (0xff00U)

#define OXCAN_RX_SYS_NRX_XGR                     (0x00c0U)
#define OXCAN_RX_SYS_TOE_XGR                     (0xc000U)
#define OXCAN_RX_SYS_CHK_XGR                     (0xc0c0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_RX_SYS_LSB_TOE                     (8U)

#define OXCAN_RX_NUM_POM                         (7U)
/* #define OXCAN_RX_POM_PARKING                  (0U)  */
/* #define OXCAN_RX_POM_RIDING                   (1U)  */
/* #define OXCAN_RX_POM_POWONNORMAL              (2U)  */
/* #define OXCAN_RX_POM_POWONEMERGENCY           (3U)  */
/* #define OXCAN_RX_POM_PARK_HIGHVOLT            (4U)  */
/* #define OXCAN_RX_POM_PARK_HIGHVOLT_HEAT       (5U)  */
/* #define OXCAN_RX_POM_CHECKING                 (6U)  */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_OPEMD_NUM_CHK                      (17U)

#define OXCAN_OPEMD_CHK_NM_AWK                   (0U)
#define OXCAN_OPEMD_CHK_PAR                      (1U)    /* Parking                               */
#define OXCAN_OPEMD_CHK_RID_ON                   (2U)    /* Riding                                */
#define OXCAN_OPEMD_CHK_PON_ON                   (3U)    /* PowerOnNormal                         */
#define OXCAN_OPEMD_CHK_POE_ON                   (4U)    /* PowerOnEmergency                      */

#define OXCAN_OPEMD_CHK_PAR_HV                   (5U)    /* ParkingHighVoltage                    */
#define OXCAN_OPEMD_CHK_PAR_HVHC                 (6U)    /* ParkingHighVoltageAndHeatConditioning */
#define OXCAN_OPEMD_CHK_CHK                      (7U)    /* Checking                              */
#define OXCAN_OPEMD_CHK_PDM                      (8U)    /* Pre-Delivery mode                     */
#define OXCAN_OPEMD_CHK_OTA1                     (9U)    /* OTA Special status No.1               */
#define OXCAN_OPEMD_CHK_OTA2                     (10U)   /* OTA Special status No.2               */
#define OXCAN_OPEMD_CHK_OTA3                     (11U)   /* OTA Special status No.3               */
#define OXCAN_OPEMD_CHK_OTA4                     (12U)   /* OTA Special status No.4               */
#define OXCAN_OPEMD_CHK_WRP                      (13U)   /* Wired reprogramming                   */
#define OXCAN_OPEMD_CHK_EDS                      (14U)   /* Emergency driving stop                */
#define OXCAN_OPEMD_CHK_PAO                      (15U)   /* Power all off                         */

#define OXCAN_OPEMD_CHK_VCAN_ON                  (16U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((BswM_CSConf_SysStatusName_PAR      != OXCAN_SYS_PAR               ) || \
     (BswM_CSConf_SysStatusName_RID      != OXCAN_SYS_RID               ) || \
     (BswM_CSConf_SysStatusName_PON      != OXCAN_SYS_PON               ) || \
     (BswM_CSConf_SysStatusName_POE      != OXCAN_SYS_POE               ) || \
     (BswM_CSConf_SysStatusName_PAR_HV   != OXCAN_SYS_PAR_HV            ) || \
     (BswM_CSConf_SysStatusName_PAR_HVHC != OXCAN_SYS_PAR_HVHC          ) || \
     (BswM_CSConf_SysStatusName_CHK      != OXCAN_SYS_CHK               ))
#error "oxcan.c : OXCAN_SYS_XXX shall be compatible with BSWM_CS_SYSSTAT_XXX."
#endif

#if ((OXCAN_RX_SYS_TOE_PAR                   != (OXCAN_RX_SYS_NRX_PAR << OXCAN_RX_SYS_LSB_TOE               )) || \
     (OXCAN_RX_SYS_TOE_RID                   != (OXCAN_RX_SYS_NRX_RID << OXCAN_RX_SYS_LSB_TOE               )) || \
     (OXCAN_RX_SYS_TOE_PON                   != (OXCAN_RX_SYS_NRX_PON << OXCAN_RX_SYS_LSB_TOE               )) || \
     (OXCAN_RX_SYS_TOE_POE                   != (OXCAN_RX_SYS_NRX_POE << OXCAN_RX_SYS_LSB_TOE               )) || \
     (OXCAN_RX_SYS_TOE_PAR_HV                != (OXCAN_RX_SYS_NRX_PAR_HV   << OXCAN_RX_SYS_LSB_TOE          )) || \
     (OXCAN_RX_SYS_TOE_PAR_HVHC              != (OXCAN_RX_SYS_NRX_PAR_HVHC << OXCAN_RX_SYS_LSB_TOE          )) || \
     (OXCAN_RX_SYS_TOE_CHK                   != (OXCAN_RX_SYS_NRX_CHK    << OXCAN_RX_SYS_LSB_TOE            )) || \
     (OXCAN_RX_SYS_TOE_VDC                   != (OXCAN_RX_SYS_NRX_VDC << OXCAN_RX_SYS_LSB_TOE               )) || \
     (OXCAN_RX_SYS_TOE_PTC                   != (OXCAN_RX_SYS_NRX_PTC << OXCAN_RX_SYS_LSB_TOE               )))
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
