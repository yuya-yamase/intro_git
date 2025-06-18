/* Spi-r04-3000-0200-a-v00 */
/************************************************************************************************/
/*																								*/
/*		SPI User Configuration																	*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/


/*==============================================================================================*/
/*	include files																				*/
/*==============================================================================================*/
#include	"Std_Types.h"
#include	"Spi_Ucfg.h"

#include	"pil_spi.h"
#include	"Dma.h"
#include	"Spi.h"

/*==============================================================================================*/
/*	defines / data types / structs / unions	/ macros											*/
/*==============================================================================================*/
/*	Mode A Channel Configuration Data	*/
#define		Spi_SetModeAChannelConfig(id)																	\
{																											\
	{																										\
		/* MSPInCTL1レジスタに設定する値 */																	\
		( (U4)MSPI_CTL1_MSSEL 	* (U4)PIL_SPI_MASTERSLAVE_MASTER ) 										+	\
		( (U4)MSPI_CTL1_CSIE	* (U4)MSPI_CTL1_CSIE_IGNORE ) 											+	\
		( (U4)MSPI_CTL1_SAMP 	* (U4)MSPI_CTL1_SAMP_STANDARD ) 										+	\
		( (U4)MSPI_CTL1_CKR 	* (U4)SPI_UCFG_MODEA_CH##id##_SHIFTCLOCKIDLELEVEL ) 					+	\
		( (U4)MSPI_CTL1_SOLS_0 	* (U4)SPI_UCFG_MODEA_CH##id##_SOUTFUNCTION ),								\
		/* u4CFG1:MSPInCFGm1レジスタに設定する値 */															\
		( (U4)MSPI_CFG1_CPOL	* (U4)SPI_UCFG_MODEA_CH##id##_CLOCKIDLELEVEL )							+	\
		( (U4)MSPI_CFG1_CPHA	* (U4)SPI_UCFG_MODEA_CH##id##_STARTEDGE )								+	\
		( (U4)MSPI_CFG1_DIR		* (U4)SPI_UCFG_MODEA_CH##id##_BITDIRECTION )							+	\
		( (U4)MSPI_CFG1_ICLS	* (U4)MSPI_CFG1_ICLS_CS_INACTIVE )										+	\
		( (U4)MSPI_CFG1_FIDL	* (U4)MSPI_CFG1_FIDL_IDLE_NOT_INSERT )									+	\
		( (U4)MSPI_CFG1_CSRI	* (U4)MSPI_CFG1_CSRI_CS_INACTIVE )										+	\
		( (U4)MSPI_CFG1_SAFCM	* (U4)MSPI_CFG1_SAFCM_NOT_MASK_CRCERR )									+	\
		( (U4)MSPI_CFG1_SAFS	* (U4)MSPI_CFG1_SAFS_IN_FRAME )											+	\
		( (U4)MSPI_CFG1_SAFE	* (U4)MSPI_CFG1_SAFE_DISABLE )											+	\
		( (U4)MSPI_CFG1_PS_0	* (U4)MSPI_CFG1_PS_ODD_PARITY )											+	\
		( (U4)MSPI_CFG1_DECHK	* (U4)MSPI_CFG1_DECHK_NO ),													\
		/* u2CFG2:MSPInCFGm2レジスタに設定する値 */															\
		(U2)SPI_UCFG_MODEA_CH##id##_DATASIZE,																\
		/* u2CFG3:MSPInCFGm3レジスタに設定する値 */															\
		(U2)SPI_UCFG_MODEA_CH##id##_BITRATE_PATTERN,														\
		/* u2SSEL:MSPInSSELmレジスタに設定する値 */															\
		( (U2)MSPI_SSEL_JOBEN	* (U2)MSPI_SSEL_JOBEN_END )												+	\
		( (U2)MSPI_SSEL_CSR_0	* (U2)( (U2)BIT0 << (U2)SPI_UCFG_MODEA_CH##id##_CSID ) ),					\
		/* u2SEUP:MSPInSEUPmレジスタに設定する値 */															\
		(U2)( ( (PL)SPI_UCFG_MODEA_CH##id##_CS2CLKDELAY / plPIL_SPI_CLOCK_LSB ) + (PL)0.5 ),				\
		/* u2HOLD:MSPInHOLDmレジスタに設定する値 */															\
		(U2)( ( (PL)SPI_UCFG_MODEA_CH##id##_CLK2CSDELAY / plPIL_SPI_CLOCK_LSB ) + (PL)0.5 ),				\
		/* u2IDLE:MSPInIDLEmレジスタに設定する値 設定可能な最小値とする */									\
		(U2)1U,																								\
		/* u2IDLE:MSPInINDAmレジスタに設定する値 */															\
		(U2)( ( (PL)SPI_UCFG_MODEA_CH##id##_INTERDATATIME / plPIL_SPI_CLOCK_LSB ) + (PL)0.5 ),				\
		/* u1CsID:Chip Select ID (0 ～ 11) */																\
		(U1)SPI_UCFG_MODEA_CH##id##_CSID,																	\
		/* u1CsActiveLevelId:Chip Select Active Level */													\
		(U1)SPI_UCFG_MODEA_CH##id##_CSACTIVELEVEL,															\
		/* u1MasterSlave(don't care) */																		\
		(U1)PIL_SPI_MASTERSLAVE_MASTER																		\
	},																										\
	/* u4CoreId */																							\
	(U4)SPI_UCFG_MODEA_CH##id##_COREID,																		\
	/* u2DataSize */																						\
	(U2)SPI_UCFG_MODEA_CH##id##_DATASIZE,																\
	/* u1HwChannel */																						\
	(U1)SPI_UCFG_MODEA_CH##id##_HARDCH																		\
}

/*	Mode B Channel Configuration Data	*/
#define		Spi_SetModeBChannelConfig(id)																	\
{																											\
	{																										\
		/* MSPInCTL1レジスタに設定する値 */																	\
		( (U4)MSPI_CTL1_MSSEL 	* (U4)PIL_SPI_MASTERSLAVE_MASTER ) 										+	\
		( (U4)MSPI_CTL1_CSIE	* (U4)MSPI_CTL1_CSIE_IGNORE ) 											+	\
		( (U4)MSPI_CTL1_SAMP 	* (U4)MSPI_CTL1_SAMP_STANDARD ) 										+	\
		( (U4)MSPI_CTL1_CKR 	* (U4)MSPI_CTL1_CKR_HIGH ) 												+	\
		( (U4)MSPI_CTL1_SOLS_0 	* (U4)MSPI_CTL1_SOLS_LOW_HOLD ),											\
		/* u4CFG1:MSPInCFGm1レジスタに設定する値 */															\
		( (U4)MSPI_CFG1_CPOL	* (U4)SPI_UCFG_MODEB_CH##id##_CLOCKIDLELEVEL )							+	\
		( (U4)MSPI_CFG1_CPHA	* (U4)SPI_UCFG_MODEB_CH##id##_STARTEDGE )								+	\
		( (U4)MSPI_CFG1_DIR		* (U4)SPI_UCFG_MODEB_CH##id##_BITDIRECTION )							+	\
		( (U4)MSPI_CFG1_ICLS	* (U4)MSPI_CFG1_ICLS_CS_INACTIVE )										+	\
		( (U4)MSPI_CFG1_FIDL	* (U4)MSPI_CFG1_FIDL_IDLE_INSERT )										+	\
		( (U4)MSPI_CFG1_CSRI	* (U4)MSPI_CFG1_CSRI_CS_INACTIVE )										+	\
		( (U4)MSPI_CFG1_SAFCM	* (U4)MSPI_CFG1_SAFCM_NOT_MASK_CRCERR )									+	\
		( (U4)MSPI_CFG1_SAFS	* (U4)MSPI_CFG1_SAFS_IN_FRAME )											+	\
		( (U4)MSPI_CFG1_SAFE	* (U4)MSPI_CFG1_SAFE_DISABLE )											+	\
		( (U4)MSPI_CFG1_PS_0	* (U4)MSPI_CFG1_PS_ODD_PARITY )											+	\
		( (U4)MSPI_CFG1_DECHK	* (U4)MSPI_CFG1_DECHK_NO ),													\
		/* u2CFG2:MSPInCFGm2レジスタに設定する値 */															\
		(U2)PIL_SPI_LENGTH_32BIT,																			\
		/* u2CFG3:MSPInCFGm3レジスタに設定する値 */															\
		(U2)SPI_UCFG_MODEB_CH##id##_BITRATE_PATTERN,														\
		/* u2SSEL:MSPInSSELmレジスタに設定する値 */															\
		( (U2)MSPI_SSEL_JOBEN	* (U2)MSPI_SSEL_JOBEN_END )												+	\
		( (U2)MSPI_SSEL_CSR_0	* (U2)( (U2)BIT0 << (U2)SPI_UCFG_MODEB_CH##id##_CSID ) ),					\
		/* u2SEUP:MSPInSEUPmレジスタに設定する値 */															\
		(U2)( ( (PL)SPI_UCFG_MODEB_CH##id##_CS2CLKDELAY / plPIL_SPI_CLOCK_LSB ) + (PL)0.5 ),				\
		/* u2HOLD:MSPInHOLDmレジスタに設定する値 */															\
		(U2)( ( (PL)SPI_UCFG_MODEB_CH##id##_CLK2CSDELAY / plPIL_SPI_CLOCK_LSB ) + (PL)0.5 ),				\
		/* u2IDLE:MSPInIDLEmレジスタに設定する値 */															\
		(U2)( ( (PL)SPI_UCFG_MODEB_CH##id##_NEXTACCESSDELAY / plPIL_SPI_CLOCK_LSB ) + (PL)0.5 ),			\
		/* u2IDLE:MSPInINDAmレジスタに設定する値 */															\
		(U2)( ( (PL)SPI_UCFG_MODEB_CH##id##_INTERDATATIME / plPIL_SPI_CLOCK_LSB ) + (PL)0.5 ),				\
		/* u1CsID:Chip Select ID (0 ～ 11) */																\
		(U1)SPI_UCFG_MODEB_CH##id##_CSID,																	\
		/* u1CsActiveLevelId:Chip Select Active Level */													\
		(U1)SPI_UCFG_MODEB_CH##id##_CSACTIVELEVEL,															\
		/* u1MasterSlave(don't care) */																		\
		(U1)PIL_SPI_MASTERSLAVE_MASTER																		\
	},																										\
	/* u4CoreId */																							\
	(U4)SPI_UCFG_MODEB_CH##id##_COREID,																		\
	/* u1HwChannel */																						\
	(U1)SPI_UCFG_MODEB_CH##id##_HARDCH																		\
}

#define		SPI_UCFG_MODEC_GetAddressMask(dma_size)															\
(																											\
	(((U1)(dma_size) == (U1)u1DMA_TRANSSIZE_1)																\
			? (U4)0x00000000U																				\
			: (((U1)(dma_size) == (U1)u1DMA_TRANSSIZE_2)													\
				 ? (U4)BIT0																					\
				 : (U4)(BIT0+BIT1)))																		\
)

/*	Mode C Channel Configuration Data	*/
#define		Spi_SetModeCChannelConfig_master(id)															\
{																											\
	{																										\
		/* MSPInCTL1レジスタに設定する値 */																	\
		( (U4)MSPI_CTL1_MSSEL 	* (U4)SPI_UCFG_MODEC_CH##id##_MASTERSLAVEMODE ) 						+	\
		( (U4)MSPI_CTL1_CSIE	* (U4)MSPI_CTL1_CSIE_IGNORE ) 											+	\
		( (U4)MSPI_CTL1_SAMP 	* (U4)MSPI_CTL1_SAMP_STANDARD ) 										+	\
		( (U4)MSPI_CTL1_CKR 	* (U4)SPI_UCFG_MODEC_CH##id##_SHIFTCLOCKIDLELEVEL ) 					+	\
		( (U4)MSPI_CTL1_SOLS_0 	* (U4)SPI_UCFG_MODEC_CH##id##_SOUTFUNCTION ),								\
		/* u4CFG1:MSPInCFGm1レジスタに設定する値 */															\
		( (U4)MSPI_CFG1_CPOL	* (U4)SPI_UCFG_MODEC_CH##id##_CLOCKIDLELEVEL )							+	\
		( (U4)MSPI_CFG1_CPHA	* (U4)SPI_UCFG_MODEC_CH##id##_STARTEDGE )								+	\
		( (U4)MSPI_CFG1_DIR		* (U4)SPI_UCFG_MODEC_CH##id##_BITDIRECTION )							+	\
		( (U4)MSPI_CFG1_ICLS	* (U4)MSPI_CFG1_ICLS_CS_INACTIVE )										+	\
		( (U4)MSPI_CFG1_FIDL	* (U4)MSPI_CFG1_FIDL_IDLE_INSERT )										+	\
		( (U4)MSPI_CFG1_CSRI	* (U4)MSPI_CFG1_CSRI_CS_INACTIVE )										+	\
		( (U4)MSPI_CFG1_SAFCM	* (U4)MSPI_CFG1_SAFCM_NOT_MASK_CRCERR )									+	\
		( (U4)MSPI_CFG1_SAFS	* (U4)MSPI_CFG1_SAFS_IN_FRAME )											+	\
		( (U4)MSPI_CFG1_SAFE	* (U4)MSPI_CFG1_SAFE_DISABLE )											+	\
		( (U4)MSPI_CFG1_PS_0	* (U4)MSPI_CFG1_PS_ODD_PARITY )											+	\
		( (U4)MSPI_CFG1_DECHK	* (U4)MSPI_CFG1_DECHK_NO ),													\
		/* u2CFG2:MSPInCFGm2レジスタに設定する値 */															\
		(U2)SPI_UCFG_MODEC_CH##id##_DATASIZE,																\
		/* u2CFG3:MSPInCFGm3レジスタに設定する値 */															\
		(U2)SPI_UCFG_MODEC_CH##id##_BITRATE_PATTERN,														\
		/* u2SSEL:MSPInSSELmレジスタに設定する値 */															\
		( (U2)MSPI_SSEL_JOBEN	* (U2)MSPI_SSEL_JOBEN_END )												+	\
		( (U2)MSPI_SSEL_CSR_0	* (U2)( (U2)BIT0 << (U2)SPI_UCFG_MODEC_CH##id##_CSID ) ),					\
		/* u2SEUP:MSPInSEUPmレジスタに設定する値 */															\
		(U2)( ( (PL)SPI_UCFG_MODEC_CH##id##_CS2CLKDELAY / plPIL_SPI_CLOCK_LSB ) + (PL)0.5 ),				\
		/* u2HOLD:MSPInHOLDmレジスタに設定する値 */															\
		(U2)( ( (PL)SPI_UCFG_MODEC_CH##id##_CLK2CSDELAY / plPIL_SPI_CLOCK_LSB ) + (PL)0.5 ),				\
		/* u2IDLE:MSPInIDLEmレジスタに設定する値 */															\
		(U2)( ( (PL)SPI_UCFG_MODEC_CH##id##_NEXTACCESSDELAY / plPIL_SPI_CLOCK_LSB ) + (PL)0.5 ),			\
		/* u2IDLE:MSPInINDAmレジスタに設定する値 */															\
		(U2)( ( (PL)SPI_UCFG_MODEC_CH##id##_INTERDATATIME / plPIL_SPI_CLOCK_LSB ) + (PL)0.5 ),				\
		/* u1CsID:Chip Select ID (0 ～ 11) */																\
		(U1)SPI_UCFG_MODEC_CH##id##_CSID,																	\
		/* u1CsActiveLevelId:Chip Select Active Level */													\
		(U1)SPI_UCFG_MODEC_CH##id##_CSACTIVELEVEL,															\
		/* u1MasterSlave */																					\
		(U1)SPI_UCFG_MODEC_CH##id##_MASTERSLAVEMODE															\
	},																										\
	/* u4CoreId */																							\
	(U4)SPI_UCFG_MODEC_CH##id##_COREID,																		\
	/* u4NotifId */																							\
	(U4)SPI_UCFG_MODEC_CH##id##_NOTIF_ID,																	\
	/* u4AddressMask*/																						\
	(U4)SPI_UCFG_MODEC_GetAddressMask(SPI_UCFG_MODEC_CH##id##_DMASIZE),										\
	/* u1HwChannel */																						\
	(U1)SPI_UCFG_MODEC_CH##id##_HARDCH,																		\
	/* DMA送信チャネル */																					\
	(U1)SPI_UCFG_MODEC_CH##id##_DMATXCH,																	\
	/* DMA受信チャネル */																					\
	(U1)SPI_UCFG_MODEC_CH##id##_DMARXCH,																	\
	/* DMA転送サイズ */																						\
	(U1)SPI_UCFG_MODEC_CH##id##_DMASIZE,																	\
	/* u1NotifArg */																						\
	(U1)SPI_UCFG_MODEC_CH##id##_NOTIF_ARG,																	\
	/* u1NotifEnable */																						\
	(U1)SPI_UCFG_MODEC_CH##id##_NOTIF_ENABLE																\
}

#define		Spi_SetModeCChannelConfig_slave(id)																\
{																											\
	{																										\
		/* MSPInCTL1レジスタに設定する値 */																	\
		( (U4)MSPI_CTL1_MSSEL 	* (U4)SPI_UCFG_MODEC_CH##id##_MASTERSLAVEMODE ) 						+	\
		( (U4)MSPI_CTL1_CSIE	* (U4)MSPI_CTL1_CSIE_RECOGNIZE ) 											+	\
		( (U4)MSPI_CTL1_SAMP 	* (U4)MSPI_CTL1_SAMP_STANDARD ) 										+	\
		( (U4)MSPI_CTL1_CKR 	* (U4)SPI_UCFG_MODEC_CH##id##_SHIFTCLOCKIDLELEVEL ) 					+	\
		( (U4)MSPI_CTL1_SOLS_0 	* (U4)MSPI_CTL1_SOLS_LOW_HOLD ),											\
		/* u4CFG1:MSPInCFGm1レジスタに設定する値 */															\
		( (U4)MSPI_CFG1_CPOL	* (U4)MSPI_CFG1_CPOL_IDLE_LOW )											+	\
		( (U4)MSPI_CFG1_CPHA	* (U4)SPI_UCFG_MODEC_CH##id##_STARTEDGE )								+	\
		( (U4)MSPI_CFG1_DIR		* (U4)SPI_UCFG_MODEC_CH##id##_BITDIRECTION )							+	\
		( (U4)MSPI_CFG1_ICLS	* (U4)MSPI_CFG1_ICLS_CS_INACTIVE )										+	\
		( (U4)MSPI_CFG1_FIDL	* (U4)MSPI_CFG1_FIDL_IDLE_NOT_INSERT )									+	\
		( (U4)MSPI_CFG1_CSRI	* (U4)MSPI_CFG1_CSRI_CS_HOLD_ACTIVE )									+	\
		( (U4)MSPI_CFG1_SAFCM	* (U4)MSPI_CFG1_SAFCM_NOT_MASK_CRCERR )									+	\
		( (U4)MSPI_CFG1_SAFS	* (U4)MSPI_CFG1_SAFS_IN_FRAME )											+	\
		( (U4)MSPI_CFG1_SAFE	* (U4)MSPI_CFG1_SAFE_DISABLE )											+	\
		( (U4)MSPI_CFG1_PS_0	* (U4)MSPI_CFG1_PS_ODD_PARITY )											+	\
		( (U4)MSPI_CFG1_DECHK	* (U4)MSPI_CFG1_DECHK_NO ),													\
		/* u2CFG2:MSPInCFGm2レジスタに設定する値 */															\
		(U2)SPI_UCFG_MODEC_CH##id##_DATASIZE,																\
		/* u2CFG3:MSPInCFGm3レジスタに設定する値 */															\
		(U2)PIL_SPI_BITRATE_SLAVE,																			\
		/* u2SSEL:MSPInSSELmレジスタに設定する値 */															\
		( (U2)MSPI_SSEL_JOBEN	* (U2)MSPI_SSEL_JOBEN_END )												+	\
		( (U2)MSPI_SSEL_CSR_0	* (U2)MSPI_SSEL_CSR_DEACTIVATE ),											\
		/* u2SEUP:MSPInSEUPmレジスタに設定する値 */															\
		(U2)1U,																								\
		/* u2HOLD:MSPInHOLDmレジスタに設定する値 */															\
		(U2)1U,																								\
		/* u2IDLE:MSPInIDLEmレジスタに設定する値 */															\
		(U2)1U,																								\
		/* u2IDLE:MSPInINDAmレジスタに設定する値 */															\
		(U2)0U,																								\
		/* u1CsID:Chip Select ID (0 ～ 11) */																\
		(U1)SPI_UCFG_MODEC_CH##id##_CSID,																	\
		/* u1CsActiveLevelId:Chip Select Active Level */													\
		(U1)SPI_UCFG_MODEC_CH##id##_CSACTIVELEVEL,															\
		/* u1MasterSlave */																					\
		(U1)SPI_UCFG_MODEC_CH##id##_MASTERSLAVEMODE															\
	},																										\
	/* u4CoreId */																							\
	(U4)SPI_UCFG_MODEC_CH##id##_COREID,																		\
	/* u4NotifId */																							\
	(U4)SPI_UCFG_MODEC_CH##id##_NOTIF_ID,																	\
	/* u4AddressMask*/																						\
	(U4)SPI_UCFG_MODEC_GetAddressMask(SPI_UCFG_MODEC_CH##id##_DMASIZE),										\
	/* u1HwChannel */																						\
	(U1)SPI_UCFG_MODEC_CH##id##_HARDCH,																		\
	/* DMA送信チャネル */																					\
	(U1)SPI_UCFG_MODEC_CH##id##_DMATXCH,																	\
	/* DMA受信チャネル */																					\
	(U1)SPI_UCFG_MODEC_CH##id##_DMARXCH,																	\
	/* DMA転送サイズ */																						\
	(U1)SPI_UCFG_MODEC_CH##id##_DMASIZE,																	\
	/* u1NotifArg */																						\
	(U1)SPI_UCFG_MODEC_CH##id##_NOTIF_ARG,																	\
	/* u1NotifEnable */																						\
	(U1)SPI_UCFG_MODEC_CH##id##_NOTIF_ENABLE																\
}

#ifdef	JGXSTACK
#define	SYNC_stack_Spi_SetModeCChannelConfig_u4NotifId(id)		(SYNC_stack_SPI_UCFG_MODEC_CH##id##_NOTIF_ID)
#endif	/* JGXSTACK */

/*==============================================================================================*/
/*	variables																					*/
/*==============================================================================================*/
// #pragma ghs section bss=".SPI_BSS_VAR_NO_INIT"

#if (SPI_CFG_MODEC_USE == ON)
#if (SPI_UCFG_MODEC_CHANNEL_NUM > 0)
Spi_ModeC_ChannelDataType		stSpi_ModeC_ChannelData[SPI_UCFG_MODEC_CHANNEL_NUM]          __attribute__((section(".bss_SHARE_SPI_MODEC_CHANNELDATA")));
#else
Spi_ModeC_ChannelDataType		stSpi_ModeC_ChannelData[1]          						 __attribute__((section(".bss_SHARE_SPI_MODEC_CHANNELDATA")));
#endif
#endif

#if (SPI_CFG_MODEA_USE == ON)
#if (SPI_UCFG_MODEA_CHANNEL_NUM > 0)
Spi_ModeA_ChannelDataType		stSpi_ModeA_ChannelData[SPI_UCFG_MODEA_CHANNEL_NUM]          __attribute__((section(".bss_SHARE_SPI_MODEA_CHANNELDATA")));			/* Channel buffer information */
#else
Spi_ModeA_ChannelDataType		stSpi_ModeA_ChannelData[1]							         __attribute__((section(".bss_SHARE_SPI_MODEA_CHANNELDATA")));
#endif
#endif

// #pragma ghs section bss=default

/*==============================================================================================*/
/*	constants																					*/
/*==============================================================================================*/
#pragma ghs section rodata=".SPI_RODATA_CONST"

/*	Spi SpinLockID	*/
const	Spi_UserConfigType	cstSpi_UcfgData = 
{
	(U2)IOC_SPINLOCK_ID_SPI
};

/*	ModeA Communication A Configuration Data	*/
#if (SPI_CFG_MODEA_USE == ON)
#if (SPI_UCFG_MODEA_CHANNEL_NUM > 0)
static	const	Spi_ModeA_ChannelConfigType	s_cstSpi_UcfgModeAChannelData[SPI_UCFG_MODEA_CHANNEL_NUM] =
{
	Spi_SetModeAChannelConfig(0)
#if (SPI_UCFG_MODEA_CHANNEL_NUM > 1)
	,Spi_SetModeAChannelConfig(1)
#endif
#if (SPI_UCFG_MODEA_CHANNEL_NUM > 2)
	,Spi_SetModeAChannelConfig(2)
#endif
#if (SPI_UCFG_MODEA_CHANNEL_NUM > 3)
	,Spi_SetModeAChannelConfig(3)
#endif
#if (SPI_UCFG_MODEA_CHANNEL_NUM > 4)
	,Spi_SetModeAChannelConfig(4)
#endif
#if (SPI_UCFG_MODEA_CHANNEL_NUM > 5)
	,Spi_SetModeAChannelConfig(5)
#endif
#if (SPI_UCFG_MODEA_CHANNEL_NUM > 6)
	,Spi_SetModeAChannelConfig(6)
#endif
#if (SPI_UCFG_MODEA_CHANNEL_NUM > 7)
	,Spi_SetModeAChannelConfig(7)
#endif
#if (SPI_UCFG_MODEA_CHANNEL_NUM > 8)
	,Spi_SetModeAChannelConfig(8)
#endif
#if (SPI_UCFG_MODEA_CHANNEL_NUM > 9)
	,Spi_SetModeAChannelConfig(9)
#endif
};
#else
static	const	Spi_ModeA_ChannelConfigType	s_cstSpi_UcfgModeAChannelData[1] =
{
	{ { (U4)0x00000000U, (U4)0x00000000U, (U2)0x0000, (U2)0x0000, (U2)0x0000, (U2)0x0000, (U2)0x0000, (U2)0x0000, (U1)0x00, (U1)0x00, (U1)0x00 }, (U4)0x00000000U, (U2)0x0000, (U1)0x00 }
};
#endif

#if (SPI_UCFG_MODEA_SEQUENCE_NUM > 0) 
static	const	U1	s_cu1Spi_UcfgModeASeqData[SPI_UCFG_MODEA_SEQUENCE_NUM] =
{
	SPI_UCFG_SEQ0_CHID
#if (SPI_UCFG_MODEA_SEQUENCE_NUM > 1)
	,SPI_UCFG_SEQ1_CHID
#endif
#if (SPI_UCFG_MODEA_SEQUENCE_NUM > 2)
	,SPI_UCFG_SEQ2_CHID
#endif
#if (SPI_UCFG_MODEA_SEQUENCE_NUM > 3)
	,SPI_UCFG_SEQ3_CHID
#endif
#if (SPI_UCFG_MODEA_SEQUENCE_NUM > 4)
	,SPI_UCFG_SEQ4_CHID
#endif
#if (SPI_UCFG_MODEA_SEQUENCE_NUM > 5)
	,SPI_UCFG_SEQ5_CHID
#endif
#if (SPI_UCFG_MODEA_SEQUENCE_NUM > 6)
	,SPI_UCFG_SEQ6_CHID
#endif
#if (SPI_UCFG_MODEA_SEQUENCE_NUM > 7)
	,SPI_UCFG_SEQ7_CHID
#endif
#if (SPI_UCFG_MODEA_SEQUENCE_NUM > 8)
	,SPI_UCFG_SEQ8_CHID
#endif
#if (SPI_UCFG_MODEA_SEQUENCE_NUM > 9)
	,SPI_UCFG_SEQ9_CHID
#endif	
};
#else
static	const	U1	s_cu1Spi_UcfgModeASeqData[1] =
{
	(U1)0x00
};
#endif
#endif

/*	Mode B Communication Configuration Data	*/
#if (SPI_CFG_MODEB_USE == ON)
#if (SPI_UCFG_MODEB_CHANNEL_NUM > 0)
static	const	Spi_ModeB_ChannelConfigType	s_cstSpi_UcfgModeBChannelData[SPI_UCFG_MODEB_CHANNEL_NUM] =
{
	Spi_SetModeBChannelConfig(0)
#if (SPI_UCFG_MODEB_CHANNEL_NUM > 1)
	,Spi_SetModeBChannelConfig(1)
#endif
#if (SPI_UCFG_MODEB_CHANNEL_NUM > 2)
	,Spi_SetModeBChannelConfig(2)
#endif
};
#else
static	const	Spi_ModeB_ChannelConfigType	s_cstSpi_UcfgModeBChannelData[1] =
{
	{ { (U4)0x00000000U, (U4)0x00000000U, (U2)0x0000, (U2)0x0000, (U2)0x0000, (U2)0x0000, (U2)0x0000, (U2)0x0000, (U1)0x00, (U1)0x00, (U1)0x00 }, (U4)0x00000000U, (U1)0x00 }
};
#endif
#endif

/*	Mode C Communication Configuration Data	*/
#if (SPI_CFG_MODEC_USE == ON)
#if (SPI_UCFG_MODEC_CHANNEL_NUM > 0)
static	const	Spi_ModeC_ChannelConfigType	s_cstSpi_UcfgModeCChannelData[SPI_UCFG_MODEC_CHANNEL_NUM] =
{
#if ( SPI_UCFG_MODEC_CH0_MASTERSLAVEMODE == PIL_SPI_MASTERSLAVE_MASTER )
	Spi_SetModeCChannelConfig_master(0)
#else
	Spi_SetModeCChannelConfig_slave(0)
#endif
#if (SPI_UCFG_MODEC_CHANNEL_NUM > 1)
#if ( SPI_UCFG_MODEC_CH1_MASTERSLAVEMODE == PIL_SPI_MASTERSLAVE_MASTER )
	,Spi_SetModeCChannelConfig_master(1)
#else
	,Spi_SetModeCChannelConfig_slave(1)
#endif
#endif
#if (SPI_UCFG_MODEC_CHANNEL_NUM > 2)
#if ( SPI_UCFG_MODEC_CH2_MASTERSLAVEMODE == PIL_SPI_MASTERSLAVE_MASTER )
	,Spi_SetModeCChannelConfig_master(2)
#else
	,Spi_SetModeCChannelConfig_slave(2)
#endif
#endif
#if (SPI_UCFG_MODEC_CHANNEL_NUM > 3)
#if ( SPI_UCFG_MODEC_CH3_MASTERSLAVEMODE == PIL_SPI_MASTERSLAVE_MASTER )
	,Spi_SetModeCChannelConfig_master(3)
#else
	,Spi_SetModeCChannelConfig_slave(3)
#endif
#endif
};
#else
static	const	Spi_ModeC_ChannelConfigType	s_cstSpi_UcfgModeCChannelData[1] =
{
	{ { (U4)0x00000000U, (U4)0x00000000U, (U2)0x0000, (U2)0x0000, (U2)0x0000, (U2)0x0000, (U2)0x0000, (U2)0x0000, (U1)0x00, (U1)0x00, (U1)0x00 }, (U4)0x00000000U, (U4)(RTE_EVT_ID_DUMMY), (U4)0x00000000U, (U1)0x00, (U1)0x00, (U1)0x00, (U1)0x00, (U1)0x00 }
};
#endif
#endif

#if (SPI_CFG_MODEA_USE == ON)
const	Spi_ModeA_UserConfigType	cstSpi_UcfgModeAData =
{
	&s_cstSpi_UcfgModeAChannelData[0],
	&s_cu1Spi_UcfgModeASeqData[0],
	(U1)SPI_UCFG_MODEA_CHANNEL_NUM
};
#endif

#if (SPI_CFG_MODEB_USE == ON)
const	Spi_ModeB_UserConfigType	cstSpi_UcfgModeBData =
{
	&s_cstSpi_UcfgModeBChannelData[0],
	(U1)SPI_UCFG_MODEB_CHANNEL_NUM
};
#endif

#if (SPI_CFG_MODEC_USE == ON)
const	Spi_ModeC_UserConfigType	cstSpi_UcfgModeCData =
{
	&s_cstSpi_UcfgModeCChannelData[0],
	(U1)SPI_UCFG_MODEC_CHANNEL_NUM
};
#endif

#pragma ghs section rodata=default

#ifdef	JGXSTACK

void SYNC_stack_s_cstSpi_UcfgModeCChannelData_u4NotifId( const S4* t_pcs4Param )
{
#if( SPI_UCFG_MODEC_CHANNEL_NUM > 0 )
    SYNC_stack_Spi_SetModeCChannelConfig_u4NotifId(0)( t_pcs4Param );
#endif
#if( SPI_UCFG_MODEC_CHANNEL_NUM > 1 )
    SYNC_stack_Spi_SetModeCChannelConfig_u4NotifId(1)( t_pcs4Param );
#endif
#if( SPI_UCFG_MODEC_CHANNEL_NUM > 2 )
	SYNC_stack_Spi_SetModeCChannelConfig_u4NotifId(2)( t_pcs4Param );
#endif
#if( SPI_UCFG_MODEC_CHANNEL_NUM > 3 )
    SYNC_stack_Spi_SetModeCChannelConfig_u4NotifId(3)( t_pcs4Param );
#endif
}

#endif	/* JGXSTACK */
/*-- End Of File -------------------------------------------------------------------------------*/
