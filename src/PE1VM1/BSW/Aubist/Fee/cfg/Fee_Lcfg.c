/* Fee_Lcfg.c                                                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
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
    /* ID:11    */ 1U,
    /* ID:12    */ 1U,
    /* ID:13    */ 2U,
    /* ID:14    */ 2U,
    /* ID:15    */ 3U,
    /* ID:16    */ 3U,
    /* ID:17    */ 3U,
    /* ID:18    */ 4U,
    /* ID:19    */ 4U,
    /* ID:20    */ 4U,
    /* ID:21    */ 4U,
    /* ID:22    */ 4U,
    /* ID:23    */ 5U,
    /* ID:24    */ 5U,
    /* ID:25    */ 5U,
    /* ID:26    */ 5U,
    /* ID:27    */ 5U,
    /* ID:28    */ 5U,
    /* ID:29    */ 5U,
    /* ID:30    */ 5U,
    /* ID:31    */ 5U,
    /* ID:32    */ 5U,
    /* ID:33    */ 5U,
    /* ID:34    */ 5U,
    /* ID:35    */ 5U,
    /* ID:36    */ 5U,
    /* ID:37    */ 5U,
    /* ID:38    */ 5U,
    /* ID:39    */ 5U,
    /* ID:40    */ 5U,
    /* ID:41    */ 5U,
    /* ID:42    */ 5U,
    /* ID:43    */ 5U,
    /* ID:44    */ 6U,
    /* ID:45    */ 6U,
    /* ID:46    */ 6U,
    /* ID:47    */ 6U,
    /* ID:48    */ 6U,
    /* ID:49    */ 6U,
    /* ID:50    */ 6U,
    /* ID:51    */ 6U,
    /* ID:52    */ 6U,
    /* ID:53    */ 6U,
    /* ID:54    */ 6U,
    /* ID:55    */ 6U,
    /* ID:56    */ 6U,
    /* ID:57    */ 6U,
    /* ID:58    */ 6U,
    /* ID:59    */ 6U,
    /* ID:60    */ 6U,
    /* ID:61    */ 6U,
    /* ID:62    */ 6U,
    /* ID:63    */ 6U,
    /* ID:64    */ 6U,
    /* ID:65    */ 7U,
    /* ID:66    */ 7U,
    /* ID:67    */ 7U,
    /* ID:68    */ 7U,
    /* ID:69    */ 7U,
    /* ID:70    */ 7U,
    /* ID:71    */ 7U,
    /* ID:72    */ 7U,
    /* ID:73    */ 7U,
    /* ID:74    */ 7U,
    /* ID:75    */ 7U,
    /* ID:76    */ 7U,
    /* ID:77    */ 7U,
    /* ID:78    */ 7U,
    /* ID:79    */ 7U,
    /* ID:80    */ 7U,
    /* ID:81    */ 7U,
    /* ID:82    */ 7U,
    /* ID:83    */ 7U,
    /* ID:84    */ 7U,
    /* ID:85    */ 7U,
    /* ID:86    */ 4U,
    /* ID:87    */ 4U,
    /* ID:88    */ 4U,
    /* ID:89    */ 4U,

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
    /* ID:11    Area:1   Dataset:1   */ 0U,
    /* ID:12    Area:1   Dataset:1   */ 1U,
    /* ID:13    Area:2   Dataset:1   */ 0U,
    /* ID:14    Area:2   Dataset:1   */ 1U,
    /* ID:15    Area:3   Dataset:1   */ 0U,
    /* ID:16    Area:3   Dataset:1   */ 1U,
    /* ID:17    Area:3   Dataset:1   */ 2U,
    /* ID:18    Area:4   Dataset:1   */ 0U,
    /* ID:19    Area:4   Dataset:1   */ 1U,
    /* ID:20    Area:4   Dataset:1   */ 2U,
    /* ID:21    Area:4   Dataset:1   */ 3U,
    /* ID:22    Area:4   Dataset:1   */ 4U,
    /* ID:23    Area:5   Dataset:1   */ 0U,
    /* ID:24    Area:5   Dataset:1   */ 1U,
    /* ID:25    Area:5   Dataset:1   */ 2U,
    /* ID:26    Area:5   Dataset:1   */ 3U,
    /* ID:27    Area:5   Dataset:1   */ 4U,
    /* ID:28    Area:5   Dataset:1   */ 5U,
    /* ID:29    Area:5   Dataset:1   */ 6U,
    /* ID:30    Area:5   Dataset:1   */ 7U,
    /* ID:31    Area:5   Dataset:1   */ 8U,
    /* ID:32    Area:5   Dataset:1   */ 9U,
    /* ID:33    Area:5   Dataset:1   */ 10U,
    /* ID:34    Area:5   Dataset:1   */ 11U,
    /* ID:35    Area:5   Dataset:1   */ 12U,
    /* ID:36    Area:5   Dataset:1   */ 13U,
    /* ID:37    Area:5   Dataset:1   */ 14U,
    /* ID:38    Area:5   Dataset:1   */ 15U,
    /* ID:39    Area:5   Dataset:1   */ 16U,
    /* ID:40    Area:5   Dataset:1   */ 17U,
    /* ID:41    Area:5   Dataset:1   */ 18U,
    /* ID:42    Area:5   Dataset:1   */ 19U,
    /* ID:43    Area:5   Dataset:1   */ 20U,
    /* ID:44    Area:6   Dataset:1   */ 0U,
    /* ID:45    Area:6   Dataset:1   */ 1U,
    /* ID:46    Area:6   Dataset:1   */ 2U,
    /* ID:47    Area:6   Dataset:1   */ 3U,
    /* ID:48    Area:6   Dataset:1   */ 4U,
    /* ID:49    Area:6   Dataset:1   */ 5U,
    /* ID:50    Area:6   Dataset:1   */ 6U,
    /* ID:51    Area:6   Dataset:1   */ 7U,
    /* ID:52    Area:6   Dataset:1   */ 8U,
    /* ID:53    Area:6   Dataset:1   */ 9U,
    /* ID:54    Area:6   Dataset:1   */ 10U,
    /* ID:55    Area:6   Dataset:1   */ 11U,
    /* ID:56    Area:6   Dataset:1   */ 12U,
    /* ID:57    Area:6   Dataset:1   */ 13U,
    /* ID:58    Area:6   Dataset:1   */ 14U,
    /* ID:59    Area:6   Dataset:1   */ 15U,
    /* ID:60    Area:6   Dataset:1   */ 16U,
    /* ID:61    Area:6   Dataset:1   */ 17U,
    /* ID:62    Area:6   Dataset:1   */ 18U,
    /* ID:63    Area:6   Dataset:1   */ 19U,
    /* ID:64    Area:6   Dataset:1   */ 20U,
    /* ID:65    Area:7   Dataset:1   */ 0U,
    /* ID:66    Area:7   Dataset:1   */ 1U,
    /* ID:67    Area:7   Dataset:1   */ 2U,
    /* ID:68    Area:7   Dataset:1   */ 3U,
    /* ID:69    Area:7   Dataset:1   */ 4U,
    /* ID:70    Area:7   Dataset:1   */ 5U,
    /* ID:71    Area:7   Dataset:1   */ 6U,
    /* ID:72    Area:7   Dataset:1   */ 7U,
    /* ID:73    Area:7   Dataset:1   */ 8U,
    /* ID:74    Area:7   Dataset:1   */ 9U,
    /* ID:75    Area:7   Dataset:1   */ 10U,
    /* ID:76    Area:7   Dataset:1   */ 11U,
    /* ID:77    Area:7   Dataset:1   */ 12U,
    /* ID:78    Area:7   Dataset:1   */ 13U,
    /* ID:79    Area:7   Dataset:1   */ 14U,
    /* ID:80    Area:7   Dataset:1   */ 15U,
    /* ID:81    Area:7   Dataset:1   */ 16U,
    /* ID:82    Area:7   Dataset:1   */ 17U,
    /* ID:83    Area:7   Dataset:1   */ 18U,
    /* ID:84    Area:7   Dataset:1   */ 19U,
    /* ID:85    Area:7   Dataset:1   */ 20U,
    /* ID:86    Area:4   Dataset:1   */ 5U,
    /* ID:87    Area:4   Dataset:1   */ 6U,
    /* ID:88    Area:4   Dataset:1   */ 7U,
    /* ID:89    Area:4   Dataset:1   */ 8U,

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

