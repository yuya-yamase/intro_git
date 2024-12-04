/* pil_spi-r04-3000-0200-a-v01 */
/************************************************************************************************/
/*																								*/
/*		PIL SPI Driver																			*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

#ifndef PIL_SPI_H
#define PIL_SPI_H

/*==============================================================================================*/
/*	include files																				*/
/*==============================================================================================*/
#include	"Bsw_cfg.h"

#include	"Reg_Mspi.h"

/*==============================================================================================*/
/*	defines / data types / structs / unions	/ macros											*/
/*==============================================================================================*/
/* MSPI Channel Number */
#define		u1PIL_SPI_UNIT_NUM			( (U1)MSPI_UNIT_NUM ) 		/* ユニット数 */
#define		u1PIL_SPI_CH_NUM			( (U1)MSPI_CH_NUM )			/* チャネル数 */

/* Hard Channel ID : ユニット番号(4Bit)+チャネル番号(4Bit) */
#define		Pil_Spi_SetCH( t_Unit, t_Ch )	( ( ( t_Unit ) * 0x10) + ( t_Ch ) )

/* MSPIチャネルからユニット番号、チャネル番号を取得するマクロ */
#define		Pil_Spi_GetUnitNo( t_Id )			( (U1)( ( ( t_Id ) & (U1)0xF0 ) >> (U1)4 ) )	/* 右4bitシフトしてUnitNoを抽出(上位4bit取り出し) */
#define		Pil_Spi_GetSpiChNo( t_Id )			( (U1)( ( t_Id ) & (U1)0x0F ) )					/* 上位4bitを切り捨てSpiChannelNoを抽出(下位4bit取り出し) */

/* Hard Channel ID  */
#define		PIL_SPI_CH0_0		Pil_Spi_SetCH( 0 , 0 )
#define		PIL_SPI_CH0_1		Pil_Spi_SetCH( 0 , 1 )
#define		PIL_SPI_CH0_2		Pil_Spi_SetCH( 0 , 2 )
#define		PIL_SPI_CH0_3		Pil_Spi_SetCH( 0 , 3 )
#define		PIL_SPI_CH0_4		Pil_Spi_SetCH( 0 , 4 )
#define		PIL_SPI_CH0_5		Pil_Spi_SetCH( 0 , 5 )
#define		PIL_SPI_CH0_6		Pil_Spi_SetCH( 0 , 6 )
#define		PIL_SPI_CH0_7		Pil_Spi_SetCH( 0 , 7 )
#define		PIL_SPI_CH0_8		Pil_Spi_SetCH( 0 , 8 )
#define		PIL_SPI_CH0_9		Pil_Spi_SetCH( 0 , 9 )
#define		PIL_SPI_CH0_10		Pil_Spi_SetCH( 0 , 10 )
#define		PIL_SPI_CH0_11		Pil_Spi_SetCH( 0 , 11 )
#define		PIL_SPI_CH1_0		Pil_Spi_SetCH( 1 , 0 )
#define		PIL_SPI_CH1_1		Pil_Spi_SetCH( 1 , 1 )
#define		PIL_SPI_CH1_2		Pil_Spi_SetCH( 1 , 2 )
#define		PIL_SPI_CH1_3		Pil_Spi_SetCH( 1 , 3 )
#define		PIL_SPI_CH1_4		Pil_Spi_SetCH( 1 , 4 )
#define		PIL_SPI_CH1_5		Pil_Spi_SetCH( 1 , 5 )
#define		PIL_SPI_CH1_6		Pil_Spi_SetCH( 1 , 6 )
#define		PIL_SPI_CH1_7		Pil_Spi_SetCH( 1 , 7 )
#define		PIL_SPI_CH1_8		Pil_Spi_SetCH( 1 , 8 )
#define		PIL_SPI_CH1_9		Pil_Spi_SetCH( 1 , 9 )
#define		PIL_SPI_CH1_10		Pil_Spi_SetCH( 1 , 10 )
#define		PIL_SPI_CH1_11		Pil_Spi_SetCH( 1 , 11 )
#define		PIL_SPI_CH2_0		Pil_Spi_SetCH( 2 , 0 )
#define		PIL_SPI_CH2_1		Pil_Spi_SetCH( 2 , 1 )
#define		PIL_SPI_CH2_2		Pil_Spi_SetCH( 2 , 2 )
#define		PIL_SPI_CH2_3		Pil_Spi_SetCH( 2 , 3 )
#define		PIL_SPI_CH2_4		Pil_Spi_SetCH( 2 , 4 )
#define		PIL_SPI_CH2_5		Pil_Spi_SetCH( 2 , 5 )
#define		PIL_SPI_CH2_6		Pil_Spi_SetCH( 2 , 6 )
#define		PIL_SPI_CH2_7		Pil_Spi_SetCH( 2 , 7 )
#define		PIL_SPI_CH2_8		Pil_Spi_SetCH( 2 , 8 )
#define		PIL_SPI_CH2_9		Pil_Spi_SetCH( 2 , 9 )
#define		PIL_SPI_CH2_10		Pil_Spi_SetCH( 2 , 10 )
#define		PIL_SPI_CH2_11		Pil_Spi_SetCH( 2 , 11 )
#define		PIL_SPI_CH3_0		Pil_Spi_SetCH( 3 , 0 )
#define		PIL_SPI_CH3_1		Pil_Spi_SetCH( 3 , 1 )
#define		PIL_SPI_CH3_2		Pil_Spi_SetCH( 3 , 2 )
#define		PIL_SPI_CH3_3		Pil_Spi_SetCH( 3 , 3 )
#define		PIL_SPI_CH4_0		Pil_Spi_SetCH( 4 , 0 )
#define		PIL_SPI_CH4_1		Pil_Spi_SetCH( 4 , 1 )
#define		PIL_SPI_CH4_2		Pil_Spi_SetCH( 4 , 2 )
#define		PIL_SPI_CH4_3		Pil_Spi_SetCH( 4 , 3 )
#define		PIL_SPI_CH5_0		Pil_Spi_SetCH( 5 , 0 )
#define		PIL_SPI_CH5_1		Pil_Spi_SetCH( 5 , 1 )
#define		PIL_SPI_CH5_2		Pil_Spi_SetCH( 5 , 2 )
#define		PIL_SPI_CH5_3		Pil_Spi_SetCH( 5 , 3 )
#define		PIL_SPI_CH6_0		Pil_Spi_SetCH( 6 , 0 )
#define		PIL_SPI_CH7_0		Pil_Spi_SetCH( 7 , 0 )
#define		PIL_SPI_CH7_1		Pil_Spi_SetCH( 7 , 1 )
#define		PIL_SPI_CH7_2		Pil_Spi_SetCH( 7 , 2 )
#define		PIL_SPI_CH7_3		Pil_Spi_SetCH( 7 , 3 )
#define		PIL_SPI_CH8_0		Pil_Spi_SetCH( 8 , 0 )
#define		PIL_SPI_CH8_1		Pil_Spi_SetCH( 8 , 1 )
#define		PIL_SPI_CH8_2		Pil_Spi_SetCH( 8 , 2 )
#define		PIL_SPI_CH8_3		Pil_Spi_SetCH( 8 , 3 )
#define		PIL_SPI_CH9_0		Pil_Spi_SetCH( 9 , 0 )

/* DataSize */
#define		PIL_SPI_LENGTH_8BIT			(8)
#define		PIL_SPI_LENGTH_16BIT		(16)
#define		PIL_SPI_LENGTH_32BIT		(32)

/* Bit Rate(MSPInPRCSm,MSPInCDIVm設定値) */
/* 分周式 : ( MSPInCLK / ( (4 ^ MSPInPRCSm) * MSPInCDIVm * 2 ) ) */
#define		Pil_Spi_SetBITRATE( t_Prcs, t_Cdiv )	( ( ( (U2)MSPI_CFG3_PRCS_0 ) * ( (U2)(t_Prcs) ) ) + ( ( (U2)MSPI_CFG3_CDIV_0 ) * ( (U2)(t_Cdiv) ) ) )

#define		PIL_SPI_BITRATE_10M		Pil_Spi_SetBITRATE( 0 , 4 )
#define		PIL_SPI_BITRATE_8M		Pil_Spi_SetBITRATE( 0 , 5 )
#define		PIL_SPI_BITRATE_6_7M	Pil_Spi_SetBITRATE( 0 , 6 )
#define		PIL_SPI_BITRATE_5M		Pil_Spi_SetBITRATE( 0 , 8 )
#define		PIL_SPI_BITRATE_4M		Pil_Spi_SetBITRATE( 0 , 10 )
#define		PIL_SPI_BITRATE_2_5M	Pil_Spi_SetBITRATE( 1 , 4 )
#define		PIL_SPI_BITRATE_2M		Pil_Spi_SetBITRATE( 1 , 5 )
#define		PIL_SPI_BITRATE_1M		Pil_Spi_SetBITRATE( 1 , 10 )
#define		PIL_SPI_BITRATE_SLAVE	Pil_Spi_SetBITRATE( 0 , 1 )

/* Bit Direction(MSPInDIRm設定値) */
#define		PIL_SPI_DIRECTION_MSBFIRST	(MSPI_CFG1_DIR_MSB_FIRST)
#define		PIL_SPI_DIRECTION_LSBFIRST	(MSPI_CFG1_DIR_LSB_FIRST)

/* Data Change Timing */
#define		PIL_SPI_STARTEDGE_CLK		(MSPI_CFG1_CPHA_ODD_OUT_EVEN_SAMP)
#define		PIL_SPI_STARTEDGE_CS		(MSPI_CFG1_CPHA_EVEN_OUT_ODD_SAMP)

/* Chip Select Channel ID */
#define		PIL_SPI_CSID_0				(0)
#define		PIL_SPI_CSID_1				(1)
#define		PIL_SPI_CSID_2				(2)
#define		PIL_SPI_CSID_3				(3)
#define		PIL_SPI_CSID_4				(4)
#define		PIL_SPI_CSID_5				(5)
#define		PIL_SPI_CSID_6				(6)
#define		PIL_SPI_CSID_7				(7)
#define		PIL_SPI_CSID_8				(8)
#define		PIL_SPI_CSID_9				(9)
#define		PIL_SPI_CSID_10				(10)
#define		PIL_SPI_CSID_11				(11)

/* Master Slave Mode */
#define		PIL_SPI_MASTERSLAVE_MASTER	(0)
#define		PIL_SPI_MASTERSLAVE_SLAVE	(1)

#define		plPIL_SPI_CLOCK_LSB			((PL)(12.5))		/* lsb = 12.5ns */

/* Spi Delay time */
#define		PIL_SPI_DELAY_12_5NS		(12.5)
#define		PIL_SPI_DELAY_50NS			(50.0)
#define		PIL_SPI_DELAY_100NS			(100.0)
#define		PIL_SPI_DELAY_125NS			(125.0)
#define		PIL_SPI_DELAY_150NS			(150.0)
#define		PIL_SPI_DELAY_175NS			(175.0)
#define		PIL_SPI_DELAY_200NS			(200.0)
#define		PIL_SPI_DELAY_225NS			(225.0)
#define		PIL_SPI_DELAY_250NS			(250.0)
#define		PIL_SPI_DELAY_275NS			(275.0)
#define		PIL_SPI_DELAY_300NS			(300.0)
#define		PIL_SPI_DELAY_800NS			(800.0)

/* MSPInCTL1.MSPInCKR: MSPIn Clock default level */
#define		PIL_SPI_CKR_LOW				(MSPI_CTL1_CKR_LOW)		/* 0:The default level of MSPInSCK is low	*/
#define		PIL_SPI_CKR_HIGH			(MSPI_CTL1_CKR_HIGH)	/* 1:The default level of MSPInSCK is high	*/

/* MSPInCTL1.MSPInSOLS: These bits select the MSPInSOUT function in Master mode */
#define		PIL_SPI_SOLS_LOW_HOLD		(MSPI_CTL1_SOLS_LOW_HOLD)
#define		PIL_SPI_SOLS_LOW			(MSPI_CTL1_SOLS_LOW)
#define		PIL_SPI_SOLS_HIGH_HOLD		(MSPI_CTL1_SOLS_HIGH_HOLD)
#define		PIL_SPI_SOLS_HIGH			(MSPI_CTL1_SOLS_HIGH)

/* タイムアウト設定値 */
#define PIL_SPI_WAIT_MAX				(0xFFFFFFFFU)			/* 設定最大値 */
#define u4PIL_SPI_WAIT_1US				((U4)1)					/* LIB_WaitによるWait時間 */

/* User Config Data Type Definition */
typedef struct
{
	U2									u2SpinlockId;
}Pil_Spi_UserConfigType;

/* Pil Spi Channel Configuration Type */
typedef struct{
	U4									u4CTL1;				/* MSPInCTL1レジスタに設定する値	*/
	U4									u4CFG1; 			/* MSPInCFGm1レジスタに設定する値	*/
	U2									u2CFG2; 			/* MSPInCFGm2レジスタに設定する値	*/
	U2									u2CFG3; 			/* MSPInCFGm3レジスタに設定する値	*/
	U2									u2SSEL;				/* MSPInSSELmレジスタに設定する値	*/
	U2									u2SEUP;				/* MSPInSEUPmレジスタに設定する値	*/
	U2									u2HOLD; 			/* MSPInHOLDmレジスタに設定する値	*/
	U2									u2IDLE; 			/* MSPInIDLEmレジスタに設定する値	*/
	U2									u2INDA; 			/* MSPInINDAmレジスタに設定する値	*/
	U1									u1CsID; 			/* Chip Select ID					*/
	U1									u1CsActiveLevel;	/* Chip Select ActiveLevel			*/
	U1									u1MasterSlave;		/* Master mode / Slave mode 		*/
}Pil_Spi_ChannelConfigType;

/* Pil Spi ModeC Data Type */
typedef	struct{
	U1									u1Data;
}Pil_Spi_ModeC_DataType;

/*==============================================================================================*/
/* functions																					*/
/*==============================================================================================*/
/*----------------------------------------------------------------------------------------------*/
/* API Functions																				*/
/*----------------------------------------------------------------------------------------------*/
/************************************************************************************************/
/*	Service name	:	SetComMode																*/
/*	Reentrancy		:	Concurrency Safe for different unit numbers								*/
/*						Non Re-entrant for the same unit numbers								*/
/*	Parameters (in)	:	HwChannelID - ID of SPI Unit & Channel ( PIL_SPI_CH*_# )				*/
/*					:				( * : Unit No( 0 - 9 ) , # : Channel No( 0 - 11 ) )			*/
/*					:	PilChannelConfig - Channel Configuration(Sync)							*/
/*	Return value	:	none																	*/
/*	Caveat			:	・同一ハードユニットは全て同一コアで使用すること						*/
/*					:	・通信停止状態(CTL0.EN=0)でのコールを前提とする							*/
/*					:	・Init時以外はPil_Spi_DisableCommunicationをコールしてから使用すること	*/
/*					:	・Init時以外は使用する側で必ず割禁(排他)をかけた上で使用すること		*/
/************************************************************************************************/
void	Pil_Spi_SetComMode( U1 t_u1HwChannelID, const Pil_Spi_ChannelConfigType* t_pcstPilChannelConfig );

#if ( ( SPI_CFG_MODEA_USE == ON ) || ( SPI_CFG_MODEB_USE == ON ) )
/************************************************************************************************/
/*	Service name	:	CheckComMode															*/
/*	Reentrancy		:	Concurrency Safe														*/
/*	Parameters (in)	:	HwChannelID - ID of SPI Unit & Channel ( PIL_SPI_CH*_# )				*/
/*					:				( * : Unit No( 0 - 9 ) , # : Channel No( 0 - 11 ) )			*/
/*					:	PilChannelConfig - Channel Configuration(Sync)							*/
/*	Return value	:	RegError - Register Error (OK / NG)										*/
/*	Caveat			:	-													 					*/
/************************************************************************************************/
U1		Pil_Spi_CheckComMode( U1 t_u1HwChannelID, const Pil_Spi_ChannelConfigType* t_pcstPilChannelConfig );
#endif

/************************************************************************************************/
/*	Service name	:	DisableCommunication													*/
/*	Reentrancy		:	Concurrency Safe														*/
/*	Parameters (in)	:	HwChannelID - ID of SPI Unit & Channel ( PIL_SPI_CH*_# )				*/
/*					:				( * : Unit No( 0 - 9 ) , # : Channel No( 0 - 11 ) )			*/
/*	Return value	:	none																	*/
/*	Caveat			:	・同一ハードユニットは全て同一コアで使用すること						*/
/************************************************************************************************/
void	Pil_Spi_DisableCommunication( U1 t_u1HwChannelID );

#if ( ( SPI_CFG_MODEA_USE == ON ) || ( SPI_CFG_MODEB_USE == ON ) )
/************************************************************************************************/
/*	Service name	:	SetFrameNumber															*/
/*	Reentrancy		:	Concurrency Safe for different unit numbers								*/
/*					:	Re-entrant for the same unit numbers									*/
/*	Parameters (in)	:	HwChannelID - ID of SPI Unit & Channel ( PIL_SPI_CH*_# )				*/
/*					:				( * : Unit No( 0 - 9 ) , # : Channel No( 0 - 11 ) )			*/
/*					:	Length - Frame Number													*/
/*	Return value	:	none																	*/
/*	Caveat			:	・同一ハードユニットは全て同一コアで使用すること						*/
/************************************************************************************************/
void	Pil_Spi_SetFrameNumber( U1 t_u1HwChannelID, U2 t_u2Length );

/************************************************************************************************/
/*	Service name	:	SendReceiveData															*/
/*	Reentrancy		:	Concurrency Safe for different unit numbers								*/
/*					:	Re-entrant for the same unit numbers									*/
/*	Parameters (in)	:	HwChannelID - ID of SPI Unit & Channel ( PIL_SPI_CH*_# )				*/
/*					:				( * : Unit No( 0 - 9 ) , # : Channel No( 0 - 11 ) )			*/
/*					:	TxData - Send Data(32bit)												*/
/*					:	PilChannelConfig - Channel Configuration(Sync)							*/
/*	Return value	:	Receive Data(32bit)														*/
/*	Caveat			:	・同一ハードユニットは全て同一コアで使用すること						*/
/************************************************************************************************/
U4		Pil_Spi_SendReceiveData( U1 t_u1HwChannelID, U4 t_u4TxData, const Pil_Spi_ChannelConfigType* t_pcstPilChannelConfig );
#endif

#if (SPI_CFG_MODEC_USE == ON)
/************************************************************************************************/
/*	Service name	:	StartAsync																*/
/*	Reentrancy		:	Concurrency Safe for different unit numbers								*/
/*						Non Re-entrant for the same unit numbers								*/
/*	Parameters (in)	:	HwChannelID - ID of SPI Unit & Channel ( PIL_SPI_CH*_# )				*/
/*					:				( * : Unit No( 0 - 9 ) , # : Channel No( 0 - 11 ) )			*/
/*					:	PilChannelConfig - Channel Configuration(Sync)							*/
/*					:	Times - Send Receive Data Times (1 - 0xFFFF(1 times = 2byte))			*/
/*	Return value	:	none																	*/
/*	Caveat			:	・同一ハードユニットは全て同一コアで使用すること						*/
/*						・本関数はモードC通信のDMA転送トリガとしての使用のみサポートする		*/
/*						・使用する側で必ず割禁(排他)をかけた上で使用すること					*/
/************************************************************************************************/
void	Pil_Spi_StartAsync(  U1 t_u1HwChannelID, const Pil_Spi_ChannelConfigType* t_pcstPilChannelConfig, U2 t_u2Times );
#endif

/************************************************************************************************/
/*	Service name	:	EnableUnit																*/
/*	Reentrancy		:	Concurrency Safe														*/
/*	Parameters (in)	:	UnitNo																	*/
/*	Return value	:	none																	*/
/*	Caveat			:	・同一ハードユニットは全て同一コアで使用すること						*/
/************************************************************************************************/
void	Pil_Spi_EnableUnit( U1 t_u1UnitNo );

#if (SPI_CFG_MODEC_USE == ON)
/************************************************************************************************/
/*	Service name	:	GetOvrunErrStatus														*/
/*	Reentrancy		:	Concurrency Safe														*/
/*	parameters (in)	:	HwChannelID - ID of SPI Unit & Channel ( PIL_SPI_CH*_# )				*/
/*					:				( * : Unit No( 0 - 9 ) , # : Channel No( 0 - 11 ) )			*/
/*	Return value	:	Overrun Error Status( No Error(==0) or Error(!=0) )						*/
/*	Caveat			:	・オーバーランエラーはスレーブモード時のみ検出する						*/
/************************************************************************************************/
ZORN	Pil_Spi_GetOvrunErrStatus( U1 t_u1HwChannelID );
#endif

/*==============================================================================================*/
/*	constants																					*/
/*==============================================================================================*/
// #define SEL_ROMSEC	(BSW_SEC_C_LROM0_CPU0_ASIL_CFG_SDA)
// #include "Bsw_Seccfg_Roms.h"
#pragma ghs section rodata=".SPI_RODATA_CONST"
extern	const	Pil_Spi_UserConfigType	cstPil_Spi_UcfgData;
// #include "Bsw_Seccfg_Rome.h"
// #undef SEL_ROMSEC
#pragma ghs section rodata=default

#endif /* PIL_SPI_H */
/*-- End Of File -------------------------------------------------------------------------------*/
