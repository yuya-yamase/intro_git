/* Dcm_Dsp_StorageMng_Cfg_h(v5-3-0)                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_StorageMng_Cfg/HEADER                             */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DCM_DSP_STORAGEMNG_CFG_H
#define DCM_DSP_STORAGEMNG_CFG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_P_STORAGE_BLOCKID_NUM                ((uint16)1U)
#define DCM_P_STORAGE_BLOCKID_TBL                (DCM_P_STORAGE_BLOCKID_NUM + (uint16)1U)

#define DCM_P_STORAGE_BLIDX_STA_ROE              ((uint16)0U)
#define DCM_P_STORAGE_BLIDX_END_ROE              ((uint16)0U)

#define DCM_DSP_STORAGEMNG_GETERRRETRYMAX        ((uint8)0U)
#define DCM_DSP_STORAGEMNG_WRITERETRYMAX         ((uint8)0U)

#define DCM_DSP_STORAGE_BLOCKID_MAXNUMPERCYCLE   ((uint16)0xFFFFU)

#define DCM_DSP_STORAGEMNG_FUNC_NUM              ((uint8)2U)
#define DCM_DSP_STORAGEMNG_FUNC_SID86            ((uint8)0x00U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef P2FUNC( void, DCM_CODE, Dcm_Dsp_StorageMng_ReadConf_FuncType )
( const uint16 u2BlockIdx, const uint8 u1Result );
typedef P2FUNC( void, DCM_CODE, Dcm_Dsp_StorageMng_SetDataS2M_FuncType )
( const uint16 u2BlockIdx );
typedef P2FUNC( void, DCM_CODE, Dcm_Dsp_StorageMng_SetDataM2S_FuncType )
( const uint16 u2BlockIdx );

typedef struct
{
    Dcm_Dsp_StorageMng_ReadConf_FuncType      ptReadComfFunc;
    Dcm_Dsp_StorageMng_SetDataS2M_FuncType    ptSetDataS2MFunc;
    Dcm_Dsp_StorageMng_SetDataM2S_FuncType    ptSetDataM2SFunc;
}Dcm_Dsp_StorageMng_FuncListType;

typedef struct{
    uint16      u2BlockId;
    uint8       u1FuncIdx;
}Dcm_Dsp_StorageMng_BlockListType;

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
extern CONST( AB_83_ConstV Dcm_Dsp_StorageMng_FuncListType, DCM_CONFIG_DATA ) Dcm_Dsp_StorageMng_stFuncList[ DCM_DSP_STORAGEMNG_FUNC_NUM ];
extern CONST( AB_83_ConstV Dcm_Dsp_StorageMng_BlockListType, DCM_CONFIG_DATA ) Dcm_Dsp_StorageMng_stBlockList[ DCM_P_STORAGE_BLOCKID_TBL ];
extern CONST( AB_83_ConstV uint32, DCM_CONFIG_DATA ) Dcm_Dsp_StorageMng_u4ReadAllFsTime;
extern CONST( AB_83_ConstV uint32, DCM_CONFIG_DATA ) Dcm_Dsp_StorageMng_u4SingleBlockFsTime;
extern CONST( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_Dsp_StorageMng_u2BlockId_Num;
extern CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_Dsp_StorageMng_u1FuncList_Num;
extern CONST( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_Dsp_StorageMng_u2Queue_Max;
extern CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_Dsp_StorageMng_u1GetErrRetry_Max;
extern CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_Dsp_StorageMng_u1WriteRetry_Max;
extern CONST( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_Dsp_StorageMng_u2IdNum_PerCycle;
extern CONST( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_Dsp_StorageMng_u2BIdx_StaRoe;
extern CONST( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_Dsp_StorageMng_u2BIdx_EndRoe;

#define DCM_STOP_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>

#endif /* DCM_DSP_STORAGEMNG_CFG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-10-0                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
