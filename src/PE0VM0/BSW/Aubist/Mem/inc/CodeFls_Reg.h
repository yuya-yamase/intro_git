/* CodeFls_Reg_h                                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | RH850/U2Ax/CodeFls/HEADER                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef CODEFLS_REG_H
#define CODEFLS_REG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include "./CodeFls_Device.h"


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Flash Pin Monitor Register */
#define CODEFLS_U4_REGADD_FPMON_0                   ((uint32)(CODEFLS_U4_REGADD_FACI0_BASE + 0x000UL))
#define CODEFLS_U4_REGADD_FPMON_1                   ((uint32)(CODEFLS_U4_REGADD_FACI1_BASE + 0x000UL))
#define CODEFLS_U1_REGBIT_FPMON_SFWE                ((uint8)0x80U)
#define CODEFLS_U1_REGBIT_FPMON_RESET               ((uint8)0x00U)

/* Flash Access Status Register */
#define CODEFLS_U4_REGADD_FASTAT_0                  ((uint32)(CODEFLS_U4_REGADD_FACI0_BASE + 0x010UL))
#define CODEFLS_U4_REGADD_FASTAT_1                  ((uint32)(CODEFLS_U4_REGADD_FACI1_BASE + 0x010UL))
#define CODEFLS_U1_REGBIT_FASTAT_CMDLK              ((uint8)0x10U)

/* Flash Access Error Interrupt Enable Register */
#define CODEFLS_U4_REGADD_FAEINT_0                  ((uint32)(CODEFLS_U4_REGADD_FACI0_BASE + 0x014UL))
#define CODEFLS_U4_REGADD_FAEINT_1                  ((uint32)(CODEFLS_U4_REGADD_FACI1_BASE + 0x014UL))
#define CODEFLS_U1_REGBIT_FAEINT_RESET              ((uint8)0x99U)

/* Flash Command Start Address Register */
#define CODEFLS_U4_REGADD_FSADDR_0                  ((uint32)(CODEFLS_U4_REGADD_FACI0_BASE + 0x030UL))
#define CODEFLS_U4_REGADD_FSADDR_1                  ((uint32)(CODEFLS_U4_REGADD_FACI1_BASE + 0x030UL))
#define CODEFLS_U4_REGBIT_FSADDR_RESET              ((uint32)0x00000000UL)

/* Flash Command End Address Register */
#define CODEFLS_U4_REGADD_FEADDR_0                  ((uint32)(CODEFLS_U4_REGADD_FACI0_BASE + 0x034UL))
#define CODEFLS_U4_REGADD_FEADDR_1                  ((uint32)(CODEFLS_U4_REGADD_FACI1_BASE + 0x034UL))
#define CODEFLS_U4_REGBIT_FEADDR_RESET              ((uint32)0x00000000UL)

/* Code Flash Valid Area Protection Register */
#define CODEFLS_U4_REGADD_FCVAPROT_0                ((uint32)(CODEFLS_U4_REGADD_FACI0_BASE + 0x040UL))
#define CODEFLS_U4_REGADD_FCVAPROT_1                ((uint32)(CODEFLS_U4_REGADD_FACI1_BASE + 0x040UL))
#define CODEFLS_U2_REGBIT_FCVAPROT_DIS              ((uint16)0xFE01U)
#define CODEFLS_U2_REGBIT_FCVAPROT_ENA              ((uint16)0xFE00U)

/* Flash Status Register */
#define CODEFLS_U4_REGADD_FSTATR_0                  ((uint32)(CODEFLS_U4_REGADD_FACI0_BASE + 0x080UL))
#define CODEFLS_U4_REGADD_FSTATR_1                  ((uint32)(CODEFLS_U4_REGADD_FACI1_BASE + 0x080UL))
#define CODEFLS_U4_REGBIT_FSTATR_NOERR              ((uint32)0x00000000UL)
#define CODEFLS_U4_REGBIT_FSTATR_ERCDTCT            ((uint32)0x20000000UL)      /* bit29: Erase counter ECC 2-Bit Error Detection Monitoring Bit */
#define CODEFLS_U4_REGBIT_FSTATR_SWTDTCT            ((uint32)0x08000000UL)      /* bit27: Switch Area and TAG Area ECC 2-Bit Error Detection Monitoring Bit */
#define CODEFLS_U4_REGBIT_FSTATR_SECDTCT            ((uint32)0x02000000UL)      /* bit25: Security Setting Area ECC 2-Bit Error Detection Monitoring Bit */
#define CODEFLS_U4_REGBIT_FSTATR_BPLDTCT            ((uint32)0x00020000UL)      /* bit17: Block Protection Area ECC 2-Bit Error Detection Monitoring Bit */
#define CODEFLS_U4_REGBIT_FSTATR_FRDY               ((uint32)0x00008000UL)      /* bit15: Flash Ready */
#define CODEFLS_U4_REGBIT_FSTATR_ILGLERR            ((uint32)0x00004000UL)      /* bit14: Illegal Command Error */
#define CODEFLS_U4_REGBIT_FSTATR_ERSERR             ((uint32)0x00002000UL)      /* bit13: Erasure Error */
#define CODEFLS_U4_REGBIT_FSTATR_PRGERR             ((uint32)0x00001000UL)      /* bit12: Programming Error */
#define CODEFLS_U4_REGBIT_FSTATR_SUSRDY             ((uint32)0x00000800UL)      /* bit11: Suspend Ready */
#define CODEFLS_U4_REGBIT_FSTATR_ERSSPD             ((uint32)0x00000200UL)      /* bit 9: Erasure-Suspended Status */
#define CODEFLS_U4_REGBIT_FSTATR_PRGSPD             ((uint32)0x00000100UL)      /* bit 8: Programming Suspension Status */
#define CODEFLS_U4_REGBIT_FSTATR_FHVEERR            ((uint32)0x00000040UL)      /* bit 6: FHVE Setting Error */
#define CODEFLS_U4_REGBIT_FSTATR_CFGDTCT            ((uint32)0x00000020UL)      /* bit 5: Configuration Setting Area ECC 2-Bit Error Detection Monitoring Bit */
#define CODEFLS_U4_REGBIT_FSTATR_TBLDTCT            ((uint32)0x00000008UL)      /* bit 3: 2-Bit Error Detection Monitor : P/E Parameter Table */

#define CODEFLS_U4_FSTATR_MASK_ERR                  (CODEFLS_U4_REGBIT_FSTATR_ERCDTCT | \
                                                        CODEFLS_U4_REGBIT_FSTATR_SWTDTCT | \
                                                        CODEFLS_U4_REGBIT_FSTATR_SECDTCT | \
                                                        CODEFLS_U4_REGBIT_FSTATR_BPLDTCT | \
                                                        CODEFLS_U4_REGBIT_FSTATR_ILGLERR | \
                                                        CODEFLS_U4_REGBIT_FSTATR_ERSERR  | \
                                                        CODEFLS_U4_REGBIT_FSTATR_PRGERR  | \
                                                        CODEFLS_U4_REGBIT_FSTATR_SUSRDY  | \
                                                        CODEFLS_U4_REGBIT_FSTATR_ERSSPD  | \
                                                        CODEFLS_U4_REGBIT_FSTATR_PRGSPD  | \
                                                        CODEFLS_U4_REGBIT_FSTATR_FHVEERR | \
                                                        CODEFLS_U4_REGBIT_FSTATR_CFGDTCT | \
                                                        CODEFLS_U4_REGBIT_FSTATR_TBLDTCT )

/* Flash Programming/Erasure Mode Entry Register */
#define CODEFLS_U4_REGADD_FENTRYR_0                 ((uint32)(CODEFLS_U4_REGADD_FACI0_BASE + 0x084UL))
#define CODEFLS_U4_REGADD_FENTRYR_1                 ((uint32)(CODEFLS_U4_REGADD_FACI1_BASE + 0x084UL))
#define CODEFLS_U2_REGBIT_FENTRY_FENTRYD            ((uint16)0x0080U)
#define CODEFLS_U2_REGBIT_FENTRY_FENTRYC            ((uint16)0x0001U)
#define CODEFLS_U2_REGBIT_FENTRY_KEY                ((uint16)0xAA00U)
#define CODEFLS_U2_REGBIT_FENTRY_OFF                ((uint16)0x0000U)
#define CODEFLS_U2_MODE_DPE                         (CODEFLS_U2_REGBIT_FENTRY_FENTRYD)
#define CODEFLS_U2_MODE_CPE                         (CODEFLS_U2_REGBIT_FENTRY_FENTRYC)
#define CODEFLS_U2_MODE_USER                        (CODEFLS_U2_REGBIT_FENTRY_OFF)

/* Flash Sequencer Set-up Initialize Register */
#define CODEFLS_U4_REGADD_FSUINITR_0                ((uint32)(CODEFLS_U4_REGADD_FACI0_BASE + 0x08CUL))
#define CODEFLS_U4_REGADD_FSUINITR_1                ((uint32)(CODEFLS_U4_REGADD_FACI1_BASE + 0x08CUL))
#define CODEFLS_U2_REGBIT_FSUINITR_KEY              ((uint16)0x2D00U)
#define CODEFLS_U2_REGBIT_FSUINITR_SUINIT           ((uint16)0x0001U)
#define CODEFLS_U2_REGBIT_FSUINITR_RESET            ((uint16)0x0000U)

/* FACI Reset Transfer Warning Interrupt Enable Register */
#define CODEFLS_U4_READDR_FRTEINT_0                 ((uint32)(CODEFLS_U4_REGADD_FACI0_BASE + 0x09CUL))
#define CODEFLS_U4_READDR_FRTEINT_1                 ((uint32)(CODEFLS_U4_REGADD_FACI1_BASE + 0x09CUL))
#define CODEFLS_U1_REGBIT_FRTEINT_DISABLE           ((uint8)0x00U)

/* Flash ECC Test Mode Register */
#define CODEFLS_U4_REGADD_FECCTMD_0                 ((uint32)(CODEFLS_U4_REGADD_FACI0_BASE + 0x104UL))
#define CODEFLS_U4_REGADD_FECCTMD_1                 ((uint32)(CODEFLS_U4_REGADD_FACI1_BASE + 0x104UL))
#define CODEFLS_U2_REGBIT_FECCTMD_KEY               ((uint16)0xA600U)
#define CODEFLS_U2_REGBIT_FECCTMD_RESET             ((uint16)0x0030U)

/* Switch Area Status Register */
#define CODEFLS_U4_REGADD_FSWASTAT_0                ((uint32)(CODEFLS_U4_REGADD_FACI0_BASE + 0x0A8UL))
#define CODEFLS_U1_REGBIT_FSWASTAT_SWAS             ((uint8)0x02U)
#define CODEFLS_U1_REGBIT_FSWASTAT_CFGVA            ((uint8)0x04U)
#define CODEFLS_U1_REGBIT_FSWASTAT_SECVA            ((uint8)0x08U)
#define CODEFLS_U1_REGBIT_FSWASTAT_BPVA0            ((uint8)0x10U)
#define CODEFLS_U1_REGBIT_FSWASTAT_BPVA1            ((uint8)0x20U)


/* Customer ID A Input Register 0-7 */
#define CODEFLS_U4_REGADD_CUSTIDAIN0                ((uint32)(CODEFLS_U4_REGADD_AUTH_BASE + 0x080UL))
#define CODEFLS_U4_REGADD_CUSTIDAIN1                ((uint32)(CODEFLS_U4_REGADD_AUTH_BASE + 0x084UL))
#define CODEFLS_U4_REGADD_CUSTIDAIN2                ((uint32)(CODEFLS_U4_REGADD_AUTH_BASE + 0x088UL))
#define CODEFLS_U4_REGADD_CUSTIDAIN3                ((uint32)(CODEFLS_U4_REGADD_AUTH_BASE + 0x08CUL))
#define CODEFLS_U4_REGADD_CUSTIDAIN4                ((uint32)(CODEFLS_U4_REGADD_AUTH_BASE + 0x090UL))
#define CODEFLS_U4_REGADD_CUSTIDAIN5                ((uint32)(CODEFLS_U4_REGADD_AUTH_BASE + 0x094UL))
#define CODEFLS_U4_REGADD_CUSTIDAIN6                ((uint32)(CODEFLS_U4_REGADD_AUTH_BASE + 0x098UL))
#define CODEFLS_U4_REGADD_CUSTIDAIN7                ((uint32)(CODEFLS_U4_REGADD_AUTH_BASE + 0x09CUL))

/* Customer ID B Input Register 0-7 */
#define CODEFLS_U4_REGADD_CUSTIDBIN0                ((uint32)(CODEFLS_U4_REGADD_AUTH_BASE + 0x0A0UL))
#define CODEFLS_U4_REGADD_CUSTIDBIN1                ((uint32)(CODEFLS_U4_REGADD_AUTH_BASE + 0x0A4UL))
#define CODEFLS_U4_REGADD_CUSTIDBIN2                ((uint32)(CODEFLS_U4_REGADD_AUTH_BASE + 0x0A8UL))
#define CODEFLS_U4_REGADD_CUSTIDBIN3                ((uint32)(CODEFLS_U4_REGADD_AUTH_BASE + 0x0ACUL))
#define CODEFLS_U4_REGADD_CUSTIDBIN4                ((uint32)(CODEFLS_U4_REGADD_AUTH_BASE + 0x0B0UL))
#define CODEFLS_U4_REGADD_CUSTIDBIN5                ((uint32)(CODEFLS_U4_REGADD_AUTH_BASE + 0x0B4UL))
#define CODEFLS_U4_REGADD_CUSTIDBIN6                ((uint32)(CODEFLS_U4_REGADD_AUTH_BASE + 0x0B8UL))
#define CODEFLS_U4_REGADD_CUSTIDBIN7                ((uint32)(CODEFLS_U4_REGADD_AUTH_BASE + 0x0BCUL))

/* Customer ID C Input Register 0-7 */
#define CODEFLS_U4_REGADD_CUSTIDCIN0                ((uint32)(CODEFLS_U4_REGADD_AUTH_BASE + 0x0C0UL))
#define CODEFLS_U4_REGADD_CUSTIDCIN1                ((uint32)(CODEFLS_U4_REGADD_AUTH_BASE + 0x0C4UL))
#define CODEFLS_U4_REGADD_CUSTIDCIN2                ((uint32)(CODEFLS_U4_REGADD_AUTH_BASE + 0x0C8UL))
#define CODEFLS_U4_REGADD_CUSTIDCIN3                ((uint32)(CODEFLS_U4_REGADD_AUTH_BASE + 0x0CCUL))
#define CODEFLS_U4_REGADD_CUSTIDCIN4                ((uint32)(CODEFLS_U4_REGADD_AUTH_BASE + 0x0D0UL))
#define CODEFLS_U4_REGADD_CUSTIDCIN5                ((uint32)(CODEFLS_U4_REGADD_AUTH_BASE + 0x0D4UL))
#define CODEFLS_U4_REGADD_CUSTIDCIN6                ((uint32)(CODEFLS_U4_REGADD_AUTH_BASE + 0x0D8UL))
#define CODEFLS_U4_REGADD_CUSTIDCIN7                ((uint32)(CODEFLS_U4_REGADD_AUTH_BASE + 0x0DCUL))

#define CODEFLS_U4_REGBIT_CUSTID_RESET              ((uint32)0x00000000UL)

/* ID Authentication Status Register */
#define CODEFLS_U4_REGADD_IDST                      ((uint32)(CODEFLS_U4_REGADD_AUTH_BASE + 0x1FCUL))
#define CODEFLS_U1_BITSHIFT_IDST_CUSTID             ((uint8)4U)

/* FLMD Control Register */
#define CODEFLS_U4_REGADD_FLMDCNT                   ((uint32)(CODEFLS_U4_REGADD_FLMD_BASE + 0x000UL))
#define CODEFLS_U4_REGBIT_FLMDCNT_SFWE              ((uint32)0x00000001UL)
#define CODEFLS_U4_REGBIT_FLMDCNT_RESET             ((uint32)0x00000000UL)

/* FHVE3/15 Control Register */
#define CODEFLS_U4_REGADD_FHVE3FP0                  ((uint32)(CODEFLS_U4_REGADD_FHVE_BASE + 0x000UL))
#define CODEFLS_U4_REGADD_FHVE15FP0                 ((uint32)(CODEFLS_U4_REGADD_FHVE_BASE + 0x004UL))
#define CODEFLS_U4_REGADD_FHVE3FP1                  ((uint32)(CODEFLS_U4_REGADD_FHVE_BASE + 0x010UL))
#define CODEFLS_U4_REGADD_FHVE15FP1                 ((uint32)(CODEFLS_U4_REGADD_FHVE_BASE + 0x014UL))
#define CODEFLS_U4_REGBIT_FHVE_CNT                  ((uint32)0x00000001UL)
#define CODEFLS_U4_REGBIT_FHVE_RESET                ((uint32)0x00000000UL)

/* Code Flash Memory Mapping Mode Status Register */
#define CODEFLS_U4_REGADD_CFMAPSTT                  ((uint32)(CODEFLS_U4_REGADD_SCDS_BASE + 0x450UL))
#define CODEFLS_U4_REGBIT_CFMAPSTT_DOUBLE           ((uint32)0x00000000UL)
#define CODEFLS_U4_MASK_CFMAPSTT                    ((uint32)0x00000001UL)

/* Blank Check Register */
#define CODEFLS_U4_REGADD_FCPSR_0                   ((uint32)(CODEFLS_U4_REGADD_FACI0_BASE + 0x0E0UL))
#define CODEFLS_U4_REGADD_FCPSR_1                   ((uint32)(CODEFLS_U4_REGADD_FACI1_BASE + 0x0E0UL))
#define CODEFLS_U4_FSADDR_UP_ADDR                   ((uint32)0x0C000000U)
#define CODEFLS_U1_BLCHK_OFFSET_ADDR                ((uint8)0x20U)
#define CODEFLS_U4_BLCHK_BF_MASK                    ((uint32)0x00008000UL)          /* Blank Flag  */

/* FACI command-issuing area */
#define CODEFLS_U4_FLASH_ACCESS_CMD_AREA0           ((uint32)0xFFA20000UL)
#define CODEFLS_U4_FLASH_ACCESS_CMD_AREA1           ((uint32)0xFFA30000UL)
#define CODEFLS_U1_FLASH_ACCESS_CMD_ERASE           ((uint8)0x20U)                         /* Block Erasure command                */
#define CODEFLS_U1_FLASH_ACCESS_CMD_CLEARSTAT       ((uint8)0x50U)                         /* Status Clearing command              */
#define CODEFLS_U1_FLASH_ACCESS_CMD_FORCED_STOP     ((uint8)0xB3U)                         /* Forced Stop command                  */
#define CODEFLS_U1_FLASH_ACCESS_CMD_WRITE           ((uint8)0xE8U)                         /* Programming command                  */
#define CODEFLS_U1_FLASH_ACCESS_CMD_PROPERTY_WRITE  ((uint8)0x45U)                         /* Property Programming command         */
#define CODEFLS_U1_FLASH_ACCESS_CMD_PROPERTY_ERASE  ((uint8)0x47U)                         /* Property Erasure command             */
#define CODEFLS_U1_FLASH_ACCESS_CMD_SWITCH_WRITE    ((uint8)0x85U)                         /* Switch Programming command           */
#define CODEFLS_U1_FLASH_ACCESS_CMD_SWITCH_ERASE    ((uint8)0x87U)                         /* Switch Erasure command               */
#define CODEFLS_U1_FLASH_ACCESS_CMD_TAG_UPDATE      ((uint8)0x83U)                         /* TAG Update command                   */
#define CODEFLS_U1_FLASH_ACCESS_CMD_TAG_ERASE       ((uint8)0x89U)                         /* TAG Erasure command                  */

#define CODEFLS_U1_FLASH_ACCESS_CMD_EXE             ((uint8)0xD0U)                         /* Command Execute Command              */

/* Configration Setting Area */
/* VOF Program completion flag n for Configuration Setting Area : back side */
#define CODEFLS_U4_REGADD_CSAB_CSAVOFC00            ((uint32)(CODEFLS_U4_REGADD_CSAB_BASE + 0x0100UL + (0x04UL * 0UL)))
#define CODEFLS_U4_REGADD_CSAB_CSAVOFC08            ((uint32)(CODEFLS_U4_REGADD_CSAB_BASE + 0x0100UL + (0x04UL * 8UL)))
#define CODEFLS_U4_REGADD_CSAB_CSAVOFC09            ((uint32)(CODEFLS_U4_REGADD_CSAB_BASE + 0x0100UL + (0x04UL * 9UL)))
#define CODEFLS_U4_REGADD_CSAB_CSAVOFC10            ((uint32)(CODEFLS_U4_REGADD_CSAB_BASE + 0x0100UL + (0x04UL * 10UL)))
#define CODEFLS_U4_REGADD_CSAB_CSAVOFC11            ((uint32)(CODEFLS_U4_REGADD_CSAB_BASE + 0x0100UL + (0x04UL * 11UL)))
#define CODEFLS_U4_REGADD_CSAB_CSAVOFC12            ((uint32)(CODEFLS_U4_REGADD_CSAB_BASE + 0x0100UL + (0x04UL * 12UL)))
#define CODEFLS_U4_REGADD_CSAB_CSAVOFC13            ((uint32)(CODEFLS_U4_REGADD_CSAB_BASE + 0x0100UL + (0x04UL * 13UL)))
#define CODEFLS_U4_REGADD_CSAB_CSAVOFC14            ((uint32)(CODEFLS_U4_REGADD_CSAB_BASE + 0x0100UL + (0x04UL * 14UL)))
#define CODEFLS_U4_REGADD_CSAB_CSAVOFC15            ((uint32)(CODEFLS_U4_REGADD_CSAB_BASE + 0x0100UL + (0x04UL * 15UL)))
#define CODEFLS_U4_REGADD_CSAB_CSAVOFC16            ((uint32)(CODEFLS_U4_REGADD_CSAB_BASE + 0x0100UL + (0x04UL * 16UL)))
#define CODEFLS_U4_REGADD_CSAB_CSAVOFC17            ((uint32)(CODEFLS_U4_REGADD_CSAB_BASE + 0x0100UL + (0x04UL * 17UL)))
#define CODEFLS_U4_REGADD_CSAB_CSAVOFC18            ((uint32)(CODEFLS_U4_REGADD_CSAB_BASE + 0x0100UL + (0x04UL * 18UL)))
#define CODEFLS_U4_REGADD_CSAB_CSAVOFC19            ((uint32)(CODEFLS_U4_REGADD_CSAB_BASE + 0x0100UL + (0x04UL * 19UL)))
#define CODEFLS_U1_CSAVOFCN_NUM                     ((uint8)13U)                           /* Number of CSAVOFCn registers */
#define CODEFLS_U4_REGBIT_CSA_CSAVOFCN_COMP         ((uint32)0x5AA5A55AUL)

/* Configration Setting Area Erase Address */
#define CODEFLS_U4_ERASEADD_CSAB                    (CODEFLS_U4_REGADD_CSAB_BASE)

/* Configration Setting Area Write Address */
/* Back Side */
#define CODEFLS_U4_WRITEADD_CSAB_AREA00             ((uint32)(CODEFLS_U4_REGADD_CSAB_BASE + 0x200UL + (0x20UL * 0UL)))
#define CODEFLS_U4_WRITEADD_CSAB_AREA08             ((uint32)(CODEFLS_U4_REGADD_CSAB_BASE + 0x200UL + (0x20UL * 8UL)))
#define CODEFLS_U4_WRITEADD_CSAB_AREA09             ((uint32)(CODEFLS_U4_REGADD_CSAB_BASE + 0x200UL + (0x20UL * 9UL)))
#define CODEFLS_U4_WRITEADD_CSAB_AREA10             ((uint32)(CODEFLS_U4_REGADD_CSAB_BASE + 0x200UL + (0x20UL * 10UL)))
#define CODEFLS_U4_WRITEADD_CSAB_AREA11             ((uint32)(CODEFLS_U4_REGADD_CSAB_BASE + 0x200UL + (0x20UL * 11UL)))
#define CODEFLS_U4_WRITEADD_CSAB_AREA12             ((uint32)(CODEFLS_U4_REGADD_CSAB_BASE + 0x200UL + (0x20UL * 12UL)))
#define CODEFLS_U4_WRITEADD_CSAB_AREA13             ((uint32)(CODEFLS_U4_REGADD_CSAB_BASE + 0x200UL + (0x20UL * 13UL)))
#define CODEFLS_U4_WRITEADD_CSAB_AREA14             ((uint32)(CODEFLS_U4_REGADD_CSAB_BASE + 0x200UL + (0x20UL * 14UL)))
#define CODEFLS_U4_WRITEADD_CSAB_AREA15             ((uint32)(CODEFLS_U4_REGADD_CSAB_BASE + 0x200UL + (0x20UL * 15UL)))
#define CODEFLS_U4_WRITEADD_CSAB_AREA16             ((uint32)(CODEFLS_U4_REGADD_CSAB_BASE + 0x200UL + (0x20UL * 16UL)))
#define CODEFLS_U4_WRITEADD_CSAB_AREA17             ((uint32)(CODEFLS_U4_REGADD_CSAB_BASE + 0x200UL + (0x20UL * 17UL)))
#define CODEFLS_U4_WRITEADD_CSAB_AREA18             ((uint32)(CODEFLS_U4_REGADD_CSAB_BASE + 0x200UL + (0x20UL * 18UL)))
#define CODEFLS_U4_WRITEADD_CSAB_AREA19             ((uint32)(CODEFLS_U4_REGADD_CSAB_BASE + 0x200UL + (0x20UL * 19UL)))

/* Front Side */
#define CODEFLS_U4_WRITEADD_CSAF_AREA00             ((uint32)(CODEFLS_U4_REGADD_CSAF_BASE + 0x200UL + (0x20UL * 0UL)))
#define CODEFLS_U4_WRITEADD_CSAF_AREA08             ((uint32)(CODEFLS_U4_REGADD_CSAF_BASE + 0x200UL + (0x20UL * 8UL)))
#define CODEFLS_U4_WRITEADD_CSAF_AREA09             ((uint32)(CODEFLS_U4_REGADD_CSAF_BASE + 0x200UL + (0x20UL * 9UL)))
#define CODEFLS_U4_WRITEADD_CSAF_AREA10             ((uint32)(CODEFLS_U4_REGADD_CSAF_BASE + 0x200UL + (0x20UL * 10UL)))
#define CODEFLS_U4_WRITEADD_CSAF_AREA11             ((uint32)(CODEFLS_U4_REGADD_CSAF_BASE + 0x200UL + (0x20UL * 11UL)))
#define CODEFLS_U4_WRITEADD_CSAF_AREA12             ((uint32)(CODEFLS_U4_REGADD_CSAF_BASE + 0x200UL + (0x20UL * 12UL)))
#define CODEFLS_U4_WRITEADD_CSAF_AREA13             ((uint32)(CODEFLS_U4_REGADD_CSAF_BASE + 0x200UL + (0x20UL * 13UL)))
#define CODEFLS_U4_WRITEADD_CSAF_AREA14             ((uint32)(CODEFLS_U4_REGADD_CSAF_BASE + 0x200UL + (0x20UL * 14UL)))
#define CODEFLS_U4_WRITEADD_CSAF_AREA15             ((uint32)(CODEFLS_U4_REGADD_CSAF_BASE + 0x200UL + (0x20UL * 15UL)))
#define CODEFLS_U4_WRITEADD_CSAF_AREA16             ((uint32)(CODEFLS_U4_REGADD_CSAF_BASE + 0x200UL + (0x20UL * 16UL)))
#define CODEFLS_U4_WRITEADD_CSAF_AREA17             ((uint32)(CODEFLS_U4_REGADD_CSAF_BASE + 0x200UL + (0x20UL * 17UL)))
#define CODEFLS_U4_WRITEADD_CSAF_AREA18             ((uint32)(CODEFLS_U4_REGADD_CSAF_BASE + 0x200UL + (0x20UL * 18UL)))
#define CODEFLS_U4_WRITEADD_CSAF_AREA19             ((uint32)(CODEFLS_U4_REGADD_CSAF_BASE + 0x200UL + (0x20UL * 19UL)))

/* Configration Setting Area Number of write area */
#define CODEFLS_U1_WRITEADD_AREA_NUM                ((uint8)13U)
/* Configration Setting Area Definition for area arrays */
#define CODEFLS_CSA_AREA_NUM                        (2U)
#define CODEFLS_CSA_AREA_BACK                       (0U)
#define CODEFLS_CSA_AREA_FRONT                      (1U)

/* OPBT13 */
#define CODEFLS_CSA_OPBT13_IDX                      (5U)
#define CODEFLS_U4_CSA_OPBT13_BIT_DBMAPSW0          ((uint32)0x00000001UL)
#define CODEFLS_U4_CSA_OPBT13_BIT_DBMAPSW1          ((uint32)0x00000002UL)

/* Security Setting Area */
/* VOF Program completion flag n for Security Setting Area : back side */
#define CODEFLS_U4_REGADD_SVAB_SSAVOFC00            ((uint32)(CODEFLS_U4_REGADD_SVAB_BASE + 0x0100UL + (0x04UL * 0UL)))
#define CODEFLS_U4_REGADD_SVAB_SSAVOFC01            ((uint32)(CODEFLS_U4_REGADD_SVAB_BASE + 0x0100UL + (0x04UL * 1UL)))
#define CODEFLS_U4_REGADD_SVAB_SSAVOFC07            ((uint32)(CODEFLS_U4_REGADD_SVAB_BASE + 0x0100UL + (0x04UL * 7UL)))
#define CODEFLS_U4_REGADD_SVAB_SSAVOFC08            ((uint32)(CODEFLS_U4_REGADD_SVAB_BASE + 0x0100UL + (0x04UL * 8UL)))
#define CODEFLS_U4_REGADD_SVAB_SSAVOFC09            ((uint32)(CODEFLS_U4_REGADD_SVAB_BASE + 0x0100UL + (0x04UL * 9UL)))
#define CODEFLS_U4_REGADD_SVAB_SSAVOFC10            ((uint32)(CODEFLS_U4_REGADD_SVAB_BASE + 0x0100UL + (0x04UL * 10UL)))
#define CODEFLS_U4_REGADD_SVAB_SSAVOFC11            ((uint32)(CODEFLS_U4_REGADD_SVAB_BASE + 0x0100UL + (0x04UL * 11UL)))
#define CODEFLS_U4_REGADD_SVAB_SSAVOFC12            ((uint32)(CODEFLS_U4_REGADD_SVAB_BASE + 0x0100UL + (0x04UL * 12UL)))
#define CODEFLS_U4_REGADD_SVAB_SSAVOFC13            ((uint32)(CODEFLS_U4_REGADD_SVAB_BASE + 0x0100UL + (0x04UL * 13UL)))
#define CODEFLS_U4_REGADD_SVAB_SSAVOFC14            ((uint32)(CODEFLS_U4_REGADD_SVAB_BASE + 0x0100UL + (0x04UL * 14UL)))
#define CODEFLS_U4_REGADD_SVAB_SSAVOFC15            ((uint32)(CODEFLS_U4_REGADD_SVAB_BASE + 0x0100UL + (0x04UL * 15UL)))
#define CODEFLS_U4_REGADD_SVAB_SSAVOFC16            ((uint32)(CODEFLS_U4_REGADD_SVAB_BASE + 0x0100UL + (0x04UL * 16UL)))
#define CODEFLS_U4_REGADD_SVAB_SSAVOFC17            ((uint32)(CODEFLS_U4_REGADD_SVAB_BASE + 0x0100UL + (0x04UL * 17UL)))
#define CODEFLS_U4_REGADD_SVAB_SSAVOFC18            ((uint32)(CODEFLS_U4_REGADD_SVAB_BASE + 0x0100UL + (0x04UL * 18UL)))
#define CODEFLS_U4_REGADD_SVAB_SSAVOFC40            ((uint32)(CODEFLS_U4_REGADD_SVAB_BASE + 0x0100UL + (0x04UL * 40UL)))
#define CODEFLS_U1_SSAVOFCN_NUM                     ((uint8)15U)                           /* Number of SSAVOFCn registers */
#define CODEFLS_U4_REGBIT_SVA_SSAVOFCN_COMP         ((uint32)0x5AA5A55AUL)

/* Block Protection Area */
/* VOF Program completion flag n for Block Protection Setting Area for FPSYS0 */
#define CODEFLS_U4_REGADD_BVA0B_BPA0VOFC00          ((uint32)(CODEFLS_U4_REGADD_BVA0B_BASE + 0x0100UL + (0x04UL * 0UL)))
#define CODEFLS_U4_REGADD_BVA0B_BPA0VOFC01          ((uint32)(CODEFLS_U4_REGADD_BVA0B_BASE + 0x0100UL + (0x04UL * 1UL)))
#define CODEFLS_U4_REGADD_BVA0B_BPA0VOFC02          ((uint32)(CODEFLS_U4_REGADD_BVA0B_BASE + 0x0100UL + (0x04UL * 2UL)))
#define CODEFLS_U4_REGADD_BVA0B_BPA0VOFC03          ((uint32)(CODEFLS_U4_REGADD_BVA0B_BASE + 0x0100UL + (0x04UL * 3UL)))
#define CODEFLS_U4_REGADD_BVA0B_BPA0VOFC04          ((uint32)(CODEFLS_U4_REGADD_BVA0B_BASE + 0x0100UL + (0x04UL * 4UL)))
#define CODEFLS_U4_REGADD_BVA0B_BPA0VOFC05          ((uint32)(CODEFLS_U4_REGADD_BVA0B_BASE + 0x0100UL + (0x04UL * 5UL)))
#define CODEFLS_U4_REGADD_BVA0B_BPA0VOFC06          ((uint32)(CODEFLS_U4_REGADD_BVA0B_BASE + 0x0100UL + (0x04UL * 6UL)))
#define CODEFLS_U4_REGADD_BVA0B_BPA0VOFC07          ((uint32)(CODEFLS_U4_REGADD_BVA0B_BASE + 0x0100UL + (0x04UL * 7UL)))
#define CODEFLS_U4_REGADD_BVA0B_BPA0VOFC15          ((uint32)(CODEFLS_U4_REGADD_BVA0B_BASE + 0x0100UL + (0x04UL * 15UL)))
#define CODEFLS_U4_REGADD_BVA0B_BPA0VOFC16          ((uint32)(CODEFLS_U4_REGADD_BVA0B_BASE + 0x0100UL + (0x04UL * 16UL)))
#define CODEFLS_U4_REGADD_BVA0B_BPA0VOFC17          ((uint32)(CODEFLS_U4_REGADD_BVA0B_BASE + 0x0100UL + (0x04UL * 17UL)))
#define CODEFLS_U4_REGADD_BVA0B_BPA0VOFC18          ((uint32)(CODEFLS_U4_REGADD_BVA0B_BASE + 0x0100UL + (0x04UL * 18UL)))
#define CODEFLS_U4_REGADD_BVA0B_BPA0VOFC19          ((uint32)(CODEFLS_U4_REGADD_BVA0B_BASE + 0x0100UL + (0x04UL * 19UL)))
#define CODEFLS_U4_REGADD_BVA0B_BPA0VOFC20          ((uint32)(CODEFLS_U4_REGADD_BVA0B_BASE + 0x0100UL + (0x04UL * 20UL)))
#define CODEFLS_U4_REGADD_BVA0B_BPA0VOFC21          ((uint32)(CODEFLS_U4_REGADD_BVA0B_BASE + 0x0100UL + (0x04UL * 21UL)))
#define CODEFLS_U4_REGADD_BVA0B_BPA0VOFC22          ((uint32)(CODEFLS_U4_REGADD_BVA0B_BASE + 0x0100UL + (0x04UL * 22UL)))
#define CODEFLS_U4_REGADD_BVA0B_BPA0VOFC23          ((uint32)(CODEFLS_U4_REGADD_BVA0B_BASE + 0x0100UL + (0x04UL * 23UL)))
#define CODEFLS_U4_REGADD_BVA0B_BPA0VOFC24          ((uint32)(CODEFLS_U4_REGADD_BVA0B_BASE + 0x0100UL + (0x04UL * 24UL)))
#define CODEFLS_U4_REGADD_BVA0B_BPA0VOFC25          ((uint32)(CODEFLS_U4_REGADD_BVA0B_BASE + 0x0100UL + (0x04UL * 25UL)))
#define CODEFLS_U4_REGADD_BVA0B_BPA0VOFC26          ((uint32)(CODEFLS_U4_REGADD_BVA0B_BASE + 0x0100UL + (0x04UL * 26UL)))
#define CODEFLS_U4_REGADD_BVA0B_BPA0VOFC27          ((uint32)(CODEFLS_U4_REGADD_BVA0B_BASE + 0x0100UL + (0x04UL * 27UL)))
#define CODEFLS_U4_REGADD_BVA0B_BPA0VOFC28          ((uint32)(CODEFLS_U4_REGADD_BVA0B_BASE + 0x0100UL + (0x04UL * 28UL)))
#define CODEFLS_U4_REGADD_BVA0B_BPA0VOFC29          ((uint32)(CODEFLS_U4_REGADD_BVA0B_BASE + 0x0100UL + (0x04UL * 29UL)))
#define CODEFLS_U4_REGADD_BVA0B_BPA0VOFC30          ((uint32)(CODEFLS_U4_REGADD_BVA0B_BASE + 0x0100UL + (0x04UL * 30UL)))
#define CODEFLS_U4_REGADD_BVA0B_BPA0VOFC31          ((uint32)(CODEFLS_U4_REGADD_BVA0B_BASE + 0x0100UL + (0x04UL * 31UL)))
#define CODEFLS_U4_REGADD_BVA0B_BPA0VOFC39          ((uint32)(CODEFLS_U4_REGADD_BVA0B_BASE + 0x0100UL + (0x04UL * 39UL)))
#define CODEFLS_U1_BPA0VOFCN_NUM                    ((uint8)26U)                           /* Number of BPA0VOFCn registers */

/* Valid Option Byte Flag n for Block Protection Area for FPSYS1 */
#define CODEFLS_U4_REGADD_BVA1B_BPA1VOFC00          ((uint32)(CODEFLS_U4_REGADD_BVA1B_BASE + 0x0100UL + (0x04UL * 0UL)))
#define CODEFLS_U4_REGADD_BVA1B_BPA1VOFC01          ((uint32)(CODEFLS_U4_REGADD_BVA1B_BASE + 0x0100UL + (0x04UL * 1UL)))
#define CODEFLS_U4_REGADD_BVA1B_BPA1VOFC02          ((uint32)(CODEFLS_U4_REGADD_BVA1B_BASE + 0x0100UL + (0x04UL * 2UL)))
#define CODEFLS_U4_REGADD_BVA1B_BPA1VOFC03          ((uint32)(CODEFLS_U4_REGADD_BVA1B_BASE + 0x0100UL + (0x04UL * 3UL)))
#define CODEFLS_U4_REGADD_BVA1B_BPA1VOFC04          ((uint32)(CODEFLS_U4_REGADD_BVA1B_BASE + 0x0100UL + (0x04UL * 4UL)))
#define CODEFLS_U4_REGADD_BVA1B_BPA1VOFC05          ((uint32)(CODEFLS_U4_REGADD_BVA1B_BASE + 0x0100UL + (0x04UL * 5UL)))
#define CODEFLS_U4_REGADD_BVA1B_BPA1VOFC06          ((uint32)(CODEFLS_U4_REGADD_BVA1B_BASE + 0x0100UL + (0x04UL * 6UL)))
#define CODEFLS_U4_REGADD_BVA1B_BPA1VOFC07          ((uint32)(CODEFLS_U4_REGADD_BVA1B_BASE + 0x0100UL + (0x04UL * 7UL)))
#define CODEFLS_U4_REGADD_BVA1B_BPA1VOFC16          ((uint32)(CODEFLS_U4_REGADD_BVA1B_BASE + 0x0100UL + (0x04UL * 16UL)))
#define CODEFLS_U4_REGADD_BVA1B_BPA1VOFC17          ((uint32)(CODEFLS_U4_REGADD_BVA1B_BASE + 0x0100UL + (0x04UL * 17UL)))
#define CODEFLS_U4_REGADD_BVA1B_BPA1VOFC18          ((uint32)(CODEFLS_U4_REGADD_BVA1B_BASE + 0x0100UL + (0x04UL * 18UL)))
#define CODEFLS_U4_REGADD_BVA1B_BPA1VOFC19          ((uint32)(CODEFLS_U4_REGADD_BVA1B_BASE + 0x0100UL + (0x04UL * 19UL)))
#define CODEFLS_U4_REGADD_BVA1B_BPA1VOFC20          ((uint32)(CODEFLS_U4_REGADD_BVA1B_BASE + 0x0100UL + (0x04UL * 20UL)))
#define CODEFLS_U4_REGADD_BVA1B_BPA1VOFC21          ((uint32)(CODEFLS_U4_REGADD_BVA1B_BASE + 0x0100UL + (0x04UL * 21UL)))
#define CODEFLS_U4_REGADD_BVA1B_BPA1VOFC22          ((uint32)(CODEFLS_U4_REGADD_BVA1B_BASE + 0x0100UL + (0x04UL * 22UL)))
#define CODEFLS_U4_REGADD_BVA1B_BPA1VOFC23          ((uint32)(CODEFLS_U4_REGADD_BVA1B_BASE + 0x0100UL + (0x04UL * 23UL)))
#define CODEFLS_U4_REGADD_BVA1B_BPA1VOFC24          ((uint32)(CODEFLS_U4_REGADD_BVA1B_BASE + 0x0100UL + (0x04UL * 24UL)))
#define CODEFLS_U4_REGADD_BVA1B_BPA1VOFC25          ((uint32)(CODEFLS_U4_REGADD_BVA1B_BASE + 0x0100UL + (0x04UL * 25UL)))
#define CODEFLS_U4_REGADD_BVA1B_BPA1VOFC26          ((uint32)(CODEFLS_U4_REGADD_BVA1B_BASE + 0x0100UL + (0x04UL * 26UL)))
#define CODEFLS_U4_REGADD_BVA1B_BPA1VOFC27          ((uint32)(CODEFLS_U4_REGADD_BVA1B_BASE + 0x0100UL + (0x04UL * 27UL)))
#define CODEFLS_U4_REGADD_BVA1B_BPA1VOFC28          ((uint32)(CODEFLS_U4_REGADD_BVA1B_BASE + 0x0100UL + (0x04UL * 28UL)))
#define CODEFLS_U4_REGADD_BVA1B_BPA1VOFC29          ((uint32)(CODEFLS_U4_REGADD_BVA1B_BASE + 0x0100UL + (0x04UL * 29UL)))
#define CODEFLS_U4_REGADD_BVA1B_BPA1VOFC30          ((uint32)(CODEFLS_U4_REGADD_BVA1B_BASE + 0x0100UL + (0x04UL * 30UL)))
#define CODEFLS_U4_REGADD_BVA1B_BPA1VOFC31          ((uint32)(CODEFLS_U4_REGADD_BVA1B_BASE + 0x0100UL + (0x04UL * 31UL)))
#define CODEFLS_U1_BPA1VOFCN_NUM                    ((uint8)24U)                           /* Number of BPA1VOFCn registers */

#define CODEFLS_U4_REGBIT_BVA_BPAVOFCN_COMP         ((uint32)0x5AA5A55AUL)

/* Switch Area */
/* Area n Program Complete Flag */
#define CODEFLS_U4_REGADD_SWAB_ANPC                 ((uint32)(CODEFLS_U4_REGADD_SWAB_BASE + 0x0000UL))
#define CODEFLS_U4_REGBIT_SWA_ANPC_COMP             ((uint32)0x5AA5A55AUL)

/* Configuration setting Valid Area */
#define CODEFLS_U4_REGADD_SWAF_CVA                  ((uint32)(CODEFLS_U4_REGADD_SWAF_BASE + 0x0200UL))
#define CODEFLS_U4_REGADD_SWAB_CVA                  ((uint32)(CODEFLS_U4_REGADD_SWAB_BASE + 0x0200UL))
#define CODEFLS_U4_REGBIT_SWA_CVA_AREA0             ((uint32)0xA55A5AA5UL)
#define CODEFLS_U4_REGBIT_SWA_CVA_AREA1             ((uint32)0x5AA5A55AUL)

/* Security setting Valid Area */
#define CODEFLS_U4_REGADD_SWAF_SVA                  ((uint32)(CODEFLS_U4_REGADD_SWAF_BASE + 0x0204UL))
#define CODEFLS_U4_REGADD_SWAB_SVA                  ((uint32)(CODEFLS_U4_REGADD_SWAB_BASE + 0x0204UL))
#define CODEFLS_U4_REGBIT_SWA_SVA_AREA0             ((uint32)0xA55A5AA5UL)
#define CODEFLS_U4_REGBIT_SWA_SVA_AREA1             ((uint32)0x5AA5A55AUL)

/* Block protection setting Valid Area for FPSYS0 */
#define CODEFLS_U4_REGADD_SWAF_BVA0                 ((uint32)(CODEFLS_U4_REGADD_SWAF_BASE + 0x0208UL))
#define CODEFLS_U4_REGADD_SWAB_BVA0                 ((uint32)(CODEFLS_U4_REGADD_SWAB_BASE + 0x0208UL))
/* Block protection setting Valid Area for FPSYS1 */
#define CODEFLS_U4_REGADD_SWAF_BVA1                 ((uint32)(CODEFLS_U4_REGADD_SWAF_BASE + 0x020CUL))
#define CODEFLS_U4_REGADD_SWAB_BVA1                 ((uint32)(CODEFLS_U4_REGADD_SWAB_BASE + 0x020CUL))
#define CODEFLS_U4_REGBIT_SWA_BVA_AREA0             ((uint32)0xA55A5AA5UL)
#define CODEFLS_U4_REGBIT_SWA_BVA_AREA1             ((uint32)0x5AA5A55AUL)

/* Security Setting Area Erase Address */
#define CODEFLS_U4_ERASEADD_SWAB                    (CODEFLS_U4_REGADD_SWAB_BASE)

/* Security Setting Area Write Address */
#define CODEFLS_U4_WRITEADD_SWAB_CVA                ((uint32)(CODEFLS_U4_REGADD_SWAB_BASE + 0x0200UL))

/* Security Setting Area Reserved Value */
#define CODEFLS_U4_SWA_RESERVED                     ((uint32)0xFFFFFFFFUL)

/* TAG Area */
/* VAF Program Complete Flag */
#define CODEFLS_U4_REGADD_TAG_VAPC                  ((uint32)(CODEFLS_U4_REGADD_TAG_BASE + 0x0000UL))
#define CODEFLS_U4_REGBIT_TAG_VAPC_VALUE            ((uint32)0x5AA5A55AUL)

/* Configration Setting Area Erase Address */
#define CODEFLS_U4_ERASEADD_TAG                     (CODEFLS_U4_REGADD_TAG_BASE)

/* Configration Setting Area Write Address */
#define CODEFLS_U4_WRITEADD_TAG_VAF                 (CODEFLS_U4_REGADD_TAG_BASE + 0x0200UL)

/* Long-Term System Counter : LTSC0 */
#define CODEFLS_U4_REGADD_LTSC0_TCS                 (CODEFLS_U4_REGADD_LTSC0_BASE + 0x0010UL)
#define CODEFLS_U4_REGADD_LTSC0_CNTL                (CODEFLS_U4_REGADD_LTSC0_BASE + 0x0040UL)
#define CODEFLS_U4_REGBIT_LTSC0_TS                  ((uint32)0x00000001UL)

/* Code Flash ECC */
#define CODEFLS_U4_REG_CF_SERSTR            (*(AB_83_ConstV uint32 *)(CODEFLS_U4_REG_CFECC_CFLCAP_BASE + 0x20UL))   /* Code Flash 1-bit error status register                       */
#define CODEFLS_U4_REG_CF_DERSTR            (*(AB_83_ConstV uint32 *)(CODEFLS_U4_REG_CFECC_CFLCAP_BASE + 0x24UL))   /* Code Flash Fatal error status register                       */
/* MISRA DEVIATION */ /* It may be replaceable with another equivalent function call */
#define CODEFLS_U4_REG_CF_nSEADR(n)         (*(AB_83_ConstV uint32 *)(CODEFLS_U4_REG_CFECC_CFLCAP_BASE + 0x70UL + (0x04UL * (n))))  /* Code Flash n-th 1-bit error address register : n = 0-3 */
#define CODEFLS_U4_REG_CF_00DEADR           (*(AB_83_ConstV uint32 *)(CODEFLS_U4_REG_CFECC_CFLCAP_BASE + 0xF0UL))   /* Code Flash 1st fatal error address register                  */

/* Code Flash 1-bit Error Status Register : CF_SERSTR */
#define CODEFLS_U4_CF_SERSTR_SEDF03         ((uint32)0x00000008UL)          /* Indicates ECC 1 bit error is detected and error address is stored in CF_03SEADR register     */
#define CODEFLS_U4_CF_SERSTR_SEDF02         ((uint32)0x00000004UL)          /* Indicates ECC 1 bit error is detected and error address is stored in CF_02SEADR register     */
#define CODEFLS_U4_CF_SERSTR_SEDF01         ((uint32)0x00000002UL)          /* Indicates ECC 1 bit error is detected and error address is stored in CF_01SEADR register     */
#define CODEFLS_U4_CF_SERSTR_SEDF00         ((uint32)0x00000001UL)          /* Indicates ECC 1 bit error is detected and error address is stored in CF_00SEADR register     */
#define CODEFLS_U4_CF_SERSTR_ALL            (CODEFLS_U4_CF_SERSTR_SEDF03 \
                                            |CODEFLS_U4_CF_SERSTR_SEDF02 \
                                            |CODEFLS_U4_CF_SERSTR_SEDF01 \
                                            |CODEFLS_U4_CF_SERSTR_SEDF00)
#define CODEFLS_U4_CF_SERSTR_RESET          ((uint32)0x00000000UL)          /* reset Value                                                                                  */

/* Code Flash Fatal Error Status Register : CF_DERSTR */
#define CODEFLS_U4_CF_DERSTR_APEF00         ((uint32)0x00000004UL)          /* Indicates address parity error is detected                                                   */
#define CODEFLS_U4_CF_DERSTR_DEDF00         ((uint32)0x00000002UL)          /* Indicates ECC 2 bit error is detected                                                        */
#define CODEFLS_U4_CF_DERSTR_ALL            (CODEFLS_U4_CF_DERSTR_APEF00 \
                                            |CODEFLS_U4_CF_DERSTR_DEDF00)
#define CODEFLS_U4_CF_DERSTR_RESET          ((uint32)0x00000000UL)          /* reset Value                                                                                  */

/* Code Flash n-th 1-bit Error Address Register(CF_nSEADR) */
/* Code Flash 1st Fatal Error Address Register(CF_00DEADR) */
#define CODEFLS_U4_CF_EADR_MASK             ((uint32)0x03FFFFFCUL)          /* address mask                                                                                 */

#define CODEFLS_U4_CF_EADR_INF_FT_PE0       ((uint32)0x00000000UL)          /* Indicates ECC error is detected in read data fetched from CodeFlash to PE0                   */
#define CODEFLS_U4_CF_EADR_INF_FT_PE1       ((uint32)0x10000000UL)          /* Indicates ECC error is detected in read data fetched from CodeFlash to PE1                   */
#define CODEFLS_U4_CF_EADR_INF_FT_PE2       ((uint32)0x20000000UL)          /* Indicates ECC error is detected in read data fetched from CodeFlash to PE2                   */
#define CODEFLS_U4_CF_EADR_INF_FT_PE3       ((uint32)0x30000000UL)          /* Indicates ECC error is detected in read data fetched from CodeFlash to PE3                   */
#define CODEFLS_U4_CF_EADR_INF_LD_PE0       ((uint32)0x08000000UL)          /* Indicates ECC error is detected in read data loaded from CodeFlash to PE0                    */
#define CODEFLS_U4_CF_EADR_INF_LD_PE1       ((uint32)0x18000000UL)          /* Indicates ECC error is detected in read data loaded from CodeFlash to PE1                    */
#define CODEFLS_U4_CF_EADR_INF_LD_PE2       ((uint32)0x28000000UL)          /* Indicates ECC error is detected in read data loaded from CodeFlash to PE2                    */
#define CODEFLS_U4_CF_EADR_INF_LD_PE3       ((uint32)0x38000000UL)          /* Indicates ECC error is detected in read data loaded from CodeFlash to PE3                    */
#define CODEFLS_U4_CF_EADR_INF_MASK         ((uint32)0xF8000000UL)          /* information mask                                                                             */


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef struct
{
    CONSTP2VAR(uint8, TYPEDEF, MEM_CONST) AB_83_ConstV          pu1CMDAREA;                 /* FACI command-issuing area :1byte                         */
    CONSTP2VAR(uint32, TYPEDEF, MEM_CONST) AB_83_ConstV          pu4CMDAREA;                 /* FACI command-issuing area :4byte                         */
    CONSTP2VAR(uint8, TYPEDEF, MEM_CONST) AB_83_ConstV          pu1FPMON;                   /* Flash Pin Monitor Register                               */
    CONSTP2VAR(uint8, TYPEDEF, MEM_CONST) AB_83_ConstV          pu1FASTAT;                  /* Flash Access Status Register                             */
    CONSTP2VAR(uint8, TYPEDEF, MEM_CONST) AB_83_ConstV          pu1FAEINT;                  /* Flash Access Error Interrupt Enable Register             */
    CONSTP2VAR(uint32, TYPEDEF, MEM_CONST) AB_83_ConstV          pu4FSADDR;                  /* Flash Command Start Address Register                     */
    CONSTP2VAR(uint32, TYPEDEF, MEM_CONST) AB_83_ConstV          pu4FEADDR;                  /* Flash Command End Address Register                       */
    CONSTP2VAR(uint16, TYPEDEF, MEM_CONST) AB_83_ConstV          pu2FCVAPROT;                /* Code Flash Valid Area Protection Register                */
    CONSTP2VAR(uint32, TYPEDEF, MEM_CONST) AB_83_ConstV          pu4FSTATR;                  /* Flash Status Register                                    */
    CONST     (AB_83_ConstV uint32, MEM_CONST)                     u4FSTATRADD;                /* Flash Status Register :Address                           */
    CONSTP2VAR(uint16, TYPEDEF, MEM_CONST) AB_83_ConstV          pu2FENTRYR;                 /* Flash Programming/Erasure Mode Entry Register            */
    CONST     (AB_83_ConstV uint32, MEM_CONST)                     u4FENTRYRADD;               /* Flash Programming/Erasure Mode Entry Register :Address   */
    CONSTP2VAR(uint16, TYPEDEF, MEM_CONST) AB_83_ConstV          pu2FSUINITR;                /* Flash Sequencer Set-up Initialize Register               */
    CONSTP2VAR(uint8, TYPEDEF, MEM_CONST) AB_83_ConstV          pu1FRTEINT;                 /* FACI Reset Transfer Warning Interrupt Enable Register    */
    CONSTP2VAR(uint16, TYPEDEF, MEM_CONST) AB_83_ConstV          pu2FECCTMD;                 /* Flash ECC Test Mode Register                             */
    CONSTP2VAR(uint32, TYPEDEF, MEM_CONST) AB_83_ConstV          pu4FHVE3;                   /* FHVE3 ontrol Register                                    */
    CONSTP2VAR(uint32, TYPEDEF, MEM_CONST) AB_83_ConstV          pu4FHVE15;                  /* FHVE15 ontrol Register                                   */
    CONSTP2VAR(uint16, TYPEDEF, MEM_CONST) AB_83_ConstV          pu2FCPSR;                   /* Flash Sequencer Process Switch Register                  */
} st_CodeFls_FACI_RegType;

typedef struct
{
    CONSTP2VAR(uint32, TYPEDEF, MEM_CONST) AB_83_ConstV          pu4CUSTIDxIN0;              /* Customer ID x Input Register 0                           */
    CONSTP2VAR(uint32, TYPEDEF, MEM_CONST) AB_83_ConstV          pu4CUSTIDxIN1;              /* Customer ID x Input Register 1                           */
    CONSTP2VAR(uint32, TYPEDEF, MEM_CONST) AB_83_ConstV          pu4CUSTIDxIN2;              /* Customer ID x Input Register 2                           */
    CONSTP2VAR(uint32, TYPEDEF, MEM_CONST) AB_83_ConstV          pu4CUSTIDxIN3;              /* Customer ID x Input Register 3                           */
    CONSTP2VAR(uint32, TYPEDEF, MEM_CONST) AB_83_ConstV          pu4CUSTIDxIN4;              /* Customer ID x Input Register 4                           */
    CONSTP2VAR(uint32, TYPEDEF, MEM_CONST) AB_83_ConstV          pu4CUSTIDxIN5;              /* Customer ID x Input Register 5                           */
    CONSTP2VAR(uint32, TYPEDEF, MEM_CONST) AB_83_ConstV          pu4CUSTIDxIN6;              /* Customer ID x Input Register 6                           */
    CONSTP2VAR(uint32, TYPEDEF, MEM_CONST) AB_83_ConstV          pu4CUSTIDxIN7;              /* Customer ID x Input Register 7                           */
} st_CodeFls_IDCTRL_RegType;

typedef struct
{
    CONSTP2VAR(uint32, TYPEDEF, MEM_CONST) AB_83_ConstV          pu4CSAVOFCn[CODEFLS_U1_CSAVOFCN_NUM];       /* VOF Program completion flag n for Configuration Setting Area               */
} st_CodeFls_CSA_RegType;

typedef struct
{
    CONSTP2VAR(uint32, TYPEDEF, MEM_CONST) AB_83_ConstV          pu4SSAVOFCn[CODEFLS_U1_SSAVOFCN_NUM];       /* VOF Program completion flag n for Security Setting Area                    */
} st_CodeFls_SVA_RegType;

typedef struct
{
    CONSTP2VAR(uint32, TYPEDEF, MEM_CONST) AB_83_ConstV          pu4BPA0VOFCn[CODEFLS_U1_BPA0VOFCN_NUM];     /* VOF Program completion flag n for Block Protection Setting Area for FPSYS0 */
    CONSTP2VAR(uint32, TYPEDEF, MEM_CONST) AB_83_ConstV          pu4BPA1VOFCn[CODEFLS_U1_BPA1VOFCN_NUM];     /* VOF Program completion flag n for Block Protection Setting Area for FPSYS1 */
} st_CodeFls_BVA_RegType;

typedef struct
{
    CONSTP2VAR(uint32, TYPEDEF, MEM_CONST) AB_83_ConstV          pu4CVA;         /* Configuration setting Valid Area                 */
    CONSTP2VAR(uint32, TYPEDEF, MEM_CONST) AB_83_ConstV          pu4SVA;         /* Security setting Valid Area                      */
    CONSTP2VAR(uint32, TYPEDEF, MEM_CONST) AB_83_ConstV          pu4BVA0;        /* Block protection setting Valid Area for FPSYS0   */
    CONSTP2VAR(uint32, TYPEDEF, MEM_CONST) AB_83_ConstV          pu4BVA1;        /* Block protection setting Valid Area for FPSYS1   */
} st_CodeFls_SWAF_RegType;

typedef struct
{
    CONSTP2VAR(uint32, TYPEDEF, MEM_CONST) AB_83_ConstV          pu4AnPC;        /* Area n Program Complete Flag                     */
    CONSTP2VAR(uint32, TYPEDEF, MEM_CONST) AB_83_ConstV          pu4CVA;         /* Configuration setting Valid Area                 */
    CONSTP2VAR(uint32, TYPEDEF, MEM_CONST) AB_83_ConstV          pu4SVA;         /* Security setting Valid Area                      */
    CONSTP2VAR(uint32, TYPEDEF, MEM_CONST) AB_83_ConstV          pu4BVA0;        /* Block protection setting Valid Area for FPSYS0   */
    CONSTP2VAR(uint32, TYPEDEF, MEM_CONST) AB_83_ConstV          pu4BVA1;        /* Block protection setting Valid Area for FPSYS1   */
} st_CodeFls_SWAB_RegType;

typedef struct
{
    CONSTP2VAR(uint32, TYPEDEF, MEM_CONST) AB_83_ConstV          pu4VAPC;        /* VAF Program Complete Flag                        */
} st_CodeFls_TAG_RegType;

typedef struct
{
    CONSTP2VAR(uint32, TYPEDEF, MEM_CONST) AB_83_ConstV          pu4LTSCnTCS;    /* LTSC Timer Counter Start Register                */
    CONSTP2VAR(uint32, TYPEDEF, MEM_CONST) AB_83_ConstV          pu4LTSCnCNTL;   /* LTSC Timer Counter Register L                    */
} st_CodeFls_LTSC_RegType;

typedef struct
{
    CONSTP2VAR(uint32, TYPEDEF, MEM_CONST) AB_83_ConstV          pu4FLMDCNT;     /* FLMD Control Register                            */
    CONSTP2VAR(uint32, TYPEDEF, MEM_CONST) AB_83_ConstV          pu4IDST;        /* ID Authentication Status Register                */
    CONSTP2VAR(uint32, TYPEDEF, MEM_CONST) AB_83_ConstV          pu4CFMAPSTT;    /* Code Flash Memory Mapping Mode Status Register   */
    CONSTP2VAR(uint8, TYPEDEF, MEM_CONST) AB_83_ConstV          pu1FSWASTAT;    /* Switch Area Status Register                      */
    st_CodeFls_FACI_RegType     FACI[CODEFLS_U1_FACI_NUM];                              /* Register Structure by FACI                       */
    st_CodeFls_IDCTRL_RegType   ID[CODEFLS_U1_AUTHID_NUM];                              /* Register structure by authentication ID          */
    st_CodeFls_CSA_RegType      CSA;                                                    /* Configration Setting Area Register Structure     */
    st_CodeFls_SVA_RegType      SVA;                                                    /* Security Setting Area Register Structure         */
    st_CodeFls_BVA_RegType      BVA;                                                    /* Block Protection Area  Register Structure        */
    st_CodeFls_SWAF_RegType     SWAF;                                                   /* Swith Area: front side Register Structure        */
    st_CodeFls_SWAB_RegType     SWAB;                                                   /* Swith Area: back side Register Structure         */
    st_CodeFls_TAG_RegType      TAG;                                                    /* TAG Area Register Structure                      */
    st_CodeFls_LTSC_RegType     LTSC;                                                   /* LTSC0 Register Structure                         */
} st_CodeFls_RegType;


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define MEM_START_SEC_VAR_NO_INIT_32
#include <Mem_MemMap.h>

#define MEM_STOP_SEC_VAR_NO_INIT_32
#include <Mem_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define MEM_START_SEC_CONST_32
#include <Mem_MemMap.h>

#define MEM_STOP_SEC_CONST_32
#include <Mem_MemMap.h>


#endif  /* CODEFLS_REG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1.00          :2025/03/24                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
