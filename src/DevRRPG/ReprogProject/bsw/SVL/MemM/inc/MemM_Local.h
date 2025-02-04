/* MemM_Local_h_Revision(v2.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | MemM/Local/HEADER                                           */
/******************************************************************************/
#ifndef MEMM_LOCAL_H
#define MEMM_LOCAL_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define MEMM_GRNT_MODE_NUM                  (5UL)

#define MEMM_GRNT_AREA_NUM                  (2UL)
#define MEMM_GRNT_AREA_NONE                 (0xFFU)
#define MEMM_GRNT_AREA_1ST                  (0x00U)
#define MEMM_GRNT_AREA_2ND                  (0x01U)

#define MEMM_ERASE_GRNTACT_NONE             ((uint8)0xFFU)
#define MEMM_ERASE_GRNTACT_ERASE            ((uint8)0x00U)
#define MEMM_ERASE_GRNTACT_WRITE            ((uint8)0x01U)

#define MEMM_WRITE_GRNT_AREA_NOT_SKIP       (0x00U)
#define MEMM_WRITE_GRNT_AREA_SKIP           ((uint8)0x01U)

#define MEMM_INVALID_GRNT_VALUE             (0x00000000UL)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef struct {
    uint32 MemoryId;
    uint32 VirtualAddr;
    uint32 PhysicalAddr;
    uint32 Size;
    uint32 GrntAddr[MEMM_GRNT_AREA_NUM];
    uint8 TargetDevice;
} MemM_MemoryAreaConfigType;

typedef struct {
    uint32 TimeOutValueCodeFls;
    uint32 TimeOutValueExtCodeFls;
} MemM_EraseTimerConfigType;

typedef struct {
    uint32 TimeOutValueCodeFls;
    uint32 TimeOutValueExtCodeFls;
    uint32 TimeOutValueCodeRam;
} MemM_WriteTimerConfigType;

typedef struct {
    uint32 TimeOutValueCodeFls;
    uint32 TimeOutValueExtCodeFls;
    uint32 TimeOutValueCodeRam;
} MemM_ReadTimerConfigType;

typedef struct {
    uint32 TimeOutValue;
} MemM_RpgCmpltTimerConfigType;

typedef struct {
    MemM_EraseTimerConfigType EraseTimerData;
    MemM_WriteTimerConfigType WriteTimerData;
    MemM_ReadTimerConfigType ReadTimerData;
    MemM_RpgCmpltTimerConfigType RpgCmpltTimerData;
} MemM_TimerConfigType;

typedef struct {
    uint32 WriteValue;
    uint8 Action;
    uint8 TargetArea;
} MemM_GrntEraseConfigType;

typedef struct {
    uint32 ExpectedValue;
    uint8 SkipReq;
} MemM_GrntWriteSkipConfigType;

typedef struct {
    MemM_GrntWriteSkipConfigType SkipData[MEMM_GRNT_AREA_NUM];
} MemM_GrntWriteConfigType;

typedef struct {
    uint32 WriteValue;
} MemM_GrntRpgCompleteConfigType;

typedef struct {
    MemM_GrntEraseConfigType ReqEraseData;
    MemM_GrntWriteConfigType ReqWriteData;
    MemM_GrntRpgCompleteConfigType ReqRpgCompleteData;
} MemM_GrntConfigType;

typedef struct {
    P2CONST(MemM_MemoryAreaConfigType, TYPEDEF, MEMM_APPL_CONST) MemoryAreaData;
    P2CONST(MemM_TimerConfigType, TYPEDEF, MEMM_APPL_CONST) TimerData;
    P2CONST(MemM_GrntConfigType, TYPEDEF, MEMM_APPL_CONST) GrntData;
    uint32 GrntAreaSize;
    uint32 GrntBlockSize;
    uint8 GrntMode;
    uint8 MemoryAreaNum;
} MemM_ConfigType;


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/


#endif /* MEMM_LOCAL_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2018/10/23 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

