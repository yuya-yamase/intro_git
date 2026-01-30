/* Dem_UdmFaultMng_c(v5-8-0)                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/UdmFaultMng/CODE                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )

#include "../../../cfg/Dem_Cfg.h"
#include "../../../cfg/Dem_UserDefMem_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_Udm_DataAvl.h"
#include "../../../inc/Dem_Rc_RecMngCmn.h"
#include "../../../inc/Dem_Rc_RecMngCmn_Table.h"
#include "../../../inc/Dem_Rc_UdmMng.h"
#include "../../../inc/Dem_Rc_UdmMng_rc.h"
#include "../../../inc/Dem_Rc_UdmMngTable.h"
#include "../../../inc/Dem_Rc_UdmEventRecordTable.h"
#include "../../../inc/Dem_Rc_UdmFaultRecordTable.h"
#include "../../../inc/Dem_Utl.h"
#include "Dem_UdmMng_local.h"
#include "Dem_UdmMng_GetRecordData.h"

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

static FUNC( void, DEM_CODE ) Dem_UdmFaultMng_SetFaultRecord_Ctl
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmFaultIndex,
    P2CONST( Dem_UdmFaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) SrcUdmFaultRecordPtr
);

static FUNC( void, DEM_CODE ) Dem_UdmFaultMng_InitRecord_Ctl
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmFaultIndex
);

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmFaultMngM_GetRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmFaultIndex,
    P2VAR( Dem_UdmFaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) UdmFaultRecordPtr
);
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

static FUNC( void, DEM_CODE ) Dem_UdmFaultMng_GetRecord_Ctl
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmFaultIndex,
    P2VAR( Dem_UdmFaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) DestUdmFaultRecordPtr
);

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
static FUNC( void, DEM_CODE ) Dem_UdmFaultMng_GetRecord_MM
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmFaultIndex,
    P2VAR( Dem_UdmFaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) DestUdmFaultRecordPtr
);
static FUNC( void, DEM_CODE ) Dem_UdmFaultMng_Get_PaddingRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmFaultIndex,
    P2VAR( Dem_UdmFaultRecordType, AUTOMATIC, AUTOMATIC ) UdmFaultRecordPtr
);
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */
static FUNC( void, DEM_CODE ) Dem_UdmMng_UpdateFaultRecordConsistencyId
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmFaultIndex,
    P2VAR( Dem_u08_ConsistencyIdType, AUTOMATIC, AUTOMATIC ) ConsistencyIdPtr
);

static FUNC( void, DEM_CODE ) Dem_UdmFaultMng_InitFaultRecord_Ctl
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmFaultIndex
);

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
static FUNC( void, DEM_CODE ) Dem_UdmFaultMng_InitFRData_Padding
(
    P2VAR( Dem_UdmFaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) UdmFaultRecordPtr
);

static FUNC( void, DEM_CODE ) Dem_UdmFaultMng_InitMirrorMemory
( void );

#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

static FUNC_P2VAR( Dem_UdmFaultRecordType, DEM_VAR_SAVED_ZONE, DEM_CODE ) Dem_UdmFaultMng_GetFaultRecordPtr
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmFaultIndex
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/*  if DEM_NVM_SYNC_PROCESS_ENABLE is STD_OFF, these valiables are set but never used.  */
VAR( Dem_UdmFaultRecordType, DEM_VAR_NO_INIT ) Dem_TmpUdmFaultMirror;
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_UdmFaultMngC_GetEmptyFaultIndex                      */
/* Description   | Gets the empty the udm fault record from the udm fault   */
/*               | record list corresponding to the specified memory kind   */
/*               | index.(for UdmDem_DataCtl subunit)                       */
/* Preconditions | The specified UdmGroupKindIndex shall be within the      */
/*               | range of the Dem_UserDefinedMemoryTable[].               */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        The index for Dem_UserDefinedMemoryTable[].       */
/*               | [in] UdmStartFaultIndex :                                */
/*               |        The udm fault index corresponding to the specific */
/*               |         udm fault record.                                */
/* Return Value  | Dem_u08_UdmFaultIndexType                                */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_UdmFaultIndexType, DEM_CODE ) Dem_UdmFaultMngC_GetEmptyFaultIndex
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmStartFaultIndex
)
{
    P2CONST( Dem_UdmFaultRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) udmFaultRecordPtr;
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) udmFaultRecordNum;
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) udmFaultIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;

    udmFaultIndex   =   DEM_UDMFAULTINDEX_INITIAL;
    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;
    if( UdmGroupKindIndex < userDefinedMemoryNum )                                              /* [GUD:if]UdmGroupKindIndex */
    {
        udmFaultRecordNum = Dem_UdmFaultRecordTable[UdmGroupKindIndex].DemFaultRecordNum;       /* [GUD]UdmGroupKindIndex */

        for( udmFaultIndex = UdmStartFaultIndex; udmFaultIndex < udmFaultRecordNum ; udmFaultIndex++ )  /* [GUD:for]udmFaultIndex */
        {
            udmFaultRecordPtr = ( P2CONST( Dem_UdmFaultRecordType, TYPEDEF, DEM_VAR_SAVED_ZONE ) )Dem_UdmFaultMng_GetFaultRecordPtr( UdmGroupKindIndex, udmFaultIndex );    /* [GUD]UdmGroupKindIndex *//* [GUD]udmFaultIndex *//* [GUD:RET:IF_GUARDED UdmGroupKindIndex/UdmFaultIndex]udmFaultRecordPtr */

            /* Check EventIndex is initialized. */
            if( udmFaultRecordPtr->UdmEventIndex == DEM_UDMEVENTINDEX_INVALID )                 /* [GUD]udmFaultRecordPtr */
            {
                break;
            }
        }
    }

    return udmFaultIndex;

}

/****************************************************************************/
/* Function Name | Dem_UdmFaultMngC_GetLowestPriorityFaultIndex             */
/* Description   | get lowest priority of fault record.                     */
/* Preconditions | The specified UdmGroupKindIndex shall be within the      */
/*               | range of the Dem_UserDefinedMemoryTable[].               */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        The index for Dem_UserDefinedMemoryTable[].       */
/*               | [in] EventPriorityOverwrite :                            */
/*               |        request priority.                                 */
/*               | [in] EventDisplacementStrategy :                         */
/* Return Value  | Dem_u08_UdmFaultIndexType                                */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmFaultMngC_GetLowestPriorityFaultIndex
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u08_EventPriorityType, AUTOMATIC ) LimitEventPriority,
    VAR( Dem_u08_EventDisplacementStrategyType, AUTOMATIC ) EventDisplacementStrategy,
    P2VAR( Dem_u16_UdmEventIndexType, AUTOMATIC, AUTOMATIC ) UdmEventIndexLowestPriorityPtr
)
{
    P2CONST( Dem_UdmFaultRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) udmFaultRecordPtr;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) udmFaultRecordNum;
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) udmFaultIndex;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmLowestEventIndex;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventIndexMinNum;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventIndexMaxNum;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventConfigureNum;
    VAR( Dem_u08_EventPriorityType, AUTOMATIC ) eventPriority;
    VAR( Dem_u08_EventPriorityType, AUTOMATIC ) latchPriority;
    VAR( boolean, AUTOMATIC ) availableStatus;
    VAR( Dem_u16_OccrOrderType, AUTOMATIC ) udmLatchFaultOccurrenceOrder;
    VAR( Dem_u16_OccrOrderType, AUTOMATIC ) udmFaultOccurrenceOrder;

    retVal  =   DEM_IRT_NG;
    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;

    if( UdmGroupKindIndex < userDefinedMemoryNum )                                              /* [GUD:if]UdmGroupKindIndex */
    {
        /*  get faultrecord total number        */
        udmFaultRecordNum       =   Dem_UdmFaultRecordTable[UdmGroupKindIndex].DemFaultRecordNum;                       /* [GUD]UdmGroupKindIndex */
        udmEventIndexMinNum     =   Dem_CfgInfoUdm_GetStartUdmEventIndex_InMemory( UdmGroupKindIndex );                 /* [GUD]UdmGroupKindIndex */
        udmEventConfigureNum    =   Dem_CfgInfoUdm_GetConfigureNumOfUdmEventIndex_InMemory( UdmGroupKindIndex );        /* [GUD]UdmGroupKindIndex */
        udmEventIndexMaxNum     =   udmEventIndexMinNum + ( udmEventConfigureNum - ( Dem_u16_UdmEventIndexType )1U );

        /*------------------------------*/
        /*  search reset value.         */
        udmLatchFaultOccurrenceOrder    =   DEM_FAIL_OCCURRENCE_NUM_INVALID;
        latchPriority                   =   LimitEventPriority;
        udmLowestEventIndex             =   DEM_UDMEVENTINDEX_INVALID;


        /*------------------------------*/
        /*  search fault record.        */
        for( udmFaultIndex = (Dem_u08_UdmFaultIndexType)0U; udmFaultIndex < udmFaultRecordNum ; udmFaultIndex++ )   /* [GUD:for]udmFaultIndex */
        {
            /*  get fault record address        */
            udmFaultRecordPtr = ( P2CONST( Dem_UdmFaultRecordType, TYPEDEF, DEM_VAR_SAVED_ZONE ) )Dem_UdmFaultMng_GetFaultRecordPtr( UdmGroupKindIndex, udmFaultIndex );    /* [GUD]UdmGroupKindIndex *//* [GUD]udmFaultIndex[GUD:RET:IF_GUARDED UdmGroupKindIndex/udmFaultIndex]udmFaultRecordPtr */

            /*----------------------------------*/
            /* Check EventIndex is initialized. */
            if(( udmFaultRecordPtr->UdmEventIndex <= udmEventIndexMaxNum ) && ( udmFaultRecordPtr->UdmEventIndex >= udmEventIndexMinNum ))  /* [GUD]udmFaultRecordPtr */
            {
                /*  check event available.      */
                availableStatus  =   Dem_UdmDataAvl_GetEvtAvl( udmFaultRecordPtr->UdmEventIndex );                                          /* [GUD]udmFaultRecordPtr */
                if ( availableStatus == (boolean)TRUE )
                {
                    /*------------------------------*/
                    /*  get priority                */
                    eventPriority = Dem_CfgInfoUdm_GetEventPriority( udmFaultRecordPtr->UdmEventIndex );                                    /* [GUD]udmFaultRecordPtr */
                }
                else
                {
                    /*  the event is not available.         */
                    /*  lowest priority.                    */
                    eventPriority   =   DEM_PRIORITY_EVT_AVL;
                }

                udmFaultOccurrenceOrder =   udmFaultRecordPtr->UdmFaultOccurrenceOrder;                                                     /* [GUD]udmFaultRecordPtr */

                /*  check the priority is lower than request.       */
                if ( LimitEventPriority < eventPriority )
                {
                    if ( latchPriority < eventPriority )
                    {
                        /*------------------------------*/
                        /*  get lower priority.         */
                        latchPriority                   =   eventPriority;                      /*  update latch priority.              */
                        udmLatchFaultOccurrenceOrder    =   udmFaultOccurrenceOrder;            /*  reset value                         */
                        udmLowestEventIndex             =   udmFaultRecordPtr->UdmEventIndex;   /*  update lowest udmeventindex.        */  /* [GUD]udmFaultRecordPtr */
                        retVal  =   DEM_IRT_OK;
                    }
                    else if ( latchPriority == eventPriority )
                    {
                        /*------------------------------*/
                        /*  same priority.              */
                        /*  get occurrence order        */
                        if ( EventDisplacementStrategy == DEM_DISPLACEMENT_PRIO_OCC )
                        {
                            /*  oldest.     */
                            if ( udmFaultOccurrenceOrder < udmLatchFaultOccurrenceOrder )
                            {
                                udmLatchFaultOccurrenceOrder    =   udmFaultOccurrenceOrder;            /*  latch oldest occurrence.        */
                                udmLowestEventIndex             =   udmFaultRecordPtr->UdmEventIndex;   /*  update lowest udmeventindex.    */  /* [GUD]udmFaultRecordPtr */
                                retVal  =   DEM_IRT_OK;
                            }
                        }
                        else
                        {
                            /*  newest.     */
                            if ( udmFaultOccurrenceOrder > udmLatchFaultOccurrenceOrder )
                            {
                                udmLatchFaultOccurrenceOrder    =   udmFaultOccurrenceOrder;            /*  latch newest occurrence.        */
                                udmLowestEventIndex             =   udmFaultRecordPtr->UdmEventIndex;   /*  update lowest udmeventindex.    */  /* [GUD]udmFaultRecordPtr */
                                retVal  =   DEM_IRT_OK;
                            }
                        }
                    }
                    else
                    {
                        /*  no latch.       */
                    }
                }
            }
        }
    }
    if ( retVal == DEM_IRT_OK )
    {
        *UdmEventIndexLowestPriorityPtr =   udmLowestEventIndex;
    }
    return retVal;

}

/****************************************************************************/
/* Function Name | Dem_UdmFaultMngC_GetFaultRecordNum                       */
/* Description   | Gets number of fault records from the udm fault record   */
/*               | list corresponding to the specified memory kind index.   */
/*               | (for UdmDem_DataCtl subunit)                             */
/* Preconditions | The specified UdmGroupKindIndex shall be within the      */
/*               | range of the Dem_UserDefinedMemoryTable[].               */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        The index for Dem_UserDefinedMemoryTable[].       */
/* Return Value  | Dem_u08_UdmFaultIndexType                                */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_UdmFaultIndexType, DEM_CODE ) Dem_UdmFaultMngC_GetFaultRecordNum
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex
)
{
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) udmFaultRecordNum;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;

    udmFaultRecordNum    =   (Dem_u08_UdmFaultIndexType)0U;
    userDefinedMemoryNum =   Dem_UserDefinedMemoryNum;
    if( UdmGroupKindIndex < userDefinedMemoryNum )                                              /* [GUD:if]UdmGroupKindIndex */
    {
        udmFaultRecordNum = Dem_UdmFaultRecordTable[UdmGroupKindIndex].DemFaultRecordNum;       /* [GUD]UdmGroupKindIndex */
    }
    return udmFaultRecordNum;

}

/****************************************************************************/
/* Function Name | Dem_UdmFaultMngC_GetRecord                               */
/* Description   | Gets the data body of the udm fault record from the udm  */
/*               | fault record list corresponding to the specified udm fa- */
/*               | ult index.(for Dem_DataCtl subunit)                      */
/* Preconditions | The specified udm fault index be within the range of the */
/*               |  udm fault record list.                                  */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        The index for Dem_UserDefinedMemoryTable[].       */
/*               | [in] UdmFaultIndex :                                     */
/*               |        The udm fault index corresponding to the specific */
/*               |         udm fault record.                                */
/*               | [out] UdmFaultRecordPtr :                                */
/*               |        The pointer of the udm fault record correspondin- */
/*               |        g to the specified udm fault index.               */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmFaultMngC_GetRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmFaultIndex,
    P2VAR( Dem_UdmFaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) UdmFaultRecordPtr
)
{
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) udmFaultRecordNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;

    retVal = DEM_IRT_NG;

    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;
    if( UdmGroupKindIndex < userDefinedMemoryNum )                                              /* [GUD:if]UdmGroupKindIndex */
    {
        udmFaultRecordNum = Dem_UdmFaultRecordTable[UdmGroupKindIndex].DemFaultRecordNum;           /* [GUD]UdmGroupKindIndex */

        if( UdmFaultIndex < udmFaultRecordNum )
        {
            Dem_UdmFaultMng_GetRecord_Ctl( UdmGroupKindIndex, UdmFaultIndex, UdmFaultRecordPtr );   /* [GUD]UdmGroupKindIndex */
            retVal = DEM_IRT_OK;
        }
        else
        {
            /* No process */
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_UdmFaultMngC_ClearFaultRecord                        */
/* Description   | Sets the data body of the fault record to the fault rec- */
/*               | ord list corresponding to the specified fault index. (f- */
/*               | or Dem_DataCtl subunit)                                  */
/* Preconditions | The specified fault index be within the range of the fa- */
/*               | ult record list.                                         */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        The index for Dem_UserDefinedMemoryTable[].       */
/*               | [in] UdmFaultIndex :                                     */
/*               |        The fault index corresponding to the specific fa- */
/*               |        ult record.                                       */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmFaultMngC_ClearFaultRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmFaultIndex
)
{
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;

    retVal = DEM_IRT_NG;

    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;
    if( UdmGroupKindIndex < userDefinedMemoryNum )                                              /* [GUD:if]UdmGroupKindIndex */
    {
        failRecordNum = Dem_UdmFaultRecordTable[UdmGroupKindIndex].DemFaultRecordNum;           /* [GUD]UdmGroupKindIndex */

        if( UdmFaultIndex < failRecordNum )
        {
            Dem_UdmFaultMng_InitFaultRecord_Ctl( UdmGroupKindIndex, UdmFaultIndex );            /* [GUD]UdmGroupKindIndex */

            retVal = DEM_IRT_OK;
        }
        else
        {
            /* No process */
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_UdmFaultMngC_CompareFaultRecord                      */
/* Description   | compare data.                                            */
/* Preconditions |                                                          */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        The index for Dem_UserDefinedMemoryTable[].       */
/*               | [in] UdmFaultIndex :                                     */
/*               | [in] CheckUdmFaultRecordPtr :                            */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK  : same.                               */
/*               |        DEM_IRT_NG  : different.                          */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | rename from Dem_UdmFaultMng_CmpWithFaultRecord(v5-3-0).  */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmFaultMngC_CompareFaultRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmFaultIndex,
    P2CONST( Dem_UdmFaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) CheckUdmFaultRecordPtr
)
{
    P2CONST( Dem_UdmFaultRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) udmFaultRecordPtr;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_OK;
    udmFaultRecordPtr = ( P2CONST( Dem_UdmFaultRecordType, TYPEDEF, DEM_VAR_SAVED_ZONE ) )Dem_UdmFaultMng_GetFaultRecordPtr( UdmGroupKindIndex, UdmFaultIndex );    /* [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/UdmFaultIndex/udmFaultRecordPtr */

    if ( udmFaultRecordPtr != NULL_PTR )    /* [GUD:if]udmFaultRecordPtr */
    {
        if( udmFaultRecordPtr->UdmEventIndex != CheckUdmFaultRecordPtr->UdmEventIndex )                             /* [GUD]udmFaultRecordPtr */
        {
            retVal = DEM_IRT_NG;
        }
        else if( udmFaultRecordPtr->UdmFaultOccurrenceOrder != CheckUdmFaultRecordPtr->UdmFaultOccurrenceOrder )    /* [GUD]udmFaultRecordPtr */
        {
            retVal = DEM_IRT_NG;
        }
        else if( udmFaultRecordPtr->RecordNumberIndex != CheckUdmFaultRecordPtr->RecordNumberIndex )                /* [GUD]udmFaultRecordPtr */
        {
            retVal = DEM_IRT_NG;
        }
#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )
        else if( udmFaultRecordPtr->TimeSeriesFreezeFrameListIndex != CheckUdmFaultRecordPtr->TimeSeriesFreezeFrameListIndex )  /* [GUD]udmFaultRecordPtr */
        {
            retVal = DEM_IRT_NG;
        }
#endif /* ( DEM_TSFF_UDM_SUPPORT == STD_ON ) */
        else
        {
            /* No process */
        }
    }
    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_UdmFaultMngC_SetFaultRecord                          */
/* Description   | Sets the data body of the fault record to the fault rec- */
/*               | ord list corresponding to the specified fault index. (f- */
/*               | or Dem_DataCtl subunit)                                  */
/* Preconditions | The specified fault index be within the range of the fa- */
/*               | ult record list.                                         */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        The index for Dem_UserDefinedMemoryTable[].       */
/*               | [in] UdmFaultIndex :                                     */
/*               |        The fault index corresponding to the specific fa- */
/*               |        ult record.                                       */
/*               | [in] UdmFaultRecordPtr :                                 */
/*               |                     &Dem_TmpEventMemoryEntry.FaultRecord */
/*               |        The pointer of the fault record corresponding to  */
/*               |         the specified fault index.                       */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmFaultMngC_SetFaultRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmFaultIndex,
    P2CONST( Dem_UdmFaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) UdmFaultRecordPtr
)
{
    VAR( Dem_u16_UdmEventStrgIndexType, AUTOMATIC ) udmEventStrgIndex;
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindUdmFault;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindUdmEvent;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) consistencyId;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;

    retVal = DEM_IRT_NG;

    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;
    if( UdmGroupKindIndex < userDefinedMemoryNum )                                              /* [GUD:if]UdmGroupKindIndex */
    {
        failRecordNum = Dem_UdmFaultRecordTable[UdmGroupKindIndex].DemFaultRecordNum;           /* [GUD]UdmGroupKindIndex */

        if( UdmFaultIndex < failRecordNum )                                                     /* [GUD:if]UdmFaultIndex */
        {
            consistencyId   =   DEM_CONSISTENCY_INITIAL;
            Dem_UdmFaultMng_SetFaultRecord_Ctl( UdmGroupKindIndex, UdmFaultIndex, UdmFaultRecordPtr );                                      /* [GUD]UdmGroupKindIndex *//* [GUD]UdmFaultIndex */
            Dem_UdmMng_UpdateFaultRecordConsistencyId( UdmGroupKindIndex, UdmFaultIndex, &consistencyId );                                  /* [GUD]UdmGroupKindIndex *//* [GUD]UdmFaultIndex */
            Dem_UdmEventMng_SetEventRecordConsistencyId( UdmFaultRecordPtr->UdmEventIndex, consistencyId );
            /* Change Dem_FaultNvMStatus */
            recMngCmnKindUdmFault = Dem_UdmFaultNvMStatus[ UdmGroupKindIndex ].DemRecMngCmnKindUdmFault;                                    /* [GUD]UdmGroupKindIndex */
            Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindUdmFault, ( Dem_u16_RecordIndexType )UdmFaultIndex );                             /* [GUD]UdmFaultIndex */
            recMngCmnKindUdmEvent = Dem_UdmEventNvMStatus[ UdmGroupKindIndex ].DemRecMngCmnKindUdmEvent;                                    /* [GUD]UdmGroupKindIndex */
            udmEventStrgIndex = Dem_CfgInfoUdm_CnvUdmEventIndexToUdmEventStrgIndex( UdmGroupKindIndex, UdmFaultRecordPtr->UdmEventIndex );  /* [GUD]UdmGroupKindIndex */
            Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindUdmEvent, ( Dem_u16_RecordIndexType )udmEventStrgIndex );
            retVal = DEM_IRT_OK;
        }
        else
        {
            /* No process */
        }
    }

    return retVal;
}

#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_UdmFaultMngC_SetTSFFListIndex                        */
/* Description   | Sets the data body of the fault record to the fault rec- */
/*               | ord list corresponding to the specified fault index. (f- */
/*               | or Dem_DataCtl subunit)                                  */
/* Preconditions | The specified fault index be within the range of the fa- */
/*               | ult record list.                                         */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        The index for Dem_UserDefinedMemoryTable[].       */
/*               | [in] UdmFaultIndex :                                     */
/*               |        The fault index corresponding to the specific fa- */
/*               |        ult record.                                       */
/*               | [in] SrcUdmFaultRecordPtr :                              */
/*               |                     &Dem_TmpEventMemoryEntry.FaultRecord */
/*               |        The pointer of the fault record corresponding to  */
/*               |         the specified fault index.                       */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmFaultMngC_SetTSFFListIndex
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmFaultIndex,
    P2CONST( Dem_UdmFaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) SrcUdmFaultRecordPtr
)
{
    P2VAR( Dem_UdmFaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) udmFaultRecordPtr;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;

    udmFaultRecordPtr = Dem_UdmFaultMng_GetFaultRecordPtr( UdmGroupKindIndex, UdmFaultIndex );  /* [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/UdmFaultIndex/udmFaultRecordPtr */
    if( udmFaultRecordPtr != NULL_PTR )         /* [GUD:if]udmFaultRecordPtr */
    {
        /*  set TSFFList data.       */
        udmFaultRecordPtr->TimeSeriesFreezeFrameListIndex = SrcUdmFaultRecordPtr->TimeSeriesFreezeFrameListIndex;   /* [GUD:if]udmFaultRecordPtr */

        retVal = DEM_IRT_OK;
    }

    return retVal;
}
#endif /* ( DEM_TSFF_UDM_SUPPORT == STD_ON ) */


/****************************************************************************/
/* Function Name | Dem_UdmFaultMng_SetFaultRecord_Ctl                       */
/* Description   | Set fault record data. (for Control data)                */
/* Preconditions | The specified fault index be within the range of the fa- */
/*               | ult record list.                                         */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        The index for Dem_UserDefinedMemoryTable[].       */
/*               | [in] UdmFaultIndex :                                     */
/*               |        The fault index corresponding to the specific fa- */
/*               |        ult record.                                       */
/*               | [in] SrcUdmFaultRecordPtr :                              */
/*               |                     &Dem_TmpEventMemoryEntry.FaultRecord */
/*               |        The pointer of the fault record corresponding to  */
/*               |         the specified fault index.                       */
/* Return Value  | none.                                                    */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_UdmFaultMng_SetFaultRecord_Ctl
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmFaultIndex,
    P2CONST( Dem_UdmFaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) SrcUdmFaultRecordPtr
)
{
    P2VAR( Dem_UdmFaultRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) udmFaultRecordPtr;

    udmFaultRecordPtr = Dem_UdmFaultMng_GetFaultRecordPtr( UdmGroupKindIndex, UdmFaultIndex );  /* [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/UdmFaultIndex/udmFaultRecordPtr */

    if ( udmFaultRecordPtr != NULL_PTR )            /* [GUD:if]udmFaultRecordPtr */
    {
        /*  set fault data.        */
        udmFaultRecordPtr->UdmEventIndex = SrcUdmFaultRecordPtr->UdmEventIndex;                         /* [GUD]udmFaultRecordPtr */
        udmFaultRecordPtr->UdmFaultOccurrenceOrder = SrcUdmFaultRecordPtr->UdmFaultOccurrenceOrder;     /* [GUD]udmFaultRecordPtr */

        /*  set FFList data.       */
        udmFaultRecordPtr->RecordNumberIndex = SrcUdmFaultRecordPtr->RecordNumberIndex;                 /* [GUD]udmFaultRecordPtr */

#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )
        /*  set TSFFList data.       */
        udmFaultRecordPtr->TimeSeriesFreezeFrameListIndex = SrcUdmFaultRecordPtr->TimeSeriesFreezeFrameListIndex;   /* [GUD]udmFaultRecordPtr */
#endif /* ( DEM_TSFF_UDM_SUPPORT == STD_ON ) */
    }
    return ;
}


#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_UdmFaultMngM_GetRecord                               */
/* Description   | Gets the data body and the consistency counter of the u- */
/*               | dm fault record from the udm fault record list correspo- */
/*               | nding to the specified udm fault index.                  */
/* Preconditions | The specified udm fault index be within the range of the */
/*               |  udm fault record list.                                  */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        The index for Dem_UserDefinedMemoryTable[].       */
/*               | [in] UdmFaultIndex :                                     */
/*               |        The udm fault index corresponding to the specific */
/*               |         udm fault record.                                */
/*               | [out] UdmFaultRecordPtr :                                */
/*               |        The pointer of the udm fault record corresponding */
/*               |         to the specified udm fault index.                */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmFaultMngM_GetRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmFaultIndex,
    P2VAR( Dem_UdmFaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) UdmFaultRecordPtr
)
{
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) udmFaultRecordNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;
    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;

    if( UdmGroupKindIndex < userDefinedMemoryNum )                                              /* [GUD:if]UdmGroupKindIndex */
    {
        udmFaultRecordNum = Dem_UdmFaultRecordTable[UdmGroupKindIndex].DemFaultRecordNum;       /* [GUD]UdmGroupKindIndex */
        if( UdmFaultIndex < udmFaultRecordNum )                                                 /* [GUD:if]UdmFaultIndex */
        {
            Dem_UdmFaultMng_GetRecord_Ctl( UdmGroupKindIndex, UdmFaultIndex, UdmFaultRecordPtr );   /* [GUD]UdmGroupKindIndex *//* [GUD]UdmFaultIndex */
            Dem_UdmFaultMng_GetRecord_MM( UdmGroupKindIndex, UdmFaultIndex, UdmFaultRecordPtr );    /* [GUD]UdmGroupKindIndex *//* [GUD]UdmFaultIndex */
            retVal = DEM_IRT_OK;
        }
    }

    return retVal;
}
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */


/****************************************************************************/
/* Function Name | Dem_UdmFaultMngM_GetFreezeFrameIndex                     */
/* Description   | Gets the FreezeFrameIndex of udm fault record from the u-*/
/*               | dm fault record list corresponding to the specified udm  */
/*               | fault index.                                             */
/* Preconditions | The specified udm fault index and udm kind index be with-*/
/*               | in the range of the udm fault record list.               */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        The index for Dem_UserDefinedMemoryTable[].       */
/*               | [in] UdmFaultIndex :                                     */
/*               |        The udm fault index corresponding to the specific */
/*               |         udm fault record.                                */
/*               | [out] UdmFreezeFrameIndexPtr :                           */
/*               |        The pointer of the udm fault record corresponding */
/*               |         to the specified udm fault index.                */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmFaultMngM_GetFreezeFrameIndex
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmFaultIndex,
    P2VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC, AUTOMATIC ) UdmFreezeFrameIndexPtr
)
{
    P2VAR( Dem_UdmFaultRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) udmFaultRecordPtr;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) recordNumberIndex;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) udmFFDRecordNum;

    udmFaultRecordPtr = Dem_UdmFaultMng_GetFaultRecordPtr( UdmGroupKindIndex, UdmFaultIndex );  /* [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/UdmFaultIndex/udmFaultRecordPtr */

    if ( udmFaultRecordPtr != NULL_PTR )                                                    /* [GUD:if]udmFaultRecordPtr */
    {
        /*--------------------------------------*/
        /*  limit check : RecordNumberIndex     */
        recordNumberIndex   =   udmFaultRecordPtr->RecordNumberIndex;                       /* [GUD]udmFaultRecordPtr */
        udmFFDRecordNum     =   Dem_UdmFFDMng_GetFFDRecordNum( UdmGroupKindIndex );         /* [GUD]UdmGroupKindIndex */
        if( recordNumberIndex >= udmFFDRecordNum )
        {
            recordNumberIndex   =   DEM_UDMFFRECINDEX_INITIAL;
        }
    }
    else
    {
        recordNumberIndex   =   DEM_UDMFFRECINDEX_INITIAL;
    }

    *UdmFreezeFrameIndexPtr = recordNumberIndex;

    return;
}


#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_UdmFaultMngM_GetTSFFListIndex                        */
/* Description   | Gets the TSFFListIndex of udm fault record from the udm  */
/*               | fault record list corresponding to the specified udm fau-*/
/*               | lt index.                                                */
/* Preconditions | The specified udm fault index and udm kind index be with-*/
/*               | in the range of the udm fault record list.               */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        The index for Dem_UserDefinedMemoryTable[].       */
/*               | [in] UdmFaultIndex :                                     */
/*               |        The udm fault index corresponding to the specific */
/*               |         udm fault record.                                */
/*               | [out] UdmTSFFListIndexPtr :                              */
/*               |        The pointer of the udm fault record corresponding */
/*               |         to the specified udm fault index.                */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmFaultMngM_GetTSFFListIndex
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmFaultIndex,
    P2VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC, AUTOMATIC ) UdmTSFFListIndexPtr
)
{
    P2VAR( Dem_UdmFaultRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) udmFaultRecordPtr;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsFFListRecIndex;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsffTotalDTCNum;

    udmFaultRecordPtr = Dem_UdmFaultMng_GetFaultRecordPtr( UdmGroupKindIndex, UdmFaultIndex );  /* [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/UdmFaultIndex/udmFaultRecordPtr */

    if ( udmFaultRecordPtr != NULL_PTR )                                            /* [GUD:if]udmFaultRecordPtr */
    {
        tsffTotalDTCNum     =   Dem_TSFFTotalDTCNum;
        tsFFListRecIndex    =   udmFaultRecordPtr->TimeSeriesFreezeFrameListIndex;  /* [GUD]udmFaultRecordPtr */
        if( tsFFListRecIndex >= tsffTotalDTCNum )
        {
            tsFFListRecIndex    =   DEM_TSFFLISTINDEX_INVALID;
        }
    }
    else
    {
        tsFFListRecIndex    =   DEM_TSFFLISTINDEX_INVALID;
    }
    *UdmTSFFListIndexPtr = tsFFListRecIndex;

    return;
}


/****************************************************************************/
/* Function Name | Dem_UdmFaultMng_InitTSFFListIndex                        */
/* Description   | Clear the TSFFListIndexof udm fault record from the      */
/*               | udm fault record list corresponding to the specified udm */
/*               | fault index.                                             */
/* Preconditions | The specified udm fault index and udm kind index be with-*/
/*               | in the range of the udm fault record list.               */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        The index for Dem_UserDefinedMemoryTable[].       */
/*               | [in] UdmFaultIndex :                                     */
/*               |        The udm fault index corresponding to the specific */
/*               |         udm fault record.                                */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmFaultMng_InitTSFFListIndex
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmFaultIndex
)
{
    P2VAR( Dem_UdmFaultRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) udmFaultRecordPtr;

    udmFaultRecordPtr = Dem_UdmFaultMng_GetFaultRecordPtr( UdmGroupKindIndex, UdmFaultIndex );  /* [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/UdmFaultIndex/udmFaultRecordPtr */

    if ( udmFaultRecordPtr != NULL_PTR )                                                    /* [GUD:if]udmFaultRecordPtr */
    {
        udmFaultRecordPtr->TimeSeriesFreezeFrameListIndex = DEM_TSFFLISTINDEX_INVALID;      /* [GUD]udmFaultRecordPtr */
    }
    return;
}
#endif /* ( DEM_TSFF_UDM_SUPPORT == STD_ON ) */


/****************************************************************************/
/* Function Name | Dem_UdmFaultMng_InitCtlRecordData                        */
/* Description   | Initializes the specified udm fault record.              */
/* Preconditions |                                                          */
/* Parameters    | [out] UdmFaultRecordPtr :                                */
/*               |        The specified udm fault record to initialize.     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmFaultMng_InitCtlRecordData
(
    P2VAR( Dem_UdmFaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) UdmFaultRecordPtr
)
{
    /* Sets initial value to the specified udm fault record. */

    /* The event index. */
    UdmFaultRecordPtr->UdmEventIndex            = DEM_UDMEVENTINDEX_INVALID;

    UdmFaultRecordPtr->UdmFaultOccurrenceOrder = DEM_FAIL_OCCURRENCE_NUM_INVALID;

    /* Initialize FFList. */
    UdmFaultRecordPtr->RecordNumberIndex = DEM_UDMFFRECINDEX_INITIAL;

#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )
    /* Initialize TSFFList. */
    UdmFaultRecordPtr->TimeSeriesFreezeFrameListIndex = DEM_TSFFLISTINDEX_INVALID;
#endif /* ( DEM_TSFF_UDM_SUPPORT == STD_ON ) */

    return ;
}


/****************************************************************************/
/* Function Name | Dem_UdmFaultMng_InitSpecificRecordNumberIndex            */
/* Description   | Initializes specified RecordNumberIndex of the fault     */
/*               | record.                                                  */
/* Preconditions |                                                          */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        The index for Dem_UserDefinedMemoryTable[].       */
/*               | [in]  UdmFaultIndex :                                    */
/*               |        The fault index.                                  */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmFaultMng_InitSpecificRecordNumberIndex
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmFaultIndex
)
{
    P2VAR( Dem_UdmFaultRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) udmFaultRecordPtr;

    udmFaultRecordPtr = Dem_UdmFaultMng_GetFaultRecordPtr( UdmGroupKindIndex, UdmFaultIndex );  /* [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/UdmFaultIndex/udmFaultRecordPtr */

    if ( udmFaultRecordPtr != NULL_PTR )                                                    /* [GUD:if]udmFaultRecordPtr */
    {
        udmFaultRecordPtr->RecordNumberIndex = DEM_UDMFFRECINDEX_INITIAL;                   /* [GUD]udmFaultRecordPtr */

#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )
        udmFaultRecordPtr->TimeSeriesFreezeFrameListIndex = DEM_TSFFLISTINDEX_INVALID;      /* [GUD]udmFaultRecordPtr */
#endif /* ( DEM_TSFF_UDM_SUPPORT == STD_ON ) */
    }
    return;
}


/****************************************************************************/
/* Function Name | Dem_UdmFaultMng_InitRecord_Ctl                           */
/* Description   | Initializes the specified udm fault record.              */
/* Preconditions | The specified UdmGroupKindIndex shall be within the      */
/*               | range of the Dem_UserDefinedMemoryTable[].               */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        The index for Dem_UserDefinedMemoryTable[].       */
/*               | [in] UdmFaultIndex :                                     */
/*               |        The udm fault index corresponding to the specific */
/*               |         udm fault record.                                */
/* Return Value  | void                                                     */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_UdmFaultMng_InitRecord_Ctl
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmFaultIndex
)
{
    P2VAR( Dem_UdmFaultRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) udmFaultRecordPtr;

    udmFaultRecordPtr = Dem_UdmFaultMng_GetFaultRecordPtr( UdmGroupKindIndex, UdmFaultIndex );  /* [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/UdmFaultIndex/udmFaultRecordPtr */

    if ( udmFaultRecordPtr != NULL_PTR )                                                    /* [GUD:if]udmFaultRecordPtr */
    {
        /* Sets initial value to the specified fault record. */
        udmFaultRecordPtr->UdmEventIndex = DEM_UDMEVENTINDEX_INVALID;                       /* [GUD]udmFaultRecordPtr */
        udmFaultRecordPtr->UdmFaultOccurrenceOrder = DEM_FAIL_OCCURRENCE_NUM_INVALID;       /* [GUD]udmFaultRecordPtr */

        /* Initialize FFList. */
        udmFaultRecordPtr->RecordNumberIndex = DEM_UDMFFRECINDEX_INITIAL;                   /* [GUD]udmFaultRecordPtr */

#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )
        /* Initialize TSFFList. */
        udmFaultRecordPtr->TimeSeriesFreezeFrameListIndex = DEM_TSFFLISTINDEX_INVALID;      /* [GUD]udmFaultRecordPtr */
#endif /* ( DEM_TSFF_UDM_SUPPORT == STD_ON ) */
    }
    return ;
}


/****************************************************************************/
/* Function Name | Dem_UdmFaultMng_GetRecord_Ctl                            */
/* Description   | Get udm fault record data. (for Control data)            */
/* Preconditions | The specified UdmGroupKindIndex shall be within the      */
/*               | range of the Dem_UserDefinedMemoryTable[].               */
/*               | The specified udm fault index be within the range of the */
/*               |  udm fault record list.                                  */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        The index for Dem_UserDefinedMemoryTable[].       */
/*               | [in] UdmFaultIndex :                                     */
/*               |        The udm fault index corresponding to the specific */
/*               |         udm fault record.                                */
/*               | [out] DestUdmFaultRecordPtr :                            */
/*               |        The pointer of the udm fault record corresponding */
/*               |         to the specified udm fault index.                */
/* Return Value  | none.                                                    */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_UdmFaultMng_GetRecord_Ctl
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmFaultIndex,
    P2VAR( Dem_UdmFaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) DestUdmFaultRecordPtr
)
{
    P2CONST( Dem_UdmFaultRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) udmFaultRecordPtr;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventIndex;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventConfigureNum;

    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) recordNumberIndex;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) udmFFDRecordNum;
#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )  /*  [FuncSw]    */
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsFFListRecIndex;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsffTotalDTCNum;
#endif  /* ( DEM_TSFF_UDM_SUPPORT == STD_ON )           */

    udmFaultRecordPtr = ( P2CONST( Dem_UdmFaultRecordType, TYPEDEF, DEM_VAR_SAVED_ZONE ) )Dem_UdmFaultMng_GetFaultRecordPtr( UdmGroupKindIndex, UdmFaultIndex );    /* [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/UdmFaultIndex/udmFaultRecordPtr */

    if ( udmFaultRecordPtr != NULL_PTR )                    /* [GUD:if]udmFaultRecordPtr */
    {
        DestUdmFaultRecordPtr->UdmFaultOccurrenceOrder  = udmFaultRecordPtr->UdmFaultOccurrenceOrder;   /* [GUD]udmFaultRecordPtr */
        DestUdmFaultRecordPtr->ConsistencyIdForFault    = udmFaultRecordPtr->ConsistencyIdForFault;     /* [GUD]udmFaultRecordPtr */

        /*--------------------------------------*/
        /*  limit check : UdmEventIndex         */
        udmEventConfigureNum =  Dem_UdmEventConfigureNum;
        udmEventIndex       =   udmFaultRecordPtr->UdmEventIndex;                                       /* [GUD]udmFaultRecordPtr */
        if( udmEventIndex >= udmEventConfigureNum )
        {
            udmEventIndex   =   DEM_UDMEVENTINDEX_INVALID;
        }
        /*  get fault data.        */
        DestUdmFaultRecordPtr->UdmEventIndex    = udmEventIndex;

        /*--------------------------------------*/
        /*  limit check : RecordNumberIndex     */
        recordNumberIndex   =   udmFaultRecordPtr->RecordNumberIndex;                                   /* [GUD]udmFaultRecordPtr */
        udmFFDRecordNum     =   Dem_UdmFFDMng_GetFFDRecordNum( UdmGroupKindIndex );                     /* [GUD]UdmGroupKindIndex */
        if( recordNumberIndex >= udmFFDRecordNum )
        {
            recordNumberIndex   =   DEM_UDMFFRECINDEX_INITIAL;
        }
        DestUdmFaultRecordPtr->RecordNumberIndex        = recordNumberIndex;


#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )  /*  [FuncSw]    */

        /*--------------------------------------------------*/
        /*  limit check : TimeSeriesFreezeFrameListIndex    */
        tsffTotalDTCNum     =   Dem_TSFFTotalDTCNum;
        tsFFListRecIndex    =   udmFaultRecordPtr->TimeSeriesFreezeFrameListIndex;                      /* [GUD]udmFaultRecordPtr */
        if( tsFFListRecIndex >= tsffTotalDTCNum )
        {
            tsFFListRecIndex    =   DEM_TSFFLISTINDEX_INVALID;
        }
        /*  get TSFFList data.       */
        DestUdmFaultRecordPtr->TimeSeriesFreezeFrameListIndex = tsFFListRecIndex;

#endif /* ( DEM_TSFF_UDM_SUPPORT == STD_ON ) */
    }
    else
    {
        DestUdmFaultRecordPtr->UdmEventIndex                    = DEM_UDMEVENTINDEX_INVALID;
        DestUdmFaultRecordPtr->UdmFaultOccurrenceOrder          = DEM_FAIL_OCCURRENCE_NUM_INVALID;
        DestUdmFaultRecordPtr->ConsistencyIdForFault            = DEM_CONSISTENCY_INITIAL;
        DestUdmFaultRecordPtr->RecordNumberIndex                = DEM_UDMFFRECINDEX_INITIAL;
#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )
        DestUdmFaultRecordPtr->TimeSeriesFreezeFrameListIndex   = DEM_TSFFLISTINDEX_INVALID;
#endif /* ( DEM_TSFF_UDM_SUPPORT == STD_ON ) */
    }
    return ;
}


#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_UdmFaultMng_GetRecord_MM                             */
/* Description   | Get udm fault record data. (for MM data)                 */
/* Preconditions | The specified udm fault index be within the range of the */
/*               |  udm fault record list.                                  */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        The index for Dem_UserDefinedMemoryTable[].       */
/*               | [in] UdmFaultIndex :                                     */
/*               |        The udm fault index corresponding to the specific */
/*               |         udm fault record.                                */
/*               | [out] DestUdmFaultRecordPtr :                            */
/*               |        The pointer of the udm fault record corresponding */
/*               |         to the specified udm fault index.                */
/* Return Value  | none.                                                    */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-8-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_UdmFaultMng_GetRecord_MM
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmFaultIndex,
    P2VAR( Dem_UdmFaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) DestUdmFaultRecordPtr
)
{
    P2CONST( Dem_UdmFaultRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) udmFaultRecordPtr;

    udmFaultRecordPtr = ( P2CONST( Dem_UdmFaultRecordType, TYPEDEF, DEM_VAR_SAVED_ZONE ) )Dem_UdmFaultMng_GetFaultRecordPtr( UdmGroupKindIndex, UdmFaultIndex );    /* [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/UdmFaultIndex/udmFaultRecordPtr */

    if ( udmFaultRecordPtr != NULL_PTR )                                                                /* [GUD:if]udmFaultRecordPtr */
    {
        /*  copy CCid.              */
        DestUdmFaultRecordPtr->ConsistencyIdForFault = udmFaultRecordPtr->ConsistencyIdForFault;        /* [GUD]udmFaultRecordPtr */

        /*  copy padding.           */
        Dem_UdmFaultMng_Get_PaddingRecord( UdmGroupKindIndex, UdmFaultIndex, DestUdmFaultRecordPtr );   /* [GUD]UdmGroupKindIndex *//* [GUD]UdmFaultIndex */
    }
    else
    {
        DestUdmFaultRecordPtr->ConsistencyIdForFault = DEM_CONSISTENCY_INITIAL;
    }
    return ;
}
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */


#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_UdmFaultMng_Get_PaddingRecord                        */
/* Description   | Get UdmFaultRecord padding data.                         */
/* Preconditions |                                                          */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        The index for Dem_UserDefinedMemoryTable[].       */
/*               | [in] UdmFaultIndex :                                     */
/*               |        The udm fault index corresponding to the specific */
/*               |         udm fault record.                                */
/*               | [out] UdmFaultRecordPtr :                                */
/*               |        The pointer of the udm fault record corresponding */
/*               |         to the specified udm fault index.                */
/* Return Value  | void                                                     */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-7-0      | no object changed.                                       */
/*   v5-8-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_UdmFaultMng_Get_PaddingRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmFaultIndex,
    P2VAR( Dem_UdmFaultRecordType, AUTOMATIC, AUTOMATIC ) UdmFaultRecordPtr
)
{
    P2CONST( Dem_UdmFaultRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) udmFaultRecordPtr;
    VAR( Dem_u16_PaddingIndexType, AUTOMATIC ) padidx;
    VAR( Dem_u16_PaddingIndexType, AUTOMATIC ) udmFaultRecordBlockPaddingSize;

    udmFaultRecordPtr = ( P2CONST( Dem_UdmFaultRecordType, TYPEDEF, DEM_VAR_SAVED_ZONE ) )Dem_UdmFaultMng_GetFaultRecordPtr( UdmGroupKindIndex, UdmFaultIndex );    /* [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/UdmFaultIndex/udmFaultRecordPtr */

    if ( udmFaultRecordPtr != NULL_PTR )                                                /* [GUD:if]udmFaultRecordPtr */
    {
        udmFaultRecordBlockPaddingSize = Dem_UdmFaultRecordBlockPaddingSize;

        for( padidx = (Dem_u16_PaddingIndexType)0U; padidx < udmFaultRecordBlockPaddingSize; padidx++ )     /* [GUD:for]padidx */
        {
            UdmFaultRecordPtr->Reserve[padidx] = udmFaultRecordPtr->Reserve[padidx];    /* [GUD]udmFaultRecordPtr *//* [GUD]padidx *//* [ARYCHK] DEM_UDMFAULT_RECORD_PADDINGSIZE_TO_BLOCKSIZE / 1 / padidx *//* [ARYCHK] DEM_UDMFAULT_RECORD_PADDINGSIZE_TO_BLOCKSIZE / 1 / padidx */
        }
    }
    return ;
}

/****************************************************************************/
/* Function Name | Dem_UdmFaultMng_InitFRData_Padding                       */
/* Description   | Initializes UdmFaultRecord padding area.                 */
/* Preconditions |                                                          */
/* Parameters    | [out] UdmFaultRecordPtr :                                */
/*               |        The specified udm fault record to initialize.     */
/* Return Value  | void                                                     */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_UdmFaultMng_InitFRData_Padding
(
    P2VAR( Dem_UdmFaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) UdmFaultRecordPtr
)
{
    VAR( Dem_u16_PaddingIndexType, AUTOMATIC ) padidx;
    VAR( Dem_u16_PaddingIndexType, AUTOMATIC ) udmFaultRecordBlockPaddingSize;

    /*    initialize padding area    */
    udmFaultRecordBlockPaddingSize = Dem_UdmFaultRecordBlockPaddingSize;
    for( padidx = (Dem_u16_PaddingIndexType)0U; padidx < udmFaultRecordBlockPaddingSize; padidx++ ) /* [GUD:for]padidx */
    {
        UdmFaultRecordPtr->Reserve[padidx] = DEM_DATA_RESERVE_INITIAL_VALUE;                        /* [GUD]padidx *//* [ARYCHK] DEM_UDMFAULT_RECORD_PADDINGSIZE_TO_BLOCKSIZE / 1 / padidx */
    }

    return;
}

#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */


/****************************************************************************/
/* Function Name | Dem_UdmFaultMng_Init                                     */
/* Description   | Init process of Udm Fault.                               */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmFaultMng_Init
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
)
{
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndex;
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) udmFaultIndex;
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) udmFaultRecordNum;

    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;
    udmGroupKindIndex    = ( Dem_u16_UdmDemMemKindIndexType )RecordFieldIndex;

    if( udmGroupKindIndex < userDefinedMemoryNum )                                                                  /* [GUD:if]udmGroupKindIndex */
    {
        udmFaultRecordNum = Dem_UdmFaultRecordTable[udmGroupKindIndex].DemFaultRecordNum;                           /* [GUD]udmGroupKindIndex */
        for( udmFaultIndex = (Dem_u08_UdmFaultIndexType)0U; udmFaultIndex < udmFaultRecordNum; udmFaultIndex++ )    /* [GUD:for]udmFaultIndex */
        {
            Dem_UdmFaultNvMStatus[ udmGroupKindIndex ].DemUdmFaultNvMStatusPtr[ udmFaultIndex ] = DEM_RECMNGCMN_NVM_STS_NOT_VERIFIED;   /* [GUD]udmGroupKindIndex *//* [GUD]udmFaultIndex *//* [ARYCHK] udmFaultRecordNum / 1 / udmFaultIndex *//* [ARYDESC] The registered data size of Dem_UdmFaultNvMStatus[ udmGroupKindIndex ].DemUdmFaultNvMStatusPtr is the same as Dem_UdmFaultRecordTable[udmGroupKindIndex].DemFaultRecordNum */
        }
    }

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    /* [FuncSw] */
    Dem_UdmFaultMng_InitMirrorMemory();
#endif  /*   ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )  */

    return;
}

/****************************************************************************/
/* Function Name | Dem_UdmFaultMng_InitSavedZone                            */
/* Description   | Initialize savedzone process of udm Fault.               */
/* Preconditions |                                                          */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/*               | [in] InitType :                                          */
/*               |          Initialize savedzone type                       */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmFaultMng_InitSavedZone
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_SavedZoneInitializeType, AUTOMATIC ) InitType      /* MISRA DEVIATION */
)
{
    P2VAR( Dem_UdmFaultRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) udmFaultRecordPtr;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndex;
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) udmFaultIndex;
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) udmFaultRecordNum;

    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;
    udmGroupKindIndex    = ( Dem_u16_UdmDemMemKindIndexType )RecordFieldIndex;

    if( udmGroupKindIndex < userDefinedMemoryNum )                                          /* [GUD:if]udmGroupKindIndex */
    {
        udmFaultRecordNum = Dem_UdmFaultRecordTable[udmGroupKindIndex].DemFaultRecordNum;   /* [GUD]udmGroupKindIndex */
        for( udmFaultIndex = (Dem_u08_UdmFaultIndexType)0U; udmFaultIndex < udmFaultRecordNum; udmFaultIndex++ )    /* [GUD:for]udmFaultIndex */
        {
            udmFaultRecordPtr = Dem_UdmFaultMng_GetFaultRecordPtr( udmGroupKindIndex, udmFaultIndex );  /* [GUD]udmGroupKindIndex *//* [GUD]udmFaultIndex *//* [GUD:RET:Not NULL_PTR] udmGroupKindIndex/udmFaultIndex/udmFaultRecordPtr */

            /* Sets initial value to the specified fault record. */
            udmFaultRecordPtr->UdmEventIndex = DEM_UDMEVENTINDEX_INVALID;                   /* [GUD]udmFaultRecordPtr */
            udmFaultRecordPtr->UdmFaultOccurrenceOrder = DEM_FAIL_OCCURRENCE_NUM_INVALID;   /* [GUD]udmFaultRecordPtr */
            udmFaultRecordPtr->ConsistencyIdForFault = DEM_CONSISTENCY_INITIAL;             /* [GUD]udmFaultRecordPtr */
            /* Initialize FFList. */
            udmFaultRecordPtr->RecordNumberIndex = DEM_UDMFFRECINDEX_INITIAL;               /* [GUD]udmFaultRecordPtr */
#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )
            /* Initialize TSFFList. */
            udmFaultRecordPtr->TimeSeriesFreezeFrameListIndex = DEM_TSFFLISTINDEX_INVALID;  /* [GUD]udmFaultRecordPtr */
#endif /* ( DEM_TSFF_UDM_SUPPORT == STD_ON ) */
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_UdmFaultMng_DataVerify                               */
/* Description   | Verifies Udm Fault data.                                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |          DEM_IRT_OK      : DataVerify completed.         */
/*               |          DEM_IRT_PENDING : Continue DataVerify.          */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmFaultMng_DataVerify
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex     /* MISRA DEVIATION */
)
{
    /* No Process */
    return DEM_IRT_OK;
}

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_UdmFaultMng_SetRecordMirror                          */
/* Description   | Set to the Mirror Memory.                                */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/*               | [in/out] BlockMirrorPtr :                                */
/*               |        Nonvolatile synchronous data information.         */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmFaultMng_SetRecordMirror
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
)
{
    (void)Dem_UdmFaultMngM_GetRecord( (Dem_u16_UdmDemMemKindIndexType)RecordFieldIndex, (Dem_u08_UdmFaultIndexType)BlockMirrorPtr->RecordIndex, &Dem_TmpUdmFaultMirror );  /* no return check required */

    BlockMirrorPtr->MirrorPtr = &Dem_TmpUdmFaultMirror;

    return;
}
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

/****************************************************************************/
/* Function Name | Dem_UdmFaultMng_ClearAllNotVerifiedRecord                */
/* Description   | Clear not verrified record.                              */
/* Preconditions |                                                          */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/*               | [in/out] ClearRecordIndexPtr :                           */
/*               |          target record index                             */
/*               | [in/out] RestOfProcessableNumPtr :                       */
/*               |          rest number of Processable Record               */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |          DEM_IRT_OK      : Completed.                    */
/*               |          DEM_IRT_PENDING : Continue.                     */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmFaultMng_ClearAllNotVerifiedRecord
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    P2VAR( Dem_u16_RecordIndexType, AUTOMATIC, AUTOMATIC ) ClearRecordIndexPtr,
    P2VAR( Dem_u32_TotalRecordNumType, AUTOMATIC, AUTOMATIC ) RestOfProcessableNumPtr
)
{
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndex;
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) udmFaultIndex;
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) udmFaultRecordNum;
    VAR( Dem_u32_TotalRecordNumType, AUTOMATIC ) loopCount;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    loopCount = (Dem_u08_UdmFaultIndexType)0U;
    retVal = DEM_IRT_OK;

    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;
    udmGroupKindIndex = ( Dem_u16_UdmDemMemKindIndexType)RecordFieldIndex;

    if( udmGroupKindIndex < userDefinedMemoryNum )          /* [GUD:if]udmGroupKindIndex */
    {
        udmFaultRecordNum = Dem_UdmFaultRecordTable[udmGroupKindIndex].DemFaultRecordNum;   /* [GUD]udmGroupKindIndex */
        for( udmFaultIndex = (Dem_u08_UdmFaultIndexType)( *ClearRecordIndexPtr ); udmFaultIndex < udmFaultRecordNum; udmFaultIndex++ )          /* [GUD:for]udmFaultIndex */
        {
            if( loopCount < *RestOfProcessableNumPtr )
            {
                if( Dem_UdmFaultNvMStatus[ udmGroupKindIndex ].DemUdmFaultNvMStatusPtr[ udmFaultIndex ] == DEM_RECMNGCMN_NVM_STS_NOT_VERIFIED ) /* [GUD]udmGroupKindIndex *//* [GUD]udmFaultIndex *//* [ARYCHK] udmFaultRecordNum / 1 / udmFaultIndex *//* [ARYDESC] The registered data size of Dem_UdmFaultNvMStatus[ udmGroupKindIndex ].DemUdmFaultNvMStatusPtr is the same as Dem_UdmFaultRecordTable[udmGroupKindIndex].DemFaultRecordNum */
                {
                    Dem_UdmFaultMng_InitRecord_Ctl( udmGroupKindIndex, udmFaultIndex );                                                         /* [GUD]udmGroupKindIndex *//* [GUD]udmFaultIndex *//* [ARYDESC] The registered data size of Dem_UdmFaultNvMStatus[ udmGroupKindIndex ].DemUdmFaultNvMStatusPtr is the same as Dem_UdmFaultRecordTable[udmGroupKindIndex].DemFaultRecordNum */
                    Dem_UdmFaultNvMStatus[ udmGroupKindIndex ].DemUdmFaultNvMStatusPtr[ udmFaultIndex ] = DEM_RECMNGCMN_NVM_STS_NON_TARGET;     /* [GUD]udmGroupKindIndex *//* [GUD]udmFaultIndex *//* [ARYCHK] udmFaultRecordNum / 1 / udmFaultIndex */
                }
                loopCount = loopCount + (Dem_u32_TotalRecordNumType)1U;
            }
            else
            {
                *ClearRecordIndexPtr = (Dem_u08_UdmFaultIndexType)udmFaultIndex;
                retVal = DEM_IRT_PENDING;
                break;
            }
        }

        if( udmFaultIndex >= udmFaultRecordNum )
        {
            *RestOfProcessableNumPtr = ( *RestOfProcessableNumPtr ) - loopCount;  /* no wrap around */
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_UdmFaultMng_GetNumOfStoredFault                      */
/* Description   | Get the number of stored Fault.                          */
/* Preconditions |                                                          */
/* Parameters    | UdmEventMemoryRecordListPtr                              */
/* Return Value  | void                                                     */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmFaultMng_GetNumOfStoredFault
(
    P2VAR( Dem_UdmEventMemoryRecordType, AUTOMATIC, DEM_VAR_NO_INIT )  UdmEventMemoryRecordListPtr
)
{
    P2CONST( Dem_UdmFaultRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) udmFaultRecordPtr;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventConfigureNum;
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) udmFaultIndex;
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) udmFaultRecordNum;
    VAR( Dem_u16_OccrOrderType, AUTOMATIC ) lastOfFaultOccurrenceOrder;

    udmEventConfigureNum = Dem_UdmEventConfigureNum;

    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;
    for( udmGroupKindIndex = (Dem_u16_UdmDemMemKindIndexType)0U; udmGroupKindIndex < userDefinedMemoryNum; udmGroupKindIndex++ )        /* [GUD:for]udmGroupKindIndex */
    {
        udmFaultRecordNum = Dem_UdmFaultRecordTable[udmGroupKindIndex].DemFaultRecordNum;                                               /* [GUD]udmGroupKindIndex */

        lastOfFaultOccurrenceOrder  =   (Dem_u16_OccrOrderType)0U;
        for( udmFaultIndex = (Dem_u08_UdmFaultIndexType)0U; udmFaultIndex < udmFaultRecordNum; udmFaultIndex++ )                        /* [GUD:for]udmFaultIndex */
        {
            udmFaultRecordPtr = ( P2CONST( Dem_UdmFaultRecordType, TYPEDEF, DEM_VAR_SAVED_ZONE ) )Dem_UdmFaultMng_GetFaultRecordPtr( udmGroupKindIndex, udmFaultIndex );    /* [GUD]udmGroupKindIndex *//* [GUD]udmFaultIndex *//* [GUD:RET:IF_GUARDED UdmGroupKindIndex/UdmFaultIndex] udmFaultRecordPtr */

            if( udmFaultRecordPtr->UdmEventIndex < udmEventConfigureNum )                                                               /* [GUD]udmFaultRecordPtr */
            {
                UdmEventMemoryRecordListPtr[udmGroupKindIndex].NumberOfEventMemoryEntries = UdmEventMemoryRecordListPtr[udmGroupKindIndex].NumberOfEventMemoryEntries + (Dem_u08_OrderIndexType)1U;     /* [GUD]udmGroupKindIndex *//* [ARYCHK] DEM_USER_DEFINED_MEMORY_NUM / 1 / udmGroupKindIndex *//* [ARYCHK] DEM_USER_DEFINED_MEMORY_NUM / 1 / udmGroupKindIndex */

                /*  set last of occurrence number.      */
                if ( udmFaultRecordPtr->UdmFaultOccurrenceOrder < DEM_FAIL_OCCURRENCE_NUM_INVALID )                                     /* [GUD]udmFaultRecordPtr */
                {
                    if ( lastOfFaultOccurrenceOrder < udmFaultRecordPtr->UdmFaultOccurrenceOrder )                                      /* [GUD]udmFaultRecordPtr */
                    {
                        lastOfFaultOccurrenceOrder  =   udmFaultRecordPtr->UdmFaultOccurrenceOrder;                                     /* [GUD]udmFaultRecordPtr */
                    }
                }
            }
        }
        UdmEventMemoryRecordListPtr[udmGroupKindIndex].LastOfFaultOccurrenceOrder    =   lastOfFaultOccurrenceOrder + (Dem_u16_OccrOrderType)1U;        /* [GUD]udmGroupKindIndex *//* [ARYCHK] DEM_USER_DEFINED_MEMORY_NUM / 1 / udmGroupKindIndex */

    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_UdmMng_UpdateFaultRecordConsistencyId                */
/* Description   | Decriment and sets the consistency Id of the fault       */
/*               | record to the fault record list corresponding to the     */
/*               | specified fault index.                                   */
/* Preconditions | The specified UdmGroupKindIndex shall be within the      */
/*               | range of the Dem_UserDefinedMemoryTable[].               */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        The index for Dem_UserDefinedMemoryTable[].       */
/*               | [in] UdmFaultIndex :                                     */
/*               |        The fault index corresponding to the specific fa- */
/*               |        ult record.                                       */
/*               | [out] ConsistencyId :                                    */
/*               |        updated consistencyId                             */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_UdmMng_UpdateFaultRecordConsistencyId
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmFaultIndex,
    P2VAR( Dem_u08_ConsistencyIdType, AUTOMATIC, AUTOMATIC ) ConsistencyIdPtr
)
{
    P2VAR( Dem_UdmFaultRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) udmFaultRecordPtr;
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) consistencyId;

    udmFaultRecordPtr = Dem_UdmFaultMng_GetFaultRecordPtr( UdmGroupKindIndex, UdmFaultIndex );  /* [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/UdmFaultIndex/udmFaultRecordPtr */

    if ( udmFaultRecordPtr != NULL_PTR )                                    /* [GUD:if]udmFaultRecordPtr */
    {
        consistencyId = udmFaultRecordPtr->ConsistencyIdForFault;           /* [GUD]udmFaultRecordPtr */

        consistencyId = Dem_UtlCid_CalcConsistencyId( consistencyId );

        udmFaultRecordPtr->ConsistencyIdForFault = consistencyId;           /* [GUD]udmFaultRecordPtr */
        *ConsistencyIdPtr = consistencyId;
    }
    else
    {
        *ConsistencyIdPtr = DEM_CONSISTENCY_INITIAL;
    }
    return;
}


#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_UdmFaultMng_InitMirrorMemory                         */
/* Description   | Initialize the Mirror Memory.                            */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-8-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_UdmFaultMng_InitMirrorMemory
( void )
{

    Dem_UdmFaultMng_InitCtlRecordData( &Dem_TmpUdmFaultMirror );
    Dem_TmpUdmFaultMirror.ConsistencyIdForFault = DEM_CONSISTENCY_INITIAL;

    Dem_UdmFaultMng_InitFRData_Padding( &Dem_TmpUdmFaultMirror );

    return;
}
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */


/****************************************************************************/
/* Function Name | Dem_UdmFaultMng_InitFaultRecord_Ctl                      */
/* Description   | Initializes the specified fault record.                  */
/* Preconditions | The specified UdmGroupKindIndex shall be within the      */
/*               | range of the Dem_UserDefinedMemoryTable[].               */
/*               | [in] UdmGroupKindIndex :                                 */
/*               |        The index for Dem_UserDefinedMemoryTable[].       */
/* Parameters    | [in] UdmFaultIndex :                                     */
/*               |        The fault index corresponding to the specific fa- */
/*               |        ult record.                                       */
/* Return Value  | void                                                     */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_UdmFaultMng_InitFaultRecord_Ctl
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmFaultIndex
)
{
    P2VAR( Dem_UdmFaultRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) udmFaultRecordPtr;

    udmFaultRecordPtr = Dem_UdmFaultMng_GetFaultRecordPtr( UdmGroupKindIndex, UdmFaultIndex );  /* [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/UdmFaultIndex/udmFaultRecordPtr */

    if ( udmFaultRecordPtr != NULL_PTR )                                                /* [GUD:if]udmFaultRecordPtr */
    {
        /* Sets initial value to the specified fault record. */
        udmFaultRecordPtr->UdmEventIndex  = DEM_UDMEVENTINDEX_INVALID;                  /* [GUD]udmFaultRecordPtr */
        udmFaultRecordPtr->UdmFaultOccurrenceOrder  = DEM_FAIL_OCCURRENCE_NUM_INVALID;  /* [GUD]udmFaultRecordPtr */

        /* Initialize FFList. */
        udmFaultRecordPtr->RecordNumberIndex = DEM_UDMFFRECINDEX_INITIAL;               /* [GUD]udmFaultRecordPtr */

#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )
        /* Initialize TSFFList. */
        udmFaultRecordPtr->TimeSeriesFreezeFrameListIndex = DEM_TSFFLISTINDEX_INVALID;  /* [GUD]udmFaultRecordPtr */
#endif /* ( DEM_TSFF_UDM_SUPPORT == STD_ON ) */
    }
    return ;
}


/****************************************************************************/
/* Function Name | Dem_UdmFaultMng_GetFaultRecordPtr                        */
/* Description   | Calculates the pointer of the list of UdmFault Record b- */
/*               | y the specified UdmGroupKindIndex and UdmFaultIndex.     */
/* Preconditions | The specified UdmGroupKindIndex shall be within the      */
/*               | range of the Dem_UserDefinedMemoryTable[].               */
/*               | [in] UdmGroupKindIndex :                                 */
/*               |        The index for Dem_UserDefinedMemoryTable[].       */
/* Parameters    | [in] UdmFaultIndex :                                     */
/*               |        The fault index corresponding to the specific fa- */
/*               |        ult record.                                       */
/* Return Value  | void                                                     */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:Not NULL_PTR] ReturnValue                       */
/* VariableGuard | [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/UdmFaultIndex   */
/* VariableGuard | [GUD:RET:IF_GUARDED UdmGroupKindIndex/UdmFaultIndex] ReturnValue */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC_P2VAR( Dem_UdmFaultRecordType, DEM_VAR_SAVED_ZONE, DEM_CODE ) Dem_UdmFaultMng_GetFaultRecordPtr
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmFaultIndex
)
{
    P2VAR( Dem_UdmFaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) udmFaultRecordPtr;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) faultRecordNum;

    udmFaultRecordPtr = NULL_PTR;

    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;
    if( UdmGroupKindIndex < userDefinedMemoryNum )                                      /* [GUD:if]UdmGroupKindIndex */
    {
        faultRecordNum = Dem_UdmFaultRecordTable[UdmGroupKindIndex].DemFaultRecordNum;  /* [GUD]UdmGroupKindIndex */
        if( UdmFaultIndex < faultRecordNum )                                            /* [GUD:if]UdmFaultIndex */
        {
            udmFaultRecordPtr = &(Dem_UdmFaultRecordTable[UdmGroupKindIndex].DemFaultRecordListStartPtr[UdmFaultIndex]);    /* [GUD]UdmGroupKindIndex *//* [GUD]UdmFaultIndex *//* [ARYCHK] faultRecordNum / 1 / UdmFaultIndex */
        }
    }

    return udmFaultRecordPtr;
}

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_UdmFaultMng_GetEventIdFromRecordData                 */
/* Description   | get event id from record data                            */
/* Preconditions | none                                                     */
/* Parameters    | [in]  RecordFieldIndex :                                 */
/*               | [in]  RecordIndex :                                      */
/*               | [out] EventIdPtr  :                                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_NG : failed                               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmFaultMng_GetEventIdFromRecordData
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) RecordIndex,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventIndex;
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) udmFaultIndex;
    VAR( Dem_u08_UserDefinedMemoryType, AUTOMATIC ) memType;
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInfoTableIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;

    udmEventIndex   =   DEM_UDMEVENTINDEX_INVALID;
    udmFaultIndex   =   ( Dem_u08_UdmFaultIndexType )RecordIndex;
    udmGroupKindIndex = ( Dem_u16_UdmDemMemKindIndexType )RecordFieldIndex;

    retVal  =   DEM_IRT_NG;
    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;
    if( udmGroupKindIndex < userDefinedMemoryNum )          /* [GUD:if]udmGroupKindIndex */
    {
        /* Get udm info table index. */
        udmInfoTableIndex = Dem_CfgInfoUdm_GetDemUserDefinedMemoryInfoTableIndex( udmGroupKindIndex );      /* [GUD]udmGroupKindIndex */

        memType =   Dem_CfgInfoUdm_GetUserDefinedMemoryTypeByMemKind( udmInfoTableIndex );
        if ( memType == DEM_MEMORYTYPE_ASYNCEVENT )
        {
            retVal  =   Dem_UdmMng_GetUdmEventIndexFromUdmFaultRecord( udmGroupKindIndex, udmFaultIndex, &udmEventIndex );      /* [GUD]udmGroupKindIndex */
        }
        else
        {
            /*  DEM_MEMORYTYPE_SYNCEVENT    */

#ifndef JGXSTACK
            Dem_UdmExcFncTable[udmGroupKindIndex].ExclusiveEnterFnc();  /* [GUD]udmGroupKindIndex */
#else   /* JGXSTACK */
            Dem_UdmExcEnterFnc_ForStack();
#endif  /* JGXSTACK */

            retVal  =   Dem_UdmMng_GetUdmEventIndexFromUdmFaultRecord( udmGroupKindIndex, udmFaultIndex, &udmEventIndex );      /* [GUD]udmGroupKindIndex */

#ifndef JGXSTACK
            Dem_UdmExcFncTable[udmGroupKindIndex].ExclusiveExitFnc();   /* [GUD]udmGroupKindIndex */
#else   /* JGXSTACK */
            Dem_UdmExcExitFnc_ForStack();
#endif  /* JGXSTACK */
        }

        if ( retVal == DEM_IRT_OK )
        {
            retVal  =   Dem_UdmMng_GetEventIdFromUdmEventIndex( udmEventIndex, EventIdPtr );
        }
    }
    return retVal;
}
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/*  v5-8-0         :2024-10-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
