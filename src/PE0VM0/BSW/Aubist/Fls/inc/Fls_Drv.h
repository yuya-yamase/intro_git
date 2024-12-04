/* Fls_Drv_h_Revision(v1_0_0)                                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Fls/Drv/HEADER                                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef FLS_DRV_H
#define FLS_DRV_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Fls.h>
#include "../usr/Fls_Cdd_Callout.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define FLS_DRV_U1_REGBIT_FASTAT_CMDLK      ((uint8)0x10u)              /* the bit of Command Lock */
#define FLS_DRV_U1_REGBIT_FAEINT_RESET      ((uint8)0x00u)              /* The value for initialization of Flash Access Error Interrupt Enable Register(Hard defaults:0x99u) */

#define FLS_DRV_U4_REGBIT_FSTATR_TBLDTCT    (0x00000008uL)              /* the bit which is an error detection 2 bits (rewriting parameter table) */
#define FLS_DRV_U4_REGBIT_FSTATR_CFGDTCT    (0x00000020uL)              /* the bit which is an error detection 2 bits (Configuration setting) */
#define FLS_DRV_U4_REGBIT_FSTATR_FHVEERR    (0x00000040uL)              /* Flash Write/Erase Protect Error */

#define FLS_DRV_U4_REGBIT_FSTATR_PRGERR     (0x00001000uL)              /* the bit of Programming Error */
#define FLS_DRV_U4_REGBIT_FSTATR_ERSERR     (0x00002000uL)              /* the bit of Erasure Error */
#define FLS_DRV_U4_REGBIT_FSTATR_ILGERR     (0x00004000uL)              /* the bit of Illegal Command Error */
#define FLS_DRV_U4_REGBIT_FSTATR_FRDY       (0x00008000uL)              /* the bit of Flash Ready */
#define FLS_DRV_U4_REGBIT_FSTATR_BPLDTCT    (0x00020000uL)              /* the bit of Block Protection Area ECC 2-Bit Error Detection Monitoring Bit */
#define FLS_DRV_U4_REGBIT_FSTATR_SECDTCT    (0x02000000uL)              /* the bit which is an error detection 2 bits (Security setting area)*/

#define FLS_DRV_U4_REGBIT_FSTATR_ERCDTCT    (0x20000000uL)              /* the bit of Erase counter ECC 2-Bit Error Detection Monitoring Bit */
#define FLS_DRV_U4_REGBIT_FSTATR_SWTDTCT    (0x08000000uL)              /* the bit of Switch Area and TAG Area ECC 2-Bit Error Detection Monitoring Bit*/

#define FLS_DRV_U4_REGBIT_FSTATR_RESET      (0x00000000uL)              /* FSTATR register defaults */

#define FLS_DRV_U2_REGBIT_FENTRYD           ((uint16)0x0080u)           /* the bit of Data Flash Programming/Erasure Mode Entry */
#define FLS_DRV_U2_REGBIT_FENTRYC           ((uint16)0x0001u)           /* the bit of Code Flash Programming/Erasure Mode Entry */
#define FLS_DRV_U2_REGBIT_FENTRY_KEY        ((uint16)0xAA00u)           /* Key Code(Control of the rewriting propriety of the bit) setting value */
#define FLS_DRV_U2_REGBIT_FENTRY_OFF        ((uint16)0x0000u)           /* Read Mode Entry */
#define FLS_DRV_U2_MODE_PE                  (FLS_DRV_U2_REGBIT_FENTRYD) /* Data Flash Programming/Erasure Mode Entry */
#define FLS_DRV_U2_MODE_CPE                 (FLS_DRV_U2_REGBIT_FENTRYC) /* Code Flash Programming/Erasure Mode Entry */
#define FLS_DRV_U2_MODE_USER                (FLS_DRV_U2_REGBIT_FENTRY_OFF)  /* Read Mode Entry */

#define FLS_DRV_U2_REGBIT_FSUINITR_OFF      ((uint16)0x0000u)           /* Flash sequencer setting off            */
#define FLS_DRV_U2_REGBIT_FSUINITR_KEY      ((uint16)0x2D00u)           /* Key Code(Control of the rewriting propriety of the bit) setting value */

#if ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A8 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A16 )
#define FLS_DRV_U2_REGBIT_FCPSR_SUSPMD      ((uint16)0x00u)             /* Suspension-priority mode */
#endif

#define FLS_DRV_U2_REGBIT_FECCTMD_KEY       ((uint16)0xA600u)           /* Key Code(Control of the rewriting propriety of the bit) setting value */
#define FLS_DRV_U2_REGBIT_FECCTMD_RESET     ((uint16)0x0030u)           /* The value for initialization of Flash ECC Test Mode Register */

#if ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A8 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A16 )
#define FLS_DRV_U4_REGBIT_DFERSTR_DEDF      (0x00000002uL)              /* ECC 2-Bit Error Monitor Flag */
#define FLS_DRV_U4_REGVAL_DFERSTR_NOERR     (0x00000000uL)              /* An ECC error is not generated. */
#define FLS_DRV_U4_REGBIT_DFERSTC_ERRCLR    (0x01uL)                    /* SEDF/DEDF Flag Clear (SEDF/DEDF is in DFERSTR register) */
#elif ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2B6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2B10 )
#define FLS_DRV_U4_REGVAL_DFSERSTR_NOERR    (0x00000000uL)              /* An ECC 1-Bit error is not generated. */
#define FLS_DRV_U4_REGBIT_DFSERSTC_SSTCLR   (0x0FuL)                    /* SEDF Flag Clear (SEDF is in DFSERSTR register) */
#define FLS_DRV_U4_REGVAL_DFDERSTR_NOERR    (0x00000000uL)              /* An ECC 2-Bit error is not generated. */
#define FLS_DRV_U4_REGBIT_DFDERSTC_DSTCLR   (0x01uL)                    /* DEDF Flag Clear (DEDF is in DFDERSTR register) */
#endif

#if ( FLS_CDD_AUTH_DFID_API == STD_ON )
#define FLS_DRV_U4_REGBIT_DFIDR             (0x00000002uL)
#endif /* FLS_CDD_AUTH_DFID_API == STD_ON */

#define FLS_DRV_U4_REGBIT_FHVE_ON           (0x00000000uL)              /* It is impossible to write, erase and blank check. (Protection setting) */
#define FLS_DRV_U4_REGBIT_FHVE_OFF          (0x00000001uL)              /* It is possible to write, erase and blank check.(Protection release) */

#define FLS_DRV_U4_PROTECT_MODE_ON          (FLS_DRV_U4_REGBIT_FHVE_ON) /* Protection setting */
#define FLS_DRV_U4_PROTECT_MODE_OFF         (FLS_DRV_U4_REGBIT_FHVE_OFF) /* Protection release */

#define FLS_DRV_U4_DFLASH_CMD_ADD_0         (0xFFA20000uL)              /* FACI 0 command issue area */
#if ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A8 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A16 )
#define FLS_DRV_U4_DFLASH_CMD_ADD_1         (0xFFA20000uL + 0x10000uL)  /* FACI 1 command issue area */
#endif

#define FLS_DRV_U1_CMD_ERASE                ((uint8)0x20u)              /* Block Erase Command */
#define FLS_DRV_U1_CMD_CLEARSTAT            ((uint8)0x50u)              /* Status Clear Command */
#define FLS_DRV_U1_CMD_FORCED_STOP          ((uint8)0xB3u)              /* Forced Stop Command */
#define FLS_DRV_U1_CMD_WRITE                ((uint8)0xE8u)              /* Program Command */
#define FLS_DRV_U1_CMD_EXE                  ((uint8)0xD0u)              /* Command execution Command */

#define FLS_DRV_U4_DATA_TRANSFERSIZE_4BYTE  (0x04uL)                    /* Command execution Command */

#define FLS_DRV_U4_BLOCK_SIZE               (FLS_SECTOR_SIZE)           /* the block size */

#define FLS_DRV_U2_BLOCK_SIZE_2N            ((uint16)0x000Cu)           /* the block size(2^N Byte) for U2Ax */

#define FLS_DRV_U4_ACCESS_SIZE              (FLS_CFG_WRITE_UNIT_SIZE)   /* the access size */
#define FLS_DRV_U4_READ_SIZE                ((uint32)2u)                /* the read size */
#if ( FLS_CDD_COMPARE_API == STD_ON )
#define FLS_DRV_U4_COMP_SIZE                ((uint32)4u)                /* the compare size */
#endif /* FLS_CDD_COMPARE_API == STD_ON */

#if ( FLS_CDD_COMPARE_API == STD_ON )
#define FLS_DRV_U4_PROC_COMP_MAX_SIZE       (0x00000040uL)              /* the compare max processing size */
#endif /* FLS_CDD_COMPARE_API == STD_ON */

#define FLS_DRV_U4_TOTAL_SIZE               (FLS_SECTOR_SIZE * FLS_SECTOR_NUMBER)  /* The amount of data of data Flash (total size) */

#if ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A8 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A16 )
#define FLS_DRV_U1_FCU_MAX                  ((uint8)0x02u)              /* FCU Max */
#elif ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2B6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2B10 )
#define FLS_DRV_U1_FCU_MAX                  ((uint8)0x01u)              /* FCU Max */
#endif

#if ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A6 )
#define FLS_DRV_U4_BOUNDARY_ONE_BLOCK_SECTOR_NUM    ((uint32)32u)       /* number of sectors in FACI0 */
#elif ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A8 )
#define FLS_DRV_U4_BOUNDARY_ONE_BLOCK_SECTOR_NUM    ((uint32)32u)       /* number of sectors in FACI(each FACI0 and FACI1) */
#elif ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A16 )
#define FLS_DRV_U4_BOUNDARY_ONE_BLOCK_SECTOR_NUM    ((uint32)64u)       /* number of sectors in FACI(each FACI0 and FACI1) */
#elif ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2B6 )
#define FLS_DRV_U4_BOUNDARY_ONE_BLOCK_SECTOR_NUM    ((uint32)32u)       /* number of sectors in FACI(each FACI0 and FACI1) */
#elif ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2B10 )
#define FLS_DRV_U4_BOUNDARY_ONE_BLOCK_SECTOR_NUM    ((uint32)64u)       /* number of sectors in FACI(each FACI0 and FACI1) */
#endif

/* FACI size */
#define FLS_DRV_U4_BOUNDARY_ONE_BLOCK_SIZE  (FLS_SECTOR_SIZE * FLS_DRV_U4_BOUNDARY_ONE_BLOCK_SECTOR_NUM)

#define FLS_DRV_U4_REGBIT_BLANKCHECK_BLANK  (0x00008000uL)              /* Blank Flag */

/****************************************************************************/
/* 1 loop Clock:49Clock(U2Ax),44Clock(U2Bx)                                 */
/* Time-out interval:forced stop 40usec                                     */
/****************************************************************************/
/* (3Clock + read,access,wait,state count) */
#if ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A8 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A16 )
#define FLS_DRV_U4_FLASH_LDW_CLOCK_NUM      (39uL)                      /* ld.h  clock cycles per instruction */
#elif ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2B6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2B10 )
#define FLS_DRV_U4_FLASH_LDW_CLOCK_NUM      (34uL)                      /* ld.h  clock cycles per instruction */
#endif
#define FLS_DRV_U4_FLASH_MOV_CLOCK_NUM      (1uL)                       /* mov   clock cycles per instruction */
#define FLS_DRV_U4_FLASH_AND_CLOCK_NUM      (1uL)                       /* and   clock cycles per instruction */
#define FLS_DRV_U4_FLASH_BNZ_T_CLOCK_NUM    (2uL)                       /* bnz(agreement)     clock cycles per instruction */
#define FLS_DRV_U4_FLASH_BNZ_F_CLOCK_NUM    (2uL)                       /* bnz(disagreement)  clock cycles per instruction */
#define FLS_DRV_U4_FLASH_ADD_CLOCK_NUM      (1uL)                       /* and   clock cycles per instruction */

/* 1 loop total clock count:43 */
#define FLS_DRV_U4_REGREADY_CLKCNT          ( FLS_DRV_U4_FLASH_LDW_CLOCK_NUM   \
                                            + FLS_DRV_U4_FLASH_MOV_CLOCK_NUM   \
                                            + FLS_DRV_U4_FLASH_AND_CLOCK_NUM   \
                                            + FLS_DRV_U4_FLASH_BNZ_F_CLOCK_NUM \
                                            + FLS_DRV_U4_FLASH_AND_CLOCK_NUM   \
                                            + FLS_DRV_U4_FLASH_BNZ_F_CLOCK_NUM \
                                            + FLS_DRV_U4_FLASH_ADD_CLOCK_NUM   \
                                            + FLS_DRV_U4_FLASH_BNZ_T_CLOCK_NUM )

#define FLS_DRV_U4_FORCEDSTOP_TIME          (40uL)


/* the value of the bit shift */
#define FLS_DRV_U1_BITSHIFT_8               ((uint8)8u)
#define FLS_DRV_U1_BITSHIFT_16              ((uint8)16u)
#define FLS_DRV_U1_BITSHIFT_24              ((uint8)24u)

#define FLS_DRV_U4_BITMASK_0_TO_7BIT        (0x000000FFuL)
#define FLS_DRV_U4_BITMASK_8_TO_15BIT       (0x0000FF00uL)
#define FLS_DRV_U4_BITMASK_16_TO_23BIT      (0x00FF0000uL)

/* Array index */
#define FLS_DRV_U1_IDX_0                    ((uint8)0u)
#define FLS_DRV_U1_IDX_1                    ((uint8)1u)
#define FLS_DRV_U1_IDX_2                    ((uint8)2u)
#define FLS_DRV_U1_IDX_3                    ((uint8)3u)

#define FLS_DRV_U1_BIT1_TRUE                ((uint8)0x00u)              /* Data 1 is effective. */
#define FLS_DRV_U1_BIT2_TRUE                ((uint8)0x01u)              /* Data 2 is effective. */

#define FLS_DRV_U1_VAL_0                    ((uint8)0x00u)
#if ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A8 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A16 )
#define FLS_DRV_U1_VAL_1                    ((uint8)0x01u)
#endif
#define FLS_DRV_U4_VAL_0                    (0x00000000uL)
#define FLS_DRV_U4_VAL_1                    (0x00000001uL)

#define FLS_DRV_U4_MAX_NUM                  (0xFFFFFFFFuL)

#ifndef FLS_DRV_STATIC
    #define FLS_DRV_STATIC static
#endif /* FLS_DRV_STATIC */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

typedef uint8  Fls_StatusType;

#define FLS_DRV_U1_OK                       ((Fls_StatusType)0x00u)     /* Normal end */
#define FLS_DRV_U1_BUSY                     ((Fls_StatusType)0x01u)     /* During execution */

#define FLS_DRV_U1_ERR_WRITE                ((Fls_StatusType)0x03u)     /* Write error */
#define FLS_DRV_U1_ERR_ERASE                ((Fls_StatusType)0x04u)     /* Erasure error */
#define FLS_DRV_U1_ERR_BLANKCHECK           ((Fls_StatusType)0x05u)     /* Blank check error */
#define FLS_DRV_U1_ERR_ECC_DED              ((Fls_StatusType)0x06u)     /* ECC(2bit) error */
#define FLS_DRV_U1_ERR_INTERNAL             ((Fls_StatusType)0x07u)     /* Internal error */
#define FLS_DRV_U1_ERR_TIMEOUT              ((Fls_StatusType)0x08u)     /* Timeout error */

#if ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A8 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A16 )
typedef uint8  Fls_DataArea;

#define FLS_DRV_U1_AREA_FACI0               ((Fls_DataArea)0x01u)       /* Data area 0 */
#define FLS_DRV_U1_AREA_FACI1               ((Fls_DataArea)0x02u)       /* Data area 1 */
#define FLS_DRV_U1_AREA_FACIALL             ((Fls_DataArea)0x03u)       /* Data area 0 & 1 */
#endif

typedef uint8 Fls_CommandType;

#define FLS_DRV_U1_CMDTYPE_NONE             ((Fls_CommandType)0x00u)    /* FLS_DRV_CMDTYPE_NONE */
#define FLS_DRV_U1_CMDTYPE_ERASE            ((Fls_CommandType)0x01u)    /* Erasure processing */
#define FLS_DRV_U1_CMDTYPE_WRITE            ((Fls_CommandType)0x02u)    /* Write processing */

typedef uint8 Fls_FlagType;

#define FLS_DRV_U1_FALSE                    ((Fls_FlagType)0x00u)       /* False(Flag used within FLS_DRV) */
#define FLS_DRV_U1_TRUE                     ((Fls_FlagType)0x01u)       /* True (Flag used within FLS_DRV) */

/* Operation information */
typedef struct{
    uint32          u4FlashAdd;                                         /* Start address of Flash */
    P2CONST( uint8, AUTOMATIC, FLS_APPL_CONST ) ptBufAdd;               /* Address */
    uint32          u4FlashAddEnd;                                      /* End address of Flash */
    Fls_CommandType stCommand_enu;                                      /* Command */
    Fls_StatusType  stStatus;                                           /* Command Status */
} FLS_DRV_MULTIOP_T;

/* FLS Data */
typedef struct{
    FLS_DRV_MULTIOP_T   stMulOp_str[FLS_DRV_U1_FCU_MAX];                /* Operation information */
    MemIf_StatusType    stiStat_enu;                                    /* FLS internal state */
    MemIf_JobResultType stiJobResult_enu;                               /* FLS processing result */
} FLS_DRV_DATA_T;

/* Register Address by FCI */
typedef struct{
    uint32          u4RegAddFASTAT;
    uint32          u4RegAddFAEINT;
    uint32          u4RegAddFSADR;
    uint32          u4RegAddFEADR;
    uint32          u4RegAddFSTATR;
    uint32          u4RegAddFENTRYR;
    uint32          u4RegAddFSUINITR;
    uint32          u4RegAddFBCCNT;
#if ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A8 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A16 )
    uint32          u4RegAddFCPSR;
#endif
    uint32          u4RegAddFBCSTAT;
    uint32          u4RegAddFECCTMD;
    uint32          u4RegAddFHVE3;
    uint32          u4RegAddFHVE15;
    uint32          u4RegAddFACICMD;
} FLS_DRV_REGADDFCI_T;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define FLS_START_SEC_CODE
#include <Fls_MemMap.h>

FUNC( void, FLS_CODE ) Fls_Drv_InitVariables(void);
FUNC( void, FLS_CODE ) Fls_Drv_ClearOperationInfo(void);
FUNC( void, FLS_CODE ) Fls_Drv_InitRegister(uint8 u1_area);
FUNC( void, FLS_CODE ) Fls_Drv_ResetRegister(uint8 u1_area);
FUNC( void, FLS_CODE ) Fls_Drv_ResetInitr(uint8 u1_area);
FUNC( void, FLS_CODE ) Fls_Drv_ErrRefresh(uint8 u1_area);
FUNC( void, FLS_CODE ) Fls_Drv_EndCurrentOperation(Fls_StatusType st_stat, uint8 u1_area);

FUNC( void, FLS_CODE ) Fls_Drv_SetProtect(uint32 u4_mode,uint8 u1_area);

FUNC( Fls_StatusType, FLS_CODE ) Fls_Drv_Reset(uint8 u1_area);
FUNC( Fls_StatusType, FLS_CODE ) Fls_Drv_SwitchMode(uint16 u2_mode,uint8 u1_area);

#if ( FLS_DEV_ERROR_DETECT == STD_ON )
FUNC( Std_ReturnType, FLS_CODE ) Fls_Drv_ChkBuffer_u1( 
    P2CONST( uint8, AUTOMATIC, TYPEDEF ) pt_addBuf 
);
FUNC( Std_ReturnType, FLS_CODE ) Fls_Drv_ChkBuffer_u4(
    P2CONST( uint32, AUTOMATIC, TYPEDEF ) pt_addBuf 
);
FUNC( Std_ReturnType, FLS_CODE ) Fls_Drv_ChkAddress( uint32 u4_addStart, uint32 u4_align );
FUNC( Std_ReturnType, FLS_CODE ) Fls_Drv_ChkLength( uint32 u4_addStart, uint32 u4_bCnt, uint32 u4_align );
FUNC( Std_ReturnType, FLS_CODE ) Fls_Drv_ChkEraseLength( uint32 u4_addStart, uint32 u4_bCnt );
#endif /* FLS_DEV_ERROR_DETECT == STD_ON */
FUNC( Fls_StatusType, FLS_CODE ) Fls_Drv_StartWriteOperation( P2CONST( uint8, AUTOMATIC, FLS_APPL_CONST ) pt_AddSrc, uint32 u4_addDest, uint32 u4_cnt, uint8 u1_area );
FUNC( Fls_StatusType, FLS_CODE ) Fls_Drv_StartBCEraseOperation( uint32 u4_addStart, uint32 u4_addEnd, uint8 u1_fcuCmd, uint8 u1_area );
FUNC( Fls_StatusType, FLS_CODE ) Fls_Drv_ReadOperation (uint32 u4_addSrc, P2VAR( uint8, AUTOMATIC, TYPEDEF ) pt_AddDest, uint32 u4_cnt);
FUNC( Fls_FlagType, FLS_CODE ) Fls_Drv_MultiOperation (P2VAR( Fls_StatusType, AUTOMATIC, TYPEDEF ) pt_stat, uint8 u1_area);
FUNC( Fls_FlagType, FLS_CODE ) Fls_Drv_CheckStatus (P2VAR( Fls_StatusType, AUTOMATIC, TYPEDEF ) pt_stat, uint8 u1_area);

#if ( FLS_CDD_COMPARE_API == STD_ON )
FUNC( Fls_Cdd_JobResultType, FLS_CODE ) Fls_Drv_CheckCompare(P2CONST( uint8, AUTOMATIC, FLS_APPL_CONST ) pt_AddBuf, P2CONST( uint8, AUTOMATIC, FLS_APPL_CONST )  pt_CompareBuf, uint32 u4_cntTotal);
#endif /* FLS_CDD_COMPARE_API == STD_ON */

FUNC( uint8, FLS_CODE ) Fls_Drv_GetRegReady_Asm( uint32 u4_addr, uint32 u4_bit1, uint32 u4_bit2, uint32 u4_cnt); /* MISRA DEVIATION : This is a function defined in assembler. */

FUNC( void, FLS_CODE ) Fls_Drv_Syncp_Asm(void); /* MISRA DEVIATION : This is a function defined in assembler. */


#if ( FLS_CDD_AUTH_DFID_API == STD_ON )
FUNC( Fls_FlagType, FLS_CODE ) Fls_Drv_VerifyID(P2CONST( Fls_Cdd_DataFlashIDType, AUTOMATIC, FLS_APPL_CONST ) pt_IDValue);
#endif /* FLS_CDD_AUTH_DFID_API == STD_ON */

#if ( FLS_CDD_BLANK_CHECK_API == STD_ON ) || ( FLS_CDD_NOT_BLANK_ADDRESS_API == STD_ON )
FUNC( Fls_StatusType, FLS_CODE ) Fls_Drv_StartBCOperation( uint32 u4_addStart, uint32 u4_addEnd, Fls_AddressType* pt_AddDest);
#endif /* ( FLS_CDD_BLANK_CHECK_API == STD_ON ) || ( FLS_CDD_NOT_BLANK_ADDRESS_API == STD_ON ) */

#if ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A8 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A16 )
FUNC( Fls_DataArea, FLS_CODE ) Fls_Drv_CalculateTargetArea( uint32 u4_addStart, uint32 u4_bCnt );
#endif

#define FLS_STOP_SEC_CODE
#include <Fls_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define FLS_START_SEC_VAR_NO_INIT_32
#include <Fls_MemMap.h>

extern VAR( FLS_DRV_DATA_T, FLS_VAR_NO_INIT ) Fls_Str;

#define FLS_STOP_SEC_VAR_NO_INIT_32
#include <Fls_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Global macros                                                            */
/*--------------------------------------------------------------------------*/

#endif       /* FLS_DRV_H */


/****************************************************************************/
/* History                                                                  */
/* Version :Date                                                            */
/* [Number] :[Date]                                                         */
/****************************************************************************/

/**** End of File ***********************************************************/
