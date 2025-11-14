/* Fee_Ccd_Lcfg.c v2-0-0                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/CCD/LCFG/CODE                                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

#include <Fee.h>
#include "Fee_Cfg_Internal_Ext.h"
#include "../inc/Fee_ExConst.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

#if (FEE_RECORDPOSTBL_ENABLE == STD_ON) 
#define FEE_CCD_LCFG_DATASET_INDEX_MASK_VAL ((uint16)( (uint16)1U << (uint16)FEE_DATASET_SELECTION_BITS ) - (uint16)1U )
#endif /* FEE_RECORDPOSTBL_ENABLE == STD_ON */ 

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#define FEE_START_SEC_CONST_CONFIG_32
#include <Fee_MemMap.h>

CONST( AB_83_ConstV uint8,  FEE_CONFIG_DATA ) Fee_DatasetSelectionBits = FEE_DATASET_SELECTION_BITS;
CONST( AB_83_ConstV uint16, FEE_CONFIG_DATA ) Fee_MaxCalcCheckSumBytes = FEE_MAX_CALC_CHECKSUM_BYTES;
CONST( AB_83_ConstV uint8,  FEE_CONFIG_DATA ) Fee_IntentRebuildEnable = FEE_INTENT_RBLD_ENABLE;

#if (FEE_RECORDPOSTBL_ENABLE == STD_ON) 
CONST( AB_83_ConstV uint16, FEE_CONFIG_DATA ) Fee_DatasetIndexMask = FEE_CCD_LCFG_DATASET_INDEX_MASK_VAL;
#endif /* FEE_RECORDPOSTBL_ENABLE == STD_ON */ 

#define FEE_STOP_SEC_CONST_CONFIG_32
#include <Fee_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

#if (FEE_RECORDPOSTBL_ENABLE == STD_ON)

#define FEE_START_SEC_VAR_NO_INIT_32
#include <Fee_MemMap.h>
VAR(uint8, FEE_VAR_NO_INIT) Fee_RecordPosTBLValidFlag[FEE_AREA_NUM];
#define FEE_STOP_SEC_VAR_NO_INIT_32
#include <Fee_MemMap.h>

#define FEE_START_SEC_CONST_CONFIG_32
#include <Fee_MemMap.h>
CONST(AB_83_ConstV uint8, FEE_CONFIG_DATA) Fee_RecordPosTBLValidFlagSize = (uint8)(sizeof(Fee_RecordPosTBLValidFlag) / sizeof(Fee_RecordPosTBLValidFlag[0]));
#define FEE_STOP_SEC_CONST_CONFIG_32
#include <Fee_MemMap.h>


#define FEE_START_SEC_VAR_NO_INIT_32
#include <Fee_MemMap.h>
VAR(uint8, FEE_VAR_NO_INIT) Fee_RecordPosTBLValidFlagMrr[FEE_AREA_NUM];
#define FEE_STOP_SEC_VAR_NO_INIT_32
#include <Fee_MemMap.h>

#define FEE_START_SEC_CONST_CONFIG_32
#include <Fee_MemMap.h>
CONST(AB_83_ConstV uint8, FEE_CONFIG_DATA) Fee_RecordPosTBLValidFlagMrrSize = (uint8)(sizeof(Fee_RecordPosTBLValidFlagMrr) / sizeof(Fee_RecordPosTBLValidFlagMrr[0]));
#define FEE_STOP_SEC_CONST_CONFIG_32
#include <Fee_MemMap.h>

#endif /* FEE_RECORDPOSTBL_ENABLE == STD_ON */


#define FEE_START_SEC_VAR_NO_INIT_32
#include <Fee_MemMap.h>
VAR(Fee_LwpInfType, FEE_VAR_NO_INIT) Fee_LastWPosInfo1[FEE_AREA_NUM];
#define FEE_STOP_SEC_VAR_NO_INIT_32
#include <Fee_MemMap.h>

#define FEE_START_SEC_CONST_CONFIG_32
#include <Fee_MemMap.h>
CONST(AB_83_ConstV uint32, FEE_CONFIG_DATA) Fee_LastWPosInfo1Size = (uint32)(sizeof(Fee_LastWPosInfo1) / sizeof(Fee_LastWPosInfo1[0]));
#define FEE_STOP_SEC_CONST_CONFIG_32
#include <Fee_MemMap.h>


#define FEE_START_SEC_VAR_NO_INIT_32
#include <Fee_MemMap.h>
VAR(Fee_LwpInfType, FEE_VAR_NO_INIT) Fee_LastWPosInfo2[FEE_AREA_NUM];
#define FEE_STOP_SEC_VAR_NO_INIT_32
#include <Fee_MemMap.h>

#define FEE_START_SEC_CONST_CONFIG_32
#include <Fee_MemMap.h>
CONST(AB_83_ConstV uint32, FEE_CONFIG_DATA) Fee_LastWPosInfo2Size = (uint32)(sizeof(Fee_LastWPosInfo2) / sizeof(Fee_LastWPosInfo2[0]));
#define FEE_STOP_SEC_CONST_CONFIG_32
#include <Fee_MemMap.h>

#define FEE_START_SEC_VAR_NO_INIT_32
#include <Fee_MemMap.h>
VAR(Fee_UseBlockType, FEE_VAR_NO_INIT) Fee_UseBlockInfo[FEE_SCTR_NUM_TOTAL];
#define FEE_STOP_SEC_VAR_NO_INIT_32
#include <Fee_MemMap.h>

#define FEE_START_SEC_CONST_CONFIG_32
#include <Fee_MemMap.h>
CONST(AB_83_ConstV uint32, FEE_CONFIG_DATA) Fee_UseBlockInfoSize = (uint32)(sizeof(Fee_UseBlockInfo) / sizeof(Fee_UseBlockInfo[0]));
#define FEE_STOP_SEC_CONST_CONFIG_32
#include <Fee_MemMap.h>

#if ( FEE_USE_REDUNDANCY_RAM == STD_ON )
#define FEE_START_SEC_VAR_NO_INIT_32
#include <Fee_MemMap.h>
VAR(Fee_UseBlockType, FEE_VAR_NO_INIT) Fee_UseBlockInfoSub[FEE_SCTR_NUM_TOTAL];
#define FEE_STOP_SEC_VAR_NO_INIT_32
#include <Fee_MemMap.h>

#define FEE_START_SEC_CONST_CONFIG_32
#include <Fee_MemMap.h>
CONST(AB_83_ConstV uint32, FEE_CONFIG_DATA) Fee_UseBlockInfoSubSize = (uint32)(sizeof(Fee_UseBlockInfoSub) / sizeof(Fee_UseBlockInfoSub[0]));
#define FEE_STOP_SEC_CONST_CONFIG_32
#include <Fee_MemMap.h>
#endif /* FEE_USE_REDUNDANCY_RAM == STD_ON */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/*  1-1-0          :2019/07/03                                              */
/*  2-0-0          :2022/08/24                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
