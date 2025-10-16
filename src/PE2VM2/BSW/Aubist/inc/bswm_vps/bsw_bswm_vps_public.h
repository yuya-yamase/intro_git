/* bsw_bswm_vps_public_h_v3-0-0                                             */
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
#define BSW_BSWM_VPS_PDU_BYTE_INVALID             (0xFFU)              /* Data position : INVALID       */
#define BSW_BSWM_VPS_PDU_BYTE_0                   (0x00U)              /* Data position : byte0         */
#define BSW_BSWM_VPS_PDU_BYTE_1                   (0x01U)              /* Data position : byte1         */
#define BSW_BSWM_VPS_PDU_BYTE_2                   (0x02U)              /* Data position : byte2         */
#define BSW_BSWM_VPS_PDU_BYTE_3                   (0x03U)              /* Data position : byte3         */
#define BSW_BSWM_VPS_PDU_BYTE_4                   (0x04U)              /* Data position : byte4         */
#define BSW_BSWM_VPS_PDU_BYTE_5                   (0x05U)              /* Data position : byte5         */
#define BSW_BSWM_VPS_PDU_BYTE_6                   (0x06U)              /* Data position : byte6         */
#define BSW_BSWM_VPS_PDU_BYTE_7                   (0x07U)              /* Data position : byte7         */
#define BSW_BSWM_VPS_PDU_BYTE_8                   (0x08U)              /* Data position : byte8         */
#define BSW_BSWM_VPS_PDU_BYTE_9                   (0x09U)              /* Data position : byte9         */
#define BSW_BSWM_VPS_PDU_BYTE_10                  (0x0AU)              /* Data position : byte10        */
#define BSW_BSWM_VPS_PDU_BYTE_11                  (0x0BU)              /* Data position : byte11        */
#define BSW_BSWM_VPS_PDU_BYTE_12                  (0x0CU)              /* Data position : byte12        */
#define BSW_BSWM_VPS_PDU_BYTE_13                  (0x0DU)              /* Data position : byte13        */
#define BSW_BSWM_VPS_PDU_BYTE_14                  (0x0EU)              /* Data position : byte14        */
#define BSW_BSWM_VPS_PDU_BYTE_15                  (0x0FU)              /* Data position : byte15        */
#define BSW_BSWM_VPS_PDU_BYTE_16                  (0x10U)              /* Data position : byte16        */
#define BSW_BSWM_VPS_PDU_BYTE_17                  (0x11U)              /* Data position : byte17        */
#define BSW_BSWM_VPS_PDU_BYTE_18                  (0x12U)              /* Data position : byte18        */
#define BSW_BSWM_VPS_PDU_BYTE_19                  (0x13U)              /* Data position : byte19        */
#define BSW_BSWM_VPS_PDU_BYTE_20                  (0x14U)              /* Data position : byte20        */
#define BSW_BSWM_VPS_PDU_BYTE_21                  (0x15U)              /* Data position : byte21        */
#define BSW_BSWM_VPS_PDU_BYTE_22                  (0x16U)              /* Data position : byte22        */
#define BSW_BSWM_VPS_PDU_BYTE_23                  (0x17U)              /* Data position : byte23        */
#define BSW_BSWM_VPS_PDU_BYTE_24                  (0x18U)              /* Data position : byte24        */
#define BSW_BSWM_VPS_PDU_BYTE_25                  (0x19U)              /* Data position : byte25        */
#define BSW_BSWM_VPS_PDU_BYTE_26                  (0x1AU)              /* Data position : byte26        */
#define BSW_BSWM_VPS_PDU_BYTE_27                  (0x1BU)              /* Data position : byte27        */
#define BSW_BSWM_VPS_PDU_BYTE_28                  (0x1CU)              /* Data position : byte28        */
#define BSW_BSWM_VPS_PDU_BYTE_29                  (0x1DU)              /* Data position : byte29        */
#define BSW_BSWM_VPS_PDU_BYTE_30                  (0x1EU)              /* Data position : byte30        */
#define BSW_BSWM_VPS_PDU_BYTE_31                  (0x1FU)              /* Data position : byte31        */
#define BSW_BSWM_VPS_PDU_BYTE_32                  (0x20U)              /* Data position : byte32        */
#define BSW_BSWM_VPS_PDU_BYTE_33                  (0x21U)              /* Data position : byte33        */
#define BSW_BSWM_VPS_PDU_BYTE_34                  (0x22U)              /* Data position : byte34        */
#define BSW_BSWM_VPS_PDU_BYTE_35                  (0x23U)              /* Data position : byte35        */
#define BSW_BSWM_VPS_PDU_BYTE_36                  (0x24U)              /* Data position : byte36        */
#define BSW_BSWM_VPS_PDU_BYTE_37                  (0x25U)              /* Data position : byte37        */
#define BSW_BSWM_VPS_PDU_BYTE_38                  (0x26U)              /* Data position : byte38        */
#define BSW_BSWM_VPS_PDU_BYTE_39                  (0x27U)              /* Data position : byte39        */
#define BSW_BSWM_VPS_PDU_BYTE_40                  (0x28U)              /* Data position : byte40        */
#define BSW_BSWM_VPS_PDU_BYTE_41                  (0x29U)              /* Data position : byte41        */
#define BSW_BSWM_VPS_PDU_BYTE_42                  (0x2AU)              /* Data position : byte42        */
#define BSW_BSWM_VPS_PDU_BYTE_43                  (0x2BU)              /* Data position : byte43        */
#define BSW_BSWM_VPS_PDU_BYTE_44                  (0x2CU)              /* Data position : byte44        */
#define BSW_BSWM_VPS_PDU_BYTE_45                  (0x2DU)              /* Data position : byte45        */
#define BSW_BSWM_VPS_PDU_BYTE_46                  (0x2EU)              /* Data position : byte46        */
#define BSW_BSWM_VPS_PDU_BYTE_47                  (0x2FU)              /* Data position : byte47        */
#define BSW_BSWM_VPS_PDU_BYTE_48                  (0x30U)              /* Data position : byte48        */
#define BSW_BSWM_VPS_PDU_BYTE_49                  (0x31U)              /* Data position : byte49        */
#define BSW_BSWM_VPS_PDU_BYTE_50                  (0x32U)              /* Data position : byte50        */
#define BSW_BSWM_VPS_PDU_BYTE_51                  (0x33U)              /* Data position : byte51        */
#define BSW_BSWM_VPS_PDU_BYTE_52                  (0x34U)              /* Data position : byte52        */
#define BSW_BSWM_VPS_PDU_BYTE_53                  (0x35U)              /* Data position : byte53        */
#define BSW_BSWM_VPS_PDU_BYTE_54                  (0x36U)              /* Data position : byte54        */
#define BSW_BSWM_VPS_PDU_BYTE_55                  (0x37U)              /* Data position : byte55        */
#define BSW_BSWM_VPS_PDU_BYTE_56                  (0x38U)              /* Data position : byte56        */
#define BSW_BSWM_VPS_PDU_BYTE_57                  (0x39U)              /* Data position : byte57        */
#define BSW_BSWM_VPS_PDU_BYTE_58                  (0x3AU)              /* Data position : byte58        */
#define BSW_BSWM_VPS_PDU_BYTE_59                  (0x3BU)              /* Data position : byte59        */
#define BSW_BSWM_VPS_PDU_BYTE_60                  (0x3CU)              /* Data position : byte60        */
#define BSW_BSWM_VPS_PDU_BYTE_61                  (0x3DU)              /* Data position : byte61        */
#define BSW_BSWM_VPS_PDU_BYTE_62                  (0x3EU)              /* Data position : byte62        */
#define BSW_BSWM_VPS_PDU_BYTE_63                  (0x3FU)              /* Data position : byte63        */

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

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void                    bsw_bswm_vps_ctrl_Init( void );
void                    bsw_bswm_vps_ctrl_DeInit( void );
void                    bsw_bswm_vps_ctrl_Wakeup( void );
void                    bsw_bswm_vps_ctrl_MainFunction( void );
void                    bsw_bswm_vps_ctrl_SetSysStat( BswConstR uint32* Mask, BswConstR uint32* SysStatus );
void                    bsw_bswm_vps_ctrl_SetWakeupFactor( uint16 Factor, uint8 State );
Std_ReturnType          bsw_bswm_vps_ctrl_StartStateHandling( uint8 Kind );
void                    bsw_bswm_vps_ctrl_StopStatHdl( void );

void                    bsw_bswm_vps_ctrl_GetRxSystemStatus( NetworkHandleType Network, uint32* SysStatus );
void                    bsw_bswm_vps_ctrl_GetSysStat( uint32* SysStatus );

void                    bsw_bswm_vps_ctrl_MainFuncCoBus( void );
boolean                 bsw_bswm_vps_ctrl_RxIndication( PduIdType PduId, BswConstR PduInfoType* PduInfoPtr );
void                    bsw_bswm_vps_ctrl_TxConf( PduIdType TxPduId );
void                    bsw_bswm_vps_ctrl_TxReqConf( PduIdType TxPduId );
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

void                    bsw_bswm_vps_ctrl_CbkRxSystemStatus( NetworkHandleType Network, BswConstR uint32* SysStatus, uint8 HandlingState );
void                    bsw_bswm_vps_ctrl_CbkErrorRx( NetworkHandleType Network, PduIdType PduId );
void                    bsw_bswm_vps_ctrl_CbkRxHdlReq( NetworkHandleType Network, uint8 State );
Std_ReturnType          bsw_bswm_vps_ctrl_CbkAllowResponse( NetworkHandleType Network, uint8 State );
void                    bsw_bswm_vps_ctrl_CbkRxHdlRes( NetworkHandleType Network, uint8 State, PduIdType PduId );
void                    bsw_bswm_vps_ctrl_CbkTimeoutHandling( void );
void                    bsw_bswm_vps_ctrl_CbkRxVPSTOut( NetworkHandleType Network );
boolean                 bsw_bswm_vps_ctrl_CbkPrRxVPSMsg( NetworkHandleType Network, PduIdType PduId, BswConstR uint8 *ptMsg );

void                    bsw_bswm_vps_ctrl_InitCS( void );
void                    bsw_bswm_vps_ctrl_DeInitCS( void );
void                    bsw_bswm_vps_ctrl_WakeupCS( void );
void                    bsw_bswm_vps_ctrl_MainFuncCS( void );
void                    bsw_bswm_vps_ctrl_GetWuSystemStatusCS( uint32* SysStatus );
void                    bsw_bswm_vps_ctrl_SetSysStatCS( BswConstR uint32* Mask, BswConstR uint32* SysStatus );
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
/*  v3-0-0          :2025/02/24                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
