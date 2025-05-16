/* reg_bist-r04-3000-0000-a-v02 */
/************************************************************************************************/
/*																								*/
/*		BIST register definition (for RH850U2A)													*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

#ifndef REG_BIST_H
#define REG_BIST_H


/*==============================================================================================*/
/*	register type definition																	*/
/*==============================================================================================*/

/* BIST */
/* ============================================================================ */
/* ============================ Module: BIST ================================== */
/* ============================================================================ */
typedef	struct											/* BIST */
{
	union												/* BSEQ0ST */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xCMPERR					:1;				/* CMPERR */
			U4	xBISTEND				:1;				/* BISTEND */
			U4	b30Dummy1				:30;
		} stBit;
	} unBSEQ0ST;										/* 0xFF9A4400 - 0xFF9A4403 */

	union												/* BSEQ0STB */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xCMPERRB				:1;				/* CMPERRB */
			U4	xBISTENDB				:1;				/* BISTENDB */
			U4	b30Dummy1				:30;
		} stBit;
	} unBSEQ0STB;										/* 0xFF9A4404 - 0xFF9A4407 */

	union												/* BISTST */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xLBIST1ST				:1;				/* LBIST1ST */
			U4	xLBIST2ST				:1;				/* LBIST2ST */
			U4	xMBIST1ST				:1;				/* MBIST1ST */
			U4	xMBIST2ST				:1;				/* MBIST2ST */
			U4	xMBIST3ST				:1;				/* MBIST3ST */
			U4	b27Dummy1				:27;
		} stBit;
	} unBISTST;											/* 0xFF9A4408 - 0xFF9A440B */

	union												/* BSEQ0SEL */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b4HWLBISTSEL			:4;				/* HWLBISTSEL */
			U4	b2HWTESTSET				:2;				/* HWTESTSET */
			U4	b9Dummy2				:9;
			U4	xPARAMSEL				:1;				/* PARAMSEL */
			U4	b16Dummy3				:16;
		} stBit;
	} unBSEQ0SEL;										/* 0xFF9A440C - 0xFF9A440F */

	U1	u1Dummy1[0xFF9A6000U - 0xFF9A4410];				/* 0xFF9A4410 - 0xFF9A5FFF */

	union												/* LBISTREF1 */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b20LBISTREF1			:20;			/* LBISTREF1 */
			U4	b12Dummy1				:12;
		} stBit;
	} unLBISTREF1;										/* 0xFF9A6000 - 0xFF9A6004 */

	union												/* LBISTREF2 */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b20LBISTREF2			:20;			/* LBISTREF2 */
			U4	b12Dummy1				:12;
		} stBit;
	} unLBISTREF2;										/* 0xFF9A6004 - 0xFF9A6008 */

	union												/* MBISTREF1 */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b20MBISTREF1			:20;			/* MBISTREF1 */
			U4	b12Dummy1				:12;
		} stBit;
	} unMBISTREF1;										/* 0xFF9A6008 - 0xFF9A600C */

	union												/* MBISTREF1 */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b20MBISTREF2			:20;			/* MBISTREF2 */
			U4	b12Dummy1				:12;
		} stBit;
	} unMBISTREF2;										/* 0xFF9A600C - 0xFF9A6010 */

	union												/* MBISTREF3 */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b20MBISTREF3			:20;			/* MBISTREF3 */
			U4	b12Dummy1				:12;
		} stBit;
	} unMBISTREF3;										/* 0xFF9A6010 - 0xFF9A6014 */

	union												/* LBISTSIG1 */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b20LBISTSIG1			:20;			/* LBISTSIG1 */
			U4	b12Dummy1				:12;
		} stBit;
	} unLBISTSIG1;										/* 0xFF9A6014 - 0xFF9A6018 */

	union												/* LBISTSIG2 */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b20LBISTSIG2			:20;			/* LBISTSIG2 */
			U4	b12Dummy1				:12;
		} stBit;
	} unLBISTSIG2;										/* 0xFF9A6018 - 0xFF9A601C */

	union												/* MBISTSIG1 */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b20MBISTSIG1			:20;			/* MBISTSIG1 */
			U4	b12Dummy1				:12;
		} stBit;
	} unMBISTSIG1;										/* 0xFF9A601C - 0xFF9A6020 */

	union												/* MBISTSIG2 */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b20MBISTSIG2			:20;			/* MBISTSIG2 */
			U4	b12Dummy1				:12;
		} stBit;
	} unMBISTSIG2;										/* 0xFF9A6020 - 0xFF9A6024 */

	union												/* MBISTSIG3 */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b20MBISTSIG3			:20;			/* MBISTSIG3 */
			U4	b12Dummy1				:12;
		} stBit;
	} unMBISTSIG3;										/* 0xFF9A6024 - 0xFF9A6028 */

	U4	u4MBIST1FTAG0;									/* MBIST1FTAG0  0xFF9A6028 */

	U4	u4MBIST1FTAG1;									/* MBIST1FTAG1  0xFF9A602C */

	U4	u4MBIST1FTAG2;									/* MBIST1FTAG2  0xFF9A6030 */

	U4	u4MBIST1FTAG3;									/* MBIST1FTAG3  0xFF9A6034 */

	U4	u4MBIST1FTAG4;									/* MBIST1FTAG4  0xFF9A6038 */

	U4	u4MBIST1FTAG5;									/* MBIST1FTAG5  0xFF9A603C */

	U4	u4MBIST1FTAG6;									/* MBIST1FTAG6  0xFF9A6040 */

	U4	u4MBIST1FTAG7;									/* MBIST1FTAG7  0xFF9A6044 */

	U4	u4MBIST2FTAG0;									/* MBIST2FTAG0  0xFF9A6048 */

	U4	u4MBIST2FTAG1;									/* MBIST2FTAG1  0xFF9A604C */

	U4	u4MBIST2FTAG2;									/* MBIST2FTAG2  0xFF9A6050 */

	U1	u1Dummy2[0xFF9A6068U - 0xFF9A6054U];			/* 0xFF9A6054 - 0xFF9A6068 */

	U4	u4MBIST3FTAG0;									/* MBIST3FTAG0  0xFF9A6068 */

	U1	u1Dummy3[0xFF9A6088U - 0xFF9A606CU];			/* 0xFF9A606C - 0xFF9A6088 */

	U4	u4MBIST1ECC0;									/* MBIST1ECC0  0xFF9A6088 */

	U4	u4MBIST1ECC1;									/* MBIST1ECC1  0xFF9A608C */

	U4	u4MBIST1ECC2;									/* MBIST1ECC2  0xFF9A6090 */

	U4	u4MBIST1ECC3;									/* MBIST1ECC3  0xFF9A6094 */

	U4	u4MBIST1ECC4;									/* MBIST1ECC4  0xFF9A6098 */

	U4	u4MBIST1ECC5;									/* MBIST1ECC5  0xFF9A609C */

	U4	u4MBIST1ECC6;									/* MBIST1ECC6  0xFF9A60A0 */

	U4	u4MBIST1ECC7;									/* MBIST1ECC7  0xFF9A60A4 */

	U4	u4MBIST2ECC0;									/* MBIST2ECC0  0xFF9A60A8 */

	U4	u4MBIST2ECC1;									/* MBIST2ECC1  0xFF9A60AC */

	U4	u4MBIST2ECC2;									/* MBIST2ECC2  0xFF9A60B0 */

	U1	u1Dummy4[0xFF9A60C8U - 0xFF9A60B4U];			/* 0xFF9A60A8 - 0xFF9A60E0 */

	U4	u4MBIST3ECC0;									/* MBIST3ECC0  0xFF9A60C8 */
}	Reg_Bist_BistType;

/* SYSCTRL */
/* ============================================================================ */
/* ============================ Module: SYSCTRL =============================== */
/* ============================================================================ */
typedef	struct											/* SYSCTRL */
{
	union												/* BSEQ0CTL */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xHWBISTEXE				:1;				/* HWBISTEXE */
			U4	xHWBISTSEL				:1;				/* HWBISTSEL */
			U4	b30Dummy1				:30;
		} stBit;
	} unBSEQ0CTL;										/* 0xFF988400 - 0xFF988404 */

	union												/* BSEQ1CTL */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xHWBISTEXE				:1;				/* HWBISTEXE */
			U4	b31Dummy1				:31;
		} stBit;
	} unBSEQ1CTL;										/* 0xFF988404 - 0xFF988408 */

	union												/* BSEQ2CTL */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xHWBISTEXE				:1;				/* HWBISTEXE */
			U4	b31Dummy1				:31;
		} stBit;
	} unBSEQ2CTL;										/* 0xFF988408 - 0xFF98840C */

}	Reg_Bist_SysctrlType;


/*======================================================================*/
/*	register BIT definition												*/
/*======================================================================*/
/* BIST */
/* Module: BIST */
/* LBISTREF1 */
#define		BIST_LBISTREF1_LBISTREF1						(0x000FFFFFU)
/* LBISTREF2 */
#define		BIST_LBISTREF2_LBISTREF2						(0x000FFFFFU)
/* MBISTREF1 */
#define		BIST_MBISTREF1_MBISTREF1						(0x000FFFFFU)
/* MBISTREF2 */
#define		BIST_MBISTREF2_MBISTREF2						(0x000FFFFFU)
/* MBISTREF3 */
#define		BIST_MBISTREF3_MBISTREF3						(0x000FFFFFU)
/* MBISTREF4 */
#define		BIST_MBISTREF4_MBISTREF4						(0x000FFFFFU)
/* MBISTREF5 */
#define		BIST_MBISTREF5_MBISTREF5						(0x000FFFFFU)
/* MBISTREF6 */
#define		BIST_MBISTREF6_MBISTREF6						(0x000FFFFFU)
/* MBISTREF7 */
#define		BIST_MBISTREF7_MBISTREF7						(0x000FFFFFU)
/* MBISTREF8 */
#define		BIST_MBISTREF8_MBISTREF8						(0x000FFFFFU)
/* LBISTSIG1 */
#define		BIST_LBISTSIG1_LBISTSIG1						(0x000FFFFFU)
/* LBISTSIG2 */
#define		BIST_LBISTSIG2_LBISTSIG2						(0x000FFFFFU)
/* MBISTSIG1 */
#define		BIST_MBISTSIG1_MBISTSIG1						(0x000FFFFFU)
/* MBISTSIG2 */
#define		BIST_MBISTSIG2_MBISTSIG2						(0x000FFFFFU)
/* MBISTSIG3 */
#define		BIST_MBISTSIG3_MBISTSIG3						(0x000FFFFFU)
/* MBISTSIG4 */
#define		BIST_MBISTSIG4_MBISTSIG4						(0x000FFFFFU)
/* MBISTSIG5 */
#define		BIST_MBISTSIG5_MBISTSIG5						(0x000FFFFFU)
/* MBISTSIG6 */
#define		BIST_MBISTSIG6_MBISTSIG6						(0x000FFFFFU)
/* MBISTSIG7 */
#define		BIST_MBISTSIG7_MBISTSIG7						(0x000FFFFFU)
/* MBISTSIG8 */
#define		BIST_MBISTSIG8_MBISTSIG8						(0x000FFFFFU)
/* MBIST1FTAG0 */
#define		BIST_MBIST1FTAG0_MBIST1FTAG0					(0xFFFFFFFFU)
/* MBIST1FTAG1 */
#define		BIST_MBIST1FTAG1_MBIST1FTAG1					(0xFFFFFFFFU)
/* MBIST1FTAG2 */
#define		BIST_MBIST1FTAG2_MBIST1FTAG2					(0xFFFFFFFFU)
/* MBIST1FTAG3 */
#define		BIST_MBIST1FTAG3_MBIST1FTAG3					(0xFFFFFFFFU)
/* MBIST1FTAG4 */
#define		BIST_MBIST1FTAG4_MBIST1FTAG4					(0xFFFFFFFFU)
/* MBIST1FTAG5 */
#define		BIST_MBIST1FTAG5_MBIST1FTAG5					(0xFFFFFFFFU)
/* MBIST1FTAG6 */
#define		BIST_MBIST1FTAG6_MBIST1FTAG6					(0xFFFFFFFFU)
/* MBIST1FTAG7 */
#define		BIST_MBIST1FTAG7_MBIST1FTAG7					(0xFFFFFFFFU)
/* MBIST2FTAG0 */
#define		BIST_MBIST2FTAG0_MBIST2FTAG0					(0xFFFFFFFFU)
/* MBIST2FTAG1 */
#define		BIST_MBIST2FTAG1_MBIST2FTAG1					(0xFFFFFFFFU)
/* MBIST2FTAG2 */
#define		BIST_MBIST2FTAG2_MBIST2FTAG2					(0xFFFFFFFFU)
/* MBIST3FTAG0 */
#define		BIST_MBIST3FTAG0_MBIST3FTAG0					(0xFFFFFFFFU)
/* MBIST3FTAG1 */
#define		BIST_MBIST3FTAG1_MBIST3FTAG1					(0xFFFFFFFFU)
/* MBIST3FTAG2 */
#define		BIST_MBIST3FTAG2_MBIST3FTAG2					(0xFFFFFFFFU)
/* MBIST4FTAG0 */
#define		BIST_MBIST4FTAG0_MBIST4FTAG0					(0xFFFFFFFFU)
/* MBIST4FTAG1 */
#define		BIST_MBIST4FTAG1_MBIST4FTAG1					(0xFFFFFFFFU)
/* MBIST5FTAG0 */
#define		BIST_MBIST5FTAG0_MBIST5FTAG0					(0xFFFFFFFFU)
/* MBIST5FTAG1 */
#define		BIST_MBIST5FTAG1_MBIST5FTAG1					(0xFFFFFFFFU)
/* MBIST6FTAG0 */
#define		BIST_MBIST6FTAG0_MBIST6FTAG0					(0xFFFFFFFFU)
/* MBIST6FTAG1 */
#define		BIST_MBIST6FTAG1_MBIST6FTAG1					(0xFFFFFFFFU)
/* MBIST7FTAG0 */
#define		BIST_MBIST7FTAG0_MBIST7FTAG0					(0xFFFFFFFFU)
/* MBIST7FTAG1 */
#define		BIST_MBIST7FTAG1_MBIST7FTAG1					(0xFFFFFFFFU)
/* MBIST8FTAG0 */
#define		BIST_MBIST8FTAG0_MBIST8FTAG0					(0xFFFFFFFFU)
/* MBIST8FTAG1 */
#define		BIST_MBIST8FTAG1_MBIST8FTAG1					(0xFFFFFFFFU)
/* MBIST8FTAG2 */
#define		BIST_MBIST8FTAG2_MBIST8FTAG2					(0xFFFFFFFFU)
/* MBIST8FTAG3 */
#define		BIST_MBIST8FTAG3_MBIST8FTAG3					(0xFFFFFFFFU)
/* MBIST8FTAG4 */
#define		BIST_MBIST8FTAG4_MBIST8FTAG4					(0xFFFFFFFFU)
/* MBIST8FTAG5 */
#define		BIST_MBIST8FTAG5_MBIST8FTAG5					(0xFFFFFFFFU)
/* MBIST8FTAG6 */
#define		BIST_MBIST8FTAG6_MBIST8FTAG6					(0xFFFFFFFFU)
/* MBIST1ECC0 */
#define		BIST_MBIST1ECC0_MBIST1ECC0						(0xFFFFFFFFU)
/* MBIST1ECC1 */
#define		BIST_MBIST1ECC1_MBIST1ECC1						(0xFFFFFFFFU)
/* MBIST1ECC2 */
#define		BIST_MBIST1ECC2_MBIST1ECC2						(0xFFFFFFFFU)
/* MBIST1ECC3 */
#define		BIST_MBIST1ECC3_MBIST1ECC3						(0xFFFFFFFFU)
/* MBIST1ECC4 */
#define		BIST_MBIST1ECC4_MBIST1ECC4						(0xFFFFFFFFU)
/* MBIST1ECC5 */
#define		BIST_MBIST1ECC5_MBIST1ECC5						(0xFFFFFFFFU)
/* MBIST1ECC6 */
#define		BIST_MBIST1ECC6_MBIST1ECC6						(0xFFFFFFFFU)
/* MBIST1ECC7 */
#define		BIST_MBIST1ECC7_MBIST1ECC7						(0xFFFFFFFFU)
/* MBIST2ECC0 */
#define		BIST_MBIST2ECC0_MBIST2ECC0						(0xFFFFFFFFU)
/* MBIST2ECC1 */
#define		BIST_MBIST2ECC1_MBIST2ECC1						(0xFFFFFFFFU)
/* MBIST2ECC2 */
#define		BIST_MBIST2ECC2_MBIST2ECC2						(0xFFFFFFFFU)
/* MBIST3ECC0 */
#define		BIST_MBIST3ECC0_MBIST3ECC0						(0xFFFFFFFFU)
/* MBIST3ECC1 */
#define		BIST_MBIST3ECC1_MBIST3ECC1						(0xFFFFFFFFU)
/* MBIST3ECC2 */
#define		BIST_MBIST3ECC2_MBIST3ECC2						(0xFFFFFFFFU)
/* MBIST4ECC0 */
#define		BIST_MBIST4ECC0_MBIST4ECC0						(0xFFFFFFFFU)
/* MBIST4ECC1 */
#define		BIST_MBIST4ECC1_MBIST4ECC1						(0xFFFFFFFFU)
/* MBIST5ECC0 */
#define		BIST_MBIST5ECC0_MBIST5ECC0						(0xFFFFFFFFU)
/* MBIST5ECC1 */
#define		BIST_MBIST5ECC1_MBIST5ECC1						(0xFFFFFFFFU)
/* MBIST6ECC0 */
#define		BIST_MBIST6ECC0_MBIST6ECC0						(0xFFFFFFFFU)
/* MBIST6ECC1 */
#define		BIST_MBIST6ECC1_MBIST6ECC1						(0xFFFFFFFFU)
/* MBIST7ECC0 */
#define		BIST_MBIST7ECC0_MBIST7ECC0						(0xFFFFFFFFU)
/* MBIST7ECC1 */
#define		BIST_MBIST7ECC1_MBIST7ECC1						(0xFFFFFFFFU)
/* MBIST8ECC0 */
#define		BIST_MBIST8ECC0_MBIST8ECC0						(0xFFFFFFFFU)
/* MBIST8ECC1 */
#define		BIST_MBIST8ECC1_MBIST8ECC1						(0xFFFFFFFFU)
/* MBIST8ECC2 */
#define		BIST_MBIST8ECC2_MBIST8ECC2						(0xFFFFFFFFU)
/* MBIST8ECC3 */
#define		BIST_MBIST8ECC3_MBIST8ECC3						(0xFFFFFFFFU)
/* MBIST8ECC4 */
#define		BIST_MBIST8ECC4_MBIST8ECC4						(0xFFFFFFFFU)
/* MBIST8ECC5 */
#define		BIST_MBIST8ECC5_MBIST8ECC5						(0xFFFFFFFFU)
/* MBIST8ECC6 */
#define		BIST_MBIST8ECC6_MBIST8ECC6						(0xFFFFFFFFU)
/* BSEQ0ST */
#define		BIST_BSEQ0ST_BISTEND							(BIT1)
#define		BIST_BSEQ0ST_CMPERR								(BIT0)
/* BSEQ0STB */
#define		BIST_BSEQ0STB_BISTENDB							(BIT1)
#define		BIST_BSEQ0STB_CMPERRB							(BIT0)
/* BISTST */
#define		BIST_BISTST_MBIST8ST							(BIT9)
#define		BIST_BISTST_MBIST7ST							(BIT8)
#define		BIST_BISTST_MBIST6ST							(BIT7)
#define		BIST_BISTST_MBIST5ST							(BIT6)
#define		BIST_BISTST_MBIST4ST							(BIT5)
#define		BIST_BISTST_MBIST3ST							(BIT4)
#define		BIST_BISTST_MBIST1ST							(BIT2)
#define		BIST_BISTST_LBIST2ST							(BIT1)
#define		BIST_BISTST_LBIST1ST							(BIT0)
/* BSEQ0SEL */
#define		BIST_BSEQ0SEL_PARAMSEL							(BIT15)
	#define		BIST_BSEQ0SEL_PARAMSEL_OPBT					(0)
	#define		BIST_BSEQ0SEL_PARAMSEL_REG					(1)
#define		BIST_BSEQ0SEL_HWTESTSET							(BIT5 + BIT4)
	#define		BIST_BSEQ0SEL_HTSET_LBISTONLY				(1)
	#define		BIST_BSEQ0SEL_HTSET_MBISTONLY				(2)
	#define		BIST_BSEQ0SEL_LBISTANDMBIST_HWTESTSET		(3)
#define		BIST_BSEQ0SEL_HWLBISTSEL						(BIT1 + BIT0)
	#define		BIST_BSEQ0SEL_HLSEL_SO1						(0)
	#define		BIST_BSEQ0SEL_HLSEL_SO2						(1)
	#define		BIST_BSEQ0SEL_HLSEL_SO3						(2)
	#define		BIST_BSEQ0SEL_HLSEL_SO5						(0)
	#define		BIST_BSEQ0SEL_HLSEL_SO6						(1)
	#define		BIST_BSEQ0SEL_HLSEL_SO7						(2)
	#define		BIST_BSEQ0SEL_HLSEL_SO9						(4)
	#define		BIST_BSEQ0SEL_HLSEL_S10						(5)
	#define		BIST_BSEQ0SEL_HLSEL_S11						(6)
	#define		BIST_BSEQ0SEL_HLSEL_S12						(7)
	#define		BIST_BSEQ0SEL_HLSEL_S13						(8)
	#define		BIST_BSEQ0SEL_HLSEL_S14						(9)
	#define		BIST_BSEQ0SEL_HLSEL_S15						(10)
	#define		BIST_BSEQ0SEL_HLSEL_S16						(11)
	#define		BIST_BSEQ0SEL_HLSEL_S17						(12)
	#define		BIST_BSEQ0SEL_HLSEL_S18						(13)
	#define		BIST_BSEQ0SEL_HLSEL_S19						(14)
	#define		BIST_BSEQ0SEL_HLSEL_S20						(15)


/* Module: SYSCTRL */
/* BSEQ0CTL */
#define		BIST_SYSCTRL_BSEQ0CTL_HWBISTSEL					(BIT1)
	#define		BIST_SYSCTRL_BSEQ0CTL_HBSEL_OPBT			(0)
	#define		BIST_SYSCTRL_BSEQ0CTL_HBSEL_HWBISTEXE		(1)
#define		BIST_SYSCTRL_BSEQ0CTL_HWBISTEXE					(BIT0)
	#define		BIST_SYSCTRL_BSEQ0CTL_HBEXE_SKIPPED			(0)
	#define		BIST_SYSCTRL_BSEQ0CTL_HBEXE_EXECUTED		(1)
/* BSEQ1CTL */
#define		BIST_SYSCTRL_BSEQ1CTL_HWBISTEXE					(BIT0)
	#define		BIST_SYSCTRL_BSEQ1CTL_HBEXE_SKIPPED			(0)
	#define		BIST_SYSCTRL_BSEQ1CTL_HBEXE_EXECUTED		(1)
/* BSEQ2CTL */
#define		BIST_SYSCTRL_BSEQ2CTL_HWBISTEXE					(BIT0)
	#define		BIST_SYSCTRL_BSEQ2CTL_HBEXE_SKIPPED			(0)
	#define		BIST_SYSCTRL_BSEQ2CTL_HBEXE_EXECUTED		(1)

/*==============================================================================================*/
/*	struct address definition																	*/
/*==============================================================================================*/
#define		REG_BIST_BIST		(*(volatile Reg_Bist_BistType	  *)(0xFF9A4400U))
#define		REG_BIST_SYSCTRL	(*(volatile Reg_Bist_SysctrlType  *)(0xFF988400U))


#endif /* REG_BIST_H */
