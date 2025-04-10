/* Reg_CLOCK-r04-30700-0000-a-v01 */
/************************************************************************************************/
/*																								*/
/*		Clock Controller register definition (for RH850U2A and RH850U2B and RCARS4 G4MH)		*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

#ifndef	REG_CLOCK_H
#define	REG_CLOCK_H

#include	"Std_Types.h"
#include	"Mcal_SpalCmn.h"

/*==============================================================================================*/
/*	register type definition																	*/
/*==============================================================================================*/
/*------------------------------------------------------------------------------*/
/* Clock Controller Registers for ISO area										*/
/*------------------------------------------------------------------------------*/
typedef	struct {

#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
	uint32	u4PLLE;
	uint32	u4PLLS;
	uint8	u1Dummy1[4];
	uint32	u4PLLSTPM;
	uint8	u1Dummy2[240];
	uint32	u4CKSC_CPUC;
	uint8	u1Dummy3[4];
	uint32	u4CKSC_CPUS;
	uint8	u1Dummy4[20];
	uint32	u4CLKD_PLLC;
	uint8	u1Dummy5[4];
	uint32	u4CLKD_PLLS;
	uint8	u1Dummy6[20];
	uint32	u4CKSC_RLINC;
	uint8	u1Dummy7[4];
	uint32	u4CKSC_RLINS;
	uint8	u1Dummy8[4];
	uint32	u4CKSC_RCANC;
	uint8	u1Dummy9[4];
	uint32	u4CKSC_RCANS;
	uint8	u1Dummy10[4];
	uint32	u4CKSC_ADCC;
	uint8	u1Dummy11[4];
	uint32	u4CKSC_ADCS;
	uint8	u1Dummy12[4];
	uint32	u4CKSC_MSPIC;
	uint8	u1Dummy13[4];
	uint32	u4CKSC_MSPIS;
	uint8	u1Dummy14[1412];
	uint32	u4CLKKCPROT1;

#elif ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
	uint32	u4PLLE;
	uint32	u4PLLS;
	uint8	u1Dummy1[4];
	uint32	u4PLLSTPM;
	uint8	u1Dummy2[28];
	uint32	u4SSCGC;
	uint8	u1Dummy3[28];
	uint32	u4SSCG1C;
	uint8	u1Dummy4[176];
	uint32	u4CKS_CLEANC;
	uint8	u1Dummy5[4];
	uint32	u4CKS_CLEANS;
	uint8	u1Dummy6[4];
	uint32	u4CKS_SSCGC;
	uint32	u4CKS_SSCGS;
	uint32	u4CKS_SSCG1C;
	uint32	u4CKS_SSCG1S;
	uint32	u4CKD_PLLC;
	uint8	u1Dummy7[4];
	uint32	u4CKD_PLLS;
	uint8	u1Dummy8[4];
	uint32	u4CKD_SSCGC;
	uint32	u4CKD_SSCGS;
	uint32	u4CKD_SSCG1C;
	uint32	u4CKD_SSCG1S;
	uint32	u4CKS_RLINC;
	uint8	u1Dummy9[4];
	uint32	u4CKS_RLINS;
	uint8	u1Dummy10[4];
	uint32	u4CKS_RCANC;
	uint8	u1Dummy11[4];
	uint32	u4CKS_RCANS;
	uint8	u1Dummy12[20];
	uint32	u4CKS_MSPIC;
	uint8	u1Dummy13[4];
	uint32	u4CKS_MSPIS;
	uint8	u1Dummy14[20];
	uint32	u4CKS_SWDTC;
	uint8	u1Dummy15[4];
	uint32	u4CKS_SWDTS;
	uint8	u1Dummy16[1380];
	uint32	u4CLKKCPROT1;

#else	/* MCAL_SPAL_TARGET == MCAL_TARGET_RCARS4_G4MH */
	uint32	u4PLLE;
	uint32	u4PLLS;
	uint8	u1Dummy1[248];
	uint32	u4CKSC_CPUC;
	uint8	u1Dummy2[4];
	uint32	u4CKSC_CPUS;
	uint8	u1Dummy3[20];
	uint32	u4CLKD_PLLC;
	uint8	u1Dummy4[4];
	uint32	u4CLKD_PLLS;
	uint8	u1Dummy5[20];
	uint32	u4CKSC_RLINC;
	uint8	u1Dummy6[4];
	uint32	u4CKSC_RLINS;
	uint8	u1Dummy7[4];
	uint32	u4CKSC_RCANC;
	uint8	u1Dummy8[4];
	uint32	u4CKSC_RCANS;
	uint8	u1Dummy9[20];
	uint32	u4CKSC_MSPIC;
	uint8	u1Dummy10[4];
	uint32	u4CKSC_MSPIS;
	uint8	u1Dummy11[1412];
	uint32	u4CLKKCPROT1;

#endif

} Reg_Clock_IsoType;

/*------------------------------------------------------------------------------*/
/* Clock Controller Registers for AWO area										*/
/*------------------------------------------------------------------------------*/
typedef	struct {

#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
	uint32	u4MOSCE;
	uint32	u4MOSCS;
	uint8	u1Dummy1[4];
	uint32	u4MOSCSTPM;
	uint8	u1Dummy2[240];
	uint32	u4HSOSCS;
	uint32	u4HSOSCSTPM;
	uint8	u1Dummy3[248];
	uint32	u4CKSC_AWDTC;
	uint8	u1Dummy4[4];
	uint32	u4CKSC_AWDTS;
	uint8	u1Dummy5[4];
	uint32	u4CKSC_ATAUJC;
	uint8	u1Dummy6[4];
	uint32	u4CKSC_ATAUJS;
	uint8	u1Dummy7[4];
	uint32	u4CKSC_ARTCAC;
	uint8	u1Dummy8[4];
	uint32	u4CKSC_ARTCAS;
	uint8	u1Dummy9[4];
	uint32	u4CKSC_AADCC;
	uint8	u1Dummy10[4];
	uint32	u4CKSC_AADCS;
	uint8	u1Dummy11[4];
	uint32	u4CLKD_AADCC;
	uint8	u1Dummy12[4];
	uint32	u4CLKD_AADCS;
	uint8	u1Dummy13[4];
	uint32	u4CKSC_FOUT0C;
	uint8	u1Dummy14[4];
	uint32	u4CKSC_FOUT0S;
	uint8	u1Dummy15[4];
	uint32	u4CLKD_FOUT0C;
	uint8	u1Dummy16[4];
	uint32	u4CLKD_FOUT0S;
	uint8	u1Dummy17[4];
	uint32	u4CKSC_FOUT1C;
	uint8	u1Dummy18[4];
	uint32	u4CKSC_FOUT1S;
	uint8	u1Dummy19[4];
	uint32	u4CLKD_FOUT1C;
	uint8	u1Dummy20[4];
	uint32	u4CLKD_FOUT1S;
	uint8	u1Dummy21[116];
	uint32	u4CKSC_WDTC;
	uint8	u1Dummy22[4];
	uint32	u4CKSC_WDTS;

#elif ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
	uint32	u4MOSCE;
	uint32	u4MOSCS;
	uint8	u1Dummy1[4];
	uint32	u4MOSCSTPM;
	uint8	u1Dummy2[240];
	uint32	u4HSOSCS;
	uint32	u4HSOSCSTPM;
	uint8	u1Dummy3[248];
	uint32	u4CKS_AWDTC;
	uint8	u1Dummy4[4];
	uint32	u4CKS_AWDTS;
	uint8	u1Dummy5[4];
	uint32	u4CKS_ATAUJC;
	uint8	u1Dummy6[4];
	uint32	u4CKS_ATAUJS;
	uint8	u1Dummy7[4];
	uint32	u4CKS_ARTCAC;
	uint8	u1Dummy8[4];
	uint32	u4CKS_ARTCAS;
	uint8	u1Dummy9[4];
	uint32	u4CKS_AADCC;
	uint8	u1Dummy10[4];
	uint32	u4CKS_AADCS;
	uint8	u1Dummy11[20];
	uint32	u4CKS_EXTCLK0C;
	uint8	u1Dummy12[4];
	uint32	u4CKS_EXTCLK0S;
	uint8	u1Dummy13[4];
	uint32	u4CKD_EXTCLK0C;
	uint8	u1Dummy14[4];
	uint32	u4CKD_EXTCLK0S;
	uint8	u1Dummy15[4];
	uint32	u4CKS_EXTCLK1C;
	uint8	u1Dummy16[4];
	uint32	u4CKS_EXTCLK1S;
	uint8	u1Dummy17[4];
	uint32	u4CKD_EXTCLK1C;
	uint8	u1Dummy18[4];
	uint32	u4CKD_EXTCLK1S;
	uint8	u1Dummy19[116];
	uint32	u4CKS_WDTC;
	uint8	u1Dummy20[4];
	uint32	u4CKS_WDTS;

#else	/* MCAL_SPAL_TARGET == MCAL_TARGET_RCARS4_G4MH */
	uint32	u4MOSCE;
	uint32	u4MOSCS;
	uint8	u1Dummy1[4];
	uint32	u4MOSCSTPM;
	uint8	u1Dummy2[240];
	uint32	u4HSOSCS;
	uint32	u4HSOSCSTPM;
	uint8	u1Dummy3[264];
	uint32	u4CKSC_ATAUJC;
	uint8	u1Dummy4[4];
	uint32	u4CKSC_ATAUJS;
	uint8	u1Dummy5[4];
	uint32	u4CKSC_ARTCAC;
	uint8	u1Dummy6[4];
	uint32	u4CKSC_ARTCAS;
	uint8	u1Dummy7[36];
	uint32	u4CKSC_FOUT0C;
	uint8	u1Dummy8[4];
	uint32	u4CKSC_FOUT0S;
	uint8	u1Dummy9[4];
	uint32	u4CLKD_FOUT0C;
	uint8	u1Dummy10[4];
	uint32	u4CLKD_FOUT0S;
	uint8	u1Dummy11[148];
	uint32	u4CKSC_WDTC;
	uint8	u1Dummy12[4];
	uint32	u4CKSC_WDTS;

#endif

} Reg_Clock_AwoType;

/*==============================================================================================*/
/*	register BIT definition																		*/
/*==============================================================================================*/
/*------------------------------------------------------------------------------*/
/* Clock Controller Registers for ISO area										*/
/*------------------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
/*	PLLE															*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_PLLE_PLLDISTRG			( BIT1 )
#define	CLOCK_PLLE_PLLENTRG				( BIT0 )
/* Bit setting value definition */
#define	CLOCK_PLLE_PLLDISTRG_NOFUNCTION	(0U)
#define	CLOCK_PLLE_PLLDISTRG_STOP		(1U)
#define	CLOCK_PLLE_PLLENTRG_NOFUNCTION	(0U)
#define	CLOCK_PLLE_PLLENTRG_START		(1U)

/*------------------------------------------------------------------*/
/*	PLLS															*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_PLLS_PLLCLKSTAB			( BIT1 )
#define	CLOCK_PLLS_PLLCLKEN				( BIT0 )
/* Bit setting value definition */
#define	CLOCK_PLLS_PLLCLKSTAB_UNSTABLE	(0U)
#define	CLOCK_PLLS_PLLCLKSTAB_STABLE	(1U)
#define	CLOCK_PLLS_PLLCLKEN_DISTRGSET	(0U)
#define	CLOCK_PLLS_PLLCLKEN_ENTRGSET	(1U)

#if ( ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) || ( MCAL_SPAL_TARGET == MCAL_TARGET_RCARS4_G4MH ) )

/*------------------------------------------------------------------*/
/*	CKSC_CPUC														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CKSC_CPUC_CPUCLKSCSID		( BIT0 )
/* Bit setting value definition */
#define	CLOCK_CKSC_CPUC_CPUCLKSCSID_PLLO	(0U)
#define	CLOCK_CKSC_CPUC_CPUCLKSCSID_IOSC	(1U)

/*------------------------------------------------------------------*/
/*	CKSC_CPUS														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CKSC_CPUS_CPUCLKSACT		( BIT0 )
/* Bit setting value definition */
#define	CLOCK_CKSC_CPUS_CPUCLKSACT_PLLO	(0U)
#define	CLOCK_CKSC_CPUS_CPUCLKSACT_IOSC	(1U)

/*------------------------------------------------------------------*/
/*	CLKD_PLLC														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CLKD_PLLC_PLLCLKDCSID		( BIT2 + BIT1 + BIT0 )
#define	CLOCK_CLKD_PLLC_PLLCLKDCSID_0	( BIT0 )
/* Bit setting value definition */
#define	CLOCK_CLKD_PLLC_PLLCLKDCSID_NO_DIV	(1U)		/* No division	*/
#define	CLOCK_CLKD_PLLC_PLLCLKDCSID_1_2		(2U)		/* Divided by 2	*/

/*------------------------------------------------------------------*/
/*	CLKD_PLLS														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CLKD_PLLS_PLLCLKDSYNC		( BIT1 )
/* Bit setting value definition */
#define	CLOCK_CLKD_PLLS_PLLCLKDSYNC_NOT_SYNC	(0U)
#define	CLOCK_CLKD_PLLS_PLLCLKDSYNC_SYNC		(1U)

/*------------------------------------------------------------------*/
/*	CKSC_RLINC														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CKSC_RLINC_RLINSCSID		( BIT1 + BIT0 )
#define	CLOCK_CKSC_RLINC_RLINSCSID_0	( BIT0 )
/* Bit setting value definition */
#define	CLOCK_CKSC_RLINC_RLINSCSID_MOSC		(0U)		/* CLK_MOSC		*/
#define	CLOCK_CKSC_RLINC_RLINSCSID_HSB		(1U)		/* CLK_HSB		*/
#define	CLOCK_CKSC_RLINC_RLINSCSID_1_4_MOSC	(2U)		/* CLK_MOSC/4	*/
#define	CLOCK_CKSC_RLINC_RLINSCSID_1_8_MOSC	(3U)		/* CLK_MOSC/8	*/

/*------------------------------------------------------------------*/
/*	CKSC_RLINS														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CKSC_RLINS_RLINSACT		( BIT1 + BIT0 )
#define	CLOCK_CKSC_RLINS_RLINSACT_0		( BIT0 )
/* Bit setting value definition */
#define	CLOCK_CKSC_RLINS_RLINSACT_MOSC		(0U)		/* CLK_MOSC		*/
#define	CLOCK_CKSC_RLINS_RLINSACT_HSB		(1U)		/* CLK_HSB		*/
#define	CLOCK_CKSC_RLINS_RLINSACT_1_4_MOSC	(2U)		/* CLK_MOSC/4	*/
#define	CLOCK_CKSC_RLINS_RLINSACT_1_8_MOSC	(3U)		/* CLK_MOSC/8	*/

/*------------------------------------------------------------------*/
/*	CKSC_RCANC														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CKSC_RCANC_RCANSCSID		( BIT1 + BIT0 )
#define	CLOCK_CKSC_RCANC_RCANSCSID_0	( BIT0 )
/* Bit setting value definition */
#define	CLOCK_CKSC_RCANC_RCANSCSID_MOSC		(1U)		/* CLK_MOSC		*/
#define	CLOCK_CKSC_RCANC_RCANSCSID_1_2_MOSC	(2U)		/* CLK_MOSC/2	*/
#define	CLOCK_CKSC_RCANC_RCANSCSID_1_4_MOSC	(3U)		/* CLK_MOSC/4	*/

/*------------------------------------------------------------------*/
/*	CKSC_RCANS														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CKSC_RCANS_RCANSACT		( BIT1 + BIT0 )
#define	CLOCK_CKSC_RCANS_RCANSACT_0		( BIT0 )
/* Bit setting value definition */
#define	CLOCK_CKSC_RCANS_RCANSACT_MOSC		(1U)		/* CLK_MOSC		*/
#define	CLOCK_CKSC_RCANS_RCANSACT_1_2_MOSC	(2U)		/* CLK_MOSC/2	*/
#define	CLOCK_CKSC_RCANS_RCANSACT_1_4_MOSC	(3U)		/* CLK_MOSC/4	*/

/*------------------------------------------------------------------*/
/*	CKSC_MSPIC														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CKSC_MSPIC_MSPISCSID		( BIT0 )
/* Bit setting value definition */
#define	CLOCK_CKSC_MSPIC_MSPISCSID_MOSC	(0U)
#define	CLOCK_CKSC_MSPIC_MSPISCSID_HSB	(1U)

/*------------------------------------------------------------------*/
/*	CKSC_MSPIS														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CKSC_MSPIS_MSPISACT		( BIT0 )
/* Bit setting value definition */
#define	CLOCK_CKSC_MSPIS_MSPISACT_MOSC	(0U)
#define	CLOCK_CKSC_MSPIS_MSPISACT_HSB	(1U)

#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) || ( MCAL_SPAL_TARGET == MCAL_TARGET_RCARS4_G4MH ) */

#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )

/*------------------------------------------------------------------*/
/*	CKSC_ADCC														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CKSC_ADCC_ADCSCSID		( BIT0 )
/* Bit setting value definition */
#define	CLOCK_CKSC_ADCC_ADCSCSID_LSB		(0U)		/* CLK_LSB		*/
#define	CLOCK_CKSC_ADCC_ADCSCSID_1_2_LSB	(1U)		/* CLK_LSB/2	*/

/*------------------------------------------------------------------*/
/*	CKSC_ADCS														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CKSC_ADCS_ADCSACT			( BIT0 )
/* Bit setting value definition */
#define	CLOCK_CKSC_ADCS_ADCSACT_LSB		(0U)			/* CLK_LSB		*/
#define	CLOCK_CKSC_ADCS_ADCSACT_1_2_LSB	(1U)			/* CLK_LSB/2	*/

#endif	/* MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A */

#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )

/*------------------------------------------------------------------*/
/*	SSCGC															*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_SSCGC_SSMODE1				( BIT9 )
#define	CLOCK_SSCGC_SELMFREQ			( BIT7 + BIT6 + BIT5 + BIT4 + BIT3 )
#define	CLOCK_SSCGC_SELMFREQ_0			( BIT3 )
#define	CLOCK_SSCGC_SELMPERCENT			( BIT2 + BIT1 + BIT0 )
#define	CLOCK_SSCGC_SELMPERCENT_0		( BIT0 )
/* Bit setting value definition */
#define	CLOCK_SSCGC_SSMODE1_DISABLE		(0U)
#define	CLOCK_SSCGC_SSMODE1_ENABLE		(1U)
#define	CLOCK_SSCGC_SELMPERCENT_1		(0U)
#define	CLOCK_SSCGC_SELMPERCENT_2		(1U)
#define	CLOCK_SSCGC_SELMPERCENT_3		(2U)
#define	CLOCK_SSCGC_SELMPERCENT_4		(3U)
#define	CLOCK_SSCGC_SELMPERCENT_5		(4U)
#define	CLOCK_SSCGC_SELMFREQ_LOWEST_VALID_VALUE		(8U)

/*------------------------------------------------------------------*/
/*	CKS_CLEANC														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CKS_CLEANC_SYSCLKSCSID	( BIT0 )
/* Bit setting value definition */
#define	CLOCK_CKS_CLEANC_SYSCLKSCSID_PLLO	(0U)
#define	CLOCK_CKS_CLEANC_SYSCLKSCSID_IOSC	(1U)

/*------------------------------------------------------------------*/
/*	CKS_CLEANS														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CKS_CLEANS_SYSCLKSACT		( BIT0 )
/* Bit setting value definition */
#define	CLOCK_CKS_CLEANS_SYSCLKSACT_PLLO	(0U)
#define	CLOCK_CKS_CLEANS_SYSCLKSACT_IOSC	(1U)

/*------------------------------------------------------------------*/
/*	CKS_SSCGC														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CKS_SSCGC_SYSCLKSCSID		( BIT0 )
/* Bit setting value definition */
#define	CLOCK_CKS_SSCGC_SYSCLKSCSID_SSCGO	(0U)
#define	CLOCK_CKS_SSCGC_SYSCLKSCSID_IOSC	(1U)

/*------------------------------------------------------------------*/
/*	CKS_SSCGS														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CKS_SSCGS_SYSCLKSACT		( BIT0 )
/* Bit setting value definition */
#define	CLOCK_CKS_SSCGS_SYSCLKSACT_SSCG	(0U)
#define	CLOCK_CKS_SSCGS_SYSCLKSACT_IOSC	(1U)

/*------------------------------------------------------------------*/
/*	CKD_PLLC														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CKD_PLLC_PLLCLKDCSID		( BIT3 + BIT2 + BIT1 + BIT0 )
#define	CLOCK_CKD_PLLC_PLLCLKDCSID_0	( BIT0 )
/* Bit setting value definition */
#define	CLOCK_CKD_PLLC_PLLCLKDCSID_NO_DIV	(0U)		/* No division		*/
#define	CLOCK_CKD_PLLC_PLLCLKDCSID_2_16		(2U)		/* Divided by 2/16	*/
#define	CLOCK_CKD_PLLC_PLLCLKDCSID_3_16		(3U)		/* Divided by 3/16	*/
#define	CLOCK_CKD_PLLC_PLLCLKDCSID_4_16		(4U)		/* Divided by 4/16	*/
#define	CLOCK_CKD_PLLC_PLLCLKDCSID_5_16		(5U)		/* Divided by 5/16	*/
#define	CLOCK_CKD_PLLC_PLLCLKDCSID_6_16		(6U)		/* Divided by 6/16	*/
#define	CLOCK_CKD_PLLC_PLLCLKDCSID_7_16		(7U)		/* Divided by 7/16	*/
#define	CLOCK_CKD_PLLC_PLLCLKDCSID_8_16		(8U)		/* Divided by 8/16	*/
#define	CLOCK_CKD_PLLC_PLLCLKDCSID_9_16		(9U)		/* Divided by 9/16	*/
#define	CLOCK_CKD_PLLC_PLLCLKDCSID_10_16	(10U)		/* Divided by 10/16	*/
#define	CLOCK_CKD_PLLC_PLLCLKDCSID_11_16	(11U)		/* Divided by 11/16	*/
#define	CLOCK_CKD_PLLC_PLLCLKDCSID_12_16	(12U)		/* Divided by 12/16	*/
#define	CLOCK_CKD_PLLC_PLLCLKDCSID_13_16	(13U)		/* Divided by 13/16	*/
#define	CLOCK_CKD_PLLC_PLLCLKDCSID_14_16	(14U)		/* Divided by 14/16	*/
#define	CLOCK_CKD_PLLC_PLLCLKDCSID_15_16	(15U)		/* Divided by 15/16	*/

/*------------------------------------------------------------------*/
/*	CKD_PLLS														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CKD_PLLS_PLLCLKDSYNC		( BIT1 )
/* Bit setting value definition */
#define	CLOCK_CKD_PLLS_PLLCLKDSYNC_NOT_SYNC	(0U)
#define	CLOCK_CKD_PLLS_PLLCLKDSYNC_SYNC		(1U)

/*------------------------------------------------------------------*/
/*	CKD_SSCGC														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CKD_SSCGC_SSCGCLKDCSID	( BIT3 + BIT2 + BIT1 + BIT0 )
#define	CLOCK_CKD_SSCGC_SSCGCLKDCSID_0	( BIT0 )
/* Bit setting value definition */
#define	CLOCK_CKD_SSCGC_SSCGCLKDCSID_NO_DIV	(0U)		/* No division		*/
#define	CLOCK_CKD_SSCGC_SSCGCLKDCSID_2_16	(2U)		/* Divided by 2/16	*/
#define	CLOCK_CKD_SSCGC_SSCGCLKDCSID_3_16	(3U)		/* Divided by 3/16	*/
#define	CLOCK_CKD_SSCGC_SSCGCLKDCSID_4_16	(4U)		/* Divided by 4/16	*/
#define	CLOCK_CKD_SSCGC_SSCGCLKDCSID_5_16	(5U)		/* Divided by 5/16	*/
#define	CLOCK_CKD_SSCGC_SSCGCLKDCSID_6_16	(6U)		/* Divided by 6/16	*/
#define	CLOCK_CKD_SSCGC_SSCGCLKDCSID_7_16	(7U)		/* Divided by 7/16	*/
#define	CLOCK_CKD_SSCGC_SSCGCLKDCSID_8_16	(8U)		/* Divided by 8/16	*/
#define	CLOCK_CKD_SSCGC_SSCGCLKDCSID_9_16	(9U)		/* Divided by 9/16	*/
#define	CLOCK_CKD_SSCGC_SSCGCLKDCSID_10_16	(10U)	/* Divided by 10/16	*/
#define	CLOCK_CKD_SSCGC_SSCGCLKDCSID_11_16	(11U)	/* Divided by 11/16	*/
#define	CLOCK_CKD_SSCGC_SSCGCLKDCSID_12_16	(12U)	/* Divided by 12/16	*/
#define	CLOCK_CKD_SSCGC_SSCGCLKDCSID_13_16	(13U)	/* Divided by 13/16	*/
#define	CLOCK_CKD_SSCGC_SSCGCLKDCSID_14_16	(14U)	/* Divided by 14/16	*/
#define	CLOCK_CKD_SSCGC_SSCGCLKDCSID_15_16	(15U)	/* Divided by 15/16	*/

/*------------------------------------------------------------------*/
/*	CKD_SSCGS														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CKD_SSCGS_SSCGCLKDSYNC	( BIT1 )
/* Bit setting value definition */
#define	CLOCK_CKD_SSCGS_SSCGCLKDSYNC_NOT_SYNC	(0U)
#define	CLOCK_CKD_SSCGS_SSCGCLKDSYNC_SYNC		(1U)

/*------------------------------------------------------------------*/
/*	CKS_RLINC														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CKS_RLINC_RLIN23SCSID		( BIT18 + BIT17 + BIT16 )
#define	CLOCK_CKS_RLINC_RLIN23SCSID_0	( BIT16 )
#define	CLOCK_CKS_RLINC_RLINSCSID		( BIT2 + BIT1 + BIT0 )
#define	CLOCK_CKS_RLINC_RLINSCSID_0		( BIT0 )
/* Bit setting value definition */
#define	CLOCK_CKS_RLINC_RLIN23SCSID_EMG			(0U)
#define	CLOCK_CKS_RLINC_RLIN23SCSID_HBUS		(1U)
#define	CLOCK_CKS_RLINC_RLIN23SCSID_MOSC		(2U)
#define	CLOCK_CKS_RLINC_RLIN23SCSID_4_MOSC		(3U)
#define	CLOCK_CKS_RLINC_RLIN23SCSID_8_MOSC		(4U)
#define	CLOCK_CKS_RLINC_RLINSCSID_EMG			(0U)
#define	CLOCK_CKS_RLINC_RLINSCSID_HBUS			(1U)
#define	CLOCK_CKS_RLINC_RLINSCSID_MOSC			(2U)
#define	CLOCK_CKS_RLINC_RLINSCSID_4_MOSC		(3U)
#define	CLOCK_CKS_RLINC_RLINSCSID_8_MOSC		(4U)

/*------------------------------------------------------------------*/
/*	CKS_RLINS														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CKS_RLINS_RLIN23SACT		( BIT18 + BIT17 + BIT16 )
#define	CLOCK_CKS_RLINS_RLIN23SACT_0	( BIT16 )
#define	CLOCK_CKS_RLINS_RLINSACT		( BIT2 + BIT1 + BIT0 )
#define	CLOCK_CKS_RLINS_RLINSACT_0		( BIT0 )
/* Bit setting value definition */
#define	CLOCK_CKS_RLINS_RLIN23SACT_EMG			(0U)
#define	CLOCK_CKS_RLINS_RLIN23SACT_HBUS			(1U)
#define	CLOCK_CKS_RLINS_RLIN23SACT_MOSC			(2U)
#define	CLOCK_CKS_RLINS_RLIN23SACT_4_MOSC		(3U)
#define	CLOCK_CKS_RLINS_RLIN23SACT_8_MOSC		(4U)
#define	CLOCK_CKS_RLINS_RLINSACT_EMG			(0U)
#define	CLOCK_CKS_RLINS_RLINSACT_HBUS			(1U)
#define	CLOCK_CKS_RLINS_RLINSACT_MOSC			(2U)
#define	CLOCK_CKS_RLINS_RLINSACT_4_MOSC			(3U)
#define	CLOCK_CKS_RLINS_RLINSACT_8_MOSC			(4U)

/*------------------------------------------------------------------*/
/*	CKS_RCANC														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CKS_RCANC_RCANCSCSID		( BIT17 + BIT16 )
#define	CLOCK_CKS_RCANC_RCANCSCSID_0	( BIT16 )
#define	CLOCK_CKS_RCANC_RCANXINSCSID	( BIT1 + BIT0 )
#define	CLOCK_CKS_RCANC_RCANXINSCSID_0	( BIT0 )
/* Bit setting value definition */
#define	CLOCK_CKS_RCANC_RCANCSCSID_EMG		(0U)
#define	CLOCK_CKS_RCANC_RCANCSCSID_HSB		(1U)
#define	CLOCK_CKS_RCANC_RCANCSCSID_2_HSB	(2U)
#define	CLOCK_CKS_RCANC_RCANCSCSID_4_HSB	(3U)
#define	CLOCK_CKS_RCANC_RCANXINSCSID_EMG	(0U)
#define	CLOCK_CKS_RCANC_RCANXINSCSID_MOSC	(1U)
#define	CLOCK_CKS_RCANC_RCANXINSCSID_2_MOSC	(2U)
#define	CLOCK_CKS_RCANC_RCANXINSCSID_4_MOSC	(3U)

/*------------------------------------------------------------------*/
/*	CKS_RCANS														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CKS_RCANS_RCANCSACT		( BIT17 + BIT16 )
#define	CLOCK_CKS_RCANS_RCANCSACT_0		( BIT16 )
#define	CLOCK_CKS_RCANS_RCANXINSACT		( BIT1 + BIT0 )
#define	CLOCK_CKS_RCANS_RCANXINSACT_0	( BIT0 )
/* Bit setting value definition */
#define	CLOCK_CKS_RCANS_RCANCSACT_EMG		(0U)
#define	CLOCK_CKS_RCANS_RCANCSACT_HSB		(1U)
#define	CLOCK_CKS_RCANS_RCANCSACT_2_HSB		(2U)
#define	CLOCK_CKS_RCANS_RCANCSACT_4_HSB		(3U)
#define	CLOCK_CKS_RCANS_RCANXINSACT_EMG		(0U)
#define	CLOCK_CKS_RCANS_RCANXINSACT_MOSC	(1U)
#define	CLOCK_CKS_RCANS_RCANXINSACT_2_MOSC	(2U)
#define	CLOCK_CKS_RCANS_RCANXINSACT_4_MOSC	(3U)

/*------------------------------------------------------------------*/
/*	CKS_MSPIC														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CKS_MSPIC_MSPISCSID		( BIT1 + BIT0 )
#define	CLOCK_CKS_MSPIC_MSPISCSID_0		( BIT0 )
/* Bit setting value definition */
#define	CLOCK_CKS_MSPIC_MSPISCSID_EMG	(0U)
#define	CLOCK_CKS_MSPIC_MSPISCSID_MOSC	(1U)
#define	CLOCK_CKS_MSPIC_MSPISCSID_HSB	(2U)

/*------------------------------------------------------------------*/
/*	CKS_MSPIS														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CKS_MSPIS_MSPISACT		( BIT1 + BIT0 )
#define	CLOCK_CKS_MSPIS_MSPISACT_0		( BIT0 )
/* Bit setting value definition */
#define	CLOCK_CKS_MSPIS_MSPISACT_EMG	(0U)
#define	CLOCK_CKS_MSPIS_MSPISACT_MOSC	(1U)
#define	CLOCK_CKS_MSPIS_MSPISACT_HSB	(2U)

/*------------------------------------------------------------------*/
/*	CKS_SWDTC														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CKS_SWDTC_SWDTSCSID		( BIT1 + BIT0 )
#define	CLOCK_CKS_SWDTC_SWDTSCSID_0		( BIT0 )
/* Bit setting value definition */
#define	CLOCK_CKS_SWDTC_SWDTSCSID_1_20_HSIOSC		(0U)
#define	CLOCK_CKS_SWDTC_SWDTSCSID_1_640_HSIOSC		(1U)
#define	CLOCK_CKS_SWDTC_SWDTSCSID_1_800_HSIOSC		(2U)
#define	CLOCK_CKS_SWDTC_SWDTSCSID_1_100000_HSIOSC	(3U)

/*------------------------------------------------------------------*/
/*	CKS_SWDTCS														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CKS_SWDTS_SWDTSACT		( BIT1 + BIT0 )
#define	CLOCK_CKS_SWDTS_SWDTSACT_0		( BIT0 )
/* Bit setting value definition */
#define	CLOCK_CKS_SWDTS_SWDTSACT_1_20_HSIOSC		(0U)
#define	CLOCK_CKS_SWDTS_SWDTSACT_1_640_HSIOSC		(1U)
#define	CLOCK_CKS_SWDTS_SWDTSACT_1_800_HSIOSC		(2U)
#define	CLOCK_CKS_SWDTS_SWDTSACT_1_100000_HSIOSC	(3U)

#endif	/* MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B */

/*------------------------------------------------------------------------------*/
/* Clock Controller Registers for AWO area										*/
/*------------------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
/*	MOSCE															*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_MOSCE_MOSCDISTRG			( BIT1 )
#define	CLOCK_MOSCE_MOSCENTRG			( BIT0 )
/* Bit setting value definition */
#define	CLOCK_MOSCE_MOSCDISTRG_NO_FUNC	(0U)
#define	CLOCK_MOSCE_MOSCDISTRG_STOP		(1U)
#define	CLOCK_MOSCE_MOSCENTRG_NO_FUNC	(0U)
#define	CLOCK_MOSCE_MOSCENTRG_START		(1U)

/*------------------------------------------------------------------*/
/*	MOSCS															*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_MOSCS_MOSCSTAB			( BIT1 )
#define	CLOCK_MOSCS_MOSCEN				( BIT0 )
/* Bit setting value definition */
#define	CLOCK_MOSCS_MOSCSTAB_UNSTABLE	(0U)
#define	CLOCK_MOSCS_MOSCSTAB_STABLE		(1U)
#define	CLOCK_MOSCS_MOSCEN_DISTRG_SET	(0U)
#define	CLOCK_MOSCS_MOSCEN_ENTRG_SET	(1U)

/*------------------------------------------------------------------*/
/*	MOSCSTPM														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_MOSCSTPM_MOSCSTPMSK		( BIT0 )
/* Bit setting value definition */
#define	CLOCK_MOSCSTPM_MOSCSTPMSK_STOP		(0U)
#define	CLOCK_MOSCSTPM_MOSCSTPMSK_CONTINUE	(1U)

/*------------------------------------------------------------------*/
/*	HSOSCS															*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_HSOSCS_HSOSCSTAB			( BIT1 )
/* Bit setting value definition */
#define	CLOCK_HSOSCS_HSOSCSTAB_UNSTABLE	(0U)
#define	CLOCK_HSOSCS_HSOSCSTAB_STABLE	(1U)

/*------------------------------------------------------------------*/
/*	HSOSCSTPM														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_HSOSCSTPM_HSOSCSTPMSK		( BIT0 )
/* Bit setting value definition */
#define	CLOCK_HSOSCSTPM_HSOSCSTPMSK_STOP		(0U)
#define	CLOCK_HSOSCSTPM_HSOSCSTPMSK_CONTINUE	(1U)

#if ( ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) || ( MCAL_SPAL_TARGET == MCAL_TARGET_RCARS4_G4MH ) )

/*------------------------------------------------------------------*/
/*	CKSC_ATAUJC														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CKSC_ATAUJC_ATAUJSCSID	( BIT1 + BIT0 )
#define	CLOCK_CKSC_ATAUJC_ATAUJSCSID_0	( BIT0 )
/* Bit setting value definition */
#define	CLOCK_CKSC_ATAUJC_ATAUJSCSID_LSIOSC			(0U)
#define	CLOCK_CKSC_ATAUJC_ATAUJSCSID_1_20_HSIOSC	(1U)
#define	CLOCK_CKSC_ATAUJC_ATAUJSCSID_MOSC			(2U)
#define	CLOCK_CKSC_ATAUJC_ATAUJSCSID_HSB			(3U)

/*------------------------------------------------------------------*/
/*	CKSC_ATAUJS														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CKSC_ATAUJS_ATAUJSACT		( BIT1 + BIT0 )
#define	CLOCK_CKSC_ATAUJS_ATAUJSACT_0	( BIT0 )
/* Bit setting value definition */
#define	CLOCK_CKSC_ATAUJS_ATAUJSACT_LSIOSC		(0U)
#define	CLOCK_CKSC_ATAUJS_ATAUJSACT_1_20_HSIOSC	(1U)
#define	CLOCK_CKSC_ATAUJS_ATAUJSACT_MOSC		(2U)
#define	CLOCK_CKSC_ATAUJS_ATAUJSACT_HSB			(3U)

/*------------------------------------------------------------------*/
/*	CKSC_ARTCAC														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CKSC_ARTCAC_ARTCASCSID	( BIT0 )
/* Bit setting value definition */
#define	CLOCK_CKSC_ARTCAC_ARTCASCSID_1_16_MOSC	(0U)
#define	CLOCK_CKSC_ARTCAC_ARTCASCSID_LSIOSC		(1U)

/*------------------------------------------------------------------*/
/*	CKSC_ARTCAS														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CKSC_ARTCAS_ARTCASACT		( BIT0 )
/* Bit setting value definition */
#define	CLOCK_CKSC_ARTCAS_ARTCASACT_1_16_MOSC	(0U)
#define	CLOCK_CKSC_ARTCAS_ARTCASACT_LSIOSC		(1U)

/*------------------------------------------------------------------*/
/*	CKSC_FOUT0C														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CKSC_FOUT0C_FOUT0SCSID	( BIT2 + BIT1 + BIT0 )
#define	CLOCK_CKSC_FOUT0C_FOUT0SCSID_0	( BIT0 )
/* Bit setting value definition */
#define	CLOCK_CKSC_FOUT0C_FOUT0SCSID_A_MOSC			(0U)
#define	CLOCK_CKSC_FOUT0C_FOUT0SCSID_HSB			(1U)
#define	CLOCK_CKSC_FOUT0C_FOUT0SCSID_LSIOSC			(3U)
#define	CLOCK_CKSC_FOUT0C_FOUT0SCSID_1_20_HSIOSC	(4U)
#define	CLOCK_CKSC_FOUT0C_FOUT0SCSID_B_MOSC			(6U)
#define	CLOCK_CKSC_FOUT0C_FOUT0SCSID_C_MOSC			(7U)

/*------------------------------------------------------------------*/
/*	CKSC_FOUT0S														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CKSC_FOUT0S_FOUT0SACT		( BIT2 + BIT1 + BIT0 )
#define	CLOCK_CKSC_FOUT0S_FOUT0SACT_0	( BIT0 )
/* Bit setting value definition */
#define	CLOCK_CKSC_FOUT0S_FOUT0SACT_A_MOSC			(0U)
#define	CLOCK_CKSC_FOUT0S_FOUT0SACT_HSB				(1U)
#define	CLOCK_CKSC_FOUT0S_FOUT0SACT_LSIOSC			(3U)
#define	CLOCK_CKSC_FOUT0S_FOUT0SACT_1_20_HSIOSC		(4U)
#define	CLOCK_CKSC_FOUT0S_FOUT0SACT_B_MOSC			(6U)
#define	CLOCK_CKSC_FOUT0S_FOUT0SACT_C_MOSC			(7U)

/*------------------------------------------------------------------*/
/*	CLKD_FOUT0C														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CLKD_FOUT0C_FOUT0DIV		( BIT9 + BIT8 + BIT7 + BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0 )
#define	CLOCK_CLKD_FOUT0C_FOUT0DIV_0	( BIT0 )

/*------------------------------------------------------------------*/
/*	CLKD_FOUT0S														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CLKD_FOUT0S_FOUT0CLKACT	( BIT1 )
#define	CLOCK_CLKD_FOUT0S_FOUT0SYNC		( BIT0 )
/* Bit setting value definition */
#define	CLOCK_CLKD_FOUT0S_FOUT0CLKACT_STOP		(0U)
#define	CLOCK_CLKD_FOUT0S_FOUT0CLKACT_ONGOING	(1U)
#define	CLOCK_CLKD_FOUT0S_FOUT0SYNC_NOT_STABLE	(0U)
#define	CLOCK_CLKD_FOUT0S_FOUT0SYNC_STABLE		(1U)

/*------------------------------------------------------------------*/
/*	CKSC_WDTC														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CKSC_WDTC_WDTSCSID		( BIT0 )
/* Bit setting value definition */
#define	CLOCK_CKSC_WDTC_WDTSCSID_1_20_HSIOSC	(0U)
#define	CLOCK_CKSC_WDTC_WDTSCSID_1_640_HSIOSC	(1U)

/*------------------------------------------------------------------*/
/*	CKSC_WDTS														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CKSC_WDTS_WDTSACT			( BIT0 )
/* Bit setting value definition */
#define	CLOCK_CKSC_WDTS_WDTSACT_1_20_HSIOSC		(0U)
#define	CLOCK_CKSC_WDTS_WDTSACT_1_640_HSIOSC	(1U)

#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) || ( MCAL_SPAL_TARGET == MCAL_TARGET_RCARS4_G4MH ) */

#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )

/*------------------------------------------------------------------*/
/*	CKSC_AWDTC														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CKSC_AWDTC_AWDTSCSID		( BIT0 )
/* Bit setting value definition */
#define	CLOCK_CKSC_AWDTC_AWDTSCSID_LSIOSC		(0U)
#define	CLOCK_CKSC_AWDTC_AWDTSCSID_1_128_LSIOSC	(1U)

/*------------------------------------------------------------------*/
/*	CKSC_AWDTS														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CKSC_AWDTS_AWDTSACT		( BIT0 )
/* Bit setting value definition */
#define	CLOCK_CKSC_AWDTS_AWDTSACT_LSIOSC		(0U)
#define	CLOCK_CKSC_AWDTS_AWDTSACT_1_128_LSIOSC	(1U)

/*------------------------------------------------------------------*/
/*	CKSC_AADCC														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CKSC_AADCC_AADCSCSID		( BIT1 + BIT0 )
#define	CLOCK_CKSC_AADCC_AADCSCSID_0	( BIT0 )
/* Bit setting value definition */
#define	CLOCK_CKSC_AADCC_AADCSCSID_MOSC			(0U)
#define	CLOCK_CKSC_AADCC_AADCSCSID_1_20_HSIOSC	(1U)
#define	CLOCK_CKSC_AADCC_AADCSCSID_LSB			(2U)

/*------------------------------------------------------------------*/
/*	CKSC_AADCS														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CKSC_AADCS_AADCSACT		( BIT1 + BIT0 )
#define	CLOCK_CKSC_AADCS_AADCSACT_0		( BIT0 )
/* Bit setting value definition */
#define	CLOCK_CKSC_AADCS_AADCSACT_MOSC			(0U)
#define	CLOCK_CKSC_AADCS_AADCSACT_1_20_HSIOSC	(1U)
#define	CLOCK_CKSC_AADCS_AADCSACT_LSB			(2U)

/*------------------------------------------------------------------*/
/*	CLKD_AADCC														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CLKD_AADCC_AADCDCSID		( BIT0 )
/* Bit setting value definition */
#define	CLOCK_CLKD_AADCC_AADCDCSID_1_2		(0U)
#define	CLOCK_CLKD_AADCC_AADCDCSID_NO_DIV	(1U)

/*------------------------------------------------------------------*/
/*	CLKD_AADCS														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CLKD_AADCS_AADCDACT		( BIT0 )
/* Bit setting value definition */
#define	CLOCK_CLKD_AADCS_AADCDACT_1_2		(0U)
#define	CLOCK_CLKD_AADCS_AADCDACT_NO_DIV	(1U)

/*------------------------------------------------------------------*/
/*	CKSC_FOUT1C														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CKSC_FOUT1C_FOUT1SCSID	( BIT2 + BIT1 + BIT0 )
#define	CLOCK_CKSC_FOUT1C_FOUT1SCSID_0	( BIT0 )
/* Bit setting value definition */
#define	CLOCK_CKSC_FOUT1C_FOUT1SCSID_A_MOSC			(0U)
#define	CLOCK_CKSC_FOUT1C_FOUT1SCSID_HSB			(1U)
#define	CLOCK_CKSC_FOUT1C_FOUT1SCSID_LSIOSC			(3U)
#define	CLOCK_CKSC_FOUT1C_FOUT1SCSID_1_20_HSIOSC	(4U)
#define	CLOCK_CKSC_FOUT1C_FOUT1SCSID_B_MOSC			(6U)
#define	CLOCK_CKSC_FOUT1C_FOUT1SCSID_C_MOSC			(7U)

/*------------------------------------------------------------------*/
/*	CKSC_FOUT1S														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CKSC_FOUT1S_FOUT1SACT		( BIT2 + BIT1 + BIT0 )
#define	CLOCK_CKSC_FOUT1S_FOUT1SACT_0	( BIT0 )
/* Bit setting value definition */
#define	CLOCK_CKSC_FOUT1S_FOUT1SACT_A_MOSC			(0U)
#define	CLOCK_CKSC_FOUT1S_FOUT1SACT_HSB				(1U)
#define	CLOCK_CKSC_FOUT1S_FOUT1SACT_LSIOSC			(3U)
#define	CLOCK_CKSC_FOUT1S_FOUT1SACT_1_20_HSIOSC		(4U)
#define	CLOCK_CKSC_FOUT1S_FOUT1SACT_B_MOSC			(6U)
#define	CLOCK_CKSC_FOUT1S_FOUT1SACT_C_MOSC			(7U)

/*------------------------------------------------------------------*/
/*	CLKD_FOUT1C														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CLKD_FOUT1C_FOUT1DIV		( BIT9 + BIT8 + BIT7 + BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0 )
#define	CLOCK_CLKD_FOUT1C_FOUT1DIV_0	( BIT0 )

/*------------------------------------------------------------------*/
/*	CLKD_FOUT1S														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CLKD_FOUT1S_FOUT1CLKACT	( BIT1 )
#define	CLOCK_CLKD_FOUT1S_FOUT1SYNC		( BIT0 )
/* Bit setting value definition */
#define	CLOCK_CLKD_FOUT1S_FOUT1CLKACT_STOP		(0U)
#define	CLOCK_CLKD_FOUT1S_FOUT1CLKACT_ONGOING	(1U)
#define	CLOCK_CLKD_FOUT1S_FOUT1SYNC_NOT_STABLE	(0U)
#define	CLOCK_CLKD_FOUT1S_FOUT1SYNC_STABLE		(1U)

#endif	/* MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A */

#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )

/*------------------------------------------------------------------*/
/*	CKS_AWDTC														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CKS_AWDTC_AWDTSCSID		( BIT0 )
/* Bit setting value definition */
#define	CLOCK_CKS_AWDTC_AWDTSCSID_LSIOSC		(0U)
#define	CLOCK_CKS_AWDTC_AWDTSCSID_1_128_LSIOSC	(1U)

/*------------------------------------------------------------------*/
/*	CKS_AWDTS														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CKS_AWDTS_AWDTSACT		( BIT0 )
/* Bit setting value definition */
#define	CLOCK_CKS_AWDTS_AWDTSACT_LSIOSC			(0U)
#define	CLOCK_CKS_AWDTS_AWDTSACT_1_128_LSIOSC	(1U)

/*------------------------------------------------------------------*/
/*	CKS_ATAUJC														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CKS_ATAUJC_ATAUJSCSID		( BIT2 + BIT1 + BIT0 )
#define	CLOCK_CKS_ATAUJC_ATAUJSCSID_0	( BIT0 )
/* Bit setting value definition */
#define	CLOCK_CKS_ATAUJC_ATAUJSCSID_EMG			(0U)
#define	CLOCK_CKS_ATAUJC_ATAUJSCSID_LSIOSC		(1U)
#define	CLOCK_CKS_ATAUJC_ATAUJSCSID_1_20_HSIOSC	(2U)
#define	CLOCK_CKS_ATAUJC_ATAUJSCSID_MOSC		(3U)
#define	CLOCK_CKS_ATAUJC_ATAUJSCSID_HSB			(4U)

/*------------------------------------------------------------------*/
/*	CKS_ATAUJS														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CKS_ATAUJS_ATAUJSACT		( BIT2 + BIT1 + BIT0 )
#define	CLOCK_CKS_ATAUJS_ATAUJSACT_0	( BIT0 )
/* Bit setting value definition */
#define	CLOCK_CKS_ATAUJS_ATAUJSACT_EMG			(0U)
#define	CLOCK_CKS_ATAUJS_ATAUJSACT_LSIOSC		(1U)
#define	CLOCK_CKS_ATAUJS_ATAUJSACT_1_20_HSIOSC	(2U)
#define	CLOCK_CKS_ATAUJS_ATAUJSACT_MOSC			(3U)
#define	CLOCK_CKS_ATAUJS_ATAUJSACT_HSB			(4U)

/*------------------------------------------------------------------*/
/*	CKS_ARTCAC														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CKS_ARTCAC_ARTCASCSID		( BIT1 + BIT0 )
#define	CLOCK_CKS_ARTCAC_ARTCASCSID_0	( BIT0 )
/* Bit setting value definition */
#define	CLOCK_CKS_ARTCAC_ARTCASCSID_EMG			(0U)
#define	CLOCK_CKS_ARTCAC_ARTCASCSID_LSIOSC		(1U)
#define	CLOCK_CKS_ARTCAC_ARTCASCSID_1_16_MOSC	(2U)

/*------------------------------------------------------------------*/
/*	CKS_ARTCAS														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CKS_ARTCAS_ARTCASACT		( BIT1 + BIT0 )
#define	CLOCK_CKS_ARTCAS_ARTCASACT_0	( BIT0 )
/* Bit setting value definition */
#define	CLOCK_CKS_ARTCAS_ARTCASACT_EMG			(0U)
#define	CLOCK_CKS_ARTCAS_ARTCASACT_LSIOSC		(1U)
#define	CLOCK_CKS_ARTCAS_ARTCASACT_1_16_MOSC	(2U)

/*------------------------------------------------------------------*/
/*	CKS_AADCC														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CKS_AADCC_AADCSCSID		( BIT1 + BIT0 )
#define	CLOCK_CKS_AADCC_AADCSCSID_0		( BIT0 )
/* Bit setting value definition */
#define	CLOCK_CKS_AADCC_AADCSCSID_EMG			(0U)
#define	CLOCK_CKS_AADCC_AADCSCSID_1_20_HSIOSC	(1U)
#define	CLOCK_CKS_AADCC_AADCSCSID_MOSC			(2U)
#define	CLOCK_CKS_AADCC_AADCSCSID_LSB			(3U)

/*------------------------------------------------------------------*/
/*	CKS_AADCS														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CKS_AADCS_AADCSACT		( BIT1 + BIT0 )
#define	CLOCK_CKS_AADCS_AADCSACT_0		( BIT0 )
/* Bit setting value definition */
#define	CLOCK_CKS_AADCS_AADCSACT_EMG			(0U)
#define	CLOCK_CKS_AADCS_AADCSACT_1_20_HSIOSC	(1U)
#define	CLOCK_CKS_AADCS_AADCSACT_MOSC			(2U)
#define	CLOCK_CKS_AADCS_AADCSACT_LSB			(3U)

/*------------------------------------------------------------------*/
/*	CKS_EXTCLK0C													*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_EXTCLK0SCSID				( BIT3 + BIT2 + BIT1 + BIT0 )
#define	CLOCK_EXTCLK0SCSID_0			( BIT0 )
/* Bit setting value definition */
#define	CLOCK_EXTCLK0SCSID_MOSC			(0U)
#define	CLOCK_EXTCLK0SCSID_LSIOSC		(1U)
#define	CLOCK_EXTCLK0SCSID_1_20_HSIOSC	(2U)
#define	CLOCK_EXTCLK0SCSID_CLK_HSB		(4U)
#define	CLOCK_EXTCLK0SCSID_CLKC_HSB		(5U)

/*------------------------------------------------------------------*/
/*	CKS_EXTCLK0S													*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_EXTCLK0SACT				( BIT3 + BIT2 + BIT1 + BIT0 )
#define	CLOCK_EXTCLK0SACT_0				( BIT0 )
/* Bit setting value definition */
#define	CLOCK_EXTCLK0SACT_MOSC			(0U)
#define	CLOCK_EXTCLK0SACT_LSIOSC		(1U)
#define	CLOCK_EXTCLK0SACT_1_20_HSIOSC	(2U)
#define	CLOCK_EXTCLK0SACT_CLK_HSB		(4U)
#define	CLOCK_EXTCLK0SACT_CLKC_HSB		(5U)

/*------------------------------------------------------------------*/
/*	CKD_EXTCLK0C													*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CKD_EXTCLK0C_EXTCLK0DIV	( BIT9 + BIT8 + BIT7 + BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0 )
#define	CLOCK_CKD_EXTCLK0C_EXTCLK0DIV_0	( BIT0 )

/*------------------------------------------------------------------*/
/*	CKD_EXTCLK0S													*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_EXTCLK0CLKACT				( BIT1 )
#define	CLOCK_EXTCLK0SYNC				( BIT0 )
/* Bit setting value definition */
#define	CLOCK_EXTCLK0CLKACT_STOP		(0U)
#define	CLOCK_EXTCLK0CLKACT_ONGOING		(1U)
#define	CLOCK_EXTCLK0SYNC_NOT_STABLE	(0U)
#define	CLOCK_EXTCLK0SYNC_STABLE		(1U)

/*------------------------------------------------------------------*/
/*	CKS_EXTCLK1C													*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_EXTCLK1SCSID				( BIT3 + BIT2 + BIT1 + BIT0 )
#define	CLOCK_EXTCLK1SCSID_0			( BIT0 )
/* Bit setting value definition */
#define	CLOCK_EXTCLK1SCSID_MOSC			(0U)
#define	CLOCK_EXTCLK1SCSID_LSIOSC		(1U)
#define	CLOCK_EXTCLK1SCSID_1_20_HSIOSC	(2U)
#define	CLOCK_EXTCLK1SCSID_CLK_HSB		(4U)
#define	CLOCK_EXTCLK1SCSID_CLKC_HSB		(5U)

/*------------------------------------------------------------------*/
/*	CKS_EXTCLK1S													*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_EXTCLK1SACT				( BIT3 + BIT2 + BIT1 + BIT0 )
#define	CLOCK_EXTCLK1SACT_0				( BIT0 )
/* Bit setting value definition */
#define	CLOCK_EXTCLK1SACT_MOSC			(0U)
#define	CLOCK_EXTCLK1SACT_LSIOSC		(1U)
#define	CLOCK_EXTCLK1SACT_1_20_HSIOSC	(2U)
#define	CLOCK_EXTCLK1SACT_CLK_HSB		(4U)
#define	CLOCK_EXTCLK1SACT_CLKC_HSB		(5U)

/*------------------------------------------------------------------*/
/*	CKD_EXTCLK1C													*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CKD_EXTCLK1C_EXTCLK1DIV	( BIT9 + BIT8 + BIT7 + BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0 )
#define	CLOCK_CKD_EXTCLK1C_EXTCLK1DIV_0	( BIT0 )

/*------------------------------------------------------------------*/
/*	CKD_EXTCLK1S													*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_EXTCLK1CLKACT				( BIT1 )
#define	CLOCK_EXTCLK1SYNC				( BIT0 )
/* Bit setting value definition */
#define	CLOCK_EXTCLK1CLKACT_STOP		(0U)
#define	CLOCK_EXTCLK1CLKACT_ONGOING		(1U)
#define	CLOCK_EXTCLK1SYNC_NOT_STABLE	(0U)
#define	CLOCK_EXTCLK1SYNC_STABLE		(1U)

/*------------------------------------------------------------------*/
/*	CKS_WDTC														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CKS_WDTC_WDTSCSID			( BIT1 + BIT0 )
#define	CLOCK_CKS_WDTC_WDTSCSID_0		( BIT0 )
/* Bit setting value definition */
#define	CLOCK_CKS_WDTC_WDTSCSID_1_20_HSIOSC		(0U)
#define	CLOCK_CKS_WDTC_WDTSCSID_1_640_HSIOSC	(1U)
#define	CLOCK_CKS_WDTC_WDTSCSID_1_800_HSIOSC	(2U)

/*------------------------------------------------------------------*/
/*	CKS_WDTS														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLOCK_CKS_WDTS_WDTSACT			( BIT1 + BIT0 )
#define	CLOCK_CKS_WDTS_WDTSACT_0		( BIT0 )
/* Bit setting value definition */
#define	CLOCK_CKS_WDTS_WDTSACT_1_20_HSIOSC		(0U)
#define	CLOCK_CKS_WDTS_WDTSACT_1_640_HSIOSC		(1U)
#define	CLOCK_CKS_WDTS_WDTSACT_1_800_HSIOSC		(2U)

#endif	/* MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B */

/*==============================================================================================*/
/*	struct address definition																	*/
/*==============================================================================================*/
#define	REG_CLOCK_ISO	(*(volatile Reg_Clock_IsoType *)(0xFF980000U))	/* Clock Controller Registers for ISO area */
#define	REG_CLOCK_AWO	(*(volatile Reg_Clock_AwoType *)(0xFF988000U))	/* Clock Controller Registers for AWO area */

/*----------------------------------------------------------------------------------------------*/
/*	register setting definition																	*/
/*----------------------------------------------------------------------------------------------*/
#define	MCU_CLOCK_PROTECT_DISABLE		( (uint32)0xA5A5A500U )			/* Disables write access of protected registers */
#define	MCU_CLOCK_PROTECT_ENABLE		( (uint32)0xA5A5A501U )			/* Enables write access of protected registers */

#endif	/* REG_CLOCK_H */
/*-- End Of File -------------------------------------------------------------------------------*/
