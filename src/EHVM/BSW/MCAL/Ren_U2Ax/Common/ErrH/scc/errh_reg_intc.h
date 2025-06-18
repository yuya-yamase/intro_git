/* reg_intc_r04-3000-0000-a-v01 */
/************************************************************************************************/
/*																								*/
/*		INTC register definition (for RH850U2A)													*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

#ifndef REG_INTC_H
#define REG_INTC_H


#include "reg_dma.h"

#define	INTC_INTC1_CH_NUM		(32)
#define	INTC_INTC2_CH_NUM		(736)
#define	INTC_CH_NUM				(INTC_INTC1_CH_NUM + INTC_INTC2_CH_NUM)

#define	INTC_IMR_REG_NUM		((INTC_CH_NUM/32))
#define INTC_PINT_REG_NUM		((DMA_DTS_CH_NUM/32) * 2)

/*==============================================================================================*/
/*	register type definition																	*/
/*==============================================================================================*/

/* ソフトウェア割り込み */
typedef	struct
{
	U1	u1SINTR0;									/* 0xFFC00000 - 0xFFC00001 *//* ソフトウェア割り込みレジスタ 0 */

	U1	u1Dummy_FFC00001[0xFFC00004U - 0xFFC00001U];	/* 0xFFC00001 - 0xFFC00004 */

	U1	u1SINTR1;									/* 0xFFC00004 - 0xFFC00005 *//* ソフトウェア割り込みレジスタ 1 */

	U1	u1Dummy_FFFC00005[0xFFC00008U - 0xFFC00005U];	/* 0xFFC00005 - 0xFFC00008 */

	U1	u1SINTR2;									/* 0xFFC00008 - 0xFFC00009 *//* ソフトウェア割り込みレジスタ 2 */

	U1	u1Dummy_FFC00009[0xFFC0000CU - 0xFFC00009U];	/* 0xFFC00009 - 0xFFC0000C */

	U1	u1SINTR3;									/* 0xFFC0000C - 0xFFC0000D *//* ソフトウェア割り込みレジスタ 3 */

}Reg_Eint_Type;


/* 周辺割り込み機能 */
typedef struct
{

	union
	{
		U4		u4Data;
	}unPINT[INTC_PINT_REG_NUM];						/* 0xFF090000 - 0xFF090020 *//* 周辺割り込みステータスレジスタ */

	union
	{
		U4		u4Data;
	}unPINTCLR[INTC_PINT_REG_NUM];					/* 0xFF090020 - 0xFF090040 *//* 周辺割り込みステータスクリアレジスタ */

	U1	u1Dummy_FF090040[0xFF090200U - 0xFF090040U];	/* 0xFF090040 - 0xFF090200 */

	union
	{
		U4		u4Data;
		U2		u2Data[2];
		U1		u1Data[4];
		struct
		{
			U4		b1TPTMSEL0		:1;		/* PE0 TPTM割り込み */
			U4		b1TPTMSEL1		:1;		/* PE1 TPTM割り込み */
			U4		b1TPTMSEL2		:1;		/* PE2 TPTM割り込み */
			U4		b1TPTMSEL3		:1;		/* PE3 TPTM割り込み */
			U4		b26Dummy1		:28;	/* 予約ビット */
		}stBit;
	}unTPTMSEL;								/* 0xFF090200 - 0xFF090204 *//* EI TPTM割り込み FE EI 選択レジスタ */
}Reg_Intif_Type;


/* 割り込み制御1(self) */
typedef struct
{
	union
	{
		U2		u2Data;
		U1		u1Data[2];
		struct
		{
			U2		b4EIP		:4;		/* 割り込み優先度 */
			U2		b1Dummy1	:1;		/* 予約ビット */
			U2		xEIOV		:1;		/* 割り込みオーバーフロー */
			U2		xEITB		:1;		/* 割り込みベクタ方式選択ビット */
			U2		xEIMK		:1;		/* 割り込みマスクビット */
			U2		b4Dummy2	:4;		/* 予約ビット */
			U2		xEIRF		:1;		/* 割り込み要求フラグ */
			U2		b2Dummy3	:2;		/* 予約ビット */
			U2		xEICT		:1;		/* 割り込みチャネルタイプビット */
		}stBit;
	}unEIC[INTC_INTC1_CH_NUM];								/* 0xFFFC0000 - 0xFFFC0040 *//* EI レベル割り込み制御レジスタ */

	U1	u1Dummy_FFFC0040[0xFFFC00F0U - 0xFFFC0040U];			/* 0xFFFC0040 - 0xFFFC00F0 */

	union
	{
		U4		u4Data;
		U2		u2Data[2];
		U1		u1Data[4];
	}unIMR0;												/* 0xFFFC00F0 - 0xFFFC00F4 *//* EI レベル割り込みマスクレジスタ */

	U1	u1Dummy_FFFC00F4[0xFFFC0100U - 0xFFFC00F4U];			/* 0xFFFC00F4 - 0xFFFC0100 */

	union
	{
		U4		u4Data;
		U2		u2Data[2];
		U1		u1Data[4];
		struct
		{
			U4		b3PEID		:3;		/* 割り込みバインド（要求）指定 */
			U4		b5Dummy1	:5;		/* 予約ビット */
			U4		b3GPID		:3;		/* GPIDの指定（仮想化機能が有効の場合のみ書き込み可） */
			U4		b4Dummy2	:4;		/* 予約ビット */
			U4		b1GM		:1;		/* ゲストモード選択ビット（仮想化機能が有効の場合のみ書き込み可） */
			U4		b16Dummy3	:16;	/* 予約ビット */
		}stBit;
	}unEIBD[INTC_INTC1_CH_NUM];								/* 0xFFFC0100 - 0xFFFC0180 *//* EI レベル割り込みバインドレジスタ */

	U1	u1Dummy_FFFC0180[0xFFFC01C0U - 0xFFFC0180U];			/* 0xFFFC0180 - 0xFFFC01C0 */

	union
	{
		U4		u4Data;
		U2		u2Data[2];
		U1		u1Data[4];
		struct
		{
			U4		b3PEID		:3;		/* 割り当てPE指定 */
			U4		b5Dummy1	:5;		/* 予約ビット */
			U4		b3GPID		:3;		/* GPIDの指定（仮想化機能が有効の場合のみ書き込み可） */
			U4		b4Dummy2	:4;		/* 予約ビット */
			U4		b1GM		:1;		/* ゲストモード選択ビット（仮想化機能が有効の場合のみ書き込み可） */
			U4		b16Dummy3	:16;	/* 予約ビット */
		}stBit;
	}unFIBD;								/* 0xFFFC01C0 - 0xFFFC01C4 *//* FE レベル割込みバインドレジスタ */

	U1	u1Dummy_FFFC01C4[0xFFFC0200U - 0xFFFC01C4U];			/* 0xFFFC01C4 - 0xFFFC0200 */

	union
	{
		U4		u4Data;
		U2		u2Data[2];
		U1		u1Data[4];
		struct
		{
			U4		b6EIP		:6;		/* 割り込み優先度(64段階) */
			U4		b9Dummy1	:9;		/* 予約ビット */
			U4		b1EIOV		:1;		/* 割り込みオーバーフロー */
			U4		b6Dummy2	:6;		/* 予約ビット */
			U4		b1EITB		:1;		/* 割り込みベクタ方式選択ビット */
			U4		b1EIMK		:1;		/* 割り込みマスクビット */
			U4		b4Dummy3	:4;		/* 予約ビット */
			U4		b1EIRF		:1;		/* 割り込み要求フラグ */
			U4		b2Dummy4	:2;		/* 予約ビット */
			U4		b1EICT		:1;		/* 割り込みチャネルタイプビット */
		}stBit;
	}unEEIC[INTC_INTC1_CH_NUM];								/* 0xFFFC0200 - 0xFFFC0280 *//* EI レベル割り込み制御拡張レジスタ */

	union
	{
		U4		u4Data;
		U2		u2Data[2];
		U1		u1Data[4];
		struct
		{
			U4		b6BGPR		:6;		/* 優先度閾値 */
			U4		b26Dummy1	:26;	/*予約ビット*/
		}stBit;
	}unEIBG;								/* 0xFFFC0280 - 0xFFFC0284 *//* バックグラウンドゲスト要求のための優先度閾値を構成するレジスタ */
																		 /* 仮想化機能が有効でない場合、Reservedとして扱う*/

	U1	u1Dummy_FFFC0284[0xFFFC02C0U - 0xFFFC0284U];			/* 0xFFFC0284 - 0xFFFC02C0 */

	union
	{
		U4		u4Data;
		U2		u2Data[2];
		U1		u1Data[4];
		struct
		{
			U4		b1BGE		:1;		/* FEレベル割込みのバックグラウンドゲスト使用可否ビット */
			U4		b31Dummy1	:31;	/*予約ビット*/
		}stBit;
	}unFIBG;								/* 0xFFFC02C0 - 0xFFFC02C4 *//* バックグラウンドゲスト使用可否レジスタ */
																		 /* 仮想化機能が有効でない場合、Reservedとして扱う*/

	U1	u1Dummy_FFFC02C4[0xFFFC02F0U - 0xFFFC02C4U];			/* 0xFFFC02C4 - 0xFFFC02F0 */

	union
	{
		U4		u4Data;
		U2		u2Data[2];
		U1		u1Data[4];
		struct
		{
			U4		b1IHVE		:1;		/* 仮想化機能の有効ビット */
			U4		b31Dummy1	:31;	/*予約ビット*/
		}stBit;
	}unIHVCFG;								/* 0xFFFC02F0 - 0xFFFC02F4 *//* INTC1レジスタの仮想化関連ビット機能を有効にするレジスタ */

}Reg_Intc1self_Type;

/* 割り込み制御1(CPU0) */
typedef struct
{
	union
	{
		U2		u2Data;
		U1		u1Data[2];
		struct
		{
			U2		b4EIP		:4;		/* 割り込み優先度 */
			U2		b1Dummy1	:1;		/* 予約ビット */
			U2		xEIOV		:1;		/* 割り込みオーバーフロー */
			U2		xEITB		:1;		/* 割り込みベクタ方式選択ビット */
			U2		xEIMK		:1;		/* 割り込みマスクビット */
			U2		b4Dummy2	:4;		/* 予約ビット */
			U2		xEIRF		:1;		/* 割り込み要求フラグ */
			U2		b2Dummy3	:2;		/* 予約ビット */
			U2		xEICT		:1;		/* 割り込みチャネルタイプビット */
		}stBit;
	}unEIC[INTC_INTC1_CH_NUM];								/* 0xFFFC4000 - 0xFFFC4040 *//* EI レベル割り込み制御レジスタ */

	U1	u1Dummy_FFFC4040[0xFFFC40F0U - 0xFFFC4040U];			/* 0xFFFC4040 - 0xFFFC40F0 */

	union
	{
		U4		u4Data;
		U2		u2Data[2];
		U1		u1Data[4];
	}unIMR0;												/* 0xFFFC40F0 - 0xFFFC40F4 *//* EI レベル割り込みマスクレジスタ */

	U1	u1Dummy_FFFC40F4[0xFFFC4100U - 0xFFFC40F4U];			/* 0xFFFC40F4 - 0xFFFC4100 */

	union
	{
		U4		u4Data;
		U2		u2Data[2];
		U1		u1Data[4];
		struct
		{
			U4		b3PEID		:3;		/* 割り込みバインド（要求）指定 */
			U4		b5Dummy1	:5;		/* 予約ビット */
			U4		b3GPID		:3;		/* GPIDの指定（仮想化機能が有効の場合のみ書き込み可） */
			U4		b4Dummy2	:4;		/* 予約ビット */
			U4		b1GM		:1;		/* ゲストモード選択ビット（仮想化機能が有効の場合のみ書き込み可） */
			U4		b16Dummy3	:16;	/* 予約ビット */
		}stBit;
	}unEIBD[INTC_INTC1_CH_NUM];								/* 0xFFFC4100 - 0xFFFC4180 *//* EI レベル割り込みバインドレジスタ */

	U1	u1Dummy_FFFC4180[0xFFFC41C0U - 0xFFFC4180U];			/* 0xFFFC4180 - 0xFFFC41C0 */

	union
	{
		U4		u4Data;
		U2		u2Data[2];
		U1		u1Data[4];
		struct
		{
			U4		b3PEID		:3;		/* 割り込みバインド（要求）指定 */
			U4		b5Dummy1	:5;		/* 予約ビット */
			U4		b3GPID		:3;		/* GPIDの指定（仮想化機能が有効の場合のみ書き込み可） */
			U4		b4Dummy2	:4;		/* 予約ビット */
			U4		b1GM		:1;		/* ゲストモード選択ビット（仮想化機能が有効の場合のみ書き込み可） */
			U4		b16Dummy3	:16;	/* 予約ビット */
		}stBit;
	}unFIBD;								/* 0xFFFC41C0 - 0xFFFC41C4 *//* FE レベル割込みバインドレジスタ */

	U1	u1Dummy_FFFC41C4[0xFFFC4200U - 0xFFFC41C4U];			/* 0xFFFC41C4 - 0xFFFC4200 */

	union
	{
		U4		u4Data;
		U2		u2Data[2];
		U1		u1Data[4];
		struct
		{
			U4		b6EIP		:6;		/* 割り込み優先度(64段階) */
			U4		b9Dummy1	:9;		/* 予約ビット */
			U4		b1EIOV		:1;		/* 割り込みオーバーフロー */
			U4		b6Dummy2	:6;		/* 予約ビット */
			U4		b1EITB		:1;		/* 割り込みベクタ方式選択ビット */
			U4		b1EIMK		:1;		/* 割り込みマスクビット */
			U4		b4Dummy3	:4;		/* 予約ビット */
			U4		b1EIRF		:1;		/* 割り込み要求フラグ */
			U4		b2Dummy4	:2;		/* 予約ビット */
			U4		b1EICT		:1;		/* 割り込みチャネルタイプビット */
		}stBit;
	}unEEIC[INTC_INTC1_CH_NUM];								/* 0xFFFC4200 - 0xFFFC4280 *//* EI レベル割り込み制御拡張レジスタ */

	union
	{
		U4		u4Data;
		U2		u2Data[2];
		U1		u1Data[4];
		struct
		{
			U4		b6BGPR		:6;		/* 優先度閾値 */
			U4		b26Dummy1	:26;	/*予約ビット*/
		}stBit;
	}unEIBG;								/* 0xFFFC4280 - 0xFFFC4284 *//* バックグラウンドゲスト要求のための優先度閾値を構成するレジスタ */
                                                                         /* 仮想化機能が有効でない場合、Reservedとして扱う*/

	U1	u1Dummy_FFFC4284[0xFFFC42C0U - 0xFFFC4284U];			/* 0xFFFC4284 - 0xFFFC42C0 */

	union
	{
		U4		u4Data;
		U2		u2Data[2];
		U1		u1Data[4];
		struct
		{
			U4		b1BGE		:1;		/* FEレベル割込みのバックグラウンドゲスト使用可否ビット */
			U4		b31Dummy1	:31;	/*予約ビット*/
		}stBit;
	}unFIBG;								/* 0xFFFC42C0 - 0xFFFC42C4 *//* バックグラウンドゲスト使用可否レジスタ */
                                                                         /* 仮想化機能が有効でない場合、Reservedとして扱う*/

	U1	u1Dummy_FFFC42C4[0xFFFC42F0U - 0xFFFC42C4U];			/* 0xFFFC42C4 - 0xFFFC42F0 */

	union
	{
		U4		u4Data;
		U2		u2Data[2];
		U1		u1Data[4];
		struct
		{
			U4		b1IHVE		:1;		/* 仮想化機能の有効ビット */
			U4		b31Dummy1	:31;	/*予約ビット*/
		}stBit;
	}unIHVCFG;								/* 0xFFFC42F0 - 0xFFFC42F4 *//* INTC1レジスタの仮想化関連ビット機能を有効にするレジスタ */

}Reg_Intc1cpu0_Type;

/* 割り込み制御1(CPU1) */
typedef struct
{
	union
	{
		U2		u2Data;
		U1		u1Data[2];
		struct
		{
			U2		b4EIP		:4;		/* 割り込み優先度 */
			U2		b1Dummy1	:1;		/* 予約ビット */
			U2		xEIOV		:1;		/* 割り込みオーバーフロー */
			U2		xEITB		:1;		/* 割り込みベクタ方式選択ビット */
			U2		xEIMK		:1;		/* 割り込みマスクビット */
			U2		b4Dummy2	:4;		/* 予約ビット */
			U2		xEIRF		:1;		/* 割り込み要求フラグ */
			U2		b2Dummy3	:2;		/* 予約ビット */
			U2		xEICT		:1;		/* 割り込みチャネルタイプビット */
		}stBit;
	}unEIC[INTC_INTC1_CH_NUM];								/* 0xFFFC8000 - 0xFFFC8040 *//* EI レベル割り込み制御レジスタ */

	U1	u1Dummy_FFFC8040[0xFFFC80F0U - 0xFFFC8040U];			/* 0xFFFC8040 - 0xFFFC80F0 */

	union
	{
		U4		u4Data;
		U2		u2Data[2];
		U1		u1Data[4];
	}unIMR0;												/* 0xFFFC80F0 - 0xFFFC80F4 *//* EI レベル割り込みマスクレジスタ */

	U1	u1Dummy_FFFC80F4[0xFFFC8100U - 0xFFFC80F4U];			/* 0xFFFC80F4 - 0xFFFC8100 */

	union
	{
		U4		u4Data;
		U2		u2Data[2];
		U1		u1Data[4];
		struct
		{
			U4		b3PEID		:3;		/* 割り込みバインド（要求）指定 */
			U4		b5Dummy1	:5;		/* 予約ビット */
			U4		b3GPID		:3;		/* GPIDの指定（仮想化機能が有効の場合のみ書き込み可） */
			U4		b4Dummy2	:4;		/* 予約ビット */
			U4		b1GM		:1;		/* ゲストモード選択ビット（仮想化機能が有効の場合のみ書き込み可） */
			U4		b16Dummy3	:16;	/* 予約ビット */
		}stBit;
	}unEIBD[INTC_INTC1_CH_NUM];								/* 0xFFFC8100 - 0xFFFC8180 *//* EI レベル割り込みバインドレジスタ */

	U1	u1Dummy_FFFC8180[0xFFFC81C0U - 0xFFFC8180U];			/* 0xFFFC8180 - 0xFFFC81C0 */

	union
	{
		U4		u4Data;
		U2		u2Data[2];
		U1		u1Data[4];
		struct
		{
			U4		b3PEID		:3;		/* 割り込みバインド（要求）指定 */
			U4		b5Dummy1	:5;		/* 予約ビット */
			U4		b3GPID		:3;		/* GPIDの指定（仮想化機能が有効の場合のみ書き込み可） */
			U4		b4Dummy2	:4;		/* 予約ビット */
			U4		b1GM		:1;		/* ゲストモード選択ビット（仮想化機能が有効の場合のみ書き込み可） */
			U4		b16Dummy3	:16;	/* 予約ビット */
		}stBit;
	}unFIBD;								/* 0xFFFC81C0 - 0xFFFC81C4 *//* FE レベル割込みバインドレジスタ */

	U1	u1Dummy_FFFC81C4[0xFFFC8200U - 0xFFFC81C4U];			/* 0xFFFC81C4 - 0xFFFC8200 */

	union
	{
		U4		u4Data;
		U2		u2Data[2];
		U1		u1Data[4];
		struct
		{
			U4		b6EIP		:6;		/* 割り込み優先度(64段階) */
			U4		b9Dummy1	:9;		/* 予約ビット */
			U4		b1EIOV		:1;		/* 割り込みオーバーフロー */
			U4		b6Dummy2	:6;		/* 予約ビット */
			U4		b1EITB		:1;		/* 割り込みベクタ方式選択ビット */
			U4		b1EIMK		:1;		/* 割り込みマスクビット */
			U4		b4Dummy3	:4;		/* 予約ビット */
			U4		b1EIRF		:1;		/* 割り込み要求フラグ */
			U4		b2Dummy4	:2;		/* 予約ビット */
			U4		b1EICT		:1;		/* 割り込みチャネルタイプビット */
		}stBit;
	}unEEIC[INTC_INTC1_CH_NUM];								/* 0xFFFC8200 - 0xFFFC8280 *//* EI レベル割り込み制御拡張レジスタ */

	union
	{
		U4		u4Data;
		U2		u2Data[2];
		U1		u1Data[4];
		struct
		{
			U4		b6BGPR		:6;		/* 優先度閾値 */
			U4		b26Dummy1	:26;	/*予約ビット*/
		}stBit;
	}unEIBG;								/* 0xFFFC8280 - 0xFFFC8284 *//* バックグラウンドゲスト要求のための優先度閾値を構成するレジスタ */
                                                                         /* 仮想化機能が有効でない場合、Reservedとして扱う*/

	U1	u1Dummy_FFFC8284[0xFFFC82C0U - 0xFFFC8284U];			/* 0xFFFC8284 - 0xFFFC82C0 */

	union
	{
		U4		u4Data;
		U2		u2Data[2];
		U1		u1Data[4];
		struct
		{
			U4		b1BGE		:1;		/* FEレベル割込みのバックグラウンドゲスト使用可否ビット */
			U4		b31Dummy1	:31;	/*予約ビット*/
		}stBit;
	}unFIBG;								/* 0xFFFC82C0 - 0xFFFC82C4 *//* バックグラウンドゲスト使用可否レジスタ */
                                                                         /* 仮想化機能が有効でない場合、Reservedとして扱う*/

	U1	u1Dummy_FFFC82C4[0xFFFC82F0U - 0xFFFC82C4U];			/* 0xFFFC82C4 - 0xFFFC82F0 */

	union
	{
		U4		u4Data;
		U2		u2Data[2];
		U1		u1Data[4];
		struct
		{
			U4		b1IHVE		:1;		/* 仮想化機能の有効ビット */
			U4		b31Dummy1	:31;	/*予約ビット*/
		}stBit;
	}unIHVCFG;								/* 0xFFFC82F0 - 0xFFFC82F4 *//* INTC1レジスタの仮想化関連ビット機能を有効にするレジスタ */

}Reg_Intc1cpu1_Type;


/* 割り込み制御1(CPU2) */
typedef struct
{
	union
	{
		U2		u2Data;
		U1		u1Data[2];
		struct
		{
			U2		b4EIP		:4;		/* 割り込み優先度 */
			U2		b1Dummy1	:1;		/* 予約ビット */
			U2		xEIOV		:1;		/* 割り込みオーバーフロー */
			U2		xEITB		:1;		/* 割り込みベクタ方式選択ビット */
			U2		xEIMK		:1;		/* 割り込みマスクビット */
			U2		b4Dummy2	:4;		/* 予約ビット */
			U2		xEIRF		:1;		/* 割り込み要求フラグ */
			U2		b2Dummy3	:2;		/* 予約ビット */
			U2		xEICT		:1;		/* 割り込みチャネルタイプビット */
		}stBit;
	}unEIC[INTC_INTC1_CH_NUM];								/* 0xFFFCC000 - 0xFFFCC040 *//* EI レベル割り込み制御レジスタ */

	U1	u1Dummy_FFFCC040[0xFFFCC0F0U - 0xFFFCC040U];			/* 0xFFFCC040 - 0xFFFCC0F0 */

	union
	{
		U4		u4Data;
		U2		u2Data[2];
		U1		u1Data[4];
	}unIMR0;												/* 0xFFFCC0F0 - 0xFFFCC0F4 *//* EI レベル割り込みマスクレジスタ */

	U1	u1Dummy_FFFCC0F4[0xFFFCC100U - 0xFFFCC0F4U];			/* 0xFFFCC0F4 - 0xFFFCC100 */

	union
	{
		U4		u4Data;
		U2		u2Data[2];
		U1		u1Data[4];
		struct
		{
			U4		b3PEID		:3;		/* 割り込みバインド（要求）指定 */
			U4		b5Dummy1	:5;		/* 予約ビット */
			U4		b3GPID		:3;		/* GPIDの指定（仮想化機能が有効の場合のみ書き込み可） */
			U4		b4Dummy2	:4;		/* 予約ビット */
			U4		b1GM		:1;		/* ゲストモード選択ビット（仮想化機能が有効の場合のみ書き込み可） */
			U4		b16Dummy3	:16;	/* 予約ビット */
		}stBit;
	}unEIBD[INTC_INTC1_CH_NUM];								/* 0xFFFCC100 - 0xFFFCC180 *//* EI レベル割り込みバインドレジスタ */

	U1	u1Dummy_FFFCC180[0xFFFCC1C0U - 0xFFFCC180U];			/* 0xFFFCC180 - 0xFFFCC1C0 */

	union
	{
		U4		u4Data;
		U2		u2Data[2];
		U1		u1Data[4];
		struct
		{
			U4		b3PEID		:3;		/* 割り込みバインド（要求）指定 */
			U4		b5Dummy1	:5;		/* 予約ビット */
			U4		b3GPID		:3;		/* GPIDの指定（仮想化機能が有効の場合のみ書き込み可） */
			U4		b4Dummy2	:4;		/* 予約ビット */
			U4		b1GM		:1;		/* ゲストモード選択ビット（仮想化機能が有効の場合のみ書き込み可） */
			U4		b16Dummy3	:16;	/* 予約ビット */
		}stBit;
	}unFIBD;								/* 0xFFFCC1C0 - 0xFFFCC1C4 *//* FE レベル割込みバインドレジスタ */

	U1	u1Dummy_FFFCC1C4[0xFFFCC200U - 0xFFFCC1C4U];			/* 0xFFFCC1C4 - 0xFFFCC200 */

	union
	{
		U4		u4Data;
		U2		u2Data[2];
		U1		u1Data[4];
		struct
		{
			U4		b6EIP		:6;		/* 割り込み優先度(64段階) */
			U4		b9Dummy1	:9;		/* 予約ビット */
			U4		b1EIOV		:1;		/* 割り込みオーバーフロー */
			U4		b6Dummy2	:6;		/* 予約ビット */
			U4		b1EITB		:1;		/* 割り込みベクタ方式選択ビット */
			U4		b1EIMK		:1;		/* 割り込みマスクビット */
			U4		b4Dummy3	:4;		/* 予約ビット */
			U4		b1EIRF		:1;		/* 割り込み要求フラグ */
			U4		b2Dummy4	:2;		/* 予約ビット */
			U4		b1EICT		:1;		/* 割り込みチャネルタイプビット */
		}stBit;
	}unEEIC[INTC_INTC1_CH_NUM];								/* 0xFFFCC200 - 0xFFFCC280 *//* EI レベル割り込み制御拡張レジスタ */

	union
	{
		U4		u4Data;
		U2		u2Data[2];
		U1		u1Data[4];
		struct
		{
			U4		b6BGPR		:6;		/* 優先度閾値 */
			U4		b26Dummy1	:26;	/*予約ビット*/
		}stBit;
	}unEIBG;								/* 0xFFFCC280 - 0xFFFCC284 *//* バックグラウンドゲスト要求のための優先度閾値を構成するレジスタ */
                                                                         /* 仮想化機能が有効でない場合、Reservedとして扱う*/

	U1	u1Dummy_FFFCC284[0xFFFCC2C0U - 0xFFFCC284U];			/* 0xFFFCC284 - 0xFFFCC2C0 */

	union
	{
		U4		u4Data;
		U2		u2Data[2];
		U1		u1Data[4];
		struct
		{
			U4		b1BGE		:1;		/* FEレベル割込みのバックグラウンドゲスト使用可否ビット */
			U4		b31Dummy1	:31;	/*予約ビット*/
		}stBit;
	}unFIBG;								/* 0xFFFCC2C0 - 0xFFFCC2C4 *//* バックグラウンドゲスト使用可否レジスタ */
                                                                         /* 仮想化機能が有効でない場合、Reservedとして扱う*/

	U1	u1Dummy_FFFCC2C4[0xFFFCC2F0U - 0xFFFCC2C4U];			/* 0xFFFCC2C4 - 0xFFFCC2F0 */

	union
	{
		U4		u4Data;
		U2		u2Data[2];
		U1		u1Data[4];
		struct
		{
			U4		b1IHVE		:1;		/* 仮想化機能の有効ビット */
			U4		b31Dummy1	:31;	/*予約ビット*/
		}stBit;
	}unIHVCFG;								/* 0xFFFCC2F0 - 0xFFFCC2F4 *//* INTC1レジスタの仮想化関連ビット機能を有効にするレジスタ */

}Reg_Intc1cpu2_Type;


/* 割り込み制御1(CPU3) */
typedef struct
{
	union
	{
		U2		u2Data;
		U1		u1Data[2];
		struct
		{
			U2		b4EIP		:4;		/* 割り込み優先度 */
			U2		b1Dummy1	:1;		/* 予約ビット */
			U2		xEIOV		:1;		/* 割り込みオーバーフロー */
			U2		xEITB		:1;		/* 割り込みベクタ方式選択ビット */
			U2		xEIMK		:1;		/* 割り込みマスクビット */
			U2		b4Dummy2	:4;		/* 予約ビット */
			U2		xEIRF		:1;		/* 割り込み要求フラグ */
			U2		b2Dummy3	:2;		/* 予約ビット */
			U2		xEICT		:1;		/* 割り込みチャネルタイプビット */
		}stBit;
	}unEIC[INTC_INTC1_CH_NUM];								/* 0xFFFD0000 - 0xFFFD0040 *//* EI レベル割り込み制御レジスタ */

	U1	u1Dummy_FFFD0040[0xFFFD00F0U - 0xFFFD0040U];			/* 0xFFFD0040 - 0xFFFD00F0 */

	union
	{
		U4		u4Data;
		U2		u2Data[2];
		U1		u1Data[4];
	}unIMR0;												/* 0xFFFD00F0 - 0xFFFD00F4 *//* EI レベル割り込みマスクレジスタ */

	U1	u1Dummy_FFFD00F4[0xFFFD0100U - 0xFFFD00F4U];			/* 0xFFFD00F4 - 0xFFFD0100 */

	union
	{
		U4		u4Data;
		U2		u2Data[2];
		U1		u1Data[4];
		struct
		{
			U4		b3PEID		:3;		/* 割り込みバインド（要求）指定 */
			U4		b5Dummy1	:5;		/* 予約ビット */
			U4		b3GPID		:3;		/* GPIDの指定（仮想化機能が有効の場合のみ書き込み可） */
			U4		b4Dummy2	:4;		/* 予約ビット */
			U4		b1GM		:1;		/* ゲストモード選択ビット（仮想化機能が有効の場合のみ書き込み可） */
			U4		b16Dummy3	:16;	/* 予約ビット */
		}stBit;
	}unEIBD[INTC_INTC1_CH_NUM];								/* 0xFFFD0100 - 0xFFFD0180 *//* EI レベル割り込みバインドレジスタ */

	U1	u1Dummy_FFFD0180[0xFFFD01C0U - 0xFFFD0180U];			/* 0xFFFD0180 - 0xFFFD01C0 */

	union
	{
		U4		u4Data;
		U2		u2Data[2];
		U1		u1Data[4];
		struct
		{
			U4		b3PEID		:3;		/* 割り込みバインド（要求）指定 */
			U4		b5Dummy1	:5;		/* 予約ビット */
			U4		b3GPID		:3;		/* GPIDの指定（仮想化機能が有効の場合のみ書き込み可） */
			U4		b4Dummy2	:4;		/* 予約ビット */
			U4		b1GM		:1;		/* ゲストモード選択ビット（仮想化機能が有効の場合のみ書き込み可） */
			U4		b16Dummy3	:16;	/* 予約ビット */
		}stBit;
	}unFIBD;								/* 0xFFFD01C0 - 0xFFFD01C4 *//* FE レベル割込みバインドレジスタ */

	U1	u1Dummy_FFFD01C4[0xFFFD0200U - 0xFFFD01C4U];			/* 0xFFFD01C4 - 0xFFFD0200 */

	union
	{
		U4		u4Data;
		U2		u2Data[2];
		U1		u1Data[4];
		struct
		{
			U4		b6EIP		:6;		/* 割り込み優先度(64段階) */
			U4		b9Dummy1	:9;		/* 予約ビット */
			U4		b1EIOV		:1;		/* 割り込みオーバーフロー */
			U4		b6Dummy2	:6;		/* 予約ビット */
			U4		b1EITB		:1;		/* 割り込みベクタ方式選択ビット */
			U4		b1EIMK		:1;		/* 割り込みマスクビット */
			U4		b4Dummy3	:4;		/* 予約ビット */
			U4		b1EIRF		:1;		/* 割り込み要求フラグ */
			U4		b2Dummy4	:2;		/* 予約ビット */
			U4		b1EICT		:1;		/* 割り込みチャネルタイプビット */
		}stBit;
	}unEEIC[INTC_INTC1_CH_NUM];								/* 0xFFFD0200 - 0xFFFD0280 *//* EI レベル割り込み制御拡張レジスタ */

	union
	{
		U4		u4Data;
		U2		u2Data[2];
		U1		u1Data[4];
		struct
		{
			U4		b6BGPR		:6;		/* 優先度閾値 */
			U4		b26Dummy1	:26;	/*予約ビット*/
		}stBit;
	}unEIBG;								/* 0xFFFD0280 - 0xFFFD0284 *//* バックグラウンドゲスト要求のための優先度閾値を構成するレジスタ */
                                                                         /* 仮想化機能が有効でない場合、Reservedとして扱う*/

	U1	u1Dummy_FFFD0284[0xFFFD02C0U - 0xFFFD0284U];			/* 0xFFFD0284 - 0xFFFD02C0 */

	union
	{
		U4		u4Data;
		U2		u2Data[2];
		U1		u1Data[4];
		struct
		{
			U4		b1BGE		:1;		/* FEレベル割込みのバックグラウンドゲスト使用可否ビット */
			U4		b31Dummy1	:31;	/*予約ビット*/
		}stBit;
	}unFIBG;								/* 0xFFFD02C0 - 0xFFFD02C4 *//* バックグラウンドゲスト使用可否レジスタ */
                                                                         /* 仮想化機能が有効でない場合、Reservedとして扱う*/

	U1	u1Dummy_FFFD02C4[0xFFFD02F0U - 0xFFFD02C4U];			/* 0xFFFD02C4 - 0xFFFD02F0 */

	union
	{
		U4		u4Data;
		U2		u2Data[2];
		U1		u1Data[4];
		struct
		{
			U4		b1IHVE		:1;		/* 仮想化機能の有効ビット */
			U4		b31Dummy1	:31;	/*予約ビット*/
		}stBit;
	}unIHVCFG;								/* 0xFFFD02F0 - 0xFFFD02F4 *//* INTC1レジスタの仮想化関連ビット機能を有効にするレジスタ */

}Reg_Intc1cpu3_Type;


/* 割り込み制御2 */
typedef struct
{

	union
	{
		U2		u2Data;
		U1		u1Data[2];
		struct
		{
			U2		b4EIP		:4;		/* 割り込み優先度 */
			U2		b1Dummy1	:1;		/* 予約ビット */
			U2		xEIOV		:1;		/* 割り込みオーバーフロー */
			U2		xEITB		:1;		/* 割り込みベクタ方式選択ビット */
			U2		xEIMK		:1;		/* 割り込みマスクビット */
			U2		b4Dummy2	:4;		/* 予約ビット */
			U2		xEIRF		:1;		/* 割り込み要求フラグ */
			U2		b2Dummy3	:2;		/* 予約ビット */
			U2		xEICT		:1;		/* 割り込みチャネルタイプビット */
		}stBit;
	}unEIC[INTC_CH_NUM];			/* 0 - 31はdummy定義：アクセス禁止 */	/* 0xFFF80000 - 0xFFF80600 *//* EI レベル割り込み制御レジスタ */

	U1	u1Dummy_FFF80600[0xFFF81000U - 0xFFF80600U];							/* 0xFFF80600 - 0xFFF81000 */

	union
	{
		U4		u4Data;
		U2		u2Data[2];
		U1		u1Data[4];
	}unIMR[INTC_IMR_REG_NUM];		/* 0はdummy定義：アクセス禁止 */		/* 0xFFF81000 - 0xFFF81060 */

	U1	u1Dummy_FFF81080[0xFFF81FE0U - 0xFFF81060U];							/* 0xFFF81060 - 0xFFF81FE0 */

 	union
	{
		U4		u4Data;
		U2		u2Data[2];
		U1		u1Data[4];
		struct
		{
			U4		b6BGPR		:6;		/* 優先度閾値 (IntC1cpu0 EIBG.BGPRと同じ値に設定)*/
			U4		b26Dummy1	:26;	/*予約ビット*/
		}stBit;
	}unI2EIBG0;								/* 0xFFF81FE0 - 0xFFF81FE4 *//* PE0 バックグラウンドゲスト要求のための優先度閾値を構成するレジスタ */

 	union
	{
		U4		u4Data;
		U2		u2Data[2];
		U1		u1Data[4];
		struct
		{
			U4		b6BGPR		:6;		/* 優先度閾値 (IntC1cpu1 EIBG.BGPRと同じ値に設定)*/
			U4		b26Dummy1	:26;	/*予約ビット*/
		}stBit;
	}unI2EIBG1;								/* 0xFFF81FE4 - 0xFFF81FE8 *//* PE1 バックグラウンドゲスト要求のための優先度閾値を構成するレジスタ */

 	union
	{
		U4		u4Data;
		U2		u2Data[2];
		U1		u1Data[4];
		struct
		{
			U4		b6BGPR		:6;		/* 優先度閾値 (IntC1cpu2 EIBG.BGPRと同じ値に設定)*/
			U4		b26Dummy1	:26;	/*予約ビット*/
		}stBit;
	}unI2EIBG2;								/* 0xFFF81FE8 - 0xFFF81FEC *//* PE2 バックグラウンドゲスト要求のための優先度閾値を構成するレジスタ */

 	union
	{
		U4		u4Data;
		U2		u2Data[2];
		U1		u1Data[4];
		struct
		{
			U4		b6BGPR		:6;		/* 優先度閾値 (IntC1cpu3 EIBG.BGPRと同じ値に設定)*/
			U4		b26Dummy1	:26;	/*予約ビット*/
		}stBit;
	}unI2EIBG3;								/* 0xFFF81FEC - 0xFFF81FF0 *//* PE3 バックグラウンドゲスト要求のための優先度閾値を構成するレジスタ */

	U1	u1Dummy_FFF81FF0[0xFFF82000U - 0xFFF81FF0U];							/* 0xFFF81FF0 - 0xFFF82000 */

	union
	{
		U4		u4Data;
		U2		u2Data[2];
		U1		u1Data[4];
		struct
		{
			U4		b3PEID		:3;		/* 割り込みバインド（要求）指定 */
			U4		b5Dummy1	:5;		/* 予約ビット */
			U4		b3GPID		:3;		/* GPIDの指定（仮想化機能が有効の場合のみ書き込み可） */
			U4		b4Dummy2	:4;		/* 予約ビット */
			U4		b1GM		:1;		/* ゲストモード選択ビット（仮想化機能が有効の場合のみ書き込み可） */
			U4		b8Dummy3	:8;		/* 予約ビット */
			U4		b2BCP		:2;		/* ブロードキャスト 割り込み番号設定 */
			U4		b5Dummy4	:5;		/* 予約ビット */
			U4		b1CST		:1;		/* ブロードキャスト 割り込み */
		}stBit;
	}
	unEIBD[INTC_CH_NUM];			/* 0 - 31はdummy定義：アクセス禁止 *//* 0xFFF82000 - 0xFFF82C00 *//* EIレベル割込みバインドレジスタ */

	U1	u1Dummy_FFF82C00[0xFFF84000U - 0xFFF82C00U];							/* 0xFFF82C00 - 0xFFF84000 */

	union
	{
		U4		u4Data;
		U2		u2Data[2];
		U1		u1Data[4];
		struct
		{
			U4		b6EIP		:6;		/* 割り込み優先度(64段階) */
			U4		b9Dummy1	:9;		/* 予約ビット */
			U4		b1EIOV		:1;		/* 割り込みオーバーフロー */
			U4		b6Dummy2	:6;		/* 予約ビット */
			U4		b1EITB		:1;		/* 割り込みベクタ方式選択ビット */
			U4		b1EIMK		:1;		/* 割り込みマスクビット */
			U4		b4Dummy3	:4;		/* 予約ビット */
			U4		b1EIRF		:1;		/* 割り込み要求フラグ */
			U4		b2Dummy4	:2;		/* 予約ビット */
			U4		b1EICT		:1;		/* 割り込みチャネルタイプビット */
		}stBit;
	}unEEIC[INTC_CH_NUM];			/* 0 - 31はdummy定義：アクセス禁止 *//* 0xFFF84000 - 0xFFF85000 *//* 拡張EIレベル割り込み制御レジスタ */

}Reg_Intc2_Type;

/* FEレベルノンマスカブル割込み制御 */
typedef	struct
{
	union
	{
		U4		u4Data;
		struct
		{
			U4		b1NMIF		:1;		/* 外部 FEレベルノンマスカブル割込み発生フラグ */
			U4		b31Dummy1	:31;	/* 予約ビット */
		}stBit;
	}unFENMIF;									/* 0xFF9A3A00 - 0xFF9A3A04 *//* FEレベルノンマスカブル割込みステータスレジスタ */

	U1	u1Dummy_FFC00021[0xFF9A3A08U - 0xFF9A3A04U];	/* 0xFF9A3A08 - 0xFF9A3A04 */

	union
	{
		U4	u4Data;
		struct
		{
			U4		b1NMIC		:1;		/* 外部 FEレベルノンマスカブル割込みフラグクリア */
			U4		b31Dummy1	:31;	/* 予約ビット */
		}stBit;
	}unFENMIC;									/* 0xFF9A3A08 - 0xFF9A3A0C *//* FEレベルノンマスカブル割込みフラグクリアレジスタ */

}Reg_Fenc_Type;

/* CPU0 FEレベルマスカブル割込み制御 */
typedef	struct
{
	union
	{
		U4		u4Data;
		struct
		{
			U4		b1SWDTFEINTF		:1;		/* Secure WDT overflow割込みステータス */
			U4		b1TPTMFEINTF		:1;		/* PEx Time Protection Timer割込みステータス */
			U4		b1ECMFEINTF			:1;		/* PEx ECM割込みステータス */
			U4		b29Dummy1			:29;	/* 予約ビット */
		}stBit;
	}unFEINTF;									/* 0xFF9A3B00 - 0xFF9A3B04 *//* PE0 FEレベルマスカブル割込みステータスレジスタ */

	union
	{
		U4		u4Data;
		struct
		{
			U4		b1SWDTFEINTMSK		:1;		/* Secure WDT overflow割込みのマスク */
			U4		b1TPTMFEINTMSK		:1;		/* PEx Time Protection Timer割込みのマスク */
			U4		b1ECMFEINTMSK		:1;		/* PEx ECM割込みステータスのマスク */
			U4		b29Dummy1			:29;	/* 予約ビット */
		}stBit;
	}unFEINTMSK;									/* 0xFF9A3B04 - 0xFF9A3B08 *//* PE0 FEレベルマスカブル割込み マスクレジスタ */

	union
	{
		U4		u4Data;
		struct
		{
			U4		b1SWDTFEINTC		:1;		/* Secure WDT overflow割込みステータスクリア */
			U4		b1TPTMFEINTC		:1;		/* PEx Time Protection Timer割込みステータスクリア */
			U4		b1ECMFEINTC			:1;		/* PEx ECM割込みステータスクリア */
			U4		b29Dummy1			:29;	/* 予約ビット */
		}stBit;
	}unFEINTC ;									/* 0xFF9A3B08 - 0xFF9A3B0C *//* PE0 FEレベルマスカブル割込みステータスクリアレジスタ */

}Reg_Feinccpu0_Type;


/* CPU1 FEレベルマスカブル割込み制御 */
typedef	struct
{
	union
	{
		U4		u4Data;
		struct
		{
			U4		b1SWDTFEINTF		:1;		/* Secure WDT overflow割込みステータス */
			U4		b1TPTMFEINTF		:1;		/* PEx Time Protection Timer割込みステータス */
			U4		b1ECMFEINTF			:1;		/* PEx ECM割込みステータス */
			U4		b29Dummy1			:29;	/* 予約ビット */
		}stBit;
	}unFEINTF;									/* 0xFF9A3C00 - 0xFF9A3C04 *//* PE1 FEレベルマスカブル割込みステータスレジスタ */

	union
	{
		U4		u4Data;
		struct
		{
			U4		b1SWDTFEINTMSK		:1;		/* Secure WDT overflow割込みのマスク */
			U4		b1TPTMFEINTMSK		:1;		/* PEx Time Protection Timer割込みのマスク */
			U4		b1ECMFEINTMSK		:1;		/* PEx ECM割込みステータスのマスク */
			U4		b29Dummy1			:29;	/* 予約ビット */
		}stBit;
	}unFEINTMSK;								/* 0xFF9A3C04 - 0xFF9A3C08 *//* PE1 FEレベルマスカブル割込み マスクレジスタ */

	union
	{
		U4		u4Data;
		struct
		{
			U4		b1SWDTFEINTC		:1;		/* Secure WDT overflow割込みステータスクリア */
			U4		b1TPTMFEINTC		:1;		/* PEx Time Protection Timer割込みステータスクリア */
			U4		b1ECMFEINTC			:1;		/* PEx ECM割込みステータスクリア */
			U4		b29Dummy1			:29;	/* 予約ビット */
		}stBit;
	}unFEINTC ;									/* 0xFF9A3C08 - 0xFF9A3C0C *//* PE1 FEレベルマスカブル割込みステータスクリアレジスタ */

}Reg_Feinccpu1_Type;


/* CPU2 FEレベルマスカブル割込み制御 */
typedef	struct
{
	union
	{
		U4		u4Data;
		struct
		{
			U4		b1SWDTFEINTF		:1;		/* Secure WDT overflow割込みステータス */
			U4		b1TPTMFEINTF		:1;		/* PEx Time Protection Timer割込みステータス */
			U4		b1ECMFEINTF			:1;		/* PEx ECM割込みステータス */
			U4		b29Dummy1			:29;	/* 予約ビット */
		}stBit;
	}unFEINTF;									/* 0xFF9A3D00 - 0xFF9A3D04 *//* PE2 FEレベルマスカブル割込みステータスレジスタ */

	union
	{
		U4		u4Data;
		struct
		{
			U4		b1SWDTFEINTMSK		:1;		/* Secure WDT overflow割込みのマスク */
			U4		b1TPTMFEINTMSK		:1;		/* PEx Time Protection Timer割込みのマスク */
			U4		b1ECMFEINTMSK		:1;		/* PEx ECM割込みステータスのマスク */
			U4		b29Dummy1			:29;	/* 予約ビット */
		}stBit;
	}unFEINTMSK;								/* 0xFF9A3D04 - 0xFF9A3D08 *//* PE2 FEレベルマスカブル割込み マスクレジスタ */

	union
	{
		U4		u4Data;
		struct
		{
			U4		b1SWDTFEINTC		:1;		/* Secure WDT overflow割込みステータスクリア */
			U4		b1TPTMFEINTC		:1;		/* PEx Time Protection Timer割込みステータスクリア */
			U4		b1ECMFEINTC			:1;		/* PEx ECM割込みステータスクリア */
			U4		b29Dummy1			:29;	/* 予約ビット */
		}stBit;
	}unFEINTC ;									/* 0xFF9A3D08 - 0xFF9A3D0C *//* PE2 FEレベルマスカブル割込みステータスクリアレジスタ */

}Reg_Feinccpu2_Type;

/* CPU3 FEレベルマスカブル割込み制御 */
typedef	struct
{
	union
	{
		U4		u4Data;
		struct
		{
			U4		b1SWDTFEINTF		:1;		/* Secure WDT overflow割込みステータス */
			U4		b1TPTMFEINTF		:1;		/* PEx Time Protection Timer割込みステータス */
			U4		b1ECMFEINTF			:1;		/* PEx ECM割込みステータス */
			U4		b29Dummy1			:29;	/* 予約ビット */
		}stBit;
	}unFEINTF;									/* 0xFF9A3E00 - 0xFF9A3E04 *//* PE3 FEレベルマスカブル割込みステータスレジスタ */

	union
	{
		U4		u4Data;
		struct
		{
			U4		b1SWDTFEINTMSK		:1;		/* Secure WDT overflow割込みのマスク */
			U4		b1TPTMFEINTMSK		:1;		/* PEx Time Protection Timer割込みのマスク */
			U4		b1ECMFEINTMSK		:1;		/* PEx ECM割込みステータスのマスク */
			U4		b29Dummy1			:29;	/* 予約ビット */
		}stBit;
	}unFEINTMSK;								/* 0xFF9A3E04 - 0xFF9A3E08 *//* PE3 FEレベルマスカブル割込み マスクレジスタ */

	union
	{
		U4		u4Data;
		struct
		{
			U4		b1SWDTFEINTC		:1;		/* Secure WDT overflow割込みステータスクリア */
			U4		b1TPTMFEINTC		:1;		/* PEx Time Protection Timer割込みステータスクリア */
			U4		b1ECMFEINTC			:1;		/* PEx ECM割込みステータスクリア */
			U4		b29Dummy1			:29;	/* 予約ビット */
		}stBit;
	}unFEINTC ;									/* 0xFF9A3E08 - 0xFF9A3E0C *//* PE3 FEレベルマスカブル割込みステータスクリアレジスタ */

}Reg_Feinccpu3_Type;

/*==============================================================================================*/
/*	register BIT definition																		*/
/*==============================================================================================*/
/* EIC */
#define		INTC_EIC_EICT				(BIT15)		/* 割り込みチャネルタイプビット */
	#define		INTC_EIC_EICT_EDGE			(0)		/* エッジ検出 */
	#define		INTC_EIC_EICT_LEVEL			(1)		/* レベル検出 */
#define		INTC_EIC_EIRF				(BIT12)		/* 割り込み要求フラグ */
	#define		INTC_EIC_EIRF_NOINT			(0)		/* 割り込み要求なし（初期値） */
	#define		INTC_EIC_EIRF_INTREQ		(1)		/* 割り込み要求あり */
#define		INTC_EIC_EIMK				(BIT7)		/* 割り込みマスクビット */
	#define		INTC_EIC_EIMK_ENABLE		(0)		/* 割り込み処理を許可 */
	#define		INTC_EIC_EIMK_DISABLE		(1)		/* 割り込み処理を禁止（初期値） */
#define		INTC_EIC_EITB				(BIT6)		/* 割り込みベクタ方式選択ビット */
	#define		INTC_EIC_EITB_DIRECT		(0)		/* 優先度に基づいた直接分岐方式 */
	#define		INTC_EIC_EITB_TABLE			(1)		/* テーブル参照方式 */
#define		INTC_EIC_EIOV				(BIT5)		/* 割り込みオーバーフロービット */
	#define		INTC_EIC_EIOV_NO_OVERFLOW		(0)		/* オーバーフローなし */
	#define		INTC_EIC_EIOV_OVERFLOW		(1)		/* 割込みオーバーフロー検出(エッジ検出時) */
#define		INTC_EIC_EIP				(BIT3 + BIT2 + BIT1 + BIT0)		/* 16 レベルの割り込み優先度 */
	#define		INTC_EIC_EIP_LEVEL15	(0x0FU)		/* 割り込み優先度レベル15 */
#define		INTC_EIC_EIP_0				(BIT0)

/* IMR */
#define		INTC_IMR_EIMK31				(BIT31)		/* EIレベル割り込みマスク31 */
#define		INTC_IMR_EIMK30				(BIT30)		/* EIレベル割り込みマスク30 */
#define		INTC_IMR_EIMK29				(BIT29)		/* EIレベル割り込みマスク29 */
#define		INTC_IMR_EIMK28				(BIT28)		/* EIレベル割り込みマスク28 */
#define		INTC_IMR_EIMK27				(BIT27)		/* EIレベル割り込みマスク27 */
#define		INTC_IMR_EIMK26				(BIT26)		/* EIレベル割り込みマスク26 */
#define		INTC_IMR_EIMK25				(BIT25)		/* EIレベル割り込みマスク25 */
#define		INTC_IMR_EIMK24				(BIT24)		/* EIレベル割り込みマスク24 */
#define		INTC_IMR_EIMK23				(BIT23)		/* EIレベル割り込みマスク23 */
#define		INTC_IMR_EIMK22				(BIT22)		/* EIレベル割り込みマスク22 */
#define		INTC_IMR_EIMK21				(BIT21)		/* EIレベル割り込みマスク21 */
#define		INTC_IMR_EIMK20				(BIT20)		/* EIレベル割り込みマスク20 */
#define		INTC_IMR_EIMK19				(BIT19)		/* EIレベル割り込みマスク19 */
#define		INTC_IMR_EIMK18				(BIT18)		/* EIレベル割り込みマスク18 */
#define		INTC_IMR_EIMK17				(BIT17)		/* EIレベル割り込みマスク17 */
#define		INTC_IMR_EIMK16				(BIT16)		/* EIレベル割り込みマスク16 */
#define		INTC_IMR_EIMK15				(BIT15)		/* EIレベル割り込みマスク15 */
#define		INTC_IMR_EIMK14				(BIT14)		/* EIレベル割り込みマスク14 */
#define		INTC_IMR_EIMK13				(BIT13)		/* EIレベル割り込みマスク13 */
#define		INTC_IMR_EIMK12				(BIT12)		/* EIレベル割り込みマスク12 */
#define		INTC_IMR_EIMK11				(BIT11)		/* EIレベル割り込みマスク11 */
#define		INTC_IMR_EIMK10				(BIT10)		/* EIレベル割り込みマスク10 */
#define		INTC_IMR_EIMK9				(BIT9)		/* EIレベル割り込みマスク9 */
#define		INTC_IMR_EIMK8				(BIT8)		/* EIレベル割り込みマスク8 */
#define		INTC_IMR_EIMK7				(BIT7)		/* EIレベル割り込みマスク7 */
#define		INTC_IMR_EIMK6				(BIT6)		/* EIレベル割り込みマスク6 */
#define		INTC_IMR_EIMK5				(BIT5)		/* EIレベル割り込みマスク5 */
#define		INTC_IMR_EIMK4				(BIT4)		/* EIレベル割り込みマスク4 */
#define		INTC_IMR_EIMK3				(BIT3)		/* EIレベル割り込みマスク3 */
#define		INTC_IMR_EIMK2				(BIT2)		/* EIレベル割り込みマスク2 */
#define		INTC_IMR_EIMK1				(BIT1)		/* EIレベル割り込みマスク1 */
#define		INTC_IMR_EIMK0				(BIT0)		/* EIレベル割り込みマスク0 */
	#define		INTC_IMR_EIMK_ENABLE		(0)		/* 割り込み許可 */
	#define		INTC_IMR_EIMK_DISABLE		(1)		/* 割り込み禁止 */

/* EIBD */
#define		INTC_EIBD_CST				(BIT31)					/* ブロードキャスト 割り込み許可 */
#define		INTC_EIBD_BCP				(BIT25 + BIT24)			/* ブロードキャスト 割り込み番号設定 */
#define		INTC_EIBD_BCP_0				(BIT24)
#define		INTC_EIBD_GM				(BIT15)					/* チャネルバインド指定 */
	#define		INTC_EIBD_HOST				(0)					/* ホストパーティションを指定*/
	#define		INTC_EIBD_GUEST				(1)					/* ゲストパーティションを指定*/
#define		INTC_EIBD_GPID				(BIT10 + BIT9 + BIT8)	/* GPID指定 */
#define		INTC_EIBD_GPID_8			(BIT8)
#define		INTC_EIBD_PEID				(BIT2 + BIT1 + BIT0)	/* 割り込みバインド（要求）指定 */
#define		INTC_EIBD_PEID_0			(BIT0)
	#define		INTC_EIBD_PEID_PE0			(0)					/* PE0に割り込みをバインド */
	#define		INTC_EIBD_PEID_PE1			(1)					/* PE1に割り込みをバインド */
	#define		INTC_EIBD_PEID_PE2			(2)					/* PE2に割り込みをバインド */
	#define		INTC_EIBD_PEID_PE3			(3)					/* PE3に割り込みをバインド */

/* FIBD */
#define		INTC_FIBD_GM				(BIT15)					/* チャネルバインド指定 */
	#define		INTC_FIBD_HOST				(0)					/* ホストパーティションを指定*/
	#define		INTC_FIBD_GUEST				(1)					/* ゲストパーティションを指定*/
#define		INTC_FIBD_GPID				(BIT10 + BIT9 + BIT8)	/* GPID指定 */
#define		INTC_FIBD_GPID_8			(BIT8)	
#define		INTC_FIBD_PEID				(BIT2 + BIT1 + BIT0)	/* 割り込みバインド（要求）指定 */
#define		INTC_FIBD_PEID_0			(BIT0)
	#define		INTC_FIBD_PEID_PE0			(0)					/* PE0に割り込みをバインド */
	#define		INTC_FIBD_PEID_PE1			(1)					/* PE1に割り込みをバインド */
	#define		INTC_FIBD_PEID_PE2			(2)					/* PE2に割り込みをバインド */
	#define		INTC_FIBD_PEID_PE3			(3)					/* PE3に割り込みをバインド */

/* EEIC */
#define		INTC_EEIC_EICT				(BIT31)		/* 割り込みチャネルタイプビット */
	#define		INTC_EEIC_EICT_EDGE			(0)		/* エッジ検出 */
	#define		INTC_EEIC_EICT_LEVEL		(1)		/* レベル検出 */
#define		INTC_EEIC_EIRF				(BIT28)		/* 割り込み要求フラグ */
	#define		INTC_EEIC_EIRF_NOINT		(0)		/* 割り込み要求なし（初期値） */
	#define		INTC_EEIC_EIRF_INTREQ		(1)		/* 割り込み要求あり */
#define		INTC_EEIC_EIMK				(BIT23)		/* 割り込みマスクビット */
	#define		INTC_EEIC_EIMK_ENABLE		(0)		/* 割り込み許可 */
	#define		INTC_EEIC_EIMK_DISABLE		(1)		/* 割り込み禁止 */
#define		INTC_EEIC_EITB				(BIT22)		/* 割り込みベクタ方式選択ビット */
	#define		INTC_EEIC_EITB_DIRECT		(0)		/* 優先度に基づいた直接分岐方式 */
	#define		INTC_EEIC_EITB_TABLE		(1)		/* テーブル参照方式 */
#define		INTC_EEIC_EIOV				(BIT15)		/* 割り込みオーバーフロービット */
	#define		INTC_EEIC_EIOV_DISABLE		(0)		/* オーバーフローなし */
	#define		INTC_EEIC_EIOV_ENABLE		(1)		/* 割込みオーバーフロー検出(エッジ検出時) */
#define		INTC_EEIC_EIP				(BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)		/* 64 レベルの割り込み優先度 */
#define		INTC_EEIC_EIP_0				(BIT0)
	#define		INTC_EEIC_EIP_LEVEL15	(0x0FU)		/* 割り込み優先度レベル15 */
	#define		INTC_EEIC_EIP_LEVEL63	(0x3FU)		/* 割り込み優先度レベル63 */

/* IHVCFG */
#define		INTC_IHVCFG_IHVE			(BIT0)		/* IntC1レジスタ仮想化機能ビット */

/* EIBG */
#define		INTC_EIBG_BGPR				(BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)		/* 優先度閾値設定 */
#define		INTC_EIBG_BGPR_0			(BIT0)	

/* I2EIBG */
#define		INTC_I2EIBG_BGPR			(BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)		/* 優先度閾値設定 */
#define		INTC_I2EIBG_BGPR_0			(BIT0)

/* FIBG */
#define		INTC_FIBG_BGE				(BIT0)		/* FEレベル割込みのバックグラウンドゲスト使用可否ビット */
	#define		INTC_FIBG_BGE_NOTALLOW		(0)		/* バックグラウンドゲスト使用不可 */
	#define		INTC_FIBG_BGE_ALLOW			(1)		/* バックグラウンドゲスト使用許可(仮想化機能有効時のみ) */

/* SINTR */
#define		INTC_SINTR_INCREMENTS		(0x01)		/* カウンタをインクリメント */
#define		INTC_SINTR_DECREMENTS		(0x00)		/* カウンタをデクリメント */

/* PINT */
#define		INTC_PINT_REGNO_TCI0_31			(0)		/* PINT レジスタCH0 */
#define		INTC_PINT_REGNO_TCI32_63		(1)		/* PINT レジスタCH1 */
#define		INTC_PINT_REGNO_TCI64_95		(2)		/* PINT レジスタCH2 */
#define		INTC_PINT_REGNO_TCI96_127		(3)		/* PINT レジスタCH3 */
#define		INTC_PINT_REGNO_CCI0_31			(4)		/* PINT レジスタCH4 */
#define		INTC_PINT_REGNO_CCI32_63		(5)		/* PINT レジスタCH5 */
#define		INTC_PINT_REGNO_CCI64_95		(6)		/* PINT レジスタCH6 */
#define		INTC_PINT_REGNO_CCI96_127		(7)		/* PINT レジスタCH7 */

#define		INTC_PINT_INTDTS31			(BIT31)		/* 周辺割り込みステータス31 */
#define		INTC_PINT_INTDTS30			(BIT30)		/* 周辺割り込みステータス30 */
#define		INTC_PINT_INTDTS29			(BIT29)		/* 周辺割り込みステータス29 */
#define		INTC_PINT_INTDTS28			(BIT28)		/* 周辺割り込みステータス28 */
#define		INTC_PINT_INTDTS27			(BIT27)		/* 周辺割り込みステータス27 */
#define		INTC_PINT_INTDTS26			(BIT26)		/* 周辺割り込みステータス26 */
#define		INTC_PINT_INTDTS25			(BIT25)		/* 周辺割り込みステータス25 */
#define		INTC_PINT_INTDTS24			(BIT24)		/* 周辺割り込みステータス24 */
#define		INTC_PINT_INTDTS23			(BIT23)		/* 周辺割り込みステータス23 */
#define		INTC_PINT_INTDTS22			(BIT22)		/* 周辺割り込みステータス22 */
#define		INTC_PINT_INTDTS21			(BIT21)		/* 周辺割り込みステータス21 */
#define		INTC_PINT_INTDTS20			(BIT20)		/* 周辺割り込みステータス20 */
#define		INTC_PINT_INTDTS19			(BIT19)		/* 周辺割り込みステータス19 */
#define		INTC_PINT_INTDTS18			(BIT18)		/* 周辺割り込みステータス18 */
#define		INTC_PINT_INTDTS17			(BIT17)		/* 周辺割り込みステータス17 */
#define		INTC_PINT_INTDTS16			(BIT16)		/* 周辺割り込みステータス16 */
#define		INTC_PINT_INTDTS15			(BIT15)		/* 周辺割り込みステータス15 */
#define		INTC_PINT_INTDTS14			(BIT14)		/* 周辺割り込みステータス14 */
#define		INTC_PINT_INTDTS13			(BIT13)		/* 周辺割り込みステータス13 */
#define		INTC_PINT_INTDTS12			(BIT12)		/* 周辺割り込みステータス12 */
#define		INTC_PINT_INTDTS11			(BIT11)		/* 周辺割り込みステータス11 */
#define		INTC_PINT_INTDTS10			(BIT10)		/* 周辺割り込みステータス10 */
#define		INTC_PINT_INTDTS9			(BIT9)		/* 周辺割り込みステータス9 */
#define		INTC_PINT_INTDTS8			(BIT8)		/* 周辺割り込みステータス8 */
#define		INTC_PINT_INTDTS7			(BIT7)		/* 周辺割り込みステータス7 */
#define		INTC_PINT_INTDTS6			(BIT6)		/* 周辺割り込みステータス6 */
#define		INTC_PINT_INTDTS5			(BIT5)		/* 周辺割り込みステータス5 */
#define		INTC_PINT_INTDTS4			(BIT4)		/* 周辺割り込みステータス4 */
#define		INTC_PINT_INTDTS3			(BIT3)		/* 周辺割り込みステータス3 */
#define		INTC_PINT_INTDTS2			(BIT2)		/* 周辺割り込みステータス2 */
#define		INTC_PINT_INTDTS1			(BIT1)		/* 周辺割り込みステータス1 */
#define		INTC_PINT_INTDTS0			(BIT0)		/* 周辺割り込みステータス0 */

#define		INTC_PINT_INTCDTS31			(BIT31)		/* 周辺割り込みステータス31 */
#define		INTC_PINT_INTCDTS30			(BIT30)		/* 周辺割り込みステータス30 */
#define		INTC_PINT_INTCDTS29			(BIT29)		/* 周辺割り込みステータス29 */
#define		INTC_PINT_INTCDTS28			(BIT28)		/* 周辺割り込みステータス28 */
#define		INTC_PINT_INTCDTS27			(BIT27)		/* 周辺割り込みステータス27 */
#define		INTC_PINT_INTCDTS26			(BIT26)		/* 周辺割り込みステータス26 */
#define		INTC_PINT_INTCDTS25			(BIT25)		/* 周辺割り込みステータス25 */
#define		INTC_PINT_INTCDTS24			(BIT24)		/* 周辺割り込みステータス24 */
#define		INTC_PINT_INTCDTS23			(BIT23)		/* 周辺割り込みステータス23 */
#define		INTC_PINT_INTCDTS22			(BIT22)		/* 周辺割り込みステータス22 */
#define		INTC_PINT_INTCDTS21			(BIT21)		/* 周辺割り込みステータス21 */
#define		INTC_PINT_INTCDTS20			(BIT20)		/* 周辺割り込みステータス20 */
#define		INTC_PINT_INTCDTS19			(BIT19)		/* 周辺割り込みステータス19 */
#define		INTC_PINT_INTCDTS18			(BIT18)		/* 周辺割り込みステータス18 */
#define		INTC_PINT_INTCDTS17			(BIT17)		/* 周辺割り込みステータス17 */
#define		INTC_PINT_INTCDTS16			(BIT16)		/* 周辺割り込みステータス16 */
#define		INTC_PINT_INTCDTS15			(BIT15)		/* 周辺割り込みステータス15 */
#define		INTC_PINT_INTCDTS14			(BIT14)		/* 周辺割り込みステータス14 */
#define		INTC_PINT_INTCDTS13			(BIT13)		/* 周辺割り込みステータス13 */
#define		INTC_PINT_INTCDTS12			(BIT12)		/* 周辺割り込みステータス12 */
#define		INTC_PINT_INTCDTS11			(BIT11)		/* 周辺割り込みステータス11 */
#define		INTC_PINT_INTCDTS10			(BIT10)		/* 周辺割り込みステータス10 */
#define		INTC_PINT_INTCDTS9			(BIT9)		/* 周辺割り込みステータス9 */
#define		INTC_PINT_INTCDTS8			(BIT8)		/* 周辺割り込みステータス8 */
#define		INTC_PINT_INTCDTS7			(BIT7)		/* 周辺割り込みステータス7 */
#define		INTC_PINT_INTCDTS6			(BIT6)		/* 周辺割り込みステータス6 */
#define		INTC_PINT_INTCDTS5			(BIT5)		/* 周辺割り込みステータス5 */
#define		INTC_PINT_INTCDTS4			(BIT4)		/* 周辺割り込みステータス4 */
#define		INTC_PINT_INTCDTS3			(BIT3)		/* 周辺割り込みステータス3 */
#define		INTC_PINT_INTCDTS2			(BIT2)		/* 周辺割り込みステータス2 */
#define		INTC_PINT_INTCDTS1			(BIT1)		/* 周辺割り込みステータス1 */
#define		INTC_PINT_INTCDTS0			(BIT0)		/* 周辺割り込みステータス0 */
	#define		INTC_PINT_NOINTREQ			(0)		/* 周辺割り込み要求無効 */
	#define		INTC_PINT_INTREQ			(1)		/* 周辺割り込み要求有効 */

/* PINTCLR */
#define		INTC_PINTCLR_REGNO_TCI0_31		(0)			/* PINTCLR レジスタCH0 */
#define		INTC_PINTCLR_REGNO_TCI32_63		(1)			/* PINTCLR レジスタCH1 */
#define		INTC_PINTCLR_REGNO_TCI64_95		(2)			/* PINTCLR レジスタCH2 */
#define		INTC_PINTCLR_REGNO_TCI96_127	(3)			/* PINTCLR レジスタCH3 */
#define		INTC_PINTCLR_REGNO_CCI0_31		(4)			/* PINTCLR レジスタCH4 */
#define		INTC_PINTCLR_REGNO_CCI32_63		(5)			/* PINTCLR レジスタCH5 */
#define		INTC_PINTCLR_REGNO_CCI64_95		(6)			/* PINTCLR レジスタCH6 */
#define		INTC_PINTCLR_REGNO_CCI96_127	(7)			/* PINTCLR レジスタCH7 */

#define		INTC_PINTCLR_INTCLR31		(BIT31)		/* 周辺割り込みステータスクリア31 */
#define		INTC_PINTCLR_INTCLR30		(BIT30)		/* 周辺割り込みステータスクリア30 */
#define		INTC_PINTCLR_INTCLR29		(BIT29)		/* 周辺割り込みステータスクリア29 */
#define		INTC_PINTCLR_INTCLR28		(BIT28)		/* 周辺割り込みステータスクリア28 */
#define		INTC_PINTCLR_INTCLR27		(BIT27)		/* 周辺割り込みステータスクリア27 */
#define		INTC_PINTCLR_INTCLR26		(BIT26)		/* 周辺割り込みステータスクリア26 */
#define		INTC_PINTCLR_INTCLR25		(BIT25)		/* 周辺割り込みステータスクリア25 */
#define		INTC_PINTCLR_INTCLR24		(BIT24)		/* 周辺割り込みステータスクリア24 */
#define		INTC_PINTCLR_INTCLR23		(BIT23)		/* 周辺割り込みステータスクリア23 */
#define		INTC_PINTCLR_INTCLR22		(BIT22)		/* 周辺割り込みステータスクリア22 */
#define		INTC_PINTCLR_INTCLR21		(BIT21)		/* 周辺割り込みステータスクリア21 */
#define		INTC_PINTCLR_INTCLR20		(BIT20)		/* 周辺割り込みステータスクリア20 */
#define		INTC_PINTCLR_INTCLR19		(BIT19)		/* 周辺割り込みステータスクリア19 */
#define		INTC_PINTCLR_INTCLR18		(BIT18)		/* 周辺割り込みステータスクリア18 */
#define		INTC_PINTCLR_INTCLR17		(BIT17)		/* 周辺割り込みステータスクリア17 */
#define		INTC_PINTCLR_INTCLR16		(BIT16)		/* 周辺割り込みステータスクリア16 */
#define		INTC_PINTCLR_INTCLR15		(BIT15)		/* 周辺割り込みステータスクリア15 */
#define		INTC_PINTCLR_INTCLR14		(BIT14)		/* 周辺割り込みステータスクリア14 */
#define		INTC_PINTCLR_INTCLR13		(BIT13)		/* 周辺割り込みステータスクリア13 */
#define		INTC_PINTCLR_INTCLR12		(BIT12)		/* 周辺割り込みステータスクリア12 */
#define		INTC_PINTCLR_INTCLR11		(BIT11)		/* 周辺割り込みステータスクリア11 */
#define		INTC_PINTCLR_INTCLR10		(BIT10)		/* 周辺割り込みステータスクリア10 */
#define		INTC_PINTCLR_INTCLR9		(BIT9)		/* 周辺割り込みステータスクリア9 */
#define		INTC_PINTCLR_INTCLR8		(BIT8)		/* 周辺割り込みステータスクリア8 */
#define		INTC_PINTCLR_INTCLR7		(BIT7)		/* 周辺割り込みステータスクリア7 */
#define		INTC_PINTCLR_INTCLR6		(BIT6)		/* 周辺割り込みステータスクリア6 */
#define		INTC_PINTCLR_INTCLR5		(BIT5)		/* 周辺割り込みステータスクリア5 */
#define		INTC_PINTCLR_INTCLR4		(BIT4)		/* 周辺割り込みステータスクリア4 */
#define		INTC_PINTCLR_INTCLR3		(BIT3)		/* 周辺割り込みステータスクリア3 */
#define		INTC_PINTCLR_INTCLR2		(BIT2)		/* 周辺割り込みステータスクリア2 */
#define		INTC_PINTCLR_INTCLR1		(BIT1)		/* 周辺割り込みステータスクリア1 */
#define		INTC_PINTCLR_INTCLR0		(BIT0)		/* 周辺割り込みステータスクリア0 */

#define		INTC_PINTCLR_INTCTCLR31		(BIT31)		/* 周辺割り込みステータスクリア31 */
#define		INTC_PINTCLR_INTCTCLR30		(BIT30)		/* 周辺割り込みステータスクリア30 */
#define		INTC_PINTCLR_INTCTCLR29		(BIT29)		/* 周辺割り込みステータスクリア29 */
#define		INTC_PINTCLR_INTCTCLR28		(BIT28)		/* 周辺割り込みステータスクリア28 */
#define		INTC_PINTCLR_INTCTCLR27		(BIT27)		/* 周辺割り込みステータスクリア27 */
#define		INTC_PINTCLR_INTCTCLR26		(BIT26)		/* 周辺割り込みステータスクリア26 */
#define		INTC_PINTCLR_INTCTCLR25		(BIT25)		/* 周辺割り込みステータスクリア25 */
#define		INTC_PINTCLR_INTCTCLR24		(BIT24)		/* 周辺割り込みステータスクリア24 */
#define		INTC_PINTCLR_INTCTCLR23		(BIT23)		/* 周辺割り込みステータスクリア23 */
#define		INTC_PINTCLR_INTCTCLR22		(BIT22)		/* 周辺割り込みステータスクリア22 */
#define		INTC_PINTCLR_INTCTCLR21		(BIT21)		/* 周辺割り込みステータスクリア21 */
#define		INTC_PINTCLR_INTCTCLR20		(BIT20)		/* 周辺割り込みステータスクリア20 */
#define		INTC_PINTCLR_INTCTCLR19		(BIT19)		/* 周辺割り込みステータスクリア19 */
#define		INTC_PINTCLR_INTCTCLR18		(BIT18)		/* 周辺割り込みステータスクリア18 */
#define		INTC_PINTCLR_INTCTCLR17		(BIT17)		/* 周辺割り込みステータスクリア17 */
#define		INTC_PINTCLR_INTCTCLR16		(BIT16)		/* 周辺割り込みステータスクリア16 */
#define		INTC_PINTCLR_INTCTCLR15		(BIT15)		/* 周辺割り込みステータスクリア15 */
#define		INTC_PINTCLR_INTCTCLR14		(BIT14)		/* 周辺割り込みステータスクリア14 */
#define		INTC_PINTCLR_INTCTCLR13		(BIT13)		/* 周辺割り込みステータスクリア13 */
#define		INTC_PINTCLR_INTCTCLR12		(BIT12)		/* 周辺割り込みステータスクリア12 */
#define		INTC_PINTCLR_INTCTCLR11		(BIT11)		/* 周辺割り込みステータスクリア11 */
#define		INTC_PINTCLR_INTCTCLR10		(BIT10)		/* 周辺割り込みステータスクリア10 */
#define		INTC_PINTCLR_INTCTCLR9		(BIT9)		/* 周辺割り込みステータスクリア9 */
#define		INTC_PINTCLR_INTCTCLR8		(BIT8)		/* 周辺割り込みステータスクリア8 */
#define		INTC_PINTCLR_INTCTCLR7		(BIT7)		/* 周辺割り込みステータスクリア7 */
#define		INTC_PINTCLR_INTCTCLR6		(BIT6)		/* 周辺割り込みステータスクリア6 */
#define		INTC_PINTCLR_INTCTCLR5		(BIT5)		/* 周辺割り込みステータスクリア5 */
#define		INTC_PINTCLR_INTCTCLR4		(BIT4)		/* 周辺割り込みステータスクリア4 */
#define		INTC_PINTCLR_INTCTCLR3		(BIT3)		/* 周辺割り込みステータスクリア3 */
#define		INTC_PINTCLR_INTCTCLR2		(BIT2)		/* 周辺割り込みステータスクリア2 */
#define		INTC_PINTCLR_INTCTCLR1		(BIT1)		/* 周辺割り込みステータスクリア1 */
#define		INTC_PINTCLR_INTCTCLR0		(BIT0)		/* 周辺割り込みステータスクリア0 */

/* TPTMSEL */
#define		INTC_TPTMSEL_TPTMSEL3		(BIT3)		/* PE3 FEINT/EIINT TPTM割り込み */
#define		INTC_TPTMSEL_TPTMSEL2		(BIT2)		/* PE2 FEINT/EIINT TPTM割り込み */
#define		INTC_TPTMSEL_TPTMSEL1		(BIT1)		/* PE1 FEINT/EIINT TPTM割り込み */
#define		INTC_TPTMSEL_TPTMSEL0		(BIT0)		/* PE0 FEINT/EIINT TPTM割り込み */
	#define		INTC_TPTMSEL_IME_FEINT		(0)		/* FEINT TPTM割り込み有効 */
	#define		INTC_TPTMSEL_IME_EIINT		(1)		/* EIINT TPTM割り込み有効 */

/* FENMIF */
#define		INTC_FENMIF_NMIF				(BIT0)		/* 外部 FEレベルノンマスカブル割込み発生フラグ */
	#define		INTC_FENMIF_NMIF_NO_INTERRUPT		(0)		/* 割込み発生なし */
	#define		INTC_FENMIF_NMIF_INTERRUPT			(1)		/* 割込み発生あり */

/* FENMIC */
#define		INTC_FENMIC_NMIC				(BIT0)		/* 外部 FEレベルノンマスカブル割込みフラグクリア */
	#define		INTC_FENMIC_NMIC_FLAGCLEARED		(1)		/* フラグクリア */

/* FEINTF */
#define		INTC_FEINTF_ECMPE			(BIT2)		/* PEx ECM割込みステータス */
	#define		INTC_FENMIF_ECM_NOOCUR			(0)		/* 割込み発生なし */
	#define		INTC_FENMIF_EUM_OCUR			(1)		/* 割込み発生あり */
#define		INTC_FEINTF_TPTMPE			(BIT1)		/* PEx Time Protection Timer割込みステータス */
	#define		INTC_FENMIF_TPTM_NOOCUR			(0)		/* 割込み発生なし */
	#define		INTC_FENMIF_TPTM_OCUR			(1)		/* 割込み発生あり */
#define		INTC_FEINTF_SWDT			(BIT0)		/* Secure WDT overflow割込みステータス */
	#define		INTC_FENMIF_SWDT_NOOCUR			(0)		/* 割込み発生なし */
	#define		INTC_FENMIF_SWDT_OCUR			(1)		/* 割込み発生あり */

/* FEINTMSK */
#define		INTC_FEINTMSK_ECMPE			(BIT2)		/* PEx ECM割込みステータスのマスク */
	#define		INTC_FEINTMSK_ECM_NOMSK			(0)		/* マスクなし */
	#define		INTC_FEINTMSK_ECM_MSK			(1)		/* マスクあり */
#define		INTC_FEINTMSK_TPTMPE		(BIT1)		/* PEx Time Protection Timer割込みのマスク */
	#define		INTC_FEINTMSK_TPTM_NOMSK		(0)		/* マスクなし */
	#define		INTC_FEINTMSK_TPTM_MSK			(1)		/* マスクあり */
#define		INTC_FEINTMSK_SWDT			(BIT0)		/* Secure WDT overflow割込みのマスク */
	#define		INTC_FEINTMSK_SWDT_NOMSK		(0)		/* マスクなし */
	#define		INTC_FEINTMSK_SWDT_MSK			(1)		/* マスクあり */

/* FEINTC */
#define		INTC_FFEINTC_ECM			(BIT2)		/* PEx ECM割込み */
	#define		INTC_FEINTC_ECM_FLGCLR		(1)		/* フラグクリア */
#define		INTC_FFEINTC_TPTM			(BIT1)		/* PEx Time Protection Timer割込み */
	#define		INTC_FEINTC_TPTM_FLGCLR		(1)		/* フラグクリア */
#define		INTC_FFEINTC_SWDT			(BIT0)		/* Secure WDT overflow割込み */
	#define		INTC_FEINTC_SWDT_FLGCLR		(1)		/* フラグクリア */



/*==============================================================================================*/
/*	struct address definition																	*/
/*==============================================================================================*/
#define		Reg_EINT		(*(volatile Reg_Eint_Type*) (0xFFC00000U))
#define		Reg_INTIF		(*(volatile Reg_Intif_Type*)(0xFF090000U))
#define		Reg_INTC1SELF	(*(volatile Reg_Intc1self_Type*)(0xFFFC0000U))
#define		Reg_INTC1CPU0	(*(volatile Reg_Intc1cpu0_Type*)(0xFFFC4000U))
#define		Reg_INTC1CPU1	(*(volatile Reg_Intc1cpu1_Type*)(0xFFFC8000U))
#define		Reg_INTC1CPU2	(*(volatile Reg_Intc1cpu2_Type*)(0xFFFCC000U))
#define		Reg_INTC1CPU3	(*(volatile Reg_Intc1cpu3_Type*)(0xFFFD0000U))
#define		Reg_INTC2		(*(volatile Reg_Intc2_Type*)(0xFFF80000U))	/* 0xFFF80040ではなく0xFFF80000をベースアドレスとする */
																		/* 理由：割り込みCh32のEICにアクセスする場合に、Reg_INTC2.unEIC[32].u2Dataで0xFFF80040にアクセスするようにするため */
																		/*       0xFFF80040をベースとした場合、割り込みCh32のEICにアクセスする場合、Reg_INTC2.unEIC[32-32].u2Dataとする必要がある */
#define		Reg_FENC		(*(volatile Reg_Fenc_Type*) (0xFF9A3A00U))
#define		Reg_FEINCCPU0	(*(volatile Reg_Feinccpu0_Type*) (0xFF9A3B00U))
#define		Reg_FEINCCPU1	(*(volatile Reg_Feinccpu1_Type*) (0xFF9A3C00U))
#define		Reg_FEINCCPU2	(*(volatile Reg_Feinccpu2_Type*) (0xFF9A3D00U))
#define		Reg_FEINCCPU3	(*(volatile Reg_Feinccpu3_Type*) (0xFF9A3E00U))

/*==============================================================================================*/
/*	INTC channel ID definition																	*/
/*==============================================================================================*/
/* INTC2 */
#if 0 // zantei 未使用なのでコメントアウト
#define		INTC_CH_IPIR0				(0)		/* INT_IPIR0 プロセッサ間割り込み0 */
#define		INTC_CH_IPIR1				(1)		/* INT_IPIR1 プロセッサ間割り込み1 */
#define		INTC_CH_IPIR2				(2)		/* INT_IPIR2 プロセッサ間割り込み2 */
#define		INTC_CH_IPIR3				(3)		/* INT_IPIR3 プロセッサ間割り込み3 */

#define		INTC_CH_BRDC0				(4)		/* INT_BRDC0 ブロードキャスト通知0 */
#define		INTC_CH_BRDC1				(5)		/* INT_BRDC1 ブロードキャスト通知1 */
#define		INTC_CH_BRDC2				(6)		/* INT_BRDC2 ブロードキャスト通知2 */
#define		INTC_CH_BRDC3				(7)		/* INT_BRDC3 ブロードキャスト通知3 */

#define		INTC_CH_ECMMI				(8)		/* ECM マスカブル割り込み(EI レベル) */
#define		INTC_CH_ECMDCLSMI			(9)		/* DCLS エラー割り込み(EI レベル) */

/* TAUD0 */
#define		INTC_CH_TAUD0_I0				(10)		/*  TAUD0 チャネル0 割込み  */
#define		INTC_CH_TAUD0_I2				(11)		/*  TAUD0 チャネル2 割込み  */
#define		INTC_CH_TAUD0_I4				(12)		/*  TAUD0 チャネル4 割込み  */
#define		INTC_CH_TAUD0_I6				(13)		/*  TAUD0 チャネル6 割込み  */
#define		INTC_CH_TAUD0_I8				(23)		/*  TAUD0 チャネル8 割込み  */
#define		INTC_CH_TAUD0_I10				(24)		/*  TAUD0 チャネル10 割込み  */
#define		INTC_CH_TAUD0_I12				(25)		/*  TAUD0 チャネル12 割込み  */
#define		INTC_CH_TAUD0_I14				(26)		/*  TAUD0 チャネル14 割込み  */

#define		INTC_CH_SINT0				(14)	/* intreq_sint[0] ソフトウェア割り込み0 */
#define		INTC_CH_SINT1				(15)	/* intreq_sint[1] ソフトウェア割り込み1 */
#define		INTC_CH_SINT2				(16)	/* intreq_sint[2] ソフトウェア割り込み2 */
#define		INTC_CH_SINT3				(17)	/* intreq_sint[3] ソフトウェア割り込み3 */

/* OSTM */
#define		INTC_CH_OSTM0_TINT			(360)	/* OSTM OSTM0 割り込み */
#define		INTC_CH_OSTM1_TINT			(361)	/* OSTM OSTM1 割り込み(CPU0) */
#define		INTC_CH_OSTM2_TINT			(841)	/* OSTM OSTM2 割り込み(CPU1) */
#define		INTC_CH_OSTM3_TINT			(842)	/* OSTM OSTM2 割り込み(CPU2) */

/* ICU-M */
#define		INTC_CH_ICU2PES0				(21)		/* ICU-M ICU2PES0 割り込み */
#define		INTC_CH_ICU2PES1				(21)		/* ICU-M ICU2PES1 割り込み */
#define		INTC_CH_ICU2PES2				(21)		/* ICU-M ICU2PES2 割り込み */
#define		INTC_CH_ICU2PES3				(21)		/* ICU-M ICU2PES3 割り込み */

/* WDTB */
#define		INTC_CH_WDTB0_TIT			(22)	/* WTDTB WDTB0 割り込み(CPU0) */
#define		INTC_CH_WDTB1_TIT			(22)	/* WTDTB WDTB1 割り込み(CPU1) */
#define		INTC_CH_WDTB2_TIT			(22)	/* WTDTB WDTB1 割り込み(CPU2) */
#define		INTC_CH_WDTB3_TIT			(22)	/* WTDTB WDTB1 割り込み(CPU3) */

/* TPTM */
#define		INTC_CH_TPTM_TINT0			(31)	/* TPTM 割り込み(CPU0) */
#define		INTC_CH_TPTM_TINT1			(31)	/* TPTM 割り込み(CPU1) */
#define		INTC_CH_TPTM_TINT2			(31)	/* TPTM 割り込み(CPU2) */
#define		INTC_CH_TPTM_TINT3			(31)	/* TPTM 割り込み(CPU3) */

/* BHP */
#define		INTC_CH_DCUDEGRADPE			(32)		/*  デグラデーション割り込み*/

/* DEBUG */
#define		INTC_CH_INSTRAMIMPLERR		(33)		/* RAM未実装領域へのアクセス検出割り込み  */
#define		INTC_CH_TCUHDRQMSK			(34)		/* マスク生成通知割込み  */

/* FLASH */
#define		INTC_CH_FL0ENDNM				(35)		/* FPSYS0フラッシュシーケンサ処理終了割り込み */
#define		INTC_CH_FL2ENDNM				(37)		/* FPSYS2フラッシュシーケンサ処理終了割り込み */

/* DFP */
#define		INTC_CH_DFP_INT_OUT0			(38)		/* DFP割り込み0 */
#define		INTC_CH_DFP_INT_OUT1			(39)		/* DFP割り込み1 */
#define		INTC_CH_DFP_INT_OUT2			(40)		/* DFP割り込み2 */
#define		INTC_CH_DFP_INT_OUT3			(41)		/* DFP割り込み3 */
#define		INTC_CH_DFP_INT_OUT4			(42)		/* DFP割り込み4 */
#define		INTC_CH_DFP_INT_OUT5			(43)		/* DFP割り込み5 */
#define		INTC_CH_DFP_INT_OUT6			(44)		/* DFP割り込み6 */
#define		INTC_CH_DFP_INT_OUT7			(45)		/* DFP割り込み7 */
#define		INTC_CH_DFP_INT_OUT8			(46)		/* DFP割り込み8 */
#define		INTC_CH_DFP_INT_OUT9			(47)		/* DFP割り込み9 */
#define		INTC_CH_DFP_INT_OUT10			(48)		/* DFP割り込み10 */
#define		INTC_CH_DFP_INT_OUT11			(49)		/* DFP割り込み11 */
#define		INTC_CH_DFP_INT_OUT12			(50)		/* DFP割り込み12 */
#define		INTC_CH_DFP_INT_OUT13			(51)		/* DFP割り込み13 */
#define		INTC_CH_DFP_INT_OUT14			(52)		/* DFP割り込み14 */
#define		INTC_CH_DFP_INT_OUT15			(53)		/* DFP割り込み15 */

/* EMU */
#define		INTC_CH_EMU0_INT0				(38)		/* EMU3S0 割り込み0 */
#define		INTC_CH_EMU0_INT1				(39)		/* EMU3S0 割り込み1 */
#define		INTC_CH_EMU0_INT2				(40)		/* EMU3S0 割り込み2 */
#define		INTC_CH_EMU0_INT3				(41)		/* EMU3S0 割り込み3 */
#define		INTC_CH_EMU0_INT4				(42)		/* EMU3S0 割り込み4 */
#define		INTC_CH_EMU0_INT5				(43)		/* EMU3S0 割り込み5 */
#define		INTC_CH_EMU0_INT6				(44)		/* EMU3S0 割り込み6 */
#define		INTC_CH_EMU0_INT7				(45)		/* EMU3S0 割り込み7 */

#define		INTC_CH_EMU1_INT0				(48)		/* EMU3S1 割り込み0 */
#define		INTC_CH_EMU1_INT1				(49)		/* EMU3S1 割り込み1 */
#define		INTC_CH_EMU1_INT2				(50)		/* EMU3S1 割り込み2 */
#define		INTC_CH_EMU1_INT3				(51)		/* EMU3S1 割り込み3 */
#define		INTC_CH_EMU1_INT4				(52)		/* EMU3S1 割り込み4 */
#define		INTC_CH_EMU1_INT5				(53)		/* EMU3S1 割り込み5 */
#define		INTC_CH_EMU1_INT6				(54)		/* EMU3S1 割り込み6 */
#define		INTC_CH_EMU1_INT7				(55)		/* EMU3S1 割り込み7 */

/* TPBA */
#define		INTC_CH_TPBA0IPRD				(47)		/* TPBA0周期一致検出割り込み */
#define		INTC_CH_TPBA0IDTY				(48)		/* TPB0デューティ一致検出割り込み */
#define		INTC_CH_TPBA0IPAT				(49)		/* TPBA0パターン番号一致検出割り込み */
#define		INTC_CH_TPBA0IPRD_510			(510)		/* TPBA0周期一致検出割り込み */
#define		INTC_CH_TPBA0IDTY_511			(511)		/* TPB0デューティ一致検出割り込み */
#define		INTC_CH_TPBA0IPAT_512			(512)		/* TPBA0パターン番号一致検出割り込み */

#define		INTC_CH_TPBA1IPRD				(50)		/* TPBA 1周期一致検出割り込み */
#define		INTC_CH_TPBA1IDTY				(51)		/* TPB1デューティ一致検出割り込み */
#define		INTC_CH_TPBA1IPAT				(52)		/* TPBA1パターン番号一致検出割り込み */
#define		INTC_CH_TPBA1IPRD_513			(513)		/* TPBA1周期一致検出割り込み */
#define		INTC_CH_TPBA1IDTY_514			(514)		/* TPB1デューティ一致検出割り込み */
#define		INTC_CH_TPBA1IPAT_515			(515)		/* TPBA1パターン番号一致検出割り込み */

/* sDMAC */
#define		INTC_CH_SDMAC0_INTREQ0		(70)	/* sDMAC0 CH0 転送完了割り込み */
#define		INTC_CH_SDMAC0_INTREQ1		(71)	/* sDMAC0 CH1 転送完了割り込み */
#define		INTC_CH_SDMAC0_INTREQ2		(72)	/* sDMAC0 CH2 転送完了割り込み */
#define		INTC_CH_SDMAC0_INTREQ3		(73)	/* sDMAC0 CH3 転送完了割り込み */
#define		INTC_CH_SDMAC0_INTREQ4		(74)	/* sDMAC0 CH4 転送完了割り込み */
#define		INTC_CH_SDMAC0_INTREQ5		(75)	/* sDMAC0 CH5 転送完了割り込み */
#define		INTC_CH_SDMAC0_INTREQ6		(76)	/* sDMAC0 CH6 転送完了割り込み */
#define		INTC_CH_SDMAC0_INTREQ7		(77)	/* sDMAC0 CH7 転送完了割り込み */
#define		INTC_CH_SDMAC0_INTREQ8		(78)	/* sDMAC0 CH8 転送完了割り込み */
#define		INTC_CH_SDMAC0_INTREQ9		(79)	/* sDMAC0 CH9 転送完了割り込み */
#define		INTC_CH_SDMAC0_INTREQ10		(80)	/* sDMAC0 CH10 転送完了割り込み */
#define		INTC_CH_SDMAC0_INTREQ11		(81)	/* sDMAC0 CH11 転送完了割り込み */
#define		INTC_CH_SDMAC0_INTREQ12		(82)	/* sDMAC0 CH12 転送完了割り込み */
#define		INTC_CH_SDMAC0_INTREQ13		(83)	/* sDMAC0 CH13 転送完了割り込み */
#define		INTC_CH_SDMAC0_INTREQ14		(84)	/* sDMAC0 CH14 転送完了割り込み */
#define		INTC_CH_SDMAC0_INTREQ15		(85)	/* sDMAC0 CH15 転送完了割り込み */

#define		INTC_CH_SDMAC0_INTREQAERR	(29)	/* sDMAC0/1 アドレスエラー割り込み */

#define		INTC_CH_SDMAC1_INTREQ0		(825)	/* sDMAC1 CH0 転送完了割り込み */
#define		INTC_CH_SDMAC1_INTREQ1		(826)	/* sDMAC1 CH1 転送完了割り込み */
#define		INTC_CH_SDMAC1_INTREQ2		(827)	/* sDMAC1 CH2 転送完了割り込み */
#define		INTC_CH_SDMAC1_INTREQ3		(828)	/* sDMAC1 CH3 転送完了割り込み */
#define		INTC_CH_SDMAC1_INTREQ4		(829)	/* sDMAC1 CH4 転送完了割り込み */
#define		INTC_CH_SDMAC1_INTREQ5		(830)	/* sDMAC1 CH5 転送完了割り込み */
#define		INTC_CH_SDMAC1_INTREQ6		(831)	/* sDMAC1 CH6 転送完了割り込み */
#define		INTC_CH_SDMAC1_INTREQ7		(832)	/* sDMAC1 CH7 転送完了割り込み */
#define		INTC_CH_SDMAC1_INTREQ8		(833)	/* sDMAC1 CH8 転送完了割り込み */
#define		INTC_CH_SDMAC1_INTREQ9		(834)	/* sDMAC1 CH9 転送完了割り込み */
#define		INTC_CH_SDMAC1_INTREQ10		(835)	/* sDMAC1 CH10 転送完了割り込み */
#define		INTC_CH_SDMAC1_INTREQ11		(836)	/* sDMAC1 CH11 転送完了割り込み */
#define		INTC_CH_SDMAC1_INTREQ12		(837)	/* sDMAC1 CH12 転送完了割り込み */
#define		INTC_CH_SDMAC1_INTREQ13		(838)	/* sDMAC1 CH13 転送完了割り込み */
#define		INTC_CH_SDMAC1_INTREQ14		(839)	/* sDMAC1 CH14 転送完了割り込み */
#define		INTC_CH_SDMAC1_INTREQ15		(840)	/* sDMAC1 CH15 転送完了割り込み */

/* DTS */
#if 0  /* reg_dma.h と定義がかぶっているため削除 */
#define		INTC_CH_DTS_CH31TO0			(62)	/* DTS CH31-0 転送完了割り込み */
#define		INTC_CH_DTS_CH63TO32		(63)	/* DTS CH63-32 転送完了割り込み */
#define		INTC_CH_DTS_CH95TO64		(64)	/* DTS CH95-64 転送完了割り込み */
#define		INTC_CH_DTS_CH127TO96		(65)	/* DTS CH127-96 転送完了割り込み */
#define		INTC_CH_DTSCT_CH31TO0		(66)	/* DTSCT CH31-0 転送回数一致割り込み */
#define		INTC_CH_DTSCT_CH63TO32		(67)	/* DTSCT CH63-32 転送回数一致割り込み */
#define		INTC_CH_DTSCT_CH95TO64		(68)	/* DTSCT CH95-64 転送回数一致割り込み */
#define		INTC_CH_DTSCT_CH127TO96		(69)	/* DTSCT CH127-96 転送回数一致割り込み */
#endif /* reg_dma.h と定義がかぶっているため削除 */

#define		INTC_CH_DTS_INTDTSERR		(30)	/* DTS 転送エラー割り込み */

/* ATU A */
#define		INTC_CH_ATUA_SLIA0			(18)	/* ICRA0~ICRA7 インプットキャプチャ割り込み */
#define		INTC_CH_ATUA_SLIA1			(19)	/* ICRA0~ICRA7 インプットキャプチャ割り込み */
#define		INTC_CH_ATUA_SLIA2			(27)	/* ICRA0~ICRA7 インプットキャプチャ割り込み */
#define		INTC_CH_ATUA_SLIA3			(28)	/* ICRA0~ICRA7 インプットキャプチャ割り込み */

#define		INTC_CH_ATUA_ICRA_BASE		(86)	/* ICRA0~ICRA7,TCNTA インプットキャプチャ割り込み */
	#define		INTC_CH_ATUA_ICRA0		(86)	/* ICRA0 インプットキャプチャ割り込み */
	#define		INTC_CH_ATUA_ICRA1		(87)	/* ICRA1 インプットキャプチャ割り込み */
	#define		INTC_CH_ATUA_ICRA2		(88)	/* ICRA2 インプットキャプチャ割り込み */
	#define		INTC_CH_ATUA_ICRA3		(89)	/* ICRA3 インプットキャプチャ割り込み */
	#define		INTC_CH_ATUA_ICRA4		(90)	/* ICRA4 インプットキャプチャ割り込み */
	#define		INTC_CH_ATUA_ICRA5		(91)	/* ICRA5 インプットキャプチャ割り込み */
	#define		INTC_CH_ATUA_ICRA6		(92)	/* ICRA6 インプットキャプチャ割り込み */
	#define		INTC_CH_ATUA_ICRA7		(93)	/* ICRA7 インプットキャプチャ割り込み */
	#define		INTC_CH_ATUA_TCNTAOVF	(94)	/* TCNTA オーバフロー割り込み */

/* ATU B */
#define		INTC_CH_ATUB_OCRB0			(95)	/* OCRB0 コンペアマッチ割り込み */
#define		INTC_CH_ATUB_OCRB1			(96)	/* OCRB1 コンペアマッチ割り込み */
#define		INTC_CH_ATUB_OCRB6			(97)	/* OCRB6 コンペアマッチ割り込み */
#define		INTC_CH_ATUB_OCRB10		(98)	/* OCRB10 コンペアマッチ割り込み */
#define		INTC_CH_ATUB_OCRB11		(99)	/* OCRB11 コンペアマッチ割り込み */
#define		INTC_CH_ATUB_OCRB12		(100)	/* OCRB12 コンペアマッチ割り込み */
#define		INTC_CH_ATUB_ICRB6			(101)	/* TCNTB6MとICRB6の比較 条件マッチ割り込み */
#define		INTC_CH_ATUB_CMFB6_6M		(102)	/* CMFB6とCMFB6MのAND/OR条件 条件マッチ割り込み */
#define		INTC_CH_ATUB_ICRB0			(103)	/* ICRB0 インプットキャプチャ割り込み */
#define 	INTC_CH_ATUB_OCR2B0 		(298)	/* OCR2B0  コンペアマッチ割り込み */
#define 	INTC_CH_ATUB_OCR2B1 		(299)	/* OCR2B1 コンペアマッチ割り込み */
#define 	INTC_CH_ATUB_OCR2B10		(300)	/* OCR2B10 コンペアマッチ割り込み */
#define 	INTC_CH_ATUB_OCR2B11		(301)	/* OCR2B11 コンペアマッチ割り込み */
#define 	INTC_CH_ATUB_OCR2B12		(302)	/* OCR2B12 コンペアマッチ割り込み */
#define 	INTC_CH_ATUB_ICR2B0 		(303)	/* ICR2B0 インプットキャプチャ割り込み */

/* ATU C */
#define		INTC_CH_ATUC_BASE_NUM		(11)

#define		INTC_CH_ATUC0_BASE			(104)	/* GRC0_0~GRC0_3,OCRC0_0~OCRC0_3 インプットキャプチャ/コンペアマッチ割り込み */
	#define		INTC_CH_ATUC_SLIC00	(104)	/* GRC0_0,OCRC0_0 インプットキャプチャ/コンペアマッチ割り込み */
	#define		INTC_CH_ATUC_SLIC01	(105)	/* GRC0_1,OCRC0_1 インプットキャプチャ/コンペアマッチ割り込み */
	#define		INTC_CH_ATUC_SLIC02	(106)	/* GRC0_2,OCRC0_2 インプットキャプチャ/コンペアマッチ割り込み */
	#define		INTC_CH_ATUC_SLIC03	(107)	/* GRC0_3,OCRC0_3 インプットキャプチャ/コンペアマッチ割り込み */
#define		INTC_CH_ATUC1_BASE			(108)	/* GRC1_0~GRC1_3,OCRC1_0~OCRC1_3 インプットキャプチャ/コンペアマッチ割り込み */
	#define		INTC_CH_ATUC_SLIC10	(108)	/* GRC1_0,OCRC1_0 インプットキャプチャ/コンペアマッチ割り込み */
	#define		INTC_CH_ATUC_SLIC11	(109)	/* GRC1_1,OCRC1_1 インプットキャプチャ/コンペアマッチ割り込み */
	#define		INTC_CH_ATUC_SLIC12	(110)	/* GRC1_2,OCRC1_2 インプットキャプチャ/コンペアマッチ割り込み */
	#define		INTC_CH_ATUC_SLIC13	(111)	/* GRC1_3,OCRC1_3 インプットキャプチャ/コンペアマッチ割り込み */
#define		INTC_CH_ATUC2_BASE			(112)	/* GRC2_0~GRC2_3,OCRC2_0~OCRC2_3 インプットキャプチャ/コンペアマッチ割り込み */
	#define		INTC_CH_ATUC_SLIC20	(112)	/* GRC2_0,OCRC2_0 インプットキャプチャ/コンペアマッチ割り込み */
	#define		INTC_CH_ATUC_SLIC21	(113)	/* GRC2_1,OCRC2_1 インプットキャプチャ/コンペアマッチ割り込み */
	#define		INTC_CH_ATUC_SLIC22	(114)	/* GRC2_2,OCRC2_2 インプットキャプチャ/コンペアマッチ割り込み */
	#define		INTC_CH_ATUC_SLIC23	(115)	/* GRC2_3,OCRC2_3 インプットキャプチャ/コンペアマッチ割り込み */
#define		INTC_CH_ATUC3_BASE			(116)	/* GRC3_0~GRC3_3,OCRC3_0~OCRC3_3 インプットキャプチャ/コンペアマッチ割り込み */
	#define		INTC_CH_ATUC_SLIC30	(116)	/* GRC3_0,OCRC3_0 インプットキャプチャ/コンペアマッチ割り込み */
	#define		INTC_CH_ATUC_SLIC31	(117)	/* GRC3_1,OCRC3_1 インプットキャプチャ/コンペアマッチ割り込み */
	#define		INTC_CH_ATUC_SLIC32	(118)	/* GRC3_2,OCRC3_2 インプットキャプチャ/コンペアマッチ割り込み */
	#define		INTC_CH_ATUC_SLIC33	(119)	/* GRC3_3,OCRC3_3 インプットキャプチャ/コンペアマッチ割り込み */
#define		INTC_CH_ATUC4_BASE			(120)	/* GRC4_0~GRC4_3,OCRC4_0~OCRC4_3 インプットキャプチャ/コンペアマッチ割り込み */
	#define		INTC_CH_ATUC_SLIC40	(120)	/* GRC4_0,OCRC4_0 インプットキャプチャ/コンペアマッチ割り込み */
	#define		INTC_CH_ATUC_SLIC41	(121)	/* GRC4_1,OCRC4_1 インプットキャプチャ/コンペアマッチ割り込み */
	#define		INTC_CH_ATUC_SLIC42	(122)	/* GRC4_2,OCRC4_2 インプットキャプチャ/コンペアマッチ割り込み */
	#define		INTC_CH_ATUC_SLIC43	(123)	/* GRC4_3,OCRC4_3 インプットキャプチャ/コンペアマッチ割り込み */
#define		INTC_CH_ATUC5_BASE			(124)	/* GRC5_0~GRC5_3,OCRC5_0~OCRC5_3 インプットキャプチャ/コンペアマッチ割り込み */
	#define		INTC_CH_ATUC_SLIC50	(124)	/* GRC5_0,OCRC5_0 インプットキャプチャ/コンペアマッチ割り込み */
	#define		INTC_CH_ATUC_SLIC51	(125)	/* GRC5_1,OCRC5_1 インプットキャプチャ/コンペアマッチ割り込み */
	#define		INTC_CH_ATUC_SLIC52	(126)	/* GRC5_2,OCRC5_2 インプットキャプチャ/コンペアマッチ割り込み */
	#define		INTC_CH_ATUC_SLIC53	(127)	/* GRC5_3,OCRC5_3 インプットキャプチャ/コンペアマッチ割り込み */
#define		INTC_CH_ATUC6_BASE			(128)	/* GRC6_0~GRC6_3,OCRC6_0~OCRC2_3 インプットキャプチャ/コンペアマッチ割り込み */
	#define		INTC_CH_ATUC_SLIC60	(128)	/* GRC6_0,OCRC6_0 インプットキャプチャ/コンペアマッチ割り込み */
	#define		INTC_CH_ATUC_SLIC61	(129)	/* GRC6_1,OCRC6_1 インプットキャプチャ/コンペアマッチ割り込み */
	#define		INTC_CH_ATUC_SLIC62	(130)	/* GRC6_2,OCRC6_2 インプットキャプチャ/コンペアマッチ割り込み */
	#define		INTC_CH_ATUC_SLIC63	(131)	/* GRC6_3,OCRC6_3 インプットキャプチャ/コンペアマッチ割り込み */
#define		INTC_CH_ATUC7_BASE			(132)	/* GRC7_0~GRC7_3,OCRC7_0~OCRC7_3 インプットキャプチャ/コンペアマッチ割り込み */
	#define		INTC_CH_ATUC_SLIC70	(132)	/* GRC7_0,OCRC7_0 インプットキャプチャ/コンペアマッチ割り込み */
	#define		INTC_CH_ATUC_SLIC71	(133)	/* GRC7_1,OCRC7_1 インプットキャプチャ/コンペアマッチ割り込み */
	#define		INTC_CH_ATUC_SLIC72	(134)	/* GRC7_2,OCRC7_2 インプットキャプチャ/コンペアマッチ割り込み */
	#define		INTC_CH_ATUC_SLIC73	(135)	/* GRC7_3,OCRC7_3 インプットキャプチャ/コンペアマッチ割り込み */
#define		INTC_CH_ATUC8_BASE			(136)	/* GRC8_0~GRC8_3,OCRC8_0~OCRC8_3 インプットキャプチャ/コンペアマッチ割り込み */
	#define		INTC_CH_ATUC_SLIC80	(136)	/* GRC8_0,OCRC8_0 インプットキャプチャ/コンペアマッチ割り込み */
	#define		INTC_CH_ATUC_SLIC81	(137)	/* GRC8_1,OCRC8_1 インプットキャプチャ/コンペアマッチ割り込み */
	#define		INTC_CH_ATUC_SLIC82	(138)	/* GRC8_2,OCRC8_2 インプットキャプチャ/コンペアマッチ割り込み */
	#define		INTC_CH_ATUC_SLIC83	(139)	/* GRC8_3,OCRC8_3 インプットキャプチャ/コンペアマッチ割り込み */
#define		INTC_CH_ATUC9_BASE			(140)	/* GRC9_0~GRC9_3,OCRC9_0~OCRC9_3 インプットキャプチャ/コンペアマッチ割り込み */
	#define		INTC_CH_ATUC_SLIC90	(140)	/* GRC9_0,OCRC9_0 インプットキャプチャ/コンペアマッチ割り込み */
	#define		INTC_CH_ATUC_SLIC91	(141)	/* GRC9_1,OCRC9_1 インプットキャプチャ/コンペアマッチ割り込み */
	#define		INTC_CH_ATUC_SLIC92	(142)	/* GRC9_2,OCRC9_2 インプットキャプチャ/コンペアマッチ割り込み */
	#define		INTC_CH_ATUC_SLIC93	(143)	/* GRC9_3,OCRC9_3 インプットキャプチャ/コンペアマッチ割り込み */
#define		INTC_CH_ATUC10_BASE		(144)	/* GRC10_0~GRC10_3,OCRC10_0~OCRC10_3 インプットキャプチャ/コンペアマッチ割り込み */
	#define		INTC_CH_ATUC_SLIC100	(144)	/* GRC10_0,OCRC10_0 インプットキャプチャ/コンペアマッチ割り込み */
	#define		INTC_CH_ATUC_SLIC101	(145)	/* GRC10_1,OCRC10_1 インプットキャプチャ/コンペアマッチ割り込み */
	#define		INTC_CH_ATUC_SLIC102	(146)	/* GRC10_2,OCRC10_2 インプットキャプチャ/コンペアマッチ割り込み */
	#define		INTC_CH_ATUC_SLIC103	(147)	/* GRC10_3,OCRC10_3 インプットキャプチャ/コンペアマッチ割り込み */
                                                
/* ATU D */
#define		INTC_CH_ATUD0_BASE			(164)	/* OCR1D0_0~OCR1D0_3,OCR2D0_0~OCR2D0_3 コンペアマッチ、D0_0~D0_3 ON/OFF ワンショットパルス、UDID0_0~UDID0_3 ダウンカウンタアンダフロー 割り込み */
	#define		INTC_CH_ATUD_SLID00	(164)	/* OCR1D0_0,OCR2D0_0 コンペアマッチ、D0_0 ON/OFF ワンショットパルス、UDID0_0 ダウンカウンタアンダフロー 割り込み */
	#define		INTC_CH_ATUD_SLID01	(165)	/* OCR1D0_1,OCR2D0_1 コンペアマッチ、D0_1 ON/OFF ワンショットパルス、UDID0_1 ダウンカウンタアンダフロー 割り込み */
	#define		INTC_CH_ATUD_SLID02	(166)	/* OCR1D0_2,OCR2D0_2 コンペアマッチ、D0_2 ON/OFF ワンショットパルス、UDID0_2 ダウンカウンタアンダフロー 割り込み */
	#define		INTC_CH_ATUD_SLID03	(167)	/* OCR1D0_3,OCR2D0_3 コンペアマッチ、D0_3 ON/OFF ワンショットパルス、UDID0_3 ダウンカウンタアンダフロー 割り込み */
#define		INTC_CH_ATUD1_BASE			(168)	/* OCR1D1_0~OCR1D1_3,OCR2D1_0~OCR2D1_3 コンペアマッチ、D1_0~D1_3 ON/OFF ワンショットパルス、UDID1_0~UDID1_3 ダウンカウンタアンダフロー 割り込み */
	#define		INTC_CH_ATUD_SLID10	(168)	/* OCR1D1_0,OCR2D1_0 コンペアマッチ、D1_0 ON/OFF ワンショットパルス、UDID1_0 ダウンカウンタアンダフロー 割り込み */
	#define		INTC_CH_ATUD_SLID11	(169)	/* OCR1D1_1,OCR2D1_1 コンペアマッチ、D1_1 ON/OFF ワンショットパルス、UDID1_1 ダウンカウンタアンダフロー 割り込み */
	#define		INTC_CH_ATUD_SLID12	(170)	/* OCR1D1_2,OCR2D1_2 コンペアマッチ、D1_2 ON/OFF ワンショットパルス、UDID1_2 ダウンカウンタアンダフロー 割り込み */
	#define		INTC_CH_ATUD_SLID13	(171)	/* OCR1D1_3,OCR2D1_3 コンペアマッチ、D1_3 ON/OFF ワンショットパルス、UDID1_3 ダウンカウンタアンダフロー 割り込み */
#define		INTC_CH_ATUD2_BASE			(172)	/* OCR1D2_0~OCR1D2_3,OCR2D2_0~OCR2D2_3 コンペアマッチ、D2_0~D2_3 ON/OFF ワンショットパルス、UDID2_0~UDID2_3 ダウンカウンタアンダフロー 割り込み */
	#define		INTC_CH_ATUD_SLID20	(172)	/* OCR1D2_0,OCR2D2_0 コンペアマッチ、D2_0 ON/OFF ワンショットパルス、UDID2_0 ダウンカウンタアンダフロー 割り込み */
	#define		INTC_CH_ATUD_SLID21	(173)	/* OCR1D2_1,OCR2D2_1 コンペアマッチ、D2_1 ON/OFF ワンショットパルス、UDID2_1 ダウンカウンタアンダフロー 割り込み */
	#define		INTC_CH_ATUD_SLID22	(174)	/* OCR1D2_2,OCR2D2_2 コンペアマッチ、D2_2 ON/OFF ワンショットパルス、UDID2_2 ダウンカウンタアンダフロー 割り込み */
	#define		INTC_CH_ATUD_SLID23	(175)	/* OCR1D2_3,OCR2D2_3 コンペアマッチ、D2_3 ON/OFF ワンショットパルス、UDID2_3 ダウンカウンタアンダフロー 割り込み */
#define		INTC_CH_ATUD3_BASE			(176)	/* OCR1D3_0~OCR1D3_3,OCR2D3_0~OCR2D3_3 コンペアマッチ、D3_0~D3_3 ON/OFF ワンショットパルス、UDID3_0~UDID3_3 ダウンカウンタアンダフロー 割り込み */
	#define		INTC_CH_ATUD_SLID30	(176)	/* OCR1D3_0,OCR2D3_0 コンペアマッチ、D3_0 ON/OFF ワンショットパルス、UDID3_0 ダウンカウンタアンダフロー 割り込み */
	#define		INTC_CH_ATUD_SLID31	(177)	/* OCR1D3_1,OCR2D3_1 コンペアマッチ、D3_1 ON/OFF ワンショットパルス、UDID3_1 ダウンカウンタアンダフロー 割り込み */
	#define		INTC_CH_ATUD_SLID32	(178)	/* OCR1D3_2,OCR2D3_2 コンペアマッチ、D3_2 ON/OFF ワンショットパルス、UDID3_2 ダウンカウンタアンダフロー 割り込み */
	#define		INTC_CH_ATUD_SLID33	(179)	/* OCR1D3_3,OCR2D3_3 コンペアマッチ、D3_3 ON/OFF ワンショットパルス、UDID3_3 ダウンカウンタアンダフロー 割り込み */
#define		INTC_CH_ATUD4_BASE			(180)	/* OCR1D4_0~OCR1D4_3,OCR2D4_0~OCR2D4_3 コンペアマッチ、D4_0~D4_3 ON/OFF ワンショットパルス、UDID4_0~UDID4_3 ダウンカウンタアンダフロー 割り込み */
	#define		INTC_CH_ATUD_SLID40	(180)	/* OCR1D4_0,OCR2D4_0 コンペアマッチ、D4_0 ON/OFF ワンショットパルス、UDID4_0 ダウンカウンタアンダフロー 割り込み */
	#define		INTC_CH_ATUD_SLID41	(181)	/* OCR1D4_1,OCR2D4_1 コンペアマッチ、D4_1 ON/OFF ワンショットパルス、UDID4_1 ダウンカウンタアンダフロー 割り込み */
	#define		INTC_CH_ATUD_SLID42	(182)	/* OCR1D4_2,OCR2D4_2 コンペアマッチ、D4_2 ON/OFF ワンショットパルス、UDID4_2 ダウンカウンタアンダフロー 割り込み */
	#define		INTC_CH_ATUD_SLID43	(183)	/* OCR1D4_3,OCR2D4_3 コンペアマッチ、D4_3 ON/OFF ワンショットパルス、UDID4_3 ダウンカウンタアンダフロー 割り込み */
#define		INTC_CH_ATUD5_BASE			(184)	/* OCR1D5_0~OCR1D5_3,OCR2D5_0~OCR2D5_3 コンペアマッチ、D5_0~D5_3 ON/OFF ワンショットパルス、UDID5_0~UDID5_3 ダウンカウンタアンダフロー 割り込み */
	#define		INTC_CH_ATUD_SLID50	(184)	/* OCR1D5_0,OCR2D5_0 コンペアマッチ、D5_0 ON/OFF ワンショットパルス、UDID5_0 ダウンカウンタアンダフロー 割り込み */
	#define		INTC_CH_ATUD_SLID51	(185)	/* OCR1D5_1,OCR2D5_1 コンペアマッチ、D5_1 ON/OFF ワンショットパルス、UDID5_1 ダウンカウンタアンダフロー 割り込み */
	#define		INTC_CH_ATUD_SLID52	(186)	/* OCR1D5_2,OCR2D5_2 コンペアマッチ、D5_2 ON/OFF ワンショットパルス、UDID5_2 ダウンカウンタアンダフロー 割り込み */
	#define		INTC_CH_ATUD_SLID53	(187)	/* OCR1D5_3,OCR2D5_3 コンペアマッチ、D5_3 ON/OFF ワンショットパルス、UDID5_3 ダウンカウンタアンダフロー 割り込み */
#define		INTC_CH_ATUD6_BASE			(188)	/* OCR1D6_0~OCR1D6_3,OCR2D6_0~OCR2D6_3 コンペアマッチ、D6_0~D6_3 ON/OFF ワンショットパルス、UDID6_0~UDID6_3 ダウンカウンタアンダフロー 割り込み */
	#define		INTC_CH_ATUD_SLID60	(188)	/* OCR1D6_0,OCR2D6_0 コンペアマッチ、D6_0 ON/OFF ワンショットパルス、UDID6_0 ダウンカウンタアンダフロー 割り込み */
	#define		INTC_CH_ATUD_SLID61	(189)	/* OCR1D6_1,OCR2D6_1 コンペアマッチ、D6_1 ON/OFF ワンショットパルス、UDID6_1 ダウンカウンタアンダフロー 割り込み */
	#define		INTC_CH_ATUD_SLID62	(190)	/* OCR1D6_2,OCR2D6_2 コンペアマッチ、D6_2 ON/OFF ワンショットパルス、UDID6_2 ダウンカウンタアンダフロー 割り込み */
	#define		INTC_CH_ATUD_SLID63	(191)	/* OCR1D6_3,OCR2D6_3 コンペアマッチ、D6_3 ON/OFF ワンショットパルス、UDID6_3 ダウンカウンタアンダフロー 割り込み */
#define		INTC_CH_ATUD7_BASE			(192)	/* OCR1D7_0~OCR1D7_3,OCR2D7_0~OCR2D7_3 コンペアマッチ、D7_0~D7_3 ON/OFF ワンショットパルス、UDID7_0~UDID7_3 ダウンカウンタアンダフロー 割り込み */
	#define		INTC_CH_ATUD_SLID70	(192)	/* OCR1D7_0,OCR2D7_0 コンペアマッチ、D7_0 ON/OFF ワンショットパルス、UDID7_0 ダウンカウンタアンダフロー 割り込み */
	#define		INTC_CH_ATUD_SLID71	(193)	/* OCR1D7_1,OCR2D7_1 コンペアマッチ、D7_1 ON/OFF ワンショットパルス、UDID7_1 ダウンカウンタアンダフロー 割り込み */
	#define		INTC_CH_ATUD_SLID72	(194)	/* OCR1D7_2,OCR2D7_2 コンペアマッチ、D7_2 ON/OFF ワンショットパルス、UDID7_2 ダウンカウンタアンダフロー 割り込み */
	#define		INTC_CH_ATUD_SLID73	(195)	/* OCR1D7_3,OCR2D7_3 コンペアマッチ、D7_3 ON/OFF ワンショットパルス、UDID7_3 ダウンカウンタアンダフロー 割り込み */

/* ATU E */
#define		INTC_CH_ATUE0_BASE			(212)	/* CYLRE0_0~CYLRE0_3, サイクルコンペアマッチ、DTRE0_0~DTRE0_3 デューティコンペアマッチ 割り込み */
	#define		INTC_CH_ATUE_CMIE00	(212)	/* CYLRE0_0, サイクルコンペアマッチ、DTRE0_0 デューティコンペアマッチ 割り込み */
	#define		INTC_CH_ATUE_CMIE01	(213)	/* CYLRE0_1, サイクルコンペアマッチ、DTRE0_1 デューティコンペアマッチ 割り込み */
	#define		INTC_CH_ATUE_CMIE02	(214)	/* CYLRE0_2, サイクルコンペアマッチ、DTRE0_2 デューティコンペアマッチ 割り込み */
	#define		INTC_CH_ATUE_CMIE03	(215)	/* CYLRE0_3, サイクルコンペアマッチ、DTRE0_3 デューティコンペアマッチ 割り込み */
#define		INTC_CH_ATUE1_BASE			(216)	/* CYLRE1_0~CYLRE1_3, サイクルコンペアマッチ、DTRE1_0~DTRE1_3 デューティコンペアマッチ 割り込み */
	#define		INTC_CH_ATUE_CMIE10	(216)	/* CYLRE1_0, サイクルコンペアマッチ、DTRE1_0 デューティコンペアマッチ 割り込み */
	#define		INTC_CH_ATUE_CMIE11	(217)	/* CYLRE1_1, サイクルコンペアマッチ、DTRE1_1 デューティコンペアマッチ 割り込み */
	#define		INTC_CH_ATUE_CMIE12	(218)	/* CYLRE1_2, サイクルコンペアマッチ、DTRE1_2 デューティコンペアマッチ 割り込み */
	#define		INTC_CH_ATUE_CMIE13	(219)	/* CYLRE1_3, サイクルコンペアマッチ、DTRE1_3 デューティコンペアマッチ 割り込み */
#define		INTC_CH_ATUE2_BASE			(220)	/* CYLRE2_0~CYLRE2_3, サイクルコンペアマッチ、DTRE2_0~DTRE2_3 デューティコンペアマッチ 割り込み */
	#define		INTC_CH_ATUE_CMIE20	(220)	/* CYLRE2_0, サイクルコンペアマッチ、DTRE2_0 デューティコンペアマッチ 割り込み */
	#define		INTC_CH_ATUE_CMIE21	(221)	/* CYLRE2_1, サイクルコンペアマッチ、DTRE2_1 デューティコンペアマッチ 割り込み */
	#define		INTC_CH_ATUE_CMIE22	(222)	/* CYLRE2_2, サイクルコンペアマッチ、DTRE2_2 デューティコンペアマッチ 割り込み */
	#define		INTC_CH_ATUE_CMIE23	(223)	/* CYLRE2_3, サイクルコンペアマッチ、DTRE2_3 デューティコンペアマッチ 割り込み */
#define		INTC_CH_ATUE3_BASE			(224)	/* CYLRE3_0~CYLRE3_3, サイクルコンペアマッチ、DTRE3_0~DTRE3_3 デューティコンペアマッチ 割り込み */
	#define		INTC_CH_ATUE_CMIE30	(224)	/* CYLRE3_0, サイクルコンペアマッチ、DTRE3_0 デューティコンペアマッチ 割り込み */
	#define		INTC_CH_ATUE_CMIE31	(225)	/* CYLRE3_1, サイクルコンペアマッチ、DTRE3_1 デューティコンペアマッチ 割り込み */
	#define		INTC_CH_ATUE_CMIE32	(226)	/* CYLRE3_2, サイクルコンペアマッチ、DTRE3_2 デューティコンペアマッチ 割り込み */
	#define		INTC_CH_ATUE_CMIE33	(227)	/* CYLRE3_3, サイクルコンペアマッチ、DTRE3_3 デューティコンペアマッチ 割り込み */
#define		INTC_CH_ATUE4_BASE			(228)	/* CYLRE4_0~CYLRE4_3, サイクルコンペアマッチ、DTRE4_0~DTRE4_3 デューティコンペアマッチ 割り込み */
	#define		INTC_CH_ATUE_CMIE40	(228)	/* CYLRE4_0, サイクルコンペアマッチ、DTRE5_0 デューティコンペアマッチ 割り込み */
	#define		INTC_CH_ATUE_CMIE41	(229)	/* CYLRE4_1, サイクルコンペアマッチ、DTRE4_1 デューティコンペアマッチ 割り込み */
	#define		INTC_CH_ATUE_CMIE42	(230)	/* CYLRE4_2, サイクルコンペアマッチ、DTRE4_2 デューティコンペアマッチ 割り込み */
	#define		INTC_CH_ATUE_CMIE43	(231)	/* CYLRE4_3, サイクルコンペアマッチ、DTRE4_3 デューティコンペアマッチ 割り込み */
#define		INTC_CH_ATUE5_BASE			(232)	/* CYLRE5_0~CYLRE5_3, サイクルコンペアマッチ、DTRE5_0~DTRE5_3 デューティコンペアマッチ 割り込み */
	#define		INTC_CH_ATUE_CMIE50	(232)	/* CYLRE5_0, サイクルコンペアマッチ、DTRE5_0 デューティコンペアマッチ 割り込み */
	#define		INTC_CH_ATUE_CMIE51	(233)	/* CYLRE5_1, サイクルコンペアマッチ、DTRE5_1 デューティコンペアマッチ 割り込み */
	#define		INTC_CH_ATUE_CMIE52	(234)	/* CYLRE5_2, サイクルコンペアマッチ、DTRE5_2 デューティコンペアマッチ 割り込み */
	#define		INTC_CH_ATUE_CMIE53	(235)	/* CYLRE5_3, サイクルコンペアマッチ、DTRE5_3 デューティコンペアマッチ 割り込み */
#define		INTC_CH_ATUE6_BASE			(236)	/* CYLRE6_0~CYLRE6_3, サイクルコンペアマッチ、DTRE6_0~DTRE6_3 デューティコンペアマッチ 割り込み */
	#define		INTC_CH_ATUE_CMIE60	(236)	/* CYLRE6_0, サイクルコンペアマッチ、DTRE6_0 デューティコンペアマッチ 割り込み */
	#define		INTC_CH_ATUE_CMIE61	(237)	/* CYLRE6_1, サイクルコンペアマッチ、DTRE6_1 デューティコンペアマッチ 割り込み */
	#define		INTC_CH_ATUE_CMIE62	(238)	/* CYLRE6_2, サイクルコンペアマッチ、DTRE6_2 デューティコンペアマッチ 割り込み */
	#define		INTC_CH_ATUE_CMIE63	(239)	/* CYLRE6_3, サイクルコンペアマッチ、DTRE6_3 デューティコンペアマッチ 割り込み */
#define		INTC_CH_ATUE7_BASE			(240)	/* CYLRE7_0~CYLRE7_3, サイクルコンペアマッチ、DTRE7_0~DTRE7_3 デューティコンペアマッチ 割り込み */
	#define		INTC_CH_ATUE_CMIE70	(240)	/* CYLRE7_0, サイクルコンペアマッチ、DTRE7_0 デューティコンペアマッチ 割り込み */
	#define		INTC_CH_ATUE_CMIE71	(241)	/* CYLRE7_1, サイクルコンペアマッチ、DTRE7_1 デューティコンペアマッチ 割り込み */
	#define		INTC_CH_ATUE_CMIE72	(242)	/* CYLRE7_2, サイクルコンペアマッチ、DTRE7_2 デューティコンペアマッチ 割り込み */
	#define		INTC_CH_ATUE_CMIE73	(243)	/* CYLRE7_3, サイクルコンペアマッチ、DTRE7_3 デューティコンペアマッチ 割り込み */
#define		INTC_CH_ATUE8_BASE			(244)	/* CYLRE8_0~CYLRE8_3, サイクルコンペアマッチ、DTRE8_0~DTRE8_3 デューティコンペアマッチ 割り込み */
	#define		INTC_CH_ATUE_CMIE80	(244)	/* CYLRE8_0, サイクルコンペアマッチ、DTRE8_0 デューティコンペアマッチ 割り込み */
	#define		INTC_CH_ATUE_CMIE81	(245)	/* CYLRE8_1, サイクルコンペアマッチ、DTRE8_1 デューティコンペアマッチ 割り込み */
	#define		INTC_CH_ATUE_CMIE82	(246)	/* CYLRE8_2, サイクルコンペアマッチ、DTRE8_2 デューティコンペアマッチ 割り込み */
	#define		INTC_CH_ATUE_CMIE83	(247)	/* CYLRE8_3, サイクルコンペアマッチ、DTRE8_3 デューティコンペアマッチ 割り込み */

/* ATU F */
#define		INTC_CH_ATUF0_ICIF_BASE	(252)	/* Timer F0~F15 インプットキャプチャ割り込み */
	#define		INTC_CH_ATUF0_ICIF0	(252)	/* Timer F0 インプットキャプチャ割り込み */
	#define		INTC_CH_ATUF0_ICIF1	(253)	/* Timer F1 インプットキャプチャ割り込み */
	#define		INTC_CH_ATUF0_ICIF2	(254)	/* Timer F2 インプットキャプチャ割り込み */
	#define		INTC_CH_ATUF0_ICIF3	(255)	/* Timer F3 インプットキャプチャ割り込み */
	#define		INTC_CH_ATUF0_ICIF4	(256)	/* Timer F4 インプットキャプチャ割り込み */
	#define		INTC_CH_ATUF0_ICIF5	(257)	/* Timer F5 インプットキャプチャ割り込み */
	#define		INTC_CH_ATUF0_ICIF6	(258)	/* Timer F6 インプットキャプチャ割り込み */
	#define		INTC_CH_ATUF0_ICIF7	(259)	/* Timer F7 インプットキャプチャ割り込み */
	#define		INTC_CH_ATUF0_ICIF8	(260)	/* Timer F8 インプットキャプチャ割り込み */
	#define		INTC_CH_ATUF0_ICIF9	(261)	/* Timer F9 インプットキャプチャ割り込み */
	#define		INTC_CH_ATUF0_ICIF10	(262)	/* Timer F10 インプットキャプチャ割り込み */
	#define		INTC_CH_ATUF0_ICIF11	(263)	/* Timer F11 インプットキャプチャ割り込み */
	#define		INTC_CH_ATUF0_ICIF12	(264)	/* Timer F12 インプットキャプチャ割り込み */
	#define		INTC_CH_ATUF0_ICIF13	(265)	/* Timer F13 インプットキャプチャ割り込み */
	#define		INTC_CH_ATUF0_ICIF14	(266)	/* Timer F14 インプットキャプチャ割り込み */
	#define		INTC_CH_ATUF0_ICIF15	(267)	/* Timer F15 インプットキャプチャ割り込み */

/* ATU G */
#define		INTC_CH_ATUG_CMIG0			(272)	/* OCRG0 コンペアマッチ割り込み */
#define		INTC_CH_ATUG_CMIG1			(273)	/* OCRG1 コンペアマッチ割り込み */
#define		INTC_CH_ATUG_CMIG2			(274)	/* OCRG2 コンペアマッチ割り込み */
#define		INTC_CH_ATUG_CMIG3			(275)	/* OCRG3 コンペアマッチ割り込み */
#define		INTC_CH_ATUG_CMIG4			(276)	/* OCRG4 コンペアマッチ割り込み */
#define		INTC_CH_ATUG_CMIG5			(277)	/* OCRG5 コンペアマッチ割り込み */
#define		INTC_CH_ATUG_CMIG6			(278)	/* OCRG6 コンペアマッチ割り込み */
#define		INTC_CH_ATUG_CMIG7			(279)	/* OCRG7 コンペアマッチ割り込み */
#define		INTC_CH_ATUG_CMIG8			(280)	/* OCRG8 コンペアマッチ割り込み */
#define		INTC_CH_ATUG_CMIG9			(281)	/* OCRG9 コンペアマッチ割り込み */
#define		INTC_CH_ATUG_CMIG10			(282)	/* OCRG10 コンペアマッチ割り込み */
#define		INTC_CH_ATUG_CMIG11			(283)	/* OCRG11 コンペアマッチ割り込み */
#define		INTC_CH_ATUG_CMIG12			(284)	/* OCRG12 コンペアマッチ割り込み */
#define		INTC_CH_ATUG_CMIG13			(285)	/* OCRG13 コンペアマッチ割り込み */

/* ATU MULTI D */
#define		INTC_CH_ATU_MULTID0			(286)	/* Timer D マルチショットパルス機能書込要求割り込み0 、Timer D マルチショットパルス機能終了割り込みサブブロック0 、Timer D マルチショットパルス機能チャネル同期機能書込要求割り込みサブブロック0 */
#define		INTC_CH_ATU_MULTID1			(287)	/* Timer D マルチショットパルス機能書込要求割り込み1 、Timer D マルチショットパルス機能終了割り込みサブブロック1 、Timer D マルチショットパルス機能チャネル同期機能書込要求割り込みサブブロック1 */
#define		INTC_CH_ATU_MULTID2			(288)	/* Timer D マルチショットパルス機能書込要求割り込み2、Timer D マルチショットパルス機能終了割り込みサブブロック2、Timer D マルチショットパルス機能チャネル同期機能書込要求割り込みサブブロック2 */
#define		INTC_CH_ATU_MULTID3			(289)	/* Timer D マルチショットパルス機能書込要求割り込み3 、Timer D マルチショットパルス機能終了割り込みサブブロック3 、Timer D マルチショットパルス機能チャネル同期機能書込要求割り込みサブブロック3 */
#define		INTC_CH_ATU_MULTID4			(290)	/* Timer D マルチショットパルス機能書込要求割り込み4 、Timer D マルチショットパルス機能終了割り込みサブブロック4 、Timer D マルチショットパルス機能チャネル同期機能書込要求割り込みサブブロック4 */

/* ENCA */
#define		INTC_CH_ENCA1IOV_304		(304)	/* ENCA1 オーバーフロー割り込み */
#define		INTC_CH_ENCA1I0_305			(305)	/* ENCA1 キャプチャ/コンペアマッチ割り込み0 */
#define		INTC_CH_ENCA1I1_306			(306)	/* ENCA1 キャプチャ/コンペアマッチ割り込み1 */
#define		INTC_CH_ENCA1IUD_307		(307)	/* ENCA1 アンダーフロー割り込み */
#define		INTC_CH_ENCA1IEC_308		(308)	/* ENCA1 エンコーダクリア割り込み (フェーズZ) */

#define		INTC_CH_ENCA0IOV			(309)	/* ENCA0 オーバーフロー割り込み */
#define		INTC_CH_ENCA0I0				(310)	/* ENCA0 キャプチャ/コンペアマッチ割り込み0 */
#define		INTC_CH_ENCA0I1				(311)	/* ENCA0 キャプチャ/コンペアマッチ割り込み1 */
#define		INTC_CH_ENCA0IUD			(312)	/* ENCA0 アンダーフロー割り込み */
#define		INTC_CH_ENCA0IEC			(313)	/* ENCA0 エンコーダクリア割り込み (フェーズZ) */

#define		INTC_CH_ENCA1IOV_421		(421)	/* ENCA1 オーバーフロー割り込み */
#define		INTC_CH_ENCA1I0_422			(422)	/* ENCA1 キャプチャ/コンペアマッチ割り込み0 */
#define		INTC_CH_ENCA1I1_423			(423)	/* ENCA1 キャプチャ/コンペアマッチ割り込み1 */
#define		INTC_CH_ENCA1IUD_424		(424)	/* ENCA1 アンダーフロー割り込み */
#define		INTC_CH_ENCA1IEC_425		(425)	/* ENCA1 エンコーダクリア割り込み (フェーズZ) */

#define		INTC_CH_ENCA1IOV_505		(505)	/* ENCA1 オーバーフロー割り込み */
#define		INTC_CH_ENCA1I0_506			(506)	/* ENCA1 キャプチャ/コンペアマッチ割り込み0 */
#define		INTC_CH_ENCA1I1_507			(507)	/* ENCA1 キャプチャ/コンペアマッチ割り込み0 */
#define		INTC_CH_ENCA1IUD_508		(508)	/* ENCA1 アンダーフロー割り込み */
#define		INTC_CH_ENCA1IEC_509		(509)	/* ENCA1 エンコーダクリア割り込み (フェーズZ) */

/* TAPA */
#define		INTC_CH_TAPA0IPEK0			(314)	/* TAPA0ピーク割り込み0 */
#define		INTC_CH_TAPA0IVLY0			(315)	/* TAPA0バレー割り込み0 */
#define		INTC_CH_TAPA1IPEK0			(316)	/* TAPA1ピーク割り込み0 */
#define		INTC_CH_TAPA1IVLY0			(317)	/* TAPA1バレー割り込み0 */
#define		INTC_CH_TAPA2IPEK0			(318)	/* TAPA2ピーク割り込み0 */
#define		INTC_CH_TAPA2IVLY0			(319)	/* TAPA2バレー割り込み0 */

/* TAUD0 */
#define		INTC_CH_TAUD0_I1			(320)	/* TAUD0 チャンネル1割り込み */
#define		INTC_CH_TAUD0_I3			(321)	/* TAUD0 チャンネル3割り込み */
#define		INTC_CH_TAUD0_I5			(322)	/* TAUD0 チャンネル5割り込み */
#define		INTC_CH_TAUD0_I7			(323)	/* TAUD0 チャンネル7割り込み */
#define		INTC_CH_TAUD0_I9			(324)	/* TAUD0 チャンネル9割り込み */
#define		INTC_CH_TAUD0_I11			(325)	/* TAUD0 チャンネル11割り込み */
#define		INTC_CH_TAUD0_I13			(326)	/* TAUD0 チャンネル13割り込み */
#define		INTC_CH_TAUD0_I15			(327)	/* TAUD0 チャンネル15割り込み */

/* TAUD1 */
#define		INTC_CH_TAUD1_I0			(328)	/* TAUD1 チャンネル0割り込み */
#define		INTC_CH_TAUD1_I1			(329)	/* TAUD1 チャンネル1割り込み */
#define		INTC_CH_TAUD1_I2			(330)	/* TAUD1 チャンネル2割り込み */
#define		INTC_CH_TAUD1_I3			(331)	/* TAUD1 チャンネル3割り込み */
#define		INTC_CH_TAUD1_I4			(332)	/* TAUD1 チャンネル4割り込み */
#define		INTC_CH_TAUD1_I5			(333)	/* TAUD1 チャンネル5割り込み */
#define		INTC_CH_TAUD1_I6			(334)	/* TAUD1 チャンネル6割り込み */
#define		INTC_CH_TAUD1_I7			(335)	/* TAUD1 チャンネル7割り込み */
#define		INTC_CH_TAUD1_I8			(336)	/* TAUD1 チャンネル8割り込み */
#define		INTC_CH_TAUD1_I9			(337)	/* TAUD1 チャンネル9割り込み */
#define		INTC_CH_TAUD1_I10			(338)	/* TAUD1 チャンネル10割り込み */
#define		INTC_CH_TAUD1_I11			(339)	/* TAUD1 チャンネル11割り込み */
#define		INTC_CH_TAUD1_I12			(340)	/* TAUD1 チャンネル12割り込み */
#define		INTC_CH_TAUD1_I13			(341)	/* TAUD1 チャンネル13割り込み */
#define		INTC_CH_TAUD1_I14			(342)	/* TAUD1 チャンネル14割り込み */
#define		INTC_CH_TAUD1_I15			(343)	/* TAUD1 チャンネル15割り込み */

/* TAUD2 */
#define		INTC_CH_TAUD2_I0			(344)	/* TAUD2 チャンネル0割り込み */
#define		INTC_CH_TAUD2_I1			(345)	/* TAUD2 チャンネル1割り込み */
#define		INTC_CH_TAUD2_I2			(346)	/* TAUD2 チャンネル2割り込み */
#define		INTC_CH_TAUD2_I3			(347)	/* TAUD2 チャンネル3割り込み */
#define		INTC_CH_TAUD2_I4			(348)	/* TAUD2 チャンネル4割り込み */
#define		INTC_CH_TAUD2_I5			(349)	/* TAUD2 チャンネル5割り込み */
#define		INTC_CH_TAUD2_I6			(350)	/* TAUD2 チャンネル6割り込み */
#define		INTC_CH_TAUD2_I7			(351)	/* TAUD2 チャンネル7割り込み */
#define		INTC_CH_TAUD2_I8			(352)	/* TAUD2 チャンネル8割り込み */
#define		INTC_CH_TAUD2_I9			(353)	/* TAUD2 チャンネル9割り込み */
#define		INTC_CH_TAUD2_I10			(354)	/* TAUD2 チャンネル10割り込み */
#define		INTC_CH_TAUD2_I11			(355)	/* TAUD2 チャンネル11割り込み */
#define		INTC_CH_TAUD2_I12			(356)	/* TAUD2 チャンネル12割り込み */
#define		INTC_CH_TAUD2_I13			(357)	/* TAUD2 チャンネル13割り込み */
#define		INTC_CH_TAUD2_I14			(358)	/* TAUD2 チャンネル14割り込み */
#define		INTC_CH_TAUD2_I15			(359)	/* TAUD2 チャンネル15割り込み */

/* TAUD3 */
#define		INTC_CH_TAUD3_I0_379		(379)	/* TAUD3 チャンネル0割り込み */
#define		INTC_CH_TAUD3_I1_380		(380)	/* TAUD3 チャンネル1割り込み */
#define		INTC_CH_TAUD3_I2_381		(381)	/* TAUD3 チャンネル2割り込み */
#define		INTC_CH_TAUD3_I3_382		(382)	/* TAUD3 チャンネル3割り込み */
#define		INTC_CH_TAUD3_I4_383		(383)	/* TAUD3 チャンネル4割り込み */
#define		INTC_CH_TAUD3_I5_384		(384)	/* TAUD3 チャンネル4割り込み */
#define		INTC_CH_TAUD3_I6_385		(385)	/* TAUD3 チャンネル5割り込み */
#define		INTC_CH_TAUD3_I7_386		(386)	/* TAUD3 チャンネル6割り込み */
#define		INTC_CH_TAUD3_I8_387		(387)	/* TAUD3 チャンネル8割り込み */
#define		INTC_CH_TAUD3_I9_388		(388)	/* TAUD3 チャンネル9割り込み */
#define		INTC_CH_TAUD3_I10_389		(389)	/* TAUD3 チャンネル10割り込み */
#define		INTC_CH_TAUD3_I11_390		(390)	/* TAUD3 チャンネル11割り込み */
#define		INTC_CH_TAUD3_I12_391		(391)	/* TAUD3 チャンネル12割り込み */
#define		INTC_CH_TAUD3_I13_392		(392)	/* TAUD3 チャンネル13割り込み */
#define		INTC_CH_TAUD3_I14_393		(393)	/* TAUD3 チャンネル14割り込み */
#define		INTC_CH_TAUD3_I15_394		(394)	/* TAUD3 チャンネル15割り込み */
#define		INTC_CH_TAUD3_I0_505		(505)	/* TAUD3チャンネル0割り込み */
#define		INTC_CH_TAUD3_I1_506		(506)	/* TAUD3チャンネル1割り込み */
#define		INTC_CH_TAUD3_I2_507		(507)	/* TAUD3チャンネル2割り込み */
#define		INTC_CH_TAUD3_I3_508		(508)	/* TAUD3チャンネル3割り込み */
#define		INTC_CH_TAUD3_I4_509		(509)	/* TAUD3チャンネル4割り込み */
#define		INTC_CH_TAUD3_I5_510		(510)	/* TAUD3チャンネル5割り込み */
#define		INTC_CH_TAUD3_I6_511		(511)	/* TAUD3チャンネル6割り込み */
#define		INTC_CH_TAUD3_I7_512		(512)	/* TAUD3チャンネル7割り込み */
#define		INTC_CH_TAUD3_I8_513		(513)	/* TAUD3チャンネル8割り込み */
#define		INTC_CH_TAUD3_I9_514		(514)	/* TAUD3チャンネル9割り込み */
#define		INTC_CH_TAUD3_I10_515		(515)	/* TAUD3チャンネル10割り込み */
#define		INTC_CH_TAUD3_I11_516		(516)	/* TAUD3チャンネル11割り込み */
#define		INTC_CH_TAUD3_I12_517		(517)	/* TAUD3チャンネル12割り込み */
#define		INTC_CH_TAUD3_I13_518		(518)	/* TAUD3チャンネル13割り込み */
#define		INTC_CH_TAUD3_I14_519		(519)	/* TAUD3チャンネル14割り込み */
#define		INTC_CH_TAUD3_I15_520		(520)	/* TAUD3チャンネル15割り込み */
#define		INTC_CH_TAUD3_I0_793		(793)	/* TAUD3チャンネル0割り込み */
#define		INTC_CH_TAUD3_I1_794		(794)	/* TAUD3チャンネル1割り込み */
#define		INTC_CH_TAUD3_I2_795		(795)	/* TAUD3チャンネル2割り込み */
#define		INTC_CH_TAUD3_I3_796		(796)	/* TAUD3チャンネル3割り込み */
#define		INTC_CH_TAUD3_I4_797		(797)	/* TAUD3チャンネル4割り込み */
#define		INTC_CH_TAUD3_I5_798		(798)	/* TAUD3チャンネル5割り込み */
#define		INTC_CH_TAUD3_I6_799		(799)	/* TAUD3チャンネル6割り込み */
#define		INTC_CH_TAUD3_I7_800		(800)	/* TAUD3チャンネル7割り込み */
#define		INTC_CH_TAUD3_I8_801		(801)	/* TAUD3チャンネル8割り込み */
#define		INTC_CH_TAUD3_I9_802		(802)	/* TAUD3チャンネル9割り込み */
#define		INTC_CH_TAUD3_I10_803		(803)	/* TAUD3チャンネル10割り込み */
#define		INTC_CH_TAUD3_I11_804		(804)	/* TAUD3チャンネル11割り込み */
#define		INTC_CH_TAUD3_I12_817		(817)	/* TAUD3チャンネル12割り込み */
#define		INTC_CH_TAUD3_I13_818		(818)	/* TAUD3チャンネル13割り込み */
#define		INTC_CH_TAUD3_I14_819		(819)	/* TAUD3チャンネル14割り込み */
#define		INTC_CH_TAUD3_I15_820		(820)	/* TAUD3チャンネル15割り込み */

/* TSG30 */
#define		INTC_CH_TSG30I0				(362)	/* TSG30コンペアマッチ割り込み0またはTSG30 周期割り込み (HTPWMモードのみ) */
#define		INTC_CH_TSG30I1				(363)	/* TSG30コンペアマッチ割り込み1 */
#define		INTC_CH_TSG30I2				(364)	/* TSG30コンペアマッチ割り込み2 */
#define		INTC_CH_TSG30I3				(365)	/* TSG30コンペアマッチ割り込み3 */
#define		INTC_CH_TSG30I4				(366)	/* TSG30コンペアマッチ割り込み4 */
#define		INTC_CH_TSG30I5				(367)	/* TSG30コンペアマッチ割り込み5 */
#define		INTC_CH_TSG30I6				(368)	/* TSG30コンペアマッチ割り込み6 */
#define		INTC_CH_TSG30I7				(369)	/* TSG30コンペアマッチ割り込み7 */
#define		INTC_CH_TSG30I8				(370)	/* TSG30コンペアマッチ割り込み8 */
#define		INTC_CH_TSG30I9				(371)	/* TSG30コンペアマッチ割り込み9 */
#define		INTC_CH_TSG30I10			(372)	/* TSG30コンペアマッチ割り込み10 */
#define		INTC_CH_TSG30I11			(373)	/* TSG30コンペアマッチ割り込み11 */
#define		INTC_CH_TSG30I12			(374)	/* TSG30コンペアマッチ割り込み12 */
#define		INTC_CH_TSG30IPEK			(375)	/* TSG30ピーク割り込み */
#define		INTC_CH_TSG30IVLY			(376)	/* TSG 30バレー割り込み */
#define		INTC_CH_TSG30IER			(377)	/* TSG 30 error割り込み */
#define		INTC_CH_TSG30IWN			(378)	/* TSG 30 warning割り込み */

/* TSG31 */
#define		INTC_CH_TSG31I0				(379)	/* TSG31コンペアマッチ割り込み0またはTSG30 周期割り込み (HTPWMモードのみ) */
#define		INTC_CH_TSG31I1				(380)	/* TSG31コンペアマッチ割り込み1 */
#define		INTC_CH_TSG31I2				(381)	/* TSG31コンペアマッチ割り込み2 */
#define		INTC_CH_TSG31I3				(382)	/* TSG31コンペアマッチ割り込み3 */
#define		INTC_CH_TSG31I4				(383)	/* TSG31コンペアマッチ割り込み4 */
#define		INTC_CH_TSG31I5				(384)	/* TSG31コンペアマッチ割り込み4 */
#define		INTC_CH_TSG31I6				(385)	/* TSG31コンペアマッチ割り込み5 */
#define		INTC_CH_TSG31I7				(386)	/* TSG31コンペアマッチ割り込み6 */
#define		INTC_CH_TSG31I8				(387)	/* TSG31コンペアマッチ割り込み8 */
#define		INTC_CH_TSG31I9				(388)	/* TSG31コンペアマッチ割り込み9 */
#define		INTC_CH_TSG31I10			(389)	/* TSG31コンペアマッチ割り込み10 */
#define		INTC_CH_TSG31I11			(390)	/* TSG31コンペアマッチ割り込み11 */
#define		INTC_CH_TSG31I12			(391)	/* TSG31コンペアマッチ割り込み12 */
#define		INTC_CH_TSG31IPEK			(392)	/* TSG31ピーク割り込み */
#define		INTC_CH_TSG31IVLY			(393)	/* TSG31バレー割り込み */
#define		INTC_CH_TSG31IER			(394)	/* TSG31 error割り込み */
#define		INTC_CH_TSG31IWN			(395)	/* TSG 31 warning割り込み */

/* TSG32 */
#define		INTC_CH_TSG32I0				(396)	/* TSG32コンペアマッチ割り込み0またはTSG32 周期割り込み (HTPWMモードのみ) */
#define		INTC_CH_TSG32I1				(397)	/* TSG32コンペアマッチ割り込み1 */
#define		INTC_CH_TSG32I2				(398)	/* TSG32コンペアマッチ割り込み2 */
#define		INTC_CH_TSG32I3				(399)	/* TSG32コンペアマッチ割り込み3 */
#define		INTC_CH_TSG32I4				(400)	/* TSG32コンペアマッチ割り込み4 */
#define		INTC_CH_TSG32I5				(401)	/* TSG32コンペアマッチ割り込み5 */
#define		INTC_CH_TSG32I6				(402)	/* TSG32コンペアマッチ割り込み6 */
#define		INTC_CH_TSG32I7				(403)	/* TSG32コンペアマッチ割り込み7 */
#define		INTC_CH_TSG32I8				(404)	/* TSG32コンペアマッチ割り込み8 */
#define		INTC_CH_TSG32I9				(405)	/* TSG32コンペアマッチ割り込み9 */
#define		INTC_CH_TSG32I10			(406)	/* TSG32コンペアマッチ割り込み10 */
#define		INTC_CH_TSG32I11			(407)	/* TSG32コンペアマッチ割り込み11 */
#define		INTC_CH_TSG32I12			(408)	/* TSG32コンペアマッチ割り込み12 */
#define		INTC_CH_TSG32IPEK			(409)	/* TSG32ピーク割り込み */
#define		INTC_CH_TSG32IVLY			(410)	/* TSG 32バレー割り込み */
#define		INTC_CH_TSG32IER			(411)	/* TSG 32 error割り込み */
#define		INTC_CH_TSG32IWN			(412)	/* TSG 32warning割り込み */

/* TPTMU */
#define		INTC_CH_TPTMU00				(413)	/* PE0のTPTMアップタイマー割り込み0 */
#define		INTC_CH_TPTMU01				(414)	/* PE0のTPTMアップタイマー割り込み1 */
#define		INTC_CH_TPTMU02				(415)	/* PE0のTPTMアップタイマー割り込み2 */
#define		INTC_CH_TPTMU03				(416)	/* PE0のTPTMアップタイマー割り込み3 */
#define		INTC_CH_TPTMU10				(417)	/* PE1のTPTMアップタイマー割り込み0 */
#define		INTC_CH_TPTMU11				(418)	/* PE1のTPTMアップタイマー割り込み1 */
#define		INTC_CH_TPTMU12				(419)	/* PE1のTPTMアップタイマー割り込み2 */
#define		INTC_CH_TPTMU13				(420)	/* PE1のTPTMアップタイマー割り込み3 */
#define		INTC_CH_TPTMU20				(843)	/* PE2のTPTMアップタイマー割り込み0 */
#define		INTC_CH_TPTMU21				(844)	/* PE2のTPTMアップタイマー割り込み1 */
#define		INTC_CH_TPTMU22				(845)	/* PE2のTPTMアップタイマー割り込み2 */
#define		INTC_CH_TPTMU23				(846)	/* PE2のTPTMアップタイマー割り込み3 */
#define		INTC_CH_TPTMU30				(847)	/* PE3のTPTMアップタイマー割り込み0 */
#define		INTC_CH_TPTMU31				(848)	/* PE3のTPTMアップタイマー割り込み1 */
#define		INTC_CH_TPTMU32				(849)	/* PE3のTPTMアップタイマー割り込み2 */
#define		INTC_CH_TPTMU33				(850)	/* PE3のTPTMアップタイマー割り込み3 */

/* RDC */
#define		INTC_CH_RDC3AL0CMP2			(421)	/* Phi比較割り込み出力2 (RDC3AL0) */
#define		INTC_CH_RDC3AS0CMP2			(421)	/* Phi比較割り込み出力2 (RDC3AS0) */
#define		INTC_CH_RDC3AL0CMP1			(422)	/* Phi比較割り込み出力1 (RDC3AL0) */
#define		INTC_CH_RDC3AS0CMP1			(422)	/* Phi比較割り込み出力1 (RDC3AS0) */
#define		INTC_CH_RDC3AL0CMP0			(423)	/* Phi比較割り込み出力0 (RDC3AL0) */
#define		INTC_CH_RDC3AS0CMP0			(423)	/* Phi比較割り込み出力0 (RDC3AS0) */
#define		INTC_CH_RDC3AL0ERR			(424)	/* 障害検出割り込み出力 (RDC3AL0) */
#define		INTC_CH_RDC3AS0ERR			(424)	/* 障害検出割り込み出力 (RDC3AS0) */
#define		INTC_CH_RDC3AL0ENCZ			(425)	/* Z信号割り込み出力 (RDC3 AL0) */
#define		INTC_CH_RDC3AS0ENCZ			(425)	/* Z信号割り込み出力 (RDC3 AS0) */
#define		INTC_CH_RDC3AL0EZC			(426)	/* Excitation zero-crossing 割り込み出力 (RDC3AL0) */
#define		INTC_CH_RDC3AS0EZC			(426)	/* Excitation zero-crossing 割り込み出力 (RDC3AS0) */
#define		INTC_CH_RDC3AL0ET			(427)	/* Excitation timer 割り込み出力 (RDC3AL0) */
#define		INTC_CH_RDC3AS0ET			(427)	/* Excitation timer 割り込み出力 (RDC3AS0) */
#define		INTC_CH_RDC3AL0BE			(428)	/* BIST終了割り込み出力 (RDC3AL0) */
#define		INTC_CH_RDC3AS0BE			(428)	/* BIST終了割り込み出力 (RDC3AS0) */
#define		INTC_CH_RDC3AL1CMP2			(429)	/* Phi比較割り込み出力2 (RDC3AL1) */
#define		INTC_CH_RDC3AS1CMP2			(429)	/* Phi比較割り込み出力2 (RDC3AS1) */
#define		INTC_CH_RDC3AL1CMP1			(430)	/* Phi比較割り込み出力1 (RDC3AL1) */
#define		INTC_CH_RDC3AS1CMP1			(430)	/* Phi比較割り込み出力1 (RDC3AS1) */
#define		INTC_CH_RDC3AL1CMP0			(431)	/* Phi比較割り込み出力0 (RDC3AL1) */
#define		INTC_CH_RDC3AS1CMP0			(431)	/* Phi比較割り込み出力0 (RDC3AS1) */
#define		INTC_CH_RDC3AL1ERR			(432)	/* 障害検出割り込み出力 (RDC3AL1) */
#define		INTC_CH_RDC3AS1ERR			(432)	/* 障害検出割り込み出力 (RDC3AS1) */
#define		INTC_CH_RDC3AL1ENCZ			(433)	/* Z信号割り込み出力 (RDC3AL1) */
#define		INTC_CH_RDC3AS1ENCZ			(433)	/* Z信号割り込み出力 (RDC3AS1) */
#define		INTC_CH_RDC3AL1EZC			(434)	/* Excitation zero-crossing 割り込み出力 (RDC3AL1) */
#define		INTC_CH_RDC3AS1EZC			(434)	/* Excitation zero-crossing 割り込み出力 (RDC3AS1) */
#define		INTC_CH_RDC3AL1ET			(435)	/* Excitation timer 割り込み出力 (RDC3AL1) */
#define		INTC_CH_RDC3AS1ET			(435)	/* Excitation timer 割り込み出力 (RDC3AS1) */
#define		INTC_CH_RDC3AL1BE			(436)	/* BIST終了割り込み出力 (RDC3AL1) */
#define		INTC_CH_RDC3AS1BE			(436)	/* BIST終了割り込み出力 (RDC3AS1) */

/* ADCH,DSADC,CADC */
#define		INTC_CH_ADC_ADMPXI0			(437)	/* ADCH0 MPX 割り込み要求 */
#define		INTC_CH_ADC_ADMPXI2			(438)	/* ADCH2 MPX 割り込み要求 */
#define		INTC_CH_ADC_ADMPXI1			(439)	/* ADCH1 MPX 割り込み要求 */
#define		INTC_CH_ADC_ADMPXI3			(440)	/* ADCH3 MPX 割り込み要求 */
#define		INTC_CH_ADC_ADI00			(441)	/* ADCH0 スキャングループ0 終了割り込み */
#define		INTC_CH_ADC_ADI01			(442)	/* ADCH0 スキャングループ1 終了割り込み */
#define		INTC_CH_ADC_ADI02			(443)	/* ADCH0 スキャングループ2 終了割り込み */
#define		INTC_CH_ADC_ADI03			(444)	/* ADCH0 スキャングループ3 終了割り込み */
#define		INTC_CH_ADC_ADI04			(445)	/* ADCH0 スキャングループ4 終了割り込み */
#define		INTC_CH_ADC_ADI20			(446)	/* ADCH2 スキャングループ0 終了割り込み */
#define		INTC_CH_ADC_ADI21			(447)	/* ADCH2 スキャングループ1 終了割り込み */
#define		INTC_CH_ADC_ADI22			(448)	/* ADCH2 スキャングループ2 終了割り込み */
#define		INTC_CH_ADC_ADI23			(449)	/* ADCH2 スキャングループ3 終了割り込み */
#define		INTC_CH_ADC_ADI24			(450)	/* ADCH2 スキャングループ4 終了割り込み */
#define		INTC_CH_ADC_ADI10			(451)	/* ADCH1 スキャングループ0 終了割り込み */
#define		INTC_CH_ADC_ADI11			(452)	/* ADCH1 スキャングループ1 終了割り込み */
#define		INTC_CH_ADC_ADI12			(453)	/* ADCH1 スキャングループ2 終了割り込み */
#define		INTC_CH_ADC_ADI13			(454)	/* ADCH1 スキャングループ3 終了割り込み */
#define		INTC_CH_ADC_ADI14			(455)	/* ADCH1 スキャングループ4 終了割り込み */
#define		INTC_CH_ADC_ADI30			(456)	/* ADCH3 スキャングループ0 終了割り込み */
#define		INTC_CH_ADC_ADI31			(457)	/* ADCH3 スキャングループ1 終了割り込み */
#define		INTC_CH_ADC_ADI32			(458)	/* ADCH3 スキャングループ2 終了割り込み */
#define		INTC_CH_ADC_ADI33			(459)	/* ADCH3 スキャングループ3 終了割り込み */
#define		INTC_CH_ADC_ADI34			(460)	/* ADCH3 スキャングループ4 終了割り込み */
#define		INTC_CH_ADC_ADE0			(461)	/* ADCH0 AD エラー割り込み要求 */
#define		INTC_CH_ADC_ADE2			(462)	/* ADCH2 AD エラー割り込み要求 */
#define		INTC_CH_ADC_ADE1			(463)	/* ADCH1 AD エラー割り込み要求 */
#define		INTC_CH_ADC_ADE3			(464)	/* ADCH3 AD エラー割り込み要求 */
/* DSADC */
#define		INTC_CH_DSADERR00			(465)	/* DSADE00 DSAD エラー割り込み要求*/
#define		INTC_CH_DSADERR10			(466)	/* DSADE10 DSAD エラー割り込み要求*/
#define		INTC_CH_DSADERR20			(467)	/* DSADE20 DSAD エラー割り込み要求*/
#define		INTC_CH_DSADERR12			(468)	/* DSADE12 DSAD エラー割り込み要求*/
#define		INTC_CH_DSADERR13			(469)	/* DSADE13 DSAD エラー割り込み要求*/
#define		INTC_CH_DSADERR11			(470)	/* DSADE11 DSAD エラー割り込み要求*/
#define		INTC_CH_DSADERR15			(471)	/* DSADE15 DSAD エラー割り込み要求 */
#define		INTC_CH_DSADERR14			(472)	/* DSADE14 DSAD エラー割り込み要求 */
#define		INTC_CH_DSADERR22			(473)	/* DSADE22 DSAD エラー割り込み要求 */
#define		INTC_CH_DSADERR21			(474)	/* DSADE21 DSAD エラー割り込み要求 */
/* CADC */
#define		INTC_CH_CADCERR				(475)	/* CADE CAD エラー割り込み要求*/
/* 積算 */
#define		INTC_CH_ADC_ASI0			(476)	/* ASI0 積算終了割り込み*/
#define		INTC_CH_ADC_ASI1			(477)	/* ASI1 積算終了割り込み*/
#define		INTC_CH_ADC_ASI2			(478)	/* ASI2 積算終了割り込み*/
#define		INTC_CH_ADC_ASI3			(479)	/* ASI3 積算終了割り込み*/
#define		INTC_CH_ADC_ASI4			(480)	/* ASI4 積算終了割り込み*/
#define		INTC_CH_ADC_ASI5			(481)	/* ASI5 積算終了割り込み*/
#define		INTC_CH_ADC_ASI6			(482)	/* ASI6 積算終了割り込み*/
#define		INTC_CH_ADC_ASI7			(483)	/* ASI7 積算終了割り込み*/
#define		INTC_CH_ADC_ASI8			(484)	/* ASI8 積算終了割り込み*/
#define		INTC_CH_ADC_ASI9			(485)	/* ASI9 積算終了割り込み*/
#define		INTC_CH_ADC_ASI10			(486)	/* ASI10 積算終了割り込み*/
#define		INTC_CH_ADC_ASI11			(487)	/* ASI11 積算終了割り込み*/
#define		INTC_CH_ADC_ASI12			(488)	/* ASI12 積算終了割り込み*/
#define		INTC_CH_ADC_ASI13			(489)	/* ASI13 積算終了割り込み*/
#define		INTC_CH_ADC_ASI14			(490)	/* ASI14 積算終了割り込み*/
#define		INTC_CH_ADC_ASI15			(491)	/* ASI15 積算終了割り込み*/
/* Resource1のみ */
#define		INTC_CH_ADC_BFP0			(492)	/* AD 割り込み Resource1のみ */
#define		INTC_CH_ADC_BFP1			(493)	/* AD 割り込み Resource1のみ */
#define		INTC_CH_ADC_BFP2			(494)	/* AD 割り込み Resource1のみ */
#define		INTC_CH_ADC_BFP3			(495)	/* AD 割り込み Resource1のみ */
#define		INTC_CH_ADC_BFP4			(496)	/* AD 割り込み Resource1のみ */
#define		INTC_CH_ADC_BFP5			(497)	/* AD 割り込み Resource1のみ */
#define		INTC_CH_ADC_BFP6			(498)	/* AD 割り込み Resource1のみ */
#define		INTC_CH_ADC_BFP7			(499)	/* AD 割り込み Resource1のみ */
#define		INTC_CH_ADC_BFP8			(500)	/* AD 割り込み Resource1のみ */

/* FCMP */
#define		INTC_CH_FCMP0INTREQ			(501)	/* チャネル0の比較結果割り込み */
#define		INTC_CH_FCMP1INTREQ			(502)	/* チャネル1の比較結果割り込み */
#define		INTC_CH_FCMP2INTREQ			(503)	/* チャネル2の比較結果割り込み */
#define		INTC_CH_FCMP3INTREQ			(504)	/* チャネル3の比較結果割り込み */

/* DFE0 */
#define		INTC_CH_DFE0_DOUTCNDCH0		(505)	/* DFE0 CH0 アウトプットデータ割り込み、コンディションマッチ割り込み0 */
#define		INTC_CH_DFE0_DOUTCNDCH1		(506)	/* DFE0 CH1 アウトプットデータ割り込み、コンディションマッチ割り込み0 */
#define		INTC_CH_DFE0_DOUTCNDCH2		(507)	/* DFE0 CH2 アウトプットデータ割り込み、コンディションマッチ割り込み0 */
#define		INTC_CH_DFE0_DOUTCNDCH3		(508)	/* DFE0 CH3 アウトプットデータ割り込み、コンディションマッチ割り込み0 */
#define		INTC_CH_DFE0_DOUTCNDCH4		(509)	/* DFE0 CH4 アウトプットデータ割り込み、コンディションマッチ割り込み0 */
#define		INTC_CH_DFE0_DOUTCNDCH5		(510)	/* DFE0 CH5 アウトプットデータ割り込み、コンディションマッチ割り込み0 */
#define		INTC_CH_DFE0_DOUTCNDCH6		(511)	/* DFE0 CH6 アウトプットデータ割り込み、コンディションマッチ割り込み0 */
#define		INTC_CH_DFE0_DOUTCNDCH7		(512)	/* DFE0 CH7 アウトプットデータ割り込み、コンディションマッチ割り込み0 */
#define		INTC_CH_DFE0_DOUTCNDCH8		(513)	/* DFE0 CH8 アウトプットデータ割り込み、コンディションマッチ割り込み0 */
#define		INTC_CH_DFE0_DOUTCNDCH9		(514)	/* DFE0 CH9 アウトプットデータ割り込み、コンディションマッチ割り込み0 */
#define		INTC_CH_DFE0_DOUTCNDCH10	(515)	/* DFE0 CH10 アウトプットデータ割り込み、コンディションマッチ割り込み0 */
#define		INTC_CH_DFE0_DOUTCNDCH11	(516)	/* DFE0 CH11 アウトプットデータ割り込み、コンディションマッチ割り込み0 */
#define		INTC_CH_DFE0_DOUTCNDCH12	(517)	/* DFE0 CH12 アウトプットデータ割り込み、コンディションマッチ割り込み0 */
#define		INTC_CH_DFE0_DOUTCNDCH13	(518)	/* DFE0 CH13 アウトプットデータ割り込み、コンディションマッチ割り込み0 */
#define		INTC_CH_DFE0_DOUTCNDCH14	(519)	/* DFE0 CH14 アウトプットデータ割り込み、コンディションマッチ割り込み0 */
#define		INTC_CH_DFE0_DOUTCNDCH15	(520)	/* DFE0 CH15 アウトプットデータ割り込み、コンディションマッチ割り込み0 */

#define		INTC_CH_DFE0_CND1CH10		(522)	/* DFE0 CH0 コンディションマッチ割り込み1 */
#define		INTC_CH_DFE0_CND1CH11		(523)	/* DFE0 CH1 コンディションマッチ割り込み1 */
#define		INTC_CH_DFE0_CND1CH12		(524)	/* DFE0 CH2 コンディションマッチ割り込み1 */
#define		INTC_CH_DFE0_CND1CH13		(525)	/* DFE0 CH3 コンディションマッチ割り込み1 */

#define		INTC_CH_DFE0_ERR			(521)	/* DFE0 エラー割り込み */

#define		INTC_CH_DFE0_SUBOUT0		(526)	/* DFE0 Different割り込み0 */
#define		INTC_CH_DFE0_SUBOUT1		(527)	/* DFE0 Different割り込み1 */
#define		INTC_CH_DFE0_SUBOUT2		(528)	/* DFE0 Different割り込み2 */

#define		INTC_CH_DFE0_FEND0			(529)	/* DFE0 CH0 フィルタ処理終了割り込み要求 */
#define		INTC_CH_DFE0_FEND1			(530)	/* DFE0 CH1 フィルタ処理終了割り込み要求 */
#define		INTC_CH_DFE0_FEND2			(531)	/* DFE0 CH2 フィルタ処理終了割り込み要求 */
#define		INTC_CH_DFE0_FEND3			(532)	/* DFE0 CH3 フィルタ処理終了割り込み要求 */
#define		INTC_CH_DFE0_FEND4			(533)	/* DFE0 CH4 フィルタ処理終了割り込み要求 */
#define		INTC_CH_DFE0_FEND5			(534)	/* DFE0 CH5 フィルタ処理終了割り込み要求 */
#define		INTC_CH_DFE0_FEND6			(535)	/* DFE0 CH6 フィルタ処理終了割り込み要求 */
#define		INTC_CH_DFE0_FEND7			(536)	/* DFE0 CH7 フィルタ処理終了割り込み要求 */
#define		INTC_CH_DFE0_FEND8			(537)	/* DFE0 CH8 フィルタ処理終了割り込み要求 */
#define		INTC_CH_DFE0_FEND9			(538)	/* DFE0 CH9 フィルタ処理終了割り込み要求 */
#define		INTC_CH_DFE0_FEND10			(539)	/* DFE0 CH10 フィルタ処理終了割り込み要求 */
#define		INTC_CH_DFE0_FEND11			(540)	/* DFE0 CH11 フィルタ処理終了割り込み要求 */
#define		INTC_CH_DFE0_FEND12			(541)	/* DFE0 CH12 フィルタ処理終了割り込み要求 */
#define		INTC_CH_DFE0_FEND13			(542)	/* DFE0 CH13 フィルタ処理終了割り込み要求 */
#define		INTC_CH_DFE0_FEND14			(543)	/* DFE0 CH14 フィルタ処理終了割り込み要求 */
#define		INTC_CH_DFE0_FEND15			(544)	/* DFE0 CH15 フィルタ処理終了割り込み要求 */

/* DFE1*/
#define		INTC_CH_DFE1_DOUTCNDCH0		(545)	/* DFE1 CH0 アウトプットデータ割り込み、コンディションマッチ割り込み1 */
#define		INTC_CH_DFE1_DOUTCNDCH1		(546)	/* DFE1 CH1 アウトプットデータ割り込み、コンディションマッチ割り込み1 */
#define		INTC_CH_DFE1_DOUTCNDCH2		(547)	/* DFE1 CH2 アウトプットデータ割り込み、コンディションマッチ割り込み1 */
#define		INTC_CH_DFE1_DOUTCNDCH3		(548)	/* DFE1 CH3 アウトプットデータ割り込み、コンディションマッチ割り込み1 */

#define		INTC_CH_DFE1_CND1CH10		(550)	/* DFE1 CH0 コンディションマッチ割り込み1 */
#define		INTC_CH_DFE1_CND1CH11		(551)	/* DFE1 CH1 コンディションマッチ割り込み1 */
#define		INTC_CH_DFE1_CND1CH12		(552)	/* DFE1 CH2 コンディションマッチ割り込み1 */
#define		INTC_CH_DFE1_CND1CH13		(553)	/* DFE1 CH3 コンディションマッチ割り込み1 */

#define		INTC_CH_DFE1_ERR			(549)	/* DFE1 エラー割り込み */

#define		INTC_CH_DFE1_SUBOUT0		(554)	/* DFE1 Different割り込み0 */
#define		INTC_CH_DFE1_SUBOUT1		(555)	/* DFE1 Different割り込み1 */
#define		INTC_CH_DFE1_SUBOUT2		(556)	/* DFE1 Different割り込み2 */

#define		INTC_CH_DFE1FEND0			(557)	/* DFE1 CH0 フィルタ処理終了割り込み要求 */
#define		INTC_CH_DFE1FEND1			(558)	/* DFE1 CH1 フィルタ処理終了割り込み要求 */
#define		INTC_CH_DFE1FEND2			(559)	/* DFE1 CH2 フィルタ処理終了割り込み要求 */
#define		INTC_CH_DFE1FEND3			(560)	/* DFE1 CH3 フィルタ処理終了割り込み要求 */

/* DEF_FIFO */
#define		INTC_CH_DFEFIFOOUTA			(561)	/* DFE_FIFO バッファA キャプチャ完了割り込み要求 */
#define		INTC_CH_DFEFIFOOUTB			(562)	/* DFE_FIFO バッファB キャプチャ完了割り込み要求 */
#define		INTC_CH_DFEFIFOERR			(563)	/* DFE_FIFO エラー割り込み */

/* MSPI */
#define		INTC_CH_MSPI0TX0			(564)		/* MSPI0 CH0 送信ステータス割り込み */
#define		INTC_CH_MSPI0TX1			(565)		/* MSPI0 CH1 送信ステータス割り込み */
#define		INTC_CH_MSPI0TX2			(566)		/* MSPI0 CH2 送信ステータス割り込み */
#define		INTC_CH_MSPI0RX0			(567)		/* MSPI0 CH0 受信ステータス割り込み */
#define		INTC_CH_MSPI0RX1			(568)		/* MSPI0 CH1 受信ステータス割り込み */
#define		INTC_CH_MSPI0RX2			(569)		/* MSPI0 CH2 受信ステータス割り込み */

#define		INTC_CH_MSPI1TX0			(570)		/* MSPI1 CH0 送信ステータス割り込み */
#define		INTC_CH_MSPI1TX1			(571)		/* MSPI1 CH1 送信ステータス割り込み */
#define		INTC_CH_MSPI1TX2			(572)		/* MSPI1 CH2 送信ステータス割り込み */
#define		INTC_CH_MSPI1RX0			(573)		/* MSPI1 CH0 受信ステータス割り込み */
#define		INTC_CH_MSPI1RX1			(574)		/* MSPI1 CH1 受信ステータス割り込み */
#define		INTC_CH_MSPI1RX2			(575)		/* MSPI1 CH2 受信ステータス割り込み */

#define		INTC_CH_MSPI0TX				(576)		/* MSPI0チャンネル選択可能送信状態割り込み */
#define		INTC_CH_MSPI0RX				(577)		/* MSPI0チャンネル選択受信状態割り込み */
#define		INTC_CH_MSPI0FE				(578)		/* MSPI0チャンネル選択可能フレームカウント終了割り込み */
#define		INTC_CH_MSPI0ERR			(579)		/* MSPI0チャンネル選択可能エラー割り込み */

#define		INTC_CH_MSPI1TX				(580)		/* MSPI1チャンネル選択可能送信状態割り込み */
#define		INTC_CH_MSPI1RX				(581)		/* MSPI1チャンネル選択受信状態割り込み */
#define		INTC_CH_MSPI1FE				(582)		/* MSPI1チャンネル選択可能フレームカウント終了割り込み */
#define		INTC_CH_MSPI1ERR			(583)		/* MSPI1チャンネル選択可能エラー割り込み */

#define		INTC_CH_MSPI2TX				(584)		/* MSPI2チャンネル選択可能送信状態割り込み */
#define		INTC_CH_MSPI2RX				(585)		/* MSPI2チャンネル選択受信状態割り込み */
#define		INTC_CH_MSPI2FE				(586)		/* MSPI2チャンネル選択可能フレームカウント終了割り込み */
#define		INTC_CH_MSPI2ERR			(587)		/* MSPI2チャンネル選択可能エラー割り込み */

#define		INTC_CH_MSPI3TX				(588)		/* MSPI3チャンネル選択可能送信状態割り込み */
#define		INTC_CH_MSPI3RX				(589)		/* MSPI3チャンネル選択受信状態割り込み */
#define		INTC_CH_MSPI3FE				(590)		/* MSPI3チャンネル選択可能フレームカウント終了割り込み */
#define		INTC_CH_MSPI3ERR			(591)		/* MSPI3チャンネル選択可能エラー割り込み */

#define		INTC_CH_MSPI4TX				(592)		/* MSPI4チャンネル選択可能送信状態割り込み */
#define		INTC_CH_MSPI4RX				(593)		/* MSPI4チャンネル選択受信状態割り込み */
#define		INTC_CH_MSPI4FE				(594)		/* MSPI4チャンネル選択可能フレームカウント終了割り込み */
#define		INTC_CH_MSPI4ERR			(595)		/* MSPI4チャンネル選択可能エラー割り込み */

#define		INTC_CH_MSPI5TX				(596)		/* MSPI5チャンネル選択可能送信状態割り込み */
#define		INTC_CH_MSPI5RX				(597)		/* MSPI5チャンネル選択受信状態割り込み */
#define		INTC_CH_MSPI5FE				(598)		/* MSPI5チャンネル選択可能フレームカウント終了割り込み */
#define		INTC_CH_MSPI5ERR			(599)		/* MSPI5チャンネル選択可能エラー割り込み */

#define		INTC_CH_MSPI6TX				(600)		/* MSPI6チャンネル選択可能送信状態割り込み */
#define		INTC_CH_MSPI6RX				(601)		/* MSPI6チャンネル選択受信状態割り込み */
#define		INTC_CH_MSPI6FE				(602)		/* MSPI6チャンネル選択可能フレームカウント終了割り込み */
#define		INTC_CH_MSPI6ERR			(603)		/* MSPI6チャンネル選択可能エラー割り込み */

#define		INTC_CH_MSPI7TX				(851)		/* MSPI7チャンネル選択可能送信状態割り込み */
#define		INTC_CH_MSPI7RX				(852)		/* MSPI7チャンネル選択受信状態割り込み */
#define		INTC_CH_MSPI7FE				(853)		/* MSPI7チャンネル選択可能フレームカウント終了割り込み */
#define		INTC_CH_MSPI7ERR			(854)		/* MSPI7チャンネル選択可能エラー割り込み */

#define		INTC_CH_MSPI8TX				(855)		/* MSPI8チャンネル選択可能送信状態割り込み */
#define		INTC_CH_MSPI8RX				(856)		/* MSPI8チャンネル選択受信状態割り込み */
#define		INTC_CH_MSPI8FE				(857)		/* MSPI8チャンネル選択可能フレームカウント終了割り込み */
#define		INTC_CH_MSPI8ERR			(858)		/* MSPI8チャンネル選択可能エラー割り込み */

#define		INTC_CH_MSPI9TX				(859)		/* MSPI9チャンネル選択可能送信状態割り込み */
#define		INTC_CH_MSPI9RX				(860)		/* MSPI9チャンネル選択受信状態割り込み */
#define		INTC_CH_MSPI9FE				(861)		/* MSPI9チャンネル選択可能フレームカウント終了割り込み */
#define		INTC_CH_MSPI9ERR			(862)		/* MSPI9チャンネル選択可能エラー割り込み */

/* RS-CANFD_mux0 */
#define		INTC_CH_RCAN_ERR_MUX0		(576)	/* CANnエラー割り込み(n=0-9) mux0 */
#define		INTC_CH_RCAN_REC_MUX0		(577)	/* CANn送受信FIFO受信完了割り込み (n=0~9) mux0 */
#define		INTC_CH_RCAN_TRX_MUX0		(578)	/* CANn送信割り込み (n=0~9)  mux0 */
#define		INTC_CH_RCAN_VMTX_MUX0		(579)	/* CANn仮想マシンTX割り込み (n=0~9)  mux0 */
#define		INTC_CH_RCAN_VMRX_MUX0		(580)	/* CANn仮想マシンRX割り込み (n=0~9)  mux0 */
#define		INTC_CH_RCAN_VMERR_MUX0		(581)	/* CANn仮想マシンエラー割り込み (n=0~9)  mux0 */

/* RS-CANFD_mux1 */
#define		INTC_CH_RCAN_ERR_MUX1		(582)	/* CANnエラー割り込み (n=0-9)  mux1 */
#define		INTC_CH_RCAN_REC_MUX1		(583)	/* CANn送受信FIFO受信完了割り込み (n=0~9) mux1 */
#define		INTC_CH_RCAN_TRX_MUX1		(584)	/* CANn送信割り込み (n=0~9) mux1 */
#define		INTC_CH_RCAN_VMTX_MUX1		(585)	/* CANn仮想マシンTX割り込み (n=0~9)  mux1 */
#define		INTC_CH_RCAN_VMRX_MUX1		(586)	/* CANn仮想マシンRX割り込み (n=0~9)  mux1 */
#define		INTC_CH_RCAN_VMERR_MUX1		(587)	/* CANn仮想マシンエラー割り込み (n=0~9)  mux1 */

/* RS-CANFD_mux2 */
#define		INTC_CH_RCAN_ERR_MUX2		(588)	/* CANnエラー割り込み (n=0-9)  mux2 */
#define		INTC_CH_RCAN_REC_MUX2		(589)	/* CANn送受信FIFO受信完了割り込み (n=0~9) mux2 */
#define		INTC_CH_RCAN_TRX_MUX2		(590)	/* CANn送信割り込み (n=0~9) mux2 */
#define		INTC_CH_RCAN_VMTX_MUX2		(591)	/* CANn仮想マシンTX割り込み (n=0~9)  mux2 */
#define		INTC_CH_RCAN_VMRX_MUX2		(592)	/* CANn仮想マシンRX割り込み (n=0~9)  mux2 */
#define		INTC_CH_RCAN_VMERR_MUX2		(593)	/* CANn仮想マシンエラー割り込み (n=0~9)  mux2 */

/* RS-CANFD_mux3 */
#define		INTC_CH_RCAN_ERR_MUX3		(594)	/* CANnエラー割り込み (n=0-9)  mux3 */
#define		INTC_CH_RCAN_REC_MUX3		(595)	/* CANn送受信FIFO受信完了割り込み (n=0~9) mux3 */
#define		INTC_CH_RCAN_TRX_MUX3		(596)	/* CANn送信割り込み (n=0~9) mux3 */
#define		INTC_CH_RCAN_VMTX_MUX3		(597)	/* CANn仮想マシンTX割り込み (n=0~9)  mux3 */
#define		INTC_CH_RCAN_VMRX_MUX3		(598)	/* CANn仮想マシンRX割り込み (n=0~9)  mux3 */
#define		INTC_CH_RCAN_VMERR_MUX3		(599)	/* CANn仮想マシンエラー割り込み (n=0~9)  mux3 */

/* RS-CANFD_mux4 */
#define		INTC_CH_RCAN_ERR_MUX4		(600)	/* CANnエラー割り込み (n=0-9)  mux4 */
#define		INTC_CH_RCAN_REC_MUX4		(601)	/* CANn送受信FIFO受信完了割り込み (n=0~9) mux4 */
#define		INTC_CH_RCAN_TRX_MUX4		(602)	/* CANn送信割り込み (n=0~9) mux4 */
#define		INTC_CH_RCAN_VMTX_MUX4		(603)	/* CANn仮想マシンTX割り込み (n=0~9)  mux4 */
#define		INTC_CH_RCAN_VMRX_MUX4		(604)	/* CANn仮想マシンRX割り込み (n=0~9)  mux4 */
#define		INTC_CH_RCAN_VMERR_MUX4		(605)	/* CANn仮想マシンエラー割り込み (n=0~9)  mux4 */

/* RS-CANFD_mux5 */
#define		INTC_CH_RCAN_ERR_MUX5		(606)	/* CANnエラー割り込み (n=0-9)  mux5 */
#define		INTC_CH_RCAN_REC_MUX5		(607)	/* CANn送受信FIFO受信完了割り込み (n=0~9) mux5 */
#define		INTC_CH_RCAN_TRX_MUX5		(608)	/* CANn送信割り込み (n=0~9) mux5 */
#define		INTC_CH_RCAN_VMTX_MUX5		(609)	/* CANn仮想マシンTX割り込み (n=0~9)  mux5 */
#define		INTC_CH_RCAN_VMRX_MUX5		(610)	/* CANn仮想マシンRX割り込み (n=0~9)  mux5 */
#define		INTC_CH_RCAN_VMERR_MUX5		(611)	/* CANn仮想マシンエラー割り込み (n=0~9)  mux5 */

/* RS-CANFD_mux6 */
#define		INTC_CH_RCAN_ERR_MUX6		(612)	/* CANnエラー割り込み (n=0-9)  mux6 */
#define		INTC_CH_RCAN_REC_MUX6		(613)	/* CANn送受信FIFO受信完了割り込み (n=0~9) mux6 */
#define		INTC_CH_RCAN_TRX_MUX6		(614)	/* CANn送信割り込み (n=0~9) mux6 */
#define		INTC_CH_RCAN_VMTX_MUX6		(615)	/* CANn仮想マシンTX割り込み (n=0~9)  mux6 */
#define		INTC_CH_RCAN_VMRX_MUX6		(616)	/* CANn仮想マシンRX割り込み (n=0~9)  mux6 */
#define		INTC_CH_RCAN_VMERR_MUX6		(617)	/* CANn仮想マシンエラー割り込み (n=0~9)  mux6 */

/* RLIN3 */
#define		INTC_CH_RLIN30				(620)	/* RLIN30 割り込み */
#define		INTC_CH_RLIN30_INTTX		(621)	/* RLIN30 送信割り込み */
#define		INTC_CH_RLIN30_INTRX		(622)	/* RLIN30 受信完了割り込み */
#define		INTC_CH_RLIN30_INTSTATU		(623)	/* RLIN30 ステータス割り込み */
#define		INTC_CH_RLIN30_URDC			(624)	/* RLIN 30ループバック遅延データ整合性チェック割り込み */
#define		INTC_CH_RLIN31				(625)	/* RLIN31 割り込み */
#define		INTC_CH_RLIN31_INTTX		(626)	/* RLIN31 送信割り込み */
#define		INTC_CH_RLIN31_INTRX		(627)	/* RLIN31 受信完了割り込み */
#define		INTC_CH_RLIN31_INTSTATUS	(628)	/* RLIN31 ステータス割り込み */
#define		INTC_CH_RLIN31_URDC			(629)	/* RLIN 31ループバック遅延データ整合性チェック割り込み */
#define		INTC_CH_RLIN32				(630)	/* RLIN32 割り込み */
#define		INTC_CH_RLIN32_INTTX		(631)	/* RLIN32 送信割り込み */
#define		INTC_CH_RLIN32_INTRX		(632)	/* RLIN32 受信完了割り込み */
#define		INTC_CH_RLIN32_INTSTATUS	(633)	/* RLIN32 ステータス割り込み */
#define		INTC_CH_RLIN32_URDC			(634)	/* RLIN 32ループバック遅延データ整合性チェック割り込み */
#define		INTC_CH_RLIN33				(635)	/* RLIN33 割り込み */
#define		INTC_CH_RLIN33_INTTX		(636)	/* RLIN33 送信割り込み */
#define		INTC_CH_RLIN33_INTRX		(637)	/* RLIN33 受信完了割り込み */
#define		INTC_CH_RLIN33_INTSTATUS	(638)	/* RLIN33 ステータス割り込み */
#define		INTC_CH_RLIN33_URDC			(639)	/* RLIN 33ループバック遅延データ整合性チェック割り込み */
#define		INTC_CH_RLIN34				(640)	/* RLIN34 割り込み */
#define		INTC_CH_RLIN34_INTTX		(641)	/* RLIN34 送信割り込み */
#define		INTC_CH_RLIN34_INTRX		(642)	/* RLIN34 受信完了割り込み */
#define		INTC_CH_RLIN34_INTSTATUS	(643)	/* RLIN34 ステータス割り込み */
#define		INTC_CH_RLIN35				(644)	/* RLIN35 割り込み */
#define		INTC_CH_RLIN35_INTTX		(645)	/* RLIN35 送信割り込み */
#define		INTC_CH_RLIN35_INTRX		(646)	/* RLIN35 受信完了割り込み */
#define		INTC_CH_RLIN35_INTSTATUS	(647)	/* RLIN35 ステータス割り込み */
#define		INTC_CH_RLIN323				(648)	/* RLIN323 割り込み */
#define		INTC_CH_RLIN323_INTTX		(649)	/* RLIN323 送信割り込み */
#define		INTC_CH_RLIN323_INTRX		(650)	/* RLIN323 受信完了割り込み */
#define		INTC_CH_RLIN323_INTSTATUS	(651)	/* RLIN323 ステータス割り込み */

/* RS-CANFD */
#define		INTC_CH_RCAN_GERR0			(652)	/* RSCFD0 グローバルエラー割り込み */
#define		INTC_CH_RCAN_GRECC0			(653)	/* RSCFD0 受信 FIFO 割り込み */

#define		INTC_CH_RCAN0_ERR			(658)	/* CAN0 エラー割り込み */
#define		INTC_CH_RCAN0_REC			(659)	/* CAN0 転送/受信 FIFO 受信完了割り込み */
#define		INTC_CH_RCAN0_TRX			(660)	/* CAN0 送信割り込み */
#define		INTC_CH_RCAN0_VMTX			(661)	/* CAN0 仮想マシンTX割り込み */
#define		INTC_CH_RCAN0_VMRX			(662)	/* CAN0 仮想マシンRX割り込み */
#define		INTC_CH_RCAN0_VMERR			(663)	/* CAN0 仮想マシンエラー割り込み */

#define		INTC_CH_RCAN1_ERR			(664)	/* CAN1 エラー割り込み */
#define		INTC_CH_RCAN1_REC			(665)	/* CAN1 転送/受信 FIFO 受信完了割り込み */
#define		INTC_CH_RCAN1_TRX			(666)	/* CAN1 送信割り込み */
#define		INTC_CH_RCAN1_VMTX			(667)	/* CAN1 仮想マシンTX割り込み */
#define		INTC_CH_RCAN1_VMRX			(668)	/* CAN1 仮想マシンRX割り込み */
#define		INTC_CH_RCAN1_VMERR			(669)	/* CAN1 仮想マシンエラー割り込み */

#define		INTC_CH_RCAN2_ERR			(670)	/* CAN2 エラー割り込み */
#define		INTC_CH_RCAN2_REC			(671)	/* CAN2 転送/受信 FIFO 受信完了割り込み */
#define		INTC_CH_RCAN2_TRX			(672)	/* CAN2 送信割り込み */
#define		INTC_CH_RCAN2_VMTX			(673)	/* CAN2 仮想マシンTX割り込み */
#define		INTC_CH_RCAN2_VMRX			(674)	/* CAN2 仮想マシンRX割り込み */
#define		INTC_CH_RCAN2_VMERR			(675)	/* CAN2 仮想マシンエラー割り込み */

#define		INTC_CH_RCAN3_ERR			(676)	/* CAN3 エラー割り込み */
#define		INTC_CH_RCAN3_REC			(677)	/* CAN3 転送/受信 FIFO 受信完了割り込み */
#define		INTC_CH_RCAN3_TRX			(678)	/* CAN3 送信割り込み */
#define		INTC_CH_RCAN3_VMTX			(679)	/* CAN3 仮想マシンTX割り込み */
#define		INTC_CH_RCAN3_VMRX			(680)	/* CAN3 仮想マシンRX割り込み */
#define		INTC_CH_RCAN3_VMERR			(681)	/* CAN3 仮想マシンエラー割り込み */

#define		INTC_CH_RCAN4_ERR			(682)	/* CAN4 エラー割り込み */
#define		INTC_CH_RCAN4_REC			(683)	/* CAN4 転送/受信 FIFO 受信完了割り込み */
#define		INTC_CH_RCAN4_TRX			(684)	/* CAN4 送信割り込み */
#define		INTC_CH_RCAN4_VMTX			(685)	/* CAN4 仮想マシンTX割り込み */
#define		INTC_CH_RCAN4_VMRX			(686)	/* CAN4 仮想マシンRX割り込み */
#define		INTC_CH_RCAN4_VMERR			(687)	/* CAN4 仮想マシンエラー割り込み */

#define		INTC_CH_RCAN5_ERR			(688)	/* CAN5 エラー割り込み */
#define		INTC_CH_RCAN5_REC			(689)	/* CAN5 転送/受信 FIFO 受信完了割り込み */
#define		INTC_CH_RCAN5_TRX			(690)	/* CAN5 送信割り込み */
#define		INTC_CH_RCAN5_VMTX			(691)	/* CAN5 仮想マシンTX割り込み */
#define		INTC_CH_RCAN5_VMRX			(692)	/* CAN5 仮想マシンRX割り込み */
#define		INTC_CH_RCAN5_VMERR			(693)	/* CAN5 仮想マシンエラー割り込み */

#define		INTC_CH_RCAN6_ERR			(694)	/* CAN6 エラー割り込み */
#define		INTC_CH_RCAN6_REC			(695)	/* CAN6 転送/受信 FIFO 受信完了割り込み */
#define		INTC_CH_RCAN6_TRX			(696)	/* CAN6 送信割り込み */
#define		INTC_CH_RCAN6_VMTX			(697)	/* CAN6 仮想マシンTX割り込み */
#define		INTC_CH_RCAN6_VMRX			(698)	/* CAN6 仮想マシンRX割り込み */
#define		INTC_CH_RCAN6_VMERR			(699)	/* CAN6 仮想マシンエラー割り込み */

#define		INTC_CH_RCAN7_ERR			(700)	/* CAN7 エラー割り込み */
#define		INTC_CH_RCAN7_REC			(701)	/* CAN7 転送/受信 FIFO 受信完了割り込み */
#define		INTC_CH_RCAN7_TRX			(702)	/* CAN7 送信割り込み */
#define		INTC_CH_RCAN7_VMTX			(703)	/* CAN7 仮想マシンTX割り込み */
#define		INTC_CH_RCAN7_VMRX			(704)	/* CAN7 仮想マシンRX割り込み */
#define		INTC_CH_RCAN7_VMERR			(705)	/* CAN7 仮想マシンエラー割り込み */

/* ETNC(TSN0) */
#define		INTC_CH_ETND00				(708)		/* ETND0 (エンドステーション) 割り込み0 */
#define		INTC_CH_ETND01				(709)		/* ETND1 (エンドステーション) 割り込み1 */
#define		INTC_CH_ETND02				(710)		/* ETND2 (エンドステーション) 割り込み2 */
#define		INTC_CH_ETND03				(711)		/* ETND3 (エンドステーション) 割り込み3 */
#define		INTC_CH_ETND04				(712)		/* ETND4 (エンドステーション) 割り込み4 */
#define		INTC_CH_ETND05				(713)		/* ETND5 (エンドステーション) 割り込み5 */
#define		INTC_CH_ETND06				(714)		/* ETND6 (エンドステーション) 割り込み6 */
#define		INTC_CH_ETND07				(715)		/* ETND7 (エンドステーション) 割り込み7 */

/* QOS3 */
#define		INTC_CH_QOS3_0				(717)		/* CPU0コードフラッシュバスポート割り込み(Ch3) */
#define		INTC_CH_QOS3_1				(717)		/* CPU0周辺機器バスポート割り込み(Ch3) */
#define		INTC_CH_QOS3_2				(717)		/* CPU0クラスタRAMバスポート割り込み(Ch 3) */
#define		INTC_CH_QOS3_3				(717)		/* CPU1コードフラッシュバスポート割り込み(Ch3) */
#define		INTC_CH_QOS3_4				(717)		/* CPU1周辺機器バスポート割り込み(Ch3) */
#define		INTC_CH_QOS3_5				(717)		/* CPU1クラスタRAMバスポート割り込み(Ch 3) */
#define		INTC_CH_QOS3_6				(717)		/* CPU2コードフラッシュバスポート割り込み(Ch3) */
#define		INTC_CH_QOS3_7				(717)		/* CPU2周辺機器バスポート割り込み(Ch3) */
#define		INTC_CH_QOS3_8				(717)		/* CPU2クラスタRAMバスポート割り込み(Ch 3) */
#define		INTC_CH_QOS3_24				(717)		/* DTS (Ch3) */
#define		INTC_CH_QOS3_25				(717)		/* SDMAC0 (Ch3) */
#define		INTC_CH_QOS3_26				(717)		/* SDMAC1 (Ch3) */
#define		INTC_CH_QOS3_27				(717)		/* ICUM Code Flash bus (Ch3) */
#define		INTC_CH_QOS3_28				(717)		/* ICUM System bus (Ch3) */
#define		INTC_CH_QOS3_31				(717)		/* DFP Code Flash bus (Ch3) */
#define		INTC_CH_QOS3_32				(717)		/* DFP System bus (Ch3) */
#define		INTC_CH_QOS3_33				(717)		/* GTM (Ch3) */
#define		INTC_CH_QOS3_34				(717)		/* RHSIF0 (Ch3) */
#define		INTC_CH_QOS3_35				(717)		/* RHSIF1 (Ch3) */
#define		INTC_CH_QOS3_36				(717)		/* Flexray0 (Ch3) */
#define		INTC_CH_QOS3_38				(717)		/* Ether 0 (Ch3) */

/* QOS4 */
#define		INTC_CH_QOS4_0				(718)		/* CPU0コードフラッシュバスポート割り込み(Ch4) */
#define		INTC_CH_QOS4_1				(718)		/* CPU0周辺機器バスポート割り込み(Ch4) */
#define		INTC_CH_QOS4_2				(718)		/* CPU0クラスタRAMバスポート割り込み(Ch4) */
#define		INTC_CH_QOS4_3				(718)		/* CPU1コードフラッシュバスポート割り込み(Ch4) */
#define		INTC_CH_QOS4_4				(718)		/* CPU1周辺機器バスポート割り込み(Ch4) */
#define		INTC_CH_QOS4_5				(718)		/* CPU1クラスタRAMバスポート割り込み(Ch4) */
#define		INTC_CH_QOS4_6				(718)		/* CPU2コードフラッシュバスポート割り込み(Ch4) */
#define		INTC_CH_QOS4_7				(718)		/* CPU2周辺機器バスポート割り込み(Ch4) */
#define		INTC_CH_QOS4_8				(718)		/* CPU2クラスタRAMバスポート割り込み(Ch4) */
#define		INTC_CH_QOS4_24				(718)		/* DTS (Ch4) */
#define		INTC_CH_QOS4_25				(718)		/* SDMAC0 (Ch4) */
#define		INTC_CH_QOS4_26				(718)		/* SDMAC1 (Ch4) */
#define		INTC_CH_QOS4_27				(718)		/* ICUM Code Flash bus (Ch4) */
#define		INTC_CH_QOS4_28				(718)		/* ICUM System bus (Ch4) */
#define		INTC_CH_QOS4_31				(718)		/* DFP Code Flash bus (Ch4) */
#define		INTC_CH_QOS4_32				(718)		/* DFP System bus (Ch4) */
#define		INTC_CH_QOS4_33				(718)		/* GTM (Ch4) */
#define		INTC_CH_QOS4_34				(718)		/* RHSIF0 (Ch4) */
#define		INTC_CH_QOS4_35				(718)		/* RHSIF1 (Ch4) */
#define		INTC_CH_QOS4_36				(718)		/* Flexray0 (Ch4) */
#define		INTC_CH_QOS4_38				(718)		/* Ether 0 (Ch4) */

/* QOS5 */
#define		INTC_CH_QOS5_0				(719)		/* CPU0コードフラッシュバスポート割り込み(Ch5) */
#define		INTC_CH_QOS5_1				(719)		/* CPU0周辺機器バスポート割り込み(Ch5) */
#define		INTC_CH_QOS5_2				(719)		/* CPU0クラスタRAMバスポート割り込み(Ch5) */
#define		INTC_CH_QOS5_3				(719)		/* CPU1コードフラッシュバスポート割り込み(Ch5) */
#define		INTC_CH_QOS5_4				(719)		/* CPU1周辺機器バスポート割り込み(Ch5) */
#define		INTC_CH_QOS5_5				(719)		/* CPU1クラスタRAMバスポート割り込み(Ch5) */
#define		INTC_CH_QOS5_6				(719)		/* CPU2コードフラッシュバスポート割り込み(Ch5) */
#define		INTC_CH_QOS5_7				(719)		/* CPU2周辺機器バスポート割り込み(Ch5) */
#define		INTC_CH_QOS5_8				(719)		/* CPU2クラスタRAMバスポート割り込み(Ch5) */
#define		INTC_CH_QOS5_24				(719)		/* DTS (Ch5) */
#define		INTC_CH_QOS5_25				(719)		/* SDMAC0 (Ch5) */
#define		INTC_CH_QOS5_26				(719)		/* SDMAC1 (Ch5) */
#define		INTC_CH_QOS5_27				(719)		/* ICUM Code Flash bus (Ch5) */
#define		INTC_CH_QOS5_28				(719)		/* ICUM System bus (Ch5) */
#define		INTC_CH_QOS5_31				(719)		/* DFP Code Flash bus (Ch5) */
#define		INTC_CH_QOS5_32				(719)		/* DFP System bus (Ch5) */
#define		INTC_CH_QOS5_33				(719)		/* GTM (Ch5) */
#define		INTC_CH_QOS5_34				(719)		/* RHSIF0 (Ch5) */
#define		INTC_CH_QOS5_35				(719)		/* RHSIF1 (Ch5) */
#define		INTC_CH_QOS5_36				(719)		/* Flexray0 (Ch5) */
#define		INTC_CH_QOS5_38				(719)		/* Ether 0 (Ch5) */

/* QOS6 */
#define		INTC_CH_QOS6_0				(720)		/* CPU0コードフラッシュバスポート割り込み(Ch6) */
#define		INTC_CH_QOS6_1				(720)		/* CPU0周辺機器バスポート割り込み(Ch6) */
#define		INTC_CH_QOS6_2				(720)		/* CPU0クラスタRAMバスポート割り込み(Ch6) */
#define		INTC_CH_QOS6_3				(720)		/* CPU1コードフラッシュバスポート割り込み(Ch6) */
#define		INTC_CH_QOS6_4				(720)		/* CPU1周辺機器バスポート割り込み(Ch6) */
#define		INTC_CH_QOS6_5				(720)		/* CPU1クラスタRAMバスポート割り込み(Ch6) */
#define		INTC_CH_QOS6_6				(720)		/* CPU2コードフラッシュバスポート割り込み(Ch6) */
#define		INTC_CH_QOS6_7				(720)		/* CPU2周辺機器バスポート割り込み(Ch6) */
#define		INTC_CH_QOS6_8				(720)		/* CPU2クラスタRAMバスポート割り込み(Ch6) */
#define		INTC_CH_QOS6_24				(720)		/* DTS (Ch6) */
#define		INTC_CH_QOS6_25				(720)		/* SDMAC0 (Ch6) */
#define		INTC_CH_QOS6_26				(720)		/* SDMAC1 (Ch6) */
#define		INTC_CH_QOS6_27				(720)		/* ICUM Code Flash bus (Ch6) */
#define		INTC_CH_QOS6_28				(720)		/* ICUM System bus (Ch6) */
#define		INTC_CH_QOS6_31				(720)		/* DFP Code Flash bus (Ch6) */
#define		INTC_CH_QOS6_32				(720)		/* DFP System bus (Ch6) */
#define		INTC_CH_QOS6_33				(720)		/* GTM (Ch6) */
#define		INTC_CH_QOS6_34				(720)		/* RHSIF0 (Ch6) */
#define		INTC_CH_QOS6_35				(720)		/* RHSIF1 (Ch6) */
#define		INTC_CH_QOS6_36				(720)		/* Flexray0 (Ch6) */
#define		INTC_CH_QOS6_38				(720)		/* Ether 0 (Ch6) */

/* QOS7 */
#define		INTC_CH_QOS7_0				(721)		/* CPU0コードフラッシュバスポート割り込み(Ch7) */
#define		INTC_CH_QOS7_1				(721)		/* CPU0周辺機器バスポート割り込み(Ch7) */
#define		INTC_CH_QOS7_2				(721)		/* CPU0クラスタRAMバスポート割り込み(Ch7) */
#define		INTC_CH_QOS7_3				(721)		/* CPU1コードフラッシュバスポート割り込み(Ch7) */
#define		INTC_CH_QOS7_4				(721)		/* CPU1周辺機器バスポート割り込み(Ch7) */
#define		INTC_CH_QOS7_5				(721)		/* CPU1クラスタRAMバスポート割り込み(Ch7) */
#define		INTC_CH_QOS7_6				(721)		/* CPU2コードフラッシュバスポート割り込み(Ch7) */
#define		INTC_CH_QOS7_7				(721)		/* CPU2周辺機器バスポート割り込み(Ch7) */
#define		INTC_CH_QOS7_8				(721)		/* CPU2クラスタRAMバスポート割り込み(Ch7) */
#define		INTC_CH_QOS7_9				(721)		/* CPU3コードフラッシュバスポート割り込み(Ch7) */
#define		INTC_CH_QOS7_24				(721)		/* DTS (Ch7) */
#define		INTC_CH_QOS7_25				(721)		/* SDMAC0 (Ch7) */
#define		INTC_CH_QOS7_26				(721)		/* SDMAC1 (Ch7) */
#define		INTC_CH_QOS7_27				(721)		/* ICUM Code Flash bus (Ch7) */
#define		INTC_CH_QOS7_28				(721)		/* ICUM System bus (Ch7) */
#define		INTC_CH_QOS7_31				(721)		/* DFP Code Flash bus (Ch7) */
#define		INTC_CH_QOS7_32				(721)		/* DFP System bus (Ch7) */
#define		INTC_CH_QOS7_33				(721)		/* GTM (Ch7) */
#define		INTC_CH_QOS7_34				(721)		/* RHSIF0 (Ch7) */
#define		INTC_CH_QOS7_35				(721)		/* RHSIF1 (Ch7) */
#define		INTC_CH_QOS7_36				(721)		/* Flexray0 (Ch7) */
#define		INTC_CH_QOS7_38				(721)		/* Ether 0 (Ch7) */

/* ICUMHB */
#define		INTC_CH_ICU2PE0				(753)		/* ICUMHBからINTC 2へのPE間割り込み(ICUPからCPU (PE) への割り込み要求) */
#define		INTC_CH_ICU2PE1				(754)		/* ICUMHBからINTC 2へのPE間割り込み(ICUPからCPU (PE) への割り込み要求) */
#define		INTC_CH_ICU2PE2				(755)		/* ICUMHBからINTC 2へのPE間割り込み(ICUPからCPU (PE) への割り込み要求) */
#define		INTC_CH_ICU2PE3				(756)		/* ICUMHBからINTC 2へのPE間割り込み(ICUPからCPU (PE) への割り込み要求) */
#define		INTC_CH_ICU2PE4				(757)		/* ICUMHBからINTC 2へのPE間割り込み(ICUPからCPU (PE) への割り込み要求) */
#define		INTC_CH_ICU2PE5				(758)		/* ICUMHBからINTC 2へのPE間割り込み(ICUPからCPU (PE) への割り込み要求) */
#define		INTC_CH_ICU2PE6				(759)		/* ICUMHBからINTC 2へのPE間割り込み(ICUPからCPU (PE) への割り込み要求) */
#define		INTC_CH_ICU2PE7				(760)		/* ICUMHBからINTC 2へのPE間割り込み(ICUPからCPU (PE) への割り込み要求) */

/* PORT */
#define		INTC_CH_IRQ0				(765)		/* 外部割り込み0 */
#define		INTC_CH_IRQ1				(766)		/* 外部割り込み1 */
#define		INTC_CH_IRQ2				(767)		/* 外部割り込み2 */
#define		INTC_CH_IRQ3				(768)		/* 外部割り込み3 */
#define		INTC_CH_IRQ4				(769)		/* 外部割り込み4 */
#define		INTC_CH_IRQ5				(770)		/* 外部割り込み5 */
#define		INTC_CH_IRQ6				(771)		/* 外部割り込み6 */
#define		INTC_CH_IRQ7				(772)		/* 外部割り込み7 */
#define		INTC_CH_IRQ8				(773)		/* 外部割り込み8 */
#define		INTC_CH_IRQ9				(774)		/* 外部割り込み9 */
#define		INTC_CH_IRQ10				(775)		/* 外部割り込み10 */
#define		INTC_CH_IRQ11				(776)		/* 外部割り込み11 */
#define		INTC_CH_IRQ12				(777)		/* 外部割り込み12 */
#define		INTC_CH_IRQ13				(778)		/* 外部割り込み13 */
#define		INTC_CH_IRQ14				(779)		/* 外部割り込み14 */
#define		INTC_CH_IRQ15				(780)		/* 外部割り込み15 */
#define		INTC_CH_IRQ16				(781)		/* 外部割り込み16 */
#define		INTC_CH_IRQ17				(782)		/* 外部割り込み17 */
#define		INTC_CH_IRQ18				(783)		/* 外部割り込み18 */
#define		INTC_CH_IRQ19				(784)		/* 外部割り込み19 */
#define		INTC_CH_IRQ20				(785)		/* 外部割り込み20 */
#define		INTC_CH_IRQ21				(786)		/* 外部割り込み21 */
#define		INTC_CH_IRQ22				(787)		/* 外部割り込み22 */
#define		INTC_CH_IRQ23				(788)		/* 外部割り込み23 */
#define		INTC_CH_IRQ24				(789)		/* 外部割り込み24 */
#define		INTC_CH_IRQ25				(790)		/* 外部割り込み25 */
#define		INTC_CH_IRQ26				(791)		/* 外部割り込み26 */
#define		INTC_CH_IRQ27				(792)		/* 外部割り込み27 */
#define		INTC_CH_IRQ28				(793)		/* 外部割り込み28 */
#define		INTC_CH_IRQ29				(794)		/* 外部割り込み29 */
#define		INTC_CH_IRQ30				(795)		/* 外部割り込み30 */
#define		INTC_CH_IRQ31				(796)		/* 外部割り込み31 */
#define		INTC_CH_IRQ32				(797)		/* 外部割り込み32 */
#define		INTC_CH_IRQ33				(798)		/* 外部割り込み33 */
#define		INTC_CH_IRQ34				(799)		/* 外部割り込み34 */
#define		INTC_CH_IRQ35				(800)		/* 外部割り込み35 */
#define		INTC_CH_IRQ36				(801)		/* 外部割り込み36 */
#define		INTC_CH_IRQ37				(802)		/* 外部割り込み37 */
#define		INTC_CH_IRQ38				(803)		/* 外部割り込み38 */
#define		INTC_CH_IRQ39				(804)		/* 外部割り込み39 */
#define		INTC_CH_IRQ40				(817)		/* 外部割り込み40 */
#define		INTC_CH_IRQ41				(818)		/* 外部割り込み41 */
#define		INTC_CH_IRQ42				(819)		/* 外部割り込み42 */
#define		INTC_CH_IRQ43				(820)		/* 外部割り込み43 */

#define		INTC_CH_DNFA1WUF0			(805)		/* RLIN30受信データのエッジ検出 */
#define		INTC_CH_DNFA1WUF1			(806)		/* RLIN31受信データのエッジ検出 */
#define		INTC_CH_DNFA2WUF0			(807)		/* RSCFD0受信データのエッジ検出 */
#define		INTC_CH_DNFA2WUF1			(808)		/* RSCFD1受信データのエッジ検出 */
#define		INTC_CH_DNFA0WUF0			(809)		/* FLXA0ch A受信データのエッジ検出 */

#define		INTC_CH_DCUTDI				(810)		/* オンチップデバッグ機能専用割り込み */

#define		INTC_CH_TAPA0ESO			(811)		/* 非常用Hi-Z入力0 */
#define		INTC_CH_TAPA1ESO			(812)		/* 非常用Hi-Z入力1 */
#define		INTC_CH_TAPA2ESO			(813)		/* 非常用Hi-Z入力2 */
#define		INTC_CH_TAPA3ESO			(814)		/* 非常用Hi-Z入力3 */
#define		INTC_CH_TAPA4ESO			(815)		/* 非常用Hi-Z入力4 */
#define		INTC_CH_TAPA5ESO			(816)		/* 非常用Hi-Z入力5 */

/* QOS0 */
#define		INTC_CH_QOS0_0				(822)		/* CPU0コードフラッシュバスポート (Ch0) */
#define		INTC_CH_QOS0_1				(822)		/* CPU0周辺機器バスポート (Ch0) */
#define		INTC_CH_QOS0_2				(822)		/* CPU0クラスタRAMバスポート (Ch0) */
#define		INTC_CH_QOS0_3				(822)		/* CPU1コードフラッシュバスポート (Ch0) */
#define		INTC_CH_QOS0_4				(822)		/* CPU1周辺機器バスポート (Ch0) */
#define		INTC_CH_QOS0_5				(822)		/* CPU1クラスタRAMバスポート (Ch0) */
#define		INTC_CH_QOS0_6				(822)		/* CPU2コードフラッシュバスポート (Ch0) */
#define		INTC_CH_QOS0_7				(822)		/* CPU2周辺機器バスポート (Ch0) */
#define		INTC_CH_QOS0_8				(822)		/* CPU2クラスタRAMバスポート (Ch0) */
#define		INTC_CH_QOS0_24				(822)		/* DTS (Ch0) */
#define		INTC_CH_QOS0_25				(822)		/* SDMAC0 (Ch0) */
#define		INTC_CH_QOS0_26				(822)		/* SDMAC1 (Ch0) */
#define		INTC_CH_QOS0_27				(822)		/* ICUM Code Flash bus (Ch0) */
#define		INTC_CH_QOS0_28				(822)		/* ICUM System bus (Ch0) */
#define		INTC_CH_QOS0_31				(822)		/* DFP Code Flash bus (Ch0) */
#define		INTC_CH_QOS0_32				(822)		/* DFP System bus (Ch0) */
#define		INTC_CH_QOS0_33				(822)		/* GTM (Ch0) */
#define		INTC_CH_QOS0_34				(822)		/* RHSIF0 (Ch0) */
#define		INTC_CH_QOS0_36				(822)		/* Flexray0 (Ch0) */
#define		INTC_CH_QOS0_38				(822)		/* Ether 0 (Ch0) */

/* QOS1 */
#define		INTC_CH_QOS1_0				(823)		/* CPU0コードフラッシュバスポート (Ch1) */
#define		INTC_CH_QOS1_1				(823)		/* CPU0周辺機器バスポート (Ch1) */
#define		INTC_CH_QOS1_2				(823)		/* CPU0クラスタRAMバスポート (Ch1) */
#define		INTC_CH_QOS1_3				(823)		/* CPU1コードフラッシュバスポート (Ch1) */
#define		INTC_CH_QOS1_4				(823)		/* CPU1周辺機器バスポート (Ch1) */
#define		INTC_CH_QOS1_5				(823)		/* CPU1クラスタRAMバスポート (Ch1) */
#define		INTC_CH_QOS1_6				(823)		/* CPU2コードフラッシュバスポート (Ch1) */
#define		INTC_CH_QOS1_7				(823)		/* CPU2周辺機器バスポート (Ch1) */
#define		INTC_CH_QOS1_8				(823)		/* CPU2クラスタRAMバスポート (Ch1) */
#define		INTC_CH_QOS1_24				(823)		/* DTS (Ch1) */
#define		INTC_CH_QOS1_25				(823)		/* SDMAC0 (Ch1) */
#define		INTC_CH_QOS1_26				(823)		/* SDMAC1 (Ch1) */
#define		INTC_CH_QOS1_27				(823)		/* ICUM Code Flash bus (Ch1) */
#define		INTC_CH_QOS1_28				(823)		/* ICUM System bus (Ch1) */
#define		INTC_CH_QOS1_31				(823)		/* DFP Code Flash bus (Ch1) */
#define		INTC_CH_QOS1_32				(823)		/* DFP System bus (Ch1) */
#define		INTC_CH_QOS1_33				(823)		/* GTM (Ch1) */
#define		INTC_CH_QOS1_34				(823)		/* RHSIF0 (Ch1) */
#define		INTC_CH_QOS1_36				(823)		/* Flexray0 (Ch1) */
#define		INTC_CH_QOS1_38				(823)		/* Ether 0 (Ch1) */

/* QOS2 */
#define		INTC_CH_QOS2_0				(824)		/* CPU0コードフラッシュバスポート (Ch2) */
#define		INTC_CH_QOS2_1				(824)		/* CPU0周辺機器バスポート (Ch2) */
#define		INTC_CH_QOS2_2				(824)		/* CPU0クラスタRAMバスポート (Ch2) */
#define		INTC_CH_QOS2_3				(824)		/* CPU1コードフラッシュバスポート (Ch2) */
#define		INTC_CH_QOS2_4				(824)		/* CPU1周辺機器バスポート (Ch2) */
#define		INTC_CH_QOS2_5				(824)		/* CPU1クラスタRAMバスポート (Ch2) */
#define		INTC_CH_QOS2_6				(824)		/* CPU2コードフラッシュバスポート (Ch2) */
#define		INTC_CH_QOS2_7				(824)		/* CPU2周辺機器バスポート (Ch2) */
#define		INTC_CH_QOS2_8				(824)		/* CPU2クラスタRAMバスポート (Ch2) */
#define		INTC_CH_QOS2_24				(824)		/* DTS (Ch2) */
#define		INTC_CH_QOS2_25				(824)		/* SDMAC0 (Ch2) */
#define		INTC_CH_QOS2_26				(824)		/* SDMAC1 (Ch2) */
#define		INTC_CH_QOS2_27				(824)		/* ICUM Code Flash bus (Ch2) */
#define		INTC_CH_QOS2_28				(824)		/* ICUM System bus (Ch2) */
#define		INTC_CH_QOS2_31				(824)		/* DFP Code Flash bus (Ch2) */
#define		INTC_CH_QOS2_32				(824)		/* DFP System bus (Ch2) */
#define		INTC_CH_QOS2_33				(824)		/* GTM (Ch2) */
#define		INTC_CH_QOS2_34				(824)		/* RHSIF0 (Ch2) */
#define		INTC_CH_QOS2_36				(824)		/* Flexray0 (Ch2) */
#define		INTC_CH_QOS2_38				(824)		/* Ether 0 (Ch2) */

/* RS-CANFD_mux7 */
#define		INTC_CH_RCANERR_MUX7		(722)		/* CANnエラー割り込み (n=0-9) (mux7) */
#define		INTC_CH_RCANREC_MUX7		(723)		/* CANn送受信FIFO受信完了割り込み (n=0-9) (mux7) */
#define		INTC_CH_RCANTRX_MUX7		(724)		/* CANn送信割り込み (n=0-9) (mux7) */
#define		INTC_CH_RCANVMTX_MUX7		(725)		/* CANn仮想マシンTX割り込み (n=0-9) (mux7) */
#define		INTC_CH_RCANVMRX_MUX7		(726)		/* CANn仮想マシンRX割り込み (n=0-9) (mux7) */
#define		INTC_CH_RCANVMERR_MUX7		(727)		/* CANn仮想マシンエラー割り込み (n=0-9) (mux7) */

/* RS-CANFD_mux8 */
#define		INTC_CH_RCANnERR_MUX8		(851)		/* CANnエラー割り込み (n=0-9) (mux8) */
#define		INTC_CH_RCANnREC_MUX8		(852)		/* CANn送受信FIFO受信完了割り込み (n=0-9) (mux8) */
#define		INTC_CH_RCANnTRX_MUX8		(853)		/* CANn送信割り込み (n=0-9) (mux8) */
#define		INTC_CH_RCANnVMTX_MUX8		(854)		/* CANn仮想マシンTX割り込み (n=0-9) (mux8) */
#define		INTC_CH_RCANnVMRX_MUX8		(855)		/* CANn仮想マシンRX割り込み (n=0-9) (mux8) */
#define		INTC_CH_RCANnVMERR_MUX8		(856)		/* CANn仮想マシンエラー割り込み (n=0-9) (mux8) */

/* RS-CANFD_mux9 */
#define		INTC_CH_RCANnERR_MUX9		(863)		/* CANnエラー割り込み (n=0-9) (mux9) */
#define		INTC_CH_RCANnREC_MUX9		(864)		/* CANn送受信FIFO受信完了割り込み (n=0-9) (mux9) */
#define		INTC_CH_RCANnTRX_MUX9		(865)		/* CANn送信割り込み (n=0-9) (mux9) */
#define		INTC_CH_RCANnVMTX_MUX9		(866)		/* CANn仮想マシンTX割り込み (n=0-9) (mux9) */
#define		INTC_CH_RCANnVMRX_MUX9		(867)		/* CANn仮想マシンRX割り込み (n=0-9) (mux9) */
#define		INTC_CH_RCANnVMERR_MUX9		(868)		/* CANn仮想マシンエラー割り込み (n=0-9) (mux9) */

/* RS-CANFD_mux10 */
#define		INTC_CH_RCANnERR_MUX10		(871)		/* CANnエラー割り込み (n=0-9) (mux10) */
#define		INTC_CH_RCANnREC_MUX10		(872)		/* CANn送受信FIFO受信完了割り込み (n=0-9) (mux10) */
#define		INTC_CH_RCANnTRX_MUX10		(873)		/* CANn送信割り込み (n=0-9) (mux10) */
#define		INTC_CH_RCANnVMTX_MUX10		(874)		/* CANn仮想マシンTX割り込み (n=0-9) (mux10) */
#define		INTC_CH_RCANnVMRX_MUX10		(875)		/* CANn仮想マシンRX割り込み (n=0-9) (mux10) */
#define		INTC_CH_RCANnVMERR_MUX10	(876)		/* CANn仮想マシンエラー割り込み (n=0-9) (mux10) */

/* RS-CANFD_mux11 */
#define		INTC_CH_RCANnERR_MUX11		(917)		/* CANnエラー割り込み (n=0-9) (mux11) */
#define		INTC_CH_RCANnREC_MUX11		(918)		/* CANn送受信FIFO受信完了割り込み (n=0-9) (mux11) */
#define		INTC_CH_RCANnTRX_MUX11		(919)		/* CANn送信割り込み (n=0-9) (mux11) */
#define		INTC_CH_RCANnVMTX_MUX11		(920)		/* CANn仮想マシンTX割り込み (n=0-9) (mux11) */
#define		INTC_CH_RCANnVMRX_MUX11		(921)		/* CANn仮想マシンRX割り込み (n=0-9) (mux11) */
#define		INTC_CH_RCANnVMERR_MUX11	(922)		/* CANn仮想マシンエラー割り込み (n=0-9) (mux11) */

/* RS-CANFD_mux12 */
#define		INTC_CH_RCANnERR_MUX12		(924)		/* CANnエラー割り込み (n=0-9) (mux12) */
#define		INTC_CH_RCANnREC_MUX12		(925)		/* CANn送受信FIFO受信完了割り込み (n=0-9) (mux12) */
#define		INTC_CH_RCANnTRX_MUX12		(926)		/* CANn送信割り込み (n=0-9) (mux12) */
#define		INTC_CH_RCANnVMTX_MUX12		(927)		/* CANn仮想マシンTX割り込み (n=0-9) (mux12) */
#define		INTC_CH_RCANnVMRX_MUX12		(928)		/* CANn仮想マシンRX割り込み (n=0-9) (mux12) */
#define		INTC_CH_RCANnVMERR_MUX12	(929)		/* CANn仮想マシンエラー割り込み (n=0-9) (mux12) */

/* RS-CANFD_mux13 */
#define		INTC_CH_RCANnERR_MUX13		(930)		/* CANnエラー割り込み (n=0-9) (mux13) */
#define		INTC_CH_RCANnREC_MUX13		(931)		/* CANn送受信FIFO受信完了割り込み (n=0-9) (mux13) */
#define		INTC_CH_RCANnTRX_MUX13		(932)		/* CANn送信割り込み (n=0-9) (mux13) */
#define		INTC_CH_RCANnVMTX_MUX13		(933)		/* CANn仮想マシンTX割り込み (n=0-9) (mux13) */
#define		INTC_CH_RCANnVMRX_MUX13		(934)		/* CANn仮想マシンRX割り込み (n=0-9) (mux13) */
#define		INTC_CH_RCANnVMERR_MUX13	(935)		/* CANn仮想マシンエラー割り込み (n=0-9) (mux13) */

/* RS-CANFD_mux14 */
#define		INTC_CH_RCANnERR_MUX14		(936)		/* CANnエラー割り込み (n=0-9) (mux14) */
#define		INTC_CH_RCANnREC_MUX14		(937)		/* CANn送受信FIFO受信完了割り込み (n=0-9) (mux14) */
#define		INTC_CH_RCANnTRX_MUX14		(938)		/* CANn送信割り込み (n=0-9) (mux14) */
#define		INTC_CH_RCANnVMTX_MUX14		(939)		/* CANn仮想マシンTX割り込み (n=0-9) (mux14) */
#define		INTC_CH_RCANnVMRX_MUX14		(940)		/* CANn仮想マシンRX割り込み (n=0-9) (mux14) */
#define		INTC_CH_RCANnVMERR_MUX14	(941)		/* CANn仮想マシンエラー割り込み (n=0-9) (mux14) */

/* RSENT*/
#define		INTC_CH_RSENT0_RI			(733)	/* RSENT0 受信割り込み */
#define		INTC_CH_RSENT1_RI			(734)	/* RSENT1 受信割り込み */
#define		INTC_CH_RSENT2_RI			(735)	/* RSENT2 受信割り込み */
#define		INTC_CH_RSENT3_RI			(736)	/* RSENT3 受信割り込み */
#define		INTC_CH_RSENT4_RI			(737)	/* RSENT4 受信割り込み */
#define		INTC_CH_RSENT5_RI			(738)	/* RSENT5 受信割り込み */
#define		INTC_CH_RSENT6_RI			(739)	/* RSENT6 受信割り込み */
#define		INTC_CH_RSENT7_RI			(740)	/* RSENT7 受信割り込み */
#define		INTC_CH_RSENT8_RI			(741)	/* RSENT8 受信割り込み */
#define		INTC_CH_RSENT9_RI			(742)	/* RSENT9 受信割り込み */
#define		INTC_CH_RSENT10_RI			(890)	/* RSENT10 受信割り込み */
#define		INTC_CH_RSENT11_RI			(891)	/* RSENT11 受信割り込み */
#define		INTC_CH_RSENT12_RI			(892)	/* RSENT12 受信割り込み */
#define		INTC_CH_RSENT13_RI			(893)	/* RSENT13 受信割り込み */
#define		INTC_CH_RSENT14_RI			(894)	/* RSENT14 受信割り込み */
#define		INTC_CH_RSENT15_RI			(895)	/* RSENT15 受信割り込み */
#define		INTC_CH_RSENT16_RI			(896)	/* RSENT16 受信割り込み */
#define		INTC_CH_RSENT17_RI			(897)	/* RSENT17 受信割り込み */
#define		INTC_CH_RSENT18_RI			(898)	/* RSENT18 受信割り込み */
#define		INTC_CH_RSENT19_RI			(899)	/* RSENT19 受信割り込み */
#define		INTC_CH_RSENT20_RI			(900)	/* RSENT20 受信割り込み */
#define		INTC_CH_RSENT21_RI			(901)	/* RSENT21 受信割り込み */
#define		INTC_CH_RSENT22_RI			(902)	/* RSENT22 受信割り込み */
#define		INTC_CH_RSENT23_RI			(903)	/* RSENT23 受信割り込み */
#define		INTC_CH_RSENT24_RI			(904)	/* RSENT24 受信割り込み */
#define		INTC_CH_RSENT25_RI			(905)	/* RSENT25 受信割り込み */
#define		INTC_CH_RSENT26_RI			(906)	/* RSENT26 受信割り込み */
#define		INTC_CH_RSENT27_RI			(907)	/* RSENT27 受信割り込み */
#define		INTC_CH_RSENT28_RI			(908)	/* RSENT28 受信割り込み */
#define		INTC_CH_RSENT29_RI			(909)	/* RSENT29 受信割り込み */

#define		INTC_CH_RSENT0_SI			(743)	/* RSENT0 ステータス割り込み */
#define		INTC_CH_RSENT1_SI			(744)	/* RSENT1 ステータス割り込み */
#define		INTC_CH_RSENT2_SI			(745)	/* RSENT2 ステータス割り込み */
#define		INTC_CH_RSENT3_SI			(746)	/* RSENT3 ステータス割り込み */
#define		INTC_CH_RSENT4_SI			(747)	/* RSENT4 ステータス割り込み */
#define		INTC_CH_RSENT5_SI			(748)	/* RSENT5 ステータス割り込み */
#define		INTC_CH_RSENT6_SI			(749)	/* RSENT6 ステータス割り込み */
#define		INTC_CH_RSENT7_SI			(750)	/* RSENT7 ステータス割り込み */
#define		INTC_CH_RSENT8_SI			(751)	/* RSENT8 ステータス割り込み */
#define		INTC_CH_RSENT9_SI			(752)	/* RSENT9 ステータス割り込み */
#define		INTC_CH_RSENT10_SI			(910)	/* RSENT10 ステータス割り込み */
#define		INTC_CH_RSENT11_SI			(911)	/* RSENT11 ステータス割り込み */
#define		INTC_CH_RSENT12_SI			(912)	/* RSENT12 ステータス割り込み */
#define		INTC_CH_RSENT13_SI			(913)	/* RSENT13 ステータス割り込み */
#define		INTC_CH_RSENT14_SI			(914)	/* RSENT14 ステータス割り込み */
#define		INTC_CH_RSENT15_SI			(915)	/* RSENT15 ステータス割り込み */
#define		INTC_CH_RSENT16_SI			(916)	/* RSENT16 ステータス割り込み */
#define		INTC_CH_RSENT17_SI			(917)	/* RSENT17 ステータス割り込み */
#define		INTC_CH_RSENT18_SI			(918)	/* RSENT18 ステータス割り込み */
#define		INTC_CH_RSENT19_SI			(919)	/* RSENT19 ステータス割り込み */
#define		INTC_CH_RSENT20_SI			(920)	/* RSENT20 ステータス割り込み */
#define		INTC_CH_RSENT21_SI			(921)	/* RSENT21 ステータス割り込み */
#define		INTC_CH_RSENT22_SI			(922)	/* RSENT22 ステータス割り込み */
#define		INTC_CH_RSENT23_SI			(923)	/* RSENT23 テータス割り込み */
#define		INTC_CH_RSENT24_SI			(924)	/* RSENT24 ステータス割り込み */
#define		INTC_CH_RSENT25_SI			(925)	/* RSENT25 ステータス割り込み */
#define		INTC_CH_RSENT26_SI			(926)	/* RSENT26 ステータス割り込み */
#define		INTC_CH_RSENT27_SI			(927)	/* RSENT27 ステータス割り込み */
#define		INTC_CH_RSENT28_SI			(928)	/* RSENT28 ステータス割り込み */
#define		INTC_CH_RSENT29_SI			(929)	/* RSENT29 ステータス割り込み */

/* RHSIF */
#define		INTC_CH_RHSIF0_TXCMP		(871)	/* RHSIF0 送信完了割り込み */
#define		INTC_CH_RHSIF0_TXERR		(872)	/* RHSIF0 送信例外割り込み */
#define		INTC_CH_RHSIF0_RXCMP		(873)	/* RHSIF0 受信完了割り込み */
#define		INTC_CH_RHSIF0_RXERR		(874)	/* RHSIF0 受信例外割り込み */
#define		INTC_CH_RHSIF0_RXICLC		(875)	/* RHSIF0 ICLC受信割り込み */
#define		INTC_CH_RHSIF0_HSIFCH0		(876)	/* RHSIF0 CH0割り込み */
#define		INTC_CH_RHSIF0_HSIFCH1		(877)	/* RHSIF0 CH1割り込み */
#define		INTC_CH_RHSIF0_HSIFCH2		(878)	/* RHSIF0 CH2割り込み */
#define		INTC_CH_RHSIF0_HSIFCH3		(879)	/* RHSIF0 CH3割り込み */
#define		INTC_CH_RHSIF0_HSIFSTR		(880)	/* RHSIF0 ストリーム割り込み */
#define		INTC_CH_RHSIF0_HSIFERR		(881)	/* RHSIF0 エラー割り込み */

/* RIIC */
#define		INTC_CH_RIIC0RI				(882)	/* RIIC0 受信終了割り込み */
#define		INTC_CH_RIIC0TI				(883)	/* RIIC0 送信データ空割り込み */
#define		INTC_CH_RIIC1RI				(884)	/* RIIC1 受信終了割り込み */
#define		INTC_CH_RIIC1TI				(885)	/* RIIC1 送信データ空割り込み */
#define		INTC_CH_RIIC0EE				(886)	/* RIIC0 通信異常またはイベント発生割り込み */
#define		INTC_CH_RIIC0TEI			(887)	/* RIIC0 送信終了割り込み */
#define		INTC_CH_RIIC1EE				(888)	/* RIIC1 通信異常またはイベント発生割り込み */
#define		INTC_CH_RIIC1TEI			(889)	/* RIIC1 送信終了割り込み */

/* RHSB */
#define		INTC_CH_RHSB0_DTF			(604)	/* RHSB0 データフレーム通信割り込み */
#define		INTC_CH_RHSB0_CTF			(605)	/* RHSB0 コマンドフレーム通信割り込み */
#define		INTC_CH_RHSB0_ETF			(606)	/* RHSB0 エマージェンシーフレーム通信割り込み */
#define		INTC_CH_RHSB0_RF			(607)	/* RHSB0 データ受信割り込み */
#define		INTC_CH_RHSB0_ERR			(608)	/* RHSB0 アップストリームエラー・タイムアウト検出・データ消失割り込み */
#define		INTC_CH_RHSB0_UFR			(609)	/* RHSB0 受信されたアップストリームフレーム */
#define		INTC_CH_RHSB0_UEI0			(610)	/* RHSB0 アップストリーム外部割り込み0 */
#define		INTC_CH_RHSB0_UEI1			(611)	/* RHSB0 アップストリーム外部割り込み1 */

#define		INTC_CH_RHSB1_DTF			(612)	/* RHSB1 データフレーム通信割り込み */
#define		INTC_CH_RHSB1_CTF			(613)	/* RHSB1 コマンドフレーム通信割り込み */
#define		INTC_CH_RHSB1_ETF			(614)	/* RHSB1 エマージェンシーフレーム通信割り込み */
#define		INTC_CH_RHSB1_RF			(615)	/* RHSB1 データ受信割り込み */
#define		INTC_CH_RHSB1_ERR			(616)	/* RHSB1 アップストリームエラー・タイムアウト検出・データ消失割り込み */
#define		INTC_CH_RHSB1_UFR			(617)	/* RHSB1 受信されたアップストリームフレーム */
#define		INTC_CH_RHSB1_UEI0			(618)	/* RHSB1 アップストリーム外部割り込み0 */
#define		INTC_CH_RHSB1_UEI1			(619)	/* RHSB1 アップストリーム外部割り込み1 */

#define		INTC_CH_RHSB2_DTF			(863)	/* RHSB2 データフレーム通信割り込み */
#define		INTC_CH_RHSB2_CTF			(864)	/* RHSB2 コマンドフレーム通信割り込み */
#define		INTC_CH_RHSB2_ETF			(865)	/* RHSB2 エマージェンシーフレーム通信割り込み */
#define		INTC_CH_RHSB2_RF			(866)	/* RHSB2 データ受信割り込み */
#define		INTC_CH_RHSB2_ERR			(867)	/* RHSB2 アップストリームエラー・タイムアウト検出・データ消失割り込み */
#define		INTC_CH_RHSB2_UFR			(868)	/* RHSB2 受信されたアップストリームフレーム */
#define		INTC_CH_RHSB2_UEI0			(869)	/* RHSB2 アップストリーム外部割り込み0 */
#define		INTC_CH_RHSB2_UEI1			(870)	/* RHSB2 アップストリーム外部割り込み1 */

/* FLXA */
#define		INTC_CH_FLXA0_LINE0			(722)	/* FLXA0 ユニバーサル割り込み */
#define		INTC_CH_FLXA0_LINE1			(723)	/* FLXA0 ユニバーサル割り込み */
#define		INTC_CH_FLXA0_TIM0			(724)	/* FLXA0 タイマー0割り込み */
#define		INTC_CH_FLXA0_TIM1			(725)	/* FLXA0 タイマー1割り込み */
#define		INTC_CH_FLXA0_TIM2			(726)	/* FLXA0 タイマー2割り込み */
#define		INTC_CH_FLXA0_FDA			(727)	/* FLXA0 FIFO データ使用割り込み */
#define		INTC_CH_FLXA0_FW			(728)	/* FLXA0 FIFO 転送異常割り込み */
#define		INTC_CH_FLXA0_OW			(729)	/* FLXA0 アウトプット転送ワーニング割り込み */
#define		INTC_CH_FLXA0_OT			(730)	/* FLXA0 アウトプット転送完了割り込み */
#define		INTC_CH_FLXA0_IQF			(731)	/* FLXA0 インプットキューフル割り込み */
#define		INTC_CH_FLXA0_IQE			(732)	/* FLXA0 インプットキューエンプティ割り込み */

/* TemperatureSenser */
#define		INTC_CH_TSOT_ERR			(762)	/* 温度センサー エラー割り込み */
#define		INTC_CH_TSOT_INTEND			(763)	/* 温度測定完了割り込み */
#define		INTC_CH_TSOT_ULIABE			(764)	/* 保証範囲異常/異常温度割り込み */

/* PSI5x */
#define		INTC_CH_PSI50SI				(930)		/* PSI50 ステータス割り込み */
#define		INTC_CH_PSI50RI				(931)		/* PSI50 受信割り込み */
#define		INTC_CH_PSI50TI				(932)		/* PSI50 転送割り込み */
#define		INTC_CH_PSI51SI				(933)		/* PSI51 ステータス割り込み */
#define		INTC_CH_PSI51RI				(934)		/* PSI51 受信割り込み */
#define		INTC_CH_PSI51TI				(935)		/* PSI51 転送割り込み */
#define		INTC_CH_PSI52SI				(936)		/* PSI52 ステータス割り込み */
#define		INTC_CH_PSI52RI				(937)		/* PSI52 受信割り込み */
#define		INTC_CH_PSI52TI				(938)		/* PSI52 転送割り込み */
#define		INTC_CH_PSI53SI				(939)		/* PSI53 ステータス割り込み */
#define		INTC_CH_PSI53RI				(940)		/* PSI53 受信割り込み */
#define		INTC_CH_PSI53TI				(941)		/* PSI53 転送割り込み */
#define		INTC_CH_PSI5W				(942)		/* 全チャネルイネーブルの終了通知割り込み */
#define		INTC_CH_PSI5S0INTCH0		(943)		/* PSI5S0 CH0 の通信割り込み */
#define		INTC_CH_PSI5S0INTCH1		(944)		/* PSI5S0 CH1 の通信割り込み */
#define		INTC_CH_PSI5S0INTCH2		(945)		/* PSI5S0 CH2 の通信割り込み */
#define		INTC_CH_PSI5S0INTCH3		(946)		/* PSI5S0 CH3 の通信割り込み */
#define		INTC_CH_PSI5S0INTCH4		(947)		/* PSI5S0 CH4 の通信割り込み */
#define		INTC_CH_PSI5S0INTCH5		(948)		/* PSI5S0 CH5 の通信割り込み */
#define		INTC_CH_PSI5S0INTCH6		(949)		/* PSI5S0 CH6 の通信割り込み */
#define		INTC_CH_PSI5S0INTCH7		(950)		/* PSI5S0 CH7 の通信割り込み */
#define		INTC_CH_PSI5S1INTCH0		(951)		/* PSI5S1 CH0 の通信割り込み */
#define		INTC_CH_PSI5S1INTCH1		(952)		/* PSI5S1 CH1 の通信割り込み */
#define		INTC_CH_PSI5S1INTCH2		(953)		/* PSI5S1 CH2 の通信割り込み */
#define		INTC_CH_PSI5S1INTCH3		(954)		/* PSI5S1 CH3 の通信割り込み */
#define		INTC_CH_PSI5S1INTCH4		(955)		/* PSI5S1 CH4 の通信割り込み */
#define		INTC_CH_PSI5S1INTCH5		(956)		/* PSI5S1 CH5 の通信割り込み */
#define		INTC_CH_PSI5S1INTCH6		(957)		/* PSI5S1 CH6 の通信割り込み */
#define		INTC_CH_PSI5S1INTCH7		(958)		/* PSI5S1 CH7 の通信割り込み */

/* INTMMCA0 */
#define		INTC_CH_MMCA0				(959)		/* MMCA 割り込み */

/* ATU Interrupt Head Number */
#define		INTC_CH_ATUA_HEAD			(86)	/* ATU TimerA 割り込み先頭CH */
#define		INTC_CH_ATUB_HEAD			(95)	/* ATU TimerB 割り込み先頭CH */
#define		INTC_CH_ATUC_HEAD			(104)	/* ATU TimerC 割り込み先頭CH */
#define		INTC_CH_ATUD_HEAD			(164)	/* ATU TimerD 割り込み先頭CH */
#define		INTC_CH_ATUE_HEAD			(212)	/* ATU TimerE 割り込み先頭CH */
#define		INTC_CH_ATUF_HEAD			(252)	/* ATU TimerF 割り込み先頭CH */
#define		INTC_CH_ATUG_HEAD			(272)	/* ATU TimerG 割り込み先頭CH */

/* ADC Interrupt Head Number */
#define		INTC_CH_ADC0_HEAD			(441)	/* ADCH ADC割り込み先頭CH */
#define		INTC_CH_ADC1_HEAD			(451)	/* ADCH ADC割り込み先頭CH */
#define		INTC_CH_ADC2_HEAD			(446)	/* ADCH ADC割り込み先頭CH */
#define		INTC_CH_ADC3_HEAD			(456)	/* ADCH ADC割り込み先頭CH */

#endif // zantei 未使用なのでコメントアウト

#endif /* REG_INTC_H */
/*-- End Of File -------------------------------------------------------------------------------*/
