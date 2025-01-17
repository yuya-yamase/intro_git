/* Reg_CLMA-r04-30700-0000-a-v01 */
/************************************************************************************************/
/*																								*/
/*		Clock Monitor register definition (for RH850U2A and RH850U2B and RCARS4 G4MH)			*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

#ifndef	REG_CLMA_H
#define	REG_CLMA_H

/*==============================================================================================*/
/* include files																				*/
/*==============================================================================================*/
#include	"Std_Types.h"
#include	"Mcal_SpalCmn.h"

/*==============================================================================================*/
/*	register type definition																	*/
/*==============================================================================================*/
/*------------------------------------------------------------------------------*/
/* Clock Monitor Registers for CLMAC											*/
/*------------------------------------------------------------------------------*/
typedef	struct {
	uint32	u4CLMATEST;
	uint32	u4CLMATESTS;
#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
	uint8	u1CLMABCE;
#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B ) */
} Reg_Clmac_Type;

/*------------------------------------------------------------------------------*/
/* Clock Monitor Registers for CLMA0											*/
/*------------------------------------------------------------------------------*/
typedef	struct {
	uint8	u1CLMA0CTL;
	uint8	u1Dummy1[7];
	uint16	u2CLMA0CMPL;
	uint8	u1Dummy2[2];
	uint16	u2CLMA0CMPH;
} Reg_Clma0_Type;

/*------------------------------------------------------------------------------*/
/* Clock Monitor Registers for CLMA1											*/
/*------------------------------------------------------------------------------*/
typedef	struct {
	uint8	u1CLMA1CTL;
	uint8	u1Dummy1[7];
	uint16	u2CLMA1CMPL;
	uint8	u1Dummy2[2];
	uint16	u2CLMA1CMPH;
} Reg_Clma1_Type;

/*------------------------------------------------------------------------------*/
/* Clock Monitor Registers for CLMA2											*/
/*------------------------------------------------------------------------------*/
typedef	struct {
	uint8	u1CLMA2CTL;
	uint8	u1Dummy1[7];
	uint16	u2CLMA2CMPL;
	uint8	u1Dummy2[2];
	uint16	u2CLMA2CMPH;
} Reg_Clma2_Type;

/*------------------------------------------------------------------------------*/
/* Clock Monitor Registers for CLMA3											*/
/*------------------------------------------------------------------------------*/
typedef	struct {
	uint8	u1CLMA3CTL;
	uint8	u1Dummy1[7];
	uint16	u2CLMA3CMPL;
	uint8	u1Dummy2[2];
	uint16	u2CLMA3CMPH;
#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
	uint8	u1Dummy3[2];
	uint8	u1CLMA3STPDTEN;
#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B ) */
} Reg_Clma3_Type;

/*------------------------------------------------------------------------------*/
/* Clock Monitor Registers for CLMA4											*/
/*------------------------------------------------------------------------------*/
typedef	struct {
	uint8	u1CLMA4CTL;
	uint8	u1Dummy1[7];
	uint16	u2CLMA4CMPL;
	uint8	u1Dummy2[2];
	uint16	u2CLMA4CMPH;
#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
	uint8	u1Dummy3[2];
	uint8	u1CLMA4STPDTEN;
#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B ) */
} Reg_Clma4_Type;

/*------------------------------------------------------------------------------*/
/* Clock Monitor Registers for CLMA5											*/
/*------------------------------------------------------------------------------*/
typedef	struct {
#if	( ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) || ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B ) )
	uint8	u1CLMA5CTL;
	uint8	u1Dummy1[7];
	uint16	u2CLMA5CMPL;
	uint8	u1Dummy2[2];
	uint16	u2CLMA5CMPH;
#endif	/* ( ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) || ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B ) ) */
} Reg_Clma5_Type;

/*------------------------------------------------------------------------------*/
/* Clock Monitor Registers for CLMA6											*/
/*------------------------------------------------------------------------------*/
typedef	struct {
	uint8	u1CLMA6CTL;
	uint8	u1Dummy1[7];
	uint16	u2CLMA6CMPL;
	uint8	u1Dummy2[2];
	uint16	u2CLMA6CMPH;
#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
	uint8	u1Dummy3[2];
	uint8	u1CLMA6STPDTEN;
#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B ) */
} Reg_Clma6_Type;

/*------------------------------------------------------------------------------*/
/* Clock Monitor Registers for CLMA7											*/
/*------------------------------------------------------------------------------*/
typedef	struct {
	uint8	u1CLMA7CTL;
	uint8	u1Dummy1[7];
	uint16	u2CLMA7CMPL;
	uint8	u1Dummy2[2];
	uint16	u2CLMA7CMPH;
#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
	uint8	u1Dummy3[2];
	uint8	u1CLMA7STPDTEN;
#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B ) */
} Reg_Clma7_Type;

/*------------------------------------------------------------------------------*/
/* Clock Monitor Registers for CLMA8											*/
/*------------------------------------------------------------------------------*/
typedef	struct {
#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
#if	( ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A16_516PIN ) || ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A16_373PIN ) )
	uint8	u1CLMA8CTL;
	uint8	u1Dummy1[7];
	uint16	u2CLMA8CMPL;
	uint8	u1Dummy2[2];
	uint16	u2CLMA8CMPH;
#endif	/* ( ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A16_516PIN ) || ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A16_373PIN ) ) */

#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) */
} Reg_Clma8_Type;

/*------------------------------------------------------------------------------*/
/* Clock Monitor Registers for CLMA9											*/
/*------------------------------------------------------------------------------*/
typedef	struct {
#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
#if	( ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A16_516PIN ) || ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A16_373PIN ) )
	uint8	u1CLMA9CTL;
	uint8	u1Dummy1[7];
	uint16	u2CLMA9CMPL;
	uint8	u1Dummy2[2];
	uint16	u2CLMA9CMPH;
#endif	/* ( ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A16_516PIN ) || ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A16_373PIN ) ) */

#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) */
} Reg_Clma9_Type;

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
/*------------------------------------------------------------------------------*/
/* Clock Monitor Registers for CLMA10											*/
/*------------------------------------------------------------------------------*/
typedef	struct {
	uint8	u1CLMA10CTL;
	uint8	u1Dummy1[7];
	uint16	u2CLMA10CMPL;
	uint8	u1Dummy2[2];
	uint16	u2CLMA10CMPH;
	uint8	u1Dummy3[2];
	uint8	u1CLMA10STPDTEN;
} Reg_Clma10_Type;

/*------------------------------------------------------------------------------*/
/* Clock Monitor Registers for CLMA12											*/
/*------------------------------------------------------------------------------*/
typedef	struct {
	uint8	u1CLMA12CTL;
	uint8	u1Dummy1[7];
	uint16	u2CLMA12CMPL;
	uint8	u1Dummy2[2];
	uint16	u2CLMA12CMPH;
	uint8	u1Dummy3[2];
	uint8	u1CLMA12STPDTEN;
} Reg_Clma12_Type;

/*------------------------------------------------------------------------------*/
/* Clock Monitor Registers for CLMA13											*/
/*------------------------------------------------------------------------------*/
typedef	struct {
	uint8	u1CLMA13CTL;
	uint8	u1Dummy1[7];
	uint16	u2CLMA13CMPL;
	uint8	u1Dummy2[2];
	uint16	u2CLMA13CMPH;
	uint8	u1Dummy3[2];
	uint8	u1CLMA13STPDTEN;
} Reg_Clma13_Type;

/*------------------------------------------------------------------------------*/
/* Clock Monitor Registers for CLMA14											*/
/*------------------------------------------------------------------------------*/
typedef	struct {
	uint8	u1CLMA14CTL;
	uint8	u1Dummy1[7];
	uint16	u2CLMA14CMPL;
	uint8	u1Dummy2[2];
	uint16	u2CLMA14CMPH;
} Reg_Clma14_Type;

/*------------------------------------------------------------------------------*/
/* Clock Monitor Registers for CLMA15											*/
/*------------------------------------------------------------------------------*/
typedef	struct {
	uint8	u1CLMA15CTL;
	uint8	u1Dummy1[7];
	uint16	u2CLMA15CMPL;
	uint8	u1Dummy2[2];
	uint16	u2CLMA15CMPH;
} Reg_Clma15_Type;

/*------------------------------------------------------------------------------*/
/* Clock Monitor Registers for CLMA16											*/
/*------------------------------------------------------------------------------*/
typedef	struct {
	uint8	u1CLMA16CTL;
	uint8	u1Dummy1[7];
	uint16	u2CLMA16CMPL;
	uint8	u1Dummy2[2];
	uint16	u2CLMA16CMPH;
	uint8	u1Dummy3[2];
	uint8	u1CLMA16STPDTEN;
} Reg_Clma16_Type;

/*------------------------------------------------------------------------------*/
/* Clock Monitor Registers for CLMA17											*/
/*------------------------------------------------------------------------------*/
typedef	struct {
	uint8	u1CLMA17CTL;
	uint8	u1Dummy1[7];
	uint16	u2CLMA17CMPL;
	uint8	u1Dummy2[2];
	uint16	u2CLMA17CMPH;
} Reg_Clma17_Type;
#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B ) */

/*------------------------------------------------------------------------------*/
/* Clock Monitor Register Key Code Protection Register							*/
/*------------------------------------------------------------------------------*/
typedef	struct
{
	uint32	u4CLMAKCPROT;
} Reg_Clmakcprot_Type;

/*==============================================================================================*/
/*	register BIT definition																		*/
/*==============================================================================================*/
/*------------------------------------------------------------------*/
/*	CLMATEST														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLMA_CLMATEST_CLMA17TESEN			( BIT20 )
#define	CLMA_CLMATEST_CLMA16TESEN			( BIT19 )
#define	CLMA_CLMATEST_CLMA15TESEN			( BIT18 )
#define	CLMA_CLMATEST_CLMA14TESEN			( BIT17 )
#define	CLMA_CLMATEST_CLMA13TESEN			( BIT16 )
#define	CLMA_CLMATEST_CLMA12TESEN			( BIT15 )
#define	CLMA_CLMATEST_CLMA10TESEN			( BIT13 )
#define	CLMA_CLMATEST_CLMA9TESEN			( BIT12 )
#define	CLMA_CLMATEST_CLMA8TESEN			( BIT11 )
#define	CLMA_CLMATEST_CLMA7TESEN			( BIT10 )
#define	CLMA_CLMATEST_CLMA6TESEN			( BIT9 )
#define	CLMA_CLMATEST_CLMA5TESEN			( BIT8 )
#define	CLMA_CLMATEST_CLMA4TESEN			( BIT7 )
#define	CLMA_CLMATEST_CLMA3TESEN			( BIT6 )
#define	CLMA_CLMATEST_CLMA2TESEN			( BIT5 )
#define	CLMA_CLMATEST_CLMA1TESEN			( BIT4 )
#define	CLMA_CLMATEST_CLMA0TESEN			( BIT3 )
#define	CLMA_CLMATEST_ERRMSK				( BIT2 )
#define	CLMA_CLMATEST_MONCLKMSK				( BIT1 )
#define	CLMA_CLMATEST_RESCLM				( BIT0 )
/* Bit setting value definition */
#define	CLMA_CLMATEST_CLMAnTESEN_DISABLE	(0U)
#define	CLMA_CLMATEST_CLMAnTESEN_ENABLE		(1U)
#define	CLMA_CLMATEST_ERRMSK_ENABLE			(0U)
#define	CLMA_CLMATEST_ERRMSK_DISABLE		(1U)
#define	CLMA_CLMATEST_MONCLKMSK_ENABLE		(0U)
#define	CLMA_CLMATEST_MONCLKMSK_DISABLE		(1U)
#define	CLMA_CLMATEST_RESCLM_RELEASE		(0U)
#define	CLMA_CLMATEST_RESCLM_ASSERT			(1U)

/*------------------------------------------------------------------*/
/*	CLMATESTS														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLMA_CLMATESTS_CLMA17ERRS			( BIT17 )
#define	CLMA_CLMATESTS_CLMA16ERRS			( BIT16 )
#define	CLMA_CLMATESTS_CLMA15ERRS			( BIT15 )
#define	CLMA_CLMATESTS_CLMA14ERRS			( BIT14 )
#define	CLMA_CLMATESTS_CLMA13ERRS			( BIT13 )
#define	CLMA_CLMATESTS_CLMA12ERRS			( BIT12 )
#define	CLMA_CLMATESTS_CLMA10ERRS			( BIT10 )
#define	CLMA_CLMATESTS_CLMA9ERRS			( BIT9 )
#define	CLMA_CLMATESTS_CLMA8ERRS			( BIT8 )
#define	CLMA_CLMATESTS_CLMA7ERRS			( BIT7 )
#define	CLMA_CLMATESTS_CLMA6ERRS			( BIT6 )
#define	CLMA_CLMATESTS_CLMA5ERRS			( BIT5 )
#define	CLMA_CLMATESTS_CLMA4ERRS			( BIT4 )
#define	CLMA_CLMATESTS_CLMA3ERRS			( BIT3 )
#define	CLMA_CLMATESTS_CLMA2ERRS			( BIT2 )
#define	CLMA_CLMATESTS_CLMA1ERRS			( BIT1 )
#define	CLMA_CLMATESTS_CLMA0ERRS			( BIT0 )
/* Bit setting value definition */
#define	CLMA_CLMATESTS_CLMAnERRS_NOERROR	(0U)
#define	CLMA_CLMATESTS_CLMAnERRS_ERROR		(1U)

/*------------------------------------------------------------------*/
/*	CLMABCE															*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLMA_CLMABCE_CLMABCE				( BIT0 )
/* Bit setting value definition */
#define	CLMA_CLMABCE_CLMABCE_DISABLE		(0U)
#define	CLMA_CLMABCE_CLMABCE_ENABLE			(1U)

/*------------------------------------------------------------------*/
/*	CLMAnCTL														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLMA_CLMAnCTL_CLMAnCLME				( BIT0 )
/* Bit setting value definition */
#define	CLMA_CLMAnCTL_CLMAnCLME_DISABLE		(0U)
#define	CLMA_CLMAnCTL_CLMAnCLME_ENABLE		(1U)

/*------------------------------------------------------------------*/
/*	CLMAnCMPL														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLMA_CLMAnCMPL_CLMAnCMPL			( BIT11 + BIT10 + BIT9 + BIT8 + BIT7 + BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0 )

/*------------------------------------------------------------------*/
/*	CLMAnCMPH														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLMA_CLMAnCMPH_CLMAnCMPH			( BIT11 + BIT10 + BIT9 + BIT8 + BIT7 + BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0 )

/*------------------------------------------------------------------*/
/*	CLMAnSTPDTEN													*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLMA_CLMAnSTPDTEN_CLMAnSTPDTEN		( BIT0 )
/* Bit setting value definition */
#define	CLMA_CLMAnSTPDTEN_DISABLE			(0U)
#define	CLMA_CLMAnSTPDTEN_ENABLE			(1U)

/*------------------------------------------------------------------*/
/*	CLMAKCPROT														*/
/*------------------------------------------------------------------*/
/* Bit definition */
#define	CLMA_CLMAKCPROT_KCE					( BIT0 )
#define	CLMA_CLMAKCPROT_KCPROT				( BIT31 + BIT30 + BIT29 + BIT28 + BIT27 + BIT26 + BIT25 + BIT24 + BIT23 + BIT22			\
											+ BIT21 + BIT20 + BIT19 + BIT18 + BIT17 + BIT16 + BIT15 + BIT14 + BIT13 + BIT12			\
											+ BIT11 + BIT10 + BIT9 + BIT8 + BIT7 + BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0 )
/* Bit setting value definition */
#define	CLMA_CLMAKCPROT_DISABLE				( (uint32)0xA5A5A500U )
#define	CLMA_CLMAKCPROT_ENABLE				( (uint32)0xA5A5A501U )

/*==============================================================================================*/
/*	struct address definition																	*/
/*==============================================================================================*/
#define	REG_CLMAC	(*(volatile Reg_Clmac_Type *)(0xFF989000U))
#define	REG_CLMA0	(*(volatile Reg_Clma0_Type *)(0xFF989100U))
#define	REG_CLMA1	(*(volatile Reg_Clma1_Type *)(0xFF989200U))
#define	REG_CLMA2	(*(volatile Reg_Clma2_Type *)(0xFF989300U))
#define	REG_CLMA3	(*(volatile Reg_Clma3_Type *)(0xFF981800U))
#define	REG_CLMA4	(*(volatile Reg_Clma4_Type *)(0xFF981900U))

#if	( ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) || ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B ) )
#define	REG_CLMA5	(*(volatile Reg_Clma5_Type *)(0xFF981A00U))
#endif	/* ( ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) || ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B ) ) */

#define	REG_CLMA6	(*(volatile Reg_Clma6_Type *)(0xFF981B00U))
#define	REG_CLMA7	(*(volatile Reg_Clma7_Type *)(0xFF981C00U))

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
#if	( ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A16_516PIN ) || ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A16_373PIN ) )
#define	REG_CLMA8	(*(volatile Reg_Clma8_Type *)(0xFF981D00U))
#define	REG_CLMA9	(*(volatile Reg_Clma9_Type *)(0xFF981E00U))
#endif	/* ( ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A16_516PIN ) || ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A16_373PIN ) ) */
#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) */

#if	( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
#define	REG_CLMA10	(*(volatile Reg_Clma10_Type *)(0xFF981F00U))
#define	REG_CLMA12	(*(volatile Reg_Clma12_Type *)(0xFF982100U))
#define	REG_CLMA13	(*(volatile Reg_Clma13_Type *)(0xFF982200U))
#define	REG_CLMA14	(*(volatile Reg_Clma14_Type *)(0xFF982300U))
#define	REG_CLMA15	(*(volatile Reg_Clma15_Type *)(0xFF982400U))
#define	REG_CLMA16	(*(volatile Reg_Clma16_Type *)(0xFF982500U))
#define	REG_CLMA17	(*(volatile Reg_Clma17_Type *)(0xFF982600U))
#endif	/* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B ) */

#define	REG_CLMAKCPROT	(*(volatile Reg_Clmakcprot_Type *)(0xFF982700U))

/*----------------------------------------------------------------------------------------------*/
/*	register setting definition																	*/
/*----------------------------------------------------------------------------------------------*/

#endif	/* REG_CLMA_H */
/*-- End Of File -------------------------------------------------------------------------------*/
