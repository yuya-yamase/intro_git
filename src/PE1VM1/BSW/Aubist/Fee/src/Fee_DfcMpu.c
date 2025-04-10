/* Fee_DfcMpu.c v2-0-0                                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/DFCMPU/CODE                                           */
/*--------------------------------------------------------------------------*/
/* Notes        | RH850/U2A16                                               */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Fee.h>
#include "../inc/Fee_Common.h"
#include "../inc/Fee_DfcMpu.h"
#include "../inc/Fee_DfcMpu_Internal.h"
#include "../inc/Fee_Lib.h"
#include "../inc/Fee_Mpu_Const.h"
#include "../inc/Fee_FlsWrp.h"

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define FEE_DFCMPU_COMPARE_BUFFER_SIZE          (FEE_DATA_FLASH_ECC_FIX_SIZE / FEE_BYTE_NUM_04) /* Buffer size for comparision in 4-byte unit */
#define FEE_DFCMPU_VALUE_0                      (0U)          /* Check value */
#define FEE_DFCMPU_ALIGN_MASK_4                 (0x00000003U) /* 4-byte alignment check */

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define FEE_START_SEC_CODE
#include <Fee_MemMap.h>

/****************************************************************************/
/* Function Name | Fee_DfcMpu_SyncRead                                      */
/* Description   | Function to read data from flash                         */
/* Preconditions |                                                          */
/* Parameters    | SourceAddress    : Flash address of source data          */
/*               | TargetAddressPtr : Pointer to buffer to store read data  */
/*               | Length           : Number of bytes for read              */
/* Return Value  | FEE_DFCMPU_RESULT_OK                                     */
/*               | FEE_DFCMPU_RESULT_NG_READ                                */
/* Notes         | This function returns FEE_DFCMPU_RESULT_OK               */
/*               | even if ECC error is detected.                           */
/*               | Length may be multiple of 2-byte.                        */
/****************************************************************************/
FUNC( uint8, FEE_CODE )
Fee_DfcMpu_SyncRead(
    uint32                           SourceAddress,
    P2VAR(uint8, AUTOMATIC, TYPEDEF) TargetAddressPtr,
    uint32                           Length
){
    uint8                 Rtn;
    Fls_Cdd_JobResultType ReadResult;

    ReadResult = Fee_FlsWrp_Cdd_Read( (Fls_AddressType)( SourceAddress - (uint32)FEE_DATA_FLASH_ADDRESS_START ), TargetAddressPtr, (Fls_LengthType)Length );
    if( ( ReadResult == (Fls_Cdd_JobResultType)FLS_CDD_RSP_OK ) ||
        ( ReadResult == (Fls_Cdd_JobResultType)FLS_CDD_RSP_NG_READ ) )
    {
        Rtn = FEE_DFCMPU_RESULT_OK;
    }
    else
    {
        Rtn = FEE_DFCMPU_RESULT_NG_READ;
        Fee_Lib_SetMemory( TargetAddressPtr, FEE_INIDAT_UINT8, (uint32)Length );
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_DfcMpu_SyncReadUint16                                */
/* Description   | Function to read 2-byte data from flash                  */
/* Preconditions |                                                          */
/* Parameters    | SourceAddress    : Flash address of source data          */
/*               | TargetAddressPtr : Pointer to buffer to store read data  */
/* Return Value  | FEE_DFCMPU_RESULT_OK                                     */
/*               | FEE_DFCMPU_RESULT_NG_READ                                */
/* Notes         | This function returns FEE_DFCMPU_RESULT_OK               */
/*               | even if ECC error is detected.                           */
/****************************************************************************/
FUNC( uint8, FEE_CODE )
Fee_DfcMpu_SyncReadUint16(
    uint32                            SourceAddress,
    P2VAR(uint16, AUTOMATIC, TYPEDEF) TargetAddressPtr
){
    uint8                 Rtn;
    uint8                 ReadBuffer[FEE_NUM_OF_BYTE_IN_UINT16];
    uint16                ReadDataMSByte0;
    uint16                ReadDataMSByte1;
    uint16                ReadData;
    Fls_Cdd_JobResultType ReadResult;

    ReadResult = Fee_FlsWrp_Cdd_Read( (Fls_AddressType)( SourceAddress - (uint32)FEE_DATA_FLASH_ADDRESS_START ), &ReadBuffer[0], (Fls_LengthType)FEE_BYTE_NUM_02 );
    if( ( ReadResult == (Fls_Cdd_JobResultType)FLS_CDD_RSP_OK ) ||
        ( ReadResult == (Fls_Cdd_JobResultType)FLS_CDD_RSP_NG_READ ) )
    {
        Rtn = FEE_DFCMPU_RESULT_OK;
        ReadDataMSByte0 = (uint16)((uint16)ReadBuffer[FEE_UINT16_MSBYTE_INDEX_0] << (uint16)FEE_NUM_OF_BITS_IN_1BYTE);
        ReadDataMSByte1 = (uint16)ReadBuffer[FEE_UINT16_MSBYTE_INDEX_1];
        ReadData = ReadDataMSByte0 + ReadDataMSByte1;
        *TargetAddressPtr = ReadData;

    }
    else
    {
        Rtn = FEE_DFCMPU_RESULT_NG_READ;
        *TargetAddressPtr = FEE_INIDAT_UINT16;
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_DfcMpu_SyncReadUint32                                */
/* Description   | Function to read 4-byte data from flash                  */
/* Preconditions |                                                          */
/* Parameters    | SourceAddress    : Flash address of source data          */
/*               | TargetAddressPtr : Pointer to buffer to store read data  */
/* Return Value  | FEE_DFCMPU_RESULT_OK                                     */
/*               | FEE_DFCMPU_RESULT_NG_READ                                */
/* Notes         | This function returns FEE_DFCMPU_RESULT_OK               */
/*               | even if ECC error is detected.                           */
/****************************************************************************/
FUNC( uint8, FEE_CODE )
Fee_DfcMpu_SyncReadUint32(
    uint32                            SourceAddress,
    P2VAR(uint32, AUTOMATIC, TYPEDEF) TargetAddressPtr
){
    uint8                 Rtn;
    uint8                 ReadBuffer[FEE_NUM_OF_BYTE_IN_UINT32];
    uint32                ReadData;
    uint32                ReadDataMSByte0;
    uint32                ReadDataMSByte1;
    uint32                ReadDataMSByte2;
    uint32                ReadDataMSByte3;
    Fls_Cdd_JobResultType ReadResult;

    ReadResult = Fee_FlsWrp_Cdd_Read( (Fls_AddressType)( SourceAddress - (uint32)FEE_DATA_FLASH_ADDRESS_START ), &ReadBuffer[0], (Fls_LengthType)FEE_BYTE_NUM_04 );
    if( ( ReadResult == (Fls_Cdd_JobResultType)FLS_CDD_RSP_OK ) ||
        ( ReadResult == (Fls_Cdd_JobResultType)FLS_CDD_RSP_NG_READ ) )
    {
        Rtn = FEE_DFCMPU_RESULT_OK;
        ReadDataMSByte0  = (uint32)ReadBuffer[FEE_UINT32_MSBYTE_INDEX_0] << (uint32)FEE_NUM_OF_BITS_IN_3BYTE;
        ReadDataMSByte1  = (uint32)ReadBuffer[FEE_UINT32_MSBYTE_INDEX_1] << (uint32)FEE_NUM_OF_BITS_IN_2BYTE;
        ReadDataMSByte2  = (uint32)ReadBuffer[FEE_UINT32_MSBYTE_INDEX_2] << (uint32)FEE_NUM_OF_BITS_IN_1BYTE;
        ReadDataMSByte3  = (uint32)ReadBuffer[FEE_UINT32_MSBYTE_INDEX_3];
        ReadData         = ReadDataMSByte0 + ReadDataMSByte1 + ReadDataMSByte2 + ReadDataMSByte3;
        *TargetAddressPtr = ReadData;

    }
    else
    {
        Rtn = FEE_DFCMPU_RESULT_NG_READ;
        *TargetAddressPtr = FEE_INIDAT_UINT32;
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_DfcMpu_SyncCompare_EccFixSize                        */
/* Description   | Function to compare data on flash                        */
/* Preconditions |                                                          */
/* Parameters    | SourceAddress    : Flash address of source data          */
/*               | TargetAddressPtr : Pointer to target data buffer         */
/* Return Value  | FEE_DFCMPU_RESULT_OK                                     */
/*               | FEE_DFCMPU_RESULT_BLANK                                  */
/*               | FEE_DFCMPU_RESULT_NG_COMPARE                             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, FEE_CODE )
Fee_DfcMpu_SyncCompare_EccFixSize(
    uint32                             SourceAddress,
    P2CONST(uint8, AUTOMATIC, TYPEDEF) TargetAddressPtr
){
    uint8                 Rtn;
    Fls_Cdd_JobResultType BlankCheckResult;
    uint8                 CompareResult;
    uint32                ReadBuffer[FEE_DFCMPU_COMPARE_BUFFER_SIZE];

    BlankCheckResult = Fee_FlsWrp_Cdd_BlankCheck( (Fls_AddressType)( SourceAddress - (uint32)FEE_DATA_FLASH_ADDRESS_START ), (Fls_LengthType)FEE_DATA_FLASH_ECC_FIX_SIZE );
    if( BlankCheckResult == (Fls_Cdd_JobResultType)FLS_CDD_RSP_OK )
    {
        Rtn = FEE_DFCMPU_RESULT_BLANK;
    }
    else if( BlankCheckResult == (Fls_Cdd_JobResultType)FLS_CDD_RSP_NG_BLANKCHECK )
    {
        /* Return value is not checked. */
        (void)Fee_DfcMpu_SyncRead( SourceAddress, (uint8 *)ReadBuffer, (uint32)FEE_DATA_FLASH_ECC_FIX_SIZE );
        CompareResult = Fee_Lib_CompareMemory( (uint8 *)ReadBuffer, TargetAddressPtr, (uint32)FEE_DATA_FLASH_ECC_FIX_SIZE );
        if( CompareResult == FEE_LIB_EQUAL )
        {
            Rtn = FEE_DFCMPU_RESULT_OK;
        }
        else
        {
            Rtn = FEE_DFCMPU_RESULT_NG_COMPARE;
        }
    }
    else
    {
        Rtn = FEE_DFCMPU_RESULT_NG_COMPARE;
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_DfcMpu_SyncBlankCheck                                */
/* Description   | Function to execute blank check on flash                 */
/* Preconditions |                                                          */
/* Parameters    | SourceAddress : Flash address of blank check             */
/*               | Length        : Number of bytes for blank check          */
/* Return Value  | FEE_DFCMPU_RESULT_OK                                     */
/*               | FEE_DFCMPU_RESULT_NG_BLANKCHECK                          */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, FEE_CODE )
Fee_DfcMpu_SyncBlankCheck(
    uint32 SourceAddress,
    uint32 Length
){
    uint8                 Rtn;
    Fls_Cdd_JobResultType BlankCheckResult;

    BlankCheckResult = Fee_FlsWrp_Cdd_BlankCheck( (Fls_AddressType)( SourceAddress - (uint32)FEE_DATA_FLASH_ADDRESS_START ), (Fls_LengthType)Length );
    if( BlankCheckResult == (Fls_Cdd_JobResultType)FLS_CDD_RSP_OK )
    {
        Rtn = FEE_DFCMPU_RESULT_OK;
    }
    else
    {
        Rtn = FEE_DFCMPU_RESULT_NG_BLANKCHECK;
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_DfcMpu_SyncNotBlankAddress                           */
/* Description   | Function to search not-blank address on flash            */
/* Preconditions |                                                          */
/* Parameters    | SourceAddress   : Flash address of blank check           */
/*               | Length          : Number of bytes for blank check        */
/*               | NotBlankAddress : Pointer to buffer to store             */
/*               |                   not-blank address                      */
/* Return Value  | FEE_DFCMPU_RESULT_OK                                     */
/*               | FEE_DFCMPU_RESULT_BLANK                                  */
/*               | FEE_DFCMPU_RESULT_ERROR                                  */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, FEE_CODE )
Fee_DfcMpu_SyncNotBlankAddress(
    uint32                            SourceAddress,
    uint32                            Length,
    P2VAR(uint32, AUTOMATIC, TYPEDEF) NotBlankAddress
){
    uint8                 Rtn;
    Fls_Cdd_JobResultType BlankCheckResult;
    Fls_AddressType       NotBlankRelAddr;

    BlankCheckResult = Fee_FlsWrp_Cdd_NotBlankAddress( (Fls_AddressType)( SourceAddress - (uint32)FEE_DATA_FLASH_ADDRESS_START ), (Fls_LengthType)Length, &NotBlankRelAddr );
    if( BlankCheckResult == (Fls_Cdd_JobResultType)FLS_CDD_RSP_OK )
    {
        Rtn = FEE_DFCMPU_RESULT_OK;
        *NotBlankAddress = NotBlankRelAddr + (uint32)FEE_DATA_FLASH_ADDRESS_START;
    }
    else if( BlankCheckResult == (Fls_Cdd_JobResultType)FLS_CDD_RSP_NG_ALLBLANK )
    {
        Rtn = FEE_DFCMPU_RESULT_BLANK;
    }
    else
    {
        Rtn = FEE_DFCMPU_RESULT_ERROR;
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_DfcMpu_DirectRead                                    */
/* Description   | Function to read data from flash                         */
/* Preconditions |                                                          */
/* Parameters    | SourceAddress    : Flash address of source data          */
/*               | TargetAddressPtr : Pointer to buffer to store read data  */
/*               | Length           : Number of bytes for read              */
/* Return Value  | FEE_DFCMPU_RESULT_OK                                     */
/*               | FEE_DFCMPU_RESULT_INTEGRITY_FAILED                       */
/*               | FEE_DFCMPU_RESULT_INOPERATIVE_HSM                        */
/*               | FEE_DFCMPU_RESULT_ERROR                                  */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, FEE_CODE )
Fee_DfcMpu_DirectRead(
    uint32                           SourceAddress,
    P2VAR(uint8, AUTOMATIC, TYPEDEF) TargetAddressPtr,
    uint32                           Length
){
    uint8                 Rtn;
    Std_ReturnType        CheckResult;
    Fls_Cdd_JobResultType ReadResult;

    CheckResult = Fee_DfcMpu_CheckConditionForRead( SourceAddress, Length );
    if( CheckResult == (Std_ReturnType)E_OK )
    {
        ReadResult = Fee_FlsWrp_Cdd_Read( (Fls_AddressType)SourceAddress, TargetAddressPtr, (Fls_LengthType)Length );

        switch( ReadResult )
        {
            case (Fls_Cdd_JobResultType)FLS_CDD_RSP_OK:
                Rtn = FEE_DFCMPU_RESULT_OK;
                break;
            case (Fls_Cdd_JobResultType)FLS_CDD_RSP_NG_READ:
                Rtn = FEE_DFCMPU_RESULT_INTEGRITY_FAILED;
                break;
            case (Fls_Cdd_JobResultType)FLS_CDD_RSP_NG_USED_HSM:
                Rtn = FEE_DFCMPU_RESULT_INOPERATIVE_HSM;
                break;
            default:
                Rtn = FEE_DFCMPU_RESULT_ERROR;
                break;
        }
    }
    else
    {
        Rtn = FEE_DFCMPU_RESULT_ERROR;
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_DfcMpu_DirectBlankCheck                              */
/* Description   | Function to execute blank check on flash                 */
/* Preconditions |                                                          */
/* Parameters    | SourceAddress : Flash address of blank check             */
/*               | Length        : Number of bytes for blank check          */
/* Return Value  | FEE_DFCMPU_RESULT_OK                                     */
/*               | FEE_DFCMPU_RESULT_NG_BLANKCHECK                          */
/*               | FEE_DFCMPU_RESULT_FATALERROR                             */
/*               | FEE_DFCMPU_RESULT_INOPERATIVE_HSM                        */
/*               | FEE_DFCMPU_RESULT_ERROR                                  */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, FEE_CODE )
Fee_DfcMpu_DirectBlankCheck(
    uint32 SourceAddress,
    uint32 Length
){
    uint8                 Rtn;
    Fls_Cdd_JobResultType BlankCheckResult;

    if( Length <= (uint32)FEE_DFAI_RW_SIZE_MAX )
    {
        BlankCheckResult = Fee_FlsWrp_Cdd_BlankCheck( SourceAddress, (Fls_LengthType)Length );

        switch( BlankCheckResult )
        {
            case (Fls_Cdd_JobResultType)FLS_CDD_RSP_OK:
                Rtn = FEE_DFCMPU_RESULT_OK;
                break;
            case (Fls_Cdd_JobResultType)FLS_CDD_RSP_NG_BLANKCHECK:
                Rtn = FEE_DFCMPU_RESULT_NG_BLANKCHECK;
                break;
            case (Fls_Cdd_JobResultType)FLS_CDD_RSP_NG_FATALFAILED:
                Rtn = FEE_DFCMPU_RESULT_FATALERROR;
                break;
            case (Fls_Cdd_JobResultType)FLS_CDD_RSP_NG_USED_HSM:
                Rtn = FEE_DFCMPU_RESULT_INOPERATIVE_HSM;
                break;
            default:
                Rtn = FEE_DFCMPU_RESULT_ERROR;
                break;
        }
    }
    else
    {
        Rtn = FEE_DFCMPU_RESULT_ERROR;
    }

    return Rtn;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Fee_DfcMpu_CheckConditionForRead                         */
/* Description   | Function to check condition for direct flash access      */
/* Preconditions |                                                          */
/* Parameters    | SourceAddress : Flash address of read or blank check     */
/*               | Length        : Number of bytes for read or blank check  */
/* Return Value  | E_OK                                                     */
/*               | E_NOT_OK                                                 */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, FEE_CODE )
Fee_DfcMpu_CheckConditionForRead(
    uint32 SourceAddress,
    uint32 Length
){
    Std_ReturnType   Rtn;

    Rtn = (Std_ReturnType)E_NOT_OK;
    if( ( SourceAddress & (uint32)FEE_DFCMPU_ALIGN_MASK_4 ) == (uint32)FEE_DFCMPU_VALUE_0 )
    {
        if( ( Length & (uint32)FEE_DFCMPU_ALIGN_MASK_4 ) == (uint32)FEE_DFCMPU_VALUE_0 )
        {
            if( Length <= (uint32)FEE_DFAI_RW_SIZE_MAX )
            {
                Rtn = (Std_ReturnType)E_OK;
            }
        }
    }

    return Rtn;
}

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  2-0-0          :2022/08/24                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
