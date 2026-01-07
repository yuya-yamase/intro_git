/* IdsM_Context_h_v2-0-0                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name | IdsM/Context/HEADER                                        */
/*--------------------------------------------------------------------------*/
/* Notes       |                                                            */
/****************************************************************************/

#ifndef IDSM_CONTEXT_H
#define IDSM_CONTEXT_H

#if ( IDSM_CFG_USE_CTXDATA == STD_ON )
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

FUNC(void, IDSM_CODE) IdsM_Context_Init
(
    void
);

FUNC(Std_ReturnType, IDSM_CODE) IdsM_Context_SetBuff
(
    P2CONST(uint8, AUTOMATIC, IDSM_APPL_CONST) ptData,
    VAR(uint16, AUTOMATIC) u2DataSize,
    P2VAR(uint16, AUTOMATIC, IDSM_APPL_DATA) ptCtxDataIndex1,
    P2VAR(uint16, AUTOMATIC, IDSM_APPL_DATA) ptCtxDataIndex2
);

FUNC(void, IDSM_CODE) IdsM_Context_ClearBuff
(
    VAR(uint16, AUTOMATIC) u2CtxDataIndex1,
    VAR(uint16, AUTOMATIC) u2CtxDataIndex2
);

FUNC(void, IDSM_CODE) IdsM_Context_GetCtxData
(
    VAR(uint16, AUTOMATIC) u2CtxDataIndex1,
    VAR(uint16, AUTOMATIC) u2CtxDataIndex2,
    VAR(uint16, AUTOMATIC) u2CtxDataSize,
    P2VAR(uint8, AUTOMATIC, IDSM_APPL_DATA) ptCtxData
);

FUNC_P2CONST(volatile uint8, IDSM_VAR_NO_INIT, IDSM_CODE) IdsM_Context_GetBuffAdr
(
    VAR(uint16, AUTOMATIC) u2CtxDataIndex1,
    VAR(uint16, AUTOMATIC) u2CtxDataIndex2
);

#define IDSM_STOP_SEC_CODE
#include <IdsM_MemMap.h>
/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* ( IDSM_CFG_USE_CTXDATA == STD_ON ) */
#endif /* IDSM_CONTEXT_H */

/****************************************************************************/
/* History                                                                  */
/*  Version    :Date                                                        */
/*  v2-0-0     :2022/11/30                                                  */
/****************************************************************************/

/**** End of File ***********************************************************/
