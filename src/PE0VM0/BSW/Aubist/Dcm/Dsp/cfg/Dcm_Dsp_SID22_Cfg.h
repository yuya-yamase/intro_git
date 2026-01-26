/* Dcm_Dsp_SID22_Cfg_h(v5-4-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID22_Cfg/HEADER                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DCM_DSP_SID22_CFG_H
#define DCM_DSP_SID22_CFG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>
#if ( DCM_SUPPORT_SID22 == STD_ON )


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_P_MAX_DID_TO_READ        ((uint16)1U)    /* DcmDspMaxDidToRead            */
#define DCM_P_RES_MAX_DATA_LENGTH    ((uint32)4294967295U)    /* DcmDspSID22ResMaxDataLength   */
#define DCM_P_SID22_RESDATALEN_MAX   ((uint32)(DCM_P_RES_MAX_DATA_LENGTH - (uint32)1U))
#define DCM_P_DID_CHECK_NUM_PER_CYCLE ((uint16)1364U)     /* DcmDspSID22DidCheckNumPerCycle */
#define DCM_P_DID_READ_NUM_PER_CYCLE ((uint16)1U)    /* DcmDspSID22DidReadNumPerCycle */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>

extern CONST( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_P_u2Max_Did_To_Read;
extern CONST( AB_83_ConstV uint32, DCM_CONFIG_DATA ) Dcm_P_Sid22_u4Resdatalen_Max;
extern CONST( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_P_u2Did_Check_Num_Per_Cycle;
extern CONST( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_P_u2Did_Read_Num_Per_Cycle;
extern CONST( AB_83_ConstV boolean, DCM_CONFIG_DATA ) Dcm_P_Sid22_bRoorIfAnyOneUnsupportedDidExist;

#define DCM_STOP_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>

#endif /* DCM_SUPPORT_SID22 == STD_ON */
#endif /* DCM_DSP_SID22_CFG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v3-0-0         :2019-07-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-4-0         :2023-06-28                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-5-1                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
