/* bsw_cannm_y_public_h_V2-1-0                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANNM/Y/PUBLIC/HEADER                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_CANNM_Y_PUBLIC_H
#define BSW_CANNM_Y_PUBLIC_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define    BSW_CANNM_Y_PDU_NUM                    (1U)    /* Number of Pdu-ID */
#define    BSW_CANNM_Y_CTRL_RESET                 (0U)    /* Controller Reset when TxTimeout */
#define    BSW_CANNM_Y_TX_CANCEL                  (1U)    /* Cancel Transmit when TxTimeout */
#define    BSW_CANNM_Y_SENDSTART                  (0U)    /* Kind of Waiting Time to Start Transmission when Power is Turned ON : SENDSTART */
#define    BSW_CANNM_Y_DISABLESND                 (1U)    /* Kind of Waiting Time to Start Transmission when Power is Turned ON : DISABLESEND */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void            bsw_cannm_y_ctrl_Init(BswConst Bsw_CanNm_ConfigType* cannmConfigPtr);
void            bsw_cannm_y_ctrl_DeInit(void);
Std_ReturnType  bsw_cannm_y_ctrl_PsvStartUp(NetworkHandleType NetworkHandle);
Std_ReturnType  bsw_cannm_y_ctrl_NwRequest(NetworkHandleType NetworkHandle);
Std_ReturnType  bsw_cannm_y_ctrl_NwRelease(NetworkHandleType NetworkHandle);
Std_ReturnType  bsw_cannm_y_ctrl_DisableCom( NetworkHandleType NetworkHandle );
Std_ReturnType  bsw_cannm_y_ctrl_EnableCom( NetworkHandleType NetworkHandle );
Std_ReturnType  bsw_cannm_y_ctrl_GetState(NetworkHandleType nmNetworkHandle, Nm_StateType* nmStatePtr, Nm_ModeType* nmModePtr);
void            bsw_cannm_y_ctrl_MainFunction(void);

void            bsw_cannm_y_ctrl_Wakeup(BswConst Bsw_CanNm_ConfigType* cannmConfigPtr);
void            bsw_cannm_y_ctrl_Sleep(void);
uint8           bsw_cannm_y_ctrl_CheckAwake( NetworkHandleType nmChannelHandle );
uint8           bsw_cannm_y_ctrl_GetIPDUState( NetworkHandleType nmChannelHandle );
void            bsw_cannm_y_ctrl_CheckRam(void);

Std_ReturnType  bsw_cannm_y_ctrl_GetNodeId( NetworkHandleType nmChannelHandle, uint8* nmNodeIdPtr );
Std_ReturnType  bsw_cannm_y_ctrl_GetLclNodeId( NetworkHandleType nmChannelHandle, uint8* nmNodeIdPtr );
Std_ReturnType  bsw_cannm_y_ctrl_SetUserData( NetworkHandleType nmChannelHandle, BswConstR uint8* nmUserDataPtr );
Std_ReturnType  bsw_cannm_y_ctrl_GetUserData( NetworkHandleType nmChannelHandle, uint8* nmUserDataPtr );
Std_ReturnType  bsw_cannm_y_ctrl_GetPduData( NetworkHandleType nmChannelHandle, uint8* nmPduDataPtr );

uint16          bsw_cannm_y_ctrl_TxEvtWakeup( NetworkHandleType nmNetworkHandle );
void            bsw_cannm_y_ctrl_CancelEvtWkup( NetworkHandleType nmNetworkHandle );

void            bsw_cannm_y_ctrl_TxConf(PduIdType TxPduId, NetworkHandleType nmChannelHandle, Std_ReturnType result );
void            bsw_cannm_y_ctrl_RxIndication(PduIdType RxPduId,  NetworkHandleType nmChannelHandle, BswConstR PduInfoType* PduInfoPtr);

Std_ReturnType  bsw_cannm_y_ctrl_SetSlpReadyBit( NetworkHandleType nmNetworkHandle, boolean nmSleepReadyBit );
Std_ReturnType  bsw_cannm_y_ctrl_RequestBusSync( NetworkHandleType nmNetworkHandle );
Std_ReturnType  bsw_cannm_y_ctrl_ReqSyncPncShutdown( NetworkHandleType nmChannelHandle, PNCHandleType PNC );
Std_ReturnType  bsw_cannm_y_ctrl_CancelReqSyncPncShutdown( NetworkHandleType nmChannelHandle, PNCHandleType PNC );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif  /* BSW_CANNM_Y_PUBLIC_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v2-0-0          :2022/01/06                                             */
/*  v2-1-0          :2022/11/09                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
