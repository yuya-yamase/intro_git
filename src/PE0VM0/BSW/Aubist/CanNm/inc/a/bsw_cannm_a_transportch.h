/* bsw_cannm_a_transportch_h_v2-0-0                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANNM/A/TRANSPORTCH/HEADER                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef BSW_CANNM_A_TRANSPORTCH_H
#define BSW_CANNM_A_TRANSPORTCH_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/*** MESSAGE KIND ***/
#define BSW_CANNM_A_TRANS_MKIND_MSK         (0x07U)         /* Message type mask value   */
#define BSW_CANNM_A_TRANS_MKIND_WKUP        (0x00U)         /* Message type:WKUP     */
#define BSW_CANNM_A_TRANS_MKIND_ALIVE       (0x01U)         /* Message type:ALIVE    */
#define BSW_CANNM_A_TRANS_MKIND_RING        (0x02U)         /* Message type:RING     */
#define BSW_CANNM_A_TRANS_MKIND_LMPHOM      (0x04U)         /* Message type:LMPHOM   */

/*** RECEIVE MESSAGE DATA POSITION ***/
#define BSW_CANNM_A_TRANS_R_MPS_DST         (0U)            /* Received CAN frame 0:DST    */
#define BSW_CANNM_A_TRANS_R_MPS_OPCODE      (1U)            /* Received CAN frame 1:OPCODE */

/* Unit internal public definition */
/*** MESSAGE SEND-RECEIVE DIRECTION ***/
#define BSW_CANNM_A_TRANS_DIR_RX            (0x7fU)     /* Message Direction:Receiving */
#define BSW_CANNM_A_TRANS_DIR_TX            (0x80U)     /* Message Direction:Transmission */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void   bsw_cannm_a_trans_MpuResetInit(BswU1 u1NetID);
void   bsw_cannm_a_trans_GetMsg(BswU1 u1NetID, Bsw_CanNmA_STCanNmMsgBufType **ptMessage);
BswU2 bsw_cannm_a_trans_GetMsgEvent(BswU1 u1NetID) ;
void   bsw_cannm_a_trans_InitMsgQ(BswU1 u1NetID);

/* Unit internal public definition */
void  bsw_cannm_a_trans_SetMsg(BswU1 u1NetID, BswU1 u1KindSR, BswU2 u2Sid, BswConstR BswU1 u1DataBuf[]);

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif  /* BSW_CANNM_A_TRANSPORTCH_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/05/18                                             */
/*  v2-0-0          :2021/12/02                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
