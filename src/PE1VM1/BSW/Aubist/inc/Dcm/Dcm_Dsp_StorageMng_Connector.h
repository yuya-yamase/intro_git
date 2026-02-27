/* Dcm_Dsp_StorageMng_Connector_h(v5-8-0)                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_StorageMng_Connector/HEADER                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DCM_DSP_STORAGEMNG_CONNECTOR_H
#define DCM_DSP_STORAGEMNG_CONNECTOR_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>
#if ( DCM_NVM_USE == STD_ON )
#include <NvM.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_NVM_REQ_OK                   NVM_REQ_OK
#define DCM_NVM_REQ_NOT_OK               NVM_REQ_NOT_OK
#define DCM_NVM_REQ_PENDING              NVM_REQ_PENDING
#define DCM_NVM_REQ_INTEGRITY_FAILED     NVM_REQ_INTEGRITY_FAILED
#define DCM_NVM_REQ_BLOCK_SKIPPED        NVM_REQ_BLOCK_SKIPPED
#define DCM_NVM_REQ_NV_INVALIDATED       NVM_REQ_NV_INVALIDATED
#define DCM_NVM_REQ_CANCELED             NVM_REQ_CANCELED
#define DCM_NVM_REQ_RESTORED_FROM_ROM    NVM_REQ_RESTORED_FROM_ROM

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef NvM_BlockIdType          Dcm_NvM_BlockIdType;
typedef NvM_RequestResultType    Dcm_NvM_RequestResultType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_StorageMng_Cnct_NvMGetErrSt
(
    const Dcm_NvM_BlockIdType u2BlockId,
    P2VAR( Dcm_NvM_RequestResultType, AUTOMATIC, DCM_APPL_DATA ) ptRequestResultPtr
);
FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_StorageMng_Cnct_NvMWriteBL
(
    const Dcm_NvM_BlockIdType u2BlockId
);
FUNC (Std_ReturnType, DCM_CODE ) Dcm_Dsp_StorageMng_Cnct_NvMCancelJob
(
    const Dcm_NvM_BlockIdType u2BlockId
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

#endif /* DCM_NVM_USE */

#endif /* DCM_DSP_STORAGEMNG_CONNECTOR_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-8-0         :2024-10-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
