/* Fee_Ext.h v2-0-0                                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/EXT/HEADER                                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef FEE_EXT_H
#define FEE_EXT_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include "../Fee/cfg/Fee_Cfg.h"

/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/* Job Results output by DirectAccess */
#define FEE_EXT_DRCT_JOB_OK                 (0x00U)
#define FEE_EXT_DRCT_JOB_BUSY               (0x01U)
#define FEE_EXT_DRCT_JOB_BLANK              (0x02U)
#define FEE_EXT_DRCT_JOB_NOT_BLANK          (0x03U)
#define FEE_EXT_DRCT_JOB_ERROR              (0x04U)
#define FEE_EXT_DRCT_JOB_CANCELED           (0x05U)
#define FEE_EXT_DRCT_JOB_FATALERROR         (0x06U)
#define FEE_EXT_DRCT_JOB_ACCEPT             (0x07U)
#define FEE_EXT_DRCT_JOB_NOT_ACCEPT         (0x08U)
#define FEE_EXT_DRCT_JOB_INOPERATIVE_HSM    (0x09U)
#define FEE_EXT_DRCT_JOB_INTEGRITY_FAILED   (0x0AU)

/* Status of DirectAccess */
#define FEE_EXT_DRCT_STATUS_IDLE            (0x00U)
#define FEE_EXT_DRCT_STATUS_BUSY            (0x01U)
#define FEE_EXT_DRCT_STATUS_ERROR           (0x02U)

/* Return values of getting free space. */
#define FEE_EXT_E_FRSP_OK                   (0x00U)
#define FEE_EXT_E_FRSP_PARAM_ERROR          (0x01U)
#define FEE_EXT_E_FRSP_BUSY                 (0x02U)
#define FEE_EXT_E_FRSP_AREA_FAULT           (0x03U)
#define FEE_EXT_E_FRSP_INTERNAL_ERROR       (0x04U)

/* Detail results of getting free space. */
#define FEE_EXT_FRSP_RESULT_OK                      (0x00U)
#define FEE_EXT_FRSP_RESULT_MNG_OVER_LIMIT          (0x01U)
#define FEE_EXT_FRSP_RESULT_DATA_OVER_LIMIT         (0x02U)
#define FEE_EXT_FRSP_RESULT_PENDING_RBLD            (0x04U)
#define FEE_EXT_FRSP_RESULT_BLANK                   (0x08U)
#define FEE_EXT_FRSP_RESULT_AREAINFO_INCONSISTENT   (0x10U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef uint8 Fee_ExtDirect_ReturnType;
typedef uint8 Fee_ExtDirectStatusType;

/* For getting free space. */
typedef uint8 Fee_ExtFreeSpaceReturnType;
typedef uint8 Fee_ExtFreeSpaceResultType;
typedef struct{
    Fee_ExtFreeSpaceResultType  Result;
    uint16                      RcrdNum;
    uint32                      DataAreaByte;
}Fee_ExtFreeSpaceInfoType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define FEE_START_SEC_CODE
#include <Fee_MemMap.h>

FUNC( void,           FEE_CODE ) Fee_MainFunction_ExtNonPeriodic( void );

FUNC( Fee_ExtDirect_ReturnType, FEE_CODE )
Fee_ExtDirectWrite(
    uint32 u4Address,
    uint32 u4Length,
    P2CONST( uint8, AUTOMATIC, TYPEDEF ) ptWriteData
);

FUNC( Fee_ExtDirect_ReturnType, FEE_CODE )
Fee_ExtDirectErase(
    uint32 u4Address,
    uint16 u2SectorNum
);

FUNC( void, FEE_CODE )
Fee_ExtDirectMainFunction(
    void
);

FUNC( Fee_ExtDirectStatusType, FEE_CODE )
Fee_ExtDirectGetStatus( void );

FUNC( Fee_ExtDirect_ReturnType, FEE_CODE )
Fee_ExtGetDirectJobResult(
    void
);

FUNC( Fee_ExtDirect_ReturnType, FEE_CODE )
Fee_ExtDirectRead(
    uint32 u4Address,
    uint32 u4Length,
    P2VAR( uint8, AUTOMATIC, TYPEDEF ) ptReadData
);

FUNC( Fee_ExtDirect_ReturnType, FEE_CODE )
Fee_ExtDirectBlankCheck(
    uint32 u4Address,
    uint32 u4Length
);

FUNC( Fee_ExtFreeSpaceReturnType, FEE_CODE )
Fee_ExtGetFreeSpace(
    uint8  AreaNo,
    uint16 LimitSearchMngArea,
    uint32 LimitSearchDataArea,
    P2VAR( Fee_ExtFreeSpaceInfoType, AUTOMATIC, TYPEDEF ) FreeSpaceInfoPtr
);

FUNC( MemIf_ExtProductionErrorType, FEE_CODE )
Fee_ExtGetProductionError(
    P2VAR(uint16, AUTOMATIC, TYPEDEF) BlockNumber,
    P2VAR(uint8, AUTOMATIC, TYPEDEF) JobKind,
    P2VAR(uint8, AUTOMATIC, TYPEDEF) Level
);

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

#endif    /* FEE_EXT_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/*  1-0-1          :2019/02/01                                              */
/*  1-1-0          :2019/10/09                                              */
/*  2-0-0          :2021/05/26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
