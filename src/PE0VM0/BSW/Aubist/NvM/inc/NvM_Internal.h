/* NvM_Internal.h v2-0-0                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | NVM/INTERNAL/HEADER                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     NVM_INTERNAL_H
#define     NVM_INTERNAL_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

#define NVM_BLOCKID_MIN                       (0U)
#define NVM_RESERVED_BLOCKID_MULTIJOB         (0U)
#define NVM_RESERVED_BLOCKID_CONFID           (1U)

#define NVM_USER_BLOCKID_MIN                  (2U)
#define NVM_USER_BLOCKID_MAX                  ((NvM_BlockIdType)NvMBlockDescriptorsSize - (NvM_BlockIdType)1U)

#define NVM_BLOCKID_INVALID                   (0xFFFFU)

#define NVM_PRIORITY_IMMEDIATE                (0U)

#define NVM_INSTANCE_ID                       (0U)

#define NVM_RND_NUM_UINT32_00                 (0x9DA70AE7U)
#define NVM_RND_NUM_UINT32_01                 (0x3F721401U)
#define NVM_RND_NUM_UINT32_02                 (0xA1A62093U)
#define NVM_RND_NUM_UINT32_03                 (0x22AA8A36U)
#define NVM_RND_NUM_UINT32_04                 (0xB9145954U)
#define NVM_RND_NUM_UINT32_05                 (0x71AAD7E6U)
#define NVM_RND_NUM_UINT32_06                 (0xB6E96AF1U)
#define NVM_RND_NUM_UINT32_07                 (0x1C646989U)
#define NVM_RND_NUM_UINT32_08                 (0x9C1F8709U)
#define NVM_RND_NUM_UINT32_09                 (0x2ECE2284U)
#define NVM_RND_NUM_UINT32_10                 (0xEA907101U)

#define NVM_RND_NUM_UINT32_20                 (0x5AF50761U)
#define NVM_RND_NUM_UINT32_21                 (0x1EC4B267U)
#define NVM_RND_NUM_UINT32_22                 (0x10162F75U)
#define NVM_RND_NUM_UINT32_23                 (0xD66F5F19U)

#define NVM_RND_NUM_UINT32_30                 (0x2C620EB7U)
#define NVM_RND_NUM_UINT32_31                 (0x6B40B5E6U)
#define NVM_RND_NUM_UINT32_32                 (0x5786A145U)

#define NVM_RND_NUM_UINT32_40                 (0x352C7072U)
#define NVM_RND_NUM_UINT32_41                 (0xA740AA7AU)

#define NVM_SERVICE_ID_INIT                   (0x00U)
#define NVM_SERVICE_ID_SETDATAIDX             (0x01U)
#define NVM_SERVICE_ID_GETDATAIDX             (0x02U)
#define NVM_SERVICE_ID_SETBLKPROTECT          (0x03U)
#define NVM_SERVICE_ID_GETERRORSTS            (0x04U)
#define NVM_SERVICE_ID_SETRAMBLKSTS           (0x05U)
#define NVM_SERVICE_ID_READBLK                (0x06U)
#define NVM_SERVICE_ID_WRITEBLK               (0x07U)
#define NVM_SERVICE_ID_RESTOREBLKDEF          (0x08U)
#define NVM_SERVICE_ID_ERASENVBLK             (0x09U)
#define NVM_SERVICE_ID_CANCELWRITEALL         (0x0AU)
#define NVM_SERVICE_ID_INVALIDATENVBLK        (0x0BU)
#define NVM_SERVICE_ID_READALL                (0x0CU)
#define NVM_SERVICE_ID_WRITEALL               (0x0DU)
#define NVM_SERVICE_ID_MAINFUNCTION           (0x0EU)
#define NVM_SERVICE_ID_GETVERSIONINF          (0x0FU)
#define NVM_SERVICE_ID_CACNCELJOBS            (0x10U)
#define NVM_SERVICE_ID_JOBENDNOTIFICATION     (0x11U)
#define NVM_SERVICE_ID_JOBERRNOTIFICATION     (0x12U)
#define NVM_SERVICE_ID_SETBLKLOCKSTS          (0x13U)
#define NVM_SERVICE_ID_READPRAMBLK            (0x16U)
#define NVM_SERVICE_ID_WRITEPRAMBLK           (0x17U)
#define NVM_SERVICE_ID_RESTOREPRAMBLKDEF      (0x18U)
#define NVM_SERVICE_ID_VALIDATEALL            (0x19U)
#define NVM_SERVICE_ID_INVALID                (0xFFU)

#define NVM_JOB_NON                           (NVM_RND_NUM_UINT32_00)
#define NVM_JOB_ID_INVALID                    (NVM_RND_NUM_UINT32_01)

#define NVM_JOB_READ_BLOCK                    (NVM_RND_NUM_UINT32_02)
#define NVM_JOB_WRITE_BLOCK                   (NVM_RND_NUM_UINT32_03)
#define NVM_JOB_RESTORE_BLOCK_DEFAULTS        (NVM_RND_NUM_UINT32_04)
#define NVM_JOB_CANCEL_WRITE_ALL              (NVM_RND_NUM_UINT32_05)
#define NVM_JOB_READ_PRAM_BLOCK               (NVM_RND_NUM_UINT32_06)
#define NVM_JOB_WRITE_PRAM_BLOCK              (NVM_RND_NUM_UINT32_07)
#define NVM_JOB_RESTORE_PRAM_BLOCK_DEFAULTS   (NVM_RND_NUM_UINT32_08)
#define NVM_JOB_READ_ALL                      (NVM_RND_NUM_UINT32_09)
#define NVM_JOB_WRITE_ALL                     (NVM_RND_NUM_UINT32_10)

#define NVM_SINGLE_JOBID_NUM                         (8U)
#define NVM_MULTI_JOBID_NUM                          (3U)

#endif  /* NVM_INTERNAL_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/*  1-1-0          :2018/11/14                                              */
/*  2-0-0          :2021/07/27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
