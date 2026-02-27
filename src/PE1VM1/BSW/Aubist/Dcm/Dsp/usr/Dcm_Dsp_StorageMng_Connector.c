/* Dcm_Dsp_StorageMng_Connector_c(v5-0-0)                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_StorageMng_Connector/CODE                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsp_StorageMng_Connector.h>
#if ( DCM_NVM_USE == STD_ON )
#include "Dcm_Dsp_StorageMng_Cfg.h"
#include "Dcm_Dsp_SID86_Cfg.h"
#include "oxdocan_aubif.h"

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

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* Function Name | Dcm_Dsp_StorageMng_Cnct_NvMGetErrSt                      */
/* Description   | Get job status                                           */
/* Preconditions | None                                                     */
/* Parameters    | [IN]u2BlockId            :Block ID of NVRAM block        */
/*               | [OUT]ptRequestResultPtr  :Processing status of job       */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK                                                   */
/*               |   E_NOT_OK                                               */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_StorageMng_Cnct_NvMGetErrSt
(
    const Dcm_NvM_BlockIdType u2BlockId,
    P2VAR( Dcm_NvM_RequestResultType, AUTOMATIC, DCM_APPL_DATA ) ptRequestResultPtr
)
{
    Std_ReturnType u1_RetVal;
    Dcm_NvM_BlockIdType u2_t_BlkIdx;

    u1_RetVal = E_NOT_OK;

    if(u2BlockId == (Dcm_NvM_BlockIdType)0U){   /* DCM_DSP_STORAGEMNG_READALL_BLOCKID */
        *ptRequestResultPtr = DCM_NVM_REQ_OK;
        u1_RetVal = E_OK;
    }
#if ((defined(DCM_DSP_SID86_NVM_USE)  ) && \
     (DCM_DSP_SID86_NVM_USE == STD_ON))
    else{
        if(u2BlockId >= Dcm_Dsp_StorageMng_stBlockList[0].u2BlockId){
            u2_t_BlkIdx = u2BlockId - Dcm_Dsp_StorageMng_stBlockList[0].u2BlockId;
/* Since DCM_P_STORAGE_BLIDX_STA_ROE is 0, redundant processing is commented out.                             */
/*          if((DCM_P_STORAGE_BLIDX_STA_ROE <= u2_t_BlkIdx) && (u2_t_BlkIdx <= DCM_P_STORAGE_BLIDX_END_ROE)){ */
/*              u2_t_BlkIdx = u2_t_BlkIdx - DCM_P_STORAGE_BLIDX_STA_ROE;                                      */
            if(u2_t_BlkIdx <= DCM_P_STORAGE_BLIDX_END_ROE){
                *ptRequestResultPtr = u1_g_oXDoCANAubIfRoeNvmGetErrSt(u2_t_BlkIdx);
                u1_RetVal = E_OK;
            }
        }
    }
#endif

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_StorageMng_Cnct_NvMWriteBL                       */
/* Description   | Send write request                                       */
/* Preconditions | None                                                     */
/* Parameters    | [IN]u2BlockId            :Block ID of NVRAM block        */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK                                                   */
/*               |   E_NOT_OK                                               */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_StorageMng_Cnct_NvMWriteBL
(
    const Dcm_NvM_BlockIdType u2BlockId
)
{
    Std_ReturnType u1_RetVal;
    Dcm_NvM_BlockIdType u2_t_BlkIdx;

    u1_RetVal = E_NOT_OK;

#if ((defined(DCM_DSP_SID86_NVM_USE) ) && \
     (DCM_DSP_SID86_NVM_USE == STD_ON))
    if(u2BlockId >= Dcm_Dsp_StorageMng_stBlockList[0].u2BlockId){
        u2_t_BlkIdx = u2BlockId - Dcm_Dsp_StorageMng_stBlockList[0].u2BlockId;
/* Since DCM_P_STORAGE_BLIDX_STA_ROE is 0, redundant processing is commented out.                         */
/*      if((DCM_P_STORAGE_BLIDX_STA_ROE <= u2_t_BlkIdx) && (u2_t_BlkIdx <= DCM_P_STORAGE_BLIDX_END_ROE)){ */
/*          u2_t_BlkIdx = u2_t_BlkIdx - DCM_P_STORAGE_BLIDX_STA_ROE;                                      */
        if(u2_t_BlkIdx <= DCM_P_STORAGE_BLIDX_END_ROE){
            vd_g_oXDoCANAubIfRoeNvmWrBlock(u2_t_BlkIdx);
            u1_RetVal = E_OK;
        }
    }
#endif

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_StorageMng_Cnct_NvMCancelJob                     */
/* Description   | Cancel job request                                       */
/* Preconditions | None                                                     */
/* Parameters    | [IN]u2BlockId            :Block ID of NVRAM block        */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK                                                   */
/*               |   E_NOT_OK                                               */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC (Std_ReturnType, DCM_CODE ) Dcm_Dsp_StorageMng_Cnct_NvMCancelJob
(
    const Dcm_NvM_BlockIdType u2BlockId
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_NOT_OK;

    return u1_RetVal;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

#endif  /* DCM_NVM_USE */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2021-12-24                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

