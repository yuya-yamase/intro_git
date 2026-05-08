/* 0.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO TECHNO Corporation                                                                                               */
/*===================================================================================================================================*/
/*  Transmission and reception processing of subframe 4 in XSPI communication.                                                       */
/*  Handled data: CAN Data/Repro/LCAN Data                                                                                           */
/*===================================================================================================================================*/

#ifndef XSPI_IVI_SUB1_POWER_H
#define XSPI_IVI_SUB1_POWER_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define XSPI_IVI_SUB1_POWER_H_MAJOR           (0)
#define XSPI_IVI_SUB1_POWER_H_MINOR           (1)
#define XSPI_IVI_SUB1_POWER_H_PATCH           (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define    XSPI_IVI_POWER_DEV_INI_NUM           (5U)
#define    XSPI_IVI_POWER_EIZO_INI              (0U)
#define    XSPI_IVI_POWER_GVIFRECV_INI          (1U)
#define    XSPI_IVI_POWER_GVIFSEND_INI          (2U)
#define    XSPI_IVI_POWER_GYRO_INI              (3U)
#define    XSPI_IVI_POWER_POWER_INI             (4U)

#define     XSPI_IVI_POWER_RESET_COMP_CAMERA    (0x01U)
#define     XSPI_IVI_POWER_RESET_COMP_DIAGCAN   (0x02U)
#define     XSPI_IVI_POWER_RESET_COMP_GYRO      (0x04U)
#define     XSPI_IVI_POWER_RESET_COMP_CAN       (0x08U)
#define     XSPI_IVI_POWER_RESET_COMP_CLOCK     (0x10U)
#define     XSPI_IVI_POWER_RESET_COMP_DTCROB    (0x20U)
#define     XSPI_IVI_POWER_RESET_COMP_RARNM     (0x40U)

#define    XSPI_IVI_POWER_01_BUFSIZ             (6U)    /* 電源状態通知 バッファサイズ */
#define    XSPI_IVI_POWER_01_BYTE2              (0U)    /* 基本ステート */
#define    XSPI_IVI_POWER_01_BYTE3              (1U)    /* 特殊ステート */
#define    XSPI_IVI_POWER_01_BYTE4              (2U)    /* OTA特殊ステート */
#define    XSPI_IVI_POWER_01_BYTE5              (3U)    /* 見た目状態 */
#define    XSPI_IVI_POWER_01_BYTE6              (4U)    /* 車両電源(特殊)ステート遷移中フラグ */
#define    XSPI_IVI_POWER_01_BYTE7              (5U)    /* 途絶状態 */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void            vd_g_XspiIviSub1PowerInit(void);
void            vd_g_XspiIviSub1PowerMainTask(void);
void            vd_g_XspiIviSub1PowerResetRoutine(void);
void            vd_g_XspiIviSub1PowerGetSts(U1* u1_ap_data);
void            vd_g_XspiIviSub1PowerAna(const U1 * u1_ap_XSPI_ADD, const U2 u2_a_data_size);
void            vd_g_XspiIviSub1_PowerState1stSend(void);
void            vd_g_XspiIviSub1DevInitFinish(void);
void            vd_g_XspiIviSub1PowerDevInitCmpApp(const U1 u1_a_ID);
void            vd_g_XspiIviSub1PowerBmoniVolSend(void);
void            vd_g_XspiIviSub1PowerBootLogResSend(const U1 * u1_ap_DATA);
void            vd_g_XspiIviSub1PowerVMResetComp(const U1 u1_a_ID);
void            vd_g_XspiIviSub1PowerCDCResetComp(const U1 u1_a_ID);
void            vd_g_XspiIviSub1PowerSoCBootRec(void);
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#endif /* XSPI_IVI_SUB1_POWER_H */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  x_spi_ivi_sub1_control.c                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/
