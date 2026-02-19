/* IdsM_Sink_h_v2-0-1                                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name | IdsM/Sink/HEADER                                           */
/*--------------------------------------------------------------------------*/
/* Notes       |                                                            */
/****************************************************************************/

#ifndef IDSM_SINK_H
#define IDSM_SINK_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define IDSM_START_SEC_CODE
#include <IdsM_MemMap.h>

FUNC(void, IDSM_CODE) IdsM_Sink_Init
(
    void
);

FUNC(void, IDSM_CODE) IdsM_Sink_TxMsgSizeCalc
(
    P2CONST(IdsMEventBuffType, AUTOMATIC, AUTOMATIC) ptEventInfo,
    P2VAR(uint16, AUTOMATIC, AUTOMATIC) ptTxMsgSize
);

FUNC(Std_ReturnType, IDSM_CODE) IdsM_Sink_SetBuff
(
    P2CONST(IdsMEventBuffType, AUTOMATIC, AUTOMATIC) ptEventInfo
);

#if (IDSM_CFG_USE_IDSR == STD_ON)
FUNC(void, IDSM_CODE) IdsM_Sink_IdsRTransmit
(
    void
);

FUNC(void, IDSM_CODE) IdsM_Sink_IdsRTxConfirmation
(
    VAR(PduIdType, AUTOMATIC) udPduId,
    VAR(Std_ReturnType, AUTOMATIC) udresult
);

FUNC(Std_ReturnType, IDSM_CODE) IdsM_Sink_IdsRTxConfirmationChk
(
    void
);

FUNC(void, IDSM_CODE) IdsM_Sink_IdsRQSEvErrNotify
(
    void
);
#endif  /* IDSM_CFG_USE_IDSR == STD_ON */

#if (IDSM_CFG_USE_DEM == STD_ON)
FUNC(void, IDSM_CODE) IdsM_Sink_DemTransmit
(
    void
);

FUNC(void, IDSM_CODE) IdsM_Sink_DemQSEvErrNotify
(
    void
);

FUNC(Std_ReturnType, IDSM_CODE) IdsM_Sink_DemReadCallback
(
    P2VAR(uint8, AUTOMATIC, IDSM_APPL_DATA) ptBuffer
);
#endif  /* IDSM_CFG_USE_DEM == STD_ON */

FUNC(void, IDSM_CODE) IdsM_Sink_QSEvBuffFullNotify
(
    P2CONST(IdsMEventBuffType, AUTOMATIC, AUTOMATIC) ptEventInfo
);

#if ((IDSM_CFG_RAM_ERROR_CHECK == STD_ON) && (IDSM_CFG_USE_IDSR == STD_ON))
FUNC(void, IDSM_CODE) IdsM_Sink_DetectRamError
(
    void
);
#endif /* ((IDSM_CFG_RAM_ERROR_CHECK == STD_ON) && (IDSM_CFG_USE_IDSR == STD_ON)) */

#define IDSM_STOP_SEC_CODE
#include <IdsM_MemMap.h>
/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* IDSM_SINK_H */

/****************************************************************************/
/* History                                                                  */
/*  Version    :Date                                                        */
/*  v2-0-0     :2022/11/30                                                  */
/*  v2-0-1     :2023/02/24                                                  */
/****************************************************************************/

/**** End of File ***********************************************************/
