/* bsw_bswm_vps_public_h_v3-0-9                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/BSWM/VPS/PUBLIC/HEADER                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_BSWM_VPS_PUBLIC_H
#define BSW_BSWM_VPS_PUBLIC_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define BSW_BSWM_VPS_PDU_BYTE_0                   (0x00U)              /* Data position : byte0         */
#define BSW_BSWM_VPS_PDU_BYTE_1                   (0x01U)              /* Data position : byte1         */
#define BSW_BSWM_VPS_PDU_BYTE_2                   (0x02U)              /* Data position : byte2         */
#define BSW_BSWM_VPS_PDU_BYTE_3                   (0x03U)              /* Data position : byte3         */
#define BSW_BSWM_VPS_PDU_BYTE_4                   (0x04U)              /* Data position : byte4         */
#define BSW_BSWM_VPS_PDU_BYTE_5                   (0x05U)              /* Data position : byte5         */
#define BSW_BSWM_VPS_PDU_BYTE_6                   (0x06U)              /* Data position : byte6         */
#define BSW_BSWM_VPS_PDU_BYTE_7                   (0x07U)              /* Data position : byte7         */

#define BSW_BSWM_VPS_PDU_BIT_0                    (0x00U)              /* Data position : bit0          */
#define BSW_BSWM_VPS_PDU_BIT_1                    (0x01U)              /* Data position : bit1          */
#define BSW_BSWM_VPS_PDU_BIT_2                    (0x02U)              /* Data position : bit2          */
#define BSW_BSWM_VPS_PDU_BIT_3                    (0x03U)              /* Data position : bit3          */
#define BSW_BSWM_VPS_PDU_BIT_4                    (0x04U)              /* Data position : bit4          */
#define BSW_BSWM_VPS_PDU_BIT_5                    (0x05U)              /* Data position : bit5          */
#define BSW_BSWM_VPS_PDU_BIT_6                    (0x06U)              /* Data position : bit6          */
#define BSW_BSWM_VPS_PDU_BIT_7                    (0x07U)              /* Data position : bit7          */

#define BSW_BSWM_VPS_VPSINFO1                     (0x01U)              /* VPSINFO Bit value (for bit 0) */
#define BSW_BSWM_VPS_VPSINFO2                     (0x02U)              /* VPSINFO Bit value (for bit 1) */
#define BSW_BSWM_VPS_VPSINFO3                     (0x04U)              /* VPSINFO Bit value (for bit 2) */
#define BSW_BSWM_VPS_VPSINFO4                     (0x08U)              /* VPSINFO Bit value (for bit 3) */
#define BSW_BSWM_VPS_VPSINFO5                     (0x10U)              /* VPSINFO Bit value (for bit 4) */
#define BSW_BSWM_VPS_VPSINFO6                     (0x20U)              /* VPSINFO Bit value (for bit 5) */
#define BSW_BSWM_VPS_VPSINFO7                     (0x40U)              /* VPSINFO Bit value (for bit 6) */
#define BSW_BSWM_VPS_VPSINFO8                     (0x80U)              /* VPSINFO Bit value (for bit 7) */

#define BSW_BSWM_VPS_KIND_VPS                     (0x00U)              /* VPS Kind : VPS */
#define BSW_BSWM_VPS_KIND_VPSSP                   (0x01U)              /* VPS Kind : VPS Special */

#define BSW_BSWM_VPS_MSG_VPS             (0x00U)    /* Vehicle Power State */
#define BSW_BSWM_VPS_MSG_RLYONCONFREQ    (0x01U)    /* RlyOnConf Request   */
#define BSW_BSWM_VPS_MSG_RLYONCONFRES    (0x02U)    /* RlyOnConf Response  */

#define BSW_BSWM_VPS_TRANSITION_NONE           (0x00U)
#define BSW_BSWM_VPS_TRANSITION_REQ            (0x01U)

#define BSW_BSWM_VPS_RLYONCONF_WKUP            (0x00U)
#define BSW_BSWM_VPS_RLYONCONF_SLP             (0x01U)
#define BSW_BSWM_VPS_RLYONCONF_NONE            (0x02U)
#define BSW_BSWM_VPS_RLYONCONF_RESERVE         (0x03U)

#define BSW_BSWM_VPS_CHANNEL_00                (0U)
#define BSW_BSWM_VPS_CHANNEL_01                (1U)
#define BSW_BSWM_VPS_CHANNEL_02                (2U)
#define BSW_BSWM_VPS_CHANNEL_03                (3U)
#define BSW_BSWM_VPS_CHANNEL_04                (4U)
#define BSW_BSWM_VPS_CHANNEL_05                (5U)
#define BSW_BSWM_VPS_CHANNEL_06                (6U)
#define BSW_BSWM_VPS_CHANNEL_07                (7U)
#define BSW_BSWM_VPS_CHANNEL_08                (8U)
#define BSW_BSWM_VPS_CHANNEL_09                (9U)
#define BSW_BSWM_VPS_CHANNEL_10                (10U)
#define BSW_BSWM_VPS_CHANNEL_11                (11U)
#define BSW_BSWM_VPS_CHANNEL_12                (12U)
#define BSW_BSWM_VPS_CHANNEL_13                (13U)
#define BSW_BSWM_VPS_CHANNEL_14                (14U)
#define BSW_BSWM_VPS_CHANNEL_15                (15U)
#define BSW_BSWM_VPS_CHANNEL_16                (16U)
#define BSW_BSWM_VPS_CHANNEL_17                (17U)
#define BSW_BSWM_VPS_CHANNEL_18                (18U)
#define BSW_BSWM_VPS_CHANNEL_19                (19U)
#define BSW_BSWM_VPS_CHANNEL_20                (20U)
#define BSW_BSWM_VPS_CHANNEL_21                (21U)
#define BSW_BSWM_VPS_CHANNEL_22                (22U)
#define BSW_BSWM_VPS_CHANNEL_23                (23U)
#define BSW_BSWM_VPS_CHANNEL_24                (24U)
#define BSW_BSWM_VPS_CHANNEL_25                (25U)
#define BSW_BSWM_VPS_CHANNEL_26                (26U)
#define BSW_BSWM_VPS_CHANNEL_27                (27U)
#define BSW_BSWM_VPS_CHANNEL_28                (28U)
#define BSW_BSWM_VPS_CHANNEL_29                (29U)
#define BSW_BSWM_VPS_CHANNEL_30                (30U)
#define BSW_BSWM_VPS_CHANNEL_31                (31U)

#define BSW_BSWM_VPS_USERHANDLE_USRAWKNONE     (0xFFU)

#define BSW_BSWM_VPS_PDUID_INVALID             (0xFFFFU)
#define BSW_BSWM_VPS_GLOBALBUS_INVALID         (0xFFU)
#define BSW_BSWM_VPS_WF_INVALID                (0xFFU)

#define BSW_BSWM_VPS_ON                        (0U)
#define BSW_BSWM_VPS_OFF                       (1U)

#define BSW_BSWM_VPS_ACTIVEBUS_NONE            (0xFFU)
/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct
{
    BswU2 u2RlyOnConfTimer;
    BswU2 u2WfChgVPSTimer;
    BswU2 u2WfResetTimer;
    BswU2 u2WfRxPncTimer;
    BswU1 u1RlyOnConfTimerOn;
    BswU1 u1WfChgVPSTimerOn;
    BswU1 u1WfResetTimerOn;
    BswU1 u1WfRxPncTimerOn;
    BswU1 u1SetSysStEvnt;
    BswU1 u1VhPwStSpTransSt;
    BswU1 u1ActiveBus;
    BswU1 u1SetSysStatReq;
    BswU1 u1RxSysStChng;
    BswU1 u1RlyOnConfKind;
    BswU1 u1RxTransSt0;
    BswU1 u1RxTransSt1;
    BswU1 u1RxVPSFixSt;
    BswU1 u1DummyPad0;
} Bsw_BswM_VPS_StsType;

typedef struct
{
    BswU2 u2RxVPSStatus;
    BswU2 u2RxVPSTimer;
    BswU1 u1RxVPSTimerOn;
    BswU1 u1DummyPad;
} Bsw_BswM_RxVPS_StsType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void                    bsw_bswm_vps_ctrl_Init( void );
void                    bsw_bswm_vps_ctrl_DeInit( void );
void                    bsw_bswm_vps_ctrl_Wakeup( void );
void                    bsw_bswm_vps_ctrl_MainFunction( void );
void                    bsw_bswm_vps_ctrl_SetSysStat( uint32* Mask, uint32* SysStatus );
void                    bsw_bswm_vps_ctrl_SetWakeupFactor( uint16 Factor, uint8 State );
Std_ReturnType          bsw_bswm_vps_ctrl_StartStateHandling( uint8 Kind );
void                    bsw_bswm_vps_ctrl_StopStatHdl( void );

void                    bsw_bswm_vps_ctrl_GetRxSystemStatus( NetworkHandleType Network, uint32* SysStatus );
void                    bsw_bswm_vps_ctrl_GetSysStat( uint32* SysStatus );

void                    bsw_bswm_vps_ctrl_MainFuncCoBus( void );
void                    bsw_bswm_vps_ctrl_RxIndication( PduIdType PduId );
void                    bsw_bswm_vps_ctrl_StartNetwork( NetworkHandleType Network );
void                    bsw_bswm_vps_ctrl_NmRxIndication( NetworkHandleType Network, BswConstR PduInfoType* PduInfoPtr );
void                    bsw_bswm_vps_ctrl_TxIpduCallout( PduIdType PduId, PduInfoType* PduInfoPtr );

Std_ReturnType          bsw_bswm_vps_ctrl_SelectActiveBus( NetworkHandleType Network );
uint8                   bsw_bswm_vps_ctrl_GetHandlingState( void );
uint8                   bsw_bswm_vps_ctrl_GetRxHandlingState( NetworkHandleType Network );
void                    bsw_bswm_vps_ctrl_FailInitSysSt( void );
Std_ReturnType          bsw_bswm_vps_ctrl_ClearVPSTOutTim( NetworkHandleType Network );
void                    bsw_bswm_vps_ctrl_DisRxFixSysSt( void );
void                    bsw_bswm_vps_ctrl_EnaRxFixSysSt( void );

void                    bsw_bswm_vps_ctrl_CbkRxSystemStatus( NetworkHandleType Network, uint32* SysStatus, uint8 HandlingState );
void                    bsw_bswm_vps_ctrl_CbkErrorRx( NetworkHandleType Network, PduIdType PduId );
void                    bsw_bswm_vps_ctrl_CbkRxHdlReq( NetworkHandleType Network, uint8 State );
boolean                 bsw_bswm_vps_ctrl_CbkAllowResponse( NetworkHandleType Network, uint8 State );
void                    bsw_bswm_vps_ctrl_CbkRxHdlRes( NetworkHandleType Network, uint8 State, PduIdType PduId );
void                    bsw_bswm_vps_ctrl_CbkTimeoutHandling( void );
void                    bsw_bswm_vps_ctrl_CbkRxVPSTOut( NetworkHandleType Network );

void                    bsw_bswm_vps_ctrl_InitCS( void );
void                    bsw_bswm_vps_ctrl_DeInitCS( void );
void                    bsw_bswm_vps_ctrl_WakeupCS( void );
void                    bsw_bswm_vps_ctrl_MainFuncCS( void );
void                    bsw_bswm_vps_ctrl_GetWuSystemStatusCS( uint32* SysStatus );
void                    bsw_bswm_vps_ctrl_SetSysStatCS( uint32* Mask, uint32* SysStatus );
void                    bsw_bswm_vps_ctrl_ChkSysStatRam( void );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* BSW_BSWM_VPS_PUBLIC_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v3-0-0          :2024/11/13                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
