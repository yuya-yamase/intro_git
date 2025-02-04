/* MemM_h_Revision(v3.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | MemM/HEADER                                                 */
/******************************************************************************/
#ifndef MEMM_H
#define MEMM_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define MEMM_UNINIT                         ((MemM_StatusType)0x00U)
#define MEMM_IDLE                           ((MemM_StatusType)0x01U)
#define MEMM_BUSY                           ((MemM_StatusType)0x02U)
#define MEMM_UPDATEIDLE                     ((MemM_StatusType)0x03U)
#define MEMM_UPDATEBUSY                     ((MemM_StatusType)0x04U)
#define MEMM_UPDATECOMPLETE                 ((MemM_StatusType)0x05U)

#define MEMM_JOB_OK                         ((MemM_JobResultType)0x00U)
#define MEMM_JOB_FAILED                     ((MemM_JobResultType)0x01U)
#define MEMM_JOB_PENDING                    ((MemM_JobResultType)0x02U)

#define MEMM_DEVICE_TYPE_CODEFLS            ((uint8)0x00U)
#define MEMM_DEVICE_TYPE_EXTCODEFLS         ((uint8)0x01U)
#define MEMM_DEVICE_TYPE_CODERAM            ((uint8)0x02U)

#define MEMM_GRNT_MODE_KEYWORDSTAMP         ((uint8)0x00U)
#define MEMM_GRNT_MODE_FLASHSTATUS1         ((uint8)0x01U)
#define MEMM_GRNT_MODE_FLASHSTATUS2         ((uint8)0x02U)
#define MEMM_GRNT_MODE_FLASHSTATUS3         ((uint8)0x03U)
#define MEMM_GRNT_MODE_FLASHSTATUS4         ((uint8)0x04U)

#define MEMM_INVALID_ADDR                   ((uint32)0xFFFFFFFFUL)
#define MEMM_INVALID_SIZE                   ((uint32)0UL)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef uint8 MemM_StatusType;
typedef uint8 MemM_JobResultType;

#if ( REPROG_CFG_GETBLOCKINFO_USE == STD_ON )
typedef struct {
    uint32 Addr;
    uint32 Size;
} MemM_BlockInfoType;
#endif


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
FUNC(Std_ReturnType, MEMM_CODE_SLOW) MemM_Erase
(
    VAR(uint32, AUTOMATIC) MemoryId,
    VAR(uint32, AUTOMATIC) TargetAddr,
    VAR(uint32, AUTOMATIC) TargetSize
);
FUNC(Std_ReturnType, MEMM_CODE_SLOW) MemM_WriteStart
(
    VAR(uint32, AUTOMATIC) MemoryId,
    VAR(uint32, AUTOMATIC) DestAddr,
    VAR(uint32, AUTOMATIC) TotalSize
);
FUNC(Std_ReturnType, MEMM_CODE_SLOW) MemM_WriteUpdate
(
    P2CONST(uint8, AUTOMATIC, MEMM_APPL_CONST) SrcAddr,
    VAR(uint32, AUTOMATIC) Size
);
FUNC(Std_ReturnType, MEMM_CODE_SLOW) MemM_WriteFinish (void);
FUNC(Std_ReturnType, MEMM_CODE_SLOW) MemM_Read
(
    VAR(uint32, AUTOMATIC) MemoryId,
    VAR(uint32, AUTOMATIC) SrcAddr,
    P2VAR(uint8, AUTOMATIC, MEMM_APPL_DATA) DestAddr,
    VAR(uint32, AUTOMATIC) Size
);
FUNC(MemM_StatusType, MEMM_CODE_SLOW) MemM_GetStatus (void);
FUNC(MemM_JobResultType, MEMM_CODE_SLOW) MemM_GetJobResult (void);
FUNC(void, MEMM_CODE_SLOW) MemM_Init (void);
FUNC(void, MEMM_CODE_SLOW) MemM_MainFunction (void);
FUNC(void, MEMM_CODE_SLOW) MemM_DeInit (void);
FUNC(Std_ReturnType, MEMM_CODE_SLOW) MemM_ReprogComplete (void);
FUNC(Std_ReturnType, MEMM_CODE_SLOW) MemM_CnvPhysicalAddr
(
    VAR(uint32, AUTOMATIC) MemoryId,
    VAR(uint32, AUTOMATIC) VirtualAddr,
    P2VAR(uint32, AUTOMATIC, MEMM_APPL_DATA) PhysicalAddr,
    P2VAR(uint8, AUTOMATIC, MEMM_APPL_DATA) DeviceType
);
#if ( REPROG_CFG_GETBLOCKINFO_USE == STD_ON )
FUNC(Std_ReturnType, MEMM_CODE_SLOW) MemM_GetBlockInfo
(
    VAR(uint32, AUTOMATIC) MemoryId,
    VAR(uint32, AUTOMATIC) Addr,
    P2VAR(MemM_BlockInfoType, AUTOMATIC, MEMM_APPL_DATA) BlockInfo
);
#endif


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/


#endif /* MEMM_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2018/10/23 :Update                                rel.AUBASS */
/*  v3.00       :2021/09/14 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

