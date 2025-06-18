/* reg_peg-r04-3000-0000-a-v01 */
/************************************************************************************************/
/*																								*/
/*		PEG register definition (for RH850U2B)													*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

#if 0 // zantei MPUÇÕ2åéññîÒëŒâû

#ifndef REG_PEG_H
#define REG_PEG_H


/*==============================================================================================*/
/*	include files																				*/
/*==============================================================================================*/


/*==============================================================================================*/
/*	defines																						*/
/*==============================================================================================*/
#define		REG_PEG_CH_NUM			(8)			/* PEGÉ`ÉÉÉlÉãêî */


/*==============================================================================================*/
/*	register type definition																	*/
/*==============================================================================================*/
typedef	struct											/* GUARD_PEnCL0, GUARD_PEnCL1, GUARD_PEnCL2	 */
{

	union												/* PEGKCPROT OFFSET 0x00  */
	{
		U4	u4Data;										/* 32-bit Access		  */
		struct											/* Bit Access			  */
		{
			U4	xKCE					:1;				/* KCE					  */
			U4	b31KCPROT				:31;			/* KCPROT				  */
		} stBit;
	} unPEGKCPROT;

	U1	u1Dummy1[60];									/* OFFSET 0x04 - 0x3F	  */

	struct												/* OFFSET 0x40 - 0xBC	  */
	{
		union											/* PEGPROT OFFSET 0x40	  */
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
				U4	b23Dummy4			:23;			/* Reserved Bits		  */
			} stBit;
		} unPEGPROT;

		U4	u4PEGSPID;									/* PEGSPID OFFSET 0x44	  */

		union											/* PEGBAD OFFSET 0x48	  */
		{
			U4	u4Data;									/* 32-bit Access		  */
			struct										/* Bit Access			  */
			{
				U4	b12Dummy1			:12;			/* Reserved Bits		  */
				U4	b14BAD				:14;			/* BAD					  */
				U4	b6Dummy2			:6;				/* Reserved Bits		  */
			} stBit;
		} unPEGBAD;

		union											/* PEGADV OFFSET 0x4C	  */
		{
			U4	u4Data;									/* 32-bit Access		  */
			struct										/* Bit Access			  */
			{
				U4	b12Dummy1			:12;			/* Reserved Bits		  */
				U4	b14ADV				:14;			/* ADV					  */
				U4	b6Dummy2			:6;				/* Reserved Bits		  */
			} stBit;
		} unPEGADV;

	} stCH[REG_PEG_CH_NUM];

} Reg_Peg_GuardpeclType;



typedef	struct											/* GUARD_M/S_PEnCL0, GUARD_M/S_PEnCL1, GUARD_M/S_PEnCL2	 */
{

	union												/* PEGOVFCLR OFFSET 0x00  */
	{
		U4	u4Data;										/* 32-bit Access		  */
		struct											/* Bit Access			  */
		{
			U4	xDummy1					:1;				/* Reserved Bits		  */
			U4	xCLRO					:1;				/* CLRO					  */
			U4	b30Dummy2				:30;			/* Reserved Bits		  */
		} stBit;
	} unPEGOVFCLR;

	union												/* PEGOVFSTAT OFFSET 0x04 */
	{
		U4	u4Data;										/* 32-bit Access		  */
		struct											/* Bit Access			  */
		{
			U4	xDummy1					:1;				/* Reserved Bits		  */
			U4	xOVF					:1;				/* OVF					  */
			U4	b30Dummy2				:30;			/* Reserved Bits		  */
		} stBit;
	} unPEGOVFSTAT;

	U4	u4PEGERRADDR;									/* PEGERRADDR OFFSET 0x08 */

	union												/* PEGERRTYPE OFFSET 0x0C */
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
	} unPEGERRTYPE;

	U4	u4PEGSPIDERRCLR;								/* PEGSPIDERRCLR OFFSET 0x10 */

	U4	u4PEGSPIDERRSTAT;								/* PEGSPIDERRSTAT OFFSET 0x14 */

} Reg_Peg_PegcapType;



/*----------------------------------------------------------------------------------------------*/
/*	register BIT definition																		*/
/*----------------------------------------------------------------------------------------------*/
/* PEGKCPROT */
#define		PEG_PEGKCPROT_KCPROT				(BIT31+BIT30+BIT29+BIT28+BIT27+BIT26+BIT25+BIT24+BIT23+BIT22+BIT21+BIT20+BIT19+BIT18+BIT17+BIT16+BIT15+BIT14+BIT13+BIT12+BIT11+BIT10+BIT9+BIT8+BIT7+BIT6+BIT5+BIT4+BIT3+BIT2+BIT1)
#define		PEG_PEGKCPROT_KCPROT_0				(BIT1)
#define		PEG_PEGKCPROT_KCE					(BIT0)
	#define		PEG_PEGKCPROT_KCE_DISABLE		(0xA5A5A500U)
	#define		PEG_PEGKCPROT_KCE_ENABLE		(0xA5A5A501U)

/* PEGPROTm */
#define		PEG_PEGPROT_GEN						(BIT8)
	#define		PEG_PEGPROT_GEN_DISABLE			(0)
	#define		PEG_PEGPROT_GEN_ENABLE			(1)
#define		PEG_PEGPROT_DBG						(BIT6)
	#define		PEG_PEGPROT_DBG_OTHER			(0)
	#define		PEG_PEGPROT_DBG_ENABLE			(1)
#define		PEG_PEGPROT_UM						(BIT4)
	#define		PEG_PEGPROT_UM_DISABLE			(0)
	#define		PEG_PEGPROT_UM_OTHER			(1)
#define		PEG_PEGPROT_WG						(BIT1)
	#define		PEG_PEGPROT_WG_USE				(0)
	#define		PEG_PEGPROT_WG_NOUSE			(1)
#define		PEG_PEGPROT_RG						(BIT0)
	#define		PEG_PEGPROT_RG_USE				(0)
	#define		PEG_PEGPROT_RG_NOUSE			(1)

/* PEGSPIDm */

/* PEGBADm */
#define		PEG_PEGBAD_BAD						(BIT25+BIT24+BIT23+BIT22+BIT21+BIT20+BIT19+BIT18+BIT17+BIT16+BIT15+BIT14+BIT13+BIT12)
#define		PEG_PEGBAD_BAD_0					(BIT12)

/* PEGADVm */
#define		PEG_PEGADV_ADV						(BIT25+BIT24+BIT23+BIT22+BIT21+BIT20+BIT19+BIT18+BIT17+BIT16+BIT15+BIT14+BIT13+BIT12)
#define		PEG_PEGADV_ADV_0					(BIT12)

/* PEGOVFCLR */
#define		PEG_PEGOVFCLR_CLRO					(BIT1)
	#define		PEG_PEGOVFCLR_CLRO_CLEAR		(1)

/* PEGOVFSTAT */
#define		PEG_PEGOVFSTAT_OVF					(BIT1)
	#define		PEG_PEGOVFSTAT_OVF_CLEAR		(0)

/* PEGERRADDR */

/* PEGERRTYPE */
#define		PEG_PEGERRTYPE_SEC					(BIT13)
#define		PEG_PEGERRTYPE_DBG					(BIT12)
#define		PEG_PEGERRTYPE_UM					(BIT11)
#define		PEG_PEGERRTYPE_SPID					(BIT10+BIT9+BIT8+BIT7+BIT6)
#define		PEG_PEGERRTYPE_SPID_0				(BIT6)
#define		PEG_PEGERRTYPE_WRITE				(BIT0)

/* PEGSPIDERRCLR */

/* PEGSPIDERRSTAT */



/*----------------------------------------------------------------------------------------------*/
/*	struct address definition																	*/
/*----------------------------------------------------------------------------------------------*/
#define		Reg_PEG_GUARDPE0CL0		(*(volatile Reg_Peg_GuardpeclType *)(0xFFC6C000U))
#define		Reg_PEG_GUARDPE1CL0		(*(volatile Reg_Peg_GuardpeclType *)(0xFFC6C100U))
#define		Reg_PEG_GUARDPE2CL1		(*(volatile Reg_Peg_GuardpeclType *)(0xFFC6C200U))
#define		Reg_PEG_GUARDPE3CL1		(*(volatile Reg_Peg_GuardpeclType *)(0xFFC6C300U))
#define		Reg_PEG_GUARDPE4CL2		(*(volatile Reg_Peg_GuardpeclType *)(0xFFC6C400U))
#define		Reg_PEG_GUARDPE5CL2		(*(volatile Reg_Peg_GuardpeclType *)(0xFFC6C500U))
#define		Reg_PEG_PEGCAPMPE0CL0	(*(volatile Reg_Peg_PegcapType	 *)(0xFFC6C800U))
#define		Reg_PEG_PEGCAPSPE0CL0	(*(volatile Reg_Peg_PegcapType	 *)(0xFFC6C820U))
#define		Reg_PEG_PEGCAPMPE1CL0	(*(volatile Reg_Peg_PegcapType	 *)(0xFFC6C840U))
#define		Reg_PEG_PEGCAPSPE1CL0	(*(volatile Reg_Peg_PegcapType	 *)(0xFFC6C860U))
#define		Reg_PEG_PEGCAPMPE2CL1	(*(volatile Reg_Peg_PegcapType	 *)(0xFFC6C880U))
#define		Reg_PEG_PEGCAPSPE2CL1	(*(volatile Reg_Peg_PegcapType	 *)(0xFFC6C8A0U))
#define		Reg_PEG_PEGCAPMPE3CL1	(*(volatile Reg_Peg_PegcapType	 *)(0xFFC6C8C0U))
#define		Reg_PEG_PEGCAPSPE3CL1	(*(volatile Reg_Peg_PegcapType	 *)(0xFFC6C8E0U))
#define		Reg_PEG_PEGCAPMPE4CL2	(*(volatile Reg_Peg_PegcapType	 *)(0xFFC6C900U))
#define		Reg_PEG_PEGCAPSPE4CL2	(*(volatile Reg_Peg_PegcapType	 *)(0xFFC6C920U))
#define		Reg_PEG_PEGCAPMPE5CL2	(*(volatile Reg_Peg_PegcapType	 *)(0xFFC6C940U))
#define		Reg_PEG_PEGCAPSPE5CL2	(*(volatile Reg_Peg_PegcapType	 *)(0xFFC6C960U))



#endif /* REG_PEG_H */

#endif // zantei MPUÇÕ2åéññîÒëŒâû

/*-- End Of File -------------------------------------------------------------------------------*/
