/* SchM_IdsM_h_v2-0-0                                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | SchM_IdsM/HEADER                                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef SCHM_IDSM_H
#define SCHM_IDSM_H

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

#define IDSM_START_SEC_CODE
#include <IdsM_MemMap.h>

FUNC(void, IDSM_CODE) IdsM_MainFunction(void);

#define IDSM_STOP_SEC_CODE
#include <IdsM_MemMap.h>

#define IDSM_START_SEC_CODE
#include <IdsM_MemMap.h>

FUNC(void, IDSM_CODE) IdsM_Ab_MainFunctionTx(void);

#define IDSM_STOP_SEC_CODE
#include <IdsM_MemMap.h>


/*----------------------------------*/
/* Bsw ExclusiveArea Api Prototype  */
/*----------------------------------*/

#define SCHM_START_SEC_CODE_CALLOUT
#include <SchM_MemMap.h>

FUNC(void, SCHM_CODE_CALLOUT) SchM_Enter_IdsM_General(void);
FUNC(void, SCHM_CODE_CALLOUT) SchM_Exit_IdsM_General(void);

FUNC(void, SCHM_CODE_CALLOUT) SchM_Enter_IdsM_State(void);
FUNC(void, SCHM_CODE_CALLOUT) SchM_Exit_IdsM_State(void);

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

#endif /* SCHM_IDSM_H */


/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-3-z0003                                        */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
