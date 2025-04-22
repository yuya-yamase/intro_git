/* ErrH-r04-3000-0200-b-v00 */
/************************************************************************************************/
/*																								*/
/*		ErrH Driver																				*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

#if 0 // zantei MPUは2月末非対応

#ifndef ERRH_SLG_H
#define ERRH_SLG_H

/*==============================================================================================*/
/*	include files																				*/
/*==============================================================================================*/
#include	"ErrH.h"

/*==============================================================================================*/
/* defines / data types / structs / unions	/ macros											*/
/*==============================================================================================*/
#define		ERRH_SLG_CORE_NUM				(3)						/* CORE数 */

/* PEG */
#define		ERRH_SLG_PEG_AREA_NUM			(8)						/* PEG領域数 */

/* CRG */
#define		ERRH_SLG_CRAM_CL_NUM			(2)						/* CRAM実装クラスタ数 */
#define		ERRH_SLG_CRAM_CL0				(0U)					/* CRAM0 */
#define		ERRH_SLG_CRAM_CL1				(1U)					/* CRAM1 */
#define		ERRH_SLG_CRG_CRG_AREA_NUM		(8)						/* CRG領域数 */
#define		ERRH_SLG_CRG_CSG_AREA_NUM		(4)						/* CSG領域数 */
#define		ERRH_SLG_DMA_BUSMASTER_NUM		(3)						/* DMAのバスマスタ数 */

/* DMACG */
#define		ERRH_SLG_DMA0					(0x00U)					/* DMA0 */
#define		ERRH_SLG_DMA1					(0x01U)					/* DMA1 */

/* PBG */
#define		ERRH_SLG_PBG_GROUP_NUM			(28)					/* グループ数 */
#define		ERRH_SLG_PBG_CHANNEL_NUM		(16)					/* チャネル数 */

#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_TRIPLECORE ) )
#define		ERRH_SLG_CONFIG_CORE_NUM		(3)				/* コンフィグコア数							 */
#else	/* U2B6、またはU2B10でデュアルコアの場合 */
#define		ERRH_SLG_CONFIG_CORE_NUM		(2)				/* コンフィグコア数							 */
#endif

#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
#define		ERRH_SLG_REGCHECK_NUM			(252)					/* SLGレジスタ診断数 */
#else	/* U2B6の場合 */
#define		ERRH_SLG_REGCHECK_NUM			(172)					/* SLGレジスタ診断数 */
#endif

/*==============================================================================================*/
/* functions																					*/
/*==============================================================================================*/
/*----------------------------------------------------------------------------------------------*/
/* API Functions																				*/
/*----------------------------------------------------------------------------------------------*/
/************************************************************************************************/
/* Service name		:	Slave Guard Clear Error													*/
/* Reentrancy		:	Re-entrant																*/
/* Parameters (in)	:	ErrorID 																*/
/*					:	ModuleNum																*/
/* Return value		:	none																	*/
/* Caveats			:	・本APIはECMアラーム割り込みからの実行に限定する。						*/
/*					:	・ECMアラーム割り込みにて通知した異常IDを本APIの引数として指定すること。*/
/************************************************************************************************/
void	ErrH_Slg_ClearError( U2 t_u2ErrorID, U2 t_u2ModuleNum );

/************************************************************************************************/
/* Service name		:	Slave Guard Get Error Status											*/
/* Reentrancy		:	Concurrency Safe														*/
/* Parameters (in)	:	ErrorID 																*/
/*					:	ModuleNum																*/
/* Return value		:	Error Status															*/
/* Caveats			:	・本APIはECMアラーム割り込みからの実行に限定する。						*/
/*					:	・ECMアラーム割り込みにて通知した異常IDを本APIの引数として指定すること。*/
/************************************************************************************************/
U4	ErrH_Slg_GetErrStatus( U2 t_u2ErrorID, U2 t_u2ModuleNum );

/************************************************************************************************/
/* Service name		:	Slave Guard Get Error Address											*/
/* Reentrancy		:	Concurrency Safe														*/
/* Parameters (in)	:	ErrorID 																*/
/*					:	ModuleNum																*/
/* Return value		:	Error Address															*/
/* Caveats			:	・本APIはECMアラーム割り込みからの実行に限定する。						*/
/*					:	・ECMアラーム割り込みにて通知した異常IDを本APIの引数として指定すること。*/
/************************************************************************************************/
U4	ErrH_Slg_GetErrAddress( U2 t_u2ErrorID, U2 t_u2ModuleNum );

/************************************************************************************************/
/* Service name		:	Slave Guard Get Error Access Info										*/
/* Reentrancy		:	Concurrency Safe														*/
/* Parameters (in)	:	ErrorID 																*/
/*					:	ModuleNum																*/
/* Return value		:	Error Access Inof														*/
/* Caveats			:	・本APIはECMアラーム割り込みからの実行に限定する。						*/
/*					:	・ECMアラーム割り込みにて通知した異常IDを本APIの引数として指定すること。*/
/************************************************************************************************/
U4	ErrH_Slg_GetErrAccessInfo( U2 t_u2ErrorID, U2 t_u2ModuleNum );

/************************************************************************************************/
/* Service name		:	Slave Guard Disable All Guard											*/
/* Reentrancy		:	Non Re-entrant															*/
/* Parameters (in)	:	none																	*/
/* Return value		:	none																	*/
/* Caveats			:	・本APIはコア0からのコールに限定する。									*/
/*					:	・本APIはInit時の使用に限定する。										*/
/************************************************************************************************/
void	ErrH_Slg_DisableAllGuard( void );

/************************************************************************************************/
/* Service name		:	Request Register Diag Function											*/
/* Reentrancy		:	Non Re-entrant															*/
/* Parameters(in)	:	*ConfigTable(Sync)														*/
/* Return value		:	Register Diag Result													*/
/* Caveats			:	本APIはコア0からのコールに限定する。									*/
/************************************************************************************************/
U1	ErrH_Slg_CheckReg_ASIL( const ErrH_RegCheckConfigType *t_pcstConfigTable );

/*----------------------------------------------------------------------------------------------*/
/* Scheduled / Event Functions																	*/
/*----------------------------------------------------------------------------------------------*/
/************************************************************************************************/
/* Function			:	Initialization															*/
/* Schedule			:	EcuM_AL_DriverInitOne_Core0												*/
/* Parameters(in)	:	*ConfigData(Sync)														*/
/************************************************************************************************/
void	ErrH_Slg_Init( const ErrH_UserConfigType *t_pcstConfigData );


/*==============================================================================================*/
/* constants																					*/
/*==============================================================================================*/
extern	const	ErrH_PegConfigType		cu4ErrH_UcfgPegData[ ERRH_SLG_CONFIG_CORE_NUM ][ ERRH_SLG_PEG_AREA_NUM ];			/* PEG Config Data */
extern	const	ErrH_CrgConfigType		cu4ErrH_UcfgCrgCrgData[ ERRH_SLG_CRAM_CL_NUM ][ ERRH_SLG_CRG_CRG_AREA_NUM ];		/* CRG Config Data */
extern	const	ErrH_CrgConfigType		cu4ErrH_UcfgCrgCsgData[ ERRH_SLG_CRAM_CL_NUM ][ ERRH_SLG_CRG_CSG_AREA_NUM ];		/* CSG Config Data */
extern	const	U4						cu4ErrH_UcfgSpidMaskData[ ERRH_SLG_DMA_BUSMASTER_NUM ];								/* CSG Config Data */
extern	const	ErrH_PbgConfigType		cstErrH_UcfgPbgData;																/* PBG Config Data */

extern	const	ErrH_RegCheckType		cstErrH_SlgRegCheckTbl[ ERRH_SLG_REGCHECK_NUM ];									/* Register Check Table(SLG) */
extern	const	ErrH_RegCheckConfigType	cstErrH_UcfgSlgRegCheckData;														/* Register Check Data(SLG) */

#endif /* ERRH_SLG_H */
#endif // zantei MPUは2月末非対応
/*-- End Of File -------------------------------------------------------------------------------*/
