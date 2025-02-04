/* CanSM_c_Revision(v3.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | CanSM/CODE                                                  */
/******************************************************************************/

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <CanSM.h>
#include <CanSM_BswM.h>
#include <CanSM_ComM.h>
#include <CanSM_Cbk.h>
#include <CanIf.h>
#include <ComM_BusSM.h>
#include <Tm.h>
#include <EcuM.h>
#include <Sys.h>
#include <BswM_CanSM.h>
#include <UsrSoftIf.h>
#include <ReprogOpt.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define CANSM_MAXCONTROLLER_NUM          ((uint8)16U)

#define CANSM_NETWORKID_INVALID          (0xFFU)

#define CANSM_UNINITED                   ((uint8)0x00U)
#define CANSM_INITED                     ((uint8)0x01U)

#define CANSM_BSM_S_NOT_INITIALIZED      ((uint8)0x00U)
#define CANSM_BSM_S_PRE_NOCOM            ((uint8)0x01U)
#define CANSM_BSM_S_NOCOM                ((uint8)0x02U)
#define CANSM_BSM_S_PRE_FULLCOM          ((uint8)0x03U)
#define CANSM_BSM_S_FULLCOM              ((uint8)0x04U)
#define CANSM_BSM_S_CHANGE_BAUDRATE      ((uint8)0x05U)

#define CANSM_S_CC_STOPPED               ((uint8)0x00U)
#define CANSM_S_CC_STOPPED_WAIT          ((uint8)0x01U)
#define CANSM_S_CC_STARTED               ((uint8)0x02U)
#define CANSM_S_CC_STARTED_WAIT          ((uint8)0x03U)

#define CANSM_SETMODE_OK                 ((uint8)0x00U)
#define CANSM_SETMODE_PENDING            ((uint8)0x01U)
#define CANSM_SETMODE_NOT_OK             ((uint8)0x02U)

#define CANSM_API_ID_INIT                (0x00U)
#define CANSM_API_ID_REQCOMMODE          (0x01U)
#define CANSM_API_ID_CONTROLLERMODEIND   (0x02U)
#define CANSM_API_ID_MAINFUNCTION        (0x03U)

#define CANSM_E_UNINIT                   (0x00U)
#define CANSM_E_PARAM_POINTER            (0x01U)
#define CANSM_E_PARAM_CONTROLLER         (0x02U)
#define CANSM_E_STATUS                   (0x03U)
#define CANSM_E_PRENOCOM_STS_HANDLE      (0x04U)
#define CANSM_E_PREFULLCOM_STS_HANDLE    (0x05U)
#define CANSM_E_BAUDRATE_STS_HANDLE      (0x06U)
#define CANSM_E_GET_BAUDRATE_CFG_ID      (0x07U)

#define CANSM_MAXTIMESPAN                (0xFFFFFFFFUL)

#define CANSM_MSEC_TO_USEC               (1000UL)

#define CANSM_FIRSTMODEREQUEST_NUM       ((uint16)1U)

#define CANSM_LINKCTRL_TYPE1             ((uint8)0x01U)
#define CANSM_LINKCTRL_TYPE2             ((uint8)0x02U)

#define CANSM_ENTRYPRM_IDX_CANID_HIGH    (1U)

#define CANSM_ENTRYPRM_IDX_BAUDRATE_HIGH (14U)
#define CANSM_ENTRYPRM_IDX_BAUDRATE_MID  (15U)
#define CANSM_ENTRYPRM_IDX_BAUDRATE_LOW  (16U)

#define CANSM_LINKREC_HIGH_POS           (0U)
#define CANSM_LINKREC_MID_POS            (1U)
#define CANSM_LINKREC_LOW_POS            (2U)

#define CANSM_BPS_TO_KBPS                ((uint32)1000UL)

/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef uint8 CanSM_StateType;
typedef uint8 CanSM_BSMStateType;
typedef uint8 CanSM_BSMSubStateType;
typedef uint8 CanSM_SetModeResultType;

typedef struct {
    Tm_PredefTimer1us32bitType TimerInstance;
    uint16 ModeRequestCnt;
    NetworkHandleType NetworkId;
    uint8 BaudRateConfigIDFlg;
    uint16 BaudRateConfigID;
    CanSM_BSMStateType CanSMState;
    CanSM_BSMSubStateType CanSMSubState;
} CanSM_NetworkMngType;

typedef struct {
    CanSM_SetModeResultType SetModeResult;
    CanIf_ControllerModeType CurrentControllerMode;
    CanIf_ControllerModeType RequestedControllerMode;
} CanSM_ControllerMngType;

typedef struct {
    uint32 Baudrate;
    uint8  linkControlModeIdentifier;
} CanSM_BaudrateMatrixType;


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
static FUNC(Std_ReturnType, CANSM_CODE_FAST) CanSM_SetControllerModePerNetwork
(
    VAR(uint8, AUTOMATIC) NetworkIndex,
    VAR(CanIf_ControllerModeType, AUTOMATIC) ControllerMode
);

static FUNC(CanSM_SetModeResultType, CANSM_CODE_FAST) CanSM_CheckControllerModeIndication
(
    VAR(uint8, AUTOMATIC) NetworkIndex
);

static FUNC(Std_ReturnType, CANSM_CODE_FAST) CanSM_RepetitionTimeHandle
(
    VAR(uint8, AUTOMATIC) NetworkIndex
);

static FUNC(Std_ReturnType, CANSM_CODE_FAST) CanSM_PreNoComStsHandle
(
    VAR(uint8, AUTOMATIC) NetworkIndex
);

static FUNC(Std_ReturnType, CANSM_CODE_FAST) CanSM_PreFullComStsHandle
(
    VAR(uint8, AUTOMATIC) NetworkIndex
);

static FUNC(void, CANSM_CODE_FAST) CanSM_ReportError
(
    VAR(uint8, AUTOMATIC) ApiId,
    VAR(uint8, AUTOMATIC) ErrorId
);

static FUNC(Std_ReturnType, CANSM_CODE_FAST) CanSM_SetBaudrateStsHandle
(
    VAR(uint8, AUTOMATIC) NetworkIndex
);

static FUNC(uint8, CANSM_CODE_FAST) CanSM_GetNetworkIdOfCanId
(
    VAR(uint32, AUTOMATIC) CanId
);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define CANSM_START_SEC_VAR
#include <CanSM_MemMap.h>

static VAR(CanSM_NetworkMngType, CANSM_VAR_CLEARED) CanSM_NetworkMng_Data[CANSM_MAXNETWORK_NUM];
static VAR(uint32, CANSM_VAR_CLEARED) CanSM_ModeRequestWaitTime;
static VAR(uint16, CANSM_VAR_CLEARED) CanSM_ModeRequestCntMax;
static VAR(CanSM_ControllerMngType, CANSM_VAR_CLEARED) CanSM_ControllerMng_Data[CANSM_MAXCONTROLLER_NUM];
static VAR(CanSM_StateType, CANSM_VAR_CLEARED) CanSM_InitState;

#define CANSM_STOP_SEC_VAR
#include <CanSM_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define CANSM_START_SEC_CST
#include <CanSM_MemMap.h>

static CONST(AB_83_ConstV CanSM_BaudrateMatrixType, CANSM_CONST) CanSM_BaudrateMatrixTbl[] = {
     { 125UL,   0x10U }
    ,{ 250UL,   0x11U }
    ,{ 500UL,   0x12U }
    ,{ 1000UL,  0x13U }
};
static CONST(AB_83_ConstV uint8, CANSM_CONST) CanSM_BaudrateMatrixTblNum = (sizeof(CanSM_BaudrateMatrixTbl) / sizeof(CanSM_BaudrateMatrixTbl[0]));

#define CANSM_STOP_SEC_CST
#include <CanSM_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define CANSM_START_SEC_CODE
#include <CanSM_MemMap.h>

/******************************************************************************/
/* Function Name | CanSM_Init                                                 */
/* Description   | This service initializes the CanSM module                  */
/* Preconditions |                                                            */
/* Parameters    | [IN]ConfigPtr : Pointer to CanSM Configuration Data        */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, CANSM_CODE_SLOW) CanSM_Init
(
    P2CONST(CanSM_ConfigType, AUTOMATIC, CANSM_APPL_CONST) ConfigPtr
)
{
    P2CONST(UsrSoftIf_EntryParamType, AUTOMATIC, CANSM_APPL_CONST) EntryParamPtr;
    VAR(uint8, AUTOMATIC) NetworkIndex;
    VAR(uint8, AUTOMATIC) ControllerIndex;
    VAR(uint8, AUTOMATIC) BootMode;
    VAR(ComM_ModeType, AUTOMATIC) ComMode;
    VAR(Tm_PredefTimer1us32bitType, AUTOMATIC) Timer;
    VAR(uint16, AUTOMATIC) BaudRateConfigID;
    VAR(CanSM_BaudrateInfoType, AUTOMATIC) BaudrateInfo;
    VAR(Std_ReturnType, AUTOMATIC) Result;
    VAR(uint32, AUTOMATIC) CanId;
    VAR(uint8, AUTOMATIC) NetworkId;

    if( ReprogOpt_CanDisableConfig == (uint8)STD_ON )
    {
        /* No process */
    }
    else if( CanSM_InitState == CANSM_UNINITED )
    {
        if( ConfigPtr == &CanSM_Cfg_Data )
        {
            BootMode = EcuM_GetBootMode();
            Result = (Std_ReturnType)E_NOT_OK;
            if( BootMode == ECUM_START_AP_ENTRY )
            {
                EntryParamPtr = UsrSoftIf_GetEntryParam();
                if( EntryParamPtr != NULL_PTR )
                {
                    /* Get NetworkId from CanId of EntryParam */
                    CanId = Rpg_ByteCombine(
                        &EntryParamPtr->EntryParam[CANSM_ENTRYPRM_IDX_CANID_HIGH],
                        (uint8)sizeof(CanId));
                    NetworkId = CanSM_GetNetworkIdOfCanId(CanId);

                    /* Get BaudRateConfigID from BaudrateInfo of EntryParam */
                    if( ( EntryParamPtr->EntryParam[CANSM_ENTRYPRM_IDX_BAUDRATE_HIGH] != (uint8)0U ) ||
                        ( EntryParamPtr->EntryParam[CANSM_ENTRYPRM_IDX_BAUDRATE_MID] != (uint8)0U ) ||
                        ( EntryParamPtr->EntryParam[CANSM_ENTRYPRM_IDX_BAUDRATE_LOW] != (uint8)0U ) )
                    {
                        BaudRateConfigID = 0U;
                        BaudrateInfo.linkControlType = CANSM_LINKCTRL_TYPE2;
                        BaudrateInfo.linkControlModeIdentifier = 0U;
                        BaudrateInfo.linkRecord[CANSM_LINKREC_HIGH_POS] =
                            EntryParamPtr->EntryParam[CANSM_ENTRYPRM_IDX_BAUDRATE_HIGH];
                        BaudrateInfo.linkRecord[CANSM_LINKREC_MID_POS] =
                            EntryParamPtr->EntryParam[CANSM_ENTRYPRM_IDX_BAUDRATE_MID];
                        BaudrateInfo.linkRecord[CANSM_LINKREC_LOW_POS] =
                            EntryParamPtr->EntryParam[CANSM_ENTRYPRM_IDX_BAUDRATE_LOW];
                        Result = CanSM_GetBaudrateConfigId(&BaudrateInfo, &BaudRateConfigID);
                        if( Result != (Std_ReturnType)E_OK )
                        {
                            CanSM_ReportError(CANSM_API_ID_INIT, CANSM_E_GET_BAUDRATE_CFG_ID);
                        }
                    }
                }
            }
            for( NetworkIndex = 0U; NetworkIndex < CANSM_MAXNETWORK_NUM; NetworkIndex++ )
            {
                CanSM_NetworkMng_Data[NetworkIndex].NetworkId = CANSM_NETWORKID_INVALID;
                CanSM_NetworkMng_Data[NetworkIndex].BaudRateConfigIDFlg = (uint8)STD_OFF;
                CanSM_NetworkMng_Data[NetworkIndex].BaudRateConfigID = 0U;
                if( NetworkIndex < CanSM_Cfg_Data.NetworkInfoTbl->NetworkNum )
                {
                    CanSM_NetworkMng_Data[NetworkIndex].NetworkId =
                        CanSM_Cfg_Data.NetworkInfoTbl->NetworkSettingTbl[NetworkIndex].NetworkId;
                    CanSM_NetworkMng_Data[NetworkIndex].ModeRequestCnt = 0U;
                    CanSM_NetworkMng_Data[NetworkIndex].CanSMState = CANSM_BSM_S_NOCOM;
                    CanSM_NetworkMng_Data[NetworkIndex].CanSMSubState = CANSM_S_CC_STOPPED;
                    Timer.StartPoint = 0UL;
                    CanSM_NetworkMng_Data[NetworkIndex].TimerInstance = Timer;

                    ComMode = COMM_NO_COMMUNICATION;

                    ComM_BusSM_ModeIndication(
                        CanSM_NetworkMng_Data[NetworkIndex].NetworkId,
                        &ComMode);
                    if( ( Result == (Std_ReturnType)E_OK ) &&
                        ( NetworkId == CanSM_NetworkMng_Data[NetworkIndex].NetworkId ) )
                    {
                        CanSM_NetworkMng_Data[NetworkIndex].BaudRateConfigIDFlg = (uint8)STD_ON;
                        CanSM_NetworkMng_Data[NetworkIndex].BaudRateConfigID = BaudRateConfigID;
                    }
                }

            }

            for( ControllerIndex = 0U; ControllerIndex < CANSM_MAXCONTROLLER_NUM; ControllerIndex++ )
            {
                CanSM_ControllerMng_Data[ControllerIndex].SetModeResult = CANSM_SETMODE_OK;
                CanSM_ControllerMng_Data[ControllerIndex].CurrentControllerMode = CANIF_CS_STOPPED;
                CanSM_ControllerMng_Data[ControllerIndex].RequestedControllerMode = CANIF_CS_STOPPED;
            }
            CanSM_ModeRequestWaitTime = (uint32)CanSM_Cfg_Data.NetworkInfoTbl->ModeRequestRepetitionTime * CANSM_MSEC_TO_USEC;  /* no wrap around */
            CanSM_ModeRequestCntMax = (uint16)CanSM_Cfg_Data.NetworkInfoTbl->ModeRequestRepetitionMax + CANSM_FIRSTMODEREQUEST_NUM;

            CanSM_InitState = CANSM_INITED;
        }
        else
        {
            CanSM_ReportError(CANSM_API_ID_INIT, CANSM_E_PARAM_POINTER);
        }
    }
    else
    {
        CanSM_ReportError(CANSM_API_ID_INIT, CANSM_E_STATUS);
    }

    return;
}

/******************************************************************************/
/* Function Name | CanSM_RequestComMode                                       */
/* Description   | This service shall change the communication mode of a CAN  */
/*               | network to the requested one                               */
/* Preconditions |                                                            */
/* Parameters    | [IN]Network   : Network Identifier                         */
/*               | [IN]ComM_Mode : Communication Mode                         */
/* Return Value  | Status                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, CANSM_CODE_SLOW) CanSM_RequestComMode
(
    VAR(NetworkHandleType, AUTOMATIC) Network,
    VAR(ComM_ModeType, AUTOMATIC) ComM_Mode
)
{
    VAR(Std_ReturnType, AUTOMATIC) Result;
    VAR(uint8, AUTOMATIC) NetworkIndex;
    VAR(uint8, AUTOMATIC) MaskLevel;
    VAR(uint8, AUTOMATIC) CurrentStsIndFlg;

    Result = E_NOT_OK;

    if( ReprogOpt_CanDisableConfig == (uint8)STD_ON )
    {
        Result = E_OK;
    }
    else if( CanSM_InitState == CANSM_INITED )
    {
        for( NetworkIndex = 0U; NetworkIndex < CanSM_Cfg_Data.NetworkInfoTbl->NetworkNum; NetworkIndex++ )
        {
            if( CanSM_NetworkMng_Data[NetworkIndex].NetworkId == Network )
            {
                break;
            }
        }

        if( NetworkIndex < CanSM_Cfg_Data.NetworkInfoTbl->NetworkNum )
        {
            CurrentStsIndFlg = STD_OFF;

            MaskLevel = MaskInterruptAll();

            if( ( ComM_Mode == COMM_NO_COMMUNICATION ) &&
                ( CanSM_NetworkMng_Data[NetworkIndex].CanSMState == CANSM_BSM_S_FULLCOM ) )
            {
                CanSM_NetworkMng_Data[NetworkIndex].CanSMState = CANSM_BSM_S_PRE_NOCOM;
                CanSM_NetworkMng_Data[NetworkIndex].CanSMSubState = CANSM_S_CC_STOPPED;
                CanSM_NetworkMng_Data[NetworkIndex].ModeRequestCnt = 0U;
                CurrentStsIndFlg = STD_ON;
                Result = E_OK;
            }
            else if( ( ComM_Mode == COMM_FULL_COMMUNICATION ) &&
                     ( CanSM_NetworkMng_Data[NetworkIndex].CanSMState == CANSM_BSM_S_NOCOM ) )
            {
                CanSM_NetworkMng_Data[NetworkIndex].CanSMState = CANSM_BSM_S_PRE_FULLCOM;
                CanSM_NetworkMng_Data[NetworkIndex].CanSMSubState = CANSM_S_CC_STARTED;
                CanSM_NetworkMng_Data[NetworkIndex].ModeRequestCnt = 0U;
                Result = E_OK;
            }
            else
            {
                /* Nothing */
            }

            UnMaskInterruptAll(MaskLevel);

            if( CurrentStsIndFlg == (uint8)STD_ON )
            {
                BswM_CanSM_CurrentState(
                    CanSM_NetworkMng_Data[NetworkIndex].NetworkId,
                    CANSM_BSWM_NO_COMMUNICATION);
            }
        }
    }
    else
    {
        /* No process */
    }

    return Result;
}

/******************************************************************************/
/* Function Name | CanSM_ControllerModeIndication                             */
/* Description   | This callback shall notify the CanSM module about a CAN    */
/*               | controller mode change                                     */
/* Preconditions |                                                            */
/* Parameters    | [IN]ControllerId   : Controller Identifier                 */
/*               | [IN]ControllerMode : Controller Mode                       */
/* Return Value  | None                                                       */
/* Notes         | Execute this API on base context                           */
/******************************************************************************/
FUNC(void, CANSM_CODE_SLOW) CanSM_ControllerModeIndication
(
    VAR(uint8, AUTOMATIC) ControllerId,
    VAR(CanIf_ControllerModeType, AUTOMATIC) ControllerMode
)
{
    VAR(Std_ReturnType, AUTOMATIC) CanSMStsResult;
    VAR(uint8, AUTOMATIC) NetworkIndex;
    VAR(uint8, AUTOMATIC) ControllerIndex;

    if( ReprogOpt_CanDisableConfig == (uint8)STD_ON )
    {
        /* No process */
    }
    else if( CanSM_InitState == CANSM_INITED )
    {
        CanSMStsResult = E_NOT_OK;

        for( NetworkIndex = 0U; NetworkIndex < CanSM_Cfg_Data.NetworkInfoTbl->NetworkNum; NetworkIndex++ )
        {
            for( ControllerIndex = 0U;
                 ControllerIndex < CanSM_Cfg_Data.NetworkInfoTbl->NetworkSettingTbl[NetworkIndex].ControllerNum;
                 ControllerIndex++ )
            {
                if( ControllerId == CanSM_Cfg_Data.NetworkInfoTbl->NetworkSettingTbl[NetworkIndex].
                                        ControllerSettingTbl[ControllerIndex].ControllerId )
                {
                    break;
                }
            }

            if( ControllerIndex < CanSM_Cfg_Data.NetworkInfoTbl->NetworkSettingTbl[NetworkIndex].ControllerNum )
            {
                if( ( CanSM_NetworkMng_Data[NetworkIndex].CanSMState == CANSM_BSM_S_PRE_NOCOM ) &&
                    ( ( CanSM_NetworkMng_Data[NetworkIndex].CanSMSubState == CANSM_S_CC_STOPPED ) ||
                      ( CanSM_NetworkMng_Data[NetworkIndex].CanSMSubState == CANSM_S_CC_STOPPED_WAIT ) ) )
                {
                    CanSMStsResult = E_OK;
                }
                else if( ( CanSM_NetworkMng_Data[NetworkIndex].CanSMState == CANSM_BSM_S_PRE_FULLCOM ) &&
                    ( ( CanSM_NetworkMng_Data[NetworkIndex].CanSMSubState == CANSM_S_CC_STARTED ) ||
                      ( CanSM_NetworkMng_Data[NetworkIndex].CanSMSubState == CANSM_S_CC_STARTED_WAIT ) ) )
                {
                    CanSMStsResult = E_OK;
                }
                else if( CanSM_NetworkMng_Data[NetworkIndex].CanSMState == CANSM_BSM_S_CHANGE_BAUDRATE )
                {
                    CanSMStsResult = E_OK;
                }
                else
                {
                    /* Nothing */
                }
                break;
            }
        }

        if( CanSMStsResult == (Std_ReturnType)E_OK )
        {
            if( CanSM_ControllerMng_Data[ControllerId].RequestedControllerMode == ControllerMode )
            {
                if( CanSM_ControllerMng_Data[ControllerId].SetModeResult == CANSM_SETMODE_PENDING )
                {
                    CanSM_ControllerMng_Data[ControllerId].SetModeResult = CANSM_SETMODE_OK;
                    CanSM_ControllerMng_Data[ControllerId].CurrentControllerMode = ControllerMode;
                }
            }
            else
            {
                if( !( ( CanSM_NetworkMng_Data[NetworkIndex].CanSMState == CANSM_BSM_S_PRE_NOCOM ) &&
                       ( CanSM_NetworkMng_Data[NetworkIndex].CanSMSubState == CANSM_S_CC_STOPPED ) &&
                       ( ControllerMode == CANIF_CS_STARTED ) ) )
                {
                    CanSM_ReportError(CANSM_API_ID_CONTROLLERMODEIND, CANSM_E_STATUS);
                }
                else
                {
                    /* If CanSM_ControllerModeIndication(CANIF_CS_STARTED) was delayed, */
                    /* discard CanSM_ControllerMode(CANIF_CS_STARTED). */
                }
            }
        }
        else
        {
            CanSM_ReportError(CANSM_API_ID_CONTROLLERMODEIND, CANSM_E_PARAM_CONTROLLER);
        }
    }
    else
    {
        CanSM_ReportError(CANSM_API_ID_CONTROLLERMODEIND, CANSM_E_UNINIT);
    }

    return;
}

/******************************************************************************/
/* Function Name | CanSM_MainFunction                                         */
/* Description   | Scheduled function of the CanSM                            */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | Execute this API on base context                           */
/******************************************************************************/
FUNC(void, CANSM_CODE_SLOW) CanSM_MainFunction (void)
{
    VAR(uint8, AUTOMATIC) NetworkIndex;
    VAR(Std_ReturnType, AUTOMATIC) Result;

    if( ReprogOpt_CanDisableConfig == (uint8)STD_ON )
    {
        /* No process */
    }
    else if( CanSM_InitState == CANSM_INITED )
    {
        for( NetworkIndex = 0U; NetworkIndex < CanSM_Cfg_Data.NetworkInfoTbl->NetworkNum; NetworkIndex++ )
        {
            if( CanSM_NetworkMng_Data[NetworkIndex].CanSMState == CANSM_BSM_S_PRE_NOCOM )
            {
                Result = CanSM_PreNoComStsHandle(NetworkIndex);

                if( Result != (Std_ReturnType)E_OK )
                {
                    CanSM_ReportError(CANSM_API_ID_MAINFUNCTION, CANSM_E_PRENOCOM_STS_HANDLE);
                }
            }
            else if( CanSM_NetworkMng_Data[NetworkIndex].CanSMState == CANSM_BSM_S_PRE_FULLCOM )
            {
                Result = CanSM_PreFullComStsHandle(NetworkIndex);

                if( Result != (Std_ReturnType)E_OK )
                {
                    CanSM_ReportError(CANSM_API_ID_MAINFUNCTION, CANSM_E_PREFULLCOM_STS_HANDLE);
                }
            }
            else if( CanSM_NetworkMng_Data[NetworkIndex].CanSMState == CANSM_BSM_S_CHANGE_BAUDRATE )
            {
                Result = CanSM_SetBaudrateStsHandle(NetworkIndex);
                if( Result != (Std_ReturnType)E_OK )
                {
                    CanSM_ReportError(CANSM_API_ID_MAINFUNCTION, CANSM_E_BAUDRATE_STS_HANDLE);
                }
            }
            else
            {
                /* Nothing */
            }
        }
    }
    else
    {
        /* No process */
    }

    return;
}

#if 0   /* Nbr1503(ChangeBaudrate) */
/******************************************************************************/
/* Function Name | CanSM_SetBaudrate                                          */
/* Description   | This service shall set baudrate                            */
/* Preconditions |                                                            */
/* Parameters    | [IN]Network          : Network Identifier                  */
/*               | [IN]BaudRateConfigID : Baudrate Config Index               */
/* Return Value  | Status                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | the communication mode being COMM_FULL_COMMUNICATION       */
/******************************************************************************/
FUNC(Std_ReturnType, CANSM_CODE_SLOW) CanSM_SetBaudrate
(
    VAR(NetworkHandleType, AUTOMATIC) Network,
    VAR(uint16, AUTOMATIC) BaudRateConfigID
)
{
    VAR(Std_ReturnType, AUTOMATIC) Result;
    VAR(uint8, AUTOMATIC) NetworkIndex;

    Result = E_NOT_OK;

    if( ReprogOpt_CanDisableConfig == (uint8)STD_ON )
    {
        Result = E_OK;
    }
    else if( CanSM_InitState == CANSM_INITED )
    {
        for( NetworkIndex = 0U; NetworkIndex < CanSM_Cfg_Data.NetworkInfoTbl->NetworkNum; NetworkIndex++ )
        {
            if( ( CanSM_NetworkMng_Data[NetworkIndex].CanSMState == CANSM_BSM_S_FULLCOM ) &&
                ( CanSM_NetworkMng_Data[NetworkIndex].NetworkId == Network ) )
            {
                BswM_CanSM_CurrentState(
                    CanSM_NetworkMng_Data[NetworkIndex].NetworkId,
                    CANSM_BSWM_CHANGE_BAUDRATE);
                CanSM_NetworkMng_Data[NetworkIndex].CanSMState = CANSM_BSM_S_CHANGE_BAUDRATE;
                CanSM_NetworkMng_Data[NetworkIndex].CanSMSubState = CANSM_S_CC_STOPPED;
                CanSM_NetworkMng_Data[NetworkIndex].ModeRequestCnt = 0U;
                CanSM_NetworkMng_Data[NetworkIndex].BaudRateConfigIDFlg = (uint8)STD_ON;
                CanSM_NetworkMng_Data[NetworkIndex].BaudRateConfigID = BaudRateConfigID;
                Result = E_OK;
                break;
            }
        }
    }
    else
    {
        /* No process */
    }

    return Result;
}

/******************************************************************************/
/* Function Name | CanSM_CheckBaudrate                                        */
/* Description   | This service shall check baudrate                          */
/* Preconditions |                                                            */
/* Parameters    | [IN]Network          : Network Identifier                  */
/*               | [IN]BaudRateConfigID : Baudrate Config Index               */
/* Return Value  | Status                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, CANSM_CODE_SLOW) CanSM_CheckBaudrate
(
    VAR(NetworkHandleType, AUTOMATIC) Network,
    VAR(uint16, AUTOMATIC) BaudRateConfigID
)
{
    VAR(Std_ReturnType, AUTOMATIC) Result;
    VAR(uint8, AUTOMATIC) NetworkIndex;
    VAR(uint8, AUTOMATIC) ControllerIndex;
    VAR(uint8, AUTOMATIC) CfgControllerId;
    VAR(Std_ReturnType, AUTOMATIC) FuncReturn;

    Result = E_NOT_OK;

    if( ReprogOpt_CanDisableConfig == (uint8)STD_ON )
    {
        Result = E_OK;
    }
    else if( CanSM_InitState == CANSM_INITED )
    {
        for( NetworkIndex = 0U; NetworkIndex < CanSM_Cfg_Data.NetworkInfoTbl->NetworkNum; NetworkIndex++ )
        {
            if( CanSM_Cfg_Data.NetworkInfoTbl->NetworkSettingTbl[NetworkIndex].NetworkId == Network )
            {
                for( ControllerIndex = 0U;
                     ControllerIndex < CanSM_Cfg_Data.NetworkInfoTbl->NetworkSettingTbl[NetworkIndex].ControllerNum;
                     ControllerIndex++ )
                {
                    CfgControllerId =
                            CanSM_Cfg_Data.NetworkInfoTbl->NetworkSettingTbl[NetworkIndex].ControllerSettingTbl[ControllerIndex].ControllerId;
                    Result = E_OK;
                    FuncReturn = CanIf_CheckBaudrate(CfgControllerId, BaudRateConfigID);
                    if( FuncReturn != (Std_ReturnType)E_OK )
                    {
                        Result = E_NOT_OK;
                        break;
                    }
                }
                break;
            }
        }
    }
    else
    {
        /* No process */
    }

    return Result;
}

/******************************************************************************/
/* Function Name | CanSM_GetNetworkId                                         */
/* Description   | This service shall get network identifier                  */
/* Preconditions |                                                            */
/* Parameters    | [IN]PduId      : PDU Identifier                            */
/*               | [OUT]NetworkId : Network Identifier                        */
/* Return Value  | Status                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, CANSM_CODE_SLOW) CanSM_GetNetworkId
(
    VAR(PduIdType, AUTOMATIC) PduId,
    P2VAR(NetworkHandleType, AUTOMATIC, CANSM_APPL_DATA) NetworkId
)
{
    VAR(Std_ReturnType, AUTOMATIC) Result;
    VAR(uint8, AUTOMATIC) PduIdIndex;
    VAR(uint8, AUTOMATIC) ControllerIndex;
    VAR(uint8, AUTOMATIC) NetworkIndex;

    Result = E_NOT_OK;

    if( ReprogOpt_CanDisableConfig == (uint8)STD_ON )
    {
        *NetworkId = 0U;
        Result = E_OK;
    }
    else
    {
        for( PduIdIndex = 0U; PduIdIndex < CanSM_Cfg_Data.PduIdInfoTbl->PduIdNum; PduIdIndex++ )
        {
            if( CanSM_Cfg_Data.PduIdInfoTbl->PduIdSettingTbl[PduIdIndex].PduId == PduId )
            {
                for( NetworkIndex = 0U; NetworkIndex < CanSM_Cfg_Data.NetworkInfoTbl->NetworkNum; NetworkIndex++ )
                {
                    for( ControllerIndex = 0U;
                        ControllerIndex < CanSM_Cfg_Data.NetworkInfoTbl->NetworkSettingTbl[NetworkIndex].ControllerNum;
                        ControllerIndex++ )
                    {
                        if( CanSM_Cfg_Data.NetworkInfoTbl->NetworkSettingTbl[NetworkIndex].
                            ControllerSettingTbl[ControllerIndex].ControllerId ==
                            CanSM_Cfg_Data.PduIdInfoTbl->PduIdSettingTbl[PduIdIndex].Controller )
                        {
                            *NetworkId = CanSM_Cfg_Data.NetworkInfoTbl->NetworkSettingTbl[NetworkIndex].NetworkId;
                            Result = E_OK;
                            break;
                        }
                    }
                    if( Result == (Std_ReturnType)E_OK )
                    {
                        break;
                    }
                }
                if( Result == (Std_ReturnType)E_OK )
                {
                    break;
                }
            }
        }
    }

    return Result;
}
#endif

/******************************************************************************/
/* Function Name | CanSM_GetBaudrateConfigId                                  */
/* Description   | This service shall get baudrate config table index         */
/* Preconditions |                                                            */
/* Parameters    | [IN]BaudrateInfo      : Baudrate Information               */
/*               | [OUT]BaudRateConfigID : Baudrate Config Index              */
/* Return Value  | Status                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, CANSM_CODE_SLOW) CanSM_GetBaudrateConfigId
(
    P2CONST(CanSM_BaudrateInfoType, TYPEDEF, CANSM_APPL_CONST) BaudrateInfo,
    P2VAR(uint16, AUTOMATIC, CANSM_APPL_DATA) BaudRateConfigID
)
{
    VAR(Std_ReturnType, AUTOMATIC) Result;
    VAR(uint8, AUTOMATIC) i;
    VAR(uint8, AUTOMATIC) TblNum;
    VAR(uint8, AUTOMATIC) BaudrateConfigIndex;
    VAR(uint32, AUTOMATIC) Baudrate;
    VAR(uint32, AUTOMATIC) BaudrateTmp;

    Result = E_NOT_OK;
    Baudrate = 0UL;

    if( ReprogOpt_CanDisableConfig == (uint8)STD_ON )
    {
        *BaudRateConfigID = 0U;
        Result = E_OK;
    }
    else
    {
        if( BaudrateInfo->linkControlType == CANSM_LINKCTRL_TYPE1 )
        {
            TblNum = CanSM_BaudrateMatrixTblNum;
            for( i = 0U; i < TblNum; i++ )
            {
                if( BaudrateInfo->linkControlModeIdentifier == CanSM_BaudrateMatrixTbl[i].linkControlModeIdentifier )
                {
                    Baudrate = CanSM_BaudrateMatrixTbl[i].Baudrate;
                }
            }
        }
        else if( BaudrateInfo->linkControlType == CANSM_LINKCTRL_TYPE2 )
        {
            BaudrateTmp = Rpg_ByteCombine(&BaudrateInfo->linkRecord[CANSM_LINKREC_HIGH_POS], CANSM_LINKRECORD_NUM);
            Baudrate = Rpg_Div_u32(BaudrateTmp, CANSM_BPS_TO_KBPS);
        }
        else
        {
            /* Nothing */
        }

        if( Baudrate != 0UL )
        {
            for( BaudrateConfigIndex = 0U;
                BaudrateConfigIndex < CanSM_Cfg_Data.BaudrateInfoTbl->BaudrateNum;
                BaudrateConfigIndex++ )
            {
                if( Baudrate ==
                        (uint32)CanSM_Cfg_Data.BaudrateInfoTbl->BaudrateSettingTbl[BaudrateConfigIndex].Baudrate )
                {
                    *BaudRateConfigID = BaudrateConfigIndex;
                    Result = E_OK;
                    break;
                }
            }
        }
    }

    return Result;
}

/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/
/******************************************************************************/
/* Function Name | CanSM_SetControllerModePerNetwork                          */
/* Description   | This service shall set the controller mode of network      */
/*               | which was indicated                                        */
/* Preconditions |                                                            */
/* Parameters    | [IN]NetworkIndex   : CanSM_NetworkMng_Data Table Index     */
/*               | [IN]ControllerMode : Controller Mode                       */
/* Return Value  | Status                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(Std_ReturnType, CANSM_CODE_FAST) CanSM_SetControllerModePerNetwork
(
    VAR(uint8, AUTOMATIC) NetworkIndex,
    VAR(CanIf_ControllerModeType, AUTOMATIC) ControllerMode
)
{
    VAR(Std_ReturnType, AUTOMATIC) Result;
    VAR(Std_ReturnType, AUTOMATIC) FuncReturn;
    VAR(uint8, AUTOMATIC) ControllerIndex;
    VAR(uint8, AUTOMATIC) CfgControllerId;
    VAR(uint16, AUTOMATIC) BaudRateConfigID;

    Result = E_OK;

    for( ControllerIndex = 0U;
         ControllerIndex < CanSM_Cfg_Data.NetworkInfoTbl->NetworkSettingTbl[NetworkIndex].ControllerNum;
         ControllerIndex++ )
    {
        CfgControllerId =
            CanSM_Cfg_Data.NetworkInfoTbl->NetworkSettingTbl[NetworkIndex].ControllerSettingTbl[ControllerIndex].ControllerId;

        if( ControllerMode != CanSM_ControllerMng_Data[CfgControllerId].CurrentControllerMode )
        {
            if( CanSM_ControllerMng_Data[CfgControllerId].SetModeResult != CANSM_SETMODE_PENDING )
            {
                CanSM_ControllerMng_Data[CfgControllerId].SetModeResult = CANSM_SETMODE_PENDING;
                CanSM_ControllerMng_Data[CfgControllerId].RequestedControllerMode = ControllerMode;

                FuncReturn = (Std_ReturnType)E_OK;
                if( ControllerMode == CANIF_CS_STARTED )
                {
                    if( CanSM_NetworkMng_Data[NetworkIndex].BaudRateConfigIDFlg == (uint8)STD_ON )
                    {
                        BaudRateConfigID = CanSM_NetworkMng_Data[NetworkIndex].BaudRateConfigID;

                        FuncReturn = CanIf_SetBaudrate(CfgControllerId, BaudRateConfigID);
                    }
                }

                if( FuncReturn == (Std_ReturnType)E_OK )
                {
                    FuncReturn = CanIf_SetControllerMode(CfgControllerId, ControllerMode);
                }

                if( FuncReturn != (Std_ReturnType)E_OK )
                {
                    CanSM_ControllerMng_Data[CfgControllerId].SetModeResult = CANSM_SETMODE_NOT_OK;
                    Result = E_NOT_OK;
                }
            }
        }
    }

    return Result;
}

/******************************************************************************/
/* Function Name | CanSM_CheckControllerModeIndication                        */
/* Description   | This service shall check the result of                     */
/*               | the controller mode setting                                */
/* Preconditions |                                                            */
/* Parameters    | [IN]NetworkIndex   : CanSM_NetworkMng_Data Table Index     */
/* Return Value  | Result of controller mode setting                          */
/*               |  CANSM_SETMODE_OK                                          */
/*               |  CANSM_SETMODE_PENDING                                     */
/*               |  CANSM_SETMODE_NOT_OK                                      */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(CanSM_SetModeResultType, CANSM_CODE_FAST) CanSM_CheckControllerModeIndication
(
    VAR(uint8, AUTOMATIC) NetworkIndex
)
{
    VAR(CanSM_SetModeResultType, AUTOMATIC) Result;
    VAR(uint8, AUTOMATIC) ControllerIndex;
    VAR(uint8, AUTOMATIC) CfgControllerId;

    Result = CANSM_SETMODE_OK;

    for( ControllerIndex = 0U;
         ControllerIndex < CanSM_Cfg_Data.NetworkInfoTbl->NetworkSettingTbl[NetworkIndex].ControllerNum;
         ControllerIndex++ )
    {
        CfgControllerId =
            CanSM_Cfg_Data.NetworkInfoTbl->NetworkSettingTbl[NetworkIndex].ControllerSettingTbl[ControllerIndex].ControllerId;

        if( CanSM_ControllerMng_Data[CfgControllerId].SetModeResult == CANSM_SETMODE_PENDING )
        {
            Result = CANSM_SETMODE_PENDING;
        }
        else if( CanSM_ControllerMng_Data[CfgControllerId].SetModeResult != CANSM_SETMODE_OK )
        {
            Result = CANSM_SETMODE_NOT_OK;
            break;
        }
        else
        {
            /* Nothing */
        }
    }

    return Result;
}

/******************************************************************************/
/* Function Name | CanSM_RepetitionTimeHandle                                 */
/* Description   | This service shall handle repetition time                  */
/* Preconditions |                                                            */
/* Parameters    | [IN]NetworkIndex   : CanSM_NetworkMng_Data Table Index     */
/* Return Value  | Status                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | Execute this API during                                    */
/*               | the waiting for CanSM_ControllerModeIndication             */
/******************************************************************************/
static FUNC(Std_ReturnType, CANSM_CODE_FAST) CanSM_RepetitionTimeHandle
(
    VAR(uint8, AUTOMATIC) NetworkIndex
)
{
    VAR(Std_ReturnType, AUTOMATIC) Result;
    VAR(Std_ReturnType, AUTOMATIC) FuncReturn;
    VAR(uint32, AUTOMATIC) TimeSpan;
    VAR(uint8, AUTOMATIC) ControllerIndex;
    VAR(uint8, AUTOMATIC) CfgControllerId;

    Result = E_OK;
    TimeSpan = CANSM_MAXTIMESPAN;

    FuncReturn = Tm_GetTimeSpan1us32bit(&CanSM_NetworkMng_Data[NetworkIndex].TimerInstance, &TimeSpan);

    if( FuncReturn == (Std_ReturnType)E_OK )
    {
        if( TimeSpan >= CanSM_ModeRequestWaitTime )
        {
            if( CanSM_NetworkMng_Data[NetworkIndex].CanSMSubState == CANSM_S_CC_STOPPED_WAIT )
            {
                CanSM_NetworkMng_Data[NetworkIndex].CanSMSubState = CANSM_S_CC_STOPPED;
            }
            else
            {
                CanSM_NetworkMng_Data[NetworkIndex].CanSMSubState = CANSM_S_CC_STARTED;
            }

            for( ControllerIndex = 0U;
                 ControllerIndex < CanSM_Cfg_Data.NetworkInfoTbl->NetworkSettingTbl[NetworkIndex].ControllerNum;
                 ControllerIndex++ )
            {
                CfgControllerId =
                    CanSM_Cfg_Data.NetworkInfoTbl->
                        NetworkSettingTbl[NetworkIndex].ControllerSettingTbl[ControllerIndex].ControllerId;

                if( CanSM_ControllerMng_Data[CfgControllerId].SetModeResult == CANSM_SETMODE_PENDING )
                {
                    CanSM_ControllerMng_Data[CfgControllerId].SetModeResult = CANSM_SETMODE_NOT_OK;
                }
            }
        }
    }
    else
    {
        Result = E_NOT_OK;
    }

    return Result;
}

/******************************************************************************/
/* Function Name | CanSM_PreNoComStsHandle                                    */
/* Description   | This service shall handle pre-nocommunication status       */
/* Preconditions |                                                            */
/* Parameters    | [IN]NetworkIndex   : CanSM_NetworkMng_Data Table Index     */
/* Return Value  | Status                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | Execute from CanSM_MainFunction in CANSM_BSM_S_PRE_NOCOM   */
/******************************************************************************/
static FUNC(Std_ReturnType, CANSM_CODE_FAST) CanSM_PreNoComStsHandle
(
    VAR(uint8, AUTOMATIC) NetworkIndex
)
{
    VAR(Std_ReturnType, AUTOMATIC) Result;
    VAR(Std_ReturnType, AUTOMATIC) FuncReturn;
    VAR(CanSM_SetModeResultType, AUTOMATIC) SetModeResult;
    VAR(ComM_ModeType, AUTOMATIC) ComMode;
    VAR(uint8, AUTOMATIC) MaskLevel;

    Result = E_OK;

    if( CanSM_NetworkMng_Data[NetworkIndex].CanSMSubState == CANSM_S_CC_STOPPED )
    {
        if( CanSM_NetworkMng_Data[NetworkIndex].ModeRequestCnt < CanSM_ModeRequestCntMax )
        {
            CanSM_NetworkMng_Data[NetworkIndex].ModeRequestCnt++;

            FuncReturn = CanSM_SetControllerModePerNetwork(NetworkIndex, CANIF_CS_STOPPED);

            if( FuncReturn == (Std_ReturnType)E_OK )
            {
                SetModeResult = CanSM_CheckControllerModeIndication(NetworkIndex);

                if( SetModeResult == CANSM_SETMODE_OK )
                {
                    ComMode = COMM_NO_COMMUNICATION;

                    ComM_BusSM_ModeIndication(
                        CanSM_NetworkMng_Data[NetworkIndex].NetworkId,
                        &ComMode);

                    if( CanSM_NetworkMng_Data[NetworkIndex].CanSMState == CANSM_BSM_S_CHANGE_BAUDRATE )
                    {
                        CanSM_NetworkMng_Data[NetworkIndex].CanSMSubState = CANSM_S_CC_STARTED;
                    }
                    else
                    {
                        CanSM_NetworkMng_Data[NetworkIndex].CanSMState = CANSM_BSM_S_NOCOM;
                    }
                }
                else if( SetModeResult == CANSM_SETMODE_PENDING )
                {
                    FuncReturn = Tm_ResetTimer1us32bit(&CanSM_NetworkMng_Data[NetworkIndex].TimerInstance);

                    if( FuncReturn == (Std_ReturnType)E_OK )
                    {
                        CanSM_NetworkMng_Data[NetworkIndex].CanSMSubState = CANSM_S_CC_STOPPED_WAIT;
                    }
                    else
                    {
                        Result = E_NOT_OK;
                    }
                }
                else
                {
                    Result = E_NOT_OK;
                }
            }
        }
        else
        {
            CanSM_NetworkMng_Data[NetworkIndex].CanSMState = CANSM_BSM_S_PRE_NOCOM;
            CanSM_NetworkMng_Data[NetworkIndex].ModeRequestCnt = 0U;
            Result = E_NOT_OK;
        }
    }
    else if( CanSM_NetworkMng_Data[NetworkIndex].CanSMSubState == CANSM_S_CC_STOPPED_WAIT )
    {
        SetModeResult = CanSM_CheckControllerModeIndication(NetworkIndex);

        if( SetModeResult == CANSM_SETMODE_OK )
        {
            ComMode = COMM_NO_COMMUNICATION;

            ComM_BusSM_ModeIndication(
                CanSM_NetworkMng_Data[NetworkIndex].NetworkId,
                &ComMode);

            MaskLevel = MaskInterruptAll();

            CanSM_NetworkMng_Data[NetworkIndex].CanSMSubState = CANSM_S_CC_STARTED;
            if( CanSM_NetworkMng_Data[NetworkIndex].CanSMState != CANSM_BSM_S_CHANGE_BAUDRATE )
            {
                CanSM_NetworkMng_Data[NetworkIndex].CanSMState = CANSM_BSM_S_NOCOM;
                CanSM_NetworkMng_Data[NetworkIndex].CanSMSubState = CANSM_S_CC_STOPPED;
            }

            UnMaskInterruptAll(MaskLevel);
        }
        else if( SetModeResult == CANSM_SETMODE_PENDING )
        {
            FuncReturn = CanSM_RepetitionTimeHandle(NetworkIndex);

            if( FuncReturn != (Std_ReturnType)E_OK )
            {
                Result = E_NOT_OK;
            }
        }
        else
        {
            Result = E_NOT_OK;
        }
    }
    else
    {
        Result = E_NOT_OK;
    }

    return Result;
}

/******************************************************************************/
/* Function Name | CanSM_PreFullComStsHandle                                  */
/* Description   | This service shall handle pre-fullcommunication status     */
/* Preconditions |                                                            */
/* Parameters    | [IN]NetworkIndex   : CanSM_NetworkMng_Data Table Index     */
/* Return Value  | Status                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | Execute from CanSM_MainFunction in CANSM_BSM_S_PRE_FULLCOM */
/******************************************************************************/
static FUNC(Std_ReturnType, CANSM_CODE_FAST) CanSM_PreFullComStsHandle
(
    VAR(uint8, AUTOMATIC) NetworkIndex
)
{
    VAR(Std_ReturnType, AUTOMATIC) Result;
    VAR(Std_ReturnType, AUTOMATIC) FuncReturn;
    VAR(CanSM_SetModeResultType, AUTOMATIC) SetModeResult;
    VAR(ComM_ModeType, AUTOMATIC) ComMode;
    VAR(uint8, AUTOMATIC) MaskLevel;

    Result = E_OK;

    if( CanSM_NetworkMng_Data[NetworkIndex].CanSMSubState == CANSM_S_CC_STARTED )
    {
        if( CanSM_NetworkMng_Data[NetworkIndex].ModeRequestCnt < CanSM_ModeRequestCntMax )
        {
            CanSM_NetworkMng_Data[NetworkIndex].ModeRequestCnt++;

            FuncReturn = CanSM_SetControllerModePerNetwork(NetworkIndex, CANIF_CS_STARTED);

            if( FuncReturn == (Std_ReturnType)E_OK )
            {
                SetModeResult = CanSM_CheckControllerModeIndication(NetworkIndex);

                if( SetModeResult == CANSM_SETMODE_OK )
                {
                    ComMode = COMM_FULL_COMMUNICATION;

                    ComM_BusSM_ModeIndication(
                        CanSM_NetworkMng_Data[NetworkIndex].NetworkId,
                        &ComMode);

                    BswM_CanSM_CurrentState(
                        CanSM_NetworkMng_Data[NetworkIndex].NetworkId,
                        CANSM_BSWM_FULL_COMMUNICATION);

                    CanSM_NetworkMng_Data[NetworkIndex].CanSMState = CANSM_BSM_S_FULLCOM;
                }
                else if( SetModeResult == CANSM_SETMODE_PENDING )
                {
                    FuncReturn = Tm_ResetTimer1us32bit(&CanSM_NetworkMng_Data[NetworkIndex].TimerInstance);

                    if( FuncReturn == (Std_ReturnType)E_OK )
                    {
                        CanSM_NetworkMng_Data[NetworkIndex].CanSMSubState = CANSM_S_CC_STARTED_WAIT;
                    }
                    else
                    {
                        Result = E_NOT_OK;
                    }
                }
                else
                {
                    Result = E_NOT_OK;
                }
            }
        }
        else
        {
            MaskLevel = MaskInterruptAll();

            CanSM_NetworkMng_Data[NetworkIndex].CanSMState = CANSM_BSM_S_PRE_NOCOM;
            CanSM_NetworkMng_Data[NetworkIndex].CanSMSubState = CANSM_S_CC_STOPPED;

            UnMaskInterruptAll(MaskLevel);

            CanSM_NetworkMng_Data[NetworkIndex].ModeRequestCnt = 0U;
            Result = E_NOT_OK;
        }
    }
    else if( CanSM_NetworkMng_Data[NetworkIndex].CanSMSubState == CANSM_S_CC_STARTED_WAIT )
    {
        SetModeResult = CanSM_CheckControllerModeIndication(NetworkIndex);

        if( SetModeResult == CANSM_SETMODE_OK )
        {
            ComMode = COMM_FULL_COMMUNICATION;

            ComM_BusSM_ModeIndication(
                CanSM_NetworkMng_Data[NetworkIndex].NetworkId,
                &ComMode);

            BswM_CanSM_CurrentState(
                CanSM_NetworkMng_Data[NetworkIndex].NetworkId,
                CANSM_BSWM_FULL_COMMUNICATION);

            MaskLevel = MaskInterruptAll();

            CanSM_NetworkMng_Data[NetworkIndex].CanSMState = CANSM_BSM_S_FULLCOM;
            CanSM_NetworkMng_Data[NetworkIndex].CanSMSubState = CANSM_S_CC_STARTED;

            UnMaskInterruptAll(MaskLevel);
        }
        else if( SetModeResult == CANSM_SETMODE_PENDING )
        {
            FuncReturn = CanSM_RepetitionTimeHandle(NetworkIndex);

            if( FuncReturn != (Std_ReturnType)E_OK )
            {
                Result = E_NOT_OK;
            }
        }
        else
        {
            Result = E_NOT_OK;
        }
    }
    else
    {
        Result = E_NOT_OK;
    }

    return Result;
}

/******************************************************************************/
/* Function Name | CanSM_ReportError                                          */
/* Description   | Notified of the error information                          */
/* Preconditions |                                                            */
/* Parameters    | [IN] ApiId   : Api ID                                      */
/*               | [IN] ErrorId : Error ID                                    */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, CANSM_CODE_FAST) CanSM_ReportError
(
    VAR(uint8, AUTOMATIC) ApiId,
    VAR(uint8, AUTOMATIC) ErrorId
)
{
    VAR(EcuM_ErrorType, AUTOMATIC) ErrorInfo;

    ErrorInfo.ModuleId = ECUM_MODULE_CANSM;
    ErrorInfo.ApiId = ApiId;
    ErrorInfo.ErrorId = ErrorId;
    EcuM_ReportError(&ErrorInfo);

    return;
}

/******************************************************************************/
/* Function Name | CanSM_SetBaudrateStsHandle                                 */
/* Description   | This service shall handle set baudrate status              */
/* Preconditions |                                                            */
/* Parameters    | [IN]NetworkIndex : CanSM_NetworkMng_Data Table Index       */
/* Return Value  | Status                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | Execute from CanSM_MainFunction                            */
/*               | in CANSM_BSM_S_CHANGE_BAUDRATE                             */
/******************************************************************************/
static FUNC(Std_ReturnType, CANSM_CODE_FAST) CanSM_SetBaudrateStsHandle
(
    VAR(uint8, AUTOMATIC) NetworkIndex
)
{
    VAR(Std_ReturnType, AUTOMATIC) Result;

    if( ( CanSM_NetworkMng_Data[NetworkIndex].CanSMSubState == CANSM_S_CC_STOPPED ) ||
        ( CanSM_NetworkMng_Data[NetworkIndex].CanSMSubState == CANSM_S_CC_STOPPED_WAIT ) )
    {
        Result = CanSM_PreNoComStsHandle(NetworkIndex);
    }
    else /* CANSM_S_CC_STARTED or CANSM_S_CC_STARTED_WAIT */
    {
        Result = CanSM_PreFullComStsHandle(NetworkIndex);
    }

    return Result;
}

/******************************************************************************/
/* Function Name | CanSM_GetNetworkIdOfCanId                                  */
/* Description   | This service shall get network identifier                  */
/* Preconditions |                                                            */
/* Parameters    | [IN]CanId : CAN Identifier                                 */
/* Return Value  | NetworkId                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, CANSM_CODE_FAST) CanSM_GetNetworkIdOfCanId
(
    VAR(uint32, AUTOMATIC) CanId
)
{
    VAR(uint8, AUTOMATIC) NetworkId;
    VAR(uint8, AUTOMATIC) PduIndex;
    VAR(uint8, AUTOMATIC) ControllerId;
    VAR(uint8, AUTOMATIC) NetworkIndex;
    VAR(uint8, AUTOMATIC) ControllerIndex;

    NetworkId = CANSM_NETWORKID_INVALID;

    for( PduIndex = 0U; PduIndex < CanSM_Cfg_Data.PduIdInfoTbl->PduIdNum; PduIndex++ )
    {
        if( CanId == CanSM_Cfg_Data.PduIdInfoTbl->PduIdSettingTbl[PduIndex].CanId )
        {
            ControllerId = CanSM_Cfg_Data.PduIdInfoTbl->PduIdSettingTbl[PduIndex].Controller;
            for( NetworkIndex = 0U; NetworkIndex < CanSM_Cfg_Data.NetworkInfoTbl->NetworkNum; NetworkIndex++ )
            {
                for( ControllerIndex = 0U; ControllerIndex < CanSM_Cfg_Data.NetworkInfoTbl->NetworkSettingTbl[NetworkIndex].ControllerNum; ControllerIndex++ )
                {
                    if( ControllerId == CanSM_Cfg_Data.NetworkInfoTbl->NetworkSettingTbl[NetworkIndex].ControllerSettingTbl[ControllerIndex].ControllerId )
                    {
                        NetworkId = CanSM_Cfg_Data.NetworkInfoTbl->NetworkSettingTbl[NetworkIndex].NetworkId;
                        break;
                    }
                }
                if( ControllerIndex < CanSM_Cfg_Data.NetworkInfoTbl->NetworkSettingTbl[NetworkIndex].ControllerNum )
                {
                    break;
                }
            }
            if( NetworkIndex < CanSM_Cfg_Data.NetworkInfoTbl->NetworkNum )
            {
                break;
            }
        }
    }

    return NetworkId;
}

#define CANSM_STOP_SEC_CODE
#include <CanSM_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2020/03/10 :Update                                rel.AUBASS */
/*  v3.00       :2022/06/07 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/**** End of File *************************************************************/

