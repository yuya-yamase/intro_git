/* Dcm_Dsp_DidMng_OBD_h(v5-3-0)                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_DidMng_OBD/HEADER                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DCM_DSP_DIDMNG_OBD_H
#define DCM_DSP_DIDMNG_OBD_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

#include "../../Dcm/Dsp/cfg/Dcm_Dsp_DidMng_OBD_Cfg.h"
#include <Dcm/Dcm_Main_Common.h>
#include <Dcm.h>

#if( DCM_OBD_RANGE_DID_USE == STD_ON )

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

FUNC( void, DCM_CODE ) Dcm_Dsp_DidMng_OBD_ClrForEachReq
(
    void
);
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_OBD_ChkObdDid
(
    const uint16 u2Did
);
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_OBD_GetObdDidDataLen
(
    const uint16  u2Did,
    P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA)ptDataLength
);
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_OBD_CallReadObdDidFnc
(
    const uint16 u2Did,
    const Dcm_OpStatusType u1OpStatus,
    const uint32 u4DataBufferLength,
    P2VAR( uint8,  AUTOMATIC, DCM_APPL_DATA ) ptData,
    P2VAR( uint32, AUTOMATIC, DCM_APPL_DATA ) ptDataLength,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ptErrorCode
);

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
#define DCM_START_SEC_CONST
#include <Dcm_MemMap.h>


#define DCM_STOP_SEC_CONST
#include <Dcm_MemMap.h>

#endif /* DCM_OBD_RANGE_DID_USE == STD_ON */

#endif /* DCM_DSP_DIDMNG_OBD_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-2-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

