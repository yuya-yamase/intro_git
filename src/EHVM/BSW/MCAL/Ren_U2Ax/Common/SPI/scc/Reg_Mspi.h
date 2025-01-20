/* Reg_Mspi-r04-3000-0100-a-v00 */
/************************************************************************************************/
/*																								*/
/*		MSPI register definition (for RH850U2B)													*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

#ifndef REG_MSPI_H
#define REG_MSPI_H

#include "Pf_Types.h"
#include "Mcal_CmnCfg.h"

/*==============================================================================================*/
/*	defines																						*/
/*==============================================================================================*/
#if ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A16_373PIN ) 
#define	MSPI_UNIT_NUM			(9)				/* MSPIユニット数 */
#elif ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A6_292PIN )
#define	MSPI_UNIT_NUM			(6)				/* MSPIユニット数 */
#else
#error "This chip is not supported!"
#endif
#define	MSPI_CH_NUM				(8)				/* ユニット内のチャネル数 */

#define	MSPI_TGCTLI_NUM			(0)				/* TGCTLiレジスタ数 */
#if ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A16_373PIN ) 
#define	MSPI_RAM_SIZE			(0x80)			/* MSPI RAMサイズ(バイト数) */
#elif ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A6_292PIN )
#define	MSPI_RAM_SIZE			(0x200)			/* MSPI RAMサイズ(バイト数) */
#else
#error "This chip is not supported!"
#endif

#define	MSPI_INTF_FACTOR_TX		(0)				/* INTF0(INTMSPInTX) */
#define	MSPI_INTF_FACTOR_RX		(1)				/* INTF1(INTMSPInRX) */
#define	MSPI_INTF_FACTOR_FE		(2)				/* INTF2(INTMSPInFE) */
#define	MSPI_INTF_FACTOR_ERR	(3)				/* INTF3(INTMSPInERR) */
#define	MSPI_INTF_FACTOR_NUM	(4)				/* INTFの要因数 */

/*==============================================================================================*/
/*	register type definition																	*/
/*==============================================================================================*/

/***************************/
/*          MSPIn          */
/***************************/
typedef	struct {
	union {
		U1	u1Data;
		struct {
			U1	xEN			:1;
			U1	b7Dummy1	:7;
		}stBit;
	}unCTL0;	/* 0x0000 */

	U1	u1Dummy1[0x0004 - 0x0001];

	union {
		U4	u4Data;
		struct {
			U4	b12CSP		:12;
			U4	b12Dummy1	:12;
			U4	b2SOLS		:2;
			U4	xDummy2		:1;
			U4	xCKR		:1;
			U4	xSAMP		:1;
			U4	xCSIE		:1;
			U4	xDummy3		:1;
			U4	xMSSEL		:1;
		}stBit;
	}unCTL1;	/* 0x0004 */

	union {
		U1	u1Data;
		struct {
			U1	xLBM		:1;
			U1	xDCS		:1;
			U1	b6Dummy1	:6;
		}stBit;
	}unCTL2;	/* 0x0008 */

	U1	u1Dummy2[0x0010 - 0x0009];

	union {
		U1	u1Data;
		struct {
			U1	xCSF		:1;
			U1	b3Dummy1	:3;
			U1	b4CNUMF		:4;
		}stBit;
	}unSTR0;	/* 0x0010 */

	U1	u1Dummy3[0x0080 - 0x0011];

	struct {
		union {
			U4	u4Data;
			struct {
				U4	xITXE		:1;
				U4	xIRXE		:1;
				U4	xIFEE		:1;
				U4	xIERE		:1;
				U4	b8Dummy1	:8;
				U4	xFCCE		:1;
				U4	b3Dummy2	:3;
				U4	xLOCK		:1;
				U4	b3Dummy3	:3;
				U4	b3PRIO		:3;
				U4	xDummy4		:1;
				U4	b2MD		:2;
				U4	b2Dummy5	:2;
				U4	xRXE		:1;
				U4	xTXE		:1;
				U4	b2Dummy6	:2;
			}stBit;
		}unCFG0;		/* 0x00 + ( 0x80 * (m+1) ) */

		union {
			U4	u4Data;
			struct {
				U4	xDECHK		:1;
				U4	b3Dummy1	:3;
				U4	b2PS		:2;
				U4	b2Dummy2	:2;
				U4	xSAFE		:1;
				U4	xSAFS		:1;
				U4	xDummy3		:1;
				U4	xSAFCM		:1;
				U4	b4Dummy4	:4;
				U4	xCSRI		:1;
				U4	xFIDL		:1;
				U4	xICLS		:1;
				U4	xDummy5		:1;
				U4	xDIR		:1;
				U4	b3Dummy6	:3;
				U4	xCPHA		:1;
				U4	xCPOL		:1;
				U4	b6Dummy7	:6;
			}stBit;
		}unCFG1;		/* 0x04 + ( 0x80 * (m+1) ) */

		union {
			U2	u2Data;
			struct {
				U2	b8FLEN		:8;
				U2	b8Dummy1	:8;
			}stBit;
		}unCFG2;		/* 0x08 + ( 0x80 * (m+1) ) */

		U1	u1Dummy4[0x0C - 0x0A];

		union {
			U2	u2Data;
			struct {
				U2	b5CDIV		:5;
				U2	b3Dummy1	:3;
				U2	b2PRCS		:2;
				U2	b6Dummy2	:6;
			}stBit;
		}unCFG3;		/* 0x0C + ( 0x80 * (m+1) ) */

		U1	u1Dummy5[0x10 - 0x0E];

		union {
			U4	u4Data;
			struct {
				U4	b2SIZE		:2;
				U4	b14Dummy1	:14;
				U4	b6HWTS		:6;
				U4	b10Dummy2	:10;
			}stBit;
		}unCFG4;		/* 0x10 + ( 0x80 * (m+1) ) */

		U1	u1Dummy6[0x18 - 0x14];

		union {
			U2	u2Data;
			struct {
				U2	b12SEUP		:12;
				U2	b4Dummy1	:4;
			}stBit;
		}unSEUP;		/* 0x18 + ( 0x80 * (m+1) ) */

		U1	u1Dummy7[0x1C - 0x1A];

		union {
			U2	u2Data;
			struct {
				U2	b12HOLD		:12;
				U2	b4Dummy1	:4;
			}stBit;
		}unHOLD;		/* 0x1C + ( 0x80 * (m+1) ) */

		U1	u1Dummy8[0x20 - 0x1E];

		union {
			U2	u2Data;
			struct {
				U2	b12IDLE		:12;
				U2	b4Dummy1	:4;
			}stBit;
		}unIDLE;		/* 0x20 + ( 0x80 * (m+1) ) */

		U1	u1Dummy9[0x24 - 0x22];

		union {
			U2	u2Data;
			struct {
				U2	b12INDA		:12;
				U2	b4Dummy1	:4;
			}stBit;
		}unINDA;		/* 0x24 + ( 0x80 * (m+1) ) */

		U1	u1Dummy10[0x28 - 0x26];

		union {
			U2	u2Data;
			struct {
				U2	b2Dummy1	:2;
				U2	b7RASTAD	:7;
				U2	b7Dummy2	:7;
			}stBit;
		}unRASTAD;		/* 0x28 + ( 0x80 * (m+1) ) */

		U1	u1Dummy11[0x2C - 0x2A];

		U2	u2CFSET;	/* 0x2C + ( 0x80 * (m+1) ) */

		U1	u1Dummy12[0x30 - 0x2E];

		union {
			U4	u4Data;
			struct {
				U4	b16TXDA0	:16;
				U4	b12CSR		:12;
				U4	b3Dummy1	:3;
				U4	xJOBEN		:1;
			}stBit;
		}unSSTX;		/* 0x30 + ( 0x80 * (m+1) ) */

		union {
			U1	u1Data;
			struct {
				U1	xCHENS		:1;
				U1	xACTFS		:1;
				U1	b6Dummy1	:6;
			}stBit;
		}unCSTS;		/* 0x34 + ( 0x80 * (m+1) ) */

		U1	u1Dummy13[0x38 - 0x35];

		union {
			U1	u1Data;
			struct {
				U1	xCHENC		:1;
				U1	b7Dummy1	:7;
			}stBit;
		}unCSTC;		/* 0x38 + ( 0x80 * (m+1) ) */

		U1	u1Dummy14[0x3C - 0x39];

		union {
			U2	u2Data;
			struct {
				U2	b12CSR		:12;
				U2	b3Dummy1	:3;
				U2	xJOBEN		:1;
			}stBit;
		}unSSEL;		/* 0x3C + ( 0x80 * (m+1) ) */

		U1	u1Dummy15[0x40 - 0x3E];

		union {
			U1	u1Data[4];		/*  8-bit Access */
			U2	u2Data[2];		/* 16-bit Access */
			U4	u4Data;			/* 32-bit Access */
		}unTXDA0;		/* 0x40 + ( 0x80 * (m+1) ) */

		U1	u1Dummy16[0x4C - 0x44];

		union {
			U1	u1Data;
			struct {
				U1	xPEFST		:1;
				U1	xCEFST		:1;
				U1	b2Dummy1	:2;
				U1	xDCEFST		:1;
				U1	b3Dummy2	:3;
			}stBit;
		}unFRERST;		/* 0x4C + ( 0x80 * (m+1) ) */

		U1	u1Dummy17[0x50 - 0x4D];

		union {
			U1	u1Data[4];		/*  8-bit Access */
			U2	u2Data[2];		/* 16-bit Access */
			U4	u4Data;			/* 32-bit Access */
		}unRXDA0;		/* 0x50 + ( 0x80 * (m+1) ) */

		U1	u1Dummy18[0x58 - 0x54];

		union {
			U2	u2Data;
			struct {
				U2	xCHEN		:1;
				U2	xACTF		:1;
				U2	b2Dummy1	:2;
				U2	xRXRQF		:1;
				U2	xTXRQF		:1;
				U2	b2Dummy2	:2;
				U2	b8FIRXN		:8;
			}stBit;
		}unCSTR;		/* 0x58 + ( 0x80 * (m+1) ) */

		U1	u1Dummy19[0x5C - 0x5A];

		struct {
			U2	u2CFCNT;
			U2	u2Dummy1;
		}stCFCNT;		/* 0x5C + ( 0x80 * (m+1) ) */

		union {
			U4	u4Data;
			struct {
				U4	b16RXDA0	:16;
				U4	xPEFST		:1;
				U4	xCEFST		:1;
				U4	b2Dummy1	:2;
				U4	xDEFST		:1;
				U4	b11Dummy2	:11;
			}stBit;
		}unFSRX;		/* 0x60 + ( 0x80 * (m+1) ) */

		union {
			U1	u1Data;
			struct {
				U1	xPEFSC		:1;
				U1	xCEFSC		:1;
				U1	b2Dummy1	:2;
				U1	xDCEFSC		:1;
				U1	b3Dummy2	:3;
			}stBit;
		}unFRERSTC;		/* 0x64 + ( 0x80 * (m+1) ) */

		U1	u1Dummy20[0x68 - 0x65];

		union {
			U1	u1Data;
			struct {
				U1	xPE			:1;
				U1	xCE			:1;
				U1	b2Dummy1	:2;
				U1	xDCE		:1;
				U1	xOVRUE		:1;
				U1	xOVWRE		:1;
				U1	xOVREE		:1;
			}stBit;
		}unCEST;		/* 0x68 + ( 0x80 * (m+1) ) */

		U1	u1Dummy21[0x6C - 0x69];

		union {
			U1	u1Data;
			struct {
				U1	xPEC		:1;
				U1	xCEC		:1;
				U1	b2Dummy1	:2;
				U1	xDCEC		:1;
				U1	xOVRUEC		:1;
				U1	xOVWREC		:1;
				U1	xOVREEC		:1;
			}stBit;
		}unCESTC;		/* 0x6C + ( 0x80 * (m+1) ) */

		U1	u1Dummy22[0x80 - 0x6D];

	}stCH[MSPI_CH_NUM];

	U1	u1Dummy23[0x1000 - 0x0680];

	union {
		U1	u1Data[MSPI_RAM_SIZE];		/*  8-bit Access */
		U2	u2Data[MSPI_RAM_SIZE/2];	/* 16-bit Access */
		U4	u4Data[MSPI_RAM_SIZE/4];	/* 32-bit Access */
	}unRAM;		/* 0x1000 */
}Reg_Mspi_UnitType;

/***************************/
/*        MSPInINTF        */
/***************************/
typedef	struct {

	struct {
		union {
			U4	u4Data;
			struct {
				U4	b12INTF		:12;
				U4	b20Dummy1	:20;
			}stBit;
		}unINTF;	/* 0x00 + ( k * 0x30 ) */

		union {
			U4	u4Data;
			struct {
				U4	b12INTMSK	:12;
				U4	b20Dummy1	:20;
			}stBit;
		}unINTMSK;	/* 0x04 + ( k * 0x30 ) */

		union {
			U4	u4Data;
			struct {
				U4	b12INTFC	:12;
				U4	b20Dummy1	:20;
			}stBit;
		}unINTFC;	/* 0x08 + ( k * 0x30 ) */

		U1	u1Dummy1[0x30 - 0x0C];

	}stFACTOR[MSPI_INTF_FACTOR_NUM];
}Reg_Mspi_IntfType;

/***************************/
/*         MSPITG          */
/***************************/
typedef	struct {

	union {
		U4	u4Data;
		struct {
			U4	xTRGSEL0	:1;
			U4	b3SRCSEL0	:3;
			U4	xTRGSEL1	:1;
			U4	b3SRCSEL1	:3;
			U4	xTRGSEL2	:1;
			U4	b3SRCSEL2	:3;
			U4	xTRGSEL3	:1;
			U4	b3SRCSEL3	:3;
			U4	xTRGSEL4	:1;
			U4	b3SRCSEL4	:3;
			U4	xTRGSEL5	:1;
			U4	b3SRCSEL5	:3;
			U4	xTRGSEL6	:1;
			U4	b3SRCSEL6	:3;
			U4	xTRGSEL7	:1;
			U4	b3SRCSEL7	:3;
		}stBit;
	}unTGCTLN[MSPI_UNIT_NUM];	/* 0x00 */

	union {
		U4	u4Data;
		struct {
			U4	xDMAAS02	:1;
			U4	xDMAAS03	:1;
			U4	xDMAAS06	:1;
			U4	xDMAAS07	:1;
			U4	xDMAAS010	:1;
			U4	xDMAAS011	:1;
			U4	xDMAAS12	:1;
			U4	xDMAAS13	:1;
			U4	xDMAAS16	:1;
			U4	xDMAAS17	:1;
			U4	xDMAAS110	:1;
			U4	xDMAAS111	:1;
			U4	xDMAAS22	:1;
			U4	xDMAAS23	:1;
			U4	xDMAAS26	:1;
			U4	xDMAAS27	:1;
			U4	xDMAAS210	:1;
			U4	xDMAAS211	:1;
			U4	b14Dummy1	:14;
		}stBit;
	}unTGDMAALT;	/* 0x28 */

	union {
		U4	u4Data;
		struct {
			U4	xDTSAS06	:1;
			U4	xDTSAS07	:1;
			U4	xDTSAS08	:1;
			U4	xDTSAS09	:1;
			U4	xDTSAS010	:1;
			U4	xDTSAS011	:1;
			U4	xDTSAS18	:1;
			U4	xDTSAS19	:1;
			U4	xDTSAS110	:1;
			U4	xDTSAS111	:1;
			U4	b22Dummy1	:22;
		}stBit;
	}unTGDTSALT;	/* 0x2C */

	union {
		U4	u4Data;
		struct {
			U4	xTRGSEL8	:1;
			U4	b3SRCSEL8	:3;
			U4	xTRGSEL9	:1;
			U4	b3SRCSEL9	:3;
			U4	xTRGSEL10	:1;
			U4	b3SRCSEL10	:3;
			U4	xTRGSEL11	:1;
			U4	b3SRCSEL11	:3;
			U4	b16Dummy1	:16;
		}stBit;
	}unTGCTLI[MSPI_TGCTLI_NUM];	/* 0x30 */
}Reg_Mspi_TgType;

/*======================================================================*/
/*	register BIT definition												*/
/*======================================================================*/

/*------------------------------------------------------------------*/
/*	CTL0															*/
/*------------------------------------------------------------------*/
/* ビット定義 */
#define		MSPI_CTL0_EN									(BIT0)

/* ビット設定値定義 */
#define		MSPI_CTL0_EN_DISABLE							(0)
#define		MSPI_CTL0_EN_ENABLE								(1)

/*------------------------------------------------------------------*/
/*	CTL1															*/
/*------------------------------------------------------------------*/
/* ビット定義 */
#define		MSPI_CTL1_MSSEL									(BIT31)
#define		MSPI_CTL1_CSIE									(BIT29)
#define		MSPI_CTL1_SAMP									(BIT28)
#define		MSPI_CTL1_CKR									(BIT27)
#define		MSPI_CTL1_SOLS									(BIT25 + BIT24)
#define		MSPI_CTL1_SOLS_0								(BIT24)
#define		MSPI_CTL1_CSP									(BIT11 + BIT10 + BIT9 + BIT8 + BIT7 + BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)
#define		MSPI_CTL1_CSP_0									(BIT0)

/* ビット設定値定義 */
#define		MSPI_CTL1_MSSEL_MASTER							(0)
#define		MSPI_CTL1_MSSEL_SLAVE							(1)

#define		MSPI_CTL1_CSIE_IGNORE							(0)
#define		MSPI_CTL1_CSIE_RECOGNIZE						(1)

#define		MSPI_CTL1_SAMP_STANDARD							(0)
#define		MSPI_CTL1_SAMP_NEXT_EDGE						(1)

#define		MSPI_CTL1_CKR_LOW								(0)
#define		MSPI_CTL1_CKR_HIGH								(1)

#define		MSPI_CTL1_SOLS_LOW_HOLD							(0)
#define		MSPI_CTL1_SOLS_LOW								(1)
#define		MSPI_CTL1_SOLS_HIGH_HOLD						(2)
#define		MSPI_CTL1_SOLS_HIGH								(3)

#define		MSPI_CTL1_CSP_ACTIVE_LOW						(0)
#define		MSPI_CTL1_CSP_ACTIVE_HIGH						(1)

/*------------------------------------------------------------------*/
/*	CTL2															*/
/*------------------------------------------------------------------*/
/* ビット定義 */
#define		MSPI_CTL2_DCS									(BIT1)
#define		MSPI_CTL2_LBM									(BIT0)

/* ビット設定値定義 */
#define		MSPI_CTL2_DCS_DISABLE							(0)
#define		MSPI_CTL2_DCS_ENABLE							(1)

#define		MSPI_CTL2_LBM_DISABLE							(0)
#define		MSPI_CTL2_LBM_ENABLE							(1)

/*------------------------------------------------------------------*/
/*	STR0															*/
/*------------------------------------------------------------------*/
/* ビット定義 */
#define		MSPI_STR0_CNUMF									(BIT7 + BIT6 + BIT5 + BIT4)
#define		MSPI_STR0_CNUMF_0								(BIT4) /* 設定値は数値として参照するため定義不要 */
#define		MSPI_STR0_CSF									(BIT0)

/* ビット設定値定義 */
#define		MSPI_STR0_CSF_NOT_COMMUNICATE					(0)
#define		MSPI_STR0_CSF_COMMUNICATE						(1)

/*------------------------------------------------------------------*/
/*	CFG0															*/
/*------------------------------------------------------------------*/
/* ビット定義 */
#define		MSPI_CFG0_TXE									(BIT29)
#define		MSPI_CFG0_RXE									(BIT28)
#define		MSPI_CFG0_MD									(BIT25 + BIT24)
#define		MSPI_CFG0_MD_0									(BIT24)
#define		MSPI_CFG0_PRIO									(BIT22 + BIT21 + BIT20)
#define		MSPI_CFG0_PRIO_0								(BIT20)
#define		MSPI_CFG0_LOCK									(BIT16)
#define		MSPI_CFG0_FCCE									(BIT12)
#define		MSPI_CFG0_IERE									(BIT3)
#define		MSPI_CFG0_IFEE									(BIT2)
#define		MSPI_CFG0_IRXE									(BIT1)
#define		MSPI_CFG0_ITXE									(BIT0)

/* ビット設定値定義 */
#define		MSPI_CFG0_TXE_DISABLE							(0)
#define		MSPI_CFG0_TXE_ENABLE							(1)

#define		MSPI_CFG0_RXE_DISABLE							(0)
#define		MSPI_CFG0_RXE_ENABLE							(1)

#define		MSPI_CFG0_MD_DIRECT								(0)
#define		MSPI_CFG0_MD_FIXED_BUFFER						(1)
#define		MSPI_CFG0_MD_FIXED_FIFO							(2)

#define		MSPI_CFG0_PRIO_LEVEL1							(0)
#define		MSPI_CFG0_PRIO_LEVEL2							(1)
#define		MSPI_CFG0_PRIO_LEVEL3							(2)
#define		MSPI_CFG0_PRIO_LEVEL4							(3)
#define		MSPI_CFG0_PRIO_LEVEL5							(4)
#define		MSPI_CFG0_PRIO_LEVEL6							(5)
#define		MSPI_CFG0_PRIO_LEVEL7							(6)
#define		MSPI_CFG0_PRIO_LEVEL8							(7)

#define		MSPI_CFG0_LOCK_DISABLE							(0)
#define		MSPI_CFG0_LOCK_ENABLE							(1)

#define		MSPI_CFG0_FCCE_CHEN_CLEAR						(0)
#define		MSPI_CFG0_FCCE_CHEN_NOT_CLEAR					(1)

#define		MSPI_CFG0_IERE_DISABLE							(0)
#define		MSPI_CFG0_IERE_ENABLE							(1)

#define		MSPI_CFG0_IFEE_DISABLE							(0)
#define		MSPI_CFG0_IFEE_ENABLE							(1)

#define		MSPI_CFG0_IRXE_DISABLE							(0)
#define		MSPI_CFG0_IRXE_ENABLE							(1)

#define		MSPI_CFG0_ITXE_DISABLE							(0)
#define		MSPI_CFG0_ITXE_ENABLE							(1)

/*------------------------------------------------------------------*/
/*	CFG1															*/
/*------------------------------------------------------------------*/
/* ビット定義 */
#define		MSPI_CFG1_CPOL									(BIT25)
#define		MSPI_CFG1_CPHA									(BIT24)
#define		MSPI_CFG1_DIR									(BIT20)
#define		MSPI_CFG1_ICLS									(BIT18)
#define		MSPI_CFG1_FIDL									(BIT17)
#define		MSPI_CFG1_CSRI									(BIT16)
#define		MSPI_CFG1_SAFCM									(BIT11)
#define		MSPI_CFG1_SAFS									(BIT9)
#define		MSPI_CFG1_SAFE									(BIT8)
#define		MSPI_CFG1_PS									(BIT5 + BIT4)
#define		MSPI_CFG1_PS_0									(BIT4)
#define		MSPI_CFG1_DECHK									(BIT0)

/* ビット設定値定義 */
#define		MSPI_CFG1_CPOL_IDLE_LOW							(0)
#define		MSPI_CFG1_CPOL_IDLE_HIGH						(1)

#define		MSPI_CFG1_CPHA_EVEN_OUT_ODD_SAMP				(0)
#define		MSPI_CFG1_CPHA_ODD_OUT_EVEN_SAMP				(1)

#define		MSPI_CFG1_DIR_MSB_FIRST							(0)
#define		MSPI_CFG1_DIR_LSB_FIRST							(1)

#define		MSPI_CFG1_ICLS_CS_INACTIVE						(0)
#define		MSPI_CFG1_ICLS_CS_HOLD_ACTIVE					(1)

#define		MSPI_CFG1_FIDL_IDLE_NOT_INSERT					(0)
#define		MSPI_CFG1_FIDL_IDLE_INSERT						(1)

#define		MSPI_CFG1_CSRI_CS_HOLD_ACTIVE					(0)
#define		MSPI_CFG1_CSRI_CS_INACTIVE						(1)

#define		MSPI_CFG1_SAFCM_NOT_MASK_CRCERR					(0)
#define		MSPI_CFG1_SAFCM_MASK_CRCERR						(1)

#define		MSPI_CFG1_SAFS_IN_FRAME							(0)
#define		MSPI_CFG1_SAFS_OUT_OF_FRAME						(1)

#define		MSPI_CFG1_SAFE_DISABLE							(0)
#define		MSPI_CFG1_SAFE_ENABLE							(1)

#define		MSPI_CFG1_PS_ODD_PARITY							(0)
#define		MSPI_CFG1_PS_EVEN_PARITY						(1)
#define		MSPI_CFG1_PS_ZERO_PARITY						(2)

#define		MSPI_CFG1_DECHK_NO								(0)
#define		MSPI_CFG1_DECHK_PARITY							(1)

/*------------------------------------------------------------------*/
/*	CFG2															*/
/*------------------------------------------------------------------*/
/* ビット定義 */
#define		MSPI_CFG2_FLEN									(BIT7 + BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)
#define		MSPI_CFG2_FLEN_0								(BIT0)

/* ビット設定値定義 (任意の値を設定するため定義不要) */

/*------------------------------------------------------------------*/
/*	CFG3															*/
/*------------------------------------------------------------------*/
/* ビット定義 */
#define		MSPI_CFG3_PRCS									(BIT9 + BIT8)
#define		MSPI_CFG3_PRCS_0								(BIT8)
#define		MSPI_CFG3_CDIV									(BIT4 + BIT3 + BIT2 + BIT1 + BIT0)
#define		MSPI_CFG3_CDIV_0								(BIT0) /* 設定値は任意の値を設定するため定義不要 */

/* ビット設定値定義 */
#define		MSPI_CFG3_PRCS_CLK								(0)
#define		MSPI_CFG3_PRCS_CLK_4							(1)
#define		MSPI_CFG3_PRCS_CLK_16							(2)
#define		MSPI_CFG3_PRCS_CLK_64							(3)

/*------------------------------------------------------------------*/
/*	CFG4															*/
/*------------------------------------------------------------------*/
/* ビット定義 */
#define		MSPI_CFG4_HWTS									(BIT21 + BIT20 + BIT19 + BIT18 + BIT17 + BIT16)
#define		MSPI_CFG4_HWTS_0								(BIT16)
#define		MSPI_CFG4_SIZE									(BIT1 + BIT0)
#define		MSPI_CFG4_SIZE_0								(BIT0)

/* ビット設定値定義 */
#define		MSPI_CFG4_HWTS_DISABLE							(0)
#define		MSPI_CFG4_HWTS_IRQ0_ATU0						(1)
#define		MSPI_CFG4_HWTS_IRQ1_ATU1						(2)
#define		MSPI_CFG4_HWTS_IRQ2_ATU2						(3)
#define		MSPI_CFG4_HWTS_IRQ3_ATU3						(4)
#define		MSPI_CFG4_HWTS_INTTPTMU00						(5)
#define		MSPI_CFG4_HWTS_INTTPTMU01						(6)
#define		MSPI_CFG4_HWTS_INTTPTMU02						(7)
#define		MSPI_CFG4_HWTS_INTTPTMU03						(8)
#define		MSPI_CFG4_HWTS_INTTPTMU10						(9)
#define		MSPI_CFG4_HWTS_INTTPTMU11						(10)
#define		MSPI_CFG4_HWTS_INTTPTMU12						(11)
#define		MSPI_CFG4_HWTS_INTTPTMU13						(12)
#define		MSPI_CFG4_HWTS_INTTPTMU20						(13)
#define		MSPI_CFG4_HWTS_INTTPTMU21						(14)
#define		MSPI_CFG4_HWTS_INTTPTMU22						(15)
#define		MSPI_CFG4_HWTS_INTTPTMU23						(16)
#define		MSPI_CFG4_HWTS_INTTPTMU30						(17)
#define		MSPI_CFG4_HWTS_INTTPTMU31						(18)
#define		MSPI_CFG4_HWTS_INTTPTMU32						(19)
#define		MSPI_CFG4_HWTS_INTTPTMU33						(20)
#define		MSPI_CFG4_HWTS_GTMMSPICFG00_ATU4				(21)
#define		MSPI_CFG4_HWTS_GTMMSPICFG01_ATU5				(22)
#define		MSPI_CFG4_HWTS_GTMMSPICFG02_ATU6				(23)
#define		MSPI_CFG4_HWTS_GTMMSPICFG10_ATU7				(24)
#define		MSPI_CFG4_HWTS_GTMMSPICFG11_ATU8				(25)
#define		MSPI_CFG4_HWTS_GTMMSPICFG12_ATU9				(26)
#define		MSPI_CFG4_HWTS_GTMMSPICFG20_ATU10				(27)
#define		MSPI_CFG4_HWTS_GTMMSPICFG21_ATU11				(28)
#define		MSPI_CFG4_HWTS_GTMMSPICFG22_ATU12				(29)
#define		MSPI_CFG4_HWTS_GTMMSPICFG30_ATU13				(30)
#define		MSPI_CFG4_HWTS_GTMMSPICFG31_ATU14				(31)
#define		MSPI_CFG4_HWTS_GTMMSPICFG32_ATU15				(32)
#define		MSPI_CFG4_HWTS_GTMMSPICFG40_ATU16				(33)
#define		MSPI_CFG4_HWTS_GTMMSPICFG41_ATU17				(34)
#define		MSPI_CFG4_HWTS_GTMMSPICFG42_ATU18				(35)
#define		MSPI_CFG4_HWTS_GTMMSPICFG50_ATU19				(36)
#define		MSPI_CFG4_HWTS_GTMMSPICFG51_ATU20				(37)
#define		MSPI_CFG4_HWTS_GTMMSPICFG52_ATU21				(38)
#define		MSPI_CFG4_HWTS_GTMMSPICFG60_ATU22				(39)
#define		MSPI_CFG4_HWTS_GTMMSPICFG61_ATU23				(40)
#define		MSPI_CFG4_HWTS_GTMMSPICFG62_ATU24				(41)
#define		MSPI_CFG4_HWTS_GTMMSPICFG70_ATU25				(42)
#define		MSPI_CFG4_HWTS_GTMMSPICFG71_ATU26				(43)
#define		MSPI_CFG4_HWTS_GTMMSPICFG72_ATU27				(44)
#define		MSPI_CFG4_HWTS_GTMMSPICFG80_ATU28				(45)
#define		MSPI_CFG4_HWTS_GTMMSPICFG81_ATU29				(46)
#define		MSPI_CFG4_HWTS_GTMMSPICFG82_ATU30				(47)
#define		MSPI_CFG4_HWTS_GTMMSPICFG90_ATU31				(48)
#define		MSPI_CFG4_HWTS_GTMMSPICFG91_TAUD0_8				(49)
#define		MSPI_CFG4_HWTS_GTMMSPICFG92_TAUD1_9				(50)
#define		MSPI_CFG4_HWTS_TAUD2_10							(51)
#define		MSPI_CFG4_HWTS_TAUD3_11							(52)
#define		MSPI_CFG4_HWTS_TAUD4_12							(53)
#define		MSPI_CFG4_HWTS_TAUD5_13							(54)
#define		MSPI_CFG4_HWTS_TAUD6_14							(55)
#define		MSPI_CFG4_HWTS_INTTSG30IVLY						(56)
#define		MSPI_CFG4_HWTS_INTTSG30IPEK						(57)
#define		MSPI_CFG4_HWTS_INTTSG30I12						(58)
#define		MSPI_CFG4_HWTS_INTTSG30I11						(59)
#define		MSPI_CFG4_HWTS_INTTSG31IVLY						(60)
#define		MSPI_CFG4_HWTS_INTTSG31IPEK						(61)
#define		MSPI_CFG4_HWTS_INTTSG31I12						(62)
#define		MSPI_CFG4_HWTS_INTTSG31I11						(63)

#define		MSPI_CFG4_SIZE_STAGESIZE8						(0)
#define		MSPI_CFG4_SIZE_STAGESIZE16						(1)
#define		MSPI_CFG4_SIZE_STAGESIZE32						(2)

/*------------------------------------------------------------------*/
/*	SEUP															*/
/*------------------------------------------------------------------*/
/* ビット定義 */
#define		MSPI_SEUP_SEUP									(BIT11 + BIT10 + BIT9 + BIT8 + BIT7 + BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)
#define		MSPI_SEUP_SEUP_0								(BIT0)

/* ビット設定値定義 (任意の値を設定するため定義不要) */

/*------------------------------------------------------------------*/
/*	HOLD															*/
/*------------------------------------------------------------------*/
/* ビット定義 */
#define		MSPI_HOLD_HOLD									(BIT11 + BIT10 + BIT9 + BIT8 + BIT7 + BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)
#define		MSPI_HOLD_HOLD_0								(BIT0)

/* ビット設定値定義 (任意の値を設定するため定義不要) */

/*------------------------------------------------------------------*/
/*	IDLE															*/
/*------------------------------------------------------------------*/
/* ビット定義 */
#define		MSPI_IDLE_IDLE									(BIT11 + BIT10 + BIT9 + BIT8 + BIT7 + BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)
#define		MSPI_IDLE_IDLE_0								(BIT0)

/* ビット設定値定義 (任意の値を設定するため定義不要) */

/*------------------------------------------------------------------*/
/*	INDA															*/
/*------------------------------------------------------------------*/
/* ビット定義 */
#define		MSPI_INDA_INDA									(BIT11 + BIT10 + BIT9 + BIT8 + BIT7 + BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)
#define		MSPI_INDA_INDA_0								(BIT0)

/* ビット設定値定義 (任意の値を設定するため定義不要) */

/*------------------------------------------------------------------*/
/*	RASTAD															*/
/*------------------------------------------------------------------*/
/* ビット定義 */
#define		MSPI_RASTAD_RASTAD								(BIT8 + BIT7 + BIT6 + BIT5 + BIT4 + BIT3 + BIT2)
#define		MSPI_RASTAD_RASTAD_0							(BIT2)

/* ビット設定値定義 (任意の値を設定するため定義不要) */

/*------------------------------------------------------------------*/
/*	CFSET															*/
/*------------------------------------------------------------------*/
/* ビット定義 (ビット単位でのアクセス不要のため定義不要) */

/* ビット設定値定義 (任意の値を設定するため定義不要) */

/*------------------------------------------------------------------*/
/*	SSTX															*/
/*------------------------------------------------------------------*/
/* ビット定義 */
#define		MSPI_SSTX_JOBEN									(BIT31)
#define		MSPI_SSTX_CSR									(BIT27 + BIT26 + BIT25 + BIT24 + BIT23 + BIT22 + BIT21 + BIT20 + BIT19 + BIT18 + BIT17 + BIT16)
#define		MSPI_SSTX_CSR_0									(BIT16)
#define		MSPI_SSTX_TXDA0									(BIT15 + BIT14 + BIT13 + BIT12 + BIT11 + BIT10 + BIT9 + BIT8 \
															+ BIT7 + BIT6 +  BIT5 +  BIT4 +  BIT3 +  BIT2 +  BIT1 + BIT0)
#define		MSPI_SSTX_TXDA0_0								(BIT0) /* 設定値は任意の値を設定するため定義不要 */

/* ビット設定値定義 (設定値はSSELレジスタの同ビットと同じため定義不要) */

/*------------------------------------------------------------------*/
/*	CSTS															*/
/*------------------------------------------------------------------*/
/* ビット定義 */
#define		MSPI_CSTS_ACTFS									(BIT1)
#define		MSPI_CSTS_CHENS									(BIT0)

/* ビット設定値定義 */
#define		MSPI_CSTS_ACTFS_NO_FUNCTION						(0)
#define		MSPI_CSTS_ACTFS_SET								(1)

#define		MSPI_CSTS_CHENS_NO_FUNCTION						(0)
#define		MSPI_CSTS_CHENS_SET								(1)

/*------------------------------------------------------------------*/
/*	CSTC															*/
/*------------------------------------------------------------------*/
/* ビット定義 */
#define		MSPI_CSTC_CHENC									(BIT0)

/* ビット設定値定義 */
#define		MSPI_CSTC_CHENC_NO_FUNCTION						(0)
#define		MSPI_CSTC_CHENC_CLEAR							(1)

/*------------------------------------------------------------------*/
/*	SSEL															*/
/*------------------------------------------------------------------*/
/* ビット定義 */
#define		MSPI_SSEL_JOBEN									(BIT15)
#define		MSPI_SSEL_CSR									(BIT11 + BIT10 + BIT9 + BIT8 + BIT7 + BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)
#define		MSPI_SSEL_CSR_0									(BIT0)

/* ビット設定値定義 */
#define		MSPI_SSEL_JOBEN_END								(0)
#define		MSPI_SSEL_JOBEN_CONTINIOUS						(1)

#define		MSPI_SSEL_CSR_DEACTIVATE						(0)
#define		MSPI_SSEL_CSR_ACTIVATE							(1)

/*------------------------------------------------------------------*/
/*	TXDA0															*/
/*------------------------------------------------------------------*/
/* ビット定義 (ビット単位でのアクセス不要のため定義不要) */

/* ビット設定値定義 (任意の値を設定するため定義不要) */

/*------------------------------------------------------------------*/
/*	FRERST															*/
/*------------------------------------------------------------------*/
/* ビット定義 */
#define		MSPI_FRERST_DCEFST								(BIT4)
#define		MSPI_FRERST_CEFST								(BIT1)
#define		MSPI_FRERST_PEFST								(BIT0)

/* ビット設定値定義 */
#define		MSPI_FRERST_DCEFST_ERR_NOT_DETECT				(0)
#define		MSPI_FRERST_DCEFST_ERR_DETECT					(1)

#define		MSPI_FRERST_CEFST_ERR_NOT_DETECT				(0)
#define		MSPI_FRERST_CEFST_ERR_DETECT					(1)

#define		MSPI_FRERST_PEFST_ERR_NOT_DETECT				(0)
#define		MSPI_FRERST_PEFST_ERR_DETECT					(1)

/*------------------------------------------------------------------*/
/*	RXDA0															*/
/*------------------------------------------------------------------*/
/* ビット定義 (ビット単位でのアクセス不要のため定義不要) */

/* ビット設定値定義 (任意の値を設定するため定義不要) */

/*------------------------------------------------------------------*/
/*	CSTR															*/
/*------------------------------------------------------------------*/
/* ビット定義 */
#define		MSPI_CSTR_FIRXN									(BIT15 + BIT14 + BIT13 + BIT12 + BIT11 + BIT10 + BIT9 + BIT8)
#define		MSPI_CSTR_FIRXN_0								(BIT8) /* 設定値は数値として参照するため定義不要 */
#define		MSPI_CSTR_TXRQF									(BIT5)
#define		MSPI_CSTR_RXRQF									(BIT4)
#define		MSPI_CSTR_ACTF									(BIT1)
#define		MSPI_CSTR_CHEN									(BIT0)

/* ビット設定値定義 */
#define		MSPI_CSTR_TXRQF_NO_REQUEST						(0)
#define		MSPI_CSTR_TXRQF_REQUEST							(1)

#define		MSPI_CSTR_RXRQF_NO_REQUEST						(0)
#define		MSPI_CSTR_RXRQF_REQUEST							(1)

#define		MSPI_CSTR_ACTF_INACTIVE							(0)
#define		MSPI_CSTR_ACTF_ACTIVE							(1)

#define		MSPI_CSTR_CHEN_DISABLE							(0)
#define		MSPI_CSTR_CHEN_ENABLE							(1)

/*------------------------------------------------------------------*/
/*	CFCNT															*/
/*------------------------------------------------------------------*/
/* ビット定義 (ビット単位でのアクセス不要のため定義不要) */

/* ビット設定値定義 (数値として参照するため定義不要) */

/*------------------------------------------------------------------*/
/*	FSRX															*/
/*------------------------------------------------------------------*/
/* ビット定義 */
#define		MSPI_FSRX_DEFST									(BIT20)
#define		MSPI_FSRX_CEFST									(BIT17)
#define		MSPI_FSRX_PEFST									(BIT16)
#define		MSPI_FSRX_RXDA0									(BIT15 + BIT14 + BIT13 + BIT12 + BIT11 + BIT10 + BIT9 + BIT8 \
															+ BIT7 + BIT6 +  BIT5 +  BIT4 +  BIT3 +  BIT2 +  BIT1 + BIT0)
#define		MSPI_FSRX_RXDA0_0								(BIT0) /* 設定値は数値として参照するため定義不要 */

/* ビット設定値定義 (設定値はFRERSTレジスタの同ビットと同じため定義不要。本レジスタのDEFSTビットはFRERSTレジスタのDCEFSTビットと同じ。) */

/*------------------------------------------------------------------*/
/*	FRERSTC															*/
/*------------------------------------------------------------------*/
/* ビット定義 */
#define		MSPI_FRERSTC_DCEFSC								(BIT4)
#define		MSPI_FRERSTC_CEFSC								(BIT1)
#define		MSPI_FRERSTC_PEFSC								(BIT0)

/* ビット設定値定義 */
#define		MSPI_FRERSTC_DCEFSC_NO_FUNCTION					(0)
#define		MSPI_FRERSTC_DCEFSC_CLEAR						(1)

#define		MSPI_FRERSTC_CEFSC_NO_FUNCTION					(0)
#define		MSPI_FRERSTC_CEFSC_CLEAR						(1)

#define		MSPI_FRERSTC_PEFSC_NO_FUNCTION					(0)
#define		MSPI_FRERSTC_PEFSC_CLEAR						(1)

/*------------------------------------------------------------------*/
/*	CEST															*/
/*------------------------------------------------------------------*/
/* ビット定義 */
#define		MSPI_CEST_OVREE									(BIT7)
#define		MSPI_CEST_OVWRE									(BIT6)
#define		MSPI_CEST_OVRUE									(BIT5)
#define		MSPI_CEST_DCE									(BIT4)
#define		MSPI_CEST_CE									(BIT1)
#define		MSPI_CEST_PE									(BIT0)

/* ビット設定値定義 */
#define		MSPI_CEST_OVREE_ERR_NOT_DETECT					(0)
#define		MSPI_CEST_OVREE_ERR_DETECT						(1)

#define		MSPI_CEST_OVWRE_ERR_NOT_DETECT					(0)
#define		MSPI_CEST_OVWRE_ERR_DETECT						(1)

#define		MSPI_CEST_OVRUE_ERR_NOT_DETECT					(0)
#define		MSPI_CEST_OVRUE_ERR_DETECT						(1)

#define		MSPI_CEST_DCE_ERR_NOT_DETECT					(0)
#define		MSPI_CEST_DCE_ERR_DETECT						(1)

#define		MSPI_CEST_CE_ERR_NOT_DETECT						(0)
#define		MSPI_CEST_CE_ERR_DETECT							(1)

#define		MSPI_CEST_PE_ERR_NOT_DETECT						(0)
#define		MSPI_CEST_PE_ERR_DETECT							(1)

/*------------------------------------------------------------------*/
/*	CESTC															*/
/*------------------------------------------------------------------*/
/* ビット定義 */
#define		MSPI_CESTC_OVREEC								(BIT7)
#define		MSPI_CESTC_OVWREC								(BIT6)
#define		MSPI_CESTC_OVRUEC								(BIT5)
#define		MSPI_CESTC_DCEC									(BIT4)
#define		MSPI_CESTC_CEC									(BIT1)
#define		MSPI_CESTC_PEC									(BIT0)

/* ビット設定値定義 */
#define		MSPI_CESTC_OVREEC_NO_FUNCTION					(0)
#define		MSPI_CESTC_OVREEC_CLEAR							(1)

#define		MSPI_CESTC_OVWREC_NO_FUNCTION					(0)
#define		MSPI_CESTC_OVWREC_CLEAR							(1)

#define		MSPI_CESTC_OVRUEC_NO_FUNCTION					(0)
#define		MSPI_CESTC_OVRUEC_CLEAR							(1)

#define		MSPI_CESTC_DCEC_NO_FUNCTION						(0)
#define		MSPI_CESTC_DCEC_CLEAR							(1)

#define		MSPI_CESTC_CEC_NO_FUNCTION						(0)
#define		MSPI_CESTC_CEC_CLEAR							(1)

#define		MSPI_CESTC_PEC_NO_FUNCTION						(0)
#define		MSPI_CESTC_PEC_CLEAR							(1)

/*------------------------------------------------------------------*/
/*	INTF															*/
/*------------------------------------------------------------------*/
/* ビット定義 */
#define		MSPI_INTF_INTF									(BIT11 + BIT10 + BIT9 + BIT8 + BIT7 + BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)
#define		MSPI_INTF_INTF_0								(BIT0)

/* ビット設定値定義 */
#define		MSPI_INTF_INTF_NO_INTERRUPT						(0)
#define		MSPI_INTF_INTF_INTERRUPT						(1)

/*------------------------------------------------------------------*/
/*	INTMSK															*/
/*------------------------------------------------------------------*/
/* ビット定義 */
#define		MSPI_INTMSK_INTMSK								(BIT11 + BIT10 + BIT9 + BIT8 + BIT7 + BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)
#define		MSPI_INTMSK_INTMSK_0							(BIT0)

/* ビット設定値定義 */
#define		MSPI_INTMSK_INTMSK_NO_MASK						(0)
#define		MSPI_INTMSK_INTMSK_MASK							(1)

/*------------------------------------------------------------------*/
/*	INTFC															*/
/*------------------------------------------------------------------*/
/* ビット定義 */
#define		MSPI_INTFC_INTFC								(BIT11 + BIT10 + BIT9 + BIT8 + BIT7 + BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)
#define		MSPI_INTFC_INTFC_0								(BIT0)

/* ビット設定値定義 */
#define		MSPI_INTFC_INTFC_NO_FUNCTION					(0)
#define		MSPI_INTFC_INTFC_CLEAR							(1)

/*------------------------------------------------------------------*/
/*	TGCTLn															*/
/*------------------------------------------------------------------*/
/* ビット定義 */
#define		MSPI_TGCTLN_SRCSEL7								(BIT31 + BIT30 + BIT29)
#define		MSPI_TGCTLN_SRCSEL7_0							(BIT29)
#define		MSPI_TGCTLN_TRGSEL7								(BIT28)
#define		MSPI_TGCTLN_SRCSEL6								(BIT27 + BIT26 + BIT25)
#define		MSPI_TGCTLN_SRCSEL6_0							(BIT25)
#define		MSPI_TGCTLN_TRGSEL6								(BIT24)
#define		MSPI_TGCTLN_SRCSEL5								(BIT23 + BIT22 + BIT21)
#define		MSPI_TGCTLN_SRCSEL5_0							(BIT21)
#define		MSPI_TGCTLN_TRGSEL5								(BIT20)
#define		MSPI_TGCTLN_SRCSEL4								(BIT19 + BIT18 + BIT17)
#define		MSPI_TGCTLN_SRCSEL4_0							(BIT17)
#define		MSPI_TGCTLN_TRGSEL4								(BIT16)
#define		MSPI_TGCTLN_SRCSEL3								(BIT15 + BIT14 + BIT13)
#define		MSPI_TGCTLN_SRCSEL3_0							(BIT13)
#define		MSPI_TGCTLN_TRGSEL3								(BIT12)
#define		MSPI_TGCTLN_SRCSEL2								(BIT11 + BIT10 + BIT9)
#define		MSPI_TGCTLN_SRCSEL2_0							(BIT9)
#define		MSPI_TGCTLN_TRGSEL2								(BIT8)
#define		MSPI_TGCTLN_SRCSEL1								(BIT7  + BIT6  + BIT5)
#define		MSPI_TGCTLN_SRCSEL1_0							(BIT5)
#define		MSPI_TGCTLN_TRGSEL1								(BIT4)
#define		MSPI_TGCTLN_SRCSEL0								(BIT3  + BIT2  + BIT1)
#define		MSPI_TGCTLN_SRCSEL0_0							(BIT1)
#define		MSPI_TGCTLN_TRGSEL0								(BIT0)

/* ビット設定値定義 */
#define		MSPI_TGCTL_SRCSEL_NONE_NONE						(0)
#define		MSPI_TGCTL_SRCSEL_TX_NONE						(1)
#define		MSPI_TGCTL_SRCSEL_RX_NONE						(2)
#define		MSPI_TGCTL_SRCSEL_FE_NONE						(3)
#define		MSPI_TGCTL_SRCSEL_NONE_TX						(4)
#define		MSPI_TGCTL_SRCSEL_NONE_RX						(5)
#define		MSPI_TGCTL_SRCSEL_NONE_FE						(6)
#define		MSPI_TGCTL_SRCSEL_TX_RX							(7)

#define		MSPI_TGCTL_TRGSEL_DMA							(0)
#define		MSPI_TGCTL_TRGSEL_DTS							(1)

/*------------------------------------------------------------------*/
/*	TGDMAALT														*/
/*------------------------------------------------------------------*/
/* ビット定義 */
#define		MSPI_TGDMAALT_DMAAS211							(BIT17)
#define		MSPI_TGDMAALT_DMAAS210							(BIT16)
#define		MSPI_TGDMAALT_DMAAS27							(BIT15)
#define		MSPI_TGDMAALT_DMAAS26							(BIT14)
#define		MSPI_TGDMAALT_DMAAS23							(BIT13)
#define		MSPI_TGDMAALT_DMAAS22							(BIT12)
#define		MSPI_TGDMAALT_DMAAS111							(BIT11)
#define		MSPI_TGDMAALT_DMAAS110							(BIT10)
#define		MSPI_TGDMAALT_DMAAS17							(BIT9)
#define		MSPI_TGDMAALT_DMAAS16							(BIT8)
#define		MSPI_TGDMAALT_DMAAS13							(BIT7)
#define		MSPI_TGDMAALT_DMAAS12							(BIT6)
#define		MSPI_TGDMAALT_DMAAS011							(BIT5)
#define		MSPI_TGDMAALT_DMAAS010							(BIT4)
#define		MSPI_TGDMAALT_DMAAS07							(BIT3)
#define		MSPI_TGDMAALT_DMAAS06							(BIT2)
#define		MSPI_TGDMAALT_DMAAS03							(BIT1)
#define		MSPI_TGDMAALT_DMAAS02							(BIT0)

/* ビット設定値定義 */
#define		MSPI_TGDMAALT_DMAAS_NOT_USE						(0)
#define		MSPI_TGDMAALT_DMAAS_USE							(1)

/*------------------------------------------------------------------*/
/*	TGDTSALT														*/
/*------------------------------------------------------------------*/
/* ビット定義 */
#define		MSPI_TGDTSALT_DTSAS111							(BIT9)
#define		MSPI_TGDTSALT_DTSAS110							(BIT8)
#define		MSPI_TGDTSALT_DTSAS19							(BIT7)
#define		MSPI_TGDTSALT_DTSAS18							(BIT6)
#define		MSPI_TGDTSALT_DTSAS011							(BIT5)
#define		MSPI_TGDTSALT_DTSAS010							(BIT4)
#define		MSPI_TGDTSALT_DTSAS09							(BIT3)
#define		MSPI_TGDTSALT_DTSAS08							(BIT2)
#define		MSPI_TGDTSALT_DTSAS07							(BIT1)
#define		MSPI_TGDTSALT_DTSAS06							(BIT0)

/* ビット設定値定義 */
#define		MSPI_TGDTSALT_DTSAS_NOT_USE						(0)
#define		MSPI_TGDTSALT_DTSAS_USE							(1)

/*------------------------------------------------------------------*/
/*	TGCTLi															*/
/*------------------------------------------------------------------*/
/* ビット定義 */
#define		MSPI_TGCTLI_SRCSEL11							(BIT15 + BIT14 + BIT13)
#define		MSPI_TGCTLI_SRCSEL11_0							(BIT13)
#define		MSPI_TGCTLI_TRGSEL11							(BIT12)
#define		MSPI_TGCTLI_SRCSEL10							(BIT11 + BIT10 + BIT9)
#define		MSPI_TGCTLI_SRCSEL10_0							(BIT9)
#define		MSPI_TGCTLI_TRGSEL10							(BIT8)
#define		MSPI_TGCTLI_SRCSEL9								(BIT7  + BIT6  + BIT5)
#define		MSPI_TGCTLI_SRCSEL9_0							(BIT5)
#define		MSPI_TGCTLI_TRGSEL9								(BIT4)
#define		MSPI_TGCTLI_SRCSEL8								(BIT3  + BIT2  + BIT1)
#define		MSPI_TGCTLI_SRCSEL8_0							(BIT1)
#define		MSPI_TGCTLI_TRGSEL8								(BIT0)

/* ビット設定値定義 (設定値はTGCTLnレジスタの同ビットと同じため定義不要) */


/*==============================================================================================*/
/*	struct address definition																	*/
/*==============================================================================================*/
#define		REG_MSPI0		(*(volatile Reg_Mspi_UnitType *)(0xFFC76000U))
#define		REG_MSPI1		(*(volatile Reg_Mspi_UnitType *)(0xFFC7E000U))
#define		REG_MSPI2		(*(volatile Reg_Mspi_UnitType *)(0xFFD80000U))
#define		REG_MSPI3		(*(volatile Reg_Mspi_UnitType *)(0xFFCC0000U))
#define		REG_MSPI4		(*(volatile Reg_Mspi_UnitType *)(0xFFD82000U))
#define		REG_MSPI5		(*(volatile Reg_Mspi_UnitType *)(0xFFCC4000U))
#define		REG_MSPI6		(*(volatile Reg_Mspi_UnitType *)(0xFFD84000U))
#define		REG_MSPI7		(*(volatile Reg_Mspi_UnitType *)(0xFFCC8000U))
#define		REG_MSPI8		(*(volatile Reg_Mspi_UnitType *)(0xFFD86000U))
#define		REG_MSPI9		(*(volatile Reg_Mspi_UnitType *)(0xFFCCC000U))
#define		REG_MSPI0INTF	(*(volatile Reg_Mspi_IntfType *)(0xFFC75740U))
#define		REG_MSPI1INTF	(*(volatile Reg_Mspi_IntfType *)(0xFFC7C840U))
#define		REG_MSPI2INTF	(*(volatile Reg_Mspi_IntfType *)(0xFFC75840U))
#define		REG_MSPI3INTF	(*(volatile Reg_Mspi_IntfType *)(0xFFC7CA40U))
#define		REG_MSPI4INTF	(*(volatile Reg_Mspi_IntfType *)(0xFFC75940U))
#define		REG_MSPI5INTF	(*(volatile Reg_Mspi_IntfType *)(0xFFC7CC40U))
#define		REG_MSPI6INTF	(*(volatile Reg_Mspi_IntfType *)(0xFFC75A40U))
#define		REG_MSPI7INTF	(*(volatile Reg_Mspi_IntfType *)(0xFFC7CE40U))
#define		REG_MSPI8INTF	(*(volatile Reg_Mspi_IntfType *)(0xFFC75B40U))
#define		REG_MSPI9INTF	(*(volatile Reg_Mspi_IntfType *)(0xFFC7D040U))
#define		REG_MSPITG		(*(volatile Reg_Mspi_TgType   *)(0xFFC75D00U))

// #define SEL_ROMSEC	(BSW_SEC_C_LROM0_CPU0_ASIL_SDA)
// #include "Bsw_Seccfg_Roms.h"
#pragma ghs section rodata=".SPI_RODATA_CONST"
extern volatile Reg_Mspi_UnitType* const cpstReg_Mspi[MSPI_UNIT_NUM];
extern volatile Reg_Mspi_IntfType* const cpstReg_MspiIntf[MSPI_UNIT_NUM];
// #include "Bsw_Seccfg_Rome.h"
// #undef SEL_ROMSEC
#pragma ghs section rodata=default

#endif /* REG_MSPI_H */
/*-- End Of File -------------------------------------------------------------------------------*/
