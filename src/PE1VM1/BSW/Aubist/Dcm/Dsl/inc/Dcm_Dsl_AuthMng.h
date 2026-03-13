/* Dcm_Dsl_AuthMng_h(v5-0-0)                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name | DCM/Dsl_AuthMng/HEADER                                     */
/*--------------------------------------------------------------------------*/
/* Notes |                                                                  */
/****************************************************************************/
#ifndef DCM_DSL_AUTHMNG_H
#define DCM_DSL_AUTHMNG_H

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
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

#if( DCM_AUTHENTICATION_USE == STD_ON )
FUNC(void, DCM_CODE) Dcm_Dsl_AuthMng_Init
(void);

FUNC(void, DCM_CODE) Dcm_Dsl_AuthMng_GetAuthState
(
    const uint16 u2ConnectionId,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptAuthenticated
);

FUNC(void, DCM_CODE) Dcm_Dsl_AuthMng_SetAuthState
(
    const uint8 u1Authenticated,
    const uint16 u2ConnectionId,
    const boolean bDelayUpdate
);

FUNC(void, DCM_CODE) Dcm_Dsl_AuthMng_SetAuthConf
(
    const uint16 u2ConnectionId,
    const boolean bUpdateEnable
);

FUNC(void, DCM_CODE) Dcm_Dsl_AuthMng_ReqAuthStateChangeNotification
(
    const uint16 u2ConnectionId
);
#endif /* DCM_AUTHENTICATION_USE == STD_ON */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* DCM_DSL_AUTHMNG_H */
/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
