/* Dcm_Dsp_SID2F_Cfg_h(v5-8-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
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
#define DCM_DSP_SID2F_CONTROLSTATE_ALLSET       ((uint8)0U)
#define DCM_DSP_SID2F_CONTROLSTATE_IOCP03SET    ((uint8)1U)
#define DCM_DSP_SID2F_CONTROLSTATE_ALLNOSET     ((uint8)2U)

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

extern CONST ( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_Dsp_Sid2F_u1SetReportControlState;

#define DCM_STOP_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>

#endif /* DCM_SUPPORT_SID2F == STD_ON */
#endif /* DCM_DSP_SID2F_CFG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-8-0         :2024-10-29                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-10-0                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
