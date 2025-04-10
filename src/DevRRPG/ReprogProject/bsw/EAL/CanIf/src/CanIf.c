/* CanIf_c_Revision(v3.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | CanIf/CODE                                                  */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <CanIf.h>
#include <CanSM_Cbk.h>
#include <EcuM.h>
#include <ReprogOpt.h>
#include "CanIf_Local.h"


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
static FUNC(Std_ReturnType, CANIF_CODE_FAST) CanIf_SearchPduId
(
    VAR(PduIdType, AUTOMATIC) CanIfTxPduId,
    P2VAR(uint8, AUTOMATIC, CANIF_APPL_DATA) Index
);

static FUNC(Std_ReturnType, CANIF_CODE_FAST) CanIf_CheckControllerId
(
    VAR(uint8, AUTOMATIC) ControllerId
);

static FUNC(void, CANIF_CODE_FAST) CanIf_ReportError
(
    VAR(uint8, AUTOMATIC) ApiId,
    VAR(uint8, AUTOMATIC) ErrorId
);

/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define CANIF_START_SEC_VAR
#include <CanIf_MemMap.h>

static VAR(uint8, CANIF_VAR_CLEARED) CanIf_InitStatus;

#define CANIF_STOP_SEC_VAR
#include <CanIf_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define CANIF_START_SEC_CST
#include <CanIf_MemMap.h>


#define CANIF_STOP_SEC_CST
#include <CanIf_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define CANIF_START_SEC_CODE
#include <CanIf_MemMap.h>

/******************************************************************************/
/* Function Name | CanIf_Init                                                 */
/* Description   | This service Initializes internal and external interfaces  */
/*               | of the CAN Interface for the further processing            */
/* Preconditions |                                                            */
/* Parameters    | [IN]ConfigPtr : CanIf Configuration Table                  */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, CANIF_CODE_SLOW) CanIf_Init
(
    P2CONST(CanIf_ConfigType, AUTOMATIC, CANIF_APPL_CONST) ConfigPtr
)
{
    if( ReprogOpt_CanDisableConfig == (uint8)STD_ON )
    {
        /* No process */
    }
    else if( CanIf_InitStatus == CANIF_CS_UNINIT )
    {
        if( ConfigPtr == &CanIf_Cfg_Data )
        {
            CanIf_InitStatus = CANIF_CS_INIT;
        }
        else
        {
            CanIf_ReportError(CANIF_API_ID_INIT, CANIF_E_PARAM_POINTER);
        }
    }
    else
    {
        CanIf_ReportError(CANIF_API_ID_INIT, CANIF_E_UNINIT);
    }

    return;
}

/******************************************************************************/
/* Function Name | CanIf_SetControllerMode                                    */
/* Description   | This service calls the corresponding CAN Driver service    */
/*               | for changing of the CAN controller mode                    */
/* Preconditions |                                                            */
/* Parameters    | [IN]ControllerId   : Controller Identifier                 */
/*               | [IN]ControllerMode : Controller Mode                       */
/* Return Value  | Status                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, CANIF_CODE_SLOW) CanIf_SetControllerMode
(
    VAR(uint8, AUTOMATIC) ControllerId,
    VAR(CanIf_ControllerModeType, AUTOMATIC) ControllerMode
)
{
    VAR(Std_ReturnType, AUTOMATIC) Result;
    VAR(Std_ReturnType, AUTOMATIC) CheckResult;
    VAR(Can_ReturnType, AUTOMATIC) CanResult;
    VAR(Can_StateTransitionType, AUTOMATIC) Transition;

    Result = E_NOT_OK;

    if( ReprogOpt_CanDisableConfig == (uint8)STD_ON )
    {
        /* No process */
    }
    else if( CanIf_InitStatus == CANIF_CS_INIT )
    {
        CheckResult = CanIf_CheckControllerId(ControllerId);

        if( CheckResult == (Std_ReturnType)E_OK )
        {
            if( ControllerMode == CANIF_CS_STARTED )
            {
                Transition = CAN_T_START;
                Result = E_OK;
            }
            else if( ControllerMode == CANIF_CS_STOPPED )
            {
                Transition = CAN_T_STOP;
                Result = E_OK;
            }
            else
            {
                /* NOTHING */
            }
        }

        if( Result == (Std_ReturnType)E_OK )
        {
            CanResult = Can_SetControllerMode((U1)ControllerId, Transition);

            if( CanResult != CAN_OK )
            {
                Result = E_NOT_OK;
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
/* Function Name | CanIf_Transmit                                             */
/* Description   | This service initiates a request for transmission of the   */
/*               | CAN L-PDU specified by the CanTxSduId and CAN related data */
/*               | in the L-SDU structure                                     */
/* Preconditions |                                                            */
/* Parameters    | [IN]CanIfTxSduId   : Transmit SDU Identifier               */
/*               | [IN]CanIfTxInfoPtr : Address of Transmission Information   */
/*               |                      Buffer                                */
/* Return Value  | Status                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, CANIF_CODE_SLOW) CanIf_Transmit
(
    VAR(PduIdType, AUTOMATIC) CanIfTxSduId,
    P2CONST(PduInfoType, AUTOMATIC, CANIF_APPL_CONST) CanIfTxInfoPtr
)
{
    VAR(Std_ReturnType, AUTOMATIC) Result;
    VAR(Std_ReturnType, AUTOMATIC) SearchResult;
    VAR(Can_ReturnType, AUTOMATIC) CanResult;
    VAR(uint8, AUTOMATIC) TxIndex;
    VAR(Can_IdType, AUTOMATIC) CanId;
    VAR(Can_IdType, AUTOMATIC) CanIdType;
    VAR(Can_PduType, AUTOMATIC) PduInfo;

    Result = E_NOT_OK;
    TxIndex = 0U;

    if( ReprogOpt_CanDisableConfig == (uint8)STD_ON )
    {
        /* No process */
    }
    else if( CanIf_InitStatus == CANIF_CS_INIT )
    {
        if( CanIfTxInfoPtr != NULL_PTR )
        {
            if( CanIfTxInfoPtr->SduDataPtr != NULL_PTR )
            {
                if( CanIfTxInfoPtr->SduLength <= CANIF_SDUMAXLENGTH )
                {
                    SearchResult = CanIf_SearchPduId(CanIfTxSduId, &TxIndex);

                    if( SearchResult == (Std_ReturnType)E_OK )
                    {
                        CanIdType = (Can_IdType)CanIf_Cfg_Data.TxRxInfoTbl->TxPduSettingTbl[TxIndex].TxPduCanIdType;
                        CanId = CanIf_Cfg_Data.TxRxInfoTbl->TxPduSettingTbl[TxIndex].TxPduCanId;
                        CanId |= CanIdType << CANIF_CANIDTYPE_SHIFTBIT;
                        PduInfo.swPduHandle = CanIfTxSduId;
                        PduInfo.length = (U1)CanIfTxInfoPtr->SduLength;
                        PduInfo.id = CanId;
                        PduInfo.sdu = CanIfTxInfoPtr->SduDataPtr;
                        CanResult = Can_Write(CanIf_Cfg_Data.TxRxInfoTbl->TxPduSettingTbl[TxIndex].HthIndx, &PduInfo);

                        if( CanResult == CAN_OK )
                        {
                            Result = E_OK;
                        }
                    }
                }
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
/* Function Name | CanIf_CancelTransmit                                       */
/* Description   | This service cancels the transmission of CAN corresponding */
/*               | to CanTxSduId                                              */
/* Preconditions |                                                            */
/* Parameters    | [IN]CanIfTxSduId : Transmit SDU Identifier                 */
/* Return Value  | Status                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, CANIF_CODE_SLOW) CanIf_CancelTransmit
(
    VAR(PduIdType, AUTOMATIC) CanIfTxSduId
)
{
    VAR(Std_ReturnType, AUTOMATIC) Result;
    VAR(Std_ReturnType, AUTOMATIC) SearchResult;
    VAR(uint8, AUTOMATIC) TxIndex;

    Result = E_NOT_OK;
    TxIndex = 0U;

    if( ReprogOpt_CanDisableConfig == (uint8)STD_ON )
    {
        /* No process */
    }
    else if( CanIf_InitStatus == CANIF_CS_INIT )
    {
        SearchResult = CanIf_SearchPduId(CanIfTxSduId, &TxIndex);

        if( SearchResult == (Std_ReturnType)E_OK )
        {
            Can_Cancel(CanIf_Cfg_Data.TxRxInfoTbl->TxPduSettingTbl[TxIndex].HthIndx);

            Result = E_OK;
        }
    }
    else
    {
        /* No process */
    }

    return Result;
}

/******************************************************************************/
/* Function Name | CanIf_TxConfirmation                                       */
/* Description   | This service confirms a previously successfully processed  */
/*               | transmission of a CAN TxPDU                                */
/* Preconditions |                                                            */
/* Parameters    | [IN]CanTxPduId : PDU Identifier                            */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, CANIF_CODE_SLOW) CanIf_TxConfirmation
(
    VAR(PduIdType, AUTOMATIC) CanTxPduId
)
{
    VAR(Std_ReturnType, AUTOMATIC) SearchResult;
    VAR(uint8, AUTOMATIC) TxIndex;

    TxIndex = 0U;

    if( ReprogOpt_CanDisableConfig == (uint8)STD_ON )
    {
        /* No process */
    }
    else if( CanIf_InitStatus == CANIF_CS_INIT )
    {
        SearchResult = CanIf_SearchPduId(CanTxPduId, &TxIndex);

        if( SearchResult == (Std_ReturnType)E_OK )
        {
            CanIf_Cfg_Data.TxRxInfoTbl->TxPduSettingTbl[TxIndex].TxConfirmationFunc(CanTxPduId);
        }
    }
    else
    {
        /* No process */
    }

    return;
}

/******************************************************************************/
/* Function Name | CanIf_SetBaudrate                                          */
/* Description   | This service shall set the baud rate configuration of the  */
/*               | CAN controller                                             */
/* Preconditions |                                                            */
/* Parameters    | [IN]ControllerId     : Controller Identifier               */
/*               | [IN]BaudRateConfigID : Baudrate Identifier                 */
/* Return Value  | Status                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, CANIF_CODE_SLOW) CanIf_SetBaudrate
(
    VAR(uint8, AUTOMATIC) ControllerId,
    VAR(uint16, AUTOMATIC) BaudRateConfigID
)
{
    VAR(Std_ReturnType, AUTOMATIC) Result;
    VAR(Std_ReturnType, AUTOMATIC) CheckResult;

    Result = E_NOT_OK;

    if( ReprogOpt_CanDisableConfig == (uint8)STD_ON )
    {
        /* No process */
    }
    else if( CanIf_InitStatus == CANIF_CS_INIT )
    {
        CheckResult = CanIf_CheckControllerId(ControllerId);

        if( CheckResult == (Std_ReturnType)E_OK )
        {
            CheckResult = Can_SetBaudrate((U1)ControllerId, (U2)BaudRateConfigID);

            if( CheckResult == (Std_ReturnType)E_OK )
            {
                Result = E_OK;
            }
        }
    }
    else
    {
        /* No process */
    }

    return Result;
}

#if 0   /* Nbr1503(ChangeBaudrate) */
/******************************************************************************/
/* Function Name | CanIf_CheckBaudrate                                        */
/* Description   | This service shall check, if a certain CAN controller      */
/*               | supports a requested baudrate                              */
/* Preconditions |                                                            */
/* Parameters    | [IN]ControllerId     : Controller Identifier               */
/*               | [IN]BaudRateConfigID : Baudrate Identifier                 */
/* Return Value  | Status                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, CANIF_CODE_SLOW) CanIf_CheckBaudrate
(
    VAR(uint8, AUTOMATIC) ControllerId,
    VAR(uint16, AUTOMATIC) BaudRateConfigID
)
{
    VAR(Std_ReturnType, AUTOMATIC) Result;
    VAR(Std_ReturnType, AUTOMATIC) CheckResult;

    Result = E_NOT_OK;

    if( ReprogOpt_CanDisableConfig == (uint8)STD_ON )
    {
        /* No process */
    }
    else if( CanIf_InitStatus == CANIF_CS_INIT )
    {
        CheckResult = CanIf_CheckControllerId(ControllerId);

        if( CheckResult == (Std_ReturnType)E_OK )
        {
            CheckResult = Can_CheckBaudrate((U1)ControllerId, (U2)BaudRateConfigID);

            if( CheckResult == (Std_ReturnType)E_OK )
            {
                Result = E_OK;
            }
        }
    }
    else
    {
        /* No process */
    }

    return Result;
}
#endif

/******************************************************************************/
/* Function Name | CanIf_RxIndication                                         */
/* Description   | This service indicates a successful reception of a         */
/*               | received CAN Rx LPDU to the CanIf after passing all        */
/*               | filters and validation checks                              */
/* Preconditions |                                                            */
/* Parameters    | [IN]Mailbox    : Address of CAN HardWare Object            */
/*               |                  Information                               */
/*               | [IN]PduInfoPtr : Address of PDU Information                */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, CANIF_CODE_SLOW) CanIf_RxIndication
(
    P2CONST(Can_HwType, AUTOMATIC, CANIF_APPL_CONST) Mailbox,
    P2CONST(PduInfoType, AUTOMATIC, CANIF_APPL_CONST) PduInfoPtr
)
{
#if (CANIF_UCFG_CANFD_SUPPORT != STD_ON)
    VAR(Std_ReturnType, AUTOMATIC) Result;
#endif
    VAR(Gdn_PduInfoType, AUTOMATIC) Gdn_PduInfo;
    VAR(uint8, AUTOMATIC) CanIdType;
    VAR(uint32, AUTOMATIC) CanId;
    VAR(uint8, AUTOMATIC) PduIndex;

#if (CANIF_UCFG_CANFD_SUPPORT != STD_ON)
    Result = E_NOT_OK;
#endif

    if( ReprogOpt_CanDisableConfig == (uint8)STD_ON )
    {
        /* No process */
    }
    else if( CanIf_InitStatus == CANIF_CS_INIT )
    {
        if( Mailbox != NULL_PTR )
        {
            if( ( PduInfoPtr != NULL_PTR ) &&
                ( PduInfoPtr->SduDataPtr != NULL_PTR ) &&
                ( PduInfoPtr->SduLength <= CANIF_SDUMAXLENGTH ) )
            {
                CanIdType = (uint8)(Mailbox->CanId >> CANIF_CANIDTYPE_SHIFTBIT);

#if (CANIF_UCFG_CANFD_SUPPORT == STD_ON)
                if( ( CanIdType == CANIF_STANDARD_CAN ) || ( CanIdType == CANIF_STANDARD_FD_CAN ) )
                {
                    CanId = Mailbox->CanId & CANIF_STANDARD_CANID_MASK;
                }
                else
                {
                    CanId = Mailbox->CanId & CANIF_EXTENDED_CANID_MASK;
                }
#else
                if( CanIdType == CANIF_STANDARD_CAN )
                {
                    CanId = Mailbox->CanId & CANIF_STANDARD_CANID_MASK;
                    Result = E_OK;
                }
                else if( CanIdType == CANIF_EXTENDED_CAN )
                {
                    CanId = Mailbox->CanId & CANIF_EXTENDED_CANID_MASK;
                    Result = E_OK;
                }
                else
                {
                    /* NOTHING */
                }
#endif

#if (CANIF_UCFG_CANFD_SUPPORT != STD_ON)
                if( Result == (Std_ReturnType)E_OK )
                {
#endif
                    for( PduIndex = 0U; PduIndex < CanIf_Cfg_Data.TxRxInfoTbl->RxPduSettingNum; PduIndex++ )
                    {
                        if( ( CanId == CanIf_Cfg_Data.TxRxInfoTbl->RxPduSettingTbl[PduIndex].RxPduCanId ) &&
                            ( CanIdType == CanIf_Cfg_Data.TxRxInfoTbl->RxPduSettingTbl[PduIndex].RxPduCanIdType ) &&
                            ( Mailbox->Hoh == CanIf_Cfg_Data.TxRxInfoTbl->RxPduSettingTbl[PduIndex].HrhIndx ) )
                        {
                            Gdn_PduInfo.SduDataPtr = PduInfoPtr->SduDataPtr;
                            Gdn_PduInfo.SduLength = (uint16)PduInfoPtr->SduLength;
                            CanIf_Cfg_Data.TxRxInfoTbl->RxPduSettingTbl[PduIndex].RxIndicationFunc(
                                CanIf_Cfg_Data.TxRxInfoTbl->RxPduSettingTbl[PduIndex].RxPduId, &Gdn_PduInfo);
                        }
                    }
#if (CANIF_UCFG_CANFD_SUPPORT != STD_ON)
                }
#endif
            }
        }
    }
    else
    {
        /* No process */
    }

    return;
}

/******************************************************************************/
/* Function Name | CanIf_ControllerModeIndication                             */
/* Description   | This service indicates a controller state transition       */
/*               | referring to the corresponding CAN controller with the     */
/*               | abstract CanIf ControllerId                                */
/* Preconditions |                                                            */
/* Parameters    | [IN]ControllerId   : Controller Identifier                 */
/*               | [IN]ControllerMode : Controller Mode                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, CANIF_CODE_SLOW) CanIf_ControllerModeIndication
(
    VAR(uint8, AUTOMATIC) ControllerId,
    VAR(CanIf_ControllerModeType, AUTOMATIC) ControllerMode
)
{
    VAR(Std_ReturnType, AUTOMATIC) CheckResult;

    if( ReprogOpt_CanDisableConfig == (uint8)STD_ON )
    {
        /* No process */
    }
    else if( CanIf_InitStatus == CANIF_CS_INIT )
    {
        CheckResult = CanIf_CheckControllerId(ControllerId);

        if( CheckResult == (Std_ReturnType)E_OK )
        {
            if( ( ControllerMode == CANIF_CS_STARTED ) || ( ControllerMode == CANIF_CS_STOPPED ) )
            {
                CanSM_ControllerModeIndication(ControllerId, ControllerMode);
            }
        }
    }
    else
    {
        /* No process */
    }

    return;
}

/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/
/******************************************************************************/
/* Function Name | CanIf_SearchPduId                                          */
/* Description   | This service searches an index of CanTxPduId               */
/* Preconditions |                                                            */
/* Parameters    | [IN]CanIfTxPduId : CanIfTxPduId for Finding TxPduId        */
/*               | [OUT]Index       : Index of PDU Identifier                 */
/* Return Value  | Status                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | Guarantee a value of Index                                 */
/******************************************************************************/
static FUNC(Std_ReturnType, CANIF_CODE_FAST) CanIf_SearchPduId
(
    VAR(PduIdType, AUTOMATIC) CanIfTxPduId,
    P2VAR(uint8, AUTOMATIC, CANIF_APPL_DATA) Index
)
{
    VAR(Std_ReturnType, AUTOMATIC) Result;
    VAR(uint8, AUTOMATIC) PduIndex;

    Result = E_NOT_OK;

    for( PduIndex = 0U; PduIndex < CanIf_Cfg_Data.TxRxInfoTbl->TxPduSettingNum; PduIndex++ )
    {
        if( CanIfTxPduId == CanIf_Cfg_Data.TxRxInfoTbl->TxPduSettingTbl[PduIndex].TxPduId )
        {
            *Index = PduIndex;
            Result = E_OK;
            break;
        }
    }

    return Result;
}

/******************************************************************************/
/* Function Name | CanIf_CheckControllerId                                    */
/* Description   | This service checks the CAN ControllerId                   */
/* Preconditions |                                                            */
/* Parameters    | [IN]ControllerId : ControllerId for Checking               */
/* Return Value  | Status                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(Std_ReturnType, CANIF_CODE_FAST) CanIf_CheckControllerId
(
    VAR(uint8, AUTOMATIC) ControllerId
)
{
    VAR(Std_ReturnType, AUTOMATIC) Result;
    VAR(uint8, AUTOMATIC) ControllerIndex;

    Result = E_NOT_OK;

    for( ControllerIndex = 0U; ControllerIndex < CanIf_Cfg_Data.ControllerInfoTbl->ControllerSettingNum; ControllerIndex++ )
    {
        if( ControllerId == CanIf_Cfg_Data.ControllerInfoTbl->ControllerSettingTbl[ControllerIndex].CanControllerId )
        {
            Result = E_OK;
            break;
        }
    }

    return Result;
}

/******************************************************************************/
/* Function Name | CanIf_ReportError                                           */
/* Description   | Notified of the error information                          */
/* Preconditions |                                                            */
/* Parameters    | [IN] ApiId   : Api ID                                      */
/*               | [IN] ErrorId : Error ID                                    */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, CANIF_CODE_FAST) CanIf_ReportError
(
    VAR(uint8, AUTOMATIC) ApiId,
    VAR(uint8, AUTOMATIC) ErrorId
)
{
    VAR(EcuM_ErrorType, AUTOMATIC) ErrorInfo;

    ErrorInfo.ModuleId = ECUM_MODULE_CANIF;
    ErrorInfo.ApiId = ApiId;
    ErrorInfo.ErrorId = ErrorId;
    EcuM_ReportError(&ErrorInfo);

    return;
}

#define CANIF_STOP_SEC_CODE
#include <CanIf_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2019/12/03 :Update                                rel.AUBASS */
/*  v3.00       :2022/03/01 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/**** End of File *************************************************************/

