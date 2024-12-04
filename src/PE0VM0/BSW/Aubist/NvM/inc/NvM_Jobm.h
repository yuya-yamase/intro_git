/* NvM_Jobm.h v2-1-0                                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | NVM/JOBM/HEADER                                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     NVM_JOBM_H
#define     NVM_JOBM_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/* Destructive cancel kind */
#define NVM_JOBM_DSTRCTV_CXL_PREEMPTION            (0x00U)
#define NVM_JOBM_DSTRCTV_CXL_TIMEOUT               (0x01U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

typedef struct {
    uint32 u4JobId;
    NvM_BlockIdType u2BlockId;
    P2VAR( uint8, TYPEDEF, NVM_APPL_DATA ) ptDstPtr;
    P2CONST( uint8, TYPEDEF, TYPEDEF ) ptSrcPtr;
} NvM_Jobm_stJobInfomationType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

#define NVM_START_SEC_CODE
#include <NvM_MemMap.h>

FUNC( void, NVM_CODE )
NvM_Jobm_Init( void );

FUNC( Std_ReturnType, NVM_CODE )
NvM_Jobm_RequestJob(
    uint32 u4JobId,
    NvM_BlockIdType u2BlockId,
    P2VAR( uint8, AUTOMATIC, NVM_APPL_DATA ) ptDstPtr,
    P2CONST( uint8, AUTOMATIC, TYPEDEF ) ptSrcPtr
);

FUNC( void, NVM_CODE )
NvM_Jobm_MainFunction(
    uint8 CallMode
);

FUNC( Std_ReturnType, NVM_CODE )
NvM_Jobm_CancelJobs(
    NvM_BlockIdType ReqBlockId
);

FUNC( void, NVM_CODE )
NvM_Jobm_DestructiveCancelJobs( uint8 Kind );

FUNC( void, NVM_CODE )
NvM_Jobm_AbortJobs( void );

#if ( NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON )
FUNC( void, NVM_CODE )
NvM_Jobm_CancelWriteAll( void );
#endif /* NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON */

FUNC( void, NVM_CODE )
NvM_Jobm_SingleBlockEndNotification(
    NvM_BlockIdType u2BlockId,
    uint32 u4JobId,
    uint8 u1JobResult
);

FUNC( void, NVM_CODE )
NvM_Jobm_MultiBlockEndNotification(
    uint32 u4JobId,
    uint8 u1JobResult
);

FUNC( void, NVM_CODE )
NvM_Jobm_NfyIsSglBlkProcStart(
    boolean IsStart
);

FUNC( void, NVM_CODE )
NvM_Jobm_NfyAbortJob(
    NvM_BlockIdType BlockId,
    uint32 JobId
);

#define NVM_STOP_SEC_CODE
#include <NvM_MemMap.h>

#endif  /* NVM_JOBM_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/*  2-1-0          :2022/07/20                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
