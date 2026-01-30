/* Dcm_Main_EvtDistr_h(v3-2-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Main_EvtDistr/HEADER                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DCM_MAIN_EVTDISTR_H
#define DCM_MAIN_EVTDISTR_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../../Dcm/Main/cfg/Dcm_Main_EvtDistr_Cfg.h"

#include <Dcm.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Dcm_Main_EvtDistr_RetType */
#define DCM_MAIN_EVTDISTR_E_OK          ((uint8)0x00U)      /* OK */
#define DCM_MAIN_EVTDISTR_E_ID          ((uint8)0x01U)      /* Invalid ID */
#define DCM_MAIN_EVTDISTR_E_OVERFLOW    ((uint8)0x02U)      /* Queue overflow */
#define DCM_MAIN_EVTDISTR_E_NOTFOUND    ((uint8)0x03U)      /* ID Not Found In Queue */
#define DCM_M_EVTDISTR_ID_DELETED       ((uint8)0xFFU)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef uint8               Dcm_Main_EvtDistr_RetType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>
FUNC( void, DCM_CODE ) Dcm_Main_EvtDistr_Init
( void );
FUNC( void, DCM_CODE ) Dcm_Main_EvtDistr_Main
( void );
FUNC( Dcm_Main_EvtDistr_RetType, DCM_CODE ) Dcm_Main_EvtDistr_SendEvent
(
    const uint8 u1EventId
);
FUNC( Dcm_Main_EvtDistr_RetType, DCM_CODE ) Dcm_Main_EvtDistr_DeleteEvent
(
    const uint8   u1DelEvendId,
    const boolean bOneEntry
);

#define DCM_STOP_SEC_CODE
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

#endif /* DCM_MAIN_EVTDISTR_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v3-2-0         :2020-10-28                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
