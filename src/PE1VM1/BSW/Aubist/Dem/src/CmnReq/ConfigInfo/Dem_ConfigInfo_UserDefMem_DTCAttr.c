/* Dem_ConfigInfo_c(v5-5-0)                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
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
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )

#include "../../../cfg/Dem_UserDefMem_Cfg.h"

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
/* Function Name | Dem_CfgInfoUdm_GetFreezeFrameClassRef                    */
/* Description   | GetData by UdmEventIndex : DemFreezeFrameClassRef        */
/* Preconditions | UdmEventIndex < Dem_UdmEventConfigureNum                 */
/* Parameters    | [in] UdmEventIndex :  UdmEventIndex                      */
/*               | [out] FFClassIndexPtr                                    */
/*               |     <  DEM_FFCLASSINDEX_INVALID  :valid                  */
/*               |     == DEM_FFCLASSINDEX_INVALID  :invalid                */
/* Return Value  | none.                                                    */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:Not DEM_FFCLASSINDEX_INVALID ] UdmEventIndex    */
/* VariableGuard | [GUD:RET:Not DEM_FFCLASSINDEX_INVALID ] FFClassIndexPtr  */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_CfgInfoUdm_GetFreezeFrameClassRef
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    P2VAR( Dem_u16_FFClassIndexType, AUTOMATIC, AUTOMATIC ) FFClassIndexPtr
)
{
    VAR( Dem_u16_UdmDTCAttrIndexType, AUTOMATIC ) dtcAttrRef;
    VAR( Dem_u16_FFClassIndexType, AUTOMATIC ) freezeFrameClassRef;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) eventConfigureNum;

    eventConfigureNum = Dem_UdmEventConfigureNum;

    freezeFrameClassRef =   DEM_FFCLASSINDEX_INVALID;

    if( UdmEventIndex < eventConfigureNum )                 /* [GUD:if]UdmEventIndex */
    {
        /*  get DTCAttributeTable index.            */
        dtcAttrRef    =   Dem_UdmEventParameterTable[ UdmEventIndex ].DemDTCAttributesRef;      /* [GUD]UdmEventIndex *//* [GUD:CFG:IF_GUARDED: UdmEventIndex ]dtcAttrRef */

        /*------------------------------------------------------------------------------------------------------*/
        /*  If UdmEventIndex do not have DTC Attribute, [dtcAttrRef] is point to the invalid information area.  */
        /*  Therefore, it's no need dtcAttrRef value area guard.                                                */
        /*------------------------------------------------------------------------------------------------------*/

        /* get the reference of freeze frame class. */
        freezeFrameClassRef   =   Dem_UdmDTCAttributeTable[ dtcAttrRef ].DemFreezeFrameClassRef;        /* [GUD]dtcAttrRef */
    }

    *FFClassIndexPtr    =   freezeFrameClassRef;

    return ;
}


/****************************************************************************/
/* Function Name | Dem_CfgInfoUdm_GetMemoryDestination                      */
/* Description   | GetData by UdmEventIndex : Dem_UdmDTCAttributeTable[].DemMemoryDestinationRef */
/* Preconditions | UdmEventIndex < Dem_UdmEventConfigureNum                 */
/* Parameters    | [in] UdmEventIndex :  UdmEventIndex                      */
/* Return Value  | Dem_u08_UdmMemoryInfoTableIndexType                      */
/*               |           Reference to Dem_UserDefinedMemoryInfoTable[]. */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:IF_GUARDED: UdmEventIndex ] ReturnValue         */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_UdmMemoryInfoTableIndexType, DEM_CODE ) Dem_CfgInfoUdm_GetMemoryDestination
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex           /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u16_UdmDTCAttrIndexType, AUTOMATIC ) dtcAttrRef;
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInfoTableIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndex;

    /*  get DTCAttributeTable index.            */
    dtcAttrRef    =   Dem_UdmEventParameterTable[ UdmEventIndex ].DemDTCAttributesRef;  /* [GUDCHK:CALLER]UdmEventIndex */

    /*  get udm group index.            */
    udmGroupKindIndex    =   Dem_UdmDTCAttributeTable[ dtcAttrRef ].DemMemoryDestinationRef;  /* [GUDCHK:CALLER]dtcAttrRef */

    /*  get udm info table index.            */
    udmInfoTableIndex    =   Dem_UserDefinedMemoryGroupTable[ udmGroupKindIndex ].DemUserDefinedMemoryInfoTableIndex;  /* [GUDCHK:CALLER]udmGroupKindIndex */

    return udmInfoTableIndex;
}


/****************************************************************************/
/* Function Name | Dem_CfgInfoUdm_GetMaxNumberFreezeFrameRecords            */
/* Description   | GetData by UdmEventIndex : Dem_UdmDTCAttributeTable[].DemMaxNumberFreezeFrameRecords */
/* Preconditions | UdmEventIndex < Dem_UdmEventConfigureNum                 */
/* Parameters    | [in] UdmEventIndex :  UdmEventIndex                      */
/* Return Value  | Dem_u16_UdmFFDIndexType                                  */
/*               |           Max number of freeze frame records.             */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:IF_GUARDED:UdmEventIndex] ReturnValue           */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u16_UdmFFDIndexType, DEM_CODE ) Dem_CfgInfoUdm_GetMaxNumberFreezeFrameRecords
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex
)
{
    VAR( Dem_u16_UdmDTCAttrIndexType, AUTOMATIC ) dtcAttrRef;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) maxNumberFreezeFrameRecords;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) eventConfigureNum;

    eventConfigureNum = Dem_UdmEventConfigureNum;

    maxNumberFreezeFrameRecords =   (Dem_u16_UdmFFDIndexType)0U;
    if( UdmEventIndex < eventConfigureNum )                 /* [GUD:if]UdmEventIndex */
    {
        /*  get DTCAttributeTable index.            */
        dtcAttrRef = Dem_UdmEventParameterTable[ UdmEventIndex ].DemDTCAttributesRef;       /* [GUD]UdmEventIndex *//* [GUD:CFG:IF_GUARDED: UdmEventIndex ]dtcAttrRef */

        /*  get config data.                        */
        maxNumberFreezeFrameRecords = Dem_UdmDTCAttributeTable[ dtcAttrRef ].DemMaxNumberFreezeFrameRecords;        /* [GUD]dtcAttrRef */
    }

    return maxNumberFreezeFrameRecords;
}

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetExDataClassRef                            */
/* Description   | GetData by EventIndex : Dem_UdmDTCAttributeTable[].DemExDataClassRef    */
/* Preconditions | UdmEventIndex < Dem_UdmEventConfigureNum                 */
/* Parameters    | [in] UdmEventIndex :  UdmEventIndex                      */
/*               | [out]ExDataClassRefPtr                                   */
/*               |      < DEM_EXDATACLASSINDEX_INVALID  : valid             */
/*               |     == DEM_EXDATACLASSINDEX_INVALID  : invalid           */
/* Return Value  | none.                                                    */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_CfgInfoUdm_GetExDataClassRef
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,          /* [PRMCHK:CALLER] */
    P2VAR( Dem_u16_ExDataClassIndexType, AUTOMATIC, AUTOMATIC ) ExDataClassRefPtr
)
{
    VAR( Dem_u16_DTCAttrIndexType, AUTOMATIC ) dtcAttrRef;

    /*  get DTCAttributeTable index.            */
    dtcAttrRef      =   Dem_UdmEventParameterTable[ UdmEventIndex ].DemDTCAttributesRef;    /* [GUDCHK:CALLER]UdmEventIndex *//* [GUD:CFG:IF_GUARDED: UdmEventIndex ]dtcAttrRef */

    /*------------------------------------------------------------------------------------------------------*/
    /*  If EventIndex do not have DTC Attribute, [dtcAttrRef] is point to the invalid information area.     */
    /*  Therefore, it's no need dtcAttrRef value area guard.                                                */
    /*------------------------------------------------------------------------------------------------------*/

    /*  get config data.                        */
    *ExDataClassRefPtr    =   Dem_UdmDTCAttributeTable[ dtcAttrRef ].DemExDataClassRef;     /* [GUDCHK:CALLER]UdmEventIndex */

    return ;
}


#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_CfgInfoUdm_GetMaxNumberFreezeFrameRecords            */
/* Description   | GetData by UdmEventIndex : Dem_UdmDTCAttributeTable[].DemTimeSeriesFreezeFrameRecordClassRef */
/* Preconditions | UdmEventIndex < Dem_UdmEventConfigureNum                 */
/* Parameters    | [in] UdmEventIndex :  UdmEventIndex                      */
/* Return Value  | Dem_u16_TSFFRecClassIndexType                            */
/*               |           Reference to Dem_TSFFRecordClassTable[].       */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:IF_GUARDED: UdmEventIndex ] ReturnValue         */
/* VariableGuard | [GUD:RET:Not DEM_TSFF_RECORD_CLASS_REF_INVALID ] ReturnValue   */
/* VariableGuard | [GUD:RET:Not DEM_TSFF_RECORD_CLASS_REF_INVALID ] UdmEventIndex */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u16_TSFFRecClassIndexType, DEM_CODE ) Dem_CfgInfoUdm_GetTimeSeriesFreezeFrameRecordClassRef
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex
)
{
    VAR( Dem_u16_UdmDTCAttrIndexType, AUTOMATIC ) dtcAttrRef;
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) tsffRecordClassRef;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) eventConfigureNum;

    eventConfigureNum = Dem_UdmEventConfigureNum;

    tsffRecordClassRef  =   DEM_TSFF_RECORD_CLASS_REF_INVALID;

    if ( UdmEventIndex < eventConfigureNum )                                                /* [GUD:if]UdmEventIndex */
    {
        /*  get DTCAttributeTable index.            */
        dtcAttrRef = Dem_UdmEventParameterTable[ UdmEventIndex ].DemDTCAttributesRef;       /* [GUD]UdmEventIndex *//* [GUD:CFG:IF_GUARDED: UdmEventIndex ]dtcAttrRef */

        /*  get config data.                        */
        tsffRecordClassRef = Dem_UdmDTCAttributeTable[ dtcAttrRef ].DemTimeSeriesFreezeFrameRecordClassRef;     /* [GUD]dtcAttrRef */
    }

    return tsffRecordClassRef;
}
#endif /* ( DEM_TSFF_UDM_SUPPORT == STD_ON ) */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )      */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
