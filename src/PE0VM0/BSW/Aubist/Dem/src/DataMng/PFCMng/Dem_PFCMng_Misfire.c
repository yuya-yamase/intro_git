/* Dem_PFCMng_Misfire_c(v5-5-0)                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/PFCMng/CODE                                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../cfg/Dem_NvM_Cfg.h"
#include "../../../inc/Dem_Rc_PFCMng.h"
#include "../../../inc/Dem_Pm_DTC_PFC.h"

#if ( DEM_PFC_SUPPORT == STD_ON )
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
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

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_PFCMng_GetStoredMisfireSpaceEventStrgIndex            */
/* Description   | Get the stored misfire space eventindex and check.       */
/* Preconditions | none                                                     */
/* Parameters    | Dem_u16_EventStrgIndexType                               */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Check result is OK.                  */
/*               |        DEM_IRT_NG : Check result is NG.                  */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | refactor function.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PFCMng_GetStoredMisfireSpaceEventStrgIndex
(
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) StoredMisFirePFCMisFireEventStrgIndexPtr
)
{

    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) storedMisFirePFCMisFireEventStrgIndex;

    storedMisFirePFCMisFireEventStrgIndex = Dem_PFCRecord[Dem_MisfirePFCRecordIndex].EventStrgIndex;    /* [GUD:CFG]Dem_MisfirePFCRecordIndex */

    /* Check event available status, MIL indicator and OBD. */
    retVal = Dem_DTC_CheckAvailableAndMILStatusByEventStrgIndex( storedMisFirePFCMisFireEventStrgIndex );

    if( retVal == DEM_IRT_OK )
    {
        *StoredMisFirePFCMisFireEventStrgIndexPtr = storedMisFirePFCMisFireEventStrgIndex;
    }
    else
    {
        *StoredMisFirePFCMisFireEventStrgIndexPtr = DEM_EVENTSTRGINDEX_INVALID;
    }

    return retVal;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON ) */
#endif /* ( DEM_PFC_SUPPORT == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
