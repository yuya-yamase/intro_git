/* Dem_Misfire_EventEntryMake_FFDCyl_c(v5-5-0)                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Misfire_EventEntryMake_FFDCyl/CODE                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_Pm_Misfire.h"
#include "../../../inc/Dem_Rc_MisfireMng.h"
#include "Dem_Misfire_EventEntry_local.h"

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
/* Function Name | Dem_Misfire_SetFFDCylToTmp                               */
/* Description   | Set FFDCyl in the temporary area.                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in] MisfireFFDCylIndex :                                */
/*               | [in] FFDCyl :                                            */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_SetFFDCylToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) MisfireFFDCylIndex,        /* [PRMCHK:CALLER] */
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) FFDCyl
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvId;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndex;

    /*  convert id.     */
    retCnvId    =   Dem_CfgInfoPm_CnvEventStrgIndexToMisfireStrgIndex( EventStrgIndex, &misfireIndex );     /* [GUD:RET:DEM_IRT_OK] misfireIndex */

    if ( retCnvId == DEM_IRT_OK )
    {
        Dem_TmpMisfireEventMemoryEntry.MisfireRecord[ misfireIndex ].FFDCyl[MisfireFFDCylIndex] = FFDCyl;   /* [GUD] misfireIndex *//* [GUDCHK:CALLER]MisfireFFDCylIndex */
    }
    return;
}


/****************************************************************************/
/* Function Name | Dem_Misfire_GetFFDCylToTmp                               */
/* Description   | Get FFDCyl in the temporary area.                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in] MisfireFFDCylIndex :                                */
/*               | [out] FFDCylPtr :                                        */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_GetFFDCylToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) MisfireFFDCylIndex,        /* [PRMCHK:CALLER] */
    P2VAR( Dem_MisfireCylinderType, AUTOMATIC, AUTOMATIC ) FFDCylPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvId;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndex;

    /*  convert id.     */
    retCnvId    =   Dem_CfgInfoPm_CnvEventStrgIndexToMisfireStrgIndex( EventStrgIndex, &misfireIndex );     /* [GUD:RET:DEM_IRT_OK] misfireIndex */

    if ( retCnvId == DEM_IRT_OK )
    {
        *FFDCylPtr = Dem_TmpMisfireEventMemoryEntry.MisfireRecord[ misfireIndex ].FFDCyl[MisfireFFDCylIndex];   /* [GUD] misfireIndex *//* [GUDCHK:CALLER]MisfireFFDCylIndex */
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_Misfire_SetMisfireKindOfFFDToTmp                     */
/* Description   | Set MisfireKindOfFFD in the temporary area.              */
/* Preconditions | none                                                     */
/* Parameters    | [in] MisfireFFDCylIndex :                                */
/*               | [in] MisfireKindOfFFD :                                  */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_SetMisfireKindOfFFDToTmp
(
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) MisfireFFDCylIndex,        /* [PRMCHK:CALLER] */
    VAR( Dem_u08_MisfireKindType, AUTOMATIC ) MisfireKindOfFFD
)
{
    Dem_TmpMisfireEventMemoryEntry.MisfireComRecord.MisfireKindOfFFD[MisfireFFDCylIndex] = MisfireKindOfFFD;        /* [GUDCHK:CALLER]MisfireFFDCylIndex */

    return;
}


/****************************************************************************/
/* Function Name | Dem_Misfire_GetMisfireKindOfFFDToTmp                     */
/* Description   | Get MisfireKindOfFFD in the temporary area.              */
/* Preconditions | none                                                     */
/* Parameters    | [in] MisfireFFDCylIndex :                                */
/*               | [out] MisfireKindOfFFDPtr :                              */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_GetMisfireKindOfFFDToTmp
(
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) MisfireFFDCylIndex,        /* [PRMCHK:CALLER] */
    P2VAR( Dem_u08_MisfireKindType, AUTOMATIC, AUTOMATIC ) MisfireKindOfFFDPtr
)
{
    *MisfireKindOfFFDPtr = Dem_TmpMisfireEventMemoryEntry.MisfireComRecord.MisfireKindOfFFD[MisfireFFDCylIndex];    /* [GUDCHK:CALLER]MisfireFFDCylIndex */

    return;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
