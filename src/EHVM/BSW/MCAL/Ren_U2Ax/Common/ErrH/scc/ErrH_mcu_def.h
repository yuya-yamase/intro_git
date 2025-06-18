/* Bsw-r04-3000-0000-c */
/************************************************************************************************/
/*																								*/
/*		MCU type definition																		*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

#ifndef MCU_DEF_H
#define MCU_DEF_H

/*==============================================================================================*/
/*	include files																				*/
/*==============================================================================================*/
#include	"ErrH_cfg.h"

/*==============================================================================================*/
/*	Configuration Definition																	*/
/*==============================================================================================*/
#define		MCU_RENESAS			(1U)

// #define 	MCU_AURIX2G_TC3		(1U) 	/* AURIX2G_TC3x Series */
// #define 	MCU_RH850U2B		(2U) 	/* RH850U2B Series */
// #define 	MCU_RH850E2			(3U) 	/* RH850E2 Series */
// #define 	MCU_RH850E1			(4U) 	/* RH850E1 Series */
#define 	MCU_RH850U2A		(5U) 	/* RH850U2A Series */

// #define 	MCU_RH850E2M		(1U) 	/* RH850E2M */
// #define 	MCU_RH850U2B6		(2U) 	/* RH850U2B6 */
// #define 	MCU_RH850U2B10		(3U) 	/* RH850U2B10 */
#define 	MCU_RH850U2A6		(4U) 	/* RH850U2A6 */
#define 	MCU_RH850U2A16		(5U) 	/* RH850U2A16 */

// #define		MCU_GRADE_HI		(1U)		/* High Class */
// #define		MCU_GRADE_M1		(2U)		/* Middle 1 Class */
// #define		MCU_GRADE_M2		(3U)		/* Middle 2 Class */
// #define		MCU_GRADE_L1		(4U)		/* Low 1 Class */
// #define		MCU_GRADE_L2		(5U)		/* Low 2 Class */
// #define		MCU_GRADE_SL		(6U)		/* Super Low Class */

#define		MCU_PIN_373			(1U)		/* PIN373 */
#define		MCU_PIN_292			(2U)		/* PIN292 */

#define		MCU_CLK_400MHZ		(1U)		/* RENESAS(M1) */

// #define		MCU_OS_RV850		(1U)		/* RV850 */
#define		MCU_OS_AUBIST		(2U)		/* AUBIST */

// #define		MCU_ENDIAN_BIG		(1U)		/* Big Endian */
#define		MCU_ENDIAN_LIT		(2U)		/* Little Endian */

#define		MCU_CMP_GHILLS		(1U)		/* GreenHills */
// #define		MCU_CMP_HEW			(2U)		/* RENESAS Hew */

// #define		MCU_SINGLECORE		(1U)		/* Single Core */
#define		MCU_DUALCORE		(2U)		/* Dual Core */
// #define		MCU_TRIPLECORE		(3U)		/* Triple Core */
#define		MCU_QUADCORE		(4U)		/* Quad Core */

#define		MCU_CORE_0			(0U)		/* Core0 */
#define		MCU_CORE_1			(1U)		/* Core1 */
#define		MCU_CORE_2			(2U)		/* Core2 */
#define		MCU_CORE_3			(3U)		/* Core3 */

/*==============================================================================================*/
/*	TARGET definition																			*/
/*==============================================================================================*/
#if   ( BSW_CFG_TARGET == 10U )		/* RH850/U2B6 292Pin 使用コア2 */
	#define		MCU_MAKER			MCU_RENESAS
	#define		MCU_TYPE			MCU_RH850U2B
	#define 	MCU_TYPE_SERIES 	MCU_RH850U2B6
	#define		MCU_GRADE			MCU_GRADE_M1
	#define		MCU_PIN_NUM			MCU_PIN_292
	#define		MCU_LOCKSTEP_TYPE	MCU_DUALCORE
	#define		MCU_LOCKSTEP_NUM	MCU_DUALCORE
	#define		MCU_CLK_TYPE		MCU_CLK_400MHZ
	#define		MCU_OS_TYPE			MCU_OS_RV850
	#define		MCU_COMPILER_TYPE	MCU_CMP_GHILLS
	#define		MCU_ENDIAN_TYPE		MCU_ENDIAN_LIT
	#define		MCU_CORE_TYPE		MCU_TRIPLECORE
	#define		MCU_CORE_NUM		MCU_DUALCORE

#elif   ( BSW_CFG_TARGET == 11U )	/* RH850/U2B10 292Pin 使用コア2 */
	#define		MCU_MAKER			MCU_RENESAS
	#define		MCU_TYPE			MCU_RH850U2B
	#define 	MCU_TYPE_SERIES 	MCU_RH850U2B10
	#define		MCU_GRADE			MCU_GRADE_M1
	#define		MCU_PIN_NUM			MCU_PIN_292
	#define		MCU_LOCKSTEP_TYPE	MCU_TRIPLECORE
	#define		MCU_LOCKSTEP_NUM	MCU_DUALCORE
	#define		MCU_CLK_TYPE		MCU_CLK_400MHZ
	#define		MCU_OS_TYPE			MCU_OS_RV850
	#define		MCU_COMPILER_TYPE	MCU_CMP_GHILLS
	#define		MCU_ENDIAN_TYPE		MCU_ENDIAN_LIT
	#define		MCU_CORE_TYPE		MCU_TRIPLECORE
	#define		MCU_CORE_NUM		MCU_DUALCORE

#elif   ( BSW_CFG_TARGET == 12U )	/* RH850/U2B10 373Pin 使用コア2 */
	#define		MCU_MAKER			MCU_RENESAS
	#define		MCU_TYPE			MCU_RH850U2B
	#define 	MCU_TYPE_SERIES 	MCU_RH850U2B10
	#define		MCU_GRADE			MCU_GRADE_M1
	#define		MCU_PIN_NUM			MCU_PIN_373
	#define		MCU_LOCKSTEP_TYPE	MCU_TRIPLECORE
	#define		MCU_LOCKSTEP_NUM	MCU_DUALCORE
	#define		MCU_CLK_TYPE		MCU_CLK_400MHZ
	#define		MCU_OS_TYPE			MCU_OS_RV850
	#define		MCU_COMPILER_TYPE	MCU_CMP_GHILLS
	#define		MCU_ENDIAN_TYPE		MCU_ENDIAN_LIT
	#define		MCU_CORE_TYPE		MCU_TRIPLECORE
	#define		MCU_CORE_NUM		MCU_DUALCORE

#elif   ( BSW_CFG_TARGET == 13U )	/* RH850/U2B10 292Pin 使用コア2 */
	#define		MCU_MAKER			MCU_RENESAS
	#define		MCU_TYPE			MCU_RH850U2B
	#define 	MCU_TYPE_SERIES 	MCU_RH850U2B10
	#define		MCU_GRADE			MCU_GRADE_M1
	#define		MCU_PIN_NUM			MCU_PIN_292
	#define		MCU_LOCKSTEP_TYPE	MCU_DUALCORE
	#define		MCU_LOCKSTEP_NUM	MCU_DUALCORE
	#define		MCU_CLK_TYPE		MCU_CLK_400MHZ
	#define		MCU_OS_TYPE			MCU_OS_RV850
	#define		MCU_COMPILER_TYPE	MCU_CMP_GHILLS
	#define		MCU_ENDIAN_TYPE		MCU_ENDIAN_LIT
	#define		MCU_CORE_TYPE		MCU_QUADCORE
	#define		MCU_CORE_NUM		MCU_DUALCORE

#elif   ( BSW_CFG_TARGET == 14U )	/* RH850/U2B10 373Pin 使用コア2 */
	#define		MCU_MAKER			MCU_RENESAS
	#define		MCU_TYPE			MCU_RH850U2B
	#define 	MCU_TYPE_SERIES 	MCU_RH850U2B10
	#define		MCU_GRADE			MCU_GRADE_M1
	#define		MCU_PIN_NUM			MCU_PIN_373
	#define		MCU_LOCKSTEP_TYPE	MCU_DUALCORE
	#define		MCU_LOCKSTEP_NUM	MCU_DUALCORE
	#define		MCU_CLK_TYPE		MCU_CLK_400MHZ
	#define		MCU_OS_TYPE			MCU_OS_RV850
	#define		MCU_COMPILER_TYPE	MCU_CMP_GHILLS
	#define		MCU_ENDIAN_TYPE		MCU_ENDIAN_LIT
	#define		MCU_CORE_TYPE		MCU_QUADCORE
	#define		MCU_CORE_NUM		MCU_DUALCORE

#elif   ( BSW_CFG_TARGET == 15U )	/* RH850/U2B6 292Pin 使用コア3 */
	#define		MCU_MAKER			MCU_RENESAS
	#define		MCU_TYPE			MCU_RH850U2B
	#define 	MCU_TYPE_SERIES 	MCU_RH850U2B6
	#define		MCU_GRADE			MCU_GRADE_M1
	#define		MCU_PIN_NUM			MCU_PIN_292
	#define		MCU_LOCKSTEP_TYPE	MCU_DUALCORE
	#define		MCU_LOCKSTEP_NUM	MCU_DUALCORE
	#define		MCU_CLK_TYPE		MCU_CLK_400MHZ
	#define		MCU_OS_TYPE			MCU_OS_RV850
	#define		MCU_COMPILER_TYPE	MCU_CMP_GHILLS
	#define		MCU_ENDIAN_TYPE		MCU_ENDIAN_LIT
	#define		MCU_CORE_TYPE		MCU_TRIPLECORE
	#define		MCU_CORE_NUM		MCU_TRIPLECORE

#elif   ( BSW_CFG_TARGET == 16U )	/* RH850/U2B10 292Pin 使用コア3 */
	#define		MCU_MAKER			MCU_RENESAS
	#define		MCU_TYPE			MCU_RH850U2B
	#define 	MCU_TYPE_SERIES 	MCU_RH850U2B10
	#define		MCU_GRADE			MCU_GRADE_M1
	#define		MCU_PIN_NUM			MCU_PIN_292
	#define		MCU_LOCKSTEP_TYPE	MCU_TRIPLECORE
	#define		MCU_LOCKSTEP_NUM	MCU_TRIPLECORE
	#define		MCU_CLK_TYPE		MCU_CLK_400MHZ
	#define		MCU_OS_TYPE			MCU_OS_RV850
	#define		MCU_COMPILER_TYPE	MCU_CMP_GHILLS
	#define		MCU_ENDIAN_TYPE		MCU_ENDIAN_LIT
	#define		MCU_CORE_TYPE		MCU_TRIPLECORE
	#define		MCU_CORE_NUM		MCU_TRIPLECORE

#elif   ( BSW_CFG_TARGET == 17U )	/* RH850/U2B10 373Pin 使用コア3 */
	#define		MCU_MAKER			MCU_RENESAS
	#define		MCU_TYPE			MCU_RH850U2B
	#define 	MCU_TYPE_SERIES 	MCU_RH850U2B10
	#define		MCU_GRADE			MCU_GRADE_M1
	#define		MCU_PIN_NUM			MCU_PIN_373
	#define		MCU_LOCKSTEP_TYPE	MCU_TRIPLECORE
	#define		MCU_LOCKSTEP_NUM	MCU_TRIPLECORE
	#define		MCU_CLK_TYPE		MCU_CLK_400MHZ
	#define		MCU_OS_TYPE			MCU_OS_RV850
	#define		MCU_COMPILER_TYPE	MCU_CMP_GHILLS
	#define		MCU_ENDIAN_TYPE		MCU_ENDIAN_LIT
	#define		MCU_CORE_TYPE		MCU_TRIPLECORE
	#define		MCU_CORE_NUM		MCU_TRIPLECORE

#elif   ( BSW_CFG_TARGET == 18U )	/* RH850/U2B10 292Pin 使用コア3 */
	#define		MCU_MAKER			MCU_RENESAS
	#define		MCU_TYPE			MCU_RH850U2B
	#define 	MCU_TYPE_SERIES 	MCU_RH850U2B10
	#define		MCU_GRADE			MCU_GRADE_M1
	#define		MCU_PIN_NUM			MCU_PIN_292
	#define		MCU_LOCKSTEP_TYPE	MCU_DUALCORE
	#define		MCU_LOCKSTEP_NUM	MCU_DUALCORE
	#define		MCU_CLK_TYPE		MCU_CLK_400MHZ
	#define		MCU_OS_TYPE			MCU_OS_RV850
	#define		MCU_COMPILER_TYPE	MCU_CMP_GHILLS
	#define		MCU_ENDIAN_TYPE		MCU_ENDIAN_LIT
	#define		MCU_CORE_TYPE		MCU_QUADCORE
	#define		MCU_CORE_NUM		MCU_TRIPLECORE

#elif   ( BSW_CFG_TARGET == 19U )	/* RH850/U2B10 373Pin 使用コア3 */
	#define		MCU_MAKER			MCU_RENESAS
	#define		MCU_TYPE			MCU_RH850U2B
	#define 	MCU_TYPE_SERIES 	MCU_RH850U2B10
	#define		MCU_GRADE			MCU_GRADE_M1
	#define		MCU_PIN_NUM			MCU_PIN_373
	#define		MCU_LOCKSTEP_TYPE	MCU_DUALCORE
	#define		MCU_LOCKSTEP_NUM	MCU_DUALCORE
	#define		MCU_CLK_TYPE		MCU_CLK_400MHZ
	#define		MCU_OS_TYPE			MCU_OS_RV850
	#define		MCU_COMPILER_TYPE	MCU_CMP_GHILLS
	#define		MCU_ENDIAN_TYPE		MCU_ENDIAN_LIT
	#define		MCU_CORE_TYPE		MCU_QUADCORE
	#define		MCU_CORE_NUM		MCU_TRIPLECORE

#elif   ( BSW_CFG_TARGET == 20U )	/* RH850/U2B10 292Pin 使用コア4 */
	#define		MCU_MAKER			MCU_RENESAS
	#define		MCU_TYPE			MCU_RH850U2B
	#define 	MCU_TYPE_SERIES 	MCU_RH850U2B10
	#define		MCU_GRADE			MCU_GRADE_M1
	#define		MCU_PIN_NUM			MCU_PIN_292
	#define		MCU_LOCKSTEP_TYPE	MCU_DUALCORE
	#define		MCU_LOCKSTEP_NUM	MCU_DUALCORE
	#define		MCU_CLK_TYPE		MCU_CLK_400MHZ
	#define		MCU_OS_TYPE			MCU_OS_RV850
	#define		MCU_COMPILER_TYPE	MCU_CMP_GHILLS
	#define		MCU_ENDIAN_TYPE		MCU_ENDIAN_LIT
	#define		MCU_CORE_TYPE		MCU_QUADCORE
	#define		MCU_CORE_NUM		MCU_QUADCORE

#elif   ( BSW_CFG_TARGET == 21U )	/* RH850/U2B10 373Pin 使用コア4 */
	#define		MCU_MAKER			MCU_RENESAS
	#define		MCU_TYPE			MCU_RH850U2B
	#define 	MCU_TYPE_SERIES 	MCU_RH850U2B10
	#define		MCU_GRADE			MCU_GRADE_M1
	#define		MCU_PIN_NUM			MCU_PIN_373
	#define		MCU_LOCKSTEP_TYPE	MCU_DUALCORE
	#define		MCU_LOCKSTEP_NUM	MCU_DUALCORE
	#define		MCU_CLK_TYPE		MCU_CLK_400MHZ
	#define		MCU_OS_TYPE			MCU_OS_RV850
	#define		MCU_COMPILER_TYPE	MCU_CMP_GHILLS
	#define		MCU_ENDIAN_TYPE		MCU_ENDIAN_LIT
	#define		MCU_CORE_TYPE		MCU_QUADCORE
	#define		MCU_CORE_NUM		MCU_QUADCORE

#elif   ( BSW_CFG_TARGET == 22U )	/* RH850/U2A6 292Pin 使用コア2 */
	#define		MCU_MAKER			MCU_RENESAS
	#define		MCU_TYPE			MCU_RH850U2A
	#define 	MCU_TYPE_SERIES 	MCU_RH850U2A6
	#define		MCU_GRADE			MCU_GRADE_M1
	#define		MCU_PIN_NUM			MCU_PIN_292
	#define		MCU_LOCKSTEP_TYPE	MCU_DUALCORE
	#define		MCU_LOCKSTEP_NUM	MCU_DUALCORE
	#define		MCU_CLK_TYPE		MCU_CLK_400MHZ
	#define		MCU_OS_TYPE			MCU_OS_AUBIST
	#define		MCU_COMPILER_TYPE	MCU_CMP_GHILLS
	#define		MCU_ENDIAN_TYPE		MCU_ENDIAN_LIT
	#define		MCU_CORE_TYPE		MCU_QUADCORE
	#define		MCU_CORE_NUM		MCU_DUALCORE

#elif   ( BSW_CFG_TARGET == 23U )	/* RH850/U2A16 373Pin 使用コア4 */
	#define		MCU_MAKER			MCU_RENESAS
	#define		MCU_TYPE			MCU_RH850U2A
	#define 	MCU_TYPE_SERIES 	MCU_RH850U2A16
	#define		MCU_GRADE			MCU_GRADE_M1
	#define		MCU_PIN_NUM			MCU_PIN_373
	#define		MCU_LOCKSTEP_TYPE	MCU_DUALCORE
	#define		MCU_LOCKSTEP_NUM	MCU_DUALCORE
	#define		MCU_CLK_TYPE		MCU_CLK_400MHZ
	#define		MCU_OS_TYPE			MCU_OS_AUBIST
	#define		MCU_COMPILER_TYPE	MCU_CMP_GHILLS
	#define		MCU_ENDIAN_TYPE		MCU_ENDIAN_LIT
	#define		MCU_CORE_TYPE		MCU_QUADCORE
	#define		MCU_CORE_NUM		MCU_QUADCORE

#else
	#error "BSW_CFG_TARGET 設定間違い"

#endif


/*----------------------------------------------------------------------------------------------*/
/*	自動設定項目																				*/
/*----------------------------------------------------------------------------------------------*/


#endif /* MCU_DEF_H */
/*-- End Of File -------------------------------------------------------------------------------*/
