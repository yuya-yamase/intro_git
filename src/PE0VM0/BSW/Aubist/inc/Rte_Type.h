/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

#ifndef RTE_TYPE_H
#define RTE_TYPE_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct {
    uint32 u4ErrorFactor;
    uint32 u4ErrorState;
} Mscd_ErrorInfo_ErrorFactorInfoType;

typedef struct {
    uint16 u2BlockId;
    uint32 u4ErrorResult;
} Mscd_ErrorInfo_ErrorResultInfoType;

typedef uint8 Mscd_MsStatusType;

typedef uint16 NvM_BlockIdType;

typedef uint8 NvM_BlockRequestType;

typedef uint8 NvM_InitBlockRequestType;

typedef uint8 NvM_MultiBlockRequestType;

typedef uint8 NvM_RequestResultType;

#endif /* RTE_TYPE_H */
/**** End of File ***********************************************************/
