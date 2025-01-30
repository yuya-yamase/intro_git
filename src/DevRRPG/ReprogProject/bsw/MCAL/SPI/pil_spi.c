/* pil_spi-r04-3000-0200-a-v01 */
/************************************************************************************************/
/*																								*/
/*		PIL SPI Driver																			*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

/*==============================================================================================*/
/*	include files																				*/
/*==============================================================================================*/
#include	"Std_Types.h"
#include	"Bsw_cfg.h"

#include	"pil_spi.h"

#include	"Reg_Mspi.h"

/*==============================================================================================*/
/*	prototypes																					*/
/*==============================================================================================*/
#if ( SPI_CFG_SYNCSEND_TIMEOUT < PIL_SPI_WAIT_MAX )
extern void Esr_Ap_Pil_Spi_SyncSendWait_TimeOutError( void );
#endif

#if ( SPI_CFG_SYNCRECEIVE_TIMEOUT < PIL_SPI_WAIT_MAX )
extern void Esr_Ap_Pil_Spi_SyncReceiveWait_TimeOutError( void );
#endif

/*==============================================================================================*/
/*	defines / data types / structs / unions	/ macros											*/
/*==============================================================================================*/
#define	u2PIL_SPI_CFSET_SYNC_COM		((U2)1)
#define	u1PIL_SPI_TGCTL_JDG_NO			((U1)8)
#define	u1PIL_SPI_TGCTL_SHIFT			((U1)4)
#define	s4PIL_SPI_CTL0_DUMMY_READ_COUNT	((S4)12)

/* レジスタ化け確認対象ビット */
#define u4PIL_SPI_CTL1_CHK_M			((U4)MSPI_CTL1_MSSEL + (U4)MSPI_CTL1_CSIE + (U4)MSPI_CTL1_SAMP + (U4)MSPI_CTL1_CKR + 				\
										 (U4)MSPI_CTL1_SOLS + (U4)MSPI_CTL1_CSP)
#define u4PIL_SPI_CFG1_CHK_M			((U4)MSPI_CFG1_CPOL + (U4)MSPI_CFG1_CPHA + (U4)MSPI_CFG1_DIR  + (U4)MSPI_CFG1_ICLS + 				\
										 (U4)MSPI_CFG1_FIDL + (U4)MSPI_CFG1_CSRI + (U4)MSPI_CFG1_SAFE + (U4)MSPI_CFG1_DECHK)
#define u2PIL_SPI_CFG2_CHK_M			((U2)MSPI_CFG2_FLEN)
#define u2PIL_SPI_CFG3_CHK_M			((U2)MSPI_CFG3_PRCS + (U2)MSPI_CFG3_CDIV)
#define u2PIL_SPI_SEUP_CHK_M			((U2)MSPI_SEUP_SEUP)
#define u2PIL_SPI_HOLD_CHK_M			((U2)MSPI_HOLD_HOLD)
#define u2PIL_SPI_IDLE_CHK_M			((U2)MSPI_IDLE_IDLE)
#define u2PIL_SPI_INDA_CHK_M			((U2)MSPI_INDA_INDA)


/*==============================================================================================*/
/*	variables																					*/
/*==============================================================================================*/

/*==============================================================================================*/
/* functions																					*/
/*==============================================================================================*/
// #define SEL_PRGSEC	(BSW_SEC_P_LROM0_CPU0_ASIL)
// #include "Bsw_Seccfg_Prgs.h"
#pragma ghs section text=".SPI_TEXT_CODE"

/*----------------------------------------------------------------------------------------------*/
/* API Functions																				*/
/*----------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------*/
/*	SPI Communication Mode Set Function															*/
/*	return		: none																			*/
/*	parameters	: HwChannelID - ID of SPI Unit & Channel ( PIL_SPI_CH*_# )						*/
/*				:				( * : Unit No( 0 - 9 ) , # : Channel No( 0 - 11 ) )				*/
/*				: PilChannelConfig - Channel Configuration										*/
/*----------------------------------------------------------------------------------------------*/
/* CTL1はPort_Init前の設定が必要 他レジスタはPort_Init後の設定でよいが、一括してPort_Init前に実施する */
void	Pil_Spi_SetComMode( U1 t_u1HwChannelID, const Pil_Spi_ChannelConfigType* t_pcstPilChannelConfig )
{
	U4									t_u4CSP;
	U4									t_u4BitPos;
	U1									t_u1CsActiveLevel;
	U1									t_u1CsID;
	U1									t_u1UnitNo;
	U1									t_u1ChNo;

	t_u1CsID = t_pcstPilChannelConfig->u1CsID;

	/* DI_ALL(); *//* 使用する側で割禁実施すること */

	t_u1UnitNo = Pil_Spi_GetUnitNo( t_u1HwChannelID );
	t_u1ChNo = Pil_Spi_GetSpiChNo( t_u1HwChannelID );

	/* CTL1、CTL2はEN=0のときのみ設定可能なため、本関数はEN=0であることを前提とする */
	t_u4BitPos = (U4)MSPI_CTL1_CSP_0 << (U4)t_u1CsID;
	t_u1CsActiveLevel = t_pcstPilChannelConfig->u1CsActiveLevel;

	/* CSP設定値作成(他CSのCSアクティブレベルは値を保持する) */
	t_u4CSP = ( cpstReg_Mspi[t_u1UnitNo]->unCTL1.u4Data & (U4)MSPI_CTL1_CSP );	/* CSP領域のみ抽出 */

	if ( t_u1CsActiveLevel == (U1)LO )
	{
		t_u4CSP &= (U4)~t_u4BitPos;
	}
	else
	{
		t_u4CSP |= t_u4BitPos;
	}
	cpstReg_Mspi[t_u1UnitNo]->unCTL1.u4Data = t_u4CSP | t_pcstPilChannelConfig->u4CTL1;

	cpstReg_Mspi[t_u1UnitNo]->unCTL2.u1Data = 
		( (U1)MSPI_CTL2_DCS	* (U1)MSPI_CTL2_DCS_DISABLE ) 				+
		( (U1)MSPI_CTL2_LBM	* (U1)MSPI_CTL2_LBM_DISABLE );

	/* CFG1,CFG2,CFG3,CFG4,SEUP,HOLD,IDLE,INDAはCHEN = 0の時のみ設定可能なため、本関数はCHEN=0であることを前提とする */
	cpstReg_Mspi[t_u1UnitNo]->stCH[t_u1ChNo].unCFG1.u4Data = t_pcstPilChannelConfig->u4CFG1;
	cpstReg_Mspi[t_u1UnitNo]->stCH[t_u1ChNo].unCFG2.u2Data = t_pcstPilChannelConfig->u2CFG2;
	cpstReg_Mspi[t_u1UnitNo]->stCH[t_u1ChNo].unCFG3.u2Data = t_pcstPilChannelConfig->u2CFG3;

	cpstReg_Mspi[t_u1UnitNo]->stCH[t_u1ChNo].unCFG4.u4Data = 
		( (U4)MSPI_CFG4_HWTS_0	* (U4)MSPI_CFG4_HWTS_DISABLE )			+
		( (U4)MSPI_CFG4_SIZE_0	* (U4)MSPI_CFG4_SIZE_STAGESIZE8 );

	cpstReg_Mspi[t_u1UnitNo]->stCH[t_u1ChNo].unSEUP.u2Data = t_pcstPilChannelConfig->u2SEUP;
	cpstReg_Mspi[t_u1UnitNo]->stCH[t_u1ChNo].unHOLD.u2Data = t_pcstPilChannelConfig->u2HOLD;
	cpstReg_Mspi[t_u1UnitNo]->stCH[t_u1ChNo].unIDLE.u2Data = t_pcstPilChannelConfig->u2IDLE;
	cpstReg_Mspi[t_u1UnitNo]->stCH[t_u1ChNo].unINDA.u2Data = t_pcstPilChannelConfig->u2INDA;

	/* EI_ALL(); *//* 使用する側で割禁実施すること */
}

#if ( ( SPI_CFG_MODEA_USE == ON ) || ( SPI_CFG_MODEB_USE == ON ) )
/*----------------------------------------------------------------------------------------------*/
/*	SPI Communication Mode Check Function														*/
/*	return		: RegError - Register Error 													*/
/*	parameters	: HwChannelID - ID of SPI Unit & Channel ( PIL_SPI_CH*_# )						*/
/*				:				( * : Unit No( 0 - 9 ) , # : Channel No( 0 - 11 ) )				*/
/*				: PilChannelConfig - Channel Configuration										*/
/*----------------------------------------------------------------------------------------------*/
U1	Pil_Spi_CheckComMode( U1 t_u1HwChannelID, const Pil_Spi_ChannelConfigType* t_pcstPilChannelConfig )
{
	U4									t_u4CTL1;			/* CTL1レジスタ値 */
	U4									t_u4CTL1Config;		/* CTL1コンフィグ値 */
	U4									t_u4CSP;			/* CTL1.CSP設定値 */
	U4									t_u4BitPos;
	U1									t_u1CsActiveLevel;
	U1									t_u1CsID;
	U1									t_u1RegError;
	U1									t_u1UnitNo;
	U1									t_u1ChNo;

	t_u1RegError = (U1)OK;
	t_u1CsID = t_pcstPilChannelConfig->u1CsID;

	t_u1UnitNo = Pil_Spi_GetUnitNo( t_u1HwChannelID );
	t_u1ChNo = Pil_Spi_GetSpiChNo( t_u1HwChannelID );

	t_u4BitPos = (U4)MSPI_CTL1_CSP_0 << (U4)t_u1CsID;
	t_u1CsActiveLevel = t_pcstPilChannelConfig->u1CsActiveLevel;

	t_u4CTL1 = cpstReg_Mspi[t_u1UnitNo]->unCTL1.u4Data;

	/* CSP設定値作成(他CSのCSアクティブレベルは値を保持する) */
	t_u4CSP = ( t_u4CTL1 & (U4)MSPI_CTL1_CSP );

	if ( t_u1CsActiveLevel == (U1)LO )
	{
		t_u4CSP &= (U4)~t_u4BitPos;
	}
	else
	{
		t_u4CSP |= t_u4BitPos;
	}

	t_u4CTL1Config = t_u4CSP | t_pcstPilChannelConfig->u4CTL1;

	if ( ( t_u4CTL1 & u4PIL_SPI_CTL1_CHK_M ) != ( t_u4CTL1Config & u4PIL_SPI_CTL1_CHK_M ) )
	{
		t_u1RegError = (U1)NG;
	}

	if ( ( cpstReg_Mspi[t_u1UnitNo]->unCTL2.u1Data & (U2)MSPI_CTL2_LBM ) != (U2)( (U2)MSPI_CTL2_LBM * (U2)MSPI_CTL2_LBM_DISABLE ) )
	{
		t_u1RegError = (U1)NG;
	}
	if ( ( cpstReg_Mspi[t_u1UnitNo]->stCH[t_u1ChNo].unCFG1.u4Data & u4PIL_SPI_CFG1_CHK_M ) != ( t_pcstPilChannelConfig->u4CFG1 & u4PIL_SPI_CFG1_CHK_M ) )
	{
		t_u1RegError = (U1)NG;
	}
	if ( ( cpstReg_Mspi[t_u1UnitNo]->stCH[t_u1ChNo].unCFG2.u2Data & u2PIL_SPI_CFG2_CHK_M ) != ( t_pcstPilChannelConfig->u2CFG2 & u2PIL_SPI_CFG2_CHK_M ) )
	{
		t_u1RegError = (U1)NG;
	}
	if ( ( cpstReg_Mspi[t_u1UnitNo]->stCH[t_u1ChNo].unCFG3.u2Data & u2PIL_SPI_CFG3_CHK_M ) != ( t_pcstPilChannelConfig->u2CFG3 & u2PIL_SPI_CFG3_CHK_M ) )
	{
		t_u1RegError = (U1)NG;
	}
	if ( ( cpstReg_Mspi[t_u1UnitNo]->stCH[t_u1ChNo].unCFG4.u4Data & (U4)MSPI_CFG4_HWTS ) != (U4)( ( (U4)MSPI_CFG4_HWTS_0 * (U4)MSPI_CFG4_HWTS_DISABLE ) ) )
	{
		t_u1RegError = (U1)NG;
	}
	if ( ( cpstReg_Mspi[t_u1UnitNo]->stCH[t_u1ChNo].unSEUP.u2Data & u2PIL_SPI_SEUP_CHK_M ) != ( t_pcstPilChannelConfig->u2SEUP & u2PIL_SPI_SEUP_CHK_M ) )
	{
		t_u1RegError = (U1)NG;
	}
	if ( ( cpstReg_Mspi[t_u1UnitNo]->stCH[t_u1ChNo].unHOLD.u2Data & u2PIL_SPI_HOLD_CHK_M ) != ( t_pcstPilChannelConfig->u2HOLD & u2PIL_SPI_HOLD_CHK_M ) )
	{
		t_u1RegError = (U1)NG;
	}
	if ( ( cpstReg_Mspi[t_u1UnitNo]->stCH[t_u1ChNo].unIDLE.u2Data & u2PIL_SPI_IDLE_CHK_M ) != ( t_pcstPilChannelConfig->u2IDLE & u2PIL_SPI_IDLE_CHK_M ) )
	{
		t_u1RegError = (U1)NG;
	}
	if ( ( cpstReg_Mspi[t_u1UnitNo]->stCH[t_u1ChNo].unINDA.u2Data & u2PIL_SPI_INDA_CHK_M ) != ( t_pcstPilChannelConfig->u2INDA & u2PIL_SPI_INDA_CHK_M ) )
	{
		t_u1RegError = (U1)NG;
	}

	return( t_u1RegError );
}
#endif

/*----------------------------------------------------------------------------------------------*/
/*	SPI Disable Communication Function															*/
/*	return		: none																			*/
/*	parameters	: HwChannelID - ID of SPI Unit & Channel ( PIL_SPI_CH*_# )						*/
/*				:				( * : Unit No( 0 - 9 ) , # : Channel No( 0 - 11 ) )				*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Spi_DisableCommunication( U1 t_u1HwChannelID )
{
	S4									i;
	U1									t_u1UnitNo;
	volatile U1							t_u1Dummy;

	t_u1UnitNo = Pil_Spi_GetUnitNo( t_u1HwChannelID );

	cpstReg_Mspi[t_u1UnitNo]->unCTL0.u1Data = 
		( (U1)MSPI_CTL0_EN		* (U1)MSPI_CTL0_EN_DISABLE );

	/* @notice CTL0 ENは1→0としてから再度1にするまでMSPInCLK * 4以上 or PCLK * 4以上空ける必要があるためウェイトする。 */
	/*         ENへの0書き込み後にEN=0となるまではPCLK * 2であり、DeInit時等での通信停止のみの場合は2クロック分余分なウェイトとなるが */
	/*         処理共通化のためここでは4クロック分のウェイトとする。 */
	for ( i = (S4)0 ; i < s4PIL_SPI_CTL0_DUMMY_READ_COUNT ; i++ )
	{
		t_u1Dummy = cpstReg_Mspi[t_u1UnitNo]->unCTL0.u1Data;			/* CTL0をダミーリード */
	}
}

#if ( ( SPI_CFG_MODEA_USE == ON ) || ( SPI_CFG_MODEB_USE == ON ) )
/*----------------------------------------------------------------------------------------------*/
/*	SPI Set Frame Number Function																*/
/*	return		: none																			*/
/*	parameters	: HwChannelID - ID of SPI Unit & Channel ( PIL_SPI_CH*_# )						*/
/*				:				( * : Unit No( 0 - 9 ) , # : Channel No( 0 - 11 ) )				*/
/*				:	Length - Frame Number														*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Spi_SetFrameNumber( U1 t_u1HwChannelID, U2 t_u2Length )
{
	U1									t_u1UnitNo;
	U1									t_u1ChNo;

	t_u1UnitNo = Pil_Spi_GetUnitNo( t_u1HwChannelID );
	t_u1ChNo = Pil_Spi_GetSpiChNo( t_u1HwChannelID );

	cpstReg_Mspi[t_u1UnitNo]->stCH[t_u1ChNo].u2CFSET = t_u2Length;
}

/*----------------------------------------------------------------------------------------------*/
/*	SPI Data Send Function																		*/
/*	return		: Receive Data																	*/
/*	parameters	: HwChannelID - ID of SPI Unit & Channel ( PIL_SPI_CH*_# )						*/
/*				:				( * : Unit No( 0 - 9 ) , # : Channel No( 0 - 11 ) )				*/
/*				: TxData - Send Data															*/
/*				: PilChannelConfig(Sync)														*/
/*----------------------------------------------------------------------------------------------*/
U4		Pil_Spi_SendReceiveData( U1 t_u1HwChannelID, U4 t_u4TxData, const Pil_Spi_ChannelConfigType* t_pcstPilChannelConfig )
{
	U4									t_u4ReceiveData;
	U1									t_u1UnitNo;
	U1									t_u1ChNo;
#if ( SPI_CFG_SYNCSEND_TIMEOUT < PIL_SPI_WAIT_MAX ) || ( SPI_CFG_SYNCRECEIVE_TIMEOUT < PIL_SPI_WAIT_MAX )
	U4									t_u4CountVal;
#endif


	t_u1UnitNo = Pil_Spi_GetUnitNo( t_u1HwChannelID );
	t_u1ChNo = Pil_Spi_GetSpiChNo( t_u1HwChannelID );

	BSW_CFG_GETSPINLOCK_PIL_SPI();
	/* DI_ALL(); */		/* GETSPINLOCK内でDI_ALL実施のためコメント化 */

	/* ユニット有効 */
	cpstReg_Mspi[t_u1UnitNo]->unCTL0.u1Data = 
		( (U1)MSPI_CTL0_EN		* (U1)MSPI_CTL0_EN_ENABLE );

	cpstReg_Mspi[t_u1UnitNo]->stCH[t_u1ChNo].unCFG0.u4Data = 
		( (U4)MSPI_CFG0_TXE		* (U4)MSPI_CFG0_TXE_ENABLE )			+
		( (U4)MSPI_CFG0_RXE		* (U4)MSPI_CFG0_RXE_ENABLE )			+
		( (U4)MSPI_CFG0_MD_0	* (U4)MSPI_CFG0_MD_DIRECT )				+
		( (U4)MSPI_CFG0_PRIO_0	* (U4)MSPI_CFG0_PRIO_LEVEL8 )			+
		( (U4)MSPI_CFG0_LOCK	* (U4)MSPI_CFG0_LOCK_DISABLE )			+
		( (U4)MSPI_CFG0_FCCE	* (U4)MSPI_CFG0_FCCE_CHEN_CLEAR )		+
		( (U4)MSPI_CFG0_IERE	* (U4)MSPI_CFG0_IERE_DISABLE )			+
		( (U4)MSPI_CFG0_IFEE	* (U4)MSPI_CFG0_IFEE_DISABLE )			+
		( (U4)MSPI_CFG0_IRXE	* (U4)MSPI_CFG0_IRXE_DISABLE )			+
		( (U4)MSPI_CFG0_ITXE	* (U4)MSPI_CFG0_ITXE_DISABLE );
	
	/* フレーム数 1固定 */
/*	cpstReg_Mspi[t_u1UnitNo]->stCH[t_u1ChNo].u2CFSET = u2PIL_SPI_CFSET_SYNC_COM; */
	
	/* CS選択 */
	cpstReg_Mspi[t_u1UnitNo]->stCH[t_u1ChNo].unSSEL.u2Data = t_pcstPilChannelConfig->u2SSEL;
	
	/* チャネル有効化、チャネルアクティブ */
	cpstReg_Mspi[t_u1UnitNo]->stCH[t_u1ChNo].unCSTS.u1Data = 
		( (U1)MSPI_CSTS_ACTFS	* (U1)MSPI_CSTS_ACTFS_SET )						+
		( (U1)MSPI_CSTS_CHENS	* (U1)MSPI_CSTS_CHENS_SET );

	/* 送信準備待ち */
#if ( SPI_CFG_SYNCSEND_TIMEOUT < PIL_SPI_WAIT_MAX )
	t_u4CountVal = (U4)0;
#endif
	while ( ( cpstReg_Mspi[t_u1UnitNo]->stCH[t_u1ChNo].unCSTR.u2Data & (U2)MSPI_CSTR_TXRQF ) != (U2)( (U2)MSPI_CSTR_TXRQF * (U2)MSPI_CSTR_TXRQF_REQUEST ) )
	{
		/* 送信データ準備完了まで待機する */
#if ( SPI_CFG_SYNCSEND_TIMEOUT < PIL_SPI_WAIT_MAX )
		/* タイムアウト判定 */
		if( t_u4CountVal >= (U4)SPI_CFG_SYNCSEND_TIMEOUT )
		{
			Esr_Ap_Pil_Spi_SyncSendWait_TimeOutError();								/* タイムアウト通知処理 */
			break;
		}
		LIB_Wait( u4PIL_SPI_WAIT_1US );
		t_u4CountVal++;																/* @qac 3383:ラップアラウンドしない */
#endif
	}
	/* 送信データ書込み */
	cpstReg_Mspi[t_u1UnitNo]->stCH[t_u1ChNo].unTXDA0.u4Data = t_u4TxData;

	/* 受信完了待ち */
#if ( SPI_CFG_SYNCRECEIVE_TIMEOUT < PIL_SPI_WAIT_MAX )
	t_u4CountVal = (U4)0;
#endif
	while ( ( cpstReg_Mspi[t_u1UnitNo]->stCH[t_u1ChNo].unCSTR.u2Data & (U2)MSPI_CSTR_RXRQF ) != (U2)( (U2)MSPI_CSTR_RXRQF * (U2)MSPI_CSTR_RXRQF_REQUEST ) )
	{
		/* 受信完了まで待機する */
#if ( SPI_CFG_SYNCRECEIVE_TIMEOUT < PIL_SPI_WAIT_MAX )
		/* タイムアウト判定 */
		if( t_u4CountVal >= (U4)SPI_CFG_SYNCRECEIVE_TIMEOUT )
		{
			Esr_Ap_Pil_Spi_SyncReceiveWait_TimeOutError();							/* タイムアウト通知処理 */
			break;
		}
		LIB_Wait( u4PIL_SPI_WAIT_1US );
		t_u4CountVal++;																/* @qac 3383:ラップアラウンドしない */
#endif
	}
	t_u4ReceiveData = cpstReg_Mspi[t_u1UnitNo]->stCH[t_u1ChNo].unRXDA0.u4Data;

	/* EI_ALL(); */		/* RELEASESPINLOCK内でEI_ALL実施のためコメント化 */
	BSW_CFG_RELEASESPINLOCK_PIL_SPI();

	return ( t_u4ReceiveData );
}
#endif

#if (SPI_CFG_MODEC_USE == ON)
/*----------------------------------------------------------------------------------------------*/
/*	SPI AsyncSend Start Function																*/
/*	return		: none																			*/
/*	parameters	: HwChannelID - ID of SPI Unit & Channel ( PIL_SPI_CH*_# )						*/
/*				:				( * : Unit No( 0 - 9 ) , # : Channel No( 0 - 11 ) )				*/
/*				: PilChannelConfig - Communication Information									*/
/*				: Times - Send Receive Data Times (1 - 0xFFFF(1 times = 2byte))					*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Spi_StartAsync( U1 t_u1HwChannelID, const Pil_Spi_ChannelConfigType* t_pcstPilChannelConfig, U2 t_u2Times )
{
	U4									t_u4Data;
	U4									t_u4Mask;
	U4									t_u4SetData;
	U1									t_u1UnitNo;
	U1									t_u1ChNo;
	U1									t_u1BitShiftNum;

	t_u1UnitNo = Pil_Spi_GetUnitNo( t_u1HwChannelID );
	t_u1ChNo = Pil_Spi_GetSpiChNo( t_u1HwChannelID );

	/* コール元(Spi_AsyncTransmit)にて排他処理実施のためコメント化 */
	/* BSW_CFG_GETSPINLOCK_PIL_SPI(); */
	/* DI_ALL(); */		/* GETSPINLOCK内でDI_ALL実施のためコメント化 */

	/* ユニット有効 */
	cpstReg_Mspi[t_u1UnitNo]->unCTL0.u1Data = 
		( (U1)MSPI_CTL0_EN		* (U1)MSPI_CTL0_EN_ENABLE );

	cpstReg_Mspi[t_u1UnitNo]->stCH[t_u1ChNo].unCFG0.u4Data = 
		( (U4)MSPI_CFG0_TXE		* (U4)MSPI_CFG0_TXE_ENABLE )			+
		( (U4)MSPI_CFG0_RXE		* (U4)MSPI_CFG0_RXE_ENABLE )			+
		( (U4)MSPI_CFG0_MD_0	* (U4)MSPI_CFG0_MD_DIRECT )				+
		( (U4)MSPI_CFG0_PRIO_0	* (U4)MSPI_CFG0_PRIO_LEVEL8 )			+
		( (U4)MSPI_CFG0_LOCK	* (U4)MSPI_CFG0_LOCK_DISABLE )			+
		( (U4)MSPI_CFG0_FCCE	* (U4)MSPI_CFG0_FCCE_CHEN_CLEAR )		+
		( (U4)MSPI_CFG0_IERE	* (U4)MSPI_CFG0_IERE_DISABLE )			+
		( (U4)MSPI_CFG0_IFEE	* (U4)MSPI_CFG0_IFEE_DISABLE )			+
		( (U4)MSPI_CFG0_IRXE	* (U4)MSPI_CFG0_IRXE_ENABLE )			+
		( (U4)MSPI_CFG0_ITXE	* (U4)MSPI_CFG0_ITXE_ENABLE );

	/* フレーム数設定 */
	cpstReg_Mspi[t_u1UnitNo]->stCH[t_u1ChNo].u2CFSET = t_u2Times;

	/* CS選択 */
	cpstReg_Mspi[t_u1UnitNo]->stCH[t_u1ChNo].unSSEL.u2Data = t_pcstPilChannelConfig->u2SSEL;

	/* DTS転送要因選択、DTS使用設定 */
	if ( t_u1ChNo < u1PIL_SPI_TGCTL_JDG_NO )													/* チャネル0-7と8-11で設定するレジスタが異なるため、チャネル番号の判定を行う */
	{
		t_u4Data = REG_MSPITG.unTGCTLN[t_u1UnitNo].u4Data;
		t_u1BitShiftNum = t_u1ChNo * u1PIL_SPI_TGCTL_SHIFT;
		t_u4Mask = ( (U4)MSPI_TGCTLN_TRGSEL0 | (U4)MSPI_TGCTLN_SRCSEL0 ) << (U4)t_u1BitShiftNum;
		t_u4Data &= (U4)~t_u4Mask;																/* 該当CHのみ0でクリア */
		t_u4SetData = ( (U4)MSPI_TGCTLN_TRGSEL0		* (U4)MSPI_TGCTL_TRGSEL_DMA )		+
					  ( (U4)MSPI_TGCTLN_SRCSEL0_0	* (U4)MSPI_TGCTL_SRCSEL_TX_RX );
		t_u4SetData = t_u4SetData << (U4)t_u1BitShiftNum;
		t_u4Data |= t_u4SetData; 
		REG_MSPITG.unTGCTLN[t_u1UnitNo].u4Data = t_u4Data;
	}
	else
	{
		t_u4Data = REG_MSPITG.unTGCTLI[t_u1UnitNo].u4Data;
		t_u1BitShiftNum = ( t_u1ChNo - u1PIL_SPI_TGCTL_JDG_NO ) * u1PIL_SPI_TGCTL_SHIFT;		/* 格納先を合わせる処理が必要となる */
		t_u4Mask = ( (U4)MSPI_TGCTLI_TRGSEL8 | (U4)MSPI_TGCTLI_SRCSEL8 ) << (U4)t_u1BitShiftNum;
		t_u4Data &= (U4)~t_u4Mask;																/* 該当CHのみ0でクリア */
		t_u4SetData = ( (U4)MSPI_TGCTLI_TRGSEL8		* (U4)MSPI_TGCTL_TRGSEL_DMA )		+
					  ( (U4)MSPI_TGCTLI_SRCSEL8_0	* (U4)MSPI_TGCTL_SRCSEL_TX_RX );
		t_u4SetData = t_u4SetData << (U4)t_u1BitShiftNum;
		t_u4Data |= t_u4SetData; 
		REG_MSPITG.unTGCTLI[t_u1UnitNo].u4Data = t_u4Data;
	}

	/* チャネル有効化、チャネルアクティブ */
	cpstReg_Mspi[t_u1UnitNo]->stCH[t_u1ChNo].unCSTS.u1Data = 
		( (U1)MSPI_CSTS_ACTFS	* (U1)MSPI_CSTS_ACTFS_SET )						+
		( (U1)MSPI_CSTS_CHENS	* (U1)MSPI_CSTS_CHENS_SET );

	/* コール元(Spi_AsyncTransmit)にて排他処理実施のためコメント化 */
	/* EI_ALL(); */		/* RELEASESPINLOCK内でEI_ALL実施のためコメント化 */
	/* BSW_CFG_RELEASESPINLOCK_PIL_SPI(); */
}
#endif

/*----------------------------------------------------------------------------------------------*/
/*	SPI Unit Enable Function																	*/
/*	return		: none																			*/
/*	parameters	: UnitNo																		*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Spi_EnableUnit( U1 t_u1UnitNo )
{
	/* ユニット有効 */
	cpstReg_Mspi[t_u1UnitNo]->unCTL0.u1Data = 
		( (U1)MSPI_CTL0_EN		* (U1)MSPI_CTL0_EN_ENABLE );
}

#if (SPI_CFG_MODEC_USE == ON)
/*----------------------------------------------------------------------------------------------*/
/*	SPI Overrun Error Status Get Function														*/
/*	return		: Overrun Error Status															*/
/*	parameters	: HwChannelID - ID of SPI Unit & Channel ( PIL_SPI_CH*_# )						*/
/*				:				( * : Unit No( 0 - 9 ) , # : Channel No( 0 - 11 ) )				*/
/*----------------------------------------------------------------------------------------------*/
ZORN	Pil_Spi_GetOvrunErrStatus( U1 t_u1HwChannelID )
{
	ZORN								t_udStatus;
	U1									t_u1Status;
	U1									t_u1UnitNo;
	U1									t_u1ChNo;

	t_u1UnitNo = Pil_Spi_GetUnitNo( t_u1HwChannelID );
	t_u1ChNo = Pil_Spi_GetSpiChNo( t_u1HwChannelID );

	/* オーバーランエラー状態を取得する */
	t_u1Status = ( cpstReg_Mspi[t_u1UnitNo]->stCH[t_u1ChNo].unCEST.u1Data & (U1)MSPI_CEST_OVRUE );
	t_udStatus = (ZORN)t_u1Status;

	return ( t_udStatus );
}
#endif

// #include "Bsw_Seccfg_Prge.h"
// #undef SEL_PRGSEC
#pragma ghs section text=default
/*-- End Of File -------------------------------------------------------------------------------*/
