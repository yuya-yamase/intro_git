/* Reg_STBC-r04-307 */
/************************************************************************************************/
/*																								*/
/*		Standby Controller Register definition													*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

#ifndef	REG_STBC_H
#define	REG_STBC_H

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
	uint32	u4MSR_RSCFD;
	uint8	u1Dummy1[12];
	uint32	u4MSR_FLXA;
	uint8	u1Dummy2[12];
	uint32	u4MSR_GTM;
	uint8	u1Dummy3[12];
	uint32	u4MSR_ETNB;
	uint8	u1Dummy4[12];
	uint32	u4MSR_RSENT;
	uint8	u1Dummy5[12];
	uint32	u4MSR_MSPI;
	uint8	u1Dummy6[12];
	uint32	u4MSR_RLIN3;
	uint8	u1Dummy7[12];
	uint32	u4MSR_ADCJ_ISO;
	uint8	u1Dummy8[12];
	uint32	u4MSR_CXPI;
	uint8	u1Dummy9[12];
	uint32	u4MSR_MMCA;
	uint8	u1Dummy10[12];
	uint32	u4MSR_ENCA;
	uint8	u1Dummy11[12];
	uint32	u4MSR_PSI5;
	uint8	u1Dummy12[12];
	uint32	u4MSR_PSI5S;
	uint8	u1Dummy13[12];
	uint32	u4MSR_PWMD;
	uint8	u1Dummy14[12];
	uint32	u4MSR_RHSIF;
	uint8	u1Dummy15[12];
	uint32	u4MSR_RIIC;
	uint8	u1Dummy16[12];
	uint32	u4MSR_SCI3;
	uint8	u1Dummy17[28];
	uint32	u4MSR_TAPA;
	uint8	u1Dummy18[12];
	uint32	u4MSR_TAUD;
	uint8	u1Dummy19[12];
	uint32	u4MSR_TAUJ_ISO;
	uint8	u1Dummy20[12];
	uint32	u4MSR_TPBA;
	uint8	u1Dummy21[12];
	uint32	u4MSR_TSG3;
	uint8	u1Dummy22[28];
	uint32	u4MSR_OSTM;
	uint8	u1Dummy23[1404];
	uint32	u4STBCKCPROT;
	uint8	u1Dummy24[12];
	uint32	u4MSRKCPROT;

#elif ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
	uint32	u4MSR_RSCFD;
	uint8	u1Dummy1[12];
	uint32	u4MSR_FLXA;
	uint8	u1Dummy2[12];
	uint32	u4MSR_GTM;
	uint8	u1Dummy3[12];
	uint32	u4MSR_ETN;
	uint8	u1Dummy4[12];
	uint32	u4MSR_RSENT;
	uint8	u1Dummy5[12];
	uint32	u4MSR_MSPI;
	uint8	u1Dummy6[12];
	uint32	u4MSR_RLIN3;
	uint8	u1Dummy7[12];
	uint32	u4MSR_DSADC_CADC;
	uint8	u1Dummy8[4];
	uint32	u4MSR_ADCK_ISO;
	uint8	u1Dummy9[20];
	uint32	u4MSR_MMCA;
	uint8	u1Dummy10[12];
	uint32	u4MSR_ENCA;
	uint8	u1Dummy11[12];
	uint32	u4MSR_PSI5;
	uint8	u1Dummy12[12];
	uint32	u4MSR_PSI5S;
	uint8	u1Dummy13[28];
	uint32	u4MSR_RHSIF;
	uint32	u4MSR_RHSB;
	uint8	u1Dummy14[8];
	uint32	u4MSR_RIIC;
	uint8	u1Dummy15[28];
	uint32	u4MSR_SFMA;
	uint8	u1Dummy16[12];
	uint32	u4MSR_TAPA;
	uint8	u1Dummy17[12];
	uint32	u4MSR_TAUD;
	uint8	u1Dummy18[28];
	uint32	u4MSR_TPBA;
	uint8	u1Dummy19[12];
	uint32	u4MSR_TSG3;
	uint8	u1Dummy20[28];
	uint32	u4MSR_OSTM;
	uint8	u1Dummy21[44];
	uint32	u4MSR_ATU;
	uint8	u1Dummy22[12];
	uint32	u4MSR_DFE;
	uint8	u1Dummy23[12];
	uint32	u4MSR_DFP;
	uint8	u1Dummy24[12];
	uint32	u4MSR_RDC;
	uint8	u1Dummy25[12];
	uint32	u4MSR_FCOMP;
	uint8	u1Dummy26[12];
	uint32	u4MSR_EMU;
	uint8	u1Dummy27[28];
	uint32	u4MSR_HRPWM;
	uint8	u1Dummy28[76];
	uint32	u4MSR_DSMIF;
	uint8	u1Dummy29[1164];
	uint32	u4STBCKCPROT;
	uint8	u1Dummy30[12];
	uint32	u4MSRKCPROT;

#else	/* MCAL_SPAL_TARGET == MCAL_TARGET_RCARS4_G4MH */
	uint32	u4MSR_RSCFD;
	uint8	u1Dummy1[12];
	uint32	u4MSR_FLXA;
	uint8	u1Dummy2[28];
	uint32	u4MSR_ETNB;
	uint8	u1Dummy3[12];
	uint32	u4MSR_RSENT;
	uint8	u1Dummy4[12];
	uint32	u4MSR_MSPI;
	uint8	u1Dummy5[12];
	uint32	u4MSR_RLIN3;
	uint8	u1Dummy6[140];
	uint32	u4MSR_RIIC;
	uint8	u1Dummy7[60];
	uint32	u4MSR_TAUD;
	uint8	u1Dummy8[12];
	uint32	u4MSR_TAUJ_ISO;
	uint8	u1Dummy9[60];
	uint32	u4MSR_OSTM;
	uint8	u1Dummy10[1404];
	uint32	u4STBCKCPROT;
	uint8	u1Dummy11[12];
	uint32	u4MSRKCPROT;

#endif

} Reg_Stbc_IsoType;

typedef	struct {

#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
	uint32	u4STBC0PSC;
	uint32	u4STBC0STPT;
	uint32	u4PWRGD_CNT;
	uint8	u1Dummy1[244];
	uint32	u4IOHOLD0;
	uint8	u1Dummy2[4];
	uint32	u4IOHOLD2;
	uint8	u1Dummy3[244];
	uint32	u4MSR_ADCJ_AWO;
	uint8	u1Dummy4[12];
	uint32	u4MSR_RTCA;
	uint8	u1Dummy5[12];
	uint32	u4MSR_TAUJ_AWO;
	uint8	u1Dummy6[12];
	uint32	u4MSR_WDTB_AWO;

#elif ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
	uint32	u4STBC0PSC;
	uint32	u4STBC0STPT;
	uint32	u4PWRGD_CNT;
	uint8	u1Dummy1[244];
	uint32	u4IOHOLD0;
	uint32	u4IOHOLD1;
	uint8	u1Dummy2[248];
	uint32	u4MSR_ADCK_AWO;
	uint8	u1Dummy3[12];
	uint32	u4MSR_RTCA;
	uint8	u1Dummy4[12];
	uint32	u4MSR_TAUJ_AWO;
	uint8	u1Dummy5[12];
	uint32	u4MSR_WDTB_AWO;

#else	/* MCAL_SPAL_TARGET == MCAL_TARGET_RCARS4_G4MH */
	uint32	u4STBC0PSC;
	uint8	u1Dummy1[252];
	uint32	u4IOHOLD0;
	uint8	u1Dummy2[268];
	uint32	u4MSR_RTCA;
	uint8	u1Dummy3[12];
	uint32	u4MSR_TAUJ_AWO;
	uint8	u1Dummy4[12];
	uint32	u4MSR_WDTB_AWO;

#endif

} Reg_Stbc_AwoType;

/* WUFn_Ax register */
typedef	struct {
	union {
		uint32	u4Data;
		struct {
			uint32	xWUFn0		:1;
			uint32	xWUFn1		:1;
			uint32	xWUFn2		:1;
			uint32	xWUFn3		:1;
			uint32	xWUFn4		:1;
			uint32	xWUFn5		:1;
			uint32	xWUFn6		:1;
			uint32	xWUFn7		:1;
			uint32	xWUFn8		:1;
			uint32	xWUFn9		:1;
			uint32	xWUFn10		:1;
			uint32	xWUFn11		:1;
			uint32	xWUFn12		:1;
			uint32	xWUFn13		:1;
			uint32	xWUFn14		:1;
			uint32	xWUFn15		:1;
			uint32	xWUFn16		:1;
			uint32	xWUFn17		:1;
			uint32	xWUFn18		:1;
			uint32	xWUFn19		:1;
			uint32	xWUFn20		:1;
			uint32	xWUFn21		:1;
			uint32	xWUFn22		:1;
			uint32	xWUFn23		:1;
			uint32	xWUFn24		:1;
			uint32	xWUFn25		:1;
			uint32	xWUFn26		:1;
			uint32	xWUFn27		:1;
			uint32	xWUFn28		:1;
			uint32	xWUFn29		:1;
			uint32	xWUFn30		:1;
			uint32	xWUFn31		:1;
		} stBit;
	} unWUFn;
} Stbc_WUFn_Ax;

/* WUFMSKn_Ax Register */
typedef	struct {
	union {
		uint32	u4Data;
		struct {
			uint32	xWUFMSKn0		:1;
			uint32	xWUFMSKn1		:1;
			uint32	xWUFMSKn2		:1;
			uint32	xWUFMSKn3		:1;
			uint32	xWUFMSKn4		:1;
			uint32	xWUFMSKn5		:1;
			uint32	xWUFMSKn6		:1;
			uint32	xWUFMSKn7		:1;
			uint32	xWUFMSKn8		:1;
			uint32	xWUFMSKn9		:1;
			uint32	xWUFMSKn10		:1;
			uint32	xWUFMSKn11		:1;
			uint32	xWUFMSKn12		:1;
			uint32	xWUFMSKn13		:1;
			uint32	xWUFMSKn14		:1;
			uint32	xWUFMSKn15		:1;
			uint32	xWUFMSKn16		:1;
			uint32	xWUFMSKn17		:1;
			uint32	xWUFMSKn18		:1;
			uint32	xWUFMSKn19		:1;
			uint32	xWUFMSKn20		:1;
			uint32	xWUFMSKn21		:1;
			uint32	xWUFMSKn22		:1;
			uint32	xWUFMSKn23		:1;
			uint32	xWUFMSKn24		:1;
			uint32	xWUFMSKn25		:1;
			uint32	xWUFMSKn26		:1;
			uint32	xWUFMSKn27		:1;
			uint32	xWUFMSKn28		:1;
			uint32	xWUFMSKn29		:1;
			uint32	xWUFMSKn30		:1;
			uint32	xWUFMSKn31		:1;
		} stBit;
	} unWUFMSKn;
} Stbc_WUFMSKn_Ax;

/* WUFCn_Ax Register */
typedef	struct {
	union {
		uint32	u4Data;
		struct {
			uint32	xWUFCn0			:1;
			uint32	xWUFCn1			:1;
			uint32	xWUFCn2			:1;
			uint32	xWUFCn3			:1;
			uint32	xWUFCn4			:1;
			uint32	xWUFCn5			:1;
			uint32	xWUFCn6			:1;
			uint32	xWUFCn7			:1;
			uint32	xWUFCn8			:1;
			uint32	xWUFCn9			:1;
			uint32	xWUFCn10		:1;
			uint32	xWUFCn11		:1;
			uint32	xWUFCn12		:1;
			uint32	xWUFCn13		:1;
			uint32	xWUFCn14		:1;
			uint32	xWUFCn15		:1;
			uint32	xWUFCn16		:1;
			uint32	xWUFCn17		:1;
			uint32	xWUFCn18		:1;
			uint32	xWUFCn19		:1;
			uint32	xWUFCn20		:1;
			uint32	xWUFCn21		:1;
			uint32	xWUFCn22		:1;
			uint32	xWUFCn23		:1;
			uint32	xWUFCn24		:1;
			uint32	xWUFCn25		:1;
			uint32	xWUFCn26		:1;
			uint32	xWUFCn27		:1;
			uint32	xWUFCn28		:1;
			uint32	xWUFCn29		:1;
			uint32	xWUFCn30		:1;
			uint32	xWUFCn31		:1;
		} stBit;
	} unWUFCn;
} Stbc_WUFCn_Ax;


/* STBC WUF0_ A0-related registers */
typedef	struct {
	/* WUF0_A0 register */
	Stbc_WUFn_Ax	stWUF0_A0;

	/* WUFMSK0_A0 register */
	Stbc_WUFMSKn_Ax	stWUFMSK0_A0;

	/* WUFC0_A0 register */
	Stbc_WUFCn_Ax	stWUFC0_A0;

} Stbc_WUF0A0;


/* STBC WUF0_ A1-related register */
typedef	struct {
	/* WUF0_A1 register */
	Stbc_WUFn_Ax	stWUF0_A1;

	/* WUFMSK0_A1 register */
	Stbc_WUFMSKn_Ax	stWUFMSK0_A1;

	/* WUFC0_A1 register */
	Stbc_WUFCn_Ax	stWUFC0_A1;

} Stbc_WUF0A1;


/* STBC TAUJ-related registers */
typedef	struct {
	/* WUF0_A2 register */
	Stbc_WUFn_Ax	stWUF0_A2;

	/* WUFMSK0_A2 register */
	Stbc_WUFMSKn_Ax	stWUFMSK0_A2;

	/* WUFC0_A2 register */
	Stbc_WUFCn_Ax	stWUFC0_A2;

} Stbc_TAUJ;

/*==============================================================================================*/
/*	struct address definition																	*/
/*==============================================================================================*/
#define	REG_STBC_ISO	(*(volatile Reg_Stbc_IsoType *)(0xFF981000U))	/* Standby Controller Registers for ISO area */
#define	REG_STBC_AWO	(*(volatile Reg_Stbc_AwoType *)(0xFF988C00U))	/* Standby Controller Registers for AWO area */

#define	REG_STBC_WUF0A0_ADR				((uint32)(0xFF98E000U))										/* WUF0_A0 Address */
#define	REG_STBC_WUF0A1_ADR				((uint32)(0xFF98E010U))										/* WUF0_A1 Address */
#define	REG_STBC_TAUJ_ADR				((uint32)(0xFF98E020U))										/* WUF0_A2 Address */

/*  STBC WUF0A0 related register address */
#define REG_STBC_WUF0A0					(*(volatile Stbc_WUF0A0*)	REG_STBC_WUF0A0_ADR)
/*  STBC WUFA10 related register address */
#define REG_STBC_WUF0A1					(*(volatile Stbc_WUF0A1*)	REG_STBC_WUF0A1_ADR)
/*  EICn TAUJ related register address */
#define	REG_STBC_TAUJ					(*(volatile Stbc_TAUJ*)	REG_STBC_TAUJ_ADR)

/* IOHOLD, STBCKCPROT-related register address */
#define REG_STBC_STBCKCPROT				((volatile uint32 *) 0xFF981700U)	/* STBCKCPROT register address in U2x */
#define REG_STBC_IOHOLD0				((volatile uint32 *) 0xFF988D00U)	/* IOHOLD0 register address in IOHOLD0 */
#if MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A
#define REG_STBC_IOHOLD2				((volatile uint32 *) 0xFF988D08U)	/* IOHOLD2 register address in IOHOLD2 */
#else
#define REG_STBC_IOHOLD1				((volatile uint32 *) 0xFF988D04U)	/* IOHOLD2 register address in IOHOLD1 */
#endif /* MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A */
/* Value to write to register */
#define REG_STBC_STBCKCPROT_WRITE_ENABLE	((uint32)0xA5A5A501U)				/* enable to write IOHOLD0 */
#define REG_STBC_STBCKCPROT_WRITE_DISABLE	((uint32)0xA5A5A500U)				/* disable to write IOHOLD0 */
#define REG_STBC_RELEASE_IOBUFFERHOLD		((uint32)0x00000000U)				/* release I/O buffer hold state */

/*----------------------------------------------------------------------------------------------*/
/*	register setting definition																	*/
/*----------------------------------------------------------------------------------------------*/
#define	MCU_MS_CLOCK_SUPPLIED			( 0x0U )	/* The peripheral in the stop modes is supplied */
#define	MCU_MS_CLOCK_STOPPED			( 0x1U )	/* The peripheral in the stop modes is stopped */

#define	MCU_STPMSK_CLOCK_STOPPED		( 0x0U )	/* The peripheral in the STOP, DeepSTOP and Cyclic STOP mode is stopped */
#define	MCU_STPMSK_CLOCK_SUPPLIED		( 0x1U )	/* The peripheral in the STOP, DeepSTOP and Cyclic STOP mode is supplied */

#define	MCU_STBC0PSC_DEEPSTOP_MODE		( 0x2U )	/* Transition to DeepSTOP mode */

#define	MCU_PWRGD_CNT_PWRGD_CNT_MIN		( 0x000U )	/* Waiting minimum period for ISOVDD to be stable */
#define	MCU_PWRGD_CNT_PWRGD_CNT_MAX		( 0xFFFU )	/* Waiting maximum period for ISOVDD to be stable */
#define	STBC_PWRGD_CNT_PWRGD_CNT		( BIT11 + BIT10 + BIT9 + BIT8 + BIT7 + BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0 )

#define	MSR_RSCFD_2_RESERVED_BIT	( 0x1U )	/* RSCFD_2 value after reset */
#define	MSR_FLXA_1_RESERVED_BIT		( 0x1U )	/* FLXA_1 value after reset */
#define	MSR_ETN_2_RESERVED_BIT		( 0x1U )	/* ETN_2 value after reset */
#define	MSR_PSI5_4_RESERVED_BIT		( 0x1U )	/* PSI5_4 value after reset */
#define	MSR_OSTM_6_RESERVED_BIT		( 0x1U )	/* OSTM_6 value after reset */
#define	MSR_OSTM_7_RESERVED_BIT		( 0x1U )	/* OSTM_6 value after reset */
#define	MSR_OSTM_8_RESERVED_BIT		( 0x1U )	/* OSTM_6 value after reset */
#define	MSR_OSTM_9_RESERVED_BIT		( 0x1U )	/* OSTM_6 value after reset */

#define	MCU_STBC_PROTECT_DISABLE		( (uint32)0xA5A5A500U )	/* Disables write access of protected registers */
#define	MCU_STBC_PROTECT_ENABLE			( (uint32)0xA5A5A501U )	/* Enables write access of protected registers */

#define	MSR_RSCFD_MS_RSCFD_0			( BIT0 )
#define	MSR_RSCFD_MS_RSCFD_1			( BIT1 )
#define	MSR_RSCFD_MS_RSCFD_2			( BIT2 )
#define	MSR_RSCFD_STPMSK_RSCFD			( BIT31)
#define	MSR_FLXA_MS_FLXA_0				( BIT0 )
#define	MSR_FLXA_MS_FLXA_1				( BIT1 )
#define	MSR_RSENT_MS_RSENT_0			( BIT0 )
#define	MSR_RSENT_MS_RSENT_1			( BIT1 )
#define	MSR_RSENT_MS_RSENT_2			( BIT2 )
#define	MSR_RSENT_MS_RSENT_3			( BIT3 )
#define	MSR_RSENT_MS_RSENT_4			( BIT4 )
#define	MSR_RSENT_MS_RSENT_5			( BIT5 )
#define	MSR_RSENT_MS_RSENT_6			( BIT6 )
#define	MSR_RSENT_MS_RSENT_7			( BIT7 )
#define	MSR_RSENT_MS_RSENT_8			( BIT8 )
#define	MSR_RSENT_MS_RSENT_9			( BIT9 )
#define	MSR_RSENT_MS_RSENT_10			( BIT10 )
#define	MSR_RSENT_MS_RSENT_11			( BIT11 )
#define	MSR_RSENT_MS_RSENT_12			( BIT12 )
#define	MSR_RSENT_MS_RSENT_13			( BIT13 )
#define	MSR_RSENT_MS_RSENT_14			( BIT14 )
#define	MSR_RSENT_MS_RSENT_15			( BIT15 )
#define	MSR_RSENT_MS_RSENT_16			( BIT16 )
#define	MSR_RSENT_MS_RSENT_17			( BIT17 )
#define	MSR_RSENT_MS_RSENT_18			( BIT18 )
#define	MSR_RSENT_MS_RSENT_19			( BIT19 )
#define	MSR_RSENT_MS_RSENT_20			( BIT20 )
#define	MSR_RSENT_MS_RSENT_21			( BIT21 )
#define	MSR_RSENT_MS_RSENT_22			( BIT22 )
#define	MSR_RSENT_MS_RSENT_23			( BIT23 )
#define	MSR_RSENT_MS_RSENT_24			( BIT24 )
#define	MSR_RSENT_MS_RSENT_25			( BIT25 )
#define	MSR_RSENT_MS_RSENT_26			( BIT26 )
#define	MSR_RSENT_MS_RSENT_27			( BIT27 )
#define	MSR_RSENT_MS_RSENT_28			( BIT28 )
#define	MSR_RSENT_MS_RSENT_29			( BIT29 )
#define	MSR_MSPI_MS_MSPI_0				( BIT0 )
#define	MSR_MSPI_MS_MSPI_1				( BIT1 )
#define	MSR_MSPI_MS_MSPI_2				( BIT2 )
#define	MSR_MSPI_MS_MSPI_3				( BIT3 )
#define	MSR_MSPI_MS_MSPI_4				( BIT4 )
#define	MSR_MSPI_MS_MSPI_5				( BIT5 )
#define	MSR_MSPI_MS_MSPI_6				( BIT6 )
#define	MSR_MSPI_MS_MSPI_7				( BIT7 )
#define	MSR_MSPI_MS_MSPI_8				( BIT8 )
#define	MSR_MSPI_MS_MSPI_9				( BIT9 )
#define	MSR_RLIN3_MS_RLIN3_0			( BIT0 )
#define	MSR_RLIN3_MS_RLIN3_1			( BIT1 )
#define	MSR_RLIN3_MS_RLIN3_2			( BIT2 )
#define	MSR_RLIN3_MS_RLIN3_3			( BIT3 )
#define	MSR_RLIN3_MS_RLIN3_4			( BIT4 )
#define	MSR_RLIN3_MS_RLIN3_5			( BIT5 )
#define	MSR_RLIN3_MS_RLIN3_6			( BIT6 )
#define	MSR_RLIN3_MS_RLIN3_7			( BIT7 )
#define	MSR_RLIN3_MS_RLIN3_8			( BIT8 )
#define	MSR_RLIN3_MS_RLIN3_9			( BIT9 )
#define	MSR_RLIN3_MS_RLIN3_10			( BIT10 )
#define	MSR_RLIN3_MS_RLIN3_11			( BIT11 )
#define	MSR_RLIN3_MS_RLIN3_12			( BIT12 )
#define	MSR_RLIN3_MS_RLIN3_13			( BIT13 )
#define	MSR_RLIN3_MS_RLIN3_14			( BIT14 )
#define	MSR_RLIN3_MS_RLIN3_15			( BIT15 )
#define	MSR_RLIN3_MS_RLIN3_16			( BIT16 )
#define	MSR_RLIN3_MS_RLIN3_17			( BIT17 )
#define	MSR_RLIN3_MS_RLIN3_18			( BIT18 )
#define	MSR_RLIN3_MS_RLIN3_19			( BIT19 )
#define	MSR_RLIN3_MS_RLIN3_20			( BIT20 )
#define	MSR_RLIN3_MS_RLIN3_21			( BIT21 )
#define	MSR_RLIN3_MS_RLIN3_22			( BIT22 )
#define	MSR_RLIN3_MS_RLIN3_23			( BIT23 )
#define	MSR_RLIN3_STPMSK_RLIN3			( BIT31 )
#define	MSR_RIIC_MS_RIIC_0				( BIT0 )
#define	MSR_RIIC_MS_RIIC_1				( BIT1 )
#define	MSR_TAUD_MS_TAUD_0				( BIT0 )
#define	MSR_TAUD_MS_TAUD_1				( BIT1 )
#define	MSR_TAUD_MS_TAUD_2				( BIT2 )
#define	MSR_TAUD_MS_TAUD_3				( BIT3 )
#define	MSR_OSTM_MS_OSTM_0				( BIT0 )
#define	MSR_OSTM_MS_OSTM_1				( BIT1 )
#define	MSR_OSTM_MS_OSTM_2				( BIT2 )
#define	MSR_OSTM_MS_OSTM_3				( BIT3 )
#define	MSR_OSTM_MS_OSTM_4				( BIT4 )
#define	MSR_OSTM_MS_OSTM_5				( BIT5 )
#define	MSR_OSTM_MS_OSTM_6				( BIT6 )
#define	MSR_OSTM_MS_OSTM_7				( BIT7 )
#define	MSR_OSTM_MS_OSTM_8				( BIT8 )
#define	MSR_OSTM_MS_OSTM_9				( BIT9 )
#define	MSR_RTCA_MS_RTCA_0				( BIT0 )
#define	MSR_RTCA_STPMSK_RTCA			( BIT31 )
#define	MSR_TAUJ_AWO_MS_TAUJ_2			( BIT0 )
#define	MSR_TAUJ_AWO_MS_TAUJ_3			( BIT1 )
#define	MSR_TAUJ_AWO_STPMSK_TAUJ_AWO	( BIT31 )
#define	MSR_WDTB_AWO_STPMSK_WDTB_AWO	( BIT31 )

#define	MSR_ETNB_MS_ETNB_0				( BIT0 )
#define	MSR_ETNB_MS_ETNB_1				( BIT1 )
#define	MSR_TAUJ_ISO_MS_TAUJ_0			( BIT0 )
#define	MSR_TAUJ_ISO_MS_TAUJ_1			( BIT1 )

#define	MSR_GTM_MS_GTM_0				( BIT0 )
#define	MSR_MMCA_MS_MMCA_0				( BIT0 )
#define	MSR_ENCA_MS_ENCA_0				( BIT0 )
#define	MSR_ENCA_MS_ENCA_1				( BIT1 )
#define	MSR_PSI5_MS_PSI5_0				( BIT0 )
#define	MSR_PSI5_MS_PSI5_1				( BIT1 )
#define	MSR_PSI5_MS_PSI5_2				( BIT2 )
#define	MSR_PSI5_MS_PSI5_3				( BIT3 )
#define	MSR_PSI5_MS_PSI5_4				( BIT4 )
#define	MSR_PSI5_MS_PSI5_5				( BIT5 )
#define	MSR_PSI5S_MS_PSI5S_0			( BIT0 )
#define	MSR_PSI5S_MS_PSI5S_1			( BIT1 )
#define	MSR_RHSIF_MS_RHSIF_0			( BIT0 )
#define	MSR_RHSIF_MS_RHSIF_1			( BIT1 )
#define	MSR_TAPA_MS_TAPA_0				( BIT0 )
#define	MSR_TAPA_MS_TAPA_1				( BIT1 )
#define	MSR_TAPA_MS_TAPA_2				( BIT2 )
#define	MSR_TAPA_MS_TAPA_3				( BIT3 )
#define	MSR_TAPA_MS_TAPA_4				( BIT4 )
#define	MSR_TAPA_MS_TAPA_5				( BIT5 )
#define	MSR_TPBA_MS_TPBA_0				( BIT0 )
#define	MSR_TPBA_MS_TPBA_1				( BIT1 )
#define	MSR_TSG3_MS_TSG3_0				( BIT0 )
#define	MSR_TSG3_MS_TSG3_1				( BIT1 )
#define	MSR_TSG3_MS_TSG3_2				( BIT2 )

#define	MSR_ADCJ_ISO_MS_ADCJ_0			( BIT0 )
#define	MSR_ADCJ_ISO_MS_ADCJ_1			( BIT1 )
#define	MSR_CXPI_MS_CXPI_0				( BIT0 )
#define	MSR_CXPI_MS_CXPI_1				( BIT1 )
#define	MSR_CXPI_MS_CXPI_2				( BIT2 )
#define	MSR_CXPI_MS_CXPI_3				( BIT3 )
#define	MSR_PWMD_MS_PWMD_0				( BIT0 )
#define	MSR_SCI3_MS_SCI3_0				( BIT0 )
#define	MSR_SCI3_MS_SCI3_1				( BIT1 )
#define	MSR_SCI3_MS_SCI3_2				( BIT2 )
#define	MSR_ADCJ_AWO_MS_ADCJ_2			( BIT0 )
#define	MSR_ADCJ_AWO_STPMSK_ADCJ		( BIT31 )

#define	MSR_ETN_MS_ETN_0				( BIT0 )
#define	MSR_ETN_MS_ETN_1				( BIT1 )
#define	MSR_ETN_MS_ETN_2				( BIT2 )
#define	MSR_ETN_MS_ETN_4				( BIT4 )
#define	MSR_DSADC_CADC_MS_DSADC_0		( BIT0 )
#define	MSR_DSADC_CADC_MS_DSADC_1		( BIT1 )
#define	MSR_DSADC_CADC_MS_DSADC_2		( BIT2 )
#define	MSR_DSADC_CADC_MS_DSADC_3		( BIT3 )
#define	MSR_DSADC_CADC_MS_DSADC_4		( BIT4 )
#define	MSR_DSADC_CADC_MS_DSADC_5		( BIT5 )
#define	MSR_DSADC_CADC_MS_DSADC_6		( BIT6 )
#define	MSR_ADCK_ISO_MS_ADCK_ISO_0		( BIT0 )
#define	MSR_ADCK_ISO_MS_ADCK_ISO_1		( BIT1 )
#define	MSR_ADCK_ISO_MS_ADCK_ISO_2		( BIT2 )
#define	MSR_ADCK_ISO_MS_ADCK_ISO_3		( BIT3 )
#define	MSR_ADCK_ISO_MS_ADCK_ISO_4		( BIT4 )
#define	MSR_ADCK_ISO_MS_ADCK_ISO_5		( BIT5 )
#define	MSR_ADCK_ISO_MS_ADCK_ISO_6		( BIT6 )
#define	MSR_ADCK_ISO_MS_ADCK_ISO_7		( BIT7 )
#define	MSR_RHSB_MS_RHSB_0				( BIT0 )
#define	MSR_RHSB_MS_RHSB_1				( BIT1 )
#define	MSR_RHSB_MS_RHSB_2				( BIT2 )
#define	MSR_RHSB_MS_RHSB_3				( BIT3 )
#define	MSR_SFMA_MS_SFMA_0				( BIT0 )
#define	MSR_ATU_MS_ATU_0				( BIT0 )
#define	MSR_DFE_MS_DFE_0				( BIT0 )
#define	MSR_RDC_MS_RDC_0				( BIT0 )
#define	MSR_RDC_MS_RDC_1				( BIT1 )
#define	MSR_RDC_MS_RDC_2				( BIT2 )
#define	MSR_RDC_MS_RDC_3				( BIT3 )
#define	MSR_FCOMP_MS_FCOMP_0			( BIT0 )
#define	MSR_FCOMP_MS_FCOMP_1			( BIT1 )
#define	MSR_FCOMP_MS_FCOMP_2			( BIT2 )
#define	MSR_FCOMP_MS_FCOMP_3			( BIT3 )
#define	MSR_FCOMP_MS_FCOMP_4			( BIT4 )
#define	MSR_FCOMP_MS_FCOMP_5			( BIT5 )
#define	MSR_FCOMP_MS_FCOMP_6			( BIT6 )
#define	MSR_FCOMP_MS_FCOMP_7			( BIT7 )
#define	MSR_FCOMP_MS_FCOMP_8			( BIT8 )
#define	MSR_FCOMP_MS_FCOMP_9			( BIT9 )
#define	MSR_FCOMP_MS_FCOMP_10			( BIT10 )
#define	MSR_EMU_MS_EMU_0				( BIT0 )
#define	MSR_EMU_MS_EMU_1				( BIT1 )
#define	MSR_HRPWM_MS_HRPWM_0			( BIT0 )
#define	MSR_ADCK_AWO_MS_ADCK_AWO_0		( BIT0 )
#define	MSR_ADCK_AWO_STPMSK_ADCK		( BIT31 )
#define	MSR_WDTB_AWO_MS_WDTB_AWO_0		( BIT0 )

/* WUFn_Ax register bit definition */
#define	REG_WUFN_WAKEUP_NOT_GENERATED		((uint32)(0U))								/* Wake-Up Factor is not generated */
#define	REG_WUFN_WAKEUP_GENERATED			((uint32)(1U))								/* Wake-Up Factor is generated */

/* WUFMSKn_Ax register bit definition */
#define	REG_WUFMSKN_WFACTOR_ENABLE			((uint32)(0U))								/* Wake-Up Factor is enabled */
#define	REG_WUFMSKN_WFACTOR_DISABLE			((uint32)(1U))								/* Wake-Up Factor is disabled */

/* WUFCn_Ax register bit definition */
#define	REG_WUFCN_NOT_MODIFIED				((uint32)(0U))								/* WUFy is not modified */
#define	REG_WUFCN_CLEAR						((uint32)(1U))								/* WUFy is cleared */
	#define	REG_WUFCN0_CLEAR				((uint32)(0x00000001U))						/* WUFC0 is cleared */
	#define	REG_WUFCN1_CLEAR				((uint32)(0x00000002U))						/* WUFC1 is cleared */
	#define	REG_WUFCN2_CLEAR				((uint32)(0x00000004U))						/* WUFC2 is cleared */
	#define	REG_WUFCN3_CLEAR				((uint32)(0x00000008U))						/* WUFC3 is cleared */
	#define	REG_WUFCN4_CLEAR				((uint32)(0x00000010U))						/* WUFC4 is cleared */
	#define	REG_WUFCN5_CLEAR				((uint32)(0x00000020U))						/* WUFC5 is cleared */
	#define	REG_WUFCN6_CLEAR				((uint32)(0x00000040U))						/* WUFC6 is cleared */
	#define	REG_WUFCN7_CLEAR				((uint32)(0x00000080U))						/* WUFC7 is cleared */
	#define	REG_WUFCN8_CLEAR				((uint32)(0x00000100U))						/* WUFC8 is cleared */
	#define	REG_WUFCN9_CLEAR				((uint32)(0x00000200U))						/* WUFC9 is cleared */
	#define	REG_WUFCN10_CLEAR				((uint32)(0x00000400U))						/* WUFC10 is cleared */
	#define	REG_WUFCN11_CLEAR				((uint32)(0x00000800U))						/* WUFC11 is cleared */
	#define	REG_WUFCN12_CLEAR				((uint32)(0x00001000U))						/* WUFC12 is cleared */
	#define	REG_WUFCN13_CLEAR				((uint32)(0x00002000U))						/* WUFC13 is cleared */
	#define	REG_WUFCN14_CLEAR				((uint32)(0x00004000U))						/* WUFC14 is cleared */
	#define	REG_WUFCN15_CLEAR				((uint32)(0x00008000U))						/* WUFC15 is cleared */
	#define	REG_WUFCN16_CLEAR				((uint32)(0x00010000U))						/* WUFC16 is cleared */
	#define	REG_WUFCN17_CLEAR				((uint32)(0x00020000U))						/* WUFC17 is cleared */
	#define	REG_WUFCN18_CLEAR				((uint32)(0x00040000U))						/* WUFC18 is cleared */
	#define	REG_WUFCN19_CLEAR				((uint32)(0x00080000U))						/* WUFC19 is cleared */
	#define	REG_WUFCN20_CLEAR				((uint32)(0x00100000U))						/* WUFC20 is cleared */
	#define	REG_WUFCN21_CLEAR				((uint32)(0x00200000U))						/* WUFC21 is cleared */
	#define	REG_WUFCN22_CLEAR				((uint32)(0x00400000U))						/* WUFC22 is cleared */
	#define	REG_WUFCN23_CLEAR				((uint32)(0x00800000U))						/* WUFC23 is cleared */
	#define	REG_WUFCN24_CLEAR				((uint32)(0x01000000U))						/* WUFC24 is cleared */
	#define	REG_WUFCN25_CLEAR				((uint32)(0x02000000U))						/* WUFC25 is cleared */
	#define	REG_WUFCN26_CLEAR				((uint32)(0x04000000U))						/* WUFC26 is cleared */
	#define	REG_WUFCN27_CLEAR				((uint32)(0x08000000U))						/* WUFC27 is cleared */
	#define	REG_WUFCN28_CLEAR				((uint32)(0x10000000U))						/* WUFC28 is cleared */
	#define	REG_WUFCN29_CLEAR				((uint32)(0x20000000U))						/* WUFC29 is cleared */
	#define	REG_WUFCN30_CLEAR				((uint32)(0x40000000U))						/* WUFC30 is cleared */
	#define	REG_WUFCN31_CLEAR				((uint32)(0x80000000U))						/* WUFC31 is cleared */

#endif	/* REG_STBC_H */
/*-- End Of File -------------------------------------------------------------------------------*/
