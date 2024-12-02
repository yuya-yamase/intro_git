/* DIO-r04-303 */
/************************************************************************************************/
/*																								*/
/*		DIO Driver																				*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

/*==============================================================================================*/
/* include files																				*/
/*==============================================================================================*/
#include "Mcal_SpalCmn.h"

#include "Dio.h"

/*==============================================================================================*/
/* constants																					*/
/*==============================================================================================*/
#define DIO_START_SEC_CONST_UNSPECIFIED
#include "Dio_MemMap.h"

CONST(Dio_ChannelGroupType, DIO_CONST) cstDio_ChannelGroupArray[DIO_CFG_CH_GRP_ARRAY_SIZE] = {
	 {DIO_CFG_CH_GRP_0_MASK, DIO_CFG_CH_GRP_0_OFFSET, DIO_CFG_CH_GRP_0_PORT}
#if ( DIO_CFG_CH_GRP_ARRAY_SIZE > 1U )
	,{DIO_CFG_CH_GRP_1_MASK, DIO_CFG_CH_GRP_1_OFFSET, DIO_CFG_CH_GRP_1_PORT}
#endif /* ( DIO_CFG_CH_GRP_ARRAY_SIZE > 1U ) */
#if ( DIO_CFG_CH_GRP_ARRAY_SIZE > 2U )
	,{DIO_CFG_CH_GRP_2_MASK, DIO_CFG_CH_GRP_2_OFFSET, DIO_CFG_CH_GRP_2_PORT}
#endif /* ( DIO_CFG_CH_GRP_ARRAY_SIZE > 2U ) */
#if ( DIO_CFG_CH_GRP_ARRAY_SIZE > 3U )
	,{DIO_CFG_CH_GRP_3_MASK, DIO_CFG_CH_GRP_3_OFFSET, DIO_CFG_CH_GRP_3_PORT}
#endif /* ( DIO_CFG_CH_GRP_ARRAY_SIZE > 3U ) */
#if ( DIO_CFG_CH_GRP_ARRAY_SIZE > 4U )
	,{DIO_CFG_CH_GRP_4_MASK, DIO_CFG_CH_GRP_4_OFFSET, DIO_CFG_CH_GRP_4_PORT}
#endif /* ( DIO_CFG_CH_GRP_ARRAY_SIZE > 4U ) */
#if ( DIO_CFG_CH_GRP_ARRAY_SIZE > 5U )
	,{DIO_CFG_CH_GRP_5_MASK, DIO_CFG_CH_GRP_5_OFFSET, DIO_CFG_CH_GRP_5_PORT}
#endif /* ( DIO_CFG_CH_GRP_ARRAY_SIZE > 5U ) */
#if ( DIO_CFG_CH_GRP_ARRAY_SIZE > 6U )
	,{DIO_CFG_CH_GRP_6_MASK, DIO_CFG_CH_GRP_6_OFFSET, DIO_CFG_CH_GRP_6_PORT}
#endif /* ( DIO_CFG_CH_GRP_ARRAY_SIZE > 6U ) */
#if ( DIO_CFG_CH_GRP_ARRAY_SIZE > 7U )
	,{DIO_CFG_CH_GRP_7_MASK, DIO_CFG_CH_GRP_7_OFFSET, DIO_CFG_CH_GRP_7_PORT}
#endif /* ( DIO_CFG_CH_GRP_ARRAY_SIZE > 7U ) */
#if ( DIO_CFG_CH_GRP_ARRAY_SIZE > 8U )
	,{DIO_CFG_CH_GRP_8_MASK, DIO_CFG_CH_GRP_8_OFFSET, DIO_CFG_CH_GRP_8_PORT}
#endif /* ( DIO_CFG_CH_GRP_ARRAY_SIZE > 8U ) */
#if ( DIO_CFG_CH_GRP_ARRAY_SIZE > 9U )
	,{DIO_CFG_CH_GRP_9_MASK, DIO_CFG_CH_GRP_9_OFFSET, DIO_CFG_CH_GRP_9_PORT}
#endif /* ( DIO_CFG_CH_GRP_ARRAY_SIZE > 9U ) */
#if ( DIO_CFG_CH_GRP_ARRAY_SIZE > 10U )
	,{DIO_CFG_CH_GRP_10_MASK, DIO_CFG_CH_GRP_10_OFFSET, DIO_CFG_CH_GRP_10_PORT}
#endif /* ( DIO_CFG_CH_GRP_ARRAY_SIZE > 10U ) */
#if ( DIO_CFG_CH_GRP_ARRAY_SIZE > 11U )
	,{DIO_CFG_CH_GRP_11_MASK, DIO_CFG_CH_GRP_11_OFFSET, DIO_CFG_CH_GRP_11_PORT}
#endif /* ( DIO_CFG_CH_GRP_ARRAY_SIZE > 11U ) */
#if ( DIO_CFG_CH_GRP_ARRAY_SIZE > 12U )
	,{DIO_CFG_CH_GRP_12_MASK, DIO_CFG_CH_GRP_12_OFFSET, DIO_CFG_CH_GRP_12_PORT}
#endif /* ( DIO_CFG_CH_GRP_ARRAY_SIZE > 12U ) */
#if ( DIO_CFG_CH_GRP_ARRAY_SIZE > 13U )
	,{DIO_CFG_CH_GRP_13_MASK, DIO_CFG_CH_GRP_13_OFFSET, DIO_CFG_CH_GRP_13_PORT}
#endif /* ( DIO_CFG_CH_GRP_ARRAY_SIZE > 13U ) */
#if ( DIO_CFG_CH_GRP_ARRAY_SIZE > 14U )
	,{DIO_CFG_CH_GRP_14_MASK, DIO_CFG_CH_GRP_14_OFFSET, DIO_CFG_CH_GRP_14_PORT}
#endif /* ( DIO_CFG_CH_GRP_ARRAY_SIZE > 14U ) */
#if ( DIO_CFG_CH_GRP_ARRAY_SIZE > 15U )
	,{DIO_CFG_CH_GRP_15_MASK, DIO_CFG_CH_GRP_15_OFFSET, DIO_CFG_CH_GRP_15_PORT}
#endif /* ( DIO_CFG_CH_GRP_ARRAY_SIZE > 15U ) */
#if ( DIO_CFG_CH_GRP_ARRAY_SIZE > 16U )
	,{DIO_CFG_CH_GRP_16_MASK, DIO_CFG_CH_GRP_16_OFFSET, DIO_CFG_CH_GRP_16_PORT}
#endif /* ( DIO_CFG_CH_GRP_ARRAY_SIZE > 16U ) */
#if ( DIO_CFG_CH_GRP_ARRAY_SIZE > 17U )
	,{DIO_CFG_CH_GRP_17_MASK, DIO_CFG_CH_GRP_17_OFFSET, DIO_CFG_CH_GRP_17_PORT}
#endif /* ( DIO_CFG_CH_GRP_ARRAY_SIZE > 17U ) */
#if ( DIO_CFG_CH_GRP_ARRAY_SIZE > 18U )
	,{DIO_CFG_CH_GRP_18_MASK, DIO_CFG_CH_GRP_18_OFFSET, DIO_CFG_CH_GRP_18_PORT}
#endif /* ( DIO_CFG_CH_GRP_ARRAY_SIZE > 18U ) */
#if ( DIO_CFG_CH_GRP_ARRAY_SIZE > 19U )
	,{DIO_CFG_CH_GRP_19_MASK, DIO_CFG_CH_GRP_19_OFFSET, DIO_CFG_CH_GRP_19_PORT}
#endif /* ( DIO_CFG_CH_GRP_ARRAY_SIZE > 19U ) */
#if ( DIO_CFG_CH_GRP_ARRAY_SIZE > 20U )
	,{DIO_CFG_CH_GRP_20_MASK, DIO_CFG_CH_GRP_20_OFFSET, DIO_CFG_CH_GRP_20_PORT}
#endif /* ( DIO_CFG_CH_GRP_ARRAY_SIZE > 20U ) */
#if ( DIO_CFG_CH_GRP_ARRAY_SIZE > 21U )
	,{DIO_CFG_CH_GRP_21_MASK, DIO_CFG_CH_GRP_21_OFFSET, DIO_CFG_CH_GRP_21_PORT}
#endif /* ( DIO_CFG_CH_GRP_ARRAY_SIZE > 21U ) */
#if ( DIO_CFG_CH_GRP_ARRAY_SIZE > 22U )
	,{DIO_CFG_CH_GRP_22_MASK, DIO_CFG_CH_GRP_22_OFFSET, DIO_CFG_CH_GRP_22_PORT}
#endif /* ( DIO_CFG_CH_GRP_ARRAY_SIZE > 22U ) */
#if ( DIO_CFG_CH_GRP_ARRAY_SIZE > 23U )
	,{DIO_CFG_CH_GRP_23_MASK, DIO_CFG_CH_GRP_23_OFFSET, DIO_CFG_CH_GRP_23_PORT}
#endif /* ( DIO_CFG_CH_GRP_ARRAY_SIZE > 23U ) */
#if ( DIO_CFG_CH_GRP_ARRAY_SIZE > 24U )
	,{DIO_CFG_CH_GRP_24_MASK, DIO_CFG_CH_GRP_24_OFFSET, DIO_CFG_CH_GRP_24_PORT}
#endif /* ( DIO_CFG_CH_GRP_ARRAY_SIZE > 24U ) */
#if ( DIO_CFG_CH_GRP_ARRAY_SIZE > 25U )
	,{DIO_CFG_CH_GRP_25_MASK, DIO_CFG_CH_GRP_25_OFFSET, DIO_CFG_CH_GRP_25_PORT}
#endif /* ( DIO_CFG_CH_GRP_ARRAY_SIZE > 25U ) */
#if ( DIO_CFG_CH_GRP_ARRAY_SIZE > 26U )
	,{DIO_CFG_CH_GRP_26_MASK, DIO_CFG_CH_GRP_26_OFFSET, DIO_CFG_CH_GRP_26_PORT}
#endif /* ( DIO_CFG_CH_GRP_ARRAY_SIZE > 26U ) */
#if ( DIO_CFG_CH_GRP_ARRAY_SIZE > 27U )
	,{DIO_CFG_CH_GRP_27_MASK, DIO_CFG_CH_GRP_27_OFFSET, DIO_CFG_CH_GRP_27_PORT}
#endif /* ( DIO_CFG_CH_GRP_ARRAY_SIZE > 27U ) */
#if ( DIO_CFG_CH_GRP_ARRAY_SIZE > 28U )
	,{DIO_CFG_CH_GRP_28_MASK, DIO_CFG_CH_GRP_28_OFFSET, DIO_CFG_CH_GRP_28_PORT}
#endif /* ( DIO_CFG_CH_GRP_ARRAY_SIZE > 28U ) */
#if ( DIO_CFG_CH_GRP_ARRAY_SIZE > 29U )
	,{DIO_CFG_CH_GRP_29_MASK, DIO_CFG_CH_GRP_29_OFFSET, DIO_CFG_CH_GRP_29_PORT}
#endif /* ( DIO_CFG_CH_GRP_ARRAY_SIZE > 29U ) */
#if ( DIO_CFG_CH_GRP_ARRAY_SIZE > 30U )
	,{DIO_CFG_CH_GRP_30_MASK, DIO_CFG_CH_GRP_30_OFFSET, DIO_CFG_CH_GRP_30_PORT}
#endif /* ( DIO_CFG_CH_GRP_ARRAY_SIZE > 30U ) */
#if ( DIO_CFG_CH_GRP_ARRAY_SIZE > 31U )
	,{DIO_CFG_CH_GRP_31_MASK, DIO_CFG_CH_GRP_31_OFFSET, DIO_CFG_CH_GRP_31_PORT}
#endif /* ( DIO_CFG_CH_GRP_ARRAY_SIZE > 31U ) */
};

#define DIO_STOP_SEC_CONST_UNSPECIFIED
#include "Dio_MemMap.h"
/*-- End Of File -------------------------------------------------------------------------------*/
