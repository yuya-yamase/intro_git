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

    u1_RetVal = NvM_GetErrorStatus( u2BlockId, ptRequestResultPtr );

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

    u1_RetVal = NvM_WriteBlock( u2BlockId, NULL_PTR );

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

