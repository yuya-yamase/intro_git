/* Dcm_Dsp_SID2F_h(v5-0-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID2F/HEADER                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DCM_DSP_SID2F_H
#define DCM_DSP_SID2F_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../../Dcm/Dsp/cfg/Dcm_Dsp_SID2F_Cfg.h"
#include <Dcm.h>
#if ( DCM_SUPPORT_SID2F == STD_ON )

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
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID2F
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
);
FUNC( void, DCM_CODE ) Dcm_Dsp_SID2F_IOControlCbk
(
    const uint8 u1EventId
);
FUNC( void, DCM_CODE ) Dcm_Dsp_SID2F_ReadDataCbk
(
    const uint8 u1EventId
);
FUNC( void, DCM_CODE ) Dcm_Dsp_SID2F_RetCtrl_ByChgSec
(
    const Dcm_SecLevelType u1SecLevelOld,
    const Dcm_SecLevelType u1SecLevelNew
);
FUNC( void, DCM_CODE ) Dcm_Dsp_SID2F_RetCtrl_ByChgSes
(
    const Dcm_SesCtrlType u1SesCtrlTypeOld,
    const Dcm_SesCtrlType u1SesCtrlTypeNew
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

#endif /* DCM_SUPPORT_SID2F == STD_ON */
#endif /* DCM_DSP_SID2F_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v5-0-0         :2022-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
