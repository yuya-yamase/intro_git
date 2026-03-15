/* Spi-r04-3000-0200-a-v00 */
/************************************************************************************************/
/*																								*/
/*		SPI Driver																				*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

#ifndef SPI_UCFG_H
#define SPI_UCFG_H

/*==============================================================================================*/
/*	include files																				*/
/*==============================================================================================*/
#include "bswlib.h"
#include "Os.h"

/*==============================================================================================*/
/*	defines / data types / structs / unions / macros											*/
/*==============================================================================================*/
#define BSW_CFG_GETSPINLOCK_SPI()					SuspendAllInterrupts()
#define BSW_CFG_RELEASESPINLOCK_SPI()	 			ResumeAllInterrupts()

#define BSW_CFG_GETSPINLOCK_PIL_SPI()				SuspendAllInterrupts()
#define BSW_CFG_RELEASESPINLOCK_PIL_SPI()			ResumeAllInterrupts()

#define SPI_CFG_MODEA_USE					(OFF)
#define SPI_CFG_MODEB_USE					(OFF)
#define SPI_CFG_MODEC_USE					(ON)

#define SPI_CFG_SYNCSEND_TIMEOUT			(20U)	/* @todo S.Abe : 20251024 to avoid an infinit loop */
#define SPI_CFG_SYNCRECEIVE_TIMEOUT			(20U)	/* @todo S.Abe : 20251024 to avoid an infinit loop */
#define SPI_CFG_SENDDMASTOP_TIMEOUT			(20U)	/* @todo S.Abe : 20251024 to avoid an infinit loop */
#define SPI_CFG_RECEIVEDMASTOP_TIMEOUT		(20U)	/* @todo S.Abe : 20251024 to avoid an infinit loop */
#define SPI_CFG_ASYNCDMASTART_TIMEOUT		(20U)	/* @todo S.Abe : 20251024 to avoid an infinit loop */

#define Bswlib_GetCoreId()					(u4_g_GetCoreId())


/* Spi Communication ModeC ID (SPI_COMC_ID xxx) */
#define SPI_COMC_ID_SOC_MCU1				(0)

#define SPI_UCFG_MODEC_CHANNEL_NUM			(1)

#define SPI_UCFG_MODEC_CH0_HARDCH			(PIL_SPI_CH2_0)
#define SPI_UCFG_MODEC_CH0_SHIFTCLOCKIDLELEVEL	(PIL_SPI_CKR_HIGH)
#define SPI_UCFG_MODEC_CH0_SOUTFUNCTION		(PIL_SPI_SOLS_LOW)
#define SPI_UCFG_MODEC_CH0_CLOCKIDLELEVEL	(LO)
#define SPI_UCFG_MODEC_CH0_STARTEDGE		(PIL_SPI_STARTEDGE_CLK)
#define SPI_UCFG_MODEC_CH0_BITRATE_PATTERN	(PIL_SPI_BITRATE_10M)
#define SPI_UCFG_MODEC_CH0_BITDIRECTION		(PIL_SPI_DIRECTION_MSBFIRST)
#define SPI_UCFG_MODEC_CH0_DATASIZE			(PIL_SPI_LENGTH_32BIT)
#define SPI_UCFG_MODEC_CH0_CSINENABLE 		(PIL_SPI_CS_IGNORE)
#define SPI_UCFG_MODEC_CH0_CSACTIVELEVEL	(LO)
#define SPI_UCFG_MODEC_CH0_CSID				(PIL_SPI_CSID_0)
#define SPI_UCFG_MODEC_CH0_MASTERSLAVEMODE	(PIL_SPI_MASTERSLAVE_SLAVE)
#define SPI_UCFG_MODEC_CH0_CS2CLKDELAY		(PIL_SPI_DELAY_50NS)
#define SPI_UCFG_MODEC_CH0_CLK2CSDELAY		(PIL_SPI_DELAY_50NS)
#define SPI_UCFG_MODEC_CH0_NEXTACCESSDELAY	(PIL_SPI_DELAY_50NS)
#define SPI_UCFG_MODEC_CH0_COREID			(BSW_CORE_ID_CORE1)
#define SPI_UCFG_MODEC_CH0_TRGSELDMADTS		(PIL_SPI_TGCTL_TRGSEL_DMA)
#define SPI_UCFG_MODEC_CH0_DMATXCH			(DMA_CH_DATA_ID_0)
#define SPI_UCFG_MODEC_CH0_DMARXCH			(DMA_CH_DATA_ID_1)
#define SPI_UCFG_MODEC_CH0_DMASIZE			(u1DMA_TRANSSIZE_4)
#define SPI_UCFG_MODEC_CH0_NOTIF_ID			(0) //@todo
#define SPI_UCFG_MODEC_CH0_NOTIF_ARG		(0)
#define SPI_UCFG_MODEC_CH0_NOTIF_ENABLE		(OFF)


#define IOC_SPINLOCK_ID_PIL_SPI				(0)
#define IOC_SPINLOCK_ID_SPI					(0)

#endif /* SPI_UCFG_H */
/*-- End Of File -------------------------------------------------------------------------------*/
