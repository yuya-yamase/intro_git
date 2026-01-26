/* Dcm_Dsp_SID29_c(v5-3-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID29/CODE                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>

#if ( DCM_AUTHENTICATION_USE == STD_ON )

#include <Dcm/Dcm_Dsp_SID29.h>
#include <Dcm/Dcm_Dsp_SID29_Callout.h>
#include <Dcm/Dcm_Dsp_Main.h>
#include "../../Dsp/inc/Dcm_Dsp_MsgMaker.h"
#include <Dcm/Dcm_Main_EvtDistr.h>
#include <Dcm/Dcm_Dsl_Ctrl.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* AuthenticationTask */
#define DCM_DSP_SID29_AUTHTASK_DEAUTH           ((uint8)0x00U)
#define DCM_DSP_SID29_AUTHTASK_VRFYCERTUNIIDR   ((uint8)0x01U)
#define DCM_DSP_SID29_AUTHTASK_VRFYCERTBIIDR    ((uint8)0x02U)
#define DCM_DSP_SID29_AUTHTASK_VRFYPOWN         ((uint8)0x03U)
#define DCM_DSP_SID29_AUTHTASK_AUTHCONFIG       ((uint8)0x08U)
#define DCM_DSP_SID29_AUTHTASK_INVALID          ((uint8)0xFFU)

/* Connection ID */
#define DCM_DSP_SID29_CNCTID_INVALID            ((uint16)0xFFFFU)

/* Request Information */
#define DCM_DSP_SID29_REQ_SUB00_LEN             ((Dcm_MsgLenType)0x00000000U)

#define DCM_DSP_SID29_REQ_SUB01_MINLEN          ((Dcm_MsgLenType)0x00000006U)   /* communicationConfiguration(1byte) + */
                                                                                /* lengthOfCertificateClient(2byte) +  */
                                                                                /* certificateClient(1byte) +          */
                                                                                /* lengthOfChallengeClient(2byte)      */

#define DCM_DSP_SID29_REQ_SUB02_MINLEN          ((Dcm_MsgLenType)0x00000007U)   /* communicationConfiguration(1byte) + */
                                                                                /* lengthOfCertificateClient(2byte) +  */
                                                                                /* certificateClient(1byte) +          */
                                                                                /* lengthOfChallengeClient(2byte) +    */
                                                                                /* challengeClient(1byte)              */

#define DCM_DSP_SID29_REQ_SUB03_MINLEN          ((Dcm_MsgLenType)0x00000005U)   /* lengthOfProofOfOwnershipClient(2byte) + */
                                                                                /* proofOfOwnershipClient(1byte) +         */
                                                                                /* lengthOfEphemeralPublicKeyClient(2byte) */

#define DCM_DSP_SID29_REQ_SUB08_LEN             ((Dcm_MsgLenType)0x00000000U)

#define DCM_DSP_SID29_REQ_COCO_POS              ((uint8)0x00U)
#define DCM_DSP_SID29_REQ_COCO_LEN              ((uint8)0x01U)
#define DCM_DSP_SID29_REQ_COCO_VALID_VAL        ((uint8)0x00U)

#define DCM_DSP_SID29_REQ_LOCECL_MSB_POS        ((uint8)0x01U)
#define DCM_DSP_SID29_REQ_LOCECL_LSB_POS        ((uint8)0x02U)
#define DCM_DSP_SID29_REQ_LOCECL_LEN            ((uint8)0x02U)
#define DCM_DSP_SID29_REQ_LOCECL_SHIFT          ((uint8)0x08U)
#define DCM_DSP_SID29_REQ_LOCECL_INVALID_VAL    ((uint16)0x0000U)

#define DCM_DSP_SID29_REQ_CECL_POS              ((uint8)( DCM_DSP_SID29_REQ_COCO_LEN + DCM_DSP_SID29_REQ_LOCECL_LEN ))

#define DCM_DSP_SID29_REQ_LOCHCL_LEN            ((uint8)0x02U)
#define DCM_DSP_SID29_REQ_LOCHCL_SHIFT          ((uint8)0x08U)
#define DCM_DSP_SID29_REQ_LOCHCL_INVALID_VAL    ((uint16)0x0000U)

#define DCM_DSP_SID29_REQ_LPOWNCL_MSB_POS       ((uint8)0x00U)
#define DCM_DSP_SID29_REQ_LPOWNCL_LSB_POS       ((uint8)0x01U)
#define DCM_DSP_SID29_REQ_LPOWNCL_LEN           ((uint8)0x02U)
#define DCM_DSP_SID29_REQ_LPOWNCL_SHIFT         ((uint8)0x08U)
#define DCM_DSP_SID29_REQ_LPOWNCL_INVALID_VAL   ((uint16)0x0000U)

#define DCM_DSP_SID29_REQ_POWNCL_POS            (DCM_DSP_SID29_REQ_LPOWNCL_LEN)

#define DCM_DSP_SID29_REQ_LOEPKCL_LEN           ((uint8)0x02U)
#define DCM_DSP_SID29_REQ_LOEPKCL_SHIFT         ((uint8)0x08U)
#define DCM_DSP_SID29_REQ_LOEPKCL_VALID_VAL     ((uint16)0x0000U)

/* Response Information */
#define DCM_DSP_SID29_RES_RETVAL_POS            ((uint8)0x00U)
#define DCM_DSP_SID29_RES_RETVAL_LEN            ((uint8)0x01U)

#define DCM_DSP_SID29_RES_LOCHSE_MSB_POS        ((uint8)0x01U)
#define DCM_DSP_SID29_RES_LOCHSE_LSB_POS        ((uint8)0x02U)
#define DCM_DSP_SID29_RES_LOCHSE_LEN            ((uint8)0x02U)
#define DCM_DSP_SID29_RES_LOCHSE_SHIFT          ((uint8)0x08U)

#define DCM_DSP_SID29_RES_LOCESE_LEN            ((uint8)0x02U)
#define DCM_DSP_SID29_RES_LOCESE_SHIFT          ((uint8)0x08U)

#define DCM_DSP_SID29_RES_LPOWNSE_LEN           ((uint8)0x02U)
#define DCM_DSP_SID29_RES_LPOWNSE_SHIFT         ((uint8)0x08U)

#define DCM_DSP_SID29_RES_LOEPKSE_LEN           ((uint8)0x02U)

#define DCM_DSP_SID29_RES_LOSKI_MSB_POS         ((uint8)0x01U)
#define DCM_DSP_SID29_RES_LOSKI_LSB_POS         ((uint8)0x02U)
#define DCM_DSP_SID29_RES_LOSKI_LEN             ((uint8)0x02U)

/* AuthenticationReturnParameter  */
#define DCM_DSP_SID29_AUTHRETPARA_ACAPCE        ((uint8)0x02U)
#define DCM_DSP_SID29_AUTHRETPARA_DAS           ((uint8)0x10U)
#define DCM_DSP_SID29_AUTHRETPARA_CVOVN         ((uint8)0x11U)
#define DCM_DSP_SID29_AUTHRETPARA_OVAC          ((uint8)0x12U)

/* LengthOfEphemeralPublicKeyServer */
#define DCM_DSP_SID29_LOEPKSE_MSB               ((uint8)0x00U)
#define DCM_DSP_SID29_LOEPKSE_LSB               ((uint8)0x00U)

/* LengthOfSessionKeyInfo */
#define DCM_DSP_SID29_LOSKI_MSB                 ((uint8)0x00U)
#define DCM_DSP_SID29_LOSKI_LSB                 ((uint8)0x00U)


/* NRC of verification fails */
#define DCM_DSP_SID29_NRC_VERI_FAIL_RANGE_MIN   ((uint8)0x50U)
#define DCM_DSP_SID29_NRC_VERI_FAIL_RANGE_MAX   ((uint8)0x5DU)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

#if ( DCM_SUPPORT_SID29_SUB00 == STD_ON )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID29_Sub00_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
);
#endif /* DCM_SUPPORT_SID29_SUB00 == STD_ON */

#if ( DCM_SUPPORT_SID29_SUB01 == STD_ON )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID29_Sub01_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
);
#endif /* DCM_SUPPORT_SID29_SUB01 == STD_ON */

#if ( DCM_SUPPORT_SID29_SUB02 == STD_ON )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID29_Sub02_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
);
#endif /* DCM_SUPPORT_SID29_SUB02 == STD_ON */

#if ( DCM_SUPPORT_SID29_SUB03 == STD_ON )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID29_Sub03_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
);
#endif /* DCM_SUPPORT_SID29_SUB03 == STD_ON */

#if ( DCM_SUPPORT_SID29_SUB08 == STD_ON )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID29_Sub08_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
);
#endif /* DCM_SUPPORT_SID29_SUB08 == STD_ON */

static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID29_VrfyCertUnidirProc
(
    const Dcm_OpStatusType u1OpStatus
);

static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID29_VrfyCertBidirProc
(
    const Dcm_OpStatusType u1OpStatus
);

static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID29_VrfyPownProc
(
    const Dcm_OpStatusType u1OpStatus
);

#if ( DCM_SUPPORT_SID29_SUB01 == STD_ON )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID29_Sub01_CancelProc
( void );
#endif /* DCM_SUPPORT_SID29_SUB01 == STD_ON */

#if ( DCM_SUPPORT_SID29_SUB02 == STD_ON )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID29_Sub02_CancelProc
( void );
#endif /* DCM_SUPPORT_SID29_SUB02 == STD_ON */

#if ( DCM_SUPPORT_SID29_SUB03 == STD_ON )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID29_Sub03_CancelProc
( void );
#endif /* DCM_SUPPORT_SID29_SUB03 == STD_ON */

#if ( ( DCM_SUPPORT_SID29_SUB00 == STD_ON ) || ( DCM_SUPPORT_SID29_SUB08 == STD_ON ) )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID29_CancelProcOnlySetIdleFlag
( void );
#endif /* DCM_SUPPORT_SID29_SUB00 == STD_ON || DCM_SUPPORT_SID29_SUB08 == STD_ON */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

static VAR( Dcm_VrfyCertIndataType, DCM_VAR_NO_INIT ) Dcm_Dsp_SID29_stVrfyCertIndata;
static VAR( Dcm_VrfyPownIndataType, DCM_VAR_NO_INIT ) Dcm_Dsp_SID29_stVrfyPownIndata;
static VAR( uint16, DCM_VAR_NO_INIT ) Dcm_Dsp_SID29_u2ConnectionId;
static VAR( uint8, DCM_VAR_NO_INIT ) Dcm_Dsp_SID29_u1AuthTask;
static VAR( boolean, DCM_VAR_NO_INIT ) Dcm_Dsp_SID29_bVrfyCertExctdFlg[DCM_DSL_CLIENT_NUM];

#define DCM_STOP_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CONST
#include <Dcm_MemMap.h>


#define DCM_STOP_SEC_CONST
#include <Dcm_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID29_Init                                       */
/* Description   | SID29 initialization                                     */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID29_Init   /* MISRA DEVIATION */
( void )
{
    uint16 u2_ClientCnt;
    uint16 u2_ClientNumMax;

    Dcm_Dsp_SID29_stVrfyCertIndata.u2LengthOfCertificateClient = (uint16)0x0000U;
    Dcm_Dsp_SID29_stVrfyCertIndata.ptCertificateClient         = NULL_PTR;
    Dcm_Dsp_SID29_stVrfyCertIndata.u2LengthOfChallengeClient   = (uint16)0x0000U;
    Dcm_Dsp_SID29_stVrfyCertIndata.ptChallengeClient           = NULL_PTR;

    Dcm_Dsp_SID29_stVrfyPownIndata.u2LengthOfPownClient = (uint16)0x0000U;
    Dcm_Dsp_SID29_stVrfyPownIndata.ptPownClient         = NULL_PTR;

    Dcm_Dsp_SID29_u2ConnectionId = DCM_DSP_SID29_CNCTID_INVALID;
    Dcm_Dsp_SID29_u1AuthTask     = DCM_DSP_SID29_AUTHTASK_INVALID;

    u2_ClientNumMax = Dcm_Dsl_u2ClientNum;
    for( u2_ClientCnt = (uint16)0U; u2_ClientCnt < u2_ClientNumMax; u2_ClientCnt++ )
    {
        Dcm_Dsp_SID29_bVrfyCertExctdFlg[u2_ClientCnt] = (boolean)FALSE;
    }

    return ;
}

#if ( DCM_SUPPORT_SID29_SUB00 == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_SID29_Sub00                                          */
/* Description   | Request processing of SID29 Subfunction00                */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus    : Operation state                       */
/*               | [IN] pMsgContext : Message Context                       */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK           : Processing normal                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID29_Sub00    /* MISRA DEVIATION */
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_OK;

    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
        u1_RetVal = Dcm_Dsp_SID29_Sub00_InitialProc( pMsgContext );
    }
    else if( OpStatus == (Dcm_OpStatusType)DCM_CANCEL )
    {
        u1_RetVal = Dcm_Dsp_SID29_CancelProcOnlySetIdleFlag();
    }
    else
    {
        /* No process */
    }

    return u1_RetVal;
}
#endif /* DCM_SUPPORT_SID29_SUB00 == STD_ON */

#if ( DCM_SUPPORT_SID29_SUB01 == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_SID29_Sub01                                          */
/* Description   | Request processing of SID29 Subfunction01                */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus    : Operation state                       */
/*               | [IN] pMsgContext : Message Context                       */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK           : Processing normal                     */
/*               |   DCM_E_PENDING  : Pending                               */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID29_Sub01    /* MISRA DEVIATION */
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_OK;

    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
        u1_RetVal = Dcm_Dsp_SID29_Sub01_InitialProc( pMsgContext );
    }
    else if( OpStatus == (Dcm_OpStatusType)DCM_CANCEL )
    {
        u1_RetVal = Dcm_Dsp_SID29_Sub01_CancelProc();
    }
    else
    {
        /* No process */
    }

    return u1_RetVal;
}
#endif /* DCM_SUPPORT_SID29_SUB01 == STD_ON */

#if ( DCM_SUPPORT_SID29_SUB02 == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_SID29_Sub02                                          */
/* Description   | Request processing of SID29 Subfunction02                */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus    : Operation state                       */
/*               | [IN] pMsgContext : Message Context                       */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK           : Processing normal                     */
/*               |   DCM_E_PENDING  : Pending                               */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID29_Sub02    /* MISRA DEVIATION */
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_OK;

    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
        u1_RetVal = Dcm_Dsp_SID29_Sub02_InitialProc( pMsgContext );
    }
    else if( OpStatus == (Dcm_OpStatusType)DCM_CANCEL )
    {
        u1_RetVal = Dcm_Dsp_SID29_Sub02_CancelProc();
    }
    else
    {
        /* No process */
    }

    return u1_RetVal;
}
#endif /* DCM_SUPPORT_SID29_SUB02 == STD_ON */

#if ( DCM_SUPPORT_SID29_SUB03 == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_SID29_Sub03                                          */
/* Description   | Request processing of SID29 Subfunction03                */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus    : Operation state                       */
/*               | [IN] pMsgContext : Message Context                       */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK           : Processing normal                     */
/*               |   DCM_E_PENDING  : Pending                               */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID29_Sub03    /* MISRA DEVIATION */
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_OK;

    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
        u1_RetVal = Dcm_Dsp_SID29_Sub03_InitialProc( pMsgContext );
    }
    else if( OpStatus == (Dcm_OpStatusType)DCM_CANCEL )
    {
        u1_RetVal = Dcm_Dsp_SID29_Sub03_CancelProc();
    }
    else
    {
        /* No process */
    }

    return u1_RetVal;
}
#endif /* DCM_SUPPORT_SID29_SUB03 == STD_ON */

#if ( DCM_SUPPORT_SID29_SUB08 == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_SID29_Sub08                                          */
/* Description   | Request processing of SID29 Subfunction08                */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus    : Operation state                       */
/*               | [IN] pMsgContext : Message Context                       */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK           : Processing normal                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID29_Sub08    /* MISRA DEVIATION */
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_OK;

    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
        u1_RetVal = Dcm_Dsp_SID29_Sub08_InitialProc( pMsgContext );
    }
    else if( OpStatus == (Dcm_OpStatusType)DCM_CANCEL )
    {
        u1_RetVal = Dcm_Dsp_SID29_CancelProcOnlySetIdleFlag();
    }
    else
    {
        /* No process */
    }

    return u1_RetVal;
}
#endif /* DCM_SUPPORT_SID29_SUB08 == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID29_VrfyCertUnidirCbk                          */
/* Description   | Callback function for event delivery registration of     */
/*               | Dcm_VerifyCertificateUnidir                              */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId : Event ID                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID29_VrfyCertUnidirCbk
(
    const uint8 u1EventId   /* MISRA DEVIATION */
)
{
    (void)Dcm_Dsp_SID29_VrfyCertUnidirProc( DCM_PENDING );    /* no return check required */

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID29_VrfyCertBidirCbk                           */
/* Description   | Callback function for event delivery registration of     */
/*               | Dcm_VerifyCertificateBidir                               */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId : Event ID                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID29_VrfyCertBidirCbk
(
    const uint8 u1EventId   /* MISRA DEVIATION */
)
{
    (void)Dcm_Dsp_SID29_VrfyCertBidirProc( DCM_PENDING );     /* no return check required */

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID29_VrfyPownCbk                                */
/* Description   | Callback function for event delivery registration of     */
/*               | Dcm_VerifyPown                                           */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId : Event ID                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID29_VrfyPownCbk
(
    const uint8 u1EventId   /* MISRA DEVIATION */
)
{
    (void)Dcm_Dsp_SID29_VrfyPownProc( DCM_PENDING );          /* no return check required */

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID29_NotifyAuthStateUpdate                      */
/* Description   | Notification of authentication state update              */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1AuthState    : Authentication state               */
/*               | [IN] u2ConnectionId : Connection ID                      */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID29_NotifyAuthStateUpdate
(
    const uint8 u1AuthState,
    const uint16 u2ConnectionId
)
{
    if( u1AuthState == (uint8)DCM_DEAUTHENTICATED )
    {
        Dcm_Dsp_SID29_bVrfyCertExctdFlg[u2ConnectionId] = (boolean)FALSE;
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID29_Confirmation                               */
/* Description   | Complete transmission of SID29 response message          */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1IdContext    : ID Context                         */
/*               | [IN] u2ConnectionId : Connection ID                      */
/*               | [IN] u1Status       : Status                             */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID29_Confirmation   /* MISRA DEVIATION */
(
    const Dcm_IdContextType u1IdContext,            /* MISRA DEVIATION */
    const uint16 u2ConnectionId,
    const Dcm_ConfirmationStatusType u1Status
)
{
    if( ( Dcm_Dsp_SID29_u1AuthTask == DCM_DSP_SID29_AUTHTASK_VRFYCERTUNIIDR ) ||
        ( Dcm_Dsp_SID29_u1AuthTask == DCM_DSP_SID29_AUTHTASK_VRFYCERTBIIDR ) )
    {
        if( u1Status == (Dcm_ConfirmationStatusType)DCM_RES_POS_OK )
        {
            Dcm_Dsp_SID29_bVrfyCertExctdFlg[u2ConnectionId] = (boolean)TRUE;
        }
    }

    return;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#if ( DCM_SUPPORT_SID29_SUB00 == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID29_Sub00_InitialProc                          */
/* Description   | Initial process of SID29 Subfunction00                   */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext : Message Context                      */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK            : Processing normal                    */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID29_Sub00_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
)
{
    uint16          u2_ConnectionId;
    Std_ReturnType  u1_RetVal;

    u1_RetVal = E_OK;

    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );
    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

    Dcm_Dsp_Main_stMsgContext = *ptMsgContext;
    Dcm_Dsp_SID29_u1AuthTask = DCM_DSP_SID29_AUTHTASK_DEAUTH;

    if( Dcm_Dsp_Main_stMsgContext.reqDataLen == DCM_DSP_SID29_REQ_SUB00_LEN )
    {
        u2_ConnectionId = DCM_DSP_SID29_CNCTID_INVALID;
        (void)Dcm_GetActiveProtocol( NULL_PTR,              /* no return check required */
                                     &u2_ConnectionId,
                                     NULL_PTR );

        Dcm_Dsl_SetAuthState( DCM_DEAUTHENTICATED,
                              u2_ConnectionId );

        Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID29_RES_RETVAL_POS] = DCM_DSP_SID29_AUTHRETPARA_DAS;
        Dcm_Dsp_Main_stMsgContext.resDataLen = (uint32)DCM_DSP_SID29_RES_RETVAL_LEN;

        Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
    }
    else
    {
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext,
                                     DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT );
    }

    return u1_RetVal;
}
#endif /* DCM_SUPPORT_SID29_SUB00 == STD_ON */

#if ( DCM_SUPPORT_SID29_SUB01 == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID29_Sub01_InitialProc                          */
/* Description   | Initial process of SID29 Subfunction01                   */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext : Message Context                      */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK            : Processing normal                    */
/*               |   DCM_E_PENDING   : Pending                              */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID29_Sub01_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
)
{
    uint32                          u4_ChallengeClientPos;
    uint32                          u4_LengthOfChallengeClientPos;
    uint16                          u2_ConnectionId;
    uint16                          u2_LengthOfCertificateClient;
    uint16                          u2_LengthOfChallengeClient;
    Std_ReturnType                  u1_RetVal;
    Dcm_NegativeResponseCodeType    u1_ErrorCode;
    boolean                         b_SendNegResFlag;

    u1_RetVal = E_OK;
    b_SendNegResFlag = (boolean)FALSE;

    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );
    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

    Dcm_Dsp_Main_stMsgContext = *ptMsgContext;
    Dcm_Dsp_SID29_u1AuthTask = DCM_DSP_SID29_AUTHTASK_VRFYCERTUNIIDR;

    u2_ConnectionId = DCM_DSP_SID29_CNCTID_INVALID;
    (void)Dcm_GetActiveProtocol( NULL_PTR,                      /* no return check required */
                                 &u2_ConnectionId,
                                 NULL_PTR );
    Dcm_Dsp_SID29_bVrfyCertExctdFlg[u2_ConnectionId] = (boolean)FALSE;

    if( Dcm_Dsp_Main_stMsgContext.reqDataLen >= DCM_DSP_SID29_REQ_SUB01_MINLEN )
    {
        if( Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID29_REQ_COCO_POS] == DCM_DSP_SID29_REQ_COCO_VALID_VAL )
        {
            u2_LengthOfCertificateClient = (uint16)( (uint16)Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID29_REQ_LOCECL_MSB_POS] << DCM_DSP_SID29_REQ_LOCECL_SHIFT ) |
                                                   (uint16)Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID29_REQ_LOCECL_LSB_POS];

            if( u2_LengthOfCertificateClient != DCM_DSP_SID29_REQ_LOCECL_INVALID_VAL )
            {
                u4_LengthOfChallengeClientPos = (uint32)( DCM_DSP_SID29_REQ_COCO_LEN +
                                                          DCM_DSP_SID29_REQ_LOCECL_LEN +    /* no wrap around */
                                                          (uint32)u2_LengthOfCertificateClient );
                u2_LengthOfChallengeClient = (uint16)( (uint16)Dcm_Dsp_Main_stMsgContext.reqData[u4_LengthOfChallengeClientPos] << DCM_DSP_SID29_REQ_LOCHCL_SHIFT );
                u4_LengthOfChallengeClientPos++;    /* no wrap around */
                u2_LengthOfChallengeClient |= (uint16)Dcm_Dsp_Main_stMsgContext.reqData[u4_LengthOfChallengeClientPos];

                if( Dcm_Dsp_Main_stMsgContext.reqDataLen == (uint32)( DCM_DSP_SID29_REQ_COCO_LEN +
                                                                      DCM_DSP_SID29_REQ_LOCECL_LEN +            /* no wrap around */
                                                                      (uint32)u2_LengthOfCertificateClient +    /* no wrap around */
                                                                      DCM_DSP_SID29_REQ_LOCHCL_LEN +            /* no wrap around */
                                                                      (uint32)u2_LengthOfChallengeClient ) )
                {
                    Dcm_Dsp_SID29_u2ConnectionId = u2_ConnectionId;

                    Dcm_Dsp_SID29_stVrfyCertIndata.u2LengthOfCertificateClient = u2_LengthOfCertificateClient;
                    Dcm_Dsp_SID29_stVrfyCertIndata.ptCertificateClient = &Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID29_REQ_CECL_POS];
                    Dcm_Dsp_SID29_stVrfyCertIndata.u2LengthOfChallengeClient = u2_LengthOfChallengeClient;
                    u4_ChallengeClientPos = (uint32)( DCM_DSP_SID29_REQ_COCO_LEN +
                                                      DCM_DSP_SID29_REQ_LOCECL_LEN +            /* no wrap around */
                                                      (uint32)u2_LengthOfCertificateClient +    /* no wrap around */
                                                      DCM_DSP_SID29_REQ_LOCHCL_LEN );
                    Dcm_Dsp_SID29_stVrfyCertIndata.ptChallengeClient = &Dcm_Dsp_Main_stMsgContext.reqData[u4_ChallengeClientPos];

                    u1_RetVal = Dcm_Dsp_SID29_VrfyCertUnidirProc( DCM_INITIAL );
                }
                else
                {
                    u1_ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
                    b_SendNegResFlag = (boolean)TRUE;
                }
            }
            else
            {
                u1_ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
                b_SendNegResFlag = (boolean)TRUE;
            }
        }
        else
        {
            u1_ErrorCode = DCM_E_REQUESTOUTOFRANGE;
            b_SendNegResFlag = (boolean)TRUE;
        }
    }
    else
    {
        u1_ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        b_SendNegResFlag = (boolean)TRUE;
    }

    if( b_SendNegResFlag == (boolean)TRUE )
    {
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext,
                                     u1_ErrorCode );
    }

    return u1_RetVal;
}
#endif /* DCM_SUPPORT_SID29_SUB01 == STD_ON */

#if ( DCM_SUPPORT_SID29_SUB02 == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID29_Sub02_InitialProc                          */
/* Description   | Initial process of SID29 Subfunction02                   */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext : Message Context                      */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK            : Processing normal                    */
/*               |   DCM_E_PENDING   : Pending                              */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID29_Sub02_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
)
{
    uint32                          u4_LengthOfChallengeClientPos;
    uint32                          u4_ChallengeClientPos;
    uint16                          u2_ConnectionId;
    uint16                          u2_LengthOfCertificateClient;
    uint16                          u2_LengthOfChallengeClient;
    Std_ReturnType                  u1_RetVal;
    Dcm_NegativeResponseCodeType    u1_ErrorCode;
    boolean                         b_SendNegResFlag;

    u1_RetVal = E_OK;
    b_SendNegResFlag = (boolean)FALSE;

    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );
    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

    Dcm_Dsp_Main_stMsgContext = *ptMsgContext;
    Dcm_Dsp_SID29_u1AuthTask = DCM_DSP_SID29_AUTHTASK_VRFYCERTBIIDR;

    u2_ConnectionId = DCM_DSP_SID29_CNCTID_INVALID;
    (void)Dcm_GetActiveProtocol( NULL_PTR,                      /* no return check required */
                                 &u2_ConnectionId,
                                 NULL_PTR );
    Dcm_Dsp_SID29_bVrfyCertExctdFlg[u2_ConnectionId] = (boolean)FALSE;

    if( Dcm_Dsp_Main_stMsgContext.reqDataLen >= DCM_DSP_SID29_REQ_SUB02_MINLEN )
    {
        if( Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID29_REQ_COCO_POS] == DCM_DSP_SID29_REQ_COCO_VALID_VAL )
        {
            u2_LengthOfCertificateClient = (uint16)( (uint16)Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID29_REQ_LOCECL_MSB_POS] << DCM_DSP_SID29_REQ_LOCECL_SHIFT ) |
                                                   (uint16)Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID29_REQ_LOCECL_LSB_POS];

            if( u2_LengthOfCertificateClient != DCM_DSP_SID29_REQ_LOCECL_INVALID_VAL )
            {
                u4_LengthOfChallengeClientPos = (uint32)( DCM_DSP_SID29_REQ_COCO_LEN +
                                                          DCM_DSP_SID29_REQ_LOCECL_LEN +    /* no wrap around */
                                                          (uint32)u2_LengthOfCertificateClient );
                u2_LengthOfChallengeClient = (uint16)( (uint16)Dcm_Dsp_Main_stMsgContext.reqData[u4_LengthOfChallengeClientPos] << DCM_DSP_SID29_REQ_LOCHCL_SHIFT );
                u4_LengthOfChallengeClientPos++;    /* no wrap around */
                u2_LengthOfChallengeClient |= (uint16)Dcm_Dsp_Main_stMsgContext.reqData[u4_LengthOfChallengeClientPos];

                if( u2_LengthOfChallengeClient != DCM_DSP_SID29_REQ_LOCHCL_INVALID_VAL )
                {
                    if( Dcm_Dsp_Main_stMsgContext.reqDataLen == (uint32)( DCM_DSP_SID29_REQ_COCO_LEN +
                                                                          DCM_DSP_SID29_REQ_LOCECL_LEN +            /* no wrap around */
                                                                          (uint32)u2_LengthOfCertificateClient +    /* no wrap around */
                                                                          DCM_DSP_SID29_REQ_LOCHCL_LEN +            /* no wrap around */
                                                                          (uint32)u2_LengthOfChallengeClient ) )
                    {
                        Dcm_Dsp_SID29_u2ConnectionId = u2_ConnectionId;

                        Dcm_Dsp_SID29_stVrfyCertIndata.u2LengthOfCertificateClient = u2_LengthOfCertificateClient;
                        Dcm_Dsp_SID29_stVrfyCertIndata.ptCertificateClient = &Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID29_REQ_CECL_POS];
                        Dcm_Dsp_SID29_stVrfyCertIndata.u2LengthOfChallengeClient = u2_LengthOfChallengeClient;
                        u4_ChallengeClientPos = (uint32)( DCM_DSP_SID29_REQ_COCO_LEN +
                                                          DCM_DSP_SID29_REQ_LOCECL_LEN +            /* no wrap around */
                                                          (uint32)u2_LengthOfCertificateClient +    /* no wrap around */
                                                          DCM_DSP_SID29_REQ_LOCHCL_LEN );
                        Dcm_Dsp_SID29_stVrfyCertIndata.ptChallengeClient = &Dcm_Dsp_Main_stMsgContext.reqData[u4_ChallengeClientPos];

                        u1_RetVal = Dcm_Dsp_SID29_VrfyCertBidirProc( DCM_INITIAL );
                    }
                    else
                    {
                        u1_ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
                        b_SendNegResFlag = (boolean)TRUE;
                    }
                }
                else
                {
                    u1_ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
                    b_SendNegResFlag = (boolean)TRUE;
                }
            }
            else
            {
                u1_ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
                b_SendNegResFlag = (boolean)TRUE;
            }
        }
        else
        {
            u1_ErrorCode = DCM_E_REQUESTOUTOFRANGE;
            b_SendNegResFlag = (boolean)TRUE;
        }
    }
    else
    {
        u1_ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        b_SendNegResFlag = (boolean)TRUE;
    }

    if( b_SendNegResFlag == (boolean)TRUE )
    {
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext,
                                     u1_ErrorCode );
    }

    return u1_RetVal;
}
#endif /* DCM_SUPPORT_SID29_SUB02 == STD_ON */

#if ( DCM_SUPPORT_SID29_SUB03 == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID29_Sub03_InitialProc                          */
/* Description   | Initial process of SID29 Subfunction03                   */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext : Message Context                      */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK            : Processing normal                    */
/*               |   DCM_E_PENDING   : Pending                              */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID29_Sub03_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
)
{
    uint32                          u4_LengthOfEphemeralPublicKeyClientPos;
    uint16                          u2_LengthOfProofOfOwnershipClient;
    uint16                          u2_LengthOfEphemeralPublicKeyClient;
    uint16                          u2_ConnectionId;
    Std_ReturnType                  u1_RetVal;
    Dcm_NegativeResponseCodeType    u1_ErrorCode;
    boolean                         b_SendNegResFlag;

    u1_RetVal = E_OK;
    b_SendNegResFlag = (boolean)FALSE;

    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );
    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

    Dcm_Dsp_Main_stMsgContext = *ptMsgContext;
    Dcm_Dsp_SID29_u1AuthTask = DCM_DSP_SID29_AUTHTASK_VRFYPOWN;

    if( Dcm_Dsp_Main_stMsgContext.reqDataLen >= DCM_DSP_SID29_REQ_SUB03_MINLEN )
    {
        u2_LengthOfProofOfOwnershipClient = (uint16)( (uint16)Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID29_REQ_LPOWNCL_MSB_POS] << DCM_DSP_SID29_REQ_LPOWNCL_SHIFT ) |
                                                    (uint16)Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID29_REQ_LPOWNCL_LSB_POS];

        if( u2_LengthOfProofOfOwnershipClient != DCM_DSP_SID29_REQ_LPOWNCL_INVALID_VAL )
        {
            u4_LengthOfEphemeralPublicKeyClientPos = (uint32)( DCM_DSP_SID29_REQ_LPOWNCL_LEN +  /* no wrap around */
                                                               (uint32)u2_LengthOfProofOfOwnershipClient );
            u2_LengthOfEphemeralPublicKeyClient = (uint16)( (uint16)Dcm_Dsp_Main_stMsgContext.reqData[u4_LengthOfEphemeralPublicKeyClientPos] << DCM_DSP_SID29_REQ_LOEPKCL_SHIFT );
            u4_LengthOfEphemeralPublicKeyClientPos++;   /* no wrap around */
            u2_LengthOfEphemeralPublicKeyClient |= (uint16)Dcm_Dsp_Main_stMsgContext.reqData[u4_LengthOfEphemeralPublicKeyClientPos];

            if( u2_LengthOfEphemeralPublicKeyClient == DCM_DSP_SID29_REQ_LOEPKCL_VALID_VAL )
            {
                if( Dcm_Dsp_Main_stMsgContext.reqDataLen == (uint32)( DCM_DSP_SID29_REQ_LPOWNCL_LEN +               /* no wrap around */
                                                                      (uint32)u2_LengthOfProofOfOwnershipClient +   /* no wrap around */
                                                                      DCM_DSP_SID29_REQ_LOEPKCL_LEN ) )
                {
                    u2_ConnectionId = DCM_DSP_SID29_CNCTID_INVALID;
                    (void)Dcm_GetActiveProtocol( NULL_PTR,                          /* no return check required */
                                                 &u2_ConnectionId, NULL_PTR );

                    if( Dcm_Dsp_SID29_bVrfyCertExctdFlg[u2_ConnectionId] == (boolean)TRUE )
                    {
                        Dcm_Dsp_SID29_u2ConnectionId = u2_ConnectionId;

                        Dcm_Dsp_SID29_stVrfyPownIndata.u2LengthOfPownClient = u2_LengthOfProofOfOwnershipClient;
                        Dcm_Dsp_SID29_stVrfyPownIndata.ptPownClient = &Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID29_REQ_POWNCL_POS];

                        u1_RetVal = Dcm_Dsp_SID29_VrfyPownProc( DCM_INITIAL );
                    }
                    else
                    {
                        u1_ErrorCode = DCM_E_REQUESTSEQUENCEERROR;
                        b_SendNegResFlag = (boolean)TRUE;
                    }
                }
                else
                {
                    u1_ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
                    b_SendNegResFlag = (boolean)TRUE;
                }
            }
            else
            {
                u1_ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
                b_SendNegResFlag = (boolean)TRUE;
            }
        }
        else
        {
            u1_ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
            b_SendNegResFlag = (boolean)TRUE;
        }
    }
    else
    {
        u1_ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        b_SendNegResFlag = (boolean)TRUE;
    }

    if( b_SendNegResFlag == (boolean)TRUE )
    {
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext,
                                     u1_ErrorCode );
    }

    return u1_RetVal;
}
#endif /* DCM_SUPPORT_SID29_SUB03 == STD_ON */

#if ( DCM_SUPPORT_SID29_SUB08 == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID29_Sub08_InitialProc                          */
/* Description   | Initial process of SID29 Subfunction08                   */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext : Message Context                      */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK            : Processing normal                    */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID29_Sub08_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
)
{
    Std_ReturnType  u1_RetVal;

    u1_RetVal = E_OK;

    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );
    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

    Dcm_Dsp_Main_stMsgContext = *ptMsgContext;
    Dcm_Dsp_SID29_u1AuthTask = DCM_DSP_SID29_AUTHTASK_AUTHCONFIG;

    if( Dcm_Dsp_Main_stMsgContext.reqDataLen == DCM_DSP_SID29_REQ_SUB08_LEN )
    {
        Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID29_RES_RETVAL_POS] = DCM_DSP_SID29_AUTHRETPARA_ACAPCE;
        Dcm_Dsp_Main_stMsgContext.resDataLen = (uint32)DCM_DSP_SID29_RES_RETVAL_LEN;

        Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
    }
    else
    {
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext,
                                     DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT );
    }

    return u1_RetVal;
}
#endif /* DCM_SUPPORT_SID29_SUB08 == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID29_VrfyCertUnidirProc                         */
/* Description   | Process of verify client certificate Unidirectionally    */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus   : Operation state                        */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK          : Processing normal                      */
/*               |   DCM_E_PENDING : Pending                                */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID29_VrfyCertUnidirProc
(
    const Dcm_OpStatusType u1OpStatus
)
{
    uint32                          u4_OutDataMaxLength;
    uint32                          u4_LengthOfEphemeralPublicKeyServerPos;
    uint16                          u2_LengthOfChallengeServer;
    Std_ReturnType                  u1_RetVal;
    Dcm_NegativeResponseCodeType    u1_ErrorCode;

    u4_OutDataMaxLength = (uint32)( Dcm_Dsp_Main_stMsgContext.resMaxDataLen - DCM_DSP_SID29_RES_RETVAL_LEN );   /* no wrap around */
    u1_ErrorCode = DCM_E_GENERALREJECT;

    u1_RetVal = Dcm_VerifyCertificateUnidir( u1OpStatus,
                                             Dcm_Dsp_SID29_u2ConnectionId,
                                             &Dcm_Dsp_SID29_stVrfyCertIndata,
                                             u4_OutDataMaxLength,
                                             &Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID29_RES_LOCHSE_MSB_POS],
                                             &u1_ErrorCode );
    if( u1_RetVal == (Std_ReturnType)E_OK )
    {
        if( u1OpStatus == (Dcm_OpStatusType)DCM_PENDING )
        {
            Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        }

        Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID29_RES_RETVAL_POS] = DCM_DSP_SID29_AUTHRETPARA_CVOVN;

        u2_LengthOfChallengeServer = (uint16)( (uint16)Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID29_RES_LOCHSE_MSB_POS] << DCM_DSP_SID29_RES_LOCHSE_SHIFT ) |
                                             (uint16)Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID29_RES_LOCHSE_LSB_POS];

        u4_LengthOfEphemeralPublicKeyServerPos = (uint32)( DCM_DSP_SID29_RES_RETVAL_LEN +
                                                           DCM_DSP_SID29_RES_LOCHSE_LEN +   /* no wrap around */
                                                          (uint32)u2_LengthOfChallengeServer );

        Dcm_Dsp_Main_stMsgContext.resData[u4_LengthOfEphemeralPublicKeyServerPos] = DCM_DSP_SID29_LOEPKSE_MSB;
        u4_LengthOfEphemeralPublicKeyServerPos++;   /* no wrap around */
        Dcm_Dsp_Main_stMsgContext.resData[u4_LengthOfEphemeralPublicKeyServerPos] = DCM_DSP_SID29_LOEPKSE_LSB;

        Dcm_Dsp_Main_stMsgContext.resDataLen = (uint32)( DCM_DSP_SID29_RES_RETVAL_LEN +
                                                         DCM_DSP_SID29_RES_LOCHSE_LEN +         /* no wrap around */
                                                         (uint32)u2_LengthOfChallengeServer +   /* no wrap around */
                                                         DCM_DSP_SID29_RES_LOEPKSE_LEN );

        Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
    }
    else if( u1_RetVal == (Std_ReturnType)DCM_E_PENDING )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID29_VRFYCERTUNIDIR );  /* no return check required */
    }
    else
    {
        if( u1OpStatus == (Dcm_OpStatusType)DCM_PENDING )
        {
            Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        }

        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext,
                                     u1_ErrorCode );
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID29_VrfyCertBidirProc                          */
/* Description   | Process of verify client certificate Bidirectionally     */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus   : Operation state                        */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK          : Processing normal                      */
/*               |   DCM_E_PENDING : Pending                                */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID29_VrfyCertBidirProc
(
    const Dcm_OpStatusType u1OpStatus
)
{
    uint32                          u4_OutDataMaxLength;
    uint32                          u4_LengthOfCertificateServerPos;
    uint32                          u4_LengthOfProofOfOwnershipServerPos;
    uint32                          u4_LengthOfEphemeralPublicKeyServerPos;
    uint16                          u2_LengthOfChallengeServer;
    uint16                          u2_LengthOfCertificateServer;
    uint16                          u2_LengthOfProofOfOwnershipServer;
    Std_ReturnType                  u1_RetVal;
    Dcm_NegativeResponseCodeType    u1_ErrorCode;

    u4_OutDataMaxLength = (uint32)( Dcm_Dsp_Main_stMsgContext.resMaxDataLen - DCM_DSP_SID29_RES_RETVAL_LEN );   /* no wrap around */
    u1_ErrorCode = DCM_E_GENERALREJECT;

    u1_RetVal = Dcm_VerifyCertificateBidir( u1OpStatus,
                                            Dcm_Dsp_SID29_u2ConnectionId,
                                            &Dcm_Dsp_SID29_stVrfyCertIndata,
                                            u4_OutDataMaxLength,
                                            &Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID29_RES_LOCHSE_MSB_POS],
                                            &u1_ErrorCode );
    if( u1_RetVal == (Std_ReturnType)E_OK )
    {
        if( u1OpStatus == (Dcm_OpStatusType)DCM_PENDING )
        {
            Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        }

        Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID29_RES_RETVAL_POS] = DCM_DSP_SID29_AUTHRETPARA_CVOVN;

        u2_LengthOfChallengeServer = (uint16)( (uint16)Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID29_RES_LOCHSE_MSB_POS] << DCM_DSP_SID29_RES_LOCHSE_SHIFT ) |
                                             (uint16)Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID29_RES_LOCHSE_LSB_POS];

        u4_LengthOfCertificateServerPos = (uint32)( DCM_DSP_SID29_RES_RETVAL_LEN +
                                                    DCM_DSP_SID29_RES_LOCHSE_LEN +  /* no wrap around */
                                                    (uint32)u2_LengthOfChallengeServer );
        u2_LengthOfCertificateServer = (uint16)( (uint16)Dcm_Dsp_Main_stMsgContext.resData[u4_LengthOfCertificateServerPos] << DCM_DSP_SID29_RES_LOCESE_SHIFT );
        u4_LengthOfCertificateServerPos++;  /* no wrap around */
        u2_LengthOfCertificateServer |= (uint16)Dcm_Dsp_Main_stMsgContext.resData[u4_LengthOfCertificateServerPos];

        u4_LengthOfProofOfOwnershipServerPos = (uint32)( DCM_DSP_SID29_RES_RETVAL_LEN +
                                                         DCM_DSP_SID29_RES_LOCHSE_LEN +         /* no wrap around */
                                                         (uint32)u2_LengthOfChallengeServer +   /* no wrap around */
                                                         DCM_DSP_SID29_RES_LOCESE_LEN +         /* no wrap around */
                                                         (uint32)u2_LengthOfCertificateServer );
        u2_LengthOfProofOfOwnershipServer = (uint16)( (uint16)Dcm_Dsp_Main_stMsgContext.resData[u4_LengthOfProofOfOwnershipServerPos] << DCM_DSP_SID29_RES_LPOWNSE_SHIFT );
        u4_LengthOfProofOfOwnershipServerPos++; /* no wrap around */
        u2_LengthOfProofOfOwnershipServer |= (uint16)Dcm_Dsp_Main_stMsgContext.resData[u4_LengthOfProofOfOwnershipServerPos];

        u4_LengthOfEphemeralPublicKeyServerPos = (uint32)( DCM_DSP_SID29_RES_RETVAL_LEN +
                                                           DCM_DSP_SID29_RES_LOCHSE_LEN +           /* no wrap around */
                                                           (uint32)u2_LengthOfChallengeServer +     /* no wrap around */
                                                           DCM_DSP_SID29_RES_LOCESE_LEN +           /* no wrap around */
                                                           (uint32)u2_LengthOfCertificateServer +   /* no wrap around */
                                                           DCM_DSP_SID29_RES_LPOWNSE_LEN +          /* no wrap around */
                                                           (uint32)u2_LengthOfProofOfOwnershipServer );

        Dcm_Dsp_Main_stMsgContext.resData[u4_LengthOfEphemeralPublicKeyServerPos] = DCM_DSP_SID29_LOEPKSE_MSB;
        u4_LengthOfEphemeralPublicKeyServerPos++;   /* no wrap around */
        Dcm_Dsp_Main_stMsgContext.resData[u4_LengthOfEphemeralPublicKeyServerPos] = DCM_DSP_SID29_LOEPKSE_LSB;

        Dcm_Dsp_Main_stMsgContext.resDataLen = (uint32)( DCM_DSP_SID29_RES_RETVAL_LEN +
                                                         DCM_DSP_SID29_RES_LOCHSE_LEN +                 /* no wrap around */
                                                         (uint32)u2_LengthOfChallengeServer +           /* no wrap around */
                                                         DCM_DSP_SID29_RES_LOCESE_LEN +                 /* no wrap around */
                                                         (uint32)u2_LengthOfCertificateServer +         /* no wrap around */
                                                         DCM_DSP_SID29_RES_LPOWNSE_LEN +                /* no wrap around */
                                                         (uint32)u2_LengthOfProofOfOwnershipServer +    /* no wrap around */
                                                         DCM_DSP_SID29_RES_LOEPKSE_LEN );

        Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
    }
    else if( u1_RetVal == (Std_ReturnType)DCM_E_PENDING )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID29_VRFYCERTBIDIR );   /* no return check required */
    }
    else
    {
        if( u1OpStatus == (Dcm_OpStatusType)DCM_PENDING )
        {
            Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        }

        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext,
                                     u1_ErrorCode );
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID29_VrfyPownProc                               */
/* Description   | Process of verify client proof of ownership              */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus   : Operation state                        */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK          : Processing normal                      */
/*               |   DCM_E_PENDING : Pending                                */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID29_VrfyPownProc
(
    const Dcm_OpStatusType u1OpStatus
)
{
    Std_ReturnType                  u1_RetVal;
    Dcm_NegativeResponseCodeType    u1_ErrorCode;

    u1_ErrorCode = DCM_E_GENERALREJECT;

    u1_RetVal = Dcm_VerifyPown( u1OpStatus,
                                Dcm_Dsp_SID29_u2ConnectionId,
                                &Dcm_Dsp_SID29_stVrfyPownIndata,
                                &u1_ErrorCode );
    if( u1_RetVal == (Std_ReturnType)E_OK )
    {
        if( u1OpStatus == (Dcm_OpStatusType)DCM_PENDING )
        {
            Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        }

        Dcm_Dsl_SetAuthState( DCM_AUTHENTICATED,
                              Dcm_Dsp_SID29_u2ConnectionId );

        Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID29_RES_RETVAL_POS] = DCM_DSP_SID29_AUTHRETPARA_OVAC;
        Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID29_RES_LOSKI_MSB_POS] = DCM_DSP_SID29_LOSKI_MSB;
        Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID29_RES_LOSKI_LSB_POS] = DCM_DSP_SID29_LOSKI_LSB;

        Dcm_Dsp_Main_stMsgContext.resDataLen = (uint32)( DCM_DSP_SID29_RES_RETVAL_LEN +
                                                         DCM_DSP_SID29_RES_LOSKI_LEN );

        Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
    }
    else if( u1_RetVal == (Std_ReturnType)DCM_E_PENDING )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID29_VRFYPOWN );    /* no return check required */
    }
    else
    {
        if( u1OpStatus == (Dcm_OpStatusType)DCM_PENDING )
        {
            Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        }
        
        
        if( ( ( u1_ErrorCode >= DCM_DSP_SID29_NRC_VERI_FAIL_RANGE_MIN ) &&
              ( u1_ErrorCode <= DCM_DSP_SID29_NRC_VERI_FAIL_RANGE_MAX ) ) ||
            (   u1_ErrorCode == DCM_E_GENERALREJECT                     ) )
        {
            Dcm_Dsp_SID29_bVrfyCertExctdFlg[Dcm_Dsp_SID29_u2ConnectionId] = (boolean)FALSE;
        }
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext,
                                     u1_ErrorCode );
    }

    return u1_RetVal;
}

#if ( DCM_SUPPORT_SID29_SUB01 == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID29_Sub01_CancelProc                           */
/* Description   | Cancel process of SID29 Subfunction01                    */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK : Processing normal                               */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID29_Sub01_CancelProc
( void )
{
    Std_ReturnType  u1_RetVal;
    boolean         b_UserNotifyFlag;

    u1_RetVal = E_OK;

    b_UserNotifyFlag = Dcm_Dsp_Main_GetUserNotifyFlag();
    if( b_UserNotifyFlag == (boolean)TRUE )
    {
        (void)Dcm_VerifyCertificateUnidir( DCM_CANCEL,                      /* no return check required */
                                           DCM_DSP_SID29_CNCTID_INVALID,
                                           NULL_PTR,
                                           0x00000000UL,
                                           NULL_PTR,
                                           NULL_PTR );

        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
    }

    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID29_VRFYCERTUNIDIR,  /* no return check required */
                                         (boolean)FALSE );

    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return u1_RetVal;
}
#endif /* DCM_SUPPORT_SID29_SUB01 == STD_ON */

#if ( DCM_SUPPORT_SID29_SUB02 == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID29_Sub02_CancelProc                           */
/* Description   | Cancel process of SID29 Subfunction02                    */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK : Processing normal                               */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID29_Sub02_CancelProc
( void )
{
    Std_ReturnType  u1_RetVal;
    boolean         b_UserNotifyFlag;

    u1_RetVal = E_OK;

    b_UserNotifyFlag = Dcm_Dsp_Main_GetUserNotifyFlag();
    if( b_UserNotifyFlag == (boolean)TRUE )
    {
        (void)Dcm_VerifyCertificateBidir( DCM_CANCEL,                       /* no return check required */
                                          DCM_DSP_SID29_CNCTID_INVALID,
                                          NULL_PTR,
                                          0x00000000UL,
                                          NULL_PTR,
                                          NULL_PTR );

        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
    }

    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID29_VRFYCERTBIDIR,   /* no return check required */
                                         (boolean)FALSE );

    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return u1_RetVal;
}
#endif /* DCM_SUPPORT_SID29_SUB02 == STD_ON */

#if ( DCM_SUPPORT_SID29_SUB03 == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID29_Sub03_CancelProc                           */
/* Description   | Cancel process of SID29 Subfunction03                    */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK : Processing normal                               */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID29_Sub03_CancelProc
( void )
{
    Std_ReturnType  u1_RetVal;
    boolean         b_UserNotifyFlag;

    u1_RetVal = E_OK;

    b_UserNotifyFlag = Dcm_Dsp_Main_GetUserNotifyFlag();
    if( b_UserNotifyFlag == (boolean)TRUE )
    {
        (void)Dcm_VerifyPown( DCM_CANCEL,                               /* no return check required */
                              DCM_DSP_SID29_CNCTID_INVALID,
                              NULL_PTR,
                              NULL_PTR );

        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
    }

    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID29_VRFYPOWN,    /* no return check required */
                                         (boolean)FALSE );

    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return u1_RetVal;
}
#endif /* DCM_SUPPORT_SID29_SUB03 == STD_ON */

#if ( ( DCM_SUPPORT_SID29_SUB00 == STD_ON ) || ( DCM_SUPPORT_SID29_SUB08 == STD_ON ) )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID29_CancelProcOnlySetIdleFlag                  */
/* Description   | Cancel process of SID29 for only set IdleFlag to TRUE    */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK : Processing normal                               */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID29_CancelProcOnlySetIdleFlag
( void )
{
    Std_ReturnType  u1_RetVal;

    u1_RetVal = E_OK;

    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return u1_RetVal;
}
#endif /* DCM_SUPPORT_SID29_SUB00 == STD_ON || DCM_SUPPORT_SID29_SUB08 == STD_ON */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
#endif /* DCM_AUTHENTICATION_USE */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

