/* Dem_NvM_Connector_c(v5-10-0)                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/NvM_Connector/CODE                                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "Dem_NvM_Connector.h"

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
/* Function Name | Dem_NvM_GetErrorStatus                                   */
/* Description   | Gets status of NvM block.                                */
/* Preconditions | none                                                     */
/* Parameters    | [in] BlockId :                                           */
/*               |        Nv block ID                                       */
/*               | [out] RequestResultPtr :                                 */
/*               |        Nv block status                                   */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : success                                    */
/*               |        E_NOT_OK : failed                                 */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_NvM_GetErrorStatus
(
    VAR( Dem_NvM_BlockIdType, AUTOMATIC ) BlockId,
    P2VAR( Dem_NvM_RequestResultType, AUTOMATIC, AUTOMATIC ) RequestResultPtr
)
{
    VAR( Std_ReturnType, AUTOMATIC ) retVal;

    retVal = NvM_GetErrorStatus( BlockId, RequestResultPtr );

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_NvM_WriteBlock                                       */
/* Description   | Write a block.                                           */
/* Preconditions | none                                                     */
/* Parameters    | [in] BlockId :                                           */
/*               |        Nv block ID                                       */
/*               | [in] NvM_SrcPtr :                                        */
/*               |        In case null pointer, select permanence RAM poin- */
/*               |        ted BlockId for read.                             */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : success                                    */
/*               |        E_NOT_OK : failed                                 */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_NvM_WriteBlock
(
    VAR( Dem_NvM_BlockIdType, AUTOMATIC ) BlockId,
    P2VAR( void, AUTOMATIC, DEM_VAR_NO_INIT ) NvM_SrcPtr
)
{
    VAR( Std_ReturnType, AUTOMATIC ) retVal;

    if( BlockId != DEM_NVM_MULTI_REQ_BLOCK_ID )
    {
        retVal = NvM_WriteBlock( BlockId, NvM_SrcPtr );
    }
    else
    {
        retVal = E_NOT_OK;
    }
    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_NvM_CancelJobs                                       */
/* Description   | Cancel a block Jobs.                                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] BlockId :                                           */
/*               |        Nv block ID                                       */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : success                                    */
/*               |        E_NOT_OK : failed                                 */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_NvM_CancelJobs
(
    VAR( Dem_NvM_BlockIdType, AUTOMATIC ) BlockId
)
{
    VAR( Std_ReturnType, AUTOMATIC ) retVal;

    retVal = NvM_CancelJobs( BlockId );

    return retVal;
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
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
