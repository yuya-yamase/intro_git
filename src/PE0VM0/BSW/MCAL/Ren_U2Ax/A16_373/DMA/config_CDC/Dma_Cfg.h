/* Copyright  : DENSO CORPORATION */
#ifndef DMA_CFG_H
#define DMA_CFG_H

/*==============================================================================================*/
/*	include files																				*/
/*==============================================================================================*/

/*==============================================================================================*/
/*	DMA common configuration																	*/
/*==============================================================================================*/
/* Total number of channels using Dma */
#define	DMA_UCFG_CHDATA_NUM				(0u)

/* Uninterruptible/Uninterruptible */
#define DMA_ENTER_CRITICAL_SECTION()											/* Do not interrupt */
#define DMA_EXIT_CRITICAL_SECTION()												/* Allow interrupts */

/* Register Check */
#define	DMA_CFG_REG_CHK						(STD_OFF)
#define DMA_CFG_REG_REFRESH					(STD_OFF)

/* DMATRGSEL DTS,DMA Access */
#define DMA_CFG_GLOBAL_REG_CONTROL			(STD_ON)
#define DMA_CFG_DMA0_ACCESS					(STD_ON)
#define DMA_CFG_DMA1_ACCESS					(STD_OFF)

/*==============================================================================================*/
/*	Configuration per DMA channel ID															*/
/*==============================================================================================*/


/*-- End Of File -------------------------------------------------------------------------------*/
#endif /* DMA_CFG_H */
