/* Dcm_Dsp_SID19_Sub42_h(v5-5-0)                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID19_Sub42/HEADER                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DCM_DSP_SID19_SUB42_H
#define DCM_DSP_SID19_SUB42_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>
#if ( DCM_SUPPORT_SID19_SUB42 == STD_ON )

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

FUNC(Std_ReturnType, DCM_CODE) Dcm_SID19_Sub42
(
    Dcm_OpStatusType OpStatus,
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext
);
FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub42_GetDTCCbk
(
    const uint8 u1EventId
);
#if ( DCM_PAGEDBUFFER_SID19_SUB42_ENABLED == STD_ON )
FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub42_GetSizeOfDTCCbk
(
    const uint8 u1EventId
);
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub42_UpdatePage
(
    Dcm_MsgType     ptResData,
    Dcm_MsgLenType  u4ResMaxDataLen
);
FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub42_CancelPage
(
    void
);
#endif /* DCM_PAGEDBUFFER_SID19_SUB42_ENABLED == STD_ON */

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


#endif /* DCM_SUPPORT_SID19_SUB42 == STD_ON */
#endif /* DCM_DSP_SID19_SUB42_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-2-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File************************************************************/
