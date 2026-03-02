/* Copyright  : DENSO CORPORATION */
#ifndef DMA_CFG_H
#define DMA_CFG_H

/*==============================================================================================*/
/*	include files																				*/
/*==============================================================================================*/
#include	"Os.h"

/*==============================================================================================*/
/*	DMA common configuration																	*/
/*==============================================================================================*/
/* Total number of channels using Dma */
#define	DMA_UCFG_CHDATA_NUM				(2u)

/* Uninterruptible/Uninterruptible */
#define DMA_ENTER_CRITICAL_SECTION()			SuspendAllInterrupts()							/* Do not interrupt */
#define DMA_EXIT_CRITICAL_SECTION()				ResumeAllInterrupts()							/* Allow interrupts */

/* Register Check */
#define	DMA_CFG_REG_CHK						(STD_OFF)
#define DMA_CFG_REG_REFRESH					(STD_OFF)

/* DMATRGSEL DTS,DMA Access */
#define DMA_CFG_GLOBAL_REG_CONTROL			(STD_OFF)
#define DMA_CFG_DMA0_ACCESS					(STD_ON)
#define DMA_CFG_DMA1_ACCESS					(STD_OFF)

/*==============================================================================================*/
/*	Configuration per DMA channel ID															*/
/*==============================================================================================*/
/* [DMA_CH_DATA_ID_0] */
#define	DMA_UCFG_CHDATA0_TYPE				(DMA_DMAC0)							/* DMA_DMAC0								*/
																				/* DMA_DMAC1								*/
																				/* DMA_DTS									*/
#define	DMA_UCFG_CHDATA0_REQ				(PIL_DMAC_GR0_DMAMSPI20)			/* [DMAC] PIL_DMAC_GRn_xxx					*/
																				/* [DTS]  PIL_DTS_GRn_xxx					*/
#define	DMA_UCFG_CHDATA0_HWCH				(PIL_DMAC_CH2)						/* [DMAC] PIL_DMAC_CH0 - PIL_DMAC_CH15		*/
																				/* [DTS]  Same value as DMA_UCFG_CHDATA0_REQ*/
#define	DMA_UCFG_CHDATA0_PRILEVEL			(DMA_PRIORITY_NOUSE)				/* [DMAC] Don't Care						*/
																				/* [DTS]  DMA_PRIORITY0 - DMA_PRIORITY3		*/
#define	DMA_UCFG_CHDATA0_NOTIFICATION		(NULL_PTR)							/* Callback Pointer							*/

/* [DMA_CH_DATA_ID_1] config */
#define	DMA_UCFG_CHDATA1_TYPE				(DMA_DMAC0)							/* See DMA_UCFG_CHDATA0_TYPE			*/
#define	DMA_UCFG_CHDATA1_REQ				(PIL_DMAC_GR0_DMAMSPI21)			/* See DMA_UCFG_CHDATA0_REQ for range			*/
#define	DMA_UCFG_CHDATA1_HWCH				(PIL_DMAC_CH3)						/* See DMA_UCFG_CHDATA0_HWCH for range			*/
#define	DMA_UCFG_CHDATA1_PRILEVEL			(DMA_PRIORITY_NOUSE)				/* See DMA_UCFG_CHDATA0_PRILEVEL for range		*/
#define	DMA_UCFG_CHDATA1_NOTIFICATION		(NULL_PTR)							/* See DMA_UCFG_CHDATA0_NOTIFICATION for range	*/


/*-- End Of File -------------------------------------------------------------------------------*/
#endif /* DMA_CFG_H */
