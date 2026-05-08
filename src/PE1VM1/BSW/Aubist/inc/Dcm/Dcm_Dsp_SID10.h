/* Dcm_Dsp_SID10_h(v5-8-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID10/HEADER                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DCM_DSP_SID10_H
#define DCM_DSP_SID10_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../../Dcm/Dsp/cfg/Dcm_Dsp_SID10_Cfg.h"
#include <Dcm.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_NO_BOOT                 ((uint8)0U)
#define DCM_OEM_BOOT                ((uint8)1U)
#define DCM_SYS_BOOT                ((uint8)2U)
#define DCM_OEM_BOOT_RESPAPP        ((uint8)3U)
#define DCM_SYS_BOOT_RESPAPP        ((uint8)4U)


#if ( DCM_SUPPORT_SID10 == STD_ON )
/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>
FUNC( void, DCM_CODE ) Dcm_Dsp_SID10_Init
( void );
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID10
(
    Dcm_OpStatusType u1OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext,
    const uint8 u1SubFunction
);
FUNC( void, DCM_CODE ) Dcm_Dsp_SID10_Confirmation
(
    const Dcm_IdContextType u1IdContext,
    const uint16 u2ConnectionId,
    const Dcm_ConfirmationStatusType u1Status
);
FUNC( void, DCM_CODE ) Dcm_Dsp_SID10_Cbk
(
    const uint8 u1EventId
);
FUNC( void, DCM_CODE ) Dcm_Dsp_SID10_ChkSesCtrlCbk
(
    const uint8 u1EventId
);

FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_GetP2ServerValue
(
    const Dcm_SesCtrlType u1SesCtrlType,
    const Dcm_ProtocolType u1ProtocolType,
    P2VAR( uint16, AUTOMATIC, DCM_APPL_DATA ) ptP2ServerMax,
    P2VAR( uint16, AUTOMATIC, DCM_APPL_DATA ) ptP2StarServerMax,
    P2VAR( uint16, AUTOMATIC, DCM_APPL_DATA ) ptP2StarServerLsb,
    P2VAR( uint16, AUTOMATIC, DCM_APPL_DATA ) ptP2StarServerMin
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

#endif /* DCM_SUPPORT_SID10 == STD_ON */
#endif /* DCM_DSP_SID10_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-8-0         :2024-10-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
