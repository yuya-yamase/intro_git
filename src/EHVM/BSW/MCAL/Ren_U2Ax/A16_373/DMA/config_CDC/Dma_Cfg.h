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
#define	DMA_UCFG_CHDATA_NUM				(10u)

/* Uninterruptible/Uninterruptible */
#define DMA_ENTER_CRITICAL_SECTION()			SuspendAllInterrupts()							/* Do not interrupt */
#define DMA_EXIT_CRITICAL_SECTION()				ResumeAllInterrupts()							/* Allow interrupts */

/* Register Check */
#define	DMA_CFG_REG_CHK						(STD_OFF)
#define DMA_CFG_REG_REFRESH					(STD_OFF)

/* DMATRGSEL DTS,DMA Access */
#define DMA_CFG_GLOBAL_REG_CONTROL			(STD_ON)
#define DMA_CFG_DMA0_ACCESS					(STD_ON)
#define DMA_CFG_DMA1_ACCESS					(STD_ON)

/*==============================================================================================*/
/*	Configuration per DMA channel ID															*/
/*==============================================================================================*/
/* [DMA_CH_DATA_ID_0] */
#define	DMA_UCFG_CHDATA0_TYPE				(DMA_DMAC0)							/* DMA_DMAC0								*/
																				/* DMA_DMAC1								*/
																				/* DMA_DTS									*/
#define	DMA_UCFG_CHDATA0_REQ				(PIL_DMAC_GR0_DMAMSPI16)			/* [DMAC] PIL_DMAC_GRn_xxx					*/
																				/* [DTS]  PIL_DTS_GRn_xxx					*/
#define	DMA_UCFG_CHDATA0_HWCH				(PIL_DMAC_CH0)						/* [DMAC] PIL_DMAC_CH0 - PIL_DMAC_CH15		*/
																				/* [DTS]  Same value as DMA_UCFG_CHDATA0_REQ*/
#define	DMA_UCFG_CHDATA0_PRILEVEL			(DMA_PRIORITY_NOUSE)				/* [DMAC] Don't Care						*/
																				/* [DTS]  DMA_PRIORITY0 - DMA_PRIORITY3		*/
#define	DMA_UCFG_CHDATA0_NOTIFICATION		(NULL_PTR)							/* Callback Pointer							*/

/* [DMA_CH_DATA_ID_1] config */
#define	DMA_UCFG_CHDATA1_TYPE				(DMA_DMAC0)							/* See DMA_UCFG_CHDATA0_TYPE			*/
#define	DMA_UCFG_CHDATA1_REQ				(PIL_DMAC_GR0_DMAMSPI17)			/* See DMA_UCFG_CHDATA0_REQ for range			*/
#define	DMA_UCFG_CHDATA1_HWCH				(PIL_DMAC_CH1)						/* See DMA_UCFG_CHDATA0_HWCH for range			*/
#define	DMA_UCFG_CHDATA1_PRILEVEL			(DMA_PRIORITY_NOUSE)				/* See DMA_UCFG_CHDATA0_PRILEVEL for range		*/
#define	DMA_UCFG_CHDATA1_NOTIFICATION		(NULL_PTR)							/* See DMA_UCFG_CHDATA0_NOTIFICATION for range	*/

/* [DMA_CH_DATA_ID_2] config */
#define	DMA_UCFG_CHDATA2_TYPE				(DMA_DMAC0)							/* See DMA_UCFG_CHDATA0_TYPE			*/
#define	DMA_UCFG_CHDATA2_REQ				(PIL_DMAC_GR0_DMAMSPI20)			/* See DMA_UCFG_CHDATA0_REQ for range			*/
#define	DMA_UCFG_CHDATA2_HWCH				(PIL_DMAC_CH2)						/* See DMA_UCFG_CHDATA0_HWCH for range			*/
#define	DMA_UCFG_CHDATA2_PRILEVEL			(DMA_PRIORITY_NOUSE)				/* See DMA_UCFG_CHDATA0_PRILEVEL for range		*/
#define	DMA_UCFG_CHDATA2_NOTIFICATION		(NULL_PTR)							/* See DMA_UCFG_CHDATA0_NOTIFICATION for range	*/

/* [DMA_CH_DATA_ID_3] config */
#define	DMA_UCFG_CHDATA3_TYPE				(DMA_DMAC0)							/* See DMA_UCFG_CHDATA0_TYPE			*/
#define	DMA_UCFG_CHDATA3_REQ				(PIL_DMAC_GR0_DMAMSPI21)			/* See DMA_UCFG_CHDATA0_REQ for range			*/
#define	DMA_UCFG_CHDATA3_HWCH				(PIL_DMAC_CH3)						/* See DMA_UCFG_CHDATA0_HWCH for range			*/
#define	DMA_UCFG_CHDATA3_PRILEVEL			(DMA_PRIORITY_NOUSE)				/* See DMA_UCFG_CHDATA0_PRILEVEL for range		*/
#define	DMA_UCFG_CHDATA3_NOTIFICATION		(NULL_PTR)							/* See DMA_UCFG_CHDATA0_NOTIFICATION for range	*/

/* [DMA_CH_DATA_ID_4] config */
#define	DMA_UCFG_CHDATA4_TYPE				(DMA_DMAC0)							/* See DMA_UCFG_CHDATA0_TYPE			*/
#define	DMA_UCFG_CHDATA4_REQ				(PIL_DMAC_GR0_DMAMSPI24)			/* See DMA_UCFG_CHDATA0_REQ for range			*/
#define	DMA_UCFG_CHDATA4_HWCH				(PIL_DMAC_CH4)						/* See DMA_UCFG_CHDATA0_HWCH for range			*/
#define	DMA_UCFG_CHDATA4_PRILEVEL			(DMA_PRIORITY_NOUSE)				/* See DMA_UCFG_CHDATA0_PRILEVEL for range		*/
#define	DMA_UCFG_CHDATA4_NOTIFICATION		(NULL_PTR)							/* See DMA_UCFG_CHDATA0_NOTIFICATION for range	*/

/* [DMA_CH_DATA_ID_5] config */
#define	DMA_UCFG_CHDATA5_TYPE				(DMA_DMAC0)							/* See DMA_UCFG_CHDATA0_TYPE			*/
#define	DMA_UCFG_CHDATA5_REQ				(PIL_DMAC_GR0_DMAMSPI25)			/* See DMA_UCFG_CHDATA0_REQ for range			*/
#define	DMA_UCFG_CHDATA5_HWCH				(PIL_DMAC_CH5)						/* See DMA_UCFG_CHDATA0_HWCH for range			*/
#define	DMA_UCFG_CHDATA5_PRILEVEL			(DMA_PRIORITY_NOUSE)				/* See DMA_UCFG_CHDATA0_PRILEVEL for range		*/
#define	DMA_UCFG_CHDATA5_NOTIFICATION		(NULL_PTR)							/* See DMA_UCFG_CHDATA0_NOTIFICATION for range	*/

/* [DMA_CH_DATA_ID_6] config */
#warning "BEVCDCFD-2393"
#if 0 /* BEVCDCFD-2393 */
#else /* BEVCDCFD-2393 */
#define	DMA_UCFG_CHDATA6_TYPE				(DMA_DMAC1)							/* See DMA_UCFG_CHDATA0_TYPE			*/
#define	DMA_UCFG_CHDATA6_REQ				(PIL_DMAC_GR0_INTTAUD1I0)			/* See DMA_UCFG_CHDATA0_REQ for range			*/
#define	DMA_UCFG_CHDATA6_HWCH				(PIL_DMAC_CH0)						/* See DMA_UCFG_CHDATA0_HWCH for range			*/
#define	DMA_UCFG_CHDATA6_PRILEVEL			(DMA_PRIORITY_NOUSE)				/* See DMA_UCFG_CHDATA0_PRILEVEL for range		*/
#define	DMA_UCFG_CHDATA6_NOTIFICATION		(NULL_PTR)							/* See DMA_UCFG_CHDATA0_NOTIFICATION for range	*/
#endif /* BEVCDCFD-2393 */

/* [DMA_CH_DATA_ID_7] config */
#define	DMA_UCFG_CHDATA7_TYPE				(DMA_DMAC0)							/* See DMA_UCFG_CHDATA0_TYPE			*/
#define	DMA_UCFG_CHDATA7_REQ				(PIL_DMAC_GR0_INTTAUD1I0)			/* See DMA_UCFG_CHDATA0_REQ for range			*/
#define	DMA_UCFG_CHDATA7_HWCH				(PIL_DMAC_CH6)						/* See DMA_UCFG_CHDATA0_HWCH for range			*/
#define	DMA_UCFG_CHDATA7_PRILEVEL			(DMA_PRIORITY_NOUSE)				/* See DMA_UCFG_CHDATA0_PRILEVEL for range		*/
#define	DMA_UCFG_CHDATA7_NOTIFICATION		(NULL_PTR)							/* See DMA_UCFG_CHDATA0_NOTIFICATION for range	*/

/* [DMA_CH_DATA_ID_8] config */
#define	DMA_UCFG_CHDATA8_TYPE				(DMA_DMAC0)							/* See DMA_UCFG_CHDATA0_TYPE			*/
#define	DMA_UCFG_CHDATA8_REQ				(PIL_DMAC_GR0_INTTAUD1I0)			/* See DMA_UCFG_CHDATA0_REQ for range			*/
#define	DMA_UCFG_CHDATA8_HWCH				(PIL_DMAC_CH7)						/* See DMA_UCFG_CHDATA0_HWCH for range			*/
#define	DMA_UCFG_CHDATA8_PRILEVEL			(DMA_PRIORITY_NOUSE)				/* See DMA_UCFG_CHDATA0_PRILEVEL for range		*/
#define	DMA_UCFG_CHDATA8_NOTIFICATION		(NULL_PTR)							/* See DMA_UCFG_CHDATA0_NOTIFICATION for range	*/

/* [DMA_CH_DATA_ID_9] config */
#define	DMA_UCFG_CHDATA9_TYPE				(DMA_DMAC0)							/* See DMA_UCFG_CHDATA0_TYPE			*/
#define	DMA_UCFG_CHDATA9_REQ				(PIL_DMAC_GR0_INTTAUD1I0)			/* See DMA_UCFG_CHDATA0_REQ for range			*/
#define	DMA_UCFG_CHDATA9_HWCH				(PIL_DMAC_CH8)						/* See DMA_UCFG_CHDATA0_HWCH for range			*/
#define	DMA_UCFG_CHDATA9_PRILEVEL			(DMA_PRIORITY_NOUSE)				/* See DMA_UCFG_CHDATA0_PRILEVEL for range		*/
#define	DMA_UCFG_CHDATA9_NOTIFICATION		(NULL_PTR)							/* See DMA_UCFG_CHDATA0_NOTIFICATION for range	*/


/*-- End Of File -------------------------------------------------------------------------------*/
#endif /* DMA_CFG_H */
