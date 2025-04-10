/* Dem_DataCtl_SpecificEventEntry_c(v5-5-0)                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataCtl_SpecificEventeEntry/CODE                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "Dem_DataCtl_EventEntry_local.h"
#include "../../../inc/Dem_Rc_DataMng.h"

#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )
#include "../../../inc/Dem_Pm_Similar.h"
#include "../../../inc/Dem_Pm_Misfire.h"



/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
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


/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>


/****************************************************************************/
/* Function Name | Dem_Data_UpdateSpecificEventMemoryEntryFromTmp           */
/* Description   | Updates the specific event memory entry from temporary   */
/*               | area.                                                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the event ID.    */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_UpdateSpecificEventMemoryEntryFromTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) consistencyId;
    VAR( boolean, AUTOMATIC ) consistencyIdUpdateFlg;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFaultIndex;

#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    Dem_Similar_CompareSimilarInfoToTmp( EventStrgIndex );
#endif  /*   ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )         */
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    Dem_Misfire_CompareMisfireInfoToTmp( EventStrgIndex );
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )           */

    Dem_Data_SetConsistencyIdUpdateFlg();

    Dem_Data_GetConsistencyIdUpdateFlg( &consistencyIdUpdateFlg, &consistencyId );

    /* Starts exclusion. */
    SchM_Enter_Dem_EventMemory();

    if( consistencyIdUpdateFlg == (boolean)TRUE )
    {
        resultOfGetFaultIndex = Dem_DataMngC_GetER_FaultIndex( EventStrgIndex, &faultIndex );       /* [GUD:RET:DEM_IRT_OK] EventStrgIndex */
        if( resultOfGetFaultIndex == DEM_IRT_OK )
        {
            Dem_DataMng_SetFaultRecordConsistencyId( faultIndex, consistencyId );
        }

        Dem_DataMng_SetEventRecordConsistencyId( EventStrgIndex, consistencyId );
    }

#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    Dem_Similar_UpdateEventMemoryEntryFromTmp( EventStrgIndex, consistencyIdUpdateFlg, consistencyId );
#endif  /*   ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )         */
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    Dem_Misfire_UpdateEventMemoryEntryFromTmp( EventStrgIndex, consistencyIdUpdateFlg, consistencyId );
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )           */

    /* Finishes exclusion. */
    SchM_Exit_Dem_EventMemory();

    return ;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
