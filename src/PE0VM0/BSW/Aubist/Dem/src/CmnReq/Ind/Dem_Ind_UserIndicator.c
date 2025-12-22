/* Dem_Ind_UserIndicator_c(v5-9-0)                                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Ind_UserIndicator/CODE                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../cfg/Dem_Indicator_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../inc/Dem_CmnLib_DataAvl.h"
#include "../../../inc/Dem_Pm_Ind.h"
#include "../../../inc/Dem_Udm_Ind.h"
#include "Dem_Ind_cmn_local.h"

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

#if ( DEM_USER_DEFINED_INDICATOR_SUPPORT == STD_ON )
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Ind_GetUserDefinedIndicatorWIRStatus
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    P2VAR( Dem_IndicatorStatusType, AUTOMATIC, AUTOMATIC ) IndicatorStatusPtr
);
#endif  /* ( DEM_USER_DEFINED_INDICATOR_SUPPORT == STD_ON )   */


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



#if ( DEM_USER_DEFINED_INDICATOR_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Ind_GetUserDefinedIndicatorStatus                    */
/* Description   | Get UserDefined Indicator Status by Indicator Id.        */
/* Preconditions | none                                                     */
/* Parameters    | [in]  IndicatorId :                                      */
/*               |        Indicator Id.                                     */
/*               | [out] IndicatorStatusPtr                                 */
/*               |          DEM_INDICATOR_OFF        : Indicator Off        */
/*               |          DEM_INDICATOR_CONTINUOUS : Indicator On         */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Success.                             */
/*               |        DEM_IRT_NG : Failed.                              */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/*   v5-8-0      | no object changed.                                       */
/*   v5-9-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Ind_GetUserDefinedIndicatorStatus
(
    VAR( Dem_u08_IndicatorIdType, AUTOMATIC ) IndicatorId,
    P2VAR( Dem_IndicatorStatusType, AUTOMATIC, AUTOMATIC ) IndicatorStatusPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) loopCount;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndexNum;
    VAR( Dem_u08_IndicatorInfoIndexType, AUTOMATIC ) indicatorConfigureNum;
    P2CONST( AB_83_ConstV Dem_u16_EventCtrlIndexType, AUTOMATIC, DEM_CONFIG_DATA ) eventIdxListPtr;
    VAR( boolean, AUTOMATIC ) availableStatus;

    retVal = DEM_IRT_NG;
    indicatorConfigureNum = Dem_IndicatorInfoConfigureNum;

    *IndicatorStatusPtr = DEM_INDICATOR_OFF;

    if ( IndicatorId < indicatorConfigureNum )                              /* [GUD:if]IndicatorId */
    {
        eventCtrlIndexNum = Dem_IndicatorInfoTable[IndicatorId].EventNum;                                   /* [GUD]IndicatorId */
        eventIdxListPtr = Dem_IndicatorInfoTable[IndicatorId].EventIdxListPtr;                              /* [GUD]IndicatorId */

        for( loopCount = (Dem_u16_EventCtrlIndexType)0U ; loopCount < eventCtrlIndexNum ; loopCount++ )     /* [GUD:for]loopCount */
        {
            eventCtrlIndex = (Dem_u16_EventCtrlIndexType)eventIdxListPtr[loopCount];                        /* [GUD]loopCount *//* [ARYCHK] eventCtrlIndexNum / 1 / loopCount *//* [ARYDESC] Dem_IndicatorInfoTable[].EventIdxListPtr size is output in Dem_IndicatorInfoTable[].EventNum. */

            availableStatus = Dem_DataAvl_GetEvtAvlCommon( eventCtrlIndex );

            if( availableStatus == (boolean)TRUE )
            {
                (void)Dem_Ind_GetUserDefinedIndicatorWIRStatus( eventCtrlIndex, IndicatorStatusPtr );    /* no return check required */
                if( *IndicatorStatusPtr == DEM_INDICATOR_CONTINUOUS )
                {
                    break;
                }
            }
        }
        retVal = DEM_IRT_OK;
    }
    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Ind_GetUserDefinedIndicatorStatusByEventCtrlIndex    */
/* Description   | Get UserDefined Indicator Status by Indicator Id.        */
/* Preconditions | none                                                     */
/* Parameters    | [in]  EventCtrlIndex :                                   */
/*               |        event Id.                                         */
/*               | [in]  IndicatorId :                                      */
/*               |        Indicator Id.                                     */
/*               | [out] IndicatorStatusPtr                                 */
/*               |          DEM_INDICATOR_OFF        : Indicator Off        */
/*               |          DEM_INDICATOR_CONTINUOUS : Indicator On         */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Success.                             */
/*               |        DEM_IRT_NG : Failed.                              */
/* Notes         |                                                          */
/*               |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/*   v5-8-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Ind_GetUserDefinedIndicatorStatusByEventCtrlIndex
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( Dem_u08_IndicatorIdType, AUTOMATIC ) IndicatorId,
    P2VAR( Dem_IndicatorStatusType, AUTOMATIC, AUTOMATIC ) IndicatorStatusPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retResult;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) loopCount;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndexInTable;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndexNum;
    VAR( Dem_u08_IndicatorInfoIndexType, AUTOMATIC ) indicatorConfigureNum;
    P2CONST( AB_83_ConstV Dem_u16_EventCtrlIndexType, AUTOMATIC, DEM_CONFIG_DATA ) eventIdxListPtr;

    *IndicatorStatusPtr = DEM_INDICATOR_OFF;
    indicatorConfigureNum = Dem_IndicatorInfoConfigureNum;
    retVal = DEM_IRT_NG;

    if ( IndicatorId < indicatorConfigureNum )                              /* [GUD:if]IndicatorId */
    {
        eventCtrlIndexNum = Dem_IndicatorInfoTable[IndicatorId].EventNum;                                   /* [GUD]IndicatorId */
        eventIdxListPtr = Dem_IndicatorInfoTable[IndicatorId].EventIdxListPtr;                              /* [GUD]IndicatorId */

        for( loopCount = (Dem_u16_EventCtrlIndexType)0U ; loopCount < eventCtrlIndexNum ; loopCount++ )     /* [GUD:for]loopCount */
        {
            eventCtrlIndexInTable = (Dem_u16_EventCtrlIndexType)eventIdxListPtr[loopCount];                     /* [GUD]loopCount *//* [ARYCHK] eventCtrlIndexNum / 1 / loopCount *//* [ARYDESC] Dem_IndicatorInfoTable[].EventIdxListPtr size is output in Dem_IndicatorInfoTable[].EventNum. */

            if( eventCtrlIndexInTable == EventCtrlIndex )
            {
                retResult = Dem_Ind_GetUserDefinedIndicatorWIRStatus( EventCtrlIndex, IndicatorStatusPtr );
                if( retResult == DEM_IRT_OK )
                {
                    retVal = DEM_IRT_OK;
                }
                break;
            }
        }
    }
    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Ind_GetUserDefinedIndicatorWIRStatus                 */
/* Description   | Get UserDefined Indicator Id Check Result                */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventCtrlIndex :                                    */
/*               |        Event index.                                      */
/*               | [out] IndicatorStatusPtr                                 */
/*               |          DEM_INDICATOR_OFF        : Indicator Off        */
/*               |          DEM_INDICATOR_CONTINUOUS : Indicator On         */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Success.                             */
/*               |        DEM_IRT_NG : Failed.                              */
/* Notes         |                                                          */
/*               |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Ind_GetUserDefinedIndicatorWIRStatus
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    P2VAR( Dem_IndicatorStatusType, AUTOMATIC, AUTOMATIC ) IndicatorStatusPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
    VAR( Dem_u08_MemoryKindType, AUTOMATIC ) memKind;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )  */

    *IndicatorStatusPtr = DEM_INDICATOR_OFF;

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
    /* check eventIndex kind. */
    memKind = Dem_CfgInfoCmn_CheckMemoryTypeFromEventCtrlIndex( EventCtrlIndex );
    if( memKind != DEM_MEMKIND_PRIMARY )
    {
        /*  userDefinedMemory       */
        retTempVal = Dem_CfgInfoUdm_CnvEventCtrlIndexToUdmEventIndex( EventCtrlIndex, &udmEventIndex );             /* [GUD:RET:DEM_IRT_OK] udmEventIndex */
        if( retTempVal == DEM_IRT_OK )
        {
            retVal      =   Dem_UdmInd_GetUserDefinedIndicator_UserDefMem( udmEventIndex, IndicatorStatusPtr );     /* [GUD] udmEventIndex */
        }
        else
        {
            retVal = DEM_IRT_NG;
        }
    }
    else
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )  */
    {
        /*  PrimaryMemory           */
        eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( EventCtrlIndex );                        /* [GUD:RET:IF_GUARDED: EventCtrlIndex ]eventStrgIndex */
        retVal          =   Dem_Ind_GetUserDefinedIndicator_Primary( eventStrgIndex, IndicatorStatusPtr );
    }
    return retVal;
}


#endif  /* ( DEM_USER_DEFINED_INDICATOR_SUPPORT == STD_ON )   */

#if ( DEM_USER_DEFINED_INDICATOR_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_Ind_GetUserDefinedIndicatorStatus                    */
/* Description   | Get UserDefined Indicator Status by Indicator Id.        */
/* Preconditions | none                                                     */
/* Parameters    | [in]  IndicatorId :                                      */
/*               |        Indicator Id.                                     */
/*               | [out] IndicatorStatusPtr                                 */
/*               |          DEM_INDICATOR_OFF        : Indicator Off        */
/*               |          DEM_INDICATOR_CONTINUOUS : Indicator On         */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Success.                             */
/*               |        DEM_IRT_NG : Failed.                              */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Ind_GetUserDefinedIndicatorStatus
(
    VAR( Dem_u08_IndicatorIdType, AUTOMATIC ) IndicatorId,                       /* MISRA DEVIATION */
    P2VAR( Dem_IndicatorStatusType, AUTOMATIC, AUTOMATIC ) IndicatorStatusPtr    /* MISRA DEVIATION */
)
{
    /*  This is empty function for function switching.  */
    return DEM_IRT_NG;
}

/****************************************************************************/
/* Function Name | Dem_Ind_GetUserDefinedIndicatorStatusByEventCtrlIndex    */
/* Description   | Get UserDefined Indicator Status by Indicator Id.        */
/* Preconditions | none                                                     */
/* Parameters    | [in]  EventCtrlIndex :                                   */
/*               | [in]  IndicatorId :                                      */
/*               |        Indicator Id.                                     */
/*               | [out] IndicatorStatusPtr                                 */
/*               |          DEM_INDICATOR_OFF        : Indicator Off        */
/*               |          DEM_INDICATOR_CONTINUOUS : Indicator On         */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Success.                             */
/*               |        DEM_IRT_NG : Failed.                              */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Ind_GetUserDefinedIndicatorStatusByEventCtrlIndex
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,                /* MISRA DEVIATION */
    VAR( Dem_u08_IndicatorIdType, AUTOMATIC ) IndicatorId,                       /* MISRA DEVIATION */
    P2VAR( Dem_IndicatorStatusType, AUTOMATIC, AUTOMATIC ) IndicatorStatusPtr    /* MISRA DEVIATION */
)
{
    /*  This is empty function for function switching.  */
    return DEM_IRT_NG;
}

#endif  /* ( DEM_USER_DEFINED_INDICATOR_SUPPORT == STD_OFF )   */


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/*  v5-8-0         :2024-10-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
