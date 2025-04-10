/* Dem_NvM_If_Connector_c(v5-3-0)                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/NvM_If_Connector/CODE                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "Dem_NvM_If_Connector.h"

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
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>
/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CONST
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_CONST
#include <Dem_MemMap.h>
/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>


#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )

/****************************************************************************/
/* Function Name | Dem_NvM_If_GetReadAllStatus                              */
/* Description   | Gets status of NvM ReadAll.                              */
/* Preconditions | none                                                     */
/* Parameters    | [out] RequestResultPtr :                                 */
/*               |        Nv block status                                   */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : success                                    */
/*               |        E_NOT_OK : failed                                 */
/* Notes         | At the caller, the value of RequestResultPtr is          */
/*               | guaranteed.                                              */
/*               | Caller:Dem_MM_GetMultiBlockStatus                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_NvM_If_GetReadAllStatus
(
    P2VAR( Dem_NvM_RequestResultType, AUTOMATIC, AUTOMATIC ) RequestResultPtr
)
{
    /* (*RequestResultPtr) = DEM_NVM_REQ_OK; */
    return ((Std_ReturnType)E_OK);
}


/****************************************************************************/
/* Function Name | Dem_NvM_If_GetWriteBlockStatus                           */
/* Description   | Get the status of write request block.                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] BlockId :                                           */
/*               |        Nv block ID                                       */
/*               | [out] RequestResultPtr :                                 */
/*               |        Nv block status                                   */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : success                                    */
/*               |        E_NOT_OK : failed                                 */
/* Notes         | At the caller, the value of RequestResultPtr is          */
/*               | guaranteed.                                              */
/*               | Caller:Dem_MM_ProcessConfirmComplete                     */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_NvM_If_GetWriteBlockStatus
(
    VAR( Dem_BlockIdType, AUTOMATIC ) BlockId,
    P2VAR( Dem_NvM_RequestResultType, AUTOMATIC, AUTOMATIC ) RequestResultPtr
)
{
    (*RequestResultPtr) = u1_g_oXDoCANAubIfDtcNvmWrStat(BlockId);

    return ((Std_ReturnType)E_OK);
}


/****************************************************************************/
/* Function Name | Dem_NvM_If_GetReadBlockStatus                            */
/* Description   | Get the status of read request block.                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] BlockId :                                           */
/*               |        Nv block ID                                       */
/*               | [out] RequestResultPtr :                                 */
/*               |        Nv block status                                   */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : success                                    */
/*               |        E_NOT_OK : failed                                 */
/* Notes         | At the caller, the value of RequestResultPtr is          */
/*               | guaranteed.                                              */
/*               | Caller:Dem_MM_CheckReadComplete                          */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_NvM_If_GetReadBlockStatus
(
    VAR( Dem_BlockIdType, AUTOMATIC ) BlockId,
    P2VAR( Dem_NvM_RequestResultType, AUTOMATIC, AUTOMATIC ) RequestResultPtr
)
{
    /* (*RequestResultPtr) = DEM_NVM_REQ_OK; */
    return ((Std_ReturnType)E_OK);
}


/****************************************************************************/
/* Function Name | Dem_NvM_If_WriteSingleBlock                              */
/* Description   | Get the status of write request block.                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] BlockId :                                           */
/*               |        Nv block ID                                       */
/*               | [in] NvM_SrcPtr :                                        */
/*               |        In case null pointer, select permanence RAM poin- */
/*               |        ted BlockId for read.                             */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : success                                    */
/*               |        E_NOT_OK : failed                                 */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_NvM_If_WriteSingleBlock
(
    VAR( Dem_BlockIdType, AUTOMATIC ) BlockId,
    P2VAR( void, AUTOMATIC, DEM_VAR_NO_INIT ) NvM_SrcPtr
)
{
    vd_g_oXDoCANAubIfDtcNvmWrBlock(BlockId, NvM_SrcPtr);
    return ((Std_ReturnType)E_OK);
}


/****************************************************************************/
/* Function Name | Dem_NvM_If_CancelWriteJob                                */
/* Description   | Cancel single block write request.                       */
/* Preconditions | none                                                     */
/* Parameters    | [in] BlockId :                                           */
/*               |        Nv block ID                                       */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : success                                    */
/*               |        E_NOT_OK : failed                                 */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_NvM_If_CancelWriteJob
(
    VAR( Dem_BlockIdType, AUTOMATIC ) BlockId
)
{
    /* Nvmc doesn't support cancel logic */
    return ((Std_ReturnType)E_NOT_OK);

}


#endif /* DEM_NVM_SYNC_PROCESS_ENABLE  -STD_ON- */


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v2-0-0         :2019-03-27                                              */
/*  v4-0-0         :2020-03-19                                              */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
