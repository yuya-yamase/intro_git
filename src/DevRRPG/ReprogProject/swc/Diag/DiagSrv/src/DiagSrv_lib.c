/* DiagSrv_lib_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | DiagSrv/Lib/CODE                                            */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <DiagLib.h>
#include <RpgLib.h>
#include <Rte.h>

#if (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON)
#include <DiagSrv.h>
#endif

#include "DiagSrv_lib_Cfg.h"
#include "DiagSrv_Local.h"


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_SBL_CLEAR_SIZE              (32U)
#define DIAGSRV_REWRITESTSMATRIXTBL_NUM     (sizeof(DiagSrv_RewriteStatMatrixTbl) / sizeof(DiagSrv_RewriteStatMatrixTbl[0]))


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef struct {
    uint8 Before;
    uint8 After;
} DiagSrv_RewriteStatMatrixType;

typedef struct {
    uint32 Num;
    P2CONST(DiagSrv_RewriteStatMatrixType, TYPEDEF, DIAGSRV_APPL_CONST) MatrixPtr;
} DiagSrv_RewriteStatMatInfoType;


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_InvalidSbl (void);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_VAR
#include <DiagSrv_MemMap.h>

static VAR(uint8, DIAGSRV_VAR_CLEARED) DiagSrv_RewriteStatus;
static VAR(uint8, DIAGSRV_VAR_CLEARED) DiagSrv_CipherTextMode;
static VAR(uint8, DIAGSRV_VAR_CLEARED) DiagSrv_CompressionMode;
static VAR(uint8, DIAGSRV_VAR_CLEARED) DiagSrv_FingerPrintTmpArea[DIAGSRV_CFG_FINGERPRINT_SIZE];
static VAR(uint8, DIAGSRV_VAR_CLEARED) DiagSrv_ChangePrgSessionFlag;
static VAR(uint8, DIAGSRV_VAR_CLEARED) DiagSrv_WriteDeviceType;

#define DIAGSRV_STOP_SEC_VAR
#include <DiagSrv_MemMap.h>

#define DIAGSRV_START_SEC_VAR_NONCE
#include <DiagSrv_MemMap.h>

static VAR(uint8, DIAGSRV_VAR_CLEARED) DiagSrv_NonceTmpArea[DIAGSRV_NONCE_BUFF_SIZE];

#define DIAGSRV_STOP_SEC_VAR_NONCE
#include <DiagSrv_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_CST
#include <DiagSrv_MemMap.h>

static CONST(DiagSrv_RewriteStatMatrixType, DIAGSRV_CONST) DiagSrv_RewriteStatMatrixTbl[] = {
     { DIAGSRV_REWRITESTAT_IDLE,             DIAGSRV_REWRITESTAT_FINGER_RECV      }
    ,{ DIAGSRV_REWRITESTAT_FINGER_RECV,      DIAGSRV_REWRITESTAT_READY            }
    ,{ DIAGSRV_REWRITESTAT_READY,            DIAGSRV_REWRITESTAT_SBL_DL_START     }
    ,{ DIAGSRV_REWRITESTAT_SBL_DL_START,     DIAGSRV_REWRITESTAT_SBL_DL_UPDATE    }
    ,{ DIAGSRV_REWRITESTAT_SBL_DL_UPDATE,    DIAGSRV_REWRITESTAT_SBL_DL_END       }
    ,{ DIAGSRV_REWRITESTAT_SBL_DL_END,       DIAGSRV_REWRITESTAT_SBL_DL_COMPLETE  }
    ,{ DIAGSRV_REWRITESTAT_SBL_DL_COMPLETE,  DIAGSRV_REWRITESTAT_SBL_DL_CHECK     }
    ,{ DIAGSRV_REWRITESTAT_SBL_DL_CHECK,     DIAGSRV_REWRITESTAT_ERASE            }
    ,{ DIAGSRV_REWRITESTAT_ERASE,            DIAGSRV_REWRITESTAT_DATA_DL_START    }
    ,{ DIAGSRV_REWRITESTAT_DATA_DL_START,    DIAGSRV_REWRITESTAT_DATA_DL_UPDATE   }
    ,{ DIAGSRV_REWRITESTAT_DATA_DL_UPDATE,   DIAGSRV_REWRITESTAT_DATA_DL_END      }
    ,{ DIAGSRV_REWRITESTAT_DATA_DL_END,      DIAGSRV_REWRITESTAT_DATA_DL_COMPLETE }
    ,{ DIAGSRV_REWRITESTAT_DATA_DL_COMPLETE, DIAGSRV_REWRITESTAT_DATA_CHECK       }
    ,{ DIAGSRV_REWRITESTAT_DATA_CHECK,       DIAGSRV_REWRITESTAT_VALIDATE         }
    ,{ DIAGSRV_REWRITESTAT_DATA_CHECK,       DIAGSRV_REWRITESTAT_FINGER_RECV      }
};

static CONST(AB_83_ConstV DiagSrv_RewriteStatMatInfoType, DIAGSRV_CONST) DiagSrv_RewriteStatMatInfo = {
    DIAGSRV_REWRITESTSMATRIXTBL_NUM,
    &DiagSrv_RewriteStatMatrixTbl[0]
};

#define DIAGSRV_STOP_SEC_CST
#include <DiagSrv_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define DIAGSRV_START_SEC_CODE
#include <DiagSrv_MemMap.h>

/******************************************************************************/
/* Function Name | DiagSrv_lib_Init                                           */
/* Description   | Initializes internal value                                 */
/* Preconditions |                                                            */
/* Parameters    | [IN] BootModeEx : Extended boot mode                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_lib_Init
(
    VAR(uint8, AUTOMATIC) BootModeEx
)
{
    VAR(uint8, AUTOMATIC) i;

    DiagSrv_SetRewriteStatus(DIAGSRV_REWRITESTAT_IDLE);

    DiagSrv_SetWriteDeviceType(DIAGSRV_DEVICE_TYPE_CODERAM);

    DiagSrv_EnableChangePrgSession();

    for( i = 0U; i < DiagSrv_RewriteAreaStatus.StatusInfoNum; i++ )
    {
        DiagSrv_RewriteAreaStatus.StatusInfoPtr[i].RewriteAreaNum = DiagSrv_RewriteAreaConfig.InfoPtr[i].RewriteAreaNum;
        DiagSrv_RewriteAreaStatus.StatusInfoPtr[i].Status = DIAGSRV_LBSTAT_BEFORE_REWRITING;
    }

    DiagSrv_RewriteAreaStatus.BootInfoPtr->ExtendedBootMode = BootModeEx;

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_GetRewriteStatus                                   */
/* Description   | Acquires rewrite status                                    */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Status                                                     */
/*               |  DIAGSRV_REWRITESTAT_IDLE                                  */
/*               |  DIAGSRV_REWRITESTAT_FINGER_RECV                           */
/*               |  DIAGSRV_REWRITESTAT_READY                                 */
/*               |  DIAGSRV_REWRITESTAT_SBL_DL_START                          */
/*               |  DIAGSRV_REWRITESTAT_SBL_DL_UPDATE                         */
/*               |  DIAGSRV_REWRITESTAT_SBL_DL_END                            */
/*               |  DIAGSRV_REWRITESTAT_SBL_DL_COMPLETE                       */
/*               |  DIAGSRV_REWRITESTAT_SBL_DL_CHECK                          */
/*               |  DIAGSRV_REWRITESTAT_ERASE                                 */
/*               |  DIAGSRV_REWRITESTAT_DATA_DL_START                         */
/*               |  DIAGSRV_REWRITESTAT_DATA_DL_UPDATE                        */
/*               |  DIAGSRV_REWRITESTAT_DATA_DL_END                           */
/*               |  DIAGSRV_REWRITESTAT_DATA_DL_COMPLETE                      */
/*               |  DIAGSRV_REWRITESTAT_DATA_CHECK                            */
/*               |  DIAGSRV_REWRITESTAT_VALIDATE                              */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_GetRewriteStatus (void)
{
    return DiagSrv_RewriteStatus;
}

/******************************************************************************/
/* Function Name | DiagSrv_SetRewriteStatus                                   */
/* Description   | Acquires rewrite status                                    */
/* Preconditions |                                                            */
/* Parameters    | [IN] Status : Rewrite status                               */
/*               |       DIAGSRV_REWRITESTAT_IDLE                             */
/*               |       DIAGSRV_REWRITESTAT_FINGER_RECV                      */
/*               |       DIAGSRV_REWRITESTAT_READY                            */
/*               |       DIAGSRV_REWRITESTAT_SBL_DL_START                     */
/*               |       DIAGSRV_REWRITESTAT_SBL_DL_UPDATE                    */
/*               |       DIAGSRV_REWRITESTAT_SBL_DL_END                       */
/*               |       DIAGSRV_REWRITESTAT_SBL_DL_COMPLETE                  */
/*               |       DIAGSRV_REWRITESTAT_SBL_DL_CHECK                     */
/*               |       DIAGSRV_REWRITESTAT_ERASE                            */
/*               |       DIAGSRV_REWRITESTAT_DATA_DL_START                    */
/*               |       DIAGSRV_REWRITESTAT_DATA_DL_UPDATE                   */
/*               |       DIAGSRV_REWRITESTAT_DATA_DL_END                      */
/*               |       DIAGSRV_REWRITESTAT_DATA_DL_COMPLETE                 */
/*               |       DIAGSRV_REWRITESTAT_DATA_CHECK                       */
/*               |       DIAGSRV_REWRITESTAT_VALIDATE                         */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_SetRewriteStatus
(
    VAR(uint8, AUTOMATIC) Status
)
{
    VAR(uint32, AUTOMATIC) i;
    VAR(uint8, AUTOMATIC) ChangeFlg;

    ChangeFlg = STD_OFF;

    if( Status == DIAGSRV_REWRITESTAT_IDLE )
    {
        ChangeFlg = STD_ON;
    }
    else if( Status == DiagSrv_RewriteStatus )
    {
        /* No process */
    }
    else
    {
        for( i = 0U; i < DiagSrv_RewriteStatMatInfo.Num; i++ )
        {
            if( ( DiagSrv_RewriteStatus == DiagSrv_RewriteStatMatInfo.MatrixPtr[i].Before ) &&
                ( Status == DiagSrv_RewriteStatMatInfo.MatrixPtr[i].After ) )
            {
                ChangeFlg = STD_ON;
                break;
            }
        }
    }

    if( ChangeFlg == (uint8)STD_ON )
    {
        if ( Status == DIAGSRV_REWRITESTAT_IDLE )
        {
            DiagSrv_SetRewriteAreaNumber(DIAGSRV_REWRITEAREA_INVALID);

            DiagLib_SetTransferMode(DIAG_TFMODE_NONE);

            DiagSrv_SetCipherTextMode(STD_OFF);
            DiagSrv_SetCompressionMode(STD_OFF);
            DiagSrv_ClearNonceTempArea();
            DiagSrv_ClearFingerprintTempArea();

            RpgLib_NotifyFlsCtrlMode(RPGLIB_FLSCTRL_NOTREADY);
            DiagSrv_InvalidSbl();

#if (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON)
            DiagSrv_SubM_ClearSequence();
#endif
        }
        else if( Status == DIAGSRV_REWRITESTAT_SBL_DL_START )
        {
            RpgLib_NotifyFlsCtrlMode(RPGLIB_FLSCTRL_NOTREADY);
            DiagSrv_InvalidSbl();
        }
        else if( Status == DIAGSRV_REWRITESTAT_SBL_DL_COMPLETE )
        {
            DiagSrv_SetCipherTextMode(STD_OFF);
            DiagSrv_SetCompressionMode(STD_OFF);
        }
        else if( Status == DIAGSRV_REWRITESTAT_SBL_DL_CHECK )
        {
            RpgLib_NotifyFlsCtrlMode(RPGLIB_FLSCTRL_READY);
        }
        else if( Status == DIAGSRV_REWRITESTAT_DATA_DL_COMPLETE )
        {
            DiagSrv_SetCipherTextMode(STD_OFF);
            DiagSrv_SetCompressionMode(STD_OFF);
            DiagSrv_ClearNonceTempArea();
        }
        else if( Status == DIAGSRV_REWRITESTAT_DATA_CHECK )
        {
            DiagSrv_ClearFingerprintTempArea();
        }
        else
        {
            /* No process */
        }

        DiagSrv_RewriteStatus = Status;
    }

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_GetCipherTextMode                                  */
/* Description   | Acquires ciphertext mode                                   */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Flag                                                       */
/*               |  STD_ON                                                    */
/*               |  STD_OFF                                                   */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_GetCipherTextMode (void)
{
    return DiagSrv_CipherTextMode;
}

/******************************************************************************/
/* Function Name | DiagSrv_SetCipherTextMode                                  */
/* Description   | Sets ciphertext mode                                       */
/* Preconditions |                                                            */
/* Parameters    | [IN] Flag : Ciphertext mode                                */
/*               |       STD_ON                                               */
/*               |       STD_OFF                                              */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_SetCipherTextMode
(
    VAR(uint8, AUTOMATIC) Flag
)
{
    DiagSrv_CipherTextMode = Flag;

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_GetCompressionMode                                 */
/* Description   | Acquires compression mode                                  */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Flag                                                       */
/*               |  STD_ON                                                    */
/*               |  STD_OFF                                                   */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_GetCompressionMode (void)
{
    return DiagSrv_CompressionMode;
}

/******************************************************************************/
/* Function Name | DiagSrv_SetCompressionMode                                 */
/* Description   | Sets compression mode                                      */
/* Preconditions |                                                            */
/* Parameters    | [IN] Flag : Compression mode                               */
/*               |       STD_ON                                               */
/*               |       STD_OFF                                              */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_SetCompressionMode
(
    VAR(uint8, AUTOMATIC) Flag
)
{
    DiagSrv_CompressionMode = Flag;

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_GetNonceTempArea                                   */
/* Description   | Acquires nonce temporary area                              */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Temporarily save area                                      */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC_P2VAR(uint8, DIAGSRV_APPL_DATA, DIAGSRV_CODE_FAST) DiagSrv_GetNonceTempArea (void)
{
    return DiagSrv_NonceTmpArea;
}

/******************************************************************************/
/* Function Name | DiagSrv_SetNonceTempArea                                   */
/* Description   | Sets nonce temporary area                                  */
/* Preconditions |                                                            */
/* Parameters    | [IN] Nonce : Nonce                                         */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_SetNonceTempArea
(
    P2CONST(uint8, AUTOMATIC, DIAGSRV_APPL_CONST) Nonce
)
{
    Rte_Rpg_MemCopy(DiagSrv_NonceTmpArea, Nonce, sizeof(DiagSrv_NonceTmpArea));

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_ClearNonceTempArea                                 */
/* Description   | Clear nonce temporary area                                 */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_ClearNonceTempArea (void)
{
    Rte_Rpg_MemSet(DiagSrv_NonceTmpArea, 0U, sizeof(DiagSrv_NonceTmpArea));

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_GetFingerprintTempArea                             */
/* Description   | Acquires fingerprint temporary area                        */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Temporarily save area                                      */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC_P2VAR(uint8, DIAGSRV_APPL_DATA, DIAGSRV_CODE_FAST) DiagSrv_GetFingerprintTempArea (void)
{
    return &DiagSrv_FingerPrintTmpArea[0];
}

/******************************************************************************/
/* Function Name | DiagSrv_SetFingerprintTempArea                             */
/* Description   | Sets fingerprint temporary area                            */
/* Preconditions |                                                            */
/* Parameters    | [IN] Fingerprint : Fingerprint                             */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_SetFingerprintTempArea
(
    P2CONST(uint8, AUTOMATIC, DIAGSRV_APPL_CONST) Fingerprint
)
{
    Rte_Rpg_MemCopy(&DiagSrv_FingerPrintTmpArea[0], Fingerprint, sizeof(DiagSrv_FingerPrintTmpArea));

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_ClearFingerprintTempArea                           */
/* Description   | Clear fingerprint temporary area                           */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_ClearFingerprintTempArea (void)
{
    Rte_Rpg_MemSet(&DiagSrv_FingerPrintTmpArea[0], 0U, sizeof(DiagSrv_FingerPrintTmpArea));

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_GetRprgDataAreaInfo                                */
/* Description   | Acquires RPRG data area                                    */
/* Preconditions |                                                            */
/* Parameters    | [IN]  RewriteAreaNum : Rewrite area number                 */
/*               | [OUT] DataAddr       : RPRG data address                   */
/*               | [OUT] DataSize       : RPRG data size                      */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_GetRprgDataAreaInfo
(
    VAR(uint8, AUTOMATIC) RewriteAreaNum,
    P2VAR(uint32, AUTOMATIC, DIAGSRV_APPL_DATA) DataAddr,
    P2VAR(uint32, AUTOMATIC, DIAGSRV_APPL_DATA) DataSize
)
{
    VAR(uint8, AUTOMATIC) i;

    for( i = 0U; i < DiagSrv_RprgDataAreaConfig.RewriteInfoNum; i++ )
    {
        if( RewriteAreaNum == DiagSrv_RprgDataAreaConfig.InfoPtr[i].RewriteAreaNum )
        {
            *DataAddr = DiagSrv_RprgDataAreaConfig.InfoPtr[i].RprgDataAddr;
            *DataSize = DiagSrv_RprgDataAreaConfig.InfoPtr[i].RprgDataSize;
            break;
        }
    }

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_GetEraseAreaInfo                                   */
/* Description   | Acquires erase area                                        */
/* Preconditions |                                                            */
/* Parameters    | [IN]  RewriteAreaNum : Rewrite area number                 */
/*               | [OUT] EraseAddr      : Erase address                       */
/*               | [OUT] EraseSize      : Erase size                          */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, DIAGSRV_CODE_FAST) DiagSrv_GetEraseAreaInfo
(
    VAR(uint8, AUTOMATIC) RewriteAreaNum,
    P2VAR(uint32, AUTOMATIC, DIAGSRV_APPL_DATA) EraseAddr,
    P2VAR(uint32, AUTOMATIC, DIAGSRV_APPL_DATA) EraseSize
)
{
    VAR(RpgLib_MemBlockInfoType, AUTOMATIC) StartBlockInfo;
    VAR(RpgLib_MemBlockInfoType, AUTOMATIC) EndBlockInfo;
    VAR(uint32, AUTOMATIC) RewriteAddr;
    VAR(uint32, AUTOMATIC) RewriteSize;
    VAR(uint32, AUTOMATIC) RewriteEndNextAddr;
    VAR(Std_ReturnType, AUTOMATIC) FucRet;
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Ret = E_NOT_OK;

    RewriteAddr = 0UL;
    RewriteSize = 0UL;
    DiagSrv_GetRewriteAreaInfo(RewriteAreaNum, &RewriteAddr, &RewriteSize);

    RewriteEndNextAddr = RewriteAddr + RewriteSize; /* no wrap around */
    if( RewriteEndNextAddr > 0UL )
    {
        StartBlockInfo.BlockTopAddr = 0UL;
        StartBlockInfo.BlockSize = 0UL;
        FucRet = RpgLib_GetMemBlockInfo(RPGLIB_MEMORYID_0, RewriteAddr, &StartBlockInfo);
        if( FucRet == (Std_ReturnType)E_OK )
        {
            EndBlockInfo.BlockTopAddr = 0UL;
            EndBlockInfo.BlockSize = 0UL;
            FucRet = RpgLib_GetMemBlockInfo(RPGLIB_MEMORYID_0, RewriteEndNextAddr - 1UL, &EndBlockInfo);
            if( FucRet == (Std_ReturnType)E_OK )
            {
                *EraseAddr = StartBlockInfo.BlockTopAddr;
                *EraseSize = (EndBlockInfo.BlockTopAddr + EndBlockInfo.BlockSize) - StartBlockInfo.BlockTopAddr;    /* no wrap around */

                Ret = E_OK;
            }
        }
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | DiagSrv_GetVersionAreaInfo                                 */
/* Description   | Acquires version information area                          */
/* Preconditions |                                                            */
/* Parameters    | [OUT] VerAddr : Version area address                       */
/*               | [OUT] VerSize : Version area size                          */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_GetVersionAreaInfo
(
    P2VAR(uint32, AUTOMATIC, DIAGSRV_APPL_DATA) VerAddr,
    P2VAR(uint8, AUTOMATIC, DIAGSRV_APPL_DATA) VerSize
)
{
    *VerAddr = DiagSrv_VersionInfoConfig.VersionAddr;
    *VerSize = DiagSrv_VersionInfoConfig.VersionSize;

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_GetTempVersionAreaInfo                             */
/* Description   | Acquires temporary version information area                */
/* Preconditions |                                                            */
/* Parameters    | [OUT] TempVerAddr : Temporary version area address         */
/*               | [OUT] TempVerSize : Temporary version area size            */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_GetTempVersionAreaInfo
(
    P2VAR(uint32, AUTOMATIC, DIAGSRV_APPL_DATA) TempVerAddr,
    P2VAR(uint8, AUTOMATIC, DIAGSRV_APPL_DATA) TempVerSize
)
{
    *TempVerAddr = DiagSrv_VersionInfoConfig.TemporaryVersionAddr;
    *TempVerSize = DiagSrv_VersionInfoConfig.VersionSize;

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_SetRewriteAreaStatus                               */
/* Description   | Sets rewrite area status                                   */
/* Preconditions |                                                            */
/* Parameters    | [IN] RewriteAreaNum : Rewrite area number                  */
/*               | [IN] Status         : Rewrite area status                  */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_SetRewriteAreaStatus
(
    VAR(uint8, AUTOMATIC) RewriteAreaNum,
    VAR(uint8, AUTOMATIC) Status
)
{
    VAR(uint8, AUTOMATIC) i;

    for( i = 0U; i < DiagSrv_RewriteAreaStatus.StatusInfoNum; i++ )
    {
        if( DiagSrv_RewriteAreaStatus.StatusInfoPtr[i].RewriteAreaNum == RewriteAreaNum )
        {
            if( Status == DIAGSRV_LBSTAT_IN_REWRITING )
            {
                if( (DiagSrv_RewriteAreaStatus.StatusInfoPtr[i].Status == DIAGSRV_LBSTAT_BEFORE_REWRITING) ||
                    (DiagSrv_RewriteAreaStatus.StatusInfoPtr[i].Status == DIAGSRV_LBSTAT_REWRITING_OK) )
                {
                    DiagSrv_RewriteAreaStatus.StatusInfoPtr[i].Status = Status;
                }
            }
            else if( (Status == DIAGSRV_LBSTAT_REWRITING_OK) || (Status == DIAGSRV_LBSTAT_REWRITING_NG) )
            {
                if( DiagSrv_RewriteAreaStatus.StatusInfoPtr[i].Status == DIAGSRV_LBSTAT_IN_REWRITING )
                {
                    DiagSrv_RewriteAreaStatus.StatusInfoPtr[i].Status = Status;
                }
            }
            else
            {
                /* No process */
                /* When SBL rewriting fails, APL still remains,           */
                /* so, transition from DIAGSRV_LBSTAT_BEFORE_REWRITING to */
                /* DIAGSRV_LBSTAT_REWRITING_NG is not performed.          */
            }
            break;
        }
    }

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_GetRewriteAreaStatus                               */
/* Description   | Acquires rewrite area status                               */
/* Preconditions |                                                            */
/* Parameters    | [IN] RewriteAreaNum : Rewrite area number                  */
/* Return Value  | Rewrite area status                                        */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_GetRewriteAreaStatus
(
    VAR(uint8, AUTOMATIC) RewriteAreaNum
)
{
    VAR(uint8, AUTOMATIC) i;
    VAR(uint8, AUTOMATIC) Status;

    Status = DIAGSRV_LBSTAT_REWRITING_NG;

    for( i = 0U; i < DiagSrv_RewriteAreaStatus.StatusInfoNum; i++ )
    {
        if( DiagSrv_RewriteAreaStatus.StatusInfoPtr[i].RewriteAreaNum == RewriteAreaNum )
        {
            Status = DiagSrv_RewriteAreaStatus.StatusInfoPtr[i].Status;
            break;
        }
    }

    return Status;
}

/******************************************************************************/
/* Function Name | DiagSrv_GetRewriteAreaStatusInfo                           */
/* Description   | Acquires rewrite area status information                   */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Rewrite area status information                            */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC_P2CONST(DiagSrv_RewriteAreaStatusType, DIAGSRV_APPL_CONST, DIAGSRV_CODE_FAST) DiagSrv_GetRewriteAreaStatusInfo (void)
{
    return &DiagSrv_RewriteAreaStatus;
}

/******************************************************************************/
/* Function Name | DiagSrv_SetWriteDeviceType                                 */
/* Description   | Sets Write device type                                     */
/* Preconditions |                                                            */
/* Parameters    | [IN] DeviceType : Device type                              */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_SetWriteDeviceType
(
    VAR(uint8, AUTOMATIC) DeviceType
)
{
    DiagSrv_WriteDeviceType = DeviceType;

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_GetWriteDeviceType                                 */
/* Description   | Acquires write device type                                 */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | DiagSrv_WriteDeviceType                                    */
/*               |  DIAGSRV_DEVICE_TYPE_CODEFLS                               */
/*               |  DIAGSRV_DEVICE_TYPE_EXTCODEFLS                            */
/*               |  DIAGSRV_DEVICE_TYPE_CODERAM                               */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_GetWriteDeviceType (void)
{
    return DiagSrv_WriteDeviceType;
}

/******************************************************************************/
/* Function Name | DiagSrv_GetEncryptionFlag                                  */
/* Description   | Acquires encryption flag                                   */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Flag                                                       */
/*               |  DIAGSRV_ENCRYPTIONFLAG_ON                                 */
/*               |  DIAGSRV_ENCRYPTIONFLAG_OFF                                */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_GetEncryptionFlag (void)
{
    return DiagSrv_EncryptionFlagConfig;
}

/******************************************************************************/
/* Function Name | DiagSrv_EnableChangePrgSession                             */
/* Description   | Enable to change to programmingSession                     */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_EnableChangePrgSession (void)
{
    DiagSrv_ChangePrgSessionFlag = STD_ON;

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_DisableChangePrgSession                            */
/* Description   | Disable to change to programmingSession                    */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_DisableChangePrgSession (void)
{
    DiagSrv_ChangePrgSessionFlag = STD_OFF;

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_CheckChangePrgSession                              */
/* Description   | Checks if it can be changed to programmingSession          */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Flag                                                       */
/*               |  STD_ON                                                    */
/*               |  STD_OFF                                                   */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_CheckChangePrgSession (void)
{
    return DiagSrv_ChangePrgSessionFlag;
}


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

/******************************************************************************/
/* Function Name | DiagSrv_InvalidSbl                                         */
/* Description   | Invalidate sbl                                             */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_InvalidSbl (void)
{
    VAR(uint8, AUTOMATIC) DeviceType;
    VAR(uint32, AUTOMATIC) SblAddr;
    VAR(uint32, AUTOMATIC) SblSize;
    VAR(uint32, AUTOMATIC) PhysicalAddr;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    SblAddr = 0UL;
    SblSize = 0UL;
    DiagSrv_GetSblAreaInfo(&SblAddr, &SblSize);

    PhysicalAddr = 0UL;
    DeviceType = RPGLIB_DEVICE_TYPE_CODEFLS;
    FuncRet = RpgLib_CnvPhysicalAddr(RPGLIB_MEMORYID_0, SblAddr, &PhysicalAddr, &DeviceType);
    if( FuncRet == (Std_ReturnType)E_OK )
    {
        Rte_Rpg_MemSet((uint8 *)PhysicalAddr, 0x00U, DIAGSRV_SBL_CLEAR_SIZE);
    }

    return;
}

#define DIAGSRV_STOP_SEC_CODE
#include <DiagSrv_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/10/04 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

