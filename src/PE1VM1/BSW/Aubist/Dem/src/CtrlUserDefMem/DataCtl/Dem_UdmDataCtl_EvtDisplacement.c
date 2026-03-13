/* Dem_UdmDataCtl_EvtDisplacement_c(v5-5-0)                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/UdmDataCtl_EvtDisplacement/CODE                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
#include "../../../cfg/Dem_UserDefMem_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_Udm_Data.h"
#include "../../../inc/Dem_Rc_UdmMng.h"
#include "../../../inc/Dem_CmnLib_DTC_DTCStatus.h"

#include "Dem_UdmDataCtl_EvtDisplacement_local.h"

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


/****************************************************************************/
/* Function Name | Dem_UdmData_SetEventDisplacement                         */
/* Description   | Sets fault record which to be overwritten and which to   */
/*               | overwrite.                                               */
/* Preconditions |                                                          */
/* Parameters    | [in]   UdmInfoTableIndex                                 */
/*               | [in]   UdmEventIndexOverWrite                            */
/*               | [out]  UdmEventIndexOverwrittenPtr                       */
/*               |              overwritten event.                          */
/*               | [out]  OldDTCStatusAtOverwrittenPtr                      */
/*               |              statusOfDTC of overwritten event.           */
/*               | [out]  NewDTCStatusAtOverwrittenPtr                      */
/*               |              statusOfDTC of overwritten event.           */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : The fault record will be overwritten */
/*               |        DEM_IRT_NG : The fault record will not be overwr- */
/*               |                     itten                                */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_SetEventDisplacement
(
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) UdmInfoTableIndex,
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndexOverWrite,
    P2VAR( Dem_u16_UdmEventIndexType, AUTOMATIC, AUTOMATIC ) UdmEventIndexOverwrittenPtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) OldDTCStatusAtOverwrittenPtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) NewDTCStatusAtOverwrittenPtr
)
{
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventIndexOverwritten;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_EventDisplacementStrategyType, AUTOMATIC ) eventDispStrategy;
    VAR( Dem_u08_EventPriorityType, AUTOMATIC ) eventPriority;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;

    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;

    /*  get EventDisplacementStrategy.  */
    eventDispStrategy   =   Dem_CfgInfoUdm_GetEventDisplacementStrategy( UdmInfoTableIndex, UdmEventIndexOverWrite );

    if ( eventDispStrategy == DEM_DISPLACEMENT_NONE )
    {
        /*  always not overwrite.       */
        retVal  =   DEM_IRT_NG;
    }
    else
    {
        /*  judge overwrite.            */
        eventPriority   =   Dem_CfgInfoUdm_GetEventPriority( UdmEventIndexOverWrite );

        /* Get udm group index by udm event index. */
        udmGroupKindIndex = Dem_CfgInfoUdm_GetUserDefinedMemoryGroupKindIndexByEventIndex( UdmInfoTableIndex, UdmEventIndexOverWrite );

        if( udmGroupKindIndex < userDefinedMemoryNum )  /* [GUD:if]udmGroupKindIndex */
        {
            retVal  =   Dem_UdmFaultMngC_GetLowestPriorityFaultIndex( udmGroupKindIndex, eventPriority, eventDispStrategy, &udmEventIndexOverwritten ); /* [GUD]udmGroupKindIndex */
            if ( retVal == DEM_IRT_OK )
            {
                *UdmEventIndexOverwrittenPtr    =   udmEventIndexOverwritten;           /*  output overwritten event index  */

                /*  output current statusOfDTC by overwritten event.    */
                (void)Dem_UdmEventMngC_GetER_StatusOfDTC( udmEventIndexOverwritten, OldDTCStatusAtOverwrittenPtr ); /* no return check required */

                /*----------------------------------------------*/
                /*  Update statusOfDTC at Overflow occurred.    */
                /*----------------------------------------------*/
                *NewDTCStatusAtOverwrittenPtr = Dem_DTC_ResetAllConfirmedDTCStatus_OnOverflow( *OldDTCStatusAtOverwrittenPtr );
            }
        }
        else
        {
            retVal  =   DEM_IRT_NG;
        }
    }

    return retVal;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
