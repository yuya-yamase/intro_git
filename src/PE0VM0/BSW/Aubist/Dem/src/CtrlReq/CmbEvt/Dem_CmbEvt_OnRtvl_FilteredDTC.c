/* Dem_CmbEvt_OnRtvl_FilteredDTC_c(v5-5-0)                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/CmbEvt_OnRtvl_FilteredDTC/CODE                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

#if ( DEM_OBD_SUPPORT == STD_ON )
#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )

#include "../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../inc/Dem_Rc_PFCMng.h"
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


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

static VAR( Dem_u08_FaultIndexType, DEM_VAR_NO_INIT ) Dem_NumOfOutputCompletedEventOfFilteredDTC;
static VAR( Dem_u16_EventStrgIndexType, DEM_VAR_NO_INIT ) Dem_OutputCompletedEventStrgIndex[DEM_FAIL_RECORD_NUM];

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE_TRUST          /*  PreInit section               */
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_CODE_TRUST           /*  PreInit section               */
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_CmbEvt_StartOfCheckOutputFilteredDTC                 */
/* Description   | start of check output OBDDTC.                            */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | rename from Dem_CmbEvt_StartOfCheckOutputOBDDTC(v5-3-0). */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_CmbEvt_StartOfCheckOutputFilteredDTC
( void )
{
    Dem_NumOfOutputCompletedEventOfFilteredDTC = ( Dem_u08_FaultIndexType )0U;

    return ;
}

#if ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_CmbEvt_CheckOutputFilteredObdDTC                     */
/* Description   | check output OBDDTC.                                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/* Parameters    | [in] ObdDTCValue :                                       */
/*               |                                                          */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : output OK.                                */
/*               |        FALSE : output NG.                                */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | rename from Dem_CmbEvt_CheckOutputOBDDTC(v5-3-0).        */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_CmbEvt_CheckOutputFilteredObdDTC
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u16_ObdDTCValueType, AUTOMATIC ) ObdDTCValue
)
{
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) numOfOutputCompletedEvent;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) outputEventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u16_ObdDTCValueType, AUTOMATIC ) outputCompletedObdDTC;
    VAR( uint8, AUTOMATIC ) loopcnt;
    VAR( boolean, AUTOMATIC ) retVal;

    numOfOutputCompletedEvent = Dem_NumOfOutputCompletedEventOfFilteredDTC;
    failRecordNum              = Dem_FailRecordNum;
    eventStorageNum            = Dem_PrimaryMemEventStorageNum;
    retVal                     = (boolean)TRUE;

    /* check out range access. */
    if( numOfOutputCompletedEvent < failRecordNum )                                                            /* [GUD:if]numOfOutputCompletedEvent */
    {
        /*  output check. */
        for( loopcnt = ( Dem_u08_FaultIndexType )0U; loopcnt < numOfOutputCompletedEvent; loopcnt++ )          /* [GUD:for]loopcnt */
        {
            outputEventStrgIndex    =   Dem_OutputCompletedEventStrgIndex[loopcnt];                            /* [GUD]loopcnt */
            if ( outputEventStrgIndex < eventStorageNum )                                                       /* [GUD:if]outputEventStrgIndex */
            {
                outputCompletedObdDTC   =   Dem_CfgInfoPm_GetObdDTCValue( outputEventStrgIndex );               /* [GUD]outputEventStrgIndex */

                if( outputCompletedObdDTC == ObdDTCValue )
                {
                    /* if matched, not output. */
                    retVal = (boolean)FALSE;
                    break;
                }
            }
        }
        if( retVal == (boolean)TRUE )
        {
            /* if not matched, store EventStrgIndex. */
            Dem_OutputCompletedEventStrgIndex[numOfOutputCompletedEvent] = EventStrgIndex;                                /* [GUD]numOfOutputCompletedEvent */
            Dem_NumOfOutputCompletedEventOfFilteredDTC = Dem_NumOfOutputCompletedEventOfFilteredDTC + ( Dem_u08_FaultIndexType )1U;
        }
    }
    else
    {
        retVal = (boolean)FALSE;
    }

    return retVal;
}
#endif  /* ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )    */

/****************************************************************************/
/* Function Name | Dem_CmbEvt_CheckOutputFilteredUdsDTC                     */
/* Description   | check output UdsDTC.                                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/* Parameters    | [in] UdsDTCValue :                                       */
/*               |                                                          */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : output OK.                                */
/*               |        FALSE : output NG.                                */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_CmbEvt_CheckOutputFilteredObdDTC.      */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_CmbEvt_CheckOutputFilteredUdsDTC
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) UdsDTCValue
)
{
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) outputUdsDTCValue;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) numberOfEventStrgIndexInDTC;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) outputEventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) numOfOutputCompletedEvent;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) loopcnt;
    VAR( boolean, AUTOMATIC ) retVal;

    numOfOutputCompletedEvent = Dem_NumOfOutputCompletedEventOfFilteredDTC;
    failRecordNum              = Dem_FailRecordNum;
    eventStorageNum            = Dem_PrimaryMemEventStorageNum;
    retVal                     = (boolean)TRUE;

    /*  check number of events that has same DTC.       */
    numberOfEventStrgIndexInDTC =   Dem_CmbEvt_NumOfEventStrgIndex_InDTCGrp( EventStrgIndex );

    if ( numberOfEventStrgIndexInDTC == (Dem_u16_EventStrgIndexType)0U )
    {
        retVal = (boolean)FALSE;
    }
    else if ( numberOfEventStrgIndexInDTC == (Dem_u16_EventStrgIndexType)1U )
    {
        /*  no process. return TRUE.    */
    }
    else
    {
        /* check out range access. */
        if( numOfOutputCompletedEvent < failRecordNum )                                                            /* [GUD:if]numOfOutputCompletedEvent */
        {
            /*  output check. */
            for( loopcnt = ( Dem_u08_FaultIndexType )0U; loopcnt < numOfOutputCompletedEvent; loopcnt++ )          /* [GUD:for]loopcnt */
            {
                outputEventStrgIndex    =   Dem_OutputCompletedEventStrgIndex[loopcnt];                                         /* [GUD]loopcnt */
                if ( outputEventStrgIndex < eventStorageNum )                                                       /* [GUD:if]outputEventStrgIndex */
                {
                    outputUdsDTCValue       =   Dem_CfgInfoPm_GetUdsDTCValue( outputEventStrgIndex );               /* [GUD]outputEventStrgIndex */

                    if( outputUdsDTCValue == UdsDTCValue )
                    {
                        /* if matched, not output. */
                        retVal = (boolean)FALSE;
                        break;
                    }
                }
            }

            if( retVal == (boolean)TRUE )
            {
                /* if not matched, store EventStrgIndex. */
                Dem_OutputCompletedEventStrgIndex[numOfOutputCompletedEvent] = EventStrgIndex;                                /* [GUD]numOfOutputCompletedEvent */
                Dem_NumOfOutputCompletedEventOfFilteredDTC = Dem_NumOfOutputCompletedEventOfFilteredDTC + ( Dem_u08_FaultIndexType )1U;
            }
        }
        else
        {
            retVal = (boolean)FALSE;
        }
    }
    return retVal;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )    */
#endif  /* ( DEM_OBD_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
