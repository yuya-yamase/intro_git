/* 1.0.5 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Oem eXtention of CAN User Hooks                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef OXCAN_USRHK_H
#define OXCAN_USRHK_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_USRHK_H_MAJOR                      (1U)
#define OXCAN_USRHK_H_MINOR                      (0U)
#define OXCAN_USRHK_H_PATCH                      (5U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void    vd_g_oXCANUsrhkExirEnaCh(const U1 u1_a_CTRLR);                   /* called from oxcan_aubif.c :: Can_UEdgeEnableDetect  */
void    vd_g_oXCANUsrhkExirDisCh(const U1 u1_a_CTRLR);                   /* called from oxcan_aubif.c :: Can_UEdgeDisableDetect */
void    vd_g_oXCANUsrhkExirClrIRQst(const U1 u1_a_CTRLR);                /* called from oxcan_aubif.c :: Can_UEdgeClearStatus   */
U4      u4_g_oXCANUsrhkExirIRQst(const U1 u1_a_CTRLR);                   /* called from oxcan_aubif.c :: Can_UEdgeGetStatus     */

U1      u1_g_oXCANUsrhkPwonBusAwake(void);                               /* called from libbswcs.a via syshook.c                */

void    vd_g_oXCANUsrhkTrcvToAct(const U1 u1_a_CH);                      /* called from libbswcs.a via syshook.c                */
void    vd_g_oXCANUsrhkTrcvToInact(const U1 u1_a_CH);                    /* called from libbswcs.a via syshook.c                */

void    vd_g_oXCANUsrhkEvtxReqed(const U2 u2_a_MSG);                     /* called from libbswcs.a via syshook.c                */

void    vd_g_oXCANUsrhkTxConfirm(const U2 u2_a_MSG, const U1 u1_a_CH, const U1 u1_a_TXMODE);
                                                                         /* called from libbswcs.a via syshook.c                */
void    vd_g_oXCANUsrhkTxAck(const U2 u2_a_MSG);                         /* called from libbswcs.a via syshook.c                */

void    vd_g_oXCANUsrhkRxMsg(const U2 u2_a_MSG);                         /* called from libbswcs.a via syshook.c                */

void    vd_g_oXCANUsrhkNwToAct(const U1 u1_a_CH);                        /* called from oxcan_bodycom.c                         */

U1      u1_g_oXCANUsrhkCntChk(const U2 u2_a_MSG, const U1 u1_a_CHKRST, const U1 u1_a_PREV, const U1 u1_a_NEXT);
                                                                         /* called from oxcan_aubif.c :: Com_CbkCounterErr      */
void    vd_g_oXCANUsrhkSumErr(const U2 u2_a_PDUID);                      /* called from oxcan_aubif.c :: CanIf_CbkSumErr        */
void    vd_g_oXCANUsrhkDlcErr(const U2 u2_a_PDUID);                      /* called from oxcan_aubif.c :: CanIf_CbkLengthErr     */
#if (OXCAN_NMDIAG_GBL_SUP == 1U)
void    vd_g_oXCANUsrhkPreStoreMsg(const U1 u1_a_CH, const U4 u4_a_CANID);
                                                                         /* called from oxcan_aubif.c :: CanIf_CbkPreStoreMsg   */
#endif  /* #if (OXCAN_NMDIAG_GBL_SUP == 1U) */
void    vd_g_oXCANUsrhkTxTOut(const U2 u2_a_MSG);                        /* called from libbswcs.a via syshook.c                */

void    vd_g_oXCANUsrhkDetectBusoff(const U1 u1_a_NW);                   /* called from libbswcs.a via syshook.c                */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif /* OXCAN_USRHK_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see  oxcan_usrhk.c                                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/
