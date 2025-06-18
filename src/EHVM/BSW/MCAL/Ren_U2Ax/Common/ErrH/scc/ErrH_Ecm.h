/* ErrH-r04-3000-0200-b-v00 */
/************************************************************************************************/
/*																								*/
/*		ErrH Driver																				*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

#ifndef ERRH_ECM_H
#define ERRH_ECM_H

/*==============================================================================================*/
/*	include files																				*/
/*==============================================================================================*/
#include	"errh_reg_ecm.h"

/*==============================================================================================*/
/* defines / data types / structs / unions	/ macros											*/
/*==============================================================================================*/
#define		ERRH_ECM_MASTER					(0U)			/* ECMマスタ側ID				 */
#define		ERRH_ECM_CHECKER				(1U)			/* ECMチェッカ側ID				 */

#define		ERRH_ECM_ERROR_ID_REG_NUM		(32)			/* レジスタ毎のエラー数			 */

#if ( MCU_TYPE_SERIES == MCU_RH850U2A6 )
#define			ERRH_ECM_CONFIG_REG_NUM			(9)				/* コンフィグレジスタ数						 */
#else	/* U2A16 */
#define			ERRH_ECM_CONFIG_REG_NUM			(11)			/* コンフィグレジスタ数						 */
#endif

#if ( MCU_TYPE_SERIES == MCU_RH850U2A16 )
#define			ERRH_ECM_CONFIG_CORE_NUM		(4)				/* コンフィグコア数							 */
#else	/* U2A6の場合 */
#define			ERRH_ECM_CONFIG_CORE_NUM		(2)				/* コンフィグコア数							 */
#endif

#if 0 // zantei REGCHKは2月末非対応
#if ( MCU_TYPE_SERIES == MCU_RH850U2A16 )
#define		ERRH_ECM_REGCHECK_NUM			(77)			/* ECMレジスタ診断数 */
#else	/* U2B6の場合 */
#define		ERRH_ECM_REGCHECK_NUM			(60)			/* ECMレジスタ診断数 */
#endif
#endif // zantei REGCHKは2月末非対応

/*==============================================================================================*/
/* functions																					*/
/*==============================================================================================*/
/*----------------------------------------------------------------------------------------------*/
/* API Functions																				*/
/*----------------------------------------------------------------------------------------------*/
/************************************************************************************************/
/* Service name		:	Clear Error Status														*/
/* Reentrancy		:	Re-entrant																*/
/* Parameters (in)	:	ErrorID																	*/
/* Return value		:	none																	*/
/* Caveats			:	本APIはECMアラーム割り込みからの実行に限定する。						*/
/************************************************************************************************/
void	ErrH_Ecm_ClearErrorStatus( U2 t_u2ErrorID );

/************************************************************************************************/
/* Service name		:	Request Register Check Function											*/
/* Reentrancy		:	Non Re-entrant															*/
/* Parameters(in)	:	*ConfigTable(Sync)														*/
/* Return value		:	Register Check Result													*/
/* Caveats			:	本APIはコア0からのコールに限定する。									*/
/************************************************************************************************/
U1	ErrH_Ecm_CheckReg_ASIL( const ErrH_RegCheckConfigType *t_pcstConfigTable );

/*----------------------------------------------------------------------------------------------*/
/* Scheduled / Event Functions																	*/
/*----------------------------------------------------------------------------------------------*/
/************************************************************************************************/
/* Function			:	Alarm Interrupt															*/
/* Schedule			:	ErrH_AlarmInterrupt														*/
/* Parameters(in)	:	*ConfigTable(Sync)														*/
/************************************************************************************************/
void	ErrH_Ecm_AlarmInterrupt( const U4 *t_pcu4ConfigTable );

/************************************************************************************************/
/* Function			:	Before Initialization													*/
/* Schedule			:	ErrH_Init_0( EcuM_AL_DriverInitZero_Core0 , EcuM_AL_DriverInitZero_Core1 )	*/
/* Parameters(in)	:	CoreID																	*/
/*					:	*ConfigTable(Sync)														*/
/************************************************************************************************/
void	ErrH_Ecm_PreInit( U4 t_u4CoreId, const U4 *t_pcu4ConfigTable );

/************************************************************************************************/
/* Function			:	Initialization															*/
/* Schedule			:	ErrH_Init_1( EcuM_AL_DriverInitZero_Core0 , EcuM_AL_DriverInitZero_Core1 )	*/
/* Parameters(in)	:	CoreID																	*/
/*					:	*ConfigData(Sync)														*/
/************************************************************************************************/
void	ErrH_Ecm_Init( U4 t_u4CoreId, const ErrH_UserConfigType *t_pcstConfigData );


/*==============================================================================================*/
/* constants																					*/
/*==============================================================================================*/
extern	const	U4						cu4ErrH_UcfgNcfIrTypeData[ERRH_ECM_CONFIG_REG_NUM];									/* ECMISCFG @ Maskable Interrupt */
extern	const	U4						cu4ErrH_UcfgNcfNotifCoreData[ERRH_ECM_CONFIG_CORE_NUM][ERRH_ECM_CONFIG_REG_NUM];	/* Maskable Interrupt */
extern	const	U4						cu4ErrH_UcfgNcfInitInfData[ERRH_ECM_CONFIG_REG_NUM];								/* Init Inform */
extern	const	U4						cu4ErrH_UcfgNcfResetData[ERRH_ECM_CONFIG_REG_NUM];									/* ECMIRCFGn @ Internal Reset */
extern	const	U4						cu4ErrH_UcfgNcfEoutData[ERRH_ECM_CONFIG_REG_NUM];									/* ECMEMKn @ Errorout Mask */

#if 0 // zantei REGCHKは2月末非対応
extern	const	ErrH_RegCheckType		cstErrH_EcmRegCheckTbl[ ERRH_ECM_REGCHECK_NUM ];									/* Register Check Table(ECM) */
extern	const	ErrH_RegCheckConfigType	cstErrH_UcfgEcmRegCheckData;														/* Register Check Data(ECM) */
#endif // zantei REGCHKは2月末非対応

#endif /* ERRH_ECM_H */
/*-- End Of File -------------------------------------------------------------------------------*/
