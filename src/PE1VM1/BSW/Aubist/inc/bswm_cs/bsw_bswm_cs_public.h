/* bsw_bswm_cs_public_h_v3-0-0                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/BSWM/CS/PUBLIC/HEADER                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_BSWM_CS_PUBLIC_H
#define BSW_BSWM_CS_PUBLIC_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* XCP Kind                     */
#define BSW_BSWM_CS_XCP_KIND_NONE              (0x00U)
#define BSW_BSWM_CS_XCP_KIND_CAN               (0x01U)
#define BSW_BSWM_CS_XCP_KIND_LIN               (0x02U)
#define BSW_BSWM_CS_XCP_KIND_ETH               (0x03U)

/*------------------------------*/
/* Unit:status                  */
/*------------------------------*/
/* CS Status                    */
#define BSW_BSWM_CS_CSST_RUN                   (0x01U)
#define BSW_BSWM_CS_CSST_UNINIT                (0x02U)

/* Receive enable type of PNC I-PDU control */
#define BSW_BSWM_CS_PNCIPDU_RXTYPE_CH          (0x00U)
#define BSW_BSWM_CS_PNCIPDU_RXTYPE_PNC         (0x01U)

/*------------------------------*/
/* Unit:sysstat                 */
/*------------------------------*/
/* System Status                */
#define BSW_BSWM_CS_SYSSTAT_NONE               (0x00000000UL)
#define BSW_BSWM_CS_SYSSTAT_BAT                (0x00000001UL)
#define BSW_BSWM_CS_SYSSTAT_ACC                (0x00000002UL)
#define BSW_BSWM_CS_SYSSTAT_IG                 (0x00000004UL)
#define BSW_BSWM_CS_SYSSTAT_USER1              (0x00000008UL)
#define BSW_BSWM_CS_SYSSTAT_USER2              (0x00000010UL)
#define BSW_BSWM_CS_SYSSTAT_USER3              (0x00000020UL)
#define BSW_BSWM_CS_SYSSTAT_USER4              (0x00000040UL)
#define BSW_BSWM_CS_SYSSTAT_USER5              (0x00000080UL)
#define BSW_BSWM_CS_SYSSTAT_USER6              (0x00000100UL)
#define BSW_BSWM_CS_SYSSTAT_USER7              (0x00000200UL)
#define BSW_BSWM_CS_SYSSTAT_USER8              (0x00000400UL)
#define BSW_BSWM_CS_SYSSTAT_USER9              (0x00000800UL)
#define BSW_BSWM_CS_SYSSTAT_USER10             (0x00001000UL)
#define BSW_BSWM_CS_SYSSTAT_USER11             (0x00002000UL)
#define BSW_BSWM_CS_SYSSTAT_USER12             (0x00004000UL)
#define BSW_BSWM_CS_SYSSTAT_USER13             (0x00008000UL)
#define BSW_BSWM_CS_SYSSTAT_USER14             (0x00010000UL)
#define BSW_BSWM_CS_SYSSTAT_USER15             (0x00020000UL)
#define BSW_BSWM_CS_SYSSTAT_USER16             (0x00040000UL)
#define BSW_BSWM_CS_SYSSTAT_USER17             (0x00080000UL)
#define BSW_BSWM_CS_SYSSTAT_USER18             (0x00100000UL)
#define BSW_BSWM_CS_SYSSTAT_USER19             (0x00200000UL)
#define BSW_BSWM_CS_SYSSTAT_USER20             (0x00400000UL)
#define BSW_BSWM_CS_SYSSTAT_USER21             (0x00800000UL)
#define BSW_BSWM_CS_SYSSTAT_USER22             (0x01000000UL)
#define BSW_BSWM_CS_SYSSTAT_USER23             (0x02000000UL)
#define BSW_BSWM_CS_SYSSTAT_USER24             (0x04000000UL)
#define BSW_BSWM_CS_SYSSTAT_USER25             (0x08000000UL)
#define BSW_BSWM_CS_SYSSTAT_USER26             (0x10000000UL)
#define BSW_BSWM_CS_SYSSTAT_USER27             (0x20000000UL)
#define BSW_BSWM_CS_SYSSTAT_USER28             (0x40000000UL)
#define BSW_BSWM_CS_SYSSTAT_USER29             (0x80000000UL)
#define BSW_BSWM_CS_SYSSTAT_USER30             (0x00000001UL)
#define BSW_BSWM_CS_SYSSTAT_USER31             (0x00000002UL)
#define BSW_BSWM_CS_SYSSTAT_USER32             (0x00000004UL)
#define BSW_BSWM_CS_SYSSTAT_USER33             (0x00000008UL)
#define BSW_BSWM_CS_SYSSTAT_USER34             (0x00000010UL)
#define BSW_BSWM_CS_SYSSTAT_USER35             (0x00000020UL)
#define BSW_BSWM_CS_SYSSTAT_USER36             (0x00000040UL)
#define BSW_BSWM_CS_SYSSTAT_USER37             (0x00000080UL)
#define BSW_BSWM_CS_SYSSTAT_USER38             (0x00000100UL)
#define BSW_BSWM_CS_SYSSTAT_USER39             (0x00000200UL)
#define BSW_BSWM_CS_SYSSTAT_USER40             (0x00000400UL)
#define BSW_BSWM_CS_SYSSTAT_USER41             (0x00000800UL)
#define BSW_BSWM_CS_SYSSTAT_USER42             (0x00001000UL)
#define BSW_BSWM_CS_SYSSTAT_USER43             (0x00002000UL)
#define BSW_BSWM_CS_SYSSTAT_USER44             (0x00004000UL)
#define BSW_BSWM_CS_SYSSTAT_USER45             (0x00008000UL)
#define BSW_BSWM_CS_SYSSTAT_USER46             (0x00010000UL)
#define BSW_BSWM_CS_SYSSTAT_USER47             (0x00020000UL)
#define BSW_BSWM_CS_SYSSTAT_USER48             (0x00040000UL)
#define BSW_BSWM_CS_SYSSTAT_USER49             (0x00080000UL)
#define BSW_BSWM_CS_SYSSTAT_USER50             (0x00100000UL)
#define BSW_BSWM_CS_SYSSTAT_USER51             (0x00200000UL)
#define BSW_BSWM_CS_SYSSTAT_USER52             (0x00400000UL)
#define BSW_BSWM_CS_SYSSTAT_USER53             (0x00800000UL)
#define BSW_BSWM_CS_SYSSTAT_USER54             (0x01000000UL)
#define BSW_BSWM_CS_SYSSTAT_USER55             (0x02000000UL)
#define BSW_BSWM_CS_SYSSTAT_USER56             (0x04000000UL)
#define BSW_BSWM_CS_SYSSTAT_USER57             (0x08000000UL)
#define BSW_BSWM_CS_SYSSTAT_USER58             (0x10000000UL)
#define BSW_BSWM_CS_SYSSTAT_USER59             (0x20000000UL)
#define BSW_BSWM_CS_SYSSTAT_USER60             (0x40000000UL)
#define BSW_BSWM_CS_SYSSTAT_USER61             (0x80000000UL)

/* System Status Mask Bit       */
#define BSW_BSWM_CS_SYSSTAT_MASK_BAT           (BSW_BSWM_CS_SYSSTAT_BAT)
#define BSW_BSWM_CS_SYSSTAT_MASK_ACC           (BSW_BSWM_CS_SYSSTAT_ACC)
#define BSW_BSWM_CS_SYSSTAT_MASK_IG            (BSW_BSWM_CS_SYSSTAT_IG)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER1         (BSW_BSWM_CS_SYSSTAT_USER1)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER2         (BSW_BSWM_CS_SYSSTAT_USER2)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER3         (BSW_BSWM_CS_SYSSTAT_USER3)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER4         (BSW_BSWM_CS_SYSSTAT_USER4)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER5         (BSW_BSWM_CS_SYSSTAT_USER5)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER6         (BSW_BSWM_CS_SYSSTAT_USER6)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER7         (BSW_BSWM_CS_SYSSTAT_USER7)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER8         (BSW_BSWM_CS_SYSSTAT_USER8)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER9         (BSW_BSWM_CS_SYSSTAT_USER9)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER10        (BSW_BSWM_CS_SYSSTAT_USER10)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER11        (BSW_BSWM_CS_SYSSTAT_USER11)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER12        (BSW_BSWM_CS_SYSSTAT_USER12)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER13        (BSW_BSWM_CS_SYSSTAT_USER13)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER14        (BSW_BSWM_CS_SYSSTAT_USER14)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER15        (BSW_BSWM_CS_SYSSTAT_USER15)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER16        (BSW_BSWM_CS_SYSSTAT_USER16)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER17        (BSW_BSWM_CS_SYSSTAT_USER17)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER18        (BSW_BSWM_CS_SYSSTAT_USER18)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER19        (BSW_BSWM_CS_SYSSTAT_USER19)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER20        (BSW_BSWM_CS_SYSSTAT_USER20)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER21        (BSW_BSWM_CS_SYSSTAT_USER21)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER22        (BSW_BSWM_CS_SYSSTAT_USER22)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER23        (BSW_BSWM_CS_SYSSTAT_USER23)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER24        (BSW_BSWM_CS_SYSSTAT_USER24)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER25        (BSW_BSWM_CS_SYSSTAT_USER25)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER26        (BSW_BSWM_CS_SYSSTAT_USER26)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER27        (BSW_BSWM_CS_SYSSTAT_USER27)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER28        (BSW_BSWM_CS_SYSSTAT_USER28)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER29        (BSW_BSWM_CS_SYSSTAT_USER29)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER30        (BSW_BSWM_CS_SYSSTAT_USER30)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER31        (BSW_BSWM_CS_SYSSTAT_USER31)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER32        (BSW_BSWM_CS_SYSSTAT_USER32)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER33        (BSW_BSWM_CS_SYSSTAT_USER33)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER34        (BSW_BSWM_CS_SYSSTAT_USER34)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER35        (BSW_BSWM_CS_SYSSTAT_USER35)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER36        (BSW_BSWM_CS_SYSSTAT_USER36)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER37        (BSW_BSWM_CS_SYSSTAT_USER37)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER38        (BSW_BSWM_CS_SYSSTAT_USER38)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER39        (BSW_BSWM_CS_SYSSTAT_USER39)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER40        (BSW_BSWM_CS_SYSSTAT_USER40)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER41        (BSW_BSWM_CS_SYSSTAT_USER41)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER42        (BSW_BSWM_CS_SYSSTAT_USER42)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER43        (BSW_BSWM_CS_SYSSTAT_USER43)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER44        (BSW_BSWM_CS_SYSSTAT_USER44)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER45        (BSW_BSWM_CS_SYSSTAT_USER45)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER46        (BSW_BSWM_CS_SYSSTAT_USER46)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER47        (BSW_BSWM_CS_SYSSTAT_USER47)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER48        (BSW_BSWM_CS_SYSSTAT_USER48)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER49        (BSW_BSWM_CS_SYSSTAT_USER49)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER50        (BSW_BSWM_CS_SYSSTAT_USER50)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER51        (BSW_BSWM_CS_SYSSTAT_USER51)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER52        (BSW_BSWM_CS_SYSSTAT_USER52)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER53        (BSW_BSWM_CS_SYSSTAT_USER53)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER54        (BSW_BSWM_CS_SYSSTAT_USER54)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER55        (BSW_BSWM_CS_SYSSTAT_USER55)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER56        (BSW_BSWM_CS_SYSSTAT_USER56)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER57        (BSW_BSWM_CS_SYSSTAT_USER57)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER58        (BSW_BSWM_CS_SYSSTAT_USER58)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER59        (BSW_BSWM_CS_SYSSTAT_USER59)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER60        (BSW_BSWM_CS_SYSSTAT_USER60)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER61        (BSW_BSWM_CS_SYSSTAT_USER61)

/* Number of System Status      */
#define BSW_BSWM_CS_SYSSTAT_NUM                ((uint8)64U)
#define BSW_BSWM_CS_SYSSTATTBLNUM              (BSW_BSWM_CS_SYSSTAT_NUM >> 5U)

/*------------------------------*/
/* Unit:ctrl                    */
/*------------------------------*/
/* CPU Awake Factor             */
#define BSW_BSWM_CS_AWAKE_NONE                 (0x00U)
#define BSW_BSWM_CS_AWAKE_EXIST                (0xFFU)

/* Message Deliver              */
#define BSW_BSWM_CS_MSGDELIVER_HIGH            (0x01U)
#define BSW_BSWM_CS_MSGDELIVER_MIDDLE          (0x02U)

/* Event transmission Status    */
#define BSW_BSWM_CS_EVTX_OK                    (0x00U)
#define BSW_BSWM_CS_EVTX_WAIT                  (0x01U)

/* Return code                  */
#define BSW_BSWM_CS_RET_OK                     ((Bsw_BswM_CS_RetCtrlType)(0x00U))
#define BSW_BSWM_CS_RET_INVALID                ((Bsw_BswM_CS_RetCtrlType)(0x11U))
#define BSW_BSWM_CS_RET_TXSTOP                 ((Bsw_BswM_CS_RetCtrlType)(0x12U))
#define BSW_BSWM_CS_RET_TXRUN                  ((Bsw_BswM_CS_RetCtrlType)(0x13U))
#define BSW_BSWM_CS_RET_DMSTOP                 ((Bsw_BswM_CS_RetCtrlType)(0x14U))
#define BSW_BSWM_CS_RET_DMRUN                  ((Bsw_BswM_CS_RetCtrlType)(0x15U))

/* Com transmission Status      */
#define BSW_BSWM_CS_COM_TX_DISABLE             (0x00U)
#define BSW_BSWM_CS_COM_PERI_TX_ENABLE         (0x01U)
#define BSW_BSWM_CS_COM_EV_TX_ENABLE           (0x02U)

/* XCP transmission mode        */
#define BSW_BSWM_CS_XCPMODE_OFF                (0x00U)
#define BSW_BSWM_CS_XCPMODE_ON                 (0xFFU)

/* Control method of transmission limiting function */
#define BSW_BSWM_CS_TXCTRL_NOUSE               (0x00U)
#define BSW_BSWM_CS_TXCTRL_STOPALL             (BSW_BSWM_CS_TXCTRL_STOPEV|BSW_BSWM_CS_TXCTRL_STOPPRD)
#define BSW_BSWM_CS_TXCTRL_STOPEV              (0x01U)
#define BSW_BSWM_CS_TXCTRL_STOPPRD             (0x02U)
#define BSW_BSWM_CS_TXCTRL_CYCCHG              (0x04U)

/* Send and Receive Status */
#define BSW_BSWM_CS_TRXST_TRX_ENABLE           (0x03U)
#define BSW_BSWM_CS_TRXST_TRX_DISABLE          (0x00U)
#define BSW_BSWM_CS_TRXST_RX_ENABLE            (0x01U)

/* Transmission request clear object */
#define BSW_BSWM_CS_COM_TX_MODE_ALL             (BSW_BSWM_CS_COM_TX_MODE_PERIODIC| BSW_BSWM_CS_COM_TX_MODE_EVENT)
#define BSW_BSWM_CS_COM_TX_MODE_EVENT           (0x01U)
#define BSW_BSWM_CS_COM_TX_MODE_PERIODIC        (0x02U)
#define BSW_BSWM_CS_COM_TX_MODE_INVALID         (0x00U)

/* Channel Invalid              */
#define BSW_BSWM_CS_CHANNEL_INVALID            (0xFFU)

/* Component ID                 */
#define BSW_BSWM_CS_UPCOMP_COM                 (0x0000U)
#define BSW_BSWM_CS_UPCOMP_CDD1                (0x1800U)
#define BSW_BSWM_CS_UPCOMP_CDD2                (0x2000U)

/* Message authentication pattern for MultiplexerPDU */
#define BSW_BSWM_CS_MUX_MA_MSG                 (0x00U)
#define BSW_BSWM_CS_MUX_MA_MUXPDU              (0x01U)
#define BSW_BSWM_CS_MUX_MA_MSG_MUXPDU          (0x02U)
#define BSW_BSWM_CS_MUX_MA_NONE                (0xFFU)

/* Wakeup Type */
#define BSW_BSWM_CS_WKUP_PWON                  (0x01U)
#define BSW_BSWM_CS_WKUP_BS                    (0x02U)

/* Periodic Tx Reset Reason */
#define BSW_BSWM_CS_RSTR_BUSWAKEUP             (0x01U)
#define BSW_BSWM_CS_RSTR_RESUMETX              (0x02U)

/* success or failure of channel power on wakeup */
#define BSW_BSWM_CS_WKUP_CHPW_ON               (0x00U)
#define BSW_BSWM_CS_WKUP_CHPW_OFF              (0xFFU)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef uint8           Bsw_BswM_CS_RetCtrlType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*------------------------------*/
/* Unit:status                  */
/*------------------------------*/
void                    bsw_bswm_cs_st_Init( void );
void                    bsw_bswm_cs_st_PrepareDeInit( void );
void                    bsw_bswm_cs_st_DeInit( void );
void                    bsw_bswm_cs_st_Wakeup( void );
void                    bsw_bswm_cs_st_Sleep( void );
void                    bsw_bswm_cs_st_Reset( void );
void                    bsw_bswm_cs_st_MainFunctionHigh( void );
void                    bsw_bswm_cs_st_MainFunctionMid( void );
void                    bsw_bswm_cs_st_DetectFail( void );
uint8                   bsw_bswm_cs_st_GetClockProv( void );
uint8                   bsw_bswm_cs_st_GetStatus( void );
void                    bsw_bswm_cs_st_ReqProvideClock( void );

/*------------------------------*/
/* Unit:sysstat                 */
/*------------------------------*/
void                    bsw_bswm_cs_sysst_SetSysStat( uint32 Mask, uint32 SysStatus );
void                    bsw_bswm_cs_sysst_SetSysStatExt( uint32* Mask, uint32* SysStatus );
uint8                   bsw_bswm_cs_sysst_GetSysStat( void );
void                    bsw_bswm_cs_sysst_GetSysStatExt( uint32* SysStatus );
uint32                  bsw_bswm_cs_sysst_GetLatSysStat( void );
void                    bsw_bswm_cs_sysst_GetLatSSExt( uint32* SysStatus );
void                    bsw_bswm_cs_sysst_GetECUInitPw( uint32* EcuInitPw );
uint8                   bsw_bswm_cs_sysst_JudgeWkUpChPw( NetworkHandleType Network );

/*------------------------------*/
/* Unit:ctrl                    */
/*------------------------------*/
uint8                   bsw_bswm_cs_ctrl_CheckAwake( void );
void                    bsw_bswm_cs_ctrl_DisableTx( NetworkHandleType Network );
void                    bsw_bswm_cs_ctrl_EnableTx( NetworkHandleType Network );
void                    bsw_bswm_cs_ctrl_StopNetwork( NetworkHandleType Network );
void                    bsw_bswm_cs_ctrl_StartNetwork( NetworkHandleType Network );
void                    bsw_bswm_cs_ctrl_EvtWkupTxConf( NetworkHandleType Network, uint16 DisableTime );
void                    bsw_bswm_cs_st_SetIpduGrVct( NetworkHandleType Network, uint8 TxIpduGrpVct, uint8 RxIpduGrpVct );
void                    bsw_bswm_cs_st_SetIpduGrVctExt( NetworkHandleType Network, uint32* TxIpduGrpVct, uint32* RxIpduGrpVct );
void                    bsw_bswm_cs_st_SetWkIpGrVct( NetworkHandleType Network, uint32 IpduGrpVct );
void                    bsw_bswm_cs_st_SetWkIpGrVctExt( NetworkHandleType Network, uint32* IpduGrpVct );
void                    bsw_bswm_cs_st_SetDMGrVct( NetworkHandleType Network, uint8 IpduGrpVct );
void                    bsw_bswm_cs_st_SetDMGrVctExt( NetworkHandleType Network, uint32* IpduGrpVct );
void                    bsw_bswm_cs_ctrl_SetTxControl( NetworkHandleType Network, uint8 TxStatus );
void                    bsw_bswm_cs_ctrl_ResetPeriTx( NetworkHandleType Network, uint8 ResetReason, uint16 offset );
Bsw_BswM_CS_RetCtrlType bsw_bswm_cs_ctrl_StopTxPdu( NetworkHandleType Network );
Bsw_BswM_CS_RetCtrlType bsw_bswm_cs_ctrl_ResumeTxPdu( NetworkHandleType Network );
uint16                  bsw_bswm_cs_ctrl_GetRsmWaitTime( NetworkHandleType Network );
uint8                   bsw_bswm_cs_ctrl_GetTxCtrlType( NetworkHandleType Network );
void                    bsw_bswm_cs_ctrl_ClearTxPdu( NetworkHandleType Network, uint8 clrTxMode );
void                    bsw_bswm_cs_ctrl_ClrNoAwkEvtPdu( NetworkHandleType Network, uint32* NonBusAwakePw );
void                    bsw_bswm_cs_ctrl_StartChgPeriCh( NetworkHandleType Network );
void                    bsw_bswm_cs_ctrl_StopChgPeriCh( NetworkHandleType Network );
void                    bsw_bswm_cs_ctrl_RestartChCtrl( NetworkHandleType Network );
Bsw_BswM_CS_RetCtrlType bsw_bswm_cs_ctrl_StopDMCtrl( NetworkHandleType Network );
Bsw_BswM_CS_RetCtrlType bsw_bswm_cs_ctrl_RsmDMCtrl( NetworkHandleType Network );
void                    bsw_bswm_cs_ctrl_ReqDMCtrReset( NetworkHandleType Network );
void                    bsw_bswm_cs_ctrl_DetectChFail( NetworkHandleType Network );
void                    bsw_bswm_cs_ctrl_ReleaseChFail( NetworkHandleType Network );
uint8                   bsw_bswm_cs_ctrl_GetTRXStatus( NetworkHandleType Network );
void                    bsw_bswm_cs_ctrl_SetXcpTxMode( NetworkHandleType Network, uint8 TxMode );
uint8                   bsw_bswm_cs_ctrl_GetTxPduCh( uint16 CompId, PduIdType PduId );
uint8                   bsw_bswm_cs_ctrl_GetRxPduCh( uint16 CompId, PduIdType PduId );
void                    bsw_bswm_cs_ctrl_SetFirstTxStat( NetworkHandleType Network );
void                    bsw_bswm_cs_ctrl_BusWakeup( NetworkHandleType Network, uint8 WakeupKind, uint16 DisableSend, uint16 EnablePeriodic );

void                    bsw_bswm_cs_ctrl_ChgWkupIPDUGrp( NetworkHandleType Network, uint32* IpduGrpStat );
void                    bsw_bswm_cs_ctrl_SetEventAwake( NetworkHandleType Network );
uint8                   bsw_bswm_cs_ctrl_TransWkupEvt( NetworkHandleType Network, PduIdType PduId );

/*------------------------------*/
/* Unit:user                    */
/*------------------------------*/
uint32                  bsw_bswm_cs_user_CbkChgIniSysSt( uint32 SysStatus );
void                    bsw_bswm_cs_user_CbkChgIniSSExt( uint32* SysStatus );
void                    bsw_bswm_cs_user_CbkSetSysStat( void );
void                    bsw_bswm_cs_user_CbkProvClkInit( void );
void                    bsw_bswm_cs_user_CbkProvClkWkup( void );
void                    bsw_bswm_cs_user_CbkWkupSrcInd( void );
void                    bsw_bswm_cs_user_CbkAppMainFunc( void );
void                    bsw_bswm_cs_user_CbkDcmMainFunc( void );
void                    bsw_bswm_cs_user_CbkPreMFuncHi( void );
void                    bsw_bswm_cs_user_CbkPostMFuncHi( void );
void                    bsw_bswm_cs_user_CbkPreMFuncMid( void );
void                    bsw_bswm_cs_user_CbkPostMFuncMd( void );
void                    bsw_bswm_cs_user_CbkSetBusAwake( void );
uint16                  bsw_bswm_cs_user_CbkSetRsmTime( NetworkHandleType Network );
void                    bsw_bswm_cs_user_CbkNetworkStrt( NetworkHandleType Network );
void                    bsw_bswm_cs_user_CbkNetworkStop( NetworkHandleType Network );
void                    bsw_bswm_cs_user_CbkEnableTx( NetworkHandleType Network );
void                    bsw_bswm_cs_user_CbkDisableTx( NetworkHandleType Network );
uint16                  bsw_bswm_cs_user_CbkSetDMWaitTm( NetworkHandleType Network );
void                    bsw_bswm_cs_user_CbkDetectFail( void );
void                    bsw_bswm_cs_user_CbkPreWakeup( void );
void                    bsw_bswm_cs_user_CbkPostSleep( void );
void                    bsw_bswm_cs_user_CbkSecMFuncTx( void );
void                    bsw_bswm_cs_user_CbkSecMFuncRx( void );
Std_ReturnType          bsw_bswm_cs_user_CbkPrFailClrEv( NetworkHandleType Network );

/*------------------------------*/
/* Unit:system                  */
/*------------------------------*/
uint16                  bsw_bswm_cs_system_ms2HTickRup( uint16 msTime );
uint16                  bsw_bswm_cs_system_ms2MTickRup( uint16 msTime );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* BSW_BSWM_CS_PUBLIC_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v2-0-0          :2021/11/16                                             */
/*  v2-2-0          :2023/06/08                                             */
/*  v3-0-0          :2024/11/13                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
