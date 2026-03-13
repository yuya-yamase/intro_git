/* SchM_Dcm_h_v2-0-0                                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | SchM_Dcm/HEADER                                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef SCHM_DCM_H
#define SCHM_DCM_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

#include <Std_Types.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/*----------------------------------*/
/* Entry Point Prototype            */
/*----------------------------------*/

#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

FUNC(void, DCM_CODE) Dcm_MainFunction(void);

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>


/*----------------------------------*/
/* Bsw ExclusiveArea Api Prototype  */
/*----------------------------------*/

#define SCHM_START_SEC_CODE_CALLOUT
#include <SchM_MemMap.h>

FUNC(void, SCHM_CODE_CALLOUT) SchM_Enter_Dcm_Dsl_CmHdl(void);
FUNC(void, SCHM_CODE_CALLOUT) SchM_Exit_Dcm_Dsl_CmHdl(void);

FUNC(void, SCHM_CODE_CALLOUT) SchM_Enter_Dcm_Dsl_SecLevel(void);
FUNC(void, SCHM_CODE_CALLOUT) SchM_Exit_Dcm_Dsl_SecLevel(void);

FUNC(void, SCHM_CODE_CALLOUT) SchM_Enter_Dcm_Dsl_Session(void);
FUNC(void, SCHM_CODE_CALLOUT) SchM_Exit_Dcm_Dsl_Session(void);

FUNC(void, SCHM_CODE_CALLOUT) SchM_Enter_Dcm_Dsl_TxPduInfo(void);
FUNC(void, SCHM_CODE_CALLOUT) SchM_Exit_Dcm_Dsl_TxPduInfo(void);

FUNC(void, SCHM_CODE_CALLOUT) SchM_Enter_Dcm_Main_EvtDistr(void);
FUNC(void, SCHM_CODE_CALLOUT) SchM_Exit_Dcm_Main_EvtDistr(void);

FUNC(void, SCHM_CODE_CALLOUT) SchM_Enter_Dcm_Main_TmrSrv(void);
FUNC(void, SCHM_CODE_CALLOUT) SchM_Exit_Dcm_Main_TmrSrv(void);

FUNC(void, SCHM_CODE_CALLOUT) SchM_Enter_Dcm_Dsl_Ctrl(void);
FUNC(void, SCHM_CODE_CALLOUT) SchM_Exit_Dcm_Dsl_Ctrl(void);

FUNC(void, SCHM_CODE_CALLOUT) SchM_Enter_Dcm_Dsp_Roe(void);
FUNC(void, SCHM_CODE_CALLOUT) SchM_Exit_Dcm_Dsp_Roe(void);

#define SCHM_STOP_SEC_CODE_CALLOUT
#include <SchM_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* SCHM_DCM_H */


/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
