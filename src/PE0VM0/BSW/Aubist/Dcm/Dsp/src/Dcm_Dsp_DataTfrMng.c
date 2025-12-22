/* Dcm_Dsp_DataTfrMng_c(v5-3-0)                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_DataTfrMng/CODE                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>

#if ( DCM_ULDL_SERVICE_USE == STD_ON )

#include <Dcm/Dcm_Dsp_DataTfrMng.h>
#include "../../Dsp/cfg/Dcm_Dsp_DataTfrMng_Cfg.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
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
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

static VAR( Dcm_Dsp_DataTfrMng_TfrInfoType, DCM_VAR_NO_INIT ) Dcm_Dsp_DataTfrMng_stTfrInfo;
static VAR( uint8, DCM_VAR_NO_INIT ) Dcm_Dsp_DataTfrMng_u1TfrStatus;

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
/* Function Name | Dcm_Dsp_DataTfrMng_Init                                  */
/* Description   | DataTfrMng initialization                                */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | Call From Dcm_Init.                                      */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_DataTfrMng_Init
( void )
{
    Dcm_Dsp_DataTfrMng_stTfrInfo.u4MemoryAddress = (uint32)0x00000000U;
    Dcm_Dsp_DataTfrMng_stTfrInfo.u4MemorySize    = (uint32)0x00000000U;
    Dcm_Dsp_DataTfrMng_stTfrInfo.u1Dfid          = (uint8)0x00U;
    Dcm_Dsp_DataTfrMng_stTfrInfo.u1MemoryId      = (uint8)0x00U;
    Dcm_Dsp_DataTfrMng_stTfrInfo.u1Bsc           = (uint8)0x00U;

    Dcm_Dsp_DataTfrMng_u1TfrStatus = DCM_TFR_NONE;

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_DataTfrMng_InitTfrStatus                         */
/* Description   | Initialize transfer status                               */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | Call From SID37,and SW-C.                                */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_DataTfrMng_InitTfrStatus
( void )
{
    Dcm_Dsp_DataTfrMng_u1TfrStatus = DCM_TFR_NONE;

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_DataTfrMng_GetTfrStatus                          */
/* Description   | Get transfer status                                      */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | uint8                                                    */
/*               |  Transfer status                                         */
/* Notes         | Call From SID36,SID37,and SW-C.                          */
/****************************************************************************/
FUNC( uint8, DCM_CODE ) Dcm_Dsp_DataTfrMng_GetTfrStatus
( void )
{
    return Dcm_Dsp_DataTfrMng_u1TfrStatus;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_DataTfrMng_InitTfrInfo                           */
/* Description   | Initialize transfer information                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | Call From SID37,and SW-C.                                */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_DataTfrMng_InitTfrInfo
( void )
{
    Dcm_Dsp_DataTfrMng_stTfrInfo.u4MemoryAddress = (uint32)0x00000000U;
    Dcm_Dsp_DataTfrMng_stTfrInfo.u4MemorySize    = (uint32)0x00000000U;
    Dcm_Dsp_DataTfrMng_stTfrInfo.u1Dfid          = (uint8)0x00U;
    Dcm_Dsp_DataTfrMng_stTfrInfo.u1MemoryId      = (uint8)0x00U;
    Dcm_Dsp_DataTfrMng_stTfrInfo.u1Bsc           = (uint8)0x00U;

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_DataTfrMng_GetTfrInfo                            */
/* Description   | Get transfer information                                 */
/* Preconditions | None                                                     */
/* Parameters    | [OUT] ptTfrInfo : Transfer information                   */
/* Return Value  | None                                                     */
/* Notes         | ptTfrInfo must be a valid pointer                        */
/*               | Call From SID36,SID37.                                   */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_DataTfrMng_GetTfrInfo
(
    P2VAR( Dcm_Dsp_DataTfrMng_TfrInfoType, AUTOMATIC, DCM_APPL_DATA ) ptTfrInfo
)
{
    ptTfrInfo->u4MemoryAddress = Dcm_Dsp_DataTfrMng_stTfrInfo.u4MemoryAddress;
    ptTfrInfo->u4MemorySize    = Dcm_Dsp_DataTfrMng_stTfrInfo.u4MemorySize;
    ptTfrInfo->u1Dfid          = Dcm_Dsp_DataTfrMng_stTfrInfo.u1Dfid;
    ptTfrInfo->u1MemoryId      = Dcm_Dsp_DataTfrMng_stTfrInfo.u1MemoryId;
    ptTfrInfo->u1Bsc           = Dcm_Dsp_DataTfrMng_stTfrInfo.u1Bsc;

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_DataTfrMng_ChkAlfid                              */
/* Description   | Check addressAndLengthFormatIdentifier                   */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1Alfid : addressAndLengthFormatIdentifier          */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK     : Alfid is supported                          */
/*               |   E_NOT_OK : Alfid is not supported                      */
/* Notes         | Call From SID34,SID35.                                   */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DataTfrMng_ChkAlfid
(
    const uint8 u1Alfid
)
{
    Std_ReturnType u1_RetVal;
    uint8          u1_CfgAlfidNum;
    uint8          u1_CfgAlfid;
    uint8          u1_Cnt;

    u1_RetVal = E_NOT_OK;

    u1_CfgAlfidNum = Dcm_Dsp_DataTfrMng_u1AlfidNum;
    for( u1_Cnt = (uint8)0U; u1_Cnt < u1_CfgAlfidNum; u1_Cnt++ )
    {
        u1_CfgAlfid = Dcm_Dsp_DataTfrMng_u1AlfidTbl[u1_Cnt];
        if( u1Alfid == u1_CfgAlfid )
        {
            u1_RetVal = E_OK;
            break;
        }
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_DataTfrMng_ProcReqDL                             */
/* Description   | Process of request download                              */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1OpStatus             : Operation state            */
/*               | [IN] u1DataFormatIdentifier : Data format identifier     */
/*               | [IN] u1MemoryIdentifier     : Memory identifier          */
/*               | [IN] u4MemoryAddress        : Memory address             */
/*               | [IN] u4MemorySize           : Memory size                */
/*               | [INOUT] ptBlockLength       : Block length               */
/*               | [OUT] ptErrorCode           : Error code                 */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK          : Request was successful                 */
/*               |   E_NOT_OK      : Request was not successful             */
/*               |   DCM_E_PENDING : Request is not yet finished            */
/* Notes         | Call From SID34.                                         */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DataTfrMng_ProcReqDL
(
    Dcm_OpStatusType u1OpStatus,
    uint8 u1DataFormatIdentifier,
    uint8 u1MemoryIdentifier,
    uint32 u4MemoryAddress,
    uint32 u4MemorySize,
    P2VAR( uint32, AUTOMATIC, DCM_APPL_DATA ) ptBlockLength,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
)
{
    Std_ReturnType u1_RetVal;

    if( u1OpStatus != (Dcm_OpStatusType)DCM_CANCEL )
    {
        u1_RetVal = Dcm_Dsp_DataTfrMng_CallProcReqDLFnc( u1OpStatus,
                                                         u1DataFormatIdentifier,
                                                         u1MemoryIdentifier,
                                                         u4MemoryAddress,
                                                         u4MemorySize,
                                                         ptBlockLength,
                                                         ptErrorCode );

        if( u1_RetVal == (Std_ReturnType)E_OK )
        {
            Dcm_Dsp_DataTfrMng_stTfrInfo.u4MemoryAddress = u4MemoryAddress;
            Dcm_Dsp_DataTfrMng_stTfrInfo.u4MemorySize    = u4MemorySize;
            Dcm_Dsp_DataTfrMng_stTfrInfo.u1Dfid          = u1DataFormatIdentifier;
            Dcm_Dsp_DataTfrMng_stTfrInfo.u1MemoryId      = u1MemoryIdentifier;
            Dcm_Dsp_DataTfrMng_stTfrInfo.u1Bsc           = (uint8)0x00U;

            Dcm_Dsp_DataTfrMng_u1TfrStatus = DCM_TFR_DL_START;
        }
        else if( ( u1_RetVal == (Std_ReturnType)DCM_E_PENDING ) ||
                 ( u1_RetVal == (Std_ReturnType)E_NOT_OK ) )
        {
            /* No process */
        }
        else
        {
            *ptErrorCode = DCM_E_GENERALREJECT;
            u1_RetVal = E_NOT_OK;
        }
    }
    else
    {
        (void)Dcm_Dsp_DataTfrMng_CallProcReqDLFnc( u1OpStatus,              /* No return check required */
                                                   u1DataFormatIdentifier,
                                                   u1MemoryIdentifier,
                                                   u4MemoryAddress,
                                                   u4MemorySize,
                                                   ptBlockLength,
                                                   ptErrorCode );
        u1_RetVal = E_OK;
    }

    return u1_RetVal;
}

#if ( DCM_UL_PROCESS_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DataTfrMng_ProcReqUL                             */
/* Description   | Process of request upload                                */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1OpStatus             : Operation state            */
/*               | [IN] u1DataFormatIdentifier : Data format identifier     */
/*               | [IN] u1MemoryIdentifier     : Memory identifier          */
/*               | [IN] u4MemoryAddress        : Memory address             */
/*               | [IN] u4MemorySize           : Memory size                */
/*               | [INOUT] ptBlockLength       : Block length               */
/*               | [OUT] ptErrorCode           : Error code                 */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK          : Request was successful                 */
/*               |   E_NOT_OK      : Request was not successful             */
/*               |   DCM_E_PENDING : Request is not yet finished            */
/* Notes         | Call From SID35.                                         */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DataTfrMng_ProcReqUL
(
    Dcm_OpStatusType u1OpStatus,
    uint8 u1DataFormatIdentifier,
    uint8 u1MemoryIdentifier,
    uint32 u4MemoryAddress,
    uint32 u4MemorySize,
    P2VAR( uint32, AUTOMATIC, DCM_APPL_DATA ) ptBlockLength,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
)
{
    Std_ReturnType u1_RetVal;

    if( u1OpStatus != (Dcm_OpStatusType)DCM_CANCEL )
    {
        u1_RetVal = Dcm_Dsp_DataTfrMng_CallProcReqULFnc( u1OpStatus,
                                                         u1DataFormatIdentifier,
                                                         u1MemoryIdentifier,
                                                         u4MemoryAddress,
                                                         u4MemorySize,
                                                         ptBlockLength,
                                                         ptErrorCode );

        if( u1_RetVal == (Std_ReturnType)E_OK )
        {
            Dcm_Dsp_DataTfrMng_stTfrInfo.u4MemoryAddress = u4MemoryAddress;
            Dcm_Dsp_DataTfrMng_stTfrInfo.u4MemorySize    = u4MemorySize;
            Dcm_Dsp_DataTfrMng_stTfrInfo.u1Dfid          = u1DataFormatIdentifier;
            Dcm_Dsp_DataTfrMng_stTfrInfo.u1MemoryId      = u1MemoryIdentifier;
            Dcm_Dsp_DataTfrMng_stTfrInfo.u1Bsc           = (uint8)0x00U;

            Dcm_Dsp_DataTfrMng_u1TfrStatus = DCM_TFR_UL_START;
        }
        else if( ( u1_RetVal == (Std_ReturnType)DCM_E_PENDING ) ||
                 ( u1_RetVal == (Std_ReturnType)E_NOT_OK ) )
        {
            /* No process */
        }
        else
        {
            *ptErrorCode = DCM_E_GENERALREJECT;
            u1_RetVal = E_NOT_OK;
        }
    }
    else
    {
        (void)Dcm_Dsp_DataTfrMng_CallProcReqULFnc( u1OpStatus,              /* No return check required */
                                                   u1DataFormatIdentifier,
                                                   u1MemoryIdentifier,
                                                   u4MemoryAddress,
                                                   u4MemorySize,
                                                   ptBlockLength,
                                                   ptErrorCode );
        u1_RetVal = E_OK;
    }

    return u1_RetVal;
}
#endif  /* DCM_UL_PROCESS_USE == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsp_DataTfrMng_ProcTfrDataWrite                      */
/* Description   | Process of transfer data write                           */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1OpStatus   : Operation state                      */
/*               | [IN] u1Bsc        : Block sequence counter               */
/*               | [IN] u4MemorySize : Size of ptMemoryData                 */
/*               | [IN] ptMemoryData : Memory data                          */
/*               | [OUT] ptErrorCode : Error code                           */
/* Return Value  | Dcm_ReturnWriteMemoryType                                */
/*               |   DCM_WRITE_OK          : Write was successful           */
/*               |   DCM_WRITE_FAILED      : Write was not successful       */
/*               |   DCM_WRITE_PENDING     : Write is not yet finished      */
/*               |   DCM_WRITE_FORCE_RCRRP : RCRRP response                 */
/* Notes         | Call only when transfer status is DCM_TFR_DL_START or    */
/*               | DCM_TFR_DL_PROCEED                                       */
/*               | Call From SID36.                                         */
/****************************************************************************/
FUNC( Dcm_ReturnWriteMemoryType, DCM_CODE ) Dcm_Dsp_DataTfrMng_ProcTfrDataWrite
(
    Dcm_OpStatusType u1OpStatus,
    uint8 u1Bsc,
    uint32 u4MemorySize,
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA ) ptMemoryData,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
)
{
    Dcm_ReturnWriteMemoryType u1_RetVal;

    if( u1OpStatus != (Dcm_OpStatusType)DCM_CANCEL )
    {
        u1_RetVal = Dcm_Dsp_DataTfrMng_CallProcTfrDataWriteFnc( u1OpStatus,
                                                                Dcm_Dsp_DataTfrMng_stTfrInfo.u1MemoryId,
                                                                Dcm_Dsp_DataTfrMng_stTfrInfo.u4MemoryAddress,
                                                                u4MemorySize,
                                                                ptMemoryData,
                                                                ptErrorCode );

        if( u1_RetVal == DCM_WRITE_OK )
        {
            Dcm_Dsp_DataTfrMng_stTfrInfo.u1Bsc = u1Bsc;
            Dcm_Dsp_DataTfrMng_u1TfrStatus = DCM_TFR_DL_PROCEED;
        }
        else if( ( u1_RetVal == DCM_WRITE_PENDING ) ||
                 ( u1_RetVal == DCM_WRITE_FORCE_RCRRP ) ||
                 ( u1_RetVal == DCM_WRITE_FAILED ) )
        {
            /* No process */
        }
        else
        {
            *ptErrorCode = DCM_E_GENERALREJECT;
            u1_RetVal = DCM_WRITE_FAILED;
        }
    }
    else
    {
        (void)Dcm_Dsp_DataTfrMng_CallProcTfrDataWriteFnc( u1OpStatus,           /* No return check required */
                                                          (uint8)0x00U,
                                                          (uint32)0x00000000U,
                                                          u4MemorySize,
                                                          ptMemoryData,
                                                          ptErrorCode );
        u1_RetVal = DCM_WRITE_OK;
    }

    return u1_RetVal;
}

#if ( DCM_UL_PROCESS_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DataTfrMng_ProcTfrDataRead                       */
/* Description   | Process of transfer data Read                            */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1OpStatus        : Operation state                 */
/*               | [IN] u1Bsc             : Block sequence counter          */
/*               | [IN/OUT] ptMemorySize  : Size of ptMemoryData            */
/*               | [OUT] ptMemoryData     : Memory data                     */
/*               | [OUT] ptErrorCode      : Error code                      */
/* Return Value  | Dcm_ReturnReadMemoryType                                 */
/*               |   DCM_READ_OK          : Read was successful             */
/*               |   DCM_READ_FAILED      : Read was not successful         */
/*               |   DCM_READ_PENDING     : Read is not yet finished        */
/*               |   DCM_READ_FORCE_RCRRP : RCRRP response                  */
/* Notes         | Call only when transfer status is DCM_TFR_UL_START or    */
/*               |   DCM_TFR_UL_PROCEED                                     */
/*               | Call From SID36.                                         */
/****************************************************************************/
FUNC( Dcm_ReturnReadMemoryType, DCM_CODE ) Dcm_Dsp_DataTfrMng_ProcTfrDataRead
(
    Dcm_OpStatusType u1OpStatus,
    uint8 u1Bsc,
    P2VAR( uint32, AUTOMATIC, DCM_APPL_DATA ) ptMemorySize,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptMemoryData,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
)
{
    Dcm_ReturnReadMemoryType u1_RetVal;

    if( u1OpStatus != (Dcm_OpStatusType)DCM_CANCEL )
    {
        u1_RetVal = Dcm_Dsp_DataTfrMng_CallProcTfrDataReadFnc( u1OpStatus,
                                                               Dcm_Dsp_DataTfrMng_stTfrInfo.u1MemoryId,
                                                               Dcm_Dsp_DataTfrMng_stTfrInfo.u4MemoryAddress,
                                                               ptMemorySize,
                                                               ptMemoryData,
                                                               ptErrorCode );

        if( u1_RetVal == DCM_READ_OK )
        {
            Dcm_Dsp_DataTfrMng_stTfrInfo.u1Bsc = u1Bsc;
            Dcm_Dsp_DataTfrMng_u1TfrStatus = DCM_TFR_UL_PROCEED;
        }
        else if( ( u1_RetVal == DCM_READ_PENDING ) ||
                 ( u1_RetVal == DCM_READ_FORCE_RCRRP ) ||
                 ( u1_RetVal == DCM_READ_FAILED ) )
        {
            /* No process */
        }
        else
        {
            *ptErrorCode = DCM_E_GENERALREJECT;
            u1_RetVal = DCM_READ_FAILED;
        }
    }
    else
    {
        (void)Dcm_Dsp_DataTfrMng_CallProcTfrDataReadFnc( u1OpStatus,           /* No return check required */
                                                          (uint8)0x00U,
                                                          (uint32)0x00000000U,
                                                          ptMemorySize,
                                                          ptMemoryData,
                                                          ptErrorCode );
        u1_RetVal = DCM_READ_OK;
    }

    return u1_RetVal;
}
#endif  /* DCM_UL_PROCESS_USE == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsp_DataTfrMng_ProcReqTfrExit                        */
/* Description   | Process of request transfer exit                         */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1OpStatus   : Operation state                      */
/*               | [IN] ptTransferRequestParameterRecord                    */
/*               |                   : Transfer request parameter record    */
/*               | [IN] u4TransferRequestParameterRecordSize                */
/*               |                   : Transfer request parameter record    */
/*               |                     size                                 */
/*               | [OUT] ptTransferResponseParameterRecord                  */
/*               |                   : Transfer response parameter record   */
/*               | [INOUT] ptTransferResponseParameterRecordSize            */
/*               |                   : Transfer response parameter record   */
/*               |                     size                                 */
/*               | [OUT] ptErrorCode : Error code                           */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK          : Request was successful                 */
/*               |   E_NOT_OK      : Request was not successful             */
/*               |   DCM_E_PENDING : Request is not yet finished            */
/* Notes         | Call From SID37.                                         */
/****************************************************************************/
#if ( DCM_UL_PROCESS_USE == STD_OFF )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DataTfrMng_ProcReqTfrExit
(
    Dcm_OpStatusType u1OpStatus,
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA ) ptTransferRequestParameterRecord,
    uint32 u4TransferRequestParameterRecordSize,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptTransferResponseParameterRecord,
    P2VAR( uint32, AUTOMATIC, DCM_APPL_DATA ) ptTransferResponseParameterRecordSize,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
)
{
    Std_ReturnType u1_RetVal;

    if( u1OpStatus != (Dcm_OpStatusType)DCM_CANCEL )
    {
        u1_RetVal = Dcm_Dsp_DataTfrMng_CallProcReqTfrExitFnc( u1OpStatus,
                                                              ptTransferRequestParameterRecord,
                                                              u4TransferRequestParameterRecordSize,
                                                              ptTransferResponseParameterRecord,
                                                              ptTransferResponseParameterRecordSize,
                                                              ptErrorCode );

        if( u1_RetVal == (Std_ReturnType)E_OK )
        {
            Dcm_Dsp_DataTfrMng_u1TfrStatus = DCM_TFR_DL_FIN;
        }
        else if( ( u1_RetVal == (Std_ReturnType)DCM_E_PENDING ) ||
                 ( u1_RetVal == (Std_ReturnType)E_NOT_OK ) )
        {
            /* No process */
        }
        else
        {
            *ptErrorCode = DCM_E_GENERALREJECT;
            u1_RetVal = E_NOT_OK;
        }
    }
    else
    {
        (void)Dcm_Dsp_DataTfrMng_CallProcReqTfrExitFnc( u1OpStatus,                             /* No return check required */
                                                        ptTransferRequestParameterRecord,
                                                        u4TransferRequestParameterRecordSize,
                                                        ptTransferResponseParameterRecord,
                                                        ptTransferResponseParameterRecordSize,
                                                        ptErrorCode );
        u1_RetVal = E_OK;
    }

    return u1_RetVal;
}
#endif  /* DCM_UL_PROCESS_USE == STD_OFF */
#if ( DCM_UL_PROCESS_USE == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DataTfrMng_ProcReqTfrExit
(
    Dcm_OpStatusType u1OpStatus,
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA ) ptTransferRequestParameterRecord,
    uint32 u4TransferRequestParameterRecordSize,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptTransferResponseParameterRecord,
    P2VAR( uint32, AUTOMATIC, DCM_APPL_DATA ) ptTransferResponseParameterRecordSize,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
)
{
    Std_ReturnType u1_RetVal;

    if( u1OpStatus != (Dcm_OpStatusType)DCM_CANCEL )
    {
        u1_RetVal = Dcm_Dsp_DataTfrMng_CallProcReqTfrExitFnc( u1OpStatus,
                                                              ptTransferRequestParameterRecord,
                                                              u4TransferRequestParameterRecordSize,
                                                              ptTransferResponseParameterRecord,
                                                              ptTransferResponseParameterRecordSize,
                                                              ptErrorCode );

        if( u1_RetVal == (Std_ReturnType)E_OK )
        {
            if( ( Dcm_Dsp_DataTfrMng_u1TfrStatus == DCM_TFR_UL_START ) ||
                ( Dcm_Dsp_DataTfrMng_u1TfrStatus == DCM_TFR_UL_PROCEED ) ||
                ( Dcm_Dsp_DataTfrMng_u1TfrStatus == DCM_TFR_UL_FIN ) )
            {
                Dcm_Dsp_DataTfrMng_u1TfrStatus = DCM_TFR_UL_FIN;
            }
            else
            {
                Dcm_Dsp_DataTfrMng_u1TfrStatus = DCM_TFR_DL_FIN;
            }
        }
        else if( ( u1_RetVal == (Std_ReturnType)DCM_E_PENDING ) ||
                 ( u1_RetVal == (Std_ReturnType)E_NOT_OK ) )
        {
            /* No process */
        }
        else
        {
            *ptErrorCode = DCM_E_GENERALREJECT;
            u1_RetVal = E_NOT_OK;
        }
    }
    else
    {
        (void)Dcm_Dsp_DataTfrMng_CallProcReqTfrExitFnc( u1OpStatus,                             /* No return check required */
                                                        ptTransferRequestParameterRecord,
                                                        u4TransferRequestParameterRecordSize,
                                                        ptTransferResponseParameterRecord,
                                                        ptTransferResponseParameterRecordSize,
                                                        ptErrorCode );
        u1_RetVal = E_OK;
    }

    return u1_RetVal;
}
#endif  /* DCM_UL_PROCESS_USE == STD_ON */

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

#endif /* DCM_ULDL_SERVICE_USE == STD_ON */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

