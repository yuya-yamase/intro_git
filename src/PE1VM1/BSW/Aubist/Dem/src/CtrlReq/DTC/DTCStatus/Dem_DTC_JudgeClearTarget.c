/* Dem_DTC_JudgeClearTarget_c(v5-8-0)                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DTC_JudgeClearTarget/CODE                             */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../../inc/Dem_Pm_DTC.h"
#include "../../../../inc/Dem_CmnLib_Control.h"
#include "../../../../inc/Dem_CmnLib_ConfigInfo.h"

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
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>


/****************************************************************************/
/* Function Name | Dem_DTC_JudgeDTCClearTarget                              */
/* Description   | Judge if DTCinfo is a target for Clear                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the event ID.    */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : target to clear                           */
/*               |        FALSE : not target to clear                       */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-8-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_DTC_JudgeDTCClearTarget
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( boolean, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) execClearDTC;
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) getDTCGroup;
    VAR( Dem_DTCOriginType, AUTOMATIC ) getDTCOrigin;
    VAR( boolean, AUTOMATIC ) clearAllowed;
    VAR( boolean, AUTOMATIC ) eventOBDKind;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;

    retVal = (boolean)FALSE;

    eventStorageNum = Dem_PrimaryMemEventStorageNum;
    execClearDTC = Dem_Control_CheckExecClearDTCProcessActive();

    if( execClearDTC == (boolean)TRUE )
    {
        Dem_Control_GetClearType( &getDTCGroup, &getDTCOrigin );

        if( getDTCOrigin == DEM_DTC_ORIGIN_PRIMARY_MEMORY )
        {
            if( EventStrgIndex < eventStorageNum )                                                                  /* [GUD:if]EventStrgIndex */
            {
                clearAllowed = Dem_CfgInfoPm_ClearAllowed_InEvtStrgGrp( EventStrgIndex );

                if( clearAllowed == (boolean)TRUE )
                {
                    if( getDTCGroup == DEM_DTC_GROUP_EMISSION_REL_DTCS )
                    {
                        eventOBDKind = Dem_CfgInfoPm_CheckEventKindOfOBD_InEvtStrgGrp( EventStrgIndex );    /* [GUD]EventStrgIndex */

                        if( eventOBDKind == (boolean)TRUE )
                        {
                            retVal = (boolean)TRUE;
                        }
                    }
                    else
                    {
                        retVal = (boolean)TRUE;
                    }
                }
            }
        }
    }

    return retVal;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-8-0         :2024-10-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
