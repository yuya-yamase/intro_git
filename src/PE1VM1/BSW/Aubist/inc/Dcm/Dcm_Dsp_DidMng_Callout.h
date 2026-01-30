/* Dcm_Dsp_DidMng_Callout_h(v5-3-0)                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_DidMng_Callout/HEADER                             */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DCM_DSP_DIDMNG_CALLOUT_H
#define DCM_DSP_DIDMNG_CALLOUT_H

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

/* DcmDspDataFreezeCurrentStateFnc */

/* DcmDspDataReadFnc */

/* DcmDspDataResetToDefaultFnc */

/* DcmDspDataReturnControlToEcuFnc */

/* DcmDspDataShortTermAdjustmentFnc */

/* DcmDspDidCheckControlParamFnc */

/* DcmDspDidRangeIsDidAvailableFnc */

/* DcmDspDidRangeReadDataLengthFnc */

/* DcmDspDidRangeReadDidFnc */

/* DcmDspDidRangeWriteDidFnc */

/* DcmDspDidReadModeRuleFnc */

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


#endif /* DCM_DSP_DIDMNG_CALLOUT_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v3-0-0         :2019-05-29                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-10-0                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
