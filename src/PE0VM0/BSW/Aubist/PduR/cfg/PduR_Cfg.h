/* pdur_cfg_h_v2-0-0                                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | PDUR/CFG/HEADER                                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_PDUR_CFG_H
#define BSW_PDUR_CFG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>
#include <ComStack_Types.h>

#include <pdur/bsw_pdur.h>


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Message Number */
/* Upper Component */
#define BSW_PDUR_CFG_MSGCOM_NUM            (486U)
#define BSW_PDUR_CFG_MSGDCM_NUM            (10U)
#define BSW_PDUR_CFG_MSGLDCOM_NUM          (0U)
#define BSW_PDUR_CFG_MSGCDD1_NUM           (0U)
#define BSW_PDUR_CFG_MSGCDD2_NUM           (0U)
/* Lower Component */
#define BSW_PDUR_CFG_MSGCANIF_NUM          (486U)
#define BSW_PDUR_CFG_MSGLINIF_NUM          (0U)
#define BSW_PDUR_CFG_MSGSOADIF_NUM         (0U)
#define BSW_PDUR_CFG_MSGCDD1IF_NUM         (0U)
#define BSW_PDUR_CFG_MSGCDD2IF_NUM         (0U)
#define BSW_PDUR_CFG_MSGDOIPIF_NUM         (0U)
#define BSW_PDUR_CFG_MSGCANTP_NUM          (10U)
#define BSW_PDUR_CFG_MSGLINTP_NUM          (0U)
#define BSW_PDUR_CFG_MSGSOADTP_NUM         (0U)
#define BSW_PDUR_CFG_MSGCDD1TP_NUM         (0U)
#define BSW_PDUR_CFG_MSGCDD2TP_NUM         (0U)
#define BSW_PDUR_CFG_MSGDOIPTP_NUM         (0U)

/* Message Authentication by I-PDU */
#define BSW_PDUR_CFG_IPDU_MA               (BSW_NOUSE)

/* Zero Cost Operation */
#define BSW_PDUR_CFG_ZEROCOSTOPERATION     (BSW_NOUSE)

/* PDU ID for Tx UpperCdd-PDU */

/* PDU ID for Rx UpperCdd-PDU */

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

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#endif /* BSW_PDUR_CFG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/10/16                                             */
/*  v1-1-0          :2019/11/26                                             */
/*  v2-0-0          :2021/02/12                                             */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-2                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
