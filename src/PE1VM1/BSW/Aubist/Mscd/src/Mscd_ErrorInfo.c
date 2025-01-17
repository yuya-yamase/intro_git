/* Mscd_ErrorInfo.c v2-0-0                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | MSCD/ERRORINFO/CODE                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Mscd.h>

#include <Mscd_Common.h>
#include "../inc/Mscd_ErrorInfo.h"

#include "../inc/Mscd_Msif.h"
#include "../inc/Mscd_ErrorInfo_Internal.h"
#include "../usr/Mscd_ErrorInfo_UserHook.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

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
#define MSCD_START_SEC_CODE
#include <Mscd_MemMap.h>
/****************************************************************************/
/* Function Name | Mscd_ErrorInfo_Init （エラー情報初期化）                 */
/* Description   | エラー情報を初期化する                                   */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, MSCD_CODE)
Mscd_ErrorInfo_Init( void )
{
#if ( MSCD_ERRORINFO_USE == STD_ON )

    Mscd_ErrorInfo_stSingleErrorResultInfo.u4ErrorResult = MSCD_ERRINFO_RESULT_NO_ERROR;
    Mscd_ErrorInfo_stSingleErrorResultInfo.u2BlockId = MSCD_MSIF_BLOCKID_INVALID;

    Mscd_ErrorInfo_stMultiErrorResultInfo.u4ErrorResult = MSCD_ERRINFO_RESULT_NO_ERROR;
    Mscd_ErrorInfo_stMultiErrorResultInfo.u2BlockId = MSCD_MSIF_BLOCKID_INVALID;

    Mscd_ErrorInfo_stErrorFactorInfo.u4ErrorFactor = MSCD_ERRINFO_NO_ERROR;
    Mscd_ErrorInfo_stErrorFactorInfo.u4ErrorState = MSCD_ERRINFO_NO_ERROR;

    Mscd_ErrorInfo_u1CurrentSingleBlockRequest = MSCD_MSIF_SINGLE_BLOCK_REQUEST_INVALID;
    Mscd_ErrorInfo_u1CurrentMultiBlockRequest = MSCD_MSIF_MULTI_BLOCK_REQUEST_INVALID;
#endif /*( MSCD_ERRORINFO_USE == STD_ON )*/
    return;
}

/****************************************************************************/
/* Function Name | Mscd_ErrorInfo_SingleBlockJobStartHook                   */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u1BlockRequest                                           */
/* Return Value  | None                                                     */
/* Notes         | When a single block job starts during a multi block job, */
/*               | an argument is the Block Request of the multi block job. */
/****************************************************************************/
FUNC(void, MSCD_CODE) Mscd_ErrorInfo_SingleBlockJobStartHook( NvM_BlockRequestType u1BlockRequest )
{
#if ( MSCD_ERRORINFO_USE == STD_ON )

    /* Update current BlockRequest */
    switch (u1BlockRequest)
    {
        case NVM_READ_BLOCK :
        case NVM_WRITE_BLOCK :
        case NVM_RESTORE_BLOCK_DEFAULTS :
            Mscd_ErrorInfo_u1CurrentMultiBlockRequest = MSCD_MSIF_MULTI_BLOCK_REQUEST_INVALID;
            Mscd_ErrorInfo_u1CurrentSingleBlockRequest = u1BlockRequest;
            break;
            
        /* When single block job during multi block job starts, not update block request */
        case NVM_READ_ALL_BLOCK :
        case NVM_WRITE_ALL_BLOCK :
            break;
            
        /* Case getting block request that should not input ( assumed garbled data ) */
        default :
            Mscd_ErrorInfo_u1CurrentMultiBlockRequest = MSCD_MSIF_MULTI_BLOCK_REQUEST_INVALID;
            Mscd_ErrorInfo_u1CurrentSingleBlockRequest = MSCD_MSIF_SINGLE_BLOCK_REQUEST_INVALID;
            break;
    }
    
    /* Store Block Id */
    Mscd_ErrorInfo_stSingleErrorResultInfo.u2BlockId = Mscd_Msif_GetCurrentSingleJobBlockId();
    /* Clear result */
    Mscd_ErrorInfo_stSingleErrorResultInfo.u4ErrorResult = MSCD_ERRINFO_RESULT_NO_ERROR;
    
#endif /*( MSCD_ERRORINFO_USE == STD_ON )*/
    return;
}

/****************************************************************************/
/* Function Name | Mscd_ErrorInfo_MultiBlockJobStartHook                    */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u1MultiBlockRequest                                      */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, MSCD_CODE) Mscd_ErrorInfo_MultiBlockJobStartHook( NvM_MultiBlockRequestType u1MultiBlockRequest )
{
#if ( MSCD_ERRORINFO_USE == STD_ON )

    /* Update current BlockRequest */
    switch (u1MultiBlockRequest)
    {
        case NVM_READ_ALL :
            Mscd_ErrorInfo_u1CurrentSingleBlockRequest = NVM_READ_ALL_BLOCK;
            Mscd_ErrorInfo_u1CurrentMultiBlockRequest = u1MultiBlockRequest;
            break;
        case NVM_WRITE_ALL :
            Mscd_ErrorInfo_u1CurrentSingleBlockRequest = NVM_WRITE_ALL_BLOCK;
            Mscd_ErrorInfo_u1CurrentMultiBlockRequest = u1MultiBlockRequest;
            break;
            
        /* Case getting block request that should not input ( assumed garbled data ) */
        default :
            Mscd_ErrorInfo_u1CurrentSingleBlockRequest = MSCD_MSIF_SINGLE_BLOCK_REQUEST_INVALID;
            Mscd_ErrorInfo_u1CurrentMultiBlockRequest = MSCD_MSIF_MULTI_BLOCK_REQUEST_INVALID;
            break;
    }
    
    /* Store Block Id */
    Mscd_ErrorInfo_stMultiErrorResultInfo.u2BlockId = MSCD_MSIF_BLOCKID_MULTIJOB;
    /* Clear result */
    Mscd_ErrorInfo_stMultiErrorResultInfo.u4ErrorResult = MSCD_ERRINFO_RESULT_NO_ERROR;

#endif /*( MSCD_ERRORINFO_USE == STD_ON )*/
    return;
}

/****************************************************************************/
/* Function Name | Mscd_ErrorInfo_SingleBlockJobEndHook                     */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u1BlockRequest                                           */
/* Return Value  | None                                                     */
/* Notes         | When a single block job ends during a multi block job,   */
/*               | an argument is the Block Request of the multi block job. */
/****************************************************************************/
FUNC(void, MSCD_CODE) Mscd_ErrorInfo_SingleBlockJobEndHook( NvM_BlockRequestType u1BlockRequest )
{
#if ( MSCD_ERRORINFO_USE == STD_ON )

#endif /*( MSCD_ERRORINFO_USE == STD_ON )*/
    return;
}

/****************************************************************************/
/* Function Name | Mscd_ErrorInfo_MultiBlockJobEndHook                      */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u1MultiBlockRequest                                      */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, MSCD_CODE) Mscd_ErrorInfo_MultiBlockJobEndHook( NvM_MultiBlockRequestType u1MultiBlockRequest )
{
#if ( MSCD_ERRORINFO_USE == STD_ON )

#endif /*( MSCD_ERRORINFO_USE == STD_ON )*/
    return;
}

/****************************************************************************/
/* Function Name | Mscd_ErrorInfo_DetectErrorFactor                         */
/*               | （エラー情報(要因)検出時更新）                           */
/* Description   | エラー発生の通知を受け、エラー情報(要因)を更新する。     */
/* Preconditions |                                                          */
/* Parameters    | u1ErrorFactor       : エラー要因                         */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, MSCD_CODE)
Mscd_ErrorInfo_DetectErrorFactor( uint8 u1ErrorFactor )
{
#if ( MSCD_ERRORINFO_USE == STD_ON )
    uint32 u4OldErrorFactor;

    if( u1ErrorFactor < (uint8)MSCD_ERRINFO_ERRORFACTOR_NUM )
    {
        u4OldErrorFactor = Mscd_ErrorInfo_stErrorFactorInfo.u4ErrorFactor;

        /* Update error factor */
        Mscd_ErrorInfo_stErrorFactorInfo.u4ErrorFactor |= Mscd_ErrorInfo_stErrorFactor_BitPtnTbl[u1ErrorFactor].u4ErrorFactor;

        /* Update error status */
        Mscd_ErrorInfo_UpdateStateErrorFactor();

        /* Notify only if the error factor first time */
        if ( u4OldErrorFactor != Mscd_ErrorInfo_stErrorFactorInfo.u4ErrorFactor )
        {
            /* Return value is not checked. Cannot support even if E_NOT_OK is notified by a user. */
            (void)Mscd_ErrorInfo_ErrorFactorHook( &Mscd_ErrorInfo_stErrorFactorInfo );
        }
    }
#endif /*( MSCD_ERRORINFO_USE == STD_ON )*/
    return;
}

/****************************************************************************/
/* Function Name | Mscd_ErrorInfo_UpdateErrorResult                         */
/*               | （エラー情報(結果)更新）                                 */
/* Description   | エラー情報(結果)を更新する                               */
/* Preconditions |                                                          */
/* Parameters    | u4ErrorResult     : エラー情報(結果)                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, MSCD_CODE)
Mscd_ErrorInfo_UpdateErrorResult( uint32 u4ErrorResult )
{
#if ( MSCD_ERRORINFO_USE == STD_ON )
    uint32 u4TransErrorResult;

    /* Convert errorinfo(results) in the definition value of ERRINFO component */
    u4TransErrorResult = Mscd_ErrorInfo_TransformErrorResult( u4ErrorResult );

    /* Update the converted error information (results) */
    /* If Single Block Job is processing. */
    if ( (Mscd_ErrorInfo_u1CurrentMultiBlockRequest == MSCD_MSIF_MULTI_BLOCK_REQUEST_INVALID ) )
    {
        switch (Mscd_ErrorInfo_u1CurrentSingleBlockRequest)
        {
            case NVM_READ_BLOCK :
            case NVM_WRITE_BLOCK :
            case NVM_RESTORE_BLOCK_DEFAULTS :
            case NVM_READ_ALL_BLOCK :
            case NVM_WRITE_ALL_BLOCK :
                Mscd_ErrorInfo_stSingleErrorResultInfo.u4ErrorResult |= u4TransErrorResult;
                break;
            /* Case getting block request that should not input ( assumed garbled data ) */
            default :
                /* Do Nothing */
                break;
        }
    }
    /* If Multi Block Job is processing. */
    else
    {
        switch (Mscd_ErrorInfo_u1CurrentMultiBlockRequest)
        {
            case NVM_READ_ALL :
            case NVM_WRITE_ALL :
                Mscd_ErrorInfo_stSingleErrorResultInfo.u4ErrorResult |= u4TransErrorResult;
                Mscd_ErrorInfo_stMultiErrorResultInfo.u4ErrorResult |= u4TransErrorResult;
                break;
            /* Case getting block request that should not input ( assumed garbled data ) */
            default :
                /* Do Nothing */
                break;
        }
    }
    
#endif /*( MSCD_ERRORINFO_USE == STD_ON )*/
    return;
}

#if ( MSCD_ERRORINFO_USE == STD_ON )
/****************************************************************************/
/* Function Name | Mscd_ErrorInfo_GetErrorFactor                            */
/*               | （エラー情報(要因)取得）                                 */
/* Description   | エラー情報(要因)を取得する                               */
/* Preconditions |                                                          */
/* Parameters    | *ptrResult : Pointer of ErrorFactor                      */
/* Return Value  | E_OK       : Request Accept                              */
/*               | E_NOT_OK   : Request deny                                */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, MSCD_CODE)
Mscd_ErrorInfo_GetErrorFactor( P2VAR(Mscd_ErrorInfo_ErrorFactorInfoType, AUTOMATIC, MSCD_APPL_DATA) ptrResult )
{
    Std_ReturnType u1StdReturn;
    
    u1StdReturn = E_NOT_OK;
    
    if ( ptrResult != NULL_PTR )
    {
        ptrResult->u4ErrorFactor = Mscd_ErrorInfo_stErrorFactorInfo.u4ErrorFactor;
        ptrResult->u4ErrorState = Mscd_ErrorInfo_stErrorFactorInfo.u4ErrorState;
        u1StdReturn = E_OK;
    }

    return u1StdReturn;
}
#endif /*( MSCD_ERRORINFO_USE == STD_ON )*/

#if ( MSCD_ERRORINFO_USE == STD_ON )
/****************************************************************************/
/* Function Name | Mscd_ErrorInfo_GetSingleBlockJobErrorResult              */
/*               | （シングルブロック処理エラー情報(結果)取得）             */
/* Description   | シングルブロック処理中に起こったエラー情報(結果)         */
/*               | を取得する                                               */
/* Preconditions |                                                          */
/* Parameters    | u1BlockRequest : Block Request                           */
/*               | *prResult      : Error Result                            */
/* Return Value  | E_OK           : Request Accept                          */
/*               | E_NOT_OK       : Request deny                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, MSCD_CODE)
Mscd_ErrorInfo_GetSingleBlockJobErrorResult( NvM_BlockRequestType u1BlockRequest, P2VAR(Mscd_ErrorInfo_ErrorResultInfoType, AUTOMATIC, MSCD_APPL_DATA) ptrResult )
{
    Std_ReturnType u1StdReturn;
    Std_ReturnType u1ParamCheck;
    
    u1StdReturn = E_NOT_OK;
    u1ParamCheck = E_NOT_OK;

    if ( ptrResult != NULL_PTR )
    {
        if ( u1BlockRequest == Mscd_ErrorInfo_u1CurrentSingleBlockRequest )
        {
            u1ParamCheck = E_OK;
        }
    }

    if ( u1ParamCheck == (Std_ReturnType)E_OK )
    {
        switch (u1BlockRequest)
        {
        case NVM_READ_BLOCK :
        case NVM_WRITE_BLOCK :
        case NVM_RESTORE_BLOCK_DEFAULTS :
        case NVM_READ_ALL_BLOCK :
        case NVM_WRITE_ALL_BLOCK :
                ptrResult->u2BlockId     = Mscd_ErrorInfo_stSingleErrorResultInfo.u2BlockId;
                ptrResult->u4ErrorResult = Mscd_ErrorInfo_stSingleErrorResultInfo.u4ErrorResult;
                u1StdReturn = E_OK;
                break;
                
            /* Case getting block request that should not input ( assumed garbled data ) */
            default :
                /* Do Nothing */
                break;
        }
    }
    return u1StdReturn;
}
#endif /*( MSCD_ERRORINFO_USE == STD_ON )*/

#if ( MSCD_ERRORINFO_USE == STD_ON )
/****************************************************************************/
/* Function Name | Mscd_ErrorInfo_GetMultiBlockJobErrorResult               */
/*               | （マルチブロック処理エラー情報(結果)取得）               */
/* Description   | マルチブロック処理中に起こったエラー情報(結果)           */
/*               | を取得する                                               */
/* Preconditions |                                                          */
/* Parameters    | u1MultiBlockRequest : Block Request                      */
/*               | *prResult           : Error Result                       */
/* Return Value  | E_OK                : Request Accept                     */
/*               | E_NOT_OK            : Request deny                       */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, MSCD_CODE)
Mscd_ErrorInfo_GetMultiBlockJobErrorResult( NvM_MultiBlockRequestType u1MultiBlockRequest, P2VAR(Mscd_ErrorInfo_ErrorResultInfoType, AUTOMATIC, MSCD_APPL_DATA) ptrResult )
{
    Std_ReturnType u1StdReturn;
    Std_ReturnType u1ParamCheck;
    
    u1StdReturn = E_NOT_OK;
    u1ParamCheck = E_NOT_OK;

    if ( ptrResult != NULL_PTR )
    {
        if ( u1MultiBlockRequest == Mscd_ErrorInfo_u1CurrentMultiBlockRequest )
        {
            u1ParamCheck = E_OK;
        }
    }

    if ( u1ParamCheck == (Std_ReturnType)E_OK )
    {
        switch (u1MultiBlockRequest)
        {
            case NVM_READ_ALL :
            case NVM_WRITE_ALL :
                ptrResult->u2BlockId     = Mscd_ErrorInfo_stMultiErrorResultInfo.u2BlockId;
                ptrResult->u4ErrorResult = Mscd_ErrorInfo_stMultiErrorResultInfo.u4ErrorResult;
                u1StdReturn = E_OK;
                break;
                
            /* Case getting block request that should not input ( assumed garbled data ) */
            default :
                /* Do Nothing */
                break;
        }
    }
    return u1StdReturn;
}
#endif /*( MSCD_ERRORINFO_USE == STD_ON )*/

#define MSCD_STOP_SEC_CODE
#include <Mscd_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/*  2-0-0          :2022/07/15                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
