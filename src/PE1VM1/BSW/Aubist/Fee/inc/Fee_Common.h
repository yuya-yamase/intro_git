/* Fee_Common.h v2-1-0                                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/COMMON/HEADER                                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef FEE_COMMON_H
#define FEE_COMMON_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
/* DTFEE type definition header file */
#include <Mscd_Common.h>
#include "Fee_Mpu_Const.h"
#include "Fee_Mpu_Dev_Const.h"
#include "../cfg/Fee_Cfg_Internal_Ext.h"
#include "Fee_Mpu_Const_Ext.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define FEE_NUM_OF_BITS_IN_1BYTE    (8U)
#define FEE_NUM_OF_BITS_IN_2BYTE    (16U)
#define FEE_NUM_OF_BITS_IN_3BYTE    (24U)

#define FEE_NUM_OF_BYTE_IN_UINT16   (2U)
#define FEE_NUM_OF_BYTE_IN_UINT32   (4U)

/* Data length */
#define FEE_LENGTH_00           (0U)
#define FEE_LENGTH_02           (2U)
#define FEE_LENGTH_04           (4U)
#define FEE_LENGTH_06           (6U)
#define FEE_LENGTH_08           (8U)
#define FEE_LENGTH_16           (16U)
#define FEE_LENGTH_32           (32U)
#define FEE_LENGTH_64           (64U)

#define FEE_LENGTH_UNDEF        (0U)
#define FEE_LENGTH_INVALID      (0U)

/* For checking redundancy data */
#define FEE_MIRROR_CHECK_UINT8  (0xFFU)
#define FEE_MIRROR_CHECK_UINT16 (0xFFFFU)
#define FEE_MIRROR_CHECK_UINT32 (0xFFFFFFFFU)


#define FEE_ASBSDATASETNUM     (2U)
#define FEE_ASBSDATAKINDNUM    (4U)

#define FEE_CWRITE_MAX         (6U) /* The max number of acceptable write requests at MNGDFC.                              */
                                    /* The max case is to fix all block status of one sector.                              */
                                    /* Block status which need to fix are 3 status, "used", "transferring", and "using".   */
                                    /* And each status is redundancy data using 2 words.                                   */

#define FEE_DATA_LENGTH_MAX    (32768U)     /* The maximum length in writing data.                                                      */
                                            /* Essentially, FEE is able to accept range of uint16 in AUTOSAR.                           */
                                            /* However, FEE limit the valid range for the following reasons.                            */
                                            /*     1. It may overflow because FEE adds some value to the data length.                   */
                                            /*     2. The developer guarantees only a smaller range than the max of uint16.             */

#if (FEE_DATA_FLASH_ECC_FIX_SIZE == FEE_BYTE_NUM_04)

#define FEE_AREASTATUSLEN       ((uint8)8U)     /* (4 * 2)[byte] */
#define FEE_BLOCKSTATUSLEN      ((uint8)24U)        /* (4 * 6)[byte] */
#define FEE_STARTRECORDPOS      ((uint8)32U)        /* FEE_AREASTATUSLEN + FEE_BLOCKSTATUSLEN */

#define FEE_RECORDMNGINFOLEN    (12U)                   /* The length of one record management information area. */
#define FEE_WRITECHECKPOS       (4U)                    /* The write check position in a record. */
#define FEE_DATASTATUSPOS       (8U)                    /* The data status position in a record. */

#elif (FEE_DATA_FLASH_ECC_FIX_SIZE == FEE_BYTE_NUM_08)

#if (FEE_DATA_FLASH_READ_SIZE == FEE_BYTE_NUM_08)

#define FEE_AREASTATUSLEN       ((uint8)16U)        /* Write Unit (Duplex) (8 * 2) [byte] */
#define FEE_BLOCKSTATUSLEN      ((uint8)48U)        /* (write unit * block status size) (duplex) ((8 * 3) * 2) [byte] */

#define FEE_RECORDMNGINFOLEN    (24U)                   /* The length of one record management information area. */
#define FEE_WRITECHECKPOS       (8U)                    /* The write check position in a record. */
#define FEE_DATASTATUSPOS       (16U)                   /* The data status position in a record. */

#elif (FEE_DATA_FLASH_READ_SIZE == FEE_BYTE_NUM_16)

#define FEE_AREASTATUSLEN       ((uint8)32U)        /* Read buffer unit (duplex) (16 * 2) [byte] */
#define FEE_BLOCKSTATUSLEN      ((uint8)96U)        /* (read buffer unit * block status size) (duplex) ((16 * 3) * 2) [byte] */

#else
#error "This read unit size isn't supported"
#endif /*FEE_READ_UNIT_SIZE*/

#define FEE_STARTRECORDPOS      ((uint8)(FEE_AREASTATUSLEN + FEE_BLOCKSTATUSLEN))   /* FEE_AREASTATUSLEN + FEE_BLOCKSTATUSLEN */

#else
#error "This unit size isn't supported"
#endif

#if (FEE_WC_DIVIDE_WRITE==STD_ON)
#define FEE_HALFWORD_WRITE_USE  (STD_ON)

#else
#define FEE_HALFWORD_WRITE_USE  (STD_OFF)
#endif

#if ( FEE_DATA_FLASH_BLANK_VAL_TYPE == FEE_DATA_FLASH_BLANK_VAL_TYPE_FF )
#define FEE_DATA_FLASH_BLANK_VAL_UINT1      (0xFFU)
#define FEE_DATA_FLASH_BLANK_VAL_UINT2      (0xFFFFU)
#define FEE_DATA_FLASH_BLANK_VAL_UINT4      (0xFFFFFFFFUL)
#define FEE_DATA_FLASH_IVTBLA_VAL_UINT1     (0x00U)
#define FEE_DATA_FLASH_IVTBLA_VAL_UINT2     (0x0000U)
#define FEE_DATA_FLASH_IVTBLA_VAL_UINT4     (0x00000000UL)

#define FEE_DATA_FLASH_DS_VAL_UINT1_UPPER   (0x11U)
#define FEE_DATA_FLASH_DS_VAL_UINT1_LOWER   (0x00U)

#elif ( FEE_DATA_FLASH_BLANK_VAL_TYPE == FEE_DATA_FLASH_BLANK_VAL_TYPE_00 )
#define FEE_DATA_FLASH_BLANK_VAL_UINT1      (0x00U)
#define FEE_DATA_FLASH_BLANK_VAL_UINT2      (0x0000U)
#define FEE_DATA_FLASH_BLANK_VAL_UINT4      (0x00000000UL)
#define FEE_DATA_FLASH_IVTBLA_VAL_UINT1     (0xFFU)
#define FEE_DATA_FLASH_IVTBLA_VAL_UINT2     (0xFFFFU)
#define FEE_DATA_FLASH_IVTBLA_VAL_UINT4     (0xFFFFFFFFUL)

#define FEE_DATA_FLASH_DS_VAL_UINT1_UPPER   (0xEEU)
#define FEE_DATA_FLASH_DS_VAL_UINT1_LOWER   (0xFFU)

#else /* FEE_DATA_FLASH_BLANK_VAL_TYPE */
#error "The type that the value of data flash in a state of erase is not supported."
#endif /* FEE_DATA_FLASH_BLANK_VAL_TYPE */

/* Block number invalid value */
#define FEE_BLOCKNUM_INVALID        ((uint8)0xFFU)


/* Return Common Definition */
#define FEE_STATUS_OK           ((uint32)0x00000000UL)      /* normal */
#define FEE_STATUS_NG           ((uint32)0x00000001UL)      /* Abnormal */
#define FEE_STATUS_EXIT         ((uint32)0x00000002UL)      /* Uncontinuable */
#define FEE_STATUS_DONE         ((uint32)0x00000003UL)      /* Done */
#define FEE_STATUS_CONT         ((uint32)0x00000004UL)      /* Continuable */
#define FEE_STATUS_BUSY         ((uint32)0x00000005UL)      /* Processing */
#define FEE_STATUS_INVALID      ((uint32)0x00000006UL)      /* Invalid data present */
#define FEE_STATUS_NODATA       ((uint32)0x00000007UL)      /* Block unused/no data */

/* Block status type */
/* Order is meaningful, so be careful when changing definition values! */
/* Affects block status data fixed transition destination decision table (Fee _ FixBSJudgeTBL)! */
/* Affects the block status judgment function (FEE _ JudgeBlockStatus) */
#define FEE_BS_AREA         ((uint8)0x00U)      /* Area Status */
#define FEE_BS_USING        ((uint8)0x01U)      /* In use */
#define FEE_BS_MOVE         ((uint8)0x02U)      /* Transferring */
#define FEE_BS_USED         ((uint8)0x03U)      /* Used */
#define FEE_BS_UNUSED       ((uint8)0x04U)      /* Not used */
#define FEE_BS_ILLEGAL      ((uint8)0x05U)      /* Incorrect */
#define FEE_BS_MAX          ((uint8)0x06U)      /* Block status type guard */
#define FEE_BS_INVALID      ((uint8)0xFFU)      /* Invalid value */

/* Block status determination processing type */
#define FEE_BSFIXKIND_NONFIX        (0x00U)     /* No firm requirement */
#define FEE_BSFIXKIND_FIX1ST        (0x10U)     /* 1 must be confirmed */
#define FEE_BSFIXKIND_FIX2ND        (0x20U)     /* 2nd confirmed needed */
#define FEE_BSFIXKIND_FIXALL        (0x30U)     /* Both must be confirmed */

/* write BlockStatus place */
#define FEE_BSWRITE_NOTWRITE        (0x00U)     /* do not need to write */
#define FEE_BSWRITE_MAIN            (0x01U)     /* write main */
#define FEE_BSWRITE_SUB             (0x02U)     /* write sub */
#define FEE_BSWRITE_ALL             (0x03U)     /* write both main and sub */

/* Duplex data type */
#define FEE_DUPLIDATA_1ST       ((uint32)0x00000000UL)      /* 1st data */
#define FEE_DUPLIDATA_2ND       ((uint32)0x00000001UL)      /* 2nd data */

/* Block status data judgment result */
/* Order is meaningful, so be careful when changing definition values! */
/* Affects block status judgment table (Fee _ JudgeBSTBL)! */
#define FEE_BSDATA_ERASE            (0x00U)     /* erasure */
#define FEE_BSDATA_VALID            (0x01U)     /* 0x55AA55AA */
#define FEE_BSDATA_OTHER            (0x02U)     /* NOT ABOVE */

/* Initialization mode */
#define FEE_INIT_ALL            ((uint8)0x00U)      /* ALL AREA */
#define FEE_INIT_ONE            ((uint8)0x01U)      /* Designated Area */

/* Flag common definition */
#define FEE_FLAG_OFF        ((uint8)0x00U)      /* Flag OFF */
#define FEE_FLAG_ON         ((uint8)0x01U)      /* Flag ON */

/* Flag value for continuity writing */
#define FEE_CWFLG_NONE          (0x0000U)           /* Initialize value */
#define FEE_CWFLG_VOLMINCHK     ((uint16)0x0008U)   /* Check voltage */
#define FEE_CWFLG_ERRSTOP       ((uint16)0x0004U)   /* Stop DFC error occured*/
#define FEE_CWFLG_DFCERRCHK     ((uint16)0x0002U)   /* Check DFC error */
#define FEE_CWFLG_VRFYERRCHK    ((uint16)0x0001U)   /* Check verify error */

#if ( FEE_HALFWORD_WRITE_USE == STD_ON ) 
#define FEE_DATA_FLASH_HALF_WRITE_SIZE  (FEE_DATA_FLASH_ECC_FIX_SIZE/2U)
#define FEE_CWOFFSET_HALFWORD           (FEE_DATA_FLASH_HALF_WRITE_SIZE)           /* Write Address Offset Halfword */
#endif /* FEE_HALFWORD_WRITE_USE */ 
#define FEE_CWOFFSET_INVALID            (0xFFFFU)                                  /* Write Address Offset Invalid */
#define FEE_CWOFFSET_ZERO               (0U)                                       /* Write Address Offset Zero */


/* Timer common definition */
#define FEE_TM_INVALID  ((uint32)0xFFFFFFFFUL)      /* Timer disabled */

/* Record-related */
#define FEE_XFLAGDAT_PHYSICAL_IMAGE           (0x66U)

#define FEE_DATAAREA_REC_TAIL_OFFSET        ( FEE_DFLASH_FORMAT_XFLAG_SIZE ) /* The position of a data area record. */

#define FEE_RECORD_FORMAT_OFFSET_ID           (0U)                  /*  Offset from beginning of buffer record(number of bytes): ID */
#define FEE_RECORD_FORMAT_OFFSET_DATAADDR     (2U)                  /* Data address position */

#if (FEE_ENDIAN == FEE_ENDIAN_BIG)
#define FEE_RECORD_FORMAT_OFFSET_ID_MSBYTE          (0U)    /*  Offset from beginning of buffer record(number of bytes): ID most significant byte */
#define FEE_RECORD_FORMAT_OFFSET_ID_LSBYTE          (1U)    /*  Offset from beginning of buffer record(number of bytes): ID least significant byte */
#define FEE_RECORD_FORMAT_OFFSET_DATAADDR_MSBYTE    (2U)    /*  Offset from beginning of buffer record(number of bytes): DATA ADDR most significant byte */
#define FEE_RECORD_FORMAT_OFFSET_DATAADDR_LSBYTE    (3U)    /*  Offset from beginning of buffer record(number of bytes): DATA ADDR least significant byte */
#define FEE_RECORD_FORMAT_OFFSET_CS_MSBYTE_INDEX_0  (FEE_DFLASH_ONE_TIME_WRITE_SIZE - FEE_RECORD_SIZE_CHECKSUM)              /*  Offset from beginning of buffer record(number of bytes): CS 1st byte */
#define FEE_RECORD_FORMAT_OFFSET_CS_MSBYTE_INDEX_1  ( ( FEE_DFLASH_ONE_TIME_WRITE_SIZE - FEE_RECORD_SIZE_CHECKSUM ) + 1U)    /*  Offset from beginning of buffer record(number of bytes): CS 2nd byte */
#define FEE_RECORD_FORMAT_OFFSET_CS_MSBYTE_INDEX_2  ( ( FEE_DFLASH_ONE_TIME_WRITE_SIZE - FEE_RECORD_SIZE_CHECKSUM ) + 2U)    /*  Offset from beginning of buffer record(number of bytes): CS 3rd byte */
#define FEE_RECORD_FORMAT_OFFSET_CS_MSBYTE_INDEX_3  ( ( FEE_DFLASH_ONE_TIME_WRITE_SIZE - FEE_RECORD_SIZE_CHECKSUM ) + 3U)    /*  Offset from beginning of buffer record(number of bytes): CS 4th byte */

#elif (FEE_ENDIAN == FEE_ENDIAN_LITTLE)
#define FEE_RECORD_FORMAT_OFFSET_ID_MSBYTE          (1U)    /*  Offset from beginning of buffer record(number of bytes): ID most significant byte */
#define FEE_RECORD_FORMAT_OFFSET_ID_LSBYTE          (0U)    /*  Offset from beginning of buffer record(number of bytes): ID least significant byte */
#define FEE_RECORD_FORMAT_OFFSET_DATAADDR_MSBYTE    (3U)    /*  Offset from beginning of buffer record(number of bytes): DATA ADDR most significant byte */
#define FEE_RECORD_FORMAT_OFFSET_DATAADDR_LSBYTE    (2U)    /*  Offset from beginning of buffer record(number of bytes): DATA ADDR least significant byte */
#define FEE_RECORD_FORMAT_OFFSET_CS_MSBYTE_INDEX_0  ( ( FEE_DFLASH_ONE_TIME_WRITE_SIZE - FEE_RECORD_SIZE_CHECKSUM ) + 3U)    /*  Offset from beginning of buffer record(number of bytes): CS 1st byte */
#define FEE_RECORD_FORMAT_OFFSET_CS_MSBYTE_INDEX_1  ( ( FEE_DFLASH_ONE_TIME_WRITE_SIZE - FEE_RECORD_SIZE_CHECKSUM ) + 2U)    /*  Offset from beginning of buffer record(number of bytes): CS 2nd byte */
#define FEE_RECORD_FORMAT_OFFSET_CS_MSBYTE_INDEX_2  ( ( FEE_DFLASH_ONE_TIME_WRITE_SIZE - FEE_RECORD_SIZE_CHECKSUM ) + 1U)    /*  Offset from beginning of buffer record(number of bytes): CS 3rd byte */
#define FEE_RECORD_FORMAT_OFFSET_CS_MSBYTE_INDEX_3  (FEE_DFLASH_ONE_TIME_WRITE_SIZE - FEE_RECORD_SIZE_CHECKSUM)              /*  Offset from beginning of buffer record(number of bytes): CS 4th byte */

#else
/*"This endian isn't supported"*/
#endif

#define FEE_RECORD_SIZE_BLOCKNUM            (2U)    /* The size of block number. */
#define FEE_RECORD_SIZE_DATAADDR            (2U)    /* The size of data address. */
#define FEE_RECORD_SIZE_BLOCKNUM_DATAADDR   (FEE_RECORD_SIZE_BLOCKNUM + FEE_RECORD_SIZE_DATAADDR)
#define FEE_RECORD_SIZE_CHECKSUM            (4U)    /* The size of check sum. */

#define FEE_RECORD_PADDING_VAL              (0x00U)

#define FEE_CHECKSUM_UNLOCK_VAL             (0xC0000000U)

/* Common */
#define FEE_BIT0                    ((uint32)0x00000001U)           /* BIT0 */
#define FEE_UPPER4BIT               (0xF0U)                 /* Top 4 bit mask */
#define FEE_LOWER4BIT               (0x0FU)                 /* Lower 4-bit mask */

/* ADDRESS INVALID */
#define FEE_ADDRESS_INVALID     ((uint32)0xFFFFFFFFU)

/* Operational status */
#define FEE_STATUSIDLE                  ((uint8)0x00U)      /* Idle */
#define FEE_STATUSWRITE                 ((uint8)0x01U)      /* Writing */
#define FEE_STATUSMOVE                  ((uint8)0x02U)      /* Data Restructuring */
#define FEE_STATUSIDREAD                ((uint8)0x03U)      /* Reading by ID */
#define FEE_STATUSMAX                   ((uint8)0x04U)      /* State Guard */

/* MAIN STATE */
#define FEE_MSTATUSWBIDLE               ((uint8)0x10U)      /* Writing - Idle */
#define FEE_MSTATUSWBSEL                ((uint8)0x11U)      /* Writing - Block selected */
#define FEE_MSTATUSWBMOVE               ((uint8)0x12U)      /* Writing - Data transfer */
#define FEE_MSTATUSWBWRITE              ((uint8)0x13U)      /* WRITING - WRITING RECORD */
#define FEE_MSTATUSRIDLE                ((uint8)0x30U)      /* Reading by ID - Idle */
#define FEE_MSTATUSRBSRCH               ((uint8)0x31U)      /* Reading by ID - Searching for free space */
#define FEE_MSTATUSRPREPISRCH           ((uint8)0x32U)      /* Reading by ID - Preparing to read by ID */
#define FEE_MSTATUSRISRCH               ((uint8)0x33U)      /* Reading specified ID - Reading specified ID data */
#define FEE_MSTATUSINVALID              ((uint8)0xFFU)      /* Invalid value */

/* Substate */
#define FEE_SSTATUSWSIDLE               ((uint8)0x10U)      /* Block selected - idle (unused) */
#define FEE_SSTATUSWSFIX                ((uint8)0x11U)      /* Selecting block - finalizing block status data */
#define FEE_SSTATUSWSUSG                ((uint8)0x12U)      /* Blocks selected - Blocks in use are being created*/
#define FEE_SSTATUSWSMOV                ((uint8)0x13U)      /* BLOCK SELECTING - IN TRANSFER BLOCK CREATING */
#define FEE_SSTATUSWSWEMOV              ((uint8)0x14U)      /* BLOCK SELECTING - RESTRUCTION ENDING SETTING */
#define FEE_SSTATUSWSALLU               ((uint8)0x15U)      /* Block Selection - Area Disabled/Used Setting */
#define FEE_SSTATUSWSFAIL               ((uint8)0x16U)      /* BLOCK SELECTED - USED/FAILURE SETTING */
#define FEE_SSTATUSWMIDLE               ((uint8)0x20U)      /* Data transfer in progress - idle */
#define FEE_SSTATUSWMSRCHMPS            ((uint8)0x21U)      /* Data transfer in progress - Searching for last source data location */
#define FEE_SSTATUSWMPREPSRCHMDT        ((uint8)0x22U)      /* Data transfer in progress - preparing to retrieve source data */
#define FEE_SSTATUSWMSRCHMDT            ((uint8)0x23U)      /* Data transfer in progress - Retrieving source data */
#define FEE_SSTATUSWMPREPSRCHSDT        ((uint8)0x24U)      /* Data transfer in progress - Preparing to retrieve destination data */
#define FEE_SSTATUSWMSRCHSDT            ((uint8)0x25U)      /* Data transfer in progress - Retrieving destination data */
#define FEE_SSTATUSWMWRITE              ((uint8)0x26U)      /* Transferring data - Writing data */
#define FEE_SSTATUSWWIDLE               ((uint8)0x30U)      /* Writing record - Idle */
#define FEE_SSTATUSWWSRCHPOSMNG         ((uint8)0x31U)      /* WRITING RECORD - SEARCHING WRITING RECORD LOCATION (MANAGEMENT INFORMATION) */
#define FEE_SSTATUSWWSTARTSRCHPOSDAT    ((uint8)0x32U)      /* WRITING RECORD - START SEARCH FOR WRITING RECORD POSITION (DATA) */
#define FEE_SSTATUSWWSRCHPOSDAT         ((uint8)0x33U)      /* WRITING RECORD - SEARCHING WRITING RECORD LOCATION (DATA) */
#define FEE_SSTATUSWWPREPSRCHOLD        ((uint8)0x34U)      /* Writing record - preparing to retrieve old data */
#define FEE_SSTATUSWWSRCHOLD            ((uint8)0x35U)      /* WRITING RECORD - SEARCHING OLD DATA */
#define FEE_SSTATUSWWWRITE              ((uint8)0x36U)      /* WRITING RECORD - WRITING DATA */
#define FEE_SSTATUSINVALID              ((uint8)0xFFU)      /* Invalid value */

/* Subsubstate */
#define FEE_SSSTATUSWSUIDLE             ((uint8)0x20U)      /* Blocking in use - idle (unused) */
#define FEE_SSSTATUSWSUWERSG            ((uint8)0x21U)      /* Creating block in use - Waiting to be erased */
#define FEE_SSSTATUSWSUWUSG             ((uint8)0x22U)      /* Creating block in use - Waiting for setting in use */
#define FEE_SSSTATUSWSUERSG             ((uint8)0x23U)      /* Creating blocks in use - erasing */
#define FEE_SSSTATUSWSUUSG              ((uint8)0x24U)      /* In use block creation - In use setting */
#define FEE_SSSTATUSWSMIDLE             ((uint8)0x30U)      /* Blocking in transit - idle (unused) */
#define FEE_SSSTATUSWSMWMOVE            ((uint8)0x31U)      /* Creating transfer block - Waiting for transfer settings */
#define FEE_SSSTATUSWSMWUSD             ((uint8)0x32U)      /* Blocking in transit - Waiting for used settings */
#define FEE_SSSTATUSWSMWERSG            ((uint8)0x33U)      /* Creating block in transit - waiting for erase */
#define FEE_SSSTATUSWSMMOVE             ((uint8)0x34U)      /* Creating block in transit - Setting in transit */
#define FEE_SSSTATUSWSMUSD              ((uint8)0x35U)      /* Transferring block creating - used setting */
#define FEE_SSSTATUSWSMERSG             ((uint8)0x36U)      /* Blocking in transit - erasing */
#define FEE_SSSTATUSWSEIDLE             ((uint8)0x40U)      /* Reorg end setting - Idle */
#define FEE_SSSTATUSWSEUSG              ((uint8)0x41U)      /* Reorg end set - In use set */
#define FEE_SSSTATUSWSEUSD              ((uint8)0x42U)      /* Reorg end setting - Used setting */
#define FEE_SSSTATUSWSAIDLE             ((uint8)0x50U)      /* Area Disabled/Used Setting - Idle */
#define FEE_SSSTATUSWSASET              ((uint8)0x51U)      /* Area Disabled/Used Setting - Setting */
#define FEE_SSSTATUSWSFIDLE             ((uint8)0x60U)      /* Used/Fault Setting - Idle (unused) */
#define FEE_SSSTATUSWSFWMUSD            ((uint8)0x61U)      /* Used/Fault Setting - Main Block Waiting for Used Setting */
#define FEE_SSSTATUSWSFWSUSD            ((uint8)0x62U)      /* Used/Fault Setting - Subblock Waiting for Used Setting */
#define FEE_SSSTATUSWSFWMF              ((uint8)0x63U)      /* USED/FAILURE SETTING - MAIN BLOCK FAILURE SETTING WAITING */
#define FEE_SSSTATUSWSFWSF              ((uint8)0x64U)      /* Used/Fault Setting - Subblock Fault Setting Waiting */
#define FEE_SSSTATUSWSFSET              ((uint8)0x65U)      /* Used/Fault Setting - Setting */

#define FEE_SSSTATUSINVALID     ((uint8)0xFFU)      /* Invalid value */

/* Data for buffer initialization */
#define FEE_INIDAT_UINT8                ((uint8)FEE_DATA_FLASH_BLANK_VAL_UINT1)
#define FEE_INIDAT_UINT32               ((uint32)FEE_DATA_FLASH_BLANK_VAL_UINT4)
#define FEE_INIDAT_UINT16               ((uint16)FEE_DATA_FLASH_BLANK_VAL_UINT2)

/* WC write data */
#if (FEE_ENDIAN == FEE_ENDIAN_BIG)
#define FEE_WCDAT_PHYSICAL_IMAGE_UPPER  ((uint8)0xAAU)
#define FEE_WCDAT_PHYSICAL_IMAGE_LOWER  ((uint8)0xAAU)

#elif (FEE_ENDIAN == FEE_ENDIAN_LITTLE)
#define FEE_WCDAT_PHYSICAL_IMAGE_UPPER  ((uint8)0xAAU)
#define FEE_WCDAT_PHYSICAL_IMAGE_LOWER  ((uint8)0xAAU)

#else
/*"This endian isn't supported"*/
#endif

/* DATA-STATUS write data */
#if (FEE_ENDIAN == FEE_ENDIAN_BIG)
#define FEE_DSDAT_PHYSICAL_IMAGE_UPPER  ((uint8)FEE_DATA_FLASH_DS_VAL_UINT1_UPPER)
#define FEE_DSDAT_PHYSICAL_IMAGE_LOWER  ((uint8)FEE_DATA_FLASH_DS_VAL_UINT1_LOWER)

#elif (FEE_ENDIAN == FEE_ENDIAN_LITTLE)
#define FEE_DSDAT_PHYSICAL_IMAGE_UPPER ((uint8)FEE_DATA_FLASH_DS_VAL_UINT1_LOWER)
#define FEE_DSDAT_PHYSICAL_IMAGE_LOWER ((uint8)FEE_DATA_FLASH_DS_VAL_UINT1_UPPER)

#else
/*"This endian isn't supported"*/
#endif

/* BS initial status data */
#if (FEE_ENDIAN == FEE_ENDIAN_BIG)
#define FEE_BSDAT_PHYSICAL_IMAGE_UPPER  ((uint8)0x55U)
#define FEE_BSDAT_PHYSICAL_IMAGE_LOWER  ((uint8)0xAAU)

#elif (FEE_ENDIAN == FEE_ENDIAN_LITTLE)
#define FEE_BSDAT_PHYSICAL_IMAGE_UPPER  ((uint8)0xAAU)
#define FEE_BSDAT_PHYSICAL_IMAGE_LOWER  ((uint8)0x55U)

#else
/*"This endian isn't supported"*/
#endif

#define FEE_DFLASH_FORMAT_BS_MAX_SIZE          (8U)
#define FEE_DFLASH_FORMAT_WC_MAX_SIZE          (8U)
#define FEE_DFLASH_FORMAT_DS_MAX_SIZE          (8U)
#define FEE_DFLASH_FORMAT_XFLAG_MAX_SIZE       (8U)


#define FEE_AREANUM_INVALID (0xFFU)         /* Area number invalid value */

#define FEE_SRCH_REMAIN_COUNT_ZERO  (0)     /* 0 searchable */

/* array-index-number */
#define FEE_ARRAY_INDEX_00  (0U)
#define FEE_ARRAY_INDEX_01  (1U)

#if (FEE_ENDIAN == FEE_ENDIAN_BIG)
#define FEE_UINT16_MSBYTE_INDEX_0  (0U)
#define FEE_UINT16_MSBYTE_INDEX_1  (1U)

#define FEE_UINT32_MSBYTE_INDEX_0  (0U)
#define FEE_UINT32_MSBYTE_INDEX_1  (1U)
#define FEE_UINT32_MSBYTE_INDEX_2  (2U)
#define FEE_UINT32_MSBYTE_INDEX_3  (3U)

#elif (FEE_ENDIAN == FEE_ENDIAN_LITTLE)
#define FEE_UINT16_MSBYTE_INDEX_0  (1U)
#define FEE_UINT16_MSBYTE_INDEX_1  (0U)

#define FEE_UINT32_MSBYTE_INDEX_0  (3U)
#define FEE_UINT32_MSBYTE_INDEX_1  (2U)
#define FEE_UINT32_MSBYTE_INDEX_2  (1U)
#define FEE_UINT32_MSBYTE_INDEX_3  (0U)

#else
/*"This endian isn't supported"*/
#endif

#define FEE_BLKSTARTADDRTBL Fee_Mpu_Cau4SectorTopAddresse
#define FEE_READ_UNIT_SIZE      FEE_DATA_FLASH_READ_SIZE

#define FEE_DFAI_RW_SIZE_MAX      (64U)


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* Data Flash Control Management Data Structure */
typedef struct {
    uint8   u1MngDFCStatus;                     /* Data Flash Control State */
    uint8   u1CWriteIndex;                      /* Index of buffer for continuous write */
    uint8   u1CWriteNum;                        /* Number of consecutive write data */
    uint8   u1RetryFlag;                        /* Flag for retrying to write */
    uint16  u2CWriteDataLength[FEE_CWRITE_MAX]; /* WriteData Length */
    uint16  u2CWriteAddrOffset[FEE_CWRITE_MAX]; /* WriteAddr Offset */
    uint16  u2CWriteFlag[FEE_CWRITE_MAX];       /* Flags for continuous writing */
    uint32  u4CWriteAddrBuf[FEE_CWRITE_MAX];    /* ADDRESS BUFFER FOR CONTINUOUS WRITE */
    P2CONST( uint8, AUTOMATIC, TYPEDEF ) ptu1CWriteDataAddr[FEE_CWRITE_MAX];
} Fee_MngDfcInfType;


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define FEE_START_SEC_CODE
#include <Fee_MemMap.h>

/* RESPONSE HOOK CALL COMMON PROCESSING */
FUNC(void, FEE_CODE) Fee_RspHook( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo);

/* Data write status management with block management */
FUNC(uint32, FEE_CODE) Fee_BWriteMain( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );

/* ID-specified data read status management */
FUNC(uint32, FEE_CODE) Fee_ReadMain( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );

/* Data transfer state management */
FUNC(uint32, FEE_CODE) Fee_MoveData( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );

FUNC( void, FEE_CODE )
Fee_Driver_Init( void );

FUNC( Std_ReturnType, FEE_CODE )
Fee_Driver_Cancel( void );

FUNC( void, FEE_CODE )
Fee_Driver_AbortDfc( void );

FUNC( void, FEE_CODE )
Fee_Driver_AsyncCancel( void );

FUNC( void, FEE_CODE )
Fee_Driver_AsyncAbort( void );

FUNC( boolean, FEE_CODE )
Fee_Driver_IsWaitingForCancel( void );

/* Data Flash periodic processing execution instruction */
FUNC(void, FEE_CODE) Fee_ExecPeriodic( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo , uint8 u1_callmode );

/* Select area to use */
FUNC(void, FEE_CODE) Fee_SelectUseArea( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );

/* Write block selection state management */
FUNC(uint32, FEE_CODE) Fee_SelectWriteBlock( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );

FUNC(void, FEE_CODE) Fee_WriteBlockStatus(
    uint8 u1BlockNo,
    uint32 u4BSDataKind,
    uint8 u1WritePlace
);

/* Read block selection */
FUNC(uint32, FEE_CODE) Fee_SelectReadBlock( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );

/* Initializing block data in use */
FUNC(void, FEE_CODE) Fee_ClrUseBlockInfo( void );

FUNC( Std_ReturnType, FEE_CODE )
Fee_Block_CheckUseBlockInfo( void );

FUNC( void, FEE_CODE )
Fee_Block_SetUseBlockInfoSub( void );

#if ( MSCD_FREESPACE_USE == STD_ON )
FUNC( uint32, FEE_CODE )
Fee_Block_GetSectorInfo(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo,
    P2VAR( boolean,        AUTOMATIC, TYPEDEF         ) NeedsToFix
);
#endif /*( MSCD_FREESPACE_USE == STD_ON )*/

FUNC( void, FEE_CODE )
Fee_Record_Init( void );

FUNC( Std_ReturnType, FEE_CODE )
Fee_Record_CheckRAM( void );

FUNC( void, FEE_CODE )
Fee_Record_SetRAMSub( void );

/* Find Free Space */
FUNC(uint32, FEE_CODE) Fee_SrchFreeSpace( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );

/* Record write status management */
FUNC(uint32, FEE_CODE) Fee_WriteRecord( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );

FUNC( boolean, FEE_CODE )
Fee_Record_CheckWriteSpace(
    uint16 WriteDataLen,
    uint16 TargetSector,
    P2CONST( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo
);

FUNC( void, FEE_CODE )
Fee_Record_StateWtMvStart(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo
);

FUNC( uint32, FEE_CODE )
Fee_Record_StateWtMvExec(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo
);

FUNC( void, FEE_CODE )
Fee_Record_StateScRdStart( void );

FUNC( uint32, FEE_CODE )
Fee_Record_StateScRdExec(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo, 
    P2VAR( uint32,         AUTOMATIC, TYPEDEF )         DstSrchResult
);

FUNC( void, FEE_CODE )
Fee_Record_StateScMsStart( void );

FUNC( uint32, FEE_CODE )
Fee_Record_StateScMsExec(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo, 
    P2VAR( uint32,         AUTOMATIC, TYPEDEF )         DstSrchResult
);

FUNC( void, FEE_CODE )
Fee_Record_StateScMdStart( void );

FUNC( uint32, FEE_CODE )
Fee_Record_StateScMdExec(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo, 
    P2VAR( uint32,         AUTOMATIC, TYPEDEF )         DstSrchResult
);

FUNC( Std_ReturnType, FEE_CODE )
Fee_MngDfc_CheckRAM( void );

FUNC( void, FEE_CODE )
Fee_MngDfc_SetRAMSub( void );

/* Data Flash Control Management for Periodic Processing */
FUNC(uint32, FEE_CODE) Fee_MngDfcForPrd( uint8 u1_callmode );

/* ADD BUFFER FOR CONTINUOUS WRITE */
FUNC(void, FEE_CODE) Fee_AddCWriteBuf( uint32 u4Address, P2CONST(uint8, AUTOMATIC, TYPEDEF) ptu1Src, uint16 u2Length, uint16 u2OffSet, uint16 u2Flg );

/* Continuous write start processing */
FUNC(void, FEE_CODE) Fee_StartCWrite( void );


/* Initiate erase */
FUNC(void, FEE_CODE) Fee_StartErase( uint8 u1BlockNo );

/* Start blank check */
FUNC(void, FEE_CODE) Fee_StartBlankCheck( uint32 u4StartTailAddress, uint32 u4EndTopAddress );

/* Buffer Initialization for Continuous Writing */
FUNC(void, FEE_CODE) Fee_ClearCWriteBuf( void );

/* Data Flash control result acquisition processing */
FUNC(uint32, FEE_CODE) Fee_GetMngDfcResult( P2VAR(uint32, AUTOMATIC, TYPEDEF) ptu4Address );

/* Initialize MHA management data */
FUNC(void, FEE_CODE) Fee_InitCpuDtfData( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );

/* Dataset processing */
FUNC(void, FEE_CODE) Fee_Lib_SetMemory( P2VAR(uint8, AUTOMATIC, TYPEDEF) DstPtr, uint8 Constant, uint32 Length );

/* Final write record position read processing */
FUNC(uint32, FEE_CODE) Fee_RefLastWritePos( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );

/* Final write record position preservation */
FUNC(uint32, FEE_CODE) Fee_SetLastWritePos( P2CONST(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );

/* Initialize last write record position */
FUNC(void, FEE_CODE) Fee_InitLastWritePos( uint8 u1AreaNum, uint8 u1Mode );

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

#define FEE_START_SEC_CONST_32
#include <Fee_MemMap.h>

extern CONST(uint8, FEE_CONST) Fee_FixWCData[FEE_DFLASH_FORMAT_WC_MAX_SIZE];
extern CONST(uint8, FEE_CONST) Fee_FixDSData[FEE_DFLASH_FORMAT_DS_MAX_SIZE];
extern CONST(uint8, FEE_CONST) Fee_FixBSData[FEE_DFLASH_FORMAT_BS_MAX_SIZE];
extern CONST(uint8, FEE_CONST) Fee_FixXFlagData[FEE_DFLASH_FORMAT_XFLAG_MAX_SIZE];

#define FEE_STOP_SEC_CONST_32
#include <Fee_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* FEE_COMMON_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/*  1-1-0          :2019/10/09                                              */
/*  2-0-0          :2022/08/24                                              */
/*  2-1-0          :2024/07/19                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
