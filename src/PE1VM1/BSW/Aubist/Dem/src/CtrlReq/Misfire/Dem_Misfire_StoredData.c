/* Dem_Misfire_StoredData_c(v5-5-0)                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Dem_Misfire_StoredData/CODE                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#if ( DEM_DTCSTOREDDATA_DEMINTERNAL_SUPPORT == STD_ON )
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_Pm_Misfire.h"
#include "../../../inc/Dem_Rc_MisfireMng.h"
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

static VAR( boolean, DEM_VAR_NO_INIT ) Dem_Misfire_CompletedOutputStoredDataFlag;


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_Misfire_InitOutputStoredData                         */
/* Description   | Initialize data.                                         */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_InitOutputStoredData
( void )
{
    Dem_Misfire_CompletedOutputStoredDataFlag = (boolean)FALSE;

    return;
}


/****************************************************************************/
/* Function Name | Dem_Misfire_CheckOutputStoredData                        */
/* Description   | Check if StoredData can be output if Event is Misfire    */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        Event index.                                      */
/* Return Value  | boolean                                                  */
/*               |        TRUE : StoredData can be output                   */
/*               |        FALSE : StoredData cannot be output               */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_Misfire_CheckOutputStoredData
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( boolean, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvId;

    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) misfireFFDCylIndexNum;
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) misfireConfirmedFFDCylIndex;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndex;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndexForOutputOfConfirmedFFD;

    retVal = (boolean)FALSE;

    if( Dem_Misfire_CompletedOutputStoredDataFlag != (boolean)TRUE )
    {
        misfireFFDCylIndexNum = Dem_MisfireFFDCylIndexNum;
        misfireConfirmedFFDCylIndex = Dem_MisfireFFDCylIndexConfirmed;
        /* Check that Misfire has ConfirmedFFD configured */
        if( misfireConfirmedFFDCylIndex < misfireFFDCylIndexNum )
        {
            retCnvId = Dem_CfgInfoPm_CnvEventStrgIndexToMisfireStrgIndex( EventStrgIndex, &misfireIndex );
            /* The caller has already checked that EventStrgIndex is Misfire, so it cannot fail */
            if( retCnvId == DEM_IRT_OK )
            {
                misfireIndexForOutputOfConfirmedFFD = Dem_Misfire_GetMisfireStrgIndexOfStoredFFD( misfireConfirmedFFDCylIndex );
                if( misfireIndex == misfireIndexForOutputOfConfirmedFFD )
                {
                    retVal = (boolean)TRUE;
                }
            }
        }
    }


    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Misfire_CompletedOutputStoredData                    */
/* Description   | Completion of output processing from Misfire to StoredD- */
/*               | ata.                                                     */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_CompletedOutputStoredData
( void )
{

    Dem_Misfire_CompletedOutputStoredDataFlag = (boolean)TRUE;

    return;
}


/****************************************************************************/
/* Function Name | Dem_Misfire_GetDTCAndStatusOfStoredData                  */
/* Description   | Get DTC and Status of Misfire for StoredData             */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        Event index.                                      */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_GetDTCAndStatusOfStoredData
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
)
{
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) misfireFFDCy;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvId;
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) misfireFFDCylIndexNum;
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) misfireConfirmedFFDCylIndex;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireCylinderNum;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireCylinderNumber;

    retCnvId = Dem_CfgInfoPm_CnvEventStrgIndexToMisfireStrgIndex( EventStrgIndex, &misfireIndex );
    if( retCnvId == DEM_IRT_OK )
    {
        misfireFFDCylIndexNum = Dem_MisfireFFDCylIndexNum;
        misfireConfirmedFFDCylIndex = Dem_MisfireFFDCylIndexConfirmed;
        /* If Confirmed FFD or Confirmed TSFFD does not exist, this process will not come,  */
        /* but if Confirmed FFD is not configured, out-of-range access may occur during processing, so insert guard processing */
        if( misfireConfirmedFFDCylIndex < misfireFFDCylIndexNum )
        {
            misfireCylinderNum = Dem_MisfireCylinderNum;
            misfireFFDCy = Dem_MisfireMng_GetFFDCyl( misfireIndex, misfireConfirmedFFDCylIndex );
            misfireCylinderNumber = Dem_CfgInfoPm_GetMisfireCylinderNumberFromCylBit( misfireFFDCy );
            if( misfireCylinderNumber < misfireCylinderNum )
            {
                *DTCValuePtr = Dem_CfgInfoPm_GetUdsDTCByMisfireCylinderNumber( misfireCylinderNumber );
                *DTCStatusPtr = Dem_Misfire_GetCylinderDTCStatus( misfireCylinderNumber );
                /* Since it is mutually guarded with clear processing, correspondence during clear execution is not included */
            }
        }
    }

    return;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */
#endif  /* ( DEM_DTCSTOREDDATA_DEMINTERNAL_SUPPORT == STD_ON )     */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

