/* Dcm_Dsp_StorageMng_Cfg_c(v5-3-0)                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_StorageMng_Cfg/CODE                               */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../../Dsp/cfg/Dcm_Dsp_StorageMng_Cfg.h"
#include <Dcm/Dcm_Dsp_SID86.h>
#include <Dcm.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

#define DCM_STOP_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>
CONST( AB_83_ConstV Dcm_Dsp_StorageMng_FuncListType, DCM_CONFIG_DATA ) Dcm_Dsp_StorageMng_stFuncList[ DCM_DSP_STORAGEMNG_FUNC_NUM ] =
{
    {
        &Dcm_Dsp_SID86_ReadConfirmation,
        &Dcm_Dsp_SID86_SetDataStorage2Mirror,
        &Dcm_Dsp_SID86_SetDataMirror2Storage
    },
    {
        NULL_PTR,
        NULL_PTR,
        NULL_PTR
    }
};

CONST( AB_83_ConstV Dcm_Dsp_StorageMng_BlockListType, DCM_CONFIG_DATA ) Dcm_Dsp_StorageMng_stBlockList[ DCM_P_STORAGE_BLOCKID_TBL ] =
{
    { (uint16)0x0001U, DCM_DSP_STORAGEMNG_FUNC_SID86  },
    { (uint16)0x0000U, (uint8)0x00U }
};

CONST( AB_83_ConstV uint32, DCM_CONFIG_DATA ) Dcm_Dsp_StorageMng_u4ReadAllFsTime = 4294967286UL;
CONST( AB_83_ConstV uint32, DCM_CONFIG_DATA ) Dcm_Dsp_StorageMng_u4SingleBlockFsTime = 4294967286UL;
CONST( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_Dsp_StorageMng_u2BlockId_Num = DCM_P_STORAGE_BLOCKID_NUM;
CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_Dsp_StorageMng_u1FuncList_Num = DCM_DSP_STORAGEMNG_FUNC_NUM;
CONST( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_Dsp_StorageMng_u2Queue_Max = (uint16)(DCM_P_STORAGE_BLOCKID_NUM + (uint16)1U);
CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_Dsp_StorageMng_u1GetErrRetry_Max = DCM_DSP_STORAGEMNG_GETERRRETRYMAX;
CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_Dsp_StorageMng_u1WriteRetry_Max = DCM_DSP_STORAGEMNG_WRITERETRYMAX;
CONST( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_Dsp_StorageMng_u2IdNum_PerCycle = DCM_DSP_STORAGE_BLOCKID_MAXNUMPERCYCLE;
CONST( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_Dsp_StorageMng_u2BIdx_StaRoe = DCM_P_STORAGE_BLIDX_STA_ROE;
CONST( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_Dsp_StorageMng_u2BIdx_EndRoe = DCM_P_STORAGE_BLIDX_END_ROE;

#define DCM_STOP_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>


#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-10-0                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
