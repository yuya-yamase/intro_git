/* Dcm_Dsp_SID19_Sub04_Cfg_h(v5-5-0)                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID19_Sub04_Cfg/HEADER                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DCM_DSP_SID19_SUB04_CFG_H
#define DCM_DSP_SID19_SUB04_CFG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>
#if ( DCM_SUPPORT_SID19_SUB04 == STD_ON )


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSP_SID19_SUB04_MAXNUM_SSDAT       ((uint8)1U)
#define DCM_DSP_SID19_SUB04_REMOVE_NASSRN_NUM  ((uint8)2U)


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

extern CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_Dsp_SID19_Sub04_u1RemoveNASSRNTbl[DCM_DSP_SID19_SUB04_REMOVE_NASSRN_NUM];

extern CONST ( AB_83_ConstV boolean, DCM_CONFIG_DATA ) Dcm_Dsp_SID19_Sub04_bOutputLegislatedOBDData;
extern CONST ( AB_83_ConstV boolean, DCM_CONFIG_DATA ) Dcm_Dsp_SID19_Sub04_bAcceptRepRecNumFF;
extern CONST ( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_Dsp_SID19_Sub04_u1Max_Num_SSDat;
extern CONST ( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_Dsp_SID19_Sub04_u1RemoveNASSRNNum;

#define DCM_STOP_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>


#endif /* DCM_SUPPORT_SID19_SUB04 == STD_ON */
#endif /* DCM_DSP_SID19_SUB04_CFG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v3-0-0         :2019-05-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-5-1                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

