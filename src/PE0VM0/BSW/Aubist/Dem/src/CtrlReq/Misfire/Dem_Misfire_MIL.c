/* Dem_Misfire_MIL_c(v5-5-0)                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Misfire_MIL/CODE                                      */
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
#include "Dem_Misfire_local.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
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

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Misfire_GetMILBlinkingStatus_CAT                     */
/* Description   | Get the MIL blinking status of CAT.                      */
/* Preconditions | none                                                     */
/* Parameters    | [in] StatusOfDTC :                                       */
/*               |      StatusOfDTC of CAT                                  */
/* Return Value  | boolean :                                                */
/*               |      TRUE  : Status is blinking.                         */
/*               |      FALSE : Status is no blinking.                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | rename from Dem_Misfire_GetCatMILBlinkingStatus(v5-3-0). */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_Misfire_GetMILBlinkingStatus_CAT
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) StatusOfDTC
)
{
    VAR( boolean, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) stopIndicatorBlinkingAtOperationCycleUpdate;

    stopIndicatorBlinkingAtOperationCycleUpdate = Dem_StopIndicatorBlinkingAtOperationCycleUpdate;

    if( stopIndicatorBlinkingAtOperationCycleUpdate == (boolean)FALSE )
    {
        if( (StatusOfDTC & DEM_UDS_STATUS_TF) == DEM_UDS_STATUS_TF )        /*  statusOfDTC : bit0  */
        {
            retVal = (boolean)TRUE;
        }
        else
        {
            retVal = (boolean)FALSE;
        }
    }
    else
    {
        if( ( (StatusOfDTC & DEM_UDS_STATUS_TF) == DEM_UDS_STATUS_TF ) &&       /*  statusOfDTC : bit0  */
            ( (StatusOfDTC & DEM_UDS_STATUS_TFTOC) == DEM_UDS_STATUS_TFTOC ) )  /*  statusOfDTC : bit1  */
        {
            retVal = (boolean)TRUE;
        }
        else
        {
            retVal = (boolean)FALSE;
        }
    }

    return retVal;
}
#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )   */

/******************************************************************************/
/* Function Name | Dem_Misfire_GetMILStatus                                   */
/* Description   | Get MIL status of misfire.                                 */
/* Preconditions | none                                                       */
/* Parameters    | none                                                       */
/* Return Value  | Dem_u08_MisfireIndStatusType :                             */
/*               |      DEM_MISFIRE_IND_OFF : Indicator is off.               */
/*               |      DEM_MISFIRE_IND_CONTINUOUS : Indicator is continuous. */
/*               |      DEM_MISFIRE_IND_BLINKING : Indicator is blinking.     */
/*               |      DEM_MISFIRE_IND_CONTINUOUS | DEM_MISFIRE_IND_BLINKING */
/*               |       : Indicator is continuous and blinking.              */
/* Notes         | -                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/******************************************************************************/
FUNC( Dem_u08_MisfireIndStatusType, DEM_CODE ) Dem_Misfire_GetMILStatus
(
    VAR( Dem_u08_MisfireKindBitType, AUTOMATIC ) availableMisfireKind
)
{
    VAR( Dem_u08_MisfireIndStatusType, AUTOMATIC ) retVal;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) statusOfDTCEmission;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) misfireEmissionEventStrgIndex;
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )   /*  [FuncSw]    */
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) statusOfDTCCAT;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) misfireCatEventStrgIndex;
    VAR( boolean, AUTOMATIC ) blinkingState;
    VAR( boolean, AUTOMATIC ) retCheckWIRBit;
#endif  /*  ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )          */

    retVal = DEM_MISFIRE_IND_OFF;

    if (( availableMisfireKind & DEM_MISFIRE_KINDBIT_EMISSION ) == DEM_MISFIRE_KINDBIT_EMISSION )
    {
        misfireEmissionEventStrgIndex   = Dem_CfgInfoPm_GetEventStrgIndex_MisfireEmission();

        statusOfDTCEmission = DEM_DTCSTATUS_BYTE_ALL_OFF;
        (void)Dem_DataMngC_GetER_StatusOfDTC( misfireEmissionEventStrgIndex, &statusOfDTCEmission );    /* no return check required */
        if( (statusOfDTCEmission & DEM_UDS_STATUS_WIR) == DEM_UDS_STATUS_WIR )          /*  statusOfDTC : bit7  */
        {
            retVal = DEM_MISFIRE_IND_CONTINUOUS;
        }
    }

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )   /*  [FuncSw]    */
    if (( availableMisfireKind & DEM_MISFIRE_KINDBIT_CAT ) == DEM_MISFIRE_KINDBIT_CAT )
    {
        misfireCatEventStrgIndex        = Dem_CfgInfoPm_GetEventStrgIndex_MisfireCAT();

        statusOfDTCCAT = DEM_DTCSTATUS_BYTE_ALL_OFF;
        (void)Dem_DataMngC_GetER_StatusOfDTC( misfireCatEventStrgIndex, &statusOfDTCCAT );     /* no return check required */
        if( (statusOfDTCCAT & DEM_UDS_STATUS_WIR) == DEM_UDS_STATUS_WIR )               /*  statusOfDTC : bit7  */
        {
            retVal = DEM_MISFIRE_IND_CONTINUOUS;
        }

        blinkingState = Dem_Misfire_GetMILBlinkingStatus_CAT( statusOfDTCCAT );

        if( blinkingState == (boolean)TRUE )
        {
            if( retVal != DEM_MISFIRE_IND_CONTINUOUS )
            {
                retCheckWIRBit = Dem_Misfire_CheckWIRBitAtIndicatorBlinking_CAT( statusOfDTCCAT );
                if( retCheckWIRBit == (boolean)TRUE )
                {
                    retVal = DEM_MISFIRE_IND_CONTINUOUS;
                }
            }
            retVal |= DEM_MISFIRE_IND_BLINKING;
        }
    }
#endif  /*  ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )          */

    return retVal;
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

