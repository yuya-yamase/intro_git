/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2023 CRI Middleware Co., Ltd.
 *
 * Appli.   : CRI Sample Program
 * Module   : definition of registers
 * File     : def_reg.h
 *
 ****************************************************************************/
#if		!defined(__DEF_REG_H__)
#define __DEF_REG_H__

/***************************************************************************
 *		インクルードファイル
 *		Include file
 ***************************************************************************/
#include <cri_xpt.h>

#if defined(__cplusplus)
extern "C" {
#endif	/* defined(__cplusplus) */
/***************************************************************************
 *		定数マクロ
 *		Constant Macro
 ***************************************************************************/

/***************************************************************************
 *      処理マクロ
 *      Macro Functions
 ***************************************************************************/

/***************************************************************************
 *      データ型宣言
 *      Data Type Declarations
 ***************************************************************************/
/* 8-bit register */
typedef struct Reg8Tag {
	CriUint8	U8;
} Reg8;

/* 16-bit register */
typedef struct Reg16Tag {
	CriUint16	U16;
} Reg16;

/* 32-bit register */
typedef struct Reg32Tag {
	CriUint32	U32;
} Reg32;

/* Struct for definition 32-bit register (8-bit access type) */
typedef struct Reg32T8Tag {
	CriUint8	U8;				/* [+0x00] register */
	CriUint8	padding1;
	CriUint8	padding2;
	CriUint8	padding3;
} Reg32T8;

/* Struct for definition 32-bit register (16-bit access type) */
typedef struct Reg32T16Tag {
	CriUint16	U16;			/* [+0x00] register */
	CriUint16	padding2;
} Reg32T16;

/* PBG error Registers */
typedef struct RegPbgErrslvnTag {
	/* [+0x00] */
	Reg32		PBGOVFCLR;			/* Guard error overflow clear register */
	Reg32		PBGOVFSTAT;			/* Guard error overflow status register */
	Reg32		PBGERRADDR;			/* Guard error address register */
	Reg32		PBGERRTYPE;			/* Guard error access information register */
	Reg32		PBGSPIDERRCLR;		/* Guard SPID error clear register */
	Reg32		PBGSPIDERRSTAT;		/* Guard SPID error status register */
	Reg32		PBGKCPROT;			/* Key code protection register */
} RegPbgErrslvn;

/* PBG channel Registers */
typedef struct RegPbgChannelTag {
	/* [+0x00] */
	Reg32		PBGPROT0_0;			/* Channel 0 protection control register*/
	Reg32		PBGPROT1_0;			/* Channel 0 SPID setting register */
	Reg32		PBGPROT0_1;
	Reg32		PBGPROT1_1;
	Reg32		PBGPROT0_2;
	Reg32		PBGPROT1_2;
	Reg32		PBGPROT0_3;
	Reg32		PBGPROT1_3;
	Reg32		PBGPROT0_4;
	Reg32		PBGPROT1_4;
	Reg32		PBGPROT0_5;
	Reg32		PBGPROT1_5;
	Reg32		PBGPROT0_6;
	Reg32		PBGPROT1_6;
	Reg32		PBGPROT0_7;
	Reg32		PBGPROT1_7;
	Reg32		PBGPROT0_8;
	Reg32		PBGPROT1_8;
	Reg32		PBGPROT0_9;
	Reg32		PBGPROT1_9;
	Reg32		PBGPROT0_10;
	Reg32		PBGPROT1_10;
	Reg32		PBGPROT0_11;
	Reg32		PBGPROT1_11;
	Reg32		PBGPROT0_12;
	Reg32		PBGPROT1_12;
	Reg32		PBGPROT0_13;
	Reg32		PBGPROT1_13;
	Reg32		PBGPROT0_14;
	Reg32		PBGPROT1_14;
	Reg32		PBGPROT0_15;
	Reg32		PBGPROT1_15;
} RegPbgChannel;

/* DMA Global Register */
/* j:unit, n:Channel, m:trigger group */
typedef struct RegSdmacGlobalTag {
	/* [+0x00] */
	Reg8		padding0[0x10];
	Reg32		DMAjESTA;			/* DMA address error interrupt status register */
	Reg8		padding14[0xC];
	Reg32		DMAjISTA;			/* DMA channel interrupt status register */
	Reg8		padding24[0x1C];
	Reg32		DMAjCHPRI;			/* DMA channel request priority register */
	Reg8		padding44[0x1C];
	Reg16		DMAjOR;				/* DMA operation register */
	Reg8		padding62[0x1E];
	Reg32		DMAjCHRST;			/* DMA channel reset register */
	Reg8		padding84[0x7C];
	/* [+0x100] */
	Reg32		DMAjCM_n[16];		/* DMA channel master setting register */
	Reg8		padding140[0x1EC0];
} RegSdmacGlobal;

/* DMA Channel Registers */
typedef struct RegSdmacChannelTag {
	/* [+0x00] */
	Reg32		DMAjSAR;			/* DMA source address register */
	/* [+0x04] */
	Reg32		DMAjDAR;			/* DMA destination address register */
	/* [+0x08] */
	Reg32		DMAjTSR;			/* DMA transfer size register */
	/* [+0x0C] */
	Reg32		DMAjTSRB;			/* DMA transfer size register B */
	/* [+0x10] */
	Reg32		DMAjTMR;			/* DMA transfer mode register */
	/* [+0x14] */
	Reg16		DMAjCHCR;			/* DMA channel control register */
	/* [+0x16] */
	Reg16		DMAjCHSTP;			/* DMA channel suspend register */
	/* [+0x18] */
	Reg32		DMAjCHSTA;			/* DMA channel status register */
	/* [+0x1C] */
	Reg32		DMAjCHFCR;			/* DMA channel flag clear register */
	/* [+0x20] */
	Reg32		DMAjGIAI;			/* DMA gather inner address increment register */
	/* [+0x24] */
	Reg32		DMAjGOAI;			/* DMA gather outer address increment register */
	/* [+0x28] */
	Reg32		DMAjSIAI;			/* DMA scatter inner address increment register */
	/* [+0x2C] */
	Reg32		DMAjSOAI;			/* DMA scatter outer address increment register */
	Reg8		padding30[0x8];
	/* [+0x38] */
	Reg32		DMAjSGST;			/* DMA scatter gather status register */
	/* [+0x3C] */
	Reg32		DMAjSGCR;			/* DMA scatter gather control register */
	/* [+0x40] */
	Reg32		DMAjRS;				/* DMA resource select register */
	Reg8		padding44[0x4];
	/* [+0x48] */
	Reg32		DMAjBUFCR;			/* DMA buffer control registers */
	Reg8		padding4C[0x4];
	/* [+0x50] */
	Reg32		DMAjDPPTR;			/* DMA descriptor pointer register */
	/* [+0x54] */
	Reg32		DMAjDPCR;			/* DMA descriptor control register */
	Reg8		padding58[0x28];
	/* [+0x80] */
} RegSdmacChannel;

typedef struct RegSdmacTag {
	RegSdmacGlobal	global;
	RegSdmacChannel	channel[16];
} RegSdmac;

/* Descriptor Memory */
typedef struct RegDescriptorMemoryTag {
	/* [+0x00] */
	Reg32		DESCRIPTOR[1024];		/* Descriptor Memory */
} RegDescriptorMemory;

/* TAUDn Registers */
/* n:Register group, m:Channel */
typedef struct RegTaudTag {
	/* [+0x00] */
	Reg32T16		TAUDnCDRm[16];		/* TAUDn Channel Data Register m */
	/* [+0x40] */
	Reg16		TAUDnTOL;			/* TAUDn Channel Output Active Level Register */
	Reg8		padding42[2];
	/* [+0x44] */
	Reg16		TAUDnRDT;			/* TAUDn Channel Reload Data Trigger Register */
	Reg8		padding46[2];
	/* [+0x48] */
	Reg16		TAUDnRSF;			/* TAUDn Channel Reload Status Register */
	Reg8		padding4A[2];
	/* [+0x4C] */
	Reg16		TAUDnTRO;			/* TAUDn Channel Real-time Output Register */
	Reg8		padding4E[2];
	/* [+0x50] */
	Reg16		TAUDnTME;			/* TAUDn Channel Modulation Output Enable Register */
	Reg8		padding52[2];
	/* [+0x54] */
	Reg16		TAUDnTDL;			/* TAUDn Channel Dead Time Output Level Register */
	Reg8		padding56[2];
	/* [+0x58] */
	Reg16		TAUDnTO;			/* TAUDn Channel Output Register */
	Reg8		padding5A[2];
	/* [+0x5C] */
	Reg16		TAUDnTOE;			/* TAUDn Channel Output Enable Register */
	Reg8		padding5E[0x22];
	/* [+0x80] */
	Reg32T16	TAUDnCNTm[16];		/* TAUDn Channel Counter Register m */
	/* [+0xC0] */
	Reg32T8		TAUDnCMURm[16];		/* TAUDn Channel Mode User Register m */
	Reg8		padding[0x40];
	/* [+0x140] */
	Reg32T8		TAUDnCSRm[16];		/* TAUDn Channel Status Register m */
	/* [+0x180] */
	Reg32T8		TAUDnCSCm[16];		/* TAUDn Channel Status Clear Trigger Register m  */
	/* [+0x1C0] */
	Reg16		TAUDnTE;			/* TAUDn Channel Enable Status Register */
	Reg8		paddnig1C2[2];
	/* [+0x1C4] */
	Reg16		TAUDnTS;			/* TAUDn Channel Start Trigger Register */
	Reg8		padding1C6[2];
	/* [+0x1C8] */
	Reg16		TAUDnTT;			/* TAUDn Channel Stop Trigger Register */
	Reg8		padding1CA[0x36];
	/* [+0x200] */
	Reg32T16	TAUDnCMORm[16];		/* TAUDn Channel Mode OS Register m */
	/* [+0x240] */
	Reg16		TAUDnTPS;			/*  TAUDn Prescaler Clock Select Register */
	Reg8		padding242[2];
	/* [+0x244] */
	Reg8		TAUDnBRS;			/* TAUDn Prescaler Baud Rate Setting Register */
	Reg8		padding245[3];
	/* [+0x248] */
	Reg16		TAUDnTOM;			/* TAUDn Channel Output Mode Register */
	Reg8		padding24A[2];
	/* [+0x24C] */
	Reg16		TAUDnTOC;			/* TAUDn Channel Output Configuration Register */
	Reg8		padding24E[2];
	/* [0x250] */
	Reg16		TAUDnTDE;			/* TAUDn Channel Dead Time Output Enable Register */
	Reg8		padding252[2];
	/* [+0x254] */
	Reg16		TAUDnTDM;			/*TAUDn Channel Dead Time Output Mode Register*/
	Reg8		padding256[2];
	/* [+0x258] */
	Reg16		TAUDnTRE;			/* TAUDn Channel Real-time Output Enable Registe */
	Reg8		padding25A[2];
	/* [+0x25C] */
	Reg16		TAUDnTRC;			/* TAUDn Channel Real-time Output Control Register */
	Reg8		padding25E[2];
	/* [+0x260] */
	Reg16		TAUDnRDE;			/* TAUDn Channel Reload Data Enable Register */
	Reg8		padding262[2];
	/* [+0x264] */
	Reg16		TAUDnRDM;			/* TAUDn Channel Reload Data Mode Register */
	Reg8		padding266[2];
	/* [+0x268] */
	Reg16		TAUDnRDS;			/* TAUDn Channel Reload Data Control Channel Select Register */
	Reg8		padding26A[2];
	/* [+0x26C] */
	Reg16		TAUDnRDC;			/* TAUDn Channel Reload Data Control Register */
} RegTaud;

/* TAUJn Registers */
/* n:Register group, m:Channel */
typedef struct RegTaujTag {
	/* [+0x00] */
	Reg32		TAUJnCDRm[4];		/* TAUJn Channel Data Register m */
	/* [+0x10] */
	Reg32		TAUJnCNTm[4];		/* TAUJn Channel Counter Register m */
	/* [+0x20] */
	Reg8		TAUJnCMURm[4];		/* TAUJn Channel Mode User Register m */
	Reg8		padding24[0xc];
	/* [+0x30] */
	Reg8		TAUJnCSRm[4];		/* TAUJn Channel Status Register m */
	Reg8		padding34[0xc];
	/* [+0x40] */
	Reg8		TAUJnCSCm[4];		/* TAUJn Channel Status Clear Trigger Register m  */
	Reg8		padding44[0xc];
	/* [+0x50] */
	Reg8		TAUJnTE;			/* TAUJn Channel Enable Status Register */
	Reg8		padding51[3];
	/* [+0x54] */
	Reg8		TAUJnTS;			/* TAUJn Channel Start Trigger Register */
	Reg8		padding55[3];
	/* [+0x58] */
	Reg8		TAUJnTT;			/* TAUJn Channel Stop Trigger Register */
	Reg8		padding59[3];
	/* [+0x5c] */
	Reg8		TAUJnTO;			/* TAUJn Channel Output Register */
	Reg8		padding5d[3];
	/* [+0x60] */
	Reg8		TAUJnTOE;			/* TAUJn Channel Output Enable Register */
	Reg8		padding61[3];
	/* [+0x64] */
	Reg8		TAUJnTOL;			/* TAUJn Channel Output Active Level Register */
	Reg8		paddding65[3];
	/* [+0x68] */
	Reg8		TAUJnRDT;			/* TAUJn Channel Reload Data Trigger Register */
	Reg8		padding69[3];
	/* [+0x6c] */
	Reg8		TAUJnRSF;			/* TAUJn Channel Reload Status Register */
	Reg8		padding6d[0x13];
	/* [+0x80] */
	Reg16		TAUJnCMORm[4];		/* TAUJn Channel Mode OS Register m */
	Reg8		padding88[8];
	/* [+0x90] */
	Reg16		TAUJnTPS;			/*  TAUDn Prescaler Clock Select Register */
	Reg8		padding92[2];
	/* [+0x94] */
	Reg8		TAUJnBRS;			/* TAUJn Prescaler Baud Rate Setting Register */
	Reg8		padding95[3];
	/* [+0x98] */
	Reg8		TAUJnTOM;			/* TAUJn Channel Output Mode Register */
	Reg8		padding99[3];
	/* [+0x9c] */
	Reg8		TAUJnTOC;			/* TAUJn Channel Output Configuration Register */
	Reg8		padding9d[3];
	/* [+0xa0] */
	Reg8		TAUJnRDE;			/* TAUJn Channel Reload Data Enable Register */
	Reg8		paddingA1[3];
	/* [+0xa4] */
	Reg8		TAUJnRDM;			/* TAUJn Channel Reload Data Mode Register */
} RegTauj;

/* Registers Peripheral Guard */
#pragma ghs io REG_PBGERRSLV50		0xFFC7B000U		/* For PBG51 */
extern volatile RegPbgErrslvn REG_PBGERRSLV50;
#pragma ghs io REG_PBG51			0xFFC7A400U		/* For TAUD */
extern volatile RegPbgChannel REG_PBG51;

/* Registers sDMAC */
#pragma ghs io REG_DMAC					0xFFF98000U		/* Group SDMAC1 */
extern volatile RegSdmac REG_DMAC;
#pragma ghs io REG_DESCRIPTOR			0xFFF9C000U
extern volatile RegDescriptorMemory REG_DESCRIPTOR;

/* Registers TAUD */
#pragma ghs io REG_TAUD1			0xFFBF5000U
extern volatile RegTaud REG_TAUD1;

/* Registers TAUJ */
#pragma ghs io REG_TAUJ0			0xFFBF7000U
extern volatile RegTauj REG_TAUJ0;

#if defined(__cplusplus)
}	/* extern "C" */
#endif	/* defined(__cplusplus) */

 #endif	/* !defined(__DEF_REG_H__) */
/*------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                          */
/*------------------------------------------------------------------------------------------------------*/
