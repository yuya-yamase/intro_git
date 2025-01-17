/* pdur_secoc_h_v2-0-0                                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | PDUR/SECOC/HEADER                                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_PDUR_SECOC_AR_H
#define BSW_PDUR_SECOC_AR_H

#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>

#include <PduR.h>
#include <pdur/bsw_pdur_public.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Function */
#define PduR_SecOCTransmit                (bsw_pdur_rt_SecOCTransmit)
#define PduR_SecOCCancelTransmit          (bsw_pdur_rt_SecOCCancelTx)
#define PduR_SecOCIfRxIndication          (bsw_pdur_rt_SecOCIfRxIndication)
#define PduR_SecOCIfTxConfirmation        (bsw_pdur_rt_SecOCIfTxConfirm)
#define PduR_SecOCTpRxIndication          (bsw_pdur_rt_SecOCTpRxIndication)
#define PduR_SecOCTpStartOfReception      (bsw_pdur_rt_SecOCTpSOR)
#define PduR_SecOCTpCopyRxData            (bsw_pdur_rt_SecOCTpCopyRxData)
#define PduR_SecOCTpTxConfirmation        (bsw_pdur_rt_SecOCTpTxConfirm)
#define PduR_SecOCTpCopyTxData            (bsw_pdur_rt_SecOCTpCopyTxData)
#define PduR_SecOCCancelReceive           (bsw_pdur_rt_SecOCCancelRx)
#define PduR_SecOCIfTriggerTransmit       (bsw_pdur_rt_SecOCIfTriggerTx)

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

#endif /* BSW_PDUR_SECOC_AR_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/02/22                                             */
/*  v1-1-0          :2019/01/15                                             */
/*  v2-0-0          :2021/05/24                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
