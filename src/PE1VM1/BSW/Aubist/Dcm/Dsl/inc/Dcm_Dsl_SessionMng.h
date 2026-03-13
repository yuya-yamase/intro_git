/* Dcm_Dsl_SessionMng_h(v5-3-0)                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name | DCM/Dsl_SessionMng/HEADER                                  */
/*--------------------------------------------------------------------------*/
/* Notes |                                                                  */
/****************************************************************************/
#ifndef DCM_DSL_SESSIONMNG_H
#define DCM_DSL_SESSIONMNG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>
#include "../../Dsl/inc/Dcm_Dsl_Main.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

FUNC(void, DCM_CODE) Dcm_Dsl_SessionMng_Init
(void);

#if( DCM_M_RESPONSE_AFTER_REBOOT == STD_ON )
FUNC(void, DCM_CODE) Dcm_Dsl_SessionMng_SetInitialSession
(
    const Dcm_SesCtrlType u1SesCtrlType
);
#endif /* DCM_M_RESPONSE_AFTER_REBOOT == STD_ON */

FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsl_SessionMng_GetSesCtrlType
(
    P2VAR(Dcm_SesCtrlType, AUTOMATIC, DCM_APPL_DATA) ptSesCtrlType
);

FUNC(void, DCM_CODE) Dcm_Dsl_SessionMng_SetSesCtrlType
(
    const Dcm_SesCtrlType u1SesCtrlType,
    const boolean bDelayUpdate,
    const uint8 u1SesChgKind
);

FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsl_SessionMng_SwitchModeSesCtrl
(
    const uint8 u1Mode
);

FUNC(void, DCM_CODE) Dcm_Dsl_SessionMng_SetSesConf
(
    const boolean bUpdateEnable
);

FUNC(void, DCM_CODE) Dcm_Dsl_SessionMng_ReqSesCtrlChgNotification
(void);

FUNC(void, DCM_CODE) Dcm_Dsl_SessionMng_Refresh
(void);

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* DCM_DSL_SESSIONMNG_H */
/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v3-0-0         :2019-05-29                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
