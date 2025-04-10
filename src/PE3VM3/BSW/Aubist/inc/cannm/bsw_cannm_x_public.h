/* bsw_cannm_x_public_h_v3-0-0                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANNM/X/PUBLIC/HEADER                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_CANNM_X_PUBLIC_H
#define BSW_CANNM_X_PUBLIC_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define    BSW_CANNM_X_PDU_NUM                    (4U)    /*Number of Pdu-ID */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void            bsw_cannm_x_ctrl_CbkInit(BswConst Bsw_CanNm_ConfigType* cannmConfigPtr);
void            bsw_cannm_x_ctrl_CbkDeInit(void);
Std_ReturnType  bsw_cannm_x_ctrl_CbkPsvStartUp(NetworkHandleType NetworkHandle);
Std_ReturnType  bsw_cannm_x_ctrl_CbkNwRequest(NetworkHandleType NetworkHandle);
Std_ReturnType  bsw_cannm_x_ctrl_CbkNwRelease(NetworkHandleType NetworkHandle);
Std_ReturnType  bsw_cannm_x_ctrl_CbkGetState(NetworkHandleType nmNetworkHandle, Nm_StateType* nmStatePtr, Nm_ModeType* nmModePtr);
void            bsw_cannm_x_ctrl_CbkMainFunc(void);

uint8           bsw_cannm_x_ctrl_CbkGetIPDUStat( NetworkHandleType nmChannelHandle );
uint8           bsw_cannm_x_ctrl_CbkCheckAwake( NetworkHandleType nmChannelHandle );

void            bsw_cannm_x_ctrl_CbkWakeup(BswConst Bsw_CanNm_ConfigType* cannmConfigPtr);
void            bsw_cannm_x_ctrl_CbkSleep(void);

Std_ReturnType  bsw_cannm_x_ctrl_CbkDisableCom( NetworkHandleType NetworkHandle );
Std_ReturnType  bsw_cannm_x_ctrl_CbkEnableCom( NetworkHandleType NetworkHandle );

void            bsw_cannm_x_ctrl_CbkTxConf(PduIdType TxPduId, NetworkHandleType nmChannelHandle, Std_ReturnType result );
void            bsw_cannm_x_ctrl_CbkRxInd(PduIdType RxPduId,  NetworkHandleType nmChannelHandle, BswConstR PduInfoType* PduInfoPtr);

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif  /* BSW_CANNM_X_PUBLIC_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v2-0-0          :2021/05/13                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
