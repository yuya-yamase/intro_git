/* Reg_ADC-r04-303 */
/************************************************************************************************/
/*																								*/
/*		ADC register definition for RH850U2A/U2B												*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/
#ifndef REG_ADC_H
#define REG_ADC_H

/*==============================================================================================*/
/* include files																				*/
/*==============================================================================================*/
#include "Platform_Types.h"
#include "Mcal_SpalCmn.h"

/*==============================================================================================*/
/* defines / data types / structs / unions	/ macros											*/
/*==============================================================================================*/
/*--------------------------------------------------------------------------*/
/* defines - number of units, sg ...										*/
/*--------------------------------------------------------------------------*/
#define ADC_CHANNEL_NUM				(64U)		/* Max number of Virtual channel	*/
#define	ADC_VCT_NUM					(8U)		/* Number of virtual channel lower and lower limit Tables per module (y) */
#define	ADC_SELB_MODULE_NUM			(1U)		/* Number of SELB module	*/
#define	ADC_UNITA_HW_TRG_NUM		(6U)		/* SGTSEL:Scan Group x Start Trigger Num	*/

#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B) 
#define ADC_SGDIAG_CHANNEL_NUM	(3U)
#define	ADC_AIR_MODULE_NUM		(1U)
/* AIR interrupt	*/
#define	ADC_AIR_ISELR_0			(0U)
#define	ADC_AIR_ISELR_1			(1U)
#define	ADC_AIR_ISELR_NUM		(2U)
/* AIR DMA			*/
#define	ADC_AIR_DSELR_0			(0U)
#define	ADC_AIR_DSELR_1			(1U)
#define	ADC_AIR_DSELR_NUM		(2U)
#endif

/*--------------------------------------------------------------------------*/
/* defines - HW Unit														*/
/*--------------------------------------------------------------------------*/
#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2A)
	#define	ADC_HWUNIT0			(0U)
	#define	ADC_HWUNIT1			(1U)
	#define	ADC_HWUNIT2			(2U)
	#define	ADC_HWUNIT_NUM		(3U)
#elif (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B) 
	#if ((MCAL_PKG_TARGET==MCAL_PKG_U2B10_292PIN) || (MCAL_PKG_TARGET==MCAL_PKG_U2B6_292PIN))
		#define	ADC_HWUNIT0			(0U)
		#define	ADC_HWUNIT1			(1U)
		#define	ADC_HWUNIT2			(2U)
		#define	ADC_HWUNIT_NUM		(3U)
	#elif ((MCAL_PKG_TARGET==MCAL_PKG_U2B10_468PIN) || (MCAL_PKG_TARGET==MCAL_PKG_U2B10_373PIN))
		#define	ADC_HWUNIT0			(0U)
		#define	ADC_HWUNIT1			(1U)
		#define	ADC_HWUNIT2			(2U)
		#define	ADC_HWUNIT3			(3U)
		#define	ADC_HWUNIT_NUM		(4U)
	#else
		/* MCAL_PKG_U2B24_468PIN or MCAL_PKG_U2B24_373PIN	*/
		/* MCAL_PKG_U2B20_468PIN or MCAL_PKG_U2B20_373PIN	*/
		#define	ADC_HWUNIT0			(0U)
		#define	ADC_HWUNIT1			(1U)
		#define	ADC_HWUNIT2			(2U)
		#define	ADC_HWUNIT3			(3U)
		#define	ADC_HWUNITA			(4U)
		#define	ADC_HWUNIT_NUM		(5U)
	#endif
#endif

/*--------------------------------------------------------------------------*/
/* defines - HW Unit with T&H												*/
/*--------------------------------------------------------------------------*/
#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2A)
	#define	ADC_HWUNIT0_WTH			(0U)
	#define	ADC_HWUNIT1_WTH			(1U)
	#define	ADC_HWUNIT_WTH_NUM		(2U)
#elif (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B) 
	#define	ADC_HWUNIT0_WTH			(0U)
	#define	ADC_HWUNIT1_WTH			(1U)
	#define	ADC_HWUNIT2_WTH			(2U)
	#define	ADC_HWUNIT_WTH_NUM		(3U)
#endif

/*--------------------------------------------------------------------------*/
/* defines - T&H															*/
/*--------------------------------------------------------------------------*/
/* T&H Num	*/
#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2A)
	#define ADC_TH_NUM				(4U)
#elif (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B) 
	#define ADC_TH_NUM				(6U)
#endif

/* T&H Group	*/
#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2A)
	#define ADC_TH_GRP_A			(0U)
	#define ADC_TH_GRP_NUM			(1U)
#elif (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B) 
	#define ADC_TH_GRP_A			(0U)
	#define ADC_TH_GRP_B			(1U)
	#define ADC_TH_GRP_NUM			(2U)
#endif
#define ADC_TH_GRP_NONE				(0xffU)	/* T&H Unused	*/

/*--------------------------------------------------------------------------*/
/* defines - Scan Group														*/
/*--------------------------------------------------------------------------*/
#define ADC_SG0					(0U)
#define ADC_SG1					(1U)
#define ADC_SG2					(2U)
#define ADC_SG3					(3U)
#define ADC_SG4					(4U)
#define ADC_SG_NUM				(5U)
#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B) 
#define ADC_SG_DIAG				(5U)
#endif

/*==============================================================================================*/
/*	register type definition																	*/
/*==============================================================================================*/

/***************************/
/*           ADC           */
/***************************/
/* 0xFFCA0000 -  0xFFCA08BC */
typedef	struct
{
	struct
	{
		uint32	u4VCR[ADC_CHANNEL_NUM];						/* 0xFFCA0000 - 0xFFCA0100 *//* Virtual Channel Registers n */

		#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) 

			uint8	u1Dummy1[0xFFCA0180U - 0xFFCA0100U];		/* 0xFFCA0100 - 0xFFCA0180 */

			uint32	u4PWDVCR;									/* 0xFFCA0180 - 0xFFCA0184 */

			uint8	u1Dummy2[0xFFCA01A0U - 0xFFCA0184U];		/* 0xFFCA0184 - 0xFFCA01A0 */

		#elif	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )	/* ADC0, ADC1, ADC2, ADC3 only */

			uint8	u1Dummy1[0xFFCA0184U - 0xFFCA0100U];		/* 0xFFCA0100 - 0xFFCA0184 */

			struct{
				uint8	u1data;									/* 0xFFCA0184 - 0xFFCA0185 */

				uint8	u1Dummy2[0xFFCA0188U - 0xFFCA0185U];	/* 0xFFCA0185 - 0xFFCA0188 */

			}stSGDIAGVCR[ADC_SGDIAG_CHANNEL_NUM];				/* 0xFFCA0184 - 0xFFCA0190 */

			uint8	u1Dammy3[0xFFCA01A0U - 0xFFCA0190U];			/* 0xFFCA0190 - 0xFFCA01A0 */

		#endif

		uint16	u2DR[ADC_CHANNEL_NUM];						/* 0xFFCA01A0 - 0xFFCA0220 *//* Data Registers n */

		#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) 

			uint8	u1Dummy4[0xFFCA0260U - 0xFFCA0220U];		/* 0xFFCA0220 - 0xFFCA0260 */

			uint16	u2PWDDR;									/* 0xFFCA0260 - 0xFFCA0262 *//* PWM-Diag data register */

			uint8	u1Dummy5[0xFFCA0280U - 0xFFCA0262U];		/* 0xFFCA0262 - 0xFFCA0280 */

		#elif	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )	/* ADC0, ADC1, ADC2, ADC3 only */

			uint8	u1Dummy4[0xFFCA0264U - 0xFFCA0220U];		/* 0xFFCA0220 - 0xFFCA0264 */

			uint32	u4SGDIAGDR0_1;								/* 0xFFCA0264 - 0xFFCA0268 */

			uint16	u2SGDIAGDR2;								/* 0xFFCA0268 - 0xFFCA026A */

			uint8	u1Dammy5[0xFFCA026CU - 0xFFCA026AU];			/* 0xFFCA026A - 0xFFCA026C */

			uint32	u4SGDIAGSRR;								/* 0xFFCA026C - 0xFFCA0270 */

			uint8	u1Dummy6[0xFFCA0280U - 0xFFCA0270U];		/* 0xFFCA0270 - 0xFFCA0280 */

		#endif

		uint32	u4DIR[ADC_CHANNEL_NUM];							/* 0xFFCA0280 - 0xFFCA0380 */

		#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) 

			uint8	u1Dummy7[0xFFCA0400U - 0xFFCA0380U];		/* 0xFFCA0380 - 0xFFCA0400 */

			uint32	u4PWDDIR;									/* 0xFFCA0400 - 0xFFCA0404 *//* PWM-Diag supplementary information register */

			uint8	u1Dummy8[0xFFCA0440U - 0xFFCA0404U];		/* 0xFFCA0404 - 0xFFCA0440 */

		#elif	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )	/* ADC0, ADC1, ADC2, ADC3 only */

			uint8	u1Dummy7[0xFFCA0404U - 0xFFCA0380U];		/* 0xFFCA0380 - 0xFFCA0404 */

			uint32	u4SGDIAGDIR[ADC_SGDIAG_CHANNEL_NUM];		/* 0xFFCA0404 - 0xFFCA0410 */

			uint8	u1Dammy8[0xFFCA0440U - 0xFFCA0410U];		/* 0xFFCA0410 - 0xFFCA0440 */

		#endif

		struct
		{
			uint8	u1SGSTCR;								/* 0xFFCA0440 - 0xFFCA0441 *//* Scan Group Start Control Register */

			uint8	u1Dummy9[0xFFCA0444U - 0xFFCA0441U];	/* 0xFFCA0441 - 0xFFCA0444 */

			uint8	u1SGSTPCR;								/* 0xFFCA0444 - 0xFFCA0445 *//* Scan Group Stop Control Register */

			uint8	u1Dummy10[0xFFCA0448U - 0xFFCA0445U];	/* 0xFFCA0445 - 0xFFCA0448 */

			uint8	u1ADTSTCR;								/* 0xFFCA0448 - 0xFFCA0449 *//* Only scan group stop control register *//* SG3,4 is provided */

			uint8	u1Dummy11[0xFFCA044CU - 0xFFCA0449U];	/* 0xFFCA0449 - 0xFFCA044C */

			uint8	u1ADTENDCR;								/* 0xFFCA044C - 0xFFCA044D *//* Only scan group stop control register *//* SG3,4 is provided */

			uint8	u1Dummy12[0xFFCA0450U - 0xFFCA044DU];	/* 0xFFCA044D - 0xFFCA0450 */

			uint8	u1SGCR;									/* 0xFFCA0450 - 0xFFCA0451 *//* Scan Group x Control Register */

			uint8	u1Dummy13[0xFFCA0454U - 0xFFCA0451U];	/* 0xFFCA0451 - 0xFFCA0454 */

			uint16	u2SGVCPR;								/* 0xFFCA0454 - 0xFFCA0456 *//* Register to specify start and end pointers */

			uint8	u1Dummy14[0xFFCA0458U - 0xFFCA0456U];	/* 0xFFCA0456 - 0xFFCA0458 */

			uint8	u1SGMCYCR;								/* 0xFFCA0458 - 0xFFCA0459 *//* Register specifying scan count for multi-cycle scans */

			uint8	u1Dummy15[0xFFCA0460U - 0xFFCA0459U];	/* 0xFFCA0459 - 0xFFCA0460 */

			uint8	u1SGSR;									/* 0xFFCA0460 - 0xFFCA0461 *//* Register for scan group x status */

			uint8	u1Dummy16[0xFFCA0464U - 0xFFCA0461U];	/* 0xFFCA0461 - 0xFFCA0464*/

			uint32	u4ADTIPR;								/* 0xFFCA0464 - 0xFFCA0468 *//* Registers that control the start of A/D timer x *//* Only SG3,4 are provided */

			uint32	u4ADTPRR;								/* 0xFFCA0468 - 0xFFCA046C *//* Register to control end of A/D timer x *//* Only SG3,4 is provided */

			uint8	u1Dummy17[0xFFCA0480U - 0xFFCA046CU];	/* 0xFFCA046C - 0xFFCA0480 */

		}stSG[ADC_SG_NUM];									/* 0xFFCA0440 - 0xFFCA0580 */

		#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )

			uint8	u1PWDCR;									/* 0xFFCA0580 - 0xFFCA0581 *//* Registers that control PWM-Diag */

			uint8	u1Dummy18[0xFFCA0584U - 0xFFCA0581U];		/* 0xFFCA0581 - 0xFFCA0584 */

			uint8	u1PWDSGCR;									/* 0xFFCA0584 - 0xFFCA0585 *//* Registers that control PWM-Diag hardware triggers */

			uint8	u1Dummy19[0xFFCA0600U - 0xFFCA0585U];		/* 0xFFCA0585 - 0xFFCA0600 */

		#elif	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )	/* Unit0,1,2,3				*/

			uint8	u1Dummy18[0xFFCA05C0U - 0xFFCA0580U];		/* 0xFFCA0580 - 0xFFCA05C0 */

			uint8	u1SGDIAGSTCR;								/* 0xFFCA05C0 - 0xFFCA05C1 */

			uint8	u1Dummy19[0xFFCA05C4U - 0xFFCA05C1U];		/* 0xFFCA05C1 - 0xFFCA05C4 */

			uint8	u1SGDIAGSTPCR;								/* 0xFFCA05C4 - 0xFFCA05C5 */

			uint8	u1Dummy20[0xFFCA05D0U - 0xFFCA05C5U];		/* 0xFFCA05C5 - 0xFFCA05D0 */

			uint32	u4SGDIAGCR;									/* 0xFFCA05D0 - 0xFFCA05D4 */

			uint8	u1Dummy21[0xFFCA05E0U - 0xFFCA05D4U];		/* 0xFFCA05D4 - 0xFFCA05E0 */

			uint32	u4SGDIAGPCCR0;								/* 0xFFCA05E0 - 0xFFCA05E4 */

			uint32	u4SGDIAGPCCR1;								/* 0xFFCA05E4 - 0xFFCA05E8 *//* Only Unit3	*/

			uint8	u1Dummy22[0xFFCA05F0U - 0xFFCA05E8U];		/* 0xFFCA05E8 - 0xFFCA05F0 */

			uint8	u1SGDIAGSR;									/* 0xFFCA05F0 - 0xFFCA05F1 */

			uint8	u1Dummy23[0xFFCA0600U - 0xFFCA05F1U];		/* 0xFFCA05F1 - 0xFFCA0600 */

		#endif

		uint16	u2SGSTR;									/* 0xFFCA0600 - 0xFFCA0602 *//* Scan Group x Status Register */

		uint8	u1Dummy24[0xFFCA0610U - 0xFFCA0602U];		/* 0xFFCA0602 - 0xFFCA0610 */

		uint8	u1ADSYNSTCR;								/* 0xFFCA0610 - 0xFFCA0611 *//* A/D Synchronization Start Control Register: Only Unit0	*/

		uint8	u1Dummy25[0xFFCA0614U - 0xFFCA0611U];		/* 0xFFCA0611 - 0xFFCA0614 */

		uint8	u1ADTSYNSTCR;								/* 0xFFCA0614 - 0xFFCA0615 *//* Registers that control the start of the simultaneous counting operation of ADCJ0 and ADCJ1 A/D timers */

		uint8	u1Dummy26[0xFFCA0640U - 0xFFCA0615U];		/* 0xFFCA0615 - 0xFFCA0640 */
			
		uint8	u1ADHALTR;									/* 0xFFCA0640 - 0xFFCA0641 *//* AD end register */

		uint8	u1Dummy27[0xFFCA0644U - 0xFFCA0641U];		/* 0xFFCA0641 - 0xFFCA0644 */

		uint8	u1ADCR1;									/* 0xFFCA0644 - 0xFFCA0645 *//* AD control register 1 */

		uint8	u1Dummy28[0xFFCA0648U - 0xFFCA0645U];		/* 0xFFCA0645 - 0xFFCA0648 */

		uint8	u1ADCR2;									/* 0xFFCA0648 - 0xFFCA0649 *//* AD control register 2 */

		uint8	u1Dummy29[0xFFCA064CU - 0xFFCA0649U];		/* 0xFFCA0649 - 0xFFCA064C */

		uint32	u4SMPCR;									/* 0xFFCA064C - 0xFFCA0650 *//* Registers that control sampling */

		uint8	u1MPXCURCR;									/* 0xFFCA0650 - 0xFFCA0651 *//* MPX Current Control Register */

		uint8	u1Dummy30[0xFFCA0654U - 0xFFCA0651U];		/* 0xFFCA0651 - 0xFFCA0654 */
		
		uint8	u1MPXINTER;									/* 0xFFCA0654 - 0xFFCA0655 *//* MPX interrupt enable register */

		uint8	u1Dummy31[0xFFCA0658U - 0xFFCA0655U];		/* 0xFFCA0655 - 0xFFCA0658 */

		uint32	u4MPXCURR1;									/* 0xFFCA0658 - 0xFFCA065C *//* MPX current register 1 */

		uint8	u1MPXCURR2;									/* 0xFFCA065C - 0xFFCA065D *//* MPX current register 2 */

		uint8	u1Dummy32[0xFFCA0660U - 0xFFCA065DU];		/* 0xFFCA065D - 0xFFCA0660 */

		uint8	u1MPXCMDR;									/* 0xFFCA0660 - 0xFFCA0661 *//* MPX command information register */

		uint8	u1Dummy33[0xFFCA0670U - 0xFFCA0661U];		/* 0xFFCA0661 - 0xFFCA0670 */

		#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )

			uint16	u2GTMENTSGER;								/* 0xFFCA0670 - 0xFFCA0672 */

		#elif	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )	/* ADC0, ADC1, ADC2, ADC3 only */

			uint16	u2DFASENTSGER;								/* 0xFFCA0670 - 0xFFCA0672 */

		#endif

		uint8	u1Dummy34[0xFFCA0674U - 0xFFCA0672U];		/* 0xFFCA0672 - 0xFFCA0674 */

		struct
		{
			uint8	u1Data;									/* 0xFFCA0674 - 0xFFCA0675 */

			uint8	u1Dummy35[0xFFCA0678U - 0xFFCA0675U];	/* 0xFFCA0675 - 0xFFCA0678 */	

		}stADENDP[ADC_SG_NUM];								/* 0xFFCA0674 - 0xFFCA0688 */						

		uint8	u1Dummy36[0xFFCA0690U - 0xFFCA0688U];		/* 0xFFCA0688 - 0xFFCA0690 */

		uint8	u1THSMPSTCR;								/* 0xFFCA0690 - 0xFFCA0691 *//* Register to control start of sampling for all T&H */

		uint8	u1Dummy37[0xFFCA0694U - 0xFFCA0691U];		/* 0xFFCA0691 - 0xFFCA0694 */

		uint8	u1THSTPCR;									/* 0xFFCA0694 - 0xFFCA0695 *//* Register to control all T&H stops */

		uint8	u1Dummy38[0xFFCA0698U - 0xFFCA0695U];		/* 0xFFCA0695 - 0xFFCA0698 */

		uint8	u1THCR;										/* 0xFFCA0698 - 0xFFCA0699 *//* Registers that control T& H's automatic sampling function */

		uint8	u1Dummy39[0xFFCA06A0U - 0xFFCA0699U];		/* 0xFFCA0699 - 0xFFCA06A0 */

		uint8	u1THAHLDSTCR;								/* 0xFFCA06A0 - 0xFFCA06A1 *//* Registers controlling start of hold for T&H group A */

		#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )

			uint8	u1Dummy40[0xFFCA06B4U - 0xFFCA06A1U];		/* 0xFFCA06A1 - 0xFFCA06B4 */

		#elif	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )	/* ADC0, ADC1, ADC2, ADC3 only */

			uint8	u1Dummy40[0xFFCA06A4U - 0xFFCA06A1U];		/* 0xFFCA06A1 - 0xFFCA06A4 */

			uint8	u1THBHLDSTCR;							/* 0xFFCA06A4 - 0xFFCA06A5 *//* Registers that control start of hold for T&H group B */

			uint8	u1Dummy41[0xFFCA06B0U - 0xFFCA06A5U];		/* 0xFFCA06A5 - 0xFFCA06B0 */

			uint16	u2THGSR;								/* 0xFFCA06B0 - 0xFFCA06B2 */

			uint8	u1Dummy42[0xFFCA06B4U - 0xFFCA06B2U];		/* 0xFFCA06B2 - 0xFFCA06B4 */

		#endif

		uint8	u1THER;										/* 0xFFCA06B4 - 0xFFCA06B5 *//* Registers that control whether each T&H is enabled or disabled */

		uint8	u1Dummy43[0xFFCA06C0U - 0xFFCA06B5U];		/* 0xFFCA06B5 - 0xFFCA06C0 */

		uint8	u1THACR;									/* 0xFFCA06C0 - 0xFFCA06C1 *//* Registers that control T&H group A */

		#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )

			uint8	u1Dummy44[0xFFCA0700U - 0xFFCA06C1U];		/* 0xFFCA06C1 - 0xFFCA0700 */

		#elif	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )	/* ADC0, ADC1, ADC2, ADC3 only */

			uint8	u1Dummy44[0xFFCA06C4U - 0xFFCA06C1U];		/* 0xFFCA06C1 - 0xFFCA06C4 */

			uint8	u1THBCR;									/* 0xFFCA06C4 - 0xFFCA06C5 *//* Registers that control T&H group B */

			uint8	u1Dummy45[0xFFCA0700U - 0xFFCA06C5U];		/* 0xFFCA06C5 - 0xFFCA0700 */

		#endif

		struct
		{
			uint16	u2Data;									/* 0xFFCA0700 - 0xFFCA0702 */

			uint8	u1Dummy46[0xFFCA0704U - 0xFFCA0702U];	/* 0xFFCA0702 - 0xFFCA0704 */	

		}stWAITTR[ADC_VCT_NUM];								/* 0xFFCA0700 - 0xFFCA0720 */

		uint8	u1Dummy47[0xFFCA0740U - 0xFFCA0720U];		/* 0xFFCA0720 - 0xFFCA0740 */

		uint8	u1VMONVDCR1;								/* 0xFFCA0740 - 0xFFCA0741 *//* Voltage Monitoring Voltage Divider Control Register: Only Unit0	*/

		uint8	u1Dummy48[0xFFCA0744U - 0xFFCA0741U];		/* 0xFFCA0741 - 0xFFCA0744 */

		uint8	u1VMONVDCR2;								/* 0xFFCA0744 - 0xFFCA0745 *//* Voltage Monitoring Voltage Divider Control Register: Only Unit0	*/

		uint8	u1Dummy49[0xFFCA0760U - 0xFFCA0745U];		/* 0xFFCA0745 - 0xFFCA0760 */

		uint8	u1TDCR;										/* 0xFFCA0760 - 0xFFCA0761 *//* Registers that control T&H path self-diagnosis and pin-level self-diagnosis */

		uint8	u1Dummy50[0xFFCA0764U - 0xFFCA0761U];		/* 0xFFCA0761 - 0xFFCA0764 */

		uint16	u2ODCR;										/* 0xFFCA0764 - 0xFFCA0766 *//* Disconnection detection control register */

		uint8	u1Dummy51[0xFFCA0770U - 0xFFCA0766U];		/* 0xFFCA0766 - 0xFFCA0770 */

		uint8	u1SFTCR;									/* 0xFFCA0770 - 0xFFCA0771 *//* Safety control register */

		uint8	u1Dummy52[0xFFCA0774U - 0xFFCA0771U];		/* 0xFFCA0771 - 0xFFCA0774 */

		uint8	u1TOCCR;									/* 0xFFCA0774 - 0xFFCA0775 *//* Register to control trigger overlap check */

		uint8	u1Dummy53[0xFFCA0790U - 0xFFCA0775U];		/* 0xFFCA0775 - 0xFFCA0790 */

		uint8	u1TOCER;									/* 0xFFCA0790 - 0xFFCA0791 *//* Register indicating trigger overlap check error */

		uint8	u1Dummy54[0xFFCA079CU - 0xFFCA0791U];		/* 0xFFCA0791 - 0xFFCA079C */

		uint8	u1OWER;										/* 0xFFCA079C - 0xFFCA079D *//* Overwrite error register */

		uint8	u1Dummy55[0xFFCA07A0U - 0xFFCA079DU];		/* 0xFFCA079D - 0xFFCA07A0 */

		uint8	u1PER;										/* 0xFFCA07A0 - 0xFFCA07A1 *//* Parity error register */

		uint8	u1Dummy56[0xFFCA07A4U - 0xFFCA07A1U];		/* 0xFFCA07A1 - 0xFFCA07A4 */

		uint8	u1IDER;										/* 0xFFCA07A4 - 0xFFCA07A5 *//* Register indicating ID error */

		uint8	u1Dummy57[0xFFCA07A8U - 0xFFCA07A5U];		/* 0xFFCA07A5 - 0xFFCA07A8 */

		uint16	u2ECR;										/* 0xFFCA07A8 - 0xFFCA07AA *//* error-clear register */

		#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )

			uint8	u1Dummy58[0xFFCA0800U - 0xFFCA07AAU];		/* 0xFFCA07AA - 0xFFCA0800 */

		#elif	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )	/* ADC1 only */

			uint8	u1Dummy58[0xFFCA07B0U - 0xFFCA07AAU];		/* 0xFFCA07AA - 0xFFCA07B0 */

			struct{

				uint8	u1Data;									/* 0xFFCA07B0 - 0xFFCA07B1 */

				uint8	u1Dammy59[0xFFCA07B4U - 0xFFCA07B1U];	/* 0xFFCA07B1 - 0xFFCA07B4 */
			
			}stSTPDCR[ADC_SGDIAG_CHANNEL_NUM];			/* 0xFFCA07B0 - 0xFFCA07BC */

			uint8	u1Dummy60[0xFFCA0800U - 0xFFCA07BCU];		/* 0xFFCA07BC - 0xFFCA0800 */

		#endif

		uint32	u4VCULLMTBR[ADC_VCT_NUM];					/* 0xFFCA0800 - 0xFFCA0820 *//* Virtual channel lower/lower table register y */

		uint8	u1Dummy61[0xFFCA0840U - 0xFFCA0820U];		/* 0xFFCA0820 - 0xFFCA0840 */

		uint32	u4VCLMINTER1;								/* 0xFFCA0840 - 0xFFCA0844 *//* Virtual channel lower/lower error interrupt enable register 1 */

		uint32	u4VCLMINTER2;								/* 0xFFCA0844 - 0xFFCA0848 *//* Virtual channel lower/lower error interrupt enable register 2 */

		#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )

			uint8	u1Dummy62[0xFFCA084CU - 0xFFCA0848U];		/* 0xFFCA0848 - 0xFFCA084C */

			uint8	u1PWVCLMINTER;								/* 0xFFCA084C - 0xFFCA084D *//* Register controlling upper/lower limit check */

			uint8	u1Dummy63[0xFFCA0860U - 0xFFCA084DU];		/* 0xFFCA084D - 0xFFCA0860 */

		#elif	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )	/* ADC0, ADC1, ADC2, ADC3 only */

			uint8	u1Dummy62[0xFFCA0850U - 0xFFCA0848U];		/* 0xFFCA0848 - 0xFFCA0850 */

			uint8	u1SDVCLMINTER;								/* 0xFFCA0850 - 0xFFCA0851 */

			uint8	u1Dummy63[0xFFCA0860U - 0xFFCA0851U];		/* 0xFFCA0851 - 0xFFCA0860 */

		#endif

		uint32	u4VCLMSR1;									/* 0xFFCA0860 - 0xFFCA0864 *//* Virtual Channel Upper/Lower Limit Exceeded Status Register 1 */

		uint32	u4VCLMSR2;									/* 0xFFCA0864 - 0xFFCA0868 *//* Virtual Channel Upper/Lower Exceeding Status Register 2 */

		#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )

			uint8	u1Dummy64[0xFFCA086CU - 0xFFCA0868U];		/* 0xFFCA0868 - 0xFFCA086C */

			uint32	u4PWVCLMSR;									/* 0xFFCA086C - 0xFFCA0870 *//* Register showing upper/lower PWMDiag check result */

			uint8	u1Dummy65[0xFFCA0880U - 0xFFCA0870U];		/* 0xFFCA0870 - 0xFFCA0880 */

		#elif	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )	/* ADC0, ADC1, ADC2, ADC3 only */

			uint8	u1Dummy64[0xFFCA0870U - 0xFFCA0868U];		/* 0xFFCA0868 - 0xFFCA0870 */

			uint32	u4SDVCLMSR;									/* 0xFFCA0870 - 0xFFCA0874 */

			uint8	u1Dummy65[0xFFCA0880U - 0xFFCA0874U];		/* 0xFFCA0874 - 0xFFCA0880 */

		#endif

		struct
		{
			uint16	u2Data;									/* 0xFFCA0880 - 0xFFCA0882 */
			
			uint8	u1Dummy66[0xFFCA0884U - 0xFFCA0882U];	/* 0xFFCA0882 - 0xFFCA0884 */	

		}stSGULCR[ADC_SG_NUM];								/* 0xFFCA0880 - 0xFFCA0894 */

		#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )

			uint8	u1Dummy67[0xFFCA08A0U - 0xFFCA0894U];		/* 0xFFCA0894 - 0xFFCA08A0 */

		#elif	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )	/* ADC0, ADC1, ADC2, ADC3 only */

			uint16	u2SGDIAGULCR;								/* 0xFFCA0894 - 0xFFCA0896 */

			uint8	u1Dummy67[0xFFCA08A0U - 0xFFCA0896U];		/* 0xFFCA0896 - 0xFFCA08A0 */

		#endif

		uint32	u4VCLMSCR1;									/* 0xFFCA08A0 - 0xFFCA08A4 *//* Virtual Channel Upper/Lower Limit Exceeded Status Clear Register 1 */

		uint32	u4VCLMSCR2;									/* 0xFFCA08A4 - 0xFFCA08A8 *//* Virtual Channel Upper/Lower Limit Exceeded Status Clear Register 2 */

		#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )

			uint8	u1Dummy68[0xFFCA08ACU - 0xFFCA08A8U];		/* 0xFFCA08A8 - 0xFFCA08AC */

			uint8	u1PWVCLMSCR;								/* Register to clear upper/lower check status of 0xFFCA08AC - 0xFFCA08AD *//* PWM-Diag */

			uint8	u1Dummy69[0xFFCA08B4U - 0xFFCA08ADU];		/* 0xFFCA08AD - 0xFFCA08B4 */	

		#elif	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )	/* ADC0, ADC1, ADC2, ADC3 only */

			uint8	u1Dummy68[0xFFCA08B0U - 0xFFCA08A8U];		/* 0xFFCA08A8 - 0xFFCA08B0 */

			uint8	u1SDVCLMSCR;								/* 0xFFCA08B0 - 0xFFCA08B1 */

			uint8	u1Dummy69[0xFFCA08B4U - 0xFFCA08B1U];		/* 0xFFCA08B1 - 0xFFCA08B4 */

		#endif

		uint8	u1SGULCCR;									/* 0xFFCA08B4 - 0xFFCA08B5 *//* Register to clear upper/lower check status register for each scan */

		uint8	u1Dummy70[0xFFCA08B8U - 0xFFCA08B5U];		/* 0xFFCA08B5 - 0xFFCA08B8 */

		uint8	u1VCLMASCR;									/* 0xFFCA08B8 - 0xFFCA08B9 *//* Register to clear virtual channel upper/lower check status */

		uint8	u1Dummy71[0xFFCA08BCU - 0xFFCA08B9U];		/* 0xFFCA08B9 - 0xFFCA08BC */

	}stMODULE;

}Reg_Adc_Type;

/***************************/
/*           SELB          */
/***************************/
/* 0xFF9A3800 - 0xFF9A3820 */
typedef struct
{

	uint32	u4SGTSEL[ADC_SG_NUM];							/* 0xFF9A3800 - 0xFF9A3804 *//* Available only for ADC2/ADCA */

}Reg_Adc_SELB_Type;


/***************************/
/*           AIR           */
/***************************/
/* 0xFFCB2500 - 0xFFCB2510 */
typedef struct
{
	uint32	u4AIRISELR0;									/* 0xFFCB2500 - 0xFFCB2504 */

	uint32	u4AIRISELR1;									/* 0xFFCB2504 - 0xFFCB2508 */
	
	uint32	u4AIRDSELR0;									/* 0xFFCB2508 - 0xFFCB250C */
	
	uint32	u4AIRDSELR1;									/* 0xFFCB250C - 0xFFCB2510 */

}Reg_Air_Type;

/*==============================================================================================*/
/*	register BIT definition																		*/
/*==============================================================================================*/
/*==================*/
/*	ADC				*/
/*==================*/
/* VCR */
#define		ADC_VCR_VCULLMTBS				(BIT31 + BIT30 + BIT29 + BIT28)
#define		ADC_VCR_VCULLMTBS_0				(BIT28)			/* Virtual Channel Upper/Lower Table Register Selection */
	#define		ADC_VCR_VCULLMTBS_DISABLED		(0U)		/* Disable    Select (default) */
	#define		ADC_VCR_VCULLMTBS_VCULLMTBR0	(1U)		/* VCULLMTBR0 select */
	#define		ADC_VCR_VCULLMTBS_VCULLMTBR1	(2U)		/* VCULLMTBR1 select */
	#define		ADC_VCR_VCULLMTBS_VCULLMTBR2	(3U)		/* VCULLMTBR2 select */
	#define		ADC_VCR_VCULLMTBS_VCULLMTBR3	(4U)		/* VCULLMTBR3 select */
	#define		ADC_VCR_VCULLMTBS_VCULLMTBR4	(5U)		/* VCULLMTBR4 select */
	#define		ADC_VCR_VCULLMTBS_VCULLMTBR5	(6U)		/* VCULLMTBR5 select */
	#define		ADC_VCR_VCULLMTBS_VCULLMTBR6	(7U)		/* VCULLMTBR6 select */
	#define		ADC_VCR_VCULLMTBS_VCULLMTBR7	(8U)		/* VCULLMTBR7 select */
#define		ADC_VCR_WTTS					(BIT27 + BIT26 + BIT25 + BIT24)
#define		ADC_VCR_WTTS_0					(BIT24)			/* Weight time table register selection between virtual channels of the same scan group */
	#define		ADC_VCR_WTTS_DISABLED			(0U)		/* Disable selection (default) */
	#define		ADC_VCR_WTTS_WAITTR0			(1U)		/* WAITTR0Select */
	#define		ADC_VCR_WTTS_WAITTR1			(2U)		/* WAITTR1 selection */
	#define		ADC_VCR_WTTS_WAITTR2			(3U)		/* Select WAITTR2 */
	#define		ADC_VCR_WTTS_WAITTR3			(4U)		/* Select WAITTR3 */
	#define		ADC_VCR_WTTS_WAITTR4			(5U)		/* WAITTR4 selected */
	#define		ADC_VCR_WTTS_WAITTR5			(6U)		/* Select WAITTR5 */
	#define		ADC_VCR_WTTS_WAITTR6			(7U)		/* WAITTR6 selection */
	#define		ADC_VCR_WTTS_WAITTR7			(8U)		/* Select WAITTR7 */

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
	#define		ADC_VCR_GTMENT					(BIT20)
		#define		ADC_VCR_GTMENT_DISABLED			(0U)		/* GTM entry */
		#define		ADC_VCR_GTMENT_ENABLED			(1U)		/* No GTM entry */
	#define		ADC_VCR_GTMTAG					(BIT19 + BIT18 + BIT17 + BIT16)
	#define		ADC_VCR_GTMTAG_0				(BIT16)			/* GTM tag */
#elif	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
	#define		ADC_VCR_DFENT					(BIT20)
		#define		ADC_VCR_DFENT_DISABLED			(0U)		/* DFE entry */
		#define		ADC_VCR_DFENT_ENABLED			(1U)		/* No DFE entry */
	#define		ADC_VCR_DFETAG					(BIT19 + BIT18 + BIT17 + BIT16)
	#define		ADC_VCR_DFETAG_0				(BIT16)			/* DFE tag */
#endif

#define		ADC_VCR_CNVCLS					(BIT14 + BIT13 + BIT12 + BIT11)
#define		ADC_VCR_CNVCLS_0				(BIT11)			/* Conversion type */
	#define		ADC_VCR_CNVCLS_NORMAL			(0U)		/* Normal A/D conversion */
	#define		ADC_VCR_CNVCLS_HOLD				(1U)		/* Hold value */
	#define		ADC_VCR_CNVCLS_EXTEND			(2U)		/* Extended sampling */
	#define		ADC_VCR_CNVCLS_DIAG				(3U)		/* Self-diagnosis */
	#define		ADC_VCR_CNVCLS_ADD				(4U)		/* Normal A/D conversion in addition mode */
	#define		ADC_VCR_CNVCLS_NORMAL_MPX		(5U)		/* Regular A/D conversion w/MPX */
	#define		ADC_VCR_CNVCLS_ADD_MPX			(6U)		/* Normal A/D conversion in addition mode w/MPX */
	#define		ADC_VCR_CNVCLS_PIN_DIAG			(7U)		/* Pin-level self-diagnosis */
	#define		ADC_VCR_CNVCLS_BREAK1			(8U)		/* Disconnection detection mode1 */
	#define		ADC_VCR_CNVCLS_BREAK2_DOWN		(9U)		/* Disconnection detection mode 2IO pulldown */
	#define		ADC_VCR_CNVCLS_BREAK2_UP		(10U)		/* Disconnection detection mode 2IO pull-up */
	#define		ADC_VCR_CNVCLS_BREAK1_DIAG		(11U)		/* Self-diagnosis in breakage detection mode 1 */
	#define		ADC_VCR_CNVCLS_BREAK2_DOWN_DIAG	(12U)		/* Disconnection detection mode 2 Self-diagnosis with IO pulldown */
	#define		ADC_VCR_CNVCLS_BREAK2_UP_DIAG	(13U)		/* Self-diagnosis with Disconnection Detection Mode 2 IO Pull-up */
	#define		ADC_VCR_CNVCLS_DATAPATH_DIAG	(14U)		/* Data path diagnostics */
#define		ADC_VCR_MPXV					(BIT10 + BIT9 + BIT8)
#define		ADC_VCR_MPXV_0					(BIT8)			/* MPX Channel */
#define		ADC_VCR_ADIE					(BIT7)			/* Virtual channel end interrupt enable */
	#define		ADC_VCR_ADIE_NOTOUTPUT			(0U)		/* Does not output ADImx at virtual channel end of virtual channel n on SGx */
	#define		ADC_VCR_ADIE_OUTPUT				(1U)		/* Output ADImx at virtual channel end of virtual channel n on SGx */
#define		ADC_VCR_GCTRL					(BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)
#define		ADC_VCR_GCTRL_0					(BIT0)			/* General Control */
	#define		ADC_VCR_GCTRL_AN000				(0U)		/* Conversion type: Normal A/D conversion, value set during normal A/D conversion in addition mode (physical channel) */
	#define		ADC_VCR_GCTRL_AN001				(1U)
	#define		ADC_VCR_GCTRL_AN002				(2U)
	#define		ADC_VCR_GCTRL_AN003				(3U)
	#define		ADC_VCR_GCTRL_AN010				(4U)
	#define		ADC_VCR_GCTRL_AN011				(5U)
	#define		ADC_VCR_GCTRL_AN012				(6U)
	#define		ADC_VCR_GCTRL_AN013				(7U)
	#define		ADC_VCR_GCTRL_AN020				(8U)
	#define		ADC_VCR_GCTRL_AN021				(9U)
	#define		ADC_VCR_GCTRL_AN022				(10U)
	#define		ADC_VCR_GCTRL_AN023				(11U)
	#define		ADC_VCR_GCTRL_AN030				(12U)
	#define		ADC_VCR_GCTRL_AN031				(13U)
	#define		ADC_VCR_GCTRL_AN032				(14U)
	#define		ADC_VCR_GCTRL_AN033				(15U)
	#define		ADC_VCR_GCTRL_AN040				(16U)
	#define		ADC_VCR_GCTRL_AN041				(17U)
	#define		ADC_VCR_GCTRL_AN042				(18U)
	#define		ADC_VCR_GCTRL_AN043				(19U)
	#define		ADC_VCR_GCTRL_AN050				(20U)
	#define		ADC_VCR_GCTRL_AN051				(21U)
	#define		ADC_VCR_GCTRL_AN052				(22U)
	#define		ADC_VCR_GCTRL_AN053				(23U)
	#define		ADC_VCR_GCTRL_AN060				(24U)
	#define		ADC_VCR_GCTRL_AN061				(25U)
	#define		ADC_VCR_GCTRL_AN062				(26U)
	#define		ADC_VCR_GCTRL_AN063				(27U)
	#define		ADC_VCR_GCTRL_AN070				(28U)
	#define		ADC_VCR_GCTRL_AN071				(29U)
	#define		ADC_VCR_GCTRL_AN072				(30U)
	#define		ADC_VCR_GCTRL_AN073				(31U)
	#define		ADC_VCR_GCTRL_AN080				(32U)
	#define		ADC_VCR_GCTRL_AN081				(33U)
	#define		ADC_VCR_GCTRL_AN100				(0U)	
	#define		ADC_VCR_GCTRL_AN101				(1U)	
	#define		ADC_VCR_GCTRL_AN102				(2U)	
	#define		ADC_VCR_GCTRL_AN103				(3U)	
	#define		ADC_VCR_GCTRL_AN110				(4U)	
	#define		ADC_VCR_GCTRL_AN111				(5U)	
	#define		ADC_VCR_GCTRL_AN112				(6U)	
	#define		ADC_VCR_GCTRL_AN113				(7U)
	#define		ADC_VCR_GCTRL_AN120				(8U)	
	#define		ADC_VCR_GCTRL_AN121				(9U)	
	#define		ADC_VCR_GCTRL_AN122				(10U)
	#define		ADC_VCR_GCTRL_AN123				(11U)
	#define		ADC_VCR_GCTRL_AN130				(12U)
	#define		ADC_VCR_GCTRL_AN131				(13U)
	#define		ADC_VCR_GCTRL_AN132				(14U)
	#define		ADC_VCR_GCTRL_AN133				(15U)
	#define		ADC_VCR_GCTRL_AN140				(16U)
	#define		ADC_VCR_GCTRL_AN141				(17U)
	#define		ADC_VCR_GCTRL_AN142				(18U)
	#define		ADC_VCR_GCTRL_AN143				(19U)
	#define		ADC_VCR_GCTRL_AN150				(20U)
	#define		ADC_VCR_GCTRL_AN151				(21U)
	#define		ADC_VCR_GCTRL_AN152				(22U)
	#define		ADC_VCR_GCTRL_AN153				(23U)
	#define		ADC_VCR_GCTRL_AN160				(24U)
	#define		ADC_VCR_GCTRL_AN161				(25U)
	#define		ADC_VCR_GCTRL_AN162				(26U)
	#define		ADC_VCR_GCTRL_AN163				(27U)
	#define		ADC_VCR_GCTRL_AN170				(28U)
	#define		ADC_VCR_GCTRL_AN171				(29U)
	#define		ADC_VCR_GCTRL_AN172				(30U)
	#define		ADC_VCR_GCTRL_AN173				(31U)
	#define		ADC_VCR_GCTRL_AN180				(32U)
	#define		ADC_VCR_GCTRL_AN181				(33U)
	#define		ADC_VCR_GCTRL_AN200				(0U)	
	#define		ADC_VCR_GCTRL_AN201				(1U)	
	#define		ADC_VCR_GCTRL_AN202				(2U)	
	#define		ADC_VCR_GCTRL_AN203				(3U)	
	#define		ADC_VCR_GCTRL_AN210				(4U)	
	#define		ADC_VCR_GCTRL_AN211				(5U)	
	#define		ADC_VCR_GCTRL_AN212				(6U)	
	#define		ADC_VCR_GCTRL_AN213				(7U)	
	#define		ADC_VCR_GCTRL_AN220				(8U)	
	#define		ADC_VCR_GCTRL_AN221				(9U)	
	#define		ADC_VCR_GCTRL_AN222				(10U)
	#define		ADC_VCR_GCTRL_AN223				(11U)
	#define		ADC_VCR_GCTRL_AN230				(12U)
	#define		ADC_VCR_GCTRL_AN231				(13U)
	#define		ADC_VCR_GCTRL_AN232				(14U)
	#define		ADC_VCR_GCTRL_AN233				(15U)
	#define		ADC_VCR_GCTRL_AN240				(16U)
	#define		ADC_VCR_GCTRL_AN241				(17U)
	#define		ADC_VCR_GCTRL_AN242				(18U)
	#define		ADC_VCR_GCTRL_AN243				(19U)
	#define		ADC_VCR_GCTRL_AN250				(20U)
	#define		ADC_VCR_GCTRL_AN251				(21U)
	#define		ADC_VCR_GCTRL_AN252				(22U)
	#define		ADC_VCR_GCTRL_AN253				(23U)
	#define		ADC_VCR_GCTRL_AN260				(24U)
	#define		ADC_VCR_GCTRL_AN261				(25U)
	#define		ADC_VCR_GCTRL_AN262				(26U)
	#define		ADC_VCR_GCTRL_AN263				(27U)
	#define		ADC_VCR_GCTRL_AN270				(28U)
	#define		ADC_VCR_GCTRL_AN271				(29U)
	#define		ADC_VCR_GCTRL_AN272				(30U)
	#define		ADC_VCR_GCTRL_AN273				(31U)
	#define		ADC_VCR_GCTRL_AN300				(0U)	
	#define		ADC_VCR_GCTRL_AN301				(1U)	
	#define		ADC_VCR_GCTRL_AN302				(2U)	
	#define		ADC_VCR_GCTRL_AN303				(3U)	
	#define		ADC_VCR_GCTRL_AN310				(4U)	
	#define		ADC_VCR_GCTRL_AN311				(5U)	
	#define		ADC_VCR_GCTRL_AN312				(6U)	
	#define		ADC_VCR_GCTRL_AN313				(7U)	
	#define		ADC_VCR_GCTRL_AN320				(8U)	
	#define		ADC_VCR_GCTRL_AN321				(9U)	
	#define		ADC_VCR_GCTRL_AN322				(10U)
	#define		ADC_VCR_GCTRL_AN323				(11U)
	#define		ADC_VCR_GCTRL_AN330				(12U)
	#define		ADC_VCR_GCTRL_AN331				(13U)
	#define		ADC_VCR_GCTRL_AN332				(14U)
	#define		ADC_VCR_GCTRL_AN333				(15U)
	#define		ADC_VCR_GCTRL_AN340				(16U)
	#define		ADC_VCR_GCTRL_AN341				(17U)
	#define		ADC_VCR_GCTRL_AN342				(18U)
	#define		ADC_VCR_GCTRL_AN343				(19U)
	#define		ADC_VCR_GCTRL_AN350				(20U)
	#define		ADC_VCR_GCTRL_AN351				(21U)
	#define		ADC_VCR_GCTRL_AN352				(22U)
	#define		ADC_VCR_GCTRL_AN353				(23U)
	#define		ADC_VCR_GCTRL_AN360				(24U)
	#define		ADC_VCR_GCTRL_AN361				(25U)
	#define		ADC_VCR_GCTRL_AN362				(26U)
	#define		ADC_VCR_GCTRL_AN363				(27U)
	#define		ADC_VCR_GCTRL_AN370				(28U)
	#define		ADC_VCR_GCTRL_AN371				(29U)
	#define		ADC_VCR_GCTRL_AN372				(30U)
	#define		ADC_VCR_GCTRL_AN373				(31U)
	#define		ADC_VCR_GCTRL_AN380				(32U)
	#define		ADC_VCR_GCTRL_AN381				(33U)
	#define		ADC_VCR_GCTRL_AN382				(34U)
	#define		ADC_VCR_GCTRL_AN383				(35U)
	#define		ADC_VCR_GCTRL_AN390				(36U)
	#define		ADC_VCR_GCTRL_AN391				(37U)
	#define		ADC_VCR_GCTRL_AN392				(38U)
	#define		ADC_VCR_GCTRL_AN393				(39U)
	#define		ADC_VCR_GCTRL_ANA00				(0U)	
	#define		ADC_VCR_GCTRL_ANA01				(1U)	
	#define		ADC_VCR_GCTRL_ANA02				(2U)	
	#define		ADC_VCR_GCTRL_ANA03				(3U)	
	#define		ADC_VCR_GCTRL_ANA10				(4U)	
	#define		ADC_VCR_GCTRL_ANA11				(5U)	
	#define		ADC_VCR_GCTRL_ANA12				(6U)	
	#define		ADC_VCR_GCTRL_ANA13				(7U)	
	#define		ADC_VCR_GCTRL_ANA20				(8U)	
	#define		ADC_VCR_GCTRL_ANA21				(9U)	
	#define		ADC_VCR_GCTRL_ANA22				(10U)
	#define		ADC_VCR_GCTRL_ANA23				(11U)
	#define		ADC_VCR_GCTRL_ANA30				(12U)
	#define		ADC_VCR_GCTRL_ANA31				(13U)
	#define		ADC_VCR_GCTRL_ANA32				(14U)
	#define		ADC_VCR_GCTRL_ANA33				(15U)
	#define		ADC_VCR_GCTRL_ANA40				(16U)
	#define		ADC_VCR_GCTRL_ANA41				(17U)
	#define		ADC_VCR_GCTRL_ANA42				(18U)
	#define		ADC_VCR_GCTRL_ANA43				(19U)
	#define		ADC_VCR_GCTRL_ANA50				(20U)
	#define		ADC_VCR_GCTRL_ANA51				(21U)
	#define		ADC_VCR_GCTRL_ANA52				(22U)
	#define		ADC_VCR_GCTRL_ANA53				(23U)
	#define		ADC_VCR_GCTRL_ANA60				(24U)
	#define		ADC_VCR_GCTRL_ANA61				(25U)
	#define		ADC_VCR_GCTRL_ANA62				(26U)
	#define		ADC_VCR_GCTRL_ANA63				(27U)
	#define		ADC_VCR_GCTRL_ANA70				(28U)
	#define		ADC_VCR_GCTRL_ANA71				(29U)
	#define		ADC_VCR_GCTRL_SELFDIAG00		(ADC_VCR_GCTRL_SELFDIAG)	/* SELF-DIAGNOSTIC DETERMINATION */
	#define		ADC_VCR_GCTRL_SELFDIAG01		(ADC_VCR_GCTRL_SELFDIAG)	/* SELF-DIAGNOSTIC DETERMINATION */
	#define		ADC_VCR_GCTRL_SELFDIAG10		(ADC_VCR_GCTRL_SELFDIAG)	/* SELF-DIAGNOSTIC DETERMINATION */
	#define		ADC_VCR_GCTRL_SELFDIAG11		(ADC_VCR_GCTRL_SELFDIAG)	/* SELF-DIAGNOSTIC DETERMINATION */
	#define		ADC_VCR_GCTRL_SELFDIAG20		(ADC_VCR_GCTRL_SELFDIAG)	/* SELF-DIAGNOSTIC DETERMINATION */
	#define		ADC_VCR_GCTRL_SELFDIAG21		(ADC_VCR_GCTRL_SELFDIAG)	/* SELF-DIAGNOSTIC DETERMINATION */
	#define		ADC_VCR_GCTRL_SELFDIAG30		(ADC_VCR_GCTRL_SELFDIAG)	/* SELF-DIAGNOSTIC DETERMINATION */
	#define		ADC_VCR_GCTRL_SELFDIAG31		(ADC_VCR_GCTRL_SELFDIAG)	/* SELF-DIAGNOSTIC DETERMINATION */
	#define		ADC_VCR_GCTRL_SELFDIAG			(100U)						/* FOR SELF-DIAGNOSTIC DETERMINATION *//* AN *** SET A VALUE NOT TO BE USED ON THE RIGHTLINE */
	#define		ADC_VCR_GCTRL_AVREFH_1			(0x10U)		/* Conversion type: Set value at self-diagnosis (internal voltage value) AVREFH x 1 */
	#define		ADC_VCR_GCTRL_AVREFH_3_4		(0x0CU)		/* AVREFH x 3/4 */
	#define		ADC_VCR_GCTRL_AVREFH_1_2		(0x08U)		/* AVREFH x 1/2 */
	#define		ADC_VCR_GCTRL_AVREFH_1_4		(0x04U)		/* AVREFH x 1/4 */
	#define		ADC_VCR_GCTRL_AVREFH_0			(0x00U)		/* AVREFH x 0 */

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
	#define		ADC_VCR_DEFBIT				(ADC_VCR_VCULLMTBS|ADC_VCR_WTTS|ADC_VCR_GTMENT|ADC_VCR_CNVCLS|ADC_VCR_ADIE|ADC_VCR_GCTRL)
#elif	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
	#define		ADC_VCR_DEFBIT				(ADC_VCR_VCULLMTBS|ADC_VCR_WTTS|ADC_VCR_DFENT| ADC_VCR_CNVCLS|ADC_VCR_ADIE|ADC_VCR_GCTRL)
#endif

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
/* PWDVCR */
#define		ADC_PWDVCR_WTTS					(BIT19 + BIT18 + BIT17 + BIT16)
#define		ADC_PWDVCR_WTTS_0				(BIT16)			/* Weight time table register selection between virtual channels of PWM-Diag */
	#define		ADC_PWDVCR_WTTS_DISABLED		(0U)		/* Disable selection (default) */
	#define		ADC_PWDVCR_WTTS_WAITTR0			(1U)		/* WAITTR0Select */
	#define		ADC_PWDVCR_WTTS_WAITTR1			(2U)		/* WAITTR1 selection */
	#define		ADC_PWDVCR_WTTS_WAITTR2			(3U)		/* Select WAITTR2 */
	#define		ADC_PWDVCR_WTTS_WAITTR3			(4U)		/* Select WAITTR3 */
	#define		ADC_PWDVCR_WTTS_WAITTR4			(5U)		/* WAITTR4 selected */
	#define		ADC_PWDVCR_WTTS_WAITTR5			(6U)		/* Select WAITTR5 */
	#define		ADC_PWDVCR_WTTS_WAITTR6			(7U)		/* WAITTR6 selection */
	#define		ADC_PWDVCR_WTTS_WAITTR7			(8U)		/* Select WAITTR7 */
#define		ADC_PWDVCR_MPXE					(BIT15)	
	#define		ADC_PWDVCR_MPXE_NORMAL			(0U)		/* Normal A/D conversion */
	#define		ADC_PWDVCR_MPXE_NORMAL_MPX		(1U)		/* Regular A/D conversion w/MPX */
#define		ADC_PWDVCR_MPXV					(BIT14 + BIT13 + BIT12)
#define		ADC_PWDVCR_MPXV_0				(BIT12)			/* Select an MPX channel */
#define		ADC_PWDVCR_VCULLMTBS			(BIT11 + BIT10 + BIT9 + BIT8)
#define		ADC_PWDVCR_VCULLMTBS_0			(BIT8)			/* Virtual channel upper/lower table register selection in PWM-Diag */
	#define		ADC_PWDVCR_VCULLMTBS_DISABLED	(0U)		/* Disable    Select (default) */
	#define		ADC_PWDVCR_VCULLMTBS_VCULLMTBR0	(1U)		/* VCULLMTBR0 select */
	#define		ADC_PWDVCR_VCULLMTBS_VCULLMTBR1	(2U)		/* VCULLMTBR1 select */
	#define		ADC_PWDVCR_VCULLMTBS_VCULLMTBR2	(3U)		/* VCULLMTBR2 select */
	#define		ADC_PWDVCR_VCULLMTBS_VCULLMTBR3	(4U)		/* VCULLMTBR3 select */
	#define		ADC_PWDVCR_VCULLMTBS_VCULLMTBR4	(5U)		/* VCULLMTBR4 select */
	#define		ADC_PWDVCR_VCULLMTBS_VCULLMTBR5	(6U)		/* VCULLMTBR5 select */
	#define		ADC_PWDVCR_VCULLMTBS_VCULLMTBR6	(7U)		/* VCULLMTBR6 select */
	#define		ADC_PWDVCR_VCULLMTBS_VCULLMTBR7	(8U)		/* VCULLMTBR7 select */
/* PWDVCR_GCTRL created when used */
#define		ADC_PWDVCR_GCTRL				(BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)
#define		ADC_PWDVCR_GCTRL_0				(BIT0)		/* PWM-Diag generic control */

#elif	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
/* SGDIAGVCR */
#define		ADC_SGDIAGVCR_CNVCLS			(BIT3 + BIT2 + BIT1 + BIT0)
#define		ADC_SGDIAGVCR_CNVCLS_0			(BIT0)
	#define		ADC_SGDIAGVCR_CNVCLS_NORMAL				(0U)		/* Normal A/D conversion */
	#define		ADC_SGDIAGVCR_CNVCLS_ADD				(4U)		/* Normal A/D conversion in addition mode */
	#define		ADC_SGDIAGVCR_CNVCLS_PIN_DIAG			(7U)		/* Pin-level self-diagnosis */
	#define		ADC_SGDIAGVCR_CNVCLS_B2_DN				(9U)		/* Disconnection detection mode 2IO pulldown */
	#define		ADC_SGDIAGVCR_CNVCLS_B2_UP				(10U)		/* Disconnection detection mode 2IO pull-up */
	#define		ADC_SGDIAGVCR_CNVCLS_B2_DN_DIAG			(12U)		/* Disconnection detection mode 2 Self-diagnosis with IO pulldown */
	#define		ADC_SGDIAGVCR_CNVCLS_B2_UP_DIAG			(13U)		/* Self-diagnosis with Disconnection Detection Mode 2 IO Pull-up */
#endif

/* DR */
#define		ADC_DR_DR						(0xFFFFU)
#define		ADC_DR_DR_0						(BIT0)			/* Data register j */

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
/* PWDDR */
#define		ADC_PWDDR_PWDDR					(0xFFFFU)
#define		ADC_PWDDR_PWDDR_0				(BIT0)			/* Data register j in PWM-Diag */

#elif	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
/* SGDIAGDR0_1 */
#define		ADC_SGDIAGDR0_1_SGDIAGDR1		(0xFFFF0000U)
#define		ADC_SGDIAGDR0_1_SGDIAGDR1_0		(BIT16)
#define		ADC_SGDIAGDR0_1_SGDIAGDR0		(0x0000FFFFU)
#define		ADC_SGDIAGDR0_1_SGDIAGDR0_0		(BIT0)

/* SGDIAGDR2 */
#define		ADC_SGDIAGDR2_SGDIAGDR2			(0xFFFFU)
#define		ADC_SGDIAGDR2_SGDIAGDR2_0		(BIT0)

/* SGDIAGSRR */
#define		ADC_SGDIAGSRR_SRR1				(0xFFFF0000U)
#define		ADC_SGDIAGSRR_SRR1_0			(BIT16)
#define		ADC_SGDIAGSRR_SRR0				(0x0000FFFFU)
#define		ADC_SGDIAGSRR_SRR0_0			(BIT0)

#endif

/* DIR */
#define		ADC_DIR_MPXE					(BIT31)
	#define		ADC_DIR_MPXE_DISABLE			(0U)		/* Not using MPX */
	#define		ADC_DIR_MPXE_ENABLE				(1U)		/* Use MPX */
#define		ADC_DIR_MPXV					(BIT30 + BIT29 + BIT28)
#define		ADC_DIR_MPXV_0					(BIT28)			/* MPX Channel */
#define		ADC_DIR_IDEF					(BIT26)			/* ID error */
	#define		ADC_DIR_IDEF_ERROR				(0U)		/* ERROR YES */
	#define		ADC_DIR_IDEF_NOERROR			(1U)		/* No error */
#define		ADC_DIR_WFLAG					(BIT25)			/* Light flag */
	#define		ADC_DIR_WFLAG_CLEAR				(0U)		/* Clear */
	#define		ADC_DIR_WFLAG_SET				(1U)		/* Settings */
#define		ADC_DIR_PRTY					(BIT24)			/* Parity */
/* DIR_ID is created when used */
#define		ADC_DIR_ID						(BIT21 + BIT20 + BIT19 + BIT18 + BIT17 + BIT16)
#define		ADC_DIR_ID_0					(BIT16)
#define		ADC_DIR_DR						(0x0000FFFFU)
#define		ADC_DIR_DR_0					(BIT0)			/* Data */

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
/* PWDDIR */
#define		ADC_PWDDIR_MPXE					(BIT31)
	#define		ADC_PWDDIR_MPXE_DISABLE			(0U)		/* Not using MPX */
	#define		ADC_PWDDIR_MPXE_ENABLE			(1U)		/* Use MPX */
#define		ADC_PWDDIR_MPXV					(BIT30 + BIT29 + BIT28)
#define		ADC_PWDDIR_MPXV_0					(BIT28)		/* MPX Channel */
#define		ADC_PWDDIR_IDEF					(BIT26)			/* ID error */
	#define		ADC_PWDDIR_IDEF_ERROR			(0U)		/* ERROR YES */
	#define		ADC_PWDDIR_IDEF_NOERROR			(1U)		/* No error */
#define		ADC_PWDDIR_WFLAG					(BIT25)		/* Light flag */
	#define		ADC_PWDDIR_WFLAG_CLEAR			(0U)		/* Clear */
	#define		ADC_PWDDIR_WFLAG_SET			(1U)		/* Settings */
#define		ADC_PWDDIR_PRTY					(BIT24)			/* Parity */
#define		ADC_PWDDIR_ID					(BIT21 + BIT20 + BIT19 + BIT18 + BIT17 + BIT16)
#define		ADC_PWDDIR_ID_0					(BIT16)
#define		ADC_PWDDIR_DR					(0x0000FFFFU)
#define		ADC_PWDDIR_DR_0					(BIT0)			/* PWM-Diag data */

#elif	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
/* SGDIAGDIR */
#define		ADC_SGDIAGDIR_IDEF					(BIT26)			/* ID error */
	#define		ADC_SGDIAGDIR_IDEF_ERROR			(0U)		/* ERROR YES */
	#define		ADC_SGDIAGDIR_IDEF_NOERROR			(1U)		/* No error */
#define		ADC_SGDIAGDIR_WFLAG					(BIT25)		/* Light flag */
	#define		ADC_SGDIAGDIR_WFLAG_CLEAR			(0U)		/* Clear */
	#define		ADC_SGDIAGDIR_WFLAG_SET				(1U)		/* Settings */
#define		ADC_SGDIAGDIR_PRTY					(BIT24)			/* Parity */
#define		ADC_SGDIAGDIR_ID					(BIT21 + BIT20 + BIT19 + BIT18 + BIT17 + BIT16)
#define		ADC_SGDIAGDIR_DR					(0x0000FFFFU)
#define		ADC_SGDIAGDIR_DR_0					(BIT0)

#endif

/* SGCR */
#define		ADC_SGCR_ADTSTARTE				(BIT7)			/* AD timer synchronization start enabled */
	#define		ADC_SGCR_ADTSTARTE_DISABLE		(0U)		/* ADTSTART disabled */
	#define		ADC_SGCR_ADTSTARTE_ENABLE		(1U)		/* ADGSTART permission */
#define		ADC_SGCR_ADSTARTE				(BIT6)			/* Scan group synchronization start enabled */
	#define		ADC_SGCR_ADSTARTE_DISABLE		(0U)		/* ADSTART disabled */
	#define		ADC_SGCR_ADSTARTE_ENABLE		(1U)		/* ADSTART permission */
#define		ADC_SGCR_SCANMD					(BIT5)			/* SCAN MODE */
	#define		ADC_SGCR_SCANMD_MULTI_CYCLE		(0U)		/* Multi-cycle scan mode */
	#define		ADC_SGCR_SCANMD_CONTINUOUS		(1U)		/* Continuous scan mode */
#define		ADC_SGCR_ADIE					(BIT4)			/* End scan interrupt enable */
	#define		ADC_SGCR_ADIE_DISABLE			(0U)		/* No ADImx output at end of SGx scan */
	#define		ADC_SGCR_ADIE_ENABLE			(1U)		/* Output ADImx at end of SGx scan */
#define		ADC_SGCR_TRGMD_SG3_4			(BIT1 + BIT0)	/* Trigger mode */
#define		ADC_SGCR_TRGMD_SG0_2			(BIT0)			
	#define		ADC_SGCR_TRGMD_SOFT				(0U)		/* Trigger input to SGx disabled */
	#define		ADC_SGCR_TRGMD_HARD				(1U)		/* select SGx_TRG hardware trigger for trigger input to SGx */
	#define		ADC_SGCR_TRGMD_ADTIMER			(2U)		/* Trigger input to AD timer x disabled (x=3,4) */
	#define		ADC_SGCR_TRGMD_ADTIMER_HARD		(3U)		/* Select SGx_TRG hardware trigger for trigger input to AD timer x (x=3,4) */
#define		ADC_SGCR_DEFBIT					(ADC_SGCR_ADTSTARTE|ADC_SGCR_ADSTARTE|ADC_SGCR_SCANMD|ADC_SGCR_ADIE|ADC_SGCR_TRGMD_SG3_4)

/* SGVCPR */
#define		ADC_SGVCPR_VCEP					(BIT13 + BIT12 + BIT11 + BIT10 + BIT9 + BIT8)
#define		ADC_SGVCPR_VCEP_0				(BIT8)			/* End virtual channel pointer (mirror of ADCJnSGVCEP) */
#define		ADC_SGVCPR_VCEP_BITPOS			(8U)
#define		ADC_SGVCPR_VCSP					(BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)
#define		ADC_SGVCPR_VCSP_0				(BIT0)			/* Start virtual channel pointer (mirror of ADCJnSGVCSP) */
#define		ADC_SGVCPR_DEFBIT				(ADC_SGVCPR_VCEP|ADC_SGVCPR_VCSP)

/* SGMCYCR */
#define		ADC_SGMCYCR_MCYC				(0xFFU)
#define		ADC_SGMCYCR_MCYC_0				(BIT0)			/* MULTI-CYCLE SPECIFICATION */
#define		ADC_SGMCYCR_DEFBIT				(ADC_SGMCYCR_MCYC)

/* SGSTCR */
#define		ADC_SGSTCR_SGST					(BIT0)			/* Start scan group */
	#define		ADC_SGSTCR_SGST_SCAN_START		(1U)		/* Scan group x start condition in SGST: When writing 1 in SGST with SGACT=0 */

/* SGSTPCR */
#define		ADC_SGSTPCR_SGSTP				(BIT0)			/* Stop scan group */
	#define		ADC_SGSTPCR_SGST_SCAN_NOTSTOP	(0U)		/* No function */
	#define		ADC_SGSTPCR_SGST_SCAN_STOP		(1U)		/* Scan group x Stop condition at SGSTP: When writing 1 to SGSTP with SGACT=1 */

/* ADTSTCR */
#define		ADC_ADTSTCR_ADTST				(BIT0)			/* Start A/D timer */
	#define		ADC_ADTSTCR_ADTST_NOTSTART		(0U)		/* No function */
	#define		ADC_ADTSTCR_ADTST_START			(1U)		/* ADTSTA/D timer y start condition: When writing 1 in SGST with ADTACT=0 */

/* ADTENDCR */
#define		ADC_ADTENDCR_ADTEND				(BIT0)			/* A/D timer ends */
	#define		ADC_ADTSTCR_ADTEND_NOTSTOP		(0U)		/* No function */
	#define		ADC_ADTSTCR_ADTEND_STOP			(1U)		/* ADTSTA/D timer y Stop condition: When writing 1 in SGST with ADTACT=1 */

/* ADTIPR */
#define		ADC_ADTIPR_ADTIP				(0x001FFFFFU)
#define		ADC_ADTIPR_ADTIP_0				(BIT0)			/* AD timer initial phase */

/* ADTPRR */
#define		ADC_ADTPRR_ADTPR				(0x001FFFFFU)
#define		ADC_ADTPRR_ADTPR_0				(BIT0)			/* AD timer period */

/* SGSR */
#define		ADC_SGSR_ADTACT					(BIT2)			/* AD timer status (x=3,4) */
	#define		ADC_SGSR_ADTACT_IDLE			(0U)
	#define		ADC_SGSR_ADTACT_RUNNITG			(1U)
#define		ADC_SGSR_SGACT					(BIT1)			/* Scan Group Status */
	#define		ADC_SGSR_SGACT_IDLE				(0U)
	#define		ADC_SGSR_SGACT_BUSY				(1U)

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
/* PWDCR */
#define		ADC_PWDCR_PWE					(BIT0)			/* PWM-Diag enabled */
	#define		ADC_PWDCR_PWE_DISABLE			(0U)		/* PWM-Diag disabled */
	#define		ADC_PWDCR_PWE_ENABLE			(1U)		/* PWM-Diag Allowed */
#define		ADC_PWDCR_DEFBIT				(ADC_PWDCR_PWE)

/* PWDSGCR */
#define		ADC_PWDSGCR_TRGMD				(BIT0)			/* PWM-Diag Trigger Mode */
	#define		ADC_PWDSGCR_TRGMD_SOFT			(0U)		/* Trigger input to PWM-Diag disabled */
	#define		ADC_PWDSGCR_TRGMD_HARD			(1U)		/* Select hardware trigger for trigger input to PWM-Diag */

#elif	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
/* SGDIAGCR 	*/
#define		ADC_SGDIAGCR_VCULLMTBS1			(BIT23 + BIT22 + BIT21 + BIT20)
#define		ADC_SGDIAGCR_VCULLMTBS1_0		(BIT20)
	#define		ADC_SGDIAGCR_VCULLMTBS1_DISABLED	(0U)		/* Disable    Select (default) */
	#define		ADC_SGDIAGCR_VCULLMTBS1_VCULL0		(1U)		/* VCULLMTBR0 select */
	#define		ADC_SGDIAGCR_VCULLMTBS1_VCULL1		(2U)		/* VCULLMTBR1 select */
	#define		ADC_SGDIAGCR_VCULLMTBS1_VCULL2		(3U)		/* VCULLMTBR2 select */
	#define		ADC_SGDIAGCR_VCULLMTBS1_VCULL3		(4U)		/* VCULLMTBR3 select */
	#define		ADC_SGDIAGCR_VCULLMTBS1_VCULL4		(5U)		/* VCULLMTBR4 select */
	#define		ADC_SGDIAGCR_VCULLMTBS1_VCULL5		(6U)		/* VCULLMTBR5 select */
	#define		ADC_SGDIAGCR_VCULLMTBS1_VCULL6		(7U)		/* VCULLMTBR6 select */
	#define		ADC_SGDIAGCR_VCULLMTBS1_VCULL7		(8U)		/* VCULLMTBR7 select */
#define		ADC_SGDIAGCR_VCULLMTBS0			(BIT19 + BIT18 + BIT17 + BIT16)
#define		ADC_SGDIAGCR_VCULLMTBS0_0		(BIT16)
	#define		ADC_SGDIAGCR_VCULLMTBS0_DISABLED	(0U)		/* Disable    Select (default) */
	#define		ADC_SGDIAGCR_VCULLMTBS0_VCULL0		(1U)		/* VCULLMTBR0 select */
	#define		ADC_SGDIAGCR_VCULLMTBS0_VCULL1		(2U)		/* VCULLMTBR1 select */
	#define		ADC_SGDIAGCR_VCULLMTBS0_VCULL2		(3U)		/* VCULLMTBR2 select */
	#define		ADC_SGDIAGCR_VCULLMTBS0_VCULL3		(4U)		/* VCULLMTBR3 select */
	#define		ADC_SGDIAGCR_VCULLMTBS0_VCULL4		(5U)		/* VCULLMTBR4 select */
	#define		ADC_SGDIAGCR_VCULLMTBS0_VCULL5		(6U)		/* VCULLMTBR5 select */
	#define		ADC_SGDIAGCR_VCULLMTBS0_VCULL6		(7U)		/* VCULLMTBR6 select */
	#define		ADC_SGDIAGCR_VCULLMTBS0_VCULL7		(8U)		/* VCULLMTBR7 select */
#define		ADC_SGDIAGCR_SMD				(BIT12)				/* Subtraction Type Select															*/
	#define		ADC_SGDIAGCR_SMD_MODE0				(0U)
	#define		ADC_SGDIAGCR_SMD_MODE1				(1U)
#define		ADC_SGDIAGCR_ISM				(BIT10)				/* SG-Diag End Interrupt Mode Select												*/
	#define		ADC_SGDIAGCR_ISM_EVERYTIME			(0U)		/* An interrupt is output every time when diag scan is end.							*/
	#define		ADC_SGDIAGCR_ISM_LASTPHCH			(1U)		/* An interrupt is output only when diag scan of the last physical channel is end.	*/
#define		ADC_SGDIAGCR_SDPS				(BIT9)				/* Diag Scan Group End Pointer Select												*/
	#define		ADC_SGDIAGCR_SDPS_CH2				(0U)		/* SG-Diag virtual channel 2 is set for end pointer.								*/
	#define		ADC_SGDIAGCR_SDPS_CH0				(1U)		/* SG-Diag virtual channel 0 is set for end pointer.								*/
#define		ADC_SGDIAGCR_ADIE				(BIT8)				/* SG-Diag End Interrupt															*/
	#define		ADC_SGDIAGCR_ADIE_DISABLE			(0U)
	#define		ADC_SGDIAGCR_ADIE_ENABLE			(1U)
#define		ADC_SGDIAGCR_TRGMD				(BIT0)				/* hardware triggers of Diag scan groups											*/
	#define		ADC_SGDIAGCR_TRGMD_DISABLE			(0U)
	#define		ADC_SGDIAGCR_TRGMD_ENABLE			(1U)

/* SGDIAGPCCR0	*/
/* SGDIAGPCCR1	*/
#define		ADC_SGDIAGPCCR_SDPCE39			(BIT7)			/* SG-Diag Physical Channel Enable ch39	*/
#define		ADC_SGDIAGPCCR_SDPCE38			(BIT6)			/* SG-Diag Physical Channel Enable ch38	*/
#define		ADC_SGDIAGPCCR_SDPCE37			(BIT5)			/* SG-Diag Physical Channel Enable ch37	*/
#define		ADC_SGDIAGPCCR_SDPCE36			(BIT4)			/* SG-Diag Physical Channel Enable ch36	*/
#define		ADC_SGDIAGPCCR_SDPCE35			(BIT3)			/* SG-Diag Physical Channel Enable ch35	*/
#define		ADC_SGDIAGPCCR_SDPCE34			(BIT2)			/* SG-Diag Physical Channel Enable ch34	*/
#define		ADC_SGDIAGPCCR_SDPCE33			(BIT1)			/* SG-Diag Physical Channel Enable ch33	*/
#define		ADC_SGDIAGPCCR_SDPCE32			(BIT0)			/* SG-Diag Physical Channel Enable ch32	*/
#define		ADC_SGDIAGPCCR_SDPCE31			(BIT31)			/* SG-Diag Physical Channel Enable ch31	*/
#define		ADC_SGDIAGPCCR_SDPCE30			(BIT30)			/* SG-Diag Physical Channel Enable ch30	*/
#define		ADC_SGDIAGPCCR_SDPCE29			(BIT29)			/* SG-Diag Physical Channel Enable ch29	*/
#define		ADC_SGDIAGPCCR_SDPCE28			(BIT28)			/* SG-Diag Physical Channel Enable ch28	*/
#define		ADC_SGDIAGPCCR_SDPCE27			(BIT27)			/* SG-Diag Physical Channel Enable ch27	*/
#define		ADC_SGDIAGPCCR_SDPCE26			(BIT26)			/* SG-Diag Physical Channel Enable ch26	*/
#define		ADC_SGDIAGPCCR_SDPCE25			(BIT25)			/* SG-Diag Physical Channel Enable ch25	*/
#define		ADC_SGDIAGPCCR_SDPCE24			(BIT24)			/* SG-Diag Physical Channel Enable ch24	*/
#define		ADC_SGDIAGPCCR_SDPCE23			(BIT23)			/* SG-Diag Physical Channel Enable ch23	*/
#define		ADC_SGDIAGPCCR_SDPCE22			(BIT22)			/* SG-Diag Physical Channel Enable ch22	*/
#define		ADC_SGDIAGPCCR_SDPCE21			(BIT21)			/* SG-Diag Physical Channel Enable ch21	*/
#define		ADC_SGDIAGPCCR_SDPCE20			(BIT20)			/* SG-Diag Physical Channel Enable ch20	*/
#define		ADC_SGDIAGPCCR_SDPCE19			(BIT19)			/* SG-Diag Physical Channel Enable ch19	*/
#define		ADC_SGDIAGPCCR_SDPCE18			(BIT18)			/* SG-Diag Physical Channel Enable ch18	*/
#define		ADC_SGDIAGPCCR_SDPCE17			(BIT17)			/* SG-Diag Physical Channel Enable ch17	*/
#define		ADC_SGDIAGPCCR_SDPCE16			(BIT16)			/* SG-Diag Physical Channel Enable ch16	*/
#define		ADC_SGDIAGPCCR_SDPCE15			(BIT15)			/* SG-Diag Physical Channel Enable ch15	*/
#define		ADC_SGDIAGPCCR_SDPCE14			(BIT14)			/* SG-Diag Physical Channel Enable ch14	*/
#define		ADC_SGDIAGPCCR_SDPCE13			(BIT13)			/* SG-Diag Physical Channel Enable ch13	*/
#define		ADC_SGDIAGPCCR_SDPCE12			(BIT12)			/* SG-Diag Physical Channel Enable ch12	*/
#define		ADC_SGDIAGPCCR_SDPCE11			(BIT11)			/* SG-Diag Physical Channel Enable ch11	*/
#define		ADC_SGDIAGPCCR_SDPCE10			(BIT10)			/* SG-Diag Physical Channel Enable ch10	*/
#define		ADC_SGDIAGPCCR_SDPCE9			(BIT9)			/* SG-Diag Physical Channel Enable ch9	*/
#define		ADC_SGDIAGPCCR_SDPCE8			(BIT8)			/* SG-Diag Physical Channel Enable ch8	*/
#define		ADC_SGDIAGPCCR_SDPCE7			(BIT7)			/* SG-Diag Physical Channel Enable ch7	*/
#define		ADC_SGDIAGPCCR_SDPCE6			(BIT6)			/* SG-Diag Physical Channel Enable ch6	*/
#define		ADC_SGDIAGPCCR_SDPCE5			(BIT5)			/* SG-Diag Physical Channel Enable ch5	*/
#define		ADC_SGDIAGPCCR_SDPCE4			(BIT4)			/* SG-Diag Physical Channel Enable ch4	*/
#define		ADC_SGDIAGPCCR_SDPCE3			(BIT3)			/* SG-Diag Physical Channel Enable ch3	*/
#define		ADC_SGDIAGPCCR_SDPCE2			(BIT2)			/* SG-Diag Physical Channel Enable ch2	*/
#define		ADC_SGDIAGPCCR_SDPCE1			(BIT1)			/* SG-Diag Physical Channel Enable ch1	*/
#define		ADC_SGDIAGPCCR_SDPCE0			(BIT0)			/* SG-Diag Physical Channel Enable ch0	*/
	#define		ADC_SGDIAGPCCR_SDPCEy_NOTCNV	(0U)		/* Not converted						*/
	#define		ADC_SGDIAGPCCR_SDPCEy_CNV		(1U)		/* To be converted						*/

/* SGDIAGSR		*/
#define		ADC_SGDIAGSR_SDACT				(BIT1)			/* Scan Group Status									*/
	#define		ADC_SGDIAGSR_SDACT_IDLE			(0U)		/* The Diag scan group is in idle state.				*/
	#define		ADC_SGDIAGSR_SDACT_RUNNITG		(1U)		/* A/D conversion of the Diag scan group is in progress	*/

/* SGDIAGSTCR	*/
#define		ADC_SGDIAGSTCR_SGST				(BIT0)			/* SG-Diag Start Control Register	*/
	#define		ADC_SGSTCR_SGST_START			(1U)		/* A/D conversion start				*/

/* SGDIAGSTPCR	*/
#define		ADC_SGDIAGSTPCR_SGSTP			(BIT0)			/* SG-Diag Stop Control Register	*/
	#define		ADC_SSGDIAGSTPCR_SGSTP_STOP		(1U)		/* A/D conversion stop				*/

#endif	/* #elif	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )	*/

/* SGSTR */
#define		ADC_SGSTR_ADTACT_4				(BIT13)			/* AD timer status (x=4) */
	#define		ADC_SGSTR_ADTACT_4_IDLE			(0U)		/* AD timer 4 is down */
	#define		ADC_SGSTR_ADTACT_4_RUN			(1U)		/* AD timer 4 is in progress */
#define		ADC_SGSTR_ADTACT_3				(BIT12)			/* AD timer status (x=3) */
	#define		ADC_SGSTR_ADTACT_3_IDLE			(0U)		/* AD timer 3 is stopped */
	#define		ADC_SGSTR_ADTACT_3_RUN			(1U)		/* AD timer 3 in progress */
#define		ADC_SGSTR_SHACT					(BIT7)			/* T&H status */
	#define		ADC_SGSTR_SHACT_STOP			(0U)		/* T&H is stopped */
	#define		ADC_SGSTR_SHACT_PROGRESS		(1U)		/* T&H in progress */
#define		ADC_SGSTR_SVSACT				(BIT6)			/* SVSTOP status */
	#define		ADC_SGSTR_SVSACT_CANSELED		(0U)		/* SVSTOP disabled */
	#define		ADC_SGSTR_SVSACT_ACCEPTED		(1U)		/* SVSTOP allowed */
#define		ADC_SGSTR_SGACT_4				(BIT5)			/* Scan Group 4 (SG4) Status Flag								*/
	#define		ADC_SGSTR_SGACT_4_COMPLETE		(0U)		/* A/D conversion for SG4 is completed.							*/
	#define		ADC_SGSTR_SGACT_4_PROGRESS		(1U)		/* A/D conversion for SG4 is in processing or suspension.		*/
#define		ADC_SGSTR_SGACT_3				(BIT4)			/* Scan Group 0 (SG3) Status Flag								*/
	#define		ADC_SGSTR_SGACT_3_COMPLETE		(0U)		/* A/D conversion for SG3 is completed.							*/
	#define		ADC_SGSTR_SGACT_3_PROGRESS		(1U)		/* A/D conversion for SG3 is in processing or suspension.		*/
#define		ADC_SGSTR_SGACT_2				(BIT3)			/* Scan Group 0 (SG2) Status Flag								*/
	#define		ADC_SGSTR_SGACT_2_COMPLETE		(0U)		/* A/D conversion for SG2 is completed.							*/
	#define		ADC_SGSTR_SGACT_2_PROGRESS		(1U)		/* A/D conversion for SG2 is in processing or suspension.		*/
#define		ADC_SGSTR_SGACT_1				(BIT2)			/* Scan Group 0 (SG1) Status Flag								*/
	#define		ADC_SGSTR_SGACT_1_COMPLETE		(0U)		/* A/D conversion for SG1 is completed.							*/
	#define		ADC_SGSTR_SGACT_1_PROGRESS		(1U)		/* A/D conversion for SG1 is in processing or suspension.		*/
#define		ADC_SGSTR_SGACT_0				(BIT1)			/* Scan Group 0 (SG0) Status Flag								*/
	#define		ADC_SGSTR_SGACT_0_COMPLETE		(0U)		/* A/D conversion for SG0 is completed.							*/
	#define		ADC_SGSTR_SGACT_0_PROGRESS		(1U)		/* A/D conversion for SG0 is in processing or suspension.		*/
#define		ADC_SGSTR_SDACT					(BIT0)			/* SDACT SG-Diag Scan Group Status Flag							*/
	#define		ADC_SGSTR_SDACT_COMPLETE		(0U)		/* A/D conversion for SG-Diag is completed						*/
	#define		ADC_SGSTR_SDACT_PROGRESS		(1U)		/* A/D conversion for SG-Diag is in processing or suspension	*/

/* ADSYNSTCR */
#define		ADC_ADSYNSTCR_ADSTART			(BIT0)			/* Control start of synchronization of ADCJ0 and ADCJ1 (only ADCJ0 is effective) */
	#define		ADC_ADSYNSTCR_ADSTART_START		(1U)		/* Start synchronous A/D conversion */

/* ADTSYNSTCR */
#define		ADC_ADTSYNSTCR_ADTSTART			(BIT0)			/* Control start of synchronous counting operation of A/D timer (valid only for ADCJ0) */
	#define		ADC_ADTSYNSTCR_ADSTART_START	(1U)		/* A/D timer synchronous counting operation started */

/* SGTSELx */
#define		ADC_SGTSELX_TXSEL_5				(BIT5)			/* Trigger mode (valid only for ADCJ2) */			
#define		ADC_SGTSELX_TXSEL_4				(BIT4)			/* Trigger mode (valid only for ADCJ2) */
#define		ADC_SGTSELX_TXSEL_3				(BIT3)			/* Trigger mode (valid only for ADCJ2) */
#define		ADC_SGTSELX_TXSEL_2				(BIT2)			/* Trigger mode (valid only for ADCJ2) */
#define		ADC_SGTSELX_TXSEL_1				(BIT1)			/* Trigger mode (valid only for ADCJ2) */
#define		ADC_SGTSELX_TXSEL_0				(BIT0)			/* Trigger mode (valid only for ADCJ2) */
	#define		ADC_SGTSELX_TXSEL_SOFT			(0U)		/* Trigger input to SGx disabled */
	#define		ADC_SGTSELX_TXSEL_HARD			(1U)		/* select SGx_TRG hardware trigger for trigger input to SGx */
#define		ADC_SGTSEL_DEFBIT				(ADC_SGTSELX_TXSEL_5|ADC_SGTSELX_TXSEL_4|ADC_SGTSELX_TXSEL_3|ADC_SGTSELX_TXSEL_2|ADC_SGTSELX_TXSEL_1|ADC_SGTSELX_TXSEL_0)

/* ADHALTR */
#define		ADC_ADHALTR_HALT				(BIT0)			/* END */
	#define		ADC_ADHALTR_HALT_SCAN_NOTHALT	(0U)		/* Don't quit */
	#define		ADC_ADHALTR_HALT_SCAN_HALT		(1U)		/* EXIT */

/* ADCR1 */
#define		ADC_ADCR1_SUSMTD				(BIT1 + BIT0)
#define		ADC_ADCR1_SUSMTD_0				(BIT0)			/* Suspend method */
	#define		ADC_ADCR1_SUSMTD_SYNC			(0U)		/* Synchronous Suspend */
	#define		ADC_ADCR1_SUSMTD_ASYNC_SG0		(1U)		/* Asynchronous suspend when high priority SG interrupts SG0/Synchronous suspend when high priority SG interrupts low priority SG (except SG0) */
	#define		ADC_ADCR1_SUSMTD_ASYNC			(2U)		/* Asynchronous suspend */
#define		ADC_ADCR1_DEFBIT				(ADC_ADCR1_SUSMTD)

/* ADCR2 */
#define		ADC_ADCR2_DFMT					(BIT6 + BIT5 + BIT4)
#define		ADC_ADCR2_DFMT_0				(BIT4)			/* Data Format */
	#define		ADC_ADCR2_DFMT_12BIT_FIXED_POINT		(0U)		/* 12BIT signed fixed-point format */
	#define		ADC_ADCR2_DFMT_12BIT_INT				(1U)		/* 12BIT signed integer format */
	#define		ADC_ADCR2_DFMT_12BIT_UNFIXED_POINT		(2U)		/* 12BIT unsigned fixed-point format */
	#define		ADC_ADCR2_DFMT_10BIT_UNFIXED_POINT		(3U)		/* 10BIT unsigned fixed-point format */
	#define		ADC_ADCR2_DFMT_12BIT_UNINT_R			(4U)		/* 12BIT unsigned integer format right-justified */
	#define		ADC_ADCR2_DFMT_12BIT_UNINT_L			(5U)		/* 12BIT unsigned integer format left-justified */
#define		ADC_ADCR2_ADDNT					(BIT0)			/* Addition count selection */
	#define		ADC_ADCR2_ADDNT_2TIMES			(0U)		/* Add twice */
	#define		ADC_ADCR2_ADDNT_4TIMES			(1U)		/* Add four times */
#define		ADC_ADCR2_DEFBIT				(ADC_ADCR2_DFMT|ADC_ADCR2_ADDNT)

/* SMPCR */
#define		ADC_SMPCR_EXSMPT				(BIT23 + BIT22 + BIT21 + BIT20 + BIT19 + BIT18 + BIT17 + BIT16)
#define		ADC_SMPCR_EXSMPT_0				(BIT16)			/* Extended Sampling Period	*/
	#define		ADC_SMPCR_EXSMPT_60STATES		(0x00U)		/* 60states					*/
	#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2A)
	#define		ADC_SMPCR_EXSMPT_99STATES		(0x63U)		/* 99states					*/
	#elif (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B) 
	#define		ADC_SMPCR_EXSMPT_102STATES		(0x66U)		/* 102states				*/
	#endif
	#define		ADC_SMPCR_EXSMPT_138STATES		(0x8AU)		/* 138states				*/
	#define		ADC_SMPCR_EXSMPT_252STATES		(0xFCU)		/* 252states				*/
#define		ADC_SMPCR_BUFAMPD				(BIT15)			/* With/without buffer amplifier */
	#define		ADC_SMPCR_BUFAMPD_ENABLE		(0U)		/* Use buffer amplifier */
	#define		ADC_SMPCR_BUFAMPD_DISABLE		(1U)		/* No buffer amplifier */
#define		ADC_SMPCR_SMPTS					(BIT12)			/* Sampling period selection */
	#define		ADC_SMPCR_SMPTS_DISABLE			(0U)		/* No SMPT */
	#define		ADC_SMPCR_SMPTS_ENABLE			(1U)		/* SMPT used */
#define		ADC_SMPCR_SMPT					(BIT7 + BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)
#define		ADC_SMPCR_SMPT_0				(BIT0)			/* Sampling period */
	#define		ADC_SMPCR_SMPT_18STATES			(0x00U)		/* 18states */
	#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2A)
	#define		ADC_SMPCR_SMPT_99STATES			(0x63U)		/* 99states */
	#elif (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B) 
	#define		ADC_SMPCR_SMPT_102STATES		(0x66U)		/* 102states */
	#endif
	#define		ADC_SMPCR_SMPT_204STATES		(0xCCU)		/* 204states */
	#define		ADC_SMPCR_SMPT_252STATES		(0xFCU)		/* 252states */
#define		ADC_SMPCR_DEFBIT				(ADC_SMPCR_BUFAMPD|ADC_SMPCR_SMPTS|ADC_SMPCR_SMPT)

/* MPXCURCR */
#define		ADC_MPXCURCR_MSKCFMT			(BIT3 + BIT2 + BIT1 + BIT0)
#define		ADC_MPXCURCR_MSKCFMT_0			(BIT0)			/* MSKC format specification */
	#define		ADC_MPXCURCR_MSKCFMT_MSKC0		(0U)		/* MSKCFMT[3]=MSKC[15:12],MSKCFMT[2]=MSKC[11:8],MSKCFMT[1]=MSKC[7:4],MSKCFMT[0]=MSKC[3:0] = 0000 */
	#define		ADC_MPXCURCR_MSKCFMT_MSKC1		(1U)		/* MSKCFMT[3]=MSKC[15:12],MSKCFMT[2]=MSKC[11:8],MSKCFMT[1]=MSKC[7:4],MSKCFMT[0]=MSKC[3:0] = 1111 */

/* MPXINTER */
#define		ADC_MPXINTER_ADMPXIE			(BIT0)			/* MPX interrupt enable */
	#define		ADC_MPXINTER_ADMPXIE_NOTOUTPUT	(0U)		/* No ADMPXIn output */
	#define		ADC_MPXINTER_ADMPXIE_OUTPUT		(1U)		/* ADMPXIn output */

/* MPXCURR1 */
#define		ADC_MPXCURR1_MSKC				(0xFFFF0000U)
#define		ADC_MPXCURR1_MSKC_0				(BIT16)			/* Mask control */
#define		ADC_MPXCURR1_MPXCMD				(0x0000FF00U)
#define		ADC_MPXCURR1_MPXCMD_0			(BIT8)			/* SPI communication command information */
#define		ADC_MPXCURR1_MPXCUR				(BIT2 + BIT1 + BIT0)
#define		ADC_MPXCURR1_MPXCUR_0			(BIT0)			/* Current MPX value */

/* MPXCURR2 */
#define		ADC_MPXCURR2_MPXCUR				(BIT2 + BIT1 + BIT0)
#define		ADC_MPXCURR2_MPXCUR_0			(BIT0)			/* Current MPX value */

/* MPXCMDR */
#define		ADC_MPXCMDR_MPXCMD				(0xFFU)
#define		ADC_MPXCMDR_MPXCMD_0			(BIT0)			/* SPI communication command information */

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
/* GTMENTSGER */
#define		ADC_GTMENTSGER_GTMENTSGXE		(BIT12 + BIT11 + BIT10 + BIT9 + BIT8)
#define		ADC_GTMENTSGER_GTMENTSG4E		(BIT12)			/* GTM entry for SG4 */
	#define		ADC_GTMENTSGER_GTMENTSG4E_DISABLE	(0U)
	#define		ADC_GTMENTSGER_GTMENTSG4E_ENABLE	(1U)
#define		ADC_GTMENTSGER_GTMENTSG3E		(BIT11)			/* GTM entry for SG3 */
	#define		ADC_GTMENTSGER_GTMENTSG3E_DISABLE	(0U)
	#define		ADC_GTMENTSGER_GTMENTSG3E_ENABLE	(1U)
#define		ADC_GTMENTSGER_GTMENTSG2E		(BIT10)			/* GTM entry for SG2 */
	#define		ADC_GTMENTSGER_GTMENTSG2E_DISABLE	(0U)
	#define		ADC_GTMENTSGER_GTMENTSG2E_ENABLE	(1U)
#define		ADC_GTMENTSGER_GTMENTSG1E		(BIT9)			/* GTM entry for SG1 */
	#define		ADC_GTMENTSGER_GTMENTSG1E_DISABLE	(0U)
	#define		ADC_GTMENTSGER_GTMENTSG1E_ENABLE	(1U)
#define		ADC_GTMENTSGER_GTMENTSG0E		(BIT8)			/* GTM entry for SG0 */
	#define		ADC_GTMENTSGER_GTMENTSG0E_DISABLE	(0U)
	#define		ADC_GTMENTSGER_GTMENTSG0E_ENABLE	(1U)

#elif	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
/* DFASENTSGER */
#define		ADC_DFASENTSGER_DFENTSGXE		(BIT12 + BIT11 + BIT10 + BIT9 + BIT8)
#define		ADC_DFASENTSGER_DFENTSG4E		(BIT12)			/* SG4:DFE and GTM entry Scan Group Enable	*/
	#define		ADC_DFASENTSGER_DFENTSG4E_DISABLE	(0U)
	#define		ADC_DFASENTSGER_DFENTSG4E_ENABLE	(1U)
#define		ADC_DFASENTSGER_DFENTSG3E		(BIT11)			/* SG3:DFE and GTM entry Scan Group Enable	*/
	#define		ADC_DFASENTSGER_DFENTSG3E_DISABLE	(0U)
	#define		ADC_DFASENTSGER_DFENTSG3E_ENABLE	(1U)
#define		ADC_DFASENTSGER_DFENTSG2E		(BIT10)			/* SG2:DFE and GTM entry Scan Group Enable	*/
	#define		ADC_DFASENTSGER_DFENTSG2E_DISABLE	(0U)
	#define		ADC_DFASENTSGER_DFENTSG2E_ENABLE	(1U)
#define		ADC_DFASENTSGER_DFENTSG1E		(BIT9)			/* SG1:DFE and GTM entry Scan Group Enable	*/
	#define		ADC_DFASENTSGER_DFENTSG1E_DISABLE	(0U)
	#define		ADC_DFASENTSGER_DFENTSG1E_ENABLE	(1U)
#define		ADC_DFASENTSGER_DFENTSG0E		(BIT8)			/* SG0:DFE and GTM entry Scan Group Enable	*/
	#define		ADC_DFASENTSGER_DFENTSG0E_DISABLE	(0U)
	#define		ADC_DFASENTSGER_DFENTSG0E_ENABLE	(1U)
#define		ADC_DFASENTSGER_ASENTSGXE		(BIT4 + BIT3 + BIT2 + BIT1 + BIT0)
#define		ADC_DFASENTSGER_ASENTSG4E		(BIT4)			/* SG4:ASF Entry Scan Group Enable			*/
	#define		ADC_DFASENTSGER_ASENTSG4E_DISABLE	(0U)
	#define		ADC_DFASENTSGER_ASENTSG4E_ENABLE	(1U)
#define		ADC_DFASENTSGER_ASENTSG3E		(BIT3)			/* SG3:ASF Entry Scan Group Enable			*/
	#define		ADC_DFASENTSGER_ASENTSG3E_DISABLE	(0U)
	#define		ADC_DFASENTSGER_ASENTSG3E_ENABLE	(1U)
#define		ADC_DFASENTSGER_ASENTSG2E		(BIT2)			/* SG2:ASF Entry Scan Group Enable			*/
	#define		ADC_DFASENTSGER_ASENTSG2E_DISABLE	(0U)
	#define		ADC_DFASENTSGER_ASENTSG2E_ENABLE	(1U)
#define		ADC_DFASENTSGER_ASENTSG1E		(BIT1)			/* SG1:ASF Entry Scan Group Enable			*/
	#define		ADC_DFASENTSGER_ASENTSG1E_DISABLE	(0U)
	#define		ADC_DFASENTSGER_ASENTSG1E_ENABLE	(1U)
#define		ADC_DFASENTSGER_ASENTSG0E		(BIT0)			/* SG0:ASF Entry Scan Group Enable			*/
	#define		ADC_DFASENTSGER_ASENTSG0E_DISABLE	(0U)
	#define		ADC_DFASENTSGER_ASENTSG0E_ENABLE	(1U)

#endif

/* ADENDP */
#define		ADC_ADENDP_ENDP					(BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)
#define		ADC_ADENDP_ENDP_0				(BIT0)			/* AD conversion monitor virtual channel pointer */

/* THSMPSTCR */
#define		ADC_THSMPSTCR_SMPST				(BIT0)			/* T&H sampling start control */
	#define		ADC_THSMPSTCR_SMPST_NOTSTART	(0U)
	#define		ADC_THSMPSTCR_SMPST_START		(1U)
#define		ADC_THSMPSTCR_DEFBIT			(ADC_THSMPSTCR_SMPST)

/* THSTPCR */
#define		ADC_THSTPCR_THSTP				(BIT0)			/* T&H sampling stop control */
	#define		ADC_THSTPCR_THSTP_NOTSTOP		(0U)
	#define		ADC_THSTPCR_THSTP_STOP			(1U)

/* THCR */
#define		ADC_THCR_ASMPMSK				(BIT0)			/* Control T& H's automatic sampling function */
	#define		ADC_THCR_ASMPMSK_AUTO			(0U)
	#define		ADC_THCR_ASMPMSK_NOTAUTO		(1U)
#define		ADC_THCR_DEFBIT				(ADC_THCR_ASMPMSK)

/* THAHLDSTCR */
#define		ADC_THAHLDSTCR_HLDST			(BIT0)			/* Control start of hold for T&H Group A */
	#define		ADC_THAHLDSTCR_HLDST_NOTSTART	(0U)
	#define		ADC_THAHLDSTCR_HLDST_START		(1U)

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
/* THBHLDSTCR */
#define		ADC_THBHLDSTCR_HLDST			(BIT0)			/* Control the start of T&H Group B hold */
	#define		ADC_THBHLDSTCR_HLDST_NOTSTART	(0U)
	#define		ADC_THBHLDSTCR_HLDST_START		(1U)

/* THGSR */
#define		ADC_THGSR_TH5GS					(BIT10)
	#define		ADC_THGSR_TH5GS_SELECTED_A		(0U)
	#define		ADC_THGSR_TH5GS_SELECTED_B		(1U)
#define		ADC_THGSR_TH4GS					(BIT8)
	#define		ADC_THGSR_TH4GS_SELECTED_A		(0U)
	#define		ADC_THGSR_TH4GS_SELECTED_B		(1U)
#define		ADC_THGSR_TH3GS					(BIT6)
	#define		ADC_THGSR_TH3GS_SELECTED_A		(0U)
	#define		ADC_THGSR_TH3GS_SELECTED_B		(1U)
#define		ADC_THGSR_TH2GS					(BIT4)
	#define		ADC_THGSR_TH2GS_SELECTED_A		(0U)
	#define		ADC_THGSR_TH2GS_SELECTED_B		(1U)
#define		ADC_THGSR_TH1GS					(BIT2)
	#define		ADC_THGSR_TH1GS_SELECTED_A		(0U)
	#define		ADC_THGSR_TH1GS_SELECTED_B		(1U)
#define		ADC_THGSR_TH0GS					(BIT0)
	#define		ADC_THGSR_TH0GS_SELECTED_A		(0U)
	#define		ADC_THGSR_TH0GS_SELECTED_B		(1U)
#define		ADC_THGSR_DEFBIT				(ADC_THGSR_TH5GS|ADC_THGSR_TH4GS|ADC_THGSR_TH3GS|ADC_THGSR_TH2GS|ADC_THGSR_TH1GS|ADC_THGSR_TH0GS)
#endif

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
/* THER */
#define		ADC_THER_THZE					(BIT3 + BIT2 + BIT1 + BIT0)
#define		ADC_THER_TH3E					(BIT3)			/* Enable control of T&H */
#define		ADC_THER_TH2E					(BIT2)
#define		ADC_THER_TH1E					(BIT1)
#define		ADC_THER_TH0E					(BIT0)
	#define		ADC_THER_THZE_DISABLE			(0U)
	#define		ADC_THER_THZE_ENABLE			(1U)
#elif	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
/* THER */
#define		ADC_THER_THZE					(BIT5 + BIT4 +BIT3 + BIT2 + BIT1 + BIT0)
#define		ADC_THER_TH5E					(BIT5)			/* Enable control of T&H */
#define		ADC_THER_TH4E					(BIT4)
#define		ADC_THER_TH3E					(BIT3)
#define		ADC_THER_TH2E					(BIT2)
#define		ADC_THER_TH1E					(BIT1)
#define		ADC_THER_TH0E					(BIT0)
	#define		ADC_THER_THZE_DISABLE			(0U)
	#define		ADC_THER_THZE_ENABLE			(1U)
#endif
#define		ADC_THER_DEFBIT				(ADC_THER_THZE)

/* THACR */
#define		ADC_THACR_HLDCTE				(BIT5)			/* Hold control enabled */
	#define		ADC_THACR_HLDCTE_DISABLE		(0U)
	#define		ADC_THACR_HLDCTE_ENABLE			(1U)
#define		ADC_THACR_HLDTE					(BIT4)			/* hold trigger enable */
	#define		ADC_THACR_HLDTE_DISABLE			(0U)
	#define		ADC_THACR_HLDTE_ENABLE			(1U)
#define		ADC_THACR_SGS					(BIT1 + BIT0)
#define		ADC_THACR_SGS_0					(BIT0)			/* Select SG */
	#define		ADC_THACR_SGS_SG1				(0U)
	#define		ADC_THACR_SGS_SG2				(1U)
	#define		ADC_THACR_SGS_SG3				(2U)
	#define		ADC_THACR_SGS_SG4				(3U)
#define		ADC_THACR_DEFBIT				(ADC_THACR_HLDCTE|ADC_THACR_HLDTE|ADC_THACR_SGS)

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
/* THBCR */
#define		ADC_THBCR_HLDCTE				(BIT5)			/* Hold control enabled */
	#define		ADC_THBCR_HLDCTE_DISABLE		(0U)
	#define		ADC_THBCR_HLDCTE_ENABLE			(1U)
#define		ADC_THBCR_HLDTE					(BIT4)			/* hold trigger enable */
	#define		ADC_THBCR_HLDTE_DISABLE			(0U)
	#define		ADC_THBCR_HLDTE_ENABLE			(1U)
#define		ADC_THBCR_SGS					(BIT1 + BIT0)
#define		ADC_THBCR_SGS_0					(BIT0)			/* Select SG */
	#define		ADC_THBCR_SGS_SG1				(0U)
	#define		ADC_THBCR_SGS_SG2				(1U)
	#define		ADC_THBCR_SGS_SG3				(2U)
	#define		ADC_THBCR_SGS_SG4				(3U)
#define		ADC_THBCR_DEFBIT				(ADC_THBCR_HLDCTE|ADC_THBCR_HLDTE|ADC_THBCR_SGS)
#endif

/* WAITTR */
#define		ADC_WAITTR_WAITTIME				(0x3FFFU)
#define		ADC_WAITTR_WAITTIME_0			(BIT0)			/* Waiting time */

/* VMONVDCR1 */
#define		ADC_VMONVDCR1_VDE1				(BIT0)			/* Voltage divider enable (resistance-voltage divider control) */

/* VMONVDCR2 */
#define		ADC_VMONVDCR2_VDE2				(BIT0)			/* Voltage divider enable (resistance-voltage divider control) */

/* TDCR */
#define		ADC_TDCR_THSDE					(BIT7)			/* Terminal-level self-diagnostic enable */
	#define		ADC_TDCR_THSDE_DISABLE			(0U)		/* Don't do terminal level self-diagnosis */
	#define		ADC_TDCR_THSDE_ENABLE			(1U)		/* Do terminal level self-diagnosis */
#define		ADC_TDCR_TDLV					(BIT1 + BIT0)
#define		ADC_TDCR_TDLV_0					(BIT0)			/* Terminal level self-diagnostic level specification */
	#define		ADC_TDCR_TDLV_LEVEL0			(0U)		/* Discharge even physical channel group to AVSS, charge odd physical channel group to AVCC */
	#define		ADC_TDCR_TDLV_LEVEL1			(1U)		/* Charge an even physical channel group to AVCC and discharge an odd physical channel group to AVSS */
	#define		ADC_TDCR_TDLV_LEVEL2			(2U)		/* Discharge an even physical channel group to AVSS and an odd physical channel group to 1/2* Charge AVCC */
	#define		ADC_TDCR_TDLV_LEVEL3			(3U)		/* Charge an even physical channel group to 1/2*AVCC and discharge an odd physical channel group to AVSS */

/* ODCR */
#define		ADC_ODCR_WADDE					(BIT8)			/* Enable disconnect detection in additional mode */
	#define		ADC_ODCR_WADDE_NORMAL			(0U)		/* Perform A/D conversion of disconnect detection mode in normal mode */
	#define		ADC_ODCR_WADDE_ADDITION			(1U)		/* Perform A/D conversion of disconnect detection mode in add mode */
#define		ADC_ODCR_ODPW					(BIT4 + BIT3 + BIT2 + BIT1 + BIT0)
#define		ADC_ODCR_ODPW_0					(BIT0)
	#define		ADC_ODCR_ODPW_STATE1			(0x04U)		/* 1state (internal clock equivalent) */
	#define		ADC_ODCR_ODPW_STATE2			(0x05U)		/* 2-state (internal clock equivalent) */
	#define		ADC_ODCR_ODPW_STATE3			(0x06U)		/* 3 states (internal clock equivalent) */
	#define		ADC_ODCR_ODPW_STATE4			(0x07U)		/* 4 states (internal clock equivalent) */
	#define		ADC_ODCR_ODPW_STATE5			(0x08U)		/* 5 states (internal clock equivalent) */
	#define		ADC_ODCR_ODPW_STATE6			(0x09U)		/* 6 states (internal clock equivalent) */
	#define		ADC_ODCR_ODPW_STATE7			(0x0AU)		/* 7 states (internal clock equivalent) */
	#define		ADC_ODCR_ODPW_STATE8			(0x0BU)		/* 8 states (internal clock equivalent) */
	#define		ADC_ODCR_ODPW_STATE9			(0x0CU)		/* 9 states (internal clock equivalent) */
	#define		ADC_ODCR_ODPW_STATE10			(0x0DU)		/* 10 states (internal clock equivalent) */
	#define		ADC_ODCR_ODPW_STATE11			(0x0EU)		/* 11 states (internal clock equivalent) */
	#define		ADC_ODCR_ODPW_STATE12			(0x0FU)		/* 12 states (internal clock equivalent) */
	#define		ADC_ODCR_ODPW_STATE13			(0x10U)		/* 13 states (internal clock equivalent) */
	#define		ADC_ODCR_ODPW_STATE14			(0x11U)		/* 14 states (internal clock equivalent) */
	#define		ADC_ODCR_ODPW_STATE15			(0x12U)		/* 15 states (internal clock equivalent) */
	#define		ADC_ODCR_ODPW_STATE16			(0x13U)		/* 16 states (internal clock equivalent) */
	#define		ADC_ODCR_ODPW_STATE17			(0x14U)		/* 17 states (internal clock equivalent) */

/* SFTCR */
#define		ADC_SFTCR_TOCEIE				(BIT6)			/* Trigger overlap check error interrupt enabled */
	#define		ADC_SFTCR_TOCEIE_DISABLE		(0U)		/* Forbidden */
	#define		ADC_SFTCR_TOCEIE_ENABLE			(1U)		/* Allowed */
#define		ADC_SFTCR_RDCLRE				(BIT4)			/* LEAD & CLEAR ENABLE */
	#define		ADC_SFTCR_RDCLRE_DR_NOCLR		(0U)		/* ADCBmDRn or ADCBmDIRn leads and ADCBmDRn leads via IFC do not clear ADCBmDRn and ADCBmDIRn */
	#define		ADC_SFTCR_RDCLRE_DR_CLR			(1U)		/* Clear ADCBmDRn and ADCBmDIRn with ADCBmDRn or ADCBmDIRn leads and ADCBmDRn leads via IFC */
#define		ADC_SFTCR_OWEIE					(BIT2)			/* Overwrite error interrupt enable */
	#define		ADC_SFTCR_OWEIE_DISABLE			(0U)		/* Forbidden */
	#define		ADC_SFTCR_OWEIE_ENABLE			(1U)		/* Allowed */
#define		ADC_SFTCR_PEIE					(BIT1)			/* Parity error interrupt enable */
	#define		ADC_SFTCR_PEIE_DISABLE			(0U)		/* Forbidden */
	#define		ADC_SFTCR_PEIE_ENABLE			(1U)		/* Allowed */
#define		ADC_SFTCR_IDEIE					(BIT0)			/* ID error interrupt enable */
	#define		ADC_SFTCR_IDEIE_DISABLE			(0U)		/* Forbidden */
	#define		ADC_SFTCR_IDEIE_ENABLE			(1U)		/* Allowed */
#define		ADC_SFTCR_DEFBIT				(ADC_SFTCR_TOCEIE|ADC_SFTCR_RDCLRE|ADC_SFTCR_OWEIE|ADC_SFTCR_PEIE|ADC_SFTCR_IDEIE)

/* TOCCR */
#define		ADC_TOCCR_TOCE					(BIT0)			/* Trigger overlap check function enabled */
	#define		ADC_TOCCR_TOCE_DISABLE			(0U)		/* Invalid */
	#define		ADC_TOCCR_TOCE_ENABLE			(1U)		/* Valid */
#define		ADC_TOCCR_DEFBIT				(ADC_TOCCR_TOCE)

/* TOCER */
#define		ADC_TOCER_TOCESG				(BIT5 + BIT4 + BIT3 + BIT2 + BIT1)
#define		ADC_TOCER_TOCESG_4				(BIT5)			/* Trigger overlap check error on SG4 */
	#define		ADC_TOCER_TOCESG_4_NOERROR		(0U)		/* Invalid */
	#define		ADC_TOCER_TOCESG_4_ERROR		(1U)		/* Valid */
#define		ADC_TOCER_TOCESG_3				(BIT4)			/* Trigger overlap check error on SG3 */
	#define		ADC_TOCER_TOCESG_3_NOERROR		(0U)		/* Invalid */
	#define		ADC_TOCER_TOCESG_3_ERROR		(1U)		/* Valid */
#define		ADC_TOCER_TOCESG_2				(BIT3)			/* Trigger overlap check error in SG2 */
	#define		ADC_TOCER_TOCESG_2_NOERROR		(0U)		/* Invalid */
	#define		ADC_TOCER_TOCESG_2_ERROR		(1U)		/* Valid */
#define		ADC_TOCER_TOCESG_1				(BIT2)			/* Trigger overlap check error in SG1 */
	#define		ADC_TOCER_TOCESG_1_NOERROR		(0U)		/* Invalid */
	#define		ADC_TOCER_TOCESG_1_ERROR		(1U)		/* Valid */
#define		ADC_TOCER_TOCESG_0				(BIT1)			/* Trigger overlap check error on SG0 */
	#define		ADC_TOCER_TOCESG_0_NOERROR		(0U)		/* Invalid */
	#define		ADC_TOCER_TOCESG_0_ERROR		(1U)		/* Valid */

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
#define		ADC_TOCER_TOCESD				(BIT0)			/* DG-Diag has an overlap error */
	#define		ADC_TOCER_TOCESD_NOERROR		(0U)		/* Invalid */
	#define		ADC_TOCER_TOCESD_ERROR			(1U)		/* Valid */

#endif

/* OWER */
#define		ADC_OWER_OWE					(BIT7)			/* Overwrite error */
	#define		ADC_OWER_OWE_NOERROR			(0U)		/* No error */
	#define		ADC_OWER_OWE_ERROR				(1U)		/* ERROR YES */

#define		ADC_OWER_OWECAP					(BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)
#define		ADC_OWER_OWECAP_0				(BIT0)			/* Overwrite error capture */

/* PER */
#define		ADC_PER_PE						(BIT7)			/* Parity error */
	#define		ADC_PER_PE_NOERROR				(0U)		/* No error */
	#define		ADC_PER_PE_ERROR				(1U)		/* ERROR YES */
#define		ADC_PER_PECAP					(BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)
#define		ADC_PER_PECAP_0					(BIT0)			/* Parity Error Capture */

/* IDER */
#define		ADC_IDER_IDE					(BIT7)			/* ID error */
	#define		ADC_IDER_IDE_NOERROR			(0U)		/* No error */
	#define		ADC_IDER_IDE_ERROR				(1U)		/* ERROR YES */
#define		ADC_IDER_IDECAP					(BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)
#define		ADC_IDER_IDECAP_0				(BIT0)			/* ID error capture */

/* ECR */
#define		ADC_ECR_TOCESGC					(BIT13 + BIT12 + BIT11 + BIT10 + BIT9)
#define		ADC_ECR_TOCESGC_4				(BIT13)			/* Trigger overlap check error cleared on SG4 */
#define		ADC_ECR_TOCESGC_3				(BIT12)			/* Trigger overlap check error cleared on SG3 */
#define		ADC_ECR_TOCESGC_2				(BIT11)			/* Trigger overlap check error cleared in SG2 */
#define		ADC_ECR_TOCESGC_1				(BIT10)			/* Trigger overlap check error cleared in SG1 */
#define		ADC_ECR_TOCESGC_0				(BIT9)			/* Trigger overlap check error cleared on SG0 */
	#define		ADC_ECR_TOCESGC_NOTCLR			(0U)		/* Invalid */
	#define		ADC_ECR_TOCESGC_CLR				(1U)		/* Valid */

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
#define		ADC_ECR_TOCESDC					(BIT8)
	#define		ADC_ECR_TOCESDC_NOTCLR			(0U)		/* Invalid */
	#define		ADC_ECR_TOCESDC_CLR				(1U)		/* Valid */

#endif

#define		ADC_ECR_OWEC					(BIT2)			/* Overwrite Error Clear */
	#define		ADC_ECR_OWEC_NOTCLR				(0U)		/* NOT CLEAR */
	#define		ADC_ECR_OWEC_CLR				(1U)		/* Clear */
#define		ADC_ECR_PEC						(BIT1)			/* Parity Error Clear */
	#define		ADC_ECR_PEC_NOTCLR				(0U)		/* NOT CLEAR */
	#define		ADC_ECR_PEC_CLR					(1U)		/* Clear */
#define		ADC_ECR_IDEC					(BIT0)			/* ID error clear */
	#define		ADC_ECR_IDEC_NOTCLR				(0U)		/* NOT CLEAR */
	#define		ADC_ECR_IDEC_CLR				(1U)		/* Clear */

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
/* STPDCR */
#define		ADC_STPDCR_SPDE					(BIT0)
	#define		ADC_STPDCR_SPDE_DISABLE			(0U)		/* Invalid */
	#define		ADC_STPDCR_SPDE_ENABLE			(1U)		/* Valid */

#endif

/* VCULLMTBR */
#define		ADC_VCULLMTBR_VCULMTB			(0xFFFF0000U)
#define		ADC_VCULLMTBR_VCULMTB_0			(BIT16)			/* Cap table */
#define		ADC_VCULLMTBR_VCLLMTB			(0x0000FFFFU)
#define		ADC_VCULLMTBR_VCLLMTB_0			(BIT0)			/* Lower table */

/* VCLMINTER1 */
#define		ADC_VCLMINTER1_ADUL31IE			(BIT31)			/* Virtual channel upper/lower error interrupt enable */
#define		ADC_VCLMINTER1_ADUL30IE			(BIT30)
#define		ADC_VCLMINTER1_ADUL29IE			(BIT29)
#define		ADC_VCLMINTER1_ADUL28IE			(BIT28)
#define		ADC_VCLMINTER1_ADUL27IE			(BIT27)
#define		ADC_VCLMINTER1_ADUL26IE			(BIT26)
#define		ADC_VCLMINTER1_ADUL25IE			(BIT25)
#define		ADC_VCLMINTER1_ADUL24IE			(BIT24)
#define		ADC_VCLMINTER1_ADUL23IE			(BIT23)
#define		ADC_VCLMINTER1_ADUL22IE			(BIT22)
#define		ADC_VCLMINTER1_ADUL21IE			(BIT21)
#define		ADC_VCLMINTER1_ADUL20IE			(BIT20)
#define		ADC_VCLMINTER1_ADUL19IE			(BIT19)
#define		ADC_VCLMINTER1_ADUL18IE			(BIT18)
#define		ADC_VCLMINTER1_ADUL17IE			(BIT17)
#define		ADC_VCLMINTER1_ADUL16IE			(BIT16)
#define		ADC_VCLMINTER1_ADUL15IE			(BIT15)
#define		ADC_VCLMINTER1_ADUL14IE			(BIT14)
#define		ADC_VCLMINTER1_ADUL13IE			(BIT13)
#define		ADC_VCLMINTER1_ADUL12IE			(BIT12)
#define		ADC_VCLMINTER1_ADUL11IE			(BIT11)
#define		ADC_VCLMINTER1_ADUL10IE			(BIT10)
#define		ADC_VCLMINTER1_ADUL09IE			(BIT9)
#define		ADC_VCLMINTER1_ADUL08IE			(BIT8)
#define		ADC_VCLMINTER1_ADUL07IE			(BIT7)
#define		ADC_VCLMINTER1_ADUL06IE			(BIT6)
#define		ADC_VCLMINTER1_ADUL05IE			(BIT5)
#define		ADC_VCLMINTER1_ADUL04IE			(BIT4)
#define		ADC_VCLMINTER1_ADUL03IE			(BIT3)
#define		ADC_VCLMINTER1_ADUL02IE			(BIT2)
#define		ADC_VCLMINTER1_ADUL01IE			(BIT1)
#define		ADC_VCLMINTER1_ADUL00IE			(BIT0)
	#define		ADC_VCLMINTER1_ADULIE_NOTOUTPUT	(0U)		/* Upper/Lower error interrupt not output by virtual channel result */
	#define		ADC_VCLMINTER1_ADULIE_OUTPUT	(1U)		/* Upper/Lower error interrupt is output by virtual channel result */

/* VCLMINTER2 */
#define		ADC_VCLMINTER2_ADUL63IE			(BIT31)			/* Virtual channel upper/lower error interrupt enable */
#define		ADC_VCLMINTER2_ADUL62IE			(BIT30)
#define		ADC_VCLMINTER2_ADUL61IE			(BIT29)
#define		ADC_VCLMINTER2_ADUL60IE			(BIT28)
#define		ADC_VCLMINTER2_ADUL59IE			(BIT27)
#define		ADC_VCLMINTER2_ADUL58IE			(BIT26)
#define		ADC_VCLMINTER2_ADUL57IE			(BIT25)
#define		ADC_VCLMINTER2_ADUL56IE			(BIT24)
#define		ADC_VCLMINTER2_ADUL55IE			(BIT23)
#define		ADC_VCLMINTER2_ADUL54IE			(BIT22)
#define		ADC_VCLMINTER2_ADUL53IE			(BIT21)
#define		ADC_VCLMINTER2_ADUL52IE			(BIT20)
#define		ADC_VCLMINTER2_ADUL51IE			(BIT19)
#define		ADC_VCLMINTER2_ADUL50IE			(BIT18)
#define		ADC_VCLMINTER2_ADUL49IE			(BIT17)
#define		ADC_VCLMINTER2_ADUL48IE			(BIT16)
#define		ADC_VCLMINTER2_ADUL47IE			(BIT15)
#define		ADC_VCLMINTER2_ADUL46IE			(BIT14)
#define		ADC_VCLMINTER2_ADUL45IE			(BIT13)
#define		ADC_VCLMINTER2_ADUL44IE			(BIT12)
#define		ADC_VCLMINTER2_ADUL43IE			(BIT11)
#define		ADC_VCLMINTER2_ADUL42IE			(BIT10)
#define		ADC_VCLMINTER2_ADUL41IE			(BIT9)
#define		ADC_VCLMINTER2_ADUL40IE			(BIT8)
#define		ADC_VCLMINTER2_ADUL39IE			(BIT7)			
#define		ADC_VCLMINTER2_ADUL38IE			(BIT6)
#define		ADC_VCLMINTER2_ADUL37IE			(BIT5)
#define		ADC_VCLMINTER2_ADUL36IE			(BIT4)
#define		ADC_VCLMINTER2_ADUL35IE			(BIT3)
#define		ADC_VCLMINTER2_ADUL34IE			(BIT2)
#define		ADC_VCLMINTER2_ADUL33IE			(BIT1)
#define		ADC_VCLMINTER2_ADUL32IE			(BIT0)
	#define		ADC_VCLMINTER2_ADULIE_NOTOUTPUT	(0U)		/* Upper/Lower error interrupt not output by virtual channel result */
	#define		ADC_VCLMINTER2_ADULIE_OUTPUT	(1U)		/* Upper/Lower error interrupt is output by virtual channel result */

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
/* PWVCLMINTER */
#define		ADC_PWVCLMINTER_PWADULIE			(BIT0)
	#define		ADC_PWVCLMINTER_PWADULIE_NOTOUTPUT	(0U)	/* PWM-Diag limit check interrupt not output by virtual channel result */
	#define		ADC_PWVCLMINTER_PWADULIE_OUTPUT		(1U)	/* PWM-Diag limit check upper/lower error interrupt is output by virtual channel result */

#elif	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
/* SDVCLMINTER */
#define		ADC_SDVCLMINTER_SDADULIE			(BIT0)
	#define		ADC_SDVCLMINTER_SDADULIE_NOTOUTPUT	(0U)	/* SG-Diag limit check interrupt not output by virtual channel result */
	#define		ADC_SDVCLMINTER_SDADULIE_OUTPUT		(1U)	/* SG-Diag limit check upper/lower error interrupt is output by virtual channel result */

#endif

/* VCLMSR1 */
#define		ADC_VCLMSR1_VC31LMS				(BIT31)			/* Virtual channel upper/lower limit exceeded status */
#define		ADC_VCLMSR1_VC30LMS				(BIT30)
#define		ADC_VCLMSR1_VC29LMS				(BIT29)
#define		ADC_VCLMSR1_VC28LMS				(BIT28)
#define		ADC_VCLMSR1_VC27LMS				(BIT27)
#define		ADC_VCLMSR1_VC26LMS				(BIT26)
#define		ADC_VCLMSR1_VC25LMS				(BIT25)
#define		ADC_VCLMSR1_VC24LMS				(BIT24)
#define		ADC_VCLMSR1_VC23LMS				(BIT23)
#define		ADC_VCLMSR1_VC22LMS				(BIT22)
#define		ADC_VCLMSR1_VC21LMS				(BIT21)
#define		ADC_VCLMSR1_VC20LMS				(BIT20)
#define		ADC_VCLMSR1_VC19LMS				(BIT19)
#define		ADC_VCLMSR1_VC18LMS				(BIT18)
#define		ADC_VCLMSR1_VC17LMS				(BIT17)
#define		ADC_VCLMSR1_VC16LMS				(BIT16)
#define		ADC_VCLMSR1_VC15LMS				(BIT15)
#define		ADC_VCLMSR1_VC14LMS				(BIT14)
#define		ADC_VCLMSR1_VC13LMS				(BIT13)
#define		ADC_VCLMSR1_VC12LMS				(BIT12)
#define		ADC_VCLMSR1_VC11LMS				(BIT11)
#define		ADC_VCLMSR1_VC10LMS				(BIT10)
#define		ADC_VCLMSR1_VC09LMS				(BIT9)
#define		ADC_VCLMSR1_VC08LMS				(BIT8)
#define		ADC_VCLMSR1_VC07LMS				(BIT7)
#define		ADC_VCLMSR1_VC06LMS				(BIT6)
#define		ADC_VCLMSR1_VC05LMS				(BIT5)
#define		ADC_VCLMSR1_VC04LMS				(BIT4)
#define		ADC_VCLMSR1_VC03LMS				(BIT3)
#define		ADC_VCLMSR1_VC02LMS				(BIT2)
#define		ADC_VCLMSR1_VC01LMS				(BIT1)
#define		ADC_VCLMSR1_VC00LMS				(BIT0)
	#define		ADC_VCLMSR1_VCLMS_NOTOUTPUT		(0U)		/* Limit not reached */
	#define		ADC_VCLMSR1_VCLMS_OUTPUT		(1U)		/* Limit exceeded */

/* VCLMSR2 */
#define		ADC_VCLMSR2_VC63LMS				(BIT31)			/* Virtual channel upper/lower limit exceeded status */
#define		ADC_VCLMSR2_VC62LMS				(BIT30)
#define		ADC_VCLMSR2_VC61LMS				(BIT29)
#define		ADC_VCLMSR2_VC60LMS				(BIT28)
#define		ADC_VCLMSR2_VC59LMS				(BIT27)
#define		ADC_VCLMSR2_VC58LMS				(BIT26)
#define		ADC_VCLMSR2_VC57LMS				(BIT25)
#define		ADC_VCLMSR2_VC56LMS				(BIT24)
#define		ADC_VCLMSR2_VC55LMS				(BIT23)
#define		ADC_VCLMSR2_VC54LMS				(BIT22)
#define		ADC_VCLMSR2_VC53LMS				(BIT21)
#define		ADC_VCLMSR2_VC52LMS				(BIT20)
#define		ADC_VCLMSR2_VC51LMS				(BIT19)
#define		ADC_VCLMSR2_VC50LMS				(BIT18)
#define		ADC_VCLMSR2_VC49LMS				(BIT17)
#define		ADC_VCLMSR2_VC48LMS				(BIT16)
#define		ADC_VCLMSR2_VC47LMS				(BIT15)
#define		ADC_VCLMSR2_VC46LMS				(BIT14)
#define		ADC_VCLMSR2_VC45LMS				(BIT13)
#define		ADC_VCLMSR2_VC44LMS				(BIT12)
#define		ADC_VCLMSR2_VC43LMS				(BIT11)
#define		ADC_VCLMSR2_VC42LMS				(BIT10)
#define		ADC_VCLMSR2_VC41LMS				(BIT9)
#define		ADC_VCLMSR2_VC40LMS				(BIT8)
#define		ADC_VCLMSR2_VC39LMS				(BIT7)			
#define		ADC_VCLMSR2_VC38LMS				(BIT6)
#define		ADC_VCLMSR2_VC37LMS				(BIT5)
#define		ADC_VCLMSR2_VC36LMS				(BIT4)
#define		ADC_VCLMSR2_VC35LMS				(BIT3)
#define		ADC_VCLMSR2_VC34LMS				(BIT2)
#define		ADC_VCLMSR2_VC33LMS				(BIT1)
#define		ADC_VCLMSR2_VC32LMS				(BIT0)
	#define		ADC_VCLMSR2_VCLMS_NOTOUTPUT		(0U)		/* Limit not reached */
	#define		ADC_VCLMSR2_VCLMS_OUTPUT		(1U)		/* Limit exceeded */

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
/* PWVCLMINTERR */
#define		ADC_PWVCLMINTER_PWVCLMS			(BIT0)
	#define		ADC_PWVCLMINTER_PWVCLMS_NOTREPORT	(0U)		/* PWM-Diag upper/lower limit check status not output */
	#define		ADC_PWVCLMINTER_PWVCLMS_REPORT		(1U)		/* PWM-Diag upper/lower limit check status is output */

#elif	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
/* SDVCLMSR */
#define		ADC_SDVCLMSR_SR1LMS				(BIT2)
	#define		ADC_SDVCLMSR_SR1LMS_NOTREPORT		(0U)
	#define		ADC_SDVCLMSR_SR1LMS_REPORT			(1U)
#define		ADC_SDVCLMSR_SR0LMS				(BIT1)
	#define		ADC_SDVCLMSR_SR0LMS_NOTREPORT		(0U)
	#define		ADC_SDVCLMSR_SR0LMS_REPORT			(1U)
#define		ADC_SDVCLMSR_SDVC0LMS			(BIT0)
	#define		ADC_SDVCLMSR_SDVC0LMS_NOTREPORT		(0U)
	#define		ADC_SDVCLMSR_SDVC0LMS_REPORT		(1U)

#endif

/* SGULCR */
#define		ADC_SGULCR_UE					(BIT15)
	#define		ADC_SGULCR_UE_NOTREPORT			(0U)		/* No upper limit check status is output */
	#define		ADC_SGULCR_UE_REPORT			(1U)		/* Upper limit check status is output */
#define		ADC_SGULCR_LE					(BIT14)
	#define		ADC_SGULCR_LE_NOTREPORT			(0U)		/* LOWER LIMIT CHECK STATUS NOT OUTPUT */
	#define		ADC_SGULCR_LE_REPORT			(1U)		/* LOWER LIMIT CHECK STATUS IS OUTPUT */
#define		ADC_SGULCR_MPXE					(BIT11)
	#define		ADC_SGULCR_MPXE_NOTUSE			(0U)		/* Do not use MPX function during upper/lower limit status notification */
	#define		ADC_SGULCR_MPXE_USE				(1U)		/* Use MPX function on upper/lower limit status notification */
#define		ADC_SGULCR_MPXEMPXV				(BIT10 + BIT9 + BIT8)
#define		ADC_SGULCR_MPXEMPXV_0			(BIT8)
#define		ADC_SGULCR_ULE					(BIT7)
	#define		ADC_SGULCR_ULE_NOTREPORT		(0U)		/* Upper/Lower limit check status not output */
	#define		ADC_SGULCR_ULE_REPORT			(1U)		/* Upper/Lower limit check status is output */
#define		ADC_SGULCR_ULPC					(BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)
#define		ADC_SGULCR_ULPC_0				(BIT0)

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
/* SGDIAGULCR */
#define		ADC_SGDIAGULCR_UE				(BIT15)
	#define		ADC_SGDIAGULCR_UE_NOTREPORT		(0U)		/* No upper limit check status is output */
	#define		ADC_SGDIAGULCR_UE_REPORT		(1U)		/* Upper limit check status is output */
#define		ADC_SGDIAGULCR_LE				(BIT14)
	#define		ADC_SGDIAGULCR_LE_NOTREPORT		(0U)		/* LOWER LIMIT CHECK STATUS NOT OUTPUT */
	#define		ADC_SGDIAGULCR_LE_REPORT		(1U)		/* LOWER LIMIT CHECK STATUS IS OUTPUT */
#define		ADC_SGDIAGULCR_ULE				(BIT7)
	#define		ADC_SGDIAGULCR_ULE_NOTREPORT	(0U)		/* Upper/Lower limit check status not output */
	#define		ADC_SGDIAGULCR_ULE_REPORT		(1U)		/* Upper/Lower limit check status is output */
#define		ADC_SGDIAGULCR_ULPC				(BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)
#define		ADC_SGDIAGULCR_ULPC_0			(BIT0)

#endif

/* VCLMSCR1 */
#define		ADC_VCLMSCR1_VC31LMSC			(BIT31)			/* Virtual channel upper/lower limit exceeded status cleared */
#define		ADC_VCLMSCR1_VC30LMSC			(BIT30)
#define		ADC_VCLMSCR1_VC29LMSC			(BIT29)
#define		ADC_VCLMSCR1_VC28LMSC			(BIT28)
#define		ADC_VCLMSCR1_VC27LMSC			(BIT27)
#define		ADC_VCLMSCR1_VC26LMSC			(BIT26)
#define		ADC_VCLMSCR1_VC25LMSC			(BIT25)
#define		ADC_VCLMSCR1_VC24LMSC			(BIT24)
#define		ADC_VCLMSCR1_VC23LMSC			(BIT23)
#define		ADC_VCLMSCR1_VC22LMSC			(BIT22)
#define		ADC_VCLMSCR1_VC21LMSC			(BIT21)
#define		ADC_VCLMSCR1_VC20LMSC			(BIT20)
#define		ADC_VCLMSCR1_VC19LMSC			(BIT19)
#define		ADC_VCLMSCR1_VC18LMSC			(BIT18)
#define		ADC_VCLMSCR1_VC17LMSC			(BIT17)
#define		ADC_VCLMSCR1_VC16LMSC			(BIT16)
#define		ADC_VCLMSCR1_VC15LMSC			(BIT15)
#define		ADC_VCLMSCR1_VC14LMSC			(BIT14)
#define		ADC_VCLMSCR1_VC13LMSC			(BIT13)
#define		ADC_VCLMSCR1_VC12LMSC			(BIT12)
#define		ADC_VCLMSCR1_VC11LMSC			(BIT11)
#define		ADC_VCLMSCR1_VC10LMSC			(BIT10)
#define		ADC_VCLMSCR1_VC09LMSC			(BIT9)
#define		ADC_VCLMSCR1_VC08LMSC			(BIT8)
#define		ADC_VCLMSCR1_VC07LMSC			(BIT7)
#define		ADC_VCLMSCR1_VC06LMSC			(BIT6)
#define		ADC_VCLMSCR1_VC05LMSC			(BIT5)
#define		ADC_VCLMSCR1_VC04LMSC			(BIT4)
#define		ADC_VCLMSCR1_VC03LMSC			(BIT3)
#define		ADC_VCLMSCR1_VC02LMSC			(BIT2)
#define		ADC_VCLMSCR1_VC01LMSC			(BIT1)
#define		ADC_VCLMSCR1_VC00LMSC			(BIT0)
	#define		ADC_VCLMSCR1_VCLMSC_NOTCLR		(0U)		/* No clear */
	#define		ADC_VCLMSCR1_VCLMSC_CLR			(1U)		/* Clear VCjLMS in VCLMSR1 */

/* VCLMSCR2 */
#define		ADC_VCLMSCR2_VC63LMSC			(BIT31)			/* Virtual channel upper/lower limit exceeded status cleared */
#define		ADC_VCLMSCR2_VC62LMSC			(BIT30)
#define		ADC_VCLMSCR2_VC61LMSC			(BIT29)
#define		ADC_VCLMSCR2_VC60LMSC			(BIT28)
#define		ADC_VCLMSCR2_VC59LMSC			(BIT27)
#define		ADC_VCLMSCR2_VC58LMSC			(BIT26)
#define		ADC_VCLMSCR2_VC57LMSC			(BIT25)
#define		ADC_VCLMSCR2_VC56LMSC			(BIT24)
#define		ADC_VCLMSCR2_VC55LMSC			(BIT23)
#define		ADC_VCLMSCR2_VC54LMSC			(BIT22)
#define		ADC_VCLMSCR2_VC53LMSC			(BIT21)
#define		ADC_VCLMSCR2_VC52LMSC			(BIT20)
#define		ADC_VCLMSCR2_VC51LMSC			(BIT19)
#define		ADC_VCLMSCR2_VC50LMSC			(BIT18)
#define		ADC_VCLMSCR2_VC49LMSC			(BIT17)
#define		ADC_VCLMSCR2_VC48LMSC			(BIT16)
#define		ADC_VCLMSCR2_VC47LMSC			(BIT15)
#define		ADC_VCLMSCR2_VC46LMSC			(BIT14)
#define		ADC_VCLMSCR2_VC45LMSC			(BIT13)
#define		ADC_VCLMSCR2_VC44LMSC			(BIT12)
#define		ADC_VCLMSCR2_VC43LMSC			(BIT11)
#define		ADC_VCLMSCR2_VC42LMSC			(BIT10)
#define		ADC_VCLMSCR2_VC41LMSC			(BIT9)
#define		ADC_VCLMSCR2_VC40LMSC			(BIT8)
#define		ADC_VCLMSCR2_VC39LMSC			(BIT7)			
#define		ADC_VCLMSCR2_VC38LMSC			(BIT6)
#define		ADC_VCLMSCR2_VC37LMSC			(BIT5)
#define		ADC_VCLMSCR2_VC36LMSC			(BIT4)
#define		ADC_VCLMSCR2_VC35LMSC			(BIT3)
#define		ADC_VCLMSCR2_VC34LMSC			(BIT2)
#define		ADC_VCLMSCR2_VC33LMSC			(BIT1)
#define		ADC_VCLMSCR2_VC32LMSC			(BIT0)
	#define		ADC_VCLMSCR2_VCLMSC_NOTCLR		(0U)		/* No clear */
	#define		ADC_VCLMSCR2_VCLMSC_CLR			(1U)		/* Clear VCjLMS in VCLMSR2 */

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
/* PWVCLMSCR */
#define		ADC_PWVCLMSCR_PWVCLMSC			(BIT0)
	#define		ADC_PWVCLMSCR_PWVCLMSC_NOTCLR	(0U)		/* No clear */
	#define		ADC_PWVCLMSCR_PWVCLMSC_CLR		(1U)		/* Clear PWVCLMS in PWVCLMSR */

#elif	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
/* SDVCLMSCR */
#define		ADC_SDVCLMSCR_SR1LMSC			(BIT2)
	#define		ADC_SDVCLMSCR_SR1LMSC_NOTCLR	(0U)		/* No clear */
	#define		ADC_SDVCLMSCR_SR1LMSC_CLR		(1U)		/* Clear SR1LMSC in SDVCLMSCR */
#define		ADC_SDVCLMSCR_SR0LMSC			(BIT1)
	#define		ADC_SDVCLMSCR_SR0LMSC_NOTCLR	(0U)		/* No clear */
	#define		ADC_SDVCLMSCR_SR0LMSC_CLR		(1U)		/* Clear SR0LMSC in SDVCLMSCR */
#define		ADC_SDVCLMSCR_SDVC0LMSC			(BIT0)
	#define		ADC_SDVCLMSCR_SDVC0LMSC_NOTCLR	(0U)		/* No clear */
	#define		ADC_SDVCLMSCR_SDVC0LMSC_CLR		(1U)		/* Clear SDVC0LMSC in SDVCLMSCR */

#endif

/* SGULCCR */
#define		ADC_SGULCCR_SGULCC				(BIT5 + BIT4 + BIT3 + BIT2 + BIT1)
#define		ADC_SGULCCR_SGULCC_4			(BIT5)
#define		ADC_SGULCCR_SGULCC_3			(BIT4)
#define		ADC_SGULCCR_SGULCC_2			(BIT3)
#define		ADC_SGULCCR_SGULCC_1			(BIT2)
#define		ADC_SGULCCR_SGULCC_0			(BIT1)
	#define		ADC_SGULCCR_SGULCC_NOTCLR		(0U)		/* No clear */
	#define		ADC_SGULCCR_SGULCC_CLR			(1U)		/* Clear SGULCRx */

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
#define		ADC_SGULCCR_SDULCC				(BIT0)
	#define		ADC_SGULCCR_SDULCC_NOTCLR		(0U)		/* No clear */
	#define		ADC_SGULCCR_SDULCC_CLR			(1U)		/* Clear SDULCC */

#endif

/* VCLMASCR */
#define		ADC_VCLMASCR_ALLMSC				(BIT0)
	#define		ADC_VCLMASCR_ALLMSC_NOTCLR		(0U)		/* No clear */
	#define		ADC_VCLMASCR_ALLMSC_CLR			(1U)		/* Clear the status register limit check */

/***************************/
/*           AIR           */
/***************************/
/* AIRISELR0 */
#define		AIR_AIRISELR0_ISEL				(BIT0)

/* AIRISELR1 */
#define		AIR_AIRISELR1_ISEL				(BIT0)

/* AIRDSELR0*/
#define		AIR_AIRDSELR0_DSEL				(BIT0)

/* AIRDSELR1 */
#define		AIR_AIRDSELR1_DSEL				(BIT0)

/* setting value	*/
#define		ADC_AIR_ITRSELECT_OFF			(0U)			/* interrupt request select		*/
#define		ADC_AIR_ITRSELECT_ON			(1U)			/* interrupt request Not select	*/
/* bit position (common)	*/
#define		AIR_AIRSEL_INTADCK0I0			(BIT4)
#define		AIR_AIRSEL_INTADCK0I1			(BIT5)
#define		AIR_AIRSEL_INTADCK0I2			(BIT6)
#define		AIR_AIRSEL_INTADCK0I3			(BIT7)
#define		AIR_AIRSEL_INTADCK0I4			(BIT8)
#define		AIR_AIRSEL_INTADCK2I0			(BIT9)
#define		AIR_AIRSEL_INTADCK2I1			(BIT10)
#define		AIR_AIRSEL_INTADCK2I2			(BIT11)
#define		AIR_AIRSEL_INTADCK2I3			(BIT12)
#define		AIR_AIRSEL_INTADCK2I4			(BIT13)
#define		AIR_AIRSEL_INTADCK1I0			(BIT14)
#define		AIR_AIRSEL_INTADCK1I1			(BIT15)
#define		AIR_AIRSEL_INTADCK1I2			(BIT16)
#define		AIR_AIRSEL_INTADCK1I3			(BIT17)
#define		AIR_AIRSEL_INTADCK1I4			(BIT18)
#define		AIR_AIRSEL_INTADCK3I0			(BIT19)
#define		AIR_AIRSEL_INTADCK3I1			(BIT20)
#define		AIR_AIRSEL_INTADCK3I2			(BIT21)
#define		AIR_AIRSEL_INTADCK3I3			(BIT22)
#define		AIR_AIRSEL_INTADCK3I4			(BIT23)

#define		ADC_AIRSEL_UNIT0_DEFBIT			(AIR_AIRSEL_INTADCK0I0|AIR_AIRSEL_INTADCK0I1|AIR_AIRSEL_INTADCK0I2|AIR_AIRSEL_INTADCK0I3|AIR_AIRSEL_INTADCK0I4)
#define		ADC_AIRSEL_UNIT1_DEFBIT			(AIR_AIRSEL_INTADCK1I0|AIR_AIRSEL_INTADCK1I1|AIR_AIRSEL_INTADCK1I2|AIR_AIRSEL_INTADCK1I3|AIR_AIRSEL_INTADCK1I4)
#define		ADC_AIRSEL_UNIT2_DEFBIT			(AIR_AIRSEL_INTADCK2I0|AIR_AIRSEL_INTADCK2I1|AIR_AIRSEL_INTADCK2I2|AIR_AIRSEL_INTADCK2I3|AIR_AIRSEL_INTADCK2I4)
#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B) 
	#if ((MCAL_PKG_TARGET==MCAL_PKG_U2B10_292PIN) || (MCAL_PKG_TARGET==MCAL_PKG_U2B6_292PIN))
	#define	ADC_AIRSEL_UNIT3_DEFBIT			(0U)
	#else
	#define	ADC_AIRSEL_UNIT3_DEFBIT			(AIR_AIRSEL_INTADCK3I0|AIR_AIRSEL_INTADCK3I1|AIR_AIRSEL_INTADCK3I2|AIR_AIRSEL_INTADCK3I3|AIR_AIRSEL_INTADCK3I4)
	#endif
#else
	#define	ADC_AIRSEL_UNIT3_DEFBIT			(0U)
#endif
#define		ADC_AIRISELR0_DEFBIT	(ADC_AIRSEL_UNIT0_DEFBIT|ADC_AIRSEL_UNIT1_DEFBIT|ADC_AIRSEL_UNIT2_DEFBIT|ADC_AIRSEL_UNIT3_DEFBIT)
#define		ADC_AIRDSELR0_DEFBIT	(ADC_AIRISELR0_DEFBIT)


/*==============================================================================================*/
/*	struct address definition																	*/
/*==============================================================================================*/
#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) 
#define		Reg_ADC0		(*(volatile Reg_Adc_Type*)		(0xFFCA0000U))
#define		Reg_ADC1		(*(volatile Reg_Adc_Type*)		(0xFFF20000U))
#define		Reg_ADC2		(*(volatile Reg_Adc_Type*)		(0xFF9A2000U))
#define		Reg_SELB		(*(volatile Reg_Adc_SELB_Type*)	(0xFF9A3800U))
#endif
#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
#define		Reg_ADC0		(*(volatile Reg_Adc_Type*)		(0xFFCA0000U))
#define		Reg_ADC1		(*(volatile Reg_Adc_Type*)		(0xFFF20000U))
#define		Reg_ADC2		(*(volatile Reg_Adc_Type*)		(0xFFCA1000U))
#define		Reg_ADC3		(*(volatile Reg_Adc_Type*)		(0xFFF21000U))
#define		Reg_ADCA		(*(volatile Reg_Adc_Type*)		(0xFF9A2000U))
#define		Reg_SELB		(*(volatile Reg_Adc_SELB_Type*)	(0xFF9A3000U))
#define		Reg_AIR			(*(volatile Reg_Air_Type*)		(0xFFCB2500U))
#endif
extern volatile Reg_Adc_Type* const cpstReg_Adc[ADC_HWUNIT_NUM];
extern volatile Reg_Adc_SELB_Type* const cpstReg_SELB_Adc[ADC_SELB_MODULE_NUM];

/****************************/
/*	INTC					*/
/****************************/
/* INTC2	*/
#define	ADC_INTC_EIC32						(32U)							/* EIC32		*/


/* INTC access by ADC Moudle	*/
#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2A)
	#define ADC_INTC_EIC225_INTADCJ0SEC			(225U)	/* ADCJ0 Secondary voltage monitor error interrupt	*/
	#define ADC_INTC_EIC226_INTADCJ0ERR			(226U)	/* ADCJ0 A/D error interrupt upper/ lower limit error interrupt	*/
	#define ADC_INTC_EIC227_INTADCJ0I0			(227U)	/* ADCJ0 Scan group 0 (SG0) end interrupt	*/
	#define ADC_INTC_EIC228_INTADCJ0I1			(228U)	/* ADCJ0 Scan group 1 (SG1) end interrupt	*/
	#define ADC_INTC_EIC229_INTADCJ0I2			(229U)	/* ADCJ0 Scan group 2 (SG2) end interrupt	*/
	#define ADC_INTC_EIC230_INTADCJ0I3			(230U)	/* ADCJ0 Scan group 3 (SG3) end interrupt	*/
	#define ADC_INTC_EIC231_INTADCJ0I4			(231U)	/* ADCJ0 Scan group 4 (SG4) end interrupt	*/
	#define ADC_INTC_EIC232_INTADCJ1ERR			(232U)	/* ADCJ1 A/D error interrupt upper/ lower limit error interrupt	*/
	#define ADC_INTC_EIC233_INTADCJ1I0			(233U)	/* ADCJ1 Scan group 0 (SG0) end interrupt	*/
	#define ADC_INTC_EIC234_INTADCJ1I1			(234U)	/* ADCJ1 Scan group 1 (SG1) end interrupt	*/
	#define ADC_INTC_EIC235_INTADCJ1I2			(235U)	/* ADCJ1 Scan group 2 (SG2) end interrupt	*/
	#define ADC_INTC_EIC236_INTADCJ1I3			(236U)	/* ADCJ1 Scan group 3 (SG3) end interrupt	*/
	#define ADC_INTC_EIC237_INTADCJ1I4			(237U)	/* ADCJ1 Scan group 4 (SG4) end interrupt	*/
	#define ADC_INTC_EIC238_INTADCJ2ERR			(238U)	/* ADCJ2 A/D error interrupt upper/ lower limit error interrupt	*/
	#define ADC_INTC_EIC239_INTADCJ2I0			(239U)	/* ADCJ2 Scan group 0 (SG0) end interrupt	*/
	#define ADC_INTC_EIC240_INTADCJ2I1			(240U)	/* ADCJ2 Scan group 1 (SG1) end interrupt	*/
	#define ADC_INTC_EIC241_INTADCJ2I2			(241U)	/* ADCJ2 Scan group 2 (SG2) end interrupt	*/
	#define ADC_INTC_EIC242_INTADCJ2I3			(242U)	/* ADCJ2 Scan group 3 (SG3) end interrupt	*/
	#define ADC_INTC_EIC243_INTADCJ2I4			(243U)	/* ADCJ2 Scan group 4 (SG4) end interrupt	*/

	#define	ADC_INTC2_EIC_END					(ADC_INTC_EIC243_INTADCJ2I4)

#elif (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
	/* AIR	*/
	#define ADC_INTC_EIC437_ADMPXI0				(437U)	/* INTAIRINTREQ0	*/
	#define ADC_INTC_EIC438_ADMPXI2				(438U)	/* INTAIRINTREQ1	*/
	#define ADC_INTC_EIC439_ADMPXI1				(439U)	/* INTAIRINTREQ2	*/
	#define ADC_INTC_EIC440_ADMPXI3				(440U)	/* INTAIRINTREQ3	*/
	#define ADC_INTC_EIC441_INTADCK0I0			(441U)	/* INTAIRINTREQ4	*/
	#define ADC_INTC_EIC442_INTADCK0I1			(442U)	/* INTAIRINTREQ5	*/
	#define ADC_INTC_EIC443_INTADCK0I2			(443U)	/* INTAIRINTREQ6	*/
	#define ADC_INTC_EIC444_INTADCK0I3			(444U)	/* INTAIRINTREQ7	*/
	#define ADC_INTC_EIC445_INTADCK0I4			(445U)	/* INTAIRINTREQ8	*/
	#define ADC_INTC_EIC446_INTADCK2I0			(446U)	/* INTAIRINTREQ9	*/
	#define ADC_INTC_EIC447_INTADCK2I1			(447U)	/* INTAIRINTREQ10	*/
	#define ADC_INTC_EIC448_INTADCK2I2			(448U)	/* INTAIRINTREQ11	*/
	#define ADC_INTC_EIC449_INTADCK2I3			(449U)	/* INTAIRINTREQ12	*/
	#define ADC_INTC_EIC440_INTADCK2I4			(440U)	/* INTAIRINTREQ13	*/
	#define ADC_INTC_EIC451_INTADCK1I0			(451U)	/* INTAIRINTREQ14	*/
	#define ADC_INTC_EIC452_INTADCK1I1			(452U)	/* INTAIRINTREQ15	*/
	#define ADC_INTC_EIC453_INTADCK1I2			(453U)	/* INTAIRINTREQ16	*/
	#define ADC_INTC_EIC454_INTADCK1I3			(454U)	/* INTAIRINTREQ17	*/
	#define ADC_INTC_EIC455_INTADCK1I4			(455U)	/* INTAIRINTREQ18	*/
	#define ADC_INTC_EIC456_INTADCK3I0			(456U)	/* INTAIRINTREQ19	*/
	#define ADC_INTC_EIC457_INTADCK3I1			(457U)	/* INTAIRINTREQ20	*/
	#define ADC_INTC_EIC458_INTADCK3I2			(458U)	/* INTAIRINTREQ21	*/
	#define ADC_INTC_EIC459_INTADCK3I3			(459U)	/* INTAIRINTREQ22	*/
	#define ADC_INTC_EIC460_INTADCK3I4			(460U)	/* INTAIRINTREQ23	*/
	#define ADC_INTC_EIC461_INTADCK0ERR			(461U)	/* INTAIRINTREQ24	*/
	#define ADC_INTC_EIC462_INTADCK2ERR			(462U)	/* INTAIRINTREQ25	*/
	#define ADC_INTC_EIC463_INTADCK1ERR			(463U)	/* INTAIRINTREQ26	*/
	#define ADC_INTC_EIC464_INTADCK3ERR			(464U)	/* INTAIRINTREQ27	*/
	#define ADC_INTC_EIC465_DSADE00				(465U)	/* INTAIRINTREQ28	*/
	#define ADC_INTC_EIC466_DSADE10				(466U)	/* INTAIRINTREQ29	*/
	#define ADC_INTC_EIC467_DSADE20				(467U)	/* INTAIRINTREQ30	*/
	#define ADC_INTC_EIC468_DSADE12				(468U)	/* INTAIRINTREQ31	*/
	#define ADC_INTC_EIC469_DSADE13				(469U)	/* INTAIRINTREQ32	*/
	#define ADC_INTC_EIC470_DSADE11				(470U)	/* INTAIRINTREQ33	*/
	#define ADC_INTC_EIC471_DSADE15				(471U)	/* INTAIRINTREQ34	*/
	#define ADC_INTC_EIC472_DSADE14				(472U)	/* INTAIRINTREQ35	*/
	#define ADC_INTC_EIC473_DSADE22				(473U)	/* INTAIRINTREQ36	*/
	#define ADC_INTC_EIC474_DSADE21				(474U)	/* INTAIRINTREQ37	*/
	#define ADC_INTC_EIC475_CADE00				(475U)	/* INTAIRINTREQ38	*/
	#define ADC_INTC_EIC476_ASI0				(476U)	/* INTAIRINTREQ39	*/
	#define ADC_INTC_EIC477_ASI1				(477U)	/* INTAIRINTREQ40	*/
	#define ADC_INTC_EIC478_ASI2				(478U)	/* INTAIRINTREQ41	*/
	#define ADC_INTC_EIC479_ASI3				(479U)	/* INTAIRINTREQ42	*/
	#define ADC_INTC_EIC480_ASI4				(480U)	/* INTAIRINTREQ43	*/
	#define ADC_INTC_EIC481_ASI5				(481U)	/* INTAIRINTREQ44	*/
	#define ADC_INTC_EIC482_ASI6				(482U)	/* INTAIRINTREQ45	*/
	#define ADC_INTC_EIC483_ASI7				(483U)	/* INTAIRINTREQ46	*/
	#define ADC_INTC_EIC484_ASI8				(484U)	/* INTAIRINTREQ47	*/
	#define ADC_INTC_EIC485_ASI9				(485U)	/* INTAIRINTREQ48	*/
	#define ADC_INTC_EIC486_ASI10				(486U)	/* INTAIRINTREQ49	*/
	#define ADC_INTC_EIC487_ASI11				(487U)	/* INTAIRINTREQ50	*/
	#define ADC_INTC_EIC488_ASI12				(488U)	/* INTAIRINTREQ51	*/
	#define ADC_INTC_EIC489_ASI13				(489U)	/* INTAIRINTREQ52	*/
	#define ADC_INTC_EIC490_ASI14				(490U)	/* INTAIRINTREQ53	*/
	#define ADC_INTC_EIC491_ASI15				(491U)	/* INTAIRINTREQ54	*/
	#define ADC_INTC_EIC492_INTADCK_SD0			(492U)	/* INTAIRINTREQ55	*/
	#define ADC_INTC_EIC493_INTADCK_SD1			(493U)	/* INTAIRINTREQ56	*/
	#define ADC_INTC_EIC494_INTADCK_SD2			(494U)	/* INTAIRINTREQ57	*/
	#define ADC_INTC_EIC495_INTADCK_SD3			(495U)	/* INTAIRINTREQ58	*/
	#define ADC_INTC_EIC496_DSMIF0UPDATE0		(496U)	/* INTAIRINTREQ59	*/
	/* ADCKA	*/
	#define ADC_INTC_EIC982_INTADCKAERR			(982U)	/* ADCKA A/D error interrupt upper/ lower limit error interrupt	*/
	#define ADC_INTC_EIC983_INTADCKAI0			(983U)	/* ADCKA Scan group 0 (SG0) end interrupt	*/
	#define ADC_INTC_EIC984_INTADCKAI1			(984U)	/* ADCKA Scan group 1 (SG1) end interrupt	*/
	#define ADC_INTC_EIC985_INTADCKAI2			(985U)	/* ADCKA Scan group 2 (SG2) end interrupt	*/
	#define ADC_INTC_EIC986_INTADCKAI3			(986U)	/* ADCKA Scan group 3 (SG3) end interrupt	*/
	#define ADC_INTC_EIC987_INTADCKAI4			(987U)	/* ADCKA Scan group 4 (SG4) end interrupt 	*/
	
	#define	ADC_INTC2_EIC_END					(ADC_INTC_EIC987_INTADCKAI4)
#endif
	#define	ADC_INTC2_EIC_SIZE					(ADC_INTC2_EIC_END + 1U)

/* INTC access by ADC Moudle	*/
#if (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2A)
	#define ADC_INTC_ADCx0I0			(ADC_INTC_EIC227_INTADCJ0I0)	/* ADCx0 Scan group 0 (SG0) end interrupt	*/
	#define ADC_INTC_ADCx0I1			(ADC_INTC_EIC228_INTADCJ0I1)	/* ADCx0 Scan group 1 (SG1) end interrupt	*/
	#define ADC_INTC_ADCx0I2			(ADC_INTC_EIC229_INTADCJ0I2)	/* ADCx0 Scan group 2 (SG2) end interrupt	*/
	#define ADC_INTC_ADCx0I3			(ADC_INTC_EIC230_INTADCJ0I3)	/* ADCx0 Scan group 3 (SG3) end interrupt	*/
	#define ADC_INTC_ADCx0I4			(ADC_INTC_EIC231_INTADCJ0I4)	/* ADCx0 Scan group 4 (SG4) end interrupt	*/
	#define ADC_INTC_ADCx1I0			(ADC_INTC_EIC233_INTADCJ1I0)	/* ADCx1 Scan group 0 (SG0) end interrupt	*/
	#define ADC_INTC_ADCx1I1			(ADC_INTC_EIC234_INTADCJ1I1)	/* ADCx1 Scan group 1 (SG1) end interrupt	*/
	#define ADC_INTC_ADCx1I2			(ADC_INTC_EIC235_INTADCJ1I2)	/* ADCx1 Scan group 2 (SG2) end interrupt	*/
	#define ADC_INTC_ADCx1I3			(ADC_INTC_EIC236_INTADCJ1I3)	/* ADCx1 Scan group 3 (SG3) end interrupt	*/
	#define ADC_INTC_ADCx1I4			(ADC_INTC_EIC237_INTADCJ1I4)	/* ADCx1 Scan group 4 (SG4) end interrupt	*/
	#define ADC_INTC_ADCx2I0			(ADC_INTC_EIC239_INTADCJ2I0)	/* ADCx2 Scan group 0 (SG0) end interrupt	*/
	#define ADC_INTC_ADCx2I1			(ADC_INTC_EIC240_INTADCJ2I1)	/* ADCx2 Scan group 1 (SG1) end interrupt	*/
	#define ADC_INTC_ADCx2I2			(ADC_INTC_EIC241_INTADCJ2I2)	/* ADCx2 Scan group 2 (SG2) end interrupt	*/
	#define ADC_INTC_ADCx2I3			(ADC_INTC_EIC242_INTADCJ2I3)	/* ADCx2 Scan group 3 (SG3) end interrupt	*/
	#define ADC_INTC_ADCx2I4			(ADC_INTC_EIC243_INTADCJ2I4)	/* ADCx2 Scan group 4 (SG4) end interrupt	*/
#elif (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
	#define ADC_INTC_ADCx0I0			(ADC_INTC_EIC441_INTADCK0I0)	/* ADCx0 Scan group 0 (SG0) end interrupt	*/
	#define ADC_INTC_ADCx0I1			(ADC_INTC_EIC442_INTADCK0I1)	/* ADCx0 Scan group 1 (SG1) end interrupt	*/
	#define ADC_INTC_ADCx0I2			(ADC_INTC_EIC443_INTADCK0I2)	/* ADCx0 Scan group 2 (SG2) end interrupt	*/
	#define ADC_INTC_ADCx0I3			(ADC_INTC_EIC444_INTADCK0I3)	/* ADCx0 Scan group 3 (SG3) end interrupt	*/
	#define ADC_INTC_ADCx0I4			(ADC_INTC_EIC445_INTADCK0I4)	/* ADCx0 Scan group 4 (SG4) end interrupt	*/
	#define ADC_INTC_ADCx1I0			(ADC_INTC_EIC451_INTADCK1I0)	/* ADCx1 Scan group 0 (SG0) end interrupt	*/
	#define ADC_INTC_ADCx1I1			(ADC_INTC_EIC452_INTADCK1I1)	/* ADCx1 Scan group 1 (SG1) end interrupt	*/
	#define ADC_INTC_ADCx1I2			(ADC_INTC_EIC453_INTADCK1I2)	/* ADCx1 Scan group 2 (SG2) end interrupt	*/
	#define ADC_INTC_ADCx1I3			(ADC_INTC_EIC454_INTADCK1I3)	/* ADCx1 Scan group 3 (SG3) end interrupt	*/
	#define ADC_INTC_ADCx1I4			(ADC_INTC_EIC455_INTADCK1I4)	/* ADCx1 Scan group 4 (SG4) end interrupt	*/
	#define ADC_INTC_ADCx2I0			(ADC_INTC_EIC446_INTADCK2I0)	/* ADCx2 Scan group 0 (SG0) end interrupt	*/
	#define ADC_INTC_ADCx2I1			(ADC_INTC_EIC447_INTADCK2I1)	/* ADCx2 Scan group 1 (SG1) end interrupt	*/
	#define ADC_INTC_ADCx2I2			(ADC_INTC_EIC448_INTADCK2I2)	/* ADCx2 Scan group 2 (SG2) end interrupt	*/
	#define ADC_INTC_ADCx2I3			(ADC_INTC_EIC449_INTADCK2I3)	/* ADCx2 Scan group 3 (SG3) end interrupt	*/
	#define ADC_INTC_ADCx2I4			(ADC_INTC_EIC440_INTADCK2I4)	/* ADCx2 Scan group 4 (SG4) end interrupt	*/
	#define ADC_INTC_ADCx3I0			(ADC_INTC_EIC456_INTADCK3I0)	/* ADCx3 Scan group 0 (SG0) end interrupt	*/
	#define ADC_INTC_ADCx3I1			(ADC_INTC_EIC457_INTADCK3I1)	/* ADCx3 Scan group 1 (SG1) end interrupt	*/
	#define ADC_INTC_ADCx3I2			(ADC_INTC_EIC458_INTADCK3I2)	/* ADCx3 Scan group 2 (SG2) end interrupt	*/
	#define ADC_INTC_ADCx3I3			(ADC_INTC_EIC459_INTADCK3I3)	/* ADCx3 Scan group 3 (SG3) end interrupt	*/
	#define ADC_INTC_ADCx3I4			(ADC_INTC_EIC460_INTADCK3I4)	/* ADCx3 Scan group 4 (SG4) end interrupt	*/
	#define ADC_INTC_ADCxAI0			(ADC_INTC_EIC983_INTADCKAI0)	/* ADCxA Scan group 0 (SG0) end interrupt	*/
	#define ADC_INTC_ADCxAI1			(ADC_INTC_EIC984_INTADCKAI1)	/* ADCxA Scan group 1 (SG1) end interrupt	*/
	#define ADC_INTC_ADCxAI2			(ADC_INTC_EIC985_INTADCKAI2)	/* ADCxA Scan group 2 (SG2) end interrupt	*/
	#define ADC_INTC_ADCxAI3			(ADC_INTC_EIC986_INTADCKAI3)	/* ADCxA Scan group 3 (SG3) end interrupt	*/
	#define ADC_INTC_ADCxAI4			(ADC_INTC_EIC987_INTADCKAI4)	/* ADCxA Scan group 4 (SG4) end interrupt	*/
#endif

typedef	struct {
	uint16	u2EIC[ADC_INTC2_EIC_SIZE];
} Reg_Adc_Intc2_Type;

/* EIC	*/
#define		ADC_INTC_EIMKn			(BIT7)			/* Interrupt Mask			*/
	#define		ADC_INTC_EIMKn_ENABLE		(0U)		/* Interrupt processing is enabled.		*/
	#define		ADC_INTC_EIMKn_DISABLE		(1U)		/* Interrupt processing is disabled.	*/
#define		ADC_INTC_EIRFn			(BIT7)			/* Interrupt Request Flag	*/
	#define		ADC_INTC_EIRFn_OFF			(0U)		/* No interrupt request					*/
	#define		ADC_INTC_EIRFn_ON			(1U)		/* Interrupt request present			*/


#define Reg_ADC_INTC2				(*(volatile Reg_Adc_Intc2_Type*)(0xFFF80000U))

#endif
/*-- End Of File -------------------------------------------------------------------------------*/
