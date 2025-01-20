/* Dcm_Dsp_SID3E_c(v5-0-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID3E/CODE                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsp_SID3E.h>
#if ( DCM_SUPPORT_SID3E == STD_ON )
#include <Dcm/Dcm_Dsp_Main.h>
#include "../../Dsp/inc/Dcm_Dsp_MsgMaker.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSP_SID3E_MSGLEN ((uint8)0U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID3E_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
);
static FUNC(void, DCM_CODE) Dcm_Dsp_SID3E_CancelProc
(
    void
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

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* Function Name | Dcm_SID3E_Sub00                                          */
/* Description   | SID3E request processing                                 */
/* Preconditions |                                                          */
/* Parameters    | [IN]   Dcm_OpStatusType             : OpStatus           */
/*               | [IN]   const Dcm_MsgContextType*    : pMsgContext        */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK          0x00                                       */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID3E_Sub00    /* MISRA DEVIATION */
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
)
{
    Std_ReturnType  u1_RetVal;

    u1_RetVal = E_OK;

    if( OpStatus == ( Dcm_OpStatusType )DCM_INITIAL )           /* DCM_INITIAL */
    {
        u1_RetVal = Dcm_Dsp_SID3E_InitialProc( pMsgContext );
    }
    else if( OpStatus == (Dcm_OpStatusType)DCM_CANCEL )         /* DCM_CANCEL */
    {
        Dcm_Dsp_SID3E_CancelProc();
    }
    else
    {
        /* No process */
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID3E_InitialProc                                */
/* Description   | Execute SID 3E request processing                        */
/* Preconditions |                                                          */
/* Parameters    | [IN]   const Dcm_MsgContextType*    : ptMsgContext       */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK          0x00                                       */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID3E_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
)
{
    Std_ReturnType  u1_RetVal;
    Dcm_NegativeResponseCodeType u1_ErrorCode;
    Dcm_MsgContextType st_MsgContext_temp;

    u1_RetVal = E_OK;

    /* Set Dcm_Dsp_Main_bIdleFlag in FALSE                                  */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );
    st_MsgContext_temp = *ptMsgContext;

    if( st_MsgContext_temp.reqDataLen == DCM_DSP_SID3E_MSGLEN )
    {
        Dcm_Dsp_MsgMaker_SendPosRes( &st_MsgContext_temp );
    }
    else
    {
        u1_ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        Dcm_Dsp_MsgMaker_SendNegRes( &st_MsgContext_temp, u1_ErrorCode );
    }

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID3E_CancelProc                                 */
/* Description   | Cancel function for SID3E                                */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsp_SID3E_CancelProc
(
    void
)
{
    /* Set Dcm_Dsp_Main_bIdleFlag in TRUE                                   */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return;
}


#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
#endif /* DCM_SUPPORT_SID3E == STD_ON */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v5-0-0         :2022-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
