/* Dem_OccrDTC_TrgDcmReports_c(v5-5-0)                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/OccrDTC_TrgDcmReports/CODE                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#if ( DEM_TRIGGER_DCM_REPORTS == STD_ON )
#include <Dem/Dem_Common.h>
#include <Dcm_Dem.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_DTC_DTCStatus.h"
#include "../../../inc/Dem_Pm_DataAvl.h"
#include "../../../inc/Dem_Pm_OccrDTC.h"

#include "Dem_OccrDTC_local.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
typedef uint8        Dem_u08_OccrDTCTriggerStatusType;                /*  OccuDTC TriggerStatus type     */

#define DEM_REQ_TRG_ON_DTCSTATUS_START      ((Dem_u08_OccrDTCTriggerStatusType)0x00U)
#define DEM_REQ_TRG_ON_DTCSTATUS_STOP       ((Dem_u08_OccrDTCTriggerStatusType)0x11U)

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

static VAR( Dem_u08_OccrDTCTriggerStatusType, DEM_VAR_NO_INIT ) Dem_ReqTriggerOnDTCStatus;

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE_TRUST          /*  PreInit section                     */
#include <Dem_MemMap.h>
/****************************************************************************/
/* Function Name | Dem_OccrDTC_PreInitNotifyDTCStatusChanged                */
/* Description   | Pre-init process of Dem_OccrDTC unit.                    */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE_TRUST ) Dem_OccrDTC_PreInitNotifyDTCStatusChanged        /*  PreInit section     */
(void)
{
    Dem_ReqTriggerOnDTCStatus = DEM_REQ_TRG_ON_DTCSTATUS_STOP;

    return;
}

#define DEM_STOP_SEC_CODE_TRUST           /*  PreInit section                     */
#include <Dem_MemMap.h>

/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_OccrDTC_ReqNotifyDTCStatusChanged                    */
/* Description   | Request Trigger                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in]  TriggerNotification :                              */
/*               |        TRUE  : Request Trigger Start                     */
/*               |        FALSE : Request Trigger Stop                      */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_OccrDTC_ReqNotifyDTCStatusChanged
(
    VAR( boolean, AUTOMATIC ) TriggerNotification
)
{
    if( TriggerNotification == (boolean)FALSE )
    {
        Dem_ReqTriggerOnDTCStatus = DEM_REQ_TRG_ON_DTCSTATUS_STOP;
    }
    else
    {
        Dem_ReqTriggerOnDTCStatus = DEM_REQ_TRG_ON_DTCSTATUS_START;
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_OccrDTC_NotifyDTCStatusChanged                       */
/* Description   | Notify DTCStatus Changed                                 */
/* Preconditions | none                                                     */
/* Parameters    | [in]  EventCtrlIndex   :                                 */
/*               | [in]  OldDTCStatus :                                     */
/*               | [in]  NewDTCStatus :                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_OccrDTC_NotifyDTCStatusChanged
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) OldDTCStatus,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) NewDTCStatus
)
{
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) dtcValue;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) oldDTCStatusTmp;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) newDTCStatusTmp;

    if( Dem_ReqTriggerOnDTCStatus != DEM_REQ_TRG_ON_DTCSTATUS_STOP )
    {
        oldDTCStatusTmp =   OldDTCStatus;
        newDTCStatusTmp =   NewDTCStatus;

        /*------------------------------------------*/
        /*  convert to output statusOfDTC.          */
        /*------------------------------------------*/
        Dem_DTC_CnvUpdateDTCStatus_ForOutput( &oldDTCStatusTmp, &newDTCStatusTmp );

        if( oldDTCStatusTmp != newDTCStatusTmp )
        {
            retVal = Dem_DataAvl_GetUDSDTCByEventStrgIndex( EventStrgIndex, &dtcValue );            /* [GUD:RET:DEM_IRT_OK] EventStrgIndex */
            if( retVal == DEM_IRT_OK )
            {
                (void)Dcm_DemTriggerOnDTCStatus( dtcValue, oldDTCStatusTmp, newDTCStatusTmp );    /* no return check required */
            }
        }
    }

    return;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif /* ( DEM_TRIGGER_DCM_REPORTS == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
