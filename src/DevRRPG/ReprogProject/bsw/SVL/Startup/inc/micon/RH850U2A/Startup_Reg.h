/* Startup_Reg_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Startup/Reg/HEADER                                          */
/******************************************************************************/
#ifndef STARTUP_REG_H
#define STARTUP_REG_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/*******/
/* CPU */
/*******/
/* EBASE */
#define STARTUP_VAL_EBASE_RINT_DV_ON                (0x00000003UL)  /* Vector address shrink and direct vector method */
/* ICCTRL */
#define STARTUP_VAL_ICCTRL_OFF                      (0x00010002UL)  /* Instruction cache is invalid */
#define STARTUP_VAL_ICCTRL_CLEAR                    (0x00010102UL)  /* Instruction cache is invalid and the entire instruction cache is cleared */
#define STARTUP_VAL_ICCTRL_RESET                    (0x00010003UL)  /* Instruction cache is valid(= Value after reset) */
/* RDBCR */
#define STARTUP_VAL_RDBCR_CLEAR                     (0x00000103UL)  /* Clear */
/* PSW */
#define STARTUP_VAL_PSW_RESET                       (0x00000020UL)  /* Value after reset */

/********/
/* OPBT */
/********/
/* Address */
#define STARTUP_REG_CSAF_BASE                       (0xFF320800UL)
#define STARTUP_REG_CSAF_OPBT9                      (STARTUP_REG_CSAF_BASE + 0x3C4UL)
/* Mask */
#define STARTUP_MASK_CSAF_OPBT9_PE0_HVE             (0x00000100UL)  /* PE0 Hypervisor */

/********/
/* INTC */
/********/
/* Address */
#define STARTUP_REG_INTC1_PE0_BASE                  (0xFFFC4000UL)
#define STARTUP_REG_INTC1_PE0_IHVCFG                (STARTUP_REG_INTC1_PE0_BASE + 0x2F0UL)

/*********/
/* Reset */
/*********/
/* Address */
#define STARTUP_REG_RESET_RESF                      (0xFF988500UL)
#define STARTUP_REG_RESET_RESFC                     (0xFF980C00UL)
/* Set value */
#define STARTUP_VAL_RESET_RESFC_CLEAR               (0x0000F5DDUL)  /* All clear */
/* Mask */
#define STARTUP_MASK_RESET_RESF_PRESF0              (0x00000001UL)  /* Power on reset */

/***********/
/* Protect */
/***********/
/* Address */
#define STARTUP_REG_MSRKCPROT                       (0xFF981710UL)
#define STARTUP_REG_ECCKCPROT                       (0xFFFB2800UL)
/* Set value */
#define STARTUP_VAL_KCPROT_ENABLE                   (0xA5A5A501UL)  /* Enable */
#define STARTUP_VAL_KCPROT_DISABLE                  (0xA5A5A500UL)  /* Disable */

/******************/
/* ECC(CodeFlash) */
/******************/
/* Address */
#define STARTUP_REG_ECCCNT_CFP_PE0CL0_BASE          (0xFFC48000UL)
#define STARTUP_REG_ECCCNT_CFP_PE0CL0_CFPECCCTL     (STARTUP_REG_ECCCNT_CFP_PE0CL0_BASE + 0x00UL)
#define STARTUP_REG_ECCCNT_CFCCL0_BASE              (0xFFC48800UL)
#define STARTUP_REG_ECCCNT_CFCCL0_CFCECCCTL         (STARTUP_REG_ECCCNT_CFCCL0_BASE + 0x00UL)
#define STARTUP_REG_ECCCNT_CFCCL1_BASE              (0xFFC48880UL)                              /* For U2A16 only */
#define STARTUP_REG_ECCCNT_CFCCL1_CFCECCCTL         (STARTUP_REG_ECCCNT_CFCCL1_BASE + 0x00UL)   /* For U2A16 only */
#define STARTUP_REG_MECCCAP_CFL_BASE                (0xFFC52400UL)
#define STARTUP_REG_MECCCAP_CFL_CF_ERRINT           (STARTUP_REG_MECCCAP_CFL_BASE + 0x00UL)
#define STARTUP_REG_MECCCAP_CFL_CF_SSTCLR           (STARTUP_REG_MECCCAP_CFL_BASE + 0x10UL)
#define STARTUP_REG_MECCCAP_CFL_CF_DSTCLR           (STARTUP_REG_MECCCAP_CFL_BASE + 0x14UL)
#define STARTUP_REG_MECCCAP_CFL_CF_OVFCLR           (STARTUP_REG_MECCCAP_CFL_BASE + 0x18UL)
#define STARTUP_REG_MECCCAP_CFL_CF_SERSTR           (STARTUP_REG_MECCCAP_CFL_BASE + 0x20UL)
#define STARTUP_REG_MECCCAP_CFL_CF_DERSTR           (STARTUP_REG_MECCCAP_CFL_BASE + 0x24UL)
#define STARTUP_REG_MECCCAP_CFL_CF_00SEADR          (STARTUP_REG_MECCCAP_CFL_BASE + 0x70UL)
#define STARTUP_REG_MECCCAP_CFL_CF_00DEADR          (STARTUP_REG_MECCCAP_CFL_BASE + 0xF0UL)
/* Set value */
#define STARTUP_VAL_PE0CL0_CFPECCCTL_OFF            (0x00000003UL)  /* ECC disable */
#define STARTUP_VAL_PE0CL0_CFPECCCTL_ON             (0x00000002UL)  /* ECC enable, 1-bit error correction disable */
#define STARTUP_VAL_PE0CL0_CFPECCCTL_RESET          (0x00000000UL)  /* ECC enable, 1-bit error correction enable(= Value after reset) */
#define STARTUP_VAL_CFCCL0_CFCECCCTL_OFF            (0x00000007UL)  /* ECC disable */
#define STARTUP_VAL_CFCCL0_CFCECCCTL_ON             (0x00000002UL)  /* ECC enable, 1-bit error correction disable, address parity enable */
#define STARTUP_VAL_CFCCL0_CFCECCCTL_RESET          (0x00000000UL)  /* ECC enable, 1-bit error correction enable,  address parity enable(= Value after reset) */
#define STARTUP_VAL_CFCCL1_CFCECCCTL_OFF            (STARTUP_VAL_CFCCL0_CFCECCCTL_OFF)       /* For U2A16 only */
#define STARTUP_VAL_CFCCL1_CFCECCCTL_ON             (STARTUP_VAL_CFCCL0_CFCECCCTL_ON)        /* For U2A16 only */
#define STARTUP_VAL_CFCCL1_CFCECCCTL_RESET          (STARTUP_VAL_CFCCL0_CFCECCCTL_RESET)     /* For U2A16 only */
#define STARTUP_VAL_CF_ERRINT_OFF                   (0x00000000UL)  /* Error report disable */
#define STARTUP_VAL_CF_ERRINT_ON                    (0x00000087UL)  /* Error report enable(= Value after reset) */
#define STARTUP_VAL_CF_SSTCLR                       (0x0000000FUL)  /* All clear */
#define STARTUP_VAL_CF_DSTCLR                       (0x00000001UL)  /* All clear */
#define STARTUP_VAL_CF_OVFCLR                       (0x00000003UL)  /* All clear */
/* Mask */
#define STARTUP_MASK_CF_SERSTR                      (0x0000000FUL)  /* 1-bit error has occurred */
#define STARTUP_MASK_CF_DERSTR                      (0x00000006UL)  /* Address parity error and/or 2-bit error has occurred */
/* Macro */
#define STARTUP_GET_CF_ECCADR(eadr)                 (((eadr) & 0x03FFFFFCUL) << 2UL)        /* Get address from EADR */
#define STARTUP_CF_SEADR_STEP                       (4UL)           /* nSEADR register address step value */

/*****************/
/* ECC(LocalRAM) */
/*****************/
/* Address */
#define STARTUP_REG_ECCCNT_LR_PE0CL0_BASE           (0xFFC49800UL)
#define STARTUP_REG_ECCCNT_LR_PE0CL0_LRECCCTL       (STARTUP_REG_ECCCNT_LR_PE0CL0_BASE + 0x00UL)
#define STARTUP_REG_ECCCNT_LR_PE0CL0_LRECCTSTCTL    (STARTUP_REG_ECCCNT_LR_PE0CL0_BASE + 0x10UL)
#define STARTUP_REG_MECCCAP_LR_PE0CL0_BASE          (0xFFC50000UL)
#define STARTUP_REG_MECCCAP_LR_PE0CL0_LR0_ERRINT    (STARTUP_REG_MECCCAP_LR_PE0CL0_BASE + 0x00UL)
#define STARTUP_REG_MECCCAP_LR_PE0CL0_LR0_SSTCLR    (STARTUP_REG_MECCCAP_LR_PE0CL0_BASE + 0x10UL)
#define STARTUP_REG_MECCCAP_LR_PE0CL0_LR0_DSTCLR    (STARTUP_REG_MECCCAP_LR_PE0CL0_BASE + 0x14UL)
#define STARTUP_REG_MECCCAP_LR_PE0CL0_LR0_OVFCLR    (STARTUP_REG_MECCCAP_LR_PE0CL0_BASE + 0x18UL)
#define STARTUP_REG_MECCCAP_LR_PE0CL0_LR0_SERSTR    (STARTUP_REG_MECCCAP_LR_PE0CL0_BASE + 0x20UL)
#define STARTUP_REG_MECCCAP_LR_PE0CL0_LR0_DERSTR    (STARTUP_REG_MECCCAP_LR_PE0CL0_BASE + 0x24UL)
/* Set value */
#define STARTUP_VAL_PE0CL0_LRECCCTL_OFF             (0x0000000BUL)  /* ECC disable */
#define STARTUP_VAL_PE0CL0_LRECCCTL_ON              (0x00000002UL)  /* ECC enable, 1-bit error correction disable, address feedback enable */
#define STARTUP_VAL_PE0CL0_LRECCCTL_RESET           (0x00000000UL)  /* ECC enable, 1-bit error correction enable,  address feedback enable(= Value after reset) */
#define STARTUP_VAL_PE0CL0_LRECCTSTCTL_OFF          (0x00000000UL)  /* Normal mode(= Value after reset) */
#define STARTUP_VAL_LR0_ERRINT_OFF                  (0x00000000UL)  /* Error report disable */
#define STARTUP_VAL_LR0_ERRINT_ON                   (0x0000008BUL)  /* Error report enable(= Value after reset) */
#define STARTUP_VAL_LR0_SSTCLR                      (0x000000FFUL)  /* All clear */
#define STARTUP_VAL_LR0_DSTCLR                      (0x00000001UL)  /* All clear */
#define STARTUP_VAL_LR0_OVFCLR                      (0x00000003UL)  /* All clear */
/* Mask */
#define STARTUP_MASK_LR0_SERSTR                     (0x000000FFUL)  /* 1-bit error has occurred */
#define STARTUP_MASK_LR0_DERSTR                     (0x0000000AUL)  /* Address feedback error and/or 2-bit error has occurred */

/*******************/
/* ECC(ClusterRAM) */
/*******************/
/* Address */
#define STARTUP_REG_ECCCNT_CRCCL0_BASE              (0xFFC49C00UL)
#define STARTUP_REG_ECCCNT_CRCCL0_CRCAFCTL          (STARTUP_REG_ECCCNT_CRCCL0_BASE + 0x00UL)
#define STARTUP_REG_ECCCNT_CRCCL0_CRCECCTSTCTL      (STARTUP_REG_ECCCNT_CRCCL0_BASE + 0x10UL)
#define STARTUP_REG_ECCCNT_CRCCL1_BASE              (0xFFC49C80UL)                              /* For U2A16 only */
#define STARTUP_REG_ECCCNT_CRCCL1_CRCAFCTL          (STARTUP_REG_ECCCNT_CRCCL1_BASE + 0x00UL)   /* For U2A16 only */
#define STARTUP_REG_ECCCNT_CRCCL1_CRCECCTSTCTL      (STARTUP_REG_ECCCNT_CRCCL1_BASE + 0x10UL)   /* For U2A16 only */
#define STARTUP_REG_ECCCNT_CRCCL2_BASE              (0xFFC49D00UL)                              /* For U2A8,16 */
#define STARTUP_REG_ECCCNT_CRCCL2_CRCAFCTL          (STARTUP_REG_ECCCNT_CRCCL2_BASE + 0x00UL)   /* For U2A8,16 */
#define STARTUP_REG_ECCCNT_CRCCL2_CRCECCTSTCTL      (STARTUP_REG_ECCCNT_CRCCL2_BASE + 0x10UL)   /* For U2A8,16 */
#define STARTUP_REG_ECCCNT_CRCCL3_BASE              (0xFFC49D80UL)
#define STARTUP_REG_ECCCNT_CRCCL3_CRCAFCTL          (STARTUP_REG_ECCCNT_CRCCL3_BASE + 0x00UL)
#define STARTUP_REG_ECCCNT_CRCCL3_CRCECCTSTCTL      (STARTUP_REG_ECCCNT_CRCCL3_BASE + 0x10UL)
#define STARTUP_REG_ECCCNT_CRA_BASE                 (0xFFC49E00UL)
#define STARTUP_REG_ECCCNT_CRA_CRAECCCTL            (STARTUP_REG_ECCCNT_CRA_BASE + 0x00UL)
#define STARTUP_REG_MECCCAP_CRAM_BASE               (0xFFC52000UL)
#define STARTUP_REG_MECCCAP_CRAM_CR_ERRINT          (STARTUP_REG_MECCCAP_CRAM_BASE + 0x00UL)
#define STARTUP_REG_MECCCAP_CRAM_CR_SSTCLR          (STARTUP_REG_MECCCAP_CRAM_BASE + 0x10UL)
#define STARTUP_REG_MECCCAP_CRAM_CR_DSTCLR          (STARTUP_REG_MECCCAP_CRAM_BASE + 0x14UL)
#define STARTUP_REG_MECCCAP_CRAM_CR_OVFCLR          (STARTUP_REG_MECCCAP_CRAM_BASE + 0x18UL)
#define STARTUP_REG_MECCCAP_CRAM_CR_SERSTR          (STARTUP_REG_MECCCAP_CRAM_BASE + 0x20UL)
#define STARTUP_REG_MECCCAP_CRAM_CR_DERSTR          (STARTUP_REG_MECCCAP_CRAM_BASE + 0x24UL)
/* Set value */
#define STARTUP_VAL_CRCCL0_CRCAFCTL_OFF             (0x00000008UL)  /* Address feedback disable */
#define STARTUP_VAL_CRCCL0_CRCAFCTL_ON              (0x00000000UL)  /* Address feedback enable(= Value after reset) */
#define STARTUP_VAL_CRCCL0_CRCECCTSTCTL_OFF         (0x00000000UL)  /* Normal mode(= Value after reset) */
#define STARTUP_VAL_CRCCL1_CRCAFCTL_OFF             (STARTUP_VAL_CRCCL0_CRCAFCTL_OFF)           /* For U2A16 only */
#define STARTUP_VAL_CRCCL1_CRCAFCTL_ON              (STARTUP_VAL_CRCCL0_CRCAFCTL_ON)            /* For U2A16 only */
#define STARTUP_VAL_CRCCL1_CRCECCTSTCTL_OFF         (STARTUP_VAL_CRCCL0_CRCECCTSTCTL_OFF)       /* For U2A16 only */
#define STARTUP_VAL_CRCCL2_CRCAFCTL_OFF             (STARTUP_VAL_CRCCL0_CRCAFCTL_OFF)           /* For U2A8,16 */
#define STARTUP_VAL_CRCCL2_CRCAFCTL_ON              (STARTUP_VAL_CRCCL0_CRCAFCTL_ON)            /* For U2A8,16 */
#define STARTUP_VAL_CRCCL2_CRCECCTSTCTL_OFF         (STARTUP_VAL_CRCCL0_CRCECCTSTCTL_OFF)       /* For U2A8,16 */
#define STARTUP_VAL_CRCCL3_CRCAFCTL_OFF             (STARTUP_VAL_CRCCL0_CRCAFCTL_OFF)
#define STARTUP_VAL_CRCCL3_CRCAFCTL_ON              (STARTUP_VAL_CRCCL0_CRCAFCTL_ON)
#define STARTUP_VAL_CRCCL3_CRCECCTSTCTL_OFF         (STARTUP_VAL_CRCCL0_CRCECCTSTCTL_OFF)
#define STARTUP_VAL_CRA_CRAECCCTL_OFF               (0x00000003UL)  /* ECC disable */
#define STARTUP_VAL_CRA_CRAECCCTL_ON                (0x00000002UL)  /* ECC enable, 1-bit error correction disable */
#define STARTUP_VAL_CRA_CRAECCCTL_RESET             (0x00000000UL)  /* ECC enable, 1-bit error correction enable(= Value after reset) */
#define STARTUP_VAL_CR_ERRINT_OFF                   (0x00000000UL)  /* Error report disable */
#define STARTUP_VAL_CR_ERRINT_ON                    (0x0000008BUL)  /* Error report enable(= Value after reset) */
#define STARTUP_VAL_CR_SSTCLR                       (0x000000FFUL)  /* All clear */
#define STARTUP_VAL_CR_DSTCLR                       (0x00000001UL)  /* All clear */
#define STARTUP_VAL_CR_OVFCLR                       (0x00000003UL)  /* All clear */
/* Mask */
#define STARTUP_MASK_CR_SERSTR                      (0x000000FFUL)  /* 1-bit error has occurred */
#define STARTUP_MASK_CR_DERSTR                      (0x0000000AUL)  /* Address feedback error and/or 2-bit error has occurred */

/**********************/
/* Standby Controller */
/**********************/
/* Address */
#define STARTUP_REG_MSR_RSCFD                       (0xFF981000UL)
#define STARTUP_REG_MSR_FLXA                        (0xFF981010UL)
#define STARTUP_REG_MSR_GTM                         (0xFF981020UL)
#define STARTUP_REG_MSR_ETNB                        (0xFF981030UL)
#define STARTUP_REG_MSR_RSENT                       (0xFF981040UL)
#define STARTUP_REG_MSR_MSPI                        (0xFF981050UL)
#define STARTUP_REG_MSR_RLIN3                       (0xFF981060UL)
#define STARTUP_REG_MSR_ADCJ_ISO                    (0xFF981070UL)
#define STARTUP_REG_MSR_CXPI                        (0xFF981080UL)
#define STARTUP_REG_MSR_MMCA                        (0xFF981090UL)
#define STARTUP_REG_MSR_ENCA                        (0xFF9810A0UL)
#define STARTUP_REG_MSR_PSI5                        (0xFF9810B0UL)
#define STARTUP_REG_MSR_PSI5S                       (0xFF9810C0UL)
#define STARTUP_REG_MSR_PWMD                        (0xFF9810D0UL)
#define STARTUP_REG_MSR_RHSIF                       (0xFF9810E0UL)
#define STARTUP_REG_MSR_RIIC                        (0xFF9810F0UL)
#define STARTUP_REG_MSR_SCI3                        (0xFF981100UL)
#define STARTUP_REG_MSR_TAPA                        (0xFF981120UL)
#define STARTUP_REG_MSR_TAUD                        (0xFF981130UL)
#define STARTUP_REG_MSR_TAUJ_ISO                    (0xFF981140UL)
#define STARTUP_REG_MSR_TPBA                        (0xFF981150UL)
#define STARTUP_REG_MSR_TSG3                        (0xFF981160UL)
#define STARTUP_REG_MSR_OSTM                        (0xFF981180UL)
#define STARTUP_REG_MSR_ADCJ_AWO                    (0xFF988E00UL)
#define STARTUP_REG_MSR_RTCA                        (0xFF988E10UL)
#define STARTUP_REG_MSR_TAUJ_AWO                    (0xFF988E20UL)
#define STARTUP_REG_MSR_WDTB_AWO                    (0xFF988E30UL)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/

#endif /* STARTUP_REG_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2021/03/09 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

