/* bsw_cannm_a_nmpktch_h_v3-0-0                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANNM/A/NMPKTCH/HEADER                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef BSW_CANNM_A_NMPKTCH_H
#define BSW_CANNM_A_NMPKTCH_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/*** MESSAGE RELATED DEFINITION ***/
#define BSW_CANNM_A_TRANS_MSG_DLC           (0x08U)         /* DLC value 8                         */
#define BSW_CANNM_A_TRANS_U1_MAX            (0xffU)         /* Skip Alive Message Data2 setting value 0xFF */

/*** SEND MESSAGE DATA POSITION ***/
#define BSW_CANNM_A_TRANS_S_MPS_DST         (0U)            /* Transmit CAN frame 0:DST    */
#define BSW_CANNM_A_TRANS_S_MPS_OPCODE      (1U)            /* Transmit CAN frame 1:OPCODE */
#define BSW_CANNM_A_TRANS_S_MPS_DATA1       (2U)            /* Transmit CAN frame 2:DATA1  */
#define BSW_CANNM_A_TRANS_S_MPS_DATA2       (3U)            /* Transmit CAN frame 3:DATA2  */
#define BSW_CANNM_A_TRANS_S_MPS_DATA3       (4U)            /* Transmit CAN frame 4:DATA3  */
#define BSW_CANNM_A_TRANS_S_MPS_DATA4       (5U)            /* Transmit CAN frame 5:DATA4  */
#define BSW_CANNM_A_TRANS_S_MPS_DATA5       (6U)            /* Transmit CAN frame 6:DATA5  */
#define BSW_CANNM_A_TRANS_S_MPS_DATA6       (7U)            /* Transmit CAN frame 7:DATA6  */

/*** ROM MESSAGE DATA SPEC NO POSITION ***/
#define BSW_CANNM_A_TRANS_SPECNO_1          (1U)            /* DATA2 Data[1]:SPECNo(1) */
#define BSW_CANNM_A_TRANS_SPECNO_2          (2U)            /* DATA3 Data[2]:SPECNo(2) */


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void   bsw_cannm_a_trans_WDtReq(BswU1 u1NetID, BswU1 u1Dest, BswU1 u1OpCode, BswConst BswU1 *ptDataField);
void   bsw_cannm_a_trans_WDtRqWUmsg(BswU1 u1NetID);
BswU1  bsw_cannm_a_trans_SendMessage(BswU1 u1CanNetID, BswConstR BswU1 u1DtBuf[]);
void   bsw_cannm_a_trans_SendQueClr(BswU1 u1CanNetID);


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif  /* BSW_CANNM_A_NMPKTCH_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/05/18                                             */
/*  v2-0-0          :2021/12/03                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
