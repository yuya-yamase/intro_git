/* PwrCtrl_cfg_private                                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name | PwrCtrl_cfg_private/HEADER                                 */
/*--------------------------------------------------------------------------*/
/* Notes       |                                                            */
/****************************************************************************/
#ifndef PWRCTRL_CFG_H
#define PWRCTRL_CFG_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"

#include <Ecu_Intg.h>
#include <Ecu_IntgHAL.h>
#include "oxcan.h"
#include "gpt_drv_frt.h"
#include "pwm_drv.h"
#include "Dio.h"
#include "Dio_Symbols.h"

#include "EthSW_Task.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* 周期の時間指定(LSB:5ms) */
#define PWRCTRL_CFG_TASK_TIME               (5U)

/* 異常系チェック実行可否定義 */
#define PWRCTRL_CFG_PRIVATE_ERR_CHK         (PWRCTRL_CFG_PRIVATE_ERR_CHK_DISABLE)
#define PWRCTRL_CFG_PRIVATE_ERR_CHK_DISABLE (0U)
#define PWRCTRL_CFG_PRIVATE_ERR_CHK_ENABLE  (1U)

#include "PwrCtrl_Common.h"
#include "PwrCtrl_Main.h"
#include "PwrCtrl_NoRedun.h"
#include "PwrCtrl_Sip.h"
#include "PwrCtrl_Sys.h"

/*--------------------------------------------------------------------------*/
/*  Literal Definitions                                                     */
/*--------------------------------------------------------------------------*/
/* SYS電源制御 Port設定 */
#define     PWRCTRL_CFG_PRIVATE_PORT_BU_DD_MODE             (0)         /* (DIO_ID_APORT0_CH12) */
#define     PWRCTRL_CFG_PRIVATE_PORT_BOOST_DCDC             (1)         /* (DIO_ID_PORT10_CH4)  */
#define     PWRCTRL_CFG_PRIVATE_PORT_ASIL_DCDC              (2)         /* (DIO_ID_APORT0_CH15) */
#define     PWRCTRL_CFG_PRIVATE_PORT_DD_FREQ                (3)         /* (DIO_ID_PORT2_CH6)   */
#define     PWRCTRL_CFG_PRIVATE_PORT_BOOST_ASIL_FREQ        (4)         /* (DIO_ID_PORT21_CH3)  */
#define     PWRCTRL_CFG_PRIVATE_PORT_V33_PERI               (5)         /* (DIO_ID_PORT10_CH2)  */
#define     PWRCTRL_CFG_PRIVATE_PORT_V33_ASIL               (6)         /* (DIO_ID_APORT0_CH13) */
#define     PWRCTRL_CFG_PRIVATE_PORT_V18                    (7)         /* (DIO_ID_APORT1_CH0)  */
#define     PWRCTRL_CFG_PRIVATE_PORT_V18_ASIL               (8)         /* (DIO_ID_APORT0_CH9)  */
#define     PWRCTRL_CFG_PRIVATE_PORT_AUDIO                  (9)         /* (DIO_ID_APORT5_CH0)  */
#define     PWRCTRL_CFG_PRIVATE_PORT_V11_ASIL               (10)        /* (DIO_ID_APORT0_CH11) */
#define     PWRCTRL_CFG_PRIVATE_PORT_EIZO                   (11)        /* (DIO_ID_PORT6_CH11)  */
/* 非冗長電源制御 Port設定 */
#define     PWRCTRL_CFG_PRIVATE_PORT_BOOT                   (12)        /* (DIO_ID_PORT0_CH2)   */
#define     PWRCTRL_CFG_PRIVATE_PORT_MBPWR                  (13)        /* (DIO_ID_PORT22_CH1)  */
#define     PWRCTRL_CFG_PRIVATE_PORT_GVIF_TX_MBWK           (14)        /* (DIO_ID_PORT20_CH9)  */
#define     PWRCTRL_CFG_PRIVATE_PORT_DISP                   (15)        /* (DIO_ID_PORT22_CH2)  */
#define     PWRCTRL_CFG_PRIVATE_PORT_GVIF_TX_DSPWK          (16)        /* (DIO_ID_PORT2_CH0)   */
#define     PWRCTRL_CFG_PRIVATE_PORT_HUB_PWRON              (17)        /* (DIO_ID_PORT4_CH14)  */
#define     PWRCTRL_CFG_PRIVATE_PORT_MCU_PORT_HUB_WK        (18)        /* (DIO_ID_PORT4_CH0)   */
/* デバイスON/OFF制御用 Port設定 */
/* #define     MCU_PORT_V33_PERI               (xxx) */
#define     MCU_PORT_USB_LED_ON             (19)        /* (DIO_ID_APORT0_CH10) */
#define     MCU_PORT_V_IC_RST               (20)        /* (DIO_ID_PORT3_CH3)   */
#define     MCU_PORT_DISP_REQ_GPIO0         (21)        /* (DIO_ID_PORT2_CH2)   */
/* #define     MCU_PORT_AUDIO                  (xxx) */
#define     MCU_PORT_GVIF_CAN_RST           (22)        /* (DIO_ID_PORT10_CH6)  */
#define     MCU_PORT_GVIF_CDISP_RST         (23)        /* (DIO_ID_PORT17_CH4)  */
#define     MCU_PORT_MIC_ON                 (24)        /* (DIO_ID_PORT11_CH13) */
#define     MCU_PORT_AMFM_ANT_ON            (25)        /* (DIO_ID_PORT4_CH8)   */
#define     MCU_PORT_GPS_ANT_ON             (26)        /* (DIO_ID_APORT4_CH2)  */
#define     MCU_PORT_DAB_ANT_ON             (27)        /* (DIO_ID_PORT11_CH4)  */
#define     MCU_PORT_DTV_ANT_ON             (28)        /* (DIO_ID_PORT11_CH4)  */
#define     MCU_PORT_PM_SYS_MUTE            (29)        /* (DIO_ID_PORT20_CH8)  */
#define     MCU_PORT_MOST_WAKE_ON           (30)        /* (DIO_ID_PORT24_CH11) */
#define     MCU_PORT_PIC_POFF               (31)        /* (DIO_ID_PORT11_CH7)  */
#define     MCU_PORT_P_ON                   (32)        /* (DIO_ID_PORT11_CH6)  */
#define     MCU_PORT_XM_ON                  (33)        /* (DIO_ID_APORT4_CH10) */
#define     MCU_PORT_XM_SHDN                (34)        /* (DIO_ID_PORT11_CH4)  */
#define     MCU_PORT_SENSOR_ON              (35)        /* (DIO_ID_PORT8_CH7)   */
#define     MCU_PORT_GPS_RST                (36)        /* (DIO_ID_APORT4_CH8)  */
#define     MCU_PORT_GPS_PMONI              (37)        /* (DIO_ID_PORT6_CH3)   */
#define     MCU_PORT_MM_STBY_N              (38)        /* (DIO_ID_PORT10_CH11) */
#define     MCU_PORT_GPS_PCTL               (39)        /* (DIO_ID_APORT4_CH5)  */
#define     MCU_PORT_BU_DTE                 (40)        /* (DIO_ID_PORT0_CH4)   */
/* SIP電源制御 Port設定 */
#define     PWRCTRL_CFG_PRIVATE_PORT_VB33_SIP               (41)        /* (DIO_ID_APORT5_CH1)  */
#define     PWRCTRL_CFG_PRIVATE_PORT_LOW_POWER              (42)        /* (DIO_ID_PORT10_CH5)  */
#define     PWRCTRL_CFG_PRIVATE_PORT_PM_PWR_EN              (43)        /* (DIO_ID_PORT8_CH2)   */
#define     PWRCTRL_CFG_PRIVATE_PORT_PMIC_FAST_POFF_EN      (44)        /* (DIO_ID_PORT8_CH0)   */
#define     PWRCTRL_CFG_PRIVATE_PORT_MM_OFF_REQ             (45)        /* (DIO_ID_PORT17_CH2)  */
#define     PWRCTRL_CFG_PRIVATE_PORT_POFF_COMPLETE          (46)        /* (DIO_ID_PORT8_CH6)   */
#define     PWRCTRL_CFG_PRIVATE_PORT_MM_SUSPEND_REQ         (47)        /* (DIO_ID_PORT10_CH10) */
#define     PWRCTRL_CFG_PRIVATE_PORT_STR_WAKE               (48)        /* (DIO_ID_PORT22_CH0)  */
#define     PWRCTRL_CFG_PRIVATE_PORT_PMA_PS_HOLD            (49)        /* (DIO_ID_PORT3_CH1)   */
#define     PWRCTRL_CFG_PRIVATE_PORT_SOC_RESOUT             (50)        /* (DIO_ID_PORT8_CH3)   */
#define     PWRCTRL_CFG_PRIVATE_PORT_SAIL_RESOUT            (51)        /* (DIO_ID_PORT8_CH8)   */
#define     PWRCTRL_CFG_PRIVATE_PORT_AOSS_SLP_ENTRY_EXIT    (52)        /* (DIO_ID_PORT17_CH0)  */
#define     PWRCTRL_CFG_PRIVATE_PORT_PM_RESIN               (53)        /* (DIO_ID_PORT8_CH9)   */
#define     MCU_PORT_NUM                    (54)

/*--------------------------------------------------------------------------*/
/*  Variable Externs                                                        */
/*--------------------------------------------------------------------------*/
extern const U2 Mcu_Dio_PortId[MCU_PORT_NUM];

#endif /* PWRCTRL_CFG_H */

/**** End of File ***********************************************************/
