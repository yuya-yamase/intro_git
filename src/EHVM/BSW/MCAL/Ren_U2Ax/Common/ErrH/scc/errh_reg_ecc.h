/* reg_ecc-r04-3000-0000-a-v04 */
/************************************************************************************************/
/*																								*/
/*		ECC register definition (for RH850U2B)													*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

#if 0 // zantei ECCは2月末非対応

#ifndef REG_ECC_H
#define REG_ECC_H

/*==============================================================================================*/
/* include files																				*/
/*==============================================================================================*/
#include	"ErrH_mcu_def.h"

/*==============================================================================================*/
/*	defines																						*/
/*==============================================================================================*/
#define		ECC_BUFFNUM_CF				(16)			/* Code Flash 1bitエラーキャプチャ バッファ数 */
#define		ECC_BUFFNUM_DF				(4)				/* Data Flash 1bitエラーキャプチャ バッファ数 */
#define		ECC_BUFFNUM_LRAM			(8)				/* Local RAM 1bitエラーキャプチャ バッファ数 */
#define		ECC_BUFFNUM_CRAM			(8)				/* Cluster RAM 1bitエラーキャプチャ バッファ数 */

#define		ECC7_CHANNEL_NUM			(47)			/* Peripheral RAM (32 Bits) チャネル数 */
#define		ECC6_CHANNEL_NUM			(4)				/* Peripheral RAM (16 Bits) チャネル数 */
#if ( MCU_TYPE_SERIES == MCU_RH850U2B6 )
#define		A_CHANNEL_NUM				(28)			/* Data Transfer Path  BUSA チャネル数 */
#elif ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_DUALCORE ) )		/* U2B10 and 2Core */
#define		A_CHANNEL_NUM				(32)			/* Data Transfer Path  BUSA チャネル数 */
#else /* U2B10 and more than 2Core */
#define		A_CHANNEL_NUM				(35)			/* Data Transfer Path  BUSA チャネル数 */
#endif
#define		V2ANW_CHANNEL_NUM			(11)			/* Data Transfer Path  V2ANW チャネル数 */
#define		PBNECC_CHANNEL_NUM			(11)			/* Data Transfer Path  PBNECC チャネル数 */
#if ( MCU_TYPE_SERIES == MCU_RH850U2B6 )
#define		HBNECC_CHANNEL_NUM			(7)				/* Data Transfer Path  HBNECC チャネル数 */
#elif ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
#define		HBNECC_CHANNEL_NUM			(7)				/* Data Transfer Path  HBNECC チャネル数 */
#else
    #error "MCU_TYPE_SERIES is not supported"
#endif
#define		V2AN_CHANNEL_NUM			(11)			/* Data Transfer Path  V2AN チャネル数 */

/*==============================================================================================*/
/*	register type definition																	*/
/*==============================================================================================*/

/* ECCKC */
/* ============================================================================ */
/* ============================ Module: ECCKC ================================= */
/* ============================================================================ */
typedef	struct											/* ECCKC */
{
	union												/* KCPROT */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xKCE					:1;				/* KCE */
			U4	b31KCPROT				:31;			/* KCPROT[31:1] */
		} stBit;
	} unKCPROT;											/* 0xFFFB2800 - 0xFFFB2804 */

}	Reg_Ecc_EccKcType;


/* ECCCNT_CFP_PE0CL0 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_CFP_PE0CL0 ===================== */
/* ============================================================================ */
typedef	struct											/* ECCCNT_CFP_PE0CL0 */
{
	union												/* CFPECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	b30Dummy1				:30;
		} stBit;
	} unCFPECCCTL;										/* 0xFFC48000 - 0xFFC48004 */

}	Reg_Ecc_EccCnt_Cfp_Pe0Cl0Type;


/* ECCCNT_CFP_PE1CL0 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_CFP_PE1CL0 ===================== */
/* ============================================================================ */
typedef	struct											/* ECCCNT_CFP_PE1CL0 */
{
	union												/* CFPECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	b30Dummy1				:30;
		} stBit;
	} unCFPECCCTL;										/* 0xFFC48080 - 0xFFC48084 */

}	Reg_Ecc_EccCnt_Cfp_Pe1Cl0Type;


/* ECCCNT_CFP_PE2CL1 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_CFP_PE2CL1 ===================== */
/* ============================================================================ */
typedef	struct											/* ECCCNT_CFP_PE2CL1 */
{
	union												/* CFPECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	b30Dummy1				:30;
		} stBit;
	} unCFPECCCTL;										/* 0xFFC48100 - 0xFFC48104 */

}	Reg_Ecc_EccCnt_Cfp_Pe2Cl1Type;


/* ECCCNT_CFP_PE3CL1 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_CFP_PE3CL1 ===================== */
/* ============================================================================ */
typedef	struct											/* ECCCNT_CFP_PE3CL1 */
{
	union												/* CFPECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	b30Dummy1				:30;
		} stBit;
	} unCFPECCCTL;										/* 0xFFC48180 - 0xFFC48184 */

}	Reg_Ecc_EccCnt_Cfp_Pe3Cl1Type;


/* ECCCNT_CFP_PE4CL2 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_CFP_PE4CL2 ===================== */
/* ============================================================================ */
typedef	struct											/* ECCCNT_CFP_PE4CL2 */
{
	union												/* CFPECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	b30Dummy1				:30;
		} stBit;
	} unCFPECCCTL;										/* 0xFFC48200 - 0xFFC48204 */

}	Reg_Ecc_EccCnt_Cfp_Pe4Cl2Type;


/* ECCCNT_CFP_PE5CL2 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_CFP_PE5CL2 ===================== */
/* ============================================================================ */
typedef	struct											/* ECCCNT_CFP_PE5CL2 */
{
	union												/* CFPECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	b30Dummy1				:30;
		} stBit;
	} unCFPECCCTL;										/* 0xFFC48280 - 0xFFC48284 */

}	Reg_Ecc_EccCnt_Cfp_Pe5Cl2Type;


/* ECCCNT_CFCCL0 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_CFCCL0 ========================= */
/* ============================================================================ */
typedef	struct											/* ECCCNT_CFCCL0 */
{
	union												/* CFCECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	xAPEDIS					:1;				/* APEDIS */
			U4	b21Dummy1				:21;
			U4	xBLANKMASKENABLE		:1;				/* BLANKMASKENABLE */
			U4	b7Dummy2				:7;
		} stBit;
	} unCFCECCCTL;										/* 0xFFC48800 - 0xFFC48804 */

}	Reg_Ecc_EccCnt_Cfccl0Type;


/* ECCCNT_CFCCL1 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_CFCCL1 ========================= */
/* ============================================================================ */
typedef	struct											/* ECCCNT_CFCCL1 */
{
	union												/* CFCECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	xAPEDIS					:1;				/* APEDIS */
			U4	b21Dummy1				:21;
			U4	xBLANKMASKENABLE		:1;				/* BLANKMASKENABLE */
			U4	b7Dummy2				:7;
		} stBit;
	} unCFCECCCTL;										/* 0xFFC48880 - 0xFFC48884 */

}	Reg_Ecc_EccCnt_Cfccl1Type;


/* ECCCNT_CFCCL2 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_CFCCL2 ========================= */
/* ============================================================================ */
typedef	struct											/* ECCCNT_CFCCL2 */
{
	union												/* CFCECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	xAPEDIS					:1;				/* APEDIS */
			U4	b21Dummy1				:21;
			U4	xBLANKMASKENABLE		:1;				/* BLANKMASKENABLE */
			U4	b7Dummy2				:7;
		} stBit;
	} unCFCECCCTL;										/* 0xFFC48900 - 0xFFC48904 */

}	Reg_Ecc_EccCnt_Cfccl2Type;


/* ECCCNT_CFS */
/* ============================================================================ */
/* ============================ Module: ECCCNT_CFS ============================ */
/* ============================================================================ */
typedef	struct											/* ECCCNT_CFS */
{
	union												/* CFSECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	b30Dummy1				:30;
		} stBit;
	} unCFSECCCTL;										/* 0xFFC48A00 - 0xFFC48A04 */

}	Reg_Ecc_EccCnt_CfsType;


/* MECCCAP_CFL */
/* ============================================================================ */
/* ============================ Module: MECCCAP_CFL =========================== */
/* ============================================================================ */
typedef	struct											/* MECCCAP_CFL */
{
	union												/* CF_ERRINT */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDIE					:1;				/* SEDIE */
			U4	xDEDIE					:1;				/* DEDIE */
			U4	xAPEIE					:1;				/* APEIE */
			U4	b4Dummy1				:4;
			U4	xSEOVFIE				:1;				/* SEOVFIE */
			U4	b24Dummy2				:24;
		} stBit;
	} unCF_ERRINT;										/* 0xFFC55400 - 0xFFC55404 */

	U1	u1Dummy1[0xFFC55410U - 0xFFC55404U];			/* 0xFFC55404 - 0xFFC55410 */

	union												/* CF_SSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSSTCLR00				:1;				/* SSTCLR00 */
			U4	xSSTCLR01				:1;				/* SSTCLR01 */
			U4	xSSTCLR02				:1;				/* SSTCLR02 */
			U4	xSSTCLR03				:1;				/* SSTCLR03 */
			U4	xSSTCLR04				:1;				/* SSTCLR04 */
			U4	xSSTCLR05				:1;				/* SSTCLR05 */
			U4	xSSTCLR06				:1;				/* SSTCLR06 */
			U4	xSSTCLR07				:1;				/* SSTCLR07 */
			U4	xSSTCLR08				:1;				/* SSTCLR08 */
			U4	xSSTCLR09				:1;				/* SSTCLR09 */
			U4	xSSTCLR10				:1;				/* SSTCLR10 */
			U4	xSSTCLR11				:1;				/* SSTCLR11 */
			U4	xSSTCLR12				:1;				/* SSTCLR12 */
			U4	xSSTCLR13				:1;				/* SSTCLR13 */
			U4	xSSTCLR14				:1;				/* SSTCLR14 */
			U4	xSSTCLR15				:1;				/* SSTCLR15 */
			U4	b16Dummy1				:16;
		} stBit;
	} unCF_SSTCLR;										/* 0xFFC55410 - 0xFFC55414 */

	union												/* CF_DSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDSTCLR00				:1;				/* DSTCLR00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unCF_DSTCLR;										/* 0xFFC55414 - 0xFFC55418 */

	union												/* CF_OVFCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSERROVFCLR0			:1;				/* SERROVFCLR0 */
			U4	xSERROVFCLR1			:1;				/* SERROVFCLR1 */
			U4	b30Dummy1				:30;
		} stBit;
	} unCF_OVFCLR;										/* 0xFFC55418 - 0xFFC5541C */

	U1	u1Dummy2[0xFFC55420U - 0xFFC5541CU];			/* 0xFFC5541C - 0xFFC55420 */

	union												/* CF_SERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDF00					:1;				/* SEDF00 */
			U4	xSEDF01					:1;				/* SEDF01 */
			U4	xSEDF02					:1;				/* SEDF02 */
			U4	xSEDF03					:1;				/* SEDF03 */
			U4	xSEDF04					:1;				/* SEDF04 */
			U4	xSEDF05					:1;				/* SEDF05 */
			U4	xSEDF06					:1;				/* SEDF06 */
			U4	xSEDF07					:1;				/* SEDF07 */
			U4	xSEDF08					:1;				/* SEDF08 */
			U4	xSEDF09					:1;				/* SEDF09 */
			U4	xSEDF10					:1;				/* SEDF10 */
			U4	xSEDF11					:1;				/* SEDF11 */
			U4	xSEDF12					:1;				/* SEDF12 */
			U4	xSEDF13					:1;				/* SEDF13 */
			U4	xSEDF14					:1;				/* SEDF14 */
			U4	xSEDF15					:1;				/* SEDF15 */
			U4	b16Dummy1				:16;
		} stBit;
	} unCF_SERSTR;										/* 0xFFC55420 - 0xFFC55424 */

	union												/* CF_DERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDummy1					:1;
			U4	xDEDF00					:1;				/* DEDF00 */
			U4	xAPEF00					:1;				/* APEF00 */
			U4	b29Dummy2				:29;
		} stBit;
	} unCF_DERSTR;										/* 0xFFC55424 - 0xFFC55428 */

	union												/* CF_OVFSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSERROVF0				:1;				/* SERROVF0 */
			U4	xSERROVF1				:1;				/* SERROVF1 */
			U4	b30Dummy1				:30;
		} stBit;
	} unCF_OVFSTR;										/* 0xFFC55428 - 0xFFC5542C */

	U1	u1Dummy3[0xFFC55430U - 0xFFC5542CU];			/* 0xFFC5542C - 0xFFC55430 */

	union												/* CF_SERINF */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDLINF00				:1;				/* SEDLINF00 */
			U4	xSEDLINF01				:1;				/* SEDLINF01 */
			U4	xSEDLINF02				:1;				/* SEDLINF02 */
			U4	xSEDLINF03				:1;				/* SEDLINF03 */
			U4	xSEDLINF04				:1;				/* SEDLINF04 */
			U4	xSEDLINF05				:1;				/* SEDLINF05 */
			U4	xSEDLINF06				:1;				/* SEDLINF06 */
			U4	xSEDLINF07				:1;				/* SEDLINF07 */
			U4	xSEDLINF08				:1;				/* SEDLINF08 */
			U4	xSEDLINF09				:1;				/* SEDLINF09 */
			U4	xSEDLINF10				:1;				/* SEDLINF10 */
			U4	xSEDLINF11				:1;				/* SEDLINF11 */
			U4	b4Dummy1				:4;
			U4	xSEDLINF16				:1;				/* SEDLINF16 */
			U4	xSEDLINF17				:1;				/* SEDLINF17 */
			U4	b14Dummy2				:14;
		} stBit;
	} unCF_SERINF;										/* 0xFFC55430 - 0xFFC55434 */

	U1	u1Dummy4[0xFFC55470U - 0xFFC55434U];			/* 0xFFC55434 - 0xFFC55470 */

	union												/* CF_00SEADR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b2Dummy1				:2;
			U4	b24SEADR0				:24;			/* SEADR0[25:2] */
			U4	xDummy2					:1;
			U4	b5SEDL					:5;				/* SEDL[4:0] */
		} stBit;
	} unCF_nSEADR[ECC_BUFFNUM_CF];						/* 0xFFC55470 - 0xFFC554B0 */

	U1	u1Dummy5[0xFFC554F0U - 0xFFC554B0U];			/* 0xFFC554B0 - 0xFFC554F0 */

	union												/* CF_00DEADR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b2Dummy1				:2;
			U4	b24DEADR0				:24;			/* DEADR0[25:2] */
			U4	xDummy2					:1;
			U4	b5DEDL					:5;				/* DEDL[4:0] */
		} stBit;
	} unCF_00DEADR;										/* 0xFFC554F0 - 0xFFC554F4 */

	union												/* CF_00DESPIDCLR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDESPIDCLR0				:1;				/* DESPIDCLR0 */
			U4	xDESPIDCLR1				:1;				/* DESPIDCLR1 */
			U4	xDESPIDCLR2				:1;				/* DESPIDCLR2 */
			U4	xDESPIDCLR3				:1;				/* DESPIDCLR3 */
			U4	xDESPIDCLR4				:1;				/* DESPIDCLR4 */
			U4	xDESPIDCLR5				:1;				/* DESPIDCLR5 */
			U4	xDESPIDCLR6				:1;				/* DESPIDCLR6 */
			U4	xDESPIDCLR7				:1;				/* DESPIDCLR7 */
			U4	xDESPIDCLR8				:1;				/* DESPIDCLR8 */
			U4	xDESPIDCLR9				:1;				/* DESPIDCLR9 */
			U4	xDESPIDCLR10			:1;				/* DESPIDCLR10 */
			U4	xDESPIDCLR11			:1;				/* DESPIDCLR11 */
			U4	xDESPIDCLR12			:1;				/* DESPIDCLR12 */
			U4	xDESPIDCLR13			:1;				/* DESPIDCLR13 */
			U4	xDESPIDCLR14			:1;				/* DESPIDCLR14 */
			U4	xDESPIDCLR15			:1;				/* DESPIDCLR15 */
			U4	xDESPIDCLR16			:1;				/* DESPIDCLR16 */
			U4	xDESPIDCLR17			:1;				/* DESPIDCLR17 */
			U4	xDESPIDCLR18			:1;				/* DESPIDCLR18 */
			U4	xDESPIDCLR19			:1;				/* DESPIDCLR19 */
			U4	xDESPIDCLR20			:1;				/* DESPIDCLR20 */
			U4	xDESPIDCLR21			:1;				/* DESPIDCLR21 */
			U4	xDESPIDCLR22			:1;				/* DESPIDCLR22 */
			U4	xDESPIDCLR23			:1;				/* DESPIDCLR23 */
			U4	xDESPIDCLR24			:1;				/* DESPIDCLR24 */
			U4	xDESPIDCLR25			:1;				/* DESPIDCLR25 */
			U4	xDESPIDCLR26			:1;				/* DESPIDCLR26 */
			U4	xDESPIDCLR27			:1;				/* DESPIDCLR27 */
			U4	xDESPIDCLR28			:1;				/* DESPIDCLR28 */
			U4	xDESPIDCLR29			:1;				/* DESPIDCLR29 */
			U4	xDESPIDCLR30			:1;				/* DESPIDCLR30 */
			U4	xDESPIDCLR31			:1;				/* DESPIDCLR31 */
		} stBit;
	} unCF_00DESPIDCLR;									/* 0xFFC554F4 - 0xFFC554F8 */

	union												/* CF_00DESPID */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDESPID0				:1;				/* DESPID0 */
			U4	xDESPID1				:1;				/* DESPID1 */
			U4	xDESPID2				:1;				/* DESPID2 */
			U4	xDESPID3				:1;				/* DESPID3 */
			U4	xDESPID4				:1;				/* DESPID4 */
			U4	xDESPID5				:1;				/* DESPID5 */
			U4	xDESPID6				:1;				/* DESPID6 */
			U4	xDESPID7				:1;				/* DESPID7 */
			U4	xDESPID8				:1;				/* DESPID8 */
			U4	xDESPID9				:1;				/* DESPID9 */
			U4	xDESPID10				:1;				/* DESPID10 */
			U4	xDESPID11				:1;				/* DESPID11 */
			U4	xDESPID12				:1;				/* DESPID12 */
			U4	xDESPID13				:1;				/* DESPID13 */
			U4	xDESPID14				:1;				/* DESPID14 */
			U4	xDESPID15				:1;				/* DESPID15 */
			U4	xDESPID16				:1;				/* DESPID16 */
			U4	xDESPID17				:1;				/* DESPID17 */
			U4	xDESPID18				:1;				/* DESPID18 */
			U4	xDESPID19				:1;				/* DESPID19 */
			U4	xDESPID20				:1;				/* DESPID20 */
			U4	xDESPID21				:1;				/* DESPID21 */
			U4	xDESPID22				:1;				/* DESPID22 */
			U4	xDESPID23				:1;				/* DESPID23 */
			U4	xDESPID24				:1;				/* DESPID24 */
			U4	xDESPID25				:1;				/* DESPID25 */
			U4	xDESPID26				:1;				/* DESPID26 */
			U4	xDESPID27				:1;				/* DESPID27 */
			U4	xDESPID28				:1;				/* DESPID28 */
			U4	xDESPID29				:1;				/* DESPID29 */
			U4	xDESPID30				:1;				/* DESPID30 */
			U4	xDESPID31				:1;				/* DESPID31 */
		} stBit;
	} unCF_00DESPID;									/* 0xFFC554F8 - 0xFFC554FC */

	U1	u1Dummy6[0xFFC55500U - 0xFFC554FCU];			/* 0xFFC554FC - 0xFFC55500 */

	union												/* CF_nSESPIDCLR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSESPIDCLR0				:1;				/* SESPIDCLR0 */
			U4	xSESPIDCLR1				:1;				/* SESPIDCLR1 */
			U4	xSESPIDCLR2				:1;				/* SESPIDCLR2 */
			U4	xSESPIDCLR3				:1;				/* SESPIDCLR3 */
			U4	xSESPIDCLR4				:1;				/* SESPIDCLR4 */
			U4	xSESPIDCLR5				:1;				/* SESPIDCLR5 */
			U4	xSESPIDCLR6				:1;				/* SESPIDCLR6 */
			U4	xSESPIDCLR7				:1;				/* SESPIDCLR7 */
			U4	xSESPIDCLR8				:1;				/* SESPIDCLR8 */
			U4	xSESPIDCLR9				:1;				/* SESPIDCLR9 */
			U4	xSESPIDCLR10			:1;				/* SESPIDCLR10 */
			U4	xSESPIDCLR11			:1;				/* SESPIDCLR11 */
			U4	xSESPIDCLR12			:1;				/* SESPIDCLR12 */
			U4	xSESPIDCLR13			:1;				/* SESPIDCLR13 */
			U4	xSESPIDCLR14			:1;				/* SESPIDCLR14 */
			U4	xSESPIDCLR15			:1;				/* SESPIDCLR15 */
			U4	xSESPIDCLR16			:1;				/* SESPIDCLR16 */
			U4	xSESPIDCLR17			:1;				/* SESPIDCLR17 */
			U4	xSESPIDCLR18			:1;				/* SESPIDCLR18 */
			U4	xSESPIDCLR19			:1;				/* SESPIDCLR19 */
			U4	xSESPIDCLR20			:1;				/* SESPIDCLR20 */
			U4	xSESPIDCLR21			:1;				/* SESPIDCLR21 */
			U4	xSESPIDCLR22			:1;				/* SESPIDCLR22 */
			U4	xSESPIDCLR23			:1;				/* SESPIDCLR23 */
			U4	xSESPIDCLR24			:1;				/* SESPIDCLR24 */
			U4	xSESPIDCLR25			:1;				/* SESPIDCLR25 */
			U4	xSESPIDCLR26			:1;				/* SESPIDCLR26 */
			U4	xSESPIDCLR27			:1;				/* SESPIDCLR27 */
			U4	xSESPIDCLR28			:1;				/* SESPIDCLR28 */
			U4	xSESPIDCLR29			:1;				/* SESPIDCLR29 */
			U4	xSESPIDCLR30			:1;				/* SESPIDCLR30 */
			U4	xSESPIDCLR31			:1;				/* SESPIDCLR31 */
		} stBit;
	} unCF_nSESPIDCLR[ECC_BUFFNUM_CF];					/* 0xFFC55500 - 0xFFC55540 */

	U1	u1Dummy7[0xFFC55580U - 0xFFC55540U];			/* 0xFFC55540 - 0xFFC55580 */

	union												/* CF_nSESPID */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSESPID0				:1;				/* SESPID0 */
			U4	xSESPID1				:1;				/* SESPID1 */
			U4	xSESPID2				:1;				/* SESPID2 */
			U4	xSESPID3				:1;				/* SESPID3 */
			U4	xSESPID4				:1;				/* SESPID4 */
			U4	xSESPID5				:1;				/* SESPID5 */
			U4	xSESPID6				:1;				/* SESPID6 */
			U4	xSESPID7				:1;				/* SESPID7 */
			U4	xSESPID8				:1;				/* SESPID8 */
			U4	xSESPID9				:1;				/* SESPID9 */
			U4	xSESPID10				:1;				/* SESPID10 */
			U4	xSESPID11				:1;				/* SESPID11 */
			U4	xSESPID12				:1;				/* SESPID12 */
			U4	xSESPID13				:1;				/* SESPID13 */
			U4	xSESPID14				:1;				/* SESPID14 */
			U4	xSESPID15				:1;				/* SESPID15 */
			U4	xSESPID16				:1;				/* SESPID16 */
			U4	xSESPID17				:1;				/* SESPID17 */
			U4	xSESPID18				:1;				/* SESPID18 */
			U4	xSESPID19				:1;				/* SESPID19 */
			U4	xSESPID20				:1;				/* SESPID20 */
			U4	xSESPID21				:1;				/* SESPID21 */
			U4	xSESPID22				:1;				/* SESPID22 */
			U4	xSESPID23				:1;				/* SESPID23 */
			U4	xSESPID24				:1;				/* SESPID24 */
			U4	xSESPID25				:1;				/* SESPID25 */
			U4	xSESPID26				:1;				/* SESPID26 */
			U4	xSESPID27				:1;				/* SESPID27 */
			U4	xSESPID28				:1;				/* SESPID28 */
			U4	xSESPID29				:1;				/* SESPID29 */
			U4	xSESPID30				:1;				/* SESPID30 */
			U4	xSESPID31				:1;				/* SESPID31 */
		} stBit;
	} unCF_nSESPID[ECC_BUFFNUM_CF];						/* 0xFFC55580 - 0xFFC555C0 */

}	Reg_Ecc_MeccCap_CflType;


/* ECCDF */
/* ============================================================================ */
/* ============================ Module: ECCDF ================================= */
/* ============================================================================ */
typedef	struct											/* ECCDF */
{
	union												/* DFECCCTL */
	{
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	b30Dummy1				:30;
		} stBit;
	} unDFECCCTL;										/* 0xFFC62C00 - 0xFFC62C04 */

	union												/* DFSERSTR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDF0					:1;				/* SEDF0 */
			U4	xSEDF1					:1;				/* SEDF1 */
			U4	xSEDF2					:1;				/* SEDF2 */
			U4	xSEDF3					:1;				/* SEDF3 */
			U4	b28Dummy1				:28;
		} stBit;
	} unDFSERSTR;										/* 0xFFC62C04 - 0xFFC62C08 */

	union												/* DFDERSTR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDEDF					:1;				/* DEDF */
			U4	b31Dummy1				:31;
		} stBit;
	} unDFDERSTR;										/* 0xFFC62C08 - 0xFFC62C0C*/

	union												/* DFSERSTC */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSSTCLR0				:1;				/* SSTCLR0 */
			U4	xSSTCLR1				:1;				/* SSTCLR1 */
			U4	xSSTCLR2				:1;				/* SSTCLR2 */
			U4	xSSTCLR3				:1;				/* SSTCLR3 */
			U4	b28Dummy1				:28;
		} stBit;
	} unDFSERSTC;										/* 0xFFC62C0C - 0xFFC62C10 */

	union												/* DFDERSTC */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDSTCLR					:1;				/* DSTCLR */
			U4	b31Dummy1				:31;
		} stBit;
	} unDFDERSTC;										/* 0xFFC62C10 - 0xFFC62C14 */

	union												/* DFOVFSTR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xERROVF					:1;				/* ERROVF */
			U4	b31Dummy1				:31;
		} stBit;
	} unDFOVFSTR;										/* 0xFFC62C14 - 0xFFC62C18 */

	union												/* DFOVFSTC */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xERROVFCLR				:1;				/* ERROVFCLR */
			U4	b31Dummy1				:31;
		} stBit;
	} unDFOVFSTC;										/* 0xFFC62C18 - 0xFFC62C1C */

	union												/* DFERRINT */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDIE					:1;				/* SEDIE */
			U4	xDEDIE					:1;				/* DEDIE */
			U4	xSEOVFIE				:1;				/* SEOVFIE */
			U4	b29Dummy1				:29;
		} stBit;
	} unDFERRINT;										/* 0xFFC62C1C - 0xFFC62C20 */

	union												/* DFSEADRn */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b2Dummy1				:2;
			U4	b19DFSEADR				:19;			/* DFSEADR[20:2] */
			U4	b11Dummy2				:11;
		} stBit;
	} unDFSEADRn[ECC_BUFFNUM_DF];						/* 0xFFC62C20 - 0xFFC62C30 */

	U1	u1Dummy1[0xFFC62C60U - 0xFFC62C30U];			/* 0xFFC62C30 - 0xFFC62C60 */

	union												/* DFDEADR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b2Dummy1				:2;
			U4	b19DFEADR				:19;			/* DFDEADR[20:2] */
			U4	b11Dummy2				:11;
		} stBit;
	} unDFDEADR;										/* 0xFFC62C60 - 0xFFC62C64 */

	U1	u1Dummy2[0xFFC62C70U - 0xFFC62C64U];			/* 0xFFC62C64 - 0xFFC62C70 */

	union												/* DFSESPID0 */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSESPID0				:1;				/* SESPID0 */
			U4	xSESPID1				:1;				/* SESPID1 */
			U4	xSESPID2				:1;				/* SESPID2 */
			U4	xSESPID3				:1;				/* SESPID3 */
			U4	xSESPID4				:1;				/* SESPID4 */
			U4	xSESPID5				:1;				/* SESPID5 */
			U4	xSESPID6				:1;				/* SESPID6 */
			U4	xSESPID7				:1;				/* SESPID7 */
			U4	xSESPID8				:1;				/* SESPID8 */
			U4	xSESPID9				:1;				/* SESPID9 */
			U4	xSESPID10				:1;				/* SESPID10 */
			U4	xSESPID11				:1;				/* SESPID11 */
			U4	xSESPID12				:1;				/* SESPID12 */
			U4	xSESPID13				:1;				/* SESPID13 */
			U4	xSESPID14				:1;				/* SESPID14 */
			U4	xSESPID15				:1;				/* SESPID15 */
			U4	xSESPID16				:1;				/* SESPID16 */
			U4	xSESPID17				:1;				/* SESPID17 */
			U4	xSESPID18				:1;				/* SESPID18 */
			U4	xSESPID19				:1;				/* SESPID19 */
			U4	xSESPID20				:1;				/* SESPID20 */
			U4	xSESPID21				:1;				/* SESPID21 */
			U4	xSESPID22				:1;				/* SESPID22 */
			U4	xSESPID23				:1;				/* SESPID23 */
			U4	xSESPID24				:1;				/* SESPID24 */
			U4	xSESPID25				:1;				/* SESPID25 */
			U4	xSESPID26				:1;				/* SESPID26 */
			U4	xSESPID27				:1;				/* SESPID27 */
			U4	xSESPID28				:1;				/* SESPID28 */
			U4	xSESPID29				:1;				/* SESPID29 */
			U4	xSESPID30				:1;				/* SESPID30 */
			U4	xSESPID31				:1;				/* SESPID31 */
		} stBit;
	} unDFSESPID0;										/* 0xFFC62C70 - 0xFFC62C74 */

	union												/* DFSESPIDC0 */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSESPIDCLR0				:1;				/* SESPIDCLR0 */
			U4	xSESPIDCLR1				:1;				/* SESPIDCLR1 */
			U4	xSESPIDCLR2				:1;				/* SESPIDCLR2 */
			U4	xSESPIDCLR3				:1;				/* SESPIDCLR3 */
			U4	xSESPIDCLR4				:1;				/* SESPIDCLR4 */
			U4	xSESPIDCLR5				:1;				/* SESPIDCLR5 */
			U4	xSESPIDCLR6				:1;				/* SESPIDCLR6 */
			U4	xSESPIDCLR7				:1;				/* SESPIDCLR7 */
			U4	xSESPIDCLR8				:1;				/* SESPIDCLR8 */
			U4	xSESPIDCLR9				:1;				/* SESPIDCLR9 */
			U4	xSESPIDCLR10			:1;				/* SESPIDCLR10 */
			U4	xSESPIDCLR11			:1;				/* SESPIDCLR11 */
			U4	xSESPIDCLR12			:1;				/* SESPIDCLR12 */
			U4	xSESPIDCLR13			:1;				/* SESPIDCLR13 */
			U4	xSESPIDCLR14			:1;				/* SESPIDCLR14 */
			U4	xSESPIDCLR15			:1;				/* SESPIDCLR15 */
			U4	xSESPIDCLR16			:1;				/* SESPIDCLR16 */
			U4	xSESPIDCLR17			:1;				/* SESPIDCLR17 */
			U4	xSESPIDCLR18			:1;				/* SESPIDCLR18 */
			U4	xSESPIDCLR19			:1;				/* SESPIDCLR19 */
			U4	xSESPIDCLR20			:1;				/* SESPIDCLR20 */
			U4	xSESPIDCLR21			:1;				/* SESPIDCLR21 */
			U4	xSESPIDCLR22			:1;				/* SESPIDCLR22 */
			U4	xSESPIDCLR23			:1;				/* SESPIDCLR23 */
			U4	xSESPIDCLR24			:1;				/* SESPIDCLR24 */
			U4	xSESPIDCLR25			:1;				/* SESPIDCLR25 */
			U4	xSESPIDCLR26			:1;				/* SESPIDCLR26 */
			U4	xSESPIDCLR27			:1;				/* SESPIDCLR27 */
			U4	xSESPIDCLR28			:1;				/* SESPIDCLR28 */
			U4	xSESPIDCLR29			:1;				/* SESPIDCLR29 */
			U4	xSESPIDCLR30			:1;				/* SESPIDCLR30 */
			U4	xSESPIDCLR31			:1;				/* SESPIDCLR31 */
		} stBit;
	} unDFSESPIDC0;										/* 0xFFC62C74 - 0xFFC62C78 */

	union												/* DFSESPID1 */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSESPID0				:1;				/* SESPID0 */
			U4	xSESPID1				:1;				/* SESPID1 */
			U4	xSESPID2				:1;				/* SESPID2 */
			U4	xSESPID3				:1;				/* SESPID3 */
			U4	xSESPID4				:1;				/* SESPID4 */
			U4	xSESPID5				:1;				/* SESPID5 */
			U4	xSESPID6				:1;				/* SESPID6 */
			U4	xSESPID7				:1;				/* SESPID7 */
			U4	xSESPID8				:1;				/* SESPID8 */
			U4	xSESPID9				:1;				/* SESPID9 */
			U4	xSESPID10				:1;				/* SESPID10 */
			U4	xSESPID11				:1;				/* SESPID11 */
			U4	xSESPID12				:1;				/* SESPID12 */
			U4	xSESPID13				:1;				/* SESPID13 */
			U4	xSESPID14				:1;				/* SESPID14 */
			U4	xSESPID15				:1;				/* SESPID15 */
			U4	xSESPID16				:1;				/* SESPID16 */
			U4	xSESPID17				:1;				/* SESPID17 */
			U4	xSESPID18				:1;				/* SESPID18 */
			U4	xSESPID19				:1;				/* SESPID19 */
			U4	xSESPID20				:1;				/* SESPID20 */
			U4	xSESPID21				:1;				/* SESPID21 */
			U4	xSESPID22				:1;				/* SESPID22 */
			U4	xSESPID23				:1;				/* SESPID23 */
			U4	xSESPID24				:1;				/* SESPID24 */
			U4	xSESPID25				:1;				/* SESPID25 */
			U4	xSESPID26				:1;				/* SESPID26 */
			U4	xSESPID27				:1;				/* SESPID27 */
			U4	xSESPID28				:1;				/* SESPID28 */
			U4	xSESPID29				:1;				/* SESPID29 */
			U4	xSESPID30				:1;				/* SESPID30 */
			U4	xSESPID31				:1;				/* SESPID31 */
		} stBit;
	} unDFSESPID1;										/* 0xFFC62C78 - 0xFFC62C7C */

	union												/* DFSESPIDC1 */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSESPIDCLR0				:1;				/* SESPIDCLR0 */
			U4	xSESPIDCLR1				:1;				/* SESPIDCLR1 */
			U4	xSESPIDCLR2				:1;				/* SESPIDCLR2 */
			U4	xSESPIDCLR3				:1;				/* SESPIDCLR3 */
			U4	xSESPIDCLR4				:1;				/* SESPIDCLR4 */
			U4	xSESPIDCLR5				:1;				/* SESPIDCLR5 */
			U4	xSESPIDCLR6				:1;				/* SESPIDCLR6 */
			U4	xSESPIDCLR7				:1;				/* SESPIDCLR7 */
			U4	xSESPIDCLR8				:1;				/* SESPIDCLR8 */
			U4	xSESPIDCLR9				:1;				/* SESPIDCLR9 */
			U4	xSESPIDCLR10			:1;				/* SESPIDCLR10 */
			U4	xSESPIDCLR11			:1;				/* SESPIDCLR11 */
			U4	xSESPIDCLR12			:1;				/* SESPIDCLR12 */
			U4	xSESPIDCLR13			:1;				/* SESPIDCLR13 */
			U4	xSESPIDCLR14			:1;				/* SESPIDCLR14 */
			U4	xSESPIDCLR15			:1;				/* SESPIDCLR15 */
			U4	xSESPIDCLR16			:1;				/* SESPIDCLR16 */
			U4	xSESPIDCLR17			:1;				/* SESPIDCLR17 */
			U4	xSESPIDCLR18			:1;				/* SESPIDCLR18 */
			U4	xSESPIDCLR19			:1;				/* SESPIDCLR19 */
			U4	xSESPIDCLR20			:1;				/* SESPIDCLR20 */
			U4	xSESPIDCLR21			:1;				/* SESPIDCLR21 */
			U4	xSESPIDCLR22			:1;				/* SESPIDCLR22 */
			U4	xSESPIDCLR23			:1;				/* SESPIDCLR23 */
			U4	xSESPIDCLR24			:1;				/* SESPIDCLR24 */
			U4	xSESPIDCLR25			:1;				/* SESPIDCLR25 */
			U4	xSESPIDCLR26			:1;				/* SESPIDCLR26 */
			U4	xSESPIDCLR27			:1;				/* SESPIDCLR27 */
			U4	xSESPIDCLR28			:1;				/* SESPIDCLR28 */
			U4	xSESPIDCLR29			:1;				/* SESPIDCLR29 */
			U4	xSESPIDCLR30			:1;				/* SESPIDCLR30 */
			U4	xSESPIDCLR31			:1;				/* SESPIDCLR31 */
		} stBit;
	} unDFSESPIDC1;										/* 0xFFC62C7C - 0xFFC62C80 */

	union												/* DFSESPID2 */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSESPID0				:1;				/* SESPID0 */
			U4	xSESPID1				:1;				/* SESPID1 */
			U4	xSESPID2				:1;				/* SESPID2 */
			U4	xSESPID3				:1;				/* SESPID3 */
			U4	xSESPID4				:1;				/* SESPID4 */
			U4	xSESPID5				:1;				/* SESPID5 */
			U4	xSESPID6				:1;				/* SESPID6 */
			U4	xSESPID7				:1;				/* SESPID7 */
			U4	xSESPID8				:1;				/* SESPID8 */
			U4	xSESPID9				:1;				/* SESPID9 */
			U4	xSESPID10				:1;				/* SESPID10 */
			U4	xSESPID11				:1;				/* SESPID11 */
			U4	xSESPID12				:1;				/* SESPID12 */
			U4	xSESPID13				:1;				/* SESPID13 */
			U4	xSESPID14				:1;				/* SESPID14 */
			U4	xSESPID15				:1;				/* SESPID15 */
			U4	xSESPID16				:1;				/* SESPID16 */
			U4	xSESPID17				:1;				/* SESPID17 */
			U4	xSESPID18				:1;				/* SESPID18 */
			U4	xSESPID19				:1;				/* SESPID19 */
			U4	xSESPID20				:1;				/* SESPID20 */
			U4	xSESPID21				:1;				/* SESPID21 */
			U4	xSESPID22				:1;				/* SESPID22 */
			U4	xSESPID23				:1;				/* SESPID23 */
			U4	xSESPID24				:1;				/* SESPID24 */
			U4	xSESPID25				:1;				/* SESPID25 */
			U4	xSESPID26				:1;				/* SESPID26 */
			U4	xSESPID27				:1;				/* SESPID27 */
			U4	xSESPID28				:1;				/* SESPID28 */
			U4	xSESPID29				:1;				/* SESPID29 */
			U4	xSESPID30				:1;				/* SESPID30 */
			U4	xSESPID31				:1;				/* SESPID31 */
		} stBit;
	} unDFSESPID2;										/* 0xFFC62C80 - 0xFFC62C84 */

	union												/* DFSESPIDC2 */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSESPIDCLR0				:1;				/* SESPIDCLR0 */
			U4	xSESPIDCLR1				:1;				/* SESPIDCLR1 */
			U4	xSESPIDCLR2				:1;				/* SESPIDCLR2 */
			U4	xSESPIDCLR3				:1;				/* SESPIDCLR3 */
			U4	xSESPIDCLR4				:1;				/* SESPIDCLR4 */
			U4	xSESPIDCLR5				:1;				/* SESPIDCLR5 */
			U4	xSESPIDCLR6				:1;				/* SESPIDCLR6 */
			U4	xSESPIDCLR7				:1;				/* SESPIDCLR7 */
			U4	xSESPIDCLR8				:1;				/* SESPIDCLR8 */
			U4	xSESPIDCLR9				:1;				/* SESPIDCLR9 */
			U4	xSESPIDCLR10			:1;				/* SESPIDCLR10 */
			U4	xSESPIDCLR11			:1;				/* SESPIDCLR11 */
			U4	xSESPIDCLR12			:1;				/* SESPIDCLR12 */
			U4	xSESPIDCLR13			:1;				/* SESPIDCLR13 */
			U4	xSESPIDCLR14			:1;				/* SESPIDCLR14 */
			U4	xSESPIDCLR15			:1;				/* SESPIDCLR15 */
			U4	xSESPIDCLR16			:1;				/* SESPIDCLR16 */
			U4	xSESPIDCLR17			:1;				/* SESPIDCLR17 */
			U4	xSESPIDCLR18			:1;				/* SESPIDCLR18 */
			U4	xSESPIDCLR19			:1;				/* SESPIDCLR19 */
			U4	xSESPIDCLR20			:1;				/* SESPIDCLR20 */
			U4	xSESPIDCLR21			:1;				/* SESPIDCLR21 */
			U4	xSESPIDCLR22			:1;				/* SESPIDCLR22 */
			U4	xSESPIDCLR23			:1;				/* SESPIDCLR23 */
			U4	xSESPIDCLR24			:1;				/* SESPIDCLR24 */
			U4	xSESPIDCLR25			:1;				/* SESPIDCLR25 */
			U4	xSESPIDCLR26			:1;				/* SESPIDCLR26 */
			U4	xSESPIDCLR27			:1;				/* SESPIDCLR27 */
			U4	xSESPIDCLR28			:1;				/* SESPIDCLR28 */
			U4	xSESPIDCLR29			:1;				/* SESPIDCLR29 */
			U4	xSESPIDCLR30			:1;				/* SESPIDCLR30 */
			U4	xSESPIDCLR31			:1;				/* SESPIDCLR31 */
		} stBit;
	} unDFSESPIDC2;										/* 0xFFC62C84 - 0xFFC62C88 */

	union												/* DFSESPID3 */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSESPID0				:1;				/* SESPID0 */
			U4	xSESPID1				:1;				/* SESPID1 */
			U4	xSESPID2				:1;				/* SESPID2 */
			U4	xSESPID3				:1;				/* SESPID3 */
			U4	xSESPID4				:1;				/* SESPID4 */
			U4	xSESPID5				:1;				/* SESPID5 */
			U4	xSESPID6				:1;				/* SESPID6 */
			U4	xSESPID7				:1;				/* SESPID7 */
			U4	xSESPID8				:1;				/* SESPID8 */
			U4	xSESPID9				:1;				/* SESPID9 */
			U4	xSESPID10				:1;				/* SESPID10 */
			U4	xSESPID11				:1;				/* SESPID11 */
			U4	xSESPID12				:1;				/* SESPID12 */
			U4	xSESPID13				:1;				/* SESPID13 */
			U4	xSESPID14				:1;				/* SESPID14 */
			U4	xSESPID15				:1;				/* SESPID15 */
			U4	xSESPID16				:1;				/* SESPID16 */
			U4	xSESPID17				:1;				/* SESPID17 */
			U4	xSESPID18				:1;				/* SESPID18 */
			U4	xSESPID19				:1;				/* SESPID19 */
			U4	xSESPID20				:1;				/* SESPID20 */
			U4	xSESPID21				:1;				/* SESPID21 */
			U4	xSESPID22				:1;				/* SESPID22 */
			U4	xSESPID23				:1;				/* SESPID23 */
			U4	xSESPID24				:1;				/* SESPID24 */
			U4	xSESPID25				:1;				/* SESPID25 */
			U4	xSESPID26				:1;				/* SESPID26 */
			U4	xSESPID27				:1;				/* SESPID27 */
			U4	xSESPID28				:1;				/* SESPID28 */
			U4	xSESPID29				:1;				/* SESPID29 */
			U4	xSESPID30				:1;				/* SESPID30 */
			U4	xSESPID31				:1;				/* SESPID31 */
		} stBit;
	} unDFSESPID3;										/* 0xFFC62C88 - 0xFFC62C8C */

	union												/* DFSESPIDC3 */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSESPIDCLR0				:1;				/* SESPIDCLR0 */
			U4	xSESPIDCLR1				:1;				/* SESPIDCLR1 */
			U4	xSESPIDCLR2				:1;				/* SESPIDCLR2 */
			U4	xSESPIDCLR3				:1;				/* SESPIDCLR3 */
			U4	xSESPIDCLR4				:1;				/* SESPIDCLR4 */
			U4	xSESPIDCLR5				:1;				/* SESPIDCLR5 */
			U4	xSESPIDCLR6				:1;				/* SESPIDCLR6 */
			U4	xSESPIDCLR7				:1;				/* SESPIDCLR7 */
			U4	xSESPIDCLR8				:1;				/* SESPIDCLR8 */
			U4	xSESPIDCLR9				:1;				/* SESPIDCLR9 */
			U4	xSESPIDCLR10			:1;				/* SESPIDCLR10 */
			U4	xSESPIDCLR11			:1;				/* SESPIDCLR11 */
			U4	xSESPIDCLR12			:1;				/* SESPIDCLR12 */
			U4	xSESPIDCLR13			:1;				/* SESPIDCLR13 */
			U4	xSESPIDCLR14			:1;				/* SESPIDCLR14 */
			U4	xSESPIDCLR15			:1;				/* SESPIDCLR15 */
			U4	xSESPIDCLR16			:1;				/* SESPIDCLR16 */
			U4	xSESPIDCLR17			:1;				/* SESPIDCLR17 */
			U4	xSESPIDCLR18			:1;				/* SESPIDCLR18 */
			U4	xSESPIDCLR19			:1;				/* SESPIDCLR19 */
			U4	xSESPIDCLR20			:1;				/* SESPIDCLR20 */
			U4	xSESPIDCLR21			:1;				/* SESPIDCLR21 */
			U4	xSESPIDCLR22			:1;				/* SESPIDCLR22 */
			U4	xSESPIDCLR23			:1;				/* SESPIDCLR23 */
			U4	xSESPIDCLR24			:1;				/* SESPIDCLR24 */
			U4	xSESPIDCLR25			:1;				/* SESPIDCLR25 */
			U4	xSESPIDCLR26			:1;				/* SESPIDCLR26 */
			U4	xSESPIDCLR27			:1;				/* SESPIDCLR27 */
			U4	xSESPIDCLR28			:1;				/* SESPIDCLR28 */
			U4	xSESPIDCLR29			:1;				/* SESPIDCLR29 */
			U4	xSESPIDCLR30			:1;				/* SESPIDCLR30 */
			U4	xSESPIDCLR31			:1;				/* SESPIDCLR31 */
		} stBit;
	} unDFSESPIDC3;										/* 0xFFC62C8C - 0xFFC62C90 */

	U1	u1Dummy3[0xFFC62CF0U - 0xFFC62C90U];			/* 0xFFC62C90 - 0xFFC62CF0 */

	union												/* DFDESPID */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDESPID0				:1;				/* DESPID0 */
			U4	xDESPID1				:1;				/* DESPID1 */
			U4	xDESPID2				:1;				/* DESPID2 */
			U4	xDESPID3				:1;				/* DESPID3 */
			U4	xDESPID4				:1;				/* DESPID4 */
			U4	xDESPID5				:1;				/* DESPID5 */
			U4	xDESPID6				:1;				/* DESPID6 */
			U4	xDESPID7				:1;				/* DESPID7 */
			U4	xDESPID8				:1;				/* DESPID8 */
			U4	xDESPID9				:1;				/* DESPID9 */
			U4	xDESPID10				:1;				/* DESPID10 */
			U4	xDESPID11				:1;				/* DESPID11 */
			U4	xDESPID12				:1;				/* DESPID12 */
			U4	xDESPID13				:1;				/* DESPID13 */
			U4	xDESPID14				:1;				/* DESPID14 */
			U4	xDESPID15				:1;				/* DESPID15 */
			U4	xDESPID16				:1;				/* DESPID16 */
			U4	xDESPID17				:1;				/* DESPID17 */
			U4	xDESPID18				:1;				/* DESPID18 */
			U4	xDESPID19				:1;				/* DESPID19 */
			U4	xDESPID20				:1;				/* DESPID20 */
			U4	xDESPID21				:1;				/* DESPID21 */
			U4	xDESPID22				:1;				/* DESPID22 */
			U4	xDESPID23				:1;				/* DESPID23 */
			U4	xDESPID24				:1;				/* DESPID24 */
			U4	xDESPID25				:1;				/* DESPID25 */
			U4	xDESPID26				:1;				/* DESPID26 */
			U4	xDESPID27				:1;				/* DESPID27 */
			U4	xDESPID28				:1;				/* DESPID28 */
			U4	xDESPID29				:1;				/* DESPID29 */
			U4	xDESPID30				:1;				/* DESPID30 */
			U4	xDESPID31				:1;				/* DESPID31 */
		} stBit;
	} unDFDESPID;										/* 0xFFC62CF0 - 0xFFC62CF4 */

	union												/* DFDESPIDC */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDESPIDCLR0				:1;				/* DESPIDCLR0 */
			U4	xDESPIDCLR1				:1;				/* DESPIDCLR1 */
			U4	xDESPIDCLR2				:1;				/* DESPIDCLR2 */
			U4	xDESPIDCLR3				:1;				/* DESPIDCLR3 */
			U4	xDESPIDCLR4				:1;				/* DESPIDCLR4 */
			U4	xDESPIDCLR5				:1;				/* DESPIDCLR5 */
			U4	xDESPIDCLR6				:1;				/* DESPIDCLR6 */
			U4	xDESPIDCLR7				:1;				/* DESPIDCLR7 */
			U4	xDESPIDCLR8				:1;				/* DESPIDCLR8 */
			U4	xDESPIDCLR9				:1;				/* DESPIDCLR9 */
			U4	xDESPIDCLR10			:1;				/* DESPIDCLR10 */
			U4	xDESPIDCLR11			:1;				/* DESPIDCLR11 */
			U4	xDESPIDCLR12			:1;				/* DESPIDCLR12 */
			U4	xDESPIDCLR13			:1;				/* DESPIDCLR13 */
			U4	xDESPIDCLR14			:1;				/* DESPIDCLR14 */
			U4	xDESPIDCLR15			:1;				/* DESPIDCLR15 */
			U4	xDESPIDCLR16			:1;				/* DESPIDCLR16 */
			U4	xDESPIDCLR17			:1;				/* DESPIDCLR17 */
			U4	xDESPIDCLR18			:1;				/* DESPIDCLR18 */
			U4	xDESPIDCLR19			:1;				/* DESPIDCLR19 */
			U4	xDESPIDCLR20			:1;				/* DESPIDCLR20 */
			U4	xDESPIDCLR21			:1;				/* DESPIDCLR21 */
			U4	xDESPIDCLR22			:1;				/* DESPIDCLR22 */
			U4	xDESPIDCLR23			:1;				/* DESPIDCLR23 */
			U4	xDESPIDCLR24			:1;				/* DESPIDCLR24 */
			U4	xDESPIDCLR25			:1;				/* DESPIDCLR25 */
			U4	xDESPIDCLR26			:1;				/* DESPIDCLR26 */
			U4	xDESPIDCLR27			:1;				/* DESPIDCLR27 */
			U4	xDESPIDCLR28			:1;				/* DESPIDCLR28 */
			U4	xDESPIDCLR29			:1;				/* DESPIDCLR29 */
			U4	xDESPIDCLR30			:1;				/* DESPIDCLR30 */
			U4	xDESPIDCLR31			:1;				/* DESPIDCLR31 */
		} stBit;
	} unDFDESPIDC;										/* 0xFFC62CF4 - 0xFFC62CF8 */

	union												/* DFTSTCTL */
	{
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xECCTST					:1;				/* ECCTST */
			U4	b31Dummy1				:31;
		} stBit;
	} unDFTSTCTL;										/* 0xFFC62CF8 - 0xFFC62CFC */

	union												/* DFKCPROT */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xKCE					:1;				/* KCE */
			U4	b31KCPROT				:31;			/* KCPROT[31:1] */
		} stBit;
	} unDFKCPROT;										/* 0xFFC62CFC - 0xFFC62D00 */

}	Reg_Ecc_EccDfType;


/* ECCCNT_LR_PE0CL0 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_LR_PE0CL0 ====================== */
/* ============================================================================ */
typedef	struct											/* ECCCNT_LR_PE0CL0 */
{
	union												/* LRECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	xDummy1					:1;
			U4	xAFEDIS					:1;				/* AFEDIS */
			U4	b28Dummy2				:28;
		} stBit;
	} unLRECCCTL;										/* 0xFFC49800 - 0xFFC49804 */

	U1	u1Dummy1[0xFFC49810U - 0xFFC49804U];			/* 0xFFC49804 - 0xFFC49810 */

	union												/* LRECCTSTCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDATSEL					:1;				/* DATSEL */
			U4	xECCTST					:1;				/* ECCTST */
			U4	b30Dummy1				:30;
		} stBit;
	} unLRECCTSTCTL;									/* 0xFFC49810 - 0xFFC49814 */

	U1	u1Dummy2[0xFFC49820U - 0xFFC49814U];			/* 0xFFC49814 - 0xFFC49820 */

	union												/* LRAFINV */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b4Dummy1				:4;
			U4	b17AFINV				:17;			/* AFINV[20:4] */
			U4	b11Dummy2				:11;
		} stBit;
	} unLRAFINV;										/* 0xFFC49820 - 0xFFC49824 */

	U1	u1Dummy3[0xFFC49860U - 0xFFC49824U];			/* 0xFFC49824 - 0xFFC49860 */

	union												/* LRTDATBFECCF */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b7BFECC0				:7;				/* BFECC0[6:0] */
			U4	xDummy1					:1;
			U4	b7BFECC1				:7;				/* BFECC1[6:0] */
			U4	xDummy2					:1;
			U4	b7BFECC2				:7;				/* BFECC2[6:0] */
			U4	xDummy3					:1;
			U4	b7BFECC3				:7;				/* BFECC3[6:0] */
			U4	xDummy4					:1;
		} stBit;
	} unLRTDATBFECCF;									/* 0xFFC49860 - 0xFFC49864 */

}	Reg_Ecc_EccCnt_Lr_Pe0Cl0Type;


/* ECCCNT_LR_PE1CL0 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_LR_PE1CL0 ====================== */
/* ============================================================================ */
typedef	struct											/* ECCCNT_LR_PE1CL0 */
{
	union												/* LRECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	xDummy1					:1;
			U4	xAFEDIS					:1;				/* AFEDIS */
			U4	b28Dummy2				:28;
		} stBit;
	} unLRECCCTL;										/* 0xFFC49880 - 0xFFC49884 */

	U1	u1Dummy1[0xFFC49890U - 0xFFC49884U];			/* 0xFFC49884 - 0xFFC49890 */

	union												/* LRECCTSTCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDATSEL					:1;				/* DATSEL */
			U4	xECCTST					:1;				/* ECCTST */
			U4	b30Dummy1				:30;
		} stBit;
	} unLRECCTSTCTL;									/* 0xFFC49890 - 0xFFC49894 */

	U1	u1Dummy2[0xFFC498A0U - 0xFFC49894U];			/* 0xFFC49894 - 0xFFC498A0 */

	union												/* LRAFINV */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b4Dummy1				:4;
			U4	b17AFINV				:17;			/* AFINV[20:4] */
			U4	b11Dummy2				:11;
		} stBit;
	} unLRAFINV;										/* 0xFFC498A0 - 0xFFC498A4 */

	U1	u1Dummy3[0xFFC498E0U - 0xFFC498A4U];			/* 0xFFC498A4 - 0xFFC498E0 */

	union												/* LRTDATBFECCF */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b7BFECC0				:7;				/* BFECC0[6:0] */
			U4	xDummy1					:1;
			U4	b7BFECC1				:7;				/* BFECC1[6:0] */
			U4	xDummy2					:1;
			U4	b7BFECC2				:7;				/* BFECC2[6:0] */
			U4	xDummy3					:1;
			U4	b7BFECC3				:7;				/* BFECC3[6:0] */
			U4	xDummy4					:1;
		} stBit;
	} unLRTDATBFECCF;									/* 0xFFC498E0 - 0xFFC498E4 */

}	Reg_Ecc_EccCnt_Lr_Pe1Cl0Type;


/* ECCCNT_LR_PE2CL1 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_LR_PE2CL1 ====================== */
/* ============================================================================ */
typedef	struct											/* ECCCNT_LR_PE2CL1 */
{
	union												/* LRECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	xDummy1					:1;
			U4	xAFEDIS					:1;				/* AFEDIS */
			U4	b28Dummy2				:28;
		} stBit;
	} unLRECCCTL;										/* 0xFFC49900 - 0xFFC49904 */

	U1	u1Dummy1[0xFFC49910U - 0xFFC49904U];			/* 0xFFC49904 - 0xFFC49910 */

	union												/* LRECCTSTCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDATSEL					:1;				/* DATSEL */
			U4	xECCTST					:1;				/* ECCTST */
			U4	b30Dummy1				:30;
		} stBit;
	} unLRECCTSTCTL;									/* 0xFFC49910 - 0xFFC49914 */

	U1	u1Dummy2[0xFFC49920U - 0xFFC49914U];			/* 0xFFC49914 - 0xFFC49920 */

	union												/* LRAFINV */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b4Dummy1				:4;
			U4	b17AFINV				:17;			/* AFINV[20:4] */
			U4	b11Dummy2				:11;
		} stBit;
	} unLRAFINV;										/* 0xFFC49920 - 0xFFC49924 */

	U1	u1Dummy3[0xFFC49960U - 0xFFC49924U];			/* 0xFFC49924 - 0xFFC49960 */

	union												/* LRTDATBFECCF */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b7BFECC0				:7;				/* BFECC0[6:0] */
			U4	xDummy1					:1;
			U4	b7BFECC1				:7;				/* BFECC1[6:0] */
			U4	xDummy2					:1;
			U4	b7BFECC2				:7;				/* BFECC2[6:0] */
			U4	xDummy3					:1;
			U4	b7BFECC3				:7;				/* BFECC3[6:0] */
			U4	xDummy4					:1;
		} stBit;
	} unLRTDATBFECCF;									/* 0xFFC49960 - 0xFFC49964 */

}	Reg_Ecc_EccCnt_Lr_Pe2Cl1Type;


/* ECCCNT_LR_PE3CL1 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_LR_PE3CL1 ====================== */
/* ============================================================================ */
typedef	struct											/* ECCCNT_LR_PE3CL1 */
{
	union												/* LRECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	xDummy1					:1;
			U4	xAFEDIS					:1;				/* AFEDIS */
			U4	b28Dummy2				:28;
		} stBit;
	} unLRECCCTL;										/* 0xFFC49980 - 0xFFC49984 */

	U1	u1Dummy1[0xFFC49990U - 0xFFC49984U];			/* 0xFFC49984 - 0xFFC49990 */

	union												/* LRECCTSTCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDATSEL					:1;				/* DATSEL */
			U4	xECCTST					:1;				/* ECCTST */
			U4	b30Dummy1				:30;
		} stBit;
	} unLRECCTSTCTL;									/* 0xFFC49990 - 0xFFC49994 */

	U1	u1Dummy2[0xFFC499A0U - 0xFFC49994U];			/* 0xFFC49994 - 0xFFC499A0 */

	union												/* LRAFINV */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b4Dummy1				:4;
			U4	b17AFINV				:17;			/* AFINV[20:4] */
			U4	b11Dummy2				:11;
		} stBit;
	} unLRAFINV;										/* 0xFFC499A0 - 0xFFC499A4 */

	U1	u1Dummy3[0xFFC499E0U - 0xFFC499A4U];			/* 0xFFC499A4 - 0xFFC499E0 */

	union												/* LRTDATBFECCF */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b7BFECC0				:7;				/* BFECC0[6:0] */
			U4	xDummy1					:1;
			U4	b7BFECC1				:7;				/* BFECC1[6:0] */
			U4	xDummy2					:1;
			U4	b7BFECC2				:7;				/* BFECC2[6:0] */
			U4	xDummy3					:1;
			U4	b7BFECC3				:7;				/* BFECC3[6:0] */
			U4	xDummy4					:1;
		} stBit;
	} unLRTDATBFECCF;									/* 0xFFC499E0 - 0xFFC499E4 */

}	Reg_Ecc_EccCnt_Lr_Pe3Cl1Type;


/* ECCCNT_LR_PE4CL2 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_LR_PE4CL2 ====================== */
/* ============================================================================ */
typedef	struct											/* ECCCNT_LR_PE4CL2 */
{
	union												/* LRECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	xDummy1					:1;
			U4	xAFEDIS					:1;				/* AFEDIS */
			U4	b28Dummy2				:28;
		} stBit;
	} unLRECCCTL;										/* 0xFFC49A00 - 0xFFC49A04 */

	U1	u1Dummy1[0xFFC49A10U - 0xFFC49A04U];			/* 0xFFC49A04 - 0xFFC49A10 */

	union												/* LRECCTSTCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDATSEL					:1;				/* DATSEL */
			U4	xECCTST					:1;				/* ECCTST */
			U4	b30Dummy1				:30;
		} stBit;
	} unLRECCTSTCTL;									/* 0xFFC49A10 - 0xFFC49A14 */

	U1	u1Dummy2[0xFFC49A20U - 0xFFC49A14U];			/* 0xFFC49A14 - 0xFFC49A20 */

	union												/* LRAFINV */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b4Dummy1				:4;
			U4	b17AFINV				:17;			/* AFINV[20:4] */
			U4	b11Dummy2				:11;
		} stBit;
	} unLRAFINV;										/* 0xFFC49A20 - 0xFFC49A24 */

	U1	u1Dummy3[0xFFC49A60U - 0xFFC49A24U];			/* 0xFFC49A24 - 0xFFC49A60 */

	union												/* LRTDATBFECCF */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b7BFECC0				:7;				/* BFECC0[6:0] */
			U4	xDummy1					:1;
			U4	b7BFECC1				:7;				/* BFECC1[6:0] */
			U4	xDummy2					:1;
			U4	b7BFECC2				:7;				/* BFECC2[6:0] */
			U4	xDummy3					:1;
			U4	b7BFECC3				:7;				/* BFECC3[6:0] */
			U4	xDummy4					:1;
		} stBit;
	} unLRTDATBFECCF;									/* 0xFFC49A60 - 0xFFC49A64 */

}	Reg_Ecc_EccCnt_Lr_Pe4Cl2Type;


/* ECCCNT_LR_PE5CL2 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_LR_PE5CL2 ====================== */
/* ============================================================================ */
typedef	struct											/* ECCCNT_LR_PE5CL2 */
{
	union												/* LRECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	xDummy1					:1;
			U4	xAFEDIS					:1;				/* AFEDIS */
			U4	b28Dummy2				:28;
		} stBit;
	} unLRECCCTL;										/* 0xFFC49A80 - 0xFFC49A84 */

	U1	u1Dummy1[0xFFC49A90U - 0xFFC49A84U];			/* 0xFFC49A84 - 0xFFC49A90 */

	union												/* LRECCTSTCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDATSEL					:1;				/* DATSEL */
			U4	xECCTST					:1;				/* ECCTST */
			U4	b30Dummy1				:30;
		} stBit;
	} unLRECCTSTCTL;									/* 0xFFC49A90 - 0xFFC49A94 */

	U1	u1Dummy2[0xFFC49AA0U - 0xFFC49A94U];			/* 0xFFC49A94 - 0xFFC49AA0 */

	union												/* LRAFINV */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b4Dummy1				:4;
			U4	b17AFINV				:17;			/* AFINV[20:4] */
			U4	b11Dummy2				:11;
		} stBit;
	} unLRAFINV;										/* 0xFFC49AA0 - 0xFFC49AA4 */

	U1	u1Dummy3[0xFFC49AE0U - 0xFFC49AA4U];			/* 0xFFC49AA4 - 0xFFC49AE0 */

	union												/* LRTDATBFECCF */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b7BFECC0				:7;				/* BFECC0[6:0] */
			U4	xDummy1					:1;
			U4	b7BFECC1				:7;				/* BFECC1[6:0] */
			U4	xDummy2					:1;
			U4	b7BFECC2				:7;				/* BFECC2[6:0] */
			U4	xDummy3					:1;
			U4	b7BFECC3				:7;				/* BFECC3[6:0] */
			U4	xDummy4					:1;
		} stBit;
	} unLRTDATBFECCF;									/* 0xFFC49AE0 - 0xFFC49AE4 */

}	Reg_Ecc_EccCnt_Lr_Pe5Cl2Type;


/* MECCCAP_LR_PE0CL0 */
/* ============================================================================ */
/* ============================ Module: MECCCAP_LR_PE0CL0 ===================== */
/* ============================================================================ */
typedef	struct											/* MECCCAP_LR_PE0CL0 */
{
	union												/* LR0_ERRINT */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDIE					:1;				/* SEDIE */
			U4	xDEDIE					:1;				/* DEDIE */
			U4	xDummy1					:1;
			U4	xAFEIE					:1;				/* AFEIE */
			U4	b3Dummy2				:3;
			U4	xSEOVFIE				:1;				/* SEOVFIE */
			U4	b24Dummy3				:24;
		} stBit;
	} unLR0_ERRINT;										/* 0xFFC52000 - 0xFFC52004 */

	U1	u1Dummy1[0xFFC52010U - 0xFFC52004U];			/* 0xFFC52004 - 0xFFC52010 */

	union												/* LR0_SSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSSTCLR00				:1;				/* SSTCLR00 */
			U4	xSSTCLR01				:1;				/* SSTCLR01 */
			U4	xSSTCLR02				:1;				/* SSTCLR02 */
			U4	xSSTCLR03				:1;				/* SSTCLR03 */
			U4	xSSTCLR04				:1;				/* SSTCLR04 */
			U4	xSSTCLR05				:1;				/* SSTCLR05 */
			U4	xSSTCLR06				:1;				/* SSTCLR06 */
			U4	xSSTCLR07				:1;				/* SSTCLR07 */
			U4	b24Dummy1				:24;
		} stBit;
	} unLR0_SSTCLR;										/* 0xFFC52010 - 0xFFC52014 */

	union												/* LR0_DSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDSTCLR00				:1;				/* DSTCLR00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unLR0_DSTCLR;										/* 0xFFC52014 - 0xFFC52018 */

	union												/* LR0_OVFCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSERROVFCLR0			:1;				/* SERROVFCLR0 */
			U4	xSERROVFCLR1			:1;				/* SERROVFCLR1 */
			U4	b30Dummy1				:30;
		} stBit;
	} unLR0_OVFCLR;										/* 0xFFC52018 - 0xFFC5201C */

	U1	u1Dummy2[0xFFC52020U - 0xFFC5201CU];			/* 0xFFC5201C - 0xFFC52020 */

	union												/* LR0_SERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDF00					:1;				/* SEDF00 */
			U4	xSEDF01					:1;				/* SEDF01 */
			U4	xSEDF02					:1;				/* SEDF02 */
			U4	xSEDF03					:1;				/* SEDF03 */
			U4	xSEDF04					:1;				/* SEDF04 */
			U4	xSEDF05					:1;				/* SEDF05 */
			U4	xSEDF06					:1;				/* SEDF06 */
			U4	xSEDF07					:1;				/* SEDF07 */
			U4	b24Dummy1				:24;
		} stBit;
	} unLR0_SERSTR;										/* 0xFFC52020 - 0xFFC52024 */

	union												/* LR0_DERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDummy1					:1;
			U4	xDEDF00					:1;				/* DEDF00 */
			U4	xDummy2					:1;
			U4	xAFEF00					:1;				/* AFEF00 */
			U4	b28Dummy3				:28;
		} stBit;
	} unLR0_DERSTR;										/* 0xFFC52024 - 0xFFC52028 */

	union												/* LR0_OVFSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSERROVF0				:1;				/* SERROVF0 */
			U4	xSERROVF1				:1;				/* SERROVF1 */
			U4	b30Dummy1				:30;
		} stBit;
	} unLR0_OVFSTR;										/* 0xFFC52028 - 0xFFC5202C */

	U1	u1Dummy3[0xFFC52030U - 0xFFC5202CU];			/* 0xFFC5202C - 0xFFC52030 */

	union												/* LR0_SERINF */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDLINF00				:1;				/* SEDLINF00 */
			U4	xSEDLINF01				:1;				/* SEDLINF01 */
			U4	xSEDLINF02				:1;				/* SEDLINF02 */
			U4	xSEDLINF03				:1;				/* SEDLINF03 */
			U4	xSEDLINF04				:1;				/* SEDLINF04 */
			U4	b27Dummy1				:27;
		} stBit;
	} unLR0_SERINF;										/* 0xFFC52030 - 0xFFC52034 */

	U1	u1Dummy4[0xFFC52070U - 0xFFC52034U];			/* 0xFFC52034 - 0xFFC52070 */

	union												/* LR0_nSEADR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b2Dummy1				:2;
			U4	b14SEADR0				:14;			/* SEADR0[15:2] */
			U4	b11Dummy2				:11;
			U4	b5SEDL					:5;				/* SEDL[4:0] */
		} stBit;
	} unLR0_nSEADR[ECC_BUFFNUM_LRAM];					/* 0xFFC52070 - 0xFFC52090 */

	U1	u1Dummy5[0xFFC520F0U - 0xFFC52090U];			/* 0xFFC52090 - 0xFFC520F0 */

	union												/* LR0_00DEADR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b2Dummy1				:2;
			U4	b14DEADR0				:14;			/* DEADR0[15:2] */
			U4	b11Dummy2				:11;
			U4	b5DEDL					:5;				/* DEDL[4:0] */
		} stBit;
	} unLR0_00DEADR;									/* 0xFFC520F0 - 0xFFC520F4 */

	union												/* LR0_00DESPIDCLR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xCLR00					:1;				/* DESPIDCLR00 */
			U4	xCLR01					:1;				/* DESPIDCLR01 */
			U4	xCLR02					:1;				/* DESPIDCLR02 */
			U4	xCLR03					:1;				/* DESPIDCLR03 */
			U4	xCLR04					:1;				/* DESPIDCLR04 */
			U4	xCLR05					:1;				/* DESPIDCLR05 */
			U4	xCLR06					:1;				/* DESPIDCLR06 */
			U4	xCLR07					:1;				/* DESPIDCLR07 */
			U4	xCLR08					:1;				/* DESPIDCLR08 */
			U4	xCLR09					:1;				/* DESPIDCLR09 */
			U4	xCLR10					:1;				/* DESPIDCLR10 */
			U4	xCLR11					:1;				/* DESPIDCLR11 */
			U4	xCLR12					:1;				/* DESPIDCLR12 */
			U4	xCLR13					:1;				/* DESPIDCLR13 */
			U4	xCLR14					:1;				/* DESPIDCLR14 */
			U4	xCLR15					:1;				/* DESPIDCLR15 */
			U4	xCLR16					:1;				/* DESPIDCLR16 */
			U4	xCLR17					:1;				/* DESPIDCLR17 */
			U4	xCLR18					:1;				/* DESPIDCLR18 */
			U4	xCLR19					:1;				/* DESPIDCLR19 */
			U4	xCLR20					:1;				/* DESPIDCLR20 */
			U4	xCLR21					:1;				/* DESPIDCLR21 */
			U4	xCLR22					:1;				/* DESPIDCLR22 */
			U4	xCLR23					:1;				/* DESPIDCLR23 */
			U4	xCLR24					:1;				/* DESPIDCLR24 */
			U4	xCLR25					:1;				/* DESPIDCLR25 */
			U4	xCLR26					:1;				/* DESPIDCLR26 */
			U4	xCLR27					:1;				/* DESPIDCLR27 */
			U4	xCLR28					:1;				/* DESPIDCLR28 */
			U4	xCLR29					:1;				/* DESPIDCLR29 */
			U4	xCLR30					:1;				/* DESPIDCLR30 */
			U4	xCLR31					:1;				/* DESPIDCLR31 */
		} stBit;
	} unLR0_00DESPIDCLR;								/* 0xFFC520F4 - 0xFFC520F8 */

	union												/* LR0_00DESPID */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSPID00					:1;				/* DESPID00 */
			U4	xSPID01					:1;				/* DESPID01 */
			U4	xSPID02					:1;				/* DESPID02 */
			U4	xSPID03					:1;				/* DESPID03 */
			U4	xSPID04					:1;				/* DESPID04 */
			U4	xSPID05					:1;				/* DESPID05 */
			U4	xSPID06					:1;				/* DESPID06 */
			U4	xSPID07					:1;				/* DESPID07 */
			U4	xSPID08					:1;				/* DESPID08 */
			U4	xSPID09					:1;				/* DESPID09 */
			U4	xSPID10					:1;				/* DESPID10 */
			U4	xSPID11					:1;				/* DESPID11 */
			U4	xSPID12					:1;				/* DESPID12 */
			U4	xSPID13					:1;				/* DESPID13 */
			U4	xSPID14					:1;				/* DESPID14 */
			U4	xSPID15					:1;				/* DESPID15 */
			U4	xSPID16					:1;				/* DESPID16 */
			U4	xSPID17					:1;				/* DESPID17 */
			U4	xSPID18					:1;				/* DESPID18 */
			U4	xSPID19					:1;				/* DESPID19 */
			U4	xSPID20					:1;				/* DESPID20 */
			U4	xSPID21					:1;				/* DESPID21 */
			U4	xSPID22					:1;				/* DESPID22 */
			U4	xSPID23					:1;				/* DESPID23 */
			U4	xSPID24					:1;				/* DESPID24 */
			U4	xSPID25					:1;				/* DESPID25 */
			U4	xSPID26					:1;				/* DESPID26 */
			U4	xSPID27					:1;				/* DESPID27 */
			U4	xSPID28					:1;				/* DESPID28 */
			U4	xSPID29					:1;				/* DESPID29 */
			U4	xSPID30					:1;				/* DESPID30 */
			U4	xSPID31					:1;				/* DESPID31 */
		} stBit;
	} unLR0_00DESPID;									/* 0xFFC520F8 - 0xFFC520FC */

	U1	u1Dummy6[0xFFC52100U - 0xFFC520FCU];			/* 0xFFC520FC - 0xFFC52100 */

	union												/* LR0_kSESPIDCLR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xCLR00					:1;				/* SESPIDCLR00 */
			U4	xCLR01					:1;				/* SESPIDCLR01 */
			U4	xCLR02					:1;				/* SESPIDCLR02 */
			U4	xCLR03					:1;				/* SESPIDCLR03 */
			U4	xCLR04					:1;				/* SESPIDCLR04 */
			U4	xCLR05					:1;				/* SESPIDCLR05 */
			U4	xCLR06					:1;				/* SESPIDCLR06 */
			U4	xCLR07					:1;				/* SESPIDCLR07 */
			U4	xCLR08					:1;				/* SESPIDCLR08 */
			U4	xCLR09					:1;				/* SESPIDCLR09 */
			U4	xCLR10					:1;				/* SESPIDCLR10 */
			U4	xCLR11					:1;				/* SESPIDCLR11 */
			U4	xCLR12					:1;				/* SESPIDCLR12 */
			U4	xCLR13					:1;				/* SESPIDCLR13 */
			U4	xCLR14					:1;				/* SESPIDCLR14 */
			U4	xCLR15					:1;				/* SESPIDCLR15 */
			U4	xCLR16					:1;				/* SESPIDCLR16 */
			U4	xCLR17					:1;				/* SESPIDCLR17 */
			U4	xCLR18					:1;				/* SESPIDCLR18 */
			U4	xCLR19					:1;				/* SESPIDCLR19 */
			U4	xCLR20					:1;				/* SESPIDCLR20 */
			U4	xCLR21					:1;				/* SESPIDCLR21 */
			U4	xCLR22					:1;				/* SESPIDCLR22 */
			U4	xCLR23					:1;				/* SESPIDCLR23 */
			U4	xCLR24					:1;				/* SESPIDCLR24 */
			U4	xCLR25					:1;				/* SESPIDCLR25 */
			U4	xCLR26					:1;				/* SESPIDCLR26 */
			U4	xCLR27					:1;				/* SESPIDCLR27 */
			U4	xCLR28					:1;				/* SESPIDCLR28 */
			U4	xCLR29					:1;				/* SESPIDCLR29 */
			U4	xCLR30					:1;				/* SESPIDCLR30 */
			U4	xCLR31					:1;				/* SESPIDCLR31 */
		} stBit;
	} unLR0_kSESPIDCLR[ECC_BUFFNUM_LRAM];				/* 0xFFC52100 - 0xFFC52120 */

	U1	u1Dummy7[0xFFC52180U - 0xFFC52120U];			/* 0xFFC52120 - 0xFFC52180 */

	union												/* LR0_kSESPID */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSPID00					:1;				/* SESPID00 */
			U4	xSPID01					:1;				/* SESPID01 */
			U4	xSPID02					:1;				/* SESPID02 */
			U4	xSPID03					:1;				/* SESPID03 */
			U4	xSPID04					:1;				/* SESPID04 */
			U4	xSPID05					:1;				/* SESPID05 */
			U4	xSPID06					:1;				/* SESPID06 */
			U4	xSPID07					:1;				/* SESPID07 */
			U4	xSPID08					:1;				/* SESPID08 */
			U4	xSPID09					:1;				/* SESPID09 */
			U4	xSPID10					:1;				/* SESPID10 */
			U4	xSPID11					:1;				/* SESPID11 */
			U4	xSPID12					:1;				/* SESPID12 */
			U4	xSPID13					:1;				/* SESPID13 */
			U4	xSPID14					:1;				/* SESPID14 */
			U4	xSPID15					:1;				/* SESPID15 */
			U4	xSPID16					:1;				/* SESPID16 */
			U4	xSPID17					:1;				/* SESPID17 */
			U4	xSPID18					:1;				/* SESPID18 */
			U4	xSPID19					:1;				/* SESPID19 */
			U4	xSPID20					:1;				/* SESPID20 */
			U4	xSPID21					:1;				/* SESPID21 */
			U4	xSPID22					:1;				/* SESPID22 */
			U4	xSPID23					:1;				/* SESPID23 */
			U4	xSPID24					:1;				/* SESPID24 */
			U4	xSPID25					:1;				/* SESPID25 */
			U4	xSPID26					:1;				/* SESPID26 */
			U4	xSPID27					:1;				/* SESPID27 */
			U4	xSPID28					:1;				/* SESPID28 */
			U4	xSPID29					:1;				/* SESPID29 */
			U4	xSPID30					:1;				/* SESPID30 */
			U4	xSPID31					:1;				/* SESPID31 */
		} stBit;
	} unLR0_kSESPID[ECC_BUFFNUM_LRAM];					/* 0xFFC52180 - 0xFFC521A0 */

}	Reg_Ecc_MeccCap_Lr_Pe0Cl0Type;


/* MECCCAP_LR_PE1CL0 */
/* ============================================================================ */
/* ============================ Module: MECCCAP_LR_PE1CL0 ===================== */
/* ============================================================================ */
typedef	struct											/* MECCCAP_LR_PE1CL0 */
{
	union												/* LR0_ERRINT */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDIE					:1;				/* SEDIE */
			U4	xDEDIE					:1;				/* DEDIE */
			U4	xDummy1					:1;
			U4	xAFEIE					:1;				/* AFEIE */
			U4	b3Dummy2				:3;
			U4	xSEOVFIE				:1;				/* SEOVFIE */
			U4	b24Dummy3				:24;
		} stBit;
	} unLR0_ERRINT;										/* 0xFFC52200 - 0xFFC52204 */

	U1	u1Dummy1[0xFFC52210U - 0xFFC52204U];			/* 0xFFC52204 - 0xFFC52210 */

	union												/* LR0_SSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSSTCLR00				:1;				/* SSTCLR00 */
			U4	xSSTCLR01				:1;				/* SSTCLR01 */
			U4	xSSTCLR02				:1;				/* SSTCLR02 */
			U4	xSSTCLR03				:1;				/* SSTCLR03 */
			U4	xSSTCLR04				:1;				/* SSTCLR04 */
			U4	xSSTCLR05				:1;				/* SSTCLR05 */
			U4	xSSTCLR06				:1;				/* SSTCLR06 */
			U4	xSSTCLR07				:1;				/* SSTCLR07 */
			U4	b24Dummy1				:24;
		} stBit;
	} unLR0_SSTCLR;										/* 0xFFC52210 - 0xFFC52214 */

	union												/* LR0_DSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDSTCLR00				:1;				/* DSTCLR00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unLR0_DSTCLR;										/* 0xFFC52214 - 0xFFC52218 */

	union												/* LR0_OVFCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSERROVFCLR0			:1;				/* SERROVFCLR0 */
			U4	xSERROVFCLR1			:1;				/* SERROVFCLR1 */
			U4	b30Dummy1				:30;
		} stBit;
	} unLR0_OVFCLR;										/* 0xFFC52218 - 0xFFC5221C */

	U1	u1Dummy2[0xFFC52220U - 0xFFC5221CU];			/* 0xFFC5221C - 0xFFC52220 */

	union												/* LR0_SERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDF00					:1;				/* SEDF00 */
			U4	xSEDF01					:1;				/* SEDF01 */
			U4	xSEDF02					:1;				/* SEDF02 */
			U4	xSEDF03					:1;				/* SEDF03 */
			U4	xSEDF04					:1;				/* SEDF04 */
			U4	xSEDF05					:1;				/* SEDF05 */
			U4	xSEDF06					:1;				/* SEDF06 */
			U4	xSEDF07					:1;				/* SEDF07 */
			U4	b24Dummy1				:24;
		} stBit;
	} unLR0_SERSTR;										/* 0xFFC52220 - 0xFFC52224 */

	union												/* LR0_DERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDummy1					:1;
			U4	xDEDF00					:1;				/* DEDF00 */
			U4	xDummy2					:1;
			U4	xAFEF00					:1;				/* AFEF00 */
			U4	b28Dummy3				:28;
		} stBit;
	} unLR0_DERSTR;										/* 0xFFC52224 - 0xFFC52228 */

	union												/* LR0_OVFSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSERROVF0				:1;				/* SERROVF0 */
			U4	xSERROVF1				:1;				/* SERROVF1 */
			U4	b30Dummy1				:30;
		} stBit;
	} unLR0_OVFSTR;										/* 0xFFC52228 - 0xFFC5222C */

	U1	u1Dummy3[0xFFC52230U - 0xFFC5222CU];			/* 0xFFC5222C - 0xFFC52230 */

	union												/* LR0_SERINF */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDLINF00				:1;				/* SEDLINF00 */
			U4	xSEDLINF01				:1;				/* SEDLINF01 */
			U4	xSEDLINF02				:1;				/* SEDLINF02 */
			U4	xSEDLINF03				:1;				/* SEDLINF03 */
			U4	xSEDLINF04				:1;				/* SEDLINF04 */
			U4	b27Dummy1				:27;
		} stBit;
	} unLR0_SERINF;										/* 0xFFC52230 - 0xFFC52234 */

	U1	u1Dummy4[0xFFC52270U - 0xFFC52234U];			/* 0xFFC52234 - 0xFFC52270 */

	union												/* LR0_nSEADR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b2Dummy1				:2;
			U4	b14SEADR0				:14;			/* SEADR0[15:2] */
			U4	b11Dummy2				:11;
			U4	b5SEDL					:5;				/* SEDL[4:0] */
		} stBit;
	} unLR0_nSEADR[ECC_BUFFNUM_LRAM];					/* 0xFFC52270 - 0xFFC52290 */

	U1	u1Dummy5[0xFFC522F0U - 0xFFC52290U];			/* 0xFFC52290 - 0xFFC522F0 */

	union												/* LR0_00DEADR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b2Dummy1				:2;
			U4	b14DEADR0				:14;			/* DEADR0[15:2] */
			U4	b11Dummy2				:11;
			U4	b5DEDL					:5;				/* DEDL[4:0] */
		} stBit;
	} unLR0_00DEADR;									/* 0xFFC522F0 - 0xFFC522F4 */

	union												/* LR0_00DESPIDCLR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xCLR00					:1;				/* DESPIDCLR00 */
			U4	xCLR01					:1;				/* DESPIDCLR01 */
			U4	xCLR02					:1;				/* DESPIDCLR02 */
			U4	xCLR03					:1;				/* DESPIDCLR03 */
			U4	xCLR04					:1;				/* DESPIDCLR04 */
			U4	xCLR05					:1;				/* DESPIDCLR05 */
			U4	xCLR06					:1;				/* DESPIDCLR06 */
			U4	xCLR07					:1;				/* DESPIDCLR07 */
			U4	xCLR08					:1;				/* DESPIDCLR08 */
			U4	xCLR09					:1;				/* DESPIDCLR09 */
			U4	xCLR10					:1;				/* DESPIDCLR10 */
			U4	xCLR11					:1;				/* DESPIDCLR11 */
			U4	xCLR12					:1;				/* DESPIDCLR12 */
			U4	xCLR13					:1;				/* DESPIDCLR13 */
			U4	xCLR14					:1;				/* DESPIDCLR14 */
			U4	xCLR15					:1;				/* DESPIDCLR15 */
			U4	xCLR16					:1;				/* DESPIDCLR16 */
			U4	xCLR17					:1;				/* DESPIDCLR17 */
			U4	xCLR18					:1;				/* DESPIDCLR18 */
			U4	xCLR19					:1;				/* DESPIDCLR19 */
			U4	xCLR20					:1;				/* DESPIDCLR20 */
			U4	xCLR21					:1;				/* DESPIDCLR21 */
			U4	xCLR22					:1;				/* DESPIDCLR22 */
			U4	xCLR23					:1;				/* DESPIDCLR23 */
			U4	xCLR24					:1;				/* DESPIDCLR24 */
			U4	xCLR25					:1;				/* DESPIDCLR25 */
			U4	xCLR26					:1;				/* DESPIDCLR26 */
			U4	xCLR27					:1;				/* DESPIDCLR27 */
			U4	xCLR28					:1;				/* DESPIDCLR28 */
			U4	xCLR29					:1;				/* DESPIDCLR29 */
			U4	xCLR30					:1;				/* DESPIDCLR30 */
			U4	xCLR31					:1;				/* DESPIDCLR31 */
		} stBit;
	} unLR0_00DESPIDCLR;								/* 0xFFC522F4 - 0xFFC522F8 */

	union												/* LR0_00DESPID */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSPID00					:1;				/* DESPID00 */
			U4	xSPID01					:1;				/* DESPID01 */
			U4	xSPID02					:1;				/* DESPID02 */
			U4	xSPID03					:1;				/* DESPID03 */
			U4	xSPID04					:1;				/* DESPID04 */
			U4	xSPID05					:1;				/* DESPID05 */
			U4	xSPID06					:1;				/* DESPID06 */
			U4	xSPID07					:1;				/* DESPID07 */
			U4	xSPID08					:1;				/* DESPID08 */
			U4	xSPID09					:1;				/* DESPID09 */
			U4	xSPID10					:1;				/* DESPID10 */
			U4	xSPID11					:1;				/* DESPID11 */
			U4	xSPID12					:1;				/* DESPID12 */
			U4	xSPID13					:1;				/* DESPID13 */
			U4	xSPID14					:1;				/* DESPID14 */
			U4	xSPID15					:1;				/* DESPID15 */
			U4	xSPID16					:1;				/* DESPID16 */
			U4	xSPID17					:1;				/* DESPID17 */
			U4	xSPID18					:1;				/* DESPID18 */
			U4	xSPID19					:1;				/* DESPID19 */
			U4	xSPID20					:1;				/* DESPID20 */
			U4	xSPID21					:1;				/* DESPID21 */
			U4	xSPID22					:1;				/* DESPID22 */
			U4	xSPID23					:1;				/* DESPID23 */
			U4	xSPID24					:1;				/* DESPID24 */
			U4	xSPID25					:1;				/* DESPID25 */
			U4	xSPID26					:1;				/* DESPID26 */
			U4	xSPID27					:1;				/* DESPID27 */
			U4	xSPID28					:1;				/* DESPID28 */
			U4	xSPID29					:1;				/* DESPID29 */
			U4	xSPID30					:1;				/* DESPID30 */
			U4	xSPID31					:1;				/* DESPID31 */
		} stBit;
	} unLR0_00DESPID;									/* 0xFFC522F8 - 0xFFC522FC */

	U1	u1Dummy6[0xFFC52300U - 0xFFC522FCU];			/* 0xFFC522FC - 0xFFC52300 */

	union												/* LR0_kSESPIDCLR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xCLR00					:1;				/* SESPIDCLR00 */
			U4	xCLR01					:1;				/* SESPIDCLR01 */
			U4	xCLR02					:1;				/* SESPIDCLR02 */
			U4	xCLR03					:1;				/* SESPIDCLR03 */
			U4	xCLR04					:1;				/* SESPIDCLR04 */
			U4	xCLR05					:1;				/* SESPIDCLR05 */
			U4	xCLR06					:1;				/* SESPIDCLR06 */
			U4	xCLR07					:1;				/* SESPIDCLR07 */
			U4	xCLR08					:1;				/* SESPIDCLR08 */
			U4	xCLR09					:1;				/* SESPIDCLR09 */
			U4	xCLR10					:1;				/* SESPIDCLR10 */
			U4	xCLR11					:1;				/* SESPIDCLR11 */
			U4	xCLR12					:1;				/* SESPIDCLR12 */
			U4	xCLR13					:1;				/* SESPIDCLR13 */
			U4	xCLR14					:1;				/* SESPIDCLR14 */
			U4	xCLR15					:1;				/* SESPIDCLR15 */
			U4	xCLR16					:1;				/* SESPIDCLR16 */
			U4	xCLR17					:1;				/* SESPIDCLR17 */
			U4	xCLR18					:1;				/* SESPIDCLR18 */
			U4	xCLR19					:1;				/* SESPIDCLR19 */
			U4	xCLR20					:1;				/* SESPIDCLR20 */
			U4	xCLR21					:1;				/* SESPIDCLR21 */
			U4	xCLR22					:1;				/* SESPIDCLR22 */
			U4	xCLR23					:1;				/* SESPIDCLR23 */
			U4	xCLR24					:1;				/* SESPIDCLR24 */
			U4	xCLR25					:1;				/* SESPIDCLR25 */
			U4	xCLR26					:1;				/* SESPIDCLR26 */
			U4	xCLR27					:1;				/* SESPIDCLR27 */
			U4	xCLR28					:1;				/* SESPIDCLR28 */
			U4	xCLR29					:1;				/* SESPIDCLR29 */
			U4	xCLR30					:1;				/* SESPIDCLR30 */
			U4	xCLR31					:1;				/* SESPIDCLR31 */
		} stBit;
	} unLR0_kSESPIDCLR[ECC_BUFFNUM_LRAM];				/* 0xFFC52300 - 0xFFC52320 */

	U1	u1Dummy7[0xFFC52380U - 0xFFC52320U];			/* 0xFFC52320 - 0xFFC52380 */

	union												/* LR0_kSESPID */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSPID00					:1;				/* SESPID00 */
			U4	xSPID01					:1;				/* SESPID01 */
			U4	xSPID02					:1;				/* SESPID02 */
			U4	xSPID03					:1;				/* SESPID03 */
			U4	xSPID04					:1;				/* SESPID04 */
			U4	xSPID05					:1;				/* SESPID05 */
			U4	xSPID06					:1;				/* SESPID06 */
			U4	xSPID07					:1;				/* SESPID07 */
			U4	xSPID08					:1;				/* SESPID08 */
			U4	xSPID09					:1;				/* SESPID09 */
			U4	xSPID10					:1;				/* SESPID10 */
			U4	xSPID11					:1;				/* SESPID11 */
			U4	xSPID12					:1;				/* SESPID12 */
			U4	xSPID13					:1;				/* SESPID13 */
			U4	xSPID14					:1;				/* SESPID14 */
			U4	xSPID15					:1;				/* SESPID15 */
			U4	xSPID16					:1;				/* SESPID16 */
			U4	xSPID17					:1;				/* SESPID17 */
			U4	xSPID18					:1;				/* SESPID18 */
			U4	xSPID19					:1;				/* SESPID19 */
			U4	xSPID20					:1;				/* SESPID20 */
			U4	xSPID21					:1;				/* SESPID21 */
			U4	xSPID22					:1;				/* SESPID22 */
			U4	xSPID23					:1;				/* SESPID23 */
			U4	xSPID24					:1;				/* SESPID24 */
			U4	xSPID25					:1;				/* SESPID25 */
			U4	xSPID26					:1;				/* SESPID26 */
			U4	xSPID27					:1;				/* SESPID27 */
			U4	xSPID28					:1;				/* SESPID28 */
			U4	xSPID29					:1;				/* SESPID29 */
			U4	xSPID30					:1;				/* SESPID30 */
			U4	xSPID31					:1;				/* SESPID31 */
		} stBit;
	} unLR0_kSESPID[ECC_BUFFNUM_LRAM];					/* 0xFFC52380 - 0xFFC523A0 */

}	Reg_Ecc_MeccCap_Lr_Pe1Cl0Type;


/* MECCCAP_LR_PE2CL1 */
/* ============================================================================ */
/* ============================ Module: MECCCAP_LR_PE2CL1 ===================== */
/* ============================================================================ */
typedef	struct											/* MECCCAP_LR_PE2CL1 */
{
	union												/* LR0_ERRINT */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDIE					:1;				/* SEDIE */
			U4	xDEDIE					:1;				/* DEDIE */
			U4	xDummy1					:1;
			U4	xAFEIE					:1;				/* AFEIE */
			U4	b3Dummy2				:3;
			U4	xSEOVFIE				:1;				/* SEOVFIE */
			U4	b24Dummy3				:24;
		} stBit;
	} unLR0_ERRINT;										/* 0xFFC52400 - 0xFFC52404 */

	U1	u1Dummy1[0xFFC52410U - 0xFFC52404U];			/* 0xFFC52404 - 0xFFC52410 */

	union												/* LR0_SSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSSTCLR00				:1;				/* SSTCLR00 */
			U4	xSSTCLR01				:1;				/* SSTCLR01 */
			U4	xSSTCLR02				:1;				/* SSTCLR02 */
			U4	xSSTCLR03				:1;				/* SSTCLR03 */
			U4	xSSTCLR04				:1;				/* SSTCLR04 */
			U4	xSSTCLR05				:1;				/* SSTCLR05 */
			U4	xSSTCLR06				:1;				/* SSTCLR06 */
			U4	xSSTCLR07				:1;				/* SSTCLR07 */
			U4	b24Dummy1				:24;
		} stBit;
	} unLR0_SSTCLR;										/* 0xFFC52410 - 0xFFC52414 */

	union												/* LR0_DSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDSTCLR00				:1;				/* DSTCLR00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unLR0_DSTCLR;										/* 0xFFC52414 - 0xFFC52418 */

	union												/* LR0_OVFCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSERROVFCLR0			:1;				/* SERROVFCLR0 */
			U4	xSERROVFCLR1			:1;				/* SERROVFCLR1 */
			U4	b30Dummy1				:30;
		} stBit;
	} unLR0_OVFCLR;										/* 0xFFC52418 - 0xFFC5241C */

	U1	u1Dummy2[0xFFC52420U - 0xFFC5241CU];			/* 0xFFC5241C - 0xFFC52420 */

	union												/* LR0_SERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDF00					:1;				/* SEDF00 */
			U4	xSEDF01					:1;				/* SEDF01 */
			U4	xSEDF02					:1;				/* SEDF02 */
			U4	xSEDF03					:1;				/* SEDF03 */
			U4	xSEDF04					:1;				/* SEDF04 */
			U4	xSEDF05					:1;				/* SEDF05 */
			U4	xSEDF06					:1;				/* SEDF06 */
			U4	xSEDF07					:1;				/* SEDF07 */
			U4	b24Dummy1				:24;
		} stBit;
	} unLR0_SERSTR;										/* 0xFFC52420 - 0xFFC52424 */

	union												/* LR0_DERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDummy1					:1;
			U4	xDEDF00					:1;				/* DEDF00 */
			U4	xDummy2					:1;
			U4	xAFEF00					:1;				/* AFEF00 */
			U4	b28Dummy3				:28;
		} stBit;
	} unLR0_DERSTR;										/* 0xFFC52424 - 0xFFC52428 */

	union												/* LR0_OVFSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSERROVF0				:1;				/* SERROVF0 */
			U4	xSERROVF1				:1;				/* SERROVF1 */
			U4	b30Dummy1				:30;
		} stBit;
	} unLR0_OVFSTR;										/* 0xFFC52428 - 0xFFC5242C */

	U1	u1Dummy3[0xFFC52430U - 0xFFC5242CU];			/* 0xFFC5242C - 0xFFC52430 */

	union												/* LR0_SERINF */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDLINF00				:1;				/* SEDLINF00 */
			U4	xSEDLINF01				:1;				/* SEDLINF01 */
			U4	xSEDLINF02				:1;				/* SEDLINF02 */
			U4	xSEDLINF03				:1;				/* SEDLINF03 */
			U4	xSEDLINF04				:1;				/* SEDLINF04 */
			U4	b27Dummy1				:27;
		} stBit;
	} unLR0_SERINF;										/* 0xFFC52430 - 0xFFC52434 */

	U1	u1Dummy4[0xFFC52470U - 0xFFC52434U];			/* 0xFFC52434 - 0xFFC52470 */

	union												/* LR0_nSEADR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b2Dummy1				:2;
			U4	b14SEADR0				:14;			/* SEADR0[15:2] */
			U4	b11Dummy2				:11;
			U4	b5SEDL					:5;				/* SEDL[4:0] */
		} stBit;
	} unLR0_nSEADR[ECC_BUFFNUM_LRAM];					/* 0xFFC52470 - 0xFFC52490 */

	U1	u1Dummy5[0xFFC524F0U - 0xFFC52490U];			/* 0xFFC52490 - 0xFFC524F0 */

	union												/* LR0_00DEADR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b2Dummy1				:2;
			U4	b14DEADR0				:14;			/* DEADR0[15:2] */
			U4	b11Dummy2				:11;
			U4	b5DEDL					:5;				/* DEDL[4:0] */
		} stBit;
	} unLR0_00DEADR;									/* 0xFFC524F0 - 0xFFC524F4 */

	union												/* LR0_00DESPIDCLR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xCLR00					:1;				/* DESPIDCLR00 */
			U4	xCLR01					:1;				/* DESPIDCLR01 */
			U4	xCLR02					:1;				/* DESPIDCLR02 */
			U4	xCLR03					:1;				/* DESPIDCLR03 */
			U4	xCLR04					:1;				/* DESPIDCLR04 */
			U4	xCLR05					:1;				/* DESPIDCLR05 */
			U4	xCLR06					:1;				/* DESPIDCLR06 */
			U4	xCLR07					:1;				/* DESPIDCLR07 */
			U4	xCLR08					:1;				/* DESPIDCLR08 */
			U4	xCLR09					:1;				/* DESPIDCLR09 */
			U4	xCLR10					:1;				/* DESPIDCLR10 */
			U4	xCLR11					:1;				/* DESPIDCLR11 */
			U4	xCLR12					:1;				/* DESPIDCLR12 */
			U4	xCLR13					:1;				/* DESPIDCLR13 */
			U4	xCLR14					:1;				/* DESPIDCLR14 */
			U4	xCLR15					:1;				/* DESPIDCLR15 */
			U4	xCLR16					:1;				/* DESPIDCLR16 */
			U4	xCLR17					:1;				/* DESPIDCLR17 */
			U4	xCLR18					:1;				/* DESPIDCLR18 */
			U4	xCLR19					:1;				/* DESPIDCLR19 */
			U4	xCLR20					:1;				/* DESPIDCLR20 */
			U4	xCLR21					:1;				/* DESPIDCLR21 */
			U4	xCLR22					:1;				/* DESPIDCLR22 */
			U4	xCLR23					:1;				/* DESPIDCLR23 */
			U4	xCLR24					:1;				/* DESPIDCLR24 */
			U4	xCLR25					:1;				/* DESPIDCLR25 */
			U4	xCLR26					:1;				/* DESPIDCLR26 */
			U4	xCLR27					:1;				/* DESPIDCLR27 */
			U4	xCLR28					:1;				/* DESPIDCLR28 */
			U4	xCLR29					:1;				/* DESPIDCLR29 */
			U4	xCLR30					:1;				/* DESPIDCLR30 */
			U4	xCLR31					:1;				/* DESPIDCLR31 */
		} stBit;
	} unLR0_00DESPIDCLR;								/* 0xFFC524F4 - 0xFFC524F8 */

	union												/* LR0_00DESPID */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSPID00					:1;				/* DESPID00 */
			U4	xSPID01					:1;				/* DESPID01 */
			U4	xSPID02					:1;				/* DESPID02 */
			U4	xSPID03					:1;				/* DESPID03 */
			U4	xSPID04					:1;				/* DESPID04 */
			U4	xSPID05					:1;				/* DESPID05 */
			U4	xSPID06					:1;				/* DESPID06 */
			U4	xSPID07					:1;				/* DESPID07 */
			U4	xSPID08					:1;				/* DESPID08 */
			U4	xSPID09					:1;				/* DESPID09 */
			U4	xSPID10					:1;				/* DESPID10 */
			U4	xSPID11					:1;				/* DESPID11 */
			U4	xSPID12					:1;				/* DESPID12 */
			U4	xSPID13					:1;				/* DESPID13 */
			U4	xSPID14					:1;				/* DESPID14 */
			U4	xSPID15					:1;				/* DESPID15 */
			U4	xSPID16					:1;				/* DESPID16 */
			U4	xSPID17					:1;				/* DESPID17 */
			U4	xSPID18					:1;				/* DESPID18 */
			U4	xSPID19					:1;				/* DESPID19 */
			U4	xSPID20					:1;				/* DESPID20 */
			U4	xSPID21					:1;				/* DESPID21 */
			U4	xSPID22					:1;				/* DESPID22 */
			U4	xSPID23					:1;				/* DESPID23 */
			U4	xSPID24					:1;				/* DESPID24 */
			U4	xSPID25					:1;				/* DESPID25 */
			U4	xSPID26					:1;				/* DESPID26 */
			U4	xSPID27					:1;				/* DESPID27 */
			U4	xSPID28					:1;				/* DESPID28 */
			U4	xSPID29					:1;				/* DESPID29 */
			U4	xSPID30					:1;				/* DESPID30 */
			U4	xSPID31					:1;				/* DESPID31 */
		} stBit;
	} unLR0_00DESPID;									/* 0xFFC524F8 - 0xFFC524FC */

	U1	u1Dummy6[0xFFC52500U - 0xFFC524FCU];			/* 0xFFC524FC - 0xFFC52500 */

	union												/* LR0_kSESPIDCLR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xCLR00					:1;				/* SESPIDCLR00 */
			U4	xCLR01					:1;				/* SESPIDCLR01 */
			U4	xCLR02					:1;				/* SESPIDCLR02 */
			U4	xCLR03					:1;				/* SESPIDCLR03 */
			U4	xCLR04					:1;				/* SESPIDCLR04 */
			U4	xCLR05					:1;				/* SESPIDCLR05 */
			U4	xCLR06					:1;				/* SESPIDCLR06 */
			U4	xCLR07					:1;				/* SESPIDCLR07 */
			U4	xCLR08					:1;				/* SESPIDCLR08 */
			U4	xCLR09					:1;				/* SESPIDCLR09 */
			U4	xCLR10					:1;				/* SESPIDCLR10 */
			U4	xCLR11					:1;				/* SESPIDCLR11 */
			U4	xCLR12					:1;				/* SESPIDCLR12 */
			U4	xCLR13					:1;				/* SESPIDCLR13 */
			U4	xCLR14					:1;				/* SESPIDCLR14 */
			U4	xCLR15					:1;				/* SESPIDCLR15 */
			U4	xCLR16					:1;				/* SESPIDCLR16 */
			U4	xCLR17					:1;				/* SESPIDCLR17 */
			U4	xCLR18					:1;				/* SESPIDCLR18 */
			U4	xCLR19					:1;				/* SESPIDCLR19 */
			U4	xCLR20					:1;				/* SESPIDCLR20 */
			U4	xCLR21					:1;				/* SESPIDCLR21 */
			U4	xCLR22					:1;				/* SESPIDCLR22 */
			U4	xCLR23					:1;				/* SESPIDCLR23 */
			U4	xCLR24					:1;				/* SESPIDCLR24 */
			U4	xCLR25					:1;				/* SESPIDCLR25 */
			U4	xCLR26					:1;				/* SESPIDCLR26 */
			U4	xCLR27					:1;				/* SESPIDCLR27 */
			U4	xCLR28					:1;				/* SESPIDCLR28 */
			U4	xCLR29					:1;				/* SESPIDCLR29 */
			U4	xCLR30					:1;				/* SESPIDCLR30 */
			U4	xCLR31					:1;				/* SESPIDCLR31 */
		} stBit;
	} unLR0_kSESPIDCLR[ECC_BUFFNUM_LRAM];				/* 0xFFC52500 - 0xFFC52520 */

	U1	u1Dummy7[0xFFC52580U - 0xFFC52520U];			/* 0xFFC52520 - 0xFFC52580 */

	union												/* LR0_kSESPID */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSPID00					:1;				/* SESPID00 */
			U4	xSPID01					:1;				/* SESPID01 */
			U4	xSPID02					:1;				/* SESPID02 */
			U4	xSPID03					:1;				/* SESPID03 */
			U4	xSPID04					:1;				/* SESPID04 */
			U4	xSPID05					:1;				/* SESPID05 */
			U4	xSPID06					:1;				/* SESPID06 */
			U4	xSPID07					:1;				/* SESPID07 */
			U4	xSPID08					:1;				/* SESPID08 */
			U4	xSPID09					:1;				/* SESPID09 */
			U4	xSPID10					:1;				/* SESPID10 */
			U4	xSPID11					:1;				/* SESPID11 */
			U4	xSPID12					:1;				/* SESPID12 */
			U4	xSPID13					:1;				/* SESPID13 */
			U4	xSPID14					:1;				/* SESPID14 */
			U4	xSPID15					:1;				/* SESPID15 */
			U4	xSPID16					:1;				/* SESPID16 */
			U4	xSPID17					:1;				/* SESPID17 */
			U4	xSPID18					:1;				/* SESPID18 */
			U4	xSPID19					:1;				/* SESPID19 */
			U4	xSPID20					:1;				/* SESPID20 */
			U4	xSPID21					:1;				/* SESPID21 */
			U4	xSPID22					:1;				/* SESPID22 */
			U4	xSPID23					:1;				/* SESPID23 */
			U4	xSPID24					:1;				/* SESPID24 */
			U4	xSPID25					:1;				/* SESPID25 */
			U4	xSPID26					:1;				/* SESPID26 */
			U4	xSPID27					:1;				/* SESPID27 */
			U4	xSPID28					:1;				/* SESPID28 */
			U4	xSPID29					:1;				/* SESPID29 */
			U4	xSPID30					:1;				/* SESPID30 */
			U4	xSPID31					:1;				/* SESPID31 */
		} stBit;
	} unLR0_kSESPID[ECC_BUFFNUM_LRAM];					/* 0xFFC52580 - 0xFFC525A0 */

}	Reg_Ecc_MeccCap_Lr_Pe2Cl1Type;


/* MECCCAP_LR_PE3CL1 */
/* ============================================================================ */
/* ============================ Module: MECCCAP_LR_PE3CL1 ===================== */
/* ============================================================================ */
typedef	struct											/* MECCCAP_LR_PE3CL1 */
{
	union												/* LR0_ERRINT */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDIE					:1;				/* SEDIE */
			U4	xDEDIE					:1;				/* DEDIE */
			U4	xDummy1					:1;
			U4	xAFEIE					:1;				/* AFEIE */
			U4	b3Dummy2				:3;
			U4	xSEOVFIE				:1;				/* SEOVFIE */
			U4	b24Dummy3				:24;
		} stBit;
	} unLR0_ERRINT;										/* 0xFFC52600 - 0xFFC52604 */

	U1	u1Dummy1[0xFFC52610U - 0xFFC52604U];			/* 0xFFC52604 - 0xFFC52610 */

	union												/* LR0_SSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSSTCLR00				:1;				/* SSTCLR00 */
			U4	xSSTCLR01				:1;				/* SSTCLR01 */
			U4	xSSTCLR02				:1;				/* SSTCLR02 */
			U4	xSSTCLR03				:1;				/* SSTCLR03 */
			U4	xSSTCLR04				:1;				/* SSTCLR04 */
			U4	xSSTCLR05				:1;				/* SSTCLR05 */
			U4	xSSTCLR06				:1;				/* SSTCLR06 */
			U4	xSSTCLR07				:1;				/* SSTCLR07 */
			U4	b24Dummy1				:24;
		} stBit;
	} unLR0_SSTCLR;										/* 0xFFC52610 - 0xFFC52614 */

	union												/* LR0_DSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDSTCLR00				:1;				/* DSTCLR00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unLR0_DSTCLR;										/* 0xFFC52614 - 0xFFC52618 */

	union												/* LR0_OVFCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSERROVFCLR0			:1;				/* SERROVFCLR0 */
			U4	xSERROVFCLR1			:1;				/* SERROVFCLR1 */
			U4	b30Dummy1				:30;
		} stBit;
	} unLR0_OVFCLR;										/* 0xFFC52618 - 0xFFC5261C */

	U1	u1Dummy2[0xFFC52620U - 0xFFC5261CU];			/* 0xFFC5261C - 0xFFC52620 */

	union												/* LR0_SERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDF00					:1;				/* SEDF00 */
			U4	xSEDF01					:1;				/* SEDF01 */
			U4	xSEDF02					:1;				/* SEDF02 */
			U4	xSEDF03					:1;				/* SEDF03 */
			U4	xSEDF04					:1;				/* SEDF04 */
			U4	xSEDF05					:1;				/* SEDF05 */
			U4	xSEDF06					:1;				/* SEDF06 */
			U4	xSEDF07					:1;				/* SEDF07 */
			U4	b24Dummy1				:24;
		} stBit;
	} unLR0_SERSTR;										/* 0xFFC52620 - 0xFFC52624 */

	union												/* LR0_DERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDummy1					:1;
			U4	xDEDF00					:1;				/* DEDF00 */
			U4	xDummy2					:1;
			U4	xAFEF00					:1;				/* AFEF00 */
			U4	b28Dummy3				:28;
		} stBit;
	} unLR0_DERSTR;										/* 0xFFC52624 - 0xFFC52628 */

	union												/* LR0_OVFSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSERROVF0				:1;				/* SERROVF0 */
			U4	xSERROVF1				:1;				/* SERROVF1 */
			U4	b30Dummy1				:30;
		} stBit;
	} unLR0_OVFSTR;										/* 0xFFC52628 - 0xFFC5262C */

	U1	u1Dummy3[0xFFC52630U - 0xFFC5262CU];			/* 0xFFC5262C - 0xFFC52630 */

	union												/* LR0_SERINF */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDLINF00				:1;				/* SEDLINF00 */
			U4	xSEDLINF01				:1;				/* SEDLINF01 */
			U4	xSEDLINF02				:1;				/* SEDLINF02 */
			U4	xSEDLINF03				:1;				/* SEDLINF03 */
			U4	xSEDLINF04				:1;				/* SEDLINF04 */
			U4	b27Dummy1				:27;
		} stBit;
	} unLR0_SERINF;										/* 0xFFC52630 - 0xFFC52634 */

	U1	u1Dummy4[0xFFC52670U - 0xFFC52634U];			/* 0xFFC52634 - 0xFFC52670 */

	union												/* LR0_nSEADR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b2Dummy1				:2;
			U4	b14SEADR0				:14;			/* SEADR0[15:2] */
			U4	b11Dummy2				:11;
			U4	b5SEDL					:5;				/* SEDL[4:0] */
		} stBit;
	} unLR0_nSEADR[ECC_BUFFNUM_LRAM];					/* 0xFFC52670 - 0xFFC52690 */

	U1	u1Dummy5[0xFFC526F0U - 0xFFC52690U];			/* 0xFFC52690 - 0xFFC526F0 */

	union												/* LR0_00DEADR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b2Dummy1				:2;
			U4	b14DEADR0				:14;			/* DEADR0[15:2] */
			U4	b11Dummy2				:11;
			U4	b5DEDL					:5;				/* DEDL[4:0] */
		} stBit;
	} unLR0_00DEADR;									/* 0xFFC526F0 - 0xFFC526F4 */

	union												/* LR0_00DESPIDCLR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xCLR00					:1;				/* DESPIDCLR00 */
			U4	xCLR01					:1;				/* DESPIDCLR01 */
			U4	xCLR02					:1;				/* DESPIDCLR02 */
			U4	xCLR03					:1;				/* DESPIDCLR03 */
			U4	xCLR04					:1;				/* DESPIDCLR04 */
			U4	xCLR05					:1;				/* DESPIDCLR05 */
			U4	xCLR06					:1;				/* DESPIDCLR06 */
			U4	xCLR07					:1;				/* DESPIDCLR07 */
			U4	xCLR08					:1;				/* DESPIDCLR08 */
			U4	xCLR09					:1;				/* DESPIDCLR09 */
			U4	xCLR10					:1;				/* DESPIDCLR10 */
			U4	xCLR11					:1;				/* DESPIDCLR11 */
			U4	xCLR12					:1;				/* DESPIDCLR12 */
			U4	xCLR13					:1;				/* DESPIDCLR13 */
			U4	xCLR14					:1;				/* DESPIDCLR14 */
			U4	xCLR15					:1;				/* DESPIDCLR15 */
			U4	xCLR16					:1;				/* DESPIDCLR16 */
			U4	xCLR17					:1;				/* DESPIDCLR17 */
			U4	xCLR18					:1;				/* DESPIDCLR18 */
			U4	xCLR19					:1;				/* DESPIDCLR19 */
			U4	xCLR20					:1;				/* DESPIDCLR20 */
			U4	xCLR21					:1;				/* DESPIDCLR21 */
			U4	xCLR22					:1;				/* DESPIDCLR22 */
			U4	xCLR23					:1;				/* DESPIDCLR23 */
			U4	xCLR24					:1;				/* DESPIDCLR24 */
			U4	xCLR25					:1;				/* DESPIDCLR25 */
			U4	xCLR26					:1;				/* DESPIDCLR26 */
			U4	xCLR27					:1;				/* DESPIDCLR27 */
			U4	xCLR28					:1;				/* DESPIDCLR28 */
			U4	xCLR29					:1;				/* DESPIDCLR29 */
			U4	xCLR30					:1;				/* DESPIDCLR30 */
			U4	xCLR31					:1;				/* DESPIDCLR31 */
		} stBit;
	} unLR0_00DESPIDCLR;								/* 0xFFC526F4 - 0xFFC526F8 */

	union												/* LR0_00DESPID */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSPID00					:1;				/* DESPID00 */
			U4	xSPID01					:1;				/* DESPID01 */
			U4	xSPID02					:1;				/* DESPID02 */
			U4	xSPID03					:1;				/* DESPID03 */
			U4	xSPID04					:1;				/* DESPID04 */
			U4	xSPID05					:1;				/* DESPID05 */
			U4	xSPID06					:1;				/* DESPID06 */
			U4	xSPID07					:1;				/* DESPID07 */
			U4	xSPID08					:1;				/* DESPID08 */
			U4	xSPID09					:1;				/* DESPID09 */
			U4	xSPID10					:1;				/* DESPID10 */
			U4	xSPID11					:1;				/* DESPID11 */
			U4	xSPID12					:1;				/* DESPID12 */
			U4	xSPID13					:1;				/* DESPID13 */
			U4	xSPID14					:1;				/* DESPID14 */
			U4	xSPID15					:1;				/* DESPID15 */
			U4	xSPID16					:1;				/* DESPID16 */
			U4	xSPID17					:1;				/* DESPID17 */
			U4	xSPID18					:1;				/* DESPID18 */
			U4	xSPID19					:1;				/* DESPID19 */
			U4	xSPID20					:1;				/* DESPID20 */
			U4	xSPID21					:1;				/* DESPID21 */
			U4	xSPID22					:1;				/* DESPID22 */
			U4	xSPID23					:1;				/* DESPID23 */
			U4	xSPID24					:1;				/* DESPID24 */
			U4	xSPID25					:1;				/* DESPID25 */
			U4	xSPID26					:1;				/* DESPID26 */
			U4	xSPID27					:1;				/* DESPID27 */
			U4	xSPID28					:1;				/* DESPID28 */
			U4	xSPID29					:1;				/* DESPID29 */
			U4	xSPID30					:1;				/* DESPID30 */
			U4	xSPID31					:1;				/* DESPID31 */
		} stBit;
	} unLR0_00DESPID;									/* 0xFFC526F8 - 0xFFC526FC */

	U1	u1Dummy6[0xFFC52700U - 0xFFC526FCU];			/* 0xFFC526FC - 0xFFC52700 */

	union												/* LR0_kSESPIDCLR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xCLR00					:1;				/* SESPIDCLR00 */
			U4	xCLR01					:1;				/* SESPIDCLR01 */
			U4	xCLR02					:1;				/* SESPIDCLR02 */
			U4	xCLR03					:1;				/* SESPIDCLR03 */
			U4	xCLR04					:1;				/* SESPIDCLR04 */
			U4	xCLR05					:1;				/* SESPIDCLR05 */
			U4	xCLR06					:1;				/* SESPIDCLR06 */
			U4	xCLR07					:1;				/* SESPIDCLR07 */
			U4	xCLR08					:1;				/* SESPIDCLR08 */
			U4	xCLR09					:1;				/* SESPIDCLR09 */
			U4	xCLR10					:1;				/* SESPIDCLR10 */
			U4	xCLR11					:1;				/* SESPIDCLR11 */
			U4	xCLR12					:1;				/* SESPIDCLR12 */
			U4	xCLR13					:1;				/* SESPIDCLR13 */
			U4	xCLR14					:1;				/* SESPIDCLR14 */
			U4	xCLR15					:1;				/* SESPIDCLR15 */
			U4	xCLR16					:1;				/* SESPIDCLR16 */
			U4	xCLR17					:1;				/* SESPIDCLR17 */
			U4	xCLR18					:1;				/* SESPIDCLR18 */
			U4	xCLR19					:1;				/* SESPIDCLR19 */
			U4	xCLR20					:1;				/* SESPIDCLR20 */
			U4	xCLR21					:1;				/* SESPIDCLR21 */
			U4	xCLR22					:1;				/* SESPIDCLR22 */
			U4	xCLR23					:1;				/* SESPIDCLR23 */
			U4	xCLR24					:1;				/* SESPIDCLR24 */
			U4	xCLR25					:1;				/* SESPIDCLR25 */
			U4	xCLR26					:1;				/* SESPIDCLR26 */
			U4	xCLR27					:1;				/* SESPIDCLR27 */
			U4	xCLR28					:1;				/* SESPIDCLR28 */
			U4	xCLR29					:1;				/* SESPIDCLR29 */
			U4	xCLR30					:1;				/* SESPIDCLR30 */
			U4	xCLR31					:1;				/* SESPIDCLR31 */
		} stBit;
	} unLR0_kSESPIDCLR[ECC_BUFFNUM_LRAM];				/* 0xFFC52700 - 0xFFC52720 */

	U1	u1Dummy7[0xFFC52780U - 0xFFC52720U];			/* 0xFFC52720 - 0xFFC52780 */

	union												/* LR0_kSESPID */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSPID00					:1;				/* SESPID00 */
			U4	xSPID01					:1;				/* SESPID01 */
			U4	xSPID02					:1;				/* SESPID02 */
			U4	xSPID03					:1;				/* SESPID03 */
			U4	xSPID04					:1;				/* SESPID04 */
			U4	xSPID05					:1;				/* SESPID05 */
			U4	xSPID06					:1;				/* SESPID06 */
			U4	xSPID07					:1;				/* SESPID07 */
			U4	xSPID08					:1;				/* SESPID08 */
			U4	xSPID09					:1;				/* SESPID09 */
			U4	xSPID10					:1;				/* SESPID10 */
			U4	xSPID11					:1;				/* SESPID11 */
			U4	xSPID12					:1;				/* SESPID12 */
			U4	xSPID13					:1;				/* SESPID13 */
			U4	xSPID14					:1;				/* SESPID14 */
			U4	xSPID15					:1;				/* SESPID15 */
			U4	xSPID16					:1;				/* SESPID16 */
			U4	xSPID17					:1;				/* SESPID17 */
			U4	xSPID18					:1;				/* SESPID18 */
			U4	xSPID19					:1;				/* SESPID19 */
			U4	xSPID20					:1;				/* SESPID20 */
			U4	xSPID21					:1;				/* SESPID21 */
			U4	xSPID22					:1;				/* SESPID22 */
			U4	xSPID23					:1;				/* SESPID23 */
			U4	xSPID24					:1;				/* SESPID24 */
			U4	xSPID25					:1;				/* SESPID25 */
			U4	xSPID26					:1;				/* SESPID26 */
			U4	xSPID27					:1;				/* SESPID27 */
			U4	xSPID28					:1;				/* SESPID28 */
			U4	xSPID29					:1;				/* SESPID29 */
			U4	xSPID30					:1;				/* SESPID30 */
			U4	xSPID31					:1;				/* SESPID31 */
		} stBit;
	} unLR0_kSESPID[ECC_BUFFNUM_LRAM];					/* 0xFFC52780 - 0xFFC527A0 */

}	Reg_Ecc_MeccCap_Lr_Pe3Cl1Type;


/* MECCCAP_LR_PE4CL2 */
/* ============================================================================ */
/* ============================ Module: MECCCAP_LR_PE4CL2 ===================== */
/* ============================================================================ */
typedef	struct											/* MECCCAP_LR_PE4CL2 */
{
	union												/* LR0_ERRINT */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDIE					:1;				/* SEDIE */
			U4	xDEDIE					:1;				/* DEDIE */
			U4	xDummy1					:1;
			U4	xAFEIE					:1;				/* AFEIE */
			U4	b3Dummy2				:3;
			U4	xSEOVFIE				:1;				/* SEOVFIE */
			U4	b24Dummy3				:24;
		} stBit;
	} unLR0_ERRINT;										/* 0xFFC52800 - 0xFFC52804 */

	U1	u1Dummy1[0xFFC52810U - 0xFFC52804U];			/* 0xFFC52804 - 0xFFC52810 */

	union												/* LR0_SSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSSTCLR00				:1;				/* SSTCLR00 */
			U4	xSSTCLR01				:1;				/* SSTCLR01 */
			U4	xSSTCLR02				:1;				/* SSTCLR02 */
			U4	xSSTCLR03				:1;				/* SSTCLR03 */
			U4	xSSTCLR04				:1;				/* SSTCLR04 */
			U4	xSSTCLR05				:1;				/* SSTCLR05 */
			U4	xSSTCLR06				:1;				/* SSTCLR06 */
			U4	xSSTCLR07				:1;				/* SSTCLR07 */
			U4	b24Dummy1				:24;
		} stBit;
	} unLR0_SSTCLR;										/* 0xFFC52810 - 0xFFC52814 */

	union												/* LR0_DSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDSTCLR00				:1;				/* DSTCLR00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unLR0_DSTCLR;										/* 0xFFC52814 - 0xFFC52818 */

	union												/* LR0_OVFCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSERROVFCLR0			:1;				/* SERROVFCLR0 */
			U4	xSERROVFCLR1			:1;				/* SERROVFCLR1 */
			U4	b30Dummy1				:30;
		} stBit;
	} unLR0_OVFCLR;										/* 0xFFC52818 - 0xFFC5281C */

	U1	u1Dummy2[0xFFC52820U - 0xFFC5281CU];			/* 0xFFC5281C - 0xFFC52820 */

	union												/* LR0_SERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDF00					:1;				/* SEDF00 */
			U4	xSEDF01					:1;				/* SEDF01 */
			U4	xSEDF02					:1;				/* SEDF02 */
			U4	xSEDF03					:1;				/* SEDF03 */
			U4	xSEDF04					:1;				/* SEDF04 */
			U4	xSEDF05					:1;				/* SEDF05 */
			U4	xSEDF06					:1;				/* SEDF06 */
			U4	xSEDF07					:1;				/* SEDF07 */
			U4	b24Dummy1				:24;
		} stBit;
	} unLR0_SERSTR;										/* 0xFFC52820 - 0xFFC52824 */

	union												/* LR0_DERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDummy1					:1;
			U4	xDEDF00					:1;				/* DEDF00 */
			U4	xDummy2					:1;
			U4	xAFEF00					:1;				/* AFEF00 */
			U4	b28Dummy3				:28;
		} stBit;
	} unLR0_DERSTR;										/* 0xFFC52824 - 0xFFC52828 */

	union												/* LR0_OVFSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSERROVF0				:1;				/* SERROVF0 */
			U4	xSERROVF1				:1;				/* SERROVF1 */
			U4	b30Dummy1				:30;
		} stBit;
	} unLR0_OVFSTR;										/* 0xFFC52828 - 0xFFC5282C */

	U1	u1Dummy3[0xFFC52830U - 0xFFC5282CU];			/* 0xFFC5282C - 0xFFC52830 */

	union												/* LR0_SERINF */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDLINF00				:1;				/* SEDLINF00 */
			U4	xSEDLINF01				:1;				/* SEDLINF01 */
			U4	xSEDLINF02				:1;				/* SEDLINF02 */
			U4	xSEDLINF03				:1;				/* SEDLINF03 */
			U4	xSEDLINF04				:1;				/* SEDLINF04 */
			U4	b27Dummy1				:27;
		} stBit;
	} unLR0_SERINF;										/* 0xFFC52830 - 0xFFC52834 */

	U1	u1Dummy4[0xFFC52870U - 0xFFC52834U];			/* 0xFFC52834 - 0xFFC52870 */

	union												/* LR0_nSEADR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b2Dummy1				:2;
			U4	b14SEADR0				:14;			/* SEADR0[15:2] */
			U4	b11Dummy2				:11;
			U4	b5SEDL					:5;				/* SEDL[4:0] */
		} stBit;
	} unLR0_nSEADR[ECC_BUFFNUM_LRAM];					/* 0xFFC52870 - 0xFFC52890 */

	U1	u1Dummy5[0xFFC528F0U - 0xFFC52890U];			/* 0xFFC52890 - 0xFFC528F0 */

	union												/* LR0_00DEADR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b2Dummy1				:2;
			U4	b14DEADR0				:14;			/* DEADR0[15:2] */
			U4	b11Dummy2				:11;
			U4	b5DEDL					:5;				/* DEDL[4:0] */
		} stBit;
	} unLR0_00DEADR;									/* 0xFFC528F0 - 0xFFC528F4 */

	union												/* LR0_00DESPIDCLR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xCLR00					:1;				/* DESPIDCLR00 */
			U4	xCLR01					:1;				/* DESPIDCLR01 */
			U4	xCLR02					:1;				/* DESPIDCLR02 */
			U4	xCLR03					:1;				/* DESPIDCLR03 */
			U4	xCLR04					:1;				/* DESPIDCLR04 */
			U4	xCLR05					:1;				/* DESPIDCLR05 */
			U4	xCLR06					:1;				/* DESPIDCLR06 */
			U4	xCLR07					:1;				/* DESPIDCLR07 */
			U4	xCLR08					:1;				/* DESPIDCLR08 */
			U4	xCLR09					:1;				/* DESPIDCLR09 */
			U4	xCLR10					:1;				/* DESPIDCLR10 */
			U4	xCLR11					:1;				/* DESPIDCLR11 */
			U4	xCLR12					:1;				/* DESPIDCLR12 */
			U4	xCLR13					:1;				/* DESPIDCLR13 */
			U4	xCLR14					:1;				/* DESPIDCLR14 */
			U4	xCLR15					:1;				/* DESPIDCLR15 */
			U4	xCLR16					:1;				/* DESPIDCLR16 */
			U4	xCLR17					:1;				/* DESPIDCLR17 */
			U4	xCLR18					:1;				/* DESPIDCLR18 */
			U4	xCLR19					:1;				/* DESPIDCLR19 */
			U4	xCLR20					:1;				/* DESPIDCLR20 */
			U4	xCLR21					:1;				/* DESPIDCLR21 */
			U4	xCLR22					:1;				/* DESPIDCLR22 */
			U4	xCLR23					:1;				/* DESPIDCLR23 */
			U4	xCLR24					:1;				/* DESPIDCLR24 */
			U4	xCLR25					:1;				/* DESPIDCLR25 */
			U4	xCLR26					:1;				/* DESPIDCLR26 */
			U4	xCLR27					:1;				/* DESPIDCLR27 */
			U4	xCLR28					:1;				/* DESPIDCLR28 */
			U4	xCLR29					:1;				/* DESPIDCLR29 */
			U4	xCLR30					:1;				/* DESPIDCLR30 */
			U4	xCLR31					:1;				/* DESPIDCLR31 */
		} stBit;
	} unLR0_00DESPIDCLR;								/* 0xFFC528F4 - 0xFFC528F8 */

	union												/* LR0_00DESPID */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSPID00					:1;				/* DESPID00 */
			U4	xSPID01					:1;				/* DESPID01 */
			U4	xSPID02					:1;				/* DESPID02 */
			U4	xSPID03					:1;				/* DESPID03 */
			U4	xSPID04					:1;				/* DESPID04 */
			U4	xSPID05					:1;				/* DESPID05 */
			U4	xSPID06					:1;				/* DESPID06 */
			U4	xSPID07					:1;				/* DESPID07 */
			U4	xSPID08					:1;				/* DESPID08 */
			U4	xSPID09					:1;				/* DESPID09 */
			U4	xSPID10					:1;				/* DESPID10 */
			U4	xSPID11					:1;				/* DESPID11 */
			U4	xSPID12					:1;				/* DESPID12 */
			U4	xSPID13					:1;				/* DESPID13 */
			U4	xSPID14					:1;				/* DESPID14 */
			U4	xSPID15					:1;				/* DESPID15 */
			U4	xSPID16					:1;				/* DESPID16 */
			U4	xSPID17					:1;				/* DESPID17 */
			U4	xSPID18					:1;				/* DESPID18 */
			U4	xSPID19					:1;				/* DESPID19 */
			U4	xSPID20					:1;				/* DESPID20 */
			U4	xSPID21					:1;				/* DESPID21 */
			U4	xSPID22					:1;				/* DESPID22 */
			U4	xSPID23					:1;				/* DESPID23 */
			U4	xSPID24					:1;				/* DESPID24 */
			U4	xSPID25					:1;				/* DESPID25 */
			U4	xSPID26					:1;				/* DESPID26 */
			U4	xSPID27					:1;				/* DESPID27 */
			U4	xSPID28					:1;				/* DESPID28 */
			U4	xSPID29					:1;				/* DESPID29 */
			U4	xSPID30					:1;				/* DESPID30 */
			U4	xSPID31					:1;				/* DESPID31 */
		} stBit;
	} unLR0_00DESPID;									/* 0xFFC528F8 - 0xFFC528FC */

	U1	u1Dummy6[0xFFC52900U - 0xFFC528FCU];			/* 0xFFC528FC - 0xFFC52900 */

	union												/* LR0_kSESPIDCLR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xCLR00					:1;				/* SESPIDCLR00 */
			U4	xCLR01					:1;				/* SESPIDCLR01 */
			U4	xCLR02					:1;				/* SESPIDCLR02 */
			U4	xCLR03					:1;				/* SESPIDCLR03 */
			U4	xCLR04					:1;				/* SESPIDCLR04 */
			U4	xCLR05					:1;				/* SESPIDCLR05 */
			U4	xCLR06					:1;				/* SESPIDCLR06 */
			U4	xCLR07					:1;				/* SESPIDCLR07 */
			U4	xCLR08					:1;				/* SESPIDCLR08 */
			U4	xCLR09					:1;				/* SESPIDCLR09 */
			U4	xCLR10					:1;				/* SESPIDCLR10 */
			U4	xCLR11					:1;				/* SESPIDCLR11 */
			U4	xCLR12					:1;				/* SESPIDCLR12 */
			U4	xCLR13					:1;				/* SESPIDCLR13 */
			U4	xCLR14					:1;				/* SESPIDCLR14 */
			U4	xCLR15					:1;				/* SESPIDCLR15 */
			U4	xCLR16					:1;				/* SESPIDCLR16 */
			U4	xCLR17					:1;				/* SESPIDCLR17 */
			U4	xCLR18					:1;				/* SESPIDCLR18 */
			U4	xCLR19					:1;				/* SESPIDCLR19 */
			U4	xCLR20					:1;				/* SESPIDCLR20 */
			U4	xCLR21					:1;				/* SESPIDCLR21 */
			U4	xCLR22					:1;				/* SESPIDCLR22 */
			U4	xCLR23					:1;				/* SESPIDCLR23 */
			U4	xCLR24					:1;				/* SESPIDCLR24 */
			U4	xCLR25					:1;				/* SESPIDCLR25 */
			U4	xCLR26					:1;				/* SESPIDCLR26 */
			U4	xCLR27					:1;				/* SESPIDCLR27 */
			U4	xCLR28					:1;				/* SESPIDCLR28 */
			U4	xCLR29					:1;				/* SESPIDCLR29 */
			U4	xCLR30					:1;				/* SESPIDCLR30 */
			U4	xCLR31					:1;				/* SESPIDCLR31 */
		} stBit;
	} unLR0_kSESPIDCLR[ECC_BUFFNUM_LRAM];				/* 0xFFC52900 - 0xFFC52920 */

	U1	u1Dummy7[0xFFC52980U - 0xFFC52920U];			/* 0xFFC52920 - 0xFFC52980 */

	union												/* LR0_kSESPID */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSPID00					:1;				/* SESPID00 */
			U4	xSPID01					:1;				/* SESPID01 */
			U4	xSPID02					:1;				/* SESPID02 */
			U4	xSPID03					:1;				/* SESPID03 */
			U4	xSPID04					:1;				/* SESPID04 */
			U4	xSPID05					:1;				/* SESPID05 */
			U4	xSPID06					:1;				/* SESPID06 */
			U4	xSPID07					:1;				/* SESPID07 */
			U4	xSPID08					:1;				/* SESPID08 */
			U4	xSPID09					:1;				/* SESPID09 */
			U4	xSPID10					:1;				/* SESPID10 */
			U4	xSPID11					:1;				/* SESPID11 */
			U4	xSPID12					:1;				/* SESPID12 */
			U4	xSPID13					:1;				/* SESPID13 */
			U4	xSPID14					:1;				/* SESPID14 */
			U4	xSPID15					:1;				/* SESPID15 */
			U4	xSPID16					:1;				/* SESPID16 */
			U4	xSPID17					:1;				/* SESPID17 */
			U4	xSPID18					:1;				/* SESPID18 */
			U4	xSPID19					:1;				/* SESPID19 */
			U4	xSPID20					:1;				/* SESPID20 */
			U4	xSPID21					:1;				/* SESPID21 */
			U4	xSPID22					:1;				/* SESPID22 */
			U4	xSPID23					:1;				/* SESPID23 */
			U4	xSPID24					:1;				/* SESPID24 */
			U4	xSPID25					:1;				/* SESPID25 */
			U4	xSPID26					:1;				/* SESPID26 */
			U4	xSPID27					:1;				/* SESPID27 */
			U4	xSPID28					:1;				/* SESPID28 */
			U4	xSPID29					:1;				/* SESPID29 */
			U4	xSPID30					:1;				/* SESPID30 */
			U4	xSPID31					:1;				/* SESPID31 */
		} stBit;
	} unLR0_kSESPID[ECC_BUFFNUM_LRAM];					/* 0xFFC52980 - 0xFFC529A0 */

}	Reg_Ecc_MeccCap_Lr_Pe4Cl2Type;


/* MECCCAP_LR_PE5CL2 */
/* ============================================================================ */
/* ============================ Module: MECCCAP_LR_PE5CL2 ===================== */
/* ============================================================================ */
typedef	struct											/* MECCCAP_LR_PE5CL2 */
{
	union												/* LR0_ERRINT */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDIE					:1;				/* SEDIE */
			U4	xDEDIE					:1;				/* DEDIE */
			U4	xDummy1					:1;
			U4	xAFEIE					:1;				/* AFEIE */
			U4	b3Dummy2				:3;
			U4	xSEOVFIE				:1;				/* SEOVFIE */
			U4	b24Dummy3				:24;
		} stBit;
	} unLR0_ERRINT;										/* 0xFFC52A00 - 0xFFC52A04 */

	U1	u1Dummy1[0xFFC52A10U - 0xFFC52A04U];			/* 0xFFC52A04 - 0xFFC52A10 */

	union												/* LR0_SSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSSTCLR00				:1;				/* SSTCLR00 */
			U4	xSSTCLR01				:1;				/* SSTCLR01 */
			U4	xSSTCLR02				:1;				/* SSTCLR02 */
			U4	xSSTCLR03				:1;				/* SSTCLR03 */
			U4	xSSTCLR04				:1;				/* SSTCLR04 */
			U4	xSSTCLR05				:1;				/* SSTCLR05 */
			U4	xSSTCLR06				:1;				/* SSTCLR06 */
			U4	xSSTCLR07				:1;				/* SSTCLR07 */
			U4	b24Dummy1				:24;
		} stBit;
	} unLR0_SSTCLR;										/* 0xFFC52A10 - 0xFFC52A14 */

	union												/* LR0_DSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDSTCLR00				:1;				/* DSTCLR00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unLR0_DSTCLR;										/* 0xFFC52A14 - 0xFFC52A18 */

	union												/* LR0_OVFCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSERROVFCLR0			:1;				/* SERROVFCLR0 */
			U4	xSERROVFCLR1			:1;				/* SERROVFCLR1 */
			U4	b30Dummy1				:30;
		} stBit;
	} unLR0_OVFCLR;										/* 0xFFC52A18 - 0xFFC52A1C */

	U1	u1Dummy2[0xFFC52A20U - 0xFFC52A1CU];			/* 0xFFC52A1C - 0xFFC52A20 */

	union												/* LR0_SERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDF00					:1;				/* SEDF00 */
			U4	xSEDF01					:1;				/* SEDF01 */
			U4	xSEDF02					:1;				/* SEDF02 */
			U4	xSEDF03					:1;				/* SEDF03 */
			U4	xSEDF04					:1;				/* SEDF04 */
			U4	xSEDF05					:1;				/* SEDF05 */
			U4	xSEDF06					:1;				/* SEDF06 */
			U4	xSEDF07					:1;				/* SEDF07 */
			U4	b24Dummy1				:24;
		} stBit;
	} unLR0_SERSTR;										/* 0xFFC52A20 - 0xFFC52A24 */

	union												/* LR0_DERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDummy1					:1;
			U4	xDEDF00					:1;				/* DEDF00 */
			U4	xDummy2					:1;
			U4	xAFEF00					:1;				/* AFEF00 */
			U4	b28Dummy3				:28;
		} stBit;
	} unLR0_DERSTR;										/* 0xFFC52A24 - 0xFFC52A28 */

	union												/* LR0_OVFSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSERROVF0				:1;				/* SERROVF0 */
			U4	xSERROVF1				:1;				/* SERROVF1 */
			U4	b30Dummy1				:30;
		} stBit;
	} unLR0_OVFSTR;										/* 0xFFC52A28 - 0xFFC52A2C */

	U1	u1Dummy3[0xFFC52A30U - 0xFFC52A2CU];			/* 0xFFC52A2C - 0xFFC52A30 */

	union												/* LR0_SERINF */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDLINF00				:1;				/* SEDLINF00 */
			U4	xSEDLINF01				:1;				/* SEDLINF01 */
			U4	xSEDLINF02				:1;				/* SEDLINF02 */
			U4	xSEDLINF03				:1;				/* SEDLINF03 */
			U4	xSEDLINF04				:1;				/* SEDLINF04 */
			U4	b27Dummy1				:27;
		} stBit;
	} unLR0_SERINF;										/* 0xFFC52A30 - 0xFFC52A34 */

	U1	u1Dummy4[0xFFC52A70U - 0xFFC52A34U];			/* 0xFFC52A34 - 0xFFC52A70 */

	union												/* LR0_nSEADR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b2Dummy1				:2;
			U4	b14SEADR0				:14;			/* SEADR0[15:2] */
			U4	b11Dummy2				:11;
			U4	b5SEDL					:5;				/* SEDL[4:0] */
		} stBit;
	} unLR0_nSEADR[ECC_BUFFNUM_LRAM];					/* 0xFFC52A70 - 0xFFC52A90 */

	U1	u1Dummy5[0xFFC52AF0U - 0xFFC52A90U];			/* 0xFFC52A90 - 0xFFC52AF0 */

	union												/* LR0_00DEADR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b2Dummy1				:2;
			U4	b14DEADR0				:14;			/* DEADR0[15:2] */
			U4	b11Dummy2				:11;
			U4	b5DEDL					:5;				/* DEDL[4:0] */
		} stBit;
	} unLR0_00DEADR;									/* 0xFFC52AF0 - 0xFFC52AF4 */

	union												/* LR0_00DESPIDCLR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xCLR00					:1;				/* DESPIDCLR00 */
			U4	xCLR01					:1;				/* DESPIDCLR01 */
			U4	xCLR02					:1;				/* DESPIDCLR02 */
			U4	xCLR03					:1;				/* DESPIDCLR03 */
			U4	xCLR04					:1;				/* DESPIDCLR04 */
			U4	xCLR05					:1;				/* DESPIDCLR05 */
			U4	xCLR06					:1;				/* DESPIDCLR06 */
			U4	xCLR07					:1;				/* DESPIDCLR07 */
			U4	xCLR08					:1;				/* DESPIDCLR08 */
			U4	xCLR09					:1;				/* DESPIDCLR09 */
			U4	xCLR10					:1;				/* DESPIDCLR10 */
			U4	xCLR11					:1;				/* DESPIDCLR11 */
			U4	xCLR12					:1;				/* DESPIDCLR12 */
			U4	xCLR13					:1;				/* DESPIDCLR13 */
			U4	xCLR14					:1;				/* DESPIDCLR14 */
			U4	xCLR15					:1;				/* DESPIDCLR15 */
			U4	xCLR16					:1;				/* DESPIDCLR16 */
			U4	xCLR17					:1;				/* DESPIDCLR17 */
			U4	xCLR18					:1;				/* DESPIDCLR18 */
			U4	xCLR19					:1;				/* DESPIDCLR19 */
			U4	xCLR20					:1;				/* DESPIDCLR20 */
			U4	xCLR21					:1;				/* DESPIDCLR21 */
			U4	xCLR22					:1;				/* DESPIDCLR22 */
			U4	xCLR23					:1;				/* DESPIDCLR23 */
			U4	xCLR24					:1;				/* DESPIDCLR24 */
			U4	xCLR25					:1;				/* DESPIDCLR25 */
			U4	xCLR26					:1;				/* DESPIDCLR26 */
			U4	xCLR27					:1;				/* DESPIDCLR27 */
			U4	xCLR28					:1;				/* DESPIDCLR28 */
			U4	xCLR29					:1;				/* DESPIDCLR29 */
			U4	xCLR30					:1;				/* DESPIDCLR30 */
			U4	xCLR31					:1;				/* DESPIDCLR31 */
		} stBit;
	} unLR0_00DESPIDCLR;								/* 0xFFC52AF4 - 0xFFC52AF8 */

	union												/* LR0_00DESPID */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSPID00					:1;				/* DESPID00 */
			U4	xSPID01					:1;				/* DESPID01 */
			U4	xSPID02					:1;				/* DESPID02 */
			U4	xSPID03					:1;				/* DESPID03 */
			U4	xSPID04					:1;				/* DESPID04 */
			U4	xSPID05					:1;				/* DESPID05 */
			U4	xSPID06					:1;				/* DESPID06 */
			U4	xSPID07					:1;				/* DESPID07 */
			U4	xSPID08					:1;				/* DESPID08 */
			U4	xSPID09					:1;				/* DESPID09 */
			U4	xSPID10					:1;				/* DESPID10 */
			U4	xSPID11					:1;				/* DESPID11 */
			U4	xSPID12					:1;				/* DESPID12 */
			U4	xSPID13					:1;				/* DESPID13 */
			U4	xSPID14					:1;				/* DESPID14 */
			U4	xSPID15					:1;				/* DESPID15 */
			U4	xSPID16					:1;				/* DESPID16 */
			U4	xSPID17					:1;				/* DESPID17 */
			U4	xSPID18					:1;				/* DESPID18 */
			U4	xSPID19					:1;				/* DESPID19 */
			U4	xSPID20					:1;				/* DESPID20 */
			U4	xSPID21					:1;				/* DESPID21 */
			U4	xSPID22					:1;				/* DESPID22 */
			U4	xSPID23					:1;				/* DESPID23 */
			U4	xSPID24					:1;				/* DESPID24 */
			U4	xSPID25					:1;				/* DESPID25 */
			U4	xSPID26					:1;				/* DESPID26 */
			U4	xSPID27					:1;				/* DESPID27 */
			U4	xSPID28					:1;				/* DESPID28 */
			U4	xSPID29					:1;				/* DESPID29 */
			U4	xSPID30					:1;				/* DESPID30 */
			U4	xSPID31					:1;				/* DESPID31 */
		} stBit;
	} unLR0_00DESPID;									/* 0xFFC52AF8 - 0xFFC52AFC */

	U1	u1Dummy6[0xFFC52B00U - 0xFFC52AFCU];			/* 0xFFC52AFC - 0xFFC52B00 */

	union												/* LR0_kSESPIDCLR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xCLR00					:1;				/* SESPIDCLR00 */
			U4	xCLR01					:1;				/* SESPIDCLR01 */
			U4	xCLR02					:1;				/* SESPIDCLR02 */
			U4	xCLR03					:1;				/* SESPIDCLR03 */
			U4	xCLR04					:1;				/* SESPIDCLR04 */
			U4	xCLR05					:1;				/* SESPIDCLR05 */
			U4	xCLR06					:1;				/* SESPIDCLR06 */
			U4	xCLR07					:1;				/* SESPIDCLR07 */
			U4	xCLR08					:1;				/* SESPIDCLR08 */
			U4	xCLR09					:1;				/* SESPIDCLR09 */
			U4	xCLR10					:1;				/* SESPIDCLR10 */
			U4	xCLR11					:1;				/* SESPIDCLR11 */
			U4	xCLR12					:1;				/* SESPIDCLR12 */
			U4	xCLR13					:1;				/* SESPIDCLR13 */
			U4	xCLR14					:1;				/* SESPIDCLR14 */
			U4	xCLR15					:1;				/* SESPIDCLR15 */
			U4	xCLR16					:1;				/* SESPIDCLR16 */
			U4	xCLR17					:1;				/* SESPIDCLR17 */
			U4	xCLR18					:1;				/* SESPIDCLR18 */
			U4	xCLR19					:1;				/* SESPIDCLR19 */
			U4	xCLR20					:1;				/* SESPIDCLR20 */
			U4	xCLR21					:1;				/* SESPIDCLR21 */
			U4	xCLR22					:1;				/* SESPIDCLR22 */
			U4	xCLR23					:1;				/* SESPIDCLR23 */
			U4	xCLR24					:1;				/* SESPIDCLR24 */
			U4	xCLR25					:1;				/* SESPIDCLR25 */
			U4	xCLR26					:1;				/* SESPIDCLR26 */
			U4	xCLR27					:1;				/* SESPIDCLR27 */
			U4	xCLR28					:1;				/* SESPIDCLR28 */
			U4	xCLR29					:1;				/* SESPIDCLR29 */
			U4	xCLR30					:1;				/* SESPIDCLR30 */
			U4	xCLR31					:1;				/* SESPIDCLR31 */
		} stBit;
	} unLR0_kSESPIDCLR[ECC_BUFFNUM_LRAM];				/* 0xFFC52B00 - 0xFFC52B20 */

	U1	u1Dummy7[0xFFC52B80U - 0xFFC52B20U];			/* 0xFFC52B20 - 0xFFC52B80 */

	union												/* LR0_kSESPID */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSPID00					:1;				/* SESPID00 */
			U4	xSPID01					:1;				/* SESPID01 */
			U4	xSPID02					:1;				/* SESPID02 */
			U4	xSPID03					:1;				/* SESPID03 */
			U4	xSPID04					:1;				/* SESPID04 */
			U4	xSPID05					:1;				/* SESPID05 */
			U4	xSPID06					:1;				/* SESPID06 */
			U4	xSPID07					:1;				/* SESPID07 */
			U4	xSPID08					:1;				/* SESPID08 */
			U4	xSPID09					:1;				/* SESPID09 */
			U4	xSPID10					:1;				/* SESPID10 */
			U4	xSPID11					:1;				/* SESPID11 */
			U4	xSPID12					:1;				/* SESPID12 */
			U4	xSPID13					:1;				/* SESPID13 */
			U4	xSPID14					:1;				/* SESPID14 */
			U4	xSPID15					:1;				/* SESPID15 */
			U4	xSPID16					:1;				/* SESPID16 */
			U4	xSPID17					:1;				/* SESPID17 */
			U4	xSPID18					:1;				/* SESPID18 */
			U4	xSPID19					:1;				/* SESPID19 */
			U4	xSPID20					:1;				/* SESPID20 */
			U4	xSPID21					:1;				/* SESPID21 */
			U4	xSPID22					:1;				/* SESPID22 */
			U4	xSPID23					:1;				/* SESPID23 */
			U4	xSPID24					:1;				/* SESPID24 */
			U4	xSPID25					:1;				/* SESPID25 */
			U4	xSPID26					:1;				/* SESPID26 */
			U4	xSPID27					:1;				/* SESPID27 */
			U4	xSPID28					:1;				/* SESPID28 */
			U4	xSPID29					:1;				/* SESPID29 */
			U4	xSPID30					:1;				/* SESPID30 */
			U4	xSPID31					:1;				/* SESPID31 */
		} stBit;
	} unLR0_kSESPID[ECC_BUFFNUM_LRAM];					/* 0xFFC52B80 - 0xFFC52BA0 */

}	Reg_Ecc_MeccCap_Lr_Pe5Cl2Type;


/* MECCCAP_LRA */
/* ============================================================================ */
/* ============================ Module: MECCCAP_LRA =========================== */
/* ============================================================================ */
typedef	struct											/* MECCCAP_LRA */
{
	union												/* LR1_ERRINT */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDIE					:1;				/* SEDIE */
			U4	xDEDIE					:1;				/* DEDIE */
			U4	b5Dummy1				:5;
			U4	xSEOVFIE				:1;				/* SEOVFIE */
			U4	b24Dummy2				:24;
		} stBit;
	} unLR1_ERRINT;										/* 0xFFC55000 - 0xFFC55004 */

	U1	u1Dummy1[0xFFC55010U - 0xFFC55004U];			/* 0xFFC55004 - 0xFFC55010 */

	union												/* LR1_SSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSSTCLR00				:1;				/* SSTCLR00 */
			U4	xSSTCLR01				:1;				/* SSTCLR01 */
			U4	xSSTCLR02				:1;				/* SSTCLR02 */
			U4	xSSTCLR03				:1;				/* SSTCLR03 */
			U4	xSSTCLR04				:1;				/* SSTCLR04 */
			U4	xSSTCLR05				:1;				/* SSTCLR05 */
			U4	xSSTCLR06				:1;				/* SSTCLR06 */
			U4	xSSTCLR07				:1;				/* SSTCLR07 */
			U4	b24Dummy1				:24;
		} stBit;
	} unLR1_SSTCLR;										/* 0xFFC55010 - 0xFFC55014 */

	union												/* LR1_DSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDSTCLR00				:1;				/* DSTCLR00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unLR1_DSTCLR;										/* 0xFFC55014 - 0xFFC55018 */

	union												/* LR1_OVFCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSERROVFCLR0			:1;				/* SERROVFCLR0 */
			U4	xSERROVFCLR1			:1;				/* SERROVFCLR1 */
			U4	b30Dummy1				:30;
		} stBit;
	} unLR1_OVFCLR;										/* 0xFFC55018 - 0xFFC5501C */

	U1	u1Dummy2[0xFFC55020U - 0xFFC5501CU];			/* 0xFFC5501C - 0xFFC55020 */

	union												/* LR1_SERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDF00					:1;				/* SEDF00 */
			U4	xSEDF01					:1;				/* SEDF01 */
			U4	xSEDF02					:1;				/* SEDF02 */
			U4	xSEDF03					:1;				/* SEDF03 */
			U4	xSEDF04					:1;				/* SEDF04 */
			U4	xSEDF05					:1;				/* SEDF05 */
			U4	xSEDF06					:1;				/* SEDF06 */
			U4	xSEDF07					:1;				/* SEDF07 */
			U4	b24Dummy1				:24;
		} stBit;
	} unLR1_SERSTR;										/* 0xFFC55020 - 0xFFC55024 */

	union												/* LR1_DERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDummy1					:1;
			U4	xDEDF00					:1;				/* DEDF00 */
			U4	b30Dummy2				:30;
		} stBit;
	} unLR1_DERSTR;										/* 0xFFC55024 - 0xFFC55028 */

	union												/* LR1_OVFSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSERROVF0				:1;				/* SERROVF0 */
			U4	xSERROVF1				:1;				/* SERROVF1 */
			U4	b30Dummy1				:30;
		} stBit;
	} unLR1_OVFSTR;										/* 0xFFC55028 - 0xFFC5502C */

	U1	u1Dummy3[0xFFC55030U - 0xFFC5502CU];			/* 0xFFC5502C - 0xFFC55030 */

	union												/* LR1_SERINF */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDLINF00				:1;				/* SEDLINF00 */
			U4	xSEDLINF01				:1;				/* SEDLINF01 */
			U4	xSEDLINF02				:1;				/* SEDLINF02 */
			U4	xSEDLINF03				:1;				/* SEDLINF03 */
			U4	xSEDLINF04				:1;				/* SEDLINF04 */
			U4	xSEDLINF05				:1;				/* SEDLINF05 */
			U4	b26Dummy1				:26;
		} stBit;
	} unLR1_SERINF;										/* 0xFFC55030 - 0xFFC55034 */

	U1	u1Dummy4[0xFFC55070U - 0xFFC55034U];			/* 0xFFC55034 - 0xFFC55070 */

	union												/* LR1_nSEADR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b2Dummy1				:2;
			U4	b23SEADR0				:23;			/* SEADR0[24:2] */
			U4	b2Dummy2				:2;
			U4	b5SEDL					:5;				/* SEDL[4:0] */
		} stBit;
	} unLR1_nSEADR[ECC_BUFFNUM_LRAM];					/* 0xFFC55070 - 0xFFC55090 */

	U1	u1Dummy5[0xFFC550F0U - 0xFFC55090U];			/* 0xFFC55090 - 0xFFC550F0 */

	union												/* LR1_00DEADR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b2Dummy1				:2;
			U4	b23DEADR0				:23;			/* DEADR0[24:2] */
			U4	b2Dummy2				:2;
			U4	b5DEDL					:5;				/* DEDL[4:0] */
		} stBit;
	} unLR1_00DEADR;									/* 0xFFC550F0 - 0xFFC550F4 */

	union												/* LR1_00DESPIDCLR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xCLR00					:1;				/* DESPIDCLR00 */
			U4	xCLR01					:1;				/* DESPIDCLR01 */
			U4	xCLR02					:1;				/* DESPIDCLR02 */
			U4	xCLR03					:1;				/* DESPIDCLR03 */
			U4	xCLR04					:1;				/* DESPIDCLR04 */
			U4	xCLR05					:1;				/* DESPIDCLR05 */
			U4	xCLR06					:1;				/* DESPIDCLR06 */
			U4	xCLR07					:1;				/* DESPIDCLR07 */
			U4	xCLR08					:1;				/* DESPIDCLR08 */
			U4	xCLR09					:1;				/* DESPIDCLR09 */
			U4	xCLR10					:1;				/* DESPIDCLR10 */
			U4	xCLR11					:1;				/* DESPIDCLR11 */
			U4	xCLR12					:1;				/* DESPIDCLR12 */
			U4	xCLR13					:1;				/* DESPIDCLR13 */
			U4	xCLR14					:1;				/* DESPIDCLR14 */
			U4	xCLR15					:1;				/* DESPIDCLR15 */
			U4	xCLR16					:1;				/* DESPIDCLR16 */
			U4	xCLR17					:1;				/* DESPIDCLR17 */
			U4	xCLR18					:1;				/* DESPIDCLR18 */
			U4	xCLR19					:1;				/* DESPIDCLR19 */
			U4	xCLR20					:1;				/* DESPIDCLR20 */
			U4	xCLR21					:1;				/* DESPIDCLR21 */
			U4	xCLR22					:1;				/* DESPIDCLR22 */
			U4	xCLR23					:1;				/* DESPIDCLR23 */
			U4	xCLR24					:1;				/* DESPIDCLR24 */
			U4	xCLR25					:1;				/* DESPIDCLR25 */
			U4	xCLR26					:1;				/* DESPIDCLR26 */
			U4	xCLR27					:1;				/* DESPIDCLR27 */
			U4	xCLR28					:1;				/* DESPIDCLR28 */
			U4	xCLR29					:1;				/* DESPIDCLR29 */
			U4	xCLR30					:1;				/* DESPIDCLR30 */
			U4	xCLR31					:1;				/* DESPIDCLR31 */
		} stBit;
	} unLR1_00DESPIDCLR;								/* 0xFFC550F4 - 0xFFC550F8 */

	union												/* LR1_00DESPID */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSPID00					:1;				/* DESPID00 */
			U4	xSPID01					:1;				/* DESPID01 */
			U4	xSPID02					:1;				/* DESPID02 */
			U4	xSPID03					:1;				/* DESPID03 */
			U4	xSPID04					:1;				/* DESPID04 */
			U4	xSPID05					:1;				/* DESPID05 */
			U4	xSPID06					:1;				/* DESPID06 */
			U4	xSPID07					:1;				/* DESPID07 */
			U4	xSPID08					:1;				/* DESPID08 */
			U4	xSPID09					:1;				/* DESPID09 */
			U4	xSPID10					:1;				/* DESPID10 */
			U4	xSPID11					:1;				/* DESPID11 */
			U4	xSPID12					:1;				/* DESPID12 */
			U4	xSPID13					:1;				/* DESPID13 */
			U4	xSPID14					:1;				/* DESPID14 */
			U4	xSPID15					:1;				/* DESPID15 */
			U4	xSPID16					:1;				/* DESPID16 */
			U4	xSPID17					:1;				/* DESPID17 */
			U4	xSPID18					:1;				/* DESPID18 */
			U4	xSPID19					:1;				/* DESPID19 */
			U4	xSPID20					:1;				/* DESPID20 */
			U4	xSPID21					:1;				/* DESPID21 */
			U4	xSPID22					:1;				/* DESPID22 */
			U4	xSPID23					:1;				/* DESPID23 */
			U4	xSPID24					:1;				/* DESPID24 */
			U4	xSPID25					:1;				/* DESPID25 */
			U4	xSPID26					:1;				/* DESPID26 */
			U4	xSPID27					:1;				/* DESPID27 */
			U4	xSPID28					:1;				/* DESPID28 */
			U4	xSPID29					:1;				/* DESPID29 */
			U4	xSPID30					:1;				/* DESPID30 */
			U4	xSPID31					:1;				/* DESPID31 */
		} stBit;
	} unLR1_00DESPID;									/* 0xFFC550F8 - 0xFFC550FC */

	U1	u1Dummy6[0xFFC55100U - 0xFFC550FCU];			/* 0xFFC550FC - 0xFFC55100 */

	union												/* LR1_kSESPIDCLR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xCLR00					:1;				/* SESPIDCLR00 */
			U4	xCLR01					:1;				/* SESPIDCLR01 */
			U4	xCLR02					:1;				/* SESPIDCLR02 */
			U4	xCLR03					:1;				/* SESPIDCLR03 */
			U4	xCLR04					:1;				/* SESPIDCLR04 */
			U4	xCLR05					:1;				/* SESPIDCLR05 */
			U4	xCLR06					:1;				/* SESPIDCLR06 */
			U4	xCLR07					:1;				/* SESPIDCLR07 */
			U4	xCLR08					:1;				/* SESPIDCLR08 */
			U4	xCLR09					:1;				/* SESPIDCLR09 */
			U4	xCLR10					:1;				/* SESPIDCLR10 */
			U4	xCLR11					:1;				/* SESPIDCLR11 */
			U4	xCLR12					:1;				/* SESPIDCLR12 */
			U4	xCLR13					:1;				/* SESPIDCLR13 */
			U4	xCLR14					:1;				/* SESPIDCLR14 */
			U4	xCLR15					:1;				/* SESPIDCLR15 */
			U4	xCLR16					:1;				/* SESPIDCLR16 */
			U4	xCLR17					:1;				/* SESPIDCLR17 */
			U4	xCLR18					:1;				/* SESPIDCLR18 */
			U4	xCLR19					:1;				/* SESPIDCLR19 */
			U4	xCLR20					:1;				/* SESPIDCLR20 */
			U4	xCLR21					:1;				/* SESPIDCLR21 */
			U4	xCLR22					:1;				/* SESPIDCLR22 */
			U4	xCLR23					:1;				/* SESPIDCLR23 */
			U4	xCLR24					:1;				/* SESPIDCLR24 */
			U4	xCLR25					:1;				/* SESPIDCLR25 */
			U4	xCLR26					:1;				/* SESPIDCLR26 */
			U4	xCLR27					:1;				/* SESPIDCLR27 */
			U4	xCLR28					:1;				/* SESPIDCLR28 */
			U4	xCLR29					:1;				/* SESPIDCLR29 */
			U4	xCLR30					:1;				/* SESPIDCLR30 */
			U4	xCLR31					:1;				/* SESPIDCLR31 */
		} stBit;
	} unLR1_kSESPIDCLR[ECC_BUFFNUM_LRAM];				/* 0xFFC55100 - 0xFFC55120 */

	U1	u1Dummy7[0xFFC55180U - 0xFFC55120U];			/* 0xFFC55120 - 0xFFC55180 */

	union												/* LR1_kSESPID */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSPID00					:1;				/* SESPID00 */
			U4	xSPID01					:1;				/* SESPID01 */
			U4	xSPID02					:1;				/* SESPID02 */
			U4	xSPID03					:1;				/* SESPID03 */
			U4	xSPID04					:1;				/* SESPID04 */
			U4	xSPID05					:1;				/* SESPID05 */
			U4	xSPID06					:1;				/* SESPID06 */
			U4	xSPID07					:1;				/* SESPID07 */
			U4	xSPID08					:1;				/* SESPID08 */
			U4	xSPID09					:1;				/* SESPID09 */
			U4	xSPID10					:1;				/* SESPID10 */
			U4	xSPID11					:1;				/* SESPID11 */
			U4	xSPID12					:1;				/* SESPID12 */
			U4	xSPID13					:1;				/* SESPID13 */
			U4	xSPID14					:1;				/* SESPID14 */
			U4	xSPID15					:1;				/* SESPID15 */
			U4	xSPID16					:1;				/* SESPID16 */
			U4	xSPID17					:1;				/* SESPID17 */
			U4	xSPID18					:1;				/* SESPID18 */
			U4	xSPID19					:1;				/* SESPID19 */
			U4	xSPID20					:1;				/* SESPID20 */
			U4	xSPID21					:1;				/* SESPID21 */
			U4	xSPID22					:1;				/* SESPID22 */
			U4	xSPID23					:1;				/* SESPID23 */
			U4	xSPID24					:1;				/* SESPID24 */
			U4	xSPID25					:1;				/* SESPID25 */
			U4	xSPID26					:1;				/* SESPID26 */
			U4	xSPID27					:1;				/* SESPID27 */
			U4	xSPID28					:1;				/* SESPID28 */
			U4	xSPID29					:1;				/* SESPID29 */
			U4	xSPID30					:1;				/* SESPID30 */
			U4	xSPID31					:1;				/* SESPID31 */
		} stBit;
	} unLR1_kSESPID[ECC_BUFFNUM_LRAM];					/* 0xFFC55180 - 0xFFC551A0 */

}	Reg_Ecc_MeccCap_LraType;


/* ECCCNT_CRCCL0 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_CRCCL0 ========================= */
/* ============================================================================ */
typedef	struct											/* ECCCNT_CRCCL0 */
{
	union												/* CRCAFCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b3Dummy1				:3;
			U4	xAFEDIS					:1;				/* AFEDIS */
			U4	b28Dummy2				:28;
		} stBit;
	} unCRCAFCTL;										/* 0xFFC49C00 - 0xFFC49C04 */

	U1	u1Dummy1[0xFFC49C10U - 0xFFC49C04U];			/* 0xFFC49C04 - 0xFFC49C10 */

	union												/* CRCECCTSTCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDATSEL					:1;				/* DATSEL */
			U4	xECCTST					:1;				/* ECCTST */
			U4	b30Dummy1				:30;
		} stBit;
	} unCRCECCTSTCTL;									/* 0xFFC49C10 - 0xFFC49C14 */

	U1	u1Dummy2[0xFFC49C20U - 0xFFC49C14U];			/* 0xFFC49C14 - 0xFFC49C20 */

	union												/* CRCAFINV */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b4Dummy1				:4;
			U4	b15AFINV				:15;			/* AFINV[18:4] */
			U4	b13Dummy2				:13;
		} stBit;
	} unCRCAFINV;										/* 0xFFC49C20 - 0xFFC49C24 */

	U1	u1Dummy3[0xFFC49C60U - 0xFFC49C24U];			/* 0xFFC49C24 - 0xFFC49C60 */

	union												/* CRCTDATBFECCF */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b7BFECC0				:7;				/* BFECC0[6:0] */
			U4	xDummy1					:1;
			U4	b7BFECC1				:7;				/* BFECC1[6:0] */
			U4	xDummy2					:1;
			U4	b7BFECC2				:7;				/* BFECC2[6:0] */
			U4	xDummy3					:1;
			U4	b7BFECC3				:7;				/* BFECC3[6:0] */
			U4	xDummy4					:1;
		} stBit;
	} unCRCTDATBFECCF;									/* 0xFFC49C60 - 0xFFC49C64 */

}	Reg_Ecc_EccCnt_Crccl0Type;


/* ECCCNT_CRCCL1 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_CRCCL1 ========================= */
/* ============================================================================ */
typedef	struct											/* ECCCNT_CRCCL1 */
{
	union												/* CRCAFCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b3Dummy1				:3;
			U4	xAFEDIS					:1;				/* AFEDIS */
			U4	b28Dummy2				:28;
		} stBit;
	} unCRCAFCTL;										/* 0xFFC49C80 - 0xFFC49C84 */

	U1	u1Dummy1[0xFFC49C90U - 0xFFC49C84U];			/* 0xFFC49C84 - 0xFFC49C90 */

	union												/* CRCECCTSTCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDATSEL					:1;				/* DATSEL */
			U4	xECCTST					:1;				/* ECCTST */
			U4	b30Dummy1				:30;
		} stBit;
	} unCRCECCTSTCTL;									/* 0xFFC49C90 - 0xFFC49C94 */

	U1	u1Dummy2[0xFFC49CA0U - 0xFFC49C94U];			/* 0xFFC49C94 - 0xFFC49CA0 */

	union												/* CRCAFINV */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b4Dummy1				:4;
			U4	b15AFINV				:15;			/* AFINV[18:4] */
			U4	b13Dummy2				:13;
		} stBit;
	} unCRCAFINV;										/* 0xFFC49CA0 - 0xFFC49CA4 */

	U1	u1Dummy3[0xFFC49CE0U - 0xFFC49CA4U];			/* 0xFFC49CA4 - 0xFFC49CE0 */

	union												/* CRCTDATBFECCF */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b7BFECC0				:7;				/* BFECC0[6:0] */
			U4	xDummy1					:1;
			U4	b7BFECC1				:7;				/* BFECC1[6:0] */
			U4	xDummy2					:1;
			U4	b7BFECC2				:7;				/* BFECC2[6:0] */
			U4	xDummy3					:1;
			U4	b7BFECC3				:7;				/* BFECC3[6:0] */
			U4	xDummy4					:1;
		} stBit;
	} unCRCTDATBFECCF;									/* 0xFFC49CE0 - 0xFFC49CE4 */

}	Reg_Ecc_EccCnt_Crccl1Type;


/* ECCCNT_CRCCL2 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_CRCCL2 ========================= */
/* ============================================================================ */
typedef	struct											/* ECCCNT_CRCCL2 */
{
	union												/* CRCAFCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b3Dummy1				:3;
			U4	xAFEDIS					:1;				/* AFEDIS */
			U4	b28Dummy2				:28;
		} stBit;
	} unCRCAFCTL;										/* 0xFFC49D00 - 0xFFC49D04 */

	U1	u1Dummy1[0xFFC49D10U - 0xFFC49D04U];			/* 0xFFC49D04 - 0xFFC49D10 */

	union												/* CRCECCTSTCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDATSEL					:1;				/* DATSEL */
			U4	xECCTST					:1;				/* ECCTST */
			U4	b30Dummy1				:30;
		} stBit;
	} unCRCECCTSTCTL;									/* 0xFFC49D10 - 0xFFC49D14 */

	U1	u1Dummy2[0xFFC49D20U - 0xFFC49D14U];			/* 0xFFC49D14 - 0xFFC49D20 */

	union												/* CRCAFINV */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b4Dummy1				:4;
			U4	b15AFINV				:15;			/* AFINV[18:4] */
			U4	b13Dummy2				:13;
		} stBit;
	} unCRCAFINV;										/* 0xFFC49D20 - 0xFFC49D24 */

	U1	u1Dummy3[0xFFC49D60U - 0xFFC49D24U];			/* 0xFFC49D24 - 0xFFC49D60 */

	union												/* CRCTDATBFECCF */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b7BFECC0				:7;				/* BFECC0[6:0] */
			U4	xDummy1					:1;
			U4	b7BFECC1				:7;				/* BFECC1[6:0] */
			U4	xDummy2					:1;
			U4	b7BFECC2				:7;				/* BFECC2[6:0] */
			U4	xDummy3					:1;
			U4	b7BFECC3				:7;				/* BFECC3[6:0] */
			U4	xDummy4					:1;
		} stBit;
	} unCRCTDATBFECCF;									/* 0xFFC49D60 - 0xFFC49D64 */

}	Reg_Ecc_EccCnt_Crccl2Type;


/* ECCCNT_CRCCL4 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_CRCCL4 ========================= */
/* ============================================================================ */
typedef	struct											/* ECCCNT_CRCCL4 */
{
	union												/* CRCAFCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b3Dummy1				:3;
			U4	xAFEDIS					:1;				/* AFEDIS */
			U4	b28Dummy2				:28;
		} stBit;
	} unCRCAFCTL;										/* 0xFFC5C380 - 0xFFC5C384 */

	U1	u1Dummy1[0xFFC5C390U - 0xFFC5C384U];			/* 0xFFC5C384 - 0xFFC5C390 */

	union												/* CRCECCTSTCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDATSEL					:1;				/* DATSEL */
			U4	xECCTST					:1;				/* ECCTST */
			U4	b30Dummy1				:30;
		} stBit;
	} unCRCECCTSTCTL;									/* 0xFFC5C390 - 0xFFC5C394 */

	U1	u1Dummy2[0xFFC5C3A0U - 0xFFC5C394U];			/* 0xFFC5C394 - 0xFFC5C3A0 */

	union												/* CRCAFINV */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b4Dummy1				:4;
			U4	b18AFINV				:18;			/* AFINV[21:4] */
			U4	b10Dummy2				:10;
		} stBit;
	} unCRCAFINV;										/* 0xFFC5C3A0 - 0xFFC5C3A4 */

	U1	u1Dummy3[0xFFC5C3E0U - 0xFFC5C3A4U];			/* 0xFFC5C3A4 - 0xFFC5C3E0 */

	union												/* CRCTDATBFECCF */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b7BFECC0				:7;				/* BFECC0[6:0] */
			U4	xDummy1					:1;
			U4	b7BFECC1				:7;				/* BFECC1[6:0] */
			U4	xDummy2					:1;
			U4	b7BFECC2				:7;				/* BFECC2[6:0] */
			U4	xDummy3					:1;
			U4	b7BFECC3				:7;				/* BFECC3[6:0] */
			U4	xDummy4					:1;
		} stBit;
	} unCRCTDATBFECCF;									/* 0xFFC5C3E0 - 0xFFC5C3E4 */

}	Reg_Ecc_EccCnt_Crccl4Type;


/* ECCCNT_CRA */
/* ============================================================================ */
/* ============================ Module: ECCCNT_CRA ============================ */
/* ============================================================================ */
typedef	struct											/* ECCCNT_CRA */
{
	union												/* CRAECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	b30Dummy1				:30;
		} stBit;
	} unCRAECCCTL;										/* 0xFFC49E00 - 0xFFC49E04 */

}	Reg_Ecc_EccCnt_CraType;


/* MECCCAP_CRAM */
/* ============================================================================ */
/* ============================ Module: MECCCAP_CRAM ========================== */
/* ============================================================================ */
typedef	struct											/* MECCCAP_CRAM */
{
	union												/* CR_ERRINT */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDIE					:1;				/* SEDIE */
			U4	xDEDIE					:1;				/* DEDIE */
			U4	xDummy1					:1;
			U4	xAFEIE					:1;				/* AFEIE */
			U4	b3Dummy2				:3;
			U4	xSEOVFIE				:1;				/* SEOVFIE */
			U4	b24Dummy3				:24;
		} stBit;
	} unCR_ERRINT;										/* 0xFFC55200 - 0xFFC55204 */

	U1	u1Dummy1[0xFFC55210U - 0xFFC55204U];			/* 0xFFC55204 - 0xFFC55210 */

	union												/* CR_SSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSSTCLR00				:1;				/* SSTCLR00 */
			U4	xSSTCLR01				:1;				/* SSTCLR01 */
			U4	xSSTCLR02				:1;				/* SSTCLR02 */
			U4	xSSTCLR03				:1;				/* SSTCLR03 */
			U4	xSSTCLR04				:1;				/* SSTCLR04 */
			U4	xSSTCLR05				:1;				/* SSTCLR05 */
			U4	xSSTCLR06				:1;				/* SSTCLR06 */
			U4	xSSTCLR07				:1;				/* SSTCLR07 */
			U4	b24Dummy1				:24;
		} stBit;
	} unCR_SSTCLR;										/* 0xFFC55210 - 0xFFC55214 */

	union												/* CR_DSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDSTCLR00				:1;				/* DSTCLR00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unCR_DSTCLR;										/* 0xFFC55214 - 0xFFC55218 */

	union												/* CR_OVFCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSERROVFCLR0			:1;				/* SERROVFCLR0 */
			U4	xSERROVFCLR1			:1;				/* SERROVFCLR1 */
			U4	b30Dummy1				:30;
		} stBit;
	} unCR_OVFCLR;										/* 0xFFC55218 - 0xFFC5521C */

	U1	u1Dummy2[0xFFC55220U - 0xFFC5521CU];			/* 0xFFC5521C - 0xFFC55220 */

	union												/* CR_SERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDF00					:1;				/* SEDF00 */
			U4	xSEDF01					:1;				/* SEDF01 */
			U4	xSEDF02					:1;				/* SEDF02 */
			U4	xSEDF03					:1;				/* SEDF03 */
			U4	xSEDF04					:1;				/* SEDF04 */
			U4	xSEDF05					:1;				/* SEDF05 */
			U4	xSEDF06					:1;				/* SEDF06 */
			U4	xSEDF07					:1;				/* SEDF07 */
			U4	b24Dummy1				:24;
		} stBit;
	} unCR_SERSTR;										/* 0xFFC55220 - 0xFFC55224 */

	union												/* CR_DERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDummy1					:1;
			U4	xDEDF00					:1;				/* DEDF00 */
			U4	xDummy2					:1;
			U4	xAFEF00					:1;				/* AFEF00 */
			U4	b28Dummy3				:28;
		} stBit;
	} unCR_DERSTR;										/* 0xFFC55224 - 0xFFC55228 */

	union												/* CR_OVFSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSERROVF0				:1;				/* SERROVF0 */
			U4	xSERROVF1				:1;				/* SERROVF1 */
			U4	b30Dummy1				:30;
		} stBit;
	} unCR_OVFSTR;										/* 0xFFC55228 - 0xFFC5522C */

	U1	u1Dummy3[0xFFC55230U - 0xFFC5522CU];			/* 0xFFC5522C - 0xFFC55230 */

	union												/* CR_SERINF */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDLINF00				:1;				/* SEDLINF00 */
			U4	xSEDLINF01				:1;				/* SEDLINF01 */
			U4	xSEDLINF02				:1;				/* SEDLINF02 */
			U4	xSEDLINF03				:1;				/* SEDLINF03 */
			U4	xSEDLINF04				:1;				/* SEDLINF04 */
			U4	xSEDLINF05				:1;				/* SEDLINF05 */
			U4	b2Dummy1				:2;
			U4	xSEDLINF08				:1;				/* SEDLINF08 */
			U4	xSEDLINF09				:1;				/* SEDLINF09 */
			U4	xSEDLINF10				:1;				/* SEDLINF10 */
			U4	xSEDLINF11				:1;				/* SEDLINF11 */
			U4	xSEDLINF12				:1;				/* SEDLINF12 */
			U4	xSEDLINF13				:1;				/* SEDLINF13 */
			U4	b2Dummy2				:2;
			U4	xSEDLINF16				:1;				/* SEDLINF16 */
			U4	xSEDLINF17				:1;				/* SEDLINF17 */
			U4	xSEDLINF18				:1;				/* SEDLINF18 */
			U4	xSEDLINF19				:1;				/* SEDLINF19 */
			U4	xSEDLINF20				:1;				/* SEDLINF20 */
			U4	xSEDLINF21				:1;				/* SEDLINF21 */
			U4	b2Dummy3				:2;
			U4	xSEDLINF24				:1;				/* SEDLINF24 */
			U4	xSEDLINF25				:1;				/* SEDLINF25 */
			U4	xSEDLINF26				:1;				/* SEDLINF26 */
			U4	xSEDLINF27				:1;				/* SEDLINF27 */
			U4	b4Dummy4				:4;
		} stBit;
	} unCR_SERINF;										/* 0xFFC55230 - 0xFFC55234 */

	U1	u1Dummy4[0xFFC55270U - 0xFFC55234U];			/* 0xFFC55234 - 0xFFC55270 */

	union												/* CR_nSEADR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b2Dummy1				:2;
			U4	b22SEADR0				:22;			/* SEADR0[23:2] */
			U4	b3Dummy2				:3;
			U4	b5SEDL					:5;				/* SEDL[4:0] */
		} stBit;
	} unCR_nSEADR[ECC_BUFFNUM_CRAM];					/* 0xFFC55270 - 0xFFC55290 */

	U1	u1Dummy5[0xFFC552F0U - 0xFFC55290U];			/* 0xFFC55290 - 0xFFC552F0 */

	union												/* CR_00DEADR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b2Dummy1				:2;
			U4	b22DEADR0				:22;			/* DEADR0[23:2] */
			U4	b3Dummy2				:3;
			U4	b5DEDL					:5;				/* DEDL[4:0] */
		} stBit;
	} unCR_00DEADR;										/* 0xFFC552F0 - 0xFFC552F4 */

	union												/* CR_00DESPIDCLR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xCLR00					:1;				/* DESPIDCLR00 */
			U4	xCLR01					:1;				/* DESPIDCLR01 */
			U4	xCLR02					:1;				/* DESPIDCLR02 */
			U4	xCLR03					:1;				/* DESPIDCLR03 */
			U4	xCLR04					:1;				/* DESPIDCLR04 */
			U4	xCLR05					:1;				/* DESPIDCLR05 */
			U4	xCLR06					:1;				/* DESPIDCLR06 */
			U4	xCLR07					:1;				/* DESPIDCLR07 */
			U4	xCLR08					:1;				/* DESPIDCLR08 */
			U4	xCLR09					:1;				/* DESPIDCLR09 */
			U4	xCLR10					:1;				/* DESPIDCLR10 */
			U4	xCLR11					:1;				/* DESPIDCLR11 */
			U4	xCLR12					:1;				/* DESPIDCLR12 */
			U4	xCLR13					:1;				/* DESPIDCLR13 */
			U4	xCLR14					:1;				/* DESPIDCLR14 */
			U4	xCLR15					:1;				/* DESPIDCLR15 */
			U4	xCLR16					:1;				/* DESPIDCLR16 */
			U4	xCLR17					:1;				/* DESPIDCLR17 */
			U4	xCLR18					:1;				/* DESPIDCLR18 */
			U4	xCLR19					:1;				/* DESPIDCLR19 */
			U4	xCLR20					:1;				/* DESPIDCLR20 */
			U4	xCLR21					:1;				/* DESPIDCLR21 */
			U4	xCLR22					:1;				/* DESPIDCLR22 */
			U4	xCLR23					:1;				/* DESPIDCLR23 */
			U4	xCLR24					:1;				/* DESPIDCLR24 */
			U4	xCLR25					:1;				/* DESPIDCLR25 */
			U4	xCLR26					:1;				/* DESPIDCLR26 */
			U4	xCLR27					:1;				/* DESPIDCLR27 */
			U4	xCLR28					:1;				/* DESPIDCLR28 */
			U4	xCLR29					:1;				/* DESPIDCLR29 */
			U4	xCLR30					:1;				/* DESPIDCLR30 */
			U4	xCLR31					:1;				/* DESPIDCLR31 */
		} stBit;
	} unCR_00DESPIDCLR;									/* 0xFFC552F4 - 0xFFC552F8 */

	union												/* CR_00DESPID */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSPID00					:1;				/* DESPID00 */
			U4	xSPID01					:1;				/* DESPID01 */
			U4	xSPID02					:1;				/* DESPID02 */
			U4	xSPID03					:1;				/* DESPID03 */
			U4	xSPID04					:1;				/* DESPID04 */
			U4	xSPID05					:1;				/* DESPID05 */
			U4	xSPID06					:1;				/* DESPID06 */
			U4	xSPID07					:1;				/* DESPID07 */
			U4	xSPID08					:1;				/* DESPID08 */
			U4	xSPID09					:1;				/* DESPID09 */
			U4	xSPID10					:1;				/* DESPID10 */
			U4	xSPID11					:1;				/* DESPID11 */
			U4	xSPID12					:1;				/* DESPID12 */
			U4	xSPID13					:1;				/* DESPID13 */
			U4	xSPID14					:1;				/* DESPID14 */
			U4	xSPID15					:1;				/* DESPID15 */
			U4	xSPID16					:1;				/* DESPID16 */
			U4	xSPID17					:1;				/* DESPID17 */
			U4	xSPID18					:1;				/* DESPID18 */
			U4	xSPID19					:1;				/* DESPID19 */
			U4	xSPID20					:1;				/* DESPID20 */
			U4	xSPID21					:1;				/* DESPID21 */
			U4	xSPID22					:1;				/* DESPID22 */
			U4	xSPID23					:1;				/* DESPID23 */
			U4	xSPID24					:1;				/* DESPID24 */
			U4	xSPID25					:1;				/* DESPID25 */
			U4	xSPID26					:1;				/* DESPID26 */
			U4	xSPID27					:1;				/* DESPID27 */
			U4	xSPID28					:1;				/* DESPID28 */
			U4	xSPID29					:1;				/* DESPID29 */
			U4	xSPID30					:1;				/* DESPID30 */
			U4	xSPID31					:1;				/* DESPID31 */
		} stBit;
	} unCR_00DESPID;									/* 0xFFC552F8 - 0xFFC552FC */

	U1	u1Dummy6[0xFFC55300U - 0xFFC552FCU];			/* 0xFFC552FC - 0xFFC55300 */

	union												/* CR_kSESPIDCLR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xCLR00					:1;				/* SESPIDCLR00 */
			U4	xCLR01					:1;				/* SESPIDCLR01 */
			U4	xCLR02					:1;				/* SESPIDCLR02 */
			U4	xCLR03					:1;				/* SESPIDCLR03 */
			U4	xCLR04					:1;				/* SESPIDCLR04 */
			U4	xCLR05					:1;				/* SESPIDCLR05 */
			U4	xCLR06					:1;				/* SESPIDCLR06 */
			U4	xCLR07					:1;				/* SESPIDCLR07 */
			U4	xCLR08					:1;				/* SESPIDCLR08 */
			U4	xCLR09					:1;				/* SESPIDCLR09 */
			U4	xCLR10					:1;				/* SESPIDCLR10 */
			U4	xCLR11					:1;				/* SESPIDCLR11 */
			U4	xCLR12					:1;				/* SESPIDCLR12 */
			U4	xCLR13					:1;				/* SESPIDCLR13 */
			U4	xCLR14					:1;				/* SESPIDCLR14 */
			U4	xCLR15					:1;				/* SESPIDCLR15 */
			U4	xCLR16					:1;				/* SESPIDCLR16 */
			U4	xCLR17					:1;				/* SESPIDCLR17 */
			U4	xCLR18					:1;				/* SESPIDCLR18 */
			U4	xCLR19					:1;				/* SESPIDCLR19 */
			U4	xCLR20					:1;				/* SESPIDCLR20 */
			U4	xCLR21					:1;				/* SESPIDCLR21 */
			U4	xCLR22					:1;				/* SESPIDCLR22 */
			U4	xCLR23					:1;				/* SESPIDCLR23 */
			U4	xCLR24					:1;				/* SESPIDCLR24 */
			U4	xCLR25					:1;				/* SESPIDCLR25 */
			U4	xCLR26					:1;				/* SESPIDCLR26 */
			U4	xCLR27					:1;				/* SESPIDCLR27 */
			U4	xCLR28					:1;				/* SESPIDCLR28 */
			U4	xCLR29					:1;				/* SESPIDCLR29 */
			U4	xCLR30					:1;				/* SESPIDCLR30 */
			U4	xCLR31					:1;				/* SESPIDCLR31 */
		} stBit;
	} unCR_kSESPIDCLR[ECC_BUFFNUM_CRAM];				/* 0xFFC55300 - 0xFFC55320 */

	U1	u1Dummy7[0xFFC55380U - 0xFFC55320U];			/* 0xFFC55320 - 0xFFC55380 */

	union												/* CR_kSESPID */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSPID00					:1;				/* SESPID00 */
			U4	xSPID01					:1;				/* SESPID01 */
			U4	xSPID02					:1;				/* SESPID02 */
			U4	xSPID03					:1;				/* SESPID03 */
			U4	xSPID04					:1;				/* SESPID04 */
			U4	xSPID05					:1;				/* SESPID05 */
			U4	xSPID06					:1;				/* SESPID06 */
			U4	xSPID07					:1;				/* SESPID07 */
			U4	xSPID08					:1;				/* SESPID08 */
			U4	xSPID09					:1;				/* SESPID09 */
			U4	xSPID10					:1;				/* SESPID10 */
			U4	xSPID11					:1;				/* SESPID11 */
			U4	xSPID12					:1;				/* SESPID12 */
			U4	xSPID13					:1;				/* SESPID13 */
			U4	xSPID14					:1;				/* SESPID14 */
			U4	xSPID15					:1;				/* SESPID15 */
			U4	xSPID16					:1;				/* SESPID16 */
			U4	xSPID17					:1;				/* SESPID17 */
			U4	xSPID18					:1;				/* SESPID18 */
			U4	xSPID19					:1;				/* SESPID19 */
			U4	xSPID20					:1;				/* SESPID20 */
			U4	xSPID21					:1;				/* SESPID21 */
			U4	xSPID22					:1;				/* SESPID22 */
			U4	xSPID23					:1;				/* SESPID23 */
			U4	xSPID24					:1;				/* SESPID24 */
			U4	xSPID25					:1;				/* SESPID25 */
			U4	xSPID26					:1;				/* SESPID26 */
			U4	xSPID27					:1;				/* SESPID27 */
			U4	xSPID28					:1;				/* SESPID28 */
			U4	xSPID29					:1;				/* SESPID29 */
			U4	xSPID30					:1;				/* SESPID30 */
			U4	xSPID31					:1;				/* SESPID31 */
		} stBit;
	} unCR_kSESPID[ECC_BUFFNUM_CRAM];					/* 0xFFC55380 - 0xFFC553A0 */

}	Reg_Ecc_MeccCap_CramType;


/* ECCCNT_IT_PE0CL0 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_IT_PE0CL0 ====================== */
/* ============================================================================ */
typedef	struct											/* ECCCNT_IT_PE0CL0 */
{
	union												/* ITECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	b2Dummy1				:2;
			U4	xAFEDIS					:1;				/* AFEDIS */
			U4	b28Dummy2				:28;
		} stBit;
	} unITECCCTL;										/* 0xFFC49000 - 0xFFC49004 */

	U1	u1Dummy1[0xFFC49020U - 0xFFC49004U];			/* 0xFFC49004 - 0xFFC49020 */

	union												/* ITAFINV */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b5Dummy1				:5;
			U4	b8AFINV					:8;				/* AFINV[12:5] */
			U4	b19Dummy2				:19;
		} stBit;
	} unITAFINV;										/* 0xFFC49020 - 0xFFC49024 */

}	Reg_Ecc_EccCnt_It_Pe0Cl0Type;


/* ECCCNT_IT_PE1CL0 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_IT_PE1CL0 ====================== */
/* ============================================================================ */
typedef	struct											/* ECCCNT_IT_PE1CL0 */
{
	union												/* ITECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	b2Dummy1				:2;
			U4	xAFEDIS					:1;				/* AFEDIS */
			U4	b28Dummy2				:28;
		} stBit;
	} unITECCCTL;										/* 0xFFC49080 - 0xFFC49084 */

	U1	u1Dummy1[0xFFC490A0U - 0xFFC49084U];			/* 0xFFC49084 - 0xFFC490A0 */

	union												/* ITAFINV */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b5Dummy1				:5;
			U4	b8AFINV					:8;				/* AFINV[12:5] */
			U4	b19Dummy2				:19;
		} stBit;
	} unITAFINV;										/* 0xFFC490A0 - 0xFFC490A4 */

}	Reg_Ecc_EccCnt_It_Pe1Cl0Type;


/* ECCCNT_IT_PE2CL1 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_IT_PE2CL1 ====================== */
/* ============================================================================ */
typedef	struct											/* ECCCNT_IT_PE2CL1 */
{
	union												/* ITECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	b2Dummy1				:2;
			U4	xAFEDIS					:1;				/* AFEDIS */
			U4	b28Dummy2				:28;
		} stBit;
	} unITECCCTL;										/* 0xFFC49100 - 0xFFC49104 */

	U1	u1Dummy1[0xFFC49120U - 0xFFC49104U];			/* 0xFFC49104 - 0xFFC49120 */

	union												/* ITAFINV */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b5Dummy1				:5;
			U4	b8AFINV					:8;				/* AFINV[12:5] */
			U4	b19Dummy2				:19;
		} stBit;
	} unITAFINV;										/* 0xFFC49120 - 0xFFC49124 */

}	Reg_Ecc_EccCnt_It_Pe2Cl1Type;


/* ECCCNT_IT_PE3CL1 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_IT_PE3CL1 ====================== */
/* ============================================================================ */
typedef	struct											/* ECCCNT_IT_PE3CL1 */
{
	union												/* ITECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	b2Dummy1				:2;
			U4	xAFEDIS					:1;				/* AFEDIS */
			U4	b28Dummy2				:28;
		} stBit;
	} unITECCCTL;										/* 0xFFC49180 - 0xFFC49184 */

	U1	u1Dummy1[0xFFC491A0U - 0xFFC49184U];			/* 0xFFC49184 - 0xFFC491A0 */

	union												/* ITAFINV */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b5Dummy1				:5;
			U4	b8AFINV					:8;				/* AFINV[12:5] */
			U4	b19Dummy2				:19;
		} stBit;
	} unITAFINV;										/* 0xFFC491A0 - 0xFFC491A4 */

}	Reg_Ecc_EccCnt_It_Pe3Cl1Type;


/* ECCCNT_IT_PE4CL2 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_IT_PE4CL2 ====================== */
/* ============================================================================ */
typedef	struct											/* ECCCNT_IT_PE4CL2 */
{
	union												/* ITECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	b2Dummy1				:2;
			U4	xAFEDIS					:1;				/* AFEDIS */
			U4	b28Dummy2				:28;
		} stBit;
	} unITECCCTL;										/* 0xFFC49200 - 0xFFC49204 */

	U1	u1Dummy1[0xFFC49220U - 0xFFC49204U];			/* 0xFFC49204 - 0xFFC49220 */

	union												/* ITAFINV */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b5Dummy1				:5;
			U4	b8AFINV					:8;				/* AFINV[12:5] */
			U4	b19Dummy2				:19;
		} stBit;
	} unITAFINV;										/* 0xFFC49220 - 0xFFC49224 */

}	Reg_Ecc_EccCnt_It_Pe4Cl2Type;


/* ECCCNT_IT_PE5CL2 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_IT_PE5CL2 ====================== */
/* ============================================================================ */
typedef	struct											/* ECCCNT_IT_PE5CL2 */
{
	union												/* ITECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	b2Dummy1				:2;
			U4	xAFEDIS					:1;				/* AFEDIS */
			U4	b28Dummy2				:28;
		} stBit;
	} unITECCCTL;										/* 0xFFC49280 - 0xFFC49284 */

	U1	u1Dummy1[0xFFC492A0U - 0xFFC49284U];			/* 0xFFC49284 - 0xFFC492A0 */

	union												/* ITAFINV */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b5Dummy1				:5;
			U4	b8AFINV					:8;				/* AFINV[12:5] */
			U4	b19Dummy2				:19;
		} stBit;
	} unITAFINV;										/* 0xFFC492A0 - 0xFFC492A4 */

}	Reg_Ecc_EccCnt_It_Pe5Cl2Type;


/* ECCCNT_ID_PE0CL0 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_ID_PE0CL0 ====================== */
/* ============================================================================ */
typedef	struct											/* ECCCNT_ID_PE0CL0 */
{
	union												/* IDECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	b2Dummy1				:2;
			U4	xAFEDIS					:1;				/* AFEDIS */
			U4	b28Dummy2				:28;
		} stBit;
	} unIDECCCTL;										/* 0xFFC49400 - 0xFFC49404 */

	U1	u1Dummy1[0xFFC49420U - 0xFFC49404U];			/* 0xFFC49404 - 0xFFC49420 */

	union												/* IDAFINV */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b3Dummy1				:3;
			U4	b10AFINV				:10;				/* AFINV[12:3] */
			U4	b19Dummy2				:19;
		} stBit;
	} unIDAFINV;										/* 0xFFC49420 - 0xFFC49424 */

}	Reg_Ecc_EccCnt_Id_Pe0Cl0Type;


/* ECCCNT_ID_PE1CL0 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_ID_PE1CL0 ====================== */
/* ============================================================================ */
typedef	struct											/* ECCCNT_ID_PE1CL0 */
{
	union												/* IDECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	b2Dummy1				:2;
			U4	xAFEDIS					:1;				/* AFEDIS */
			U4	b28Dummy2				:28;
		} stBit;
	} unIDECCCTL;										/* 0xFFC49480 - 0xFFC49484 */

	U1	u1Dummy1[0xFFC494A0U - 0xFFC49484U];			/* 0xFFC49484 - 0xFFC494A0 */

	union												/* IDAFINV */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b3Dummy1				:3;
			U4	b10AFINV				:10;				/* AFINV[12:3] */
			U4	b19Dummy2				:19;
		} stBit;
	} unIDAFINV;										/* 0xFFC494A0 - 0xFFC494A4 */

}	Reg_Ecc_EccCnt_Id_Pe1Cl0Type;


/* ECCCNT_ID_PE2CL1 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_ID_PE2CL1 ====================== */
/* ============================================================================ */
typedef	struct											/* ECCCNT_ID_PE2CL1 */
{
	union												/* IDECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	b2Dummy1				:2;
			U4	xAFEDIS					:1;				/* AFEDIS */
			U4	b28Dummy2				:28;
		} stBit;
	} unIDECCCTL;										/* 0xFFC49500 - 0xFFC49504 */

	U1	u1Dummy1[0xFFC49520U - 0xFFC49504U];			/* 0xFFC49504 - 0xFFC49520 */

	union												/* IDAFINV */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b3Dummy1				:3;
			U4	b10AFINV				:10;				/* AFINV[12:3] */
			U4	b19Dummy2				:19;
		} stBit;
	} unIDAFINV;										/* 0xFFC49520 - 0xFFC49524 */

}	Reg_Ecc_EccCnt_Id_Pe2Cl1Type;


/* ECCCNT_ID_PE3CL1 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_ID_PE3CL1 ====================== */
/* ============================================================================ */
typedef	struct											/* ECCCNT_ID_PE3CL1 */
{
	union												/* IDECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	b2Dummy1				:2;
			U4	xAFEDIS					:1;				/* AFEDIS */
			U4	b28Dummy2				:28;
		} stBit;
	} unIDECCCTL;										/* 0xFFC49580 - 0xFFC49584 */

	U1	u1Dummy1[0xFFC495A0U - 0xFFC49584U];			/* 0xFFC49584 - 0xFFC495A0 */

	union												/* IDAFINV */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b3Dummy1				:3;
			U4	b10AFINV				:10;				/* AFINV[12:3] */
			U4	b19Dummy2				:19;
		} stBit;
	} unIDAFINV;										/* 0xFFC495A0 - 0xFFC495A4 */

}	Reg_Ecc_EccCnt_Id_Pe3Cl1Type;


/* ECCCNT_ID_PE4CL2 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_ID_PE4CL2 ====================== */
/* ============================================================================ */
typedef	struct											/* ECCCNT_ID_PE4CL2 */
{
	union												/* IDECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	b2Dummy1				:2;
			U4	xAFEDIS					:1;				/* AFEDIS */
			U4	b28Dummy2				:28;
		} stBit;
	} unIDECCCTL;										/* 0xFFC49600 - 0xFFC49604 */

	U1	u1Dummy1[0xFFC49620U - 0xFFC49604U];			/* 0xFFC49604 - 0xFFC49620 */

	union												/* IDAFINV */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b3Dummy1				:3;
			U4	b10AFINV				:10;				/* AFINV[12:3] */
			U4	b19Dummy2				:19;
		} stBit;
	} unIDAFINV;										/* 0xFFC49620 - 0xFFC49624 */

}	Reg_Ecc_EccCnt_Id_Pe4Cl2Type;


/* ECCCNT_ID_PE5CL2 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_ID_PE5CL2 ====================== */
/* ============================================================================ */
typedef	struct											/* ECCCNT_ID_PE5CL2 */
{
	union												/* IDECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	b2Dummy1				:2;
			U4	xAFEDIS					:1;				/* AFEDIS */
			U4	b28Dummy2				:28;
		} stBit;
	} unIDECCCTL;										/* 0xFFC49680 - 0xFFC49684 */

	U1	u1Dummy1[0xFFC496A0U - 0xFFC49684U];			/* 0xFFC49684 - 0xFFC496A0 */

	union												/* IDAFINV */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b3Dummy1				:3;
			U4	b10AFINV				:10;				/* AFINV[12:3] */
			U4	b19Dummy2				:19;
		} stBit;
	} unIDAFINV;										/* 0xFFC496A0 - 0xFFC496A4 */

}	Reg_Ecc_EccCnt_Id_Pe5Cl2Type;


/* MECCCAP_IT_PE0CL0 */
/* ============================================================================ */
/* ============================ Module: MECCCAP_IT_PE0CL0 ===================== */
/* ============================================================================ */
typedef	struct											/* MECCCAP_IT_PE0CL0 */
{
	union												/* IT_ERRINT */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDIE					:1;				/* SEDIE */
			U4	xDEDIE					:1;				/* DEDIE */
			U4	xDummy1					:1;
			U4	xAFEIE					:1;				/* AFEIE */
			U4	b28Dummy2				:28;
		} stBit;
	} unIT_ERRINT;										/* 0xFFC53000 - 0xFFC53004 */

	U1	u1Dummy1[0xFFC53010U - 0xFFC53004U];			/* 0xFFC53004 - 0xFFC53010 */

	union												/* IT_SSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSSTCLR00				:1;				/* SSTCLR00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unIT_SSTCLR;										/* 0xFFC53010 - 0xFFC53014 */

	union												/* IT_DSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDSTCLR00				:1;				/* DSTCLR00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unIT_DSTCLR;										/* 0xFFC53014 - 0xFFC53018 */

	union												/* IT_OVFCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSERROVFCLR0			:1;				/* SERROVFCLR0 */
			U4	xSERROVFCLR1			:1;				/* SERROVFCLR1 */
			U4	b30Dummy1				:30;
		} stBit;
	} unIT_OVFCLR;										/* 0xFFC53018 - 0xFFC5301C */

	U1	u1Dummy2[0xFFC53020U - 0xFFC5301CU];			/* 0xFFC5301C - 0xFFC53020 */

	union												/* IT_SERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDF00					:1;				/* SEDF00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unIT_SERSTR;										/* 0xFFC53020 - 0xFFC53024 */

	union												/* IT_DERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDummy1					:1;
			U4	xDEDF00					:1;				/* DEDF00 */
			U4	xDummy2					:1;
			U4	xAFEF00					:1;				/* AFEF00 */
			U4	b28Dummy3				:28;
		} stBit;
	} unIT_DERSTR;										/* 0xFFC53024 - 0xFFC53028 */

	union												/* IT_OVFSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSERROVF0				:1;				/* SERROVF0 */
			U4	xSERROVF1				:1;				/* SERROVF1 */
			U4	b30Dummy1				:30;
		} stBit;
	} unIT_OVFSTR;										/* 0xFFC53028 - 0xFFC5302C */

	U1	u1Dummy3[0xFFC53030U - 0xFFC5302CU];			/* 0xFFC5302C - 0xFFC53030 */

	union												/* IT_SERINF */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDLINF00				:1;				/* SEDLINF00 */
			U4	xSEDLINF01				:1;				/* SEDLINF01 */
			U4	xSEDLINF02				:1;				/* SEDLINF02 */
			U4	xSEDLINF03				:1;				/* SEDLINF03 */
			U4	b28Dummy1				:28;
		} stBit;
	} unIT_SERINF;										/* 0xFFC53030 - 0xFFC53034 */

	U1	u1Dummy4[0xFFC53070U - 0xFFC53034U];			/* 0xFFC53034 - 0xFFC53070 */

	union												/* IT_00SEADR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b5Dummy1				:5;
			U4	b8SEADR0				:8;				/* SEADR0[12:5] */
			U4	b14Dummy2				:14;
			U4	b5SEDL					:5;				/* SEDL[4:0] */
		} stBit;
	} unIT_00SEADR;										/* 0xFFC53070 - 0xFFC53074 */

	U1	u1Dummy5[0xFFC530F0U - 0xFFC53074U];			/* 0xFFC53074 - 0xFFC530F0 */

	union												/* IT_00DEADR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b5Dummy1				:5;
			U4	b8DEADR0				:8;				/* DEADR0[12:5] */
			U4	b14Dummy2				:14;
			U4	b5DEDL					:5;				/* DEDL[4:0] */
		} stBit;
	} unIT_00DEADR;										/* 0xFFC530F0 - 0xFFC530F4 */

}	Reg_Ecc_MeccCap_It_Pe0Cl0Type;


/* MECCCAP_IT_PE1CL0 */
/* ============================================================================ */
/* ============================ Module: MECCCAP_IT_PE1CL0 ===================== */
/* ============================================================================ */
typedef	struct											/* MECCCAP_IT_PE1CL0 */
{
	union												/* IT_ERRINT */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDIE					:1;				/* SEDIE */
			U4	xDEDIE					:1;				/* DEDIE */
			U4	xDummy1					:1;
			U4	xAFEIE					:1;				/* AFEIE */
			U4	b28Dummy2				:28;
		} stBit;
	} unIT_ERRINT;										/* 0xFFC53200 - 0xFFC53204 */

	U1	u1Dummy1[0xFFC53210U - 0xFFC53204U];			/* 0xFFC53204 - 0xFFC53210 */

	union												/* IT_SSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSSTCLR00				:1;				/* SSTCLR00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unIT_SSTCLR;										/* 0xFFC53210 - 0xFFC53214 */

	union												/* IT_DSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDSTCLR00				:1;				/* DSTCLR00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unIT_DSTCLR;										/* 0xFFC53214 - 0xFFC53218 */

	union												/* IT_OVFCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSERROVFCLR0			:1;				/* SERROVFCLR0 */
			U4	xSERROVFCLR1			:1;				/* SERROVFCLR1 */
			U4	b30Dummy1				:30;
		} stBit;
	} unIT_OVFCLR;										/* 0xFFC53218 - 0xFFC5321C */

	U1	u1Dummy2[0xFFC53220U - 0xFFC5321CU];			/* 0xFFC5321C - 0xFFC53220 */

	union												/* IT_SERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDF00					:1;				/* SEDF00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unIT_SERSTR;										/* 0xFFC53220 - 0xFFC53224 */

	union												/* IT_DERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDummy1					:1;
			U4	xDEDF00					:1;				/* DEDF00 */
			U4	xDummy2					:1;
			U4	xAFEF00					:1;				/* AFEF00 */
			U4	b28Dummy3				:28;
		} stBit;
	} unIT_DERSTR;										/* 0xFFC53224 - 0xFFC53228 */

	union												/* IT_OVFSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSERROVF0				:1;				/* SERROVF0 */
			U4	xSERROVF1				:1;				/* SERROVF1 */
			U4	b30Dummy1				:30;
		} stBit;
	} unIT_OVFSTR;										/* 0xFFC53228 - 0xFFC5322C */

	U1	u1Dummy3[0xFFC53230U - 0xFFC5322CU];			/* 0xFFC5322C - 0xFFC53230 */

	union												/* IT_SERINF */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDLINF00				:1;				/* SEDLINF00 */
			U4	xSEDLINF01				:1;				/* SEDLINF01 */
			U4	xSEDLINF02				:1;				/* SEDLINF02 */
			U4	xSEDLINF03				:1;				/* SEDLINF03 */
			U4	b28Dummy1				:28;
		} stBit;
	} unIT_SERINF;										/* 0xFFC53230 - 0xFFC53234 */

	U1	u1Dummy4[0xFFC53270U - 0xFFC53234U];			/* 0xFFC53234 - 0xFFC53270 */

	union												/* IT_00SEADR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b5Dummy1				:5;
			U4	b8SEADR0				:8;				/* SEADR0[12:5] */
			U4	b14Dummy2				:14;
			U4	b5SEDL					:5;				/* SEDL[4:0] */
		} stBit;
	} unIT_00SEADR;										/* 0xFFC53270 - 0xFFC53274 */

	U1	u1Dummy5[0xFFC532F0U - 0xFFC53274U];			/* 0xFFC53274 - 0xFFC532F0 */

	union												/* IT_00DEADR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b5Dummy1				:5;
			U4	b8DEADR0				:8;				/* DEADR0[12:5] */
			U4	b14Dummy2				:14;
			U4	b5DEDL					:5;				/* DEDL[4:0] */
		} stBit;
	} unIT_00DEADR;										/* 0xFFC532F0 - 0xFFC532F4 */

}	Reg_Ecc_MeccCap_It_Pe1Cl0Type;


/* MECCCAP_IT_PE2CL1 */
/* ============================================================================ */
/* ============================ Module: MECCCAP_IT_PE2CL1 ===================== */
/* ============================================================================ */
typedef	struct											/* MECCCAP_IT_PE2CL1 */
{
	union												/* IT_ERRINT */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDIE					:1;				/* SEDIE */
			U4	xDEDIE					:1;				/* DEDIE */
			U4	xDummy1					:1;
			U4	xAFEIE					:1;				/* AFEIE */
			U4	b28Dummy2				:28;
		} stBit;
	} unIT_ERRINT;										/* 0xFFC53400 - 0xFFC53404 */

	U1	u1Dummy1[0xFFC53410U - 0xFFC53404U];			/* 0xFFC53404 - 0xFFC53410 */

	union												/* IT_SSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSSTCLR00				:1;				/* SSTCLR00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unIT_SSTCLR;										/* 0xFFC53410 - 0xFFC53414 */

	union												/* IT_DSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDSTCLR00				:1;				/* DSTCLR00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unIT_DSTCLR;										/* 0xFFC53414 - 0xFFC53418 */

	union												/* IT_OVFCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSERROVFCLR0			:1;				/* SERROVFCLR0 */
			U4	xSERROVFCLR1			:1;				/* SERROVFCLR1 */
			U4	b30Dummy1				:30;
		} stBit;
	} unIT_OVFCLR;										/* 0xFFC53418 - 0xFFC5341C */

	U1	u1Dummy2[0xFFC53420U - 0xFFC5341CU];			/* 0xFFC5341C - 0xFFC53420 */

	union												/* IT_SERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDF00					:1;				/* SEDF00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unIT_SERSTR;										/* 0xFFC53420 - 0xFFC53424 */

	union												/* IT_DERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDummy1					:1;
			U4	xDEDF00					:1;				/* DEDF00 */
			U4	xDummy2					:1;
			U4	xAFEF00					:1;				/* AFEF00 */
			U4	b28Dummy3				:28;
		} stBit;
	} unIT_DERSTR;										/* 0xFFC53424 - 0xFFC53428 */

	union												/* IT_OVFSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSERROVF0				:1;				/* SERROVF0 */
			U4	xSERROVF1				:1;				/* SERROVF1 */
			U4	b30Dummy1				:30;
		} stBit;
	} unIT_OVFSTR;										/* 0xFFC53428 - 0xFFC5342C */

	U1	u1Dummy3[0xFFC53430U - 0xFFC5342CU];			/* 0xFFC5342C - 0xFFC53430 */

	union												/* IT_SERINF */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDLINF00				:1;				/* SEDLINF00 */
			U4	xSEDLINF01				:1;				/* SEDLINF01 */
			U4	xSEDLINF02				:1;				/* SEDLINF02 */
			U4	xSEDLINF03				:1;				/* SEDLINF03 */
			U4	b28Dummy1				:28;
		} stBit;
	} unIT_SERINF;										/* 0xFFC53430 - 0xFFC53434 */

	U1	u1Dummy4[0xFFC53470U - 0xFFC53434U];			/* 0xFFC53434 - 0xFFC53470 */

	union												/* IT_00SEADR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b5Dummy1				:5;
			U4	b8SEADR0				:8;				/* SEADR0[12:5] */
			U4	b14Dummy2				:14;
			U4	b5SEDL					:5;				/* SEDL[4:0] */
		} stBit;
	} unIT_00SEADR;										/* 0xFFC53470 - 0xFFC53474 */

	U1	u1Dummy5[0xFFC534F0U - 0xFFC53474U];			/* 0xFFC53474 - 0xFFC534F0 */

	union												/* IT_00DEADR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b5Dummy1				:5;
			U4	b8DEADR0				:8;				/* DEADR0[12:5] */
			U4	b14Dummy2				:14;
			U4	b5DEDL					:5;				/* DEDL[4:0] */
		} stBit;
	} unIT_00DEADR;										/* 0xFFC534F0 - 0xFFC534F4 */

}	Reg_Ecc_MeccCap_It_Pe2Cl1Type;


/* MECCCAP_IT_PE3CL1 */
/* ============================================================================ */
/* ============================ Module: MECCCAP_IT_PE3CL1 ===================== */
/* ============================================================================ */
typedef	struct											/* MECCCAP_IT_PE3CL1 */
{
	union												/* IT_ERRINT */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDIE					:1;				/* SEDIE */
			U4	xDEDIE					:1;				/* DEDIE */
			U4	xDummy1					:1;
			U4	xAFEIE					:1;				/* AFEIE */
			U4	b28Dummy2				:28;
		} stBit;
	} unIT_ERRINT;										/* 0xFFC53600 - 0xFFC53604 */

	U1	u1Dummy1[0xFFC53610U - 0xFFC53604U];			/* 0xFFC53604 - 0xFFC53610 */

	union												/* IT_SSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSSTCLR00				:1;				/* SSTCLR00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unIT_SSTCLR;										/* 0xFFC53610 - 0xFFC53614 */

	union												/* IT_DSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDSTCLR00				:1;				/* DSTCLR00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unIT_DSTCLR;										/* 0xFFC53614 - 0xFFC53618 */

	union												/* IT_OVFCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSERROVFCLR0			:1;				/* SERROVFCLR0 */
			U4	xSERROVFCLR1			:1;				/* SERROVFCLR1 */
			U4	b30Dummy1				:30;
		} stBit;
	} unIT_OVFCLR;										/* 0xFFC53618 - 0xFFC5361C */

	U1	u1Dummy2[0xFFC53620U - 0xFFC5361CU];			/* 0xFFC5361C - 0xFFC53620 */

	union												/* IT_SERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDF00					:1;				/* SEDF00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unIT_SERSTR;										/* 0xFFC53620 - 0xFFC53624 */

	union												/* IT_DERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDummy1					:1;
			U4	xDEDF00					:1;				/* DEDF00 */
			U4	xDummy2					:1;
			U4	xAFEF00					:1;				/* AFEF00 */
			U4	b28Dummy3				:28;
		} stBit;
	} unIT_DERSTR;										/* 0xFFC53624 - 0xFFC53628 */

	union												/* IT_OVFSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSERROVF0				:1;				/* SERROVF0 */
			U4	xSERROVF1				:1;				/* SERROVF1 */
			U4	b30Dummy1				:30;
		} stBit;
	} unIT_OVFSTR;										/* 0xFFC53628 - 0xFFC5362C */

	U1	u1Dummy3[0xFFC53630U - 0xFFC5362CU];			/* 0xFFC5362C - 0xFFC53630 */

	union												/* IT_SERINF */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDLINF00				:1;				/* SEDLINF00 */
			U4	xSEDLINF01				:1;				/* SEDLINF01 */
			U4	xSEDLINF02				:1;				/* SEDLINF02 */
			U4	xSEDLINF03				:1;				/* SEDLINF03 */
			U4	b28Dummy1				:28;
		} stBit;
	} unIT_SERINF;										/* 0xFFC53630 - 0xFFC53634 */

	U1	u1Dummy4[0xFFC53670U - 0xFFC53634U];			/* 0xFFC53634 - 0xFFC53670 */

	union												/* IT_00SEADR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b5Dummy1				:5;
			U4	b8SEADR0				:8;				/* SEADR0[12:5] */
			U4	b14Dummy2				:14;
			U4	b5SEDL					:5;				/* SEDL[4:0] */
		} stBit;
	} unIT_00SEADR;										/* 0xFFC53670 - 0xFFC53674 */

	U1	u1Dummy5[0xFFC536F0U - 0xFFC53674U];			/* 0xFFC53674 - 0xFFC536F0 */

	union												/* IT_00DEADR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b5Dummy1				:5;
			U4	b8DEADR0				:8;				/* DEADR0[12:5] */
			U4	b14Dummy2				:14;
			U4	b5DEDL					:5;				/* DEDL[4:0] */
		} stBit;
	} unIT_00DEADR;										/* 0xFFC536F0 - 0xFFC536F4 */

}	Reg_Ecc_MeccCap_It_Pe3Cl1Type;


/* MECCCAP_IT_PE4CL2 */
/* ============================================================================ */
/* ============================ Module: MECCCAP_IT_PE4CL2 ===================== */
/* ============================================================================ */
typedef	struct											/* MECCCAP_IT_PE4CL2 */
{
	union												/* IT_ERRINT */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDIE					:1;				/* SEDIE */
			U4	xDEDIE					:1;				/* DEDIE */
			U4	xDummy1					:1;
			U4	xAFEIE					:1;				/* AFEIE */
			U4	b28Dummy2				:28;
		} stBit;
	} unIT_ERRINT;										/* 0xFFC53800 - 0xFFC53804 */

	U1	u1Dummy1[0xFFC53810U - 0xFFC53804U];			/* 0xFFC53804 - 0xFFC53810 */

	union												/* IT_SSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSSTCLR00				:1;				/* SSTCLR00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unIT_SSTCLR;										/* 0xFFC53810 - 0xFFC53814 */

	union												/* IT_DSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDSTCLR00				:1;				/* DSTCLR00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unIT_DSTCLR;										/* 0xFFC53814 - 0xFFC53818 */

	union												/* IT_OVFCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSERROVFCLR0			:1;				/* SERROVFCLR0 */
			U4	xSERROVFCLR1			:1;				/* SERROVFCLR1 */
			U4	b30Dummy1				:30;
		} stBit;
	} unIT_OVFCLR;										/* 0xFFC53818 - 0xFFC5381C */

	U1	u1Dummy2[0xFFC53820U - 0xFFC5381CU];			/* 0xFFC5381C - 0xFFC53820 */

	union												/* IT_SERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDF00					:1;				/* SEDF00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unIT_SERSTR;										/* 0xFFC53820 - 0xFFC53824 */

	union												/* IT_DERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDummy1					:1;
			U4	xDEDF00					:1;				/* DEDF00 */
			U4	xDummy2					:1;
			U4	xAFEF00					:1;				/* AFEF00 */
			U4	b28Dummy3				:28;
		} stBit;
	} unIT_DERSTR;										/* 0xFFC53824 - 0xFFC53828 */

	union												/* IT_OVFSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSERROVF0				:1;				/* SERROVF0 */
			U4	xSERROVF1				:1;				/* SERROVF1 */
			U4	b30Dummy1				:30;
		} stBit;
	} unIT_OVFSTR;										/* 0xFFC53828 - 0xFFC5382C */

	U1	u1Dummy3[0xFFC53830U - 0xFFC5382CU];			/* 0xFFC5382C - 0xFFC53830 */

	union												/* IT_SERINF */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDLINF00				:1;				/* SEDLINF00 */
			U4	xSEDLINF01				:1;				/* SEDLINF01 */
			U4	xSEDLINF02				:1;				/* SEDLINF02 */
			U4	xSEDLINF03				:1;				/* SEDLINF03 */
			U4	b28Dummy1				:28;
		} stBit;
	} unIT_SERINF;										/* 0xFFC53830 - 0xFFC53834 */

	U1	u1Dummy4[0xFFC53870U - 0xFFC53834U];			/* 0xFFC53834 - 0xFFC53870 */

	union												/* IT_00SEADR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b5Dummy1				:5;
			U4	b8SEADR0				:8;				/* SEADR0[12:5] */
			U4	b14Dummy2				:14;
			U4	b5SEDL					:5;				/* SEDL[4:0] */
		} stBit;
	} unIT_00SEADR;										/* 0xFFC53870 - 0xFFC53874 */

	U1	u1Dummy5[0xFFC538F0U - 0xFFC53874U];			/* 0xFFC53874 - 0xFFC538F0 */

	union												/* IT_00DEADR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b5Dummy1				:5;
			U4	b8DEADR0				:8;				/* DEADR0[12:5] */
			U4	b14Dummy2				:14;
			U4	b5DEDL					:5;				/* DEDL[4:0] */
		} stBit;
	} unIT_00DEADR;										/* 0xFFC538F0 - 0xFFC538F4 */

}	Reg_Ecc_MeccCap_It_Pe4Cl2Type;


/* MECCCAP_IT_PE5CL2 */
/* ============================================================================ */
/* ============================ Module: MECCCAP_IT_PE5CL2 ===================== */
/* ============================================================================ */
typedef	struct											/* MECCCAP_IT_PE5CL2 */
{
	union												/* IT_ERRINT */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDIE					:1;				/* SEDIE */
			U4	xDEDIE					:1;				/* DEDIE */
			U4	xDummy1					:1;
			U4	xAFEIE					:1;				/* AFEIE */
			U4	b28Dummy2				:28;
		} stBit;
	} unIT_ERRINT;										/* 0xFFC53A00 - 0xFFC53A04 */

	U1	u1Dummy1[0xFFC53A10U - 0xFFC53A04U];			/* 0xFFC53A04 - 0xFFC53A10 */

	union												/* IT_SSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSSTCLR00				:1;				/* SSTCLR00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unIT_SSTCLR;										/* 0xFFC53A10 - 0xFFC53A14 */

	union												/* IT_DSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDSTCLR00				:1;				/* DSTCLR00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unIT_DSTCLR;										/* 0xFFC53A14 - 0xFFC53A18 */

	union												/* IT_OVFCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSERROVFCLR0			:1;				/* SERROVFCLR0 */
			U4	xSERROVFCLR1			:1;				/* SERROVFCLR1 */
			U4	b30Dummy1				:30;
		} stBit;
	} unIT_OVFCLR;										/* 0xFFC53A18 - 0xFFC53A1C */

	U1	u1Dummy2[0xFFC53A20U - 0xFFC53A1CU];			/* 0xFFC53A1C - 0xFFC53A20 */

	union												/* IT_SERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDF00					:1;				/* SEDF00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unIT_SERSTR;										/* 0xFFC53A20 - 0xFFC53A24 */

	union												/* IT_DERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDummy1					:1;
			U4	xDEDF00					:1;				/* DEDF00 */
			U4	xDummy2					:1;
			U4	xAFEF00					:1;				/* AFEF00 */
			U4	b28Dummy3				:28;
		} stBit;
	} unIT_DERSTR;										/* 0xFFC53A24 - 0xFFC53A28 */

	union												/* IT_OVFSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSERROVF0				:1;				/* SERROVF0 */
			U4	xSERROVF1				:1;				/* SERROVF1 */
			U4	b30Dummy1				:30;
		} stBit;
	} unIT_OVFSTR;										/* 0xFFC53A28 - 0xFFC53A2C */

	U1	u1Dummy3[0xFFC53A30U - 0xFFC53A2CU];			/* 0xFFC53A2C - 0xFFC53A30 */

	union												/* IT_SERINF */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDLINF00				:1;				/* SEDLINF00 */
			U4	xSEDLINF01				:1;				/* SEDLINF01 */
			U4	xSEDLINF02				:1;				/* SEDLINF02 */
			U4	xSEDLINF03				:1;				/* SEDLINF03 */
			U4	b28Dummy1				:28;
		} stBit;
	} unIT_SERINF;										/* 0xFFC53A30 - 0xFFC53A34 */

	U1	u1Dummy4[0xFFC53A70U - 0xFFC53A34U];			/* 0xFFC53A34 - 0xFFC53A70 */

	union												/* IT_00SEADR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b5Dummy1				:5;
			U4	b8SEADR0				:8;				/* SEADR0[12:5] */
			U4	b14Dummy2				:14;
			U4	b5SEDL					:5;				/* SEDL[4:0] */
		} stBit;
	} unIT_00SEADR;										/* 0xFFC53A70 - 0xFFC53A74 */

	U1	u1Dummy5[0xFFC53AF0U - 0xFFC53A74U];			/* 0xFFC53A74 - 0xFFC53AF0 */

	union												/* IT_00DEADR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b5Dummy1				:5;
			U4	b8DEADR0				:8;				/* DEADR0[12:5] */
			U4	b14Dummy2				:14;
			U4	b5DEDL					:5;				/* DEDL[4:0] */
		} stBit;
	} unIT_00DEADR;										/* 0xFFC53AF0 - 0xFFC53AF4 */

}	Reg_Ecc_MeccCap_It_Pe5Cl2Type;


/* MECCCAP_ID_PE0CL0 */
/* ============================================================================ */
/* ============================ Module: MECCCAP_ID_PE0CL0 ===================== */
/* ============================================================================ */
typedef	struct											/* MECCCAP_ID_PE0CL0 */
{
	union												/* ID_ERRINT */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDIE					:1;				/* SEDIE */
			U4	xDEDIE					:1;				/* DEDIE */
			U4	xDummy1					:1;
			U4	xAFEIE					:1;				/* AFEIE */
			U4	b28Dummy2				:28;
		} stBit;
	} unID_ERRINT;										/* 0xFFC54000 - 0xFFC54004 */

	U1	u1Dummy1[0xFFC54010U - 0xFFC54004U];			/* 0xFFC54004 - 0xFFC54010 */

	union												/* ID_SSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSSTCLR00				:1;				/* SSTCLR00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unID_SSTCLR;										/* 0xFFC54010 - 0xFFC54014 */

	union												/* ID_DSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDSTCLR00				:1;				/* DSTCLR00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unID_DSTCLR;										/* 0xFFC54014 - 0xFFC54018 */

	union												/* ID_OVFCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSERROVFCLR0			:1;				/* SERROVFCLR0 */
			U4	xSERROVFCLR1			:1;				/* SERROVFCLR1 */
			U4	b30Dummy1				:30;
		} stBit;
	} unID_OVFCLR;										/* 0xFFC54018 - 0xFFC5401C */

	U1	u1Dummy2[0xFFC54020U - 0xFFC5401CU];			/* 0xFFC5401C - 0xFFC54020 */

	union												/* ID_SERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDF00					:1;				/* SEDF00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unID_SERSTR;										/* 0xFFC54020 - 0xFFC54024 */

	union												/* ID_DERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDummy1					:1;
			U4	xDEDF00					:1;				/* DEDF00 */
			U4	xDummy2					:1;
			U4	xAFEF00					:1;				/* AFEF00 */
			U4	b28Dummy3				:28;
		} stBit;
	} unID_DERSTR;										/* 0xFFC54024 - 0xFFC54028 */

	union												/* ID_OVFSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSERROVF0				:1;				/* SERROVF0 */
			U4	xSERROVF1				:1;				/* SERROVF1 */
			U4	b30Dummy1				:30;
		} stBit;
	} unID_OVFSTR;										/* 0xFFC54028 - 0xFFC5402C */

	U1	u1Dummy3[0xFFC54030U - 0xFFC5402CU];			/* 0xFFC5402C - 0xFFC54030 */

	union												/* ID_SERINF */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDLINF00				:1;				/* SEDLINF00 */
			U4	xSEDLINF01				:1;				/* SEDLINF01 */
			U4	xSEDLINF02				:1;				/* SEDLINF02 */
			U4	xSEDLINF03				:1;				/* SEDLINF03 */
			U4	b28Dummy1				:28;
		} stBit;
	} unID_SERINF;										/* 0xFFC54030 - 0xFFC54034 */

	U1	u1Dummy4[0xFFC54070U - 0xFFC54034U];			/* 0xFFC54034 - 0xFFC54070 */

	union												/* ID_00SEADR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b3Dummy1				:3;
			U4	b10SEADR0				:10;			/* SEADR0[12:3] */
			U4	b14Dummy2				:14;
			U4	b5SEDL					:5;				/* SEDL[4:0] */
		} stBit;
	} unID_00SEADR;										/* 0xFFC54070 - 0xFFC54074 */

	U1	u1Dummy5[0xFFC540F0U - 0xFFC54074U];			/* 0xFFC54074 - 0xFFC540F0 */

	union												/* ID_00DEADR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b3Dummy1				:3;
			U4	b10DEADR0				:10;			/* DEADR0[12:3] */
			U4	b14Dummy2				:14;
			U4	b5DEDL					:5;				/* DEDL[4:0] */
		} stBit;
	} unID_00DEADR;										/* 0xFFC540F0 - 0xFFC540F4 */

}	Reg_Ecc_MeccCap_Id_Pe0Cl0Type;


/* MECCCAP_ID_PE1CL0 */
/* ============================================================================ */
/* ============================ Module: MECCCAP_ID_PE1CL0 ===================== */
/* ============================================================================ */
typedef	struct											/* MECCCAP_ID_PE1CL0 */
{
	union												/* ID_ERRINT */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDIE					:1;				/* SEDIE */
			U4	xDEDIE					:1;				/* DEDIE */
			U4	xDummy1					:1;
			U4	xAFEIE					:1;				/* AFEIE */
			U4	b28Dummy2				:28;
		} stBit;
	} unID_ERRINT;										/* 0xFFC54200 - 0xFFC54204 */

	U1	u1Dummy1[0xFFC54210U - 0xFFC54204U];			/* 0xFFC54204 - 0xFFC54210 */

	union												/* ID_SSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSSTCLR00				:1;				/* SSTCLR00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unID_SSTCLR;										/* 0xFFC54210 - 0xFFC54214 */

	union												/* ID_DSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDSTCLR00				:1;				/* DSTCLR00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unID_DSTCLR;										/* 0xFFC54214 - 0xFFC54218 */

	union												/* ID_OVFCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSERROVFCLR0			:1;				/* SERROVFCLR0 */
			U4	xSERROVFCLR1			:1;				/* SERROVFCLR1 */
			U4	b30Dummy1				:30;
		} stBit;
	} unID_OVFCLR;										/* 0xFFC54218 - 0xFFC5421C */

	U1	u1Dummy2[0xFFC54220U - 0xFFC5421CU];			/* 0xFFC5421C - 0xFFC54220 */

	union												/* ID_SERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDF00					:1;				/* SEDF00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unID_SERSTR;										/* 0xFFC54220 - 0xFFC54224 */

	union												/* ID_DERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDummy1					:1;
			U4	xDEDF00					:1;				/* DEDF00 */
			U4	xDummy2					:1;
			U4	xAFEF00					:1;				/* AFEF00 */
			U4	b28Dummy3				:28;
		} stBit;
	} unID_DERSTR;										/* 0xFFC54224 - 0xFFC54228 */

	union												/* ID_OVFSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSERROVF0				:1;				/* SERROVF0 */
			U4	xSERROVF1				:1;				/* SERROVF1 */
			U4	b30Dummy1				:30;
		} stBit;
	} unID_OVFSTR;										/* 0xFFC54228 - 0xFFC5422C */

	U1	u1Dummy3[0xFFC54230U - 0xFFC5422CU];			/* 0xFFC5422C - 0xFFC54230 */

	union												/* ID_SERINF */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDLINF00				:1;				/* SEDLINF00 */
			U4	xSEDLINF01				:1;				/* SEDLINF01 */
			U4	xSEDLINF02				:1;				/* SEDLINF02 */
			U4	xSEDLINF03				:1;				/* SEDLINF03 */
			U4	b28Dummy1				:28;
		} stBit;
	} unID_SERINF;										/* 0xFFC54230 - 0xFFC54234 */

	U1	u1Dummy4[0xFFC54270U - 0xFFC54234U];			/* 0xFFC54234 - 0xFFC54270 */

	union												/* ID_00SEADR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b3Dummy1				:3;
			U4	b10SEADR0				:10;			/* SEADR0[12:3] */
			U4	b14Dummy2				:14;
			U4	b5SEDL					:5;				/* SEDL[4:0] */
		} stBit;
	} unID_00SEADR;										/* 0xFFC54270 - 0xFFC54274 */

	U1	u1Dummy5[0xFFC542F0U - 0xFFC54274U];			/* 0xFFC54274 - 0xFFC542F0 */

	union												/* ID_00DEADR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b3Dummy1				:3;
			U4	b10DEADR0				:10;			/* DEADR0[12:3] */
			U4	b14Dummy2				:14;
			U4	b5DEDL					:5;				/* DEDL[4:0] */
		} stBit;
	} unID_00DEADR;										/* 0xFFC542F0 - 0xFFC542F4 */

}	Reg_Ecc_MeccCap_Id_Pe1Cl0Type;


/* MECCCAP_ID_PE2CL1 */
/* ============================================================================ */
/* ============================ Module: MECCCAP_ID_PE2CL1 ===================== */
/* ============================================================================ */
typedef	struct											/* MECCCAP_ID_PE2CL1 */
{
	union												/* ID_ERRINT */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDIE					:1;				/* SEDIE */
			U4	xDEDIE					:1;				/* DEDIE */
			U4	xDummy1					:1;
			U4	xAFEIE					:1;				/* AFEIE */
			U4	b28Dummy2				:28;
		} stBit;
	} unID_ERRINT;										/* 0xFFC54400 - 0xFFC54404 */

	U1	u1Dummy1[0xFFC54410U - 0xFFC54404U];			/* 0xFFC54404 - 0xFFC54410 */

	union												/* ID_SSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSSTCLR00				:1;				/* SSTCLR00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unID_SSTCLR;										/* 0xFFC54410 - 0xFFC54414 */

	union												/* ID_DSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDSTCLR00				:1;				/* DSTCLR00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unID_DSTCLR;										/* 0xFFC54414 - 0xFFC54418 */

	union												/* ID_OVFCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSERROVFCLR0			:1;				/* SERROVFCLR0 */
			U4	xSERROVFCLR1			:1;				/* SERROVFCLR1 */
			U4	b30Dummy1				:30;
		} stBit;
	} unID_OVFCLR;										/* 0xFFC54418 - 0xFFC5441C */

	U1	u1Dummy2[0xFFC54420U - 0xFFC5441CU];			/* 0xFFC5441C - 0xFFC54420 */

	union												/* ID_SERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDF00					:1;				/* SEDF00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unID_SERSTR;										/* 0xFFC54420 - 0xFFC54424 */

	union												/* ID_DERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDummy1					:1;
			U4	xDEDF00					:1;				/* DEDF00 */
			U4	xDummy2					:1;
			U4	xAFEF00					:1;				/* AFEF00 */
			U4	b28Dummy3				:28;
		} stBit;
	} unID_DERSTR;										/* 0xFFC54424 - 0xFFC54428 */

	union												/* ID_OVFSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSERROVF0				:1;				/* SERROVF0 */
			U4	xSERROVF1				:1;				/* SERROVF1 */
			U4	b30Dummy1				:30;
		} stBit;
	} unID_OVFSTR;										/* 0xFFC54428 - 0xFFC5442C */

	U1	u1Dummy3[0xFFC54430U - 0xFFC5442CU];			/* 0xFFC5442C - 0xFFC54430 */

	union												/* ID_SERINF */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDLINF00				:1;				/* SEDLINF00 */
			U4	xSEDLINF01				:1;				/* SEDLINF01 */
			U4	xSEDLINF02				:1;				/* SEDLINF02 */
			U4	xSEDLINF03				:1;				/* SEDLINF03 */
			U4	b28Dummy1				:28;
		} stBit;
	} unID_SERINF;										/* 0xFFC54430 - 0xFFC54434 */

	U1	u1Dummy4[0xFFC54470U - 0xFFC54434U];			/* 0xFFC54434 - 0xFFC54470 */

	union												/* ID_00SEADR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b3Dummy1				:3;
			U4	b10SEADR0				:10;			/* SEADR0[12:3] */
			U4	b14Dummy2				:14;
			U4	b5SEDL					:5;				/* SEDL[4:0] */
		} stBit;
	} unID_00SEADR;										/* 0xFFC54470 - 0xFFC54474 */

	U1	u1Dummy5[0xFFC544F0U - 0xFFC54474U];			/* 0xFFC54474 - 0xFFC544F0 */

	union												/* ID_00DEADR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b3Dummy1				:3;
			U4	b10DEADR0				:10;			/* DEADR0[12:3] */
			U4	b14Dummy2				:14;
			U4	b5DEDL					:5;				/* DEDL[4:0] */
		} stBit;
	} unID_00DEADR;										/* 0xFFC544F0 - 0xFFC544F4 */

}	Reg_Ecc_MeccCap_Id_Pe2Cl1Type;


/* MECCCAP_ID_PE3CL1 */
/* ============================================================================ */
/* ============================ Module: MECCCAP_ID_PE3CL1 ===================== */
/* ============================================================================ */
typedef	struct											/* MECCCAP_ID_PE3CL1 */
{
	union												/* ID_ERRINT */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDIE					:1;				/* SEDIE */
			U4	xDEDIE					:1;				/* DEDIE */
			U4	xDummy1					:1;
			U4	xAFEIE					:1;				/* AFEIE */
			U4	b28Dummy2				:28;
		} stBit;
	} unID_ERRINT;										/* 0xFFC54600 - 0xFFC54604 */

	U1	u1Dummy1[0xFFC54610U - 0xFFC54604U];			/* 0xFFC54604 - 0xFFC54610 */

	union												/* ID_SSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSSTCLR00				:1;				/* SSTCLR00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unID_SSTCLR;										/* 0xFFC54610 - 0xFFC54614 */

	union												/* ID_DSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDSTCLR00				:1;				/* DSTCLR00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unID_DSTCLR;										/* 0xFFC54614 - 0xFFC54618 */

	union												/* ID_OVFCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSERROVFCLR0			:1;				/* SERROVFCLR0 */
			U4	xSERROVFCLR1			:1;				/* SERROVFCLR1 */
			U4	b30Dummy1				:30;
		} stBit;
	} unID_OVFCLR;										/* 0xFFC54618 - 0xFFC5461C */

	U1	u1Dummy2[0xFFC54620U - 0xFFC5461CU];			/* 0xFFC5461C - 0xFFC54620 */

	union												/* ID_SERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDF00					:1;				/* SEDF00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unID_SERSTR;										/* 0xFFC54620 - 0xFFC54624 */

	union												/* ID_DERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDummy1					:1;
			U4	xDEDF00					:1;				/* DEDF00 */
			U4	xDummy2					:1;
			U4	xAFEF00					:1;				/* AFEF00 */
			U4	b28Dummy3				:28;
		} stBit;
	} unID_DERSTR;										/* 0xFFC54624 - 0xFFC54628 */

	union												/* ID_OVFSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSERROVF0				:1;				/* SERROVF0 */
			U4	xSERROVF1				:1;				/* SERROVF1 */
			U4	b30Dummy1				:30;
		} stBit;
	} unID_OVFSTR;										/* 0xFFC54628 - 0xFFC5462C */

	U1	u1Dummy3[0xFFC54630U - 0xFFC5462CU];			/* 0xFFC5462C - 0xFFC54630 */

	union												/* ID_SERINF */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDLINF00				:1;				/* SEDLINF00 */
			U4	xSEDLINF01				:1;				/* SEDLINF01 */
			U4	xSEDLINF02				:1;				/* SEDLINF02 */
			U4	xSEDLINF03				:1;				/* SEDLINF03 */
			U4	b28Dummy1				:28;
		} stBit;
	} unID_SERINF;										/* 0xFFC54630 - 0xFFC54634 */

	U1	u1Dummy4[0xFFC54670U - 0xFFC54634U];			/* 0xFFC54634 - 0xFFC54670 */

	union												/* ID_00SEADR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b3Dummy1				:3;
			U4	b10SEADR0				:10;			/* SEADR0[12:3] */
			U4	b14Dummy2				:14;
			U4	b5SEDL					:5;				/* SEDL[4:0] */
		} stBit;
	} unID_00SEADR;										/* 0xFFC54670 - 0xFFC54674 */

	U1	u1Dummy5[0xFFC546F0U - 0xFFC54674U];			/* 0xFFC54674 - 0xFFC546F0 */

	union												/* ID_00DEADR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b3Dummy1				:3;
			U4	b10DEADR0				:10;			/* DEADR0[12:3] */
			U4	b14Dummy2				:14;
			U4	b5DEDL					:5;				/* DEDL[4:0] */
		} stBit;
	} unID_00DEADR;										/* 0xFFC546F0 - 0xFFC546F4 */

}	Reg_Ecc_MeccCap_Id_Pe3Cl1Type;


/* MECCCAP_ID_PE4CL2 */
/* ============================================================================ */
/* ============================ Module: MECCCAP_ID_PE4CL2 ===================== */
/* ============================================================================ */
typedef	struct											/* MECCCAP_ID_PE4CL2 */
{
	union												/* ID_ERRINT */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDIE					:1;				/* SEDIE */
			U4	xDEDIE					:1;				/* DEDIE */
			U4	xDummy1					:1;
			U4	xAFEIE					:1;				/* AFEIE */
			U4	b28Dummy2				:28;
		} stBit;
	} unID_ERRINT;										/* 0xFFC54800 - 0xFFC54804 */

	U1	u1Dummy1[0xFFC54810U - 0xFFC54804U];			/* 0xFFC54804 - 0xFFC54810 */

	union												/* ID_SSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSSTCLR00				:1;				/* SSTCLR00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unID_SSTCLR;										/* 0xFFC54810 - 0xFFC54814 */

	union												/* ID_DSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDSTCLR00				:1;				/* DSTCLR00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unID_DSTCLR;										/* 0xFFC54814 - 0xFFC54818 */

	union												/* ID_OVFCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSERROVFCLR0			:1;				/* SERROVFCLR0 */
			U4	xSERROVFCLR1			:1;				/* SERROVFCLR1 */
			U4	b30Dummy1				:30;
		} stBit;
	} unID_OVFCLR;										/* 0xFFC54818 - 0xFFC5481C */

	U1	u1Dummy2[0xFFC54820U - 0xFFC5481CU];			/* 0xFFC5481C - 0xFFC54820 */

	union												/* ID_SERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDF00					:1;				/* SEDF00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unID_SERSTR;										/* 0xFFC54820 - 0xFFC54824 */

	union												/* ID_DERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDummy1					:1;
			U4	xDEDF00					:1;				/* DEDF00 */
			U4	xDummy2					:1;
			U4	xAFEF00					:1;				/* AFEF00 */
			U4	b28Dummy3				:28;
		} stBit;
	} unID_DERSTR;										/* 0xFFC54824 - 0xFFC54828 */

	union												/* ID_OVFSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSERROVF0				:1;				/* SERROVF0 */
			U4	xSERROVF1				:1;				/* SERROVF1 */
			U4	b30Dummy1				:30;
		} stBit;
	} unID_OVFSTR;										/* 0xFFC54828 - 0xFFC5482C */

	U1	u1Dummy3[0xFFC54830U - 0xFFC5482CU];			/* 0xFFC5482C - 0xFFC54830 */

	union												/* ID_SERINF */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDLINF00				:1;				/* SEDLINF00 */
			U4	xSEDLINF01				:1;				/* SEDLINF01 */
			U4	xSEDLINF02				:1;				/* SEDLINF02 */
			U4	xSEDLINF03				:1;				/* SEDLINF03 */
			U4	b28Dummy1				:28;
		} stBit;
	} unID_SERINF;										/* 0xFFC54830 - 0xFFC54834 */

	U1	u1Dummy4[0xFFC54870U - 0xFFC54834U];			/* 0xFFC54834 - 0xFFC54870 */

	union												/* ID_00SEADR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b3Dummy1				:3;
			U4	b10SEADR0				:10;			/* SEADR0[12:3] */
			U4	b14Dummy2				:14;
			U4	b5SEDL					:5;				/* SEDL[4:0] */
		} stBit;
	} unID_00SEADR;										/* 0xFFC54870 - 0xFFC54874 */

	U1	u1Dummy5[0xFFC548F0U - 0xFFC54874U];			/* 0xFFC54874 - 0xFFC548F0 */

	union												/* ID_00DEADR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b3Dummy1				:3;
			U4	b10DEADR0				:10;			/* DEADR0[12:3] */
			U4	b14Dummy2				:14;
			U4	b5DEDL					:5;				/* DEDL[4:0] */
		} stBit;
	} unID_00DEADR;										/* 0xFFC548F0 - 0xFFC548F4 */

}	Reg_Ecc_MeccCap_Id_Pe4Cl2Type;


/* MECCCAP_ID_PE5CL2 */
/* ============================================================================ */
/* ============================ Module: MECCCAP_ID_PE5CL2 ===================== */
/* ============================================================================ */
typedef	struct											/* MECCCAP_ID_PE5CL2 */
{
	union												/* ID_ERRINT */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDIE					:1;				/* SEDIE */
			U4	xDEDIE					:1;				/* DEDIE */
			U4	xDummy1					:1;
			U4	xAFEIE					:1;				/* AFEIE */
			U4	b28Dummy2				:28;
		} stBit;
	} unID_ERRINT;										/* 0xFFC54A00 - 0xFFC54A04 */

	U1	u1Dummy1[0xFFC54A10U - 0xFFC54A04U];			/* 0xFFC54A04 - 0xFFC54A10 */

	union												/* ID_SSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSSTCLR00				:1;				/* SSTCLR00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unID_SSTCLR;										/* 0xFFC54A10 - 0xFFC54A14 */

	union												/* ID_DSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDSTCLR00				:1;				/* DSTCLR00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unID_DSTCLR;										/* 0xFFC54A14 - 0xFFC54A18 */

	union												/* ID_OVFCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSERROVFCLR0			:1;				/* SERROVFCLR0 */
			U4	xSERROVFCLR1			:1;				/* SERROVFCLR1 */
			U4	b30Dummy1				:30;
		} stBit;
	} unID_OVFCLR;										/* 0xFFC54A18 - 0xFFC54A1C */

	U1	u1Dummy2[0xFFC54A20U - 0xFFC54A1CU];			/* 0xFFC54A1C - 0xFFC54A20 */

	union												/* ID_SERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDF00					:1;				/* SEDF00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unID_SERSTR;										/* 0xFFC54A20 - 0xFFC54A24 */

	union												/* ID_DERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDummy1					:1;
			U4	xDEDF00					:1;				/* DEDF00 */
			U4	xDummy2					:1;
			U4	xAFEF00					:1;				/* AFEF00 */
			U4	b28Dummy3				:28;
		} stBit;
	} unID_DERSTR;										/* 0xFFC54A24 - 0xFFC54A28 */

	union												/* ID_OVFSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSERROVF0				:1;				/* SERROVF0 */
			U4	xSERROVF1				:1;				/* SERROVF1 */
			U4	b30Dummy1				:30;
		} stBit;
	} unID_OVFSTR;										/* 0xFFC54A28 - 0xFFC54A2C */

	U1	u1Dummy3[0xFFC54A30U - 0xFFC54A2CU];			/* 0xFFC54A2C - 0xFFC54A30 */

	union												/* ID_SERINF */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDLINF00				:1;				/* SEDLINF00 */
			U4	xSEDLINF01				:1;				/* SEDLINF01 */
			U4	xSEDLINF02				:1;				/* SEDLINF02 */
			U4	xSEDLINF03				:1;				/* SEDLINF03 */
			U4	b28Dummy1				:28;
		} stBit;
	} unID_SERINF;										/* 0xFFC54A30 - 0xFFC54A34 */

	U1	u1Dummy4[0xFFC54A70U - 0xFFC54A34U];			/* 0xFFC54A34 - 0xFFC54A70 */

	union												/* ID_00SEADR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b3Dummy1				:3;
			U4	b10SEADR0				:10;			/* SEADR0[12:3] */
			U4	b14Dummy2				:14;
			U4	b5SEDL					:5;				/* SEDL[4:0] */
		} stBit;
	} unID_00SEADR;										/* 0xFFC54A70 - 0xFFC54A74 */

	U1	u1Dummy5[0xFFC54AF0U - 0xFFC54A74U];			/* 0xFFC54A74 - 0xFFC54AF0 */

	union												/* ID_00DEADR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b3Dummy1				:3;
			U4	b10DEADR0				:10;			/* DEADR0[12:3] */
			U4	b14Dummy2				:14;
			U4	b5DEDL					:5;				/* DEDL[4:0] */
		} stBit;
	} unID_00DEADR;										/* 0xFFC54AF0 - 0xFFC54AF4 */

}	Reg_Ecc_MeccCap_Id_Pe5Cl2Type;


/* ECCCNT_DTS */
/* ============================================================================ */
/* ============================ Module: ECCCNT_DTS ============================ */
/* ============================================================================ */
typedef	struct											/* ECCCNT_DTS */
{
	union												/* DRECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	xDummy1					:1;
			U4	xAFEDIS					:1;				/* AFEDIS */
			U4	b28Dummy2				:28;
		} stBit;
	} unDRECCCTL;										/* 0xFFC4A000 - 0xFFC4A004 */

	U1	u1Dummy1[0xFFC4A010U - 0xFFC4A004U];			/* 0xFFC4A004 - 0xFFC4A010 */

	union												/* DRECCTSTCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDummy1					:1;
			U4	xECCTST					:1;				/* ECCTST */
			U4	b30Dummy1				:30;
		} stBit;
	} unDRECCTSTCTL;									/* 0xFFC4A010 - 0xFFC4A014 */

	U1	u1Dummy2[0xFFC4A020U - 0xFFC4A014U];			/* 0xFFC4A014 - 0xFFC4A020 */

	union												/* DRAFINV */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b2Dummy1				:2;
			U4	b10AFINV				:10;			/* AFINV[11:2] */
			U4	b20Dummy2				:20;
		} stBit;
	} unDRAFINV;										/* 0xFFC4A020 - 0xFFC4A024 */

	U1	u1Dummy3[0xFFC4A030U - 0xFFC4A024U];			/* 0xFFC4A024 - 0xFFC4A030 */

	union												/* DRECCTSTDIN0 */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
	} unDRECCTSTDIN0;									/* 0xFFC4A030 - 0xFFC4A034 */

	U1	u1Dummy4[0xFFC4A040U - 0xFFC4A034U];			/* 0xFFC4A034 - 0xFFC4A040 */

	union												/* DRECCTSTEIN */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b7ECC					:7;				/* ECC[6:0] */
			U4	b25Dummy1				:25;
		} stBit;
	} unDRECCTSTEIN;									/* 0xFFC4A040 - 0xFFC4A044 */

	U1	u1Dummy5[0xFFC4A050U - 0xFFC4A044U];			/* 0xFFC4A044 - 0xFFC4A050 */

	U4	u4DRTDATBFDATAF0;								/* 0xFFC4A050 - 0xFFC4A054 */

	U1	u1Dummy6[0xFFC4A060U - 0xFFC4A054U];			/* 0xFFC4A054 - 0xFFC4A060 */

	union												/* DRTDATBFECCF */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b7BFECC0				:7;				/* BFECC0[6:0] */
			U4	b25Dummy1				:25;
		} stBit;
	} unDRTDATBFECCF;									/* 0xFFC4A060 - 0xFFC4A064 */

}	Reg_Ecc_EccCnt_DtsType;


/* ECCCNT_DMDE0 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_DMDE0 ========================== */
/* ============================================================================ */
typedef	struct											/* ECCCNT_DMDE0 */
{
	union												/* DEECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	xDummy1				:1;
			U4	xAFEDIS					:1;				/* AFEDIS */
			U4	b28Dummy2				:28;
		} stBit;
	} unDEECCCTL;										/* 0xFFC4A400 - 0xFFC4A404 */

	U1	u1Dummy1[0xFFC4A410U - 0xFFC4A404U];			/* 0xFFC4A404 - 0xFFC4A410 */

	union												/* DEECCTSTCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xAFSEL					:1;				/* AFSEL */
			U4	xECCTST					:1;				/* ECCTST */
			U4	b30Dummy1				:30;
		} stBit;
	} unDEECCTSTCTL;									/* 0xFFC4A410 - 0xFFC4A414 */

	U1	u1Dummy2[0xFFC4A420U - 0xFFC4A414U];			/* 0xFFC4A414 - 0xFFC4A420 */

	union												/* DEAFINV */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b2Dummy1				:2;
			U4	b10AFINV				:10;			/* AFINV[11:2] */
			U4	b20Dummy2				:20;
		} stBit;
	} unDEAFINV;										/* 0xFFC4A420 - 0xFFC4A424 */

	U1	u1Dummy3[0xFFC4A430U - 0xFFC4A424U];			/* 0xFFC4A424 - 0xFFC4A430 */

	union												/* DEECCTSTDIN0 */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
	} unDEECCTSTDIN0;									/* 0xFFC4A430 - 0xFFC4A434 */

	U1	u1Dummy4[0xFFC4A440U - 0xFFC4A434U];			/* 0xFFC4A434 - 0xFFC4A440 */

	union												/* DEECCTSTEIN */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b7ECC					:7;				/* ECC[6:0] */
			U4	b25Dummy1				:25;
		} stBit;
	} unDEECCTSTEIN;									/* 0xFFC4A440 - 0xFFC4A444 */

	U1	u1Dummy5[0xFFC4A450U - 0xFFC4A444U];			/* 0xFFC4A444 - 0xFFC4A450 */

	U4	u4DETDATBFDATAF0;								/* 0xFFC4A450 - 0xFFC4A454 */

	U1	u1Dummy6[0xFFC4A460U - 0xFFC4A454U];			/* 0xFFC4A454 - 0xFFC4A460 */

	union												/* DETDATBFECCF */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b7BFECC0				:7;				/* BFECC0[6:0] */
			U4	b25Dummy1				:25;
		} stBit;
	} unDETDATBFECCF;									/* 0xFFC4A460 - 0xFFC4A464 */

}	Reg_Ecc_EccCnt_Dmde0Type;


/* ECCCNT_DMDA0 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_DMDA0 ========================== */
/* ============================================================================ */
typedef	struct											/* ECCCNT_DMDA0 */
{
	union												/* DAECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	b30Dummy1				:30;
		} stBit;
	} unDAECCCTL;										/* 0xFFC4A480 - 0xFFC4A484 */

	U1	u1Dummy1[0xFFC4A490U - 0xFFC4A484U];			/* 0xFFC4A484 - 0xFFC4A490 */

	union												/* DAECCTSTCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDummy1					:1;
			U4	xECCTST					:1;				/* ECCTST */
			U4	b30Dummy2				:30;
		} stBit;
	} unDAECCTSTCTL;									/* 0xFFC4A490 - 0xFFC4A494 */

	U1	u1Dummy2[0xFFC4A4B0U - 0xFFC4A494U];			/* 0xFFC4A494 - 0xFFC4A4B0 */

	union												/* DAECCTSTDIN0 */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
	} unDAECCTSTDIN0;									/* 0xFFC4A4B0 - 0xFFC4A4B4 */

	union												/* DAECCTSTDIN1 */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
	} unDAECCTSTDIN1;									/* 0xFFC4A4B4 - 0xFFC4A4B8 */

	U1	u1Dummy3[0xFFC4A4C0U - 0xFFC4A4B8U];			/* 0xFFC4A4B8 - 0xFFC4A4C0 */

	union												/* DAECCTSTEIN */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct
		{
			U4	b8ECC					:8;				/* ECC[7:0] */
			U4	b24Dummy1				:24;
		} stBit;
	} unDAECCTSTEIN;									/* 0xFFC4A4C0 - 0xFFC4A4C4 */

	U1	u1Dummy4[0xFFC4A4D0U - 0xFFC4A4C4U];			/* 0xFFC4A4C4 - 0xFFC4A4D0 */

	U4	u4DATDATBFDATAF0;								/* 0xFFC4A4D0 - 0xFFC4A4D4 */

	U4	u4DATDATBFDATAF1;								/* 0xFFC4A4D4 - 0xFFC4A4D8 */

	U1	u1Dummy5[0xFFC4A4E0U - 0xFFC4A4D8U];			/* 0xFFC4A4D8 - 0xFFC4A4E0 */

	union												/* DATDATBFECCF */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b8BFECC0				:8;				/* BFECC0[7:0] */
			U4	b24Dummy1				:24;
		} stBit;
	} unDATDATBFECCF;									/* 0xFFC4A4E0 - 0xFFC4A4E4 */

}	Reg_Ecc_EccCnt_Dmda0Type;


/* ECCCNT_DMDE1 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_DMDE1 ========================== */
/* ============================================================================ */
typedef	struct											/* ECCCNT_DMDE1 */
{
	union												/* DEECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	xDummy1					:1;
			U4	xAFEDIS					:1;				/* AFEDIS */
			U4	b28Dummy2				:28;
		} stBit;
	} unDEECCCTL;										/* 0xFFC4A500 - 0xFFC4A504 */

	U1	u1Dummy1[0xFFC4A510U - 0xFFC4A504U];			/* 0xFFC4A504 - 0xFFC4A510 */

	union												/* DEECCTSTCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xAFSEL					:1;				/* AFSEL */
			U4	xECCTST					:1;				/* ECCTST */
			U4	b30Dummy1				:30;
		} stBit;
	} unDEECCTSTCTL;									/* 0xFFC4A510 - 0xFFC4A514 */

	U1	u1Dummy2[0xFFC4A520U - 0xFFC4A514U];			/* 0xFFC4A514 - 0xFFC4A520 */

	union												/* DEAFINV */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b2Dummy1				:2;
			U4	b10AFINV				:10;			/* AFINV[11:2] */
			U4	b20Dummy2				:20;
		} stBit;
	} unDEAFINV;										/* 0xFFC4A520 - 0xFFC4A524 */

	U1	u1Dummy3[0xFFC4A530U - 0xFFC4A524U];			/* 0xFFC4A524 - 0xFFC4A530 */

	union												/* DEECCTSTDIN0 */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
	} unDEECCTSTDIN0;									/* 0xFFC4A530 - 0xFFC4A534 */

	U1	u1Dummy4[0xFFC4A540U - 0xFFC4A534U];			/* 0xFFC4A534 - 0xFFC4A540 */

	union												/* DEECCTSTEIN */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b7ECC					:7;				/* ECC[6:0] */
			U4	b25Dummy1				:25;
		} stBit;
	} unDEECCTSTEIN;									/* 0xFFC4A540 - 0xFFC4A544 */

	U1	u1Dummy5[0xFFC4A550U - 0xFFC4A544U];			/* 0xFFC4A544 - 0xFFC4A550 */

	U4	u4DETDATBFDATAF0;								/* 0xFFC4A550 - 0xFFC4A554 */

	U1	u1Dummy6[0xFFC4A560U - 0xFFC4A554U];			/* 0xFFC4A554 - 0xFFC4A560 */

	union												/* DETDATBFECCF */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b7BFECC0				:7;				/* BFECC0[6:0] */
			U4	b25Dummy1				:25;
		} stBit;
	} unDETDATBFECCF;									/* 0xFFC4A560 - 0xFFC4A564 */

}	Reg_Ecc_EccCnt_Dmde1Type;


/* ECCCNT_DMDA1 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_DMDA1 ========================== */
/* ============================================================================ */
typedef	struct											/* ECCCNT_DMDA1 */
{
	union												/* DAECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	b30Dummy1				:30;
		} stBit;
	} unDAECCCTL;										/* 0xFFC4A580 - 0xFFC4A584 */

	U1	u1Dummy1[0xFFC4A590U - 0xFFC4A584U];			/* 0xFFC4A584 - 0xFFC4A590 */

	union												/* DAECCTSTCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDummy1					:1;
			U4	xECCTST					:1;				/* ECCTST */
			U4	b30Dummy2				:30;
		} stBit;
	} unDAECCTSTCTL;									/* 0xFFC4A590 - 0xFFC4A594 */

	U1	u1Dummy2[0xFFC4A5B0U - 0xFFC4A594U];			/* 0xFFC4A594 - 0xFFC4A5B0 */

	union												/* DAECCTSTDIN0 */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
	} unDAECCTSTDIN0;									/* 0xFFC4A5B0 - 0xFFC4A5B4 */

	union												/* DAECCTSTDIN1 */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
	} unDAECCTSTDIN1;									/* 0xFFC4A5B4 - 0xFFC4A5B8 */

	U1	u1Dummy3[0xFFC4A5C0U - 0xFFC4A5B8U];			/* 0xFFC4A5B8 - 0xFFC4A5C0 */

	union												/* DAECCTSTEIN */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct
		{
			U4	b8ECC					:8;				/* ECC[7:0] */
			U4	b24Dummy1				:24;
		} stBit;
	} unDAECCTSTEIN;									/* 0xFFC4A5C0 - 0xFFC4A5C4 */

	U1	u1Dummy4[0xFFC4A5D0U - 0xFFC4A5C4U];			/* 0xFFC4A5C4 - 0xFFC4A5D0 */

	U4	u4DATDATBFDATAF0;								/* 0xFFC4A5D0 - 0xFFC4A5D4 */

	U4	u4DATDATBFDATAF1;								/* 0xFFC4A5D4 - 0xFFC4A5D8 */

	U1	u1Dummy5[0xFFC4A5E0U - 0xFFC4A5D8U];			/* 0xFFC4A5D8 - 0xFFC4A5E0 */

	union												/* DATDATBFECCF */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b8BFECC0				:8;				/* BFECC0[7:0] */
			U4	b24Dummy1				:24;
		} stBit;
	} unDATDATBFECCF;									/* 0xFFC4A5E0 - 0xFFC4A5E4 */

}	Reg_Ecc_EccCnt_Dmda1Type;


/* MECCCAP_DTS */
/* ============================================================================ */
/* ============================ Module: MECCCAP_DTS =========================== */
/* ============================================================================ */
typedef	struct											/* MECCCAP_DTS */
{
	union												/* DR_ERRINT */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDIE					:1;				/* SEDIE */
			U4	xDEDIE					:1;				/* DEDIE */
			U4	xDummy1					:1;
			U4	xAFEIE					:1;				/* AFEIE */
			U4	b3Dummy2				:3;
			U4	xSEOVFIE				:1;				/* SEOVFIE */
			U4	b24Dummy				:24;
		} stBit;
	} unDR_ERRINT;										/* 0xFFC55600 - 0xFFC55604 */

	U1	u1Dummy1[0xFFC55610U - 0xFFC55604U];			/* 0xFFC55604 - 0xFFC55610 */

	union												/* DR_SSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSSTCLR00				:1;				/* SSTCLR00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unDR_SSTCLR;										/* 0xFFC55610 - 0xFFC55614 */

	union												/* DR_DSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDSTCLR00				:1;				/* DSTCLR00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unDR_DSTCLR;										/* 0xFFC55614 - 0xFFC55618 */

	union												/* DR_OVFCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSERROVFCLR0			:1;				/* SERROVFCLR0 */
			U4	b31Dummy1				:31;
		} stBit;
	} unDR_OVFCLR;										/* 0xFFC55618 - 0xFFC5561C */

	U1	u1Dummy2[0xFFC55620U - 0xFFC5561CU];			/* 0xFFC5561C - 0xFFC55620 */

	union												/* DR_SERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDF00					:1;				/* SEDF00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unDR_SERSTR;										/* 0xFFC55620 - 0xFFC55624 */

	union												/* DR_DERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDummy1					:1;
			U4	xDEDF00					:1;				/* DEDF00 */
			U4	xDummy2					:1;
			U4	xAFEF00					:1;				/* AFEF00 */
			U4	b28Dummy3				:28;
		} stBit;
	} unDR_DERSTR;										/* 0xFFC55624 - 0xFFC55628 */

	union												/* DR_OVFSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSERROVF0				:1;				/* SERROVF0 */
			U4	b31Dummy1				:31;
		} stBit;
	} unDR_OVFSTR;										/* 0xFFC55628 - 0xFFC5562C */

	U1	u1Dummy3[0xFFC55630U - 0xFFC5562CU];			/* 0xFFC5562C - 0xFFC55630 */

	union												/* DR_SERINF */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDLINF00				:1;				/* SEDLINF00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unDR_SERINF;										/* 0xFFC55630 - 0xFFC55634 */

	U1	u1Dummy4[0xFFC55670U - 0xFFC55634U];			/* 0xFFC55634 - 0xFFC55670 */

	union												/* DR_00SEADR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b2Dummy1				:2;
			U4	b10SEADR0				:10;			/* SEADR0[11:2] */
			U4	b15Dummy2				:15;
			U4	b5SEDL					:5;				/* SEDL[4:0] */
		} stBit;
	} unDR_00SEADR;										/* 0xFFC55670 - 0xFFC55674 */

	U1	u1Dummy5[0xFFC556F0U - 0xFFC55674U];			/* 0xFFC55674 - 0xFFC556F0 */

	union												/* DR_00DEADR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b2Dummy1				:2;
			U4	b10DEADR0				:10;			/* DEADR0[11:2] */
			U4	b15Dummy2				:15;
			U4	b5DEDL					:5;				/* DEDL[4:0] */
		} stBit;
	} unDR_00DEADR;										/* 0xFFC556F0 - 0xFFC556F4 */

}	Reg_Ecc_MeccCap_DtsType;


/* MECCCAP_DMDE0 */
/* ============================================================================ */
/* ============================ Module: MECCCAP_DMDE0 ========================= */
/* ============================================================================ */
typedef	struct											/* MECCCAP_DMDE0 */
{
	union												/* DE_ERRINT */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDIE					:1;				/* SEDIE */
			U4	xDEDIE					:1;				/* DEDIE */
			U4	xDummy1					:1;
			U4	xAFEIE					:1;				/* AFEIE */
			U4	b3Dummy2				:3;
			U4	xSEOVFIE				:1;				/* SEOVFIE */
			U4	b24Dummy3				:24;
		} stBit;
	} unDE_ERRINT;										/* 0xFFC55800 - 0xFFC55804 */

	U1	u1Dummy1[0xFFC55810U - 0xFFC55804U];			/* 0xFFC55804 - 0xFFC55810 */

	union												/* DE_SSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSSTCLR00				:1;				/* SSTCLR00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unDE_SSTCLR;										/* 0xFFC55810 - 0xFFC55814 */

	union												/* DE_DSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDSTCLR00				:1;				/* DSTCLR00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unDE_DSTCLR;										/* 0xFFC55814 - 0xFFC55818 */

	union												/* DE_OVFCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSERROVFCLR0			:1;				/* SERROVFCLR0 */
			U4	b31Dummy1				:31;
		} stBit;
	} unDE_OVFCLR;										/* 0xFFC55818 - 0xFFC5581C */

	U1	u1Dummy2[0xFFC55820U - 0xFFC5581CU];			/* 0xFFC5581C - 0xFFC55820 */

	union												/* DE_SERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDF00					:1;				/* SEDF00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unDE_SERSTR;										/* 0xFFC55820 - 0xFFC55824 */

	union												/* DE_DERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDummy1					:1;
			U4	xDEDF00					:1;				/* DEDF00 */
			U4	xDummy2					:1;
			U4	xAFEF00					:1;				/* AFEF00 */
			U4	b28Dummy2				:28;
		} stBit;
	} unDE_DERSTR;										/* 0xFFC55824 - 0xFFC55828 */

	union												/* DE_OVFSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSERROVF0				:1;				/* SERROVF0 */
			U4	b31Dummy1				:31;
		} stBit;
	} unDE_OVFSTR;										/* 0xFFC55828 - 0xFFC5582C */

	U1	u1Dummy3[0xFFC55830U - 0xFFC5582CU];			/* 0xFFC5582C - 0xFFC55830 */

	union												/* DE_SERINF */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDLINF00				:1;				/* SEDLINF00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unDE_SERINF;										/* 0xFFC55830 - 0xFFC55834 */

	U1	u1Dummy4[0xFFC55870U - 0xFFC55834U];			/* 0xFFC55834 - 0xFFC55870 */

	union												/* DE_00SEADR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b2Dummy1				:2;
			U4	b10SEADR0				:10;			/* SEADR0[11:2] */
			U4	b15Dummy2				:15;
			U4	b5SEDL					:5;				/* SEDL[4:0] */
		} stBit;
	} unDE_00SEADR;										/* 0xFFC55870 - 0xFFC55874 */

	U1	u1Dummy5[0xFFC558F0U - 0xFFC55874U];			/* 0xFFC55874 - 0xFFC558F0 */

	union												/* DE_00DEADR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b2Dummy1				:2;
			U4	b10DEADR0				:10;			/* DEADR0[11:2] */
			U4	b15Dummy2				:15;
			U4	b5DEDL					:5;				/* DEDL[4:0] */
		} stBit;
	} unDE_00DEADR;										/* 0xFFC558F0 - 0xFFC558F4 */

}	Reg_Ecc_MeccCap_Dmde0Type;


/* MECCCAP_DMDA0 */
/* ============================================================================ */
/* ============================ Module: MECCCAP_DMDA0 ========================= */
/* ============================================================================ */
typedef	struct											/* MECCCAP_DMDA0 */
{
	union												/* DA_ERRINT */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDIE					:1;				/* SEDIE */
			U4	xDEDIE					:1;				/* DEDIE */
			U4	b5Dummy1				:5;
			U4	xSEOVFIE				:1;				/* SEOVFIE */
			U4	b24Dummy2				:24;
		} stBit;
	} unDA_ERRINT;										/* 0xFFC55A00 - 0xFFC55A04 */

	U1	u1Dummy1[0xFFC55A10U - 0xFFC55A04U];			/* 0xFFC55A04 - 0xFFC55A10 */

	union												/* DA_SSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSSTCLR00				:1;				/* SSTCLR00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unDA_SSTCLR;										/* 0xFFC55A10 - 0xFFC55A14 */

	union												/* DA_DSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDSTCLR00				:1;				/* DSTCLR00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unDA_DSTCLR;										/* 0xFFC55A14 - 0xFFC55A18 */

	union												/* DA_OVFCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSERROVFCLR0			:1;				/* SERROVFCLR0 */
			U4	b31Dummy1				:31;
		} stBit;
	} unDA_OVFCLR;										/* 0xFFC55A18 - 0xFFC55A1C */

	U1	u1Dummy2[0xFFC55A20U - 0xFFC55A1CU];			/* 0xFFC55A1C - 0xFFC55A20 */

	union												/* DA_SERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDF00					:1;				/* SEDF00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unDA_SERSTR;										/* 0xFFC55A20 - 0xFFC55A24 */

	union												/* DA_DERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDummy1					:1;
			U4	xDEDF00					:1;				/* DEDF00 */
			U4	b30Dummy2				:30;
		} stBit;
	} unDA_DERSTR;										/* 0xFFC55A24 - 0xFFC55A28 */

	union												/* DA_OVFSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSERROVF0				:1;				/* SERROVF0 */
			U4	b31Dummy1				:31;
		} stBit;
	} unDA_OVFSTR;										/* 0xFFC55A28 - 0xFFC55A2C */

	U1	u1Dummy3[0xFFC55A30U - 0xFFC55A2CU];			/* 0xFFC55A2C - 0xFFC55A30 */

	union												/* DA_SERINF */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDLINF00				:1;				/* SEDLINF00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unDA_SERINF;										/* 0xFFC55A30 - 0xFFC55A34 */

	U1	u1Dummy4[0xFFC55A70U - 0xFFC55A34U];			/* 0xFFC55A34 - 0xFFC55A70 */

	union												/* DA_00SEADR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b3Dummy1				:3;
			U4	b8SEADR0				:8;				/* SEADR0[10:3] */
			U4	b16Dummy2				:16;
			U4	b5SEDL					:5;				/* SEDL[4:0] */
		} stBit;
	} unDA_00SEADR;										/* 0xFFC55A70 - 0xFFC55A74 */

	U1	u1Dummy5[0xFFC55AF0U - 0xFFC55A74U];			/* 0xFFC55A74 - 0xFFC55AF0 */

	union												/* DA_00DEADR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b3Dummy1				:3;
			U4	b8DEADR0				:8;				/* DEADR0[10:3] */
			U4	b16Dummy2				:16;
			U4	b5DEDL					:5;				/* DEDL[4:0] */
		} stBit;
	} unDA_00DEADR;										/* 0xFFC55AF0 - 0xFFC55AF4 */

}	Reg_Ecc_MeccCap_Dmda0Type;


/* MECCCAP_DMDE1 */
/* ============================================================================ */
/* ============================ Module: MECCCAP_DMDE1 ========================= */
/* ============================================================================ */
typedef	struct											/* MECCCAP_DMDE1 */
{
	union												/* DE_ERRINT */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDIE					:1;				/* SEDIE */
			U4	xDEDIE					:1;				/* DEDIE */
			U4	xDummy1					:1;
			U4	xAFEIE					:1;				/* AFEIE */
			U4	b3Dummy2				:3;
			U4	xSEOVFIE				:1;				/* SEOVFIE */
			U4	b24Dummy3				:24;
		} stBit;
	} unDE_ERRINT;										/* 0xFFC55C00 - 0xFFC55C04 */

	U1	u1Dummy1[0xFFC55C10U - 0xFFC55C04U];			/* 0xFFC55C04 - 0xFFC55C10 */

	union												/* DE_SSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSSTCLR00				:1;				/* SSTCLR00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unDE_SSTCLR;										/* 0xFFC55C10 - 0xFFC55C14 */

	union												/* DE_DSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDSTCLR00				:1;				/* DSTCLR00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unDE_DSTCLR;										/* 0xFFC55C14 - 0xFFC55C18 */

	union												/* DE_OVFCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSERROVFCLR0			:1;				/* SERROVFCLR0 */
			U4	b31Dummy1				:31;
		} stBit;
	} unDE_OVFCLR;										/* 0xFFC55C18 - 0xFFC55C1C */

	U1	u1Dummy2[0xFFC55C20U - 0xFFC55C1CU];			/* 0xFFC55C1C - 0xFFC55C20 */

	union												/* DE_SERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDF00					:1;				/* SEDF00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unDE_SERSTR;										/* 0xFFC55C20 - 0xFFC55C24 */

	union												/* DE_DERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDummy1					:1;
			U4	xDummy2					:1;
			U4	xAFEF00					:1;				/* AFEF00 */
			U4	b28Dummy2				:28;
		} stBit;
	} unDE_DERSTR;										/* 0xFFC55C24 - 0xFFC55C28 */

	union												/* DE_OVFSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSERROVF0				:1;				/* SERROVF0 */
			U4	b31Dummy1				:31;
		} stBit;
	} unDE_OVFSTR;										/* 0xFFC55C28 - 0xFFC55C2C */

	U1	u1Dummy3[0xFFC55C30U - 0xFFC55C2CU];			/* 0xFFC55C2C - 0xFFC55C30 */

	union												/* DE_SERINF */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDLINF00				:1;				/* SEDLINF00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unDE_SERINF;										/* 0xFFC55C30 - 0xFFC55C34 */

	U1	u1Dummy4[0xFFC55C70U - 0xFFC55C34U];			/* 0xFFC55C34 - 0xFFC55C70 */

	union												/* DE_00SEADR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b2Dummy1				:2;
			U4	b10SEADR0				:10;			/* SEADR0[11:2] */
			U4	b15Dummy2				:15;
			U4	b5SEDL					:5;				/* SEDL[4:0] */
		} stBit;
	} unDE_00SEADR;										/* 0xFFC55C70 - 0xFFC55C74 */

	U1	u1Dummy5[0xFFC55CF0U - 0xFFC55C74U];			/* 0xFFC55C74 - 0xFFC55CF0 */

	union												/* DE_00DEADR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b2Dummy1				:2;
			U4	b10DEADR0				:10;			/* DEADR0[11:2] */
			U4	b15Dummy2				:15;
			U4	b5DEDL					:5;				/* DEDL[4:0] */
		} stBit;
	} unDE_00DEADR;										/* 0xFFC55CF0 - 0xFFC55CF4 */

}	Reg_Ecc_MeccCap_Dmde1Type;


/* MECCCAP_DMDA1 */
/* ============================================================================ */
/* ============================ Module: MECCCAP_DMDA1 ========================= */
/* ============================================================================ */
typedef	struct											/* MECCCAP_DMDA1 */
{
	union												/* DA_ERRINT */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDIE					:1;				/* SEDIE */
			U4	xDEDIE					:1;				/* DEDIE */
			U4	b5Dummy1				:5;
			U4	xSEOVFIE				:1;				/* SEOVFIE */
			U4	b24Dummy2				:24;
		} stBit;
	} unDA_ERRINT;										/* 0xFFC55E00 - 0xFFC55E04 */

	U1	u1Dummy1[0xFFC55E10U - 0xFFC55E04U];			/* 0xFFC55E04 - 0xFFC55E10 */

	union												/* DA_SSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSSTCLR00				:1;				/* SSTCLR00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unDA_SSTCLR;										/* 0xFFC55E10 - 0xFFC55E14 */

	union												/* DA_DSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDSTCLR00				:1;				/* DSTCLR00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unDA_DSTCLR;										/* 0xFFC55E14 - 0xFFC55E18 */

	union												/* DA_OVFCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSERROVFCLR0			:1;				/* SERROVFCLR0 */
			U4	b31Dummy1				:31;
		} stBit;
	} unDA_OVFCLR;										/* 0xFFC55E18 - 0xFFC55E1C */

	U1	u1Dummy2[0xFFC55E20U - 0xFFC55E1CU];			/* 0xFFC55E1C - 0xFFC55E20 */

	union												/* DA_SERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDF00					:1;				/* SEDF00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unDA_SERSTR;										/* 0xFFC55E20 - 0xFFC55E24 */

	union												/* DA_DERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDummy1					:1;
			U4	xDEDF00					:1;				/* DEDF00 */
			U4	b30Dummy2				:30;
		} stBit;
	} unDA_DERSTR;										/* 0xFFC55E24 - 0xFFC55E28 */

	union												/* DA_OVFSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSERROVF0				:1;				/* SERROVF0 */
			U4	b31Dummy1				:31;
		} stBit;
	} unDA_OVFSTR;										/* 0xFFC55E28 - 0xFFC55E2C */

	U1	u1Dummy3[0xFFC55E30U - 0xFFC55E2CU];			/* 0xFFC55E2C - 0xFFC55E30 */

	union												/* DA_SERINF */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDLINF00				:1;				/* SEDLINF00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unDA_SERINF;										/* 0xFFC55E30 - 0xFFC55E34 */

	U1	u1Dummy4[0xFFC55E70U - 0xFFC55E34U];			/* 0xFFC55E34 - 0xFFC55E70 */

	union												/* DA_00SEADR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b3Dummy1				:3;
			U4	b8SEADR0				:8;				/* SEADR0[10:3] */
			U4	b16Dummy2				:16;
			U4	b5SEDL					:5;				/* SEDL[4:0] */
		} stBit;
	} unDA_00SEADR;										/* 0xFFC55E70 - 0xFFC55E74 */

	U1	u1Dummy5[0xFFC55EF0U - 0xFFC55E74U];			/* 0xFFC55E74 - 0xFFC55EF0 */

	union												/* DA_00DEADR */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b3Dummy1				:3;
			U4	b8DEADR0				:8;				/* DEADR0[10:3] */
			U4	b16Dummy2				:16;
			U4	b5DEDL					:5;				/* DEDL[4:0] */
		} stBit;
	} unDA_00DEADR;										/* 0xFFC55EF0 - 0xFFC55EF4 */

}	Reg_Ecc_MeccCap_Dmda1Type;


/* ECC9 */
/* ============================================================================ */
/* ============================ Module: ECC9 ================================== */
/* ============================================================================ */
typedef	struct											/* ECC9 */
{
	union												/* REC1CTL */
	{
		U1	u1Data[2];									/* 8-bit  Access */
		U2	u2Data;										/* 16-bit Access */
		struct											/* Bit Access */
		{
			U2	xECEMF					:1;				/* ECEMF */
			U2	xECER1F					:1;				/* ECER1F */
			U2	xECER2F					:1;				/* ECER2F */
			U2	xEC1EDIC				:1;				/* EC1EDIC */
			U2	xEC2EDIC				:1;				/* EC2EDIC */
			U2	xEC1ECP					:1;				/* EC1ECP */
			U2	xDummy1					:1;
			U2	xECTHM					:1;				/* ECTHM */
			U2	xDummy2					:1;
			U2	xECER1C					:1;				/* ECER1C */
			U2	xECER2C					:1;				/* ECER2C */
			U2	xECOVFF					:1;				/* ECOVFF */
			U2	b2Dummy3				:2;
			U2	b2EMCA					:2;				/* EMCA[1:0] */
		} stBit;
	} unREC1CTL;										/* OFFSET 0x00 - 0x02 */

	U1	u1Dummy1[0x04U - 0x02U];						/* OFFSET 0x02 - 0x04 */

	union												/* REC1TMC */
	{
		U1	u1Data[2];									/* 8-bit  Access */
		U2	u2Data;										/* 16-bit Access */
		struct											/* Bit Access */
		{
			U2	xECREIS					:1;				/* ECREIS */
			U2	xECDCS					:1;				/* ECDCS */
			U2	xECENS					:1;				/* ECENS */
			U2	xECREOS					:1;				/* ECREOS */
			U2	xECTRRS					:1;				/* ECTRRS */
			U2	b2Dummy1				:2;
			U2	xECTMCE					:1;				/* ECTMCE */
			U2	b6Dummy2				:6;
			U2	b2ETMA					:2;				/* ETMA[1:0] */
		} stBit;
	} unREC1TMC;										/* OFFSET 0x04 - 0x06 */

	U1	u1Dummy2[0x08U - 0x06U];						/* OFFSET 0x06 - 0x08 */

	union												/* REC1TRC0 */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	b9ECHORD				:9;				/* ECHORD */
			U4	b7Dummy1				:7;
			U4	b9ECSYND				:9;				/* ECSYND */
			U4	b7Dummy2				:7;
		} stBit;
	} unREC1TRC0;										/* OFFSET 0x08 - 0x0C */

	union												/* REC1TRC1 */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	b9ECERDB				:9;				/* ECERDB */
			U4	b7Dummy1				:7;
			U4	b9ECECRD				:9;				/* ECECRD */
			U4	b7Dummy2				:7;
		} stBit;
	} unREC1TRC1;										/* OFFSET 0x0C - 0x10 */

	U4	u4REC1TED0;										/* OFFSET 0x10 - 0x14 */

	U4	u4REC1TED1;										/* OFFSET 0x14 - 0x18 */

	U4	u4REC1TED2;										/* OFFSET 0x18 - 0x1C */

	U4	u4REC1TED3;										/* OFFSET 0x1C - 0x20 */

	U4	u4REC1EAD;										/* OFFSET 0x20 - 0x24 */

}	Reg_Ecc_Ecc9Type;


/* ECC8 */
/* ============================================================================ */
/* ============================ Module: ECC8 ================================== */
/* ============================================================================ */
typedef	struct											/* ECC8 */
{
	union												/* REC1CTL */
	{
		U1	u1Data[2];									/* 8-bit  Access */
		U2	u2Data;										/* 16-bit Access */
		struct											/* Bit Access */
		{
			U2	xECEMF					:1;				/* ECEMF */
			U2	xECER1F					:1;				/* ECER1F */
			U2	xECER2F					:1;				/* ECER2F */
			U2	xEC1EDIC				:1;				/* EC1EDIC */
			U2	xEC2EDIC				:1;				/* EC2EDIC */
			U2	xEC1ECP					:1;				/* EC1ECP */
			U2	xDummy1					:1;
			U2	xECTHM					:1;				/* ECTHM */
			U2	xDummy2					:1;
			U2	xECER1C					:1;				/* ECER1C */
			U2	xECER2C					:1;				/* ECER2C */
			U2	xECOVFF					:1;				/* ECOVFF */
			U2	b2Dummy3				:2;
			U2	b2EMCA					:2;				/* EMCA[1:0] */
		} stBit;
	} unREC1CTL;										/* OFFSET 0x00 - 0x02 */

	U1	u1Dummy1[0x04U - 0x02U];						/* OFFSET 0x02 - 0x04 */

	union												/* REC1TMC */
	{
		U1	u1Data[2];									/* 8-bit  Access */
		U2	u2Data;										/* 16-bit Access */
		struct											/* Bit Access */
		{
			U2	xECREIS					:1;				/* ECREIS */
			U2	xECDCS					:1;				/* ECDCS */
			U2	xECENS					:1;				/* ECENS */
			U2	xECREOS					:1;				/* ECREOS */
			U2	xECTRRS					:1;				/* ECTRRS */
			U2	b2Dummy1				:2;
			U2	xECTMCE					:1;				/* ECTMCE */
			U2	b6Dummy2				:6;
			U2	b2ETMA					:2;				/* ETMA[1:0] */
		} stBit;
	} unREC1TMC;										/* OFFSET 0x04 - 0x06 */

	U1	u1Dummy2[0x08U - 0x06U];						/* OFFSET 0x06 - 0x08 */

	union												/* REC1TRC0 */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	b8ECHORD				:8;				/* ECHORD */
			U4	b8Dummy1				:8;
			U4	b8ECSYND				:8;				/* ECSYND */
			U4	b8Dummy2				:8;
		} stBit;
	} unREC1TRC0;										/* OFFSET 0x08 - 0x0C */

	union												/* REC1TRC1 */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	b8ECERDB				:8;				/* ECERDB */
			U4	b8Dummy1				:8;
			U4	b8ECECRD				:8;				/* ECECRD */
			U4	b8Dummy2				:8;
		} stBit;
	} unREC1TRC1;										/* OFFSET 0x0C - 0x10 */

	U4	u4REC1TED0;										/* OFFSET 0x10 - 0x14 */

	U4	u4REC1TED1;										/* OFFSET 0x14 - 0x18 */

	U1	u1Dummy3[0x20U - 0x18U];						/* OFFSET 0x18 - 0x20 */

	U4	u4REC1EAD;										/* OFFSET 0x20 - 0x24 */

}	Reg_Ecc_Ecc8Type;


/* ECC7 */
/* ============================================================================ */
/* ============================ Module: ECC7 ================================== */
/* ============================================================================ */
typedef	struct											/* ECC7 */
{
	union												/* E710CTL */
	{
		U1	u1Data[2];									/* 8-bit  Access */
		U2	u2Data;										/* 16-bit Access */
		struct											/* Bit Access */
		{
			U2	xECEMF					:1;				/* ECEMF */
			U2	xECER1F					:1;				/* ECER1F */
			U2	xECER2F					:1;				/* ECER2F */
			U2	xEC1EDIC				:1;				/* EC1EDIC */
			U2	xEC2EDIC				:1;				/* EC2EDIC */
			U2	xEC1ECP					:1;				/* EC1ECP */
			U2	xDummy1					:1;
			U2	xECTHM					:1;				/* ECTHM */
			U2	xDummy2					:1;
			U2	xECER1C					:1;				/* ECER1C */
			U2	xECER2C					:1;				/* ECER2C */
			U2	xECOVFF					:1;				/* ECOVFF */
			U2	b2Dummy3				:2;
			U2	b2EMCA					:2;				/* EMCA[1:0] */
		} stBit;
	} unE710CTL;										/* OFFSET 0x00 - 0x02 */

	U1	u1Dummy1[0x04U - 0x02U];						/* OFFSET 0x02 - 0x04 */

	union												/* E710TMC */
	{
		U1	u1Data[2];									/* 8-bit  Access */
		U2	u2Data;										/* 16-bit Access */
		struct											/* Bit Access */
		{
			U2	xECREIS					:1;				/* ECREIS */
			U2	xECDCS					:1;				/* ECDCS */
			U2	xECENS					:1;				/* ECENS */
			U2	xECREOS					:1;				/* ECREOS */
			U2	xECTRRS					:1;				/* ECTRRS */
			U2	b2Dummy1				:2;
			U2	xECTMCE					:1;				/* ECTMCE */
			U2	b6Dummy2				:6;
			U2	b2ETMA					:2;				/* ETMA[1:0] */
		} stBit;
	} unE710TMC;										/* OFFSET 0x04 - 0x06 */

	U1	u1Dummy2[0x08U - 0x06U];						/* OFFSET 0x06 - 0x08 */

	union												/* E710TRC */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	b8ECERDB				:8;				/* ECERDB */
			U4	b8ECECRD				:8;				/* ECECRD */
			U4	b8ECHORD				:8;				/* ECHORD */
			U4	b8ECSYND				:8;				/* ECSYND */
		} stBit;
	} unE710TRC;										/* OFFSET 0x08 - 0x0C */

	U4	u4E710TED;										/* OFFSET 0x0C - 0x10 */

	U4	u4E710EAD;										/* OFFSET 0x10 - 0x14 */

}	Reg_Ecc_Ecc7Type;


/* ECC6 */
/* ============================================================================ */
/* ============================ Module: ECC6 ================================== */
/* ============================================================================ */
typedef	struct											/* ECC6 */
{
	union												/* E610CTL */
	{
		U1	u1Data[2];									/* 8-bit  Access */
		U2	u2Data;										/* 16-bit Access */
		struct											/* Bit Access */
		{
			U2	xECEMF					:1;				/* ECEMF */
			U2	xECER1F					:1;				/* ECER1F */
			U2	xECER2F					:1;				/* ECER2F */
			U2	xEC1EDIC				:1;				/* EC1EDIC */
			U2	xEC2EDIC				:1;				/* EC2EDIC */
			U2	xEC1ECP					:1;				/* EC1ECP */
			U2	xDummy1					:1;
			U2	xECTHM					:1;				/* ECTHM */
			U2	xDummy2					:1;
			U2	xECER1C					:1;				/* ECER1C */
			U2	xECER2C					:1;				/* ECER2C */
			U2	xECOVFF					:1;				/* ECOVFF */
			U2	b2Dummy3				:2;
			U2	b2EMCA					:2;				/* EMCA[1:0] */
		} stBit;
	} unE610CTL;										/* OFFSET 0x00 - 0x02 */

	U1	u1Dummy1[0x04U - 0x02U];						/* OFFSET 0x02 - 0x04 */

	union												/* E610TMC */
	{
		U1	u1Data[2];									/* 8-bit  Access */
		U2	u2Data;										/* 16-bit Access */
		struct											/* Bit Access */
		{
			U2	xECREIS					:1;				/* ECREIS */
			U2	xECDCS					:1;				/* ECDCS */
			U2	xECENS					:1;				/* ECENS */
			U2	xECREOS					:1;				/* ECREOS */
			U2	xECTRRS					:1;				/* ECTRRS */
			U2	b2Dummy1				:2;
			U2	xECTMCE					:1;				/* ECTMCE */
			U2	b6Dummy2				:6;
			U2	b2ETMA					:2;				/* ETMA[1:0] */
		} stBit;
	} unE610TMC;										/* OFFSET 0x04 - 0x06 */

	U1	u1Dummy2[0x08U - 0x06U];						/* OFFSET 0x06 - 0x08 */

	union												/* E610TRC */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	b8ECRODM				:8;				/* ECRODM */
			U4	b8ECECRD				:8;				/* ECECRD */
			U4	b8ECHORD				:8;				/* ECHORD */
			U4	b8ECSYND				:8;				/* ECSYND */
		} stBit;
	} unE610TRC;										/* OFFSET 0x08 - 0x0C */

	union												/* E610TED */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	b8ECERDB				:8;				/* ECERDB */
			U4	b8ECRIDM				:8;				/* ECRIDM */
			U4	b16ECEDB				:16;			/* ECEDB */
		} stBit;
	} unE610TED;										/* OFFSET 0x0C - 0x10 */

	U4	u4E610EAD;										/* OFFSET 0x10 - 0x14 */

}	Reg_Ecc_Ecc6Type;


/* ECCCNT_A */
/* ============================================================================ */
/* ============================ Module: ECCCNT_A ============================== */
/* ============================================================================ */
typedef	struct											/* ECCCNT_A */
{
	union												/* BUSAECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	b31Dummy1				:31;
		} stBit;
	} unBUSAECCCTL;										/* OFFSET 0x00 - 0x04 */

	U1	u1Dummy1[0x10U - 0x04U];						/* OFFSET 0x04 - 0x10 */

	union												/* BUSAECCTSTCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	xDummy1					:1;
			U4	xECCTST					:1;				/* ECCTST */
			U4	b30Dummy2				:30;
		} stBit;
	} unBUSAECCTSTCTL;									/* OFFSET 0x10 - 0x14 */

	U1	u1Dummy2[0x30U - 0x14U];						/* OFFSET 0x14 - 0x30 */

	union												/* BUSAECCTSTDIN0 */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
	} unBUSAECCTSTDIN0;									/* OFFSET 0x30 - 0x34 */

	U1	u1Dummy3[0x40U - 0x34U];						/* OFFSET 0x34 - 0x40 */

	union												/* BUSAECCTSTEIN */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	b7ECC					:7;				/* ECC[6:0] */
			U4	b25Dummy1				:25;
		} stBit;
	} unBUSAECCTSTEIN;									/* OFFSET 0x40 - 0x44 */

}	Reg_Ecc_EccCnt_AType;


/* ECCCNT_D_V2XWCL0 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_D_V2XWCL0 ====================== */
/* ============================================================================ */
typedef	struct											/* ECCCNT_D_V2XWCL0 */
{
	union												/* BUSDVCECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	b30Dummy1				:30;
		} stBit;
	} unBUSDVCECCCTL;									/* 0xFFC4E000 - 0xFFC4E004 */

	U1	u1Dummy1[0xFFC4E010U - 0xFFC4E004U];			/* 0xFFC4E004 - 0xFFC4E010 */

	union												/* BUSDVCECCTSTCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	xDATSEL					:1;				/* DATSEL */
			U4	xECCTST					:1;				/* ECCTST */
			U4	b30Dummy1				:30;
		} stBit;
	} unBUSDVCECCTSTCTL;								/* 0xFFC4E010 - 0xFFC4E014 */

	U1	u1Dummy2[0xFFC4E030U - 0xFFC4E014U];			/* 0xFFC4E014 - 0xFFC4E030 */

	union												/* BUSDVCECCTSTDIN0 */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
	} unBUSDVCECCTSTDIN0;								/* 0xFFC4E030 - 0xFFC4E034 */

	U1	u1Dummy3[0xFFC4E040U - 0xFFC4E034U];			/* 0xFFC4E034 - 0xFFC4E040 */

	union												/* BUSDVCECCTSTEIN */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	b7ECC					:7;				/* ECC[6:0] */
			U4	b25Dummy1				:25;
		} stBit;
	} unBUSDVCECCTSTEIN;								/* 0xFFC4E040 - 0xFFC4E044 */

}	Reg_Ecc_EccCnt_D_V2XwCl0Type;


/* ECCCNT_D_V2XRCL0 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_D_V2XRCL0 ====================== */
/* ============================================================================ */
typedef	struct											/* ECCCNT_D_V2XRCL0 */
{
	union												/* BUSDVCECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	b30Dummy1				:30;
		} stBit;
	} unBUSDVCECCCTL;									/* 0xFFC4E080 - 0xFFC4E084 */

	U1	u1Dummy1[0xFFC4E090U - 0xFFC4E084U];			/* 0xFFC4E084 - 0xFFC4E090 */

	union												/* BUSDVCECCTSTCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	xDATSEL					:1;				/* DATSEL */
			U4	xECCTST					:1;				/* ECCTST */
			U4	b30Dummy1				:30;
		} stBit;
	} unBUSDVCECCTSTCTL;								/* 0xFFC4E090 - 0xFFC4E094 */

	U1	u1Dummy2[0xFFC4E0B0U - 0xFFC4E094U];			/* 0xFFC4E094 - 0xFFC4E0B0 */

	union												/* BUSDVCECCTSTCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
	} unBUSDVCECCTSTDIN0;								/* 0xFFC4E0B0 - 0xFFC4E0B4 */

	U1	u1Dummy3[0xFFC4E0C0U - 0xFFC4E0B4U];			/* 0xFFC4E0B4 - 0xFFC4E0C0 */

	union												/* BUSDVCECCTSTEIN */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	b7ECC					:7;				/* ECC[6:0] */
			U4	xDummy1					:1;
		} stBit;
	} unBUSDVCECCTSTEIN;								/* 0xFFC4E0C0 - 0xFFC4E0C4 */

}	Reg_Ecc_EccCnt_D_V2XrCl0Type;


/* ECCCNT_D_V2XWCL1 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_D_V2XWCL1 ====================== */
/* ============================================================================ */
typedef	struct											/* ECCCNT_D_V2XWCL1 */
{
	union												/* BUSDVCECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	b30Dummy1				:30;
		} stBit;
	} unBUSDVCECCCTL;									/* 0xFFC4E100 - 0xFFC4E104 */

	U1	u1Dummy1[0xFFC4E110U - 0xFFC4E104U];			/* 0xFFC4E104 - 0xFFC4E110 */

	union												/* BUSDVCECCTSTCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	xDATSEL					:1;				/* DATSEL */
			U4	xECCTST					:1;				/* ECCTST */
			U4	b30Dummy1				:30;
		} stBit;
	} unBUSDVCECCTSTCTL;								/* 0xFFC4E110 - 0xFFC4E114 */

	U1	u1Dummy2[0xFFC4E130U - 0xFFC4E114U];			/* 0xFFC4E114 - 0xFFC4E130 */

	union												/* BUSDVCECCTSTDIN0 */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
	} unBUSDVCECCTSTDIN0;								/* 0xFFC4E130 - 0xFFC4E134 */

	U1	u1Dummy3[0xFFC4E140U - 0xFFC4E134U];			/* 0xFFC4E134 - 0xFFC4E140 */

	union												/* BUSDVCECCTSTEIN */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	b7ECC					:7;				/* ECC[6:0] */
			U4	b25Dummy1				:25;
		} stBit;
	} unBUSDVCECCTSTEIN;								/* 0xFFC4E140 - 0xFFC4E144 */

}	Reg_Ecc_EccCnt_D_V2XwCl1Type;


/* ECCCNT_D_V2XRCL1 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_D_V2XRCL1 ====================== */
/* ============================================================================ */
typedef	struct											/* ECCCNT_D_V2XRCL1 */
{
	union												/* BUSDVCECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	b30Dummy1				:30;
		} stBit;
	} unBUSDVCECCCTL;									/* 0xFFC4E180 - 0xFFC4E184 */

	U1	u1Dummy1[0xFFC4E190U - 0xFFC4E184U];			/* 0xFFC4E184 - 0xFFC4E190 */

	union												/* BUSDVCECCTSTCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	xDATSEL					:1;				/* DATSEL */
			U4	xECCTST					:1;				/* ECCTST */
			U4	b30Dummy1				:30;
		} stBit;
	} unBUSDVCECCTSTCTL;								/* 0xFFC4E190 - 0xFFC4E194 */

	U1	u1Dummy2[0xFFC4E1B0U - 0xFFC4E194U];			/* 0xFFC4E194 - 0xFFC4E1B0 */

	union												/* BUSDVCECCTSTCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
	} unBUSDVCECCTSTDIN0;								/* 0xFFC4E1B0 - 0xFFC4E1B4 */

	U1	u1Dummy3[0xFFC4E1C0U - 0xFFC4E1B4U];			/* 0xFFC4E1B4 - 0xFFC4E1C0 */

	union												/* BUSDVCECCTSTEIN */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	b7ECC					:7;				/* ECC[6:0] */
			U4	xDummy1					:1;
		} stBit;
	} unBUSDVCECCTSTEIN;								/* 0xFFC4E1C0 - 0xFFC4E1C4 */

}	Reg_Ecc_EccCnt_D_V2XrCl1Type;


/* ECCCNT_D_V2XWCL2 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_D_V2XWCL2 ====================== */
/* ============================================================================ */
typedef	struct											/* ECCCNT_D_V2XWCL2 */
{
	union												/* BUSDVCECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	b30Dummy1				:30;
		} stBit;
	} unBUSDVCECCCTL;									/* 0xFFC4E200 - 0xFFC4E204 */

	U1	u1Dummy1[0xFFC4E210U - 0xFFC4E204U];			/* 0xFFC4E204 - 0xFFC4E210 */

	union												/* BUSDVCECCTSTCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	xDATSEL					:1;				/* DATSEL */
			U4	xECCTST					:1;				/* ECCTST */
			U4	b30Dummy1				:30;
		} stBit;
	} unBUSDVCECCTSTCTL;								/* 0xFFC4E210 - 0xFFC4E214 */

	U1	u1Dummy2[0xFFC4E230U - 0xFFC4E214U];			/* 0xFFC4E214 - 0xFFC4E230 */

	union												/* BUSDVCECCTSTDIN0 */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
	} unBUSDVCECCTSTDIN0;								/* 0xFFC4E230 - 0xFFC4E234 */

	U1	u1Dummy3[0xFFC4E240U - 0xFFC4E234U];			/* 0xFFC4E234 - 0xFFC4E240 */

	union												/* BUSDVCECCTSTEIN */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	b7ECC					:7;				/* ECC[6:0] */
			U4	b25Dummy1				:25;
		} stBit;
	} unBUSDVCECCTSTEIN;								/* 0xFFC4E240 - 0xFFC4E244 */

}	Reg_Ecc_EccCnt_D_V2XwCl2Type;


/* ECCCNT_D_V2XRCL2 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_D_V2XRCL2 ====================== */
/* ============================================================================ */
typedef	struct											/* ECCCNT_D_V2XRCL2 */
{
	union												/* BUSDVCECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	b30Dummy1				:30;
		} stBit;
	} unBUSDVCECCCTL;									/* 0xFFC4E280 - 0xFFC4E284 */

	U1	u1Dummy1[0xFFC4E290U - 0xFFC4E284U];			/* 0xFFC4E284 - 0xFFC4E290 */

	union												/* BUSDVCECCTSTCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	xDATSEL					:1;				/* DATSEL */
			U4	xECCTST					:1;				/* ECCTST */
			U4	b30Dummy1				:30;
		} stBit;
	} unBUSDVCECCTSTCTL;								/* 0xFFC4E290 - 0xFFC4E294 */

	U1	u1Dummy2[0xFFC4E2B0U - 0xFFC4E294U];			/* 0xFFC4E294 - 0xFFC4E2B0 */

	union												/* BUSDVCECCTSTCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
	} unBUSDVCECCTSTDIN0;								/* 0xFFC4E2B0 - 0xFFC4E2B4 */

	U1	u1Dummy3[0xFFC4E2C0U - 0xFFC4E2B4U];			/* 0xFFC4E2B4 - 0xFFC4E2C0 */

	union												/* BUSDVCECCTSTEIN */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	b7ECC					:7;				/* ECC[6:0] */
			U4	xDummy1					:1;
		} stBit;
	} unBUSDVCECCTSTEIN;								/* 0xFFC4E2C0 - 0xFFC4E2C4 */

}	Reg_Ecc_EccCnt_D_V2XrCl2Type;


/* ECCCNT_D_PV2APBW */
/* ============================================================================ */
/* ============================ Module: ECCCNT_D_PV2APBW ====================== */
/* ============================================================================ */
typedef	struct											/* ECCCNT_D_PV2APBW */
{
	union												/* BUSDECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	b30Dummy1				:30;
		} stBit;
	} unBUSDECCCTL;									/* 0xFFC4E400 - 0xFFC4E404 */

}	Reg_Ecc_EccCnt_D_Pv2ApbwType;


/* ECCCNT_D_CRAM */
/* ============================================================================ */
/* ============================ Module: ECCCNT_D_CRAM ========================= */
/* ============================================================================ */
typedef	struct											/* ECCCNT_D_CRAM */
{
	union												/* BUSDVCECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	b30Dummy1				:30;
		} stBit;
	} unBUSDVCECCCTL;									/* 0xFFC4E500 - 0xFFC4E504 */

	U1	u1Dummy1[0xFFC4E510U - 0xFFC4E504U];			/* 0xFFC4E504 - 0xFFC4E510 */

	union												/* BUSDVCECCTSTCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	xDATSEL					:1;				/* DATSEL */
			U4	xECCTST					:1;				/* ECCTST */
			U4	b30Dummy1				:30;
		} stBit;
	} unBUSDVCECCTSTCTL;								/* 0xFFC4E510 - 0xFFC4E514 */

	U1	u1Dummy2[0xFFC4E530U - 0xFFC4E514U];			/* 0xFFC4E514 - 0xFFC4E530 */

	union												/* BUSDVCECCTSTDIN0 */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
	} unBUSDVCECCTSTDIN0;								/* 0xFFC4E530 - 0xFFC4E534 */

	U1	u1Dummy3[0xFFC4E540U - 0xFFC4E534U];			/* 0xFFC4E534 - 0xFFC4E540 */

	union												/* BUSDVCECCTSTEIN */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	b7ECC					:7;				/* ECC[6:0] */
			U4	b25Dummy1				:25;
		} stBit;
	} unBUSDVCECCTSTEIN;								/* 0xFFC4E540 - 0xFFC4E544 */

}	Reg_Ecc_EccCnt_D_CramType;


/* ECCCNT_D_EMU */
/* ============================================================================ */
/* ============================ Module: ECCCNT_D_EMU ========================== */
/* ============================================================================ */
typedef	struct											/* ECCCNT_D_EMU */
{
	union												/* BUSDEMECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	b30Dummy1				:30;
		} stBit;
	} unBUSDEMECCCTL;									/* 0xFFC4E580 - 0xFFC4E584 */

	U1	u1Dummy1[0xFFC4E590U - 0xFFC4E584U];			/* 0xFFC4E584 - 0xFFC4E590 */

	union												/* BUSDEMECCTSTCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	xDATSEL					:1;				/* DATSEL */
			U4	xECCTST					:1;				/* ECCTST */
			U4	b30Dummy1				:30;
		} stBit;
	} unBUSDEMECCTSTCTL;								/* 0xFFC4E590 - 0xFFC4E594 */

	U1	u1Dummy2[0xFFC4E5B0U - 0xFFC4E594U];			/* 0xFFC4E594 - 0xFFC4E5B0 */

	union												/* unBUSDEMECCTSTDIN0 */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
	} unBUSDEMECCTSTDIN0;								/* 0xFFC4E5B0 - 0xFFC4E5B4 */

	U1	u1Dummy3[0xFFC4E5C0U - 0xFFC4E5B4U];			/* 0xFFC4E5B4 - 0xFFC4E5C0 */

	union												/* BUSDEMECCTSTEIN */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	b7ECC					:7;				/* ECC[6:0] */
			U4	b25Dummy1				:25;
		} stBit;
	} unBUSDEMECCTSTEIN;								/* 0xFFC4E5C0 - 0xFFC4E5C4 */

}	Reg_Ecc_EccCnt_D_EmuType;


/* ECCCNT_D_DMDE0 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_D_DMDE0 ======================== */
/* ============================================================================ */
typedef	struct											/* ECCCNT_D_DMDE0 */
{
	union												/* BUSDDEECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	b30Dummy1				:30;
		} stBit;
	} unBUSDDEECCCTL;									/* 0xFFC4E600 - 0xFFC4E604 */

	U1	u1Dummy1[0xFFC4E610U - 0xFFC4E604U];			/* 0xFFC4E604 - 0xFFC4E610 */

	union												/* BUSDDEECCTSTCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	xDummy1					:1;
			U4	xECCTST					:1;				/* ECCTST */
			U4	b30Dummy2				:30;
		} stBit;
	} unBUSDDEECCTSTCTL;								/* 0xFFC4E610 - 0xFFC4E614 */

	U1	u1Dummy2[0xFFC4E630U - 0xFFC4E614U];			/* 0xFFC4E614 - 0xFFC4E630 */

	union												/* BUSDDEECCTSTDIN0 */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
	} unBUSDDEECCTSTDIN0;								/* 0xFFC4E630 - 0xFFC4E634 */

	union												/* BUSDDEECCTSTDIN1 */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
	} unBUSDDEECCTSTDIN1;								/* 0xFFC4E634 - 0xFFC4E638 */

	U1	u1Dummy3[0xFFC4E640U - 0xFFC4E638U];			/* 0xFFC4E638 - 0xFFC4E640 */

	union												/* BUSDDEECCTSTEIN */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */\
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	b8ECC					:8;				/* ECC[7:0] */
			U4	b24Dummy1				:24;
		} stBit;
	} unBUSDDEECCTSTEIN;								/* 0xFFC4E640 - 0xFFC4E644 */

}	Reg_Ecc_EccCnt_D_Dmde0Type;


/* ECCCNT_D_DMDE1 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_D_DMDE1 ======================== */
/* ============================================================================ */
typedef	struct											/* ECCCNT_D_DMDE1 */
{
	union												/* BUSDDEECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	b30Dummy1				:30;
		} stBit;
	} unBUSDDEECCCTL;									/* 0xFFC4E680 - 0xFFC4E684 */

	U1	u1Dummy1[0xFFC4E690U - 0xFFC4E684U];			/* 0xFFC4E684 - 0xFFC4E690 */

	union												/* BUSDDEECCTSTCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	xDummy1					:1;
			U4	xECCTST					:1;				/* ECCTST */
			U4	b30Dummy2				:30;
		} stBit;
	} unBUSDDEECCTSTCTL;								/* 0xFFC4E690 - 0xFFC4E694 */

	U1	u1Dummy2[0xFFC4E6B0U - 0xFFC4E694U];			/* 0xFFC4E694 - 0xFFC4E6B0 */

	union												/* BUSDDEECCTSTDIN0 */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
	} unBUSDDEECCTSTDIN0;								/* 0xFFC4E6B0 - 0xFFC4E6B4 */

	union												/* BUSDDEECCTSTDIN1 */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
	} unBUSDDEECCTSTDIN1;								/* 0xFFC4E6B4 - 0xFFC4E6B8 */

	U1	u1Dummy3[0xFFC4E6C0U - 0xFFC4E6B8U];			/* 0xFFC4E6B8 - 0xFFC4E6C0 */

	union												/* BUSDDEECCTSTEIN */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	b8ECC					:8;				/* ECC[7:0] */
			U4	b24Dummy				:24;
		} stBit;
	} unBUSDDEECCTSTEIN;								/* 0xFFC4E6C0 - 0xFFC4E6C4 */

}	Reg_Ecc_EccCnt_D_Dmde1Type;


/* ECCCNT_C_DMR0 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_C_DMR0 ========================= */
/* ============================================================================ */
typedef	struct											/* ECCCNT_C_DMR0 */
{
	union												/* BUSCECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	b31Dummy1				:31;
		} stBit;
	} unBUSCECCCTL;										/* 0xFFC4E800 - 0xFFC4E804 */

	U1	u1Dummy1[0xFFC4E810U - 0xFFC4E804U];			/* 0xFFC4E804 - 0xFFC4E810 */

	union												/* BUSCECCTSTCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	xDummy1					:1;
			U4	xECCTST					:1;				/* ECCTST */
			U4	b30Dummy2				:30;
		} stBit;
	} unBUSCECCTSTCTL;									/* 0xFFC4E810 - 0xFFC4E814 */

	U1	u1Dummy2[0xFFC4E830U - 0xFFC4E814U];			/* 0xFFC4E814 - 0xFFC4E830 */

	union												/* BUSCECCTSTDIN0 */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
	} unBUSCECCTSTDIN0;									/* 0xFFC4E830 - 0xFFC4E834 */

	union												/* BUSCECCTSTDIN1 */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
	} unBUSCECCTSTDIN1;									/* 0xFFC4E834 - 0xFFC4E838 */

	U1	u1Dummy3[0xFFC4E840U - 0xFFC4E838U];			/* 0xFFC4E838 - 0xFFC4E840 */

	union												/* BUSCECCTSTEIN */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */\
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	b8ECC					:8;				/* ECC[7:0] */
			U4	b24Dummy1				:24;
		} stBit;
	} unBUSCECCTSTEIN;									/* 0xFFC4E840 - 0xFFC4E844 */

}	Reg_Ecc_EccCnt_C_Dmr0Type;


/* ECCCNT_C_DMW0 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_C_DMW0 ========================= */
/* ============================================================================ */
typedef	struct											/* ECCCNT_C_DMW0 */
{
	union												/* BUSCECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	b31Dummy1				:31;
		} stBit;
	} unBUSCECCCTL;										/* 0xFFC4E880 - 0xFFC4E884 */

	U1	u1Dummy1[0xFFC4E890U - 0xFFC4E884U];			/* 0xFFC4E884 - 0xFFC4E890 */

	union												/* BUSCECCTSTCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	xDummy1					:1;
			U4	xECCTST					:1;				/* ECCTST */
			U4	b30Dummy2				:30;
		} stBit;
	} unBUSCECCTSTCTL;									/* 0xFFC4E890 - 0xFFC4E894 */

	U1	u1Dummy2[0xFFC4E8B0U - 0xFFC4E894U];			/* 0xFFC4E894 - 0xFFC4E8B0 */

	union												/* BUSCECCTSTDIN0 */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
	} unBUSCECCTSTDIN0;									/* 0xFFC4E8B0 - 0xFFC4E8B4 */

	union												/* BUSCECCTSTDIN1 */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
	} unBUSCECCTSTDIN1;									/* 0xFFC4E8B4 - 0xFFC4E8B8 */

	U1	u1Dummy3[0xFFC4E8C0U - 0xFFC4E8B8U];			/* 0xFFC4E8B8 - 0xFFC4E8C0 */

	union												/* BUSCECCTSTEIN */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	b8ECC					:8;				/* ECC[7:0] */
			U4	b24Dummy				:24;
		} stBit;
	} unBUSCECCTSTEIN;									/* 0xFFC4E8C0 - 0xFFC4E8C4 */

}	Reg_Ecc_EccCnt_C_Dmw0Type;


/* ECCCNT_C_DMR1 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_C_DMR1 ========================= */
/* ============================================================================ */
typedef	struct											/* ECCCNT_C_DMR1 */
{
	union												/* BUSCECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	b31Dummy1				:31;
		} stBit;
	} unBUSCECCCTL;										/* 0xFFC4E900 - 0xFFC4E904 */

	U1	u1Dummy1[0xFFC4E910U - 0xFFC4E904U];			/* 0xFFC4E904 - 0xFFC4E910 */

	union												/* BUSCECCTSTCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	xDummy1					:1;
			U4	xECCTST					:1;				/* ECCTST */
			U4	b30Dummy2				:30;
		} stBit;
	} unBUSCECCTSTCTL;									/* 0xFFC4E910 - 0xFFC4E914 */

	U1	u1Dummy2[0xFFC4E930U - 0xFFC4E914U];			/* 0xFFC4E914 - 0xFFC4E930 */

	union												/* BUSCECCTSTDIN0 */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
	} unBUSCECCTSTDIN0;									/* 0xFFC4E930 - 0xFFC4E934 */

	union												/* BUSCECCTSTDIN1 */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
	} unBUSCECCTSTDIN1;									/* 0xFFC4E934 - 0xFFC4E938 */

	U1	u1Dummy3[0xFFC4E940U - 0xFFC4E938U];			/* 0xFFC4E938 - 0xFFC4E940 */

	union												/* BUSCECCTSTEIN */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	b8ECC					:8;				/* ECC[7:0] */
			U4	b24Dummy1				:24;
		} stBit;
	} unBUSCECCTSTEIN;									/* 0xFFC4E940 - 0xFFC4E944 */

}	Reg_Ecc_EccCnt_C_Dmr1Type;


/* ECCCNT_C_DMW1 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_C_DMW1 ========================= */
/* ============================================================================ */
typedef	struct											/* ECCCNT_C_DMW1 */
{
	union												/* BUSCECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	b31Dummy1				:31;
		} stBit;
	} unBUSCECCCTL;										/* 0xFFC4E980 - 0xFFC4E984 */

	U1	u1Dummy1[0xFFC4E990U - 0xFFC4E984U];			/* 0xFFC4E984 - 0xFFC4E990 */

	union												/* BUSCECCTSTCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	xDummy1					:1;
			U4	xECCTST					:1;				/* ECCTST */
			U4	b30Dummy2				:30;
		} stBit;
	} unBUSCECCTSTCTL;									/* 0xFFC4E990 - 0xFFC4E994 */

	U1	u1Dummy2[0xFFC4E9B0U - 0xFFC4E994U];			/* 0xFFC4E994 - 0xFFC4E9B0 */

	union												/* BUSCECCTSTDIN0 */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
	} unBUSCECCTSTDIN0;									/* 0xFFC4E9B0 - 0xFFC4E9B4 */

	union												/* BUSCECCTSTDIN1 */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
	} unBUSCECCTSTDIN1;									/* 0xFFC4E9B4 - 0xFFC4E9B8 */

	U1	u1Dummy3[0xFFC4E9C0U - 0xFFC4E9B8U];			/* 0xFFC4E9B8 - 0xFFC4E9C0 */

	union												/* BUSCECCTSTEIN */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	b8ECC					:8;				/* ECC[7:0] */
			U4	b24Dummy				:24;
		} stBit;
	} unBUSCECCTSTEIN;								/* 0xFFC4E9C0 - 0xFFC4E9C4 */

}	Reg_Ecc_EccCnt_C_Dmw1Type;


/* ECCCNT_SD_PE0CL0 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_SD_PE0CL0 ====================== */
/* ============================================================================ */
typedef	struct											/* ECCCNT_SD_PE0CL0 */
{
	union												/* BUSDECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	b30Dummy1				:30;
		} stBit;
	} unBUSDECCCTL;										/* 0xFFC4F000 - 0xFFC4F004 */

}	Reg_Ecc_EccCnt_Sd_Pe0Cl0Type;


/* ECCCNT_SD_PE1CL0 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_SD_PE1CL0 ====================== */
/* ============================================================================ */
typedef	struct											/* ECCCNT_SD_PE1CL0 */
{
	union												/* BUSDECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	b30Dummy1				:30;
		} stBit;
	} unBUSDECCCTL;										/* 0xFFC4F100 - 0xFFC4F104 */

}	Reg_Ecc_EccCnt_Sd_Pe1Cl0Type;


/* ECCCNT_SD_PE2CL1 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_SD_PE2CL1 ====================== */
/* ============================================================================ */
typedef	struct											/* ECCCNT_SD_PE2CL1 */
{
	union												/* BUSDECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	b30Dummy1				:30;
		} stBit;
	} unBUSDECCCTL;										/* 0xFFC4F200 - 0xFFC4F204 */

}	Reg_Ecc_EccCnt_Sd_Pe2Cl1Type;


/* ECCCNT_SD_PE3CL1 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_SD_PE3CL1 ====================== */
/* ============================================================================ */
typedef	struct											/* ECCCNT_SD_PE3CL1 */
{
	union												/* BUSDECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	b30Dummy1				:30;
		} stBit;
	} unBUSDECCCTL;										/* 0xFFC4F300 - 0xFFC4F304 */

}	Reg_Ecc_EccCnt_Sd_Pe3Cl1Type;


/* ECCCNT_SD_PE4CL2 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_SD_PE4CL2 ====================== */
/* ============================================================================ */
typedef	struct											/* ECCCNT_SD_PE4CL2 */
{
	union												/* BUSDECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	b30Dummy1				:30;
		} stBit;
	} unBUSDECCCTL;										/* 0xFFC4F400 - 0xFFC4F404 */

}	Reg_Ecc_EccCnt_Sd_Pe4Cl2Type;


/* ECCCNT_SD_PE5CL2 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_SD_PE5CL2 ====================== */
/* ============================================================================ */
typedef	struct											/* ECCCNT_SD_PE5CL2 */
{
	union												/* BUSDECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	b30Dummy1				:30;
		} stBit;
	} unBUSDECCCTL;										/* 0xFFC4F500 - 0xFFC4F504 */

}	Reg_Ecc_EccCnt_Sd_Pe5Cl2Type;


/* ECCCNT_MD_PE0CL0 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_MD_PE0CL0 ====================== */
/* ============================================================================ */
typedef	struct											/* ECCCNT_MD_PE0CL0 */
{
	union												/* BUSDECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	b30Dummy1				:30;
		} stBit;
	} unBUSDECCCTL;										/* 0xFFC4F080 - 0xFFC4F084 */

}	Reg_Ecc_EccCnt_Md_Pe0Cl0Type;


/* ECCCNT_MD_PE1CL0 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_MD_PE1CL0 ====================== */
/* ============================================================================ */
typedef	struct											/* ECCCNT_MD_PE1CL0 */
{
	union												/* BUSDECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	b30Dummy1				:30;
		} stBit;
	} unBUSDECCCTL;										/* 0xFFC4F180 - 0xFFC4F184 */

}	Reg_Ecc_EccCnt_Md_Pe1Cl0Type;


/* ECCCNT_MD_PE2CL1 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_MD_PE2CL1 ====================== */
/* ============================================================================ */
typedef	struct											/* ECCCNT_MD_PE2CL1 */
{
	union												/* BUSDECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	b30Dummy1				:30;
		} stBit;
	} unBUSDECCCTL;										/* 0xFFC4F280 - 0xFFC4F284 */

}	Reg_Ecc_EccCnt_Md_Pe2Cl1Type;


/* ECCCNT_MD_PE3CL1 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_MD_PE3CL1 ====================== */
/* ============================================================================ */
typedef	struct											/* ECCCNT_MD_PE3CL1 */
{
	union												/* BUSDECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	b30Dummy1				:30;
		} stBit;
	} unBUSDECCCTL;										/* 0xFFC4F380 - 0xFFC4F384 */

}	Reg_Ecc_EccCnt_Md_Pe3Cl1Type;


/* ECCCNT_MD_PE4CL2 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_MD_PE4CL2 ====================== */
/* ============================================================================ */
typedef	struct											/* ECCCNT_MD_PE4CL2 */
{
	union												/* BUSDECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	b30Dummy1				:30;
		} stBit;
	} unBUSDECCCTL;										/* 0xFFC4F480 - 0xFFC4F484 */

}	Reg_Ecc_EccCnt_Md_Pe4Cl2Type;


/* ECCCNT_MD_PE5CL2 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_MD_PE5CL2 ====================== */
/* ============================================================================ */
typedef	struct											/* ECCCNT_MD_PE5CL2 */
{
	union												/* BUSDECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	b30Dummy1				:30;
		} stBit;
	} unBUSDECCCTL;										/* 0xFFC4F580 - 0xFFC4F584 */

}	Reg_Ecc_EccCnt_Md_Pe5Cl2Type;


/* ECCCNT_D_BARR */
/* ============================================================================ */
/* ============================ Module: ECCCNT_D_BARR ========================= */
/* ============================================================================ */
typedef	struct											/* ECCCNT_D_BARR */
{
	union												/* BUSDECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	b30Dummy1				:30;
		} stBit;
	} unBUSDECCCTL;										/* 0xFFC4F800 - 0xFFC4F804 */

}	Reg_Ecc_EccCnt_D_BarrType;


/* ECCCNT_D_IPIR */
/* ============================================================================ */
/* ============================ Module: ECCCNT_D_IPIR ========================= */
/* ============================================================================ */
typedef	struct											/* ECCCNT_D_IPIR */
{
	union												/* BUSDECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	b30Dummy1				:30;
		} stBit;
	} unBUSDECCCTL;										/* 0xFFC4F880 - 0xFFC4F884 */

}	Reg_Ecc_EccCnt_D_IpirType;


/* ECCCNT_D_TPTM */
/* ============================================================================ */
/* ============================ Module: ECCCNT_D_TPTM ========================= */
/* ============================================================================ */
typedef	struct											/* ECCCNT_D_TPTM */
{
	union												/* BUSDECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	b30Dummy1				:30;
		} stBit;
	} unBUSDECCCTL;										/* 0xFFC4F980 - 0xFFC4F984 */

}	Reg_Ecc_EccCnt_D_TptmType;


/* ECCCNT_D_DTS */
/* ============================================================================ */
/* ============================ Module: ECCCNT_D_DTS ========================== */
/* ============================================================================ */
typedef	struct											/* ECCCNT_D_DTS */
{
	union												/* BUSDECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	b30Dummy1				:30;
		} stBit;
	} unBUSDECCCTL;										/* 0xFFC4FA00 - 0xFFC4FA04 */

}	Reg_Ecc_EccCnt_D_DtsType;


/* ECCCNT_D_DMA0 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_D_DMA0 ========================= */
/* ============================================================================ */
typedef	struct											/* ECCCNT_D_DMA0 */
{
	union												/* BUSDECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	b30Dummy1				:30;
		} stBit;
	} unBUSDECCCTL;										/* 0xFFC4FB00 - 0xFFC4FB04 */

}	Reg_Ecc_EccCnt_D_Dma0Type;


/* ECCCNT_D_DMA1 */
/* ============================================================================ */
/* ============================ Module: ECCCNT_D_DMA1 ========================= */
/* ============================================================================ */
typedef	struct											/* ECCCNT_D_DMA1 */
{
	union												/* BUSDECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	b30Dummy1				:30;
		} stBit;
	} unBUSDECCCTL;										/* 0xFFC4FB80 - 0xFFC4FB84 */

}	Reg_Ecc_EccCnt_D_Dma1Type;


/* ECCCNT_D_V2AnW */
/* ============================================================================ */
/* ============================ Module: ECCCNT_D_V2AnW ======================== */
/* ============================================================================ */
typedef	struct											/* ECCCNT_D_V2AnW */
{
	union												/* BUSDVCECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	b30Dummy1				:30;
		} stBit;
	} unBUSDVCECCCTL;									/* OFFSET 0x00 - 0x04 */

}	Reg_Ecc_EccCnt_D_V2AnWType;


/* DFP_ECCCNT_BUSD_ROM */
/* ============================================================================ */
/* ============================ Module: DFP_ECCCNT_BUSD_ROM =================== */
/* ============================================================================ */
typedef	struct											/* DFP_ECCCNT_BUSD_ROM */
{
	union												/* BUSDECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	b30Dummy1				:30;
		} stBit;
	} unBUSDECCCTL;										/* 0xFF0C6300 - 0xFF0C6304 */

}	Reg_Ecc_Dfp_EccCnt_Busd_RomType;


/* DFP_ECCCNT_BUSD_SYS */
/* ============================================================================ */
/* ============================ Module: DFP_ECCCNT_BUSD_SYS =================== */
/* ============================================================================ */
typedef	struct											/* DFP_ECCCNT_BUSD_SYS */
{
	union												/* BUSDECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	b30Dummy1				:30;
		} stBit;
	} unBUSDECCCTL;										/* 0xFF0C6400 - 0xFF0C6404 */

}	Reg_Ecc_Dfp_EccCnt_Busd_SysType;


/* DFP_ECCCNT_BUSD_FNT */
/* ============================================================================ */
/* ============================ Module: DFP_ECCCNT_BUSD_FNT =================== */
/* ============================================================================ */
typedef	struct											/* DFP_ECCCNT_BUSD_FNT */
{
	union												/* BUSDECCCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access */
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	b30Dummy1				:30;
		} stBit;
	} unBUSDECCCTL;										/* 0xFF0C6500 - 0xFF0C6504 */

}	Reg_Ecc_Dfp_EccCnt_Busd_FntType;


/* BECCCAP_LRAM */
/* ============================================================================ */
/* ============================ Module: BECCCAP_LRAM ========================== */
/* ============================================================================ */
typedef	struct											/* BECCCAP_LRAM */
{
	union												/* LR_BUSERRINT */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDSEDIE					:1;				/* DSEDIE */
			U4	xDDEDIE					:1;				/* DDEDIE */
			U4	xASEDIE					:1;				/* ASEDIE */
			U4	xADEDIE					:1;				/* ADEDIE */
			U4	b28Dummy1				:28;
		} stBit;
	} unLR_BUSERRINT;									/* 0xFFC50000 - 0xFFC50004 */

	U1	u1Dummy1[0xFFC50010U - 0xFFC50004U];			/* 0xFFC50004 - 0xFFC50010 */

	union												/* LR_BUSASSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xASSTCLR00				:1;				/* ASSTCLR00 */
			U4	xASSTCLR01				:1;				/* ASSTCLR01 */
			U4	xASSTCLR02				:1;				/* ASSTCLR02 */
			U4	xASSTCLR03				:1;				/* ASSTCLR03 */
			U4	xASSTCLR04				:1;				/* ASSTCLR04 */
			U4	xASSTCLR05				:1;				/* ASSTCLR05 */
			U4	b10Dummy1				:10;
			U4	xASSTCLR16				:1;				/* ASSTCLR16 */
			U4	xASSTCLR17				:1;				/* ASSTCLR17 */
			U4	xASSTCLR18				:1;				/* ASSTCLR18 */
			U4	b13Dummy2				:13;
		} stBit;
	} unLR_BUSASSTCLR;									/* 0xFFC50010 - 0xFFC50014 */

	U1	u1Dummy2[0xFFC50020U - 0xFFC50014U];			/* 0xFFC50014 - 0xFFC50020 */

	union												/* LR_BUSADSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xADSTCLR00				:1;				/* ADSTCLR00 */
			U4	xADSTCLR01				:1;				/* ADSTCLR01 */
			U4	xADSTCLR02				:1;				/* ADSTCLR02 */
			U4	xADSTCLR03				:1;				/* ADSTCLR03 */
			U4	xADSTCLR04				:1;				/* ADSTCLR04 */
			U4	xADSTCLR05				:1;				/* ADSTCLR05 */
			U4	b10Dummy1				:10;
			U4	xADSTCLR16				:1;				/* ADSTCLR16 */
			U4	xADSTCLR17				:1;				/* ADSTCLR17 */
			U4	xADSTCLR18				:1;				/* ADSTCLR18 */
			U4	b13Dummy2				:13;
		} stBit;
	} unLR_BUSADSTCLR;									/* 0xFFC50020 - 0xFFC50024 */

	U1	u1Dummy3[0xFFC50030U - 0xFFC50024U];			/* 0xFFC50024 - 0xFFC50030 */

	union												/* LR_BUSDSSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDSSTCLR00				:1;				/* DSSTCLR00 */
			U4	xDSSTCLR01				:1;				/* DSSTCLR01 */
			U4	xDSSTCLR02				:1;				/* DSSTCLR02 */
			U4	xDSSTCLR03				:1;				/* DSSTCLR03 */
			U4	xDSSTCLR04				:1;				/* DSSTCLR04 */
			U4	xDSSTCLR05				:1;				/* DSSTCLR05 */
			U4	b26Dummy1				:26;
		} stBit;
	} unLR_BUSDSSTCLR;									/* 0xFFC50030 - 0xFFC50034 */

	U1	u1Dummy4[0xFFC50040U - 0xFFC50034U];			/* 0xFFC50034 - 0xFFC50040 */

	union												/* LR_BUSDDSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDDSTCLR00				:1;				/* DDSTCLR00 */
			U4	xDDSTCLR01				:1;				/* DDSTCLR01 */
			U4	xDDSTCLR02				:1;				/* DDSTCLR02 */
			U4	xDDSTCLR03				:1;				/* DDSTCLR03 */
			U4	xDDSTCLR04				:1;				/* DDSTCLR04 */
			U4	xDDSTCLR05				:1;				/* DDSTCLR05 */
			U4	b26Dummy1				:26;
		} stBit;
	} unLR_BUSDDSTCLR;									/* 0xFFC50040 - 0xFFC50044 */

	U1	u1Dummy5[0xFFC50050U - 0xFFC50044U];			/* 0xFFC50044 - 0xFFC50050 */

	union												/* LR_BUSASERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xASEDF00				:1;				/* ASEDF00 */
			U4	xASEDF01				:1;				/* ASEDF01 */
			U4	xASEDF02				:1;				/* ASEDF02 */
			U4	xASEDF03				:1;				/* ASEDF03 */
			U4	xASEDF04				:1;				/* ASEDF04 */
			U4	xASEDF05				:1;				/* ASEDF05 */
			U4	b10Dummy1				:10;
			U4	xASEDF16				:1;				/* ASEDF16 */
			U4	xASEDF17				:1;				/* ASEDF17 */
			U4	xASEDF18				:1;				/* ASEDF18 */
			U4	b13Dummy2				:13;
		} stBit;
	} unLR_BUSASERSTR;									/* 0xFFC50050 - 0xFFC50054 */

	U1	u1Dummy6[0xFFC50060U - 0xFFC50054U];			/* 0xFFC50054 - 0xFFC50060 */

	union												/* LR_BUSADERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xADEDF00				:1;				/* ADEDF00 */
			U4	xADEDF01				:1;				/* ADEDF01 */
			U4	xADEDF02				:1;				/* ADEDF02 */
			U4	xADEDF03				:1;				/* ADEDF03 */
			U4	xADEDF04				:1;				/* ADEDF04 */
			U4	xADEDF05				:1;				/* ADEDF05 */
			U4	b10Dummy1				:10;
			U4	xADEDF16				:1;				/* ADEDF16 */
			U4	xADEDF17				:1;				/* ADEDF17 */
			U4	xADEDF18				:1;				/* ADEDF18 */
			U4	b13Dummy2				:13;
		} stBit;
	} unLR_BUSADERSTR;									/* 0xFFC50060 - 0xFFC50064 */

	U1	u1Dummy7[0xFFC50070U - 0xFFC50064U];			/* 0xFFC50064 - 0xFFC50070 */

	union												/* LR_BUSDSERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDSEDF00				:1;				/* DSEDF00 */
			U4	xDSEDF01				:1;				/* DSEDF01 */
			U4	xDSEDF02				:1;				/* DSEDF02 */
			U4	xDSEDF03				:1;				/* DSEDF03 */
			U4	xDSEDF04				:1;				/* DSEDF04 */
			U4	xDSEDF05				:1;				/* DSEDF05 */
			U4	b26Dummy1				:26;
		} stBit;
	} unLR_BUSDSERSTR;									/* 0xFFC50070 - 0xFFC50074 */

	U1	u1Dummy8[0xFFC50080U - 0xFFC50074U];			/* 0xFFC50074 - 0xFFC50080 */

	union												/* LR_BUSDDERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDDEDF00				:1;				/* DDEDF00 */
			U4	xDDEDF01				:1;				/* DDEDF01 */
			U4	xDDEDF02				:1;				/* DDEDF02 */
			U4	xDDEDF03				:1;				/* DDEDF03 */
			U4	xDDEDF04				:1;				/* DDEDF04 */
			U4	xDDEDF05				:1;				/* DDEDF05 */
			U4	b26Dummy1				:26;
		} stBit;
	} unLR_BUSDDERSTR;									/* 0xFFC50080 - 0xFFC50084 */

}	Reg_Ecc_BeccCap_LramType;


/* BECCCAP_CRAM */
/* ============================================================================ */
/* ============================ Module: BECCCAP_CRAM ========================== */
/* ============================================================================ */
typedef	struct											/* BECCCAP_CRAM */
{
	union												/* CR_BUSERRINT */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDSEDIE					:1;				/* DSEDIE */
			U4	xDDEDIE					:1;				/* DDEDIE */
			U4	xASEDIE					:1;				/* ASEDIE */
			U4	xADEDIE					:1;				/* ADEDIE */
			U4	b28Dummy1				:28;
		} stBit;
	} unCR_BUSERRINT;									/* 0xFFC50100 - 0xFFC50104 */

	U1	u1Dummy1[0xFFC50110U - 0xFFC50104U];			/* 0xFFC50104 - 0xFFC50110 */

	union												/* CR_BUSASSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xASSTCLR00				:1;				/* ASSTCLR00 */
			U4	xASSTCLR01				:1;				/* ASSTCLR01 */
			U4	xASSTCLR02				:1;				/* ASSTCLR02 */
			U4	xDummy1					:1;
			U4	xASSTCLR04				:1;				/* ASSTCLR04 */
			U4	xASSTCLR05				:1;				/* ASSTCLR05 */
			U4	xASSTCLR06				:1;				/* ASSTCLR06 */
			U4	xDummy2					:1;
			U4	xASSTCLR08				:1;				/* ASSTCLR08 */
			U4	xASSTCLR09				:1;				/* ASSTCLR09 */
			U4	xASSTCLR10				:1;				/* ASSTCLR10 */
			U4	b7Dummy3				:7;
			U4	xASSTCLR18				:1;				/* ASSTCLR18 */
			U4	b5Dummy4				:5;
			U4	xASSTCLR24				:1;				/* ASSTCLR24 */
			U4	xASSTCLR25				:1;				/* ASSTCLR25 */
			U4	xASSTCLR26				:1;				/* ASSTCLR26 */
			U4	xDummy5					:1;
			U4	xASSTCLR28				:1;				/* ASSTCLR28 */
			U4	b3Dummy6				:3;
		} stBit;
	} unCR_BUSASSTCLR;									/* 0xFFC50110 - 0xFFC50114 */

	U1	u1Dummy2[0xFFC50120U - 0xFFC50114U];			/* 0xFFC50114 - 0xFFC50120 */

	union												/* CR_BUSADSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xADSTCLR00				:1;				/* ADSTCLR00 */
			U4	xADSTCLR01				:1;				/* ADSTCLR01 */
			U4	xADSTCLR02				:1;				/* ADSTCLR02 */
			U4	xDummy1					:1;
			U4	xADSTCLR04				:1;				/* ADSTCLR04 */
			U4	xADSTCLR05				:1;				/* ADSTCLR05 */
			U4	xADSTCLR06				:1;				/* ADSTCLR06 */
			U4	xDummy2					:1;
			U4	xADSTCLR08				:1;				/* ADSTCLR08 */
			U4	xADSTCLR09				:1;				/* ADSTCLR09 */
			U4	xADSTCLR10				:1;				/* ADSTCLR10 */
			U4	b7Dummy3				:7;
			U4	xADSTCLR18				:1;				/* ADSTCLR18 */
			U4	b5Dummy4				:5;
			U4	xADSTCLR24				:1;				/* ADSTCLR24 */
			U4	xADSTCLR25				:1;				/* ADSTCLR25 */
			U4	xADSTCLR26				:1;				/* ADSTCLR26 */
			U4	xDummy5					:1;
			U4	xADSTCLR28				:1;				/* ADSTCLR28 */
			U4	b3Dummy6				:3;
		} stBit;
	} unCR_BUSADSTCLR;									/* 0xFFC50120 - 0xFFC50124 */

	U1	u1Dummy3[0xFFC50130U - 0xFFC50124U];			/* 0xFFC50124 - 0xFFC50130 */

	union												/* CR_BUSDSSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDSSTCLR00				:1;				/* DSSTCLR00 */
			U4	xDSSTCLR01				:1;				/* DSSTCLR01 */
			U4	xDSSTCLR02				:1;				/* DSSTCLR02 */
			U4	xDummy1					:1;
			U4	xDSSTCLR04				:1;				/* DSSTCLR04 */
			U4	xDSSTCLR05				:1;				/* DSSTCLR05 */
			U4	xDSSTCLR06				:1;				/* DSSTCLR06 */
			U4	xDummy2					:1;
			U4	xDSSTCLR08				:1;				/* DSSTCLR08 */
			U4	xDSSTCLR09				:1;				/* DSSTCLR09 */
			U4	xDSSTCLR10				:1;				/* DSSTCLR10 */
			U4	b7Dummy3				:7;
			U4	xDSSTCLR18				:1;				/* DSSTCLR18 */
			U4	b13Dummy4				:13;
		} stBit;
	} unCR_BUSDSSTCLR;									/* 0xFFC50130 - 0xFFC50134 */

	U1	u1Dummy4[0xFFC50140U - 0xFFC50134U];			/* 0xFFC50134 - 0xFFC50140 */

	union												/* CR_BUSDDSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDDSTCLR00				:1;				/* DDSTCLR00 */
			U4	xDDSTCLR01				:1;				/* DDSTCLR01 */
			U4	xDDSTCLR02				:1;				/* DDSTCLR02 */
			U4	xDummy1					:1;
			U4	xDDSTCLR04				:1;				/* DDSTCLR04 */
			U4	xDDSTCLR05				:1;				/* DDSTCLR05 */
			U4	xDDSTCLR06				:1;				/* DDSTCLR06 */
			U4	xDummy2					:1;
			U4	xDDSTCLR08				:1;				/* DDSTCLR08 */
			U4	xDDSTCLR09				:1;				/* DDSTCLR09 */
			U4	xDDSTCLR10				:1;				/* DDSTCLR10 */
			U4	b7Dummy3				:7;
			U4	xDDSTCLR18				:1;				/* DDSTCLR18 */
			U4	b13Dummy4				:13;
		} stBit;
	} unCR_BUSDDSTCLR;									/* 0xFFC50140 - 0xFFC50144 */

	U1	u1Dummy5[0xFFC50150U - 0xFFC50144U];			/* 0xFFC50144 - 0xFFC50150 */

	union												/* CR_BUSASERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xASEDF00				:1;				/* ASEDF00 */
			U4	xASEDF01				:1;				/* ASEDF01 */
			U4	xASEDF02				:1;				/* ASEDF02 */
			U4	xDummy1					:1;
			U4	xASEDF04				:1;				/* ASEDF04 */
			U4	xASEDF05				:1;				/* ASEDF05 */
			U4	xASEDF06				:1;				/* ASEDF06 */
			U4	xDummy2					:1;
			U4	xASEDF08				:1;				/* ASEDF08 */
			U4	xASEDF09				:1;				/* ASEDF09 */
			U4	xASEDF10				:1;				/* ASEDF10 */
			U4	b7Dummy3				:7;
			U4	xASEDF18				:1;				/* ASEDF18 */
			U4	b5Dummy4				:5;
			U4	xASEDF24				:1;				/* ASEDF24 */
			U4	xASEDF25				:1;				/* ASEDF25 */
			U4	xASEDF26				:1;				/* ASEDF26 */
			U4	xDummy5					:1;
			U4	xASEDF28				:1;				/* ASEDF28 */
			U4	b3Dummy6				:3;
		} stBit;
	} unCR_BUSASERSTR;									/* 0xFFC50150 - 0xFFC50154 */

	U1	u1Dummy6[0xFFC50160U - 0xFFC50154U];			/* 0xFFC50154 - 0xFFC50160 */

	union												/* CR_BUSADERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xADEDF00				:1;				/* ADEDF00 */
			U4	xADEDF01				:1;				/* ADEDF01 */
			U4	xADEDF02				:1;				/* ADEDF02 */
			U4	xDummy1					:1;
			U4	xADEDF04				:1;				/* ADEDF04 */
			U4	xADEDF05				:1;				/* ADEDF05 */
			U4	xADEDF06				:1;				/* ADEDF06 */
			U4	xDummy2					:1;
			U4	xADEDF08				:1;				/* ADEDF08 */
			U4	xADEDF09				:1;				/* ADEDF09 */
			U4	xADEDF10				:1;				/* ADEDF10 */
			U4	b7Dummy3				:7;
			U4	xADEDF18				:1;				/* ADEDF18 */
			U4	b5Dummy4				:5;
			U4	xADEDF24				:1;				/* ADEDF24 */
			U4	xADEDF25				:1;				/* ADEDF25 */
			U4	xADEDF26				:1;				/* ADEDF26 */
			U4	xDummy5					:1;
			U4	xADEDF28				:1;				/* ADEDF28 */
			U4	b3Dummy6				:3;
		} stBit;
	} unCR_BUSADERSTR;									/* 0xFFC50160 - 0xFFC50164 */

	U1	u1Dummy7[0xFFC50170U - 0xFFC50164U];			/* 0xFFC50164 - 0xFFC50170 */

	union												/* CR_BUSDSERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDSEDF00				:1;				/* DSEDF00 */
			U4	xDSEDF01				:1;				/* DSEDF01 */
			U4	xDSEDF02				:1;				/* DSEDF02 */
			U4	xDummy1					:1;
			U4	xDSEDF04				:1;				/* DSEDF04 */
			U4	xDSEDF05				:1;				/* DSEDF05 */
			U4	xDSEDF06				:1;				/* DSEDF06 */
			U4	xDummy2					:1;
			U4	xDSEDF08				:1;				/* DSEDF08 */
			U4	xDSEDF09				:1;				/* DSEDF09 */
			U4	xDSEDF10				:1;				/* DSEDF10 */
			U4	b7Dummy3				:7;
			U4	xDSEDF18				:1;				/* DSEDF18 */
			U4	b13Dummy4				:13;
		} stBit;
	} unCR_BUSDSERSTR;									/* 0xFFC50170 - 0xFFC50174 */

	U1	u1Dummy8[0xFFC50180U - 0xFFC50174U];			/* 0xFFC50174 - 0xFFC50180 */

	union												/* CR_BUSDDERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDDEDF00				:1;				/* DDEDF00 */
			U4	xDDEDF01				:1;				/* DDEDF01 */
			U4	xDDEDF02				:1;				/* DDEDF02 */
			U4	xDummy1					:1;
			U4	xDDEDF04				:1;				/* DDEDF04 */
			U4	xDDEDF05				:1;				/* DDEDF05 */
			U4	xDDEDF06				:1;				/* DDEDF06 */
			U4	xDummy2					:1;
			U4	xDDEDF08				:1;				/* DDEDF08 */
			U4	xDDEDF09				:1;				/* DDEDF09 */
			U4	xDDEDF10				:1;				/* DDEDF10 */
			U4	b7Dummy3				:7;
			U4	xDDEDF18				:1;				/* DDEDF18 */
			U4	b13Dummy4				:13;
		} stBit;
	} unCR_BUSDDERSTR;									/* 0xFFC50180 - 0xFFC50184 */

}	Reg_Ecc_BeccCap_CramType;


/* BECCCAP_CFL */
/* ============================================================================ */
/* ============================ Module: BECCCAP_CFL =========================== */
/* ============================================================================ */
typedef	struct											/* BECCCAP_CFL */
{
	union												/* CF_BUSERRINT */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b2Dummy1				:2;
			U4	xASEDIE					:1;				/* ASEDIE */
			U4	xADEDIE					:1;				/* ADEDIE */
			U4	b28Dummy2				:28;
		} stBit;
	} unCF_BUSERRINT;									/* 0xFFC50300 - 0xFFC50304 */

	U1	u1Dummy1[0xFFC50310U - 0xFFC50304U];			/* 0xFFC50304 - 0xFFC50310 */

	union												/* CF_BUSASSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xASSTCLR00				:1;				/* ASSTCLR00 */
			U4	xASSTCLR01				:1;				/* ASSTCLR01 */
			U4	b2Dummy1				:2;
			U4	xASSTCLR02				:1;				/* ASSTCLR02 */
			U4	xASSTCLR03				:1;				/* ASSTCLR03 */
			U4	b2Dummy2				:2;
			U4	xASSTCLR04				:1;				/* ASSTCLR04 */
			U4	xASSTCLR05				:1;				/* ASSTCLR05 */
			U4	b2Dummy3				:2;
			U4	xASSTCLR08				:1;				/* ASSTCLR08 */
			U4	xASSTCLR09				:1;				/* ASSTCLR09 */
			U4	b14Dummy4				:14;
			U4	xASSTCLR24				:1;				/* ASSTCLR24 */
			U4	xASSTCLR25				:1;				/* ASSTCLR25 */
			U4	b6Dummy5				:6;
		} stBit;
	} unCF_BUSASSTCLR;									/* 0xFFC50310 - 0xFFC50314 */

	U1	u1Dummy2[0xFFC50320U - 0xFFC50314U];			/* 0xFFC50314 - 0xFFC50320 */

	union												/* CF_BUSADSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xADSTCLR00				:1;				/* ADSTCLR00 */
			U4	xADSTCLR01				:1;				/* ADSTCLR01 */
			U4	b2Dummy1				:2;
			U4	xADSTCLR02				:1;				/* ADSTCLR02 */
			U4	xADSTCLR03				:1;				/* ADSTCLR03 */
			U4	b2Dummy2				:2;
			U4	xADSTCLR04				:1;				/* ADSTCLR04 */
			U4	xADSTCLR05				:1;				/* ADSTCLR05 */
			U4	b2Dummy3				:2;
			U4	xADSTCLR08				:1;				/* ADSTCLR08 */
			U4	xADSTCLR09				:1;				/* ADSTCLR09 */
			U4	b14Dummy4				:14;
			U4	xADSTCLR24				:1;				/* ADSTCLR24 */
			U4	xADSTCLR25				:1;				/* ADSTCLR25 */
			U4	b6Dummy5				:6;
		} stBit;
	} unCF_BUSADSTCLR;									/* 0xFFC50320 - 0xFFC50324 */

	U1	u1Dummy3[0xFFC50350U - 0xFFC50324U];			/* 0xFFC50324 - 0xFFC50350 */

	union												/* CF_BUSASERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xASEDF00				:1;				/* ASEDF00 */
			U4	xASEDF01				:1;				/* ASEDF01 */
			U4	b2Dummy1				:2;
			U4	xASEDF02				:1;				/* ASEDF02 */
			U4	xASEDF03				:1;				/* ASEDF03 */
			U4	b2Dummy2				:2;
			U4	xASEDF04				:1;				/* ASEDF04 */
			U4	xASEDF05				:1;				/* ASEDF05 */
			U4	b2Dummy3				:2;
			U4	xASEDF08				:1;				/* ASEDF08 */
			U4	xASEDF09				:1;				/* ASEDF09 */
			U4	b14Dummy4				:14;
			U4	xASEDF24				:1;				/* ASEDF24 */
			U4	xASEDF25				:1;				/* ASEDF25 */
			U4	b6Dummy5				:6;
		} stBit;
	} unCF_BUSASERSTR;									/* 0xFFC50350 - 0xFFC50354 */

	U1	u1Dummy4[0xFFC50360U - 0xFFC50354U];			/* 0xFFC50354 - 0xFFC50360 */

	union												/* CF_BUSADERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xADEDF00				:1;				/* ADEDF00 */
			U4	xADEDF01				:1;				/* ADEDF01 */
			U4	b2Dummy1				:2;
			U4	xADEDF02				:1;				/* ADEDF02 */
			U4	xADEDF03				:1;				/* ADEDF03 */
			U4	b2Dummy2				:2;
			U4	xADEDF04				:1;				/* ADEDF04 */
			U4	xADEDF05				:1;				/* ADEDF05 */
			U4	b2Dummy3				:2;
			U4	xADEDF08				:1;				/* ADEDF08 */
			U4	xADEDF09				:1;				/* ADEDF09 */
			U4	b14Dummy4				:14;
			U4	xADEDF24				:1;				/* ADEDF24 */
			U4	xADEDF25				:1;				/* ADEDF25 */
			U4	b6Dummy5				:6;
		} stBit;
	} unCF_BUSADERSTR;									/* 0xFFC50360 - 0xFFC50364 */

}	Reg_Ecc_BeccCap_CflType;


/* BECCCAP_PERI */
/* ============================================================================ */
/* ============================ Module: BECCCAP_PERI ========================== */
/* ============================================================================ */
typedef	struct											/* BECCCAP_PERI */
{
	union												/* PH_BUSERRINT */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDSEDIE					:1;				/* DSEDIE */
			U4	xDDEDIE					:1;				/* DDEDIE */
			U4	xASEDIE					:1;				/* ASEDIE */
			U4	xADEDIE					:1;				/* ADEDIE */
			U4	b28Dummy1				:28;
		} stBit;
	} unPH_BUSERRINT;									/* 0xFFC50400 - 0xFFC50404 */

	U1	u1Dummy1[0xFFC50410U - 0xFFC50404U];			/* 0xFFC50404 - 0xFFC50410 */

	union												/* PH_BUSASSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b16Dummy1				:16;
			U4	xASSTCLR16				:1;				/* ASSTCLR16 */
			U4	xASSTCLR17				:1;				/* ASSTCLR17 */
			U4	xASSTCLR18				:1;				/* ASSTCLR18 */
			U4	xDummy2					:1;
			U4	xASSTCLR20				:1;				/* ASSTCLR20 */
			U4	b4Dummy3				:4;
			U4	xASSTCLR25				:1;				/* ASSTCLR25 */
			U4	b6Dummy4				:6;
		} stBit;
	} unPH_BUSASSTCLR;									/* 0xFFC50410 - 0xFFC50414 */

	U1	u1Dummy2[0xFFC50420U - 0xFFC50414U];			/* 0xFFC50414 - 0xFFC50420 */

	union												/* PH_BUSADSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b16Dummy1				:16;
			U4	xADSTCLR16				:1;				/* ADSTCLR16 */
			U4	xADSTCLR17				:1;				/* ADSTCLR17 */
			U4	xADSTCLR18				:1;				/* ADSTCLR18 */
			U4	xDummy2					:1;
			U4	xADSTCLR20				:1;				/* ADSTCLR20 */
			U4	b4Dummy3				:4;
			U4	xADSTCLR25				:1;				/* ADSTCLR25 */
			U4	b6Dummy4				:6;
		} stBit;
	} unPH_BUSADSTCLR;									/* 0xFFC50420 - 0xFFC50424 */

	U1	u1Dummy3[0xFFC50430U - 0xFFC50424U];			/* 0xFFC50424 - 0xFFC50430 */

	union												/* PH_BUSDSSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDSSTCLR00				:1;				/* DSSTCLR00 */
			U4	xDSSTCLR01				:1;				/* DSSTCLR01 */
			U4	xDSSTCLR02				:1;				/* DSSTCLR02 */
			U4	xDSSTCLR03				:1;				/* DSSTCLR03 */
			U4	xDSSTCLR04				:1;				/* DSSTCLR04 */
			U4	xDSSTCLR05				:1;				/* DSSTCLR05 */
			U4	b2Dummy1				:2;
			U4	xDSSTCLR08				:1;				/* DSSTCLR08 */
			U4	xDSSTCLR09				:1;				/* DSSTCLR09 */
			U4	xDSSTCLR10				:1;				/* DSSTCLR10 */
			U4	xDSSTCLR11				:1;				/* DSSTCLR11 */
			U4	xDSSTCLR12				:1;				/* DSSTCLR12 */
			U4	xDSSTCLR13				:1;				/* DSSTCLR13 */
			U4	b2Dummy2				:2;
			U4	xDSSTCLR16				:1;				/* DSSTCLR16 */
			U4	xDSSTCLR17				:1;				/* DSSTCLR17 */
			U4	xDSSTCLR18				:1;				/* DSSTCLR18 */
			U4	b6Dummy3				:6;
			U4	xDSSTCLR25				:1;				/* DSSTCLR25 */
			U4	b6Dummy4				:6;
		} stBit;
	} unPH_BUSDSSTCLR;									/* 0xFFC50430 - 0xFFC50434 */

	U1	u1Dummy4[0xFFC50440U - 0xFFC50434U];			/* 0xFFC50434 - 0xFFC50440 */

	union												/* PH_BUSDDSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDDSTCLR00				:1;				/* DDSTCLR00 */
			U4	xDDSTCLR01				:1;				/* DDSTCLR01 */
			U4	xDDSTCLR02				:1;				/* DDSTCLR02 */
			U4	xDDSTCLR03				:1;				/* DDSTCLR03 */
			U4	xDDSTCLR04				:1;				/* DDSTCLR04 */
			U4	xDDSTCLR05				:1;				/* DDSTCLR05 */
			U4	b2Dummy1				:2;
			U4	xDDSTCLR08				:1;				/* DDSTCLR08 */
			U4	xDDSTCLR09				:1;				/* DDSTCLR09 */
			U4	xDDSTCLR10				:1;				/* DDSTCLR10 */
			U4	xDDSTCLR11				:1;				/* DDSTCLR11 */
			U4	xDDSTCLR12				:1;				/* DDSTCLR12 */
			U4	xDDSTCLR13				:1;				/* DDSTCLR13 */
			U4	b2Dummy2				:2;
			U4	xDDSTCLR16				:1;				/* DDSTCLR16 */
			U4	xDDSTCLR17				:1;				/* DDSTCLR17 */
			U4	xDDSTCLR18				:1;				/* DDSTCLR18 */
			U4	b6Dummy3				:6;
			U4	xDDSTCLR25				:1;				/* DDSTCLR25 */
			U4	b6Dummy4				:6;
		} stBit;
	} unPH_BUSDDSTCLR;									/* 0xFFC50440 - 0xFFC50444 */

	U1	u1Dummy5[0xFFC50450U - 0xFFC50444U];			/* 0xFFC50444 - 0xFFC50450 */

	union												/* PH_BUSASERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b16Dummy1				:16;
			U4	xASEDF16				:1;				/* ASEDF16 */
			U4	xASEDF17				:1;				/* ASEDF17 */
			U4	xASEDF18				:1;				/* ASEDF18 */
			U4	xDummy2					:1;
			U4	xASEDF20				:1;				/* ASEDF20 */
			U4	b4Dummy3				:4;
			U4	xASEDF25				:1;				/* ASEDF25 */
			U4	b6Dummy4				:6;
		} stBit;
	} unPH_BUSASERSTR;									/* 0xFFC50450 - 0xFFC50454 */

	U1	u1Dummy6[0xFFC50460U - 0xFFC50454U];			/* 0xFFC50454 - 0xFFC50460 */

	union												/* PH_BUSADERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b16Dummy1				:16;
			U4	xADEDF16				:1;				/* ADEDF16 */
			U4	xADEDF17				:1;				/* ADEDF17 */
			U4	xADEDF18				:1;				/* ADEDF18 */
			U4	xDummy2					:1;
			U4	xADEDF20				:1;				/* ADEDF20 */
			U4	b4Dummy3				:4;
			U4	xADEDF25				:1;				/* ADEDF25 */
			U4	b6Dummy4				:6;
		} stBit;
	} unPH_BUSADERSTR;									/* 0xFFC50460 - 0xFFC50464 */

	U1	u1Dummy7[0xFFC50470U - 0xFFC50464U];			/* 0xFFC50464 - 0xFFC50470 */

	union												/* PH_BUSDSERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDSEDF00				:1;				/* DSEDF00 */
			U4	xDSEDF01				:1;				/* DSEDF01 */
			U4	xDSEDF02				:1;				/* DSEDF02 */
			U4	xDSEDF03				:1;				/* DSEDF03 */
			U4	xDSEDF04				:1;				/* DSEDF04 */
			U4	xDSEDF05				:1;				/* DSEDF05 */
			U4	b2Dummy1				:2;
			U4	xDSEDF08				:1;				/* DSEDF08 */
			U4	xDSEDF09				:1;				/* DSEDF09 */
			U4	xDSEDF10				:1;				/* DSEDF10 */
			U4	xDSEDF11				:1;				/* DSEDF11 */
			U4	xDSEDF12				:1;				/* DSEDF12 */
			U4	xDSEDF13				:1;				/* DSEDF13 */
			U4	b2Dummy2				:2;
			U4	xDSEDF16				:1;				/* DSEDF16 */
			U4	xDSEDF17				:1;				/* DSEDF17 */
			U4	xDSEDF18				:1;				/* DSEDF18 */
			U4	b6Dummy3				:6;
			U4	xDSEDF25				:1;				/* DSEDF25 */
			U4	b6Dummy4				:6;
		} stBit;
	} unPH_BUSDSERSTR;									/* 0xFFC50470 - 0xFFC50474 */

	U1	u1Dummy8[0xFFC50480U - 0xFFC50474U];			/* 0xFFC50474 - 0xFFC50480 */

	union												/* PH_BUSDDERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDDEDF00				:1;				/* DDEDF00 */
			U4	xDDEDF01				:1;				/* DDEDF01 */
			U4	xDDEDF02				:1;				/* DDEDF02 */
			U4	xDDEDF03				:1;				/* DDEDF03 */
			U4	xDDEDF04				:1;				/* DDEDF04 */
			U4	xDDEDF05				:1;				/* DDEDF05 */
			U4	b2Dummy1				:2;
			U4	xDDEDF08				:1;				/* DDEDF08 */
			U4	xDDEDF09				:1;				/* DDEDF09 */
			U4	xDDEDF10				:1;				/* DDEDF10 */
			U4	xDDEDF11				:1;				/* DDEDF11 */
			U4	xDDEDF12				:1;				/* DDEDF12 */
			U4	xDDEDF13				:1;				/* DDEDF13 */
			U4	b2Dummy2				:2;
			U4	xDDEDF16				:1;				/* DDEDF16 */
			U4	xDDEDF17				:1;				/* DDEDF17 */
			U4	xDDEDF18				:1;				/* DDEDF18 */
			U4	b6Dummy3				:6;
			U4	xDDEDF25				:1;				/* DDEDF25 */
			U4	b6Dummy4				:6;
		} stBit;
	} unPH_BUSDDERSTR;									/* 0xFFC50480 - 0xFFC50484 */

}	Reg_Ecc_BeccCap_PeriType;


/* BECCCAP_DMDT */
/* ============================================================================ */
/* ============================ Module: BECCCAP_DMDT ========================== */
/* ============================================================================ */
typedef	struct											/* BECCCAP_DMDT */
{
	union												/* DM_BUSERRINT */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDSEDIE					:1;				/* DSEDIE */
			U4	xDDEDIE					:1;				/* DDEDIE */
			U4	b30Dummy1				:30;
		} stBit;
	} unDM_BUSERRINT;									/* 0xFFC50500 - 0xFFC50504 */

	U1	u1Dummy1[0xFFC50530U - 0xFFC50504U];			/* 0xFFC50504 - 0xFFC50530 */

	union												/* DM_BUSDSSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDSSTCLR00				:1;				/* DSSTCLR00 */
			U4	xDSSTCLR01				:1;				/* DSSTCLR01 */
			U4	xDSSTCLR02				:1;				/* DSSTCLR02 */
			U4	xDSSTCLR03				:1;				/* DSSTCLR03 */
			U4	xDSSTCLR04				:1;				/* DSSTCLR04 */
			U4	xDSSTCLR05				:1;				/* DSSTCLR05 */
			U4	xDSSTCLR06				:1;				/* DSSTCLR06 */
			U4	xDSSTCLR07				:1;				/* DSSTCLR07 */
			U4	xDSSTCLR08				:1;				/* DSSTCLR08 */
			U4	b23Dummy2				:23;
		} stBit;
	} unDM_BUSDSSTCLR;									/* 0xFFC50530 - 0xFFC50534 */

	U1	u1Dummy2[0xFFC50540U - 0xFFC50534U];			/* 0xFFC50534 - 0xFFC50540 */

	union												/* DM_BUSDDSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDDSTCLR00				:1;				/* DDSTCLR00 */
			U4	xDDSTCLR01				:1;				/* DDSTCLR01 */
			U4	xDDSTCLR02				:1;				/* DDSTCLR02 */
			U4	xDDSTCLR03				:1;				/* DDSTCLR03 */
			U4	xDDSTCLR04				:1;				/* DDSTCLR04 */
			U4	xDDSTCLR05				:1;				/* DDSTCLR05 */
			U4	xDDSTCLR06				:1;				/* DDSTCLR06 */
			U4	xDDSTCLR07				:1;				/* DDSTCLR07 */
			U4	xDDSTCLR08				:1;				/* DDSTCLR08 */
			U4	b23Dummy2				:23;
		} stBit;
	} unDM_BUSDDSTCLR;									/* 0xFFC50540 - 0xFFC50544 */

	U1	u1Dummy3[0xFFC50570U - 0xFFC50544U];			/* 0xFFC50544 - 0xFFC50570 */

	union												/* DM_BUSDSERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDSEDF00				:1;				/* DSEDF00 */
			U4	xDSEDF01				:1;				/* DSEDF01 */
			U4	xDSEDF02				:1;				/* DSEDF02 */
			U4	xDSEDF03				:1;				/* DSEDF03 */
			U4	xDSEDF04				:1;				/* DSEDF04 */
			U4	xDSEDF05				:1;				/* DSEDF05 */
			U4	xDSEDF06				:1;				/* DSEDF06 */
			U4	xDSEDF07				:1;				/* DSEDF07 */
			U4	xDSEDF08				:1;				/* DSEDF08 */
			U4	b23Dummy2				:23;
		} stBit;
	} unDM_BUSDSERSTR;									/* 0xFFC50570 - 0xFFC50574 */

	U1	u1Dummy4[0xFFC50580U - 0xFFC50574U];			/* 0xFFC50574 - 0xFFC50580 */

	union												/* DM_BUSDDERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDDEDF00				:1;				/* DDEDF00 */
			U4	xDDEDF01				:1;				/* DDEDF01 */
			U4	xDDEDF02				:1;				/* DDEDF02 */
			U4	xDDEDF03				:1;				/* DDEDF03 */
			U4	xDDEDF04				:1;				/* DDEDF04 */
			U4	xDDEDF05				:1;				/* DDEDF05 */
			U4	xDDEDF06				:1;				/* DDEDF06 */
			U4	xDDEDF07				:1;				/* DDEDF07 */
			U4	xDDEDF08				:1;				/* DDEDF08 */
			U4	b23Dummy2				:23;
		} stBit;
	} unDM_BUSDDERSTR;									/* 0xFFC50580 - 0xFFC50584 */

}	Reg_Ecc_BeccCap_DmdtType;


/* BECCCAP_EMU */
/* ============================================================================ */
/* ============================ Module: BECCCAP_EMU =========================== */
/* ============================================================================ */
typedef	struct											/* BECCCAP_EMU */
{
	union												/* EM_BUSERRINT */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDSEDIE					:1;				/* DSEDIE */
			U4	xDDEDIE					:1;				/* DDEDIE */
			U4	xASEDIE					:1;				/* ASEDIE */
			U4	xADEDIE					:1;				/* ADEDIE */
			U4	b28Dummy1				:28;
		} stBit;
	} unEM_BUSERRINT;									/* 0xFFC50800 - 0xFFC50804 */

	U1	u1Dummy1[0xFFC50810U - 0xFFC50804U];			/* 0xFFC50804 - 0xFFC50810 */

	union												/* EM_BUSASSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xASSTCLR00				:1;				/* ASSTCLR00 */
			U4	xDummy1					:1;
			U4	xASSTCLR02				:1;				/* ASSTCLR02 */
			U4	xDummy2					:1;
			U4	xASSTCLR04				:1;				/* ASSTCLR04 */
			U4	xDummy3					:1;
			U4	xASSTCLR06				:1;				/* ASSTCLR06 */
			U4	xDummy4					:1;
			U4	xASSTCLR08				:1;				/* ASSTCLR08 */
			U4	xDummy5					:1;
			U4	xASSTCLR10				:1;				/* ASSTCLR10 */
			U4	b5Dummy6				:5;
			U4	xASSTCLR16				:1;				/* ASSTCLR16 */
			U4	xASSTCLR17				:1;				/* ASSTCLR17 */
			U4	xASSTCLR18				:1;				/* ASSTCLR18 */
			U4	b13Dummy7				:13;
		} stBit;
	} unEM_BUSASSTCLR;									/* 0xFFC50810 - 0xFFC50814 */

	U1	u1Dummy2[0xFFC50820U - 0xFFC50814U];			/* 0xFFC50814 - 0xFFC50820 */

	union												/* EM_BUSADSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xADSTCLR00				:1;				/* ADSTCLR00 */
			U4	xDummy1					:1;
			U4	xADSTCLR02				:1;				/* ADSTCLR02 */
			U4	xDummy2					:1;
			U4	xADSTCLR04				:1;				/* ADSTCLR04 */
			U4	xDummy3					:1;
			U4	xADSTCLR06				:1;				/* ADSTCLR06 */
			U4	xDummy4					:1;
			U4	xADSTCLR08				:1;				/* ADSTCLR08 */
			U4	xDummy5					:1;
			U4	xADSTCLR10				:1;				/* ADSTCLR10 */
			U4	b5Dummy6				:5;
			U4	xADSTCLR16				:1;				/* ADSTCLR16 */
			U4	xADSTCLR17				:1;				/* ADSTCLR17 */
			U4	xADSTCLR18				:1;				/* ADSTCLR18 */
			U4	b13Dummy7				:13;
		} stBit;
	} unEM_BUSADSTCLR;									/* 0xFFC50820 - 0xFFC50824 */

	U1	u1Dummy3[0xFFC50830U - 0xFFC50824U];			/* 0xFFC50824 - 0xFFC50830 */

	union												/* EM_BUSDSSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b17Dummy1				:17;
			U4	xDSSTCLR17				:1;				/* DSSTCLR17 */
			U4	b14Dummy2				:14;
		} stBit;
	} unEM_BUSDSSTCLR;									/* 0xFFC50830 - 0xFFC50834 */

	U1	u1Dummy4[0xFFC50840U - 0xFFC50834U];			/* 0xFFC50834 - 0xFFC50840 */

	union												/* EM_BUSDDSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b17Dummy1				:17;
			U4	xDDSTCLR17				:1;				/* DDSTCLR17 */
			U4	b14Dummy2				:14;
		} stBit;
	} unEM_BUSDDSTCLR;									/* 0xFFC50840 - 0xFFC50844 */

	U1	u1Dummy5[0xFFC50850U - 0xFFC50844U];			/* 0xFFC50844 - 0xFFC50850 */

	union												/* EM_BUSASERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xASEDF00				:1;				/* ASEDF00 */
			U4	xDummy1					:1;
			U4	xASEDF02				:1;				/* ASEDF02 */
			U4	xDummy2					:1;
			U4	xASEDF04				:1;				/* ASEDF04 */
			U4	xDummy3					:1;
			U4	xASEDF06				:1;				/* ASEDF06 */
			U4	xDummy4					:1;
			U4	xASEDF08				:1;				/* ASEDF08 */
			U4	xDummy5					:1;
			U4	xASEDF10				:1;				/* ASEDF10 */
			U4	b5Dummy6				:5;
			U4	xASEDF16				:1;				/* ASEDF16 */
			U4	xASEDF17				:1;				/* ASEDF17 */
			U4	xASEDF18				:1;				/* ASEDF18 */
			U4	b13Dummy7				:13;
		} stBit;
	} unEM_BUSASERSTR;									/* 0xFFC50850 - 0xFFC50854 */

	U1	u1Dummy6[0xFFC50860U - 0xFFC50854U];			/* 0xFFC50854 - 0xFFC50860 */

	union												/* EM_BUSADERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xADEDF00				:1;				/* ADEDF00 */
			U4	xDummy1					:1;
			U4	xADEDF02				:1;				/* ADEDF02 */
			U4	xDummy2					:1;
			U4	xADEDF04				:1;				/* ADEDF04 */
			U4	xDummy3					:1;
			U4	xADEDF06				:1;				/* ADEDF06 */
			U4	xDummy4					:1;
			U4	xADEDF08				:1;				/* ADEDF08 */
			U4	xDummy5					:1;
			U4	xADEDF10				:1;				/* ADEDF10 */
			U4	b5Dummy6				:5;
			U4	xADEDF16				:1;				/* ADEDF16 */
			U4	xADEDF17				:1;				/* ADEDF17 */
			U4	xADEDF18				:1;				/* ADEDF18 */
			U4	b13Dummy7				:13;
		} stBit;
	} unEM_BUSADERSTR;									/* 0xFFC50860 - 0xFFC50864 */

	U1	u1Dummy7[0xFFC50870U - 0xFFC50864U];			/* 0xFFC50864 - 0xFFC50870 */

	union												/* EM_BUSDSERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b17Dummy1				:17;
			U4	xDSEDF17				:1;				/* DSEDF17 */
			U4	b14Dummy2				:14;
		} stBit;
	} unEM_BUSDSERSTR;									/* 0xFFC50870 - 0xFFC50874 */

	U1	u1Dummy8[0xFFC50880U - 0xFFC50874U];			/* 0xFFC50874 - 0xFFC50880 */

	union												/* EM_BUSDDERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b17Dummy1				:17;
			U4	xDDEDF17				:1;				/* DDEDF17 */
			U4	b14Dummy2				:14;
		} stBit;
	} unEM_BUSDDERSTR;									/* 0xFFC50880 - 0xFFC50884 */

}	Reg_Ecc_BeccCap_EmuType;


/* PBnECC */
/* ============================================================================ */
/* ============================ Module: PBnECC ================================ */
/* ============================================================================ */
typedef	struct											/* PBnECC */
{
	union												/* APECKCPROT */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xKCE					:1;				/* KCE */
			U4	b31KCPROT				:31;			/* KCPROT[31:1] */
		} stBit;
	} unAPECKCPROT;										/* OFFSET 0x00 - 0x04 */

}	Reg_Ecc_PbnEccType;


/* DFP_KCPROT */
/* ============================================================================ */
/* ============================ Module: DFP_KCPROT ============================ */
/* ============================================================================ */
typedef	struct											/* DFP_KCPROT */
{
	union												/* DFP_ECCKCPROT */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xKCE					:1;				/* KCE */
			U4	b31KCPROT				:31;			/* KCPROT[31:1] */
		} stBit;
	} unDFP_ECCKCPROT;									/* OFFSET 0x00 - 0x04 */

}	Reg_Ecc_Dfp_KcProtType;


/* DFP_ECCCAP_ROM */
/* ============================================================================ */
/* ============================ Module: DFP_ECCCAP_ROM ======================== */
/* ============================================================================ */
typedef	struct											/* DFP_ECCCAP_ROM */
{
	union												/* DFPR_BUSERRINT */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDSEDIE					:1;				/* DSEDIE */
			U4	xDDEDIE					:1;				/* DDEDIE */
			U4	b30Dummy1				:30;
		} stBit;
	} unDFPR_BUSERRINT;									/* 0xFF0C6600 - 0xFF0C6604 */

	U1	u1Dummy1[0xFF0C6630U - 0xFF0C6604U];			/* 0xFF0C6604 - 0xFF0C6630 */

	union												/* DFPR_BUSDSSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDSSTCLR00				:1;				/* DSSTCLR00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unDFPR_BUSDSSTCLR;								/* 0xFF0C6630 - 0xFF0C6634 */

	U1	u1Dummy2[0xFF0C6640U - 0xFF0C6634U];			/* 0xFF0C6634 - 0xFF0C6640 */

	union												/* DFPR_BUSDDSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDDSTCLR00				:1;				/* DDSTCLR00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unDFPR_BUSDDSTCLR;								/* 0xFF0C6640 - 0xFF0C6644 */

	U1	u1Dummy3[0xFF0C6670U - 0xFF0C6644U];			/* 0xFF0C6644 - 0xFF0C6670 */

	union												/* DFPR_BUSDSERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDSEDF00				:1;				/* DSEDF00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unDFPR_BUSDSERSTR;								/* 0xFF0C6670 - 0xFF0C6674 */

	U1	u1Dummy4[0xFF0C6680U - 0xFF0C6674U];			/* 0xFF0C6674 - 0xFF0C6680 */

	union												/* DFPR_BUSDDERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDDEDF00				:1;				/* DDEDF00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unDFPR_BUSDDERSTR;								/* 0xFF0C6680 - 0xFF0C6684 */

}	Reg_Ecc_Dfp_EccCap_RomType;


/* DFP_ECCCAP_SYS */
/* ============================================================================ */
/* ============================ Module: DFP_ECCCAP_SYS ======================== */
/* ============================================================================ */
typedef	struct											/* DFP_ECCCAP_SYS */
{
	union												/* DFPS_BUSERRINT */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDSEDIE					:1;				/* DSEDIE */
			U4	xDDEDIE					:1;				/* DDEDIE */
			U4	b30Dummy1				:30;
		} stBit;
	} unDFPS_BUSERRINT;									/* 0xFF0C6800 - 0xFF0C6804 */

	U1	u1Dummy1[0xFF0C6830U - 0xFF0C6804U];			/* 0xFF0C6804 - 0xFF0C6830 */

	union												/* DFPS_BUSDSSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDSSTCLR00				:1;				/* DSSTCLR00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unDFPS_BUSDSSTCLR;								/* 0xFF0C6830 - 0xFF0C6834 */

	U1	u1Dummy2[0xFF0C6840U - 0xFF0C6834U];			/* 0xFF0C6834 - 0xFF0C6840 */

	union												/* DFPS_BUSDDSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDDSTCLR00				:1;				/* DDSTCLR00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unDFPS_BUSDDSTCLR;								/* 0xFF0C6840 - 0xFF0C6844 */

	U1	u1Dummy3[0xFF0C6870U - 0xFF0C6844U];			/* 0xFF0C6844 - 0xFF0C6870 */

	union												/* DFPS_BUSDSERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDSEDF00				:1;				/* DSEDF00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unDFPS_BUSDSERSTR;								/* 0xFF0C6870 - 0xFF0C6874 */

	U1	u1Dummy4[0xFF0C6880U - 0xFF0C6874U];			/* 0xFF0C6874 - 0xFF0C6880 */

	union												/* DFPS_BUSDDERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDDEDF00				:1;				/* DDEDF00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unDFPS_BUSDDERSTR;								/* 0xFF0C6880 - 0xFF0C6884 */

}	Reg_Ecc_Dfp_EccCap_SysType;


/* DFP_ECCCAP_FNT */
/* ============================================================================ */
/* ============================ Module: DFP_ECCCAP_FNT ======================== */
/* ============================================================================ */
typedef	struct											/* DFP_ECCCAP_FNT */
{
	union												/* DFPF_BUSERRINT */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDSEDIE					:1;				/* DSEDIE */
			U4	xDDEDIE					:1;				/* DDEDIE */
			U4	xASEDIE					:1;				/* ASEDIE */
			U4	xADEDIE					:1;				/* ADEDIE */
			U4	b28Dummy1				:28;
		} stBit;
	} unDFPF_BUSERRINT;									/* 0xFF0C6A00 - 0xFF0C6A04 */

	U1	u1Dummy1[0xFF0C6A10U - 0xFF0C6A04U];			/* 0xFF0C6A04 - 0xFF0C6A10 */

	union												/* DFPF_BUSASSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xASSTCLR00				:1;				/* ASSTCLR00 */
			U4	xASSTCLR01				:1;				/* ASSTCLR01 */
			U4	b30Dummy1				:30;
		} stBit;
	} unDFPF_BUSASSTCLR;								/* 0xFF0C6A10 - 0xFF0C6A14 */

	U1	u1Dummy2[0xFF0C6A20U - 0xFF0C6A14U];			/* 0xFF0C6A14 - 0xFF0C6A20 */

	union												/* DFPF_BUSADSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xADSTCLR00				:1;				/* ADSTCLR00 */
			U4	xADSTCLR01				:1;				/* ADSTCLR01 */
			U4	b30Dummy1				:30;
		} stBit;
	} unDFPF_BUSADSTCLR;								/* 0xFF0C6A20 - 0xFF0C6A24 */

	U1	u1Dummy3[0xFF0C6A30U - 0xFF0C6A24U];			/* 0xFF0C6A24 - 0xFF0C6A30 */

	union												/* DFPF_BUSDSSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDSSTCLR00				:1;				/* DSSTCLR00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unDFPF_BUSDSSTCLR;								/* 0xFF0C6A30 - 0xFF0C6A34 */

	U1	u1Dummy4[0xFF0C6A40U - 0xFF0C6A34U];			/* 0xFF0C6A34 - 0xFF0C6A40 */

	union												/* DFPF_BUSDDSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDDSTCLR00				:1;				/* DDSTCLR00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unDFPF_BUSDDSTCLR;								/* 0xFF0C6A40 - 0xFF0C6A44 */

	U1	u1Dummy5[0xFF0C6A50U - 0xFF0C6A44U];			/* 0xFF0C6A44 - 0xFF0C6A50 */

	union												/* DFPF_BUSASERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xASEDF00				:1;				/* ASEDF00 */
			U4	xASEDF01				:1;				/* ASEDF01 */
			U4	b30Dummy1				:30;
		} stBit;
	} unDFPF_BUSASERSTR;								/* 0xFF0C6A50 - 0xFF0C6A54 */

	U1	u1Dummy6[0xFF0C6A60U - 0xFF0C6A54U];			/* 0xFF0C6A54 - 0xFF0C6A60 */

	union												/* DFPF_BUSADERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xADEDF00				:1;				/* ADEDF00 */
			U4	xADEDF01				:1;				/* ADEDF01 */
			U4	b30Dummy1				:30;
		} stBit;
	} unDFPF_BUSADERSTR;								/* 0xFF0C6A60 - 0xFF0C6A64 */

	U1	u1Dummy7[0xFF0C6A70U - 0xFF0C6A64U];			/* 0xFF0C6A64 - 0xFF0C6A70 */

	union												/* DFPF_BUSDSERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDSEDF00				:1;				/* DSEDF00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unDFPF_BUSDSERSTR;								/* 0xFF0C6A70 - 0xFF0C6A74 */

	U1	u1Dummy8[0xFF0C6A80U - 0xFF0C6A74U];			/* 0xFF0C6A74 - 0xFF0C6A80 */

	union												/* DFPF_BUSDDERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDDEDF00				:1;				/* DDEDF00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unDFPF_BUSDDERSTR;								/* 0xFF0C6A80 - 0xFF0C6A84 */

}	Reg_Ecc_Dfp_EccCap_FntType;


/* HBnECC */
/* ============================================================================ */
/* ============================ Module: HBnECC ================================ */
/* ============================================================================ */
typedef	struct											/* HBnECC */
{
	union												/* HBECECCCTL */
	{
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xECCDIS					:1;				/* ECCDIS */
			U4	xSECDIS					:1;				/* SECDIS */
			U4	xAECCDIS				:1;				/* AECCDIS */
			U4	b29Dummy1				:29;
		} stBit;
	} unHBECECCCTL;										/* OFFSET 0x0000 - 0x0004 */

	union												/* HBECERRINT */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDIE					:1;				/* SEDIE */
			U4	xDEDIE					:1;				/* DEDIE */
			U4	b2Dummy1				:2;
			U4	xASEDIE					:1;				/* ASEDIE */
			U4	xADEDIE					:1;				/* ADEDIE */
			U4	b26Dummy2				:26;
		} stBit;
	} unHBECERRINT;										/* OFFSET 0x0004 - 0x0008 */

	union												/* HBECSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSTCLR0					:1;				/* STCLR0 */
			U4	b31Dummy1				:31;
		} stBit;
	} unHBECSTCLR;										/* OFFSET 0x0008 - 0x000C */

	U1	u1Dummy1[0x0010U - 0x000CU];					/* OFFSET 0x000C - 0x0010 */

	union												/* HBEC1STERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xSEDF0					:1;				/* SEDF0 */
			U4	xDEDF0					:1;				/* DEDF0 */
			U4	b4Dummy1				:4;
			U4	xAECSEDF0				:1;				/* AECSEDF0 */
			U4	xAECDEDF0				:1;				/* AECDEDF0 */
			U4	b24Dummy2				:24;
		} stBit;
	} unHBEC1STERSTR;									/* OFFSET 0x0010 - 0x0014 */

	U1	u1Dummy2[0x0150U - 0x0014U];					/* OFFSET 0x0014 - 0x0150 */

	union												/* HBECTSTCTL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDummy1					:1;
			U4	xECCTST					:1;				/* ECCTST */
			U4	b30Dummy2				:30;
		} stBit;
	} unHBECTSTCTL;										/* OFFSET 0x0150 - 0x0154 */

	union												/* HBECTSTDIN0 */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
	} unHBECTSTDIN0;									/* OFFSET 0x0154 - 0x0158 */

	union												/* HBECTSTEIN */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b7ECC					:7;				/* ECC[6:0] */
			U4	b25Dummy1				:25;
		} stBit;
	} unHBECTSTEIN;										/* OFFSET 0x0158 - 0x015C */

	union												/* HBECKCPROT */
	{
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xKCE					:1;				/* KCE */
			U4	b31KCPROT				:31;			/* KCPROT[31:1] */
		} stBit;
	} unHBECKCPROT;										/* OFFSET 0x015C - 0x0160 */

}	Reg_Ecc_HbnEccType;


/* BECCCAP_V2An */
/* ============================================================================ */
/* ============================ Module: BECCCAP_V2An ========================== */
/* ============================================================================ */
typedef	struct											/* BECCCAP_V2An */
{
	union												/* PHC_BUSERRINT */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDSEDIE					:1;				/* DSEDIE */
			U4	xDDEDIE					:1;				/* DDEDIE */
			U4	xASEDIE					:1;				/* ASEDIE */
			U4	xADEDIE					:1;				/* ADEDIE */
			U4	b28Dummy1				:28;
		} stBit;
	} unPHC_BUSERRINT;									/* OFFSET 0x00 - 0x04 */

	U1	u1Dummy1[0x10U - 0x04U];						/* OFFSET 0x04 - 0x10 */

	union												/* PHC_BUSASSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xASSTCLR00				:1;				/* ASSTCLR00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unPHC_BUSASSTCLR;									/* OFFSET 0x10 - 0x14 */

	U1	u1Dummy2[0x20U - 0x14U];						/* OFFSET 0x14 - 0x20 */

	union												/* PHC_BUSADSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xADSTCLR00				:1;				/* ADSTCLR00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unPHC_BUSADSTCLR;									/* OFFSET 0x20 - 0x24 */

	U1	u1Dummy3[0x30U - 0x24U];						/* OFFSET 0x24 - 0x30 */

	union												/* PHC_BUSDSSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDSSTCLR00				:1;				/* DSSTCLR00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unPHC_BUSDSSTCLR;									/* OFFSET 0x30 - 0x34 */

	U1	u1Dummy4[0x40U - 0x34U];						/* OFFSET 0x34 - 0x40 */

	union												/* PHC_BUSDDSTCLR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDDSTCLR00				:1;				/* DDSTCLR00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unPHC_BUSDDSTCLR;									/* OFFSET 0x40 - 0x44 */

	U1	u1Dummy5[0x50U - 0x44U];						/* OFFSET 0x44 - 0x50 */

	union												/* PHC_BUSASERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xASEDF00				:1;				/* ASEDF00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unPHC_BUSASERSTR;									/* OFFSET 0x50 - 0x54 */

	U1	u1Dummy6[0x60U - 0x54U];						/* OFFSET 0x54 - 0x60 */

	union												/* PHC_BUSADERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xADEDF00				:1;				/* ADEDF00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unPHC_BUSADERSTR;									/* OFFSET 0x60 - 0x64 */

	U1	u1Dummy7[0x70U - 0x64U];						/* OFFSET 0x64 - 0x70 */

	union												/* PHC_BUSDSERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDSEDF00				:1;				/* DSEDF00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unPHC_BUSDSERSTR;									/* OFFSET 0x70 - 0x74 */

	U1	u1Dummy8[0x80U - 0x74U];						/* OFFSET 0x74 - 0x80 */

	union												/* PHC_BUSDDERSTR */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	xDDEDF00				:1;				/* DDEDF00 */
			U4	b31Dummy1				:31;
		} stBit;
	} unPHC_BUSDDERSTR;									/* OFFSET 0x80 - 0x84 */

}	Reg_Ecc_BeccCap_V2AnType;


/* ERRGEN */
/* ============================================================================ */
/* ============================ Module: ERRGEN ================================ */
/* ============================================================================ */
typedef	struct											/* ERRGEN */
{
	union												/* EGDATORG0 */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
	} unEGDATORG0;										/* 0xFFC58400 - 0xFFC58404 */

	union												/* EGDATORG1 */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
	} unEGDATORG1;										/* 0xFFC58404 - 0xFFC58408 */

	union												/* EGECCCAL0 */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b7ECCCAL				:7;				/* ECCCAL[6:0] */
			U4	b25Dummy1				:25;
		} stBit;
	} unEGECCCAL0;										/* 0xFFC58408 - 0xFFC5840C */

	union												/* EGECCCAL1 */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b7ECCCAL				:7;				/* ECCCAL[6:0] */
			U4	b25Dummy1				:25;
		} stBit;
	} unEGECCCAL1;										/* 0xFFC5840C - 0xFFC58410 */

	union												/* EGDATINV0 */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
	} unEGDATINV0;										/* 0xFFC58410 - 0xFFC58414 */

	union												/* EGDATINV1 */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
	} unEGDATINV1;										/* 0xFFC58414 - 0xFFC58418 */

	union												/* EGECCINV0 */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b7ECCINV				:7;				/* ECCINV[6:0] */
			U4	b25Dummy1				:25;
		} stBit;
	} unEGECCINV0;										/* 0xFFC58418 - 0xFFC5841C */

	union												/* EGECCINV1 */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct											/* Bit Access	*/
		{
			U4	b7ECCINV				:7;				/* ECCINV[6:0] */
			U4	b25Dummy1				:25;
		} stBit;
	} unEGECCINV1;										/* 0xFFC5841C - 0xFFC58420 */

	union												/* EGECC8CAL */
	{
		U1	u1Data[4];									/* 8-bit  Access */
		U2	u2Data[2];									/* 16-bit Access */
		U4	u4Data;										/* 32-bit Access */
		struct
		{
			U4	b8ECC8CAL				:8;				/* ECC8CAL[7:0] */
			U4	b24Dummy1				:24;
		} stBit;
	} unEGECC8CAL;										/* 0xFFC58420 - 0xFFC58424 */

}	Reg_Ecc_ErrgenType;


/*----------------------------------------------------------------------------------------------*/
/*	register BIT definition																		*/
/*----------------------------------------------------------------------------------------------*/
/* Key Code Protection for ECC Control Registers */
/* Module: ECCKC */
/* KCPROT */
#define		ECC_ECCKC_KCPROT_KCPROT							(0xFFFFFFFEU)
#define		ECC_ECCKC_KCPROT_KCPROT_0						(BIT1)
#define		ECC_ECCKC_KCPROT_KCE							(BIT0)
	#define		ECC_ECCDF_KCPROT_KCE_DISABLE				(0xA5A5A500U)
	#define		ECC_ECCDF_KCPROT_KCE_ENABLE					(0xA5A5A501U)

/* Code Flash ECC and Address Parity */
/* Module: ECCCNT_CFP_PE0CL0 */
/* CFPECCCTL */
#define		ECC_ECCCNT_CFP_PE0CL0_ECCCTL_SECDIS				(BIT1)
#define		ECC_ECCCNT_CFP_PE0CL0_ECCCTL_ECCDIS				(BIT0)
	#define		ECC_ECCCNT_CFP_PE0CL0_ECCCTL_ENABLE			(0)
	#define		ECC_ECCCNT_CFP_PE0CL0_ECCCTL_DISABLE		(1)
	
/* Module: ECCCNT_CFP_PE1CL0 */
/* CFPECCCTL */
#define		ECC_ECCCNT_CFP_PE1CL0_ECCCTL_SECDIS				(BIT1)
#define		ECC_ECCCNT_CFP_PE1CL0_ECCCTL_ECCDIS				(BIT0)
	#define		ECC_ECCCNT_CFP_PE1CL0_ECCCTL_ENABLE			(0)
	#define		ECC_ECCCNT_CFP_PE1CL0_ECCCTL_DISABLE		(1)

/* Module: ECCCNT_CFP_PE2CL1 */
/* CFPECCCTL */
#define		ECC_ECCCNT_CFP_PE2CL1_ECCCTL_SECDIS				(BIT1)
#define		ECC_ECCCNT_CFP_PE2CL1_ECCCTL_ECCDIS				(BIT0)
	#define		ECC_ECCCNT_CFP_PE2CL1_ECCCTL_ENABLE			(0)
	#define		ECC_ECCCNT_CFP_PE2CL1_ECCCTL_DISABLE		(1)

/* Module: ECCCNT_CFP_PE3CL1 */
/* CFPECCCTL */
#define		ECC_ECCCNT_CFP_PE3CL1_ECCCTL_SECDIS				(BIT1)
#define		ECC_ECCCNT_CFP_PE3CL1_ECCCTL_ECCDIS				(BIT0)
	#define		ECC_ECCCNT_CFP_PE3CL1_ECCCTL_ENABLE			(0)
	#define		ECC_ECCCNT_CFP_PE3CL1_ECCCTL_DISABLE		(1)

/* Module: ECCCNT_CFP_PE4CL2 */
/* CFPECCCTL */
#define		ECC_ECCCNT_CFP_PE4CL2_ECCCTL_SECDIS				(BIT1)
#define		ECC_ECCCNT_CFP_PE4CL2_ECCCTL_ECCDIS				(BIT0)
	#define		ECC_ECCCNT_CFP_PE4CL2_ECCCTL_ENABLE			(0)
	#define		ECC_ECCCNT_CFP_PE4CL2_ECCCTL_DISABLE		(1)

/* Module: ECCCNT_CFP_PE5CL2 */
/* CFPECCCTL */
#define		ECC_ECCCNT_CFP_PE5CL2_ECCCTL_SECDIS				(BIT1)
#define		ECC_ECCCNT_CFP_PE5CL2_ECCCTL_ECCDIS				(BIT0)
	#define		ECC_ECCCNT_CFP_PE5CL2_ECCCTL_ENABLE			(0)
	#define		ECC_ECCCNT_CFP_PE5CL2_ECCCTL_DISABLE		(1)

/* Module: ECCCNT_CFCCL0 */
/* CFCECCCTL */
#define		ECC_ECCCNT_CFCCL0_CFCECCCTL_BLANKMASKENABLE		(BIT24)
#define		ECC_ECCCNT_CFCCL0_CFCECCCTL_APEDIS				(BIT2)
#define		ECC_ECCCNT_CFCCL0_CFCECCCTL_SECDIS				(BIT1)
#define		ECC_ECCCNT_CFCCL0_CFCECCCTL_ECCDIS				(BIT0)
	#define		ECC_ECCCNT_CFCCL0_CFCECCCTL_ENABLE			(0)
	#define		ECC_ECCCNT_CFCCL0_CFCECCCTL_DISABLE			(1)

/* Module: ECCCNT_CFCCL1 */
/* CFCECCCTL */
#define		ECC_ECCCNT_CFCCL1_CFCECCCTL_BLANKMASKENABLE		(BIT24)
#define		ECC_ECCCNT_CFCCL1_CFCECCCTL_APEDIS				(BIT2)
#define		ECC_ECCCNT_CFCCL1_CFCECCCTL_SECDIS				(BIT1)
#define		ECC_ECCCNT_CFCCL1_CFCECCCTL_ECCDIS				(BIT0)
	#define		ECC_ECCCNT_CFCCL1_CFCECCCTL_ENABLE			(0)
	#define		ECC_ECCCNT_CFCCL1_CFCECCCTL_DISABLE			(1)

/* Module: ECCCNT_CFCCL2 */
/* CFCECCCTL */
#define		ECC_ECCCNT_CFCCL2_CFCECCCTL_BLANKMASKENABLE		(BIT24)
#define		ECC_ECCCNT_CFCCL2_CFCECCCTL_APEDIS				(BIT2)
#define		ECC_ECCCNT_CFCCL2_CFCECCCTL_SECDIS				(BIT1)
#define		ECC_ECCCNT_CFCCL2_CFCECCCTL_ECCDIS				(BIT0)
	#define		ECC_ECCCNT_CFCCL2_CFCECCCTL_ENABLE			(0)
	#define		ECC_ECCCNT_CFCCL2_CFCECCCTL_DISABLE			(1)

/* Module: ECCCNT_CFS */
/* CFSECCCTL */
#define		ECC_ECCCNT_CFS_CFSECCCTL_SECDIS					(BIT1)
#define		ECC_ECCCNT_CFS_CFSECCCTL_ECCDIS					(BIT0)
	#define		ECC_ECCCNT_CFS_CFSECCCTL_DISABLE			(1)
	#define		ECC_ECCCNT_CFS_CFSECCCTL_ENABLE				(0)

/* Module: MECCCAP_CFL */
/* CF_ERRINT */
#define		ECC_MECCCAP_CFL_CF_ERRINT_SEOVFIE				(BIT7)
#define		ECC_MECCCAP_CFL_CF_ERRINT_APEIE					(BIT2)
#define		ECC_MECCCAP_CFL_CF_ERRINT_DEDIE					(BIT1)
#define		ECC_MECCCAP_CFL_CF_ERRINT_SEDIE					(BIT0)
	#define		ECC_MECCCAP_CFL_CF_ERRINT_DISABLE			(0)
	#define		ECC_MECCCAP_CFL_CF_ERRINT_ENABLE			(1)
/* CF_SSTCLR */
#define		ECC_MECCCAP_CFL_CF_SSTCLR_CLR15					(BIT15)
#define		ECC_MECCCAP_CFL_CF_SSTCLR_CLR14					(BIT14)
#define		ECC_MECCCAP_CFL_CF_SSTCLR_CLR13					(BIT13)
#define		ECC_MECCCAP_CFL_CF_SSTCLR_CLR12					(BIT12)
#define		ECC_MECCCAP_CFL_CF_SSTCLR_CLR11					(BIT11)
#define		ECC_MECCCAP_CFL_CF_SSTCLR_CLR10					(BIT10)
#define		ECC_MECCCAP_CFL_CF_SSTCLR_CLR09					(BIT9)
#define		ECC_MECCCAP_CFL_CF_SSTCLR_CLR08					(BIT8)
#define		ECC_MECCCAP_CFL_CF_SSTCLR_CLR07					(BIT7)
#define		ECC_MECCCAP_CFL_CF_SSTCLR_CLR06					(BIT6)
#define		ECC_MECCCAP_CFL_CF_SSTCLR_CLR05					(BIT5)
#define		ECC_MECCCAP_CFL_CF_SSTCLR_CLR04					(BIT4)
#define		ECC_MECCCAP_CFL_CF_SSTCLR_CLR03					(BIT3)
#define		ECC_MECCCAP_CFL_CF_SSTCLR_CLR02					(BIT2)
#define		ECC_MECCCAP_CFL_CF_SSTCLR_CLR01					(BIT1)
#define		ECC_MECCCAP_CFL_CF_SSTCLR_CLR00					(BIT0)
	#define		ECC_MECCCAP_CFL_CF_SSTCLR_CLEAR				(1)
/* CF_DSTCLR */
#define		ECC_MECCCAP_CFL_CF_DSTCLR_DSTCLR00				(BIT0)
	#define		ECC_MECCCAP_CFL_CF_DSTCLR_CLEAR				(1)
/* CF_OVFCLR */
#define		ECC_MECCCAP_CFL_CF_OVFCLR_CLR1					(BIT1)
#define		ECC_MECCCAP_CFL_CF_OVFCLR_CLR0					(BIT0)
	#define		ECC_MECCCAP_CFL_CF_OVFCLR_CLEAR				(1)
/* CF_SERSTR */
#define		ECC_MECCCAP_CFL_CF_SERSTR_SDF15					(BIT15)
#define		ECC_MECCCAP_CFL_CF_SERSTR_SDF14					(BIT14)
#define		ECC_MECCCAP_CFL_CF_SERSTR_SDF13					(BIT13)
#define		ECC_MECCCAP_CFL_CF_SERSTR_SDF12					(BIT12)
#define		ECC_MECCCAP_CFL_CF_SERSTR_SDF11					(BIT11)
#define		ECC_MECCCAP_CFL_CF_SERSTR_SDF10					(BIT10)
#define		ECC_MECCCAP_CFL_CF_SERSTR_SDF09					(BIT9)
#define		ECC_MECCCAP_CFL_CF_SERSTR_SDF08					(BIT8)
#define		ECC_MECCCAP_CFL_CF_SERSTR_SDF07					(BIT7)
#define		ECC_MECCCAP_CFL_CF_SERSTR_SDF06					(BIT6)
#define		ECC_MECCCAP_CFL_CF_SERSTR_SDF05					(BIT5)
#define		ECC_MECCCAP_CFL_CF_SERSTR_SDF04					(BIT4)
#define		ECC_MECCCAP_CFL_CF_SERSTR_SDF03					(BIT3)
#define		ECC_MECCCAP_CFL_CF_SERSTR_SDF02					(BIT2)
#define		ECC_MECCCAP_CFL_CF_SERSTR_SDF01					(BIT1)
#define		ECC_MECCCAP_CFL_CF_SERSTR_SDF00					(BIT0)
/* CF_DERSTR */
#define		ECC_MECCCAP_CFL_CF_DERSTR_APEF00				(BIT2)
#define		ECC_MECCCAP_CFL_CF_DERSTR_DEDF00				(BIT1)
/* CF_OVFSTR */
#define		ECC_MECCCAP_CFL_CF_OVFSTR_OVF1					(BIT1)
#define		ECC_MECCCAP_CFL_CF_OVFSTR_OVF0					(BIT0)
/* CF_SERINF */
#define		ECC_MECCCAP_CFL_CF_SERINF_INF17					(BIT17)
#define		ECC_MECCCAP_CFL_CF_SERINF_INF16					(BIT16)
#define		ECC_MECCCAP_CFL_CF_SERINF_INF11					(BIT11)
#define		ECC_MECCCAP_CFL_CF_SERINF_INF10					(BIT10)
#define		ECC_MECCCAP_CFL_CF_SERINF_INF09					(BIT9)
#define		ECC_MECCCAP_CFL_CF_SERINF_INF08					(BIT8)
#define		ECC_MECCCAP_CFL_CF_SERINF_INF07					(BIT7)
#define		ECC_MECCCAP_CFL_CF_SERINF_INF06					(BIT6)
#define		ECC_MECCCAP_CFL_CF_SERINF_INF05					(BIT5)
#define		ECC_MECCCAP_CFL_CF_SERINF_INF04					(BIT4)
#define		ECC_MECCCAP_CFL_CF_SERINF_INF03					(BIT3)
#define		ECC_MECCCAP_CFL_CF_SERINF_INF02					(BIT2)
#define		ECC_MECCCAP_CFL_CF_SERINF_INF01					(BIT1)
#define		ECC_MECCCAP_CFL_CF_SERINF_INF00					(BIT0)
/* CF_nSEADR */
#define		ECC_MECCCAP_CFL_CF_SEADR_SEDL					(BIT31 + BIT30 + BIT29 + BIT28 + BIT27)
#define		ECC_MECCCAP_CFL_CF_SEADR_SEADR0					(0x03FFFFFCU)
/* CF_00DEADR */
#define		ECC_MECCCAP_CFL_CF_00DEADR_DEDL					(BIT31 + BIT30 + BIT29 + BIT28 + BIT27)
#define		ECC_MECCCAP_CFL_CF_00DEADR_DEADR0				(0x03FFFFFCU)
/* CF_00DESPIDCLR */
#define		ECC_MECCCAP_CFL_CF_DESPIDCLR_31					(BIT31)
#define		ECC_MECCCAP_CFL_CF_DESPIDCLR_30					(BIT30)
#define		ECC_MECCCAP_CFL_CF_DESPIDCLR_29					(BIT29)
#define		ECC_MECCCAP_CFL_CF_DESPIDCLR_28					(BIT28)
#define		ECC_MECCCAP_CFL_CF_DESPIDCLR_27					(BIT27)
#define		ECC_MECCCAP_CFL_CF_DESPIDCLR_26					(BIT26)
#define		ECC_MECCCAP_CFL_CF_DESPIDCLR_25					(BIT25)
#define		ECC_MECCCAP_CFL_CF_DESPIDCLR_24					(BIT24)
#define		ECC_MECCCAP_CFL_CF_DESPIDCLR_23					(BIT23)
#define		ECC_MECCCAP_CFL_CF_DESPIDCLR_22					(BIT22)
#define		ECC_MECCCAP_CFL_CF_DESPIDCLR_21					(BIT21)
#define		ECC_MECCCAP_CFL_CF_DESPIDCLR_20					(BIT20)
#define		ECC_MECCCAP_CFL_CF_DESPIDCLR_19					(BIT19)
#define		ECC_MECCCAP_CFL_CF_DESPIDCLR_18					(BIT18)
#define		ECC_MECCCAP_CFL_CF_DESPIDCLR_17					(BIT17)
#define		ECC_MECCCAP_CFL_CF_DESPIDCLR_16					(BIT16)
#define		ECC_MECCCAP_CFL_CF_DESPIDCLR_15					(BIT15)
#define		ECC_MECCCAP_CFL_CF_DESPIDCLR_14					(BIT14)
#define		ECC_MECCCAP_CFL_CF_DESPIDCLR_13					(BIT13)
#define		ECC_MECCCAP_CFL_CF_DESPIDCLR_12					(BIT12)
#define		ECC_MECCCAP_CFL_CF_DESPIDCLR_11					(BIT11)
#define		ECC_MECCCAP_CFL_CF_DESPIDCLR_10					(BIT10)
#define		ECC_MECCCAP_CFL_CF_DESPIDCLR_9					(BIT9)
#define		ECC_MECCCAP_CFL_CF_DESPIDCLR_8					(BIT8)
#define		ECC_MECCCAP_CFL_CF_DESPIDCLR_7					(BIT7)
#define		ECC_MECCCAP_CFL_CF_DESPIDCLR_6					(BIT6)
#define		ECC_MECCCAP_CFL_CF_DESPIDCLR_5					(BIT5)
#define		ECC_MECCCAP_CFL_CF_DESPIDCLR_4					(BIT4)
#define		ECC_MECCCAP_CFL_CF_DESPIDCLR_3					(BIT3)
#define		ECC_MECCCAP_CFL_CF_DESPIDCLR_2					(BIT2)
#define		ECC_MECCCAP_CFL_CF_DESPIDCLR_1					(BIT1)
#define		ECC_MECCCAP_CFL_CF_DESPIDCLR_0					(BIT0)
	#define	   ECC_MECCCAP_CFL_CF_00DESPIDCLR_CLEAR			(1)
/* CF_00DESPID */
#define		ECC_MECCCAP_CFL_CF_00DESPID_31					(BIT31)
#define		ECC_MECCCAP_CFL_CF_00DESPID_30					(BIT30)
#define		ECC_MECCCAP_CFL_CF_00DESPID_29					(BIT29)
#define		ECC_MECCCAP_CFL_CF_00DESPID_28					(BIT28)
#define		ECC_MECCCAP_CFL_CF_00DESPID_27					(BIT27)
#define		ECC_MECCCAP_CFL_CF_00DESPID_26					(BIT26)
#define		ECC_MECCCAP_CFL_CF_00DESPID_25					(BIT25)
#define		ECC_MECCCAP_CFL_CF_00DESPID_24					(BIT24)
#define		ECC_MECCCAP_CFL_CF_00DESPID_23					(BIT23)
#define		ECC_MECCCAP_CFL_CF_00DESPID_22					(BIT22)
#define		ECC_MECCCAP_CFL_CF_00DESPID_21					(BIT21)
#define		ECC_MECCCAP_CFL_CF_00DESPID_20					(BIT20)
#define		ECC_MECCCAP_CFL_CF_00DESPID_19					(BIT19)
#define		ECC_MECCCAP_CFL_CF_00DESPID_18					(BIT18)
#define		ECC_MECCCAP_CFL_CF_00DESPID_17					(BIT17)
#define		ECC_MECCCAP_CFL_CF_00DESPID_16					(BIT16)
#define		ECC_MECCCAP_CFL_CF_00DESPID_15					(BIT15)
#define		ECC_MECCCAP_CFL_CF_00DESPID_14					(BIT14)
#define		ECC_MECCCAP_CFL_CF_00DESPID_13					(BIT13)
#define		ECC_MECCCAP_CFL_CF_00DESPID_12					(BIT12)
#define		ECC_MECCCAP_CFL_CF_00DESPID_11					(BIT11)
#define		ECC_MECCCAP_CFL_CF_00DESPID_10					(BIT10)
#define		ECC_MECCCAP_CFL_CF_00DESPID_9					(BIT9)
#define		ECC_MECCCAP_CFL_CF_00DESPID_8					(BIT8)
#define		ECC_MECCCAP_CFL_CF_00DESPID_7					(BIT7)
#define		ECC_MECCCAP_CFL_CF_00DESPID_6					(BIT6)
#define		ECC_MECCCAP_CFL_CF_00DESPID_5					(BIT5)
#define		ECC_MECCCAP_CFL_CF_00DESPID_4					(BIT4)
#define		ECC_MECCCAP_CFL_CF_00DESPID_3					(BIT3)
#define		ECC_MECCCAP_CFL_CF_00DESPID_2					(BIT2)
#define		ECC_MECCCAP_CFL_CF_00DESPID_1					(BIT1)
#define		ECC_MECCCAP_CFL_CF_00DESPID_0					(BIT0)
/* CF_00SESPIDCLR */
#define		ECC_MECCCAP_CFL_CF_SESPIDCLR_31					(BIT31)
#define		ECC_MECCCAP_CFL_CF_SESPIDCLR_30					(BIT30)
#define		ECC_MECCCAP_CFL_CF_SESPIDCLR_29					(BIT29)
#define		ECC_MECCCAP_CFL_CF_SESPIDCLR_28					(BIT28)
#define		ECC_MECCCAP_CFL_CF_SESPIDCLR_27					(BIT27)
#define		ECC_MECCCAP_CFL_CF_SESPIDCLR_26					(BIT26)
#define		ECC_MECCCAP_CFL_CF_SESPIDCLR_25					(BIT25)
#define		ECC_MECCCAP_CFL_CF_SESPIDCLR_24					(BIT24)
#define		ECC_MECCCAP_CFL_CF_SESPIDCLR_23					(BIT23)
#define		ECC_MECCCAP_CFL_CF_SESPIDCLR_22					(BIT22)
#define		ECC_MECCCAP_CFL_CF_SESPIDCLR_21					(BIT21)
#define		ECC_MECCCAP_CFL_CF_SESPIDCLR_20					(BIT20)
#define		ECC_MECCCAP_CFL_CF_SESPIDCLR_19					(BIT19)
#define		ECC_MECCCAP_CFL_CF_SESPIDCLR_18					(BIT18)
#define		ECC_MECCCAP_CFL_CF_SESPIDCLR_17					(BIT17)
#define		ECC_MECCCAP_CFL_CF_SESPIDCLR_16					(BIT16)
#define		ECC_MECCCAP_CFL_CF_SESPIDCLR_15					(BIT15)
#define		ECC_MECCCAP_CFL_CF_SESPIDCLR_14					(BIT14)
#define		ECC_MECCCAP_CFL_CF_SESPIDCLR_13					(BIT13)
#define		ECC_MECCCAP_CFL_CF_SESPIDCLR_12					(BIT12)
#define		ECC_MECCCAP_CFL_CF_SESPIDCLR_11					(BIT11)
#define		ECC_MECCCAP_CFL_CF_SESPIDCLR_10					(BIT10)
#define		ECC_MECCCAP_CFL_CF_SESPIDCLR_9					(BIT9)
#define		ECC_MECCCAP_CFL_CF_SESPIDCLR_8					(BIT8)
#define		ECC_MECCCAP_CFL_CF_SESPIDCLR_7					(BIT7)
#define		ECC_MECCCAP_CFL_CF_SESPIDCLR_6					(BIT6)
#define		ECC_MECCCAP_CFL_CF_SESPIDCLR_5					(BIT5)
#define		ECC_MECCCAP_CFL_CF_SESPIDCLR_4					(BIT4)
#define		ECC_MECCCAP_CFL_CF_SESPIDCLR_3					(BIT3)
#define		ECC_MECCCAP_CFL_CF_SESPIDCLR_2					(BIT2)
#define		ECC_MECCCAP_CFL_CF_SESPIDCLR_1					(BIT1)
#define		ECC_MECCCAP_CFL_CF_SESPIDCLR_0					(BIT0)
	#define	   ECC_MECCCAP_CFL_CF_00SESPIDCLR_CLEAR			(1)
/* CF_00SESPID */
#define		ECC_MECCCAP_CFL_CF_00SESPID_31					(BIT31)
#define		ECC_MECCCAP_CFL_CF_00SESPID_30					(BIT30)
#define		ECC_MECCCAP_CFL_CF_00SESPID_29					(BIT29)
#define		ECC_MECCCAP_CFL_CF_00SESPID_28					(BIT28)
#define		ECC_MECCCAP_CFL_CF_00SESPID_27					(BIT27)
#define		ECC_MECCCAP_CFL_CF_00SESPID_26					(BIT26)
#define		ECC_MECCCAP_CFL_CF_00SESPID_25					(BIT25)
#define		ECC_MECCCAP_CFL_CF_00SESPID_24					(BIT24)
#define		ECC_MECCCAP_CFL_CF_00SESPID_23					(BIT23)
#define		ECC_MECCCAP_CFL_CF_00SESPID_22					(BIT22)
#define		ECC_MECCCAP_CFL_CF_00SESPID_21					(BIT21)
#define		ECC_MECCCAP_CFL_CF_00SESPID_20					(BIT20)
#define		ECC_MECCCAP_CFL_CF_00SESPID_19					(BIT19)
#define		ECC_MECCCAP_CFL_CF_00SESPID_18					(BIT18)
#define		ECC_MECCCAP_CFL_CF_00SESPID_17					(BIT17)
#define		ECC_MECCCAP_CFL_CF_00SESPID_16					(BIT16)
#define		ECC_MECCCAP_CFL_CF_00SESPID_15					(BIT15)
#define		ECC_MECCCAP_CFL_CF_00SESPID_14					(BIT14)
#define		ECC_MECCCAP_CFL_CF_00SESPID_13					(BIT13)
#define		ECC_MECCCAP_CFL_CF_00SESPID_12					(BIT12)
#define		ECC_MECCCAP_CFL_CF_00SESPID_11					(BIT11)
#define		ECC_MECCCAP_CFL_CF_00SESPID_10					(BIT10)
#define		ECC_MECCCAP_CFL_CF_00SESPID_9					(BIT9)
#define		ECC_MECCCAP_CFL_CF_00SESPID_8					(BIT8)
#define		ECC_MECCCAP_CFL_CF_00SESPID_7					(BIT7)
#define		ECC_MECCCAP_CFL_CF_00SESPID_6					(BIT6)
#define		ECC_MECCCAP_CFL_CF_00SESPID_5					(BIT5)
#define		ECC_MECCCAP_CFL_CF_00SESPID_4					(BIT4)
#define		ECC_MECCCAP_CFL_CF_00SESPID_3					(BIT3)
#define		ECC_MECCCAP_CFL_CF_00SESPID_2					(BIT2)
#define		ECC_MECCCAP_CFL_CF_00SESPID_1					(BIT1)
#define		ECC_MECCCAP_CFL_CF_00SESPID_0					(BIT0)


/* Data Flash ECC */
/* Module: ECCDF */
/* DFECCCTL */
#define		ECC_ECCDF_DFECCCTL_SECDIS						(BIT1)
#define		ECC_ECCDF_DFECCCTL_ECCDIS						(BIT0)
	#define		ECC_ECCDF_DFECCCTL_DISABLE					(1)
	#define		ECC_ECCDF_DFECCCTL_ENABLE					(0)
/* DFSERSTR */
#define		ECC_ECCDF_DFSERSTR_SEDF3						(BIT3)
#define		ECC_ECCDF_DFSERSTR_SEDF2						(BIT2)
#define		ECC_ECCDF_DFSERSTR_SEDF1						(BIT1)
#define		ECC_ECCDF_DFSERSTR_SEDF0						(BIT0)
/* DFDERSTR */
#define		ECC_ECCDF_DFDERSTR_DEDF							(BIT0)
/* DFSERSTC */
#define		ECC_ECCDF_DFSERSTC_SSTCLR3						(BIT3)
#define		ECC_ECCDF_DFSERSTC_SSTCLR2						(BIT2)
#define		ECC_ECCDF_DFSERSTC_SSTCLR1						(BIT1)
#define		ECC_ECCDF_DFSERSTC_SSTCLR0						(BIT0)
	#define		ECC_ECCDF_DFSERSTC_SSTCLR_NOEFFECT			(0)
	#define		ECC_ECCDF_DFSERSTC_SSTCLR_CLEAR				(1)
/* DFDERSTC */
#define		ECC_ECCDF_DFDERSTC_DSTCLR						(BIT0)
	#define		ECC_ECCDF_DFDERSTC_DSTCLR_NOEFFECT			(0)
	#define		ECC_ECCDF_DFDERSTC_DSTCLR_CLEAR				(1)
/* DFOVFSTR */
#define		ECC_ECCDF_DFOVFSTR_ERROVF						(BIT0)
/* DFOVFSTC */
#define		ECC_ECCDF_DFOVFSTC_ERROVFCLR					(BIT0)
	#define		ECC_ECCDF_DFOVFSTC_ERROVFCLR_NOEFFECT		(0)
	#define		ECC_ECCDF_DFOVFSTC_ERROVFCLR_CLEAR			(1)
/* DFERRINT */
#define		ECC_ECCDF_DFERRINT_SEOVFIE						(BIT2)
#define		ECC_ECCDF_DFERRINT_DEDIE						(BIT1)
#define		ECC_ECCDF_DFERRINT_SEDIE						(BIT0)
	#define		ECC_ECCDF_DFERRINT_DISABLE					(0)
	#define		ECC_ECCDF_DFERRINT_ENABLE					(1)
/* DFSEADR */
#define		ECC_ECCDF_DFSEADR_DFSEADR						(0x001FFFFCU)
#define		ECC_ECCDF_DFSEADR_DFSEADR_0						(BIT2)
/* DFDEADR */
#define		ECC_ECCDF_DFDEADR_DFDEADR						(0x001FFFFCU)
#define		ECC_ECCDF_DFDEADR_DFDEADR_0						(BIT2)
/* DFSESPID0 */
#define		ECC_ECCDF_DFSESPID0_DSESPID31					(BIT31)
#define		ECC_ECCDF_DFSESPID0_DSESPID30					(BIT30)
#define		ECC_ECCDF_DFSESPID0_DSESPID29					(BIT29)
#define		ECC_ECCDF_DFSESPID0_DSESPID28					(BIT28)
#define		ECC_ECCDF_DFSESPID0_DSESPID27					(BIT27)
#define		ECC_ECCDF_DFSESPID0_DSESPID26					(BIT26)
#define		ECC_ECCDF_DFSESPID0_DSESPID25					(BIT25)
#define		ECC_ECCDF_DFSESPID0_DSESPID24					(BIT24)
#define		ECC_ECCDF_DFSESPID0_DSESPID23					(BIT23)
#define		ECC_ECCDF_DFSESPID0_DSESPID22					(BIT22)
#define		ECC_ECCDF_DFSESPID0_DSESPID21					(BIT21)
#define		ECC_ECCDF_DFSESPID0_DSESPID20					(BIT20)
#define		ECC_ECCDF_DFSESPID0_DSESPID19					(BIT19)
#define		ECC_ECCDF_DFSESPID0_DSESPID18					(BIT18)
#define		ECC_ECCDF_DFSESPID0_DSESPID17					(BIT17)
#define		ECC_ECCDF_DFSESPID0_DSESPID16					(BIT16)
#define		ECC_ECCDF_DFSESPID0_DSESPID15					(BIT15)
#define		ECC_ECCDF_DFSESPID0_DSESPID14					(BIT14)
#define		ECC_ECCDF_DFSESPID0_DSESPID13					(BIT13)
#define		ECC_ECCDF_DFSESPID0_DSESPID12					(BIT12)
#define		ECC_ECCDF_DFSESPID0_DSESPID11					(BIT11)
#define		ECC_ECCDF_DFSESPID0_DSESPID10					(BIT10)
#define		ECC_ECCDF_DFSESPID0_DSESPID9					(BIT9)
#define		ECC_ECCDF_DFSESPID0_DSESPID8					(BIT8)
#define		ECC_ECCDF_DFSESPID0_DSESPID7					(BIT7)
#define		ECC_ECCDF_DFSESPID0_DSESPID6					(BIT6)
#define		ECC_ECCDF_DFSESPID0_DSESPID5					(BIT5)
#define		ECC_ECCDF_DFSESPID0_DSESPID4					(BIT4)
#define		ECC_ECCDF_DFSESPID0_DSESPID3					(BIT3)
#define		ECC_ECCDF_DFSESPID0_DSESPID2					(BIT2)
#define		ECC_ECCDF_DFSESPID0_DSESPID1					(BIT1)
#define		ECC_ECCDF_DFSESPID0_DSESPID0					(BIT0)
/* DFSESPIDC0 */
#define		ECC_ECCDF_DFSESPIDC0_31							(BIT31)
#define		ECC_ECCDF_DFSESPIDC0_30							(BIT30)
#define		ECC_ECCDF_DFSESPIDC0_29							(BIT29)
#define		ECC_ECCDF_DFSESPIDC0_28							(BIT28)
#define		ECC_ECCDF_DFSESPIDC0_27							(BIT27)
#define		ECC_ECCDF_DFSESPIDC0_26							(BIT26)
#define		ECC_ECCDF_DFSESPIDC0_25							(BIT25)
#define		ECC_ECCDF_DFSESPIDC0_24							(BIT24)
#define		ECC_ECCDF_DFSESPIDC0_23							(BIT23)
#define		ECC_ECCDF_DFSESPIDC0_22							(BIT22)
#define		ECC_ECCDF_DFSESPIDC0_21							(BIT21)
#define		ECC_ECCDF_DFSESPIDC0_20							(BIT20)
#define		ECC_ECCDF_DFSESPIDC0_19							(BIT19)
#define		ECC_ECCDF_DFSESPIDC0_18							(BIT18)
#define		ECC_ECCDF_DFSESPIDC0_17							(BIT17)
#define		ECC_ECCDF_DFSESPIDC0_16							(BIT16)
#define		ECC_ECCDF_DFSESPIDC0_15							(BIT15)
#define		ECC_ECCDF_DFSESPIDC0_14							(BIT14)
#define		ECC_ECCDF_DFSESPIDC0_13							(BIT13)
#define		ECC_ECCDF_DFSESPIDC0_12							(BIT12)
#define		ECC_ECCDF_DFSESPIDC0_11							(BIT11)
#define		ECC_ECCDF_DFSESPIDC0_10							(BIT10)
#define		ECC_ECCDF_DFSESPIDC0_9							(BIT9)
#define		ECC_ECCDF_DFSESPIDC0_8							(BIT8)
#define		ECC_ECCDF_DFSESPIDC0_7							(BIT7)
#define		ECC_ECCDF_DFSESPIDC0_6							(BIT6)
#define		ECC_ECCDF_DFSESPIDC0_5							(BIT5)
#define		ECC_ECCDF_DFSESPIDC0_4							(BIT4)
#define		ECC_ECCDF_DFSESPIDC0_3							(BIT3)
#define		ECC_ECCDF_DFSESPIDC0_2							(BIT2)
#define		ECC_ECCDF_DFSESPIDC0_1							(BIT1)
#define		ECC_ECCDF_DFSESPIDC0_0							(BIT0)
	#define	   ECC_ECCDF_DFSESPIDC0_CLEAR					(1)
/* DFSESPID1 */
#define		ECC_ECCDF_DFSESPID1_31							(BIT31)
#define		ECC_ECCDF_DFSESPID1_30							(BIT30)
#define		ECC_ECCDF_DFSESPID1_29							(BIT29)
#define		ECC_ECCDF_DFSESPID1_28							(BIT28)
#define		ECC_ECCDF_DFSESPID1_27							(BIT27)
#define		ECC_ECCDF_DFSESPID1_26							(BIT26)
#define		ECC_ECCDF_DFSESPID1_25							(BIT25)
#define		ECC_ECCDF_DFSESPID1_24							(BIT24)
#define		ECC_ECCDF_DFSESPID1_23							(BIT23)
#define		ECC_ECCDF_DFSESPID1_22							(BIT22)
#define		ECC_ECCDF_DFSESPID1_21							(BIT21)
#define		ECC_ECCDF_DFSESPID1_20							(BIT20)
#define		ECC_ECCDF_DFSESPID1_19							(BIT19)
#define		ECC_ECCDF_DFSESPID1_18							(BIT18)
#define		ECC_ECCDF_DFSESPID1_17							(BIT17)
#define		ECC_ECCDF_DFSESPID1_16							(BIT16)
#define		ECC_ECCDF_DFSESPID1_15							(BIT15)
#define		ECC_ECCDF_DFSESPID1_14							(BIT14)
#define		ECC_ECCDF_DFSESPID1_13							(BIT13)
#define		ECC_ECCDF_DFSESPID1_12							(BIT12)
#define		ECC_ECCDF_DFSESPID1_11							(BIT11)
#define		ECC_ECCDF_DFSESPID1_10							(BIT10)
#define		ECC_ECCDF_DFSESPID1_9							(BIT9)
#define		ECC_ECCDF_DFSESPID1_8							(BIT8)
#define		ECC_ECCDF_DFSESPID1_7							(BIT7)
#define		ECC_ECCDF_DFSESPID1_6							(BIT6)
#define		ECC_ECCDF_DFSESPID1_5							(BIT5)
#define		ECC_ECCDF_DFSESPID1_4							(BIT4)
#define		ECC_ECCDF_DFSESPID1_3							(BIT3)
#define		ECC_ECCDF_DFSESPID1_2							(BIT2)
#define		ECC_ECCDF_DFSESPID1_1							(BIT1)
#define		ECC_ECCDF_DFSESPID1_0							(BIT0)
/* DFSESPIDC1 */
#define		ECC_ECCDF_DFSESPIDC1_31							(BIT31)
#define		ECC_ECCDF_DFSESPIDC1_30							(BIT30)
#define		ECC_ECCDF_DFSESPIDC1_29							(BIT29)
#define		ECC_ECCDF_DFSESPIDC1_28							(BIT28)
#define		ECC_ECCDF_DFSESPIDC1_27							(BIT27)
#define		ECC_ECCDF_DFSESPIDC1_26							(BIT26)
#define		ECC_ECCDF_DFSESPIDC1_25							(BIT25)
#define		ECC_ECCDF_DFSESPIDC1_24							(BIT24)
#define		ECC_ECCDF_DFSESPIDC1_23							(BIT23)
#define		ECC_ECCDF_DFSESPIDC1_22							(BIT22)
#define		ECC_ECCDF_DFSESPIDC1_21							(BIT21)
#define		ECC_ECCDF_DFSESPIDC1_20							(BIT20)
#define		ECC_ECCDF_DFSESPIDC1_19							(BIT19)
#define		ECC_ECCDF_DFSESPIDC1_18							(BIT18)
#define		ECC_ECCDF_DFSESPIDC1_17							(BIT17)
#define		ECC_ECCDF_DFSESPIDC1_16							(BIT16)
#define		ECC_ECCDF_DFSESPIDC1_15							(BIT15)
#define		ECC_ECCDF_DFSESPIDC1_14							(BIT14)
#define		ECC_ECCDF_DFSESPIDC1_13							(BIT13)
#define		ECC_ECCDF_DFSESPIDC1_12							(BIT12)
#define		ECC_ECCDF_DFSESPIDC1_11							(BIT11)
#define		ECC_ECCDF_DFSESPIDC1_10							(BIT10)
#define		ECC_ECCDF_DFSESPIDC1_9							(BIT9)
#define		ECC_ECCDF_DFSESPIDC1_8							(BIT8)
#define		ECC_ECCDF_DFSESPIDC1_7							(BIT7)
#define		ECC_ECCDF_DFSESPIDC1_6							(BIT6)
#define		ECC_ECCDF_DFSESPIDC1_5							(BIT5)
#define		ECC_ECCDF_DFSESPIDC1_4							(BIT4)
#define		ECC_ECCDF_DFSESPIDC1_3							(BIT3)
#define		ECC_ECCDF_DFSESPIDC1_2							(BIT2)
#define		ECC_ECCDF_DFSESPIDC1_1							(BIT1)
#define		ECC_ECCDF_DFSESPIDC1_0							(BIT0)
	#define	   ECC_ECCDF_DFSESPIDC1_CLEAR					(1)
/* DFSESPID2 */
#define		ECC_ECCDF_DFSESPID2_31							(BIT31)
#define		ECC_ECCDF_DFSESPID2_30							(BIT30)
#define		ECC_ECCDF_DFSESPID2_29							(BIT29)
#define		ECC_ECCDF_DFSESPID2_28							(BIT28)
#define		ECC_ECCDF_DFSESPID2_27							(BIT27)
#define		ECC_ECCDF_DFSESPID2_26							(BIT26)
#define		ECC_ECCDF_DFSESPID2_25							(BIT25)
#define		ECC_ECCDF_DFSESPID2_24							(BIT24)
#define		ECC_ECCDF_DFSESPID2_23							(BIT23)
#define		ECC_ECCDF_DFSESPID2_22							(BIT22)
#define		ECC_ECCDF_DFSESPID2_21							(BIT21)
#define		ECC_ECCDF_DFSESPID2_20							(BIT20)
#define		ECC_ECCDF_DFSESPID2_19							(BIT19)
#define		ECC_ECCDF_DFSESPID2_18							(BIT18)
#define		ECC_ECCDF_DFSESPID2_17							(BIT17)
#define		ECC_ECCDF_DFSESPID2_16							(BIT16)
#define		ECC_ECCDF_DFSESPID2_15							(BIT15)
#define		ECC_ECCDF_DFSESPID2_14							(BIT14)
#define		ECC_ECCDF_DFSESPID2_13							(BIT13)
#define		ECC_ECCDF_DFSESPID2_12							(BIT12)
#define		ECC_ECCDF_DFSESPID2_11							(BIT11)
#define		ECC_ECCDF_DFSESPID2_10							(BIT10)
#define		ECC_ECCDF_DFSESPID2_9							(BIT9)
#define		ECC_ECCDF_DFSESPID2_8							(BIT8)
#define		ECC_ECCDF_DFSESPID2_7							(BIT7)
#define		ECC_ECCDF_DFSESPID2_6							(BIT6)
#define		ECC_ECCDF_DFSESPID2_5							(BIT5)
#define		ECC_ECCDF_DFSESPID2_4							(BIT4)
#define		ECC_ECCDF_DFSESPID2_3							(BIT3)
#define		ECC_ECCDF_DFSESPID2_2							(BIT2)
#define		ECC_ECCDF_DFSESPID2_1							(BIT1)
#define		ECC_ECCDF_DFSESPID2_0							(BIT0)
/* DFSESPIDC2 */
#define		ECC_ECCDF_DFSESPIDC2_31							(BIT31)
#define		ECC_ECCDF_DFSESPIDC2_30							(BIT30)
#define		ECC_ECCDF_DFSESPIDC2_29							(BIT29)
#define		ECC_ECCDF_DFSESPIDC2_28							(BIT28)
#define		ECC_ECCDF_DFSESPIDC2_27							(BIT27)
#define		ECC_ECCDF_DFSESPIDC2_26							(BIT26)
#define		ECC_ECCDF_DFSESPIDC2_25							(BIT25)
#define		ECC_ECCDF_DFSESPIDC2_24							(BIT24)
#define		ECC_ECCDF_DFSESPIDC2_23							(BIT23)
#define		ECC_ECCDF_DFSESPIDC2_22							(BIT22)
#define		ECC_ECCDF_DFSESPIDC2_21							(BIT21)
#define		ECC_ECCDF_DFSESPIDC2_20							(BIT20)
#define		ECC_ECCDF_DFSESPIDC2_19							(BIT19)
#define		ECC_ECCDF_DFSESPIDC2_18							(BIT18)
#define		ECC_ECCDF_DFSESPIDC2_17							(BIT17)
#define		ECC_ECCDF_DFSESPIDC2_16							(BIT16)
#define		ECC_ECCDF_DFSESPIDC2_15							(BIT15)
#define		ECC_ECCDF_DFSESPIDC2_14							(BIT14)
#define		ECC_ECCDF_DFSESPIDC2_13							(BIT13)
#define		ECC_ECCDF_DFSESPIDC2_12							(BIT12)
#define		ECC_ECCDF_DFSESPIDC2_11							(BIT11)
#define		ECC_ECCDF_DFSESPIDC2_10							(BIT10)
#define		ECC_ECCDF_DFSESPIDC2_9							(BIT9)
#define		ECC_ECCDF_DFSESPIDC2_8							(BIT8)
#define		ECC_ECCDF_DFSESPIDC2_7							(BIT7)
#define		ECC_ECCDF_DFSESPIDC2_6							(BIT6)
#define		ECC_ECCDF_DFSESPIDC2_5							(BIT5)
#define		ECC_ECCDF_DFSESPIDC2_4							(BIT4)
#define		ECC_ECCDF_DFSESPIDC2_3							(BIT3)
#define		ECC_ECCDF_DFSESPIDC2_2							(BIT2)
#define		ECC_ECCDF_DFSESPIDC2_1							(BIT1)
#define		ECC_ECCDF_DFSESPIDC2_0							(BIT0)
	#define	   ECC_ECCDF_DFSESPIDC2_CLEAR					(1)
/* DFSESPID3 */
#define		ECC_ECCDF_DFSESPID3_31							(BIT31)
#define		ECC_ECCDF_DFSESPID3_30							(BIT30)
#define		ECC_ECCDF_DFSESPID3_29							(BIT29)
#define		ECC_ECCDF_DFSESPID3_28							(BIT28)
#define		ECC_ECCDF_DFSESPID3_27							(BIT27)
#define		ECC_ECCDF_DFSESPID3_26							(BIT26)
#define		ECC_ECCDF_DFSESPID3_25							(BIT25)
#define		ECC_ECCDF_DFSESPID3_24							(BIT24)
#define		ECC_ECCDF_DFSESPID3_23							(BIT23)
#define		ECC_ECCDF_DFSESPID3_22							(BIT22)
#define		ECC_ECCDF_DFSESPID3_21							(BIT21)
#define		ECC_ECCDF_DFSESPID3_20							(BIT20)
#define		ECC_ECCDF_DFSESPID3_19							(BIT19)
#define		ECC_ECCDF_DFSESPID3_18							(BIT18)
#define		ECC_ECCDF_DFSESPID3_17							(BIT17)
#define		ECC_ECCDF_DFSESPID3_16							(BIT16)
#define		ECC_ECCDF_DFSESPID3_15							(BIT15)
#define		ECC_ECCDF_DFSESPID3_14							(BIT14)
#define		ECC_ECCDF_DFSESPID3_13							(BIT13)
#define		ECC_ECCDF_DFSESPID3_12							(BIT12)
#define		ECC_ECCDF_DFSESPID3_11							(BIT11)
#define		ECC_ECCDF_DFSESPID3_10							(BIT10)
#define		ECC_ECCDF_DFSESPID3_9							(BIT9)
#define		ECC_ECCDF_DFSESPID3_8							(BIT8)
#define		ECC_ECCDF_DFSESPID3_7							(BIT7)
#define		ECC_ECCDF_DFSESPID3_6							(BIT6)
#define		ECC_ECCDF_DFSESPID3_5							(BIT5)
#define		ECC_ECCDF_DFSESPID3_4							(BIT4)
#define		ECC_ECCDF_DFSESPID3_3							(BIT3)
#define		ECC_ECCDF_DFSESPID3_2							(BIT2)
#define		ECC_ECCDF_DFSESPID3_1							(BIT1)
#define		ECC_ECCDF_DFSESPID3_0							(BIT0)
/* DFSESPIDC3 */
#define		ECC_ECCDF_DFSESPIDC3_31							(BIT31)
#define		ECC_ECCDF_DFSESPIDC3_30							(BIT30)
#define		ECC_ECCDF_DFSESPIDC3_29							(BIT29)
#define		ECC_ECCDF_DFSESPIDC3_28							(BIT28)
#define		ECC_ECCDF_DFSESPIDC3_27							(BIT27)
#define		ECC_ECCDF_DFSESPIDC3_26							(BIT26)
#define		ECC_ECCDF_DFSESPIDC3_25							(BIT25)
#define		ECC_ECCDF_DFSESPIDC3_24							(BIT24)
#define		ECC_ECCDF_DFSESPIDC3_23							(BIT23)
#define		ECC_ECCDF_DFSESPIDC3_22							(BIT22)
#define		ECC_ECCDF_DFSESPIDC3_21							(BIT21)
#define		ECC_ECCDF_DFSESPIDC3_20							(BIT20)
#define		ECC_ECCDF_DFSESPIDC3_19							(BIT19)
#define		ECC_ECCDF_DFSESPIDC3_18							(BIT18)
#define		ECC_ECCDF_DFSESPIDC3_17							(BIT17)
#define		ECC_ECCDF_DFSESPIDC3_16							(BIT16)
#define		ECC_ECCDF_DFSESPIDC3_15							(BIT15)
#define		ECC_ECCDF_DFSESPIDC3_14							(BIT14)
#define		ECC_ECCDF_DFSESPIDC3_13							(BIT13)
#define		ECC_ECCDF_DFSESPIDC3_12							(BIT12)
#define		ECC_ECCDF_DFSESPIDC3_11							(BIT11)
#define		ECC_ECCDF_DFSESPIDC3_10							(BIT10)
#define		ECC_ECCDF_DFSESPIDC3_9							(BIT9)
#define		ECC_ECCDF_DFSESPIDC3_8							(BIT8)
#define		ECC_ECCDF_DFSESPIDC3_7							(BIT7)
#define		ECC_ECCDF_DFSESPIDC3_6							(BIT6)
#define		ECC_ECCDF_DFSESPIDC3_5							(BIT5)
#define		ECC_ECCDF_DFSESPIDC3_4							(BIT4)
#define		ECC_ECCDF_DFSESPIDC3_3							(BIT3)
#define		ECC_ECCDF_DFSESPIDC3_2							(BIT2)
#define		ECC_ECCDF_DFSESPIDC3_1							(BIT1)
#define		ECC_ECCDF_DFSESPIDC3_0							(BIT0)
	#define	   ECC_ECCDF_DFSESPIDC3_CLEAR					(1)
/* DFDESPID */
#define		ECC_ECCDF_DFDESPID_31							(BIT31)
#define		ECC_ECCDF_DFDESPID_30							(BIT30)
#define		ECC_ECCDF_DFDESPID_29							(BIT29)
#define		ECC_ECCDF_DFDESPID_28							(BIT28)
#define		ECC_ECCDF_DFDESPID_27							(BIT27)
#define		ECC_ECCDF_DFDESPID_26							(BIT26)
#define		ECC_ECCDF_DFDESPID_25							(BIT25)
#define		ECC_ECCDF_DFDESPID_24							(BIT24)
#define		ECC_ECCDF_DFDESPID_23							(BIT23)
#define		ECC_ECCDF_DFDESPID_22							(BIT22)
#define		ECC_ECCDF_DFDESPID_21							(BIT21)
#define		ECC_ECCDF_DFDESPID_20							(BIT20)
#define		ECC_ECCDF_DFDESPID_19							(BIT19)
#define		ECC_ECCDF_DFDESPID_18							(BIT18)
#define		ECC_ECCDF_DFDESPID_17							(BIT17)
#define		ECC_ECCDF_DFDESPID_16							(BIT16)
#define		ECC_ECCDF_DFDESPID_15							(BIT15)
#define		ECC_ECCDF_DFDESPID_14							(BIT14)
#define		ECC_ECCDF_DFDESPID_13							(BIT13)
#define		ECC_ECCDF_DFDESPID_12							(BIT12)
#define		ECC_ECCDF_DFDESPID_11							(BIT11)
#define		ECC_ECCDF_DFDESPID_10							(BIT10)
#define		ECC_ECCDF_DFDESPID_9							(BIT9)
#define		ECC_ECCDF_DFDESPID_8							(BIT8)
#define		ECC_ECCDF_DFDESPID_7							(BIT7)
#define		ECC_ECCDF_DFDESPID_6							(BIT6)
#define		ECC_ECCDF_DFDESPID_5							(BIT5)
#define		ECC_ECCDF_DFDESPID_4							(BIT4)
#define		ECC_ECCDF_DFDESPID_3							(BIT3)
#define		ECC_ECCDF_DFDESPID_2							(BIT2)
#define		ECC_ECCDF_DFDESPID_1							(BIT1)
#define		ECC_ECCDF_DFDESPID_0							(BIT0)
/* DFDESPIDC */
#define		ECC_ECCDF_DFDESPIDC_31							(BIT31)
#define		ECC_ECCDF_DFDESPIDC_30							(BIT30)
#define		ECC_ECCDF_DFDESPIDC_29							(BIT29)
#define		ECC_ECCDF_DFDESPIDC_28							(BIT28)
#define		ECC_ECCDF_DFDESPIDC_27							(BIT27)
#define		ECC_ECCDF_DFDESPIDC_26							(BIT26)
#define		ECC_ECCDF_DFDESPIDC_25							(BIT25)
#define		ECC_ECCDF_DFDESPIDC_24							(BIT24)
#define		ECC_ECCDF_DFDESPIDC_23							(BIT23)
#define		ECC_ECCDF_DFDESPIDC_22							(BIT22)
#define		ECC_ECCDF_DFDESPIDC_21							(BIT21)
#define		ECC_ECCDF_DFDESPIDC_20							(BIT20)
#define		ECC_ECCDF_DFDESPIDC_19							(BIT19)
#define		ECC_ECCDF_DFDESPIDC_18							(BIT18)
#define		ECC_ECCDF_DFDESPIDC_17							(BIT17)
#define		ECC_ECCDF_DFDESPIDC_16							(BIT16)
#define		ECC_ECCDF_DFDESPIDC_15							(BIT15)
#define		ECC_ECCDF_DFDESPIDC_14							(BIT14)
#define		ECC_ECCDF_DFDESPIDC_13							(BIT13)
#define		ECC_ECCDF_DFDESPIDC_12							(BIT12)
#define		ECC_ECCDF_DFDESPIDC_11							(BIT11)
#define		ECC_ECCDF_DFDESPIDC_10							(BIT10)
#define		ECC_ECCDF_DFDESPIDC_9							(BIT9)
#define		ECC_ECCDF_DFDESPIDC_8							(BIT8)
#define		ECC_ECCDF_DFDESPIDC_7							(BIT7)
#define		ECC_ECCDF_DFDESPIDC_6							(BIT6)
#define		ECC_ECCDF_DFDESPIDC_5							(BIT5)
#define		ECC_ECCDF_DFDESPIDC_4							(BIT4)
#define		ECC_ECCDF_DFDESPIDC_3							(BIT3)
#define		ECC_ECCDF_DFDESPIDC_2							(BIT2)
#define		ECC_ECCDF_DFDESPIDC_1							(BIT1)
#define		ECC_ECCDF_DFDESPIDC_0							(BIT0)
	#define	   ECC_ECCDF_DFDESPIDC_CLEAR					(1)
/* DFTSTCTL */
#define		ECC_ECCDF_DFTSTCTL_ECCTST						(BIT0)
	#define		ECC_ECCDF_DFTSTCTL_ECCTST_NORMAL			(0)
	#define		ECC_ECCDF_DFTSTCTL_ECCTST_TEST				(1)
/* DFKCPROT */
#define		ECC_ECCDF_DFKCPROT_KCPROT						(0xFFFFFFFEU)
#define		ECC_ECCDF_DFKCPROT_KCPROT_0						(BIT1)
#define		ECC_ECCDF_DFKCPROT_KCE							(BIT0)
	#define		ECC_ECCDF_DFKCPROT_KCE_DISABLE				(0xA5A5A500U)
	#define		ECC_ECCDF_DFKCPROT_KCE_ENABLE				(0xA5A5A501U)

/* Local RAM ECC and Address Parity and Address Feedback */
/* Module: ECCCNT_LR_PE0CL0 */
/* LRECCCTL */
#define		ECC_ECCCNT_LR_PE0CL0_ECCCTL_AFEDIS				(BIT3)
#define		ECC_ECCCNT_LR_PE0CL0_ECCCTL_SECDIS				(BIT1)
#define		ECC_ECCCNT_LR_PE0CL0_ECCCTL_ECCDIS				(BIT0)
	#define		ECC_ECCCNT_LR_PE0CL0_ECCCTL_ENABLE			(0)
	#define		ECC_ECCCNT_LR_PE0CL0_ECCCTL_DISABLE			(1)
/* LRECCTSTCTL */
#define		ECC_ECCCNT_LR_PE0CL0_TCTL_TST					(BIT1)
	#define		ECC_ECCCNT_LR_PE0CL0_TCTL_TST_NORMAL		(0)
	#define		ECC_ECCCNT_LR_PE0CL0_TCTL_TST_TEST			(1)
#define		ECC_ECCCNT_LR_PE0CL0_TCTL_DS					(BIT0)
	#define		ECC_ECCCNT_LR_PE0CL0_TCTL_DS_DATA			(0)
	#define		ECC_ECCCNT_LR_PE0CL0_TCTL_DS_ECC			(1)
/* LRAFINV */
#define		ECC_ECCCNT_LR_PE0CL0_LRAFINV_AFINV				(0x001FFFF0U)
/* LRTDATBFECCF */
#define		ECC_ECCCNT_LR_PE0CL0_BFECCF_BF3					(BIT30 + BIT29 + BIT28 + BIT27 + BIT26 + BIT25 + BIT24)
#define		ECC_ECCCNT_LR_PE0CL0_BFECCF_BF2					(BIT22 + BIT21 + BIT20 + BIT19 + BIT18 + BIT17 + BIT16)
#define		ECC_ECCCNT_LR_PE0CL0_BFECCF_BF1					(BIT14 + BIT13 + BIT12 + BIT11 + BIT10 + BIT9 + BIT8)
#define		ECC_ECCCNT_LR_PE0CL0_BFECCF_BF0					(BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)

/* Module: ECCCNT_LR_PE1CL0 */
/* LRECCCTL */
#define		ECC_ECCCNT_LR_PE1CL0_ECCCTL_AFEDIS				(BIT3)
#define		ECC_ECCCNT_LR_PE1CL0_ECCCTL_SECDIS				(BIT1)
#define		ECC_ECCCNT_LR_PE1CL0_ECCCTL_ECCDIS				(BIT0)
	#define		ECC_ECCCNT_LR_PE1CL0_ECCCTL_ENABLE			(0)
	#define		ECC_ECCCNT_LR_PE1CL0_ECCCTL_DISABLE			(1)
/* LRECCTSTCTL */
#define		ECC_ECCCNT_LR_PE1CL0_TCTL_TST					(BIT1)
	#define		ECC_ECCCNT_LR_PE1CL0_TCTL_TST_NORMAL		(0)
	#define		ECC_ECCCNT_LR_PE1CL0_TCTL_TST_TEST			(1)
#define		ECC_ECCCNT_LR_PE1CL0_TCTL_DS					(BIT0)
	#define		ECC_ECCCNT_LR_PE1CL0_TCTL_DS_DATA			(0)
	#define		ECC_ECCCNT_LR_PE1CL0_TCTL_DS_ECC			(1)
/* LRAFINV */
#define		ECC_ECCCNT_LR_PE1CL0_LRAFINV_AFINV				(0x001FFFF0U)
/* LRTDATBFECCF */
#define		ECC_ECCCNT_LR_PE1CL0_BFECCF_BF3					(BIT30 + BIT29 + BIT28 + BIT27 + BIT26 + BIT25 + BIT24)
#define		ECC_ECCCNT_LR_PE1CL0_BFECCF_BF2					(BIT22 + BIT21 + BIT20 + BIT19 + BIT18 + BIT17 + BIT16)
#define		ECC_ECCCNT_LR_PE1CL0_BFECCF_BF1					(BIT14 + BIT13 + BIT12 + BIT11 + BIT10 + BIT9 + BIT8)
#define		ECC_ECCCNT_LR_PE1CL0_BFECCF_BF0					(BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)

/* Module: ECCCNT_LR_PE2CL1 */
/* LRECCCTL */
#define		ECC_ECCCNT_LR_PE2CL1_ECCCTL_AFEDIS				(BIT3)
#define		ECC_ECCCNT_LR_PE2CL1_ECCCTL_SECDIS				(BIT1)
#define		ECC_ECCCNT_LR_PE2CL1_ECCCTL_ECCDIS				(BIT0)
	#define		ECC_ECCCNT_LR_PE2CL1_ECCCTL_ENABLE			(0)
	#define		ECC_ECCCNT_LR_PE2CL1_ECCCTL_DISABLE			(1)
/* LRECCTSTCTL */
#define		ECC_ECCCNT_LR_PE2CL1_TCTL_TST					(BIT1)
	#define		ECC_ECCCNT_LR_PE2CL1_TCTL_TST_NORMAL		(0)
	#define		ECC_ECCCNT_LR_PE2CL1_TCTL_TST_TEST			(1)
#define		ECC_ECCCNT_LR_PE2CL1_TCTL_DS					(BIT0)
	#define		ECC_ECCCNT_LR_PE2CL1_TCTL_DS_DATA			(0)
	#define		ECC_ECCCNT_LR_PE2CL1_TCTL_DS_ECC			(1)
/* LRAFINV */
#define		ECC_ECCCNT_LR_PE2CL1_LRAFINV_AFINV				(0x001FFFF0U)
/* LRTDATBFECCF */
#define		ECC_ECCCNT_LR_PE2CL1_BFECCF_BF3					(BIT30 + BIT29 + BIT28 + BIT27 + BIT26 + BIT25 + BIT24)
#define		ECC_ECCCNT_LR_PE2CL1_BFECCF_BF2					(BIT22 + BIT21 + BIT20 + BIT19 + BIT18 + BIT17 + BIT16)
#define		ECC_ECCCNT_LR_PE2CL1_BFECCF_BF1					(BIT14 + BIT13 + BIT12 + BIT11 + BIT10 + BIT9 + BIT8)
#define		ECC_ECCCNT_LR_PE2CL1_BFECCF_BF0					(BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)

/* Module: ECCCNT_LR_PE3CL1 */
/* LRECCCTL */
#define		ECC_ECCCNT_LR_PE3CL1_ECCCTL_AFEDIS				(BIT3)
#define		ECC_ECCCNT_LR_PE3CL1_ECCCTL_SECDIS				(BIT1)
#define		ECC_ECCCNT_LR_PE3CL1_ECCCTL_ECCDIS				(BIT0)
	#define		ECC_ECCCNT_LR_PE3CL1_ECCCTL_ENABLE			(0)
	#define		ECC_ECCCNT_LR_PE3CL1_ECCCTL_DISABLE			(1)
/* LRECCTSTCTL */
#define		ECC_ECCCNT_LR_PE3CL1_TCTL_TST					(BIT1)
	#define		ECC_ECCCNT_LR_PE3CL1_TCTL_TST_NORMAL		(0)
	#define		ECC_ECCCNT_LR_PE3CL1_TCTL_TST_TEST			(1)
#define		ECC_ECCCNT_LR_PE3CL1_TCTL_DS					(BIT0)
	#define		ECC_ECCCNT_LR_PE3CL1_TCTL_DS_DATA			(0)
	#define		ECC_ECCCNT_LR_PE3CL1_TCTL_DS_ECC			(1)
/* LRAFINV */
#define		ECC_ECCCNT_LR_PE3CL1_LRAFINV_AFINV				(0x001FFFF0U)
/* LRTDATBFECCF */
#define		ECC_ECCCNT_LR_PE3CL1_BFECCF_BF3					(BIT30 + BIT29 + BIT28 + BIT27 + BIT26 + BIT25 + BIT24)
#define		ECC_ECCCNT_LR_PE3CL1_BFECCF_BF2					(BIT22 + BIT21 + BIT20 + BIT19 + BIT18 + BIT17 + BIT16)
#define		ECC_ECCCNT_LR_PE3CL1_BFECCF_BF1					(BIT14 + BIT13 + BIT12 + BIT11 + BIT10 + BIT9 + BIT8)
#define		ECC_ECCCNT_LR_PE3CL1_BFECCF_BF0					(BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)

/* Module: ECCCNT_LR_PE4CL2 */
/* LRECCCTL */
#define		ECC_ECCCNT_LR_PE4CL2_ECCCTL_AFEDIS				(BIT3)
#define		ECC_ECCCNT_LR_PE4CL2_ECCCTL_SECDIS				(BIT1)
#define		ECC_ECCCNT_LR_PE4CL2_ECCCTL_ECCDIS				(BIT0)
	#define		ECC_ECCCNT_LR_PE4CL2_ECCCTL_ENABLE			(0)
	#define		ECC_ECCCNT_LR_PE4CL2_ECCCTL_DISABLE			(1)
/* LRECCTSTCTL */
#define		ECC_ECCCNT_LR_PE4CL2_TCTL_TST					(BIT1)
	#define		ECC_ECCCNT_LR_PE4CL2_TCTL_TST_NORMAL		(0)
	#define		ECC_ECCCNT_LR_PE4CL2_TCTL_TST_TEST			(1)
#define		ECC_ECCCNT_LR_PE4CL2_TCTL_DS					(BIT0)
	#define		ECC_ECCCNT_LR_PE4CL2_TCTL_DS_DATA			(0)
	#define		ECC_ECCCNT_LR_PE4CL2_TCTL_DS_ECC			(1)
/* LRAFINV */
#define		ECC_ECCCNT_LR_PE4CL2_LRAFINV_AFINV				(0x001FFFF0U)
/* LRTDATBFECCF */
#define		ECC_ECCCNT_LR_PE4CL2_BFECCF_BF3					(BIT30 + BIT29 + BIT28 + BIT27 + BIT26 + BIT25 + BIT24)
#define		ECC_ECCCNT_LR_PE4CL2_BFECCF_BF2					(BIT22 + BIT21 + BIT20 + BIT19 + BIT18 + BIT17 + BIT16)
#define		ECC_ECCCNT_LR_PE4CL2_BFECCF_BF1					(BIT14 + BIT13 + BIT12 + BIT11 + BIT10 + BIT9 + BIT8)
#define		ECC_ECCCNT_LR_PE4CL2_BFECCF_BF0					(BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)

/* Module: ECCCNT_LR_PE5CL2 */
/* LRECCCTL */
#define		ECC_ECCCNT_LR_PE5CL2_ECCCTL_AFEDIS				(BIT3)
#define		ECC_ECCCNT_LR_PE5CL2_ECCCTL_SECDIS				(BIT1)
#define		ECC_ECCCNT_LR_PE5CL2_ECCCTL_ECCDIS				(BIT0)
	#define		ECC_ECCCNT_LR_PE5CL2_ECCCTL_ENABLE			(0)
	#define		ECC_ECCCNT_LR_PE5CL2_ECCCTL_DISABLE			(1)
/* LRECCTSTCTL */
#define		ECC_ECCCNT_LR_PE5CL2_TCTL_TST					(BIT1)
	#define		ECC_ECCCNT_LR_PE5CL2_TCTL_TST_NORMAL		(0)
	#define		ECC_ECCCNT_LR_PE5CL2_TCTL_TST_TEST			(1)
#define		ECC_ECCCNT_LR_PE5CL2_TCTL_DS					(BIT0)
	#define		ECC_ECCCNT_LR_PE5CL2_TCTL_DS_DATA			(0)
	#define		ECC_ECCCNT_LR_PE5CL2_TCTL_DS_ECC			(1)
/* LRAFINV */
#define		ECC_ECCCNT_LR_PE5CL2_LRAFINV_AFINV				(0x001FFFF0U)
/* LRTDATBFECCF */
#define		ECC_ECCCNT_LR_PE5CL2_BFECCF_BF3					(BIT30 + BIT29 + BIT28 + BIT27 + BIT26 + BIT25 + BIT24)
#define		ECC_ECCCNT_LR_PE5CL2_BFECCF_BF2					(BIT22 + BIT21 + BIT20 + BIT19 + BIT18 + BIT17 + BIT16)
#define		ECC_ECCCNT_LR_PE5CL2_BFECCF_BF1					(BIT14 + BIT13 + BIT12 + BIT11 + BIT10 + BIT9 + BIT8)
#define		ECC_ECCCNT_LR_PE5CL2_BFECCF_BF0					(BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)

/* Module: MECCCAP_LR_PE0CL0 */
/* LR0_ERRINT */
#define		ECC_MECCCAP_LR_PE0CL0_ERINT_SEOVFIE				(BIT7)
#define		ECC_MECCCAP_LR_PE0CL0_ERINT_AFEIE				(BIT3)
#define		ECC_MECCCAP_LR_PE0CL0_ERINT_DEDIE				(BIT1)
#define		ECC_MECCCAP_LR_PE0CL0_ERINT_SEDIE				(BIT0)
	#define		ECC_MECCCAP_LR_PE0CL0_ERRINT_DISABLE		(0)
	#define		ECC_MECCCAP_LR_PE0CL0_ERRINT_ENABLE			(1)
/* LR0_SSTCLR */
#define		ECC_MECCCAP_LR_PE0CL0_SSTCLR_07					(BIT7)
#define		ECC_MECCCAP_LR_PE0CL0_SSTCLR_06					(BIT6)
#define		ECC_MECCCAP_LR_PE0CL0_SSTCLR_05					(BIT5)
#define		ECC_MECCCAP_LR_PE0CL0_SSTCLR_04					(BIT4)
#define		ECC_MECCCAP_LR_PE0CL0_SSTCLR_03					(BIT3)
#define		ECC_MECCCAP_LR_PE0CL0_SSTCLR_02					(BIT2)
#define		ECC_MECCCAP_LR_PE0CL0_SSTCLR_01					(BIT1)
#define		ECC_MECCCAP_LR_PE0CL0_SSTCLR_00					(BIT0)
	#define		ECC_MECCCAP_LR_PE0CL0_SSTCLR_CLEAR			(1)
/* LR0_DSTCLR */
#define		ECC_MECCCAP_LR_PE0CL0_DSTCLR_DSTCLR00			(BIT0)
	#define		ECC_MECCCAP_LR_PE0CL0_DSTCLR_CLEAR			(1)
/* LR0_OVFCLR */
#define		ECC_MECCCAP_LR_PE0CL0_OVFCLR_1					(BIT1)
#define		ECC_MECCCAP_LR_PE0CL0_OVFCLR_0					(BIT0)
	#define		ECC_MECCCAP_LR_PE0CL0_OVFCLR_CLEAR			(1)
/* LR0_SERSTR */
#define		ECC_MECCCAP_LR_PE0CL0_SERSTR_07					(BIT7)
#define		ECC_MECCCAP_LR_PE0CL0_SERSTR_06					(BIT6)
#define		ECC_MECCCAP_LR_PE0CL0_SERSTR_05					(BIT5)
#define		ECC_MECCCAP_LR_PE0CL0_SERSTR_04					(BIT4)
#define		ECC_MECCCAP_LR_PE0CL0_SERSTR_03					(BIT3)
#define		ECC_MECCCAP_LR_PE0CL0_SERSTR_02					(BIT2)
#define		ECC_MECCCAP_LR_PE0CL0_SERSTR_01					(BIT1)
#define		ECC_MECCCAP_LR_PE0CL0_SERSTR_00					(BIT0)
/* LR0_DERSTR */
#define		ECC_MECCCAP_LR_PE0CL0_DERSTR_AFEF00				(BIT3)
#define		ECC_MECCCAP_LR_PE0CL0_DERSTR_DEDF00				(BIT1)
/* LR0_OVFSTR */
#define		ECC_MECCCAP_LR_PE0CL0_OVFSTR_1					(BIT1)
#define		ECC_MECCCAP_LR_PE0CL0_OVFSTR_0					(BIT0)
/* LR0_SERINF */
#define		ECC_MECCCAP_LR_PE0CL0_SERINF_04					(BIT4)
#define		ECC_MECCCAP_LR_PE0CL0_SERINF_03					(BIT3)
#define		ECC_MECCCAP_LR_PE0CL0_SERINF_02					(BIT2)
#define		ECC_MECCCAP_LR_PE0CL0_SERINF_01					(BIT1)
#define		ECC_MECCCAP_LR_PE0CL0_SERINF_00					(BIT0)
/* LR0_nSEADR */
#define		ECC_MECCCAP_LR_PE0CL0_SEADR_SEDL				(BIT31 + BIT30 + BIT29 + BIT28 + BIT27)
#define		ECC_MECCCAP_LR_PE0CL0_SEADR_SEADR0				(0x0000FFFCU)
/* LR0_00DEADR */
#define		ECC_MECCCAP_LR_PE0CL0_DEADR_DEDL				(BIT31 + BIT30 + BIT29 + BIT28 + BIT27)
#define		ECC_MECCCAP_LR_PE0CL0_DEADR_DEADR0				(0x0000FFFCU)
/* LR0_00DESPIDCLR */
#define		ECC_MECCCAP_LR_PE0CL0_DSPIDC_31					(BIT31)
#define		ECC_MECCCAP_LR_PE0CL0_DSPIDC_30					(BIT30)
#define		ECC_MECCCAP_LR_PE0CL0_DSPIDC_29					(BIT29)
#define		ECC_MECCCAP_LR_PE0CL0_DSPIDC_28					(BIT28)
#define		ECC_MECCCAP_LR_PE0CL0_DSPIDC_27					(BIT27)
#define		ECC_MECCCAP_LR_PE0CL0_DSPIDC_26					(BIT26)
#define		ECC_MECCCAP_LR_PE0CL0_DSPIDC_25					(BIT25)
#define		ECC_MECCCAP_LR_PE0CL0_DSPIDC_24					(BIT24)
#define		ECC_MECCCAP_LR_PE0CL0_DSPIDC_23					(BIT23)
#define		ECC_MECCCAP_LR_PE0CL0_DSPIDC_22					(BIT22)
#define		ECC_MECCCAP_LR_PE0CL0_DSPIDC_21					(BIT21)
#define		ECC_MECCCAP_LR_PE0CL0_DSPIDC_20					(BIT20)
#define		ECC_MECCCAP_LR_PE0CL0_DSPIDC_19					(BIT19)
#define		ECC_MECCCAP_LR_PE0CL0_DSPIDC_18					(BIT18)
#define		ECC_MECCCAP_LR_PE0CL0_DSPIDC_17					(BIT17)
#define		ECC_MECCCAP_LR_PE0CL0_DSPIDC_16					(BIT16)
#define		ECC_MECCCAP_LR_PE0CL0_DSPIDC_15					(BIT15)
#define		ECC_MECCCAP_LR_PE0CL0_DSPIDC_14					(BIT14)
#define		ECC_MECCCAP_LR_PE0CL0_DSPIDC_13					(BIT13)
#define		ECC_MECCCAP_LR_PE0CL0_DSPIDC_12					(BIT12)
#define		ECC_MECCCAP_LR_PE0CL0_DSPIDC_11					(BIT11)
#define		ECC_MECCCAP_LR_PE0CL0_DSPIDC_10					(BIT10)
#define		ECC_MECCCAP_LR_PE0CL0_DSPIDC_9					(BIT9)
#define		ECC_MECCCAP_LR_PE0CL0_DSPIDC_8					(BIT8)
#define		ECC_MECCCAP_LR_PE0CL0_DSPIDC_7					(BIT7)
#define		ECC_MECCCAP_LR_PE0CL0_DSPIDC_6					(BIT6)
#define		ECC_MECCCAP_LR_PE0CL0_DSPIDC_5					(BIT5)
#define		ECC_MECCCAP_LR_PE0CL0_DSPIDC_4					(BIT4)
#define		ECC_MECCCAP_LR_PE0CL0_DSPIDC_3					(BIT3)
#define		ECC_MECCCAP_LR_PE0CL0_DSPIDC_2					(BIT2)
#define		ECC_MECCCAP_LR_PE0CL0_DSPIDC_1					(BIT1)
#define		ECC_MECCCAP_LR_PE0CL0_DSPIDC_0					(BIT0)
	#define	   ECC_MECCCAP_LR_PE0CL0_00DESPIDCLR_CLEAR		(1)
/* LR0_00DESPID */
#define		ECC_MECCCAP_LR_PE0CL0_DESPID_31					(BIT31)
#define		ECC_MECCCAP_LR_PE0CL0_DESPID_30					(BIT30)
#define		ECC_MECCCAP_LR_PE0CL0_DESPID_29					(BIT29)
#define		ECC_MECCCAP_LR_PE0CL0_DESPID_28					(BIT28)
#define		ECC_MECCCAP_LR_PE0CL0_DESPID_27					(BIT27)
#define		ECC_MECCCAP_LR_PE0CL0_DESPID_26					(BIT26)
#define		ECC_MECCCAP_LR_PE0CL0_DESPID_25					(BIT25)
#define		ECC_MECCCAP_LR_PE0CL0_DESPID_24					(BIT24)
#define		ECC_MECCCAP_LR_PE0CL0_DESPID_23					(BIT23)
#define		ECC_MECCCAP_LR_PE0CL0_DESPID_22					(BIT22)
#define		ECC_MECCCAP_LR_PE0CL0_DESPID_21					(BIT21)
#define		ECC_MECCCAP_LR_PE0CL0_DESPID_20					(BIT20)
#define		ECC_MECCCAP_LR_PE0CL0_DESPID_19					(BIT19)
#define		ECC_MECCCAP_LR_PE0CL0_DESPID_18					(BIT18)
#define		ECC_MECCCAP_LR_PE0CL0_DESPID_17					(BIT17)
#define		ECC_MECCCAP_LR_PE0CL0_DESPID_16					(BIT16)
#define		ECC_MECCCAP_LR_PE0CL0_DESPID_15					(BIT15)
#define		ECC_MECCCAP_LR_PE0CL0_DESPID_14					(BIT14)
#define		ECC_MECCCAP_LR_PE0CL0_DESPID_13					(BIT13)
#define		ECC_MECCCAP_LR_PE0CL0_DESPID_12					(BIT12)
#define		ECC_MECCCAP_LR_PE0CL0_DESPID_11					(BIT11)
#define		ECC_MECCCAP_LR_PE0CL0_DESPID_10					(BIT10)
#define		ECC_MECCCAP_LR_PE0CL0_DESPID_9					(BIT9)
#define		ECC_MECCCAP_LR_PE0CL0_DESPID_8					(BIT8)
#define		ECC_MECCCAP_LR_PE0CL0_DESPID_7					(BIT7)
#define		ECC_MECCCAP_LR_PE0CL0_DESPID_6					(BIT6)
#define		ECC_MECCCAP_LR_PE0CL0_DESPID_5					(BIT5)
#define		ECC_MECCCAP_LR_PE0CL0_DESPID_4					(BIT4)
#define		ECC_MECCCAP_LR_PE0CL0_DESPID_3					(BIT3)
#define		ECC_MECCCAP_LR_PE0CL0_DESPID_2					(BIT2)
#define		ECC_MECCCAP_LR_PE0CL0_DESPID_1					(BIT1)
#define		ECC_MECCCAP_LR_PE0CL0_DESPID_0					(BIT0)
/* LR0_00SESPIDCLR */
#define		ECC_MECCCAP_LR_PE0CL0_SSPIDC_31					(BIT31)
#define		ECC_MECCCAP_LR_PE0CL0_SSPIDC_30					(BIT30)
#define		ECC_MECCCAP_LR_PE0CL0_SSPIDC_29					(BIT29)
#define		ECC_MECCCAP_LR_PE0CL0_SSPIDC_28					(BIT28)
#define		ECC_MECCCAP_LR_PE0CL0_SSPIDC_27					(BIT27)
#define		ECC_MECCCAP_LR_PE0CL0_SSPIDC_26					(BIT26)
#define		ECC_MECCCAP_LR_PE0CL0_SSPIDC_25					(BIT25)
#define		ECC_MECCCAP_LR_PE0CL0_SSPIDC_24					(BIT24)
#define		ECC_MECCCAP_LR_PE0CL0_SSPIDC_23					(BIT23)
#define		ECC_MECCCAP_LR_PE0CL0_SSPIDC_22					(BIT22)
#define		ECC_MECCCAP_LR_PE0CL0_SSPIDC_21					(BIT21)
#define		ECC_MECCCAP_LR_PE0CL0_SSPIDC_20					(BIT20)
#define		ECC_MECCCAP_LR_PE0CL0_SSPIDC_19					(BIT19)
#define		ECC_MECCCAP_LR_PE0CL0_SSPIDC_18					(BIT18)
#define		ECC_MECCCAP_LR_PE0CL0_SSPIDC_17					(BIT17)
#define		ECC_MECCCAP_LR_PE0CL0_SSPIDC_16					(BIT16)
#define		ECC_MECCCAP_LR_PE0CL0_SSPIDC_15					(BIT15)
#define		ECC_MECCCAP_LR_PE0CL0_SSPIDC_14					(BIT14)
#define		ECC_MECCCAP_LR_PE0CL0_SSPIDC_13					(BIT13)
#define		ECC_MECCCAP_LR_PE0CL0_SSPIDC_12					(BIT12)
#define		ECC_MECCCAP_LR_PE0CL0_SSPIDC_11					(BIT11)
#define		ECC_MECCCAP_LR_PE0CL0_SSPIDC_10					(BIT10)
#define		ECC_MECCCAP_LR_PE0CL0_SSPIDC_9					(BIT9)
#define		ECC_MECCCAP_LR_PE0CL0_SSPIDC_8					(BIT8)
#define		ECC_MECCCAP_LR_PE0CL0_SSPIDC_7					(BIT7)
#define		ECC_MECCCAP_LR_PE0CL0_SSPIDC_6					(BIT6)
#define		ECC_MECCCAP_LR_PE0CL0_SSPIDC_5					(BIT5)
#define		ECC_MECCCAP_LR_PE0CL0_SSPIDC_4					(BIT4)
#define		ECC_MECCCAP_LR_PE0CL0_SSPIDC_3					(BIT3)
#define		ECC_MECCCAP_LR_PE0CL0_SSPIDC_2					(BIT2)
#define		ECC_MECCCAP_LR_PE0CL0_SSPIDC_1					(BIT1)
#define		ECC_MECCCAP_LR_PE0CL0_SSPIDC_0					(BIT0)
	#define	   ECC_MECCCAP_LR_PE0CL0_00SESPIDCLR_CLEAR		(1)
/* LR0_00SESPID */
#define		ECC_MECCCAP_LR_PE0CL0_SESPID_31					(BIT31)
#define		ECC_MECCCAP_LR_PE0CL0_SESPID_30					(BIT30)
#define		ECC_MECCCAP_LR_PE0CL0_SESPID_29					(BIT29)
#define		ECC_MECCCAP_LR_PE0CL0_SESPID_28					(BIT28)
#define		ECC_MECCCAP_LR_PE0CL0_SESPID_27					(BIT27)
#define		ECC_MECCCAP_LR_PE0CL0_SESPID_26					(BIT26)
#define		ECC_MECCCAP_LR_PE0CL0_SESPID_25					(BIT25)
#define		ECC_MECCCAP_LR_PE0CL0_SESPID_24					(BIT24)
#define		ECC_MECCCAP_LR_PE0CL0_SESPID_23					(BIT23)
#define		ECC_MECCCAP_LR_PE0CL0_SESPID_22					(BIT22)
#define		ECC_MECCCAP_LR_PE0CL0_SESPID_21					(BIT21)
#define		ECC_MECCCAP_LR_PE0CL0_SESPID_20					(BIT20)
#define		ECC_MECCCAP_LR_PE0CL0_SESPID_19					(BIT19)
#define		ECC_MECCCAP_LR_PE0CL0_SESPID_18					(BIT18)
#define		ECC_MECCCAP_LR_PE0CL0_SESPID_17					(BIT17)
#define		ECC_MECCCAP_LR_PE0CL0_SESPID_16					(BIT16)
#define		ECC_MECCCAP_LR_PE0CL0_SESPID_15					(BIT15)
#define		ECC_MECCCAP_LR_PE0CL0_SESPID_14					(BIT14)
#define		ECC_MECCCAP_LR_PE0CL0_SESPID_13					(BIT13)
#define		ECC_MECCCAP_LR_PE0CL0_SESPID_12					(BIT12)
#define		ECC_MECCCAP_LR_PE0CL0_SESPID_11					(BIT11)
#define		ECC_MECCCAP_LR_PE0CL0_SESPID_10					(BIT10)
#define		ECC_MECCCAP_LR_PE0CL0_SESPID_9					(BIT9)
#define		ECC_MECCCAP_LR_PE0CL0_SESPID_8					(BIT8)
#define		ECC_MECCCAP_LR_PE0CL0_SESPID_7					(BIT7)
#define		ECC_MECCCAP_LR_PE0CL0_SESPID_6					(BIT6)
#define		ECC_MECCCAP_LR_PE0CL0_SESPID_5					(BIT5)
#define		ECC_MECCCAP_LR_PE0CL0_SESPID_4					(BIT4)
#define		ECC_MECCCAP_LR_PE0CL0_SESPID_3					(BIT3)
#define		ECC_MECCCAP_LR_PE0CL0_SESPID_2					(BIT2)
#define		ECC_MECCCAP_LR_PE0CL0_SESPID_1					(BIT1)
#define		ECC_MECCCAP_LR_PE0CL0_SESPID_0					(BIT0)

/* Module: MECCCAP_LR_PE1CL0 */
/* LR0_ERRINT */
#define		ECC_MECCCAP_LR_PE1CL0_ERINT_SEOVFIE				(BIT7)
#define		ECC_MECCCAP_LR_PE1CL0_ERINT_AFEIE				(BIT3)
#define		ECC_MECCCAP_LR_PE1CL0_ERINT_DEDIE				(BIT1)
#define		ECC_MECCCAP_LR_PE1CL0_ERINT_SEDIE				(BIT0)
	#define		ECC_MECCCAP_LR_PE1CL0_ERRINT_DISABLE		(0)
	#define		ECC_MECCCAP_LR_PE1CL0_ERRINT_ENABLE			(1)
/* LR0_SSTCLR */
#define		ECC_MECCCAP_LR_PE1CL0_SSTCLR_07					(BIT7)
#define		ECC_MECCCAP_LR_PE1CL0_SSTCLR_06					(BIT6)
#define		ECC_MECCCAP_LR_PE1CL0_SSTCLR_05					(BIT5)
#define		ECC_MECCCAP_LR_PE1CL0_SSTCLR_04					(BIT4)
#define		ECC_MECCCAP_LR_PE1CL0_SSTCLR_03					(BIT3)
#define		ECC_MECCCAP_LR_PE1CL0_SSTCLR_02					(BIT2)
#define		ECC_MECCCAP_LR_PE1CL0_SSTCLR_01					(BIT1)
#define		ECC_MECCCAP_LR_PE1CL0_SSTCLR_00					(BIT0)
	#define		ECC_MECCCAP_LR_PE1CL0_SSTCLR_CLEAR			(1)
/* LR0_DSTCLR */
#define		ECC_MECCCAP_LR_PE1CL0_DSTCLR_DSTCLR00			(BIT0)
	#define		ECC_MECCCAP_LR_PE1CL0_DSTCLR_CLEAR			(1)
/* LR0_OVFCLR */
#define		ECC_MECCCAP_LR_PE1CL0_OVFCLR_1					(BIT1)
#define		ECC_MECCCAP_LR_PE1CL0_OVFCLR_0					(BIT0)
	#define		ECC_MECCCAP_LR_PE1CL0_OVFCLR_CLEAR			(1)
/* LR0_SERSTR */
#define		ECC_MECCCAP_LR_PE1CL0_SERSTR_07					(BIT7)
#define		ECC_MECCCAP_LR_PE1CL0_SERSTR_06					(BIT6)
#define		ECC_MECCCAP_LR_PE1CL0_SERSTR_05					(BIT5)
#define		ECC_MECCCAP_LR_PE1CL0_SERSTR_04					(BIT4)
#define		ECC_MECCCAP_LR_PE1CL0_SERSTR_03					(BIT3)
#define		ECC_MECCCAP_LR_PE1CL0_SERSTR_02					(BIT2)
#define		ECC_MECCCAP_LR_PE1CL0_SERSTR_01					(BIT1)
#define		ECC_MECCCAP_LR_PE1CL0_SERSTR_00					(BIT0)
/* LR0_DERSTR */
#define		ECC_MECCCAP_LR_PE1CL0_DERSTR_AFEF00				(BIT3)
#define		ECC_MECCCAP_LR_PE1CL0_DERSTR_DEDF00				(BIT1)
/* LR0_OVFSTR */
#define		ECC_MECCCAP_LR_PE1CL0_OVFSTR_1					(BIT1)
#define		ECC_MECCCAP_LR_PE1CL0_OVFSTR_0					(BIT0)
/* LR0_SERINF */
#define		ECC_MECCCAP_LR_PE1CL0_SERINF_04					(BIT4)
#define		ECC_MECCCAP_LR_PE1CL0_SERINF_03					(BIT3)
#define		ECC_MECCCAP_LR_PE1CL0_SERINF_02					(BIT2)
#define		ECC_MECCCAP_LR_PE1CL0_SERINF_01					(BIT1)
#define		ECC_MECCCAP_LR_PE1CL0_SERINF_00					(BIT0)
/* LR0_nSEADR */
#define		ECC_MECCCAP_LR_PE1CL0_SEADR_SEDL				(BIT31 + BIT30 + BIT29 + BIT28 + BIT27)
#define		ECC_MECCCAP_LR_PE1CL0_SEADR_SEADR0				(0x0000FFFCU)
/* LR0_00DEADR */
#define		ECC_MECCCAP_LR_PE1CL0_DEADR_DEDL				(BIT31 + BIT30 + BIT29 + BIT28 + BIT27)
#define		ECC_MECCCAP_LR_PE1CL0_DEADR_DEADR0				(0x0000FFFCU)
/* LR0_00DESPIDCLR */
#define		ECC_MECCCAP_LR_PE1CL0_DSPIDC_31					(BIT31)
#define		ECC_MECCCAP_LR_PE1CL0_DSPIDC_30					(BIT30)
#define		ECC_MECCCAP_LR_PE1CL0_DSPIDC_29					(BIT29)
#define		ECC_MECCCAP_LR_PE1CL0_DSPIDC_28					(BIT28)
#define		ECC_MECCCAP_LR_PE1CL0_DSPIDC_27					(BIT27)
#define		ECC_MECCCAP_LR_PE1CL0_DSPIDC_26					(BIT26)
#define		ECC_MECCCAP_LR_PE1CL0_DSPIDC_25					(BIT25)
#define		ECC_MECCCAP_LR_PE1CL0_DSPIDC_24					(BIT24)
#define		ECC_MECCCAP_LR_PE1CL0_DSPIDC_23					(BIT23)
#define		ECC_MECCCAP_LR_PE1CL0_DSPIDC_22					(BIT22)
#define		ECC_MECCCAP_LR_PE1CL0_DSPIDC_21					(BIT21)
#define		ECC_MECCCAP_LR_PE1CL0_DSPIDC_20					(BIT20)
#define		ECC_MECCCAP_LR_PE1CL0_DSPIDC_19					(BIT19)
#define		ECC_MECCCAP_LR_PE1CL0_DSPIDC_18					(BIT18)
#define		ECC_MECCCAP_LR_PE1CL0_DSPIDC_17					(BIT17)
#define		ECC_MECCCAP_LR_PE1CL0_DSPIDC_16					(BIT16)
#define		ECC_MECCCAP_LR_PE1CL0_DSPIDC_15					(BIT15)
#define		ECC_MECCCAP_LR_PE1CL0_DSPIDC_14					(BIT14)
#define		ECC_MECCCAP_LR_PE1CL0_DSPIDC_13					(BIT13)
#define		ECC_MECCCAP_LR_PE1CL0_DSPIDC_12					(BIT12)
#define		ECC_MECCCAP_LR_PE1CL0_DSPIDC_11					(BIT11)
#define		ECC_MECCCAP_LR_PE1CL0_DSPIDC_10					(BIT10)
#define		ECC_MECCCAP_LR_PE1CL0_DSPIDC_9					(BIT9)
#define		ECC_MECCCAP_LR_PE1CL0_DSPIDC_8					(BIT8)
#define		ECC_MECCCAP_LR_PE1CL0_DSPIDC_7					(BIT7)
#define		ECC_MECCCAP_LR_PE1CL0_DSPIDC_6					(BIT6)
#define		ECC_MECCCAP_LR_PE1CL0_DSPIDC_5					(BIT5)
#define		ECC_MECCCAP_LR_PE1CL0_DSPIDC_4					(BIT4)
#define		ECC_MECCCAP_LR_PE1CL0_DSPIDC_3					(BIT3)
#define		ECC_MECCCAP_LR_PE1CL0_DSPIDC_2					(BIT2)
#define		ECC_MECCCAP_LR_PE1CL0_DSPIDC_1					(BIT1)
#define		ECC_MECCCAP_LR_PE1CL0_DSPIDC_0					(BIT0)
	#define	   ECC_MECCCAP_LR_PE1CL0_00DESPIDCLR_CLEAR		(1)
/* LR0_00DESPID */
#define		ECC_MECCCAP_LR_PE1CL0_DESPID_31					(BIT31)
#define		ECC_MECCCAP_LR_PE1CL0_DESPID_30					(BIT30)
#define		ECC_MECCCAP_LR_PE1CL0_DESPID_29					(BIT29)
#define		ECC_MECCCAP_LR_PE1CL0_DESPID_28					(BIT28)
#define		ECC_MECCCAP_LR_PE1CL0_DESPID_27					(BIT27)
#define		ECC_MECCCAP_LR_PE1CL0_DESPID_26					(BIT26)
#define		ECC_MECCCAP_LR_PE1CL0_DESPID_25					(BIT25)
#define		ECC_MECCCAP_LR_PE1CL0_DESPID_24					(BIT24)
#define		ECC_MECCCAP_LR_PE1CL0_DESPID_23					(BIT23)
#define		ECC_MECCCAP_LR_PE1CL0_DESPID_22					(BIT22)
#define		ECC_MECCCAP_LR_PE1CL0_DESPID_21					(BIT21)
#define		ECC_MECCCAP_LR_PE1CL0_DESPID_20					(BIT20)
#define		ECC_MECCCAP_LR_PE1CL0_DESPID_19					(BIT19)
#define		ECC_MECCCAP_LR_PE1CL0_DESPID_18					(BIT18)
#define		ECC_MECCCAP_LR_PE1CL0_DESPID_17					(BIT17)
#define		ECC_MECCCAP_LR_PE1CL0_DESPID_16					(BIT16)
#define		ECC_MECCCAP_LR_PE1CL0_DESPID_15					(BIT15)
#define		ECC_MECCCAP_LR_PE1CL0_DESPID_14					(BIT14)
#define		ECC_MECCCAP_LR_PE1CL0_DESPID_13					(BIT13)
#define		ECC_MECCCAP_LR_PE1CL0_DESPID_12					(BIT12)
#define		ECC_MECCCAP_LR_PE1CL0_DESPID_11					(BIT11)
#define		ECC_MECCCAP_LR_PE1CL0_DESPID_10					(BIT10)
#define		ECC_MECCCAP_LR_PE1CL0_DESPID_9					(BIT9)
#define		ECC_MECCCAP_LR_PE1CL0_DESPID_8					(BIT8)
#define		ECC_MECCCAP_LR_PE1CL0_DESPID_7					(BIT7)
#define		ECC_MECCCAP_LR_PE1CL0_DESPID_6					(BIT6)
#define		ECC_MECCCAP_LR_PE1CL0_DESPID_5					(BIT5)
#define		ECC_MECCCAP_LR_PE1CL0_DESPID_4					(BIT4)
#define		ECC_MECCCAP_LR_PE1CL0_DESPID_3					(BIT3)
#define		ECC_MECCCAP_LR_PE1CL0_DESPID_2					(BIT2)
#define		ECC_MECCCAP_LR_PE1CL0_DESPID_1					(BIT1)
#define		ECC_MECCCAP_LR_PE1CL0_DESPID_0					(BIT0)
/* LR0_00SESPIDCLR */
#define		ECC_MECCCAP_LR_PE1CL0_SSPIDC_31					(BIT31)
#define		ECC_MECCCAP_LR_PE1CL0_SSPIDC_30					(BIT30)
#define		ECC_MECCCAP_LR_PE1CL0_SSPIDC_29					(BIT29)
#define		ECC_MECCCAP_LR_PE1CL0_SSPIDC_28					(BIT28)
#define		ECC_MECCCAP_LR_PE1CL0_SSPIDC_27					(BIT27)
#define		ECC_MECCCAP_LR_PE1CL0_SSPIDC_26					(BIT26)
#define		ECC_MECCCAP_LR_PE1CL0_SSPIDC_25					(BIT25)
#define		ECC_MECCCAP_LR_PE1CL0_SSPIDC_24					(BIT24)
#define		ECC_MECCCAP_LR_PE1CL0_SSPIDC_23					(BIT23)
#define		ECC_MECCCAP_LR_PE1CL0_SSPIDC_22					(BIT22)
#define		ECC_MECCCAP_LR_PE1CL0_SSPIDC_21					(BIT21)
#define		ECC_MECCCAP_LR_PE1CL0_SSPIDC_20					(BIT20)
#define		ECC_MECCCAP_LR_PE1CL0_SSPIDC_19					(BIT19)
#define		ECC_MECCCAP_LR_PE1CL0_SSPIDC_18					(BIT18)
#define		ECC_MECCCAP_LR_PE1CL0_SSPIDC_17					(BIT17)
#define		ECC_MECCCAP_LR_PE1CL0_SSPIDC_16					(BIT16)
#define		ECC_MECCCAP_LR_PE1CL0_SSPIDC_15					(BIT15)
#define		ECC_MECCCAP_LR_PE1CL0_SSPIDC_14					(BIT14)
#define		ECC_MECCCAP_LR_PE1CL0_SSPIDC_13					(BIT13)
#define		ECC_MECCCAP_LR_PE1CL0_SSPIDC_12					(BIT12)
#define		ECC_MECCCAP_LR_PE1CL0_SSPIDC_11					(BIT11)
#define		ECC_MECCCAP_LR_PE1CL0_SSPIDC_10					(BIT10)
#define		ECC_MECCCAP_LR_PE1CL0_SSPIDC_9					(BIT9)
#define		ECC_MECCCAP_LR_PE1CL0_SSPIDC_8					(BIT8)
#define		ECC_MECCCAP_LR_PE1CL0_SSPIDC_7					(BIT7)
#define		ECC_MECCCAP_LR_PE1CL0_SSPIDC_6					(BIT6)
#define		ECC_MECCCAP_LR_PE1CL0_SSPIDC_5					(BIT5)
#define		ECC_MECCCAP_LR_PE1CL0_SSPIDC_4					(BIT4)
#define		ECC_MECCCAP_LR_PE1CL0_SSPIDC_3					(BIT3)
#define		ECC_MECCCAP_LR_PE1CL0_SSPIDC_2					(BIT2)
#define		ECC_MECCCAP_LR_PE1CL0_SSPIDC_1					(BIT1)
#define		ECC_MECCCAP_LR_PE1CL0_SSPIDC_0					(BIT0)
	#define	   ECC_MECCCAP_LR_PE1CL0_00SESPIDCLR_CLEAR		(1)
/* LR0_00SESPID */
#define		ECC_MECCCAP_LR_PE1CL0_SESPID_31					(BIT31)
#define		ECC_MECCCAP_LR_PE1CL0_SESPID_30					(BIT30)
#define		ECC_MECCCAP_LR_PE1CL0_SESPID_29					(BIT29)
#define		ECC_MECCCAP_LR_PE1CL0_SESPID_28					(BIT28)
#define		ECC_MECCCAP_LR_PE1CL0_SESPID_27					(BIT27)
#define		ECC_MECCCAP_LR_PE1CL0_SESPID_26					(BIT26)
#define		ECC_MECCCAP_LR_PE1CL0_SESPID_25					(BIT25)
#define		ECC_MECCCAP_LR_PE1CL0_SESPID_24					(BIT24)
#define		ECC_MECCCAP_LR_PE1CL0_SESPID_23					(BIT23)
#define		ECC_MECCCAP_LR_PE1CL0_SESPID_22					(BIT22)
#define		ECC_MECCCAP_LR_PE1CL0_SESPID_21					(BIT21)
#define		ECC_MECCCAP_LR_PE1CL0_SESPID_20					(BIT20)
#define		ECC_MECCCAP_LR_PE1CL0_SESPID_19					(BIT19)
#define		ECC_MECCCAP_LR_PE1CL0_SESPID_18					(BIT18)
#define		ECC_MECCCAP_LR_PE1CL0_SESPID_17					(BIT17)
#define		ECC_MECCCAP_LR_PE1CL0_SESPID_16					(BIT16)
#define		ECC_MECCCAP_LR_PE1CL0_SESPID_15					(BIT15)
#define		ECC_MECCCAP_LR_PE1CL0_SESPID_14					(BIT14)
#define		ECC_MECCCAP_LR_PE1CL0_SESPID_13					(BIT13)
#define		ECC_MECCCAP_LR_PE1CL0_SESPID_12					(BIT12)
#define		ECC_MECCCAP_LR_PE1CL0_SESPID_11					(BIT11)
#define		ECC_MECCCAP_LR_PE1CL0_SESPID_10					(BIT10)
#define		ECC_MECCCAP_LR_PE1CL0_SESPID_9					(BIT9)
#define		ECC_MECCCAP_LR_PE1CL0_SESPID_8					(BIT8)
#define		ECC_MECCCAP_LR_PE1CL0_SESPID_7					(BIT7)
#define		ECC_MECCCAP_LR_PE1CL0_SESPID_6					(BIT6)
#define		ECC_MECCCAP_LR_PE1CL0_SESPID_5					(BIT5)
#define		ECC_MECCCAP_LR_PE1CL0_SESPID_4					(BIT4)
#define		ECC_MECCCAP_LR_PE1CL0_SESPID_3					(BIT3)
#define		ECC_MECCCAP_LR_PE1CL0_SESPID_2					(BIT2)
#define		ECC_MECCCAP_LR_PE1CL0_SESPID_1					(BIT1)
#define		ECC_MECCCAP_LR_PE1CL0_SESPID_0					(BIT0)

/* Module: MECCCAP_LR_PE2CL1 */
/* LR0_ERRINT */
#define		ECC_MECCCAP_LR_PE2CL1_ERINT_SEOVFIE				(BIT7)
#define		ECC_MECCCAP_LR_PE2CL1_ERINT_AFEIE				(BIT3)
#define		ECC_MECCCAP_LR_PE2CL1_ERINT_DEDIE				(BIT1)
#define		ECC_MECCCAP_LR_PE2CL1_ERINT_SEDIE				(BIT0)
	#define		ECC_MECCCAP_LR_PE2CL1_ERRINT_DISABLE		(0)
	#define		ECC_MECCCAP_LR_PE2CL1_ERRINT_ENABLE			(1)
/* LR0_SSTCLR */
#define		ECC_MECCCAP_LR_PE2CL1_SSTCLR_07					(BIT7)
#define		ECC_MECCCAP_LR_PE2CL1_SSTCLR_06					(BIT6)
#define		ECC_MECCCAP_LR_PE2CL1_SSTCLR_05					(BIT5)
#define		ECC_MECCCAP_LR_PE2CL1_SSTCLR_04					(BIT4)
#define		ECC_MECCCAP_LR_PE2CL1_SSTCLR_03					(BIT3)
#define		ECC_MECCCAP_LR_PE2CL1_SSTCLR_02					(BIT2)
#define		ECC_MECCCAP_LR_PE2CL1_SSTCLR_01					(BIT1)
#define		ECC_MECCCAP_LR_PE2CL1_SSTCLR_00					(BIT0)
	#define		ECC_MECCCAP_LR_PE2CL1_SSTCLR_CLEAR			(1)
/* LR0_DSTCLR */
#define		ECC_MECCCAP_LR_PE2CL1_DSTCLR_DSTCLR00			(BIT0)
	#define		ECC_MECCCAP_LR_PE2CL1_DSTCLR_CLEAR			(1)
/* LR0_OVFCLR */
#define		ECC_MECCCAP_LR_PE2CL1_OVFCLR_1					(BIT1)
#define		ECC_MECCCAP_LR_PE2CL1_OVFCLR_0					(BIT0)
	#define		ECC_MECCCAP_LR_PE2CL1_OVFCLR_CLEAR			(1)
/* LR0_SERSTR */
#define		ECC_MECCCAP_LR_PE2CL1_SERSTR_07					(BIT7)
#define		ECC_MECCCAP_LR_PE2CL1_SERSTR_06					(BIT6)
#define		ECC_MECCCAP_LR_PE2CL1_SERSTR_05					(BIT5)
#define		ECC_MECCCAP_LR_PE2CL1_SERSTR_04					(BIT4)
#define		ECC_MECCCAP_LR_PE2CL1_SERSTR_03					(BIT3)
#define		ECC_MECCCAP_LR_PE2CL1_SERSTR_02					(BIT2)
#define		ECC_MECCCAP_LR_PE2CL1_SERSTR_01					(BIT1)
#define		ECC_MECCCAP_LR_PE2CL1_SERSTR_00					(BIT0)
/* LR0_DERSTR */
#define		ECC_MECCCAP_LR_PE2CL1_DERSTR_AFEF00				(BIT3)
#define		ECC_MECCCAP_LR_PE2CL1_DERSTR_DEDF00				(BIT1)
/* LR0_OVFSTR */
#define		ECC_MECCCAP_LR_PE2CL1_OVFSTR_1					(BIT1)
#define		ECC_MECCCAP_LR_PE2CL1_OVFSTR_0					(BIT0)
/* LR0_SERINF */
#define		ECC_MECCCAP_LR_PE2CL1_SERINF_04					(BIT4)
#define		ECC_MECCCAP_LR_PE2CL1_SERINF_03					(BIT3)
#define		ECC_MECCCAP_LR_PE2CL1_SERINF_02					(BIT2)
#define		ECC_MECCCAP_LR_PE2CL1_SERINF_01					(BIT1)
#define		ECC_MECCCAP_LR_PE2CL1_SERINF_00					(BIT0)
/* LR0_nSEADR */
#define		ECC_MECCCAP_LR_PE2CL1_SEADR_SEDL				(BIT31 + BIT30 + BIT29 + BIT28 + BIT27)
#define		ECC_MECCCAP_LR_PE2CL1_SEADR_SEADR0				(0x0000FFFCU)
/* LR0_00DEADR */
#define		ECC_MECCCAP_LR_PE2CL1_DEADR_DEDL				(BIT31 + BIT30 + BIT29 + BIT28 + BIT27)
#define		ECC_MECCCAP_LR_PE2CL1_DEADR_DEADR0				(0x0000FFFCU)
/* LR0_00DESPIDCLR */
#define		ECC_MECCCAP_LR_PE2CL1_DSPIDC_31					(BIT31)
#define		ECC_MECCCAP_LR_PE2CL1_DSPIDC_30					(BIT30)
#define		ECC_MECCCAP_LR_PE2CL1_DSPIDC_29					(BIT29)
#define		ECC_MECCCAP_LR_PE2CL1_DSPIDC_28					(BIT28)
#define		ECC_MECCCAP_LR_PE2CL1_DSPIDC_27					(BIT27)
#define		ECC_MECCCAP_LR_PE2CL1_DSPIDC_26					(BIT26)
#define		ECC_MECCCAP_LR_PE2CL1_DSPIDC_25					(BIT25)
#define		ECC_MECCCAP_LR_PE2CL1_DSPIDC_24					(BIT24)
#define		ECC_MECCCAP_LR_PE2CL1_DSPIDC_23					(BIT23)
#define		ECC_MECCCAP_LR_PE2CL1_DSPIDC_22					(BIT22)
#define		ECC_MECCCAP_LR_PE2CL1_DSPIDC_21					(BIT21)
#define		ECC_MECCCAP_LR_PE2CL1_DSPIDC_20					(BIT20)
#define		ECC_MECCCAP_LR_PE2CL1_DSPIDC_19					(BIT19)
#define		ECC_MECCCAP_LR_PE2CL1_DSPIDC_18					(BIT18)
#define		ECC_MECCCAP_LR_PE2CL1_DSPIDC_17					(BIT17)
#define		ECC_MECCCAP_LR_PE2CL1_DSPIDC_16					(BIT16)
#define		ECC_MECCCAP_LR_PE2CL1_DSPIDC_15					(BIT15)
#define		ECC_MECCCAP_LR_PE2CL1_DSPIDC_14					(BIT14)
#define		ECC_MECCCAP_LR_PE2CL1_DSPIDC_13					(BIT13)
#define		ECC_MECCCAP_LR_PE2CL1_DSPIDC_12					(BIT12)
#define		ECC_MECCCAP_LR_PE2CL1_DSPIDC_11					(BIT11)
#define		ECC_MECCCAP_LR_PE2CL1_DSPIDC_10					(BIT10)
#define		ECC_MECCCAP_LR_PE2CL1_DSPIDC_9					(BIT9)
#define		ECC_MECCCAP_LR_PE2CL1_DSPIDC_8					(BIT8)
#define		ECC_MECCCAP_LR_PE2CL1_DSPIDC_7					(BIT7)
#define		ECC_MECCCAP_LR_PE2CL1_DSPIDC_6					(BIT6)
#define		ECC_MECCCAP_LR_PE2CL1_DSPIDC_5					(BIT5)
#define		ECC_MECCCAP_LR_PE2CL1_DSPIDC_4					(BIT4)
#define		ECC_MECCCAP_LR_PE2CL1_DSPIDC_3					(BIT3)
#define		ECC_MECCCAP_LR_PE2CL1_DSPIDC_2					(BIT2)
#define		ECC_MECCCAP_LR_PE2CL1_DSPIDC_1					(BIT1)
#define		ECC_MECCCAP_LR_PE2CL1_DSPIDC_0					(BIT0)
	#define	   ECC_MECCCAP_LR_PE2CL1_00DESPIDCLR_CLEAR		(1)
/* LR0_00DESPID */
#define		ECC_MECCCAP_LR_PE2CL1_DESPID_31					(BIT31)
#define		ECC_MECCCAP_LR_PE2CL1_DESPID_30					(BIT30)
#define		ECC_MECCCAP_LR_PE2CL1_DESPID_29					(BIT29)
#define		ECC_MECCCAP_LR_PE2CL1_DESPID_28					(BIT28)
#define		ECC_MECCCAP_LR_PE2CL1_DESPID_27					(BIT27)
#define		ECC_MECCCAP_LR_PE2CL1_DESPID_26					(BIT26)
#define		ECC_MECCCAP_LR_PE2CL1_DESPID_25					(BIT25)
#define		ECC_MECCCAP_LR_PE2CL1_DESPID_24					(BIT24)
#define		ECC_MECCCAP_LR_PE2CL1_DESPID_23					(BIT23)
#define		ECC_MECCCAP_LR_PE2CL1_DESPID_22					(BIT22)
#define		ECC_MECCCAP_LR_PE2CL1_DESPID_21					(BIT21)
#define		ECC_MECCCAP_LR_PE2CL1_DESPID_20					(BIT20)
#define		ECC_MECCCAP_LR_PE2CL1_DESPID_19					(BIT19)
#define		ECC_MECCCAP_LR_PE2CL1_DESPID_18					(BIT18)
#define		ECC_MECCCAP_LR_PE2CL1_DESPID_17					(BIT17)
#define		ECC_MECCCAP_LR_PE2CL1_DESPID_16					(BIT16)
#define		ECC_MECCCAP_LR_PE2CL1_DESPID_15					(BIT15)
#define		ECC_MECCCAP_LR_PE2CL1_DESPID_14					(BIT14)
#define		ECC_MECCCAP_LR_PE2CL1_DESPID_13					(BIT13)
#define		ECC_MECCCAP_LR_PE2CL1_DESPID_12					(BIT12)
#define		ECC_MECCCAP_LR_PE2CL1_DESPID_11					(BIT11)
#define		ECC_MECCCAP_LR_PE2CL1_DESPID_10					(BIT10)
#define		ECC_MECCCAP_LR_PE2CL1_DESPID_9					(BIT9)
#define		ECC_MECCCAP_LR_PE2CL1_DESPID_8					(BIT8)
#define		ECC_MECCCAP_LR_PE2CL1_DESPID_7					(BIT7)
#define		ECC_MECCCAP_LR_PE2CL1_DESPID_6					(BIT6)
#define		ECC_MECCCAP_LR_PE2CL1_DESPID_5					(BIT5)
#define		ECC_MECCCAP_LR_PE2CL1_DESPID_4					(BIT4)
#define		ECC_MECCCAP_LR_PE2CL1_DESPID_3					(BIT3)
#define		ECC_MECCCAP_LR_PE2CL1_DESPID_2					(BIT2)
#define		ECC_MECCCAP_LR_PE2CL1_DESPID_1					(BIT1)
#define		ECC_MECCCAP_LR_PE2CL1_DESPID_0					(BIT0)
/* LR0_00SESPIDCLR */
#define		ECC_MECCCAP_LR_PE2CL1_SSPIDC_31					(BIT31)
#define		ECC_MECCCAP_LR_PE2CL1_SSPIDC_30					(BIT30)
#define		ECC_MECCCAP_LR_PE2CL1_SSPIDC_29					(BIT29)
#define		ECC_MECCCAP_LR_PE2CL1_SSPIDC_28					(BIT28)
#define		ECC_MECCCAP_LR_PE2CL1_SSPIDC_27					(BIT27)
#define		ECC_MECCCAP_LR_PE2CL1_SSPIDC_26					(BIT26)
#define		ECC_MECCCAP_LR_PE2CL1_SSPIDC_25					(BIT25)
#define		ECC_MECCCAP_LR_PE2CL1_SSPIDC_24					(BIT24)
#define		ECC_MECCCAP_LR_PE2CL1_SSPIDC_23					(BIT23)
#define		ECC_MECCCAP_LR_PE2CL1_SSPIDC_22					(BIT22)
#define		ECC_MECCCAP_LR_PE2CL1_SSPIDC_21					(BIT21)
#define		ECC_MECCCAP_LR_PE2CL1_SSPIDC_20					(BIT20)
#define		ECC_MECCCAP_LR_PE2CL1_SSPIDC_19					(BIT19)
#define		ECC_MECCCAP_LR_PE2CL1_SSPIDC_18					(BIT18)
#define		ECC_MECCCAP_LR_PE2CL1_SSPIDC_17					(BIT17)
#define		ECC_MECCCAP_LR_PE2CL1_SSPIDC_16					(BIT16)
#define		ECC_MECCCAP_LR_PE2CL1_SSPIDC_15					(BIT15)
#define		ECC_MECCCAP_LR_PE2CL1_SSPIDC_14					(BIT14)
#define		ECC_MECCCAP_LR_PE2CL1_SSPIDC_13					(BIT13)
#define		ECC_MECCCAP_LR_PE2CL1_SSPIDC_12					(BIT12)
#define		ECC_MECCCAP_LR_PE2CL1_SSPIDC_11					(BIT11)
#define		ECC_MECCCAP_LR_PE2CL1_SSPIDC_10					(BIT10)
#define		ECC_MECCCAP_LR_PE2CL1_SSPIDC_9					(BIT9)
#define		ECC_MECCCAP_LR_PE2CL1_SSPIDC_8					(BIT8)
#define		ECC_MECCCAP_LR_PE2CL1_SSPIDC_7					(BIT7)
#define		ECC_MECCCAP_LR_PE2CL1_SSPIDC_6					(BIT6)
#define		ECC_MECCCAP_LR_PE2CL1_SSPIDC_5					(BIT5)
#define		ECC_MECCCAP_LR_PE2CL1_SSPIDC_4					(BIT4)
#define		ECC_MECCCAP_LR_PE2CL1_SSPIDC_3					(BIT3)
#define		ECC_MECCCAP_LR_PE2CL1_SSPIDC_2					(BIT2)
#define		ECC_MECCCAP_LR_PE2CL1_SSPIDC_1					(BIT1)
#define		ECC_MECCCAP_LR_PE2CL1_SSPIDC_0					(BIT0)
	#define	   ECC_MECCCAP_LR_PE2CL1_00SESPIDCLR_CLEAR		(1)
/* LR0_00SESPID */
#define		ECC_MECCCAP_LR_PE2CL1_SESPID_31					(BIT31)
#define		ECC_MECCCAP_LR_PE2CL1_SESPID_30					(BIT30)
#define		ECC_MECCCAP_LR_PE2CL1_SESPID_29					(BIT29)
#define		ECC_MECCCAP_LR_PE2CL1_SESPID_28					(BIT28)
#define		ECC_MECCCAP_LR_PE2CL1_SESPID_27					(BIT27)
#define		ECC_MECCCAP_LR_PE2CL1_SESPID_26					(BIT26)
#define		ECC_MECCCAP_LR_PE2CL1_SESPID_25					(BIT25)
#define		ECC_MECCCAP_LR_PE2CL1_SESPID_24					(BIT24)
#define		ECC_MECCCAP_LR_PE2CL1_SESPID_23					(BIT23)
#define		ECC_MECCCAP_LR_PE2CL1_SESPID_22					(BIT22)
#define		ECC_MECCCAP_LR_PE2CL1_SESPID_21					(BIT21)
#define		ECC_MECCCAP_LR_PE2CL1_SESPID_20					(BIT20)
#define		ECC_MECCCAP_LR_PE2CL1_SESPID_19					(BIT19)
#define		ECC_MECCCAP_LR_PE2CL1_SESPID_18					(BIT18)
#define		ECC_MECCCAP_LR_PE2CL1_SESPID_17					(BIT17)
#define		ECC_MECCCAP_LR_PE2CL1_SESPID_16					(BIT16)
#define		ECC_MECCCAP_LR_PE2CL1_SESPID_15					(BIT15)
#define		ECC_MECCCAP_LR_PE2CL1_SESPID_14					(BIT14)
#define		ECC_MECCCAP_LR_PE2CL1_SESPID_13					(BIT13)
#define		ECC_MECCCAP_LR_PE2CL1_SESPID_12					(BIT12)
#define		ECC_MECCCAP_LR_PE2CL1_SESPID_11					(BIT11)
#define		ECC_MECCCAP_LR_PE2CL1_SESPID_10					(BIT10)
#define		ECC_MECCCAP_LR_PE2CL1_SESPID_9					(BIT9)
#define		ECC_MECCCAP_LR_PE2CL1_SESPID_8					(BIT8)
#define		ECC_MECCCAP_LR_PE2CL1_SESPID_7					(BIT7)
#define		ECC_MECCCAP_LR_PE2CL1_SESPID_6					(BIT6)
#define		ECC_MECCCAP_LR_PE2CL1_SESPID_5					(BIT5)
#define		ECC_MECCCAP_LR_PE2CL1_SESPID_4					(BIT4)
#define		ECC_MECCCAP_LR_PE2CL1_SESPID_3					(BIT3)
#define		ECC_MECCCAP_LR_PE2CL1_SESPID_2					(BIT2)
#define		ECC_MECCCAP_LR_PE2CL1_SESPID_1					(BIT1)
#define		ECC_MECCCAP_LR_PE2CL1_SESPID_0					(BIT0)

/* Module: MECCCAP_LR_PE3CL1 */
/* LR0_ERRINT */
#define		ECC_MECCCAP_LR_PE3CL1_ERINT_SEOVFIE				(BIT7)
#define		ECC_MECCCAP_LR_PE3CL1_ERINT_AFEIE				(BIT3)
#define		ECC_MECCCAP_LR_PE3CL1_ERINT_DEDIE				(BIT1)
#define		ECC_MECCCAP_LR_PE3CL1_ERINT_SEDIE				(BIT0)
	#define		ECC_MECCCAP_LR_PE3CL1_ERRINT_DISABLE		(0)
	#define		ECC_MECCCAP_LR_PE3CL1_ERRINT_ENABLE			(1)
/* LR0_SSTCLR */
#define		ECC_MECCCAP_LR_PE3CL1_SSTCLR_07					(BIT7)
#define		ECC_MECCCAP_LR_PE3CL1_SSTCLR_06					(BIT6)
#define		ECC_MECCCAP_LR_PE3CL1_SSTCLR_05					(BIT5)
#define		ECC_MECCCAP_LR_PE3CL1_SSTCLR_04					(BIT4)
#define		ECC_MECCCAP_LR_PE3CL1_SSTCLR_03					(BIT3)
#define		ECC_MECCCAP_LR_PE3CL1_SSTCLR_02					(BIT2)
#define		ECC_MECCCAP_LR_PE3CL1_SSTCLR_01					(BIT1)
#define		ECC_MECCCAP_LR_PE3CL1_SSTCLR_00					(BIT0)
	#define		ECC_MECCCAP_LR_PE3CL1_SSTCLR_CLEAR			(1)
/* LR0_DSTCLR */
#define		ECC_MECCCAP_LR_PE3CL1_DSTCLR_DSTCLR00			(BIT0)
	#define		ECC_MECCCAP_LR_PE3CL1_DSTCLR_CLEAR			(1)
/* LR0_OVFCLR */
#define		ECC_MECCCAP_LR_PE3CL1_OVFCLR_1					(BIT1)
#define		ECC_MECCCAP_LR_PE3CL1_OVFCLR_0					(BIT0)
	#define		ECC_MECCCAP_LR_PE3CL1_OVFCLR_CLEAR			(1)
/* LR0_SERSTR */
#define		ECC_MECCCAP_LR_PE3CL1_SERSTR_07					(BIT7)
#define		ECC_MECCCAP_LR_PE3CL1_SERSTR_06					(BIT6)
#define		ECC_MECCCAP_LR_PE3CL1_SERSTR_05					(BIT5)
#define		ECC_MECCCAP_LR_PE3CL1_SERSTR_04					(BIT4)
#define		ECC_MECCCAP_LR_PE3CL1_SERSTR_03					(BIT3)
#define		ECC_MECCCAP_LR_PE3CL1_SERSTR_02					(BIT2)
#define		ECC_MECCCAP_LR_PE3CL1_SERSTR_01					(BIT1)
#define		ECC_MECCCAP_LR_PE3CL1_SERSTR_00					(BIT0)
/* LR0_DERSTR */
#define		ECC_MECCCAP_LR_PE3CL1_DERSTR_AFEF00				(BIT3)
#define		ECC_MECCCAP_LR_PE3CL1_DERSTR_DEDF00				(BIT1)
/* LR0_OVFSTR */
#define		ECC_MECCCAP_LR_PE3CL1_OVFSTR_1					(BIT1)
#define		ECC_MECCCAP_LR_PE3CL1_OVFSTR_0					(BIT0)
/* LR0_SERINF */
#define		ECC_MECCCAP_LR_PE3CL1_SERINF_04					(BIT4)
#define		ECC_MECCCAP_LR_PE3CL1_SERINF_03					(BIT3)
#define		ECC_MECCCAP_LR_PE3CL1_SERINF_02					(BIT2)
#define		ECC_MECCCAP_LR_PE3CL1_SERINF_01					(BIT1)
#define		ECC_MECCCAP_LR_PE3CL1_SERINF_00					(BIT0)
/* LR0_nSEADR */
#define		ECC_MECCCAP_LR_PE3CL1_SEADR_SEDL				(BIT31 + BIT30 + BIT29 + BIT28 + BIT27)
#define		ECC_MECCCAP_LR_PE3CL1_SEADR_SEADR0				(0x0000FFFCU)
/* LR0_00DEADR */
#define		ECC_MECCCAP_LR_PE3CL1_DEADR_DEDL				(BIT31 + BIT30 + BIT29 + BIT28 + BIT27)
#define		ECC_MECCCAP_LR_PE3CL1_DEADR_DEADR0				(0x0000FFFCU)
/* LR0_00DESPIDCLR */
#define		ECC_MECCCAP_LR_PE3CL1_DSPIDC_31					(BIT31)
#define		ECC_MECCCAP_LR_PE3CL1_DSPIDC_30					(BIT30)
#define		ECC_MECCCAP_LR_PE3CL1_DSPIDC_29					(BIT29)
#define		ECC_MECCCAP_LR_PE3CL1_DSPIDC_28					(BIT28)
#define		ECC_MECCCAP_LR_PE3CL1_DSPIDC_27					(BIT27)
#define		ECC_MECCCAP_LR_PE3CL1_DSPIDC_26					(BIT26)
#define		ECC_MECCCAP_LR_PE3CL1_DSPIDC_25					(BIT25)
#define		ECC_MECCCAP_LR_PE3CL1_DSPIDC_24					(BIT24)
#define		ECC_MECCCAP_LR_PE3CL1_DSPIDC_23					(BIT23)
#define		ECC_MECCCAP_LR_PE3CL1_DSPIDC_22					(BIT22)
#define		ECC_MECCCAP_LR_PE3CL1_DSPIDC_21					(BIT21)
#define		ECC_MECCCAP_LR_PE3CL1_DSPIDC_20					(BIT20)
#define		ECC_MECCCAP_LR_PE3CL1_DSPIDC_19					(BIT19)
#define		ECC_MECCCAP_LR_PE3CL1_DSPIDC_18					(BIT18)
#define		ECC_MECCCAP_LR_PE3CL1_DSPIDC_17					(BIT17)
#define		ECC_MECCCAP_LR_PE3CL1_DSPIDC_16					(BIT16)
#define		ECC_MECCCAP_LR_PE3CL1_DSPIDC_15					(BIT15)
#define		ECC_MECCCAP_LR_PE3CL1_DSPIDC_14					(BIT14)
#define		ECC_MECCCAP_LR_PE3CL1_DSPIDC_13					(BIT13)
#define		ECC_MECCCAP_LR_PE3CL1_DSPIDC_12					(BIT12)
#define		ECC_MECCCAP_LR_PE3CL1_DSPIDC_11					(BIT11)
#define		ECC_MECCCAP_LR_PE3CL1_DSPIDC_10					(BIT10)
#define		ECC_MECCCAP_LR_PE3CL1_DSPIDC_9					(BIT9)
#define		ECC_MECCCAP_LR_PE3CL1_DSPIDC_8					(BIT8)
#define		ECC_MECCCAP_LR_PE3CL1_DSPIDC_7					(BIT7)
#define		ECC_MECCCAP_LR_PE3CL1_DSPIDC_6					(BIT6)
#define		ECC_MECCCAP_LR_PE3CL1_DSPIDC_5					(BIT5)
#define		ECC_MECCCAP_LR_PE3CL1_DSPIDC_4					(BIT4)
#define		ECC_MECCCAP_LR_PE3CL1_DSPIDC_3					(BIT3)
#define		ECC_MECCCAP_LR_PE3CL1_DSPIDC_2					(BIT2)
#define		ECC_MECCCAP_LR_PE3CL1_DSPIDC_1					(BIT1)
#define		ECC_MECCCAP_LR_PE3CL1_DSPIDC_0					(BIT0)
	#define	   ECC_MECCCAP_LR_PE3CL1_00DESPIDCLR_CLEAR		(1)
/* LR0_00DESPID */
#define		ECC_MECCCAP_LR_PE3CL1_DESPID_31					(BIT31)
#define		ECC_MECCCAP_LR_PE3CL1_DESPID_30					(BIT30)
#define		ECC_MECCCAP_LR_PE3CL1_DESPID_29					(BIT29)
#define		ECC_MECCCAP_LR_PE3CL1_DESPID_28					(BIT28)
#define		ECC_MECCCAP_LR_PE3CL1_DESPID_27					(BIT27)
#define		ECC_MECCCAP_LR_PE3CL1_DESPID_26					(BIT26)
#define		ECC_MECCCAP_LR_PE3CL1_DESPID_25					(BIT25)
#define		ECC_MECCCAP_LR_PE3CL1_DESPID_24					(BIT24)
#define		ECC_MECCCAP_LR_PE3CL1_DESPID_23					(BIT23)
#define		ECC_MECCCAP_LR_PE3CL1_DESPID_22					(BIT22)
#define		ECC_MECCCAP_LR_PE3CL1_DESPID_21					(BIT21)
#define		ECC_MECCCAP_LR_PE3CL1_DESPID_20					(BIT20)
#define		ECC_MECCCAP_LR_PE3CL1_DESPID_19					(BIT19)
#define		ECC_MECCCAP_LR_PE3CL1_DESPID_18					(BIT18)
#define		ECC_MECCCAP_LR_PE3CL1_DESPID_17					(BIT17)
#define		ECC_MECCCAP_LR_PE3CL1_DESPID_16					(BIT16)
#define		ECC_MECCCAP_LR_PE3CL1_DESPID_15					(BIT15)
#define		ECC_MECCCAP_LR_PE3CL1_DESPID_14					(BIT14)
#define		ECC_MECCCAP_LR_PE3CL1_DESPID_13					(BIT13)
#define		ECC_MECCCAP_LR_PE3CL1_DESPID_12					(BIT12)
#define		ECC_MECCCAP_LR_PE3CL1_DESPID_11					(BIT11)
#define		ECC_MECCCAP_LR_PE3CL1_DESPID_10					(BIT10)
#define		ECC_MECCCAP_LR_PE3CL1_DESPID_9					(BIT9)
#define		ECC_MECCCAP_LR_PE3CL1_DESPID_8					(BIT8)
#define		ECC_MECCCAP_LR_PE3CL1_DESPID_7					(BIT7)
#define		ECC_MECCCAP_LR_PE3CL1_DESPID_6					(BIT6)
#define		ECC_MECCCAP_LR_PE3CL1_DESPID_5					(BIT5)
#define		ECC_MECCCAP_LR_PE3CL1_DESPID_4					(BIT4)
#define		ECC_MECCCAP_LR_PE3CL1_DESPID_3					(BIT3)
#define		ECC_MECCCAP_LR_PE3CL1_DESPID_2					(BIT2)
#define		ECC_MECCCAP_LR_PE3CL1_DESPID_1					(BIT1)
#define		ECC_MECCCAP_LR_PE3CL1_DESPID_0					(BIT0)
/* LR0_00SESPIDCLR */
#define		ECC_MECCCAP_LR_PE3CL1_SSPIDC_31					(BIT31)
#define		ECC_MECCCAP_LR_PE3CL1_SSPIDC_30					(BIT30)
#define		ECC_MECCCAP_LR_PE3CL1_SSPIDC_29					(BIT29)
#define		ECC_MECCCAP_LR_PE3CL1_SSPIDC_28					(BIT28)
#define		ECC_MECCCAP_LR_PE3CL1_SSPIDC_27					(BIT27)
#define		ECC_MECCCAP_LR_PE3CL1_SSPIDC_26					(BIT26)
#define		ECC_MECCCAP_LR_PE3CL1_SSPIDC_25					(BIT25)
#define		ECC_MECCCAP_LR_PE3CL1_SSPIDC_24					(BIT24)
#define		ECC_MECCCAP_LR_PE3CL1_SSPIDC_23					(BIT23)
#define		ECC_MECCCAP_LR_PE3CL1_SSPIDC_22					(BIT22)
#define		ECC_MECCCAP_LR_PE3CL1_SSPIDC_21					(BIT21)
#define		ECC_MECCCAP_LR_PE3CL1_SSPIDC_20					(BIT20)
#define		ECC_MECCCAP_LR_PE3CL1_SSPIDC_19					(BIT19)
#define		ECC_MECCCAP_LR_PE3CL1_SSPIDC_18					(BIT18)
#define		ECC_MECCCAP_LR_PE3CL1_SSPIDC_17					(BIT17)
#define		ECC_MECCCAP_LR_PE3CL1_SSPIDC_16					(BIT16)
#define		ECC_MECCCAP_LR_PE3CL1_SSPIDC_15					(BIT15)
#define		ECC_MECCCAP_LR_PE3CL1_SSPIDC_14					(BIT14)
#define		ECC_MECCCAP_LR_PE3CL1_SSPIDC_13					(BIT13)
#define		ECC_MECCCAP_LR_PE3CL1_SSPIDC_12					(BIT12)
#define		ECC_MECCCAP_LR_PE3CL1_SSPIDC_11					(BIT11)
#define		ECC_MECCCAP_LR_PE3CL1_SSPIDC_10					(BIT10)
#define		ECC_MECCCAP_LR_PE3CL1_SSPIDC_9					(BIT9)
#define		ECC_MECCCAP_LR_PE3CL1_SSPIDC_8					(BIT8)
#define		ECC_MECCCAP_LR_PE3CL1_SSPIDC_7					(BIT7)
#define		ECC_MECCCAP_LR_PE3CL1_SSPIDC_6					(BIT6)
#define		ECC_MECCCAP_LR_PE3CL1_SSPIDC_5					(BIT5)
#define		ECC_MECCCAP_LR_PE3CL1_SSPIDC_4					(BIT4)
#define		ECC_MECCCAP_LR_PE3CL1_SSPIDC_3					(BIT3)
#define		ECC_MECCCAP_LR_PE3CL1_SSPIDC_2					(BIT2)
#define		ECC_MECCCAP_LR_PE3CL1_SSPIDC_1					(BIT1)
#define		ECC_MECCCAP_LR_PE3CL1_SSPIDC_0					(BIT0)
	#define	   ECC_MECCCAP_LR_PE3CL1_00SESPIDCLR_CLEAR		(1)
/* LR0_00SESPID */
#define		ECC_MECCCAP_LR_PE3CL1_SESPID_31					(BIT31)
#define		ECC_MECCCAP_LR_PE3CL1_SESPID_30					(BIT30)
#define		ECC_MECCCAP_LR_PE3CL1_SESPID_29					(BIT29)
#define		ECC_MECCCAP_LR_PE3CL1_SESPID_28					(BIT28)
#define		ECC_MECCCAP_LR_PE3CL1_SESPID_27					(BIT27)
#define		ECC_MECCCAP_LR_PE3CL1_SESPID_26					(BIT26)
#define		ECC_MECCCAP_LR_PE3CL1_SESPID_25					(BIT25)
#define		ECC_MECCCAP_LR_PE3CL1_SESPID_24					(BIT24)
#define		ECC_MECCCAP_LR_PE3CL1_SESPID_23					(BIT23)
#define		ECC_MECCCAP_LR_PE3CL1_SESPID_22					(BIT22)
#define		ECC_MECCCAP_LR_PE3CL1_SESPID_21					(BIT21)
#define		ECC_MECCCAP_LR_PE3CL1_SESPID_20					(BIT20)
#define		ECC_MECCCAP_LR_PE3CL1_SESPID_19					(BIT19)
#define		ECC_MECCCAP_LR_PE3CL1_SESPID_18					(BIT18)
#define		ECC_MECCCAP_LR_PE3CL1_SESPID_17					(BIT17)
#define		ECC_MECCCAP_LR_PE3CL1_SESPID_16					(BIT16)
#define		ECC_MECCCAP_LR_PE3CL1_SESPID_15					(BIT15)
#define		ECC_MECCCAP_LR_PE3CL1_SESPID_14					(BIT14)
#define		ECC_MECCCAP_LR_PE3CL1_SESPID_13					(BIT13)
#define		ECC_MECCCAP_LR_PE3CL1_SESPID_12					(BIT12)
#define		ECC_MECCCAP_LR_PE3CL1_SESPID_11					(BIT11)
#define		ECC_MECCCAP_LR_PE3CL1_SESPID_10					(BIT10)
#define		ECC_MECCCAP_LR_PE3CL1_SESPID_9					(BIT9)
#define		ECC_MECCCAP_LR_PE3CL1_SESPID_8					(BIT8)
#define		ECC_MECCCAP_LR_PE3CL1_SESPID_7					(BIT7)
#define		ECC_MECCCAP_LR_PE3CL1_SESPID_6					(BIT6)
#define		ECC_MECCCAP_LR_PE3CL1_SESPID_5					(BIT5)
#define		ECC_MECCCAP_LR_PE3CL1_SESPID_4					(BIT4)
#define		ECC_MECCCAP_LR_PE3CL1_SESPID_3					(BIT3)
#define		ECC_MECCCAP_LR_PE3CL1_SESPID_2					(BIT2)
#define		ECC_MECCCAP_LR_PE3CL1_SESPID_1					(BIT1)
#define		ECC_MECCCAP_LR_PE3CL1_SESPID_0					(BIT0)


/* Module: MECCCAP_LR_PE4CL2 */
/* LR0_ERRINT */
#define		ECC_MECCCAP_LR_PE4CL2_ERINT_SEOVFIE				(BIT7)
#define		ECC_MECCCAP_LR_PE4CL2_ERINT_AFEIE				(BIT3)
#define		ECC_MECCCAP_LR_PE4CL2_ERINT_DEDIE				(BIT1)
#define		ECC_MECCCAP_LR_PE4CL2_ERINT_SEDIE				(BIT0)
	#define		ECC_MECCCAP_LR_PE4CL2_ERRINT_DISABLE		(0)
	#define		ECC_MECCCAP_LR_PE4CL2_ERRINT_ENABLE			(1)
/* LR0_SSTCLR */
#define		ECC_MECCCAP_LR_PE4CL2_SSTCLR_07					(BIT7)
#define		ECC_MECCCAP_LR_PE4CL2_SSTCLR_06					(BIT6)
#define		ECC_MECCCAP_LR_PE4CL2_SSTCLR_05					(BIT5)
#define		ECC_MECCCAP_LR_PE4CL2_SSTCLR_04					(BIT4)
#define		ECC_MECCCAP_LR_PE4CL2_SSTCLR_03					(BIT3)
#define		ECC_MECCCAP_LR_PE4CL2_SSTCLR_02					(BIT2)
#define		ECC_MECCCAP_LR_PE4CL2_SSTCLR_01					(BIT1)
#define		ECC_MECCCAP_LR_PE4CL2_SSTCLR_00					(BIT0)
	#define		ECC_MECCCAP_LR_PE4CL2_SSTCLR_CLEAR			(1)
/* LR0_DSTCLR */
#define		ECC_MECCCAP_LR_PE4CL2_DSTCLR_DSTCLR00			(BIT0)
	#define		ECC_MECCCAP_LR_PE4CL2_DSTCLR_CLEAR			(1)
/* LR0_OVFCLR */
#define		ECC_MECCCAP_LR_PE4CL2_OVFCLR_1					(BIT1)
#define		ECC_MECCCAP_LR_PE4CL2_OVFCLR_0					(BIT0)
	#define		ECC_MECCCAP_LR_PE4CL2_OVFCLR_CLEAR			(1)
/* LR0_SERSTR */
#define		ECC_MECCCAP_LR_PE4CL2_SERSTR_07					(BIT7)
#define		ECC_MECCCAP_LR_PE4CL2_SERSTR_06					(BIT6)
#define		ECC_MECCCAP_LR_PE4CL2_SERSTR_05					(BIT5)
#define		ECC_MECCCAP_LR_PE4CL2_SERSTR_04					(BIT4)
#define		ECC_MECCCAP_LR_PE4CL2_SERSTR_03					(BIT3)
#define		ECC_MECCCAP_LR_PE4CL2_SERSTR_02					(BIT2)
#define		ECC_MECCCAP_LR_PE4CL2_SERSTR_01					(BIT1)
#define		ECC_MECCCAP_LR_PE4CL2_SERSTR_00					(BIT0)
/* LR0_DERSTR */
#define		ECC_MECCCAP_LR_PE4CL2_DERSTR_AFEF00				(BIT3)
#define		ECC_MECCCAP_LR_PE4CL2_DERSTR_DEDF00				(BIT1)
/* LR0_OVFSTR */
#define		ECC_MECCCAP_LR_PE4CL2_OVFSTR_1					(BIT1)
#define		ECC_MECCCAP_LR_PE4CL2_OVFSTR_0					(BIT0)
/* LR0_SERINF */
#define		ECC_MECCCAP_LR_PE4CL2_SERINF_04					(BIT4)
#define		ECC_MECCCAP_LR_PE4CL2_SERINF_03					(BIT3)
#define		ECC_MECCCAP_LR_PE4CL2_SERINF_02					(BIT2)
#define		ECC_MECCCAP_LR_PE4CL2_SERINF_01					(BIT1)
#define		ECC_MECCCAP_LR_PE4CL2_SERINF_00					(BIT0)
/* LR0_nSEADR */
#define		ECC_MECCCAP_LR_PE4CL2_SEADR_SEDL				(BIT31 + BIT30 + BIT29 + BIT28 + BIT27)
#define		ECC_MECCCAP_LR_PE4CL2_SEADR_SEADR0				(0x0000FFFCU)
/* LR0_00DEADR */
#define		ECC_MECCCAP_LR_PE4CL2_DEADR_DEDL				(BIT31 + BIT30 + BIT29 + BIT28 + BIT27)
#define		ECC_MECCCAP_LR_PE4CL2_DEADR_DEADR0				(0x0000FFFCU)
/* LR0_00DESPIDCLR */
#define		ECC_MECCCAP_LR_PE4CL2_DSPIDC_31					(BIT31)
#define		ECC_MECCCAP_LR_PE4CL2_DSPIDC_30					(BIT30)
#define		ECC_MECCCAP_LR_PE4CL2_DSPIDC_29					(BIT29)
#define		ECC_MECCCAP_LR_PE4CL2_DSPIDC_28					(BIT28)
#define		ECC_MECCCAP_LR_PE4CL2_DSPIDC_27					(BIT27)
#define		ECC_MECCCAP_LR_PE4CL2_DSPIDC_26					(BIT26)
#define		ECC_MECCCAP_LR_PE4CL2_DSPIDC_25					(BIT25)
#define		ECC_MECCCAP_LR_PE4CL2_DSPIDC_24					(BIT24)
#define		ECC_MECCCAP_LR_PE4CL2_DSPIDC_23					(BIT23)
#define		ECC_MECCCAP_LR_PE4CL2_DSPIDC_22					(BIT22)
#define		ECC_MECCCAP_LR_PE4CL2_DSPIDC_21					(BIT21)
#define		ECC_MECCCAP_LR_PE4CL2_DSPIDC_20					(BIT20)
#define		ECC_MECCCAP_LR_PE4CL2_DSPIDC_19					(BIT19)
#define		ECC_MECCCAP_LR_PE4CL2_DSPIDC_18					(BIT18)
#define		ECC_MECCCAP_LR_PE4CL2_DSPIDC_17					(BIT17)
#define		ECC_MECCCAP_LR_PE4CL2_DSPIDC_16					(BIT16)
#define		ECC_MECCCAP_LR_PE4CL2_DSPIDC_15					(BIT15)
#define		ECC_MECCCAP_LR_PE4CL2_DSPIDC_14					(BIT14)
#define		ECC_MECCCAP_LR_PE4CL2_DSPIDC_13					(BIT13)
#define		ECC_MECCCAP_LR_PE4CL2_DSPIDC_12					(BIT12)
#define		ECC_MECCCAP_LR_PE4CL2_DSPIDC_11					(BIT11)
#define		ECC_MECCCAP_LR_PE4CL2_DSPIDC_10					(BIT10)
#define		ECC_MECCCAP_LR_PE4CL2_DSPIDC_9					(BIT9)
#define		ECC_MECCCAP_LR_PE4CL2_DSPIDC_8					(BIT8)
#define		ECC_MECCCAP_LR_PE4CL2_DSPIDC_7					(BIT7)
#define		ECC_MECCCAP_LR_PE4CL2_DSPIDC_6					(BIT6)
#define		ECC_MECCCAP_LR_PE4CL2_DSPIDC_5					(BIT5)
#define		ECC_MECCCAP_LR_PE4CL2_DSPIDC_4					(BIT4)
#define		ECC_MECCCAP_LR_PE4CL2_DSPIDC_3					(BIT3)
#define		ECC_MECCCAP_LR_PE4CL2_DSPIDC_2					(BIT2)
#define		ECC_MECCCAP_LR_PE4CL2_DSPIDC_1					(BIT1)
#define		ECC_MECCCAP_LR_PE4CL2_DSPIDC_0					(BIT0)
	#define	   ECC_MECCCAP_LR_PE4CL2_00DESPIDCLR_CLEAR		(1)
/* LR0_00DESPID */
#define		ECC_MECCCAP_LR_PE4CL2_DESPID_31					(BIT31)
#define		ECC_MECCCAP_LR_PE4CL2_DESPID_30					(BIT30)
#define		ECC_MECCCAP_LR_PE4CL2_DESPID_29					(BIT29)
#define		ECC_MECCCAP_LR_PE4CL2_DESPID_28					(BIT28)
#define		ECC_MECCCAP_LR_PE4CL2_DESPID_27					(BIT27)
#define		ECC_MECCCAP_LR_PE4CL2_DESPID_26					(BIT26)
#define		ECC_MECCCAP_LR_PE4CL2_DESPID_25					(BIT25)
#define		ECC_MECCCAP_LR_PE4CL2_DESPID_24					(BIT24)
#define		ECC_MECCCAP_LR_PE4CL2_DESPID_23					(BIT23)
#define		ECC_MECCCAP_LR_PE4CL2_DESPID_22					(BIT22)
#define		ECC_MECCCAP_LR_PE4CL2_DESPID_21					(BIT21)
#define		ECC_MECCCAP_LR_PE4CL2_DESPID_20					(BIT20)
#define		ECC_MECCCAP_LR_PE4CL2_DESPID_19					(BIT19)
#define		ECC_MECCCAP_LR_PE4CL2_DESPID_18					(BIT18)
#define		ECC_MECCCAP_LR_PE4CL2_DESPID_17					(BIT17)
#define		ECC_MECCCAP_LR_PE4CL2_DESPID_16					(BIT16)
#define		ECC_MECCCAP_LR_PE4CL2_DESPID_15					(BIT15)
#define		ECC_MECCCAP_LR_PE4CL2_DESPID_14					(BIT14)
#define		ECC_MECCCAP_LR_PE4CL2_DESPID_13					(BIT13)
#define		ECC_MECCCAP_LR_PE4CL2_DESPID_12					(BIT12)
#define		ECC_MECCCAP_LR_PE4CL2_DESPID_11					(BIT11)
#define		ECC_MECCCAP_LR_PE4CL2_DESPID_10					(BIT10)
#define		ECC_MECCCAP_LR_PE4CL2_DESPID_9					(BIT9)
#define		ECC_MECCCAP_LR_PE4CL2_DESPID_8					(BIT8)
#define		ECC_MECCCAP_LR_PE4CL2_DESPID_7					(BIT7)
#define		ECC_MECCCAP_LR_PE4CL2_DESPID_6					(BIT6)
#define		ECC_MECCCAP_LR_PE4CL2_DESPID_5					(BIT5)
#define		ECC_MECCCAP_LR_PE4CL2_DESPID_4					(BIT4)
#define		ECC_MECCCAP_LR_PE4CL2_DESPID_3					(BIT3)
#define		ECC_MECCCAP_LR_PE4CL2_DESPID_2					(BIT2)
#define		ECC_MECCCAP_LR_PE4CL2_DESPID_1					(BIT1)
#define		ECC_MECCCAP_LR_PE4CL2_DESPID_0					(BIT0)
/* LR0_00SESPIDCLR */
#define		ECC_MECCCAP_LR_PE4CL2_SSPIDC_31					(BIT31)
#define		ECC_MECCCAP_LR_PE4CL2_SSPIDC_30					(BIT30)
#define		ECC_MECCCAP_LR_PE4CL2_SSPIDC_29					(BIT29)
#define		ECC_MECCCAP_LR_PE4CL2_SSPIDC_28					(BIT28)
#define		ECC_MECCCAP_LR_PE4CL2_SSPIDC_27					(BIT27)
#define		ECC_MECCCAP_LR_PE4CL2_SSPIDC_26					(BIT26)
#define		ECC_MECCCAP_LR_PE4CL2_SSPIDC_25					(BIT25)
#define		ECC_MECCCAP_LR_PE4CL2_SSPIDC_24					(BIT24)
#define		ECC_MECCCAP_LR_PE4CL2_SSPIDC_23					(BIT23)
#define		ECC_MECCCAP_LR_PE4CL2_SSPIDC_22					(BIT22)
#define		ECC_MECCCAP_LR_PE4CL2_SSPIDC_21					(BIT21)
#define		ECC_MECCCAP_LR_PE4CL2_SSPIDC_20					(BIT20)
#define		ECC_MECCCAP_LR_PE4CL2_SSPIDC_19					(BIT19)
#define		ECC_MECCCAP_LR_PE4CL2_SSPIDC_18					(BIT18)
#define		ECC_MECCCAP_LR_PE4CL2_SSPIDC_17					(BIT17)
#define		ECC_MECCCAP_LR_PE4CL2_SSPIDC_16					(BIT16)
#define		ECC_MECCCAP_LR_PE4CL2_SSPIDC_15					(BIT15)
#define		ECC_MECCCAP_LR_PE4CL2_SSPIDC_14					(BIT14)
#define		ECC_MECCCAP_LR_PE4CL2_SSPIDC_13					(BIT13)
#define		ECC_MECCCAP_LR_PE4CL2_SSPIDC_12					(BIT12)
#define		ECC_MECCCAP_LR_PE4CL2_SSPIDC_11					(BIT11)
#define		ECC_MECCCAP_LR_PE4CL2_SSPIDC_10					(BIT10)
#define		ECC_MECCCAP_LR_PE4CL2_SSPIDC_9					(BIT9)
#define		ECC_MECCCAP_LR_PE4CL2_SSPIDC_8					(BIT8)
#define		ECC_MECCCAP_LR_PE4CL2_SSPIDC_7					(BIT7)
#define		ECC_MECCCAP_LR_PE4CL2_SSPIDC_6					(BIT6)
#define		ECC_MECCCAP_LR_PE4CL2_SSPIDC_5					(BIT5)
#define		ECC_MECCCAP_LR_PE4CL2_SSPIDC_4					(BIT4)
#define		ECC_MECCCAP_LR_PE4CL2_SSPIDC_3					(BIT3)
#define		ECC_MECCCAP_LR_PE4CL2_SSPIDC_2					(BIT2)
#define		ECC_MECCCAP_LR_PE4CL2_SSPIDC_1					(BIT1)
#define		ECC_MECCCAP_LR_PE4CL2_SSPIDC_0					(BIT0)
	#define	   ECC_MECCCAP_LR_PE4CL2_00SESPIDCLR_CLEAR		(1)
/* LR0_00SESPID */
#define		ECC_MECCCAP_LR_PE4CL2_SESPID_31					(BIT31)
#define		ECC_MECCCAP_LR_PE4CL2_SESPID_30					(BIT30)
#define		ECC_MECCCAP_LR_PE4CL2_SESPID_29					(BIT29)
#define		ECC_MECCCAP_LR_PE4CL2_SESPID_28					(BIT28)
#define		ECC_MECCCAP_LR_PE4CL2_SESPID_27					(BIT27)
#define		ECC_MECCCAP_LR_PE4CL2_SESPID_26					(BIT26)
#define		ECC_MECCCAP_LR_PE4CL2_SESPID_25					(BIT25)
#define		ECC_MECCCAP_LR_PE4CL2_SESPID_24					(BIT24)
#define		ECC_MECCCAP_LR_PE4CL2_SESPID_23					(BIT23)
#define		ECC_MECCCAP_LR_PE4CL2_SESPID_22					(BIT22)
#define		ECC_MECCCAP_LR_PE4CL2_SESPID_21					(BIT21)
#define		ECC_MECCCAP_LR_PE4CL2_SESPID_20					(BIT20)
#define		ECC_MECCCAP_LR_PE4CL2_SESPID_19					(BIT19)
#define		ECC_MECCCAP_LR_PE4CL2_SESPID_18					(BIT18)
#define		ECC_MECCCAP_LR_PE4CL2_SESPID_17					(BIT17)
#define		ECC_MECCCAP_LR_PE4CL2_SESPID_16					(BIT16)
#define		ECC_MECCCAP_LR_PE4CL2_SESPID_15					(BIT15)
#define		ECC_MECCCAP_LR_PE4CL2_SESPID_14					(BIT14)
#define		ECC_MECCCAP_LR_PE4CL2_SESPID_13					(BIT13)
#define		ECC_MECCCAP_LR_PE4CL2_SESPID_12					(BIT12)
#define		ECC_MECCCAP_LR_PE4CL2_SESPID_11					(BIT11)
#define		ECC_MECCCAP_LR_PE4CL2_SESPID_10					(BIT10)
#define		ECC_MECCCAP_LR_PE4CL2_SESPID_9					(BIT9)
#define		ECC_MECCCAP_LR_PE4CL2_SESPID_8					(BIT8)
#define		ECC_MECCCAP_LR_PE4CL2_SESPID_7					(BIT7)
#define		ECC_MECCCAP_LR_PE4CL2_SESPID_6					(BIT6)
#define		ECC_MECCCAP_LR_PE4CL2_SESPID_5					(BIT5)
#define		ECC_MECCCAP_LR_PE4CL2_SESPID_4					(BIT4)
#define		ECC_MECCCAP_LR_PE4CL2_SESPID_3					(BIT3)
#define		ECC_MECCCAP_LR_PE4CL2_SESPID_2					(BIT2)
#define		ECC_MECCCAP_LR_PE4CL2_SESPID_1					(BIT1)
#define		ECC_MECCCAP_LR_PE4CL2_SESPID_0					(BIT0)

/* Module: MECCCAP_LR_PE5CL2 */
/* LR0_ERRINT */
#define		ECC_MECCCAP_LR_PE5CL2_ERINT_SEOVFIE				(BIT7)
#define		ECC_MECCCAP_LR_PE5CL2_ERINT_AFEIE				(BIT3)
#define		ECC_MECCCAP_LR_PE5CL2_ERINT_DEDIE				(BIT1)
#define		ECC_MECCCAP_LR_PE5CL2_ERINT_SEDIE				(BIT0)
	#define		ECC_MECCCAP_LR_PE5CL2_ERRINT_DISABLE		(0)
	#define		ECC_MECCCAP_LR_PE5CL2_ERRINT_ENABLE			(1)
/* LR0_SSTCLR */
#define		ECC_MECCCAP_LR_PE5CL2_SSTCLR_07					(BIT7)
#define		ECC_MECCCAP_LR_PE5CL2_SSTCLR_06					(BIT6)
#define		ECC_MECCCAP_LR_PE5CL2_SSTCLR_05					(BIT5)
#define		ECC_MECCCAP_LR_PE5CL2_SSTCLR_04					(BIT4)
#define		ECC_MECCCAP_LR_PE5CL2_SSTCLR_03					(BIT3)
#define		ECC_MECCCAP_LR_PE5CL2_SSTCLR_02					(BIT2)
#define		ECC_MECCCAP_LR_PE5CL2_SSTCLR_01					(BIT1)
#define		ECC_MECCCAP_LR_PE5CL2_SSTCLR_00					(BIT0)
	#define		ECC_MECCCAP_LR_PE5CL2_SSTCLR_CLEAR			(1)
/* LR0_DSTCLR */
#define		ECC_MECCCAP_LR_PE5CL2_DSTCLR_DSTCLR00			(BIT0)
	#define		ECC_MECCCAP_LR_PE5CL2_DSTCLR_CLEAR			(1)
/* LR0_OVFCLR */
#define		ECC_MECCCAP_LR_PE5CL2_OVFCLR_1					(BIT1)
#define		ECC_MECCCAP_LR_PE5CL2_OVFCLR_0					(BIT0)
	#define		ECC_MECCCAP_LR_PE5CL2_OVFCLR_CLEAR			(1)
/* LR0_SERSTR */
#define		ECC_MECCCAP_LR_PE5CL2_SERSTR_07					(BIT7)
#define		ECC_MECCCAP_LR_PE5CL2_SERSTR_06					(BIT6)
#define		ECC_MECCCAP_LR_PE5CL2_SERSTR_05					(BIT5)
#define		ECC_MECCCAP_LR_PE5CL2_SERSTR_04					(BIT4)
#define		ECC_MECCCAP_LR_PE5CL2_SERSTR_03					(BIT3)
#define		ECC_MECCCAP_LR_PE5CL2_SERSTR_02					(BIT2)
#define		ECC_MECCCAP_LR_PE5CL2_SERSTR_01					(BIT1)
#define		ECC_MECCCAP_LR_PE5CL2_SERSTR_00					(BIT0)
/* LR0_DERSTR */
#define		ECC_MECCCAP_LR_PE5CL2_DERSTR_AFEF00				(BIT3)
#define		ECC_MECCCAP_LR_PE5CL2_DERSTR_DEDF00				(BIT1)
/* LR0_OVFSTR */
#define		ECC_MECCCAP_LR_PE5CL2_OVFSTR_1					(BIT1)
#define		ECC_MECCCAP_LR_PE5CL2_OVFSTR_0					(BIT0)
/* LR0_SERINF */
#define		ECC_MECCCAP_LR_PE5CL2_SERINF_04					(BIT4)
#define		ECC_MECCCAP_LR_PE5CL2_SERINF_03					(BIT3)
#define		ECC_MECCCAP_LR_PE5CL2_SERINF_02					(BIT2)
#define		ECC_MECCCAP_LR_PE5CL2_SERINF_01					(BIT1)
#define		ECC_MECCCAP_LR_PE5CL2_SERINF_00					(BIT0)
/* LR0_nSEADR */
#define		ECC_MECCCAP_LR_PE5CL2_SEADR_SEDL				(BIT31 + BIT30 + BIT29 + BIT28 + BIT27)
#define		ECC_MECCCAP_LR_PE5CL2_SEADR_SEADR0				(0x0000FFFCU)
/* LR0_00DEADR */
#define		ECC_MECCCAP_LR_PE5CL2_DEADR_DEDL				(BIT31 + BIT30 + BIT29 + BIT28 + BIT27)
#define		ECC_MECCCAP_LR_PE5CL2_DEADR_DEADR0				(0x0000FFFCU)
/* LR0_00DESPIDCLR */
#define		ECC_MECCCAP_LR_PE5CL2_DSPIDC_31					(BIT31)
#define		ECC_MECCCAP_LR_PE5CL2_DSPIDC_30					(BIT30)
#define		ECC_MECCCAP_LR_PE5CL2_DSPIDC_29					(BIT29)
#define		ECC_MECCCAP_LR_PE5CL2_DSPIDC_28					(BIT28)
#define		ECC_MECCCAP_LR_PE5CL2_DSPIDC_27					(BIT27)
#define		ECC_MECCCAP_LR_PE5CL2_DSPIDC_26					(BIT26)
#define		ECC_MECCCAP_LR_PE5CL2_DSPIDC_25					(BIT25)
#define		ECC_MECCCAP_LR_PE5CL2_DSPIDC_24					(BIT24)
#define		ECC_MECCCAP_LR_PE5CL2_DSPIDC_23					(BIT23)
#define		ECC_MECCCAP_LR_PE5CL2_DSPIDC_22					(BIT22)
#define		ECC_MECCCAP_LR_PE5CL2_DSPIDC_21					(BIT21)
#define		ECC_MECCCAP_LR_PE5CL2_DSPIDC_20					(BIT20)
#define		ECC_MECCCAP_LR_PE5CL2_DSPIDC_19					(BIT19)
#define		ECC_MECCCAP_LR_PE5CL2_DSPIDC_18					(BIT18)
#define		ECC_MECCCAP_LR_PE5CL2_DSPIDC_17					(BIT17)
#define		ECC_MECCCAP_LR_PE5CL2_DSPIDC_16					(BIT16)
#define		ECC_MECCCAP_LR_PE5CL2_DSPIDC_15					(BIT15)
#define		ECC_MECCCAP_LR_PE5CL2_DSPIDC_14					(BIT14)
#define		ECC_MECCCAP_LR_PE5CL2_DSPIDC_13					(BIT13)
#define		ECC_MECCCAP_LR_PE5CL2_DSPIDC_12					(BIT12)
#define		ECC_MECCCAP_LR_PE5CL2_DSPIDC_11					(BIT11)
#define		ECC_MECCCAP_LR_PE5CL2_DSPIDC_10					(BIT10)
#define		ECC_MECCCAP_LR_PE5CL2_DSPIDC_9					(BIT9)
#define		ECC_MECCCAP_LR_PE5CL2_DSPIDC_8					(BIT8)
#define		ECC_MECCCAP_LR_PE5CL2_DSPIDC_7					(BIT7)
#define		ECC_MECCCAP_LR_PE5CL2_DSPIDC_6					(BIT6)
#define		ECC_MECCCAP_LR_PE5CL2_DSPIDC_5					(BIT5)
#define		ECC_MECCCAP_LR_PE5CL2_DSPIDC_4					(BIT4)
#define		ECC_MECCCAP_LR_PE5CL2_DSPIDC_3					(BIT3)
#define		ECC_MECCCAP_LR_PE5CL2_DSPIDC_2					(BIT2)
#define		ECC_MECCCAP_LR_PE5CL2_DSPIDC_1					(BIT1)
#define		ECC_MECCCAP_LR_PE5CL2_DSPIDC_0					(BIT0)
	#define	   ECC_MECCCAP_LR_PE5CL2_00DESPIDCLR_CLEAR		(1)
/* LR0_00DESPID */
#define		ECC_MECCCAP_LR_PE5CL2_DESPID_31					(BIT31)
#define		ECC_MECCCAP_LR_PE5CL2_DESPID_30					(BIT30)
#define		ECC_MECCCAP_LR_PE5CL2_DESPID_29					(BIT29)
#define		ECC_MECCCAP_LR_PE5CL2_DESPID_28					(BIT28)
#define		ECC_MECCCAP_LR_PE5CL2_DESPID_27					(BIT27)
#define		ECC_MECCCAP_LR_PE5CL2_DESPID_26					(BIT26)
#define		ECC_MECCCAP_LR_PE5CL2_DESPID_25					(BIT25)
#define		ECC_MECCCAP_LR_PE5CL2_DESPID_24					(BIT24)
#define		ECC_MECCCAP_LR_PE5CL2_DESPID_23					(BIT23)
#define		ECC_MECCCAP_LR_PE5CL2_DESPID_22					(BIT22)
#define		ECC_MECCCAP_LR_PE5CL2_DESPID_21					(BIT21)
#define		ECC_MECCCAP_LR_PE5CL2_DESPID_20					(BIT20)
#define		ECC_MECCCAP_LR_PE5CL2_DESPID_19					(BIT19)
#define		ECC_MECCCAP_LR_PE5CL2_DESPID_18					(BIT18)
#define		ECC_MECCCAP_LR_PE5CL2_DESPID_17					(BIT17)
#define		ECC_MECCCAP_LR_PE5CL2_DESPID_16					(BIT16)
#define		ECC_MECCCAP_LR_PE5CL2_DESPID_15					(BIT15)
#define		ECC_MECCCAP_LR_PE5CL2_DESPID_14					(BIT14)
#define		ECC_MECCCAP_LR_PE5CL2_DESPID_13					(BIT13)
#define		ECC_MECCCAP_LR_PE5CL2_DESPID_12					(BIT12)
#define		ECC_MECCCAP_LR_PE5CL2_DESPID_11					(BIT11)
#define		ECC_MECCCAP_LR_PE5CL2_DESPID_10					(BIT10)
#define		ECC_MECCCAP_LR_PE5CL2_DESPID_9					(BIT9)
#define		ECC_MECCCAP_LR_PE5CL2_DESPID_8					(BIT8)
#define		ECC_MECCCAP_LR_PE5CL2_DESPID_7					(BIT7)
#define		ECC_MECCCAP_LR_PE5CL2_DESPID_6					(BIT6)
#define		ECC_MECCCAP_LR_PE5CL2_DESPID_5					(BIT5)
#define		ECC_MECCCAP_LR_PE5CL2_DESPID_4					(BIT4)
#define		ECC_MECCCAP_LR_PE5CL2_DESPID_3					(BIT3)
#define		ECC_MECCCAP_LR_PE5CL2_DESPID_2					(BIT2)
#define		ECC_MECCCAP_LR_PE5CL2_DESPID_1					(BIT1)
#define		ECC_MECCCAP_LR_PE5CL2_DESPID_0					(BIT0)
/* LR0_00SESPIDCLR */
#define		ECC_MECCCAP_LR_PE5CL2_SSPIDC_31					(BIT31)
#define		ECC_MECCCAP_LR_PE5CL2_SSPIDC_30					(BIT30)
#define		ECC_MECCCAP_LR_PE5CL2_SSPIDC_29					(BIT29)
#define		ECC_MECCCAP_LR_PE5CL2_SSPIDC_28					(BIT28)
#define		ECC_MECCCAP_LR_PE5CL2_SSPIDC_27					(BIT27)
#define		ECC_MECCCAP_LR_PE5CL2_SSPIDC_26					(BIT26)
#define		ECC_MECCCAP_LR_PE5CL2_SSPIDC_25					(BIT25)
#define		ECC_MECCCAP_LR_PE5CL2_SSPIDC_24					(BIT24)
#define		ECC_MECCCAP_LR_PE5CL2_SSPIDC_23					(BIT23)
#define		ECC_MECCCAP_LR_PE5CL2_SSPIDC_22					(BIT22)
#define		ECC_MECCCAP_LR_PE5CL2_SSPIDC_21					(BIT21)
#define		ECC_MECCCAP_LR_PE5CL2_SSPIDC_20					(BIT20)
#define		ECC_MECCCAP_LR_PE5CL2_SSPIDC_19					(BIT19)
#define		ECC_MECCCAP_LR_PE5CL2_SSPIDC_18					(BIT18)
#define		ECC_MECCCAP_LR_PE5CL2_SSPIDC_17					(BIT17)
#define		ECC_MECCCAP_LR_PE5CL2_SSPIDC_16					(BIT16)
#define		ECC_MECCCAP_LR_PE5CL2_SSPIDC_15					(BIT15)
#define		ECC_MECCCAP_LR_PE5CL2_SSPIDC_14					(BIT14)
#define		ECC_MECCCAP_LR_PE5CL2_SSPIDC_13					(BIT13)
#define		ECC_MECCCAP_LR_PE5CL2_SSPIDC_12					(BIT12)
#define		ECC_MECCCAP_LR_PE5CL2_SSPIDC_11					(BIT11)
#define		ECC_MECCCAP_LR_PE5CL2_SSPIDC_10					(BIT10)
#define		ECC_MECCCAP_LR_PE5CL2_SSPIDC_9					(BIT9)
#define		ECC_MECCCAP_LR_PE5CL2_SSPIDC_8					(BIT8)
#define		ECC_MECCCAP_LR_PE5CL2_SSPIDC_7					(BIT7)
#define		ECC_MECCCAP_LR_PE5CL2_SSPIDC_6					(BIT6)
#define		ECC_MECCCAP_LR_PE5CL2_SSPIDC_5					(BIT5)
#define		ECC_MECCCAP_LR_PE5CL2_SSPIDC_4					(BIT4)
#define		ECC_MECCCAP_LR_PE5CL2_SSPIDC_3					(BIT3)
#define		ECC_MECCCAP_LR_PE5CL2_SSPIDC_2					(BIT2)
#define		ECC_MECCCAP_LR_PE5CL2_SSPIDC_1					(BIT1)
#define		ECC_MECCCAP_LR_PE5CL2_SSPIDC_0					(BIT0)
	#define	   ECC_MECCCAP_LR_PE5CL2_00SESPIDCLR_CLEAR		(1)
/* LR0_00SESPID */
#define		ECC_MECCCAP_LR_PE5CL2_SESPID_31					(BIT31)
#define		ECC_MECCCAP_LR_PE5CL2_SESPID_30					(BIT30)
#define		ECC_MECCCAP_LR_PE5CL2_SESPID_29					(BIT29)
#define		ECC_MECCCAP_LR_PE5CL2_SESPID_28					(BIT28)
#define		ECC_MECCCAP_LR_PE5CL2_SESPID_27					(BIT27)
#define		ECC_MECCCAP_LR_PE5CL2_SESPID_26					(BIT26)
#define		ECC_MECCCAP_LR_PE5CL2_SESPID_25					(BIT25)
#define		ECC_MECCCAP_LR_PE5CL2_SESPID_24					(BIT24)
#define		ECC_MECCCAP_LR_PE5CL2_SESPID_23					(BIT23)
#define		ECC_MECCCAP_LR_PE5CL2_SESPID_22					(BIT22)
#define		ECC_MECCCAP_LR_PE5CL2_SESPID_21					(BIT21)
#define		ECC_MECCCAP_LR_PE5CL2_SESPID_20					(BIT20)
#define		ECC_MECCCAP_LR_PE5CL2_SESPID_19					(BIT19)
#define		ECC_MECCCAP_LR_PE5CL2_SESPID_18					(BIT18)
#define		ECC_MECCCAP_LR_PE5CL2_SESPID_17					(BIT17)
#define		ECC_MECCCAP_LR_PE5CL2_SESPID_16					(BIT16)
#define		ECC_MECCCAP_LR_PE5CL2_SESPID_15					(BIT15)
#define		ECC_MECCCAP_LR_PE5CL2_SESPID_14					(BIT14)
#define		ECC_MECCCAP_LR_PE5CL2_SESPID_13					(BIT13)
#define		ECC_MECCCAP_LR_PE5CL2_SESPID_12					(BIT12)
#define		ECC_MECCCAP_LR_PE5CL2_SESPID_11					(BIT11)
#define		ECC_MECCCAP_LR_PE5CL2_SESPID_10					(BIT10)
#define		ECC_MECCCAP_LR_PE5CL2_SESPID_9					(BIT9)
#define		ECC_MECCCAP_LR_PE5CL2_SESPID_8					(BIT8)
#define		ECC_MECCCAP_LR_PE5CL2_SESPID_7					(BIT7)
#define		ECC_MECCCAP_LR_PE5CL2_SESPID_6					(BIT6)
#define		ECC_MECCCAP_LR_PE5CL2_SESPID_5					(BIT5)
#define		ECC_MECCCAP_LR_PE5CL2_SESPID_4					(BIT4)
#define		ECC_MECCCAP_LR_PE5CL2_SESPID_3					(BIT3)
#define		ECC_MECCCAP_LR_PE5CL2_SESPID_2					(BIT2)
#define		ECC_MECCCAP_LR_PE5CL2_SESPID_1					(BIT1)
#define		ECC_MECCCAP_LR_PE5CL2_SESPID_0					(BIT0)

/* Module: MECCCAP_LRA */
/* LR1_ERRINT */
#define		ECC_MECCCAP_LRA_LR1_ERRINT_SEOVFIE				(BIT7)
#define		ECC_MECCCAP_LRA_LR1_ERRINT_DEDIE				(BIT1)
#define		ECC_MECCCAP_LRA_LR1_ERRINT_SEDIE				(BIT0)
	#define		ECC_MECCCAP_LRA_LR1_ERRINT_DISABLE			(0)
	#define		ECC_MECCCAP_LRA_LR1_ERRINT_ENABLE			(1)
/* LR1_SSTCLR */
#define		ECC_MECCCAP_LRA_LR1_SSTCLR_07					(BIT7)
#define		ECC_MECCCAP_LRA_LR1_SSTCLR_06					(BIT6)
#define		ECC_MECCCAP_LRA_LR1_SSTCLR_05					(BIT5)
#define		ECC_MECCCAP_LRA_LR1_SSTCLR_04					(BIT4)
#define		ECC_MECCCAP_LRA_LR1_SSTCLR_03					(BIT3)
#define		ECC_MECCCAP_LRA_LR1_SSTCLR_02					(BIT2)
#define		ECC_MECCCAP_LRA_LR1_SSTCLR_01					(BIT1)
#define		ECC_MECCCAP_LRA_LR1_SSTCLR_00					(BIT0)
	#define		ECC_MECCCAP_LRA_LR1_SSTCLR_CLEAR			(1)
/* LR1_DSTCLR */
#define		ECC_MECCCAP_LRA_LR1_DSTCLR_DSTCLR00				(BIT0)
	#define		ECC_MECCCAP_LRA_LR1_DSTCLR_CLEAR			(1)
/* LR1_OVFCLR */
#define		ECC_MECCCAP_LRA_LR1_OVFCLR_1					(BIT1)
#define		ECC_MECCCAP_LRA_LR1_OVFCLR_0					(BIT0)
	#define		ECC_MECCCAP_LRA_LR1_OVFCLR_CLEAR			(1)
/* LR1_SERSTR */
#define		ECC_MECCCAP_LRA_LR1_SERSTR_07					(BIT7)
#define		ECC_MECCCAP_LRA_LR1_SERSTR_06					(BIT6)
#define		ECC_MECCCAP_LRA_LR1_SERSTR_05					(BIT5)
#define		ECC_MECCCAP_LRA_LR1_SERSTR_04					(BIT4)
#define		ECC_MECCCAP_LRA_LR1_SERSTR_03					(BIT3)
#define		ECC_MECCCAP_LRA_LR1_SERSTR_02					(BIT2)
#define		ECC_MECCCAP_LRA_LR1_SERSTR_01					(BIT1)
#define		ECC_MECCCAP_LRA_LR1_SERSTR_00					(BIT0)
/* LR1_DERSTR */
#define		ECC_MECCCAP_LRA_LR1_DERSTR_DEDF00				(BIT1)
/* LR1_OVFSTR */
#define		ECC_MECCCAP_LRA_LR1_OVFSTR_1					(BIT1)
#define		ECC_MECCCAP_LRA_LR1_OVFSTR_0					(BIT0)
/* LR1_SERINF */
#define		ECC_MECCCAP_LRA_LR1_SERINF_05					(BIT5)
#define		ECC_MECCCAP_LRA_LR1_SERINF_04					(BIT4)
#define		ECC_MECCCAP_LRA_LR1_SERINF_03					(BIT3)
#define		ECC_MECCCAP_LRA_LR1_SERINF_02					(BIT2)
#define		ECC_MECCCAP_LRA_LR1_SERINF_01					(BIT1)
#define		ECC_MECCCAP_LRA_LR1_SERINF_00					(BIT0)
/* LR1_nSEADR */
#define		ECC_MECCCAP_LRA_LR1_SEADR_SEDL					(BIT31 + BIT30 + BIT29 + BIT28 + BIT27)
#define		ECC_MECCCAP_LRA_LR1_SEADR_SEADR0				(0x01FFFFFCU)
/* LR1_00DEADR */
#define		ECC_MECCCAP_LRA_LR1_DEADR_DEDL					(BIT31 + BIT30 + BIT29 + BIT28 + BIT27)
#define		ECC_MECCCAP_LRA_LR1_DEADR_DEADR0				(0x01FFFFFCU)
/* LR1_00DESPIDCLR */
#define		ECC_MECCCAP_LRA_LR1_DSPIDC_31					(BIT31)
#define		ECC_MECCCAP_LRA_LR1_DSPIDC_30					(BIT30)
#define		ECC_MECCCAP_LRA_LR1_DSPIDC_29					(BIT29)
#define		ECC_MECCCAP_LRA_LR1_DSPIDC_28					(BIT28)
#define		ECC_MECCCAP_LRA_LR1_DSPIDC_27					(BIT27)
#define		ECC_MECCCAP_LRA_LR1_DSPIDC_26					(BIT26)
#define		ECC_MECCCAP_LRA_LR1_DSPIDC_25					(BIT25)
#define		ECC_MECCCAP_LRA_LR1_DSPIDC_24					(BIT24)
#define		ECC_MECCCAP_LRA_LR1_DSPIDC_23					(BIT23)
#define		ECC_MECCCAP_LRA_LR1_DSPIDC_22					(BIT22)
#define		ECC_MECCCAP_LRA_LR1_DSPIDC_21					(BIT21)
#define		ECC_MECCCAP_LRA_LR1_DSPIDC_20					(BIT20)
#define		ECC_MECCCAP_LRA_LR1_DSPIDC_19					(BIT19)
#define		ECC_MECCCAP_LRA_LR1_DSPIDC_18					(BIT18)
#define		ECC_MECCCAP_LRA_LR1_DSPIDC_17					(BIT17)
#define		ECC_MECCCAP_LRA_LR1_DSPIDC_16					(BIT16)
#define		ECC_MECCCAP_LRA_LR1_DSPIDC_15					(BIT15)
#define		ECC_MECCCAP_LRA_LR1_DSPIDC_14					(BIT14)
#define		ECC_MECCCAP_LRA_LR1_DSPIDC_13					(BIT13)
#define		ECC_MECCCAP_LRA_LR1_DSPIDC_12					(BIT12)
#define		ECC_MECCCAP_LRA_LR1_DSPIDC_11					(BIT11)
#define		ECC_MECCCAP_LRA_LR1_DSPIDC_10					(BIT10)
#define		ECC_MECCCAP_LRA_LR1_DSPIDC_9					(BIT9)
#define		ECC_MECCCAP_LRA_LR1_DSPIDC_8					(BIT8)
#define		ECC_MECCCAP_LRA_LR1_DSPIDC_7					(BIT7)
#define		ECC_MECCCAP_LRA_LR1_DSPIDC_6					(BIT6)
#define		ECC_MECCCAP_LRA_LR1_DSPIDC_5					(BIT5)
#define		ECC_MECCCAP_LRA_LR1_DSPIDC_4					(BIT4)
#define		ECC_MECCCAP_LRA_LR1_DSPIDC_3					(BIT3)
#define		ECC_MECCCAP_LRA_LR1_DSPIDC_2					(BIT2)
#define		ECC_MECCCAP_LRA_LR1_DSPIDC_1					(BIT1)
#define		ECC_MECCCAP_LRA_LR1_DSPIDC_0					(BIT0)
	#define	   ECC_MECCCAP_LRA_LR1_00DESPIDCLR_CLEAR		(1)
/* LR1_00DESPID */
#define		ECC_MECCCAP_LRA_LR1_DESPID_31					(BIT31)
#define		ECC_MECCCAP_LRA_LR1_DESPID_30					(BIT30)
#define		ECC_MECCCAP_LRA_LR1_DESPID_29					(BIT29)
#define		ECC_MECCCAP_LRA_LR1_DESPID_28					(BIT28)
#define		ECC_MECCCAP_LRA_LR1_DESPID_27					(BIT27)
#define		ECC_MECCCAP_LRA_LR1_DESPID_26					(BIT26)
#define		ECC_MECCCAP_LRA_LR1_DESPID_25					(BIT25)
#define		ECC_MECCCAP_LRA_LR1_DESPID_24					(BIT24)
#define		ECC_MECCCAP_LRA_LR1_DESPID_23					(BIT23)
#define		ECC_MECCCAP_LRA_LR1_DESPID_22					(BIT22)
#define		ECC_MECCCAP_LRA_LR1_DESPID_21					(BIT21)
#define		ECC_MECCCAP_LRA_LR1_DESPID_20					(BIT20)
#define		ECC_MECCCAP_LRA_LR1_DESPID_19					(BIT19)
#define		ECC_MECCCAP_LRA_LR1_DESPID_18					(BIT18)
#define		ECC_MECCCAP_LRA_LR1_DESPID_17					(BIT17)
#define		ECC_MECCCAP_LRA_LR1_DESPID_16					(BIT16)
#define		ECC_MECCCAP_LRA_LR1_DESPID_15					(BIT15)
#define		ECC_MECCCAP_LRA_LR1_DESPID_14					(BIT14)
#define		ECC_MECCCAP_LRA_LR1_DESPID_13					(BIT13)
#define		ECC_MECCCAP_LRA_LR1_DESPID_12					(BIT12)
#define		ECC_MECCCAP_LRA_LR1_DESPID_11					(BIT11)
#define		ECC_MECCCAP_LRA_LR1_DESPID_10					(BIT10)
#define		ECC_MECCCAP_LRA_LR1_DESPID_9					(BIT9)
#define		ECC_MECCCAP_LRA_LR1_DESPID_8					(BIT8)
#define		ECC_MECCCAP_LRA_LR1_DESPID_7					(BIT7)
#define		ECC_MECCCAP_LRA_LR1_DESPID_6					(BIT6)
#define		ECC_MECCCAP_LRA_LR1_DESPID_5					(BIT5)
#define		ECC_MECCCAP_LRA_LR1_DESPID_4					(BIT4)
#define		ECC_MECCCAP_LRA_LR1_DESPID_3					(BIT3)
#define		ECC_MECCCAP_LRA_LR1_DESPID_2					(BIT2)
#define		ECC_MECCCAP_LRA_LR1_DESPID_1					(BIT1)
#define		ECC_MECCCAP_LRA_LR1_DESPID_0					(BIT0)
/* LR1_00SESPIDCLR */
#define		ECC_MECCCAP_LRA_LR1_SSPIDC_31					(BIT31)
#define		ECC_MECCCAP_LRA_LR1_SSPIDC_30					(BIT30)
#define		ECC_MECCCAP_LRA_LR1_SSPIDC_29					(BIT29)
#define		ECC_MECCCAP_LRA_LR1_SSPIDC_28					(BIT28)
#define		ECC_MECCCAP_LRA_LR1_SSPIDC_27					(BIT27)
#define		ECC_MECCCAP_LRA_LR1_SSPIDC_26					(BIT26)
#define		ECC_MECCCAP_LRA_LR1_SSPIDC_25					(BIT25)
#define		ECC_MECCCAP_LRA_LR1_SSPIDC_24					(BIT24)
#define		ECC_MECCCAP_LRA_LR1_SSPIDC_23					(BIT23)
#define		ECC_MECCCAP_LRA_LR1_SSPIDC_22					(BIT22)
#define		ECC_MECCCAP_LRA_LR1_SSPIDC_21					(BIT21)
#define		ECC_MECCCAP_LRA_LR1_SSPIDC_20					(BIT20)
#define		ECC_MECCCAP_LRA_LR1_SSPIDC_19					(BIT19)
#define		ECC_MECCCAP_LRA_LR1_SSPIDC_18					(BIT18)
#define		ECC_MECCCAP_LRA_LR1_SSPIDC_17					(BIT17)
#define		ECC_MECCCAP_LRA_LR1_SSPIDC_16					(BIT16)
#define		ECC_MECCCAP_LRA_LR1_SSPIDC_15					(BIT15)
#define		ECC_MECCCAP_LRA_LR1_SSPIDC_14					(BIT14)
#define		ECC_MECCCAP_LRA_LR1_SSPIDC_13					(BIT13)
#define		ECC_MECCCAP_LRA_LR1_SSPIDC_12					(BIT12)
#define		ECC_MECCCAP_LRA_LR1_SSPIDC_11					(BIT11)
#define		ECC_MECCCAP_LRA_LR1_SSPIDC_10					(BIT10)
#define		ECC_MECCCAP_LRA_LR1_SSPIDC_9					(BIT9)
#define		ECC_MECCCAP_LRA_LR1_SSPIDC_8					(BIT8)
#define		ECC_MECCCAP_LRA_LR1_SSPIDC_7					(BIT7)
#define		ECC_MECCCAP_LRA_LR1_SSPIDC_6					(BIT6)
#define		ECC_MECCCAP_LRA_LR1_SSPIDC_5					(BIT5)
#define		ECC_MECCCAP_LRA_LR1_SSPIDC_4					(BIT4)
#define		ECC_MECCCAP_LRA_LR1_SSPIDC_3					(BIT3)
#define		ECC_MECCCAP_LRA_LR1_SSPIDC_2					(BIT2)
#define		ECC_MECCCAP_LRA_LR1_SSPIDC_1					(BIT1)
#define		ECC_MECCCAP_LRA_LR1_SSPIDC_0					(BIT0)
	#define	   ECC_MECCCAP_LRA_LR1_00SESPIDCLR_CLEAR		(1)
/* LR1_00SESPID */
#define		ECC_MECCCAP_LRA_LR1_SESPID_31					(BIT31)
#define		ECC_MECCCAP_LRA_LR1_SESPID_30					(BIT30)
#define		ECC_MECCCAP_LRA_LR1_SESPID_29					(BIT29)
#define		ECC_MECCCAP_LRA_LR1_SESPID_28					(BIT28)
#define		ECC_MECCCAP_LRA_LR1_SESPID_27					(BIT27)
#define		ECC_MECCCAP_LRA_LR1_SESPID_26					(BIT26)
#define		ECC_MECCCAP_LRA_LR1_SESPID_25					(BIT25)
#define		ECC_MECCCAP_LRA_LR1_SESPID_24					(BIT24)
#define		ECC_MECCCAP_LRA_LR1_SESPID_23					(BIT23)
#define		ECC_MECCCAP_LRA_LR1_SESPID_22					(BIT22)
#define		ECC_MECCCAP_LRA_LR1_SESPID_21					(BIT21)
#define		ECC_MECCCAP_LRA_LR1_SESPID_20					(BIT20)
#define		ECC_MECCCAP_LRA_LR1_SESPID_19					(BIT19)
#define		ECC_MECCCAP_LRA_LR1_SESPID_18					(BIT18)
#define		ECC_MECCCAP_LRA_LR1_SESPID_17					(BIT17)
#define		ECC_MECCCAP_LRA_LR1_SESPID_16					(BIT16)
#define		ECC_MECCCAP_LRA_LR1_SESPID_15					(BIT15)
#define		ECC_MECCCAP_LRA_LR1_SESPID_14					(BIT14)
#define		ECC_MECCCAP_LRA_LR1_SESPID_13					(BIT13)
#define		ECC_MECCCAP_LRA_LR1_SESPID_12					(BIT12)
#define		ECC_MECCCAP_LRA_LR1_SESPID_11					(BIT11)
#define		ECC_MECCCAP_LRA_LR1_SESPID_10					(BIT10)
#define		ECC_MECCCAP_LRA_LR1_SESPID_9					(BIT9)
#define		ECC_MECCCAP_LRA_LR1_SESPID_8					(BIT8)
#define		ECC_MECCCAP_LRA_LR1_SESPID_7					(BIT7)
#define		ECC_MECCCAP_LRA_LR1_SESPID_6					(BIT6)
#define		ECC_MECCCAP_LRA_LR1_SESPID_5					(BIT5)
#define		ECC_MECCCAP_LRA_LR1_SESPID_4					(BIT4)
#define		ECC_MECCCAP_LRA_LR1_SESPID_3					(BIT3)
#define		ECC_MECCCAP_LRA_LR1_SESPID_2					(BIT2)
#define		ECC_MECCCAP_LRA_LR1_SESPID_1					(BIT1)
#define		ECC_MECCCAP_LRA_LR1_SESPID_0					(BIT0)

/* Cluster RAM ECC and Address Parity and Address Feedback */
/* Module: ECCCNT_CRCCL0 */
/* CRCAFCTL */
#define		ECC_ECCCNT_CRCCL0_CRCAFCTL_AFEDIS				(BIT3)
	#define		ECC_ECCCNT_CRCCL0_CRCAFCTL_AF_ENABLE		(0)
	#define		ECC_ECCCNT_CRCCL0_CRCAFCTL_AF_DISABLE		(1)
/* CRCECCTSTCTL */
#define		ECC_ECCCNT_CRCCL0_TSTCTL_ECCTST					(BIT1)
	#define		ECC_ECCCNT_CRCCL0_TSTCTL_TST_NORMAL			(0)
	#define		ECC_ECCCNT_CRCCL0_TSTCTL_TST_TEST			(1)
#define		ECC_ECCCNT_CRCCL0_TSTCTL_DATSEL					(BIT0)
	#define		ECC_ECCCNT_CRCCL0_TSTCTL_DS_DATA			(0)
	#define		ECC_ECCCNT_CRCCL0_TSTCTL_DS_ECC				(1)
/* CRCAFINV */
#define		ECC_ECCCNT_CRCCL0_CRCAFINV_AFINV				(0x0007FFF0U)
/* CRCTDATBFECCF */
#define		ECC_ECCCNT_CRCCL0_BFECCF_BF3					(BIT30 + BIT29 + BIT28 + BIT27 + BIT26 + BIT25 + BIT24)
#define		ECC_ECCCNT_CRCCL0_BFECCF_BF2					(BIT22 + BIT21 + BIT20 + BIT19 + BIT18 + BIT17 + BIT16)
#define		ECC_ECCCNT_CRCCL0_BFECCF_BF1					(BIT14 + BIT13 + BIT12 + BIT11 + BIT10 + BIT9 + BIT8)
#define		ECC_ECCCNT_CRCCL0_BFECCF_BF0					(BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)

/* Module: ECCCNT_CRCCL1 */
/* CRCAFCTL */
#define		ECC_ECCCNT_CRCCL1_CRCAFCTL_AFEDIS				(BIT3)
	#define		ECC_ECCCNT_CRCCL1_CRCAFCTL_AF_ENABLE		(0)
	#define		ECC_ECCCNT_CRCCL1_CRCAFCTL_AF_DISABLE		(1)
/* CRCECCTSTCTL */
#define		ECC_ECCCNT_CRCCL1_TSTCTL_ECCTST					(BIT1)
	#define		ECC_ECCCNT_CRCCL1_TSTCTL_TST_NORMAL			(0)
	#define		ECC_ECCCNT_CRCCL1_TSTCTL_TST_TEST			(1)
#define		ECC_ECCCNT_CRCCL1_TSTCTL_DATSEL					(BIT0)
	#define		ECC_ECCCNT_CRCCL1_TSTCTL_DS_DATA			(0)
	#define		ECC_ECCCNT_CRCCL1_TSTCTL_DS_ECC				(1)
/* CRCAFINV */
#define		ECC_ECCCNT_CRCCL1_CRCAFINV_AFINV				(0x0007FFF0U)
/* CRCTDATBFECCF */
#define		ECC_ECCCNT_CRCCL1_BFECCF_BF3					(BIT30 + BIT29 + BIT28 + BIT27 + BIT26 + BIT25 + BIT24)
#define		ECC_ECCCNT_CRCCL1_BFECCF_BF2					(BIT22 + BIT21 + BIT20 + BIT19 + BIT18 + BIT17 + BIT16)
#define		ECC_ECCCNT_CRCCL1_BFECCF_BF1					(BIT14 + BIT13 + BIT12 + BIT11 + BIT10 + BIT9 + BIT8)
#define		ECC_ECCCNT_CRCCL1_BFECCF_BF0					(BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)

/* Module: ECCCNT_CRCCL2 */
/* CRCAFCTL */
#define		ECC_ECCCNT_CRCCL2_CRCAFCTL_AFEDIS				(BIT3)
	#define		ECC_ECCCNT_CRCCL2_CRCAFCTL_AF_ENABLE		(0)
	#define		ECC_ECCCNT_CRCCL2_CRCAFCTL_AF_DISABLE		(1)
/* CRCECCTSTCTL */
#define		ECC_ECCCNT_CRCCL2_TSTCTL_ECCTST					(BIT1)
	#define		ECC_ECCCNT_CRCCL2_TSTCTL_TST_NORMAL			(0)
	#define		ECC_ECCCNT_CRCCL2_TSTCTL_TST_TEST			(1)
#define		ECC_ECCCNT_CRCCL2_TSTCTL_DATSEL					(BIT0)
	#define		ECC_ECCCNT_CRCCL2_TSTCTL_DS_DATA			(0)
	#define		ECC_ECCCNT_CRCCL2_TSTCTL_DS_ECC				(1)
/* CRCAFINV */
#define		ECC_ECCCNT_CRCCL2_CRCAFINV_AFINV				(0x0007FFF0U)
/* CRCTDATBFECCF */
#define		ECC_ECCCNT_CRCCL2_BFECCF_BF3					(BIT30 + BIT29 + BIT28 + BIT27 + BIT26 + BIT25 + BIT24)
#define		ECC_ECCCNT_CRCCL2_BFECCF_BF2					(BIT22 + BIT21 + BIT20 + BIT19 + BIT18 + BIT17 + BIT16)
#define		ECC_ECCCNT_CRCCL2_BFECCF_BF1					(BIT14 + BIT13 + BIT12 + BIT11 + BIT10 + BIT9 + BIT8)
#define		ECC_ECCCNT_CRCCL2_BFECCF_BF0					(BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)

/* Module: ECCCNT_CRCCL4 */
/* CRCAFCTL */
#define		ECC_ECCCNT_CRCCL4_CRCAFCTL_AFEDIS				(BIT3)
	#define		ECC_ECCCNT_CRCCL4_CRCAFCTL_AF_ENABLE		(0)
	#define		ECC_ECCCNT_CRCCL4_CRCAFCTL_AF_DISABLE		(1)
/* CRCECCTSTCTL */
#define		ECC_ECCCNT_CRCCL4_TSTCTL_ECCTST					(BIT1)
	#define		ECC_ECCCNT_CRCCL4_TSTCTL_TST_NORMAL			(0)
	#define		ECC_ECCCNT_CRCCL4_TSTCTL_TST_TEST			(1)
#define		ECC_ECCCNT_CRCCL4_TSTCTL_DATSEL					(BIT0)
	#define		ECC_ECCCNT_CRCCL4_TSTCTL_DS_DATA			(0)
	#define		ECC_ECCCNT_CRCCL4_TSTCTL_DS_ECC				(1)
/* CRCAFINV */
#define		ECC_ECCCNT_CRCCL4_CRCAFINV_AFINV				(0x003FFFF0U)
/* CRCTDATBFECCF */
#define		ECC_ECCCNT_CRCCL4_BFECCF_BF3					(BIT30 + BIT29 + BIT28 + BIT27 + BIT26 + BIT25 + BIT24)
#define		ECC_ECCCNT_CRCCL4_BFECCF_BF2					(BIT22 + BIT21 + BIT20 + BIT19 + BIT18 + BIT17 + BIT16)
#define		ECC_ECCCNT_CRCCL4_BFECCF_BF1					(BIT14 + BIT13 + BIT12 + BIT11 + BIT10 + BIT9 + BIT8)
#define		ECC_ECCCNT_CRCCL4_BFECCF_BF0					(BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)

/* Module: ECCCNT_CRA */
/* CRAECCCTL */
#define		ECC_ECCCNT_CRA_CRAECCCTL_SECDIS					(BIT1)
#define		ECC_ECCCNT_CRA_CRAECCCTL_ECCDIS					(BIT0)
	#define		ECC_ECCCNT_CRA_CRAECCCTL_DISABLE			(1)
	#define		ECC_ECCCNT_CRA_CRAECCCTL_ENABLE				(0)

/* Module: MECCCAP_CRAM */
/* CR_ERRINT */
#define		ECC_MECCCAP_CRAM_CR_ERRINT_SEOVFIE				(BIT7)
#define		ECC_MECCCAP_CRAM_CR_ERRINT_AFEIE				(BIT3)
#define		ECC_MECCCAP_CRAM_CR_ERRINT_DEDIE				(BIT1)
#define		ECC_MECCCAP_CRAM_CR_ERRINT_SEDIE				(BIT0)
	#define		ECC_MECCCAP_CRAM_CR_ERRINT_DISABLE			(0)
	#define		ECC_MECCCAP_CRAM_CR_ERRINT_ENABLE			(1)
/* CR_SSTCLR */
#define		ECC_MECCCAP_CRAM_CR_SSTCLR_07					(BIT7)
#define		ECC_MECCCAP_CRAM_CR_SSTCLR_06					(BIT6)
#define		ECC_MECCCAP_CRAM_CR_SSTCLR_05					(BIT5)
#define		ECC_MECCCAP_CRAM_CR_SSTCLR_04					(BIT4)
#define		ECC_MECCCAP_CRAM_CR_SSTCLR_03					(BIT3)
#define		ECC_MECCCAP_CRAM_CR_SSTCLR_02					(BIT2)
#define		ECC_MECCCAP_CRAM_CR_SSTCLR_01					(BIT1)
#define		ECC_MECCCAP_CRAM_CR_SSTCLR_00					(BIT0)
	#define		ECC_MECCCAP_CRAM_CR_SSTCLR_CLEAR			(1)
/* CR_DSTCLR */
#define		ECC_MECCCAP_CRAM_CR_DSTCLR_DSTCLR00				(BIT0)
	#define		ECC_MECCCAP_CRAM_CR_DSTCLR_CLEAR			(1)
/* CR_OVFCLR */
#define		ECC_MECCCAP_CRAM_CR_OVFCLR_1					(BIT1)
#define		ECC_MECCCAP_CRAM_CR_OVFCLR_0					(BIT0)
	#define		ECC_MECCCAP_CRAM_CR_OVFCLR_CLEAR			(1)
/* CR_SERSTR */
#define		ECC_MECCCAP_CRAM_CR_SERSTR_07					(BIT7)
#define		ECC_MECCCAP_CRAM_CR_SERSTR_06					(BIT6)
#define		ECC_MECCCAP_CRAM_CR_SERSTR_05					(BIT5)
#define		ECC_MECCCAP_CRAM_CR_SERSTR_04					(BIT4)
#define		ECC_MECCCAP_CRAM_CR_SERSTR_03					(BIT3)
#define		ECC_MECCCAP_CRAM_CR_SERSTR_02					(BIT2)
#define		ECC_MECCCAP_CRAM_CR_SERSTR_01					(BIT1)
#define		ECC_MECCCAP_CRAM_CR_SERSTR_00					(BIT0)
/* CR_DERSTR */
#define		ECC_MECCCAP_CRAM_CR_DERSTR_AFEF00				(BIT3)
#define		ECC_MECCCAP_CRAM_CR_DERSTR_DEDF00				(BIT1)
/* CR_OVFSTR */
#define		ECC_MECCCAP_CRAM_CR_OVFSTR_1					(BIT1)
#define		ECC_MECCCAP_CRAM_CR_OVFSTR_0					(BIT0)
/* CR_SERINF */
#define		ECC_MECCCAP_CRAM_CR_SERINF_27					(BIT27)
#define		ECC_MECCCAP_CRAM_CR_SERINF_26					(BIT26)
#define		ECC_MECCCAP_CRAM_CR_SERINF_25					(BIT25)
#define		ECC_MECCCAP_CRAM_CR_SERINF_24					(BIT24)
#define		ECC_MECCCAP_CRAM_CR_SERINF_21					(BIT21)
#define		ECC_MECCCAP_CRAM_CR_SERINF_20					(BIT20)
#define		ECC_MECCCAP_CRAM_CR_SERINF_19					(BIT19)
#define		ECC_MECCCAP_CRAM_CR_SERINF_18					(BIT18)
#define		ECC_MECCCAP_CRAM_CR_SERINF_17					(BIT17)
#define		ECC_MECCCAP_CRAM_CR_SERINF_16					(BIT16)
#define		ECC_MECCCAP_CRAM_CR_SERINF_13					(BIT13)
#define		ECC_MECCCAP_CRAM_CR_SERINF_12					(BIT12)
#define		ECC_MECCCAP_CRAM_CR_SERINF_11					(BIT11)
#define		ECC_MECCCAP_CRAM_CR_SERINF_10					(BIT10)
#define		ECC_MECCCAP_CRAM_CR_SERINF_09					(BIT9)
#define		ECC_MECCCAP_CRAM_CR_SERINF_08					(BIT8)
#define		ECC_MECCCAP_CRAM_CR_SERINF_05					(BIT5)
#define		ECC_MECCCAP_CRAM_CR_SERINF_04					(BIT4)
#define		ECC_MECCCAP_CRAM_CR_SERINF_03					(BIT3)
#define		ECC_MECCCAP_CRAM_CR_SERINF_02					(BIT2)
#define		ECC_MECCCAP_CRAM_CR_SERINF_01					(BIT1)
#define		ECC_MECCCAP_CRAM_CR_SERINF_00					(BIT0)
/* CR_nSEADR */
#define		ECC_MECCCAP_CRAM_CR_SEADR_SEDL					(BIT31 + BIT30 + BIT29 + BIT28 + BIT27)
#define		ECC_MECCCAP_CRAM_CR_SEADR_SEADR0				(0x00FFFFFCU)
/* CR_00DEADR */
#define		ECC_MECCCAP_CRAM_CR_DEADR_DEDL					(BIT31 + BIT30 + BIT29 + BIT28 + BIT27)
#define		ECC_MECCCAP_CRAM_CR_DEADR_DEADR0				(0x00FFFFFCU)
/* CR_00DESPIDCLR */
#define		ECC_MECCCAP_CRAM_CR_DSPIDC_31					(BIT31)
#define		ECC_MECCCAP_CRAM_CR_DSPIDC_30					(BIT30)
#define		ECC_MECCCAP_CRAM_CR_DSPIDC_29					(BIT29)
#define		ECC_MECCCAP_CRAM_CR_DSPIDC_28					(BIT28)
#define		ECC_MECCCAP_CRAM_CR_DSPIDC_27					(BIT27)
#define		ECC_MECCCAP_CRAM_CR_DSPIDC_26					(BIT26)
#define		ECC_MECCCAP_CRAM_CR_DSPIDC_25					(BIT25)
#define		ECC_MECCCAP_CRAM_CR_DSPIDC_24					(BIT24)
#define		ECC_MECCCAP_CRAM_CR_DSPIDC_23					(BIT23)
#define		ECC_MECCCAP_CRAM_CR_DSPIDC_22					(BIT22)
#define		ECC_MECCCAP_CRAM_CR_DSPIDC_21					(BIT21)
#define		ECC_MECCCAP_CRAM_CR_DSPIDC_20					(BIT20)
#define		ECC_MECCCAP_CRAM_CR_DSPIDC_19					(BIT19)
#define		ECC_MECCCAP_CRAM_CR_DSPIDC_18					(BIT18)
#define		ECC_MECCCAP_CRAM_CR_DSPIDC_17					(BIT17)
#define		ECC_MECCCAP_CRAM_CR_DSPIDC_16					(BIT16)
#define		ECC_MECCCAP_CRAM_CR_DSPIDC_15					(BIT15)
#define		ECC_MECCCAP_CRAM_CR_DSPIDC_14					(BIT14)
#define		ECC_MECCCAP_CRAM_CR_DSPIDC_13					(BIT13)
#define		ECC_MECCCAP_CRAM_CR_DSPIDC_12					(BIT12)
#define		ECC_MECCCAP_CRAM_CR_DSPIDC_11					(BIT11)
#define		ECC_MECCCAP_CRAM_CR_DSPIDC_10					(BIT10)
#define		ECC_MECCCAP_CRAM_CR_DSPIDC_9					(BIT9)
#define		ECC_MECCCAP_CRAM_CR_DSPIDC_8					(BIT8)
#define		ECC_MECCCAP_CRAM_CR_DSPIDC_7					(BIT7)
#define		ECC_MECCCAP_CRAM_CR_DSPIDC_6					(BIT6)
#define		ECC_MECCCAP_CRAM_CR_DSPIDC_5					(BIT5)
#define		ECC_MECCCAP_CRAM_CR_DSPIDC_4					(BIT4)
#define		ECC_MECCCAP_CRAM_CR_DSPIDC_3					(BIT3)
#define		ECC_MECCCAP_CRAM_CR_DSPIDC_2					(BIT2)
#define		ECC_MECCCAP_CRAM_CR_DSPIDC_1					(BIT1)
#define		ECC_MECCCAP_CRAM_CR_DSPIDC_0					(BIT0)
	#define	   ECC_MECCCAP_CRAM_CR_00DESPIDCLR_CLEAR		(1)
/* CR_00DESPID */
#define		ECC_MECCCAP_CRAM_CR_DESPID_31					(BIT31)
#define		ECC_MECCCAP_CRAM_CR_DESPID_30					(BIT30)
#define		ECC_MECCCAP_CRAM_CR_DESPID_29					(BIT29)
#define		ECC_MECCCAP_CRAM_CR_DESPID_28					(BIT28)
#define		ECC_MECCCAP_CRAM_CR_DESPID_27					(BIT27)
#define		ECC_MECCCAP_CRAM_CR_DESPID_26					(BIT26)
#define		ECC_MECCCAP_CRAM_CR_DESPID_25					(BIT25)
#define		ECC_MECCCAP_CRAM_CR_DESPID_24					(BIT24)
#define		ECC_MECCCAP_CRAM_CR_DESPID_23					(BIT23)
#define		ECC_MECCCAP_CRAM_CR_DESPID_22					(BIT22)
#define		ECC_MECCCAP_CRAM_CR_DESPID_21					(BIT21)
#define		ECC_MECCCAP_CRAM_CR_DESPID_20					(BIT20)
#define		ECC_MECCCAP_CRAM_CR_DESPID_19					(BIT19)
#define		ECC_MECCCAP_CRAM_CR_DESPID_18					(BIT18)
#define		ECC_MECCCAP_CRAM_CR_DESPID_17					(BIT17)
#define		ECC_MECCCAP_CRAM_CR_DESPID_16					(BIT16)
#define		ECC_MECCCAP_CRAM_CR_DESPID_15					(BIT15)
#define		ECC_MECCCAP_CRAM_CR_DESPID_14					(BIT14)
#define		ECC_MECCCAP_CRAM_CR_DESPID_13					(BIT13)
#define		ECC_MECCCAP_CRAM_CR_DESPID_12					(BIT12)
#define		ECC_MECCCAP_CRAM_CR_DESPID_11					(BIT11)
#define		ECC_MECCCAP_CRAM_CR_DESPID_10					(BIT10)
#define		ECC_MECCCAP_CRAM_CR_DESPID_9					(BIT9)
#define		ECC_MECCCAP_CRAM_CR_DESPID_8					(BIT8)
#define		ECC_MECCCAP_CRAM_CR_DESPID_7					(BIT7)
#define		ECC_MECCCAP_CRAM_CR_DESPID_6					(BIT6)
#define		ECC_MECCCAP_CRAM_CR_DESPID_5					(BIT5)
#define		ECC_MECCCAP_CRAM_CR_DESPID_4					(BIT4)
#define		ECC_MECCCAP_CRAM_CR_DESPID_3					(BIT3)
#define		ECC_MECCCAP_CRAM_CR_DESPID_2					(BIT2)
#define		ECC_MECCCAP_CRAM_CR_DESPID_1					(BIT1)
#define		ECC_MECCCAP_CRAM_CR_DESPID_0					(BIT0)
/* CR_00SESPIDCLR */
#define		ECC_MECCCAP_CRAM_CR_SSPIDC_31					(BIT31)
#define		ECC_MECCCAP_CRAM_CR_SSPIDC_30					(BIT30)
#define		ECC_MECCCAP_CRAM_CR_SSPIDC_29					(BIT29)
#define		ECC_MECCCAP_CRAM_CR_SSPIDC_28					(BIT28)
#define		ECC_MECCCAP_CRAM_CR_SSPIDC_27					(BIT27)
#define		ECC_MECCCAP_CRAM_CR_SSPIDC_26					(BIT26)
#define		ECC_MECCCAP_CRAM_CR_SSPIDC_25					(BIT25)
#define		ECC_MECCCAP_CRAM_CR_SSPIDC_24					(BIT24)
#define		ECC_MECCCAP_CRAM_CR_SSPIDC_23					(BIT23)
#define		ECC_MECCCAP_CRAM_CR_SSPIDC_22					(BIT22)
#define		ECC_MECCCAP_CRAM_CR_SSPIDC_21					(BIT21)
#define		ECC_MECCCAP_CRAM_CR_SSPIDC_20					(BIT20)
#define		ECC_MECCCAP_CRAM_CR_SSPIDC_19					(BIT19)
#define		ECC_MECCCAP_CRAM_CR_SSPIDC_18					(BIT18)
#define		ECC_MECCCAP_CRAM_CR_SSPIDC_17					(BIT17)
#define		ECC_MECCCAP_CRAM_CR_SSPIDC_16					(BIT16)
#define		ECC_MECCCAP_CRAM_CR_SSPIDC_15					(BIT15)
#define		ECC_MECCCAP_CRAM_CR_SSPIDC_14					(BIT14)
#define		ECC_MECCCAP_CRAM_CR_SSPIDC_13					(BIT13)
#define		ECC_MECCCAP_CRAM_CR_SSPIDC_12					(BIT12)
#define		ECC_MECCCAP_CRAM_CR_SSPIDC_11					(BIT11)
#define		ECC_MECCCAP_CRAM_CR_SSPIDC_10					(BIT10)
#define		ECC_MECCCAP_CRAM_CR_SSPIDC_9					(BIT9)
#define		ECC_MECCCAP_CRAM_CR_SSPIDC_8					(BIT8)
#define		ECC_MECCCAP_CRAM_CR_SSPIDC_7					(BIT7)
#define		ECC_MECCCAP_CRAM_CR_SSPIDC_6					(BIT6)
#define		ECC_MECCCAP_CRAM_CR_SSPIDC_5					(BIT5)
#define		ECC_MECCCAP_CRAM_CR_SSPIDC_4					(BIT4)
#define		ECC_MECCCAP_CRAM_CR_SSPIDC_3					(BIT3)
#define		ECC_MECCCAP_CRAM_CR_SSPIDC_2					(BIT2)
#define		ECC_MECCCAP_CRAM_CR_SSPIDC_1					(BIT1)
#define		ECC_MECCCAP_CRAM_CR_SSPIDC_0					(BIT0)
	#define	   ECC_MECCCAP_CRAM_CR_00SESPIDCLR_CLEAR		(1)
/* CR_00SESPID */
#define		ECC_MECCCAP_CRAM_CR_SESPID_31					(BIT31)
#define		ECC_MECCCAP_CRAM_CR_SESPID_30					(BIT30)
#define		ECC_MECCCAP_CRAM_CR_SESPID_29					(BIT29)
#define		ECC_MECCCAP_CRAM_CR_SESPID_28					(BIT28)
#define		ECC_MECCCAP_CRAM_CR_SESPID_27					(BIT27)
#define		ECC_MECCCAP_CRAM_CR_SESPID_26					(BIT26)
#define		ECC_MECCCAP_CRAM_CR_SESPID_25					(BIT25)
#define		ECC_MECCCAP_CRAM_CR_SESPID_24					(BIT24)
#define		ECC_MECCCAP_CRAM_CR_SESPID_23					(BIT23)
#define		ECC_MECCCAP_CRAM_CR_SESPID_22					(BIT22)
#define		ECC_MECCCAP_CRAM_CR_SESPID_21					(BIT21)
#define		ECC_MECCCAP_CRAM_CR_SESPID_20					(BIT20)
#define		ECC_MECCCAP_CRAM_CR_SESPID_19					(BIT19)
#define		ECC_MECCCAP_CRAM_CR_SESPID_18					(BIT18)
#define		ECC_MECCCAP_CRAM_CR_SESPID_17					(BIT17)
#define		ECC_MECCCAP_CRAM_CR_SESPID_16					(BIT16)
#define		ECC_MECCCAP_CRAM_CR_SESPID_15					(BIT15)
#define		ECC_MECCCAP_CRAM_CR_SESPID_14					(BIT14)
#define		ECC_MECCCAP_CRAM_CR_SESPID_13					(BIT13)
#define		ECC_MECCCAP_CRAM_CR_SESPID_12					(BIT12)
#define		ECC_MECCCAP_CRAM_CR_SESPID_11					(BIT11)
#define		ECC_MECCCAP_CRAM_CR_SESPID_10					(BIT10)
#define		ECC_MECCCAP_CRAM_CR_SESPID_9					(BIT9)
#define		ECC_MECCCAP_CRAM_CR_SESPID_8					(BIT8)
#define		ECC_MECCCAP_CRAM_CR_SESPID_7					(BIT7)
#define		ECC_MECCCAP_CRAM_CR_SESPID_6					(BIT6)
#define		ECC_MECCCAP_CRAM_CR_SESPID_5					(BIT5)
#define		ECC_MECCCAP_CRAM_CR_SESPID_4					(BIT4)
#define		ECC_MECCCAP_CRAM_CR_SESPID_3					(BIT3)
#define		ECC_MECCCAP_CRAM_CR_SESPID_2					(BIT2)
#define		ECC_MECCCAP_CRAM_CR_SESPID_1					(BIT1)
#define		ECC_MECCCAP_CRAM_CR_SESPID_0					(BIT0)


/* Instruction Cache EDC */
/* Module: ECCCNT_IT_PE0CL0 */
/* ITECCCTL */
#define		ECC_ECCCNT_IT_PE0CL0_ECCCTL_AFEDIS				(BIT3)
#define		ECC_ECCCNT_IT_PE0CL0_ECCCTL_ECCDIS				(BIT0)
	#define		ECC_ECCCNT_IT_PE0CL0_ECCCTL_ENABLE			(0)
	#define		ECC_ECCCNT_IT_PE0CL0_ECCCTL_DISABLE			(1)
/* ITAFINV */
#define		ECC_ECCCNT_IT_PE0CL0_ITAFINV_AFINV				(BIT12 + BIT11 + BIT10 + BIT9 + BIT8 + BIT7 + BIT6 + BIT5)

/* Module: ECCCNT_IT_PE1CL0 */
/* ITECCCTL */
#define		ECC_ECCCNT_IT_PE1CL0_ECCCTL_AFEDIS				(BIT3)
#define		ECC_ECCCNT_IT_PE1CL0_ECCCTL_ECCDIS				(BIT0)
	#define		ECC_ECCCNT_IT_PE1CL0_ECCCTL_ENABLE			(0)
	#define		ECC_ECCCNT_IT_PE1CL0_ECCCTL_DISABLE			(1)
/* ITAFINV */
#define		ECC_ECCCNT_IT_PE1CL0_ITAFINV_AFINV				(BIT12 + BIT11 + BIT10 + BIT9 + BIT8 + BIT7 + BIT6 + BIT5)

/* Module: ECCCNT_IT_PE2CL1 */
/* ITECCCTL */
#define		ECC_ECCCNT_IT_PE2CL1_ECCCTL_AFEDIS				(BIT3)
#define		ECC_ECCCNT_IT_PE2CL1_ECCCTL_ECCDIS				(BIT0)
	#define		ECC_ECCCNT_IT_PE2CL1_ECCCTL_ENABLE			(0)
	#define		ECC_ECCCNT_IT_PE2CL1_ECCCTL_DISABLE			(1)
/* ITAFINV */
#define		ECC_ECCCNT_IT_PE2CL1_ITAFINV_AFINV				(BIT12 + BIT11 + BIT10 + BIT9 + BIT8 + BIT7 + BIT6 + BIT5)

/* Module: ECCCNT_IT_PE3CL1 */
/* ITECCCTL */
#define		ECC_ECCCNT_IT_PE3CL1_ECCCTL_AFEDIS				(BIT3)
#define		ECC_ECCCNT_IT_PE3CL1_ECCCTL_ECCDIS				(BIT0)
	#define		ECC_ECCCNT_IT_PE3CL1_ECCCTL_ENABLE			(0)
	#define		ECC_ECCCNT_IT_PE3CL1_ECCCTL_DISABLE			(1)
/* ITAFINV */
#define		ECC_ECCCNT_IT_PE3CL1_ITAFINV_AFINV				(BIT12 + BIT11 + BIT10 + BIT9 + BIT8 + BIT7 + BIT6 + BIT5)

/* Module: ECCCNT_IT_PE4CL2 */
/* ITECCCTL */
#define		ECC_ECCCNT_IT_PE4CL2_ECCCTL_AFEDIS				(BIT3)
#define		ECC_ECCCNT_IT_PE4CL2_ECCCTL_ECCDIS				(BIT0)
	#define		ECC_ECCCNT_IT_PE4CL2_ECCCTL_ENABLE			(0)
	#define		ECC_ECCCNT_IT_PE4CL2_ECCCTL_DISABLE			(1)
/* ITAFINV */
#define		ECC_ECCCNT_IT_PE4CL2_ITAFINV_AFINV				(BIT12 + BIT11 + BIT10 + BIT9 + BIT8 + BIT7 + BIT6 + BIT5)

/* Module: ECCCNT_IT_PE5CL2 */
/* ITECCCTL */
#define		ECC_ECCCNT_IT_PE5CL2_ECCCTL_AFEDIS				(BIT3)
#define		ECC_ECCCNT_IT_PE5CL2_ECCCTL_ECCDIS				(BIT0)
	#define		ECC_ECCCNT_IT_PE5CL2_ECCCTL_ENABLE			(0)
	#define		ECC_ECCCNT_IT_PE5CL2_ECCCTL_DISABLE			(1)
/* ITAFINV */
#define		ECC_ECCCNT_IT_PE5CL2_ITAFINV_AFINV				(BIT12 + BIT11 + BIT10 + BIT9 + BIT8 + BIT7 + BIT6 + BIT5)

/* Module: ECCCNT_ID_PE0CL0 */
/* IDECCCTL */
#define		ECC_ECCCNT_ID_PE0CL0_ECCCTL_AFEDIS				(BIT3)
#define		ECC_ECCCNT_ID_PE0CL0_ECCCTL_ECCDIS				(BIT0)
	#define		ECC_ECCCNT_ID_PE0CL0_ECCCTL_ENABLE			(0)
	#define		ECC_ECCCNT_ID_PE0CL0_ECCCTL_DISABLE			(1)
/* IDAFINV */
#define		ECC_ECCCNT_ID_PE0CL0_IDAFINV_AFINV				(0x00001FF8U)

/* Module: ECCCNT_ID_PE1CL0 */
/* IDECCCTL */
#define		ECC_ECCCNT_ID_PE1CL0_ECCCTL_AFEDIS				(BIT3)
#define		ECC_ECCCNT_ID_PE1CL0_ECCCTL_ECCDIS				(BIT0)
	#define		ECC_ECCCNT_ID_PE1CL0_ECCCTL_ENABLE			(0)
	#define		ECC_ECCCNT_ID_PE1CL0_ECCCTL_DISABLE			(1)
/* IDAFINV */
#define		ECC_ECCCNT_ID_PE1CL0_IDAFINV_AFINV				(0x00001FF8U)

/* Module: ECCCNT_ID_PE2CL1 */
/* IDECCCTL */
#define		ECC_ECCCNT_ID_PE2CL1_ECCCTL_AFEDIS				(BIT3)
#define		ECC_ECCCNT_ID_PE2CL1_ECCCTL_ECCDIS				(BIT0)
	#define		ECC_ECCCNT_ID_PE2CL1_ECCCTL_ENABLE			(0)
	#define		ECC_ECCCNT_ID_PE2CL1_ECCCTL_DISABLE			(1)
/* IDAFINV */
#define		ECC_ECCCNT_ID_PE2CL1_IDAFINV_AFINV				(0x00001FF8U)

/* Module: ECCCNT_ID_PE3CL1 */
/* IDECCCTL */
#define		ECC_ECCCNT_ID_PE3CL1_ECCCTL_AFEDIS				(BIT3)
#define		ECC_ECCCNT_ID_PE3CL1_ECCCTL_ECCDIS				(BIT0)
	#define		ECC_ECCCNT_ID_PE3CL1_ECCCTL_ENABLE			(0)
	#define		ECC_ECCCNT_ID_PE3CL1_ECCCTL_DISABLE			(1)
/* IDAFINV */
#define		ECC_ECCCNT_ID_PE3CL1_IDAFINV_AFINV				(0x00001FF8U)

/* Module: ECCCNT_ID_PE4CL2 */
/* IDECCCTL */
#define		ECC_ECCCNT_ID_PE4CL2_ECCCTL_AFEDIS				(BIT3)
#define		ECC_ECCCNT_ID_PE4CL2_ECCCTL_ECCDIS				(BIT0)
	#define		ECC_ECCCNT_ID_PE4CL2_ECCCTL_ENABLE			(0)
	#define		ECC_ECCCNT_ID_PE4CL2_ECCCTL_DISABLE			(1)
/* IDAFINV */
#define		ECC_ECCCNT_ID_PE4CL2_IDAFINV_AFINV				(0x00001FF8U)

/* Module: ECCCNT_ID_PE5CL2 */
/* IDECCCTL */
#define		ECC_ECCCNT_ID_PE5CL2_ECCCTL_AFEDIS				(BIT3)
#define		ECC_ECCCNT_ID_PE5CL2_ECCCTL_ECCDIS				(BIT0)
	#define		ECC_ECCCNT_ID_PE5CL2_ECCCTL_ENABLE			(0)
	#define		ECC_ECCCNT_ID_PE5CL2_ECCCTL_DISABLE			(1)
/* IDAFINV */
#define		ECC_ECCCNT_ID_PE5CL2_IDAFINV_AFINV				(0x00001FF8U)

/* Module: MECCCAP_IT_PE0CL0 */
/* IT_ERRINT */
#define		ECC_MECCCAP_IT_PE0CL0_ERRINT_AFEIE				(BIT3)
#define		ECC_MECCCAP_IT_PE0CL0_ERRINT_DEDIE				(BIT1)
#define		ECC_MECCCAP_IT_PE0CL0_ERRINT_SEDIE				(BIT0)
	#define		ECC_MECCCAP_IT_PE0CL0_ERRINT_DISABLE		(0)
	#define		ECC_MECCCAP_IT_PE0CL0_ERRINT_ENABLE			(1)
/* IT_SSTCLR */
#define		ECC_MECCCAP_IT_PE0CL0_SSTCLR_SSTCLR00			(BIT0)
	#define		ECC_MECCCAP_IT_PE0CL0_SSTCLR_CLEAR			(1)
/* IT_DSTCLR */
#define		ECC_MECCCAP_IT_PE0CL0_DSTCLR_DSTCLR00			(BIT0)
	#define		ECC_MECCCAP_IT_PE0CL0_DSTCLR_CLEAR			(1)
/* IT_OVFCLR */
#define		ECC_MECCCAP_IT_PE0CL0_OVFCLR_1					(BIT1)
#define		ECC_MECCCAP_IT_PE0CL0_OVFCLR_0					(BIT0)
	#define		ECC_MECCCAP_IT_PE0CL0_OVFCLR_CLEAR			(1)
/* IT_SERSTR */
#define		ECC_MECCCAP_IT_PE0CL0_SERSTR_SEDF00				(BIT0)
/* IT_DERSTR */
#define		ECC_MECCCAP_IT_PE0CL0_DERSTR_AFEF00				(BIT3)
#define		ECC_MECCCAP_IT_PE0CL0_DERSTR_DEDF00				(BIT1)
/* IT_OVFSTR */
#define		ECC_MECCCAP_IT_PE0CL0_OVFSTR_1					(BIT1)
#define		ECC_MECCCAP_IT_PE0CL0_OVFSTR_0					(BIT0)
/* IT_SERINF */
#define		ECC_MECCCAP_IT_PE0CL0_SERINF_03					(BIT3)
#define		ECC_MECCCAP_IT_PE0CL0_SERINF_02					(BIT2)
#define		ECC_MECCCAP_IT_PE0CL0_SERINF_01					(BIT1)
#define		ECC_MECCCAP_IT_PE0CL0_SERINF_00					(BIT0)
/* IT_00SEADR */
#define		ECC_MECCCAP_IT_PE0CL0_SEADR_SEDL				(BIT31 + BIT30 + BIT29 + BIT28 + BIT27)
#define		ECC_MECCCAP_IT_PE0CL0_SEADR_SEADR0				(BIT12 + BIT11 + BIT10 + BIT9 + BIT8 + BIT7 + BIT6 + BIT5)
/* IT_00DEADR */
#define		ECC_MECCCAP_IT_PE0CL0_DEADR_DEDL				(BIT31 + BIT30 + BIT29 + BIT28 + BIT27)
#define		ECC_MECCCAP_IT_PE0CL0_DEADR_DEADR0				(BIT12 + BIT11 + BIT10 + BIT9 + BIT8 + BIT7 + BIT6 + BIT5)

/* Module: MECCCAP_IT_PE1CL0 */
/* IT_ERRINT */
#define		ECC_MECCCAP_IT_PE1CL0_ERRINT_AFEIE				(BIT3)
#define		ECC_MECCCAP_IT_PE1CL0_ERRINT_DEDIE				(BIT1)
#define		ECC_MECCCAP_IT_PE1CL0_ERRINT_SEDIE				(BIT0)
	#define		ECC_MECCCAP_IT_PE1CL0_ERRINT_DISABLE		(0)
	#define		ECC_MECCCAP_IT_PE1CL0_ERRINT_ENABLE			(1)
/* IT_SSTCLR */
#define		ECC_MECCCAP_IT_PE1CL0_SSTCLR_SSTCLR00			(BIT0)
	#define		ECC_MECCCAP_IT_PE1CL0_SSTCLR_CLEAR			(1)
/* IT_DSTCLR */
#define		ECC_MECCCAP_IT_PE1CL0_DSTCLR_DSTCLR00			(BIT0)
	#define		ECC_MECCCAP_IT_PE1CL0_DSTCLR_CLEAR			(1)
/* IT_OVFCLR */
#define		ECC_MECCCAP_IT_PE1CL0_OVFCLR_1					(BIT1)
#define		ECC_MECCCAP_IT_PE1CL0_OVFCLR_0					(BIT0)
	#define		ECC_MECCCAP_IT_PE1CL0_OVFCLR_CLEAR			(1)
/* IT_SERSTR */
#define		ECC_MECCCAP_IT_PE1CL0_SERSTR_SEDF00				(BIT0)
/* IT_DERSTR */
#define		ECC_MECCCAP_IT_PE1CL0_DERSTR_AFEF00				(BIT3)
#define		ECC_MECCCAP_IT_PE1CL0_DERSTR_DEDF00				(BIT1)
/* IT_OVFSTR */
#define		ECC_MECCCAP_IT_PE1CL0_OVFSTR_1					(BIT1)
#define		ECC_MECCCAP_IT_PE1CL0_OVFSTR_0					(BIT0)
/* IT_SERINF */
#define		ECC_MECCCAP_IT_PE1CL0_SERINF_03					(BIT3)
#define		ECC_MECCCAP_IT_PE1CL0_SERINF_02					(BIT2)
#define		ECC_MECCCAP_IT_PE1CL0_SERINF_01					(BIT1)
#define		ECC_MECCCAP_IT_PE1CL0_SERINF_00					(BIT0)
/* IT_00SEADR */
#define		ECC_MECCCAP_IT_PE1CL0_SEADR_SEDL				(BIT31 + BIT30 + BIT29 + BIT28 + BIT27)
#define		ECC_MECCCAP_IT_PE1CL0_SEADR_SEADR0				(BIT12 + BIT11 + BIT10 + BIT9 + BIT8 + BIT7 + BIT6 + BIT5)
/* IT_00DEADR */
#define		ECC_MECCCAP_IT_PE1CL0_DEADR_DEDL				(BIT31 + BIT30 + BIT29 + BIT28 + BIT27)
#define		ECC_MECCCAP_IT_PE1CL0_DEADR_DEADR0				(BIT12 + BIT11 + BIT10 + BIT9 + BIT8 + BIT7 + BIT6 + BIT5)

/* Module: MECCCAP_IT_PE2CL1 */
/* IT_ERRINT */
#define		ECC_MECCCAP_IT_PE2CL1_ERRINT_AFEIE				(BIT3)
#define		ECC_MECCCAP_IT_PE2CL1_ERRINT_DEDIE				(BIT1)
#define		ECC_MECCCAP_IT_PE2CL1_ERRINT_SEDIE				(BIT0)
	#define		ECC_MECCCAP_IT_PE2CL1_ERRINT_DISABLE		(0)
	#define		ECC_MECCCAP_IT_PE2CL1_ERRINT_ENABLE			(1)
/* IT_SSTCLR */
#define		ECC_MECCCAP_IT_PE2CL1_SSTCLR_SSTCLR00			(BIT0)
	#define		ECC_MECCCAP_IT_PE2CL1_SSTCLR_CLEAR			(1)
/* IT_DSTCLR */
#define		ECC_MECCCAP_IT_PE2CL1_DSTCLR_DSTCLR00			(BIT0)
	#define		ECC_MECCCAP_IT_PE2CL1_DSTCLR_CLEAR			(1)
/* IT_OVFCLR */
#define		ECC_MECCCAP_IT_PE2CL1_OVFCLR_1					(BIT1)
#define		ECC_MECCCAP_IT_PE2CL1_OVFCLR_0					(BIT0)
	#define		ECC_MECCCAP_IT_PE2CL1_OVFCLR_CLEAR			(1)
/* IT_SERSTR */
#define		ECC_MECCCAP_IT_PE2CL1_SERSTR_SEDF00				(BIT0)
/* IT_DERSTR */
#define		ECC_MECCCAP_IT_PE2CL1_DERSTR_AFEF00				(BIT3)
#define		ECC_MECCCAP_IT_PE2CL1_DERSTR_DEDF00				(BIT1)
/* IT_OVFSTR */
#define		ECC_MECCCAP_IT_PE2CL1_OVFSTR_1					(BIT1)
#define		ECC_MECCCAP_IT_PE2CL1_OVFSTR_0					(BIT0)
/* IT_SERINF */
#define		ECC_MECCCAP_IT_PE2CL1_SERINF_03					(BIT3)
#define		ECC_MECCCAP_IT_PE2CL1_SERINF_02					(BIT2)
#define		ECC_MECCCAP_IT_PE2CL1_SERINF_01					(BIT1)
#define		ECC_MECCCAP_IT_PE2CL1_SERINF_00					(BIT0)
/* IT_00SEADR */
#define		ECC_MECCCAP_IT_PE2CL1_SEADR_SEDL				(BIT31 + BIT30 + BIT29 + BIT28 + BIT27)
#define		ECC_MECCCAP_IT_PE2CL1_SEADR_SEADR0				(BIT12 + BIT11 + BIT10 + BIT9 + BIT8 + BIT7 + BIT6 + BIT5)
/* IT_00DEADR */
#define		ECC_MECCCAP_IT_PE2CL1_DEADR_DEDL				(BIT31 + BIT30 + BIT29 + BIT28 + BIT27)
#define		ECC_MECCCAP_IT_PE2CL1_DEADR_DEADR0				(BIT12 + BIT11 + BIT10 + BIT9 + BIT8 + BIT7 + BIT6 + BIT5)

/* Module: MECCCAP_IT_PE3CL1 */
/* IT_ERRINT */
#define		ECC_MECCCAP_IT_PE3CL1_ERRINT_AFEIE				(BIT3)
#define		ECC_MECCCAP_IT_PE3CL1_ERRINT_DEDIE				(BIT1)
#define		ECC_MECCCAP_IT_PE3CL1_ERRINT_SEDIE				(BIT0)
	#define		ECC_MECCCAP_IT_PE3CL1_ERRINT_DISABLE		(0)
	#define		ECC_MECCCAP_IT_PE3CL1_ERRINT_ENABLE			(1)
/* IT_SSTCLR */
#define		ECC_MECCCAP_IT_PE3CL1_SSTCLR_SSTCLR00			(BIT0)
	#define		ECC_MECCCAP_IT_PE3CL1_SSTCLR_CLEAR			(1)
/* IT_DSTCLR */
#define		ECC_MECCCAP_IT_PE3CL1_DSTCLR_DSTCLR00			(BIT0)
	#define		ECC_MECCCAP_IT_PE3CL1_DSTCLR_CLEAR			(1)
/* IT_OVFCLR */
#define		ECC_MECCCAP_IT_PE3CL1_OVFCLR_1					(BIT1)
#define		ECC_MECCCAP_IT_PE3CL1_OVFCLR_0					(BIT0)
	#define		ECC_MECCCAP_IT_PE3CL1_OVFCLR_CLEAR			(1)
/* IT_SERSTR */
#define		ECC_MECCCAP_IT_PE3CL1_SERSTR_SEDF00				(BIT0)
/* IT_DERSTR */
#define		ECC_MECCCAP_IT_PE3CL1_DERSTR_AFEF00				(BIT3)
#define		ECC_MECCCAP_IT_PE3CL1_DERSTR_DEDF00				(BIT1)
/* IT_OVFSTR */
#define		ECC_MECCCAP_IT_PE3CL1_OVFSTR_1					(BIT1)
#define		ECC_MECCCAP_IT_PE3CL1_OVFSTR_0					(BIT0)
/* IT_SERINF */
#define		ECC_MECCCAP_IT_PE3CL1_SERINF_03					(BIT3)
#define		ECC_MECCCAP_IT_PE3CL1_SERINF_02					(BIT2)
#define		ECC_MECCCAP_IT_PE3CL1_SERINF_01					(BIT1)
#define		ECC_MECCCAP_IT_PE3CL1_SERINF_00					(BIT0)
/* IT_00SEADR */
#define		ECC_MECCCAP_IT_PE3CL1_SEADR_SEDL				(BIT31 + BIT30 + BIT29 + BIT28 + BIT27)
#define		ECC_MECCCAP_IT_PE3CL1_SEADR_SEADR0				(BIT12 + BIT11 + BIT10 + BIT9 + BIT8 + BIT7 + BIT6 + BIT5)
/* IT_00DEADR */
#define		ECC_MECCCAP_IT_PE3CL1_DEADR_DEDL				(BIT31 + BIT30 + BIT29 + BIT28 + BIT27)
#define		ECC_MECCCAP_IT_PE3CL1_DEADR_DEADR0				(BIT12 + BIT11 + BIT10 + BIT9 + BIT8 + BIT7 + BIT6 + BIT5)

/* Module: MECCCAP_IT_PE4CL2 */
/* IT_ERRINT */
#define		ECC_MECCCAP_IT_PE4CL2_ERRINT_AFEIE				(BIT3)
#define		ECC_MECCCAP_IT_PE4CL2_ERRINT_DEDIE				(BIT1)
#define		ECC_MECCCAP_IT_PE4CL2_ERRINT_SEDIE				(BIT0)
	#define		ECC_MECCCAP_IT_PE4CL2_ERRINT_DISABLE		(0)
	#define		ECC_MECCCAP_IT_PE4CL2_ERRINT_ENABLE			(1)
/* IT_SSTCLR */
#define		ECC_MECCCAP_IT_PE4CL2_SSTCLR_SSTCLR00			(BIT0)
	#define		ECC_MECCCAP_IT_PE4CL2_SSTCLR_CLEAR			(1)
/* IT_DSTCLR */
#define		ECC_MECCCAP_IT_PE4CL2_DSTCLR_DSTCLR00			(BIT0)
	#define		ECC_MECCCAP_IT_PE4CL2_DSTCLR_CLEAR			(1)
/* IT_OVFCLR */
#define		ECC_MECCCAP_IT_PE4CL2_OVFCLR_1					(BIT1)
#define		ECC_MECCCAP_IT_PE4CL2_OVFCLR_0					(BIT0)
	#define		ECC_MECCCAP_IT_PE4CL2_OVFCLR_CLEAR			(1)
/* IT_SERSTR */
#define		ECC_MECCCAP_IT_PE4CL2_SERSTR_SEDF00				(BIT0)
/* IT_DERSTR */
#define		ECC_MECCCAP_IT_PE4CL2_DERSTR_AFEF00				(BIT3)
#define		ECC_MECCCAP_IT_PE4CL2_DERSTR_DEDF00				(BIT1)
/* IT_OVFSTR */
#define		ECC_MECCCAP_IT_PE4CL2_OVFSTR_1					(BIT1)
#define		ECC_MECCCAP_IT_PE4CL2_OVFSTR_0					(BIT0)
/* IT_SERINF */
#define		ECC_MECCCAP_IT_PE4CL2_SERINF_03					(BIT3)
#define		ECC_MECCCAP_IT_PE4CL2_SERINF_02					(BIT2)
#define		ECC_MECCCAP_IT_PE4CL2_SERINF_01					(BIT1)
#define		ECC_MECCCAP_IT_PE4CL2_SERINF_00					(BIT0)
/* IT_00SEADR */
#define		ECC_MECCCAP_IT_PE4CL2_SEADR_SEDL				(BIT31 + BIT30 + BIT29 + BIT28 + BIT27)
#define		ECC_MECCCAP_IT_PE4CL2_SEADR_SEADR0				(BIT12 + BIT11 + BIT10 + BIT9 + BIT8 + BIT7 + BIT6 + BIT5)
/* IT_00DEADR */
#define		ECC_MECCCAP_IT_PE4CL2_DEADR_DEDL				(BIT31 + BIT30 + BIT29 + BIT28 + BIT27)
#define		ECC_MECCCAP_IT_PE4CL2_DEADR_DEADR0				(BIT12 + BIT11 + BIT10 + BIT9 + BIT8 + BIT7 + BIT6 + BIT5)

/* Module: MECCCAP_IT_PE5CL2 */
/* IT_ERRINT */
#define		ECC_MECCCAP_IT_PE5CL2_ERRINT_AFEIE				(BIT3)
#define		ECC_MECCCAP_IT_PE5CL2_ERRINT_DEDIE				(BIT1)
#define		ECC_MECCCAP_IT_PE5CL2_ERRINT_SEDIE				(BIT0)
	#define		ECC_MECCCAP_IT_PE5CL2_ERRINT_DISABLE		(0)
	#define		ECC_MECCCAP_IT_PE5CL2_ERRINT_ENABLE			(1)
/* IT_SSTCLR */
#define		ECC_MECCCAP_IT_PE5CL2_SSTCLR_SSTCLR00			(BIT0)
	#define		ECC_MECCCAP_IT_PE5CL2_SSTCLR_CLEAR			(1)
/* IT_DSTCLR */
#define		ECC_MECCCAP_IT_PE5CL2_DSTCLR_DSTCLR00			(BIT0)
	#define		ECC_MECCCAP_IT_PE5CL2_DSTCLR_CLEAR			(1)
/* IT_OVFCLR */
#define		ECC_MECCCAP_IT_PE5CL2_OVFCLR_1					(BIT1)
#define		ECC_MECCCAP_IT_PE5CL2_OVFCLR_0					(BIT0)
	#define		ECC_MECCCAP_IT_PE5CL2_OVFCLR_CLEAR			(1)
/* IT_SERSTR */
#define		ECC_MECCCAP_IT_PE5CL2_SERSTR_SEDF00				(BIT0)
/* IT_DERSTR */
#define		ECC_MECCCAP_IT_PE5CL2_DERSTR_AFEF00				(BIT3)
#define		ECC_MECCCAP_IT_PE5CL2_DERSTR_DEDF00				(BIT1)
/* IT_OVFSTR */
#define		ECC_MECCCAP_IT_PE5CL2_OVFSTR_1					(BIT1)
#define		ECC_MECCCAP_IT_PE5CL2_OVFSTR_0					(BIT0)
/* IT_SERINF */
#define		ECC_MECCCAP_IT_PE5CL2_SERINF_03					(BIT3)
#define		ECC_MECCCAP_IT_PE5CL2_SERINF_02					(BIT2)
#define		ECC_MECCCAP_IT_PE5CL2_SERINF_01					(BIT1)
#define		ECC_MECCCAP_IT_PE5CL2_SERINF_00					(BIT0)
/* IT_00SEADR */
#define		ECC_MECCCAP_IT_PE5CL2_SEADR_SEDL				(BIT31 + BIT30 + BIT29 + BIT28 + BIT27)
#define		ECC_MECCCAP_IT_PE5CL2_SEADR_SEADR0				(BIT12 + BIT11 + BIT10 + BIT9 + BIT8 + BIT7 + BIT6 + BIT5)
/* IT_00DEADR */
#define		ECC_MECCCAP_IT_PE5CL2_DEADR_DEDL				(BIT31 + BIT30 + BIT29 + BIT28 + BIT27)
#define		ECC_MECCCAP_IT_PE5CL2_DEADR_DEADR0				(BIT12 + BIT11 + BIT10 + BIT9 + BIT8 + BIT7 + BIT6 + BIT5)

/* Module: MECCCAP_ID_PE0CL0 */
/* ID_ERRINT */
#define		ECC_MECCCAP_ID_PE0CL0_ERRINT_AFEIE				(BIT3)
#define		ECC_MECCCAP_ID_PE0CL0_ERRINT_DEDIE				(BIT1)
#define		ECC_MECCCAP_ID_PE0CL0_ERRINT_SEDIE				(BIT0)
	#define		ECC_MECCCAP_ID_PE0CL0_ERRINT_DISABLE		(0)
	#define		ECC_MECCCAP_ID_PE0CL0_ERRINT_ENABLE			(1)

/* ID_SSTCLR */
#define		ECC_MECCCAP_ID_PE0CL0_SSTCLR_SSTCLR00			(BIT0)
	#define		ECC_MECCCAP_ID_PE0CL0_SSTCLR_CLEAR			(1)
/* ID_DSTCLR */
#define		ECC_MECCCAP_ID_PE0CL0_DSTCLR_DSTCLR00			(BIT0)
	#define		ECC_MECCCAP_ID_PE0CL0_DSTCLR_CLEAR			(1)
/* ID_OVFCLR */
#define		ECC_MECCCAP_ID_PE0CL0_OVFCLR_1					(BIT1)
#define		ECC_MECCCAP_ID_PE0CL0_OVFCLR_0					(BIT0)
	#define		ECC_MECCCAP_ID_PE0CL0_OVFCLR_CLEAR			(1)
/* ID_SERSTR */
#define		ECC_MECCCAP_ID_PE0CL0_SERSTR_SEDF00				(BIT0)
/* ID_DERSTR */
#define		ECC_MECCCAP_ID_PE0CL0_DERSTR_AFEF00				(BIT3)
#define		ECC_MECCCAP_ID_PE0CL0_DERSTR_DEDF00				(BIT1)
/* ID_OVFSTR */
#define		ECC_MECCCAP_ID_PE0CL0_OVFSTR_1					(BIT1)
#define		ECC_MECCCAP_ID_PE0CL0_OVFSTR_0					(BIT0)
/* ID_SERINF */
#define		ECC_MECCCAP_ID_PE0CL0_SERINF_03					(BIT3)
#define		ECC_MECCCAP_ID_PE0CL0_SERINF_02					(BIT2)
#define		ECC_MECCCAP_ID_PE0CL0_SERINF_01					(BIT1)
#define		ECC_MECCCAP_ID_PE0CL0_SERINF_00					(BIT0)
/* ID_00SEADR */
#define		ECC_MECCCAP_ID_PE0CL0_SEADR_SEDL				(BIT31 + BIT30 + BIT29 + BIT28 + BIT27)
#define		ECC_MECCCAP_ID_PE0CL0_SEADR_SEADR0				(0x00001FF8U)
/* ID_00DEADR */
#define		ECC_MECCCAP_ID_PE0CL0_DEADR_DEDL				(BIT31 + BIT30 + BIT29 + BIT28 + BIT27)
#define		ECC_MECCCAP_ID_PE0CL0_DEADR_DEADR0				(0x00001FF8U)

/* Module: MECCCAP_ID_PE1CL0 */
/* ID_ERRINT */
#define		ECC_MECCCAP_ID_PE1CL0_ERRINT_AFEIE				(BIT3)
#define		ECC_MECCCAP_ID_PE1CL0_ERRINT_DEDIE				(BIT1)
#define		ECC_MECCCAP_ID_PE1CL0_ERRINT_SEDIE				(BIT0)
	#define		ECC_MECCCAP_ID_PE1CL0_ERRINT_DISABLE		(0)
	#define		ECC_MECCCAP_ID_PE1CL0_ERRINT_ENABLE			(1)

/* ID_SSTCLR */
#define		ECC_MECCCAP_ID_PE1CL0_SSTCLR_SSTCLR00			(BIT0)
	#define		ECC_MECCCAP_ID_PE1CL0_SSTCLR_CLEAR			(1)
/* ID_DSTCLR */
#define		ECC_MECCCAP_ID_PE1CL0_DSTCLR_DSTCLR00			(BIT0)
	#define		ECC_MECCCAP_ID_PE1CL0_DSTCLR_CLEAR			(1)
/* ID_OVFCLR */
#define		ECC_MECCCAP_ID_PE1CL0_OVFCLR_1					(BIT1)
#define		ECC_MECCCAP_ID_PE1CL0_OVFCLR_0					(BIT0)
	#define		ECC_MECCCAP_ID_PE1CL0_OVFCLR_CLEAR			(1)
/* ID_SERSTR */
#define		ECC_MECCCAP_ID_PE1CL0_SERSTR_SEDF00				(BIT0)
/* ID_DERSTR */
#define		ECC_MECCCAP_ID_PE1CL0_DERSTR_AFEF00				(BIT3)
#define		ECC_MECCCAP_ID_PE1CL0_DERSTR_DEDF00				(BIT1)
/* ID_OVFSTR */
#define		ECC_MECCCAP_ID_PE1CL0_OVFSTR_1					(BIT1)
#define		ECC_MECCCAP_ID_PE1CL0_OVFSTR_0					(BIT0)
/* ID_SERINF */
#define		ECC_MECCCAP_ID_PE1CL0_SERINF_03					(BIT3)
#define		ECC_MECCCAP_ID_PE1CL0_SERINF_02					(BIT2)
#define		ECC_MECCCAP_ID_PE1CL0_SERINF_01					(BIT1)
#define		ECC_MECCCAP_ID_PE1CL0_SERINF_00					(BIT0)
/* ID_00SEADR */
#define		ECC_MECCCAP_ID_PE1CL0_SEADR_SEDL				(BIT31 + BIT30 + BIT29 + BIT28 + BIT27)
#define		ECC_MECCCAP_ID_PE1CL0_SEADR_SEADR0				(0x00001FF8U)
/* ID_00DEADR */
#define		ECC_MECCCAP_ID_PE1CL0_DEADR_DEDL				(BIT31 + BIT30 + BIT29 + BIT28 + BIT27)
#define		ECC_MECCCAP_ID_PE1CL0_DEADR_DEADR0				(0x00001FF8U)

/* Module: MECCCAP_ID_PE2CL1 */
/* ID_ERRINT */
#define		ECC_MECCCAP_ID_PE2CL1_ERRINT_AFEIE				(BIT3)
#define		ECC_MECCCAP_ID_PE2CL1_ERRINT_DEDIE				(BIT1)
#define		ECC_MECCCAP_ID_PE2CL1_ERRINT_SEDIE				(BIT0)
	#define		ECC_MECCCAP_ID_PE2CL1_ERRINT_DISABLE		(0)
	#define		ECC_MECCCAP_ID_PE2CL1_ERRINT_ENABLE			(1)

/* ID_SSTCLR */
#define		ECC_MECCCAP_ID_PE2CL1_SSTCLR_SSTCLR00			(BIT0)
	#define		ECC_MECCCAP_ID_PE2CL1_SSTCLR_CLEAR			(1)
/* ID_DSTCLR */
#define		ECC_MECCCAP_ID_PE2CL1_DSTCLR_DSTCLR00			(BIT0)
	#define		ECC_MECCCAP_ID_PE2CL1_DSTCLR_CLEAR			(1)
/* ID_OVFCLR */
#define		ECC_MECCCAP_ID_PE2CL1_OVFCLR_1					(BIT1)
#define		ECC_MECCCAP_ID_PE2CL1_OVFCLR_0					(BIT0)
	#define		ECC_MECCCAP_ID_PE2CL1_OVFCLR_CLEAR			(1)
/* ID_SERSTR */
#define		ECC_MECCCAP_ID_PE2CL1_SERSTR_SEDF00				(BIT0)
/* ID_DERSTR */
#define		ECC_MECCCAP_ID_PE2CL1_DERSTR_AFEF00				(BIT3)
#define		ECC_MECCCAP_ID_PE2CL1_DERSTR_DEDF00				(BIT1)
/* ID_OVFSTR */
#define		ECC_MECCCAP_ID_PE2CL1_OVFSTR_1					(BIT1)
#define		ECC_MECCCAP_ID_PE2CL1_OVFSTR_0					(BIT0)
/* ID_SERINF */
#define		ECC_MECCCAP_ID_PE2CL1_SERINF_03					(BIT3)
#define		ECC_MECCCAP_ID_PE2CL1_SERINF_02					(BIT2)
#define		ECC_MECCCAP_ID_PE2CL1_SERINF_01					(BIT1)
#define		ECC_MECCCAP_ID_PE2CL1_SERINF_00					(BIT0)
/* ID_00SEADR */
#define		ECC_MECCCAP_ID_PE2CL1_SEADR_SEDL				(BIT31 + BIT30 + BIT29 + BIT28 + BIT27)
#define		ECC_MECCCAP_ID_PE2CL1_SEADR_SEADR0				(0x00001FF8U)
/* ID_00DEADR */
#define		ECC_MECCCAP_ID_PE2CL1_DEADR_DEDL				(BIT31 + BIT30 + BIT29 + BIT28 + BIT27)
#define		ECC_MECCCAP_ID_PE2CL1_DEADR_DEADR0				(0x00001FF8U)

/* Module: MECCCAP_ID_PE3CL1 */
/* ID_ERRINT */
#define		ECC_MECCCAP_ID_PE3CL1_ERRINT_AFEIE				(BIT3)
#define		ECC_MECCCAP_ID_PE3CL1_ERRINT_DEDIE				(BIT1)
#define		ECC_MECCCAP_ID_PE3CL1_ERRINT_SEDIE				(BIT0)
	#define		ECC_MECCCAP_ID_PE3CL1_ERRINT_DISABLE		(0)
	#define		ECC_MECCCAP_ID_PE3CL1_ERRINT_ENABLE			(1)

/* ID_SSTCLR */
#define		ECC_MECCCAP_ID_PE3CL1_SSTCLR_SSTCLR00			(BIT0)
	#define		ECC_MECCCAP_ID_PE3CL1_SSTCLR_CLEAR			(1)
/* ID_DSTCLR */
#define		ECC_MECCCAP_ID_PE3CL1_DSTCLR_DSTCLR00			(BIT0)
	#define		ECC_MECCCAP_ID_PE3CL1_DSTCLR_CLEAR			(1)
/* ID_OVFCLR */
#define		ECC_MECCCAP_ID_PE3CL1_OVFCLR_1					(BIT1)
#define		ECC_MECCCAP_ID_PE3CL1_OVFCLR_0					(BIT0)
	#define		ECC_MECCCAP_ID_PE3CL1_OVFCLR_CLEAR			(1)
/* ID_SERSTR */
#define		ECC_MECCCAP_ID_PE3CL1_SERSTR_SEDF00				(BIT0)
/* ID_DERSTR */
#define		ECC_MECCCAP_ID_PE3CL1_DERSTR_AFEF00				(BIT3)
#define		ECC_MECCCAP_ID_PE3CL1_DERSTR_DEDF00				(BIT1)
/* ID_OVFSTR */
#define		ECC_MECCCAP_ID_PE3CL1_OVFSTR_1					(BIT1)
#define		ECC_MECCCAP_ID_PE3CL1_OVFSTR_0					(BIT0)
/* ID_SERINF */
#define		ECC_MECCCAP_ID_PE3CL1_SERINF_03					(BIT3)
#define		ECC_MECCCAP_ID_PE3CL1_SERINF_02					(BIT2)
#define		ECC_MECCCAP_ID_PE3CL1_SERINF_01					(BIT1)
#define		ECC_MECCCAP_ID_PE3CL1_SERINF_00					(BIT0)
/* ID_00SEADR */
#define		ECC_MECCCAP_ID_PE3CL1_SEADR_SEDL				(BIT31 + BIT30 + BIT29 + BIT28 + BIT27)
#define		ECC_MECCCAP_ID_PE3CL1_SEADR_SEADR0				(0x00001FF8U)
/* ID_00DEADR */
#define		ECC_MECCCAP_ID_PE3CL1_DEADR_DEDL				(BIT31 + BIT30 + BIT29 + BIT28 + BIT27)
#define		ECC_MECCCAP_ID_PE3CL1_DEADR_DEADR0				(0x00001FF8U)

/* Module: MECCCAP_ID_PE4CL2 */
/* ID_ERRINT */
#define		ECC_MECCCAP_ID_PE4CL2_ERRINT_AFEIE				(BIT3)
#define		ECC_MECCCAP_ID_PE4CL2_ERRINT_DEDIE				(BIT1)
#define		ECC_MECCCAP_ID_PE4CL2_ERRINT_SEDIE				(BIT0)
	#define		ECC_MECCCAP_ID_PE4CL2_ERRINT_DISABLE		(0)
	#define		ECC_MECCCAP_ID_PE4CL2_ERRINT_ENABLE			(1)

/* ID_SSTCLR */
#define		ECC_MECCCAP_ID_PE4CL2_SSTCLR_SSTCLR00			(BIT0)
	#define		ECC_MECCCAP_ID_PE4CL2_SSTCLR_CLEAR			(1)
/* ID_DSTCLR */
#define		ECC_MECCCAP_ID_PE4CL2_DSTCLR_DSTCLR00			(BIT0)
	#define		ECC_MECCCAP_ID_PE4CL2_DSTCLR_CLEAR			(1)
/* ID_OVFCLR */
#define		ECC_MECCCAP_ID_PE4CL2_OVFCLR_1					(BIT1)
#define		ECC_MECCCAP_ID_PE4CL2_OVFCLR_0					(BIT0)
	#define		ECC_MECCCAP_ID_PE4CL2_OVFCLR_CLEAR			(1)
/* ID_SERSTR */
#define		ECC_MECCCAP_ID_PE4CL2_SERSTR_SEDF00				(BIT0)
/* ID_DERSTR */
#define		ECC_MECCCAP_ID_PE4CL2_DERSTR_AFEF00				(BIT3)
#define		ECC_MECCCAP_ID_PE4CL2_DERSTR_DEDF00				(BIT1)
/* ID_OVFSTR */
#define		ECC_MECCCAP_ID_PE4CL2_OVFSTR_1					(BIT1)
#define		ECC_MECCCAP_ID_PE4CL2_OVFSTR_0					(BIT0)
/* ID_SERINF */
#define		ECC_MECCCAP_ID_PE4CL2_SERINF_03					(BIT3)
#define		ECC_MECCCAP_ID_PE4CL2_SERINF_02					(BIT2)
#define		ECC_MECCCAP_ID_PE4CL2_SERINF_01					(BIT1)
#define		ECC_MECCCAP_ID_PE4CL2_SERINF_00					(BIT0)
/* ID_00SEADR */
#define		ECC_MECCCAP_ID_PE4CL2_SEADR_SEDL				(BIT31 + BIT30 + BIT29 + BIT28 + BIT27)
#define		ECC_MECCCAP_ID_PE4CL2_SEADR_SEADR0				(0x00001FF8U)
/* ID_00DEADR */
#define		ECC_MECCCAP_ID_PE4CL2_DEADR_DEDL				(BIT31 + BIT30 + BIT29 + BIT28 + BIT27)
#define		ECC_MECCCAP_ID_PE4CL2_DEADR_DEADR0				(0x00001FF8U)

/* Module: MECCCAP_ID_PE5CL2 */
/* ID_ERRINT */
#define		ECC_MECCCAP_ID_PE5CL2_ERRINT_AFEIE				(BIT3)
#define		ECC_MECCCAP_ID_PE5CL2_ERRINT_DEDIE				(BIT1)
#define		ECC_MECCCAP_ID_PE5CL2_ERRINT_SEDIE				(BIT0)
	#define		ECC_MECCCAP_ID_PE5CL2_ERRINT_DISABLE		(0)
	#define		ECC_MECCCAP_ID_PE5CL2_ERRINT_ENABLE			(1)

/* ID_SSTCLR */
#define		ECC_MECCCAP_ID_PE5CL2_SSTCLR_SSTCLR00			(BIT0)
	#define		ECC_MECCCAP_ID_PE5CL2_SSTCLR_CLEAR			(1)
/* ID_DSTCLR */
#define		ECC_MECCCAP_ID_PE5CL2_DSTCLR_DSTCLR00			(BIT0)
	#define		ECC_MECCCAP_ID_PE5CL2_DSTCLR_CLEAR			(1)
/* ID_OVFCLR */
#define		ECC_MECCCAP_ID_PE5CL2_OVFCLR_1					(BIT1)
#define		ECC_MECCCAP_ID_PE5CL2_OVFCLR_0					(BIT0)
	#define		ECC_MECCCAP_ID_PE5CL2_OVFCLR_CLEAR			(1)
/* ID_SERSTR */
#define		ECC_MECCCAP_ID_PE5CL2_SERSTR_SEDF00				(BIT0)
/* ID_DERSTR */
#define		ECC_MECCCAP_ID_PE5CL2_DERSTR_AFEF00				(BIT3)
#define		ECC_MECCCAP_ID_PE5CL2_DERSTR_DEDF00				(BIT1)
/* ID_OVFSTR */
#define		ECC_MECCCAP_ID_PE5CL2_OVFSTR_1					(BIT1)
#define		ECC_MECCCAP_ID_PE5CL2_OVFSTR_0					(BIT0)
/* ID_SERINF */
#define		ECC_MECCCAP_ID_PE5CL2_SERINF_03					(BIT3)
#define		ECC_MECCCAP_ID_PE5CL2_SERINF_02					(BIT2)
#define		ECC_MECCCAP_ID_PE5CL2_SERINF_01					(BIT1)
#define		ECC_MECCCAP_ID_PE5CL2_SERINF_00					(BIT0)
/* ID_00SEADR */
#define		ECC_MECCCAP_ID_PE5CL2_SEADR_SEDL				(BIT31 + BIT30 + BIT29 + BIT28 + BIT27)
#define		ECC_MECCCAP_ID_PE5CL2_SEADR_SEADR0				(0x00001FF8U)
/* ID_00DEADR */
#define		ECC_MECCCAP_ID_PE5CL2_DEADR_DEDL				(BIT31 + BIT30 + BIT29 + BIT28 + BIT27)
#define		ECC_MECCCAP_ID_PE5CL2_DEADR_DEADR0				(0x00001FF8U)

/* DMAC / DTS RAM ECC and Address Feedback */
/* Module: ECCCNT_DTS */
/* DRECCCTL */
#define		ECC_ECCCNT_DTS_DRECCCTL_AFEDIS					(BIT3)
#define		ECC_ECCCNT_DTS_DRECCCTL_SECDIS					(BIT1)
#define		ECC_ECCCNT_DTS_DRECCCTL_ECCDIS					(BIT0)
	#define		ECC_ECCCNT_DTS_DRECCCTL_ENABLE				(0)
	#define		ECC_ECCCNT_DTS_DRECCCTL_DISABLE				(1)
/* DRECCTSTCTL */
#define		ECC_ECCCNT_DTS_DRECCTSTCTL_ECCTST				(BIT1)
	#define		ECC_ECCCNT_DTS_TSTCTL_ECCTST_NORMAL			(0)
	#define		ECC_ECCCNT_DTS_TSTCTL_ECCTST_TEST			(1)
/* DRAFINV */
#define		ECC_ECCCNT_DTS_DRAFINV_AFINV					(0x00000FFCU)
/* DRECCTSTDIN0 */
/* No bit definition required because it only has byte access */
/* DRECCTSTEIN */
#define		ECC_ECCCNT_DTS_DRECCTSTEIN_ECC					(BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)
/* $DRTDATBFDATAF0 */
/* No bit definition required because it only has byte access */
/* DRTDATBFECCF */
#define		ECC_ECCCNT_DTS_DRTDATBFECCF_BFECC0				(BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)

/* Module: ECCCNT_DMDE0 */
/* DEECCCTL */
#define		ECC_ECCCNT_DMDE0_DEECCCTL_AFEDIS				(BIT3)
#define		ECC_ECCCNT_DMDE0_DEECCCTL_SECDIS				(BIT1)
#define		ECC_ECCCNT_DMDE0_DEECCCTL_ECCDIS				(BIT0)
	#define		ECC_ECCCNT_DMDE0_DEECCCTL_DISABLE			(1)
	#define		ECC_ECCCNT_DMDE0_DEECCCTL_ENABLE			(0)
/* DEECCTSTCTL */
#define		ECC_ECCCNT_DMDE0_DEECCTSTCTL_ECCTST				(BIT1)
	#define		ECC_ECCCNT_DMDE0_TSTCTL_TST_NORMAL			(0)
	#define		ECC_ECCCNT_DMDE0_TSTCTL_TST_TEST			(1)
#define		ECC_ECCCNT_DMDE0_DEECCTSTCTL_AFSEL				(BIT0)
	#define		ECC_ECCCNT_DMDE0_TSTCTL_AS_DESCRIPTOR_RAM	(0)
	#define		ECC_ECCCNT_DMDE0_TSTCTL_AS_CHANNEL_CONTROLLER	(1)
/* DEAFINV */
#define		ECC_ECCCNT_DMDE0_DEAFINV_AFINV					(BIT11 + BIT10 + BIT9 + BIT8 + BIT7 + BIT6 + BIT5 + BIT4 + BIT3 + BIT2)
/* DEECCTSTDIN0 */
/* No bit definition required because it only has byte access */
/* DEECCTSTEIN */
#define		ECC_ECCCNT_DMDE0_DEECCTSTEIN_ECC				(BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)

/* DETDATBFDATAF0 */
/* No bit definition required because it only has byte access */
/* DETDATBFECCF */
#define		ECC_ECCCNT_DMDE0_DETDATBFECCF_BFECC0			(BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)


/* Module: ECCCNT_DMDA0 */
/* DAECCCTL */
#define		ECC_ECCCNT_DMDA0_DAECCCTL_SECDIS				(BIT1)
#define		ECC_ECCCNT_DMDA0_DAECCCTL_ECCDIS				(BIT0)
	#define		ECC_ECCCNT_DMDA0_DAECCCTL_DISABLE			(1)
	#define		ECC_ECCCNT_DMDA0_DAECCCTL_ENABLE			(0)
/* DAECCTSTCTL */
#define		ECC_ECCCNT_DMDA0_DAECCTSTCTL_ECCTST				(BIT1)
	#define		ECC_ECCCNT_DMDA0_TSTCTL_TST_NORMAL			(0)
	#define		ECC_ECCCNT_DMDA0_TSTCTL_TST_TEST			(1)
/* DAECCTSTDIN0 */
/* No bit definition required because it only has byte access */
/* DAECCTSTDIN1 */
/* No bit definition required because it only has byte access */
/* DAECCTSTEIN */
#define		ECC_ECCCNT_DMDAO_DAECCTSTEIN_ECC				(0x000000FFU)
/* DATDATBFDATAF0 */
/* No bit definition required because it only has byte access */
/* DATDATBFDATAF1 */
/* No bit definition required because it only has byte access */
/* DATDATBFECCF */
#define		ECC_ECCCNT_DMDA0_DATDATBFECCF_BFECC0			(0x000000FFU)

/* Module: ECCCNT_DMDE1 */
/* DEECCCTL */
#define		ECC_ECCCNT_DMDE1_DEECCCTL_AFEDIS				(BIT3)
#define		ECC_ECCCNT_DMDE1_DEECCCTL_SECDIS				(BIT1)
#define		ECC_ECCCNT_DMDE1_DEECCCTL_ECCDIS				(BIT0)
	#define		ECC_ECCCNT_DMDE1_DEECCCTL_DISABLE			(1)
	#define		ECC_ECCCNT_DMDE1_DEECCCTL_ENABLE			(0)
/* DEECCTSTCTL */
#define		ECC_ECCCNT_DMDE1_DEECCTSTCTL_ECCTST				(BIT1)
	#define		ECC_ECCCNT_DMDE1_TSTCTL_TST_NORMAL			(0)
	#define		ECC_ECCCNT_DMDE1_TSTCTL_TST_TEST			(1)
#define		ECC_ECCCNT_DMDE1_DEECCTSTCTL_AFSEL				(BIT0)
	#define		ECC_ECCCNT_DMDE1_TSTCTL_AS_DESCRIPTOR_RAM	(0)
	#define		ECC_ECCCNT_DMDE1_TSTCTL_AS_CHANNEL_CONTROLLER	(1)
/* DEAFINV */
#define		ECC_ECCCNT_DMDE1_DEAFINV_AFINV					(BIT11 + BIT10 + BIT9 + BIT8 + BIT7 + BIT6 + BIT5 + BIT4 + BIT3 + BIT2)
/* DEECCTSTDIN0 */
/* No bit definition required because it only has byte access */
/* DEECCTSTEIN */
#define		ECC_ECCCNT_DMDE1_DEECCTSTEIN_ECC				(BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)
/* DETDATBFDATAF0 */
/* No bit definition required because it only has byte access */
/* DETDATBFECCF */
#define		ECC_ECCCNT_DMDE1_DETDATBFECCF_BFECC0			(BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)

/* Module: ECCCNT_DMDA1 */
/* DAECCCTL */
#define		ECC_ECCCNT_DMDA1_DAECCCTL_SECDIS				(BIT1)
#define		ECC_ECCCNT_DMDA1_DAECCCTL_ECCDIS				(BIT0)
	#define		ECC_ECCCNT_DMDA1_DAECCCTL_DISABLE			(1)
	#define		ECC_ECCCNT_DMDA1_DAECCCTL_ENABLE			(0)
/* DAECCTSTCTL */
#define		ECC_ECCCNT_DMDA1_DAECCTSTCTL_ECCTST				(BIT1)
	#define		ECC_ECCCNT_DMDA1_TSTCTL_TST_NORMAL			(0)
	#define		ECC_ECCCNT_DMDA1_TSTCTL_TST_TEST			(1)
/* DAECCTSTDIN0 */
/* No bit definition required because it only has byte access */
/* DAECCTSTDIN1 */
/* No bit definition required because it only has byte access */
/* DAECCTSTEIN */
#define		ECC_ECCCNT_DMDA1_DAECCTSTEIN_ECC				(0x000000FFU)
/* DATDATBFDATAF0 */
/* No bit definition required because it only has byte access */
/* DATDATBFDATAF1 */
/* No bit definition required because it only has byte access */
/* DATDATBFECCF */
#define		ECC_ECCCNT_DMDA1_DATDATBFECCF_BFECC0			(0x000000FFU)

/* Module: MECCCAP_DTS */
/* DR_ERRINT */
#define		ECC_MECCCAP_DTS_DR_ERRINT_SEOVFIE				(BIT7)
#define		ECC_MECCCAP_DTS_DR_ERRINT_AFEIE					(BIT3)
#define		ECC_MECCCAP_DTS_DR_ERRINT_DEDIE					(BIT1)
#define		ECC_MECCCAP_DTS_DR_ERRINT_SEDIE					(BIT0)
	#define		ECC_MECCCAP_DTS_DR_ERRINT_DISABLE			(0)
	#define		ECC_MECCCAP_DTS_DR_ERRINT_ENABLE			(1)
/* DR_SSTCLR */
#define		ECC_MECCCAP_DTS_DR_SSTCLR_SSTCLR00				(BIT0)
	#define		ECC_MECCCAP_DTS_DR_SSTCLR_CLEAR				(1)
/* DR_DSTCLR */
#define		ECC_MECCCAP_DTS_DR_DSTCLR_DSTCLR00				(BIT0)
	#define		ECC_MECCCAP_DTS_DR_DSTCLR_CLEAR				(1)
/* DR_OVFCLR */
#define		ECC_MECCCAP_DTS_DR_OVFCLR_SERROVFCLR0			(BIT0)
	#define		ECC_MECCCAP_DTS_DR_OVFCLR_CLEAR				(1)
/* DR_SERSTR */
#define		ECC_MECCCAP_DTS_DR_SERSTR_SEDF00				(BIT0)
/* DR_DERSTR */
#define		ECC_MECCCAP_DTS_DR_DERSTR_AFEF00				(BIT3)
#define		ECC_MECCCAP_DTS_DR_DERSTR_DEDF00				(BIT1)
/* DR_OVFSTR */
#define		ECC_MECCCAP_DTS_DR_OVFSTR_SERROVF0				(BIT0)
/* DR_SERINF */
#define		ECC_MECCCAP_DTS_DR_SERINF_SEDLINF00				(BIT0)
/* DR_00SEADR */
#define		ECC_MECCCAP_DTS_DR_SEADR_SEDL					(BIT31 + BIT30 + BIT29 + BIT28 + BIT27)
#define		ECC_MECCCAP_DTS_DR_SEADR_SEADR0					(0x00000FFCU)
/* DR_00DEADR */
#define		ECC_MECCCAP_DTS_DR_DEADR_DEDL					(BIT31 + BIT30 + BIT29 + BIT28 + BIT27)
#define		ECC_MECCCAP_DTS_DR_DEADR_DEADR0					(0x00000FFCU)

/* Module: MECCCAP_DMDE0 */
/* DE_ERRINT */
#define		ECC_MECCCAP_DMDE0_DE_ERRINT_SEOVFIE				(BIT7)
#define		ECC_MECCCAP_DMDE0_DE_ERRINT_AFEIE				(BIT3)
#define		ECC_MECCCAP_DMDE0_DE_ERRINT_DEDIE				(BIT1)
#define		ECC_MECCCAP_DMDE0_DE_ERRINT_SEDIE				(BIT0)
	#define		ECC_MECCCAP_DMDE0_DE_ERRINT_DISABLE			(0)
	#define		ECC_MECCCAP_DMDE0_DE_ERRINT_ENABLE			(1)
/* DE_SSTCLR */
#define		ECC_MECCCAP_DMDE0_DE_SSTCLR_SSTCLR00			(BIT0)
	#define		ECC_MECCCAP_DMDE0_DE_SSTCLR_CLEAR			(1)
/* DE_DSTCLR */
#define		ECC_MECCCAP_DMDE0_DE_DSTCLR_DSTCLR00			(BIT0)
	#define		ECC_MECCCAP_DMDE0_DE_DSTCLR_CLEAR			(1)
/* DE_OVFCLR */
#define		ECC_MECCCAP_DMDE0_DE_OVFCLR_SERROVFCLR0			(BIT0)
	#define		ECC_MECCCAP_DMDE0_DE_OVFCLR_CLEAR			(1)
/* DE_SERSTR */
#define		ECC_MECCCAP_DMDE0_DE_SERSTR_SEDF00				(BIT0)
/* DE_DERSTR */
#define		ECC_MECCCAP_DMDE0_DE_DERSTR_AFEF00				(BIT3)
#define		ECC_MECCCAP_DMDE0_DE_DERSTR_DEDF00				(BIT1)
/* DE_OVFSTR */
#define		ECC_MECCCAP_DMDE0_DE_OVFSTR_SERROVF0			(BIT0)
/* DE_SERINF */
#define		ECC_MECCCAP_DMDE0_DE_SERINF_SEDLINF00			(BIT0)
/* DE_00SEADR */
#define		ECC_MECCCAP_DMDE0_DE_SEADR_SEDL					(BIT31 + BIT30 + BIT29 + BIT28 + BIT27)
#define		ECC_MECCCAP_DMDE0_DE_SEADR_SEADR0				(0x00000FFCU)
/* DE_00DEADR */
#define		ECC_MECCCAP_DMDE0_DE_DEADR_DEDL					(BIT31 + BIT30 + BIT29 + BIT28 + BIT27)
#define		ECC_MECCCAP_DMDE0_DE_DEADR_DEADR0				(0x00000FFCU)

/* Module: MECCCAP_DMDA0 */
/* DA_ERRINT */
#define		ECC_MECCCAP_DMDA0_DA_ERRINT_SEOVFIE				(BIT7)
#define		ECC_MECCCAP_DMDA0_DA_ERRINT_DEDIE				(BIT1)
#define		ECC_MECCCAP_DMDA0_DA_ERRINT_SEDIE				(BIT0)
	#define		ECC_MECCCAP_DMDA0_DA_ERRINT_DISABLE			(0)
	#define		ECC_MECCCAP_DMDA0_DA_ERRINT_ENABLE			(1)
/* DA_SSTCLR */
#define		ECC_MECCCAP_DMDA0_DA_SSTCLR_SSTCLR00			(BIT0)
	#define		ECC_MECCCAP_DMDA0_DA_SSTCLR_CLEAR			(1)
/* DA_DSTCLR */
#define		ECC_MECCCAP_DMDA0_DA_DSTCLR_DSTCLR00			(BIT0)
	#define		ECC_MECCCAP_DMDA0_DA_DSTCLR_CLEAR			(1)
/* DA_OVFCLR */
#define		ECC_MECCCAP_DMDA0_DA_OVFCLR_SERROVFCLR0			(BIT0)
	#define		ECC_MECCCAP_DMDA0_DA_OVFCLR_CLEAR			(1)
/* DA_SERSTR */
#define		ECC_MECCCAP_DMDA0_DA_SERSTR_SEDF00				(BIT0)
/* DA_DERSTR */
#define		ECC_MECCCAP_DMDA0_DA_DERSTR_DEDF00				(BIT1)
/* DA_OVFSTR */
#define		ECC_MECCCAP_DMDA0_DA_OVFSTR_SERROVF0			(BIT0)
/* DA_SERINF */
#define		ECC_MECCCAP_DMDA0_DA_SERINF_SEDLINF00			(BIT0)
/* DA_00SEADR */
#define		ECC_MECCCAP_DMDA0_DA_SEADR_SEDL					(BIT31 + BIT30 + BIT29 + BIT28 + BIT27)
#define		ECC_MECCCAP_DMDA0_DA_SEADR_SEADR0				(0x000007F8U)
/* DA_00DEADR */
#define		ECC_MECCCAP_DMDA0_DA_DEADR_DEDL					(BIT31 + BIT30 + BIT29 + BIT28 + BIT27)
#define		ECC_MECCCAP_DMDA0_DA_DEADR_DEADR0				(0x000007F8U)

/* Module: MECCCAP_DMDE1 */
/* DE_ERRINT */
#define		ECC_MECCCAP_DMDE1_DE_ERRINT_SEOVFIE				(BIT7)
#define		ECC_MECCCAP_DMDE1_DE_ERRINT_AFEIE				(BIT3)
#define		ECC_MECCCAP_DMDE1_DE_ERRINT_DEDIE				(BIT1)
#define		ECC_MECCCAP_DMDE1_DE_ERRINT_SEDIE				(BIT0)
	#define		ECC_MECCCAP_DMDE1_DE_ERRINT_DISABLE			(0)
	#define		ECC_MECCCAP_DMDE1_DE_ERRINT_ENABLE			(1)
/* DE_SSTCLR */
#define		ECC_MECCCAP_DMDE1_DE_SSTCLR_SSTCLR00			(BIT0)
	#define		ECC_MECCCAP_DMDE1_DE_SSTCLR_CLEAR			(1)
/* DE_DSTCLR */
#define		ECC_MECCCAP_DMDE1_DE_DSTCLR_DSTCLR00			(BIT0)
	#define		ECC_MECCCAP_DMDE1_DE_DSTCLR_CLEAR			(1)
/* DE_OVFCLR */
#define		ECC_MECCCAP_DMDE1_DE_OVFCLR_SERROVFCLR0			(BIT0)
	#define		ECC_MECCCAP_DMDE1_DE_OVFCLR_CLEAR			(1)
/* DE_SERSTR */
#define		ECC_MECCCAP_DMDE1_DE_SERSTR_SEDF00				(BIT0)
/* DE_DERSTR */
#define		ECC_MECCCAP_DMDE1_DE_DERSTR_AFEF00				(BIT3)
#define		ECC_MECCCAP_DMDE1_DE_DERSTR_DEDF00				(BIT1)
/* DE_OVFSTR */
#define		ECC_MECCCAP_DMDE1_DE_OVFSTR_SERROVF0			(BIT0)
/* DE_SERINF */
#define		ECC_MECCCAP_DMDE1_DE_SERINF_SEDLINF00			(BIT0)
/* DE_00SEADR */
#define		ECC_MECCCAP_DMDE1_DE_SEADR_SEDL					(BIT31 + BIT30 + BIT29 + BIT28 + BIT27)
#define		ECC_MECCCAP_DMDE1_DE_SEADR_SEADR0				(0x00000FFCU)
/* DE_00DEADR */
#define		ECC_MECCCAP_DMDE1_DE_DEADR_DEDL					(BIT31 + BIT30 + BIT29 + BIT28 + BIT27)
#define		ECC_MECCCAP_DMDE1_DE_DEADR_DEADR0				(0x00000FFCU)

/* Module: MECCCAP_DMDA1 */
/* DA_ERRINT */
#define		ECC_MECCCAP_DMDA1_DA_ERRINT_SEOVFIE				(BIT7)
#define		ECC_MECCCAP_DMDA1_DA_ERRINT_DEDIE				(BIT1)
#define		ECC_MECCCAP_DMDA1_DA_ERRINT_SEDIE				(BIT0)
	#define		ECC_MECCCAP_DMDA1_DA_ERRINT_DISABLE			(0)
	#define		ECC_MECCCAP_DMDA1_DA_ERRINT_ENABLE			(1)
/* DA_SSTCLR */
#define		ECC_MECCCAP_DMDA1_DA_SSTCLR_SSTCLR00			(BIT0)
	#define		ECC_MECCCAP_DMDA1_DA_SSTCLR_CLEAR			(1)
/* DA_DSTCLR */
#define		ECC_MECCCAP_DMDA1_DA_DSTCLR_DSTCLR00			(BIT0)
	#define		ECC_MECCCAP_DMDA1_DA_DSTCLR_CLEAR			(1)
/* DA_OVFCLR */
#define		ECC_MECCCAP_DMDA1_DA_OVFCLR_SERROVFCLR0			(BIT0)
	#define		ECC_MECCCAP_DMDA1_DA_OVFCLR_CLEAR			(1)
/* DA_SERSTR */
#define		ECC_MECCCAP_DMDA1_DA_SERSTR_SEDF00				(BIT0)
/* DA_DERSTR */
#define		ECC_MECCCAP_DMDA1_DA_DERSTR_DEDF00				(BIT1)
/* DA_OVFSTR */
#define		ECC_MECCCAP_DMDA1_DA_OVFSTR_SERROVF0			(BIT0)
/* DA_SERINF */
#define		ECC_MECCCAP_DMDA1_DA_SERINF_SEDLINF00			(BIT0)
/* DA_00SEADR */
#define		ECC_MECCCAP_DMDA1_DA_SEADR_SEDL					(BIT31 + BIT30 + BIT29 + BIT28 + BIT27)
#define		ECC_MECCCAP_DMDA1_DA_SEADR_SEADR0				(0x000007F8U)
/* DA_00DEADR */
#define		ECC_MECCCAP_DMDA1_DA_DEADR_DEDL					(BIT31 + BIT30 + BIT29 + BIT28 + BIT27)
#define		ECC_MECCCAP_DMDA1_DA_DEADR_DEADR0				(0x000007F8U)


/* ECC for Peripheral RAM (32 Bits) */
/* Module: ECC7 */
/* E710CTL */
#define		ECC_ECC7_E710CTL_EMCA							(BIT15 + BIT14)
	#define		ECC_ECC7_E710CTL_EMCA_WRITE					(0x01U)
#define		ECC_ECC7_E710CTL_EMCA_0							(BIT14)
#define		ECC_ECC7_E710CTL_ECOVFF							(BIT11)
#define		ECC_ECC7_E710CTL_ECER2C							(BIT10)
	#define		ECC_ECC7_E710CTL_ECER2C_WRITE				(1)
#define		ECC_ECC7_E710CTL_ECER1C							(BIT9)
	#define		ECC_ECC7_E710CTL_ECER1C_WRITE				(1)
#define		ECC_ECC7_E710CTL_ECTHM							(BIT7)
	#define		ECC_ECC7_E710CTL_ECTHM_ENABLE				(0)
	#define		ECC_ECC7_E710CTL_ECTHM_DISABLE				(1)
#define		ECC_ECC7_E710CTL_EC1ECP							(BIT5)
	#define		ECC_ECC7_E710CTL_EC1ECP_ENABLE				(0)
	#define		ECC_ECC7_E710CTL_EC1ECP_DISABLE				(1)
#define		ECC_ECC7_E710CTL_EC2EDIC						(BIT4)
	#define		ECC_ECC7_E710CTL_EC2EDIC_NOTNOTIFIED		(0)
	#define		ECC_ECC7_E710CTL_EC2EDIC_NOTIFIED			(1)
#define		ECC_ECC7_E710CTL_EC1EDIC						(BIT3)
	#define		ECC_ECC7_E710CTL_EC1EDIC_NOTNOTIFIED		(0)
	#define		ECC_ECC7_E710CTL_EC1EDIC_NOTIFIED			(1)
#define		ECC_ECC7_E710CTL_ECER2F							(BIT2)
#define		ECC_ECC7_E710CTL_ECER1F							(BIT1)
#define		ECC_ECC7_E710CTL_ECEMF							(BIT0)
/* E710TMC */
#define		ECC_ECC7_E710TMC_ETMA							(BIT15 + BIT14)
	#define		ECC_ECC7_E710TMC_ETMA_WRITE					(0x02U)
#define		ECC_ECC7_E710TMC_ETMA_0							(BIT14)
#define		ECC_ECC7_E710TMC_ECTMCE							(BIT7)
	#define		ECC_ECC7_E710TMC_ECTMCE_DISABLE				(0)
	#define		ECC_ECC7_E710TMC_ECTMCE_ENABLE				(1)
#define		ECC_ECC7_E710TMC_ECTRRS							(BIT4)
	#define		ECC_ECC7_E710TMC_ECTRRS_DISABLE				(0)
	#define		ECC_ECC7_E710TMC_ECTRRS_ENABLE				(1)
#define		ECC_ECC7_E710TMC_ECREOS							(BIT3)
	#define		ECC_ECC7_E710TMC_ECREOS_RESULT				(0)
	#define		ECC_ECC7_E710TMC_ECREOS_VALUE				(1)
#define		ECC_ECC7_E710TMC_ECENS							(BIT2)
	#define		ECC_ECC7_E710TMC_ECENS_WRITE				(0)
	#define		ECC_ECC7_E710TMC_ECENS_VALUE				(1)
#define		ECC_ECC7_E710TMC_ECDCS							(BIT1)
	#define		ECC_ECC7_E710TMC_ECDCS_LOWER32BIT			(0)
	#define		ECC_ECC7_E710TMC_ECDCS_VALUE				(1)
#define		ECC_ECC7_E710TMC_ECREIS							(BIT0)
	#define		ECC_ECC7_E710TMC_ECREIS_UPPER7BIT			(0)
	#define		ECC_ECC7_E710TMC_ECREIS_VALUE				(1)
/* E710TRC */
#define		ECC_ECC7_E710TRC_ECSYND							(0xFF000000U)
#define		ECC_ECC7_E710TRC_ECSYND_0						(BIT24)
#define		ECC_ECC7_E710TRC_ECHORD							(0x00FF0000U)
#define		ECC_ECC7_E710TRC_ECHORD_0						(BIT16)
#define		ECC_ECC7_E710TRC_ECECRD							(0x0000FF00U)
#define		ECC_ECC7_E710TRC_ECECRD_0						(BIT8)
#define		ECC_ECC7_E710TRC_ECERDB							(0x000000FFU)
#define		ECC_ECC7_E710TRC_ECERDB_0						(BIT0)
/* E710TED */
/* No bit definition required because it only has byte access */
/* E710EAD */
/* No bit definition required because it only has byte access */

/* ECC for Peripheral RAM (16 Bits) */
/* Module: ECC6 */
/* E610CTL */
#define		ECC_ECC6_E610CTL_EMCA							(BIT15 + BIT14)
	#define		ECC_ECC6_E610CTL_EMCA_WRITE					(0x01U)
#define		ECC_ECC6_E610CTL_EMCA_0							(BIT14)
#define		ECC_ECC6_E610CTL_ECOVFF							(BIT11)
#define		ECC_ECC6_E610CTL_ECER2C							(BIT10)
	#define		ECC_ECC6_E610CTL_ECER2C_WRITE				(1)
#define		ECC_ECC6_E610CTL_ECER1C							(BIT9)
	#define		ECC_ECC6_E610CTL_ECER1C_WRITE				(1)
#define		ECC_ECC6_E610CTL_ECTHM							(BIT7)
	#define		ECC_ECC6_E610CTL_ECTHM_ENABLE				(0)
	#define		ECC_ECC6_E610CTL_ECTHM_DISABLE				(1)
#define		ECC_ECC6_E610CTL_EC1ECP							(BIT5)
	#define		ECC_ECC6_E610CTL_EC1ECP_ENABLE				(0)
	#define		ECC_ECC6_E610CTL_EC1ECP_DISABLE				(1)
#define		ECC_ECC6_E610CTL_EC2EDIC						(BIT4)
	#define		ECC_ECC6_E610CTL_EC2EDIC_NOTNOTIFIED		(0)
	#define		ECC_ECC6_E610CTL_EC2EDIC_NOTIFIED			(1)
#define		ECC_ECC6_E610CTL_EC1EDIC						(BIT3)
	#define		ECC_ECC6_E610CTL_EC1EDIC_NOTNOTIFIED		(0)
	#define		ECC_ECC6_E610CTL_EC1EDIC_NOTIFIED			(1)
#define		ECC_ECC6_E610CTL_ECER2F							(BIT2)
#define		ECC_ECC6_E610CTL_ECER1F							(BIT1)
#define		ECC_ECC6_E610CTL_ECEMF							(BIT0)
/* E610TMC */
#define		ECC_ECC6_E610TMC_ETMA							(BIT15 + BIT14)
	#define		ECC_ECC6_E610TMC_ETMA_WRITE					(0x02U)
#define		ECC_ECC6_E610TMC_ETMA_0							(BIT14)
#define		ECC_ECC6_E610TMC_ECTMCE							(BIT7)
	#define		ECC_ECC6_E610TMC_ECTMCE_DISABLE				(0)
	#define		ECC_ECC6_E610TMC_ECTMCE_ENABLE				(1)
#define		ECC_ECC6_E610TMC_ECTRRS							(BIT4)
	#define		ECC_ECC6_E610TMC_ECTRRS_DISABLE				(0)
	#define		ECC_ECC6_E610TMC_ECTRRS_ENABLE				(1)
#define		ECC_ECC6_E610TMC_ECREOS							(BIT3)
	#define		ECC_ECC6_E610TMC_ECREOS_RESULT				(0)
	#define		ECC_ECC6_E610TMC_ECREOS_VALUE				(1)
#define		ECC_ECC6_E610TMC_ECENS							(BIT2)
	#define		ECC_ECC6_E610TMC_ECENS_WRITE				(0)
	#define		ECC_ECC6_E610TMC_ECENS_VALUE				(1)
#define		ECC_ECC6_E610TMC_ECDCS							(BIT1)
	#define		ECC_ECC6_E610TMC_ECDCS_LOWER16BIT			(0)
	#define		ECC_ECC6_E610TMC_ECDCS_VALUE				(1)
#define		ECC_ECC6_E610TMC_ECREIS							(BIT0)
	#define		ECC_ECC6_E610TMC_ECREIS_UPPER6BIT			(0)
	#define		ECC_ECC6_E610TMC_ECREIS_VALUE				(1)
/* E610TRC */
#define		ECC_ECC6_E610TRC_ECSYND							(0xFF000000U)
#define		ECC_ECC6_E610TRC_ECSYND_0						(BIT24)
#define		ECC_ECC6_E610TRC_ECHORD							(0x00FF0000U)
#define		ECC_ECC6_E610TRC_ECHORD_0						(BIT16)
#define		ECC_ECC6_E610TRC_ECECRD							(0x0000FF00U)
#define		ECC_ECC6_E610TRC_ECECRD_0						(BIT8)
#define		ECC_ECC6_E610TRC_ECRODM							(0x000000FFU)
#define		ECC_ECC6_E610TRC_ECRODM_0						(BIT0)
/* E610TED */
#define		ECC_ECC6_E610TED_ECEDB							(0xFFFF0000U)
#define		ECC_ECC6_E610TED_ECEDB_0						(BIT16)
#define		ECC_ECC6_E610TED_ECRIDM							(0x0000FF00U)
#define		ECC_ECC6_E610TED_ECRIDM_0						(BIT8)
#define		ECC_ECC6_E610TED_ECERDB							(0x000000FFU)
#define		ECC_ECC6_E610TED_ECERDB_0						(BIT0)
/* E610EAD */
/* No bit definition required because it only has byte access */


/* Safety Mechanism on Data Transfer Path */
/* Module: ECCCNT_A */
/* BUSAECCCTL */
#define		ECC_ECCCNT_A_BUSAECCCTL_ECCDIS					(BIT0)
	#define		ECC_ECCCNT_A_ECCCTL_ECCDIS_ENABLE			(0)
	#define		ECC_ECCCNT_A_ECCCTL_ECCDIS_DISABLE			(1)
/* BUSAECCTSTCTL */
#define		ECC_ECCCNT_A_BUSAECCTSTCTL_ECCTST				(BIT1)
	#define		ECC_ECCCNT_A_TSTCTL_ECCTST_NORMAL			(0)
	#define		ECC_ECCCNT_A_TSTCTL_ECCTST_TEST				(1)
/* BUSAECCTSTDIN0 */
/* No bit definition required because it only has byte access */
/* BUSAECCTSTEIN */
#define		ECC_ECCCNT_A_BUSAECCTSTEIN_ECC					(BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)

/* DFP_ECCCNT_BUSA_FNT */
/* BUSAECCCTL */
#define		ECC_DFP_ECCCNT_BUSA_FNT_ECCCTL_ECCDIS			(BIT0)
	#define		ECC_DFP_ECCCNT_B_FNT_CTL_DIS_ENABLE			(0)
	#define		ECC_DFP_ECCCNT_B_FNT_CTL_DIS_DISABLE		(1)
/* BUSAECCTSTCTL */
#define		ECC_DFP_ECCCNT_BUSA_FNT_ECCTSTCTL_ECCTST		(BIT1)
	#define		ECC_DFP_ECCCNT_B_FNT_TCTL_TST_NORMAL		(0)
	#define		ECC_DFP_ECCCNT_B_FNT_TCTL_TST_TEST			(1)
/* BUSAECCTSTDIN0 */
/* No bit definition required because it only has byte access */
/* BUSAECCTSTEIN */
#define		ECC_DFP_ECCCNT_BUSA_FNT_BUSAECCTSTEIN_ECC		(BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)

/* Module: ECCCNT_D_V2XWCL0 */
/* BUSDVCECCCTL */
#define		ECC_ECCCNT_D_V2XWCL0_ECCCTL_SECDIS				(BIT1)
	#define		ECC_ECCCNT_D_V2XWCL0_CTL_SD_CORRECT			(0)
	#define		ECC_ECCCNT_D_V2XWCL0_CTL_SD_NOTCORRECT		(1)
#define		ECC_ECCCNT_D_V2XWCL0_ECCCTL_ECCDIS				(BIT0)
	#define		ECC_ECCCNT_D_V2XWCL0_CTL_ED_ENABLE			(0)
	#define		ECC_ECCCNT_D_V2XWCL0_CTL_ED_DISABLE			(1)
/* BUSDVCECCTSTCTL */
#define		ECC_ECCCNT_D_V2XWCL0_TSTCTL_ECCTST				(BIT1)
	#define		ECC_ECCCNT_D_V2XWCL0_TCTL_TST_NORMAL		(0)
	#define		ECC_ECCCNT_D_V2XWCL0_TCTL_TST_TEST			(1)
#define		ECC_ECCCNT_D_V2XWCL0_TSTCTL_DATSEL				(BIT0)
	#define		ECC_ECCCNT_D_V2XWCL0_TCTL_DS_LOWER			(0)
	#define		ECC_ECCCNT_D_V2XWCL0_TCTL_DS_UPPER			(1)
/* BUSDVCECCTSTDIN0 */
/* No bit definition required because it only has byte access */
/* BUSDVCECCTSTEIN */
#define		ECC_ECCCNT_D_V2XWCL0_BUSDVCECCTSTEIN_ECC		(BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)

/* Module: ECCCNT_D_V2XRCL0 */
/* BUSDVCECCCTL */
#define		ECC_ECCCNT_D_V2XRCL0_ECCCTL_SECDIS				(BIT1)
	#define		ECC_ECCCNT_D_V2XRCL0_CTL_SD_CORRECT			(0)
	#define		ECC_ECCCNT_D_V2XRCL0_CTL_SD_NOTCORRECT		(1)
#define		ECC_ECCCNT_D_V2XRCL0_ECCCTL_ECCDIS				(BIT0)
	#define		ECC_ECCCNT_D_V2XRCL0_CTL_ED_ENABLE			(0)
	#define		ECC_ECCCNT_D_V2XRCL0_CTL_ED_DISABLE			(1)
/* BUSDVCECCTSTCTL */
#define		ECC_ECCCNT_D_V2XRCL0_TSTCTL_ECCTST				(BIT1)
	#define		ECC_ECCCNT_D_V2XRCL0_TCTL_TST_NORMAL		(0)
	#define		ECC_ECCCNT_D_V2XRCL0_TCTL_TST_TEST			(1)
#define		ECC_ECCCNT_D_V2XRCL0_TSTCTL_DATSEL				(BIT0)
	#define		ECC_ECCCNT_D_V2XRCL0_TCTL_DS_LOWER			(0)
	#define		ECC_ECCCNT_D_V2XRCL0_TCTL_DS_UPPER			(1)
/* BUSDVCECCTSTDIN0 */
/* No bit definition required because it only has byte access */
/* BUSDVCECCTSTEIN */
#define		ECC_ECCCNT_D_V2XRCL0_BUSDVCECCTSTEIN_ECC		(BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)

/* Module: ECCCNT_D_V2XWCL1 */
/* BUSDVCECCCTL */
#define		ECC_ECCCNT_D_V2XWCL1_ECCCTL_SECDIS				(BIT1)
	#define		ECC_ECCCNT_D_V2XWCL1_CTL_SD_CORRECT			(0)
	#define		ECC_ECCCNT_D_V2XWCL1_CTL_SD_NOTCORRECT		(1)
#define		ECC_ECCCNT_D_V2XWCL1_ECCCTL_ECCDIS				(BIT0)
	#define		ECC_ECCCNT_D_V2XWCL1_CTL_ED_ENABLE			(0)
	#define		ECC_ECCCNT_D_V2XWCL1_CTL_ED_DISABLE			(1)
/* BUSDVCECCTSTCTL */
#define		ECC_ECCCNT_D_V2XWCL1_TSTCTL_ECCTST				(BIT1)
	#define		ECC_ECCCNT_D_V2XWCL1_TCTL_TST_NORMAL		(0)
	#define		ECC_ECCCNT_D_V2XWCL1_TCTL_TST_TEST			(1)
#define		ECC_ECCCNT_D_V2XWCL1_TSTCTL_DATSEL				(BIT0)
	#define		ECC_ECCCNT_D_V2XWCL1_TCTL_DS_LOWER			(0)
	#define		ECC_ECCCNT_D_V2XWCL1_TCTL_DS_UPPER			(1)
/* BUSDVCECCTSTDIN0 */
/* No bit definition required because it only has byte access */
/* BUSDVCECCTSTEIN */
#define		ECC_ECCCNT_D_V2XWCL1_BUSDVCECCTSTEIN_ECC		(BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)

/* Module: ECCCNT_D_V2XRCL1 */
/* BUSDVCECCCTL */
#define		ECC_ECCCNT_D_V2XRCL1_ECCCTL_SECDIS				(BIT1)
	#define		ECC_ECCCNT_D_V2XRCL1_CTL_SD_CORRECT			(0)
	#define		ECC_ECCCNT_D_V2XRCL1_CTL_SD_NOTCORRECT		(1)
#define		ECC_ECCCNT_D_V2XRCL1_ECCCTL_ECCDIS				(BIT0)
	#define		ECC_ECCCNT_D_V2XRCL1_CTL_ED_ENABLE			(0)
	#define		ECC_ECCCNT_D_V2XRCL1_CTL_ED_DISABLE			(1)
/* BUSDVCECCTSTCTL */
#define		ECC_ECCCNT_D_V2XRCL1_TSTCTL_ECCTST				(BIT1)
	#define		ECC_ECCCNT_D_V2XRCL1_TCTL_TST_NORMAL		(0)
	#define		ECC_ECCCNT_D_V2XRCL1_TCTL_TST_TEST			(1)
#define		ECC_ECCCNT_D_V2XRCL1_TSTCTL_DATSEL				(BIT0)
	#define		ECC_ECCCNT_D_V2XRCL1_TCTL_DS_LOWER			(0)
	#define		ECC_ECCCNT_D_V2XRCL1_TCTL_DS_UPPER			(1)
/* BUSDVCECCTSTDIN0 */
/* No bit definition required because it only has byte access */
/* BUSDVCECCTSTEIN */
#define		ECC_ECCCNT_D_V2XRCL1_BUSDVCECCTSTEIN_ECC		(BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)

/* Module: ECCCNT_D_V2XWCL2 */
/* BUSDVCECCCTL */
#define		ECC_ECCCNT_D_V2XWCL2_ECCCTL_SECDIS				(BIT1)
	#define		ECC_ECCCNT_D_V2XWCL2_CTL_SD_CORRECT			(0)
	#define		ECC_ECCCNT_D_V2XWCL2_CTL_SD_NOTCORRECT		(1)
#define		ECC_ECCCNT_D_V2XWCL2_ECCCTL_ECCDIS				(BIT0)
	#define		ECC_ECCCNT_D_V2XWCL2_CTL_ED_ENABLE			(0)
	#define		ECC_ECCCNT_D_V2XWCL2_CTL_ED_DISABLE			(1)
/* BUSDVCECCTSTCTL */
#define		ECC_ECCCNT_D_V2XWCL2_TSTCTL_ECCTST				(BIT1)
	#define		ECC_ECCCNT_D_V2XWCL2_TCTL_TST_NORMAL		(0)
	#define		ECC_ECCCNT_D_V2XWCL2_TCTL_TST_TEST			(1)
#define		ECC_ECCCNT_D_V2XWCL2_TSTCTL_DATSEL				(BIT0)
	#define		ECC_ECCCNT_D_V2XWCL2_TCTL_DS_LOWER			(0)
	#define		ECC_ECCCNT_D_V2XWCL2_TCTL_DS_UPPER			(1)
/* BUSDVCECCTSTDIN0 */
/* No bit definition required because it only has byte access */
/* BUSDVCECCTSTEIN */
#define		ECC_ECCCNT_D_V2XWCL2_BUSDVCECCTSTEIN_ECC		(BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)

/* Module: ECCCNT_D_V2XRCL2 */
/* BUSDVCECCCTL */
#define		ECC_ECCCNT_D_V2XRCL2_ECCCTL_SECDIS				(BIT1)
	#define		ECC_ECCCNT_D_V2XRCL2_CTL_SD_CORRECT			(0)
	#define		ECC_ECCCNT_D_V2XRCL2_CTL_SD_NOTCORRECT		(1)
#define		ECC_ECCCNT_D_V2XRCL2_ECCCTL_ECCDIS				(BIT0)
	#define		ECC_ECCCNT_D_V2XRCL2_CTL_ED_ENABLE			(0)
	#define		ECC_ECCCNT_D_V2XRCL2_CTL_ED_DISABLE			(1)
/* BUSDVCECCTSTCTL */
#define		ECC_ECCCNT_D_V2XRCL2_TSTCTL_ECCTST				(BIT1)
	#define		ECC_ECCCNT_D_V2XRCL2_TCTL_TST_NORMAL		(0)
	#define		ECC_ECCCNT_D_V2XRCL2_TCTL_TST_TEST			(1)
#define		ECC_ECCCNT_D_V2XRCL2_TSTCTL_DATSEL				(BIT0)
	#define		ECC_ECCCNT_D_V2XRCL2_TCTL_DS_LOWER			(0)
	#define		ECC_ECCCNT_D_V2XRCL2_TCTL_DS_UPPER			(1)
/* BUSDVCECCTSTDIN0 */
/* No bit definition required because it only has byte access */
/* BUSDVCECCTSTEIN */
#define		ECC_ECCCNT_D_V2XRCL2_BUSDVCECCTSTEIN_ECC		(BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)

/* Module: ECCCNT_D_PV2APBW */
/* BUSDECCCTL */
#define		ECC_ECCCNT_D_PV2APBW_ECCCTL_SECDIS				(BIT1)
	#define		ECC_ECCCNT_D_PV2APBW_CTL_SD_CORRECT			(0)
	#define		ECC_ECCCNT_D_PV2APBW_CTL_SD_NOTCORRECT		(1)
#define		ECC_ECCCNT_D_PV2APBW_ECCCTL_ECCDIS				(BIT0)
	#define		ECC_ECCCNT_D_PV2APBW_CTL_ED_ENABLE			(0)
	#define		ECC_ECCCNT_D_PV2APBW_CTL_ED_DISABLE			(1)

/* Module: ECCCNT_D_CRAM */
/* BUSDVCECCCTL */
#define		ECC_ECCCNT_D_CRAM_ECCCTL_SECDIS					(BIT1)
	#define		ECC_ECCCNT_D_CRAM_CTL_SD_CORRECT			(0)
	#define		ECC_ECCCNT_D_CRAM_CTL_SD_NOTCORRECT			(1)
#define		ECC_ECCCNT_D_CRAM_ECCCTL_ECCDIS					(BIT0)
	#define		ECC_ECCCNT_D_CRAM_CTL_ED_ENABLE				(0)
	#define		ECC_ECCCNT_D_CRAM_CTL_ED_DISABLE			(1)
/* BUSDVCECCTSTCTL */
#define		ECC_ECCCNT_D_CRAM_ECCTSTCTL_ECCTST				(BIT1)
	#define		ECC_ECCCNT_D_CRAM_TCTL_TST_NORMAL			(0)
	#define		ECC_ECCCNT_D_CRAM_TCTL_TST_TEST				(1)
#define		ECC_ECCCNT_D_CRAM_ECCTSTCTL_DATSEL				(BIT0)
	#define		ECC_ECCCNT_D_CRAM_TCTL_DS_LOWER				(0)
	#define		ECC_ECCCNT_D_CRAM_TCTL_DS_UPPER				(1)
/* BUSDVCECCTSTDIN0 */
/* No bit definition required because it only has byte access */
/* BUSDVCECCTSTEIN */
#define		ECC_ECCCNT_D_CRAM_BUSDVCECCTSTEIN_ECC			(BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)

/* Module: ECCCNT_D_EMU */
/* BUSDEMECCCTL */
#define		ECC_ECCCNT_D_EMU_ECCCTL_SECDIS					(BIT1)
	#define		ECC_ECCCNT_D_EMU_CTL_SD_CORRECT				(0)
	#define		ECC_ECCCNT_D_EMU_CTL_SD_NOTCORRECT			(1)
#define		ECC_ECCCNT_D_EMU_ECCCTL_ECCDIS					(BIT0)
	#define		ECC_ECCCNT_D_EMU_CTL_ED_ENABLE				(0)
	#define		ECC_ECCCNT_D_EMU_CTL_ED_DISABLE				(1)
/* BUSDEMECCTSTCTL */
#define		ECC_ECCCNT_D_EMU_ECCTSTCTL_ECCTST				(BIT1)
	#define		ECC_ECCCNT_D_EMU_TCTL_TST_NORMAL			(0)
	#define		ECC_ECCCNT_D_EMU_TCTL_TST_TEST				(1)
#define		ECC_ECCCNT_D_EMU_ECCTSTCTL_DATSEL				(BIT0)
	#define		ECC_ECCCNT_D_EMU_TCTL_DS_LOWER				(0)
	#define		ECC_ECCCNT_D_EMU_TCTL_DS_UPPER				(1)
/* BUSDEMECCTSTDIN0 */
/* No bit definition required because it only has byte access */
/* BUSDEMECCTSTEIN */
#define		ECC_ECCCNT_D_EMU_BUSDEMECCTSTEIN_ECC			(BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)

/* Module: ECCCNT_D_DMDE0 */
/* BUSDDEECCCTL */
#define		ECC_ECCCNT_D_DMDE0_ECCCTL_SECDIS				(BIT1)
	#define		ECC_ECCCNT_D_DMDE0_CTL_SD_CORRECT			(0)
	#define		ECC_ECCCNT_D_DMDE0_CTL_SD_NOTCORRECT		(1)
#define		ECC_ECCCNT_D_DMDE0_ECCCTL_ECCDIS				(BIT0)
	#define		ECC_ECCCNT_D_DMDE0_CTL_ED_ENABLE			(0)
	#define		ECC_ECCCNT_D_DMDE0_CTL_ED_DISABLE			(1)
/* BUSDDEECCTSTCTL */
#define		ECC_ECCCNT_D_DMDE0_ECCTSTCTL_ECCTST				(BIT1)
	#define		ECC_ECCCNT_D_DMDE0_TCTL_TST_NORMAL			(0)
	#define		ECC_ECCCNT_D_DMDE0_TCTL_TST_TEST			(1)
/* BUSDDEECCTSTDIN0 */
/* No bit definition required because it only has byte access */
/* BUSDDEECCTSTDIN1 */
/* No bit definition required because it only has byte access */
/* BUSDDEECCTSTEIN */
#define		ECC_ECCCNT_D_DMDE0_BUSDDEECCTSTEIN_ECC			(0x000000FFU)

/* Module: ECCCNT_D_DMDE1 */
/* BUSDDEECCCTL */
#define		ECC_ECCCNT_D_DMDE1_ECCCTL_SECDIS				(BIT1)
	#define		ECC_ECCCNT_D_DMDE1_CTL_SD_CORRECT			(0)
	#define		ECC_ECCCNT_D_DMDE1_CTL_SD_NOTCORRECT		(1)
#define		ECC_ECCCNT_D_DMDE1_ECCCTL_ECCDIS				(BIT0)
	#define		ECC_ECCCNT_D_DMDE1_CTL_ED_ENABLE			(0)
	#define		ECC_ECCCNT_D_DMDE1_CTL_ED_DISABLE			(1)
/* BUSDDEECCTSTCTL */
#define		ECC_ECCCNT_D_DMDE1_ECCTSTCTL_ECCTST				(BIT1)
	#define		ECC_ECCCNT_D_DMDE1_TCTL_TST_NORMAL			(0)
	#define		ECC_ECCCNT_D_DMDE1_TCTL_TST_TEST			(1)
/* BUSDDEECCTSTDIN0 */
/* No bit definition required because it only has byte access */
/* BUSDDEECCTSTDIN1 */
/* No bit definition required because it only has byte access */
/* BUSDDEECCTSTEIN */
#define		ECC_ECCCNT_D_DMDE1_BUSDDEECCTSTEIN_ECC			(0x000000FFU)

/* Module: ECCCNT_C_DMR0 */
/* BUSCECCCTL */
#define		ECC_ECCCNT_C_DMR0_ECCCTL_ECCDIS					(BIT0)
	#define		ECC_ECCCNT_C_DMR0_CTL_ED_ENABLE				(0)
	#define		ECC_ECCCNT_C_DMR0_CTL_ED_DISABLE			(1)
/* BUSCECCTSTCTL */
#define		ECC_ECCCNT_C_DMR0_ECCTSTCTL_ECCTST				(BIT1)
	#define		ECC_ECCCNT_C_DMR0_TCTL_TST_NORMAL			(0)
	#define		ECC_ECCCNT_C_DMR0_TCTL_TST_TEST				(1)
/* BUSCECCTSTDIN0 */
/* No bit definition required because it only has byte access */
/* BUSCECCTSTDIN1 */
/* No bit definition required because it only has byte access */
/* BUSCECCTSTEIN */
#define		ECC_ECCCNT_C_DMR0_BUSCECCTSTEIN_ECC				(0x000000FFU)

/* Module: ECCCNT_C_DMW0 */
/* BUSCECCCTL */
#define		ECC_ECCCNT_C_DMW0_ECCCTL_ECCDIS					(BIT0)
	#define		ECC_ECCCNT_C_DMW0_CTL_ED_ENABLE				(0)
	#define		ECC_ECCCNT_C_DMW0_CTL_ED_DISABLE			(1)
/* BUSCECCTSTCTL */
#define		ECC_ECCCNT_C_DMW0_ECCTSTCTL_ECCTST				(BIT1)
	#define		ECC_ECCCNT_C_DMW0_TCTL_TST_NORMAL			(0)
	#define		ECC_ECCCNT_C_DMW0_TCTL_TST_TEST				(1)
/* BUSCECCTSTDIN0 */
/* No bit definition required because it only has byte access */
/* BUSCECCTSTDIN1 */
/* No bit definition required because it only has byte access */
/* BUSCECCTSTEIN */
#define		ECC_ECCCNT_C_DMW0_BUSCECCTSTEIN_ECC				(0x000000FFU)

/* Module: ECCCNT_C_DMR1 */
/* BUSCECCCTL */
#define		ECC_ECCCNT_C_DMR1_ECCCTL_ECCDIS					(BIT0)
	#define		ECC_ECCCNT_C_DMR1_CTL_ED_ENABLE				(0)
	#define		ECC_ECCCNT_C_DMR1_CTL_ED_DISABLE			(1)
/* BUSCECCTSTCTL */
#define		ECC_ECCCNT_C_DMR1_ECCTSTCTL_ECCTST				(BIT1)
	#define		ECC_ECCCNT_C_DMR1_TCTL_TST_NORMAL			(0)
	#define		ECC_ECCCNT_C_DMR1_TCTL_TST_TEST				(1)
/* BUSCECCTSTDIN0 */
/* No bit definition required because it only has byte access */
/* BUSCECCTSTDIN1 */
/* No bit definition required because it only has byte access */
/* BUSCECCTSTEIN */
#define		ECC_ECCCNT_C_DMR1_BUSCECCTSTEIN_ECC				(0x000000FFU)

/* Module: ECCCNT_C_DMW1 */
/* BUSCECCCTL */
#define		ECC_ECCCNT_C_DMW1_ECCCTL_ECCDIS					(BIT0)
	#define		ECC_ECCCNT_C_DMW1_CTL_ED_ENABLE				(0)
	#define		ECC_ECCCNT_C_DMW1_CTL_ED_DISABLE			(1)
/* BUSCECCTSTCTL */
#define		ECC_ECCCNT_C_DMW1_ECCTSTCTL_ECCTST				(BIT1)
	#define		ECC_ECCCNT_C_DMW1_TCTL_TST_NORMAL			(0)
	#define		ECC_ECCCNT_C_DMW1_TCTL_TST_TEST				(1)
/* BUSCECCTSTDIN0 */
/* No bit definition required because it only has byte access */
/* BUSCECCTSTDIN1 */
/* No bit definition required because it only has byte access */
/* BUSCECCTSTEIN */
#define		ECC_ECCCNT_C_DMW1_BUSCECCTSTEIN_ECC				(0x000000FFU)

/* Module: ECCCNT_SD_PE0CL0 */
/* BUSDECCCTL */
#define		ECC_ECCCNT_SD_PE0CL0_ECCCTL_SECDIS				(BIT1)
	#define		ECC_ECCCNT_SD_PE0CL0_CTL_SD_CORRECT			(0)
	#define		ECC_ECCCNT_SD_PE0CL0_CTL_SD_NOTCORRECT		(1)
#define		ECC_ECCCNT_SD_PE0CL0_ECCCTL_ECCDIS				(BIT0)
	#define		ECC_ECCCNT_SD_PE0CL0_CTL_ED_ENABLE			(0)
	#define		ECC_ECCCNT_SD_PE0CL0_CTL_ED_DISABLE			(1)

/* Module: ECCCNT_SD_PE1CL0 */
/* BUSDECCCTL */
#define		ECC_ECCCNT_SD_PE1CL0_ECCCTL_SECDIS				(BIT1)
	#define		ECC_ECCCNT_SD_PE1CL0_CTL_SD_CORRECT			(0)
	#define		ECC_ECCCNT_SD_PE1CL0_CTL_SD_NOTCORRECT		(1)
#define		ECC_ECCCNT_SD_PE1CL0_ECCCTL_ECCDIS				(BIT0)
	#define		ECC_ECCCNT_SD_PE1CL0_CTL_ED_ENABLE			(0)
	#define		ECC_ECCCNT_SD_PE1CL0_CTL_ED_DISABLE			(1)

/* Module: ECCCNT_SD_PE2CL1 */
/* BUSDECCCTL */
#define		ECC_ECCCNT_SD_PE2CL1_ECCCTL_SECDIS				(BIT1)
	#define		ECC_ECCCNT_SD_PE2CL1_CTL_SD_CORRECT			(0)
	#define		ECC_ECCCNT_SD_PE2CL1_CTL_SD_NOTCORRECT		(1)
#define		ECC_ECCCNT_SD_PE2CL1_ECCCTL_ECCDIS				(BIT0)
	#define		ECC_ECCCNT_SD_PE2CL1_CTL_ED_ENABLE			(0)
	#define		ECC_ECCCNT_SD_PE2CL1_CTL_ED_DISABLE			(1)

/* Module: ECCCNT_SD_PE3CL1 */
/* BUSDECCCTL */
#define		ECC_ECCCNT_SD_PE3CL1_ECCCTL_SECDIS				(BIT1)
	#define		ECC_ECCCNT_SD_PE3CL1_CTL_SD_CORRECT			(0)
	#define		ECC_ECCCNT_SD_PE3CL1_CTL_SD_NOTCORRECT		(1)
#define		ECC_ECCCNT_SD_PE3CL1_ECCCTL_ECCDIS				(BIT0)
	#define		ECC_ECCCNT_SD_PE3CL1_CTL_ED_ENABLE			(0)
	#define		ECC_ECCCNT_SD_PE3CL1_CTL_ED_DISABLE			(1)

/* Module: ECCCNT_SD_PE4CL2 */
/* BUSDECCCTL */
#define		ECC_ECCCNT_SD_PE4CL2_ECCCTL_SECDIS				(BIT1)
	#define		ECC_ECCCNT_SD_PE4CL2_CTL_SD_CORRECT			(0)
	#define		ECC_ECCCNT_SD_PE4CL2_CTL_SD_NOTCORRECT		(1)
#define		ECC_ECCCNT_SD_PE4CL2_ECCCTL_ECCDIS				(BIT0)
	#define		ECC_ECCCNT_SD_PE4CL2_CTL_ED_ENABLE			(0)
	#define		ECC_ECCCNT_SD_PE4CL2_CTL_ED_DISABLE			(1)

/* Module: ECCCNT_SD_PE5CL2 */
/* BUSDECCCTL */
#define		ECC_ECCCNT_SD_PE5CL2_ECCCTL_SECDIS				(BIT1)
	#define		ECC_ECCCNT_SD_PE5CL2_CTL_SD_CORRECT			(0)
	#define		ECC_ECCCNT_SD_PE5CL2_CTL_SD_NOTCORRECT		(1)
#define		ECC_ECCCNT_SD_PE5CL2_ECCCTL_ECCDIS				(BIT0)
	#define		ECC_ECCCNT_SD_PE5CL2_CTL_ED_ENABLE			(0)
	#define		ECC_ECCCNT_SD_PE5CL2_CTL_ED_DISABLE			(1)

/* Module: ECCCNT_MD_PE0CL0 */
/* BUSDECCCTL */
#define		ECC_ECCCNT_MD_PE0CL0_ECCCTL_SECDIS				(BIT1)
	#define		ECC_ECCCNT_MD_PE0CL0_CTL_SD_CORRECT			(0)
	#define		ECC_ECCCNT_MD_PE0CL0_CTL_SD_NOTCORRECT		(1)
#define		ECC_ECCCNT_MD_PE0CL0_ECCCTL_ECCDIS				(BIT0)
	#define		ECC_ECCCNT_MD_PE0CL0_CTL_ED_ENABLE			(0)
	#define		ECC_ECCCNT_MD_PE0CL0_CTL_ED_DISABLE			(1)

/* Module: ECCCNT_MD_PE1CL0 */
/* BUSDECCCTL */
#define		ECC_ECCCNT_MD_PE1CL0_ECCCTL_SECDIS				(BIT1)
	#define		ECC_ECCCNT_MD_PE1CL0_CTL_SD_CORRECT			(0)
	#define		ECC_ECCCNT_MD_PE1CL0_CTL_SD_NOTCORRECT		(1)
#define		ECC_ECCCNT_MD_PE1CL0_ECCCTL_ECCDIS				(BIT0)
	#define		ECC_ECCCNT_MD_PE1CL0_CTL_ED_ENABLE			(0)
	#define		ECC_ECCCNT_MD_PE1CL0_CTL_ED_DISABLE			(1)

/* Module: ECCCNT_MD_PE2CL1 */
/* BUSDECCCTL */
#define		ECC_ECCCNT_MD_PE2CL1_ECCCTL_SECDIS				(BIT1)
	#define		ECC_ECCCNT_MD_PE2CL1_CTL_SD_CORRECT			(0)
	#define		ECC_ECCCNT_MD_PE2CL1_CTL_SD_NOTCORRECT		(1)
#define		ECC_ECCCNT_MD_PE2CL1_ECCCTL_ECCDIS				(BIT0)
	#define		ECC_ECCCNT_MD_PE2CL1_CTL_ED_ENABLE			(0)
	#define		ECC_ECCCNT_MD_PE2CL1_CTL_ED_DISABLE			(1)

/* Module: ECCCNT_MD_PE3CL1 */
/* BUSDECCCTL */
#define		ECC_ECCCNT_MD_PE3CL1_ECCCTL_SECDIS				(BIT1)
	#define		ECC_ECCCNT_MD_PE3CL1_CTL_SD_CORRECT			(0)
	#define		ECC_ECCCNT_MD_PE3CL1_CTL_SD_NOTCORRECT		(1)
#define		ECC_ECCCNT_MD_PE3CL1_ECCCTL_ECCDIS				(BIT0)
	#define		ECC_ECCCNT_MD_PE3CL1_CTL_ED_ENABLE			(0)
	#define		ECC_ECCCNT_MD_PE3CL1_CTL_ED_DISABLE			(1)

/* Module: ECCCNT_MD_PE4CL2 */
/* BUSDECCCTL */
#define		ECC_ECCCNT_MD_PE4CL2_ECCCTL_SECDIS				(BIT1)
	#define		ECC_ECCCNT_MD_PE4CL2_CTL_SD_CORRECT			(0)
	#define		ECC_ECCCNT_MD_PE4CL2_CTL_SD_NOTCORRECT		(1)
#define		ECC_ECCCNT_MD_PE4CL2_ECCCTL_ECCDIS				(BIT0)
	#define		ECC_ECCCNT_MD_PE4CL2_CTL_ED_ENABLE			(0)
	#define		ECC_ECCCNT_MD_PE4CL2_CTL_ED_DISABLE			(1)

/* Module: ECCCNT_MD_PE5CL2 */
/* BUSDECCCTL */
#define		ECC_ECCCNT_MD_PE5CL2_ECCCTL_SECDIS				(BIT1)
	#define		ECC_ECCCNT_MD_PE5CL2_CTL_SD_CORRECT			(0)
	#define		ECC_ECCCNT_MD_PE5CL2_CTL_SD_NOTCORRECT		(1)
#define		ECC_ECCCNT_MD_PE5CL2_ECCCTL_ECCDIS				(BIT0)
	#define		ECC_ECCCNT_MD_PE5CL2_CTL_ED_ENABLE			(0)
	#define		ECC_ECCCNT_MD_PE5CL2_CTL_ED_DISABLE			(1)

/* Module: ECCCNT_D_BARR */
/* BUSDECCCTL */
#define		ECC_ECCCNT_D_BARR_ECCCTL_SECDIS					(BIT1)
	#define		ECC_ECCCNT_D_BARR_CTL_SD_CORRECT			(0)
	#define		ECC_ECCCNT_D_BARR_CTL_SD_NOTCORRECT			(1)
#define		ECC_ECCCNT_D_BARR_ECCCTL_ECCDIS					(BIT0)
	#define		ECC_ECCCNT_D_BARR_CTL_ED_ENABLE				(0)
	#define		ECC_ECCCNT_D_BARR_CTL_ED_DISABLE			(1)

/* Module: ECCCNT_D_IPIR */
/* BUSDECCCTL */
#define		ECC_ECCCNT_D_IPIR_ECCCTL_SECDIS					(BIT1)
	#define		ECC_ECCCNT_D_IPIR_CTL_SD_CORRECT			(0)
	#define		ECC_ECCCNT_D_IPIR_CTL_SD_NOTCORRECT			(1)
#define		ECC_ECCCNT_D_IPIR_ECCCTL_ECCDIS					(BIT0)
	#define		ECC_ECCCNT_D_IPIR_CTL_ED_ENABLE				(0)
	#define		ECC_ECCCNT_D_IPIR_CTL_ED_DISABLE			(1)

/* Module: ECCCNT_D_TPTM */
/* BUSDECCCTL */
#define		ECC_ECCCNT_D_TPTM_ECCCTL_SECDIS					(BIT1)
	#define		ECC_ECCCNT_D_TPTM_CTL_SD_CORRECT			(0)
	#define		ECC_ECCCNT_D_TPTM_CTL_SD_NOTCORRECT			(1)
#define		ECC_ECCCNT_D_TPTM_ECCCTL_ECCDIS					(BIT0)
	#define		ECC_ECCCNT_D_TPTM_CTL_ED_ENABLE				(0)
	#define		ECC_ECCCNT_D_TPTM_CTL_ED_DISABLE			(1)

/* Module: ECCCNT_D_DTS */
/* BUSDECCCTL */
#define		ECC_ECCCNT_D_DTS_ECCCTL_SECDIS					(BIT1)
	#define		ECC_ECCCNT_D_DTS_CTL_SD_CORRECT				(0)
	#define		ECC_ECCCNT_D_DTS_CTL_SD_NOTCORRECT			(1)
#define		ECC_ECCCNT_D_DTS_ECCCTL_ECCDIS					(BIT0)
	#define		ECC_ECCCNT_D_DTS_CTL_ED_ENABLE				(0)
	#define		ECC_ECCCNT_D_DTS_CTL_ED_DISABLE				(1)

/* Module: ECCCNT_D_DMA0 */
/* BUSDECCCTL */
#define		ECC_ECCCNT_D_DMA0_ECCCTL_SECDIS					(BIT1)
	#define		ECC_ECCCNT_D_DMA0_CTL_SD_CORRECT			(0)
	#define		ECC_ECCCNT_D_DMA0_CTL_SD_NOTCORRECT			(1)
#define		ECC_ECCCNT_D_DMA0_ECCCTL_ECCDIS					(BIT0)
	#define		ECC_ECCCNT_D_DMA0_CTL_ED_ENABLE				(0)
	#define		ECC_ECCCNT_D_DMA0_CTL_ED_DISABLE			(1)

/* Module: ECCCNT_D_DMA1 */
/* BUSDECCCTL */
#define		ECC_ECCCNT_D_DMA1_ECCCTL_SECDIS					(BIT1)
	#define		ECC_ECCCNT_D_DMA1_CTL_SD_CORRECT			(0)
	#define		ECC_ECCCNT_D_DMA1_CTL_SD_NOTCORRECT			(1)
#define		ECC_ECCCNT_D_DMA1_ECCCTL_ECCDIS					(BIT0)
	#define		ECC_ECCCNT_D_DMA1_CTL_ED_ENABLE				(0)
	#define		ECC_ECCCNT_D_DMA1_CTL_ED_DISABLE			(1)

/* Module: ECCCNT_D_V2AnW */
/* BUSDVCECCCTL */
#define		ECC_ECCCNT_D_V2AnW_ECCCTL_SECDIS				(BIT1)
	#define		ECC_ECCCNT_D_V2AnW_CTL_SD_CORRECT			(0)
	#define		ECC_ECCCNT_D_V2AnW_CTL_SD_NOTCORRECT		(1)
#define		ECC_ECCCNT_D_V2AnW_ECCCTL_ECCDIS				(BIT0)
	#define		ECC_ECCCNT_D_V2AnW_CTL_ED_ENABLE			(0)
	#define		ECC_ECCCNT_D_V2AnW_CTL_ED_DISABLE			(1)

/* Module: DFP_ECCCNT_BUSD_ROM */
/* BUSDECCCTL */
#define		ECC_DFP_ECCCNT_BUSD_ROM_CTL_SECDIS				(BIT1)
	#define		ECC_DFP_ECCCNT_BUSD_ROM_CTL_S_CORRECT		(0)
	#define		ECC_DFP_ECCCNT_BUSD_ROM_CTL_S_NOTCORRECT	(1)
#define		ECC_DFP_ECCCNT_BUSD_ROM_CTL_ECCDIS				(BIT0)
	#define		ECC_DFP_ECCCNT_BUSD_ROM_CTL_E_ENABLE		(0)
	#define		ECC_DFP_ECCCNT_BUSD_ROM_CTL_E_DISABLE		(1)

/* Module: DFP_ECCCNT_BUSD_SYS */
/* BUSDECCCTL */
#define		ECC_DFP_ECCCNT_BUSD_SYS_CTL_SECDIS				(BIT1)
	#define		ECC_DFP_ECCCNT_BUSD_SYS_CTL_S_CORRECT		(0)
	#define		ECC_DFP_ECCCNT_BUSD_SYS_CTL_S_NOTCORRECT	(1)
#define		ECC_DFP_ECCCNT_BUSD_SYS_CTL_ECCDIS				(BIT0)
	#define		ECC_DFP_ECCCNT_BUSD_SYS_CTL_E_ENABLE		(0)
	#define		ECC_DFP_ECCCNT_BUSD_SYS_CTL_E_DISABLE		(1)

/* Module: DFP_ECCCNT_BUSD_FNT */
/* BUSDECCCTL */
#define		ECC_DFP_ECCCNT_BUSD_FNT_CTL_SECDIS				(BIT1)
	#define		ECC_DFP_ECCCNT_BUSD_FNT_CTL_S_CORRECT		(0)
	#define		ECC_DFP_ECCCNT_BUSD_FNT_CTL_S_NOTCORRECT	(1)
#define		ECC_DFP_ECCCNT_BUSD_FNT_CTL_ECCDIS				(BIT0)
	#define		ECC_DFP_ECCCNT_BUSD_FNT_CTL_E_ENABLE		(0)
	#define		ECC_DFP_ECCCNT_BUSD_FNT_CTL_E_DISABLE		(1)

/* Module: BECCCAP_LRAM */
/* LR_BUSERRINT */
#define		ECC_BECCCAP_LRAM_BUSERRINT_ADEDIE				(BIT3)
	#define		ECC_BECCCAP_LRAM_ERRINT_ADE_DISABLE			(0)
	#define		ECC_BECCCAP_LRAM_ERRINT_ADE_ENABLE			(1)
#define		ECC_BECCCAP_LRAM_BUSERRINT_ASEDIE				(BIT2)
	#define		ECC_BECCCAP_LRAM_ERRINT_ASE_DISABLE			(0)
	#define		ECC_BECCCAP_LRAM_ERRINT_ASE_ENABLE			(1)
#define		ECC_BECCCAP_LRAM_BUSERRINT_DDEDIE				(BIT1)
	#define		ECC_BECCCAP_LRAM_ERRINT_DDE_DISABLE			(0)
	#define		ECC_BECCCAP_LRAM_ERRINT_DDE_ENABLE			(1)
#define		ECC_BECCCAP_LRAM_BUSERRINT_DSEDIE				(BIT0)
	#define		ECC_BECCCAP_LRAM_ERRINT_DSE_DISABLE			(0)
	#define		ECC_BECCCAP_LRAM_ERRINT_DSE_ENABLE			(1)
/* LR_BUSASSTCLR */
#define		ECC_BECCCAP_LRAM_BUSASSTCLR_18					(BIT18)
#define		ECC_BECCCAP_LRAM_BUSASSTCLR_17					(BIT17)
#define		ECC_BECCCAP_LRAM_BUSASSTCLR_16					(BIT16)
#define		ECC_BECCCAP_LRAM_BUSASSTCLR_05					(BIT5)
#define		ECC_BECCCAP_LRAM_BUSASSTCLR_04					(BIT4)
#define		ECC_BECCCAP_LRAM_BUSASSTCLR_03					(BIT3)
#define		ECC_BECCCAP_LRAM_BUSASSTCLR_02					(BIT2)
#define		ECC_BECCCAP_LRAM_BUSASSTCLR_01					(BIT1)
#define		ECC_BECCCAP_LRAM_BUSASSTCLR_00					(BIT0)
	#define		ECC_BECCCAP_LRAM_BUSASSTCLR_CLEAR			(1)
/* LR_BUSADSTCLR */
#define		ECC_BECCCAP_LRAM_BUSADSTCLR_18					(BIT18)
#define		ECC_BECCCAP_LRAM_BUSADSTCLR_17					(BIT17)
#define		ECC_BECCCAP_LRAM_BUSADSTCLR_16					(BIT16)
#define		ECC_BECCCAP_LRAM_BUSADSTCLR_05					(BIT5)
#define		ECC_BECCCAP_LRAM_BUSADSTCLR_04					(BIT4)
#define		ECC_BECCCAP_LRAM_BUSADSTCLR_03					(BIT3)
#define		ECC_BECCCAP_LRAM_BUSADSTCLR_02					(BIT2)
#define		ECC_BECCCAP_LRAM_BUSADSTCLR_01					(BIT1)
#define		ECC_BECCCAP_LRAM_BUSADSTCLR_00					(BIT0)
	#define		ECC_BECCCAP_LRAM_BUSADSTCLR_CLEAR			(1)
/* LR_BUSDSSTCLR */
#define		ECC_BECCCAP_LRAM_BUSDSSTCLR_05					(BIT5)
#define		ECC_BECCCAP_LRAM_BUSDSSTCLR_04					(BIT4)
#define		ECC_BECCCAP_LRAM_BUSDSSTCLR_03					(BIT3)
#define		ECC_BECCCAP_LRAM_BUSDSSTCLR_02					(BIT2)
#define		ECC_BECCCAP_LRAM_BUSDSSTCLR_01					(BIT1)
#define		ECC_BECCCAP_LRAM_BUSDSSTCLR_00					(BIT0)
	#define		ECC_BECCCAP_LRAM_BUSDSSTCLR_CLEAR			(1)
/* LR_BUSDDSTCLR */
#define		ECC_BECCCAP_LRAM_BUSDDSTCLR_05					(BIT5)
#define		ECC_BECCCAP_LRAM_BUSDDSTCLR_04					(BIT4)
#define		ECC_BECCCAP_LRAM_BUSDDSTCLR_03					(BIT3)
#define		ECC_BECCCAP_LRAM_BUSDDSTCLR_02					(BIT2)
#define		ECC_BECCCAP_LRAM_BUSDDSTCLR_01					(BIT1)
#define		ECC_BECCCAP_LRAM_BUSDDSTCLR_00					(BIT0)
	#define		ECC_BECCCAP_LRAM_BUSDDSTCLR_CLEAR			(1)
/* LR_BUSASERSTR */
#define		ECC_BECCCAP_LRAM_BUSASERSTR_18					(BIT18)
#define		ECC_BECCCAP_LRAM_BUSASERSTR_17					(BIT17)
#define		ECC_BECCCAP_LRAM_BUSASERSTR_16					(BIT16)
#define		ECC_BECCCAP_LRAM_BUSASERSTR_05					(BIT5)
#define		ECC_BECCCAP_LRAM_BUSASERSTR_04					(BIT4)
#define		ECC_BECCCAP_LRAM_BUSASERSTR_03					(BIT3)
#define		ECC_BECCCAP_LRAM_BUSASERSTR_02					(BIT2)
#define		ECC_BECCCAP_LRAM_BUSASERSTR_01					(BIT1)
#define		ECC_BECCCAP_LRAM_BUSASERSTR_00					(BIT0)
/* LR_BUSADERSTR */
#define		ECC_BECCCAP_LRAM_BUSADERSTR_18					(BIT18)
#define		ECC_BECCCAP_LRAM_BUSADERSTR_17					(BIT17)
#define		ECC_BECCCAP_LRAM_BUSADERSTR_16					(BIT16)
#define		ECC_BECCCAP_LRAM_BUSADERSTR_05					(BIT5)
#define		ECC_BECCCAP_LRAM_BUSADERSTR_04					(BIT4)
#define		ECC_BECCCAP_LRAM_BUSADERSTR_03					(BIT3)
#define		ECC_BECCCAP_LRAM_BUSADERSTR_02					(BIT2)
#define		ECC_BECCCAP_LRAM_BUSADERSTR_01					(BIT1)
#define		ECC_BECCCAP_LRAM_BUSADERSTR_00					(BIT0)
/* LR_BUSDSERSTR */
#define		ECC_BECCCAP_LRAM_BUSDSERSTR_05					(BIT5)
#define		ECC_BECCCAP_LRAM_BUSDSERSTR_04					(BIT4)
#define		ECC_BECCCAP_LRAM_BUSDSERSTR_03					(BIT3)
#define		ECC_BECCCAP_LRAM_BUSDSERSTR_02					(BIT2)
#define		ECC_BECCCAP_LRAM_BUSDSERSTR_01					(BIT1)
#define		ECC_BECCCAP_LRAM_BUSDSERSTR_00					(BIT0)
/* LR_BUSDDERSTR */
#define		ECC_BECCCAP_LRAM_BUSDDERSTR_05					(BIT5)
#define		ECC_BECCCAP_LRAM_BUSDDERSTR_04					(BIT4)
#define		ECC_BECCCAP_LRAM_BUSDDERSTR_03					(BIT3)
#define		ECC_BECCCAP_LRAM_BUSDDERSTR_02					(BIT2)
#define		ECC_BECCCAP_LRAM_BUSDDERSTR_01					(BIT1)
#define		ECC_BECCCAP_LRAM_BUSDDERSTR_00					(BIT0)

/* Module: BECCCAP_CRAM */
/* CR_BUSERRINT */
#define		ECC_BECCCAP_CRAM_BUSERRINT_ADEDIE				(BIT3)
	#define		ECC_BECCCAP_CRAM_ERRINT_ADE_DISABLE			(0)
	#define		ECC_BECCCAP_CRAM_ERRINT_ADE_ENABLE			(1)
#define		ECC_BECCCAP_CRAM_BUSERRINT_ASEDIE				(BIT2)
	#define		ECC_BECCCAP_CRAM_ERRINT_ASE_DISABLE			(0)
	#define		ECC_BECCCAP_CRAM_ERRINT_ASE_ENABLE			(1)
#define		ECC_BECCCAP_CRAM_BUSERRINT_DDEDIE				(BIT1)
	#define		ECC_BECCCAP_CRAM_ERRINT_DDE_DISABLE			(0)
	#define		ECC_BECCCAP_CRAM_ERRINT_DDE_ENABLE			(1)
#define		ECC_BECCCAP_CRAM_BUSERRINT_DSEDIE				(BIT0)
	#define		ECC_BECCCAP_CRAM_ERRINT_DSE_DISABLE			(0)
	#define		ECC_BECCCAP_CRAM_ERRINT_DSE_ENABLE			(1)
/* CR_BUSASSTCLR */
#define		ECC_BECCCAP_CRAM_BUSASSTCLR_28					(BIT28)
#define		ECC_BECCCAP_CRAM_BUSASSTCLR_26					(BIT26)
#define		ECC_BECCCAP_CRAM_BUSASSTCLR_25					(BIT25)
#define		ECC_BECCCAP_CRAM_BUSASSTCLR_24					(BIT24)
#define		ECC_BECCCAP_CRAM_BUSASSTCLR_18					(BIT18)
#define		ECC_BECCCAP_CRAM_BUSASSTCLR_10					(BIT10)
#define		ECC_BECCCAP_CRAM_BUSASSTCLR_09					(BIT9)
#define		ECC_BECCCAP_CRAM_BUSASSTCLR_08					(BIT8)
#define		ECC_BECCCAP_CRAM_BUSASSTCLR_06					(BIT6)
#define		ECC_BECCCAP_CRAM_BUSASSTCLR_05					(BIT5)
#define		ECC_BECCCAP_CRAM_BUSASSTCLR_04					(BIT4)
#define		ECC_BECCCAP_CRAM_BUSASSTCLR_02					(BIT2)
#define		ECC_BECCCAP_CRAM_BUSASSTCLR_01					(BIT1)
#define		ECC_BECCCAP_CRAM_BUSASSTCLR_00					(BIT0)
	#define		ECC_BECCCAP_CRAM_BUSASSTCLR_CLEAR			(1)
/* CR_BUSADSTCLR */
#define		ECC_BECCCAP_CRAM_BUSADSTCLR_28					(BIT28)
#define		ECC_BECCCAP_CRAM_BUSADSTCLR_26					(BIT26)
#define		ECC_BECCCAP_CRAM_BUSADSTCLR_25					(BIT25)
#define		ECC_BECCCAP_CRAM_BUSADSTCLR_24					(BIT24)
#define		ECC_BECCCAP_CRAM_BUSADSTCLR_18					(BIT18)
#define		ECC_BECCCAP_CRAM_BUSADSTCLR_10					(BIT10)
#define		ECC_BECCCAP_CRAM_BUSADSTCLR_09					(BIT9)
#define		ECC_BECCCAP_CRAM_BUSADSTCLR_08					(BIT8)
#define		ECC_BECCCAP_CRAM_BUSADSTCLR_06					(BIT6)
#define		ECC_BECCCAP_CRAM_BUSADSTCLR_05					(BIT5)
#define		ECC_BECCCAP_CRAM_BUSADSTCLR_04					(BIT4)
#define		ECC_BECCCAP_CRAM_BUSADSTCLR_02					(BIT2)
#define		ECC_BECCCAP_CRAM_BUSADSTCLR_01					(BIT1)
#define		ECC_BECCCAP_CRAM_BUSADSTCLR_00					(BIT0)
	#define		ECC_BECCCAP_CRAM_BUSADSTCLR_CLEAR			(1)
/* CR_BUSDSSTCLR */
#define		ECC_BECCCAP_CRAM_BUSDSSTCLR_18					(BIT18)
#define		ECC_BECCCAP_CRAM_BUSDSSTCLR_10					(BIT10)
#define		ECC_BECCCAP_CRAM_BUSDSSTCLR_09					(BIT9)
#define		ECC_BECCCAP_CRAM_BUSDSSTCLR_08					(BIT8)
#define		ECC_BECCCAP_CRAM_BUSDSSTCLR_06					(BIT6)
#define		ECC_BECCCAP_CRAM_BUSDSSTCLR_05					(BIT5)
#define		ECC_BECCCAP_CRAM_BUSDSSTCLR_04					(BIT4)
#define		ECC_BECCCAP_CRAM_BUSDSSTCLR_02					(BIT2)
#define		ECC_BECCCAP_CRAM_BUSDSSTCLR_01					(BIT1)
#define		ECC_BECCCAP_CRAM_BUSDSSTCLR_00					(BIT0)
	#define		ECC_BECCCAP_CRAM_BUSDSSTCLR_CLEAR			(1)
/* CR_BUSDDSTCLR */
#define		ECC_BECCCAP_CRAM_BUSDDSTCLR_18					(BIT18)
#define		ECC_BECCCAP_CRAM_BUSDDSTCLR_10					(BIT10)
#define		ECC_BECCCAP_CRAM_BUSDDSTCLR_09					(BIT9)
#define		ECC_BECCCAP_CRAM_BUSDDSTCLR_08					(BIT8)
#define		ECC_BECCCAP_CRAM_BUSDDSTCLR_06					(BIT6)
#define		ECC_BECCCAP_CRAM_BUSDDSTCLR_05					(BIT5)
#define		ECC_BECCCAP_CRAM_BUSDDSTCLR_04					(BIT4)
#define		ECC_BECCCAP_CRAM_BUSDDSTCLR_02					(BIT2)
#define		ECC_BECCCAP_CRAM_BUSDDSTCLR_01					(BIT1)
#define		ECC_BECCCAP_CRAM_BUSDDSTCLR_00					(BIT0)
	#define		ECC_BECCCAP_CRAM_BUSDDSTCLR_CLEAR			(1)
/* CR_BUSASERSTR */
#define		ECC_BECCCAP_CRAM_BUSASERSTR_28					(BIT28)
#define		ECC_BECCCAP_CRAM_BUSASERSTR_26					(BIT26)
#define		ECC_BECCCAP_CRAM_BUSASERSTR_25					(BIT25)
#define		ECC_BECCCAP_CRAM_BUSASERSTR_24					(BIT24)
#define		ECC_BECCCAP_CRAM_BUSASERSTR_18					(BIT18)
#define		ECC_BECCCAP_CRAM_BUSASERSTR_10					(BIT10)
#define		ECC_BECCCAP_CRAM_BUSASERSTR_09					(BIT9)
#define		ECC_BECCCAP_CRAM_BUSASERSTR_08					(BIT8)
#define		ECC_BECCCAP_CRAM_BUSASERSTR_06					(BIT6)
#define		ECC_BECCCAP_CRAM_BUSASERSTR_05					(BIT5)
#define		ECC_BECCCAP_CRAM_BUSASERSTR_04					(BIT4)
#define		ECC_BECCCAP_CRAM_BUSASERSTR_02					(BIT2)
#define		ECC_BECCCAP_CRAM_BUSASERSTR_01					(BIT1)
#define		ECC_BECCCAP_CRAM_BUSASERSTR_00					(BIT0)
/* CR_BUSADERSTR */
#define		ECC_BECCCAP_CRAM_BUSADERSTR_28					(BIT28)
#define		ECC_BECCCAP_CRAM_BUSADERSTR_26					(BIT26)
#define		ECC_BECCCAP_CRAM_BUSADERSTR_25					(BIT25)
#define		ECC_BECCCAP_CRAM_BUSADERSTR_24					(BIT24)
#define		ECC_BECCCAP_CRAM_BUSADERSTR_18					(BIT18)
#define		ECC_BECCCAP_CRAM_BUSADERSTR_10					(BIT10)
#define		ECC_BECCCAP_CRAM_BUSADERSTR_09					(BIT9)
#define		ECC_BECCCAP_CRAM_BUSADERSTR_08					(BIT8)
#define		ECC_BECCCAP_CRAM_BUSADERSTR_06					(BIT6)
#define		ECC_BECCCAP_CRAM_BUSADERSTR_05					(BIT5)
#define		ECC_BECCCAP_CRAM_BUSADERSTR_04					(BIT4)
#define		ECC_BECCCAP_CRAM_BUSADERSTR_02					(BIT2)
#define		ECC_BECCCAP_CRAM_BUSADERSTR_01					(BIT1)
#define		ECC_BECCCAP_CRAM_BUSADERSTR_00					(BIT0)
/* CR_BUSDSERSTR */
#define		ECC_BECCCAP_CRAM_BUSDSERSTR_18					(BIT18)
#define		ECC_BECCCAP_CRAM_BUSDSERSTR_10					(BIT10)
#define		ECC_BECCCAP_CRAM_BUSDSERSTR_09					(BIT9)
#define		ECC_BECCCAP_CRAM_BUSDSERSTR_08					(BIT8)
#define		ECC_BECCCAP_CRAM_BUSDSERSTR_06					(BIT6)
#define		ECC_BECCCAP_CRAM_BUSDSERSTR_05					(BIT5)
#define		ECC_BECCCAP_CRAM_BUSDSERSTR_04					(BIT4)
#define		ECC_BECCCAP_CRAM_BUSDSERSTR_02					(BIT2)
#define		ECC_BECCCAP_CRAM_BUSDSERSTR_01					(BIT1)
#define		ECC_BECCCAP_CRAM_BUSDSERSTR_00					(BIT0)
/* CR_BUSDDERSTR */
#define		ECC_BECCCAP_CRAM_BUSDDERSTR_18					(BIT18)
#define		ECC_BECCCAP_CRAM_BUSDDERSTR_10					(BIT10)
#define		ECC_BECCCAP_CRAM_BUSDDERSTR_09					(BIT9)
#define		ECC_BECCCAP_CRAM_BUSDDERSTR_08					(BIT8)
#define		ECC_BECCCAP_CRAM_BUSDDERSTR_06					(BIT6)
#define		ECC_BECCCAP_CRAM_BUSDDERSTR_05					(BIT5)
#define		ECC_BECCCAP_CRAM_BUSDDERSTR_04					(BIT4)
#define		ECC_BECCCAP_CRAM_BUSDDERSTR_02					(BIT2)
#define		ECC_BECCCAP_CRAM_BUSDDERSTR_01					(BIT1)
#define		ECC_BECCCAP_CRAM_BUSDDERSTR_00					(BIT0)

/* Module: BECCCAP_CFL */
/* CF_BUSERRINT */
#define		ECC_BECCCAP_CFL_BUSERRINT_ADEDIE				(BIT3)
	#define		ECC_BECCCAP_CFL_ERRINT_ADE_DISABLE			(0)
	#define		ECC_BECCCAP_CFL_ERRINT_ADE_ENABLE			(1)
#define		ECC_BECCCAP_CFL_BUSERRINT_ASEDIE				(BIT2)
	#define		ECC_BECCCAP_CFL_ERRINT_ASE_DISABLE			(0)
	#define		ECC_BECCCAP_CFL_ERRINT_ASE_ENABLE			(1)
/* CF_BUSASSTCLR */
#define		ECC_BECCCAP_CFL_BUSASSTCLR_25					(BIT25)
#define		ECC_BECCCAP_CFL_BUSASSTCLR_24					(BIT24)
#define		ECC_BECCCAP_CFL_BUSASSTCLR_09					(BIT9)
#define		ECC_BECCCAP_CFL_BUSASSTCLR_08					(BIT8)
#define		ECC_BECCCAP_CFL_BUSASSTCLR_05					(BIT5)
#define		ECC_BECCCAP_CFL_BUSASSTCLR_04					(BIT4)
#define		ECC_BECCCAP_CFL_BUSASSTCLR_03					(BIT3)
#define		ECC_BECCCAP_CFL_BUSASSTCLR_02					(BIT2)
#define		ECC_BECCCAP_CFL_BUSASSTCLR_01					(BIT1)
#define		ECC_BECCCAP_CFL_BUSASSTCLR_00					(BIT0)
	#define		ECC_BECCCAP_CFL_BUSASSTCLR_CLEAR			(1)
/* CF_BUSADSTCLR */
#define		ECC_BECCCAP_CFL_BUSADSTCLR_25					(BIT25)
#define		ECC_BECCCAP_CFL_BUSADSTCLR_24					(BIT24)
#define		ECC_BECCCAP_CFL_BUSADSTCLR_09					(BIT9)
#define		ECC_BECCCAP_CFL_BUSADSTCLR_08					(BIT8)
#define		ECC_BECCCAP_CFL_BUSADSTCLR_05					(BIT5)
#define		ECC_BECCCAP_CFL_BUSADSTCLR_04					(BIT4)
#define		ECC_BECCCAP_CFL_BUSADSTCLR_03					(BIT3)
#define		ECC_BECCCAP_CFL_BUSADSTCLR_02					(BIT2)
#define		ECC_BECCCAP_CFL_BUSADSTCLR_01					(BIT1)
#define		ECC_BECCCAP_CFL_BUSADSTCLR_00					(BIT0)
	#define		ECC_BECCCAP_CFL_BUSADSTCLR_CLEAR			(1)
/* CF_BUSASERSTR */
#define		ECC_BECCCAP_CFL_BUSASERSTR_25					(BIT25)
#define		ECC_BECCCAP_CFL_BUSASERSTR_24					(BIT24)
#define		ECC_BECCCAP_CFL_BUSASERSTR_09					(BIT9)
#define		ECC_BECCCAP_CFL_BUSASERSTR_08					(BIT8)
#define		ECC_BECCCAP_CFL_BUSASERSTR_05					(BIT5)
#define		ECC_BECCCAP_CFL_BUSASERSTR_04					(BIT4)
#define		ECC_BECCCAP_CFL_BUSASERSTR_03					(BIT3)
#define		ECC_BECCCAP_CFL_BUSASERSTR_02					(BIT2)
#define		ECC_BECCCAP_CFL_BUSASERSTR_01					(BIT1)
#define		ECC_BECCCAP_CFL_BUSASERSTR_00					(BIT0)
/* CF_BUSADERSTR */
#define		ECC_BECCCAP_CFL_BUSADERSTR_25					(BIT25)
#define		ECC_BECCCAP_CFL_BUSADERSTR_24					(BIT24)
#define		ECC_BECCCAP_CFL_BUSADERSTR_09					(BIT9)
#define		ECC_BECCCAP_CFL_BUSADERSTR_08					(BIT8)
#define		ECC_BECCCAP_CFL_BUSADERSTR_05					(BIT5)
#define		ECC_BECCCAP_CFL_BUSADERSTR_04					(BIT4)
#define		ECC_BECCCAP_CFL_BUSADERSTR_03					(BIT3)
#define		ECC_BECCCAP_CFL_BUSADERSTR_02					(BIT2)
#define		ECC_BECCCAP_CFL_BUSADERSTR_01					(BIT1)
#define		ECC_BECCCAP_CFL_BUSADERSTR_00					(BIT0)

/* Module: BECCCAP_PERI */
/* PH_BUSERRINT */
#define		ECC_BECCCAP_PERI_BUSERRINT_ADEDIE				(BIT3)
	#define		ECC_BECCCAP_PERI_ERRINT_ADE_DISABLE			(0)
	#define		ECC_BECCCAP_PERI_ERRINT_ADE_ENABLE			(1)
#define		ECC_BECCCAP_PERI_BUSERRINT_ASEDIE				(BIT2)
	#define		ECC_BECCCAP_PERI_ERRINT_ASE_DISABLE			(0)
	#define		ECC_BECCCAP_PERI_ERRINT_ASE_ENABLE			(1)
#define		ECC_BECCCAP_PERI_BUSERRINT_DDEDIE				(BIT1)
	#define		ECC_BECCCAP_PERI_ERRINT_DDE_DISABLE			(0)
	#define		ECC_BECCCAP_PERI_ERRINT_DDE_ENABLE			(1)
#define		ECC_BECCCAP_PERI_BUSERRINT_DSEDIE				(BIT0)
	#define		ECC_BECCCAP_PERI_ERRINT_DSE_DISABLE			(0)
	#define		ECC_BECCCAP_PERI_ERRINT_DSE_ENABLE			(1)
/* PH_BUSASSTCLR */
#define		ECC_BECCCAP_PERI_BUSASSTCLR_25					(BIT25)
#define		ECC_BECCCAP_PERI_BUSASSTCLR_20					(BIT20)
#define		ECC_BECCCAP_PERI_BUSASSTCLR_18					(BIT18)
#define		ECC_BECCCAP_PERI_BUSASSTCLR_17					(BIT17)
#define		ECC_BECCCAP_PERI_BUSASSTCLR_16					(BIT16)
	#define		ECC_BECCCAP_PERI_BUSASSTCLR_CLEAR			(1)
/* PH_BUSADSTCLR */
#define		ECC_BECCCAP_PERI_BUSADSTCLR_25					(BIT25)
#define		ECC_BECCCAP_PERI_BUSADSTCLR_20					(BIT20)
#define		ECC_BECCCAP_PERI_BUSADSTCLR_18					(BIT18)
#define		ECC_BECCCAP_PERI_BUSADSTCLR_17					(BIT17)
#define		ECC_BECCCAP_PERI_BUSADSTCLR_16					(BIT16)
	#define		ECC_BECCCAP_PERI_BUSADSTCLR_CLEAR			(1)
/* PH_BUSDSSTCLR */
#define		ECC_BECCCAP_PERI_BUSDSSTCLR_25					(BIT25)
#define		ECC_BECCCAP_PERI_BUSDSSTCLR_18					(BIT18)
#define		ECC_BECCCAP_PERI_BUSDSSTCLR_17					(BIT17)
#define		ECC_BECCCAP_PERI_BUSDSSTCLR_16					(BIT16)
#define		ECC_BECCCAP_PERI_BUSDSSTCLR_13					(BIT13)
#define		ECC_BECCCAP_PERI_BUSDSSTCLR_12					(BIT12)
#define		ECC_BECCCAP_PERI_BUSDSSTCLR_11					(BIT11)
#define		ECC_BECCCAP_PERI_BUSDSSTCLR_10					(BIT10)
#define		ECC_BECCCAP_PERI_BUSDSSTCLR_09					(BIT9)
#define		ECC_BECCCAP_PERI_BUSDSSTCLR_08					(BIT8)
#define		ECC_BECCCAP_PERI_BUSDSSTCLR_05					(BIT5)
#define		ECC_BECCCAP_PERI_BUSDSSTCLR_04					(BIT4)
#define		ECC_BECCCAP_PERI_BUSDSSTCLR_03					(BIT3)
#define		ECC_BECCCAP_PERI_BUSDSSTCLR_02					(BIT2)
#define		ECC_BECCCAP_PERI_BUSDSSTCLR_01					(BIT1)
#define		ECC_BECCCAP_PERI_BUSDSSTCLR_00					(BIT0)
	#define		ECC_BECCCAP_PERI_BUSDSSTCLR_CLEAR			(1)
/* PH_BUSDDSTCLR */
#define		ECC_BECCCAP_PERI_BUSDDSTCLR_25					(BIT25)
#define		ECC_BECCCAP_PERI_BUSDDSTCLR_18					(BIT18)
#define		ECC_BECCCAP_PERI_BUSDDSTCLR_17					(BIT17)
#define		ECC_BECCCAP_PERI_BUSDDSTCLR_16					(BIT16)
#define		ECC_BECCCAP_PERI_BUSDDSTCLR_13					(BIT13)
#define		ECC_BECCCAP_PERI_BUSDDSTCLR_12					(BIT12)
#define		ECC_BECCCAP_PERI_BUSDDSTCLR_11					(BIT11)
#define		ECC_BECCCAP_PERI_BUSDDSTCLR_10					(BIT10)
#define		ECC_BECCCAP_PERI_BUSDDSTCLR_09					(BIT9)
#define		ECC_BECCCAP_PERI_BUSDDSTCLR_08					(BIT8)
#define		ECC_BECCCAP_PERI_BUSDDSTCLR_05					(BIT5)
#define		ECC_BECCCAP_PERI_BUSDDSTCLR_04					(BIT4)
#define		ECC_BECCCAP_PERI_BUSDDSTCLR_03					(BIT3)
#define		ECC_BECCCAP_PERI_BUSDDSTCLR_02					(BIT2)
#define		ECC_BECCCAP_PERI_BUSDDSTCLR_01					(BIT1)
#define		ECC_BECCCAP_PERI_BUSDDSTCLR_00					(BIT0)
	#define		ECC_BECCCAP_PERI_BUSDDSTCLR_CLEAR			(1)
/* PH_BUSASERSTR */
#define		ECC_BECCCAP_PERI_BUSASERSTR_25					(BIT25)
#define		ECC_BECCCAP_PERI_BUSASERSTR_20					(BIT20)
#define		ECC_BECCCAP_PERI_BUSASERSTR_18					(BIT18)
#define		ECC_BECCCAP_PERI_BUSASERSTR_17					(BIT17)
#define		ECC_BECCCAP_PERI_BUSASERSTR_16					(BIT16)
/* PH_BUSADERSTR */
#define		ECC_BECCCAP_PERI_BUSADERSTR_25					(BIT25)
#define		ECC_BECCCAP_PERI_BUSADERSTR_20					(BIT20)
#define		ECC_BECCCAP_PERI_BUSADERSTR_18					(BIT18)
#define		ECC_BECCCAP_PERI_BUSADERSTR_17					(BIT17)
#define		ECC_BECCCAP_PERI_BUSADERSTR_16					(BIT16)
/* PH_BUSDSERSTR */
#define		ECC_BECCCAP_PERI_BUSDSERSTR_25					(BIT25)
#define		ECC_BECCCAP_PERI_BUSDSERSTR_18					(BIT18)
#define		ECC_BECCCAP_PERI_BUSDSERSTR_17					(BIT17)
#define		ECC_BECCCAP_PERI_BUSDSERSTR_16					(BIT16)
#define		ECC_BECCCAP_PERI_BUSDSERSTR_13					(BIT13)
#define		ECC_BECCCAP_PERI_BUSDSERSTR_12					(BIT12)
#define		ECC_BECCCAP_PERI_BUSDSERSTR_11					(BIT11)
#define		ECC_BECCCAP_PERI_BUSDSERSTR_10					(BIT10)
#define		ECC_BECCCAP_PERI_BUSDSERSTR_09					(BIT9)
#define		ECC_BECCCAP_PERI_BUSDSERSTR_08					(BIT8)
#define		ECC_BECCCAP_PERI_BUSDSERSTR_05					(BIT5)
#define		ECC_BECCCAP_PERI_BUSDSERSTR_04					(BIT4)
#define		ECC_BECCCAP_PERI_BUSDSERSTR_03					(BIT3)
#define		ECC_BECCCAP_PERI_BUSDSERSTR_02					(BIT2)
#define		ECC_BECCCAP_PERI_BUSDSERSTR_01					(BIT1)
#define		ECC_BECCCAP_PERI_BUSDSERSTR_00					(BIT0)
/* PH_BUSDDERSTR */
#define		ECC_BECCCAP_PERI_BUSDDERSTR_25					(BIT25)
#define		ECC_BECCCAP_PERI_BUSDDERSTR_18					(BIT18)
#define		ECC_BECCCAP_PERI_BUSDDERSTR_17					(BIT17)
#define		ECC_BECCCAP_PERI_BUSDDERSTR_16					(BIT16)
#define		ECC_BECCCAP_PERI_BUSDDERSTR_13					(BIT13)
#define		ECC_BECCCAP_PERI_BUSDDERSTR_12					(BIT12)
#define		ECC_BECCCAP_PERI_BUSDDERSTR_11					(BIT11)
#define		ECC_BECCCAP_PERI_BUSDDERSTR_10					(BIT10)
#define		ECC_BECCCAP_PERI_BUSDDERSTR_09					(BIT9)
#define		ECC_BECCCAP_PERI_BUSDDERSTR_08					(BIT8)
#define		ECC_BECCCAP_PERI_BUSDDERSTR_05					(BIT5)
#define		ECC_BECCCAP_PERI_BUSDDERSTR_04					(BIT4)
#define		ECC_BECCCAP_PERI_BUSDDERSTR_03					(BIT3)
#define		ECC_BECCCAP_PERI_BUSDDERSTR_02					(BIT2)
#define		ECC_BECCCAP_PERI_BUSDDERSTR_01					(BIT1)
#define		ECC_BECCCAP_PERI_BUSDDERSTR_00					(BIT0)

/* Module: BECCCAP_DMDT */
/* DM_BUSERRINT */
#define		ECC_BECCCAP_DMDT_BUSERRINT_DDEDIE				(BIT1)
	#define		ECC_BECCCAP_DMDT_ERRINT_DDE_DISABLE			(0)
	#define		ECC_BECCCAP_DMDT_ERRINT_DDE_ENABLE			(1)
#define		ECC_BECCCAP_DMDT_BUSERRINT_DSEDIE				(BIT0)
	#define		ECC_BECCCAP_DMDT_ERRINT_DSE_DISABLE			(0)
	#define		ECC_BECCCAP_DMDT_ERRINT_DSE_ENABLE			(1)
/* DM_BUSDSSTCLR */
#define		ECC_BECCCAP_DMDT_BUSDSSTCLR_08					(BIT8)
#define		ECC_BECCCAP_DMDT_BUSDSSTCLR_07					(BIT7)
#define		ECC_BECCCAP_DMDT_BUSDSSTCLR_06					(BIT6)
#define		ECC_BECCCAP_DMDT_BUSDSSTCLR_05					(BIT5)
#define		ECC_BECCCAP_DMDT_BUSDSSTCLR_04					(BIT4)
#define		ECC_BECCCAP_DMDT_BUSDSSTCLR_03					(BIT3)
#define		ECC_BECCCAP_DMDT_BUSDSSTCLR_02					(BIT2)
#define		ECC_BECCCAP_DMDT_BUSDSSTCLR_01					(BIT1)
#define		ECC_BECCCAP_DMDT_BUSDSSTCLR_00					(BIT0)
	#define		ECC_BECCCAP_DMDT_BUSDSSTCLR_CLEAR			(1)
/* DM_BUSDDSTCLR */
#define		ECC_BECCCAP_DMDT_BUSDDSTCLR_08					(BIT8)
#define		ECC_BECCCAP_DMDT_BUSDDSTCLR_07					(BIT7)
#define		ECC_BECCCAP_DMDT_BUSDDSTCLR_06					(BIT6)
#define		ECC_BECCCAP_DMDT_BUSDDSTCLR_05					(BIT5)
#define		ECC_BECCCAP_DMDT_BUSDDSTCLR_04					(BIT4)
#define		ECC_BECCCAP_DMDT_BUSDDSTCLR_03					(BIT3)
#define		ECC_BECCCAP_DMDT_BUSDDSTCLR_02					(BIT2)
#define		ECC_BECCCAP_DMDT_BUSDDSTCLR_01					(BIT1)
#define		ECC_BECCCAP_DMDT_BUSDDSTCLR_00					(BIT0)
	#define		ECC_BECCCAP_DMDT_BUSDDSTCLR_CLEAR			(1)
/* DM_BUSDSERSTR */
#define		ECC_BECCCAP_DMDT_BUSDSERSTR_08					(BIT8)
#define		ECC_BECCCAP_DMDT_BUSDSERSTR_07					(BIT7)
#define		ECC_BECCCAP_DMDT_BUSDSERSTR_06					(BIT6)
#define		ECC_BECCCAP_DMDT_BUSDSERSTR_05					(BIT5)
#define		ECC_BECCCAP_DMDT_BUSDSERSTR_04					(BIT4)
#define		ECC_BECCCAP_DMDT_BUSDSERSTR_03					(BIT3)
#define		ECC_BECCCAP_DMDT_BUSDSERSTR_02					(BIT2)
#define		ECC_BECCCAP_DMDT_BUSDSERSTR_01					(BIT1)
#define		ECC_BECCCAP_DMDT_BUSDSERSTR_00					(BIT0)
/* DM_BUSDDERSTR */
#define		ECC_BECCCAP_DMDT_BUSDDERSTR_08					(BIT8)
#define		ECC_BECCCAP_DMDT_BUSDDERSTR_07					(BIT7)
#define		ECC_BECCCAP_DMDT_BUSDDERSTR_06					(BIT6)
#define		ECC_BECCCAP_DMDT_BUSDDERSTR_05					(BIT5)
#define		ECC_BECCCAP_DMDT_BUSDDERSTR_04					(BIT4)
#define		ECC_BECCCAP_DMDT_BUSDDERSTR_03					(BIT3)
#define		ECC_BECCCAP_DMDT_BUSDDERSTR_02					(BIT2)
#define		ECC_BECCCAP_DMDT_BUSDDERSTR_01					(BIT1)
#define		ECC_BECCCAP_DMDT_BUSDDERSTR_00					(BIT0)

/* Module: BECCCAP_EMU */
/* EM_BUSERRINT */
#define		ECC_BECCCAP_EMU_BUSERRINT_ADEDIE				(BIT3)
	#define		ECC_BECCCAP_EMU_ERRINT_ADE_DISABLE			(0)
	#define		ECC_BECCCAP_EMU_ERRINT_ADE_ENABLE			(1)
#define		ECC_BECCCAP_EMU_BUSERRINT_ASEDIE				(BIT2)
	#define		ECC_BECCCAP_EMU_ERRINT_ASE_DISABLE			(0)
	#define		ECC_BECCCAP_EMU_ERRINT_ASE_ENABLE			(1)
#define		ECC_BECCCAP_EMU_BUSERRINT_DDEDIE				(BIT1)
	#define		ECC_BECCCAP_EMU_ERRINT_DDE_DISABLE			(0)
	#define		ECC_BECCCAP_EMU_ERRINT_DDE_ENABLE			(1)
#define		ECC_BECCCAP_EMU_BUSERRINT_DSEDIE				(BIT0)
	#define		ECC_BECCCAP_EMU_ERRINT_DSE_DISABLE			(0)
	#define		ECC_BECCCAP_EMU_ERRINT_DSE_ENABLE			(1)
/* EM_BUSASSTCLR */
#define		ECC_BECCCAP_EMU_BUSASSTCLR_18					(BIT18)
#define		ECC_BECCCAP_EMU_BUSASSTCLR_17					(BIT17)
#define		ECC_BECCCAP_EMU_BUSASSTCLR_16					(BIT16)
#define		ECC_BECCCAP_EMU_BUSASSTCLR_10					(BIT10)
#define		ECC_BECCCAP_EMU_BUSASSTCLR_08					(BIT8)
#define		ECC_BECCCAP_EMU_BUSASSTCLR_06					(BIT6)
#define		ECC_BECCCAP_EMU_BUSASSTCLR_04					(BIT4)
#define		ECC_BECCCAP_EMU_BUSASSTCLR_02					(BIT2)
#define		ECC_BECCCAP_EMU_BUSASSTCLR_00					(BIT0)
	#define		ECC_BECCCAP_EMU_BUSASSTCLR_CLEAR			(1)
/* EM_BUSADSTCLR */
#define		ECC_BECCCAP_EMU_BUSADSTCLR_18					(BIT18)
#define		ECC_BECCCAP_EMU_BUSADSTCLR_17					(BIT17)
#define		ECC_BECCCAP_EMU_BUSADSTCLR_16					(BIT16)
#define		ECC_BECCCAP_EMU_BUSADSTCLR_10					(BIT10)
#define		ECC_BECCCAP_EMU_BUSADSTCLR_08					(BIT8)
#define		ECC_BECCCAP_EMU_BUSADSTCLR_06					(BIT6)
#define		ECC_BECCCAP_EMU_BUSADSTCLR_04					(BIT4)
#define		ECC_BECCCAP_EMU_BUSADSTCLR_02					(BIT2)
#define		ECC_BECCCAP_EMU_BUSADSTCLR_00					(BIT0)
	#define		ECC_BECCCAP_EMU_BUSADSTCLR_CLEAR			(1)
/* EM_BUSDSSTCLR */
#define		ECC_BECCCAP_EMU_BUSDSSTCLR_DSSTCLR17			(BIT17)
	#define		ECC_BECCCAP_EMU_BUSDSSTCLR_CLEAR			(1)
/* EM_BUSDDSTCLR */
#define		ECC_BECCCAP_EMU_BUSDDSTCLR_DDSTCLR17			(BIT17)
	#define		ECC_BECCCAP_EMU_BUSDDSTCLR_CLEAR			(1)
/* EM_BUSASERSTR */
#define		ECC_BECCCAP_EMU_BUSASERSTR_18					(BIT18)
#define		ECC_BECCCAP_EMU_BUSASERSTR_17					(BIT17)
#define		ECC_BECCCAP_EMU_BUSASERSTR_16					(BIT16)
#define		ECC_BECCCAP_EMU_BUSASERSTR_10					(BIT10)
#define		ECC_BECCCAP_EMU_BUSASERSTR_08					(BIT8)
#define		ECC_BECCCAP_EMU_BUSASERSTR_06					(BIT6)
#define		ECC_BECCCAP_EMU_BUSASERSTR_04					(BIT4)
#define		ECC_BECCCAP_EMU_BUSASERSTR_02					(BIT2)
#define		ECC_BECCCAP_EMU_BUSASERSTR_00					(BIT0)
/* EM_BUSADERSTR */
#define		ECC_BECCCAP_EMU_BUSADERSTR_18					(BIT18)
#define		ECC_BECCCAP_EMU_BUSADERSTR_17					(BIT17)
#define		ECC_BECCCAP_EMU_BUSADERSTR_16					(BIT16)
#define		ECC_BECCCAP_EMU_BUSADERSTR_10					(BIT10)
#define		ECC_BECCCAP_EMU_BUSADERSTR_08					(BIT8)
#define		ECC_BECCCAP_EMU_BUSADERSTR_06					(BIT6)
#define		ECC_BECCCAP_EMU_BUSADERSTR_04					(BIT4)
#define		ECC_BECCCAP_EMU_BUSADERSTR_02					(BIT2)
#define		ECC_BECCCAP_EMU_BUSADERSTR_00					(BIT0)
/* EM_BUSDSERSTR */
#define		ECC_BECCCAP_EMU_BUSDSERSTR_17					(BIT17)
/* EM_BUSDDERSTR */
#define		ECC_BECCCAP_EMU_BUSDDERSTR_17					(BIT17)

/* Module: PBnECC */
/* APECKCPROT */
#define		ECC_PBNECC_APECKCPROT_KCPROT					(0xFFFFFFFEU)
#define		ECC_PBNECC_APECKCPROT_KCPROT_0					(BIT1)
#define		ECC_PBNECC_APECKCPROT_KCE						(BIT0)
	#define		ECC_PBNECC_APECKCPROT_KCE_DISABLE			(0xA5A5A500U)
	#define		ECC_PBNECC_APECKCPROT_KCE_ENABLE			(0xA5A5A501U)

/* Module: DFP_KCPROT */
/* DFP_ECCKCPROT */
#define		ECC_DFP_KCPROT_DFP_KCPROT_KCPROT				(0xFFFFFFFEU)
#define		ECC_DFP_KCPROT_DFP_KCPROT_KCE					(BIT0)
	#define		ECC_DFP_KCPROT_DFP_KCPROT_KCE_DISABLE		(0xA5A5A500U)
	#define		ECC_DFP_KCPROT_DFP_KCPROT_KCE_ENABLE		(0xA5A5A501U)

/* Module: DFP_ECCCAP_ROM */
/* DFPR_BUSERRINT */
#define		ECC_DFP_ECCCAP_ROM_BUSERRINT_DDEDIE				(BIT1)
	#define		ECC_DFP_ECCCAP_ROM_ERRINT_DDE_DISABLE		(0)
	#define		ECC_DFP_ECCCAP_ROM_ERRINT_DDE_ENABLE		(1)
#define		ECC_DFP_ECCCAP_ROM_BUSERRINT_DSEDIE				(BIT0)
	#define		ECC_DFP_ECCCAP_ROM_ERRINT_DSE_DISABLE		(0)
	#define		ECC_DFP_ECCCAP_ROM_ERRINT_DSE_ENABLE		(1)
/* DFPR_BUSDSSTCLR */
#define		ECC_DFP_ECCCAP_ROM_BUSDSSTCLR_DSSTCLR00			(BIT0)
	#define		ECC_DFP_ECCCAP_ROM_BUSDSSTCLR_CLEAR			(1)
/* DFPR_BUSDDSTCLR */
#define		ECC_DFP_ECCCAP_ROM_BUSDDSTCLR_DDSTCLR00			(BIT0)
	#define		ECC_DFP_ECCCAP_ROM_BUSDDSTCLR_CLEAR			(1)
/* DFPR_BUSDSERSTR */
#define		ECC_DFP_ECCCAP_ROM_BUSDSERSTR_DSEDF00			(BIT0)
/* DFPR_BUSDDERSTR */
#define		ECC_DFP_ECCCAP_ROM_BUSDDERSTR_DDEDF00			(BIT0)

/* Module: DFP_ECCCAP_SYS */
/* DFPS_BUSERRINT */
#define		ECC_DFP_ECCCAP_SYS_BUSERRINT_DDEDIE				(BIT1)
	#define		ECC_DFP_ECCCAP_SYS_ERRINT_DDE_DISABLE		(0)
	#define		ECC_DFP_ECCCAP_SYS_ERRINT_DDE_ENABLE		(1)
#define		ECC_DFP_ECCCAP_SYS_BUSERRINT_DSEDIE				(BIT0)
	#define		ECC_DFP_ECCCAP_SYS_ERRINT_DSE_DISABLE		(0)
	#define		ECC_DFP_ECCCAP_SYS_ERRINT_DSE_ENABLE		(1)
/* DFPS_BUSDSSTCLR */
#define		ECC_DFP_ECCCAP_SYS_DSSTCLR_DSSTCLR00			(BIT0)
	#define		ECC_DFP_ECCCAP_SYS_DSSTCLR_CLEAR			(1)
/* DFPS_BUSDDSTCLR */
#define		ECC_DFP_ECCCAP_SYS_DDSTCLR_DDSTCLR00			(BIT0)
	#define		ECC_DFP_ECCCAP_SYS_DDSTCLR_CLEAR			(1)
/* DFPS_BUSDSERSTR */
#define		ECC_DFP_ECCCAP_SYS_DSERSTR_DSEDF00				(BIT0)
/* DFPS_BUSDDERSTR */
#define		ECC_DFP_ECCCAP_SYS_DDERSTR_DDEDF00				(BIT0)

/* Module: DFP_ECCCAP_FNT */
/* DFPF_BUSERRINT */
#define		ECC_DFP_ECCCAP_FNT_BUSERRINT_ADEDIE				(BIT3)
	#define		ECC_DFP_ECCCAP_FNT_ERRINT_ADE_DISABLE		(0)
	#define		ECC_DFP_ECCCAP_FNT_ERRINT_ADE_ENABLE		(1)
#define		ECC_DFP_ECCCAP_FNT_BUSERRINT_ASEDIE				(BIT2)
	#define		ECC_DFP_ECCCAP_FNT_ERRINT_ASE_DISABLE		(0)
	#define		ECC_DFP_ECCCAP_FNT_ERRINT_ASE_ENABLE		(1)
#define		ECC_DFP_ECCCAP_FNT_BUSERRINT_DDEDIE				(BIT1)
	#define		ECC_DFP_ECCCAP_FNT_ERRINT_DDE_DISABLE		(0)
	#define		ECC_DFP_ECCCAP_FNT_ERRINT_DDE_ENABLE		(1)
#define		ECC_DFP_ECCCAP_FNT_BUSERRINT_DSEDIE				(BIT0)
	#define		ECC_DFP_ECCCAP_FNT_ERRINT_DSE_DISABLE		(0)
	#define		ECC_DFP_ECCCAP_FNT_ERRINT_DSE_ENABLE		(1)
/* DFPF_BUSASSTCLR */
#define		ECC_DFP_ECCCAP_FNT_ASSTCLR_01					(BIT1)
#define		ECC_DFP_ECCCAP_FNT_ASSTCLR_00					(BIT0)
	#define		ECC_DFP_ECCCAP_FNT_ASSTCLR_CLEAR			(1)
/* DFPF_BUSADSTCLR */
#define		ECC_DFP_ECCCAP_FNT_ADSTCLR_01					(BIT1)
#define		ECC_DFP_ECCCAP_FNT_ADSTCLR_00					(BIT0)
	#define		ECC_DFP_ECCCAP_FNT_BUSADSTCLR_CLEAR			(1)
/* DFPF_BUSDSSTCLR */
#define		ECC_DFP_ECCCAP_FNT_BUSDSSTCLR_00				(BIT0)
	#define		ECC_DFP_ECCCAP_FNT_BUSDSSTCLR_CLEAR			(1)
/* DFPF_BUSDDSTCLR */
#define		ECC_DFP_ECCCAP_FNT_BUSDDSTCLR_00				(BIT0)
	#define		ECC_DFP_ECCCAP_FNT_BUSDDSTCLR_CLEAR			(1)
/* DFPF_BUSASERSTR */
#define		ECC_DFP_ECCCAP_FNT_ASERSTR_01					(BIT1)
#define		ECC_DFP_ECCCAP_FNT_ASERSTR_00					(BIT0)
/* DFPF_BUSADERSTR */
#define		ECC_DFP_ECCCAP_FNT_ADERSTR_01					(BIT1)
#define		ECC_DFP_ECCCAP_FNT_ADERSTR_00					(BIT0)
/* DFPF_BUSDSERSTR */
#define		ECC_DFP_ECCCAP_FNT_DSERSTR_00					(BIT0)
/* DFPF_BUSDDERSTR */
#define		ECC_DFP_ECCCAP_FNT_DDERSTR_00					(BIT0)

/* Module: HBnECC */
/* HBECECCCTL */
#define		ECC_HBNECC_HBECECCCTL_AECCDIS					(BIT2)
	#define		ECC_HBNECC_HBECECCCTL_AECCDIS_ENABLE		(0)
	#define		ECC_HBNECC_HBECECCCTL_AECCDIS_DISABLE		(1)
#define		ECC_HBNECC_HBECECCCTL_SECDIS					(BIT1)
	#define		ECC_HBNECC_HBECECCCTL_SECDIS_CORRECT		(0)
	#define		ECC_HBNECC_HBECECCCTL_SECDIS_NOTCORRECT		(1)
#define		ECC_HBNECC_HBECECCCTL_ECCDIS					(BIT0)
	#define		ECC_HBNECC_HBECECCCTL_ECCDIS_ENABLE			(0)
	#define		ECC_HBNECC_HBECECCCTL_ECCDIS_DISABLE		(1)
/* HBECERRINT */
#define		ECC_HBNECC_HBECERRINT_ADEDIE					(BIT5)
	#define		ECC_HBNECC_HBECERRINT_ADEDIE_DISABLE		(0)
	#define		ECC_HBNECC_HBECERRINT_ADEDIE_ENABLE			(1)
#define		ECC_HBNECC_HBECERRINT_ASEDIE					(BIT4)
	#define		ECC_HBNECC_HBECERRINT_ASEDIE_DISABLE		(0)
	#define		ECC_HBNECC_HBECERRINT_ASEDIE_ENABLE			(1)
#define		ECC_HBNECC_HBECERRINT_DEDIE						(BIT1)
	#define		ECC_HBNECC_HBECERRINT_DEDIE_DISABLE			(0)
	#define		ECC_HBNECC_HBECERRINT_DEDIE_ENABLE			(1)
#define		ECC_HBNECC_HBECERRINT_SEDIE						(BIT0)
	#define		ECC_HBNECC_HBECERRINT_SEDIE_DISABLE			(0)
	#define		ECC_HBNECC_HBECERRINT_SEDIE_ENABLE			(1)
/* HBECSTCLR */
#define		ECC_HBNECC_HBECSTCLR_STCLR0						(BIT0)
	#define		ECC_HBNECC_HBECSTCLR_CLEAR					(1)
/* HBEC1STERSTR */
#define		ECC_HBNECC_HBEC1STERSTR_AECDEDF0				(BIT7)
#define		ECC_HBNECC_HBEC1STERSTR_AECSEDF0				(BIT6)
#define		ECC_HBNECC_HBEC1STERSTR_DEDF0					(BIT1)
#define		ECC_HBNECC_HBEC1STERSTR_SEDF0					(BIT0)
/* HBECTSTCTL */
#define		ECC_HBNECC_HBECTSTCTL_ECCTST					(BIT1)
	#define		ECC_HBNECC_HBECTSTCTL_ECCTST_NORMAL			(0)
	#define		ECC_HBNECC_HBECTSTCTL_ECCTST_TEST			(1)
/* HBECTSTDIN0 */
/* No bit definition required because it only has byte access */
/* HBECTSTEIN */
#define		ECC_HBNECC_HBECTSTEIN_ECC						(BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)
#define		ECC_HBNECC_HBECTSTEIN_ECC_0						(BIT0)
/* HBECKCPROT */
#define		ECC_HBNECC_HBECKCPROT_KCPROT					(0xFFFFFFFEU)
#define		ECC_HBNECC_HBECKCPROT_KCPROT_0					(BIT1)
#define		ECC_HBNECC_HBECKCPROT_KCE						(BIT0)
	#define		ECC_HBNECC_HBECKCPROT_KCE_DISABLE			(0xA5A5A500U)
	#define		ECC_HBNECC_HBECKCPROT_KCE_ENABLE			(0xA5A5A501U)

/* Module: BECCCAP_V2An */
/* PHC_BUSERRINT */
#define		ECC_BECCCAP_V2AN_BUSERRINT_ADEDIE			(BIT3)
	#define		ECC_BECCCAP_V2AN_ERRINT_ADE_DISABLE		(0)
	#define		ECC_BECCCAP_V2AN_ERRINT_ADE_ENABLE		(1)
#define		ECC_BECCCAP_V2AN_BUSERRINT_ASEDIE			(BIT2)
	#define		ECC_BECCCAP_V2AN_ERRINT_ASE_DISABLE		(0)
	#define		ECC_BECCCAP_V2AN_ERRINT_ASE_ENABLE		(1)
#define		ECC_BECCCAP_V2AN_BUSERRINT_DDEDIE			(BIT1)
	#define		ECC_BECCCAP_V2AN_ERRINT_DDE_DISABLE		(0)
	#define		ECC_BECCCAP_V2AN_ERRINT_DDE_ENABLE		(1)
#define		ECC_BECCCAP_V2AN_BUSERRINT_DSEDIE			(BIT0)
	#define		ECC_BECCCAP_V2AN_ERRINT_DSE_DISABLE		(0)
	#define		ECC_BECCCAP_V2AN_ERRINT_DSE_ENABLE		(1)
/* PHC_BUSASSTCLR */
#define		ECC_BECCCAP_V2AN_BUSASSTCLR_ASSTCLR00		(BIT0)
	#define		ECC_BECCCAP_V2AN_BUSASSTCLR_CLEAR		(1)
/* PHC_BUSADSTCLR */
#define		ECC_BECCCAP_V2AN_BUSADSTCLR_ADSTCLR00		(BIT0)
	#define		ECC_BECCCAP_V2AN_BUSADSTCLR_CLEAR		(1)
/* PHC_BUSDSSTCLR */
#define		ECC_BECCCAP_V2AN_BUSDSSTCLR_DSSTCLR00		(BIT0)
	#define		ECC_BECCCAP_V2AN_BUSDSSTCLR_CLEAR		(1)
/* PHC_BUSDDSTCLR */
#define		ECC_BECCCAP_V2AN_BUSDDSTCLR_DDSTCLR00		(BIT0)
	#define		ECC_BECCCAP_V2AN_BUSDDSTCLR_CLEAR		(1)
/* PHC_BUSASERSTR */
#define		ECC_BECCCAP_V2AN_BUSASERSTR_ASEDF00			(BIT0)
/* PHC_BUSADERSTR */
#define		ECC_BECCCAP_V2AN_BUSADERSTR_ADEDF00			(BIT0)
/* PHC_BUSDSERSTR */
#define		ECC_BECCCAP_V2AN_BUSDSERSTR_DSEDF00			(BIT0)
/* PHC_BUSDDERSTR */
#define		ECC_BECCCAP_V2AN_BUSDDERSTR_DDEDF00			(BIT0)


/* Error Injection for ECC Function */
/* Module: ERRGEN */
/* EGDATORG0 */
/* No bit definition required because it only has byte access */
/* EGDATORG1 */
/* No bit definition required because it only has byte access */
/* EGECCCAL0 */
#define		ECC_ERRGEN_EGECCCAL0_ECCCAL						(BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)
#define		ECC_ERRGEN_EGECCCAL0_ECCCAL_0					(BIT0)
/* EGECCCAL1 */
#define		ECC_ERRGEN_EGECCCAL1_ECCCAL						(BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)
#define		ECC_ERRGEN_EGECCCAL1_ECCCAL_0					(BIT0)
/* EGDATINV0 */
/* No bit definition required because it only has byte access */
/* EGDATINV1 */
/* No bit definition required because it only has byte access */
/* EGECCINV0 */
#define		ECC_ERRGEN_EGECCINV0_ECCINV						(BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)
#define		ECC_ERRGEN_EGECCINV0_ECCINV_0					(BIT0)
/* EGECCINV1 */
#define		ECC_ERRGEN_EGECCINV1_ECCINV						(BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)
#define		ECC_ERRGEN_EGECCINV1_ECCINV_0					(BIT0)
/* EGECC8CAL */
#define		ECC_ERRGEN_EGECC8CAL_ECC8CAL					(0x0000FFU)
#define		ECC_ERRGEN_EGECC8CAL_ECC8CAL_0					(BIT0)

/*----------------------------------------------------------------------------------------------*/
/*	struct address definition																	*/
/*----------------------------------------------------------------------------------------------*/
#define		REG_ECC_ECCKC					(*(volatile Reg_Ecc_EccKcType			   *)(0xFFFB2800U))

#define		REG_ECC_ECCCNT_CFP_PE0CL0		(*(volatile Reg_Ecc_EccCnt_Cfp_Pe0Cl0Type  *)(0xFFC48000U))
#define		REG_ECC_ECCCNT_CFP_PE1CL0		(*(volatile Reg_Ecc_EccCnt_Cfp_Pe1Cl0Type  *)(0xFFC48080U))
#define		REG_ECC_ECCCNT_CFP_PE2CL1		(*(volatile Reg_Ecc_EccCnt_Cfp_Pe2Cl1Type  *)(0xFFC48100U))
#define		REG_ECC_ECCCNT_CFP_PE3CL1		(*(volatile Reg_Ecc_EccCnt_Cfp_Pe3Cl1Type  *)(0xFFC48180U))
#define		REG_ECC_ECCCNT_CFP_PE4CL2		(*(volatile Reg_Ecc_EccCnt_Cfp_Pe4Cl2Type  *)(0xFFC48200U))
#define		REG_ECC_ECCCNT_CFP_PE5CL2		(*(volatile Reg_Ecc_EccCnt_Cfp_Pe5Cl2Type  *)(0xFFC48280U))
#define		REG_ECC_ECCCNT_CFCCL0			(*(volatile Reg_Ecc_EccCnt_Cfccl0Type	   *)(0xFFC48800U))
#define		REG_ECC_ECCCNT_CFCCL1			(*(volatile Reg_Ecc_EccCnt_Cfccl1Type	   *)(0xFFC48880U))
#define		REG_ECC_ECCCNT_CFCCL2			(*(volatile Reg_Ecc_EccCnt_Cfccl2Type	   *)(0xFFC48900U))
#define		REG_ECC_ECCCNT_CFS				(*(volatile Reg_Ecc_EccCnt_CfsType		   *)(0xFFC48A00U))
#define		REG_ECC_MECCCAP_CFL				(*(volatile Reg_Ecc_MeccCap_CflType		   *)(0xFFC55400U))

#define		REG_ECC_ECCDF					(*(volatile Reg_Ecc_EccDfType			   *)(0xFFC62C00U))

#define		REG_ECC_ECCCNT_LR_PE0CL0		(*(volatile Reg_Ecc_EccCnt_Lr_Pe0Cl0Type   *)(0xFFC49800U))
#define		REG_ECC_ECCCNT_LR_PE1CL0		(*(volatile Reg_Ecc_EccCnt_Lr_Pe1Cl0Type   *)(0xFFC49880U))
#define		REG_ECC_ECCCNT_LR_PE2CL1		(*(volatile Reg_Ecc_EccCnt_Lr_Pe2Cl1Type   *)(0xFFC49900U))
#define		REG_ECC_ECCCNT_LR_PE3CL1		(*(volatile Reg_Ecc_EccCnt_Lr_Pe3Cl1Type   *)(0xFFC49980U))
#define		REG_ECC_ECCCNT_LR_PE4CL2		(*(volatile Reg_Ecc_EccCnt_Lr_Pe4Cl2Type   *)(0xFFC49A00U))
#define		REG_ECC_ECCCNT_LR_PE5CL2		(*(volatile Reg_Ecc_EccCnt_Lr_Pe5Cl2Type   *)(0xFFC49A80U))
#define		REG_ECC_MECCCAP_LR_PE0CL0		(*(volatile Reg_Ecc_MeccCap_Lr_Pe0Cl0Type  *)(0xFFC52000U))
#define		REG_ECC_MECCCAP_LR_PE1CL0		(*(volatile Reg_Ecc_MeccCap_Lr_Pe1Cl0Type  *)(0xFFC52200U))
#define		REG_ECC_MECCCAP_LR_PE2CL1		(*(volatile Reg_Ecc_MeccCap_Lr_Pe2Cl1Type  *)(0xFFC52400U))
#define		REG_ECC_MECCCAP_LR_PE3CL1		(*(volatile Reg_Ecc_MeccCap_Lr_Pe3Cl1Type  *)(0xFFC52600U))
#define		REG_ECC_MECCCAP_LR_PE4CL2		(*(volatile Reg_Ecc_MeccCap_Lr_Pe4Cl2Type  *)(0xFFC52800U))
#define		REG_ECC_MECCCAP_LR_PE5CL2		(*(volatile Reg_Ecc_MeccCap_Lr_Pe5Cl2Type  *)(0xFFC52A00U))
#define		REG_ECC_MECCCAP_LRA				(*(volatile Reg_Ecc_MeccCap_LraType		   *)(0xFFC55000U))

#define		REG_ECC_ECCCNT_CRCCL0			(*(volatile Reg_Ecc_EccCnt_Crccl0Type	   *)(0xFFC49C00U))
#define		REG_ECC_ECCCNT_CRCCL1			(*(volatile Reg_Ecc_EccCnt_Crccl1Type	   *)(0xFFC49C80U))
#define		REG_ECC_ECCCNT_CRCCL2			(*(volatile Reg_Ecc_EccCnt_Crccl2Type	   *)(0xFFC49D00U))
#define		REG_ECC_ECCCNT_CRCCL4			(*(volatile Reg_Ecc_EccCnt_Crccl4Type	   *)(0xFFC5C380U))
#define		REG_ECC_ECCCNT_CRA				(*(volatile Reg_Ecc_EccCnt_CraType		   *)(0xFFC49E00U))
#define		REG_ECC_MECCCAP_CRAM			(*(volatile Reg_Ecc_MeccCap_CramType	   *)(0xFFC55200U))

#define		REG_ECC_ECCCNT_IT_PE0CL0		(*(volatile Reg_Ecc_EccCnt_It_Pe0Cl0Type   *)(0xFFC49000U))
#define		REG_ECC_ECCCNT_IT_PE1CL0		(*(volatile Reg_Ecc_EccCnt_It_Pe1Cl0Type   *)(0xFFC49080U))
#define		REG_ECC_ECCCNT_IT_PE2CL1		(*(volatile Reg_Ecc_EccCnt_It_Pe2Cl1Type   *)(0xFFC49100U))
#define		REG_ECC_ECCCNT_IT_PE3CL1		(*(volatile Reg_Ecc_EccCnt_It_Pe3Cl1Type   *)(0xFFC49180U))
#define		REG_ECC_ECCCNT_IT_PE4CL2		(*(volatile Reg_Ecc_EccCnt_It_Pe4Cl2Type   *)(0xFFC49200U))
#define		REG_ECC_ECCCNT_IT_PE5CL2		(*(volatile Reg_Ecc_EccCnt_It_Pe5Cl2Type   *)(0xFFC49280U))
#define		REG_ECC_ECCCNT_ID_PE0CL0		(*(volatile Reg_Ecc_EccCnt_Id_Pe0Cl0Type   *)(0xFFC49400U))
#define		REG_ECC_ECCCNT_ID_PE1CL0		(*(volatile Reg_Ecc_EccCnt_Id_Pe1Cl0Type   *)(0xFFC49480U))
#define		REG_ECC_ECCCNT_ID_PE2CL1		(*(volatile Reg_Ecc_EccCnt_Id_Pe2Cl1Type   *)(0xFFC49500U))
#define		REG_ECC_ECCCNT_ID_PE3CL1		(*(volatile Reg_Ecc_EccCnt_Id_Pe3Cl1Type   *)(0xFFC49580U))
#define		REG_ECC_ECCCNT_ID_PE4CL2		(*(volatile Reg_Ecc_EccCnt_Id_Pe4Cl2Type   *)(0xFFC49600U))
#define		REG_ECC_ECCCNT_ID_PE5CL2		(*(volatile Reg_Ecc_EccCnt_Id_Pe5Cl2Type   *)(0xFFC49680U))
#define		REG_ECC_MECCCAP_IT_PE0CL0		(*(volatile Reg_Ecc_MeccCap_It_Pe0Cl0Type  *)(0xFFC53000U))
#define		REG_ECC_MECCCAP_IT_PE1CL0		(*(volatile Reg_Ecc_MeccCap_It_Pe1Cl0Type  *)(0xFFC53200U))
#define		REG_ECC_MECCCAP_IT_PE2CL1		(*(volatile Reg_Ecc_MeccCap_It_Pe2Cl1Type  *)(0xFFC53400U))
#define		REG_ECC_MECCCAP_IT_PE3CL1		(*(volatile Reg_Ecc_MeccCap_It_Pe3Cl1Type  *)(0xFFC53600U))
#define		REG_ECC_MECCCAP_IT_PE4CL2		(*(volatile Reg_Ecc_MeccCap_It_Pe4Cl2Type  *)(0xFFC53800U))
#define		REG_ECC_MECCCAP_IT_PE5CL2		(*(volatile Reg_Ecc_MeccCap_It_Pe5Cl2Type  *)(0xFFC53A00U))
#define		REG_ECC_MECCCAP_ID_PE0CL0		(*(volatile Reg_Ecc_MeccCap_Id_Pe0Cl0Type  *)(0xFFC54000U))
#define		REG_ECC_MECCCAP_ID_PE1CL0		(*(volatile Reg_Ecc_MeccCap_Id_Pe1Cl0Type  *)(0xFFC54200U))
#define		REG_ECC_MECCCAP_ID_PE2CL1		(*(volatile Reg_Ecc_MeccCap_Id_Pe2Cl1Type  *)(0xFFC54400U))
#define		REG_ECC_MECCCAP_ID_PE3CL1		(*(volatile Reg_Ecc_MeccCap_Id_Pe3Cl1Type  *)(0xFFC54600U))
#define		REG_ECC_MECCCAP_ID_PE4CL2		(*(volatile Reg_Ecc_MeccCap_Id_Pe4Cl2Type  *)(0xFFC54800U))
#define		REG_ECC_MECCCAP_ID_PE5CL2		(*(volatile Reg_Ecc_MeccCap_Id_Pe5Cl2Type  *)(0xFFC54A00U))

#define		REG_ECC_ECCCNT_DTS				(*(volatile Reg_Ecc_EccCnt_DtsType		   *)(0xFFC4A000U))
#define		REG_ECC_ECCCNT_DMDE0			(*(volatile Reg_Ecc_EccCnt_Dmde0Type	   *)(0xFFC4A400U))
#define		REG_ECC_ECCCNT_DMDA0			(*(volatile Reg_Ecc_EccCnt_Dmda0Type	   *)(0xFFC4A480U))
#define		REG_ECC_ECCCNT_DMDE1			(*(volatile Reg_Ecc_EccCnt_Dmde1Type	   *)(0xFFC4A500U))
#define		REG_ECC_ECCCNT_DMDA1			(*(volatile Reg_Ecc_EccCnt_Dmda1Type	   *)(0xFFC4A580U))
#define		REG_ECC_MECCCAP_DTS				(*(volatile Reg_Ecc_MeccCap_DtsType		   *)(0xFFC55600U))
#define		REG_ECC_MECCCAP_DMDE0			(*(volatile Reg_Ecc_MeccCap_Dmde0Type	   *)(0xFFC55800U))
#define		REG_ECC_MECCCAP_DMDA0			(*(volatile Reg_Ecc_MeccCap_Dmda0Type	   *)(0xFFC55A00U))
#define		REG_ECC_MECCCAP_DMDE1			(*(volatile Reg_Ecc_MeccCap_Dmde1Type	   *)(0xFFC55C00U))
#define		REG_ECC_MECCCAP_DMDA1			(*(volatile Reg_Ecc_MeccCap_Dmda1Type	   *)(0xFFC55E00U))

#define		REG_ECC_E9RS00					(*(volatile Reg_Ecc_Ecc9Type			   *)(0xFFF5B600U))
#define		REG_ECC_E9RS01					(*(volatile Reg_Ecc_Ecc9Type			   *)(0xFFF59000U))
#define		REG_ECC_E9RS02					(*(volatile Reg_Ecc_Ecc9Type			   *)(0xFFF59400U))
#define		REG_ECC_E9RS03					(*(volatile Reg_Ecc_Ecc9Type			   *)(0xFFF59600U))
#define		REG_ECC_E9RS04					(*(volatile Reg_Ecc_Ecc9Type			   *)(0xFFF5AA00U))
#define		REG_ECC_E9RS05					(*(volatile Reg_Ecc_Ecc9Type			   *)(0xFFF5AC00U))
#define		REG_ECC_E9RS06					(*(volatile Reg_Ecc_Ecc9Type			   *)(0xFFF5AE00U))
#define		REG_ECC_E9RS07					(*(volatile Reg_Ecc_Ecc9Type			   *)(0xFFF5B000U))
#define		REG_ECC_E9ES00					(*(volatile Reg_Ecc_Ecc9Type			   *)(0xFFF5D000U))
#define		REG_ECC_E9ES01					(*(volatile Reg_Ecc_Ecc9Type			   *)(0xFFF5D200U))
#define		REG_ECC_E9ES02					(*(volatile Reg_Ecc_Ecc9Type			   *)(0xFFF5D400U))
#define		REG_ECC_E9ES10					(*(volatile Reg_Ecc_Ecc9Type			   *)(0xFFF5F400U))
#define		REG_ECC_E9ES11					(*(volatile Reg_Ecc_Ecc9Type			   *)(0xFFF5F600U))
#define		REG_ECC_E9ES12					(*(volatile Reg_Ecc_Ecc9Type			   *)(0xFFF5F800U))

#define		REG_ECC_E8RS00					(*(volatile Reg_Ecc_Ecc8Type			   *)(0xFFF59E00U))
#define		REG_ECC_E8RS01					(*(volatile Reg_Ecc_Ecc8Type			   *)(0xFFF5A200U))
#define		REG_ECC_E8RS02					(*(volatile Reg_Ecc_Ecc8Type			   *)(0xFFF5A600U))
#define		REG_ECC_E8RS03					(*(volatile Reg_Ecc_Ecc8Type			   *)(0xFFF5A800U))
#define		REG_ECC_E8RS04					(*(volatile Reg_Ecc_Ecc8Type			   *)(0xFFF5B200U))
#define		REG_ECC_E8ES00					(*(volatile Reg_Ecc_Ecc8Type			   *)(0xFFF5CC00U))
#define		REG_ECC_E8ES01					(*(volatile Reg_Ecc_Ecc8Type			   *)(0xFFF5CE00U))
#define		REG_ECC_E8ES10					(*(volatile Reg_Ecc_Ecc8Type			   *)(0xFFF5F000U))
#define		REG_ECC_E8ES11					(*(volatile Reg_Ecc_Ecc8Type			   *)(0xFFF5F200U))

#define		REG_ECC_E7RC01					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFF860500U))
#define		REG_ECC_E7RC02					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFF860300U))
#define		REG_ECC_E7RC03					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFF860400U))
#define		REG_ECC_E7RC04					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFF860600U))
#define		REG_ECC_E7RC11					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFF860D00U))
#define		REG_ECC_E7RC12					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFF860B00U))
#define		REG_ECC_E7RC13					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFF860C00U))
#define		REG_ECC_E7RC14					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFF860E00U))
#define		REG_ECC_E7FR00					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFF0C0000U))
#define		REG_ECC_E7FR01					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFF0C0200U))
#define		REG_ECC_E7FR02					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFF0C0400U))
#define		REG_ECC_E7GT00					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFF50000U))
#define		REG_ECC_E7GT01					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFF50200U))
#define		REG_ECC_E7GT10					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFF50400U))
#define		REG_ECC_E7GT11					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFF50600U))
#define		REG_ECC_E7GT20					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFF50800U))
#define		REG_ECC_E7GT21					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFF50A00U))
#define		REG_ECC_E7GT30					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFF50C00U))
#define		REG_ECC_E7GT31					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFF50E00U))
#define		REG_ECC_E7GT40					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFF51000U))
#define		REG_ECC_E7GT41					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFF51200U))
#define		REG_ECC_E7GT50					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFF51400U))
#define		REG_ECC_E7GT51					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFF51600U))
#define		REG_ECC_E7GT60					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFF51800U))
#define		REG_ECC_E7GT61					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFF51A00U))
#define		REG_ECC_E7GT70					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFF51C00U))
#define		REG_ECC_E7GT71					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFF51E00U))
#define		REG_ECC_E7GT80					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFF52000U))
#define		REG_ECC_E7GT81					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFF52200U))
#define		REG_ECC_E7GT90					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFF52400U))
#define		REG_ECC_E7GT91					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFF52600U))
#define		REG_ECC_E7GT100					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFF52800U))
#define		REG_ECC_E7GT101					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFF52A00U))
#define		REG_ECC_E7GT102					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFF52C00U))
#define		REG_ECC_E7GT110					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFF52E00U))
#define		REG_ECC_E7GT111					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFF53000U))
#define		REG_ECC_E7GT112					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFF53200U))
#define		REG_ECC_E7MS00					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFC75700U))
#define		REG_ECC_E7MS01					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFD68700U))
#define		REG_ECC_E7MS02					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFC75800U))
#define		REG_ECC_E7MS03					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFD68800U))
#define		REG_ECC_E7MS04					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFC75900U))
#define		REG_ECC_E7MS05					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFD68900U))
#define		REG_ECC_E7MS06					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFC75A00U))
#define		REG_ECC_E7MS07					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFD68A00U))
#define		REG_ECC_E7MS08					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFC75B00U))
#define		REG_ECC_E7MS09					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFD68B00U))
#define		REG_ECC_E7MM00					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFD55200U))
#define		REG_ECC_E7MM01					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFD55300U))
#define		REG_ECC_E7ES00					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFF5C000U))
#define		REG_ECC_E7ES01					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFF5C200U))
#define		REG_ECC_E7ES02					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFF5C400U))
#define		REG_ECC_E7ES03					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFF5C600U))
#define		REG_ECC_E7ES04					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFF5C800U))
#define		REG_ECC_E7ES05					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFF5CA00U))
#define		REG_ECC_E7ES10					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFF5E400U))
#define		REG_ECC_E7ES11					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFF5E600U))
#define		REG_ECC_E7ES12					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFF5E800U))
#define		REG_ECC_E7ES13					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFF5EA00U))
#define		REG_ECC_E7ES14					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFF5EC00U))
#define		REG_ECC_E7ES15					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFF5EE00U))
#define		REG_ECC_E7RS00					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFF59200U))
#define		REG_ECC_E7RS03					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFF59C00U))
#define		REG_ECC_E7RS04					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFF5A000U))
#define		REG_ECC_E7RS05					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFF5A400U))
#define		REG_ECC_E7DF00					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFD8C100U))
#define		REG_ECC_E7DF10					(*(volatile Reg_Ecc_Ecc7Type			   *)(0xFFD74000U))

#define		REG_ECC_DFE0_DMEM0				(*(volatile Reg_Ecc_Ecc6Type			   *)(0xFFD8C120U))
#define		REG_ECC_DFE0_DMEM1				(*(volatile Reg_Ecc_Ecc6Type			   *)(0xFFD8C140U))
#define		REG_ECC_DFE1_DMEM0				(*(volatile Reg_Ecc_Ecc6Type			   *)(0xFFD74020U))
#define		REG_ECC_DFE1_DMEM1				(*(volatile Reg_Ecc_Ecc6Type			   *)(0xFFD74040U))
#define		REG_ECC_E6RS00					(*(volatile Reg_Ecc_Ecc6Type			   *)(0xFFF59800U))
#define		REG_ECC_E6RS01					(*(volatile Reg_Ecc_Ecc6Type			   *)(0xFFF59A00U))
#define		REG_ECC_E6RS02					(*(volatile Reg_Ecc_Ecc6Type			   *)(0xFFF5B400U))

#define		REG_ECC_ECCCNT_A_CCIB0CL0		(*(volatile Reg_Ecc_EccCnt_AType		   *)(0xFFC4B000U))
#define		REG_ECC_ECCCNT_A_CCIB1CL0		(*(volatile Reg_Ecc_EccCnt_AType		   *)(0xFFC4B080U))
#define		REG_ECC_ECCCNT_A_CCIB0CL1		(*(volatile Reg_Ecc_EccCnt_AType		   *)(0xFFC4B200U))
#define		REG_ECC_ECCCNT_A_CCIB1CL1		(*(volatile Reg_Ecc_EccCnt_AType		   *)(0xFFC4B280U))
#define		REG_ECC_ECCCNT_A_CCIB0CL2		(*(volatile Reg_Ecc_EccCnt_AType		   *)(0xFFC4B400U))
#define		REG_ECC_ECCCNT_A_CCIB1CL2		(*(volatile Reg_Ecc_EccCnt_AType		   *)(0xFFC4B480U))
#define		REG_ECC_ECCCNT_SA_PE0CL0		(*(volatile Reg_Ecc_EccCnt_AType		   *)(0xFFC4C000U))
#define		REG_ECC_ECCCNT_A_GCFU0CL0		(*(volatile Reg_Ecc_EccCnt_AType		   *)(0xFFC4C080U))
#define		REG_ECC_ECCCNT_SA_PE1CL0		(*(volatile Reg_Ecc_EccCnt_AType		   *)(0xFFC4C200U))
#define		REG_ECC_ECCCNT_A_GCFU1CL0		(*(volatile Reg_Ecc_EccCnt_AType		   *)(0xFFC4C280U))
#define		REG_ECC_ECCCNT_SA_PE2CL1		(*(volatile Reg_Ecc_EccCnt_AType		   *)(0xFFC4C400U))
#define		REG_ECC_ECCCNT_A_GCFU2CL1		(*(volatile Reg_Ecc_EccCnt_AType		   *)(0xFFC4C480U))
#define		REG_ECC_ECCCNT_SA_PE3CL1		(*(volatile Reg_Ecc_EccCnt_AType		   *)(0xFFC4C600U))
#define		REG_ECC_ECCCNT_A_GCFU3CL1		(*(volatile Reg_Ecc_EccCnt_AType		   *)(0xFFC4C680U))
#define		REG_ECC_ECCCNT_SA_PE4CL2		(*(volatile Reg_Ecc_EccCnt_AType		   *)(0xFFC4C800U))
#define		REG_ECC_ECCCNT_A_GCFU4CL2		(*(volatile Reg_Ecc_EccCnt_AType		   *)(0xFFC4C880U))
#define		REG_ECC_ECCCNT_SA_PE5CL2		(*(volatile Reg_Ecc_EccCnt_AType		   *)(0xFFC4CA00U))
#define		REG_ECC_ECCCNT_A_GCFU5CL2		(*(volatile Reg_Ecc_EccCnt_AType		   *)(0xFFC4CA80U))
#define		REG_ECC_ECCCNT_A_X2VCL0			(*(volatile Reg_Ecc_EccCnt_AType		   *)(0xFFC4D000U))
#define		REG_ECC_ECCCNT_A_X2VCL1			(*(volatile Reg_Ecc_EccCnt_AType		   *)(0xFFC4D080U))
#define		REG_ECC_ECCCNT_A_X2VCL2			(*(volatile Reg_Ecc_EccCnt_AType		   *)(0xFFC4D100U))
#define		REG_ECC_ECCCNT_A_BARR			(*(volatile Reg_Ecc_EccCnt_AType		   *)(0xFFC4D200U))
#define		REG_ECC_ECCCNT_A_IPIR			(*(volatile Reg_Ecc_EccCnt_AType		   *)(0xFFC4D280U))
#define		REG_ECC_ECCCNT_A_TPTM			(*(volatile Reg_Ecc_EccCnt_AType		   *)(0xFFC4D380U))
#define		REG_ECC_ECCCNT_A_CRAM			(*(volatile Reg_Ecc_EccCnt_AType		   *)(0xFFC4D400U))
#define		REG_ECC_ECCCNT_A_SG0			(*(volatile Reg_Ecc_EccCnt_AType		   *)(0xFFC4D480U))
#define		REG_ECC_ECCCNT_A_SX2PV			(*(volatile Reg_Ecc_EccCnt_AType		   *)(0xFFC4D500U))
#define		REG_ECC_ECCCNT_A_SX2FX			(*(volatile Reg_Ecc_EccCnt_AType		   *)(0xFFC4D580U))
#define		REG_ECC_ECCCNT_A_FX2SX			(*(volatile Reg_Ecc_EccCnt_AType		   *)(0xFFC4D600U))
#define		REG_ECC_ECCCNT_A_EX2FX			(*(volatile Reg_Ecc_EccCnt_AType		   *)(0xFFC4D800U))
#define		REG_ECC_ECCCNT_A_GCFUE			(*(volatile Reg_Ecc_EccCnt_AType		   *)(0xFFC4D880U))
#define		REG_ECC_ECCCNT_A_GCFUF			(*(volatile Reg_Ecc_EccCnt_AType		   *)(0xFFC4D680U))
#define		REG_ECC_ECCCNT_A_SX2MB			(*(volatile Reg_Ecc_EccCnt_AType		   *)(0xFFC4D700U))
#define		REG_ECC_ECCCNT_A_V2A1			(*(volatile Reg_Ecc_EccCnt_AType		   *)(0xFFC63800U))
#define		REG_ECC_ECCCNT_A_V2A2			(*(volatile Reg_Ecc_EccCnt_AType		   *)(0xFFDE0000U))
#define		REG_ECC_ECCCNT_A_V2A3			(*(volatile Reg_Ecc_EccCnt_AType		   *)(0xFFC72000U))
#define		REG_ECC_ECCCNT_A_V2A4			(*(volatile Reg_Ecc_EccCnt_AType		   *)(0xFFC74000U))
#define		REG_ECC_ECCCNT_A_V2A5			(*(volatile Reg_Ecc_EccCnt_AType		   *)(0xFFC79000U))
#define		REG_ECC_ECCCNT_A_V2A6			(*(volatile Reg_Ecc_EccCnt_AType		   *)(0xFFC80000U))
#define		REG_ECC_ECCCNT_A_V2A7			(*(volatile Reg_Ecc_EccCnt_AType		   *)(0xFFF48000U))
#define		REG_ECC_ECCCNT_A_V2A8			(*(volatile Reg_Ecc_EccCnt_AType		   *)(0xFFF28000U))
#define		REG_ECC_ECCCNT_A_V2A9			(*(volatile Reg_Ecc_EccCnt_AType		   *)(0xFF0A0000U))
#define		REG_ECC_ECCCNT_A_V2A10			(*(volatile Reg_Ecc_EccCnt_AType		   *)(0xFF878000U))
#define		REG_ECC_ECCCNT_A_V2A11			(*(volatile Reg_Ecc_EccCnt_AType		   *)(0xFF8B0000U))
#define		REG_ECC_DFP_ECCCNT_BUSA_FNT		(*(volatile Reg_Ecc_EccCnt_AType		   *)(0xFF0C6200U))
#define		REG_ECC_ECCCNT_D_V2XWCL0		(*(volatile Reg_Ecc_EccCnt_D_V2XwCl0Type   *)(0xFFC4E000U))
#define		REG_ECC_ECCCNT_D_V2XRCL0		(*(volatile Reg_Ecc_EccCnt_D_V2XrCl0Type   *)(0xFFC4E080U))
#define		REG_ECC_ECCCNT_D_V2XWCL1		(*(volatile Reg_Ecc_EccCnt_D_V2XwCl1Type   *)(0xFFC4E100U))
#define		REG_ECC_ECCCNT_D_V2XRCL1		(*(volatile Reg_Ecc_EccCnt_D_V2XrCl1Type   *)(0xFFC4E180U))
#define		REG_ECC_ECCCNT_D_V2XWCL2		(*(volatile Reg_Ecc_EccCnt_D_V2XwCl2Type   *)(0xFFC4E200U))
#define		REG_ECC_ECCCNT_D_V2XRCL2		(*(volatile Reg_Ecc_EccCnt_D_V2XrCl2Type   *)(0xFFC4E280U))
#define		REG_ECC_ECCCNT_D_PV2APBW		(*(volatile Reg_Ecc_EccCnt_D_Pv2ApbwType   *)(0xFFC4E400U))
#define		REG_ECC_ECCCNT_D_CRAM			(*(volatile Reg_Ecc_EccCnt_D_CramType	   *)(0xFFC4E500U))
#define		REG_ECC_ECCCNT_D_EMU			(*(volatile Reg_Ecc_EccCnt_D_EmuType	   *)(0xFFC4E580U))
#define		REG_ECC_ECCCNT_D_DMDE0			(*(volatile Reg_Ecc_EccCnt_D_Dmde0Type	   *)(0xFFC4E600U))
#define		REG_ECC_ECCCNT_D_DMDE1			(*(volatile Reg_Ecc_EccCnt_D_Dmde1Type	   *)(0xFFC4E680U))
#define		REG_ECC_ECCCNT_C_DMR0			(*(volatile Reg_Ecc_EccCnt_C_Dmr0Type	   *)(0xFFC4E800U))
#define		REG_ECC_ECCCNT_C_DMW0			(*(volatile Reg_Ecc_EccCnt_C_Dmw0Type	   *)(0xFFC4E880U))
#define		REG_ECC_ECCCNT_C_DMR1			(*(volatile Reg_Ecc_EccCnt_C_Dmr1Type	   *)(0xFFC4E900U))
#define		REG_ECC_ECCCNT_C_DMW1			(*(volatile Reg_Ecc_EccCnt_C_Dmw1Type	   *)(0xFFC4E980U))
#define		REG_ECC_ECCCNT_SD_PE0CL0		(*(volatile Reg_Ecc_EccCnt_Sd_Pe0Cl0Type   *)(0xFFC4F000U))
#define		REG_ECC_ECCCNT_MD_PE0CL0		(*(volatile Reg_Ecc_EccCnt_Md_Pe0Cl0Type   *)(0xFFC4F080U))
#define		REG_ECC_ECCCNT_SD_PE1CL0		(*(volatile Reg_Ecc_EccCnt_Sd_Pe1Cl0Type   *)(0xFFC4F100U))
#define		REG_ECC_ECCCNT_MD_PE1CL0		(*(volatile Reg_Ecc_EccCnt_Md_Pe1Cl0Type   *)(0xFFC4F180U))
#define		REG_ECC_ECCCNT_SD_PE2CL1		(*(volatile Reg_Ecc_EccCnt_Sd_Pe2Cl1Type   *)(0xFFC4F200U))
#define		REG_ECC_ECCCNT_MD_PE2CL1		(*(volatile Reg_Ecc_EccCnt_Md_Pe2Cl1Type   *)(0xFFC4F280U))
#define		REG_ECC_ECCCNT_SD_PE3CL1		(*(volatile Reg_Ecc_EccCnt_Sd_Pe3Cl1Type   *)(0xFFC4F300U))
#define		REG_ECC_ECCCNT_MD_PE3CL1		(*(volatile Reg_Ecc_EccCnt_Md_Pe3Cl1Type   *)(0xFFC4F380U))
#define		REG_ECC_ECCCNT_SD_PE4CL2		(*(volatile Reg_Ecc_EccCnt_Sd_Pe4Cl2Type   *)(0xFFC4F400U))
#define		REG_ECC_ECCCNT_MD_PE4CL2		(*(volatile Reg_Ecc_EccCnt_Md_Pe4Cl2Type   *)(0xFFC4F480U))
#define		REG_ECC_ECCCNT_SD_PE5CL2		(*(volatile Reg_Ecc_EccCnt_Sd_Pe5Cl2Type   *)(0xFFC4F500U))
#define		REG_ECC_ECCCNT_MD_PE5CL2		(*(volatile Reg_Ecc_EccCnt_Md_Pe5Cl2Type   *)(0xFFC4F580U))
#define		REG_ECC_ECCCNT_D_BARR			(*(volatile Reg_Ecc_EccCnt_D_BarrType	   *)(0xFFC4F800U))
#define		REG_ECC_ECCCNT_D_IPIR			(*(volatile Reg_Ecc_EccCnt_D_IpirType	   *)(0xFFC4F880U))
#define		REG_ECC_ECCCNT_D_TPTM			(*(volatile Reg_Ecc_EccCnt_D_TptmType	   *)(0xFFC4F980U))
#define		REG_ECC_ECCCNT_D_DTS			(*(volatile Reg_Ecc_EccCnt_D_DtsType	   *)(0xFFC4FA00U))
#define		REG_ECC_ECCCNT_D_DMA0			(*(volatile Reg_Ecc_EccCnt_D_Dma0Type	   *)(0xFFC4FB00U))
#define		REG_ECC_ECCCNT_D_DMA1			(*(volatile Reg_Ecc_EccCnt_D_Dma1Type	   *)(0xFFC4FB80U))
#define		REG_ECC_ECCCNT_D_V2A1W			(*(volatile Reg_Ecc_EccCnt_D_V2AnWType	   *)(0xFFC63900U))
#define		REG_ECC_ECCCNT_D_V2A2W			(*(volatile Reg_Ecc_EccCnt_D_V2AnWType	   *)(0xFFDE0100U))
#define		REG_ECC_ECCCNT_D_V2A3W			(*(volatile Reg_Ecc_EccCnt_D_V2AnWType	   *)(0xFFC72100U))
#define		REG_ECC_ECCCNT_D_V2A4W			(*(volatile Reg_Ecc_EccCnt_D_V2AnWType	   *)(0xFFC74100U))
#define		REG_ECC_ECCCNT_D_V2A5W			(*(volatile Reg_Ecc_EccCnt_D_V2AnWType	   *)(0xFFC79100U))
#define		REG_ECC_ECCCNT_D_V2A6W			(*(volatile Reg_Ecc_EccCnt_D_V2AnWType	   *)(0xFFC80100U))
#define		REG_ECC_ECCCNT_D_V2A7W			(*(volatile Reg_Ecc_EccCnt_D_V2AnWType	   *)(0xFFF48400U))
#define		REG_ECC_ECCCNT_D_V2A8W			(*(volatile Reg_Ecc_EccCnt_D_V2AnWType	   *)(0xFFF28400U))
#define		REG_ECC_ECCCNT_D_V2A9W			(*(volatile Reg_Ecc_EccCnt_D_V2AnWType	   *)(0xFF0A0200U))
#define		REG_ECC_ECCCNT_D_V2A10W			(*(volatile Reg_Ecc_EccCnt_D_V2AnWType	   *)(0xFF878400U))
#define		REG_ECC_ECCCNT_D_V2A11W			(*(volatile Reg_Ecc_EccCnt_D_V2AnWType	   *)(0xFF8B0400U))
#define		REG_ECC_DFP_ECCCNT_BUSD_ROM		(*(volatile Reg_Ecc_Dfp_EccCnt_Busd_RomType *)(0xFF0C6300U))
#define		REG_ECC_DFP_ECCCNT_BUSD_SYS		(*(volatile Reg_Ecc_Dfp_EccCnt_Busd_SysType *)(0xFF0C6400U))
#define		REG_ECC_DFP_ECCCNT_BUSD_FNT		(*(volatile Reg_Ecc_Dfp_EccCnt_Busd_FntType *)(0xFF0C6500U))
#define		REG_ECC_BECCCAP_LRAM			(*(volatile Reg_Ecc_BeccCap_LramType	   *)(0xFFC50000U))
#define		REG_ECC_BECCCAP_CRAM			(*(volatile Reg_Ecc_BeccCap_CramType	   *)(0xFFC50100U))
#define		REG_ECC_BECCCAP_CFL				(*(volatile Reg_Ecc_BeccCap_CflType		   *)(0xFFC50300U))
#define		REG_ECC_BECCCAP_PERI			(*(volatile Reg_Ecc_BeccCap_PeriType	   *)(0xFFC50400U))
#define		REG_ECC_BECCCAP_DMDT			(*(volatile Reg_Ecc_BeccCap_DmdtType	   *)(0xFFC50500U))
#define		REG_ECC_BECCCAP_EMU				(*(volatile Reg_Ecc_BeccCap_EmuType		   *)(0xFFC50800U))
#define		REG_ECC_PB1ECC					(*(volatile Reg_Ecc_PbnEccType			   *)(0xFFC62F60U))
#define		REG_ECC_PB2ECC					(*(volatile Reg_Ecc_PbnEccType			   *)(0xFFDE0900U))
#define		REG_ECC_PB3ECC					(*(volatile Reg_Ecc_PbnEccType			   *)(0xFFC72900U))
#define		REG_ECC_PB4ECC					(*(volatile Reg_Ecc_PbnEccType			   *)(0xFFC75100U))
#define		REG_ECC_PB5ECC					(*(volatile Reg_Ecc_PbnEccType			   *)(0xFFC7A100U))
#define		REG_ECC_PB6ECC					(*(volatile Reg_Ecc_PbnEccType			   *)(0xFFC81100U))
#define		REG_ECC_PB7ECC					(*(volatile Reg_Ecc_PbnEccType			   *)(0xFFF49100U))
#define		REG_ECC_PB8ECC					(*(volatile Reg_Ecc_PbnEccType			   *)(0xFFF29100U))
#define		REG_ECC_PB9ECC					(*(volatile Reg_Ecc_PbnEccType			   *)(0xFF0A1100U))
#define		REG_ECC_PB10ECC					(*(volatile Reg_Ecc_PbnEccType			   *)(0xFF879100U))
#define		REG_ECC_PB11ECC					(*(volatile Reg_Ecc_PbnEccType			   *)(0xFF8B1100U))
#define		REG_ECC_HB90MECC				(*(volatile Reg_Ecc_HbnEccType			   *)(0xFF0C3000U))
#define		REG_ECC_HB90SECC				(*(volatile Reg_Ecc_HbnEccType			   *)(0xFF0C3400U))
#define		REG_ECC_HB91MECC				(*(volatile Reg_Ecc_HbnEccType			   *)(0xFF0C3C00U))
#define		REG_ECC_HB91SECC				(*(volatile Reg_Ecc_HbnEccType			   *)(0xFF0C4000U))
#define		REG_ECC_HB92MECC				(*(volatile Reg_Ecc_HbnEccType			   *)(0xFF0C0C00U))
#define		REG_ECC_HB92SECC				(*(volatile Reg_Ecc_HbnEccType			   *)(0xFF0C1000U))
#define		REG_ECC_HB94SECC				(*(volatile Reg_Ecc_HbnEccType			   *)(0xFF0C3800U))
#define		REG_ECC_HB97MECC				(*(volatile Reg_Ecc_HbnEccType			   *)(0xFF0C4800U))
#define		REG_ECC_HB98MECC				(*(volatile Reg_Ecc_HbnEccType			   *)(0xFFF5D600U))
#define		REG_ECC_HB99MECC				(*(volatile Reg_Ecc_HbnEccType			   *)(0xFFF5D800U))
#define		REG_ECC_HB910MECC				(*(volatile Reg_Ecc_HbnEccType			   *)(0xFFF5DA00U))
#define		REG_ECC_HB911MECC				(*(volatile Reg_Ecc_HbnEccType			   *)(0xFF0C4C00U))
#define		REG_ECC_HB912MECC				(*(volatile Reg_Ecc_HbnEccType			   *)(0xFF0C5000U))
#define		REG_ECC_BECCCAP_V2A1			(*(volatile Reg_Ecc_BeccCap_V2AnType	   *)(0xFFC63A00U))
#define		REG_ECC_BECCCAP_V2A2			(*(volatile Reg_Ecc_BeccCap_V2AnType	   *)(0xFFDE0200U))
#define		REG_ECC_BECCCAP_V2A3			(*(volatile Reg_Ecc_BeccCap_V2AnType	   *)(0xFFC72200U))
#define		REG_ECC_BECCCAP_V2A4			(*(volatile Reg_Ecc_BeccCap_V2AnType	   *)(0xFFC74200U))
#define		REG_ECC_BECCCAP_V2A5			(*(volatile Reg_Ecc_BeccCap_V2AnType	   *)(0xFFC79200U))
#define		REG_ECC_BECCCAP_V2A6			(*(volatile Reg_Ecc_BeccCap_V2AnType	   *)(0xFFC80200U))
#define		REG_ECC_BECCCAP_V2A7			(*(volatile Reg_Ecc_BeccCap_V2AnType	   *)(0xFFF48800U))
#define		REG_ECC_BECCCAP_V2A8			(*(volatile Reg_Ecc_BeccCap_V2AnType	   *)(0xFFF28800U))
#define		REG_ECC_BECCCAP_V2A9			(*(volatile Reg_Ecc_BeccCap_V2AnType	   *)(0xFF0A0400U))
#define		REG_ECC_BECCCAP_V2A10			(*(volatile Reg_Ecc_BeccCap_V2AnType	   *)(0xFF878800U))
#define		REG_ECC_BECCCAP_V2A11			(*(volatile Reg_Ecc_BeccCap_V2AnType	   *)(0xFF8B0800U))
#define		REG_ECC_DFP_ECCCAP_ROM			(*(volatile Reg_Ecc_Dfp_EccCap_RomType	   *)(0xFF0C6600U))
#define		REG_ECC_DFP_ECCCAP_SYS			(*(volatile Reg_Ecc_Dfp_EccCap_SysType	   *)(0xFF0C6800U))
#define		REG_ECC_DFP_ECCCAP_FNT			(*(volatile Reg_Ecc_Dfp_EccCap_FntType	   *)(0xFF0C6A00U))
#define		REG_ECC_DFP_KCPROT				(*(volatile Reg_Ecc_Dfp_KcProtType		   *)(0xFF0C6F00U))


#define		REG_ECC_ERRGEN					(*(volatile Reg_Ecc_ErrgenType			   *)(0xFFC58400U))

extern	volatile Reg_Ecc_Ecc7Type* const pcstReg_Ecc7[];
extern	volatile Reg_Ecc_Ecc6Type* const pcstReg_Ecc6[];
extern	volatile Reg_Ecc_EccCnt_AType* const pcstReg_A[];
extern	volatile Reg_Ecc_EccCnt_D_V2AnWType* const pcstReg_V2AnW[];
extern	volatile Reg_Ecc_PbnEccType* const pcstReg_PbnEcc[];
extern	volatile Reg_Ecc_HbnEccType* const pcstReg_HbnEcc[];
extern	volatile Reg_Ecc_BeccCap_V2AnType* const pcstReg_V2an[];


#endif /* REG_ECC_H */
#endif // zantei ECCは2月末非対応
/*-- End Of File -------------------------------------------------------------------------------*/
