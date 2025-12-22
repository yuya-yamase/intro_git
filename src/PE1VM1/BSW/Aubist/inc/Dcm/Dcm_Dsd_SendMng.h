/* Dcm_Dsd_SendMng_h(v5-3-0)                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name | DCM/Dsd_SendMng/HEADER                                     */
/*--------------------------------------------------------------------------*/
/* Notes |                                                                  */
/****************************************************************************/
#ifndef DCM_DSD_SENDMNG_H
#define DCM_DSD_SENDMNG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>
#include <Dcm/Dcm_Main_Common.h>

/*--------------------------------------------------------------------------*/
/* Macros */
/*--------------------------------------------------------------------------*/
#define DCM_DSD_NORES_RANGE_MASK ((uint8)0x40U)
#if( DCM_PAGEDBUFFER_ENABLED == STD_ON )
#define DCM_DSD_UPDATEPAGE_INITIAL_ACT  ((uint32)0x00000000U)
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_ON */


/*--------------------------------------------------------------------------*/
/* Types */
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/* Function Prototypes */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>
FUNC(void, DCM_CODE) Dcm_Dsd_SendMng_Init
(void);

FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsd_DataConfirmationFunctionality
(
    const Dcm_ConfirmationStatusType u1ConfirmationStatus,
    const boolean bIsSendForcedPending
);

FUNC(void, DCM_CODE) Dcm_Dsd_SendMng_ClrStoredData
(void);

FUNC(void, DCM_CODE) Dcm_Dsd_SendMng_SendNoResNeg
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
);

#if( DCM_PAGEDBUFFER_ENABLED == STD_ON )
FUNC(void, DCM_CODE) DsdInternal_StartPagedProcessing
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext
);

FUNC(void, DCM_CODE) DsdInternal_ProcessPage
(
    Dcm_MsgLenType FilledPageLen
);

FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsd_UpdatePage
(
    Dcm_MsgType     ptResData,
    Dcm_MsgLenType  u4ResMaxDataLen
);

FUNC(void, DCM_CODE) Dcm_Dsd_CancelPagedBufferProcessing
(void);

FUNC(Dcm_MsgLenType, DCM_CODE) Dcm_Dsd_GetResponseDataLength
(void);
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_ON */


FUNC(boolean, DCM_CODE) Dcm_Dsd_IsSuppressNegMsg
(
    const uint8 u1SID,
    const Dcm_NegativeResponseCodeType u1Nrc,
    const uint16 u2ConnectionId
);

#if( DCM_SID86_ROE_USE == STD_ON )
FUNC( Dcm_StatusType, DCM_CODE ) Dcm_Dsd_RoeSendReq
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext,
    const uint16 u2ConnectionId
);
#endif /* DCM_SID86_ROE_USE == STD_ON */

#if ( DCM_DIAG_COM_DATA_PROVIDE_USE == STD_ON )
FUNC(void, DCM_CODE) Dcm_Dsd_ProvideDiagComData
(
    P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext,
    const uint8 u1ResponseKind
);
#endif /* DCM_DIAG_COM_DATA_PROVIDE_USE == STD_ON */


#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>


#define DCM_STOP_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CONST
#include <Dcm_MemMap.h>


#define DCM_STOP_SEC_CONST
#include <Dcm_MemMap.h>

#endif /* DCM_DSDSEND_MNG_H */
/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v3-0-0         :2019-05-29                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
