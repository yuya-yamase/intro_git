/* reg_crg-r04-3000-0000-a-v01 */
/************************************************************************************************/
/*																								*/
/*		CRG register definition (for RH850U2B)													*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

#if 0 // zantei MPUは2月末非対応

#ifndef REG_CRG_H
#define REG_CRG_H


/*==============================================================================================*/
/*	include files																				*/
/*==============================================================================================*/


/*==============================================================================================*/
/*	defines																						*/
/*==============================================================================================*/
#define		REG_CRG_CRG_CH_NUM			(8)		/* CRGチャネル数 */
#define		REG_CRG_CSG_CH_NUM			(4)		/* CSGチャネル数 */

/*==============================================================================================*/
/*	register type definition																	*/
/*==============================================================================================*/
typedef	struct											/* GUARD_CRAMCRGm(m=0 - 2)	  */
{

	union												/* CRGKCPROT OFFSET 0x00  */
	{
		U4	u4Data;										/* 32-bit Access		  */
		struct											/* Bit Access			  */
		{
			U4	xKCE					:1;				/* KCE					  */
			U4	b31KCPROT				:31;			/* KCPROT				 */
		} stBit;
	} unCRGKCPROT;

	U1	u1Dummy1[12];									/* OFFSET 0x04 - 0x0F	  */

	struct												/* OFFSET 0x10 - 0x8F	  */
	{
		union											/* CRGPROTm OFFSET 0x00   */
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
				U4	xDummy3				:1;				/* Reserved Bits		  */
				U4	xGEN				:1;				/* GEN					  */
				U4	b7Dummy4			:7;				/* Reserved Bits		  */
				U4	xOW				:1;					/* OW					  */
				U4	b15Dummy4			:15;			/* Reserved Bits		  */
			} stBit;
		} unCRGPROT;

		U4	u4CRGSPID;									/* CRGSPIDm OFFSET 0x04   */

		union											/* CRGBADm OFFSET 0x08	  */
		{
			U4	u4Data;									/* 32-bit Access		  */
			struct										/* Bit Access			  */
			{
				U4	b8Dummy1			:8;				/* Reserved Bits		  */
				U4	b11BAD				:11;			/* BAD					  */
				U4	b13Dummy2			:13;			/* Reserved Bits		  */
			} stBit;
		} unCRGBAD;

		union											/* CRGADVm OFFSET 0x0C	  */
		{
			U4	u4Data;									/* 32-bit Access		  */
			struct										/* Bit Access			  */
			{
				U4	b8Dummy1			:8;				/* Reserved Bits		  */
				U4	b11ADV				:11;			/* ADV					  */
				U4	b13Dummy2			:13;			/* Reserved Bits		  */
			} stBit;
		} unCRGADV;

		U4	u4CRGIVCSPID;								/* CRGIVCSPIDm OFFSET 0x10  */

		U1	u1Dummy2[12];								/* OFFSET 0x14 - 0x20	  */

	} stCH[REG_CRG_CRG_CH_NUM];

} Reg_Crg_Guardcramcrg0Type;


typedef	struct											/* GUARD_CRAMCRGm(m = 4)  */
{

	union												/* CRGKCPROT OFFSET 0x00  */
	{
		U4	u4Data;										/* 32-bit Access		  */
		struct											/* Bit Access			  */
		{
			U4	xKCE					:1;				/* KCE					  */
			U4	b31KCPROT				:31;			/* KCPROT				  */
		} stBit;
	} unCRGKCPROT;

	U1	u1Dummy1[12];									/* OFFSET 0x04 - 0x0F	  */

	struct												/* OFFSET 0x10 - 0x8F	  */
	{
		union											/* CRGPROTm OFFSET 0x00   */
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
				U4	xDummy3				:1;				/* Reserved Bits		  */
				U4	xGEN				:1;				/* GEN					  */
				U4	b7Dummy4			:7;				/* Reserved Bits		  */
				U4	xOW				:1;					/* OW					  */
				U4	b15Dummy4			:15;			/* Reserved Bits		  */
			} stBit;
		} unCRGPROT;

		U4	u4CRGSPID;									/* CRGSPIDm OFFSET 0x04   */

		union											/* CRGBADm OFFSET 0x08	  */
		{
			U4	u4Data;									/* 32-bit Access		  */
			struct										/* Bit Access			  */
			{
				U4	b8Dummy1			:8;				/* Reserved Bits		  */
				U4	b14BAD				:14;			/* BAD					  */
				U4	b10Dummy2			:10;			/* Reserved Bits		  */
			} stBit;
		} unCRGBAD;

		union											/* CRGADVm OFFSET 0x0C	  */
		{
			U4	u4Data;									/* 32-bit Access		  */
			struct										/* Bit Access			  */
			{
				U4	b8Dummy1			:8;				/* Reserved Bits		  */
				U4	b14ADV				:14;			/* ADV					  */
				U4	b10Dummy2			:10;			/* Reserved Bits		  */
			} stBit;
		} unCRGADV;

		U4	u4CRGIVCSPID;								/* CRGIVCSPIDm OFFSET 0x10   */

		U1	u1Dummy2[12];								/* OFFSET 0x14 - 0x20	  */

	} stCH[REG_CRG_CRG_CH_NUM];

} Reg_Crg_Guardcramcrg4Type;


typedef	struct											/* GUARD_CRAMCSGm(m=0 - 2)  */
{

	struct												/* OFFSET 0x10 - 0x8F	  */
	{
		union											/* CSGPROTm OFFSET 0x00   */
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
				U4	xDummy3				:1;				/* Reserved Bits		  */
				U4	xGEN				:1;				/* GEN					  */
				U4	b22Dummy4			:22;			/* Reserved Bits		  */
				U4	xLOCK				:1;				/* LOCK					  */
			} stBit;
		} unCSGPROT;

		U4	u4CSGSPID;									/* CSGSPIDm OFFSET 0x04   */

		union											/* CSGBADm OFFSET 0x08	  */
		{
			U4	u4Data;									/* 32-bit Access		  */
			struct										/* Bit Access			  */
			{
				U4	b8Dummy1			:8;				/* Reserved Bits		  */
				U4	b11BAD				:11;			/* BAD					  */
				U4	b13Dummy2			:13;			/* Reserved Bits		  */
			} stBit;
		} unCSGBAD;

		union											/* CSGADVm OFFSET 0x0C	  */
		{
			U4	u4Data;									/* 32-bit Access		  */
			struct										/* Bit Access			  */
			{
				U4	b8Dummy1			:8;				/* Reserved Bits		  */
				U4	b11ADV				:11;			/* ADV					  */
				U4	b13Dummy2			:13;			/* Reserved Bits		  */
			} stBit;
		} unCSGADV;

		U1	u1Dummy2[16];								/* OFFSET 0x10 - 0x20	  */

	} stCH[REG_CRG_CSG_CH_NUM];

} Reg_Crg_Guardcramcsg0Type;


typedef	struct											/* GUARD_CRAMCSGm(m = 4)  */
{

	struct												/* OFFSET 0x10 - 0x8F	  */
	{
		union											/* CSGPROTm OFFSET 0x00   */
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
				U4	xDummy3				:1;				/* Reserved Bits		  */
				U4	xGEN				:1;				/* GEN					  */
				U4	b22Dummy4			:22;			/* Reserved Bits		  */
				U4	xLOCK				:1;				/* LOCK					  */
			} stBit;
		} unCSGPROT;

		U4	u4CSGSPID;									/* CSGSPIDm OFFSET 0x04   */

		union											/* CSGBADm OFFSET 0x08	  */
		{
			U4	u4Data;									/* 32-bit Access		  */
			struct										/* Bit Access			  */
			{
				U4	b8Dummy1			:8;				/* Reserved Bits		  */
				U4	b14BAD				:14;			/* BAD					  */
				U4	b10Dummy2			:10;			/* Reserved Bits		  */
			} stBit;
		} unCSGBAD;

		union											/* CSGADVm OFFSET 0x0C	  */
		{
			U4	u4Data;									/* 32-bit Access		  */
			struct										/* Bit Access			  */
			{
				U4	b8Dummy1			:8;				/* Reserved Bits		  */
				U4	b14ADV				:14;			/* ADV					  */
				U4	b10Dummy2			:10;			/* Reserved Bits		  */
			} stBit;
		} unCSGADV;

		U1	u1Dummy2[16];								/* OFFSET 0x10 - 0x20	  */

	} stCH[REG_CRG_CSG_CH_NUM];

} Reg_Crg_Guardcramcsg4Type;


typedef	struct											/* CRGCAP_***			  */
{
	union												/* CRGOVFCLR OFFSET 0x00  */
	{
		U4	u4Data;										/* 32-bit Access		  */
		struct											/* Bit Access			  */
		{
			U4	xDummy1					:1;				/* Reserved Bits		  */
			U4	xCLRO					:1;				/* CLRO					  */
			U4	b30Dummy2				:30;			/* Reserved Bits		  */
		} stBit;
	} unCRGOVFCLR;

	union												/* CRGOVFSTAT OFFSET 0x04 */
	{
		U4	u4Data;										/* 32-bit Access		  */
		struct											/* Bit Access			  */
		{
			U4	xDummy1					:1;				/* Reserved Bits		  */
			U4	xOVF					:1;				/* OVF					  */
			U4	b30Dummy2				:30;			/* Reserved Bits		  */
		} stBit;
	} unCRGOVFSTAT;

	U4	u4CRGERRADDR;									/* CRGERRADDR OFFSET 0x08 */

	union												/* CRGERRTYPE OFFSET 0x0C */
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
	} unCRGERRTYPE;

	U4	u4CRGSPIDERRCLR;								/* CRGSPIDERRCLR OFFSET 0x10 */

	U4	u4CRGSPIDERRSTAT;								/* CRGSPIDERRSTAT OFFSET 0x14 */

} Reg_Crg_CrgcapType;



/*----------------------------------------------------------------------------------------------*/
/*	register BIT definition																		*/
/*----------------------------------------------------------------------------------------------*/
/* CRGKCPROT */
#define		CRG_CRGKCPROT_KCPROT				(BIT31+BIT30+BIT29+BIT28+BIT27+BIT26+BIT25+BIT24+BIT23+BIT22+BIT21+BIT20+BIT19+BIT18+BIT17+BIT16+BIT15+BIT14+BIT13+BIT12+BIT11+BIT10+BIT9+BIT8+BIT7+BIT6+BIT5+BIT4+BIT3+BIT2+BIT1)
#define		CRG_CRGKCPROT_KCPROT_0				(BIT1)
#define		CRG_CRGKCPROT_KCE					(BIT0)
	#define		CRG_CRGKCPROT_KCE_DISABLE		(0xA5A5A500U)
	#define		CRG_CRGKCPROT_KCE_ENABLE		(0xA5A5A501U)

/* CRGPROTm */
#define		CRG_CRGPROT_OW						(BIT16)
	#define		CRG_CRGPROT_OW_DISABLE			(0)
	#define		CRG_CRGPROT_OW_ENABLE			(1)
#define		CRG_CRGPROT_GEN						(BIT8)
	#define		CRG_CRGPROT_GEN_DISABLE			(0)
	#define		CRG_CRGPROT_GEN_ENABLE			(1)
#define		CRG_CRGPROT_DBG						(BIT6)
	#define		CRG_CRGPROT_DBG_OTHER			(0)
	#define		CRG_CRGPROT_DBG_ENABLE			(1)
#define		CRG_CRGPROT_UM						(BIT4)
	#define		CRG_CRGPROT_UM_DISABLE			(0)
	#define		CRG_CRGPROT_UM_OTHER			(1)
#define		CRG_CRGPROT_WG						(BIT1)
	#define		CRG_CRGPROT_WG_USE				(0)
	#define		CRG_CRGPROT_WG_NOUSE			(1)
#define		CRG_CRGPROT_RG						(BIT0)
	#define		CRG_CRGPROT_RG_USE				(0)
	#define		CRG_CRGPROT_RG_NOUSE			(1)

/* CRGSPIDm */

/* CRGBADm */
#define		CRG_CRGBAD_BAD_21					(BIT21+BIT20+BIT19+BIT18+BIT17+BIT16+BIT15+BIT14+BIT13+BIT12+BIT11+BIT10+BIT9+BIT8)
#define		CRG_CRGBAD_BAD						(BIT18+BIT17+BIT16+BIT15+BIT14+BIT13+BIT12+BIT11+BIT10+BIT9+BIT8)
#define		CRG_CRGBAD_BAD_0					(BIT8)

/* CRGADVm */
#define		CRG_CRGADV_ADV_21					(BIT21+BIT20+BIT19+BIT18+BIT17+BIT16+BIT15+BIT14+BIT13+BIT12+BIT11+BIT10+BIT9+BIT8)
#define		CRG_CRGADV_ADV						(BIT18+BIT17+BIT16+BIT15+BIT14+BIT13+BIT12+BIT11+BIT10+BIT9+BIT8)
#define		CRG_CRGADV_ADV_0					(BIT8)

/* CRGIVCSPID */

/* CSGPROTm */
#define		CRG_CSGPROT_LOCK					(BIT31)
	#define		CRG_CSGPROT_LOCK_DISABLE		(0)
	#define		CRG_CSGPROT_LOCK_ENABLE			(1)
#define		CRG_CSGPROT_GEN						(BIT8)
	#define		CRG_CSGPROT_GEN_DISABLE			(0)
	#define		CRG_CSGPROT_GEN_ENABLE			(1)
#define		CRG_CSGPROT_DBG						(BIT6)
	#define		CRG_CSGPROT_DBG_OTHER			(0)
	#define		CRG_CSGPROT_DBG_ENABLE			(1)
#define		CRG_CSGPROT_UM						(BIT4)
	#define		CRG_CSGPROT_UM_DISABLE			(0)
	#define		CRG_CSGPROT_UM_OTHER			(1)
#define		CRG_CSGPROT_WG						(BIT1)
	#define		CRG_CSGPROT_WG_USE				(0)
	#define		CRG_CSGPROT_WG_NOUSE			(1)
#define		CRG_CSGPROT_RG						(BIT0)
	#define		CRG_CSGPROT_RG_USE				(0)
	#define		CRG_CSGPROT_RG_NOUSE			(1)

/* CSGSPIDm */

/* CSGBADm */
#define		CRG_CSGBAD_BAD_21					(BIT21+BIT20+BIT19+BIT18+BIT17+BIT16+BIT15+BIT14+BIT13+BIT12+BIT11+BIT10+BIT9+BIT8)
#define		CRG_CSGBAD_BAD						(BIT18+BIT17+BIT16+BIT15+BIT14+BIT13+BIT12+BIT11+BIT10+BIT9+BIT8)
#define		CRG_CSGBAD_BAD_0					(BIT8)

/* CSGADVm */
#define		CRG_CSGADV_ADV_21					(BIT21+BIT20+BIT19+BIT18+BIT17+BIT16+BIT15+BIT14+BIT13+BIT12+BIT11+BIT10+BIT9+BIT8)
#define		CRG_CSGADV_ADV						(BIT18+BIT17+BIT16+BIT15+BIT14+BIT13+BIT12+BIT11+BIT10+BIT9+BIT8)
#define		CRG_CSGADV_ADV_0					(BIT8)

/* CRGOVFCLR */
#define		CRG_CRGOVFCLR_CLRO					(BIT1)
	#define		CRG_CRGOVFCLR_CLRO_CLEAR		(1)

/* CRGOVFSTAT */
#define		CRG_CRGOVFSTAT_OVF					(BIT1)
	#define		CRG_CRGOVFSTAT_OVF_CLEAR		(0)

/* CRGERRADDR */

/* CRGERRTYPE */
#define		CRG_CRGERRTYPE_SEC					(BIT13)
#define		CRG_CRGERRTYPE_DBG					(BIT12)
#define		CRG_CRGERRTYPE_UM					(BIT11)
#define		CRG_CRGERRTYPE_SPID					(BIT10+BIT9+BIT8+BIT7+BIT6)
#define		CRG_CRGERRTYPE_SPID_0				(BIT6)
#define		CRG_CRGERRTYPE_WRITE				(BIT0)

/* CRGSPIDERRCLR */

/* CRGSPIDERRSTAT */


/*----------------------------------------------------------------------------------------------*/
/*	struct address definition																	*/
/*----------------------------------------------------------------------------------------------*/
#define		Reg_CRG_GUARDCRAMCRG0	(*(volatile Reg_Crg_Guardcramcrg0Type *)(0xFFC6D000U))
#define		Reg_CRG_GUARDCRAMCRG1	(*(volatile Reg_Crg_Guardcramcrg0Type *)(0xFFC6D200U))
#define		Reg_CRG_GUARDCRAMCRG2	(*(volatile Reg_Crg_Guardcramcrg0Type *)(0xFFC6D400U))
#define		Reg_CRG_GUARDCRAMCRG4	(*(volatile Reg_Crg_Guardcramcrg4Type *)(0xFFC5C000U))
#define		Reg_CRG_CRGCAPPE0CL0	(*(volatile Reg_Crg_CrgcapType	   *)   (0xFFC6D800U))
#define		Reg_CRG_CRGCAPPE1CL0	(*(volatile Reg_Crg_CrgcapType	   *)   (0xFFC6D820U))
#define		Reg_CRG_CRGCAPPE2CL1	(*(volatile Reg_Crg_CrgcapType	   *)   (0xFFC6D840U))
#define		Reg_CRG_CRGCAPPE3CL1	(*(volatile Reg_Crg_CrgcapType	   *)   (0xFFC6D860U))
#define		Reg_CRG_CRGCAPPE4CL2	(*(volatile Reg_Crg_CrgcapType	   *)   (0xFFC6D880U))
#define		Reg_CRG_CRGCAPPE5CL2	(*(volatile Reg_Crg_CrgcapType	   *)   (0xFFC6D8A0U))
#define		Reg_CRG_CRGCAPCRAMHCL0	(*(volatile Reg_Crg_CrgcapType	   *)   (0xFFC6DA00U))
#define		Reg_CRG_CRGCAPCRAMLCL0	(*(volatile Reg_Crg_CrgcapType	   *)   (0xFFC6DA20U))
#define		Reg_CRG_CRGCAPSX2MBHCL0	(*(volatile Reg_Crg_CrgcapType	   *)   (0xFFC6DA40U))
#define		Reg_CRG_CRGCAPSX2MBLCL0	(*(volatile Reg_Crg_CrgcapType	   *)   (0xFFC6DA60U))
#define		Reg_CRG_CRGCAPCRAMHCL1	(*(volatile Reg_Crg_CrgcapType	   *)   (0xFFC6DA80U))
#define		Reg_CRG_CRGCAPCRAMLCL1	(*(volatile Reg_Crg_CrgcapType	   *)   (0xFFC6DAA0U))
#define		Reg_CRG_CRGCAPSX2MBHCL1	(*(volatile Reg_Crg_CrgcapType	   *)   (0xFFC6DAC0U))
#define		Reg_CRG_CRGCAPSX2MBLCL1	(*(volatile Reg_Crg_CrgcapType	   *)   (0xFFC6DAE0U))
#define		Reg_CRG_CRGCAPCRAMHCL2	(*(volatile Reg_Crg_CrgcapType	   *)   (0xFFC6DB00U))
#define		Reg_CRG_CRGCAPCRAMLCL2	(*(volatile Reg_Crg_CrgcapType	   *)   (0xFFC6DB20U))
#define		Reg_CRG_CRGCAPSX2MBHCL2	(*(volatile Reg_Crg_CrgcapType	   *)   (0xFFC6DB40U))
#define		Reg_CRG_CRGCAPSX2MBLCL2	(*(volatile Reg_Crg_CrgcapType	   *)   (0xFFC6DB60U))
#define		Reg_CRG_CRGCAPCRAMHCL4	(*(volatile Reg_Crg_CrgcapType	   *)   (0xFFC6DC00U))
#define		Reg_CRG_CRGCAPCRAMLCL4	(*(volatile Reg_Crg_CrgcapType	   *)   (0xFFC6DC20U))
#define		Reg_CRG_CRGCAPSX2MBHCL4	(*(volatile Reg_Crg_CrgcapType	   *)   (0xFFC6DC40U))
#define		Reg_CRG_CRGCAPSX2MBLCL4	(*(volatile Reg_Crg_CrgcapType	   *)   (0xFFC6DC60U))
#define		Reg_CRG_GUARDCRAMCSG0	(*(volatile Reg_Crg_Guardcramcsg0Type *)(0xFFC6E000U))
#define		Reg_CRG_GUARDCRAMCSG1	(*(volatile Reg_Crg_Guardcramcsg0Type *)(0xFFC6E200U))
#define		Reg_CRG_GUARDCRAMCSG2	(*(volatile Reg_Crg_Guardcramcsg0Type *)(0xFFC6E400U))
#define		Reg_CRG_GUARDCRAMCSG4	(*(volatile Reg_Crg_Guardcramcsg4Type *)(0xFFC5C300U))



#endif /* REG_CRG_H */
#endif // zantei MPUは2月末非対応

/*-- End Of File -------------------------------------------------------------------------------*/
