/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_SWIC_IntErr.c                                         */
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include <EthSwt_SWIC_Cfg.h>
#include <LIB.h>
#include "EthSwt_SWIC_Reg.h"
#include "EthSwt_SWIC_Define.h"
#include "EthSwt_SWIC_IntErr.h"
#include "EthSwt_SWIC_IntErr_Cfg.h"
#include "EthSwt_SWIC_initRegListSeqGetInterrupt.h"
#include "EthSwt_SWIC_initRegListSeqPhySwicOff.h"
#include "EthSwt_SWIC_initRegListSeqInitSeq.h"
#include "EthSwt_SWIC_Cfg.h"
#include <Dio.h>
#include <Dio_Symbols.h>
/* -------------------------------------------------------------------------- */
#define D_ETHSWT_SWIC_EV_INTN_ERROR                     (9U)
#define	ETHSWT_SWIC_CNTCVL		(*((volatile sint32*)0xE6081000uL))		/* Current Count Value Lower register (CNTCVL) QAC対応(sint32) */
#define	SWIC_REG_BIT(a)		(1uL << (a))			/* ビット */
/* -------------------------------------------------------------------------- */
struct swic_reg_tbl {								/* レジスタテーブル */
	const swic_reg_data_t	*tbl;
	const uint32			num;
};
static struct {
    sint32								time;
    volatile uint8						req;
} swicGetIntErrTimer;
/* -------------------------------------------------------------------------- */
static uint8 ethswt_swic_interr_check_intn(void);
static Std_ReturnType ethswt_swic_interr_errDtct (uint32 * const errFactor);
static void ethswt_swic_interr_portMacResetRequest(uint32 * const errFactor);
static Std_ReturnType ethswt_swic_interr_TblReg(const uint8 SwitchPortIdx, const struct swic_reg_tbl tbl[], const uint32 num, uint32 * const errFactor);
/* -------------------------------------------------------------------------- */

void EthSwt_SWIC_IntErr_Init(void)
{
	/* 周期タイマの初期化 */
	swicGetIntErrTimer.time = 0;
	swicGetIntErrTimer.req = STD_ON;
}

/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_IntErr_TimerUpdate (void)
{
	swicGetIntErrTimer.time = swicGetIntErrTimer.time + D_ETHSWT_SWIC_PERIOD;
	if (D_ETHSWT_SWIC_INTERR_GET_CYCLE <= swicGetIntErrTimer.time) {
		swicGetIntErrTimer.time = swicGetIntErrTimer.time - D_ETHSWT_SWIC_INTERR_GET_CYCLE;
		swicGetIntErrTimer.req = STD_ON;
	}

	return;
}
/* -------------------------------------------------------------------------- */

void EthSwt_SWIC_IntErr_Clear(void)
{
	/* 周期タイマの初期化 */
	LIB_DI();
	swicGetIntErrTimer.time = 0;
	swicGetIntErrTimer.req = STD_ON;
	LIB_EI();
}
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_IntErr_Action(uint32 * const errFactor)
{
	Std_ReturnType result = E_OK;
	uint8 idx;
	uint8 req;
	uint8 intn;

	LIB_DI();
	req = swicGetIntErrTimer.req;
	LIB_EI();

	if(STD_ON == req) {
		LIB_DI();
		swicGetIntErrTimer.req = STD_OFF;
		LIB_EI();

    	/* ETH_U2A_RESET_Nの確認 */
		intn = ethswt_swic_interr_check_intn();
		if(STD_LOW == intn)
		{
			/* SWIC内部エラー検出 */
			result = ethswt_swic_interr_errDtct(errFactor);
		}
	}
	return result;
}
/* -------------------------------------------------------------------------- */
static uint8 ethswt_swic_interr_check_intn(void)
{
	return (U1)Dio_ReadChannel(DIO_ID_APORT4_CH1);	/* ETH_U2A_RESET_Nの確認 */
}
/* -------------------------------------------------------------------------- */
static Std_ReturnType ethswt_swic_interr_errDtct (uint32 * const errFactor)
{
	Std_ReturnType	result = E_NOT_OK;

	static struct {								/* ベリファイ異常記憶用 */
		const swic_reg_data_t *volatile	tbl;	/* 異常テーブル */
		volatile uint32					idx;	/* 異常位置 */
		volatile uint16					val;	/* 読めた値 */
		volatile uint8					mon_seq;/* 割り込み時の処理レジスタ種別 */
		volatile uint8					mon_val;/* 割り込み時の処理レジスタ値 */
		volatile uint32					rst_fct;/* リセット要因 */
	}	swic_Reg_Err;

	struct swic_reg_mon;
	struct swic_reg_bit {						/* レジスタ設定[割り込み時の処理]で灰色のbitは無効ビット */
		const uint32				bit;		/* 対象ビット */
		const struct swic_reg_mon	*tbl;		/* 継続先 */
		const sint32				prc;		/* 処理番号 */
	};
	struct swic_reg_itm {
		const struct swic_reg_bit	*tbl;
		const uint32				num;
	};
	struct swic_reg_mon {
		const struct swic_reg_tbl	tbl;
		const struct swic_reg_itm	fnc;
		const uint8					log;
	};
	static const struct swic_reg_bit bit_unc2[]	/* [WD_CTRL 0x3A] Secondary Uncorrectable ECC Watch Dog Event */
	=	{ {SWIC_REG_BIT(6), NULL_PTR,  1}		/* bit6:①ハードリセット [EgrAct UCECC Event]     */
		, {SWIC_REG_BIT(4), NULL_PTR,  1}		/* bit4:①ハードリセット [Ingress UCECCErr Event] */
		};
	static const struct swic_reg_mon seq_unc2 = {SWIC_REG_TBL(g_regListSeqGetWatchdog2ndUncorectECC), SWIC_REG_TBL(bit_unc2), 0x3Au};
	static const struct swic_reg_bit bit_unc[]	/* [WD_CTRL 0x26] Uncorrectable ECC Watch Dog Event */
	=	{ {SWIC_REG_BIT(7), NULL_PTR,  1}		/* bit7:①ハードリセット [PktUCECCErrEvent]       */
		, {SWIC_REG_BIT(6), NULL_PTR,  1}		/* bit6:①ハードリセット [PvtUCECCErrEvent]       */
		, {SWIC_REG_BIT(4), NULL_PTR,  1}		/* bit4:①ハードリセット [TcamActUCECCErrEvent]   */
		, {SWIC_REG_BIT(3), NULL_PTR,  1}		/* bit3:①ハードリセット [QUCECCErrEvent]         */
		, {SWIC_REG_BIT(2), NULL_PTR,  1}		/* bit2:①ハードリセット [VtuUCECCErrEvent]       */
		, {SWIC_REG_BIT(1), NULL_PTR,  1}		/* bit1:①ハードリセット [AtuUCECCErrEvent]       */
		, {SWIC_REG_BIT(0), &seq_unc2, 0}		/* bit0:[WD_CTRL 0x3A]   [SecondaryUCECCErrEvent] */
		};
	static const struct swic_reg_bit bit_misc[]	/* [WD_CTRL 0x16] Miscellaneous Watch Dog Event */
	=	{ {SWIC_REG_BIT(7), NULL_PTR,  1}		/* bit7:①ハードリセット [ECCOut MisEven]        */
		, {SWIC_REG_BIT(6), NULL_PTR,  1}		/* bit6:①ハードリセット [ECCErr InjectMisEvent] */
		, {SWIC_REG_BIT(5), NULL_PTR,  1}		/* bit5:①ハードリセット [MBus ParityErrEvent]   */
		, {SWIC_REG_BIT(4), NULL_PTR,  1}		/* bit4:①ハードリセット [Reg ParityErr Event]   */
		, {SWIC_REG_BIT(1), NULL_PTR,  1}		/* bit1:①ハードリセット [PLLWDEvent]            */
		};
	static const struct swic_reg_bit bit_data[]	/* [WD_CTRL 0x12] Data Path Watch Dog Event */
	=	{ {SWIC_REG_BIT(5), NULL_PTR,  2}		/* bit5:②FIRソフトリセット [FBus CRCErr Event] */
		, {SWIC_REG_BIT(2), NULL_PTR,  2}		/* bit2:②FIRソフトリセット [QC WD Event]       */
		, {SWIC_REG_BIT(1), NULL_PTR,  2}		/* bit1:②FIRソフトリセット [EgressWD Event]    */
		};
	static const struct swic_reg_mon seq_unc  = {SWIC_REG_TBL(g_regListSeqGetWatchdogUncorectECC),    SWIC_REG_TBL(bit_unc),  0x26u};
	static const struct swic_reg_mon seq_misc = {SWIC_REG_TBL(g_regListSeqGetWatchdogMiscellaneous),  SWIC_REG_TBL(bit_misc), 0x16u};
	static const struct swic_reg_mon seq_data = {SWIC_REG_TBL(g_regListSeqGetWatchdogDatePath),       SWIC_REG_TBL(bit_data), 0x12u};
	static const struct swic_reg_bit bit_src[]	/* [WD_CTRL 0x00] Watch Dog Interrupt Source */
	=	{ {SWIC_REG_BIT(7), NULL_PTR,  1}		/* bit7:①ハードリセット [SMHaltWD Int]  */
		, {SWIC_REG_BIT(5), &seq_unc,  0}		/* bit5:[WD_CTRL 0x26]   [ParityWD Int]  */
		, {SWIC_REG_BIT(1), &seq_misc, 0}		/* bit1:[WD_CTRL 0x16]   [MiscWDInt]     */
		, {SWIC_REG_BIT(0), &seq_data, 0}		/* bit0:[WD_CTRL 0x12]   [DataPathWDInt] */
		};
	static const struct swic_reg_mon seq_src  = {SWIC_REG_TBL(g_regListSeqGetWatchdogIntSource),      SWIC_REG_TBL(bit_src), 0x00u};
		
	Std_ReturnType				err;
	const struct swic_reg_mon	*tbl = &seq_src;
	uint32						val = 0uL;

	/* Watch Dog Interrupt Sourceの指定bitのいずれかが1になっているか確認 */
	do {
		const struct swic_reg_bit	*const bit = tbl->fnc.tbl;
		const uint32				num = tbl->fnc.num;
		uint32						i;
		uint32						msk;
        result = EthSwt_SWIC_Reg_SetTbl(tbl->tbl.tbl, tbl->tbl.num, &val , errFactor);
		if (E_NOT_OK == result) { break; }			/* return reslut;を変更*/
		swic_Reg_Err.mon_val = (uint8)val;

		tbl = NULL_PTR;
		msk = 0uL;								/* 有効ビット算出 */
		for (i=0uL ; i<num ; i++)
		{
			msk |= bit[i].bit;
		}
		val &= msk;
		if (0uL == val) {					/* 有効なbit無:③処置不要：読んでも落ちないbitもあるので継続 */
			*errFactor = D_ETHSWT_SWIC_ERR_WRONGVALUE;	/* 期待値は有効なbitがあることのため */
			result = E_NOT_OK;				/* 早期リターンから変更 */
			break;
		}	
		for (i=0uL ; i<num ; i++) {
			if (val != bit[i].bit) { continue; }/* 1bit一致のみ */
			if (bit[i].tbl != NULL_PTR) {
				tbl = bit[i].tbl;
				break;
			}
			switch (bit[i].prc) {
			case 1:		/* ①FIRハードリセット */
				result = E_NOT_OK;
				break;						/* breakを追加 */
			case 2:		/* ②FIRソフトリセット */
				ethswt_swic_interr_portMacResetRequest(errFactor);
				break;						/* breakを追加 */
			default:	/* 処理無し */
			}
			break;
		}

	}	while (NULL_PTR != tbl);
	/* FIRハードリセット検知 もしくは複数ビット1:①FIRハードリセット */
	if(E_NOT_OK == result && D_ETHSWT_SWIC_ERR_NONE == *errFactor )
	{
		/* ①FIRハードリセット */		
		*errFactor = D_ETHSWT_SWIC_EV_INTN_ERROR;
	}
	return result;

}
static Std_ReturnType ethswt_swic_interr_tblReg(const uint8 SwitchPortIdx, const struct swic_reg_tbl tbl[], const uint32 num, uint32 * const errFactor)
{
	uint32		val;	/* g_regListSeqSet100BTxStartなどの余分な読み込み対策 */
	if (SwitchPortIdx >= num)				{ return E_NOT_OK; }
	if (tbl[SwitchPortIdx].num <= 0uL)		{ return E_NOT_OK; }
	if (tbl[SwitchPortIdx].tbl == NULL_PTR)	{ return E_NOT_OK; }
	return EthSwt_SWIC_Reg_SetTbl(tbl[SwitchPortIdx].tbl, tbl[SwitchPortIdx].num, &val , errFactor);
}

void ethswt_swic_interr_waitMS(const sint32 tmo)
{
	const sint32	st  = ETHSWT_SWIC_CNTCVL;		/* 257sより小さい待ちなのでLOのみ使用 */
	const sint32	par = (tmo * 16670L) + 1L;		/* 1s=16666660:150ppm:[少]×[多]○ */
	sint32			i;
	for (i = tmo * (1000000L/6L) ; i > 0L ; i--) {	/* 1GHz:1ループ6命令としてガード(実測値150倍) */
		const sint32	et = ETHSWT_SWIC_CNTCVL;
		if ((et - st) > par)	{ break; }			/* QAC対策でsint32使用/ms待ちなので問題なし */
	}
	return;
}
/* -------------------------------------------------------------------------- */
static void ethswt_swic_interr_portMacResetRequest(uint32 * const errFactor)
{
	static const struct {
		const struct swic_reg_tbl	tbl;	/* 処理テーブル */
		const sint32				tmo;	/* 処理後に待つ時間(ms) */
	}	tbl[]
	=	{ {SWIC_REG_TBL(g_regListSeqRelayOff),	2}	/* 2ms wait */
		, {SWIC_REG_TBL(g_regListSeqSWICReset),	0}	/* ↑余分な読み込みがあるのでチェックにできない */
		, {SWIC_REG_TBL(g_regListSeqRelayOn),	0}
		};
	static const struct swic_reg_tbl off[]
	=	{ {&g_regListSeqRelayOff[14],	2u}	/* P8 */
		, {&g_regListSeqRelayOff[0],	2u}	/* P1 */
		, {&g_regListSeqRelayOff[2],	2u}
		, {&g_regListSeqRelayOff[4],	2u}
		, {&g_regListSeqRelayOff[6],	2u}
		, {&g_regListSeqRelayOff[8],	2u}
		, {&g_regListSeqRelayOff[10],	2u}
		};
	uint32	i;
	uint32	val;
	uint8	idx;
	for (i=0u ; i<SWIC_TBL_NUM(tbl); i++) {
		(void)EthSwt_SWIC_Reg_SetTbl(tbl[i].tbl.tbl, tbl[i].tbl.num, &val , errFactor);
		if (0 < tbl[i].tmo ) {
			ethswt_swic_interr_waitMS(tbl[i].tmo);
		}
	}
	for (idx=0U; idx<D_ETHSWT_SWIC_PORT_NUM; idx++) {
		if (G_ETHSWT_SWIC_PORT_DEFINE[idx] != ETH_MODE_DOWN)	{ continue; }	/* リンクダウン不要 */
		(void)ethswt_swic_interr_tblReg(idx, off, SWIC_TBL_NUM(off), errFactor);
	}
	return;}
