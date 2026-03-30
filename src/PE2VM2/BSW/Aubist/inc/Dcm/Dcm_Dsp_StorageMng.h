/* Dcm_Dsp_StorageMng_h(v5-1-0)                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_StorageMng/HEADER                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DCM_DSP_STORAGEMNG_H
#define DCM_DSP_STORAGEMNG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>
#include "../../Dcm/Dsp/cfg/Dcm_Dsp_StorageMng_Cfg.h"
#if ( DCM_NVM_USE == STD_ON )

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
FUNC( void, DCM_CODE ) Dcm_Dsp_StorageMng_Init
( void );
FUNC( void, DCM_CODE ) Dcm_Dsp_StorageMng_Refresh
( void );
FUNC( void, DCM_CODE ) Dcm_Dsp_StorageMng_ReReadAllCbk
(
    const uint8 u1EventId
);
FUNC( void, DCM_CODE ) Dcm_Dsp_StorageMng_ReReadBlockCbk
(
    const uint8 u1EventId
);
FUNC( void, DCM_CODE ) Dcm_Dsp_StorageMng_ReadAllFsTOCbk
(
    const uint8 u1TimerId
);

FUNC( Std_ReturnType, DCM_CODE) Dcm_Dsp_StorageMng_EnQueue
(
    const uint16 u2BlockIdx
);
FUNC( void, DCM_CODE ) Dcm_Dsp_StorageMng_GetErrorStsCbk
(
    const uint8 u1EventId
);
FUNC( void, DCM_CODE ) Dcm_Dsp_StorageMng_DeQueueCbk
(
    const uint8 u1EventId
);
FUNC( void, DCM_CODE ) Dcm_Dsp_StorageMng_RewriteCbk
(
    const uint8 u1EventId
);
FUNC( void, DCM_CODE ) Dcm_Dsp_StorageMng_WriteBlFsTOCbk
(
    const uint8 u1TimerId
);
FUNC( boolean, DCM_CODE ) Dcm_Dsp_StorageMng_GetSleepPermission
( void );
FUNC( void, DCM_CODE ) Dcm_Dsp_StorageMng_PreWriteAll
( void );

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

#endif /* DCM_NVM_USE */

#endif /* DCM_DSP_STORAGEMNG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

