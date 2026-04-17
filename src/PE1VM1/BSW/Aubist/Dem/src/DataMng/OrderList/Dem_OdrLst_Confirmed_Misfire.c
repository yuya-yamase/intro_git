/* Dem_OdrLst_Confirmed_Misfire_c(v5-7-0)                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/Dem_OdrLst_Confirmed_Misfire/CODE                     */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#if ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT == STD_ON )
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
#include "../../../inc/Dem_Rc_OdrLst.h"
#include "../../../inc/Dem_Pm_Misfire.h"
#include "../../../inc/Dem_Rc_MisfireMng.h"

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

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/*==========================================================================*/
/*  Function for USE confirmed order list.                                  */
/*==========================================================================*/

/****************************************************************************/
/* Function Name | Dem_OdrLst_Confirmed_Misfire_GetLargestOccurrenceOrder   */
/* Description   | Get largest ConfirmedCylOccurrenceOrder.                 */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u16_OccrOrderType                                    */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | new created.                                             */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u16_OccrOrderType, DEM_CODE ) Dem_OdrLst_Confirmed_Misfire_GetLargestOccurrenceOrder
( void )
{
    VAR( Dem_MisfireComRecordType, AUTOMATIC ) misfireComRecord;
    VAR( Dem_u16_OccrOrderType, AUTOMATIC ) retLargestConfirmedOccurrenceOrder;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireCylinderNum;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireConfirmedOrderIndex;

    retLargestConfirmedOccurrenceOrder = (Dem_u16_OccrOrderType)0U;

    Dem_MisfireMng_GetMisfireComRecord( &misfireComRecord );
    misfireCylinderNum = Dem_MisfireCylinderNum;
    for( misfireConfirmedOrderIndex = (Dem_MisfireCylinderNumberType)0U; misfireConfirmedOrderIndex < misfireCylinderNum; misfireConfirmedOrderIndex++ )    /* [GUD:for]misfireConfirmedOrderIndex */
    {
        if( misfireComRecord.ConfirmedOrderCylList[misfireConfirmedOrderIndex] < misfireCylinderNum )   /* [GUD]misfireConfirmedOrderIndex *//* [ARYCHK] DEM_MISFIRE_CYLINDER_AND_RM_NUM / 1 / misfireConfirmedOrderIndex */
        {
            retLargestConfirmedOccurrenceOrder = misfireComRecord.OccurrenceOrderListOfConfirmedCyl[misfireConfirmedOrderIndex];    /* [GUD]misfireConfirmedOrderIndex *//* [ARYCHK] DEM_MISFIRE_CYLINDER_AND_RM_NUM / 1 / misfireConfirmedOrderIndex */
        }
        else
        {
            break;
        }
    }

    return retLargestConfirmedOccurrenceOrder;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */
#endif /* ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT == STD_ON ) */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-6-0         :2024-01-29                                              */
/*  v5-7-0         :2024-05-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
