/* reg_hbg-r04-3000-0000-a-v00 */
/************************************************************************************************/
/*																								*/
/*		HBG register definition (for RH850U2B)													*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

#if 0 // zantei MPU‚Í2ŒŽ––”ñ‘Î‰ž

#ifndef REG_HBG_H
#define REG_HBG_H


/*==============================================================================================*/
/*	include files																				*/
/*==============================================================================================*/


/*==============================================================================================*/
/*	defines																						*/
/*==============================================================================================*/


/*==============================================================================================*/
/*	register type definition																	*/
/*==============================================================================================*/
/* HBG */
/* ============================================================================ */
/* =============================== Module: HBG ================================ */
/* ============================================================================ */
typedef	struct											/* HBG						   */
{
	union												/* HBGPROT0 OFFSET 0x00		   */
	{
		U4	u4Data;										/* 32-bit Access			   */
		struct											/* Bit Access				   */
		{
			U4	xRG					:1;					/* RG						   */
			U4	xWG					:1;					/* WG						   */
			U4	b2Dummy1			:2;					/* Reserved Bits			   */
			U4	xUM					:1;					/* UM						   */
			U4	xDummy2				:1;					/* Reserved Bits			   */
			U4	xDBG				:1;					/* DBG						   */
			U4	xDummy3				:1;					/* Reserved Bits			   */
			U4	xGEN				:1;					/* GEN						   */
			U4	b22Dummy4			:22;				/* Reserved Bits			   */
			U4	xLOCK				:1;					/* LOCK						   */
		} stBit;
	} unHBGPROT0;

	U4	u4HBGPROT1;										/* HBGPROT1 OFFSET 0x04		   */

} Reg_Hbg_HbgType;

typedef	struct											/* HBGERRSLV				   */
{
	union												/* HBGOVFCLR OFFSET 0x00	   */
	{
		U4	u4Data;										/* 32-bit Access			   */
		struct											/* Bit Access				   */
		{
			U4	xDummy1					:1;				/* Reserved Bits			   */
			U4	xCLRO					:1;				/* CLRO						   */
			U4	b30Dummy2				:30;			/* Reserved Bits			   */
		} stBit;
	} unHBGOVFCLR;

	union												/* HBGOVFSTAT OFFSET 0x04	   */
	{
		U4	u4Data;										/* 32-bit Access			   */
		struct											/* Bit Access				   */
		{
			U4	xDummy1					:1;				/* Reserved Bits			   */
			U4	xOVF					:1;				/* OVF						   */
			U4	b30Dummy2				:30;			/* Reserved Bits			   */
		} stBit;
	} unHBGOVFSTAT;

	U4	u4HBGERRADDR;									/* HBGERRADDR OFFSET 0x08	   */

	union												/* HBGERRTYPE OFFSET 0x0C	   */
	{
		U4	u4Data;										/* 32-bit Access			   */
		struct											/* Bit Access				   */
		{
			U4	xWRITE					:1;				/* WRITE					   */
			U4	b5Dummy1				:5;				/* Reserved Bits			   */
			U4	b5SPID					:5;				/* SPID						   */
			U4	xUM						:1;				/* UM						   */
			U4	xDBG					:1;				/* DBG						   */
			U4	xSEC					:1;				/* SEC						   */
			U4	b18Dummy2				:18;			/* Reserved Bits			   */
		} stBit;
	} unHBGERRTYPE;

	U4	u4HBGSPIDERRCLR;								/* HBGSPIDERRCLR OFFSET 0x10   */

	U4	u4HBGSPIDERRSTAT;								/* HBGSPIDERRSTAT OFFSET 0x14  */

	union												/* HBGKCPROT OFFSET 0x18	   */
	{
		U4	u4Data;										/* 32-bit Access			   */
		struct											/* Bit Access				   */
		{
			U4	xKCE					:1;				/* KCE						   */
			U4	b31KCPROT				:31;			/* KCPROT					   */
		} stBit;
	} unHBGKCPROT;

} Reg_Hbg_HbgErrSlvType;

/*----------------------------------------------------------------------------------------------*/
/*	register BIT definition																		*/
/*----------------------------------------------------------------------------------------------*/
/* =============================== Module: HBG ================================ */
/* HBGOVFCLR */
#define		HBG_HBGOVFCLR_CLRO					(BIT1)
	#define		HBG_HBGOVFCLR_CLRO_CLEAR		(1)

/* HBGOVFSTAT */
#define		HBG_HBGOVFSTAT_OVF					(BIT1)
	#define		HBG_HBGOVFSTAT_OVF_CLEAR		(0)

/* HBGERRADDR */

/* HBGERRTYPE */
#define		HBG_HBGERRTYPE_SEC					(BIT13)
#define		HBG_HBGERRTYPE_DBG					(BIT12)
#define		HBG_HBGERRTYPE_UM					(BIT11)
#define		HBG_HBGERRTYPE_SPID					(BIT10+BIT9+BIT8+BIT7+BIT6)
#define		HBG_HBGERRTYPE_SPID_0				(BIT6)
#define		HBG_HBGERRTYPE_WRITE				(BIT0)

/* HBGSPIDERRCLR */

/* HBGSPIDERRSTAT */

/* HBGKCPROT */
#define		HBG_HBGKCPROT_KCPROT				(BIT31+BIT30+BIT29+BIT28+BIT27+BIT26+BIT25+BIT24+BIT23+BIT22+BIT21+BIT20+BIT19+BIT18+BIT17+BIT16+BIT15+BIT14+BIT13+BIT12+BIT11+BIT10+BIT9+BIT8+BIT7+BIT6+BIT5+BIT4+BIT3+BIT2+BIT1)
#define		HBG_HBGKCPROT_KCPROT_0				(BIT1)
#define		HBG_HBGKCPROT_KCE					(BIT0)
	#define		HBG_HBGKCPROT_KCE_DISABLE		(0xA5A5A500U)
	#define		HBG_HBGKCPROT_KCE_ENABLE		(0xA5A5A501U)

/* HBGPROT0 */
#define		HBG_HBGPROT0_LOCK					(BIT31)
	#define		HBG_HBGPROT0_LOCK_DISABLE		(0)
	#define		HBG_HBGPROT0_LOCK_ENABLE		(1)
#define		HBG_HBGPROT0_GEN					(BIT8)
	#define		HBG_HBGPROT0_GEN_DISABLE		(0)
	#define		HBG_HBGPROT0_GEN_ENABLE			(1)
#define		HBG_HBGPROT0_DBG					(BIT6)
	#define		HBG_HBGPROT0_DBG_OTHER			(0)
	#define		HBG_HBGPROT0_DBG_ENABLE			(1)
#define		HBG_HBGPROT0_UM						(BIT4)
	#define		HBG_HBGPROT0_UM_DISABLE			(0)
	#define		HBG_HBGPROT0_UM_OTHER			(1)
#define		HBG_HBGPROT0_WG						(BIT1)
	#define		HBG_HBGPROT0_WG_USE				(0)
	#define		HBG_HBGPROT0_WG_NOUSE			(1)
#define		HBG_HBGPROT0_RG						(BIT0)
	#define		HBG_HBGPROT0_RG_USE				(0)
	#define		HBG_HBGPROT0_RG_NOUSE			(1)

/* HBGPROT1 */


/*----------------------------------------------------------------------------------------------*/
/*	struct address definition																	*/
/*----------------------------------------------------------------------------------------------*/
#define		Reg_HBG_HBG90			(*(volatile Reg_Hbg_HbgType        *)(0xFF0D0C00U))
#define		Reg_HBG_HBGERRSLV90		(*(volatile Reg_Hbg_HbgErrSlvType  *)(0xFF0D4600U))
#define		Reg_HBG_HBG91			(*(volatile Reg_Hbg_HbgType        *)(0xFF0D1000U))
#define		Reg_HBG_HBGERRSLV91		(*(volatile Reg_Hbg_HbgErrSlvType  *)(0xFF0D4800U))
#define		Reg_HBG_HBG92			(*(volatile Reg_Hbg_HbgType        *)(0xFF0D0000U))
#define		Reg_HBG_HBGERRSLV92		(*(volatile Reg_Hbg_HbgErrSlvType  *)(0xFF0D4000U))
#define		Reg_HBG_HBG94			(*(volatile Reg_Hbg_HbgType        *)(0xFF0D0800U))
#define		Reg_HBG_HBGERRSLV94		(*(volatile Reg_Hbg_HbgErrSlvType  *)(0xFF0D4400U))

#endif /* REG_HBG_H */
#endif // zantei MPU‚Í2ŒŽ––”ñ‘Î‰ž
/*-- End Of File -------------------------------------------------------------------------------*/
