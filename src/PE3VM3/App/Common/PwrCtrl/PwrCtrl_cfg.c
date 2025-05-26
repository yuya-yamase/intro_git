/* PwrCtrl_Cfg_c_v1-0-0                                                  */
/****************************************************************************/
/* Copyright (C) 2023 Denso Co.,Ltd. All rights reserved.                   */
/****************************************************************************/

/****************************************************************************/
/* Object Name | PwrCtrl_Common/CODE                                        */
/*--------------------------------------------------------------------------*/
/* Notes       |                                                            */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "PwrCtrl_cfg_private.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
const U2 Mcu_Dio_PortId[MCU_PORT_NUM] = {
/* SYS電源制御 Port設定 */
    DIO_ID_APORT0_CH12,
    DIO_ID_PORT10_CH4,
    DIO_ID_APORT0_CH15,
    DIO_ID_PORT2_CH6,
    DIO_ID_PORT21_CH3,
    DIO_ID_PORT10_CH2,
    DIO_ID_APORT0_CH13,
    DIO_ID_APORT1_CH0,
    DIO_ID_APORT0_CH9,
    DIO_ID_APORT5_CH0,
    DIO_ID_APORT0_CH11,
    DIO_ID_PORT6_CH11,
/* 非冗長電源制御 Port設定 */
    DIO_ID_PORT0_CH2,
    DIO_ID_PORT22_CH1,
    DIO_ID_PORT20_CH9,
    DIO_ID_PORT22_CH2,
    DIO_ID_PORT2_CH0,
    DIO_ID_PORT4_CH14,
    DIO_ID_PORT4_CH0,
/* デバイスON/OFF制御用 Port設定 */
    DIO_ID_APORT0_CH10,
    DIO_ID_PORT3_CH3,
    DIO_ID_PORT2_CH2,
    DIO_ID_PORT10_CH6,
    DIO_ID_PORT17_CH4,
    DIO_ID_PORT11_CH13,
    DIO_ID_PORT4_CH8,
    DIO_ID_APORT4_CH2,
    DIO_ID_PORT11_CH4,
    DIO_ID_PORT11_CH4,
    DIO_ID_PORT20_CH8,
    DIO_ID_PORT24_CH11,
    DIO_ID_PORT11_CH7,
    DIO_ID_PORT11_CH6,
    DIO_ID_APORT4_CH10,
    DIO_ID_PORT11_CH4,
    DIO_ID_PORT8_CH7,
    DIO_ID_APORT4_CH8,
    DIO_ID_PORT6_CH3,
    DIO_ID_PORT10_CH11,
    DIO_ID_APORT4_CH5,
    DIO_ID_PORT0_CH4,
/* SIP電源制御 Port設定 */
    DIO_ID_APORT5_CH1,
    DIO_ID_PORT10_CH5,
    DIO_ID_PORT8_CH2,
    DIO_ID_PORT8_CH0,
    DIO_ID_PORT17_CH2,
    DIO_ID_PORT8_CH6,
    DIO_ID_PORT10_CH10,
    DIO_ID_PORT22_CH0,
    DIO_ID_PORT3_CH1,
    DIO_ID_PORT8_CH3,
    DIO_ID_PORT8_CH8,
    DIO_ID_PORT17_CH0,
    DIO_ID_PORT8_CH9,
};

/*--------------------------------------------------------------------------*/
/* Functions                                                                */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* Service API                                                              */
/****************************************************************************/
/**** End of File ***********************************************************/
