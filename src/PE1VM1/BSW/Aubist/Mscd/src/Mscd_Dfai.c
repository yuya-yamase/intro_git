/* Mscd_Dfai.c v2-0-0                                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | MSCD/DFAI/CODE                                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Mscd.h>
#include <Fee_Ext.h>

#include <Mscd_Common.h>
#include "../inc/Mscd_Dfai.h"

#include "../cfg/Mscd_Lcfg.h"
#include "../inc/Mscd_Suspend.h"
#include "../inc/Mscd_Dfai_Internal.h"

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define MSCD_START_SEC_CODE
#include <Mscd_MemMap.h>

#if( MSCD_DFAI_USE == STD_ON )
/****************************************************************************/
/* Function Name | Mscd_Dfai_Write                                          */
/* Description   | Write request to memory medium                           */
/* Preconditions |                                                          */
/* Parameters    | u1MemoryIdentifier   : memory medium ID                  */
/*               |              * For future expansion. Currently fixed at 0*/
/*               | u4Address            : write request address             */
/*               | ptSrcPtr             : first pointer of data written     */
/*               | u4Length             : write data length                 */
/* Return Value  | Mscd_Dfai_ReturnType                                     */
/*               |           MSCD_DFAI_JOB_ACCEPT                           */
/*               |           MSCD_DFAI_JOB_NOT_ACCEPT                       */
/*               |           MSCD_DFAI_JOB_INOPERATIVE_HSM                  */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Mscd_Dfai_ReturnType, MSCD_CODE)
Mscd_Dfai_Write( uint8 u1MemoryIdentifier, uint32 u4Address, P2CONST(uint8, AUTOMATIC, MSCD_APPL_CONST) ptSrcPtr, uint32 u4Length )
{
    Mscd_Dfai_ReturnType u1Result;
    uint8 u1Suspend_state;
    Std_ReturnType u1Param_check_result;
    Fee_ExtDirect_ReturnType u1OpeResult;

    u1Result = MSCD_DFAI_JOB_NOT_ACCEPT;

   /* Only perform when MS is stopped */
    u1Suspend_state = Mscd_Suspend_GetUserSuspendState();
    if( MSCD_SUSPEND_MS_RUN != u1Suspend_state )
    {
        /* Check if the request parameters are within the user memory area specified in the config */
        u1Param_check_result = Mscd_Dfai_CheckAddrRange( u4Address, u4Length );

        if( u1Param_check_result == (Std_ReturnType)E_OK )
        {
            u1OpeResult = Fee_ExtDirectWrite( u4Address, u4Length, ptSrcPtr );

            if ( u1OpeResult == (Fee_ExtDirect_ReturnType)FEE_EXT_DRCT_JOB_ACCEPT )
            {
                u1Result = MSCD_DFAI_JOB_ACCEPT;
            }
            else if ( u1OpeResult == (Fee_ExtDirect_ReturnType)FEE_EXT_DRCT_JOB_INOPERATIVE_HSM )
            {
                u1Result = MSCD_DFAI_JOB_INOPERATIVE_HSM;
            }
            else
            {
                u1Result = MSCD_DFAI_JOB_NOT_ACCEPT;
            }
        }
    }
    return( u1Result );
}
#endif  /* MSCD_DFAI_USE == STD_ON */

#if( MSCD_DFAI_USE == STD_ON )
/****************************************************************************/
/* Function Name | Mscd_Dfai_Erase                                          */
/* Description   | Request to erase to memory medium                        */
/* Preconditions |                                                          */
/* Parameters    | u1MemoryIdentifier   : memory medium ID                  */
/*               |      * For future expansion. Currently fixed at 0        */
/*               | u4Address            : erasable address                  */
/*               |      * Relative address at beginning of sector           */
/*               | u4Length             : Erase data length                 */
/* Return Value  | Mscd_Dfai_ReturnType                                     */
/*               |           MSCD_DFAI_JOB_ACCEPT                           */
/*               |           MSCD_DFAI_JOB_NOT_ACCEPT                       */
/*               |           MSCD_DFAI_JOB_INOPERATIVE_HSM                  */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Mscd_Dfai_ReturnType, MSCD_CODE)
Mscd_Dfai_Erase( uint8 u1MemoryIdentifier, uint32 u4Address, uint32 u4Length )
{
    Mscd_Dfai_ReturnType u1Result;
    uint8 u1Suspend_state;
    uint16 u2Req_sector_num;
    Std_ReturnType u1Param_check_result;
    Fee_ExtDirect_ReturnType u1OpeResult;

    u1Result = MSCD_DFAI_JOB_NOT_ACCEPT;

    /* Only perform when MS is stopped */
    u1Suspend_state = Mscd_Suspend_GetUserSuspendState();
    if( MSCD_SUSPEND_MS_RUN != u1Suspend_state )
    {

        /* Check if the request parameters are within the user memory area specified in the config */
        u1Param_check_result = Mscd_Dfai_CheckAddrRange( u4Address, u4Length );

        if( u1Param_check_result == (Std_ReturnType)E_OK )
        {
            /* Calculating the number of sectors to erase from u4Length. */
            u2Req_sector_num = (uint16)( (u4Length + ((uint32)MSCD_DFAI_FLASH_SECTOR_SIZE - (uint32)MSCD_DFAI_1LSB) ) / (uint32)MSCD_DFAI_FLASH_SECTOR_SIZE );

            u1OpeResult = Fee_ExtDirectErase( u4Address, u2Req_sector_num );

            if ( u1OpeResult == (Fee_ExtDirect_ReturnType)FEE_EXT_DRCT_JOB_ACCEPT )
            {
                u1Result = MSCD_DFAI_JOB_ACCEPT;
            }
            else if ( u1OpeResult == (Fee_ExtDirect_ReturnType)FEE_EXT_DRCT_JOB_INOPERATIVE_HSM )
            {
                u1Result = MSCD_DFAI_JOB_INOPERATIVE_HSM;
            }
            else
            {
                u1Result = MSCD_DFAI_JOB_NOT_ACCEPT;
            }
        }
    }
    return( u1Result );
}
#endif  /* MSCD_DFAI_USE == STD_ON */

#if( MSCD_DFAI_USE == STD_ON )
/****************************************************************************/
/* Function Name | Mscd_Dfai_ MainFunction (Driver Periodic)                */
/* Description   | Allow asynchronous processing to proceed                 */
/* Preconditions |                                                          */
/* Parameters    | u1MemoryIdentifier   : memory medium ID                  */
/*               |          * For future expansion. Currently fixed at 0    */
/* Return Value  | None                                                     */
/* Notes         | Consider building logic for memory medium IDs in the future and */
/*               | Realize with a function instead of name substitution     */
/****************************************************************************/
FUNC(void, MSCD_CODE)
Mscd_Dfai_MainFunction( uint8 u1MemoryIdentifier )
{
    uint8 u1Suspend_state;

    u1Suspend_state = Mscd_Suspend_GetUserSuspendState();
    if( MSCD_SUSPEND_MS_RUN != u1Suspend_state )
    {
        Fee_ExtDirectMainFunction( );
    }
    return;
}
#endif  /* MSCD_DFAI_USE == STD_ON */

#if( MSCD_DFAI_USE == STD_ON )
/****************************************************************************/
/* Function Name | Mscd_Dfai_GetStatus                                      */
/* Description   | Service to return the status of the flash driver.        */
/* Preconditions | None                                                     */
/* Parameters    | u1MemoryIdentifier                                       */
/* Return Value  | Mscd_Dfai_StatusType                                     */
/*               |      MSCD_DFAI_STATE_IDLE                                */
/*               |      MSCD_DFAI_STATE_BUSY                                */
/*               |      MSCD_DFAI_STATE_ERROR                               */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Mscd_Dfai_StatusType, MSCD_CODE )
Mscd_Dfai_GetStatus(
    uint8 u1MemoryIdentifier
){
    Mscd_Dfai_StatusType    Rtn     = MSCD_DFAI_STATE_ERROR;
    Fee_ExtDirectStatusType FeeStatus;
    uint8                   SuspendState;

    SuspendState = Mscd_Suspend_GetUserSuspendState();
    if( MSCD_SUSPEND_MS_RUN != SuspendState )
    {
        FeeStatus = Fee_ExtDirectGetStatus();
        
        if( FeeStatus == (Fee_ExtDirectStatusType)FEE_EXT_DRCT_STATUS_IDLE )
        {
            Rtn = MSCD_DFAI_STATE_IDLE;
        }
        else if( FeeStatus == (Fee_ExtDirectStatusType)FEE_EXT_DRCT_STATUS_BUSY )
        {
            Rtn = MSCD_DFAI_STATE_BUSY;
        }
        else if( FeeStatus == (Fee_ExtDirectStatusType)FEE_EXT_DRCT_STATUS_ERROR )
        {
            Rtn = MSCD_DFAI_STATE_ERROR;
        }
        else
        {
            /* RAM garbled. */
            Rtn = MSCD_DFAI_STATE_ERROR;
        }
    }

    return( Rtn );
}
#endif  /* MSCD_DFAI_USE == STD_ON */

#if( MSCD_DFAI_USE == STD_ON )
/****************************************************************************/
/* Function Name | Mscd_Dfai_GetJobResult                                   */
/* Description   | Service to return the job result of the flash driver     */
/* Preconditions |                                                          */
/* Parameters    | u1MemoryIdentifier                                       */
/* Return Value  | Mscd_Dfai_ReturnType                                     */
/*               |      MSCD_DFAI_JOB_OK                                    */
/*               |      MSCD_DFAI_JOB_BUSY                                  */
/*               |      MSCD_DFAI_JOB_ERROR                                 */
/*               |      MSCD_DFAI_JOB_CANCELED                              */
/*               |      MSCD_DFAI_JOB_FATALERROR                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Mscd_Dfai_ReturnType, MSCD_CODE)
Mscd_Dfai_GetJobResult( uint8 u1MemoryIdentifier )
{
    Mscd_Dfai_ReturnType u1Result;
    Fee_ExtDirect_ReturnType u1Req_result;

    u1Req_result = Fee_ExtGetDirectJobResult();

    /* RETURN CONVERSION */
    switch( u1Req_result )
    {
        case FEE_EXT_DRCT_JOB_OK:
            u1Result = MSCD_DFAI_JOB_OK;
            break;
        case FEE_EXT_DRCT_JOB_BUSY:
            u1Result = MSCD_DFAI_JOB_BUSY;
            break;
        case FEE_EXT_DRCT_JOB_CANCELED:
            u1Result = MSCD_DFAI_JOB_CANCELED;
            break;
        case FEE_EXT_DRCT_JOB_FATALERROR:
            u1Result = MSCD_DFAI_JOB_FATALERROR;
            break;
        case FEE_EXT_DRCT_JOB_ERROR:
        default: /* Treat ram garbled as failures (errors) */
            u1Result = MSCD_DFAI_JOB_ERROR;
            break;
    }

    return( u1Result );
}
#endif  /* MSCD_DFAI_USE == STD_ON */

#if( MSCD_DFAI_USE == STD_ON )
/****************************************************************************/
/* Function Name | Mscd_Dfai_Read (synchronous)                             */
/* Description   | Make a synchronous read request to the memory medium     */
/* Preconditions |                                                          */
/* Parameters    | u1MemoryIdentifier   : memory medium ID                  */
/*               |             * For future expansion. Currently fixed at 0 */
/*               | u4Address            : read-request address              */
/*               | ptSrcPtr             : first pointer of data to be read  */
/*               | u4Length             : length of read data               */
/* Return Value  | Mscd_Dfai_ReturnType                                     */
/*               |      MSCD_DFAI_JOB_OK         : Success                  */
/*               |      MSCD_DFAI_JOB_ERROR      : Failure (error)          */
/*               |      MSCD_DFAI_JOB_FATALERROR : Fail (fatal error)       */
/*               |      MSCD_DFAI_JOB_INOPERATIVE_HSM                       */
/*               |      MSCD_DFAI_JOB_INTEGRITY_FAILED                      */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Mscd_Dfai_ReturnType, MSCD_CODE)
Mscd_Dfai_Read( uint8 u1MemoryIdentifier, uint32 u4Address, P2VAR(uint8, AUTOMATIC, MSCD_APPL_DATA) ptSrcPtr, uint32 u4Length )
{
    Mscd_Dfai_ReturnType u1Result;
    uint8 u1Suspend_state;
    Std_ReturnType u1Param_check_result;
    Fee_ExtDirect_ReturnType u1Req_result;

    u1Result = MSCD_DFAI_JOB_ERROR;

    /* Only perform when MS is stopped */
    u1Suspend_state = Mscd_Suspend_GetUserSuspendState();
    if( MSCD_SUSPEND_MS_RUN != u1Suspend_state )
    {
        /* Check if the request parameters are within the user memory area specified in the config */
        u1Param_check_result = Mscd_Dfai_CheckAddrRange( u4Address, u4Length );

        if( u1Param_check_result == (Std_ReturnType)E_OK )
        {
            u1Req_result = Fee_ExtDirectRead( u4Address, u4Length, ptSrcPtr );

            switch( u1Req_result )
            {
                case FEE_EXT_DRCT_JOB_OK:
                    u1Result = MSCD_DFAI_JOB_OK;
                    break;
                case FEE_EXT_DRCT_JOB_FATALERROR:
                    u1Result = MSCD_DFAI_JOB_FATALERROR;
                    break;
                case FEE_EXT_DRCT_JOB_INOPERATIVE_HSM:
                    u1Result = MSCD_DFAI_JOB_INOPERATIVE_HSM;
                    break;
                case FEE_EXT_DRCT_JOB_INTEGRITY_FAILED:
                    u1Result = MSCD_DFAI_JOB_INTEGRITY_FAILED;
                    break;
                case FEE_EXT_DRCT_JOB_ERROR:
                default:
                    u1Result = MSCD_DFAI_JOB_ERROR;
                    break;
            }
        }
    }

    return( u1Result );
}
#endif  /* MSCD_DFAI_USE == STD_ON */

#if( MSCD_DFAI_USE == STD_ON )
/****************************************************************************/
/* Function Name | Mscd_Dfai_BlankCheck (synchronous)                       */
/* Description   | Request synchronous blank check to memory medium         */
/* Preconditions |                                                          */
/* Parameters    | u1MemoryIdentifier   : memory medium ID                  */
/*               |          * For future expansion. Currently fixed at 0    */
/*               | u4Address            : Address to be checked             */
/*               | u4Length             : length of data to check           */
/* Return Value  | Mscd_Dfai_ReturnType                                     */
/*               |      MSCD _ DFAI _ JOB _ BLANK       : blank             */
/*               |      MSCD _ DFAI _ JOB _ NOT _ BLANK : non-blank         */
/*               |      MSCD _ DFAI _ JOB _ ERROR       : Failure (error)   */
/*               |      MSCD _ DFAI _ JOB _ FATALERROR  : Fail (fatal error) */
/*               |      MSCD_DFAI_JOB_INOPERATIVE_HSM                       */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Mscd_Dfai_ReturnType, MSCD_CODE)
Mscd_Dfai_BlankCheck( uint8 u1MemoryIdentifier, uint32 u4Address, uint32 u4Length )
{
    Mscd_Dfai_ReturnType u1Result;
    uint8 u1Suspend_state;
    Std_ReturnType u1Param_check_result;
    Fee_ExtDirect_ReturnType u1Req_result;

    u1Result = MSCD_DFAI_JOB_ERROR;

    /* Only perform when MS is stopped */
    u1Suspend_state = Mscd_Suspend_GetUserSuspendState();
    if( MSCD_SUSPEND_MS_RUN != u1Suspend_state )
    {
        /* Check if the request parameters are within the user memory area specified in the config */
        u1Param_check_result = Mscd_Dfai_CheckAddrRange( u4Address, u4Length );

        /* Require a blank check from DFDA if parameter check is OK, otherwise return E_NOT_OK */
        if( u1Param_check_result == (Std_ReturnType)E_OK )
        {
            u1Req_result = Fee_ExtDirectBlankCheck( u4Address, u4Length );

            /* RETURN CONVERSION */
            switch( u1Req_result )
            {
                case FEE_EXT_DRCT_JOB_BLANK:
                    u1Result = MSCD_DFAI_JOB_BLANK;
                    break;
                /* Because non-blank and DFDA returns DTF_FEE_RESULT_OK when read, */
                /* Convert to MSCD_DFAI_JOB_NOT_BLANK */
                case FEE_EXT_DRCT_JOB_NOT_BLANK:
                    u1Result = MSCD_DFAI_JOB_NOT_BLANK;
                    break;
                case FEE_EXT_DRCT_JOB_FATALERROR:
                    u1Result = MSCD_DFAI_JOB_FATALERROR;
                    break;
                case FEE_EXT_DRCT_JOB_INOPERATIVE_HSM:
                    u1Result = MSCD_DFAI_JOB_INOPERATIVE_HSM;
                    break;
                case FEE_EXT_DRCT_JOB_ERROR:
                default: /* If it is ram garbled, treat it as a failure (error). */
                    u1Result = MSCD_DFAI_JOB_ERROR;
                    break;
            }
        }
    }

    return( u1Result );
}
#endif  /* MSCD_DFAI_USE == STD_ON */

#define MSCD_STOP_SEC_CODE
#include <Mscd_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/*  1-1-0          :2019/02/14                                              */
/*  2-0-0          :2021/05/18                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
