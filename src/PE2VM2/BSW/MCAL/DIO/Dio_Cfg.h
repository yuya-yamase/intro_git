/* DIO-r04-303 */
/************************************************************************************************/
/*																								*/
/*		DIO Driver																				*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/
#ifndef DIO_CFG_H
#define DIO_CFG_H

/*==============================================================================================*/
/* defines																						*/
/*==============================================================================================*/
/*----------------------------------------------------------------------------------------------*/
/* Critical Section Macro																		*/
/*----------------------------------------------------------------------------------------------*/
#define DIO_ENTER_CRITICAL_SECTION()			/* Exclusive Start								*/
#define DIO_EXIT_CRITICAL_SECTION()				/* Exclusive End								*/

/*----------------------------------------------------------------------------------------------*/
/* API Selection																				*/
/*----------------------------------------------------------------------------------------------*/
#define DIO_FLIP_CHANNEL_API		(STD_ON)

/*----------------------------------------------------------------------------------------------*/
/* Common Config																				*/
/*----------------------------------------------------------------------------------------------*/
#define DIO_CFG_PROTECTION_CONTROL	(STD_OFF)

/*----------------------------------------------------------------------------------------------*/
/* Channel Group Array Size Setting (Max32)														*/
/*----------------------------------------------------------------------------------------------*/
#define DIO_CFG_CH_GRP_ARRAY_SIZE	(1U)

/*----------------------------------------------------------------------------------------------*/
/* Channel Group Parameters Setting																*/
/*----------------------------------------------------------------------------------------------*/
#define DIO_CFG_CH_GRP_0_MASK		DIO_CH_GRP_MASK_16_0
#define DIO_CFG_CH_GRP_0_OFFSET		DIO_OFFSET_0
#define DIO_CFG_CH_GRP_0_PORT		DIO_ID_PORT0

#define DIO_CFG_CH_GRP_1_MASK		DIO_CH_GRP_MASK_16_0
#define DIO_CFG_CH_GRP_1_OFFSET		DIO_OFFSET_0
#define DIO_CFG_CH_GRP_1_PORT		DIO_ID_PORT0

#define DIO_CFG_CH_GRP_2_MASK		DIO_CH_GRP_MASK_16_0
#define DIO_CFG_CH_GRP_2_OFFSET		DIO_OFFSET_0
#define DIO_CFG_CH_GRP_2_PORT		DIO_ID_PORT0

#define DIO_CFG_CH_GRP_3_MASK		DIO_CH_GRP_MASK_16_0
#define DIO_CFG_CH_GRP_3_OFFSET		DIO_OFFSET_0
#define DIO_CFG_CH_GRP_3_PORT		DIO_ID_PORT0

#define DIO_CFG_CH_GRP_4_MASK		DIO_CH_GRP_MASK_16_0
#define DIO_CFG_CH_GRP_4_OFFSET		DIO_OFFSET_0
#define DIO_CFG_CH_GRP_4_PORT		DIO_ID_PORT0

#define DIO_CFG_CH_GRP_5_MASK		DIO_CH_GRP_MASK_16_0
#define DIO_CFG_CH_GRP_5_OFFSET		DIO_OFFSET_0
#define DIO_CFG_CH_GRP_5_PORT		DIO_ID_PORT0

#define DIO_CFG_CH_GRP_6_MASK		DIO_CH_GRP_MASK_16_0
#define DIO_CFG_CH_GRP_6_OFFSET		DIO_OFFSET_0
#define DIO_CFG_CH_GRP_6_PORT		DIO_ID_PORT0

#define DIO_CFG_CH_GRP_7_MASK		DIO_CH_GRP_MASK_16_0
#define DIO_CFG_CH_GRP_7_OFFSET		DIO_OFFSET_0
#define DIO_CFG_CH_GRP_7_PORT		DIO_ID_PORT0

#define DIO_CFG_CH_GRP_8_MASK		DIO_CH_GRP_MASK_16_0
#define DIO_CFG_CH_GRP_8_OFFSET		DIO_OFFSET_0
#define DIO_CFG_CH_GRP_8_PORT		DIO_ID_PORT0

#define DIO_CFG_CH_GRP_9_MASK		DIO_CH_GRP_MASK_16_0
#define DIO_CFG_CH_GRP_9_OFFSET		DIO_OFFSET_0
#define DIO_CFG_CH_GRP_9_PORT		DIO_ID_PORT0

#define DIO_CFG_CH_GRP_10_MASK		DIO_CH_GRP_MASK_16_0
#define DIO_CFG_CH_GRP_10_OFFSET	DIO_OFFSET_0
#define DIO_CFG_CH_GRP_10_PORT		DIO_ID_PORT0

#define DIO_CFG_CH_GRP_11_MASK		DIO_CH_GRP_MASK_16_0
#define DIO_CFG_CH_GRP_11_OFFSET	DIO_OFFSET_0
#define DIO_CFG_CH_GRP_11_PORT		DIO_ID_PORT0

#define DIO_CFG_CH_GRP_12_MASK		DIO_CH_GRP_MASK_16_0
#define DIO_CFG_CH_GRP_12_OFFSET	DIO_OFFSET_0
#define DIO_CFG_CH_GRP_12_PORT		DIO_ID_PORT0

#define DIO_CFG_CH_GRP_13_MASK		DIO_CH_GRP_MASK_16_0
#define DIO_CFG_CH_GRP_13_OFFSET	DIO_OFFSET_0
#define DIO_CFG_CH_GRP_13_PORT		DIO_ID_PORT0

#define DIO_CFG_CH_GRP_14_MASK		DIO_CH_GRP_MASK_16_0
#define DIO_CFG_CH_GRP_14_OFFSET	DIO_OFFSET_0
#define DIO_CFG_CH_GRP_14_PORT		DIO_ID_PORT0

#define DIO_CFG_CH_GRP_15_MASK		DIO_CH_GRP_MASK_16_0
#define DIO_CFG_CH_GRP_15_OFFSET	DIO_OFFSET_0
#define DIO_CFG_CH_GRP_15_PORT		DIO_ID_PORT0

#define DIO_CFG_CH_GRP_16_MASK		DIO_CH_GRP_MASK_16_0
#define DIO_CFG_CH_GRP_16_OFFSET	DIO_OFFSET_0
#define DIO_CFG_CH_GRP_16_PORT		DIO_ID_PORT0

#define DIO_CFG_CH_GRP_17_MASK		DIO_CH_GRP_MASK_16_0
#define DIO_CFG_CH_GRP_17_OFFSET	DIO_OFFSET_0
#define DIO_CFG_CH_GRP_17_PORT		DIO_ID_PORT0

#define DIO_CFG_CH_GRP_18_MASK		DIO_CH_GRP_MASK_16_0
#define DIO_CFG_CH_GRP_18_OFFSET	DIO_OFFSET_0
#define DIO_CFG_CH_GRP_18_PORT		DIO_ID_PORT0

#define DIO_CFG_CH_GRP_19_MASK		DIO_CH_GRP_MASK_16_0
#define DIO_CFG_CH_GRP_19_OFFSET	DIO_OFFSET_0
#define DIO_CFG_CH_GRP_19_PORT		DIO_ID_PORT0

#define DIO_CFG_CH_GRP_20_MASK		DIO_CH_GRP_MASK_16_0
#define DIO_CFG_CH_GRP_20_OFFSET	DIO_OFFSET_0
#define DIO_CFG_CH_GRP_20_PORT		DIO_ID_PORT0

#define DIO_CFG_CH_GRP_21_MASK		DIO_CH_GRP_MASK_16_0
#define DIO_CFG_CH_GRP_21_OFFSET	DIO_OFFSET_0
#define DIO_CFG_CH_GRP_21_PORT		DIO_ID_PORT0

#define DIO_CFG_CH_GRP_22_MASK		DIO_CH_GRP_MASK_16_0
#define DIO_CFG_CH_GRP_22_OFFSET	DIO_OFFSET_0
#define DIO_CFG_CH_GRP_22_PORT		DIO_ID_PORT0

#define DIO_CFG_CH_GRP_23_MASK		DIO_CH_GRP_MASK_16_0
#define DIO_CFG_CH_GRP_23_OFFSET	DIO_OFFSET_0
#define DIO_CFG_CH_GRP_23_PORT		DIO_ID_PORT0

#define DIO_CFG_CH_GRP_24_MASK		DIO_CH_GRP_MASK_16_0
#define DIO_CFG_CH_GRP_24_OFFSET	DIO_OFFSET_0
#define DIO_CFG_CH_GRP_24_PORT		DIO_ID_PORT0

#define DIO_CFG_CH_GRP_25_MASK		DIO_CH_GRP_MASK_16_0
#define DIO_CFG_CH_GRP_25_OFFSET	DIO_OFFSET_0
#define DIO_CFG_CH_GRP_25_PORT		DIO_ID_PORT0

#define DIO_CFG_CH_GRP_26_MASK		DIO_CH_GRP_MASK_16_0
#define DIO_CFG_CH_GRP_26_OFFSET	DIO_OFFSET_0
#define DIO_CFG_CH_GRP_26_PORT		DIO_ID_PORT0

#define DIO_CFG_CH_GRP_27_MASK		DIO_CH_GRP_MASK_16_0
#define DIO_CFG_CH_GRP_27_OFFSET	DIO_OFFSET_0
#define DIO_CFG_CH_GRP_27_PORT		DIO_ID_PORT0

#define DIO_CFG_CH_GRP_28_MASK		DIO_CH_GRP_MASK_16_0
#define DIO_CFG_CH_GRP_28_OFFSET	DIO_OFFSET_0
#define DIO_CFG_CH_GRP_28_PORT		DIO_ID_PORT0

#define DIO_CFG_CH_GRP_29_MASK		DIO_CH_GRP_MASK_16_0
#define DIO_CFG_CH_GRP_29_OFFSET	DIO_OFFSET_0
#define DIO_CFG_CH_GRP_29_PORT		DIO_ID_PORT0

#define DIO_CFG_CH_GRP_30_MASK		DIO_CH_GRP_MASK_16_0
#define DIO_CFG_CH_GRP_30_OFFSET	DIO_OFFSET_0
#define DIO_CFG_CH_GRP_30_PORT		DIO_ID_PORT0

#define DIO_CFG_CH_GRP_31_MASK		DIO_CH_GRP_MASK_16_0
#define DIO_CFG_CH_GRP_31_OFFSET	DIO_OFFSET_0
#define DIO_CFG_CH_GRP_31_PORT		DIO_ID_PORT0

#endif /* DIO_CFG_H */
/*-- End Of File -------------------------------------------------------------------------------*/
