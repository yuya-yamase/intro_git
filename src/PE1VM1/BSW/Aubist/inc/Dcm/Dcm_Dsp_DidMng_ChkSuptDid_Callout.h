/* Dcm_Dsp_DidMng_ChkSuptDid_Callout_h(v5-1-0)                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_DidMng_ChkSuptDid_Callout/HEADER                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DCM_DSP_DIDMNG_CHKSUPTDID_CALLOUT_H
#define DCM_DSP_DIDMNG_CHKSUPTDID_CALLOUT_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
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
#define DCM_START_SEC_CODE_CALLOUT
#include <Dcm_MemMap.h>


#if ( ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) )
FUNC( Std_ReturnType, DCM_CODE_CALLOUT ) Dcm_CheckSupportedDid
(
    uint16 u2Did,
    Dcm_DidRequestType u1ReqType,
    uint16 u2PduId
);
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON */

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
#define DCM_START_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>


#define DCM_STOP_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>


#endif /* DCM_DSP_DIDMNG_CHKSUPTDID_CALLOUT_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-1-0         :2018-08-20                                              */
/*  v3-0-0         :2019-05-29                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-10-0                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
