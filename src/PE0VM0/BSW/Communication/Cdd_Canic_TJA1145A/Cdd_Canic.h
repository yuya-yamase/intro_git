/* Cdd_Canic-r03-5000-0200-a-v09 */
/************************************************************************************************/
/*																								*/
/*		CAN Transceiver IC Communication Driver (TJA1145A)										*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

#ifndef	CDD_CANIC_H
#define	CDD_CANIC_H

/*==============================================================================================*/
/* defines																						*/
/*==============================================================================================*/
#define	CDD_CANIC_SW_VARI_VERSION		50
#define	CDD_CANIC_SW_REQ_MAJOR_VERSION	0
#define	CDD_CANIC_SW_REQ_INDIV_VERSION	(-1)
#define	CDD_CANIC_SW_SRC_MAJOR_VERSION	0

/*==============================================================================================*/
/* include files																				*/
/*==============================================================================================*/
#include	"Cdd_Canic_Cfg.h"		/* 自ユニットのコンフィグヘッダファイル */


/*==============================================================================================*/
/* data types / structs / unions / macros														*/
/*==============================================================================================*/


typedef struct {
	U1								u1SpiChId;				/*!< Description: SPIチャネルID			\n*/
															/*!< LSB   : 1							\n*/
															/*!< Offset: 0							\n*/
															/*!< Unit  : -							\n*/
															/*!< Range : SPIEXT_ID_CANIC_0			*/
	U1								u1CoreId;				/*!< Description: 割付コアID			\n*/
															/*!< LSB   : 1							\n*/
															/*!< Offset: 0							\n*/
															/*!< Unit  : -							\n*/
															/*!< Range : 0～3						*/
	U4								u4DiohChIdWriteWake;	/*!< Description: DIOHチャネルID(WAKE)	\n*/
															/*!< LSB   : -							\n*/
															/*!< Offset: -							\n*/
															/*!< Unit  : -							\n*/
															/*!< Range : DIOH_ID_O_CANIC_WAKE_0		*/
	U4								u4DiohChIdReadInh;		/*!< Description: DIOHチャネルID(INH)	\n*/
															/*!< LSB   : -							\n*/
															/*!< Offset: -							\n*/
															/*!< Unit  : -							\n*/
															/*!< Range : DIOH_ID_I_CANIC_INH_0		*/
	U1								u1RegLockControl;		/*!< Description: Lock Controlレジスタ設定				\n*/
															/*!< LSB   : -											\n*/
															/*!< Offset: -											\n*/
															/*!< Unit  : -											\n*/
															/*!< Range : -											*/
	U1								u1RegSystemEventEnable;	/*!< Description: System Event Enableレジスタ設定		\n*/
															/*!< LSB   : -											\n*/
															/*!< Offset: -											\n*/
															/*!< Unit  : -											\n*/
															/*!< Range : -											*/
	U1								u1RegTrscvEventEnable;	/*!< Description: Transceiver Event Enableレジスタ設定	\n*/
															/*!< LSB   : -											\n*/
															/*!< Offset: -											\n*/
															/*!< Unit  : -											\n*/
															/*!< Range : -											*/
	U1								u1RegWakePinEnable;		/*!< Description: WAKE Pin Enableレジスタ設定			\n*/
															/*!< LSB   : -											\n*/
															/*!< Offset: -											\n*/
															/*!< Unit  : -											\n*/
															/*!< Range : -											*/
	U1								u1RegTmpltCanControl;	/*!< Description: CAN Controlレジスタ設定テンプレート	\n*/
															/*!< LSB   : -											\n*/
															/*!< Offset: -											\n*/
															/*!< Unit  : -											\n*/
															/*!< Range : -											*/
	U1								u1RegWufDataRate;		/*!< Description: WUF DataRateレジスタ設定				\n*/
															/*!< LSB   : -											\n*/
															/*!< Offset: -											\n*/
															/*!< Unit  : -											\n*/
															/*!< Range : -											*/
	U1								u1RegWufId0;			/*!< Description: WUF ID0レジスタ設定					\n*/
															/*!< LSB   : -											\n*/
															/*!< Offset: -											\n*/
															/*!< Unit  : -											\n*/
															/*!< Range : -											*/
	U1								u1RegWufId1;			/*!< Description: WUF ID1レジスタ設定					\n*/
															/*!< LSB   : -											\n*/
															/*!< Offset: -											\n*/
															/*!< Unit  : -											\n*/
															/*!< Range : -											*/
	U1								u1RegWufId2;			/*!< Description: WUF ID2レジスタ設定					\n*/
															/*!< LSB   : -											\n*/
															/*!< Offset: -											\n*/
															/*!< Unit  : -											\n*/
															/*!< Range : -											*/
	U1								u1RegWufId3;			/*!< Description: WUF ID3レジスタ設定					\n*/
															/*!< LSB   : -											\n*/
															/*!< Offset: -											\n*/
															/*!< Unit  : -											\n*/
															/*!< Range : -											*/
	U1								u1RegWufIdMask0;		/*!< Description: WUF IDMASK0レジスタ設定			\n*/
															/*!< LSB   : -											\n*/
															/*!< Offset: -											\n*/
															/*!< Unit  : -											\n*/
															/*!< Range : -											*/
	U1								u1RegWufIdMask1;		/*!< Description: WUF IDMASK1レジスタ設定			\n*/
															/*!< LSB   : -											\n*/
															/*!< Offset: -											\n*/
															/*!< Unit  : -											\n*/
															/*!< Range : -											*/
	U1								u1RegWufIdMask2;		/*!< Description: WUF IDMASK2レジスタ設定			\n*/
															/*!< LSB   : -											\n*/
															/*!< Offset: -											\n*/
															/*!< Unit  : -											\n*/
															/*!< Range : -											*/
	U1								u1RegWufIdMask3;		/*!< Description: WUF IDMASK3レジスタ設定			\n*/
															/*!< LSB   : -											\n*/
															/*!< Offset: -											\n*/
															/*!< Unit  : -											\n*/
															/*!< Range : -											*/
	U1								u1RegFrameControl;		/*!< Description: Frame Controlレジスタ設定				\n*/
															/*!< LSB   : -											\n*/
															/*!< Offset: -											\n*/
															/*!< Unit  : -											\n*/
															/*!< Range : -											*/
															
	U1								u1RegWufDataMask0;		/*!< Description: Wuf Data Mask0レジスタ設定			\n*/
															/*!< LSB   : -											\n*/
															/*!< Offset: -											\n*/
															/*!< Unit  : -											\n*/
															/*!< Range : -											*/

	U1								u1RegWufDataMask1;		/*!< Description: Wuf Data Mask1レジスタ設定			\n*/
															/*!< LSB   : -											\n*/
															/*!< Offset: -											\n*/
															/*!< Unit  : -											\n*/
															/*!< Range : -											*/
															
	U1								u1RegWufDataMask2;		/*!< Description: Wuf Data Mask2レジスタ設定			\n*/
															/*!< LSB   : -											\n*/
															/*!< Offset: -											\n*/
															/*!< Unit  : -											\n*/
															/*!< Range : -											*/

	U1								u1RegWufDataMask3;		/*!< Description: Wuf Data Mask3レジスタ設定			\n*/
															/*!< LSB   : -											\n*/
															/*!< Offset: -											\n*/
															/*!< Unit  : -											\n*/
															/*!< Range : -											*/
	U1								u1RegWufDataMask4;		/*!< Description: Wuf Data Mask4レジスタ設定			\n*/
															/*!< LSB   : -											\n*/
															/*!< Offset: -											\n*/
															/*!< Unit  : -											\n*/
															/*!< Range : -											*/

	U1								u1RegWufDataMask5;		/*!< Description: Wuf Data Mask5レジスタ設定			\n*/
															/*!< LSB   : -											\n*/
															/*!< Offset: -											\n*/
															/*!< Unit  : -											\n*/
															/*!< Range : -											*/
															
	U1								u1RegWufDataMask6;		/*!< Description: Wuf Data Mask6レジスタ設定			\n*/
															/*!< LSB   : -											\n*/
															/*!< Offset: -											\n*/
															/*!< Unit  : -											\n*/
															/*!< Range : -											*/

	U1								u1RegWufDataMask7;		/*!< Description: Wuf Data Mask7レジスタ設定			\n*/
															/*!< LSB   : -											\n*/
															/*!< Offset: -											\n*/
															/*!< Unit  : -											\n*/
															/*!< Range : -											*/
} Cdd_Canic_IcConfigType;

typedef struct {
	const	Cdd_Canic_IcConfigType	*pcstIcCfg;		/*!< Description: ICコンフィグデータ	\n*/
													/*!< LSB   : -							\n*/
													/*!< Offset: -							\n*/
													/*!< Unit  : -							\n*/
													/*!< Range : -							*/
} Cdd_Canic_UserConfigType;

#define		CDD_CANIC_OTWE_DISABLE		(0x00)
/*!< Description: System Event Enableレジスタ::OTWE値（Disable）	\n*/
/*!< Type  : U1														\n*/
/*!< LSB   : -														\n*/
/*!< Offset: -														\n*/
/*!< Unit  : -														\n*/

#define		CDD_CANIC_SPIFE_DISABLE		(0x00)
/*!< Description: System Event Enableレジスタ::SPIFE値（Disable）	\n*/
/*!< Type  : U1														\n*/
/*!< LSB   : -														\n*/
/*!< Offset: -														\n*/
/*!< Unit  : -														\n*/

#define		CDD_CANIC_CBSE_DISABLE		(0x00)
/*!< Description: Transceiver Event Enableレジスタ::CBSE値（Disable）	\n*/
/*!< Type  : U1															\n*/
/*!< LSB   : -															\n*/
/*!< Offset: -															\n*/
/*!< Unit  : -															\n*/

#define		CDD_CANIC_CFE_DISABLE		(0x00)
/*!< Description: Transceiver Event Enableレジスタ::CFE値（Disable）	\n*/
/*!< Type  : U1															\n*/
/*!< LSB   : -															\n*/
/*!< Offset: -															\n*/
/*!< Unit  : -															\n*/

#define		CDD_CANIC_CWE_DISABLE		(0x00)
/*!< Description: Transceiver Event Enableレジスタ::CWE値（Disable）	\n*/
/*!< Type  : U1															\n*/
/*!< LSB   : -															\n*/
/*!< Offset: -															\n*/
/*!< Unit  : -															\n*/

#define		CDD_CANIC_CWE_ENABLE		(0x01)
/*!< Description: Transceiver Event Enableレジスタ::CWE値（Enable）		\n*/
/*!< Type  : U1															\n*/
/*!< LSB   : -															\n*/
/*!< Offset: -															\n*/
/*!< Unit  : -															\n*/

#define		CDD_CANIC_WPRE_ENABLE		(0x01)
/*!< Description: WAKE Pin Enableレジスタ::WPRE値（Enable）				\n*/
/*!< Type  : U1															\n*/
/*!< LSB   : -															\n*/
/*!< Offset: -															\n*/
/*!< Unit  : -															\n*/

#define		CDD_CANIC_WPFE_DISABLE		(0x00)
/*!< Description: WAKE Pin Enableレジスタ::WPFE値（Disable）			\n*/
/*!< Type  : U1															\n*/
/*!< LSB   : -															\n*/
/*!< Offset: -															\n*/
/*!< Unit  : -															\n*/

#define		CDD_CANIC_LKXC_ALL_UNLOCK		(0x00)
/*!< Description: Lock Controlレジスタ::全LKxC値（Unlock）				\n*/
/*!< Type  : U1															\n*/
/*!< LSB   : -															\n*/
/*!< Offset: -															\n*/
/*!< Unit  : -															\n*/

#define		CDD_CANIC_CANFD_TOLERATE		(0x01)
/*!< Description: CANFD許容設定値（許容する）							\n*/
/*!< Type  : U1															\n*/
/*!< LSB   : -															\n*/
/*!< Offset: -															\n*/
/*!< Unit  : -															\n*/

#define		CDD_CANIC_CANFD_NOT_TOLERATE		(0x00)
/*!< Description: CANFD許容設定値（許容しない）							\n*/
/*!< Type  : U1															\n*/
/*!< LSB   : -															\n*/
/*!< Offset: -															\n*/
/*!< Unit  : -															\n*/

#define		CDD_CANIC_PN_DISABLE		(0x00)
/*!< Description: パーシャルネットワーク機能設定値（無効）				\n*/
/*!< Type  : U1															\n*/
/*!< LSB   : -															\n*/
/*!< Offset: -															\n*/
/*!< Unit  : -															\n*/

#define		CDD_CANIC_PN_ENABLE		(0x01)
/*!< Description: パーシャルネットワーク機能設定値（有効）				\n*/
/*!< Type  : U1															\n*/
/*!< LSB   : -															\n*/
/*!< Offset: -															\n*/
/*!< Unit  : -															\n*/

#define		CDD_CANIC_SYSE_PO				((U1)BIT4)
/*!< Description: SystemEventStatusイベント確認マスク（POイベント）		\n*/
/*!< Type  : U1															\n*/
/*!< LSB   : -															\n*/
/*!< Offset: -															\n*/
/*!< Unit  : -															\n*/

#define		CDD_CANIC_WUF_DATARATE_500		(0x05)
/*!< Description: WUF ビットレート設定値								\n*/
/*!< Type  : U1															\n*/
/*!< LSB   : -															\n*/
/*!< Offset: -															\n*/
/*!< Unit  : -															\n*/

#define		CDD_CANIC_IDE_STANDAERD		(0x00)
/*!< Description: 受信WUF CANIDフォーマット（Standard）					\n*/
/*!< Type  : U1															\n*/
/*!< LSB   : -															\n*/
/*!< Offset: -															\n*/
/*!< Unit  : -															\n*/

#define		CDD_CANIC_IDE_EXTENDED		(0x01)
/*!< Description: 受信WUF CANIDフォーマット（Extemded）					\n*/
/*!< Type  : U1															\n*/
/*!< LSB   : -															\n*/
/*!< Offset: -															\n*/
/*!< Unit  : -															\n*/

#define		CDD_CANIC_WUF_DATAMASK_OFF		(0x00)
/*!< Description: 受信WUF DLC評価（OFF）								\n*/
/*!< Type  : U1															\n*/
/*!< LSB   : -															\n*/
/*!< Offset: -															\n*/
/*!< Unit  : -															\n*/

#define		CDD_CANIC_WUF_DATAMASK_ON		(0x01)
/*!< Description: 受信WUF DLC評価（ON）									\n*/
/*!< Type  : U1															\n*/
/*!< LSB   : -															\n*/
/*!< Offset: -															\n*/
/*!< Unit  : -															\n*/

#define		CDD_CANIC_DLC8		(0x08)
/*!< Description: DLC設定値（8）										\n*/
/*!< Type  : U1															\n*/
/*!< LSB   : -															\n*/
/*!< Offset: -															\n*/
/*!< Unit  : -															\n*/

#define		u1CDD_CANIC_MC_NORMAL		((U1)0x07U)
/*!< Description: Mode Controlレジスタ::MC値（NORMAL）	\n*/
/*!< Type  : U1											\n*/
/*!< LSB   : -											\n*/
/*!< Offset: -											\n*/
/*!< Unit  : -											\n*/

#define		u1CDD_CANIC_MC_SLEEP		((U1)0x01U)
/*!< Description: Mode Controlレジスタ::MC値（SLEEP）	\n*/
/*!< Type  : U1											\n*/
/*!< LSB   : -											\n*/
/*!< Offset: -											\n*/
/*!< Unit  : -											\n*/

#define		u1CDD_CANIC_MC_STANDBY		((U1)0x04U)
/*!< Description: Mode Controlレジスタ::MC値（STANDBY）	\n*/
/*!< Type  : U1											\n*/
/*!< LSB   : -											\n*/
/*!< Offset: -											\n*/
/*!< Unit  : -											\n*/
/*==============================================================================================*/
/* functions																					*/
/*==============================================================================================*/
/*----------------------------------------------------------------------------------------------*/
/* API Functions																				*/
/*----------------------------------------------------------------------------------------------*/
/************************************************************************************************/
/* Service name		:	Get the Status of Initialization										*/
/* Reentrancy		:	Concurrency Safe														*/
/* Parameters(in)	:	IcNo - CAN IC Number													*/
/* Return value		:	Status of Initialization (OK/NG)										*/
/* Limitation		:	none																	*/
/************************************************************************************************/
U1	Cdd_Canic_GetInitStatus( U1 t_u1IcNo );

/************************************************************************************************/
/* Service name		:	Read and Clean the Status of SPI Communication							*/
/* Reentrancy		:	Concurrency Safe														*/
/* Parameters(in)	:	IcNo - CAN IC Number													*/
/* Return value		:	Status of SPI Communication (OK/NG/UNFIX)								*/
/* Limitation		:	none																	*/
/************************************************************************************************/
U1	Cdd_Canic_ReadClearSpiStatus( U1 t_u1IcNo );

/************************************************************************************************/
/* Service name		:	Read and Clean the Content of System Event Status Register				*/
/* Reentrancy		:	Concurrency Safe														*/
/* Parameters(in)	:	IcNo - CAN IC Number													*/
/* Return value		:	Content of System Event Status Register									*/
/* Limitation		:	none																	*/
/************************************************************************************************/
U1	Cdd_Canic_ReadClearSystemEventStatus( U1 t_u1IcNo );

/************************************************************************************************/
/* Service name		:	Get the Status of WakeUpFrameStatus										*/
/* Reentrancy		:	Concurrency Safe														*/
/* Parameters(in)	:	IcNo - CAN IC Number													*/
/* Return value		:	Status of Receive WakeUpFrame ( ON/OFF )								*/
/* Limitation		:	none																	*/
/************************************************************************************************/
Std_StatusType	Cdd_Canic_GetWakeUpFrameStatus( U1 t_u1IcNo );

/************************************************************************************************/
/* Service name		:	Set the Status of ICMode												*/
/* Reentrancy		:	Concurrency Safe														*/
/* Parameters(in)	:	IcNo - CAN IC Number													*/
/*						Mode - CAN IC Mode	( u1CDD_CANIC_MC_NORMAL / u1CDD_CANIC_MC_SLEEP )	*/
/* Return value		:	none																	*/
/* Limitation		:	none																	*/
/************************************************************************************************/
void	Cdd_Canic_SetControlMode( U1 t_u1IcNo , U1 t_u1Mode );

/************************************************************************************************/
/* Service name		:	Get the Status of ICMode												*/
/* Reentrancy		:	Concurrency Safe														*/
/* Parameters(in)	:	IcNo - CAN IC Number													*/
/* Return value		:	CAN IC Mode -															*/
/*						u1CDD_CANIC_MC_NORMAL													*/
/*						u1CDD_CANIC_MC_STANDBY													*/
/*						u1CDD_CANIC_MC_SLEEP													*/
/* Limitation		:	none																	*/
/************************************************************************************************/
U1	Cdd_Canic_GetControlMode( U1 t_u1IcNo );

/*----------------------------------------------------------------------------------------------*/
/* Scheduled / Event Functions																	*/
/*----------------------------------------------------------------------------------------------*/
/************************************************************************************************/
/* Function			:	Initialization															*/
/* Schedule			:	Init																	*/
/* Parameters(in)	:	none																	*/
/************************************************************************************************/
void	Cdd_Canic_Init( void );

/************************************************************************************************/
/* Function			:	Shutdown																*/
/* Schedule			:	Shutdown																*/
/* Parameters(in)	:	none																	*/
/************************************************************************************************/
void	Cdd_Canic_Shutdown( void );

/************************************************************************************************/
/* Function			:	Idle																	*/
/* Schedule			:	Idle																	*/
/* Parameters(in)	:	Core - Active Core														*/
/************************************************************************************************/
void	Cdd_Canic_Idle( U1 t_u1CoreId );

#endif	/* CDD_CANIC_H */
/*-- End Of File -------------------------------------------------------------------------------*/
