/* Dem_SimilarMngVld._c(v5-3-0)                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/SimilarMngVld./CODE                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../../cfg/Dem_Cfg.h"

#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )
#include "../../../../cfg/Dem_Similar_Cfg.h"
#include "../../../../inc/Dem_Rc_SimilarMng.h"
#include "../../../../inc/Dem_Rc_ClrInfoMng.h"
#include "../../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../../inc/Dem_Rc_RecMngCmn.h"
#include "../../../../inc/Dem_Rc_RecMngCmn_Table.h"
#include "Dem_SimilarMng_local.h"

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


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>


/****************************************************************************/
/* Function Name | Dem_SimilarMng_GetFactoryCheckResult_EventStrgIndex      */
/* Description   | get factory check result of Similar record.              */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the specific ev- */
/*               |        ent record.                                       */
/* Return Value  | boolean                                                  */
/*               |          TRUE      : Factory default                     */
/*               |          FALSE     : Non Factory default                 */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_SimilarMng_GetFactoryCheckResult_EventStrgIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) similarStrgIndex;
    VAR( boolean, AUTOMATIC ) resultOfFactoryCheck;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvId;

    resultOfFactoryCheck = (boolean)FALSE;

    retCnvId = Dem_CfgInfoPm_CnvEventStrgIndexToSimilarStrgIndex( EventStrgIndex, &similarStrgIndex );
    if( retCnvId == DEM_IRT_OK )
    {
        resultOfFactoryCheck = Dem_SimilarMng_GetFactoryCheckResult( similarStrgIndex );
    }

    return resultOfFactoryCheck;
}


/****************************************************************************/
/* Function Name | Dem_SimilarMng_CheckClearId_EventStrgIndex               */
/* Description   | get clearID check result of Similar record.              */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the specific ev- */
/*               |        ent record.                                       */
/* Return Value  | boolean                                                  */
/*               |          TRUE      : ClearId check OK                    */
/*               |          FALSE     : ClearId check NG                    */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_SimilarMng_CheckClearId_EventStrgIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) ClearID
)
{
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) similarStrgIndex;
    VAR( boolean, AUTOMATIC ) resultOfClearIdCheck;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvId;

    resultOfClearIdCheck = (boolean)TRUE;

    retCnvId = Dem_CfgInfoPm_CnvEventStrgIndexToSimilarStrgIndex( EventStrgIndex, &similarStrgIndex );
    if( retCnvId == DEM_IRT_OK )
    {
        resultOfClearIdCheck = Dem_SimilarMng_CheckClearId( similarStrgIndex, ClearID );
    }

    return resultOfClearIdCheck;
}


/****************************************************************************/
/* Function Name | Dem_SimilarMng_CheckConsistencyId_EventStrgIndex         */
/* Description   | get consistencyId check result of Similar record.        */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the specific ev- */
/*               |        ent record.                                       */
/* Return Value  | boolean                                                  */
/*               |          TRUE      : consistencyID check OK              */
/*               |          FALSE     : consistencyID check NG              */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_SimilarMng_CheckConsistencyId_EventStrgIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyId
)
{
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) similarStrgIndex;
    VAR( boolean, AUTOMATIC ) resultOfConsistencyIdCheck;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvId;

    resultOfConsistencyIdCheck = (boolean)TRUE;

    retCnvId = Dem_CfgInfoPm_CnvEventStrgIndexToSimilarStrgIndex( EventStrgIndex, &similarStrgIndex );
    if( retCnvId == DEM_IRT_OK )
    {
        resultOfConsistencyIdCheck = Dem_SimilarMng_CheckConsistencyId( similarStrgIndex, ConsistencyId );
    }

    return resultOfConsistencyIdCheck;
}


/****************************************************************************/
/* Function Name | Dem_SimilarMng_NvMClearSimilarRecordList_EventStrgIndex  */
/* Description   | clear similar record                                     */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the specific ev- */
/*               |        ent record.                                       */
/* Return Value  | none                                                     */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_SimilarMng_NvMClearSimilarRecord_EventStrgIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) similarStrgIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvId;

    retCnvId = Dem_CfgInfoPm_CnvEventStrgIndexToSimilarStrgIndex( EventStrgIndex, &similarStrgIndex );
    if( retCnvId == DEM_IRT_OK )
    {
        Dem_SimilarMng_ClearSimilarRecordList( similarStrgIndex );
    }

    return;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
