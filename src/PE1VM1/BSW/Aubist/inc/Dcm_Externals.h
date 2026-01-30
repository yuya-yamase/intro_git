/* Dcm_Externals_h(v5-6-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dcm_Externals/HEADER                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef DCM_EXTERNALS_H
#define DCM_EXTERNALS_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>

#include <Dcm/Dcm_Main_Common_Callout.h>
#include <Dcm/Dcm_Dsl_Main_Callout.h>
#include <Dcm/Dcm_Dsd_Main_Callout.h>
#include <Dcm/Dcm_Dsp_SID02_Callout.h>
#include <Dcm/Dcm_Dsp_SID04_Callout.h>
#include <Dcm/Dcm_Dsp_SID10_Callout.h>
#include <Dcm/Dcm_Dsp_SID11_Callout.h>
#include <Dcm/Dcm_Dsp_SID14_Callout.h>
#include <Dcm/Dcm_Dsp_SID19_Sub42_Callout.h>
#include <Dcm/Dcm_Dsp_SID19_Sub55_Callout.h>
#include <Dcm/Dcm_Dsp_SID27_Callout.h>
#include <Dcm/Dcm_Dsp_SID28_Callout.h>
#include <Dcm/Dcm_Dsp_SID29_Callout.h>
#include <Dcm/Dcm_Dsp_SID2C_Callout.h>
#include <Dcm/Dcm_Dsp_SID2F_Callout.h>
#include <Dcm/Dcm_Dsp_SID31_Callout.h>
#include <Dcm/Dcm_Dsp_SID31_ChkSuptRid_Callout.h>
#include <Dcm/Dcm_Dsp_SID34_Callout.h>
#include <Dcm/Dcm_Dsp_SID35_Callout.h>
#include <Dcm/Dcm_Dsp_SID36_Callout.h>
#include <Dcm/Dcm_Dsp_SID37_Callout.h>
#include <Dcm/Dcm_Dsp_SID85_Callout.h>
#include <Dcm/Dcm_Dsp_SID86_Callout.h>
#include <Dcm/Dcm_Dsp_SIDA4_Callout.h>
#include <Dcm/Dcm_Dsp_SIDB9_Callout.h>
#include <Dcm/Dcm_Dsp_SIDBA_Callout.h>
#include <Dcm/Dcm_Dsp_DataTfrMng_Callout.h>
#include <Dcm/Dcm_Dsp_DidMng_Callout.h>
#include <Dcm/Dcm_Dsp_DidMng_ChkSuptDid_Callout.h>
#include <Dcm/Dcm_Dsp_MemMng_Callout.h>
#include <Dcm/Dcm_Dsp_OBDIf_Callout.h>
/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE_CALLOUT
#include <Dcm_MemMap.h>


#define DCM_STOP_SEC_CODE_CALLOUT
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
#define DCM_START_SEC_CONST
#include <Dcm_MemMap.h>


#define DCM_STOP_SEC_CONST
#include <Dcm_MemMap.h>

#endif /* DCM_EXTERNALS_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-02-27                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-10-0                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
