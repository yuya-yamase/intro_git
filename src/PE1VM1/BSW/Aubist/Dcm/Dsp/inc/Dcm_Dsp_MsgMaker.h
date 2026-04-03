/* Dcm_Dsp_MsgMaker_h(v5-0-0)                                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_MsgMaker/HEADER                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DCM_DSP_MSGMAKER_H
#define DCM_DSP_MSGMAKER_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../../Dsp/cfg/Dcm_Dsp_MsgMaker_Cfg.h"
#include <Dcm.h>

#include <Dcm/Dcm_Dsd_SendMng.h>
#include <Dcm/Dcm_Main_Common.h>

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

#if ( DCM_USE_PROVIDE_SERVICE == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Dsp_MsgMaker_SendNegRes
(
    P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext,
    const Dcm_NegativeResponseCodeType u1ErrorCode
);
#endif /* DCM_USE_PROVIDE_SERVICE == STD_ON */
#if ( DCM_USE_PROVIDE_SERVICE == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Dsp_MsgMaker_SendPosRes
(
    P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
);
#endif /* DCM_USE_PROVIDE_SERVICE == STD_ON */
FUNC( void, DCM_CODE ) DspInternal_DcmConfirmation
(
    Dcm_IdContextType idContext,
    uint16 ConnectionId,
    Dcm_ConfirmationStatusType status
);
#if ( DCM_PAGEDBUFFER_ENABLED == STD_ON )
FUNC(void, DCM_CODE) Dcm_Dsp_MsgMaker_SrvInit
(void);
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_ON */

#if ( DCM_PAGEDBUFFER_ENABLED == STD_ON )
#if ( DCM_USE_PROVIDE_SERVICE == STD_ON )
FUNC(void, DCM_CODE) Dcm_Dsp_MsgMaker_StartPagedProcessing
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext,
    const uint16 u2PagedBufferId
);
FUNC(void, DCM_CODE) Dcm_Dsp_MsgMaker_ProcessPage
(
    const Dcm_MsgLenType FilledPageLen
);
#endif /* DCM_USE_PROVIDE_SERVICE == STD_ON */
FUNC(Std_ReturnType, DCM_CODE) DspInternal_DcmUpdatePage
(
    Dcm_MsgType     ptResData,
    Dcm_MsgLenType  u4ResMaxDataLen
);
FUNC(void, DCM_CODE) DspInternal_CancelPagedBufferProcessing
(void);
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_ON */


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


#endif /* DCM_DSP_MSGMAKER_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v3-0-0         :2019-07-29                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v5-0-0         :2022-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
