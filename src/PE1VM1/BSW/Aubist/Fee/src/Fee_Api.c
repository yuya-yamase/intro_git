/* Fee_Api.c v2-1-0                                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/API/CODE                                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Fee.h>

#include "../inc/Fee_Mpu_Dev_Const.h"

/* MHA (Data Flash) I/F header */
#include "../inc/Fee_Legacy.h"

/* MHA header */
#include "../inc/Fee_Lib.h"

/* MHA library header */
#include "../inc/Fee_Common.h"

/* D.F.C. header */
#include "../inc/Fee_Dfc.h"

#include "../inc/Fee_Ram.h"

#include "../inc/Fee_FreeSpace.h"
#include "../inc/Fee_Record_Pos_Tbl.h"

#include "../inc/Fee_Api.h"
#include "../inc/Fee_Api_Internal.h"

#include "../inc/Fee_FlsWrp.h"
#include <NvM_Ext.h>
#include <Mscd_Common.h>

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define FEE_START_SEC_CONST_32
#include <Fee_MemMap.h>

/* Table for obtaining operating status */
CONST(AB_83_ConstV uint8, FEE_CONST) Fee_Legacy_GetStatusTBL[FEE_STATUSMAX] = 
{
    FEE_IDLING,     /* Idle: Waiting */
    FEE_WRITING,    /* WRITING: WRITING */
    FEE_REBUILDING, /* Reorganizing: Reorganizing data */
    FEE_ID_READING, /* Reading ID-specified data: Reading ID-specified data */
};

#define FEE_STOP_SEC_CONST_32
#include <Fee_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define FEE_START_SEC_CODE
#include <Fee_MemMap.h>

/****************************************************************************/
/* Function Name | Fee_Legacy_WriteData                                     */
/* Description   | Data write request                                       */
/* Preconditions | None                                                     */
/* Parameters    | uint 16 data _ id              : ID of data to write     */
/*               | const uint8 *data _ address    : first address of        */
/*               |                                  data written            */
/*               | uint8 No                       : Number of write area    */
/* Return Value  | Write request accepted result                            */
/*               | 0x00: FEE_REQUEST_ACCEPT       : Request accepted        */
/*               | 0x01: FEE_REQUEST_DECLINE      : Request denied          */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint8, FEE_CODE) Fee_Legacy_WriteData( uint16 data_id, P2CONST(uint8, AUTOMATIC, TYPEDEF) data_address, uint8 No )
{
    uint8           u1tReturn;                          /* RETURN */
    uint16          DataLength;
    Std_ReturnType      DataLenResult;

    u1tReturn = FEE_REQUEST_DECLINE;

    if ( data_address != NULL_PTR )
    {
        /* First address is not null */
        /* Are data write requests acceptable? */
        if ( Fee_CpuDtfInfo.u1ProcessStatus == FEE_STATUSIDLE )
        {
            /* Acceptable when running idle */
            DataLength = FEE_LENGTH_00;
            DataLenResult = Fee_Legacy_GetDataLength( data_id, &DataLength);
            if( DataLenResult == (Std_ReturnType) E_OK )
            {
                /* Initialize MHA management data */
                Fee_InitCpuDtfData( &Fee_CpuDtfInfo );
                /* Save Area Number */
                Fee_CpuDtfInfo.u1AreaNum = No;
                /* Area selection processing */
                Fee_SelectUseArea( &Fee_CpuDtfInfo );
                /* Save DATA-ID */
                Fee_CpuDtfInfo.u2DATA_ID = data_id;

                /* Save request data */
                Fee_CpuDtfInfo.ptu1ReqWriteAddr = data_address;
                Fee_CpuDtfInfo.u2ReqDataLen     = DataLength;

                /* Main timer counter settings */
                Fee_CpuDtfInfo.u4MainTimerCnt = Fee_LmtWriteTime;
                /* Set operational status to writing (STATUS_WRITE) */
                Fee_CpuDtfInfo.u1ProcessStatus = FEE_STATUSWRITE;
                /* Set main state to idle (MAIN_STATUS_WBIDLE) */
                Fee_CpuDtfInfo.u1MainStatus = FEE_MSTATUSWBIDLE;
                /* Final write record position read processing */
                /* Return value is not checked. */
                (void)Fee_RefLastWritePos( &Fee_CpuDtfInfo );

                /* Set the sub of RAMs. */
                Fee_Block_SetUseBlockInfoSub();
                Fee_Lib_SetCpuDtfDataSub();

                /* Set the return variable to accept requests */
                u1tReturn = FEE_REQUEST_ACCEPT;
            }
        }
    }
    
    /* Return request acceptance result to upper layer */
    return u1tReturn;
}

/****************************************************************************/
/* Function Name | Fee_Legacy_ReadData                                      */
/* Description   | Data read request (ID-specified read)                    */
/* Preconditions | None                                                     */
/* Parameters    | uint 16 data _ id               : ID of data to be read  */
/*               | uint8 No                        : number of reading area */
/* Return Value  | Result of accepting ID-specified read request            */
/*               | 0x00: FEE_REQUEST_ACCEPT       : Request accepted        */
/*               | 0x01: FEE_REQUEST_DECLINE      : Request denied          */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint8, FEE_CODE) Fee_Legacy_ReadData( uint16 data_id, uint8 No, P2VAR( uint8, AUTOMATIC, FEE_APPL_DATA ) DataBufferPtr )
{
    uint8           u1tReturn;                          /* RETURN */
    uint16          DataLength;
    Std_ReturnType  DataLenResult;

    u1tReturn = FEE_REQUEST_DECLINE;

    if ( DataBufferPtr != NULL_PTR )
    {
        /* Is data read request (ID-specified read) acceptable? */
        if ( Fee_CpuDtfInfo.u1ProcessStatus == FEE_STATUSIDLE )
        {
            /* Acceptable when running idle */
            DataLength = FEE_LENGTH_00;
            DataLenResult = Fee_Legacy_GetDataLength( data_id, &DataLength);
            if( DataLenResult == (Std_ReturnType) E_OK )
            {
                /* Initialize MHA management data */
                Fee_InitCpuDtfData( &Fee_CpuDtfInfo );
                /* Save Area Number */
                Fee_CpuDtfInfo.u1AreaNum = No;
                /* Area selection processing */
                Fee_SelectUseArea( &Fee_CpuDtfInfo );
                /* Save DATA-ID */
                Fee_CpuDtfInfo.u2DATA_ID = data_id;

                /* Save request data */
                Fee_CpuDtfInfo.u2ReqDataLen     = DataLength;
                Fee_CpuDtfInfo.ptu1ReqReadAddr  = DataBufferPtr;

                /* Main timer counter settings */
                Fee_CpuDtfInfo.u4MainTimerCnt = Fee_LmtIdReadTime;
                /* Set operational status to STATUS _ IDREAD */
                Fee_CpuDtfInfo.u1ProcessStatus = FEE_STATUSIDREAD;
                /* Set main state to idle (MAIN _ STATUS _ RIDLE) */
                Fee_CpuDtfInfo.u1MainStatus = FEE_MSTATUSRIDLE;
                /* Final write record position read processing */
                /* Return value is not checked. */
                (void)Fee_RefLastWritePos( &Fee_CpuDtfInfo );

                /* Set the sub of RAMs. */
                Fee_Block_SetUseBlockInfoSub();
                Fee_Lib_SetCpuDtfDataSub();

                /* Set the return variable to accept requests */
                u1tReturn = FEE_REQUEST_ACCEPT;
            }
        }
    }

    /* Return request acceptance result to upper layer */
    return u1tReturn;
}

/****************************************************************************/
/* Function Name | Fee_Legacy_Rebuild                                       */
/* Description   | Data reorganization request                              */
/* Preconditions | None                                                     */
/* Parameters    | uint8 No       : Number of the reorganization area       */
/*               | Restructuring Request Received Result                    */
/* Return Value  | 0x00: FEE_REQUEST_ACCEPT       : Request accepted        */
/*               | 0x01: FEE_REQUEST_DECLINE      : Request denied          */
/*               | 0x02  : FEE_REQUEST_IRBLD_CNFM_NOT_OK                    */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint8, FEE_CODE) Fee_Legacy_Rebuild( uint8 No )
{
    uint8           u1tReturn;                          /* RETURN */
    Std_ReturnType  ChkIntentRbld;

    /* Initialize return variable with request denied */
    u1tReturn = FEE_REQUEST_DECLINE;
    
    /* Are data restructuring requests acceptable? */
    if ( Fee_CpuDtfInfo.u1ProcessStatus == FEE_STATUSIDLE )
    {
        /* Inquire whether compulsory realignment can be implemented */
        ChkIntentRbld = Mscd_Cnfm_CheckIntentRbld( No );
        if( ChkIntentRbld == (Std_ReturnType)E_OK )
        {
            /* Acceptable when running idle */
            /* Initialize MHA management data */
            Fee_InitCpuDtfData( &Fee_CpuDtfInfo );

            /* Save Area Number */
            Fee_CpuDtfInfo.u1AreaNum = No;
            /* Area selection processing */
            Fee_SelectUseArea( &Fee_CpuDtfInfo );

            /* Main timer counter settings */
            Fee_CpuDtfInfo.u4MainTimerCnt = Fee_LmtRebuildTime;
            /* Set operational status to STATUS _ MOVE */
            Fee_CpuDtfInfo.u1ProcessStatus = FEE_STATUSMOVE;
            /* Set main state to idle (MAIN _ STATUS _ WBIDLE) */
            Fee_CpuDtfInfo.u1MainStatus = FEE_MSTATUSWBIDLE;
            /* Final write record position read processing */
            /* Return value is not checked. */
            (void)Fee_RefLastWritePos( &Fee_CpuDtfInfo );

            /* Set the sub of RAMs. */
            Fee_Block_SetUseBlockInfoSub();
            Fee_Lib_SetCpuDtfDataSub();

            /* Set the return variable to accept requests */
            u1tReturn = FEE_REQUEST_ACCEPT;
        }
        else
        {
            u1tReturn = FEE_REQUEST_IRBLD_CNFM_NOT_OK;
        }
    }

    /* Return request acceptance result to upper layer */
    return u1tReturn;
}

/****************************************************************************/
/* Function Name | Fee_Legacy_GetFreeSpace                                  */
/* Description   | Function to get free spaces sizes on data flash.         */
/* Preconditions | None                                                     */
/* Parameters    | AreaNo                                                   */
/*               | LimitSearchMngArea                                       */
/*               | LimitSearchDataArea                                      */
/*               | FreeSpaceInfoPtr                                         */
/* Return Value  | FEE_EXT_E_FRSP_OK                                        */
/*               | FEE_EXT_E_FRSP_BUSY                                      */
/*               | FEE_EXT_E_FRSP_AREA_FAULT                                */
/*               | FEE_EXT_E_FRSP_INTERNAL_ERROR                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Fee_ExtFreeSpaceReturnType, FEE_CODE )
Fee_Legacy_GetFreeSpace(
    uint8  AreaNo,
    uint16 LimitSearchMngArea,
    uint32 LimitSearchDataArea,
    P2VAR( Fee_ExtFreeSpaceInfoType, AUTOMATIC, TYPEDEF ) FreeSpaceInfoPtr
){
    Fee_ExtFreeSpaceReturnType  Rtn;
    MemIf_StatusType            DfcStatus;
    Fee_ExtFreeSpaceInfoType    TmpFreeSpaceInfo;
    Std_ReturnType              CheckCpuDtfDataResult;
    uint8                       ProcessStatus;

    CheckCpuDtfDataResult = Fee_Lib_CheckCpuDtfData();
    if( CheckCpuDtfDataResult == (Std_ReturnType)E_OK )
    {
        ProcessStatus = Fee_CpuDtfInfo.u1ProcessStatus;
        if(( ProcessStatus == FEE_STATUSIDLE )
        || ( ProcessStatus == FEE_STATUSIDREAD ))
        {
            DfcStatus = Fee_Dfc_GetStatus();
            if( DfcStatus == MEMIF_IDLE )
            {
                Rtn = Fee_FreeSpace_GetFreeSpace( AreaNo, LimitSearchMngArea, LimitSearchDataArea, &TmpFreeSpaceInfo );
            }
            else
            {
                Rtn = FEE_EXT_E_FRSP_BUSY;
            }
        }
        else
        {
            Rtn = FEE_EXT_E_FRSP_BUSY;
        }
    }
    else
    {
        Rtn = FEE_EXT_E_FRSP_INTERNAL_ERROR;
    }

    if( Rtn == (Fee_ExtFreeSpaceReturnType)FEE_EXT_E_FRSP_OK )
    {
        FreeSpaceInfoPtr->Result       = TmpFreeSpaceInfo.Result;
        FreeSpaceInfoPtr->RcrdNum      = TmpFreeSpaceInfo.RcrdNum;
        FreeSpaceInfoPtr->DataAreaByte = TmpFreeSpaceInfo.DataAreaByte;
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_Legacy_PwonInit                                      */
/* Description   | Data Flash driver initialization request (at reset)      */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, FEE_CODE) Fee_Legacy_PwonInit( void )
{
    Fee_Driver_Init();

    /* Notify when to reset */
    Fee_ResetInitHook();

     Fee_Legacy_SetRAMAllSub();

   /* Return to function call */
    return;
}

/****************************************************************************/
/* Function Name | Fee_Legacy_Abort                                         */
/* Description   | Data Flash driver forced initialization                  */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, FEE_CODE) Fee_Legacy_Abort( void )
{
    Std_ReturnType CancelResult;

    CancelResult = Fee_Driver_Cancel();
    if( CancelResult == (Std_ReturnType)E_OK )
    {
        Fee_Legacy_SetRAMAllSub();
    }

    return;
}

/****************************************************************************/
/* Function Name | Fee_Legacy_GetStatus                                     */
/* Description   | Data Flash operation status acquisition request          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Data Flash operating status                              */
/*               |   0x00 : FEE_IDLING       : Waiting                      */
/*               |   0x01 : FEE_WRITING      : Writing                      */
/*               |   0x02: FEE_ID_READING    : Reading ID designation       */
/*               |   0x06: FEE_REBUILDING    : Reorganizing data            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint8, FEE_CODE) Fee_Legacy_GetStatus( void )
{
    uint8               u1tReturn;                      /* RETURN */
    uint8               u1tStateInfo;                   /* for operating state storage */
    MemIf_StatusType    DfcStatus;                      /* For storing DFC operating state */
    

    /* INITIALIZED WITH RETURN VARIABLES WAITING */
    u1tReturn = FEE_IDLING;
    /* Eject operating status */
    u1tStateInfo = Fee_CpuDtfInfo.u1ProcessStatus;

    if ( u1tStateInfo < FEE_STATUSMAX )
    {
        /* If condition is within normal range */
        /* get data flash working state */
        u1tReturn = Fee_Legacy_GetStatusTBL[u1tStateInfo];
    }

    if ( u1tReturn == FEE_IDLING )
    {
        /* If return is waiting, check if DFC is not working */
        DfcStatus = Fee_Dfc_GetStatus();
        
        if( DfcStatus != MEMIF_IDLE )
        {
            u1tReturn = FEE_DFC_ERROR;
        }
        else
        {
            /* No process to keep Idling status */
        }
    }

    /* Return data Flash behavior state to function caller */
    return u1tReturn;
}

/****************************************************************************/
/* Function Name | Fee_Legacy_PeriodicFunc                                  */
/* Description   | Data Flash periodic processing                           */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, FEE_CODE) Fee_Legacy_PeriodicFunc( void )
{
    Std_ReturnType CheckResult;
    boolean isLockStatus;

    /* Check RAMs. */
    CheckResult = Fee_Legacy_CheckRAMAll();
    if( CheckResult != (Std_ReturnType)E_OK )
    {
        Fee_CpuDtfInfo.u1Result = FEE_RSP_GARBLED_RAM;
    }

    /* Check main timer value */
    if ( Fee_CpuDtfInfo.u4MainTimerCnt != (uint32)FEE_TM_COUNT_ZERO )
    {
        /* Main timer is running */
        /* Timer count decrement */
        Fee_CpuDtfInfo.u4MainTimerCnt--;
    }
    else
    {
        /* Timeout */
        /* Set processing result to timeout (RSP _ TIMEOUT) */
        Fee_CpuDtfInfo.u1Result = FEE_RSP_TIMEOUT;
    }
    /* Check the D.F.C. timer count value */
    if ( Fee_CpuDtfInfo.u4DFCTimerCnt != (uint32)FEE_TM_COUNT_ZERO )
    {
        /* Check lock status, decrement timer if not locked */
        isLockStatus = Fee_FlsWrp_IsLockStatus();
        if( (boolean)TRUE != isLockStatus )
        {
            /* The D.F.C. timer is running */
            /* Timer count decrement */
            Fee_CpuDtfInfo.u4DFCTimerCnt--;
        }
    }
    else
    {
        /* Timeout */
        /* Set processing result to timeout (RSP _ TIMEOUT) */
        Fee_CpuDtfInfo.u1Result = FEE_RSP_TIMEOUT;
    }

    /* Data Flash Periodic (common) */
    Fee_Periodic_FuncCommon( (uint8)FEE_CALL_TIMING_PERIODIC );

    /* Set the sub RAMs. */
    Fee_Legacy_SetRAMAllSub();

    /* Return to function call */
    return;
}

/****************************************************************************/
/* Function Name | Fee_Legacy_NonPeriodicFunc                               */
/* Description   | Data Flash irregular processing                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, FEE_CODE) Fee_Legacy_NonPeriodicFunc( void )
{
    Std_ReturnType CheckResult;

    /* Check RAMs. */
    CheckResult = Fee_Legacy_CheckRAMAll();
    if( CheckResult != (Std_ReturnType)E_OK )
    {
        Fee_CpuDtfInfo.u1Result = FEE_RSP_GARBLED_RAM;
    }

    /* Data Flash Periodic (common) */
    Fee_Periodic_FuncCommon( (uint8)FEE_CALL_TIMING_NOT_PERIODIC );

    /* Set the sub RAMs. */
    Fee_Legacy_SetRAMAllSub();

    return;
}

/****************************************************************************/
/* Function Name | Fee_Periodic_FuncCommon                                  */
/* Description   | Data Flash periodic processing (common)                  */
/* Preconditions | None                                                     */
/* Parameters    | u1_callmode : type of periodic process                   */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, FEE_CODE) Fee_Periodic_FuncCommon( uint8 u1_callmode )
{
    /* Flash access permission decision */
    Fee_FlashAccessCheck();
    
    /* Check the operating status because AreaNum is set to an impossible value for initializing */
    if ( Fee_CpuDtfInfo.u1ProcessStatus != FEE_STATUSIDLE )
    {
        /* Initialize searchable count */
        Fee_CpuDtfInfo.u4SrchRemainCount = Fee_CpuDtfInfo.ptstAreaInf->u2MaxReadNum;
    }
    /* Data Flash periodic processing execution instruction */
    Fee_ExecPeriodic( &Fee_CpuDtfInfo , u1_callmode );

    /* Return to function call */
    return;
}

/****************************************************************************/
/* Function Name | Fee_Legacy_GetDataLength                                 */
/* Description   | Get specified data ID and data length of specified area  */
/* Preconditions | None                                                     */
/* Parameters    | DATA ID                                                  */
/* Return Value  | Area number                                              */
/*               | specified data ID and data length of specified area      */
/*               | Result of data length acquisition                        */
/* Notes         | Global variable  :Identity information table             */
/****************************************************************************/
FUNC(Std_ReturnType, FEE_CODE) Fee_Legacy_GetDataLength( uint16 data_id , P2VAR(uint16, AUTOMATIC, TYPEDEF) DataLength )
{
    NvM_BlockIdType NvRamBlockId;
    Std_ReturnType  Rtn = E_NOT_OK;
    Std_ReturnType  BlockLenResult;

    /* Calculate Block Id */
    NvRamBlockId = (NvM_BlockIdType)( data_id >> Fee_DatasetSelectionBits );

    BlockLenResult = NvM_ExtGetNvBlockLength( NvRamBlockId , DataLength );

    if( BlockLenResult == (Std_ReturnType) E_OK )
    {
        /* Check a range of length */
        if( *DataLength < (uint16)FEE_DATA_LENGTH_MAX )
        {
            if( *DataLength > (uint16)FEE_LENGTH_00 )
            {
                Rtn = E_OK;
            }
        }
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee _ FlashAccessCheck (Flash accessibility check)       */
/* Description   | Determine whether access to Flash is available           */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, FEE_CODE) Fee_FlashAccessCheck( void )
{
    uint8               CheckResult = FEE_RSP_OK;
    MemIf_StatusType    DfcStatus;
    uint32              u4FlashAccessState;   /* Flash access permission judgment result */

    /* Check the Fls module status */
    DfcStatus = Fee_Dfc_GetStatus();
    if( DfcStatus == MEMIF_UNINIT )
    {
        CheckResult = FEE_RSP_NG_DTF_CTRL;
    }
    else if( DfcStatus == MEMIF_BUSY_INTERNAL )
    {
        CheckResult = FEE_RSP_NG_DTF_CTRL;
    }
    else
    {
        /* No process */
    }

    /* Flash access permission decision */
    u4FlashAccessState = Fee_FlashAccessCheckHook();

    switch ( u4FlashAccessState )
    {
        case FEE_FLASH_ACCESS_DISABLE:
            /* If Flash is not accessible, set processing result to Data Flash controller error */
            CheckResult = FEE_RSP_NG_DTF_CTRL;
            break;
        case FEE_FLASH_ACCESS_WRITE_DISABLE:
            if ((FEE_STATUSWRITE == Fee_CpuDtfInfo.u1ProcessStatus)
             || (FEE_STATUSMOVE == Fee_CpuDtfInfo.u1ProcessStatus))
            {
                /* For non-writable and write-performing operations (write/reorganize/initialize) */
                /* Set processing result to Data Flash controller error */
                CheckResult = FEE_RSP_NG_DTF_CTRL;
            }
            break;
        case FEE_FLASH_ACCESS_READ_DISABLE:
        case FEE_FLASH_ACCESS_ENABLE:
        default:
            /* No process */
            break;
    }

    if( CheckResult != FEE_RSP_OK )
    {
        Fee_CpuDtfInfo.u1Result = CheckResult;
    }

    return;
}

/****************************************************************************/
/* Function Name | Fee_Legacy_CheckRAMAll                                   */
/* Description   | Function to check RAMs of all units.                     */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, FEE_CODE )
Fee_Legacy_CheckRAMAll( void )
{
    Std_ReturnType Rtn;

    Rtn = Fee_Dfc_CheckRAM();
    if( Rtn == (Std_ReturnType)E_OK )
    {
        Rtn = Fee_MngDfc_CheckRAM();
        if( Rtn == (Std_ReturnType)E_OK )
        {
            Rtn = Fee_Record_CheckRAM();
            if( Rtn == (Std_ReturnType)E_OK )
            {
                Rtn = Fee_Block_CheckUseBlockInfo();
                if( Rtn == (Std_ReturnType)E_OK )
                {
                    Rtn = Fee_Lib_CheckCpuDtfData();
                }
            }
        }
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_Legacy_SetRAMAllSub                                  */
/* Description   | Function to set value to sub RAMs of all units.          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Check result.                                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_Legacy_SetRAMAllSub( void )
{
    Fee_Dfc_SetRAMSub();
    Fee_MngDfc_SetRAMSub();
    Fee_Record_SetRAMSub();
    Fee_Block_SetUseBlockInfoSub();
    Fee_Lib_SetCpuDtfDataSub();

    return;
}

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/*  1-1-0          :2019/08/27                                              */
/*  2-0-0          :2022/08/24                                              */
/*  2-1-0          :2024/09/04                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
