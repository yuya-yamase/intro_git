/* Dcm_Dsp_SID86_Callout_h(v5-0-0)                                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID86_Callout/HEADER                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DCM_DSP_SID86_CALLOUT_H
#define DCM_DSP_SID86_CALLOUT_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE_CALLOUT
#include <Dcm_MemMap.h>

FUNC( Std_ReturnType, DCM_CODE_CALLOUT ) Dcm_SetComparisonOfValues
(
    const uint8 u1RoeEventId,
    P2CONST( Dcm_ComparisonValueType, AUTOMATIC, DCM_APPL_DATA ) ptRecord
);

FUNC( Std_ReturnType, DCM_CODE_CALLOUT ) Dcm_CheckRoeCondition
(
    const uint8 u1SubFunction,
    const uint8 u1EventWindowTime,
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA ) ptEventTypeRecord,
    const uint8 u1EventTypeRecordLength,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
);

FUNC( Std_ReturnType, DCM_CODE_CALLOUT ) Dcm_IndicateRoeStatusChange
(
    void
);

#define DCM_STOP_SEC_CODE_CALLOUT
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>


#define DCM_STOP_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CONST
#include <Dcm_MemMap.h>


#define DCM_STOP_SEC_CONST
#include <Dcm_MemMap.h>


#endif /* DCM_DSP_SID86_CALLOUT_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2021-09-28                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-10-0                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
