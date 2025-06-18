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
#include	"ErrH_slg.h"

#include	"ErrH_peg.h"

/*==============================================================================================*/
/* prototypes																					*/
/*==============================================================================================*/

/*==============================================================================================*/
/* defines / data types / structs / unions	/ macros											*/
/*==============================================================================================*/
#define		u4ERRH_PEG_REGPROTMASK					((U4)0x00000153U)	/* PROT用マスク */
#define		u4ERRH_PEG_REGADVMASK					((U4)0x03FFF000U)	/* ADVm用マスク */

/* リザーブビット用のマスク値 */
#define		u4ERRH_PEG_MASK_GUARD_PENCL0_PEGBAD		((U4)0xFC000FFFU)	/* BADm用マスク */

#define		u4ERRH_PEG_PEGSPIDERRCLR_ALLBIT_CLR		((U4)0xFFFFFFFFU)	/* PEGSPIDERRCLRレジスタ、全ビットクリア値 */
#define		u4ERRH_PEG_PEGSPIDERRSTAT_NOERR			((U4)0x00000000U)	/* PEGSPIDERRSTAT、エラーなし */
#define		u4ERRH_PEG_ERRSTAT_SPIDERR				((U4)0x00000001U)	/* SPIDエラー発生 */
#define		u4ERRH_PEG_NOERR						((U4)0x00000000U)	/* エラーなし */
#define		u4ERRH_PEG_INVALID_ADDR					((U4)0x00000000U)	/* エラーアドレス無効値 */
#define		u4ERRH_PEG_INVALID_INFO					((U4)0x00000000U)	/* エラーアクセス情報無効値 */
/*==============================================================================================*/
/* constants																					*/
/*==============================================================================================*/
#pragma ghs section rodata=".ERRH_RODATA_CONST"

/* 制御レジスタ */
static volatile Reg_Peg_GuardpeclType* const cstErrH_Peg_Reg[ERRH_SLG_CORE_NUM] = {
			&Reg_PEG_GUARDPE0CL0,
			&Reg_PEG_GUARDPE1CL0,
#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_TRIPLECORE ) )
			&Reg_PEG_GUARDPE2CL1
#else
			NULL_POINTER
#endif
};

/* エラーレジスタ */
/* PEGCAP_M */
static volatile Reg_Peg_PegcapType* const cstErrH_Peg_ErrRegM[ERRH_SLG_CORE_NUM] = {
			&Reg_PEG_PEGCAPMPE0CL0,
			&Reg_PEG_PEGCAPMPE1CL0,
#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_TRIPLECORE ) )
			&Reg_PEG_PEGCAPMPE2CL1
#else
			NULL_POINTER
#endif
};

/* PEGCAP_S */
static volatile Reg_Peg_PegcapType* const cstErrH_Peg_ErrRegS[ERRH_SLG_CORE_NUM] = {
			&Reg_PEG_PEGCAPSPE0CL0,
			&Reg_PEG_PEGCAPSPE1CL0,
#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_TRIPLECORE ) )
			&Reg_PEG_PEGCAPSPE2CL1
#else
			NULL_POINTER
#endif
};

#pragma ghs section rodata="default

/*==============================================================================================*/
/* variables																					*/
/*==============================================================================================*/

/*==============================================================================================*/
/* functions																					*/
/*==============================================================================================*/
#pragma ghs section text=".ERRH_TEXT_CODE"
/*----------------------------------------------------------------------------------------------*/
/* API Functions																				*/
/*----------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------*/
/* Set Mode & Start Guard Function																*/
/* Return		: none																			*/
/* Parameters	: Area - ID of Area Number( AREA_ID0 / 1 / 2 / 3 / 4 / 5 / 6 / 7 )				*/
/*				: Core - Core0/Core1/Core2( 0 / 1 / 2 )											*/
/*				: *ProtectionSetting															*/
/*----------------------------------------------------------------------------------------------*/
void	ErrH_Peg_SetModeStartGuard( U1 t_u1Area , U1 t_u1Core , const ErrH_PegProtSetType *t_pcstProtSet )
{
	volatile	Reg_Peg_GuardpeclType*	t_pstRegPegGuard;
				U4						t_u4RegTemp;

	t_pstRegPegGuard = (volatile Reg_Peg_GuardpeclType*)cstErrH_Peg_Reg[t_u1Core];

	if ( t_pstRegPegGuard != NULL_POINTER ) 
	{
		/* PEGKCPROT - PE ガードキーコード保護レジスタ(PE0) 保護解除 */
		t_pstRegPegGuard->unPEGKCPROT.u4Data = (U4)PEG_PEGKCPROT_KCE_ENABLE;

		t_u4RegTemp = u4ERRH_PEG_REGADVMASK & t_pcstProtSet->u4Addv;											/* 必要なビットのみを抽出 */
		t_pstRegPegGuard->stCH[t_u1Area].unPEGADV.u4Data	= t_u4RegTemp;										/* PEGADVm  */

		t_u4RegTemp = t_pstRegPegGuard->stCH[t_u1Area].unPEGBAD.u4Data & u4ERRH_PEG_MASK_GUARD_PENCL0_PEGBAD;	/* PEGBADmを読み出し、有効ビットのみをマスク */
		t_u4RegTemp = t_u4RegTemp | t_pcstProtSet->u4Base;														/* 設定値を加算（有効ビットのみを設定） */
		t_pstRegPegGuard->stCH[t_u1Area].unPEGBAD.u4Data	= t_u4RegTemp;										/* PEGBADmへ書き込み */

		t_pstRegPegGuard->stCH[t_u1Area].u4PEGSPID			= t_pcstProtSet->u4Spid;							/* PEGSPIDm */

		t_u4RegTemp = u4ERRH_PEG_REGPROTMASK & t_pcstProtSet->u4Prot;											/* 必要なビットのみを抽出 */
		t_pstRegPegGuard->stCH[t_u1Area].unPEGPROT.u4Data	= t_u4RegTemp;										/* PEGPROTm */
		
		/* PEGKCPROT - PE ガードキーコード保護レジスタ(PE0) 保護設定 */
		t_pstRegPegGuard->unPEGKCPROT.u4Data = (U4)PEG_PEGKCPROT_KCE_DISABLE;
		Bswlib_Sync_Pipeline_4( t_pstRegPegGuard->unPEGKCPROT.u4Data );
	}
}

/*----------------------------------------------------------------------------------------------*/
/* PEG Clear Error Function																		*/
/* Return		: none																			*/
/* Parameters	: Core - Core0/Core1/Core2( 0 / 1 / 2 )											*/
/*				: ModuleNum - PEG Module Number( 0 / 1  )										*/
/*----------------------------------------------------------------------------------------------*/
void	ErrH_Peg_ClearError( U1 t_u1Core, U2 t_u2ModuleNum )
{
	volatile	Reg_Peg_PegcapType*	t_pstRegPegCapM;
	volatile	Reg_Peg_PegcapType*	t_pstRegPegCapS;

	
	/* モジュール番号をチェック */
	if( t_u2ModuleNum == (U2)ERRH_SLG_PEGCAPM )
	{
		/* PEGCAP_M */
		t_pstRegPegCapM = (volatile Reg_Peg_PegcapType*)cstErrH_Peg_ErrRegM[t_u1Core];

		if ( t_pstRegPegCapM != NULL_POINTER )
		{
			/* エラーステータスクリア */
			t_pstRegPegCapM->unPEGOVFCLR.u4Data		= (U4)( (U4)PEG_PEGOVFCLR_CLRO * (U4)PEG_PEGOVFCLR_CLRO_CLEAR );
			t_pstRegPegCapM->u4PEGSPIDERRCLR		= u4ERRH_PEG_PEGSPIDERRCLR_ALLBIT_CLR;
			Bswlib_Sync_Pipeline_4( t_pstRegPegCapM->unPEGOVFCLR.u4Data );
		}
	}
	else if ( t_u2ModuleNum == (U2)ERRH_SLG_PEGCAPS )
	{
		/* PEGCAP_S */
		t_pstRegPegCapS = (volatile Reg_Peg_PegcapType*)cstErrH_Peg_ErrRegS[t_u1Core];

		if ( t_pstRegPegCapS != NULL_POINTER )
		{
			/* エラーステータスクリア */
			t_pstRegPegCapS->unPEGOVFCLR.u4Data		= (U4)( (U4)PEG_PEGOVFCLR_CLRO * (U4)PEG_PEGOVFCLR_CLRO_CLEAR );
			t_pstRegPegCapS->u4PEGSPIDERRCLR		= u4ERRH_PEG_PEGSPIDERRCLR_ALLBIT_CLR;
			Bswlib_Sync_Pipeline_4( t_pstRegPegCapS->unPEGOVFCLR.u4Data );
		}
	}
	else
	{
		/* 処理なし */
	}

}

/*----------------------------------------------------------------------------------------------*/
/* PEG Get Error Status Function																*/
/* Return		: Error Status																	*/
/* Parameters	: Core - Core0/Core1/Core2( 0 / 1 / 2 )											*/
/*				: ModuleNum - PEG Module Number( 0 / 1  )										*/
/*----------------------------------------------------------------------------------------------*/
U4	ErrH_Peg_GetErrStatus( U1 t_u1Core, U2 t_u2ModuleNum )
{
	volatile	Reg_Peg_PegcapType*	t_pstRegPegCapM;
	volatile	Reg_Peg_PegcapType*	t_pstRegPegCapS;
				U4					t_u4ErrorStatus;

	t_u4ErrorStatus = u4ERRH_PEG_NOERR;	/* エラーなしで初期化 */

	/* モジュール番号をチェック */
	if( t_u2ModuleNum == (U2)ERRH_SLG_PEGCAPM )
	{
		/* PEGCAP_M */
		t_pstRegPegCapM = (volatile Reg_Peg_PegcapType*)cstErrH_Peg_ErrRegM[t_u1Core];
		
		if ( t_pstRegPegCapM != NULL_POINTER )
		{
			/* エラーステータス取得 */
			t_u4ErrorStatus = t_pstRegPegCapM->unPEGOVFSTAT.u4Data;

			if( t_pstRegPegCapM->u4PEGSPIDERRSTAT != u4ERRH_PEG_PEGSPIDERRSTAT_NOERR )
			{
				t_u4ErrorStatus |= u4ERRH_PEG_ERRSTAT_SPIDERR;
			}
		}
	}
	else if ( t_u2ModuleNum == (U2)ERRH_SLG_PEGCAPS )
	{
		/* PEGCAP_S */
		t_pstRegPegCapS = (volatile Reg_Peg_PegcapType*)cstErrH_Peg_ErrRegS[t_u1Core];

		if ( t_pstRegPegCapS != NULL_POINTER )
		{
			/* エラーステータス取得 */
			t_u4ErrorStatus = t_pstRegPegCapS->unPEGOVFSTAT.u4Data;

			if( t_pstRegPegCapS->u4PEGSPIDERRSTAT != u4ERRH_PEG_PEGSPIDERRSTAT_NOERR )
			{
				t_u4ErrorStatus |= u4ERRH_PEG_ERRSTAT_SPIDERR;
			}
		}
	}
	else
	{
		/* 処理なし */
	}

	return( t_u4ErrorStatus );
}

/*----------------------------------------------------------------------------------------------*/
/* PEG Get Error Address Function																*/
/* Return		: Error Address																	*/
/* Parameters	: Core - Core0/Core1/Core2( 0 / 1 / 2 )											*/
/*				: ModuleNum - PEG Module Number( 0 / 1  )										*/
/*----------------------------------------------------------------------------------------------*/
U4	ErrH_Peg_GetErrAddress( U1 t_u1Core, U2 t_u2ModuleNum )
{
	volatile	Reg_Peg_PegcapType*	t_pstRegPegCapM;
	volatile	Reg_Peg_PegcapType*	t_pstRegPegCapS;
				U4					t_u4ErrorAddress;

	t_u4ErrorAddress = u4ERRH_PEG_INVALID_ADDR;	/* エラーアドレス無効値で初期化 */

	/* モジュール番号をチェック */
	if( t_u2ModuleNum == (U2)ERRH_SLG_PEGCAPM )
	{
		/* PEGCAP_M */
		t_pstRegPegCapM = (volatile Reg_Peg_PegcapType*)cstErrH_Peg_ErrRegM[t_u1Core];
		
		if ( t_pstRegPegCapM != NULL_POINTER )
		{
			/* エラーアドレス取得 */
			t_u4ErrorAddress = t_pstRegPegCapM->u4PEGERRADDR;
		}
	}
	else if ( t_u2ModuleNum == (U2)ERRH_SLG_PEGCAPS )
	{
		/* PEGCAP_S */
		t_pstRegPegCapS = (volatile Reg_Peg_PegcapType*)cstErrH_Peg_ErrRegS[t_u1Core];

		if ( t_pstRegPegCapS != NULL_POINTER )
		{
			/* エラーアドレス取得 */
			t_u4ErrorAddress = t_pstRegPegCapS->u4PEGERRADDR;
		}
	}
	else
	{
		/* 処理なし */
	}

	return( t_u4ErrorAddress );
}

/*----------------------------------------------------------------------------------------------*/
/* PEG Get Error Access info Function															*/
/* Return		: Error Access info																*/
/* Parameters	: Core - Core0/Core1/Core2( 0 / 1 / 2 )											*/
/*				: ModuleNum - PEG Module Number( 0 / 1  )										*/
/*----------------------------------------------------------------------------------------------*/
U4	ErrH_Peg_GetErrAccessInfo( U1 t_u1Core, U2 t_u2ModuleNum )
{
	volatile	Reg_Peg_PegcapType*	t_pstRegPegCapM;
	volatile	Reg_Peg_PegcapType*	t_pstRegPegCapS;
				U4					t_u4ErrorAccessInfo;

	t_u4ErrorAccessInfo =  u4ERRH_PEG_INVALID_INFO;	/* エラーアクセス情報無効値で初期化 */

	/* モジュール番号をチェック */
	if( t_u2ModuleNum == (U2)ERRH_SLG_PEGCAPM )
	{
		/* PEGCAP_M */
		t_pstRegPegCapM = (volatile Reg_Peg_PegcapType*)cstErrH_Peg_ErrRegM[t_u1Core];
		
		if ( t_pstRegPegCapM != NULL_POINTER )
		{
			/* エラーアクセス情報取得 */
			t_u4ErrorAccessInfo = t_pstRegPegCapM->unPEGERRTYPE.u4Data;
		}
	}
	else if ( t_u2ModuleNum == (U2)ERRH_SLG_PEGCAPS )
	{
		/* PEGCAP_S */
		t_pstRegPegCapS = (volatile Reg_Peg_PegcapType*)cstErrH_Peg_ErrRegS[t_u1Core];

		if ( t_pstRegPegCapS != NULL_POINTER )
		{
			/* エラーアクセス情報取得 */
			t_u4ErrorAccessInfo = t_pstRegPegCapS->unPEGERRTYPE.u4Data;
		}
	}
	
	else
	{
		/* 処理なし */
	}

	return( t_u4ErrorAccessInfo );
}

/*----------------------------------------------------------------------------------------------*/
/* Scheduled / Event Functions																	*/
/*----------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------*/
/* Local Functions																				*/
/*----------------------------------------------------------------------------------------------*/

#pragma ghs section text=default

#endif // zantei MPUは2月末非対応
/*-- End Of File -------------------------------------------------------------------------------*/
