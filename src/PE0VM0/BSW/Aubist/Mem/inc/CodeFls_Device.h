/* CodeFls_Device_h                                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | RH850/U2Ax/CodeFls/HEADER                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef CODEFLS_DEVICE_H
#define CODEFLS_DEVICE_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* FACI Number */
#define CODEFLS_U1_FACI_NUM                 ((uint8)2U)

/* Number of FACI by microcomputer */
#define CODEFLS_U1_FACI_NUM_U2A8_U2A6       ((uint8)1U)
#define CODEFLS_U1_FACI_NUM_U2A16           ((uint8)2U)

/* Number of authentication ID types */
#define CODEFLS_U1_AUTHID_NUM               ((uint8)3U)

/* Number of authentication ID registers */
#define CODEFLS_U1_AUTHID_CNT               ((uint8)8U)

/* FACIn Register Base Address */
#define CODEFLS_U4_REGADD_FACI0_BASE        ((uint32)0xFFA10000UL)
#define CODEFLS_U4_REGADD_FACI1_BASE        ((uint32)0xFFA14000UL)

/* Self-programming ID input Register Base Address */
#define CODEFLS_U4_REGADD_AUTH_BASE         ((uint32)0xFFA08000UL)

/* FLMD Register Base Address */
#define CODEFLS_U4_REGADD_FLMD_BASE         ((uint32)0xFFA00000UL)

/* FHVE Register Base Address */
#define CODEFLS_U4_REGADD_FHVE_BASE         ((uint32)0xFF984800UL)

/* SCDS Register Base Address */
#define CODEFLS_U4_REGADD_SCDS_BASE         ((uint32)0xFFCD0000UL)

/* Configration Setting Area Base Address */
#define CODEFLS_U4_REGADD_CSAF_BASE         ((uint32)0xFF320800UL)
#define CODEFLS_U4_REGADD_CSAB_BASE         ((uint32)0xFF321000UL)

/* Security Setting Area Base Address */
#define CODEFLS_U4_REGADD_SVAB_BASE         ((uint32)0xFF322000UL)

/* Block Protection Area Base Address*/
#define CODEFLS_U4_REGADD_BVA0B_BASE        ((uint32)0xFF323000UL)
#define CODEFLS_U4_REGADD_BVA1B_BASE        ((uint32)0xFF340800UL)

/* Switch Area Base Address */
#define CODEFLS_U4_REGADD_SWAF_BASE         ((uint32)0xFF373800UL)
#define CODEFLS_U4_REGADD_SWAB_BASE         ((uint32)0xFF374000UL)

/* TAG Area Base Address */
#define CODEFLS_U4_REGADD_TAG_BASE          ((uint32)0xFF374800UL)

/* LTSC0 Base Address */
#define CODEFLS_U4_REGADD_LTSC0_BASE        ((uint32)0xFFC78100UL)

/* ECC Register Base Address */
#define CODEFLS_U4_REG_CFECC_CFLCAP_BASE    ((uint32)0xFFC52400UL)          /* Code Flash ECC(MECCCAP_CFL)          */

/* Maximum CPU operating frequency by microcomputer */
#define CODEFLS_U2_CPUCLK_MAX               ((uint16)400U)

/* Processing Monitoring Timer */
#define CODEFLS_U4_ERASE_TIME               ((uint32)0x0012C0C8UL)          /* Erase Monitoring Timer -             1229ms */
#define CODEFLS_U4_WRITE_TIME               ((uint32)0x00000FA0UL)          /* Write Monitoring Timer -                4ms */
#define CODEFLS_U4_PROPERTY_ERASE_TIME      ((uint32)0x00021B10UL)          /* Property Erasure Monitoring Timer -   138ms */
#define CODEFLS_U4_PROPERTY_WRITE_TIME      ((uint32)0x00000FA0UL)          /* Property Programming Monitoring Timer - 4ms */
#define CODEFLS_U4_SWITCH_ERASE_TIME        ((uint32)0x000226C8UL)          /* Switch Erasure Monitoring Timer -     141ms */
#define CODEFLS_U4_SWITCH_WRITE_TIME        ((uint32)0x00000BB8UL)          /* Switch Programming Monitoring Timer -   3ms */
#define CODEFLS_U4_TAG_ERASE_TIME           ((uint32)0x000226C8UL)          /* TAG Erasure Monitoring Timer -        141ms */
#define CODEFLS_U4_TAG_UPDATE_TIME          ((uint32)0x00000BB8UL)          /* TAG Update Monitoring Timer -           3ms */

#define CODEFLS_U4_FORCEDSTOP_TIME          ((uint32)40UL)                  /* Forced stop command wait time - microsecond           */
#define CODEFLS_U4_ICUCPE_TIME              ((uint32)10000UL)               /* Cord Flash P/E Mode Switching wait time - microsecond */
#define CODEFLS_U4_REGREADY_CLKCNT          ((uint32)45UL)                  /* Number of clocks in the CodeFls_Drv_GetRegReady_Asm   */
#define CODEFLS_U4_REGREADY16BIT_CLKCNT     ((uint32)45UL)                  /* Number of clocks in the CodeFls_Drv_GetRegReady16bit_Asm  */
#define CODEFLS_U4_CLK_HSB                  ((uint32)80UL)                  /* Peripheral high speed clock */


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


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


#endif  /* CODEFLS_DEVICE_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1.00          :2025/03/24                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
