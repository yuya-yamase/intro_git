/* pdur_soad_h_v3-0-0                                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | PDUR/SOAD/HEADER                                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_PDUR_SOAD_AR_H
#define BSW_PDUR_SOAD_AR_H

#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>

#include <PduR.h>
#include <pdur/bsw_pdur_public.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Function */
#define PduR_SoAdIfRxIndication           (bsw_pdur_rt_SoAdIfRxIndication)
#define PduR_SoAdIfTxConfirmation         (bsw_pdur_rt_SoAdIfTxConfirm)
#define PduR_SoAdIfTriggerTransmit        (bsw_pdur_rt_SoAdIfTriggerTx)
#define PduR_SoAdTpRxIndication           (bsw_pdur_rt_SoAdTpRxIndication)
#define PduR_SoAdTpStartOfReception       (bsw_pdur_rt_SoAdTpStartOfRecept)
#define PduR_SoAdTpCopyRxData             (bsw_pdur_rt_SoAdTpCopyRxData)
#define PduR_SoAdTpTxConfirmation         (bsw_pdur_rt_SoAdTpTxConfirm)
#define PduR_SoAdTpCopyTxData             (bsw_pdur_rt_SoAdTpCopyTxData)

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

#endif /* BSW_PDUR_SOAD_AR_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/02/22                                             */
/*  v2-0-0          :2022/02/25                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
