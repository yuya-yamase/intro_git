/* bsw_cannm_b_config_h_v2-0-0                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANNM/B/CONFIG/HEADER                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     BSW_CANNM_B_CONFIG_H
#define     BSW_CANNM_B_CONFIG_H

#include <comm/bsw_comm.h>
#include "../../../ComM/inc/bsw_comm_config.h"
#include "../../cfg/b/CanNm_B_Cfg.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Total number of received NM message */
#define BSW_CANNM_B_RX_MSG_NUM_0_7     (BSW_CANNM_B_CFG_RXMSG_NMNUM_CH0 + BSW_CANNM_B_CFG_RXMSG_NMNUM_CH1 + BSW_CANNM_B_CFG_RXMSG_NMNUM_CH2 + \
                                        BSW_CANNM_B_CFG_RXMSG_NMNUM_CH3 + BSW_CANNM_B_CFG_RXMSG_NMNUM_CH4 + BSW_CANNM_B_CFG_RXMSG_NMNUM_CH5 + \
                                        BSW_CANNM_B_CFG_RXMSG_NMNUM_CH6 + BSW_CANNM_B_CFG_RXMSG_NMNUM_CH7)
#define BSW_CANNM_B_RX_MSG_NUM_8_15    (BSW_CANNM_B_CFG_RXMSG_NMNUM_CH8  + BSW_CANNM_B_CFG_RXMSG_NMNUM_CH9  + BSW_CANNM_B_CFG_RXMSG_NMNUM_CH10 + \
                                        BSW_CANNM_B_CFG_RXMSG_NMNUM_CH11 + BSW_CANNM_B_CFG_RXMSG_NMNUM_CH12 + BSW_CANNM_B_CFG_RXMSG_NMNUM_CH13 + \
                                        BSW_CANNM_B_CFG_RXMSG_NMNUM_CH14 + BSW_CANNM_B_CFG_RXMSG_NMNUM_CH15)
#define BSW_CANNM_B_RX_MSG_NUM_16_23   (BSW_CANNM_B_CFG_RXMSG_NMNUM_CH16 + BSW_CANNM_B_CFG_RXMSG_NMNUM_CH17 + BSW_CANNM_B_CFG_RXMSG_NMNUM_CH18 + \
                                        BSW_CANNM_B_CFG_RXMSG_NMNUM_CH19 + BSW_CANNM_B_CFG_RXMSG_NMNUM_CH20 + BSW_CANNM_B_CFG_RXMSG_NMNUM_CH21 + \
                                        BSW_CANNM_B_CFG_RXMSG_NMNUM_CH22 + BSW_CANNM_B_CFG_RXMSG_NMNUM_CH23)
#define BSW_CANNM_B_RX_MSG_NUM_24_31   (BSW_CANNM_B_CFG_RXMSG_NMNUM_CH24 + BSW_CANNM_B_CFG_RXMSG_NMNUM_CH25 + BSW_CANNM_B_CFG_RXMSG_NMNUM_CH26 + \
                                        BSW_CANNM_B_CFG_RXMSG_NMNUM_CH27 + BSW_CANNM_B_CFG_RXMSG_NMNUM_CH28 + BSW_CANNM_B_CFG_RXMSG_NMNUM_CH29 + \
                                        BSW_CANNM_B_CFG_RXMSG_NMNUM_CH30 + BSW_CANNM_B_CFG_RXMSG_NMNUM_CH31)
#define BSW_CANNM_B_RX_MSG_NUM         (BSW_CANNM_B_RX_MSG_NUM_0_7 + BSW_CANNM_B_RX_MSG_NUM_8_15 + BSW_CANNM_B_RX_MSG_NUM_16_23 + BSW_CANNM_B_RX_MSG_NUM_24_31)

/* CanNm Number of channels used */
#define BSW_CANNM_B_CAN_CH_NUM         (BSW_COMM_BUS_TYPE_CHNUM(CAN))

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif  /* BSW_CANNM_B_CONFIG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/04/25                                             */
/*  v1-1-0          :2018/12/13                                             */
/*  v2-0-0          :2021/12/02                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
