/* Dcm_Dsp_SID10_Callout_h(v5-0-0)                                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID10_Callout/HEADER                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DCM_DSP_SID10_CALLOUT_H
#define DCM_DSP_SID10_CALLOUT_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>
#if ( DCM_SUPPORT_SID10 == STD_ON )

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
FUNC( Std_ReturnType, DCM_CODE_CALLOUT ) Dcm_SetProgConditions
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_ProgConditionsType, AUTOMATIC, DCM_APPL_DATA ) ProgConditions
);

FUNC( Std_ReturnType, DCM_CODE_CALLOUT ) Dcm_CheckSessionControl
(
    const uint8 u1SubFunction,
    Dcm_OpStatusType OpStatus,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
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

#endif /* DCM_SUPPORT_SID10 == STD_ON */
#endif /* DCM_DSP_SID10_CALLOUT_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v5-0-0         :2022-03-29                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-5-1                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
