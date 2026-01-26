/* Dem_DataAvl_PriMem_DTC_c(v5-5-0)                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataAvl_PriMem_DTC/CODE                               */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_DataAvl.h"
#include "../../../inc/Dem_Pm_DataAvl.h"

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

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataAvl_GetEventStrgIndex_InDTCGrp
(
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr
);

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
/* Function Name | Dem_DataAvl_GetDTCByEventStrgIndex                       */
/* Description   | Gets the DTC value which is corresponding to the specif- */
/*               | ied event index and the specified format is configured - */
/*               | in.                                                      */
/* Preconditions | The specified event index corresponding to the event ID  */
/*               |  has been already retrieved.                             */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the event ID.    */
/*               | [in] DTCFormat :                                         */
/*               |        DTCFormat type of Dem's external definition.      */
/*               | [out] DTCValuePtr :                                      */
/*               |        The DTC value corresponding the specified event - */
/*               |        index.                                            */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEN_IRT_OK : Retrieving the DTC value was succes- */
/*               |        sful.                                             */
/*               |        DEM_IRT_NG : Retrieving the DTC value was failed- */
/*               |        .                                                 */
/*               |        DEM_IRT_NODATAAVAILABLE : There is no DTC config- */
/*               |        ured in the requestedformat                       */
/*               |                                                          */
/* Notes         | This function is access to only Config ROM data.         */
/*               | This function is not access to global RAM data.          */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:DEM_IRT_OK] EventStrgIndex                      */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataAvl_GetDTCByEventStrgIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;

    if( DTCFormat == DEM_DTC_FORMAT_UDS )
    {
        retVal = Dem_DataAvl_GetUDSDTCByEventStrgIndex( EventStrgIndex , DTCValuePtr ); /* [GUD:RET:DEM_IRT_OK] EventStrgIndex */
    }
    else if( DTCFormat == DEM_DTC_FORMAT_OBD )
    {
        retVal = Dem_DataAvl_GetOBDDTCByEventStrgIndex( EventStrgIndex , DTCValuePtr ); /* [GUD:RET:DEM_IRT_OK] EventStrgIndex */
    }
    else
    {
        /* Out of range. */
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_DataAvl_GetUDSDTCByEventStrgIndex                       */
/* Description   | Gets the UDS DTC value which is corresponding to the sp- */
/*               | ecified event index and the specified format is configu- */
/*               | redin.                                                   */
/* Preconditions | The specified event index corresponding to the event ID  */
/*               |  has been already retrieved.                             */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the event ID.    */
/*               | [out] DTCValuePtr :                                      */
/*               |        The DTC value corresponding the specified event - */
/*               |        index.                                            */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEN_IRT_OK :  EventStrgIndex has UDS DTC.         */
/*               |        DEM_IRT_NODATAAVAILABLE :                         */
/*               |                      EventStrgIndex has no UDS DTC.      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:DEM_IRT_OK] EventStrgIndex                      */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataAvl_GetUDSDTCByEventStrgIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) resultValidateDTC;
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) udsDTCValue;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;

    retVal = DEM_IRT_NG;

    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    if( EventStrgIndex < eventStorageNum )                                          /* [GUD:if]EventStrgIndex */
    {
        /* Initializes the return value to OK. */
        retVal = DEM_IRT_NODATAAVAILABLE;

        udsDTCValue         =   Dem_CfgInfoPm_GetUdsDTCValue( EventStrgIndex );     /* [GUD]EventStrgIndex */
        resultValidateDTC   =   Dem_DataAvl_ValidateDTC( udsDTCValue );

        if( resultValidateDTC == (boolean)TRUE )
        {
            /* Store the DTC value of the DTC table held in the designated DTC value storage area. */
            *DTCValuePtr = udsDTCValue;

            retVal = DEM_IRT_OK;
        }
    }
    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_DataAvl_GetOBDDTCByEventStrgIndex                    */
/* Description   | Gets the OBD DTC value which is corresponding to the sp- */
/*               | ecified event index and the specified format is configu- */
/*               | redin.                                                   */
/* Preconditions | The specified event index corresponding to the event ID  */
/*               |  has been already retrieved.                             */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the event ID.    */
/*               | [out] DTCValuePtr :                                      */
/*               |        The DTC value corresponding the specified event - */
/*               |        index.                                            */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEN_IRT_OK :  EventStrgIndex has OBD DTC.         */
/*               |        DEM_IRT_NODATAAVAILABLE :                         */
/*               |                      EventStrgIndex has no OBD DTC.      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:DEM_IRT_OK] EventStrgIndex                      */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataAvl_GetOBDDTCByEventStrgIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr /* MISRA DEVIATION */
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
#if ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )    /*  [FuncSw]        */
    VAR( boolean, AUTOMATIC ) eventOBDKind;
#endif  /*   ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )               */


    retVal = DEM_IRT_NG;

    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    if( EventStrgIndex < eventStorageNum )                                                          /* [GUD:if]EventStrgIndex */
    {
        /* Initializes the return value. */
        retVal = DEM_IRT_NODATAAVAILABLE;

#if ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )    /*  [FuncSw]        */
        /*  get event OBD kind.     */
        eventOBDKind    =   Dem_CfgInfoPm_CheckEventKindOfOBD_InEvtStrgGrp( EventStrgIndex );       /* [GUD]EventStrgIndex */
        if( eventOBDKind == (boolean)TRUE ) /*  OBD     */
        {
            *DTCValuePtr = (Dem_u32_DTCValueType)Dem_CfgInfoPm_GetObdDTCValue( EventStrgIndex );    /* [GUD]EventStrgIndex */

            retVal = DEM_IRT_OK;
        }
#endif  /*   ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )               */
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_DataAvl_GetEventStrgIndexByDTC                          */
/* Description   | Gets the event index corresponding to the specified DTC  */
/*               |  value.                                                  */
/* Preconditions | The specified DTC value has been already registered.     */
/* Parameters    | [in] DTCValue :                                          */
/*               |        The specified DTC value.                          */
/*               | [out] EventStrgIndexPtr :                                */
/*               |        The event index corresponding to the specified D- */
/*               |        TC value.                                         */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Retrieving the event index was succ- */
/*               |        essful.                                           */
/*               |        DEM_IRT_NG : Retrieving the event index was fail- */
/*               |        ed.                                               */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:DEM_IRT_OK] EventStrgIndexPtr                   */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataAvl_GetEventStrgIndexByDTC
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr,
    P2VAR( Dem_MisfireCylinderNumberType, AUTOMATIC, AUTOMATIC ) MisfireCylinderNumberPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) targetEventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) searchEventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireCylinder;
    VAR( boolean, AUTOMATIC ) resultValidateDTC;
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) udsDTCValue;

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( Dem_u08_MisfireKindBitType, AUTOMATIC ) availableMisfireKind;
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */
#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON ) /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) bDelegate;
#endif  /* ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )          */

    /* Initializes the return value to NG. */
    retVal = DEM_IRT_NG;

    targetEventStrgIndex  =   DEM_EVENTSTRGINDEX_INVALID;
    misfireCylinder =   DEM_MISFIRE_CYL_NUM_INVALID;

    resultValidateDTC = Dem_DataAvl_ValidateDTC( DTCValue );

    if( resultValidateDTC != (boolean)TRUE )
    {
        /* No process */
    }
    else
    {
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
        misfireCylinder =   Dem_CfgInfoPm_GetMisfireCylinderNumberByUdsDTC( DTCValue );
        if ( misfireCylinder != DEM_MISFIRE_CYL_NUM_INVALID )
        {
            /*  it's misfire cylinder DTC.      */
            availableMisfireKind    =   Dem_DataAvl_GetMisfireCylDTCAvailableAndEventStrgIndex( &targetEventStrgIndex );  /* [GUD:RET:Not DEM_MISFIRE_KINDBIT_NONE] eventStrgIndex */
            if( availableMisfireKind != DEM_MISFIRE_KINDBIT_NONE )
            {
                /* Sets the return value to OK. */
                retVal = DEM_IRT_OK;
            }
        }
        else
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */
        {
            eventStorageNum =   Dem_PrimaryMemEventStorageNum;

            /* Event index loops from 0 to eventStorageNum.*/
            for( searchEventStrgIndex = (Dem_u16_EventStrgIndexType)0U; searchEventStrgIndex < eventStorageNum; searchEventStrgIndex++ )    /* [GUD:for]searchEventStrgIndex */
            {
#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON ) /*  [FuncSw]    */
                bDelegate   =   Dem_CmbEvt_CheckDelegateEventStrgIndex_InDTCGrp( searchEventStrgIndex );    /* [GUD]searchEventStrgIndex */
                if( bDelegate == (boolean)TRUE )
#endif  /* ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )          */
                {
                    /* Confirm comparison between DemDtcValue of the held DTC table and specified DTC value*/
                    udsDTCValue =   Dem_CfgInfoPm_GetUdsDTCValue( searchEventStrgIndex );                   /* [GUD]searchEventStrgIndex */
                    if( udsDTCValue == DTCValue )
                    {
                        targetEventStrgIndex    =   searchEventStrgIndex;
                        retVal = Dem_DataAvl_GetEventStrgIndex_InDTCGrp( &targetEventStrgIndex );
                        /* Leave the loop. */
                        break;
                    }
                    else
                    {
                        /* No process */
                    }
                }
            }
        }
    }

    /* Store the event index in the specified event index storage area. */
    *EventStrgIndexPtr          =   targetEventStrgIndex;
    *MisfireCylinderNumberPtr   =   misfireCylinder;

    /* Returns with the result. */
    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_DataAvl_GetEventStrgIndex_InDTCGrp                   */
/* Description   | Gets the event index corresponding to the specified DTC  */
/*               |  value.                                                  */
/* Preconditions | The specified DTC value has been already registered.     */
/* Parameters    | [in/out] EventStrgIndexPtr :                             */
/*               |        The event index corresponding to the event ID.    */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Retrieving the event index was succ- */
/*               |        essful.                                           */
/*               |        DEM_IRT_NG : Retrieving the event index was fail- */
/*               |        ed.                                               */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:DEM_IRT_OK] EventStrgIndexPtr                   */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataAvl_GetEventStrgIndex_InDTCGrp
(
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr
)
{
    VAR( boolean, AUTOMATIC ) availableStatus;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON ) /*  [FuncSw]    */
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndexNum;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndexCnt;
#endif  /* ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )          */

    /* Initializes the return value to NG. */
    retVal = DEM_IRT_NG;

    eventStrgIndex  =   ( *EventStrgIndexPtr );

#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON ) /*  [FuncSw]    */

    /* get num of event index in DTC group. */
    eventStrgIndexNum = Dem_CmbEvt_NumOfEventStrgIndex_InDTCGrp( eventStrgIndex );

    if ( eventStrgIndexNum == (Dem_u16_EventStrgIndexType)1U )
#endif  /* ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )          */
    {
        /* Checks event available status */
        availableStatus = Dem_DataAvl_GetEvtAvl_InEvtStrgGrp( eventStrgIndex );
        if( availableStatus == (boolean)TRUE )
        {
            /* Sets the return value to OK. */
            retVal = DEM_IRT_OK;
        }
    }
#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON ) /*  [FuncSw]    */
    else
    {
        for( eventStrgIndexCnt = ( Dem_u16_EventStrgIndexType )0U; eventStrgIndexCnt < eventStrgIndexNum; eventStrgIndexCnt++ )
        {
            /* Checks event available status */
            availableStatus = Dem_DataAvl_GetEvtAvl_InEvtStrgGrp( eventStrgIndex );
            if( availableStatus == (boolean)TRUE )
            {
                /* Sets the return value to OK. */
                retVal = DEM_IRT_OK;
                /* Leave the loop. */
                break;
            }

            /* get next event index. */
            eventStrgIndex = Dem_CmbEvt_GetNextEventStrgIndex_InDTCGrp( eventStrgIndex );
        }
    }
#endif  /* ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )          */

    /* Store the event index in the specified event index storage area. */
    ( *EventStrgIndexPtr )  =   eventStrgIndex;

    /* Returns with the result. */
    return retVal;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
