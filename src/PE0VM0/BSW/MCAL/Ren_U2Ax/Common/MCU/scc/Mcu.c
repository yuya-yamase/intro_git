/* MCU-r04-303 */
/************************************************************************************************/
/*																								*/
/*		MCU Driver																				*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

/*==============================================================================================*/
/* include files																				*/
/*==============================================================================================*/
#include	"Std_Types.h"
#include	"Mcal_SpalCmn.h"
#include	"McalCommon_lib.h"
#include	"Mcu.h"
#include	"Mcu_Cfg.h"
#include	"Reg_Clock.h"
#include	"Reg_Clma.h"
#include	"Reg_Stbc.h"
#include	"Reg_Reset.h"
#include	"Reg_Ecm.h"

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
#include	"Reg_Adc.h"
#include	"Reg_Tauj.h"
#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) */

#if	( MCU_CFG_DEM_SET_EVENT == STD_ON )
#include	"Rte_Dem_Type.h"
#endif	/* ( MCU_CFG_DEM_SET_EVENT == STD_ON ) */

/*==============================================================================================*/
/* defines / data types / structs / unions / macros												*/
/*==============================================================================================*/
#define	MCU_PLLE_PLLENTRG_STARTPLL		( (uint32)( CLOCK_PLLE_PLLENTRG_START * CLOCK_PLLE_PLLENTRG ) )						/* PLL enable trigger */

#define	MCU_PLLS_STOPPED				( (uint32)( ( CLOCK_PLLS_PLLCLKEN_DISTRGSET * CLOCK_PLLS_PLLCLKEN ) + ( CLOCK_PLLS_PLLCLKSTAB_UNSTABLE * CLOCK_PLLS_PLLCLKSTAB ) ) )	/* PLL is stopped */
#define	MCU_PLLS_STABLE 				( (uint32)( ( CLOCK_PLLS_PLLCLKEN_ENTRGSET * CLOCK_PLLS_PLLCLKEN ) + ( CLOCK_PLLS_PLLCLKSTAB_STABLE * CLOCK_PLLS_PLLCLKSTAB ) ) )		/* PLL is stable and enable */
#define	MCU_PLLS_PLLCLKSTAB_STABLE		( (uint32)( CLOCK_PLLS_PLLCLKSTAB_STABLE * CLOCK_PLLS_PLLCLKSTAB ) )				/* PLL is stable */

#define	MCU_MOSCE_MOSCENTRG_START		( (uint32)( CLOCK_MOSCS_MOSCEN_ENTRG_SET * CLOCK_MOSCS_MOSCEN ) )					/* MainOSC enable trigger */

#define	MCU_MOSCS_STOPPED				( (uint32)( ( CLOCK_MOSCS_MOSCEN_DISTRG_SET * CLOCK_MOSCS_MOSCEN ) + ( CLOCK_MOSCS_MOSCSTAB_UNSTABLE * CLOCK_MOSCS_MOSCSTAB ) ) )		/* MainOSC is stopped */
#define	MCU_MOSCS_STABLE 				( (uint32)( ( CLOCK_MOSCS_MOSCEN_ENTRG_SET * CLOCK_MOSCS_MOSCEN ) + ( CLOCK_MOSCS_MOSCSTAB_STABLE * CLOCK_MOSCS_MOSCSTAB ) ) )			/* MainOSC is stable and enable */
#define	MCU_MOSCS_MOSCSTAB_STABLE		( (uint32)( CLOCK_MOSCS_MOSCSTAB_STABLE * CLOCK_MOSCS_MOSCSTAB ) )					/* MainOSC is stable */
#define	MCU_MOSCS_MOSCEN_ENABLE			( (uint32)( CLOCK_MOSCS_MOSCEN_ENTRG_SET * CLOCK_MOSCS_MOSCEN ) )					/* MainOSC is enable */

#define	MCU_HSOSCS_STABLE 				( (uint32)( CLOCK_HSOSCS_HSOSCSTAB_STABLE * CLOCK_HSOSCS_HSOSCSTAB ) )				/* HSIntOSC is stable */

#define	MCU_FOUT0C_STOPPED				( (uint32)( 0U * CLOCK_CLKD_FOUT0C_FOUT0DIV_0 ) )									/* FOUT0 is stopped */
#define	MCU_EXTCLK0C_STOPPED			( (uint32)( 0U * CLOCK_CKD_EXTCLK0C_EXTCLK0DIV_0 ) )								/* EXTCLK0 is stopped */
#define	MCU_FOUT1C_STOPPED				( (uint32)( 0U * CLOCK_CLKD_FOUT1C_FOUT1DIV_0 ) )									/* FOUT1 is stopped */
#define	MCU_EXTCLK1C_STOPPED			( (uint32)( 0U * CLOCK_CKD_EXTCLK1C_EXTCLK1DIV_0 ) )								/* EXTCLK1 is stopped */

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
#define	MCU_PLL_SYNC					( (uint32)( CLOCK_CLKD_PLLS_PLLCLKDSYNC_SYNC * CLOCK_CLKD_PLLS_PLLCLKDSYNC ) )		/* PLL is synchronized */
#define	MCU_FOUT0S_STABLE				( (uint32)( CLOCK_CLKD_FOUT0S_FOUT0SYNC_STABLE * CLOCK_CLKD_FOUT0S_FOUT0SYNC ) )	/* FOUT0 is synchronized */
#define	MCU_FOUT0S_STOP_STABLE			( (uint32)( CLOCK_CLKD_FOUT0S_FOUT0CLKACT_STOP * CLOCK_CLKD_FOUT0S_FOUT0CLKACT ) + \
												  ( CLOCK_CLKD_FOUT0S_FOUT0SYNC_STABLE * CLOCK_CLKD_FOUT0S_FOUT0SYNC ) )	/* FOUT0 is stop and synchronized */
#define	MCU_FOUT1S_STABLE				( (uint32)( CLOCK_CLKD_FOUT1S_FOUT1SYNC_STABLE * CLOCK_CLKD_FOUT1S_FOUT1SYNC ) )	/* FOUT1 is synchronized */
#define	MCU_FOUT1S_STOP_STABLE			( (uint32)( CLOCK_CLKD_FOUT1S_FOUT1CLKACT_STOP * CLOCK_CLKD_FOUT1S_FOUT1CLKACT ) + \
												  ( CLOCK_CLKD_FOUT1S_FOUT1SYNC_STABLE * CLOCK_CLKD_FOUT1S_FOUT1SYNC ) )	/* FOUT1 is stop and synchronized */
#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) */

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
#define	MCU_PLL_SYNC					( (uint32)( CLOCK_CKD_PLLS_PLLCLKDSYNC_SYNC * CLOCK_CKD_PLLS_PLLCLKDSYNC ) )		/* PLL is synchronized */
#define	MCU_EXTCLK0S_ONGOING			( (uint32)( CLOCK_EXTCLK0CLKACT_ONGOING * CLOCK_EXTCLK0CLKACT ) )
#define	MCU_EXTCLK0S_STABLE				( (uint32)( CLOCK_EXTCLK0SYNC_STABLE * CLOCK_EXTCLK0SYNC ) )						/* EXTCLK0 is synchronized */
#define	MCU_EXTCLK0S_STOP_STABLE		( (uint32)( ( CLOCK_EXTCLK0CLKACT_STOP * CLOCK_EXTCLK0CLKACT ) + ( CLOCK_EXTCLK0SYNC_STABLE * CLOCK_EXTCLK0SYNC ) ) )	/* EXTCLK0 is stop and synchronized */
#define	MCU_EXTCLK1S_ONGOING			( (uint32)( CLOCK_EXTCLK1CLKACT_ONGOING * CLOCK_EXTCLK1CLKACT ) )
#define	MCU_EXTCLK1S_STABLE				( (uint32)( CLOCK_EXTCLK1SYNC_STABLE * CLOCK_EXTCLK1SYNC ) )						/* EXTCLK1 is synchronized */
#define	MCU_EXTCLK1S_STOP_STABLE		( (uint32)( ( CLOCK_EXTCLK1CLKACT_STOP * CLOCK_EXTCLK1CLKACT ) + ( CLOCK_EXTCLK1SYNC_STABLE * CLOCK_EXTCLK1SYNC ) ) )	/* EXTCLK1 is stop and synchronized */
#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B ) */

#define	MCU_CKSC_CPUC_CPUCLKSCSID_PLLO	( (uint32)( CLOCK_CKSC_CPUC_CPUCLKSCSID_PLLO * CLOCK_CKSC_CPUC_CPUCLKSCSID ) )		/* Clock source for system clock */

#define	MCU_CLK_PLLO_16_16				( (uint32)( CLOCK_CKD_PLLC_PLLCLKDCSID_NO_DIV * CLOCK_CKD_PLLC_PLLCLKDCSID_0 ) )	/* PLL is 16/16 */
#define	MCU_CLK_PLLO_4_16				( (uint32)( CLOCK_CKD_PLLC_PLLCLKDCSID_4_16 * CLOCK_CKD_PLLC_PLLCLKDCSID_0 ) )		/* PLL is 4/16 */
#define	MCU_CLK_PLLO_6_16				( (uint32)( CLOCK_CKD_PLLC_PLLCLKDCSID_6_16 * CLOCK_CKD_PLLC_PLLCLKDCSID_0 ) )		/* PLL is 6/16 */
#define	MCU_CLK_PLLO_8_16				( (uint32)( CLOCK_CKD_PLLC_PLLCLKDCSID_8_16 * CLOCK_CKD_PLLC_PLLCLKDCSID_0 ) )		/* PLL is 8/16 */
#define	MCU_CLK_PLLO_10_16				( (uint32)( CLOCK_CKD_PLLC_PLLCLKDCSID_10_16 * CLOCK_CKD_PLLC_PLLCLKDCSID_0 ) )		/* PLL is 10/16 */
#define	MCU_CLK_PLLO_12_16				( (uint32)( CLOCK_CKD_PLLC_PLLCLKDCSID_12_16 * CLOCK_CKD_PLLC_PLLCLKDCSID_0 ) )		/* PLL is 12/16 */
#define	MCU_CLK_PLLO_14_16				( (uint32)( CLOCK_CKD_PLLC_PLLCLKDCSID_14_16 * CLOCK_CKD_PLLC_PLLCLKDCSID_0 ) )		/* PLL is 14/16 */

#define	MCU_CLK_SYS_PLL_1				( (uint32)( CLOCK_CLKD_PLLC_PLLCLKDCSID_NO_DIV * CLOCK_CLKD_PLLC_PLLCLKDCSID_0 ) )	/* System clock is 1/1 */
#define	MCU_CLK_SYS_PLL_2				( (uint32)( CLOCK_CLKD_PLLC_PLLCLKDCSID_1_2 * CLOCK_CLKD_PLLC_PLLCLKDCSID_0 ) )		/* System clock is 1/2 */

#define	MCU_SSCG_SYNC					( (uint32)( CLOCK_CKD_SSCGS_SSCGCLKDSYNC_SYNC * CLOCK_CKD_SSCGS_SSCGCLKDSYNC ) )	/* SSCG is synchronized */

#define	MCU_CKS_CLEANC_SYSCLKSC_PLLO	( (uint32)( CLOCK_CKS_CLEANC_SYSCLKSCSID_PLLO * CLOCK_CKS_CLEANC_SYSCLKSCSID ) )	/* PLL clock source for system clock */
#define	MCU_CKS_SSCGC_SYSCLKSC_SSCGO	( (uint32)( CLOCK_CKS_SSCGC_SYSCLKSCSID_SSCGO * CLOCK_CKS_SSCGC_SYSCLKSCSID ) )		/* SSCG PLL clock source for system clock */

#define	MCU_CLK_SSCGO_16_16				( (uint32)( CLOCK_CKD_PLLC_PLLCLKDCSID_NO_DIV * CLOCK_CKD_PLLC_PLLCLKDCSID_0 ) )	/* SSCG is 16/16 */
#define	MCU_CLK_SSCGO_4_16				( (uint32)( CLOCK_CKD_PLLC_PLLCLKDCSID_4_16 * CLOCK_CKD_PLLC_PLLCLKDCSID_0 ) )		/* SSCG is 4/16 */
#define	MCU_CLK_SSCGO_6_16				( (uint32)( CLOCK_CKD_PLLC_PLLCLKDCSID_6_16 * CLOCK_CKD_PLLC_PLLCLKDCSID_0 ) )		/* SSCG is 6/16 */
#define	MCU_CLK_SSCGO_8_16				( (uint32)( CLOCK_CKD_PLLC_PLLCLKDCSID_8_16 * CLOCK_CKD_PLLC_PLLCLKDCSID_0 ) )		/* SSCG is 8/16 */
#define	MCU_CLK_SSCGO_10_16				( (uint32)( CLOCK_CKD_PLLC_PLLCLKDCSID_10_16 * CLOCK_CKD_PLLC_PLLCLKDCSID_0 ) )		/* SSCG is 10/16 */
#define	MCU_CLK_SSCGO_12_16				( (uint32)( CLOCK_CKD_PLLC_PLLCLKDCSID_12_16 * CLOCK_CKD_PLLC_PLLCLKDCSID_0 ) )		/* SSCG is 12/16 */
#define	MCU_CLK_SSCGO_14_16				( (uint32)( CLOCK_CKD_PLLC_PLLCLKDCSID_14_16 * CLOCK_CKD_PLLC_PLLCLKDCSID_0 ) )		/* SSCG is 14/16 */

#define	MCU_CPU_SACT					( (uint32)( CLOCK_CKSC_CPUS_CPUCLKSACT_PLLO * CLOCK_CKSC_CPUS_CPUCLKSACT ) )		/* CPU is stable */
#define	MCU_CLEAN_SACT					( (uint32)( CLOCK_CKS_CLEANS_SYSCLKSACT_PLLO * CLOCK_CKS_CLEANS_SYSCLKSACT ) )		/* CPU(clean) is stable */
#define	MCU_SSCG_SACT					( (uint32)( CLOCK_CKS_SSCGS_SYSCLKSACT_SSCG * CLOCK_CKS_SSCGS_SYSCLKSACT ) )		/* SSCG is stable */

#define	MCU_SSCGC_SSMODE1_BITPOS		( (uint32)( CLOCK_SSCGC_SSMODE1_ENABLE * CLOCK_SSCGC_SSMODE1 ) )					/* SSCG modulation control */

#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
#define	MCU_WAIT_SSCG_STABLE_TIME_INIT	( (uint32)100U )			/* Wait for SSCG stabilization (200us) with 200MHz */
#define	MCU_WAIT_SSCG_STABLE_TIME_6_16	( (uint32)38U )			/* Wait for SSCG stabilization (100us) with 6/16 SSCG (800MHz) */
#define	MCU_WAIT_SSCG_STABLE_TIME_8_16	( (uint32)50U )			/* Wait for SSCG stabilization (100us) with 8/16 SSCG (800MHz) */
#define	MCU_WAIT_SSCG_STABLE_TIME_10_16	( (uint32)63U )			/* Wait for SSCG stabilization (100us) with 10/16 SSCG (800MHz) */
#define	MCU_WAIT_SSCG_STABLE_TIME_12_16	( (uint32)75U )			/* Wait for SSCG stabilization (100us) with 12/16 SSCG (800MHz) */
#define	MCU_WAIT_SSCG_STABLE_TIME_14_16	( (uint32)88U )			/* Wait for SSCG stabilization (100us) with 14/16 SSCG (800MHz) */
#define	MCU_WAIT_SSCG_STABLE_TIME_16_16	( (uint32)100U )		/* Wait for SSCG stabilization (100us) with 16/16 SSCG (800MHz) */
#define	MCU_WAIT_SSCG_STABLE_TIME		( (uint32)200U )		/* Wait for SSCG stabilization (200us) with 16/16 SSCG (400MHz) */
#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B ) */

#define	MCU_PLL_READ_STABLE_TIMES		( (sint32)4 )										/* Number of times to check that Main OSC clock is stable */
#define	MCU_WAIT_PLL_STABLE_TIME_1_2_PLL	( (uint32)50U )									/* Wait for PLL stabilization (100us) with 1/2 PLL (200MHz) */
#define	MCU_WAIT_PLL_STABLE_TIME		( (uint32)100U )									/* Wait for PLL stabilization (100us) with 1/1 PLL (400MHz) */

#define	MCU_LSINTOSC_CLOCK				( (uint32)240U )									/* LS intOSC clock frequency */

#define	MCU_PLLS_MASK					( CLOCK_PLLS_PLLCLKEN + CLOCK_PLLS_PLLCLKSTAB )
#define	MCU_MOSCS_MASK					( CLOCK_MOSCS_MOSCEN + CLOCK_MOSCS_MOSCSTAB )

#define	MCU_CLMATEST_DISABLE			( (uint32)0x00000000U )								/* Disable CLMA Reset */

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
#define	MCU_CLMATEST_ENABLE				( ( MCU_CFG_CLMA0CLME * BIT3 ) + ( MCU_CFG_CLMA1CLME * BIT4 ) + ( MCU_CFG_CLMA2CLME * BIT5 )		\
										+ ( MCU_CFG_CLMA3CLME * BIT6 ) + ( MCU_CFG_CLMA5CLME * BIT8 ) + ( MCU_CFG_CLMA6CLME * BIT9 )		\
										+ ( MCU_CFG_CLMA7CLME * BIT10 ) + ( MCU_CFG_CLMA8CLME * BIT11 ) + ( MCU_CFG_CLMA9CLME * BIT12 ) )	/* Enabled clock monitor */

#elif ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
#define	MCU_CLMATEST_ENABLE				( ( MCU_CFG_CLMA0CLME * BIT3 ) + ( MCU_CFG_CLMA1CLME * BIT4 ) + ( MCU_CFG_CLMA2CLME * BIT5 )		\
										+ ( MCU_CFG_CLMA3CLME * BIT6 ) + ( MCU_CFG_CLMA5CLME * BIT8 ) + ( MCU_CFG_CLMA6CLME * BIT9 )		\
										+ ( MCU_CFG_CLMA7CLME * BIT10 ) + ( MCU_CFG_CLMA13CLME * BIT16 ) + ( MCU_CFG_CLMA14CLME * BIT17 )	\
										+ ( MCU_CFG_CLMA15CLME * BIT18 ) + ( MCU_CFG_CLMA16CLME * BIT19 ) + ( MCU_CFG_CLMA17CLME * BIT20 ) )/* Enabled clock monitor */
#endif

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )

#if	( ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A16_516PIN ) || ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A16_373PIN ) )
#define	MCU_CLMATEST_ENABLE_ISO			( (uint32)( ( MCU_CFG_CLMA3CLME * BIT6 ) + ( MCU_CFG_CLMA5CLME * BIT8 ) + ( MCU_CFG_CLMA6CLME * BIT9 )		\
												  + ( MCU_CFG_CLMA7CLME * BIT10 ) + ( MCU_CFG_CLMA8CLME * BIT11 ) + ( MCU_CFG_CLMA9CLME * BIT12 ) ) )/* Enabled clock monitor in ISO area */

#else
#define	MCU_CLMATEST_ENABLE_ISO			( (uint32)( ( MCU_CFG_CLMA3CLME * BIT6 ) + ( MCU_CFG_CLMA5CLME * BIT8 ) + ( MCU_CFG_CLMA6CLME * BIT9 )		\
												  + ( MCU_CFG_CLMA7CLME * BIT10 ) ) )														/* Enabled clock monitor in ISO area */

#endif	/* ( ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A16_516PIN ) || ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A16_373PIN ) ) */

#elif ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
#define	MCU_CLMATEST_ENABLE_ISO			( (uint32)( ( MCU_CFG_CLMA3CLME * BIT6 ) + ( MCU_CFG_CLMA5CLME * BIT8 ) + ( MCU_CFG_CLMA6CLME * BIT9 )		\
												  + ( MCU_CFG_CLMA7CLME * BIT10 ) + ( MCU_CFG_CLMA13CLME * BIT16 ) + ( MCU_CFG_CLMA14CLME * BIT17 )	\
												  + ( MCU_CFG_CLMA15CLME * BIT18 ) + ( MCU_CFG_CLMA16CLME * BIT19 ) + ( MCU_CFG_CLMA17CLME * BIT20 ) ) )/* Enabled clock monitor in ISO area */
#endif

#define	MCU_CLMATEST_CLMA3TESEN			( (uint32)( MCU_CFG_CLMA3CLME * BIT6 ) )			/* CLMA3 self-test enable */
#define	MCU_CLMATEST_ERRMSK3			( (uint32)( ( MCU_CFG_CLMA3CLME * BIT6 ) + BIT2 ) )	/* Mask the error notification */
#define	MCU_CLMATEST_RESET3				( (uint32)( MCU_CLMATEST_ERRMSK3 + BIT0 ) )			/* Reset clock nonitor */
#define	MCU_CLMATEST_RELEASE_RESET3		( (uint32)( MCU_CLMATEST_ERRMSK3 ) )				/* Release clock monitor reset */
#define	MCU_CLMATEST_RELEASE_MASK3		( (uint32)( MCU_CFG_CLMA3CLME * BIT6 ) )			/* Release mask of the error notification */

#define	MCU_CLMATEST_ERRMSK_ISO			( (uint32)( MCU_CLMATEST_ENABLE_ISO + BIT2 ) )		/* Mask the error notification in ISO area */
#define	MCU_CLMATEST_RESET_ISO			( (uint32)( MCU_CLMATEST_ERRMSK_ISO + BIT0 ) )		/* Reset clock nonitor in ISO area */
#define	MCU_CLMATEST_RELEASE_RESET_ISO	( (uint32)( MCU_CLMATEST_ENABLE_ISO + BIT2 ) )		/* Release clock monitor reset in ISO area */
#define	MCU_CLMATEST_RELEASE_MASK_ISO	( (uint32)( MCU_CLMATEST_ENABLE_ISO ) )				/* Release mask of the error notification in ISO area */

#define	MCU_CLMA_TIMER					( (uint32)3 )										/* 2 cycles of sampling clock for CLMA */

#define	MCU_ERROR51_BITPOS				( (uint32)0x00080000 )								/* CLMA3 ECM error number bit position */

#define	MCU_TIMEOUT_COUNT_MOSC_STABLE	( (sint32)116000 )									/* MainOSC oscillation stabilization time 10ms */
#define	MCU_PROCESS_TIME_OUT_OTHER		( (sint32)4000 )									/* Timeout count for confirm completion of setting */
#define	MCU_PROCESS_TIME_OUT_PERI		( (sint32)1000 )
#define	MCU_PROCESS_TIME_OUT_POST_PERI	( (sint32)3000 )
#define	MCU_PROCESS_TIME_OUT_PRE_FOUT	( (sint32)87000 )
#define	MCU_PROCESS_TIME_OUT_POST_FOUT	( (sint32)173000 )

#define	MCU_ISOVDD_STBL_TIME_MIN		( 4U )					/* Minimum recovery time from DeepSTOP mode */
#define	MCU_ISOVDD_STBL_TIME_MAX		( 17067U )				/* Maximum recovery time from DeepSTOP mode */
#define	MCU_PWRGD_CNT_SETTING			( ( ( (uint32)MCU_CFG_ISOVDD_STBL_TIME * MCU_LSINTOSC_CLOCK ) / (uint32)1000 ) - (uint32)1 )

#define	MCU_MULTIPLE_RESET_NUM			( (sint32)2 )										/* Number of multiple resets */

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
#define	MCU_NUM_RESET_REASON			( (sint32)14 )										/* Number of reset factors */

#elif ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
#define	MCU_NUM_RESET_REASON			( (sint32)15 )										/* Number of reset factors */
#endif

#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
#define MCU_NUM_CLK_REG_SET_TBL			( 10U )
#elif ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
#define MCU_NUM_CLK_REG_SET_TBL			( 5U )
#endif

#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
#define MCU_NUM_CLK_SLEEP_REG_SET_TBL	( 6U )
#endif

#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
#define MCU_NUM_MSR_REG_SET_TBL			( 27U )
#elif ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
#define MCU_NUM_MSR_REG_SET_TBL			( 23U )
#endif

#define MCU_CLK_REG_SET_TIMEOUT_CNT_PERI		( (sint32)0x000003E8 )
#define MCU_CLK_REG_SET_TIMEOUT_CNT_PRE_PERI	( (sint32)0x000007D0 )
#define MCU_CLK_REG_SET_TIMEOUT_CNT_POST_PERI	( (sint32)0x00000BB8 )
#define MCU_CLK_REG_SET_TIMEOUT_CNT_PRE_WDT		( (sint32)0x00001770 )
#define MCU_CLK_REG_SET_TIMEOUT_CNT_POST_WDT	( (sint32)0x00002AF8 )
#define MCU_CLK_REG_SET_TIMEOUT_CNT_PRE_AWDTB	( (sint32)0x000FE268 )
#define MCU_CLK_REG_SET_TIMEOUT_CNT_POST_AWDTB	( (sint32)0x001FC0E8 )
#define MCU_CLK_REG_SET_TIMEOUT_CNT_PRE_SWDT	( (sint32)0x00003E80 )

#define	MCU_TIMEOUT_COUNT_REG_REFRESH	( (sint32)0x0000FFFF )

/* Register enable bit mask */
#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
#define MCU_ENABLE_BIT_MASK_MSR_RTCA		( MSR_RTCA_MS_RTCA_0 + MSR_RTCA_STPMSK_RTCA )
#define MCU_ENABLE_BIT_MASK_MSR_RSCFD		( MSR_RSCFD_MS_RSCFD_0 + MSR_RSCFD_MS_RSCFD_1 + MSR_RSCFD_STPMSK_RSCFD )
#define MCU_ENABLE_BIT_MASK_MSR_GTM			( MSR_GTM_MS_GTM_0 )
#define MCU_ENABLE_BIT_MASK_MSR_MSPI		( MSR_MSPI_MS_MSPI_0 + MSR_MSPI_MS_MSPI_1 + MSR_MSPI_MS_MSPI_2 + MSR_MSPI_MS_MSPI_3 + MSR_MSPI_MS_MSPI_4	\
											+ MSR_MSPI_MS_MSPI_5 + MSR_MSPI_MS_MSPI_6 + MSR_MSPI_MS_MSPI_7 + MSR_MSPI_MS_MSPI_8 + MSR_MSPI_MS_MSPI_9 )
#define MCU_ENABLE_BIT_MASK_MSR_RLIN3		( MSR_RLIN3_MS_RLIN3_0 + MSR_RLIN3_MS_RLIN3_1 + MSR_RLIN3_MS_RLIN3_2 + MSR_RLIN3_MS_RLIN3_3 + MSR_RLIN3_MS_RLIN3_4		\
											+ MSR_RLIN3_MS_RLIN3_5 + MSR_RLIN3_MS_RLIN3_6 + MSR_RLIN3_MS_RLIN3_7 + MSR_RLIN3_MS_RLIN3_8 + MSR_RLIN3_MS_RLIN3_9		\
											+ MSR_RLIN3_MS_RLIN3_10 + MSR_RLIN3_MS_RLIN3_11 + MSR_RLIN3_MS_RLIN3_12 + MSR_RLIN3_MS_RLIN3_13 + MSR_RLIN3_MS_RLIN3_14	\
											+ MSR_RLIN3_MS_RLIN3_15 + MSR_RLIN3_MS_RLIN3_16 + MSR_RLIN3_MS_RLIN3_17 + MSR_RLIN3_MS_RLIN3_18 + MSR_RLIN3_MS_RLIN3_19	\
											+ MSR_RLIN3_MS_RLIN3_20 + MSR_RLIN3_MS_RLIN3_21 + MSR_RLIN3_MS_RLIN3_22 + MSR_RLIN3_MS_RLIN3_23 + MSR_RLIN3_STPMSK_RLIN3 )
#define MCU_ENABLE_BIT_MASK_MSR_MMCA		( MSR_MMCA_MS_MMCA_0 )
#define MCU_ENABLE_BIT_MASK_MSR_ENCA		( MSR_ENCA_MS_ENCA_0 + MSR_ENCA_MS_ENCA_1 )
#define MCU_ENABLE_BIT_MASK_MSR_PSI5S		( MSR_PSI5S_MS_PSI5S_0 + MSR_PSI5S_MS_PSI5S_1 )
#define MCU_ENABLE_BIT_MASK_MSR_RIIC		( MSR_RIIC_MS_RIIC_0 + MSR_RIIC_MS_RIIC_1 )
#define MCU_ENABLE_BIT_MASK_MSR_TPBA 		( MSR_TPBA_MS_TPBA_0 + MSR_TPBA_MS_TPBA_1 )
#define MCU_ENABLE_BIT_MASK_MSR_TAUJ_AWO	( MSR_TAUJ_AWO_MS_TAUJ_2 + MSR_TAUJ_AWO_MS_TAUJ_3 + MSR_TAUJ_AWO_STPMSK_TAUJ_AWO )
#define MCU_ENABLE_BIT_MASK_MSR_RSENT		( MSR_RSENT_MS_RSENT_0 + MSR_RSENT_MS_RSENT_1 + MSR_RSENT_MS_RSENT_2 + MSR_RSENT_MS_RSENT_3 + MSR_RSENT_MS_RSENT_4	\
											+ MSR_RSENT_MS_RSENT_5 + MSR_RSENT_MS_RSENT_6 + MSR_RSENT_MS_RSENT_7 )
#define MCU_ENABLE_BIT_MASK_MSR_WDTB_AWO	( MSR_WDTB_AWO_STPMSK_WDTB_AWO )
#define MCU_ENABLE_BIT_MASK_MSR_FLXA		( MSR_FLXA_MS_FLXA_0 + MSR_FLXA_MS_FLXA_1 )
#define MCU_ENABLE_BIT_MASK_MSR_ETNB		( MSR_ETNB_MS_ETNB_0 + MSR_ETNB_MS_ETNB_1 )
#define MCU_ENABLE_BIT_MASK_MSR_ADCJ_ISO	( MSR_ADCJ_ISO_MS_ADCJ_0 + MSR_ADCJ_ISO_MS_ADCJ_1 )
#define MCU_ENABLE_BIT_MASK_MSR_CXPI		( MSR_CXPI_MS_CXPI_0 + MSR_CXPI_MS_CXPI_1 + MSR_CXPI_MS_CXPI_2 + MSR_CXPI_MS_CXPI_3 )
#define MCU_ENABLE_BIT_MASK_MSR_PSI5		( MSR_PSI5_MS_PSI5_0 + MSR_PSI5_MS_PSI5_1 + MSR_PSI5_MS_PSI5_2 + MSR_PSI5_MS_PSI5_3 )
#define MCU_ENABLE_BIT_MASK_MSR_PWMD		( MSR_PWMD_MS_PWMD_0 )
#define MCU_ENABLE_BIT_MASK_MSR_RHSIF		( MSR_RHSIF_MS_RHSIF_0 )
#define MCU_ENABLE_BIT_MASK_MSR_SCI3		( MSR_SCI3_MS_SCI3_0 + MSR_SCI3_MS_SCI3_1 + MSR_SCI3_MS_SCI3_2 )
#define MCU_ENABLE_BIT_MASK_MSR_TAPA		( MSR_TAPA_MS_TAPA_0 + MSR_TAPA_MS_TAPA_1 + MSR_TAPA_MS_TAPA_2 + MSR_TAPA_MS_TAPA_3 )
#define MCU_ENABLE_BIT_MASK_MSR_TAUD		( MSR_TAUD_MS_TAUD_0 + MSR_TAUD_MS_TAUD_1 + MSR_TAUD_MS_TAUD_2 )
#define MCU_ENABLE_BIT_MASK_MSR_TAUJ_ISO	( MSR_TAUJ_ISO_MS_TAUJ_0 + MSR_TAUJ_ISO_MS_TAUJ_1 )
#define MCU_ENABLE_BIT_MASK_MSR_TSG3		( MSR_TSG3_MS_TSG3_0 + MSR_TSG3_MS_TSG3_1 )
#define MCU_ENABLE_BIT_MASK_MSR_OSTM		( MSR_OSTM_MS_OSTM_0 + MSR_OSTM_MS_OSTM_1 + MSR_OSTM_MS_OSTM_2 + MSR_OSTM_MS_OSTM_3 + MSR_OSTM_MS_OSTM_4	\
											+ MSR_OSTM_MS_OSTM_5 + MSR_OSTM_MS_OSTM_6 + MSR_OSTM_MS_OSTM_7 + MSR_OSTM_MS_OSTM_8 + MSR_OSTM_MS_OSTM_9 )
#define MCU_ENABLE_BIT_MASK_MSR_ADCJ_AWO	( MSR_ADCJ_AWO_MS_ADCJ_2 + MSR_ADCJ_AWO_STPMSK_ADCJ	)

#elif ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
#define MCU_ENABLE_BIT_MASK_MSR_RSCFD		( MSR_RSCFD_MS_RSCFD_0 + MSR_RSCFD_MS_RSCFD_1 )
#define MCU_ENABLE_BIT_MASK_MSR_GTM			( MSR_GTM_MS_GTM_0 )
#define MCU_ENABLE_BIT_MASK_MSR_MSPI		( MSR_MSPI_MS_MSPI_0 + MSR_MSPI_MS_MSPI_1 + MSR_MSPI_MS_MSPI_2 + MSR_MSPI_MS_MSPI_3 + MSR_MSPI_MS_MSPI_4	\
											+ MSR_MSPI_MS_MSPI_5 + MSR_MSPI_MS_MSPI_6 + MSR_MSPI_MS_MSPI_7 + MSR_MSPI_MS_MSPI_8 + MSR_MSPI_MS_MSPI_9 )
#define MCU_ENABLE_BIT_MASK_MSR_RLIN3		( MSR_RLIN3_MS_RLIN3_0 + MSR_RLIN3_MS_RLIN3_1 + MSR_RLIN3_MS_RLIN3_2 + MSR_RLIN3_MS_RLIN3_3 + MSR_RLIN3_MS_RLIN3_4		\
											+ MSR_RLIN3_MS_RLIN3_5 + MSR_RLIN3_MS_RLIN3_6 + MSR_RLIN3_MS_RLIN3_7 + MSR_RLIN3_MS_RLIN3_8 + MSR_RLIN3_MS_RLIN3_9		\
											+ MSR_RLIN3_MS_RLIN3_10 + MSR_RLIN3_MS_RLIN3_11 + MSR_RLIN3_MS_RLIN3_12 + MSR_RLIN3_MS_RLIN3_13 + MSR_RLIN3_MS_RLIN3_14	\
											+ MSR_RLIN3_MS_RLIN3_15 + MSR_RLIN3_MS_RLIN3_16 + MSR_RLIN3_MS_RLIN3_17 + MSR_RLIN3_MS_RLIN3_18 + MSR_RLIN3_MS_RLIN3_19	\
											+ MSR_RLIN3_MS_RLIN3_20 + MSR_RLIN3_MS_RLIN3_21 + MSR_RLIN3_MS_RLIN3_22 + MSR_RLIN3_MS_RLIN3_23 )
#define MCU_ENABLE_BIT_MASK_MSR_ENCA		( MSR_ENCA_MS_ENCA_0 + MSR_ENCA_MS_ENCA_1 )
#define MCU_ENABLE_BIT_MASK_MSR_TPBA 		( MSR_TPBA_MS_TPBA_0 + MSR_TPBA_MS_TPBA_1 )
#define MCU_ENABLE_BIT_MASK_MSR_FLXA		( MSR_FLXA_MS_FLXA_0 )
#define MCU_ENABLE_BIT_MASK_MSR_ETN			( MSR_ETN_MS_ETN_0 + MSR_ETN_MS_ETN_1 + MSR_ETN_MS_ETN_2 )
#define MCU_ENABLE_BIT_MASK_MSR_RSENT		( MSR_RSENT_MS_RSENT_0 + MSR_RSENT_MS_RSENT_1 + MSR_RSENT_MS_RSENT_2 + MSR_RSENT_MS_RSENT_3 + MSR_RSENT_MS_RSENT_4		\
											+ MSR_RSENT_MS_RSENT_5 + MSR_RSENT_MS_RSENT_6 + MSR_RSENT_MS_RSENT_7 + MSR_RSENT_MS_RSENT_8 + MSR_RSENT_MS_RSENT_9		\
											+ MSR_RSENT_MS_RSENT_10 + MSR_RSENT_MS_RSENT_11 + MSR_RSENT_MS_RSENT_12 + MSR_RSENT_MS_RSENT_13 + MSR_RSENT_MS_RSENT_14	\
											+ MSR_RSENT_MS_RSENT_15 + MSR_RSENT_MS_RSENT_16 + MSR_RSENT_MS_RSENT_17 + MSR_RSENT_MS_RSENT_18 + MSR_RSENT_MS_RSENT_19	\
											+ MSR_RSENT_MS_RSENT_20 + MSR_RSENT_MS_RSENT_21 + MSR_RSENT_MS_RSENT_22 + MSR_RSENT_MS_RSENT_23 + MSR_RSENT_MS_RSENT_24	\
											+ MSR_RSENT_MS_RSENT_25 + MSR_RSENT_MS_RSENT_26 + MSR_RSENT_MS_RSENT_27 + MSR_RSENT_MS_RSENT_28 + MSR_RSENT_MS_RSENT_29 )
#define MCU_ENABLE_BIT_MASK_MSR_DSADC_CADC	( MSR_DSADC_CADC_MS_DSADC_0 + MSR_DSADC_CADC_MS_DSADC_1 + MSR_DSADC_CADC_MS_DSADC_2 + MSR_DSADC_CADC_MS_DSADC_3	)
#define MCU_ENABLE_BIT_MASK_MSR_ADCK_ISO	( MSR_ADCK_ISO_MS_ADCK_ISO_0 + MSR_ADCK_ISO_MS_ADCK_ISO_1 + MSR_ADCK_ISO_MS_ADCK_ISO_2 + MSR_ADCK_ISO_MS_ADCK_ISO_3	\
											+ MSR_ADCK_ISO_MS_ADCK_ISO_4 + MSR_ADCK_ISO_MS_ADCK_ISO_5 + MSR_ADCK_ISO_MS_ADCK_ISO_6 + MSR_ADCK_ISO_MS_ADCK_ISO_7	)
#define MCU_ENABLE_BIT_MASK_MSR_RHSIF		( MSR_RHSIF_MS_RHSIF_0 + MSR_RHSIF_MS_RHSIF_1 )
#define MCU_ENABLE_BIT_MASK_MSR_RHSB		( MSR_RHSB_MS_RHSB_0 + MSR_RHSB_MS_RHSB_1 + MSR_RHSB_MS_RHSB_2 + MSR_RHSB_MS_RHSB_3 )
#define MCU_ENABLE_BIT_MASK_MSR_SFMA		( MSR_SFMA_MS_SFMA_0 )
#define MCU_ENABLE_BIT_MASK_MSR_TAPA		( MSR_TAPA_MS_TAPA_0 + MSR_TAPA_MS_TAPA_1 + MSR_TAPA_MS_TAPA_2 + MSR_TAPA_MS_TAPA_3 + MSR_TAPA_MS_TAPA_4	\
											+ MSR_TAPA_MS_TAPA_5 )
#define MCU_ENABLE_BIT_MASK_MSR_TAUD		( MSR_TAUD_MS_TAUD_0 + MSR_TAUD_MS_TAUD_1 + MSR_TAUD_MS_TAUD_2 + MSR_TAUD_MS_TAUD_3 )
#define MCU_ENABLE_BIT_MASK_MSR_TSG3		( MSR_TSG3_MS_TSG3_0 + MSR_TSG3_MS_TSG3_1 + MSR_TSG3_MS_TSG3_2 )
#define MCU_ENABLE_BIT_MASK_MSR_OSTM		( MSR_OSTM_MS_OSTM_0 + MSR_OSTM_MS_OSTM_1 + MSR_OSTM_MS_OSTM_2 + MSR_OSTM_MS_OSTM_3 + MSR_OSTM_MS_OSTM_4	\
											+ MSR_OSTM_MS_OSTM_5 )
#define MCU_ENABLE_BIT_MASK_MSR_DFE			( MSR_DFE_MS_DFE_0 )
#define MCU_ENABLE_BIT_MASK_MSR_RDC			( MSR_RDC_MS_RDC_0 + MSR_RDC_MS_RDC_1 + MSR_RDC_MS_RDC_2 + MSR_RDC_MS_RDC_3 )
#define MCU_ENABLE_BIT_MASK_MSR_FCOMP		( MSR_FCOMP_MS_FCOMP_0 + MSR_FCOMP_MS_FCOMP_1 + MSR_FCOMP_MS_FCOMP_2 + MSR_FCOMP_MS_FCOMP_3 + MSR_FCOMP_MS_FCOMP_4	\
											+ MSR_FCOMP_MS_FCOMP_5 + MSR_FCOMP_MS_FCOMP_6 + MSR_FCOMP_MS_FCOMP_7 + MSR_FCOMP_MS_FCOMP_8 + MSR_FCOMP_MS_FCOMP_9	\
											+ MSR_FCOMP_MS_FCOMP_10 )
#define MCU_ENABLE_BIT_MASK_MSR_EMU			( MSR_EMU_MS_EMU_0 + MSR_EMU_MS_EMU_1 )
#define MCU_ENABLE_BIT_MASK_MSR_HRPWM		( MSR_HRPWM_MS_HRPWM_0 )

#endif /* MCAL_SPAL_TARGET */

#define MCU_SSCGC_REGCHK_EXPECTED_VALUE	( ( CLOCK_SSCGC_SSMODE1_ENABLE * CLOCK_SSCGC_SSMODE1 )				\
										+ ( MCU_CFG_CLK_SSCG_FREQ_TYPE_0 * CLOCK_SSCGC_SELMFREQ_0 )			\
										+ ( MCU_CFG_CLK_SSCG_PERCENT_TYPE_0 * CLOCK_SSCGC_SELMPERCENT_0 ) )
#define MCU_ENABLE_BIT_MASK_SSCGC		( CLOCK_SSCGC_SSMODE1 + CLOCK_SSCGC_SELMFREQ + CLOCK_SSCGC_SELMPERCENT )
#define MCU_REGCHK_RESULT_DUMMY_BIT		( (uint32)BIT31 )	/* Dummy bit for QAC countermeasures */

#define MCU_WAIT_SLEEP_TIMEOUT_UNLIMITED	(0xFFFFFFFFU)
 
#define MCU_CONVERT_WAITTIME_SHIFT_PLLO2	(1U)
#define MCU_CONVERT_WAITTIME_SHIFT_IOSC		(2U)

typedef struct {
	volatile uint32*	pu4ControlReg;	/* Control Register Address */
	volatile uint32*	pu4StatusReg;	/* Status Register Address */
	uint32				u4SetValue;		/* Setting Register Value */
	sint32				s4TimeoutCnt;	/* Timeout count for confirm completion of register setting */
	uint32				u4RegMask;		/* Register Mask Value */
} Mcu_ClockRegisterSettingType;

typedef struct {
	volatile uint32*	pu4ControlReg;	/* Control Register Address */
	uint32				u4SetValue;		/* Setting Register Value */
	uint32				u4RegMask;		/* Register Mask Value */
} Mcu_ModuleStandbyRegisterType;

/*==============================================================================================*/
/* prototypes																					*/
/*==============================================================================================*/
#define MCU_START_SEC_CODE_GLOBAL
#include "Mcu_MemMap.h"

#if	( MCU_CFG_RESET_REASON == STD_ON )
static FUNC( void, MCU_CODE ) Mcu_ResetInit( void );
#endif	/* ( MCU_CFG_RESET_REASON == STD_ON ) */

#if	( MCU_CFG_INIT_CLOCK == STD_ON )
static FUNC( Std_ReturnType, MCU_CODE ) Mcu_ClockUpStart( void );
static FUNC( Std_ReturnType, MCU_CODE ) Mcu_ClockSetupPeri( void );
#endif	/* #if	( MCU_CFG_INIT_CLOCK == STD_ON ) */

#if	( MCU_CFG_NO_PLL == FALSE )
static FUNC( Std_ReturnType, MCU_CODE ) Mcu_ClockDistributePll( void );
static FUNC( Std_ReturnType, MCU_CODE ) Mcu_ClockSetupFout( void );
static FUNC( Std_ReturnType, MCU_CODE ) Mcu_ClockSupplyPeri( void );
#endif	/* ( MCU_CFG_NO_PLL == FALSE ) */

#if	( MCU_CFG_NO_PLL == FALSE )
static FUNC( Std_ReturnType, MCU_CODE ) Mcu_ClockControlPll( void );

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
static FUNC( Std_ReturnType, MCU_CODE ) Mcu_ClockUpSscg( void );
static FUNC( Std_ReturnType, MCU_CODE ) Mcu_ClockUpPll( void );
#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B ) */
#endif	/* ( MCU_CFG_NO_PLL == FALSE ) */

#if	( MCU_CFG_CLK_MONITOR == STD_ON )

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
#if	( MCU_CFG_CLMA3CLME == STD_ON )
static FUNC( void, MCU_CODE ) Mcu_ClockMonitorReset( void );
#endif	/* ( MCU_CFG_CLMA3CLME == STD_ON ) */
#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) */

static FUNC( Std_ReturnType, MCU_CODE ) Mcu_ClockMonitorSetup( void );
#endif	/* ( MCU_CFG_CLK_MONITOR == STD_ON ) */

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )

#if	( MCU_CFG_CLK_MONITOR == STD_ON )
static FUNC( void, MCU_CODE ) Mcu_ClockMonitorStandby( void );
#endif	/* ( MCU_CFG_CLK_MONITOR == STD_ON ) */

static FUNC( Std_ReturnType, MCU_CODE ) Mcu_StandbyClockDown( void );
static FUNC( Std_ReturnType, MCU_CODE ) Mcu_StandbyPeri( void );
static FUNC( Std_ReturnType, MCU_CODE ) Mcu_StandbyFout( void );
static FUNC( Std_ReturnType, MCU_CODE ) Mcu_StandbySetPwrgdCnt( void );
#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) */

#if	( ( ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B ) && ( ( MCU_CFG_INIT_CLOCK == STD_ON ) || ( ( MCU_CFG_REG_CHK == STD_ON ) && ( MCU_CFG_REG_REFRESH == STD_ON ) ) ) ) ||	\
	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) )
static FUNC( Std_ReturnType, MCU_CODE ) Mcu_SetClockRegister
	( volatile uint32* t_pu4ControlReg, const volatile uint32* t_pu4StatusReg, const uint32 t_u4SetValue, const sint32 t_s4TimeoutCnt );
#endif

#if	( ( ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B ) && ( ( MCU_CFG_INIT_CLOCK == STD_ON ) || ( MCU_CFG_NO_PLL == FALSE ) ) ) || ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) )
static FUNC( Std_ReturnType, MCU_CODE ) Mcu_ProcessTimeOut
	( volatile uint32* t_pu4StatusReg, uint32 t_u4RegMask, const uint32 t_u4StatusValue, const sint32 t_s4TimeoutCnt );
#endif	/* ( ( ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B ) && ( ( MCU_CFG_INIT_CLOCK == STD_ON ) || ( MCU_CFG_NO_PLL == FALSE ) ) ) || ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) ) */

#if ( MCU_CFG_REG_CHK == STD_ON )
static FUNC( uint32, MCU_CODE ) Mcu_Regchk_ClockRegister( volatile uint32* t_pu4ControlReg, const volatile uint32* t_pu4StatusReg, const uint32 t_u4ExpectValue, const uint32 t_u4RegMask );
static FUNC( uint32, MCU_CODE ) Mcu_Regchk_u4ForRefreshPossible( volatile uint32* t_pu4Register, const uint32 t_u4ExpectValue , const uint32 t_u4RegMask );
static FUNC( uint32, MCU_CODE ) Mcu_Regchk_u4ForRefreshImpossible( volatile uint32* t_pu4Register, const uint32 t_u4ExpectValue , const uint32 t_u4RegMask );
static FUNC( uint32, MCU_CODE ) Mcu_Regchk_ClkCtrl( void );
#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
static FUNC( uint32, MCU_CODE ) Mcu_Regchk_Fout( void );
static FUNC( uint32, MCU_CODE ) Mcu_Regchk_Fout0Clkd( void );
static FUNC( uint32, MCU_CODE ) Mcu_Regchk_Fout1Clkd( void );
#endif
#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
static FUNC( uint32, MCU_CODE ) Mcu_Regchk_Extclk( void );
static FUNC( uint32, MCU_CODE ) Mcu_Regchk_Extclk0Clkd( void );
static FUNC( uint32, MCU_CODE ) Mcu_Regchk_Extclk1Clkd( void );
#endif
#if ( MCU_CFG_CLK_MONITOR == STD_ON )
static FUNC( uint32, MCU_CODE ) Mcu_Regchk_Clma( void );
static FUNC( uint32, MCU_CODE ) Mcu_Regchk_u1ForRefreshPossible( volatile uint8* t_pu1Register, const uint8 t_u1ExpectValue , const uint8 t_u1RegMask );
static FUNC( uint32, MCU_CODE ) Mcu_Regchk_u2ForRefreshPossible( volatile uint16* t_pu2Register, const uint16 t_u2ExpectValue , const uint16 t_u2RegMask );
#endif
#endif	/* MCU_CFG_REG_CHK == STD_ON */

#define MCU_STOP_SEC_CODE_GLOBAL
#include "Mcu_MemMap.h"

/*==============================================================================================*/
/* constants																					*/
/*==============================================================================================*/
#define MCU_START_SEC_CONST_UNSPECIFIED
#include "Mcu_MemMap.h"

#if	( MCU_CFG_RESET_REASON == STD_ON )
static const stMcu_ResetReason stMcu_ResetReasonTbl[ MCU_NUM_RESET_REASON ] = {
	{ (uint32)MCU_RESF_POWER_ON_RESET, MCU_POWER_ON_RESET },							/* Power On Reset */

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
	{ (uint32)MCU_RESF_POWER_OFF_STANDBY_RESET, MCU_POWER_OFF_STANDBY_RESET },			/* Power Off Standby Reset */
#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B ) */

	{ (uint32)MCU_RESF_EXTERNAL_RESET, MCU_EXTERNAL_RESET },							/* External Reset */
	{ (uint32)MCU_RESF_PRIMARY_VMON_RESET, MCU_PRIMARY_VMON_RESET },					/* Primary VMON Reset */
	{ (uint32)MCU_RESF_SOFTWARE_SYSTEM_RESET, MCU_SOFTWARE_SYSTEM_RESET },				/* Software System Reset */
	{ (uint32)MCU_RESF_ECM_SYSTEM_RESET_2, MCU_ECM_SYSTEM_RESET_2 },					/* ECM System Reset 2 */
	{ (uint32)MCU_RESF_WDTBA_RESET, MCU_WDTBA_RESET },									/* WDTBA Reset */
	{ (uint32)MCU_RESF_SOFTWARE_APPLICATION_RESET, MCU_SOFTWARE_APPLICATION_RESET },	/* Software Application Reset */
	{ (uint32)MCU_RESF_ECM_APPLICATION_RESET, MCU_ECM_APPLICATION_RESET },				/* ECM Application Reset */
	{ (uint32)MCU_RESF_HW_BIST0_EXECUTION_RESET, MCU_HW_BIST0_EXECUTION_RESET },		/* HW BIST0 Execution Reset */
	{ (uint32)MCU_RESF_HW_BIST1_EXECUTION_RESET, MCU_HW_BIST1_EXECUTION_RESET },		/* HW BIST1 Execution Reset */
	{ (uint32)MCU_RESF_HW_BIST2_EXECUTION_RESET, MCU_HW_BIST2_EXECUTION_RESET },		/* HW BIST2 Execution Reset */
	{ (uint32)MCU_RESF_DEEPSTOP_RESET	, MCU_DEEPSTOP_RESET },							/* DeepSTOP Reset */

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
	{ (uint32)MCU_RESF_ICUMHA_SOFT_SYS_RESET, MCU_ICUMHA_SOFT_SYS_RESET },				/* ICUM Software System Reset for RH850U2A */
	{ (uint32)MCU_RESF_ICUMHA_SOFT_APP_RESET, MCU_ICUMHA_SOFT_APP_RESET }				/* ICUM Software Application Reset for RH850U2A */
#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) */

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
	{ (uint32)MCU_RESF_ICUMHB_SOFT_SYS_RESET, MCU_ICUMHB_SOFT_SYS_RESET },				/* ICUM Software System Reset for RH850U2B */
	{ (uint32)MCU_RESF_ICUMHB_SOFT_APP_RESET, MCU_ICUMHB_SOFT_APP_RESET }				/* ICUM Software Application Reset for RH850U2B */
#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B ) */

};
#endif	/* ( MCU_CFG_RESET_REASON == STD_ON ) */

static const Mcu_ClockRegisterSettingType stMcu_ClockRegisterSettingTbl[ MCU_NUM_CLK_REG_SET_TBL ] = {

#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
	{	&REG_CLOCK_ISO.u4CKSC_RLINC,	&REG_CLOCK_ISO.u4CKSC_RLINS,	(uint32)MCU_CFG_CLK_RLIN_TYPE_0,		MCU_CLK_REG_SET_TIMEOUT_CNT_PERI,			CLOCK_CKSC_RLINS_RLINSACT	},
	{	&REG_CLOCK_ISO.u4CKSC_RCANC,	&REG_CLOCK_ISO.u4CKSC_RCANS,	(uint32)MCU_CFG_CLK_RCAN_TYPE_0,		MCU_CLK_REG_SET_TIMEOUT_CNT_PERI,			CLOCK_CKSC_RCANS_RCANSACT	},
	{	&REG_CLOCK_ISO.u4CKSC_ADCC,		&REG_CLOCK_ISO.u4CKSC_ADCS,		(uint32)MCU_CFG_CLK_ADCJ_TYPE_0,		MCU_CLK_REG_SET_TIMEOUT_CNT_PERI,			CLOCK_CKSC_ADCS_ADCSACT		},
	{	&REG_CLOCK_ISO.u4CKSC_MSPIC,	&REG_CLOCK_ISO.u4CKSC_MSPIS,	(uint32)MCU_CFG_CLK_MSPI_A_TYPE_0,		MCU_CLK_REG_SET_TIMEOUT_CNT_PERI,			CLOCK_CKSC_MSPIS_MSPISACT	},
	{	&REG_CLOCK_AWO.u4CKSC_AWDTC,	&REG_CLOCK_AWO.u4CKSC_AWDTS,	(uint32)MCU_CFG_CLK_WDTBA_A_TYPE_0,		MCU_CLK_REG_SET_TIMEOUT_CNT_PRE_AWDTB,		CLOCK_CKSC_AWDTS_AWDTSACT	},
	{	&REG_CLOCK_AWO.u4CKSC_ATAUJC,	&REG_CLOCK_AWO.u4CKSC_ATAUJS,	(uint32)MCU_CFG_CLK_ATAUJC_A_TYPE_0,	MCU_CLK_REG_SET_TIMEOUT_CNT_PRE_PERI,		CLOCK_CKSC_ATAUJS_ATAUJSACT	},
	{	&REG_CLOCK_AWO.u4CKSC_ARTCAC,	&REG_CLOCK_AWO.u4CKSC_ARTCAS,	(uint32)MCU_CFG_CLK_ARTCAC_A_TYPE_0,	MCU_CLK_REG_SET_TIMEOUT_CNT_PRE_PERI,		CLOCK_CKSC_ARTCAS_ARTCASACT	},
	{	&REG_CLOCK_AWO.u4CKSC_AADCC,	&REG_CLOCK_AWO.u4CKSC_AADCS,	(uint32)MCU_CFG_CLK_AADCC_A_TYPE_0,		MCU_CLK_REG_SET_TIMEOUT_CNT_PERI,			CLOCK_CKSC_AADCS_AADCSACT	},
	{	&REG_CLOCK_AWO.u4CLKD_AADCC,	&REG_CLOCK_AWO.u4CLKD_AADCS,	(uint32)MCU_CFG_CLKD_AADCC_TYPE_0,		MCU_CLK_REG_SET_TIMEOUT_CNT_PERI,			CLOCK_CLKD_AADCS_AADCDACT	},
	{	&REG_CLOCK_AWO.u4CKSC_WDTC,		&REG_CLOCK_AWO.u4CKSC_WDTS,		(uint32)MCU_CFG_CLK_WDTC_A_TYPE_0,		MCU_CLK_REG_SET_TIMEOUT_CNT_PRE_WDT,		CLOCK_CKSC_WDTS_WDTSACT		}

#elif ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
	{	&REG_CLOCK_ISO.u4CKS_RLINC,		&REG_CLOCK_ISO.u4CKS_RLINS,
		(uint32)( ( MCU_CFG_CLK_RLIN3_CH23_TYPE_0 * CLOCK_CKS_RLINC_RLIN23SCSID_0 ) + MCU_CFG_CLK_RLIN3_TYPE_0 ),	MCU_CLK_REG_SET_TIMEOUT_CNT_PERI,
		( CLOCK_CKS_RLINS_RLIN23SACT + CLOCK_CKS_RLINS_RLINSACT )																														},
	{	&REG_CLOCK_ISO.u4CKS_RCANC,		&REG_CLOCK_ISO.u4CKS_RCANS,
		(uint32)( ( MCU_CFG_CLK_CANFD_C_TYPE_0 * CLOCK_CKS_RCANC_RCANCSCSID_0 ) + MCU_CFG_CLK_CANFD_XIN_TYPE_0 ),	MCU_CLK_REG_SET_TIMEOUT_CNT_PERI,
		( CLOCK_CKS_RCANS_RCANCSACT + CLOCK_CKS_RCANS_RCANXINSACT )																														},
	{	&REG_CLOCK_ISO.u4CKS_MSPIC,		&REG_CLOCK_ISO.u4CKS_MSPIS,		(uint32)MCU_CFG_CLK_MSPI_B_TYPE_0,		MCU_CLK_REG_SET_TIMEOUT_CNT_PERI,			CLOCK_CKS_MSPIS_MSPISACT	},
	{	&REG_CLOCK_AWO.u4CKS_WDTC,		&REG_CLOCK_AWO.u4CKS_WDTS,		(uint32)MCU_CFG_CLK_WDTC_B_TYPE_0,		MCU_CLK_REG_SET_TIMEOUT_CNT_PRE_WDT,		CLOCK_CKS_WDTS_WDTSACT		},
	{	&REG_CLOCK_ISO.u4CKS_SWDTC,		&REG_CLOCK_ISO.u4CKS_SWDTS,		(uint32)MCU_CFG_CLK_SWDT_TYPE_0,		MCU_CLK_REG_SET_TIMEOUT_CNT_PRE_SWDT,		CLOCK_CKS_SWDTS_SWDTSACT	}
#endif

};

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
static const Mcu_ClockRegisterSettingType stMcu_SleepClockRegisterSettingTbl[ MCU_NUM_CLK_SLEEP_REG_SET_TBL ] = {
	{	&REG_CLOCK_AWO.u4CKSC_AWDTC,	&REG_CLOCK_AWO.u4CKSC_AWDTS,	(uint32)MCU_CFG_CLK_WDTBA_A_SLEEP,		MCU_CLK_REG_SET_TIMEOUT_CNT_POST_AWDTB,		CLOCK_CKSC_AWDTS_AWDTSACT	},
	{	&REG_CLOCK_AWO.u4CKSC_ATAUJC,	&REG_CLOCK_AWO.u4CKSC_ATAUJS,	(uint32)MCU_CFG_CLK_ATAUJC_A_SLEEP,		MCU_CLK_REG_SET_TIMEOUT_CNT_POST_PERI,		CLOCK_CKSC_ATAUJS_ATAUJSACT	},
	{	&REG_CLOCK_AWO.u4CKSC_ARTCAC,	&REG_CLOCK_AWO.u4CKSC_ARTCAS,	(uint32)MCU_CFG_CLK_ARTCAC_A_SLEEP,		MCU_CLK_REG_SET_TIMEOUT_CNT_POST_PERI,		CLOCK_CKSC_ARTCAS_ARTCASACT	},
	{	&REG_CLOCK_AWO.u4CKSC_AADCC,	&REG_CLOCK_AWO.u4CKSC_AADCS,	(uint32)MCU_CFG_CLK_AADCC_A_SLEEP,		MCU_CLK_REG_SET_TIMEOUT_CNT_PERI,			CLOCK_CKSC_AADCS_AADCSACT	},
	{	&REG_CLOCK_AWO.u4CLKD_AADCC,	&REG_CLOCK_AWO.u4CLKD_AADCS,	(uint32)MCU_CFG_CLKD_AADCC_SLEEP,		MCU_CLK_REG_SET_TIMEOUT_CNT_PERI,			CLOCK_CLKD_AADCS_AADCDACT	},
	{	&REG_CLOCK_AWO.u4CKSC_WDTC,		&REG_CLOCK_AWO.u4CKSC_WDTS,		(uint32)MCU_CFG_CLK_WDTC_A_SLEEP,		MCU_CLK_REG_SET_TIMEOUT_CNT_POST_WDT,		CLOCK_CKSC_WDTS_WDTSACT		}
};
#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) */

static const Mcu_ModuleStandbyRegisterType stMcu_ModuleStandbyRegisterSettingTbl[ MCU_NUM_MSR_REG_SET_TBL ] = {

#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
	{	&REG_STBC_AWO.u4MSR_RTCA,		  ( MCU_CFG_MS_RTCA_0_TYPE_0		* MSR_RTCA_MS_RTCA_0 )
										+ ( MCU_CFG_STPMSK_RTCA_TYPE_0		* MSR_RTCA_STPMSK_RTCA )		,
											MCU_ENABLE_BIT_MASK_MSR_RTCA									},

	{	&REG_STBC_ISO.u4MSR_RSCFD,		  ( MCU_CFG_MS_RSCFD_0_TYPE_0		* MSR_RSCFD_MS_RSCFD_0 )
										+ ( MCU_CFG_MS_RSCFD_1_TYPE_0		* MSR_RSCFD_MS_RSCFD_1 )
										+ ( MCU_CFG_STPMSK_RSCFD_TYPE_0		* MSR_RSCFD_STPMSK_RSCFD )		,
											MCU_ENABLE_BIT_MASK_MSR_RSCFD									},

	{	&REG_STBC_ISO.u4MSR_GTM,		  ( MCU_CFG_MS_GTM_0_TYPE_0			* MSR_GTM_MS_GTM_0 )			,
											MCU_ENABLE_BIT_MASK_MSR_GTM										},

	{	&REG_STBC_ISO.u4MSR_MSPI,		  ( MCU_CFG_MS_MSPI_0_TYPE_0		* MSR_MSPI_MS_MSPI_0 )
										+ ( MCU_CFG_MS_MSPI_1_TYPE_0		* MSR_MSPI_MS_MSPI_1 )
										+ ( MCU_CFG_MS_MSPI_2_TYPE_0		* MSR_MSPI_MS_MSPI_2 )
										+ ( MCU_CFG_MS_MSPI_3_TYPE_0		* MSR_MSPI_MS_MSPI_3 )
										+ ( MCU_CFG_MS_MSPI_4_TYPE_0		* MSR_MSPI_MS_MSPI_4 )
										+ ( MCU_CFG_MS_MSPI_5_TYPE_0		* MSR_MSPI_MS_MSPI_5 )
										+ ( MCU_CFG_MS_MSPI_6_TYPE_0		* MSR_MSPI_MS_MSPI_6 )
										+ ( MCU_CFG_MS_MSPI_7_TYPE_0		* MSR_MSPI_MS_MSPI_7 )
										+ ( MCU_CFG_MS_MSPI_8_TYPE_0		* MSR_MSPI_MS_MSPI_8 )
										+ ( MCU_CFG_MS_MSPI_9_TYPE_0		* MSR_MSPI_MS_MSPI_9 )			,
											MCU_ENABLE_BIT_MASK_MSR_MSPI									},

	{	&REG_STBC_ISO.u4MSR_RLIN3,		  ( MCU_CFG_MS_RLIN3_0_TYPE_0		* MSR_RLIN3_MS_RLIN3_0 )
										+ ( MCU_CFG_MS_RLIN3_1_TYPE_0		* MSR_RLIN3_MS_RLIN3_1 )
										+ ( MCU_CFG_MS_RLIN3_2_TYPE_0		* MSR_RLIN3_MS_RLIN3_2 )
										+ ( MCU_CFG_MS_RLIN3_3_TYPE_0		* MSR_RLIN3_MS_RLIN3_3 )
										+ ( MCU_CFG_MS_RLIN3_4_TYPE_0		* MSR_RLIN3_MS_RLIN3_4 )
										+ ( MCU_CFG_MS_RLIN3_5_TYPE_0		* MSR_RLIN3_MS_RLIN3_5 )
										+ ( MCU_CFG_MS_RLIN3_6_TYPE_0		* MSR_RLIN3_MS_RLIN3_6 )
										+ ( MCU_CFG_MS_RLIN3_7_TYPE_0		* MSR_RLIN3_MS_RLIN3_7 )
										+ ( MCU_CFG_MS_RLIN3_8_TYPE_0		* MSR_RLIN3_MS_RLIN3_8 )
										+ ( MCU_CFG_MS_RLIN3_9_TYPE_0		* MSR_RLIN3_MS_RLIN3_9 )
										+ ( MCU_CFG_MS_RLIN3_10_TYPE_0		* MSR_RLIN3_MS_RLIN3_10 )
										+ ( MCU_CFG_MS_RLIN3_11_TYPE_0		* MSR_RLIN3_MS_RLIN3_11 )
										+ ( MCU_CFG_MS_RLIN3_12_TYPE_0		* MSR_RLIN3_MS_RLIN3_12 )
										+ ( MCU_CFG_MS_RLIN3_13_TYPE_0		* MSR_RLIN3_MS_RLIN3_13 )
										+ ( MCU_CFG_MS_RLIN3_14_TYPE_0		* MSR_RLIN3_MS_RLIN3_14 )
										+ ( MCU_CFG_MS_RLIN3_15_TYPE_0		* MSR_RLIN3_MS_RLIN3_15 )
										+ ( MCU_CFG_MS_RLIN3_16_TYPE_0		* MSR_RLIN3_MS_RLIN3_16 )
										+ ( MCU_CFG_MS_RLIN3_17_TYPE_0		* MSR_RLIN3_MS_RLIN3_17 )
										+ ( MCU_CFG_MS_RLIN3_18_TYPE_0		* MSR_RLIN3_MS_RLIN3_18 )
										+ ( MCU_CFG_MS_RLIN3_19_TYPE_0		* MSR_RLIN3_MS_RLIN3_19 )
										+ ( MCU_CFG_MS_RLIN3_20_TYPE_0		* MSR_RLIN3_MS_RLIN3_20 )
										+ ( MCU_CFG_MS_RLIN3_21_TYPE_0		* MSR_RLIN3_MS_RLIN3_21 )
										+ ( MCU_CFG_MS_RLIN3_22_TYPE_0		* MSR_RLIN3_MS_RLIN3_22 )
										+ ( MCU_CFG_MS_RLIN3_23_TYPE_0		* MSR_RLIN3_MS_RLIN3_23 )
										+ ( MCU_CFG_STPMSK_RLIN3_TYPE_0		* MSR_RLIN3_STPMSK_RLIN3 )		,
											MCU_ENABLE_BIT_MASK_MSR_RLIN3									},

	{	&REG_STBC_ISO.u4MSR_MMCA,		  ( MCU_CFG_MS_MMCA_0_TYPE_0		* MSR_MMCA_MS_MMCA_0 )			,
											MCU_ENABLE_BIT_MASK_MSR_MMCA									},

	{	&REG_STBC_ISO.u4MSR_ENCA,		  ( MCU_CFG_MS_ENCA_0_TYPE_0		* MSR_ENCA_MS_ENCA_0 )
										+ ( MCU_CFG_MS_ENCA_1_TYPE_0		* MSR_ENCA_MS_ENCA_1 )			,
											MCU_ENABLE_BIT_MASK_MSR_ENCA									},

	{	&REG_STBC_ISO.u4MSR_PSI5S,		  ( MCU_CFG_MS_PSI5S_0_TYPE_0		* MSR_PSI5S_MS_PSI5S_0 )
										+ ( MCU_CFG_MS_PSI5S_1_TYPE_0		* MSR_PSI5S_MS_PSI5S_1 )		,
											MCU_ENABLE_BIT_MASK_MSR_PSI5S									},

	{	&REG_STBC_ISO.u4MSR_RIIC,		  ( MCU_CFG_MS_RIIC_0_TYPE_0		* MSR_RIIC_MS_RIIC_0 )
										+ ( MCU_CFG_MS_RIIC_1_TYPE_0		* MSR_RIIC_MS_RIIC_1 )			,
											MCU_ENABLE_BIT_MASK_MSR_RIIC									},

	{	&REG_STBC_ISO.u4MSR_TPBA, 		  ( MCU_CFG_MS_TPBA_0_TYPE_0		* MSR_TPBA_MS_TPBA_0 )
										+ ( MCU_CFG_MS_TPBA_1_TYPE_0		* MSR_TPBA_MS_TPBA_1 )			,
											MCU_ENABLE_BIT_MASK_MSR_TPBA									},

	{	&REG_STBC_AWO.u4MSR_TAUJ_AWO,	  ( MCU_CFG_MS_TAUJ_AWO_2_TYPE_0	* MSR_TAUJ_AWO_MS_TAUJ_2 )
										+ ( MCU_CFG_MS_TAUJ_AWO_3_TYPE_0	* MSR_TAUJ_AWO_MS_TAUJ_3 )
										+ ( MCU_CFG_STPMSK_TAUJ_AWO_TYPE_0	* MSR_TAUJ_AWO_STPMSK_TAUJ_AWO ),
											MCU_ENABLE_BIT_MASK_MSR_TAUJ_AWO								},

	{	&REG_STBC_ISO.u4MSR_RSENT,		  ( MCU_CFG_MS_RSENT_0_TYPE_0		* MSR_RSENT_MS_RSENT_0 )
										+ ( MCU_CFG_MS_RSENT_1_TYPE_0		* MSR_RSENT_MS_RSENT_1 )
										+ ( MCU_CFG_MS_RSENT_2_TYPE_0		* MSR_RSENT_MS_RSENT_2 )
										+ ( MCU_CFG_MS_RSENT_3_TYPE_0		* MSR_RSENT_MS_RSENT_3 )
										+ ( MCU_CFG_MS_RSENT_4_TYPE_0		* MSR_RSENT_MS_RSENT_4 )
										+ ( MCU_CFG_MS_RSENT_5_TYPE_0		* MSR_RSENT_MS_RSENT_5 )
										+ ( MCU_CFG_MS_RSENT_6_TYPE_0		* MSR_RSENT_MS_RSENT_6 )
										+ ( MCU_CFG_MS_RSENT_7_TYPE_0		* MSR_RSENT_MS_RSENT_7 )		,
											MCU_ENABLE_BIT_MASK_MSR_RSENT									},

	{	&REG_STBC_AWO.u4MSR_WDTB_AWO,	  ( MCU_CFG_STPMSK_WDTB_AWO_TYPE_0	* MSR_WDTB_AWO_STPMSK_WDTB_AWO ),
											MCU_ENABLE_BIT_MASK_MSR_WDTB_AWO								},

	{	&REG_STBC_ISO.u4MSR_FLXA,		  ( MCU_CFG_MS_FLXA_0_TYPE_0		* MSR_FLXA_MS_FLXA_0 )
										+ ( MCU_CFG_MS_FLXA_1_TYPE_0		* MSR_FLXA_MS_FLXA_1 )			,
											MCU_ENABLE_BIT_MASK_MSR_FLXA									},

	{	&REG_STBC_ISO.u4MSR_ETNB,		  ( MCU_CFG_MS_ETNB_0_TYPE_0		* MSR_ETNB_MS_ETNB_0 )
										+ ( MCU_CFG_MS_ETNB_1_TYPE_0		* MSR_ETNB_MS_ETNB_1 )			,
											MCU_ENABLE_BIT_MASK_MSR_ETNB									},

	{	&REG_STBC_ISO.u4MSR_ADCJ_ISO,	  ( MCU_CFG_MS_ADCJ_ISO_0_TYPE_0	* MSR_ADCJ_ISO_MS_ADCJ_0 )
										+ ( MCU_CFG_MS_ADCJ_ISO_1_TYPE_0	* MSR_ADCJ_ISO_MS_ADCJ_1 )		,
											MCU_ENABLE_BIT_MASK_MSR_ADCJ_ISO								},

	{	&REG_STBC_ISO.u4MSR_CXPI,		  ( MCU_CFG_MS_CXPI_0_TYPE_0		* MSR_CXPI_MS_CXPI_0 )
										+ ( MCU_CFG_MS_CXPI_1_TYPE_0		* MSR_CXPI_MS_CXPI_1 )
										+ ( MCU_CFG_MS_CXPI_2_TYPE_0		* MSR_CXPI_MS_CXPI_2 )
										+ ( MCU_CFG_MS_CXPI_3_TYPE_0		* MSR_CXPI_MS_CXPI_3 )			,
											MCU_ENABLE_BIT_MASK_MSR_CXPI									},

	{	&REG_STBC_ISO.u4MSR_PSI5,		  ( MCU_CFG_MS_PSI5_0_TYPE_0		* MSR_PSI5_MS_PSI5_0 )
										+ ( MCU_CFG_MS_PSI5_1_TYPE_0		* MSR_PSI5_MS_PSI5_1 )
										+ ( MCU_CFG_MS_PSI5_2_TYPE_0		* MSR_PSI5_MS_PSI5_2 )
										+ ( MCU_CFG_MS_PSI5_3_TYPE_0		* MSR_PSI5_MS_PSI5_3 )			,
											MCU_ENABLE_BIT_MASK_MSR_PSI5									},

	{	&REG_STBC_ISO.u4MSR_PWMD,		  ( MCU_CFG_MS_PWMD_TYPE_0			* MSR_PWMD_MS_PWMD_0 )			,
											MCU_ENABLE_BIT_MASK_MSR_PWMD									},

	{	&REG_STBC_ISO.u4MSR_RHSIF,		  ( MCU_CFG_MS_RHSIF_0_TYPE_0		* MSR_RHSIF_MS_RHSIF_0 )		,
											MCU_ENABLE_BIT_MASK_MSR_RHSIF									},

	{	&REG_STBC_ISO.u4MSR_SCI3,		  ( MCU_CFG_MS_SCI3_0_TYPE_0		* MSR_SCI3_MS_SCI3_0 )
										+ ( MCU_CFG_MS_SCI3_1_TYPE_0		* MSR_SCI3_MS_SCI3_1 )
										+ ( MCU_CFG_MS_SCI3_2_TYPE_0		* MSR_SCI3_MS_SCI3_2 )			,
											MCU_ENABLE_BIT_MASK_MSR_SCI3									},

	{	&REG_STBC_ISO.u4MSR_TAPA,		  ( MCU_CFG_MS_TAPA_0_TYPE_0		* MSR_TAPA_MS_TAPA_0 )
										+ ( MCU_CFG_MS_TAPA_1_TYPE_0		* MSR_TAPA_MS_TAPA_1 )
										+ ( MCU_CFG_MS_TAPA_2_TYPE_0		* MSR_TAPA_MS_TAPA_2 )
										+ ( MCU_CFG_MS_TAPA_3_TYPE_0		* MSR_TAPA_MS_TAPA_3 )			,
											MCU_ENABLE_BIT_MASK_MSR_TAPA									},

	{	&REG_STBC_ISO.u4MSR_TAUD,		  ( MCU_CFG_MS_TAUD_0_TYPE_0		* MSR_TAUD_MS_TAUD_0 )
										+ ( MCU_CFG_MS_TAUD_1_TYPE_0		* MSR_TAUD_MS_TAUD_1 )
										+ ( MCU_CFG_MS_TAUD_2_TYPE_0		* MSR_TAUD_MS_TAUD_2 )			,
											MCU_ENABLE_BIT_MASK_MSR_TAUD									},

	{	&REG_STBC_ISO.u4MSR_TAUJ_ISO,	  ( MCU_CFG_MS_TAUJ_ISO_0_TYPE_0	* MSR_TAUJ_ISO_MS_TAUJ_0 )
										+ ( MCU_CFG_MS_TAUJ_ISO_1_TYPE_0	* MSR_TAUJ_ISO_MS_TAUJ_1 )		,
											MCU_ENABLE_BIT_MASK_MSR_TAUJ_ISO								},

	{	&REG_STBC_ISO.u4MSR_TSG3,		  ( MCU_CFG_MS_TSG3_0_TYPE_0		* MSR_TSG3_MS_TSG3_0 )
										+ ( MCU_CFG_MS_TSG3_1_TYPE_0		* MSR_TSG3_MS_TSG3_1 )			,
											MCU_ENABLE_BIT_MASK_MSR_TSG3									},

	{	&REG_STBC_ISO.u4MSR_OSTM,		  ( MCU_CFG_MS_OSTM_0_TYPE_0		* MSR_OSTM_MS_OSTM_0 )
										+ ( MCU_CFG_MS_OSTM_1_TYPE_0		* MSR_OSTM_MS_OSTM_1 )
										+ ( MCU_CFG_MS_OSTM_2_TYPE_0		* MSR_OSTM_MS_OSTM_2 )
										+ ( MCU_CFG_MS_OSTM_3_TYPE_0		* MSR_OSTM_MS_OSTM_3 )
										+ ( MCU_CFG_MS_OSTM_4_TYPE_0		* MSR_OSTM_MS_OSTM_4 )
										+ ( MCU_CFG_MS_OSTM_5_TYPE_0		* MSR_OSTM_MS_OSTM_5 )
										+ ( MCU_CFG_MS_OSTM_6_TYPE_0		* MSR_OSTM_MS_OSTM_6 )
										+ ( MCU_CFG_MS_OSTM_7_TYPE_0		* MSR_OSTM_MS_OSTM_7 )
										+ ( MCU_CFG_MS_OSTM_8_TYPE_0		* MSR_OSTM_MS_OSTM_8 )
										+ ( MCU_CFG_MS_OSTM_9_TYPE_0		* MSR_OSTM_MS_OSTM_9 )			,
											MCU_ENABLE_BIT_MASK_MSR_OSTM									},

	{	&REG_STBC_AWO.u4MSR_ADCJ_AWO,	  ( MCU_CFG_MS_ADCJ_AWO_2_TYPE_0	* MSR_ADCJ_AWO_MS_ADCJ_2 )
										+ ( MCU_CFG_STPMSK_ADCJ_AWO_TYPE_0	* MSR_ADCJ_AWO_STPMSK_ADCJ )	,
											MCU_ENABLE_BIT_MASK_MSR_ADCJ_AWO								}

#elif ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
	{	&REG_STBC_ISO.u4MSR_RSCFD,		  ( MCU_CFG_MS_RSCFD_0_TYPE_0		* MSR_RSCFD_MS_RSCFD_0 )
										+ ( MCU_CFG_MS_RSCFD_1_TYPE_0		* MSR_RSCFD_MS_RSCFD_1 )
										+ ( MSR_RSCFD_2_RESERVED_BIT		* MSR_RSCFD_MS_RSCFD_2 )		,
											MCU_ENABLE_BIT_MASK_MSR_RSCFD									},

	{	&REG_STBC_ISO.u4MSR_GTM,		  ( MCU_CFG_MS_GTM_0_TYPE_0			* MSR_GTM_MS_GTM_0 )			,
											MCU_ENABLE_BIT_MASK_MSR_GTM									},

	{	&REG_STBC_ISO.u4MSR_MSPI,		  ( MCU_CFG_MS_MSPI_0_TYPE_0		* MSR_MSPI_MS_MSPI_0 )
										+ ( MCU_CFG_MS_MSPI_1_TYPE_0		* MSR_MSPI_MS_MSPI_1 )
										+ ( MCU_CFG_MS_MSPI_2_TYPE_0		* MSR_MSPI_MS_MSPI_2 )
										+ ( MCU_CFG_MS_MSPI_3_TYPE_0		* MSR_MSPI_MS_MSPI_3 )
										+ ( MCU_CFG_MS_MSPI_4_TYPE_0		* MSR_MSPI_MS_MSPI_4 )
										+ ( MCU_CFG_MS_MSPI_5_TYPE_0		* MSR_MSPI_MS_MSPI_5 )
										+ ( MCU_CFG_MS_MSPI_6_TYPE_0		* MSR_MSPI_MS_MSPI_6 )
										+ ( MCU_CFG_MS_MSPI_7_TYPE_0		* MSR_MSPI_MS_MSPI_7 )
										+ ( MCU_CFG_MS_MSPI_8_TYPE_0		* MSR_MSPI_MS_MSPI_8 )
										+ ( MCU_CFG_MS_MSPI_9_TYPE_0		* MSR_MSPI_MS_MSPI_9 )			,
											MCU_ENABLE_BIT_MASK_MSR_MSPI									},

	{	&REG_STBC_ISO.u4MSR_RLIN3,		  ( MCU_CFG_MS_RLIN3_0_TYPE_0		* MSR_RLIN3_MS_RLIN3_0 )
										+ ( MCU_CFG_MS_RLIN3_1_TYPE_0		* MSR_RLIN3_MS_RLIN3_1 )
										+ ( MCU_CFG_MS_RLIN3_2_TYPE_0		* MSR_RLIN3_MS_RLIN3_2 )
										+ ( MCU_CFG_MS_RLIN3_3_TYPE_0		* MSR_RLIN3_MS_RLIN3_3 )
										+ ( MCU_CFG_MS_RLIN3_4_TYPE_0		* MSR_RLIN3_MS_RLIN3_4 )
										+ ( MCU_CFG_MS_RLIN3_5_TYPE_0		* MSR_RLIN3_MS_RLIN3_5 )
										+ ( MCU_CFG_MS_RLIN3_6_TYPE_0		* MSR_RLIN3_MS_RLIN3_6 )
										+ ( MCU_CFG_MS_RLIN3_7_TYPE_0		* MSR_RLIN3_MS_RLIN3_7 )
										+ ( MCU_CFG_MS_RLIN3_8_TYPE_0		* MSR_RLIN3_MS_RLIN3_8 )
										+ ( MCU_CFG_MS_RLIN3_9_TYPE_0		* MSR_RLIN3_MS_RLIN3_9 )
										+ ( MCU_CFG_MS_RLIN3_10_TYPE_0		* MSR_RLIN3_MS_RLIN3_10 )
										+ ( MCU_CFG_MS_RLIN3_11_TYPE_0		* MSR_RLIN3_MS_RLIN3_11 )
										+ ( MCU_CFG_MS_RLIN3_12_TYPE_0		* MSR_RLIN3_MS_RLIN3_12 )
										+ ( MCU_CFG_MS_RLIN3_13_TYPE_0		* MSR_RLIN3_MS_RLIN3_13 )
										+ ( MCU_CFG_MS_RLIN3_14_TYPE_0		* MSR_RLIN3_MS_RLIN3_14 )
										+ ( MCU_CFG_MS_RLIN3_15_TYPE_0		* MSR_RLIN3_MS_RLIN3_15 )
										+ ( MCU_CFG_MS_RLIN3_16_TYPE_0		* MSR_RLIN3_MS_RLIN3_16 )
										+ ( MCU_CFG_MS_RLIN3_17_TYPE_0		* MSR_RLIN3_MS_RLIN3_17 )
										+ ( MCU_CFG_MS_RLIN3_18_TYPE_0		* MSR_RLIN3_MS_RLIN3_18 )
										+ ( MCU_CFG_MS_RLIN3_19_TYPE_0		* MSR_RLIN3_MS_RLIN3_19 )
										+ ( MCU_CFG_MS_RLIN3_20_TYPE_0		* MSR_RLIN3_MS_RLIN3_20 )
										+ ( MCU_CFG_MS_RLIN3_21_TYPE_0		* MSR_RLIN3_MS_RLIN3_21 )
										+ ( MCU_CFG_MS_RLIN3_22_TYPE_0		* MSR_RLIN3_MS_RLIN3_22 )
										+ ( MCU_CFG_MS_RLIN3_23_TYPE_0		* MSR_RLIN3_MS_RLIN3_23 )		,
											MCU_ENABLE_BIT_MASK_MSR_RLIN3									},

	{	&REG_STBC_ISO.u4MSR_ENCA,		  ( MCU_CFG_MS_ENCA_0_TYPE_0		* MSR_ENCA_MS_ENCA_0 )
										+ ( MCU_CFG_MS_ENCA_1_TYPE_0		* MSR_ENCA_MS_ENCA_1 )			,
											MCU_ENABLE_BIT_MASK_MSR_ENCA									},

	{	&REG_STBC_ISO.u4MSR_TPBA, 		  ( MCU_CFG_MS_TPBA_0_TYPE_0		* MSR_TPBA_MS_TPBA_0 )
										+ ( MCU_CFG_MS_TPBA_1_TYPE_0		* MSR_TPBA_MS_TPBA_1 )			,
											MCU_ENABLE_BIT_MASK_MSR_TPBA									},

	{	&REG_STBC_ISO.u4MSR_FLXA,		  ( MCU_CFG_MS_FLXA_0_TYPE_0		* MSR_FLXA_MS_FLXA_0 )
										+ ( MSR_FLXA_1_RESERVED_BIT			* MSR_FLXA_MS_FLXA_1 )			,
											MCU_ENABLE_BIT_MASK_MSR_FLXA									},

	{	&REG_STBC_ISO.u4MSR_ETN,		  ( MCU_CFG_MS_ETN_0_TYPE_0			* MSR_ETN_MS_ETN_0 )
										+ ( MCU_CFG_MS_ETN_1_TYPE_0			* MSR_ETN_MS_ETN_1 )
										+ ( MCU_CFG_MS_ETN_2_TYPE_0			* MSR_ETN_MS_ETN_2 )
										+ ( MSR_ETN_4_RESERVED_BIT			* MSR_ETN_MS_ETN_4 )			,
											MCU_ENABLE_BIT_MASK_MSR_ETN										},

	{	&REG_STBC_ISO.u4MSR_RSENT,		  ( MCU_CFG_MS_RSENT_0_TYPE_0		* MSR_RSENT_MS_RSENT_0 )
										+ ( MCU_CFG_MS_RSENT_1_TYPE_0		* MSR_RSENT_MS_RSENT_1 )
										+ ( MCU_CFG_MS_RSENT_2_TYPE_0		* MSR_RSENT_MS_RSENT_2 )
										+ ( MCU_CFG_MS_RSENT_3_TYPE_0		* MSR_RSENT_MS_RSENT_3 )
										+ ( MCU_CFG_MS_RSENT_4_TYPE_0		* MSR_RSENT_MS_RSENT_4 )
										+ ( MCU_CFG_MS_RSENT_5_TYPE_0		* MSR_RSENT_MS_RSENT_5 )
										+ ( MCU_CFG_MS_RSENT_6_TYPE_0		* MSR_RSENT_MS_RSENT_6 )
										+ ( MCU_CFG_MS_RSENT_7_TYPE_0		* MSR_RSENT_MS_RSENT_7 )
										+ ( MCU_CFG_MS_RSENT_8_TYPE_0		* MSR_RSENT_MS_RSENT_8 )
										+ ( MCU_CFG_MS_RSENT_9_TYPE_0		* MSR_RSENT_MS_RSENT_9 )
										+ ( MCU_CFG_MS_RSENT_10_TYPE_0		* MSR_RSENT_MS_RSENT_10 )
										+ ( MCU_CFG_MS_RSENT_11_TYPE_0		* MSR_RSENT_MS_RSENT_11 )
										+ ( MCU_CFG_MS_RSENT_12_TYPE_0		* MSR_RSENT_MS_RSENT_12 )
										+ ( MCU_CFG_MS_RSENT_13_TYPE_0		* MSR_RSENT_MS_RSENT_13 )
										+ ( MCU_CFG_MS_RSENT_14_TYPE_0		* MSR_RSENT_MS_RSENT_14 )
										+ ( MCU_CFG_MS_RSENT_15_TYPE_0		* MSR_RSENT_MS_RSENT_15 )
										+ ( MCU_CFG_MS_RSENT_16_TYPE_0		* MSR_RSENT_MS_RSENT_16 )
										+ ( MCU_CFG_MS_RSENT_17_TYPE_0		* MSR_RSENT_MS_RSENT_17 )
										+ ( MCU_CFG_MS_RSENT_18_TYPE_0		* MSR_RSENT_MS_RSENT_18 )
										+ ( MCU_CFG_MS_RSENT_19_TYPE_0		* MSR_RSENT_MS_RSENT_19 )
										+ ( MCU_CFG_MS_RSENT_20_TYPE_0		* MSR_RSENT_MS_RSENT_20 )
										+ ( MCU_CFG_MS_RSENT_21_TYPE_0		* MSR_RSENT_MS_RSENT_21 )
										+ ( MCU_CFG_MS_RSENT_22_TYPE_0		* MSR_RSENT_MS_RSENT_22 )
										+ ( MCU_CFG_MS_RSENT_23_TYPE_0		* MSR_RSENT_MS_RSENT_23 )
										+ ( MCU_CFG_MS_RSENT_24_TYPE_0		* MSR_RSENT_MS_RSENT_24 )
										+ ( MCU_CFG_MS_RSENT_25_TYPE_0		* MSR_RSENT_MS_RSENT_25 )
										+ ( MCU_CFG_MS_RSENT_26_TYPE_0		* MSR_RSENT_MS_RSENT_26 )
										+ ( MCU_CFG_MS_RSENT_27_TYPE_0		* MSR_RSENT_MS_RSENT_27 )
										+ ( MCU_CFG_MS_RSENT_28_TYPE_0		* MSR_RSENT_MS_RSENT_28 )
										+ ( MCU_CFG_MS_RSENT_29_TYPE_0		* MSR_RSENT_MS_RSENT_29 )		,
											MCU_ENABLE_BIT_MASK_MSR_RSENT									},

	{	&REG_STBC_ISO.u4MSR_DSADC_CADC,	  ( MCU_CFG_MS_DSADC_CADC_0_TYPE_0	* MSR_DSADC_CADC_MS_DSADC_0 )
										+ ( MCU_CFG_MS_DSADC_CADC_1_TYPE_0	* MSR_DSADC_CADC_MS_DSADC_1 )
										+ ( MCU_CFG_MS_DSADC_CADC_2_TYPE_0	* MSR_DSADC_CADC_MS_DSADC_2 )
										+ ( MCU_CFG_MS_DSADC_CADC_3_TYPE_0	* MSR_DSADC_CADC_MS_DSADC_3 )	,
											MCU_ENABLE_BIT_MASK_MSR_DSADC_CADC								},

	{	&REG_STBC_ISO.u4MSR_ADCK_ISO,	  ( MCU_CFG_MS_ADCK_ISO_0_TYPE_0	* MSR_ADCK_ISO_MS_ADCK_ISO_0 )
										+ ( MCU_CFG_MS_ADCK_ISO_1_TYPE_0	* MSR_ADCK_ISO_MS_ADCK_ISO_1 )
										+ ( MCU_CFG_MS_ADCK_ISO_2_TYPE_0	* MSR_ADCK_ISO_MS_ADCK_ISO_2 )
										+ ( MCU_CFG_MS_ADCK_ISO_3_TYPE_0	* MSR_ADCK_ISO_MS_ADCK_ISO_3 )
										+ ( MCU_CFG_MS_ADCK_ISO_4_TYPE_0	* MSR_ADCK_ISO_MS_ADCK_ISO_4 )
										+ ( MCU_CFG_MS_ADCK_ISO_5_TYPE_0	* MSR_ADCK_ISO_MS_ADCK_ISO_5 )
										+ ( MCU_CFG_MS_ADCK_ISO_6_TYPE_0	* MSR_ADCK_ISO_MS_ADCK_ISO_6 )
										+ ( MCU_CFG_MS_ADCK_ISO_7_TYPE_0	* MSR_ADCK_ISO_MS_ADCK_ISO_7 )	,
											MCU_ENABLE_BIT_MASK_MSR_ADCK_ISO								},

	{	&REG_STBC_ISO.u4MSR_RHSIF,		  ( MCU_CFG_MS_RHSIF_0_TYPE_0		* MSR_RHSIF_MS_RHSIF_0 )
										+ ( MCU_CFG_MS_RHSIF_1_TYPE_0		* MSR_RHSIF_MS_RHSIF_1 )		,
											MCU_ENABLE_BIT_MASK_MSR_RHSIF									},

	{	&REG_STBC_ISO.u4MSR_RHSB,		  ( MCU_CFG_MS_RHSB_0_TYPE_0		* MSR_RHSB_MS_RHSB_0 )
										+ ( MCU_CFG_MS_RHSB_1_TYPE_0		* MSR_RHSB_MS_RHSB_1 )
										+ ( MCU_CFG_MS_RHSB_2_TYPE_0		* MSR_RHSB_MS_RHSB_2 )
										+ ( MCU_CFG_MS_RHSB_3_TYPE_0		* MSR_RHSB_MS_RHSB_3 )			,
											MCU_ENABLE_BIT_MASK_MSR_RHSB									},

	{	&REG_STBC_ISO.u4MSR_SFMA,		  ( MCU_CFG_MS_SFMA_0_TYPE_0		* MSR_SFMA_MS_SFMA_0 )			,
											MCU_ENABLE_BIT_MASK_MSR_SFMA									},

	{	&REG_STBC_ISO.u4MSR_TAPA,		  ( MCU_CFG_MS_TAPA_0_TYPE_0		* MSR_TAPA_MS_TAPA_0 )
										+ ( MCU_CFG_MS_TAPA_1_TYPE_0		* MSR_TAPA_MS_TAPA_1 )
										+ ( MCU_CFG_MS_TAPA_2_TYPE_0		* MSR_TAPA_MS_TAPA_2 )
										+ ( MCU_CFG_MS_TAPA_3_TYPE_0		* MSR_TAPA_MS_TAPA_3 )
										+ ( MCU_CFG_MS_TAPA_4_TYPE_0		* MSR_TAPA_MS_TAPA_4 )
										+ ( MCU_CFG_MS_TAPA_5_TYPE_0		* MSR_TAPA_MS_TAPA_5 )			,
											MCU_ENABLE_BIT_MASK_MSR_TAPA									},

	{	&REG_STBC_ISO.u4MSR_TAUD,		  ( MCU_CFG_MS_TAUD_0_TYPE_0		* MSR_TAUD_MS_TAUD_0 )
										+ ( MCU_CFG_MS_TAUD_1_TYPE_0		* MSR_TAUD_MS_TAUD_1 )
										+ ( MCU_CFG_MS_TAUD_2_TYPE_0		* MSR_TAUD_MS_TAUD_2 )
										+ ( MCU_CFG_MS_TAUD_3_TYPE_0		* MSR_TAUD_MS_TAUD_3 )			,
											MCU_ENABLE_BIT_MASK_MSR_TAUD									},

	{	&REG_STBC_ISO.u4MSR_TSG3,		  ( MCU_CFG_MS_TSG3_0_TYPE_0		* MSR_TSG3_MS_TSG3_0 )
										+ ( MCU_CFG_MS_TSG3_1_TYPE_0		* MSR_TSG3_MS_TSG3_1 )
										+ ( MCU_CFG_MS_TSG3_2_TYPE_0		* MSR_TSG3_MS_TSG3_2 )			,
											MCU_ENABLE_BIT_MASK_MSR_TSG3									},

	{	&REG_STBC_ISO.u4MSR_OSTM,		  ( MCU_CFG_MS_OSTM_0_TYPE_0		* MSR_OSTM_MS_OSTM_0 )
										+ ( MCU_CFG_MS_OSTM_1_TYPE_0		* MSR_OSTM_MS_OSTM_1 )
										+ ( MCU_CFG_MS_OSTM_2_TYPE_0		* MSR_OSTM_MS_OSTM_2 )
										+ ( MCU_CFG_MS_OSTM_3_TYPE_0		* MSR_OSTM_MS_OSTM_3 )
										+ ( MCU_CFG_MS_OSTM_4_TYPE_0		* MSR_OSTM_MS_OSTM_4 )
										+ ( MCU_CFG_MS_OSTM_5_TYPE_0		* MSR_OSTM_MS_OSTM_5 )
										+ ( MSR_OSTM_6_RESERVED_BIT			* MSR_OSTM_MS_OSTM_6 )
										+ ( MSR_OSTM_7_RESERVED_BIT			* MSR_OSTM_MS_OSTM_7 )
										+ ( MSR_OSTM_8_RESERVED_BIT			* MSR_OSTM_MS_OSTM_8 )
										+ ( MSR_OSTM_9_RESERVED_BIT			* MSR_OSTM_MS_OSTM_9 )			,
											MCU_ENABLE_BIT_MASK_MSR_OSTM									},

	{	&REG_STBC_ISO.u4MSR_DFE,		  ( MCU_CFG_MS_DFE_0_TYPE_0			* MSR_DFE_MS_DFE_0 )			,
											MCU_ENABLE_BIT_MASK_MSR_DFE										},

	{	&REG_STBC_ISO.u4MSR_RDC,		  ( MCU_CFG_MS_RDC_0_TYPE_0			* MSR_RDC_MS_RDC_0 )
										+ ( MCU_CFG_MS_RDC_1_TYPE_0			* MSR_RDC_MS_RDC_1 )
										+ ( MCU_CFG_MS_RDC_2_TYPE_0			* MSR_RDC_MS_RDC_2 )
										+ ( MCU_CFG_MS_RDC_3_TYPE_0			* MSR_RDC_MS_RDC_3 )			,
											MCU_ENABLE_BIT_MASK_MSR_RDC									},

	{	&REG_STBC_ISO.u4MSR_FCOMP,		  ( MCU_CFG_MS_FCOMP_0_TYPE_0		* MSR_FCOMP_MS_FCOMP_0 )
										+ ( MCU_CFG_MS_FCOMP_1_TYPE_0		* MSR_FCOMP_MS_FCOMP_1 )
										+ ( MCU_CFG_MS_FCOMP_2_TYPE_0		* MSR_FCOMP_MS_FCOMP_2 )
										+ ( MCU_CFG_MS_FCOMP_3_TYPE_0		* MSR_FCOMP_MS_FCOMP_3 )
										+ ( MCU_CFG_MS_FCOMP_4_TYPE_0		* MSR_FCOMP_MS_FCOMP_4 )
										+ ( MCU_CFG_MS_FCOMP_5_TYPE_0		* MSR_FCOMP_MS_FCOMP_5 )
										+ ( MCU_CFG_MS_FCOMP_6_TYPE_0		* MSR_FCOMP_MS_FCOMP_6 )
										+ ( MCU_CFG_MS_FCOMP_7_TYPE_0		* MSR_FCOMP_MS_FCOMP_7 )
										+ ( MCU_CFG_MS_FCOMP_8_TYPE_0		* MSR_FCOMP_MS_FCOMP_8 )
										+ ( MCU_CFG_MS_FCOMP_9_TYPE_0		* MSR_FCOMP_MS_FCOMP_9 )
										+ ( MCU_CFG_MS_FCOMP_10_TYPE_0		* MSR_FCOMP_MS_FCOMP_10 )		,
											MCU_ENABLE_BIT_MASK_MSR_FCOMP									},

	{	&REG_STBC_ISO.u4MSR_EMU,		  ( MCU_CFG_MS_EMU_0_TYPE_0			* MSR_EMU_MS_EMU_0 )
										+ ( MCU_CFG_MS_EMU_1_TYPE_0			* MSR_EMU_MS_EMU_1 )			,
											MCU_ENABLE_BIT_MASK_MSR_EMU										},

	{	&REG_STBC_ISO.u4MSR_HRPWM,		  ( MCU_CFG_MS_HRPWM_0_TYPE_0		* MSR_HRPWM_MS_HRPWM_0 )		,
											MCU_ENABLE_BIT_MASK_MSR_HRPWM									}
#endif

};

#define MCU_STOP_SEC_CONST_UNSPECIFIED
#include "Mcu_MemMap.h"

/*==============================================================================================*/
/* variables																					*/
/*==============================================================================================*/
#define MCU_START_SEC_VAR_NO_INIT_GLOBAL_32
#include "Mcu_MemMap.h"

#if	( MCU_CFG_RESET_REASON == STD_ON )
static uint32 s_u4ResetRawValue;
#endif	/* ( MCU_CFG_RESET_REASON == STD_ON ) */

#define MCU_STOP_SEC_VAR_NO_INIT_GLOBAL_32
#include "Mcu_MemMap.h"

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
/* Limitation		:	This function must be called with interrupts disabled.					*/
/*					:	Do not use the configuration information given in ConfigPtr.			*/
/*					:	Set the argument to NULL.												*/
/*					:	Call once before using the MCU API.										*/
/************************************************************************************************/
FUNC( void, MCU_CODE ) Mcu_Init( const Mcu_ConfigType* ConfigPtr )
{
	(void)ConfigPtr;

#if	( MCU_CFG_RESET_REASON == STD_ON )
	Mcu_ResetInit();
#endif	/* ( MCU_CFG_RESET_REASON == STD_ON ) */
}

#if	( MCU_CFG_INIT_CLOCK == STD_ON )
/************************************************************************************************/
/* Service name		:	Initialize the PLL and MCU clock										*/
/* Reentrancy		:	Non Re-entrant															*/
/* Parameters(in)	:	ClockSetting - the configuration (parameters) for the Clock settings	*/
/* Return value		:	E_OK		| Success													*/
/*				 	:	E_NOT_OK	| Failure													*/
/* Limitation		:	Call Mcu_Init before calling this API.									*/
/*					:	Set the argument to MCU_CLOCK_TYPE_0.									*/
/************************************************************************************************/
FUNC( Std_ReturnType, MCU_CODE ) Mcu_InitClock( Mcu_ClockType ClockSetting )
{
	Std_ReturnType t_udResult;

	(void)ClockSetting;

	REG_CLOCK_ISO.u4CLKKCPROT1 = MCU_CLOCK_PROTECT_ENABLE;								/* Enable writing to protected registers */

	t_udResult = Mcu_ClockUpStart();

	if ( t_udResult == E_OK )
	{
		t_udResult = Mcu_ClockSetupPeri();
	}

	REG_CLOCK_ISO.u4CLKKCPROT1 = MCU_CLOCK_PROTECT_DISABLE;								/* Disnable writing to protected registers */

#if	( MCU_CFG_DEM_SET_EVENT == STD_ON )
	if ( t_udResult == E_OK )
	{
		(void)Dem_SetEventStatus( MCU_CFG_E_CLOCK_FAILURE, DEM_EVENT_STATUS_PASSED );	/* Notify DEM of PASS */
	}
	else
	{
		(void)Dem_SetEventStatus( MCU_CFG_E_CLOCK_FAILURE, DEM_EVENT_STATUS_FAILED );	/* Notify DEM of FAIL */
	}
#endif	/* ( MCU_CFG_DEM_SET_EVENT == STD_ON ) */

	return ( t_udResult );
}
#endif	/* ( MCU_CFG_INIT_CLOCK == STD_ON ) */

#if	( MCU_CFG_NO_PLL == FALSE )
/************************************************************************************************/
/* Service name		:	Activate the PLL clock to the MCU clock distribution					*/
/* Reentrancy		:	Non Re-entrant															*/
/* Parameters(in)	:	None																	*/
/* Return value		:	E_OK		| Success													*/
/*				 	:	E_NOT_OK	| Failure													*/
/* Limitation		:	Call this API after confirming that the PLL is locked by				*/
/*					:	Mcu_GetPllStatus().														*/
/************************************************************************************************/
FUNC( Std_ReturnType, MCU_CODE ) Mcu_DistributePllClock( void )
{
	Std_ReturnType t_udResult;

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
	volatile uint32 t_u4Reg;
#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) */

	/*---------------------------------------*/
	/* Enable writing to protected registers */
	/*---------------------------------------*/
	REG_CLOCK_ISO.u4CLKKCPROT1 = MCU_CLOCK_PROTECT_ENABLE;
	REG_STBC_ISO.u4MSRKCPROT = MCU_STBC_PROTECT_ENABLE;

	t_udResult = Mcu_ClockDistributePll();

	if ( t_udResult == E_OK )
	{
		t_udResult = Mcu_ClockSetupFout();
	}

	if ( t_udResult == E_OK )
	{
		t_udResult = Mcu_ClockSupplyPeri();
	}

#if	( MCU_CFG_CLK_MONITOR == STD_ON )
	if ( t_udResult == E_OK )
	{
#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
#if	( MCU_CFG_CLMA3CLME == STD_ON )
		Mcu_ClockMonitorReset();
#endif	/* ( MCU_CFG_CLMA3CLME == STD_ON ) */
#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) */

		t_udResult = Mcu_ClockMonitorSetup();
	}
#endif	/* ( MCU_CFG_CLK_MONITOR == STD_ON ) */

	/*----------------------------------------*/
	/* Disable writing to protected registers */
	/*----------------------------------------*/
	REG_CLOCK_ISO.u4CLKKCPROT1 = MCU_CLOCK_PROTECT_DISABLE;
	REG_STBC_ISO.u4MSRKCPROT = MCU_STBC_PROTECT_DISABLE;

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
	/*--------------------------------------------------------------------------------------------------*/
	/* ADCKA and TAUJ2/TAUJ3 need to wait for time before register setting after module standby cancel.	*/
	/* Read the register of ADCKA or TAUJ2/TAUJ3 once. (Dummy read)										*/
	/*--------------------------------------------------------------------------------------------------*/
#if ( MCU_CFG_MS_ADCJ_AWO_2_TYPE_0 == MCU_MS_CLOCK_SUPPLIED )
	t_u4Reg = Reg_ADC2.stMODULE.u4VCR[0];
#endif

#if ( MCU_CFG_MS_TAUJ_AWO_2_TYPE_0 == MCU_MS_CLOCK_SUPPLIED )
	t_u4Reg = REG_TAUJ2.u4TAUJnCNTm[0];
#endif

#if ( MCU_CFG_MS_TAUJ_AWO_3_TYPE_0 == MCU_MS_CLOCK_SUPPLIED )
	t_u4Reg = REG_TAUJ3.u4TAUJnCNTm[0];
#endif

#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) */

	return ( t_udResult );
}
#endif	/* ( MCU_CFG_NO_PLL == FALSE ) */

/************************************************************************************************/
/* Service name		:	Provide the lock status of the PLL										*/
/* Reentrancy		:	Re-entrant																*/
/* Parameters(in)	:	None																	*/
/* Return value		:	MCU_PLL_LOCKED				|	Stable state 							*/
/*					:	MCU_PLL_UNLOCKED			|	Unstable state 							*/
/*					:	MCU_PLL_STATUS_UNDEFINED	|	Undefined state 						*/
/* Limitation		:	Call Mcu_Init before calling this API.									*/
/************************************************************************************************/
FUNC( Mcu_PllStatusType, MCU_CODE ) Mcu_GetPllStatus( void )
{
	Mcu_PllStatusType t_udResult;

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
	sint32 t_s4Count;
#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) */

#if ( MCU_CFG_NO_PLL == FALSE )
	if ( ( REG_CLOCK_ISO.u4PLLS & MCU_PLLS_MASK ) == MCU_PLLS_STABLE )				/* Confirm that the PLL/SSCG has been stable */
	{
		t_udResult = MCU_PLL_LOCKED;

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
		for ( t_s4Count = 0; t_s4Count < MCU_PLL_READ_STABLE_TIMES; t_s4Count++ )	/* Read PLL clock stable state 4 times */
		{
			if ( ( REG_CLOCK_ISO.u4PLLS & CLOCK_PLLS_PLLCLKSTAB ) != MCU_PLLS_PLLCLKSTAB_STABLE )
			{
				t_udResult = MCU_PLL_UNLOCKED;
				break;
			}
		}
#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) */

	}
	else
	{
		t_udResult = MCU_PLL_UNLOCKED;
	}

#else
	t_udResult = MCU_PLL_STATUS_UNDEFINED;
#endif	/* ( MCU_CFG_NO_PLL == FALSE ) */

	return ( t_udResult );
}

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
/************************************************************************************************/
/* Service name		:	Switch to Chip Standby Mode												*/
/* Reentrancy		:	Non Re-entrant															*/
/* Parameters(in)	:	McuMode - Chip Standby Mode configuration								*/
/* Return value		:	None																	*/
/* Limitation		:	DeepSTOP mode is not supported for U2B.									*/
/*					:	Call Mcu_Init before calling this API.									*/
/************************************************************************************************/
FUNC( void, MCU_CODE ) Mcu_SetMode( Mcu_ModeType McuMode )
{
	Std_ReturnType t_udResult;
	uint32 t_u4RegValue;
	(void)McuMode;

	t_udResult = E_OK;

	/*---------------------------------------*/
	/* Enable writing to protected registers */
	/*---------------------------------------*/
	REG_CLOCK_ISO.u4CLKKCPROT1 = MCU_CLOCK_PROTECT_ENABLE;
	REG_STBC_ISO.u4STBCKCPROT = MCU_STBC_PROTECT_ENABLE;

	/* If Mcu_SetMode is called after wake-up from DeepSTOP mode without gear-up in Mcu_InitClock, */
	/* the processings of setting regsiters that are retained in DeepSTOP mode are skipped. */
	/* Whether a gear-up has been performed is determined by the clock source of CPU system clock. */
	t_u4RegValue = REG_CLOCK_ISO.u4CKSC_CPUS;
	if ( t_u4RegValue == MCU_CKSC_CPUC_CPUCLKSCSID_PLLO )
	{
#if	( MCU_CFG_CLK_MONITOR == STD_ON )
		Mcu_ClockMonitorStandby();
#endif	/* ( MCU_CFG_CLK_MONITOR == STD_ON ) */

		t_udResult = Mcu_StandbyClockDown();

		if ( t_udResult == E_OK )
		{
			t_udResult = Mcu_StandbyPeri();
		}

		if ( t_udResult == E_OK )
		{
			t_udResult = Mcu_StandbyFout();
		}

		if ( t_udResult == E_OK )
		{
			t_udResult = Mcu_StandbySetPwrgdCnt();
		}
	}
	else
	{
		if ( ( REG_CLOCK_AWO.u4MOSCS & CLOCK_MOSCS_MOSCEN ) == MCU_MOSCS_MOSCEN_ENABLE )
		{
			t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_AWO.u4MOSCS, CLOCK_MOSCS_MOSCSTAB, MCU_MOSCS_MOSCSTAB_STABLE, MCU_PROCESS_TIME_OUT_OTHER );
		}
	}

	if ( t_udResult == E_OK )
	{
#if	( MCU_CFG_RESET_REASON == STD_ON )
		REG_RESET_ISO.u4RESFC = MCU_CLEAR_RESET_FACTOR;			/* Clear the reset factor register */
#endif	/* ( MCU_CFG_RESET_REASON == STD_ON ) */

#if	( MCU_CFG_USE_SLEEP_READY_CALLOUT == STD_ON )
		MCU_CFG_SLEEP_READY_CALLOUT();
#endif	/* ( MCU_CFG_USE_SLEEP_READY_CALLOUT == STD_ON ) */

		REG_STBC_AWO.u4STBC0PSC = MCU_STBC0PSC_DEEPSTOP_MODE;	/* Activate the DeepSTOP Mode */

		/* Wait for transition to DeepSTOP */
#if	( MCU_CFG_WAIT_SLEEP_TIMEOUT == MCU_WAIT_SLEEP_TIMEOUT_UNLIMITED )
		while(1)
		{
			/* Infinity loop. No action required. */
		}
#else
		if ( t_u4RegValue == MCU_CKSC_CPUC_CPUCLKSCSID_PLLO )
		{
			MCAL_LIB_Wait( MCU_CFG_WAIT_SLEEP_TIMEOUT >> MCU_CONVERT_WAITTIME_SHIFT_PLLO2 );
		}
		else
		{
			MCAL_LIB_Wait( MCU_CFG_WAIT_SLEEP_TIMEOUT >> MCU_CONVERT_WAITTIME_SHIFT_IOSC );
		}
#endif
	}
#if	( MCU_CFG_DEM_SET_EVENT == STD_ON )
	else
	{
		(void)Dem_SetEventStatus( MCU_CFG_E_CLOCK_FAILURE, DEM_EVENT_STATUS_FAILED );
	}
#endif	/* ( MCU_CFG_DEM_SET_EVENT == STD_ON ) */

	/*----------------------------------------*/
	/* Disable writing to protected registers */
	/*----------------------------------------*/
	REG_CLOCK_ISO.u4CLKKCPROT1 = MCU_CLOCK_PROTECT_DISABLE;
	REG_STBC_ISO.u4STBCKCPROT = MCU_STBC_PROTECT_DISABLE;
}
#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) */

#if	( MCU_CFG_PERFORM_RESET == STD_ON )
/************************************************************************************************/
/* Service name		:	Perform a microcontroller reset											*/
/* Reentrancy		:	Non Re-entrant															*/
/* Parameters(in)	:	None																	*/
/* Return value		:	None																	*/
/* Limitation		:	Call Mcu_Init before calling this API.									*/
/************************************************************************************************/
FUNC( void, MCU_CODE ) Mcu_PerformReset( void )
{
	REG_RESET_ISO.u4RESKCPROT0 = MCU_RESET_PROTECT_ENABLE;	/* Enable writing to protected registers */

#if	( MCU_CFG_RESET_SETTING == MCU_SYSTEM_RESET_2 )
	REG_RESET_AWO.u4SWSRESA = MCU_GENERATE_RESET;			/* Software system reset 2 trigger */

#elif	( MCU_CFG_RESET_SETTING == MCU_APPLICATION_RESET )
	REG_RESET_AWO.u4SWARESA = MCU_GENERATE_RESET;			/* Software application reset trigger */
#endif	/* MCU_CFG_RESET_SETTING */

	REG_RESET_ISO.u4RESKCPROT0 = MCU_RESET_PROTECT_DISABLE;	/* Disable writing to protected registers */
}
#endif	/* ( MCU_CFG_PERFORM_RESET == STD_ON ) */

#if	( MCU_CFG_RESET_REASON == STD_ON )
/************************************************************************************************/
/* Service name		:	Provide the reset factor												*/
/* Reentrancy		:	Re-entrant																*/
/* Parameters(in)	:	None																	*/
/* Return value		:	None																	*/
/* Limitation		:	Call Mcu_Init before calling this API.									*/
/************************************************************************************************/
FUNC( Mcu_ResetType, MCU_CODE ) Mcu_GetResetReason( void )
{
	sint32 i;
	sint32 t_s4Cnt;
	Mcu_ResetType t_udResult;

	t_s4Cnt = (sint32)0;
	t_udResult = MCU_RESET_UNDEFINED;

	for ( i = 0; i < MCU_NUM_RESET_REASON; i++ )
	{
		if ( ( s_u4ResetRawValue & stMcu_ResetReasonTbl[i].RegBit ) == stMcu_ResetReasonTbl[i].RegBit )	/* Check correspondence between register bits and reset reasons */
		{
			t_udResult = stMcu_ResetReasonTbl[i].ResetType;
			t_s4Cnt++;

			if ( t_s4Cnt >= MCU_MULTIPLE_RESET_NUM )													/* Multiple reset factors */
			{
				t_udResult = MCU_MULTIPLE_RESET;
				break;
			}
		}
	}

	return ( t_udResult );
}
#endif	/* ( MCU_CFG_RESET_REASON == STD_ON ) */

#if	( MCU_CFG_RESET_REASON == STD_ON )
/************************************************************************************************/
/* Service name		:	Provide the raw reset factor											*/
/* Reentrancy		:	Re-entrant																*/
/* Parameters(in)	:	None																	*/
/* Return value		:	None																	*/
/* Limitation		:	Call Mcu_Init before calling this API.									*/
/************************************************************************************************/
FUNC( Mcu_RawResetType, MCU_CODE ) Mcu_GetResetRawValue( void )
{
	Mcu_RawResetType t_udResult;

	t_udResult = (Mcu_RawResetType)s_u4ResetRawValue;

	return ( t_udResult );
}
#endif	/* ( MCU_CFG_RESET_REASON == STD_ON ) */

/*----------------------------------------------------------------------------------------------*/
/* Local Functions																				*/
/*----------------------------------------------------------------------------------------------*/
#if	( MCU_CFG_RESET_REASON == STD_ON )
/************************************************************************************************/
/* Function			:	Mcu_ResetInit															*/
/* Reentrancy		:	Re-entrant																*/
/* Parameters(in)	:	None																	*/
/* Return value		:	None																	*/
/* Limitation		:	None																	*/
/************************************************************************************************/
static FUNC( void, MCU_CODE ) Mcu_ResetInit( void )
{
	s_u4ResetRawValue = REG_RESET_AWO.u4RESF;			/* Save the reset factor */
	REG_RESET_ISO.u4RESFC = MCU_CLEAR_RESET_FACTOR;		/* Clear the reset factor register */
}
#endif	/* ( MCU_CFG_RESET_REASON == STD_ON ) */

#if	( MCU_CFG_INIT_CLOCK == STD_ON )
/************************************************************************************************/
/* Function			:	Mcu_ClockUpStart														*/
/* Reentrancy		:	Re-entrant																*/
/* Parameters(in)	:	None																	*/
/* Return value		:	Std_ReturnType															*/
/* Limitation		:	None																	*/
/************************************************************************************************/
static FUNC( Std_ReturnType, MCU_CODE ) Mcu_ClockUpStart( void )
{
	sint32 i;
	Std_ReturnType t_udResult;

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
	sint32 t_s4Count;
#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) */

	if ( ( REG_CLOCK_AWO.u4MOSCS & MCU_MOSCS_MASK ) == MCU_MOSCS_STOPPED )		/* Confirm that MainOSC is stopped */
	{
		REG_CLOCK_AWO.u4MOSCE = MCU_MOSCE_MOSCENTRG_START;						/* Start the MainOSC */
	}

	t_udResult = E_NOT_OK;
	for( i = 0; i < MCU_TIMEOUT_COUNT_MOSC_STABLE; i++ )
	{
		if( ( REG_CLOCK_AWO.u4MOSCS & MCU_MOSCS_MASK ) == MCU_MOSCS_STABLE )
		{
			t_udResult = E_OK;
			break;
		}
	}

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
	if ( t_udResult == E_OK )
	{
		for ( t_s4Count = 0; t_s4Count < MCU_PLL_READ_STABLE_TIMES; t_s4Count++ )	/* Read MainOSC stable state 4 times */
		{
			if ( ( REG_CLOCK_AWO.u4MOSCS & CLOCK_MOSCS_MOSCSTAB ) != MCU_MOSCS_MOSCSTAB_STABLE )
			{
				t_udResult = E_NOT_OK;
				break;
			}
		}
	}

	if ( t_udResult == E_OK )
	{
		if ( ( REG_CLOCK_ISO.u4PLLS & MCU_PLLS_MASK) == MCU_PLLS_STOPPED )		/* Confirm that PLL is stopped */
		{
			REG_CLOCK_ISO.u4PLLE = MCU_PLLE_PLLENTRG_STARTPLL;					/* Start the PLL */
		}
	}
#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) */

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
	if ( t_udResult == E_OK )
	{
		if ( ( REG_CLOCK_ISO.u4PLLS & MCU_PLLS_MASK ) == MCU_PLLS_STOPPED )		/* Confirm that SSCG is stopped */
		{
			REG_CLOCK_ISO.u4PLLE = MCU_PLLE_PLLENTRG_STARTPLL;					/* Start the SSCG */
		}

#if	( MCU_CFG_CLK_SSCG_SSMODE1_TYPE_0 == STD_ON )
		REG_CLOCK_ISO.u4SSCGC &= ~MCU_SSCGC_SSMODE1_BITPOS;											/* SSCG Control modulation disabled */
		MCAL_LIB_Wait( MCU_WAIT_SSCG_STABLE_TIME_INIT );											/* Wait at least 200 microseconds */
		REG_CLOCK_ISO.u4SSCGC = ( MCU_CFG_CLK_SSCG_FREQ_TYPE_0 * CLOCK_SSCGC_SELMFREQ_0 )
							  + ( MCU_CFG_CLK_SSCG_PERCENT_TYPE_0 * CLOCK_SSCGC_SELMPERCENT_0 );	/* Initialize SSCG modulation frequency and dithered range */
		REG_CLOCK_ISO.u4SSCGC |= MCU_SSCGC_SSMODE1_BITPOS;											/* SSCG Control modulation enabled */
#endif	/* ( MCU_CFG_CLK_SSCG_SSMODE1_TYPE_0 == STD_ON ) */
	}
#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B ) */

	return ( t_udResult );
}
#endif	/* ( MCU_CFG_INIT_CLOCK == STD_ON ) */

#if	( MCU_CFG_INIT_CLOCK == STD_ON )
/************************************************************************************************/
/* Function			:	Mcu_ClockSetupPeri														*/
/* Reentrancy		:	Re-entrant																*/
/* Parameters(in)	:	None																	*/
/* Return value		:	Std_ReturnType															*/
/* Limitation		:	None																	*/
/************************************************************************************************/
static FUNC( Std_ReturnType, MCU_CODE ) Mcu_ClockSetupPeri( void )
{
	const Mcu_ClockRegisterSettingType* t_pstSetTbl;
	sint32 t_s4Count;
	Std_ReturnType t_udResult;

	/*-------------------------------------------*/
	/* Initialize clock selector/divider control */
	/*-------------------------------------------*/
	for( t_s4Count = 0; t_s4Count < (sint32)MCU_NUM_CLK_REG_SET_TBL; t_s4Count++ )
	{
		t_pstSetTbl = &stMcu_ClockRegisterSettingTbl[t_s4Count];
		t_udResult = Mcu_SetClockRegister( t_pstSetTbl->pu4ControlReg, t_pstSetTbl->pu4StatusReg, t_pstSetTbl->u4SetValue, t_pstSetTbl->s4TimeoutCnt );
		if( t_udResult != E_OK )
		{
			/* Clock Setting Fail */
			break;
		}
	}

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
	/*-------------------------------------------*/
	/* Initialize FOUT0 clock selector/divider   */
	/*-------------------------------------------*/
	if ( t_udResult == E_OK )
	{
		/* Set CKSC_FOUT only if the config setting is different from the current value, because FOUT must be stopped once when changing CKSC_FOUT. */
		if ( REG_CLOCK_AWO.u4CKSC_FOUT0S != ( MCU_CFG_CLK_FOUT0C_TYPE_0 * CLOCK_CKSC_FOUT0S_FOUT0SACT_0 ) )
		{
			t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_AWO.u4CLKD_FOUT0S, CLOCK_CLKD_FOUT0S_FOUT0SYNC, MCU_FOUT0S_STABLE, MCU_PROCESS_TIME_OUT_PRE_FOUT );

			if ( t_udResult == E_OK )
			{
				REG_CLOCK_AWO.u4CLKD_FOUT0C = MCU_FOUT0C_STOPPED;		/* Stop the FOUT clock once before operating CKSC_FOUT */
				t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_AWO.u4CLKD_FOUT0S, ( CLOCK_CLKD_FOUT0S_FOUT0CLKACT + CLOCK_CLKD_FOUT0S_FOUT0SYNC ), MCU_FOUT0S_STOP_STABLE, MCU_PROCESS_TIME_OUT_PRE_FOUT );
			}

			if ( t_udResult == E_OK )
			{
				REG_CLOCK_AWO.u4CKSC_FOUT0C = ( MCU_CFG_CLK_FOUT0C_TYPE_0 * CLOCK_CKSC_FOUT0C_FOUT0SCSID_0 );
				t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_AWO.u4CKSC_FOUT0S, CLOCK_CKSC_FOUT0S_FOUT0SACT, MCU_CFG_CLK_FOUT0C_TYPE_0 * CLOCK_CKSC_FOUT0S_FOUT0SACT_0, MCU_PROCESS_TIME_OUT_PERI );
			}
		}
	}

	/*-------------------------------------------*/
	/* Initialize FOUT1 clock selector/divider   */
	/*-------------------------------------------*/
	if ( t_udResult == E_OK )
	{
		/* Set CKSC_FOUT only if the config setting is different from the current value, because FOUT must be stopped once when changing CKSC_FOUT. */
		if ( REG_CLOCK_AWO.u4CKSC_FOUT1S != ( MCU_CFG_CLK_FOUT1C_TYPE_0 * CLOCK_CKSC_FOUT1S_FOUT1SACT_0 ) )
		{
			t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_AWO.u4CLKD_FOUT1S, CLOCK_CLKD_FOUT1S_FOUT1SYNC, MCU_FOUT1S_STABLE, MCU_PROCESS_TIME_OUT_PRE_FOUT );

			if ( t_udResult == E_OK )
			{
				REG_CLOCK_AWO.u4CLKD_FOUT1C = MCU_FOUT1C_STOPPED;		/* Stop the FOUT clock once before operating CKSC_FOUT */
				t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_AWO.u4CLKD_FOUT1S, ( CLOCK_CLKD_FOUT1S_FOUT1CLKACT + CLOCK_CLKD_FOUT1S_FOUT1SYNC ), MCU_FOUT1S_STOP_STABLE, MCU_PROCESS_TIME_OUT_PRE_FOUT );
			}

			if ( t_udResult == E_OK )
			{
				REG_CLOCK_AWO.u4CKSC_FOUT1C = ( MCU_CFG_CLK_FOUT1C_TYPE_0 * CLOCK_CKSC_FOUT1C_FOUT1SCSID_0 );
				t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_AWO.u4CKSC_FOUT1S, CLOCK_CKSC_FOUT1S_FOUT1SACT, MCU_CFG_CLK_FOUT1C_TYPE_0 * CLOCK_CKSC_FOUT1S_FOUT1SACT_0, MCU_PROCESS_TIME_OUT_PERI );
			}
		}
	}
#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) */

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
	/*--------------------------------------------*/
	/* Initialize EXTCLK0C clock selector/divider */
	/*--------------------------------------------*/
	if ( t_udResult == E_OK )
	{
		if ( REG_CLOCK_AWO.u4CKS_EXTCLK0S != ( MCU_CFG_CLK_EXTCLK0C_TYPE_0 * CLOCK_EXTCLK0SACT_0 ) )
		{
			 t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_AWO.u4CKD_EXTCLK0S, CLOCK_EXTCLK0SYNC, MCU_EXTCLK0S_STABLE, MCU_PROCESS_TIME_OUT_PRE_FOUT );

			if ( t_udResult == E_OK )
			{
				REG_CLOCK_AWO.u4CKD_EXTCLK0C = MCU_EXTCLK0C_STOPPED;	/* Stop the EXTCLK clock once before operating CKS_EXTCLK */
				t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_AWO.u4CKD_EXTCLK0S, ( CLOCK_EXTCLK0CLKACT + CLOCK_EXTCLK0SYNC ), MCU_EXTCLK0S_STOP_STABLE, MCU_PROCESS_TIME_OUT_PRE_FOUT );
			}

			if ( t_udResult == E_OK )
			{
				REG_CLOCK_AWO.u4CKS_EXTCLK0C = ( MCU_CFG_CLK_EXTCLK0C_TYPE_0 * CLOCK_EXTCLK0SCSID_0 );
				t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_AWO.u4CKS_EXTCLK0S, CLOCK_EXTCLK0SACT, MCU_CFG_CLK_EXTCLK0C_TYPE_0 * CLOCK_EXTCLK0SACT_0, MCU_PROCESS_TIME_OUT_PERI );
			}
		}

		if ( REG_CLOCK_AWO.u4CKS_EXTCLK1S != ( MCU_CFG_CLK_EXTCLK1C_TYPE_0 * CLOCK_EXTCLK1SACT_0 ) )
		{
			if ( t_udResult == E_OK )
			{
				t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_AWO.u4CKD_EXTCLK1S, CLOCK_EXTCLK1SYNC, MCU_EXTCLK1S_STABLE, MCU_PROCESS_TIME_OUT_PRE_FOUT );
			}

			if ( t_udResult == E_OK )
			{
				REG_CLOCK_AWO.u4CKD_EXTCLK1C = MCU_EXTCLK1C_STOPPED;	/* Stop the EXTCLK clock once before operating CKS_EXTCLK */
				t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_AWO.u4CKD_EXTCLK1S, ( CLOCK_EXTCLK0CLKACT + CLOCK_EXTCLK1SYNC ), MCU_EXTCLK1S_STOP_STABLE, MCU_PROCESS_TIME_OUT_PRE_FOUT );
			}

			if ( t_udResult == E_OK )
			{
				REG_CLOCK_AWO.u4CKS_EXTCLK1C = ( MCU_CFG_CLK_EXTCLK1C_TYPE_0 * CLOCK_EXTCLK1SCSID_0 );
				t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_AWO.u4CKS_EXTCLK1S, CLOCK_EXTCLK1SACT, MCU_CFG_CLK_EXTCLK1C_TYPE_0 * CLOCK_EXTCLK1SACT_0, MCU_PROCESS_TIME_OUT_PERI );
			}
		}
	}
#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B ) */

	return ( t_udResult );
}
#endif	/* ( MCU_CFG_INIT_CLOCK == STD_ON ) */

#if	( MCU_CFG_NO_PLL == FALSE )
/************************************************************************************************/
/* Function			:	Mcu_ClockDistributePll													*/
/* Reentrancy		:	Re-entrant																*/
/* Parameters(in)	:	None																	*/
/* Return value		:	Std_ReturnType															*/
/* Limitation		:	None																	*/
/************************************************************************************************/
static FUNC( Std_ReturnType, MCU_CODE ) Mcu_ClockDistributePll( void )
{
	Std_ReturnType t_udResult;

	/*------------------------------------------------------------------------*/
	/* Check the synchronized divider clock before setting frequency division */
	/*------------------------------------------------------------------------*/
#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
	t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_ISO.u4CLKD_PLLS, CLOCK_CLKD_PLLS_PLLCLKDSYNC, MCU_PLL_SYNC, MCU_PROCESS_TIME_OUT_PERI );

#elif	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
	t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_ISO.u4CKD_PLLS, CLOCK_CKD_PLLS_PLLCLKDSYNC, MCU_PLL_SYNC, MCU_PROCESS_TIME_OUT_PERI );
	if ( t_udResult == E_OK )
	{
		t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_ISO.u4CKD_SSCGS, CLOCK_CKD_SSCGS_SSCGCLKDSYNC, MCU_SSCG_SYNC, MCU_PROCESS_TIME_OUT_PERI );
	}
#endif	/* MCAL_SPAL_TARGET */

	/*----------------------------------------------------------*/
	/* Initialize the clock divider and change the clock source */
	/*----------------------------------------------------------*/
	if ( t_udResult == E_OK )
	{
		t_udResult = Mcu_ClockControlPll();							/* Change the clock source for CPU */
	}

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
	if ( t_udResult == E_OK )
	{
		t_udResult = Mcu_ClockUpSscg();								/* Divide the SSCG clock step by step */
	}

	if ( t_udResult == E_OK )
	{
		t_udResult = Mcu_ClockUpPll();								/* Divide the PLL clock step by step */
	}
#endif	/* MCAL_SPAL_TARGET */

	return ( t_udResult );
}
#endif	/* ( MCU_CFG_NO_PLL == FALSE ) */

#if	( MCU_CFG_NO_PLL == FALSE )
/************************************************************************************************/
/* Function			:	Mcu_ClockControlPll														*/
/* Reentrancy		:	Re-entrant																*/
/* Parameters(in)	:	None																	*/
/* Return value		:	Std_ReturnType															*/
/* Limitation		:	None																	*/
/************************************************************************************************/
static FUNC( Std_ReturnType, MCU_CODE ) Mcu_ClockControlPll( void )
{
	Std_ReturnType t_udResult;

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
	REG_CLOCK_ISO.u4CLKD_PLLC = MCU_CLK_SYS_PLL_2;					/* Division ratio of clock source PLL is changed from 1/1 to 1/2 */
	t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_ISO.u4CLKD_PLLS, CLOCK_CLKD_PLLS_PLLCLKDSYNC, MCU_PLL_SYNC, MCU_PROCESS_TIME_OUT_PERI );

	if ( t_udResult == E_OK )
	{
		REG_CLOCK_ISO.u4CKSC_CPUC = MCU_CKSC_CPUC_CPUCLKSCSID_PLLO;	/* The clock source for the system clock is changed from IOSC to PLLO */
		t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_ISO.u4CKSC_CPUS, CLOCK_CKSC_CPUS_CPUCLKSACT, MCU_CPU_SACT, MCU_PROCESS_TIME_OUT_PERI );
	}

	if ( t_udResult == E_OK )
	{
		MCAL_LIB_Wait( MCU_WAIT_PLL_STABLE_TIME_1_2_PLL );			/* Wait at least 100 microseconds ( Since the PLL is 1/2, it takes twice as long ) */
		REG_CLOCK_ISO.u4CLKD_PLLC = MCU_CLK_SYS_PLL_1;				/* Division ratio of clock source PLL is changed from 1/2 to 1/1 */
		t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_ISO.u4CLKD_PLLS, CLOCK_CLKD_PLLS_PLLCLKDSYNC, MCU_PLL_SYNC, MCU_PROCESS_TIME_OUT_PERI );
	}

	if ( t_udResult == E_OK )
	{
		MCAL_LIB_Wait( MCU_WAIT_PLL_STABLE_TIME );					/* Wait at least 100 microseconds */
	}

#elif	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
	REG_CLOCK_ISO.u4CKD_PLLC = MCU_CLK_PLLO_6_16;					/* Division ratio of clock source PLL/SSCG is changed from 1/1 to 3/8 */
	REG_CLOCK_ISO.u4CKD_SSCGC = MCU_CLK_SSCGO_6_16;

	t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_ISO.u4CKD_PLLS, CLOCK_CKD_PLLS_PLLCLKDSYNC, MCU_PLL_SYNC, MCU_PROCESS_TIME_OUT_PERI );	/* Check the divider status */

	if ( t_udResult == E_OK )
	{
		t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_ISO.u4CKD_SSCGS, CLOCK_CKD_SSCGS_SSCGCLKDSYNC, MCU_SSCG_SYNC, MCU_PROCESS_TIME_OUT_PERI );
	}

	if ( t_udResult == E_OK )
	{
		REG_CLOCK_ISO.u4CKS_SSCGC = MCU_CKS_SSCGC_SYSCLKSC_SSCGO;	/* The clock source for the system clock is changed from IOSC to PLLO/SSCGO */
		REG_CLOCK_ISO.u4CKS_CLEANC = MCU_CKS_CLEANC_SYSCLKSC_PLLO;
		t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_ISO.u4CKS_CLEANS, CLOCK_CKS_CLEANS_SYSCLKSACT, MCU_CLEAN_SACT, MCU_PROCESS_TIME_OUT_PERI );
	}

	if ( t_udResult == E_OK )
	{
		t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_ISO.u4CKS_SSCGS, CLOCK_CKS_SSCGS_SYSCLKSACT, MCU_SSCG_SACT, MCU_PROCESS_TIME_OUT_PERI );
	}
#endif	/* MCAL_SPAL_TARGET */

	return ( t_udResult );
}

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
/************************************************************************************************/
/* Function			:	Mcu_ClockUpSscg															*/
/* Reentrancy		:	Re-entrant																*/
/* Parameters(in)	:	None																	*/
/* Return value		:	Std_ReturnType															*/
/* Limitation		:	None																	*/
/************************************************************************************************/
static FUNC( Std_ReturnType, MCU_CODE ) Mcu_ClockUpSscg( void )
{
	Std_ReturnType t_udResult;

	MCAL_LIB_Wait( MCU_WAIT_SSCG_STABLE_TIME_6_16 );			/* Wait at least 100 microseconds ( Since the PLL/SSCG is 6/16, it takes 16/6 as long ) */
	REG_CLOCK_ISO.u4CKD_SSCGC = MCU_CLK_SSCGO_8_16;
	t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_ISO.u4CKD_SSCGS, CLOCK_CKD_SSCGS_SSCGCLKDSYNC, MCU_SSCG_SYNC, MCU_PROCESS_TIME_OUT_PERI );

	if ( t_udResult == E_OK )
	{
		MCAL_LIB_Wait( MCU_WAIT_SSCG_STABLE_TIME_8_16 );
		REG_CLOCK_ISO.u4CKD_SSCGC = MCU_CLK_SSCGO_10_16;
		t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_ISO.u4CKD_SSCGS, CLOCK_CKD_SSCGS_SSCGCLKDSYNC, MCU_SSCG_SYNC, MCU_PROCESS_TIME_OUT_PERI );
	}

	if ( t_udResult == E_OK )
	{
		MCAL_LIB_Wait( MCU_WAIT_SSCG_STABLE_TIME_10_16 );
		REG_CLOCK_ISO.u4CKD_SSCGC = MCU_CLK_SSCGO_12_16;
		t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_ISO.u4CKD_SSCGS, CLOCK_CKD_SSCGS_SSCGCLKDSYNC, MCU_SSCG_SYNC, MCU_PROCESS_TIME_OUT_PERI );
	}

	if ( t_udResult == E_OK )
	{
		MCAL_LIB_Wait( MCU_WAIT_SSCG_STABLE_TIME_12_16 );
		REG_CLOCK_ISO.u4CKD_SSCGC = MCU_CLK_SSCGO_14_16;
		t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_ISO.u4CKD_SSCGS, CLOCK_CKD_SSCGS_SSCGCLKDSYNC, MCU_SSCG_SYNC, MCU_PROCESS_TIME_OUT_PERI );
	}

	if ( t_udResult == E_OK )
	{
		MCAL_LIB_Wait( MCU_WAIT_SSCG_STABLE_TIME_14_16 );
		REG_CLOCK_ISO.u4CKD_SSCGC = MCU_CLK_SSCGO_16_16;
		t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_ISO.u4CKD_SSCGS, CLOCK_CKD_SSCGS_SSCGCLKDSYNC, MCU_SSCG_SYNC, MCU_PROCESS_TIME_OUT_PERI );
	}

	return ( t_udResult );
}

/************************************************************************************************/
/* Function			:	Mcu_ClockUpPll															*/
/* Reentrancy		:	Re-entrant																*/
/* Parameters(in)	:	None																	*/
/* Return value		:	Std_ReturnType															*/
/* Limitation		:	None																	*/
/************************************************************************************************/
static FUNC( Std_ReturnType, MCU_CODE ) Mcu_ClockUpPll( void )
{
	Std_ReturnType t_udResult;

	MCAL_LIB_Wait( MCU_WAIT_SSCG_STABLE_TIME_16_16 );
	REG_CLOCK_ISO.u4CKD_PLLC = MCU_CLK_PLLO_8_16;
	t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_ISO.u4CKD_PLLS, CLOCK_CKD_PLLS_PLLCLKDSYNC, MCU_PLL_SYNC, MCU_PROCESS_TIME_OUT_PERI );

	if ( t_udResult == E_OK )
	{
		MCAL_LIB_Wait( MCU_WAIT_SSCG_STABLE_TIME_16_16 );
		REG_CLOCK_ISO.u4CKD_PLLC = MCU_CLK_PLLO_10_16;
		t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_ISO.u4CKD_PLLS, CLOCK_CKD_PLLS_PLLCLKDSYNC, MCU_PLL_SYNC, MCU_PROCESS_TIME_OUT_PERI );
	}

	if ( t_udResult == E_OK )
	{
		MCAL_LIB_Wait( MCU_WAIT_SSCG_STABLE_TIME_16_16 );
		REG_CLOCK_ISO.u4CKD_PLLC = MCU_CLK_PLLO_12_16;
		t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_ISO.u4CKD_PLLS, CLOCK_CKD_PLLS_PLLCLKDSYNC, MCU_PLL_SYNC, MCU_PROCESS_TIME_OUT_PERI );
	}

	if ( t_udResult == E_OK )
	{
		MCAL_LIB_Wait( MCU_WAIT_SSCG_STABLE_TIME_16_16 );
		REG_CLOCK_ISO.u4CKD_PLLC = MCU_CLK_PLLO_14_16;
		t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_ISO.u4CKD_PLLS, CLOCK_CKD_PLLS_PLLCLKDSYNC, MCU_PLL_SYNC, MCU_PROCESS_TIME_OUT_PERI );
	}

	if ( t_udResult == E_OK )
	{
		MCAL_LIB_Wait( MCU_WAIT_SSCG_STABLE_TIME_16_16 );
		REG_CLOCK_ISO.u4CKD_PLLC = MCU_CLK_PLLO_16_16;
		t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_ISO.u4CKD_PLLS, CLOCK_CKD_PLLS_PLLCLKDSYNC, MCU_PLL_SYNC, MCU_PROCESS_TIME_OUT_PERI );
	}

	if ( t_udResult == E_OK )
	{
		MCAL_LIB_Wait( MCU_WAIT_SSCG_STABLE_TIME_16_16 );
	}

	return ( t_udResult );
}
#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B ) */
#endif	/* ( MCU_CFG_NO_PLL == FALSE ) */

#if	( MCU_CFG_NO_PLL == FALSE )
/************************************************************************************************/
/* Function			:	Mcu_ClockSetupFout														*/
/* Reentrancy		:	Re-entrant																*/
/* Parameters(in)	:	None																	*/
/* Return value		:	Std_ReturnType															*/
/* Limitation		:	None																	*/
/************************************************************************************************/
static FUNC( Std_ReturnType, MCU_CODE ) Mcu_ClockSetupFout( void )
{
	Std_ReturnType t_udResult;

	t_udResult = E_OK;

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
	if ( REG_CLOCK_AWO.u4CLKD_FOUT0C != ( MCU_CFG_CLKD_FOUT0C_TYPE_0 * CLOCK_CLKD_FOUT0C_FOUT0DIV_0 ) )
	{
		t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_AWO.u4CLKD_FOUT0S, CLOCK_CLKD_FOUT0S_FOUT0SYNC, MCU_FOUT0S_STABLE, MCU_PROCESS_TIME_OUT_POST_FOUT );

		if ( t_udResult == E_OK )
		{
			REG_CLOCK_AWO.u4CLKD_FOUT0C = ( MCU_CFG_CLKD_FOUT0C_TYPE_0 * CLOCK_CLKD_FOUT0C_FOUT0DIV_0 );
			t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_AWO.u4CLKD_FOUT0S, CLOCK_CLKD_FOUT0S_FOUT0SYNC, MCU_FOUT0S_STABLE, MCU_PROCESS_TIME_OUT_POST_FOUT );
		}
	}

	if ( REG_CLOCK_AWO.u4CLKD_FOUT1C != ( MCU_CFG_CLKD_FOUT1C_TYPE_0 * CLOCK_CLKD_FOUT1C_FOUT1DIV_0 ) )
	{
		if ( t_udResult == E_OK )
		{
			t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_AWO.u4CLKD_FOUT1S, CLOCK_CLKD_FOUT1S_FOUT1SYNC, MCU_FOUT1S_STABLE, MCU_PROCESS_TIME_OUT_POST_FOUT );
		}

		if ( t_udResult == E_OK )
		{
			REG_CLOCK_AWO.u4CLKD_FOUT1C = ( MCU_CFG_CLKD_FOUT1C_TYPE_0 * CLOCK_CLKD_FOUT1C_FOUT1DIV_0 );
			t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_AWO.u4CLKD_FOUT1S, CLOCK_CLKD_FOUT1S_FOUT1SYNC, MCU_FOUT1S_STABLE, MCU_PROCESS_TIME_OUT_POST_FOUT );
		}
	}
#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) */

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
	if ( REG_CLOCK_AWO.u4CKD_EXTCLK0C != ( MCU_CFG_CLKD_EXTCLK0C_TYPE_0 * CLOCK_CKD_EXTCLK0C_EXTCLK0DIV_0 ) )
	{
		t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_AWO.u4CKD_EXTCLK0S, CLOCK_EXTCLK0SYNC, MCU_EXTCLK0S_STABLE, MCU_PROCESS_TIME_OUT_POST_FOUT );

		if ( t_udResult == E_OK )
		{
			REG_CLOCK_AWO.u4CKD_EXTCLK0C = ( MCU_CFG_CLKD_EXTCLK0C_TYPE_0 * CLOCK_CKD_EXTCLK0C_EXTCLK0DIV_0 );
			t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_AWO.u4CKD_EXTCLK0S, CLOCK_EXTCLK0SYNC, MCU_EXTCLK0S_STABLE, MCU_PROCESS_TIME_OUT_POST_FOUT );
		}
	}

	if ( REG_CLOCK_AWO.u4CKD_EXTCLK1C != ( MCU_CFG_CLKD_EXTCLK1C_TYPE_0 * CLOCK_CKD_EXTCLK1C_EXTCLK1DIV_0 ) )
	{
		if ( t_udResult == E_OK )
		{
			t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_AWO.u4CKD_EXTCLK1S, CLOCK_EXTCLK1SYNC, MCU_EXTCLK1S_STABLE, MCU_PROCESS_TIME_OUT_POST_FOUT );
		}

		if ( t_udResult == E_OK )
		{
			REG_CLOCK_AWO.u4CKD_EXTCLK1C = ( MCU_CFG_CLKD_EXTCLK1C_TYPE_0 * CLOCK_CKD_EXTCLK1C_EXTCLK1DIV_0 );
			t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_AWO.u4CKD_EXTCLK1S, CLOCK_EXTCLK1SYNC, MCU_EXTCLK1S_STABLE, MCU_PROCESS_TIME_OUT_POST_FOUT );
		}
	}
#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B ) */

	return ( t_udResult );
}
#endif	/* ( MCU_CFG_NO_PLL == FALSE ) */

#if	( MCU_CFG_NO_PLL == FALSE )
/************************************************************************************************/
/* Function			:	Mcu_ClockSupplyPeri														*/
/* Reentrancy		:	Re-entrant																*/
/* Parameters(in)	:	None																	*/
/* Return value		:	Std_ReturnType															*/
/* Limitation		:	None																	*/
/************************************************************************************************/
static FUNC( Std_ReturnType, MCU_CODE ) Mcu_ClockSupplyPeri( void )
{
	sint32 t_s4Count;
	const Mcu_ModuleStandbyRegisterType* t_pstSetTbl;
	Std_ReturnType t_udResult;

	/*-----------------------------------------------------------------------------------------------------------*/
	/* In module standby mode, the clock is supplied from the PLL, so it is initialized after the PLL stabilizes */
	/*-----------------------------------------------------------------------------------------------------------*/
	for( t_s4Count = 0; t_s4Count < (sint32)MCU_NUM_MSR_REG_SET_TBL; t_s4Count++ )
	{
		t_pstSetTbl = &stMcu_ModuleStandbyRegisterSettingTbl[t_s4Count];
		*t_pstSetTbl->pu4ControlReg = t_pstSetTbl->u4SetValue;
	}

	/*----------------------------------------------------------------------------------*/
	/* Check the value to ensure the wait time until the module starts supplying clocks */
	/*----------------------------------------------------------------------------------*/
#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
	t_udResult = Mcu_ProcessTimeOut( &REG_STBC_AWO.u4MSR_ADCJ_AWO, ( MSR_ADCJ_AWO_MS_ADCJ_2 + MSR_ADCJ_AWO_STPMSK_ADCJ ),
		( MCU_CFG_MS_ADCJ_AWO_2_TYPE_0 * MSR_ADCJ_AWO_MS_ADCJ_2 ) + ( MCU_CFG_STPMSK_ADCJ_AWO_TYPE_0 * MSR_ADCJ_AWO_STPMSK_ADCJ ), MCU_PROCESS_TIME_OUT_PERI );

#elif ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
	t_udResult = Mcu_ProcessTimeOut( &REG_STBC_ISO.u4MSR_HRPWM, MSR_HRPWM_MS_HRPWM_0,
		( MCU_CFG_MS_HRPWM_0_TYPE_0 * MSR_HRPWM_MS_HRPWM_0 ), MCU_PROCESS_TIME_OUT_PERI );
#endif /* MCAL_SPAL_TARGET */

	return ( t_udResult );
}
#endif	/* ( MCU_CFG_NO_PLL == FALSE ) */

#if	( MCU_CFG_CLK_MONITOR == STD_ON )

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
#if	( MCU_CFG_CLMA3CLME == STD_ON )
/************************************************************************************************/
/* Function			:	Mcu_ClockMonitorReset													*/
/* Reentrancy		:	Re-entrant																*/
/* Parameters(in)	:	None																	*/
/* Return value		:	None																	*/
/* Limitation		:	None																	*/
/************************************************************************************************/
static FUNC( void, MCU_CODE ) Mcu_ClockMonitorReset( void )
{
	volatile uint32 t_u4DummyRead;

	REG_CLMAKCPROT.u4CLMAKCPROT = CLMA_CLMAKCPROT_ENABLE;		/* Enable writing to protected registers */

	/*---------------------*/
	/* Reset clock monitor */
	/*---------------------*/
	REG_CLMAC.u4CLMATEST = MCU_CLMATEST_CLMA3TESEN;
	REG_CLMAC.u4CLMATEST = MCU_CLMATEST_ERRMSK3;
	REG_CLMAC.u4CLMATEST = MCU_CLMATEST_RESET3;

	MCAL_LIB_Wait( MCU_CLMA_TIMER );							/* Wait at least 2 cycles on the corresponding sampling clock for CLMA3 */

	/*-----------------------------*/
	/* Release Reset clock monitor */
	/*-----------------------------*/
	REG_CLMAC.u4CLMATEST = MCU_CLMATEST_RELEASE_RESET3;
	REG_CLMAC.u4CLMATEST = MCU_CLMATEST_RELEASE_MASK3;
	REG_CLMAC.u4CLMATEST = MCU_CLMATEST_DISABLE;

	Reg_ECM_ECM->stECM.u4ECMKCPROT = ECM_PROTECT_KEY_ENABLE;
	Reg_ECM_ECM->stECM.u4ECMESSTC1 = MCU_ERROR51_BITPOS;
	t_u4DummyRead = Reg_ECM_ECM->stECM.u4ECMESSTC1;
	mcalcommon_syncp_func();
	Reg_ECM_ECM->stECM.u4ECMKCPROT = ECM_PROTECT_KEY_DISABLE;

	REG_CLMAKCPROT.u4CLMAKCPROT = CLMA_CLMAKCPROT_DISABLE;		/* Disable writing to protected registers */
}
#endif	/* ( MCU_CFG_CLMA3CLME == STD_ON ) */
#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) */

/************************************************************************************************/
/* Function			:	Mcu_ClockMonitorSetup													*/
/* Reentrancy		:	Re-entrant																*/
/* Parameters(in)	:	None																	*/
/* Return value		:	Std_ReturnType															*/
/* Limitation		:	None																	*/
/************************************************************************************************/
static FUNC( Std_ReturnType, MCU_CODE ) Mcu_ClockMonitorSetup( void )
{
	Std_ReturnType t_udResult;

#if ( ( MCU_CFG_CLMA0CLME == STD_ON ) || ( MCU_CFG_CLMA1CLME == STD_ON ) || ( MCU_CFG_CLMA2CLME == STD_ON ) )
	t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_AWO.u4HSOSCS, CLOCK_HSOSCS_HSOSCSTAB, MCU_HSOSCS_STABLE, MCU_PROCESS_TIME_OUT_OTHER );
#else
	t_udResult = E_OK;
#endif

	REG_CLMAKCPROT.u4CLMAKCPROT = CLMA_CLMAKCPROT_ENABLE;

	/*--------------------------------------*/
	/* Clock monitor enable/disable setting */
	/*--------------------------------------*/
#if	( MCU_CFG_CLMA0CLME == STD_ON )
	if ( ( REG_CLMA0.u1CLMA0CTL == CLMA_CLMAnCTL_CLMAnCLME_DISABLE ) && ( t_udResult == E_OK ) )
	{
		REG_CLMA0.u2CLMA0CMPL = MCU_CFG_CLMA0CMPL;
		REG_CLMA0.u2CLMA0CMPH = MCU_CFG_CLMA0CMPH;

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
#if	( MCU_CFG_CLMABCE == STD_ON )
		REG_CLMAC.u1CLMABCE = CLMA_CLMABCE_CLMABCE_ENABLE;			/* Enable the backup function of the clock monitor */
#else
		REG_CLMAC.u1CLMABCE = CLMA_CLMABCE_CLMABCE_DISABLE;			/* Disable the backup function of the clock monitor */
#endif	/* MCU_CFG_CLMABCE */
#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B ) */

		REG_CLMA0.u1CLMA0CTL = CLMA_CLMAnCTL_CLMAnCLME_ENABLE;
	}

#else	/* ( MCU_CFG_CLMA0CLME == STD_OFF ) */
	REG_CLMA0.u1CLMA0CTL = CLMA_CLMAnCTL_CLMAnCLME_DISABLE;
#endif	/* ( MCU_CFG_CLMA0CLME == STD_ON ) */

#if	( MCU_CFG_CLMA1CLME == STD_ON )
	if ( ( REG_CLMA1.u1CLMA1CTL == CLMA_CLMAnCTL_CLMAnCLME_DISABLE ) && ( t_udResult == E_OK ) )
	{
		REG_CLMA1.u2CLMA1CMPL = MCU_CFG_CLMA1CMPL;
		REG_CLMA1.u2CLMA1CMPH = MCU_CFG_CLMA1CMPH;
		REG_CLMA1.u1CLMA1CTL = CLMA_CLMAnCTL_CLMAnCLME_ENABLE;
	}
#else	/* ( MCU_CFG_CLMA1CLME == STD_OFF ) */
	REG_CLMA1.u1CLMA1CTL = CLMA_CLMAnCTL_CLMAnCLME_DISABLE;
#endif	/* ( MCU_CFG_CLMA1CLME == STD_ON ) */

#if	( MCU_CFG_CLMA2CLME == STD_ON )
	if ( ( REG_CLMA2.u1CLMA2CTL == CLMA_CLMAnCTL_CLMAnCLME_DISABLE ) && ( t_udResult == E_OK ) )
	{
		REG_CLMA2.u2CLMA2CMPL = MCU_CFG_CLMA2CMPL;
		REG_CLMA2.u2CLMA2CMPH = MCU_CFG_CLMA2CMPH;
		REG_CLMA2.u1CLMA2CTL = CLMA_CLMAnCTL_CLMAnCLME_ENABLE;
	}
#else	/* ( MCU_CFG_CLMA2CLME == STD_OFF ) */
	REG_CLMA2.u1CLMA2CTL = CLMA_CLMAnCTL_CLMAnCLME_DISABLE;
#endif	/* ( MCU_CFG_CLMA2CLME == STD_ON ) */

#if	( MCU_CFG_CLMA3CLME == STD_ON )
	REG_CLMA3.u2CLMA3CMPL = MCU_CFG_CLMA3CMPL;
	REG_CLMA3.u2CLMA3CMPH = MCU_CFG_CLMA3CMPH;

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
#if	( MCU_CFG_CLMABCE == STD_ON )
		REG_CLMAC.u1CLMABCE = CLMA_CLMABCE_CLMABCE_ENABLE;			/* Enable the backup function of the clock monitor */
#else
		REG_CLMAC.u1CLMABCE = CLMA_CLMABCE_CLMABCE_DISABLE;			/* Disable the backup function of the clock monitor */
#endif	/* MCU_CFG_CLMABCE */

	REG_CLMA3.u1CLMA3STPDTEN = CLMA_CLMAnSTPDTEN_DISABLE;

#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B ) */

	REG_CLMA3.u1CLMA3CTL = CLMA_CLMAnCTL_CLMAnCLME_ENABLE;

#else	/* ( MCU_CFG_CLMA3CLME == STD_OFF ) */
	REG_CLMA3.u1CLMA3CTL = CLMA_CLMAnCTL_CLMAnCLME_DISABLE;
#endif	/* ( MCU_CFG_CLMA3CLME == STD_ON ) */

	REG_CLMA4.u1CLMA4CTL = CLMA_CLMAnCTL_CLMAnCLME_DISABLE;

#if	( MCU_CFG_CLMA5CLME == STD_ON )
	REG_CLMA5.u2CLMA5CMPL = MCU_CFG_CLMA5CMPL;
	REG_CLMA5.u2CLMA5CMPH = MCU_CFG_CLMA5CMPH;
	REG_CLMA5.u1CLMA5CTL = CLMA_CLMAnCTL_CLMAnCLME_ENABLE;
#else	/* ( MCU_CFG_CLMA5CLME == STD_OFF ) */
	REG_CLMA5.u1CLMA5CTL = CLMA_CLMAnCTL_CLMAnCLME_DISABLE;
#endif	/* ( MCU_CFG_CLMA5CLME == STD_ON ) */

#if	( MCU_CFG_CLMA6CLME == STD_ON )
	REG_CLMA6.u2CLMA6CMPL = MCU_CFG_CLMA6CMPL;
	REG_CLMA6.u2CLMA6CMPH = MCU_CFG_CLMA6CMPH;

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
	REG_CLMA6.u1CLMA6STPDTEN = CLMA_CLMAnSTPDTEN_DISABLE;
#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B ) */

	REG_CLMA6.u1CLMA6CTL = CLMA_CLMAnCTL_CLMAnCLME_ENABLE;

#else	/* ( MCU_CFG_CLMA6CLME == STD_OFF ) */
	REG_CLMA6.u1CLMA6CTL = CLMA_CLMAnCTL_CLMAnCLME_DISABLE;
#endif	/* ( MCU_CFG_CLMA6CLME == STD_ON ) */

#if	( MCU_CFG_CLMA7CLME == STD_ON )
	REG_CLMA7.u2CLMA7CMPL = MCU_CFG_CLMA7CMPL;
	REG_CLMA7.u2CLMA7CMPH = MCU_CFG_CLMA7CMPH;

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
	REG_CLMA7.u1CLMA7STPDTEN = CLMA_CLMAnSTPDTEN_DISABLE;
#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B ) */

	REG_CLMA7.u1CLMA7CTL = CLMA_CLMAnCTL_CLMAnCLME_ENABLE;

#else	/* ( MCU_CFG_CLMA7CLME == STD_OFF ) */
	REG_CLMA7.u1CLMA7CTL = CLMA_CLMAnCTL_CLMAnCLME_DISABLE;
#endif	/* ( MCU_CFG_CLMA7CLME == STD_ON ) */

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
#if	( ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A16_516PIN ) || ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A16_373PIN ) )
#if	( MCU_CFG_CLMA8CLME == STD_ON )
	REG_CLMA8.u2CLMA8CMPL = MCU_CFG_CLMA8CMPL;
	REG_CLMA8.u2CLMA8CMPH = MCU_CFG_CLMA8CMPH;
	REG_CLMA8.u1CLMA8CTL = CLMA_CLMAnCTL_CLMAnCLME_ENABLE;
#else	/* ( MCU_CFG_CLMA8CLME == STD_OFF ) */
	REG_CLMA8.u1CLMA8CTL = CLMA_CLMAnCTL_CLMAnCLME_DISABLE;
#endif	/* ( MCU_CFG_CLMA8CLME == STD_ON ) */

#if	( MCU_CFG_CLMA9CLME == STD_ON )
	REG_CLMA9.u2CLMA9CMPL = MCU_CFG_CLMA9CMPL;
	REG_CLMA9.u2CLMA9CMPH = MCU_CFG_CLMA9CMPH;
	REG_CLMA9.u1CLMA9CTL = CLMA_CLMAnCTL_CLMAnCLME_ENABLE;
#else	/* ( MCU_CFG_CLMA9CLME == STD_OFF ) */
	REG_CLMA9.u1CLMA9CTL = CLMA_CLMAnCTL_CLMAnCLME_DISABLE;
#endif	/* ( MCU_CFG_CLMA9CLME == STD_ON ) */
#endif	/* ( ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A16_516PIN ) || ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A16_373PIN ) ) */
#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) */

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
#if	( MCU_CFG_CLMA13CLME == STD_ON )
	REG_CLMA13.u2CLMA13CMPL = MCU_CFG_CLMA13CMPL;
	REG_CLMA13.u2CLMA13CMPH = MCU_CFG_CLMA13CMPH;
	REG_CLMA13.u1CLMA13STPDTEN = CLMA_CLMAnSTPDTEN_DISABLE;
	REG_CLMA13.u1CLMA13CTL = CLMA_CLMAnCTL_CLMAnCLME_ENABLE;

#else	/* ( MCU_CFG_CLMA13CLME == STD_OFF ) */
	REG_CLMA13.u1CLMA13CTL = CLMA_CLMAnCTL_CLMAnCLME_DISABLE;
#endif	/* ( MCU_CFG_CLMA13CLME == STD_ON ) */

#if	( MCU_CFG_CLMA14CLME == STD_ON )
	REG_CLMA14.u2CLMA14CMPL = MCU_CFG_CLMA14CMPL;
	REG_CLMA14.u2CLMA14CMPH = MCU_CFG_CLMA14CMPH;
	REG_CLMA14.u1CLMA14CTL = CLMA_CLMAnCTL_CLMAnCLME_ENABLE;
#else	/* ( MCU_CFG_CLMA14CLME == STD_OFF ) */
	REG_CLMA14.u1CLMA14CTL = CLMA_CLMAnCTL_CLMAnCLME_DISABLE;
#endif	/* ( MCU_CFG_CLMA14CLME == STD_ON ) */

#if	( MCU_CFG_CLMA15CLME == STD_ON )
	REG_CLMA15.u2CLMA15CMPL = MCU_CFG_CLMA15CMPL;
	REG_CLMA15.u2CLMA15CMPH = MCU_CFG_CLMA15CMPH;

#if	( MCU_CFG_CLMABCE == STD_ON )
		REG_CLMAC.u1CLMABCE = CLMA_CLMABCE_CLMABCE_ENABLE;			/* Enable the backup function of the clock monitor */
#else
		REG_CLMAC.u1CLMABCE = CLMA_CLMABCE_CLMABCE_DISABLE;			/* Disable the backup function of the clock monitor */
#endif	/* MCU_CFG_CLMABCE */

	REG_CLMA15.u1CLMA15CTL = CLMA_CLMAnCTL_CLMAnCLME_ENABLE;

#else	/* ( MCU_CFG_CLMA15CLME == STD_OFF ) */
	REG_CLMA15.u1CLMA15CTL = CLMA_CLMAnCTL_CLMAnCLME_DISABLE;
#endif	/* ( MCU_CFG_CLMA15CLME == STD_ON ) */

#if	( MCU_CFG_CLMA16CLME == STD_ON )
	REG_CLMA16.u2CLMA16CMPL = MCU_CFG_CLMA16CMPL;
	REG_CLMA16.u2CLMA16CMPH = MCU_CFG_CLMA16CMPH;
	REG_CLMA16.u1CLMA16STPDTEN = CLMA_CLMAnSTPDTEN_DISABLE;
	REG_CLMA16.u1CLMA16CTL = CLMA_CLMAnCTL_CLMAnCLME_ENABLE;

#else	/* ( MCU_CFG_CLMA16CLME == STD_OFF ) */
	REG_CLMA16.u1CLMA16CTL = CLMA_CLMAnCTL_CLMAnCLME_DISABLE;
#endif	/* ( MCU_CFG_CLMA16CLME == STD_ON ) */

#if	( MCU_CFG_CLMA17CLME == STD_ON )
	REG_CLMA17.u2CLMA17CMPL = MCU_CFG_CLMA17CMPL;
	REG_CLMA17.u2CLMA17CMPH = MCU_CFG_CLMA17CMPH;
	REG_CLMA17.u1CLMA17CTL = CLMA_CLMAnCTL_CLMAnCLME_ENABLE;
#else	/* ( MCU_CFG_CLMA17CLME == STD_OFF ) */
	REG_CLMA17.u1CLMA17CTL = CLMA_CLMAnCTL_CLMAnCLME_DISABLE;
#endif	/* ( MCU_CFG_CLMA17CLME == STD_ON ) */
#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B ) */

	REG_CLMAKCPROT.u4CLMAKCPROT = CLMA_CLMAKCPROT_DISABLE;		/* Disable writing to protected registers */

	return ( t_udResult );
}
#endif	/* ( MCU_CFG_CLK_MONITOR == STD_ON ) */

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )

#if	( MCU_CFG_CLK_MONITOR == STD_ON )
/************************************************************************************************/
/* Function			:	Mcu_ClockMonitorStandby													*/
/* Reentrancy		:	Re-entrant																*/
/* Parameters(in)	:	None																	*/
/* Return value		:	None																	*/
/* Limitation		:	None																	*/
/************************************************************************************************/
static FUNC( void, MCU_CODE ) Mcu_ClockMonitorStandby( void )
{
	REG_CLMAKCPROT.u4CLMAKCPROT = CLMA_CLMAKCPROT_ENABLE;		/* Enable writing to protected registers */

	/*-------------------------*/
	/* Reset CLMAn in ISO area */
	/*-------------------------*/
	REG_CLMAC.u4CLMATEST = MCU_CLMATEST_ENABLE_ISO;
	REG_CLMAC.u4CLMATEST = MCU_CLMATEST_ERRMSK_ISO;
	REG_CLMAC.u4CLMATEST = MCU_CLMATEST_RESET_ISO;

	MCAL_LIB_Wait( MCU_CLMA_TIMER );		/* Wait at least 2 cycles on the corresponding sampling clock */

	/*---------------------------------*/
	/* Release CLMAn Reset in ISO area */
	/*---------------------------------*/
	REG_CLMAC.u4CLMATEST = MCU_CLMATEST_RELEASE_RESET_ISO;
	REG_CLMAC.u4CLMATEST = MCU_CLMATEST_RELEASE_MASK_ISO;
	REG_CLMAC.u4CLMATEST = MCU_CLMATEST_DISABLE;

	REG_CLMAKCPROT.u4CLMAKCPROT = CLMA_CLMAKCPROT_DISABLE;		/* Disable writing to protected registers */
}
#endif	/* ( MCU_CFG_CLK_MONITOR == STD_ON ) */

#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) */

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
/************************************************************************************************/
/* Function			:	Mcu_StandbyClockDown													*/
/* Reentrancy		:	Re-entrant																*/
/* Parameters(in)	:	None																	*/
/* Return value		:	Std_ReturnType															*/
/* Limitation		:	None																	*/
/************************************************************************************************/
static FUNC( Std_ReturnType, MCU_CODE ) Mcu_StandbyClockDown( void )
{
	Std_ReturnType t_udResult;

	t_udResult = E_OK;

	REG_CLOCK_AWO.u4MOSCSTPM = ( MCU_CFG_STPMSK_MOSC_TYPE_0		* CLOCK_MOSCSTPM_MOSCSTPMSK );		/* Main OSC stops operation in chip standby mode */
	REG_CLOCK_AWO.u4HSOSCSTPM = ( MCU_CFG_STPMSK_HSIOSC_TYPE_0	* CLOCK_HSOSCSTPM_HSOSCSTPMSK );	/* HS IntOSC stops operation in chip standby mode */

#if ( MCU_CFG_REG_CHK == STD_ON )
	if ( ( REG_CLOCK_AWO.u4MOSCSTPM & CLOCK_MOSCSTPM_MOSCSTPMSK ) != ( ( MCU_CFG_STPMSK_MOSC_TYPE_0 * CLOCK_MOSCSTPM_MOSCSTPMSK ) & CLOCK_MOSCSTPM_MOSCSTPMSK )
	  || ( REG_CLOCK_AWO.u4HSOSCSTPM & CLOCK_HSOSCSTPM_HSOSCSTPMSK ) != ( ( MCU_CFG_STPMSK_HSIOSC_TYPE_0 * CLOCK_HSOSCSTPM_HSOSCSTPMSK ) & CLOCK_HSOSCSTPM_HSOSCSTPMSK ) )
	{
		t_udResult = E_NOT_OK;
	}
#endif

#if ( MCU_CFG_REG_CHK == STD_ON )
	if ( t_udResult == E_OK )
	{
#endif
		if ( REG_CLOCK_ISO.u4CLKD_PLLC == MCU_CLK_SYS_PLL_1 )
		{
			t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_ISO.u4CLKD_PLLS, CLOCK_CLKD_PLLS_PLLCLKDSYNC, MCU_PLL_SYNC, MCU_PROCESS_TIME_OUT_PERI );

			if ( t_udResult == E_OK )
			{
				REG_CLOCK_ISO.u4CLKD_PLLC = MCU_CLK_SYS_PLL_2;		/* Change the clock divider of the PLL to 1/2 */
				t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_ISO.u4CLKD_PLLS, CLOCK_CLKD_PLLS_PLLCLKDSYNC, MCU_PLL_SYNC, MCU_PROCESS_TIME_OUT_PERI );
			}

			if ( t_udResult == E_OK )
			{
				MCAL_LIB_Wait( MCU_WAIT_PLL_STABLE_TIME_1_2_PLL );			/* Wait at least 100 microseconds */
			}
		}
#if ( MCU_CFG_REG_CHK == STD_ON )
	}
#endif

	return ( t_udResult );
}
#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) */

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
/************************************************************************************************/
/* Function			:	Mcu_StandbyPeri															*/
/* Reentrancy		:	Re-entrant																*/
/* Parameters(in)	:	None																	*/
/* Return value		:	Std_ReturnType															*/
/* Limitation		:	None																	*/
/************************************************************************************************/
static FUNC( Std_ReturnType, MCU_CODE ) Mcu_StandbyPeri( void )
{
	Std_ReturnType t_udResult;
	sint32 t_s4Count;
	const Mcu_ClockRegisterSettingType* t_pstSetTbl;

	t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_ISO.u4PLLS, CLOCK_PLLS_PLLCLKSTAB, MCU_PLLS_PLLCLKSTAB_STABLE, MCU_PROCESS_TIME_OUT_PERI );

	if ( t_udResult == E_OK )
	{
		t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_AWO.u4MOSCS, ( CLOCK_MOSCS_MOSCEN + CLOCK_MOSCS_MOSCSTAB ), MCU_MOSCS_STABLE, MCU_PROCESS_TIME_OUT_OTHER );
	}

	if ( t_udResult == E_OK )
	{
		/*--------------------------------------------------*/
		/* Set clock source before transition to sleep mode */
		/*--------------------------------------------------*/
		for( t_s4Count = 0; t_s4Count < (sint32)MCU_NUM_CLK_SLEEP_REG_SET_TBL; t_s4Count++ )
		{
			t_pstSetTbl = &stMcu_SleepClockRegisterSettingTbl[t_s4Count];
			t_udResult = Mcu_SetClockRegister( t_pstSetTbl->pu4ControlReg, t_pstSetTbl->pu4StatusReg, t_pstSetTbl->u4SetValue, t_pstSetTbl->s4TimeoutCnt );
			if( t_udResult != E_OK )
			{
				/* Clock Setting Fail */
				break;
			}
		}
	}

	return ( t_udResult );
}
#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) */

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
/************************************************************************************************/
/* Function			:	Mcu_StandbyFout															*/
/* Reentrancy		:	Re-entrant																*/
/* Parameters(in)	:	None																	*/
/* Return value		:	Std_ReturnType															*/
/* Limitation		:	None																	*/
/************************************************************************************************/
static FUNC( Std_ReturnType, MCU_CODE ) Mcu_StandbyFout( void )
{
	Std_ReturnType t_udResult;

	t_udResult = E_OK;

	/*-------------------------------------------------*/
	/* Set FOUT0 clock selector/divider for standby    */
	/*-------------------------------------------------*/
	/* Set CKSC_FOUT only if the config setting is different from the current value, because FOUT must be stopped once when changing CKSC_FOUT. */
	if ( REG_CLOCK_AWO.u4CKSC_FOUT0S != ( MCU_CFG_CLK_FOUT0C_SLEEP * CLOCK_CKSC_FOUT0S_FOUT0SACT_0 ) )
	{
		t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_AWO.u4CLKD_FOUT0S, CLOCK_CLKD_FOUT0S_FOUT0SYNC, MCU_FOUT0S_STABLE, MCU_PROCESS_TIME_OUT_POST_FOUT );

		if ( t_udResult == E_OK )
		{
			REG_CLOCK_AWO.u4CLKD_FOUT0C = MCU_FOUT0C_STOPPED;			/* Stop the FOUT clock once before operating CKSC_FOUT */
			t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_AWO.u4CLKD_FOUT0S, ( CLOCK_CLKD_FOUT0S_FOUT0CLKACT + CLOCK_CLKD_FOUT0S_FOUT0SYNC ), MCU_FOUT0S_STOP_STABLE, MCU_PROCESS_TIME_OUT_POST_FOUT );
		}

		if ( t_udResult == E_OK )
		{
			REG_CLOCK_AWO.u4CKSC_FOUT0C = ( MCU_CFG_CLK_FOUT0C_SLEEP * CLOCK_CKSC_FOUT0C_FOUT0SCSID_0 );
			t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_AWO.u4CKSC_FOUT0S, CLOCK_CKSC_FOUT0S_FOUT0SACT, MCU_CFG_CLK_FOUT0C_SLEEP * CLOCK_CKSC_FOUT0S_FOUT0SACT_0, MCU_PROCESS_TIME_OUT_PERI );
		}
	}

	if ( t_udResult == E_OK )
	{
		t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_AWO.u4CLKD_FOUT0S, CLOCK_CLKD_FOUT0S_FOUT0SYNC, MCU_FOUT0S_STABLE, MCU_PROCESS_TIME_OUT_POST_FOUT );

		if ( t_udResult == E_OK )
		{
			REG_CLOCK_AWO.u4CLKD_FOUT0C = ( MCU_CFG_CLKD_FOUT0C_SLEEP * CLOCK_CLKD_FOUT0C_FOUT0DIV_0 );
#if ( MCU_CFG_REG_CHK == STD_ON )
			if ( ( REG_CLOCK_AWO.u4CLKD_FOUT0C & CLOCK_CLKD_FOUT0C_FOUT0DIV ) == ( ( MCU_CFG_CLKD_FOUT0C_SLEEP * CLOCK_CLKD_FOUT0C_FOUT0DIV_0 ) & CLOCK_CLKD_FOUT0C_FOUT0DIV ) )
			{
#endif
				t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_AWO.u4CLKD_FOUT0S, CLOCK_CLKD_FOUT0S_FOUT0SYNC, MCU_FOUT0S_STABLE, MCU_PROCESS_TIME_OUT_POST_FOUT );
#if ( MCU_CFG_REG_CHK == STD_ON )
			}
			else
			{
				t_udResult = E_NOT_OK;
			}
#endif
		}
	}

	/*-------------------------------------------------*/
	/* Set FOUT1 clock selector/divider for standby    */
	/*-------------------------------------------------*/
	if ( t_udResult == E_OK )
	{
		/* Set CKSC_FOUT only if the config setting is different from the current value, because FOUT must be stopped once when changing CKSC_FOUT. */
		if ( REG_CLOCK_AWO.u4CKSC_FOUT1S != ( MCU_CFG_CLK_FOUT1C_SLEEP * CLOCK_CKSC_FOUT1S_FOUT1SACT_0 ) )
		{
			t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_AWO.u4CLKD_FOUT1S, CLOCK_CLKD_FOUT1S_FOUT1SYNC, MCU_FOUT1S_STABLE, MCU_PROCESS_TIME_OUT_POST_FOUT );

			if ( t_udResult == E_OK )
			{
				REG_CLOCK_AWO.u4CLKD_FOUT1C = MCU_FOUT1C_STOPPED;			/* Stop the FOUT clock once before operating CKSC_FOUT */
				t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_AWO.u4CLKD_FOUT1S, ( CLOCK_CLKD_FOUT1S_FOUT1CLKACT + CLOCK_CLKD_FOUT1S_FOUT1SYNC ), MCU_FOUT1S_STOP_STABLE, MCU_PROCESS_TIME_OUT_POST_FOUT );
			}

			if ( t_udResult == E_OK )
			{
				REG_CLOCK_AWO.u4CKSC_FOUT1C = ( MCU_CFG_CLK_FOUT1C_SLEEP * CLOCK_CKSC_FOUT1C_FOUT1SCSID_0 );
				t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_AWO.u4CKSC_FOUT1S, CLOCK_CKSC_FOUT1S_FOUT1SACT, MCU_CFG_CLK_FOUT1C_SLEEP * CLOCK_CKSC_FOUT1S_FOUT1SACT_0, MCU_PROCESS_TIME_OUT_PERI );
			}
		}

		if ( t_udResult == E_OK )
		{
			t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_AWO.u4CLKD_FOUT1S, CLOCK_CLKD_FOUT1S_FOUT1SYNC, MCU_FOUT1S_STABLE, MCU_PROCESS_TIME_OUT_POST_FOUT );

			if ( t_udResult == E_OK )
			{
				REG_CLOCK_AWO.u4CLKD_FOUT1C = ( MCU_CFG_CLKD_FOUT1C_SLEEP * CLOCK_CLKD_FOUT1C_FOUT1DIV_0 );
#if ( MCU_CFG_REG_CHK == STD_ON )
				if ( ( REG_CLOCK_AWO.u4CLKD_FOUT1C & CLOCK_CLKD_FOUT1C_FOUT1DIV ) == ( ( MCU_CFG_CLKD_FOUT1C_SLEEP * CLOCK_CLKD_FOUT1C_FOUT1DIV_0 ) & CLOCK_CLKD_FOUT1C_FOUT1DIV ) )
				{
#endif
					t_udResult = Mcu_ProcessTimeOut( &REG_CLOCK_AWO.u4CLKD_FOUT1S, CLOCK_CLKD_FOUT1S_FOUT1SYNC, MCU_FOUT1S_STABLE, MCU_PROCESS_TIME_OUT_POST_FOUT );
#if ( MCU_CFG_REG_CHK == STD_ON )
				}
				else
				{
					t_udResult = E_NOT_OK;
				}
#endif
			}
		}
	}

	return ( t_udResult );
}
#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) */

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
/************************************************************************************************/
/* Function			:	Mcu_StandbySetPwrgdCnt													*/
/* Reentrancy		:	Re-entrant																*/
/* Parameters(in)	:	None																	*/
/* Return value		:	Std_ReturnType															*/
/* Limitation		:	None																	*/
/************************************************************************************************/
static FUNC( Std_ReturnType, MCU_CODE ) Mcu_StandbySetPwrgdCnt( void )
{
	Std_ReturnType t_udResult;

	t_udResult = E_OK;

	/*--------------------------------------------------------*/
	/* Set the waiting time when returning from DeepSTOP mode */
	/*--------------------------------------------------------*/
#if		( MCU_CFG_ISOVDD_STBL_TIME <= MCU_ISOVDD_STBL_TIME_MIN )
	REG_STBC_AWO.u4PWRGD_CNT = MCU_PWRGD_CNT_PWRGD_CNT_MIN;
#elif	( MCU_CFG_ISOVDD_STBL_TIME >= MCU_ISOVDD_STBL_TIME_MAX )
	REG_STBC_AWO.u4PWRGD_CNT = MCU_PWRGD_CNT_PWRGD_CNT_MAX;
#else
	REG_STBC_AWO.u4PWRGD_CNT = MCU_PWRGD_CNT_SETTING;
#endif	/* MCU_CFG_ISOVDD_STBL_TIME */

#if 	( MCU_CFG_REG_CHK == STD_ON )
#if		( MCU_CFG_ISOVDD_STBL_TIME <= MCU_ISOVDD_STBL_TIME_MIN )
	if ( ( REG_STBC_AWO.u4PWRGD_CNT & STBC_PWRGD_CNT_PWRGD_CNT ) != ( MCU_PWRGD_CNT_PWRGD_CNT_MIN & STBC_PWRGD_CNT_PWRGD_CNT ) )
#elif	( MCU_CFG_ISOVDD_STBL_TIME >= MCU_ISOVDD_STBL_TIME_MAX )
	if ( ( REG_STBC_AWO.u4PWRGD_CNT & STBC_PWRGD_CNT_PWRGD_CNT ) != ( MCU_PWRGD_CNT_PWRGD_CNT_MAX & STBC_PWRGD_CNT_PWRGD_CNT ) )
#else
	if ( ( REG_STBC_AWO.u4PWRGD_CNT & STBC_PWRGD_CNT_PWRGD_CNT ) != ( MCU_PWRGD_CNT_SETTING & STBC_PWRGD_CNT_PWRGD_CNT ) )
#endif	/* MCU_CFG_ISOVDD_STBL_TIME */
	{
		t_udResult = E_NOT_OK;
	}
#endif	/* MCU_CFG_REG_CHK */

	return ( t_udResult );
}
#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) */

#if	( ( ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B ) && ( ( MCU_CFG_INIT_CLOCK == STD_ON ) || ( ( MCU_CFG_REG_CHK == STD_ON ) && ( MCU_CFG_REG_REFRESH == STD_ON ) ) ) ) ||	\
	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) )
/************************************************************************************************/
/* Function			:	Mcu_SetClockRegister													*/
/* Reentrancy		:	Re-entrant																*/
/* Parameters(in)	:	t_pu4ControlReg - Control Register Address								*/
/* Parameters(in)	:	t_pu4StatusReg - Status Register Address								*/
/* Parameters(in)	:	t_u4SetValue - Setting Register Value									*/
/* Parameters(in)	:	t_s4TimeoutCnt - Timeout count for confirm completion of setting		*/
/* Return value		:	Setting result															*/
/* Limitation		:	Only use for Clock Selector Register or Clock Divider Register.			*/
/*					:	Assumed that CLKKCPROT1 has already enabled write access.				*/
/*					:	Only useful in case of control register and status register has same	*/
/*					:	value and meaning.														*/
/************************************************************************************************/
static FUNC( Std_ReturnType, MCU_CODE ) Mcu_SetClockRegister( volatile uint32* t_pu4ControlReg, const volatile uint32* t_pu4StatusReg, const uint32 t_u4SetValue, const sint32 t_s4TimeoutCnt )
{
	Std_ReturnType t_udResult;
	sint32 i;

	t_udResult = E_NOT_OK;

	*t_pu4ControlReg = t_u4SetValue;			/* Select source clock */
	mcalcommon_syncp_func();

	for( i = 0; i < t_s4TimeoutCnt; i++ )		/* Confirm completion of selection */
	{
		if( *t_pu4StatusReg == t_u4SetValue )
		{
			t_udResult = E_OK;
			break;
		}
	}

	return ( t_udResult );
}
#endif

#if	( ( ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B ) && ( ( MCU_CFG_INIT_CLOCK == STD_ON ) || ( MCU_CFG_NO_PLL == FALSE ) ) ) || ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) )
/************************************************************************************************/
/* Function			:	Mcu_ProcessTimeOut														*/
/* Reentrancy		:	Re-entrant																*/
/* Parameters(in)	:	t_pu4StatusReg - Status Register Address								*/
/* Parameters(in)	:	t_u4RegMask - Status Register Mask Value								*/
/* Parameters(in)	:	t_u4StatusValue - Status Register expected value						*/
/* Parameters(in)	:	t_s4TimeoutCnt - Timeout count for confirm completion of setting		*/
/* Return value		:	Setting result															*/
/* Limitation		:	None																	*/
/************************************************************************************************/
static FUNC( Std_ReturnType, MCU_CODE ) Mcu_ProcessTimeOut( volatile uint32* t_pu4StatusReg, uint32 t_u4RegMask, const uint32 t_u4StatusValue, const sint32 t_s4TimeoutCnt )
{
	Std_ReturnType t_udResult;
	sint32 i;

	t_udResult = E_NOT_OK;

	for( i = 0; i < t_s4TimeoutCnt; i++ )		/* Confirm completion of selection */
	{
		if( ( *t_pu4StatusReg & t_u4RegMask ) == t_u4StatusValue )
		{
			t_udResult = E_OK;
			break;
		}
	}

	return ( t_udResult );
}
#endif	/* ( ( ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B ) && ( ( MCU_CFG_INIT_CLOCK == STD_ON ) || ( MCU_CFG_NO_PLL == FALSE ) ) ) || ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) ) */

#if ( MCU_CFG_REG_CHK == STD_ON )
/************************************************************************************************/
/* Function			:	Mcu_Regchk_All															*/
/* Reentrancy		:	Non Reentrant															*/
/* Parameters(in)	:	None																	*/
/* Return value		:	Register Check Result													*/
/* Limitation		:	None																	*/
/************************************************************************************************/
FUNC( uint32, MCU_CODE ) Mcu_Regchk_All( void )
{
	uint32 t_u4Result;
	sint32 i;
	const Mcu_ModuleStandbyRegisterType* t_pstMsrTbl;

	/* Check Clock Controller Register */
	REG_CLOCK_ISO.u4CLKKCPROT1 = MCU_CLOCK_PROTECT_ENABLE;
	t_u4Result = Mcu_Regchk_ClkCtrl();
#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
	t_u4Result |= Mcu_Regchk_Fout();
#else	/* MCAL_TARGET_RH850U2B */
	t_u4Result |= Mcu_Regchk_Extclk();
#endif
	REG_CLOCK_ISO.u4CLKKCPROT1 = MCU_CLOCK_PROTECT_DISABLE;

	/* Check Standby Controller Register */
	REG_STBC_ISO.u4MSRKCPROT = MCU_STBC_PROTECT_ENABLE;
	for( i = 0; i < (sint32)MCU_NUM_MSR_REG_SET_TBL; i++ )
	{
		t_pstMsrTbl = &stMcu_ModuleStandbyRegisterSettingTbl[i];
		t_u4Result |= Mcu_Regchk_u4ForRefreshPossible( t_pstMsrTbl->pu4ControlReg, t_pstMsrTbl->u4SetValue, t_pstMsrTbl->u4RegMask );
	}
	REG_STBC_ISO.u4MSRKCPROT = MCU_STBC_PROTECT_DISABLE;

#if ( MCU_CFG_CLK_MONITOR == STD_ON )
	/* Check Clock Monitor Register */
	t_u4Result |= Mcu_Regchk_Clma();
#endif

	return ( t_u4Result );
}

/************************************************************************************************/
/* Function			:	Mcu_Regchk_ClockRegister												*/
/* Reentrancy		:	Non Reentrant															*/
/* Parameters(in)	:	t_pu4ControlReg - Control Register Address								*/
/* Parameters(in)	:	t_pu4StatusReg - Status Register Address								*/
/* Parameters(in)	:	t_u4ExpectValue - Expected Register Value								*/
/* Parameters(in)	:	t_u4RegMask - Mask value for bits to check								*/
/* Return value		:	Register Check Result													*/
/* Limitation		:	Only use for Clock Selector Register or Clock Divider Register.			*/
/*					:	Assumed that CLKKCPROT1 has already enabled write access.				*/
/*					:	Only useful in case of control register and status register has same	*/
/*					:	value and meaning.														*/
/************************************************************************************************/
static FUNC( uint32, MCU_CODE ) Mcu_Regchk_ClockRegister( volatile uint32* t_pu4ControlReg, const volatile uint32* t_pu4StatusReg, const uint32 t_u4ExpectValue, const uint32 t_u4RegMask )
{
	uint32 t_u4Result;
#if ( MCU_CFG_REG_REFRESH == STD_ON )
	Std_ReturnType t_udSubResult;
#endif

	t_u4Result = MCU_REGCHK_OK;

	if( ( *t_pu4StatusReg & t_u4RegMask ) != ( t_u4ExpectValue & t_u4RegMask ) )
	{
#if ( MCU_CFG_REG_REFRESH == STD_ON )
		t_udSubResult = Mcu_SetClockRegister( t_pu4ControlReg, t_pu4StatusReg, t_u4ExpectValue, MCU_TIMEOUT_COUNT_REG_REFRESH );
		if( t_udSubResult == E_OK )
		{
			t_u4Result = MCU_REGCHK_REFRESH_SUCCESS;
		}
		else
		{
			t_u4Result = MCU_REGCHK_REFRESH_FAILED;
		}
#else
		t_u4Result = MCU_REGCHK_NG;
#endif	/* MCU_CFG_REG_REFRESH */
	}

	return ( t_u4Result );
}

/************************************************************************************************/
/* Function			:	Mcu_Regchk_u4ForRefreshPossible											*/
/* Reentrancy		:	Non Reentrant															*/
/* Parameters(in)	:	t_pu4Register - Register Address										*/
/* Parameters(in)	:	t_u4ExpectValue - Expected Register Value								*/
/* Parameters(in)	:	t_u4RegMask - Mask value for bits to check								*/
/* Return value		:	Register Check Result													*/
/* Limitation		:	Assumed that Protection Register has already enabled write access		*/
/************************************************************************************************/
static FUNC( uint32, MCU_CODE ) Mcu_Regchk_u4ForRefreshPossible( volatile uint32* t_pu4Register, const uint32 t_u4ExpectValue , const uint32 t_u4RegMask )
{
	uint32 t_u4Result;

	t_u4Result = MCU_REGCHK_OK;

	if( ( *t_pu4Register & t_u4RegMask ) != ( t_u4ExpectValue & t_u4RegMask ) )
	{
#if ( MCU_CFG_REG_REFRESH == STD_ON )
		*t_pu4Register = t_u4ExpectValue;
		if( ( *t_pu4Register & t_u4RegMask ) == ( t_u4ExpectValue & t_u4RegMask ) )
		{
			t_u4Result = MCU_REGCHK_REFRESH_SUCCESS;
		}
		else
		{
			t_u4Result = MCU_REGCHK_REFRESH_FAILED;
		}
#else
		t_u4Result = MCU_REGCHK_NG;
#endif	/* MCU_CFG_REG_REFRESH */
	}

	return ( t_u4Result );
}

/************************************************************************************************/
/* Function			:	Mcu_Regchk_u4ForRefreshImpossible										*/
/* Reentrancy		:	Non Reentrant															*/
/* Parameters(in)	:	t_pu4Register - Register Address										*/
/* Parameters(in)	:	t_u4ExpectValue - Expected Register Value								*/
/* Parameters(in)	:	t_u4RegMask - Mask value for bits to check								*/
/* Return value		:	Register Check Result													*/
/* Limitation		:	None																	*/
/************************************************************************************************/
static FUNC( uint32, MCU_CODE ) Mcu_Regchk_u4ForRefreshImpossible( volatile uint32* t_pu4Register, const uint32 t_u4ExpectValue , const uint32 t_u4RegMask )
{
	uint32 t_u4Result;

	t_u4Result = MCU_REGCHK_OK;

	if( ( *t_pu4Register & t_u4RegMask ) != ( t_u4ExpectValue & t_u4RegMask ) )
	{
#if ( MCU_CFG_REG_REFRESH == STD_ON )
		t_u4Result = MCU_REGCHK_REFRESH_IMPOSSIBLE;
#else
		t_u4Result = MCU_REGCHK_NG;
#endif	/* MCU_CFG_REG_REFRESH */
	}

	return ( t_u4Result );
}

/************************************************************************************************/
/* Function			:	Mcu_Regchk_ClkCtrl														*/
/* Reentrancy		:	Non Reentrant															*/
/* Parameters(in)	:	None																	*/
/* Return value		:	Register Check Result													*/
/* Limitation		:	Assumed that Protection Register has already enabled write access		*/
/************************************************************************************************/
static FUNC( uint32, MCU_CODE ) Mcu_Regchk_ClkCtrl( void )
{
	uint32 t_u4Result;
	sint32 i;
	const Mcu_ClockRegisterSettingType* t_pstClkTbl;

	t_u4Result = MCU_REGCHK_OK;

	for( i = 0; i < (sint32)MCU_NUM_CLK_REG_SET_TBL; i++ )
	{
		t_pstClkTbl = &stMcu_ClockRegisterSettingTbl[i];
		t_u4Result |= Mcu_Regchk_ClockRegister( t_pstClkTbl->pu4ControlReg, t_pstClkTbl->pu4StatusReg, t_pstClkTbl->u4SetValue, t_pstClkTbl->u4RegMask );
	}

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )

#if	( MCU_CFG_CLK_SSCG_SSMODE1_TYPE_0 == STD_ON )
	if( ( REG_CLOCK_ISO.u4SSCGC & MCU_ENABLE_BIT_MASK_SSCGC ) != ( MCU_SSCGC_REGCHK_EXPECTED_VALUE & MCU_ENABLE_BIT_MASK_SSCGC ) )
	{
		/* SSCGC Register Fail */
#if ( MCU_CFG_REG_REFRESH == STD_ON )
		REG_CLOCK_ISO.u4SSCGC &= ~CLOCK_SSCGC_SSMODE1;												/* SSCG Control modulation disabled */
		MCAL_LIB_Wait( MCU_WAIT_SSCG_STABLE_TIME );													/* Wait at least 200 microseconds */
		REG_CLOCK_ISO.u4SSCGC = ( MCU_CFG_CLK_SSCG_FREQ_TYPE_0 * CLOCK_SSCGC_SELMFREQ_0 )
							  + ( MCU_CFG_CLK_SSCG_PERCENT_TYPE_0 * CLOCK_SSCGC_SELMPERCENT_0 );	/* Initialize SSCG modulation frequency and dithered range */
		REG_CLOCK_ISO.u4SSCGC |= CLOCK_SSCGC_SSMODE1;												/* SSCG Control modulation enabled */
		if( ( REG_CLOCK_ISO.u4SSCGC & MCU_ENABLE_BIT_MASK_SSCGC ) != ( MCU_SSCGC_REGCHK_EXPECTED_VALUE & MCU_ENABLE_BIT_MASK_SSCGC ) )
		{
			t_u4Result |= MCU_REGCHK_REFRESH_FAILED;
		}
		else
		{
			t_u4Result |= MCU_REGCHK_REFRESH_SUCCESS;
		}
#else
		t_u4Result |= MCU_REGCHK_NG;
#endif	/* MCU_CFG_REG_REFRESH */
	}
#endif	/* ( MCU_CFG_CLK_SSCG_SSMODE1_TYPE_0 == STD_ON ) */

#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B ) */

	return ( t_u4Result );
}

#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
/************************************************************************************************/
/* Function			:	Mcu_Regchk_Fout															*/
/* Reentrancy		:	Non Reentrant															*/
/* Parameters(in)	:	None																	*/
/* Return value		:	Register Check Result													*/
/* Limitation		:	None																	*/
/************************************************************************************************/
static FUNC( uint32, MCU_CODE ) Mcu_Regchk_Fout( void )
{
	uint32 t_u4Result;

	t_u4Result = Mcu_Regchk_Fout0Clkd();
	t_u4Result |= Mcu_Regchk_u4ForRefreshImpossible( &REG_CLOCK_AWO.u4CKSC_FOUT0S, MCU_CFG_CLK_FOUT0C_TYPE_0, CLOCK_CKSC_FOUT0S_FOUT0SACT );
	t_u4Result |= Mcu_Regchk_Fout1Clkd();
	t_u4Result |= Mcu_Regchk_u4ForRefreshImpossible( &REG_CLOCK_AWO.u4CKSC_FOUT1S, MCU_CFG_CLK_FOUT1C_TYPE_0, CLOCK_CKSC_FOUT1S_FOUT1SACT );

	return ( t_u4Result );
}
#endif /* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) */

#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
/************************************************************************************************/
/* Function			:	Mcu_Regchk_Fout0Clkd													*/
/* Reentrancy		:	Non Reentrant															*/
/* Parameters(in)	:	None																	*/
/* Return value		:	Register Check Result													*/
/* Limitation		:	Assumed that CLKKCPROT1 has already enabled write access.				*/
/************************************************************************************************/
static FUNC( uint32, MCU_CODE ) Mcu_Regchk_Fout0Clkd( void )
{
	uint32 t_u4Result;
#if ( MCU_CFG_REG_REFRESH == STD_ON )
	Std_ReturnType t_udSubResult;
#endif

	t_u4Result = MCU_REGCHK_OK;

	if ( ( REG_CLOCK_AWO.u4CLKD_FOUT0C & CLOCK_CLKD_FOUT0C_FOUT0DIV ) != ( MCU_CFG_CLKD_FOUT0C_TYPE_0 & CLOCK_CLKD_FOUT0C_FOUT0DIV ) )
	{

#if ( MCU_CFG_REG_REFRESH == STD_ON )
		/* Refresh only when FOUT divider is stable (Hardware limitation) */
		if ( ( REG_CLOCK_AWO.u4CLKD_FOUT0S & CLOCK_CLKD_FOUT0S_FOUT0SYNC ) == MCU_FOUT0S_STABLE )
		{
			REG_CLOCK_AWO.u4CLKD_FOUT0C = ( MCU_CFG_CLKD_FOUT0C_TYPE_0 * CLOCK_CLKD_FOUT0C_FOUT0DIV_0 );
			if ( ( REG_CLOCK_AWO.u4CLKD_FOUT0C & CLOCK_CLKD_FOUT0C_FOUT0DIV ) != ( MCU_CFG_CLKD_FOUT0C_TYPE_0 & CLOCK_CLKD_FOUT0C_FOUT0DIV ) )
			{
				t_u4Result = MCU_REGCHK_REFRESH_FAILED;
			}
			else
			{
				t_udSubResult = Mcu_ProcessTimeOut( &REG_CLOCK_AWO.u4CLKD_FOUT0S, CLOCK_CLKD_FOUT0S_FOUT0SYNC, MCU_FOUT0S_STABLE, MCU_TIMEOUT_COUNT_REG_REFRESH );
				if ( t_udSubResult != E_OK )
				{
					t_u4Result = MCU_REGCHK_REFRESH_FAILED;
				}
				else
				{
					t_u4Result = MCU_REGCHK_REFRESH_SUCCESS;
				}
			}
		}
		else
		{
			t_u4Result = MCU_REGCHK_REFRESH_IMPOSSIBLE;
		}
#else
		t_u4Result = MCU_REGCHK_NG;
#endif	/* MCU_CFG_REG_REFRESH == STD_ON */

	}

	return ( t_u4Result );
}
#endif /* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) */

#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
/************************************************************************************************/
/* Function			:	Mcu_Regchk_Fout1Clkd													*/
/* Reentrancy		:	Non Reentrant															*/
/* Parameters(in)	:	None																	*/
/* Return value		:	Register Check Result													*/
/* Limitation		:	Assumed that CLKKCPROT1 has already enabled write access.				*/
/************************************************************************************************/
static FUNC( uint32, MCU_CODE ) Mcu_Regchk_Fout1Clkd( void )
{
	uint32 t_u4Result;
#if ( MCU_CFG_REG_REFRESH == STD_ON )
	Std_ReturnType t_udSubResult;
#endif

	t_u4Result = MCU_REGCHK_OK;

	if ( ( REG_CLOCK_AWO.u4CLKD_FOUT1C & CLOCK_CLKD_FOUT1C_FOUT1DIV ) != ( MCU_CFG_CLKD_FOUT1C_TYPE_0 & CLOCK_CLKD_FOUT1C_FOUT1DIV ) )
	{

#if ( MCU_CFG_REG_REFRESH == STD_ON )
		/* Refresh only when FOUT divider is stable (Hardware limitation) */
		if ( ( REG_CLOCK_AWO.u4CLKD_FOUT1S & CLOCK_CLKD_FOUT1S_FOUT1SYNC ) == MCU_FOUT1S_STABLE )
		{
			REG_CLOCK_AWO.u4CLKD_FOUT1C = ( MCU_CFG_CLKD_FOUT1C_TYPE_0 * CLOCK_CLKD_FOUT1C_FOUT1DIV_0 );
			if ( ( REG_CLOCK_AWO.u4CLKD_FOUT1C & CLOCK_CLKD_FOUT1C_FOUT1DIV ) != ( MCU_CFG_CLKD_FOUT1C_TYPE_0 & CLOCK_CLKD_FOUT1C_FOUT1DIV ) )
			{
				t_u4Result = MCU_REGCHK_REFRESH_FAILED;
			}
			else
			{
				t_udSubResult = Mcu_ProcessTimeOut( &REG_CLOCK_AWO.u4CLKD_FOUT1S, CLOCK_CLKD_FOUT1S_FOUT1SYNC, MCU_FOUT1S_STABLE, MCU_TIMEOUT_COUNT_REG_REFRESH );
				if ( t_udSubResult == E_OK )
				{
					t_u4Result = MCU_REGCHK_REFRESH_SUCCESS;
				}
				else
				{
					t_u4Result = MCU_REGCHK_REFRESH_FAILED;
				}
			}
		}
		else
		{
			t_u4Result = MCU_REGCHK_REFRESH_IMPOSSIBLE;
		}
#else
		t_u4Result = MCU_REGCHK_NG;
#endif	/* MCU_CFG_REG_REFRESH == STD_ON */

	}

	return ( t_u4Result );
}
#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) */

#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
/************************************************************************************************/
/* Function			:	Mcu_Regchk_Extclk														*/
/* Reentrancy		:	Non Reentrant															*/
/* Parameters(in)	:	None																	*/
/* Return value		:	Register Check Result													*/
/* Limitation		:	None																	*/
/************************************************************************************************/
static FUNC( uint32, MCU_CODE ) Mcu_Regchk_Extclk( void )
{
	uint32 t_u4Result;

	t_u4Result = Mcu_Regchk_Extclk0Clkd();
	t_u4Result |= Mcu_Regchk_u4ForRefreshImpossible( &REG_CLOCK_AWO.u4CKS_EXTCLK0S, MCU_CFG_CLK_EXTCLK0C_TYPE_0, CLOCK_EXTCLK0SACT );
	t_u4Result |= Mcu_Regchk_Extclk1Clkd();
	t_u4Result |= Mcu_Regchk_u4ForRefreshImpossible( &REG_CLOCK_AWO.u4CKS_EXTCLK1S, MCU_CFG_CLK_EXTCLK1C_TYPE_0, CLOCK_EXTCLK1SACT );

	return ( t_u4Result );
}

/************************************************************************************************/
/* Function			:	Mcu_Regchk_Extclk0Clkd													*/
/* Reentrancy		:	Non Reentrant															*/
/* Parameters(in)	:	None																	*/
/* Return value		:	Register Check Result													*/
/* Limitation		:	Assumed that CLKKCPROT1 has already enabled write access.				*/
/************************************************************************************************/
static FUNC( uint32, MCU_CODE ) Mcu_Regchk_Extclk0Clkd( void )
{
	uint32 t_u4Result;
#if ( MCU_CFG_REG_REFRESH == STD_ON )
	Std_ReturnType t_udSubResult;
#endif

	t_u4Result = MCU_REGCHK_OK;

	if ( ( REG_CLOCK_AWO.u4CKD_EXTCLK0C & CLOCK_CKD_EXTCLK0C_EXTCLK0DIV ) != ( MCU_CFG_CLKD_EXTCLK0C_TYPE_0 & CLOCK_CKD_EXTCLK0C_EXTCLK0DIV ) )
	{

#if ( MCU_CFG_REG_REFRESH == STD_ON )
		/* Refresh only when EXTCLK divider is stable (Hardware limitation) */
		if ( ( REG_CLOCK_AWO.u4CKD_EXTCLK0S & CLOCK_EXTCLK0SYNC ) == MCU_EXTCLK0S_STABLE )
		{
			REG_CLOCK_AWO.u4CKD_EXTCLK0C = ( MCU_CFG_CLKD_EXTCLK0C_TYPE_0 * CLOCK_CKD_EXTCLK0C_EXTCLK0DIV_0 );
			if ( ( REG_CLOCK_AWO.u4CKD_EXTCLK0C & CLOCK_CKD_EXTCLK0C_EXTCLK0DIV ) != ( MCU_CFG_CLKD_EXTCLK0C_TYPE_0 & CLOCK_CKD_EXTCLK0C_EXTCLK0DIV ) )
			{
				t_u4Result = MCU_REGCHK_REFRESH_FAILED;
			}
			else
			{
				t_udSubResult = Mcu_ProcessTimeOut( &REG_CLOCK_AWO.u4CKD_EXTCLK0S, CLOCK_EXTCLK0SYNC, MCU_EXTCLK0S_STABLE, MCU_TIMEOUT_COUNT_REG_REFRESH );
				if ( t_udSubResult != E_OK )
				{
					t_u4Result = MCU_REGCHK_REFRESH_FAILED;
				}
				else
				{
					t_u4Result = MCU_REGCHK_REFRESH_SUCCESS;
				}
			}
		}
		else
		{
			t_u4Result = MCU_REGCHK_REFRESH_IMPOSSIBLE;
		}
#else
		t_u4Result = MCU_REGCHK_NG;
#endif	/* MCU_CFG_REG_REFRESH == STD_ON */

	}

	return ( t_u4Result );
}

/************************************************************************************************/
/* Function			:	Mcu_Regchk_Extclk1Clkd													*/
/* Reentrancy		:	Non Reentrant															*/
/* Parameters(in)	:	None																	*/
/* Return value		:	Register Check Result													*/
/* Limitation		:	Assumed that CLKKCPROT1 has already enabled write access.				*/
/************************************************************************************************/
static FUNC( uint32, MCU_CODE ) Mcu_Regchk_Extclk1Clkd( void )
{
	uint32 t_u4Result;
#if ( MCU_CFG_REG_REFRESH == STD_ON )
	Std_ReturnType t_udSubResult;
#endif

	t_u4Result = MCU_REGCHK_OK;

	if ( ( REG_CLOCK_AWO.u4CKD_EXTCLK1C & CLOCK_CKD_EXTCLK1C_EXTCLK1DIV ) != ( MCU_CFG_CLKD_EXTCLK1C_TYPE_0 & CLOCK_CKD_EXTCLK1C_EXTCLK1DIV ) )
	{

#if ( MCU_CFG_REG_REFRESH == STD_ON )
		/* Refresh only when EXTCLK divider is stable (Hardware limitation) */
		if ( ( REG_CLOCK_AWO.u4CKD_EXTCLK1S & CLOCK_EXTCLK1SYNC ) == MCU_EXTCLK1S_STABLE )
		{
			REG_CLOCK_AWO.u4CKD_EXTCLK1C = ( MCU_CFG_CLKD_EXTCLK1C_TYPE_0 * CLOCK_CKD_EXTCLK1C_EXTCLK1DIV_0 );
			if ( ( REG_CLOCK_AWO.u4CKD_EXTCLK1C & CLOCK_CKD_EXTCLK1C_EXTCLK1DIV ) != ( MCU_CFG_CLKD_EXTCLK1C_TYPE_0 & CLOCK_CKD_EXTCLK1C_EXTCLK1DIV ) )
			{
				t_u4Result = MCU_REGCHK_REFRESH_FAILED;
			}
			else
			{
				t_udSubResult = Mcu_ProcessTimeOut( &REG_CLOCK_AWO.u4CKD_EXTCLK1S, CLOCK_EXTCLK1SYNC, MCU_EXTCLK1S_STABLE, MCU_TIMEOUT_COUNT_REG_REFRESH );
				if ( t_udSubResult != E_OK )
				{
					t_u4Result = MCU_REGCHK_REFRESH_FAILED;
				}
				else
				{
					t_u4Result = MCU_REGCHK_REFRESH_SUCCESS;
				}
			}
		}
		else
		{
			t_u4Result = MCU_REGCHK_REFRESH_IMPOSSIBLE;
		}
#else
		t_u4Result = MCU_REGCHK_NG;
#endif	/* MCU_CFG_REG_REFRESH == STD_ON */

	}

	return ( t_u4Result );
}
#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B ) */

#if ( MCU_CFG_CLK_MONITOR == STD_ON )
/************************************************************************************************/
/* Function			:	Mcu_Regchk_Clma															*/
/* Reentrancy		:	Non Reentrant															*/
/* Parameters(in)	:	None																	*/
/* Return value		:	Register Check Result													*/
/* Limitation		:	None																	*/
/************************************************************************************************/
static FUNC( uint32, MCU_CODE ) Mcu_Regchk_Clma( void )
{
	uint32 t_u4Result;

	t_u4Result = MCU_REGCHK_OK + MCU_REGCHK_RESULT_DUMMY_BIT;

	REG_CLMAKCPROT.u4CLMAKCPROT = CLMA_CLMAKCPROT_ENABLE;

#if ( MCU_CFG_CLMA0CLME == STD_ON )
	t_u4Result |= Mcu_Regchk_u2ForRefreshPossible( &REG_CLMA0.u2CLMA0CMPL, MCU_CFG_CLMA0CMPL, (uint16)CLMA_CLMAnCMPL_CLMAnCMPL);
	t_u4Result |= Mcu_Regchk_u2ForRefreshPossible( &REG_CLMA0.u2CLMA0CMPH, MCU_CFG_CLMA0CMPH, (uint16)CLMA_CLMAnCMPH_CLMAnCMPH);
#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
#if ( MCU_CFG_CLMABCE == STD_ON )
	t_u4Result |= Mcu_Regchk_u1ForRefreshPossible( &REG_CLMAC.u1CLMABCE, (uint8)CLMA_CLMABCE_CLMABCE_ENABLE, (uint8)CLMA_CLMABCE_CLMABCE);
#else
	t_u4Result |= Mcu_Regchk_u1ForRefreshPossible( &REG_CLMAC.u1CLMABCE, (uint8)CLMA_CLMABCE_CLMABCE_DISABLE, (uint8)CLMA_CLMABCE_CLMABCE);
#endif /* MCU_CFG_CLMABCE */
#endif /* MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B */
	t_u4Result |= Mcu_Regchk_u1ForRefreshPossible( &REG_CLMA0.u1CLMA0CTL, (uint8)CLMA_CLMAnCTL_CLMAnCLME_ENABLE, (uint8)CLMA_CLMAnCTL_CLMAnCLME);
#else /* MCU_CFG_CLMA0CLME == STD_ON */
	t_u4Result |= Mcu_Regchk_u1ForRefreshPossible( &REG_CLMA0.u1CLMA0CTL, (uint8)CLMA_CLMAnCTL_CLMAnCLME_DISABLE, (uint8)CLMA_CLMAnCTL_CLMAnCLME);
#endif /* MCU_CFG_CLMA0CLME == STD_ON */

#if ( MCU_CFG_CLMA1CLME == STD_ON )
	t_u4Result |= Mcu_Regchk_u2ForRefreshPossible( &REG_CLMA1.u2CLMA1CMPL, MCU_CFG_CLMA1CMPL, (uint16)CLMA_CLMAnCMPL_CLMAnCMPL);
	t_u4Result |= Mcu_Regchk_u2ForRefreshPossible( &REG_CLMA1.u2CLMA1CMPH, MCU_CFG_CLMA1CMPH, (uint16)CLMA_CLMAnCMPH_CLMAnCMPH);
	t_u4Result |= Mcu_Regchk_u1ForRefreshPossible( &REG_CLMA1.u1CLMA1CTL, (uint8)CLMA_CLMAnCTL_CLMAnCLME_ENABLE, (uint8)CLMA_CLMAnCTL_CLMAnCLME);
#else
	t_u4Result |= Mcu_Regchk_u1ForRefreshPossible( &REG_CLMA1.u1CLMA1CTL, (uint8)CLMA_CLMAnCTL_CLMAnCLME_DISABLE, (uint8)CLMA_CLMAnCTL_CLMAnCLME);
#endif

#if ( MCU_CFG_CLMA2CLME == STD_ON )
	t_u4Result |= Mcu_Regchk_u2ForRefreshPossible( &REG_CLMA2.u2CLMA2CMPL, MCU_CFG_CLMA2CMPL, (uint16)CLMA_CLMAnCMPL_CLMAnCMPL);
	t_u4Result |= Mcu_Regchk_u2ForRefreshPossible( &REG_CLMA2.u2CLMA2CMPH, MCU_CFG_CLMA2CMPH, (uint16)CLMA_CLMAnCMPH_CLMAnCMPH);
	t_u4Result |= Mcu_Regchk_u1ForRefreshPossible( &REG_CLMA2.u1CLMA2CTL, (uint8)CLMA_CLMAnCTL_CLMAnCLME_ENABLE, (uint8)CLMA_CLMAnCTL_CLMAnCLME);
#else
	t_u4Result |= Mcu_Regchk_u1ForRefreshPossible( &REG_CLMA2.u1CLMA2CTL, (uint8)CLMA_CLMAnCTL_CLMAnCLME_DISABLE, (uint8)CLMA_CLMAnCTL_CLMAnCLME);
#endif

#if ( MCU_CFG_CLMA3CLME == STD_ON )
	t_u4Result |= Mcu_Regchk_u2ForRefreshPossible( &REG_CLMA3.u2CLMA3CMPL, MCU_CFG_CLMA3CMPL, (uint16)CLMA_CLMAnCMPL_CLMAnCMPL);
	t_u4Result |= Mcu_Regchk_u2ForRefreshPossible( &REG_CLMA3.u2CLMA3CMPH, MCU_CFG_CLMA3CMPH, (uint16)CLMA_CLMAnCMPH_CLMAnCMPH);
#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
#if ( MCU_CFG_CLMABCE == STD_ON )
	t_u4Result |= Mcu_Regchk_u1ForRefreshPossible( &REG_CLMAC.u1CLMABCE, (uint8)CLMA_CLMABCE_CLMABCE_ENABLE, (uint8)CLMA_CLMABCE_CLMABCE);
#else
	t_u4Result |= Mcu_Regchk_u1ForRefreshPossible( &REG_CLMAC.u1CLMABCE, (uint8)CLMA_CLMABCE_CLMABCE_DISABLE, (uint8)CLMA_CLMABCE_CLMABCE);
#endif /* MCU_CFG_CLMABCE */
	t_u4Result |= Mcu_Regchk_u1ForRefreshPossible( &REG_CLMA3.u1CLMA3STPDTEN, (uint8)CLMA_CLMAnSTPDTEN_DISABLE, (uint8)CLMA_CLMAnSTPDTEN_CLMAnSTPDTEN);
#endif /* MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B */
	t_u4Result |= Mcu_Regchk_u1ForRefreshPossible( &REG_CLMA3.u1CLMA3CTL, (uint8)CLMA_CLMAnCTL_CLMAnCLME_ENABLE, (uint8)CLMA_CLMAnCTL_CLMAnCLME);
#else
	t_u4Result |= Mcu_Regchk_u1ForRefreshPossible( &REG_CLMA3.u1CLMA3CTL, (uint8)CLMA_CLMAnCTL_CLMAnCLME_DISABLE, (uint8)CLMA_CLMAnCTL_CLMAnCLME);
#endif

	t_u4Result |= Mcu_Regchk_u1ForRefreshPossible( &REG_CLMA4.u1CLMA4CTL, (uint8)CLMA_CLMAnCTL_CLMAnCLME_DISABLE, (uint8)CLMA_CLMAnCTL_CLMAnCLME);

#if ( MCU_CFG_CLMA5CLME == STD_ON )
	t_u4Result |= Mcu_Regchk_u2ForRefreshPossible( &REG_CLMA5.u2CLMA5CMPL, MCU_CFG_CLMA5CMPL, (uint16)CLMA_CLMAnCMPL_CLMAnCMPL);
	t_u4Result |= Mcu_Regchk_u2ForRefreshPossible( &REG_CLMA5.u2CLMA5CMPH, MCU_CFG_CLMA5CMPH, (uint16)CLMA_CLMAnCMPH_CLMAnCMPH);
	t_u4Result |= Mcu_Regchk_u1ForRefreshPossible( &REG_CLMA5.u1CLMA5CTL, (uint8)CLMA_CLMAnCTL_CLMAnCLME_ENABLE, (uint8)CLMA_CLMAnCTL_CLMAnCLME);
#else
	t_u4Result |= Mcu_Regchk_u1ForRefreshPossible( &REG_CLMA5.u1CLMA5CTL, (uint8)CLMA_CLMAnCTL_CLMAnCLME_DISABLE, (uint8)CLMA_CLMAnCTL_CLMAnCLME);
#endif

#if ( MCU_CFG_CLMA6CLME == STD_ON )
	t_u4Result |= Mcu_Regchk_u2ForRefreshPossible( &REG_CLMA6.u2CLMA6CMPL, MCU_CFG_CLMA6CMPL, (uint16)CLMA_CLMAnCMPL_CLMAnCMPL);
	t_u4Result |= Mcu_Regchk_u2ForRefreshPossible( &REG_CLMA6.u2CLMA6CMPH, MCU_CFG_CLMA6CMPH, (uint16)CLMA_CLMAnCMPH_CLMAnCMPH);
#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
	t_u4Result |= Mcu_Regchk_u1ForRefreshPossible( &REG_CLMA6.u1CLMA6STPDTEN, (uint8)CLMA_CLMAnSTPDTEN_DISABLE, (uint8)CLMA_CLMAnSTPDTEN_CLMAnSTPDTEN);
#endif
	t_u4Result |= Mcu_Regchk_u1ForRefreshPossible( &REG_CLMA6.u1CLMA6CTL, (uint8)CLMA_CLMAnCTL_CLMAnCLME_ENABLE, (uint8)CLMA_CLMAnCTL_CLMAnCLME);
#else
	t_u4Result |= Mcu_Regchk_u1ForRefreshPossible( &REG_CLMA6.u1CLMA6CTL, (uint8)CLMA_CLMAnCTL_CLMAnCLME_DISABLE, (uint8)CLMA_CLMAnCTL_CLMAnCLME);
#endif

#if ( MCU_CFG_CLMA7CLME == STD_ON )
	t_u4Result |= Mcu_Regchk_u2ForRefreshPossible( &REG_CLMA7.u2CLMA7CMPL, MCU_CFG_CLMA7CMPL, (uint16)CLMA_CLMAnCMPL_CLMAnCMPL);
	t_u4Result |= Mcu_Regchk_u2ForRefreshPossible( &REG_CLMA7.u2CLMA7CMPH, MCU_CFG_CLMA7CMPH, (uint16)CLMA_CLMAnCMPH_CLMAnCMPH);
#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
	t_u4Result |= Mcu_Regchk_u1ForRefreshPossible( &REG_CLMA7.u1CLMA7STPDTEN, (uint8)CLMA_CLMAnSTPDTEN_DISABLE, (uint8)CLMA_CLMAnSTPDTEN_CLMAnSTPDTEN);
#endif
	t_u4Result |= Mcu_Regchk_u1ForRefreshPossible( &REG_CLMA7.u1CLMA7CTL, (uint8)CLMA_CLMAnCTL_CLMAnCLME_ENABLE, (uint8)CLMA_CLMAnCTL_CLMAnCLME);
#else
	t_u4Result |= Mcu_Regchk_u1ForRefreshPossible( &REG_CLMA7.u1CLMA7CTL, (uint8)CLMA_CLMAnCTL_CLMAnCLME_DISABLE, (uint8)CLMA_CLMAnCTL_CLMAnCLME);
#endif

#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
#if	( ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A16_516PIN ) || ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A16_373PIN ) )
#if ( MCU_CFG_CLMA8CLME == STD_ON )
	t_u4Result |= Mcu_Regchk_u2ForRefreshPossible( &REG_CLMA8.u2CLMA8CMPL, MCU_CFG_CLMA8CMPL, (uint16)CLMA_CLMAnCMPL_CLMAnCMPL);
	t_u4Result |= Mcu_Regchk_u2ForRefreshPossible( &REG_CLMA8.u2CLMA8CMPH, MCU_CFG_CLMA8CMPH, (uint16)CLMA_CLMAnCMPH_CLMAnCMPH);
	t_u4Result |= Mcu_Regchk_u1ForRefreshPossible( &REG_CLMA8.u1CLMA8CTL, (uint8)CLMA_CLMAnCTL_CLMAnCLME_ENABLE, (uint8)CLMA_CLMAnCTL_CLMAnCLME);
#else
	t_u4Result |= Mcu_Regchk_u1ForRefreshPossible( &REG_CLMA8.u1CLMA8CTL, (uint8)CLMA_CLMAnCTL_CLMAnCLME_DISABLE, (uint8)CLMA_CLMAnCTL_CLMAnCLME);
#endif

#if ( MCU_CFG_CLMA9CLME == STD_ON )
	t_u4Result |= Mcu_Regchk_u2ForRefreshPossible( &REG_CLMA9.u2CLMA9CMPL, MCU_CFG_CLMA9CMPL, (uint16)CLMA_CLMAnCMPL_CLMAnCMPL);
	t_u4Result |= Mcu_Regchk_u2ForRefreshPossible( &REG_CLMA9.u2CLMA9CMPH, MCU_CFG_CLMA9CMPH, (uint16)CLMA_CLMAnCMPH_CLMAnCMPH);
	t_u4Result |= Mcu_Regchk_u1ForRefreshPossible( &REG_CLMA9.u1CLMA9CTL, (uint8)CLMA_CLMAnCTL_CLMAnCLME_ENABLE, (uint8)CLMA_CLMAnCTL_CLMAnCLME);
#else
	t_u4Result |= Mcu_Regchk_u1ForRefreshPossible( &REG_CLMA9.u1CLMA9CTL, (uint8)CLMA_CLMAnCTL_CLMAnCLME_DISABLE, (uint8)CLMA_CLMAnCTL_CLMAnCLME);
#endif
#endif
#endif /* MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A */

#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
#if ( MCU_CFG_CLMA13CLME == STD_ON )
	t_u4Result |= Mcu_Regchk_u2ForRefreshPossible( &REG_CLMA13.u2CLMA13CMPL, MCU_CFG_CLMA13CMPL, (uint16)CLMA_CLMAnCMPL_CLMAnCMPL);
	t_u4Result |= Mcu_Regchk_u2ForRefreshPossible( &REG_CLMA13.u2CLMA13CMPH, MCU_CFG_CLMA13CMPH, (uint16)CLMA_CLMAnCMPH_CLMAnCMPH);
#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
	t_u4Result |= Mcu_Regchk_u1ForRefreshPossible( &REG_CLMA13.u1CLMA13STPDTEN, (uint8)CLMA_CLMAnSTPDTEN_DISABLE, (uint8)CLMA_CLMAnSTPDTEN_CLMAnSTPDTEN);
#endif
	t_u4Result |= Mcu_Regchk_u1ForRefreshPossible( &REG_CLMA13.u1CLMA13CTL, (uint8)CLMA_CLMAnCTL_CLMAnCLME_ENABLE, (uint8)CLMA_CLMAnCTL_CLMAnCLME);
#else
	t_u4Result |= Mcu_Regchk_u1ForRefreshPossible( &REG_CLMA13.u1CLMA13CTL, (uint8)CLMA_CLMAnCTL_CLMAnCLME_DISABLE, (uint8)CLMA_CLMAnCTL_CLMAnCLME);
#endif

#if ( MCU_CFG_CLMA14CLME == STD_ON )
	t_u4Result |= Mcu_Regchk_u2ForRefreshPossible( &REG_CLMA14.u2CLMA14CMPL, MCU_CFG_CLMA14CMPL, (uint16)CLMA_CLMAnCMPL_CLMAnCMPL);
	t_u4Result |= Mcu_Regchk_u2ForRefreshPossible( &REG_CLMA14.u2CLMA14CMPH, MCU_CFG_CLMA14CMPH, (uint16)CLMA_CLMAnCMPH_CLMAnCMPH);
	t_u4Result |= Mcu_Regchk_u1ForRefreshPossible( &REG_CLMA14.u1CLMA14CTL, (uint8)CLMA_CLMAnCTL_CLMAnCLME_ENABLE, (uint8)CLMA_CLMAnCTL_CLMAnCLME);
#else
	t_u4Result |= Mcu_Regchk_u1ForRefreshPossible( &REG_CLMA14.u1CLMA14CTL, (uint8)CLMA_CLMAnCTL_CLMAnCLME_DISABLE, (uint8)CLMA_CLMAnCTL_CLMAnCLME);
#endif

#if ( MCU_CFG_CLMA15CLME == STD_ON )
	t_u4Result |= Mcu_Regchk_u2ForRefreshPossible( &REG_CLMA15.u2CLMA15CMPL, MCU_CFG_CLMA15CMPL, (uint16)CLMA_CLMAnCMPL_CLMAnCMPL);
	t_u4Result |= Mcu_Regchk_u2ForRefreshPossible( &REG_CLMA15.u2CLMA15CMPH, MCU_CFG_CLMA15CMPH, (uint16)CLMA_CLMAnCMPH_CLMAnCMPH);
#if ( MCU_CFG_CLMABCE == STD_ON )
	t_u4Result |= Mcu_Regchk_u1ForRefreshPossible( &REG_CLMAC.u1CLMABCE, (uint8)CLMA_CLMABCE_CLMABCE_ENABLE, (uint8)CLMA_CLMABCE_CLMABCE);
#else
	t_u4Result |= Mcu_Regchk_u1ForRefreshPossible( &REG_CLMAC.u1CLMABCE, (uint8)CLMA_CLMABCE_CLMABCE_DISABLE, (uint8)CLMA_CLMABCE_CLMABCE);
#endif /* MCU_CFG_CLMABCE */
	t_u4Result |= Mcu_Regchk_u1ForRefreshPossible( &REG_CLMA15.u1CLMA15CTL, (uint8)CLMA_CLMAnCTL_CLMAnCLME_ENABLE, (uint8)CLMA_CLMAnCTL_CLMAnCLME);
#else
	t_u4Result |= Mcu_Regchk_u1ForRefreshPossible( &REG_CLMA15.u1CLMA15CTL, (uint8)CLMA_CLMAnCTL_CLMAnCLME_DISABLE, (uint8)CLMA_CLMAnCTL_CLMAnCLME);
#endif

#if ( MCU_CFG_CLMA16CLME == STD_ON )
	t_u4Result |= Mcu_Regchk_u2ForRefreshPossible( &REG_CLMA16.u2CLMA16CMPL, MCU_CFG_CLMA16CMPL, (uint16)CLMA_CLMAnCMPL_CLMAnCMPL);
	t_u4Result |= Mcu_Regchk_u2ForRefreshPossible( &REG_CLMA16.u2CLMA16CMPH, MCU_CFG_CLMA16CMPH, (uint16)CLMA_CLMAnCMPH_CLMAnCMPH);
#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
	t_u4Result |= Mcu_Regchk_u1ForRefreshPossible( &REG_CLMA16.u1CLMA16STPDTEN, (uint8)CLMA_CLMAnSTPDTEN_DISABLE, (uint8)CLMA_CLMAnSTPDTEN_CLMAnSTPDTEN);
#endif
	t_u4Result |= Mcu_Regchk_u1ForRefreshPossible( &REG_CLMA16.u1CLMA16CTL, (uint8)CLMA_CLMAnCTL_CLMAnCLME_ENABLE, (uint8)CLMA_CLMAnCTL_CLMAnCLME);
#else
	t_u4Result |= Mcu_Regchk_u1ForRefreshPossible( &REG_CLMA16.u1CLMA16CTL, (uint8)CLMA_CLMAnCTL_CLMAnCLME_DISABLE, (uint8)CLMA_CLMAnCTL_CLMAnCLME);
#endif

#if ( MCU_CFG_CLMA17CLME == STD_ON )
	t_u4Result |= Mcu_Regchk_u2ForRefreshPossible( &REG_CLMA17.u2CLMA17CMPL, MCU_CFG_CLMA17CMPL, (uint16)CLMA_CLMAnCMPL_CLMAnCMPL);
	t_u4Result |= Mcu_Regchk_u2ForRefreshPossible( &REG_CLMA17.u2CLMA17CMPH, MCU_CFG_CLMA17CMPH, (uint16)CLMA_CLMAnCMPH_CLMAnCMPH);
	t_u4Result |= Mcu_Regchk_u1ForRefreshPossible( &REG_CLMA17.u1CLMA17CTL, (uint8)CLMA_CLMAnCTL_CLMAnCLME_ENABLE, (uint8)CLMA_CLMAnCTL_CLMAnCLME);
#else
	t_u4Result |= Mcu_Regchk_u1ForRefreshPossible( &REG_CLMA17.u1CLMA17CTL, (uint8)CLMA_CLMAnCTL_CLMAnCLME_DISABLE, (uint8)CLMA_CLMAnCTL_CLMAnCLME);
#endif
#endif /* MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B */

	REG_CLMAKCPROT.u4CLMAKCPROT = CLMA_CLMAKCPROT_DISABLE;

	t_u4Result &= ~MCU_REGCHK_RESULT_DUMMY_BIT;

	return ( t_u4Result );
}

/************************************************************************************************/
/* Function			:	Mcu_Regchk_u1ForRefreshPossible											*/
/* Reentrancy		:	Non Reentrant															*/
/* Parameters(in)	:	t_pu1Register - Register Address										*/
/* Parameters(in)	:	t_u1ExpectValue - Expected Register Value								*/
/* Parameters(in)	:	t_u1RegMask - Mask value for bits to check								*/
/* Return value		:	Register Check Result													*/
/* Limitation		:	Assumed that Protection Register has already enabled write access		*/
/************************************************************************************************/
static FUNC( uint32, MCU_CODE ) Mcu_Regchk_u1ForRefreshPossible( volatile uint8* t_pu1Register, const uint8 t_u1ExpectValue , const uint8 t_u1RegMask )
{
	uint32 t_u4Result;

	t_u4Result = MCU_REGCHK_OK;

	if( ( *t_pu1Register & t_u1RegMask ) != ( t_u1ExpectValue & t_u1RegMask ) )
	{
#if ( MCU_CFG_REG_REFRESH == STD_ON )
		*t_pu1Register = t_u1ExpectValue;
		if( ( *t_pu1Register & t_u1RegMask ) == ( t_u1ExpectValue & t_u1RegMask ) )
		{
			t_u4Result = MCU_REGCHK_REFRESH_SUCCESS;
		}
		else
		{
			t_u4Result = MCU_REGCHK_REFRESH_FAILED;
		}
#else
		t_u4Result = MCU_REGCHK_NG;
#endif	/* MCU_CFG_REG_REFRESH */
	}

	return ( t_u4Result );
}

/************************************************************************************************/
/* Function			:	Mcu_Regchk_u2ForRefreshPossible											*/
/* Reentrancy		:	Non Reentrant															*/
/* Parameters(in)	:	t_pu2Register - Register Address										*/
/* Parameters(in)	:	t_u2ExpectValue - Expected Register Value								*/
/* Parameters(in)	:	t_u2RegMask - Mask value for bits to check								*/
/* Return value		:	Register Check Result													*/
/* Limitation		:	Assumed that Protection Register has already enabled write access		*/
/************************************************************************************************/
static FUNC( uint32, MCU_CODE ) Mcu_Regchk_u2ForRefreshPossible( volatile uint16* t_pu2Register, const uint16 t_u2ExpectValue , const uint16 t_u2RegMask )
{
	uint32 t_u4Result;

	t_u4Result = MCU_REGCHK_OK;

	if( ( *t_pu2Register & t_u2RegMask ) != ( t_u2ExpectValue & t_u2RegMask ) )
	{
#if ( MCU_CFG_REG_REFRESH == STD_ON )
		*t_pu2Register = t_u2ExpectValue;
		if( ( *t_pu2Register & t_u2RegMask ) == ( t_u2ExpectValue & t_u2RegMask ) )
		{
			t_u4Result = MCU_REGCHK_REFRESH_SUCCESS;
		}
		else
		{
			t_u4Result = MCU_REGCHK_REFRESH_FAILED;
		}
#else
		t_u4Result = MCU_REGCHK_NG;
#endif	/* MCU_CFG_REG_REFRESH */
	}

	return ( t_u4Result );
}

#endif /* MCU_CFG_CLK_MONITOR == STD_ON */

#endif /* MCU_CFG_REG_CHK == STD_ON */

#define MCU_STOP_SEC_CODE_GLOBAL
#include "Mcu_MemMap.h"
/*-- End Of File -------------------------------------------------------------------------------*/
