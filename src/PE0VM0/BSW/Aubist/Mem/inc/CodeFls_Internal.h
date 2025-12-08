/* CodeFls_Internal_h                                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | RH850/U2Ax/CodeFls/HEADER                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef CODEFLS_INTERNAL_H
#define CODEFLS_INTERNAL_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Internal Flags */
#define CODEFLS_U1_FALSE                    ((uint8)0x00U)              /* False                                    */
#define CODEFLS_U1_TRUE                     ((uint8)0x01U)              /* True                                     */

/* Operation Information Settings */
#define CODEFLS_U1_OPINFO_CMD_NONE          ((uint8)0xFFU)              /* No command                               */
#define CODEFLS_U4_OPINFO_ADDR_NONE         ((uint32)0x00000000UL)      /* No address                               */
#define CODEFLS_U4_OPINFO_SIZE_NONE         ((uint32)0x00000000UL)      /* No size                                  */
#define CODEFLS_PU1_OPINFO_BUFFER_NULL      ((uint8 *)0)                /* No buffer                                */

/* Block information initial value */
#define CODEFLS_U4_BLKINFO_ADDR_NONE        ((uint32)0x00000000UL)      /* Address initial value                    */
#define CODEFLS_U4_BLKINFO_SIZE_NONE        ((uint32)0x00000000UL)      /* Size Initial Value                       */

/* Block size */
#define CODEFLS_U4_BLOCK_SIZE               ((uint32)0x00010000UL)      /* for 64KB                                 */
#define CODEFLS_U4_SMALL_BLOCK_SIZE         ((uint32)0x00004000UL)      /* for 16KB                                 */

/* Mask value for block alignment check */
#define CODEFLS_U4_BLOCK_MASK               ((uint32)0x0000FFFFUL)      /* for 64KB Align Mask                      */
#define CODEFLS_U4_SMALL_BLOCK_MASK         ((uint32)0x00003FFFUL)      /* for 16KB Align Mask                      */

/* Mask value for write data alignment check */
#define CODEFLS_WRITEDATA_MASK              ((uint32)0x000001FFUL)      /* Write data alignment mask                */

/* Mask value for obtaining the block start address */
#define CODEFLS_U4_BLOCK_ADDR_MASK          ((uint32)0xFFFF0000UL)      /* for 64KB Mask                            */
#define CODEFLS_U4_SMALL_BLOCK_ADDR_MASK    ((uint32)0xFFFFC000UL)      /* for 16KB Mask                            */

#define CODEFLS_U4_CF1_ADDR_64K_START       ((uint32)0x00020000UL)      /* Start address of the user area (64KB)    */

/* Job Management Timer */
#define CODEFLS_U4_JOBTIMER_RESET           ((uint32)0x00000000UL)      /* Job Management Timer Reset Value         */

#define CODEFLS_U1_TRANSFERSIZE             ((uint8)0x80U)              /* FLI Block Transfer Size                  */
#define CODEFLS_U1_TRANSFERSIZE_HWAREA      ((uint8)0x08U)              /* FLI Block Transfer Size(Hardware Property area) */

/* Bit Shift Value */
#define CODEFLS_BITSHIFT_24                 (24U)
#define CODEFLS_BITSHIFT_16                 (16U)
#define CODEFLS_BITSHIFT_8                  (8U)
#define CODEFLS_BITSHIFT_2                  (2U)

/* Code Flash Area Information Setting Table Number */
#define CODEFLS_U1_INFONUM_0                ((uint8)0x00U)              /* Initial Value                            */
#define CODEFLS_U1_INFONUM_NONE             ((uint8)0xFFU)              /* Out of Code Flash Area Range             */

/* FACI Number */
#define CODEFLS_U1_FACI_0                   ((uint8)0x00U)
#define CODEFLS_U1_FACI_1                   ((uint8)0x01U)

/* Map Mode */
#define CODEFLS_U1_MAPMODE_DOUBLE           ((uint8)0x00U)
#define CODEFLS_U1_MAPMODE_SINGLE           ((uint8)0x01U)

/* Flash Memory valid area switching state */
#define CODEFLS_U1_SVA_NONE                 ((uint8)0x00U)              /* No status                                */
#define CODEFLS_U1_SVA_PROPERTY_ERASE       ((uint8)0x01U)              /* Property Erasure running                 */
#define CODEFLS_U1_SVA_PROPERTY_WRITE1      ((uint8)0x02U)              /* Property Programming running1            */
#define CODEFLS_U1_SVA_PROPERTY_WRITE2      ((uint8)0x03U)              /* Property Programming running2            */
#define CODEFLS_U1_SVA_TAG_ERASE_PRE1       ((uint8)0x04U)              /* TAG Erasure running - pre1               */
#define CODEFLS_U1_SVA_TAG_UPDATE_PRE1      ((uint8)0x05U)              /* TAG Update running - pre1                */
#define CODEFLS_U1_SVA_TAG_ERASE_PRE2       ((uint8)0x06U)              /* TAG Erasure running - pre2               */
#define CODEFLS_U1_SVA_TAG_UPDATE_PRE2      ((uint8)0x07U)              /* TAG Update running - pre2                */
#define CODEFLS_U1_SVA_SWITCH_ERASE         ((uint8)0x08U)              /* Switch Erasure running                   */
#define CODEFLS_U1_SVA_SWITCH_WRITE         ((uint8)0x09U)              /* Switch Programming running               */
#define CODEFLS_U1_SVA_TAG_ERASE            ((uint8)0x0AU)              /* TAG Erasure running                      */
#define CODEFLS_U1_SVA_TAG_UPDATE           ((uint8)0x0BU)              /* TAG Update running                       */

/* Initialization request type */
#define CODEFLS_U1_REQ_INIT                 ((uint8)0x00U)
#define CODEFLS_U1_REQ_DEINIT               ((uint8)0x01U)

/* Array Index */
#define CODEFLS_IDX_0                       (0U)
#define CODEFLS_IDX_1                       (1U)
#define CODEFLS_IDX_2                       (2U)
#define CODEFLS_IDX_3                       (3U)
#define CODEFLS_IDX_4                       (4U)
#define CODEFLS_IDX_5                       (5U)
#define CODEFLS_IDX_6                       (6U)
#define CODEFLS_IDX_7                       (7U)
#define CODEFLS_IDX_8                       (8U)
#define CODEFLS_IDX_9                       (9U)
#define CODEFLS_IDX_10                      (10U)
#define CODEFLS_IDX_11                      (11U)
#define CODEFLS_IDX_12                      (12U)
#define CODEFLS_IDX_13                      (13U)
#define CODEFLS_IDX_14                      (14U)
#define CODEFLS_IDX_15                      (15U)
#define CODEFLS_IDX_16                      (16U)
#define CODEFLS_IDX_17                      (17U)
#define CODEFLS_IDX_18                      (18U)
#define CODEFLS_IDX_19                      (19U)
#define CODEFLS_IDX_20                      (20U)
#define CODEFLS_IDX_21                      (21U)
#define CODEFLS_IDX_22                      (22U)
#define CODEFLS_IDX_23                      (23U)
#define CODEFLS_IDX_24                      (24U)
#define CODEFLS_IDX_25                      (25U)
#define CODEFLS_IDX_26                      (26U)
#define CODEFLS_IDX_27                      (27U)
#define CODEFLS_IDX_28                      (28U)
#define CODEFLS_IDX_29                      (29U)
#define CODEFLS_IDX_30                      (30U)
#define CODEFLS_IDX_31                      (31U)

#define CODEFLS_U1_VAL_0                    ((uint8)0U)
#define CODEFLS_U1_VAL_1                    ((uint8)1U)
#define CODEFLS_U1_VAL_2                    ((uint8)2U)
#define CODEFLS_U1_VAL_3                    ((uint8)3U)
#define CODEFLS_U2_VAL_1                    ((uint16)1U)
#define CODEFLS_U2_VAL_2                    ((uint16)2U)
#define CODEFLS_U2_VAL_3                    ((uint16)3U)
#define CODEFLS_U1_VAL_4                    ((uint8)4U)
#define CODEFLS_U4_VAL_0                    ((uint32)0x00000000UL)
#define CODEFLS_U4_VAL_1                    ((uint32)0x00000001UL)
#define CODEFLS_U4_VAL_2                    ((uint32)0x00000002UL)
#define CODEFLS_U4_VAL_MAX                  ((uint32)0xFFFFFFFFUL)

/* Mask value for blank check data alignment check */
#define CODEFLS_BLANK_CHECK_DATA_MASK       ((uint32)0x000001FFUL)      /* Blank check data alignment mask              */
/* For blank check result (Maximum value allowed for user-specific errors in Std_ReturnType) */
#define CODEFLS_U1_BLANKCHECK_NOT_BLANK     ((uint8)0x3FU)

/* Processor Element Identifier Value */
#define CODEFLS_U4_PEID_PE0                 ((uint32)0x00000000UL)
#define CODEFLS_U4_PEID_PE1                 ((uint32)0x00000001UL)
#define CODEFLS_U4_PEID_PE2                 ((uint32)0x00000002UL)
#define CODEFLS_U4_PEID_PE3                 ((uint32)0x00000003UL)

/* LTSC Timer Maximum Value - microsecond */
#define CODEFLS_U4_TIMER_MAX                ((uint32)0x03333333UL)      /* Result of 0xFFFFFFFF devided by CODEFLS_U4_CLK_HSB */


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* Operational Information */
typedef struct
{
    uint8 u1Cmd;                                                        /* command                                     */
    uint32 u4OpAddr;                                                    /* Current flash control start address         */
    P2CONST(uint8, TYPEDEF, MEM_APPL_DATA) pu1BufAddr;                /* Write data storage address                  */
    uint32 u4OpSize;                                                    /* Remaining Size                              */
    uint32 u4BankAddr;                                                  /* Bank First Address                          */
    uint8 u1FaciNum;                                                    /* FACI number to be processed                 */
    uint8 u1SVAStatus;                                                  /* Flash Memory valid area switching state     */
} CodeFls_MultiOpType;

/* Operation Information Mirror Area */
typedef struct
{
    uint8 u1CheckCmd;                                                   /* command                                     */
    uint32 u4CheckAddr;                                                 /* Current flash control start address         */
    P2CONST(uint8, TYPEDEF, MEM_APPL_DATA) pu1CheckBuf;               /* Write data storage address                  */
    uint32 u4CheckSize;                                                 /* Remaining Size                              */
    uint32 u4CheckBank;                                                 /* Bank First Address                          */
    uint8 u1CheckFaci;                                                  /* FACI number to be processed                 */
    uint8 u1CheckSVA;                                                   /* Flash Memory valid area switching state     */
} CodeFls_OpMirrorType;


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define MEM_START_SEC_VAR_NO_INIT_32
#include <Mem_MemMap.h>

extern VAR(uint8, MEM_VAR_NO_INIT) CodeFls_u1gJobStatus;                                        /* Job Status                               */
extern VAR(uint8, MEM_VAR_NO_INIT) CodeFls_u1gMirrorJobStatus;                                  /* Job Status Mirror Area                   */
extern VAR(uint8, MEM_VAR_NO_INIT) CodeFls_u1gJobResult;                                        /* Job Processing Results                   */
extern VAR(uint8, MEM_VAR_NO_INIT) CodeFls_u1gMirrorJobResult;                                  /* Job Processing Results Mirror Area       */
extern VAR(uint32, MEM_VAR_NO_INIT) CodeFls_u4gJobTimer;                                        /* Job Management Timer                     */
extern VAR(CodeFls_MultiOpType, MEM_VAR_NO_INIT) CodeFls_stgMultiOpInfo;                        /* Operational Information                  */
extern VAR(CodeFls_OpMirrorType, MEM_VAR_NO_INIT) CodeFls_stgMirrorArea;                        /* Operation Information Mirror Area        */
extern VAR(uint16, MEM_VAR_NO_INIT) CodeFls_u2gCpuFreq;                                         /* CPU operating frequency                  */
extern VAR(uint32, MEM_VAR_NO_INIT) CodeFls_u4gWriteBuffer[CODEFLS_U1_TRANSFERSIZE_HWAREA];     /* Write Buffer                             */

#define MEM_STOP_SEC_VAR_NO_INIT_32
#include <Mem_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define MEM_START_SEC_CONST_32
#include <Mem_MemMap.h>

#define MEM_STOP_SEC_CONST_32
#include <Mem_MemMap.h>


#endif  /* CODEFLS_INTERNAL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1.00          :2025/03/24                                              */
/*  v1.01          :2025/04/14                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
