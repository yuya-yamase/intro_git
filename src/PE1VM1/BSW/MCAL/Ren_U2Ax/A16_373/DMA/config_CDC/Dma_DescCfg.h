/* Dma-rA4-3000-0100-a-v01 */
/************************************************************************************************/
/*																								*/
/*		MCAL DMA Desc Driver																	*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

#ifndef DMA_DESCCFG_H
#define DMA_DESCCFG_H

/*==============================================================================================*/
/*	include files																				*/
/*==============================================================================================*/

/*==============================================================================================*/
/*	defines / data types / structs / unions	/ macros											*/
/*==============================================================================================*/
/* Warning Chime */
/* PWM slave  for signal "SG02"                 */
#define u2_DMAC_DESC_PTR_BUZ_S1_0      (u2_DMAC_DESC_RAM_ADDR_0_6)
#define u2_DMAC_DESC_PTR_BUZ_S1_1      (u2_DMAC_DESC_RAM_ADDR_0_6 + u2_DMAC_DESC_RAM_DBR_OFFSET)

/* PWM slave  for signal "SG03"                 */
#define u2_DMAC_DESC_PTR_BUZ_S2_0      (u2_DMAC_DESC_RAM_ADDR_0_7)
#define u2_DMAC_DESC_PTR_BUZ_S2_1      (u2_DMAC_DESC_RAM_ADDR_0_7 + u2_DMAC_DESC_RAM_DBR_OFFSET)

/* PWM master for signal "SG02" and "SG03"      */
#define u2_DMAC_DESC_PTR_BUZ_M_0       (u2_DMAC_DESC_RAM_ADDR_0_8)
#define u2_DMAC_DESC_PTR_BUZ_M_1       (u2_DMAC_DESC_RAM_ADDR_0_8 + u2_DMAC_DESC_RAM_DBR_OFFSET)

#endif /* DMA_DESCCFG_H */
/*-- End Of File -------------------------------------------------------*/
