/* reg_pbg-r04-3000-0000-a-v01 */
/************************************************************************************************/
/*																								*/
/*		PEG register definition (for RH850U2B)													*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

#if 0 // zantei MPUは2月末非対応

#ifndef REG_PBG_H
#define REG_PBG_H


/*==============================================================================================*/
/*	include files																				*/
/*==============================================================================================*/


/*==============================================================================================*/
/*	defines																						*/
/*==============================================================================================*/
#define		REG_PBG_CH_NUM			(16)			/* PBGチャネル数 */

/*==============================================================================================*/
/*	register type definition																	*/
/*==============================================================================================*/
/* PBG */
/* ============================================================================ */
/* =============================== Module: PBG ================================ */
/* ============================================================================ */
typedef	struct											/* PBG */
{
	struct												/* OFFSET 0x00 - 0x7F	  */
	{
		union											/* PBGPROT0_m OFFSET 0x00 */
		{
			U4	u4Data;									/* 32-bit Access		  */
			struct										/* Bit Access			  */
			{
				U4	xRG					:1;				/* RG					  */
				U4	xWG					:1;				/* WG					  */
				U4	b2Dummy1			:2;				/* Reserved Bits		  */
				U4	xUM					:1;				/* UM					  */
				U4	xDummy2				:1;				/* Reserved Bits		  */
				U4	xDBG				:1;				/* DBG					  */
				U4	xSEC				:1;				/* SEC					  */
				U4	xGEN				:1;				/* GEN					  */
				U4	b22Dummy3			:22;			/* Reserved Bits		  */
				U4	xLOCK				:1;				/* LOCK					  */
			} stBit;
		} unPBGPROT0;

		U4	u4PBGPROT1;									/* PBGPROT1_m OFFSET 0x04 */
	} stPBGPROT01[REG_PBG_CH_NUM];						/* PBG Groupに対応したdummy定義：アクセス禁止 */
														/* PBG00		:6, 11 - 15		 */
														/* PBG01		:6, 7, 14, 15	 */
														/* PBG10		:3 - 15			 */
														/* PBG20		:dummy定義なし	 */
														/* PBG21		:dummy定義なし	 */
														/* PBG22		:3				 */
														/* PBG23		:dummy定義なし	 */
														/* PBG24		:2 - 15			 */
														/* PBG30		:9				 */
														/* PBG31		:6				 */
														/* PBG32		:7 - 15			 */
														/* PBG40		:9				 */
														/* PBG41		:15				 */
														/* PBG50		:11,12			 */
														/* PBG51		:9, 10			 */
														/* PBG52		:7 - 15			 */
														/* PBG60		:6				 */
														/* PBG61		:9 - 15			 */
														/* PBG62		:4 - 15			 */
														/* PBG70		:dummy定義なし	 */
														/* PBG71		:4 - 15			 */
														/* PBG8H0		:11 - 15		 */
														/* PBG8L0		:13				 */
														/* PBG90		:10 - 15		 */
														/* PBG91		:4 - 15			 */
														/* PBG92		:8 - 15			 */
														/* PBG100		:12				 */
														/* PBG101		:7 - 15			 */
														/* PBG11H0		:13				 */
														/* PBG11H1		:1, 2			 */
														/* PBG11H2		:2 - 15			 */
														/* PBG11L0		:1, 9 - 15		 */

} Reg_Pbg_PbgType;

typedef	struct											/* PBG */
{
	union												/* PBGOVFCLR OFFSET 0x00  */
	{
		U4	u4Data;										/* 32-bit Access		  */
		struct											/* Bit Access			  */
		{
			U4	xDummy1					:1;				/* Reserved Bits		  */
			U4	xCLRO					:1;				/* CLRO					  */
			U4	b30Dummy2				:30;			/* Reserved Bits		  */
		} stBit;
	} unPBGOVFCLR;

	union												/* PBGOVFSTAT OFFSET 0x04 */
	{
		U4	u4Data;										/* 32-bit Access		  */
		struct											/* Bit Access			  */
		{
			U4	xDummy1					:1;				/* Reserved Bits		  */
			U4	xOVF					:1;				/* OVF					  */
			U4	b30Dummy2				:30;			/* Reserved Bits		  */
		} stBit;
	} unPBGOVFSTAT;

	U4	u4PBGERRADDR;									/* PBGERRADDR OFFSET 0x08 */

	union												/* PBGERRTYPE OFFSET 0x0C */
	{
		U4	u4Data;										/* 32-bit Access		  */
		struct											/* Bit Access			  */
		{
			U4	xWRITE					:1;				/* WRITE				  */
			U4	b5Dummy1				:5;				/* Reserved Bits		  */
			U4	b5SPID					:5;				/* SPID					  */
			U4	xUM						:1;				/* UM					  */
			U4	xDBG					:1;				/* DBG					  */
			U4	xSEC					:1;				/* SEC					  */
			U4	b18Dummy2				:18;			/* Reserved Bits		  */
		} stBit;
	} unPBGERRTYPE;

	U4	u4PBGSPIDERRCLR;								/* PBGERRADDR OFFSET 0x10 */

	U4	u4PBGSPIDERRSTAT;								/* PBGERRADDR OFFSET 0x14 */

	union												/* PBGKCPROT OFFSET 0x18  */
	{
		U4	u4Data;										/* 32-bit Access		  */
		struct											/* Bit Access			  */
		{
			U4	xKCE					:1;				/* KCE					  */
			U4	b31KCPROT				:31;			/* KCPROT				  */
		} stBit;
	} unPBGKCPROT;

} Reg_Pbg_PbgErrSlvType;

/*----------------------------------------------------------------------------------------------*/
/*	register BIT definition																		*/
/*----------------------------------------------------------------------------------------------*/
/* =============================== Module: PBG ================================ */
/* PBGOVFCLR */
#define		PBG_PBGOVFCLR_CLRO					(BIT1)
	#define		PBG_PBGOVFCLR_CLRO_CLEAR		(1)

/* PBGOVFSTAT */
#define		PBG_PBGOVFSTAT_OVF					(BIT1)
	#define		PBG_PBGOVFSTAT_OVF_CLEAR		(0)

/* PBGERRADDR */

/* PBGERRTYPE */
#define		PBG_PBGERRTYPE_SEC					(BIT13)
#define		PBG_PBGERRTYPE_DBG					(BIT12)
#define		PBG_PBGERRTYPE_UM					(BIT11)
#define		PBG_PBGERRTYPE_SPID					(BIT10+BIT9+BIT8+BIT7+BIT6)
#define		PBG_PBGERRTYPE_SPID_0				(BIT6)
#define		PBG_PBGERRTYPE_WRITE				(BIT0)

/* PBGERRADDR */

/* PBGERRADDR */

/* PBGKCPROT */
#define		PBG_PBGKCPROT_KCPROT				(BIT31+BIT30+BIT29+BIT28+BIT27+BIT26+BIT25+BIT24+BIT23+BIT22+BIT21+BIT20+BIT19+BIT18+BIT17+BIT16+BIT15+BIT14+BIT13+BIT12+BIT11+BIT10+BIT9+BIT8+BIT7+BIT6+BIT5+BIT4+BIT3+BIT2+BIT1)
#define		PBG_PBGKCPROT_KCPROT_0				(BIT1)
#define		PBG_PBGKCPROT_KCE					(BIT0)
	#define		PBG_PBGKCPROT_KCE_DISABLE		(0xA5A5A500U)
	#define		PBG_PBGKCPROT_KCE_ENABLE		(0xA5A5A501U)

/* PBGPROT0 */
#define		PBG_PBGPROT0_LOCK					(BIT31)
	#define		PBG_PBGPROT0_LOCK_DISABLE		(0)
	#define		PBG_PBGPROT0_LOCK_ENABLE		(1)
#define		PBG_PBGPROT0_GEN					(BIT8)
	#define		PBG_PBGPROT0_GEN_DISABLE		(0)
	#define		PBG_PBGPROT0_GEN_ENABLE			(1)
#define		PBG_PBGPROT0_SEC					(BIT7)
	#define		PBG_PBGPROT0_SEC_DISABLE		(0)
	#define		PBG_PBGPROT0_SEC_OTHER			(1)
#define		PBG_PBGPROT0_DBG					(BIT6)
	#define		PBG_PBGPROT0_DBG_OTHER			(0)
	#define		PBG_PBGPROT0_DBG_ENABLE			(1)
#define		PBG_PBGPROT0_UM						(BIT4)
	#define		PBG_PBGPROT0_UM_DISABLE			(0)
	#define		PBG_PBGPROT0_UM_OTHER			(1)
#define		PBG_PBGPROT0_WG						(BIT1)
	#define		PBG_PBGPROT0_WG_USE				(0)
	#define		PBG_PBGPROT0_WG_NOUSE			(1)
#define		PBG_PBGPROT0_RG						(BIT0)
	#define		PBG_PBGPROT0_RG_USE				(0)
	#define		PBG_PBGPROT0_RG_NOUSE			(1)

/* PBGPROT1 */


/*----------------------------------------------------------------------------------------------*/
/*	struct address definition																	*/
/*----------------------------------------------------------------------------------------------*/
#define		Reg_PBG_PBG00			(*(volatile Reg_Pbg_PbgType	  *)		(0xFFC6B080U))
#define		Reg_PBG_PBG01			(*(volatile Reg_Pbg_PbgType	  *)		(0xFFC6B100U))
#define		Reg_PBG_PBGERRSLV00		(*(volatile Reg_Pbg_PbgErrSlvType	  *)(0xFFC6B000U))
#define		Reg_PBG_PBG10			(*(volatile Reg_Pbg_PbgType	  *)		(0xFFC63000U))
#define		Reg_PBG_PBGERRSLV10		(*(volatile Reg_Pbg_PbgErrSlvType	  *)(0xFFC63100U))
#define		Reg_PBG_PBG20			(*(volatile Reg_Pbg_PbgType	  *)		(0xFFDE0B00U))
#define		Reg_PBG_PBG21			(*(volatile Reg_Pbg_PbgType	  *)		(0xFFDE0C00U))
#define		Reg_PBG_PBG22			(*(volatile Reg_Pbg_PbgType	  *)		(0xFFDE0D00U))
#define		Reg_PBG_PBG23			(*(volatile Reg_Pbg_PbgType	  *)		(0xFFDE0E00U))
#define		Reg_PBG_PBG24			(*(volatile Reg_Pbg_PbgType	  *)		(0xFFDE1200U))
#define		Reg_PBG_PBGERRSLV20		(*(volatile Reg_Pbg_PbgErrSlvType	  *)(0xFFDE1000U))
#define		Reg_PBG_PBG30			(*(volatile Reg_Pbg_PbgType	  *)		(0xFFC72B00U))
#define		Reg_PBG_PBG31			(*(volatile Reg_Pbg_PbgType	  *)		(0xFFC72C00U))
#define		Reg_PBG_PBG32			(*(volatile Reg_Pbg_PbgType	  *)		(0xFFC72D00U))
#define		Reg_PBG_PBGERRSLV30		(*(volatile Reg_Pbg_PbgErrSlvType	  *)(0xFFC73200U))
#define		Reg_PBG_PBG40			(*(volatile Reg_Pbg_PbgType	  *)		(0xFFC75300U))
#define		Reg_PBG_PBG41			(*(volatile Reg_Pbg_PbgType	  *)		(0xFFC75380U))
#define		Reg_PBG_PBGERRSLV40		(*(volatile Reg_Pbg_PbgErrSlvType	  *)(0xFFC75400U))
#define		Reg_PBG_PBG50			(*(volatile Reg_Pbg_PbgType	  *)		(0xFFC7A300U))
#define		Reg_PBG_PBG51			(*(volatile Reg_Pbg_PbgType	  *)		(0xFFC7A400U))
#define		Reg_PBG_PBG52			(*(volatile Reg_Pbg_PbgType	  *)		(0xFFC7A500U))
#define		Reg_PBG_PBGERRSLV50		(*(volatile Reg_Pbg_PbgErrSlvType	  *)(0xFFC7B000U))
#define		Reg_PBG_PBG60			(*(volatile Reg_Pbg_PbgType	  *)		(0xFFC81000U))
#define		Reg_PBG_PBG61			(*(volatile Reg_Pbg_PbgType	  *)		(0xFFC81200U))
#define		Reg_PBG_PBGERRSLV60		(*(volatile Reg_Pbg_PbgErrSlvType	  *)(0xFFC83000U))
#define		Reg_PBG_PBG62			(*(volatile Reg_Pbg_PbgType	  *)		(0xFFC82000U))
#define		Reg_PBG_PBGERRSLV62		(*(volatile Reg_Pbg_PbgErrSlvType	  *)(0xFFC83040U))
#define		Reg_PBG_PBG70			(*(volatile Reg_Pbg_PbgType	  *)		(0xFFF49400U))
#define		Reg_PBG_PBG71			(*(volatile Reg_Pbg_PbgType	  *)		(0xFFF49600U))
#define		Reg_PBG_PBGERRSLV70		(*(volatile Reg_Pbg_PbgErrSlvType	  *)(0xFFF4A000U))
#define		Reg_PBG_PBG8H0			(*(volatile Reg_Pbg_PbgType	  *)		(0xFFF29300U))
#define		Reg_PBG_PBGERRSLV8H0	(*(volatile Reg_Pbg_PbgErrSlvType	  *)(0xFFF2A000U))
#define		Reg_PBG_PBG8L0			(*(volatile Reg_Pbg_PbgType	  *)		(0xFF97A000U))
#define		Reg_PBG_PBGERRSLV8L0	(*(volatile Reg_Pbg_PbgErrSlvType	  *)(0xFF97A200U))
#define		Reg_PBG_PBG90			(*(volatile Reg_Pbg_PbgType	  *)		(0xFF0A1300U))
#define		Reg_PBG_PBGERRSLV90		(*(volatile Reg_Pbg_PbgErrSlvType	  *)(0xFF0A1400U))
#define		Reg_PBG_PBG91			(*(volatile Reg_Pbg_PbgType	  *)		(0xFF0A1500U))
#define		Reg_PBG_PBGERRSLV91		(*(volatile Reg_Pbg_PbgErrSlvType	  *)(0xFF0A1600U))
#define		Reg_PBG_PBG92			(*(volatile Reg_Pbg_PbgType	  *)		(0xFF0A1700U))
#define		Reg_PBG_PBG100			(*(volatile Reg_Pbg_PbgType	  *)		(0xFF879400U))
#define		Reg_PBG_PBG101			(*(volatile Reg_Pbg_PbgType	  *)		(0xFF879500U))
#define		Reg_PBG_PBGERRSLV100	(*(volatile Reg_Pbg_PbgErrSlvType	  *)(0xFF87A000U))
#define		Reg_PBG_PBG11H0			(*(volatile Reg_Pbg_PbgType	  *)		(0xFF8B1400U))
#define		Reg_PBG_PBG11H1			(*(volatile Reg_Pbg_PbgType	  *)		(0xFF8B1600U))
#define		Reg_PBG_PBG11H2			(*(volatile Reg_Pbg_PbgType	  *)		(0xFF8B1800U))
#define		Reg_PBG_PBGERRSLV11H0	(*(volatile Reg_Pbg_PbgErrSlvType	  *)(0xFF8B2000U))
#define		Reg_PBG_PBG11L0			(*(volatile Reg_Pbg_PbgType	  *)		(0xFF8F8000U))
#define		Reg_PBG_PBGERRSLV11L0	(*(volatile Reg_Pbg_PbgErrSlvType	  *)(0xFF8F8100U))

#endif /* REG_PBG_H */

#endif // zantei MPUは2月末非対応

/*-- End Of File -------------------------------------------------------------------------------*/
