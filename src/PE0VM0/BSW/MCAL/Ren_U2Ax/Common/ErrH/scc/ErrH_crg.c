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

#include	"ErrH.h"
#include	"ErrH_slg.h"

#include	"ErrH_crg.h"


/*==============================================================================================*/
/* prototypes																					*/
/*==============================================================================================*/

/*==============================================================================================*/
/* defines / data types / structs / unions	/ macros											*/
/*==============================================================================================*/
#define		ERRH_CRG_ERRREGNUM					(11)				/* エラーレジスタ数 */
#define		u1ERRH_CRG_MODULEMASK				((U1)ERRH_SLG_CRGPE0CL0)	/* マスクデータ(SLGモジュール番号、CRGの先頭値) */
#define		u4ERRH_CRG_REGPROTMASK				((U4)0x00000153U)	/* PROT用マスク */
#define		u4ERRH_CRG_REGBADMASK				((U4)0x0007FF00U)	/* BADm用マスク */
#define		u4ERRH_CRG_REGADVMASK				((U4)0x0007FF00U)	/* ADVm用マスク */

#define		u4ERRH_CRG_CRGSPIDERRCLR_ALLBIT_CLR	((U4)0xFFFFFFFFU)	/* CRGSPIDERRCLRレジスタ、全ビットクリア値 */
#define		u4ERRH_CRG_CRGSPIDERRSTAT_NOERR		((U4)0x00000000U)	/* CRGSPIDERRSTAT、エラーなし */
#define		u4ERRH_CRG_ERRSTAT_SPIDERR			((U4)0x00000001U)	/* SPIDエラー発生 */
#define		u4ERRH_CRG_NOERR					((U4)0x00000000U)	/* エラーなし */
#define		u4ERRH_CRG_INVALID_ADDR				((U4)0x00000000U)	/* エラーアドレス無効値 */
#define		u4ERRH_CRG_INVALID_INFO				((U4)0x00000000U)	/* エラーアクセス情報無効値 */
/*==============================================================================================*/
/* constants																					*/
/*==============================================================================================*/
#pragma ghs section rodata=".ERRH_RODATA_CONST"
/* 制御レジスタ */
static volatile Reg_Crg_Guardcramcrg0Type* const cstErrH_Crg_CrgReg[ERRH_SLG_CRAM_CL_NUM] = {
			&Reg_CRG_GUARDCRAMCRG0,
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
			&Reg_CRG_GUARDCRAMCRG1
#else
			NULL_POINTER
#endif
};

static volatile Reg_Crg_Guardcramcsg0Type* const cstErrH_Crg_CsgReg[ERRH_SLG_CRAM_CL_NUM] = {
			&Reg_CRG_GUARDCRAMCSG0,
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
			&Reg_CRG_GUARDCRAMCSG1
#else
			NULL_POINTER
#endif
};

/* エラーレジスタ */
static volatile Reg_Crg_CrgcapType* const cstErrH_Crg_ErrReg[ERRH_CRG_ERRREGNUM] = {
			&Reg_CRG_CRGCAPPE0CL0,
			&Reg_CRG_CRGCAPPE1CL0,
#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_TRIPLECORE ) )
			&Reg_CRG_CRGCAPPE2CL1,
#else
			NULL_POINTER,
#endif
			&Reg_CRG_CRGCAPCRAMHCL0,
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
			&Reg_CRG_CRGCAPCRAMHCL1,
#else
			NULL_POINTER,
#endif
			&Reg_CRG_CRGCAPCRAMLCL0,
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
			&Reg_CRG_CRGCAPCRAMLCL1,
#else
			NULL_POINTER,
#endif
			&Reg_CRG_CRGCAPSX2MBHCL0,
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
			&Reg_CRG_CRGCAPSX2MBHCL1,
#else
			NULL_POINTER,
#endif
			&Reg_CRG_CRGCAPSX2MBLCL0,
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
			&Reg_CRG_CRGCAPSX2MBLCL1
#else
			NULL_POINTER
#endif
};

#pragma ghs section rodata=default

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
/*				: ClNum -   Cluster0/Cluster1( 0 / 1 )											*/
/*				: *ProtectionSetting															*/
/*----------------------------------------------------------------------------------------------*/
void	ErrH_Crg_SetModeStartCrgGuard( U1 t_u1Area , U1 t_u1ClNum , const ErrH_CrgProtSetType *t_pcstProtSet )
{
	volatile	Reg_Crg_Guardcramcrg0Type*	t_pstRegCrgGuard;
				U4							t_u4RegTemp;

	t_pstRegCrgGuard = (volatile Reg_Crg_Guardcramcrg0Type*)cstErrH_Crg_CrgReg[t_u1ClNum];

	if ( t_pstRegCrgGuard != NULL_POINTER ) 
	{
		/* CRGKCPROT - クラスタRAM ガードキーコード保護レジスタ 保護解除 */
		t_pstRegCrgGuard->unCRGKCPROT.u4Data = (U4)CRG_CRGKCPROT_KCE_ENABLE;

		t_pstRegCrgGuard->stCH[ t_u1Area ].u4CRGSPID		 = t_pcstProtSet->u4Spid;		/* チャネル SPID 設定 */
		
		t_u4RegTemp = u4ERRH_CRG_REGBADMASK & t_pcstProtSet->u4Base;						/* 必要なビットのみを抽出 */
		t_pstRegCrgGuard->stCH[ t_u1Area ].unCRGBAD.u4Data   = t_u4RegTemp;					/* チャネルベースアドレス設定 */
		
		t_u4RegTemp = u4ERRH_CRG_REGADVMASK & t_pcstProtSet->u4Addv;						/* 必要なビットのみを抽出 */
		t_pstRegCrgGuard->stCH[ t_u1Area ].unCRGADV.u4Data   = t_u4RegTemp;					/* チャネル有効ビット設定 */
		
		t_u4RegTemp = u4ERRH_CRG_REGPROTMASK & t_pcstProtSet->u4Prot;						/* 必要なビットのみを抽出 */
		t_pstRegCrgGuard->stCH[ t_u1Area ].unCRGPROT.u4Data  = t_u4RegTemp;					/* チャネル保護制御 */

		/* CRGKCPROT - クラスタRAM ガードキーコード保護レジスタ 保護設定 */
		t_pstRegCrgGuard->unCRGKCPROT.u4Data = (U4)CRG_CRGKCPROT_KCE_DISABLE;
		Bswlib_Sync_Pipeline_4( t_pstRegCrgGuard->unCRGKCPROT.u4Data );
	}
}

/*----------------------------------------------------------------------------------------------*/
/* Set Mode & Start CSG Guard Function															*/
/* Return		: none																			*/
/* Parameters	: Area - ID of Area Number( AREA_ID0 / 1 / 2 / 3 )								*/
/*				: ClNum -   Cluster0/Cluster1( 0 / 1 )											*/
/*				: *ProtectionSetting															*/
/*----------------------------------------------------------------------------------------------*/
void	ErrH_Crg_SetModeStartCsgGuard( U1 t_u1Area , U1 t_u1ClNum , const ErrH_CrgProtSetType *t_pcstProtSet )
{
	volatile	Reg_Crg_Guardcramcrg0Type*	t_pstRegCrgGuard;
	volatile	Reg_Crg_Guardcramcsg0Type*	t_pstRegCsgGuard;
				U4							t_u4RegTemp;

	t_pstRegCrgGuard = (volatile Reg_Crg_Guardcramcrg0Type*)cstErrH_Crg_CrgReg[t_u1ClNum];
	t_pstRegCsgGuard = (volatile Reg_Crg_Guardcramcsg0Type*)cstErrH_Crg_CsgReg[t_u1ClNum];

	if ( t_pstRegCsgGuard != NULL_POINTER ) 
	{
		/* CRGKCPROT - クラスタRAM ガードキーコード保護レジスタ 保護解除 */
		t_pstRegCrgGuard->unCRGKCPROT.u4Data = (U4)CRG_CRGKCPROT_KCE_ENABLE;

		t_pstRegCsgGuard->stCH[ t_u1Area ].u4CSGSPID		 = t_pcstProtSet->u4Spid;		/* チャネル SPID 設定 */
		
		t_u4RegTemp = u4ERRH_CRG_REGBADMASK & t_pcstProtSet->u4Base;						/* 必要なビットのみを抽出 */
		t_pstRegCsgGuard->stCH[ t_u1Area ].unCSGBAD.u4Data   = t_u4RegTemp;					/* チャネルベースアドレス設定 */
		
		t_u4RegTemp = u4ERRH_CRG_REGADVMASK & t_pcstProtSet->u4Addv;						/* 必要なビットのみを抽出 */
		t_pstRegCsgGuard->stCH[ t_u1Area ].unCSGADV.u4Data   = t_u4RegTemp;					/* チャネル有効ビット設定 */
		
		t_u4RegTemp = u4ERRH_CRG_REGPROTMASK & t_pcstProtSet->u4Prot;						/* 必要なビットのみを抽出 */
		t_pstRegCsgGuard->stCH[ t_u1Area ].unCSGPROT.u4Data  = t_u4RegTemp;					/* チャネル保護制御 */

		/* CRGKCPROT - クラスタRAM ガードキーコード保護レジスタ 保護設定 */
		t_pstRegCrgGuard->unCRGKCPROT.u4Data = (U4)CRG_CRGKCPROT_KCE_DISABLE;
		Bswlib_Sync_Pipeline_4( t_pstRegCrgGuard->unCRGKCPROT.u4Data );
	}
}

/*----------------------------------------------------------------------------------------------*/
/* CRG Clear Error Function																		*/
/* Return		: none																			*/
/* Parameters	: ModuleNum - CRG Module Number( 100～110  )									*/
/*----------------------------------------------------------------------------------------------*/
void	ErrH_Crg_ClearError( U2 t_u2ModuleNum )
{

	volatile	Reg_Crg_CrgcapType*	t_pstRegCrgCap;
				U1					t_u1ModuleNum;		/* マスク後モジュールNo */

	t_u1ModuleNum	=	(U1)(t_u2ModuleNum - u1ERRH_CRG_MODULEMASK);	/* モジュールNoマスク */

	if ( t_u1ModuleNum <= (U1)ERRH_CRG_ERRREGNUM )
	{
		t_pstRegCrgCap = (volatile Reg_Crg_CrgcapType*)cstErrH_Crg_ErrReg[t_u1ModuleNum];

		if ( t_pstRegCrgCap != NULL_POINTER )
		{
			/* エラーステータスクリア */
			t_pstRegCrgCap->unCRGOVFCLR.u4Data	=	(U4)( (U4)CRG_CRGOVFCLR_CLRO * (U4)CRG_CRGOVFCLR_CLRO_CLEAR );
			t_pstRegCrgCap->u4CRGSPIDERRCLR		=	u4ERRH_CRG_CRGSPIDERRCLR_ALLBIT_CLR;

			Bswlib_Sync_Pipeline_4( t_pstRegCrgCap->unCRGOVFCLR.u4Data );
		}
	}
}

/*----------------------------------------------------------------------------------------------*/
/* CRG Get Error Status Function																*/
/* Return		: Error Status																	*/
/* Parameters	: ModuleNum - CRG Module Number( 100～110  )									*/
/*----------------------------------------------------------------------------------------------*/
U4	ErrH_Crg_GetErrorStatus( U2 t_u2ModuleNum )
{
	volatile	Reg_Crg_CrgcapType*	t_pstRegCrgCap;
				U4					t_u4ErrorStatus;	/* エラーステータス */
				U1					t_u1ModuleNum;		/* マスク後モジュールNo */

	t_u4ErrorStatus = u4ERRH_CRG_NOERR;	/* エラーなしで初期化 */

	t_u1ModuleNum	=	(U1)(t_u2ModuleNum - u1ERRH_CRG_MODULEMASK);	/* モジュールNoマスク */

	if ( t_u1ModuleNum <= (U1)ERRH_CRG_ERRREGNUM )
	{
		t_pstRegCrgCap = (volatile Reg_Crg_CrgcapType*)cstErrH_Crg_ErrReg[t_u1ModuleNum];

		if ( t_pstRegCrgCap != NULL_POINTER )
		{
			/* エラーステータス取得 */
			t_u4ErrorStatus = t_pstRegCrgCap->unCRGOVFSTAT.u4Data;

			if( t_pstRegCrgCap->u4CRGSPIDERRSTAT != u4ERRH_CRG_CRGSPIDERRSTAT_NOERR )
			{
				t_u4ErrorStatus |= u4ERRH_CRG_ERRSTAT_SPIDERR;
			}
		}
	}
	
	return( t_u4ErrorStatus );
}

/*----------------------------------------------------------------------------------------------*/
/* CRG Get Error Address Function																*/
/* Return		: Error Address																	*/
/* Parameters	: ModuleNum - CRG Module Number( 100～110  )									*/
/*----------------------------------------------------------------------------------------------*/
U4	ErrH_Crg_GetErrAddress( U2 t_u2ModuleNum  )
{
	volatile	Reg_Crg_CrgcapType*	t_pstRegCrgCap;
				U4					t_u4ErrorAddress;	/* エラーアドレス */
				U1					t_u1ModuleNum;		/* マスク後モジュールNo */

	t_u4ErrorAddress = u4ERRH_CRG_INVALID_ADDR;	/* エラーアドレス無効値で初期化 */

	t_u1ModuleNum	=	(U1)(t_u2ModuleNum - u1ERRH_CRG_MODULEMASK);	/* モジュールNoマスク */

	if ( t_u1ModuleNum <= (U1)ERRH_CRG_ERRREGNUM )
	{
		t_pstRegCrgCap = (volatile Reg_Crg_CrgcapType*)cstErrH_Crg_ErrReg[t_u1ModuleNum];

		if ( t_pstRegCrgCap != NULL_POINTER )
		{
			/* エラーアドレス取得 */
			t_u4ErrorAddress = t_pstRegCrgCap->u4CRGERRADDR;
		}
	}

	return( t_u4ErrorAddress );
}

/*----------------------------------------------------------------------------------------------*/
/* CRG Get Error Access info Function															*/
/* Return		: Error Access info																*/
/* Parameters	: ModuleNum - CRG Module Number( 100～110  )									*/
/*----------------------------------------------------------------------------------------------*/
U4	ErrH_Crg_GetErrAccessInfo( U2 t_u2ModuleNum )
{
	volatile	Reg_Crg_CrgcapType*	t_pstRegCrgCap;
				U4					t_u4ErrorAccessInfo;	/* エラーアクセス情報 */
				U1					t_u1ModuleNum;			/* マスク後モジュールNo */

	t_u4ErrorAccessInfo = u4ERRH_CRG_INVALID_INFO;	/* エラーアクセス情報無効値で初期化 */

	t_u1ModuleNum	=	(U1)(t_u2ModuleNum - u1ERRH_CRG_MODULEMASK);	/* モジュールNoマスク */

	if ( t_u1ModuleNum <= (U1)ERRH_CRG_ERRREGNUM )
	{
		t_pstRegCrgCap	=	(volatile Reg_Crg_CrgcapType*)cstErrH_Crg_ErrReg[t_u1ModuleNum];

		if ( t_pstRegCrgCap != NULL_POINTER )
		{
			/* エラーアクセス情報取得 */
			t_u4ErrorAccessInfo = t_pstRegCrgCap->unCRGERRTYPE.u4Data;
		}
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
