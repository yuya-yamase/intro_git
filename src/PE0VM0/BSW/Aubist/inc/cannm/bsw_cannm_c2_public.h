/* bsw_cannm_c2_public_h_V2-0-0                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANNM/C2/PUBLIC/HEADER                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_CANNM_C2_PUBLIC_H
#define BSW_CANNM_C2_PUBLIC_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define    BSW_CANNM_C2_PDU_NUM                (1U)    /* Number of Pdu-ID */
#define    BSW_CANNM_C2_CTRL_RESET             (0U)    /* Controller Reset when TxTimeout */
#define    BSW_CANNM_C2_TX_CANCEL              (1U)    /* Cancel Transmit when TxTimeout  */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void            bsw_cannm_c2_ctrl_Init(BswConst Bsw_CanNm_ConfigType* cannmConfigPtr);
void            bsw_cannm_c2_ctrl_DeInit(void);
Std_ReturnType  bsw_cannm_c2_ctrl_PsvStartUp(NetworkHandleType NetworkHandle);
Std_ReturnType  bsw_cannm_c2_ctrl_NwRequest(NetworkHandleType NetworkHandle);
Std_ReturnType  bsw_cannm_c2_ctrl_NwRelease(NetworkHandleType NetworkHandle);
Std_ReturnType  bsw_cannm_c2_ctrl_DisableCom( NetworkHandleType NetworkHandle );
Std_ReturnType  bsw_cannm_c2_ctrl_EnableCom( NetworkHandleType NetworkHandle );
Std_ReturnType  bsw_cannm_c2_ctrl_GetState(NetworkHandleType nmNetworkHandle, Nm_StateType* nmStatePtr, Nm_ModeType* nmModePtr);
void            bsw_cannm_c2_ctrl_MainFunction(void);

void            bsw_cannm_c2_ctrl_Wakeup(BswConst Bsw_CanNm_ConfigType* cannmConfigPtr);
void            bsw_cannm_c2_ctrl_Sleep(void);
uint8           bsw_cannm_c2_ctrl_CheckAwake( NetworkHandleType nmChannelHandle );
uint8           bsw_cannm_c2_ctrl_GetIPDUState( NetworkHandleType nmChannelHandle );
void            bsw_cannm_c2_ctrl_CheckRam(void);

Std_ReturnType  bsw_cannm_c2_ctrl_GetNodeId( NetworkHandleType nmChannelHandle, uint8* nmNodeIdPtr );
Std_ReturnType  bsw_cannm_c2_ctrl_GetLclNodeId( NetworkHandleType nmChannelHandle, uint8* nmNodeIdPtr );
Std_ReturnType  bsw_cannm_c2_ctrl_SetUserData( NetworkHandleType nmChannelHandle, BswConstR uint8* nmUserDataPtr );
Std_ReturnType  bsw_cannm_c2_ctrl_GetUserData( NetworkHandleType nmChannelHandle, uint8* nmUserDataPtr );
Std_ReturnType  bsw_cannm_c2_ctrl_GetPduData( NetworkHandleType nmChannelHandle, uint8* nmPduDataPtr );

void            bsw_cannm_c2_ctrl_TxConf(PduIdType TxPduId, NetworkHandleType nmChannelHandle, Std_ReturnType result );
void            bsw_cannm_c2_ctrl_RxIndication(PduIdType RxPduId,  NetworkHandleType nmChannelHandle, BswConstR PduInfoType* PduInfoPtr);

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif  /* BSW_CANNM_C2_PUBLIC_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v2-0-0          :2021/05/13                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
