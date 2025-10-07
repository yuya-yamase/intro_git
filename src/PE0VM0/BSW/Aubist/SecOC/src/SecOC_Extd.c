/* SecOC_Extd_c_v2-1-0                                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name | SecOC/Extd/CODE                                            */
/*--------------------------------------------------------------------------*/
/* Notes       |                                                            */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <SchM_SecOC.h>
#include <SecOC_Extd.h>
#include "../inc/SecOC_If.h"
#include "../inc/SecOC_Rx.h"
#include "../inc/SecOC_Extd_Internal.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
#if (SECOC_AB_TRIAL_WORK == STD_ON)
#define SECOC_EXTD_PROTO_MODE_DISABLE ((uint8)0xE1U)
#define SECOC_EXTD_PROTO_MODE_ENABLE  ((uint8)0xD2U)
#endif
#endif

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define SECOC_START_SEC_CODE
#include <SecOC_MemMap.h>

#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
#if (SECOC_AB_TRIAL_WORK == STD_ON)
static FUNC(void, SECOC_CODE) SecOC_Extd_SetProtoMode
(
    uint8 u1ProtoMode
);

static FUNC(uint8, SECOC_CODE) SecOC_Extd_GetProtoMode
(
    void
);
#endif
#endif

#define SECOC_STOP_SEC_CODE
#include <SecOC_MemMap.h>
/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define SECOC_START_SEC_VAR_NO_INIT
#include <SecOC_MemMap.h>

#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
#if (SECOC_AB_TRIAL_WORK == STD_ON)
static VAR(uint8, SECOC_VAR_NO_INIT) SecOC_Extd_u1ProtoMode;
#endif
#endif

#define SECOC_STOP_SEC_VAR_NO_INIT
#include <SecOC_MemMap.h>
/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define SECOC_START_SEC_CODE
#include <SecOC_MemMap.h>

#if (SECOC_AB_EXTD_INIT == STD_ON)
/****************************************************************************/
/* Function Name | SecOC_Extd_Init                                          */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, SECOC_CODE) SecOC_Extd_Init
(
    void
)
{
#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
#if (SECOC_AB_TRIAL_WORK == STD_ON)
    SecOC_Extd_u1ProtoMode = SECOC_EXTD_PROTO_MODE_DISABLE;
#endif
#endif

    return ;
}
#endif

#if (SECOC_AB_EXTD_DEINIT == STD_ON)
/****************************************************************************/
/* Function Name | SecOC_Extd_DeInit                                        */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, SECOC_CODE) SecOC_Extd_DeInit
(
    void
)
{
#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
#if (SECOC_AB_TRIAL_WORK == STD_ON)
    SecOC_Extd_u1ProtoMode = SECOC_EXTD_PROTO_MODE_DISABLE;
#endif
#endif

    return ;
}
#endif

#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
#if (SECOC_AB_EXTD_FV_UPDATE_JUDGE == STD_ON)
/****************************************************************************/
/* Function Name | SecOC_Extd_PreFvUpdate                                   */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index :                                                */
/*               | ud_macResult :                                           */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK     : Success                                      */
/*               |  E_NOT_OK : Failure                                      */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Extd_PreFvUpdate
(
    uint16 u2Index,
    Std_ReturnType udmacResult
)
{
    Std_ReturnType ud_stdRet = udmacResult;
#if (SECOC_AB_TRIAL_WORK == STD_ON)
    P2CONST(SecOC_RxPduProcessingType, AUTOMATIC, SECOC_APPL_DATA) pt_rxConfig = &SecOC_RxPduProcessing[u2Index];
    uint8 u1_protoMode;

    if( pt_rxConfig->Ab_MessageType == (uint8)SECOC_AB_MSGTYPE_SYNC )
    {
        u1_protoMode = SecOC_Extd_GetProtoMode();

        if( u1_protoMode == (uint8)STD_ON )
        {
            ud_stdRet = E_OK;
        }
    }
#endif

    return ud_stdRet;
}
#endif

#if (SECOC_AB_EXTD_MSG_NOTIFY_JUDGE == STD_ON)
/****************************************************************************/
/* Function Name | SecOC_Extd_MessageNotifyJudge                            */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index :                                                */
/* Return Value  | boolean                                                  */
/*               |  TRUE                                                    */
/*               |  FALSE                                                   */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(boolean, SECOC_CODE) SecOC_Extd_MessageNotifyJudge
(
    uint16 u2Index
)
{
    boolean  b_ret = (boolean)FALSE;
#if (SECOC_AB_TRIAL_WORK == STD_ON)
    uint8           u1_protoMode;

    u1_protoMode = SecOC_Extd_GetProtoMode();

    if( u1_protoMode == (uint8)STD_ON )
    {
        b_ret = (boolean)TRUE;
    }
#endif

    return b_ret;
}
#endif
#endif

#if (SECOC_AB_EXTD_VERIFY_STATUS_OVERRIDE == STD_ON)
/****************************************************************************/
/* Function Name | SecOC_Extd_VerifyStatusOverride                          */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | ValueID :                                                */
/*               | overrideStatus :                                         */
/*               | numberOfMessagesToOverride :                             */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK     : Success                                      */
/*               |  E_NOT_OK : Failure                                      */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Extd_VerifyStatusOverride
(
    uint32 ValueID,
    SecOC_OverrideStatusType overrideStatus,
    uint8 numberOfMessagesToOverride
)
{
    Std_ReturnType ud_stdRet = E_NOT_OK;

#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
#if (SECOC_AB_TRIAL_WORK == STD_ON)
    if( overrideStatus == SECOC_AB_OVERRIDE_TRIAL_UNTIL_NOTICE )
    {
        SecOC_Extd_SetProtoMode( STD_ON );
        ud_stdRet = E_OK;
    }
    else if( overrideStatus == SECOC_AB_OVERRIDE_TRIAL_CANCEL )
    {
        SecOC_Extd_SetProtoMode( STD_OFF );
        ud_stdRet = E_OK;
    }
    else
    {
        /* No Processing */
    }
#endif
#endif

    return ud_stdRet;
}
#endif

#if (SECOC_AB_EXTD_MEMUTIL == STD_ON)
/****************************************************************************/
/* Function Name | SecOC_Extd_MemCpy                                        */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | ptDst : output address                                   */
/*               | ptSrc : input address                                    */
/*               | u4Size : byte size                                       */
/* Return Value  | None                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, SECOC_CODE) SecOC_Extd_MemCpy
(
    P2VAR(void, AUTOMATIC, SECOC_APPL_DATA) ptDst,
    P2CONST(void, AUTOMATIC, SECOC_APPL_DATA) ptSrc,
    uint32 u4Size
)
{
    return ;
}
#endif

#if (SECOC_AB_MSG_AUTH_19PF_COMPATIBILITY == STD_ON)
/****************************************************************************/
/* Function Name | SecOC_Ab_ResetVerifyStart                                */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2BusId :                                                */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK     : Success                                      */
/*               |  E_NOT_OK : Failure                                      */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Ab_ResetVerifyStart
(
    uint16 u2BusId
)
{
    Std_ReturnType  ud_stdRet = E_NOT_OK;

    /* Parameters check */
    if( ( SecOC_If_udState == SECOC_INIT )
        &&( u2BusId < SecOC_Ab_BusMax ) )
    {
#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
                /* Reset VerifyStart */
                SecOC_Rx_ResetBus( u2BusId );
#endif
                ud_stdRet = E_OK;

    }
    return ud_stdRet;
}
#endif

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
#if (SECOC_AB_TRIAL_WORK == STD_ON)
/****************************************************************************/
/* Function Name | SecOC_Extd_SetProtoMode                                  */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u1ProtoMode : STD_ON or STD_OFF                          */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, SECOC_CODE) SecOC_Extd_SetProtoMode
(
    uint8 u1ProtoMode
)
{
    SchM_Enter_SecOC_Extd();

    if( u1ProtoMode == (uint8)STD_ON )
    {
        SecOC_Extd_u1ProtoMode = SECOC_EXTD_PROTO_MODE_ENABLE;
    }
    else
    {
        SecOC_Extd_u1ProtoMode = SECOC_EXTD_PROTO_MODE_DISABLE;
    }

    SchM_Exit_SecOC_Extd();

    return;
}

/****************************************************************************/
/* Function Name | SecOC_Extd_GetProtoMode                                  */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | uint8                                                    */
/*               |  STD_ON  : ProtoMode enable                              */
/*               |  STD_OFF : ProtoMode disable                             */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(uint8, SECOC_CODE) SecOC_Extd_GetProtoMode
(
    void
)
{
    uint8 u1_ret = (uint8)STD_OFF;

    if( SecOC_Extd_u1ProtoMode == SECOC_EXTD_PROTO_MODE_ENABLE )
    {
        u1_ret = (uint8)STD_ON;
    }

    return u1_ret;
}
#endif
#endif

#define SECOC_STOP_SEC_CODE
#include <SecOC_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version    :Date                                                        */
/*  v2-0-0     :2023/02/28                                                  */
/*  v2-1-0     :2023/10/02                                                  */
/****************************************************************************/

/**** End of File ***********************************************************/
