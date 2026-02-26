/* Dcm_Dsp_SID23_h(v5-0-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID23/HEADER                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DCM_DSP_SID23_H
#define DCM_DSP_SID23_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../../Dcm/Dsp/cfg/Dcm_Dsp_SID23_Cfg.h"
#if ( DCM_SUPPORT_SID23 == STD_ON )
#include <Dcm/Dcm_Main_Common.h>
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

FUNC(Std_ReturnType, DCM_CODE) Dcm_SID23
(
    Dcm_OpStatusType                                        OpStatus,
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA)   pMsgContext
);
FUNC(void, DCM_CODE) Dcm_Dsp_SID23_Cbk
(
    const uint8 u1EventId
);

#if ( DCM_PAGEDBUFFER_SID23_ENABLED == STD_ON )
FUNC(void, DCM_CODE) Dcm_Dsp_SID23_UpdatePageCbk
(
    const uint8 u1EventId
);
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID23_UpdatePage
(
    Dcm_MsgType     ptResData,
    Dcm_MsgLenType  u4ResMaxDataLen
);
FUNC(void, DCM_CODE) Dcm_Dsp_SID23_CancelPage
(void);
#endif /* DCM_PAGEDBUFFER_SID23_ENABLED == STD_ON */

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


#endif /* DCM_SUPPORT_SID23 == STD_ON */
#endif /* DCM_DSP_SID23_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v3-0-0         :2019-05-29                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v5-0-0         :2022-03-29                                              */
/****************************************************************************/

/**** End of File************************************************************/
