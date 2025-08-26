/* Dcm_Dsp_SID85_Cfg_h(v5-0-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID85_Cfg/HEADER                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DCM_DSP_SID85_CFG_H
#define DCM_DSP_SID85_CFG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsp_SID85_Callout.h>
#if ( DCM_SUPPORT_SID85 == STD_ON )


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_P_DTCSETTING_IND        ((uint8)0U)
#define DCM_P_DTCSETTING_CNF        ((uint8)1U)

#define DCM_P_DTCSETTING_SUPPORT_OPTION_RECORD (STD_OFF)

#define Dcm_Dsp_SID85_CheckControl(u1Mode,u4DTCGroup,u1DTCKind)    Dcm_CheckControlDTCSetting((u1Mode),(u4DTCGroup),(u1DTCKind)) /* MISRA DEVIATION */
#define Dcm_Dsp_SID85_ControlProcess(u1Mode,OpStatus,ptOptionRecord)   Dcm_ControlDTCSettingProcess((u1Mode),(OpStatus),(ptOptionRecord)) /* MISRA DEVIATION */

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

extern CONST ( AB_83_ConstV boolean, DCM_CONFIG_DATA ) Dcm_Dsp_SID85_bReEnableDTCSet;
extern CONST ( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_Dsp_SID85_u1DTCSettingTiming;
extern CONST ( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_Dsp_SID85_u1DTCSettingOpRecordLen;

#define DCM_STOP_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>


#endif /* DCM_SUPPORT_SID85 == STD_ON */
#endif /* DCM_DSP_SID85_CFG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v3-0-0         :2019-07-29                                              */
/*  v3-2-0         :2020-08-27                                              */
/*  v5-0-0         :2022-03-29                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-3-z0003                                        */
/*  BSW plug-in        :v5-5-1                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
