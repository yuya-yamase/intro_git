/* bsw_cannm_b_public_h_V2-0-0                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANNM/B/PUBLIC/HEADER                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_CANNM_B_PUBLIC_H
#define BSW_CANNM_B_PUBLIC_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define     BSW_CANNM_B_PDU_NUM                (3U)    /* Number of NM-PDU */

#define     BSW_CANNM_B_BITPOS0MASK        (0x01U)     /* Bit mask value (for bit 0) */
#define     BSW_CANNM_B_BITPOS1MASK        (0x02U)     /* Bit mask value (for bit 1) */
#define     BSW_CANNM_B_BITPOS2MASK        (0x04U)     /* Bit mask value (for bit 2) */
#define     BSW_CANNM_B_BITPOS3MASK        (0x08U)     /* Bit mask value (for bit 3) */
#define     BSW_CANNM_B_BITPOS4MASK        (0x10U)     /* Bit mask value (for bit 4) */
#define     BSW_CANNM_B_BITPOS5MASK        (0x20U)     /* Bit mask value (for bit 5) */
#define     BSW_CANNM_B_BITPOS6MASK        (0x40U)     /* Bit mask value (for bit 6) */
#define     BSW_CANNM_B_BITPOS7MASK        (0x80U)     /* Bit mask value (for bit 7) */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*-----------------------------------*/
/* Unit : control                    */
/*-----------------------------------*/
void            bsw_cannm_b_ctrl_Init( BswConst Bsw_CanNm_ConfigType* cannmConfigPtr );
void            bsw_cannm_b_ctrl_Wakeup( BswConst Bsw_CanNm_ConfigType* cannmConfigPtr );
Std_ReturnType  bsw_cannm_b_ctrl_PassiveStartUp(NetworkHandleType NetworkHandle);
Std_ReturnType  bsw_cannm_b_ctrl_NetworkRequest(NetworkHandleType NetworkHandle);
Std_ReturnType  bsw_cannm_b_ctrl_NetworkRelease(NetworkHandleType NetworkHandle);
void            bsw_cannm_b_ctrl_MainFunction( void );
uint8           bsw_cannm_b_ctrl_CheckAwake( NetworkHandleType nmChannelHandle );
Std_ReturnType  bsw_cannm_b_ctrl_GetState( NetworkHandleType nmNetworkHandle, Nm_StateType* nmStatePtr, Nm_ModeType* nmModePtr );
uint8           bsw_cannm_b_ctrl_GetIPDUState( NetworkHandleType nmChannelHandle );
void            bsw_cannm_b_ctrl_Sleep( void );
void            bsw_cannm_b_ctrl_DeInit( void );
uint16          bsw_cannm_b_ctrl_ReqEvtWkup( NetworkHandleType nmNetworkHandle );
void            bsw_cannm_b_ctrl_CancelEvtWkup( NetworkHandleType nmNetworkHandle );
Std_ReturnType  bsw_cannm_b_ctrl_DisableCom( NetworkHandleType NetworkHandle );
Std_ReturnType  bsw_cannm_b_ctrl_EnableCom( NetworkHandleType NetworkHandle );
void            bsw_cannm_b_ctrl_CheckRam(void);

/*-----------------------------------*/
/* Unit : driver                     */
/*-----------------------------------*/
Std_ReturnType bsw_cannm_b_ctrl_PreRxMsg( BswU1 u1NetID, BswConstR CanIf_PduType* ptMsg );
void           bsw_cannm_b_ctrl_PostRxMsg( BswU1 u1NetID, BswConstR CanIf_PduType* ptMsg );
void           bsw_cannm_b_ctrl_PreTxMsg( BswU1 u1NetID, CanIf_PduType* ptMsg );
void           bsw_cannm_b_ctrl_RxIndication( PduIdType RxPduId,  NetworkHandleType nmChannelHandle, BswConstR PduInfoType* PduInfoPtr );
void           bsw_cannm_b_ctrl_TxConfirmation( PduIdType TxPduId, NetworkHandleType nmChannelHandle, Std_ReturnType result );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif /* BSW_CANNM_B_PUBLIC_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v2-0-0          :2021/12/02                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
