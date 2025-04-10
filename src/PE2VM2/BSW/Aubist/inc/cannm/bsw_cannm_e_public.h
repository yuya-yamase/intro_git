/* bsw_cannm_e_public_h_v3-0-0                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANNM/E/PUBLIC/HEADER                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_CANNM_E_PUBLIC_H
#define BSW_CANNM_E_PUBLIC_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define    BSW_CANNM_E_PDU_NUM                   (1U)       /* Number of Pdu-ID                 */

#define    BSW_CANNM_E_CONTROL_TYPE_NOUSE        (0U)       /* Control type (Nouse)             */
#define    BSW_CANNM_E_CONTROL_TYPE_MC           (1U)       /* Control type (Master Complete)   */
#define    BSW_CANNM_E_CONTROL_TYPE_MS           (2U)       /* Control type (Master Simplified) */
#define    BSW_CANNM_E_CONTROL_TYPE_SC           (3U)       /* Control type (Slave Complete)    */
#define    BSW_CANNM_E_CONTROL_TYPE_SS           (4U)       /* Control type (Slave Simplified)  */
#define    BSW_CANNM_E_CONTROL_TYPE_SE           (5U)       /* Control type (Slave Exceptional) */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void            bsw_cannm_e_ctrl_Init(BswConst Bsw_CanNm_ConfigType* cannmConfigPtr);
void            bsw_cannm_e_ctrl_DeInit(void);
Std_ReturnType  bsw_cannm_e_ctrl_PsvStartUp(NetworkHandleType NetworkHandle);
Std_ReturnType  bsw_cannm_e_ctrl_NwRequest(NetworkHandleType NetworkHandle);
Std_ReturnType  bsw_cannm_e_ctrl_NwRelease(NetworkHandleType NetworkHandle);

Std_ReturnType  bsw_cannm_e_ctrl_GetState(NetworkHandleType nmNetworkHandle, Nm_StateType* nmStatePtr, Nm_ModeType* nmModePtr);
uint8           bsw_cannm_e_ctrl_GetIPDUState( NetworkHandleType nmChannelHandle );

void            bsw_cannm_e_ctrl_MainFunction(void);

void            bsw_cannm_e_ctrl_Wakeup(BswConst Bsw_CanNm_ConfigType* cannmConfigPtr);
void            bsw_cannm_e_ctrl_Sleep(void);
uint8           bsw_cannm_e_ctrl_CheckAwake( NetworkHandleType nmChannelHandle );

Std_ReturnType  bsw_cannm_e_ctrl_DisableCom( NetworkHandleType NetworkHandle );
Std_ReturnType  bsw_cannm_e_ctrl_EnableCom( NetworkHandleType NetworkHandle );

void            bsw_cannm_e_ctrl_RxECUFrame( PduIdType RxPduId );

void            bsw_cannm_e_ctrl_CheckRam( void );
uint16          bsw_cannm_e_ctrl_CbkSetWkUpTm( NetworkHandleType network, uint16 msTime );

void            bsw_cannm_e_ctrl_RxMsg( BswU1 u1NetID, BswConstR CanIf_PduType* ptMsg );
void            bsw_cannm_e_ctrl_PreTxMsg( BswU1 u1NetID, CanIf_PduType* ptMsg );
void            bsw_cannm_e_ctrl_RxIndication( PduIdType RxPduId, NetworkHandleType nmChannelHandle, BswConstR PduInfoType* PduInfoPtr );
void            bsw_cannm_e_ctrl_TxConf( PduIdType TxPduId, NetworkHandleType nmChannelHandle, Std_ReturnType result );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif  /* BSW_CANNM_E_PUBLIC_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v2-0-0          :2021/05/13                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
