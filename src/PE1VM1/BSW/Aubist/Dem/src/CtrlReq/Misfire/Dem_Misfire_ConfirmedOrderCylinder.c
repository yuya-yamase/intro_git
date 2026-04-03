/* Dem_Misfire_ConfirmedOrderCylinder_c(v5-7-0)                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Misfire_ConfirmedOrderCylinder/CODE                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#if ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT == STD_ON )
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_Pm_DataAvl.h"
#include "../../../inc/Dem_Pm_Misfire.h"
#include "../../../inc/Dem_Rc_MisfireMng.h"
#include "../../../inc/Dem_Rc_OdrLst.h"
#include "Dem_Misfire_EventEntry_local.h"
#include "Dem_Misfire_local.h"

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

/****************************************************************************/
/* Function Name | Dem_Misfire_ClearConfirmedOrderCylListToTmp              */
/* Description   | Clear ConfirmedOrder for MisfireCylinder in the tempora- */
/*               | ry area..                                                */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_ClearConfirmedOrderCylListToTmp
( void )
{
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireCylinderNum;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireConfirmedOrderIndex;

    misfireCylinderNum = Dem_MisfireCylinderNum;
    for( misfireConfirmedOrderIndex = (Dem_MisfireCylinderNumberType)0U; misfireConfirmedOrderIndex < misfireCylinderNum; misfireConfirmedOrderIndex++ )    /* [GUD:for]misfireConfirmedOrderIndex */
    {
        Dem_TmpMisfireEventMemoryEntry.MisfireComRecord.ConfirmedOrderCylList[misfireConfirmedOrderIndex] = DEM_MISFIRE_CYL_NUM_INVALID;    /* [GUD]misfireConfirmedOrderIndex */
        Dem_TmpMisfireEventMemoryEntry.MisfireComRecord.OccurrenceOrderListOfConfirmedCyl[misfireConfirmedOrderIndex] = DEM_FAIL_OCCURRENCE_NUM_INVALID;    /* [GUD]misfireConfirmedOrderIndex */
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_Misfire_SetConfirmedOrderCylinder                    */
/* Description   | Set ConfirmedOrder for MisfireCylinder.                  */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | new created.                                             */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_SetConfirmedOrderCylinder
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_MisfireComRecordType, AUTOMATIC ) misfireComRecord;
    VAR( Dem_u16_OccrOrderType, AUTOMATIC ) confirmedOccurrenceOrder;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) bit3Cylinder;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) currentConfirmedOccurrenceCylinder;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) addConfirmedOccurrenceCylinder;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireCylinderNum;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireConfirmedOrderIndex;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) addConfirmedCylinderNumber;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetting;
    VAR( Dem_u08_MisfireKindBitType, AUTOMATIC ) availableMisfireKind;
    VAR( boolean, AUTOMATIC ) misfireEventKind;

    misfireEventKind = Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( EventStrgIndex );
    if( misfireEventKind == (boolean)TRUE )
    {
        availableMisfireKind    =   Dem_DataAvl_GetMisfireCylDTCAvailable();
        bit3Cylinder = Dem_Misfire_GetBit3Cylinder( availableMisfireKind );

        currentConfirmedOccurrenceCylinder = DEM_MISFIRE_CYLINDER_NON;
        Dem_MisfireMng_GetMisfireComRecord( &misfireComRecord );
        misfireCylinderNum = Dem_MisfireCylinderNum;
        /* Create confirmed cylinder before SetEvent from ConfirmedOrderCylList[] */
        for( misfireConfirmedOrderIndex = (Dem_MisfireCylinderNumberType)0U; misfireConfirmedOrderIndex < misfireCylinderNum; misfireConfirmedOrderIndex++ )    /* [GUD:for]misfireConfirmedOrderIndex */
        {
            if( misfireComRecord.ConfirmedOrderCylList[misfireConfirmedOrderIndex] < misfireCylinderNum )   /* [GUD]misfireConfirmedOrderIndex *//* [ARYCHK] DEM_MISFIRE_CYLINDER_AND_RM_NUM / 1 / misfireConfirmedOrderIndex */
            {
                /* Set the bit at the number position of confirmed cylinder */
                currentConfirmedOccurrenceCylinder = currentConfirmedOccurrenceCylinder + ( DEM_MISFIRE_CHECK_CYLINDER_BIT << (misfireComRecord.ConfirmedOrderCylList[misfireConfirmedOrderIndex]) );   /* [GUD]misfireConfirmedOrderIndex *//* [ARYCHK] DEM_MISFIRE_CYLINDER_AND_RM_NUM / 1 / misfireConfirmedOrderIndex */
            }
            else
            {
                /* confirmed cylinder does not exist */
                break;
            }
        }

        if( misfireConfirmedOrderIndex < misfireCylinderNum )
        {
            /* If there is confirmed cylinder that is not registered in ConfirmedOrderCylList[] */

            /* currentConfirmedOccurrenceCylinder has already calculated Random Multiple Cylinder and remembers it,  */
            /* so there is no need to recalculate Random Multiple Cylinder */

            /* Get confirmed cylinder that is not registered in ConfirmedOrderCylList[ */
            addConfirmedOccurrenceCylinder = bit3Cylinder & ~currentConfirmedOccurrenceCylinder;

            if( addConfirmedOccurrenceCylinder != DEM_MISFIRE_CYLINDER_NON )
            {
                /* If there is a newly registered confirmed cylinder */

                for( addConfirmedCylinderNumber = DEM_MISFIRE_CYL_NUM_RM; addConfirmedCylinderNumber < misfireCylinderNum; addConfirmedCylinderNumber++ )
                {
                    /* Add unregistered confirmed cylinder number to ConfirmedOrderCylList[] */
                    if( ( addConfirmedOccurrenceCylinder & ( (Dem_MisfireCylinderType)(DEM_MISFIRE_CHECK_CYLINDER_BIT << addConfirmedCylinderNumber) ) ) != DEM_MISFIRE_CYLINDER_NON )
                    {
                        confirmedOccurrenceOrder = DEM_FAIL_OCCURRENCE_NUM_INVALID;
                        resultOfGetting = Dem_OdrLst_Confirmed_GetAndUpdateNextOccurrenceOrder( &confirmedOccurrenceOrder );
                        if( resultOfGetting == DEM_IRT_OK )
                        {
                            SchM_Enter_Dem_EventMemory();
                            Dem_MisfireMng_SetConfirmedOrderCyl( misfireConfirmedOrderIndex, addConfirmedCylinderNumber, confirmedOccurrenceOrder );
                            SchM_Exit_Dem_EventMemory();

                            misfireConfirmedOrderIndex = misfireConfirmedOrderIndex + (Dem_MisfireCylinderNumberType)1U;
                        }
                        else
                        {
                            /* If confirmed occurrence orde cannot get any more */
                            break;
                        }
                    }
                }
            }
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_Misfire_GetConfirmedUDSDTCAndOrder                   */
/* Description   | Get ConfirmedUDSDTC and ConfirmedOrder.                  */
/* Preconditions | none                                                     */
/* Parameters    | [in] MisfireConfirmedOrderIndex                          */
/*               | [out] ConfirmedDTCPtr :                                  */
/*               | [out] ConfirmedOccurrenceOrderPtr :                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |      DEM_IRT_OK :                                        */
/*               |      DEM_IRT_NO_MATCHING_ELEMENT :                       */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Misfire_GetConfirmedUDSDTCAndOrder
(
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) MisfireConfirmedOrderIndex,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) ConfirmedDTCPtr,
    P2VAR( Dem_u16_OccrOrderType, AUTOMATIC, AUTOMATIC ) ConfirmedOccurrenceOrderPtr
)
{
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) confirmedCylinderNumber;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireCylinderNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_MisfireKindBitType, AUTOMATIC ) availableMisfireKind;

    retVal = DEM_IRT_NO_MATCHING_ELEMENT;

    availableMisfireKind = Dem_DataAvl_GetMisfireCylDTCAvailable();
    if( availableMisfireKind != DEM_MISFIRE_KINDBIT_NONE )
    {
        misfireCylinderNum = Dem_MisfireCylinderNum;
        if( MisfireConfirmedOrderIndex < misfireCylinderNum )   /* [GUD:if]MisfireConfirmedOrderIndex */
        {
            confirmedCylinderNumber = Dem_MisfireMng_GetConfirmedOrderCyl( MisfireConfirmedOrderIndex );    /* [GUD]MisfireConfirmedOrderIndex */
            if( confirmedCylinderNumber < misfireCylinderNum )
            {
                *ConfirmedDTCPtr = Dem_CfgInfoPm_GetUdsDTCByMisfireCylinderNumber( confirmedCylinderNumber );
                *ConfirmedOccurrenceOrderPtr = Dem_MisfireMng_GetConfirmedOccurrenceOrder( MisfireConfirmedOrderIndex );    /* [GUD]MisfireConfirmedOrderIndex */

                retVal = DEM_IRT_OK;
            }
        }
    }

    return retVal;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */
#endif  /* ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT == STD_ON )  */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-6-0         :2024-01-29                                              */
/*  v5-7-0         :2024-05-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

