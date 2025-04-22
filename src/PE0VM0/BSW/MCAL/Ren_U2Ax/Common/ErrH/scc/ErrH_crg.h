/* ErrH-r04-3000-0200-b-v00 */
/************************************************************************************************/
/*																								*/
/*		ErrH Driver																				*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

#if 0 // zantei MPUは2月末非対応

#ifndef ERRH_CRG_H
#define ERRH_CRG_H

/*==============================================================================================*/
/*	include files																				*/
/*==============================================================================================*/
#include	"errh_reg_crg.h"

/*==============================================================================================*/
/* defines / data types / structs / unions	/ macros											*/
/*==============================================================================================*/
/* CRG Protection Setting Type Definition */
typedef	struct
{
	U4		u4Addv;							/* チャネル有効ビット設定 */
	U4		u4Base;							/* チャネルベースアドレス設定 */
	U4		u4Prot;							/* チャネル保護制御 */
	U4		u4Spid;							/* チャネル SPID 設定 */
}	ErrH_CrgProtSetType;

/*==============================================================================================*/
/* functions																					*/
/*==============================================================================================*/
/*----------------------------------------------------------------------------------------------*/
/* API Functions																				*/
/*----------------------------------------------------------------------------------------------*/
/************************************************************************************************/
/* Service name		:	Set Mode & Start CRG Guard												*/
/* Reentrancy		:	Non Re-entrant															*/
/* Parameters		:	Area - ID of Area Number( AREA_ID0 / 1 / 2 / 3 / 4 / 5 / 6 / 7 )		*/
/*					:	ClNum -   Cluster0/Cluster1( 0 / 1 )									*/
/*					:	*ProtectionSetting(Sync)												*/
/* Return value		:	none																	*/
/* Caveats			:	・本APIはコア0からのコールに限定する。									*/
/*					:	・本APIはInit時の使用に限定する。										*/
/************************************************************************************************/
void	ErrH_Crg_SetModeStartCrgGuard( U1 t_u1Area , U1 t_u1ClNum , const ErrH_CrgProtSetType *t_pcstProtSet );

/************************************************************************************************/
/* Service name		:	Set Mode & Start CSG Guard												*/
/* Reentrancy		:	Non Re-entrant															*/
/* Parameters		:	Area - ID of Area Number( AREA_ID0 / 1 / 2 / 3 )						*/
/*					:	ClNum -   Cluster0/Cluster1( 0 / 1 )									*/
/*					:	*ProtectionSetting(Sync)												*/
/* Return value		:	none																	*/
/* Caveats			:	・本APIはコア0からのコールに限定する。									*/
/*					:	・本APIはInit時の使用に限定する。										*/
/************************************************************************************************/
void	ErrH_Crg_SetModeStartCsgGuard( U1 t_u1Area , U1 t_u1ClNum , const ErrH_CrgProtSetType *t_pcstProtSet );

/************************************************************************************************/
/* Service name		:	CRG Clear Error 														*/
/* Reentrancy		:	Re-entrant																*/
/* Parameters (in)	:	ModuleNum - CRG Module Number( 100 ～ 110  )							*/
/* Return value		:	none																	*/
/* Caveats			:	・本APIはECMアラーム割り込みからの実行に限定する。						*/
/*					:	・ECMアラーム割り込みにて通知した異常IDを本APIの引数として指定すること。*/
/************************************************************************************************/
void	ErrH_Crg_ClearError( U2 t_u2ModuleNum );

/************************************************************************************************/
/* Service name		:	CRG Get Error Status													*/
/* Reentrancy		:	Concurrency Safe														*/
/* Parameters (in)	:	ModuleNum - CRG Module Number( 100 ～ 110  )							*/
/* Return value		:	Error Status 															*/
/* Caveats			:	・本APIはECMアラーム割り込みからの実行に限定する。						*/
/*					:	・ECMアラーム割り込みにて通知した異常IDを本APIの引数として指定すること。*/
/************************************************************************************************/
U4	ErrH_Crg_GetErrorStatus( U2 t_u2ModuleNum );

/************************************************************************************************/
/* Service name		:	CRG Get Error Address													*/
/* Reentrancy		:	Concurrency Safe														*/
/* Parameters (in)	:	ModuleNum - CRG Module Number( 100 ～ 110  )							*/
/* Return value		:	Error Address															*/
/* Caveats			:	・本APIはECMアラーム割り込みからの実行に限定する。						*/
/*					:	・ECMアラーム割り込みにて通知した異常IDを本APIの引数として指定すること。*/
/************************************************************************************************/
U4	ErrH_Crg_GetErrAddress( U2 t_u2ModuleNum  );

/************************************************************************************************/
/* Service name		:	CRG Get Error Access info												*/
/* Reentrancy		:	Concurrency Safe														*/
/* Parameters (in)	:	ModuleNum - CRG Module Number( 100 ～ 110  )							*/
/* Return value		:	Error Access info														*/
/* Caveats			:	・本APIはECMアラーム割り込みからの実行に限定する。						*/
/*					:	・ECMアラーム割り込みにて通知した異常IDを本APIの引数として指定すること。*/
/************************************************************************************************/
U4	ErrH_Crg_GetErrAccessInfo( U2 t_u2ModuleNum  );

/*----------------------------------------------------------------------------------------------*/
/* Scheduled / Event Functions																	*/
/*----------------------------------------------------------------------------------------------*/


#endif /* ERRH_CRG_H */
#endif // zantei MPUは2月末非対応
/*-- End Of File -------------------------------------------------------------------------------*/
