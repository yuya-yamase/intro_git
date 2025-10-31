/* Fee_Mngdfc.c v2-1-0                                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/MNGDFC/CODE                                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Fee.h>

#include "../inc/Fee_Ram.h"
#include "../inc/Fee_Common.h"

#include "../inc/Fee_Mngdfc_Internal.h"

#include <Mscd_Common.h>

#include "../inc/Fee_ExConst.h"

#include "../inc/Fee_Dfc.h"
#include "../inc/Fee_DfcMpu.h"
#include "../inc/Fee_Mpu_Dev_Const.h"
#include "../inc/Fee_Lib.h"
#include "../inc/Fee_Legacy.h"
#include "../inc/Fee_PifExt.h"

#include "../inc/Fee_FlsWrp.h"

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Data Flash Control Management Data Related Definition */
/* Data Flash Control State */
#define FEE_MNGDFCIDLE      ((uint8)0x00U)      /* Idle */
#define FEE_MNGDFCWRITE     ((uint8)0x01U)      /* Writing */
#define FEE_MNGDFCERASE     ((uint8)0x02U)      /* Erasing */
#define FEE_MNGDFCBLANKCHK  ((uint8)0x03U)      /* Blank checking */
/* Continuous-write flag setting (error occurrence flag) */
#define FEE_CWFLG_DFCERRSTS ((uint16)0x0080U)   /* DFC error occurred */
#define FEE_CWFLG_VRFYERRSTS    ((uint16)0x0040U)   /* Verification error occurred */
/* Buffer index value 0 (for blank check/erase) */
#define FEE_CWINDEXINIT     ((uint8)0x00U)      /* Index0 */

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define FEE_CWFLG_INIT       ((uint16)0x0000U)  /* Flag initial */
#define FEE_CWNUMINIT        ((uint8)0x00U)    /* Initial number of data */

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define FEE_START_SEC_CODE
#include <Fee_MemMap.h>

/****************************************************************************/
/* Function Name | Fee_MngDfc_CheckRAM                                      */
/* Description   | Function to check RAMs.                                  */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Check result.                                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, FEE_CODE )
Fee_MngDfc_CheckRAM( void )
{
#if ( FEE_USE_REDUNDANCY_RAM == STD_ON )
    Std_ReturnType Rtn = E_NOT_OK;
    uint32         Counter;

    if((( Fee_MngDfcInfo.u1MngDFCStatus ^ Fee_MngDfcInfoSub.u1MngDFCStatus ) == (uint8)FEE_MIRROR_CHECK_UINT8 )
    && (( Fee_MngDfcInfo.u1CWriteIndex  ^ Fee_MngDfcInfoSub.u1CWriteIndex  ) == (uint8)FEE_MIRROR_CHECK_UINT8 )
    && (( Fee_MngDfcInfo.u1CWriteNum    ^ Fee_MngDfcInfoSub.u1CWriteNum    ) == (uint8)FEE_MIRROR_CHECK_UINT8 )
    && (( Fee_MngDfcInfo.u1RetryFlag    ^ Fee_MngDfcInfoSub.u1RetryFlag    ) == (uint8)FEE_MIRROR_CHECK_UINT8 ))
    {
        Rtn = E_OK;
        for ( Counter = 0U; Counter < (uint32)FEE_CWRITE_MAX; Counter++ )
        {
            if((( Fee_MngDfcInfo.u2CWriteDataLength[Counter]         ^ Fee_MngDfcInfoSub.u2CWriteDataLength[Counter]         ) != (uint16)FEE_MIRROR_CHECK_UINT16 )
            || (( Fee_MngDfcInfo.u2CWriteAddrOffset[Counter]         ^ Fee_MngDfcInfoSub.u2CWriteAddrOffset[Counter]         ) != (uint16)FEE_MIRROR_CHECK_UINT16 )
            || (( Fee_MngDfcInfo.u2CWriteFlag[Counter]               ^ Fee_MngDfcInfoSub.u2CWriteFlag[Counter]               ) != (uint16)FEE_MIRROR_CHECK_UINT16 )
            || (( Fee_MngDfcInfo.u4CWriteAddrBuf[Counter]            ^ Fee_MngDfcInfoSub.u4CWriteAddrBuf[Counter]            ) != (uint32)FEE_MIRROR_CHECK_UINT32 )
            || (  Fee_MngDfcInfo.ptu1CWriteDataAddr[Counter]        != Fee_MngDfcInfoSub.ptu1CWriteDataAddr[Counter] ))
            {
                Rtn = E_NOT_OK;
                break;
            }
        }
    }

    return Rtn;
#else /* FEE_USE_REDUNDANCY_RAM == STD_OFF */
    return E_OK;
#endif /* FEE_USE_REDUNDANCY_RAM */
}

/****************************************************************************/
/* Function Name | Fee_MngDfc_SetRAMSub                                     */
/* Description   | Function to set value to sub RAMs from main RAMs.        */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_MngDfc_SetRAMSub( void )
{
#if ( FEE_USE_REDUNDANCY_RAM == STD_ON )
    uint32 Counter;

    Fee_MngDfcInfoSub.u1MngDFCStatus = (uint8)(~Fee_MngDfcInfo.u1MngDFCStatus);
    Fee_MngDfcInfoSub.u1CWriteIndex  = (uint8)(~Fee_MngDfcInfo.u1CWriteIndex);
    Fee_MngDfcInfoSub.u1CWriteNum    = (uint8)(~Fee_MngDfcInfo.u1CWriteNum);
    Fee_MngDfcInfoSub.u1RetryFlag    = (uint8)(~Fee_MngDfcInfo.u1RetryFlag);
    for ( Counter = 0U; Counter < (uint32)FEE_CWRITE_MAX; Counter++ )
    {
        Fee_MngDfcInfoSub.u2CWriteDataLength[Counter] = (uint16)(~Fee_MngDfcInfo.u2CWriteDataLength[Counter]);
        Fee_MngDfcInfoSub.u2CWriteAddrOffset[Counter] = (uint16)(~Fee_MngDfcInfo.u2CWriteAddrOffset[Counter]);
        Fee_MngDfcInfoSub.u2CWriteFlag[Counter]       = (uint16)(~Fee_MngDfcInfo.u2CWriteFlag[Counter]);
        Fee_MngDfcInfoSub.u4CWriteAddrBuf[Counter]    = (uint32)(~Fee_MngDfcInfo.u4CWriteAddrBuf[Counter]);
        Fee_MngDfcInfoSub.ptu1CWriteDataAddr[Counter] = Fee_MngDfcInfo.ptu1CWriteDataAddr[Counter];
    }
#endif /* FEE_USE_REDUNDANCY_RAM == STD_ON */

    return;
}

/****************************************************************************/
/* Function Name | Fee_MngDfcForPrd                                         */
/* Description   | Data Flash Control Management for Periodic Processing    */
/* Preconditions | None                                                     */
/* Parameters    | u1_callmode : type of periodic process                   */
/* Return Value  | Result of processing                                     */
/*               | 0x00000005 : FEE_STATUS_BUSY : Processing                */
/*               | 0x00000003 : FEE_STATUS_DONE : Operation completed       */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_MngDfcForPrd( uint8 u1_callmode )
{
    uint32          u4tReturn;                          /* RETURN */
    uint32          u4tMngDFCResult;                    /* Data Flash Control Management Common Processing Results */

    /* Data Flash Control Management Common Process Call */
    u4tMngDFCResult = Fee_MngDfcCom( u1_callmode );
    if ( u4tMngDFCResult == FEE_STATUS_DONE )
    {
        /* Data Flash control management common processing result has completed operation */
        if ( Fee_MngDfcInfo.u1MngDFCStatus == FEE_MNGDFCWRITE )
        {
            /* Data Flash control state is being written */
            Fee_MngDfcEndWriteProcess();
            /* Set return value to run complete */
            u4tReturn = FEE_STATUS_DONE;
        }
        else if ( Fee_MngDfcInfo.u1MngDFCStatus == FEE_MNGDFCBLANKCHK )
        {
            /* Data Flash control state is blank checking */
            Fee_MngDfcEndBlanckCheckProcess();
            /* Set return value to run complete */
            u4tReturn = FEE_STATUS_DONE;
        }
        else
        {
            /* Data Flash control state is other (erased) */
            Fee_MngDfcEndEraseProcess();
            /* Set return value to run complete */
            u4tReturn = FEE_STATUS_DONE;
        }
    }
    else if ( u4tMngDFCResult == FEE_STATUS_EXIT )
    {
        /* Data Flash Control Management common processing result is being processed */
        /* Set return value while processing */
        u4tReturn = FEE_STATUS_BUSY;
    }
    else
    {
        /* Data Flash Control Management Common Processing Result is Other (Idle) */
        /* Set return value to run complete */
        u4tReturn = FEE_STATUS_DONE;
    }

    return u4tReturn;
}

/****************************************************************************/
/* Function Name | Fee_MngDfcEndWriteProcess                                */
/* Description   | Data Flash control management write termination          */
/*               | processing                                               */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, FEE_CODE) Fee_MngDfcEndWriteProcess( void )
{
    uint32          u4tCounter;                         /* Counter */
    uint32          u4tCWriteNum;                       /* Number of consecutive write data */
    uint32          u4tCWriteAddress;                   /* Continuous write address */
    P2CONST(uint8, AUTOMATIC, TYPEDEF) ptu1WriteDataAddr;                       /* Data comparison pointer */
    uint8           u1tCompareResult;

    /* Data Flash control state is being written */
    /* Flash operation terminated (To verify after this, finish Flash operation first.) */
    Fee_Dfc_End();
    /* Fetch the number of consecutive write data */
    u4tCWriteNum = (uint32)Fee_MngDfcInfo.u1CWriteNum;
    for ( u4tCounter = 0U; u4tCounter < u4tCWriteNum; u4tCounter++ )
    {
        if ( ( Fee_MngDfcInfo.u2CWriteFlag[u4tCounter] & FEE_CWFLG_VRFYERRCHK ) == FEE_CWFLG_VRFYERRCHK )
        {
            /* Verify if requested */
            u4tCWriteAddress = Fee_ConvAddr_RelativeToAbsolute( Fee_MngDfcInfo.u4CWriteAddrBuf[u4tCounter] );
            ptu1WriteDataAddr = Fee_MngDfcInfo.ptu1CWriteDataAddr[u4tCounter];
            u1tCompareResult = Fee_DfcMpu_SyncCompare_EccFixSize( u4tCWriteAddress, ptu1WriteDataAddr );
            if( u1tCompareResult != FEE_DFCMPU_RESULT_OK )
            {
                /* Set verify-error flag if verify-error */
                Fee_MngDfcInfo.u2CWriteFlag[u4tCounter] |= FEE_CWFLG_VRFYERRSTS;
                Fee_PifExt_WriteVerifyFailedNotification();
            }
        }
    }
    /* Set Data Flash Control State to Idle */
    Fee_MngDfcInfo.u1MngDFCStatus = FEE_MNGDFCIDLE;

    return;
}

/****************************************************************************/
/* Function Name | Fee_MngDfcEndBlanckCheckProcess                          */
/* Description   | Data Flash control management blank check termination    */
/*               | processing                                               */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, FEE_CODE) Fee_MngDfcEndBlanckCheckProcess( void )
{
    uint32          u4tBlankchkAddress;                 /* Nonblank address detected by blank check */

    /* Data Flash control state is blank checking */
    /* Check for errors */
    if ( ( Fee_MngDfcInfo.u2CWriteFlag[FEE_CWINDEXINIT] & FEE_CWFLG_DFCERRSTS ) == FEE_CWFLG_DFCERRSTS )
    {
        /* On error */
        /* FLAP retrieval function */
        u4tBlankchkAddress = Fee_Dfc_GetFLAP();
        /* Set to address buffer for continuous write */
        Fee_MngDfcInfo.u4CWriteAddrBuf[FEE_CWINDEXINIT] = Fee_ConvAddr_AbsToBaseRelative( u4tBlankchkAddress );
    }
    /* Flash operation terminated */
    Fee_Dfc_End();
    /* Set Data Flash Control State to Idle */
    Fee_MngDfcInfo.u1MngDFCStatus = FEE_MNGDFCIDLE;

    return;
}
/****************************************************************************/
/* Function Name | Fee_MngDfcEndEraseProcess                                */
/* Description   | Data Flash Control Management Erase termination          */
/*               | processing                                               */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, FEE_CODE) Fee_MngDfcEndEraseProcess( void )
{
    /* Data Flash control state is other (erased) */
    /* Flash operation terminated */
    Fee_Dfc_End();
    /* Set Data Flash Control State to Idle */
    Fee_MngDfcInfo.u1MngDFCStatus = FEE_MNGDFCIDLE;
    
    return;
}

/****************************************************************************/
/* Function Name | Fee_MngDfcCom                                            */
/* Description   | Data Flash Control and Management Common Process         */
/* Preconditions | None                                                     */
/* Parameters    | u1_callmode : type of periodic process                   */
/* Return Value  | Result of processing                                     */
/*               | 0x00000002 : FEE_STATUS_EXIT  : Processing               */
/*               | 0x00000003 : FEE_STATUS_DONE  : Operation completed      */
/*               | 0x00000004 : FEE_STATUS_CONT  : Idle                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_MngDfcCom( uint8 u1_callmode )
{
    uint32          u4tReturn;                          /* RETURN */
    uint32          u4tDFCResult;                       /* Status check results */
    
    /* Status check */
    u4tDFCResult = Fee_MngDfc_ExecDfcAndCheckStatus( u1_callmode );
    if ( u4tDFCResult == FEE_DFC_STATUS_BUSY )
    {
        /* BUSY */
        /* Set return value while processing */
        u4tReturn = FEE_STATUS_EXIT;
    }
    else
    {
        if ( Fee_MngDfcInfo.u1MngDFCStatus == FEE_MNGDFCIDLE )
        {
            /* Data Flash control state is idle */
            /* Set return value to idle */
            u4tReturn = FEE_STATUS_CONT;
        }
        else
        {
            if ( u4tDFCResult != FEE_DFC_STATUS_OK )
            {
                /* If the check result is not normal */
                /* Set D.F.C. error generation flag */
                Fee_MngDfcInfo.u2CWriteFlag[Fee_MngDfcInfo.u1CWriteIndex] |= FEE_CWFLG_DFCERRSTS;
            }
            if ( Fee_MngDfcInfo.u1MngDFCStatus == FEE_MNGDFCWRITE )
            {
                if( Fee_MngDfcInfo.u1RetryFlag == FEE_FLAG_ON )
                {
                    u4tReturn = Fee_MngDfcComRetry();
                }
                else
                {
                    if ( ( Fee_MngDfcInfo.u1CWriteIndex + (uint8)FEE_NEXT_CWRITENUM_OFFSET ) < Fee_MngDfcInfo.u1CWriteNum )
                    {
                        u4tReturn = Fee_MngDfcComCWrite( u4tDFCResult );
                    }
                    else
                    {
                        u4tReturn = FEE_STATUS_DONE;
                    }
                }
            }
            else
            {
                /* Data Flash control state is other (erasing or blank checking) */
                /* Set return value to run complete */
                u4tReturn = FEE_STATUS_DONE;
            }
        }
    }

    return u4tReturn;
}

/****************************************************************************/
/* Function Name | Fee_MngDfcComCWrite                                      */
/* Description   | Function to write continuity.                            */
/* Preconditions | None                                                     */
/* Parameters    | u4tDFCResult                                             */
/* Return Value  | FEE_STATUS_EXIT : On the way to execution                */
/*               | FEE_STATUS_DONE : The write was complete                 */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_MngDfcComCWrite(
    uint32 u4tDFCResult
){
    uint32          u4tReturn;

    /* Next data exist  */
    if ( ( u4tDFCResult != FEE_DFC_STATUS_OK )
      && ( ( Fee_MngDfcInfo.u2CWriteFlag[Fee_MngDfcInfo.u1CWriteIndex] & FEE_CWFLG_ERRSTOP ) == FEE_CWFLG_ERRSTOP ) )
    {
        u4tReturn = FEE_STATUS_DONE;
    }
    else
    {
        Fee_MngDfcInfo.u1CWriteIndex++;
        Fee_MngDfcReqWrite();

        u4tReturn = FEE_STATUS_EXIT;
    }

    return u4tReturn;
}

/****************************************************************************/
/* Function Name | Fee_MngDfcComRetry                                       */
/* Description   | Function to retry to write.                              */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | FEE_STATUS_EXIT : On the way to execution                */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_MngDfcComRetry( void )
{
    Fee_MngDfcReqWrite();

    return FEE_STATUS_EXIT;
}

/****************************************************************************/
/* Function Name | Fee_MngDfcReqWrite                                       */
/* Description   | Function to request writing.                             */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, FEE_CODE) Fee_MngDfcReqWrite( void )
{
    uint32          u4tAddress;
    P2CONST( uint8, AUTOMATIC, TYPEDEF )    ptu1Data;
    uint16          u2tLength;
    uint16          u2tOffset;
    uint16          u2tFlag;
    uint8           u1tIndex;

    u1tIndex = Fee_MngDfcInfo.u1CWriteIndex;
    u2tLength = Fee_MngDfcInfo.u2CWriteDataLength[u1tIndex];
    u2tOffset = Fee_MngDfcInfo.u2CWriteAddrOffset[u1tIndex];
    u4tAddress = Fee_ConvAddr_RelativeToAbsolute( Fee_MngDfcInfo.u4CWriteAddrBuf[u1tIndex] );
    u4tAddress += (uint32)u2tOffset;

    ptu1Data = &Fee_MngDfcInfo.ptu1CWriteDataAddr[u1tIndex][u2tOffset];
    u2tFlag = Fee_MngDfcInfo.u2CWriteFlag[u1tIndex];

    Fee_MngDfc_VolChkWrite( u4tAddress, ptu1Data, u2tLength, u2tFlag );

    return;
}


/****************************************************************************/
/* Function Name | Fee_AddCWriteBuf                                         */
/* Description   | Buffer addition processing for continuous writes         */
/* Preconditions | None                                                     */
/* Parameters    | uint32 u4Address  : Data Flash destination address       */
/*               | uint32 u4Data     : write data                           */
/*               | uint16 u2Length   : length of data to write              */
/*               | uint16 u2OffSet   : u4Offset from the beginning of Data  */
/*               |                     Write u2Length minutes from offset   */
/*               | uint16 u2Flg      : flag setting for continuous writing  */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, FEE_CODE) Fee_AddCWriteBuf( uint32 u4Address, P2CONST(uint8, AUTOMATIC, TYPEDEF) ptu1Src, uint16 u2Length, uint16 u2OffSet, uint16 u2Flg )
{
    uint8           u1tIndex;                           /* Write position */
    
    /* Set number of consecutive write data as write position */
    u1tIndex = Fee_MngDfcInfo.u1CWriteNum;
    
    /* ADDRESS BUFFER SETTING FOR CONTINUOUS WRITE */
    Fee_MngDfcInfo.u4CWriteAddrBuf[u1tIndex] = Fee_ConvAddr_AbsToBaseRelative( u4Address );

    /* Set data address for continuous write */
    Fee_MngDfcInfo.ptu1CWriteDataAddr[u1tIndex] = ptu1Src;

    /* Set Write Data length */
    Fee_MngDfcInfo.u2CWriteDataLength[u1tIndex] = u2Length;
    /* Set Write Addr Offset */
    Fee_MngDfcInfo.u2CWriteAddrOffset[u1tIndex] = u2OffSet;

    /* Flagset for continuous writing */
    Fee_MngDfcInfo.u2CWriteFlag[u1tIndex] = u2Flg;
    /* Increment number of consecutive write data */
    Fee_MngDfcInfo.u1CWriteNum++;
}

/****************************************************************************/
/* Function Name | Fee_StartCWrite                                          */
/* Description   | Continuous write start processing                        */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, FEE_CODE) Fee_StartCWrite( void )
{
    uint32          u4tAddress;                         /* ADDRESS */
    P2CONST( uint8, AUTOMATIC, TYPEDEF ) ptu1Src;                            /* Data pointer */
    uint16          u2tLength;                          /* Data Length */
    uint16          u2tOffset;                          /* Addr Offset */

    u2tLength = Fee_MngDfcInfo.u2CWriteDataLength[FEE_CWINDEXINIT];
    u2tOffset = Fee_MngDfcInfo.u2CWriteAddrOffset[FEE_CWINDEXINIT];
    /* Fetch write data from data Flash control management data (index = 0) */
    /* ADDRESS FOR CONTINUOUS WRITE [0] */
    u4tAddress = Fee_ConvAddr_RelativeToAbsolute( Fee_MngDfcInfo.u4CWriteAddrBuf[FEE_CWINDEXINIT] );
    u4tAddress += (uint32)u2tOffset;

    /* Data for continuous writing */
    ptu1Src = &Fee_MngDfcInfo.ptu1CWriteDataAddr[FEE_CWINDEXINIT][u2tOffset];

    Fee_MngDfc_VolChkWrite( u4tAddress, ptu1Src, u2tLength, Fee_MngDfcInfo.u2CWriteFlag[FEE_CWINDEXINIT] );
    /* Set data flash control state while writing */
    Fee_MngDfcInfo.u1MngDFCStatus = FEE_MNGDFCWRITE;

    return;
}
/****************************************************************************/
/* Function Name | Fee_StartErase                                           */
/* Description   | Erase start processing                                   */
/* Preconditions | uint8u1BlockNo: Erase block number                       */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, FEE_CODE) Fee_StartErase( uint8 u1BlockNo )
{
    uint32          u4tAddress;                         /* ADDRESS */

    /* Address calculation */
    u4tAddress = FEE_BLKSTARTADDRTBL[u1BlockNo];

    /* Buffer Initialization for Continuous Writing */
    Fee_ClearCWriteBuf();
    /* Erase function call */
    Fee_Dfc_Erase( u4tAddress );
    /* Set Data Flash Control State While Clearing */
    Fee_MngDfcInfo.u1MngDFCStatus = FEE_MNGDFCERASE;

    return;
}

/****************************************************************************/
/* Function Name | Fee_StartBlankCheck                                      */
/* Description   | blank check start processing                             */
/* Preconditions | uint 32 StartTailAddress  : blank check start address    */
/*               | uint 32 EndTopAddress     : blank check end address      */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, FEE_CODE) Fee_StartBlankCheck( uint32 u4StartTailAddress, uint32 u4EndTopAddress )
{
    /* Buffer Initialization for Continuous Writing */
    Fee_ClearCWriteBuf();
    /* Blank check function call */
    Fee_Dfc_BlankCheck( u4StartTailAddress, u4EndTopAddress, Fee_MaxBlankCheckNumber );
    /* Set data Flash control state during blank check */
    Fee_MngDfcInfo.u1MngDFCStatus = FEE_MNGDFCBLANKCHK;

    return;
}
/****************************************************************************/
/* Function Name | Fee_ClearCWriteBuf                                       */
/* Description   | Continuous write buffer initialization                   */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, FEE_CODE) Fee_ClearCWriteBuf( void )
{
    uint32          u4tCounter;                         /* Counter */

    for ( u4tCounter = 0U; u4tCounter < (uint32)FEE_CWRITE_MAX; u4tCounter++ )
    {
        /* ADDRESS BUFFER INITIALIZATION FOR CONTINUOUS WRITING */
        Fee_MngDfcInfo.u4CWriteAddrBuf[u4tCounter] = FEE_ADDRESS_INVALID;

        /* Initialize data address for continuous writing */
        Fee_MngDfcInfo.ptu1CWriteDataAddr[u4tCounter]= NULL_PTR;
        /* Flag Initialization for Continuous Write */
        Fee_MngDfcInfo.u2CWriteFlag[u4tCounter] = FEE_CWFLG_INIT; /* Initialize with 0x00U */
        Fee_MngDfcInfo.u2CWriteDataLength[u4tCounter] = FEE_LENGTH_INVALID;   /* DataLength Initialize */
        Fee_MngDfcInfo.u2CWriteAddrOffset[u4tCounter] = FEE_CWOFFSET_INVALID; /* Address Offset Initialize */
    }

    /* Data Flash Control State Initialization */
    Fee_MngDfcInfo.u1MngDFCStatus = FEE_MNGDFCIDLE;
     
    /* Initialize index of buffer for continuous write */
    Fee_MngDfcInfo.u1CWriteIndex = FEE_CWINDEXINIT;
    /* Number of data written continuously */
    Fee_MngDfcInfo.u1CWriteNum = FEE_CWNUMINIT;

    Fee_MngDfcInfo.u1RetryFlag = FEE_FLAG_OFF;

    return;
}
/****************************************************************************/
/* Function Name | Fee_GetMngDfcResult                                      */
/* Description   | Data Flash control result acquisition processing         */
/* Preconditions | uint32 *ptu4 Address: Last write/Blank error address     */
/* Parameters    | Result of processing                                     */
/*               | 0x00000000 : FEE_STATUS_OK : No error                    */
/*               | 0x00000001 : FEE_STATUS_NG : Error                       */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_GetMngDfcResult( P2VAR(uint32, AUTOMATIC, TYPEDEF) ptu4Address )
{
    uint32          u4tReturn;                          /* RETURN */
    uint32          u4tCounter;                         /* Counter */
    uint32          u4tCWriteNum;                       /* Number of consecutive write data */
    uint16          u2tCWriteFlag;                      /* Flags for continuous writing */

    /* Initialize return value without error */
    u4tReturn = FEE_STATUS_OK;
    /* Fetch the number of consecutive write data */
    u4tCWriteNum = Fee_MngDfcInfo.u1CWriteNum;

    if ( u4tCWriteNum == (uint32)FEE_CWRITENUM_ZERO )
    {
        /* Number of consecutive writes = 0: during erase/blank check */
        if ( (Fee_MngDfcInfo.u2CWriteFlag[FEE_CWINDEXINIT] & FEE_CWFLG_DFCERRSTS ) == FEE_CWFLG_DFCERRSTS )
        {
            /* If error flag is ON */
            /* Set return value with error */
            u4tReturn = FEE_STATUS_NG;
            /* Fetch a blank check address */
            if ( ptu4Address != NULL_PTR )
            {
                *ptu4Address = Fee_ConvAddr_RelativeToAbsolute( Fee_MngDfcInfo.u4CWriteAddrBuf[FEE_CWINDEXINIT] );
            }
        }
        else
        {
            /* Invalid address setting */
            if ( ptu4Address != NULL_PTR )
            {
                *ptu4Address = FEE_ADDRESS_INVALID;
            }
        }
    }
    else
    {
        /* In writing */
        for ( u4tCounter = 0U; ( u4tCounter < u4tCWriteNum ) && ( u4tReturn == FEE_STATUS_OK ); u4tCounter++ )
        {
            /* Get flags for continuous writing */
            u2tCWriteFlag = Fee_MngDfcInfo.u2CWriteFlag[u4tCounter];
            if ( ( ( u2tCWriteFlag & FEE_CWFLG_VRFYERRSTS ) == FEE_CWFLG_VRFYERRSTS )
              || ( ( u2tCWriteFlag & ( FEE_CWFLG_DFCERRCHK | FEE_CWFLG_DFCERRSTS ) )
                == ( FEE_CWFLG_DFCERRCHK | FEE_CWFLG_DFCERRSTS ) ) )
            {
                /* If the type of error to be checked is an error */
                /* Verify-check results are set only when confirmation is required */
                /* Set return value with error */
                u4tReturn = FEE_STATUS_NG;
            }
        }
        /* Fetch last write address */
        if ( ptu4Address != NULL_PTR )
        {
            *ptu4Address = Fee_ConvAddr_RelativeToAbsolute( Fee_MngDfcInfo.u4CWriteAddrBuf[u4tCWriteNum - (uint32)FEE_CWRITE_LAST_INDEX_OFFSET] );
        }
    }

    return u4tReturn;
}

/****************************************************************************/
/* Function Name | Fee_MngDfc_ExecDfcAndCheckStatus                         */
/* Description   |                                                          */
/* Preconditions | None                                                     */
/* Parameters    | u1_callmode : type of periodic process                   */
/* Return Value  |                                                          */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_MngDfc_ExecDfcAndCheckStatus( uint8 u1_callmode )
{
    uint32 Rtn;
    Std_ReturnType  u1_dfPrepare;

    Rtn = Fee_Dfc_ExecFlsMainFunction( u1_callmode );

    if( Fee_MngDfcInfo.u1MngDFCStatus == FEE_MNGDFCBLANKCHK )
    {
        /* Preparing for MemAcc data flash access. */
        u1_dfPrepare = Fee_FlsWrp_ExtDfPreExecution();
        if( u1_dfPrepare == (Std_ReturnType)E_OK )
        {
            Rtn = Fee_Dfc_ExecBlankCheck();
        }
        else
        {
            Rtn = FEE_DFC_STATUS_BUSY;
        }
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_MngDfc_VolChkWrite                                   */
/* Description   | Function to check voltage and write.                     */
/* Preconditions | None                                                     */
/* Parameters    | u4Address                                                */
/*               | ptu1Data                                                 */
/*               | u2Len                                                    */
/*               | u2Flag                                                   */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_MngDfc_VolChkWrite(
    const uint32 u4Address,
    P2CONST(uint8, AUTOMATIC, TYPEDEF) ptu1Data,
    const uint16 u2Len,
    const uint16 u2Flag
){
    Std_ReturnType srVolChkResult = E_OK;

    if(( u2Flag & FEE_CWFLG_VOLMINCHK ) == FEE_CWFLG_VOLMINCHK )
    {
        srVolChkResult = Mscd_Cnfm_CheckWcWriteHook();
    }

    if( srVolChkResult == (Std_ReturnType)E_OK )
    {
        Fee_Dfc_Write( u4Address, ptu1Data, u2Len );

        Fee_MngDfcInfo.u1RetryFlag = FEE_FLAG_OFF;
    }
    else
    {
        Fee_MngDfcInfo.u1RetryFlag = FEE_FLAG_ON;
    }

    return;
}

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/*  1-1-0          :2019/08/19                                              */
/*  2-0-0          :2022/08/24                                              */
/*  2-1-0          :2024/09/04                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
