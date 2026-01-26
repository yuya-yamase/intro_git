/* Dem_UdmControl_SyncEventEntry_c(v5-3-0)                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/UdmControl_SyncEventEntry/CODE                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_AsyncReq.h"
#include "../../../inc/Dem_Udm_Control.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_Control.h"

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )

#include "../../../cfg/Dem_UserDefMem_Cfg.h"
#include "../../../inc/Dem_Udm_Data.h"
#include "../../../inc/Dem_Rc_UdmMng.h"
#include "../../../inc/Dem_Rc_UdmMngTable.h"
#include "../../../usr/Dem_SavedZone_Callout.h"
#include "../../../usr/Dem_NotifyOverwrittenEventStatus_Callout.h"

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

static VAR( Dem_u08_DemBooleanType, DEM_VAR_NO_INIT ) Dem_UdmCtlExecSyncEventProcFlg;

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_UdmControl_Init                                      */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmControl_InitSyncEventEntry
( void )
{
    Dem_UdmCtlExecSyncEventProcFlg = DEM_BOOLEAN_FALSE;
    return;
}

/****************************************************************************/
/* Function Name | Dem_Control_SetEventCommon                               */
/* Description   | Asynchronous processing function                         */
/*               |     of SetEventFailedWithSyncFreezeFrame                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] UdmEventIndex       : Index of the Udm event.       */
/*               | [in] MonitorData0         : Monitor test result          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_BUSY : failed(retry possible)             */
/*               |        DEM_IRT_MEMORY_OVERFLOW : failed(memory full)     */
/*               |        DEM_IRT_NG : failed(retry not possible)           */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmControl_SyncEventEntry
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_MonitorDataType, AUTOMATIC ) MonitorData0
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retSaveTemp;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retEventRetntion;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) oldDTCStatus;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) newDTCStatus;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) execFlag;
    VAR( boolean, AUTOMATIC ) execUDMClear;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) maxNumberFreezeFrameRecords;

    retVal = DEM_IRT_NG;
    oldDTCStatus = DEM_DTCSTATUS_BYTE_ALL_OFF;
    execFlag = (boolean)FALSE;

    execUDMClear = Dem_UdmDTC_JudgeUdmDTCClearTarget( UdmEventIndex );
    if( execUDMClear == (boolean)TRUE )
    {
        /* If it is clearing, do nothing and return processing success */
        retVal = DEM_IRT_OK;
    }
    else
    {
        SchM_Enter_Dem_SyncEventMemoryAccess();
        if( Dem_UdmCtlExecSyncEventProcFlg != DEM_BOOLEAN_TRUE )
        {
            Dem_UdmCtlExecSyncEventProcFlg = DEM_BOOLEAN_TRUE;
            execFlag = (boolean)TRUE;
        }
        else
        {
            retVal = DEM_IRT_BUSY;
        }

        SchM_Exit_Dem_SyncEventMemoryAccess();
    }

    if( execFlag == (boolean)TRUE )
    {
        /* Obtain a temporary area for event registration */
        retSaveTemp = Dem_UdmData_SaveEventMemoryEntryToSyncTmp( UdmEventIndex );

        if( retSaveTemp == DEM_IRT_OK )
        {
            /* Gets DTC status from the temporary domain. */
            Dem_UdmData_GetDTCStatusFromSyncTmp( &oldDTCStatus );

            /* When there is an event to be updated */
            /* Execute DTC status change processing */
            newDTCStatus = Dem_UdmDTC_ChangeDTCStatusForSyncEventEntry( UdmEventIndex );

            /*--------------------------------------*/
            /*  notify SAVED_ZONE update - start.   */
            Dem_NotifySavedZoneUpdate_Enter();      /*  notify start :  savedzone area will be update.  */
            /*--------------------------------------*/
            {
                retEventRetntion = Dem_UdmData_SetFaultInfoForSyncEventEntry();
                if( retEventRetntion == DEM_IRT_OK )
                {
                    /* Set NewDTCStatus to temporary area */
                    Dem_UdmData_SetDTCStatusToSyncTmp( newDTCStatus );

                    /* get maxNumberFreezeFrameRecords in event. */
                    maxNumberFreezeFrameRecords = Dem_CfgInfoUdm_GetMaxNumberFreezeFrameRecords( UdmEventIndex );

                    if ( maxNumberFreezeFrameRecords > (Dem_u16_UdmFFDIndexType)0U )
                    {
                        Dem_UdmData_CaptureNonObdFreezeFrameToSyncTmp( UdmEventIndex, MonitorData0 );
                    }

                    /*  update data : temporary area to saved_zone area.    */
                    Dem_UdmData_UpdateEventMemoryEntryFromSyncTmp();

                    /*  notify DTC status changed.              */
                    Dem_UdmDTC_TranslateDTCStatusAfterUpdate( UdmEventIndex, &oldDTCStatus, &newDTCStatus );

                    /*  notify EventStatusChanged               */
                    Dem_CfgInfoUdm_TriggerEventStatusChangedFnc( UdmEventIndex, oldDTCStatus, newDTCStatus );

                    retVal = DEM_IRT_OK;
                }
                else
                {
                    retVal = DEM_IRT_MEMORY_OVERFLOW;
                }
            }
            /*--------------------------------------*/
            /*  notify SAVED_ZONE update - end.     */
            Dem_NotifySavedZoneUpdate_Exit();       /*  notify end :  savedzone area will be update.    */
            /*--------------------------------------*/
        }

        Dem_UdmCtlExecSyncEventProcFlg = DEM_BOOLEAN_FALSE;
    }


    return retVal;

}


/****************************************************************************/
/* Function Name | Dem_UdmControl_SyncEventEntry_RefreshRAM                 */
/* Description   | Refresh RAM  - Control                                   */
/* Preconditions | None                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | Called from Dem_MainFunction                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmControl_SyncEventEntry_RefreshRAM
( void )
{
    VAR( volatile Dem_u08_DemBooleanType, AUTOMATIC )                      b_dummyExec;      /*  for store GlobalVariable data    */
    P2VAR( volatile Dem_u08_DemBooleanType, AUTOMATIC, DEM_VAR_NO_INIT )   b_dummyExecPtr;   /*  for GlobalVariable address       */

    /* Exclusion is necessary       */
    SchM_Enter_Dem_SyncEventMemoryAccess();                 /*  enter exclusion             */

    b_dummyExecPtr     = &Dem_UdmCtlExecSyncEventProcFlg;   /*  set GlobalVariable pointer  */
    b_dummyExec        = *b_dummyExecPtr;                   /*  read GlobalVariable data    */
    *b_dummyExecPtr    = b_dummyExec;                       /*  rewrite GlobalVariable data */

    SchM_Exit_Dem_SyncEventMemoryAccess();                  /*  exit exclusion              */

    return;
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
