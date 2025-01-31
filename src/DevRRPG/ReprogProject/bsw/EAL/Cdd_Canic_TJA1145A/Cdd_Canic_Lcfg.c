/* Cdd_Canic-r03-5000-0200-a-v09 */
/************************************************************************************************/
/*																								*/
/*		CAN Transceiver IC Communication Driver (TJA1145A) User Configuration					*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

/*==============================================================================================*/
/* include files																				*/
/*==============================================================================================*/
#include	"Std_Types.h"
#include	"Cdd_Canic.h"			/* 自ユニットのヘッダファイル */
#include	"Cdd_Canic_Lcfg.h"		/* 自ユニットのヘッダファイル */

//#include	"Dioh.h"			/* 使用ユニットのヘッダファイル */
#include	"Pf_Types.h"
//#include	"Dio.h"				/* 使用ユニットのヘッダファイル */
#include	"Rte_BswUcfg.h"		/* 関連ユニットのコンフィグファイル */

/*==============================================================================================*/
/* defines / data types / structs / unions	/ macros											*/
/*==============================================================================================*/

/*----------------------------------------------------------------------------------------------*/
/* 初期化-Idle-終了処理にかけて一貫して変化しない設定値を管理する。                             */
/* 動的に変化するレジスタ設定値（ビットフィールド）等はここでは定義せず、                       */
/* Cdd_Canic.cに定義してユースケースに応じて適宜使用する設計・実装とすること。                  */
/*----------------------------------------------------------------------------------------------*/
#define	Cdd_Canic_Set_IcConfig(id) \
{ \
	(U1)SPI_COMA_ID_CANTRCV_##id, \
	(U1)CDD_CANIC_UCFG_IC##id##_COREID, \
	(U4)DIOH_ID_O_CANIC_WAKE_##id, \
	(U4)0,  /* INH 設定不要 */ 		\
	/* Lock Control Register */ \
	(U1)CDD_CANIC_LKXC_ALL_UNLOCK \
	, \
	(U1)( /* System Event Enable Register */ \
	     ( (U1)CDD_CANIC_OTWE_DISABLE  * (U1)BIT2 ) | \
	     ( (U1)CDD_CANIC_SPIFE_DISABLE * (U1)BIT1 ) \
	), \
	(U1)( /* Transceiver Event Enable Register */ \
	     ( (U1)CDD_CANIC_CBSE_DISABLE                 * (U1)BIT4 ) | \
	     ( (U1)CDD_CANIC_CFE_DISABLE                  * (U1)BIT1 ) | \
	     ( (U1)CDD_CANIC_UCFG_IC##id##_CWE_DETECTION  * (U1)BIT0 ) \
	), \
	(U1)( /* WAKE Pin Enable Register */ \
	     ( (U1)CDD_CANIC_UCFG_IC##id##_WAKEPIN_EN_WPRE  * (U1)BIT1 ) | \
	     ( (U1)CDD_CANIC_UCFG_IC##id##_WAKEPIN_EN_WPFE * (U1)BIT0 ) \
	), \
	(U1)( /* CAN Control Register (Template) */ \
	     ( (U1)CDD_CANIC_UCFG_IC##id##_CANFD_TOLERANCE * (U1)BIT6 ) | \
	     ( (U1)CDD_CANIC_UCFG_IC##id##_PARTIAL_NETWORK * (U1)BIT5 ) | \
	     ( (U1)CDD_CANIC_UCFG_IC##id##_PARTIAL_NETWORK * (U1)BIT4 ) \
	), \
	/* WUF DataRate Register */ \
	(U1)CDD_CANIC_UCFG_IC##id##_WUF_DATARATE \
	, \
	/* WUF ID0-3 Register */ \
	(U1)CDD_CANIC_UCFG_IC##id##_WUF_ID0, \
	(U1)CDD_CANIC_UCFG_IC##id##_WUF_ID1, \
	(U1)CDD_CANIC_UCFG_IC##id##_WUF_ID2, \
	(U1)CDD_CANIC_UCFG_IC##id##_WUF_ID3 \
	, \
	/* WUF ID0-3 Mask Register */ \
	(U1)CDD_CANIC_UCFG_IC##id##_WUF_IDMASK0, \
	(U1)CDD_CANIC_UCFG_IC##id##_WUF_IDMASK1, \
	(U1)CDD_CANIC_UCFG_IC##id##_WUF_IDMASK2, \
	(U1)CDD_CANIC_UCFG_IC##id##_WUF_IDMASK3 \
	, \
	(U1)( /* CAN Frame Control Register */ \
	     ( (U1)CDD_CANIC_UCFG_IC##id##_IDE * (U1)BIT7 ) | \
	     ( (U1)CDD_CANIC_UCFG_IC##id##_WUF_DATAMASK * (U1)BIT6 ) | \
	     ( (U1)CDD_CANIC_UCFG_IC##id##_DLC ) \
	), \
	/* WUF DATA MASK0-9 Register */ \
	(U1)CDD_CANIC_UCFG_IC##id##_WUF_DATAMASK0, \
	(U1)CDD_CANIC_UCFG_IC##id##_WUF_DATAMASK1, \
	(U1)CDD_CANIC_UCFG_IC##id##_WUF_DATAMASK2, \
	(U1)CDD_CANIC_UCFG_IC##id##_WUF_DATAMASK3, \
	(U1)CDD_CANIC_UCFG_IC##id##_WUF_DATAMASK4, \
	(U1)CDD_CANIC_UCFG_IC##id##_WUF_DATAMASK5, \
	(U1)CDD_CANIC_UCFG_IC##id##_WUF_DATAMASK6, \
	(U1)CDD_CANIC_UCFG_IC##id##_WUF_DATAMASK7 \
}

/*==============================================================================================*/
/* variables																					*/
/*==============================================================================================*/

/*==============================================================================================*/
/* constants																					*/
/*==============================================================================================*/
//#define		SEL_ROMSEC		(CDD_CANIC_CFG_SEC_ROM0)
//#include	"Cdd_Seccfg_Roms.h"
#pragma ghs section rosdata=".CANIC_RODATA_CONST"

const	Cdd_Canic_IcConfigType	cstCdd_Canic_UcfgIcData[CDD_CANIC_CFG_IC_NUM] =
{
	Cdd_Canic_Set_IcConfig(0)
};

const	Cdd_Canic_UserConfigType	cstCdd_Canic_UcfgData =
{
	&(cstCdd_Canic_UcfgIcData[0])	/* *pcstIcCfg */
};

//#include	"Cdd_Seccfg_Rome.h"
//#undef		SEL_ROMSEC
#pragma ghs section rosdata=default
/*-- End Of File -------------------------------------------------------------------------------*/
