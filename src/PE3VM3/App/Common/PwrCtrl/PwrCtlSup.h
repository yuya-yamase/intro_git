/* サンプルコード */

/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
#ifndef PWRCTLSUP_H
#define PWRCTLSUP_H
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"

#include "Dio.h"
#include "oxcan.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Power Mode State */
#define POWER_MODE_STATE_NUM                        (4U)
#define POWER_MODE_STATE_PARK                       (0U)        /* 0 : Parking  */
#define POWER_MODE_STATE_APPOFF                     (1U)        /* 1 : Display Off */
#define POWER_MODE_STATE_APPON                      (2U)        /* 2 : Display On */
#define POWER_MODE_STATE_EDS                        (3U)        /* 3 : EDS */
#define POWER_MODE_STATE_STANDBY                    (4U)        /* 4 : Standby 仮状態 */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define POWER_IO_STS_LOW                            (STD_LOW)
#define POWER_IO_STS_HIGH                           (STD_HIGH)

#define u1_POWER_GET_BOOT()                         ((U1)Dio_ReadChannel((Dio_ChannelType)DIO_ID_PORT0_CH2))    /* 暫定 量産時削除 */

#define vd_POWER_GET_VPSINFO1(x)                    ((void)Com_ReceiveSignal(ComConf_ComSignal_VPSINFO1, (x)))
#define vd_POWER_GET_VPSINFO2(x)                    ((void)Com_ReceiveSignal(ComConf_ComSignal_VPSINFO2, (x)))
#define vd_POWER_GET_VPSINFO3(x)                    ((void)Com_ReceiveSignal(ComConf_ComSignal_VPSINFO3, (x)))
#define vd_POWER_GET_VPSINFO4(x)                    ((void)Com_ReceiveSignal(ComConf_ComSignal_VPSINFO4, (x)))
#define vd_POWER_GET_VPSINFO5(x)                    ((void)Com_ReceiveSignal(ComConf_ComSignal_VPSINFO5, (x)))
#define vd_POWER_GET_VPSINFO6(x)                    ((void)Com_ReceiveSignal(ComConf_ComSignal_VPSINFO6, (x)))
#define vd_POWER_GET_VPSINFO7(x)                    ((void)Com_ReceiveSignal(ComConf_ComSignal_VPSINFO7, (x)))
#define vd_POWER_GET_VPSINFOS(x)                    ((void)Com_ReceiveSignal(ComConf_ComSignal_VPSINFOS, (x)))
#define vd_POWER_GET_APOFRQ(x)                      ((void)Com_ReceiveSignal(ComConf_ComSignal_APOFRQ, (x)))
#define vd_POWER_GET_PWRERRST(x)                    ((void)Com_ReceiveSignal(ComConf_ComSignal_PWRERRST, (x)))

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void    vd_g_PowerSup_BonInit(void);
void    vd_g_PowerSup_WkupInit(void);
void    vd_g_PowerSup_Routine(void);
U1      u1_g_PowerSup_ModeState(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif      /* PWRCTLSUP_H */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  PwrCtl.c                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/