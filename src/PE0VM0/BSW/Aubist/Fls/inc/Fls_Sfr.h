/* Fls_Sfr_h_Revision(v1_0_2)                                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS Corporation                                             */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Fls/Sfr/HEADER                                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef FLS_SFR_H
#define FLS_SFR_H

#include <Fls.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define FLS_DRV_U4_FCU_BASE_0               (0xFFA10000uL)                      /* FCU0 base address */
#if ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A8 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A16 )
#define FLS_DRV_U4_FCU_BASE_1               (0xFFA14000uL)                      /* FCU1 base address */
#endif

#define FLS_DRV_U4_REGADD_FASTAT_0          (FLS_DRV_U4_FCU_BASE_0 + 0x0010uL)  /* Flash Access Status Register( for data area 0) */
#define FLS_DRV_U4_REGADD_FAEINT_0          (FLS_DRV_U4_FCU_BASE_0 + 0x0014uL)  /* Flash Access Error Interrupt Enable Register( for data area 0) */
#define FLS_DRV_U4_REGADD_FSADR_0           (FLS_DRV_U4_FCU_BASE_0 + 0x0030uL)  /* FACI Command Start Address Register( for data area 0) */
#define FLS_DRV_U4_REGADD_FEADR_0           (FLS_DRV_U4_FCU_BASE_0 + 0x0034uL)  /* FACI Command End Address Register( for data area 0)*/

#define FLS_DRV_U4_REGADD_FSTATR_0          (FLS_DRV_U4_FCU_BASE_0 + 0x0080uL)  /* Flash Status Register ( for data area 0)*/
#define FLS_DRV_U4_REGADD_FENTRYR_0         (FLS_DRV_U4_FCU_BASE_0 + 0x0084uL)  /* Flash P/E Mode Entry Register */
#define FLS_DRV_U4_REGADD_FSUINITR_0        (FLS_DRV_U4_FCU_BASE_0 + 0x008CuL)  /* Flash Sequencer Set-Up Initialize Register */

#define FLS_DRV_U4_REGADD_FBCCNT_0          (FLS_DRV_U4_FCU_BASE_0 + 0x00D0uL)  /* Data Flash Blank Check Control RegisterData Flash */
#if ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A8 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A16 )
#define FLS_DRV_U4_REGADD_FCPSR_0           (FLS_DRV_U4_FCU_BASE_0 + 0x00E0uL)  /* Flash Sequencer Process Switch Register */
#endif
#define FLS_DRV_U4_REGADD_FBCSTAT_0         (FLS_DRV_U4_FCU_BASE_0 + 0x00D4uL)  /* Data Flash Blank Check Status Register */

#define FLS_DRV_U4_REGADD_FECCTMD_0         (FLS_DRV_U4_FCU_BASE_0 + 0x0104uL)  /* Flash ECC Test Mode Register */

#if ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A8 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A16 )
#define FLS_DRV_U4_REGADD_FASTAT_1          (FLS_DRV_U4_FCU_BASE_1 + 0x0010uL)  /* Flash Access Status Register( for data area 1) */
#define FLS_DRV_U4_REGADD_FAEINT_1          (FLS_DRV_U4_FCU_BASE_1 + 0x0014uL)  /* Flash Access Error Interrupt Enable Register( for data area 1) */
#define FLS_DRV_U4_REGADD_FSADR_1           (FLS_DRV_U4_FCU_BASE_1 + 0x0030uL)  /* FACI Command Start Address Register( for data area 1) */
#define FLS_DRV_U4_REGADD_FEADR_1           (FLS_DRV_U4_FCU_BASE_1 + 0x0034uL)  /* FACI Command End Address Register( for data area 1) */

#define FLS_DRV_U4_REGADD_FSTATR_1          (FLS_DRV_U4_FCU_BASE_1 + 0x0080uL)  /* Flash Status Register( for data area 1) */
#define FLS_DRV_U4_REGADD_FENTRYR_1         (FLS_DRV_U4_FCU_BASE_1 + 0x0084uL)  /* Flash P/E Mode Entry Register( for data area 1) */
#define FLS_DRV_U4_REGADD_FSUINITR_1        (FLS_DRV_U4_FCU_BASE_1 + 0x008CuL)  /* Flash Sequencer Set-Up Initialize Register( for data area 1) */

#define FLS_DRV_U4_REGADD_FBCCNT_1          (FLS_DRV_U4_FCU_BASE_1 + 0x00D0uL)  /* Data Flash Blank Check Control RegisterData Flash( for data area 1) */
#define FLS_DRV_U4_REGADD_FCPSR_1           (FLS_DRV_U4_FCU_BASE_1 + 0x00E0uL)  /* Flash Sequencer Process Switch Register( for data area 1) */
#define FLS_DRV_U4_REGADD_FBCSTAT_1         (FLS_DRV_U4_FCU_BASE_1 + 0x00D4uL)  /* Data Flash Blank Check Status Register( for data area 1) */

#define FLS_DRV_U4_REGADD_FECCTMD_1         (FLS_DRV_U4_FCU_BASE_1 + 0x0104uL)  /* Flash ECC Test Mode Register( for data area 1) */
#endif

#define FLS_DRV_U4_DECC_BASE                (0xFFC62C00uL)                      /* Data Flash ECC Register base address(U2A8 base) */

#if ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A8 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A16 )
#define FLS_DRV_U4_REGADD_DFERSTR           (FLS_DRV_U4_DECC_BASE + 0x0004uL)   /* Data flash error status register */
#define FLS_DRV_U4_REGADD_DFERSTC           (FLS_DRV_U4_DECC_BASE + 0x0008uL)   /* Data flash error status clear register */
#elif ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2B6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2B10 )
#define FLS_DRV_U4_REGADD_DFSERSTR          (FLS_DRV_U4_DECC_BASE + 0x0004uL)   /* Data flash 1-bit error status register */
#define FLS_DRV_U4_REGADD_DFDERSTR          (FLS_DRV_U4_DECC_BASE + 0x0008uL)   /* Data flash 2-bit error status register */
#define FLS_DRV_U4_REGADD_DFSERSTC          (FLS_DRV_U4_DECC_BASE + 0x000CuL)   /* Data flash 1-bit error status clear register */
#define FLS_DRV_U4_REGADD_DFDERSTC          (FLS_DRV_U4_DECC_BASE + 0x0010uL)   /* Data flash 2-bit error status clear register */
#endif

#define FLS_DRV_U4_FHVE_BASE                (0xFF984800uL)                      /* FHVE base address(U2A8) */

#define FLS_DRV_U4_REGADD_FHVE3FP0          (FLS_DRV_U4_FHVE_BASE + 0x0000uL)   /* FHVE3 Control Register ( for data area 0) */
#define FLS_DRV_U4_REGADD_FHVE15FP0         (FLS_DRV_U4_FHVE_BASE + 0x0004uL)   /* FHVE15 Control Register( for data area 0) */

#if ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A8 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A16 )
#define FLS_DRV_U4_REGADD_FHVE3FP1          (FLS_DRV_U4_FHVE_BASE + 0x0010uL)   /* FHVE3 Control Register (for data area 1) */
#define FLS_DRV_U4_REGADD_FHVE15FP1         (FLS_DRV_U4_FHVE_BASE + 0x0014uL)   /* FHVE15 Control Register (for data area 1) */
#endif

#if ( FLS_CDD_AUTH_DFID_API == STD_ON )
#define FLS_DRV_U4_REGADD_IDCTRL_BASE       (0xFFA08000uL)
#define FLS_DRV_U4_REGADD_DFIDIN0           (FLS_DRV_U4_REGADD_IDCTRL_BASE + 0x0020uL )
#define FLS_DRV_U4_REGADD_DFIDIN1           (FLS_DRV_U4_REGADD_IDCTRL_BASE + 0x0024uL )
#define FLS_DRV_U4_REGADD_DFIDIN2           (FLS_DRV_U4_REGADD_IDCTRL_BASE + 0x0028uL )
#define FLS_DRV_U4_REGADD_DFIDIN3           (FLS_DRV_U4_REGADD_IDCTRL_BASE + 0x002CuL )
#define FLS_DRV_U4_REGADD_DFIDIN4           (FLS_DRV_U4_REGADD_IDCTRL_BASE + 0x0030uL )
#define FLS_DRV_U4_REGADD_DFIDIN5           (FLS_DRV_U4_REGADD_IDCTRL_BASE + 0x0034uL )
#define FLS_DRV_U4_REGADD_DFIDIN6           (FLS_DRV_U4_REGADD_IDCTRL_BASE + 0x0038uL )
#define FLS_DRV_U4_REGADD_DFIDIN7           (FLS_DRV_U4_REGADD_IDCTRL_BASE + 0x003CuL )
#define FLS_DRV_U4_REGADD_IDST              (FLS_DRV_U4_REGADD_IDCTRL_BASE + 0x01FCuL)
#endif /* FLS_CDD_AUTH_DFID_API == STD_ON */

#define FLS_DRV_U4_REGADD_BLANKOFFSET       (0x001FFFFDuL)                  /* address offset of Blank Check Area for data flash memory */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif       /* FLS_SFR_H */


/****************************************************************************/
/* History                                                                  */
/* Version :Date                                                            */
/* [Number] :[Date]                                                         */
/****************************************************************************/

/**** End of File ***********************************************************/
