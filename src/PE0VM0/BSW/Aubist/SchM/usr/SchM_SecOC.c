/* SchM_SecOC_c_v2-0-0                                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | SchM_SecOC/CODE                                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

#include <SchM_SecOC.h>
#include "Os.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/


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


/*----------------------------------*/
/* Bsw ExclusiveArea Api            */
/*----------------------------------*/
#define SCHM_START_SEC_CODE_CALLOUT
#include <SchM_MemMap.h>

FUNC(void, SCHM_CODE_CALLOUT) SchM_Enter_SecOC_Tx(void){
    SuspendAllInterrupts();
    return;
}

FUNC(void, SCHM_CODE_CALLOUT) SchM_Exit_SecOC_Tx(void){
    ResumeAllInterrupts();
    return;
}

FUNC(void, SCHM_CODE_CALLOUT) SchM_Enter_SecOC_Rx(void){
    SuspendAllInterrupts();
    return;
}

FUNC(void, SCHM_CODE_CALLOUT) SchM_Exit_SecOC_Rx(void){
    ResumeAllInterrupts();
    return;
}

FUNC(void, SCHM_CODE_CALLOUT) SchM_Enter_SecOC_CD_FV(void){
    SuspendAllInterrupts();
    return;
}

FUNC(void, SCHM_CODE_CALLOUT) SchM_Exit_SecOC_CD_FV(void){
    ResumeAllInterrupts();
    return;
}

FUNC(void, SCHM_CODE_CALLOUT) SchM_Enter_SecOC_Buff(void){
    SuspendAllInterrupts();
    return;
}

FUNC(void, SCHM_CODE_CALLOUT) SchM_Exit_SecOC_Buff(void){
    ResumeAllInterrupts();
    return;
}

FUNC(void, SCHM_CODE_CALLOUT) SchM_Enter_SecOC_Extd(void){
    SuspendAllInterrupts();
    return;
}

FUNC(void, SCHM_CODE_CALLOUT) SchM_Exit_SecOC_Extd(void){
    ResumeAllInterrupts();
    return;
}

#define SCHM_STOP_SEC_CODE_CALLOUT
#include <SchM_MemMap.h>

/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
