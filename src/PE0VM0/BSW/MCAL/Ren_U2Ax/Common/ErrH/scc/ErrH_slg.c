/* ErrH-r04-3000-0200-b-v00 */
/************************************************************************************************/
/*																								*/
/*		ErrH Driver																				*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

#if 0 // zantei MPUは2月末非対応

/*==============================================================================================*/
/* include files																				*/
/*==============================================================================================*/
#include	"ErrH_cfg.h"
#include	"ErrH_mcu_def.h"

#include	"Dma.h"			/* DTS SPID設定用 */

#include	"errh_reg_spid.h"
#include	"ErrH_peg.h"
#include	"ErrH_crg.h"
#include	"ErrH_pbg.h"
#include	"errh_reg_hbg.h"

#include	"ErrH_slg.h"
#include    "ErrH.h"

/*==============================================================================================*/
/* prototypes																					*/
/*==============================================================================================*/
static	void			ErrH_Slg_Spid_Init( const U4 *t_pcu4ConfigTable );					/* SPID初期化 */
static	void			ErrH_Slg_Peg_Init( const ErrH_PegConfigType *t_pcstConfigTable );	/* PEG初期化 */
static	void			ErrH_Slg_Crg_Init( const ErrH_CrgConfigType *t_pcstCrgConfigTable, const ErrH_CrgConfigType *t_pcstCsgConfigTable );	/* CRG初期化 */
static	void			ErrH_Slg_Pbg_Init( const ErrH_PbgConfigType *t_pcstConfigTable );	/* PBG初期化 */
static	void			ErrH_Slg_Hbg_DisableAllGuard( void );								/* HBG無効化 */
static	U1				ErrH_Slg_Compare4ByteMask( volatile const U4 *t_pcu4Address, U4 t_u4ExpectedValue, U4 t_u4Mask );
static	void			ErrH_Slg_Reg_RestorePegCore0Prot4ByteMask( volatile U4 *t_pu4Address, U4 t_u4ExpectedValue, U4 t_u4Mask );
static	void			ErrH_Slg_Reg_RestorePegCore1Prot4ByteMask( volatile U4 *t_pu4Address, U4 t_u4ExpectedValue, U4 t_u4Mask );
static	void			ErrH_Slg_Reg_RestorePegCore2Prot4ByteMask( volatile U4 *t_pu4Address, U4 t_u4ExpectedValue, U4 t_u4Mask );
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
static	void			ErrH_Slg_Reg_RestorePegCore3Prot4ByteMask( volatile U4 *t_pu4Address, U4 t_u4ExpectedValue, U4 t_u4Mask );
#endif
static	void			ErrH_Slg_Reg_RestoreCrgCl0Prot4ByteMask( volatile U4 *t_pu4Address, U4 t_u4ExpectedValue, U4 t_u4Mask );
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
static	void			ErrH_Slg_Reg_RestoreCrgCl1Prot4ByteMask( volatile U4 *t_pu4Address, U4 t_u4ExpectedValue, U4 t_u4Mask );
#endif
static	void			ErrH_Slg_Reg_RestorePbg50Prot4ByteMask( volatile U4 *t_pu4Address, U4 t_u4ExpectedValue, U4 t_u4Mask );

/*==============================================================================================*/
/* defines / data types / structs / unions	/ macros											*/
/*==============================================================================================*/
/* SPID *//* 使用しないSPIDのため設定は行わない */
/*#define		u1ERRH_SLG_SPID_10			((U1)0x0AU) */	/* GTM	*/
/*#define		u1ERRH_SLG_SPID_11			((U1)0x0BU) */	/* GTM	*/
/*#define		u1ERRH_SLG_SPID_12			((U1)0x0CU) */	/* GTM	*/
/*#define		u1ERRH_SLG_SPID_13			((U1)0x0DU) */	/* GTM	*/
/*#define		u1ERRH_SLG_SPID_14			((U1)0x0EU) */	/* GTM	*/
/*#define		u1ERRH_SLG_SPID_15			((U1)0x0FU) */	/* GTM	*/
/*#define		u1ERRH_SLG_SPID_16			((U1)0x10U) */	/* GTM	*/
/*#define		u1ERRH_SLG_SPID_17			((U1)0x11U) */	/* GTM	*/
/*#define		u1ERRH_SLG_SPID_18			((U1)0x12U) */	/* EMU3S0	*/
/*#define		u1ERRH_SLG_SPID_20			((U1)0x14U) */	/* EMU3S1	*/
/*#define		u1ERRH_SLG_SPID_28			((U1)0x1CU) */	/* RHSIF0	*/
/*#define		u1ERRH_SLG_SPID_32			((U1)0x20U) */	/* FlexRay0	*/
/*#define		u1ERRH_SLG_SPID_34			((U1)0x22U) */	/* ETND0	*/
/*#define		u1ERRH_SLG_SPID_35			((U1)0x23U) */	/* ICUMHB	*/
/*#define		u1ERRH_SLG_SPID_36			((U1)0x24U) */	/* ICUMHB	*/
/*#define		u1ERRH_SLG_SPID_37			((U1)0x25U) */	/* ICUMHB	*/
/*#define		u1ERRH_SLG_SPID_41			((U1)0x29U) */	/* DFP	*/
/*#define		u1ERRH_SLG_SPID_42			((U1)0x2AU) */	/* MAU	*/
/*#define		u1ERRH_SLG_SPID_43			((U1)0x2BU) */	/* DFP, ICUM	 */

/* SPID MASK */
#define		u4ERRH_SLG_SPIDMASK00_USE	((U4)0x0000007FU)				/* SPID:0~6 使用するSPID */
#define		u4ERRH_SLG_SPIDMASK01_USE	((U4)0x0000007FU)				/* SPID:0~6 使用するSPID */
#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_TRIPLECORE ) )
#define		u4ERRH_SLG_SPIDMASK02_USE	((U4)0x0000007FU)				/* SPID:0~6 使用するSPID */
#endif
#define		u4ERRH_SLG_SPIDMASK_NOUSE	((U4)0x00000000U)				/* 全て使用不可 */

/* SPID MASK LOCK */
#define		u4ERRH_SLG_SPIDMASKLOCK_LOCK	((U4)SPID_BMSPIDMSKLOCK_LOCK * (U4)SPID_BMSPIDMSKLOCK_LOCK_LOCK)	/* 書き込み不可 */

/* PEG */
#define		u4ERRH_SLG_PEG_ALLRWPROTDATA			((U4)0x00000153U)	/* 制御 */
#define		u4ERRH_SLG_PEG_ALLRWSPIDDATA			((U4)0x00000007U)	/* SPID */
#define		u4ERRH_SLG_PEG_ALLRWCORE0COMBASE		((U4)0xFDC00000U)	/* ベース(Core0) */
#define		u4ERRH_SLG_PEG_ALLRWCORE1COMBASE		((U4)0xFDA00000U)	/* ベース(Core1) */
#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_TRIPLECORE ) )
#define		u4ERRH_SLG_PEG_ALLRWCORE2COMBASE		((U4)0xFD800000U)	/* ベース(Core2) */
#endif
#define		u4ERRH_SLG_PEG_ALLRWCOMADDRDATA			((U4)0x00000000U)	/* 有効ビット */

/* CRG */
#define		u4ERRH_SLG_CRG_ALLRWPROTDATA			((U4)0x00000153U)	/* 制御 */
#define		u4ERRH_SLG_CRG_ALLRWSPIDDATA			((U4)0x00000007U)	/* SPID */
#define		u4ERRH_SLG_CRG_ALLRWCRAM0COMBASE		((U4)0xFE000000U)	/* ベース(CRAM0) */
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
#define		u4ERRH_SLG_CRG_ALLRWCRAM1COMBASE		((U4)0xFE080000U)	/* ベース(CRAM1) */
#endif
#define		u4ERRH_SLG_CRG_ALLRWCOMADDRDATA			((U4)0x00000000U)	/* 有効ビット */

#if ( MCU_TYPE_SERIES == MCU_RH850U2B6 )
#define		u1ERRH_SLG_HBG_CHANNEL_NUM				((U1)2U)			/* HBGチャネル数 */
#elif ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
#define		u1ERRH_SLG_HBG_CHANNEL_NUM				((U1)3U)			/* HBGチャネル数 */
#else
	#error "MCU_TYPE_SERIES is not supported"
#endif

#define		u4ERRH_SLG_HBG_NO_GUARD					((U4)0x00000000U)	/* HBG保護無効 */

#define		u1ERRH_SLG_REGCHECK_STS_COMPLETED		((U1)0U)			/* サブモジュールレジスタ診断開始待ち(内部ステータス) */
#define		u1ERRH_SLG_REGCHECK_STS_BUSY			((U1)1U)			/* サブモジュールレジスタ診断中(内部ステータス) */
#define		u1ERRH_SLG_CHECKRESULT_MASK_UPPER4BIT	((U1)0x0FU)			/* 上位4bitマスク(4～7bit) */
#define		u1ERRH_SLG_REGCHECK_COMPLETED			((U1)0x00U)			/* サブモジュールレジスタ診断開始待ち */
#define		u1ERRH_SLG_REGCHECK_BUSY				((U1)0x10U)			/* サブモジュールレジスタ診断中 */

#define		u4ERRH_SLG_NO_ERROR						((U4)0x00000000U)	/* エラーなし */
#define		u4ERRH_SLG_INVALID_ADDRESS				((U4)0x00000000U)	/* エラーアドレス無効値 */
#define		u4ERRH_SLG_INVALID_ACCESS_INFO			((U4)0x00000000U)	/* エラーアクセス情報無効値 */
#define		u1ERRH_SLG_PEG_CH0						((U1)0U)			/* PEG CH0 */
#define		u1ERRH_SLG_PEG_CH1						((U1)1U)			/* PEG CH1 */
#define		u1ERRH_SLG_CRG_CH0						((U1)0U)			/* CRG CH0 */
#define		u1ERRH_SLG_CRG_CH1						((U1)1U)			/* CRG CH1 */

/*==============================================================================================*/
/* constants																					*/
/*==============================================================================================*/
#pragma ghs section rodata=".ERRH_RODATA_CONST"
static volatile Reg_Hbg_HbgType* const pcstReg_Hbg[u1ERRH_SLG_HBG_CHANNEL_NUM] = {
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
			&Reg_HBG_HBG90,
#endif
			&Reg_HBG_HBG92,
			&Reg_HBG_HBG94
};

static volatile Reg_Hbg_HbgErrSlvType* const pcstReg_HbgErrSlv[u1ERRH_SLG_HBG_CHANNEL_NUM] = {
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
			&Reg_HBG_HBGERRSLV90,
#endif
			&Reg_HBG_HBGERRSLV92,
			&Reg_HBG_HBGERRSLV94
};

#pragma ghs section rodata=default

/*==============================================================================================*/
/* variables																					*/
/*==============================================================================================*/
#pragma ghs section bss=".ERRH_BSS_VAR_NO_INIT"
static				U2		s_u2ErrH_Slg_RegCheckNum;		/* レジスタ診断番号 */ /* 干渉対策のため、ErrH_Slg_CheckReg_ASIL()のみからライトすること */
static	volatile	U1		s_u1ErrH_Slg_RegCheckStatus;	/* レジスタ診断ステータス */ /* 干渉対策のため、ErrH_Slg_CheckReg_ASIL()のみからライトすること */
#pragma ghs section bss=default

/*==============================================================================================*/
/* functions																					*/
/*==============================================================================================*/
#pragma ghs section text=".ERRH_TEXT_CODE"
/*----------------------------------------------------------------------------------------------*/
/* API Functions																				*/
/*----------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------*/
/* SLG Clear Error Function																		*/
/* Return		: none																			*/
/* Parameters	: ErrorID 																		*/
/*				: ModuleNum																		*/
/*----------------------------------------------------------------------------------------------*/
void	ErrH_Slg_ClearError( U2 t_u2ErrorID, U2 t_u2ModuleNum )
{
	/* ErrorIDで検索 */
	/* PEG */
	if( t_u2ErrorID == u2ERRH_NCF240_ID )
	{
		ErrH_Peg_ClearError( (U1)BSW_CORE_ID_CORE0, t_u2ModuleNum );		/* CORE0 */
	}
	if( t_u2ErrorID == u2ERRH_NCF272_ID )
	{
		ErrH_Peg_ClearError( (U1)BSW_CORE_ID_CORE1, t_u2ModuleNum );		/* CORE1 */
	}
#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_TRIPLECORE ) )	/* U2B10かつ3コア構成 */
	if( t_u2ErrorID == u2ERRH_NCF304_ID )
	{
		ErrH_Peg_ClearError( (U1)BSW_CORE_ID_CORE2, t_u2ModuleNum );		/* CORE2 */
	}
#endif
	
	/* CRG */
	if( t_u2ErrorID == u2ERRH_NCF168_ID )
	{
		ErrH_Crg_ClearError( t_u2ModuleNum );
	}
	
	/* PBG */
	if( t_u2ErrorID == u2ERRH_NCF170_ID )
	{
		ErrH_Pbg_ClearError( t_u2ModuleNum );
	}
}

/*----------------------------------------------------------------------------------------------*/
/* SLG Get Error Status Function																*/
/* Return		: Error Status																	*/
/* Parameters	: ErrorID 																		*/
/*				: ModuleNum																		*/
/*----------------------------------------------------------------------------------------------*/
U4	ErrH_Slg_GetErrStatus( U2 t_u2ErrorID, U2 t_u2ModuleNum )
{
	U4	t_u4ErrorStatus;

	t_u4ErrorStatus = u4ERRH_SLG_NO_ERROR;	/* エラーなしで初期化*/

	/* ErrorIDで検索 */
	/* PEG */
	if( t_u2ErrorID == u2ERRH_NCF240_ID )
	{
		t_u4ErrorStatus = ErrH_Peg_GetErrStatus( (U1)BSW_CORE_ID_CORE0, t_u2ModuleNum );
	}
	if( t_u2ErrorID == u2ERRH_NCF272_ID )
	{
		t_u4ErrorStatus = ErrH_Peg_GetErrStatus( (U1)BSW_CORE_ID_CORE1, t_u2ModuleNum );
	}
#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_TRIPLECORE ) )	/* U2B10かつ3コア構成 */
	if( t_u2ErrorID == u2ERRH_NCF304_ID )
	{
		t_u4ErrorStatus = ErrH_Peg_GetErrStatus( (U1)BSW_CORE_ID_CORE2, t_u2ModuleNum );
	}
#endif
	
	/* CRG */
	if( t_u2ErrorID == u2ERRH_NCF168_ID )
	{
		t_u4ErrorStatus = ErrH_Crg_GetErrorStatus( t_u2ModuleNum );
	}
	
	/* PBG */
	if( t_u2ErrorID == u2ERRH_NCF170_ID )
	{
		t_u4ErrorStatus = ErrH_Pbg_GetErrorStatus( t_u2ModuleNum );
	}

	return ( t_u4ErrorStatus ) ;
}

/*----------------------------------------------------------------------------------------------*/
/* SLG Get Error Address Function																*/
/* Return		: Error Address																	*/
/* Parameters	: ErrorID 																		*/
/*				: ModuleNum																		*/
/*----------------------------------------------------------------------------------------------*/
U4	ErrH_Slg_GetErrAddress( U2 t_u2ErrorID, U2 t_u2ModuleNum )
{
	U4	t_u4ErrorAddress;

	t_u4ErrorAddress = u4ERRH_SLG_INVALID_ADDRESS;	/* エラーアドレス無効値で初期化 */

	/* ErrorIDで検索 */
	/* PEG */
	if( t_u2ErrorID == u2ERRH_NCF240_ID )
	{
		t_u4ErrorAddress = ErrH_Peg_GetErrAddress( (U1)BSW_CORE_ID_CORE0, t_u2ModuleNum );
	}
	if( t_u2ErrorID == u2ERRH_NCF272_ID )
	{
		t_u4ErrorAddress = ErrH_Peg_GetErrAddress( (U1)BSW_CORE_ID_CORE1, t_u2ModuleNum );
	}
#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_TRIPLECORE ) )	/* U2B10かつ3コア構成 */
	if( t_u2ErrorID == u2ERRH_NCF304_ID )
	{
		t_u4ErrorAddress = ErrH_Peg_GetErrAddress( (U1)BSW_CORE_ID_CORE2, t_u2ModuleNum );
	}
#endif
	
	/* CRG */
	if( t_u2ErrorID == u2ERRH_NCF168_ID )
	{
		t_u4ErrorAddress = ErrH_Crg_GetErrAddress( t_u2ModuleNum  );

	}

	/* PBG */
	if( t_u2ErrorID == u2ERRH_NCF170_ID )
	{
		t_u4ErrorAddress = ErrH_Pbg_GetErrAddress( t_u2ModuleNum );
	}

	return ( t_u4ErrorAddress ) ;
}

/*----------------------------------------------------------------------------------------------*/
/* SLG Get Error Access info Function															*/
/* Return		: Error Access info																*/
/* Parameters	: ErrorID 																		*/
/*				: ModuleNum																		*/
/*----------------------------------------------------------------------------------------------*/
U4	ErrH_Slg_GetErrAccessInfo( U2 t_u2ErrorID, U2 t_u2ModuleNum )
{
	U4	t_u4ErrorAccessInfo;

	t_u4ErrorAccessInfo = u4ERRH_SLG_INVALID_ACCESS_INFO;	/* エラーアクセス情報無効値で初期化 */

	/* ErrorIDで検索 */
	/* PEG */
	if( t_u2ErrorID == u2ERRH_NCF240_ID )
	{
		t_u4ErrorAccessInfo = ErrH_Peg_GetErrAccessInfo( (U1)BSW_CORE_ID_CORE0, t_u2ModuleNum );
	}
	if( t_u2ErrorID == u2ERRH_NCF272_ID )
	{
		t_u4ErrorAccessInfo = ErrH_Peg_GetErrAccessInfo( (U1)BSW_CORE_ID_CORE1, t_u2ModuleNum );
	}
#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_TRIPLECORE ) )	/* U2B10かつ3コア構成 */
	if( t_u2ErrorID == u2ERRH_NCF304_ID )
	{
		t_u4ErrorAccessInfo = ErrH_Peg_GetErrAccessInfo( (U1)BSW_CORE_ID_CORE2, t_u2ModuleNum );
	}
#endif
	
	/* CRG */
	if( t_u2ErrorID == u2ERRH_NCF168_ID )
	{
		t_u4ErrorAccessInfo = ErrH_Crg_GetErrAccessInfo( t_u2ModuleNum  );
	}
	
	/* PBG */
	if( t_u2ErrorID == u2ERRH_NCF170_ID )
	{
		t_u4ErrorAccessInfo = ErrH_Pbg_GetErrAccessInfo( t_u2ModuleNum );
	}

	return ( t_u4ErrorAccessInfo ) ;
}

/*----------------------------------------------------------------------------------------------*/
/* SLG Disable All Guard																		*/
/* Return		: none																			*/
/* Parameters	: none																			*/
/*----------------------------------------------------------------------------------------------*/
void	ErrH_Slg_DisableAllGuard( void )
{
	ErrH_Pbg_DisableAllGuard();		/* PBG無効化 */
	ErrH_Slg_Hbg_DisableAllGuard();	/* HBG無効化 */
}

/*----------------------------------------------------------------------------------------------*/
/*	Request Register Check Function																*/
/*	return		: Register Check Result															*/
/*	parameters	: *ConfigTable																	*/
/*----------------------------------------------------------------------------------------------*/
U1	ErrH_Slg_CheckReg_ASIL( const ErrH_RegCheckConfigType *t_pcstConfigTable )
{
	volatile	void*							t_pvdAddress;		/* レジスタアドレス */
				U4								t_u4ExpectValue;	/* レジスタ期待値 */
				U4								t_u4Mask;			/* レジスタマスク */
				U2								t_u2RegCheckNum;	/* レジスタ診断番号 */
				U1								t_u1Result;			/* 戻り値 */

	t_u1Result = (U1)OK;											/* OKで初期化 */

	if ( s_u1ErrH_Slg_RegCheckStatus == u1ERRH_SLG_REGCHECK_STS_COMPLETED )
	{
		s_u1ErrH_Slg_RegCheckStatus = u1ERRH_SLG_REGCHECK_STS_BUSY;
		s_u2ErrH_Slg_RegCheckNum = (U2)0U;							/* レジスタ診断番号初期化 */
	}

	t_u2RegCheckNum = s_u2ErrH_Slg_RegCheckNum;						/* 現在の診断番号を取得 */

	if ( t_u2RegCheckNum < t_pcstConfigTable->u2RegNum )			/* レジスタ診断テーブル数より小さい場合 */
	{
		t_pvdAddress = t_pcstConfigTable->pcstRegData[ t_u2RegCheckNum ].pvdAddress;
		t_u4ExpectValue = t_pcstConfigTable->pcstRegData[ t_u2RegCheckNum ].u4ExpectValue;
		t_u4Mask = t_pcstConfigTable->pcstRegData[ t_u2RegCheckNum ].u4Mask;
		
		t_u1Result = ErrH_Slg_Compare4ByteMask( (volatile const U4*)t_pvdAddress, t_u4ExpectValue, t_u4Mask );
		
		if ( t_u1Result == (U1)NG )
		{
			switch ( t_pcstConfigTable->pcstRegData[ t_u2RegCheckNum ].u1Prot )
			{
				case (U1)ERRH_SLG_REG_4BYTE_PEG_CORE0_PROT:
					ErrH_Slg_Reg_RestorePegCore0Prot4ByteMask( (volatile U4*)t_pvdAddress, t_u4ExpectValue, t_u4Mask );
					break;
					
				case (U1)ERRH_SLG_REG_4BYTE_PEG_CORE1_PROT:
					ErrH_Slg_Reg_RestorePegCore1Prot4ByteMask( (volatile U4*)t_pvdAddress, t_u4ExpectValue, t_u4Mask );
					break;
					
				case (U1)ERRH_SLG_REG_4BYTE_PEG_CORE2_PROT:
					ErrH_Slg_Reg_RestorePegCore2Prot4ByteMask( (volatile U4*)t_pvdAddress, t_u4ExpectValue, t_u4Mask );
					break;
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
				case (U1)ERRH_SLG_REG_4BYTE_PEG_CORE3_PROT:
					ErrH_Slg_Reg_RestorePegCore3Prot4ByteMask( (volatile U4*)t_pvdAddress, t_u4ExpectValue, t_u4Mask );
					break;
#endif
				case (U1)ERRH_SLG_REG_4BYTE_CRG_CL0_PROT:
					ErrH_Slg_Reg_RestoreCrgCl0Prot4ByteMask( (volatile U4*)t_pvdAddress, t_u4ExpectValue, t_u4Mask );
					break;
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
				case (U1)ERRH_SLG_REG_4BYTE_CRG_CL1_PROT:
					ErrH_Slg_Reg_RestoreCrgCl1Prot4ByteMask( (volatile U4*)t_pvdAddress, t_u4ExpectValue, t_u4Mask );
					break;
#endif
				case (U1)ERRH_SLG_REG_4BYTE_PBG_PBG50_PROT:
					ErrH_Slg_Reg_RestorePbg50Prot4ByteMask( (volatile U4*)t_pvdAddress, t_u4ExpectValue, t_u4Mask );
					break;
					
				default:
					/* 処理無し */
					break;
			}
		}
		
		t_u2RegCheckNum++;
		s_u2ErrH_Slg_RegCheckNum = t_u2RegCheckNum;

		if ( s_u2ErrH_Slg_RegCheckNum < t_pcstConfigTable->u2RegNum )	/* レジスタ診断テーブルサイズより小さい場合 */
		{
			t_u1Result = t_u1Result | u1ERRH_SLG_REGCHECK_BUSY;			/* 4～7bit目にサブモジュールレジスタ診断中(0001B)をセット(本処理前は4～7bit目として0000Bを期待) */
		}
		else
		{
			/* t_u1Resultの4～7bit目にサブモジュールレジスタ診断開始待ち(0000B)をセット(本処理前は4～7bit目として0000Bを期待)。冗長となるため、処理なし */
			s_u1ErrH_Slg_RegCheckStatus = u1ERRH_SLG_REGCHECK_STS_COMPLETED;
		}
	}
	else
	{
		t_u1Result = ( t_u1Result & u1ERRH_SLG_CHECKRESULT_MASK_UPPER4BIT ) | u1ERRH_SLG_REGCHECK_COMPLETED;	/* 4～7bit目に0000B(診断開始待ち)をセット */
		s_u1ErrH_Slg_RegCheckStatus = u1ERRH_SLG_REGCHECK_STS_COMPLETED;
	}

	return( t_u1Result );
}

/*----------------------------------------------------------------------------------------------*/
/* Scheduled / Event Functions																	*/
/*----------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------*/
/* Initialization Function																		*/
/* Return		: none																			*/
/* Parameters	: *ConfigData																	*/
/*----------------------------------------------------------------------------------------------*/
void	ErrH_Slg_Init( const ErrH_UserConfigType *t_pcstConfigData )
{
	/* スレーブガード設定 */
	Dma_SetMasterCh();											/* DTS SPIDの設定 */
	ErrH_Slg_Spid_Init( t_pcstConfigData->pcu4SpidMskCfg );		/* SPIDの設定 */
	ErrH_Slg_Peg_Init( t_pcstConfigData->pcstPegCfg );			/* PEGガード設定 */
	ErrH_Slg_Crg_Init( t_pcstConfigData->pcstCrgCrgCfg, t_pcstConfigData->pcstCrgCsgCfg );		/* CRGガード設定 */
	ErrH_Slg_Pbg_Init( t_pcstConfigData->pcstPbgCfg );			/* PBGガード設定 */
}

/*----------------------------------------------------------------------------------------------*/
/* Local Functions																				*/
/*----------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------*/
/* ErrH_Peg_Init Function																		*/
/* Return		: none																			*/
/* Parameters	: *ConfigTable																	*/
/*----------------------------------------------------------------------------------------------*/
static	void	ErrH_Slg_Spid_Init( const U4 *t_pcu4ConfigTable )
{
	/* バスマスタSPID設定 */
	/* 以下の順番で設定すること UM 55.5.3.10参照 */
	/* 使用できるSPIDは以下とする */
	/* SPID=0(ASIL_CORE0/1/2),1(CORE1),2(CORE2),6(QM_CORE0/1/2),27(DMAC1),28(DMAC0),29(DTS) */
	/* ※SPID=1(CORE1),2(CORE2)はStartOS前まで使用する */
	/* SPID キーコード保護レジスタ 保護解除 */
	Reg_SPID.unSPIDKCPROT.u4Data = (U4)SPID_SPIDKCPROT_KCE_ENABLE;

	/* SPID MASK設定 */
	Reg_SPID.u4BM00SPIDMSK = u4ERRH_SLG_SPIDMASK00_USE;						/* BM00SPIDMSK */
	Reg_SPID.u4BM01SPIDMSK = u4ERRH_SLG_SPIDMASK01_USE;						/* BM01SPIDMSK */
#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_TRIPLECORE ) )
	Reg_SPID.u4BM02SPIDMSK = u4ERRH_SLG_SPIDMASK02_USE;						/* BM02SPIDMSK */
#else /* U2B6、またはU2B10 2コア */
	Reg_SPID.u4BM02SPIDMSK = u4ERRH_SLG_SPIDMASK_NOUSE;						/* BM02SPIDMSK */
#endif
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
	Reg_SPID.u4BM03SPIDMSK = u4ERRH_SLG_SPIDMASK_NOUSE;						/* BM03SPIDMSK */
#endif
	Reg_SPID.u4BM10SPIDMSK = u4ERRH_SLG_SPIDMASK_NOUSE;						/* BM10SPIDMSK */
	Reg_SPID.u4BM11SPIDMSK = u4ERRH_SLG_SPIDMASK_NOUSE;						/* BM11SPIDMSK */
	Reg_SPID.u4BM12SPIDMSK = u4ERRH_SLG_SPIDMASK_NOUSE;						/* BM12SPIDMSK */
	Reg_SPID.u4BM13SPIDMSK = u4ERRH_SLG_SPIDMASK_NOUSE;						/* BM13SPIDMSK */
	Reg_SPID.u4BM14SPIDMSK = u4ERRH_SLG_SPIDMASK_NOUSE;						/* BM14SPIDMSK */
	Reg_SPID.u4BM15SPIDMSK = u4ERRH_SLG_SPIDMASK_NOUSE;						/* BM15SPIDMSK */
	Reg_SPID.u4BM16SPIDMSK = u4ERRH_SLG_SPIDMASK_NOUSE;						/* BM16SPIDMSK */
	Reg_SPID.u4BM17SPIDMSK = u4ERRH_SLG_SPIDMASK_NOUSE;						/* BM17SPIDMSK */
#if ( MCU_TYPE_SERIES == MCU_RH850U2B6 )
	Reg_SPID.u4BM18SPIDMSK = u4ERRH_SLG_SPIDMASK_NOUSE;						/* BM18SPIDMSK */
	Reg_SPID.u4BM20SPIDMSK = u4ERRH_SLG_SPIDMASK_NOUSE;						/* BM20SPIDMSK */
#endif
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
	Reg_SPID.u4BM28SPIDMSK = u4ERRH_SLG_SPIDMASK_NOUSE;						/* BM28SPIDMSK */
#endif
	Reg_SPID.u4BM32SPIDMSK = u4ERRH_SLG_SPIDMASK_NOUSE;						/* BM32SPIDMSK */
	Reg_SPID.u4BM34SPIDMSK = u4ERRH_SLG_SPIDMASK_NOUSE;						/* BM34SPIDMSK */
	Reg_SPID.u4BM35SPIDMSK = u4ERRH_SLG_SPIDMASK_NOUSE;						/* BM35SPIDMSK */
	Reg_SPID.u4BM36SPIDMSK = u4ERRH_SLG_SPIDMASK_NOUSE;						/* BM36SPIDMSK */
	Reg_SPID.u4BM37SPIDMSK = u4ERRH_SLG_SPIDMASK_NOUSE;						/* BM37SPIDMSK */
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
	Reg_SPID.u4BM38SPIDMSK = t_pcu4ConfigTable[ERRH_SLG_BUSMASTER_SDMAC1];	/* BM38SPIDMSK */
#endif
	Reg_SPID.u4BM39SPIDMSK = t_pcu4ConfigTable[ERRH_SLG_BUSMASTER_SDMAC0];	/* BM39SPIDMSK */
	Reg_SPID.u4BM40SPIDMSK = t_pcu4ConfigTable[ERRH_SLG_BUSMASTER_DTS];		/* BM40SPIDMSK */
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
	Reg_SPID.u4BM41SPIDMSK = u4ERRH_SLG_SPIDMASK_NOUSE;						/* BM41SPIDMSK */
#endif
	Reg_SPID.u4BM42SPIDMSK = u4ERRH_SLG_SPIDMASK_NOUSE;						/* BM42SPIDMSK */
	Reg_SPID.u4BM43SPIDMSK = u4ERRH_SLG_SPIDMASK_NOUSE;						/* BM43SPIDMSK */

	/* SPID LOCK設定 */
	Reg_SPID.unBM00SPIDMSKLOCK.u4Data = u4ERRH_SLG_SPIDMASKLOCK_LOCK;		/* BM00SPIDMSKLOCK */
	Reg_SPID.unBM01SPIDMSKLOCK.u4Data = u4ERRH_SLG_SPIDMASKLOCK_LOCK;		/* BM01SPIDMSKLOCK */
	Reg_SPID.unBM02SPIDMSKLOCK.u4Data = u4ERRH_SLG_SPIDMASKLOCK_LOCK;		/* BM02SPIDMSKLOCK */
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
	Reg_SPID.unBM03SPIDMSKLOCK.u4Data = u4ERRH_SLG_SPIDMASKLOCK_LOCK;		/* BM03SPIDMSKLOCK */
#endif
	Reg_SPID.unBM10SPIDMSKLOCK.u4Data = u4ERRH_SLG_SPIDMASKLOCK_LOCK;		/* BM10SPIDMSKLOCK */
	Reg_SPID.unBM11SPIDMSKLOCK.u4Data = u4ERRH_SLG_SPIDMASKLOCK_LOCK;		/* BM11SPIDMSKLOCK */
	Reg_SPID.unBM12SPIDMSKLOCK.u4Data = u4ERRH_SLG_SPIDMASKLOCK_LOCK;		/* BM12SPIDMSKLOCK */
	Reg_SPID.unBM13SPIDMSKLOCK.u4Data = u4ERRH_SLG_SPIDMASKLOCK_LOCK;		/* BM13SPIDMSKLOCK */
	Reg_SPID.unBM14SPIDMSKLOCK.u4Data = u4ERRH_SLG_SPIDMASKLOCK_LOCK;		/* BM14SPIDMSKLOCK */
	Reg_SPID.unBM15SPIDMSKLOCK.u4Data = u4ERRH_SLG_SPIDMASKLOCK_LOCK;		/* BM15SPIDMSKLOCK */
	Reg_SPID.unBM16SPIDMSKLOCK.u4Data = u4ERRH_SLG_SPIDMASKLOCK_LOCK;		/* BM16SPIDMSKLOCK */
	Reg_SPID.unBM17SPIDMSKLOCK.u4Data = u4ERRH_SLG_SPIDMASKLOCK_LOCK;		/* BM17SPIDMSKLOCK */
#if ( MCU_TYPE_SERIES == MCU_RH850U2B6 )
	Reg_SPID.unBM18SPIDMSKLOCK.u4Data = u4ERRH_SLG_SPIDMASKLOCK_LOCK;		/* BM18SPIDMSKLOCK */
	Reg_SPID.unBM20SPIDMSKLOCK.u4Data = u4ERRH_SLG_SPIDMASKLOCK_LOCK;		/* BM20SPIDMSKLOCK */
#endif
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
	Reg_SPID.unBM28SPIDMSKLOCK.u4Data = u4ERRH_SLG_SPIDMASKLOCK_LOCK;		/* BM28SPIDMSKLOCK */
#endif
	Reg_SPID.unBM32SPIDMSKLOCK.u4Data = u4ERRH_SLG_SPIDMASKLOCK_LOCK;		/* BM32SPIDMSKLOCK */
	Reg_SPID.unBM34SPIDMSKLOCK.u4Data = u4ERRH_SLG_SPIDMASKLOCK_LOCK;		/* BM34SPIDMSKLOCK */
	Reg_SPID.unBM35SPIDMSKLOCK.u4Data = u4ERRH_SLG_SPIDMASKLOCK_LOCK;		/* BM35SPIDMSKLOCK */
	Reg_SPID.unBM36SPIDMSKLOCK.u4Data = u4ERRH_SLG_SPIDMASKLOCK_LOCK;		/* BM36SPIDMSKLOCK */
	Reg_SPID.unBM37SPIDMSKLOCK.u4Data = u4ERRH_SLG_SPIDMASKLOCK_LOCK;		/* BM37SPIDMSKLOCK */
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
	Reg_SPID.unBM38SPIDMSKLOCK.u4Data = u4ERRH_SLG_SPIDMASKLOCK_LOCK;		/* BM38SPIDMSKLOCK */
#endif
	Reg_SPID.unBM39SPIDMSKLOCK.u4Data = u4ERRH_SLG_SPIDMASKLOCK_LOCK;		/* BM39SPIDMSKLOCK */
	Reg_SPID.unBM40SPIDMSKLOCK.u4Data = u4ERRH_SLG_SPIDMASKLOCK_LOCK;		/* BM40SPIDMSKLOCK */
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
	Reg_SPID.unBM41SPIDMSKLOCK.u4Data = u4ERRH_SLG_SPIDMASKLOCK_LOCK;		/* BM41SPIDMSKLOCK */
#endif
	Reg_SPID.unBM42SPIDMSKLOCK.u4Data = u4ERRH_SLG_SPIDMASKLOCK_LOCK;		/* BM42SPIDMSKLOCK */
	Reg_SPID.unBM43SPIDMSKLOCK.u4Data = u4ERRH_SLG_SPIDMASKLOCK_LOCK;		/* BM43SPIDMSKLOCK */

	/* SPID設定 *//* 使用しないSPIDのため設定は行わない */
/*	Reg_SPID.unBM10SPID.u4Data = SPID_BMSPID_SPID_0 * u1ERRH_SLG_SPID_10; */	/* BM10SPID */
/*	Reg_SPID.unBM11SPID.u4Data = SPID_BMSPID_SPID_0 * u1ERRH_SLG_SPID_11; */	/* BM11SPID */
/*	Reg_SPID.unBM12SPID.u4Data = SPID_BMSPID_SPID_0 * u1ERRH_SLG_SPID_12; */	/* BM12SPID */
/*	Reg_SPID.unBM13SPID.u4Data = SPID_BMSPID_SPID_0 * u1ERRH_SLG_SPID_13; */	/* BM13SPID */
/*	Reg_SPID.unBM14SPID.u4Data = SPID_BMSPID_SPID_0 * u1ERRH_SLG_SPID_14; */	/* BM14SPID */
/*	Reg_SPID.unBM15SPID.u4Data = SPID_BMSPID_SPID_0 * u1ERRH_SLG_SPID_15; */	/* BM15SPID */
/*	Reg_SPID.unBM16SPID.u4Data = SPID_BMSPID_SPID_0 * u1ERRH_SLG_SPID_16; */	/* BM16SPID */
/*	Reg_SPID.unBM17SPID.u4Data = SPID_BMSPID_SPID_0 * u1ERRH_SLG_SPID_17; */	/* BM17SPID */
/*	Reg_SPID.unBM18SPID.u4Data = SPID_BMSPID_SPID_0 * u1ERRH_SLG_SPID_18; */	/* BM18SPID */
/*	Reg_SPID.unBM20SPID.u4Data = SPID_BMSPID_SPID_0 * u1ERRH_SLG_SPID_20; */	/* BM20SPID */
/*	Reg_SPID.unBM22SPID.u4Data = SPID_BMSPID_SPID_0 * u1ERRH_SLG_SPID_22; */	/* BM22SPID */
/*	Reg_SPID.unBM28SPID.u4Data = SPID_BMSPID_SPID_0 * u1ERRH_SLG_SPID_28; */	/* BM28SPID */
/*	Reg_SPID.unBM32SPID.u4Data = SPID_BMSPID_SPID_0 * u1ERRH_SLG_SPID_32; */	/* BM32SPID */
/*	Reg_SPID.unBM34SPID.u4Data = SPID_BMSPID_SPID_0 * u1ERRH_SLG_SPID_34; */	/* BM34SPID */
/*	Reg_SPID.unBM35SPID.u4Data = SPID_BMSPID_SPID_0 * u1ERRH_SLG_SPID_35; */	/* BM35SPID */
/*	Reg_SPID.unBM36SPID.u4Data = SPID_BMSPID_SPID_0 * u1ERRH_SLG_SPID_36; */	/* BM36SPID */
/*	Reg_SPID.unBM37SPID.u4Data = SPID_BMSPID_SPID_0 * u1ERRH_SLG_SPID_37; */	/* BM37SPID */
/*	Reg_SPID.unBM41SPID.u4Data = SPID_BMSPID_SPID_0 * u1ERRH_SLG_SPID_41; */	/* BM41SPID */
/*	Reg_SPID.unBM42SPID.u4Data = SPID_BMSPID_SPID_0 * u1ERRH_SLG_SPID_42; */	/* BM42SPID */
/*	Reg_SPID.unBM43SPID.u4Data = SPID_BMSPID_SPID_0 * u1ERRH_SLG_SPID_43; */	/* BM43SPID */

	/* SPID キーコード保護レジスタ 保護設定 */
	Reg_SPID.unSPIDKCPROT.u4Data = (U4)SPID_SPIDKCPROT_KCE_DISABLE;
	Bswlib_Sync_Pipeline_4( Reg_SPID.unSPIDKCPROT.u4Data );

}

/*----------------------------------------------------------------------------------------------*/
/* ErrH_Peg_Init Function																		*/
/* Return		: none																			*/
/* Parameters	: *ConfigTable																	*/
/*----------------------------------------------------------------------------------------------*/
static	void	ErrH_Slg_Peg_Init( const ErrH_PegConfigType *t_pcstConfigTable )
{
	ErrH_PegProtSetType		t_stProtSet;
	S4						i;

	/* PEG全アクセス許可設定 */
	/* PEGの設定を実施すると、全アクセス不可となるため */
	/* PEGの設定を行う前に全アクセス許可設定を行う	 */
	t_stProtSet.u4Base = u4ERRH_SLG_PEG_ALLRWCORE0COMBASE & (U4)PEG_PEGBAD_BAD;				/* チャネルベースアドレス設定 */
	t_stProtSet.u4Addv = u4ERRH_SLG_PEG_ALLRWCOMADDRDATA;									/* チャネル有効ビット設定 */
	t_stProtSet.u4Prot = u4ERRH_SLG_PEG_ALLRWPROTDATA;										/* チャネル保護制御 */
	t_stProtSet.u4Spid = u4ERRH_SLG_PEG_ALLRWSPIDDATA;										/* チャネル SPID 設定 */
	ErrH_Peg_SetModeStartGuard( u1ERRH_SLG_PEG_CH0 ,(U1)BSW_CORE_ID_CORE0 ,&t_stProtSet );

	t_stProtSet.u4Base = u4ERRH_SLG_PEG_ALLRWCORE1COMBASE & (U4)PEG_PEGBAD_BAD;				/* チャネルベースアドレス設定 */
	t_stProtSet.u4Addv = u4ERRH_SLG_PEG_ALLRWCOMADDRDATA;									/* チャネル有効ビット設定 */
	t_stProtSet.u4Prot = u4ERRH_SLG_PEG_ALLRWPROTDATA;										/* チャネル保護制御 */
	t_stProtSet.u4Spid = u4ERRH_SLG_PEG_ALLRWSPIDDATA;										/* チャネル SPID 設定 */
	ErrH_Peg_SetModeStartGuard( u1ERRH_SLG_PEG_CH0 ,(U1)BSW_CORE_ID_CORE1, &t_stProtSet );

#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_TRIPLECORE ) )
	t_stProtSet.u4Base = u4ERRH_SLG_PEG_ALLRWCORE2COMBASE & (U4)PEG_PEGBAD_BAD;				/* チャネルベースアドレス設定 */
	t_stProtSet.u4Addv = u4ERRH_SLG_PEG_ALLRWCOMADDRDATA;									/* チャネル有効ビット設定 */
	t_stProtSet.u4Prot = u4ERRH_SLG_PEG_ALLRWPROTDATA;										/* チャネル保護制御 */
	t_stProtSet.u4Spid = u4ERRH_SLG_PEG_ALLRWSPIDDATA;										/* チャネル SPID 設定 */
	ErrH_Peg_SetModeStartGuard( u1ERRH_SLG_PEG_CH0 ,(U1)BSW_CORE_ID_CORE2 ,&t_stProtSet );
#endif

	/* PEG 設定(CORE0) */
	for ( i = (S4)u1ERRH_SLG_PEG_CH1; i < (S4)ERRH_SLG_PEG_AREA_NUM; i++ )
	{
		t_stProtSet.u4Base = t_pcstConfigTable[i].u4BaseData & (U4)PEG_PEGBAD_BAD;			/* チャネルベースアドレス設定 */
		t_stProtSet.u4Addv = t_pcstConfigTable[i].u4AddvData & (U4)PEG_PEGADV_ADV;			/* チャネル有効ビット設定 */
		t_stProtSet.u4Prot = t_pcstConfigTable[i].u4ConfigData;								/* チャネル保護制御 */
		t_stProtSet.u4Spid = t_pcstConfigTable[i].u4SpidMapData;							/* チャネル SPID 設定 */
		/* PEG 開始 */
		ErrH_Peg_SetModeStartGuard( (U1)i ,(U1)BSW_CORE_ID_CORE0 ,&t_stProtSet );
	}

	/* Core0の領域0の設定 */
	t_stProtSet.u4Base = t_pcstConfigTable[u1ERRH_SLG_PEG_CH0].u4BaseData & (U4)PEG_PEGBAD_BAD;		/* チャネルベースアドレス設定 */
	t_stProtSet.u4Addv = t_pcstConfigTable[u1ERRH_SLG_PEG_CH0].u4AddvData & (U4)PEG_PEGADV_ADV;		/* チャネル有効ビット設定 */
	t_stProtSet.u4Prot = t_pcstConfigTable[u1ERRH_SLG_PEG_CH0].u4ConfigData;						/* チャネル保護制御 */
	t_stProtSet.u4Spid = t_pcstConfigTable[u1ERRH_SLG_PEG_CH0].u4SpidMapData;						/* チャネル SPID 設定 */
	/* PEG 開始 */
	ErrH_Peg_SetModeStartGuard( u1ERRH_SLG_PEG_CH0 ,(U1)BSW_CORE_ID_CORE0 ,&t_stProtSet );

	/* PEG 設定(CORE1) */
	for ( i = (S4)u1ERRH_SLG_PEG_CH1; i < (S4)ERRH_SLG_PEG_AREA_NUM; i++ )
	{
		t_stProtSet.u4Base = t_pcstConfigTable[i + (S4)ERRH_SLG_PEG_AREA_NUM].u4BaseData & (U4)PEG_PEGBAD_BAD;		/* チャネルベースアドレス設定 */
		t_stProtSet.u4Addv = t_pcstConfigTable[i + (S4)ERRH_SLG_PEG_AREA_NUM].u4AddvData & (U4)PEG_PEGADV_ADV;		/* チャネル有効ビット設定 */
		t_stProtSet.u4Prot = t_pcstConfigTable[i + (S4)ERRH_SLG_PEG_AREA_NUM].u4ConfigData;							/* チャネル保護制御 */
		t_stProtSet.u4Spid = t_pcstConfigTable[i + (S4)ERRH_SLG_PEG_AREA_NUM].u4SpidMapData;						/* チャネル SPID 設定 */
		/* PEG 開始 */									
		ErrH_Peg_SetModeStartGuard( (U1)i ,(U1)BSW_CORE_ID_CORE1 ,&t_stProtSet );
	}

	/* Core1の領域0の設定 */
	t_stProtSet.u4Base = t_pcstConfigTable[u1ERRH_SLG_PEG_CH0 + (U1)ERRH_SLG_PEG_AREA_NUM].u4BaseData & (U4)PEG_PEGBAD_BAD;		/* チャネルベースアドレス設定 */
	t_stProtSet.u4Addv = t_pcstConfigTable[u1ERRH_SLG_PEG_CH0 + (U1)ERRH_SLG_PEG_AREA_NUM].u4AddvData & (U4)PEG_PEGADV_ADV;		/* チャネル有効ビット設定 */
	t_stProtSet.u4Prot = t_pcstConfigTable[u1ERRH_SLG_PEG_CH0 + (U1)ERRH_SLG_PEG_AREA_NUM].u4ConfigData;						/* チャネル保護制御 */
	t_stProtSet.u4Spid = t_pcstConfigTable[u1ERRH_SLG_PEG_CH0 + (U1)ERRH_SLG_PEG_AREA_NUM].u4SpidMapData;						/* チャネル SPID 設定 */
	/* PEG 開始 */									
	ErrH_Peg_SetModeStartGuard( u1ERRH_SLG_PEG_CH0 ,(U1)BSW_CORE_ID_CORE1 ,&t_stProtSet );

#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_TRIPLECORE ) )
	/* PEG 設定(CORE2) */
	for ( i = (S4)u1ERRH_SLG_PEG_CH1; i < (S4)ERRH_SLG_PEG_AREA_NUM; i++ )
	{
		t_stProtSet.u4Base = t_pcstConfigTable[i + ( (S4)BSW_CORE_ID_CORE2 * (S4)ERRH_SLG_PEG_AREA_NUM )].u4BaseData & (U4)PEG_PEGBAD_BAD;		/* チャネルベースアドレス設定 */
		t_stProtSet.u4Addv = t_pcstConfigTable[i + ( (S4)BSW_CORE_ID_CORE2 * (S4)ERRH_SLG_PEG_AREA_NUM )].u4AddvData & (U4)PEG_PEGADV_ADV;		/* チャネル有効ビット設定 */
		t_stProtSet.u4Prot = t_pcstConfigTable[i + ( (S4)BSW_CORE_ID_CORE2 * (S4)ERRH_SLG_PEG_AREA_NUM )].u4ConfigData;							/* チャネル保護制御 */
		t_stProtSet.u4Spid = t_pcstConfigTable[i + ( (S4)BSW_CORE_ID_CORE2 * (S4)ERRH_SLG_PEG_AREA_NUM )].u4SpidMapData;							/* チャネル SPID 設定 */
		/* PEG 開始 */									 
		ErrH_Peg_SetModeStartGuard( (U1)i ,(U1)BSW_CORE_ID_CORE2 ,&t_stProtSet );
	}

	/* Core2の領域0の設定 */
	t_stProtSet.u4Base = t_pcstConfigTable[(S4)u1ERRH_SLG_PEG_CH0 + ( (S4)BSW_CORE_ID_CORE2 * (S4)ERRH_SLG_PEG_AREA_NUM )].u4BaseData & (U4)PEG_PEGBAD_BAD;		/* チャネルベースアドレス設定 */
	t_stProtSet.u4Addv = t_pcstConfigTable[(S4)u1ERRH_SLG_PEG_CH0 + ( (S4)BSW_CORE_ID_CORE2 * (S4)ERRH_SLG_PEG_AREA_NUM )].u4AddvData & (U4)PEG_PEGADV_ADV;		/* チャネル有効ビット設定 */
	t_stProtSet.u4Prot = t_pcstConfigTable[(S4)u1ERRH_SLG_PEG_CH0 + ( (S4)BSW_CORE_ID_CORE2 * (S4)ERRH_SLG_PEG_AREA_NUM )].u4ConfigData;									/* チャネル保護制御 */
	t_stProtSet.u4Spid = t_pcstConfigTable[(S4)u1ERRH_SLG_PEG_CH0 + ( (S4)BSW_CORE_ID_CORE2 * (S4)ERRH_SLG_PEG_AREA_NUM )].u4SpidMapData;									/* チャネル SPID 設定 */
	/* PEG 開始 */									 
	ErrH_Peg_SetModeStartGuard( u1ERRH_SLG_PEG_CH0 ,(U1)BSW_CORE_ID_CORE2 ,&t_stProtSet );
#endif
}

/*----------------------------------------------------------------------------------------------*/
/* ErrH_Crg_Init Function																		*/
/* Return		: none																			*/
/* Parameters	: *ConfigTable(CRG)																*/
/*				: *ConfigTable(CSG)																*/
/*----------------------------------------------------------------------------------------------*/
static	void	ErrH_Slg_Crg_Init( const ErrH_CrgConfigType *t_pcstCrgConfigTable, const ErrH_CrgConfigType *t_pcstCsgConfigTable )
{
	ErrH_CrgProtSetType		t_stProtSet;
	S4						i;

	/*-------------------*/
	/* CRG CRG保護設定 */
	/*-------------------*/
	/* CRG全アクセス許可設定 */
	/* CRGの設定を実施すると、全アクセス不可となるため */
	/* CRGの設定を行う前に全アクセス許可設定を行う	 */
	t_stProtSet.u4Base = u4ERRH_SLG_CRG_ALLRWCRAM0COMBASE;										/* チャネルベースアドレス設定 */
	t_stProtSet.u4Addv = u4ERRH_SLG_CRG_ALLRWCOMADDRDATA;										/* チャネル有効ビット設定 */
	t_stProtSet.u4Prot = u4ERRH_SLG_CRG_ALLRWPROTDATA;											/* チャネル保護制御 */
	t_stProtSet.u4Spid = u4ERRH_SLG_CRG_ALLRWSPIDDATA;											/* チャネル SPID 設定 */
	ErrH_Crg_SetModeStartCrgGuard( u1ERRH_SLG_CRG_CH0 ,(U1)ERRH_SLG_CRAM_CL0 ,&t_stProtSet );
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
	t_stProtSet.u4Base = u4ERRH_SLG_CRG_ALLRWCRAM1COMBASE;										/* チャネルベースアドレス設定 */
	t_stProtSet.u4Addv = u4ERRH_SLG_CRG_ALLRWCOMADDRDATA;										/* チャネル有効ビット設定 */
	t_stProtSet.u4Prot = u4ERRH_SLG_CRG_ALLRWPROTDATA;											/* チャネル保護制御 */
	t_stProtSet.u4Spid = u4ERRH_SLG_CRG_ALLRWSPIDDATA;											/* チャネル SPID 設定 */
	ErrH_Crg_SetModeStartCrgGuard( u1ERRH_SLG_CRG_CH0 ,(U1)ERRH_SLG_CRAM_CL1 ,&t_stProtSet );
#endif

	/* CRG CRAM0設定 *//* 領域1から設定 */
	for ( i = (S4)u1ERRH_SLG_CRG_CH1; i < (S4)ERRH_SLG_CRG_CRG_AREA_NUM; i++ )
	{
		t_stProtSet.u4Base = t_pcstCrgConfigTable[i].u4ComBaseData & (U4)CRG_CRGBAD_BAD;		/* チャネルベースアドレス設定 */
		t_stProtSet.u4Addv = t_pcstCrgConfigTable[i].u4ComAddrData & (U4)CRG_CRGADV_ADV;		/* チャネル有効ビット設定 */
		t_stProtSet.u4Prot	= t_pcstCrgConfigTable[i].u4ProtData;								/* チャネル保護制御 */
		t_stProtSet.u4Spid	= t_pcstCrgConfigTable[i].u4SpidMapData;							/* チャネル SPID 設定 */
		/* CRG 開始 */
		ErrH_Crg_SetModeStartCrgGuard( (U1)i ,(U1)ERRH_SLG_CRAM_CL0 ,&t_stProtSet );
	}

	/* CRG CRAM0の領域0の設定 */
	t_stProtSet.u4Base = t_pcstCrgConfigTable[u1ERRH_SLG_CRG_CH0].u4ComBaseData & (U4)CRG_CRGBAD_BAD;			/* チャネルベースアドレス設定 */
	t_stProtSet.u4Addv = t_pcstCrgConfigTable[u1ERRH_SLG_CRG_CH0].u4ComAddrData & (U4)CRG_CRGADV_ADV;			/* チャネル有効ビット設定 */
	t_stProtSet.u4Prot = t_pcstCrgConfigTable[u1ERRH_SLG_CRG_CH0].u4ProtData;									/* チャネル保護制御 */
	t_stProtSet.u4Spid = t_pcstCrgConfigTable[u1ERRH_SLG_CRG_CH0].u4SpidMapData;									/* チャネル SPID 設定 */
	/* CRG 開始 */
	ErrH_Crg_SetModeStartCrgGuard( u1ERRH_SLG_CRG_CH0 ,(U1)ERRH_SLG_CRAM_CL0 ,&t_stProtSet );


	/* CRG CRAM1設定 *//* 領域1から設定 */
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
	for ( i = (S4)u1ERRH_SLG_CRG_CH1; i < (S4)ERRH_SLG_CRG_CRG_AREA_NUM; i++ )
	{
		t_stProtSet.u4Base = t_pcstCrgConfigTable[i + (S4)ERRH_SLG_CRG_CRG_AREA_NUM].u4ComBaseData & (U4)CRG_CRGBAD_BAD;	/* チャネルベースアドレス設定 */
		t_stProtSet.u4Addv = t_pcstCrgConfigTable[i + (S4)ERRH_SLG_CRG_CRG_AREA_NUM].u4ComAddrData & (U4)CRG_CRGADV_ADV;	/* チャネル有効ビット設定 */
		t_stProtSet.u4Prot = t_pcstCrgConfigTable[i + (S4)ERRH_SLG_CRG_CRG_AREA_NUM].u4ProtData;							/* チャネル保護制御 */
		t_stProtSet.u4Spid = t_pcstCrgConfigTable[i + (S4)ERRH_SLG_CRG_CRG_AREA_NUM].u4SpidMapData;							/* チャネル SPID 設定 */
		/* CRG 開始 */
		ErrH_Crg_SetModeStartCrgGuard( (U1)i ,(U1)ERRH_SLG_CRAM_CL1 ,&t_stProtSet );
	}

	/* CRG CRAM1の領域0の設定 */
	t_stProtSet.u4Base = t_pcstCrgConfigTable[ERRH_SLG_CRG_CRG_AREA_NUM].u4ComBaseData & (U4)CRG_CRGBAD_BAD;	/* チャネルベースアドレス設定 */
	t_stProtSet.u4Addv = t_pcstCrgConfigTable[ERRH_SLG_CRG_CRG_AREA_NUM].u4ComAddrData & (U4)CRG_CRGADV_ADV;	/* チャネル有効ビット設定 */
	t_stProtSet.u4Prot = t_pcstCrgConfigTable[ERRH_SLG_CRG_CRG_AREA_NUM].u4ProtData;							/* チャネル保護制御 */
	t_stProtSet.u4Spid = t_pcstCrgConfigTable[ERRH_SLG_CRG_CRG_AREA_NUM].u4SpidMapData;							/* チャネル SPID 設定 */
	/* CRG 開始 */
	ErrH_Crg_SetModeStartCrgGuard( u1ERRH_SLG_CRG_CH0 ,(U1)ERRH_SLG_CRAM_CL1 ,&t_stProtSet );
#endif

	/*-------------------*/
	/* CRG CSG保護設定 */
	/*-------------------*/
	/* CSG全アクセス許可設定 */
	/* CSGの設定を実施すると、全アクセス不可となるため */
	/* CSGの設定を行う前に全アクセス許可設定を行う	 */
	t_stProtSet.u4Base = u4ERRH_SLG_CRG_ALLRWCRAM0COMBASE;										/* チャネルベースアドレス設定 */
	t_stProtSet.u4Addv = u4ERRH_SLG_CRG_ALLRWCOMADDRDATA;										/* チャネル有効ビット設定 */
	t_stProtSet.u4Prot = u4ERRH_SLG_CRG_ALLRWPROTDATA;											/* チャネル保護制御 */
	t_stProtSet.u4Spid = u4ERRH_SLG_CRG_ALLRWSPIDDATA;											/* チャネル SPID 設定 */
	ErrH_Crg_SetModeStartCsgGuard( u1ERRH_SLG_CRG_CH0 ,(U1)ERRH_SLG_CRAM_CL0 ,&t_stProtSet );
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
	t_stProtSet.u4Base = u4ERRH_SLG_CRG_ALLRWCRAM1COMBASE;										/* チャネルベースアドレス設定 */
	t_stProtSet.u4Addv = u4ERRH_SLG_CRG_ALLRWCOMADDRDATA;										/* チャネル有効ビット設定 */
	t_stProtSet.u4Prot = u4ERRH_SLG_CRG_ALLRWPROTDATA;											/* チャネル保護制御 */
	t_stProtSet.u4Spid = u4ERRH_SLG_CRG_ALLRWSPIDDATA;											/* チャネル SPID 設定 */
	ErrH_Crg_SetModeStartCsgGuard( u1ERRH_SLG_CRG_CH0 ,(U1)ERRH_SLG_CRAM_CL1 ,&t_stProtSet );
#endif

	/* CSG CRAM0設定 *//* 領域1から設定 */
	for ( i = (S4)u1ERRH_SLG_CRG_CH1; i < (S4)ERRH_SLG_CRG_CSG_AREA_NUM; i++ )
	{
		t_stProtSet.u4Base = t_pcstCsgConfigTable[i].u4ComBaseData & (U4)CRG_CRGBAD_BAD;		/* チャネルベースアドレス設定 */
		t_stProtSet.u4Addv = t_pcstCsgConfigTable[i].u4ComAddrData & (U4)CRG_CRGADV_ADV;		/* チャネル有効ビット設定 */
		t_stProtSet.u4Prot	= t_pcstCsgConfigTable[i].u4ProtData;								/* チャネル保護制御 */
		t_stProtSet.u4Spid	= t_pcstCsgConfigTable[i].u4SpidMapData;							/* チャネル SPID 設定 */
		/* CSG 開始 */
		ErrH_Crg_SetModeStartCsgGuard( (U1)i ,(U1)ERRH_SLG_CRAM_CL0 ,&t_stProtSet );
	}

	/* CSG CRAM0の領域0の設定 */
	t_stProtSet.u4Base = t_pcstCsgConfigTable[u1ERRH_SLG_CRG_CH0].u4ComBaseData & (U4)CRG_CRGBAD_BAD;			/* チャネルベースアドレス設定 */
	t_stProtSet.u4Addv = t_pcstCsgConfigTable[u1ERRH_SLG_CRG_CH0].u4ComAddrData & (U4)CRG_CRGADV_ADV;			/* チャネル有効ビット設定 */
	t_stProtSet.u4Prot = t_pcstCsgConfigTable[u1ERRH_SLG_CRG_CH0].u4ProtData;									/* チャネル保護制御 */
	t_stProtSet.u4Spid = t_pcstCsgConfigTable[u1ERRH_SLG_CRG_CH0].u4SpidMapData;									/* チャネル SPID 設定 */
	/* CSG 開始 */
	ErrH_Crg_SetModeStartCsgGuard( u1ERRH_SLG_CRG_CH0 ,(U1)ERRH_SLG_CRAM_CL0 ,&t_stProtSet );


	/* CSG CRAM1設定 *//* 領域1から設定 */
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
	for ( i = (S4)u1ERRH_SLG_CRG_CH1; i < (S4)ERRH_SLG_CRG_CSG_AREA_NUM; i++ )
	{
		t_stProtSet.u4Base = t_pcstCsgConfigTable[i + (S4)ERRH_SLG_CRG_CSG_AREA_NUM].u4ComBaseData & (U4)CRG_CRGBAD_BAD;	/* チャネルベースアドレス設定 */
		t_stProtSet.u4Addv = t_pcstCsgConfigTable[i + (S4)ERRH_SLG_CRG_CSG_AREA_NUM].u4ComAddrData & (U4)CRG_CRGADV_ADV;	/* チャネル有効ビット設定 */
		t_stProtSet.u4Prot = t_pcstCsgConfigTable[i + (S4)ERRH_SLG_CRG_CSG_AREA_NUM].u4ProtData;							/* チャネル保護制御 */
		t_stProtSet.u4Spid = t_pcstCsgConfigTable[i + (S4)ERRH_SLG_CRG_CSG_AREA_NUM].u4SpidMapData;							/* チャネル SPID 設定 */
		/* CSG 開始 */
		ErrH_Crg_SetModeStartCsgGuard( (U1)i ,(U1)ERRH_SLG_CRAM_CL1 ,&t_stProtSet );
	}

	/* CSG CRAM1の領域0の設定 */
	t_stProtSet.u4Base = t_pcstCsgConfigTable[ERRH_SLG_CRG_CSG_AREA_NUM].u4ComBaseData & (U4)CRG_CRGBAD_BAD;	/* チャネルベースアドレス設定 */
	t_stProtSet.u4Addv = t_pcstCsgConfigTable[ERRH_SLG_CRG_CSG_AREA_NUM].u4ComAddrData & (U4)CRG_CRGADV_ADV;	/* チャネル有効ビット設定 */
	t_stProtSet.u4Prot = t_pcstCsgConfigTable[ERRH_SLG_CRG_CSG_AREA_NUM].u4ProtData;							/* チャネル保護制御 */
	t_stProtSet.u4Spid = t_pcstCsgConfigTable[ERRH_SLG_CRG_CSG_AREA_NUM].u4SpidMapData;							/* チャネル SPID 設定 */
	/* CSG 開始 */
	ErrH_Crg_SetModeStartCsgGuard( u1ERRH_SLG_CRG_CH0 ,(U1)ERRH_SLG_CRAM_CL1 ,&t_stProtSet );
#endif
}

/*----------------------------------------------------------------------------------------------*/
/* ErrH_Pbg_Init Function																		*/
/* Return		: none																			*/
/* Parameters	: *ConfigTable																	*/
/*----------------------------------------------------------------------------------------------*/
static	void	ErrH_Slg_Pbg_Init( const ErrH_PbgConfigType *t_pcstConfigTable )
{
	const	ErrH_PbgGpDataDefType*	t_pcstGpDataConfig;
	S4		i;
	S4		j;
	U4		t_u4ProtData;			/* 設定データ(PROT) */
	U4		t_u4SpidData;			/* 設定データ(SPID) */
	U1		t_u1GpDataNum;			/* 使用するグループ数 */
	U1		t_u1GroupNum;			/* グループ番号 */

	/* グループ数を取得 */
	t_u1GpDataNum = t_pcstConfigTable->u1GroupDataNum;

	/* CH設定 */
	for ( i = (S4)0; i < (S4)t_u1GpDataNum; i++ )
	{
		t_u1GroupNum		=	t_pcstConfigTable->pstGpDataConfig[i].u1GroupNum;			/* グループNo */
		t_pcstGpDataConfig	=	&(t_pcstConfigTable->pstGpDataConfig[i]);					/* グループ情報 */
		for ( j = (S4)0; j < (S4)ERRH_SLG_PBG_CHANNEL_NUM; j++ )
		{
			t_u4ProtData	=	t_pcstGpDataConfig->pstChDataConfig[j].u4ProtData;			/* チャネル保護制御 */
			t_u4SpidData	=	t_pcstGpDataConfig->pstChDataConfig[j].u4SpidData;			/* チャネル SPID 設定 */
			if( ( t_u4ProtData & (U4)PBG_PBGPROT0_GEN ) == (U4)PBG_PBGPROT0_GEN )
			{
				ErrH_Pbg_SetModeStartGuard( t_u1GroupNum ,(U1)j ,t_u4ProtData ,t_u4SpidData );
			}
		}
	}

}

/*----------------------------------------------------------------------------------------------*/
/* SLG Hbg Disable All Guard Function															*/
/* Return		: none																			*/
/* Parameters	: none																			*/
/*----------------------------------------------------------------------------------------------*/
static	void	ErrH_Slg_Hbg_DisableAllGuard( void )
{
	S4								i;
	volatile Reg_Hbg_HbgType*		t_pstReg_Hbg;
	volatile Reg_Hbg_HbgErrSlvType*	t_pstReg_HbgErrSlv;

	/* HBGレジスタのKey Code Protection解除 */
	for( i = (S4)0; i < (S4)u1ERRH_SLG_HBG_CHANNEL_NUM; i++ )
	{
		t_pstReg_HbgErrSlv = (volatile Reg_Hbg_HbgErrSlvType*)pcstReg_HbgErrSlv[i];
		t_pstReg_HbgErrSlv->unHBGKCPROT.u4Data = (U4)HBG_HBGKCPROT_KCE_ENABLE;
		Bswlib_Sync_Pipeline_4( t_pstReg_HbgErrSlv->unHBGKCPROT.u4Data );
	}

	/* HBGの保護無効化 */
	for( i = (S4)0; i < (S4)u1ERRH_SLG_HBG_CHANNEL_NUM; i++ )
	{
		t_pstReg_Hbg = (volatile Reg_Hbg_HbgType*)pcstReg_Hbg[i];
		t_pstReg_Hbg->unHBGPROT0.u4Data = u4ERRH_SLG_HBG_NO_GUARD;
		Bswlib_Sync_Pipeline_4( t_pstReg_Hbg->unHBGPROT0.u4Data );
	}

	/* HBGレジスタのKey Code Protection再開 */
	for( i = (S4)0; i < (S4)u1ERRH_SLG_HBG_CHANNEL_NUM; i++ )
	{
		t_pstReg_HbgErrSlv = (volatile Reg_Hbg_HbgErrSlvType*)pcstReg_HbgErrSlv[i];
		t_pstReg_HbgErrSlv->unHBGKCPROT.u4Data = (U4)HBG_HBGKCPROT_KCE_DISABLE;
		Bswlib_Sync_Pipeline_4( t_pstReg_HbgErrSlv->unHBGKCPROT.u4Data );
	}
}

/*----------------------------------------------------------------------------------------------*/
/* General compare 4 byte register with mask Function											*/
/* return		: Register Check Result															*/
/* parameters	: Address(Sync)																	*/
/*				: Expected value																*/
/*				: Mask(0xXXXXXXXX <0:no compare / 1:compare>)									*/
/*----------------------------------------------------------------------------------------------*/
static U1		ErrH_Slg_Compare4ByteMask( volatile const U4 *t_pcu4Address, U4 t_u4ExpectedValue, U4 t_u4Mask )
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
/* PEG restore 4 byte register with mask Function (PEG Core0 Protection Release)				*/
/* return		: none																			*/
/* parameters	: Address(Sync)																	*/
/*				: Expected value																*/
/*				: Mask(0xXXXXXXXX <0:no restore / 1:restore>)									*/
/*----------------------------------------------------------------------------------------------*/
static void	ErrH_Slg_Reg_RestorePegCore0Prot4ByteMask( volatile U4 *t_pu4Address, U4 t_u4ExpectedValue, U4 t_u4Mask )
{
	U4							t_u4Exp;
	U4							t_u4Val;

	t_u4Exp = t_u4ExpectedValue & t_u4Mask;
	
	t_u4Val = *t_pu4Address;
	
	/* 1.PEGKCPROT - PE ガードキーコード保護レジスタ 保護解除 */
	Reg_PEG_GUARDPE0CL0.unPEGKCPROT.u4Data = (U4)PEG_PEGKCPROT_KCE_ENABLE;

	/* 2 Set Config Data */
	*t_pu4Address = ( t_u4Val & (U4)(~t_u4Mask) ) | t_u4Exp;

	/* 3.PEGKCPROT - PE ガードキーコード保護レジスタ 保護設定 */
	Reg_PEG_GUARDPE0CL0.unPEGKCPROT.u4Data = (U4)PEG_PEGKCPROT_KCE_DISABLE;
	Bswlib_Sync_Pipeline_4( Reg_PEG_GUARDPE0CL0.unPEGKCPROT.u4Data );
}

/*----------------------------------------------------------------------------------------------*/
/* PEG restore 4 byte register with mask Function (PEG Core1 Protection Release)				*/
/* return		: none																			*/
/* parameters	: Address(Sync)																	*/
/*				: Expected value																*/
/*				: Mask(0xXXXXXXXX <0:no restore / 1:restore>)									*/
/*----------------------------------------------------------------------------------------------*/
static void	ErrH_Slg_Reg_RestorePegCore1Prot4ByteMask( volatile U4 *t_pu4Address, U4 t_u4ExpectedValue, U4 t_u4Mask )
{
	U4							t_u4Exp;
	U4							t_u4Val;

	t_u4Exp = t_u4ExpectedValue & t_u4Mask;
	
	t_u4Val = *t_pu4Address;
	
	/* 1.PEGKCPROT - PE ガードキーコード保護レジスタ 保護解除 */
	Reg_PEG_GUARDPE1CL0.unPEGKCPROT.u4Data = (U4)PEG_PEGKCPROT_KCE_ENABLE;

	/* 2 Set Config Data */
	*t_pu4Address = ( t_u4Val & (U4)(~t_u4Mask) ) | t_u4Exp;

	/* 3.PEGKCPROT - PE ガードキーコード保護レジスタ 保護設定 */
	Reg_PEG_GUARDPE1CL0.unPEGKCPROT.u4Data = (U4)PEG_PEGKCPROT_KCE_DISABLE;
	Bswlib_Sync_Pipeline_4( Reg_PEG_GUARDPE1CL0.unPEGKCPROT.u4Data );
}

/*----------------------------------------------------------------------------------------------*/
/* PEG restore 4 byte register with mask Function (PEG Core2 Protection Release)				*/
/* return		: none																			*/
/* parameters	: Address(Sync)																	*/
/*				: Expected value																*/
/*				: Mask(0xXXXXXXXX <0:no restore / 1:restore>)									*/
/*----------------------------------------------------------------------------------------------*/
static void	ErrH_Slg_Reg_RestorePegCore2Prot4ByteMask( volatile U4 *t_pu4Address, U4 t_u4ExpectedValue, U4 t_u4Mask )
{
	U4							t_u4Exp;
	U4							t_u4Val;

	t_u4Exp = t_u4ExpectedValue & t_u4Mask;
	
	t_u4Val = *t_pu4Address;
	
	/* 1.PEGKCPROT - PE ガードキーコード保護レジスタ 保護解除 */
	Reg_PEG_GUARDPE2CL1.unPEGKCPROT.u4Data = (U4)PEG_PEGKCPROT_KCE_ENABLE;

	/* 2 Set Config Data */
	*t_pu4Address = ( t_u4Val & (U4)(~t_u4Mask) ) | t_u4Exp;

	/* 3.PEGKCPROT - PE ガードキーコード保護レジスタ 保護設定 */
	Reg_PEG_GUARDPE2CL1.unPEGKCPROT.u4Data = (U4)PEG_PEGKCPROT_KCE_DISABLE;
	Bswlib_Sync_Pipeline_4( Reg_PEG_GUARDPE2CL1.unPEGKCPROT.u4Data );
}

/*----------------------------------------------------------------------------------------------*/
/* PEG restore 4 byte register with mask Function (PEG Core3 Protection Release)				*/
/* return		: none																			*/
/* parameters	: Address(Sync)																	*/
/*				: Expected value																*/
/*				: Mask(0xXXXXXXXX <0:no restore / 1:restore>)									*/
/*----------------------------------------------------------------------------------------------*/
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
static void	ErrH_Slg_Reg_RestorePegCore3Prot4ByteMask( volatile U4 *t_pu4Address, U4 t_u4ExpectedValue, U4 t_u4Mask )
{
	U4							t_u4Exp;
	U4							t_u4Val;

	t_u4Exp = t_u4ExpectedValue & t_u4Mask;
	
	t_u4Val = *t_pu4Address;
	
	/* 1.PEGKCPROT - PE ガードキーコード保護レジスタ 保護解除 */
	Reg_PEG_GUARDPE3CL1.unPEGKCPROT.u4Data = (U4)PEG_PEGKCPROT_KCE_ENABLE;

	/* 2 Set Config Data */
	*t_pu4Address = ( t_u4Val & (U4)(~t_u4Mask) ) | t_u4Exp;

	/* 3.PEGKCPROT - PE ガードキーコード保護レジスタ 保護設定 */
	Reg_PEG_GUARDPE3CL1.unPEGKCPROT.u4Data = (U4)PEG_PEGKCPROT_KCE_DISABLE;
	Bswlib_Sync_Pipeline_4( Reg_PEG_GUARDPE3CL1.unPEGKCPROT.u4Data );
}
#endif

/*----------------------------------------------------------------------------------------------*/
/* CRG restore 4 byte register with mask Function (CRG CL0 Protection Release)					*/
/* return		: none																			*/
/* parameters	: Address(Sync)																	*/
/*				: Expected value																*/
/*				: Mask(0xXXXXXXXX <0:no restore / 1:restore>)									*/
/*----------------------------------------------------------------------------------------------*/
static void	ErrH_Slg_Reg_RestoreCrgCl0Prot4ByteMask( volatile U4 *t_pu4Address, U4 t_u4ExpectedValue, U4 t_u4Mask )
{
	U4							t_u4Exp;
	U4							t_u4Val;

	t_u4Exp = t_u4ExpectedValue & t_u4Mask;
	
	t_u4Val = *t_pu4Address;
	
	/* 1.CRGKCPROT - クラスタRAM ガードキーコード保護レジスタ 保護解除 */
	Reg_CRG_GUARDCRAMCRG0.unCRGKCPROT.u4Data = (U4)CRG_CRGKCPROT_KCE_ENABLE;

	/* 2 Set Config Data */
	*t_pu4Address = ( t_u4Val & (U4)(~t_u4Mask) ) | t_u4Exp;

	/* 3.CRGKCPROT - クラスタRAM ガードキーコード保護レジスタ 保護設定 */
	Reg_CRG_GUARDCRAMCRG0.unCRGKCPROT.u4Data = (U4)CRG_CRGKCPROT_KCE_DISABLE;
	Bswlib_Sync_Pipeline_4( Reg_CRG_GUARDCRAMCRG0.unCRGKCPROT.u4Data );
}

/*----------------------------------------------------------------------------------------------*/
/* CRG restore 4 byte register with mask Function (CRG CL1 Protection Release)					*/
/* return		: none																			*/
/* parameters	: Address(Sync)																	*/
/*				: Expected value																*/
/*				: Mask(0xXXXXXXXX <0:no restore / 1:restore>)									*/
/*----------------------------------------------------------------------------------------------*/
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
static void	ErrH_Slg_Reg_RestoreCrgCl1Prot4ByteMask( volatile U4 *t_pu4Address, U4 t_u4ExpectedValue, U4 t_u4Mask )
{
	U4							t_u4Exp;
	U4							t_u4Val;

	t_u4Exp = t_u4ExpectedValue & t_u4Mask;
	
	t_u4Val = *t_pu4Address;
	
	/* 1.CRGKCPROT - クラスタRAM ガードキーコード保護レジスタ 保護解除 */
	Reg_CRG_GUARDCRAMCRG1.unCRGKCPROT.u4Data = (U4)CRG_CRGKCPROT_KCE_ENABLE;

	/* 2 Set Config Data */
	*t_pu4Address = ( t_u4Val & (U4)(~t_u4Mask) ) | t_u4Exp;

	/* 3.CRGKCPROT - クラスタRAM ガードキーコード保護レジスタ 保護設定 */
	Reg_CRG_GUARDCRAMCRG1.unCRGKCPROT.u4Data = (U4)CRG_CRGKCPROT_KCE_DISABLE;
	Bswlib_Sync_Pipeline_4( Reg_CRG_GUARDCRAMCRG1.unCRGKCPROT.u4Data );
}
#endif

/*----------------------------------------------------------------------------------------------*/
/* PBG restore 4 byte register with mask Function (PBG 50 Protection Release)					*/
/* return		: none																			*/
/* parameters	: Address(Sync)																	*/
/*				: Expected value																*/
/*				: Mask(0xXXXXXXXX <0:no restore / 1:restore>)									*/
/*----------------------------------------------------------------------------------------------*/
static void	ErrH_Slg_Reg_RestorePbg50Prot4ByteMask( volatile U4 *t_pu4Address, U4 t_u4ExpectedValue, U4 t_u4Mask )
{
	U4							t_u4Exp;
	U4							t_u4Val;


	t_u4Exp = t_u4ExpectedValue & t_u4Mask;
	
	t_u4Val = *t_pu4Address;
	
	/* 1.PBGKCPROT - PB ガードキーコード保護レジスタ 保護解除 */
	Reg_PBG_PBGERRSLV50.unPBGKCPROT.u4Data = (U4)PBG_PBGKCPROT_KCE_ENABLE;

	/* 2 Set Config Data */
	*t_pu4Address = ( t_u4Val & (U4)(~t_u4Mask) ) | t_u4Exp;

	/* 3.PBGKCPROT - PB ガードキーコード保護レジスタ 保護設定 */
	Reg_PBG_PBGERRSLV50.unPBGKCPROT.u4Data = (U4)PBG_PBGKCPROT_KCE_DISABLE;
	Bswlib_Sync_Pipeline_4( Reg_PBG_PBGERRSLV50.unPBGKCPROT.u4Data );
}

#pragma ghs section text=default

#endif // zantei MPUは2月末非対応
/*-- End Of File -------------------------------------------------------------------------------*/
