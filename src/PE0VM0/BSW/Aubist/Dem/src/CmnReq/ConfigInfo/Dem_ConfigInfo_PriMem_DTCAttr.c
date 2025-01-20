/* Dem_ConfigInfo_c(v5-5-0)                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/ConfigInfo/CODE                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../cfg/Dem_Data_Cfg.h"
#include "../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"

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

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_CfgInfoPm_GetOBDFFClassRefAndFFRecNumClassRef
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u16_FFClassIndexType, AUTOMATIC, AUTOMATIC ) ObdFFClassIndexPtr,
    P2VAR( Dem_u16_FFRecNumClassIndexType, AUTOMATIC, AUTOMATIC ) ObdFFRecNumClassIndexPtr
);
#endif  /*  ( DEM_OBDFFD_SUPPORT == STD_ON )   */

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
/* Function Name | Dem_CfgInfoPm_GetFreezeFrameAndRecNumClass                 */
/* Description   | GetData by EventIndex : DemFreezeFrameClassRef and DemFreezeFrameRecNumClassRef */
/* Preconditions | EventIndex < Dem_PrimaryMemEventConfigureNum                       */
/* Parameters    | [in] EventIndex :  EventIndex                            */
/*               | [out] FFClassIndexPtr                                    */
/*               |     <  DEM_FFCLASSINDEX_INVALID  :valid                  */
/*               |     == DEM_FFCLASSINDEX_INVALID  :invalid                */
/*               | [out] FFRecNumClassIndexPtr                              */
/*               |     <  DEM_FFRECNUMCLASSINDEX_INVALID  :valid            */
/*               |     == DEM_FFRECNUMCLASSINDEX_INVALID  :invalid          */
/* Return Value  | none.                                                    */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:OUT:IF_GUARDED: EventStrgIndex ] FFClassIndexPtr                */
/* VariableGuard | [GUD:OUT:IF_GUARDED: EventStrgIndex ] FFRecNumClassIndexPtr          */
/* VariableGuard | [GUD:OUT:Not DEM_FFCLASSINDEX_INVALID] FFClassIndexPtr               */
/* VariableGuard | [GUD:OUT:Not DEM_FFRECNUMCLASSINDEX_INVALID] FFRecNumClassIndexPtr   */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_CfgInfoPm_GetFreezeFrameAndRecNumClass
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u16_FFClassIndexType, AUTOMATIC, AUTOMATIC ) FFClassIndexPtr,
    P2VAR( Dem_u16_FFRecNumClassIndexType, AUTOMATIC, AUTOMATIC ) FFRecNumClassIndexPtr
)
{
    VAR( Dem_u16_DTCAttrIndexType, AUTOMATIC ) dtcAttrRef;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u16_FFClassIndexType, AUTOMATIC ) ffClassIndex;
    VAR( Dem_u16_FFRecNumClassIndexType, AUTOMATIC ) ffRecNumClassIndex;

    eventStorageNum         =   Dem_PrimaryMemEventStorageNum;
    ffClassIndex            =   DEM_FFCLASSINDEX_INVALID;
    ffRecNumClassIndex      =   DEM_FFRECNUMCLASSINDEX_INVALID;

    if ( EventStrgIndex < eventStorageNum )                                                                 /* [GUD:if]EventStrgIndex */
    {
        /*  get DTCAttributeTable index.            */
        dtcAttrRef    =   Dem_EventParameterStorageTable[ EventStrgIndex ].DemDTCAttributesRef;             /* [GUD]EventStrgIndex *//* [GUD:CFG:IF_GUARDED: EventStrgIndex ]dtcAttrRef */

        /*------------------------------------------------------------------------------------------------------*/
        /*  If EventIndex do not have DTC Attribute, [dtcAttrRef] is point to the invalid information area.     */
        /*  Therefore, it's no need dtcAttrRef value area guard.                                                */
        /*------------------------------------------------------------------------------------------------------*/

        /* get the reference of freeze frame class. */
        ffClassIndex   =   Dem_DTCAttributeTable[ dtcAttrRef ].DemFreezeFrameClassRef;                      /* [GUD]dtcAttrRef */

        /*  get config data.                        */
        ffRecNumClassIndex   =   Dem_DTCAttributeTable[ dtcAttrRef ].DemFreezeFrameRecNumClassRef;          /* [GUD]dtcAttrRef */
    }

    *FFClassIndexPtr        =   ffClassIndex;
    *FFRecNumClassIndexPtr  =   ffRecNumClassIndex;

    return ;
}

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetNumOfFreezeFrameRecordClass             */
/* Description   | GetNumber of FreezeFrameRecordClass.(total and perDTC)   */
/* Preconditions |                                                          */
/* Parameters    | [out] FFRClassConfigureNumPtr                            */
/*               |     Number of Configured FreezeFrameRecordClass          */
/*               | [out] OBDFFRClassPerDTCMaxNumPtr                         */
/*               |     Number of FreezeFrameRecordClass per DTC.            */
/* Return Value  | none.                                                    */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_CfgInfoPm_GetNumOfFreezeFrameRecordClass
(
    P2VAR( Dem_u08_FFRecordClassIndexType, AUTOMATIC, AUTOMATIC ) FFRClassConfigureNumPtr,
    P2VAR( Dem_u08_FFListIndexType, AUTOMATIC, AUTOMATIC ) FFRClassPerDTCMaxNumPtr
)
{
    *FFRClassConfigureNumPtr    =   Dem_FFRRecordClassConfigureNum;
    *FFRClassPerDTCMaxNumPtr    =   Dem_NonOBDFFRClassPerDTCMaxNum;

    return ;
}

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetOBDFreezeFrameAndRecNumClassForClear    */
/* Description   | GetData by EventIndex : DemOBDFreezeFrameClassRef and DemOBDFreezeFrameRecNumClassRef */
/* Preconditions | EventIndex < Dem_PrimaryMemEventConfigureNum                       */
/* Parameters    | [in] EventIndex :  EventIndex                            */
/*               | [out] ObdFFClassIndexPtr                                 */
/*               |     <  DEM_FFCLASSINDEX_INVALID  :valid                  */
/*               |     == DEM_FFCLASSINDEX_INVALID  :invalid                */
/*               | [out] ObdFFRecNumClassIndexPtr                           */
/*               |     <  DEM_FFRECNUMCLASSINDEX_INVALID  :valid            */
/*               |     == DEM_FFRECNUMCLASSINDEX_INVALID  :invalid          */
/* Return Value  | none.                                                    */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:OUT:Not DEM_FFCLASSINDEX_INVALID] ObdFFClassIndexPtr                */
/* VariableGuard | [GUD:OUT:Not DEM_FFRECNUMCLASSINDEX_INVALID] ObdFFRecNumClassIndexPtr    */
/* VariableGuard | [GUD:OUT:Not DEM_FFCLASSINDEX_INVALID] EventStrgIndex          */
/* VariableGuard | [GUD:OUT:Not DEM_FFRECNUMCLASSINDEX_INVALID] EventStrgIndex    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_CfgInfoPm_GetOBDFreezeFrameAndRecNumClass. */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_CfgInfoPm_GetOBDFreezeFrameAndRecNumClassForClear
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u16_FFClassIndexType, AUTOMATIC, AUTOMATIC ) ObdFFClassIndexPtr,
    P2VAR( Dem_u16_FFRecNumClassIndexType, AUTOMATIC, AUTOMATIC ) ObdFFRecNumClassIndexPtr
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u16_FFClassIndexType, AUTOMATIC ) obdFFClassIndex;
    VAR( Dem_u16_FFRecNumClassIndexType, AUTOMATIC ) obdFFRecNumClassIndex;

    eventStorageNum         =   Dem_PrimaryMemEventStorageNum;
    obdFFClassIndex         =   DEM_FFCLASSINDEX_INVALID;
    obdFFRecNumClassIndex   =   DEM_FFRECNUMCLASSINDEX_INVALID;

    if ( EventStrgIndex < eventStorageNum )                                                                             /* [GUD:if]EventStrgIndex */
    {
        Dem_CfgInfoPm_GetOBDFFClassRefAndFFRecNumClassRef( EventStrgIndex, &obdFFClassIndex, &obdFFRecNumClassIndex );  /* [GUD]EventStrgIndex */
    }

    *ObdFFClassIndexPtr         =   obdFFClassIndex;
    *ObdFFRecNumClassIndexPtr   =   obdFFRecNumClassIndex;

    return ;
}


/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetOBDFreezeFrameAndRecNumClass            */
/* Description   | GetData by EventIndex only OBD-DTC :                     */
/*               | DemOBDFreezeFrameClassRef and DemOBDFreezeFrameRecNumClassRef */
/* Preconditions | EventStrgIndex < Dem_PrimaryMemEventConfigureNum         */
/* Parameters    | [in] EventStrgIndex :  EventStrgIndex                    */
/*               | [out] ObdFFClassIndexPtr                                 */
/*               |     <  DEM_FFCLASSINDEX_INVALID  :valid                  */
/*               |     == DEM_FFCLASSINDEX_INVALID  :invalid                */
/*               | [out] ObdFFRecNumClassIndexPtr                           */
/*               |     <  DEM_FFRECNUMCLASSINDEX_INVALID  :valid            */
/*               |     == DEM_FFRECNUMCLASSINDEX_INVALID  :invalid          */
/* Return Value  | none.                                                    */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:OUT:Not DEM_FFCLASSINDEX_INVALID] ObdFFClassIndexPtr                */
/* VariableGuard | [GUD:OUT:Not DEM_FFRECNUMCLASSINDEX_INVALID] ObdFFRecNumClassIndexPtr    */
/* VariableGuard | [GUD:OUT:Not DEM_FFCLASSINDEX_INVALID] EventStrgIndex          */
/* VariableGuard | [GUD:OUT:Not DEM_FFRECNUMCLASSINDEX_INVALID] EventStrgIndex    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | refactor function.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_CfgInfoPm_GetOBDFreezeFrameAndRecNumClass
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u16_FFClassIndexType, AUTOMATIC, AUTOMATIC ) ObdFFClassIndexPtr,
    P2VAR( Dem_u16_FFRecNumClassIndexType, AUTOMATIC, AUTOMATIC ) ObdFFRecNumClassIndexPtr
)
{
    VAR( boolean, AUTOMATIC ) isObdDTC;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u16_FFClassIndexType, AUTOMATIC ) obdFFClassIndex;
    VAR( Dem_u16_FFRecNumClassIndexType, AUTOMATIC ) obdFFRecNumClassIndex;

    eventStorageNum         =   Dem_PrimaryMemEventStorageNum;
    obdFFClassIndex         =   DEM_FFCLASSINDEX_INVALID;
    obdFFRecNumClassIndex   =   DEM_FFRECNUMCLASSINDEX_INVALID;

    if ( EventStrgIndex < eventStorageNum )                                                                                 /* [GUD:if]EventStrgIndex */
    {
        isObdDTC = Dem_CfgInfoPm_CheckEventKindOfOBD_InEvtStrgGrp( EventStrgIndex );                                        /* [GUD]EventStrgIndex */
        if ( isObdDTC == (boolean)TRUE )
        {
            Dem_CfgInfoPm_GetOBDFFClassRefAndFFRecNumClassRef( EventStrgIndex, &obdFFClassIndex, &obdFFRecNumClassIndex );  /* [GUD]EventStrgIndex */
        }
    }

    *ObdFFClassIndexPtr         =   obdFFClassIndex;
    *ObdFFRecNumClassIndexPtr   =   obdFFRecNumClassIndex;

    return ;
}


/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetOBDFFClassRefAndFFRecNumClassRef        */
/* Description   | GetData by EventIndex only OBD-DTC :                     */
/*               | DemOBDFreezeFrameClassRef and DemOBDFreezeFrameRecNumClassRef */
/* Preconditions | EventStrgIndex < Dem_PrimaryMemEventConfigureNum         */
/* Parameters    | [in] EventStrgIndex :  EventStrgIndex                    */
/*               | [out] ObdFFClassIndexPtr                                 */
/*               |     <  DEM_FFCLASSINDEX_INVALID  :valid                  */
/*               |     == DEM_FFCLASSINDEX_INVALID  :invalid                */
/*               | [out] ObdFFRecNumClassIndexPtr                           */
/*               |     <  DEM_FFRECNUMCLASSINDEX_INVALID  :valid            */
/*               |     == DEM_FFRECNUMCLASSINDEX_INVALID  :invalid          */
/* Return Value  | none.                                                    */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:OUT:Not DEM_FFCLASSINDEX_INVALID] ObdFFClassIndexPtr                */
/* VariableGuard | [GUD:OUT:Not DEM_FFRECNUMCLASSINDEX_INVALID] ObdFFRecNumClassIndexPtr    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_CfgInfoPm_GetOBDFFClassRefAndFFRecNumClassRef
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,            /* [PRMCHK:CALLER] */
    P2VAR( Dem_u16_FFClassIndexType, AUTOMATIC, AUTOMATIC ) ObdFFClassIndexPtr,
    P2VAR( Dem_u16_FFRecNumClassIndexType, AUTOMATIC, AUTOMATIC ) ObdFFRecNumClassIndexPtr
)
{
    VAR( Dem_u16_DTCAttrIndexType, AUTOMATIC ) dtcAttrRef;

    /*  get DTCAttributeTable index.            */
    dtcAttrRef    =   Dem_EventParameterStorageTable[ EventStrgIndex ].DemDTCAttributesRef;                     /* [GUDCHK:CALLER]EventStrgIndex *//* [GUD:CFG:IF_GUARDED: EventStrgIndex ]dtcAttrRef */

    /*------------------------------------------------------------------------------------------------------*/
    /*  If EventIndex do not have DTC Attribute, [dtcAttrRef] is point to the invalid information area.     */
    /*  Therefore, it's no need dtcAttrRef value area guard.                                                */
    /*------------------------------------------------------------------------------------------------------*/

    /* get the reference of freeze frame class. */
    ( *ObdFFClassIndexPtr ) =   Dem_DTCAttributeTable[ dtcAttrRef ].DemOBDFreezeFrameClassRef;                  /* [GUD]dtcAttrRef */

    /*  get config data.                        */
    ( *ObdFFRecNumClassIndexPtr )   =   Dem_DTCAttributeTable[ dtcAttrRef ].DemOBDFreezeFrameRecNumClassRef;    /* [GUD]dtcAttrRef */

    return ;
}


/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetNumOfOBDFreezeFrameRecordClass            */
/* Description   | GetNumber of FreezeFrameRecordClass.(total and perDTC)   */
/* Preconditions |                                                          */
/* Parameters    | [out] FFRClassConfigureNumPtr                            */
/*               |     Number of Configured FreezeFrameRecordClass          */
/*               | [out] OBDFFRClassPerDTCMaxNumPtr                         */
/*               |     Number of FreezeFrameRecordClass per DTC.            */
/* Return Value  | none.                                                    */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_CfgInfoPm_GetNumOfOBDFreezeFrameRecordClass
(
    P2VAR( Dem_u08_FFRecordClassIndexType, AUTOMATIC, AUTOMATIC ) FFRClassConfigureNumPtr,
    P2VAR( Dem_u08_FFListIndexType, AUTOMATIC, AUTOMATIC ) OBDFFRClassPerDTCMaxNumPtr
)
{
    *FFRClassConfigureNumPtr    =   Dem_FFRRecordClassConfigureNum;
    *OBDFFRClassPerDTCMaxNumPtr =   Dem_OBDFFRClassPerDTCMaxNum;

    return ;
}
#endif  /*  ( DEM_OBDFFD_SUPPORT == STD_ON )   */


/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetExDataClassRef                            */
/* Description   | GetData by EventIndex : Dem_DTCAttributeTable[].DemExDataClassRef    */
/* Preconditions | EventIndex < Dem_PrimaryMemEventConfigureNum                       */
/* Parameters    | [in] EventCtrlIndex :  EventCtrlIndex                            */
/*               | [out]ExDataClassRefPtr                                   */
/*               |      < DEM_EXDATACLASSINDEX_INVALID  : valid             */
/*               |     == DEM_EXDATACLASSINDEX_INVALID  : invalid           */
/* Return Value  | none.                                                    */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_CfgInfoPm_GetExDataClassRef
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,            /* [PRMCHK:CALLER] */
    P2VAR( Dem_u16_ExDataClassIndexType, AUTOMATIC, AUTOMATIC ) ExDataClassRefPtr
)
{
    VAR( Dem_u16_DTCAttrIndexType, AUTOMATIC ) dtcAttrRef;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;

    /*  get DTCAttributeTable index.            */
    eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( EventCtrlIndex );                    /* [GUDCHK:CALLER]EventCtrlIndex *//* [GUD:RET:IF_GUARDED: EventCtrlIndex ]eventStrgIndex */
    dtcAttrRef      =   Dem_EventParameterStorageTable[ eventStrgIndex ].DemDTCAttributesRef;               /* [GUDCHK:CALLER]EventCtrlIndex */

    /*------------------------------------------------------------------------------------------------------*/
    /*  If EventIndex do not have DTC Attribute, [dtcAttrRef] is point to the invalid information area.     */
    /*  Therefore, it's no need dtcAttrRef value area guard.                                                */
    /*------------------------------------------------------------------------------------------------------*/

    /*  get config data.                        */
    *ExDataClassRefPtr    =   Dem_DTCAttributeTable[ dtcAttrRef ].DemExDataClassRef;                        /* [GUDCHK:CALLER]EventCtrlIndex */

    return ;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
