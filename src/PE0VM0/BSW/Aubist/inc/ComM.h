/* comm_h_v2-2-0                                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | COMM/HEADER                                               */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_COMM_AR_H
#define BSW_COMM_AR_H

#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>
#include <ComStack_Types.h>
#include <comm/bsw_comm_public.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/*--------------------------------------*/
/* Unit:ctrl                            */
/*--------------------------------------*/
/* ComM Initialization State */
#define COMM_UNINIT                             (BSW_COMM_UNINIT)
#define COMM_INIT                               (BSW_COMM_INIT)

/* ComM Mode */
#define COMM_NO_COMMUNICATION                   (BSW_COMM_NO_COMMUNICATION)
#define COMM_SILENT_COMMUNICATION               (BSW_COMM_SILENT_COMMUNICATION)
#define COMM_FULL_COMMUNICATION                 (BSW_COMM_FULL_COMMUNICATION)
#define COMM_FULL_COMMUNICATION_WITH_WAKEUP_REQUEST     (BSW_COMM_FULL_COM_WITH_WKUP_REQ)

/* ComM State */
#define COMM_NO_COM_NO_PENDING_REQUEST          (BSW_COMM_NO_COM_NO_PENDING_REQUEST)
#define COMM_NO_COM_REQUEST_PENDING             (BSW_COMM_NO_COM_REQUEST_PENDING)
#define COMM_FULL_COM_NETWORK_REQUESTED         (BSW_COMM_FULL_COM_NETWORK_REQUESTED)
#define COMM_FULL_COM_READY_SLEEP               (BSW_COMM_FULL_COM_READY_SLEEP)
#define COMM_SILENT_COM                         (BSW_COMM_SILENT_COM)
#define COMM_INVALID_COM                        (BSW_COMM_INVALID_COM)

/* ComM PNC State */
#define COMM_PNC_REQUESTED                      (BSW_COMM_PNC_REQUESTED)
#define COMM_PNC_READY_SLEEP                    (BSW_COMM_PNC_READY_SLEEP)
#define COMM_PNC_PREPARE_SLEEP                  (BSW_COMM_PNC_PREPARE_SLEEP)
#define COMM_PNC_NO_COMMUNICATION               (BSW_COMM_PNC_NO_COMMUNICATION)

/* Channel Power Supply Judgment */
#define COMM_PWSUPPLY_OFF                       (BSW_COMM_PWSUPPLY_OFF)
#define COMM_PWSUPPLY_ON                        (BSW_COMM_PWSUPPLY_ON)

/* Channel Driving State */
#define COMM_DRVST_STOP                         (BSW_COMM_DRVST_STOP)
#define COMM_DRVST_START                        (BSW_COMM_DRVST_START)

/* Power Supply State */
#define COMM_PWSTAT_NONE                        (BSW_COMM_PWSTAT_NONE)
#define COMM_PWSTAT_BAT                         (BSW_COMM_PWSTAT_BAT)
#define COMM_PWSTAT_ACC                         (BSW_COMM_PWSTAT_ACC)
#define COMM_PWSTAT_IG                          (BSW_COMM_PWSTAT_IG)
#define COMM_PWSTAT_USER1                       (BSW_COMM_PWSTAT_USER1)
#define COMM_PWSTAT_USER2                       (BSW_COMM_PWSTAT_USER2)
#define COMM_PWSTAT_USER3                       (BSW_COMM_PWSTAT_USER3)
#define COMM_PWSTAT_USER4                       (BSW_COMM_PWSTAT_USER4)
#define COMM_PWSTAT_USER5                       (BSW_COMM_PWSTAT_USER5)

/* User Handle */
#define COMM_USERHANDLE_PW_BAT                  (BSW_COMM_USERHANDLE_PW_BAT)
#define COMM_USERHANDLE_PW_ACC                  (BSW_COMM_USERHANDLE_PW_ACC)
#define COMM_USERHANDLE_PW_IG                   (BSW_COMM_USERHANDLE_PW_IG)
#define COMM_USERHANDLE_PW_USR1                 (BSW_COMM_USERHANDLE_PW_USR1)
#define COMM_USERHANDLE_PW_USR2                 (BSW_COMM_USERHANDLE_PW_USR2)
#define COMM_USERHANDLE_PW_USR3                 (BSW_COMM_USERHANDLE_PW_USR3)
#define COMM_USERHANDLE_PW_USR4                 (BSW_COMM_USERHANDLE_PW_USR4)
#define COMM_USERHANDLE_PW_USR5                 (BSW_COMM_USERHANDLE_PW_USR5)
#define COMM_USERHANDLE_USRAWK1                 (BSW_COMM_USERHANDLE_USRAWK1)
#define COMM_USERHANDLE_USRAWK2                 (BSW_COMM_USERHANDLE_USRAWK2)
#define COMM_USERHANDLE_USRAWK3                 (BSW_COMM_USERHANDLE_USRAWK3)
#define COMM_USERHANDLE_USRAWK4                 (BSW_COMM_USERHANDLE_USRAWK4)
#define COMM_USERHANDLE_USRAWK5                 (BSW_COMM_USERHANDLE_USRAWK5)
#define COMM_USERHANDLE_USRAWK6                 (BSW_COMM_USERHANDLE_USRAWK6)
#define COMM_USERHANDLE_USRAWK7                 (BSW_COMM_USERHANDLE_USRAWK7)
#define COMM_USERHANDLE_USRAWK8                 (BSW_COMM_USERHANDLE_USRAWK8)

#define COMM_USERHANDLE_PNCUSER0                (BSW_COMM_USERHANDLE_PNCUSER0)
#define COMM_USERHANDLE_PNCUSER1                (BSW_COMM_USERHANDLE_PNCUSER1)
#define COMM_USERHANDLE_PNCUSER2                (BSW_COMM_USERHANDLE_PNCUSER2)
#define COMM_USERHANDLE_PNCUSER3                (BSW_COMM_USERHANDLE_PNCUSER3)
#define COMM_USERHANDLE_PNCUSER4                (BSW_COMM_USERHANDLE_PNCUSER4)
#define COMM_USERHANDLE_PNCUSER5                (BSW_COMM_USERHANDLE_PNCUSER5)
#define COMM_USERHANDLE_PNCUSER6                (BSW_COMM_USERHANDLE_PNCUSER6)
#define COMM_USERHANDLE_PNCUSER7                (BSW_COMM_USERHANDLE_PNCUSER7)
#define COMM_USERHANDLE_PNCUSER8                (BSW_COMM_USERHANDLE_PNCUSER8)
#define COMM_USERHANDLE_PNCUSER9                (BSW_COMM_USERHANDLE_PNCUSER9)
#define COMM_USERHANDLE_PNCUSER10               (BSW_COMM_USERHANDLE_PNCUSER10)
#define COMM_USERHANDLE_PNCUSER11               (BSW_COMM_USERHANDLE_PNCUSER11)
#define COMM_USERHANDLE_PNCUSER12               (BSW_COMM_USERHANDLE_PNCUSER12)
#define COMM_USERHANDLE_PNCUSER13               (BSW_COMM_USERHANDLE_PNCUSER13)
#define COMM_USERHANDLE_PNCUSER14               (BSW_COMM_USERHANDLE_PNCUSER14)
#define COMM_USERHANDLE_PNCUSER15               (BSW_COMM_USERHANDLE_PNCUSER15)
#define COMM_USERHANDLE_PNCUSER16               (BSW_COMM_USERHANDLE_PNCUSER16)
#define COMM_USERHANDLE_PNCUSER17               (BSW_COMM_USERHANDLE_PNCUSER17)
#define COMM_USERHANDLE_PNCUSER18               (BSW_COMM_USERHANDLE_PNCUSER18)
#define COMM_USERHANDLE_PNCUSER19               (BSW_COMM_USERHANDLE_PNCUSER19)
#define COMM_USERHANDLE_PNCUSER20               (BSW_COMM_USERHANDLE_PNCUSER20)
#define COMM_USERHANDLE_PNCUSER21               (BSW_COMM_USERHANDLE_PNCUSER21)
#define COMM_USERHANDLE_PNCUSER22               (BSW_COMM_USERHANDLE_PNCUSER22)
#define COMM_USERHANDLE_PNCUSER23               (BSW_COMM_USERHANDLE_PNCUSER23)
#define COMM_USERHANDLE_PNCUSER24               (BSW_COMM_USERHANDLE_PNCUSER24)
#define COMM_USERHANDLE_PNCUSER25               (BSW_COMM_USERHANDLE_PNCUSER25)
#define COMM_USERHANDLE_PNCUSER26               (BSW_COMM_USERHANDLE_PNCUSER26)
#define COMM_USERHANDLE_PNCUSER27               (BSW_COMM_USERHANDLE_PNCUSER27)
#define COMM_USERHANDLE_PNCUSER28               (BSW_COMM_USERHANDLE_PNCUSER28)
#define COMM_USERHANDLE_PNCUSER29               (BSW_COMM_USERHANDLE_PNCUSER29)
#define COMM_USERHANDLE_PNCUSER30               (BSW_COMM_USERHANDLE_PNCUSER30)
#define COMM_USERHANDLE_PNCUSER31               (BSW_COMM_USERHANDLE_PNCUSER31)
#define COMM_USERHANDLE_PNCUSER32               (BSW_COMM_USERHANDLE_PNCUSER32)
#define COMM_USERHANDLE_PNCUSER33               (BSW_COMM_USERHANDLE_PNCUSER33)
#define COMM_USERHANDLE_PNCUSER34               (BSW_COMM_USERHANDLE_PNCUSER34)
#define COMM_USERHANDLE_PNCUSER35               (BSW_COMM_USERHANDLE_PNCUSER35)
#define COMM_USERHANDLE_PNCUSER36               (BSW_COMM_USERHANDLE_PNCUSER36)
#define COMM_USERHANDLE_PNCUSER37               (BSW_COMM_USERHANDLE_PNCUSER37)
#define COMM_USERHANDLE_PNCUSER38               (BSW_COMM_USERHANDLE_PNCUSER38)
#define COMM_USERHANDLE_PNCUSER39               (BSW_COMM_USERHANDLE_PNCUSER39)
#define COMM_USERHANDLE_PNCUSER40               (BSW_COMM_USERHANDLE_PNCUSER40)
#define COMM_USERHANDLE_PNCUSER41               (BSW_COMM_USERHANDLE_PNCUSER41)
#define COMM_USERHANDLE_PNCUSER42               (BSW_COMM_USERHANDLE_PNCUSER42)
#define COMM_USERHANDLE_PNCUSER43               (BSW_COMM_USERHANDLE_PNCUSER43)
#define COMM_USERHANDLE_PNCUSER44               (BSW_COMM_USERHANDLE_PNCUSER44)
#define COMM_USERHANDLE_PNCUSER45               (BSW_COMM_USERHANDLE_PNCUSER45)
#define COMM_USERHANDLE_PNCUSER46               (BSW_COMM_USERHANDLE_PNCUSER46)
#define COMM_USERHANDLE_PNCUSER47               (BSW_COMM_USERHANDLE_PNCUSER47)
#define COMM_USERHANDLE_PNCUSER48               (BSW_COMM_USERHANDLE_PNCUSER48)
#define COMM_USERHANDLE_PNCUSER49               (BSW_COMM_USERHANDLE_PNCUSER49)
#define COMM_USERHANDLE_PNCUSER50               (BSW_COMM_USERHANDLE_PNCUSER50)
#define COMM_USERHANDLE_PNCUSER51               (BSW_COMM_USERHANDLE_PNCUSER51)
#define COMM_USERHANDLE_PNCUSER52               (BSW_COMM_USERHANDLE_PNCUSER52)
#define COMM_USERHANDLE_PNCUSER53               (BSW_COMM_USERHANDLE_PNCUSER53)
#define COMM_USERHANDLE_PNCUSER54               (BSW_COMM_USERHANDLE_PNCUSER54)
#define COMM_USERHANDLE_PNCUSER55               (BSW_COMM_USERHANDLE_PNCUSER55)
#define COMM_USERHANDLE_PNCUSER56               (BSW_COMM_USERHANDLE_PNCUSER56)
#define COMM_USERHANDLE_PNCUSER57               (BSW_COMM_USERHANDLE_PNCUSER57)
#define COMM_USERHANDLE_PNCUSER58               (BSW_COMM_USERHANDLE_PNCUSER58)
#define COMM_USERHANDLE_PNCUSER59               (BSW_COMM_USERHANDLE_PNCUSER59)
#define COMM_USERHANDLE_PNCUSER60               (BSW_COMM_USERHANDLE_PNCUSER60)
#define COMM_USERHANDLE_PNCUSER61               (BSW_COMM_USERHANDLE_PNCUSER61)
#define COMM_USERHANDLE_PNCUSER62               (BSW_COMM_USERHANDLE_PNCUSER62)
#define COMM_USERHANDLE_PNCUSER63               (BSW_COMM_USERHANDLE_PNCUSER63)

/* Bus Awake Factor */
#define COMM_BUSAWAKE_NONE                      (BSW_COMM_BUSAWAKE_NONE)
#define COMM_BUSAWAKE_EXIST                     (BSW_COMM_BUSAWAKE_EXIST)

/* Bus Type */
#define COMM_BUS_TYPE_CAN                       (BSW_COMM_BUS_TYPE_CAN)
#define COMM_BUS_TYPE_CDD1                      (BSW_COMM_BUS_TYPE_CDD1)
#define COMM_BUS_TYPE_CDD2                      (BSW_COMM_BUS_TYPE_CDD2)
#define COMM_BUS_TYPE_ETH                       (BSW_COMM_BUS_TYPE_ETH)
#define COMM_BUS_TYPE_LIN                       (BSW_COMM_BUS_TYPE_LIN)
#define COMM_BUS_TYPE_INVALID                   (BSW_COMM_BUS_TYPE_INVALID)

/* Channel Attribute */
#define COMM_CH_ATTRBT_PHYSICAL                 (BSW_COMM_CH_ATTRBT_PHYSICAL)
#define COMM_CH_ATTRBT_VIRTUAL                  (BSW_COMM_CH_ATTRBT_VIRTUAL)

/* Vendor ID */
#define COMM_VENDOR_ID                          (BSW_COMM_VENDOR_ID)

/* Module ID */
#define COMM_MODULE_ID                          (BSW_COMM_MODULE_ID)

/* AUTOSAR Release Version */
#define COMM_AR_RELEASE_MAJOR_VERSION           (BSW_COMM_AR_RELEASE_MAJOR_VERSION)
#define COMM_AR_RELEASE_MINOR_VERSION           (BSW_COMM_AR_RELEASE_MINOR_VERSION)
#define COMM_AR_RELEASE_REVISION_VERSION        (BSW_COMM_AR_RELEASE_REVISION_VERSION)

/* Vendor Specification Version */
#define COMM_SW_MAJOR_VERSION                   (BSW_COMM_SW_MAJOR_VERSION)
#define COMM_SW_MINOR_VERSION                   (BSW_COMM_SW_MINOR_VERSION)
#define COMM_SW_PATCH_VERSION                   (BSW_COMM_SW_PATCH_VERSION)

/* Function */
#define ComM_Init                               (bsw_comm_ctrl_Init)
#define ComM_DeInit                             (bsw_comm_ctrl_DeInit)
#define ComM_GetState                           (bsw_comm_ctrl_GetState)
#define ComM_GetStateFixed                      (bsw_comm_ctrl_GetStateFixed)
#define ComM_GetStatus                          (bsw_comm_ctrl_GetStatus)
#define ComM_RequestComMode                     (bsw_comm_ctrl_RequestComMode)
#define ComM_GetMaxComMode                      (bsw_comm_ctrl_GetMaxComMode)
#define ComM_GetRequestedComMode                (bsw_comm_ctrl_GetReqComMode)
#define ComM_GetCurrentComMode                  (bsw_comm_ctrl_GetCurComMode)
#define ComM_CommunicationAllowed               (bsw_comm_ctrl_ComAllowed)
#define ComM_GetChPowerSupply                   (bsw_comm_ctrl_GetChPowSupply)
#define ComM_GetBusAwakePower                   (bsw_comm_ctrl_GetBusAwakePower)
#define ComM_JudgeChPowerSupply                 (bsw_comm_ctrl_JudgeChPowSupply)
#define ComM_GetDriverStatus                    (bsw_comm_ctrl_GetDriverStatus)
#define ComM_SetCoBusAwake                      (bsw_comm_ctrl_SetCoBusAwake)
#define ComM_GetBusAwake                        (bsw_comm_ctrl_GetBusAwakeExcCo)
#define ComM_SetBusAwake                        (bsw_comm_ctrl_SetBusAwake)
#define ComM_ClearBusAwake                      (bsw_comm_ctrl_ClearBusAwake)
#define ComM_GetInhibitionStatus                (bsw_comm_ctrl_GetInhibitStatus)
#define ComM_PreventWakeUp                      (bsw_comm_ctrl_PreventWakeUp)
#define ComM_LimitChannelToNoComMode            (bsw_comm_ctrl_LimChNoComMode)
#define ComM_LimitECUToNoComMode                (bsw_comm_ctrl_LimECUNoComMode)
#define ComM_ReadInhibitCounter                 (bsw_comm_ctrl_ReadInhibitCnt)
#define ComM_ResetInhibitCounter                (bsw_comm_ctrl_ResetInhibitCnt)
#define ComM_SetECUGroupClassification          (bsw_comm_ctrl_SetECUGroupClass)
#define ComM_GetVersionInfo                     (bsw_comm_ctrl_GetVersionInfo)
#define ComM_SetPnEira                          (bsw_comm_ctrl_SetPnEira)
#define ComM_GetPnIntRequest                    (bsw_comm_ctrl_GetPnIntRequest)
#define ComM_GetPncAwake                        (bsw_comm_ctrl_GetPncAwake)
#define ComM_SetCoPncAwake                      (bsw_comm_ctrl_SetCoPncAwake)
#define ComM_SetCoPncAwakeNoRequest             (bsw_comm_ctrl_SetCoPncAwakeNoReq)
#define ComM_GetPncMode                         (bsw_comm_ctrl_GetPncMode)
#define ComM_GetChPncMode                       (bsw_comm_ctrl_GetChPncMode)
#define ComM_RequestChPncComMode                (bsw_comm_ctrl_ReqChPNCComMode)
#define ComM_SetChannelBusAwake                 (bsw_comm_ctrl_SetChBusAwake)

#define ComM_CbkPncModeChgNotification          (bsw_comm_ctrl_CbkPncModeChgNtf)
#define ComM_CbkSetChannelBusAwake              (bsw_comm_ctrl_CbkSetChBusAwake)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/*--------------------------------------*/
/* Unit:ctrl                            */
/*--------------------------------------*/
/* User Handle Type                */
#define ComM_UserHandleType                 Bsw_ComM_UserHandleType
/* ComM Mode Type                  */
#define ComM_ModeType                       Bsw_ComM_ModeType
/* ComM State Type                 */
#define ComM_StateType                      Bsw_ComM_StateType
/* ComM Initialization Status Type */
#define ComM_InitStatusType                 Bsw_ComM_InitStatusType
/* ComM Inhibition Status Type     */
#define ComM_InhibitionStatusType           Bsw_ComM_InhibitionStatusType

/* ComM PncMode Type               */
#define ComM_PncModeType                    Bsw_ComM_PncModeType

/* Config Type Structure */
#define ComM_ConfigType                     Bsw_ComM_ConfigType

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* BSW_COMM_AR_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/05/16                                             */
/*  v1-1-0          :2018/09/25                                             */
/*  v2-0-0          :2021/11/17                                             */
/*  v2-1-0          :2022/06/07                                             */
/*  v2-2-0          :2023/05/08                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
