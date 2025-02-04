/* Shutdown_Reg_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Shutdown/Reg/HEADER                                         */
/******************************************************************************/
#ifndef SHUTDOWN_REG_H
#define SHUTDOWN_REG_H

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
#define SHUTDOWN_VAL_EBASE_RINT_DV_ON               (0x00000003UL)  /* Vector address shrink and direct vector method */
/* PLMR */
#define SHUTDOWN_VAL_PLMR_RESET                     (0x00000010UL)  /* Value after reset */

/*********/
/* Reset */
/*********/
/* Address */
#define SHUTDOWN_REG_RESET_SWSRESA                  (0xFF98840CUL)
/* Set value */
#define SHUTDOWN_VAL_RESET_SWSRESA_ON               (0x00000001UL)  /* Generate a System Reset 2 */

/***********/
/* Protect */
/***********/
/* Address */
#define SHUTDOWN_REG_RESKCPROT0                     (0xFF980F00UL)
#define SHUTDOWN_REG_ECCKCPROT                      (0xFFFB2800UL)
/* Set value */
#define SHUTDOWN_VAL_KCPROT_ENABLE                  (0xA5A5A501UL)  /* Enable */
#define SHUTDOWN_VAL_KCPROT_DISABLE                 (0xA5A5A500UL)  /* Disable */

/******************/
/* ECC(CodeFlash) */
/******************/
/* Address */
#define SHUTDOWN_REG_MECCCAP_CFL_BASE               (0xFFC52400UL)
#define SHUTDOWN_REG_MECCCAP_CFL_CF_ERRINT          (SHUTDOWN_REG_MECCCAP_CFL_BASE + 0x00UL)
/* Set value */
#define SHUTDOWN_VAL_CF_ERRINT_ON                   (0x00000087UL)  /* Error report enable(= Value after reset) */

/*****************/
/* ECC(LocalRAM) */
/*****************/
/* Address */
#define SHUTDOWN_REG_MECCCAP_LR_PE0CL0_BASE         (0xFFC50000UL)
#define SHUTDOWN_REG_MECCCAP_LR_PE0CL0_LR0_ERRINT   (SHUTDOWN_REG_MECCCAP_LR_PE0CL0_BASE + 0x00UL)
/* Set value */
#define SHUTDOWN_VAL_LR0_ERRINT_ON                  (0x0000008BUL)  /* Error report enable(= Value after reset) */

/*******************/
/* ECC(ClusterRAM) */
/*******************/
/* Address */
#define SHUTDOWN_REG_MECCCAP_CRAM_BASE              (0xFFC52000UL)
#define SHUTDOWN_REG_MECCCAP_CRAM_CR_ERRINT         (SHUTDOWN_REG_MECCCAP_CRAM_BASE + 0x00UL)
/* Set value */
#define SHUTDOWN_VAL_CR_ERRINT_ON                   (0x0000008BUL)  /* Error report enable(= Value after reset) */


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


#endif /* SHUTDOWN_REG_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2021/03/09 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

