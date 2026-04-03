/* pdur_cfg_h_v3-0-0                                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
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
#warning "BEVCDCFD-2652"
#if 0 /* BEVCDCFD-2652 */
#define BSW_PDUR_CFG_MSGCOM_NUM            (302U)
#define BSW_PDUR_CFG_MSGDCM_NUM            (12U)
#else /* BEVCDCFD-2652 */
#define BSW_PDUR_CFG_MSGCOM_NUM            (291U)
#define BSW_PDUR_CFG_MSGDCM_NUM            (0U)
#endif /* BEVCDCFD-2652 */
#define BSW_PDUR_CFG_MSGLDCOM_NUM          (0U)
#define BSW_PDUR_CFG_MSGCDD1_NUM           (1U)
#define BSW_PDUR_CFG_MSGCDD2_NUM           (0U)
#define BSW_PDUR_CFG_MSGJ1939TPUP_NUM      (0U)

/* Lower Component */
#define BSW_PDUR_CFG_MSGCANIF_NUM          (292U)
#define BSW_PDUR_CFG_MSGLINIF_NUM          (0U)
#define BSW_PDUR_CFG_MSGSOADIF_NUM         (0U)
#define BSW_PDUR_CFG_MSGDOIPIF_NUM         (0U)
#define BSW_PDUR_CFG_MSGCANTP_NUM          (12U)
#define BSW_PDUR_CFG_MSGLINTP_NUM          (0U)
#define BSW_PDUR_CFG_MSGSOADTP_NUM         (0U)
#define BSW_PDUR_CFG_MSGDOIPTP_NUM         (0U)
#define BSW_PDUR_CFG_MSGJ1939TPLO_NUM      (0U)

/* Message Authentication by I-PDU */
#define BSW_PDUR_CFG_IPDU_MA               (BSW_NOUSE)

/* Zero Cost Operation */
#define BSW_PDUR_CFG_ZEROCOSTOPERATION     (BSW_NOUSE)

/* PDU ID for Tx UpperCdd-PDU */
#define UPPERCDD1_QSEV_Tx_CANFD_VCC_1_BUS  (0x0000U)

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
/*  v3-0-0          :2025/01/22                                             */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v3-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
