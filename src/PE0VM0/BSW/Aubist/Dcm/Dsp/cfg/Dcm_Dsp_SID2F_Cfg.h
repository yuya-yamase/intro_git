/* Dcm_Dsp_SID2F_Cfg_h(v5-3-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID2F_Cfg/HEADER                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DCM_DSP_SID2F_CFG_H
#define DCM_DSP_SID2F_CFG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>
#if ( DCM_SUPPORT_SID2F == STD_ON )
#include <Dcm/Dcm_Dsp_SID2F_Callout.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define Dcm_Dsp_SID2F_RetCtrlToECUBySec( u1SecLevelOld, u1SecLevelNew ) Dcm_IOCReturnControlToECUBySec( (u1SecLevelOld), (u1SecLevelNew) ) /* MISRA DEVIATION */
#define Dcm_Dsp_SID2F_RetCtrlToECUBySes( u1SesCtrlTypeOld, u1SesCtrlTypeNew ) Dcm_IOCReturnControlToECUBySes( (u1SesCtrlTypeOld), (u1SesCtrlTypeNew) ) /* MISRA DEVIATION */

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

extern CONST ( AB_83_ConstV boolean, DCM_CONFIG_DATA ) Dcm_Dsp_Sid2F_bReportControlStateOnlyIOCP03;

#define DCM_STOP_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>

#endif /* DCM_SUPPORT_SID2F == STD_ON */
#endif /* DCM_DSP_SID2F_CFG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-5-1                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
