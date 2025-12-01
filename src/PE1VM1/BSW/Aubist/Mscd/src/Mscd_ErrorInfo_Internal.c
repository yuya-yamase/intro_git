/* Mscd_ErrorInfo_Internal.c v2-0-0                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | MSCD/ERRORINFO/INTERNAL/CODE                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Mscd.h>
#include <Mscd_Common.h>

#include "../inc/Mscd_ErrorInfo_Internal.h"

#include "../inc/Mscd_Msif.h"

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
#define MSCD_START_SEC_VAR_NO_INIT_32
#include <Mscd_MemMap.h>

#if ( MSCD_ERRORINFO_USE == STD_ON )

VAR(Mscd_ErrorInfo_ErrorFactorInfoType, MSCD_VAR_NO_INIT) Mscd_ErrorInfo_stErrorFactorInfo;
VAR(Mscd_ErrorInfo_ErrorResultInfoType, MSCD_VAR_NO_INIT) Mscd_ErrorInfo_stSingleErrorResultInfo;
VAR(Mscd_ErrorInfo_ErrorResultInfoType, MSCD_VAR_NO_INIT) Mscd_ErrorInfo_stMultiErrorResultInfo;
VAR(NvM_BlockRequestType, MSCD_VAR_NO_INIT)               Mscd_ErrorInfo_u1CurrentSingleBlockRequest;
VAR(NvM_MultiBlockRequestType, MSCD_VAR_NO_INIT)          Mscd_ErrorInfo_u1CurrentMultiBlockRequest;

#endif /*( MSCD_ERRORINFO_USE == STD_ON )*/

#define MSCD_STOP_SEC_VAR_NO_INIT_32
#include <Mscd_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define MSCD_START_SEC_CONST_32
#include <Mscd_MemMap.h>

#if ( MSCD_ERRORINFO_USE == STD_ON )

CONST( AB_83_ConstV Mscd_ErrorInfo_ErrorFactorInfoType, MSCD_CONST) Mscd_ErrorInfo_stErrorFactor_BitPtnTbl[MSCD_ERRINFO_ERRORFACTOR_NUM] = {
    { MSCD_ERRINFO_FACTOR_FATALERROR,     (MSCD_ERRINFO_STATE_READ_DISABLE | MSCD_ERRINFO_STATE_WRITE_DISABLE) },
    { MSCD_ERRINFO_FACTOR_HSMERROR,       (MSCD_ERRINFO_STATE_READ_DISABLE | MSCD_ERRINFO_STATE_WRITE_DISABLE) },
    { MSCD_ERRINFO_FACTOR_NVM_FATALERROR, (MSCD_ERRINFO_STATE_READ_DISABLE | MSCD_ERRINFO_STATE_WRITE_DISABLE) }
};

CONST( AB_83_ConstV Mscd_ErrorInfo_ErrorResultType, MSCD_CONST) Mscd_ErrorInfo_stErrorResult_BitPtnTbl[MSCD_ERRINFO_SERVICE_ERRORSTATE_NUM] = {
    { MSCD_ERRINFO_FEE_KIND_RESTORE,                  MSCD_ERRINFO_RESULT_RESTORE                   },
    { MSCD_ERRINFO_FEE_ERR_NODATA,                    MSCD_ERRINFO_RESULT_NODATA                    },
    { MSCD_ERRINFO_FEE_ERR_NG_WRITE,                  MSCD_ERRINFO_RESULT_WRITE_NG                  },
    { MSCD_ERRINFO_FEE_ERR_TIMEOUT,                   MSCD_ERRINFO_RESULT_DRV_TIMEOUT               },
    { MSCD_ERRINFO_FEE_KIND_RECOVER,                  MSCD_ERRINFO_RESULT_VANISH_DATA               },
    { MSCD_ERRINFO_FEE_ERR_NG_DTF_CTRL,               MSCD_ERRINFO_RESULT_HARD_NG                   },
    { MSCD_ERRINFO_FEE_ERR_NG_INTERNAL,               MSCD_ERRINFO_RESULT_INTERNAL_NG               },
    { MSCD_ERRINFO_FEE_ERR_UNUSED,                    MSCD_ERRINFO_RESULT_UNUSED                    },
    { MSCD_ERRINFO_FEE_ERR_VANISH_AREA,               MSCD_ERRINFO_RESULT_VANISH_AREA               },
    { MSCD_ERRINFO_FEE_ERR_IRBLD_CNFM_NOT_OK,         MSCD_ERRINFO_RESULT_IRBLD_CNFM_NOT_OK         },
    { MSCD_ERRINFO_FEE_ERR_VOLT_CNFM_NOT_OK,          MSCD_ERRINFO_RESULT_VOLT_CNFM_NOT_OK          },
    { MSCD_ERRINFO_FEE_ERR_UNDEFINED,                 MSCD_ERRINFO_RESULT_UNDEFINED                 },
    { MSCD_ERRINFO_NVM_ERR_JOB_TIMEOUT,               MSCD_ERRINFO_RESULT_JOB_TIMEOUT               },
    { MSCD_ERRINFO_NVM_ERR_SYNC_MECHANISM_NG,         MSCD_ERRINFO_RESULT_SYNC_MECHANISM_NG         },
    { MSCD_ERRINFO_NVM_ERR_WRT_TO_PROT_SKIP,          MSCD_ERRINFO_RESULT_WRT_TO_PROT_SKIP          },
    { MSCD_ERRINFO_NVM_ERR_WRT_FRM_INVALID_RAM_SKIP,  MSCD_ERRINFO_RESULT_WRT_FRM_INVALID_RAM_SKIP  },
    { MSCD_ERRINFO_NVM_ERR_WRT_FRM_UNCHANGE_RAM_SKIP, MSCD_ERRINFO_RESULT_WRT_FRM_UNCHANGE_RAM_SKIP },
    { MSCD_ERRINFO_NVM_ERR_READ_TO_VALID_RAM_SKIP,    MSCD_ERRINFO_RESULT_READ_TO_VALID_RAM_SKIP    },
    { MSCD_ERRINFO_NVM_ERR_ABORT,                     MSCD_ERRINFO_RESULT_ABORT                     },
    { MSCD_ERRINFO_NVM_ERR_CANCEL_WRT_ALL,            MSCD_ERRINFO_RESULT_CANCEL_WRT_ALL            },
    { MSCD_ERRINFO_NVM_ERR_PREEMPT_IMM_WRT,           MSCD_ERRINFO_RESULT_PREEMPT_IMM_WRT           },
    { MSCD_ERRINFO_NVM_ERR_NODATA,                    MSCD_ERRINFO_RESULT_NODATA                    },
    { MSCD_ERRINFO_NVM_KIND_RESTORE,                  MSCD_ERRINFO_RESULT_RESTORE                   },
    { MSCD_ERRINFO_NVM_ERR_LOSS_OF_REDUNDANCY,        MSCD_ERRINFO_RESULT_LOSS_OF_REDUNDANCY        }
};

#endif /*( MSCD_ERRORINFO_USE == STD_ON )*/

#define MSCD_STOP_SEC_CONST_32
#include <Mscd_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define MSCD_START_SEC_CODE
#include <Mscd_MemMap.h>

#if ( MSCD_ERRORINFO_USE == STD_ON )
/****************************************************************************/
/* Function Name | Mscd_ErrorInfo_UpdateStateErrorFactor                    */
/*               | (error status update)                                    */
/* Description   | Update error status                                      */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, MSCD_CODE)
Mscd_ErrorInfo_UpdateStateErrorFactor( void )
{
    uint8 u1ErrorFactorCnt;
    uint32 u4TmpErrorFactor;

    /* Update Error status */
    Mscd_ErrorInfo_stErrorFactorInfo.u4ErrorState = MSCD_ERRINFO_NO_ERROR;
    for ( u1ErrorFactorCnt = 0U; u1ErrorFactorCnt < (uint8)MSCD_ERRINFO_ERRORFACTOR_NUM; u1ErrorFactorCnt++ )
    {
        u4TmpErrorFactor = (Mscd_ErrorInfo_stErrorFactorInfo.u4ErrorFactor & Mscd_ErrorInfo_stErrorFactor_BitPtnTbl[u1ErrorFactorCnt].u4ErrorFactor);
        if ( (uint32)MSCD_ERRINFO_NO_ERROR != u4TmpErrorFactor )
        {
            Mscd_ErrorInfo_stErrorFactorInfo.u4ErrorState |= Mscd_ErrorInfo_stErrorFactor_BitPtnTbl[u1ErrorFactorCnt].u4ErrorState;
        }
    }

    return;
}
#endif /*( MSCD_ERRORINFO_USE == STD_ON )*/

#if ( MSCD_ERRORINFO_USE == STD_ON )
/****************************************************************************/
/* Function Name | Mscd_ErrorInfo_TransformErrorResult                      */
/*               | (error information (result) conversion)                  */
/* Description   | Convert error information (results) for NVM-defined services  */
/*               | into error information (results) for the ERRINFO component */
/* Preconditions |                                                          */
/* Parameters    | u4ErrorResult    : Error information (result for NVM)    */
/* Return Value  | uint32           : error information (result for ERRINFO)*/
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint32, MSCD_CODE)
Mscd_ErrorInfo_TransformErrorResult( uint32 u4ErrorResult )
{
    uint8 u1ErrorResultCnt;
    uint32 u4TmpErrorResult;
    uint32 u4TransErrorResult;

    u4TransErrorResult = MSCD_ERRINFO_NO_ERROR;

    /* Convert error information (results) in the definition value of ERRINFO component */
    for ( u1ErrorResultCnt = 0U;
         u1ErrorResultCnt < (uint8)MSCD_ERRINFO_SERVICE_ERRORSTATE_NUM;
         u1ErrorResultCnt++ )
    {
        u4TmpErrorResult = (u4ErrorResult & Mscd_ErrorInfo_stErrorResult_BitPtnTbl[u1ErrorResultCnt].u4ErrorResultNvm);
        if ( u4TmpErrorResult != (uint32)MSCD_ERRINFO_NO_ERROR )
        {
            u4TransErrorResult |= Mscd_ErrorInfo_stErrorResult_BitPtnTbl[u1ErrorResultCnt].u4ErrorResult;
        }
    }

    return u4TransErrorResult;
}
#endif /*( MSCD_ERRORINFO_USE == STD_ON )*/


#define MSCD_STOP_SEC_CODE
#include <Mscd_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/*  1-1-0          :2019/01/31                                              */
/*  1-2-0          :2019/09/06                                              */
/*  2-0-0          :2020/12/22                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
