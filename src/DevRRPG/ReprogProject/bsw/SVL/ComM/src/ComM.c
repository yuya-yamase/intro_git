/* ComM_c_Revision(v3.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | ComM/CODE                                                   */
/******************************************************************************/

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <ComM.h>
#include <ComM_BusSM.h>
#include <EcuM.h>
#include <CanSM_ComM.h>
#if (REPROG_CFG_ETH_USE == STD_ON)
#include <Sys.h>
#include <EthSM.h>
#include <BswM.h>
#include <Tm.h>
#endif
#if (REPROG_CFG_CXPI_USE == STD_ON)
#include <CxpiWrap_FarcallWrapper.h>
#endif


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define COMM_MAXNETWORK_NUM (16U)

#define COMM_UNINIT         ((uint8)0x00U)
#define COMM_INIT           ((uint8)0x01U)

#if (REPROG_CFG_ETH_USE == STD_ON)
#define COMM_SENDRCV_IDLE           ((ComM_SendRcvStatusType)0x00U)
#define COMM_SENDRCV_WAITCOMSTART   ((ComM_SendRcvStatusType)0x11U)
#define COMM_SENDRCV_WAITSTART      ((ComM_SendRcvStatusType)0x22U)
#define COMM_SENDRCV_STARTED        ((ComM_SendRcvStatusType)0x33U)
#define COMM_SENDRCV_REQSTOP        ((ComM_SendRcvStatusType)0x44U)
#define COMM_SENDRCV_WAITSTOP       ((ComM_SendRcvStatusType)0x55U)
#define COMM_SENDRCV_STOPPED        ((ComM_SendRcvStatusType)0x66U)
#endif


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef uint8 ComM_InitStatusType;

#if (REPROG_CFG_ETH_USE == STD_ON)
typedef uint8 ComM_SendRcvStatusType;
#endif


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
static FUNC(void, COMM_CODE_FAST) ComM_ReportError
(
    VAR(uint8, AUTOMATIC) ApiId,
    VAR(uint8, AUTOMATIC) ErrorId
);
#if (REPROG_CFG_ETH_USE == STD_ON)
static FUNC(Std_ReturnType, COMM_CODE_FAST) ComM_EthRequestComMode
(
    VAR(NetworkHandleType, AUTOMATIC) NetworkId,
    VAR(ComM_ModeType, AUTOMATIC) ComMode
);
#endif


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define COMM_START_SEC_VAR
#include <ComM_MemMap.h>

static VAR(ComM_InitStatusType, COMM_VAR_CLEARED) ComM_InitStatus;
static VAR(ComM_ModeType, COMM_VAR_CLEARED) ComM_NetworkMode[COMM_MAXNETWORK_NUM];
#if (REPROG_CFG_ETH_USE == STD_ON)
static VAR(uint32, COMM_VAR_CLEARED) ComM_SendRcvStartWaitCounter;
static VAR(Tm_PredefTimer1us32bitType, COMM_VAR_CLEARED) ComM_SendRcvStopTimerInst;
static VAR(Tm_PredefTimer1us32bitType, COMM_VAR_CLEARED) ComM_SendRcvComStartTimerInst;
static VAR(ComM_SendRcvStatusType, COMM_VAR_CLEARED) ComM_SendRcvStatus;
static VAR(uint8, COMM_VAR_CLEARED) ComM_FullComRequestedFlg;
#endif

#define COMM_STOP_SEC_VAR
#include <ComM_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define COMM_START_SEC_CST
#include <ComM_MemMap.h>


#define COMM_STOP_SEC_CST
#include <ComM_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define COMM_START_SEC_CODE
#include <ComM_MemMap.h>

/******************************************************************************/
/* Function Name | ComM_Init                                                  */
/* Description   | Initializes the Communication Manager and restarts         */
/*               | the internal state machines                                */
/* Preconditions |                                                            */
/* Parameters    | [IN]ConfigPtr : ComM Configuration Table                   */
/* Return Value  | NONE                                                       */
/* Notes         | NONE                                                       */
/******************************************************************************/
FUNC(void, COMM_CODE_SLOW) ComM_Init
(
    P2CONST(ComM_ConfigType, AUTOMATIC, COMM_APPL_CONST) ConfigPtr
)
{
    VAR(uint32, AUTOMATIC) NetworkIndex;

    if( ComM_InitStatus == COMM_UNINIT )
    {
        if( ConfigPtr == &ComM_Cfg_Data )
        {
            for( NetworkIndex = 0UL; NetworkIndex < (uint32)COMM_MAXNETWORK_NUM; NetworkIndex++ )
            {
                ComM_NetworkMode[NetworkIndex] = COMM_NO_COMMUNICATION;
            }

#if (REPROG_CFG_ETH_USE == STD_ON)
            ComM_SendRcvStatus = COMM_SENDRCV_IDLE;
            ComM_SendRcvStartWaitCounter = 0UL;
            ComM_SendRcvStopTimerInst.StartPoint = 0UL;
            ComM_SendRcvComStartTimerInst.StartPoint = 0UL;
            ComM_FullComRequestedFlg = STD_OFF;
#endif

            ComM_InitStatus = COMM_INIT;
        }
        else
        {
            ComM_ReportError(COMM_API_ID_INIT, COMM_E_PARAM_POINTER);
        }
    }
    else
    {
        ComM_ReportError(COMM_API_ID_INIT, COMM_E_STATUS);
    }

    return;
}

/******************************************************************************/
/* Function Name | ComM_DeInit                                                */
/* Description   | This API de-initializes the Communication Manager          */
/* Preconditions |                                                            */
/* Parameters    | NONE                                                       */
/* Return Value  | NONE                                                       */
/* Notes         | NONE                                                       */
/******************************************************************************/
FUNC(void, COMM_CODE_SLOW) ComM_DeInit (void)
{
    VAR(uint32, AUTOMATIC) NetworkIndex;

    ComM_InitStatus = COMM_UNINIT;

    for( NetworkIndex = 0UL; NetworkIndex < (uint32)COMM_MAXNETWORK_NUM; NetworkIndex++ )
    {
        ComM_NetworkMode[NetworkIndex] = COMM_NO_COMMUNICATION;
    }

#if (REPROG_CFG_ETH_USE == STD_ON)
    ComM_SendRcvStatus = COMM_SENDRCV_IDLE;
    ComM_SendRcvStartWaitCounter = 0UL;
    ComM_SendRcvStopTimerInst.StartPoint = 0UL;
    ComM_SendRcvComStartTimerInst.StartPoint = 0UL;
    ComM_FullComRequestedFlg = STD_OFF;
#endif

    return;
}

/******************************************************************************/
/* Function Name | ComM_RequestComMode                                        */
/* Description   | Requesting of a Communication Mode by a user               */
/* Preconditions |                                                            */
/* Parameters    | [IN]User    : User Identifier                              */
/*               | [IN]ComMode : Communication Mode                           */
/* Return Value  | Status                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | This function is called by Base Context only when          */
/*               | REPROG_CFG_CAN_DISABLE is not STD_ON (CAN enabled) or      */
/*               | REPROG_CFG_CXPI_USE is STD_ON (CXPI enabled).              */
/******************************************************************************/
FUNC(Std_ReturnType, COMM_CODE_SLOW) ComM_RequestComMode
(
    VAR(ComM_UserHandleType, AUTOMATIC) User,
    VAR(ComM_ModeType, AUTOMATIC) ComMode
)
{
    VAR(Std_ReturnType, AUTOMATIC) Result;
    VAR(Std_ReturnType, AUTOMATIC) FuncReturn;
    VAR(uint8, AUTOMATIC) NetworkIndex;
    VAR(NetworkHandleType, AUTOMATIC) CfgNetworkId;
#if (REPROG_CFG_ETH_USE == STD_ON)
    VAR(uint8, AUTOMATIC) MaskLevel;
#endif

    Result = E_NOT_OK;

#if (REPROG_CFG_ETH_USE == STD_ON)
    MaskLevel = MaskInterruptAll();
#endif

    if( ComM_InitStatus == COMM_INIT )
    {
        if( User == COMM_USER_ID_0 )
        {
            if( ( ComMode == COMM_FULL_COMMUNICATION ) || ( ComMode == COMM_NO_COMMUNICATION ) )
            {
                Result = E_OK;
                for( NetworkIndex = 0U; NetworkIndex < ComM_Cfg_Data.NetworkInfoTbl->NetworkNum; NetworkIndex++ )
                {
                    CfgNetworkId = ComM_Cfg_Data.NetworkInfoTbl->NetworkSettingTbl[NetworkIndex].NetworkId;
                    if( ComM_NetworkMode[CfgNetworkId] != ComMode )
                    {
#if (REPROG_CFG_ETH_USE == STD_ON)
                        FuncReturn = ComM_EthRequestComMode(CfgNetworkId, ComMode);
#elif (REPROG_CFG_CXPI_USE == STD_ON)
                        FuncReturn = CxpiWrap_ComMRequestComMode((uint8)CfgNetworkId, (uint8)ComMode);
#else
                        FuncReturn = CanSM_RequestComMode(CfgNetworkId, ComMode);
#endif

                        if( FuncReturn == (Std_ReturnType)E_OK )
                        {
                            ComM_NetworkMode[CfgNetworkId] = ComMode;
                        }
                        else
                        {
                            Result = E_NOT_OK;
                            break;
                        }
                    }
                }

#if (REPROG_CFG_ETH_USE == STD_ON)
                if( Result == (Std_ReturnType)E_OK )
                {
                    if( ComMode == COMM_FULL_COMMUNICATION )
                    {
                        ComM_SendRcvStatus = COMM_SENDRCV_WAITCOMSTART;
                    }
                    else
                    {
                        if( ComM_SendRcvStatus == COMM_SENDRCV_STARTED )
                        {
                            ComM_SendRcvStatus = COMM_SENDRCV_REQSTOP;
                        }
                        else if( ( ComM_SendRcvStatus == COMM_SENDRCV_IDLE ) ||
                                 ( ComM_SendRcvStatus == COMM_SENDRCV_WAITCOMSTART ) ||
                                 ( ComM_SendRcvStatus == COMM_SENDRCV_WAITSTART ) )
                        {
                            Result = E_NOT_OK;
                        }
                        else
                        {
                            /* No process */
                        }
                    }
                }
#endif
            }
        }
    }

#if (REPROG_CFG_ETH_USE == STD_ON)
    UnMaskInterruptAll(MaskLevel);
#endif

    return Result;
}

/******************************************************************************/
/* Function Name | ComM_BusSM_ModeIndication                                  */
/* Description   | Indication of the actual bus mode by the corresponding Bus */
/*               | State Manager                                              */
/* Preconditions |                                                            */
/* Parameters    | [IN]Channel : Network Identifier                           */
/*               | [IN]ComMode : Pointer to Communication Mode                */
/* Return Value  | NONE                                                       */
/* Notes         | - This function is called by Base Context only when        */
/*               |   REPROG_CFG_CAN_DISABLE is not STD_ON (CAN enabled).      */
/*               | - This function is called by Interrupt Context only when   */
/*               |   REPROG_CFG_ETH_USE is STD_ON (Ether enabled).            */
/******************************************************************************/
FUNC(void, COMM_CODE_SLOW) ComM_BusSM_ModeIndication
(
    VAR(NetworkHandleType, AUTOMATIC) Channel,
    P2CONST(ComM_ModeType, AUTOMATIC, COMM_APPL_CONST) ComMode
)
{
    VAR(Std_ReturnType, AUTOMATIC) Result;
    VAR(uint8, AUTOMATIC) ErrorId;
    VAR(uint8, AUTOMATIC) NetworkIndex;
    VAR(NetworkHandleType, AUTOMATIC) CfgNetworkId;
#if (REPROG_CFG_ETH_USE == STD_ON)
    VAR(uint8, AUTOMATIC) FullComFlg;
#endif

    Result = E_NOT_OK;
    ErrorId = COMM_E_NOT_INITED;

    if( ComM_InitStatus == COMM_INIT )
    {
        if( ComMode != NULL_PTR )
        {
            if( ( *ComMode == COMM_FULL_COMMUNICATION ) || ( *ComMode == COMM_NO_COMMUNICATION ) )
            {
                for( NetworkIndex = 0U; NetworkIndex < ComM_Cfg_Data.NetworkInfoTbl->NetworkNum; NetworkIndex++ )
                {
                    CfgNetworkId = ComM_Cfg_Data.NetworkInfoTbl->NetworkSettingTbl[NetworkIndex].NetworkId;
                    if( Channel == CfgNetworkId )
                    {
                        ComM_NetworkMode[CfgNetworkId] = *ComMode;
                        Result = E_OK;
                        break;
                    }
                }

                if( Result != (Std_ReturnType)E_OK )
                {
                    ErrorId = COMM_E_WRONG_PARAMETERS;
                }
            }
            else
            {
                ErrorId = COMM_E_WRONG_PARAMETERS;
            }
        }
        else
        {
            ErrorId = COMM_E_PARAM_POINTER;
        }
    }

    if( Result != (Std_ReturnType)E_OK )
    {
        ComM_ReportError(COMM_API_ID_BUSSM_MODEINDICATION, ErrorId);
    }
#if (REPROG_CFG_ETH_USE == STD_ON)
    else
    {
        if( *ComMode == COMM_NO_COMMUNICATION )
        {
            FullComFlg = STD_OFF;
            for( NetworkIndex = 0U; NetworkIndex < ComM_Cfg_Data.NetworkInfoTbl->NetworkNum; NetworkIndex++ )
            {
                CfgNetworkId = ComM_Cfg_Data.NetworkInfoTbl->NetworkSettingTbl[NetworkIndex].NetworkId;
                if( ComM_NetworkMode[CfgNetworkId] != COMM_NO_COMMUNICATION )
                {
                    FullComFlg = STD_ON;
                    break;
                }
            }

            if( FullComFlg != (uint8)STD_ON )
            {
                if( ComM_SendRcvStatus == COMM_SENDRCV_WAITSTOP )
                {
                    ComM_SendRcvStatus = COMM_SENDRCV_STOPPED;
                    BswM_RequestMode(BSWM_USER_COMM_ETH_SENDRCV, BSWM_MODE_ETH_SENDRCV_STOP);
                }
            }
        }
    }
#endif

    return;
}

#if (REPROG_CFG_ETH_USE == STD_ON)
/******************************************************************************/
/* Function Name | ComM_CommunicationAllowed                                  */
/* Description   | Indicate that Communication is allowed or not allowed      */
/* Preconditions |                                                            */
/* Parameters    | [IN]Channel : Network Identifier                           */
/*               | [IN]Allowed : Communication is allowed or not allowed      */
/* Return Value  | NONE                                                       */
/* Notes         | NONE                                                       */
/******************************************************************************/
FUNC(void, COMM_CODE_SLOW) ComM_CommunicationAllowed
(
    VAR(NetworkHandleType, AUTOMATIC) Channel,
    VAR(boolean, AUTOMATIC) Allowed
)
{
    ;   /* No process */
}

/******************************************************************************/
/* Function Name | ComM_NotifyCommunicationStart                              */
/* Description   | Notify that Communication(Send and Receive) is started     */
/* Preconditions |                                                            */
/* Parameters    | NONE                                                       */
/* Return Value  | NONE                                                       */
/* Notes         | NONE                                                       */
/******************************************************************************/
FUNC(void, COMM_CODE_SLOW) ComM_NotifyCommunicationStart (void)
{
    if( ComM_SendRcvStatus == COMM_SENDRCV_WAITCOMSTART )
    {
        ComM_SendRcvStatus = COMM_SENDRCV_WAITSTART;
        ComM_SendRcvStartWaitCounter = 0UL;
    }

    return;
}

/******************************************************************************/
/* Function Name | ComM_Time                                                  */
/* Description   | TimeFunction                                               */
/* Preconditions |                                                            */
/* Parameters    | NONE                                                       */
/* Return Value  | NONE                                                       */
/* Notes         | NONE                                                       */
/******************************************************************************/
FUNC(void, COMM_CODE_SLOW) ComM_Time (void)
{
    VAR(uint32, AUTOMATIC) TimeSpan;
    VAR(uint8, AUTOMATIC) NetworkIndex;
    VAR(NetworkHandleType, AUTOMATIC) CfgNetworkId;
    VAR(Std_ReturnType, AUTOMATIC) TmReturn;
    VAR(Std_ReturnType, AUTOMATIC) EthReturn;
    VAR(uint8, AUTOMATIC) ErrFlg;

    ErrFlg = STD_OFF;

    if( ComM_SendRcvStatus == COMM_SENDRCV_WAITCOMSTART )
    {
        TimeSpan = 0UL;
        TmReturn = Tm_GetTimeSpan1us32bit((const Tm_PredefTimer1us32bitType*)&ComM_SendRcvComStartTimerInst, &TimeSpan);
        if( TmReturn == (Std_ReturnType)E_OK )
        {
            if( TimeSpan >= ComM_Cfg_Data.TimerData->SendRcvComStartTimeout )
            {
                ComM_ReportError(COMM_API_ID_COMM_TIME, COMM_E_TIMEOUT);
                ComM_SendRcvStatus = COMM_SENDRCV_STOPPED;
            }
        }
        else
        {
            ComM_ReportError(COMM_API_ID_COMM_TIME, COMM_E_TIMEOUT);
            ComM_SendRcvStatus = COMM_SENDRCV_STOPPED;
        }
    }
    else if( ComM_SendRcvStatus == COMM_SENDRCV_WAITSTART )
    {
        if( ComM_SendRcvStartWaitCounter < ComM_Cfg_Data.TimerData->SendRcvStartWaitCount )
        {
            ComM_SendRcvStartWaitCounter++;
        }
        else
        {
            BswM_RequestMode(BSWM_USER_COMM_ETH_SENDRCV, BSWM_MODE_ETH_SENDRCV_START);
            ComM_SendRcvStatus = COMM_SENDRCV_STARTED;
        }
    }
    else if( ComM_SendRcvStatus == COMM_SENDRCV_REQSTOP )
    {
        TmReturn = Tm_ResetTimer1us32bit(&ComM_SendRcvStopTimerInst);
        if(TmReturn == (Std_ReturnType)E_OK)
        {
            for( NetworkIndex = 0U; NetworkIndex < ComM_Cfg_Data.NetworkInfoTbl->NetworkNum; NetworkIndex++ )
            {
                CfgNetworkId = ComM_Cfg_Data.NetworkInfoTbl->NetworkSettingTbl[NetworkIndex].NetworkId;

                EthReturn = EthSM_RequestComMode(CfgNetworkId,COMM_NO_COMMUNICATION);
                if(EthReturn == (Std_ReturnType)E_OK)
                {
                    ComM_SendRcvStatus = COMM_SENDRCV_WAITSTOP;
                }
                else
                {
                    ErrFlg = STD_ON;
                    break;
                }
            }
        }
        else
        {
            ErrFlg = STD_ON;
        }
    }
    else if( ComM_SendRcvStatus == COMM_SENDRCV_WAITSTOP )
    {
        TimeSpan = 0UL;
        TmReturn = Tm_GetTimeSpan1us32bit((const Tm_PredefTimer1us32bitType*)&ComM_SendRcvStopTimerInst, &TimeSpan);
        if( TmReturn == (Std_ReturnType)E_OK )
        {
            if( TimeSpan >= ComM_Cfg_Data.TimerData->SendRcvStopTimeout )
            {
                ErrFlg = STD_ON;
            }
        }
        else
        {
            ErrFlg = STD_ON;
        }
    }
    else
    {
        /* No process */
    }

    if( ErrFlg == (uint8)STD_ON )
    {
        BswM_RequestMode(BSWM_USER_COMM_ETH_SENDRCV, BSWM_MODE_ETH_SENDRCV_STOP);
        ComM_SendRcvStatus = COMM_SENDRCV_STOPPED;
    }

    return;
}
#endif


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/
/******************************************************************************/
/* Function Name | ComM_ReportError                                           */
/* Description   | Notified of the error information                          */
/* Preconditions |                                                            */
/* Parameters    | [IN] ApiId   : Api ID                                      */
/*               | [IN] ErrorId : Error ID                                    */
/* Return Value  | NONE                                                       */
/* Notes         | NONE                                                       */
/******************************************************************************/
static FUNC(void, COMM_CODE_FAST) ComM_ReportError
(
    VAR(uint8, AUTOMATIC) ApiId,
    VAR(uint8, AUTOMATIC) ErrorId
)
{
    VAR(EcuM_ErrorType, AUTOMATIC) ErrorInfo;

    ErrorInfo.ModuleId = ECUM_MODULE_COMM;
    ErrorInfo.ApiId = ApiId;
    ErrorInfo.ErrorId = ErrorId;
    EcuM_ReportError(&ErrorInfo);

    return;
}

#if (REPROG_CFG_ETH_USE == STD_ON)
/******************************************************************************/
/* Function Name | ComM_EthRequestComMode                                     */
/* Description   | Requesting of a Communication Mode for Ethernet            */
/* Preconditions |                                                            */
/* Parameters    | [IN]  NetworkId : Network Identifier                       */
/*               | [IN]  ComMode   : Communication Mode                       */
/* Return Value  | Status                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | NONE                                                       */
/******************************************************************************/
static FUNC(Std_ReturnType, COMM_CODE_FAST) ComM_EthRequestComMode
(
    VAR(NetworkHandleType, AUTOMATIC) NetworkId,
    VAR(ComM_ModeType, AUTOMATIC) ComMode
)
{
    VAR(Std_ReturnType, AUTOMATIC) FuncReturn;
    VAR(Std_ReturnType, AUTOMATIC) TmReturn;
    VAR(Std_ReturnType, AUTOMATIC) Result;

    Result = E_NOT_OK;
    if( ComMode == COMM_FULL_COMMUNICATION )
    {
        if( ComM_FullComRequestedFlg == (uint8)STD_ON )
        {
            FuncReturn = EthSM_RequestComMode(NetworkId, ComMode);
            if( FuncReturn == (Std_ReturnType)E_OK )
            {
                Result = E_OK;
            }
        }
        else
        {
            TmReturn = Tm_ResetTimer1us32bit(&ComM_SendRcvComStartTimerInst);
            if( TmReturn == (Std_ReturnType)E_OK )
            {
                FuncReturn = EthSM_RequestComMode(NetworkId, ComMode);
                if( FuncReturn == (Std_ReturnType)E_OK )
                {
                    ComM_FullComRequestedFlg = STD_ON;
                    Result = E_OK;
                }
            }
        }
    }
    else /* COMM_NO_COMMUNICATION */
    {
        Result = E_OK;
    }

    return Result;
}
#endif

#define COMM_STOP_SEC_CODE
#include <ComM_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2018/06/19 :Update                                rel.AUBASS */
/*  v3.00       :2021/09/14 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/**** End of File *************************************************************/

