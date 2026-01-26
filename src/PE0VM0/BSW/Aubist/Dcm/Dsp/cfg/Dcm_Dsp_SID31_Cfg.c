/* Dcm_Dsp_SID31_Cfg_c(v5-5-1)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID31_Cfg/CODE                                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsp_SID31_ChkSuptRid_Callout.h>
#include "../../Dsp/cfg/Dcm_Dsp_SID31_Cfg.h"
#if ( DCM_SUPPORT_SID31 == STD_ON )
#include <Dcm/Dcm_Dsp_Main.h>
#include <Dcm/Dcm_Main_Common.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>

/*---------------------------------------*/
/*-----CommonAuthorization(parameter)----*/
/*---------------------------------------*/


static CONST ( AB_83_ConstV Dcm_Dsp_CommonAuthorizationType, DCM_CONFIG_DATA ) Dcm_P_SID31_ComAuth_Tbl[ DCM_P_COMAUTH_T ] =
{
    { NULL_PTR                       , NULL_PTR                       }  /* no parameter */
};

CONST ( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_P_SID31_ComAuth_INDEX_Tbl[ DCM_P_RID_T ] =
{
    (uint16)0U         /* no parameter */
};

/*------------------------------------------*/
/*-----CommonAuthorization(Multiplicity)----*/
/*------------------------------------------*/
CONST ( AB_83_ConstV Dcm_Dsp_SID31_ComAuthNumType, DCM_CONFIG_DATA ) Dcm_P_SID31_ComAuthN_Tbl[ DCM_P_COMAUTH_T ] =
{
    { (uint8)0U               , (uint8)0U              } /* no parameter */
};



/*------------------------------------------*/
/*------------ReqRslt(parameter)------------*/
/*------------------------------------------*/
CONST ( AB_83_ConstV Dcm_Dsp_RoutineInOutType, DCM_CONFIG_DATA ) Dcm_P_SID31_ReqRsltIn_Tbl[ DCM_P_RID_T ] = 
{
    /* DcmDspRequestRoutineResultsInSignal */
    { NULL_PTR                       } /* no parameter */
};


CONST ( AB_83_ConstV Dcm_Dsp_RoutineInOutType, DCM_CONFIG_DATA ) Dcm_P_SID31_ReqRsltOut_Tbl[ DCM_P_RID_T ] = 
{
    /* DcmDspRequestRoutineResultsOutSignal */
    { NULL_PTR                            } /* no parameter */
};

/*------------------------------------------*/
/*-----------ReqRslt(Multiplicity)----------*/
/*------------------------------------------*/
CONSTP2CONST ( AB_83_ConstV Dcm_Dsp_SID31_SigNumType, AUTOMATIC, DCM_APPL_CONST ) Dcm_P_SID31_RID_ReqRsltInNTbl[ DCM_P_RID_T ] =
{
    NULL_PTR                           /* no parameter */
};

CONSTP2CONST ( AB_83_ConstV Dcm_Dsp_SID31_SigNumType, AUTOMATIC, DCM_APPL_CONST ) Dcm_P_SID31_RID_ReqRsltOutNTbl[ DCM_P_RID_T ] =
{
    NULL_PTR                            /* no parameter */
};


/*------------------------------------------*/
/*-------------Start(parameter)-------------*/
/*------------------------------------------*/
CONST ( AB_83_ConstV Dcm_Dsp_RoutineInOutType, DCM_CONFIG_DATA ) Dcm_P_SID31_StaIn_Tbl[ DCM_P_RID_T ] = 
{
    /* DcmDspStartRoutineInSignal */
    { NULL_PTR                       } /* no parameter */
};

CONST ( AB_83_ConstV Dcm_Dsp_RoutineInOutType, DCM_CONFIG_DATA ) Dcm_P_SID31_StaOut_Tbl[ DCM_P_RID_T ] = 
{
    /* DcmDspStartRoutineOutSignal */
    { NULL_PTR                        } /* no parameter */
};

/*------------------------------------------*/
/*------------Start(Multiplicity)-----------*/
/*------------------------------------------*/
CONSTP2CONST ( AB_83_ConstV Dcm_Dsp_SID31_SigNumType, AUTOMATIC, DCM_APPL_CONST ) Dcm_P_SID31_RID_StaInNTbl[ DCM_P_RID_T ] =
{
    NULL_PTR                           /* no parameter */
};

CONSTP2CONST ( AB_83_ConstV Dcm_Dsp_SID31_SigNumType, AUTOMATIC, DCM_APPL_CONST ) Dcm_P_SID31_RID_StaOutNTbl[ DCM_P_RID_T ] =
{
    NULL_PTR                             /* no parameter */
};

/*------------------------------------------*/
/*--------------Stop(parameter)-------------*/
/*------------------------------------------*/
CONST ( AB_83_ConstV Dcm_Dsp_RoutineInOutType, DCM_CONFIG_DATA ) Dcm_P_SID31_StoIn_Tbl[ DCM_P_RID_T ] = 
{
    /* DcmDspStopRoutineInSignal */
    { NULL_PTR                       } /* no parameter */
};

CONST ( AB_83_ConstV Dcm_Dsp_RoutineInOutType, DCM_CONFIG_DATA ) Dcm_P_SID31_StoOut_Tbl[ DCM_P_RID_T ] = 
{
    /* DcmDspStopRoutineOutSignal */
    { NULL_PTR                        } /* no parameter */
};

/*------------------------------------------*/
/*-------------Stop(Multiplicity)-----------*/
/*------------------------------------------*/
CONSTP2CONST ( AB_83_ConstV Dcm_Dsp_SID31_SigNumType, AUTOMATIC, DCM_APPL_CONST ) Dcm_P_SID31_RID_StoInNTbl[ DCM_P_RID_T ] =
{
    NULL_PTR                           /* no parameter */
};

CONSTP2CONST ( AB_83_ConstV Dcm_Dsp_SID31_SigNumType, AUTOMATIC, DCM_APPL_CONST ) Dcm_P_SID31_RID_StoOutNTbl[ DCM_P_RID_T ] =
{
    NULL_PTR                            /* no parameter */
};

/*------------------------------------------*/
/*---------Routine_Common(parameter)--------*/
/*------------------------------------------*/
CONST ( AB_83_ConstV Dcm_Dsp_RoutineType, DCM_CONFIG_DATA ) Dcm_P_SID31_Routine_Tbl[ DCM_P_RID_T ] =
{
    /* Xxx_ReqRslt function */           /* Xxx_Start function */         /* Xxx_Stop function */         /* DcmDspRoutineIdentifier */ /* DcmDspRoutineInfoByte */ /* RoutineInfoUsed */ /* DcmDspRoutineUsePort */ /* DcmDspRoutineUsed */ /* DcmDspCommonAuthorizationRef */
    { NULL_PTR,                          NULL_PTR,                        NULL_PTR,                       (uint16)0U,                   (uint8)0x00U,               (boolean)FALSE,       (boolean)FALSE,            (boolean)FALSE,         &Dcm_P_SID31_ComAuth_Tbl[DCM_P_COMAUTH_T] } /* no parameter */
};

/*------------------------------------------*/
/*---------Routine_Common(Multiplicity)-----*/
/*------------------------------------------*/
CONST ( AB_83_ConstV Dcm_Dsp_SID31_RIDNumType, DCM_CONFIG_DATA ) Dcm_P_SID31_RIDN_Tbl[ DCM_P_RID_T ] = 
{
    { (uint8)0U , (uint8)0U ,
      (uint8)0U , (uint8)0U , (uint8)0U , (uint8)0U , (uint8)0U ,
      (uint8)0U , (uint8)0U , (uint8)0U , (uint8)0U , (uint8)0U ,
      (uint8)0U , (uint8)0U , (uint8)0U , (uint8)0U , (uint8)0U } /* no parameter */
};

/*--------------RID-------------*/
CONST( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_P_SID31_u2RIDNumber = DCM_P_RID_N;

/*------CommonAuthorization-----*/
CONST( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_P_SID31_u2Comauth_N = DCM_P_COMAUTH_N;

#define DCM_STOP_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID31_ReqResultsCout                             */
/* Description   | Routine request result read processing                   */
/* Preconditions | None                                                     */
/* Parameters    | [IN]     u2RoutineIndex : Routine index                  */
/*               | [IN/OUT] ptSigData      : Request/Response data          */
/*               | [IN]     u1OpStatus     : Operation state                */
/*               | [OUT]    ptErrorCode    : NRC                            */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Request was successful             */
/*               |   E_NOT_OK          : Request was not successful         */
/*               |   DCM_E_PENDING     : Request is not yet finished        */
/*               |   DCM_E_FORCE_RCRRP : RCRRP response                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID31_ReqResultsCout
(
    const uint16 u2RoutineIndex,                                                    /* MISRA DEVIATION */
    P2VAR( Dcm_Dsp_SID31_SigDataType, AUTOMATIC, DCM_APPL_DATA ) ptSigData,         /* MISRA DEVIATION */
    const Dcm_OpStatusType u1OpStatus,                                              /* MISRA DEVIATION */
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode     /* MISRA DEVIATION */
)
{
    Std_ReturnType u1_RetVal;
    
    u1_RetVal = E_OK;
    
    
    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID31_StartCout                                  */
/* Description   | Routine start processing                                 */
/* Preconditions | None                                                     */
/* Parameters    | [IN]     u2RoutineIndex : Routine index                  */
/*               | [IN/OUT] ptSigData      : Request/Response data          */
/*               | [IN]     u1OpStatus     : Operation state                */
/*               | [OUT]    ptErrorCode    : NRC                            */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Request was successful             */
/*               |   E_NOT_OK          : Request was not successful         */
/*               |   DCM_E_PENDING     : Request is not yet finished        */
/*               |   DCM_E_FORCE_RCRRP : RCRRP response                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID31_StartCout
(
    const uint16 u2RoutineIndex,                                                    /* MISRA DEVIATION */
    P2VAR( Dcm_Dsp_SID31_SigDataType, AUTOMATIC, DCM_APPL_DATA ) ptSigData,         /* MISRA DEVIATION */
    const Dcm_OpStatusType u1OpStatus,                                              /* MISRA DEVIATION */
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode     /* MISRA DEVIATION */
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_OK;
    
    
    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID31_StopCout                                   */
/* Description   | Routine stop processing                                  */
/* Preconditions | None                                                     */
/* Parameters    | [IN]     u2RoutineIndex : Routine index                  */
/*               | [IN/OUT] ptSigData      : Request/Response data          */
/*               | [IN]     u1OpStatus     : Operation state                */
/*               | [OUT]    ptErrorCode    : NRC                            */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Request was successful             */
/*               |   E_NOT_OK          : Request was not successful         */
/*               |   DCM_E_PENDING     : Request is not yet finished        */
/*               |   DCM_E_FORCE_RCRRP : RCRRP response                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID31_StopCout
(
    const uint16 u2RoutineIndex,                                                    /* MISRA DEVIATION */
    P2VAR( Dcm_Dsp_SID31_SigDataType, AUTOMATIC, DCM_APPL_DATA ) ptSigData,         /* MISRA DEVIATION */
    const Dcm_OpStatusType u1OpStatus,                                              /* MISRA DEVIATION */
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode     /* MISRA DEVIATION */
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_OK;
    
    
    return u1_RetVal;
}

/**********************************************************************************************************/
/* Function Name | Dcm_Dsp_SID31_CheckSupportedRid                                                        */
/* Description   | Requests if a specific RID is available.                                               */
/* Preconditions | None                                                                                   */
/* Parameters    | [IN] u2RoutineId : RID value                                                           */
/*               | [IN] u2PduId     : Received PduID                                                      */
/* Return Value  | Std_ReturnType                                                                         */
/*               |   E_OK              : RID Supported                                                    */
/*               |   E_NOT_OK          : RID Not Supported                                                */
/* Notes         | None                                                                                   */
/**********************************************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID31_CheckSupportedRid
(
    uint16 u2RoutineId,
    uint16 u2PduId 
)
{
    Std_ReturnType u1_RetVal;
    
    u1_RetVal = Dcm_CheckSupportedRid( u2RoutineId, u2PduId );
    
    return u1_RetVal;
}

/**********************************************************************************************************/
/* Function Name | Dcm_Dsp_SID31_CheckSupportedSubFuncForRid                                              */
/* Description   | Requests if a specific RID Subfunction is available.                                   */
/* Preconditions | None                                                                                   */
/* Parameters    | [IN] u2RoutineId   : RID value                                                         */
/*               | [IN] u1SubFunction : RID Subfunction value                                             */
/*               | [IN] u2PduId       : Received PduID                                                    */
/* Return Value  | Std_ReturnType                                                                         */
/*               |   E_OK              : RID Subfunction Supported                                        */
/*               |   E_NOT_OK          : RID Subfunction Not Supported                                    */
/* Notes         | None                                                                                   */
/**********************************************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID31_CheckSupportedSubFuncForRid
(
    uint16 u2RoutineId,
    uint8  u1SubFunction,
    uint16 u2PduId 
)
{
    Std_ReturnType u1_RetVal;
    
    u1_RetVal = Dcm_CheckSupportedSubFuncForRid( u2RoutineId, u1SubFunction, u2PduId );
    
    return u1_RetVal;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
#endif /* DCM_SUPPORT_SID31 == STD_ON */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-08-20                                              */
/*  v3-0-0         :2019-05-29                                              */
/*  v3-2-0         :2020-08-27                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-5-1         :2024-02-27                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-5-1                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
