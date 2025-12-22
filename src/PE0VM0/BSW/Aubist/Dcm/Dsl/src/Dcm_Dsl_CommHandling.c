/* Dcm_Dsl_CommHandling_c(v5-0-0)                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsl_CommHandling/CODE                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../../Dsl/inc/Dcm_Dsl_CommHandling.h"
#include "../../Dsl/usr/Dcm_Dsl_CommHandling_Connector.h"
#include "../../Dsl/inc/Dcm_Dsl_Ctrl_local.h"
#include "../../Dsl/inc/Dcm_Dsl_Main.h"
#include <Dcm/Dcm_Dsl_Ctrl.h>
#include <Dcm/Dcm_Main_Common.h>
#include <Dcm_ComM.h>
#include <SchM_Dcm.h>
/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSL_COMM_NO_COMMODE       ((uint8)0x00U)
#define DCM_DSL_COMM_SILENT_COMMODE   ((uint8)0x01U)
#define DCM_DSL_COMM_FULL_COMMODE     ((uint8)0x02U)
#define DCM_DSL_COMM_NOT_ACTIVE       ((uint8)0x00U)
#define DCM_DSL_COMM_ACTIVE           ((uint8)0x01U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

static FUNC(void, DCM_CODE) Dcm_Dsl_CmHdl_SetComMode
(
    const uint8 u1NetworkId,
    const uint8 u1ComMode
);

static FUNC(boolean, DCM_CODE) Dcm_Dsl_CmHdl_IsParallelActiveComMCH
(
    const uint16 u2PduIdMapIndex
);

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

static VAR(Dcm_Dsl_ComModeType, DCM_VAR_NO_INIT) Dcm_Dsl_stComMode[DCM_DSL_CLIENT_NUM];
static VAR(volatile uint8, DCM_VAR_NO_INIT) Dcm_Dsl_u1ActiveStatus;

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
#define DCM_START_SEC_CODE_SHARE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* Function Name | Dcm_ComM_NoComModeEntered                                */
/* Description   | This call informs the Dcm module about a ComM mode chan- */
/*               | ge to COMM_NO_COMMUNICATION.                             */
/* Preconditions | none                                                     */
/* Parameters    | [in] NetworkId :                                         */
/*               |        Identifier of the network concerned by the mode - */
/*               |        change                                            */
/* Return Value  | void                                                     */
/*               |         :                                                */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_ComM_NoComModeEntered
(
    uint8 NetworkId
)
{
    /* Return value ignoring */
    (void)SchM_Call_Dcm_IocM_SetNoComMode(NetworkId);

    return ;
}


/****************************************************************************/
/* Function Name | Dcm_ComM_SilentComModeEntered                            */
/* Description   | This call informs the Dcm module about a ComM mode chan- */
/*               | ge to COMM_SILENT_COMMUNICATION.                         */
/* Preconditions | none                                                     */
/* Parameters    | [in] NetworkId :                                         */
/*               |        Identifier of the network concerned by the mode - */
/*               |        change                                            */
/* Return Value  | void                                                     */
/*               |         :                                                */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_ComM_SilentComModeEntered
(
    uint8 NetworkId
)
{
    /* Return value ignoring */
    (void)SchM_Call_Dcm_IocM_SetSilentComMode(NetworkId);

    return ;
}


/****************************************************************************/
/* Function Name | Dcm_ComM_FullComModeEntered                              */
/* Description   | This call informs the Dcm module about a ComM mode chan- */
/*               | ge to COMM_FULL_COMMUNICATION.                           */
/* Preconditions | none                                                     */
/* Parameters    | [in] NetworkId :                                         */
/*               |        Identifier of the network concerned by the mode - */
/*               |        change                                            */
/* Return Value  | void                                                     */
/*               |         :                                                */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_ComM_FullComModeEntered
(
    uint8 NetworkId
)
{
    /* Return value ignoring */
    (void)SchM_Call_Dcm_IocM_SetFullComMode(NetworkId);

    return ;
}

#define DCM_STOP_SEC_CODE_SHARE
#include <Dcm_MemMap.h>

#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* Function Name | Dcm_Dsl_CmHdl_Init                                       */
/* Description   | This function initializes the Dsl_CommHandling unit.     */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_CmHdl_Init
(void)
{
    uint16 u2_ClientCnt;
    uint16 u2_ClientNum;

    u2_ClientNum = Dcm_Dsl_u2ClientNum;

    for( u2_ClientCnt = (uint16)0; u2_ClientCnt < u2_ClientNum; u2_ClientCnt++ )
    {
        Dcm_Dsl_stComMode[u2_ClientCnt].u1ComModeState        = DCM_DSL_COMM_NO_COMMODE;
        Dcm_Dsl_stComMode[u2_ClientCnt].bActiveIndicationFlag = (boolean)FALSE;
    }

    Dcm_Dsl_u1ActiveStatus = DCM_DSL_COMM_ACTIVE;

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_SetNoComMode                                         */
/* Description   | This call informs the Dcm module about a ComM mode chan- */
/*               | ge to COMM_NO_COMMUNICATION.                             */
/* Preconditions | none                                                     */
/* Parameters    | [in] u1NetworkId :                                       */
/*               |        Identifier of the network concerned by the mode - */
/*               |        change                                            */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : this value is always returned.             */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_SetNoComMode
(
    const uint8 u1NetworkId
)
{
    Dcm_Dsl_CmHdl_SetComMode(u1NetworkId, DCM_DSL_COMM_NO_COMMODE);

    return E_OK;
}


/****************************************************************************/
/* Function Name | Dcm_SetSilentComMode                                     */
/* Description   | This call informs the Dcm module about a ComM mode chan- */
/*               | ge to COMM_SILENT_COMMUNICATION.                         */
/* Preconditions | none                                                     */
/* Parameters    | [in] u1NetworkId :                                       */
/*               |        Identifier of the network concerned by the mode - */
/*               |        change                                            */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : this value is always returned.             */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_SetSilentComMode
(
    const uint8 u1NetworkId
)
{
    Dcm_Dsl_CmHdl_SetComMode(u1NetworkId, DCM_DSL_COMM_SILENT_COMMODE);

    return E_OK;
}


/****************************************************************************/
/* Function Name | Dcm_ComM_FullComModeEntered                              */
/* Description   | This call informs the Dcm module about a ComM mode chan- */
/*               | ge to COMM_FULL_COMMUNICATION.                           */
/* Preconditions | none                                                     */
/* Parameters    | [in] u1NetworkId :                                       */
/*               |        Identifier of the network concerned by the mode - */
/*               |        change                                            */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : this value is always returned.             */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_SetFullComMode
(
    const uint8 u1NetworkId
)
{
    Dcm_Dsl_CmHdl_SetComMode(u1NetworkId, DCM_DSL_COMM_FULL_COMMODE);

    return E_OK;
}


/****************************************************************************/
/* Function Name | Dcm_Dsl_CmHdl_IsComEnable                                */
/* Description   | This function checks ComMode and notifies the            */
/*               | communication availability.                              */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduIdMapIndex : Management number of PduId        */
/*               |                                                          */
/*               | [in] u1CommunicationType : Communication Type (Rx or Tx) */
/*               |                                                          */
/* Return Value  | boolean                                                  */
/*               |        True : Enable Communication                       */
/*               |        False : Disable Communication                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_Dsl_CmHdl_IsComEnable
(
    const uint16    u2PduIdMapIndex,
    const uint8     u1CommunicationType
)
{
    boolean b_RetVal;
    boolean b_TxEnable;
    uint16  u2_ClientIndex;
    uint8   u1_ComMChannel;

    b_RetVal       = (boolean)FALSE;
    u2_ClientIndex = Dcm_Dsl_PduIdMapTable[u2PduIdMapIndex].u2ClientIndex;

    if( u1CommunicationType == DCM_DSL_COMTYPE_RECEIVE )
    {
        if( (Dcm_Dsl_stComMode[u2_ClientIndex].u1ComModeState == DCM_DSL_COMM_FULL_COMMODE)
         || (Dcm_Dsl_stComMode[u2_ClientIndex].u1ComModeState == DCM_DSL_COMM_SILENT_COMMODE) )
        {
            b_RetVal = (boolean)TRUE;
        }
        else
        {
            /* none */
        }
    }
    else /* DCM_DSL_COMTYPE_TRANSMIT */
    {
        if( Dcm_Dsl_stComMode[u2_ClientIndex].u1ComModeState == DCM_DSL_COMM_FULL_COMMODE )
        {
            u1_ComMChannel = Dcm_Dsl_Ctrl_GetComMChannel(u2PduIdMapIndex);
            b_TxEnable = Dcm_Dsl_Cnct_IsComTxEnable(u1_ComMChannel);
            if( b_TxEnable == (boolean)TRUE )
            {
                b_RetVal = (boolean)TRUE;
            }
        }
        else
        {
            /* none */
        }
    }

    return b_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_SetActiveDiagnostic                                  */
/* Description   | This function sets diag to the active state.             */
/* Preconditions | none                                                     */
/* Parameters    | [in] active :  active state                              */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : this value is always returned.             */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_SetActiveDiagnostic
(
    boolean active
)
{
    Std_ReturnType   u1_RetVal;
    uint8            u1_ActiveStatus;
    uint8            u1_ComMChannel;
    uint16           u2_PduIdxCnt;
    uint16           u2_PduIdNum;

    u1_RetVal   = E_OK;
    u2_PduIdNum = Dcm_Dsl_u2PduIdNum;

    SchM_Enter_Dcm_Dsl_CmHdl(); /* exclusion control start */

    if( active == (boolean)TRUE )
    {
        Dcm_Dsl_u1ActiveStatus = DCM_DSL_COMM_ACTIVE;
    }
    else
    {
        Dcm_Dsl_u1ActiveStatus = DCM_DSL_COMM_NOT_ACTIVE;
    }
    u1_ActiveStatus = Dcm_Dsl_u1ActiveStatus;

    if( u1_ActiveStatus == DCM_DSL_COMM_ACTIVE )
    {
        for( u2_PduIdxCnt = (uint16)0; u2_PduIdxCnt < u2_PduIdNum; u2_PduIdxCnt++ )
        {
            if( Dcm_Dsl_stComMode[Dcm_Dsl_PduIdMapTable[u2_PduIdxCnt].u2ClientIndex].bActiveIndicationFlag == (boolean)TRUE )
            {
                u1_ComMChannel = Dcm_Dsl_Ctrl_GetComMChannel(u2_PduIdxCnt);
                Dcm_Dsl_Cnct_ActiveDiagnostic(u1_ComMChannel);
            }
            else
            {
                /* none */
            }
        }
    }
    else /* DCM_DSL_COMM_NOT_ACTIVE */
    {
        for( u2_PduIdxCnt = (uint16)0; u2_PduIdxCnt < u2_PduIdNum; u2_PduIdxCnt++ )
        {
            if( Dcm_Dsl_stComMode[Dcm_Dsl_PduIdMapTable[u2_PduIdxCnt].u2ClientIndex].bActiveIndicationFlag == (boolean)TRUE )
            {
                u1_ComMChannel = Dcm_Dsl_Ctrl_GetComMChannel(u2_PduIdxCnt);
                Dcm_Dsl_Cnct_InactiveDiagnostic(u1_ComMChannel);
            }
            else
            {
                /* none */
            }
        }
    }

    SchM_Exit_Dcm_Dsl_CmHdl(); /* exclusion control stop */

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsl_CmHdl_CallActive                                 */
/* Description   | This function informs ComM of the active state of the    */
/*               | DCM.                                                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduIdMapIndex : Management number of PduId        */
/*               | [in] u1RequestActive : Requested ComM state              */
/*               | [in] bActiveClient :  Active state of the client         */
/* Return Value  | void                                                     */
/*               |         :                                                */
/* Notes         |                                                          */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_CmHdl_CallActive
(
    const uint16    u2PduIdMapIndex,
    const uint8     u1RequestActive,
    const boolean   bActiveClient
)
{
    uint8           u1_ComMChannel;
    uint8           u1_ActiveStatus;
    uint16          u2_ClientIndex;
    Dcm_SesCtrlType u1_SesStatus;
    boolean         b_ParallelActive;

    u1_SesStatus       = (Dcm_SesCtrlType)0;
    u1_ActiveStatus    = Dcm_Dsl_u1ActiveStatus;
    u2_ClientIndex     = Dcm_Dsl_PduIdMapTable[u2PduIdMapIndex].u2ClientIndex;

    SchM_Enter_Dcm_Dsl_CmHdl(); /* exclusion control start */

    if( u1RequestActive == DCM_DSL_REQ_ACTIVE )
    {
        if( u1_ActiveStatus == DCM_DSL_COMM_ACTIVE )
        {
            if( Dcm_Dsl_stComMode[u2_ClientIndex].bActiveIndicationFlag == (boolean)FALSE )
            {
                u1_ComMChannel = Dcm_Dsl_Ctrl_GetComMChannel(u2PduIdMapIndex);
                Dcm_Dsl_Cnct_ActiveDiagnostic(u1_ComMChannel);
                Dcm_Dsl_stComMode[u2_ClientIndex].bActiveIndicationFlag = (boolean)TRUE;
            }
            else
            {
                /* none */
            }
        }
        else
        {
            Dcm_Dsl_stComMode[u2_ClientIndex].bActiveIndicationFlag = (boolean)TRUE;
        }
    }
    else
    {
        if( u1_ActiveStatus == DCM_DSL_COMM_ACTIVE )
        {
            if( bActiveClient == (boolean)TRUE )
            {
                /* Return value ignoring */
                (void)Dcm_GetSesCtrlType(&u1_SesStatus);
                if( u1_SesStatus == (Dcm_SesCtrlType)DCM_DEFAULT_SESSION )
                {
                    b_ParallelActive = Dcm_Dsl_CmHdl_IsParallelActiveComMCH(u2PduIdMapIndex);
                    if( b_ParallelActive == (boolean)TRUE )
                    {
                        Dcm_Dsl_stComMode[u2_ClientIndex].bActiveIndicationFlag = (boolean)FALSE;
                    }
                    else
                    {
                        u1_ComMChannel = Dcm_Dsl_Ctrl_GetComMChannel(u2PduIdMapIndex);
                        Dcm_Dsl_Cnct_InactiveDiagnostic(u1_ComMChannel);
                        Dcm_Dsl_stComMode[u2_ClientIndex].bActiveIndicationFlag = (boolean)FALSE;
                    }
                }
                else
                {
                    /* none */
                }
            }
            else
            {
                b_ParallelActive = Dcm_Dsl_CmHdl_IsParallelActiveComMCH(u2PduIdMapIndex);
                if( b_ParallelActive == (boolean)TRUE )
                {
                    Dcm_Dsl_stComMode[u2_ClientIndex].bActiveIndicationFlag = (boolean)FALSE;
                }
                else
                {
                    u1_ComMChannel = Dcm_Dsl_Ctrl_GetComMChannel(u2PduIdMapIndex);
                    Dcm_Dsl_Cnct_InactiveDiagnostic(u1_ComMChannel);
                    Dcm_Dsl_stComMode[u2_ClientIndex].bActiveIndicationFlag = (boolean)FALSE;
                }
            }
        }
        else
        {
            if( bActiveClient == (boolean)TRUE )
            {
                /* Return value ignoring */
                (void)Dcm_GetSesCtrlType(&u1_SesStatus);
                if( u1_SesStatus == (Dcm_SesCtrlType)DCM_DEFAULT_SESSION )
                {
                    Dcm_Dsl_stComMode[u2_ClientIndex].bActiveIndicationFlag = (boolean)FALSE;
                }
                else
                {
                    /* none */
                }
            }
            else
            {
                Dcm_Dsl_stComMode[u2_ClientIndex].bActiveIndicationFlag = (boolean)FALSE;
            }
        }
    }

    SchM_Exit_Dcm_Dsl_CmHdl(); /* exclusion control stop */

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_CmHdl_CallInactiveAllCh                          */
/* Description   | This function notifies ComM that all bus channels have   */
/*               | become inactive.                                         */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_CmHdl_CallInactiveAllCh
(void)
{
    uint8   u1_ComMChannel;
    uint8   u1_ActiveStatus;
    uint16  u2_PduIdxCnt;
    uint16  u2_PduIdNum;

    u1_ActiveStatus = Dcm_Dsl_u1ActiveStatus;
    u2_PduIdNum     = Dcm_Dsl_u2PduIdNum;

    SchM_Enter_Dcm_Dsl_CmHdl(); /* exclusion control start */

    if( u1_ActiveStatus == DCM_DSL_COMM_ACTIVE )
    {
        for( u2_PduIdxCnt = (uint16)0; u2_PduIdxCnt < u2_PduIdNum; u2_PduIdxCnt++ )
        {
            if( Dcm_Dsl_stComMode[Dcm_Dsl_PduIdMapTable[u2_PduIdxCnt].u2ClientIndex].bActiveIndicationFlag == (boolean)TRUE )
            {
                u1_ComMChannel = Dcm_Dsl_Ctrl_GetComMChannel(u2_PduIdxCnt);
                Dcm_Dsl_Cnct_InactiveDiagnostic(u1_ComMChannel);
                Dcm_Dsl_stComMode[Dcm_Dsl_PduIdMapTable[u2_PduIdxCnt].u2ClientIndex].bActiveIndicationFlag = (boolean)FALSE;
            }
            else
            {
                /* none */
            }
        }
    }
    else
    {
        for( u2_PduIdxCnt = (uint16)0; u2_PduIdxCnt < u2_PduIdNum; u2_PduIdxCnt++ )
        {
            if( Dcm_Dsl_stComMode[Dcm_Dsl_PduIdMapTable[u2_PduIdxCnt].u2ClientIndex].bActiveIndicationFlag == (boolean)TRUE )
            {
                Dcm_Dsl_stComMode[Dcm_Dsl_PduIdMapTable[u2_PduIdxCnt].u2ClientIndex].bActiveIndicationFlag = (boolean)FALSE;
            }
            else
            {
                /* none */
            }
        }
    }
    SchM_Exit_Dcm_Dsl_CmHdl(); /* exclusion control stop */

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_CmHdl_Refresh                                    */
/* Description   | This function refresh ComHdl ActiveStatus.               */
/* Preconditions | The user must exclude this access data.                  */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_CmHdl_Refresh
(void)
{
    uint8 u1_ActiveStatus;
    P2VAR(volatile uint8, AUTOMATIC, DCM_APPL_DATA) pt_ActiveStatus;

    pt_ActiveStatus  = &Dcm_Dsl_u1ActiveStatus;
    u1_ActiveStatus  = *pt_ActiveStatus;
    *pt_ActiveStatus = u1_ActiveStatus;
    return ;
}
/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Dcm_Dsl_CmHdl_SetComMode                                 */
/* Description   | This function Sets ComMode.                              */
/* Preconditions | none                                                     */
/* Parameters    | [in] u1NetworkId : NetworkId(ComMChannelId)              */
/*               |                                                          */
/*               | [in] u1ComMode : DCM_DSL_COMM_NO_COMMODE                 */
/*               |                : DCM_DSL_COMM_SILENT_COMMODE             */
/*               |                : DCM_DSL_COMM_FULL_COMMODE               */
/* Return Value  | void                                                     */
/*               |         :                                                */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsl_CmHdl_SetComMode
(
    const uint8 u1NetworkId,
    const uint8 u1ComMode
)
{
    uint16  u2_PduIdxCnt;
    uint16  u2_PduIdNum;
    uint8   u1_ComMChannel;

    u2_PduIdNum = Dcm_Dsl_u2PduIdNum;

    for( u2_PduIdxCnt = (uint16)0; u2_PduIdxCnt < u2_PduIdNum; u2_PduIdxCnt++ )
    {
        u1_ComMChannel = Dcm_Dsl_Ctrl_GetComMChannel(u2_PduIdxCnt);
        if( u1NetworkId == u1_ComMChannel )
        {
            SchM_Enter_Dcm_Dsl_CmHdl(); /* exclusion control start */
            Dcm_Dsl_stComMode[Dcm_Dsl_PduIdMapTable[u2_PduIdxCnt].u2ClientIndex].u1ComModeState = u1ComMode;
            SchM_Exit_Dcm_Dsl_CmHdl();  /* exclusion control stop */
        }
        else
        {
            /* none */
        }
    }

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_CmHdl_IsParallelActiveComMCH                     */
/* Description   | This function checks for parallel use of ComChannel.     */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduIdMapIndex :                                   */
/* Return Value  | boolean                                                  */
/*               |        True : ParallelChActive                           */
/*               |        False : ParallelCh InActive                       */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(boolean, DCM_CODE) Dcm_Dsl_CmHdl_IsParallelActiveComMCH
(
    const uint16 u2PduIdMapIndex
)
{
    uint16  u2_PduIdxCnt;
    uint16  u2_ReqClieintIndex;
    uint16  u2_CompClientIndex;
    uint16  u2_PduIdNum;
    uint8  u1_ReqComMChannel;
    uint8  u1_CompComMChannel;
    boolean b_Result;

    u2_PduIdNum       = Dcm_Dsl_u2PduIdNum;
    b_Result          = (boolean)FALSE;
    u1_ReqComMChannel = Dcm_Dsl_Ctrl_GetComMChannel(u2PduIdMapIndex);

    for( u2_PduIdxCnt = (uint16)0U; u2_PduIdxCnt < u2_PduIdNum; u2_PduIdxCnt++ )
    {
        u2_CompClientIndex = Dcm_Dsl_PduIdMapTable[u2_PduIdxCnt].u2ClientIndex;
        u2_ReqClieintIndex = Dcm_Dsl_PduIdMapTable[u2PduIdMapIndex].u2ClientIndex;
        if( u2_CompClientIndex != u2_ReqClieintIndex )
        {
            u1_CompComMChannel = Dcm_Dsl_Ctrl_GetComMChannel(u2_PduIdxCnt);
            if( u1_CompComMChannel == u1_ReqComMChannel )
            {
                if( Dcm_Dsl_stComMode[u2_CompClientIndex].bActiveIndicationFlag == (boolean)TRUE )
                {
                    b_Result = (boolean)TRUE;
                    break;
                }
            }
        }
    }

    return b_Result;
}

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-07-27                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v5-0-0         :2022-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
