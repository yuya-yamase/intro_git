/* Fee_Lcfg.c                                                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name | FEE/LCFG/CODE                                              */
/*--------------------------------------------------------------------------*/
/* Notes       |                                                            */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Fee.h>
#include <Fee_Ext.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define FEE_START_SEC_CONST_CONFIG_32
#include <Fee_MemMap.h>                 /* SWS_Fee_00554 */

CONST( AB_83_ConstV uint8, FEE_CONFIG_DATA ) FeeBlockConfigurations[] = {

    /* ID:2     */ 0U,
    /* ID:3     */ 0U,
    /* ID:4     */ 0U,
    /* ID:5     */ 0U,
    /* ID:6     */ 0U,
    /* ID:7     */ 0U,
    /* ID:8     */ 0U,
    /* ID:9     */ 0U,
    /* ID:10    */ 0U,
    /* ID:11    */ 0U,
    /* ID:12    */ 0U,
    /* ID:13    */ 0U,
    /* ID:14    */ 0U,
    /* ID:15    */ 0U,
    /* ID:16    */ 0U,
    /* ID:17    */ 0U,
    /* ID:18    */ 0U,
    /* ID:19    */ 0U,
    /* ID:20    */ 0U,
    /* ID:21    */ 0U,
    /* ID:22    */ 0U,
    /* ID:23    */ 0U,
    /* ID:24    */ 0U,
    /* ID:25    */ 0U,
    /* ID:26    */ 0U,
    /* ID:27    */ 0U,
    /* ID:28    */ 0U,
    /* ID:29    */ 0U,
    /* ID:30    */ 0U,
    /* ID:31    */ 0U,
    /* ID:32    */ 0U,
    /* ID:33    */ 0U,
    /* ID:34    */ 0U,
    /* ID:35    */ 0U,
    /* ID:36    */ 0U,
    /* ID:37    */ 0U,
    /* ID:38    */ 0U,
    /* ID:39    */ 0U,
    /* ID:40    */ 0U,
    /* ID:41    */ 0U,
    /* ID:42    */ 0U,
    /* ID:43    */ 0U,
    /* ID:44    */ 0U,
    /* ID:45    */ 0U,
    /* ID:46    */ 0U,

};

CONST(AB_83_ConstV uint16, FEE_CONFIG_DATA) FeeBlockConfigurationsSize = sizeof(FeeBlockConfigurations) / sizeof(FeeBlockConfigurations[0]);

#if (FEE_RECORDPOSTBL_ENABLE == STD_ON)
CONST( AB_83_ConstV uint16, FEE_CONFIG_DATA ) FeeRecPosTblIdx[] = {

    /* ID:2     Area:0   Dataset:1   */ 0U,
    /* ID:3     Area:0   Dataset:1   */ 1U,
    /* ID:4     Area:0   Dataset:1   */ 2U,
    /* ID:5     Area:0   Dataset:1   */ 3U,
    /* ID:6     Area:0   Dataset:1   */ 4U,
    /* ID:7     Area:0   Dataset:1   */ 5U,
    /* ID:8     Area:0   Dataset:1   */ 6U,
    /* ID:9     Area:0   Dataset:1   */ 7U,
    /* ID:10    Area:0   Dataset:1   */ 8U,
    /* ID:11    Area:0   Dataset:1   */ 9U,
    /* ID:12    Area:0   Dataset:1   */ 10U,
    /* ID:13    Area:0   Dataset:1   */ 11U,
    /* ID:14    Area:0   Dataset:1   */ 12U,
    /* ID:15    Area:0   Dataset:1   */ 13U,
    /* ID:16    Area:0   Dataset:1   */ 14U,
    /* ID:17    Area:0   Dataset:1   */ 15U,
    /* ID:18    Area:0   Dataset:1   */ 16U,
    /* ID:19    Area:0   Dataset:1   */ 17U,
    /* ID:20    Area:0   Dataset:1   */ 18U,
    /* ID:21    Area:0   Dataset:1   */ 19U,
    /* ID:22    Area:0   Dataset:1   */ 20U,
    /* ID:23    Area:0   Dataset:1   */ 21U,
    /* ID:24    Area:0   Dataset:1   */ 22U,
    /* ID:25    Area:0   Dataset:1   */ 23U,
    /* ID:26    Area:0   Dataset:1   */ 24U,
    /* ID:27    Area:0   Dataset:1   */ 25U,
    /* ID:28    Area:0   Dataset:1   */ 26U,
    /* ID:29    Area:0   Dataset:1   */ 27U,
    /* ID:30    Area:0   Dataset:1   */ 28U,
    /* ID:31    Area:0   Dataset:1   */ 29U,
    /* ID:32    Area:0   Dataset:1   */ 30U,
    /* ID:33    Area:0   Dataset:1   */ 31U,
    /* ID:34    Area:0   Dataset:1   */ 32U,
    /* ID:35    Area:0   Dataset:1   */ 33U,
    /* ID:36    Area:0   Dataset:1   */ 34U,
    /* ID:37    Area:0   Dataset:1   */ 35U,
    /* ID:38    Area:0   Dataset:1   */ 36U,
    /* ID:39    Area:0   Dataset:1   */ 37U,
    /* ID:40    Area:0   Dataset:1   */ 38U,
    /* ID:41    Area:0   Dataset:1   */ 39U,
    /* ID:42    Area:0   Dataset:1   */ 40U,
    /* ID:43    Area:0   Dataset:1   */ 41U,
    /* ID:44    Area:0   Dataset:1   */ 42U,
    /* ID:45    Area:0   Dataset:1   */ 43U,
    /* ID:46    Area:0   Dataset:1   */ 44U,

};

CONST(AB_83_ConstV uint16, FEE_CONFIG_DATA) FeeRecPosTblIdxSize = sizeof(FeeRecPosTblIdx) / sizeof(FeeRecPosTblIdx[0]);
#endif /* FEE_RECORDPOSTBL_ENABLE == STD_ON */

#define FEE_STOP_SEC_CONST_CONFIG_32
#include <Fee_MemMap.h>                 /* SWS_Fee_00554 */

/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

