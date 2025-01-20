/* PrgChk_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | PrgChk/CODE                                                 */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <RpgLib.h>
#include <Rte.h>
#include <Crc.h>

#include <PrgChk.h>
#include "PrgChk_Local.h"
#include "PrgChk_Cfg.h"


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define PRGCHK_STAT_IDLE            ((uint8)0x00U)
#define PRGCHK_STAT_PRE_CALC_FINISH ((uint8)0x01U)
#define PRGCHK_STAT_REQ_CALC        ((uint8)0x02U)
#define PRGCHK_STAT_REQ_CALC_FINISH ((uint8)0x03U)

#define PRGCHK_READBUF_SIZE         ((uint16)256U)
#define PRGCHK_CRC32_VALUE_SIZE     ((uint8)4U)

#define PRGCHK_4BYTE_BIT            ((uint8)32U)
#define PRGCHK_1BYTE_BIT            ((uint8)8U)

#define PRGCHK_STATUSMATRIXTBL_NUM  (sizeof(PrgChk_StatusMatrixTbl) / sizeof(PrgChk_StatusMatrixTbl[0]))


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef struct {
    uint8 LocalStatus;
    uint8 JobResult;
} PrgChk_JobInfoType;

typedef struct {
    uint8 LocalStatus;
    uint8 RetStatus;
} PrgChk_StatusMatrixType;

typedef struct {
    uint32 RemainSize;
    uint32 NextAddress;
    uint32 CalcSize;
    uint32 CalcVal;
    P2VAR(uint8, TYPEDEF, PRGCHK_APPL_DATA) ResultPtr;
    boolean IsFirstCall;
} PrgChk_CrcCalcInfoType;

typedef struct {
    uint32 Num;
    P2CONST(PrgChk_StatusMatrixType, TYPEDEF, PRGCHK_APPL_CONST) MatrixPtr;
} PrgChk_StatusMatrixInfoType;


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
static FUNC(void, PRGCHK_CODE_FAST) PrgChk_UpdateJobInfo
(
    VAR(uint8, AUTOMATIC) JobResult,
    VAR(uint8, AUTOMATIC) LocalStatus
);
static FUNC(Std_ReturnType, PRGCHK_CODE_FAST) PrgChk_GetApiAcceptation (void);
static FUNC(void, PRGCHK_CODE_FAST) PrgChk_ReleaseApiAcceptation (void);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define PRGCHK_START_SEC_VAR
#include <PrgChk_MemMap.h>

static VAR(PrgChk_JobInfoType, PRGCHK_VAR_CLEARED) PrgChk_JobInfo;
static VAR(PrgChk_CrcCalcInfoType, PRGCHK_VAR_CLEARED) PrgChk_CrcCalcInfo;
static VAR(uint8, PRGCHK_VAR_CLEARED) PrgChk_CrcCalcAreaReadBuff[PRGCHK_READBUF_SIZE];
static VAR(uint8, PRGCHK_VAR_CLEARED) PrgChk_ApiAcceptingFlg;

#define PRGCHK_STOP_SEC_VAR
#include <PrgChk_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define PRGCHK_START_SEC_CST
#include <PrgChk_MemMap.h>

static CONST(PrgChk_StatusMatrixType, PRGCHK_CONST) PrgChk_StatusMatrixTbl[] = {
     { PRGCHK_STAT_IDLE,            PRGCHK_IDLE }
    ,{ PRGCHK_STAT_PRE_CALC_FINISH, PRGCHK_IDLE }
    ,{ PRGCHK_STAT_REQ_CALC,        PRGCHK_BUSY }
    ,{ PRGCHK_STAT_REQ_CALC_FINISH, PRGCHK_IDLE }
};
static CONST(AB_83_ConstV PrgChk_StatusMatrixInfoType, PRGCHK_CONST) PrgChk_StatusMatrixInfo = {
    PRGCHK_STATUSMATRIXTBL_NUM,
    &PrgChk_StatusMatrixTbl[0]
};


#define PRGCHK_STOP_SEC_CST
#include <PrgChk_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define PRGCHK_START_SEC_CODE
#include <PrgChk_MemMap.h>

/******************************************************************************/
/* Function Name | PrgChk_Init                                                */
/* Description   | Initializes PrgChk                                         */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, PRGCHK_CODE_SLOW) PrgChk_Init (void)
{
    PrgChk_CrcCalcInfo.RemainSize = 0UL;
    PrgChk_CrcCalcInfo.NextAddress = 0UL;
    PrgChk_CrcCalcInfo.CalcSize = 0UL;
    PrgChk_CrcCalcInfo.CalcVal = 0UL;
    PrgChk_CrcCalcInfo.ResultPtr = NULL_PTR;
    PrgChk_CrcCalcInfo.IsFirstCall = TRUE;

    Rte_Rpg_MemSet(&PrgChk_CrcCalcAreaReadBuff[0], 0U, sizeof(PrgChk_CrcCalcAreaReadBuff));

    PrgChk_ApiAcceptingFlg = STD_OFF;

    PrgChk_JobInfo.JobResult = PRGCHK_JOB_OK;
    PrgChk_JobInfo.LocalStatus = PRGCHK_STAT_IDLE;

    return;
}

/******************************************************************************/
/* Function Name | PrgChk_DeInit                                              */
/* Description   | Deinitializes PrgChk                                       */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, PRGCHK_CODE_SLOW) PrgChk_DeInit (void)
{
    PrgChk_JobInfo.LocalStatus = PRGCHK_STAT_IDLE;
    PrgChk_JobInfo.JobResult = PRGCHK_JOB_OK;

    PrgChk_ApiAcceptingFlg = STD_OFF;

    Rte_Rpg_MemSet(&PrgChk_CrcCalcAreaReadBuff[0], 0U, sizeof(PrgChk_CrcCalcAreaReadBuff));

    PrgChk_CrcCalcInfo.IsFirstCall = FALSE;
    PrgChk_CrcCalcInfo.ResultPtr = NULL_PTR;
    PrgChk_CrcCalcInfo.CalcVal = 0UL;
    PrgChk_CrcCalcInfo.CalcSize = 0UL;
    PrgChk_CrcCalcInfo.NextAddress = 0UL;
    PrgChk_CrcCalcInfo.RemainSize = 0UL;

    return;
}

/******************************************************************************/
/* Function Name | PrgChk_Time                                                */
/* Description   | TimeFunction                                               */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, PRGCHK_CODE_SLOW) PrgChk_Time (void)
{
    return;
}

/******************************************************************************/
/* Function Name | PrgChk_MainFunction                                        */
/* Description   | MainFunction                                               */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, PRGCHK_CODE_SLOW) PrgChk_MainFunction (void)
{
    VAR(uint32, AUTOMATIC) ReadSize;
    VAR(uint8, AUTOMATIC) RpgLibStatus;
    VAR(uint8, AUTOMATIC) RpgLibJobResult;
    VAR(uint8, AUTOMATIC) ClearFlg;
    VAR(uint8, AUTOMATIC) ErrorFlg;
    VAR(uint8, AUTOMATIC) BitShift;
    VAR(uint8, AUTOMATIC) i;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    if( PrgChk_JobInfo.LocalStatus == PRGCHK_STAT_REQ_CALC )
    {
        ClearFlg = STD_OFF;
        ErrorFlg = STD_OFF;

        RpgLibStatus = RpgLib_GetStatus();
        if( RpgLibStatus == RPGLIB_IDLE )
        {
            RpgLibJobResult = RpgLib_GetJobResult();
            if( RpgLibJobResult == RPGLIB_JOB_OK )
            {
                PrgChk_CrcCalcInfo.CalcVal = Crc_CalculateCRC32(&PrgChk_CrcCalcAreaReadBuff[0],
                                                                PrgChk_CrcCalcInfo.CalcSize,
                                                                PrgChk_CrcCalcInfo.CalcVal,
                                                                PrgChk_CrcCalcInfo.IsFirstCall);

                PrgChk_CrcCalcInfo.IsFirstCall = FALSE;

                if( PrgChk_CrcCalcInfo.RemainSize != 0UL )
                {
                    ReadSize = PrgChk_CrcCalcInfo.RemainSize;
                    if( ReadSize > PRGCHK_READBUF_SIZE )
                    {
                        ReadSize = PRGCHK_READBUF_SIZE;
                    }

                    FuncRet = RpgLib_ReqMemRead(RPGLIB_MEMORYID_0, &PrgChk_CrcCalcAreaReadBuff[0], PrgChk_CrcCalcInfo.NextAddress, ReadSize);
                    if( FuncRet == (Std_ReturnType)E_OK )
                    {
                        PrgChk_CrcCalcInfo.CalcSize = ReadSize;
                        PrgChk_CrcCalcInfo.NextAddress += ReadSize; /* no wrap around */
                        PrgChk_CrcCalcInfo.RemainSize -= ReadSize;  /* no wrap around */
                    }
                    else
                    {
                        ClearFlg = STD_ON;
                        ErrorFlg = STD_ON;
                    }
                }
                else
                {
                    BitShift = PRGCHK_4BYTE_BIT;
                    for( i = 0U; i < PRGCHK_CRC32_VALUE_SIZE; i++ )
                    {
                        BitShift -= PRGCHK_1BYTE_BIT;   /* no wrap around */
                        PrgChk_CrcCalcInfo.ResultPtr[i] = (uint8)(PrgChk_CrcCalcInfo.CalcVal >> BitShift);
                    }
                    ClearFlg = STD_ON;

                    PrgChk_UpdateJobInfo(PRGCHK_JOB_OK, PRGCHK_STAT_REQ_CALC_FINISH);
                }
            }
            else
            {
                ClearFlg = STD_ON;
                ErrorFlg = STD_ON;
            }
        }
        else if( RpgLibStatus == RPGLIB_BUSY )
        {
            /* No process */
        }
        else
        {
            ClearFlg = STD_ON;
            ErrorFlg = STD_ON;
        }

        if( ClearFlg == (uint8)STD_ON )
        {
            PrgChk_CrcCalcInfo.RemainSize = 0UL;
            PrgChk_CrcCalcInfo.NextAddress = 0UL;
            PrgChk_CrcCalcInfo.CalcSize = 0UL;
            PrgChk_CrcCalcInfo.CalcVal = 0UL;
            PrgChk_CrcCalcInfo.ResultPtr = NULL_PTR;
            PrgChk_CrcCalcInfo.IsFirstCall = FALSE;
        }

        if( ErrorFlg == (uint8)STD_ON )
        {
            PrgChk_UpdateJobInfo(PRGCHK_JOB_FAILED, PRGCHK_STAT_IDLE);
        }
    }

    return;
}

/******************************************************************************/
/* Function Name | PrgChk_GetStatus                                           */
/* Description   | Acquires status of job                                     */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Status                                                     */
/*               |  PRGCHK_IDLE                                               */
/*               |  PRGCHK_BUSY                                               */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(uint8, PRGCHK_CODE_SLOW) PrgChk_GetStatus (void)
{
    VAR(uint32, AUTOMATIC) i;
    VAR(uint8, AUTOMATIC) Status;

    Status = PRGCHK_BUSY;

    for( i = 0UL; i < PrgChk_StatusMatrixInfo.Num; i++ )
    {
        if( PrgChk_JobInfo.LocalStatus == PrgChk_StatusMatrixInfo.MatrixPtr[i].LocalStatus )
        {
            Status = PrgChk_StatusMatrixInfo.MatrixPtr[i].RetStatus;
            break;
        }
    }

    return Status;
}

/******************************************************************************/
/* Function Name | PrgChk_GetJobResult                                        */
/* Description   | Acquires result of job                                     */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | JobResult                                                  */
/*               |  PRGCHK_JOB_OK                                             */
/*               |  PRGCHK_JOB_FAILED                                         */
/*               |  PRGCHK_JOB_PENDING                                        */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(uint8, PRGCHK_CODE_SLOW) PrgChk_GetJobResult (void)
{
    return PrgChk_JobInfo.JobResult;
}

/******************************************************************************/
/* Function Name | PrgChk_PreCalcValue                                        */
/* Description   | Prepares calculation for program check                     */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, PRGCHK_CODE_SLOW) PrgChk_PreCalcValue (void)
{
    VAR(Std_ReturnType, AUTOMATIC) Ret;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    Ret = E_NOT_OK;

    FuncRet = PrgChk_GetApiAcceptation();
    if( FuncRet == (Std_ReturnType)E_OK )
    {
        if( PrgChk_JobInfo.LocalStatus == PRGCHK_STAT_IDLE )
        {
            PrgChk_UpdateJobInfo(PRGCHK_JOB_OK, PRGCHK_STAT_PRE_CALC_FINISH);
            Ret = E_OK;
        }
        else
        {
            PrgChk_UpdateJobInfo(PRGCHK_JOB_FAILED, PRGCHK_STAT_IDLE);
        }

        PrgChk_ReleaseApiAcceptation();
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | PrgChk_PostCalcValue                                       */
/* Description   | Finishes calculation for program check                     */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, PRGCHK_CODE_SLOW) PrgChk_PostCalcValue (void)
{
    VAR(Std_ReturnType, AUTOMATIC) Ret;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    Ret = E_NOT_OK;

    FuncRet = PrgChk_GetApiAcceptation();
    if( FuncRet == (Std_ReturnType)E_OK )
    {
        if( PrgChk_JobInfo.LocalStatus == PRGCHK_STAT_REQ_CALC_FINISH )
        {
            PrgChk_UpdateJobInfo(PRGCHK_JOB_OK, PRGCHK_STAT_IDLE);
            Ret = E_OK;
        }
        else
        {
            PrgChk_UpdateJobInfo(PRGCHK_JOB_FAILED, PRGCHK_STAT_IDLE);
        }

        PrgChk_ReleaseApiAcceptation();
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | PrgChk_ReqCalcValue                                        */
/* Description   | Requests calculation for program check                     */
/* Preconditions |                                                            */
/* Parameters    | [IN]  TargetAddr : Check target address                    */
/*               | [IN]  TargetSize : Check target size                       */
/*               | [OUT] Value      : Area address of calculated value        */
/*               | [IN]  ValueSize  : Area size of calculated value           */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, PRGCHK_CODE_SLOW) PrgChk_ReqCalcValue
(
    VAR(uint32, AUTOMATIC) TargetAddr,
    VAR(uint32, AUTOMATIC) TargetSize,
    P2VAR(uint8, AUTOMATIC, PRGCHK_APPL_DATA) Value,
    VAR(uint16, AUTOMATIC) ValueSize
)
{
    VAR(uint32, AUTOMATIC) ReadSize;
    VAR(Std_ReturnType, AUTOMATIC) Ret;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    Ret = E_NOT_OK;

    FuncRet = PrgChk_GetApiAcceptation();
    if( FuncRet == (Std_ReturnType)E_OK )
    {
        if( ( PrgChk_JobInfo.LocalStatus == PRGCHK_STAT_PRE_CALC_FINISH ) &&
            ( ValueSize >= PRGCHK_CRC32_VALUE_SIZE ) )
        {
            ReadSize = TargetSize;

            if( ReadSize > PRGCHK_READBUF_SIZE )
            {
                ReadSize = PRGCHK_READBUF_SIZE;
            }

            FuncRet = RpgLib_ReqMemRead(RPGLIB_MEMORYID_0, &PrgChk_CrcCalcAreaReadBuff[0], TargetAddr, ReadSize);
            if( FuncRet == (Std_ReturnType)E_OK )
            {
                PrgChk_CrcCalcInfo.CalcSize = ReadSize;
                PrgChk_CrcCalcInfo.RemainSize = TargetSize - ReadSize;  /* no wrap around */
                PrgChk_CrcCalcInfo.NextAddress = TargetAddr + ReadSize; /* no wrap around */
                PrgChk_CrcCalcInfo.ResultPtr = Value;
                PrgChk_CrcCalcInfo.IsFirstCall = TRUE;

                PrgChk_UpdateJobInfo(PRGCHK_JOB_PENDING, PRGCHK_STAT_REQ_CALC);

                Ret = E_OK;
            }
        }

        if( Ret != (Std_ReturnType)E_OK )
        {
            PrgChk_UpdateJobInfo(PRGCHK_JOB_FAILED, PRGCHK_STAT_IDLE);
        }

        PrgChk_ReleaseApiAcceptation();
    }

    return Ret;
}

/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

/******************************************************************************/
/* Function Name | PrgChk_UpdateJobInfo                                       */
/* Description   | Update PrgChk job information                              */
/* Preconditions |                                                            */
/* Parameters    | [IN] JobResult   : Result of job                           */
/*               |       PRGCHK_JOB_OK                                        */
/*               |       PRGCHK_JOB_PENDING                                   */
/*               |       PRGCHK_JOB_FAILED                                    */
/*               | [IN] LocalStatus : Status of job                           */
/*               |       PRGCHK_STAT_IDLE                                     */
/*               |       PRGCHK_STAT_PRE_CALC_FINISH                          */
/*               |       PRGCHK_STAT_REQ_CALC                                 */
/*               |       PRGCHK_STAT_REQ_CALC_FINISH                          */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, PRGCHK_CODE_FAST) PrgChk_UpdateJobInfo
(
    VAR(uint8, AUTOMATIC) JobResult,
    VAR(uint8, AUTOMATIC) LocalStatus
)
{
    VAR(uint8, AUTOMATIC) MaskPattern;

    MaskPattern = Rte_MaskInterruptAll();   /* for JobResult/LocalStatus */
    PrgChk_JobInfo.JobResult = JobResult;
    PrgChk_JobInfo.LocalStatus = LocalStatus;
    Rte_UnMaskInterruptAll(MaskPattern);    /* for JobResult/LocalStatus */

    return;
}

/******************************************************************************/
/* Function Name | PrgChk_GetApiAcceptation                                   */
/* Description   | Acquires the acceptation of executing API                  */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(Std_ReturnType, PRGCHK_CODE_FAST) PrgChk_GetApiAcceptation (void)
{
    VAR(uint8, AUTOMATIC) MaskPattern;
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Ret = E_NOT_OK;

    MaskPattern = Rte_MaskInterruptAll();   /* prevent multiple execution */
    if( PrgChk_ApiAcceptingFlg == (uint8)STD_OFF )
    {
        PrgChk_ApiAcceptingFlg = STD_ON;
        Ret = E_OK;
    }
    Rte_UnMaskInterruptAll(MaskPattern);    /* prevent multiple execution */

    return Ret;
}

/******************************************************************************/
/* Function Name | PrgChk_ReleaseApiAcceptation                               */
/* Description   | Releases the acceptation of executing API                  */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, PRGCHK_CODE_FAST) PrgChk_ReleaseApiAcceptation (void)
{
    PrgChk_ApiAcceptingFlg = STD_OFF;

    return;
}

#define PRGCHK_STOP_SEC_CODE
#include <PrgChk_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/06/07 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

