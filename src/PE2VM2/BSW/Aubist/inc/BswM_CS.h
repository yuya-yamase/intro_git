/* bswm_cs_h_v3-0-0                                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSWM/CS/HEADER                                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_BSWM_CS_AR_H
#define BSW_BSWM_CS_AR_H

#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>
#include <ComStack_Types.h>
#include <Com.h>
#include <bswm_cs/bsw_bswm_cs_public.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/*------------------------------*/
/* Unit:status                  */
/*------------------------------*/
/* CS Status                    */
#define BSWM_CS_CSST_RUN                   (BSW_BSWM_CS_CSST_RUN)
#define BSWM_CS_CSST_UNINIT                (BSW_BSWM_CS_CSST_UNINIT)

/* Receive enable type of PNC I-PDU control */
#define BSWM_CS_PNCIPDU_RXTYPE_CH          (BSW_BSWM_CS_PNCIPDU_RXTYPE_CH)
#define BSWM_CS_PNCIPDU_RXTYPE_PNC         (BSW_BSWM_CS_PNCIPDU_RXTYPE_PNC)

/* Function */
#define BswM_CS_Init                       (bsw_bswm_cs_st_Init)
#define BswM_CS_PrepareDeInit              (bsw_bswm_cs_st_PrepareDeInit)
#define BswM_CS_DeInit                     (bsw_bswm_cs_st_DeInit)
#define BswM_CS_Wakeup                     (bsw_bswm_cs_st_Wakeup)
#define BswM_CS_Sleep                      (bsw_bswm_cs_st_Sleep)
#define BswM_CS_Reset                      (bsw_bswm_cs_st_Reset)
#define BswM_CS_MainFunctionHigh           (bsw_bswm_cs_st_MainFunctionHigh)
#define BswM_CS_MainFunctionMiddle         (bsw_bswm_cs_st_MainFunctionMid)
#define BswM_CS_DetectFail                 (bsw_bswm_cs_st_DetectFail)
#define BswM_CS_GetClockProv               (bsw_bswm_cs_st_GetClockProv)
#define BswM_CS_GetStatus                  (bsw_bswm_cs_st_GetStatus)

/* Message authentication pattern for MultiplexerPDU */
#define BSWM_CS_MUX_MA_MSG                 (BSW_BSWM_CS_MUX_MA_MSG)
#define BSWM_CS_MUX_MA_MUXPDU              (BSW_BSWM_CS_MUX_MA_MUXPDU)
#define BSWM_CS_MUX_MA_MSG_MUXPDU          (BSW_BSWM_CS_MUX_MA_MSG_MUXPDU)
#define BSWM_CS_MUX_MA_NONE                (BSW_BSWM_CS_MUX_MA_NONE)

/*------------------------------*/
/* Unit:sysstat                 */
/*------------------------------*/
/* System Status                */
#define BSWM_CS_SYSSTAT_NONE               (BSW_BSWM_CS_SYSSTAT_NONE)
#define BSWM_CS_SYSSTAT_BAT                (BSW_BSWM_CS_SYSSTAT_BAT)
#define BSWM_CS_SYSSTAT_ACC                (BSW_BSWM_CS_SYSSTAT_ACC)
#define BSWM_CS_SYSSTAT_IG                 (BSW_BSWM_CS_SYSSTAT_IG)
#define BSWM_CS_SYSSTAT_USER1              (BSW_BSWM_CS_SYSSTAT_USER1)
#define BSWM_CS_SYSSTAT_USER2              (BSW_BSWM_CS_SYSSTAT_USER2)
#define BSWM_CS_SYSSTAT_USER3              (BSW_BSWM_CS_SYSSTAT_USER3)
#define BSWM_CS_SYSSTAT_USER4              (BSW_BSWM_CS_SYSSTAT_USER4)
#define BSWM_CS_SYSSTAT_USER5              (BSW_BSWM_CS_SYSSTAT_USER5)
#define BSWM_CS_SYSSTAT_USER6              (BSW_BSWM_CS_SYSSTAT_USER6)
#define BSWM_CS_SYSSTAT_USER7              (BSW_BSWM_CS_SYSSTAT_USER7)
#define BSWM_CS_SYSSTAT_USER8              (BSW_BSWM_CS_SYSSTAT_USER8)
#define BSWM_CS_SYSSTAT_USER9              (BSW_BSWM_CS_SYSSTAT_USER9)
#define BSWM_CS_SYSSTAT_USER10             (BSW_BSWM_CS_SYSSTAT_USER10)
#define BSWM_CS_SYSSTAT_USER11             (BSW_BSWM_CS_SYSSTAT_USER11)
#define BSWM_CS_SYSSTAT_USER12             (BSW_BSWM_CS_SYSSTAT_USER12)
#define BSWM_CS_SYSSTAT_USER13             (BSW_BSWM_CS_SYSSTAT_USER13)
#define BSWM_CS_SYSSTAT_USER14             (BSW_BSWM_CS_SYSSTAT_USER14)
#define BSWM_CS_SYSSTAT_USER15             (BSW_BSWM_CS_SYSSTAT_USER15)
#define BSWM_CS_SYSSTAT_USER16             (BSW_BSWM_CS_SYSSTAT_USER16)
#define BSWM_CS_SYSSTAT_USER17             (BSW_BSWM_CS_SYSSTAT_USER17)
#define BSWM_CS_SYSSTAT_USER18             (BSW_BSWM_CS_SYSSTAT_USER18)
#define BSWM_CS_SYSSTAT_USER19             (BSW_BSWM_CS_SYSSTAT_USER19)
#define BSWM_CS_SYSSTAT_USER20             (BSW_BSWM_CS_SYSSTAT_USER20)
#define BSWM_CS_SYSSTAT_USER21             (BSW_BSWM_CS_SYSSTAT_USER21)
#define BSWM_CS_SYSSTAT_USER22             (BSW_BSWM_CS_SYSSTAT_USER22)
#define BSWM_CS_SYSSTAT_USER23             (BSW_BSWM_CS_SYSSTAT_USER23)
#define BSWM_CS_SYSSTAT_USER24             (BSW_BSWM_CS_SYSSTAT_USER24)
#define BSWM_CS_SYSSTAT_USER25             (BSW_BSWM_CS_SYSSTAT_USER25)
#define BSWM_CS_SYSSTAT_USER26             (BSW_BSWM_CS_SYSSTAT_USER26)
#define BSWM_CS_SYSSTAT_USER27             (BSW_BSWM_CS_SYSSTAT_USER27)
#define BSWM_CS_SYSSTAT_USER28             (BSW_BSWM_CS_SYSSTAT_USER28)
#define BSWM_CS_SYSSTAT_USER29             (BSW_BSWM_CS_SYSSTAT_USER29)
#define BSWM_CS_SYSSTAT_USER30             (BSW_BSWM_CS_SYSSTAT_USER30)
#define BSWM_CS_SYSSTAT_USER31             (BSW_BSWM_CS_SYSSTAT_USER31)
#define BSWM_CS_SYSSTAT_USER32             (BSW_BSWM_CS_SYSSTAT_USER32)
#define BSWM_CS_SYSSTAT_USER33             (BSW_BSWM_CS_SYSSTAT_USER33)
#define BSWM_CS_SYSSTAT_USER34             (BSW_BSWM_CS_SYSSTAT_USER34)
#define BSWM_CS_SYSSTAT_USER35             (BSW_BSWM_CS_SYSSTAT_USER35)
#define BSWM_CS_SYSSTAT_USER36             (BSW_BSWM_CS_SYSSTAT_USER36)
#define BSWM_CS_SYSSTAT_USER37             (BSW_BSWM_CS_SYSSTAT_USER37)
#define BSWM_CS_SYSSTAT_USER38             (BSW_BSWM_CS_SYSSTAT_USER38)
#define BSWM_CS_SYSSTAT_USER39             (BSW_BSWM_CS_SYSSTAT_USER39)
#define BSWM_CS_SYSSTAT_USER40             (BSW_BSWM_CS_SYSSTAT_USER40)
#define BSWM_CS_SYSSTAT_USER41             (BSW_BSWM_CS_SYSSTAT_USER41)
#define BSWM_CS_SYSSTAT_USER42             (BSW_BSWM_CS_SYSSTAT_USER42)
#define BSWM_CS_SYSSTAT_USER43             (BSW_BSWM_CS_SYSSTAT_USER43)
#define BSWM_CS_SYSSTAT_USER44             (BSW_BSWM_CS_SYSSTAT_USER44)
#define BSWM_CS_SYSSTAT_USER45             (BSW_BSWM_CS_SYSSTAT_USER45)
#define BSWM_CS_SYSSTAT_USER46             (BSW_BSWM_CS_SYSSTAT_USER46)
#define BSWM_CS_SYSSTAT_USER47             (BSW_BSWM_CS_SYSSTAT_USER47)
#define BSWM_CS_SYSSTAT_USER48             (BSW_BSWM_CS_SYSSTAT_USER48)
#define BSWM_CS_SYSSTAT_USER49             (BSW_BSWM_CS_SYSSTAT_USER49)
#define BSWM_CS_SYSSTAT_USER50             (BSW_BSWM_CS_SYSSTAT_USER50)
#define BSWM_CS_SYSSTAT_USER51             (BSW_BSWM_CS_SYSSTAT_USER51)
#define BSWM_CS_SYSSTAT_USER52             (BSW_BSWM_CS_SYSSTAT_USER52)
#define BSWM_CS_SYSSTAT_USER53             (BSW_BSWM_CS_SYSSTAT_USER53)
#define BSWM_CS_SYSSTAT_USER54             (BSW_BSWM_CS_SYSSTAT_USER54)
#define BSWM_CS_SYSSTAT_USER55             (BSW_BSWM_CS_SYSSTAT_USER55)
#define BSWM_CS_SYSSTAT_USER56             (BSW_BSWM_CS_SYSSTAT_USER56)
#define BSWM_CS_SYSSTAT_USER57             (BSW_BSWM_CS_SYSSTAT_USER57)
#define BSWM_CS_SYSSTAT_USER58             (BSW_BSWM_CS_SYSSTAT_USER58)
#define BSWM_CS_SYSSTAT_USER59             (BSW_BSWM_CS_SYSSTAT_USER59)
#define BSWM_CS_SYSSTAT_USER60             (BSW_BSWM_CS_SYSSTAT_USER60)
#define BSWM_CS_SYSSTAT_USER61             (BSW_BSWM_CS_SYSSTAT_USER61)

/* System Status Mask Bit       */
#define BSWM_CS_SYSSTAT_MASK_BAT           (BSW_BSWM_CS_SYSSTAT_MASK_BAT)
#define BSWM_CS_SYSSTAT_MASK_ACC           (BSW_BSWM_CS_SYSSTAT_MASK_ACC)
#define BSWM_CS_SYSSTAT_MASK_IG            (BSW_BSWM_CS_SYSSTAT_MASK_IG)
#define BSWM_CS_SYSSTAT_MASK_USER1         (BSW_BSWM_CS_SYSSTAT_MASK_USER1)
#define BSWM_CS_SYSSTAT_MASK_USER2         (BSW_BSWM_CS_SYSSTAT_MASK_USER2)
#define BSWM_CS_SYSSTAT_MASK_USER3         (BSW_BSWM_CS_SYSSTAT_MASK_USER3)
#define BSWM_CS_SYSSTAT_MASK_USER4         (BSW_BSWM_CS_SYSSTAT_MASK_USER4)
#define BSWM_CS_SYSSTAT_MASK_USER5         (BSW_BSWM_CS_SYSSTAT_MASK_USER5)
#define BSWM_CS_SYSSTAT_MASK_USER6         (BSW_BSWM_CS_SYSSTAT_MASK_USER6)
#define BSWM_CS_SYSSTAT_MASK_USER7         (BSW_BSWM_CS_SYSSTAT_MASK_USER7)
#define BSWM_CS_SYSSTAT_MASK_USER8         (BSW_BSWM_CS_SYSSTAT_MASK_USER8)
#define BSWM_CS_SYSSTAT_MASK_USER9         (BSW_BSWM_CS_SYSSTAT_MASK_USER9)
#define BSWM_CS_SYSSTAT_MASK_USER10        (BSW_BSWM_CS_SYSSTAT_MASK_USER10)
#define BSWM_CS_SYSSTAT_MASK_USER11        (BSW_BSWM_CS_SYSSTAT_MASK_USER11)
#define BSWM_CS_SYSSTAT_MASK_USER12        (BSW_BSWM_CS_SYSSTAT_MASK_USER12)
#define BSWM_CS_SYSSTAT_MASK_USER13        (BSW_BSWM_CS_SYSSTAT_MASK_USER13)
#define BSWM_CS_SYSSTAT_MASK_USER14        (BSW_BSWM_CS_SYSSTAT_MASK_USER14)
#define BSWM_CS_SYSSTAT_MASK_USER15        (BSW_BSWM_CS_SYSSTAT_MASK_USER15)
#define BSWM_CS_SYSSTAT_MASK_USER16        (BSW_BSWM_CS_SYSSTAT_MASK_USER16)
#define BSWM_CS_SYSSTAT_MASK_USER17        (BSW_BSWM_CS_SYSSTAT_MASK_USER17)
#define BSWM_CS_SYSSTAT_MASK_USER18        (BSW_BSWM_CS_SYSSTAT_MASK_USER18)
#define BSWM_CS_SYSSTAT_MASK_USER19        (BSW_BSWM_CS_SYSSTAT_MASK_USER19)
#define BSWM_CS_SYSSTAT_MASK_USER20        (BSW_BSWM_CS_SYSSTAT_MASK_USER20)
#define BSWM_CS_SYSSTAT_MASK_USER21        (BSW_BSWM_CS_SYSSTAT_MASK_USER21)
#define BSWM_CS_SYSSTAT_MASK_USER22        (BSW_BSWM_CS_SYSSTAT_MASK_USER22)
#define BSWM_CS_SYSSTAT_MASK_USER23        (BSW_BSWM_CS_SYSSTAT_MASK_USER23)
#define BSWM_CS_SYSSTAT_MASK_USER24        (BSW_BSWM_CS_SYSSTAT_MASK_USER24)
#define BSWM_CS_SYSSTAT_MASK_USER25        (BSW_BSWM_CS_SYSSTAT_MASK_USER25)
#define BSWM_CS_SYSSTAT_MASK_USER26        (BSW_BSWM_CS_SYSSTAT_MASK_USER26)
#define BSWM_CS_SYSSTAT_MASK_USER27        (BSW_BSWM_CS_SYSSTAT_MASK_USER27)
#define BSWM_CS_SYSSTAT_MASK_USER28        (BSW_BSWM_CS_SYSSTAT_MASK_USER28)
#define BSWM_CS_SYSSTAT_MASK_USER29        (BSW_BSWM_CS_SYSSTAT_MASK_USER29)
#define BSWM_CS_SYSSTAT_MASK_USER30        (BSW_BSWM_CS_SYSSTAT_MASK_USER30)
#define BSWM_CS_SYSSTAT_MASK_USER31        (BSW_BSWM_CS_SYSSTAT_MASK_USER31)
#define BSWM_CS_SYSSTAT_MASK_USER32        (BSW_BSWM_CS_SYSSTAT_MASK_USER32)
#define BSWM_CS_SYSSTAT_MASK_USER33        (BSW_BSWM_CS_SYSSTAT_MASK_USER33)
#define BSWM_CS_SYSSTAT_MASK_USER34        (BSW_BSWM_CS_SYSSTAT_MASK_USER34)
#define BSWM_CS_SYSSTAT_MASK_USER35        (BSW_BSWM_CS_SYSSTAT_MASK_USER35)
#define BSWM_CS_SYSSTAT_MASK_USER36        (BSW_BSWM_CS_SYSSTAT_MASK_USER36)
#define BSWM_CS_SYSSTAT_MASK_USER37        (BSW_BSWM_CS_SYSSTAT_MASK_USER37)
#define BSWM_CS_SYSSTAT_MASK_USER38        (BSW_BSWM_CS_SYSSTAT_MASK_USER38)
#define BSWM_CS_SYSSTAT_MASK_USER39        (BSW_BSWM_CS_SYSSTAT_MASK_USER39)
#define BSWM_CS_SYSSTAT_MASK_USER40        (BSW_BSWM_CS_SYSSTAT_MASK_USER40)
#define BSWM_CS_SYSSTAT_MASK_USER41        (BSW_BSWM_CS_SYSSTAT_MASK_USER41)
#define BSWM_CS_SYSSTAT_MASK_USER42        (BSW_BSWM_CS_SYSSTAT_MASK_USER42)
#define BSWM_CS_SYSSTAT_MASK_USER43        (BSW_BSWM_CS_SYSSTAT_MASK_USER43)
#define BSWM_CS_SYSSTAT_MASK_USER44        (BSW_BSWM_CS_SYSSTAT_MASK_USER44)
#define BSWM_CS_SYSSTAT_MASK_USER45        (BSW_BSWM_CS_SYSSTAT_MASK_USER45)
#define BSWM_CS_SYSSTAT_MASK_USER46        (BSW_BSWM_CS_SYSSTAT_MASK_USER46)
#define BSWM_CS_SYSSTAT_MASK_USER47        (BSW_BSWM_CS_SYSSTAT_MASK_USER47)
#define BSWM_CS_SYSSTAT_MASK_USER48        (BSW_BSWM_CS_SYSSTAT_MASK_USER48)
#define BSWM_CS_SYSSTAT_MASK_USER49        (BSW_BSWM_CS_SYSSTAT_MASK_USER49)
#define BSWM_CS_SYSSTAT_MASK_USER50        (BSW_BSWM_CS_SYSSTAT_MASK_USER50)
#define BSWM_CS_SYSSTAT_MASK_USER51        (BSW_BSWM_CS_SYSSTAT_MASK_USER51)
#define BSWM_CS_SYSSTAT_MASK_USER52        (BSW_BSWM_CS_SYSSTAT_MASK_USER52)
#define BSWM_CS_SYSSTAT_MASK_USER53        (BSW_BSWM_CS_SYSSTAT_MASK_USER53)
#define BSWM_CS_SYSSTAT_MASK_USER54        (BSW_BSWM_CS_SYSSTAT_MASK_USER54)
#define BSWM_CS_SYSSTAT_MASK_USER55        (BSW_BSWM_CS_SYSSTAT_MASK_USER55)
#define BSWM_CS_SYSSTAT_MASK_USER56        (BSW_BSWM_CS_SYSSTAT_MASK_USER56)
#define BSWM_CS_SYSSTAT_MASK_USER57        (BSW_BSWM_CS_SYSSTAT_MASK_USER57)
#define BSWM_CS_SYSSTAT_MASK_USER58        (BSW_BSWM_CS_SYSSTAT_MASK_USER58)
#define BSWM_CS_SYSSTAT_MASK_USER59        (BSW_BSWM_CS_SYSSTAT_MASK_USER59)
#define BSWM_CS_SYSSTAT_MASK_USER60        (BSW_BSWM_CS_SYSSTAT_MASK_USER60)
#define BSWM_CS_SYSSTAT_MASK_USER61        (BSW_BSWM_CS_SYSSTAT_MASK_USER61)

/* Function */
#define BswM_CS_SetSystemStatus            (bsw_bswm_cs_sysst_SetSysStat)
#define BswM_CS_SetSystemStatusExt         (bsw_bswm_cs_sysst_SetSysStatExt)
#define BswM_CS_GetSystemStatus            (bsw_bswm_cs_sysst_GetSysStat)
#define BswM_CS_GetSystemStatusExt         (bsw_bswm_cs_sysst_GetSysStatExt)
#define BswM_CS_GetLatestSystemStatus      (bsw_bswm_cs_sysst_GetLatSysStat)
#define BswM_CS_GetECUInitPower            (bsw_bswm_cs_sysst_GetECUInitPw)
#define BswM_CS_JudgeWakeUpChPower         (bsw_bswm_cs_sysst_JudgeWkUpChPw)

/*------------------------------*/
/* Unit:ctrl                    */
/*------------------------------*/
/* CPU Awake Factor             */
#define BSWM_CS_AWAKE_NONE                 (BSW_BSWM_CS_AWAKE_NONE)
#define BSWM_CS_AWAKE_EXIST                (BSW_BSWM_CS_AWAKE_EXIST)

/* Event transmission Status    */
#define BSWM_CS_EVTX_OK                    (BSW_BSWM_CS_EVTX_OK)
#define BSWM_CS_EVTX_WAIT                  (BSW_BSWM_CS_EVTX_WAIT)

/* Return code                  */
#define BSWM_CS_RET_OK                     (BSW_BSWM_CS_RET_OK)
#define BSWM_CS_RET_INVALID                (BSW_BSWM_CS_RET_INVALID)
#define BSWM_CS_RET_TXSTOP                 (BSW_BSWM_CS_RET_TXSTOP)
#define BSWM_CS_RET_TXRUN                  (BSW_BSWM_CS_RET_TXRUN)
#define BSWM_CS_RET_DMSTOP                 (BSW_BSWM_CS_RET_DMSTOP)
#define BSWM_CS_RET_DMRUN                  (BSW_BSWM_CS_RET_DMRUN)

/* Control method of transmission limiting function */
#define BSWM_CS_TXCTRL_NOUSE               (BSW_BSWM_CS_TXCTRL_NOUSE)
#define BSWM_CS_TXCTRL_STOPALL             (BSW_BSWM_CS_TXCTRL_STOPALL)
#define BSWM_CS_TXCTRL_STOPEV              (BSW_BSWM_CS_TXCTRL_STOPEV)
#define BSWM_CS_TXCTRL_STOPPRD             (BSW_BSWM_CS_TXCTRL_STOPPRD)
#define BSWM_CS_TXCTRL_CYCCHG              (BSW_BSWM_CS_TXCTRL_CYCCHG)

/* Send and Receive Status */
#define BSWM_CS_TRXST_TRX_ENABLE           (BSW_BSWM_CS_TRXST_TRX_ENABLE)
#define BSWM_CS_TRXST_TRX_DISABLE          (BSW_BSWM_CS_TRXST_TRX_DISABLE)
#define BSWM_CS_TRXST_RX_ENABLE            (BSW_BSWM_CS_TRXST_RX_ENABLE)

/* Transmission request clear object */
#define BSWM_CS_COM_TX_MODE_ALL            (BSW_BSWM_CS_COM_TX_MODE_ALL)
#define BSWM_CS_COM_TX_MODE_EVENT          (BSW_BSWM_CS_COM_TX_MODE_EVENT)
#define BSWM_CS_COM_TX_MODE_PERIODIC       (BSW_BSWM_CS_COM_TX_MODE_PERIODIC)
#define BSWM_CS_COM_TX_MODE_INVALID        (BSW_BSWM_CS_COM_TX_MODE_INVALID)

/* Channel Invalid              */
#define BSWM_CS_CHANNEL_INVALID            (BSW_BSWM_CS_CHANNEL_INVALID)

/* Component ID                 */
#define BSWM_CS_UPCOMP_COM                 (BSW_BSWM_CS_UPCOMP_COM)
#define BSWM_CS_UPCOMP_CDD1                (BSW_BSWM_CS_UPCOMP_CDD1)
#define BSWM_CS_UPCOMP_CDD2                (BSW_BSWM_CS_UPCOMP_CDD2)

/* Periodic Tx Reset Reason */
#define BSWM_CS_RSTR_BUSWAKEUP             (BSW_BSWM_CS_RSTR_BUSWAKEUP)
#define BSWM_CS_RSTR_RESUMETX              (BSW_BSWM_CS_RSTR_RESUMETX)

/* success or failure of channel power on wakeup */
#define BSWM_CS_WKUP_CHPW_ON               (BSW_BSWM_CS_WKUP_CHPW_ON)
#define BSWM_CS_WKUP_CHPW_OFF              (BSW_BSWM_CS_WKUP_CHPW_OFF)

/* Function */
#define BswM_CS_CheckAwake                 (bsw_bswm_cs_ctrl_CheckAwake)
#define BswM_CS_DisableTx                  (bsw_bswm_cs_ctrl_DisableTx)
#define BswM_CS_EnableTx                   (bsw_bswm_cs_ctrl_EnableTx)
#define BswM_CS_StopNetwork                (bsw_bswm_cs_ctrl_StopNetwork)
#define BswM_CS_StartNetwork               (bsw_bswm_cs_ctrl_StartNetwork)
#define BswM_CS_SetIpduCtrlIpduGrpVect     (bsw_bswm_cs_st_SetIpduGrVct)
#define BswM_CS_SetIpduCtrlIpduGrpVectExt  (bsw_bswm_cs_st_SetIpduGrVctExt)
#define BswM_CS_SetWkupMskIpduGrpVect      (bsw_bswm_cs_st_SetWkIpGrVct)
#define BswM_CS_SetWkupMskIpduGrpVectExt   (bsw_bswm_cs_st_SetWkIpGrVctExt)
#define BswM_CS_SetRcpDMIpduGrpVect        (bsw_bswm_cs_st_SetDMGrVct)
#define BswM_CS_SetRcpDMIpduGrpVectExt     (bsw_bswm_cs_st_SetDMGrVctExt)
#define BswM_CS_SetTxControl               (bsw_bswm_cs_ctrl_SetTxControl)
#define BswM_CS_ResetPeriodicTx            (bsw_bswm_cs_ctrl_ResetPeriTx)
#define BswM_CS_StopTxPdu                  (bsw_bswm_cs_ctrl_StopTxPdu)
#define BswM_CS_ResumeTxPdu                (bsw_bswm_cs_ctrl_ResumeTxPdu)
#define BswM_CS_GetResumeWaitTime          (bsw_bswm_cs_ctrl_GetRsmWaitTime)
#define BswM_CS_GetTxCtrlType              (bsw_bswm_cs_ctrl_GetTxCtrlType)
#define BswM_CS_ClearTxPdu                 (bsw_bswm_cs_ctrl_ClearTxPdu)
#define BswM_CS_ClearNonAwakeEvtIpdu       (bsw_bswm_cs_ctrl_ClrNoAwkEvtPdu)
#define BswM_CS_StartChangePeriodCh        (bsw_bswm_cs_ctrl_StartChgPeriCh)
#define BswM_CS_StopChangePeriodCh         (bsw_bswm_cs_ctrl_StopChgPeriCh)
#define BswM_CS_RestartChCtrl              (bsw_bswm_cs_ctrl_RestartChCtrl)
#define BswM_CS_StopDMControl              (bsw_bswm_cs_ctrl_StopDMCtrl)
#define BswM_CS_ResumeDMControl            (bsw_bswm_cs_ctrl_RsmDMCtrl)
#define BswM_CS_ReqDMCtrReset              (bsw_bswm_cs_ctrl_ReqDMCtrReset)
#define BswM_CS_DetectChFail               (bsw_bswm_cs_ctrl_DetectChFail)
#define BswM_CS_ReleaseChFail              (bsw_bswm_cs_ctrl_ReleaseChFail)
#define BswM_CS_GetTRXStatus               (bsw_bswm_cs_ctrl_GetTRXStatus)
#define BswM_CS_SetXcpTxMode               (bsw_bswm_cs_ctrl_SetXcpTxMode)
#define BswM_CS_GetTxPduChannel            (bsw_bswm_cs_ctrl_GetTxPduCh)
#define BswM_CS_GetRxPduChannel            (bsw_bswm_cs_ctrl_GetRxPduCh)

/*------------------------------*/
/* Unit:user                    */
/*------------------------------*/
/* Function */
#define BswM_CS_CbkChgInitSystemStatus     (bsw_bswm_cs_user_CbkChgIniSysSt)
#define BswM_CS_CbkChgInitSystemStatusExt  (bsw_bswm_cs_user_CbkChgIniSSExt)
#define BswM_CS_CbkSetSystemStatus         (bsw_bswm_cs_user_CbkSetSysStat)
#define BswM_CS_CbkProvideClockInit        (bsw_bswm_cs_user_CbkProvClkInit)
#define BswM_CS_CbkProvideClockWkup        (bsw_bswm_cs_user_CbkProvClkWkup)
#define BswM_CS_CbkChkWkupSrcInd           (bsw_bswm_cs_user_CbkWkupSrcInd)
#define BswM_CS_CbkAppMainFunction         (bsw_bswm_cs_user_CbkAppMainFunc)
#define BswM_CS_CbkDcmMainFunction         (bsw_bswm_cs_user_CbkDcmMainFunc)
#define BswM_CS_CbkPreMainFunctionHi       (bsw_bswm_cs_user_CbkPreMFuncHi)
#define BswM_CS_CbkPostMainFunctionHi      (bsw_bswm_cs_user_CbkPostMFuncHi)
#define BswM_CS_CbkPreMainFunctionMid      (bsw_bswm_cs_user_CbkPreMFuncMid)
#define BswM_CS_CbkPostMainFunctionMid     (bsw_bswm_cs_user_CbkPostMFuncMd)
#define BswM_CS_CbkSetBusAwake             (bsw_bswm_cs_user_CbkSetBusAwake)
#define BswM_CS_CbkSetResumeWaitTime       (bsw_bswm_cs_user_CbkSetRsmTime)
#define BswM_CS_CbkNetworkStart            (bsw_bswm_cs_user_CbkNetworkStrt)
#define BswM_CS_CbkNetworkStop             (bsw_bswm_cs_user_CbkNetworkStop)
#define BswM_CS_CbkEnableTx                (bsw_bswm_cs_user_CbkEnableTx)
#define BswM_CS_CbkDisableTx               (bsw_bswm_cs_user_CbkDisableTx)
#define BswM_CS_CbkSetDMCtrlWaitTime       (bsw_bswm_cs_user_CbkSetDMWaitTm)
#define BswM_CS_CbkDetectFail              (bsw_bswm_cs_user_CbkDetectFail)
#define BswM_CS_CbkPreWakeup               (bsw_bswm_cs_user_CbkPreWakeup)
#define BswM_CS_CbkPostSleep               (bsw_bswm_cs_user_CbkPostSleep)
#define BswM_CS_CbkSecOCMainFunctionTx     (bsw_bswm_cs_user_CbkSecMFuncTx)
#define BswM_CS_CbkSecOCMainFunctionRx     (bsw_bswm_cs_user_CbkSecMFuncRx)
#define BswM_CS_CbkPreFailRestartClrEvt    (bsw_bswm_cs_user_CbkPrFailClrEv)

/*------------------------------*/
/* Unit:system                  */
/*------------------------------*/
/* Function */
#define BswM_CS_ConvertMs2Tick_High_Rup    (bsw_bswm_cs_system_ms2HTickRup)
#define BswM_CS_ConvertMs2Tick_Mid_Rup     (bsw_bswm_cs_system_ms2MTickRup)


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
#define BswM_CS_RetCtrlType                Bsw_BswM_CS_RetCtrlType

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* BSW_BSWM_CS_AR_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/06/16                                             */
/*  v1-1-0          :2018/12/03                                             */
/*  v2-0-0          :2021/09/01                                             */
/*  v2-2-0          :2023/05/09                                             */
/*  v3-0-0          :2024/11/13                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
