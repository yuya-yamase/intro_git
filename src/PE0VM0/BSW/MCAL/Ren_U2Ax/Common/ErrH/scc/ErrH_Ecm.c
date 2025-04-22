/* ErrH-r04-3000-0200-b-v00 */
/************************************************************************************************/
/*																								*/
/*		ErrH Driver																				*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

/*==============================================================================================*/
/* include files																				*/
/*==============================================================================================*/
#include	"Std_Types.h"
#include	"Mcal_SpalCmn.h"
#include	"bswlib.h"
#include	"Os.h"

#include	"ErrH_cfg.h"
#include	"ErrH_mcu_def.h"

#include	"errh_reg_intc.h"

#include	"ErrH.h"
#include	"ErrH_Ecc.h"
#include	"ErrH_Ecm.h"

/*==============================================================================================*/
/* prototypes																					*/
/*==============================================================================================*/
static	U2		ErrH_Ecm_GetErrorId( U1 t_u1EcmID , const U4 *t_pcu4ConfigTable );
static	void	ErrH_Ecm_AllClearErrorStatus( void );
static	void	ErrH_Ecm_SetIrConfig( const U4 *t_pcu4ConfigTable );
static	void	ErrH_Ecm_SetIrTypeConfig( const U4 *t_pcu4IrtypeConfigTable );
static	void	ErrH_Ecm_SetNotifCoreConfig( const U4 *t_pcu4NotifCoreConfigTable );
static	void	ErrH_Ecm_SetErrOutMaskConfig( const U4 *t_pcu4ConfigTable );
static	U1		ErrH_Ecm_JudgeErrorId( U2 t_u2ErrorID );
static	void	ErrH_Ecm_SetInterruptEnable( U4 t_u4CoreId, const U4 *t_pcu4NotifCoreConfigTable );
// zantei REGCHKは2月末非対応	static	U1		ErrH_Ecm_Compare4ByteMask( volatile const U4 *t_pcu4Address, U4 t_u4ExpectedValue, U4 t_u4Mask );
// zantei REGCHKは2月末非対応	static	void	ErrH_Ecm_Reg_RestoreEcmProt4ByteMask( volatile U4 *t_pu4Address, U4 t_u4ExpectedValue, U4 t_u4Mask );

/*==============================================================================================*/
/* defines / data types / structs / unions	/ macros											*/
/*==============================================================================================*/
/* 初期化処理を実施するCoreNo */
/* 初期化処理を実施するCore ( BSW_CORE_ID_CORE0 / BSW_CORE_ID_CORE1 / BSW_CORE_ID_CORE2 / BSW_CORE_ID_CORE3 ) を指定 */
#define		u4ERRH_ECM_MASTER_CORE_NUM					BSW_CORE_ID_CORE0		/* 初期化実施コア */

/* 割り込み番号定義 */
#define		ERRH_ECM_ID_INTECMMI						(8)					/* ECMエラー割り込み番号 */
#define		ERRH_ECM_ID_INTECMDCLSMI					(9)					/* DCLSエラー割り込み番号 */

/* レジスタのマスク値 */
#define		u2ERRH_ECM_MASK_INTC1_EIC_ENABLE			((U2)0xFF7FU)		/* 割り込み許可 */

/* レジスタの設定値 */
#define		u2ERRH_ECM_INTC1_EIC_DISABLE				( (U2)INTC_EIC_EIMK  * (U2)INTC_EIC_EIMK_DISABLE )	/* 割り込み禁止 */

#define		u1ERRH_ECM_NOTIF_ERR						((U1)0U)			/* 通知対象エラー */
#define		u1ERRH_ECM_NOTIF_ERR_INVALID				((U1)1U)			/* 通知対象外エラー(ユーザーへ通知しない) */

/* ECMレジスタ番号 */
/* u1ERRH_ECM_REG_NO00は冗長となるため非使用 */
#define		u1ERRH_ECM_REG_NO01							((U1)1U)			/* ECMレジスタ番号1 */
#define		u1ERRH_ECM_REG_NO02							((U1)2U)			/* ECMレジスタ番号2 */
#define		u1ERRH_ECM_REG_NO03							((U1)3U)			/* ECMレジスタ番号3 */
#define		u1ERRH_ECM_REG_NO04							((U1)4U)			/* ECMレジスタ番号4 */
#define		u1ERRH_ECM_REG_NO05							((U1)5U)			/* ECMレジスタ番号5 */
#define		u1ERRH_ECM_REG_NO06							((U1)6U)			/* ECMレジスタ番号6 */
#define		u1ERRH_ECM_REG_NO07							((U1)7U)			/* ECMレジスタ番号7 */
#define		u1ERRH_ECM_REG_NO08							((U1)8U)			/* ECMレジスタ番号8 */
#define		u1ERRH_ECM_REG_NO09							((U1)9U)			/* ECMレジスタ番号9 */
#if ( MCU_TYPE_SERIES == MCU_RH850U2A16 )
#define		u1ERRH_ECM_REG_NO09							((U1)9U)			/* ECMレジスタ番号9 */
#define		u1ERRH_ECM_REG_NO10							((U1)10U)			/* ECMレジスタ番号10 */
#endif

#define		u4ERRH_ECM_NO_NOTIF							((U4)0x00000000U)	/* エラー通知無効 */
#define		u4ERRH_ECM_NO_ERR							((U4)0x00000000U)	/* エラーなし */
#define		u4ERRH_ECM_REG_DCLSERR_MASK					((U4)0x00000001U)	/* ECMレジスタ DCLSエラーのビットマスク */
#define		u4ERRH_ECM_REG_DCLSERR_SET					((U4)0x00000001U)	/* ECMレジスタ DCLSエラーのビットセット値 */
#define		u4ERRH_ECM_REG_EXC_DCLSERR_MASK				((U4)0xFFFFFFFEU)	/* ECMレジスタ DCLSエラー以外のビットマスク */
#define		u4ERRH_ECM_REG_NO_MASK						((U4)0xFFFFFFFFU)	/* ECMレジスタ0ビット以外マスク */
#if ( MCU_TYPE_SERIES == MCU_RH850U2A6 )
#define		ERRH_ECM_REG_DCLSCORE_NUM					(2)					/* ECM DCLS対応コア数 */
#define		ERRH_ECM_REG_MASKREG_NUM					(2)					/* ECMレジスタマスク対象数 */
#else	/* MCU_TYPE_SERIES == MCU_RH850U2A16 */
#define		ERRH_ECM_REG_DCLSCORE_NUM					(4)					/* ECM DCLS対応コア数 */
#define		ERRH_ECM_REG_MASKREG_NUM					(4)					/* ECMレジスタマスク対象数 */
#endif
#define		ERRH_ECM_REG_MASK_NO07						(0)					/* ECMレジスタ番号7マスクNo */
#define		ERRH_ECM_REG_MASK_NO08						(1)					/* ECMレジスタ番号8マスクNo */
#if ( MCU_TYPE_SERIES == MCU_RH850U2A16 )
#define		ERRH_ECM_REG_MASK_NO09						(2)					/* ECMレジスタ番号9マスクNo */
#define		ERRH_ECM_REG_MASK_NO10						(3)					/* ECMレジスタ番号10マスクNo */
#endif

/* ECMESSTCn */
#if MCU_TYPE_SERIES == MCU_RH850U2A6
// zantei Reserved以外すべて0クリアしているが、どのエラーをクリアするかは要検討
#define		u4ERRH_ECM_ECMESSTC0_ALLCLEAR				((U4)0x7F10081DU)	/* ECMESSTC0レジスタ全クリア値 */
#define		u4ERRH_ECM_ECMESSTC1_ALLCLEAR				((U4)0x9F3F7F77U)	/* ECMESSTC1レジスタ全クリア値 */
#define		u4ERRH_ECM_ECMESSTC2_ALLCLEAR				((U4)0x070F1101U)	/* ECMESSTC2レジスタ全クリア値 */
#define		u4ERRH_ECM_ECMESSTC3_ALLCLEAR				((U4)0x0F070707U)	/* ECMESSTC3レジスタ全クリア値 */
#define		u4ERRH_ECM_ECMESSTC4_ALLCLEAR				((U4)0x800033FFU)	/* ECMESSTC4レジスタ全クリア値 */
#define		u4ERRH_ECM_ECMESSTC5_ALLCLEAR				((U4)0x03C00F07U)	/* ECMESSTC5レジスタ全クリア値 */
#define		u4ERRH_ECM_ECMESSTC6_ALLCLEAR				((U4)0x00000003U)	/* ECMESSTC6レジスタ全クリア値 */
#define		u4ERRH_ECM_ECMESSTC7_ALLCLEAR				((U4)0x80031739U)	/* ECMESSTC7レジスタ全クリア値 */
#define		u4ERRH_ECM_ECMESSTC8_ALLCLEAR				((U4)0x80031739U)	/* ECMESSTC8レジスタ全クリア値 */
#define		u4ERRH_ECM_ECMESSTC9_ALLCLEAR				((U4)0x00000000U)	/* ECMESSTC9レジスタ全クリア値 */
#define		u4ERRH_ECM_ECMESSTC10_ALLCLEAR				((U4)0x00000000U)	/* ECMESSTC10レジスタ全クリア値 */
#elif MCU_TYPE_SERIES == MCU_RH850U2A16
// zantei Reserved以外すべて0クリアしているが、どのエラーをクリアするかは要検討
#define		u4ERRH_ECM_ECMESSTC0_ALLCLEAR				((U4)0x7F10087DU)	/* ECMESSTC0レジスタ全クリア値 */
#define		u4ERRH_ECM_ECMESSTC1_ALLCLEAR				((U4)0xFF3F7F77U)	/* ECMESSTC1レジスタ全クリア値 */
#define		u4ERRH_ECM_ECMESSTC2_ALLCLEAR				((U4)0x070F1101U)	/* ECMESSTC2レジスタ全クリア値 */
#define		u4ERRH_ECM_ECMESSTC3_ALLCLEAR				((U4)0x0F070707U)	/* ECMESSTC3レジスタ全クリア値 */
#define		u4ERRH_ECM_ECMESSTC4_ALLCLEAR				((U4)0x80003FFFU)	/* ECMESSTC4レジスタ全クリア値 */
#define		u4ERRH_ECM_ECMESSTC5_ALLCLEAR				((U4)0x0FC00F07U)	/* ECMESSTC5レジスタ全クリア値 */
#define		u4ERRH_ECM_ECMESSTC6_ALLCLEAR				((U4)0x0000000FU)	/* ECMESSTC6レジスタ全クリア値 */
#define		u4ERRH_ECM_ECMESSTC7_ALLCLEAR				((U4)0x80031739U)	/* ECMESSTC7レジスタ全クリア値 */
#define		u4ERRH_ECM_ECMESSTC8_ALLCLEAR				((U4)0x80031739U)	/* ECMESSTC8レジスタ全クリア値 */
#define		u4ERRH_ECM_ECMESSTC9_ALLCLEAR				((U4)0x80031739U)	/* ECMESSTC9レジスタ全クリア値 */
#define		u4ERRH_ECM_ECMESSTC10_ALLCLEAR				((U4)0x80031739U)	/* ECMESSTC10レジスタ全クリア値 */
#else
 #error "The microcomputer type(MCU_TYPE_SERIES) is not supported!!"
#endif

#define		u1ERRH_ECM_REGCHECK_STS_COMPLETED			((U1)0U)			/* サブモジュールレジスタ診断開始待ち(内部ステータス) */
#define		u1ERRH_ECM_REGCHECK_STS_BUSY				((U1)1U)			/* サブモジュールレジスタ診断中(内部ステータス) */
#define		u1ERRH_ECM_CHECKRESULT_MASK_UPPER4BIT		((U1)0x0FU)			/* 上位4bitマスク(4～7bit) */
#define		u1ERRH_ECM_REGCHECK_COMPLETED				((U1)0x00U)			/* サブモジュールレジスタ診断開始待ち */
#define		u1ERRH_ECM_REGCHECK_BUSY					((U1)0x10U)			/* サブモジュールレジスタ診断中 */

/*==============================================================================================*/
/* constants																					*/
/*==============================================================================================*/
#pragma ghs section rodata=".ERRH_RODATA_CONST"
#if ( MCU_TYPE_SERIES == MCU_RH850U2A6 )
static volatile U4 const cu4ErrH_Ecm_RegMaskTable[ERRH_ECM_REG_DCLSCORE_NUM][ERRH_ECM_REG_MASKREG_NUM] = 
{  /* ECM_REG_NO07 */					/* ECM_REG_NO08 */					
	{ u4ERRH_ECM_REG_EXC_DCLSERR_MASK,	u4ERRH_ECM_REG_NO_MASK			},	/* Core0 */
	{ u4ERRH_ECM_REG_NO_MASK,			u4ERRH_ECM_REG_EXC_DCLSERR_MASK	}	/* Core1 */
};
#elif ( MCU_TYPE_SERIES == MCU_RH850U2A16 )
static volatile U4 const cu4ErrH_Ecm_RegMaskTable[ERRH_ECM_REG_DCLSCORE_NUM][ERRH_ECM_REG_MASKREG_NUM] = 
{  /* ECM_REG_NO07 */					/* ECM_REG_NO08 */					/* ECM_REG_NO09 */					/* ECM_REG_NO10 */	
	{ u4ERRH_ECM_REG_EXC_DCLSERR_MASK,	u4ERRH_ECM_REG_NO_MASK,				u4ERRH_ECM_REG_NO_MASK,				u4ERRH_ECM_REG_NO_MASK			},	/* Core0 */
	{ u4ERRH_ECM_REG_NO_MASK,			u4ERRH_ECM_REG_EXC_DCLSERR_MASK,	u4ERRH_ECM_REG_NO_MASK,				u4ERRH_ECM_REG_NO_MASK			},	/* Core1 */
	{ u4ERRH_ECM_REG_NO_MASK,			u4ERRH_ECM_REG_NO_MASK,				u4ERRH_ECM_REG_EXC_DCLSERR_MASK,	u4ERRH_ECM_REG_NO_MASK			},	/* Core2 */
	{ u4ERRH_ECM_REG_NO_MASK,			u4ERRH_ECM_REG_NO_MASK,				u4ERRH_ECM_REG_NO_MASK,				u4ERRH_ECM_REG_EXC_DCLSERR_MASK	}	/* Core3 */
};
#else
 #error "The microcomputer grade(MCU_GRADE) is not supported!!"
#endif
#pragma ghs section rodata=default

/*==============================================================================================*/
/* variables																					*/
/*==============================================================================================*/
#pragma ghs section bss=".ERRH_BSS_VAR_NO_INIT"
// zantei REGCHKは2月末非対応	static				U2		s_u2ErrH_Ecm_RegCheckNum;		/* レジスタ診断番号 */ /* 干渉対策のため、ErrH_Ecm_CheckReg_ASIL()のみからライトすること */
// zantei REGCHKは2月末非対応	static	volatile	U1		s_u1ErrH_Ecm_RegCheckStatus;	/* レジスタ診断ステータス */ /* 干渉対策のため、ErrH_Ecm_CheckReg_ASIL()のみからライトすること */
#pragma ghs section bss=default

/*==============================================================================================*/
/* functions																					*/
/*==============================================================================================*/
#pragma ghs section text=".ERRH_TEXT_CODE"
/*----------------------------------------------------------------------------------------------*/
/* API Functions																				*/
/*----------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------*/
/* Clear Error Status Function																	*/
/* Return		: none																			*/
/* Parameters	: ErrorID																		*/
/*----------------------------------------------------------------------------------------------*/
void	ErrH_Ecm_ClearErrorStatus( U2 t_u2ErrorID )
{
	U1							t_u1RegNo;			/* レジスタNo */
	U2							t_u2BitPos;			/* エラーID */
	U4							t_u4ClearData;		/* クリア対象エラーIDデータ */

	t_u1RegNo = (U1)0U;			/* レジスタNo 初期化 */
	t_u2BitPos = t_u2ErrorID;	/* エラーIDコピー */

	while ( t_u2BitPos >= (U2)ERRH_ECM_ERROR_ID_REG_NUM )
	{
		t_u2BitPos = t_u2BitPos - (U2)ERRH_ECM_ERROR_ID_REG_NUM;
		t_u1RegNo = t_u1RegNo + (U1)1U;	/* レジスタNo インクリメント */
	}

	t_u4ClearData = (U4)( (U4)1U << t_u2BitPos );

	DI_ALL();	/* マスタ側のみ実施するため、DI_ALLのみで対応可能 */

	/* ECMKCPROT - ECM キーコード保護レジスタ 保護解除 */
	REG_ECM.unECMKCPROT.u4Data = (U4)ECM_ECMKCPROT_KCE_ENABLE;

	/* ECMESSTR - ECMエラーソースステータスクリアトリガレジスタ エラークリア */
	REG_ECM.unECMESSTCn.u4Data[t_u1RegNo] = t_u4ClearData;

	/* ECMKCPROT - ECM キーコード保護レジスタ 保護設定 */
	REG_ECM.unECMKCPROT.u4Data = (U4)ECM_ECMKCPROT_KCE_DISABLE;

	/* ダミーリード */
	Bswlib_Sync_Pipeline_4( REG_ECM.unECMKCPROT.u4Data );

	EI_ALL();	/* マスタ側のみ実施するため、EI_ALLのみで対応可能 */

}

#if 0 // zantei REGCHKは2月末非対応
/*----------------------------------------------------------------------------------------------*/
/*	Request Register Check Function																*/
/*	return		: Register Check Result															*/
/*	parameters	: *ConfigTable																	*/
/*----------------------------------------------------------------------------------------------*/
U1	ErrH_Ecm_CheckReg_ASIL( const ErrH_RegCheckConfigType *t_pcstConfigTable )
{
	volatile	void*							t_pvdAddress;		/* レジスタアドレス */
				U4								t_u4ExpectValue;	/* レジスタ期待値 */
				U4								t_u4Mask;			/* レジスタマスク */
				U2								t_u2RegCheckNum;	/* レジスタ診断番号 */
				U1								t_u1Result;			/* 戻り値 */

	t_u1Result = (U1)OK;											/* OKで初期化 */

	if ( s_u1ErrH_Ecm_RegCheckStatus == u1ERRH_ECM_REGCHECK_STS_COMPLETED )
	{
		s_u1ErrH_Ecm_RegCheckStatus = u1ERRH_ECM_REGCHECK_STS_BUSY;
		s_u2ErrH_Ecm_RegCheckNum = (U2)0U;							/* レジスタ診断番号初期化 */
	}

	t_u2RegCheckNum = s_u2ErrH_Ecm_RegCheckNum;																	/* 現在の診断番号を取得 */

	if ( t_u2RegCheckNum < t_pcstConfigTable->u2RegNum )														/* レジスタ診断テーブルサイズより小さい場合 */
	{
		t_pvdAddress = t_pcstConfigTable->pcstRegData[ t_u2RegCheckNum ].pvdAddress;
		t_u4ExpectValue = t_pcstConfigTable->pcstRegData[ t_u2RegCheckNum ].u4ExpectValue;
		t_u4Mask = t_pcstConfigTable->pcstRegData[ t_u2RegCheckNum ].u4Mask;
		
		t_u1Result = ErrH_Ecm_Compare4ByteMask( (volatile const U4*)t_pvdAddress, t_u4ExpectValue, t_u4Mask );
		
		if ( t_u1Result == (U1)NG )
		{
			ErrH_Ecm_Reg_RestoreEcmProt4ByteMask( (volatile U4*)t_pvdAddress, t_u4ExpectValue, t_u4Mask );
		}

		t_u2RegCheckNum++;
		s_u2ErrH_Ecm_RegCheckNum = t_u2RegCheckNum;

		if ( s_u2ErrH_Ecm_RegCheckNum < t_pcstConfigTable->u2RegNum )												/* レジスタ診断テーブルサイズより小さい場合 */
		{
			t_u1Result = t_u1Result | u1ERRH_ECM_REGCHECK_BUSY;														/* 4～7bit目にサブモジュールレジスタ診断中(0001B)をセット(本処理前は4～7bit目として0000Bを期待) */
		}
		else
		{
			/* t_u1Resultの4～7bit目にサブモジュールレジスタ診断開始待ち(0000B)をセット(本処理前は4～7bit目として0000Bを期待)。冗長となるため、処理なし */
			s_u1ErrH_Ecm_RegCheckStatus = u1ERRH_ECM_REGCHECK_STS_COMPLETED;
		}
	}
	else
	{
		t_u1Result = ( t_u1Result & u1ERRH_ECM_CHECKRESULT_MASK_UPPER4BIT ) | u1ERRH_ECM_REGCHECK_COMPLETED;		/* 4～7bit目に0000B(診断開始待ち)をセット */
		s_u1ErrH_Ecm_RegCheckStatus = u1ERRH_ECM_REGCHECK_STS_COMPLETED;
	}

	return( t_u1Result );
}
#endif // zantei REGCHKは2月末非対応

/*----------------------------------------------------------------------------------------------*/
/* Scheduled / Event Functions																	*/
/*----------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------*/
/* Alarm Interrupt Function																		*/
/* Return		: none																			*/
/* Parameters	: *ConfigTable																	*/
/*----------------------------------------------------------------------------------------------*/
void	ErrH_Ecm_AlarmInterrupt( const U4 *t_pcu4ConfigTable )
{
	U4							t_u4CoreId;			/* コアID						*/
	U2							t_u2ErrorID;		/* エラーID						*/
	U1							t_u1JudgeResult;	/* 通知対象エラー判定結果		*/

	t_u4CoreId = Bswlib_GetCoreId();
	
	/* 全てのECMエラーがなくなるまで繰り返す。 */
	while(1)
	{
		/* 引数として初期化時通知/通知先コアコンフィグレーションテーブル(コア毎の先頭アドレス)を設定  */
		t_u2ErrorID = ErrH_Ecm_GetErrorId( (U1)ERRH_ECM_MASTER, &t_pcu4ConfigTable[t_u4CoreId * (U4)ERRH_ECM_CONFIG_REG_NUM] );	/* qac 3383 : t_u4CoreIdの値によってラップアラウンドが発生しないことを確認済み。QAC結果は過剰警告 */

		/* エラーIDが初期値（エラーなし）の場合には終了 */
		if ( t_u2ErrorID == (U2)ERRH_ERROR_ID_NORMAL )
		{
			break;
		}
		else
		{
			t_u1JudgeResult = ErrH_Ecm_JudgeErrorId( t_u2ErrorID );

			if ( t_u1JudgeResult == u1ERRH_ECM_NOTIF_ERR )
			{
				/* エラー消去 */
				ErrH_Ecm_ClearErrorStatus( t_u2ErrorID );
				/* ECMエラーIDを通知する */
				ErrH_AlarmInterruptCallout( t_u2ErrorID );
			}
		}
	}
}

/*----------------------------------------------------------------------------------------------*/
/* ErrH Ecm Before Init Function																*/
/* Return		: none																			*/
/*				: *ConfigTable																	*/
/*----------------------------------------------------------------------------------------------*/
void	ErrH_Ecm_PreInit( U4 t_u4CoreId, const U4 *t_pcu4ConfigTable )
{

	/* 初期化処理を実施するCoreの場合 */
	if ( t_u4CoreId == u4ERRH_ECM_MASTER_CORE_NUM )
	{
		/* エラー情報の通知																 */
		/*	全クリア前に、Fatalエラーが発生している可能性があるため						 */
		/*	ECMエラー情報を確認し、必要があれば機能安全に通知する						 */
		ErrH_Ecm_AlarmInterrupt( t_pcu4ConfigTable );
	}
	else	/* 初期化処理を実施するCoreの場合 */
	{
			/* 処理なし */
	}
}

/*----------------------------------------------------------------------------------------------*/
/* ErrH Ecm Init Function																		*/
/* Return		: none																			*/
/* Parameters	: CoreID																		*/
/*				: *ConfigData																	*/
/*----------------------------------------------------------------------------------------------*/
void	ErrH_Ecm_Init( U4 t_u4CoreId, const ErrH_UserConfigType *t_pcstConfigData )
{
	/* 初期化処理を実施するCoreの場合 */
	if ( t_u4CoreId == u4ERRH_ECM_MASTER_CORE_NUM )
	{
		/* 通知しないECMエラーをクリアする												 */
		ErrH_Ecm_AllClearErrorStatus();

		/* ソフトとして、動作が停止してしまうレジスタから設定する						 */
		/*  レジスタ設定（内部リセットコンフィグレーション）							 */
		/*	ECMIRCFGレジスタに設定														 */
		ErrH_Ecm_SetIrConfig( t_pcstConfigData->pcu4IrCfg );				/* Ir Config */

		/*  レジスタ設定（割り込みタイプ）												 */
		/*	ECMISCFGレジスタに設定														 */
		ErrH_Ecm_SetIrTypeConfig( t_pcstConfigData->pcu4IrTypeCfg );	/* IrType Config */

		/*  レジスタ設定（通知先コア）													 */
		/*	ECMINCFGレジスタに設定														 */
		ErrH_Ecm_SetNotifCoreConfig( t_pcstConfigData->pcu4NotifCoreCfg );	/* NotifCore Config */

		/*  レジスタ設定（エラーマスク）												 */
		/*	ECMEMKレジスタに設定														 */
		ErrH_Ecm_SetErrOutMaskConfig( t_pcstConfigData->pcu4EoutCfg );	  /* EOUT Config */

		/*  エラートリガマスクコンフィグ												 */
		/*	ECMETMKnレジスタに設定														 */
		/*	エラートリガ未使用のため処理なし(初期値はエラートリガ無効)					 */

		/*  エラーパルスコンフィグ														 */
		/*	ECMEPCFGレジスタに設定														 */
		/*	ERROROUT未使用のため処理なし												 */

		/*  DelayTimer停止																 */
		/*	ECMDTMCTLレジスタに設定														 */
		/*	ERROROUT未使用であり、初期値がDelayTimer停止のため処理なし					 */

		/*  DelayTimerコンペア値設定													 */
		/*	ECMDTMCMPレジスタに設定														 */
		/*	ERROROUT未使用であり、DelayTimerを使用しないため処理なし					 */

		/*  ディレイタイマ設定															 */
		/*	ECMDTMCFGレジスタに設定														 */
		/*	ERROROUT未使用であり、DelayTimerを使用しないため処理なし					 */
	}
	
	/*  ECMエラー/DCLSエラー割り込み設定												 */
	/*	機能安全にErrorIDを通知するCoreは割り込みを使用するため							 */
	/*	割り込みを有効化する。															 */
	/*	機能安全にErrorIDを通知しないCoreは割り込み未使用のため							 */
	/*	割り込みをマスクする。															 */
	ErrH_Ecm_SetInterruptEnable( t_u4CoreId, t_pcstConfigData->pcu4NotifCoreCfg );
}

/*----------------------------------------------------------------------------------------------*/
/* Local Functions																				*/
/*----------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------*/
/* Get Error ID Function																		*/
/* Return		: ErrorID																		*/
/* Parameters	: EcmID( MASTER / CHECKER )														*/
/*				: *ConfigTable																	*/
/*----------------------------------------------------------------------------------------------*/
static	U2	ErrH_Ecm_GetErrorId( U1 t_u1EcmID , const U4 *t_pcu4ConfigTable )
{
	volatile Reg_Ecm_EcmmType*	t_pstRegEcm;		/* 確認対象レジスタ				 */
	S4							i, j;				/* ループ変数					 */
	U4							t_u4RegData;		/* 確認対象レジスタ値			 */
	U4							t_u4Mask;			/* エラー発生有無確認対象ビット	 */
	U2							t_u2ErrorID;		/* 戻り値格納変数				 */

	t_u2ErrorID = (U2)ERRH_ERROR_ID_NORMAL;	/* エラーID 正常で初期化 */

	if ( t_u1EcmID == (U1)ERRH_ECM_MASTER )	/* マスタレジスタ */
	{
		t_pstRegEcm = &REG_ECMM;
	}
	else	/* チェッカレジスタ */
	{
		t_pstRegEcm = &REG_ECMC;
	}

	/* エラーステータスレジスタを確認し、エラー発生状態を抽出する */
	for ( i = (S4)0; i < (S4)ERRH_ECM_CONFIG_REG_NUM; i++ )
	{
		/* ECMエラーIDの通知有無を変数に格納する */
		t_u4RegData = t_pstRegEcm->unECMESSTRn.u4Data[i] & t_pcu4ConfigTable[i];
		for ( j = (S4)0; j < (S4)ERRH_ECM_ERROR_ID_REG_NUM; j++ )
		{
			t_u4Mask = (U4)( (U4)1U << (U4)j );
			/* ECMエラーが発生していた場合、ECMエラーIDを戻り値に格納する */
			if ( (U4)( t_u4RegData & t_u4Mask ) != u4ERRH_ECM_NO_ERR )
			{
				t_u2ErrorID = (U2)j + (U2)i * (U2)ERRH_ECM_ERROR_ID_REG_NUM;
				break;
			}
		}
		if ( t_u2ErrorID != (U2)ERRH_ERROR_ID_NORMAL )
		{
			break;
		}
	}

	return ( t_u2ErrorID );
}

/*----------------------------------------------------------------------------------------------*/
/* All Clear Error Status Function																*/
/* Return		: none																			*/
/* Parameters	: none																			*/
/*----------------------------------------------------------------------------------------------*/
static	void	ErrH_Ecm_AllClearErrorStatus( void )
{
	/* ECMKCPROT - ECM キーコード保護レジスタ 保護解除 */
	REG_ECM.unECMKCPROT.u4Data = (U4)ECM_ECMKCPROT_KCE_ENABLE;

	/* ECMESSTCn - ECM エラーソースステータスクリアトリガレジスタn エラークリア */
	REG_ECM.unECMESSTCn.stECMESSTCn.unECMESSTC0.u4Data = u4ERRH_ECM_ECMESSTC0_ALLCLEAR;
	REG_ECM.unECMESSTCn.stECMESSTCn.unECMESSTC1.u4Data = u4ERRH_ECM_ECMESSTC1_ALLCLEAR;
	REG_ECM.unECMESSTCn.stECMESSTCn.unECMESSTC2.u4Data = u4ERRH_ECM_ECMESSTC2_ALLCLEAR;
	REG_ECM.unECMESSTCn.stECMESSTCn.unECMESSTC3.u4Data = u4ERRH_ECM_ECMESSTC3_ALLCLEAR;
	REG_ECM.unECMESSTCn.stECMESSTCn.unECMESSTC4.u4Data = u4ERRH_ECM_ECMESSTC4_ALLCLEAR;
	REG_ECM.unECMESSTCn.stECMESSTCn.unECMESSTC5.u4Data = u4ERRH_ECM_ECMESSTC5_ALLCLEAR;
	REG_ECM.unECMESSTCn.stECMESSTCn.unECMESSTC6.u4Data = u4ERRH_ECM_ECMESSTC6_ALLCLEAR;
	REG_ECM.unECMESSTCn.stECMESSTCn.unECMESSTC7.u4Data = u4ERRH_ECM_ECMESSTC7_ALLCLEAR;
	REG_ECM.unECMESSTCn.stECMESSTCn.unECMESSTC8.u4Data = u4ERRH_ECM_ECMESSTC8_ALLCLEAR;
#if ( MCU_TYPE_SERIES == MCU_RH850U2A16 )
	REG_ECM.unECMESSTCn.stECMESSTCn.unECMESSTC9.u4Data = u4ERRH_ECM_ECMESSTC9_ALLCLEAR;
	REG_ECM.unECMESSTCn.stECMESSTCn.unECMESSTC10.u4Data = u4ERRH_ECM_ECMESSTC10_ALLCLEAR;
#endif

	/* ECMKCPROT - ECM キーコード保護レジスタ 保護設定 */
	REG_ECM.unECMKCPROT.u4Data = (U4)ECM_ECMKCPROT_KCE_DISABLE;

	/* ダミーリード */
	Bswlib_Sync_Pipeline_4( REG_ECM.unECMKCPROT.u4Data );
}

/*----------------------------------------------------------------------------------------------*/
/* Set Internal Reset Config Function															*/
/* Return		: none																			*/
/* Parameters	: *ConfigTable																	*/
/*----------------------------------------------------------------------------------------------*/
static	void	ErrH_Ecm_SetIrConfig( const U4 *t_pcu4ConfigTable )
{
	S4							i;					/* ループ変数					 */

	/* ECMKCPROT - ECM キーコード保護レジスタ 保護解除 */
	REG_ECM.unECMKCPROT.u4Data = (U4)ECM_ECMKCPROT_KCE_ENABLE;

	for ( i = (S4)0; i < (S4)ERRH_ECM_CONFIG_REG_NUM; i++ )
	{
		/* Set Config Data */
		REG_ECM.unECMIRCFGn.u4Data[i] = t_pcu4ConfigTable[i];
	}

	/* ECMKCPROT - ECM キーコード保護レジスタ 保護設定 */
	REG_ECM.unECMKCPROT.u4Data = (U4)ECM_ECMKCPROT_KCE_DISABLE;

	/* ダミーリード */
	Bswlib_Sync_Pipeline_4( REG_ECM.unECMKCPROT.u4Data );
}

/*----------------------------------------------------------------------------------------------*/
/* Set Interrupt type Config Function															*/
/* Return		: none																			*/
/* Parameters	: *ConfigTable(IrType)															*/
/*----------------------------------------------------------------------------------------------*/
static	void	ErrH_Ecm_SetIrTypeConfig( const U4 *t_pcu4IrtypeConfigTable )
{
	S4							i;					/* ループ変数					 */

	/* ECMKCPROT - ECM キーコード保護レジスタ 保護解除 */
	REG_ECM.unECMKCPROT.u4Data = (U4)ECM_ECMKCPROT_KCE_ENABLE;

	for ( i = (S4)0; i < (S4)ERRH_ECM_CONFIG_REG_NUM; i++ )
	{
		/* Set Config Data */
		REG_ECM.unECMISCFGn.u4Data[i] = t_pcu4IrtypeConfigTable[i];
	}

	/* ECMKCPROT - ECM キーコード保護レジスタ 保護設定 */
	REG_ECM.unECMKCPROT.u4Data = (U4)ECM_ECMKCPROT_KCE_DISABLE;

	/* ダミーリード */
	Bswlib_Sync_Pipeline_4( REG_ECM.unECMKCPROT.u4Data );
}

/*----------------------------------------------------------------------------------------------*/
/* Set Notification Core Config Function														*/
/* Return		: none																			*/
/* Parameters	: *ConfigTable(Notif Core)														*/
/*----------------------------------------------------------------------------------------------*/
static	void	ErrH_Ecm_SetNotifCoreConfig( const U4 *t_pcu4NotifCoreConfigTable )
{
	S4							i;					/* ループ変数					 */

	/* ECMKCPROT - ECM キーコード保護レジスタ 保護解除 */
	REG_ECM.unECMKCPROT.u4Data = (U4)ECM_ECMKCPROT_KCE_ENABLE;

	for ( i = (S4)0; i < (S4)ERRH_ECM_CONFIG_REG_NUM; i++ )
	{
		/* Set Config Data */
		REG_ECM.unECMINCFG0_n.u4Data[i] = t_pcu4NotifCoreConfigTable[i];	/* BSW_CORE_ID_CORE0の値は'0'であることから、冗長な演算となるためオフセット加算処理を省略している */
		REG_ECM.unECMINCFG1_n.u4Data[i] = t_pcu4NotifCoreConfigTable[i + (S4)( (S4)BSW_CORE_ID_CORE1 * (S4)ERRH_ECM_CONFIG_REG_NUM )];
#if ( MCU_TYPE_SERIES == MCU_RH850U2A16 )
		REG_ECM.unECMINCFG2_n.u4Data[i] = t_pcu4NotifCoreConfigTable[i + (S4)( (S4)BSW_CORE_ID_CORE2 * (S4)ERRH_ECM_CONFIG_REG_NUM )];
		REG_ECM.unECMINCFG3_n.u4Data[i] = t_pcu4NotifCoreConfigTable[i + (S4)( (S4)BSW_CORE_ID_CORE3 * (S4)ERRH_ECM_CONFIG_REG_NUM )];
#else /* U2A6  */
		REG_ECM.unECMINCFG2_n.u4Data[i] = u4ERRH_ECM_NO_NOTIF;				/* マイコン初期値(エラー通知無効)を設定 */
		REG_ECM.unECMINCFG3_n.u4Data[i] = u4ERRH_ECM_NO_NOTIF;				/* マイコン初期値(エラー通知無効)を設定 */
#endif
	}

	/* ECMKCPROT - ECM キーコード保護レジスタ 保護設定 */
	REG_ECM.unECMKCPROT.u4Data = (U4)ECM_ECMKCPROT_KCE_DISABLE;

	/* ダミーリード */
	Bswlib_Sync_Pipeline_4( REG_ECM.unECMKCPROT.u4Data );
}

/*----------------------------------------------------------------------------------------------*/
/* Set Error Mask Config Function																*/
/* Return		: none																			*/
/* Parameters	: *ConfigTable																	*/
/*----------------------------------------------------------------------------------------------*/
static	void	ErrH_Ecm_SetErrOutMaskConfig( const U4 *t_pcu4ConfigTable )
{
	S4							i;					/* ループ変数					 */

	/* ECMKCPROT - ECM キーコード保護レジスタ 保護解除 */
	REG_ECM.unECMKCPROT.u4Data = (U4)ECM_ECMKCPROT_KCE_ENABLE;

	for ( i = (S4)0; i < (S4)ERRH_ECM_CONFIG_REG_NUM; i++ )
	{
		/* Set Config Data */
		REG_ECM.unECMEMKn.u4Data[i] = t_pcu4ConfigTable[i];
	}

	/* ECMKCPROT - ECM キーコード保護レジスタ 保護設定 */
	REG_ECM.unECMKCPROT.u4Data = (U4)ECM_ECMKCPROT_KCE_DISABLE;

	/* ダミーリード */
	Bswlib_Sync_Pipeline_4( REG_ECM.unECMKCPROT.u4Data );
}

/*----------------------------------------------------------------------------------------------*/
/* Judge Error ID Function																		*/
/* Return		: Judgement Result																*/
/* Parameters	: ErrorID																		*/
/*----------------------------------------------------------------------------------------------*/
static	U1	ErrH_Ecm_JudgeErrorId( U2 t_u2ErrorID )
{
// zantei ECCは2月末非対応	volatile Reg_Ecm_EcmmType*	t_pstRegEcm;		/* 確認対象モジュール			 */
// zantei ECCは2月末非対応	S4							i;					/* ループ変数					 */
// zantei ECCは2月末非対応	U4							t_u4RegData;		/* 確認対象レジスタ値			 */
	U1							t_u1JudgeResult;	/* 通知対象エラー判定結果		 */
	
#if 0 // zantei ECCは2月末非対応
	/* 検出したエラー要因IDが162(HBnECC データECC1bitエラー)の場合 */
	if( t_u2ErrorID == u2ERRH_NCF162_ID )
	{
		/* ECMエラー消去 */
		ErrH_Ecm_ClearErrorStatus( t_u2ErrorID );

		t_pstRegEcm = &REG_ECMM;
		
		/* HBnECC アドレスEDC エラー、ECC 2ビットエラー発生有無を確認 */
		/* エラー要因ID：160、161発生時は、エラー詳細情報を消去しない */
		t_u4RegData = (U4)(t_pstRegEcm->unECMESSTRn.u4Data[u1ERRH_ECM_REG_NO05] & ( (U4)BIT0 + (U4)BIT1 ) );
		if( t_u4RegData == u4ERRH_ECM_NO_ERR )
		{
			/* HBnECCは、データ、アドレスのECC 2bit、1bitエラーをクリアする(ハード仕様)  */
			for ( i = (S4)u1ERRH_ECC_DTP_HB90MECC_ADDR; i <= (S4)u1ERRH_ECC_DTP_HB912MECC_ADDR; i++ )
			{
				/* ECCエラー消去										   */
				/* HBnECCのデータエラー指定にて、ECC1bitエラーをクリアする */
				/* エラー要因IDでは、Bus特定不可のため全クリアする		   */
				ErrH_Ecc_ClearEcc1bitErr( (U1)i );
			}
		}
		t_u1JudgeResult = u1ERRH_ECM_NOTIF_ERR_INVALID;	/* 通知対象外エラー */
	}
	else
#endif // zantei ECCは2月末非対応
	{
		t_u1JudgeResult = u1ERRH_ECM_NOTIF_ERR;			/* 通知対象エラー */
	}
	
	return( t_u1JudgeResult );
}

/*----------------------------------------------------------------------------------------------*/
/* Set Interrupt Enable Function																*/
/* Return		: none																			*/
/* Parameters	: CoreID																		*/
/* 				: *ConfigTable(Notif Core)														*/
/*----------------------------------------------------------------------------------------------*/
static	void	ErrH_Ecm_SetInterruptEnable( U4 t_u4CoreId, const U4 *t_pcu4NotifCoreConfigTable )
{
	U4							t_u4ConfigValue;		/* コンフィグ値		 */
	U2							t_u2RegData;			/* 確認対象レジスタ値		 */

	/* 自コアDCLSコンペアエラーの通知先が自コア？ */
	if ( ( t_pcu4NotifCoreConfigTable[u1ERRH_ECM_REG_NO07 + (U1)t_u4CoreId + (U1)( t_u4CoreId * (U4)ERRH_ECM_CONFIG_REG_NUM )] & u4ERRH_ECM_REG_DCLSERR_MASK ) ==  u4ERRH_ECM_REG_DCLSERR_SET )	/* qac 3383 : t_u4CoreIdの値によってラップアラウンドが発生しないことを確認済み。QAC結果は過剰警告 */
	{
		t_u2RegData = Reg_INTC1SELF.unEIC[ERRH_ECM_ID_INTECMDCLSMI].u2Data & u2ERRH_ECM_MASK_INTC1_EIC_ENABLE;
		Reg_INTC1SELF.unEIC[ERRH_ECM_ID_INTECMDCLSMI].u2Data  = t_u2RegData;

		/* ダミーリード */
		Bswlib_Sync_Pipeline_2( Reg_INTC1SELF.unEIC[ERRH_ECM_ID_INTECMDCLSMI].u2Data );
	}
	else
	{
		t_u2RegData = Reg_INTC1SELF.unEIC[ERRH_ECM_ID_INTECMDCLSMI].u2Data | u2ERRH_ECM_INTC1_EIC_DISABLE;
		Reg_INTC1SELF.unEIC[ERRH_ECM_ID_INTECMDCLSMI].u2Data  = t_u2RegData;

		/* ダミーリード */
		Bswlib_Sync_Pipeline_2( Reg_INTC1SELF.unEIC[ERRH_ECM_ID_INTECMDCLSMI].u2Data );
	}

		t_u4ConfigValue = t_pcu4NotifCoreConfigTable[(U1)( t_u4CoreId * (U4)ERRH_ECM_CONFIG_REG_NUM )];							/* u1ERRH_ECM_REG_NO00は'0'であり、冗長なコードとなるため省略 */	/* qac 3383 : t_u4CoreIdの値によってラップアラウンドが発生しないことを確認済み。QAC結果は過剰警告 */
		t_u4ConfigValue |= t_pcu4NotifCoreConfigTable[u1ERRH_ECM_REG_NO01 + (U1)( t_u4CoreId * (U4)ERRH_ECM_CONFIG_REG_NUM )];	/* qac 3383 : t_u4CoreIdの値によってラップアラウンドが発生しないことを確認済み。QAC結果は過剰警告 */
		t_u4ConfigValue |= t_pcu4NotifCoreConfigTable[u1ERRH_ECM_REG_NO02 + (U1)( t_u4CoreId * (U4)ERRH_ECM_CONFIG_REG_NUM )];	/* qac 3383 : t_u4CoreIdの値によってラップアラウンドが発生しないことを確認済み。QAC結果は過剰警告 */
		t_u4ConfigValue |= t_pcu4NotifCoreConfigTable[u1ERRH_ECM_REG_NO03 + (U1)( t_u4CoreId * (U4)ERRH_ECM_CONFIG_REG_NUM )];	/* qac 3383 : t_u4CoreIdの値によってラップアラウンドが発生しないことを確認済み。QAC結果は過剰警告 */
		t_u4ConfigValue |= t_pcu4NotifCoreConfigTable[u1ERRH_ECM_REG_NO04 + (U1)( t_u4CoreId * (U4)ERRH_ECM_CONFIG_REG_NUM )];	/* qac 3383 : t_u4CoreIdの値によってラップアラウンドが発生しないことを確認済み。QAC結果は過剰警告 */
		t_u4ConfigValue |= t_pcu4NotifCoreConfigTable[u1ERRH_ECM_REG_NO05 + (U1)( t_u4CoreId * (U4)ERRH_ECM_CONFIG_REG_NUM )];	/* qac 3383 : t_u4CoreIdの値によってラップアラウンドが発生しないことを確認済み。QAC結果は過剰警告 */
		t_u4ConfigValue |= t_pcu4NotifCoreConfigTable[u1ERRH_ECM_REG_NO06 + (U1)( t_u4CoreId * (U4)ERRH_ECM_CONFIG_REG_NUM )];	/* qac 3383 : t_u4CoreIdの値によってラップアラウンドが発生しないことを確認済み。QAC結果は過剰警告 */
		t_u4ConfigValue |= ( t_pcu4NotifCoreConfigTable[u1ERRH_ECM_REG_NO07 + (U1)( t_u4CoreId * (U4)ERRH_ECM_CONFIG_REG_NUM )] & cu4ErrH_Ecm_RegMaskTable[t_u4CoreId][ERRH_ECM_REG_MASK_NO07] );	/* qac 3383 : t_u4CoreIdの値によってラップアラウンドが発生しないことを確認済み。QAC結果は過剰警告 */
		t_u4ConfigValue |= ( t_pcu4NotifCoreConfigTable[u1ERRH_ECM_REG_NO08 + (U1)( t_u4CoreId * (U4)ERRH_ECM_CONFIG_REG_NUM )] & cu4ErrH_Ecm_RegMaskTable[t_u4CoreId][ERRH_ECM_REG_MASK_NO08] );	/* qac 3383 : t_u4CoreIdの値によってラップアラウンドが発生しないことを確認済み。QAC結果は過剰警告 */
#if ( MCU_TYPE_SERIES == MCU_RH850U2A16 )
		t_u4ConfigValue |= ( t_pcu4NotifCoreConfigTable[u1ERRH_ECM_REG_NO09 + (U1)( t_u4CoreId * (U4)ERRH_ECM_CONFIG_REG_NUM )] & cu4ErrH_Ecm_RegMaskTable[t_u4CoreId][ERRH_ECM_REG_MASK_NO09] );	/* qac 3383 : t_u4CoreIdの値によってラップアラウンドが発生しないことを確認済み。QAC結果は過剰警告 */
		t_u4ConfigValue |= ( t_pcu4NotifCoreConfigTable[u1ERRH_ECM_REG_NO10 + (U1)( t_u4CoreId * (U4)ERRH_ECM_CONFIG_REG_NUM )] & cu4ErrH_Ecm_RegMaskTable[t_u4CoreId][ERRH_ECM_REG_MASK_NO10] );	/* qac 3383 : t_u4CoreIdの値によってラップアラウンドが発生しないことを確認済み。QAC結果は過剰警告 */
#endif

	/* 自コアDCLSコンペアエラー以外のエラーの通知先が自コア？ */
	if ( t_u4ConfigValue != u4ERRH_ECM_NO_NOTIF )
	{
		t_u2RegData = Reg_INTC1SELF.unEIC[ERRH_ECM_ID_INTECMMI].u2Data & u2ERRH_ECM_MASK_INTC1_EIC_ENABLE;
		Reg_INTC1SELF.unEIC[ERRH_ECM_ID_INTECMMI].u2Data  = t_u2RegData;

		/* ダミーリード */
		Bswlib_Sync_Pipeline_2( Reg_INTC1SELF.unEIC[ERRH_ECM_ID_INTECMMI].u2Data );
	}
	else
	{
		t_u2RegData = Reg_INTC1SELF.unEIC[ERRH_ECM_ID_INTECMMI].u2Data | u2ERRH_ECM_INTC1_EIC_DISABLE;
		Reg_INTC1SELF.unEIC[ERRH_ECM_ID_INTECMMI].u2Data  = t_u2RegData;

		/* ダミーリード */
		Bswlib_Sync_Pipeline_2( Reg_INTC1SELF.unEIC[ERRH_ECM_ID_INTECMMI].u2Data );
	}
}

#if 0 // zantei REGCHKは2月末非対応
/*----------------------------------------------------------------------------------------------*/
/* General compare 4 byte register with mask Function											*/
/* return		: Register Check Result															*/
/* parameters	: Address(Sync)																	*/
/*				: Expected value																*/
/*				: Mask(0xXXXXXXXX <0:no compare / 1:compare>)									*/
/*----------------------------------------------------------------------------------------------*/
static U1		ErrH_Ecm_Compare4ByteMask( volatile const U4 *t_pcu4Address, U4 t_u4ExpectedValue, U4 t_u4Mask )
{
	U4							t_u4Exp;
	U1							t_u1Result;				/* 戻り値 */

	t_u1Result = (U1)OK;
	
	t_u4Exp = t_u4ExpectedValue & t_u4Mask;
	
	if ( ( *t_pcu4Address & t_u4Mask ) != t_u4Exp )
	{
		t_u1Result = (U1)NG;
	}

	return ( t_u1Result );
}

/*----------------------------------------------------------------------------------------------*/
/* ECM restore 4 byte register with mask Function (ECM Protection Release)						*/
/* return		: none																			*/
/* parameters	: Address(Sync)																	*/
/*				: Expected value																*/
/*				: Mask(0xXXXXXXXX <0:no restore / 1:restore>)									*/
/*----------------------------------------------------------------------------------------------*/
static void	ErrH_Ecm_Reg_RestoreEcmProt4ByteMask( volatile U4 *t_pu4Address, U4 t_u4ExpectedValue, U4 t_u4Mask )
{
	U4							t_u4Exp;
	U4							t_u4Val;

	t_u4Exp = t_u4ExpectedValue & t_u4Mask;
	
	t_u4Val = *t_pu4Address;
	
	/* 1.ECMKCPROT - ECM キーコード保護レジスタ 保護解除 */
	REG_ECM.unECMKCPROT.u4Data = (U4)ECM_ECMKCPROT_KCE_ENABLE;
	
	/* 2 Set Config Data */
	*t_pu4Address = (t_u4Val & (U4)(~t_u4Mask) ) | t_u4Exp; 
	
	/* 割り込みが入ると、書き込みが失敗するが次の周期でリトライが入るので良しとする。*/

	/* 3.ECMKCPROT - ECM キーコード保護レジスタ 保護設定 */
	REG_ECM.unECMKCPROT.u4Data = (U4)ECM_ECMKCPROT_KCE_DISABLE;
	Bswlib_Sync_Pipeline_4( REG_ECM.unECMKCPROT.u4Data );
}
#endif // zantei REGCHKは2月末非対応

#pragma ghs section text=default
/*-- End Of File -------------------------------------------------------------------------------*/
