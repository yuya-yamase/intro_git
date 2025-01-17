/* SchM_Dem_c_v2-0-0                                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | SchM_Dem/CODE                                             */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

#include <SchM_Dem.h>

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

FUNC(void, SCHM_CODE_CALLOUT) SchM_Enter_Dem_EventQueueBufferAccess(void){
    return;
}

FUNC(void, SCHM_CODE_CALLOUT) SchM_Exit_Dem_EventQueueBufferAccess(void){
    return;
}

FUNC(void, SCHM_CODE_CALLOUT) SchM_Enter_Dem_EventMemory(void){
    return;
}

FUNC(void, SCHM_CODE_CALLOUT) SchM_Exit_Dem_EventMemory(void){
    return;
}

FUNC(void, SCHM_CODE_CALLOUT) SchM_Enter_Dem_CheckClearDTCStatus(void){
    return;
}

FUNC(void, SCHM_CODE_CALLOUT) SchM_Exit_Dem_CheckClearDTCStatus(void){
    return;
}

FUNC(void, SCHM_CODE_CALLOUT) SchM_Enter_Dem_ModeAccess(void){
    return;
}

FUNC(void, SCHM_CODE_CALLOUT) SchM_Exit_Dem_ModeAccess(void){
    return;
}

FUNC(void, SCHM_CODE_CALLOUT) SchM_Enter_Dem_CheckControlDTCSetting(void){
    return;
}

FUNC(void, SCHM_CODE_CALLOUT) SchM_Exit_Dem_CheckControlDTCSetting(void){
    return;
}

FUNC(void, SCHM_CODE_CALLOUT) SchM_Enter_Dem_WIRStatusAccess(void){
    return;
}

FUNC(void, SCHM_CODE_CALLOUT) SchM_Exit_Dem_WIRStatusAccess(void){
    return;
}

FUNC(void, SCHM_CODE_CALLOUT) SchM_Enter_Dem_NvMRecordAccess(void){
    return;
}

FUNC(void, SCHM_CODE_CALLOUT) SchM_Exit_Dem_NvMRecordAccess(void){
    return;
}

#define SCHM_STOP_SEC_CODE_CALLOUT
#include <SchM_MemMap.h>

/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-2                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
