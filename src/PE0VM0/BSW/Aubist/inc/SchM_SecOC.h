/* SchM_SecOC_h_v2-0-0                                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | SchM_SecOC/HEADER                                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef SCHM_SECOC_H
#define SCHM_SECOC_H

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

#define SECOC_START_SEC_CODE
#include <SecOC_MemMap.h>

FUNC(void, SECOC_CODE) SecOC_MainFunctionTx(void);

#define SECOC_STOP_SEC_CODE
#include <SecOC_MemMap.h>

#define SECOC_START_SEC_CODE
#include <SecOC_MemMap.h>

FUNC(void, SECOC_CODE) SecOC_MainFunctionRx(void);

#define SECOC_STOP_SEC_CODE
#include <SecOC_MemMap.h>


/*----------------------------------*/
/* Bsw ExclusiveArea Api Prototype  */
/*----------------------------------*/

#define SCHM_START_SEC_CODE_CALLOUT
#include <SchM_MemMap.h>

FUNC(void, SCHM_CODE_CALLOUT) SchM_Enter_SecOC_Tx(void);
FUNC(void, SCHM_CODE_CALLOUT) SchM_Exit_SecOC_Tx(void);

FUNC(void, SCHM_CODE_CALLOUT) SchM_Enter_SecOC_Rx(void);
FUNC(void, SCHM_CODE_CALLOUT) SchM_Exit_SecOC_Rx(void);

FUNC(void, SCHM_CODE_CALLOUT) SchM_Enter_SecOC_CD_FV(void);
FUNC(void, SCHM_CODE_CALLOUT) SchM_Exit_SecOC_CD_FV(void);

FUNC(void, SCHM_CODE_CALLOUT) SchM_Enter_SecOC_Buff(void);
FUNC(void, SCHM_CODE_CALLOUT) SchM_Exit_SecOC_Buff(void);

FUNC(void, SCHM_CODE_CALLOUT) SchM_Enter_SecOC_Extd(void);
FUNC(void, SCHM_CODE_CALLOUT) SchM_Exit_SecOC_Extd(void);

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

#endif /* SCHM_SECOC_H */


/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
