/* ErrH-r04-3000-0200-b-v00 */
/************************************************************************************************/
/*																								*/
/*		ErrH Driver																				*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

#if 0	// zantei ECCは2月末非対応

/*==============================================================================================*/
/* include files																				*/
/*==============================================================================================*/
#include	"ErrH_cfg.h"
#include	"ErrH.h"
#include	"ErrH_Ecc.h"

#include	"errh_reg_ecc.h"
#include	"pil_ecc.h"

/*==============================================================================================*/
/* prototypes																					*/
/*==============================================================================================*/
static	void			ErrH_Ecc_DF_Init( void );
static	void			ErrH_Ecc_Cram_Init( void );
static	void			ErrH_Ecc_PR32_Init( void );
static	void			ErrH_Ecc_PR16_Init( void );
static	void			ErrH_Ecc_DTP_Init( void );
static	void			ErrH_Ecc_ClearEcc1bitErrRomRam( U1 t_u1ModuleNum );
static	void			ErrH_Ecc_ClearEcc1bitErrPeripheral( U1 t_u1ModuleNum );
static	void			ErrH_Ecc_ClearEcc1bitErrDtpAddr( U1 t_u1ModuleNum );
static	void			ErrH_Ecc_ClearEccFatalErrRomRam( U1 t_u1ModuleNum );
static	void			ErrH_Ecc_ClearEccFatalErrPeripheral( U1 t_u1ModuleNum );
static	void			ErrH_Ecc_ClearEccFatalErrDtpAddr( U1 t_u1ModuleNum );
static	void			ErrH_Ecc_ClearEccFatalErrDtpData( U1 t_u1ModuleNum );
static	U1				ErrH_Ecc_GetEccFatalErrStsRomRam( U1 t_u1ModuleNum );
static	U1				ErrH_Ecc_GetEccFatalErrStsPeripheral( U1 t_u1ModuleNum );
static	U1				ErrH_Ecc_GetEccFatalErrStsDtpAddr( U1 t_u1ModuleNum );
static	U1				ErrH_Ecc_GetEccFatalErrStsDtpData( U1 t_u1ModuleNum );
static	U1				ErrH_Ecc_Compare4ByteMask( volatile const U4 *t_pcu4Address, U4 t_u4ExpectedValue, U4 t_u4Mask );
static	void			ErrH_Ecc_Reg_RestoreEccProt4ByteMask( volatile U4 *t_pu4Address, U4 t_u4ExpectedValue, U4 t_u4Mask );
static	void			ErrH_Ecc_Reg_RestorePb5eccApecProt4ByteMask( volatile U4 *t_pu4Address, U4 t_u4ExpectedValue, U4 t_u4Mask );

/*==============================================================================================*/
/* defines / data types / structs / unions / macros												*/
/*==============================================================================================*/
/* モジュール番号から配列の要素に変換 */
#define		u1ERRH_ECC_PR32_OFFSET				((U1)21U)				/* PR32オフセット値 */
#define		u1ERRH_ECC_PR16_OFFSET				((U1)68U)				/* PR16オフセット値 */
#define		u1ERRH_ECC_HBNECC_ADDR_OFFSET		((U1)77U)				/* HBNECCアドレスオフセット値 */
#define		u1ERRH_ECC_V2AN_ADDR_OFFSET			((U1)86U)				/* V2ANアドレスオフセット値 */
#define		u1ERRH_ECC_HBNECC_DATA_OFFSET		((U1)103U)				/* HBNECCデータオフセット値 */
#define		u1ERRH_ECC_V2AN_DATA_OFFSET			((U1)112U)				/* V2ANデータオフセット値 */

/* ECCエラーステータス(戻り値変換) */
#define		u4ERRH_ECC_ERR_NOTDETECT			((U4)0x00000000U)		/* 異常なし */
#define		u1ERRH_ECC_ERR_NOTDETECT			((U1)0x00U)				/* 異常なし */
#define		u1ERRH_ECC_ERR_1BITDETECT			((U1)0x01U)				/* 1bitエラー */
#define		u1ERRH_ECC_ERR_2BITDETECT			((U1)0x02U)				/* 2bitエラー */
#define		u1ERRH_ECC_ERR_OVF					((U1)0x04U)				/* オーバーフローエラー */

/* エラー発生アドレス格納バッファ数 */
#define		u1ERRH_ECC_ADDR_BUFFNUM_LRAM		((U1)8U)				/* LRAM エラー発生アドレス格納バッファ数 */
#define		u1ERRH_ECC_ADDR_BUFFNUM_CRAM		((U1)8U)				/* CRAM エラー発生アドレス格納バッファ数 */

/* エラー発生アドレス復号用 */
#define		u1ERRH_ECC_ADDR_LSHIFT_2BIT			((U1)2U)				/* 2bit左シフト */
#define		u1ERRH_ECC_ADDR_LSHIFT_3BIT			((U1)3U)				/* 3bit左シフト */
#define		u1ERRH_ECC_ADDR_RSHIFT_3BIT			((U1)3U)				/* 3bit右シフト */
#define		u1ERRH_ECC_ADDR_RSHIFT_5BIT			((U1)5U)				/* 5bit右シフト */
#define		u4ERRH_ECC_ADDR_OFFSET_LRAM_PE0		((U4)0xFDC00000U)		/* LRAM PE0 エラーアドレスオフセット値 */
#define		u4ERRH_ECC_ADDR_OFFSET_LRAM_PE1		((U4)0xFDA00000U)		/* LRAM PE1 エラーアドレスオフセット値 */
#define		u4ERRH_ECC_ADDR_OFFSET_LRAM_PE2		((U4)0xFD800000U)		/* LRAM PE2 エラーアドレスオフセット値 */
#define		u4ERRH_ECC_ADDR_OFFSET_LRAM_LRA		((U4)0xFC000000U)		/* LRAM PRA エラーアドレスオフセット値 */
#define		u4ERRH_ECC_ADDR_OFFSET_CRAM			((U4)0xFE000000U)		/* CRAM エラーアドレスオフセット値 */
#define		u4ERRH_ECC_ADDR_OFFSET_DTS			((U4)0xFFF89000U)		/* DTS エラーアドレスオフセット値 */
#define		u4ERRH_ECC_ADDR_OFFSET_SDMC0		((U4)0xFFF94000U)		/* SDMC0 エラーアドレスオフセット値 */
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
#define		u4ERRH_ECC_ADDR_OFFSET_SDMC1		((U4)0xFFF9C000U)		/* SDMC1 エラーアドレスオフセット値 */
#endif
#define		u4ERRH_ECC_ADDR_OFFSET_RSCANFD0		((U4)0xFF808400U)		/* RSCANFD0 エラーアドレスオフセット値 */
#define		u4ERRH_ECC_ADDR_OFFSET_4BYTE		((U4)0x00000004U)		/* エラーアドレスオフセット値(オフセット4BYTE) */
#define		u4ERRH_ECC_ADDR_OFFSET_MSPI0		((U4)0xFFC77000U)		/* MSPI0 エラーアドレスオフセット値 */
#define		u4ERRH_ECC_ADDR_OFFSET_MSPI1		((U4)0xFFD5F000U)		/* MSPI1 エラーアドレスオフセット値 */
#define		u4ERRH_ECC_ADDR_OFFSET_MSPI2		((U4)0xFFD81000U)		/* MSPI2 エラーアドレスオフセット値 */
#define		u4ERRH_ECC_ADDR_OFFSET_MSPI3		((U4)0xFFD61000U)		/* MSPI3 エラーアドレスオフセット値 */
#define		u4ERRH_ECC_ADDR_OFFSET_MSPI4		((U4)0xFFD83000U)		/* MSPI4 エラーアドレスオフセット値 */
#define		u4ERRH_ECC_ADDR_OFFSET_MSPI5		((U4)0xFFD63000U)		/* MSPI5 エラーアドレスオフセット値 */
#define		u4ERRH_ECC_ADDR_OFFSET_MSPI6		((U4)0xFFD85000U)		/* MSPI6 エラーアドレスオフセット値 */
#define		u4ERRH_ECC_ADDR_OFFSET_MSPI7		((U4)0xFFD65000U)		/* MSPI7 エラーアドレスオフセット値 */
#define		u4ERRH_ECC_ADDR_OFFSET_MSPI8		((U4)0xFFD87000U)		/* MSPI8 エラーアドレスオフセット値 */
#define		u4ERRH_ECC_ADDR_OFFSET_MSPI9		((U4)0xFFD67000U)		/* MSPI9 エラーアドレスオフセット値 */
#define		u4ERRH_ECC_ADDR_OFFSET_DFE0CM		((U4)0xFFD89000U)		/* DFE0_CMEM エラーアドレスオフセット値 */
#define		u4ERRH_ECC_ADDR_OFFSET_DFE1CM		((U4)0xFFD71000U)		/* DFE1_CMEM エラーアドレスオフセット値 */
#define		u4ERRH_ECC_ADDR_OFFSET_DFE0DM0		((U4)0xFFD8A000U)		/* DFE0_DMEM0 エラーアドレスオフセット値 */
#define		u4ERRH_ECC_ADDR_OFFSET_DFE0DM1		((U4)0xFFD8A002U)		/* DFE0_DMEM1 エラーアドレスオフセット値 */
#define		u4ERRH_ECC_ADDR_OFFSET_DFE1DM0		((U4)0xFFD72000U)		/* DFE1_DMEM0 エラーアドレスオフセット値 */
#define		u4ERRH_ECC_ADDR_OFFSET_DFE1DM1		((U4)0xFFD72002U)		/* DFE1_DMEM1 エラーアドレスオフセット値 */
#define		u4ERRH_ECC_ADDR_MASK_BIT_8_0		((U4)0x000001FFU)		/* 8-0bitマスク値 */
#define		u4ERRH_ECC_ADDR_MASK_BIT_7_0		((U4)0x000000FFU)		/* 7-0bitマスク値 */
#define		u4ERRH_ECC_ADDR_MASK_BIT_6_0		((U4)0x0000007FU)		/* 6-0bitマスク値 */
#define		u4ERRH_ECC_ADDR_MASK_BIT_5_0		((U4)0x0000003FU)		/* 5-0bitマスク値 */
#define		u4ERRH_ECC_ADDR_MASK_BIT_4_0		((U4)0x0000001FU)		/* 4-0bitマスク値 */

/* エラー詳細情報取得用 */
#define		u1ERRH_ECC_DETAIL_RSHIFT_27BIT		((U1)27U)				/* 27bit右シフト */

/* ステータスレジスタ用マスク値 */
#define		u4ERRH_ECC_MASK_1BIT_LR_PE0			((U4)( ECC_MECCCAP_LR_PE0CL0_SERSTR_07	+ ECC_MECCCAP_LR_PE0CL0_SERSTR_06	\
													 + ECC_MECCCAP_LR_PE0CL0_SERSTR_05	+ ECC_MECCCAP_LR_PE0CL0_SERSTR_04	\
													 + ECC_MECCCAP_LR_PE0CL0_SERSTR_03	+ ECC_MECCCAP_LR_PE0CL0_SERSTR_02	\
													 + ECC_MECCCAP_LR_PE0CL0_SERSTR_01	+ ECC_MECCCAP_LR_PE0CL0_SERSTR_00 ))	/* LR_PE0 1bitエラーステータスマスク値 */

#define		u4ERRH_ECC_MASK_1BIT_LR_PE1			((U4)( ECC_MECCCAP_LR_PE1CL0_SERSTR_07	+ ECC_MECCCAP_LR_PE1CL0_SERSTR_06	\
													 + ECC_MECCCAP_LR_PE1CL0_SERSTR_05	+ ECC_MECCCAP_LR_PE1CL0_SERSTR_04	\
													 + ECC_MECCCAP_LR_PE1CL0_SERSTR_03	+ ECC_MECCCAP_LR_PE1CL0_SERSTR_02	\
													 + ECC_MECCCAP_LR_PE1CL0_SERSTR_01	+ ECC_MECCCAP_LR_PE1CL0_SERSTR_00 ))	/* LR_PE1 1bitエラーステータスマスク値 */

#define		u4ERRH_ECC_MASK_1BIT_LR_PE2			((U4)( ECC_MECCCAP_LR_PE2CL1_SERSTR_07	+ ECC_MECCCAP_LR_PE2CL1_SERSTR_06	\
													 + ECC_MECCCAP_LR_PE2CL1_SERSTR_05	+ ECC_MECCCAP_LR_PE2CL1_SERSTR_04	\
													 + ECC_MECCCAP_LR_PE2CL1_SERSTR_03	+ ECC_MECCCAP_LR_PE2CL1_SERSTR_02	\
													 + ECC_MECCCAP_LR_PE2CL1_SERSTR_01	+ ECC_MECCCAP_LR_PE2CL1_SERSTR_00 ))	/* LR_PE2 1bitエラーステータスマスク値 */

#define		u4ERRH_ECC_MASK_1BIT_LR_ALL			((U4)( ECC_MECCCAP_LRA_LR1_SERSTR_07	+ ECC_MECCCAP_LRA_LR1_SERSTR_06		\
													 + ECC_MECCCAP_LRA_LR1_SERSTR_05	+ ECC_MECCCAP_LRA_LR1_SERSTR_04		\
													 + ECC_MECCCAP_LRA_LR1_SERSTR_03	+ ECC_MECCCAP_LRA_LR1_SERSTR_02		\
													 + ECC_MECCCAP_LRA_LR1_SERSTR_01	+ ECC_MECCCAP_LRA_LR1_SERSTR_00 ))		/* LR_ALL 1bitエラーステータスマスク値 */

#define		u4ERRH_ECC_MASK_1BIT_CR				((U4)( ECC_MECCCAP_CRAM_CR_SERSTR_07	+ ECC_MECCCAP_CRAM_CR_SERSTR_06		\
													 + ECC_MECCCAP_CRAM_CR_SERSTR_05	+ ECC_MECCCAP_CRAM_CR_SERSTR_04		\
													 + ECC_MECCCAP_CRAM_CR_SERSTR_03	+ ECC_MECCCAP_CRAM_CR_SERSTR_02		\
													 + ECC_MECCCAP_CRAM_CR_SERSTR_01	+ ECC_MECCCAP_CRAM_CR_SERSTR_00 ))		/* CR 1bitエラーステータスマスク値 */

#if ( MCU_TYPE_SERIES == MCU_RH850U2B6 )
#define		u4ERRH_ECC_MASK_1BIT_DTP_LRAM_ADDR	((U4)( ECC_BECCCAP_LRAM_BUSASERSTR_17	+ ECC_BECCCAP_LRAM_BUSASERSTR_16	\
													 + ECC_BECCCAP_LRAM_BUSASERSTR_02	+ ECC_BECCCAP_LRAM_BUSASERSTR_01	\
													 + ECC_BECCCAP_LRAM_BUSASERSTR_00 ))										/* DTP_LRAM_ADDR 1bitエラーステータスマスク値 */
#elif ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
#define		u4ERRH_ECC_MASK_1BIT_DTP_LRAM_ADDR	((U4)( ECC_BECCCAP_LRAM_BUSASERSTR_17	+ ECC_BECCCAP_LRAM_BUSASERSTR_16	\
													 + ECC_BECCCAP_LRAM_BUSASERSTR_03	+ ECC_BECCCAP_LRAM_BUSASERSTR_02	\
													 + ECC_BECCCAP_LRAM_BUSASERSTR_01	+ ECC_BECCCAP_LRAM_BUSASERSTR_00 ))		/* DTP_LRAM_ADDR 1bitエラーステータスマスク値 */
#else
	#error "MCU_TYPE_SERIES is not supported"
#endif

#if ( MCU_TYPE_SERIES == MCU_RH850U2B6 )
#define		u4ERRH_ECC_MASK_1BIT_DTP_CRAM_ADDR	((U4)( ECC_BECCCAP_CRAM_BUSASERSTR_24	+ ECC_BECCCAP_CRAM_BUSASERSTR_02	\
													 + ECC_BECCCAP_CRAM_BUSASERSTR_01	+ ECC_BECCCAP_CRAM_BUSASERSTR_00 ))		/* DTP_CRAM_ADDR 1bitエラーステータスマスク値 */
#elif ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
#define		u4ERRH_ECC_MASK_1BIT_DTP_CRAM_ADDR	((U4)( ECC_BECCCAP_CRAM_BUSASERSTR_25	+ ECC_BECCCAP_CRAM_BUSASERSTR_24	\
													 + ECC_BECCCAP_CRAM_BUSASERSTR_06	+ ECC_BECCCAP_CRAM_BUSASERSTR_05	\
													 + ECC_BECCCAP_CRAM_BUSASERSTR_04	+ ECC_BECCCAP_CRAM_BUSASERSTR_02	\
													 + ECC_BECCCAP_CRAM_BUSASERSTR_01	+ ECC_BECCCAP_CRAM_BUSASERSTR_00 ))		/* DTP_CRAM_ADDR 1bitエラーステータスマスク値 */
#else
	#error "MCU_TYPE_SERIES is not supported"
#endif

#if ( MCU_TYPE_SERIES == MCU_RH850U2B6 )
#define		u4ERRH_ECC_MASK_1BIT_DTP_CFL_ADDR	((U4)( ECC_BECCCAP_CFL_BUSASERSTR_24	+ ECC_BECCCAP_CFL_BUSASERSTR_01		\
													 + ECC_BECCCAP_CFL_BUSASERSTR_00 ))											/* DTP_CFL_ADDR 1bitエラーステータスマスク値 */
#elif ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
#define		u4ERRH_ECC_MASK_1BIT_DTP_CFL_ADDR	((U4)( ECC_BECCCAP_CFL_BUSASERSTR_25	+ ECC_BECCCAP_CFL_BUSASERSTR_24		\
													 + ECC_BECCCAP_CFL_BUSASERSTR_05	+ ECC_BECCCAP_CFL_BUSASERSTR_04		\
													 + ECC_BECCCAP_CFL_BUSASERSTR_01	+ ECC_BECCCAP_CFL_BUSASERSTR_00 ))		/* DTP_CFL_ADDR 1bitエラーステータスマスク値 */
#else
	#error "MCU_TYPE_SERIES is not supported"
#endif

#define		u4ERRH_ECC_MASK_1BIT_DTP_PERI_ADDR	((U4)( ECC_BECCCAP_PERI_BUSASERSTR_25	+ ECC_BECCCAP_PERI_BUSASERSTR_20	\
													 + ECC_BECCCAP_PERI_BUSASERSTR_18	+ ECC_BECCCAP_PERI_BUSASERSTR_17	\
													 + ECC_BECCCAP_PERI_BUSASERSTR_16 ))										/* DTP_PERI_ADDR 1bitエラーステータスマスク値 */

#if ( MCU_TYPE_SERIES == MCU_RH850U2B6 )
#define		u4ERRH_ECC_MASK_1BIT_DTP_EMU_ADDR	((U4)( ECC_BECCCAP_EMU_BUSASERSTR_17										\
													 + ECC_BECCCAP_EMU_BUSASERSTR_16	+ ECC_BECCCAP_EMU_BUSASERSTR_04		\
													 + ECC_BECCCAP_EMU_BUSASERSTR_02	+ ECC_BECCCAP_EMU_BUSASERSTR_00 ))		/* DTP_EMU_ADDR 1bitエラーステータスマスク値 */
#elif ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
#define		u4ERRH_ECC_MASK_1BIT_DTP_EMU_ADDR	((U4)( ECC_BECCCAP_EMU_BUSASERSTR_18	+ ECC_BECCCAP_EMU_BUSASERSTR_17		\
													 + ECC_BECCCAP_EMU_BUSASERSTR_16	+ ECC_BECCCAP_EMU_BUSASERSTR_06		\
													 + ECC_BECCCAP_EMU_BUSASERSTR_04	+ ECC_BECCCAP_EMU_BUSASERSTR_02		\
													 + ECC_BECCCAP_EMU_BUSASERSTR_00 ))											/* DTP_EMU_ADDR 1bitエラーステータスマスク値 */
#else
	#error "MCU_TYPE_SERIES is not supported"
#endif

#if ( MCU_TYPE_SERIES == MCU_RH850U2B6 )
#define		u4ERRH_ECC_MASK_2BIT_DTP_LRAM_ADDR	((U4)( ECC_BECCCAP_LRAM_BUSADERSTR_17	+ ECC_BECCCAP_LRAM_BUSADERSTR_16	\
													 + ECC_BECCCAP_LRAM_BUSADERSTR_02	+ ECC_BECCCAP_LRAM_BUSADERSTR_01	\
													 + ECC_BECCCAP_LRAM_BUSADERSTR_00 ))										/* DTP_LRAM_ADDR 2bitエラーステータスマスク値 */
#elif ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
#define		u4ERRH_ECC_MASK_2BIT_DTP_LRAM_ADDR	((U4)( ECC_BECCCAP_LRAM_BUSADERSTR_17	+ ECC_BECCCAP_LRAM_BUSADERSTR_16	\
													 + ECC_BECCCAP_LRAM_BUSADERSTR_03	+ ECC_BECCCAP_LRAM_BUSADERSTR_02	\
													 + ECC_BECCCAP_LRAM_BUSADERSTR_01	+ ECC_BECCCAP_LRAM_BUSADERSTR_00 ))		/* DTP_LRAM_ADDR 2bitエラーステータスマスク値 */
#else
	#error "MCU_TYPE_SERIES is not supported"
#endif

#if ( MCU_TYPE_SERIES == MCU_RH850U2B6 )
#define		u4ERRH_ECC_MASK_2BIT_DTP_CRAM_ADDR	((U4)( ECC_BECCCAP_CRAM_BUSADERSTR_24	+ ECC_BECCCAP_CRAM_BUSADERSTR_02	\
													 + ECC_BECCCAP_CRAM_BUSADERSTR_01	+ ECC_BECCCAP_CRAM_BUSADERSTR_00 ))		/* DTP_CRAM_ADDR 2bitエラーステータスマスク値 */
#elif ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
#define		u4ERRH_ECC_MASK_2BIT_DTP_CRAM_ADDR	((U4)( ECC_BECCCAP_CRAM_BUSADERSTR_25	+ ECC_BECCCAP_CRAM_BUSADERSTR_24	\
													 + ECC_BECCCAP_CRAM_BUSADERSTR_06	+ ECC_BECCCAP_CRAM_BUSADERSTR_05	\
													 + ECC_BECCCAP_CRAM_BUSADERSTR_04	+ ECC_BECCCAP_CRAM_BUSADERSTR_02	\
													 + ECC_BECCCAP_CRAM_BUSADERSTR_01	+ ECC_BECCCAP_CRAM_BUSADERSTR_00 ))		/* DTP_CRAM_ADDR 2bitエラーステータスマスク値 */
#else
	#error "MCU_TYPE_SERIES is not supported"
#endif

#if ( MCU_TYPE_SERIES == MCU_RH850U2B6 )
#define		u4ERRH_ECC_MASK_2BIT_DTP_CFL_ADDR	((U4)( ECC_BECCCAP_CFL_BUSADERSTR_24	+ ECC_BECCCAP_CFL_BUSADERSTR_01		\
													 + ECC_BECCCAP_CFL_BUSADERSTR_00 ))											/* DTP_CFL_ADDR 2bitエラーステータスマスク値 */

#elif ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
#define		u4ERRH_ECC_MASK_2BIT_DTP_CFL_ADDR	((U4)( ECC_BECCCAP_CFL_BUSADERSTR_25	+ ECC_BECCCAP_CFL_BUSADERSTR_24		\
													 + ECC_BECCCAP_CFL_BUSADERSTR_05	+ ECC_BECCCAP_CFL_BUSADERSTR_04		\
													 + ECC_BECCCAP_CFL_BUSADERSTR_01	+ ECC_BECCCAP_CFL_BUSADERSTR_00 ))		/* DTP_CFL_ADDR 2bitエラーステータスマスク値 */
#else
	#error "MCU_TYPE_SERIES is not supported"
#endif

#define		u4ERRH_ECC_MASK_2BIT_DTP_PERI_ADDR	((U4)( ECC_BECCCAP_PERI_BUSADERSTR_25	+ ECC_BECCCAP_PERI_BUSADERSTR_20	\
													 + ECC_BECCCAP_PERI_BUSADERSTR_18	+ ECC_BECCCAP_PERI_BUSADERSTR_17	\
													 + ECC_BECCCAP_PERI_BUSADERSTR_16 ))										/* DTP_PERI_ADDR 2bitエラーステータスマスク値 */

#if ( MCU_TYPE_SERIES == MCU_RH850U2B6 )
#define		u4ERRH_ECC_MASK_2BIT_DTP_EMU_ADDR	((U4)( ECC_BECCCAP_EMU_BUSADERSTR_17										\
													 + ECC_BECCCAP_EMU_BUSADERSTR_16	+ ECC_BECCCAP_EMU_BUSADERSTR_04		\
													 + ECC_BECCCAP_EMU_BUSADERSTR_02	+ ECC_BECCCAP_EMU_BUSADERSTR_00 ))		/* DTP_EMU_ADDR 2bitエラーステータスマスク値 */
#elif ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
#define		u4ERRH_ECC_MASK_2BIT_DTP_EMU_ADDR	((U4)( ECC_BECCCAP_EMU_BUSADERSTR_18	+ ECC_BECCCAP_EMU_BUSADERSTR_17		\
													 + ECC_BECCCAP_EMU_BUSADERSTR_16	+ ECC_BECCCAP_EMU_BUSADERSTR_06		\
													 + ECC_BECCCAP_EMU_BUSADERSTR_04	+ ECC_BECCCAP_EMU_BUSADERSTR_02		\
													 + ECC_BECCCAP_EMU_BUSADERSTR_00 ))											/* DTP_EMU_ADDR 2bitエラーステータスマスク値 */
#else
	#error "MCU_TYPE_SERIES is not supported"
#endif

#define		u4ERRH_ECC_MASK_2BIT_DTP_V2AN_ADDR	((U4)ECC_BECCCAP_V2AN_BUSADERSTR_ADEDF00)										/* DTP_V2AN_ADDR 2bitエラーステータスマスク値 */

#if ( MCU_TYPE_SERIES == MCU_RH850U2B6 )
#define		u4ERRH_ECC_MASK_2BIT_DTP_LRAM_DATA	((U4)( ECC_BECCCAP_LRAM_BUSDDERSTR_02	+ ECC_BECCCAP_LRAM_BUSDDERSTR_01	\
													 + ECC_BECCCAP_LRAM_BUSDDERSTR_00 ))										/* DTP_LRAM_DATA 2bitエラーステータスマスク値 */
#elif ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
#define		u4ERRH_ECC_MASK_2BIT_DTP_LRAM_DATA	((U4)( ECC_BECCCAP_LRAM_BUSDDERSTR_03	+ ECC_BECCCAP_LRAM_BUSDDERSTR_02	\
													 + ECC_BECCCAP_LRAM_BUSDDERSTR_01	+ ECC_BECCCAP_LRAM_BUSDDERSTR_00 ))		/* DTP_LRAM_DATA 2bitエラーステータスマスク値 */
#else
	#error "MCU_TYPE_SERIES is not supported"
#endif

#if ( MCU_TYPE_SERIES == MCU_RH850U2B6 )
#define		u4ERRH_ECC_MASK_2BIT_DTP_CRAM_DATA	((U4)( ECC_BECCCAP_CRAM_BUSDDERSTR_02	+ ECC_BECCCAP_CRAM_BUSDDERSTR_01	\
													 + ECC_BECCCAP_CRAM_BUSDDERSTR_00 ))										/* DTP_CRAM_DATA 2bitエラーステータスマスク値 */
#elif ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
#define		u4ERRH_ECC_MASK_2BIT_DTP_CRAM_DATA	((U4)( ECC_BECCCAP_CRAM_BUSDDERSTR_06	+ ECC_BECCCAP_CRAM_BUSDDERSTR_05	\
													 + ECC_BECCCAP_CRAM_BUSDDERSTR_04	+ ECC_BECCCAP_CRAM_BUSDDERSTR_02	\
													 + ECC_BECCCAP_CRAM_BUSDDERSTR_01	+ ECC_BECCCAP_CRAM_BUSDDERSTR_00 ))		/* DTP_CRAM_DATA 2bitエラーステータスマスク値 */
#else
	#error "MCU_TYPE_SERIES is not supported"
#endif

#if ( MCU_TYPE_SERIES == MCU_RH850U2B6 )
#define		u4ERRH_ECC_MASK_2BIT_DTP_PERI_DATA	((U4)( ECC_BECCCAP_PERI_BUSDDERSTR_25	+ ECC_BECCCAP_PERI_BUSDDERSTR_18	\
													 + ECC_BECCCAP_PERI_BUSDDERSTR_17	+ ECC_BECCCAP_PERI_BUSDDERSTR_16	\
													 + ECC_BECCCAP_PERI_BUSDDERSTR_11	+ ECC_BECCCAP_PERI_BUSDDERSTR_10	\
													 + ECC_BECCCAP_PERI_BUSDDERSTR_09	+ ECC_BECCCAP_PERI_BUSDDERSTR_08	\
													 + ECC_BECCCAP_PERI_BUSDDERSTR_02	+ ECC_BECCCAP_PERI_BUSDDERSTR_01	\
													 + ECC_BECCCAP_PERI_BUSDDERSTR_00 ))										/* DTP_PERI_DATA 2bitエラーステータスマスク値 */
#elif ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
#define		u4ERRH_ECC_MASK_2BIT_DTP_PERI_DATA	((U4)( ECC_BECCCAP_PERI_BUSDDERSTR_25	+ ECC_BECCCAP_PERI_BUSDDERSTR_18	\
													 + ECC_BECCCAP_PERI_BUSDDERSTR_17	+ ECC_BECCCAP_PERI_BUSDDERSTR_16	\
													 + ECC_BECCCAP_PERI_BUSDDERSTR_11	+ ECC_BECCCAP_PERI_BUSDDERSTR_10	\
													 + ECC_BECCCAP_PERI_BUSDDERSTR_09	+ ECC_BECCCAP_PERI_BUSDDERSTR_08	\
													 + ECC_BECCCAP_PERI_BUSDDERSTR_03	+ ECC_BECCCAP_PERI_BUSDDERSTR_02	\
													 + ECC_BECCCAP_PERI_BUSDDERSTR_01	+ ECC_BECCCAP_PERI_BUSDDERSTR_00 ))		/* DTP_PERI_DATA 2bitエラーステータスマスク値 */
#else
	#error "MCU_TYPE_SERIES is not supported"
#endif

#if ( MCU_TYPE_SERIES == MCU_RH850U2B6 )
#define		u4ERRH_ECC_MASK_2BIT_DTP_DMDT_DATA	((U4)( ECC_BECCCAP_DMDT_BUSDDERSTR_08	+ ECC_BECCCAP_DMDT_BUSDDERSTR_05	\
													 + ECC_BECCCAP_DMDT_BUSDDERSTR_04	+ ECC_BECCCAP_DMDT_BUSDDERSTR_01	\
													 + ECC_BECCCAP_DMDT_BUSDDERSTR_00 ))										/* DTP_DMDT_DATA 2bitエラーステータスマスク値 */
#elif ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
#define		u4ERRH_ECC_MASK_2BIT_DTP_DMDT_DATA	((U4)( ECC_BECCCAP_DMDT_BUSDDERSTR_08	+ ECC_BECCCAP_DMDT_BUSDDERSTR_07	\
													 + ECC_BECCCAP_DMDT_BUSDDERSTR_06	+ ECC_BECCCAP_DMDT_BUSDDERSTR_05	\
													 + ECC_BECCCAP_DMDT_BUSDDERSTR_04	+ ECC_BECCCAP_DMDT_BUSDDERSTR_03	\
													 + ECC_BECCCAP_DMDT_BUSDDERSTR_02	+ ECC_BECCCAP_DMDT_BUSDDERSTR_01	\
													 + ECC_BECCCAP_DMDT_BUSDDERSTR_00 ))										/* DTP_DMDT_DATA 2bitエラーステータスマスク値 */
#else
	#error "MCU_TYPE_SERIES is not supported"
#endif

#define		u4ERRH_ECC_MASK_2BIT_DTP_EMU_DATA	((U4)ECC_BECCCAP_EMU_BUSDDERSTR_17)												/* DTP_EMU_DATA 2bitエラーステータスマスク値 */

#define		u4ERRH_ECC_MASK_2BIT_DTP_V2AN_DATA	((U4)ECC_BECCCAP_V2AN_BUSDDERSTR_DDEDF00)										/* DTP_V2AN_DATA 2bitエラーステータスマスク値 */

/* リザーブビット用のマスク値 */
#define		u4ERRH_ECC_MASK_ECCCNT_CRCCL0_CRCAFCTL	((U4)0xFFFFFFF7U)															/* ECCCNT_CRCCL0_CRCAFCTL リザーブビット用のマスク値 */
#define		u4ERRH_ECC_MASK_ECCCNT_CRCCL1_CRCAFCTL	((U4)0xFFFFFFF7U)															/* ECCCNT_CRCCL1_CRCAFCTL リザーブビット用のマスク値 */
#define		u4ERRH_ECC_MASK_ECC_HBNECC_HBECECCCTL	((U4)0xFFFFFFF8U)															/* ECC_HBNECC_HBECECCCTL リザーブビット用のマスク値 */

#define		u4ERRH_ECC_ERROR_SPID_ALLCLEAR			((U4)0xFFFFFFFFU)															/* エラーSPID全クリア値 */

#define		u1ERRH_ECC_REGCHECK_STS_COMPLETED		((U1)0U)																	/* サブモジュールレジスタ診断開始待ち(内部ステータス) */
#define		u1ERRH_ECC_REGCHECK_STS_BUSY			((U1)1U)																	/* サブモジュールレジスタ診断中(内部ステータス) */
#define		u1ERRH_ECC_CHECKRESULT_MASK_UPPER4BIT	((U1)0x0FU)																	/* 上位4bitマスク(4～7bit) */
#define		u1ERRH_ECC_REGCHECK_COMPLETED			((U1)0x00U)																	/* サブモジュールレジスタ診断開始待ち */
#define		u1ERRH_ECC_REGCHECK_BUSY				((U1)0x10U)																	/* サブモジュールレジスタ診断中 */

/*==============================================================================================*/
/* constants																					*/
/*==============================================================================================*/
#pragma ghs section rodata=".ERRH_RODATA_CONST"
/* Peripheral RAM (32 bits) */
static volatile U1 const cu1Ecc_Ecc7UseTable[ECC7_CHANNEL_NUM] = 
{
	(U1)ON,		/* RS-CAN-FD0 *//* Message buffer RAM (MRAM) */
	(U1)ON,		/* RS-CAN-FD0 *//* Acceptance filter list RAM (AFLRAM 0) */
	(U1)ON,		/* RS-CAN-FD0 *//* Acceptance filter list RAM (AFLRAM 1) */
	(U1)ON,		/* RS-CAN-FD0 *//* Pretended network filter list RAM (PFLRAM) */
	(U1)OFF,	/* FlexRay0 *//* Message RAM (MRAM) */
	(U1)OFF,	/* FlexRay0 *//* Temporary buffer (TBFRAM A) */
	(U1)OFF,	/* FlexRay0 *//* Temporary buffer (TBFRAM B) */
	(U1)OFF,	/* GTM *//* MCS0_RAM0 */
	(U1)OFF,	/* GTM *//* MCS0_RAM1 */
	(U1)OFF,	/* GTM *//* MCS1_RAM0 */
	(U1)OFF,	/* GTM *//* MCS1_RAM1 */
	(U1)OFF,	/* GTM *//* MCS2_RAM0 */
	(U1)OFF,	/* GTM *//* MCS2_RAM1 */
	(U1)OFF,	/* GTM *//* MCS3_RAM0 */
	(U1)OFF,	/* GTM *//* MCS3_RAM1 */
	(U1)OFF,	/* GTM *//* MCS4_RAM0 */
	(U1)OFF,	/* GTM *//* MCS4_RAM1 */
	(U1)OFF,	/* GTM *//* MCS5_RAM0 */
	(U1)OFF,	/* GTM *//* MCS5_RAM1 */
	(U1)OFF,	/* GTM *//* MCS6_RAM0 */
	(U1)OFF,	/* GTM *//* MCS6_RAM1 */
	(U1)OFF,	/* GTM *//* FIFO0 RAM */
	(U1)OFF,	/* GTM *//* FIFO1 RAM */
	(U1)OFF,	/* GTM *//* FIFO2 RAM */
	(U1)OFF,	/* GTM *//* DPLL RAM1A */
	(U1)OFF,	/* GTM *//* DPLL RAM1B */
	(U1)OFF,	/* GTM *//* DPLL RAM2 */
	(U1)ON,		/* MSPI *//* MSPI0 RAM */
	(U1)ON,		/* MSPI *//* MSPI1 RAM */
	(U1)ON,		/* MSPI *//* MSPI2 RAM */
	(U1)ON,		/* MSPI *//* MSPI3 RAM */
	(U1)ON,		/* MSPI *//* MSPI4 RAM */
	(U1)ON,		/* MSPI *//* MSPI5 RAM */
	(U1)ON,		/* MSPI *//* MSPI6 RAM */
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
	(U1)ON,		/* MSPI *//* MSPI7 RAM */
	(U1)ON,		/* MSPI *//* MSPI8 RAM */
	(U1)ON,		/* MSPI *//* MSPI9 RAM */
#else	/* MCU_TYPE_SERIES == MCU_RH850U2B6 */
	(U1)OFF,	/* MSPI *//* MSPI7 RAM */
	(U1)OFF,	/* MSPI *//* MSPI8 RAM */
	(U1)OFF,	/* MSPI *//* MSPI9 RAM */
#endif
	(U1)OFF,	/* MMCA *//* MMCA0 RAM A *//* 非使用のため非実装 */
	(U1)OFF,	/* MMCA *//* MMCA0 RAM B *//* 非使用のため非実装 */
	(U1)OFF,	/* Ethernet *//* TSNES0 RX data RAM *//* 非使用のため非実装 */
	(U1)OFF,	/* Ethernet *//* TSNES0 RX ctrl RAM *//* 非使用のため非実装 */
	(U1)OFF,	/* Ethernet *//* TSNES0 TX data RAM *//* 非使用のため非実装 */
	(U1)OFF,	/* Ethernet *//* TSNES0 TX ctrl RAM *//* 非使用のため非実装 */
	(U1)OFF,	/* Ethernet *//* TSNES0 TAS control list RAM *//* 非使用のため非実装 */
	(U1)OFF,	/* Ethernet *//* TSNES0 PSFP control list RAM *//* 非使用のため非実装 */
	(U1)ON,		/* DFE0 *//* Coefficient memory (CMEM) */
	(U1)ON		/* DFE1 *//* Coefficient memory (CMEM) */
};

static volatile U4 const cu4Ecc_Ecc7OffsetTable[ECC7_CHANNEL_NUM] = 
{
	u4ERRH_ECC_ADDR_OFFSET_RSCANFD0,												/* RS-CAN-FD0 *//* Message buffer RAM (MRAM) */
	u4ERRH_ECC_ADDR_OFFSET_RSCANFD0,												/* RS-CAN-FD0 *//* Acceptance filter list RAM (AFLRAM 0) */
	u4ERRH_ECC_ADDR_OFFSET_RSCANFD0  +  u4ERRH_ECC_ADDR_OFFSET_4BYTE,				/* RS-CAN-FD0 *//* Acceptance filter list RAM (AFLRAM 1) */
	u4ERRH_ECC_ADDR_OFFSET_RSCANFD0,												/* RS-CAN-FD0 *//* Pretended network filter list RAM (PFLRAM) */
	(U4)0U,																			/* FlexRay0 *//* Message RAM (MRAM) *//* 非使用のため非実装 */
	(U4)0U,																			/* FlexRay0 *//* Temporary buffer (TBFRAM A) *//* 非使用のため非実装 */
	(U4)0U,																			/* FlexRay0 *//* Temporary buffer (TBFRAM B) *//* 非使用のため非実装 */
	(U4)0U,																			/* GTM *//* MCS0_RAM0 *//* 非使用のため非実装 */
	(U4)0U,																			/* GTM *//* MCS0_RAM1 *//* 非使用のため非実装 */
	(U4)0U,																			/* GTM *//* MCS1_RAM0 *//* 非使用のため非実装 */
	(U4)0U,																			/* GTM *//* MCS1_RAM1 *//* 非使用のため非実装 */
	(U4)0U,																			/* GTM *//* MCS2_RAM0 *//* 非使用のため非実装 */
	(U4)0U,																			/* GTM *//* MCS2_RAM1 *//* 非使用のため非実装 */
	(U4)0U,																			/* GTM *//* MCS3_RAM0 *//* 非使用のため非実装 */
	(U4)0U,																			/* GTM *//* MCS3_RAM1 *//* 非使用のため非実装 */
	(U4)0U,																			/* GTM *//* MCS4_RAM0 *//* 非使用のため非実装 */
	(U4)0U,																			/* GTM *//* MCS4_RAM1 *//* 非使用のため非実装 */
	(U4)0U,																			/* GTM *//* MCS5_RAM0 *//* 非使用のため非実装 */
	(U4)0U,																			/* GTM *//* MCS5_RAM1 *//* 非使用のため非実装 */
	(U4)0U,																			/* GTM *//* MCS6_RAM0 *//* 非使用のため非実装 */
	(U4)0U,																			/* GTM *//* MCS6_RAM1 *//* 非使用のため非実装 */
	(U4)0U,																			/* GTM *//* FIFO0 RAM *//* 非使用のため非実装 */
	(U4)0U,																			/* GTM *//* FIFO1 RAM *//* 非使用のため非実装 */
	(U4)0U,																			/* GTM *//* FIFO2 RAM *//* 非使用のため非実装 */
	(U4)0U,																			/* GTM *//* DPLL RAM1A *//* 非使用のため非実装 */
	(U4)0U,																			/* GTM *//* DPLL RAM1B *//* 非使用のため非実装 */
	(U4)0U,																			/* GTM *//* DPLL RAM2 *//* 非使用のため非実装 */
	u4ERRH_ECC_ADDR_OFFSET_MSPI0,													/* MSPI *//* MSPI0 RAM */
	u4ERRH_ECC_ADDR_OFFSET_MSPI1,													/* MSPI *//* MSPI1 RAM */
	u4ERRH_ECC_ADDR_OFFSET_MSPI2,													/* MSPI *//* MSPI2 RAM */
	u4ERRH_ECC_ADDR_OFFSET_MSPI3,													/* MSPI *//* MSPI3 RAM */
	u4ERRH_ECC_ADDR_OFFSET_MSPI4,													/* MSPI *//* MSPI4 RAM */
	u4ERRH_ECC_ADDR_OFFSET_MSPI5,													/* MSPI *//* MSPI5 RAM */
	u4ERRH_ECC_ADDR_OFFSET_MSPI6,													/* MSPI *//* MSPI6 RAM */
	u4ERRH_ECC_ADDR_OFFSET_MSPI7,													/* MSPI *//* MSPI7 RAM */
	u4ERRH_ECC_ADDR_OFFSET_MSPI8,													/* MSPI *//* MSPI8 RAM */
	u4ERRH_ECC_ADDR_OFFSET_MSPI9,													/* MSPI *//* MSPI9 RAM */
	(U4)0U,																			/* MMCA *//* MMCA0 RAM A *//* 非使用のため非実装 */
	(U4)0U,																			/* MMCA *//* MMCA0 RAM B *//* 非使用のため非実装 */
	(U4)0U,																			/* Ethernet *//* TSNES0 RX data RAM *//* 非使用のため非実装 */
	(U4)0U,																			/* Ethernet *//* TSNES0 RX ctrl RAM *//* 非使用のため非実装 */
	(U4)0U,																			/* Ethernet *//* TSNES0 TX data RAM *//* 非使用のため非実装 */
	(U4)0U,																			/* Ethernet *//* TSNES0 TX ctrl RAM *//* 非使用のため非実装 */
	(U4)0U,																			/* Ethernet *//* TSNES0 TAS control list RAM *//* 非使用のため非実装 */
	(U4)0U,																			/* Ethernet *//* TSNES0 PSFP control list RAM *//* 非使用のため非実装 */
	u4ERRH_ECC_ADDR_OFFSET_DFE0CM,													/* DFE0 *//* Coefficient memory (CMEM) */
	u4ERRH_ECC_ADDR_OFFSET_DFE1CM													/* DFE1 *//* Coefficient memory (CMEM) */
};

static volatile U4 const cu4Ecc_Ecc6OffsetTable[ECC6_CHANNEL_NUM] = 
{
	(U4)u4ERRH_ECC_ADDR_OFFSET_DFE0DM0,												/* DFE0 *//* Data memory (DMEM0) */
	(U4)u4ERRH_ECC_ADDR_OFFSET_DFE0DM1,												/* DFE0 *//* Data memory (DMEM1) */
	(U4)u4ERRH_ECC_ADDR_OFFSET_DFE1DM0,												/* DFE1 *//* Data memory (DMEM0) */
	(U4)u4ERRH_ECC_ADDR_OFFSET_DFE1DM1												/* DFE1 *//* Data memory (DMEM1) */
};

static volatile const U1 cu1ErrH_Ecc_EcccntATstctlSetEnTable[A_CHANNEL_NUM] = {
			(U1)ON,		/* ECCCNT_A_CCIB0CL0 */
			(U1)ON,		/* ECCCNT_A_CCIB1CL0 */
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
			(U1)ON,		/* ECCCNT_A_CCIB0CL1 */
			(U1)ON,		/* ECCCNT_A_CCIB1CL1 */
#endif
			(U1)ON,		/* ECCCNT_SA_PE0CL0 */
			(U1)ON,		/* ECCCNT_A_GCFU0CL0 */
			(U1)ON,		/* ECCCNT_SA_PE1CL0 */
			(U1)ON,		/* ECCCNT_A_GCFU1CL0 */
#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM > MCU_DUALCORE ) )	/* U2B10かつ3コア構成以上 */
			(U1)ON,		/* ECCCNT_SA_PE2CL1 */
			(U1)ON,		/* ECCCNT_A_GCFU2CL1 */
#endif
			(U1)ON,		/* ECCCNT_A_X2VCL0 */
#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM > MCU_DUALCORE ) )	/* U2B10かつ3コア構成以上 */
			(U1)ON,		/* ECCCNT_A_X2VCL1 */
#endif
			(U1)ON,		/* ECCCNT_A_BARR */
			(U1)ON,		/* ECCCNT_A_IPIR */
			(U1)ON,		/* ECCCNT_A_TPTM */
			(U1)ON,		/* ECCCNT_A_CRAM */
			(U1)OFF,	/* ECCCNT_A_SG0 */
			(U1)ON,		/* ECCCNT_A_SX2PV */
			(U1)ON,		/* ECCCNT_A_SX2FX */
			(U1)ON,		/* ECCCNT_A_FX2SX */
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
			(U1)ON,		/* ECCCNT_A_EX2FX */
			(U1)ON,		/* ECCCNT_A_GCFUE */
#endif
			(U1)ON,		/* ECCCNT_A_GCFUF */
			(U1)ON,		/* ECCCNT_A_SX2MB */
			(U1)OFF,	/* ECCCNT_A_V2A1 */
			(U1)OFF,	/* ECCCNT_A_V2A2 */
			(U1)OFF,	/* ECCCNT_A_V2A3 */
			(U1)OFF,	/* ECCCNT_A_V2A4 */
			(U1)OFF,	/* ECCCNT_A_V2A5 */
			(U1)OFF,	/* ECCCNT_A_V2A6 */
			(U1)OFF,	/* ECCCNT_A_V2A7 */
			(U1)OFF,	/* ECCCNT_A_V2A8 */
			(U1)OFF,	/* ECCCNT_A_V2A9 */
			(U1)OFF,	/* ECCCNT_A_V2A10 */
			(U1)OFF		/* ECCCNT_A_V2A11 */
};

#pragma ghs section rodata=default

/*==============================================================================================*/
/* variables																					*/
/*==============================================================================================*/
#pragma ghs section bss=".ERRH_BSS_VAR_NO_INIT"
static				U2		s_u2ErrH_Ecc_RegCheckNum;			/* レジスタ診断番号 */ /* 干渉対策のため、ErrH_Ecc_CheckReg_ASIL()のみからライトすること */
static	volatile	U1		s_u1ErrH_Ecc_RegCheckStatus;		/* レジスタ診断ステータス */ /* 干渉対策のため、ErrH_Ecc_CheckReg_ASIL()のみからライトすること */
static				U1		s_u1ErrH_Ecc_DisableRefreshEccReg;	/* ECCレジスタリフレッシュ無効化 */ /* 干渉対策のため、ErrH_Ecc_StopEccEdc()のみからライトすること */
#pragma ghs section bss=default

/*==============================================================================================*/
/* functions																					*/
/*==============================================================================================*/
#pragma ghs section text=".ERRH_TEXT_CODE"
/*----------------------------------------------------------------------------------------------*/
/* API Functions																				*/
/*----------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------*/
/*	ECC 1bit Error Clear																		*/
/*	return		: none																			*/
/*	parameters	: ModuleNumber																	*/
/*----------------------------------------------------------------------------------------------*/
void	ErrH_Ecc_ClearEcc1bitErr( U1 t_u1ModuleNum )
{
	/* モジュール番号に変更があった場合は、判定値を見直すこと */
	if ( t_u1ModuleNum < u1ERRH_ECC_DTP_LRAM_ADDR )
	{
		if ( t_u1ModuleNum < u1ERRH_ECC_DTS )
		{
			ErrH_Ecc_ClearEcc1bitErrRomRam( t_u1ModuleNum );
		}
		else
		{
			ErrH_Ecc_ClearEcc1bitErrPeripheral( t_u1ModuleNum );
		}
	}
	else
	{
		ErrH_Ecc_ClearEcc1bitErrDtpAddr( t_u1ModuleNum );
		/*	 Data Transfer PathのDataは自動訂正可能なため何もしない	*/
	}
}

/*----------------------------------------------------------------------------------------------*/
/*	ECC Fatal Error Clear																		*/
/*	return		: none																			*/
/*	parameters	: ModuleNumber																	*/
/*----------------------------------------------------------------------------------------------*/
void	ErrH_Ecc_ClearEccFatalErr( U1 t_u1ModuleNum )
{
	/* モジュール番号に変更があった場合は、判定値を見直すこと */
	if ( t_u1ModuleNum < u1ERRH_ECC_DTP_LRAM_ADDR )
	{
		if ( t_u1ModuleNum < u1ERRH_ECC_DTS )
		{
			ErrH_Ecc_ClearEccFatalErrRomRam( t_u1ModuleNum );
		}
		else
		{
			ErrH_Ecc_ClearEccFatalErrPeripheral( t_u1ModuleNum );
		}
	}
	else
	{
		if ( t_u1ModuleNum < u1ERRH_ECC_DTP_LRAM_DATA )
		{
			ErrH_Ecc_ClearEccFatalErrDtpAddr( t_u1ModuleNum );
		}
		else
		{
			ErrH_Ecc_ClearEccFatalErrDtpData( t_u1ModuleNum );
		}
	}
}

/*----------------------------------------------------------------------------------------------*/
/*	ECC 1bit Error Status Get																	*/
/*	return		: ErrorStatus																	*/
/*	parameters	: ModuleNumber																	*/
/*----------------------------------------------------------------------------------------------*/
U1		ErrH_Ecc_GetEcc1bitErrStatus( U1 t_u1ModuleNum )
{
	volatile Reg_Ecc_HbnEccType*			t_pstReg_HbnEcc;
	volatile Reg_Ecc_BeccCap_V2AnType*		t_pstReg_V2an;
	U1										t_u1ErrorStatus;

	t_u1ErrorStatus = u1ERRH_ECC_ERR_NOTDETECT;

	switch( t_u1ModuleNum )
	{
		case u1ERRH_ECC_LRAM_LRPE0:
			t_u1ErrorStatus = (U1)( REG_ECC_MECCCAP_LR_PE0CL0.unLR0_SERSTR.u4Data & u4ERRH_ECC_MASK_1BIT_LR_PE0 );
			break;

		case u1ERRH_ECC_LRAM_LRPE1:
			t_u1ErrorStatus = (U1)( REG_ECC_MECCCAP_LR_PE1CL0.unLR0_SERSTR.u4Data & u4ERRH_ECC_MASK_1BIT_LR_PE1 );
			break;

#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_TRIPLECORE ) )	/* U2B10かつ3コア構成 */
		case u1ERRH_ECC_LRAM_LRPE2:
			t_u1ErrorStatus = (U1)( REG_ECC_MECCCAP_LR_PE2CL1.unLR0_SERSTR.u4Data & u4ERRH_ECC_MASK_1BIT_LR_PE2 );
			break;
#endif

/*		case u1ERRH_ECC_LRAM_LRPE3: */
			/* 機能安全はCore3を使用しないため何もしない */

		case u1ERRH_ECC_LRAM_LRA:
			t_u1ErrorStatus = (U1)( REG_ECC_MECCCAP_LRA.unLR1_SERSTR.u4Data & u4ERRH_ECC_MASK_1BIT_LR_ALL );
			break;

		case u1ERRH_ECC_CRAM_CRAM:
			t_u1ErrorStatus = (U1)( REG_ECC_MECCCAP_CRAM.unCR_SERSTR.u4Data & u4ERRH_ECC_MASK_1BIT_CR );
			break;

		case u1ERRH_ECC_IC_ITPE0:
			t_u1ErrorStatus = (U1)( REG_ECC_MECCCAP_IT_PE0CL0.unIT_SERSTR.u4Data & (U4)ECC_MECCCAP_IT_PE0CL0_SERSTR_SEDF00 );
			break;

		case u1ERRH_ECC_IC_ITPE1:
			t_u1ErrorStatus = (U1)( REG_ECC_MECCCAP_IT_PE1CL0.unIT_SERSTR.u4Data & (U4)ECC_MECCCAP_IT_PE1CL0_SERSTR_SEDF00 );
			break;

#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_TRIPLECORE ) )	/* U2B10かつ3コア構成 */
		case u1ERRH_ECC_IC_ITPE2:
			t_u1ErrorStatus = (U1)( REG_ECC_MECCCAP_IT_PE2CL1.unIT_SERSTR.u4Data & (U4)ECC_MECCCAP_IT_PE2CL1_SERSTR_SEDF00 );
			break;
#endif

/*		case u1ERRH_ECC_IC_ITPE3: */
			/* 機能安全はCore3を使用しないため何もしない */

		case u1ERRH_ECC_IC_IDPE0:
			t_u1ErrorStatus = (U1)( REG_ECC_MECCCAP_ID_PE0CL0.unID_SERSTR.u4Data & (U4)ECC_MECCCAP_ID_PE0CL0_SERSTR_SEDF00 );
			break;

		case u1ERRH_ECC_IC_IDPE1:
			t_u1ErrorStatus = (U1)( REG_ECC_MECCCAP_ID_PE1CL0.unID_SERSTR.u4Data & (U4)ECC_MECCCAP_ID_PE1CL0_SERSTR_SEDF00 );
			break;

#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_TRIPLECORE ) )	/* U2B10かつ3コア構成 */
		case u1ERRH_ECC_IC_IDPE2:
			t_u1ErrorStatus = (U1)( REG_ECC_MECCCAP_ID_PE2CL1.unID_SERSTR.u4Data & (U4)ECC_MECCCAP_ID_PE2CL1_SERSTR_SEDF00 );
			break;
#endif

/*		case u1ERRH_ECC_IC_IDPE3: */
			/* 機能安全はCore3を使用しないため何もしない */

		case u1ERRH_ECC_DTP_LRAM_ADDR:
			if( ( REG_ECC_BECCCAP_LRAM.unLR_BUSASERSTR.u4Data & u4ERRH_ECC_MASK_1BIT_DTP_LRAM_ADDR ) != (U4)0U )
			{
				t_u1ErrorStatus = u1ERRH_ECC_ERR_1BITDETECT;
			}
			break;

		case u1ERRH_ECC_DTP_CRAM_ADDR:
			if( ( REG_ECC_BECCCAP_CRAM.unCR_BUSASERSTR.u4Data & u4ERRH_ECC_MASK_1BIT_DTP_CRAM_ADDR ) != (U4)0U )
			{
				t_u1ErrorStatus = u1ERRH_ECC_ERR_1BITDETECT;
			}
			break;

		case u1ERRH_ECC_DTP_CFL_ADDR:
			if( ( REG_ECC_BECCCAP_CFL.unCF_BUSASERSTR.u4Data & u4ERRH_ECC_MASK_1BIT_DTP_CFL_ADDR ) != (U4)0U )
			{
				t_u1ErrorStatus = u1ERRH_ECC_ERR_1BITDETECT;
			}
			break;

		case u1ERRH_ECC_DTP_PERI_ADDR:
			if( ( REG_ECC_BECCCAP_PERI.unPH_BUSASERSTR.u4Data & u4ERRH_ECC_MASK_1BIT_DTP_PERI_ADDR ) != (U4)0U )
			{
				t_u1ErrorStatus = u1ERRH_ECC_ERR_1BITDETECT;
			}
			break;

		case u1ERRH_ECC_DTP_EMU_ADDR:
			if( ( REG_ECC_BECCCAP_EMU.unEM_BUSASERSTR.u4Data & u4ERRH_ECC_MASK_1BIT_DTP_EMU_ADDR ) != (U4)0U )
			{
				t_u1ErrorStatus = u1ERRH_ECC_ERR_1BITDETECT;
			}
			break;

#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
		case u1ERRH_ECC_DTP_HB90MECC_ADDR:
		case u1ERRH_ECC_DTP_HB90SECC_ADDR:
#endif
		case u1ERRH_ECC_DTP_HB92MECC_ADDR:
		case u1ERRH_ECC_DTP_HB92SECC_ADDR:
		case u1ERRH_ECC_DTP_HB94SECC_ADDR:
		case u1ERRH_ECC_DTP_HB97MECC_ADDR:
		case u1ERRH_ECC_DTP_HB98MECC_ADDR:
#if ( MCU_TYPE_SERIES == MCU_RH850U2B6)
		case u1ERRH_ECC_DTP_HB911MECC_ADDR:
		case u1ERRH_ECC_DTP_HB912MECC_ADDR:
#endif
			t_pstReg_HbnEcc = (volatile Reg_Ecc_HbnEccType*)pcstReg_HbnEcc[t_u1ModuleNum - u1ERRH_ECC_HBNECC_ADDR_OFFSET];
			if( ( t_pstReg_HbnEcc->unHBEC1STERSTR.u4Data & (U4)ECC_HBNECC_HBEC1STERSTR_AECSEDF0 ) != (U4)0U )
			{
				t_u1ErrorStatus = u1ERRH_ECC_ERR_1BITDETECT;
			}
			break;

		case u1ERRH_ECC_DTP_V2A1_ADDR:
		case u1ERRH_ECC_DTP_V2A2_ADDR:
		case u1ERRH_ECC_DTP_V2A3_ADDR:
		case u1ERRH_ECC_DTP_V2A4_ADDR:
		case u1ERRH_ECC_DTP_V2A5_ADDR:
		case u1ERRH_ECC_DTP_V2A6_ADDR:
		case u1ERRH_ECC_DTP_V2A7_ADDR:
		case u1ERRH_ECC_DTP_V2A8_ADDR:
		case u1ERRH_ECC_DTP_V2A9_ADDR:
		case u1ERRH_ECC_DTP_V2A10_ADDR:
		case u1ERRH_ECC_DTP_V2A11_ADDR:
			t_pstReg_V2an = (volatile Reg_Ecc_BeccCap_V2AnType*)pcstReg_V2an[t_u1ModuleNum - u1ERRH_ECC_V2AN_ADDR_OFFSET];
			t_u1ErrorStatus = (U1)( t_pstReg_V2an->unPHC_BUSASERSTR.u4Data & (U4)ECC_BECCCAP_V2AN_BUSASERSTR_ASEDF00 );
			break;

/*		case u1ERRH_ECC_DF: */
			/* 機能安全のDFのECC機能は非使用のため何もしない */
/*			break; */

/*		case u1ERRH_ECC_PR32_E7FR00: */
/*		case u1ERRH_ECC_PR32_E7FR01: */
/*		case u1ERRH_ECC_PR32_E7FR02: */
			/* FlexRayは非使用のため何もしない */
/*			break; */

/*		case u1ERRH_ECC_PR32_E7GT00: */
/*		case u1ERRH_ECC_PR32_E7GT01: */
/*		case u1ERRH_ECC_PR32_E7GT10: */
/*		case u1ERRH_ECC_PR32_E7GT11: */
/*		case u1ERRH_ECC_PR32_E7GT20: */
/*		case u1ERRH_ECC_PR32_E7GT21: */
/*		case u1ERRH_ECC_PR32_E7GT30: */
/*		case u1ERRH_ECC_PR32_E7GT31: */
/*		case u1ERRH_ECC_PR32_E7GT40: */
/*		case u1ERRH_ECC_PR32_E7GT41: */
/*		case u1ERRH_ECC_PR32_E7GT50: */
/*		case u1ERRH_ECC_PR32_E7GT51: */
/*		case u1ERRH_ECC_PR32_E7GT60: */
/*		case u1ERRH_ECC_PR32_E7GT61: */
/*		case u1ERRH_ECC_PR32_E7GT100: */
/*		case u1ERRH_ECC_PR32_E7GT101: */
/*		case u1ERRH_ECC_PR32_E7GT102: */
/*		case u1ERRH_ECC_PR32_E7GT110: */
/*		case u1ERRH_ECC_PR32_E7GT111: */
/*		case u1ERRH_ECC_PR32_E7GT112: */
			/* GTMは非使用のため何もしない */
/*			break; */

/*		case u1ERRH_ECC_PR32_E7MM00: */
/*		case u1ERRH_ECC_PR32_E7MM01: */
			/* MMCAは非使用のため何もしない */
/*			break; */

/*		case u1ERRH_ECC_PR32_E7ES00: */
/*		case u1ERRH_ECC_PR32_E7ES01: */
/*		case u1ERRH_ECC_PR32_E7ES02: */
/*		case u1ERRH_ECC_PR32_E7ES03: */
/*		case u1ERRH_ECC_PR32_E7ES04: */
/*		case u1ERRH_ECC_PR32_E7ES05: */
			/* Ethernetは非使用のため何もしない */
/*			break; */

/*		case u1ERRH_ECC_DTP_DFPFNT_ADDR: */
			/* DFPは非使用のため何もしない */
/*			break; */

/*		case u1ERRH_ECC_CF: */
/*		case u1ERRH_ECC_DTS: */
/*		case u1ERRH_ECC_DMDE_DMDE0: */
/*		case u1ERRH_ECC_DMDE_DMDE1: */
/*		case u1ERRH_ECC_DMDA_DMDA0: */
/*		case u1ERRH_ECC_DMDA_DMDA1: */
/*		case u1ERRH_ECC_PR32_E7RC01: */
/*		case u1ERRH_ECC_PR32_E7RC02: */
/*		case u1ERRH_ECC_PR32_E7RC03: */
/*		case u1ERRH_ECC_PR32_E7RC04: */
/*		case u1ERRH_ECC_PR32_E7MS00: */
/*		case u1ERRH_ECC_PR32_E7MS01: */
/*		case u1ERRH_ECC_PR32_E7MS02: */
/*		case u1ERRH_ECC_PR32_E7MS03: */
/*		case u1ERRH_ECC_PR32_E7MS04: */
/*		case u1ERRH_ECC_PR32_E7MS05: */
/*		case u1ERRH_ECC_PR32_E7MS06: */
/*		case u1ERRH_ECC_PR32_E7MS07: */
/*		case u1ERRH_ECC_PR32_E7MS08: */
/*		case u1ERRH_ECC_PR32_E7MS09: */
/*		case u1ERRH_ECC_PR32_E7DF00: */
/*		case u1ERRH_ECC_PR32_E7DF10: */
/*		case u1ERRH_ECC_PR16_E6DF00: */
/*		case u1ERRH_ECC_PR16_E6DF01: */
/*		case u1ERRH_ECC_PR16_E6DF10: */
/*		case u1ERRH_ECC_PR16_E6DF11: */
/*		case u1ERRH_ECC_DTP_LRAM_DATA: */
/*		case u1ERRH_ECC_DTP_CRAM_DATA: */
/*		case u1ERRH_ECC_DTP_PERI_DATA: */
/*		case u1ERRH_ECC_DTP_DMDT_DATA: */
/*		case u1ERRH_ECC_DTP_EMU_DATA: */
/*		case u1ERRH_ECC_DTP_HB90MECC_DATA: */
/*		case u1ERRH_ECC_DTP_HB90SECC_DATA: */
/*		case u1ERRH_ECC_DTP_HB92MECC_DATA: */
/*		case u1ERRH_ECC_DTP_HB92SECC_DATA: */
/*		case u1ERRH_ECC_DTP_HB94SECC_DATA: */
/*		case u1ERRH_ECC_DTP_HB97MECC_DATA: */
/*		case u1ERRH_ECC_DTP_HB98MECC_DATA: */
/*		case u1ERRH_ECC_DTP_HB911MECC_DATA: */
/*		case u1ERRH_ECC_DTP_HB912MECC_DATA: */
/*		case u1ERRH_ECC_DTP_V2A1_DATA: */
/*		case u1ERRH_ECC_DTP_V2A2_DATA: */
/*		case u1ERRH_ECC_DTP_V2A3_DATA: */
/*		case u1ERRH_ECC_DTP_V2A4_DATA: */
/*		case u1ERRH_ECC_DTP_V2A5_DATA: */
/*		case u1ERRH_ECC_DTP_V2A6_DATA: */
/*		case u1ERRH_ECC_DTP_V2A7_DATA: */
/*		case u1ERRH_ECC_DTP_V2A8_DATA: */
/*		case u1ERRH_ECC_DTP_V2A9_DATA: */
/*		case u1ERRH_ECC_DTP_V2A10_DATA: */
/*		case u1ERRH_ECC_DTP_V2A11_DATA: */
/*		case u1ERRH_ECC_DTP_DFPROM_DATA: */
/*		case u1ERRH_ECC_DTP_DFPSYS_DATA: */
/*		case u1ERRH_ECC_DTP_DFPFNT_DATA: */
			/* 自動訂正可能であるため何もしない */
/*			break; */

		default:
			/* 何もしない */
			break;
	}

	return( t_u1ErrorStatus );
}

/*----------------------------------------------------------------------------------------------*/
/*	ECC Fatal Error Status Get																	*/
/*	return		: ErrorStatus																	*/
/*	parameters	: ModuleNumber																	*/
/*----------------------------------------------------------------------------------------------*/
U1		ErrH_Ecc_GetEccFatalErrStatus( U1 t_u1ModuleNum )
{
	U1										t_u1ErrorStatus;

	/* モジュール番号に変更があった場合は、判定値を見直すこと */
	if ( t_u1ModuleNum < u1ERRH_ECC_DTP_LRAM_ADDR )
	{
		if ( t_u1ModuleNum < u1ERRH_ECC_DTS )
		{
			t_u1ErrorStatus = ErrH_Ecc_GetEccFatalErrStsRomRam( t_u1ModuleNum );
		}
		else
		{
			t_u1ErrorStatus = ErrH_Ecc_GetEccFatalErrStsPeripheral( t_u1ModuleNum );
		}
	}
	else
	{
		if ( t_u1ModuleNum < u1ERRH_ECC_DTP_LRAM_DATA )
		{
			t_u1ErrorStatus = ErrH_Ecc_GetEccFatalErrStsDtpAddr( t_u1ModuleNum );
		}
		else
		{
			t_u1ErrorStatus = ErrH_Ecc_GetEccFatalErrStsDtpData( t_u1ModuleNum );
		}
	}

	return( t_u1ErrorStatus );
}

/*----------------------------------------------------------------------------------------------*/
/*	ECC Overflow Status Get																		*/
/*	return		: OverflowStatus																*/
/*	parameters	: ModuleNumber																	*/
/*----------------------------------------------------------------------------------------------*/
U1		ErrH_Ecc_GetEccOvfStatus( U1 t_u1ModuleNum )
{
	volatile Reg_Ecc_Ecc7Type*				t_pstReg_Ecc7;
	volatile Reg_Ecc_Ecc6Type*				t_pstReg_Ecc6;
	U1										t_OverflowStatus;

	t_OverflowStatus = u1ERRH_ECC_ERR_NOTDETECT;

	switch( t_u1ModuleNum )
	{
		case u1ERRH_ECC_CF:
			t_OverflowStatus = (U1)( REG_ECC_MECCCAP_CFL.unCF_OVFSTR.u4Data
								   & ( (U4)ECC_MECCCAP_CFL_CF_OVFSTR_OVF1 + (U4)ECC_MECCCAP_CFL_CF_OVFSTR_OVF0 ) );
			break;

/*		case u1ERRH_ECC_DF: */
			/* 機能安全のDFのECC機能は非使用のため何もしない */
/*			break; */

		case u1ERRH_ECC_LRAM_LRPE0:
			t_OverflowStatus = (U1)( REG_ECC_MECCCAP_LR_PE0CL0.unLR0_OVFSTR.u4Data
								   & ( (U4)ECC_MECCCAP_LR_PE0CL0_OVFSTR_1 + (U4)ECC_MECCCAP_LR_PE0CL0_OVFSTR_0 ) );
			break;

		case u1ERRH_ECC_LRAM_LRPE1:
			t_OverflowStatus = (U1)( REG_ECC_MECCCAP_LR_PE1CL0.unLR0_OVFSTR.u4Data
								   & ( (U4)ECC_MECCCAP_LR_PE1CL0_OVFSTR_1 + (U4)ECC_MECCCAP_LR_PE1CL0_OVFSTR_0 ) );
			break;

#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_TRIPLECORE ) )	/* U2B10かつ3コア構成 */
		case u1ERRH_ECC_LRAM_LRPE2:
			t_OverflowStatus = (U1)( REG_ECC_MECCCAP_LR_PE2CL1.unLR0_OVFSTR.u4Data
								   & ( (U4)ECC_MECCCAP_LR_PE2CL1_OVFSTR_1 + (U4)ECC_MECCCAP_LR_PE2CL1_OVFSTR_0 ) );
			break;
#endif

/*		case u1ERRH_ECC_LRAM_LRPE3: */
			/* 機能安全はCore3を使用しないため何もしない */

		case u1ERRH_ECC_LRAM_LRA:
			t_OverflowStatus = (U1)( REG_ECC_MECCCAP_LRA.unLR1_OVFSTR.u4Data
								   & ( (U4)ECC_MECCCAP_LRA_LR1_OVFSTR_1 + (U4)ECC_MECCCAP_LRA_LR1_OVFSTR_0 ) );
			break;

		case u1ERRH_ECC_CRAM_CRAM:
			t_OverflowStatus = (U1)( REG_ECC_MECCCAP_CRAM.unCR_OVFSTR.u4Data
								   & ( (U4)ECC_MECCCAP_CRAM_CR_OVFSTR_1 + (U4)ECC_MECCCAP_CRAM_CR_OVFSTR_0 ) );
			break;

		case u1ERRH_ECC_IC_ITPE0:
			t_OverflowStatus = (U1)( REG_ECC_MECCCAP_IT_PE0CL0.unIT_OVFSTR.u4Data
								   & ( (U4)ECC_MECCCAP_IT_PE0CL0_OVFSTR_1 + (U4)ECC_MECCCAP_IT_PE0CL0_OVFSTR_0 ) );
			break;

		case u1ERRH_ECC_IC_ITPE1:
			t_OverflowStatus = (U1)( REG_ECC_MECCCAP_IT_PE1CL0.unIT_OVFSTR.u4Data
								   & ( (U4)ECC_MECCCAP_IT_PE1CL0_OVFSTR_1 + (U4)ECC_MECCCAP_IT_PE1CL0_OVFSTR_0 ) );
			break;

#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_TRIPLECORE ) )	/* U2B10かつ3コア構成 */
		case u1ERRH_ECC_IC_ITPE2:
			t_OverflowStatus = (U1)( REG_ECC_MECCCAP_IT_PE2CL1.unIT_OVFSTR.u4Data
								   & ( (U4)ECC_MECCCAP_IT_PE2CL1_OVFSTR_1 + (U4)ECC_MECCCAP_IT_PE2CL1_OVFSTR_0 ) );
			break;
#endif

/*		case u1ERRH_ECC_LIC_ITPE3: */
			/* 機能安全はCore3を使用しないため何もしない */

		case u1ERRH_ECC_IC_IDPE0:
			t_OverflowStatus = (U1)( REG_ECC_MECCCAP_ID_PE0CL0.unID_OVFSTR.u4Data
								   & ( (U4)ECC_MECCCAP_ID_PE0CL0_OVFSTR_1 + (U4)ECC_MECCCAP_ID_PE0CL0_OVFSTR_0 ) );
			break;

		case u1ERRH_ECC_IC_IDPE1:
			t_OverflowStatus = (U1)( REG_ECC_MECCCAP_ID_PE1CL0.unID_OVFSTR.u4Data
								   & ( (U4)ECC_MECCCAP_ID_PE1CL0_OVFSTR_1 + (U4)ECC_MECCCAP_ID_PE1CL0_OVFSTR_0 ) );
			break;

#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_TRIPLECORE ) )	/* U2B10かつ3コア構成 */
		case u1ERRH_ECC_IC_IDPE2:
			t_OverflowStatus = (U1)( REG_ECC_MECCCAP_ID_PE2CL1.unID_OVFSTR.u4Data
								   & ( (U4)ECC_MECCCAP_ID_PE2CL1_OVFSTR_1 + (U4)ECC_MECCCAP_ID_PE2CL1_OVFSTR_0 ) );
			break;
#endif

/*		case u1ERRH_ECC_LIC_IDPE3: */
			/* 機能安全はCore3を使用しないため何もしない */

		case u1ERRH_ECC_DTS:
			t_OverflowStatus = (U1)( REG_ECC_MECCCAP_DTS.unDR_OVFSTR.u4Data & (U4)ECC_MECCCAP_DTS_DR_OVFSTR_SERROVF0 );
			break;

		case u1ERRH_ECC_DMDE_DMDE0:
			t_OverflowStatus = (U1)( REG_ECC_MECCCAP_DMDE0.unDE_OVFSTR.u4Data & (U4)ECC_MECCCAP_DMDE0_DE_OVFSTR_SERROVF0 );
			break;

#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
		case u1ERRH_ECC_DMDE_DMDE1:
			t_OverflowStatus = (U1)( REG_ECC_MECCCAP_DMDE1.unDE_OVFSTR.u4Data & (U4)ECC_MECCCAP_DMDE1_DE_OVFSTR_SERROVF0 );
			break;
#endif

		case u1ERRH_ECC_DMDA_DMDA0:
			t_OverflowStatus = (U1)( REG_ECC_MECCCAP_DMDA0.unDA_OVFSTR.u4Data & (U4)ECC_MECCCAP_DMDA0_DA_OVFSTR_SERROVF0 );
			break;

#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
		case u1ERRH_ECC_DMDA_DMDA1:
			t_OverflowStatus = (U1)( REG_ECC_MECCCAP_DMDA1.unDA_OVFSTR.u4Data & (U4)ECC_MECCCAP_DMDA1_DA_OVFSTR_SERROVF0 );

			break;
#endif

		case u1ERRH_ECC_PR32_E7RC01:
		case u1ERRH_ECC_PR32_E7RC02:
		case u1ERRH_ECC_PR32_E7RC03:
		case u1ERRH_ECC_PR32_E7RC04:
		case u1ERRH_ECC_PR32_E7MS00:
		case u1ERRH_ECC_PR32_E7MS01:
		case u1ERRH_ECC_PR32_E7MS02:
		case u1ERRH_ECC_PR32_E7MS03:
		case u1ERRH_ECC_PR32_E7MS04:
		case u1ERRH_ECC_PR32_E7MS05:
		case u1ERRH_ECC_PR32_E7MS06:
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
		case u1ERRH_ECC_PR32_E7MS07:
		case u1ERRH_ECC_PR32_E7MS08:
		case u1ERRH_ECC_PR32_E7MS09:
#endif
		case u1ERRH_ECC_PR32_E7DF00:
		case u1ERRH_ECC_PR32_E7DF10:
			t_pstReg_Ecc7 = (volatile Reg_Ecc_Ecc7Type*)pcstReg_Ecc7[t_u1ModuleNum - u1ERRH_ECC_PR32_OFFSET];
			if( ( t_pstReg_Ecc7->unE710CTL.u2Data & (U2)ECC_ECC7_E710CTL_ECOVFF ) != (U2)0U )
			{
				t_OverflowStatus = u1ERRH_ECC_ERR_OVF;
			}
			break;

/*		case u1ERRH_ECC_PR32_E7FR00: */
/*		case u1ERRH_ECC_PR32_E7FR01: */
/*		case u1ERRH_ECC_PR32_E7FR02: */
			/* FlexRayは非使用のため何もしない */
/*			break; */

/*		case u1ERRH_ECC_PR32_E7GT00: */
/*		case u1ERRH_ECC_PR32_E7GT01: */
/*		case u1ERRH_ECC_PR32_E7GT10: */
/*		case u1ERRH_ECC_PR32_E7GT11: */
/*		case u1ERRH_ECC_PR32_E7GT20: */
/*		case u1ERRH_ECC_PR32_E7GT21: */
/*		case u1ERRH_ECC_PR32_E7GT30: */
/*		case u1ERRH_ECC_PR32_E7GT31: */
/*		case u1ERRH_ECC_PR32_E7GT40: */
/*		case u1ERRH_ECC_PR32_E7GT41: */
/*		case u1ERRH_ECC_PR32_E7GT50: */
/*		case u1ERRH_ECC_PR32_E7GT51: */
/*		case u1ERRH_ECC_PR32_E7GT60: */
/*		case u1ERRH_ECC_PR32_E7GT61: */
/*		case u1ERRH_ECC_PR32_E7GT100: */
/*		case u1ERRH_ECC_PR32_E7GT101: */
/*		case u1ERRH_ECC_PR32_E7GT102: */
/*		case u1ERRH_ECC_PR32_E7GT110: */
/*		case u1ERRH_ECC_PR32_E7GT111: */
/*		case u1ERRH_ECC_PR32_E7GT112: */
			/* GTMは非使用のため何もしない */
/*			break; */

/*		case u1ERRH_ECC_PR32_E7MM00: */
/*		case u1ERRH_ECC_PR32_E7MM01: */
			/* MMCAは非使用のため何もしない */
/*			break; */

/*		case u1ERRH_ECC_PR32_E7ES00: */
/*		case u1ERRH_ECC_PR32_E7ES01: */
/*		case u1ERRH_ECC_PR32_E7ES02: */
/*		case u1ERRH_ECC_PR32_E7ES03: */
/*		case u1ERRH_ECC_PR32_E7ES04: */
/*		case u1ERRH_ECC_PR32_E7ES05: */
			/* Ethernetは非使用のため何もしない */
/*			break; */

		case u1ERRH_ECC_PR16_E6DF00:
		case u1ERRH_ECC_PR16_E6DF01:
		case u1ERRH_ECC_PR16_E6DF10:
		case u1ERRH_ECC_PR16_E6DF11:
			t_pstReg_Ecc6 = (volatile Reg_Ecc_Ecc6Type*)pcstReg_Ecc6[t_u1ModuleNum - u1ERRH_ECC_PR16_OFFSET];
			if( ( t_pstReg_Ecc6->unE610CTL.u2Data & (U2)ECC_ECC6_E610CTL_ECOVFF ) != (U2)0U )
			{
				t_OverflowStatus = u1ERRH_ECC_ERR_OVF;
			}
			break;

/*		case u1ERRH_ECC_DTP_LRAM_ADDR: */
/*		case u1ERRH_ECC_DTP_CRAM_ADDR: */
/*		case u1ERRH_ECC_DTP_CFL_ADDR: */
/*		case u1ERRH_ECC_DTP_PERI_ADDR: */
/*		case u1ERRH_ECC_DTP_EMU_ADDR: */
/*		case u1ERRH_ECC_DTP_HB90MECC_ADDR: */
/*		case u1ERRH_ECC_DTP_HB90SECC_ADDR: */
/*		case u1ERRH_ECC_DTP_HB92MECC_ADDR: */
/*		case u1ERRH_ECC_DTP_HB92SECC_ADDR: */
/*		case u1ERRH_ECC_DTP_HB94MECC_ADDR: */
/*		case u1ERRH_ECC_DTP_HB97MECC_ADDR: */
/*		case u1ERRH_ECC_DTP_HB98MECC_ADDR: */
/*		case u1ERRH_ECC_DTP_HB911MECC_ADDR: */
/*		case u1ERRH_ECC_DTP_HB912MECC_ADDR: */
/*		case u1ERRH_ECC_DTP_V2A1_ADDR: */
/*		case u1ERRH_ECC_DTP_V2A2_ADDR: */
/*		case u1ERRH_ECC_DTP_V2A3_ADDR: */
/*		case u1ERRH_ECC_DTP_V2A4_ADDR: */
/*		case u1ERRH_ECC_DTP_V2A5_ADDR: */
/*		case u1ERRH_ECC_DTP_V2A6_ADDR: */
/*		case u1ERRH_ECC_DTP_V2A7_ADDR: */
/*		case u1ERRH_ECC_DTP_V2A8_ADDR: */
/*		case u1ERRH_ECC_DTP_V2A9_ADDR: */
/*		case u1ERRH_ECC_DTP_V2A10_ADDR: */
/*		case u1ERRH_ECC_DTP_V2A11_ADDR: */
/*		case u1ERRH_ECC_DTP_DFPFNT_ADDR: */
/*		case u1ERRH_ECC_DTP_LRAM_DATA: */
/*		case u1ERRH_ECC_DTP_CRAM_DATA: */
/*		case u1ERRH_ECC_DTP_PERI_DATA: */
/*		case u1ERRH_ECC_DTP_DMDT_DATA: */
/*		case u1ERRH_ECC_DTP_EMU_DATA: */
/*		case u1ERRH_ECC_DTP_HB90MECC_DATA: */
/*		case u1ERRH_ECC_DTP_HB90SECC_DATA: */
/*		case u1ERRH_ECC_DTP_HB92MECC_DATA: */
/*		case u1ERRH_ECC_DTP_HB92SECC_DATA: */
/*		case u1ERRH_ECC_DTP_HB94MECC_DATA: */
/*		case u1ERRH_ECC_DTP_HB97MECC_DATA: */
/*		case u1ERRH_ECC_DTP_HB98MECC_DATA: */
/*		case u1ERRH_ECC_DTP_HB911MECC_DATA: */
/*		case u1ERRH_ECC_DTP_HB912MECC_DATA: */
/*		case u1ERRH_ECC_DTP_V2A1_DATA: */
/*		case u1ERRH_ECC_DTP_V2A2_DATA: */
/*		case u1ERRH_ECC_DTP_V2A3_DATA: */
/*		case u1ERRH_ECC_DTP_V2A4_DATA: */
/*		case u1ERRH_ECC_DTP_V2A5_DATA: */
/*		case u1ERRH_ECC_DTP_V2A6_DATA: */
/*		case u1ERRH_ECC_DTP_V2A7_DATA: */
/*		case u1ERRH_ECC_DTP_V2A8_DATA: */
/*		case u1ERRH_ECC_DTP_V2A9_DATA: */
/*		case u1ERRH_ECC_DTP_V2A10_DATA: */
/*		case u1ERRH_ECC_DTP_V2A11_DATA: */
/*		case u1ERRH_ECC_DTP_DFPROM_DATA: */
/*		case u1ERRH_ECC_DTP_DFPSYS_DATA: */
/*		case u1ERRH_ECC_DTP_DFPSYS_DATA: */
		/* Data Transfer Pathはオーバフローエラーは存在しない */
/*			break;*/

		default:
			/* 何もしない */
			break;
	}

	return( t_OverflowStatus );
}

/*----------------------------------------------------------------------------------------------*/
/*	ECC 1bit Error Address Get																	*/
/*	return		: ErrorAddress																	*/
/*	parameters	: ModuleNumber, Address(Sync), ArrayNum											*/
/*----------------------------------------------------------------------------------------------*/
void	ErrH_Ecc_GetEcc1bitErrAddr( U1 t_u1ModuleNum, U4* t_pu4Address, U1 t_u1ArrayNum )
{
	S4										i;
	U1										t_u1LoopNum;

	switch( t_u1ModuleNum )
	{
/*		case u1ERRH_ECC_DF: */
			/* 機能安全のDFのECC機能は非使用のため何もしない */
/*			break; */

		case u1ERRH_ECC_LRAM_LRPE0:
			if( t_u1ArrayNum > u1ERRH_ECC_ADDR_BUFFNUM_LRAM )
			{
				t_u1LoopNum = u1ERRH_ECC_ADDR_BUFFNUM_LRAM;
			}
			else
			{
				t_u1LoopNum = t_u1ArrayNum;
			}

			for( i = (S4)0; i < (S4)t_u1LoopNum; i++ )
			{
				t_pu4Address[i] = (U4)( ( REG_ECC_MECCCAP_LR_PE0CL0.unLR0_nSEADR[i].u4Data & (U4)ECC_MECCCAP_LR_PE0CL0_SEADR_SEADR0 )
									  +   u4ERRH_ECC_ADDR_OFFSET_LRAM_PE0 );	/* qac 3383 : レジスタ値のレンジ内では、ラップアラウンドが発生しないことを確認済み。QAC結果は過剰警告 */
			}
			break;

		case u1ERRH_ECC_LRAM_LRPE1:
			if( t_u1ArrayNum > u1ERRH_ECC_ADDR_BUFFNUM_LRAM )
			{
				t_u1LoopNum = u1ERRH_ECC_ADDR_BUFFNUM_LRAM;
			}
			else
			{
				t_u1LoopNum = t_u1ArrayNum;
			}

			for( i = (S4)0; i < (S4)t_u1LoopNum; i++ )
			{
				t_pu4Address[i] = (U4)( ( REG_ECC_MECCCAP_LR_PE1CL0.unLR0_nSEADR[i].u4Data & (U4)ECC_MECCCAP_LR_PE1CL0_SEADR_SEADR0 )
									  +   u4ERRH_ECC_ADDR_OFFSET_LRAM_PE1 );	/* qac 3383 : レジスタ値のレンジ内では、ラップアラウンドが発生しないことを確認済み。QAC結果は過剰警告 */
			}
			break;

#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_TRIPLECORE ) )	/* U2B10かつ3コア構成 */
		case u1ERRH_ECC_LRAM_LRPE2:
			if( t_u1ArrayNum > u1ERRH_ECC_ADDR_BUFFNUM_LRAM )
			{
				t_u1LoopNum = u1ERRH_ECC_ADDR_BUFFNUM_LRAM;
			}
			else
			{
				t_u1LoopNum = t_u1ArrayNum;
			}

			for( i = (S4)0; i < (S4)t_u1LoopNum; i++ )
			{
				t_pu4Address[i] = (U4)( ( REG_ECC_MECCCAP_LR_PE2CL1.unLR0_nSEADR[i].u4Data & (U4)ECC_MECCCAP_LR_PE2CL1_SEADR_SEADR0 )
									  +   u4ERRH_ECC_ADDR_OFFSET_LRAM_PE2 );	/* qac 3383 : レジスタ値のレンジ内では、ラップアラウンドが発生しないことを確認済み。QAC結果は過剰警告 */
			}
			break;
#endif

/*		case u1ERRH_ECC_LRAM_LRPE3: */
			/* 機能安全はCore3を使用しないため何もしない */

		case u1ERRH_ECC_LRAM_LRA:
			if( t_u1ArrayNum > u1ERRH_ECC_ADDR_BUFFNUM_LRAM )
			{
				t_u1LoopNum = u1ERRH_ECC_ADDR_BUFFNUM_LRAM;
			}
			else
			{
				t_u1LoopNum = t_u1ArrayNum;
			}

			for( i = (S4)0; i < (S4)t_u1LoopNum; i++ )
			{
				t_pu4Address[i] = (U4)( ( REG_ECC_MECCCAP_LRA.unLR1_nSEADR[i].u4Data & (U4)ECC_MECCCAP_LRA_LR1_SEADR_SEADR0 )
									  +   u4ERRH_ECC_ADDR_OFFSET_LRAM_LRA );	/* qac 3383 : レジスタ値のレンジ内では、ラップアラウンドが発生しないことを確認済み。QAC結果は過剰警告 */
			}
			break;

		case u1ERRH_ECC_CRAM_CRAM:
			if( t_u1ArrayNum > u1ERRH_ECC_ADDR_BUFFNUM_CRAM )
			{
				t_u1LoopNum = u1ERRH_ECC_ADDR_BUFFNUM_CRAM;
			}
			else
			{
				t_u1LoopNum = t_u1ArrayNum;
			}

			for( i = (S4)0; i < (S4)t_u1LoopNum; i++ )
			{
				t_pu4Address[i] = (U4)( ( REG_ECC_MECCCAP_CRAM.unCR_nSEADR[i].u4Data & (U4)ECC_MECCCAP_CRAM_CR_SEADR_SEADR0 )
									  +   u4ERRH_ECC_ADDR_OFFSET_CRAM );	/* qac 3383 : レジスタ値のレンジ内では、ラップアラウンドが発生しないことを確認済み。QAC結果は過剰警告 */
			}
			break;

		case u1ERRH_ECC_IC_ITPE0:
			*t_pu4Address = (U4)( ( REG_ECC_MECCCAP_IT_PE0CL0.unIT_00SEADR.u4Data & (U4)ECC_MECCCAP_IT_PE0CL0_SEADR_SEADR0 )
								 >> u1ERRH_ECC_ADDR_RSHIFT_5BIT );
			break;

		case u1ERRH_ECC_IC_ITPE1:
			*t_pu4Address = (U4)( ( REG_ECC_MECCCAP_IT_PE1CL0.unIT_00SEADR.u4Data & (U4)ECC_MECCCAP_IT_PE1CL0_SEADR_SEADR0 )
								 >> u1ERRH_ECC_ADDR_RSHIFT_5BIT );
			break;

#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_TRIPLECORE ) )	/* U2B10かつ3コア構成 */
		case u1ERRH_ECC_IC_ITPE2:
			*t_pu4Address = (U4)( ( REG_ECC_MECCCAP_IT_PE2CL1.unIT_00SEADR.u4Data & (U4)ECC_MECCCAP_IT_PE2CL1_SEADR_SEADR0 )
								 >> u1ERRH_ECC_ADDR_RSHIFT_5BIT );
			break;
#endif

/*		case u1ERRH_ECC_IC_ITPE3: */
			/* 機能安全はCore3を使用しないため何もしない */

		case u1ERRH_ECC_IC_IDPE0:
			*t_pu4Address = (U4)( ( REG_ECC_MECCCAP_ID_PE0CL0.unID_00SEADR.u4Data & (U4)ECC_MECCCAP_ID_PE0CL0_SEADR_SEADR0 )
								 >> u1ERRH_ECC_ADDR_RSHIFT_3BIT );
			break;

		case u1ERRH_ECC_IC_IDPE1:
			*t_pu4Address = (U4)( ( REG_ECC_MECCCAP_ID_PE1CL0.unID_00SEADR.u4Data & (U4)ECC_MECCCAP_ID_PE1CL0_SEADR_SEADR0 )
								 >> u1ERRH_ECC_ADDR_RSHIFT_3BIT );
			break;

#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_TRIPLECORE ) )	/* U2B10かつ3コア構成 */
		case u1ERRH_ECC_IC_IDPE2:
			*t_pu4Address = (U4)( ( REG_ECC_MECCCAP_ID_PE2CL1.unID_00SEADR.u4Data & (U4)ECC_MECCCAP_ID_PE2CL1_SEADR_SEADR0 )
								 >> u1ERRH_ECC_ADDR_RSHIFT_3BIT );
			break;
#endif

/*		case u1ERRH_ECC_IC_IDPE3: */
			/* 機能安全はCore3を使用しないため何もしない */

/*		case u1ERRH_ECC_CF: */
/*		case u1ERRH_ECC_DTS: */
/*		case u1ERRH_ECC_DMDE_DMDE0: */
/*		case u1ERRH_ECC_DMDE_DMDE1: */
/*		case u1ERRH_ECC_DMDA_DMDA0: */
/*		case u1ERRH_ECC_DMDA_DMDA1: */
/*		case u1ERRH_ECC_PR32_E7RC01: */
/*		case u1ERRH_ECC_PR32_E7RC02: */
/*		case u1ERRH_ECC_PR32_E7RC03: */
/*		case u1ERRH_ECC_PR32_E7RC04: */
/*		case u1ERRH_ECC_PR32_E7MS00: */
/*		case u1ERRH_ECC_PR32_E7MS01: */
/*		case u1ERRH_ECC_PR32_E7MS02: */
/*		case u1ERRH_ECC_PR32_E7MS03: */
/*		case u1ERRH_ECC_PR32_E7MS04: */
/*		case u1ERRH_ECC_PR32_E7MS05: */
/*		case u1ERRH_ECC_PR32_E7MS06: */
/*		case u1ERRH_ECC_PR32_E7MS07: */
/*		case u1ERRH_ECC_PR32_E7MS08: */
/*		case u1ERRH_ECC_PR32_E7MS09: */
/*		case u1ERRH_ECC_PR32_E7DF00: */
/*		case u1ERRH_ECC_PR32_E7DF10: */
/*		case u1ERRH_ECC_PR16_E6DF00: */
/*		case u1ERRH_ECC_PR16_E6DF01: */
/*		case u1ERRH_ECC_PR16_E6DF10: */
/*		case u1ERRH_ECC_PR16_E6DF11: */
			/* ECC 1bitエラーは自動訂正し、通知しないため、何もしない */
/*			break; */

/*		case u1ERRH_ECC_PR32_E7FR00: */
/*		case u1ERRH_ECC_PR32_E7FR01: */
/*		case u1ERRH_ECC_PR32_E7FR02: */
			/* FlexRayは非使用のため何もしない */
/*			break; */

/*		case u1ERRH_ECC_PR32_E7GT00: */
/*		case u1ERRH_ECC_PR32_E7GT01: */
/*		case u1ERRH_ECC_PR32_E7GT10: */
/*		case u1ERRH_ECC_PR32_E7GT11: */
/*		case u1ERRH_ECC_PR32_E7GT20: */
/*		case u1ERRH_ECC_PR32_E7GT21: */
/*		case u1ERRH_ECC_PR32_E7GT30: */
/*		case u1ERRH_ECC_PR32_E7GT31: */
/*		case u1ERRH_ECC_PR32_E7GT40: */
/*		case u1ERRH_ECC_PR32_E7GT41: */
/*		case u1ERRH_ECC_PR32_E7GT50: */
/*		case u1ERRH_ECC_PR32_E7GT51: */
/*		case u1ERRH_ECC_PR32_E7GT60: */
/*		case u1ERRH_ECC_PR32_E7GT61: */
/*		case u1ERRH_ECC_PR32_E7GT100: */
/*		case u1ERRH_ECC_PR32_E7GT101: */
/*		case u1ERRH_ECC_PR32_E7GT102: */
/*		case u1ERRH_ECC_PR32_E7GT110: */
/*		case u1ERRH_ECC_PR32_E7GT111: */
/*		case u1ERRH_ECC_PR32_E7GT112: */
			/* GTMは非使用のため何もしない */
/*			break; */

/*		case u1ERRH_ECC_PR32_E7MM00: */
/*		case u1ERRH_ECC_PR32_E7MM01: */
			/* MMCAは非使用のため何もしない */
/*			break; */

/*		case u1ERRH_ECC_PR32_E7ES00: */
/*		case u1ERRH_ECC_PR32_E7ES01: */
/*		case u1ERRH_ECC_PR32_E7ES02: */
/*		case u1ERRH_ECC_PR32_E7ES03: */
/*		case u1ERRH_ECC_PR32_E7ES04: */
/*		case u1ERRH_ECC_PR32_E7ES05: */
			/* Ethernetは非使用のため何もしない */
/*			break; */

/*		case u1ERRH_ECC_DTP_LRAM_ADDR: */
/*		case u1ERRH_ECC_DTP_CRAM_ADDR: */
/*		case u1ERRH_ECC_DTP_CFL_ADDR: */
/*		case u1ERRH_ECC_DTP_PERI_ADDR: */
/*		case u1ERRH_ECC_DTP_EMU_ADDR: */
/*		case u1ERRH_ECC_DTP_HB90MECC_ADDR: */
/*		case u1ERRH_ECC_DTP_HB90SECC_ADDR: */
/*		case u1ERRH_ECC_DTP_HB92MECC_ADDR: */
/*		case u1ERRH_ECC_DTP_HB92SECC_ADDR: */
/*		case u1ERRH_ECC_DTP_HB94MECC_ADDR: */
/*		case u1ERRH_ECC_DTP_HB97MECC_ADDR: */
/*		case u1ERRH_ECC_DTP_HB98MECC_ADDR: */
/*		case u1ERRH_ECC_DTP_HB911MECC_ADDR: */
/*		case u1ERRH_ECC_DTP_HB912MECC_ADDR: */
/*		case u1ERRH_ECC_DTP_V2A1_ADDR: */
/*		case u1ERRH_ECC_DTP_V2A2_ADDR: */
/*		case u1ERRH_ECC_DTP_V2A3_ADDR: */
/*		case u1ERRH_ECC_DTP_V2A4_ADDR: */
/*		case u1ERRH_ECC_DTP_V2A5_ADDR: */
/*		case u1ERRH_ECC_DTP_V2A6_ADDR: */
/*		case u1ERRH_ECC_DTP_V2A7_ADDR: */
/*		case u1ERRH_ECC_DTP_V2A8_ADDR: */
/*		case u1ERRH_ECC_DTP_V2A9_ADDR: */
/*		case u1ERRH_ECC_DTP_V2A10_ADDR: */
/*		case u1ERRH_ECC_DTP_V2A11_ADDR: */
/*		case u1ERRH_ECC_DTP_DFPFNT_ADDR: */
/*		case u1ERRH_ECC_DTP_LRAM_DATA: */
/*		case u1ERRH_ECC_DTP_CRAM_DATA: */
/*		case u1ERRH_ECC_DTP_PERI_DATA: */
/*		case u1ERRH_ECC_DTP_DMDT_DATA: */
/*		case u1ERRH_ECC_DTP_EMU_DATA: */
/*		case u1ERRH_ECC_DTP_HB90MECC_DATA: */
/*		case u1ERRH_ECC_DTP_HB90SECC_DATA: */
/*		case u1ERRH_ECC_DTP_HB92MECC_DATA: */
/*		case u1ERRH_ECC_DTP_HB92SECC_DATA: */
/*		case u1ERRH_ECC_DTP_HB94MECC_DATA: */
/*		case u1ERRH_ECC_DTP_HB97MECC_DATA: */
/*		case u1ERRH_ECC_DTP_HB98MECC_DATA: */
/*		case u1ERRH_ECC_DTP_HB911MECC_DATA: */
/*		case u1ERRH_ECC_DTP_HB912MECC_DATA: */
/*		case u1ERRH_ECC_DTP_V2A1_DATA: */
/*		case u1ERRH_ECC_DTP_V2A2_DATA: */
/*		case u1ERRH_ECC_DTP_V2A3_DATA: */
/*		case u1ERRH_ECC_DTP_V2A4_DATA: */
/*		case u1ERRH_ECC_DTP_V2A5_DATA: */
/*		case u1ERRH_ECC_DTP_V2A6_DATA: */
/*		case u1ERRH_ECC_DTP_V2A7_DATA: */
/*		case u1ERRH_ECC_DTP_V2A8_DATA: */
/*		case u1ERRH_ECC_DTP_V2A9_DATA: */
/*		case u1ERRH_ECC_DTP_V2A10_DATA: */
/*		case u1ERRH_ECC_DTP_V2A11_DATA: */
/*		case u1ERRH_ECC_DTP_DFPROM_DATA: */
/*		case u1ERRH_ECC_DTP_DFPSYS_DATA: */
/*		case u1ERRH_ECC_DTP_DFPSYS_DATA: */
			/* Data Transfer PathのECCはハード仕様でエラー発生アドレスは取得できないため何もしない */
/*			break; */

		default:
			/* 何もしない */
			break;
	}
}

/*----------------------------------------------------------------------------------------------*/
/*	ECC Fatal Error Address Get																	*/
/*	return		: ErrorAddress																	*/
/*	parameters	: ModuleNumber																	*/
/*----------------------------------------------------------------------------------------------*/
U4		ErrH_Ecc_GetEccFatalErrAddr( U1 t_u1ModuleNum )
{
	volatile Reg_Ecc_Ecc7Type*				t_pstReg_Ecc7;
	volatile Reg_Ecc_Ecc6Type*				t_pstReg_Ecc6;
	U4										t_u4ErrorAddress;

	t_u4ErrorAddress = (U4)0x00000000U;

	switch( t_u1ModuleNum )
	{
		case u1ERRH_ECC_CF:
			t_u4ErrorAddress = (U4)( ( REG_ECC_MECCCAP_CFL.unCF_00DEADR.u4Data & (U4)ECC_MECCCAP_CFL_CF_00DEADR_DEADR0 )
									<< u1ERRH_ECC_ADDR_LSHIFT_2BIT );
			break;

/*		case u1ERRH_ECC_DF: */
			/* 機能安全のDFのECC機能は非使用のため何もしない */
/*			break; */

		case u1ERRH_ECC_LRAM_LRPE0:
			t_u4ErrorAddress = (U4)( ( REG_ECC_MECCCAP_LR_PE0CL0.unLR0_00DEADR.u4Data & (U4)ECC_MECCCAP_LR_PE0CL0_DEADR_DEADR0 )
								   +   u4ERRH_ECC_ADDR_OFFSET_LRAM_PE0 );			/* qac 3383 : レジスタ値のレンジ内では、ラップアラウンドが発生しないことを確認済み。QAC結果は過剰警告 */
			break;

		case u1ERRH_ECC_LRAM_LRPE1:
			t_u4ErrorAddress = (U4)( ( REG_ECC_MECCCAP_LR_PE1CL0.unLR0_00DEADR.u4Data & (U4)ECC_MECCCAP_LR_PE1CL0_DEADR_DEADR0 )
								   +   u4ERRH_ECC_ADDR_OFFSET_LRAM_PE1 );			/* qac 3383 : レジスタ値のレンジ内では、ラップアラウンドが発生しないことを確認済み。QAC結果は過剰警告 */
			break;

#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_TRIPLECORE ) )	/* U2B10かつ3コア構成 */
		case u1ERRH_ECC_LRAM_LRPE2:
			t_u4ErrorAddress = (U4)( ( REG_ECC_MECCCAP_LR_PE2CL1.unLR0_00DEADR.u4Data & (U4)ECC_MECCCAP_LR_PE2CL1_DEADR_DEADR0 )
								   +   u4ERRH_ECC_ADDR_OFFSET_LRAM_PE2 );			/* qac 3383 : レジスタ値のレンジ内では、ラップアラウンドが発生しないことを確認済み。QAC結果は過剰警告 */
			break;
#endif

/*		case u1ERRH_ECC_LRAM_LRPE3: */
			/* 機能安全はCore3を使用しないため何もしない */

		case u1ERRH_ECC_LRAM_LRA:
			t_u4ErrorAddress = (U4)( ( REG_ECC_MECCCAP_LRA.unLR1_00DEADR.u4Data & (U4)ECC_MECCCAP_LRA_LR1_DEADR_DEADR0 )
									  +   u4ERRH_ECC_ADDR_OFFSET_LRAM_LRA );		/* qac 3383 : レジスタ値のレンジ内では、ラップアラウンドが発生しないことを確認済み。QAC結果は過剰警告 */
			break;

		case u1ERRH_ECC_CRAM_CRAM:
			t_u4ErrorAddress = (U4)( ( REG_ECC_MECCCAP_CRAM.unCR_00DEADR.u4Data & (U4)ECC_MECCCAP_CRAM_CR_DEADR_DEADR0 )
								   +   u4ERRH_ECC_ADDR_OFFSET_CRAM );				/* qac 3383 : レジスタ値のレンジ内では、ラップアラウンドが発生しないことを確認済み。QAC結果は過剰警告 */
			break;

		case u1ERRH_ECC_IC_ITPE0:
			t_u4ErrorAddress = (U4)( ( REG_ECC_MECCCAP_IT_PE0CL0.unIT_00DEADR.u4Data & (U4)ECC_MECCCAP_IT_PE0CL0_DEADR_DEADR0 )
									 >> u1ERRH_ECC_ADDR_RSHIFT_5BIT );
			break;

		case u1ERRH_ECC_IC_ITPE1:
			t_u4ErrorAddress = (U4)( ( REG_ECC_MECCCAP_IT_PE1CL0.unIT_00DEADR.u4Data & (U4)ECC_MECCCAP_IT_PE1CL0_DEADR_DEADR0 )
									 >> u1ERRH_ECC_ADDR_RSHIFT_5BIT );
			break;

#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_TRIPLECORE ) )	/* U2B10かつ3コア構成 */
		case u1ERRH_ECC_IC_ITPE2:
			t_u4ErrorAddress = (U4)( ( REG_ECC_MECCCAP_IT_PE2CL1.unIT_00DEADR.u4Data & (U4)ECC_MECCCAP_IT_PE2CL1_DEADR_DEADR0 )
									 >> u1ERRH_ECC_ADDR_RSHIFT_5BIT );
			break;
#endif

/*		case u1ERRH_ECC_IC_ITPE3: */
			/* 機能安全はCore3を使用しないため何もしない */

		case u1ERRH_ECC_IC_IDPE0:
			t_u4ErrorAddress = (U4)( ( REG_ECC_MECCCAP_ID_PE0CL0.unID_00DEADR.u4Data & (U4)ECC_MECCCAP_ID_PE0CL0_DEADR_DEADR0 )
									 >> u1ERRH_ECC_ADDR_RSHIFT_3BIT );
			break;

		case u1ERRH_ECC_IC_IDPE1:
			t_u4ErrorAddress = (U4)( ( REG_ECC_MECCCAP_ID_PE1CL0.unID_00DEADR.u4Data & (U4)ECC_MECCCAP_ID_PE1CL0_DEADR_DEADR0 )
									 >> u1ERRH_ECC_ADDR_RSHIFT_3BIT );
			break;

#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_TRIPLECORE ) )	/* U2B10かつ3コア構成 */
		case u1ERRH_ECC_IC_IDPE2:
			t_u4ErrorAddress = (U4)( ( REG_ECC_MECCCAP_ID_PE2CL1.unID_00DEADR.u4Data & (U4)ECC_MECCCAP_ID_PE2CL1_DEADR_DEADR0 )
									 >> u1ERRH_ECC_ADDR_RSHIFT_3BIT );
			break;
#endif

/*		case u1ERRH_ECC_IC_IDPE3: */
			/* 機能安全はCore3を使用しないため何もしない */

		case u1ERRH_ECC_DTS:
			t_u4ErrorAddress = (U4)( ( REG_ECC_MECCCAP_DTS.unDR_00DEADR.u4Data & (U4)ECC_MECCCAP_DTS_DR_DEADR_DEADR0 )
								   +   u4ERRH_ECC_ADDR_OFFSET_DTS );				/* qac 3383 : レジスタ値のレンジ内では、ラップアラウンドが発生しないことを確認済み。QAC結果は過剰警告 */
			break;

		case u1ERRH_ECC_DMDE_DMDE0:
			t_u4ErrorAddress = (U4)( ( REG_ECC_MECCCAP_DMDE0.unDE_00DEADR.u4Data & (U4)ECC_MECCCAP_DMDE0_DE_DEADR_DEADR0 )
									+  u4ERRH_ECC_ADDR_OFFSET_SDMC0 );				/* qac 3383 : レジスタ値のレンジ内では、ラップアラウンドが発生しないことを確認済み。QAC結果は過剰警告 */
			break;

#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
		case u1ERRH_ECC_DMDE_DMDE1:
			t_u4ErrorAddress = (U4)( ( REG_ECC_MECCCAP_DMDE1.unDE_00DEADR.u4Data & (U4)ECC_MECCCAP_DMDE1_DE_DEADR_DEADR0 )
									+  u4ERRH_ECC_ADDR_OFFSET_SDMC1 );				/* qac 3383 : レジスタ値のレンジ内では、ラップアラウンドが発生しないことを確認済み。QAC結果は過剰警告 */
			break;
#endif

		case u1ERRH_ECC_DMDA_DMDA0:
			t_u4ErrorAddress = (U4)( ( REG_ECC_MECCCAP_DMDA0.unDA_00DEADR.u4Data & (U4)ECC_MECCCAP_DMDA0_DA_DEADR_DEADR0 )
									 >> u1ERRH_ECC_ADDR_RSHIFT_3BIT );
			break;

#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
		case u1ERRH_ECC_DMDA_DMDA1:
			t_u4ErrorAddress = (U4)( ( REG_ECC_MECCCAP_DMDA1.unDA_00DEADR.u4Data & (U4)ECC_MECCCAP_DMDA1_DA_DEADR_DEADR0 )
									 >> u1ERRH_ECC_ADDR_RSHIFT_3BIT );
			break;
#endif

		case u1ERRH_ECC_PR32_E7RC01:
		case u1ERRH_ECC_PR32_E7RC04:
			t_pstReg_Ecc7 = (volatile Reg_Ecc_Ecc7Type*)pcstReg_Ecc7[t_u1ModuleNum - u1ERRH_ECC_PR32_OFFSET];
			t_u4ErrorAddress = (U4)( ( ( t_pstReg_Ecc7->u4E710EAD & u4ERRH_ECC_ADDR_MASK_BIT_5_0 ) << u1ERRH_ECC_ADDR_LSHIFT_2BIT )
									+  cu4Ecc_Ecc7OffsetTable[t_u1ModuleNum - u1ERRH_ECC_PR32_OFFSET] );	/* qac 3384 : レジスタ値のレンジ内では、ラップアラウンドが発生しないことを確認済み。QAC結果は過剰警告 */
			break;

		case u1ERRH_ECC_PR32_E7RC02:
		case u1ERRH_ECC_PR32_E7RC03:
			t_pstReg_Ecc7 = (volatile Reg_Ecc_Ecc7Type*)pcstReg_Ecc7[t_u1ModuleNum - u1ERRH_ECC_PR32_OFFSET];
			t_u4ErrorAddress = (U4)( ( ( t_pstReg_Ecc7->u4E710EAD & u4ERRH_ECC_ADDR_MASK_BIT_4_0 ) << u1ERRH_ECC_ADDR_LSHIFT_3BIT )
									+  cu4Ecc_Ecc7OffsetTable[t_u1ModuleNum - u1ERRH_ECC_PR32_OFFSET] );	/* qac 3384 : レジスタ値のレンジ内では、ラップアラウンドが発生しないことを確認済み。QAC結果は過剰警告 */
			break;

		case u1ERRH_ECC_PR32_E7MS00:
		case u1ERRH_ECC_PR32_E7MS01:
		case u1ERRH_ECC_PR32_E7MS02:
		case u1ERRH_ECC_PR32_E7MS03:
		case u1ERRH_ECC_PR32_E7MS04:
		case u1ERRH_ECC_PR32_E7MS05:
		case u1ERRH_ECC_PR32_E7MS06:
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
		case u1ERRH_ECC_PR32_E7MS07:
		case u1ERRH_ECC_PR32_E7MS08:
		case u1ERRH_ECC_PR32_E7MS09:
#endif
			t_pstReg_Ecc7 = (volatile Reg_Ecc_Ecc7Type*)pcstReg_Ecc7[t_u1ModuleNum - u1ERRH_ECC_PR32_OFFSET];
			t_u4ErrorAddress = (U4)( ( ( t_pstReg_Ecc7->u4E710EAD & u4ERRH_ECC_ADDR_MASK_BIT_6_0 ) << u1ERRH_ECC_ADDR_LSHIFT_2BIT )
									+  cu4Ecc_Ecc7OffsetTable[t_u1ModuleNum - u1ERRH_ECC_PR32_OFFSET] );	/* qac 3384 : レジスタ値のレンジ内では、ラップアラウンドが発生しないことを確認済み。QAC結果は過剰警告 */
			break;

		case u1ERRH_ECC_PR32_E7DF00:
			t_pstReg_Ecc7 = (volatile Reg_Ecc_Ecc7Type*)pcstReg_Ecc7[t_u1ModuleNum - u1ERRH_ECC_PR32_OFFSET];
			t_u4ErrorAddress = (U4)( ( ( t_pstReg_Ecc7->u4E710EAD & u4ERRH_ECC_ADDR_MASK_BIT_7_0 ) << u1ERRH_ECC_ADDR_LSHIFT_2BIT )
										 + cu4Ecc_Ecc7OffsetTable[t_u1ModuleNum - u1ERRH_ECC_PR32_OFFSET] );	/* qac 3384 : レジスタ値のレンジ内では、ラップアラウンドが発生しないことを確認済み。QAC結果は過剰警告 */
			break;

		case u1ERRH_ECC_PR32_E7DF10:
			t_pstReg_Ecc7 = (volatile Reg_Ecc_Ecc7Type*)pcstReg_Ecc7[t_u1ModuleNum - u1ERRH_ECC_PR32_OFFSET];
			t_u4ErrorAddress = (U4)( ( ( t_pstReg_Ecc7->u4E710EAD & u4ERRH_ECC_ADDR_MASK_BIT_5_0 ) << u1ERRH_ECC_ADDR_LSHIFT_2BIT )
										 + cu4Ecc_Ecc7OffsetTable[t_u1ModuleNum - u1ERRH_ECC_PR32_OFFSET] );	/* qac 3384 : レジスタ値のレンジ内では、ラップアラウンドが発生しないことを確認済み。QAC結果は過剰警告 */
			break;

/*		case u1ERRH_ECC_PR32_E7FR00: */
/*		case u1ERRH_ECC_PR32_E7FR01: */
/*		case u1ERRH_ECC_PR32_E7FR02: */
			/* FlexRayは非使用のため何もしない */
/*			break; */

/*		case u1ERRH_ECC_PR32_E7GT00: */
/*		case u1ERRH_ECC_PR32_E7GT01: */
/*		case u1ERRH_ECC_PR32_E7GT10: */
/*		case u1ERRH_ECC_PR32_E7GT11: */
/*		case u1ERRH_ECC_PR32_E7GT20: */
/*		case u1ERRH_ECC_PR32_E7GT21: */
/*		case u1ERRH_ECC_PR32_E7GT30: */
/*		case u1ERRH_ECC_PR32_E7GT31: */
/*		case u1ERRH_ECC_PR32_E7GT40: */
/*		case u1ERRH_ECC_PR32_E7GT41: */
/*		case u1ERRH_ECC_PR32_E7GT50: */
/*		case u1ERRH_ECC_PR32_E7GT51: */
/*		case u1ERRH_ECC_PR32_E7GT60: */
/*		case u1ERRH_ECC_PR32_E7GT61: */
/*		case u1ERRH_ECC_PR32_E7GT100: */
/*		case u1ERRH_ECC_PR32_E7GT101: */
/*		case u1ERRH_ECC_PR32_E7GT102: */
/*		case u1ERRH_ECC_PR32_E7GT110: */
/*		case u1ERRH_ECC_PR32_E7GT111: */
/*		case u1ERRH_ECC_PR32_E7GT112: */
			/* GTMは非使用のため何もしない */
/*			break; */

/*		case u1ERRH_ECC_PR32_E7MM00: */
/*		case u1ERRH_ECC_PR32_E7MM01: */
			/* MMCAは非使用のため何もしない */
/*			break; */

/*		case u1ERRH_ECC_PR32_E7ES00: */
/*		case u1ERRH_ECC_PR32_E7ES01: */
/*		case u1ERRH_ECC_PR32_E7ES02: */
/*		case u1ERRH_ECC_PR32_E7ES03: */
/*		case u1ERRH_ECC_PR32_E7ES04: */
/*		case u1ERRH_ECC_PR32_E7ES05: */
			/* Ethernetは非使用のため何もしない */
/*			break; */

		case u1ERRH_ECC_PR16_E6DF00:
		case u1ERRH_ECC_PR16_E6DF01:
			t_pstReg_Ecc6 = (volatile Reg_Ecc_Ecc6Type*)pcstReg_Ecc6[t_u1ModuleNum - u1ERRH_ECC_PR16_OFFSET];
			t_u4ErrorAddress = (U4)( ( ( t_pstReg_Ecc6->u4E610EAD & u4ERRH_ECC_ADDR_MASK_BIT_8_0 ) << u1ERRH_ECC_ADDR_LSHIFT_2BIT )
										 + cu4Ecc_Ecc6OffsetTable[t_u1ModuleNum - u1ERRH_ECC_PR16_OFFSET] );	/* qac 3384 : レジスタ値のレンジ内では、ラップアラウンドが発生しないことを確認済み。QAC結果は過剰警告 */
			break;

		case u1ERRH_ECC_PR16_E6DF10:
		case u1ERRH_ECC_PR16_E6DF11:
			t_pstReg_Ecc6 = (volatile Reg_Ecc_Ecc6Type*)pcstReg_Ecc6[t_u1ModuleNum - u1ERRH_ECC_PR16_OFFSET];
			t_u4ErrorAddress = (U4)( ( ( t_pstReg_Ecc6->u4E610EAD & u4ERRH_ECC_ADDR_MASK_BIT_6_0 ) << u1ERRH_ECC_ADDR_LSHIFT_2BIT )
										 + cu4Ecc_Ecc6OffsetTable[t_u1ModuleNum - u1ERRH_ECC_PR16_OFFSET] );	/* qac 3384 : レジスタ値のレンジ内では、ラップアラウンドが発生しないことを確認済み。QAC結果は過剰警告 */
			break;

/*		case u1ERRH_ECC_DTP_LRAM_ADDR: */
/*		case u1ERRH_ECC_DTP_CRAM_ADDR: */
/*		case u1ERRH_ECC_DTP_CFL_ADDR: */
/*		case u1ERRH_ECC_DTP_PERI_ADDR: */
/*		case u1ERRH_ECC_DTP_EMU_ADDR: */
/*		case u1ERRH_ECC_DTP_HB90MECC_ADDR: */
/*		case u1ERRH_ECC_DTP_HB90SECC_ADDR: */
/*		case u1ERRH_ECC_DTP_HB92MECC_ADDR: */
/*		case u1ERRH_ECC_DTP_HB92SECC_ADDR: */
/*		case u1ERRH_ECC_DTP_HB94MECC_ADDR: */
/*		case u1ERRH_ECC_DTP_HB97MECC_ADDR: */
/*		case u1ERRH_ECC_DTP_HB98MECC_ADDR: */
/*		case u1ERRH_ECC_DTP_HB911MECC_ADDR: */
/*		case u1ERRH_ECC_DTP_HB912MECC_ADDR: */
/*		case u1ERRH_ECC_DTP_V2A1_ADDR: */
/*		case u1ERRH_ECC_DTP_V2A2_ADDR: */
/*		case u1ERRH_ECC_DTP_V2A3_ADDR: */
/*		case u1ERRH_ECC_DTP_V2A4_ADDR: */
/*		case u1ERRH_ECC_DTP_V2A5_ADDR: */
/*		case u1ERRH_ECC_DTP_V2A6_ADDR: */
/*		case u1ERRH_ECC_DTP_V2A7_ADDR: */
/*		case u1ERRH_ECC_DTP_V2A8_ADDR: */
/*		case u1ERRH_ECC_DTP_V2A9_ADDR: */
/*		case u1ERRH_ECC_DTP_V2A10_ADDR: */
/*		case u1ERRH_ECC_DTP_V2A11_ADDR: */
/*		case u1ERRH_ECC_DTP_DFPFNT_ADDR: */
/*		case u1ERRH_ECC_DTP_LRAM_DATA: */
/*		case u1ERRH_ECC_DTP_CRAM_DATA: */
/*		case u1ERRH_ECC_DTP_PERI_DATA: */
/*		case u1ERRH_ECC_DTP_DMDT_DATA: */
/*		case u1ERRH_ECC_DTP_EMU_DATA: */
/*		case u1ERRH_ECC_DTP_HB90MECC_DATA: */
/*		case u1ERRH_ECC_DTP_HB90SECC_DATA: */
/*		case u1ERRH_ECC_DTP_HB92MECC_DATA: */
/*		case u1ERRH_ECC_DTP_HB92SECC_DATA: */
/*		case u1ERRH_ECC_DTP_HB94MECC_DATA: */
/*		case u1ERRH_ECC_DTP_HB97MECC_DATA: */
/*		case u1ERRH_ECC_DTP_HB98MECC_DATA: */
/*		case u1ERRH_ECC_DTP_HB911MECC_DATA: */
/*		case u1ERRH_ECC_DTP_HB912MECC_DATA: */
/*		case u1ERRH_ECC_DTP_V2A1_DATA: */
/*		case u1ERRH_ECC_DTP_V2A2_DATA: */
/*		case u1ERRH_ECC_DTP_V2A3_DATA: */
/*		case u1ERRH_ECC_DTP_V2A4_DATA: */
/*		case u1ERRH_ECC_DTP_V2A5_DATA: */
/*		case u1ERRH_ECC_DTP_V2A6_DATA: */
/*		case u1ERRH_ECC_DTP_V2A7_DATA: */
/*		case u1ERRH_ECC_DTP_V2A8_DATA: */
/*		case u1ERRH_ECC_DTP_V2A9_DATA: */
/*		case u1ERRH_ECC_DTP_V2A10_DATA: */
/*		case u1ERRH_ECC_DTP_V2A11_DATA: */
/*		case u1ERRH_ECC_DTP_DFPROM_DATA: */
/*		case u1ERRH_ECC_DTP_DFPSYS_DATA: */
/*		case u1ERRH_ECC_DTP_DFPSYS_DATA: */
			/* Data Transfer PathのECCはハード仕様でエラー発生アドレスは取得できないため何もしない */
/*			break; */

		default:
			/* 何もしない */
			break;
	}

	return( t_u4ErrorAddress );
}

/*----------------------------------------------------------------------------------------------*/
/*	ECC 1bit Error Detailed Information Get														*/
/*	return		: ErrorAddress																	*/
/*	parameters	: ModuleNumber, DetailInformation(Sync), ArrayNum								*/
/*----------------------------------------------------------------------------------------------*/
void	ErrH_Ecc_GetEcc1bitErrDetail( U1 t_u1ModuleNum, U1* t_pu1DetailInfo, U1 t_u1ArrayNum )
{
	S4										i;
	U1										t_u1LoopNum;

	switch( t_u1ModuleNum )
	{
		case u1ERRH_ECC_CRAM_CRAM:
			if( t_u1ArrayNum > u1ERRH_ECC_ADDR_BUFFNUM_CRAM )
			{
				t_u1LoopNum = u1ERRH_ECC_ADDR_BUFFNUM_CRAM;
			}
			else
			{
				t_u1LoopNum = t_u1ArrayNum;
			}

			for( i = (S4)0; i < (S4)t_u1LoopNum; i++ )
			{
				t_pu1DetailInfo[i] = (U1)( REG_ECC_MECCCAP_CRAM.unCR_nSEADR[i].u4Data >> u1ERRH_ECC_DETAIL_RSHIFT_27BIT );
			}
			break;

		default:
			/* 何もしない */
			break;
	}
}

/*----------------------------------------------------------------------------------------------*/
/*	ECC Fatal Error Detailed Information Get													*/
/*	return		: ErrorAddress																	*/
/*	parameters	: ModuleNumber																	*/
/*----------------------------------------------------------------------------------------------*/
U1		ErrH_Ecc_GetEccFatalErrDetail( U1 t_u1ModuleNum )
{
	U1										t_u1ErrorDetailInfo;

	t_u1ErrorDetailInfo = (U1)0x00U;

	switch( t_u1ModuleNum )
	{
		case u1ERRH_ECC_CF:
			t_u1ErrorDetailInfo = (U1)( REG_ECC_MECCCAP_CFL.unCF_00DEADR.u4Data >> u1ERRH_ECC_DETAIL_RSHIFT_27BIT );
			break;

		case u1ERRH_ECC_CRAM_CRAM:
			t_u1ErrorDetailInfo = (U1)( REG_ECC_MECCCAP_CRAM.unCR_00DEADR.u4Data >> u1ERRH_ECC_DETAIL_RSHIFT_27BIT );
			break;

		default:
			/* 何もしない */
			break;
	}

	return( t_u1ErrorDetailInfo );
}

/*----------------------------------------------------------------------------------------------*/
/*	ECC 1bit Error SPID Get																		*/
/*	return		: ErrorSPID																		*/
/*	parameters	: ModuleNumber, ErrorSPID(Sync), ArrayNum										*/
/*----------------------------------------------------------------------------------------------*/
void	ErrH_Ecc_GetEcc1bitErrSpid( U1 t_u1ModuleNum, U4* t_pu4ErrSpid, U1 t_u1ArrayNum )
{
	S4										i;
	U1										t_u1LoopNum;

	switch( t_u1ModuleNum )
	{
		case u1ERRH_ECC_LRAM_LRPE0:
			if( t_u1ArrayNum > u1ERRH_ECC_ADDR_BUFFNUM_LRAM )
			{
				t_u1LoopNum = u1ERRH_ECC_ADDR_BUFFNUM_LRAM;
			}
			else
			{
				t_u1LoopNum = t_u1ArrayNum;
			}

			for( i = (S4)0; i < (S4)t_u1LoopNum; i++ )
			{
				t_pu4ErrSpid[i] = REG_ECC_MECCCAP_LR_PE0CL0.unLR0_kSESPID[i].u4Data;
			}
			break;

		case u1ERRH_ECC_LRAM_LRPE1:
			if( t_u1ArrayNum > u1ERRH_ECC_ADDR_BUFFNUM_LRAM )
			{
				t_u1LoopNum = u1ERRH_ECC_ADDR_BUFFNUM_LRAM;
			}
			else
			{
				t_u1LoopNum = t_u1ArrayNum;
			}

			for( i = (S4)0; i < (S4)t_u1LoopNum; i++ )
			{
				t_pu4ErrSpid[i] = REG_ECC_MECCCAP_LR_PE1CL0.unLR0_kSESPID[i].u4Data;
			}
			break;

#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_TRIPLECORE ) )	/* U2B10かつ3コア構成 */
		case u1ERRH_ECC_LRAM_LRPE2:
			if( t_u1ArrayNum > u1ERRH_ECC_ADDR_BUFFNUM_LRAM )
			{
				t_u1LoopNum = u1ERRH_ECC_ADDR_BUFFNUM_LRAM;
			}
			else
			{
				t_u1LoopNum = t_u1ArrayNum;
			}

			for( i = (S4)0; i < (S4)t_u1LoopNum; i++ )
			{
				t_pu4ErrSpid[i] = REG_ECC_MECCCAP_LR_PE2CL1.unLR0_kSESPID[i].u4Data;
			}
			break;
#endif

/*		case u1ERRH_ECC_LRAM_LRPE3: */
			/* 機能安全はCore3を使用しないため何もしない */

		case u1ERRH_ECC_LRAM_LRA:
			if( t_u1ArrayNum > u1ERRH_ECC_ADDR_BUFFNUM_LRAM )
			{
				t_u1LoopNum = u1ERRH_ECC_ADDR_BUFFNUM_LRAM;
			}
			else
			{
				t_u1LoopNum = t_u1ArrayNum;
			}

			for( i = (S4)0; i < (S4)t_u1LoopNum; i++ )
			{
				t_pu4ErrSpid[i] = REG_ECC_MECCCAP_LRA.unLR1_kSESPID[i].u4Data;
			}
			break;

		case u1ERRH_ECC_CRAM_CRAM:
			if( t_u1ArrayNum > u1ERRH_ECC_ADDR_BUFFNUM_CRAM )
			{
				t_u1LoopNum = u1ERRH_ECC_ADDR_BUFFNUM_CRAM;
			}
			else
			{
				t_u1LoopNum = t_u1ArrayNum;
			}

			for( i = (S4)0; i < (S4)t_u1LoopNum; i++ )
			{
				t_pu4ErrSpid[i] = REG_ECC_MECCCAP_CRAM.unCR_kSESPID[i].u4Data;
			}
			break;

		default:
			/* 何もしない */
			break;
	}
}

/*----------------------------------------------------------------------------------------------*/
/*	ECC Fatal Error SPID Get																	*/
/*	return		: ErrorSPID																		*/
/*	parameters	: ModuleNumber																	*/
/*----------------------------------------------------------------------------------------------*/
U4		ErrH_Ecc_GetEccFatalErrSpid( U1 t_u1ModuleNum )
{
	U4										t_u4ErrorSpid;

	t_u4ErrorSpid = (U4)0x00000000U;

	switch( t_u1ModuleNum )
	{
		case u1ERRH_ECC_CF:
			t_u4ErrorSpid = REG_ECC_MECCCAP_CFL.unCF_00DESPID.u4Data; 
			break;

		case u1ERRH_ECC_LRAM_LRPE0:
			t_u4ErrorSpid = REG_ECC_MECCCAP_LR_PE0CL0.unLR0_00DESPID.u4Data;
			break;

		case u1ERRH_ECC_LRAM_LRPE1:
			t_u4ErrorSpid = REG_ECC_MECCCAP_LR_PE1CL0.unLR0_00DESPID.u4Data;
			break;

#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_TRIPLECORE ) )	/* U2B10かつ3コア構成 */
		case u1ERRH_ECC_LRAM_LRPE2:
			t_u4ErrorSpid = REG_ECC_MECCCAP_LR_PE2CL1.unLR0_00DESPID.u4Data;
			break;
#endif

/*		case u1ERRH_ECC_LRAM_LRPE3: */
			/* 機能安全はCore3を使用しないため何もしない */

		case u1ERRH_ECC_LRAM_LRA:
			t_u4ErrorSpid = REG_ECC_MECCCAP_LRA.unLR1_00DESPID.u4Data;
			break;

		case u1ERRH_ECC_CRAM_CRAM:
			t_u4ErrorSpid = REG_ECC_MECCCAP_CRAM.unCR_00DESPID.u4Data;
			break;

		default:
			/* 何もしない */
			break;
	}

	return( t_u4ErrorSpid );
}

/*----------------------------------------------------------------------------------------------*/
/*	ECC/EDC Stop Function																		*/
/*	return		: none																			*/
/*	parameters	: none																			*/
/*----------------------------------------------------------------------------------------------*/
void	ErrH_Ecc_StopEccEdc( void )
{
	/* ECCエラー通知無効化 */
	ErrH_Ecc_DeInit();
	
	s_u1ErrH_Ecc_DisableRefreshEccReg = (U1)ON;
}

/*----------------------------------------------------------------------------------------------*/
/* Clear All ECC Error Function																	*/
/* Return		: none																			*/
/* Parameters	: none																			*/
/*----------------------------------------------------------------------------------------------*/
void	ErrH_Ecc_ClearAllEccError( void )
{
	U1							i;			/* モジュール番号 */

	/* 全モジュールのECC Fatal、1bitエラーをクリアする			  		*/
	/* 処理を簡素化するため無条件でエラークリア関数をコールする			*/
	/* 非実装のモジュールについてもコールするが、						*/
	/* コール先関数内の分岐処理にてクリア処理を実施しないため問題なし	*/
	for ( i = (U1)0U; i < (U1)ERRH_ECC_MODULE_NUM; i++ )
	{
		ErrH_Ecc_ClearEccFatalErr( i );		/* ECC Fatalエラークリア */
		ErrH_Ecc_ClearEcc1bitErr( i );		/* ECC 1bitエラークリア  */
	}
}

/*----------------------------------------------------------------------------------------------*/
/*	Clear ECC Error Status Function																*/
/*	return		: none																			*/
/*	parameters	: RAM Type																		*/
/*----------------------------------------------------------------------------------------------*/
void	ErrH_Ecc_ClearEccErrorStatus( U1 t_u1RamType )
{
	U4							t_u4CoreId;				/* CoreID格納 */

	switch( t_u1RamType )
	{
		case u1ERRH_ECC_RAMTYPE_ALL:
			Pil_Ecc_ClearLramPe0EccFatalErrorStatus();
			Pil_Ecc_ClearLramPe1EccFatalErrorStatus();
#if ( MCU_CORE_NUM > MCU_DUALCORE )
			Pil_Ecc_ClearLramPe2EccFatalErrorStatus();
#endif
#if ( MCU_CORE_NUM > MCU_TRIPLECORE )
			Pil_Ecc_ClearLramPe3EccFatalErrorStatus();
#endif
			Pil_Ecc_ClearCramEccFatalErrorStatus();
			break;

		case u1ERRH_ECC_RAMTYPE_LRAM:
			t_u4CoreId = Bswlib_GetCoreId();

			if ( t_u4CoreId == BSW_CORE_ID_CORE0 )
			{
				Pil_Ecc_ClearLramPe0EccFatalErrorStatus();
			}
			else if ( t_u4CoreId == BSW_CORE_ID_CORE1 )
			{
				Pil_Ecc_ClearLramPe1EccFatalErrorStatus();
			}
#if ( MCU_CORE_NUM > MCU_DUALCORE )
			else if ( t_u4CoreId == BSW_CORE_ID_CORE2 )
			{
				Pil_Ecc_ClearLramPe2EccFatalErrorStatus();
			}
#endif
#if ( MCU_CORE_NUM > MCU_TRIPLECORE )
			else if ( t_u4CoreId == BSW_CORE_ID_CORE3 )
			{
				Pil_Ecc_ClearLramPe3EccFatalErrorStatus();
			}
#endif
			else
			{
				/* 処理なし */
			}
			break;

		case u1ERRH_ECC_RAMTYPE_CRAM:
			Pil_Ecc_ClearCramEccFatalErrorStatus();
			break;

		default:
			/* 何もしない */
			break;
	}
}

/*----------------------------------------------------------------------------------------------*/
/*	Get ECC Error Status Function																*/
/*	return		: Error Detect Status(=0:not error detect, !=0:error detect)					*/
/*	parameters	: RAM Type																		*/
/*----------------------------------------------------------------------------------------------*/
ZORN	ErrH_Ecc_GetEccErrorStatus( U1 t_u1RamType )
{
	ZORN	t_udErrDtctStatus;

	t_udErrDtctStatus = (ZORN)u4ERRH_ECC_ERR_NOTDETECT;

	if ( t_u1RamType == u1ERRH_ECC_RAMTYPE_CRAM )
	{
		t_udErrDtctStatus = Pil_Ecc_GetCramEccFatalErrorStatus();
	}
	return ( t_udErrDtctStatus );
}

/*----------------------------------------------------------------------------------------------*/
/*	Request Register Check Function																*/
/*	return		: Register Check Result															*/
/*	parameters	: *ConfigTable																	*/
/*----------------------------------------------------------------------------------------------*/
U1	ErrH_Ecc_CheckReg_ASIL( const ErrH_RegCheckConfigType *t_pcstConfigTable )
{
	volatile	void*							t_pvdAddress;		/* レジスタアドレス */
				U4								t_u4ExpectValue;	/* レジスタ期待値 */
				U4								t_u4Mask;			/* レジスタマスク */
				U2								t_u2RegCheckNum;	/* レジスタ診断番号 */
				U1								t_u1Result;			/* 戻り値 */

	t_u1Result = (U1)OK;											/* OKで初期化 */
	
	DI_ALL();
	
	if ( s_u1ErrH_Ecc_DisableRefreshEccReg == (U1)OFF )
	{
		if ( s_u1ErrH_Ecc_RegCheckStatus == u1ERRH_ECC_REGCHECK_STS_COMPLETED )
		{
			s_u1ErrH_Ecc_RegCheckStatus = u1ERRH_ECC_REGCHECK_STS_BUSY;
			s_u2ErrH_Ecc_RegCheckNum = (U2)0U;
		}

		t_u2RegCheckNum = s_u2ErrH_Ecc_RegCheckNum;					/* 現在の診断番号を取得 */

		if ( t_u2RegCheckNum < t_pcstConfigTable->u2RegNum )		/* レジスタ診断テーブル数より小さい場合 */
		{
			t_pvdAddress = t_pcstConfigTable->pcstRegData[ t_u2RegCheckNum ].pvdAddress;
			t_u4ExpectValue = t_pcstConfigTable->pcstRegData[ t_u2RegCheckNum ].u4ExpectValue;
			t_u4Mask = t_pcstConfigTable->pcstRegData[ t_u2RegCheckNum ].u4Mask;

			t_u1Result = ErrH_Ecc_Compare4ByteMask( (volatile const U4*)t_pvdAddress, t_u4ExpectValue, t_u4Mask );

			if ( t_u1Result == (U1)NG )
			{
				switch ( t_pcstConfigTable->pcstRegData[ t_u2RegCheckNum ].u1Prot )
				{
					case (U1)ERRH_ECC_REG_4BYTE_ECC_PROT:
						ErrH_Ecc_Reg_RestoreEccProt4ByteMask( (volatile U4*)t_pvdAddress, t_u4ExpectValue, t_u4Mask );
						break;
		
					case (U1)ERRH_ECC_REG_4BYTE_PB5ECC_APEC_PROT:
						ErrH_Ecc_Reg_RestorePb5eccApecProt4ByteMask( (volatile U4*)t_pvdAddress, t_u4ExpectValue, t_u4Mask );
						break;

					default:
						/* 処理無し */
						break;
				}
			}

			t_u2RegCheckNum++;
			s_u2ErrH_Ecc_RegCheckNum = t_u2RegCheckNum;

			if ( s_u2ErrH_Ecc_RegCheckNum < t_pcstConfigTable->u2RegNum )											/* レジスタ診断テーブルサイズより小さい場合 */
			{
				t_u1Result = t_u1Result | u1ERRH_ECC_REGCHECK_BUSY;													/* 4～7bit目にサブモジュールレジスタ診断中(0001B)をセット(本処理前は4～7bit目として0000Bを期待) */
			}
			else
			{
				/* t_u1Resultの4～7bit目にサブモジュールレジスタ診断開始待ち(0000B)をセット(本処理前は4～7bit目として0000Bを期待)。冗長となるため、処理なし */
				s_u1ErrH_Ecc_RegCheckStatus = u1ERRH_ECC_REGCHECK_STS_COMPLETED;
			}
		}
		else
		{
			t_u1Result = ( t_u1Result & u1ERRH_ECC_CHECKRESULT_MASK_UPPER4BIT ) | u1ERRH_ECC_REGCHECK_COMPLETED;	/* 4～7bit目に0000B(診断開始待ち)をセット */
			s_u1ErrH_Ecc_RegCheckStatus = u1ERRH_ECC_REGCHECK_STS_COMPLETED;
		}
	}
	
	EI_ALL();

	return( t_u1Result );
}

/*----------------------------------------------------------------------------------------------*/
/* Scheduled / Event Functions																	*/
/*----------------------------------------------------------------------------------------------*/
/************************************************************************************************/
/* Function			:	Initialization															*/
/* Schedule			:	Init																	*/
/* Parameters(in)	:	none																	*/
/************************************************************************************************/
void	ErrH_Ecc_Init( void )
{
	/* ECC制御レジスタのKey Code Protection解除 */
	REG_ECC_ECCKC.unKCPROT.u4Data = (U4)ECC_ECCDF_KCPROT_KCE_ENABLE;
	Bswlib_Sync_Pipeline_4( REG_ECC_ECCKC.unKCPROT.u4Data );

	/* Code Flash ECC 設定 */ /* qac 2987対応のため、内部関数化しない */
	/* CFPECCCTL - ECC Control Register(Reset初期値と同じ値) */
	REG_ECC_ECCCNT_CFP_PE0CL0.unCFPECCCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_CFP_PE0CL0_ECCCTL_SECDIS * (U4)ECC_ECCCNT_CFP_PE0CL0_ECCCTL_ENABLE )
													   + ( (U4)ECC_ECCCNT_CFP_PE0CL0_ECCCTL_ECCDIS * (U4)ECC_ECCCNT_CFP_PE0CL0_ECCCTL_ENABLE ) );

	REG_ECC_ECCCNT_CFP_PE1CL0.unCFPECCCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_CFP_PE1CL0_ECCCTL_SECDIS * (U4)ECC_ECCCNT_CFP_PE1CL0_ECCCTL_ENABLE )
													   + ( (U4)ECC_ECCCNT_CFP_PE1CL0_ECCCTL_ECCDIS * (U4)ECC_ECCCNT_CFP_PE1CL0_ECCCTL_ENABLE ) );

#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B6 ) || ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_DUALCORE ) ) )	/* U2B6、またはU2B10かつ2コア構成 */
	REG_ECC_ECCCNT_CFP_PE2CL1.unCFPECCCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_CFP_PE2CL1_ECCCTL_SECDIS * (U4)ECC_ECCCNT_CFP_PE2CL1_ECCCTL_DISABLE )
													   + ( (U4)ECC_ECCCNT_CFP_PE2CL1_ECCCTL_ECCDIS * (U4)ECC_ECCCNT_CFP_PE2CL1_ECCCTL_DISABLE ) );
#else /* U2B10かつ3コア構成以上 */
	REG_ECC_ECCCNT_CFP_PE2CL1.unCFPECCCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_CFP_PE2CL1_ECCCTL_SECDIS * (U4)ECC_ECCCNT_CFP_PE2CL1_ECCCTL_ENABLE )
													   + ( (U4)ECC_ECCCNT_CFP_PE2CL1_ECCCTL_ECCDIS * (U4)ECC_ECCCNT_CFP_PE2CL1_ECCCTL_ENABLE ) );
#endif

#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
	REG_ECC_ECCCNT_CFP_PE3CL1.unCFPECCCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_CFP_PE3CL1_ECCCTL_SECDIS * (U4)ECC_ECCCNT_CFP_PE3CL1_ECCCTL_DISABLE )
													   + ( (U4)ECC_ECCCNT_CFP_PE3CL1_ECCCTL_ECCDIS * (U4)ECC_ECCCNT_CFP_PE3CL1_ECCCTL_DISABLE ) );
#endif

	/* CFCECCCTL - ECC Control Register(Reset初期値と同じ値) */
	REG_ECC_ECCCNT_CFCCL0.unCFCECCCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_CFCCL0_CFCECCCTL_BLANKMASKENABLE * (U4)ECC_ECCCNT_CFCCL0_CFCECCCTL_ENABLE )
													   + ( (U4)ECC_ECCCNT_CFCCL0_CFCECCCTL_APEDIS * (U4)ECC_ECCCNT_CFCCL0_CFCECCCTL_ENABLE )
													   + ( (U4)ECC_ECCCNT_CFCCL0_CFCECCCTL_SECDIS * (U4)ECC_ECCCNT_CFCCL0_CFCECCCTL_ENABLE )
													   + ( (U4)ECC_ECCCNT_CFCCL0_CFCECCCTL_ECCDIS * (U4)ECC_ECCCNT_CFCCL0_CFCECCCTL_ENABLE ) );

#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
	REG_ECC_ECCCNT_CFCCL1.unCFCECCCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_CFCCL1_CFCECCCTL_BLANKMASKENABLE * (U4)ECC_ECCCNT_CFCCL1_CFCECCCTL_ENABLE )
													   + ( (U4)ECC_ECCCNT_CFCCL1_CFCECCCTL_APEDIS * (U4)ECC_ECCCNT_CFCCL1_CFCECCCTL_ENABLE )
													   + ( (U4)ECC_ECCCNT_CFCCL1_CFCECCCTL_SECDIS * (U4)ECC_ECCCNT_CFCCL1_CFCECCCTL_ENABLE )
													   + ( (U4)ECC_ECCCNT_CFCCL1_CFCECCCTL_ECCDIS * (U4)ECC_ECCCNT_CFCCL1_CFCECCCTL_ENABLE ) );
#endif

	/* CFSECCCTL - ECC Control Register(Reset初期値と同じ値) */
	REG_ECC_ECCCNT_CFS.unCFSECCCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_CFS_CFSECCCTL_SECDIS * (U4)ECC_ECCCNT_CFS_CFSECCCTL_ENABLE )
												+ ( (U4)ECC_ECCCNT_CFS_CFSECCCTL_ECCDIS * (U4)ECC_ECCCNT_CFS_CFSECCCTL_ENABLE ) );

	/* CF_ERRINT - Error Notification Control Register */
	REG_ECC_MECCCAP_CFL.unCF_ERRINT.u4Data = (U4)( ( (U4)ECC_MECCCAP_CFL_CF_ERRINT_SEOVFIE * (U4)ECC_MECCCAP_CFL_CF_ERRINT_ENABLE  )
												 + ( (U4)ECC_MECCCAP_CFL_CF_ERRINT_APEIE   * (U4)ECC_MECCCAP_CFL_CF_ERRINT_ENABLE  )
												 + ( (U4)ECC_MECCCAP_CFL_CF_ERRINT_DEDIE   * (U4)ECC_MECCCAP_CFL_CF_ERRINT_ENABLE  )
												 + ( (U4)ECC_MECCCAP_CFL_CF_ERRINT_SEDIE   * (U4)ECC_MECCCAP_CFL_CF_ERRINT_DISABLE ) );

	/* Data Flash ECC 設定 */
	ErrH_Ecc_DF_Init();

	/* Local RAM ECC 設定 */ /* qac 2987対応のため、内部関数化しない */
	/* LRECCCTL - ECC Control Register(Reset初期値と同じ値) */
	REG_ECC_ECCCNT_LR_PE0CL0.unLRECCCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_LR_PE0CL0_ECCCTL_AFEDIS * (U4)ECC_ECCCNT_LR_PE0CL0_ECCCTL_ENABLE )
													 + ( (U4)ECC_ECCCNT_LR_PE0CL0_ECCCTL_SECDIS * (U4)ECC_ECCCNT_LR_PE0CL0_ECCCTL_ENABLE )
													 + ( (U4)ECC_ECCCNT_LR_PE0CL0_ECCCTL_ECCDIS * (U4)ECC_ECCCNT_LR_PE0CL0_ECCCTL_ENABLE ) );

	REG_ECC_ECCCNT_LR_PE1CL0.unLRECCCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_LR_PE1CL0_ECCCTL_AFEDIS * (U4)ECC_ECCCNT_LR_PE1CL0_ECCCTL_ENABLE )
													 + ( (U4)ECC_ECCCNT_LR_PE1CL0_ECCCTL_SECDIS * (U4)ECC_ECCCNT_LR_PE1CL0_ECCCTL_ENABLE )
													 + ( (U4)ECC_ECCCNT_LR_PE1CL0_ECCCTL_ECCDIS * (U4)ECC_ECCCNT_LR_PE1CL0_ECCCTL_ENABLE ) );

#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_TRIPLECORE ) )												/* U2B10かつ3コア構成 */
	REG_ECC_ECCCNT_LR_PE2CL1.unLRECCCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_LR_PE2CL1_ECCCTL_AFEDIS * (U4)ECC_ECCCNT_LR_PE2CL1_ECCCTL_ENABLE )
													 + ( (U4)ECC_ECCCNT_LR_PE2CL1_ECCCTL_SECDIS * (U4)ECC_ECCCNT_LR_PE2CL1_ECCCTL_ENABLE )
													 + ( (U4)ECC_ECCCNT_LR_PE2CL1_ECCCTL_ECCDIS * (U4)ECC_ECCCNT_LR_PE2CL1_ECCCTL_ENABLE ) );
#endif

	/* LRECCTSTCTL - ECC Test Control Register(Reset初期値と同じ値) */
	REG_ECC_ECCCNT_LR_PE0CL0.unLRECCTSTCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_LR_PE0CL0_TCTL_TST * (U4)ECC_ECCCNT_LR_PE0CL0_TCTL_TST_NORMAL )
														+ ( (U4)ECC_ECCCNT_LR_PE0CL0_TCTL_DS * (U4)ECC_ECCCNT_LR_PE0CL0_TCTL_DS_DATA   ) );

	REG_ECC_ECCCNT_LR_PE1CL0.unLRECCTSTCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_LR_PE1CL0_TCTL_TST * (U4)ECC_ECCCNT_LR_PE1CL0_TCTL_TST_NORMAL )
														+ ( (U4)ECC_ECCCNT_LR_PE1CL0_TCTL_DS * (U4)ECC_ECCCNT_LR_PE1CL0_TCTL_DS_DATA   ) );

#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_TRIPLECORE ) )												/* U2B10かつ3コア構成 */
	REG_ECC_ECCCNT_LR_PE2CL1.unLRECCTSTCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_LR_PE2CL1_TCTL_TST * (U4)ECC_ECCCNT_LR_PE2CL1_TCTL_TST_NORMAL )
														+ ( (U4)ECC_ECCCNT_LR_PE2CL1_TCTL_DS * (U4)ECC_ECCCNT_LR_PE2CL1_TCTL_DS_DATA   ) );
#endif

	/* LR0_ERRINT - Error Notification Control Register(Reset初期値と同じ値) */
	REG_ECC_MECCCAP_LR_PE0CL0.unLR0_ERRINT.u4Data = (U4)( ( (U4)ECC_MECCCAP_LR_PE0CL0_ERINT_SEOVFIE * (U4)ECC_MECCCAP_LR_PE0CL0_ERRINT_ENABLE )
														+ ( (U4)ECC_MECCCAP_LR_PE0CL0_ERINT_AFEIE   * (U4)ECC_MECCCAP_LR_PE0CL0_ERRINT_ENABLE )
														+ ( (U4)ECC_MECCCAP_LR_PE0CL0_ERINT_DEDIE   * (U4)ECC_MECCCAP_LR_PE0CL0_ERRINT_ENABLE )
														+ ( (U4)ECC_MECCCAP_LR_PE0CL0_ERINT_SEDIE   * (U4)ECC_MECCCAP_LR_PE0CL0_ERRINT_ENABLE ) );

	REG_ECC_MECCCAP_LR_PE1CL0.unLR0_ERRINT.u4Data = (U4)( ( (U4)ECC_MECCCAP_LR_PE1CL0_ERINT_SEOVFIE * (U4)ECC_MECCCAP_LR_PE1CL0_ERRINT_ENABLE )
														+ ( (U4)ECC_MECCCAP_LR_PE1CL0_ERINT_AFEIE   * (U4)ECC_MECCCAP_LR_PE1CL0_ERRINT_ENABLE )
														+ ( (U4)ECC_MECCCAP_LR_PE1CL0_ERINT_DEDIE   * (U4)ECC_MECCCAP_LR_PE1CL0_ERRINT_ENABLE )
														+ ( (U4)ECC_MECCCAP_LR_PE1CL0_ERINT_SEDIE   * (U4)ECC_MECCCAP_LR_PE1CL0_ERRINT_ENABLE ) );

#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B6 ) || ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_DUALCORE ) ) )	/* U2B6、またはU2B10かつ2コア構成 */
	REG_ECC_MECCCAP_LR_PE2CL1.unLR0_ERRINT.u4Data = (U4)( ( (U4)ECC_MECCCAP_LR_PE2CL1_ERINT_SEOVFIE * (U4)ECC_MECCCAP_LR_PE2CL1_ERRINT_DISABLE )
														+ ( (U4)ECC_MECCCAP_LR_PE2CL1_ERINT_AFEIE   * (U4)ECC_MECCCAP_LR_PE2CL1_ERRINT_DISABLE )
														+ ( (U4)ECC_MECCCAP_LR_PE2CL1_ERINT_DEDIE   * (U4)ECC_MECCCAP_LR_PE2CL1_ERRINT_DISABLE )
														+ ( (U4)ECC_MECCCAP_LR_PE2CL1_ERINT_SEDIE   * (U4)ECC_MECCCAP_LR_PE2CL1_ERRINT_DISABLE ) );
#else /* U2B10かつ3コア構成以上 */
	REG_ECC_MECCCAP_LR_PE2CL1.unLR0_ERRINT.u4Data = (U4)( ( (U4)ECC_MECCCAP_LR_PE2CL1_ERINT_SEOVFIE * (U4)ECC_MECCCAP_LR_PE2CL1_ERRINT_ENABLE )
														+ ( (U4)ECC_MECCCAP_LR_PE2CL1_ERINT_AFEIE   * (U4)ECC_MECCCAP_LR_PE2CL1_ERRINT_ENABLE )
														+ ( (U4)ECC_MECCCAP_LR_PE2CL1_ERINT_DEDIE   * (U4)ECC_MECCCAP_LR_PE2CL1_ERRINT_ENABLE )
														+ ( (U4)ECC_MECCCAP_LR_PE2CL1_ERINT_SEDIE   * (U4)ECC_MECCCAP_LR_PE2CL1_ERRINT_ENABLE ) );
#endif

#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_TRIPLECORE ) )												/* U2B10かつ3コア構成 */
	REG_ECC_MECCCAP_LR_PE3CL1.unLR0_ERRINT.u4Data = (U4)( ( (U4)ECC_MECCCAP_LR_PE3CL1_ERINT_SEOVFIE * (U4)ECC_MECCCAP_LR_PE3CL1_ERRINT_DISABLE )
														+ ( (U4)ECC_MECCCAP_LR_PE3CL1_ERINT_AFEIE   * (U4)ECC_MECCCAP_LR_PE3CL1_ERRINT_DISABLE )
														+ ( (U4)ECC_MECCCAP_LR_PE3CL1_ERINT_DEDIE   * (U4)ECC_MECCCAP_LR_PE3CL1_ERRINT_DISABLE )
														+ ( (U4)ECC_MECCCAP_LR_PE3CL1_ERINT_SEDIE   * (U4)ECC_MECCCAP_LR_PE3CL1_ERRINT_DISABLE ) );
#endif

	/* LR1_ERRINT - Error Notification Control Register(Reset初期値と同じ値) */
	REG_ECC_MECCCAP_LRA.unLR1_ERRINT.u4Data = (U4)( ( (U4)ECC_MECCCAP_LRA_LR1_ERRINT_SEOVFIE * (U4)ECC_MECCCAP_LRA_LR1_ERRINT_ENABLE )
												  + ( (U4)ECC_MECCCAP_LRA_LR1_ERRINT_DEDIE   * (U4)ECC_MECCCAP_LRA_LR1_ERRINT_ENABLE )
												  + ( (U4)ECC_MECCCAP_LRA_LR1_ERRINT_SEDIE   * (U4)ECC_MECCCAP_LRA_LR1_ERRINT_ENABLE ) );

	/* Cluster RAM ECC 設定 */
	ErrH_Ecc_Cram_Init();

	/* Instruction cache ECC 設定 */ /* qac 2987対応のため、内部関数化しない */
	/* ITECCCTL - ECC Control Register(Reset初期値と同じ値) */
	REG_ECC_ECCCNT_IT_PE0CL0.unITECCCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_IT_PE0CL0_ECCCTL_AFEDIS * (U4)ECC_ECCCNT_IT_PE0CL0_ECCCTL_ENABLE )
													 + ( (U4)ECC_ECCCNT_IT_PE0CL0_ECCCTL_ECCDIS * (U4)ECC_ECCCNT_IT_PE0CL0_ECCCTL_ENABLE ) );

	REG_ECC_ECCCNT_IT_PE1CL0.unITECCCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_IT_PE1CL0_ECCCTL_AFEDIS * (U4)ECC_ECCCNT_IT_PE1CL0_ECCCTL_ENABLE )
													 + ( (U4)ECC_ECCCNT_IT_PE1CL0_ECCCTL_ECCDIS * (U4)ECC_ECCCNT_IT_PE1CL0_ECCCTL_ENABLE ) );

#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_TRIPLECORE ) )												/* U2B10かつ3コア構成 */
	REG_ECC_ECCCNT_IT_PE2CL1.unITECCCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_IT_PE2CL1_ECCCTL_AFEDIS * (U4)ECC_ECCCNT_IT_PE2CL1_ECCCTL_ENABLE )
													 + ( (U4)ECC_ECCCNT_IT_PE2CL1_ECCCTL_ECCDIS * (U4)ECC_ECCCNT_IT_PE2CL1_ECCCTL_ENABLE ) );
#endif

	/* IDECCCTL - ECC Control Register(Reset初期値と同じ値) */
	REG_ECC_ECCCNT_ID_PE0CL0.unIDECCCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_ID_PE0CL0_ECCCTL_AFEDIS * (U4)ECC_ECCCNT_ID_PE0CL0_ECCCTL_ENABLE )
													 + ( (U4)ECC_ECCCNT_ID_PE0CL0_ECCCTL_ECCDIS * (U4)ECC_ECCCNT_ID_PE0CL0_ECCCTL_ENABLE ) );

	REG_ECC_ECCCNT_ID_PE1CL0.unIDECCCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_ID_PE1CL0_ECCCTL_AFEDIS * (U4)ECC_ECCCNT_ID_PE1CL0_ECCCTL_ENABLE )
													 + ( (U4)ECC_ECCCNT_ID_PE1CL0_ECCCTL_ECCDIS * (U4)ECC_ECCCNT_ID_PE1CL0_ECCCTL_ENABLE ) );

#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_TRIPLECORE ) )												/* U2B10かつ3コア構成 */
	REG_ECC_ECCCNT_ID_PE2CL1.unIDECCCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_ID_PE2CL1_ECCCTL_AFEDIS * (U4)ECC_ECCCNT_ID_PE2CL1_ECCCTL_ENABLE )
													 + ( (U4)ECC_ECCCNT_ID_PE2CL1_ECCCTL_ECCDIS * (U4)ECC_ECCCNT_ID_PE2CL1_ECCCTL_ENABLE ) );
#endif

	/* IT_ERRINT - Error Notification Control Register(Reset初期値と同じ値) */
	REG_ECC_MECCCAP_IT_PE0CL0.unIT_ERRINT.u4Data = (U4)( ( (U4)ECC_MECCCAP_IT_PE0CL0_ERRINT_AFEIE * (U4)ECC_MECCCAP_IT_PE0CL0_ERRINT_ENABLE )
													   + ( (U4)ECC_MECCCAP_IT_PE0CL0_ERRINT_DEDIE * (U4)ECC_MECCCAP_IT_PE0CL0_ERRINT_ENABLE )
													   + ( (U4)ECC_MECCCAP_IT_PE0CL0_ERRINT_SEDIE * (U4)ECC_MECCCAP_IT_PE0CL0_ERRINT_ENABLE ) );

	REG_ECC_MECCCAP_IT_PE1CL0.unIT_ERRINT.u4Data = (U4)( ( (U4)ECC_MECCCAP_IT_PE1CL0_ERRINT_AFEIE * (U4)ECC_MECCCAP_IT_PE1CL0_ERRINT_ENABLE )
													   + ( (U4)ECC_MECCCAP_IT_PE1CL0_ERRINT_DEDIE * (U4)ECC_MECCCAP_IT_PE1CL0_ERRINT_ENABLE )
													   + ( (U4)ECC_MECCCAP_IT_PE1CL0_ERRINT_SEDIE * (U4)ECC_MECCCAP_IT_PE1CL0_ERRINT_ENABLE ) );

#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B6 ) || ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_DUALCORE ) ) )	/* U2B6、またはU2B10かつ2コア構成 */
	REG_ECC_MECCCAP_IT_PE2CL1.unIT_ERRINT.u4Data = (U4)( ( (U4)ECC_MECCCAP_IT_PE2CL1_ERRINT_AFEIE * (U4)ECC_MECCCAP_IT_PE2CL1_ERRINT_DISABLE )
													   + ( (U4)ECC_MECCCAP_IT_PE2CL1_ERRINT_DEDIE * (U4)ECC_MECCCAP_IT_PE2CL1_ERRINT_DISABLE )
													   + ( (U4)ECC_MECCCAP_IT_PE2CL1_ERRINT_SEDIE * (U4)ECC_MECCCAP_IT_PE2CL1_ERRINT_DISABLE ) );
#else /* U2B10かつ3コア構成以上 */
	REG_ECC_MECCCAP_IT_PE2CL1.unIT_ERRINT.u4Data = (U4)( ( (U4)ECC_MECCCAP_IT_PE2CL1_ERRINT_AFEIE * (U4)ECC_MECCCAP_IT_PE2CL1_ERRINT_ENABLE )
													   + ( (U4)ECC_MECCCAP_IT_PE2CL1_ERRINT_DEDIE * (U4)ECC_MECCCAP_IT_PE2CL1_ERRINT_ENABLE )
													   + ( (U4)ECC_MECCCAP_IT_PE2CL1_ERRINT_SEDIE * (U4)ECC_MECCCAP_IT_PE2CL1_ERRINT_ENABLE ) );
#endif

#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_TRIPLECORE ) )												/* U2B10かつ3コア構成 */
	REG_ECC_MECCCAP_IT_PE3CL1.unIT_ERRINT.u4Data = (U4)( ( (U4)ECC_MECCCAP_IT_PE3CL1_ERRINT_AFEIE * (U4)ECC_MECCCAP_IT_PE3CL1_ERRINT_DISABLE )
													   + ( (U4)ECC_MECCCAP_IT_PE3CL1_ERRINT_DEDIE * (U4)ECC_MECCCAP_IT_PE3CL1_ERRINT_DISABLE )
													   + ( (U4)ECC_MECCCAP_IT_PE3CL1_ERRINT_SEDIE * (U4)ECC_MECCCAP_IT_PE3CL1_ERRINT_DISABLE ) );
#endif

	/* ID_ERRINT - Error Notification Control Register(Reset初期値と同じ値) */
	REG_ECC_MECCCAP_ID_PE0CL0.unID_ERRINT.u4Data = (U4)( ( (U4)ECC_MECCCAP_ID_PE0CL0_ERRINT_AFEIE * (U4)ECC_MECCCAP_ID_PE0CL0_ERRINT_ENABLE )
													   + ( (U4)ECC_MECCCAP_ID_PE0CL0_ERRINT_DEDIE * (U4)ECC_MECCCAP_ID_PE0CL0_ERRINT_ENABLE )
													   + ( (U4)ECC_MECCCAP_ID_PE0CL0_ERRINT_SEDIE * (U4)ECC_MECCCAP_ID_PE0CL0_ERRINT_ENABLE ) );

	REG_ECC_MECCCAP_ID_PE1CL0.unID_ERRINT.u4Data = (U4)( ( (U4)ECC_MECCCAP_ID_PE1CL0_ERRINT_AFEIE * (U4)ECC_MECCCAP_ID_PE1CL0_ERRINT_ENABLE )
													   + ( (U4)ECC_MECCCAP_ID_PE1CL0_ERRINT_DEDIE * (U4)ECC_MECCCAP_ID_PE1CL0_ERRINT_ENABLE )
													   + ( (U4)ECC_MECCCAP_ID_PE1CL0_ERRINT_SEDIE * (U4)ECC_MECCCAP_ID_PE1CL0_ERRINT_ENABLE ) );

#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B6 ) || ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_DUALCORE ) ) )	/* U2B6、またはU2B10かつ2コア構成 */
	REG_ECC_MECCCAP_ID_PE2CL1.unID_ERRINT.u4Data = (U4)( ( (U4)ECC_MECCCAP_ID_PE2CL1_ERRINT_AFEIE * (U4)ECC_MECCCAP_ID_PE2CL1_ERRINT_DISABLE )
													   + ( (U4)ECC_MECCCAP_ID_PE2CL1_ERRINT_DEDIE * (U4)ECC_MECCCAP_ID_PE2CL1_ERRINT_DISABLE )
													   + ( (U4)ECC_MECCCAP_ID_PE2CL1_ERRINT_SEDIE * (U4)ECC_MECCCAP_ID_PE2CL1_ERRINT_DISABLE ) );
#else /* U2B10かつ3コア構成以上 */
	REG_ECC_MECCCAP_ID_PE2CL1.unID_ERRINT.u4Data = (U4)( ( (U4)ECC_MECCCAP_ID_PE2CL1_ERRINT_AFEIE * (U4)ECC_MECCCAP_ID_PE2CL1_ERRINT_ENABLE )
													   + ( (U4)ECC_MECCCAP_ID_PE2CL1_ERRINT_DEDIE * (U4)ECC_MECCCAP_ID_PE2CL1_ERRINT_ENABLE )
													   + ( (U4)ECC_MECCCAP_ID_PE2CL1_ERRINT_SEDIE * (U4)ECC_MECCCAP_ID_PE2CL1_ERRINT_ENABLE ) );
#endif

#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_TRIPLECORE ) )												/* U2B10かつ3コア構成 */
	REG_ECC_MECCCAP_ID_PE3CL1.unID_ERRINT.u4Data = (U4)( ( (U4)ECC_MECCCAP_ID_PE3CL1_ERRINT_AFEIE * (U4)ECC_MECCCAP_ID_PE3CL1_ERRINT_DISABLE )
													   + ( (U4)ECC_MECCCAP_ID_PE3CL1_ERRINT_DEDIE * (U4)ECC_MECCCAP_ID_PE3CL1_ERRINT_DISABLE )
													   + ( (U4)ECC_MECCCAP_ID_PE3CL1_ERRINT_SEDIE * (U4)ECC_MECCCAP_ID_PE3CL1_ERRINT_DISABLE ) );
#endif

	/* RAM for DTS、sDMAC (Descriptor、Data) ECC 設定 */ /* qac 2987対応のため、内部関数化しない */
	/* DRECCCTL - ECC Control Register(Reset初期値と同じ値) */
	REG_ECC_ECCCNT_DTS.unDRECCCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_DTS_DRECCCTL_AFEDIS * (U4)ECC_ECCCNT_DTS_DRECCCTL_ENABLE )
											   + ( (U4)ECC_ECCCNT_DTS_DRECCCTL_SECDIS * (U4)ECC_ECCCNT_DTS_DRECCCTL_ENABLE )
											   + ( (U4)ECC_ECCCNT_DTS_DRECCCTL_ECCDIS * (U4)ECC_ECCCNT_DTS_DRECCCTL_ENABLE ) );

	/* DRECCTSTCTL - ECC Test Control Register(Reset初期値と同じ値) */
	REG_ECC_ECCCNT_DTS.unDRECCTSTCTL.u4Data = (U4)ECC_ECCCNT_DTS_DRECCTSTCTL_ECCTST * (U4)ECC_ECCCNT_DTS_TSTCTL_ECCTST_NORMAL;

	/* DEECCCTL - ECC Control Register(Reset初期値と同じ値) */
	REG_ECC_ECCCNT_DMDE0.unDEECCCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_DMDE0_DEECCCTL_AFEDIS * (U4)ECC_ECCCNT_DMDE0_DEECCCTL_ENABLE )
												 + ( (U4)ECC_ECCCNT_DMDE0_DEECCCTL_SECDIS * (U4)ECC_ECCCNT_DMDE0_DEECCCTL_ENABLE )
												 + ( (U4)ECC_ECCCNT_DMDE0_DEECCCTL_ECCDIS * (U4)ECC_ECCCNT_DMDE0_DEECCCTL_ENABLE ) );

#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
	REG_ECC_ECCCNT_DMDE1.unDEECCCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_DMDE1_DEECCCTL_AFEDIS * (U4)ECC_ECCCNT_DMDE1_DEECCCTL_ENABLE )
												 + ( (U4)ECC_ECCCNT_DMDE1_DEECCCTL_SECDIS * (U4)ECC_ECCCNT_DMDE1_DEECCCTL_ENABLE )
												 + ( (U4)ECC_ECCCNT_DMDE1_DEECCCTL_ECCDIS * (U4)ECC_ECCCNT_DMDE1_DEECCCTL_ENABLE ) );
#endif

	/* DEECCTSTCTL - ECC Test Control Register(Reset初期値と同じ値) */
	REG_ECC_ECCCNT_DMDE0.unDEECCTSTCTL.u4Data = (U4)ECC_ECCCNT_DMDE0_DEECCTSTCTL_ECCTST * (U4)ECC_ECCCNT_DMDE0_TSTCTL_TST_NORMAL;

#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
	REG_ECC_ECCCNT_DMDE1.unDEECCTSTCTL.u4Data = (U4)ECC_ECCCNT_DMDE1_DEECCTSTCTL_ECCTST * (U4)ECC_ECCCNT_DMDE1_TSTCTL_TST_NORMAL;
#endif

	/* DAECCCTL - ECC Control Register(Reset初期値と同じ値) */
	REG_ECC_ECCCNT_DMDA0.unDAECCCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_DMDA0_DAECCCTL_SECDIS * (U4)ECC_ECCCNT_DMDA0_DAECCCTL_ENABLE )
												 + ( (U4)ECC_ECCCNT_DMDA0_DAECCCTL_ECCDIS * (U4)ECC_ECCCNT_DMDA0_DAECCCTL_ENABLE ) );

#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
	REG_ECC_ECCCNT_DMDA1.unDAECCCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_DMDA1_DAECCCTL_SECDIS * (U4)ECC_ECCCNT_DMDA1_DAECCCTL_ENABLE )
												 + ( (U4)ECC_ECCCNT_DMDA1_DAECCCTL_ECCDIS * (U4)ECC_ECCCNT_DMDA1_DAECCCTL_ENABLE ) );
#endif

	/* DAECCTSTCTL - ECC Test Control Register(Reset初期値と同じ値) */
	REG_ECC_ECCCNT_DMDA0.unDAECCTSTCTL.u4Data = (U4)ECC_ECCCNT_DMDA0_DAECCTSTCTL_ECCTST * (U4)ECC_ECCCNT_DMDA0_TSTCTL_TST_NORMAL;

#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
	REG_ECC_ECCCNT_DMDA1.unDAECCTSTCTL.u4Data = (U4)ECC_ECCCNT_DMDA1_DAECCTSTCTL_ECCTST * (U4)ECC_ECCCNT_DMDA1_TSTCTL_TST_NORMAL;
#endif

	/* DR_ERRINT - Error Notification Control Register */
	/* ECC 1bitエラーは自動訂正可能のため通知しない */
	REG_ECC_MECCCAP_DTS.unDR_ERRINT.u4Data = (U4)( ( (U4)ECC_MECCCAP_DTS_DR_ERRINT_SEOVFIE * (U4)ECC_MECCCAP_DTS_DR_ERRINT_ENABLE  )
												 + ( (U4)ECC_MECCCAP_DTS_DR_ERRINT_AFEIE   * (U4)ECC_MECCCAP_DTS_DR_ERRINT_ENABLE  )
												 + ( (U4)ECC_MECCCAP_DTS_DR_ERRINT_DEDIE   * (U4)ECC_MECCCAP_DTS_DR_ERRINT_ENABLE  )
												 + ( (U4)ECC_MECCCAP_DTS_DR_ERRINT_SEDIE   * (U4)ECC_MECCCAP_DTS_DR_ERRINT_DISABLE ) );

	/* DE_ERRINT - Error Notification Control Register */
	/* ECC 1bitエラーは自動訂正可能のため通知しない */
	REG_ECC_MECCCAP_DMDE0.unDE_ERRINT.u4Data = (U4)( ( (U4)ECC_MECCCAP_DMDE0_DE_ERRINT_SEOVFIE * (U4)ECC_MECCCAP_DMDE0_DE_ERRINT_ENABLE  )
												   + ( (U4)ECC_MECCCAP_DMDE0_DE_ERRINT_AFEIE   * (U4)ECC_MECCCAP_DMDE0_DE_ERRINT_ENABLE  )
												   + ( (U4)ECC_MECCCAP_DMDE0_DE_ERRINT_DEDIE   * (U4)ECC_MECCCAP_DMDE0_DE_ERRINT_ENABLE  )
												   + ( (U4)ECC_MECCCAP_DMDE0_DE_ERRINT_SEDIE   * (U4)ECC_MECCCAP_DMDE0_DE_ERRINT_DISABLE ) );

#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
	REG_ECC_MECCCAP_DMDE1.unDE_ERRINT.u4Data = (U4)( ( (U4)ECC_MECCCAP_DMDE1_DE_ERRINT_SEOVFIE * (U4)ECC_MECCCAP_DMDE1_DE_ERRINT_ENABLE  )
												   + ( (U4)ECC_MECCCAP_DMDE1_DE_ERRINT_AFEIE   * (U4)ECC_MECCCAP_DMDE1_DE_ERRINT_ENABLE  )
												   + ( (U4)ECC_MECCCAP_DMDE1_DE_ERRINT_DEDIE   * (U4)ECC_MECCCAP_DMDE1_DE_ERRINT_ENABLE  )
												   + ( (U4)ECC_MECCCAP_DMDE1_DE_ERRINT_SEDIE   * (U4)ECC_MECCCAP_DMDE1_DE_ERRINT_DISABLE ) );
#endif

	/* DA_ERRINT - Error Notification Control Register */
	/* ECC 1bitエラーは自動訂正可能のため通知しない */
	REG_ECC_MECCCAP_DMDA0.unDA_ERRINT.u4Data = (U4)( ( (U4)ECC_MECCCAP_DMDA0_DA_ERRINT_SEOVFIE * (U4)ECC_MECCCAP_DMDA0_DA_ERRINT_ENABLE  )
												   + ( (U4)ECC_MECCCAP_DMDA0_DA_ERRINT_DEDIE   * (U4)ECC_MECCCAP_DMDA0_DA_ERRINT_ENABLE  )
												   + ( (U4)ECC_MECCCAP_DMDA0_DA_ERRINT_SEDIE   * (U4)ECC_MECCCAP_DMDA0_DA_ERRINT_DISABLE ) );

#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
	REG_ECC_MECCCAP_DMDA1.unDA_ERRINT.u4Data = (U4)( ( (U4)ECC_MECCCAP_DMDA1_DA_ERRINT_SEOVFIE * (U4)ECC_MECCCAP_DMDA1_DA_ERRINT_ENABLE  )
												   + ( (U4)ECC_MECCCAP_DMDA1_DA_ERRINT_DEDIE   * (U4)ECC_MECCCAP_DMDA1_DA_ERRINT_ENABLE  )
												   + ( (U4)ECC_MECCCAP_DMDA1_DA_ERRINT_SEDIE   * (U4)ECC_MECCCAP_DMDA1_DA_ERRINT_DISABLE ) );
#endif

	/* Peripheral RAM (128 bits) ECC 設定												*/
	/* Peripheral RAM (128 bits)にはEthernet用のRAMしか存在しないが、					*/
	/* Ethernetは非使用機能であり、クロック供給されていないため、レジスタ設定を行わない	*/

	/* Peripheral RAM (64 bits) ECC 設定												*/
	/* Peripheral RAM (64 bits)にはEthernet用のRAMしか存在しないが、					*/
	/* Ethernetは非使用機能であり、クロック供給されていないため、レジスタ設定を行わない	*/

	/* Peripheral RAM (32 bits) ECC 設定 */
	ErrH_Ecc_PR32_Init();

	/* Peripheral RAM (16 bits) ECC 設定 */
	ErrH_Ecc_PR16_Init();

	/* Data transfer path (data、address) ECC 設定 */
	ErrH_Ecc_DTP_Init();

	/* ECC制御レジスタのKey Code Protection再開 */
	REG_ECC_ECCKC.unKCPROT.u4Data = (U4)ECC_ECCDF_KCPROT_KCE_DISABLE;
	Bswlib_Sync_Pipeline_4( REG_ECC_ECCKC.unKCPROT.u4Data );
	
	/* イニシャルシーケンスで生じたエラーを通知するため、ステータスレジスタはクリアしない */
}

/*----------------------------------------------------------------------------------------------*/
/* ErrH_Ecc_DeInit Function																		*/
/* Return		: none																			*/
/* Parameters	: none																			*/
/*----------------------------------------------------------------------------------------------*/
void	ErrH_Ecc_DeInit( void )
{
	S4		i;
	volatile Reg_Ecc_Ecc7Type*				t_pstReg_Ecc7;
	volatile Reg_Ecc_Ecc6Type*				t_pstReg_Ecc6;
	volatile Reg_Ecc_PbnEccType*			t_pstReg_PbnEcc;
	volatile Reg_Ecc_HbnEccType*			t_pstReg_HbnEcc;
	volatile Reg_Ecc_BeccCap_V2AnType*		t_pstReg_V2an;

	/* ECC制御レジスタのKey Code Protection解除 */
	REG_ECC_ECCKC.unKCPROT.u4Data = (U4)ECC_ECCDF_KCPROT_KCE_ENABLE;
	Bswlib_Sync_Pipeline_4( REG_ECC_ECCKC.unKCPROT.u4Data );

	/* 各ECC機能のエラー通知制御レジスタを通知無効に設定 */

	/* Code Flash ECC 設定 */
	/* CF_ERRINT - Error Notification Control Register */
	REG_ECC_MECCCAP_CFL.unCF_ERRINT.u4Data = (U4)( ( (U4)ECC_MECCCAP_CFL_CF_ERRINT_SEOVFIE * (U4)ECC_MECCCAP_CFL_CF_ERRINT_DISABLE )
												 + ( (U4)ECC_MECCCAP_CFL_CF_ERRINT_APEIE   * (U4)ECC_MECCCAP_CFL_CF_ERRINT_DISABLE )
												 + ( (U4)ECC_MECCCAP_CFL_CF_ERRINT_DEDIE   * (U4)ECC_MECCCAP_CFL_CF_ERRINT_DISABLE )
												 + ( (U4)ECC_MECCCAP_CFL_CF_ERRINT_SEDIE   * (U4)ECC_MECCCAP_CFL_CF_ERRINT_DISABLE ) );

	/* Data Flash ECC 設定 */
	/* Init時にECMへの通知を無効に設定しているため、DeInitでの設定は不要 */

	/* Local RAM ECC 設定 */
	/* LR0_ERRINT - Error Notification Control Register */
	REG_ECC_MECCCAP_LR_PE0CL0.unLR0_ERRINT.u4Data = (U4)( ( (U4)ECC_MECCCAP_LR_PE0CL0_ERINT_SEOVFIE * (U4)ECC_MECCCAP_LR_PE0CL0_ERRINT_DISABLE )
														+ ( (U4)ECC_MECCCAP_LR_PE0CL0_ERINT_AFEIE   * (U4)ECC_MECCCAP_LR_PE0CL0_ERRINT_DISABLE )
														+ ( (U4)ECC_MECCCAP_LR_PE0CL0_ERINT_DEDIE   * (U4)ECC_MECCCAP_LR_PE0CL0_ERRINT_DISABLE )
														+ ( (U4)ECC_MECCCAP_LR_PE0CL0_ERINT_SEDIE   * (U4)ECC_MECCCAP_LR_PE0CL0_ERRINT_DISABLE ) );

	REG_ECC_MECCCAP_LR_PE1CL0.unLR0_ERRINT.u4Data = (U4)( ( (U4)ECC_MECCCAP_LR_PE1CL0_ERINT_SEOVFIE * (U4)ECC_MECCCAP_LR_PE1CL0_ERRINT_DISABLE )
														+ ( (U4)ECC_MECCCAP_LR_PE1CL0_ERINT_AFEIE   * (U4)ECC_MECCCAP_LR_PE1CL0_ERRINT_DISABLE )
														+ ( (U4)ECC_MECCCAP_LR_PE1CL0_ERINT_DEDIE   * (U4)ECC_MECCCAP_LR_PE1CL0_ERRINT_DISABLE )
														+ ( (U4)ECC_MECCCAP_LR_PE1CL0_ERINT_SEDIE   * (U4)ECC_MECCCAP_LR_PE1CL0_ERRINT_DISABLE ) );

#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_TRIPLECORE ) )	/* U2B10かつ3コア構成 */
	/* U2B6、またはU2B10かつ2コア構成の場合、Init時にECMへの通知を無効に設定しているため、DeInitでの設定は不要 */
	REG_ECC_MECCCAP_LR_PE2CL1.unLR0_ERRINT.u4Data = (U4)( ( (U4)ECC_MECCCAP_LR_PE2CL1_ERINT_SEOVFIE * (U4)ECC_MECCCAP_LR_PE2CL1_ERRINT_DISABLE )
														+ ( (U4)ECC_MECCCAP_LR_PE2CL1_ERINT_AFEIE   * (U4)ECC_MECCCAP_LR_PE2CL1_ERRINT_DISABLE )
														+ ( (U4)ECC_MECCCAP_LR_PE2CL1_ERINT_DEDIE   * (U4)ECC_MECCCAP_LR_PE2CL1_ERRINT_DISABLE )
														+ ( (U4)ECC_MECCCAP_LR_PE2CL1_ERINT_SEDIE   * (U4)ECC_MECCCAP_LR_PE2CL1_ERRINT_DISABLE ) );
#endif

	/* LR_PE3CL1はInit時にECMへの通知を無効に設定しているため、DeInitでの設定は不要 */

	/* LR1_ERRINT - Error Notification Control Register */
	REG_ECC_MECCCAP_LRA.unLR1_ERRINT.u4Data = (U4)( ( (U4)ECC_MECCCAP_LRA_LR1_ERRINT_SEOVFIE * (U4)ECC_MECCCAP_LRA_LR1_ERRINT_DISABLE )
												  + ( (U4)ECC_MECCCAP_LRA_LR1_ERRINT_DEDIE   * (U4)ECC_MECCCAP_LRA_LR1_ERRINT_DISABLE )
												  + ( (U4)ECC_MECCCAP_LRA_LR1_ERRINT_SEDIE   * (U4)ECC_MECCCAP_LRA_LR1_ERRINT_DISABLE ) );

	/* Cluster RAM ECC 設定 */
	/* CR_ERRINT - Error Notification Control Register */
	REG_ECC_MECCCAP_CRAM.unCR_ERRINT.u4Data = (U4)( ( (U4)ECC_MECCCAP_CRAM_CR_ERRINT_SEOVFIE * (U4)ECC_MECCCAP_CRAM_CR_ERRINT_DISABLE )
												  + ( (U4)ECC_MECCCAP_CRAM_CR_ERRINT_AFEIE   * (U4)ECC_MECCCAP_CRAM_CR_ERRINT_DISABLE )
												  + ( (U4)ECC_MECCCAP_CRAM_CR_ERRINT_DEDIE   * (U4)ECC_MECCCAP_CRAM_CR_ERRINT_DISABLE )
												  + ( (U4)ECC_MECCCAP_CRAM_CR_ERRINT_SEDIE   * (U4)ECC_MECCCAP_CRAM_CR_ERRINT_DISABLE ) );

	/* Instruction cache ECC 設定 */
	/* IT_ERRINT - Error Notification Control Register */
	REG_ECC_MECCCAP_IT_PE0CL0.unIT_ERRINT.u4Data = (U4)( ( (U4)ECC_MECCCAP_IT_PE0CL0_ERRINT_AFEIE * (U4)ECC_MECCCAP_IT_PE0CL0_ERRINT_DISABLE )
													   + ( (U4)ECC_MECCCAP_IT_PE0CL0_ERRINT_DEDIE * (U4)ECC_MECCCAP_IT_PE0CL0_ERRINT_DISABLE )
													   + ( (U4)ECC_MECCCAP_IT_PE0CL0_ERRINT_SEDIE * (U4)ECC_MECCCAP_IT_PE0CL0_ERRINT_DISABLE ) );

	REG_ECC_MECCCAP_IT_PE1CL0.unIT_ERRINT.u4Data = (U4)( ( (U4)ECC_MECCCAP_IT_PE1CL0_ERRINT_AFEIE * (U4)ECC_MECCCAP_IT_PE1CL0_ERRINT_DISABLE )
													   + ( (U4)ECC_MECCCAP_IT_PE1CL0_ERRINT_DEDIE * (U4)ECC_MECCCAP_IT_PE1CL0_ERRINT_DISABLE )
													   + ( (U4)ECC_MECCCAP_IT_PE1CL0_ERRINT_SEDIE * (U4)ECC_MECCCAP_IT_PE1CL0_ERRINT_DISABLE ) );

#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_TRIPLECORE ) )	/* U2B10かつ3コア構成 */
	/* U2B6、またはU2B10かつ2コア構成の場合、Init時にECMへの通知を無効に設定しているため、DeInitでの設定は不要 */
	REG_ECC_MECCCAP_IT_PE2CL1.unIT_ERRINT.u4Data = (U4)( ( (U4)ECC_MECCCAP_IT_PE2CL1_ERRINT_AFEIE * (U4)ECC_MECCCAP_IT_PE2CL1_ERRINT_DISABLE )
													   + ( (U4)ECC_MECCCAP_IT_PE2CL1_ERRINT_DEDIE * (U4)ECC_MECCCAP_IT_PE2CL1_ERRINT_DISABLE )
													   + ( (U4)ECC_MECCCAP_IT_PE2CL1_ERRINT_SEDIE * (U4)ECC_MECCCAP_IT_PE2CL1_ERRINT_DISABLE ) );
#endif

	/* IT_PE3CL1はInit時にECMへの通知を無効に設定しているため、DeInitでの設定は不要 */

	/* ID_ERRINT - Error Notification Control Register */
	REG_ECC_MECCCAP_ID_PE0CL0.unID_ERRINT.u4Data = (U4)( ( (U4)ECC_MECCCAP_ID_PE0CL0_ERRINT_AFEIE * (U4)ECC_MECCCAP_ID_PE0CL0_ERRINT_DISABLE )
													   + ( (U4)ECC_MECCCAP_ID_PE0CL0_ERRINT_DEDIE * (U4)ECC_MECCCAP_ID_PE0CL0_ERRINT_DISABLE )
													   + ( (U4)ECC_MECCCAP_ID_PE0CL0_ERRINT_SEDIE * (U4)ECC_MECCCAP_ID_PE0CL0_ERRINT_DISABLE ) );

	REG_ECC_MECCCAP_ID_PE1CL0.unID_ERRINT.u4Data = (U4)( ( (U4)ECC_MECCCAP_ID_PE1CL0_ERRINT_AFEIE * (U4)ECC_MECCCAP_ID_PE1CL0_ERRINT_DISABLE )
													   + ( (U4)ECC_MECCCAP_ID_PE1CL0_ERRINT_DEDIE * (U4)ECC_MECCCAP_ID_PE1CL0_ERRINT_DISABLE )
													   + ( (U4)ECC_MECCCAP_ID_PE1CL0_ERRINT_SEDIE * (U4)ECC_MECCCAP_ID_PE1CL0_ERRINT_DISABLE ) );

#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_TRIPLECORE ) )	/* U2B10かつ3コア構成 */
	/* U2B6、またはU2B10かつ2コア構成の場合、Init時にECMへの通知を無効に設定しているため、DeInitでの設定は不要 */
	REG_ECC_MECCCAP_ID_PE2CL1.unID_ERRINT.u4Data = (U4)( ( (U4)ECC_MECCCAP_ID_PE2CL1_ERRINT_AFEIE * (U4)ECC_MECCCAP_ID_PE2CL1_ERRINT_DISABLE )
													   + ( (U4)ECC_MECCCAP_ID_PE2CL1_ERRINT_DEDIE * (U4)ECC_MECCCAP_ID_PE2CL1_ERRINT_DISABLE )
													   + ( (U4)ECC_MECCCAP_ID_PE2CL1_ERRINT_SEDIE * (U4)ECC_MECCCAP_ID_PE2CL1_ERRINT_DISABLE ) );
#endif

	/* ID_PE3CL1はInit時にECMへの通知を無効に設定しているため、DeInitでの設定は不要 */

	/* RAM for DTS、sDMAC (Descriptor、Data) ECC 設定 */
	/* DR_ERRINT - Error Notification Control Register */
	REG_ECC_MECCCAP_DTS.unDR_ERRINT.u4Data = (U4)( ( (U4)ECC_MECCCAP_DTS_DR_ERRINT_SEOVFIE * (U4)ECC_MECCCAP_DTS_DR_ERRINT_DISABLE )
												 + ( (U4)ECC_MECCCAP_DTS_DR_ERRINT_AFEIE   * (U4)ECC_MECCCAP_DTS_DR_ERRINT_DISABLE )
												 + ( (U4)ECC_MECCCAP_DTS_DR_ERRINT_DEDIE   * (U4)ECC_MECCCAP_DTS_DR_ERRINT_DISABLE )
												 + ( (U4)ECC_MECCCAP_DTS_DR_ERRINT_SEDIE   * (U4)ECC_MECCCAP_DTS_DR_ERRINT_DISABLE ) );

	/* DE_ERRINT - Error Notification Control Register */
	REG_ECC_MECCCAP_DMDE0.unDE_ERRINT.u4Data = (U4)( ( (U4)ECC_MECCCAP_DMDE0_DE_ERRINT_SEOVFIE * (U4)ECC_MECCCAP_DMDE0_DE_ERRINT_DISABLE )
												   + ( (U4)ECC_MECCCAP_DMDE0_DE_ERRINT_AFEIE   * (U4)ECC_MECCCAP_DMDE0_DE_ERRINT_DISABLE )
												   + ( (U4)ECC_MECCCAP_DMDE0_DE_ERRINT_DEDIE   * (U4)ECC_MECCCAP_DMDE0_DE_ERRINT_DISABLE )
												   + ( (U4)ECC_MECCCAP_DMDE0_DE_ERRINT_SEDIE   * (U4)ECC_MECCCAP_DMDE0_DE_ERRINT_DISABLE ) );

#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
	REG_ECC_MECCCAP_DMDE1.unDE_ERRINT.u4Data = (U4)( ( (U4)ECC_MECCCAP_DMDE1_DE_ERRINT_SEOVFIE * (U4)ECC_MECCCAP_DMDE1_DE_ERRINT_DISABLE )
												   + ( (U4)ECC_MECCCAP_DMDE1_DE_ERRINT_AFEIE   * (U4)ECC_MECCCAP_DMDE1_DE_ERRINT_DISABLE )
												   + ( (U4)ECC_MECCCAP_DMDE1_DE_ERRINT_DEDIE   * (U4)ECC_MECCCAP_DMDE1_DE_ERRINT_DISABLE )
												   + ( (U4)ECC_MECCCAP_DMDE1_DE_ERRINT_SEDIE   * (U4)ECC_MECCCAP_DMDE1_DE_ERRINT_DISABLE ) );
#endif

	/* DA_ERRINT - Error Notification Control Register */
	REG_ECC_MECCCAP_DMDA0.unDA_ERRINT.u4Data = (U4)( ( (U4)ECC_MECCCAP_DMDA0_DA_ERRINT_SEOVFIE * (U4)ECC_MECCCAP_DMDA0_DA_ERRINT_DISABLE )
												   + ( (U4)ECC_MECCCAP_DMDA0_DA_ERRINT_DEDIE   * (U4)ECC_MECCCAP_DMDA0_DA_ERRINT_DISABLE )
												   + ( (U4)ECC_MECCCAP_DMDA0_DA_ERRINT_SEDIE   * (U4)ECC_MECCCAP_DMDA0_DA_ERRINT_DISABLE ) );

#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
	REG_ECC_MECCCAP_DMDA1.unDA_ERRINT.u4Data = (U4)( ( (U4)ECC_MECCCAP_DMDA1_DA_ERRINT_SEOVFIE * (U4)ECC_MECCCAP_DMDA1_DA_ERRINT_DISABLE )
												   + ( (U4)ECC_MECCCAP_DMDA1_DA_ERRINT_DEDIE   * (U4)ECC_MECCCAP_DMDA1_DA_ERRINT_DISABLE )
												   + ( (U4)ECC_MECCCAP_DMDA1_DA_ERRINT_SEDIE   * (U4)ECC_MECCCAP_DMDA1_DA_ERRINT_DISABLE ) );
#endif

	/* Peripheral RAM (128 bits) ECC 設定												*/
	/* Peripheral RAM (128 bits)にはEthernet用のRAMしか存在しないが、					*/
	/* Ethernetは非使用機能であり、クロック供給されていないため、レジスタ設定を行わない	*/

	/* Peripheral RAM (64 bits) ECC 設定												*/
	/* Peripheral RAM (64 bits)にはEthernet用のRAMしか存在しないが、					*/
	/* Ethernetは非使用機能であり、クロック供給されていないため、レジスタ設定を行わない	*/

	/* Peripheral RAM (32 bits) ECC 設定 */
	for( i = (S4)0; i < (S4)ECC7_CHANNEL_NUM; i++ )
	{
		/* RS-CAN-FD、MSPI、DFEを無効に設定 */
		if( cu1Ecc_Ecc7UseTable[i] == (U1)ON )
		{
			t_pstReg_Ecc7 = (volatile Reg_Ecc_Ecc7Type*)pcstReg_Ecc7[i];

			/* E710CTL - ECC Control Register */
			/* オーバフローエラーは設定ビットがなく、無条件で通知するため、根幹となる制御ビットを無効に設定 */
			t_pstReg_Ecc7->unE710CTL.u2Data = (U2)( ( (U2)ECC_ECC7_E710CTL_EMCA_0  * (U2)ECC_ECC7_E710CTL_EMCA_WRITE			)
												   + ( (U2)ECC_ECC7_E710CTL_ECTHM   * (U2)ECC_ECC7_E710CTL_ECTHM_DISABLE		)
												   + ( (U2)ECC_ECC7_E710CTL_EC1ECP  * (U2)ECC_ECC7_E710CTL_EC1ECP_DISABLE		)
												   + ( (U2)ECC_ECC7_E710CTL_EC2EDIC * (U2)ECC_ECC7_E710CTL_EC2EDIC_NOTNOTIFIED	)
												   + ( (U2)ECC_ECC7_E710CTL_EC1EDIC * (U2)ECC_ECC7_E710CTL_EC1EDIC_NOTNOTIFIED	) );
		}
		else
		{
			/* FlexRay0、GTM、MMCA、Ethernetは非使用機能であり、クロック供給されていないため、レジスタ設定を行わない */
		}
	}

	/* Peripheral RAM (16 bits) ECC 設定 */
	for( i = (S4)0; i < (S4)ECC6_CHANNEL_NUM; i++ )
	{
		t_pstReg_Ecc6 = (volatile Reg_Ecc_Ecc6Type*)pcstReg_Ecc6[i];

		/* E610CTL - ECC Control Register */
		/* オーバフローエラーは設定ビットがなく、無条件で通知するため、根幹となる制御ビットを無効に設定 */
		t_pstReg_Ecc6->unE610CTL.u2Data = (U2)( ( (U2)ECC_ECC6_E610CTL_EMCA_0  * (U2)ECC_ECC6_E610CTL_EMCA_WRITE			)
											   + ( (U2)ECC_ECC6_E610CTL_ECTHM   * (U2)ECC_ECC6_E610CTL_ECTHM_DISABLE		)
											   + ( (U2)ECC_ECC6_E610CTL_EC1ECP  * (U2)ECC_ECC6_E610CTL_EC1ECP_DISABLE		)
											   + ( (U2)ECC_ECC6_E610CTL_EC2EDIC * (U2)ECC_ECC6_E610CTL_EC2EDIC_NOTNOTIFIED	)
											   + ( (U2)ECC_ECC6_E610CTL_EC1EDIC * (U2)ECC_ECC6_E610CTL_EC1EDIC_NOTNOTIFIED	) );
	}

	/* Data transfer pathのECC制御レジスタのKey Code Protection解除 */
	for( i = (S4)0; i < (S4)PBNECC_CHANNEL_NUM; i++ )
	{
		t_pstReg_PbnEcc = (volatile Reg_Ecc_PbnEccType*)pcstReg_PbnEcc[i];
		t_pstReg_PbnEcc->unAPECKCPROT.u4Data = (U4)ECC_PBNECC_APECKCPROT_KCE_ENABLE;
		Bswlib_Sync_Pipeline_4( t_pstReg_PbnEcc->unAPECKCPROT.u4Data );
	}

	for( i = (S4)0; i < (S4)HBNECC_CHANNEL_NUM; i++ )
	{
		t_pstReg_HbnEcc = (volatile Reg_Ecc_HbnEccType*)pcstReg_HbnEcc[i];
		t_pstReg_HbnEcc->unHBECKCPROT.u4Data = (U4)ECC_HBNECC_HBECKCPROT_KCE_ENABLE;
		Bswlib_Sync_Pipeline_4( t_pstReg_HbnEcc->unHBECKCPROT.u4Data );
	}

	/* Data transfer path (data、address) ECC 設定 */
	/* BECCCAP_LRAM */
	/* LR_BUSERRINT - Error Notification Control Register */
	REG_ECC_BECCCAP_LRAM.unLR_BUSERRINT.u4Data = (U4)( ( (U4)ECC_BECCCAP_LRAM_BUSERRINT_ADEDIE * (U4)ECC_BECCCAP_LRAM_ERRINT_ADE_DISABLE )
													 + ( (U4)ECC_BECCCAP_LRAM_BUSERRINT_ASEDIE * (U4)ECC_BECCCAP_LRAM_ERRINT_ASE_DISABLE )
													 + ( (U4)ECC_BECCCAP_LRAM_BUSERRINT_DDEDIE * (U4)ECC_BECCCAP_LRAM_ERRINT_DDE_DISABLE )
													 + ( (U4)ECC_BECCCAP_LRAM_BUSERRINT_DSEDIE * (U4)ECC_BECCCAP_LRAM_ERRINT_DSE_DISABLE ) );

	/* BECCCAP_CRAM */
	/* CR_BUSERRINT - Error Notification Control Register */
	REG_ECC_BECCCAP_CRAM.unCR_BUSERRINT.u4Data = (U4)( ( (U4)ECC_BECCCAP_CRAM_BUSERRINT_ADEDIE * (U4)ECC_BECCCAP_CRAM_ERRINT_ADE_DISABLE )
													 + ( (U4)ECC_BECCCAP_CRAM_BUSERRINT_ASEDIE * (U4)ECC_BECCCAP_CRAM_ERRINT_ASE_DISABLE )
													 + ( (U4)ECC_BECCCAP_CRAM_BUSERRINT_DDEDIE * (U4)ECC_BECCCAP_CRAM_ERRINT_DDE_DISABLE )
													 + ( (U4)ECC_BECCCAP_CRAM_BUSERRINT_DSEDIE * (U4)ECC_BECCCAP_CRAM_ERRINT_DSE_DISABLE ) );

	/* BECCCAP_CFL */
	/* CF_BUSERRINT - Error Notification Control Register */
	REG_ECC_BECCCAP_CFL.unCF_BUSERRINT.u4Data = (U4)( ( (U4)ECC_BECCCAP_CFL_BUSERRINT_ADEDIE * (U4)ECC_BECCCAP_CFL_ERRINT_ADE_DISABLE )
													+ ( (U4)ECC_BECCCAP_CFL_BUSERRINT_ASEDIE * (U4)ECC_BECCCAP_CFL_ERRINT_ASE_DISABLE ) );

	/* BECCCAP_PERI */
	/* PH_BUSERRINT - Error Notification Control Register */
	REG_ECC_BECCCAP_PERI.unPH_BUSERRINT.u4Data = (U4)( ( (U4)ECC_BECCCAP_PERI_BUSERRINT_ADEDIE * (U4)ECC_BECCCAP_PERI_ERRINT_ADE_DISABLE )
													 + ( (U4)ECC_BECCCAP_PERI_BUSERRINT_ASEDIE * (U4)ECC_BECCCAP_PERI_ERRINT_ASE_DISABLE )
													 + ( (U4)ECC_BECCCAP_PERI_BUSERRINT_DDEDIE * (U4)ECC_BECCCAP_PERI_ERRINT_DDE_DISABLE )
													 + ( (U4)ECC_BECCCAP_PERI_BUSERRINT_DSEDIE * (U4)ECC_BECCCAP_PERI_ERRINT_DSE_DISABLE ) );

	/* BECCCAP_DMDT */
	/* DM_BUSERRINT  Error Notification Control Register */
	REG_ECC_BECCCAP_DMDT.unDM_BUSERRINT.u4Data = (U4)( ( (U4)ECC_BECCCAP_DMDT_BUSERRINT_DDEDIE * (U4)ECC_BECCCAP_DMDT_ERRINT_DDE_DISABLE )
													 + ( (U4)ECC_BECCCAP_DMDT_BUSERRINT_DSEDIE * (U4)ECC_BECCCAP_DMDT_ERRINT_DSE_DISABLE ) );

	/* BECCCAP_EMU */
	/* EM_BUSERRINT - Error Notification Control Register */
	REG_ECC_BECCCAP_EMU.unEM_BUSERRINT.u4Data = (U4)( ( (U4)ECC_BECCCAP_EMU_BUSERRINT_ADEDIE * (U4)ECC_BECCCAP_EMU_ERRINT_ADE_DISABLE )
													+ ( (U4)ECC_BECCCAP_EMU_BUSERRINT_ASEDIE * (U4)ECC_BECCCAP_EMU_ERRINT_ASE_DISABLE )
													+ ( (U4)ECC_BECCCAP_EMU_BUSERRINT_DDEDIE * (U4)ECC_BECCCAP_EMU_ERRINT_DDE_DISABLE )
													+ ( (U4)ECC_BECCCAP_EMU_BUSERRINT_DSEDIE * (U4)ECC_BECCCAP_EMU_ERRINT_DSE_DISABLE ) );

	/* HBnECC(n = 90M/S, 92M/S, 94S, 97M, 98M, 911M, 912M) */
	/* HBnECC(n = 90M, 92M, 97M, 98M, 911M, 912M) */
	/* HBECERRINT - Error Notification Control Register */
	/* H-Busマスタはアドレスエラーの通知許可ビットがReservedとなっている。マイコン制約として、 */
	/* 初期値(=1)と同じ値を設定する必要があり、ENABLE(=1)を設定している。					   */
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
	REG_ECC_HB90MECC.unHBECERRINT.u4Data = (U4)( ( (U4)ECC_HBNECC_HBECERRINT_ADEDIE * (U4)ECC_HBNECC_HBECERRINT_ADEDIE_ENABLE )
											   + ( (U4)ECC_HBNECC_HBECERRINT_ASEDIE * (U4)ECC_HBNECC_HBECERRINT_ADEDIE_ENABLE )
											   + ( (U4)ECC_HBNECC_HBECERRINT_DEDIE  * (U4)ECC_HBNECC_HBECERRINT_DEDIE_DISABLE )
											   + ( (U4)ECC_HBNECC_HBECERRINT_SEDIE  * (U4)ECC_HBNECC_HBECERRINT_SEDIE_DISABLE ) );
#endif

	REG_ECC_HB92MECC.unHBECERRINT.u4Data = (U4)( ( (U4)ECC_HBNECC_HBECERRINT_ADEDIE * (U4)ECC_HBNECC_HBECERRINT_ADEDIE_ENABLE )
											   + ( (U4)ECC_HBNECC_HBECERRINT_ASEDIE * (U4)ECC_HBNECC_HBECERRINT_ADEDIE_ENABLE )
											   + ( (U4)ECC_HBNECC_HBECERRINT_DEDIE  * (U4)ECC_HBNECC_HBECERRINT_DEDIE_DISABLE )
											   + ( (U4)ECC_HBNECC_HBECERRINT_SEDIE  * (U4)ECC_HBNECC_HBECERRINT_SEDIE_DISABLE ) );

	REG_ECC_HB97MECC.unHBECERRINT.u4Data = (U4)( ( (U4)ECC_HBNECC_HBECERRINT_ADEDIE * (U4)ECC_HBNECC_HBECERRINT_ADEDIE_ENABLE )
											   + ( (U4)ECC_HBNECC_HBECERRINT_ASEDIE * (U4)ECC_HBNECC_HBECERRINT_ADEDIE_ENABLE )
											   + ( (U4)ECC_HBNECC_HBECERRINT_DEDIE  * (U4)ECC_HBNECC_HBECERRINT_DEDIE_DISABLE )
											   + ( (U4)ECC_HBNECC_HBECERRINT_SEDIE  * (U4)ECC_HBNECC_HBECERRINT_SEDIE_DISABLE ) );
											   
	REG_ECC_HB98MECC.unHBECERRINT.u4Data = (U4)( ( (U4)ECC_HBNECC_HBECERRINT_ADEDIE * (U4)ECC_HBNECC_HBECERRINT_ADEDIE_ENABLE )
											   + ( (U4)ECC_HBNECC_HBECERRINT_ASEDIE * (U4)ECC_HBNECC_HBECERRINT_ADEDIE_ENABLE )
											   + ( (U4)ECC_HBNECC_HBECERRINT_DEDIE  * (U4)ECC_HBNECC_HBECERRINT_DEDIE_DISABLE )
											   + ( (U4)ECC_HBNECC_HBECERRINT_SEDIE  * (U4)ECC_HBNECC_HBECERRINT_SEDIE_DISABLE ) );

#if ( MCU_TYPE_SERIES == MCU_RH850U2B6 )
	REG_ECC_HB911MECC.unHBECERRINT.u4Data = (U4)( ( (U4)ECC_HBNECC_HBECERRINT_ADEDIE * (U4)ECC_HBNECC_HBECERRINT_ADEDIE_ENABLE )
											   + ( (U4)ECC_HBNECC_HBECERRINT_ASEDIE * (U4)ECC_HBNECC_HBECERRINT_ADEDIE_ENABLE )
											   + ( (U4)ECC_HBNECC_HBECERRINT_DEDIE  * (U4)ECC_HBNECC_HBECERRINT_DEDIE_DISABLE )
											   + ( (U4)ECC_HBNECC_HBECERRINT_SEDIE  * (U4)ECC_HBNECC_HBECERRINT_SEDIE_DISABLE ) );
											   
	REG_ECC_HB912MECC.unHBECERRINT.u4Data = (U4)( ( (U4)ECC_HBNECC_HBECERRINT_ADEDIE * (U4)ECC_HBNECC_HBECERRINT_ADEDIE_ENABLE )
											   + ( (U4)ECC_HBNECC_HBECERRINT_ASEDIE * (U4)ECC_HBNECC_HBECERRINT_ADEDIE_ENABLE )
											   + ( (U4)ECC_HBNECC_HBECERRINT_DEDIE  * (U4)ECC_HBNECC_HBECERRINT_DEDIE_DISABLE )
											   + ( (U4)ECC_HBNECC_HBECERRINT_SEDIE  * (U4)ECC_HBNECC_HBECERRINT_SEDIE_DISABLE ) );
#endif

	/* HBnECC(n = 90S, 92S, 94S) */
	/* HBECERRINT - Error Notification Control Register */
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
	REG_ECC_HB90SECC.unHBECERRINT.u4Data = (U4)( ( (U4)ECC_HBNECC_HBECERRINT_ADEDIE * (U4)ECC_HBNECC_HBECERRINT_ADEDIE_DISABLE )
											   + ( (U4)ECC_HBNECC_HBECERRINT_ASEDIE * (U4)ECC_HBNECC_HBECERRINT_ASEDIE_DISABLE )
											   + ( (U4)ECC_HBNECC_HBECERRINT_DEDIE  * (U4)ECC_HBNECC_HBECERRINT_DEDIE_DISABLE  )
											   + ( (U4)ECC_HBNECC_HBECERRINT_SEDIE  * (U4)ECC_HBNECC_HBECERRINT_SEDIE_DISABLE  ) );
#endif

	REG_ECC_HB92SECC.unHBECERRINT.u4Data = (U4)( ( (U4)ECC_HBNECC_HBECERRINT_ADEDIE * (U4)ECC_HBNECC_HBECERRINT_ADEDIE_DISABLE )
											   + ( (U4)ECC_HBNECC_HBECERRINT_ASEDIE * (U4)ECC_HBNECC_HBECERRINT_ASEDIE_DISABLE )
											   + ( (U4)ECC_HBNECC_HBECERRINT_DEDIE  * (U4)ECC_HBNECC_HBECERRINT_DEDIE_DISABLE  )
											   + ( (U4)ECC_HBNECC_HBECERRINT_SEDIE  * (U4)ECC_HBNECC_HBECERRINT_SEDIE_DISABLE  ) );

	REG_ECC_HB94SECC.unHBECERRINT.u4Data = (U4)( ( (U4)ECC_HBNECC_HBECERRINT_ADEDIE * (U4)ECC_HBNECC_HBECERRINT_ADEDIE_DISABLE )
											   + ( (U4)ECC_HBNECC_HBECERRINT_ASEDIE * (U4)ECC_HBNECC_HBECERRINT_ASEDIE_DISABLE )
											   + ( (U4)ECC_HBNECC_HBECERRINT_DEDIE  * (U4)ECC_HBNECC_HBECERRINT_DEDIE_DISABLE  )
											   + ( (U4)ECC_HBNECC_HBECERRINT_SEDIE  * (U4)ECC_HBNECC_HBECERRINT_SEDIE_DISABLE  ) );

	/* BECCCAP_V2An(n = 1-11) */
	for( i = (S4)0; i < (S4)V2AN_CHANNEL_NUM; i++ )
	{
		t_pstReg_V2an = (volatile Reg_Ecc_BeccCap_V2AnType*)pcstReg_V2an[i];

		/* PHC_BUSERRINT - Error Notification Control Register */
		t_pstReg_V2an->unPHC_BUSERRINT.u4Data = (U4)( ( (U4)ECC_BECCCAP_V2AN_BUSERRINT_ADEDIE * (U4)ECC_BECCCAP_V2AN_ERRINT_ADE_DISABLE )
													 + ( (U4)ECC_BECCCAP_V2AN_BUSERRINT_ASEDIE * (U4)ECC_BECCCAP_V2AN_ERRINT_ASE_DISABLE )
													 + ( (U4)ECC_BECCCAP_V2AN_BUSERRINT_DDEDIE * (U4)ECC_BECCCAP_V2AN_ERRINT_DDE_DISABLE )
													 + ( (U4)ECC_BECCCAP_V2AN_BUSERRINT_DSEDIE * (U4)ECC_BECCCAP_V2AN_ERRINT_DSE_DISABLE ) );
	}

	/* DFPは非使用機能であり、クロック供給されていないため、レジスタ設定を行わない */

	/* Data transfer pathのECC制御レジスタのKey Code Protection再開 */
	for( i = (S4)0; i < (S4)PBNECC_CHANNEL_NUM; i++ )
	{
		t_pstReg_PbnEcc = (volatile Reg_Ecc_PbnEccType*)pcstReg_PbnEcc[i];
		t_pstReg_PbnEcc->unAPECKCPROT.u4Data = (U4)ECC_PBNECC_APECKCPROT_KCE_DISABLE;
		Bswlib_Sync_Pipeline_4( t_pstReg_PbnEcc->unAPECKCPROT.u4Data );
	}

	for( i = (S4)0; i < (S4)HBNECC_CHANNEL_NUM; i++ )
	{
		t_pstReg_HbnEcc = (volatile Reg_Ecc_HbnEccType*)pcstReg_HbnEcc[i];
		t_pstReg_HbnEcc->unHBECKCPROT.u4Data = (U4)ECC_HBNECC_HBECKCPROT_KCE_DISABLE;
		Bswlib_Sync_Pipeline_4( t_pstReg_HbnEcc->unHBECKCPROT.u4Data );
	}

	/* ECC制御レジスタのKey Code Protection再開 */
	REG_ECC_ECCKC.unKCPROT.u4Data = (U4)ECC_ECCDF_KCPROT_KCE_DISABLE;
	Bswlib_Sync_Pipeline_4( REG_ECC_ECCKC.unKCPROT.u4Data );
}

/*----------------------------------------------------------------------------------------------*/
/* Local Functions																				*/
/*----------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------*/
/* ErrH_Ecc_DF_Init Function																	*/
/* Return		: none																			*/
/* Parameters	: none																			*/
/*----------------------------------------------------------------------------------------------*/
static	void	ErrH_Ecc_DF_Init( void )
{
	/* Data FlashはFeeで保障するため、ECMへの通知は行わない */

	/* Data FlashのECC制御レジスタのKey Code Protection解除 */
	REG_ECC_ECCDF.unDFKCPROT.u4Data = (U4)ECC_ECCDF_DFKCPROT_KCE_ENABLE;

	/* DFECCCTL - Data Flash ECC Control Register */
	REG_ECC_ECCDF.unDFECCCTL.u4Data = (U4)( ( (U4)ECC_ECCDF_DFECCCTL_SECDIS * (U4)ECC_ECCDF_DFECCCTL_ENABLE )
										  + ( (U4)ECC_ECCDF_DFECCCTL_ECCDIS * (U4)ECC_ECCDF_DFECCCTL_ENABLE ) );

	/* DFERRINT - Data Flash Error Notification Control Register */
	REG_ECC_ECCDF.unDFERRINT.u4Data = (U4)( ( (U4)ECC_ECCDF_DFERRINT_SEOVFIE * (U4)ECC_ECCDF_DFERRINT_DISABLE )
										  + ( (U4)ECC_ECCDF_DFERRINT_DEDIE  * (U4)ECC_ECCDF_DFERRINT_DISABLE )
										  + ( (U4)ECC_ECCDF_DFERRINT_SEDIE  * (U4)ECC_ECCDF_DFERRINT_DISABLE ) );

	/* DFTSTCTL - Data Flash Test Control Register */
	REG_ECC_ECCDF.unDFTSTCTL.u4Data = (U4)ECC_ECCDF_DFTSTCTL_ECCTST * (U4)ECC_ECCDF_DFTSTCTL_ECCTST_NORMAL;

	/* Data FlashのECC制御レジスタのKey Code Protection再開 */
	REG_ECC_ECCDF.unDFKCPROT.u4Data = (U4)ECC_ECCDF_DFKCPROT_KCE_DISABLE;
	Bswlib_Sync_Pipeline_4( REG_ECC_ECCDF.unDFKCPROT.u4Data );
}

/*----------------------------------------------------------------------------------------------*/
/* ErrH_Ecc_Cram_Init Function																	*/
/* Return		: none																			*/
/* Parameters	: none																			*/
/*----------------------------------------------------------------------------------------------*/
static	void	ErrH_Ecc_Cram_Init( void )
{
	U4	t_u4RegValue;	/* レジスタ値 */

	/* CRCAFCTL - Address Feedback Control Register(Reset初期値と同じ値) */
	t_u4RegValue = (U4)( REG_ECC_ECCCNT_CRCCL0.unCRCAFCTL.u4Data & (U4)u4ERRH_ECC_MASK_ECCCNT_CRCCL0_CRCAFCTL );
	/* ECC_ECCCNT_CRCCL0_CRCAFCTL_AFEDISビットにEnable(0)をセット(冗長となるため、処理は省略) */
	REG_ECC_ECCCNT_CRCCL0.unCRCAFCTL.u4Data = t_u4RegValue;

#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
	t_u4RegValue = (U4)( REG_ECC_ECCCNT_CRCCL1.unCRCAFCTL.u4Data & (U4)u4ERRH_ECC_MASK_ECCCNT_CRCCL1_CRCAFCTL );
	/* ECC_ECCCNT_CRCCL1_CRCAFCTL_AFEDISビットにEnable(0)をセット(冗長となるため、処理は省略) */
	REG_ECC_ECCCNT_CRCCL1.unCRCAFCTL.u4Data = t_u4RegValue;
#endif

	/* CRCECCTSTCTL - ECC Test Control Register(Reset初期値と同じ値) */
	REG_ECC_ECCCNT_CRCCL0.unCRCECCTSTCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_CRCCL0_TSTCTL_ECCTST * (U4)ECC_ECCCNT_CRCCL0_TSTCTL_TST_NORMAL )
													  + ( (U4)ECC_ECCCNT_CRCCL0_TSTCTL_DATSEL * (U4)ECC_ECCCNT_CRCCL0_TSTCTL_DS_DATA   ) );

#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
	REG_ECC_ECCCNT_CRCCL1.unCRCECCTSTCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_CRCCL1_TSTCTL_ECCTST * (U4)ECC_ECCCNT_CRCCL1_TSTCTL_TST_NORMAL )
													  + ( (U4)ECC_ECCCNT_CRCCL1_TSTCTL_DATSEL * (U4)ECC_ECCCNT_CRCCL1_TSTCTL_DS_DATA   ) );
#endif

	/* CRAECCCTL - ECC Control Register(Reset初期値と同じ値) */
	REG_ECC_ECCCNT_CRA.unCRAECCCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_CRA_CRAECCCTL_SECDIS * (U4)ECC_ECCCNT_CRA_CRAECCCTL_ENABLE )
												+ ( (U4)ECC_ECCCNT_CRA_CRAECCCTL_ECCDIS * (U4)ECC_ECCCNT_CRA_CRAECCCTL_ENABLE ) );

	/* CR_ERRINT - Error Notification Control Register(Reset初期値と同じ値) */
	REG_ECC_MECCCAP_CRAM.unCR_ERRINT.u4Data = (U4)( ( (U4)ECC_MECCCAP_CRAM_CR_ERRINT_SEOVFIE * (U4)ECC_MECCCAP_CRAM_CR_ERRINT_ENABLE )
												  + ( (U4)ECC_MECCCAP_CRAM_CR_ERRINT_AFEIE   * (U4)ECC_MECCCAP_CRAM_CR_ERRINT_ENABLE )
												  + ( (U4)ECC_MECCCAP_CRAM_CR_ERRINT_DEDIE   * (U4)ECC_MECCCAP_CRAM_CR_ERRINT_ENABLE )
												  + ( (U4)ECC_MECCCAP_CRAM_CR_ERRINT_SEDIE   * (U4)ECC_MECCCAP_CRAM_CR_ERRINT_ENABLE ) );

	/* イニシャルシーケンスで生じたエラーを通知するため、ステータスレジスタはクリアしない */
}

/*----------------------------------------------------------------------------------------------*/
/* ErrH_Ecc_PR32_Init Function																	*/
/* Return		: none																			*/
/* Parameters	: none																			*/
/*----------------------------------------------------------------------------------------------*/
static	void	ErrH_Ecc_PR32_Init( void )
{
	S4		i;
	volatile Reg_Ecc_Ecc7Type*				t_pstReg_Ecc7;

	for( i = (S4)0; i < (S4)ECC7_CHANNEL_NUM; i++ )
	{
		t_pstReg_Ecc7 = (volatile Reg_Ecc_Ecc7Type*)pcstReg_Ecc7[i];

		/* RS-CAN-FD、MSPI、DFEを有効に設定 */
		if( cu1Ecc_Ecc7UseTable[i] == (U1)ON )
		{
			/* E710CTL - ECC Control Register */
			/* オーバフローエラーは設定ビットがなく、無条件で通知する */
			/* ECC 1bitエラーは自動訂正可能のため通知しない */
			/* イニシャルシーケンスで生じたエラーを通知するため、ステータスレジスタはクリアしない */
			t_pstReg_Ecc7->unE710CTL.u2Data = (U2)( ( (U2)ECC_ECC7_E710CTL_EMCA_0  * (U2)ECC_ECC7_E710CTL_EMCA_WRITE			)
												   + ( (U2)ECC_ECC7_E710CTL_ECTHM   * (U2)ECC_ECC7_E710CTL_ECTHM_ENABLE			)
												   + ( (U2)ECC_ECC7_E710CTL_EC1ECP  * (U2)ECC_ECC7_E710CTL_EC1ECP_ENABLE		)
												   + ( (U2)ECC_ECC7_E710CTL_EC2EDIC * (U2)ECC_ECC7_E710CTL_EC2EDIC_NOTIFIED		)
												   + ( (U2)ECC_ECC7_E710CTL_EC1EDIC * (U2)ECC_ECC7_E710CTL_EC1EDIC_NOTNOTIFIED	) );

			/* E710TMC - ECC Test Mode Control Register(Reset初期値と同じ値) */
			t_pstReg_Ecc7->unE710TMC.u2Data = (U2)( ( (U2)ECC_ECC7_E710TMC_ETMA_0 * (U2)ECC_ECC7_E710TMC_ETMA_WRITE	 )
												   + ( (U2)ECC_ECC7_E710TMC_ECTMCE * (U2)ECC_ECC7_E710TMC_ECTMCE_DISABLE ) );
		}
		else
		{
			/* FlexRay0、GTM、MMCA、Ethernetは非使用機能であり、クロック供給されていないため、レジスタ設定を行わない */
		}
	}
}

/*----------------------------------------------------------------------------------------------*/
/* ErrH_Ecc_PR16_Init Function																	*/
/* Return		: none																			*/
/* Parameters	: none																			*/
/*----------------------------------------------------------------------------------------------*/
static	void	ErrH_Ecc_PR16_Init( void )
{
	S4		i;
	volatile Reg_Ecc_Ecc6Type*				t_pstReg_Ecc6;

	for( i = (S4)0; i < (S4)ECC6_CHANNEL_NUM; i++ )
	{
		t_pstReg_Ecc6 = (volatile Reg_Ecc_Ecc6Type*)pcstReg_Ecc6[i];

		/* E610CTL - ECC Control Register */
		/* オーバフローエラーは設定ビットがなく、無条件で通知する */
		/* ECC 1bitエラーは自動訂正可能のため通知しない */
		/* イニシャルシーケンスで生じたエラーを通知するため、ステータスレジスタはクリアしない */
		t_pstReg_Ecc6->unE610CTL.u2Data = (U2)( ( (U2)ECC_ECC6_E610CTL_EMCA_0  * (U2)ECC_ECC6_E610CTL_EMCA_WRITE			)
											   + ( (U2)ECC_ECC6_E610CTL_ECTHM   * (U2)ECC_ECC6_E610CTL_ECTHM_ENABLE			)
											   + ( (U2)ECC_ECC6_E610CTL_EC1ECP  * (U2)ECC_ECC6_E610CTL_EC1ECP_ENABLE		)
											   + ( (U2)ECC_ECC6_E610CTL_EC2EDIC * (U2)ECC_ECC6_E610CTL_EC2EDIC_NOTIFIED		)
											   + ( (U2)ECC_ECC6_E610CTL_EC1EDIC * (U2)ECC_ECC6_E610CTL_EC1EDIC_NOTNOTIFIED	) );

		/* E610TMC - ECC Test Mode Control Register */
		t_pstReg_Ecc6->unE610TMC.u2Data = (U2)( ( (U2)ECC_ECC6_E610TMC_ETMA_0  * (U2)ECC_ECC6_E610TMC_ETMA_WRITE	 )
											   + ( (U2)ECC_ECC6_E610TMC_ECTMCE  * (U2)ECC_ECC6_E610TMC_ECTMCE_DISABLE ) );
	}
}

/*----------------------------------------------------------------------------------------------*/
/* ErrH_Ecc_DTP_Init Function																	*/
/* Return		: none																			*/
/* Parameters	: none																			*/
/*----------------------------------------------------------------------------------------------*/
static	void	ErrH_Ecc_DTP_Init( void )
{
	S4										i;
	U4										t_u4RegValue;		/* レジスタ値 */
	volatile Reg_Ecc_EccCnt_AType*			t_pstReg_A;
	volatile Reg_Ecc_EccCnt_D_V2AnWType*	t_pstReg_V2AnW;
	volatile Reg_Ecc_PbnEccType*			t_pstReg_PbnEcc;
	volatile Reg_Ecc_HbnEccType*			t_pstReg_HbnEcc;
	volatile Reg_Ecc_BeccCap_V2AnType*		t_pstReg_V2an;

	/* Data transfer pathのECC制御レジスタのKey Code Protection解除 */
	for( i = (S4)0; i < (S4)PBNECC_CHANNEL_NUM; i++ )
	{
		t_pstReg_PbnEcc = (volatile Reg_Ecc_PbnEccType*)pcstReg_PbnEcc[i];
		t_pstReg_PbnEcc->unAPECKCPROT.u4Data = (U4)ECC_PBNECC_APECKCPROT_KCE_ENABLE;
		Bswlib_Sync_Pipeline_4( t_pstReg_PbnEcc->unAPECKCPROT.u4Data );
	}

	for( i = (S4)0; i < (S4)HBNECC_CHANNEL_NUM; i++ )
	{
		t_pstReg_HbnEcc = (volatile Reg_Ecc_HbnEccType*)pcstReg_HbnEcc[i];
		t_pstReg_HbnEcc->unHBECKCPROT.u4Data = (U4)ECC_HBNECC_HBECKCPROT_KCE_ENABLE;
		Bswlib_Sync_Pipeline_4( t_pstReg_HbnEcc->unHBECKCPROT.u4Data );
	}

	/*	 ECCCNT_A_CCIBnCL0(n = 0-1)、ECCCNT_A_CCIBnCL1(n = 0-1)、ECCCNT_SA_PEnCL0(n = 0, 1)、	*/
	/*	 ECCCNT_A_GCFUnCL0(n = 0, 1)、ECCCNT_SA_PEnCL1(n = 2, 3)、ECCCNT_A_GCFUnCL1(n = 2, 3)、	*/
	/*	 ECCCNT_A_X2VCLn(n = 0, 1)、ECCCNT_A_BARR、ECCCNT_A_IPIR、ECCCNT_A_TPTM、				*/
	/*	 ECCCNT_A_CRAM、ECCCNT_A_SG0、ECCCNT_A_SX2PV、 ECCCNT_A_SX2FX、ECCCNT_A_FX2SX、			*/
	/*	 ECCCNT_A_EX2FX、ECCCNT_A_GCFUE、ECCCNT_A_GCFUF、ECCCNT_A_SX2MB、						*/
	/*	 ECCCNT_A_V2An(n = 1-11)																*/
	for( i = (S4)0; i < (S4)A_CHANNEL_NUM; i++ )
	{
		t_pstReg_A = (volatile Reg_Ecc_EccCnt_AType*)pcstReg_A[i];

		/* BUSAECCCTL - ECC Control Register(Reset初期値と同じ値) */
		t_pstReg_A->unBUSAECCCTL.u4Data = (U4)ECC_ECCCNT_A_BUSAECCCTL_ECCDIS * (U4)ECC_ECCCNT_A_ECCCTL_ECCDIS_ENABLE;

		/* BUSAECCTSTCTL - ECC Test Control Register(Reset初期値と同じ値) */
		if( cu1ErrH_Ecc_EcccntATstctlSetEnTable[i] == (U1)ON )
		{
			t_pstReg_A->unBUSAECCTSTCTL.u4Data = (U4)ECC_ECCCNT_A_BUSAECCTSTCTL_ECCTST * (U4)ECC_ECCCNT_A_TSTCTL_ECCTST_NORMAL;
		}
	}

#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B6 ) || ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_DUALCORE ) ) )	/* U2B6、またはU2B10かつ2コア構成 */
	REG_ECC_ECCCNT_SA_PE2CL1.unBUSAECCCTL.u4Data = (U4)ECC_ECCCNT_A_BUSAECCCTL_ECCDIS * (U4)ECC_ECCCNT_A_ECCCTL_ECCDIS_DISABLE;

	REG_ECC_ECCCNT_A_GCFU2CL1.unBUSAECCCTL.u4Data = (U4)ECC_ECCCNT_A_BUSAECCCTL_ECCDIS * (U4)ECC_ECCCNT_A_ECCCTL_ECCDIS_DISABLE;

	REG_ECC_ECCCNT_A_X2VCL1.unBUSAECCCTL.u4Data = (U4)ECC_ECCCNT_A_BUSAECCCTL_ECCDIS * (U4)ECC_ECCCNT_A_ECCCTL_ECCDIS_DISABLE;
#endif

#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
	REG_ECC_ECCCNT_SA_PE3CL1.unBUSAECCCTL.u4Data = (U4)ECC_ECCCNT_A_BUSAECCCTL_ECCDIS * (U4)ECC_ECCCNT_A_ECCCTL_ECCDIS_DISABLE;

	REG_ECC_ECCCNT_A_GCFU3CL1.unBUSAECCCTL.u4Data = (U4)ECC_ECCCNT_A_BUSAECCCTL_ECCDIS * (U4)ECC_ECCCNT_A_ECCCTL_ECCDIS_DISABLE;
#endif

	/* ECCCNT_D_V2XWCLn(n=0,1) */
	/* BUSDVCECCCTL - ECC Control Register(Reset初期値と同じ値) */
	REG_ECC_ECCCNT_D_V2XWCL0.unBUSDVCECCCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_D_V2XWCL0_ECCCTL_SECDIS * (U4)ECC_ECCCNT_D_V2XWCL0_CTL_SD_CORRECT )
														 + ( (U4)ECC_ECCCNT_D_V2XWCL0_ECCCTL_ECCDIS * (U4)ECC_ECCCNT_D_V2XWCL0_CTL_ED_ENABLE  ) );

#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B6 ) || ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_DUALCORE ) ) )	/* U2B6、またはU2B10かつ2コア構成 */
	REG_ECC_ECCCNT_D_V2XWCL1.unBUSDVCECCCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_D_V2XWCL1_ECCCTL_SECDIS * (U4)ECC_ECCCNT_D_V2XWCL1_CTL_SD_NOTCORRECT )
														 + ( (U4)ECC_ECCCNT_D_V2XWCL1_ECCCTL_ECCDIS * (U4)ECC_ECCCNT_D_V2XWCL1_CTL_ED_DISABLE  ) );
#else /* U2B10かつ3コア構成以上 */
	REG_ECC_ECCCNT_D_V2XWCL1.unBUSDVCECCCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_D_V2XWCL1_ECCCTL_SECDIS * (U4)ECC_ECCCNT_D_V2XWCL1_CTL_SD_CORRECT )
														 + ( (U4)ECC_ECCCNT_D_V2XWCL1_ECCCTL_ECCDIS * (U4)ECC_ECCCNT_D_V2XWCL1_CTL_ED_ENABLE  ) );
#endif

	/* BUSDVCECCTSTCTL - ECC Test Control Register(Reset初期値と同じ値) */
	REG_ECC_ECCCNT_D_V2XWCL0.unBUSDVCECCTSTCTL.u4Data = (U4)ECC_ECCCNT_D_V2XWCL0_TSTCTL_ECCTST * (U4)ECC_ECCCNT_D_V2XWCL0_TCTL_TST_NORMAL;

	REG_ECC_ECCCNT_D_V2XWCL1.unBUSDVCECCTSTCTL.u4Data = (U4)ECC_ECCCNT_D_V2XWCL1_TSTCTL_ECCTST * (U4)ECC_ECCCNT_D_V2XWCL1_TCTL_TST_NORMAL;

	/* ECCCNT_D_V2XRCLn(n=0,1) */
	/* BUSDVCECCCTL - ECC Control Register(Reset初期値と同じ値) */
	REG_ECC_ECCCNT_D_V2XRCL0.unBUSDVCECCCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_D_V2XRCL0_ECCCTL_SECDIS * (U4)ECC_ECCCNT_D_V2XRCL0_CTL_SD_CORRECT )
														 + ( (U4)ECC_ECCCNT_D_V2XRCL0_ECCCTL_ECCDIS * (U4)ECC_ECCCNT_D_V2XRCL0_CTL_ED_ENABLE  ) );

#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B6 ) || ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_DUALCORE ) ) )	/* U2B6、またはU2B10かつ2コア構成 */
	REG_ECC_ECCCNT_D_V2XRCL1.unBUSDVCECCCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_D_V2XRCL1_ECCCTL_SECDIS * (U4)ECC_ECCCNT_D_V2XRCL1_CTL_SD_NOTCORRECT )
														 + ( (U4)ECC_ECCCNT_D_V2XRCL1_ECCCTL_ECCDIS * (U4)ECC_ECCCNT_D_V2XRCL1_CTL_ED_DISABLE  ) );
#else /* U2B10かつ3コア構成以上 */
	REG_ECC_ECCCNT_D_V2XRCL1.unBUSDVCECCCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_D_V2XRCL1_ECCCTL_SECDIS * (U4)ECC_ECCCNT_D_V2XRCL1_CTL_SD_CORRECT )
														 + ( (U4)ECC_ECCCNT_D_V2XRCL1_ECCCTL_ECCDIS * (U4)ECC_ECCCNT_D_V2XRCL1_CTL_ED_ENABLE  ) );
#endif

	/* BUSDVCECCTSTCTL - ECC Test Control Register(Reset初期値と同じ値) */
	REG_ECC_ECCCNT_D_V2XRCL0.unBUSDVCECCTSTCTL.u4Data = (U4)ECC_ECCCNT_D_V2XRCL0_TSTCTL_ECCTST * (U4)ECC_ECCCNT_D_V2XRCL0_TCTL_TST_NORMAL;

	REG_ECC_ECCCNT_D_V2XRCL1.unBUSDVCECCTSTCTL.u4Data = (U4)ECC_ECCCNT_D_V2XRCL1_TSTCTL_ECCTST * (U4)ECC_ECCCNT_D_V2XRCL1_TCTL_TST_NORMAL;

	/* ECCCNT_D_PV2APBW */
	/* BUSDECCCTL - ECC Control Register(Reset初期値と同じ値) */
	REG_ECC_ECCCNT_D_PV2APBW.unBUSDECCCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_D_PV2APBW_ECCCTL_SECDIS * (U4)ECC_ECCCNT_D_PV2APBW_CTL_SD_CORRECT )
														 + ( (U4)ECC_ECCCNT_D_PV2APBW_ECCCTL_ECCDIS * (U4)ECC_ECCCNT_D_PV2APBW_CTL_ED_ENABLE  ) );

	/* ECCCNT_D_CRAM */
	/* BUSDVCECCCTL - ECC Control Register(Reset初期値と同じ値) */
	REG_ECC_ECCCNT_D_CRAM.unBUSDVCECCCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_D_CRAM_ECCCTL_SECDIS * (U4)ECC_ECCCNT_D_CRAM_CTL_SD_CORRECT )
													  + ( (U4)ECC_ECCCNT_D_CRAM_ECCCTL_ECCDIS * (U4)ECC_ECCCNT_D_CRAM_CTL_ED_ENABLE  ) );

	/* BUSDVCECCTSTCTL - ECC Test Control Register(Reset初期値と同じ値) */
	REG_ECC_ECCCNT_D_CRAM.unBUSDVCECCTSTCTL.u4Data = (U4)ECC_ECCCNT_D_CRAM_ECCTSTCTL_ECCTST * (U4)ECC_ECCCNT_D_CRAM_TCTL_TST_NORMAL;

	/* ECCCNT_D_EMU */
	/* BUSDEMECCCTL - ECC Control Register(Reset初期値と同じ値) */
	REG_ECC_ECCCNT_D_EMU.unBUSDEMECCCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_D_EMU_ECCCTL_SECDIS * (U4)ECC_ECCCNT_D_EMU_CTL_SD_CORRECT )
													 + ( (U4)ECC_ECCCNT_D_EMU_ECCCTL_ECCDIS * (U4)ECC_ECCCNT_D_EMU_CTL_ED_ENABLE  ) );

	/* BUSDEMECCTSTCTL - ECC Test Control Register(Reset初期値と同じ値) */
	REG_ECC_ECCCNT_D_EMU.unBUSDEMECCTSTCTL.u4Data = (U4)ECC_ECCCNT_D_EMU_ECCTSTCTL_ECCTST * (U4)ECC_ECCCNT_D_EMU_TCTL_TST_NORMAL;

	/* ECCCNT_D_DMDEn(n = 0, 1) */
	/* BUSDDEECCCTL - ECC Control Register(Reset初期値と同じ値) */
	REG_ECC_ECCCNT_D_DMDE0.unBUSDDEECCCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_D_DMDE0_ECCCTL_SECDIS * (U4)ECC_ECCCNT_D_DMDE0_CTL_SD_CORRECT )
													   + ( (U4)ECC_ECCCNT_D_DMDE0_ECCCTL_ECCDIS * (U4)ECC_ECCCNT_D_DMDE0_CTL_ED_ENABLE  ) );

#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
	REG_ECC_ECCCNT_D_DMDE1.unBUSDDEECCCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_D_DMDE1_ECCCTL_SECDIS * (U4)ECC_ECCCNT_D_DMDE1_CTL_SD_CORRECT )
													   + ( (U4)ECC_ECCCNT_D_DMDE1_ECCCTL_ECCDIS * (U4)ECC_ECCCNT_D_DMDE1_CTL_ED_ENABLE  ) );
#endif

	/* BUSDDEECCTSTCTL - ECC Test Control Register(Reset初期値と同じ値) */
	REG_ECC_ECCCNT_D_DMDE0.unBUSDDEECCTSTCTL.u4Data = (U4)ECC_ECCCNT_D_DMDE0_ECCTSTCTL_ECCTST * (U4)ECC_ECCCNT_D_DMDE0_TCTL_TST_NORMAL;

#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
	REG_ECC_ECCCNT_D_DMDE1.unBUSDDEECCTSTCTL.u4Data = (U4)ECC_ECCCNT_D_DMDE1_ECCTSTCTL_ECCTST * (U4)ECC_ECCCNT_D_DMDE1_TCTL_TST_NORMAL;
#endif

	/* ECCCNT_C_DMRn(n = 0, 1) */
	/* BUSCECCCTL - ECC Control Register(Reset初期値と同じ値) */
	REG_ECC_ECCCNT_C_DMR0.unBUSCECCCTL.u4Data = (U4)ECC_ECCCNT_C_DMR0_ECCCTL_ECCDIS * (U4)ECC_ECCCNT_C_DMR0_CTL_ED_ENABLE;

#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
	REG_ECC_ECCCNT_C_DMR1.unBUSCECCCTL.u4Data = (U4)ECC_ECCCNT_C_DMR1_ECCCTL_ECCDIS * (U4)ECC_ECCCNT_C_DMR1_CTL_ED_ENABLE;
#endif

	/* BUSCECCTSTCTL - ECC Test Control Register(Reset初期値と同じ値) */
	REG_ECC_ECCCNT_C_DMR0.unBUSCECCTSTCTL.u4Data = (U4)ECC_ECCCNT_C_DMR0_ECCTSTCTL_ECCTST * (U4)ECC_ECCCNT_C_DMR0_TCTL_TST_NORMAL;

#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
	REG_ECC_ECCCNT_C_DMR1.unBUSCECCTSTCTL.u4Data = (U4)ECC_ECCCNT_C_DMR1_ECCTSTCTL_ECCTST * (U4)ECC_ECCCNT_C_DMR1_TCTL_TST_NORMAL;
#endif

	/* ECCCNT_C_DMWn(n = 0, 1) */
	/* BUSCECCCTL - ECC Control Register(Reset初期値と同じ値) */
	REG_ECC_ECCCNT_C_DMW0.unBUSCECCCTL.u4Data = (U4)ECC_ECCCNT_C_DMW0_ECCCTL_ECCDIS * (U4)ECC_ECCCNT_C_DMW0_CTL_ED_ENABLE;

#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
	REG_ECC_ECCCNT_C_DMW1.unBUSCECCCTL.u4Data = (U4)ECC_ECCCNT_C_DMW1_ECCCTL_ECCDIS * (U4)ECC_ECCCNT_C_DMW1_CTL_ED_ENABLE;
#endif

	/* BUSCECCTSTCTL - ECC Test Control Register(Reset初期値と同じ値) */
	REG_ECC_ECCCNT_C_DMW0.unBUSCECCTSTCTL.u4Data = (U4)ECC_ECCCNT_C_DMW0_ECCTSTCTL_ECCTST * (U4)ECC_ECCCNT_C_DMW0_TCTL_TST_NORMAL;

#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
	REG_ECC_ECCCNT_C_DMW1.unBUSCECCTSTCTL.u4Data = (U4)ECC_ECCCNT_C_DMW1_ECCTSTCTL_ECCTST * (U4)ECC_ECCCNT_C_DMW1_TCTL_TST_NORMAL;
#endif

	/* ECCCNT_SD_PEnCL0(n = 0, 1) */
	/* BUSDECCCTL - ECC Control Register(Reset初期値と同じ値) */
	REG_ECC_ECCCNT_SD_PE0CL0.unBUSDECCCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_SD_PE0CL0_ECCCTL_SECDIS * (U4)ECC_ECCCNT_SD_PE0CL0_CTL_SD_CORRECT )
													   + ( (U4)ECC_ECCCNT_SD_PE0CL0_ECCCTL_ECCDIS * (U4)ECC_ECCCNT_SD_PE0CL0_CTL_ED_ENABLE  ) );

	REG_ECC_ECCCNT_SD_PE1CL0.unBUSDECCCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_SD_PE1CL0_ECCCTL_SECDIS * (U4)ECC_ECCCNT_SD_PE1CL0_CTL_SD_CORRECT )
													   + ( (U4)ECC_ECCCNT_SD_PE1CL0_ECCCTL_ECCDIS * (U4)ECC_ECCCNT_SD_PE1CL0_CTL_ED_ENABLE  ) );

	/* ECCCNT_SD_PEnCL1(n = 2, 3) */
	/* BUSDECCCTL - ECC Control Register(Reset初期値と同じ値) */
#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B6 ) || ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_DUALCORE ) ) )	/* U2B6、またはU2B10かつ2コア構成 */
	REG_ECC_ECCCNT_SD_PE2CL1.unBUSDECCCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_SD_PE2CL1_ECCCTL_SECDIS * (U4)ECC_ECCCNT_SD_PE2CL1_CTL_SD_NOTCORRECT )
													   + ( (U4)ECC_ECCCNT_SD_PE2CL1_ECCCTL_ECCDIS * (U4)ECC_ECCCNT_SD_PE2CL1_CTL_ED_DISABLE  ) );
#else /* U2B10かつ3コア構成以上 */
	REG_ECC_ECCCNT_SD_PE2CL1.unBUSDECCCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_SD_PE2CL1_ECCCTL_SECDIS * (U4)ECC_ECCCNT_SD_PE2CL1_CTL_SD_CORRECT )
													   + ( (U4)ECC_ECCCNT_SD_PE2CL1_ECCCTL_ECCDIS * (U4)ECC_ECCCNT_SD_PE2CL1_CTL_ED_ENABLE  ) );
#endif

#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
	REG_ECC_ECCCNT_SD_PE3CL1.unBUSDECCCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_SD_PE3CL1_ECCCTL_SECDIS * (U4)ECC_ECCCNT_SD_PE3CL1_CTL_SD_NOTCORRECT )
													   + ( (U4)ECC_ECCCNT_SD_PE3CL1_ECCCTL_ECCDIS * (U4)ECC_ECCCNT_SD_PE3CL1_CTL_ED_DISABLE  ) );
#endif

	/* ECCCNT_MD_PEnCL0(n = 0, 1) */
	/* BUSDECCCTL - ECC Control Register(Reset初期値と同じ値) */
	REG_ECC_ECCCNT_MD_PE0CL0.unBUSDECCCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_MD_PE0CL0_ECCCTL_SECDIS * (U4)ECC_ECCCNT_MD_PE0CL0_CTL_SD_CORRECT )
													   + ( (U4)ECC_ECCCNT_MD_PE0CL0_ECCCTL_ECCDIS * (U4)ECC_ECCCNT_MD_PE0CL0_CTL_ED_ENABLE  ) );

	REG_ECC_ECCCNT_MD_PE1CL0.unBUSDECCCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_MD_PE1CL0_ECCCTL_SECDIS * (U4)ECC_ECCCNT_MD_PE1CL0_CTL_SD_CORRECT )
													   + ( (U4)ECC_ECCCNT_MD_PE1CL0_ECCCTL_ECCDIS * (U4)ECC_ECCCNT_MD_PE1CL0_CTL_ED_ENABLE  ) );

	/* ECCCNT_MD_PEnCL1(n = 2, 3) */
	/* BUSDECCCTL - ECC Control Register(Reset初期値と同じ値) */
#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B6 ) || ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_DUALCORE ) ) )	/* U2B6、またはU2B10かつ2コア構成 */
	REG_ECC_ECCCNT_MD_PE2CL1.unBUSDECCCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_MD_PE2CL1_ECCCTL_SECDIS * (U4)ECC_ECCCNT_MD_PE2CL1_CTL_SD_NOTCORRECT )
													   + ( (U4)ECC_ECCCNT_MD_PE2CL1_ECCCTL_ECCDIS * (U4)ECC_ECCCNT_MD_PE2CL1_CTL_ED_DISABLE  ) );
#else /* U2B10かつ3コア構成以上 */
	REG_ECC_ECCCNT_MD_PE2CL1.unBUSDECCCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_MD_PE2CL1_ECCCTL_SECDIS * (U4)ECC_ECCCNT_MD_PE2CL1_CTL_SD_CORRECT )
													   + ( (U4)ECC_ECCCNT_MD_PE2CL1_ECCCTL_ECCDIS * (U4)ECC_ECCCNT_MD_PE2CL1_CTL_ED_ENABLE  ) );
#endif

#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
	REG_ECC_ECCCNT_MD_PE3CL1.unBUSDECCCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_MD_PE3CL1_ECCCTL_SECDIS * (U4)ECC_ECCCNT_MD_PE3CL1_CTL_SD_NOTCORRECT )
													   + ( (U4)ECC_ECCCNT_MD_PE3CL1_ECCCTL_ECCDIS * (U4)ECC_ECCCNT_MD_PE3CL1_CTL_ED_DISABLE  ) );
#endif

	/* ECCCNT_D_BARR */
	/* BUSDECCCTL - ECC Control Register(Reset初期値と同じ値) */
	REG_ECC_ECCCNT_D_BARR.unBUSDECCCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_D_BARR_ECCCTL_SECDIS * (U4)ECC_ECCCNT_D_BARR_CTL_SD_CORRECT )
													+ ( (U4)ECC_ECCCNT_D_BARR_ECCCTL_ECCDIS * (U4)ECC_ECCCNT_D_BARR_CTL_ED_ENABLE  ) );

	/* ECCCNT_D_IPIR */
	/* BUSDECCCTL - ECC Control Register(Reset初期値と同じ値) */
	REG_ECC_ECCCNT_D_IPIR.unBUSDECCCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_D_IPIR_ECCCTL_SECDIS * (U4)ECC_ECCCNT_D_IPIR_CTL_SD_CORRECT )
													+ ( (U4)ECC_ECCCNT_D_IPIR_ECCCTL_ECCDIS * (U4)ECC_ECCCNT_D_IPIR_CTL_ED_ENABLE  ) );

	/* ECCCNT_D_TPTM */
	/* BUSDECCCTL - ECC Control Register(Reset初期値と同じ値) */
	REG_ECC_ECCCNT_D_TPTM.unBUSDECCCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_D_TPTM_ECCCTL_SECDIS * (U4)ECC_ECCCNT_D_TPTM_CTL_SD_CORRECT )
													+ ( (U4)ECC_ECCCNT_D_TPTM_ECCCTL_ECCDIS * (U4)ECC_ECCCNT_D_TPTM_CTL_ED_ENABLE  ) );

	/* ECCCNT_D_DTS */
	/* BUSDECCCTL - ECC Control Register(Reset初期値と同じ値) */
	REG_ECC_ECCCNT_D_DTS.unBUSDECCCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_D_DTS_ECCCTL_SECDIS * (U4)ECC_ECCCNT_D_DTS_CTL_SD_CORRECT )
												   + ( (U4)ECC_ECCCNT_D_DTS_ECCCTL_ECCDIS * (U4)ECC_ECCCNT_D_DTS_CTL_ED_ENABLE  ) );

	/* ECCCNT_D_DMAn(n = 0, 1) */
	/* BUSDECCCTL - ECC Control Register(Reset初期値と同じ値) */
	REG_ECC_ECCCNT_D_DMA0.unBUSDECCCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_D_DMA0_ECCCTL_SECDIS * (U4)ECC_ECCCNT_D_DMA0_CTL_SD_CORRECT )
													+ ( (U4)ECC_ECCCNT_D_DMA0_ECCCTL_ECCDIS * (U4)ECC_ECCCNT_D_DMA0_CTL_ED_ENABLE  ) );

#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
	REG_ECC_ECCCNT_D_DMA1.unBUSDECCCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_D_DMA1_ECCCTL_SECDIS * (U4)ECC_ECCCNT_D_DMA1_CTL_SD_CORRECT )
													+ ( (U4)ECC_ECCCNT_D_DMA1_ECCCTL_ECCDIS * (U4)ECC_ECCCNT_D_DMA1_CTL_ED_ENABLE  ) );
#endif

	/* ECCCNT_D_V2AnW(n = 1-11) */
	for( i = (S4)0; i < (S4)V2ANW_CHANNEL_NUM; i++ )
	{
		t_pstReg_V2AnW = (volatile Reg_Ecc_EccCnt_D_V2AnWType*)pcstReg_V2AnW[i];

		/* BUSDVCECCCTL - ECC Control Register(Reset初期値と同じ値) */
		t_pstReg_V2AnW->unBUSDVCECCCTL.u4Data = (U4)( ( (U4)ECC_ECCCNT_D_V2AnW_ECCCTL_SECDIS * (U4)ECC_ECCCNT_D_V2AnW_CTL_SD_CORRECT )
													  + ( (U4)ECC_ECCCNT_D_V2AnW_ECCCTL_ECCDIS * (U4)ECC_ECCCNT_D_V2AnW_CTL_ED_ENABLE  ) );
	}

	/* DFPは非使用機能であり、クロック供給されていないため、レジスタ設定を行わない */

	/* 備考 */
	/* dataはECC 1bitを訂正可能であるためECMへ通知しない(addressは訂正不可能のため通知する) */
	/* イニシャルシーケンスで生じたエラーを通知するため、ステータスレジスタはクリアしない */

	/* BECCCAP_LRAM */
	/* LR_BUSERRINT - Error Notification Control Register */
	REG_ECC_BECCCAP_LRAM.unLR_BUSERRINT.u4Data = (U4)( ( (U4)ECC_BECCCAP_LRAM_BUSERRINT_ADEDIE * (U4)ECC_BECCCAP_LRAM_ERRINT_ADE_ENABLE  )
													 + ( (U4)ECC_BECCCAP_LRAM_BUSERRINT_ASEDIE * (U4)ECC_BECCCAP_LRAM_ERRINT_ASE_ENABLE  )
													 + ( (U4)ECC_BECCCAP_LRAM_BUSERRINT_DDEDIE * (U4)ECC_BECCCAP_LRAM_ERRINT_DDE_ENABLE  )
													 + ( (U4)ECC_BECCCAP_LRAM_BUSERRINT_DSEDIE * (U4)ECC_BECCCAP_LRAM_ERRINT_DSE_DISABLE ) );

	/* BECCCAP_CRAM */
	/* CR_BUSERRINT - Error Notification Control Register */
	REG_ECC_BECCCAP_CRAM.unCR_BUSERRINT.u4Data = (U4)( ( (U4)ECC_BECCCAP_CRAM_BUSERRINT_ADEDIE * (U4)ECC_BECCCAP_CRAM_ERRINT_ADE_ENABLE  )
													 + ( (U4)ECC_BECCCAP_CRAM_BUSERRINT_ASEDIE * (U4)ECC_BECCCAP_CRAM_ERRINT_ASE_ENABLE  )
													 + ( (U4)ECC_BECCCAP_CRAM_BUSERRINT_DDEDIE * (U4)ECC_BECCCAP_CRAM_ERRINT_DDE_ENABLE  )
													 + ( (U4)ECC_BECCCAP_CRAM_BUSERRINT_DSEDIE * (U4)ECC_BECCCAP_CRAM_ERRINT_DSE_DISABLE ) );

	/* BECCCAP_CFL */
	/* CF_BUSERRINT - Error Notification Control Register(Reset初期値と同じ値) */
	REG_ECC_BECCCAP_CFL.unCF_BUSERRINT.u4Data = (U4)( ( (U4)ECC_BECCCAP_CFL_BUSERRINT_ADEDIE * (U4)ECC_BECCCAP_CFL_ERRINT_ADE_ENABLE )
													 + ( (U4)ECC_BECCCAP_CFL_BUSERRINT_ASEDIE * (U4)ECC_BECCCAP_CFL_ERRINT_ASE_ENABLE ) );

	/* BECCCAP_PERI */
	/* PH_BUSERRINT - Error Notification Control Register */
	REG_ECC_BECCCAP_PERI.unPH_BUSERRINT.u4Data = (U4)( ( (U4)ECC_BECCCAP_PERI_BUSERRINT_ADEDIE * (U4)ECC_BECCCAP_PERI_ERRINT_ADE_ENABLE  )
													 + ( (U4)ECC_BECCCAP_PERI_BUSERRINT_ASEDIE * (U4)ECC_BECCCAP_PERI_ERRINT_ASE_ENABLE  )
													 + ( (U4)ECC_BECCCAP_PERI_BUSERRINT_DDEDIE * (U4)ECC_BECCCAP_PERI_ERRINT_DDE_ENABLE  )
													 + ( (U4)ECC_BECCCAP_PERI_BUSERRINT_DSEDIE * (U4)ECC_BECCCAP_PERI_ERRINT_DSE_DISABLE ) );

	/* BECCCAP_DMDT */
	/* DM_BUSERRINT  Error Notification Control Register */
	REG_ECC_BECCCAP_DMDT.unDM_BUSERRINT.u4Data = (U4)( ( (U4)ECC_BECCCAP_DMDT_BUSERRINT_DDEDIE * (U4)ECC_BECCCAP_DMDT_ERRINT_DDE_ENABLE  )
													 + ( (U4)ECC_BECCCAP_DMDT_BUSERRINT_DSEDIE * (U4)ECC_BECCCAP_DMDT_ERRINT_DSE_DISABLE ) );

	/* BECCCAP_EMU */
	/* EM_BUSERRINT - Error Notification Control Register */
	REG_ECC_BECCCAP_EMU.unEM_BUSERRINT.u4Data = (U4)( ( (U4)ECC_BECCCAP_EMU_BUSERRINT_ADEDIE * (U4)ECC_BECCCAP_EMU_ERRINT_ADE_ENABLE  )
													 + ( (U4)ECC_BECCCAP_EMU_BUSERRINT_ASEDIE * (U4)ECC_BECCCAP_EMU_ERRINT_ASE_ENABLE  )
													 + ( (U4)ECC_BECCCAP_EMU_BUSERRINT_DDEDIE * (U4)ECC_BECCCAP_EMU_ERRINT_DDE_ENABLE  )
													 + ( (U4)ECC_BECCCAP_EMU_BUSERRINT_DSEDIE * (U4)ECC_BECCCAP_EMU_ERRINT_DSE_DISABLE ) );

	/* HBnECC(n = 90M/S, 92M/S, 94S, 97M, 98M, 911M, 912M) */
	for( i = (S4)0; i < (S4)HBNECC_CHANNEL_NUM; i++ )
	{
		t_pstReg_HbnEcc = (volatile Reg_Ecc_HbnEccType*)pcstReg_HbnEcc[i];

		/* HBECECCCTL - ECC Control Register(Reset初期値と同じ値) */
		t_u4RegValue = (U4)( t_pstReg_HbnEcc->unHBECECCCTL.u4Data & u4ERRH_ECC_MASK_ECC_HBNECC_HBECECCCTL );
		/* ECC_HBNECC_HBECECCCTL_AECCDISビットにEnable(0)をセット、 ECC_HBNECC_HBECECCCTL_SECDISビットにCorrect(0)をセット、 */
		/* ECC_HBNECC_HBECECCCTL_ECCDISビットにEnable(0)をセット。冗長となるため、処理は省略。														 */
		t_pstReg_HbnEcc->unHBECECCCTL.u4Data = t_u4RegValue;

		/* HBECERRINT - Error Notification Control Register */
		t_pstReg_HbnEcc->unHBECERRINT.u4Data = (U4)( ( (U4)ECC_HBNECC_HBECERRINT_ADEDIE * (U4)ECC_HBNECC_HBECERRINT_ADEDIE_ENABLE )
													+ ( (U4)ECC_HBNECC_HBECERRINT_ASEDIE * (U4)ECC_HBNECC_HBECERRINT_ASEDIE_ENABLE )
													+ ( (U4)ECC_HBNECC_HBECERRINT_DEDIE  * (U4)ECC_HBNECC_HBECERRINT_DEDIE_ENABLE  )
													+ ( (U4)ECC_HBNECC_HBECERRINT_SEDIE  * (U4)ECC_HBNECC_HBECERRINT_SEDIE_ENABLE  ) );

		/* HBECTSTCTL - ECC Test Control Register */
		t_pstReg_HbnEcc->unHBECTSTCTL.u4Data = (U4)ECC_HBNECC_HBECTSTCTL_ECCTST * (U4)ECC_HBNECC_HBECTSTCTL_ECCTST_NORMAL;
	}

	/* BECCCAP_V2An(n = 1-11) */
	for( i = (S4)0; i < (S4)V2AN_CHANNEL_NUM; i++ )
	{
		t_pstReg_V2an = (volatile Reg_Ecc_BeccCap_V2AnType*)pcstReg_V2an[i];

		/* PHC_BUSERRINT - Error Notification Control Register */
		t_pstReg_V2an->unPHC_BUSERRINT.u4Data = (U4)( ( (U4)ECC_BECCCAP_V2AN_BUSERRINT_ADEDIE * (U4)ECC_BECCCAP_V2AN_ERRINT_ADE_ENABLE  )
													 + ( (U4)ECC_BECCCAP_V2AN_BUSERRINT_ASEDIE * (U4)ECC_BECCCAP_V2AN_ERRINT_ASE_ENABLE  )
													 + ( (U4)ECC_BECCCAP_V2AN_BUSERRINT_DDEDIE * (U4)ECC_BECCCAP_V2AN_ERRINT_DDE_ENABLE  )
													 + ( (U4)ECC_BECCCAP_V2AN_BUSERRINT_DSEDIE * (U4)ECC_BECCCAP_V2AN_ERRINT_DSE_DISABLE ) );
	}

	/* DFPは非使用機能であり、クロック供給されていないため、レジスタ設定を行わない */

	/* Data transfer pathのECC制御レジスタのKey Code Protection再開 */
	for( i = (S4)0; i < (S4)PBNECC_CHANNEL_NUM; i++ )
	{
		t_pstReg_PbnEcc = (volatile Reg_Ecc_PbnEccType*)pcstReg_PbnEcc[i];
		t_pstReg_PbnEcc->unAPECKCPROT.u4Data = (U4)ECC_PBNECC_APECKCPROT_KCE_DISABLE;
		Bswlib_Sync_Pipeline_4( t_pstReg_PbnEcc->unAPECKCPROT.u4Data );
	}

	for( i = (S4)0; i < (S4)HBNECC_CHANNEL_NUM; i++ )
	{
		t_pstReg_HbnEcc = (volatile Reg_Ecc_HbnEccType*)pcstReg_HbnEcc[i];
		t_pstReg_HbnEcc->unHBECKCPROT.u4Data = (U4)ECC_HBNECC_HBECKCPROT_KCE_DISABLE;
		Bswlib_Sync_Pipeline_4( t_pstReg_HbnEcc->unHBECKCPROT.u4Data );
	}
}

/*----------------------------------------------------------------------------------------------*/
/*	ECC 1bit Error Clear Function( ROM/RAM )													*/
/*	return		: none																			*/
/*	parameters	: ModuleNumber																	*/
/*----------------------------------------------------------------------------------------------*/
static	void			ErrH_Ecc_ClearEcc1bitErrRomRam( U1 t_u1ModuleNum )
{
	S4										i;

	switch( t_u1ModuleNum )
	{
		case u1ERRH_ECC_CF:
#if ( MCU_TYPE_SERIES == MCU_RH850U2B6 )
			REG_ECC_MECCCAP_CFL.unCF_SSTCLR.u4Data = (U4)( ( (U4)ECC_MECCCAP_CFL_CF_SSTCLR_CLR03 * (U4)ECC_MECCCAP_CFL_CF_SSTCLR_CLEAR )
#elif ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
			REG_ECC_MECCCAP_CFL.unCF_SSTCLR.u4Data = (U4)( ( (U4)ECC_MECCCAP_CFL_CF_SSTCLR_CLR07 * (U4)ECC_MECCCAP_CFL_CF_SSTCLR_CLEAR )
														 + ( (U4)ECC_MECCCAP_CFL_CF_SSTCLR_CLR06 * (U4)ECC_MECCCAP_CFL_CF_SSTCLR_CLEAR )
														 + ( (U4)ECC_MECCCAP_CFL_CF_SSTCLR_CLR05 * (U4)ECC_MECCCAP_CFL_CF_SSTCLR_CLEAR )
														 + ( (U4)ECC_MECCCAP_CFL_CF_SSTCLR_CLR04 * (U4)ECC_MECCCAP_CFL_CF_SSTCLR_CLEAR )
														 + ( (U4)ECC_MECCCAP_CFL_CF_SSTCLR_CLR03 * (U4)ECC_MECCCAP_CFL_CF_SSTCLR_CLEAR )
#else
	#error "MCU_TYPE_SERIES is not supported"
#endif
														 + ( (U4)ECC_MECCCAP_CFL_CF_SSTCLR_CLR02 * (U4)ECC_MECCCAP_CFL_CF_SSTCLR_CLEAR )
														 + ( (U4)ECC_MECCCAP_CFL_CF_SSTCLR_CLR01 * (U4)ECC_MECCCAP_CFL_CF_SSTCLR_CLEAR )
														 + ( (U4)ECC_MECCCAP_CFL_CF_SSTCLR_CLR00 * (U4)ECC_MECCCAP_CFL_CF_SSTCLR_CLEAR ) );

			REG_ECC_MECCCAP_CFL.unCF_OVFCLR.u4Data = (U4)( ( (U4)ECC_MECCCAP_CFL_CF_OVFCLR_CLR1 * (U4)ECC_MECCCAP_CFL_CF_OVFCLR_CLEAR )
														 + ( (U4)ECC_MECCCAP_CFL_CF_OVFCLR_CLR0 * (U4)ECC_MECCCAP_CFL_CF_OVFCLR_CLEAR ) );
			Bswlib_Sync_Pipeline_4( REG_ECC_MECCCAP_CFL.unCF_OVFCLR.u4Data );
			break;

/*		case u1ERRH_ECC_DF: */
			/* 機能安全のDFのECC機能は非使用のため何もしない */
/*			break; */

		case u1ERRH_ECC_LRAM_LRPE0:
			REG_ECC_MECCCAP_LR_PE0CL0.unLR0_SSTCLR.u4Data = (U4)( ( (U4)ECC_MECCCAP_LR_PE0CL0_SSTCLR_07 * (U4)ECC_MECCCAP_LR_PE0CL0_SSTCLR_CLEAR )
																+ ( (U4)ECC_MECCCAP_LR_PE0CL0_SSTCLR_06 * (U4)ECC_MECCCAP_LR_PE0CL0_SSTCLR_CLEAR )
																+ ( (U4)ECC_MECCCAP_LR_PE0CL0_SSTCLR_05 * (U4)ECC_MECCCAP_LR_PE0CL0_SSTCLR_CLEAR )
																+ ( (U4)ECC_MECCCAP_LR_PE0CL0_SSTCLR_04 * (U4)ECC_MECCCAP_LR_PE0CL0_SSTCLR_CLEAR )
																+ ( (U4)ECC_MECCCAP_LR_PE0CL0_SSTCLR_03 * (U4)ECC_MECCCAP_LR_PE0CL0_SSTCLR_CLEAR )
																+ ( (U4)ECC_MECCCAP_LR_PE0CL0_SSTCLR_02 * (U4)ECC_MECCCAP_LR_PE0CL0_SSTCLR_CLEAR )
																+ ( (U4)ECC_MECCCAP_LR_PE0CL0_SSTCLR_01 * (U4)ECC_MECCCAP_LR_PE0CL0_SSTCLR_CLEAR )
																+ ( (U4)ECC_MECCCAP_LR_PE0CL0_SSTCLR_00 * (U4)ECC_MECCCAP_LR_PE0CL0_SSTCLR_CLEAR ) );

			REG_ECC_MECCCAP_LR_PE0CL0.unLR0_OVFCLR.u4Data = (U4)( ( (U4)ECC_MECCCAP_LR_PE0CL0_OVFCLR_1 * (U4)ECC_MECCCAP_LR_PE0CL0_OVFCLR_CLEAR )
																+ ( (U4)ECC_MECCCAP_LR_PE0CL0_OVFCLR_0 * (U4)ECC_MECCCAP_LR_PE0CL0_OVFCLR_CLEAR ) );

			for ( i = (S4)0; i < (S4)ECC_BUFFNUM_LRAM; i++ )
			{
				REG_ECC_MECCCAP_LR_PE0CL0.unLR0_kSESPIDCLR[i].u4Data = u4ERRH_ECC_ERROR_SPID_ALLCLEAR;
			}
			Bswlib_Sync_Pipeline_4( REG_ECC_MECCCAP_LR_PE0CL0.unLR0_kSESPIDCLR[ECC_BUFFNUM_LRAM - 1].u4Data );
			break;

		case u1ERRH_ECC_LRAM_LRPE1:
			REG_ECC_MECCCAP_LR_PE1CL0.unLR0_SSTCLR.u4Data = (U4)( ( (U4)ECC_MECCCAP_LR_PE1CL0_SSTCLR_07 * (U4)ECC_MECCCAP_LR_PE1CL0_SSTCLR_CLEAR )
																+ ( (U4)ECC_MECCCAP_LR_PE1CL0_SSTCLR_06 * (U4)ECC_MECCCAP_LR_PE1CL0_SSTCLR_CLEAR )
																+ ( (U4)ECC_MECCCAP_LR_PE1CL0_SSTCLR_05 * (U4)ECC_MECCCAP_LR_PE1CL0_SSTCLR_CLEAR )
																+ ( (U4)ECC_MECCCAP_LR_PE1CL0_SSTCLR_04 * (U4)ECC_MECCCAP_LR_PE1CL0_SSTCLR_CLEAR )
																+ ( (U4)ECC_MECCCAP_LR_PE1CL0_SSTCLR_03 * (U4)ECC_MECCCAP_LR_PE1CL0_SSTCLR_CLEAR )
																+ ( (U4)ECC_MECCCAP_LR_PE1CL0_SSTCLR_02 * (U4)ECC_MECCCAP_LR_PE1CL0_SSTCLR_CLEAR )
																+ ( (U4)ECC_MECCCAP_LR_PE1CL0_SSTCLR_01 * (U4)ECC_MECCCAP_LR_PE1CL0_SSTCLR_CLEAR )
																+ ( (U4)ECC_MECCCAP_LR_PE1CL0_SSTCLR_00 * (U4)ECC_MECCCAP_LR_PE1CL0_SSTCLR_CLEAR ) );

			REG_ECC_MECCCAP_LR_PE1CL0.unLR0_OVFCLR.u4Data = (U4)( ( (U4)ECC_MECCCAP_LR_PE1CL0_OVFCLR_1 * (U4)ECC_MECCCAP_LR_PE1CL0_OVFCLR_CLEAR )
																+ ( (U4)ECC_MECCCAP_LR_PE1CL0_OVFCLR_0 * (U4)ECC_MECCCAP_LR_PE1CL0_OVFCLR_CLEAR ) );

			for ( i = (S4)0; i < (S4)ECC_BUFFNUM_LRAM; i++ )
			{
				REG_ECC_MECCCAP_LR_PE1CL0.unLR0_kSESPIDCLR[i].u4Data = u4ERRH_ECC_ERROR_SPID_ALLCLEAR;
			}
			Bswlib_Sync_Pipeline_4( REG_ECC_MECCCAP_LR_PE1CL0.unLR0_kSESPIDCLR[ECC_BUFFNUM_LRAM - 1].u4Data );
			break;

#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_TRIPLECORE ) )	/* U2B10かつ3コア構成 */
		/* U2B6、またはU2B10かつ2コア構成の場合、Init時にECMへの通知を無効に設定しているため何もしない */
		case u1ERRH_ECC_LRAM_LRPE2:
			REG_ECC_MECCCAP_LR_PE2CL1.unLR0_SSTCLR.u4Data = (U4)( ( (U4)ECC_MECCCAP_LR_PE2CL1_SSTCLR_07 * (U4)ECC_MECCCAP_LR_PE2CL1_SSTCLR_CLEAR )
																+ ( (U4)ECC_MECCCAP_LR_PE2CL1_SSTCLR_06 * (U4)ECC_MECCCAP_LR_PE2CL1_SSTCLR_CLEAR )
																+ ( (U4)ECC_MECCCAP_LR_PE2CL1_SSTCLR_05 * (U4)ECC_MECCCAP_LR_PE2CL1_SSTCLR_CLEAR )
																+ ( (U4)ECC_MECCCAP_LR_PE2CL1_SSTCLR_04 * (U4)ECC_MECCCAP_LR_PE2CL1_SSTCLR_CLEAR )
																+ ( (U4)ECC_MECCCAP_LR_PE2CL1_SSTCLR_03 * (U4)ECC_MECCCAP_LR_PE2CL1_SSTCLR_CLEAR )
																+ ( (U4)ECC_MECCCAP_LR_PE2CL1_SSTCLR_02 * (U4)ECC_MECCCAP_LR_PE2CL1_SSTCLR_CLEAR )
																+ ( (U4)ECC_MECCCAP_LR_PE2CL1_SSTCLR_01 * (U4)ECC_MECCCAP_LR_PE2CL1_SSTCLR_CLEAR )
																+ ( (U4)ECC_MECCCAP_LR_PE2CL1_SSTCLR_00 * (U4)ECC_MECCCAP_LR_PE2CL1_SSTCLR_CLEAR ) );

			REG_ECC_MECCCAP_LR_PE2CL1.unLR0_OVFCLR.u4Data = (U4)( ( (U4)ECC_MECCCAP_LR_PE2CL1_OVFCLR_1 * (U4)ECC_MECCCAP_LR_PE2CL1_OVFCLR_CLEAR )
																+ ( (U4)ECC_MECCCAP_LR_PE2CL1_OVFCLR_0 * (U4)ECC_MECCCAP_LR_PE2CL1_OVFCLR_CLEAR ) );

			for ( i = (S4)0; i < (S4)ECC_BUFFNUM_LRAM; i++ )
			{
				REG_ECC_MECCCAP_LR_PE2CL1.unLR0_kSESPIDCLR[i].u4Data = u4ERRH_ECC_ERROR_SPID_ALLCLEAR;
			}
			Bswlib_Sync_Pipeline_4( REG_ECC_MECCCAP_LR_PE2CL1.unLR0_kSESPIDCLR[ECC_BUFFNUM_LRAM - 1].u4Data );
			break;
#endif

/*		case u1ERRH_ECC_LRAM_LRPE3: */
			/* 機能安全はCore3を使用しないため何もしない */

		case u1ERRH_ECC_LRAM_LRA:
			REG_ECC_MECCCAP_LRA.unLR1_SSTCLR.u4Data = (U4)( ( (U4)ECC_MECCCAP_LRA_LR1_SSTCLR_07 * (U4)ECC_MECCCAP_LRA_LR1_SSTCLR_CLEAR )
														  + ( (U4)ECC_MECCCAP_LRA_LR1_SSTCLR_06 * (U4)ECC_MECCCAP_LRA_LR1_SSTCLR_CLEAR )
														  + ( (U4)ECC_MECCCAP_LRA_LR1_SSTCLR_05 * (U4)ECC_MECCCAP_LRA_LR1_SSTCLR_CLEAR )
														  + ( (U4)ECC_MECCCAP_LRA_LR1_SSTCLR_04 * (U4)ECC_MECCCAP_LRA_LR1_SSTCLR_CLEAR )
														  + ( (U4)ECC_MECCCAP_LRA_LR1_SSTCLR_03 * (U4)ECC_MECCCAP_LRA_LR1_SSTCLR_CLEAR )
														  + ( (U4)ECC_MECCCAP_LRA_LR1_SSTCLR_02 * (U4)ECC_MECCCAP_LRA_LR1_SSTCLR_CLEAR )
														  + ( (U4)ECC_MECCCAP_LRA_LR1_SSTCLR_01 * (U4)ECC_MECCCAP_LRA_LR1_SSTCLR_CLEAR )
														  + ( (U4)ECC_MECCCAP_LRA_LR1_SSTCLR_00 * (U4)ECC_MECCCAP_LRA_LR1_SSTCLR_CLEAR ) );

			REG_ECC_MECCCAP_LRA.unLR1_OVFCLR.u4Data = (U4)( ( (U4)ECC_MECCCAP_LRA_LR1_OVFCLR_1 * (U4)ECC_MECCCAP_LRA_LR1_OVFCLR_CLEAR )
														  + ( (U4)ECC_MECCCAP_LRA_LR1_OVFCLR_0 * (U4)ECC_MECCCAP_LRA_LR1_OVFCLR_CLEAR ) );

			for ( i = (S4)0; i < (S4)ECC_BUFFNUM_LRAM; i++ )
			{
				REG_ECC_MECCCAP_LRA.unLR1_kSESPIDCLR[i].u4Data = u4ERRH_ECC_ERROR_SPID_ALLCLEAR;
			}
			Bswlib_Sync_Pipeline_4( REG_ECC_MECCCAP_LRA.unLR1_kSESPIDCLR[ECC_BUFFNUM_LRAM - 1].u4Data );
			break;

		case u1ERRH_ECC_CRAM_CRAM:
			REG_ECC_MECCCAP_CRAM.unCR_SSTCLR.u4Data = (U4)( ( (U4)ECC_MECCCAP_CRAM_CR_SSTCLR_07 * (U4)ECC_MECCCAP_CRAM_CR_SSTCLR_CLEAR )
														  + ( (U4)ECC_MECCCAP_CRAM_CR_SSTCLR_06 * (U4)ECC_MECCCAP_CRAM_CR_SSTCLR_CLEAR )
														  + ( (U4)ECC_MECCCAP_CRAM_CR_SSTCLR_05 * (U4)ECC_MECCCAP_CRAM_CR_SSTCLR_CLEAR )
														  + ( (U4)ECC_MECCCAP_CRAM_CR_SSTCLR_04 * (U4)ECC_MECCCAP_CRAM_CR_SSTCLR_CLEAR )
														  + ( (U4)ECC_MECCCAP_CRAM_CR_SSTCLR_03 * (U4)ECC_MECCCAP_CRAM_CR_SSTCLR_CLEAR )
														  + ( (U4)ECC_MECCCAP_CRAM_CR_SSTCLR_02 * (U4)ECC_MECCCAP_CRAM_CR_SSTCLR_CLEAR )
														  + ( (U4)ECC_MECCCAP_CRAM_CR_SSTCLR_01 * (U4)ECC_MECCCAP_CRAM_CR_SSTCLR_CLEAR )
														  + ( (U4)ECC_MECCCAP_CRAM_CR_SSTCLR_00 * (U4)ECC_MECCCAP_CRAM_CR_SSTCLR_CLEAR ) );

			REG_ECC_MECCCAP_CRAM.unCR_OVFCLR.u4Data = (U4)( ( (U4)ECC_MECCCAP_CRAM_CR_OVFCLR_1 * (U4)ECC_MECCCAP_CRAM_CR_OVFCLR_CLEAR )
														  + ( (U4)ECC_MECCCAP_CRAM_CR_OVFCLR_0 * (U4)ECC_MECCCAP_CRAM_CR_OVFCLR_CLEAR ) );

			for ( i = (S4)0; i < (S4)ECC_BUFFNUM_CRAM; i++ )
			{
				REG_ECC_MECCCAP_CRAM.unCR_kSESPIDCLR[i].u4Data = u4ERRH_ECC_ERROR_SPID_ALLCLEAR;
			}
			Bswlib_Sync_Pipeline_4( REG_ECC_MECCCAP_CRAM.unCR_kSESPIDCLR[ECC_BUFFNUM_CRAM - 1].u4Data );
			break;

		case u1ERRH_ECC_IC_ITPE0:
			REG_ECC_MECCCAP_IT_PE0CL0.unIT_SSTCLR.u4Data = (U4)ECC_MECCCAP_IT_PE0CL0_SSTCLR_SSTCLR00 * (U4)ECC_MECCCAP_IT_PE0CL0_SSTCLR_CLEAR;

			REG_ECC_MECCCAP_IT_PE0CL0.unIT_OVFCLR.u4Data = (U4)( ( (U4)ECC_MECCCAP_IT_PE0CL0_OVFCLR_1 * (U4)ECC_MECCCAP_IT_PE0CL0_OVFCLR_CLEAR )
															   + ( (U4)ECC_MECCCAP_IT_PE0CL0_OVFCLR_0 * (U4)ECC_MECCCAP_IT_PE0CL0_OVFCLR_CLEAR ) );
			Bswlib_Sync_Pipeline_4( REG_ECC_MECCCAP_IT_PE0CL0.unIT_OVFCLR.u4Data );
			break;

		case u1ERRH_ECC_IC_ITPE1:
			REG_ECC_MECCCAP_IT_PE1CL0.unIT_SSTCLR.u4Data = (U4)ECC_MECCCAP_IT_PE1CL0_SSTCLR_SSTCLR00 * (U4)ECC_MECCCAP_IT_PE1CL0_SSTCLR_CLEAR;

			REG_ECC_MECCCAP_IT_PE1CL0.unIT_OVFCLR.u4Data = (U4)( ( (U4)ECC_MECCCAP_IT_PE1CL0_OVFCLR_1 * (U4)ECC_MECCCAP_IT_PE1CL0_OVFCLR_CLEAR )
															   + ( (U4)ECC_MECCCAP_IT_PE1CL0_OVFCLR_0 * (U4)ECC_MECCCAP_IT_PE1CL0_OVFCLR_CLEAR ) );
			Bswlib_Sync_Pipeline_4( REG_ECC_MECCCAP_IT_PE1CL0.unIT_OVFCLR.u4Data );
			break;

#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_TRIPLECORE ) )	/* U2B10かつ3コア構成 */
		/* U2B6、またはU2B10かつ2コア構成の場合、Init時にECMへの通知を無効に設定しているため何もしない */
		case u1ERRH_ECC_IC_ITPE2:
			REG_ECC_MECCCAP_IT_PE2CL1.unIT_SSTCLR.u4Data = (U4)ECC_MECCCAP_IT_PE2CL1_SSTCLR_SSTCLR00 * (U4)ECC_MECCCAP_IT_PE2CL1_SSTCLR_CLEAR;

			REG_ECC_MECCCAP_IT_PE2CL1.unIT_OVFCLR.u4Data = (U4)( ( (U4)ECC_MECCCAP_IT_PE2CL1_OVFCLR_1 * (U4)ECC_MECCCAP_IT_PE2CL1_OVFCLR_CLEAR )
															   + ( (U4)ECC_MECCCAP_IT_PE2CL1_OVFCLR_0 * (U4)ECC_MECCCAP_IT_PE2CL1_OVFCLR_CLEAR ) );
			Bswlib_Sync_Pipeline_4( REG_ECC_MECCCAP_IT_PE1CL0.unIT_OVFCLR.u4Data );
			break;
#endif

/*		case u1ERRH_ECC_IC_ITPE3: */
			/* 機能安全はCore3を使用しないため何もしない */

		case u1ERRH_ECC_IC_IDPE0:
			REG_ECC_MECCCAP_ID_PE0CL0.unID_SSTCLR.u4Data = (U4)ECC_MECCCAP_ID_PE0CL0_SSTCLR_SSTCLR00 * (U4)ECC_MECCCAP_ID_PE0CL0_SSTCLR_CLEAR;

			REG_ECC_MECCCAP_ID_PE0CL0.unID_OVFCLR.u4Data = (U4)( ( (U4)ECC_MECCCAP_ID_PE0CL0_OVFCLR_1 * (U4)ECC_MECCCAP_ID_PE0CL0_OVFCLR_CLEAR )
															   + ( (U4)ECC_MECCCAP_ID_PE0CL0_OVFCLR_0 * (U4)ECC_MECCCAP_ID_PE0CL0_OVFCLR_CLEAR ) );
			Bswlib_Sync_Pipeline_4( REG_ECC_MECCCAP_ID_PE0CL0.unID_OVFCLR.u4Data );
			break;

		case u1ERRH_ECC_IC_IDPE1:
			REG_ECC_MECCCAP_ID_PE1CL0.unID_SSTCLR.u4Data = (U4)ECC_MECCCAP_ID_PE1CL0_SSTCLR_SSTCLR00 * (U4)ECC_MECCCAP_ID_PE1CL0_SSTCLR_CLEAR;

			REG_ECC_MECCCAP_ID_PE1CL0.unID_OVFCLR.u4Data = (U4)( ( (U4)ECC_MECCCAP_ID_PE1CL0_OVFCLR_1 * (U4)ECC_MECCCAP_ID_PE1CL0_OVFCLR_CLEAR )
															   + ( (U4)ECC_MECCCAP_ID_PE1CL0_OVFCLR_0 * (U4)ECC_MECCCAP_ID_PE1CL0_OVFCLR_CLEAR ) );
			Bswlib_Sync_Pipeline_4( REG_ECC_MECCCAP_ID_PE1CL0.unID_OVFCLR.u4Data );
			break;

#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_TRIPLECORE ) )	/* U2B10かつ3コア構成 */
		/* U2B6、またはU2B10かつ2コア構成の場合、Init時にECMへの通知を無効に設定しているため何もしない */
		case u1ERRH_ECC_IC_IDPE2:
			REG_ECC_MECCCAP_ID_PE2CL1.unID_SSTCLR.u4Data = (U4)ECC_MECCCAP_ID_PE2CL1_SSTCLR_SSTCLR00 * (U4)ECC_MECCCAP_ID_PE2CL1_SSTCLR_CLEAR;

			REG_ECC_MECCCAP_ID_PE2CL1.unID_OVFCLR.u4Data = (U4)( ( (U4)ECC_MECCCAP_ID_PE2CL1_OVFCLR_1 * (U4)ECC_MECCCAP_ID_PE2CL1_OVFCLR_CLEAR )
															   + ( (U4)ECC_MECCCAP_ID_PE2CL1_OVFCLR_0 * (U4)ECC_MECCCAP_ID_PE2CL1_OVFCLR_CLEAR ) );
			Bswlib_Sync_Pipeline_4( REG_ECC_MECCCAP_ID_PE2CL1.unID_OVFCLR.u4Data );
			break;
#endif

/*		case u1ERRH_ECC_IC_IDPE3: */
			/* 機能安全はCore3を使用しないため何もしない */

		default:
			/* 何もしない */
			break;
	}
}

/*----------------------------------------------------------------------------------------------*/
/*	ECC 1bit Error Clear Function( Peripheral )													*/
/*	return		: none																			*/
/*	parameters	: ModuleNumber																	*/
/*----------------------------------------------------------------------------------------------*/
static	void			ErrH_Ecc_ClearEcc1bitErrPeripheral( U1 t_u1ModuleNum )
{
	volatile Reg_Ecc_Ecc7Type*				t_pstReg_Ecc7;
	volatile Reg_Ecc_Ecc6Type*				t_pstReg_Ecc6;
	U2										t_u2RegData;

	switch( t_u1ModuleNum )
	{
		case u1ERRH_ECC_DTS:
			REG_ECC_MECCCAP_DTS.unDR_SSTCLR.u4Data = (U4)ECC_MECCCAP_DTS_DR_SSTCLR_SSTCLR00 * (U4)ECC_MECCCAP_DTS_DR_SSTCLR_CLEAR;
			REG_ECC_MECCCAP_DTS.unDR_OVFCLR.u4Data = (U4)ECC_MECCCAP_DTS_DR_OVFCLR_SERROVFCLR0 * (U4)ECC_MECCCAP_DTS_DR_OVFCLR_CLEAR;
			Bswlib_Sync_Pipeline_4( REG_ECC_MECCCAP_DTS.unDR_OVFCLR.u4Data );
			break;

		case u1ERRH_ECC_DMDE_DMDE0:
			REG_ECC_MECCCAP_DMDE0.unDE_SSTCLR.u4Data = (U4)ECC_MECCCAP_DMDE0_DE_SSTCLR_SSTCLR00 * (U4)ECC_MECCCAP_DMDE0_DE_SSTCLR_CLEAR;
			REG_ECC_MECCCAP_DMDE0.unDE_OVFCLR.u4Data = (U4)ECC_MECCCAP_DMDE0_DE_OVFCLR_SERROVFCLR0 * (U4)ECC_MECCCAP_DMDE0_DE_OVFCLR_CLEAR;
			Bswlib_Sync_Pipeline_4( REG_ECC_MECCCAP_DMDE0.unDE_OVFCLR.u4Data );
			break;

#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
		case u1ERRH_ECC_DMDE_DMDE1:
			REG_ECC_MECCCAP_DMDE1.unDE_SSTCLR.u4Data = (U4)ECC_MECCCAP_DMDE1_DE_SSTCLR_SSTCLR00 * (U4)ECC_MECCCAP_DMDE1_DE_SSTCLR_CLEAR;
			REG_ECC_MECCCAP_DMDE1.unDE_OVFCLR.u4Data = (U4)ECC_MECCCAP_DMDE1_DE_OVFCLR_SERROVFCLR0 * (U4)ECC_MECCCAP_DMDE1_DE_OVFCLR_CLEAR;
			Bswlib_Sync_Pipeline_4( REG_ECC_MECCCAP_DMDE1.unDE_OVFCLR.u4Data );
			break;
#endif

		case u1ERRH_ECC_DMDA_DMDA0:
			REG_ECC_MECCCAP_DMDA0.unDA_SSTCLR.u4Data = (U4)ECC_MECCCAP_DMDA0_DA_SSTCLR_SSTCLR00 * (U4)ECC_MECCCAP_DMDA0_DA_SSTCLR_CLEAR;
			REG_ECC_MECCCAP_DMDA0.unDA_OVFCLR.u4Data = (U4)ECC_MECCCAP_DMDA0_DA_OVFCLR_SERROVFCLR0 * (U4)ECC_MECCCAP_DMDA0_DA_OVFCLR_CLEAR;
			Bswlib_Sync_Pipeline_4( REG_ECC_MECCCAP_DMDA0.unDA_OVFCLR.u4Data );
			break;

#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
		case u1ERRH_ECC_DMDA_DMDA1:
			REG_ECC_MECCCAP_DMDA1.unDA_SSTCLR.u4Data = (U4)ECC_MECCCAP_DMDA1_DA_SSTCLR_SSTCLR00 * (U4)ECC_MECCCAP_DMDA1_DA_SSTCLR_CLEAR;
			REG_ECC_MECCCAP_DMDA1.unDA_OVFCLR.u4Data = (U4)ECC_MECCCAP_DMDA1_DA_OVFCLR_SERROVFCLR0 * (U4)ECC_MECCCAP_DMDA1_DA_OVFCLR_CLEAR;
			Bswlib_Sync_Pipeline_4( REG_ECC_MECCCAP_DMDA1.unDA_OVFCLR.u4Data );
			break;
#endif

		/* Peripheral RAMのオーバフローフラグクリア方法は */
		/* ECC 1bit、2bitエラーフラグのクリアのため、ECC 2bitエラーのクリアも行う */
		case u1ERRH_ECC_PR32_E7RC01:
		case u1ERRH_ECC_PR32_E7RC02:
		case u1ERRH_ECC_PR32_E7RC03:
		case u1ERRH_ECC_PR32_E7RC04:
		case u1ERRH_ECC_PR32_E7MS00:
		case u1ERRH_ECC_PR32_E7MS01:
		case u1ERRH_ECC_PR32_E7MS02:
		case u1ERRH_ECC_PR32_E7MS03:
		case u1ERRH_ECC_PR32_E7MS04:
		case u1ERRH_ECC_PR32_E7MS05:
		case u1ERRH_ECC_PR32_E7MS06:
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
		case u1ERRH_ECC_PR32_E7MS07:
		case u1ERRH_ECC_PR32_E7MS08:
		case u1ERRH_ECC_PR32_E7MS09:
#endif
		case u1ERRH_ECC_PR32_E7DF00:
		case u1ERRH_ECC_PR32_E7DF10:
			t_pstReg_Ecc7 = (volatile Reg_Ecc_Ecc7Type*)pcstReg_Ecc7[t_u1ModuleNum - u1ERRH_ECC_PR32_OFFSET];
			t_u2RegData = t_pstReg_Ecc7->unE710CTL.u2Data & (U2)(~( (U2)ECC_ECC7_E710CTL_ECER2C | (U2)ECC_ECC7_E710CTL_ECER1C ));
			t_pstReg_Ecc7->unE710CTL.u2Data = (U2)( ( (U2)ECC_ECC7_E710CTL_ECER2C * (U2)ECC_ECC7_E710CTL_ECER2C_WRITE )
												   + ( (U2)ECC_ECC7_E710CTL_ECER1C * (U2)ECC_ECC7_E710CTL_ECER1C_WRITE )
												   + t_u2RegData );
			Bswlib_Sync_Pipeline_2( t_pstReg_Ecc7->unE710CTL.u2Data );
			break;

/*		case u1ERRH_ECC_PR32_E7FR00: */
/*		case u1ERRH_ECC_PR32_E7FR01: */
/*		case u1ERRH_ECC_PR32_E7FR02: */
			/* FlexRayは非使用のため何もしない */
/*			break; */

/*		case u1ERRH_ECC_PR32_E7GT00: */
/*		case u1ERRH_ECC_PR32_E7GT01: */
/*		case u1ERRH_ECC_PR32_E7GT10: */
/*		case u1ERRH_ECC_PR32_E7GT11: */
/*		case u1ERRH_ECC_PR32_E7GT20: */
/*		case u1ERRH_ECC_PR32_E7GT21: */
/*		case u1ERRH_ECC_PR32_E7GT30: */
/*		case u1ERRH_ECC_PR32_E7GT31: */
/*		case u1ERRH_ECC_PR32_E7GT40: */
/*		case u1ERRH_ECC_PR32_E7GT41: */
/*		case u1ERRH_ECC_PR32_E7GT50: */
/*		case u1ERRH_ECC_PR32_E7GT51: */
/*		case u1ERRH_ECC_PR32_E7GT60: */
/*		case u1ERRH_ECC_PR32_E7GT61: */
/*		case u1ERRH_ECC_PR32_E7GT100: */
/*		case u1ERRH_ECC_PR32_E7GT101: */
/*		case u1ERRH_ECC_PR32_E7GT102: */
/*		case u1ERRH_ECC_PR32_E7GT110: */
/*		case u1ERRH_ECC_PR32_E7GT111: */
/*		case u1ERRH_ECC_PR32_E7GT112: */
			/* GTMは非使用のため何もしない */
/*			break; */

/*		case u1ERRH_ECC_PR32_E7MM00: */
/*		case u1ERRH_ECC_PR32_E7MM01: */
			/* MMCAは非使用のため何もしない */
/*			break; */

/*		case u1ERRH_ECC_PR32_E7ES00: */
/*		case u1ERRH_ECC_PR32_E7ES01: */
/*		case u1ERRH_ECC_PR32_E7ES02: */
/*		case u1ERRH_ECC_PR32_E7ES03: */
/*		case u1ERRH_ECC_PR32_E7ES04: */
/*		case u1ERRH_ECC_PR32_E7ES05: */
			/* Ethernetは非使用のため何もしない */
/*			break; */

		case u1ERRH_ECC_PR16_E6DF00:
		case u1ERRH_ECC_PR16_E6DF01:
		case u1ERRH_ECC_PR16_E6DF10:
		case u1ERRH_ECC_PR16_E6DF11:
			t_pstReg_Ecc6 = (volatile Reg_Ecc_Ecc6Type*)pcstReg_Ecc6[t_u1ModuleNum - u1ERRH_ECC_PR16_OFFSET];
			t_u2RegData = t_pstReg_Ecc6->unE610CTL.u2Data & (U2)(~( (U2)ECC_ECC6_E610CTL_ECER2C | (U2)ECC_ECC6_E610CTL_ECER1C ));
			t_pstReg_Ecc6->unE610CTL.u2Data = (U2)( ( (U2)ECC_ECC6_E610CTL_ECER2C * (U2)ECC_ECC6_E610CTL_ECER2C_WRITE )
												   + ( (U2)ECC_ECC6_E610CTL_ECER1C * (U2)ECC_ECC6_E610CTL_ECER1C_WRITE )
												   + t_u2RegData );
			Bswlib_Sync_Pipeline_2( t_pstReg_Ecc6->unE610CTL.u2Data );
			break;

		default:
			/* 何もしない */
			break;
	}
}

/*----------------------------------------------------------------------------------------------*/
/*	ECC 1bit Error Clear Function( DTP Addresss)												*/
/*	return		: none																			*/
/*	parameters	: ModuleNumber																	*/
/*----------------------------------------------------------------------------------------------*/
static	void			ErrH_Ecc_ClearEcc1bitErrDtpAddr( U1 t_u1ModuleNum )
{
	volatile Reg_Ecc_HbnEccType*			t_pstReg_HbnEcc;
	volatile Reg_Ecc_BeccCap_V2AnType*		t_pstReg_V2an;

	switch( t_u1ModuleNum )
	{
		/* Data Transfer Pathはオーバフローエラーは存在しない */
		case u1ERRH_ECC_DTP_LRAM_ADDR:
			REG_ECC_BECCCAP_LRAM.unLR_BUSASSTCLR.u4Data = (U4)( ( (U4)ECC_BECCCAP_LRAM_BUSASSTCLR_17 * (U4)ECC_BECCCAP_LRAM_BUSASSTCLR_CLEAR )
															  + ( (U4)ECC_BECCCAP_LRAM_BUSASSTCLR_16 * (U4)ECC_BECCCAP_LRAM_BUSASSTCLR_CLEAR )
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
															  + ( (U4)ECC_BECCCAP_LRAM_BUSASSTCLR_03 * (U4)ECC_BECCCAP_LRAM_BUSASSTCLR_CLEAR )
#endif
															  + ( (U4)ECC_BECCCAP_LRAM_BUSASSTCLR_02 * (U4)ECC_BECCCAP_LRAM_BUSASSTCLR_CLEAR )
															  + ( (U4)ECC_BECCCAP_LRAM_BUSASSTCLR_01 * (U4)ECC_BECCCAP_LRAM_BUSASSTCLR_CLEAR )
															  + ( (U4)ECC_BECCCAP_LRAM_BUSASSTCLR_00 * (U4)ECC_BECCCAP_LRAM_BUSASSTCLR_CLEAR ) );

			Bswlib_Sync_Pipeline_4( REG_ECC_BECCCAP_LRAM.unLR_BUSASSTCLR.u4Data );
			break;

		case u1ERRH_ECC_DTP_CRAM_ADDR:
#if ( MCU_TYPE_SERIES == MCU_RH850U2B6 )
			REG_ECC_BECCCAP_CRAM.unCR_BUSASSTCLR.u4Data = (U4)( ( (U4)ECC_BECCCAP_CRAM_BUSASSTCLR_24 * (U4)ECC_BECCCAP_CRAM_BUSASSTCLR_CLEAR )
#elif ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
			REG_ECC_BECCCAP_CRAM.unCR_BUSASSTCLR.u4Data = (U4)( ( (U4)ECC_BECCCAP_CRAM_BUSASSTCLR_25 * (U4)ECC_BECCCAP_CRAM_BUSASSTCLR_CLEAR )
															  + ( (U4)ECC_BECCCAP_CRAM_BUSASSTCLR_24 * (U4)ECC_BECCCAP_CRAM_BUSASSTCLR_CLEAR )
															  + ( (U4)ECC_BECCCAP_CRAM_BUSASSTCLR_06 * (U4)ECC_BECCCAP_CRAM_BUSASSTCLR_CLEAR )
															  + ( (U4)ECC_BECCCAP_CRAM_BUSASSTCLR_05 * (U4)ECC_BECCCAP_CRAM_BUSASSTCLR_CLEAR )
															  + ( (U4)ECC_BECCCAP_CRAM_BUSASSTCLR_04 * (U4)ECC_BECCCAP_CRAM_BUSASSTCLR_CLEAR )
#else
	#error "MCU_TYPE_SERIES is not supported"
#endif
															  + ( (U4)ECC_BECCCAP_CRAM_BUSASSTCLR_02 * (U4)ECC_BECCCAP_CRAM_BUSASSTCLR_CLEAR )
															  + ( (U4)ECC_BECCCAP_CRAM_BUSASSTCLR_01 * (U4)ECC_BECCCAP_CRAM_BUSASSTCLR_CLEAR )
															  + ( (U4)ECC_BECCCAP_CRAM_BUSASSTCLR_00 * (U4)ECC_BECCCAP_CRAM_BUSASSTCLR_CLEAR ) );

			Bswlib_Sync_Pipeline_4( REG_ECC_BECCCAP_CRAM.unCR_BUSASSTCLR.u4Data );
			break;

		case u1ERRH_ECC_DTP_CFL_ADDR:
#if ( MCU_TYPE_SERIES == MCU_RH850U2B6 )
			REG_ECC_BECCCAP_CFL.unCF_BUSASSTCLR.u4Data = (U4)( ( (U4)ECC_BECCCAP_CFL_BUSASSTCLR_24 * (U4)ECC_BECCCAP_CFL_BUSASSTCLR_CLEAR )
#elif ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
			REG_ECC_BECCCAP_CFL.unCF_BUSASSTCLR.u4Data = (U4)( ( (U4)ECC_BECCCAP_CFL_BUSASSTCLR_25 * (U4)ECC_BECCCAP_CFL_BUSASSTCLR_CLEAR )
															 + ( (U4)ECC_BECCCAP_CFL_BUSASSTCLR_24 * (U4)ECC_BECCCAP_CFL_BUSASSTCLR_CLEAR )
															 + ( (U4)ECC_BECCCAP_CFL_BUSASSTCLR_05 * (U4)ECC_BECCCAP_CFL_BUSASSTCLR_CLEAR )
															 + ( (U4)ECC_BECCCAP_CFL_BUSASSTCLR_04 * (U4)ECC_BECCCAP_CFL_BUSASSTCLR_CLEAR )
#else
    #error "MCU_TYPE_SERIES is not supported"
#endif
															 + ( (U4)ECC_BECCCAP_CFL_BUSASSTCLR_01 * (U4)ECC_BECCCAP_CFL_BUSASSTCLR_CLEAR )
															 + ( (U4)ECC_BECCCAP_CFL_BUSASSTCLR_00 * (U4)ECC_BECCCAP_CFL_BUSASSTCLR_CLEAR ) );

			Bswlib_Sync_Pipeline_4( REG_ECC_BECCCAP_CFL.unCF_BUSASSTCLR.u4Data );
			break;

		case u1ERRH_ECC_DTP_PERI_ADDR:
			REG_ECC_BECCCAP_PERI.unPH_BUSASSTCLR.u4Data = (U4)( ( (U4)ECC_BECCCAP_PERI_BUSASSTCLR_25 * (U4)ECC_BECCCAP_PERI_BUSASSTCLR_CLEAR )
															  + ( (U4)ECC_BECCCAP_PERI_BUSASSTCLR_20 * (U4)ECC_BECCCAP_PERI_BUSASSTCLR_CLEAR )

															  + ( (U4)ECC_BECCCAP_PERI_BUSASSTCLR_18 * (U4)ECC_BECCCAP_PERI_BUSASSTCLR_CLEAR )
															  + ( (U4)ECC_BECCCAP_PERI_BUSASSTCLR_17 * (U4)ECC_BECCCAP_PERI_BUSASSTCLR_CLEAR )
															  + ( (U4)ECC_BECCCAP_PERI_BUSASSTCLR_16 * (U4)ECC_BECCCAP_PERI_BUSASSTCLR_CLEAR ) );
			Bswlib_Sync_Pipeline_4( REG_ECC_BECCCAP_PERI.unPH_BUSASSTCLR.u4Data );
			break;

		case u1ERRH_ECC_DTP_EMU_ADDR:
#if ( MCU_TYPE_SERIES == MCU_RH850U2B6 )
			REG_ECC_BECCCAP_EMU.unEM_BUSASSTCLR.u4Data = (U4)( ( (U4)ECC_BECCCAP_EMU_BUSASSTCLR_17 * (U4)ECC_BECCCAP_EMU_BUSASSTCLR_CLEAR )
#elif ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
			REG_ECC_BECCCAP_EMU.unEM_BUSASSTCLR.u4Data = (U4)( ( (U4)ECC_BECCCAP_EMU_BUSASSTCLR_18 * (U4)ECC_BECCCAP_EMU_BUSASSTCLR_CLEAR )
															 + ( (U4)ECC_BECCCAP_EMU_BUSASSTCLR_17 * (U4)ECC_BECCCAP_EMU_BUSASSTCLR_CLEAR )
#else
	#error "MCU_TYPE_SERIES is not supported"
#endif
															 + ( (U4)ECC_BECCCAP_EMU_BUSASSTCLR_16 * (U4)ECC_BECCCAP_EMU_BUSASSTCLR_CLEAR )
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
															 + ( (U4)ECC_BECCCAP_EMU_BUSASSTCLR_06 * (U4)ECC_BECCCAP_EMU_BUSASSTCLR_CLEAR )
#endif
															 + ( (U4)ECC_BECCCAP_EMU_BUSASSTCLR_04 * (U4)ECC_BECCCAP_EMU_BUSASSTCLR_CLEAR )
															 + ( (U4)ECC_BECCCAP_EMU_BUSASSTCLR_02 * (U4)ECC_BECCCAP_EMU_BUSASSTCLR_CLEAR )
															 + ( (U4)ECC_BECCCAP_EMU_BUSASSTCLR_00 * (U4)ECC_BECCCAP_EMU_BUSASSTCLR_CLEAR ) );

			Bswlib_Sync_Pipeline_4( REG_ECC_BECCCAP_EMU.unEM_BUSASSTCLR.u4Data );
			break;

		/* HBnECCはデータ、アドレスのECC 2bit、1bitエラーをすべてクリアする(ハード仕様) */
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
		case u1ERRH_ECC_DTP_HB90MECC_ADDR:
		case u1ERRH_ECC_DTP_HB90SECC_ADDR:
#endif
		case u1ERRH_ECC_DTP_HB92MECC_ADDR:
		case u1ERRH_ECC_DTP_HB92SECC_ADDR:
		case u1ERRH_ECC_DTP_HB94SECC_ADDR:
		case u1ERRH_ECC_DTP_HB97MECC_ADDR:
		case u1ERRH_ECC_DTP_HB98MECC_ADDR:
#if ( MCU_TYPE_SERIES == MCU_RH850U2B6)
		case u1ERRH_ECC_DTP_HB911MECC_ADDR:
		case u1ERRH_ECC_DTP_HB912MECC_ADDR:
#endif
			t_pstReg_HbnEcc = (volatile Reg_Ecc_HbnEccType*)pcstReg_HbnEcc[t_u1ModuleNum - u1ERRH_ECC_HBNECC_ADDR_OFFSET];
			t_pstReg_HbnEcc->unHBECSTCLR.u4Data = (U4)ECC_HBNECC_HBECSTCLR_STCLR0 * (U4)ECC_HBNECC_HBECSTCLR_CLEAR;
			Bswlib_Sync_Pipeline_4( t_pstReg_HbnEcc->unHBECSTCLR.u4Data );
			break;

		case u1ERRH_ECC_DTP_V2A1_ADDR:
		case u1ERRH_ECC_DTP_V2A2_ADDR:
		case u1ERRH_ECC_DTP_V2A3_ADDR:
		case u1ERRH_ECC_DTP_V2A4_ADDR:
		case u1ERRH_ECC_DTP_V2A5_ADDR:
		case u1ERRH_ECC_DTP_V2A6_ADDR:
		case u1ERRH_ECC_DTP_V2A7_ADDR:
		case u1ERRH_ECC_DTP_V2A8_ADDR:
		case u1ERRH_ECC_DTP_V2A9_ADDR:
		case u1ERRH_ECC_DTP_V2A10_ADDR:
		case u1ERRH_ECC_DTP_V2A11_ADDR:
			t_pstReg_V2an = (volatile Reg_Ecc_BeccCap_V2AnType*)pcstReg_V2an[t_u1ModuleNum - u1ERRH_ECC_V2AN_ADDR_OFFSET];
			t_pstReg_V2an->unPHC_BUSASSTCLR.u4Data = (U4)ECC_BECCCAP_V2AN_BUSASSTCLR_ASSTCLR00 * (U4)ECC_BECCCAP_V2AN_BUSASSTCLR_CLEAR;
			Bswlib_Sync_Pipeline_4( t_pstReg_V2an->unPHC_BUSASSTCLR.u4Data );
			break;

/*		case u1ERRH_ECC_DTP_DFPFNT_ADDR: */
			/* DFPは非使用のため何もしない */
/*			break; */

		default:
			/* 何もしない */
			break;
	}
}

/*----------------------------------------------------------------------------------------------*/
/*	ECC Fatal Error Clear Function( ROM/RAM )													*/
/*	return		: none																			*/
/*	parameters	: ModuleNumber																	*/
/*----------------------------------------------------------------------------------------------*/
static	void			ErrH_Ecc_ClearEccFatalErrRomRam( U1 t_u1ModuleNum )
{
	switch( t_u1ModuleNum )
	{
		case u1ERRH_ECC_CF:
			REG_ECC_MECCCAP_CFL.unCF_DSTCLR.u4Data = (U4)ECC_MECCCAP_CFL_CF_DSTCLR_DSTCLR00 * (U4)ECC_MECCCAP_CFL_CF_DSTCLR_CLEAR;
			REG_ECC_MECCCAP_CFL.unCF_00DESPIDCLR.u4Data = u4ERRH_ECC_ERROR_SPID_ALLCLEAR;
			Bswlib_Sync_Pipeline_4( REG_ECC_MECCCAP_CFL.unCF_00DESPIDCLR.u4Data );
			break;

/*		case u1ERRH_ECC_DF: */
			/* 機能安全のDFのECC機能は非使用のため何もしない */
/*			break; */

		case u1ERRH_ECC_LRAM_LRPE0:
			Pil_Ecc_ClearLramPe0EccFatalErrorStatus();
			REG_ECC_MECCCAP_LR_PE0CL0.unLR0_00DESPIDCLR.u4Data = u4ERRH_ECC_ERROR_SPID_ALLCLEAR;
			Bswlib_Sync_Pipeline_4( REG_ECC_MECCCAP_LR_PE0CL0.unLR0_00DESPIDCLR.u4Data );
			break;

		case u1ERRH_ECC_LRAM_LRPE1:
			Pil_Ecc_ClearLramPe1EccFatalErrorStatus();
			REG_ECC_MECCCAP_LR_PE1CL0.unLR0_00DESPIDCLR.u4Data = u4ERRH_ECC_ERROR_SPID_ALLCLEAR;
			Bswlib_Sync_Pipeline_4( REG_ECC_MECCCAP_LR_PE1CL0.unLR0_00DESPIDCLR.u4Data );
			break;

#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_TRIPLECORE ) )	/* U2B10かつ3コア構成 */
		/* U2B6、またはU2B10かつ2コア構成の場合、Init時にECMへの通知を無効に設定しているため何もしない */
		case u1ERRH_ECC_LRAM_LRPE2:
			Pil_Ecc_ClearLramPe2EccFatalErrorStatus();
			REG_ECC_MECCCAP_LR_PE2CL1.unLR0_00DESPIDCLR.u4Data = u4ERRH_ECC_ERROR_SPID_ALLCLEAR;
			Bswlib_Sync_Pipeline_4( REG_ECC_MECCCAP_LR_PE2CL1.unLR0_00DESPIDCLR.u4Data );
			break;
#endif

/*		case u1ERRH_ECC_LRAM_LRPE3: */
			/* 機能安全はCore3を使用しないため何もしない */

		case u1ERRH_ECC_LRAM_LRA:
			REG_ECC_MECCCAP_LRA.unLR1_DSTCLR.u4Data = (U4)ECC_MECCCAP_LRA_LR1_DSTCLR_DSTCLR00 * (U4)ECC_MECCCAP_LRA_LR1_DSTCLR_CLEAR;
			REG_ECC_MECCCAP_LRA.unLR1_00DESPIDCLR.u4Data = u4ERRH_ECC_ERROR_SPID_ALLCLEAR;
			Bswlib_Sync_Pipeline_4( REG_ECC_MECCCAP_LRA.unLR1_00DESPIDCLR.u4Data );
			break;

		case u1ERRH_ECC_CRAM_CRAM:
			Pil_Ecc_ClearCramEccFatalErrorStatus();
			REG_ECC_MECCCAP_CRAM.unCR_00DESPIDCLR.u4Data = u4ERRH_ECC_ERROR_SPID_ALLCLEAR;
			Bswlib_Sync_Pipeline_4( REG_ECC_MECCCAP_CRAM.unCR_00DESPIDCLR.u4Data );
			break;

		case u1ERRH_ECC_IC_ITPE0:
			REG_ECC_MECCCAP_IT_PE0CL0.unIT_DSTCLR.u4Data = (U4)ECC_MECCCAP_IT_PE0CL0_DSTCLR_DSTCLR00 * (U4)ECC_MECCCAP_IT_PE0CL0_DSTCLR_CLEAR;
			Bswlib_Sync_Pipeline_4( REG_ECC_MECCCAP_IT_PE0CL0.unIT_DSTCLR.u4Data );
			break;

		case u1ERRH_ECC_IC_ITPE1:
			REG_ECC_MECCCAP_IT_PE1CL0.unIT_DSTCLR.u4Data = (U4)ECC_MECCCAP_IT_PE1CL0_DSTCLR_DSTCLR00 * (U4)ECC_MECCCAP_IT_PE1CL0_DSTCLR_CLEAR;
			Bswlib_Sync_Pipeline_4( REG_ECC_MECCCAP_IT_PE1CL0.unIT_DSTCLR.u4Data );
			break;

#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_TRIPLECORE ) )	/* U2B10かつ3コア構成 */
		/* U2B6、またはU2B10かつ2コア構成の場合、Init時にECMへの通知を無効に設定しているため何もしない */
		case u1ERRH_ECC_IC_ITPE2:
			REG_ECC_MECCCAP_IT_PE2CL1.unIT_DSTCLR.u4Data = (U4)ECC_MECCCAP_IT_PE2CL1_DSTCLR_DSTCLR00 * (U4)ECC_MECCCAP_IT_PE2CL1_DSTCLR_CLEAR;
			Bswlib_Sync_Pipeline_4( REG_ECC_MECCCAP_IT_PE2CL1.unIT_DSTCLR.u4Data );
			break;
#endif

/*		case u1ERRH_ECC_IC_ITPE3: */
			/* 機能安全はCore3を使用しないため何もしない */

		case u1ERRH_ECC_IC_IDPE0:
			REG_ECC_MECCCAP_ID_PE0CL0.unID_DSTCLR.u4Data = (U4)ECC_MECCCAP_ID_PE0CL0_DSTCLR_DSTCLR00 * (U4)ECC_MECCCAP_ID_PE0CL0_DSTCLR_CLEAR;
			Bswlib_Sync_Pipeline_4( REG_ECC_MECCCAP_ID_PE0CL0.unID_DSTCLR.u4Data );
			break;

		case u1ERRH_ECC_IC_IDPE1:
			REG_ECC_MECCCAP_ID_PE1CL0.unID_DSTCLR.u4Data = (U4)ECC_MECCCAP_ID_PE1CL0_DSTCLR_DSTCLR00 * (U4)ECC_MECCCAP_ID_PE1CL0_DSTCLR_CLEAR;
			Bswlib_Sync_Pipeline_4( REG_ECC_MECCCAP_ID_PE1CL0.unID_DSTCLR.u4Data );
			break;

#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_TRIPLECORE ) )	/* U2B10かつ3コア構成 */
		/* U2B6、またはU2B10かつ2コア構成の場合、Init時にECMへの通知を無効に設定しているため何もしない */
		case u1ERRH_ECC_IC_IDPE2:
			REG_ECC_MECCCAP_ID_PE2CL1.unID_DSTCLR.u4Data = (U4)ECC_MECCCAP_ID_PE2CL1_DSTCLR_DSTCLR00 * (U4)ECC_MECCCAP_ID_PE2CL1_DSTCLR_CLEAR;
			Bswlib_Sync_Pipeline_4( REG_ECC_MECCCAP_ID_PE2CL1.unID_DSTCLR.u4Data );
			break;
#endif

/*		case u1ERRH_ECC_IC_IDPE3: */
			/* 機能安全はCore3を使用しないため何もしない */

		default:
			/* 何もしない */
			break;
	}
}

/*----------------------------------------------------------------------------------------------*/
/*	ECC Fatal Error Clear Function( Peripheral )												*/
/*	return		: none																			*/
/*	parameters	: ModuleNumber																	*/
/*----------------------------------------------------------------------------------------------*/
static	void			ErrH_Ecc_ClearEccFatalErrPeripheral( U1 t_u1ModuleNum )
{
	volatile Reg_Ecc_Ecc7Type*				t_pstReg_Ecc7;
	volatile Reg_Ecc_Ecc6Type*				t_pstReg_Ecc6;
	U2										t_u2RegData;

	switch( t_u1ModuleNum )
	{
		case u1ERRH_ECC_DTS:
			REG_ECC_MECCCAP_DTS.unDR_DSTCLR.u4Data = (U4)ECC_MECCCAP_DTS_DR_DSTCLR_DSTCLR00 * (U4)ECC_MECCCAP_DTS_DR_DSTCLR_CLEAR;
			Bswlib_Sync_Pipeline_4( REG_ECC_MECCCAP_DTS.unDR_DSTCLR.u4Data );
			break;

		case u1ERRH_ECC_DMDE_DMDE0:
			REG_ECC_MECCCAP_DMDE0.unDE_DSTCLR.u4Data = (U4)ECC_MECCCAP_DMDE0_DE_DSTCLR_DSTCLR00 * (U4)ECC_MECCCAP_DMDE0_DE_DSTCLR_CLEAR;
			Bswlib_Sync_Pipeline_4( REG_ECC_MECCCAP_DMDE0.unDE_DSTCLR.u4Data );
			break;

#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
		case u1ERRH_ECC_DMDE_DMDE1:
			REG_ECC_MECCCAP_DMDE1.unDE_DSTCLR.u4Data = (U4)ECC_MECCCAP_DMDE1_DE_DSTCLR_DSTCLR00 * (U4)ECC_MECCCAP_DMDE1_DE_DSTCLR_CLEAR;
			Bswlib_Sync_Pipeline_4( REG_ECC_MECCCAP_DMDE1.unDE_DSTCLR.u4Data );
			break;
#endif

		case u1ERRH_ECC_DMDA_DMDA0:
			REG_ECC_MECCCAP_DMDA0.unDA_DSTCLR.u4Data = (U4)ECC_MECCCAP_DMDA0_DA_DSTCLR_DSTCLR00 * (U4)ECC_MECCCAP_DMDA0_DA_DSTCLR_CLEAR;
			Bswlib_Sync_Pipeline_4( REG_ECC_MECCCAP_DMDA0.unDA_DSTCLR.u4Data );
			break;

#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
		case u1ERRH_ECC_DMDA_DMDA1:
			REG_ECC_MECCCAP_DMDA1.unDA_DSTCLR.u4Data = (U4)ECC_MECCCAP_DMDA1_DA_DSTCLR_DSTCLR00 * (U4)ECC_MECCCAP_DMDA1_DA_DSTCLR_CLEAR;
			Bswlib_Sync_Pipeline_4( REG_ECC_MECCCAP_DMDA1.unDA_DSTCLR.u4Data );
			break;
#endif

		case u1ERRH_ECC_PR32_E7RC01:
		case u1ERRH_ECC_PR32_E7RC02:
		case u1ERRH_ECC_PR32_E7RC03:
		case u1ERRH_ECC_PR32_E7RC04:
		case u1ERRH_ECC_PR32_E7MS00:
		case u1ERRH_ECC_PR32_E7MS01:
		case u1ERRH_ECC_PR32_E7MS02:
		case u1ERRH_ECC_PR32_E7MS03:
		case u1ERRH_ECC_PR32_E7MS04:
		case u1ERRH_ECC_PR32_E7MS05:
		case u1ERRH_ECC_PR32_E7MS06:
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
		case u1ERRH_ECC_PR32_E7MS07:
		case u1ERRH_ECC_PR32_E7MS08:
		case u1ERRH_ECC_PR32_E7MS09:
#endif
		case u1ERRH_ECC_PR32_E7DF00:
		case u1ERRH_ECC_PR32_E7DF10:
			t_pstReg_Ecc7 = (volatile Reg_Ecc_Ecc7Type*)pcstReg_Ecc7[t_u1ModuleNum - u1ERRH_ECC_PR32_OFFSET];
			t_u2RegData = t_pstReg_Ecc7->unE710CTL.u2Data & (U2)(~(U2)ECC_ECC7_E710CTL_ECER2C );
			t_pstReg_Ecc7->unE710CTL.u2Data = (U2)( ( (U2)ECC_ECC7_E710CTL_ECER2C * (U2)ECC_ECC7_E710CTL_ECER2C_WRITE )
												   + t_u2RegData );
			Bswlib_Sync_Pipeline_2( t_pstReg_Ecc7->unE710CTL.u2Data );
			break;

/*		case u1ERRH_ECC_PR32_E7FR00: */
/*		case u1ERRH_ECC_PR32_E7FR01: */
/*		case u1ERRH_ECC_PR32_E7FR02: */
			/* FlexRayは非使用のため何もしない */
/*			break; */

/*		case u1ERRH_ECC_PR32_E7GT00: */
/*		case u1ERRH_ECC_PR32_E7GT01: */
/*		case u1ERRH_ECC_PR32_E7GT10: */
/*		case u1ERRH_ECC_PR32_E7GT11: */
/*		case u1ERRH_ECC_PR32_E7GT20: */
/*		case u1ERRH_ECC_PR32_E7GT21: */
/*		case u1ERRH_ECC_PR32_E7GT30: */
/*		case u1ERRH_ECC_PR32_E7GT31: */
/*		case u1ERRH_ECC_PR32_E7GT40: */
/*		case u1ERRH_ECC_PR32_E7GT41: */
/*		case u1ERRH_ECC_PR32_E7GT50: */
/*		case u1ERRH_ECC_PR32_E7GT51: */
/*		case u1ERRH_ECC_PR32_E7GT60: */
/*		case u1ERRH_ECC_PR32_E7GT61: */
/*		case u1ERRH_ECC_PR32_E7GT100: */
/*		case u1ERRH_ECC_PR32_E7GT101: */
/*		case u1ERRH_ECC_PR32_E7GT102: */
/*		case u1ERRH_ECC_PR32_E7GT110: */
/*		case u1ERRH_ECC_PR32_E7GT111: */
/*		case u1ERRH_ECC_PR32_E7GT112: */
			/* GTMは非使用のため何もしない */
/*			break; */

/*		case u1ERRH_ECC_PR32_E7MM00: */
/*		case u1ERRH_ECC_PR32_E7MM01: */
			/* MMCAは非使用のため何もしない */
/*			break; */

/*		case u1ERRH_ECC_PR32_E7ES00: */
/*		case u1ERRH_ECC_PR32_E7ES01: */
/*		case u1ERRH_ECC_PR32_E7ES02: */
/*		case u1ERRH_ECC_PR32_E7ES03: */
/*		case u1ERRH_ECC_PR32_E7ES04: */
/*		case u1ERRH_ECC_PR32_E7ES05: */
			/* Ethernetは非使用のため何もしない */
/*			break; */

		case u1ERRH_ECC_PR16_E6DF00:
		case u1ERRH_ECC_PR16_E6DF01:
		case u1ERRH_ECC_PR16_E6DF10:
		case u1ERRH_ECC_PR16_E6DF11:
			t_pstReg_Ecc6 = (volatile Reg_Ecc_Ecc6Type*)pcstReg_Ecc6[t_u1ModuleNum - u1ERRH_ECC_PR16_OFFSET];
			t_u2RegData = t_pstReg_Ecc6->unE610CTL.u2Data & (U2)(~(U2)ECC_ECC6_E610CTL_ECER2C );
			t_pstReg_Ecc6->unE610CTL.u2Data = (U2)( ( (U2)ECC_ECC6_E610CTL_ECER2C * (U2)ECC_ECC6_E610CTL_ECER2C_WRITE )
												   + t_u2RegData );
			Bswlib_Sync_Pipeline_2( t_pstReg_Ecc6->unE610CTL.u2Data );
			break;

		default:
			/* 何もしない */
			break;
	}
}

/*----------------------------------------------------------------------------------------------*/
/*	ECC Fatal Error Clear Function( DTP Address )												*/
/*	return		: none																			*/
/*	parameters	: ModuleNumber																	*/
/*----------------------------------------------------------------------------------------------*/
static	void			ErrH_Ecc_ClearEccFatalErrDtpAddr( U1 t_u1ModuleNum )
{
	volatile Reg_Ecc_HbnEccType*			t_pstReg_HbnEcc;
	volatile Reg_Ecc_BeccCap_V2AnType*		t_pstReg_V2an;

	switch( t_u1ModuleNum )
	{
		case u1ERRH_ECC_DTP_LRAM_ADDR:
			REG_ECC_BECCCAP_LRAM.unLR_BUSADSTCLR.u4Data = (U4)( ( (U4)ECC_BECCCAP_LRAM_BUSADSTCLR_17 * (U4)ECC_BECCCAP_LRAM_BUSADSTCLR_CLEAR )
															  + ( (U4)ECC_BECCCAP_LRAM_BUSADSTCLR_16 * (U4)ECC_BECCCAP_LRAM_BUSADSTCLR_CLEAR )
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
															  + ( (U4)ECC_BECCCAP_LRAM_BUSADSTCLR_03 * (U4)ECC_BECCCAP_LRAM_BUSADSTCLR_CLEAR )
#endif
															  + ( (U4)ECC_BECCCAP_LRAM_BUSADSTCLR_02 * (U4)ECC_BECCCAP_LRAM_BUSADSTCLR_CLEAR )
															  + ( (U4)ECC_BECCCAP_LRAM_BUSADSTCLR_01 * (U4)ECC_BECCCAP_LRAM_BUSADSTCLR_CLEAR )
															  + ( (U4)ECC_BECCCAP_LRAM_BUSADSTCLR_00 * (U4)ECC_BECCCAP_LRAM_BUSADSTCLR_CLEAR ) );

			Bswlib_Sync_Pipeline_4( REG_ECC_BECCCAP_LRAM.unLR_BUSADSTCLR.u4Data );
			break;

		case u1ERRH_ECC_DTP_CRAM_ADDR:
#if ( MCU_TYPE_SERIES == MCU_RH850U2B6 )
			REG_ECC_BECCCAP_CRAM.unCR_BUSADSTCLR.u4Data = (U4)( ( (U4)ECC_BECCCAP_CRAM_BUSADSTCLR_24 * (U4)ECC_BECCCAP_CRAM_BUSADSTCLR_CLEAR )
#elif ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
			REG_ECC_BECCCAP_CRAM.unCR_BUSADSTCLR.u4Data = (U4)( ( (U4)ECC_BECCCAP_CRAM_BUSADSTCLR_25 * (U4)ECC_BECCCAP_CRAM_BUSADSTCLR_CLEAR )
															  + ( (U4)ECC_BECCCAP_CRAM_BUSADSTCLR_24 * (U4)ECC_BECCCAP_CRAM_BUSADSTCLR_CLEAR )
															  + ( (U4)ECC_BECCCAP_CRAM_BUSADSTCLR_06 * (U4)ECC_BECCCAP_CRAM_BUSADSTCLR_CLEAR )
															  + ( (U4)ECC_BECCCAP_CRAM_BUSADSTCLR_05 * (U4)ECC_BECCCAP_CRAM_BUSADSTCLR_CLEAR )
															  + ( (U4)ECC_BECCCAP_CRAM_BUSADSTCLR_04 * (U4)ECC_BECCCAP_CRAM_BUSADSTCLR_CLEAR )
#else
	#error "MCU_TYPE_SERIES is not supported"
#endif
															  + ( (U4)ECC_BECCCAP_CRAM_BUSADSTCLR_02 * (U4)ECC_BECCCAP_CRAM_BUSADSTCLR_CLEAR )
															  + ( (U4)ECC_BECCCAP_CRAM_BUSADSTCLR_01 * (U4)ECC_BECCCAP_CRAM_BUSADSTCLR_CLEAR )
															  + ( (U4)ECC_BECCCAP_CRAM_BUSADSTCLR_00 * (U4)ECC_BECCCAP_CRAM_BUSADSTCLR_CLEAR ) );

			Bswlib_Sync_Pipeline_4( REG_ECC_BECCCAP_CRAM.unCR_BUSADSTCLR.u4Data );
			break;

		case u1ERRH_ECC_DTP_CFL_ADDR:
#if ( MCU_TYPE_SERIES == MCU_RH850U2B6 )
			REG_ECC_BECCCAP_CFL.unCF_BUSADSTCLR.u4Data = (U4)( ( (U4)ECC_BECCCAP_CFL_BUSADSTCLR_24 * (U4)ECC_BECCCAP_CFL_BUSADSTCLR_CLEAR )

#elif ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
			REG_ECC_BECCCAP_CFL.unCF_BUSADSTCLR.u4Data = (U4)( ( (U4)ECC_BECCCAP_CFL_BUSADSTCLR_25 * (U4)ECC_BECCCAP_CFL_BUSADSTCLR_CLEAR )
															 + ( (U4)ECC_BECCCAP_CFL_BUSADSTCLR_24 * (U4)ECC_BECCCAP_CFL_BUSADSTCLR_CLEAR )
															 + ( (U4)ECC_BECCCAP_CFL_BUSADSTCLR_05 * (U4)ECC_BECCCAP_CFL_BUSADSTCLR_CLEAR )
															 + ( (U4)ECC_BECCCAP_CFL_BUSADSTCLR_04 * (U4)ECC_BECCCAP_CFL_BUSADSTCLR_CLEAR )
#else
	#error "MCU_TYPE_SERIES is not supported"
#endif
															 + ( (U4)ECC_BECCCAP_CFL_BUSADSTCLR_01 * (U4)ECC_BECCCAP_CFL_BUSADSTCLR_CLEAR )
															 + ( (U4)ECC_BECCCAP_CFL_BUSADSTCLR_00 * (U4)ECC_BECCCAP_CFL_BUSADSTCLR_CLEAR ) );

			Bswlib_Sync_Pipeline_4( REG_ECC_BECCCAP_CFL.unCF_BUSADSTCLR.u4Data );
			break;

		case u1ERRH_ECC_DTP_PERI_ADDR:
			REG_ECC_BECCCAP_PERI.unPH_BUSADSTCLR.u4Data = (U4)( ( (U4)ECC_BECCCAP_PERI_BUSADSTCLR_25 * (U4)ECC_BECCCAP_PERI_BUSADSTCLR_CLEAR )
															  + ( (U4)ECC_BECCCAP_PERI_BUSADSTCLR_20 * (U4)ECC_BECCCAP_PERI_BUSADSTCLR_CLEAR )

															  + ( (U4)ECC_BECCCAP_PERI_BUSADSTCLR_18 * (U4)ECC_BECCCAP_PERI_BUSADSTCLR_CLEAR )
															  + ( (U4)ECC_BECCCAP_PERI_BUSADSTCLR_17 * (U4)ECC_BECCCAP_PERI_BUSADSTCLR_CLEAR )
															  + ( (U4)ECC_BECCCAP_PERI_BUSADSTCLR_16 * (U4)ECC_BECCCAP_PERI_BUSADSTCLR_CLEAR ) );
			Bswlib_Sync_Pipeline_4( REG_ECC_BECCCAP_PERI.unPH_BUSADSTCLR.u4Data );
			break;

		case u1ERRH_ECC_DTP_EMU_ADDR:
#if ( MCU_TYPE_SERIES == MCU_RH850U2B6 )
			REG_ECC_BECCCAP_EMU.unEM_BUSADSTCLR.u4Data = (U4)( ( (U4)ECC_BECCCAP_EMU_BUSADSTCLR_17 * (U4)ECC_BECCCAP_EMU_BUSADSTCLR_CLEAR )
#elif ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
			REG_ECC_BECCCAP_EMU.unEM_BUSADSTCLR.u4Data = (U4)( ( (U4)ECC_BECCCAP_EMU_BUSADSTCLR_18 * (U4)ECC_BECCCAP_EMU_BUSADSTCLR_CLEAR )
															 + ( (U4)ECC_BECCCAP_EMU_BUSADSTCLR_17 * (U4)ECC_BECCCAP_EMU_BUSADSTCLR_CLEAR )
#else
	#error "MCU_TYPE_SERIES is not supported"
#endif
															 + ( (U4)ECC_BECCCAP_EMU_BUSADSTCLR_16 * (U4)ECC_BECCCAP_EMU_BUSADSTCLR_CLEAR )
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
															 + ( (U4)ECC_BECCCAP_EMU_BUSADSTCLR_06 * (U4)ECC_BECCCAP_EMU_BUSADSTCLR_CLEAR )
#endif
															 + ( (U4)ECC_BECCCAP_EMU_BUSADSTCLR_04 * (U4)ECC_BECCCAP_EMU_BUSADSTCLR_CLEAR )
															 + ( (U4)ECC_BECCCAP_EMU_BUSADSTCLR_02 * (U4)ECC_BECCCAP_EMU_BUSADSTCLR_CLEAR )
															 + ( (U4)ECC_BECCCAP_EMU_BUSADSTCLR_00 * (U4)ECC_BECCCAP_EMU_BUSADSTCLR_CLEAR ) );

			Bswlib_Sync_Pipeline_4( REG_ECC_BECCCAP_EMU.unEM_BUSADSTCLR.u4Data );
			break;

		/* HBnECCはデータ、アドレスのECC 2bit、1bitエラーをすべてクリアする(ハード仕様) */
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
		case u1ERRH_ECC_DTP_HB90MECC_ADDR:
		case u1ERRH_ECC_DTP_HB90SECC_ADDR:
#endif
		case u1ERRH_ECC_DTP_HB92MECC_ADDR:
		case u1ERRH_ECC_DTP_HB92SECC_ADDR:
		case u1ERRH_ECC_DTP_HB94SECC_ADDR:
		case u1ERRH_ECC_DTP_HB97MECC_ADDR:
		case u1ERRH_ECC_DTP_HB98MECC_ADDR:
#if ( MCU_TYPE_SERIES == MCU_RH850U2B6)
		case u1ERRH_ECC_DTP_HB911MECC_ADDR:
		case u1ERRH_ECC_DTP_HB912MECC_ADDR:
#endif
			t_pstReg_HbnEcc = (volatile Reg_Ecc_HbnEccType*)pcstReg_HbnEcc[t_u1ModuleNum - u1ERRH_ECC_HBNECC_ADDR_OFFSET];
			t_pstReg_HbnEcc->unHBECSTCLR.u4Data = (U4)ECC_HBNECC_HBECSTCLR_STCLR0 * (U4)ECC_HBNECC_HBECSTCLR_CLEAR;
			Bswlib_Sync_Pipeline_4( t_pstReg_HbnEcc->unHBECSTCLR.u4Data );
			break;

		case u1ERRH_ECC_DTP_V2A1_ADDR:
		case u1ERRH_ECC_DTP_V2A2_ADDR:
		case u1ERRH_ECC_DTP_V2A3_ADDR:
		case u1ERRH_ECC_DTP_V2A4_ADDR:
		case u1ERRH_ECC_DTP_V2A5_ADDR:
		case u1ERRH_ECC_DTP_V2A6_ADDR:
		case u1ERRH_ECC_DTP_V2A7_ADDR:
		case u1ERRH_ECC_DTP_V2A8_ADDR:
		case u1ERRH_ECC_DTP_V2A9_ADDR:
		case u1ERRH_ECC_DTP_V2A10_ADDR:
		case u1ERRH_ECC_DTP_V2A11_ADDR:
			t_pstReg_V2an = (volatile Reg_Ecc_BeccCap_V2AnType*)pcstReg_V2an[t_u1ModuleNum - u1ERRH_ECC_V2AN_ADDR_OFFSET];
			t_pstReg_V2an->unPHC_BUSADSTCLR.u4Data = (U4)ECC_BECCCAP_V2AN_BUSADSTCLR_ADSTCLR00 * (U4)ECC_BECCCAP_V2AN_BUSADSTCLR_CLEAR;
			Bswlib_Sync_Pipeline_4( t_pstReg_V2an->unPHC_BUSADSTCLR.u4Data );
			break;

/*		case u1ERRH_ECC_DTP_DFPFNT_ADDR: */
			/* DFPは非使用のため何もしない */
/*			break; */

		default:
			/* 何もしない */
			break;
	}
}

/*----------------------------------------------------------------------------------------------*/
/*	ECC Fatal Error Clear Function( DTP Data )													*/
/*	return		: none																			*/
/*	parameters	: ModuleNumber																	*/
/*----------------------------------------------------------------------------------------------*/
static	void			ErrH_Ecc_ClearEccFatalErrDtpData( U1 t_u1ModuleNum )
{
	volatile Reg_Ecc_HbnEccType*			t_pstReg_HbnEcc;
	volatile Reg_Ecc_BeccCap_V2AnType*		t_pstReg_V2an;

	switch( t_u1ModuleNum )
	{
		case u1ERRH_ECC_DTP_LRAM_DATA:
#if ( MCU_TYPE_SERIES == MCU_RH850U2B6 )
			REG_ECC_BECCCAP_LRAM.unLR_BUSDDSTCLR.u4Data = (U4)( ( (U4)ECC_BECCCAP_LRAM_BUSDDSTCLR_02 * (U4)ECC_BECCCAP_LRAM_BUSDDSTCLR_CLEAR )
#elif ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
			REG_ECC_BECCCAP_LRAM.unLR_BUSDDSTCLR.u4Data = (U4)( ( (U4)ECC_BECCCAP_LRAM_BUSDDSTCLR_03 * (U4)ECC_BECCCAP_LRAM_BUSDDSTCLR_CLEAR )
															  + ( (U4)ECC_BECCCAP_LRAM_BUSDDSTCLR_02 * (U4)ECC_BECCCAP_LRAM_BUSDDSTCLR_CLEAR )
#else
	#error "MCU_TYPE_SERIES is not supported"
#endif
															  + ( (U4)ECC_BECCCAP_LRAM_BUSDDSTCLR_01 * (U4)ECC_BECCCAP_LRAM_BUSDDSTCLR_CLEAR )
															  + ( (U4)ECC_BECCCAP_LRAM_BUSDDSTCLR_00 * (U4)ECC_BECCCAP_LRAM_BUSDDSTCLR_CLEAR ) );

			Bswlib_Sync_Pipeline_4( REG_ECC_BECCCAP_LRAM.unLR_BUSDDSTCLR.u4Data );
			break;

		case u1ERRH_ECC_DTP_CRAM_DATA:
#if ( MCU_TYPE_SERIES == MCU_RH850U2B6 )
			REG_ECC_BECCCAP_CRAM.unCR_BUSDDSTCLR.u4Data = (U4)( ( (U4)ECC_BECCCAP_CRAM_BUSDDSTCLR_02 * (U4)ECC_BECCCAP_CRAM_BUSDDSTCLR_CLEAR )
#elif ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
			REG_ECC_BECCCAP_CRAM.unCR_BUSDDSTCLR.u4Data = (U4)( ( (U4)ECC_BECCCAP_CRAM_BUSDDSTCLR_06 * (U4)ECC_BECCCAP_CRAM_BUSDDSTCLR_CLEAR )
															  + ( (U4)ECC_BECCCAP_CRAM_BUSDDSTCLR_05 * (U4)ECC_BECCCAP_CRAM_BUSDDSTCLR_CLEAR )
															  + ( (U4)ECC_BECCCAP_CRAM_BUSDDSTCLR_04 * (U4)ECC_BECCCAP_CRAM_BUSDDSTCLR_CLEAR )
															  + ( (U4)ECC_BECCCAP_CRAM_BUSDDSTCLR_02 * (U4)ECC_BECCCAP_CRAM_BUSDDSTCLR_CLEAR )
#else
	#error "MCU_TYPE_SERIES is not supported"
#endif
															  + ( (U4)ECC_BECCCAP_CRAM_BUSDDSTCLR_01 * (U4)ECC_BECCCAP_CRAM_BUSDDSTCLR_CLEAR )
															  + ( (U4)ECC_BECCCAP_CRAM_BUSDDSTCLR_00 * (U4)ECC_BECCCAP_CRAM_BUSDDSTCLR_CLEAR ) );

			Bswlib_Sync_Pipeline_4( REG_ECC_BECCCAP_CRAM.unCR_BUSDDSTCLR.u4Data );
			break;

		case u1ERRH_ECC_DTP_PERI_DATA:
			REG_ECC_BECCCAP_PERI.unPH_BUSDDSTCLR.u4Data = (U4)( ( (U4)ECC_BECCCAP_PERI_BUSDDSTCLR_25 * (U4)ECC_BECCCAP_PERI_BUSDDSTCLR_CLEAR )
															  + ( (U4)ECC_BECCCAP_PERI_BUSDDSTCLR_18 * (U4)ECC_BECCCAP_PERI_BUSDDSTCLR_CLEAR )
															  + ( (U4)ECC_BECCCAP_PERI_BUSDDSTCLR_17 * (U4)ECC_BECCCAP_PERI_BUSDDSTCLR_CLEAR )
															  + ( (U4)ECC_BECCCAP_PERI_BUSDDSTCLR_16 * (U4)ECC_BECCCAP_PERI_BUSDDSTCLR_CLEAR )
															  + ( (U4)ECC_BECCCAP_PERI_BUSDDSTCLR_11 * (U4)ECC_BECCCAP_PERI_BUSDDSTCLR_CLEAR )
															  + ( (U4)ECC_BECCCAP_PERI_BUSDDSTCLR_10 * (U4)ECC_BECCCAP_PERI_BUSDDSTCLR_CLEAR )
															  + ( (U4)ECC_BECCCAP_PERI_BUSDDSTCLR_09 * (U4)ECC_BECCCAP_PERI_BUSDDSTCLR_CLEAR )
															  + ( (U4)ECC_BECCCAP_PERI_BUSDDSTCLR_08 * (U4)ECC_BECCCAP_PERI_BUSDDSTCLR_CLEAR )
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
															  + ( (U4)ECC_BECCCAP_PERI_BUSDDSTCLR_03 * (U4)ECC_BECCCAP_PERI_BUSDDSTCLR_CLEAR )
#endif
															  + ( (U4)ECC_BECCCAP_PERI_BUSDDSTCLR_02 * (U4)ECC_BECCCAP_PERI_BUSDDSTCLR_CLEAR )
															  + ( (U4)ECC_BECCCAP_PERI_BUSDDSTCLR_01 * (U4)ECC_BECCCAP_PERI_BUSDDSTCLR_CLEAR )
															  + ( (U4)ECC_BECCCAP_PERI_BUSDDSTCLR_00 * (U4)ECC_BECCCAP_PERI_BUSDDSTCLR_CLEAR ) );

			Bswlib_Sync_Pipeline_4( REG_ECC_BECCCAP_PERI.unPH_BUSDDSTCLR.u4Data );
			break;

		case u1ERRH_ECC_DTP_DMDT_DATA:
			REG_ECC_BECCCAP_DMDT.unDM_BUSDDSTCLR.u4Data = (U4)( ( (U4)ECC_BECCCAP_DMDT_BUSDDSTCLR_08 * (U4)ECC_BECCCAP_DMDT_BUSDDSTCLR_CLEAR )
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
															  + ( (U4)ECC_BECCCAP_DMDT_BUSDDSTCLR_07 * (U4)ECC_BECCCAP_DMDT_BUSDDSTCLR_CLEAR )
															  + ( (U4)ECC_BECCCAP_DMDT_BUSDDSTCLR_06 * (U4)ECC_BECCCAP_DMDT_BUSDDSTCLR_CLEAR )
#endif
															  + ( (U4)ECC_BECCCAP_DMDT_BUSDDSTCLR_05 * (U4)ECC_BECCCAP_DMDT_BUSDDSTCLR_CLEAR )
															  + ( (U4)ECC_BECCCAP_DMDT_BUSDDSTCLR_04 * (U4)ECC_BECCCAP_DMDT_BUSDDSTCLR_CLEAR )
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
															  + ( (U4)ECC_BECCCAP_DMDT_BUSDDSTCLR_03 * (U4)ECC_BECCCAP_DMDT_BUSDDSTCLR_CLEAR )
															  + ( (U4)ECC_BECCCAP_DMDT_BUSDDSTCLR_02 * (U4)ECC_BECCCAP_DMDT_BUSDDSTCLR_CLEAR )
#endif
															  + ( (U4)ECC_BECCCAP_DMDT_BUSDDSTCLR_01 * (U4)ECC_BECCCAP_DMDT_BUSDDSTCLR_CLEAR )
															  + ( (U4)ECC_BECCCAP_DMDT_BUSDDSTCLR_00 * (U4)ECC_BECCCAP_DMDT_BUSDDSTCLR_CLEAR ) );

			Bswlib_Sync_Pipeline_4( REG_ECC_BECCCAP_DMDT.unDM_BUSDDSTCLR.u4Data );
			break;

		case u1ERRH_ECC_DTP_EMU_DATA:
			REG_ECC_BECCCAP_EMU.unEM_BUSDDSTCLR.u4Data = (U4)ECC_BECCCAP_EMU_BUSDDSTCLR_DDSTCLR17 * (U4)ECC_BECCCAP_EMU_BUSDDSTCLR_CLEAR;
			Bswlib_Sync_Pipeline_4( REG_ECC_BECCCAP_EMU.unEM_BUSDDSTCLR.u4Data );
			break;

		/* HBnECCはデータ、アドレスのECC 2bit、1bitエラーをすべてクリアする(ハード仕様) */
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
		case u1ERRH_ECC_DTP_HB90MECC_DATA:
		case u1ERRH_ECC_DTP_HB90SECC_DATA:
#endif
		case u1ERRH_ECC_DTP_HB92MECC_DATA:
		case u1ERRH_ECC_DTP_HB92SECC_DATA:
		case u1ERRH_ECC_DTP_HB94SECC_DATA:
		case u1ERRH_ECC_DTP_HB97MECC_DATA:
		case u1ERRH_ECC_DTP_HB98MECC_DATA:
#if ( MCU_TYPE_SERIES == MCU_RH850U2B6)
		case u1ERRH_ECC_DTP_HB911MECC_DATA:
		case u1ERRH_ECC_DTP_HB912MECC_DATA:
#endif
			t_pstReg_HbnEcc = (volatile Reg_Ecc_HbnEccType*)pcstReg_HbnEcc[t_u1ModuleNum - u1ERRH_ECC_HBNECC_DATA_OFFSET];
			t_pstReg_HbnEcc->unHBECSTCLR.u4Data = (U4)ECC_HBNECC_HBECSTCLR_STCLR0 * (U4)ECC_HBNECC_HBECSTCLR_CLEAR;
			Bswlib_Sync_Pipeline_4( t_pstReg_HbnEcc->unHBECSTCLR.u4Data );
			break;

		case u1ERRH_ECC_DTP_V2A1_DATA:
		case u1ERRH_ECC_DTP_V2A2_DATA:
		case u1ERRH_ECC_DTP_V2A3_DATA:
		case u1ERRH_ECC_DTP_V2A4_DATA:
		case u1ERRH_ECC_DTP_V2A5_DATA:
		case u1ERRH_ECC_DTP_V2A6_DATA:
		case u1ERRH_ECC_DTP_V2A7_DATA:
		case u1ERRH_ECC_DTP_V2A8_DATA:
		case u1ERRH_ECC_DTP_V2A9_DATA:
		case u1ERRH_ECC_DTP_V2A10_DATA:
		case u1ERRH_ECC_DTP_V2A11_DATA:
			t_pstReg_V2an = (volatile Reg_Ecc_BeccCap_V2AnType*)pcstReg_V2an[t_u1ModuleNum - u1ERRH_ECC_V2AN_DATA_OFFSET];
			t_pstReg_V2an->unPHC_BUSDDSTCLR.u4Data = (U4)ECC_BECCCAP_V2AN_BUSDDSTCLR_DDSTCLR00 * (U4)ECC_BECCCAP_V2AN_BUSDDSTCLR_CLEAR;

			Bswlib_Sync_Pipeline_4( t_pstReg_V2an->unPHC_BUSDDSTCLR.u4Data );
			break;

/*		case u1ERRH_ECC_DTP_DFPROM_DATA: */
/*		case u1ERRH_ECC_DTP_DFPSYS_DATA: */
/*		case u1ERRH_ECC_DTP_DFPFNT_DATA: */
			/* DFPは非使用のため何もしない */

		default:
			/* 何もしない */
			break;
	}
}

/*----------------------------------------------------------------------------------------------*/
/*	ECC Fatal Error Status Get Function( RAM/ROM )												*/
/*	return		: ErrorStatus																	*/
/*	parameters	: ModuleNumber																	*/
/*----------------------------------------------------------------------------------------------*/
static	U1			ErrH_Ecc_GetEccFatalErrStsRomRam( U1 t_u1ModuleNum )
{
	U1										t_u1ErrorStatus;

	t_u1ErrorStatus = u1ERRH_ECC_ERR_NOTDETECT;

	switch( t_u1ModuleNum )
	{
		case u1ERRH_ECC_CF:
			t_u1ErrorStatus = (U1)( REG_ECC_MECCCAP_CFL.unCF_DERSTR.u4Data
								  & ( (U4)ECC_MECCCAP_CFL_CF_DERSTR_APEF00 + (U4)ECC_MECCCAP_CFL_CF_DERSTR_DEDF00 ) );
			break;

/*		case u1ERRH_ECC_DF: */
			/* 機能安全のDFのECC機能は非使用のため何もしない */
/*			break; */

		case u1ERRH_ECC_LRAM_LRPE0:
			t_u1ErrorStatus = (U1)( REG_ECC_MECCCAP_LR_PE0CL0.unLR0_DERSTR.u4Data 
								  & ( (U4)ECC_MECCCAP_LR_PE0CL0_DERSTR_AFEF00 + (U4)ECC_MECCCAP_LR_PE0CL0_DERSTR_DEDF00 ) );
			break;

		case u1ERRH_ECC_LRAM_LRPE1:
			t_u1ErrorStatus = (U1)( REG_ECC_MECCCAP_LR_PE1CL0.unLR0_DERSTR.u4Data
								  & ( (U4)ECC_MECCCAP_LR_PE1CL0_DERSTR_AFEF00 + (U4)ECC_MECCCAP_LR_PE1CL0_DERSTR_DEDF00 ) );
			break;

#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_TRIPLECORE ) )	/* U2B10かつ3コア構成 */
		/* U2B6、またはU2B10かつ2コア構成の場合、Init時にECMへの通知を無効に設定しているため何もしない */
		case u1ERRH_ECC_LRAM_LRPE2:
			t_u1ErrorStatus = (U1)( REG_ECC_MECCCAP_LR_PE2CL1.unLR0_DERSTR.u4Data
								  & ( (U4)ECC_MECCCAP_LR_PE2CL1_DERSTR_AFEF00 + (U4)ECC_MECCCAP_LR_PE2CL1_DERSTR_DEDF00 ) );
			break;
#endif

/*		case u1ERRH_ECC_LRAM_LRPE3: */
			/* 機能安全はCore3を使用しないため何もしない */

		case u1ERRH_ECC_LRAM_LRA:
			t_u1ErrorStatus = (U1)( REG_ECC_MECCCAP_LRA.unLR1_DERSTR.u4Data & (U4)ECC_MECCCAP_LRA_LR1_DERSTR_DEDF00 );
			break;

		case u1ERRH_ECC_CRAM_CRAM:
			t_u1ErrorStatus = (U1)Pil_Ecc_GetCramEccFatalErrorStatus();
			break;

		case u1ERRH_ECC_IC_ITPE0:
			t_u1ErrorStatus = (U1)( REG_ECC_MECCCAP_IT_PE0CL0.unIT_DERSTR.u4Data
								  & ( (U4)ECC_MECCCAP_IT_PE0CL0_DERSTR_AFEF00 + (U4)ECC_MECCCAP_IT_PE0CL0_DERSTR_DEDF00 ) );
			break;

		case u1ERRH_ECC_IC_ITPE1:
			t_u1ErrorStatus = (U1)( REG_ECC_MECCCAP_IT_PE1CL0.unIT_DERSTR.u4Data
								  & ( (U4)ECC_MECCCAP_IT_PE1CL0_DERSTR_AFEF00 + (U4)ECC_MECCCAP_IT_PE1CL0_DERSTR_DEDF00 ) );
			break;

#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_TRIPLECORE ) )	/* U2B10かつ3コア構成 */
		/* U2B6、またはU2B10かつ2コア構成の場合、Init時にECMへの通知を無効に設定しているため何もしない */
		case u1ERRH_ECC_IC_ITPE2:
			t_u1ErrorStatus = (U1)( REG_ECC_MECCCAP_IT_PE2CL1.unIT_DERSTR.u4Data
								  & ( (U4)ECC_MECCCAP_IT_PE2CL1_DERSTR_AFEF00 + (U4)ECC_MECCCAP_IT_PE2CL1_DERSTR_DEDF00 ) );
			break;
#endif

/*		case u1ERRH_ECC_IC_ITPE3: */
			/* 機能安全はCore3を使用しないため何もしない */

		case u1ERRH_ECC_IC_IDPE0:
			t_u1ErrorStatus = (U1)( REG_ECC_MECCCAP_ID_PE0CL0.unID_DERSTR.u4Data
								  & ( (U4)ECC_MECCCAP_ID_PE0CL0_DERSTR_AFEF00 + (U4)ECC_MECCCAP_ID_PE0CL0_DERSTR_DEDF00 ) );
			break;

		case u1ERRH_ECC_IC_IDPE1:
			t_u1ErrorStatus = (U1)( REG_ECC_MECCCAP_ID_PE1CL0.unID_DERSTR.u4Data
								  & ( (U4)ECC_MECCCAP_ID_PE1CL0_DERSTR_AFEF00 + (U4)ECC_MECCCAP_ID_PE1CL0_DERSTR_DEDF00 ) );
			break;

#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM == MCU_TRIPLECORE ) )	/* U2B10かつ3コア構成 */
		/* U2B6、またはU2B10かつ2コア構成の場合、Init時にECMへの通知を無効に設定しているため何もしない */
		case u1ERRH_ECC_IC_IDPE2:
			t_u1ErrorStatus = (U1)( REG_ECC_MECCCAP_ID_PE2CL1.unID_DERSTR.u4Data
								  & ( (U4)ECC_MECCCAP_ID_PE2CL1_DERSTR_AFEF00 + (U4)ECC_MECCCAP_ID_PE2CL1_DERSTR_DEDF00 ) );
			break;
#endif

/*		case u1ERRH_ECC_IC_IDPE3: */
			/* 機能安全はCore3を使用しないため何もしない */

		default:
			/* 何もしない */
			break;
	}

	return( t_u1ErrorStatus );
}

/*----------------------------------------------------------------------------------------------*/
/*	ECC Fatal Error Status Get Function( Peripheral )											*/
/*	return		: ErrorStatus																	*/
/*	parameters	: ModuleNumber																	*/
/*----------------------------------------------------------------------------------------------*/
static	U1			ErrH_Ecc_GetEccFatalErrStsPeripheral( U1 t_u1ModuleNum )
{
	volatile Reg_Ecc_Ecc7Type*				t_pstReg_Ecc7;
	volatile Reg_Ecc_Ecc6Type*				t_pstReg_Ecc6;
	U1										t_u1ErrorStatus;

	t_u1ErrorStatus = u1ERRH_ECC_ERR_NOTDETECT;

	switch( t_u1ModuleNum )
	{
		case u1ERRH_ECC_DTS:
			t_u1ErrorStatus = (U1)( REG_ECC_MECCCAP_DTS.unDR_DERSTR.u4Data
								  & ( (U4)ECC_MECCCAP_DTS_DR_DERSTR_AFEF00 + (U4)ECC_MECCCAP_DTS_DR_DERSTR_DEDF00 ) );
			break;

		case u1ERRH_ECC_DMDE_DMDE0:
			t_u1ErrorStatus = (U1)( REG_ECC_MECCCAP_DMDE0.unDE_DERSTR.u4Data
								  & ( (U4)ECC_MECCCAP_DMDE0_DE_DERSTR_AFEF00 + (U4)ECC_MECCCAP_DMDE0_DE_DERSTR_DEDF00 ) );
			break;

#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
		case u1ERRH_ECC_DMDE_DMDE1:
			t_u1ErrorStatus = (U1)( REG_ECC_MECCCAP_DMDE1.unDE_DERSTR.u4Data
								  & ( (U4)ECC_MECCCAP_DMDE1_DE_DERSTR_AFEF00 + (U4)ECC_MECCCAP_DMDE1_DE_DERSTR_DEDF00 ) );
			break;
#endif

		case u1ERRH_ECC_DMDA_DMDA0:
			t_u1ErrorStatus = (U1)( REG_ECC_MECCCAP_DMDA0.unDA_DERSTR.u4Data & (U4)ECC_MECCCAP_DMDA0_DA_DERSTR_DEDF00 );
			break;

#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
		case u1ERRH_ECC_DMDA_DMDA1:
			t_u1ErrorStatus = (U1)( REG_ECC_MECCCAP_DMDA1.unDA_DERSTR.u4Data & (U4)ECC_MECCCAP_DMDA1_DA_DERSTR_DEDF00 );
			break;
#endif

		case u1ERRH_ECC_PR32_E7RC01:
		case u1ERRH_ECC_PR32_E7RC02:
		case u1ERRH_ECC_PR32_E7RC03:
		case u1ERRH_ECC_PR32_E7RC04:
		case u1ERRH_ECC_PR32_E7MS00:
		case u1ERRH_ECC_PR32_E7MS01:
		case u1ERRH_ECC_PR32_E7MS02:
		case u1ERRH_ECC_PR32_E7MS03:
		case u1ERRH_ECC_PR32_E7MS04:
		case u1ERRH_ECC_PR32_E7MS05:
		case u1ERRH_ECC_PR32_E7MS06:
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
		case u1ERRH_ECC_PR32_E7MS07:
		case u1ERRH_ECC_PR32_E7MS08:
		case u1ERRH_ECC_PR32_E7MS09:
#endif
		case u1ERRH_ECC_PR32_E7DF00:
		case u1ERRH_ECC_PR32_E7DF10:
			t_pstReg_Ecc7 = (volatile Reg_Ecc_Ecc7Type*)pcstReg_Ecc7[t_u1ModuleNum - u1ERRH_ECC_PR32_OFFSET];
			if( ( t_pstReg_Ecc7->unE710CTL.u2Data & (U2)ECC_ECC7_E710CTL_ECER2F ) != (U2)0U )
			{
				t_u1ErrorStatus = u1ERRH_ECC_ERR_2BITDETECT;
			}
			break;

/*		case u1ERRH_ECC_PR32_E7FR00: */
/*		case u1ERRH_ECC_PR32_E7FR01: */
/*		case u1ERRH_ECC_PR32_E7FR02: */
			/* FlexRayは非使用のため何もしない */
/*			break; */

/*		case u1ERRH_ECC_PR32_E7GT00: */
/*		case u1ERRH_ECC_PR32_E7GT01: */
/*		case u1ERRH_ECC_PR32_E7GT10: */
/*		case u1ERRH_ECC_PR32_E7GT11: */
/*		case u1ERRH_ECC_PR32_E7GT20: */
/*		case u1ERRH_ECC_PR32_E7GT21: */
/*		case u1ERRH_ECC_PR32_E7GT30: */
/*		case u1ERRH_ECC_PR32_E7GT31: */
/*		case u1ERRH_ECC_PR32_E7GT40: */
/*		case u1ERRH_ECC_PR32_E7GT41: */
/*		case u1ERRH_ECC_PR32_E7GT50: */
/*		case u1ERRH_ECC_PR32_E7GT51: */
/*		case u1ERRH_ECC_PR32_E7GT60: */
/*		case u1ERRH_ECC_PR32_E7GT61: */
/*		case u1ERRH_ECC_PR32_E7GT100: */
/*		case u1ERRH_ECC_PR32_E7GT101: */
/*		case u1ERRH_ECC_PR32_E7GT102: */
/*		case u1ERRH_ECC_PR32_E7GT110: */
/*		case u1ERRH_ECC_PR32_E7GT111: */
/*		case u1ERRH_ECC_PR32_E7GT112: */
			/* GTMは非使用のため何もしない */
/*			break; */

/*		case u1ERRH_ECC_PR32_E7MM00: */
/*		case u1ERRH_ECC_PR32_E7MM01: */
			/* MMCAは非使用のため何もしない */
/*			break; */

/*		case u1ERRH_ECC_PR32_E7ES00: */
/*		case u1ERRH_ECC_PR32_E7ES01: */
/*		case u1ERRH_ECC_PR32_E7ES02: */
/*		case u1ERRH_ECC_PR32_E7ES03: */
/*		case u1ERRH_ECC_PR32_E7ES04: */
/*		case u1ERRH_ECC_PR32_E7ES05: */
			/* Ethernetは非使用のため何もしない */
/*			break; */

		case u1ERRH_ECC_PR16_E6DF00:
		case u1ERRH_ECC_PR16_E6DF01:
		case u1ERRH_ECC_PR16_E6DF10:
		case u1ERRH_ECC_PR16_E6DF11:
			t_pstReg_Ecc6 = (volatile Reg_Ecc_Ecc6Type*)pcstReg_Ecc6[t_u1ModuleNum - u1ERRH_ECC_PR16_OFFSET];
			if( ( t_pstReg_Ecc6->unE610CTL.u2Data & (U2)ECC_ECC6_E610CTL_ECER2F ) != (U2)0U )
			{
				t_u1ErrorStatus = u1ERRH_ECC_ERR_2BITDETECT;
			}
			break;

		default:
			/* 何もしない */
			break;
	}

	return( t_u1ErrorStatus );
}

/*----------------------------------------------------------------------------------------------*/
/*	ECC Fatal Error Status Get Function( DTP Addrerss )											*/
/*	return		: ErrorStatus																	*/
/*	parameters	: ModuleNumber																	*/
/*----------------------------------------------------------------------------------------------*/
static	U1			ErrH_Ecc_GetEccFatalErrStsDtpAddr( U1 t_u1ModuleNum )
{
	volatile Reg_Ecc_HbnEccType*			t_pstReg_HbnEcc;
	volatile Reg_Ecc_BeccCap_V2AnType*		t_pstReg_V2an;
	U1										t_u1ErrorStatus;

	t_u1ErrorStatus = u1ERRH_ECC_ERR_NOTDETECT;

	switch( t_u1ModuleNum )
	{
		case u1ERRH_ECC_DTP_LRAM_ADDR:
			if( ( REG_ECC_BECCCAP_LRAM.unLR_BUSADERSTR.u4Data & u4ERRH_ECC_MASK_2BIT_DTP_LRAM_ADDR ) != (U4)0U )
			{
				t_u1ErrorStatus = u1ERRH_ECC_ERR_2BITDETECT;
			}
			break;

		case u1ERRH_ECC_DTP_CRAM_ADDR:
			if( ( REG_ECC_BECCCAP_CRAM.unCR_BUSADERSTR.u4Data & u4ERRH_ECC_MASK_2BIT_DTP_CRAM_ADDR ) != (U4)0U )
			{
				t_u1ErrorStatus = u1ERRH_ECC_ERR_2BITDETECT;
			}
			break;

		case u1ERRH_ECC_DTP_CFL_ADDR:
			if( ( REG_ECC_BECCCAP_CFL.unCF_BUSADERSTR.u4Data & u4ERRH_ECC_MASK_2BIT_DTP_CFL_ADDR ) != (U4)0U )
			{
				t_u1ErrorStatus = u1ERRH_ECC_ERR_2BITDETECT;
			}
			break;

		case u1ERRH_ECC_DTP_PERI_ADDR:
			if( ( REG_ECC_BECCCAP_PERI.unPH_BUSADERSTR.u4Data & u4ERRH_ECC_MASK_2BIT_DTP_PERI_ADDR ) != (U4)0U )
			{
				t_u1ErrorStatus = u1ERRH_ECC_ERR_2BITDETECT;
			}
			break;

		case u1ERRH_ECC_DTP_EMU_ADDR:
			if( ( REG_ECC_BECCCAP_EMU.unEM_BUSADERSTR.u4Data & u4ERRH_ECC_MASK_2BIT_DTP_EMU_ADDR ) != (U4)0U )
			{
				t_u1ErrorStatus = u1ERRH_ECC_ERR_2BITDETECT;
			}
			break;

#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
		case u1ERRH_ECC_DTP_HB90MECC_ADDR:
		case u1ERRH_ECC_DTP_HB90SECC_ADDR:
#endif
		case u1ERRH_ECC_DTP_HB92MECC_ADDR:
		case u1ERRH_ECC_DTP_HB92SECC_ADDR:
		case u1ERRH_ECC_DTP_HB94SECC_ADDR:
		case u1ERRH_ECC_DTP_HB97MECC_ADDR:
		case u1ERRH_ECC_DTP_HB98MECC_ADDR:
#if ( MCU_TYPE_SERIES == MCU_RH850U2B6)
		case u1ERRH_ECC_DTP_HB911MECC_ADDR:
		case u1ERRH_ECC_DTP_HB912MECC_ADDR:
#endif
			t_pstReg_HbnEcc = (volatile Reg_Ecc_HbnEccType*)pcstReg_HbnEcc[t_u1ModuleNum - u1ERRH_ECC_HBNECC_ADDR_OFFSET];
			if( ( t_pstReg_HbnEcc->unHBEC1STERSTR.u4Data & (U4)ECC_HBNECC_HBEC1STERSTR_AECDEDF0 ) != (U4)0U )
			{
				t_u1ErrorStatus = u1ERRH_ECC_ERR_2BITDETECT;
			}
			break;

		case u1ERRH_ECC_DTP_V2A1_ADDR:
		case u1ERRH_ECC_DTP_V2A2_ADDR:
		case u1ERRH_ECC_DTP_V2A3_ADDR:
		case u1ERRH_ECC_DTP_V2A4_ADDR:
		case u1ERRH_ECC_DTP_V2A5_ADDR:
		case u1ERRH_ECC_DTP_V2A6_ADDR:
		case u1ERRH_ECC_DTP_V2A7_ADDR:
		case u1ERRH_ECC_DTP_V2A8_ADDR:
		case u1ERRH_ECC_DTP_V2A9_ADDR:
		case u1ERRH_ECC_DTP_V2A10_ADDR:
		case u1ERRH_ECC_DTP_V2A11_ADDR:
			t_pstReg_V2an = (volatile Reg_Ecc_BeccCap_V2AnType*)pcstReg_V2an[t_u1ModuleNum - u1ERRH_ECC_V2AN_ADDR_OFFSET];
			if( ( t_pstReg_V2an->unPHC_BUSADERSTR.u4Data & u4ERRH_ECC_MASK_2BIT_DTP_V2AN_ADDR ) != (U4)0U )
			{
				t_u1ErrorStatus = u1ERRH_ECC_ERR_2BITDETECT;
			}
			break;

/*		case u1ERRH_ECC_DTP_DFPFNT_ADDR: */
			/* DFPは非使用のため何もしない */
/*			break; */

		default:
			/* 何もしない */
			break;
	}

	return( t_u1ErrorStatus );
}

/*----------------------------------------------------------------------------------------------*/
/*	ECC Fatal Error Status Get Function( DTP Data )												*/
/*	return		: ErrorStatus																	*/
/*	parameters	: ModuleNumber																	*/
/*----------------------------------------------------------------------------------------------*/
static	U1			ErrH_Ecc_GetEccFatalErrStsDtpData( U1 t_u1ModuleNum )
{
	volatile Reg_Ecc_HbnEccType*			t_pstReg_HbnEcc;
	volatile Reg_Ecc_BeccCap_V2AnType*		t_pstReg_V2an;
	U1										t_u1ErrorStatus;

	t_u1ErrorStatus = u1ERRH_ECC_ERR_NOTDETECT;

	switch( t_u1ModuleNum )
	{
		case u1ERRH_ECC_DTP_LRAM_DATA:
			if( ( REG_ECC_BECCCAP_LRAM.unLR_BUSDDERSTR.u4Data & u4ERRH_ECC_MASK_2BIT_DTP_LRAM_DATA ) != (U4)0U )
			{
				t_u1ErrorStatus = u1ERRH_ECC_ERR_2BITDETECT;
			}
			break;

		case u1ERRH_ECC_DTP_CRAM_DATA:
			if( ( REG_ECC_BECCCAP_CRAM.unCR_BUSDDERSTR.u4Data & u4ERRH_ECC_MASK_2BIT_DTP_CRAM_DATA ) != (U4)0U )
			{
				t_u1ErrorStatus = u1ERRH_ECC_ERR_2BITDETECT;
			}
			break;

		case u1ERRH_ECC_DTP_PERI_DATA:
			if( ( REG_ECC_BECCCAP_PERI.unPH_BUSDDERSTR.u4Data & u4ERRH_ECC_MASK_2BIT_DTP_PERI_DATA ) != (U4)0U )
			{
				t_u1ErrorStatus = u1ERRH_ECC_ERR_2BITDETECT;
			}
			break;

		case u1ERRH_ECC_DTP_DMDT_DATA:
			if( ( REG_ECC_BECCCAP_DMDT.unDM_BUSDDERSTR.u4Data & u4ERRH_ECC_MASK_2BIT_DTP_DMDT_DATA ) != (U4)0U )
			{
				t_u1ErrorStatus = u1ERRH_ECC_ERR_2BITDETECT;
			}
			break;

		case u1ERRH_ECC_DTP_EMU_DATA:
			if( ( REG_ECC_BECCCAP_EMU.unEM_BUSDDERSTR.u4Data & u4ERRH_ECC_MASK_2BIT_DTP_EMU_DATA ) != (U4)0U )
			{
				t_u1ErrorStatus = u1ERRH_ECC_ERR_2BITDETECT;
			}
			break;

#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
		case u1ERRH_ECC_DTP_HB90MECC_DATA:
		case u1ERRH_ECC_DTP_HB90SECC_DATA:
#endif
		case u1ERRH_ECC_DTP_HB92MECC_DATA:
		case u1ERRH_ECC_DTP_HB92SECC_DATA:
		case u1ERRH_ECC_DTP_HB94SECC_DATA:
		case u1ERRH_ECC_DTP_HB97MECC_DATA:
		case u1ERRH_ECC_DTP_HB98MECC_DATA:
#if ( MCU_TYPE_SERIES == MCU_RH850U2B6)
		case u1ERRH_ECC_DTP_HB911MECC_DATA:
		case u1ERRH_ECC_DTP_HB912MECC_DATA:
#endif
			t_pstReg_HbnEcc = (volatile Reg_Ecc_HbnEccType*)pcstReg_HbnEcc[t_u1ModuleNum - u1ERRH_ECC_HBNECC_DATA_OFFSET];
			if( ( t_pstReg_HbnEcc->unHBEC1STERSTR.u4Data & (U4)ECC_HBNECC_HBEC1STERSTR_DEDF0 ) != (U4)0U )
			{
				t_u1ErrorStatus = u1ERRH_ECC_ERR_2BITDETECT;
			}
			break;

		case u1ERRH_ECC_DTP_V2A1_DATA:
		case u1ERRH_ECC_DTP_V2A2_DATA:
		case u1ERRH_ECC_DTP_V2A3_DATA:
		case u1ERRH_ECC_DTP_V2A4_DATA:
		case u1ERRH_ECC_DTP_V2A5_DATA:
		case u1ERRH_ECC_DTP_V2A6_DATA:
		case u1ERRH_ECC_DTP_V2A7_DATA:
		case u1ERRH_ECC_DTP_V2A8_DATA:
		case u1ERRH_ECC_DTP_V2A9_DATA:
		case u1ERRH_ECC_DTP_V2A10_DATA:
		case u1ERRH_ECC_DTP_V2A11_DATA:
			t_pstReg_V2an = (volatile Reg_Ecc_BeccCap_V2AnType*)pcstReg_V2an[t_u1ModuleNum - u1ERRH_ECC_V2AN_DATA_OFFSET];
			if( ( t_pstReg_V2an->unPHC_BUSDDERSTR.u4Data & u4ERRH_ECC_MASK_2BIT_DTP_V2AN_DATA ) != (U4)0U )
			{
				t_u1ErrorStatus = u1ERRH_ECC_ERR_2BITDETECT;
			}
			break;

/*		case u1ERRH_ECC_DTP_DFPROM_DATA: */
/*		case u1ERRH_ECC_DTP_DFPSYS_DATA: */
/*		case u1ERRH_ECC_DTP_DFPFNT_DATA: */
			/* DFPは非使用のため何もしない */

		default:
			/* 何もしない */
			break;
	}

	return( t_u1ErrorStatus );
}

/*----------------------------------------------------------------------------------------------*/
/* General compare 4 byte register with mask Function											*/
/* return		: Register Check Result															*/
/* parameters	: Address(Sync)																	*/
/*				: Expected value																*/
/*				: Mask(0xXXXXXXXX <0:no compare / 1:compare>)									*/
/*----------------------------------------------------------------------------------------------*/
static U1		ErrH_Ecc_Compare4ByteMask( volatile const U4 *t_pcu4Address, U4 t_u4ExpectedValue, U4 t_u4Mask )
{
	U4							t_u4Exp;
	U1							t_u1Result;				/* 戻り値 */

	t_u1Result = (U1)OK;
	
	t_u4Exp = t_u4ExpectedValue & t_u4Mask;
	
	if ( ( *t_pcu4Address & t_u4Mask ) != t_u4Exp )
	{
		t_u1Result = (U1)NG;
	}

	return ( t_u1Result );
}

/*----------------------------------------------------------------------------------------------*/
/* ECC restore 4 byte register with mask Function (ECC Protection Release)						*/
/* return		: none																			*/
/* parameters	: Address(Sync)																	*/
/*				: Expected value																*/
/*				: Mask(0xXXXXXXXX <0:no restore / 1:restore>)									*/
/*----------------------------------------------------------------------------------------------*/
static void	ErrH_Ecc_Reg_RestoreEccProt4ByteMask( volatile U4 *t_pu4Address, U4 t_u4ExpectedValue, U4 t_u4Mask )
{
	U4							t_u4Exp;
	U4							t_u4Val;

	t_u4Exp = t_u4ExpectedValue & t_u4Mask;
	
	t_u4Val = *t_pu4Address;
	
	/* ECC制御レジスタのKey Code Protection解除 */
	REG_ECC_ECCKC.unKCPROT.u4Data = (U4)ECC_ECCDF_KCPROT_KCE_ENABLE;

	*t_pu4Address = ( t_u4Val & (U4)(~t_u4Mask) ) | t_u4Exp;

	/* ECC制御レジスタのKey Code Protection再開 */
	REG_ECC_ECCKC.unKCPROT.u4Data = (U4)ECC_ECCDF_KCPROT_KCE_DISABLE;
	Bswlib_Sync_Pipeline_4( REG_ECC_ECCKC.unKCPROT.u4Data );
}

/*----------------------------------------------------------------------------------------------*/
/* APEC restore 4 byte register with mask Function (APEC(PB5ECC) Protection Release)			*/
/* return		: none																			*/
/* parameters	: Address(Sync)																	*/
/*				: Expected value																*/
/*				: Mask(0xXXXXXXXX <0:no restore / 1:restore>)									*/
/*----------------------------------------------------------------------------------------------*/
static void	ErrH_Ecc_Reg_RestorePb5eccApecProt4ByteMask( volatile U4 *t_pu4Address, U4 t_u4ExpectedValue, U4 t_u4Mask)
{
	U4							t_u4Exp;
	U4							t_u4Val;

	t_u4Exp = t_u4ExpectedValue & t_u4Mask;
	
	t_u4Val = *t_pu4Address;
	
	/* APEC制御レジスタのKey Code Protection解除 */
	REG_ECC_PB5ECC.unAPECKCPROT.u4Data = (U4)ECC_PBNECC_APECKCPROT_KCE_ENABLE;

	*t_pu4Address = ( t_u4Val & (U4)(~t_u4Mask) ) | t_u4Exp;

	/* APEC制御レジスタのKey Code Protection再開 */
	REG_ECC_PB5ECC.unAPECKCPROT.u4Data = (U4)ECC_PBNECC_APECKCPROT_KCE_DISABLE;
	Bswlib_Sync_Pipeline_4( REG_ECC_PB5ECC.unAPECKCPROT.u4Data );
}


#pragma ghs section text=default

#endif	// zantei ECCは2月末非対応
/*-- End Of File -------------------------------------------------------------------------------*/
