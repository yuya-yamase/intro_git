/* Dem_DTC_PreFFD_c(v5-3-0)                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/


/****************************************************************************/
/* Object Name  | Dem/DTC_PreFFD/CODE                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../../inc/Dem_Pm_DTC.h"

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

#if ( DEM_FF_PRESTORAGE_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DTC_CheckRemovePrestoredFF                           */
/* Description   | Checks if remove pre-store freeze frame by DTC status.   */
/* Preconditions | none                                                     */
/* Parameters    | [in] OldDTCStatus : The DTC status will be old.          */
/*               | [in] NewDTCStatus : The DTC status will be new.          */
/* Return Value  | boolean                                                  */
/*               |        TRUE : Event registration processing              */
/*               |                     enforcement.                         */
/*               |        FALSE : Event registration processing             */
/*               |                     non-enforcement.                     */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_DTC_CheckRemovePrestoredFF
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) OldDTCStatus,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) NewDTCStatus
)
{
    VAR( boolean, AUTOMATIC ) retVal;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) oldStatus;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) newStatus;

    retVal = (boolean)FALSE;

    /* Extract TestFailed bit from old DTC status */
    oldStatus = OldDTCStatus & ( (Dem_UdsStatusByteType)DEM_UDS_STATUS_TF );    /*  statusOfDTC : bit0  */
    if( oldStatus == ((Dem_UdsStatusByteType)DEM_UDS_STATUS_TF) )               /*  statusOfDTC : bit0  */
    {
        /* If TestFailed bitof old DTC status is on. */

        /* Extract TestFailed bit from new DTC status */
        newStatus = NewDTCStatus & ( (Dem_UdsStatusByteType)DEM_UDS_STATUS_TF );    /*  statusOfDTC : bit0  */
        if( newStatus == ((Dem_UdsStatusByteType)DEM_DTCSTATUS_BYTE_ALL_OFF) )
        {
            /* If TestFailed bit of new DTC status is off. */

            retVal = ((boolean)TRUE);
        }
    }

    return retVal;
}
#endif  /*   ( DEM_FF_PRESTORAGE_SUPPORT == STD_ON )    */


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
