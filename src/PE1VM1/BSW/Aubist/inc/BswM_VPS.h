/* bswm_vps_h_v3-0-0                                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSWM/VPS/HEADER                                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_BSWM_VPS_AR_H
#define BSW_BSWM_VPS_AR_H

#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>
#include <ComStack_Types.h>
#include <bswm_vps/bsw_bswm_vps_public.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define BSWM_VPS_PDU_BYTE_INVALID            (BSW_BSWM_VPS_PDU_BYTE_INVALID)       /* Data position : INVALID        */
#define BSWM_VPS_PDU_BYTE_0                  (BSW_BSWM_VPS_PDU_BYTE_0)             /* Data position : byte0          */
#define BSWM_VPS_PDU_BYTE_1                  (BSW_BSWM_VPS_PDU_BYTE_1)             /* Data position : byte1          */
#define BSWM_VPS_PDU_BYTE_2                  (BSW_BSWM_VPS_PDU_BYTE_2)             /* Data position : byte2          */
#define BSWM_VPS_PDU_BYTE_3                  (BSW_BSWM_VPS_PDU_BYTE_3)             /* Data position : byte3          */
#define BSWM_VPS_PDU_BYTE_4                  (BSW_BSWM_VPS_PDU_BYTE_4)             /* Data position : byte4          */
#define BSWM_VPS_PDU_BYTE_5                  (BSW_BSWM_VPS_PDU_BYTE_5)             /* Data position : byte5          */
#define BSWM_VPS_PDU_BYTE_6                  (BSW_BSWM_VPS_PDU_BYTE_6)             /* Data position : byte6          */
#define BSWM_VPS_PDU_BYTE_7                  (BSW_BSWM_VPS_PDU_BYTE_7)             /* Data position : byte7          */
#define BSWM_VPS_PDU_BYTE_8                  (BSW_BSWM_VPS_PDU_BYTE_8)             /* Data position : byte8          */
#define BSWM_VPS_PDU_BYTE_9                  (BSW_BSWM_VPS_PDU_BYTE_9)             /* Data position : byte9          */
#define BSWM_VPS_PDU_BYTE_10                 (BSW_BSWM_VPS_PDU_BYTE_10)            /* Data position : byte10         */
#define BSWM_VPS_PDU_BYTE_11                 (BSW_BSWM_VPS_PDU_BYTE_11)            /* Data position : byte11         */
#define BSWM_VPS_PDU_BYTE_12                 (BSW_BSWM_VPS_PDU_BYTE_12)            /* Data position : byte12         */
#define BSWM_VPS_PDU_BYTE_13                 (BSW_BSWM_VPS_PDU_BYTE_13)            /* Data position : byte13         */
#define BSWM_VPS_PDU_BYTE_14                 (BSW_BSWM_VPS_PDU_BYTE_14)            /* Data position : byte14         */
#define BSWM_VPS_PDU_BYTE_15                 (BSW_BSWM_VPS_PDU_BYTE_15)            /* Data position : byte15         */
#define BSWM_VPS_PDU_BYTE_16                 (BSW_BSWM_VPS_PDU_BYTE_16)            /* Data position : byte16         */
#define BSWM_VPS_PDU_BYTE_17                 (BSW_BSWM_VPS_PDU_BYTE_17)            /* Data position : byte17         */
#define BSWM_VPS_PDU_BYTE_18                 (BSW_BSWM_VPS_PDU_BYTE_18)            /* Data position : byte18         */
#define BSWM_VPS_PDU_BYTE_19                 (BSW_BSWM_VPS_PDU_BYTE_19)            /* Data position : byte19         */
#define BSWM_VPS_PDU_BYTE_20                 (BSW_BSWM_VPS_PDU_BYTE_20)            /* Data position : byte20         */
#define BSWM_VPS_PDU_BYTE_21                 (BSW_BSWM_VPS_PDU_BYTE_21)            /* Data position : byte21         */
#define BSWM_VPS_PDU_BYTE_22                 (BSW_BSWM_VPS_PDU_BYTE_22)            /* Data position : byte22         */
#define BSWM_VPS_PDU_BYTE_23                 (BSW_BSWM_VPS_PDU_BYTE_23)            /* Data position : byte23         */
#define BSWM_VPS_PDU_BYTE_24                 (BSW_BSWM_VPS_PDU_BYTE_24)            /* Data position : byte24         */
#define BSWM_VPS_PDU_BYTE_25                 (BSW_BSWM_VPS_PDU_BYTE_25)            /* Data position : byte25         */
#define BSWM_VPS_PDU_BYTE_26                 (BSW_BSWM_VPS_PDU_BYTE_26)            /* Data position : byte26         */
#define BSWM_VPS_PDU_BYTE_27                 (BSW_BSWM_VPS_PDU_BYTE_27)            /* Data position : byte27         */
#define BSWM_VPS_PDU_BYTE_28                 (BSW_BSWM_VPS_PDU_BYTE_28)            /* Data position : byte28         */
#define BSWM_VPS_PDU_BYTE_29                 (BSW_BSWM_VPS_PDU_BYTE_29)            /* Data position : byte29         */
#define BSWM_VPS_PDU_BYTE_30                 (BSW_BSWM_VPS_PDU_BYTE_30)            /* Data position : byte30         */
#define BSWM_VPS_PDU_BYTE_31                 (BSW_BSWM_VPS_PDU_BYTE_31)            /* Data position : byte31         */
#define BSWM_VPS_PDU_BYTE_32                 (BSW_BSWM_VPS_PDU_BYTE_32)            /* Data position : byte32         */
#define BSWM_VPS_PDU_BYTE_33                 (BSW_BSWM_VPS_PDU_BYTE_33)            /* Data position : byte33         */
#define BSWM_VPS_PDU_BYTE_34                 (BSW_BSWM_VPS_PDU_BYTE_34)            /* Data position : byte34         */
#define BSWM_VPS_PDU_BYTE_35                 (BSW_BSWM_VPS_PDU_BYTE_35)            /* Data position : byte35         */
#define BSWM_VPS_PDU_BYTE_36                 (BSW_BSWM_VPS_PDU_BYTE_36)            /* Data position : byte36         */
#define BSWM_VPS_PDU_BYTE_37                 (BSW_BSWM_VPS_PDU_BYTE_37)            /* Data position : byte37         */
#define BSWM_VPS_PDU_BYTE_38                 (BSW_BSWM_VPS_PDU_BYTE_38)            /* Data position : byte38         */
#define BSWM_VPS_PDU_BYTE_39                 (BSW_BSWM_VPS_PDU_BYTE_39)            /* Data position : byte39         */
#define BSWM_VPS_PDU_BYTE_40                 (BSW_BSWM_VPS_PDU_BYTE_40)            /* Data position : byte40         */
#define BSWM_VPS_PDU_BYTE_41                 (BSW_BSWM_VPS_PDU_BYTE_41)            /* Data position : byte41         */
#define BSWM_VPS_PDU_BYTE_42                 (BSW_BSWM_VPS_PDU_BYTE_42)            /* Data position : byte42         */
#define BSWM_VPS_PDU_BYTE_43                 (BSW_BSWM_VPS_PDU_BYTE_43)            /* Data position : byte43         */
#define BSWM_VPS_PDU_BYTE_44                 (BSW_BSWM_VPS_PDU_BYTE_44)            /* Data position : byte44         */
#define BSWM_VPS_PDU_BYTE_45                 (BSW_BSWM_VPS_PDU_BYTE_45)            /* Data position : byte45         */
#define BSWM_VPS_PDU_BYTE_46                 (BSW_BSWM_VPS_PDU_BYTE_46)            /* Data position : byte46         */
#define BSWM_VPS_PDU_BYTE_47                 (BSW_BSWM_VPS_PDU_BYTE_47)            /* Data position : byte47         */
#define BSWM_VPS_PDU_BYTE_48                 (BSW_BSWM_VPS_PDU_BYTE_48)            /* Data position : byte48         */
#define BSWM_VPS_PDU_BYTE_49                 (BSW_BSWM_VPS_PDU_BYTE_49)            /* Data position : byte49         */
#define BSWM_VPS_PDU_BYTE_50                 (BSW_BSWM_VPS_PDU_BYTE_50)            /* Data position : byte50         */
#define BSWM_VPS_PDU_BYTE_51                 (BSW_BSWM_VPS_PDU_BYTE_51)            /* Data position : byte51         */
#define BSWM_VPS_PDU_BYTE_52                 (BSW_BSWM_VPS_PDU_BYTE_52)            /* Data position : byte52         */
#define BSWM_VPS_PDU_BYTE_53                 (BSW_BSWM_VPS_PDU_BYTE_53)            /* Data position : byte53         */
#define BSWM_VPS_PDU_BYTE_54                 (BSW_BSWM_VPS_PDU_BYTE_54)            /* Data position : byte54         */
#define BSWM_VPS_PDU_BYTE_55                 (BSW_BSWM_VPS_PDU_BYTE_55)            /* Data position : byte55         */
#define BSWM_VPS_PDU_BYTE_56                 (BSW_BSWM_VPS_PDU_BYTE_56)            /* Data position : byte56         */
#define BSWM_VPS_PDU_BYTE_57                 (BSW_BSWM_VPS_PDU_BYTE_57)            /* Data position : byte57         */
#define BSWM_VPS_PDU_BYTE_58                 (BSW_BSWM_VPS_PDU_BYTE_58)            /* Data position : byte58         */
#define BSWM_VPS_PDU_BYTE_59                 (BSW_BSWM_VPS_PDU_BYTE_59)            /* Data position : byte59         */
#define BSWM_VPS_PDU_BYTE_60                 (BSW_BSWM_VPS_PDU_BYTE_60)            /* Data position : byte60         */
#define BSWM_VPS_PDU_BYTE_61                 (BSW_BSWM_VPS_PDU_BYTE_61)            /* Data position : byte61         */
#define BSWM_VPS_PDU_BYTE_62                 (BSW_BSWM_VPS_PDU_BYTE_62)            /* Data position : byte62         */
#define BSWM_VPS_PDU_BYTE_63                 (BSW_BSWM_VPS_PDU_BYTE_63)            /* Data position : byte63         */

#define BSWM_VPS_PDU_BIT_0                   (BSW_BSWM_VPS_PDU_BIT_0)               /* Data position : bit0          */
#define BSWM_VPS_PDU_BIT_1                   (BSW_BSWM_VPS_PDU_BIT_1)               /* Data position : bit1          */
#define BSWM_VPS_PDU_BIT_2                   (BSW_BSWM_VPS_PDU_BIT_2)               /* Data position : bit2          */
#define BSWM_VPS_PDU_BIT_3                   (BSW_BSWM_VPS_PDU_BIT_3)               /* Data position : bit3          */
#define BSWM_VPS_PDU_BIT_4                   (BSW_BSWM_VPS_PDU_BIT_4)               /* Data position : bit4          */
#define BSWM_VPS_PDU_BIT_5                   (BSW_BSWM_VPS_PDU_BIT_5)               /* Data position : bit5          */
#define BSWM_VPS_PDU_BIT_6                   (BSW_BSWM_VPS_PDU_BIT_6)               /* Data position : bit6          */
#define BSWM_VPS_PDU_BIT_7                   (BSW_BSWM_VPS_PDU_BIT_7)               /* Data position : bit7          */

#define BSWM_VPS_VPSINFO1                    (BSW_BSWM_VPS_VPSINFO1)                /* VPSINFO Bit value (for bit 0) */
#define BSWM_VPS_VPSINFO2                    (BSW_BSWM_VPS_VPSINFO2)                /* VPSINFO Bit value (for bit 1) */
#define BSWM_VPS_VPSINFO3                    (BSW_BSWM_VPS_VPSINFO3)                /* VPSINFO Bit value (for bit 2) */
#define BSWM_VPS_VPSINFO4                    (BSW_BSWM_VPS_VPSINFO4)                /* VPSINFO Bit value (for bit 3) */
#define BSWM_VPS_VPSINFO5                    (BSW_BSWM_VPS_VPSINFO5)                /* VPSINFO Bit value (for bit 4) */
#define BSWM_VPS_VPSINFO6                    (BSW_BSWM_VPS_VPSINFO6)                /* VPSINFO Bit value (for bit 5) */
#define BSWM_VPS_VPSINFO7                    (BSW_BSWM_VPS_VPSINFO7)                /* VPSINFO Bit value (for bit 6) */
#define BSWM_VPS_VPSINFO8                    (BSW_BSWM_VPS_VPSINFO8)                /* VPSINFO Bit value (for bit 7) */

#define BSWM_VPS_MSG_VPS                     (BSW_BSWM_VPS_MSG_VPS)                 /* Vehicle Power State */
#define BSWM_VPS_MSG_RLYONCONFREQ            (BSW_BSWM_VPS_MSG_RLYONCONFREQ)        /* RlyOnConf Request   */
#define BSWM_VPS_MSG_RLYONCONFRES            (BSW_BSWM_VPS_MSG_RLYONCONFRES)        /* RlyOnConf Response  */

#define BSWM_VPS_TRANSITION_REQ              (BSW_BSWM_VPS_TRANSITION_REQ)
#define BSWM_VPS_TRANSITION_NONE             (BSW_BSWM_VPS_TRANSITION_NONE)

#define BSWM_VPS_RLYONCONF_WKUP              (BSW_BSWM_VPS_RLYONCONF_WKUP)
#define BSWM_VPS_RLYONCONF_SLP               (BSW_BSWM_VPS_RLYONCONF_SLP)
#define BSWM_VPS_RLYONCONF_NONE              (BSW_BSWM_VPS_RLYONCONF_NONE)
#define BSWM_VPS_RLYONCONF_RESERVE           (BSW_BSWM_VPS_RLYONCONF_RESERVE)

#define BSWM_VPS_CHANNEL_00                  (BSW_BSWM_VPS_CHANNEL_00)
#define BSWM_VPS_CHANNEL_01                  (BSW_BSWM_VPS_CHANNEL_01)
#define BSWM_VPS_CHANNEL_02                  (BSW_BSWM_VPS_CHANNEL_02)
#define BSWM_VPS_CHANNEL_03                  (BSW_BSWM_VPS_CHANNEL_03)
#define BSWM_VPS_CHANNEL_04                  (BSW_BSWM_VPS_CHANNEL_04)
#define BSWM_VPS_CHANNEL_05                  (BSW_BSWM_VPS_CHANNEL_05)
#define BSWM_VPS_CHANNEL_06                  (BSW_BSWM_VPS_CHANNEL_06)
#define BSWM_VPS_CHANNEL_07                  (BSW_BSWM_VPS_CHANNEL_07)
#define BSWM_VPS_CHANNEL_08                  (BSW_BSWM_VPS_CHANNEL_08)
#define BSWM_VPS_CHANNEL_09                  (BSW_BSWM_VPS_CHANNEL_09)
#define BSWM_VPS_CHANNEL_10                  (BSW_BSWM_VPS_CHANNEL_10)
#define BSWM_VPS_CHANNEL_11                  (BSW_BSWM_VPS_CHANNEL_11)
#define BSWM_VPS_CHANNEL_12                  (BSW_BSWM_VPS_CHANNEL_12)
#define BSWM_VPS_CHANNEL_13                  (BSW_BSWM_VPS_CHANNEL_13)
#define BSWM_VPS_CHANNEL_14                  (BSW_BSWM_VPS_CHANNEL_14)
#define BSWM_VPS_CHANNEL_15                  (BSW_BSWM_VPS_CHANNEL_15)
#define BSWM_VPS_CHANNEL_16                  (BSW_BSWM_VPS_CHANNEL_16)
#define BSWM_VPS_CHANNEL_17                  (BSW_BSWM_VPS_CHANNEL_17)
#define BSWM_VPS_CHANNEL_18                  (BSW_BSWM_VPS_CHANNEL_18)
#define BSWM_VPS_CHANNEL_19                  (BSW_BSWM_VPS_CHANNEL_19)
#define BSWM_VPS_CHANNEL_20                  (BSW_BSWM_VPS_CHANNEL_20)
#define BSWM_VPS_CHANNEL_21                  (BSW_BSWM_VPS_CHANNEL_21)
#define BSWM_VPS_CHANNEL_22                  (BSW_BSWM_VPS_CHANNEL_22)
#define BSWM_VPS_CHANNEL_23                  (BSW_BSWM_VPS_CHANNEL_23)
#define BSWM_VPS_CHANNEL_24                  (BSW_BSWM_VPS_CHANNEL_24)
#define BSWM_VPS_CHANNEL_25                  (BSW_BSWM_VPS_CHANNEL_25)
#define BSWM_VPS_CHANNEL_26                  (BSW_BSWM_VPS_CHANNEL_26)
#define BSWM_VPS_CHANNEL_27                  (BSW_BSWM_VPS_CHANNEL_27)
#define BSWM_VPS_CHANNEL_28                  (BSW_BSWM_VPS_CHANNEL_28)
#define BSWM_VPS_CHANNEL_29                  (BSW_BSWM_VPS_CHANNEL_29)
#define BSWM_VPS_CHANNEL_30                  (BSW_BSWM_VPS_CHANNEL_30)
#define BSWM_VPS_CHANNEL_31                  (BSW_BSWM_VPS_CHANNEL_31)

#define BSWM_VPS_USERHANDLE_USRAWKNONE       (BSW_BSWM_VPS_USERHANDLE_USRAWKNONE)

#define BSWM_VPS_PDUID_INVALID               (BSW_BSWM_VPS_PDUID_INVALID)
#define BSWM_VPS_GLOBALBUS_INVALID           (BSW_BSWM_VPS_GLOBALBUS_INVALID)
#define BSWM_VPS_WF_INVALID                  (BSW_BSWM_VPS_WF_INVALID)

#define BSWM_VPS_ON                          (BSW_BSWM_VPS_ON)
#define BSWM_VPS_OFF                         (BSW_BSWM_VPS_OFF)

#define BswM_VPS_Init                        (bsw_bswm_vps_ctrl_Init)
#define BswM_VPS_DeInit                      (bsw_bswm_vps_ctrl_DeInit)
#define BswM_VPS_Wakeup                      (bsw_bswm_vps_ctrl_Wakeup)

#define BswM_VPS_MainFunction                (bsw_bswm_vps_ctrl_MainFunction)
#define BswM_VPS_SetSystemStatus             (bsw_bswm_vps_ctrl_SetSysStat)
#define BswM_VPS_GetSystemStatus             (bsw_bswm_vps_ctrl_GetSysStat)
#define BswM_VPS_GetRxSystemStatus           (bsw_bswm_vps_ctrl_GetRxSystemStatus)
#define BswM_VPS_SetWakeupFactor             (bsw_bswm_vps_ctrl_SetWakeupFactor)
#define BswM_VPS_StartStateHandling          (bsw_bswm_vps_ctrl_StartStateHandling)
#define BswM_VPS_StopStateHandling           (bsw_bswm_vps_ctrl_StopStatHdl)
#define BswM_VPS_SelectActiveBus             (bsw_bswm_vps_ctrl_SelectActiveBus)
#define BswM_VPS_GetHandlingState            (bsw_bswm_vps_ctrl_GetHandlingState)
#define BswM_VPS_GetRxHandlingState          (bsw_bswm_vps_ctrl_GetRxHandlingState)
#define BswM_VPS_FailInitSystemStatus        (bsw_bswm_vps_ctrl_FailInitSysSt)
#define BswM_VPS_ClearVPSTOutTim             (bsw_bswm_vps_ctrl_ClearVPSTOutTim)
#define BswM_VPS_DisableRxFixSystemStatus    (bsw_bswm_vps_ctrl_DisRxFixSysSt)
#define BswM_VPS_EnableRxFixSystemStatus     (bsw_bswm_vps_ctrl_EnaRxFixSysSt)

#define BswM_VPS_CbkRxSystemStatus           (bsw_bswm_vps_ctrl_CbkRxSystemStatus)
#define BswM_VPS_CbkErrorRx                  (bsw_bswm_vps_ctrl_CbkErrorRx)
#define BswM_VPS_CbkRxHandlingRequest        (bsw_bswm_vps_ctrl_CbkRxHdlReq)
#define BswM_VPS_CbkAllowResponse            (bsw_bswm_vps_ctrl_CbkAllowResponse)
#define BswM_VPS_CbkRxHandlingResponse       (bsw_bswm_vps_ctrl_CbkRxHdlRes)
#define BswM_VPS_CbkTimeoutHandling          (bsw_bswm_vps_ctrl_CbkTimeoutHandling)
#define BswM_VPS_CbkRxVPSTOut                (bsw_bswm_vps_ctrl_CbkRxVPSTOut)
#define BswM_VPS_CbkPreRxVPSMsg              (bsw_bswm_vps_ctrl_CbkPrRxVPSMsg)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif  /* BSW_BSWM_VPS_AR_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v3-0-0          :2025/01/21                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
