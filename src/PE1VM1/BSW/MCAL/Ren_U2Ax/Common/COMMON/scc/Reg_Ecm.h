/* Reg_ECM-r04-307 */
/************************************************************************************************/
/*																								*/
/*		Ecm register definition (for RH850U2A and RH850U2B and RCARS4 G4MH)						*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

#ifndef PORT_REG_ECM
#define PORT_REG_ECM

/*==============================================================================================*/
/* include files																				*/
/*==============================================================================================*/
#include	"Std_Types.h"

/*==============================================================================================*/
/*	register type definition																	*/
/*==============================================================================================*/
#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
#if ( ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A16_516PIN ) || ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A16_373PIN ) || ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A16_292PIN ) )
#define ECM_INDEX_MAX_J		((uint8)11U)			/* j = 0 to 10 */
#elif ( ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A8_373PIN ) || ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A6_292PIN ) || ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A8_292PIN ) || ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A6_144PIN ) )
#define ECM_INDEX_MAX_J		((uint8)9U)				/* j = 0 to 8 */
#endif
#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) */
#if MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B
#define ECM_INDEX_MAX_J		((uint8)10U)			/* j = 0 to 9 */
#endif
#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RCARS4_G4MH )
#define ECM_INDEX_MAX_J		((uint8)12U)			/* j = 0 to 11 */
#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RCARS4_G4MH ) */


typedef	struct {

	struct {
		uint32	u4ECMMESET;							/* 0xFFD39000 - 0xFFD39004 */

		uint32	u4ECMMECLR;							/* 0xFFD39004 - 0xFFD39008 */

		uint32	u4ECMMESET0;						/* 0xFFD39008 - 0xFFD3900C */

		uint32	u4ECMMECLR0;						/* 0xFFD3900C - 0xFFD39010 */

		uint32	u4ECMMESET1;						/* 0xFFD39010 - 0xFFD39014 */

		uint32	u4ECMMECLR1;						/* 0xFFD39014 - 0xFFD39018 */
#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
#if ( ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A16_516PIN ) || ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A16_373PIN ) || ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A16_292PIN ) )
		uint32	u4ECMMESET2;						/* 0xFFD39018 - 0xFFD3901C */

		uint32	u4ECMMECLR2;						/* 0xFFD3901C - 0xFFD39020 */

		uint32	u4ECMMESET3;						/* 0xFFD39020 - 0xFFD39024 */

		uint32	u4ECMMECLR3;						/* 0xFFD39024 - 0xFFD39028 */

		uint8	u1Dummy1[( 0xFFD39048U - 0xFFD39028U )];
#elif ( ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A8_373PIN ) || ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A6_292PIN ) || ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A8_292PIN ) || ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A6_144PIN ) )
		uint8	u1Dummy1[( 0xFFD39048U - 0xFFD39018U )];
#endif
#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) */
#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
		uint32	u4ECMMESET2;						/* 0xFFD39018 - 0xFFD3901C */

		uint32	u4ECMMECLR2;						/* 0xFFD3901C - 0xFFD39020 */

		uint8	u1Dummy1[( 0xFFD39048U - 0xFFD39020U )];
#endif
#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RCARS4_G4MH )
		uint8	u1Dummy1[( 0xFFD39048U - 0xFFD39018U )];
#endif
		uint32	u4ECMMESSTRj[ECM_INDEX_MAX_J];		/* 0xFFD39048 - (0xFFD39048 + 4*j) */

	} stECMMASTER;
} REGTYPE_ECM_MASTER;

typedef	struct {

	struct {
		uint32	u4ECMCESET;							/* 0xFFD3A000 - 0xFFD3A004 */

		uint32	u4ECMCECLR;							/* 0xFFD3A004 - 0xFFD3A008 */

		uint32	u4ECMMCSET0;						/* 0xFFD3A008 - 0xFFD3A00C */

		uint32	u4ECMCECLR0;						/* 0xFFD3A00C - 0xFFD3A010 */

		uint32	u4ECMMCSET1;						/* 0xFFD3A010 - 0xFFD3A014 */

		uint32	u4ECMCECLR1;						/* 0xFFD3A014 - 0xFFD3A018 */
#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
#if ( ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A16_516PIN ) || ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A16_373PIN ) || ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A16_292PIN ) )
		uint32	u4ECMCESET2;						/* 0xFFD3A018 - 0xFFD3A01C */

		uint32	u4ECMCECLR2;						/* 0xFFD3A01C - 0xFFD3A020 */

		uint32	u4ECMCESET3;						/* 0xFFD3A020 - 0xFFD3A024 */

		uint32	u4ECMCECLR3;						/* 0xFFD3A024 - 0xFFD3A028 */

		uint8	u1Dummy1[( 0xFFD39048U - 0xFFD39028U )];
#elif ( ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A8_373PIN ) || ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A6_292PIN ) || ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A8_292PIN ) || ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A6_144PIN ) )
		uint8	u1Dummy1[( 0xFFD39048U - 0xFFD39018U )];
#endif
#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) */
#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
		uint32	u4ECMCESET2;						/* 0xFFD3A018 - 0xFFD3901C */

		uint32	u4ECMCECLR2;						/* 0xFFD3A01C - 0xFFD39020 */

		uint8	u1Dummy1[( 0xFFD39048U - 0xFFD39020U )];
#endif
#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RCARS4_G4MH )
		uint8	u1Dummy1[( 0xFFD3A048U - 0xFFD3A018U )];
#endif
		uint32	u4ECMCESSTRj[ECM_INDEX_MAX_J];		/* 0xFFD3A048 - (0xFFD3A048 + 4*j) */

	} stECMCHECKER;
} REGTYPE_ECM_CHECKER;

typedef	struct {

	struct {
#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
#if ( ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A16_516PIN ) || ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A16_373PIN ) || ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A16_292PIN ) )
		uint8	u1Dummy1[( 0xFFD38004U - 0xFFD38000U )];
		uint32	u4ECMISCFG0;						/* 0xFFD38004 - 0xFFD38008 */
		uint32	u4ECMISCFG1;						/* 0xFFD38008 - 0xFFD3800C */
		uint32	u4ECMISCFG2;						/* 0xFFD3800C - 0xFFD38010 */
		uint32	u4ECMISCFG3;						/* 0xFFD38010 - 0xFFD38014 */
		uint32	u4ECMISCFG4;						/* 0xFFD38014 - 0xFFD38018 */
		uint32	u4ECMISCFG5;						/* 0xFFD38018 - 0xFFD3801C */
		uint32	u4ECMISCFG6;						/* 0xFFD3801C - 0xFFD38020 */
		uint32	u4ECMISCFG7;						/* 0xFFD38020 - 0xFFD38024 */
		uint32	u4ECMISCFG8;						/* 0xFFD38024 - 0xFFD38028 */
		uint32	u4ECMISCFG9;						/* 0xFFD38028 - 0xFFD3802C */
		uint32	u4ECMISCFG10;						/* 0xFFD3802C - 0xFFD38030 */
		uint8	u1Dummy2[( 0xFFD38040U - 0xFFD38030U )];
		uint32	u4ECMINCFG0_0;						/* 0xFFD38040 - 0xFFD38044 */
		uint32	u4ECMINCFG0_1;						/* 0xFFD38044 - 0xFFD38048 */
		uint32	u4ECMINCFG0_2;						/* 0xFFD38048 - 0xFFD3804C */
		uint32	u4ECMINCFG0_3;						/* 0xFFD3804C - 0xFFD38050 */
		uint32	u4ECMINCFG0_4;						/* 0xFFD38050 - 0xFFD38054 */
		uint32	u4ECMINCFG0_5;						/* 0xFFD38054 - 0xFFD38058 */
		uint32	u4ECMINCFG0_6;						/* 0xFFD38058 - 0xFFD3805C */
		uint32	u4ECMINCFG0_7;						/* 0xFFD3805C - 0xFFD38060 */
		uint32	u4ECMINCFG0_8;						/* 0xFFD38060 - 0xFFD38064 */
		uint32	u4ECMINCFG0_9;						/* 0xFFD38064 - 0xFFD38068 */
		uint32	u4ECMINCFG0_10;						/* 0xFFD38068 - 0xFFD3806C */
		uint8	u1Dummy3[( 0xFFD3807CU - 0xFFD3806CU )];
		uint32	u4ECMINCFG1_0;						/* 0xFFD3807C - 0xFFD38080 */
		uint32	u4ECMINCFG1_1;						/* 0xFFD38080 - 0xFFD38084 */
		uint32	u4ECMINCFG1_2;						/* 0xFFD38084 - 0xFFD38088 */
		uint32	u4ECMINCFG1_3;						/* 0xFFD38088 - 0xFFD3808C */
		uint32	u4ECMINCFG1_4;						/* 0xFFD3808C - 0xFFD38090 */
		uint32	u4ECMINCFG1_5;						/* 0xFFD38090 - 0xFFD38094 */
		uint32	u4ECMINCFG1_6;						/* 0xFFD38094 - 0xFFD38098 */
		uint32	u4ECMINCFG1_7;						/* 0xFFD38098 - 0xFFD3809C */
		uint32	u4ECMINCFG1_8;						/* 0xFFD3809C - 0xFFD380A0 */
		uint32	u4ECMINCFG1_9;						/* 0xFFD380A0 - 0xFFD380A4 */
		uint32	u4ECMINCFG1_10;						/* 0xFFD380A4 - 0xFFD380A8 */
		uint8	u1Dummy4[( 0xFFD380B8U - 0xFFD380A8U )];
		uint32	u4ECMINCFG2_0;						/* 0xFFD380B8 - 0xFFD380BC */
		uint32	u4ECMINCFG2_1;						/* 0xFFD380BC - 0xFFD380C0 */
		uint32	u4ECMINCFG2_2;						/* 0xFFD380C0 - 0xFFD380C4 */
		uint32	u4ECMINCFG2_3;						/* 0xFFD380C4 - 0xFFD380C8 */
		uint32	u4ECMINCFG2_4;						/* 0xFFD380C8 - 0xFFD380CC */
		uint32	u4ECMINCFG2_5;						/* 0xFFD380CC - 0xFFD380D0 */
		uint32	u4ECMINCFG2_6;						/* 0xFFD380D0 - 0xFFD380D4 */
		uint32	u4ECMINCFG2_7;						/* 0xFFD380D4 - 0xFFD380D8 */
		uint32	u4ECMINCFG2_8;						/* 0xFFD380D8 - 0xFFD380DC */
		uint32	u4ECMINCFG2_9;						/* 0xFFD380DC - 0xFFD380E0 */
		uint32	u4ECMINCFG2_10;						/* 0xFFD380E0 - 0xFFD380E4 */
		uint8	u1Dummy5[( 0xFFD380F4U - 0xFFD380E4U )];
		uint32	u4ECMINCFG3_0;						/* 0xFFD380F4 - 0xFFD380F8 */
		uint32	u4ECMINCFG3_1;						/* 0xFFD380F8 - 0xFFD380FC */
		uint32	u4ECMINCFG3_2;						/* 0xFFD380FC - 0xFFD38100 */
		uint32	u4ECMINCFG3_3;						/* 0xFFD38100 - 0xFFD38104 */
		uint32	u4ECMINCFG3_4;						/* 0xFFD38104 - 0xFFD38108 */
		uint32	u4ECMINCFG3_5;						/* 0xFFD38108 - 0xFFD3810C */
		uint32	u4ECMINCFG3_6;						/* 0xFFD3810C - 0xFFD38110 */
		uint32	u4ECMINCFG3_7;						/* 0xFFD38110 - 0xFFD38114 */
		uint32	u4ECMINCFG3_8;						/* 0xFFD38114 - 0xFFD38118 */
		uint32	u4ECMINCFG3_9;						/* 0xFFD38118 - 0xFFD3811C */
		uint32	u4ECMINCFG3_10;						/* 0xFFD3811C - 0xFFD38120 */
		uint8	u1Dummy6[( 0xFFD38220U - 0xFFD38120U )];
		uint32	u4ECMIRCFG0;						/* 0xFFD38220 - 0xFFD38224 */
		uint32	u4ECMIRCFG1;						/* 0xFFD38224 - 0xFFD38228 */
		uint32	u4ECMIRCFG2;						/* 0xFFD38228 - 0xFFD3822C */
		uint32	u4ECMIRCFG3;						/* 0xFFD3822C - 0xFFD38230 */
		uint32	u4ECMIRCFG4;						/* 0xFFD38230 - 0xFFD38234 */
		uint32	u4ECMIRCFG5;						/* 0xFFD38234 - 0xFFD38238 */
		uint32	u4ECMIRCFG6;						/* 0xFFD38238 - 0xFFD3823C */
		uint32	u4ECMIRCFG7;						/* 0xFFD3823C - 0xFFD38240 */
		uint32	u4ECMIRCFG8;						/* 0xFFD38240 - 0xFFD38244 */
		uint32	u4ECMIRCFG9;						/* 0xFFD38244 - 0xFFD38248 */
		uint32	u4ECMIRCFG10;						/* 0xFFD38248 - 0xFFD3824C */
		uint8	u1Dummy7[( 0xFFD3825CU - 0xFFD3824CU )];
		uint32	u4ECMEMK0;							/* 0xFFD3825C - 0xFFD38260 */
		uint32	u4ECMEMK1;							/* 0xFFD38260 - 0xFFD38264 */
		uint32	u4ECMEMK2;							/* 0xFFD38264 - 0xFFD38268 */
		uint32	u4ECMEMK3;							/* 0xFFD38268 - 0xFFD3826C */
		uint32	u4ECMEMK4;							/* 0xFFD3826C - 0xFFD38270 */
		uint32	u4ECMEMK5;							/* 0xFFD38270 - 0xFFD38274 */
		uint32	u4ECMEMK6;							/* 0xFFD38274 - 0xFFD38278 */
		uint32	u4ECMEMK7;							/* 0xFFD38278 - 0xFFD3827C */
		uint32	u4ECMEMK8;							/* 0xFFD3827C - 0xFFD38280 */
		uint32	u4ECMEMK9;							/* 0xFFD38280 - 0xFFD38284 */
		uint32	u4ECMEMK10;							/* 0xFFD38284 - 0xFFD38288 */
		uint8	u1Dummy8[( 0xFFD38478U - 0xFFD38288U )];
		uint32	u4ECMESSTC0;						/* 0xFFD38478 - 0xFFD3847C */
		uint32	u4ECMESSTC1;						/* 0xFFD3847C - 0xFFD38480 */
		uint32	u4ECMESSTC2;						/* 0xFFD38480 - 0xFFD38484 */
		uint32	u4ECMESSTC3;						/* 0xFFD38484 - 0xFFD38488 */
		uint32	u4ECMESSTC4;						/* 0xFFD38488 - 0xFFD3848C */
		uint32	u4ECMESSTC5;						/* 0xFFD3848C - 0xFFD38490 */
		uint32	u4ECMESSTC6;						/* 0xFFD38490 - 0xFFD38494 */
		uint32	u4ECMESSTC7;						/* 0xFFD38494 - 0xFFD38498 */
		uint32	u4ECMESSTC8;						/* 0xFFD38498 - 0xFFD3849C */
		uint32	u4ECMESSTC9;						/* 0xFFD3849C - 0xFFD384A0 */
		uint32	u4ECMESSTC10;						/* 0xFFD384A0 - 0xFFD384A4 */
		uint8	u1Dummy9[( 0xFFD384B4U - 0xFFD384A4U )];
		uint32	u4ECMKCPROT;						/* 0xFFD384B4 - 0xFFD384B8 */
		uint8	u1Dummy10[( 0xFFD38740U - 0xFFD384B8U )];
		uint32	u4ECMPEM;							/* 0xFFD38740 - 0xFFD38744 */
#elif ( ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A8_373PIN ) || ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A6_292PIN ) || ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A8_292PIN ) || ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A6_144PIN ) )
		uint8	u1Dummy1[( 0xFFD38004U - 0xFFD38000U )];
		uint32	u4ECMISCFG0;						/* 0xFFD38004 - 0xFFD38008 */
		uint32	u4ECMISCFG1;						/* 0xFFD38008 - 0xFFD3800C */
		uint32	u4ECMISCFG2;						/* 0xFFD3800C - 0xFFD38010 */
		uint32	u4ECMISCFG3;						/* 0xFFD38010 - 0xFFD38014 */
		uint32	u4ECMISCFG4;						/* 0xFFD38014 - 0xFFD38018 */
		uint32	u4ECMISCFG5;						/* 0xFFD38018 - 0xFFD3801C */
		uint32	u4ECMISCFG6;						/* 0xFFD3801C - 0xFFD38020 */
		uint32	u4ECMISCFG7;						/* 0xFFD38020 - 0xFFD38024 */
		uint32	u4ECMISCFG8;						/* 0xFFD38024 - 0xFFD38028 */
		uint8	u1Dummy2[( 0xFFD38040U - 0xFFD38028U )];
		uint32	u4ECMINCFG0_0;						/* 0xFFD38040 - 0xFFD38044 */
		uint32	u4ECMINCFG0_1;						/* 0xFFD38044 - 0xFFD38048 */
		uint32	u4ECMINCFG0_2;						/* 0xFFD38048 - 0xFFD3804C */
		uint32	u4ECMINCFG0_3;						/* 0xFFD3804C - 0xFFD38050 */
		uint32	u4ECMINCFG0_4;						/* 0xFFD38050 - 0xFFD38054 */
		uint32	u4ECMINCFG0_5;						/* 0xFFD38054 - 0xFFD38058 */
		uint32	u4ECMINCFG0_6;						/* 0xFFD38058 - 0xFFD3805C */
		uint32	u4ECMINCFG0_7;						/* 0xFFD3805C - 0xFFD38060 */
		uint32	u4ECMINCFG0_8;						/* 0xFFD38060 - 0xFFD38064 */
		uint8	u1Dummy3[( 0xFFD3807CU - 0xFFD38064U )];
		uint32	u4ECMINCFG1_0;						/* 0xFFD3807C - 0xFFD38080 */
		uint32	u4ECMINCFG1_1;						/* 0xFFD38080 - 0xFFD38084 */
		uint32	u4ECMINCFG1_2;						/* 0xFFD38084 - 0xFFD38088 */
		uint32	u4ECMINCFG1_3;						/* 0xFFD38088 - 0xFFD3808C */
		uint32	u4ECMINCFG1_4;						/* 0xFFD3808C - 0xFFD38090 */
		uint32	u4ECMINCFG1_5;						/* 0xFFD38090 - 0xFFD38094 */
		uint32	u4ECMINCFG1_6;						/* 0xFFD38094 - 0xFFD38098 */
		uint32	u4ECMINCFG1_7;						/* 0xFFD38098 - 0xFFD3809C */
		uint32	u4ECMINCFG1_8;						/* 0xFFD3809C - 0xFFD380A0 */
		uint8	u1Dummy4[( 0xFFD38220U - 0xFFD380A0U )];
		uint32	u4ECMIRCFG0;						/* 0xFFD38220 - 0xFFD38224 */
		uint32	u4ECMIRCFG1;						/* 0xFFD38224 - 0xFFD38228 */
		uint32	u4ECMIRCFG2;						/* 0xFFD38228 - 0xFFD3822C */
		uint32	u4ECMIRCFG3;						/* 0xFFD3822C - 0xFFD38230 */
		uint32	u4ECMIRCFG4;						/* 0xFFD38230 - 0xFFD38234 */
		uint32	u4ECMIRCFG5;						/* 0xFFD38234 - 0xFFD38238 */
		uint32	u4ECMIRCFG6;						/* 0xFFD38238 - 0xFFD3823C */
		uint32	u4ECMIRCFG7;						/* 0xFFD3823C - 0xFFD38240 */
		uint32	u4ECMIRCFG8;						/* 0xFFD38240 - 0xFFD38244 */
		uint32	u4ECMIRCFG9;						/* 0xFFD38244 - 0xFFD38248 */
		uint32	u4ECMIRCFG10;						/* 0xFFD38248 - 0xFFD3824C */
		uint8	u1Dummy5[( 0xFFD3825CU - 0xFFD3824CU )];
		uint32	u4ECMEMK0;							/* 0xFFD3825C - 0xFFD38260 */
		uint32	u4ECMEMK1;							/* 0xFFD38260 - 0xFFD38264 */
		uint32	u4ECMEMK2;							/* 0xFFD38264 - 0xFFD38268 */
		uint32	u4ECMEMK3;							/* 0xFFD38268 - 0xFFD3826C */
		uint32	u4ECMEMK4;							/* 0xFFD3826C - 0xFFD38270 */
		uint32	u4ECMEMK5;							/* 0xFFD38270 - 0xFFD38274 */
		uint32	u4ECMEMK6;							/* 0xFFD38274 - 0xFFD38278 */
		uint32	u4ECMEMK7;							/* 0xFFD38278 - 0xFFD3827C */
		uint32	u4ECMEMK8;							/* 0xFFD3827C - 0xFFD38280 */
		uint32	u4ECMEMK9;							/* 0xFFD38280 - 0xFFD38284 */
		uint32	u4ECMEMK10;							/* 0xFFD38284 - 0xFFD38288 */
		uint8	u1Dummy6[( 0xFFD38478U - 0xFFD38288U )];
		uint32	u4ECMESSTC0;						/* 0xFFD38478 - 0xFFD3847C */
		uint32	u4ECMESSTC1;						/* 0xFFD3847C - 0xFFD38480 */
		uint32	u4ECMESSTC2;						/* 0xFFD38480 - 0xFFD38484 */
		uint32	u4ECMESSTC3;						/* 0xFFD38484 - 0xFFD38488 */
		uint32	u4ECMESSTC4;						/* 0xFFD38488 - 0xFFD3848C */
		uint32	u4ECMESSTC5;						/* 0xFFD3848C - 0xFFD38490 */
		uint32	u4ECMESSTC6;						/* 0xFFD38490 - 0xFFD38494 */
		uint32	u4ECMESSTC7;						/* 0xFFD38494 - 0xFFD38498 */
		uint32	u4ECMESSTC8;						/* 0xFFD38498 - 0xFFD3849C */
		uint8	u1Dummy7[( 0xFFD384B4U - 0xFFD3849CU )];
		uint32	u4ECMKCPROT;						/* 0xFFD384B4 - 0xFFD384B8 */
		uint8	u1Dummy8[( 0xFFD38740U - 0xFFD384B8U )];
		uint32	u4ECMPEM;							/* 0xFFD38740 - 0xFFD38744 */
#endif	/* MCAL_PKG_U2A_TARGET */

#elif	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
		uint8	u1Dummy1[( 0xFFCCD004U - 0xFFCCD000U )];
		uint32	u4ECMISCFG0;						/* 0xFFCCD004 - 0xFFCCD008 */
		uint32	u4ECMISCFG1;						/* 0xFFCCD008 - 0xFFCCD00C */
		uint32	u4ECMISCFG2;						/* 0xFFCCD00C - 0xFFCCD010 */
		uint32	u4ECMISCFG3;						/* 0xFFCCD010 - 0xFFCCD014 */
		uint32	u4ECMISCFG4;						/* 0xFFCCD014 - 0xFFCCD018 */
		uint32	u4ECMISCFG5;						/* 0xFFCCD018 - 0xFFCCD01C */
		uint32	u4ECMISCFG6;						/* 0xFFCCD01C - 0xFFCCD020 */
		uint32	u4ECMISCFG7;						/* 0xFFCCD020 - 0xFFCCD024 */
		uint32	u4ECMISCFG8;						/* 0xFFCCD024 - 0xFFCCD028 */
		uint32	u4ECMISCFG9;						/* 0xFFCCD028 - 0xFFCCD02C */
		uint8	u1Dummy2[( 0xFFCCD040U - 0xFFCCD02CU )];
		uint32	u4ECMINCFG0_0;						/* 0xFFCCD040 - 0xFFCCD044 */
		uint32	u4ECMINCFG0_1;						/* 0xFFCCD044 - 0xFFCCD048 */
		uint32	u4ECMINCFG0_2;						/* 0xFFCCD048 - 0xFFCCD04C */
		uint32	u4ECMINCFG0_3;						/* 0xFFCCD04C - 0xFFCCD050 */
		uint32	u4ECMINCFG0_4;						/* 0xFFCCD050 - 0xFFCCD054 */
		uint32	u4ECMINCFG0_5;						/* 0xFFCCD054 - 0xFFCCD058 */
		uint32	u4ECMINCFG0_6;						/* 0xFFCCD058 - 0xFFCCD05C */
		uint32	u4ECMINCFG0_7;						/* 0xFFCCD05C - 0xFFCCD060 */
		uint32	u4ECMINCFG0_8;						/* 0xFFCCD060 - 0xFFCCD064 */
		uint32	u4ECMINCFG0_9;						/* 0xFFCCD064 - 0xFFCCD068 */
		uint8	u1Dummy3[( 0xFFCCD07CU - 0xFFCCD068U )];
		uint32	u4ECMINCFG1_0;						/* 0xFFCCD07C - 0xFFCCD080 */
		uint32	u4ECMINCFG1_1;						/* 0xFFCCD080 - 0xFFCCD084 */
		uint32	u4ECMINCFG1_2;						/* 0xFFCCD084 - 0xFFCCD088 */
		uint32	u4ECMINCFG1_3;						/* 0xFFCCD088 - 0xFFCCD08C */
		uint32	u4ECMINCFG1_4;						/* 0xFFCCD08C - 0xFFCCD090 */
		uint32	u4ECMINCFG1_5;						/* 0xFFCCD090 - 0xFFCCD094 */
		uint32	u4ECMINCFG1_6;						/* 0xFFCCD094 - 0xFFCCD098 */
		uint32	u4ECMINCFG1_7;						/* 0xFFCCD098 - 0xFFCCD09C */
		uint32	u4ECMINCFG1_8;						/* 0xFFCCD09C - 0xFFCCD0A0 */
		uint32	u4ECMINCFG1_9;						/* 0xFFCCD0A0 - 0xFFCCD0A4 */
		uint8	u1Dummy4[( 0xFFCCD0B8U - 0xFFCCD0A4U )];
		uint32	u4ECMINCFG2_0;						/* 0xFFCCD0B8 - 0xFFCCD0BC */
		uint32	u4ECMINCFG2_1;						/* 0xFFCCD0BC - 0xFFCCD0C0 */
		uint32	u4ECMINCFG2_2;						/* 0xFFCCD0C0 - 0xFFCCD0C4 */
		uint32	u4ECMINCFG2_3;						/* 0xFFCCD0C4 - 0xFFCCD0C8 */
		uint32	u4ECMINCFG2_4;						/* 0xFFCCD0C8 - 0xFFCCD0CC */
		uint32	u4ECMINCFG2_5;						/* 0xFFCCD0CC - 0xFFCCD0D0 */
		uint32	u4ECMINCFG2_6;						/* 0xFFCCD0D0 - 0xFFCCD0D4 */
		uint32	u4ECMINCFG2_7;						/* 0xFFCCD0D4 - 0xFFCCD0D8 */
		uint32	u4ECMINCFG2_8;						/* 0xFFCCD0D8 - 0xFFCCD0DC */
		uint32	u4ECMINCFG2_9;						/* 0xFFCCD0DC - 0xFFCCD0E0 */
		uint8	u1Dummy5[( 0xFFCCD220U - 0xFFCCD0E0U )];
		uint32	u4ECMIRCFG0;						/* 0xFFCCD220 - 0xFFCCD224 */
		uint32	u4ECMIRCFG1;						/* 0xFFCCD224 - 0xFFCCD228 */
		uint32	u4ECMIRCFG2;						/* 0xFFCCD228 - 0xFFCCD22C */
		uint32	u4ECMIRCFG3;						/* 0xFFCCD22C - 0xFFCCD230 */
		uint32	u4ECMIRCFG4;						/* 0xFFCCD230 - 0xFFCCD234 */
		uint32	u4ECMIRCFG5;						/* 0xFFCCD234 - 0xFFCCD238 */
		uint32	u4ECMIRCFG6;						/* 0xFFCCD238 - 0xFFCCD23C */
		uint32	u4ECMIRCFG7;						/* 0xFFCCD23C - 0xFFCCD240 */
		uint32	u4ECMIRCFG8;						/* 0xFFCCD240 - 0xFFCCD244 */
		uint32	u4ECMIRCFG9;						/* 0xFFCCD244 - 0xFFCCD248 */
		uint8	u1Dummy6[( 0xFFCCD25CU - 0xFFCCD248U )];
		uint32	u4ECMEMK0;							/* 0xFFCCD25C - 0xFFCCD260 */
		uint32	u4ECMEMK1;							/* 0xFFCCD260 - 0xFFCCD264 */
		uint32	u4ECMEMK2;							/* 0xFFCCD264 - 0xFFCCD268 */
		uint32	u4ECMEMK3;							/* 0xFFCCD268 - 0xFFCCD26C */
		uint32	u4ECMEMK4;							/* 0xFFCCD26C - 0xFFCCD270 */
		uint32	u4ECMEMK5;							/* 0xFFCCD270 - 0xFFCCD274 */
		uint32	u4ECMEMK6;							/* 0xFFCCD274 - 0xFFCCD278 */
		uint32	u4ECMEMK7;							/* 0xFFCCD278 - 0xFFCCD27C */
		uint32	u4ECMEMK8;							/* 0xFFCCD27C - 0xFFCCD280 */
		uint32	u4ECMEMK9;							/* 0xFFCCD280 - 0xFFCCD284 */
		uint8	u1Dummy7[( 0xFFCCD478U - 0xFFCCD284U )];
		uint32	u4ECMESSTC0;						/* 0xFFCCD478 - 0xFFCCD47C */
		uint32	u4ECMESSTC1;						/* 0xFFCCD47C - 0xFFCCD480 */
		uint32	u4ECMESSTC2;						/* 0xFFCCD480 - 0xFFCCD484 */
		uint32	u4ECMESSTC3;						/* 0xFFCCD484 - 0xFFCCD488 */
		uint32	u4ECMESSTC4;						/* 0xFFCCD488 - 0xFFCCD48C */
		uint32	u4ECMESSTC5;						/* 0xFFCCD48C - 0xFFCCD490 */
		uint32	u4ECMESSTC6;						/* 0xFFCCD490 - 0xFFCCD494 */
		uint32	u4ECMESSTC7;						/* 0xFFCCD494 - 0xFFCCD498 */
		uint32	u4ECMESSTC8;						/* 0xFFCCD498 - 0xFFCCD49C */
		uint32	u4ECMESSTC9;						/* 0xFFCCD49C - 0xFFCCD4A0 */
		uint8	u1Dummy8[( 0xFFCCD4B4U - 0xFFCCD4A0U )];
		uint32	u4ECMKCPROT;						/* 0xFFCCD4B4 - 0xFFCCD4B8 */
		uint8	u1Dummy9[( 0xFFCCD740U - 0xFFCCD4B8U )];
		uint32	u4ECMPEM;							/* 0xFFCCD740 - 0xFFCCD744 */

#else	/* MCAL_SPAL_TARGET == MCAL_TARGET_RCARS4_G4MH */
		uint8	u1Dummy1[( 0xFFD38004U - 0xFFD38000U )];
		uint32	u4ECMISCFG0;						/* 0xFFD38004 - 0xFFD38008 */
		uint32	u4ECMISCFG1;						/* 0xFFD38008 - 0xFFD3800C */
		uint32	u4ECMISCFG2;						/* 0xFFD3800C - 0xFFD38010 */
		uint32	u4ECMISCFG3;						/* 0xFFD38010 - 0xFFD38014 */
		uint32	u4ECMISCFG4;						/* 0xFFD38014 - 0xFFD38018 */
		uint32	u4ECMISCFG5;						/* 0xFFD38018 - 0xFFD3801C */
		uint32	u4ECMISCFG6;						/* 0xFFD3801C - 0xFFD38020 */
		uint32	u4ECMISCFG7;						/* 0xFFD38020 - 0xFFD38024 */
		uint32	u4ECMISCFG8;						/* 0xFFD38024 - 0xFFD38028 */
		uint32	u4ECMISCFG9;						/* 0xFFD38028 - 0xFFD3802C */
		uint32	u4ECMISCFG10;						/* 0xFFD3802C - 0xFFD38030 */
		uint32	u4ECMISCFG11;						/* 0xFFD38030 - 0xFFD38034 */
		uint8	u1Dummy2[( 0xFFD38040U - 0xFFD38034U )];
		uint32	u4ECMINCFG0_0;						/* 0xFFD38040 - 0xFFD38044 */
		uint32	u4ECMINCFG0_1;						/* 0xFFD38044 - 0xFFD38048 */
		uint32	u4ECMINCFG0_2;						/* 0xFFD38048 - 0xFFD3804C */
		uint32	u4ECMINCFG0_3;						/* 0xFFD3804C - 0xFFD38050 */
		uint32	u4ECMINCFG0_4;						/* 0xFFD38050 - 0xFFD38054 */
		uint32	u4ECMINCFG0_5;						/* 0xFFD38054 - 0xFFD38058 */
		uint32	u4ECMINCFG0_6;						/* 0xFFD38058 - 0xFFD3805C */
		uint32	u4ECMINCFG0_7;						/* 0xFFD3805C - 0xFFD38060 */
		uint32	u4ECMINCFG0_8;						/* 0xFFD38060 - 0xFFD38064 */
		uint32	u4ECMINCFG0_9;						/* 0xFFD38064 - 0xFFD38068 */
		uint32	u4ECMINCFG0_10;						/* 0xFFD38068 - 0xFFD3806C */
		uint32	u4ECMINCFG0_11;						/* 0xFFD3806C - 0xFFD38070 */
		uint8	u1Dummy3[(  0xFFD3807CU - 0xFFD38070U )];
		uint32	u4ECMINCFG1_0;						/* 0xFFD3807C - 0xFFD38080 */
		uint32	u4ECMINCFG1_1;						/* 0xFFD38080 - 0xFFD38084 */
		uint32	u4ECMINCFG1_2;						/* 0xFFD38084 - 0xFFD38088 */
		uint32	u4ECMINCFG1_3;						/* 0xFFD38088 - 0xFFD3808C */
		uint32	u4ECMINCFG1_4;						/* 0xFFD3808C - 0xFFD38090 */
		uint32	u4ECMINCFG1_5;						/* 0xFFD38090 - 0xFFD38094 */
		uint32	u4ECMINCFG1_6;						/* 0xFFD38094 - 0xFFD38098 */
		uint32	u4ECMINCFG1_7;						/* 0xFFD38098 - 0xFFD3809C */
		uint32	u4ECMINCFG1_8;						/* 0xFFD3809C - 0xFFD380A0 */
		uint32	u4ECMINCFG1_9;						/* 0xFFD380A0 - 0xFFD380A4 */
		uint32	u4ECMINCFG1_10;						/* 0xFFD380A4 - 0xFFD380A8 */
		uint32	u4ECMINCFG1_11;						/* 0xFFD380A8 - 0xFFD380AC */
		uint8	u1Dummy4[( 0xFFD38220U - 0xFFD380ACU )];
		uint32	u4ECMIRCFG0;						/* 0xFFD38220 - 0xFFD38224 */
		uint32	u4ECMIRCFG1;						/* 0xFFD38224 - 0xFFD38228 */
		uint32	u4ECMIRCFG2;						/* 0xFFD38228 - 0xFFD3822C */
		uint32	u4ECMIRCFG3;						/* 0xFFD3822C - 0xFFD38230 */
		uint32	u4ECMIRCFG4;						/* 0xFFD38230 - 0xFFD38234 */
		uint32	u4ECMIRCFG5;						/* 0xFFD38234 - 0xFFD38238 */
		uint32	u4ECMIRCFG6;						/* 0xFFD38238 - 0xFFD3823C */
		uint32	u4ECMIRCFG7;						/* 0xFFD3823C - 0xFFD38240 */
		uint32	u4ECMIRCFG8;						/* 0xFFD38240 - 0xFFD38244 */
		uint32	u4ECMIRCFG9;						/* 0xFFD38244 - 0xFFD38248 */
		uint32	u4ECMIRCFG10;						/* 0xFFD38248 - 0xFFD3824C */
		uint32	u4ECMIRCFG11;						/* 0xFFD3824C - 0xFFD38250 */
		uint8	u1Dummy5[( 0xFFD3825CU - 0xFFD38250U )];
		uint32	u4ECMEMK0;							/* 0xFFD3825C - 0xFFD38260 */
		uint32	u4ECMEMK1;							/* 0xFFD38260 - 0xFFD38264 */
		uint32	u4ECMEMK2;							/* 0xFFD38264 - 0xFFD38268 */
		uint32	u4ECMEMK3;							/* 0xFFD38268 - 0xFFD3826C */
		uint32	u4ECMEMK4;							/* 0xFFD3826C - 0xFFD38270 */
		uint32	u4ECMEMK5;							/* 0xFFD38270 - 0xFFD38274 */
		uint32	u4ECMEMK6;							/* 0xFFD38274 - 0xFFD38278 */
		uint32	u4ECMEMK7;							/* 0xFFD38278 - 0xFFD3827C */
		uint32	u4ECMEMK8;							/* 0xFFD3827C - 0xFFD38280 */
		uint32	u4ECMEMK9;							/* 0xFFD38280 - 0xFFD38284 */
		uint32	u4ECMEMK10;							/* 0xFFD38284 - 0xFFD38288 */
		uint32	u4ECMEMK11;							/* 0xFFD38288 - 0xFFD3828C */
		uint8	u1Dummy6[( 0xFFD38478U - 0xFFD3828CU )];
		uint32	u4ECMESSTC0;						/* 0xFFD38478 - 0xFFD3847C */
		uint32	u4ECMESSTC1;						/* 0xFFD3847C - 0xFFD38480 */
		uint32	u4ECMESSTC2;						/* 0xFFD38480 - 0xFFD38484 */
		uint32	u4ECMESSTC3;						/* 0xFFD38484 - 0xFFD38488 */
		uint32	u4ECMESSTC4;						/* 0xFFD38488 - 0xFFD3848C */
		uint32	u4ECMESSTC5;						/* 0xFFD3848C - 0xFFD38490 */
		uint32	u4ECMESSTC6;						/* 0xFFD38490 - 0xFFD38494 */
		uint32	u4ECMESSTC7;						/* 0xFFD38494 - 0xFFD38498 */
		uint32	u4ECMESSTC8;						/* 0xFFD38498 - 0xFFD3849C */
		uint32	u4ECMESSTC9;						/* 0xFFD3849C - 0xFFD384A0 */
		uint32	u4ECMESSTC10;						/* 0xFFD384A0 - 0xFFD384A4 */
		uint32	u4ECMESSTC11;						/* 0xFFD384A4 - 0xFFD384A8 */
		uint8	u1Dummy7[( 0xFFD384B4U - 0xFFD384A8U )];
		uint32	u4ECMKCPROT;						/* 0xFFD384B4 - 0xFFD384B8 */
		uint8	u1Dummy8[( 0xFFD38740U - 0xFFD384B8U )];
		uint32	u4ECMPEM;							/* 0xFFD38740 - 0xFFD38744 */
#endif	/* MCAL_SPAL_TARGET */
	} stECM;
} REGTYPE_ECM;

/*==============================================================================================*/
/*	struct address definition																	*/
/*==============================================================================================*/
#if ( ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) || ( MCAL_SPAL_TARGET == MCAL_TARGET_RCARS4_G4MH ) )
#define		Reg_ECM_ECMMASTER			((volatile REGTYPE_ECM_MASTER *)			0xFFD39000UL)
#define		Reg_ECM_ECMCHECKER			((volatile REGTYPE_ECM_CHECKER *)			0xFFD3A000UL)
#define		Reg_ECM_ECM					((volatile REGTYPE_ECM *)					0xFFD38000UL)
#elif ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
#define		Reg_ECM_ECM					((volatile REGTYPE_ECM *)					0xFFCCD000UL)
#define		Reg_ECM_ECMMASTER			((volatile REGTYPE_ECM_MASTER *)			0xFFCCE000UL)
#define		Reg_ECM_ECMCHECKER			((volatile REGTYPE_ECM_CHECKER *)			0xFFCCF000UL)
#endif

#if ( ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) || ( MCAL_SPAL_TARGET == MCAL_TARGET_RCARS4_G4MH ) )
#define REG_ECM_BASE_ADDR					((uint32)0xFFD38000U)	/* Base address of ECM register	*/
#define REG_ECM_ECMIRCFG7_ADDRESS			((uint32)0xFFD3823CU)	/* ECMIRCFG j:7  Address		*/
#define REG_ECM_ECMIRCFG8_ADDRESS			((uint32)0xFFD38240U)	/* ECMIRCFG j:8  Address		*/
#define REG_ECM_ECMIRCFG9_ADDRESS			((uint32)0xFFD38244U)	/* ECMIRCFG j:9  Address		*/
#define REG_ECM_ECMIRCFG10_ADDRESS			((uint32)0xFFD38248U)	/* ECMIRCFG j:10 Address		*/
#elif MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B
#define REG_ECM_BASE_ADDR					((uint32)0xFFCCD000U)	/* Base address of ECM register	*/
#define REG_ECM_ECMIRCFG7_ADDRESS			((uint32)0xFFCCD23CU)	/* ECMIRCFG j:7  Address		*/
#define REG_ECM_ECMIRCFG8_ADDRESS			((uint32)0xFFCCD240U)	/* ECMIRCFG j:8  Address		*/
#define REG_ECM_ECMIRCFG9_ADDRESS			((uint32)0xFFCCD244U)	/* ECMIRCFG j:9  Address		*/
#define REG_ECM_ECMIRCFG10_ADDRESS			((uint32)0xFFCCD248U)	/* ECMIRCFG j:10 Address		*/
#endif
#define REG_ECM_ECMKCPROT_OFFSET			((uint32)0x000004B4U)	/* ECMKCPROT register offset	*/
#define REG_ECM_ECMPEM_OFFSET				((uint32)0x00000740U)	/* ECMPEM register offset		*/
#define REG_ECM_ECMKCPROT_ADDR				((volatile uint32 *)(REG_ECM_BASE_ADDR + REG_ECM_ECMKCPROT_OFFSET))		/* Address of ECMKCPROT register */
#define REG_ECM_ECMPEM_ADDR					((volatile uint32 *)(REG_ECM_BASE_ADDR + REG_ECM_ECMPEM_OFFSET))		/* Address of ECMPEM register */

/*----------------------------------------------------------------------------------------------*/
/*	register setting definition																	*/
/*----------------------------------------------------------------------------------------------*/
#define REG_ECM_CLR_ERROR_TRG				((uint32)0x00000001U)	/* Value for error trigger clearing				*/
#define REG_ECM_ECMPEM_MASKED				((uint32)0x00000003U)	/* ECM ECMPEM mask value						*/
#define REG_ECM_ECMPEM_UNMASKED				((uint32)0x00000000U)	/* ECM ERRORIN0 mask value						*/
#define REG_ECM_ECMIRE_4_MASKED				((uint32)0x00000010U)	/* ECM internal reset generation control bit	*/
#define REG_ECM_ECMIRE_4_ENABLE				((uint32)0x00000010U)	/* ECM internal reset generation enabled		*/

#define ECM_PROTECT_KEY_ENABLE				((uint32)0xA5A5A501U)	/* Enable write access to protected registers	*/
#define ECM_PROTECT_KEY_DISABLE				((uint32)0xA5A5A500U)	/* Disable write access to protected registers	*/

#define ECM_ERRROR_TRIGGER_0				((uint8)0x00U)			/* Error Trigger 0								*/
#define ECM_ERRROR_TRIGGER_1				((uint8)0x01U)			/* Error Trigger 1								*/
#define ECM_ERRROR_TRIGGER_2				((uint8)0x02U)			/* Error Trigger 2								*/
#define ECM_ERRROR_TRIGGER_3				((uint8)0x03U)			/* Error Trigger 3								*/

/*------------------------------------------------------------------*/
/*	ECMmECLR														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	ECM_ECMmECLR_ECMmECT				( BIT0 )
/* Bit setting value definition */
#define	ECM_ECMmECLR_ECMmECT_INVALID		(0U)
#define	ECM_ECMmECLR_ECMmECT_INACTIVE		(1U)

/*------------------------------------------------------------------*/
/*	ECMmESSTRj														*/
/*------------------------------------------------------------------*/
/* Bit setting value definition */
#define	ECM_ECMmESSTRj_ECMmSSEj_NOTOCCURRED		(0U)
#define	ECM_ECMmESSTRj_ECMmSSEj_OCCURRED		(1U)

/*------------------------------------------------------------------*/
/*	ECMmECLR														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	ECM_ECMEMKj_ECMEMK20_31				( BIT31 + BIT30 + BIT29 + BIT28 + BIT27 + BIT26 + BIT25 + BIT24 + BIT23 + BIT22 + BIT21 + BIT20 )
#define	ECM_ECMEMKj_ECMEMK0_11				( BIT11 )
/* Bit setting value definition */
#define	ECM_ECMEMKj_ECMEMK_NOTMASK			(0U)
#define	ECM_ECMEMKj_ECMEMK_MASK				(1U)

/*------------------------------------------------------------------*/
/*	ECMPEM															*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	ECM_ECMPEM_MSKM					( BIT1 )
#define	ECM_ECMPEM_MSKC					( BIT0 )
/* Bit setting value definition */
#define	ECM_ECMPEM_MSKM_NOTMASK			(0U)
#define	ECM_ECMPEM_MSKM_MASK			(1U)
#define	ECM_ECMPEM_MSKC_NOTMASK			(0U)
#define	ECM_ECMPEM_MSKC_MASK			(1U)

#define	ECM_ERROR48_BITPOS				( (uint32)0x00010000U )	/* Bit postion for ECM error number 48 */
#define	ECM_ERROR49_BITPOS				( (uint32)0x00020000U )	/* Bit postion for ECM error number 49 */
#define	ECM_ERROR50_BITPOS				( (uint32)0x00040000U )	/* Bit postion for ECM error number 50 */
#define	ECM_ERROR51_BITPOS				( (uint32)0x00080000U )	/* Bit postion for ECM error number 51 */
#define	ECM_ERROR52_BITPOS				( (uint32)0x00100000U )	/* Bit postion for ECM error number 52 */
#define	ECM_ERROR229_BITPOS				( (uint32)0x00000020U )	/* Bit postion for ECM error number 229 */
#define	ECM_ERROR261_BITPOS				( (uint32)0x00000020U )	/* Bit postion for ECM error number 261 */
#define	ECM_ERROR293_BITPOS				( (uint32)0x00000020U )	/* Bit postion for ECM error number 293 */
#define	ECM_ERROR325_BITPOS				( (uint32)0x00000020U )	/* Bit postion for ECM error number 325 */
#define	ECM_ERROR71_BITPOS				( (uint32)0x00000080U )	/* Bit postion for ECM error number 71 */
#define	ECM_ERROR72_BITPOS				( (uint32)0x00000100U )	/* Bit postion for ECM error number 72 */
#define	ECM_ERROR73_BITPOS				( (uint32)0x00000200U )	/* Bit postion for ECM error number 73 */
#define	ECM_ERROR74_BITPOS				( (uint32)0x00000400U )	/* Bit postion for ECM error number 74 */
#define	ECM_ERROR75_BITPOS				( (uint32)0x00000800U )	/* Bit postion for ECM error number 75 */
#define	ECM_ERROR76_BITPOS				( (uint32)0x00001000U )	/* Bit postion for ECM error number 76 */
#define	ECM_ERROR77_BITPOS				( (uint32)0x00002000U )	/* Bit postion for ECM error number 77 */
#define	ECM_ERROR78_BITPOS				( (uint32)0x00004000U )	/* Bit postion for ECM error number 78 */

#endif /* PORT_REG_ECM */
/*-- End Of File -------------------------------------------------------------------------------*/
