/* ErrH-r04-3000-0200-b-v00 */
/************************************************************************************************/
/*																								*/
/*		ErrH Driver																				*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

#if 0 // zantei ECCは2月末非対応

#ifndef	ERRH_ECC_H
#define	ERRH_ECC_H

/*==============================================================================================*/
/* include files																				*/
/*==============================================================================================*/

/*==============================================================================================*/
/* defines / data types / structs / unions / macros												*/
/*==============================================================================================*/
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
#define		ERRH_ECC_REGCHECK_NUM			(95)			/* ECCレジスタ診断数 */
#else	/* U2B6の場合 */
#define		ERRH_ECC_REGCHECK_NUM			(73)			/* ECCレジスタ診断数 */
#endif

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* defines																						*/
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* structs / unions																				*/
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*==============================================================================================*/
/* functions																					*/
/*==============================================================================================*/
/*----------------------------------------------------------------------------------------------*/
/* API Functions																				*/
/*----------------------------------------------------------------------------------------------*/
/************************************************************************************************/
/* Service name		:	ECC 1bit Error Clear													*/
/* Reentrancy		:	Re-entrant																*/
/* Parameters(in)	:	ModuleNumber															*/
/* Return value		:	none																	*/
/* Caveats			:	・ECCモジュール番号としてデータ転送経路のH-Busのモジュール(モジュール	*/
/*					:	  番号：No.77～85)を指定した場合、同モジュールのデータバス、アドレス	*/
/*					:	  バスのECC2ビット、1ビットエラーをすべてクリアする。(詳細は、RH850/	*/
/*					:	  U2Bマイコン ユーザーズマニュアルのHBECSTCLRレジスタを参照)			*/
/*					:	・本APIはECMアラーム割り込みからの実行に限定する。						*/
/*					:	・ECMアラーム割り込みにて通知した異常IDを本APIの引数として指定すること。*/
/************************************************************************************************/
void	ErrH_Ecc_ClearEcc1bitErr( U1 t_u1ModuleNum );

/************************************************************************************************/
/* Service name		:	ECC Fatal Error Clear													*/
/* Reentrancy		:	Re-entrant																*/
/* Parameters(in)	:	ModuleNumber															*/
/* Return value		:	none																	*/
/* Caveats			:	・ECCモジュール番号としてデータ転送経路のH-Bus(モジュール番号：No.77～	*/
/*					:	  85、103～111)のモジュールを指定した場合、同モジュールのデータバス、	*/
/*					:	  アドレスバスのECC2ビット、1ビットエラーをすべてクリアする。(詳細は、	*/
/*					:	  RH850/U2Bマイコン ユーザーズマニュアルのHBECSTCLRレジスタを参照)		*/
/*					:	・本APIはECMアラーム割り込みからの実行に限定する。						*/
/*					:	・ECMアラーム割り込みにて通知した異常IDを本APIの引数として指定すること。*/
/************************************************************************************************/
void	ErrH_Ecc_ClearEccFatalErr( U1 t_u1ModuleNum );

/************************************************************************************************/
/* Service name		:	ECC 1bit Error Status Get												*/
/* Reentrancy		:	Concurrency Safe														*/
/* Parameters(in)	:	ModuleNumber															*/
/* Return value		:	ErrorStatus																*/
/* Caveats			:	・本APIはECMアラーム割り込みからの実行に限定する。						*/
/*					:	・ECMアラーム割り込みにて通知した異常IDを本APIの引数として指定すること。*/
/************************************************************************************************/
U1		ErrH_Ecc_GetEcc1bitErrStatus( U1 t_u1ModuleNum );

/************************************************************************************************/
/* Service name		:	ECC Fatal Error Status Get												*/
/* Reentrancy		:	Concurrency Safe														*/
/* Parameters(in)	:	ModuleNumber															*/
/* Return value		:	ErrorStatus																*/
/* Caveats			:	・本APIはECMアラーム割り込みからの実行に限定する。						*/
/*					:	・ECMアラーム割り込みにて通知した異常IDを本APIの引数として指定すること。*/
/************************************************************************************************/
U1		ErrH_Ecc_GetEccFatalErrStatus( U1 t_u1ModuleNum );

/************************************************************************************************/
/* Service name		:	ECC Overflow Status Get													*/
/* Reentrancy		:	Concurrency Safe														*/
/* Parameters(in)	:	ModuleNumber															*/
/* Return value		:	OverflowStatus															*/
/* Caveats			:	・本APIはECMアラーム割り込みからの実行に限定する。						*/
/*					:	・ECMアラーム割り込みにて通知した異常IDを本APIの引数として指定すること。*/
/************************************************************************************************/
U1		ErrH_Ecc_GetEccOvfStatus( U1 t_u1ModuleNum );

/************************************************************************************************/
/* Service name		:	ECC 1bit Error Address Get												*/
/* Reentrancy		:	Concurrency Safe														*/
/* Parameters(in)	:	ModuleNumber, Address(Sync), ArrayNum									*/
/* Return value		:	none																	*/
/* Caveats			:	・本APIはECMアラーム割り込みからの実行に限定する。						*/
/*					:	・ECMアラーム割り込みにて通知した異常IDを本APIの引数として指定すること。*/
/************************************************************************************************/
void	ErrH_Ecc_GetEcc1bitErrAddr( U1 t_u1ModuleNum, U4* t_pu4Address, U1 t_u1ArrayNum );

/************************************************************************************************/
/* Service name		:	ECC Fatal Error Address Get												*/
/* Reentrancy		:	Concurrency Safe														*/
/* Parameters(in)	:	ModuleNumber															*/
/* Return value		:	ErrorAddress															*/
/* Caveats			:	・本APIはECMアラーム割り込みからの実行に限定する。						*/
/*					:	・ECMアラーム割り込みにて通知した異常IDを本APIの引数として指定すること。*/
/************************************************************************************************/
U4		ErrH_Ecc_GetEccFatalErrAddr( U1 t_u1ModuleNum );

/************************************************************************************************/
/* Service name		:	ECC 1bit Error Detailed Information Get									*/
/* Reentrancy		:	Concurrency Safe														*/
/* Parameters(in)	:	ModuleNumber, DetailInformation(Sync), ArrayNum							*/
/* Return value		:	none																	*/
/* Caveats			:	・本APIはECMアラーム割り込みからの実行に限定する。						*/
/*					:	・ECMアラーム割り込みにて通知した異常IDを本APIの引数として指定すること。*/
/************************************************************************************************/
void	ErrH_Ecc_GetEcc1bitErrDetail( U1 t_u1ModuleNum, U1* t_pu1DetailInfo, U1 t_u1ArrayNum );

/************************************************************************************************/
/* Service name		:	ECC Fatal Error Detailed Information Get								*/
/* Reentrancy		:	Concurrency Safe														*/
/* Parameters(in)	:	ModuleNumber															*/
/* Return value		:	ErrorDetailInformation													*/
/* Caveats			:	・本APIはECMアラーム割り込みからの実行に限定する。						*/
/*					:	・ECMアラーム割り込みにて通知した異常IDを本APIの引数として指定すること。*/
/************************************************************************************************/
U1		ErrH_Ecc_GetEccFatalErrDetail( U1 t_u1ModuleNum );

/************************************************************************************************/
/* Service name		:	ECC 1bit Error SPID Get													*/
/* Reentrancy		:	Concurrency Safe														*/
/* Parameters(in)	:	ModuleNumber, ErrorSPID(Sync), ArrayNum									*/
/* Return value		:	none																	*/
/* Caveats			:	・本APIはECMアラーム割り込みからの実行に限定する。						*/
/*					:	・ECMアラーム割り込みにて通知した異常IDを本APIの引数として指定すること。*/
/************************************************************************************************/
void	ErrH_Ecc_GetEcc1bitErrSpid( U1 t_u1ModuleNum, U4* t_pu4ErrSpid, U1 t_u1ArrayNum );

/************************************************************************************************/
/* Service name		:	ECC Fatal Error SPID Get												*/
/* Reentrancy		:	Concurrency Safe														*/
/* Parameters(in)	:	ModuleNumber															*/
/* Return value		:	ErrorSPID																*/
/* Caveats			:	・本APIはECMアラーム割り込みからの実行に限定する。						*/
/*					:	・ECMアラーム割り込みにて通知した異常IDを本APIの引数として指定すること。*/
/************************************************************************************************/
U4		ErrH_Ecc_GetEccFatalErrSpid( U1 t_u1ModuleNum );

/************************************************************************************************/
/* Service name		:	ECC/EDC Stop															*/
/* Reentrancy		:	Re-entrant																*/
/* Parameters(in)	:	none																	*/
/* Return value		:	none																	*/
/* Caveats			:	・本APIはECMアラーム割り込みからの実行に限定する。						*/
/*					:	・本APIはコア0からのコールに限定する。									*/
/************************************************************************************************/
void	ErrH_Ecc_StopEccEdc( void );

/************************************************************************************************/
/* Service name		:	Clear All ECC Error 													*/
/* Reentrancy		:	Re-entrant																*/
/* Parameters(in)	:	none																	*/
/* Return value		:	none																	*/
/* Caveats			:	・本APIはコア0からのコールに限定する。									*/
/*					:	・本APIはInit時の使用に限定する。										*/
/************************************************************************************************/
void	ErrH_Ecc_ClearAllEccError( void );

/************************************************************************************************/
/* Service name		:	Clear ECC Error Status													*/
/* Reentrancy		:	Re-entrant																*/
/* Parameters(in)	:	RAM Type																*/
/* Return value		:	none																	*/
/* Caveats			:	マイコン起動時～ErrH_Init_1()直前まで、もしくはシャットダウン中のみ		*/
/*					:	使用可能。																*/
/************************************************************************************************/
void	ErrH_Ecc_ClearEccErrorStatus( U1 t_u1RamType );

/************************************************************************************************/
/* Service name		:	Get ECC Error Status													*/
/* Reentrancy		:	Concurrency Safe														*/
/* Parameters(in)	:	RAM Type																*/
/* Return value		:	Error Detect Status(=0:not error detect, !=0:error detect)				*/
/* Caveats			:	none																	*/
/************************************************************************************************/
ZORN	ErrH_Ecc_GetEccErrorStatus( U1 t_u1RamType );

/************************************************************************************************/
/* Service name		:	Request Register Diag Function											*/
/* Reentrancy		:	Non Re-entrant															*/
/* Parameters(in)	:	*ConfigTable(Sync)														*/
/* Return value		:	Register Diag Result													*/
/* Caveats			:	・本APIはコア0からのコールに限定する。									*/
/*					:	・ErrH_StopEccEdc()コール後、本APIをコールしないこと。					*/
/************************************************************************************************/
U1	ErrH_Ecc_CheckReg_ASIL( const ErrH_RegCheckConfigType *t_pcstConfigTable );

/*----------------------------------------------------------------------------------------------*/
/* Scheduled / Event Functions																	*/
/*----------------------------------------------------------------------------------------------*/
/************************************************************************************************/
/* Function			:	Initialization															*/
/* Schedule			:	Init																	*/
/* Parameters(in)	:	none																	*/
/************************************************************************************************/
void	ErrH_Ecc_Init( void );

/************************************************************************************************/
/* Function			:	De-Initialization														*/
/* Schedule			:	DeInit																	*/
/* Parameters(in)	:	none																	*/
/************************************************************************************************/
void	ErrH_Ecc_DeInit( void );


/*==============================================================================================*/
/* constants																					*/
/*==============================================================================================*/
extern	const	ErrH_RegCheckType		cstErrH_EccRegCheckTbl[ ERRH_ECC_REGCHECK_NUM ];									/* Register Check Table(ECC) */
extern	const	ErrH_RegCheckConfigType	cstErrH_UcfgEccRegCheckData;														/* Register Check Data(ECC) */

#endif	/* ERRH_ECC_H */

#endif // zantei ECCは2月末非対応
/*-- End Of File -------------------------------------------------------------------------------*/
