/* bsw_bswm_cs_public_h_v2-2-0                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
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
#define BSW_BSWM_CS_SYSSTAT_NONE               (0x00U)
#define BSW_BSWM_CS_SYSSTAT_BAT                (0x01U)
#define BSW_BSWM_CS_SYSSTAT_ACC                (0x02U)
#define BSW_BSWM_CS_SYSSTAT_IG                 (0x04U)
#define BSW_BSWM_CS_SYSSTAT_USER1              (0x08U)
#define BSW_BSWM_CS_SYSSTAT_USER2              (0x10U)
#define BSW_BSWM_CS_SYSSTAT_USER3              (0x20U)
#define BSW_BSWM_CS_SYSSTAT_USER4              (0x40U)
#define BSW_BSWM_CS_SYSSTAT_USER5              (0x80U)

/* System Status Mask Bit       */
#define BSW_BSWM_CS_SYSSTAT_MASK_BAT           (BSW_BSWM_CS_SYSSTAT_BAT)
#define BSW_BSWM_CS_SYSSTAT_MASK_ACC           (BSW_BSWM_CS_SYSSTAT_ACC)
#define BSW_BSWM_CS_SYSSTAT_MASK_IG            (BSW_BSWM_CS_SYSSTAT_IG)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER1         (BSW_BSWM_CS_SYSSTAT_USER1)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER2         (BSW_BSWM_CS_SYSSTAT_USER2)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER3         (BSW_BSWM_CS_SYSSTAT_USER3)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER4         (BSW_BSWM_CS_SYSSTAT_USER4)
#define BSW_BSWM_CS_SYSSTAT_MASK_USER5         (BSW_BSWM_CS_SYSSTAT_USER5)

/* Number of System Status      */
#define BSW_BSWM_CS_SYSSTAT_NUM                ((uint8)8U)

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

/*------------------------------*/
/* Unit:sysstat                 */
/*------------------------------*/
void                    bsw_bswm_cs_sysst_SetSysStat( uint8 Mask, uint8 SysStatus );
uint8                   bsw_bswm_cs_sysst_GetSysStat( void );
uint8                   bsw_bswm_cs_sysst_GetLatSysStat( void );

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
void                    bsw_bswm_cs_st_SetWkIpGrVct( NetworkHandleType Network, uint8 IpduGrpVct );
void                    bsw_bswm_cs_st_SetDMGrVct( NetworkHandleType Network, uint8 IpduGrpVct );
void                    bsw_bswm_cs_ctrl_SetTxControl( NetworkHandleType Network, uint8 TxStatus );
void                    bsw_bswm_cs_ctrl_ResetPeriTx( NetworkHandleType Network, uint16 offset );
Bsw_BswM_CS_RetCtrlType bsw_bswm_cs_ctrl_StopTxPdu( NetworkHandleType Network );
Bsw_BswM_CS_RetCtrlType bsw_bswm_cs_ctrl_ResumeTxPdu( NetworkHandleType Network );
uint16                  bsw_bswm_cs_ctrl_GetRsmWaitTime( NetworkHandleType Network );
uint8                   bsw_bswm_cs_ctrl_GetTxCtrlType( NetworkHandleType Network );
void                    bsw_bswm_cs_ctrl_ClearTxPdu( NetworkHandleType Network, uint8 clrTxMode );
void                    bsw_bswm_cs_ctrl_ClrNoAwkEvtPdu( NetworkHandleType Network, uint8 NonBusAwakePw );
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

void                    bsw_bswm_cs_ctrl_ChgWkupIPDUGrp( Com_IpduGroupVector ipduGroupVector );
void                    bsw_bswm_cs_ctrl_SetEventAwake( NetworkHandleType Network );
uint8                   bsw_bswm_cs_ctrl_TransWkupEvt( NetworkHandleType Network, PduIdType PduId );

/*------------------------------*/
/* Unit:user                    */
/*------------------------------*/
uint8                   bsw_bswm_cs_user_CbkChgIniSysSt( uint8 SysStatus );
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
/****************************************************************************/

/**** End of File ***********************************************************/
