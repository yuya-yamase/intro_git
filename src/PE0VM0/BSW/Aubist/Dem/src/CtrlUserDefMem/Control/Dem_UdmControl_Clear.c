/* Dem_UdmControl_Clear_c(v5-5-0)                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/UdmControl_Clear/CODE                                 */
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
#include "../../../inc/Dem_Udm_Control.h"
#include "../../../inc/Dem_Udm_Data.h"
#include "../../../inc/Dem_Rc_UdmMng.h"

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

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmControl_GetNextEventIndexByDTCs
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) BaseUdmGroupKindIndex,
    P2VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC, AUTOMATIC ) NextUdmGroupKindIndexPtr,
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) BaseUdmEventIndex,
    P2VAR( Dem_u16_UdmEventIndexType, AUTOMATIC, AUTOMATIC ) NextEventUdmIndexPtr
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

static VAR( Dem_u16_UdmEventIndexType, DEM_VAR_NO_INIT )      Dem_UdmCtlClearEventIndex;
static VAR( Dem_u16_UdmDemMemKindIndexType, DEM_VAR_NO_INIT ) Dem_UdmGroupKindIndex;
static VAR( Dem_u16_UdmDemMemKindIndexType, DEM_VAR_NO_INIT ) Dem_UdmGroupKindIndexEnd;


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_UdmControl_StartClearDTC                             */
/* Description   | Initializes clear info.                                  */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCOrigin :                                         */
/*               |        The specified DTCOrigin.                          */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmControl_StartClearDTC
(
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInfoTableIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndexStart;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndexNum;

    Dem_UdmCtlClearEventIndex   =   DEM_UDMEVENTINDEX_INVALID;

    /* get udm info index by DTCOrigin. */
    retTempVal = Dem_CfgInfoUdm_CnvDTCOriginToInternalInfoTableIndex( DTCOrigin, &udmInfoTableIndex ); /* [GUD:RET:DEM_IRT_OK] udmInfoTableIndex */

    if( retTempVal == DEM_IRT_OK )
    {
        /* get udm group index. */
        Dem_CfgInfoUdm_GetUserDefinedMemoryGroupKindIndex( udmInfoTableIndex, &udmGroupKindIndexStart, &udmGroupKindIndexNum );     /* [GUD]udmInfoTableIndex */

        Dem_UdmGroupKindIndex       =   udmGroupKindIndexStart;
        Dem_UdmGroupKindIndexEnd    =   udmGroupKindIndexStart + udmGroupKindIndexNum;
    }
    else
    {
        /* When external memory or invalid DTCOrigin, set invalid value. */
        Dem_UdmGroupKindIndex       =   DEM_UDMTABLEINDEX_INVALID;
        Dem_UdmGroupKindIndexEnd    =   ( Dem_u16_UdmDemMemKindIndexType )0U;
    }

    return ;
}


/****************************************************************************/
/* Function Name | Dem_UdmControl_ClearRAM                                  */
/* Description   | Clear RAM: UserDefineMemory                              */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |    DEM_IRT_OK        :   completed.                      */
/*               |    DEM_IRT_PENDING   :   continue.                       */
/* Notes         | none                                                     */
/*               |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmControl_ClearRAM
( void )
{
    VAR( Dem_u16_AdjustCntByEventNumType, AUTOMATIC ) loopCount;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) nextUdmEventIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) nextUdmGroupKindIndex;
    VAR( Dem_u16_AdjustCntByEventNumType, AUTOMATIC ) controlClearRamEventNumByCycle;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Std_ReturnType, AUTOMATIC ) resultOfCallback = E_NOT_OK;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;

    controlClearRamEventNumByCycle = Dem_ControlClearRamEventNumByCycle;

    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;
    if ( Dem_UdmGroupKindIndex < userDefinedMemoryNum )     /* [GUD:if]Dem_UdmGroupKindIndex */
    {
        retVal  =   DEM_IRT_PENDING;

        for( loopCount = (Dem_u16_AdjustCntByEventNumType)0U; loopCount < controlClearRamEventNumByCycle; loopCount++ )     /* [GUD:for]loopCnt */
        {
            retTempVal = Dem_UdmControl_GetNextEventIndexByDTCs( Dem_UdmGroupKindIndex, &nextUdmGroupKindIndex, Dem_UdmCtlClearEventIndex, &nextUdmEventIndex );    /* [GUD]Dem_UdmGroupKindIndex *//* [GUD:RET:IF_GUARDED: Dem_UdmGroupKindIndex] nextUdmGroupKindIndex *//* [GUD:RET:DEM_IRT_OK]nextUdmEventIndex */
            if( retTempVal == DEM_IRT_OK )
            {
                /* When event index of clear target is obtained successfully */
                Dem_UdmGroupKindIndex     = nextUdmGroupKindIndex;                                                  /* [GUD]Dem_UdmGroupKindIndex( == nextUdmGroupKindIndex ) */
                Dem_UdmCtlClearEventIndex = nextUdmEventIndex;                                                      /* [GUD]Dem_UdmCtlClearEventIndex( == nextUdmEventIndex ) */

                /* Clear the specified data */
                Dem_UdmData_RequestFixedClear( Dem_UdmGroupKindIndex, Dem_UdmCtlClearEventIndex );                  /* [GUD]Dem_UdmGroupKindIndex *//* [GUD]Dem_UdmCtlClearEventIndex */

                /* Clear completion notification */
                Dem_CfgInfoUdm_TriggerInitMForEFnc( Dem_UdmCtlClearEventIndex, DEM_INIT_MONITOR_CLEAR, &resultOfCallback );     /* [GUD]Dem_UdmCtlClearEventIndex */

            }
            else
            {
                retVal  =   DEM_IRT_OK;

                break;
            }
        }
    }
    else
    {
        /*  no clear process.       */
        retVal  =   DEM_IRT_OK;
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_UdmControl_EndClearDTC                               */
/* Description   | End of ClearDTC in UserDefinedMemory.                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCOrigin                                           */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmControl_EndClearDTC
(
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInfoTableIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndexStart;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndexNum;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndexEnd;

    /* get udm info index by DTCOrigin. */
    retTempVal = Dem_CfgInfoUdm_CnvDTCOriginToInternalInfoTableIndex( DTCOrigin, &udmInfoTableIndex ); /* [GUD:RET:DEM_IRT_OK] udmInfoTableIndex */
    /* check not invalid or ecternal */
    if( retTempVal == DEM_IRT_OK )
    {
        Dem_CfgInfoUdm_GetUserDefinedMemoryGroupKindIndex( udmInfoTableIndex, &udmGroupKindIndexStart, &udmGroupKindIndexNum );     /* [GUD]udmInfoTableIndex */
        udmGroupKindIndexEnd = udmGroupKindIndexStart + udmGroupKindIndexNum;

        for( udmGroupKindIndex = udmGroupKindIndexStart; udmGroupKindIndex < udmGroupKindIndexEnd; udmGroupKindIndex++ )    /* [GUD:for]udmGroupKindIndex */
        {
            Dem_UdmData_ReplaceSearchFRIndex( udmGroupKindIndex );                                                          /* [GUD]udmGroupKindIndex */

#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )  /* [FuncSw] */
            Dem_UdmData_GenerateTSFFLRecordList( udmGroupKindIndex );                                                       /* [GUD]udmGroupKindIndex */
#endif  /* ( DEM_TSFF_UDM_SUPPORT == STD_ON )   */
        }
    }

    return ;
}

/****************************************************************************/
/* Function Name | Dem_UdmControl_GetNextEventIndexByDTCs                   */
/* Description   | Returns the next event index corresponding to the speci- */
/*               | fied DTC/group DTCs/all DTCs.                            */
/* Preconditions | Now, supports all DTCs only.                             */
/* Parameters    | [in] BaseUdmGroupKindIndex :                             */
/*               |        The specified based udm group table index.        */
/*               | [out] NextUdmGroupKindIndexPtr                           */
/*               |        The next udm group table index which has been re- */
/*               | [in] BaseEventIndex :                                    */
/*               |        The specified based event index.                  */
/*               | [out] NextEventIndexPtr :                                */
/*               |        The next event index which has been retrieved.    */
/*               |        trieved.                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : The next event index retrieving is - */
/*               |        successful.                                       */
/*               |        DEM_IRT_NO_MATCHING_ELEMENT : No more next event  */
/*               |         index.(retrieving finished)                      */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:IF_GUARDED: BaseUdmGroupKindIndex] NextUdmGroupKindIndexPtr */
/* VariableGuard | [GUD:RET:DEM_IRT_OK] NextEventUdmIndexPtr                */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmControl_GetNextEventIndexByDTCs
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) BaseUdmGroupKindIndex,
    P2VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC, AUTOMATIC ) NextUdmGroupKindIndexPtr,
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) BaseUdmEventIndex,
    P2VAR( Dem_u16_UdmEventIndexType, AUTOMATIC, AUTOMATIC ) NextEventUdmIndexPtr
)
{
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventIndex;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventIndexBase;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmGroupKindIndex;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmStartOfEventIndex;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmNumOfEventIndex;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEndOfEventIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    /* Initializes the return value to OK. */
    retVal = DEM_IRT_OK;

    /* Set event index in udm group. */
    udmStartOfEventIndex    =   Dem_CfgInfoUdm_GetStartUdmEventIndex_InMemory( BaseUdmGroupKindIndex );
    udmNumOfEventIndex      =   Dem_CfgInfoUdm_GetConfigureNumOfUdmEventIndex_InMemory( BaseUdmGroupKindIndex );
    udmEndOfEventIndex      =   udmStartOfEventIndex + udmNumOfEventIndex;

    udmEventIndexBase       =   BaseUdmEventIndex;
    udmGroupKindIndex       =   BaseUdmGroupKindIndex;

    /* Checks whether the specified based event index is initial value. */
    if( udmEventIndexBase == DEM_UDMEVENTINDEX_INVALID )
    {
        /* The specified based event index is initial value. */

        /* Sets the startof event index in memory. */
        udmEventIndex   =   udmStartOfEventIndex;
    }
    else if( ( udmEventIndexBase + (Dem_u16_UdmEventIndexType)1U ) < udmEndOfEventIndex )
    {
        /* The specified based event index is less than number of the configured events. */

        /* Sets the next event index to based event index plus one. */
        udmEventIndex  =   udmEventIndexBase + (Dem_u16_UdmEventIndexType)1U;
    }
    else
    {
        /* The specified based event index is number of the configured events or more. */

        /* Check all udm groups are searched. */
        if( ( udmGroupKindIndex + ( Dem_u16_UdmDemMemKindIndexType )1U )  < Dem_UdmGroupKindIndexEnd )
        {
            /* Set next udm group index. */
            udmGroupKindIndex = udmGroupKindIndex + ( Dem_u16_UdmDemMemKindIndexType )1U;

            /* Sets the startof event index in next udm group. */
            udmEventIndex = Dem_CfgInfoUdm_GetStartUdmEventIndex_InMemory( udmGroupKindIndex );
        }
        else
        {
            /* Sets the next event index to initial value. */
            udmEventIndex  =   DEM_UDMEVENTINDEX_INVALID;
            /* Sets return value to no matching element. */
            retVal = DEM_IRT_NO_MATCHING_ELEMENT;
        }
    }

    *NextEventUdmIndexPtr       = udmEventIndex;
    *NextUdmGroupKindIndexPtr   = udmGroupKindIndex;

    /* Returns with the result. */
    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_UdmControl_Clear_ClearDTCInfo                        */
/* Description   | Clear clear info.                                        */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmControl_Clear_ClearDTCInfo
( void )
{
    Dem_UdmCtlClearEventIndex   =   DEM_UDMEVENTINDEX_INVALID;
    Dem_UdmGroupKindIndex       =   DEM_UDMTABLEINDEX_INVALID;
    Dem_UdmGroupKindIndexEnd    =   ( Dem_u16_UdmDemMemKindIndexType )0U;

    return ;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )  */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
