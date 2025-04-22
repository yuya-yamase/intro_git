/* ErrH-r04-3000-0200-b-v00 */
/************************************************************************************************/
/*																								*/
/*		ErrH Driver																				*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

/*==============================================================================================*/
/*	include files																				*/
/*==============================================================================================*/
#include	"Std_Types.h"
#include	"Mcal_SpalCmn.h"
#include	"bswlib.h"

#include	"ErrH_cfg.h"
#include	"ErrH_mcu_def.h"

#include	"ErrH.h"

#include	"ErrH_Ecm.h"
#include	"ErrH_slg.h"
#include	"ErrH_Ecc.h"
#include	"ErrH_Bist.h"

/*==============================================================================================*/
/*	prototypes																					*/
/*==============================================================================================*/

/*==============================================================================================*/
/*	defines / data types / structs / unions	/ macros											*/
/*==============================================================================================*/
#define	u1ERRH_REGCHECK_STS_COMPLETED		((U1)0U)					/* レジスタ診断開始待ち */
#define	u1ERRH_REGCHECK_STS_BUSY_ECM		((U1)1U)					/* ECM診断中 */
#define	u1ERRH_REGCHECK_STS_BUSY_ECC		((U1)2U)					/* ECC診断中 */
#define	u1ERRH_REGCHECK_STS_BUSY_SLG		((U1)3U)					/* SLG診断中 */

#define	u1ERRH_CHECKRESULT_RSHIFT_4BIT		((U1)4U)					/* 4bit右シフト */
#define	u1ERRH_CHECKRESULT_MASK_LOWER4BIT	((U1)0x0FU)					/* 下位4bitマスク(0～3bit) */

/*==============================================================================================*/
/*	constants																					*/
/*==============================================================================================*/

/*==============================================================================================*/
/*	variables																					*/
/*==============================================================================================*/
#pragma ghs section bss=".ERRH_BSS_VAR_NO_INIT"
// zantei MPUは2月末非対応  static	U4		s_u4ErrH_MpuErrorAddress[MCU_CORE_NUM];		/* MPUエラーアドレス */

static	volatile	U1	s_u1ErrH_RegCheckStatus;	/* レジスタ診断ステータス */ /* 干渉対策のため、ErrH_CheckReg_ASIL()のみからライトすること */
#pragma ghs section bss=default

/*==============================================================================================*/
/* functions																					*/
/*==============================================================================================*/
#pragma ghs section text=".ERRH_TEXT_CODE"
/*----------------------------------------------------------------------------------------------*/
/* API Functions																				*/
/*----------------------------------------------------------------------------------------------*/

#if 0 // zantei MPUは2月末非対応
/*----------------------------------------------------------------------------------------------*/
/* Get MIPMDP Error Address																		*/
/* return		: Error Address																	*/
/* parameters	: none																			*/
/*----------------------------------------------------------------------------------------------*/
U4		ErrH_GetMipMdpAddress( void )
{
	U4							t_u4CoreId;				/* CoreID格納 */
	U4							t_u4ErrorAddress;		/* 異常発生時メモリエラーアドレス */

	/* 返り値に初期値を設定 */
	t_u4ErrorAddress = (U4)ERRH_ERROR_ADDRESS_NORMAL;

	/* Core毎に異常発生時メモリエラーアドレスを保持しているため	 */
	/* 呼び出されたCoreを判別する								 */
	t_u4CoreId = Bswlib_GetCoreId();

	/* 存在するCoreでない場合には、返り値は初期値のままとする */
	if( t_u4CoreId < MCU_CORE_NUM )
	{
		/* 戻り値にCoreに対応した異常発生時メモリエラーアドレスを格納する */
		t_u4ErrorAddress = s_u4ErrH_MpuErrorAddress[ t_u4CoreId ];
	}

	/* 異常発生時のメモリエラーアドレスを返却する */
	return( t_u4ErrorAddress );
}

/*----------------------------------------------------------------------------------------------*/
/* SlaveGuard Clear Error Function																*/
/* Return		: none																			*/
/* Parameters	: ErrorID																		*/
/*				: ModuleNumber																	*/
/*----------------------------------------------------------------------------------------------*/
void	ErrH_ClearSlgErr( U2 t_u2ErrorID, U2 t_u2ModuleNum )
{
	/* エラークリア実施 */
	ErrH_Slg_ClearError( t_u2ErrorID, t_u2ModuleNum );
}

/*----------------------------------------------------------------------------------------------*/
/* SlaveGuard Get Error Status Function															*/
/* Return		: Error Status																	*/
/* Parameters	: ErrorID																		*/
/*				: ModuleNumber																	*/
/*----------------------------------------------------------------------------------------------*/
U4	ErrH_GetSlgErrStatus( U2 t_u2ErrorID, U2 t_u2ModuleNum )
{
	U4	t_u4ErrorStatus;			/* エラーステータス取得結果 */

	/* エラーステータス取得 */
	t_u4ErrorStatus = ErrH_Slg_GetErrStatus( t_u2ErrorID, t_u2ModuleNum );

	return ( t_u4ErrorStatus ) ;
}

/*----------------------------------------------------------------------------------------------*/
/* SlaveGuard Get Error Address Function														*/
/* Return		: Error Address																	*/
/* Parameters	: ErrorID																		*/
/*				: ModuleNumber																	*/
/*----------------------------------------------------------------------------------------------*/
U4	ErrH_GetSlgErrAddress( U2 t_u2ErrorID, U2 t_u2ModuleNum )
{
	U4	t_u4ErrorAddress;			/* エラーアドレス取得結果 */

	/* エラーアドレス取得 */
	t_u4ErrorAddress = ErrH_Slg_GetErrAddress( t_u2ErrorID, t_u2ModuleNum );

	return ( t_u4ErrorAddress ) ;
}

/*----------------------------------------------------------------------------------------------*/
/* SlaveGuard Get Error Access info Function													*/
/* Return		: Error Access info																*/
/* Parameters	: ErrorID																		*/
/*				: ModuleNumber																	*/
/*----------------------------------------------------------------------------------------------*/
U4	ErrH_GetSlgErrAccessInfo( U2 t_u2ErrorID, U2 t_u2ModuleNum )
{
	U4	t_u4ErrorAcessInfo;			/* エラーアクセス情報取得結果 */

	/* エラーアクセス情報取得 */
	t_u4ErrorAcessInfo = ErrH_Slg_GetErrAccessInfo( t_u2ErrorID, t_u2ModuleNum );

	return ( t_u4ErrorAcessInfo ) ;
}
#endif // zantei MPUは2月末非対応

#if 0 // zantei ECCは2月末非対応
/*----------------------------------------------------------------------------------------------*/
/*	ECC 1bit Error Clear																		*/
/*	return		: none																			*/
/*	parameters	: ModuleNumber																	*/
/*----------------------------------------------------------------------------------------------*/
void	ErrH_ClearEcc1bitErr( U1 t_u1ModuleNum )
{
	ErrH_Ecc_ClearEcc1bitErr( t_u1ModuleNum );
}

/*----------------------------------------------------------------------------------------------*/
/*	ECC Fatal Error Clear																		*/
/*	return		: none																			*/
/*	parameters	: ModuleNumber																	*/
/*----------------------------------------------------------------------------------------------*/
void	ErrH_ClearEccFatalErr( U1 t_u1ModuleNum )
{
	ErrH_Ecc_ClearEccFatalErr( t_u1ModuleNum );
}

/*----------------------------------------------------------------------------------------------*/
/*	ECC 1bit Error Status Get																	*/
/*	return		: ErrorStatus																	*/
/*	parameters	: ModuleNumber																	*/
/*----------------------------------------------------------------------------------------------*/
U1		ErrH_GetEcc1bitErrStatus( U1 t_u1ModuleNum )
{
	U1	t_u1ErrorStatus;

	t_u1ErrorStatus = ErrH_Ecc_GetEcc1bitErrStatus( t_u1ModuleNum );

	return ( t_u1ErrorStatus );
}

/*----------------------------------------------------------------------------------------------*/
/*	ECC Fatal Error Status Get																	*/
/*	return		: ErrorStatus																	*/
/*	parameters	: ModuleNumber																	*/
/*----------------------------------------------------------------------------------------------*/
U1		ErrH_GetEccFatalErrStatus( U1 t_u1ModuleNum )
{
	U1	t_u1ErrorStatus;

	t_u1ErrorStatus = ErrH_Ecc_GetEccFatalErrStatus( t_u1ModuleNum );

	return ( t_u1ErrorStatus );
}

/*----------------------------------------------------------------------------------------------*/
/*	ECC Overflow Status Get																		*/
/*	return		: OverflowStatus																*/
/*	parameters	: ModuleNumber																	*/
/*----------------------------------------------------------------------------------------------*/
U1		ErrH_GetEccOvfStatus( U1 t_u1ModuleNum )
{
	U1	t_u1OverflowStatus;

	t_u1OverflowStatus = ErrH_Ecc_GetEccOvfStatus( t_u1ModuleNum );

	return ( t_u1OverflowStatus );
}

/*----------------------------------------------------------------------------------------------*/
/*	ECC 1bit Error Address Get																	*/
/*	return		: none																			*/
/*	parameters	: ModuleNumber, Address(Sync), ArrayNum											*/
/*----------------------------------------------------------------------------------------------*/
void	ErrH_GetEcc1bitErrAddr( U1 t_u1ModuleNum, U4* t_pu4Address, U1 t_u1ArrayNum )
{
	ErrH_Ecc_GetEcc1bitErrAddr( t_u1ModuleNum, t_pu4Address, t_u1ArrayNum );
}

/*----------------------------------------------------------------------------------------------*/
/*	ECC Fatal Error Address Get																	*/
/*	return		: ErrorAddress																	*/
/*	parameters	: ModuleNumber																	*/
/*----------------------------------------------------------------------------------------------*/
U4		ErrH_GetEccFatalErrAddr( U1 t_u1ModuleNum )
{
	U4	t_u4ErrorAddress;

	t_u4ErrorAddress = ErrH_Ecc_GetEccFatalErrAddr( t_u1ModuleNum );

	return ( t_u4ErrorAddress );
}

/*----------------------------------------------------------------------------------------------*/
/*	ECC 1bit Error Detailed Information Get														*/
/*	return		: none																			*/
/*	parameters	: ModuleNumber, DetailInformation(Sync), ArrayNum								*/
/*----------------------------------------------------------------------------------------------*/
void	ErrH_GetEcc1bitErrDetail( U1 t_u1ModuleNum, U1* t_pu1DetailInfo, U1 t_u1ArrayNum )
{
	ErrH_Ecc_GetEcc1bitErrDetail( t_u1ModuleNum, t_pu1DetailInfo, t_u1ArrayNum );
}

/*----------------------------------------------------------------------------------------------*/
/*	ECC Fatal Error Detailed Information Get													*/
/*	return		: ErrorDetailInformation														*/
/*	parameters	: ModuleNumber																	*/
/*----------------------------------------------------------------------------------------------*/
U1		ErrH_GetEccFatalErrDetail( U1 t_u1ModuleNum )
{
	U1	t_u1ErrorDetailInfo;

	t_u1ErrorDetailInfo = ErrH_Ecc_GetEccFatalErrDetail( t_u1ModuleNum );

	return ( t_u1ErrorDetailInfo );
}

/*----------------------------------------------------------------------------------------------*/
/*	ECC 1bit Error SPID Get																		*/
/*	return		: none																			*/
/*	parameters	: ModuleNumber, ErrorSPID(Sync), ArrayNum										*/
/*----------------------------------------------------------------------------------------------*/
void	ErrH_GetEcc1bitErrSpid( U1 t_u1ModuleNum, U4* t_pu4ErrSpid, U1 t_u1ArrayNum )
{
	ErrH_Ecc_GetEcc1bitErrSpid( t_u1ModuleNum, t_pu4ErrSpid, t_u1ArrayNum );
}

/*----------------------------------------------------------------------------------------------*/
/*	ECC Fatal Error SPID Get																	*/
/*	return		: ErrorSPID																		*/
/*	parameters	: ModuleNumber																	*/
/*----------------------------------------------------------------------------------------------*/
U4		ErrH_GetEccFatalErrSpid( U1 t_u1ModuleNum )
{
	U4	t_u4ErrorSpid;

	t_u4ErrorSpid = ErrH_Ecc_GetEccFatalErrSpid( t_u1ModuleNum );

	return ( t_u4ErrorSpid );
}

/*----------------------------------------------------------------------------------------------*/
/*	ECC/EDC Stop Function																		*/
/*	return		: none																			*/
/*	parameters	: none																			*/
/*----------------------------------------------------------------------------------------------*/
void	ErrH_StopEccEdc( void )
{
	ErrH_Ecc_StopEccEdc();
}
#endif // zantei ECCは2月末非対応

/*----------------------------------------------------------------------------------------------*/
/* BIST Register Value Get Function																*/
/* return		: Register Value																*/
/* parameters	: Register No																	*/
/*----------------------------------------------------------------------------------------------*/
U4	ErrH_GetBistRegValue( U1 t_u1RegNo )
{
	U4	t_u4RegisterValue;

	t_u4RegisterValue = ErrH_Bist_GetBistRegValue( t_u1RegNo );

	return ( t_u4RegisterValue );
}

#if 0 // zantei ECCは2月末非対応
/*----------------------------------------------------------------------------------------------*/
/*	Clear ECC Error Status Function																*/
/*	return		: none																			*/
/*	parameters	: RAM Type																		*/
/*----------------------------------------------------------------------------------------------*/
void	ErrH_ClearEccErrorStatus( U1 t_u1RamType )
{
	ErrH_Ecc_ClearEccErrorStatus( t_u1RamType );
}

/*----------------------------------------------------------------------------------------------*/
/*	Get ECC Error Status Function																*/
/*	return		: Error Detect Status(=0:not error detect, !=0:error detect)					*/
/*	parameters	: RAM Type																		*/
/*----------------------------------------------------------------------------------------------*/
ZORN	ErrH_GetEccErrorStatus( U1 t_u1RamType )
{
	ZORN	t_udErrDtctStatus;

	t_udErrDtctStatus = ErrH_Ecc_GetEccErrorStatus( t_u1RamType );

	return ( t_udErrDtctStatus );
}

/*----------------------------------------------------------------------------------------------*/
/*	Clear ROM Ecc Ecm Error Status Function														*/
/*	return		: none																			*/
/*	parameters	: none																			*/
/*----------------------------------------------------------------------------------------------*/
void	ErrH_ClearRomEccEcmErrorStatus( void )
{
	ErrH_Ecm_ClearErrorStatus( u2ERRH_NCF104_ID );
	ErrH_Ecm_ClearErrorStatus( u2ERRH_NCF105_ID );
	ErrH_Ecc_ClearEccFatalErr( u1ERRH_ECC_CF );
}
#endif // zantei ECCは2月末非対応

#if 0 // zantei REGCHKは2月末非対応
/*----------------------------------------------------------------------------------------------*/
/*	Request Register Check Function																*/
/*	return		: Register Check Result															*/
/*	parameters	: none																			*/
/*----------------------------------------------------------------------------------------------*/
U1	ErrH_CheckReg_ASIL( void )
{
	U1		t_u1Result;									/* 戻り値 */
	U1		t_u1RegCheckStatus;							/* レジスタ診断ステータス */
	U1		t_u1RegCheckStatusSubMod;					/* レジスタ診断ステータス(サブモジュール) */

	t_u1Result = (U1)OK;								/* 戻り値初期化(=0:異常なし) */

	if ( s_u1ErrH_RegCheckStatus == u1ERRH_REGCHECK_STS_COMPLETED )
	{
		s_u1ErrH_RegCheckStatus = u1ERRH_REGCHECK_STS_BUSY_ECM;
	}

	t_u1RegCheckStatus = s_u1ErrH_RegCheckStatus;

	switch ( t_u1RegCheckStatus )
	{
		case u1ERRH_REGCHECK_STS_BUSY_ECM:
			t_u1Result = ErrH_Ecm_CheckReg_ASIL( cstErrH_UcfgData.pcstEcmRegCheckCfg );
			t_u1RegCheckStatusSubMod = t_u1Result >> u1ERRH_CHECKRESULT_RSHIFT_4BIT;	/* 診断結果の4～7bit抽出 */

			if ( t_u1RegCheckStatusSubMod == u1ERRH_REGCHECK_COMPLETED )
			{
				s_u1ErrH_RegCheckStatus = u1ERRH_REGCHECK_STS_BUSY_ECC;
			}
			break;

		case u1ERRH_REGCHECK_STS_BUSY_ECC:
			t_u1Result = ErrH_Ecc_CheckReg_ASIL( cstErrH_UcfgData.pcstEccRegCheckCfg );
			t_u1RegCheckStatusSubMod = t_u1Result >> u1ERRH_CHECKRESULT_RSHIFT_4BIT;	/* 診断結果の4～7bit抽出 */

			if ( t_u1RegCheckStatusSubMod == u1ERRH_REGCHECK_COMPLETED )
			{
				s_u1ErrH_RegCheckStatus = u1ERRH_REGCHECK_STS_BUSY_SLG;
			}
			break;

		case u1ERRH_REGCHECK_STS_BUSY_SLG:
			t_u1Result = ErrH_Slg_CheckReg_ASIL( cstErrH_UcfgData.pcstSlgRegCheckCfg );
			t_u1RegCheckStatusSubMod = t_u1Result >> u1ERRH_CHECKRESULT_RSHIFT_4BIT;	/* 診断結果の4～7bit抽出 */

			if ( t_u1RegCheckStatusSubMod == u1ERRH_REGCHECK_COMPLETED )
			{
				s_u1ErrH_RegCheckStatus = u1ERRH_REGCHECK_STS_COMPLETED;
			}
			break;

		default:
			s_u1ErrH_RegCheckStatus = u1ERRH_REGCHECK_STS_COMPLETED;															/* ErrHレジスタ診断ステータスが化けて想定外の値となった場合は、診断開始待ちに戻す */
			break;
	}
	
	t_u1Result = t_u1Result & u1ERRH_CHECKRESULT_MASK_LOWER4BIT;																/* 診断結果の0～3bit抽出 */

	return( t_u1Result );
}

/*----------------------------------------------------------------------------------------------*/
/*	Get Register Check Status Function															*/
/*	return		: Register Check Status															*/
/*	parameters	: none																			*/
/*----------------------------------------------------------------------------------------------*/
U1	ErrH_GetRegStatus_ASIL  ( void )
{
	U1		t_u1Result;										/* 戻り値 */

	if ( s_u1ErrH_RegCheckStatus == u1ERRH_REGCHECK_STS_COMPLETED ) 
	{
		t_u1Result = u1ERRH_REGCHECK_COMPLETED;				/* レジスタ診断開始待ち */ 
	}
	else
	{
		t_u1Result = u1ERRH_REGCHECK_BUSY;					/* レジスタ診断中 */
	}

	return( t_u1Result );
}
#endif // zantei REGCHKは2月末非対応

/*----------------------------------------------------------------------------------------------*/
/* Scheduled / Event Functions																	*/
/*----------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------*/
/* Initialization in Boot Function																*/
/* Return		: none																			*/
/* Parameters	: CoreId																		*/
/*----------------------------------------------------------------------------------------------*/
void	ErrH_InitBoot( U4 t_u4CoreId )
{
	/* Core0での処理 */
	if ( t_u4CoreId == MCU_CORE_0 )
	{
// zantei MPUは2月末非対応		ErrH_Slg_DisableAllGuard();					/* Slave Guardの保護無効化 */
	}
	/* Core0以外の処理 */
	else
	{
		/* 処理なし */
	}
}

/*----------------------------------------------------------------------------------------------*/
/* Initialization Function																		*/
/* Return		: none																			*/
/* Parameters	: none																			*/
/*----------------------------------------------------------------------------------------------*/
void	ErrH_Init_0( void )
{
	U4							t_u4CoreId;				/* CoreID格納 */

	/* マルチコアになったことにより、 */
	/* Core毎に実行される処理が異なることを考慮し */
	/* Core毎に呼び出す処理を振り分ける */
	t_u4CoreId = Bswlib_GetCoreId();

	/* Core0での処理 */
	if ( t_u4CoreId == BSW_CORE_ID_CORE0 )
	{
		/* 処理なし */
	}
	/* Core1での処理 */
	else if ( t_u4CoreId == BSW_CORE_ID_CORE1 )
	{
		/* 処理なし */
	}
#if ( MCU_TYPE_SERIES == MCU_RH850U2A16 )
	/* Core2での処理 */
	else if ( t_u4CoreId == BSW_CORE_ID_CORE2 )
	{
		/* 処理なし */
	}
	/* Core3での処理 */
	else if ( t_u4CoreId == BSW_CORE_ID_CORE3 )
	{
		/* 処理なし */
	}
#endif
	else
	{
		/* 処理なし */
	}
}

/*----------------------------------------------------------------------------------------------*/
/* Initialization Function																		*/
/* Return		: none																			*/
/* Parameters	: none																			*/
/*----------------------------------------------------------------------------------------------*/
void	ErrH_Init_1( void )
{
	U4							t_u4CoreId;				/* CoreID格納 */

	/* マルチコアになったことにより、 */
	/* Core毎に実行される処理が異なることを考慮し */
	/* Core毎に呼び出す処理を振り分ける */
	t_u4CoreId = Bswlib_GetCoreId();

	/* Core0での処理 */
	if ( t_u4CoreId == BSW_CORE_ID_CORE0 )
	{
// zantei ECCは2月末非対応		ErrH_Ecc_Init();													/* ECC初期化処理 */
		ErrH_Ecm_PreInit( t_u4CoreId, cstErrH_UcfgData.pcu4InitInfCfg );	/* ECM初期化前処理 */
// zantei ECCは2月末非対応		ErrH_Ecc_ClearAllEccError();										/* 全ECCエラークリア処理 */
		ErrH_Ecm_Init( t_u4CoreId, &cstErrH_UcfgData );						/* ECM初期化処理 */
// zantei MPUは2月末非対応		ErrH_Slg_Init( &cstErrH_UcfgData );									/* Slave Guardの設定 */
	}
	/* Core1での処理 */
	else if ( t_u4CoreId == BSW_CORE_ID_CORE1 )
	{
		ErrH_Ecm_PreInit( t_u4CoreId, cstErrH_UcfgData.pcu4InitInfCfg );		/* ECM初期化前処理 */
		ErrH_Ecm_Init( t_u4CoreId, &cstErrH_UcfgData );		/* ECM初期化処理 */
	}
#if ( MCU_TYPE_SERIES == MCU_RH850U2A16 )		/* U2A16構成 */
	/* Core2での処理 */
	else if ( t_u4CoreId == BSW_CORE_ID_CORE2 )
	{
		ErrH_Ecm_PreInit( t_u4CoreId, cstErrH_UcfgData.pcu4InitInfCfg );		/* ECM初期化前処理 */
		ErrH_Ecm_Init( t_u4CoreId, &cstErrH_UcfgData );		/* ECM初期化処理 */
	}
	/* Core3での処理 */
	else if ( t_u4CoreId == BSW_CORE_ID_CORE3 )
	{
		ErrH_Ecm_PreInit( t_u4CoreId, cstErrH_UcfgData.pcu4InitInfCfg );		/* ECM初期化前処理 */
		ErrH_Ecm_Init( t_u4CoreId, &cstErrH_UcfgData );		/* ECM初期化処理 */
	}
#endif
	else
	{
		/* 処理なし */
	}
}

/*----------------------------------------------------------------------------------------------*/
/* Alarm Interrupt Function																		*/
/* Return		: none																			*/
/* Parameters	: none																			*/
/*----------------------------------------------------------------------------------------------*/
void	ErrH_AlarmInterrupt( void )
{
	/* ECMエラー割り込み発生時処理を実施する。 */
	ErrH_Ecm_AlarmInterrupt( cstErrH_UcfgData.pcu4NotifCoreCfg );
}

#if 0	// zantei MPUは2月末非対応
/*----------------------------------------------------------------------------------------------*/
/* Protection Hook Function																		*/
/* return		: none																			*/
/* parameters	: ErrId - Error ID																*/
/*				: ErrPc - Error Program Counter													*/
/*				: ErrAdr - Error Address														*/
/*----------------------------------------------------------------------------------------------*/
void	ErrH_ProtectionHook( U4 t_u4ErrId, U4 t_u4ErrPc, U4 t_u4ErrAdr )
{
	U4							t_u4CoreId;				/* CoreID格納 */

	/* MIPとMDPで処理分割せず、MPU異常アドレスを記憶する			 */
	/* Core毎に異常発生時メモリエラーアドレスを保持しているため		 */
	/* 呼び出されたCoreを判別する									 */
	t_u4CoreId = Bswlib_GetCoreId();

	/* メモリ破壊を避けるため、存在するCoreでない場合には、格納処理をスキップする */
	if( t_u4CoreId < MCU_CORE_NUM )
	{
		/* Core毎に対応した異常発生時メモリエラーアドレスを格納する */
		s_u4ErrH_MpuErrorAddress[ t_u4CoreId ] = t_u4ErrAdr;

		/* MIPMDP発生を通知する */
		ErrH_ProtectionHookCallout();
	}
}
#endif // zantei MPUは2月末非対応

/*----------------------------------------------------------------------------------------------*/
/* Local Functions																				*/
/*----------------------------------------------------------------------------------------------*/

#pragma ghs section text=default
/*-- End Of File -------------------------------------------------------------------------------*/
