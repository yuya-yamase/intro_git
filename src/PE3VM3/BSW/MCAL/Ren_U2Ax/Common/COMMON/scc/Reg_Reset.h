/* Reg_RESET-r04-307 */
/************************************************************************************************/
/*																								*/
/*		Standby Controller Register definition													*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

#ifndef	REG_RESET_H
#define	REG_RESET_H

/*==============================================================================================*/
/* include files																				*/
/*==============================================================================================*/
#include	"Std_Types.h"
#include	"Mcal_SpalCmn.h"

/*==============================================================================================*/
/*	register type definition																	*/
/*==============================================================================================*/
typedef	struct {

#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
	uint32	u4STAC_DPRAM;
	uint8	u1Dummy1[12];
	uint32	u4STAC_DTSRAM;
	uint8	u1Dummy2[28];
	uint32	u4STAC_GTM;
	uint8	u1Dummy3[28];
	uint32	u4STAC_MSPI;
	uint8	u1Dummy4[12];
	uint32	u4STAC_MMCA;
	uint8	u1Dummy5[156];
	uint32	u4SWMRESA_RSCFD;
	uint32	u4SWMRESS_RSCFD;
	uint8	u1Dummy6[8];
	uint32	u4SWMRESA_FLXA;
	uint32	u4SWMRESS_FLXA;
	uint8	u1Dummy7[8];
	uint32	u4SWMRESA_GTM;
	uint32	u4SWMRESS_GTM;
	uint8	u1Dummy8[8];
	uint32	u4SWMRESA_ETNB;
	uint32	u4SWMRESS_ETNB;
	uint8	u1Dummy9[8];
	uint32	u4SWMRESA_RSENT;
	uint32	u4SWMRESS_RSENT;
	uint8	u1Dummy10[8];
	uint32	u4SWMRESA_MSPI;
	uint32	u4SWMRESS_MSPI;
	uint8	u1Dummy11[8];
	uint32	u4SWMRESA_RLIN3;
	uint32	u4SWMRESS_RLIN3;
	uint8	u1Dummy12[8];
	uint32	u4SWMRESA_ADCJ_ISO;
	uint32	u4SWMRESS_ADCJ_ISO;
	uint8	u1Dummy13[8];
	uint32	u4SWMRESA_CXPI;
	uint32	u4SWMRESS_CXPI;
	uint8	u1Dummy14[8];
	uint32	u4SWMRESA_MMCA;
	uint32	u4SWMRESS_MMCA;
	uint8	u1Dummy15[8];
	uint32	u4SWMRESA_ENCA;
	uint32	u4SWMRESS_ENCA;
	uint8	u1Dummy16[8];
	uint32	u4SWMRESA_PSI5;
	uint32	u4SWMRESS_PSI5;
	uint8	u1Dummy17[8];
	uint32	u4SWMRESA_PSI5S;
	uint32	u4SWMRESS_PSI5S;
	uint8	u1Dummy18[8];
	uint32	u4SWMRESA_PWMD;
	uint32	u4SWMRESS_PWMD;
	uint8	u1Dummy19[8];
	uint32	u4SWMRESA_RHSIF;
	uint32	u4SWMRESS_RHSIF;
	uint8	u1Dummy20[8];
	uint32	u4SWMRESA_RIIC;
	uint32	u4SWMRESS_RIIC;
	uint8	u1Dummy21[8];
	uint32	u4SWMRESA_SCI3;
	uint32	u4SWMRESS_SCI3;
	uint8	u1Dummy22[8];
	uint32	u4SWMRESA_SFMA;
	uint32	u4SWMRESS_SFMA;
	uint8	u1Dummy23[8];
	uint32	u4SWMRESA_TAPA;
	uint32	u4SWMRESS_TAPA;
	uint8	u1Dummy24[8];
	uint32	u4SWMRESA_TAUD;
	uint32	u4SWMRESS_TAUD;
	uint8	u1Dummy25[8];
	uint32	u4SWMRESA_TAUJ_ISO;
	uint32	u4SWMRESS_TAUJ_ISO;
	uint8	u1Dummy26[8];
	uint32	u4SWMRESA_TPBA;
	uint32	u4SWMRESS_TPBA;
	uint8	u1Dummy27[8];
	uint32	u4SWMRESA_TSG3;
	uint32	u4SWMRESS_TSG3;
	uint8	u1Dummy28[24];
	uint32	u4SWMRESA_OSTM;
	uint32	u4SWMRESS_OSTM;
	uint8	u1Dummy29[376];
	uint32	u4RESFC;
	uint8	u1Dummy30[12];
	uint32	u4RESFDDC;
	uint8	u1Dummy31[748];
	uint32	u4RESKCPROT0;

#elif ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
	uint32	u4STAC_DPRAM;
	uint8	u1Dummy1[12];
	uint32	u4STAC_DTSRAM;
	uint8	u1Dummy2[28];
	uint32	u4STAC_GTM;
	uint8	u1Dummy3[12];
	uint32	u4STAC_ETN;
	uint8	u1Dummy4[12];
	uint32	u4STAC_MSPI;
	uint8	u1Dummy5[12];
	uint32	u4STAC_MMCA;
	uint8	u1Dummy6[12];
	uint32	u4STAC_DFE;
	uint8	u1Dummy7[12];
	uint32	u4STAC_EMU3;
	uint8	u1Dummy8[12];
	uint32	u4STAC_DFP;
	uint8	u1Dummy9[108];
	uint32	u4SWMRESA_RSCFD;
	uint32	u4SWMRESS_RSCFD;
	uint8	u1Dummy10[8];
	uint32	u4SWMRESA_FLXA;
	uint32	u4SWMRESS_FLXA;
	uint8	u1Dummy11[8];
	uint32	u4SWMRESA_GTM;
	uint32	u4SWMRESS_GTM;
	uint8	u1Dummy12[8];
	uint32	u4SWMRESA_ETN;
	uint32	u4SWMRESS_ETN;
	uint8	u1Dummy13[8];
	uint32	u4SWMRESA_RSENT;
	uint32	u4SWMRESS_RSENT;
	uint8	u1Dummy14[8];
	uint32	u4SWMRESA_MSPI;
	uint32	u4SWMRESS_MSPI;
	uint8	u1Dummy15[8];
	uint32	u4SWMRESA_RLIN3;
	uint32	u4SWMRESS_RLIN3;
	uint8	u1Dummy16[8];
	uint32	u4SWMRESA_ADCK_ISO;
	uint32	u4SWMRESS_ADCK_ISO;
	uint8	u1Dummy17[24];
	uint32	u4SWMRESA_MMCA;
	uint32	u4SWMRESS_MMCA;
	uint8	u1Dummy18[8];
	uint32	u4SWMRESA_ENCA;
	uint32	u4SWMRESS_ENCA;
	uint8	u1Dummy19[8];
	uint32	u4SWMRESA_PSI5;
	uint32	u4SWMRESS_PSI5;
	uint8	u1Dummy20[8];
	uint32	u4SWMRESA_PSI5S;
	uint32	u4SWMRESS_PSI5S;
	uint8	u1Dummy21[24];
	uint32	u4SWMRESA_RHSIF;
	uint32	u4SWMRESS_RHSIF;
	uint8	u1Dummy22[8];
	uint32	u4SWMRESA_RIIC;
	uint32	u4SWMRESS_RIIC;
	uint8	u1Dummy23[24];
	uint32	u4SWMRESA_SFMA;
	uint32	u4SWMRESS_SFMA;
	uint8	u1Dummy24[8];
	uint32	u4SWMRESA_TAPA;
	uint32	u4SWMRESS_TAPA;
	uint8	u1Dummy25[8];
	uint32	u4SWMRESA_TAUD;
	uint32	u4SWMRESS_TAUD;
	uint8	u1Dummy26[24];
	uint32	u4SWMRESA_TPBA;
	uint32	u4SWMRESS_TPBA;
	uint8	u1Dummy27[8];
	uint32	u4SWMRESA_TSG3;
	uint32	u4SWMRESS_TSG3;
	uint8	u1Dummy28[24];
	uint32	u4SWMRESA_OSTM;
	uint32	u4SWMRESS_OSTM;
	uint8	u1Dummy29[40];
	uint32	u4SWMRESA_DSADC_CADC;
	uint32	u4SWMRESS_DSADC_CADC;
	uint8	u1Dummy30[24];
	uint32	u4SWMRESA_RHSB;
	uint32	u4SWMRESS_RHSB;
	uint8	u1Dummy31[8];
	uint32	u4SWMRESA_ATU;
	uint32	u4SWMRESS_ATU;
	uint8	u1Dummy32[8];
	uint32	u4SWMRESA_EMU;
	uint32	u4SWMRESS_EMU;
	uint8	u1Dummy33[8];
	uint32	u4SWMRESA_PE;
	uint32	u4SWMRESS_PE;
	uint8	u1Dummy34[8];
	uint32	u4SWMRESA_FCOMP;
	uint32	u4SWMRESS_FCOMP;
	uint8	u1Dummy35[8];
	uint32	u4SWMRESA_RDC;
	uint32	u4SWMRESS_RDC;
	uint8	u1Dummy36[8];
	uint32	u4SWMRESA_DFP;
	uint32	u4SWMRESS_DFP;
	uint8	u1Dummy37[8];
	uint32	u4SWMRESA_DFE;
	uint32	u4SWMRESS_DFE;
	uint8	u1Dummy38[8];
	uint32	u4SWMRESA_WDTB_ISO;
	uint32	u4SWMRESS_WDTB_ISO;
	uint8	u1Dummy39[24];
	uint32	u4SWMRESA_HRPWM;
	uint32	u4SWMRESS_HRPWM;
	uint8	u1Dummy40[88];
	uint32	u4SWMRESA_DSMIF;
	uint32	u4SWMRESS_DSMIF;
	uint8	u1Dummy41[40];
	uint32	u4RESFC;
	uint8	u1Dummy42[12];
	uint32	u4RESFDDC;
	uint8	u1Dummy43[748];
	uint32	u4RESKCPROT0;

#else	/* MCAL_SPAL_TARGET == MCAL_TARGET_RCARS4_G4MH */
	uint8	u1Dummy1[80];
	uint32	u4STAC_MSPI;
	uint8	u1Dummy2[172];
	uint32	u4SWMRESA_RSCFD;
	uint32	u4SWMRESS_RSCFD;
	uint8	u1Dummy3[8];
	uint32	u4SWMRESA_FLXA;
	uint32	u4SWMRESS_FLXA;
	uint8	u1Dummy4[24];
	uint32	u4SWMRESA_ETNB;
	uint32	u4SWMRESS_ETNB;
	uint8	u1Dummy5[8];
	uint32	u4SWMRESA_RSENT;
	uint32	u4SWMRESS_RSENT;
	uint8	u1Dummy6[8];
	uint32	u4SWMRESA_MSPI;
	uint32	u4SWMRESS_MSPI;
	uint8	u1Dummy7[8];
	uint32	u4SWMRESA_RLIN3;
	uint32	u4SWMRESS_RLIN3;
	uint8	u1Dummy8[136];
	uint32	u4SWMRESA_RIIC;
	uint32	u4SWMRESS_RIIC;
	uint8	u1Dummy9[56];
	uint32	u4SWMRESA_TAUD;
	uint32	u4SWMRESS_TAUD;
	uint8	u1Dummy10[8];
	uint32	u4SWMRESA_TAUJ_ISO;
	uint32	u4SWMRESS_TAUJ_ISO;
	uint8	u1Dummy11[56];
	uint32	u4SWMRESA_OSTM;
	uint32	u4SWMRESS_OSTM;
	uint8	u1Dummy12[376];
	uint32	u4RESFC;
	uint8	u1Dummy13[12];
	uint32	u4RESFDDC;
	uint8	u1Dummy14[748];
	uint32	u4RESKCPROT0;

#endif

} Reg_Reset_IsoType;

typedef	struct {

#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
	uint32	u4SWSRESA;
	uint32	u4SWARESA;
	uint32	u4RESC;
	uint8	u1Dummy1[232];
	uint32	u4RESF;
	uint8	u1Dummy2[12];
	uint32	u4RESFDD;
	uint8	u1Dummy3[748];
	uint32	u4SWMRESA_ADCK_AWO;
	uint32	u4SWMRESS_ADCK_AWO;
	uint8	u1Dummy4[24];
	uint32	u4SWMRESA_TAUJ_AWO;
	uint32	u4SWMRESS_TAUJ_AWO;
	uint8	u1Dummy5[8];
	uint32	u4SWMRESA_WDTB_AWO;
	uint32	u4SWMRESS_WDTB_AWO;

#elif ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
	uint32	u4SWSRESA;
	uint32	u4SWARESA;
	uint32	u4RESC;
	uint8	u1Dummy1[232];
	uint32	u4RESF;
	uint8	u1Dummy2[12];
	uint32	u4RESFDD;
	uint8	u1Dummy3[748];
	uint32	u4SWMRESA_ADCK_AWO;
	uint32	u4SWMRESS_ADCK_AWO;
	uint8	u1Dummy4[24];
	uint32	u4SWMRESA_TAUJ_AWO;
	uint32	u4SWMRESS_TAUJ_AWO;
	uint8	u1Dummy5[8];
	uint32	u4SWMRESA_WDTB_AWO;
	uint32	u4SWMRESS_WDTB_AWO;

#else	/* MCAL_SPAL_TARGET == MCAL_TARGET_RCARS4_G4MH */
	uint32	u4SWSRESA;
	uint8	u1Dummy1[240];
	uint32	u4RESF;
	uint8	u1Dummy2[12];
	uint32	u4RESFDD;

#endif

} Reg_Reset_AwoType;


/*==============================================================================================*/
/*	struct address definition																	*/
/*==============================================================================================*/
#define	REG_RESET_ISO	(*(volatile Reg_Reset_IsoType *)(0xFF980800U))	/* Reset Controller Registers for ISO area */
#define	REG_RESET_AWO	(*(volatile Reg_Reset_AwoType *)(0xFF98840CU))	/* Reset Controller Registers for AWO area */


/*----------------------------------------------------------------------------------------------*/
/*	register setting definition																	*/
/*----------------------------------------------------------------------------------------------*/
#define	MCU_SWMRESS_NO_RESET			( (uint32)0x00000000U )	/* Reset execution is not being processed */

#define	MCU_SWMRESS_GTM_RESET			( (uint32)0x00000000U )	/* Confirm release of GTM module standby mode by Clock Monitor */
#define	MCU_SWMRESS_EMU_RESET			( (uint32)0x00000000U )	/* Confirm release of EMU module standby mode by Clock Monitor */

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
#define	MCU_CLEAR_RESET_FACTOR			( (uint32)0x0000F5DDU )	/* Clear reset factor register */
#elif	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
#define	MCU_CLEAR_RESET_FACTOR			( (uint32)0x0000F5DFU )	/* Clear reset factor register */
#elif	( MCAL_SPAL_TARGET == MCAL_TARGET_RCARS4_G4MH )
#define	MCU_CLEAR_RESET_FACTOR			( (uint32)0x0700B0DDU )	/* Clear reset factor register */
#endif	/* MCAL_SPAL_TARGET */

#define	MCU_GENERATE_RESET				( (uint32)0x00000001U )	/* Generate a software reset */

#define	MCU_RESET_PROTECT_DISABLE		( (uint32)0xA5A5A500U )	/* Disables write access of protected registers */
#define	MCU_RESET_PROTECT_ENABLE		( (uint32)0xA5A5A501U )	/* Enables write access of protected registers */

#define	MCU_RESF_POWER_ON_RESET				( BIT0 )
#define	MCU_RESF_POWER_OFF_STANDBY_RESET	( BIT1 )
#define	MCU_RESF_EXTERNAL_RESET				( BIT2 )
#define	MCU_RESF_PRIMARY_VMON_RESET			( BIT3 )
#define	MCU_RESF_SOFTWARE_SYSTEM_RESET		( BIT4 )
#define	MCU_RESF_ECM_SYSTEM_RESET_2			( BIT6 )
#define	MCU_RESF_WDTBA_RESET				( BIT7 )
#define	MCU_RESF_SOFTWARE_APPLICATION_RESET	( BIT8 )
#define	MCU_RESF_ECM_APPLICATION_RESET		( BIT10 )
#define	MCU_RESF_HW_BIST0_EXECUTION_RESET	( BIT12 )
#define	MCU_RESF_HW_BIST1_EXECUTION_RESET	( BIT13 )
#define	MCU_RESF_HW_BIST2_EXECUTION_RESET	( BIT14 )
#define	MCU_RESF_DEEPSTOP_RESET				( BIT15 )
#define	MCU_RESF_ICUMHA_SOFT_SYS_RESET		( BIT16 )
#define	MCU_RESF_ICUMHA_SOFT_APP_RESET		( BIT17 )
#define	MCU_RESF_ICUMHB_SOFT_SYS_RESET		( BIT16 )
#define	MCU_RESF_ICUMHB_SOFT_APP_RESET		( BIT17 )
#define	MCU_RESF_SOFT_POWER_ON_RESET		( BIT24 )
#define	MCU_RESF_SYSTEM_WDT_RESET			( BIT25 )
#define	MCU_RESF_RWDT_RESET					( BIT26 )

/*==============================================================================================*/
/*	register BIT definition																		*/
/*==============================================================================================*/
/*------------------------------------------------------------------*/
/*	SWMRESS_GTM														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	MCU_SWMRESS_GTM_MASK			( BIT0 )

/*------------------------------------------------------------------*/
/*	SWMRESS_EMU3													*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	MCU_SWMRESS_EMU3_0_MASK			( BIT0 )
#define	MCU_SWMRESS_EMU3_1_MASK			( BIT1 )

#endif	/* REG_RESET_H */
/*-- End Of File -------------------------------------------------------------------------------*/
