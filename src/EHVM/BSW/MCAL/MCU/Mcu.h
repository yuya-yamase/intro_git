/* MCU-r04-307 */
/************************************************************************************************/
/*																								*/
/*		MCU Driver																				*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

#ifndef MCU_H
#define	MCU_H

/*==============================================================================================*/
/* include files																				*/
/*==============================================================================================*/
#include	"Std_Types.h"
#include	"Mcal_SpalCmn.h"
#include	"Mcu_Cfg.h"

/*==============================================================================================*/
/* defines																						*/
/*==============================================================================================*/
#if ( ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) || ( MCAL_SPAL_TARGET == MCAL_TARGET_RCARS4_G4MH ) )
#define	MCU_CLK_RLIN_MOSC_1 			( CLOCK_CKSC_RLINC_RLINSCSID_MOSC )			/* RLIN clock source is MOSC/1 */
#define	MCU_CLK_RLIN_HSB_1				( CLOCK_CKSC_RLINC_RLINSCSID_HSB )			/* RLIN clock source is HSB/1 */
#define	MCU_CLK_RLIN_MOSC_4				( CLOCK_CKSC_RLINC_RLINSCSID_1_4_MOSC )		/* RLIN clock source is MOSC/4 */
#define	MCU_CLK_RLIN_MOSC_8				( CLOCK_CKSC_RLINC_RLINSCSID_1_8_MOSC )		/* RLIN clock source is MOSC/8 */

#define	MCU_CLK_RCAN_MOSC_1				( CLOCK_CKSC_RCANC_RCANSCSID_MOSC )			/* RCAN clock source is MOSC */
#define	MCU_CLK_RCAN_MOSC_2				( CLOCK_CKSC_RCANC_RCANSCSID_1_2_MOSC )		/* RCAN clock source is MOSC/2	*/
#define	MCU_CLK_RCAN_MOSC_4				( CLOCK_CKSC_RCANC_RCANSCSID_1_4_MOSC )		/* RCAN clock source is MOSC/4	*/

#define	MCU_CLK_MSPI_A_MOSC_1			( CLOCK_CKSC_MSPIC_MSPISCSID_MOSC )			/* MSPI clock source is MOSC/1 */
#define	MCU_CLK_MSPI_A_HSB_1			( CLOCK_CKSC_MSPIC_MSPISCSID_HSB )			/* MSPI clock source is HSB/1 */
#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) || ( MCAL_SPAL_TARGET == MCAL_TARGET_RCARS4_G4MH ) */

#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
#define	MCU_CLK_ADCJ_LSB_1				( CLOCK_CKSC_ADCC_ADCSCSID_LSB )			/* ADCJ clock source is LSB */
#define	MCU_CLK_ADCJ_LSB_2				( CLOCK_CKSC_ADCC_ADCSCSID_1_2_LSB )		/* ADCJ clock source is LSB/2 */
#endif	/* MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A */

#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
#define	MCU_CLK_SSCG_DITHERED_1			( CLOCK_SSCGC_SELMPERCENT_1 )				/* SSCG Modulation dithered -1.0% */
#define	MCU_CLK_SSCG_DITHERED_2			( CLOCK_SSCGC_SELMPERCENT_2 )				/* SSCG Modulation dithered -2.0% */
#define	MCU_CLK_SSCG_DITHERED_3			( CLOCK_SSCGC_SELMPERCENT_3 )				/* SSCG Modulation dithered -3.0% */
#define	MCU_CLK_SSCG_DITHERED_4			( CLOCK_SSCGC_SELMPERCENT_4 )				/* SSCG Modulation dithered -4.0% */
#define	MCU_CLK_SSCG_DITHERED_5			( CLOCK_SSCGC_SELMPERCENT_5 )				/* SSCG Modulation dithered -5.0% */

#define	MCU_CLK_RLIN3_CH23_EMG_1		( CLOCK_CKS_RLINC_RLIN23SCSID_EMG )			/* RLIN3 ch23 clock source is EMG/1 */
#define	MCU_CLK_RLIN3_CH23_HBUSC_1		( CLOCK_CKS_RLINC_RLIN23SCSID_HBUS )		/* RLIN3 ch23 clock source is HBUS/1 */
#define	MCU_CLK_RLIN3_CH23_MOSC_1		( CLOCK_CKS_RLINC_RLIN23SCSID_MOSC )		/* RLIN3 ch23 clock source is MOSC/1 */
#define	MCU_CLK_RLIN3_CH23_MOSC_4		( CLOCK_CKS_RLINC_RLIN23SCSID_4_MOSC )		/* RLIN3 ch23 clock source is MOSC/4 */
#define	MCU_CLK_RLIN3_CH23_MOSC_8		( CLOCK_CKS_RLINC_RLIN23SCSID_8_MOSC )		/* RLIN3 ch23 clock source is MOSC/8 */

#define	MCU_CLK_RLIN3_EMG_1				( CLOCK_CKS_RLINC_RLINSCSID_EMG )			/* RLIN3 clock source is EMG/1 */
#define	MCU_CLK_RLIN3_HSBC_1			( CLOCK_CKS_RLINC_RLINSCSID_HBUS )			/* RLIN3 clock source is HSBC/1 */
#define	MCU_CLK_RLIN3_MOSC_1			( CLOCK_CKS_RLINC_RLINSCSID_MOSC )			/* RLIN3 clock source is MOSC/1 */
#define	MCU_CLK_RLIN3_MOSC_4			( CLOCK_CKS_RLINC_RLINSCSID_4_MOSC )		/* RLIN3 clock source is MOSC/4 */
#define	MCU_CLK_RLIN3_MOSC_8			( CLOCK_CKS_RLINC_RLINSCSID_8_MOSC )		/* RLIN3 clock source is MOSC/8 */

#define	MCU_CLK_CANFD_C_EMG_1			( CLOCK_CKS_RCANC_RCANCSCSID_EMG )			/* RCANFD_C clock source is EMG/1 */
#define	MCU_CLK_CANFD_C_HSBC_1			( CLOCK_CKS_RCANC_RCANCSCSID_HSB )			/* RCANFD_C clock source is HSBC/1 */
#define	MCU_CLK_CANFD_C_HSBC_2			( CLOCK_CKS_RCANC_RCANCSCSID_2_HSB )		/* RCANFD_C clock source is HSBC/2 */
#define	MCU_CLK_CANFD_C_HSBC_4			( CLOCK_CKS_RCANC_RCANCSCSID_4_HSB )		/* RCANFD_C clock source is HSBC/4 */

#define	MCU_CLK_CANFD_XIN_EMG_1			( CLOCK_CKS_RCANC_RCANXINSCSID_EMG )		/* RCANFD_XIN clock source is EMG/1 */
#define	MCU_CLK_CANFD_XIN_MOSC_1		( CLOCK_CKS_RCANC_RCANXINSCSID_MOSC )		/* RCANFD_XIN clock source is MOSC/1 */
#define	MCU_CLK_CANFD_XIN_MOSC_2		( CLOCK_CKS_RCANC_RCANXINSCSID_2_MOSC )		/* RCANFD_XIN clock source is MOSC/2 */
#define	MCU_CLK_CANFD_XIN_MOSC_4		( CLOCK_CKS_RCANC_RCANXINSCSID_4_MOSC )		/* RCANFD_XIN clock source is MOSC/4 */

#define	MCU_CLK_MSPI_B_EMG_1			( CLOCK_CKS_MSPIC_MSPISCSID_EMG )			/* MSPI clock source is EMG/1 */
#define	MCU_CLK_MSPI_B_MOSC_1			( CLOCK_CKS_MSPIC_MSPISCSID_MOSC )			/* MSPI clock source is MOSC/1 */
#define	MCU_CLK_MSPI_B_HSBC_1			( CLOCK_CKS_MSPIC_MSPISCSID_HSB )			/* MSPI clock source is HSB/1 */

#define	MCU_CLK_SWDT_HSIOSC_20			( CLOCK_CKS_SWDTC_SWDTSCSID_1_20_HSIOSC )		/* SWDT clock source is HSIOSC/20 */
#define	MCU_CLK_SWDT_HSIOSC_640			( CLOCK_CKS_SWDTC_SWDTSCSID_1_640_HSIOSC )		/* SWDT clock source is HSIOSC/640 */
#define	MCU_CLK_SWDT_HSIOSC_800			( CLOCK_CKS_SWDTC_SWDTSCSID_1_800_HSIOSC )		/* SWDT clock source is HSIOSC/800 */
#define	MCU_CLK_SWDT_HSIOSC_100000		( CLOCK_CKS_SWDTC_SWDTSCSID_1_100000_HSIOSC )	/* SWDT clock source is HSIOSC/100000 */

#endif	/* MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B */

#if ( ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) || ( MCAL_SPAL_TARGET == MCAL_TARGET_RCARS4_G4MH ) )
#define	MCU_CLK_ATAUJC_A_LSIOSC_1		( CLOCK_CKSC_ATAUJC_ATAUJSCSID_LSIOSC )		/* TAUJ clock source is LSIOSC/1 */
#define	MCU_CLK_ATAUJC_A_HSIOSC_20		( CLOCK_CKSC_ATAUJC_ATAUJSCSID_1_20_HSIOSC )/* TAUJ clock source is HSIOSC/20 */
#define	MCU_CLK_ATAUJC_A_MOSC_1			( CLOCK_CKSC_ATAUJC_ATAUJSCSID_MOSC )		/* TAUJ clock source is MOSC/1 */
#define	MCU_CLK_ATAUJC_A_HSB_1			( CLOCK_CKSC_ATAUJC_ATAUJSCSID_HSB )		/* TAUJ clock source is HSB/1 */

#define	MCU_CLK_ARTCAC_A_MOSC_16		( CLOCK_CKSC_ARTCAC_ARTCASCSID_1_16_MOSC )	/* RTCA clock source is MOSC/16 */
#define	MCU_CLK_ARTCAC_A_LSIOSC_1		( CLOCK_CKSC_ARTCAC_ARTCASCSID_LSIOSC )		/* RTCA clock source is LSIOSC/1 */

#define	MCU_CLK_FOUT0C_MOSC_1			( CLOCK_CKSC_FOUT0C_FOUT0SCSID_A_MOSC )		/* FOUT clock source is MOSC/1 */
#define	MCU_CLK_FOUT0C_HSB_1			( CLOCK_CKSC_FOUT0C_FOUT0SCSID_HSB )		/* FOUT clock source is HSB/1 */
#define	MCU_CLK_FOUT0C_LSIOSC_1			( CLOCK_CKSC_FOUT0C_FOUT0SCSID_LSIOSC )		/* FOUT clock source is LSIOSC/1 */
#define	MCU_CLK_FOUT0C_HSIOSC_20		( CLOCK_CKSC_FOUT0C_FOUT0SCSID_1_20_HSIOSC )/* FOUT clock source is HSIOSC/20 */

#define	MCU_CLK_WDTC_A_HSIOSC_20		( CLOCK_CKSC_WDTC_WDTSCSID_1_20_HSIOSC )	/* WDTBA clock source is HSIOSC/20 */
#define	MCU_CLK_WDTC_A_HSIOSC_640		( CLOCK_CKSC_WDTC_WDTSCSID_1_640_HSIOSC )	/* WDTBA clock source is HSIOSC/640 */
#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) || ( MCAL_SPAL_TARGET == MCAL_TARGET_RCARS4_G4MH ) */

#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
#define	MCU_CLK_WDTBA_A_LSIOSC_1		( CLOCK_CKSC_AWDTC_AWDTSCSID_LSIOSC )		/* WDTB clock source is LSIOSC/1 */
#define	MCU_CLK_WDTBA_A_LSIOSC_128		( CLOCK_CKSC_AWDTC_AWDTSCSID_1_128_LSIOSC )	/* WDTB clock source is LSIOSC/128 */

#define	MCU_CLK_AADCC_A_MOSC_1			( CLOCK_CKSC_AADCC_AADCSCSID_MOSC )			/* ADCJ2 clock source is MOSC/1 */
#define	MCU_CLK_AADCC_A_HSIOSC_20		( CLOCK_CKSC_AADCC_AADCSCSID_1_20_HSIOSC )	/* ADCJ2 clock source is HSIOSC/20 */
#define	MCU_CLK_AADCC_A_LSB_1			( CLOCK_CKSC_AADCC_AADCSCSID_LSB )			/* ADCJ2 clock source is LSB/1 */

#define	MCU_CLKD_AADCC_1				( CLOCK_CLKD_AADCC_AADCDCSID_NO_DIV )			/* ADCJ2 clock is 1/2 */
#define	MCU_CLKD_AADCC_2				( CLOCK_CLKD_AADCC_AADCDCSID_1_2 )		/* ADCJ2 clock is 1/1 */

#define	MCU_CLK_FOUT1C_MOSC_1			( CLOCK_CKSC_FOUT1C_FOUT1SCSID_A_MOSC )		/* FOUT1 clock source is MOSC/1 */
#define	MCU_CLK_FOUT1C_HSB_1			( CLOCK_CKSC_FOUT1C_FOUT1SCSID_HSB )		/* FOUT1 clock source is HSB/1 */
#define	MCU_CLK_FOUT1C_LSIOSC_1			( CLOCK_CKSC_FOUT1C_FOUT1SCSID_LSIOSC )		/* FOUT1 clock source is LSIOSC/1 */
#define	MCU_CLK_FOUT1C_HSIOSC_20		( CLOCK_CKSC_FOUT1C_FOUT1SCSID_1_20_HSIOSC )/* FOUT1 clock source is HSIOSC/20 */
#endif	/* MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A */

#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
#define	MCU_CLK_WDTBA_B_LSIOSC_1		( CLOCK_CKS_AWDTC_AWDTSCSID_LSIOSC )		/* WDTBA clock source is LSIOSC/1 */
#define	MCU_CLK_WDTBA_B_LSIOSC_128		( CLOCK_CKS_AWDTC_AWDTSCSID_1_128_LSIOSC )	/* WDTBA clock source is LSIOSC/128 */

#define	MCU_CLK_ATAUJC_B_EMG_1			( CLOCK_CKS_ATAUJC_ATAUJSCSID_EMG )			/* TAUJ clock source is EMG/1 */
#define	MCU_CLK_ATAUJC_B_LSIOSC_1		( CLOCK_CKS_ATAUJC_ATAUJSCSID_LSIOSC )		/* TAUJ clock source is LSIOSC/1 */
#define	MCU_CLK_ATAUJC_B_HSIOSC_20		( CLOCK_CKS_ATAUJC_ATAUJSCSID_1_20_HSIOSC )	/* TAUJ clock source is HSIOSC/20 */
#define	MCU_CLK_ATAUJC_B_MOSC_1			( CLOCK_CKS_ATAUJC_ATAUJSCSID_MOSC )		/* TAUJ clock source is MOSC/1 */
#define	MCU_CLK_ATAUJC_B_HSBC_1			( CLOCK_CKS_ATAUJC_ATAUJSCSID_HSB )			/* TAUJ clock source is HSB(clean)/1 */

#define	MCU_CLK_ARTCAC_B_EMG_1			( CLOCK_CKS_ARTCAC_ARTCASCSID_EMG )			/* RTCA clock source is EMG/1 */
#define	MCU_CLK_ARTCAC_B_LSIOSC_1		( CLOCK_CKS_ARTCAC_ARTCASCSID_LSIOSC )		/* RTCA clock source is LSIOSC/1 */
#define	MCU_CLK_ARTCAC_B_MOSC_16		( CLOCK_CKS_ARTCAC_ARTCASCSID_1_16_MOSC )	/* RTCA clock source is MOSC/16 */

#define	MCU_CLK_AADCC_B_EMG_1			( CLOCK_CKS_AADCC_AADCSCSID_EMG )			/* ADCKA clock source is EMG/1 */
#define	MCU_CLK_AADCC_B_HSIOSC_20		( CLOCK_CKS_AADCC_AADCSCSID_1_20_HSIOSC )	/* ADCKA clock source is HSIOSC/20 */
#define	MCU_CLK_AADCC_B_MOSC_1			( CLOCK_CKS_AADCC_AADCSCSID_MOSC )			/* ADCKA clock source is MOSC/1 */
#define	MCU_CLK_AADCC_B_LSBC_1			( CLOCK_CKS_AADCC_AADCSCSID_LSB )			/* ADCKA clock source is LSB/1 */

#define	MCU_CLK_EXTCLK0C_MOSC_1			( CLOCK_EXTCLK0SCSID_MOSC )					/* EXTCLK0 clock source is MOSC/1 */
#define	MCU_CLK_EXTCLK0C_LSIOSC_1		( CLOCK_EXTCLK0SCSID_LSIOSC )				/* EXTCLK0 clock source is LSIOSC/1 */
#define	MCU_CLK_EXTCLK0C_HSIOSC_20		( CLOCK_EXTCLK0SCSID_1_20_HSIOSC )			/* EXTCLK0 clock source is HSIOSC/20 */
#define	MCU_CLK_EXTCLK0C_HSB_1			( CLOCK_EXTCLK0SCSID_CLK_HSB )				/* EXTCLK0 clock source is HSB/1 */
#define	MCU_CLK_EXTCLK0C_HSBC_1			( CLOCK_EXTCLK0SCSID_CLKC_HSB )				/* EXTCLK0 clock source is HSB(clean)/1 */

#define	MCU_CLK_EXTCLK1C_MOSC_1			( CLOCK_EXTCLK1SCSID_MOSC )					/* EXTCLK1 clock source is MOSC/1 */
#define	MCU_CLK_EXTCLK1C_LSIOSC_1		( CLOCK_EXTCLK1SCSID_LSIOSC )				/* EXTCLK1 clock source is LSIOSC/1 */
#define	MCU_CLK_EXTCLK1C_HSIOSC_20		( CLOCK_EXTCLK1SCSID_1_20_HSIOSC )			/* EXTCLK1 clock source is HSIOSC/20 */
#define	MCU_CLK_EXTCLK1C_HSB_1			( CLOCK_EXTCLK1SCSID_CLK_HSB )				/* EXTCLK1 clock source is HSB/1 */
#define	MCU_CLK_EXTCLK1C_HSBC_1			( CLOCK_EXTCLK1SCSID_CLKC_HSB )				/* EXTCLK1 clock source is HSB(clean)/1 */

#define	MCU_CLK_WDTC_B_HSIOSC_20		( CLOCK_CKS_WDTC_WDTSCSID_1_20_HSIOSC )		/* WDTB clock source is HSIOSC/20 */
#define	MCU_CLK_WDTC_B_HSIOSC_640		( CLOCK_CKS_WDTC_WDTSCSID_1_640_HSIOSC )	/* WDTB clock source is HSIOSC/640 */
#define	MCU_CLK_WDTC_B_HSIOSC_800		( CLOCK_CKS_WDTC_WDTSCSID_1_800_HSIOSC )	/* WDTB clock source is HSIOSC/800 */

#define	MCU_CLK_SSCG_8					( (uint32)( CLOCK_SSCGC_SELMFREQ_LOWEST_VALID_VALUE + 0U ) )	/* SSCG modulation frequency 8 */
#define	MCU_CLK_SSCG_9					( (uint32)( CLOCK_SSCGC_SELMFREQ_LOWEST_VALID_VALUE + 1U ) )	/* SSCG modulation frequency 9 */
#define	MCU_CLK_SSCG_10					( (uint32)( CLOCK_SSCGC_SELMFREQ_LOWEST_VALID_VALUE + 2U ) )	/* SSCG modulation frequency 10 */
#define	MCU_CLK_SSCG_11					( (uint32)( CLOCK_SSCGC_SELMFREQ_LOWEST_VALID_VALUE + 3U ) )	/* SSCG modulation frequency 11 */
#define	MCU_CLK_SSCG_12					( (uint32)( CLOCK_SSCGC_SELMFREQ_LOWEST_VALID_VALUE + 4U ) )	/* SSCG modulation frequency 12 */
#define	MCU_CLK_SSCG_13					( (uint32)( CLOCK_SSCGC_SELMFREQ_LOWEST_VALID_VALUE + 5U ) )	/* SSCG modulation frequency 13 */
#define	MCU_CLK_SSCG_14					( (uint32)( CLOCK_SSCGC_SELMFREQ_LOWEST_VALID_VALUE + 6U ) )	/* SSCG modulation frequency 14 */
#define	MCU_CLK_SSCG_15					( (uint32)( CLOCK_SSCGC_SELMFREQ_LOWEST_VALID_VALUE + 7U ) )	/* SSCG modulation frequency 15 */
#define	MCU_CLK_SSCG_16					( (uint32)( CLOCK_SSCGC_SELMFREQ_LOWEST_VALID_VALUE + 8U ) )	/* SSCG modulation frequency 16 */
#define	MCU_CLK_SSCG_17					( (uint32)( CLOCK_SSCGC_SELMFREQ_LOWEST_VALID_VALUE + 9U ) )	/* SSCG modulation frequency 17 */
#define	MCU_CLK_SSCG_18					( (uint32)( CLOCK_SSCGC_SELMFREQ_LOWEST_VALID_VALUE + 10U ) )	/* SSCG modulation frequency 18 */
#define	MCU_CLK_SSCG_19					( (uint32)( CLOCK_SSCGC_SELMFREQ_LOWEST_VALID_VALUE + 11U ) )	/* SSCG modulation frequency 19 */
#define	MCU_CLK_SSCG_20					( (uint32)( CLOCK_SSCGC_SELMFREQ_LOWEST_VALID_VALUE + 12U ) )	/* SSCG modulation frequency 20 */
#define	MCU_CLK_SSCG_21					( (uint32)( CLOCK_SSCGC_SELMFREQ_LOWEST_VALID_VALUE + 13U ) )	/* SSCG modulation frequency 21 */
#define	MCU_CLK_SSCG_22					( (uint32)( CLOCK_SSCGC_SELMFREQ_LOWEST_VALID_VALUE + 14U ) )	/* SSCG modulation frequency 22 */
#define	MCU_CLK_SSCG_23					( (uint32)( CLOCK_SSCGC_SELMFREQ_LOWEST_VALID_VALUE + 15U ) )	/* SSCG modulation frequency 23 */
#define	MCU_CLK_SSCG_24					( (uint32)( CLOCK_SSCGC_SELMFREQ_LOWEST_VALID_VALUE + 16U ) )	/* SSCG modulation frequency 24 */
#define	MCU_CLK_SSCG_25					( (uint32)( CLOCK_SSCGC_SELMFREQ_LOWEST_VALID_VALUE + 17U ) )	/* SSCG modulation frequency 25 */
#define	MCU_CLK_SSCG_26					( (uint32)( CLOCK_SSCGC_SELMFREQ_LOWEST_VALID_VALUE + 18U ) )	/* SSCG modulation frequency 26 */
#define	MCU_CLK_SSCG_27					( (uint32)( CLOCK_SSCGC_SELMFREQ_LOWEST_VALID_VALUE + 19U ) )	/* SSCG modulation frequency 27 */
#define	MCU_CLK_SSCG_28					( (uint32)( CLOCK_SSCGC_SELMFREQ_LOWEST_VALID_VALUE + 20U ) )	/* SSCG modulation frequency 28 */
#define	MCU_CLK_SSCG_29					( (uint32)( CLOCK_SSCGC_SELMFREQ_LOWEST_VALID_VALUE + 21U ) )	/* SSCG modulation frequency 29 */
#define	MCU_CLK_SSCG_30					( (uint32)( CLOCK_SSCGC_SELMFREQ_LOWEST_VALID_VALUE + 22U ) )	/* SSCG modulation frequency 30 */
#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B ) */

#define	MCU_SYSTEM_RESET_2				( 0U )					/* System Reset 2 by Mcu_PerformReset() */
#define	MCU_APPLICATION_RESET			( 1U )					/* Application Reset by Mcu_PerformReset() */

#define	MCU_REGCHK_OK					( (uint32)0x00000000U )
#define	MCU_REGCHK_NG					( (uint32)0x00000001U )
#define	MCU_REGCHK_REFRESH_SUCCESS		( (uint32)0x00000002U )
#define	MCU_REGCHK_REFRESH_IMPOSSIBLE	( (uint32)0x00000004U )
#define	MCU_REGCHK_REFRESH_FAILED		( (uint32)0x00000008U )

/*==============================================================================================*/
/* data types / structs / unions / macros														*/
/*==============================================================================================*/
typedef struct							/* Provided to the MCU initialization routines for configuration */
{
	uint32 Dummy;
} Mcu_ConfigType;

typedef uint32 Mcu_ClockType;			/* The identification for a clock setting */
#define	MCU_CLOCK_TYPE_0				( (Mcu_ClockType)0U )	/* Clock Setting ID 0 */

typedef enum							/* Status value returned by the function Mcu_GetPllStatus() */
{
	MCU_PLL_LOCKED,						/* Stable state 	*/
	MCU_PLL_UNLOCKED,					/* Unstable state 	*/
	MCU_PLL_STATUS_UNDEFINED			/* Undefined state 	*/
} Mcu_PllStatusType;

typedef uint32 Mcu_ModeType;			/* The identification for a MCU mode */
#define	MCU_MODE_DEEPSTOP				( (Mcu_ModeType)0U )	/* DeepSTOP Mode ID */

typedef enum							/* Reset type */
{
	MCU_POWER_ON_RESET,					/* Power On Reset */
	MCU_POWER_OFF_STANDBY_RESET,		/* Power Off Standby Reset for RH850U2B */
	MCU_EXTERNAL_RESET,					/* External Reset */
	MCU_PRIMARY_VMON_RESET,				/* Primary VMON Reset */
	MCU_SOFTWARE_SYSTEM_RESET,			/* Software System Reset */
	MCU_ECM_SYSTEM_RESET_2,				/* ECM System Reset 2 */
	MCU_WDTBA_RESET,					/* WDTBA Reset */
	MCU_SOFTWARE_APPLICATION_RESET,		/* Software Application Reset for RH850U2A or RH850U2B */
	MCU_ECM_APPLICATION_RESET,			/* ECM Application Reset for RH850U2A or RH850U2B */
	MCU_HW_BIST0_EXECUTION_RESET,		/* HW BIST (Field BIST 0) Execution */
	MCU_HW_BIST1_EXECUTION_RESET,		/* HW BIST (Field BIST 1) Execution */
	MCU_HW_BIST2_EXECUTION_RESET,		/* HW BIST (Field BIST 2) Execution for RH850U2A or RH850U2B */
	MCU_DEEPSTOP_RESET,					/* DeepSTOP Reset */
	MCU_ICUMHA_SOFT_SYS_RESET,			/* ICUMHA Software System Reset for RH850U2A */
	MCU_ICUMHB_SOFT_SYS_RESET,			/* ICUMHB Software System Reset for RH850U2B */
	MCU_ICUMHA_SOFT_APP_RESET,			/* ICUMHA Software Application Reset for RH850U2A */
	MCU_ICUMHB_SOFT_APP_RESET,			/* ICUMHB Software Application Reset for RH850U2B */
	MCU_SOFT_POWER_ON_RESET,			/* Soft Power on Reset for R-CarS4 G4MH */
	MCU_SYSTEM_WDT_RESET,				/* System WDT Reset for R-CarS4 G4MH */
	MCU_RWDT_RESET,						/* RWDT Reset for R-CarS4 G4MH */
	MCU_MULTIPLE_RESET,					/* Multiple resets above */
	MCU_RESET_UNDEFINED					/* Reset undefined */
} Mcu_ResetType;

typedef struct							/* Reset factor returned by the function Mcu_GetResetReason() */
{
	uint32	RegBit;
	Mcu_ResetType	ResetType;
} stMcu_ResetReason;

typedef uint32 Mcu_RawResetType;		/* Raw Reset factor returned by the function Mcu_GetResetRawValue() */

/*==============================================================================================*/
/* functions																					*/
/*==============================================================================================*/
#define MCU_START_SEC_CODE_GLOBAL
#include "Mcu_MemMap.h"
/*==============================================================================================*/
/* API functions																				*/
/*==============================================================================================*/
/************************************************************************************************/
/* Service name		:	Mcu Initialization														*/
/* Reentrancy		:	Non Re-entrant															*/
/* Parameters(in)	:	ConfigPtr - Pointer to configuration set								*/
/* Return value		:	None																	*/
/* Limitation		:	This function must be called with interrupts disabled					*/
/*					:	Do not use the configuration information given in ConfigPtr				*/
/*					:	Set the argument to NULL												*/
/*					:	Call once before using the MCU API										*/
/************************************************************************************************/
FUNC( void, MCU_CODE ) Mcu_Init( const Mcu_ConfigType* ConfigPtr );

#if	( MCU_CFG_INIT_CLOCK == STD_ON )
/************************************************************************************************/
/* Service name		:	Initialize the PLL and MCU clock										*/
/* Reentrancy		:	Non Re-entrant															*/
/* Parameters(in)	:	ClockSetting - the configuration (parameters) for the Clock settings	*/
/* Return value		:	E_OK		| Success													*/
/*				 	:	E_NOT_OK	| Failure													*/
/* Limitation		:	Call Mcu_Init before calling this API									*/
/*					:	Set the argument to MCU_CLOCK_TYPE_0									*/
/************************************************************************************************/
FUNC( Std_ReturnType, MCU_CODE ) Mcu_InitClock( Mcu_ClockType ClockSetting );
#endif	/* ( MCU_CFG_INIT_CLOCK == STD_ON ) */

#if	( MCU_CFG_NO_PLL == FALSE )
/************************************************************************************************/
/* Service name		:	Activate the PLL clock to the MCU clock distribution					*/
/* Reentrancy		:	Non Re-entrant															*/
/* Parameters(in)	:	None																	*/
/* Return value		:	E_OK		| Success													*/
/*				 	:	E_NOT_OK	| Failure													*/
/* Limitation		:	Call this API after confirming that the PLL is locked by				*/
/*					:	Mcu_GetPllStatus()														*/
/************************************************************************************************/
FUNC( Std_ReturnType, MCU_CODE ) Mcu_DistributePllClock( void );
#endif	/* ( MCU_CFG_NO_PLL == FALSE ) */

/************************************************************************************************/
/* Service name		:	Provide the lock status of the PLL										*/
/* Reentrancy		:	Re-entrant																*/
/* Parameters(in)	:	None																	*/
/* Return value		:	MCU_PLL_LOCKED				|	Stable state 							*/
/*					:	MCU_PLL_UNLOCKED			|	Unstable state 							*/
/*					:	MCU_PLL_STATUS_UNDEFINED	|	Undefined state 						*/
/* Limitation		:	Call Mcu_Init before calling this API									*/
/************************************************************************************************/
FUNC( Mcu_PllStatusType, MCU_CODE ) Mcu_GetPllStatus( void );

#if( ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) || ( MCAL_SPAL_TARGET == MCAL_TARGET_RCARS4_G4MH ) )
/************************************************************************************************/
/* Service name		:	Switch to Chip Standby Mode												*/
/* Reentrancy		:	Non Re-entrant															*/
/* Parameters(in)	:	McuMode - Chip Standby Mode configuration								*/
/* Return value		:	None																	*/
/* Limitation		:	For R-CarS4 G4MH, set Cortex-R52 to Sleep mode and Cortex-A55 CPU core	*/
/*					:	and cluster to OFF mode before calling this API							*/
/*					:	DeepSTOP mode is not supported for U2B6 and U2B10						*/
/*					:	Call Mcu_Init before calling this API									*/
/************************************************************************************************/
FUNC( void, MCU_CODE ) Mcu_SetMode( Mcu_ModeType McuMode );
#endif	/* ( ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) || ( MCAL_SPAL_TARGET == MCAL_TARGET_RCARS4_G4MH ) ) */

#if	( MCU_CFG_PERFORM_RESET == STD_ON )
/************************************************************************************************/
/* Service name		:	Perform a microcontroller reset											*/
/* Reentrancy		:	Non Re-entrant															*/
/* Parameters(in)	:	None																	*/
/* Return value		:	None																	*/
/* Limitation		:	Call Mcu_Init before calling this API									*/
/************************************************************************************************/
FUNC( void, MCU_CODE ) Mcu_PerformReset( void );
#endif	/* ( MCU_CFG_PERFORM_RESET == STD_ON ) */

#if	( MCU_CFG_RESET_REASON == STD_ON )
/************************************************************************************************/
/* Service name		:	Provide the reset factor												*/
/* Reentrancy		:	Re-entrant																*/
/* Parameters(in)	:	None																	*/
/* Return value		:	None																	*/
/* Limitation		:	Call Mcu_Init before calling this API									*/
/************************************************************************************************/
FUNC( Mcu_ResetType, MCU_CODE ) Mcu_GetResetReason( void );

/************************************************************************************************/
/* Service name		:	Provide the raw reset factor											*/
/* Reentrancy		:	Re-entrant																*/
/* Parameters(in)	:	None																	*/
/* Return value		:	None																	*/
/* Limitation		:	Call Mcu_Init before calling this API									*/
/************************************************************************************************/
FUNC( Mcu_RawResetType, MCU_CODE ) Mcu_GetResetRawValue( void );
#endif	/* ( MCU_CFG_RESET_REASON == STD_ON ) */

#if	( MCU_CFG_REG_CHK == STD_ON )
/************************************************************************************************/
/* Function			:	Mcu_Regchk_All															*/
/* Reentrancy		:	Non Reentrant															*/
/* Parameters(in)	:	None																	*/
/* Return value		:	Register Check Result													*/
/* Limitation		:	None																	*/
/************************************************************************************************/
FUNC( uint32, MCU_CODE ) Mcu_Regchk_All( void );
#endif /* ( MCU_CFG_REG_CHK == STD_ON ) */

/*----------------------------------------------------------------------------------------------*/
/* Scheduled / Event Functions																	*/
/*----------------------------------------------------------------------------------------------*/
#define MCU_STOP_SEC_CODE_GLOBAL
#include "Mcu_MemMap.h"

#endif /* MCU_H */
/*-- End Of File -------------------------------------------------------------------------------*/
