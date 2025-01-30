/* Cdd_Canic-r03-5000-0200-a-v09 */
/************************************************************************************************/
/*																								*/
/*		CAN Transceiver IC Communication Driver (TJA1145A)										*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/
/*==============================================================================================*/
/* include files																				*/
/*==============================================================================================*/
#include	"Std_Types.h"
//#include	"Bsw_Types.h"		/* 使用ライブラリのヘッダファイル */
//#include	"BswLib.h"			/* 使用ライブラリのヘッダファイル */
//#include	"aip_common.h"
//#include	"gpt_busywait.h"

#include	"Cdd_Canic.h"	/* 自ユニットのヘッダファイル */

#include	"Spi.h"			/* 使用ユニットのヘッダファイル */
//#include	"Dio.h"
//#include	"Tm.h"
//#include	"gpt_drv_frt.h"

/*==============================================================================================*/
/* defines / data types / structs / unions / macros												*/
/*==============================================================================================*/
#if 0
#define	CDD_CANIC_SPIEXT_SW_VARI_VERSION		50
#define	CDD_CANIC_SPIEXT_SW_REQ_MAJOR_VERSION	0
#define	CDD_CANIC_SPIEXT_SW_REQ_INDIV_VERSION	(-1)
#define	CDD_CANIC_SPIEXT_SW_SRC_MAJOR_VERSION	0

#if	( CDD_CANIC_SPIEXT_SW_VARI_VERSION != SPIEXT_SW_VARI_VERSION )
 #error	"SPIEXT : Mismatch in VARI Version"
#endif
#if	( CDD_CANIC_SPIEXT_SW_REQ_MAJOR_VERSION > SPIEXT_SW_REQ_MAJOR_VERSION )	/* 特定の版数以降のチェック */
 #error	"SPIEXT : Mismatch in REQ MAJOR Version"
#endif

#define	CDD_CANIC_DIOH_SW_VARI_VERSION		1
#define	CDD_CANIC_DIOH_SW_REQ_MAJOR_VERSION	1
#define	CDD_CANIC_DIOH_SW_REQ_INDIV_VERSION	(-1)
#define	CDD_CANIC_DIOH_SW_SRC_MAJOR_VERSION	0

#if	( CDD_CANIC_DIOH_SW_VARI_VERSION != DIOH_SW_VARI_VERSION )
 #error	"DIOH : Mismatch in VARI Version"
#endif
#if	( CDD_CANIC_DIOH_SW_REQ_MAJOR_VERSION > DIOH_SW_REQ_MAJOR_VERSION )	/* 特定の版数以降のチェック */
 #error	"DIOH : Mismatch in REQ MAJOR Version"
#endif

#define	CDD_CANIC_TM_SW_VARI_VERSION		1
#define	CDD_CANIC_TM_SW_REQ_MAJOR_VERSION	1
#define	CDD_CANIC_TM_SW_REQ_INDIV_VERSION	(-1)
#define	CDD_CANIC_TM_SW_SRC_MAJOR_VERSION	0

#if	( CDD_CANIC_TM_SW_VARI_VERSION != TM_SW_VARI_VERSION )
 #error	"TM : Mismatch in VARI Version"
#endif
#if	( CDD_CANIC_TM_SW_REQ_MAJOR_VERSION > TM_SW_REQ_MAJOR_VERSION )	/* 特定の版数以降のチェック */
 #error	"TM : Mismatch in REQ MAJOR Version"
#endif

#define CDD_CANIC_PFCORE_SW_VARI_VERSION			0
#define CDD_CANIC_PFCORE_SW_PKG_MAJOR_VERSION		0

#if	( CDD_CANIC_PFCORE_SW_VARI_VERSION != PFCORE_SW_VARI_VERSION )
 #error	"PFCORE : Mismatch in VARI Version"
#endif
#if	( CDD_CANIC_PFCORE_SW_PKG_MAJOR_VERSION > PFCORE_SW_PKG_MAJOR_VERSION )	/* 特定の版数以降のチェック */
 #error	"PFCORE : Mismatch in PKG MAJOR Version"
#endif
#endif


#define		u1CDD_CANIC_SPI_FRAME_RO_BITPOSITION		((U1)8U)
/*!< Description: SPI通信フレームのROビットの位置						\n*/
/*!< Type  : U1															\n*/
/*!< LSB   : 1															\n*/
/*!< Offset: 0															\n*/
/*!< Unit  : bit														\n*/

#define		u1CDD_CANIC_SPI_FRAME_ADDR_BITPOSITION		((U1)9U)
/*!< Description: SPI通信フレームのアドレスフィールドの開始ビット位置	\n*/
/*!< Type  : U1															\n*/
/*!< LSB   : 1															\n*/
/*!< Offset: 0															\n*/
/*!< Unit  : bit														\n*/

#define		u2CDD_CANIC_SPI_FRAME_HEADER_MASK		((U2)0xFF00U)
/*!< Description: SPI通信フレームのヘッダ部（アドレス+ROビット）のマスク	\n*/
/*!< Type  : U2																\n*/
/*!< LSB   : 1																\n*/
/*!< Offset: 0																\n*/
/*!< Unit  : bit															\n*/

#define		u2CDD_CANIC_SPI_FRAME_DATA_MASK		((U2)0x00FFU)
/*!< Description: SPI通信フレームのデータ部（データフィールド）のマスク	\n*/
/*!< Type  : U2															\n*/
/*!< LSB   : 1															\n*/
/*!< Offset: 0															\n*/
/*!< Unit  : bit														\n*/

//#define		u4CDD_CANIC_WAKEUP_TIMEOUT		((U4)( (PL)300 / (PL)TM_FRTC24_LSB ))	/* (50us + 100us)*2：Wake Pinに有効エッジが入ってからCanIcがStandbyモードになりINHがON(Active)になるまでの時間の2倍のマージン  */
#define		u4CDD_CANIC_WAKEUP_TIMEOUT		((U4)( (U4)300 * GPT_FRT_1US ))	/* (50us + 100us)*2：Wake Pinに有効エッジが入ってからCanIcがStandbyモードになりINHがON(Active)になるまでの時間の2倍のマージン  */
/*!< Description: Localウェイクアップまでのタイムアウト時間	\n*/
/*!< Type  : U4												\n*/
/*!< LSB   : 0.25/256										\n*/
/*!< Offset: 0												\n*/
/*!< Unit  : us												\n*/

#define		u1CDD_CANIC_RETRYCOUNT		((U1)2U)
/*!< Description: リトライ回数								\n*/
/*!< Type  : U1												\n*/
/*!< LSB   : 1												\n*/
/*!< Offset: 0												\n*/
/*!< Unit  : 回												\n*/

//#define		u4CDD_CANIC_TRCSV_ACTIVATION_TIMEOUT		((U4)( (PL)250 / (PL)TM_FRTC24_LSB ))
//#define		u4CDD_CANIC_TRCSV_ACTIVATION_TIMEOUT		((U4)( (U4)250 * GPT_FRT_1US ))
#define		u4CDD_CANIC_TRCSV_ACTIVATION_TIMEOUT		((U4)( 0x3 ))
/*!< Description: トランシーバ有効化までのタイムアウト時間	\n*/
/*!< Type  : U4												\n*/
/*!< LSB   : 0.25/256										\n*/
/*!< Offset: 0												\n*/
/*!< Unit  : us												\n*/

#define		u1CDD_CANIC_RO_READWRITE		((U1)0x00U)
/*!< Description: ROビット値（読書き）			\n*/
/*!< Type  : U1									\n*/
/*!< LSB   : -									\n*/
/*!< Offset: -									\n*/
/*!< Unit  : -									\n*/

#define		u1CDD_CANIC_RO_READONLY		((U1)0x01U)
/*!< Description: ROビット値（読出し限定）		\n*/
/*!< Type  : U1									\n*/
/*!< LSB   : -									\n*/
/*!< Offset: -									\n*/
/*!< Unit  : -									\n*/

#define		u1CDD_CANIC_CMC_ACTIVE_WO_UDV		((U1)0x02U)
/*!< Description: CAN Controlレジスタ::CMC値（ACTIVE w/o 低電圧検出機能）	\n*/
/*!< Type  : U1																\n*/
/*!< LSB   : -																\n*/
/*!< Offset: -																\n*/
/*!< Unit  : -																\n*/

#define		u1CDD_CANIC_PO_OTW_SPIF_ALL_CLEAR		((U1)BIT4 | (U1)BIT2 | (U1)BIT1)
/*!< Description: System Event Statusレジスタ::{PO,OTW,SPIF}値（Clear）	\n*/
/*!< Type  : U1															\n*/
/*!< LSB   : -															\n*/
/*!< Offset: -															\n*/
/*!< Unit  : -															\n*/

#define		u1CDD_CANIC_PNFDE_CBS_CF_CW_ALL_CLEAR		((U1)BIT5 | (U1)BIT4 | (U1)BIT1 | (U1)BIT0)
/*!< Description: Transceiver Event Statusレジスタ::{PNFDE,CBS,CF,CW}値（Clear）	\n*/
/*!< Type  : U1																		\n*/
/*!< LSB   : -																		\n*/
/*!< Offset: -																		\n*/
/*!< Unit  : -																		\n*/

#define		u1CDD_CANIC_WPR_WPF_ALL_CLEAR		((U1)BIT1 | (U1)BIT0)
/*!< Description: WAKE Pin Event Statusレジスタ::{WPR,WPF}値（Clear）	\n*/
/*!< Type  : U1															\n*/
/*!< LSB   : -															\n*/
/*!< Offset: -															\n*/
/*!< Unit  : -															\n*/

#define		u1CDD_CANIC_REG_ADDR_MODECONTROL		((U1)0x01U)
/*!< Description: Mode Controlレジスタアドレス	\n*/
/*!< Type  : U1									\n*/
/*!< LSB   : 1									\n*/
/*!< Offset: 0									\n*/
/*!< Unit  : -									\n*/

#define		u1CDD_CANIC_MASK_CTS		((U1)BIT7)
/*!< Description: Transceiver Statusレジスタ::CTSマスク	\n*/
/*!< Type  : U1											\n*/
/*!< LSB   : -											\n*/
/*!< Offset: -											\n*/
/*!< Unit  : -											\n*/

#define		u1CDD_CANIC_BIT_CTS		((U1)BIT7)
/*!< Description: Transceiver Statusレジスタ::CTSビット		)	\n*/
/*!< Type  : U1													\n*/
/*!< LSB   : -													\n*/
/*!< Offset: -													\n*/
/*!< Unit  : -													\n*/

#define		u1CDD_CANIC_MASK_CDR		((U1)0x07U)
/*!< Description: WUF Datarateレジスタ::CDRマスク		\n*/
/*!< Type  : U1											\n*/
/*!< LSB   : -											\n*/
/*!< Offset: -											\n*/
/*!< Unit  : -											\n*/

#define		u1CDD_CANIC_MASK_WUF		((U1)0xFFU)
/*!< Description: WUF ID関連レジスタマスク				\n*/
/*!< Type  : U1											\n*/
/*!< LSB   : -											\n*/
/*!< Offset: -											\n*/
/*!< Unit  : -											\n*/

#define		u1CDD_CANIC_MASK_WUF3		((U1)0x1FU)
/*!< Description: WUF ID関連レジスタマスク				\n*/
/*!< Type  : U1											\n*/
/*!< LSB   : -											\n*/
/*!< Offset: -											\n*/
/*!< Unit  : -											\n*/

#define		u1CDD_CANIC_MASK_FRAMECONTROL		((U1)0xCFU)
/*!< Description: Frame Control レジスタマスク			\n*/
/*!< Type  : U1											\n*/
/*!< LSB   : -											\n*/
/*!< Offset: -											\n*/
/*!< Unit  : -											\n*/

#define		u1CDD_CANIC_MASK_TRSCVEVT		((U1)BIT4 | (U1)BIT1 | (U1)BIT0)
/*!< Description: Transceiver Event Enableレジスタマスク				\n*/
/*!< Type  : U1															\n*/
/*!< LSB   : -															\n*/
/*!< Offset: -															\n*/
/*!< Unit  : -															\n*/

#define		u1CDD_CANIC_MASK_CANCONTROL		( (U1)BIT6 |(U1)BIT5 | (U1)BIT4 | (U1)BIT1 | (U1)BIT0)
/*!< Description: CAN Controlレジスタマスク								\n*/
/*!< Type  : U1															\n*/
/*!< LSB   : -															\n*/
/*!< Offset: -															\n*/
/*!< Unit  : -															\n*/

#define		u1CDD_CANIC_REG_ADDR_SYSEVTENABLE		((U1)0x04U)
/*!< Description: System Event Enableレジスタアドレス	\n*/
/*!< Type  : U1											\n*/
/*!< LSB   : 1											\n*/
/*!< Offset: 0											\n*/
/*!< Unit  : -											\n*/

#define		u1CDD_CANIC_REG_ADDR_LOCKCONTROL		((U1)0x0AU)
/*!< Description: Lock Controlレジスタアドレス	\n*/
/*!< Type  : U1									\n*/
/*!< LSB   : 1									\n*/
/*!< Offset: 0									\n*/
/*!< Unit  : -									\n*/

#define		u1CDD_CANIC_REG_ADDR_CANCONTROL		((U1)0x20U)
/*!< Description: CAN Controlレジスタアドレス	\n*/
/*!< Type  : U1									\n*/
/*!< LSB   : 1									\n*/
/*!< Offset: 0									\n*/
/*!< Unit  : -									\n*/

#define		u1CDD_CANIC_REG_ADDR_TRSCVSTATUS		((U1)0x22U)
/*!< Description: Transceiver Statusレジスタアドレス	\n*/
/*!< Type  : U1											\n*/
/*!< LSB   : 1											\n*/
/*!< Offset: 0											\n*/
/*!< Unit  : -											\n*/

#define		u1CDD_CANIC_REG_ADDR_TRSCVEVTENABLE		((U1)0x23U)
/*!< Description: Transceiver Event Enableレジスタアドレス	\n*/
/*!< Type  : U1												\n*/
/*!< LSB   : 1												\n*/
/*!< Offset: 0												\n*/
/*!< Unit  : -												\n*/

#define		u1CDD_CANIC_REG_ADDR_WUFDATARATE		((U1)0x26U)
/*!< Description: WUF Datarateレジスタアドレス				\n*/
/*!< Type  : U1												\n*/
/*!< LSB   : 1												\n*/
/*!< Offset: 0												\n*/
/*!< Unit  : -												\n*/

#define		u1CDD_CANIC_REG_ADDR_WUFID0		((U1)0x27U)
/*!< Description: WUF IDレジスタアドレス0					\n*/
/*!< Type  : U1												\n*/
/*!< LSB   : 1												\n*/
/*!< Offset: 0												\n*/
/*!< Unit  : -												\n*/

#define		u1CDD_CANIC_REG_ADDR_WUFID1		((U1)0x28U)
/*!< Description: WUF IDレジスタアドレス1					\n*/
/*!< Type  : U1												\n*/
/*!< LSB   : 1												\n*/
/*!< Offset: 0												\n*/
/*!< Unit  : -												\n*/

#define		u1CDD_CANIC_REG_ADDR_WUFID2		((U1)0x29U)
/*!< Description: WUF IDレジスタアドレス2					\n*/
/*!< Type  : U1												\n*/
/*!< LSB   : 1												\n*/
/*!< Offset: 0												\n*/
/*!< Unit  : -												\n*/

#define		u1CDD_CANIC_REG_ADDR_WUFID3		((U1)0x2AU)
/*!< Description: WUF IDレジスタアドレス3					\n*/
/*!< Type  : U1												\n*/
/*!< LSB   : 1												\n*/
/*!< Offset: 0												\n*/
/*!< Unit  : -												\n*/

#define		u1CDD_CANIC_REG_ADDR_WUFIDMASK0		((U1)0x2BU)
/*!< Description: WUF ID MASKレジスタアドレス0				\n*/
/*!< Type  : U1												\n*/
/*!< LSB   : 1												\n*/
/*!< Offset: 0												\n*/
/*!< Unit  : -												\n*/

#define		u1CDD_CANIC_REG_ADDR_WUFIDMASK1		((U1)0x2CU)
/*!< Description: WUF ID MASKレジスタアドレス1				\n*/
/*!< Type  : U1												\n*/
/*!< LSB   : 1												\n*/
/*!< Offset: 0												\n*/
/*!< Unit  : -												\n*/

#define		u1CDD_CANIC_REG_ADDR_WUFIDMASK2		((U1)0x2DU)
/*!< Description: WUF ID MASKレジスタアドレス2				\n*/
/*!< Type  : U1												\n*/
/*!< LSB   : 1												\n*/
/*!< Offset: 0												\n*/
/*!< Unit  : -												\n*/

#define		u1CDD_CANIC_REG_ADDR_WUFIDMASK3		((U1)0x2EU)
/*!< Description: WUF ID MASKレジスタアドレス3				\n*/
/*!< Type  : U1												\n*/
/*!< LSB   : 1												\n*/
/*!< Offset: 0												\n*/
/*!< Unit  : -												\n*/

#define		u1CDD_CANIC_REG_ADDR_FRAMECONTROL		((U1)0x2FU)
/*!< Description: Frame Control レジスタアドレス	\n*/
/*!< Type  : U1												\n*/
/*!< LSB   : 1												\n*/
/*!< Offset: 0												\n*/
/*!< Unit  : -												\n*/

#define		u1CDD_CANIC_REG_ADDR_WAKEPINENABLE		((U1)0x4CU)
/*!< Description: WAKE Pin Enableレジスタアドレス		\n*/
/*!< Type  : U1											\n*/
/*!< LSB   : 1											\n*/
/*!< Offset: 0											\n*/
/*!< Unit  : -											\n*/

#define		u1CDD_CANIC_REG_ADDR_SYSEVTSTATUS		((U1)0x61U)
/*!< Description: System Event Statusレジスタアドレス		\n*/
/*!< Type  : U1												\n*/
/*!< LSB   : 1												\n*/
/*!< Offset: 0												\n*/
/*!< Unit  : -												\n*/

#define		u1CDD_CANIC_REG_ADDR_TRSCVEVTSTATUS		((U1)0x63U)
/*!< Description: Transceiver Event Statusレジスタアドレス		\n*/
/*!< Type  : U1													\n*/
/*!< LSB   : 1													\n*/
/*!< Offset: 0													\n*/
/*!< Unit  : -													\n*/

#define		u1CDD_CANIC_REG_ADDR_WAKEPINEVTSTATUS		((U1)0x64U)
/*!< Description: WAKE Pin Event Statusレジスタアドレス		\n*/
/*!< Type  : U1												\n*/
/*!< LSB   : 1												\n*/
/*!< Offset: 0												\n*/
/*!< Unit  : -												\n*/

#define		u1CDD_CANIC_REG_ADDR_WUFDATAMASK0		((U1)0x68U)
/*!< Description: Wuf Data Maskレジスタアドレス0			\n*/
/*!< Type  : U1												\n*/
/*!< LSB   : 1												\n*/
/*!< Offset: 0												\n*/
/*!< Unit  : -												\n*/

#define		u1CDD_CANIC_REG_ADDR_WUFDATAMASK1		((U1)0x69U)
/*!< Description: Wuf Data Maskレジスタアドレス1			\n*/
/*!< Type  : U1												\n*/
/*!< LSB   : 1												\n*/
/*!< Offset: 0												\n*/
/*!< Unit  : -												\n*/

#define		u1CDD_CANIC_REG_ADDR_WUFDATAMASK2		((U1)0x6AU)
/*!< Description: Wuf Data Maskレジスタアドレス2			\n*/
/*!< Type  : U1												\n*/
/*!< LSB   : 1												\n*/
/*!< Offset: 0												\n*/
/*!< Unit  : -												\n*/

#define		u1CDD_CANIC_REG_ADDR_WUFDATAMASK3		((U1)0x6BU)
/*!< Description: Wuf Data Maskレジスタアドレス3			\n*/
/*!< Type  : U1												\n*/
/*!< LSB   : 1												\n*/
/*!< Offset: 0												\n*/
/*!< Unit  : -												\n*/

#define		u1CDD_CANIC_REG_ADDR_WUFDATAMASK4		((U1)0x6CU)
/*!< Description: Wuf Data Maskレジスタアドレス4			\n*/
/*!< Type  : U1												\n*/
/*!< LSB   : 1												\n*/
/*!< Offset: 0												\n*/
/*!< Unit  : -												\n*/

#define		u1CDD_CANIC_REG_ADDR_WUFDATAMASK5		((U1)0x6DU)
/*!< Description: Wuf Data Maskレジスタアドレス5			\n*/
/*!< Type  : U1												\n*/
/*!< LSB   : 1												\n*/
/*!< Offset: 0												\n*/
/*!< Unit  : -												\n*/

#define		u1CDD_CANIC_REG_ADDR_WUFDATAMASK6		((U1)0x6EU)
/*!< Description: Wuf Data Maskレジスタアドレス6			\n*/
/*!< Type  : U1												\n*/
/*!< LSB   : 1												\n*/
/*!< Offset: 0												\n*/
/*!< Unit  : -												\n*/

#define		u1CDD_CANIC_REG_ADDR_WUFDATAMASK7		((U1)0x6FU)
/*!< Description: Wuf Data Maskレジスタアドレス7			\n*/
/*!< Type  : U1												\n*/
/*!< LSB   : 1												\n*/
/*!< Offset: 0												\n*/
/*!< Unit  : -												\n*/

#define		u1CDD_CANIC_ZERODATA					((U1)0x00U)
/*!< Description: 読み出し用ダミー値						\n*/
/*!< Type  : U1												\n*/
/*!< LSB   : 1												\n*/
/*!< Offset: 0												\n*/
/*!< Unit  : -												\n*/

#define 	u1CDD_CANIC_TES_CW 						((U1)BIT0)
/*!< Description: WUF履歴(CW)マスク用コマンド						\n*/
/*!< Type  : U1												\n*/
/*!< LSB   : 1												\n*/
/*!< Offset: 0												\n*/
/*!< Unit  : -												\n*/

#define		u1CDD_CANIC_MC_MASK				((U1)(BIT2 + BIT1 + BIT0))
/*!< Description: Mode Controlレジスタ::MCマスク値		\n*/
/*!< Type  : U1											\n*/
/*!< LSB   : -											\n*/
/*!< Offset: -											\n*/
/*!< Unit  : -											\n*/

#define		u1CDD_CANIC_MC_POS				((U1)(BIT0))
/*!< Description: Mode Controlレジスタ::MCビット		\n*/
/*!< Type  : U1											\n*/
/*!< LSB   : -											\n*/
/*!< Offset: -											\n*/
/*!< Unit  : -											\n*/
#define		u2CDD_CANIC_WAIT_WAKEPINENABLE	((U2)100U * GPT_BUSY_WAIT_1_US)
/*!< Description: WakePinのエッジ検出が有効になるまでの時間(1us)+		\n*/
/*!< エッジ検出するための定常電圧の確定にかかる時間(50us)+マージン時間	\n*/
/*!< Type  : U1															\n*/
/*!< LSB   : -															\n*/
/*!< Offset: -															\n*/
/*!< Unit  : ns															\n*/
/*==============================================================================================*/
/* prototypes																					*/
/*==============================================================================================*/
/*----------------------------------------------------------------------------------------------*/
/*! Description		:	Transmit Data															*/
/*! Reentrancy		:	Concurrency Safe														*/
/*----------------------------------------------------------------------------------------------*/
/*! \param[in] t_u1IcNo \n
 *  \parblock
 *    Description : IC番号 \n
 *    Type        : U1          \n
 *    LSB         : 1           \n
 *    Offset      : 0           \n
 *    Unit        : -           \n
 *    Range       : 0
 * \endparblock																					*/
/*----------------------------------------------------------------------------------------------*/
/*! \param[in] t_u1Addr \n
 *  \parblock
 *    Description : レジスタアドレス \n
 *    Type        : U1          \n
 *    LSB         : 1           \n
 *    Offset      : 0           \n
 *    Unit        : -           \n
 *    Range       : 0x01-0x0A,0x20-0x2F,0x4B-0x4C,0x60-0x64,0x68-0x6F,0x7E
 * \endparblock																					*/
/*----------------------------------------------------------------------------------------------*/
/*! \param[in] t_u1RO \n
 *  \parblock
 *    Description : Read-Onlyフラグ \n
 *    Type        : U1          \n
 *    LSB         : -           \n
 *    Offset      : -           \n
 *    Unit        : -           \n
 *    Range       : u1CDD_CANIC_RO_READWRITE/u1CDD_CANIC_RO_READONLY
 * \endparblock																					*/
/*----------------------------------------------------------------------------------------------*/
/*! \param[in] t_u1Data \n
 *  \parblock
 *    Description : 書込みデータ \n
 *    Type        : U1           \n
 *    LSB         : 1            \n
 *    Offset      : 0            \n
 *    Unit        : -            \n
 *    Range       : -
 * \endparblock																					*/
/*----------------------------------------------------------------------------------------------*/
/*! \retval    ReadData	\n
 *    Description : 読出しデータ \n
 *    Type        : U1           \n
 *    LSB         : 1            \n
 *    Offset      : 0            \n
 *    Unit        : -            \n
 *    Range       : -																			*/
/*----------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------*/
static	U1	Cdd_Canic_TransmitData( U1 t_u1IcNo, U1 t_u1Addr, U1 t_u1RO, U1 t_u1Data );

/*==============================================================================================*/
/* constants																					*/
/*==============================================================================================*/
//#define		SEL_ROMSEC		(CDD_CANIC_CFG_SEC_ROM0)
//#include	"Cdd_Seccfg_Roms.h"
#pragma ghs section rosdata=".CANIC_RODATA_CONST"

extern	const	Cdd_Canic_UserConfigType	cstCdd_Canic_UcfgData;
//#include	"Cdd_Seccfg_Rome.h"
//#undef		SEL_ROMSEC
#pragma ghs section rosdata=default

/*==============================================================================================*/
/* variables																					*/
/*==============================================================================================*/
//#define		SEL_RAMSEC		(CDD_CANIC_CFG_SEC_RAM0)
//#include	"Cdd_Seccfg_Rams.h"
#pragma ghs section sbss=".CANIC_BSS_VAR_NO_INIT"

/*! Description: Init Status				\n*/
/*! Type   : U1								\n*/
/*! LSB    : -								\n*/
/*! Offset : -								\n*/
/*! Unit   : -								\n*/
/*! Range  : OK/NG							*/
static	U1	s_u1Cdd_Canic_InitStatus[CDD_CANIC_CFG_IC_NUM];

/*! Description: SPI Status					\n*/
/*! Type   : U1								\n*/
/*! LSB    : -								\n*/
/*! Offset : -								\n*/
/*! Unit   : -								\n*/
/*! Range  : OK/NG/UNFIX					*/
static	U1	s_u1Cdd_Canic_SpiStatus[CDD_CANIC_CFG_IC_NUM];

//#include	"Cdd_Seccfg_Rame.h"
//#undef		SEL_RAMSEC
#pragma ghs section sbss=default

/*==============================================================================================*/
/* functions																					*/
/*==============================================================================================*/
//#define		SEL_PRGSEC		(CDD_CANIC_CFG_SEC_PRG0)
//#include	"Cdd_Seccfg_Prgs.h"
#pragma ghs section text=".CANIC_TEXT_CODE"
/*----------------------------------------------------------------------------------------------*/
/* API Functions																				*/
/*----------------------------------------------------------------------------------------------*/
U1	Cdd_Canic_GetInitStatus( U1 t_u1IcNo )
{
	return( s_u1Cdd_Canic_InitStatus[t_u1IcNo] );
}

U1	Cdd_Canic_ReadClearSpiStatus( U1 t_u1IcNo )
{
	U1	t_u1SpiStatus;

	CDD_CANIC_CFG_IC0_GETSPINLOCK(); /* SPI通信状態取得・更新のため排他 */

	t_u1SpiStatus = s_u1Cdd_Canic_SpiStatus[t_u1IcNo];
	s_u1Cdd_Canic_SpiStatus[t_u1IcNo] = (U1)UNFIX;

	CDD_CANIC_CFG_IC0_RELEASESPINLOCK(); /* 排他解除 */

	return( t_u1SpiStatus );
}

Std_StatusType	Cdd_Canic_GetWakeUpFrameStatus( U1 t_u1IcNo )
{
	Std_StatusType	t_udReadData_CW;
	
	/*---------------------------------*/
	/* WUF履歴状態の取得と起動信号WUFの更新 */
	/*---------------------------------*/
	U1	t_u1ReadData = Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_TRSCVEVTSTATUS,
		                                       u1CDD_CANIC_RO_READONLY, u1CDD_CANIC_ZERODATA );
	
	if(	( t_u1ReadData & u1CDD_CANIC_TES_CW ) != (U1)0 )
	{
		t_udReadData_CW = (Std_StatusType)ON;
	}
	else
	{
		t_udReadData_CW = (Std_StatusType)OFF;
	}

	return( t_udReadData_CW );
}

U1	Cdd_Canic_ReadClearSystemEventStatus( U1 t_u1IcNo )
{
	/*----------------------------------*/
	/* System Event状態の取得とクリア   */
	/*----------------------------------*/
	U1	t_u1ReadData = Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_SYSEVTSTATUS,
	                                           u1CDD_CANIC_RO_READWRITE, u1CDD_CANIC_PO_OTW_SPIF_ALL_CLEAR );

	return( t_u1ReadData );	/* コール元で使用するデータをマスクして使うため生値を返す。(bit4:PO, bit2:OTW, bit1:SPIF) */
}

void	Cdd_Canic_SetControlMode( U1 t_u1IcNo , U1 t_u1Mode )
{
	/*-------------------------------------------------------------------------------------------*/
	/* ソースコード上、連続で通信処理を実行した場合に実測値で2.2usのCS非アクティブ時間がある	 */
	/* ICにモードの設定を行うのにかかる時間はtWH(S)で規定されており   							 */
	/* Normal/Standbyモードで250ns、Sleepモードで1usとされている	  							 */
	/* そのため、本APIから戻った直後に通信処理を実行したとしても、モードの反映は完了しているため */
	/* APIから戻るまでにレジスタへ反映ができていることを保証する		 						 */
	/*-------------------------------------------------------------------------------------------*/

	if( t_u1Mode == u1CDD_CANIC_MC_NORMAL )
	{
	/*----------------------------------*/
	/* IC動作モード設定（NORMAL）       */
	/*----------------------------------*/
		(void)Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_MODECONTROL,
		                              u1CDD_CANIC_RO_READWRITE, u1CDD_CANIC_MC_NORMAL );
	}
	else /* 引数SLEEPの場合 */
	{	
		/*----------------------------*/
		/* System Event状態の全クリア */
		/*----------------------------*/
		(void)Cdd_Canic_ReadClearSystemEventStatus(t_u1IcNo); /* システムイベント状態取得のイベントクリア機能を借用 */

		/*---------------------------------*/
		/* Transceiver Event状態の全クリア */
		/*---------------------------------*/
		(void)Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_TRSCVEVTSTATUS,
		                              u1CDD_CANIC_RO_READWRITE, u1CDD_CANIC_PNFDE_CBS_CF_CW_ALL_CLEAR );
		                              
		/*------------------------------*/
		/* Wake Pin Event状態の全クリア */
		/*------------------------------*/
		(void)Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WAKEPINEVTSTATUS,
		                              u1CDD_CANIC_RO_READWRITE, u1CDD_CANIC_WPR_WPF_ALL_CLEAR );	
		                              
		/*---------------------------*/
		/* IC動作モード設定（SLEEP） */
		/*---------------------------*/
		(void)Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_MODECONTROL,
		                              u1CDD_CANIC_RO_READWRITE, u1CDD_CANIC_MC_SLEEP );
	}
}

U1	Cdd_Canic_GetControlMode( U1 t_u1IcNo )
{	
	/*---------------------------------*/
	/* IC動作モード取得                */
	/*---------------------------------*/
	U1	t_u1ReadData = Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_MODECONTROL,
		                                       u1CDD_CANIC_RO_READONLY, u1CDD_CANIC_ZERODATA );

	return( t_u1ReadData & u1CDD_CANIC_MC_MASK ); /* MCはbit0から割り付けられているためLSBへのシフトは省略 */
}

/*----------------------------------------------------------------------------------------------*/
/* Scheduled / Event Functions																	*/
/*----------------------------------------------------------------------------------------------*/
void	Cdd_Canic_Init( void )
{
	const	U1	t_cu1IcNum = (U1)CDD_CANIC_CFG_IC_NUM;
	U1			t_u1IcNo;
	U1			t_u1Count;

	/*--------------*/
	/* IC毎の初期化 */
	/*--------------*/
	for ( t_u1IcNo = (U1)0U; t_u1IcNo < t_cu1IcNum; t_u1IcNo++ )
	{
//		const	U4		t_cu4DiohChIdWake = cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u4DiohChIdWriteWake;
//		const	U4		t_cu4DiohChIdInh = cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u4DiohChIdReadInh;
		U4				t_u4StartTime;
//		Std_StatusType	t_udInhcheck;
		U1	t_u1WriteData;

		s_u1Cdd_Canic_InitStatus[t_u1IcNo] = (U1)NG;   /* 初期化状態をNGで初期化 */
		s_u1Cdd_Canic_SpiStatus[t_u1IcNo] = (U1)UNFIX; /* SPI通信状態をUNFIXで初期化 */

		/*------------------------*/
		/* Lock Control無効化設定 */
		/*------------------------*/
		t_u1WriteData = cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegLockControl;
		(void)Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_LOCKCONTROL,
			                              u1CDD_CANIC_RO_READWRITE, t_u1WriteData );

		/*----------------------------------*/
		/* WAKE PIN有効化設定（RisingEdge） */
		/*----------------------------------*/
		t_u1WriteData = cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegWakePinEnable;
		(void)Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WAKEPINENABLE,
		                              u1CDD_CANIC_RO_READWRITE, t_u1WriteData );

//		Bswlib_Wait( (U4)u1CDD_CANIC_WAIT_WAKEPINENABLE );	/* Localウェイクアップが有効化されるまで待つ */
//		vd_g_Gpt_BusyWait( (U2)u2CDD_CANIC_WAIT_WAKEPINENABLE );  	/* Localウェイクアップが有効化されるまで待つ */

		/*-------------------------*/
		/* ICのLocalウェイクアップ */
		/*-------------------------*/
//		Dioh_WriteChannel( t_cu4DiohChIdWake, (Std_StatusType)ON ); /* WAkEピンに立ち上がりエッジ出力 */
//		Dio_WriteChannel( (Dio_ChannelType)t_cu4DiohChIdWake, (Dio_LevelType)STD_HIGH ); /* WAkEピンに立ち上がりエッジ出力 */

#if 0  /* C-DC INH信号がないため */ 
		t_u4StartTime = Tm_GetFreeRunTimeCount24();

		do
		{
			t_udInhcheck = Dioh_ReadChannel( t_cu4DiohChIdInh );				
			U4	t_u4ElapsedTime = Tm_GetFreeRunTimeCount24() - t_u4StartTime; /* 経過時間取得：U4変数のラップアラウンドを利用 */

			if ( t_u4ElapsedTime > u4CDD_CANIC_WAKEUP_TIMEOUT )
			{
				break; /* タイムアウト */
			}				
		}while ( t_udInhcheck != (Std_StatusType)ON ); /* INH端子が非アクティブ？ */
#endif		
		/*------------------------------------*/
		/* ICの初期値設定					  */
		/*------------------------------------*/
		U1	t_u1ReadData;
		Std_StatusType	t_udIsActivationTimeouted;

		/*------------------------*/
		/* WUF Datarate 設定      */
		/*------------------------*/
		t_u1WriteData = cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegWufDataRate;
		(void)Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WUFDATARATE,
			                              u1CDD_CANIC_RO_READWRITE, t_u1WriteData );

		/*------------------------*/	                              
		/* WUF ID 設定            */
		/*------------------------*/
		t_u1WriteData = cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegWufId0;
		(void)Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WUFID0,
			                              u1CDD_CANIC_RO_READWRITE, t_u1WriteData );
			                           
		t_u1WriteData = cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegWufId1;
		(void)Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WUFID1,
			                              u1CDD_CANIC_RO_READWRITE, t_u1WriteData );
			
		t_u1WriteData = cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegWufId2;
		(void)Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WUFID2,
			                              u1CDD_CANIC_RO_READWRITE, t_u1WriteData );
			                              
		t_u1WriteData = cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegWufId3;
		(void)Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WUFID3,
			                              u1CDD_CANIC_RO_READWRITE, t_u1WriteData );
			                              	                              
		/*------------------------*/	                              
		/* WUF ID MASK 設定        */
		/*------------------------*/
		t_u1WriteData = cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegWufIdMask0;
		(void)Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WUFIDMASK0,
			                              u1CDD_CANIC_RO_READWRITE, t_u1WriteData );

		t_u1WriteData = cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegWufIdMask1;
		(void)Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WUFIDMASK1,
			                              u1CDD_CANIC_RO_READWRITE, t_u1WriteData );

		t_u1WriteData = cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegWufIdMask2;
		(void)Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WUFIDMASK2,
			                              u1CDD_CANIC_RO_READWRITE, t_u1WriteData );

		t_u1WriteData = cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegWufIdMask3;
		(void)Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WUFIDMASK3,
			                              u1CDD_CANIC_RO_READWRITE, t_u1WriteData );

		/*------------------------*/	                              
		/* Frame Control 有効化設定    */
		/*------------------------*/
		t_u1WriteData = cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegFrameControl;
		(void)Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_FRAMECONTROL,
			                              u1CDD_CANIC_RO_READWRITE, t_u1WriteData );

		/*------------------------*/	                              
		/* WUF DATA MASK 設定        */
		/*------------------------*/
		t_u1WriteData = cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegWufDataMask0;
		(void)Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WUFDATAMASK0,
		                              u1CDD_CANIC_RO_READWRITE, t_u1WriteData );

		t_u1WriteData = cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegWufDataMask1;
		(void)Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WUFDATAMASK1,
		                              u1CDD_CANIC_RO_READWRITE, t_u1WriteData );

		t_u1WriteData = cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegWufDataMask2;
		(void)Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WUFDATAMASK2,
		                              u1CDD_CANIC_RO_READWRITE, t_u1WriteData );

		t_u1WriteData = cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegWufDataMask3;
		(void)Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WUFDATAMASK3,
		                              u1CDD_CANIC_RO_READWRITE, t_u1WriteData );

		t_u1WriteData = cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegWufDataMask4;
		(void)Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WUFDATAMASK4,
		                              u1CDD_CANIC_RO_READWRITE, t_u1WriteData );

		t_u1WriteData = cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegWufDataMask5;
		(void)Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WUFDATAMASK5,
		                              u1CDD_CANIC_RO_READWRITE, t_u1WriteData );

		t_u1WriteData = cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegWufDataMask6;
		(void)Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WUFDATAMASK6,
		                              u1CDD_CANIC_RO_READWRITE, t_u1WriteData );

		t_u1WriteData = cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegWufDataMask7;
		(void)Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WUFDATAMASK7,
		                              u1CDD_CANIC_RO_READWRITE, t_u1WriteData );
		
		/*--------------------------*/
		/* System Event検出要否設定 */
		/*--------------------------*/
		t_u1WriteData = cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegSystemEventEnable;
		(void)Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_SYSEVTENABLE,
		                              u1CDD_CANIC_RO_READWRITE, t_u1WriteData );

		/*-------------------------------*/
		/* Transceiver Event検出要否設定 */
		/*-------------------------------*/
		t_u1WriteData = cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegTrscvEventEnable;
		(void)Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_TRSCVEVTENABLE,
		                              u1CDD_CANIC_RO_READWRITE, t_u1WriteData );
		                              
		/*--------------------------------------------------------------------------*/
		/* IC動作モード設定（NORMAL）及びCAN トランシーバ設定（トランシーバ有効化） */
		/* をリトライ回数(u1CDD_CANIC_RETRYCOUNT)実施								*/
		/*--------------------------------------------------------------------------*/
		
		t_udIsActivationTimeouted = (Std_StatusType)ON;	/* 初期値設定 */
		
		for ( t_u1Count = (U1)0U; t_u1Count < u1CDD_CANIC_RETRYCOUNT; t_u1Count++ )
		{
			/*----------------------------*/
			/* IC動作モード設定（NORMAL） */
			/*----------------------------*/
			(void)Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_MODECONTROL,
	    	                          u1CDD_CANIC_RO_READWRITE, u1CDD_CANIC_MC_NORMAL );

			/*--------------------------------------------*/
			/* CAN トランシーバ設定（トランシーバ有効化） */
			/*--------------------------------------------*/
			t_u1WriteData = cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegTmpltCanControl;
			t_u1WriteData |= u1CDD_CANIC_CMC_ACTIVE_WO_UDV;
			(void)Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_CANCONTROL,
		                              u1CDD_CANIC_RO_READWRITE, t_u1WriteData );
		                              
//			t_u4StartTime = Tm_GetFreeRunTimeCount24();
//			t_u4StartTime = u4_g_Gpt_FrtGetUsElapsed( vdp_PTR_NA );
			t_u4StartTime = (U4)0;
			/*----------------------------*/
			/* CAN トランシーバ有効化待ち */
			/*----------------------------*/
			do 
			{
				t_u1ReadData = Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_TRSCVSTATUS,
				                                       u1CDD_CANIC_RO_READONLY, u1CDD_CANIC_ZERODATA ); /* 先ずは1回読む */
				t_u4StartTime++;
//				U4	t_u4ElapsedTime = Tm_GetFreeRunTimeCount24() - t_u4StartTime; /* 経過時間取得：U4変数のラップアラウンドを利用 */
//				U4	t_u4ElapsedTime = u4_g_Gpt_FrtGetUsElapsed( vdp_PTR_NA ) - t_u4StartTime; /* 経過時間取得：U4変数のラップアラウンドを利用 */

//				if ( t_u4ElapsedTime > u4CDD_CANIC_TRCSV_ACTIVATION_TIMEOUT )
				if ( t_u4StartTime > u4CDD_CANIC_TRCSV_ACTIVATION_TIMEOUT )
				{
					break; /* タイムアウト */
				}
			}while( ( t_u1ReadData & u1CDD_CANIC_MASK_CTS ) != u1CDD_CANIC_BIT_CTS );  /* CTSビットが1(ACTIVATED)ではない？ */

			if ( ( t_u1ReadData & u1CDD_CANIC_MASK_CTS ) == u1CDD_CANIC_BIT_CTS )
			{
				t_udIsActivationTimeouted = (Std_StatusType)OFF;  /* CTSビットが1(ACTIVATED)なのでOFFに設定 */
				break; /* 正常終了したのでリトライはしない */
			}
		}
		/*----------------*/
		/* 初期化結果判定 */
		/*----------------*/
		if ( t_udIsActivationTimeouted == (Std_StatusType)OFF )
		{
			s_u1Cdd_Canic_InitStatus[t_u1IcNo] = (U1)OK;   /* 全初期化シーケンス完了のためをOKに設定 */
		}
	}
}

void	Cdd_Canic_Shutdown( void )
{
	const	U1	t_cu1IcNum = (U1)CDD_CANIC_CFG_IC_NUM;
	U1			t_u1IcNo;
	U1			t_u1ReadData;
	Std_StatusType	t_udReadData_CW;
                                      
	/*----------------*/
	/* IC毎の終了設定 */
	/*----------------*/
	for ( t_u1IcNo = (U1)0U; t_u1IcNo < t_cu1IcNum; t_u1IcNo++ )
	{
		/****************************************************************************/
		/* ICモードがSleep以外の状態だった場合の対策								*/
		/* 通常はShutdownシーケンスに入る前にICモードSleepに遷移するが				*/
		/* 万が一Sleepに遷移できていなかった場合に設定する。						*/
		/* 起動要因有の場合、定期タスクが動くため、ECU状態がRUN中のBus Sleep Modeの	*/
		/* 遷移でCanICをSleepモードに遷移させる。Shutdownシーケンスのこの処理で		*/
		/* 誤って新規のWakeUpフレーム履歴を消さないようにする。						*/
		/* 判定式																	*/
		/*	( MC != Sleep ) && ( WakeUp履歴 == なし )								*/
		/* 																			*/
		/* 優先順位（Sleep状態では通信速度が遅くなるため)							*/
		/* 1. MCがSleep状態でない：通常シャットダウンのケースでこのパターンが大半	*/
		/* 2. WakeUpフレーム履歴が無い												*/
		/****************************************************************************/
		/* 1. MCがSleep以外の状態かチェック */
		t_u1ReadData = Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_MODECONTROL,
		                                   u1CDD_CANIC_RO_READONLY, u1CDD_CANIC_ZERODATA );	 
		if ( ( t_u1ReadData & u1CDD_CANIC_MC_MASK ) != ( u1CDD_CANIC_MC_SLEEP * u1CDD_CANIC_MC_POS ) )
		{
			/* 2. 新規Wakeupフレーム履歴なしかチェック */
			t_udReadData_CW = Cdd_Canic_GetWakeUpFrameStatus( t_u1IcNo );
			if( t_udReadData_CW == (Std_StatusType)OFF  )
			{
				/*----------------------------*/
				/* System Event状態の全クリア */
				/*----------------------------*/
				(void)Cdd_Canic_ReadClearSystemEventStatus(t_u1IcNo); /* システムイベント状態取得のイベントクリア機能を借用 */

				/*---------------------------------*/
				/* Transceiver Event状態の全クリア */
				/*---------------------------------*/
				(void)Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_TRSCVEVTSTATUS,
				                              u1CDD_CANIC_RO_READWRITE, u1CDD_CANIC_PNFDE_CBS_CF_CW_ALL_CLEAR );

				/*------------------------------*/
				/* Wake Pin Event状態の全クリア */
				/*------------------------------*/
				(void)Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WAKEPINEVTSTATUS,
				                              u1CDD_CANIC_RO_READWRITE, u1CDD_CANIC_WPR_WPF_ALL_CLEAR );

				/*---------------------------*/
				/* IC動作モード設定（SLEEP） */
				/*---------------------------*/
				(void)Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_MODECONTROL,
				                              u1CDD_CANIC_RO_READWRITE, u1CDD_CANIC_MC_SLEEP );
			}
		}
	}
}

void	Cdd_Canic_Idle( U1 t_u1CoreId )
{
	const	U1	t_cu1IcNum = (U1)CDD_CANIC_CFG_IC_NUM;
	U1			t_u1IcNo;

	/*----------------------------*/
	/* IC毎のレジスタリフレッシュ */
	/*----------------------------*/
	for ( t_u1IcNo = (U1)0U; t_u1IcNo < t_cu1IcNum; t_u1IcNo++ )
	{
		if ( cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1CoreId == t_u1CoreId ) /* 動作コアとIC割付コアが一致？ */
		{
			U1	t_u1WriteData;
			U1	t_u1ReadData;

			/*------------------------*/
			/* Lock Control無効化設定 */
			/*------------------------*/
			t_u1WriteData = cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegLockControl;
			(void)Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_LOCKCONTROL,
			                              u1CDD_CANIC_RO_READWRITE, t_u1WriteData );

			/*------------------------*/
			/* WUF Datarate 設定      */
			/*------------------------*/
			t_u1ReadData = Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WUFDATARATE,
			                                       u1CDD_CANIC_RO_READONLY, u1CDD_CANIC_ZERODATA );	
			if ( ( t_u1ReadData & u1CDD_CANIC_MASK_CDR ) != cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegWufDataRate )
			{                                     		
				t_u1WriteData = cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegWufDataRate;
				(void)Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WUFDATARATE,
			                                  u1CDD_CANIC_RO_READWRITE, t_u1WriteData );
			}
			/*------------------------*/	                              
			/* WUF ID 設定            */
			/*------------------------*/
			t_u1ReadData = Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WUFID0,
			                                       u1CDD_CANIC_RO_READONLY, u1CDD_CANIC_ZERODATA );	
			if ( ( t_u1ReadData & u1CDD_CANIC_MASK_WUF ) != cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegWufId0 )
			{                
				t_u1WriteData = cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegWufId0;
				(void)Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WUFID0,
			                              u1CDD_CANIC_RO_READWRITE, t_u1WriteData );
			}

			t_u1ReadData = Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WUFID1,
			                                       u1CDD_CANIC_RO_READONLY, u1CDD_CANIC_ZERODATA );	
			if ( ( t_u1ReadData & u1CDD_CANIC_MASK_WUF ) != cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegWufId1 )
			{ 			                           
				t_u1WriteData = cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegWufId1;
				(void)Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WUFID1,
			                              u1CDD_CANIC_RO_READWRITE, t_u1WriteData );
			}
			
			t_u1ReadData = Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WUFID2,
			                                       u1CDD_CANIC_RO_READONLY, u1CDD_CANIC_ZERODATA );	
			if ( ( t_u1ReadData & u1CDD_CANIC_MASK_WUF ) != cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegWufId2 )
			{ 
				t_u1WriteData = cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegWufId2;
				(void)Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WUFID2,
			                              u1CDD_CANIC_RO_READWRITE, t_u1WriteData );
			}
			
			t_u1ReadData = Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WUFID3,
			                                       u1CDD_CANIC_RO_READONLY, u1CDD_CANIC_ZERODATA );	
			if ( ( t_u1ReadData & u1CDD_CANIC_MASK_WUF3 ) != cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegWufId3 )
			{ 	                              
				t_u1WriteData = cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegWufId3;
				(void)Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WUFID3,
			                              u1CDD_CANIC_RO_READWRITE, t_u1WriteData );
			}	                              	                              
			/*------------------------*/	                              
			/* WUF ID MASK 設定        */
			/*------------------------*/
			t_u1ReadData = Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WUFIDMASK0,
			                                       u1CDD_CANIC_RO_READONLY, u1CDD_CANIC_ZERODATA );	
			if ( ( t_u1ReadData & u1CDD_CANIC_MASK_WUF ) != cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegWufIdMask0 )
			{ 	 
				t_u1WriteData = cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegWufIdMask0;
				(void)Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WUFIDMASK0,
			                              u1CDD_CANIC_RO_READWRITE, t_u1WriteData );
			}
			
			t_u1ReadData = Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WUFIDMASK1,
			                                       u1CDD_CANIC_RO_READONLY, u1CDD_CANIC_ZERODATA );	
			if ( ( t_u1ReadData & u1CDD_CANIC_MASK_WUF ) != cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegWufIdMask1 )
			{ 	 
				t_u1WriteData = cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegWufIdMask1;
				(void)Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WUFIDMASK1,
			                              u1CDD_CANIC_RO_READWRITE, t_u1WriteData );
			}

			t_u1ReadData = Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WUFIDMASK2,
			                                       u1CDD_CANIC_RO_READONLY, u1CDD_CANIC_ZERODATA );	
			if ( ( t_u1ReadData & u1CDD_CANIC_MASK_WUF ) != cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegWufIdMask2 )
			{ 	 
				t_u1WriteData = cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegWufIdMask2;
				(void)Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WUFIDMASK2,
			                              u1CDD_CANIC_RO_READWRITE, t_u1WriteData );
			}

			t_u1ReadData = Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WUFIDMASK3,
			                                       u1CDD_CANIC_RO_READONLY, u1CDD_CANIC_ZERODATA );	
			if ( ( t_u1ReadData & u1CDD_CANIC_MASK_WUF3 ) != cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegWufIdMask3 )
			{ 	 
				t_u1WriteData = cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegWufIdMask3;
				(void)Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WUFIDMASK3,
			                              u1CDD_CANIC_RO_READWRITE, t_u1WriteData );
			}

			/*------------------------*/	                              
			/* Frame Control 有効化設定    */
			/*------------------------*/
			t_u1ReadData = Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_FRAMECONTROL,
			                                       u1CDD_CANIC_RO_READONLY, u1CDD_CANIC_ZERODATA );	
			if ( ( t_u1ReadData & u1CDD_CANIC_MASK_FRAMECONTROL ) != cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegFrameControl )
			{ 	 
				t_u1WriteData = cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegFrameControl;
				(void)Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_FRAMECONTROL,
			                              u1CDD_CANIC_RO_READWRITE, t_u1WriteData );
			}
			
			/*------------------------*/	                              
			/* WUF DATA MASK 設定        */
			/*------------------------*/
			t_u1ReadData = Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WUFDATAMASK0,
			                                       u1CDD_CANIC_RO_READONLY, u1CDD_CANIC_ZERODATA );	
			if ( ( t_u1ReadData & u1CDD_CANIC_MASK_WUF ) != cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegWufDataMask0 )
			{ 	 
				t_u1WriteData = cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegWufDataMask0;
				(void)Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WUFDATAMASK0,
			                              u1CDD_CANIC_RO_READWRITE, t_u1WriteData );
			}

			t_u1ReadData = Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WUFDATAMASK1,
			                                       u1CDD_CANIC_RO_READONLY, u1CDD_CANIC_ZERODATA );	
			if ( ( t_u1ReadData & u1CDD_CANIC_MASK_WUF ) != cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegWufDataMask1 )
			{ 	 
				t_u1WriteData = cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegWufDataMask1;
				(void)Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WUFDATAMASK1,
			                              u1CDD_CANIC_RO_READWRITE, t_u1WriteData );
			}

			t_u1ReadData = Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WUFDATAMASK2,
			                                       u1CDD_CANIC_RO_READONLY, u1CDD_CANIC_ZERODATA );	
			if ( ( t_u1ReadData & u1CDD_CANIC_MASK_WUF ) != cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegWufDataMask2 )
			{ 	 
				t_u1WriteData = cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegWufDataMask2;
				(void)Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WUFDATAMASK2,
			                              u1CDD_CANIC_RO_READWRITE, t_u1WriteData );
			}

			t_u1ReadData = Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WUFDATAMASK3,
			                                       u1CDD_CANIC_RO_READONLY, u1CDD_CANIC_ZERODATA );	
			if ( ( t_u1ReadData & u1CDD_CANIC_MASK_WUF ) != cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegWufDataMask3 )
			{ 	 
				t_u1WriteData = cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegWufDataMask3;
				(void)Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WUFDATAMASK3,
			                              u1CDD_CANIC_RO_READWRITE, t_u1WriteData );
			}

			t_u1ReadData = Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WUFDATAMASK4,
			                                       u1CDD_CANIC_RO_READONLY, u1CDD_CANIC_ZERODATA );	
			if ( ( t_u1ReadData & u1CDD_CANIC_MASK_WUF ) != cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegWufDataMask4 )
			{ 	 
				t_u1WriteData = cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegWufDataMask4;
				(void)Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WUFDATAMASK4,
			                              u1CDD_CANIC_RO_READWRITE, t_u1WriteData );
			}

			t_u1ReadData = Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WUFDATAMASK5,
			                                       u1CDD_CANIC_RO_READONLY, u1CDD_CANIC_ZERODATA );	
			if ( ( t_u1ReadData & u1CDD_CANIC_MASK_WUF ) != cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegWufDataMask5 )
			{ 	 
				t_u1WriteData = cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegWufDataMask5;
				(void)Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WUFDATAMASK5,
			                              u1CDD_CANIC_RO_READWRITE, t_u1WriteData );
			}

			t_u1ReadData = Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WUFDATAMASK6,
			                                       u1CDD_CANIC_RO_READONLY, u1CDD_CANIC_ZERODATA );	
			if ( ( t_u1ReadData & u1CDD_CANIC_MASK_WUF ) != cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegWufDataMask6 )
			{ 	 
				t_u1WriteData = cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegWufDataMask6;
				(void)Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WUFDATAMASK6,
			                              u1CDD_CANIC_RO_READWRITE, t_u1WriteData );
			}

			t_u1ReadData = Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WUFDATAMASK7,
			                                       u1CDD_CANIC_RO_READONLY, u1CDD_CANIC_ZERODATA );	
			if ( ( t_u1ReadData & u1CDD_CANIC_MASK_WUF ) != cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegWufDataMask7 )
			{ 	 
				t_u1WriteData = cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegWufDataMask7;
				(void)Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_WUFDATAMASK7,
			                              u1CDD_CANIC_RO_READWRITE, t_u1WriteData );
			}
			
			/*-------------------------------*/
			/* Transceiver Event検出要否設定 */
			/*-------------------------------*/
			t_u1ReadData = Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_TRSCVEVTENABLE,
			                                       u1CDD_CANIC_RO_READONLY, u1CDD_CANIC_ZERODATA );	
			if ( ( t_u1ReadData & u1CDD_CANIC_MASK_TRSCVEVT ) != cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegTrscvEventEnable )	/* レジスタから読みだした値の対象Bitがコンフィグ値と一致するか確認 */
			{ 
				t_u1WriteData = cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegTrscvEventEnable; /* CBSE、CFEBitは設計上リフレッシュ不要だが、実装の観点(処理簡略化)からレジスタ全体をリフレッシュする */
				(void)Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_TRSCVEVTENABLE,
				                              u1CDD_CANIC_RO_READWRITE, t_u1WriteData );
			}
			
			/*--------------------------------------------*/
			/* CAN トランシーバ設定（トランシーバ有効化） */
			/*--------------------------------------------*/
			/*--------------------------------------------------------------------------------------------------*/
			/* Data rate register・ID registers・ID mask registers・Frame control register・Data mask registers	*/
			/* に値を書きこむとCAN control registerのPNCOKBitが0クリアされてしまい								*/
			/* パーシャルネットワーク機能が無効になってしまうため、												*/
			/* このレジスタのリフレッシュはそれらのレジスタのリフレッシュ以降に実施する必要がある				*/
			/*--------------------------------------------------------------------------------------------------*/
			t_u1ReadData = Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_CANCONTROL,
			                                       u1CDD_CANIC_RO_READONLY, u1CDD_CANIC_ZERODATA );
			t_u1WriteData = ( cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1RegTmpltCanControl | u1CDD_CANIC_CMC_ACTIVE_WO_UDV );                                       
			if ( ( t_u1ReadData & u1CDD_CANIC_MASK_CANCONTROL ) != t_u1WriteData )	/* レジスタから読みだした値の対象Bitがコンフィグ値およびActiveModeと一致するか確認 */
			{ 
				(void)Cdd_Canic_TransmitData( t_u1IcNo, u1CDD_CANIC_REG_ADDR_CANCONTROL,
			                              u1CDD_CANIC_RO_READWRITE, t_u1WriteData );
			}
		}
	}
}

/*----------------------------------------------------------------------------------------------*/
/* Local Functions																				*/
/*----------------------------------------------------------------------------------------------*/
static	U1	Cdd_Canic_TransmitData( U1 t_u1IcNo, U1 t_u1Addr, U1 t_u1RO, U1 t_u1Data )
{
	const	U1	t_cu1SpiChId = cstCdd_Canic_UcfgData.pcstIcCfg[t_u1IcNo].u1SpiChId;
	U2			t_u2SpiTxData;
	U2			t_u2SpiRxData;
	U1			t_u1RcvData;

	/*--------------------*/
	/* 送信フレームの準備 */
	/*--------------------*/
	t_u2SpiTxData = ( (U2)t_u1Addr << u1CDD_CANIC_SPI_FRAME_ADDR_BITPOSITION )
	              | ( (U2)t_u1RO   << u1CDD_CANIC_SPI_FRAME_RO_BITPOSITION )
	              |   (U2)t_u1Data; /* データフィールドの開始ビット位置は0 */

	/*----------*/
	/* 通信処理 */
	/*----------*/
	t_u2SpiRxData = (U2)Spi_SyncTransmit_SingleFrame( t_cu1SpiChId, (U4)t_u2SpiTxData );	/* SPI通信はSpiextの関数の中で排他処理が行われているため、Canicとして排他は不要 */

	CDD_CANIC_CFG_IC0_GETSPINLOCK(); /* SPI通信状態更新のため排他 */

	/*----------------*/
	/* 通信正常性検証 */
	/*----------------*/

	if ( s_u1Cdd_Canic_SpiStatus[t_u1IcNo] != (U1)NG ) {
		if ( ( t_u2SpiTxData & u2CDD_CANIC_SPI_FRAME_HEADER_MASK )
		      == ( t_u2SpiRxData & u2CDD_CANIC_SPI_FRAME_HEADER_MASK ) ) /* 送信ヘッダ部と受信ヘッダ部が一致？ */
		{
			s_u1Cdd_Canic_SpiStatus[t_u1IcNo] = (U1)OK; /* 通信正常 */
		}
		else
		{
			s_u1Cdd_Canic_SpiStatus[t_u1IcNo] = (U1)NG; /* 通信異常 */
		}
	}

	CDD_CANIC_CFG_IC0_RELEASESPINLOCK(); /* 排他解除 */

	/*--------------------*/
	/* 受信フレームの分割 */
	/*--------------------*/

	t_u1RcvData = (U1)( t_u2SpiRxData & u2CDD_CANIC_SPI_FRAME_DATA_MASK );

	return( t_u1RcvData );
}

//#include	"Cdd_Seccfg_Prge.h"
//#undef		SEL_PRGSEC
#pragma ghs section text=default
/*-- End Of File -------------------------------------------------------------------------------*/
