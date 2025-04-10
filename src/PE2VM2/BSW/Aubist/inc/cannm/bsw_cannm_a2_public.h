/* bsw_cannm_a2_public_h_v3-0-0                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANNM/A2/PUBLIC/HEADER                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_CANNM_A2_PUBLIC_H
#define BSW_CANNM_A2_PUBLIC_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define    BSW_CANNM_A2_PDU_NUM                  (1U)    /* Number of Pdu-ID */

/* Initial Value for Tx Data Field */
#define    BSW_CANNM_A2_INITTXDATA_00            (0x00U)
#define    BSW_CANNM_A2_INITTXDATA_0F            (0x0FU)
#define    BSW_CANNM_A2_INITTXDATA_FF            (0xFFU)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void            bsw_cannm_a2_ctrl_Init(BswConst Bsw_CanNm_ConfigType* cannmConfigPtr);
void            bsw_cannm_a2_ctrl_DeInit(void);
Std_ReturnType  bsw_cannm_a2_ctrl_PsvStartUp(NetworkHandleType NetworkHandle);
Std_ReturnType  bsw_cannm_a2_ctrl_NwRequest(NetworkHandleType NetworkHandle);
Std_ReturnType  bsw_cannm_a2_ctrl_NwRelease(NetworkHandleType NetworkHandle);
Std_ReturnType  bsw_cannm_a2_ctrl_DisableCom( NetworkHandleType NetworkHandle );
Std_ReturnType  bsw_cannm_a2_ctrl_EnableCom( NetworkHandleType NetworkHandle );
Std_ReturnType  bsw_cannm_a2_ctrl_GetState(NetworkHandleType nmNetworkHandle, Nm_StateType* nmStatePtr, Nm_ModeType* nmModePtr);
void            bsw_cannm_a2_ctrl_MainFunction(void);

void            bsw_cannm_a2_ctrl_Wakeup(BswConst Bsw_CanNm_ConfigType* cannmConfigPtr);
void            bsw_cannm_a2_ctrl_Sleep(void);
uint8           bsw_cannm_a2_ctrl_CheckAwake( NetworkHandleType nmChannelHandle );
uint8           bsw_cannm_a2_ctrl_GetIPDUState( NetworkHandleType nmChannelHandle );
void            bsw_cannm_a2_ctrl_SetBusOff( NetworkHandleType nmChannelHandle );
uint16          bsw_cannm_a2_ctrl_TxEvtWakeup( NetworkHandleType nmNetworkHandle );
void            bsw_cannm_a2_ctrl_CancelEvtWkup( NetworkHandleType nmNetworkHandle );
void            bsw_cannm_a2_ctrl_CheckRam(void);

Std_ReturnType  bsw_cannm_a2_ctrl_GetNodeId( NetworkHandleType nmChannelHandle, uint8* nmNodeIdPtr );
Std_ReturnType  bsw_cannm_a2_ctrl_GetLclNodeId( NetworkHandleType nmChannelHandle, uint8* nmNodeIdPtr );
Std_ReturnType  bsw_cannm_a2_ctrl_SetUserData( NetworkHandleType nmChannelHandle, BswConstR uint8* nmUserDataPtr );
Std_ReturnType  bsw_cannm_a2_ctrl_GetUserData( NetworkHandleType nmChannelHandle, uint8* nmUserDataPtr );
Std_ReturnType  bsw_cannm_a2_ctrl_GetPduData( NetworkHandleType nmChannelHandle, uint8* nmPduDataPtr );

void            bsw_cannm_a2_ctrl_TxConf(PduIdType TxPduId, NetworkHandleType nmChannelHandle, Std_ReturnType result );
void            bsw_cannm_a2_ctrl_RxIndication(PduIdType RxPduId,  NetworkHandleType nmChannelHandle, BswConstR PduInfoType* PduInfoPtr);

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif  /* BSW_CANNM_A2_PUBLIC_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v2-0-0          :2021/05/24                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
