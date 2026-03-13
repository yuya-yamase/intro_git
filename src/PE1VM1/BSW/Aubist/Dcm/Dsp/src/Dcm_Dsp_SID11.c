/* Dcm_Dsp_SID11_c(v5-1-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID11/CODE                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsp_SID11.h>
#if ( DCM_SUPPORT_SID11 == STD_ON )
#include "../../Dsp/usr/Dcm_Dsp_SID11_Connector.h"
#include "../../Dsp/inc/Dcm_Dsp_MsgMaker.h"
#include <Dcm/Dcm_Main_Common.h>
#include <Dcm/Dcm_Main_EvtDistr.h>
#include <Dcm/Dcm_Dsp_Main.h>

#include <Dcm.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define     DCM_DSP_SID11_SUBNONE                  ((uint8)0U)
#define     DCM_DSP_SID11_REQDATA_LEN              ((Dcm_MsgLenType)0x0U)
#define     DCM_DSP_SID11_RESDATA_LEN              ((Dcm_MsgLenType)0x0U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID11_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext,
    const uint8 u1SubFunction
);
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID11_CancelProc
( void );

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

static VAR( uint8, DCM_VAR_NO_INIT ) Dcm_Dsp_SID11_RequestMode;

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
/* Function Name | Dcm_Dsp_SID11_Init                                       */
/* Description   | SID 11 initialization                                    */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID11_Init    /* MISRA DEVIATION */
( void )
{
    Dcm_Dsp_SID11_RequestMode = DCM_DSP_SID11_SUBNONE;

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID11                                            */
/* Description   | Request processing of SID 11                             */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1OpStatus     : Operation state                    */
/*               | [IN] ptMsgContext   : Message Context                    */
/*               | [IN] u1SubFunction  : Sub Function                       */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID11    /* MISRA DEVIATION */
(
    Dcm_OpStatusType u1OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext,
    const uint8 u1SubFunction
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_OK;

    if( u1OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
        u1_RetVal = Dcm_Dsp_SID11_InitialProc( ptMsgContext, u1SubFunction );
    }
    else if( u1OpStatus == (Dcm_OpStatusType)DCM_CANCEL )
    {
        Dcm_Dsp_SID11_CancelProc();
    }
    else
    {
        /* No process */
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID11_Confirmation                               */
/* Description   | Complete transmission of SID 11 response message.        */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1IdContext     : Id Context                        */
/*               | [IN] u2ConnectionId  : Source Address                    */
/*               | [IN] u1Status        : Status                            */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID11_Confirmation    /* MISRA DEVIATION */
(
    const Dcm_IdContextType u1IdContext,             /* MISRA DEVIATION */
    const uint16 u2ConnectionId,                     /* MISRA DEVIATION */
    const Dcm_ConfirmationStatusType u1Status
)
{
    if( ( Dcm_Dsp_SID11_RequestMode == DCM_DSP_SID11_SUB01 ) ||
        ( Dcm_Dsp_SID11_RequestMode == DCM_DSP_SID11_SUB02 ) )
    {
        switch( u1Status )
        {
            case DCM_RES_POS_OK:
                /* Notify BswM of Mode Transition to EXECUTE */
                (void)Dcm_Dsp_SID11_Cnct_Sw_EcuReset( RTE_MODE_DcmEcuReset_EXECUTE ); /* no return check required */
                break;
            case DCM_RES_POS_NOT_OK:
                /* Notify BswM of Mode Transition to None */
                (void)Dcm_Dsp_SID11_Cnct_Sw_EcuReset( RTE_MODE_DcmEcuReset_NONE ); /* no return check required */
                break;
            case DCM_RES_NEG_OK:
            case DCM_RES_NEG_NOT_OK:
            default:
                /* No process */
                break;
        }
    }
    else
    {
        /* No Process */
    }

    Dcm_Dsp_SID11_RequestMode = DCM_DSP_SID11_SUBNONE;

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID11_Cbk                                        */
/* Description   |                                                          */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId : Event ID                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID11_Cbk    /* MISRA DEVIATION */
(
    const uint8 u1EventId                   /* MISRA DEVIATION */
)
{
    Std_ReturnType  u1_RetGetPreReset;

    if( ( Dcm_Dsp_SID11_RequestMode == DCM_DSP_SID11_SUB01 ) ||
        ( Dcm_Dsp_SID11_RequestMode == DCM_DSP_SID11_SUB02 ) )
    {
        u1_RetGetPreReset = Dcm_GetPreResetConditions();

        if( u1_RetGetPreReset == (Std_ReturnType)E_OK )
        {
            /* Send Positive response */
            Dcm_Dsp_Main_stMsgContext.resDataLen = DCM_DSP_SID11_RESDATA_LEN;
            Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
        }
        else if( u1_RetGetPreReset == (Std_ReturnType)DCM_E_PENDING )
        {
            (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID11_GETPRERESET ); /* no return check required */
        }
        else
        {
            /* Notify BswM of Mode Transition to NONE */
            (void)Dcm_Dsp_SID11_Cnct_Sw_EcuReset( RTE_MODE_DcmEcuReset_NONE ); /* no return check required */

            Dcm_Dsp_SID11_RequestMode = DCM_DSP_SID11_SUBNONE;

            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, (Dcm_NegativeResponseCodeType)DCM_E_CONDITIONSNOTCORRECT );

        }
    }

    return;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID11_InitialProc                                */
/* Description   | Initial process of SID 11 request                        */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext   : Message Context                    */
/*               | [IN] u1SubFunction  : Sub Function                       */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID11_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext,
    const uint8 u1SubFunction
)
{
    boolean                      b_SendNegResFlag;
    Std_ReturnType               u1_RetVal;
    Std_ReturnType               u1_RetCheck;
    Dcm_NegativeResponseCodeType u1_NegResCode;
    Dcm_NegativeResponseCodeType u1_ErrorCode;
    Std_ReturnType               u1_RetGetPreReset;

    b_SendNegResFlag = (boolean)FALSE;
    u1_RetVal = (Std_ReturnType)E_OK;
    Dcm_Dsp_Main_stMsgContext = *ptMsgContext;
    Dcm_Dsp_SID11_RequestMode = u1SubFunction;

    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );


    /* Check request message length */
    if( Dcm_Dsp_Main_stMsgContext.reqDataLen == DCM_DSP_SID11_REQDATA_LEN )
    {
        /* Check Condition to execute */
        u1_RetCheck = Dcm_Dsp_SID11_CheckCondition( u1SubFunction, &u1_ErrorCode );
        if( u1_RetCheck == (Std_ReturnType)E_OK )
        {
            if( ( u1SubFunction == DCM_DSP_SID11_SUB01 ) ||
                ( u1SubFunction == DCM_DSP_SID11_SUB02 ) )
            {
                if( u1SubFunction == DCM_DSP_SID11_SUB01 )
                {
                    /* Notify BswM of Mode Transition to HARD */
                    (void)Dcm_Dsp_SID11_Cnct_Sw_EcuReset( RTE_MODE_DcmEcuReset_HARD );  /* no return check required */
                }
                else /*  u1SubFunction == DCM_DSP_SID11_SUB02 */
                {
                    /* Notify BswM of Mode Transition to KEYONOFF */
                    (void)Dcm_Dsp_SID11_Cnct_Sw_EcuReset( RTE_MODE_DcmEcuReset_KEYONOFF );  /* no return check required */
                }

                u1_RetGetPreReset = Dcm_GetPreResetConditions();

                if( u1_RetGetPreReset == (Std_ReturnType)E_OK )
                {
                    /* Send Positive response */
                    Dcm_Dsp_Main_stMsgContext.resDataLen = DCM_DSP_SID11_RESDATA_LEN;
                    Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
                }
                else if( u1_RetGetPreReset == (Std_ReturnType)DCM_E_PENDING )
                {
                    (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID11_GETPRERESET ); /* no return check required */
                }
                else
                {
                    /* Notify BswM of Mode Transition to NONE */
                    (void)Dcm_Dsp_SID11_Cnct_Sw_EcuReset( RTE_MODE_DcmEcuReset_NONE ); /* no return check required */

                    /* Set NRC to 0x22 */
                    u1_NegResCode = DCM_E_CONDITIONSNOTCORRECT;
                    b_SendNegResFlag = (boolean)TRUE;
                }
            }
            else
            {
                /* No Process */
            }
        }
        else
        {
            /* Set NRC to User defined Code(0xXX) */
            u1_NegResCode = u1_ErrorCode;
            b_SendNegResFlag = (boolean)TRUE;
        }
    }
    else
    {
        /* Set NRC to 0x13 */
        u1_NegResCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        b_SendNegResFlag = (boolean)TRUE;
    }

    if( b_SendNegResFlag == (boolean)TRUE )
    {
        Dcm_Dsp_SID11_RequestMode = DCM_DSP_SID11_SUBNONE;

        /* Send Negative Response */
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_NegResCode );
    }
    else
    {
        /* No process */
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID11_CancelProc                                 */
/* Description   | Cancel process of SID 11 request                         */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID11_CancelProc
( void )
{
    if( ( Dcm_Dsp_SID11_RequestMode == DCM_DSP_SID11_SUB01 ) ||
        ( Dcm_Dsp_SID11_RequestMode == DCM_DSP_SID11_SUB02 ) )
    {
        /* Notify BswM of Mode Transition to EXECUTE */
        (void)Dcm_Dsp_SID11_Cnct_Sw_EcuReset( RTE_MODE_DcmEcuReset_NONE ); /* no return check required */
    }
    else
    {
        /* No Process*/
    }

    Dcm_Dsp_SID11_RequestMode = DCM_DSP_SID11_SUBNONE;

    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID11_GETPRERESET, (boolean)FALSE ); /* no return check required */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return;
}

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
#endif /* DCM_SUPPORT_SID11 == STD_ON */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-0-0         :2019-09-26                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
