/* Dem_UdmDTC_DTCStatus_Update_c(v5-3-0)                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/


/****************************************************************************/
/* Object Name  | Dem/UdmDTC_DTCStatus_Update/CODE                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../../cfg/Dem_Cfg.h"

#include "../../../../inc/Dem_CmnLib_ConfigInfo.h"

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )

#include "../../../../cfg/Dem_UserDefMem_Cfg.h"
#include "../../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../../inc/Dem_Udm_Data.h"
#include "../../../../inc/Dem_CmnLib_DTC_DTCStatus.h"

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
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_UdmDTC_ChangeDTCStatus_ToPassed                      */
/* Description   | DTC processing for the event which Dem received (update  */
/*               |  handling of DTC status, update information registratio- */
/*               | n to Dem_Data).                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] OldDTCStatus :                                      */
/*               |        DTC status before the event reception.            */
/*               | [out] NewDTCStatusPtr :                                  */
/*               |        DTC status after the event reception.             */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmDTC_ChangeDTCStatus_ToPassed
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) OldDTCStatus,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) NewDTCStatusPtr
)
{
    /*  passed.         */
    (*NewDTCStatusPtr)   =   Dem_DTC_SetPassedDTCStatus( OldDTCStatus );     /*  OFF : bit0,4,6      */

    return ;
}

/****************************************************************************/
/* Function Name | Dem_UdmDTC_ChangeDTCStatus_ToFailed                      */
/* Description   | DTC processing for the event which Dem received (update  */
/*               |  handling of DTC status, update information registratio- */
/*               | n to Dem_Data).                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] UdmEventIndex :                                     */
/*               |        The event index corresponding to the event ID.    */
/* Parameters    | [in] OldDTCStatus :                                      */
/*               |        DTC status before the event reception.            */
/*               | [out] NewDTCStatusPtr :                                  */
/*               |        DTC status after the event reception.             */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmDTC_ChangeDTCStatus_ToFailed
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) OldDTCStatus,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) NewDTCStatusPtr
)
{
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) tempDtcStatus;
    VAR( boolean, AUTOMATIC ) isWIRIndicator;

    tempDtcStatus   =   Dem_DTC_SetFailedDTCStatus( OldDTCStatus );     /*  bit0,1,2,5 : ON     bit4,6 : OFF    */
    tempDtcStatus   =   Dem_DTC_SetConfirmedDTCBit( tempDtcStatus );    /*  bit3 : ON                           */

    isWIRIndicator  =   Dem_CfgInfoUdm_GetIsWIRIndicator( UdmEventIndex );
    if( isWIRIndicator == (boolean)TRUE )
    {
        tempDtcStatus = Dem_DTC_SetWIRStatusBit( tempDtcStatus );       /*  bit7 : ON                           */
    }
    (*NewDTCStatusPtr)  =   tempDtcStatus;

    return ;
}

/****************************************************************************/
/* Function Name | Dem_UdmDTC_ChangeDTCStatusForSyncEventEntry              */
/* Description   | DTC processing for the event which Dem received (update  */
/*               |  handling of DTC status, update information registratio- */
/*               | n to Dem_Data).                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] UdmEventIndex :                                     */
/*               |        The event index corresponding to the event ID.    */
/* Return Value  | Dem_UdsStatusByteType                                    */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_UdsStatusByteType, DEM_CODE ) Dem_UdmDTC_ChangeDTCStatusForSyncEventEntry
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex
)
{
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) retDtcStatus;
    VAR( boolean, AUTOMATIC ) isWIRIndicator;

    retDtcStatus = Dem_DTC_SetFailedDTCStatusForSyncEventEntry();   /* bit1,2,3,5 : ON  bit0,4,6 : OFF */

    isWIRIndicator = Dem_CfgInfoUdm_GetIsWIRIndicator( UdmEventIndex );
    if( isWIRIndicator == (boolean)TRUE )
    {
        retDtcStatus = Dem_DTC_SetWIRStatusBit( retDtcStatus ); /* bit7 : ON */
    }

    return retDtcStatus;
}

/****************************************************************************/
/* Function Name | Dem_UdmDTC_UpdateDTCStatusByRetentionResult              */
/* Description   | Update DTCStatus by the event retention result           */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventRetentionResult :                              */
/*               |        Flag indicating the event retention result        */
/* Parameters    | [in/out] NewDTCStatusPtr :                               */
/*               |        Flag indicating the event retention result        */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmDTC_UpdateDTCStatusByRetentionResult
(
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) EventRetentionResult,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) NewDTCStatusPtr
)
{
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) tmpDTCStatus;

    tmpDTCStatus            = *NewDTCStatusPtr;

    if( EventRetentionResult == DEM_IRT_NG )
    {
        /* Set Zero to StatusOfDTC bit2, bit3, bit7 */
        tmpDTCStatus = Dem_DTC_ResetAllConfirmedDTCStatus_OnOverflow( tmpDTCStatus );
    }

    *NewDTCStatusPtr = tmpDTCStatus;

    return ;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )  */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
