/* bsw_cannm_z_public_h_V2-0-0                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANNM/Z/PUBLIC/HEADER                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_CANNM_Z_PUBLIC_H
#define BSW_CANNM_Z_PUBLIC_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define    BSW_CANNM_Z_PDU_NUM                    (0U)    /* Number of Pdu-ID */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void            bsw_cannm_z_ctrl_Init(BswConst Bsw_CanNm_ConfigType* cannmConfigPtr);
void            bsw_cannm_z_ctrl_DeInit(void);
Std_ReturnType  bsw_cannm_z_ctrl_NtwkReq(NetworkHandleType NetworkHandle);
Std_ReturnType  bsw_cannm_z_ctrl_NtwkRel(NetworkHandleType NetworkHandle);
Std_ReturnType  bsw_cannm_z_ctrl_GetState(NetworkHandleType nmNetworkHandle, Nm_StateType* nmStatePtr, Nm_ModeType* nmModePtr);
void            bsw_cannm_z_ctrl_MainFunction(void);
uint8           bsw_cannm_z_ctrl_GetIPDUState( NetworkHandleType nmChannelHandle );
void            bsw_cannm_z_ctrl_CheckRam(void);

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif  /* BSW_CANNM_Z_PUBLIC_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v2-0-0          :2021/05/13                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
