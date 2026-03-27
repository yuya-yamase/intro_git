/* Dcm_Dsp_SID22_h(v5-4-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID22/HEADER                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DCM_DSP_SID22_H
#define DCM_DSP_SID22_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../../Dcm/Dsp/cfg/Dcm_Dsp_SID22_Cfg.h"
#include <Dcm/Dcm_Main_Common.h>
#include <Dcm.h>
#if ( DCM_SUPPORT_SID22 == STD_ON )

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

FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID22
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
);
FUNC( void, DCM_CODE ) Dcm_Dsp_SID22_IsDidAvailableCbk
(
    const uint8 u1EventId
);
FUNC( void, DCM_CODE ) Dcm_Dsp_SID22_ReadDidDataCbk
(
    const uint8 u1EventId
);
FUNC( void, DCM_CODE ) Dcm_Dsp_SID22_DidRangeDataLenCbk
(
    const uint8 u1EventId
);
FUNC(void, DCM_CODE) Dcm_Dsp_SID22_CheckSupportCbk
(
    const uint8 u1EventId
);

#if ( DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON )
FUNC(void, DCM_CODE) Dcm_Dsp_SID22_UpdatePageCbk
(
    const uint8 u1EventId
);
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID22_UpdatePage
(
    Dcm_MsgType     ptResData,
    Dcm_MsgLenType  u4ResMaxDataLen
);
FUNC(void, DCM_CODE) Dcm_Dsp_SID22_CancelPage
(void);
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* DCM_SUPPORT_SID22 == STD_ON */
#endif /* DCM_DSP_SID22_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v3-0-0         :2019-05-29                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-4-0         :2023-06-28                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

