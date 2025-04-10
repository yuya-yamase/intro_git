/* Dcm_Dsl_CommHandling_h(v5-0-0)                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/
/****************************************************************************/
/* Object Name | Dcm/Dsl_CommHandling/HEADER                                */
/*--------------------------------------------------------------------------*/
/* Notes |                                                                  */
/****************************************************************************/
#ifndef DCM_DSL_COMMHANDLING_H
#define DCM_DSL_COMMHANDLING_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>
#include "../../Dsl/inc/Dcm_Dsl_Main.h"
/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSL_REQ_ACTIVE              ((uint8)0x00U)
#define DCM_DSL_REQ_INACTIVE            ((uint8)0x01U)


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct {
    uint8   u1ComModeState;
    boolean bActiveIndicationFlag;
} Dcm_Dsl_ComModeType;


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

FUNC(void, DCM_CODE) Dcm_Dsl_CmHdl_Init
(void);

FUNC(boolean, DCM_CODE) Dcm_Dsl_CmHdl_IsComEnable
(
    const uint16 u2PduIdMapIndex,
    const uint8 u1CommunicationType
);

FUNC(void, DCM_CODE) Dcm_Dsl_CmHdl_CallActive
(
    const uint16 u2PduIdMapIndex,
    const uint8 u1RequestActive,
    const boolean bActiveClient
);

FUNC(void, DCM_CODE) Dcm_Dsl_CmHdl_CallInactiveAllCh
(void);

FUNC(void, DCM_CODE) Dcm_Dsl_CmHdl_Refresh
(void);

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* DCM_DSL_COMMHANDLING_H */
/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-07-27                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v5-0-0         :2022-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
