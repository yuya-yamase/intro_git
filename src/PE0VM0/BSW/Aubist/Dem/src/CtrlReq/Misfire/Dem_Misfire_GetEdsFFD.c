/* Dem_Misfire_GetEdsFFD_c(v5-5-0)                                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Misfire_GetEdsFFD/CODE                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../cfg/Dem_NvM_Cfg.h"
#include "../../../inc/Dem_Pm_Misfire.h"
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
#if ( DEM_OBDONEDS_SUPPORT == STD_ON )
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

static FUNC( Dem_MisfireCylinderNumberType, DEM_CODE ) Dem_Misfire_GetMisfireObdFFDCylIndex
( void );

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
/* Function Name | Dem_Misfire_GetEdsDTCOfOBDFreezeFrame                    */
/* Description   | Judge the event index is a misfire and                   */
/*               | get DTC of the failed cylinder.                          */
/* Preconditions | none                                                     */
/* Parameters    | [out] DTCValuePtr :                                      */
/*               |          Dtc                                             */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK                  : misfire             */
/*               |        DEM_IRT_NO_MATCHING_ELEMENT : no misfire          */
/*               |        DEM_IRT_NG                  : faild               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Misfire_GetEdsDTCOfOBDFreezeFrame
(
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireCylinderNumberOutput;
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) misfireObdFFDCylIndexNum;
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) misfireObdFFDCylIndex;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndexObdFFDConfig;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) misfireObdFFDCyl;

    retVal = DEM_IRT_NG;

    misfireObdFFDCylIndexNum    = Dem_MisfireObdFFDCylIndexNum;
    misfireObdFFDCylIndex       = Dem_Misfire_GetMisfireObdFFDCylIndex();

    if( misfireObdFFDCylIndex < misfireObdFFDCylIndexNum )
    {
        misfireIndexObdFFDConfig = Dem_Misfire_GetMisfireStrgIndexOfStoredObdFFD( misfireObdFFDCylIndex );

        if( misfireIndexObdFFDConfig != DEM_MISFIRE_STRGINDEX_INVALID )
        {
            misfireObdFFDCyl                =   Dem_MisfireMng_GetObdFFDCyl( misfireIndexObdFFDConfig, misfireObdFFDCylIndex );
            misfireCylinderNumberOutput     =   Dem_CfgInfoPm_GetMisfireCylinderNumberFromCylBit( misfireObdFFDCyl );

            if( misfireCylinderNumberOutput != DEM_MISFIRE_CYL_NUM_INVALID )
            {
                *DTCValuePtr    =   Dem_CfgInfoPm_GetOBDDTCByMisfireCylinderNumber( misfireCylinderNumberOutput );
                retVal = DEM_IRT_OK;
            }
        }
    }
    return retVal;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Dem_Misfire_GetMisfireObdFFDCylIndex                     */
/* Description   | Get misfire OBD FFD cylinder index                       */
/* Preconditions | none                                                     */
/* Parameters    | [in] MisfireObdFFDCylIndex :                             */
/*               |          Misfire OBD FFD cylinder index                  */
/* Return Value  | Dem_u08_MisfireObdFFDCylIndexType                        */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( Dem_MisfireCylinderNumberType, DEM_CODE ) Dem_Misfire_GetMisfireObdFFDCylIndex
( void )
{
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) retMisfireObdFFDCylIndex;

    retMisfireObdFFDCylIndex = Dem_CfgInfoPm_GetObdFFDCylIndexOfMisfire( DEM_TRIGGER_ON_CONFIRMED );

    if( retMisfireObdFFDCylIndex == DEM_MISFIRE_OBD_FFDCYL_INDEX_INVALID )
    {
        retMisfireObdFFDCylIndex = Dem_CfgInfoPm_GetObdFFDCylIndexOfMisfire( DEM_TRIGGER_ON_PENDING );
    }

    return retMisfireObdFFDCylIndex;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_OBDONEDS_SUPPORT == STD_ON )             */
#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-1-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
