/* Dem_UdmControl_OpCycleUpdNormal_c(v5-5-0)                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/UdmControl_OpCycleUpdNormal/CODE                      */
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
#include "../../../inc/Dem_CmnLib_DTC_DTCStatus.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_Udm_Data.h"
#include "../../../inc/Dem_Udm_Control.h"
#include "../../../inc/Dem_Rc_UdmMng.h"
#include "../../../inc/Dem_Rc_UdmMngTable.h"

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
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Unit External functions                                                  */
/*--------------------------------------------------------------------------*/
/****************************************************************************/
/* Function Name | Dem_UdmControl_NormalEventMemoryEntryByOpCycle           */
/* Description   | update EventMemoryEntry of operation cycle .             */
/* Preconditions | none                                                     */
/* Parameters    | [in]  EventPos                                           */
/*               |                                                          */
/*               | [in] OperationCycleIndex : Operation cycle index.        */
/*               | [in] HealingAgingCycleFlag                               */
/*               | [in] FailureCycleFlag :                                  */
/*               |                                                          */
/*               | [out] NeedGenOrderListPtr :                              */
/*               |              need GenOrderList or not.                   */
/*               |                  TRUE    :   need generate .             */
/*               |                  FALSE   :   no need generate .          */
/*               | [out] ExecHealingPtr :                                   */
/*               |              execute healing or not.                     */
/*               |                  TRUE    :   execute healing.            */
/*               |                  FALSE   :   no execute healing.         */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmControl_NormalEventMemoryEntryByOpCycle
(
    VAR( Dem_u16_EventPosType, AUTOMATIC ) EventPos,                        /* [PRMCHK:CALLER] */
    VAR( Dem_u08_OpcycUpdateHealingAgingCycleType, AUTOMATIC ) HealingAgingCycleFlag,
    VAR( Dem_u08_OpcycUpdateFailureCycleType, AUTOMATIC ) FailureCycleFlag,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) NeedGenOrderListPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ExecHealingPtr
)
{
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventIndex;
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInfoTableIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) newDTCStatus;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) oldDTCStatus;
    VAR( Std_ReturnType, AUTOMATIC ) resultOfCallback;

    /* set initial vale. */
    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;

    if (( FailureCycleFlag != DEM_OPCYCUPD_FLCYC_INITIALVALUE ) || ( HealingAgingCycleFlag != DEM_OPCYCUPD_HACYC_INITIALVALUE ))
    {
        (void)Dem_CfgInfoUdm_CnvEventPosToUdmEventIndex( EventPos, &udmEventIndex );    /* no return check required */

        /* Get udm table info index by udm event index. */
        udmInfoTableIndex = Dem_CfgInfoUdm_GetMemoryDestination( udmEventIndex );   /* [GUDCHK:CALLER]EventPos *//* [GUD:RET:IF_GUARDED: udmEventIndex ]udmInfoTableIndex */

        /* Get udm group index by udm event index. */
        udmGroupKindIndex = Dem_CfgInfoUdm_GetUserDefinedMemoryGroupKindIndexByEventIndex( udmInfoTableIndex, udmEventIndex );

        if( udmGroupKindIndex < userDefinedMemoryNum )                      /* [GUD:if]udmGroupKindIndex */
        {
            /* Exclude StatusOfDTC update process by Dem_SetEventFailedWithSyncFreezeFrame */
#ifndef JGXSTACK
            Dem_UdmExcFncTable[udmGroupKindIndex].ExclusiveEnterFnc();      /* [GUD]udmGroupKindIndex */
#else   /* JGXSTACK */
            Dem_UdmExcEnterFnc_ForStack();
#endif  /* JGXSTACK */
            /*  get current statusOfDTC     */
            ( void )Dem_UdmEventMngC_GetER_StatusOfDTC( udmEventIndex, &oldDTCStatus ); /* no return check required */
            newDTCStatus    =   oldDTCStatus;

            if ( HealingAgingCycleFlag != DEM_OPCYCUPD_HACYC_INITIALVALUE )
            {
                /*  check bit1,6 is OFF. for condition check of bit2OFF.    */
                if( ( ( oldDTCStatus & DEM_UDS_STATUS_TFTOC ) == DEM_DTCSTATUS_BYTE_ALL_OFF ) && ( ( oldDTCStatus & DEM_UDS_STATUS_TNCTOC ) == DEM_DTCSTATUS_BYTE_ALL_OFF ) )
                {
                    /*  base statusOfDTC bit2(PendingBit) == ON    */
                    if( ( oldDTCStatus & DEM_UDS_STATUS_PDTC ) == DEM_UDS_STATUS_PDTC ) /*  statusOfDTC : bit2  */
                    {
                        newDTCStatus = Dem_DTC_ResetPendingDTCBit( newDTCStatus );
                    }
                }
            }

            if ( FailureCycleFlag != DEM_OPCYCUPD_FLCYC_INITIALVALUE )
            {
                /*  update DTC status : bit1,6      */
                newDTCStatus = Dem_DTC_RestartOperationCycleDTCStatus( newDTCStatus, FailureCycleFlag );
            }

            /*  set new DTC status to record.   */
            Dem_UdmEventMngC_SetER_StatusOfDTC( udmEventIndex, newDTCStatus );

#ifndef JGXSTACK
            Dem_UdmExcFncTable[udmGroupKindIndex].ExclusiveExitFnc();       /* [GUD]udmGroupKindIndex */
#else   /* JGXSTACK */
            Dem_UdmExcExitFnc_ForStack();
#endif  /* JGXSTACK */
            Dem_CfgInfoUdm_TriggerInitMForEFnc( udmEventIndex, DEM_INIT_MONITOR_RESTART, &resultOfCallback );
        }

    }

    *NeedGenOrderListPtr    =   (boolean)FALSE;
    *ExecHealingPtr         =   (boolean)FALSE;

    return ;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )  */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
