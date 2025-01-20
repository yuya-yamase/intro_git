/* CmpDecmp_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | CmpDecmp/CODE                                               */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <CmpDecmp.h>

/*===== Sample ===============================================================*/
#if (REPROG_CFG_DECOMPRESS_ENABLE == STD_ON)
#include "COMPRESS_LZMA_DECODE.h"   /* Use emCompress */
#endif
/*===== Sample ===============================================================*/


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/*===== Sample ===============================================================*/
#if (REPROG_CFG_DECOMPRESS_ENABLE == STD_ON)
#define CMPDECMP_STAT_IDLE                      ((uint8)0x00U)
#define CMPDECMP_STAT_PRE_DECMP                 ((uint8)0x01U)
#define CMPDECMP_STAT_PRE_DECMP_FINISH          ((uint8)0x02U)
#define CMPDECMP_STAT_REQ_DECMP                 ((uint8)0x03U)
#define CMPDECMP_STAT_REQ_DECMP_SUSPEND         ((uint8)0x04U)
#define CMPDECMP_STAT_REQ_DECMP_SUSPEND_IDLE    ((uint8)0x05U)
#define CMPDECMP_STAT_REQ_DECMP_FINISH          ((uint8)0x06U)
#define CMPDECMP_STAT_REQ_DECMP_FINISH_IDLE     ((uint8)0x07U)
#define CMPDECMP_STAT_POST_DECMP                ((uint8)0x08U)
#define CMPDECMP_STAT_POST_DECMP_FINISH         ((uint8)0x09U)

#define CMPDECMP_DECMP_BUFF_SIZE                ((uint16)4096U)
#endif
/*===== Sample ===============================================================*/


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
/*===== Sample ===============================================================*/
#if (REPROG_CFG_DECOMPRESS_ENABLE == STD_ON)
static FUNC(void, CMPDECMP_CODE_FAST) CmpDecmp_Main_PreDecmp (void);
static FUNC(void, CMPDECMP_CODE_FAST) CmpDecmp_Main_Decompress (void);
static FUNC(void, CMPDECMP_CODE_FAST) CmpDecmp_Main_PostDecmp (void);
static FUNC(Std_ReturnType, CMPDECMP_CODE_FAST) CmpDecmp_Decompress_Start
(
    P2CONST(CmpDecmp_DecompressInfoType, AUTOMATIC, CMPDECMP_APPL_CONST) DecmpInfo
);
static FUNC(Std_ReturnType, CMPDECMP_CODE_FAST) CmpDecmp_Decompress_Resume
(
    P2VAR(CmpDecmp_DecompressInfoType, AUTOMATIC, CMPDECMP_APPL_DATA) DecmpInfo
);
#endif
/*===== Sample ===============================================================*/


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define CMPDECMP_START_SEC_VAR
#include <CmpDecmp_MemMap.h>

/*===== Sample ===============================================================*/
#if (REPROG_CFG_DECOMPRESS_ENABLE == STD_ON)
static uint8 CmpDecmp_Status;
static uint8 CmpDecmp_FailedFlag;
static uint32 CmpDecmp_TotalCompSize;
static uint32 CmpDecmp_ProcessedCompSize;
static COMPRESS_LZMA_STREAM CmpDecmp_Stream;
#endif
/*===== Sample ===============================================================*/

#define CMPDECMP_STOP_SEC_VAR
#include <CmpDecmp_MemMap.h>

#define CMPDECMP_START_SEC_VAR_LARGE
#include <CmpDecmp_MemMap.h>

/*===== Sample ===============================================================*/
#if (REPROG_CFG_DECOMPRESS_ENABLE == STD_ON)
static uint8 CmpDecmp_Decmp_Buff[CMPDECMP_DECMP_BUFF_SIZE];
static COMPRESS_LZMA_DECODE_CONTEXT CmpDecmp_Decmp_Ctx;
#endif
/*===== Sample ===============================================================*/

#define CMPDECMP_STOP_SEC_VAR_LARGE
#include <CmpDecmp_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define CMPDECMP_START_SEC_CST
#include <CmpDecmp_MemMap.h>

#define CMPDECMP_STOP_SEC_CST
#include <CmpDecmp_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define CMPDECMP_START_SEC_CODE
#include <CmpDecmp_MemMap.h>

/******************************************************************************/
/* Function Name | CmpDecmp_Init                                              */
/* Description   | Initializes CmpDecmp                                       */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, CMPDECMP_CODE_SLOW) CmpDecmp_Init (void)
{
/*===== Sample ===============================================================*/
#if (REPROG_CFG_DECOMPRESS_ENABLE == STD_ON)
    CmpDecmp_Stream.AvailIn  = 0UL;
    CmpDecmp_Stream.pIn      = NULL_PTR;
    CmpDecmp_Stream.AvailOut = 0UL;
    CmpDecmp_Stream.pOut     = NULL_PTR;

    CmpDecmp_TotalCompSize = 0UL;
    CmpDecmp_ProcessedCompSize = 0UL;

    CmpDecmp_Status = CMPDECMP_STAT_IDLE;
    CmpDecmp_FailedFlag = STD_OFF;
#endif
/*===== Sample ===============================================================*/

    return;
}

/******************************************************************************/
/* Function Name | CmpDecmp_DeInit                                            */
/* Description   | Deinitializes CmpDecmp                                     */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, CMPDECMP_CODE_SLOW) CmpDecmp_DeInit (void)
{
/*===== Sample ===============================================================*/
#if (REPROG_CFG_DECOMPRESS_ENABLE == STD_ON)
    CmpDecmp_Status = CMPDECMP_STAT_IDLE;
    CmpDecmp_FailedFlag = STD_OFF;

    CmpDecmp_TotalCompSize = 0UL;
    CmpDecmp_ProcessedCompSize = 0UL;

    CmpDecmp_Stream.AvailIn  = 0UL;
    CmpDecmp_Stream.pIn      = NULL_PTR;
    CmpDecmp_Stream.AvailOut = 0UL;
    CmpDecmp_Stream.pOut     = NULL_PTR;
#endif
/*===== Sample ===============================================================*/

    return;
}

/******************************************************************************/
/* Function Name | CmpDecmp_Time                                              */
/* Description   | TimeFunction                                               */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, CMPDECMP_CODE_SLOW) CmpDecmp_Time (void)
{
    return;
}

/******************************************************************************/
/* Function Name | CmpDecmp_MainFunction                                      */
/* Description   | MainFunction                                               */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, CMPDECMP_CODE_SLOW) CmpDecmp_MainFunction (void)
{
/*===== Sample ===============================================================*/
#if (REPROG_CFG_DECOMPRESS_ENABLE == STD_ON)
    if( CmpDecmp_Status == CMPDECMP_STAT_PRE_DECMP )
    {
        CmpDecmp_Main_PreDecmp();
    }
    else if( CmpDecmp_Status == CMPDECMP_STAT_REQ_DECMP )
    {
        CmpDecmp_Main_Decompress();
    }
    else if( CmpDecmp_Status == CMPDECMP_STAT_POST_DECMP )
    {
        CmpDecmp_Main_PostDecmp();
    }
    else
    {
        /* No process */
    }
#endif
/*===== Sample ===============================================================*/

    return;
}

/******************************************************************************/
/* Function Name | CmpDecmp_PreDecompress                                     */
/* Description   | Prepares decompression                                     */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/*               |  CMPDECMP_E_PENDING                                        */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, CMPDECMP_CODE_SLOW) CmpDecmp_PreDecompress (void)
{
/*===== Sample ===============================================================*/
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Ret = E_NOT_OK;

#if (REPROG_CFG_DECOMPRESS_ENABLE == STD_ON)
    if( CmpDecmp_FailedFlag == (uint8)STD_OFF )
    {
        if( (CmpDecmp_Status == CMPDECMP_STAT_IDLE) ||
            (CmpDecmp_Status == CMPDECMP_STAT_PRE_DECMP) ||
            (CmpDecmp_Status == CMPDECMP_STAT_POST_DECMP_FINISH) )
        {
            CmpDecmp_Status = CMPDECMP_STAT_PRE_DECMP;
            Ret = CMPDECMP_E_PENDING;
        }
        else if( CmpDecmp_Status == CMPDECMP_STAT_PRE_DECMP_FINISH )
        {
            Ret = E_OK;
        }
        else
        {
            CmpDecmp_FailedFlag = STD_ON;
        }
    }
#endif

    return Ret;
/*===== Sample ===============================================================*/
}

/******************************************************************************/
/* Function Name | CmpDecmp_PostDecompress                                    */
/* Description   | Completes decompression                                    */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/*               |  CMPDECMP_E_PENDING                                        */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, CMPDECMP_CODE_SLOW) CmpDecmp_PostDecompress (void)
{
/*===== Sample ===============================================================*/
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Ret = E_NOT_OK;

#if (REPROG_CFG_DECOMPRESS_ENABLE == STD_ON)
    if( CmpDecmp_FailedFlag == (uint8)STD_OFF )
    {
        if( (CmpDecmp_Status == CMPDECMP_STAT_REQ_DECMP_FINISH_IDLE) ||
            (CmpDecmp_Status == CMPDECMP_STAT_POST_DECMP) )
        {
            CmpDecmp_Status = CMPDECMP_STAT_POST_DECMP;
            Ret = CMPDECMP_E_PENDING;
        }
        else if( CmpDecmp_Status == CMPDECMP_STAT_POST_DECMP_FINISH )
        {
            Ret = E_OK;
        }
        else
        {
            CmpDecmp_FailedFlag = STD_ON;
        }
    }
#endif

    return Ret;
/*===== Sample ===============================================================*/
}

/******************************************************************************/
/* Function Name | CmpDecmp_Decompress                                        */
/* Description   | Requests decompression                                     */
/* Preconditions |                                                            */
/* Parameters    | [IN] Op           : Operation                              */
/*               |   CMPDECMP_DECMP_START                                     */
/*               |   CMPDECMP_DECMP_RESUME                                    */
/* Parameters    | [INOUT] DecmpInfo : Information of decompression           */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  CMPDECMP_E_PENDING                                        */
/*               |  CMPDECMP_E_SUSPEND                                        */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, CMPDECMP_CODE_SLOW) CmpDecmp_Decompress
(
    VAR(uint8, AUTOMATIC) Op,
    P2VAR(CmpDecmp_DecompressInfoType, AUTOMATIC, CMPDECMP_APPL_DATA) DecmpInfo
)
{
/*===== Sample ===============================================================*/
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Ret = E_NOT_OK;

#if (REPROG_CFG_DECOMPRESS_ENABLE == STD_ON)
    if( CmpDecmp_FailedFlag == (uint8)STD_OFF )
    {
        if( Op == CMPDECMP_DECMP_START )
        {
            Ret = CmpDecmp_Decompress_Start(DecmpInfo);
        }
        else if( Op == CMPDECMP_DECMP_RESUME )
        {
            Ret = CmpDecmp_Decompress_Resume(DecmpInfo);
        }
        else
        {
            /* No process */
        }

        if( ((Ret == (Std_ReturnType)E_OK) || (Ret == CMPDECMP_E_SUSPEND)) &&
            (CMPDECMP_DECMP_BUFF_SIZE >= CmpDecmp_Stream.AvailOut) )
        {
            DecmpInfo->DecompBuf        = CmpDecmp_Decmp_Buff;
            DecmpInfo->DecompResultSize = CMPDECMP_DECMP_BUFF_SIZE - CmpDecmp_Stream.AvailOut;

            if( Ret == (Std_ReturnType)E_OK )
            {
                CmpDecmp_Status = CMPDECMP_STAT_REQ_DECMP_FINISH_IDLE;
            }
            else
            {
                CmpDecmp_Status = CMPDECMP_STAT_REQ_DECMP_SUSPEND_IDLE;
            }
        }
    }
#endif

    return Ret;
/*===== Sample ===============================================================*/
}

/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

/*===== Sample ===============================================================*/
#if (REPROG_CFG_DECOMPRESS_ENABLE == STD_ON)
/******************************************************************************/
/* Function Name | CmpDecmp_Main_PreDecmp                                     */
/* Description   | Mainfunction of CMPDECMP_STAT_PRE_DECMP                    */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, CMPDECMP_CODE_FAST) CmpDecmp_Main_PreDecmp (void)
{
    COMPRESS_LZMA_DECODE_Init(&CmpDecmp_Decmp_Ctx);
    CmpDecmp_ProcessedCompSize = 0UL;
    CmpDecmp_Status = CMPDECMP_STAT_PRE_DECMP_FINISH;

    return;
}

/******************************************************************************/
/* Function Name | CmpDecmp_Main_PostDecmp                                    */
/* Description   | Mainfunction of CMPDECMP_STAT_POST_DECMP                   */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, CMPDECMP_CODE_FAST) CmpDecmp_Main_PostDecmp (void)
{
    CmpDecmp_Status = CMPDECMP_STAT_POST_DECMP_FINISH;

    return;
}

/******************************************************************************/
/* Function Name | CmpDecmp_Main_Decompress                                   */
/* Description   | Mainfunction of CMPDECMP_STAT_REQ_DECMP                    */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, CMPDECMP_CODE_FAST) CmpDecmp_Main_Decompress (void)
{
    VAR(ILEAST16, AUTOMATIC) LZMA_Ret;
    VAR(ILEAST16, AUTOMATIC) LZMA_Flush;
    VAR(uint32, AUTOMATIC) AvailInBefore;

    LZMA_Flush = 0;
    AvailInBefore = CmpDecmp_Stream.AvailIn;
    if( (CmpDecmp_Stream.AvailIn + CmpDecmp_ProcessedCompSize) >= CmpDecmp_TotalCompSize )
    {
        /* Last compressed data */
        LZMA_Flush = 1;
    }

    LZMA_Ret = COMPRESS_LZMA_DECODE_Run(&CmpDecmp_Decmp_Ctx, &CmpDecmp_Stream, LZMA_Flush);
    if( LZMA_Ret == 0 )
    {
        CmpDecmp_ProcessedCompSize += (AvailInBefore - CmpDecmp_Stream.AvailIn);
        if( (CmpDecmp_Stream.AvailIn == 0UL) && (LZMA_Flush == 0) )
        {
            /* Expansion of input compressed data (non-last data) is completed. */
            CmpDecmp_Status = CMPDECMP_STAT_REQ_DECMP_FINISH;
        }
        else
        {
            /* The expansion buffer is full and expansion processing remains. */
            CmpDecmp_Status = CMPDECMP_STAT_REQ_DECMP_SUSPEND;
        }
    }
    else if( LZMA_Ret > 0 )
    {
        /* Expansion of input compressed data (last data) is completed. */
        CmpDecmp_Status = CMPDECMP_STAT_REQ_DECMP_FINISH;
    }
    else
    {
        /* Error occurred */
        CmpDecmp_FailedFlag = STD_ON;
        CmpDecmp_Status = CMPDECMP_STAT_IDLE;
    }

    return;
}

/******************************************************************************/
/* Function Name | CmpDecmp_Decompress_Start                                  */
/* Description   | Starts decompression                                       */
/* Preconditions |                                                            */
/* Parameters    | [IN] DecmpInfo : Information of decompression              */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/*               |  CMPDECMP_E_PENDING                                        */
/*               |  CMPDECMP_E_SUSPEND                                        */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(Std_ReturnType, CMPDECMP_CODE_FAST) CmpDecmp_Decompress_Start
(
    P2CONST(CmpDecmp_DecompressInfoType, AUTOMATIC, CMPDECMP_APPL_CONST) DecmpInfo
)
{
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Ret = E_NOT_OK;

    if( (CmpDecmp_Status == CMPDECMP_STAT_PRE_DECMP_FINISH) ||
        (CmpDecmp_Status == CMPDECMP_STAT_REQ_DECMP_FINISH_IDLE) )
    {
        CmpDecmp_Stream.AvailIn  = DecmpInfo->CompDataSize;
        CmpDecmp_Stream.pIn      = DecmpInfo->CompData;
        CmpDecmp_Stream.AvailOut = CMPDECMP_DECMP_BUFF_SIZE;
        CmpDecmp_Stream.pOut     = CmpDecmp_Decmp_Buff;

        CmpDecmp_TotalCompSize = DecmpInfo->CompDataTotalSize;

        CmpDecmp_Status = CMPDECMP_STAT_REQ_DECMP;

        Ret = CMPDECMP_E_PENDING;
    }
    else if( CmpDecmp_Status == CMPDECMP_STAT_REQ_DECMP )
    {
        Ret = CMPDECMP_E_PENDING;
    }
    else if( CmpDecmp_Status == CMPDECMP_STAT_REQ_DECMP_SUSPEND )
    {
        Ret = CMPDECMP_E_SUSPEND;
    }
    else if( CmpDecmp_Status == CMPDECMP_STAT_REQ_DECMP_FINISH )
    {
        Ret = E_OK;
    }
    else
    {
        /* No process */
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | CmpDecmp_Decompress_Resume                                 */
/* Description   | Resumes decompression                                      */
/* Preconditions |                                                            */
/* Parameters    | [INOUT] DecmpInfo : Information of decompression           */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/*               |  CMPDECMP_E_PENDING                                        */
/*               |  CMPDECMP_E_SUSPEND                                        */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(Std_ReturnType, CMPDECMP_CODE_FAST) CmpDecmp_Decompress_Resume
(
    P2VAR(CmpDecmp_DecompressInfoType, AUTOMATIC, CMPDECMP_APPL_DATA) DecmpInfo
)
{
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Ret = E_NOT_OK;

    if( CmpDecmp_Status == CMPDECMP_STAT_REQ_DECMP_SUSPEND_IDLE )
    {
        CmpDecmp_Stream.AvailOut = CMPDECMP_DECMP_BUFF_SIZE;
        CmpDecmp_Stream.pOut     = CmpDecmp_Decmp_Buff;

        CmpDecmp_Status = CMPDECMP_STAT_REQ_DECMP;
        Ret = CMPDECMP_E_PENDING;
    }
    else if( CmpDecmp_Status == CMPDECMP_STAT_REQ_DECMP )
    {
        Ret = CMPDECMP_E_PENDING;
    }
    else if( CmpDecmp_Status == CMPDECMP_STAT_REQ_DECMP_SUSPEND )
    {
        Ret = CMPDECMP_E_SUSPEND;
    }
    else if( CmpDecmp_Status == CMPDECMP_STAT_REQ_DECMP_FINISH )
    {
        Ret = E_OK;
    }
    else
    {
        /* No process */
    }

    return Ret;
}
#endif
/*===== Sample ===============================================================*/

#define CMPDECMP_STOP_SEC_CODE
#include <CmpDecmp_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/08/02 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

