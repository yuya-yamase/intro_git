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

