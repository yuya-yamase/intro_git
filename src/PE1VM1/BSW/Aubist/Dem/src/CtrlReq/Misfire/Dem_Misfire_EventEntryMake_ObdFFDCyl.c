/* Dem_Misfire_EventEntryMake_ObdFFDCyl_c(v5-9-0)                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Misfire_EventEntryMake_ObdFFDCyl/CODE                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
#if ( DEM_OBDFFD_SUPPORT == STD_ON )

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
/* Function Name | Dem_Misfire_SetObdFFDCylToTmp                            */
/* Description   | Set FFDCyl in the temporary area.                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in] MisfireObdFFDCylIndex :                             */
/*               | [in] FFDCyl :                                            */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_SetObdFFDCylToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) MisfireObdFFDCylIndex,      /* [PRMCHK:CALLER] */
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) FFDCyl
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvId;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndex;

    /*  convert id.     */
    retCnvId    =   Dem_CfgInfoPm_CnvEventStrgIndexToMisfireStrgIndex( EventStrgIndex, &misfireIndex );     /* [GUD:RET:DEM_IRT_OK] misfireIndex */
    if ( retCnvId == DEM_IRT_OK )
    {
        Dem_TmpMisfireEventMemoryEntry.MisfireRecord[ misfireIndex ].OBDFFDCyl[MisfireObdFFDCylIndex] = FFDCyl; /* [GUD] misfireIndex *//* [GUDCHK:CALLER]MisfireObdFFDCylIndex */
    }
    return;
}


/****************************************************************************/
/* Function Name | Dem_Misfire_GetObdFFDCylToTmp                            */
/* Description   | Get FFDCyl in the temporary area.                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in] MisfireObdFFDCylIndex :                             */
/*               | [out] FFDCylPtr :                                        */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_GetObdFFDCylToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) MisfireObdFFDCylIndex,      /* [PRMCHK:CALLER] */
    P2VAR( Dem_MisfireCylinderType, AUTOMATIC, AUTOMATIC ) FFDCylPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvId;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndex;

    /*  convert id.     */
    retCnvId    =   Dem_CfgInfoPm_CnvEventStrgIndexToMisfireStrgIndex( EventStrgIndex, &misfireIndex );     /* [GUD:RET:DEM_IRT_OK] misfireIndex */
    if ( retCnvId == DEM_IRT_OK )
    {
        *FFDCylPtr = Dem_TmpMisfireEventMemoryEntry.MisfireRecord[ misfireIndex ].OBDFFDCyl[ MisfireObdFFDCylIndex ];   /* [GUD] misfireIndex *//* [GUDCHK:CALLER]MisfireObdFFDCylIndex */
    }

    return;
}


#if ( DEM_OBDONUDS_SUPPORT == STD_ON )
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Misfire_GetPairObdFFDCylToTmp                        */
/* Description   | Get pair FFDCyl in the temporary area.                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in] MisfireObdFFDCylIndex :                             */
/*               | [out] FFDCylPtr :                                        */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-9-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_GetPairObdFFDCylToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) MisfireObdFFDCylIndex,      /* [PRMCHK:CALLER] */
    P2VAR( Dem_MisfireCylinderType, AUTOMATIC, AUTOMATIC ) FFDCylPtr
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) misfirePairEventStrgIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultGetMisfirePairEvent;

    resultGetMisfirePairEvent= Dem_CfgInfoPm_GetMisfirePairEventStrgIndexByStrgIndex( EventStrgIndex, &misfirePairEventStrgIndex );
    if( resultGetMisfirePairEvent == DEM_IRT_OK )
    {
        Dem_Misfire_GetObdFFDCylToTmp( misfirePairEventStrgIndex, MisfireObdFFDCylIndex, FFDCylPtr );   /* [GUDCHK:CALLER]MisfireObdFFDCylIndex */
    }

    return;
}
#endif /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON ) */
#endif /* ( DEM_OBDONUDS_SUPPORT == STD_ON ) */


/****************************************************************************/
/* Function Name | Dem_Misfire_SetMisfireKindOfObdFFDToTmp                  */
/* Description   | Set MisfireKindOfFFD in the temporary area.              */
/* Preconditions | none                                                     */
/* Parameters    | [in] MisfireObdFFDCylIndex :                             */
/*               | [in] MisfireKindOfFFD :                                  */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_SetMisfireKindOfObdFFDToTmp
(
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) MisfireObdFFDCylIndex,      /* [PRMCHK:CALLER] */
    VAR( Dem_u08_MisfireKindType, AUTOMATIC ) MisfireKindOfFFD
)
{
    Dem_TmpMisfireEventMemoryEntry.MisfireComRecord.MisfireKindOfOBDFFD[MisfireObdFFDCylIndex] = MisfireKindOfFFD;  /* [GUDCHK:CALLER]MisfireObdFFDCylIndex */

    return;
}


/****************************************************************************/
/* Function Name | Dem_Misfire_GetMisfireKindOfObdFFDToTmp                  */
/* Description   | Get MisfireKindOfFFD in the temporary area.              */
/* Preconditions | none                                                     */
/* Parameters    | [in] MisfireObdFFDCylIndex :                             */
/*               | [out] MisfireKindOfFFDPtr :                              */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_GetMisfireKindOfObdFFDToTmp
(
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) MisfireObdFFDCylIndex,      /* [PRMCHK:CALLER] */
    P2VAR( Dem_u08_MisfireKindType, AUTOMATIC, AUTOMATIC ) MisfireKindOfFFDPtr
)
{
    *MisfireKindOfFFDPtr = Dem_TmpMisfireEventMemoryEntry.MisfireComRecord.MisfireKindOfOBDFFD[MisfireObdFFDCylIndex];  /* [GUDCHK:CALLER]MisfireObdFFDCylIndex */

    return;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */
#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
