/* Dcm_Dsp_SID36_h(v5-3-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID36/HEADER                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DCM_DSP_SID36_H
#define DCM_DSP_SID36_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>

#if( DCM_SUPPORT_SID36 == STD_ON )

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

FUNC( void, DCM_CODE ) Dcm_Dsp_SID36_Init
( void );

FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID36
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
);

FUNC( void, DCM_CODE ) Dcm_Dsp_SID36_ChkMsgLenCbk
(
    const uint8 u1EventId
);

FUNC( void, DCM_CODE ) Dcm_Dsp_SID36_ChkReqSequenceCbk
(
    const uint8 u1EventId
);

#if ( DCM_UL_PROCESS_USE == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Dsp_SID36_ChkReqSequenceUpLoadCbk
(
    const uint8 u1EventId
);
#endif  /* DCM_UL_PROCESS_USE == STD_ON */

FUNC( void, DCM_CODE ) Dcm_Dsp_SID36_ChkTfrDataSuspendedCbk
(
    const uint8 u1EventId
);

#if ( DCM_UL_PROCESS_USE == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Dsp_SID36_ChkTfrDataSuspendedUpLoadCbk
(
    const uint8 u1EventId
);
#endif  /* DCM_UL_PROCESS_USE == STD_ON */

FUNC( void, DCM_CODE ) Dcm_Dsp_SID36_ProcTfrDataWriteCbk
(
    const uint8 u1EventId
);

#if ( DCM_UL_PROCESS_USE == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Dsp_SID36_ProcTfrDataReadCbk
(
    const uint8 u1EventId
);
#endif  /* DCM_UL_PROCESS_USE == STD_ON */

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

#endif /* DCM_SUPPORT_SID36 == STD_ON */
#endif /* DCM_DSP_SID36_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
