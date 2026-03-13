/* Dem_UdmDataCtl_InfoEvent_c(v5-5-0)                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/UdmDataCtl_InfoEvent/CODE                             */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_Udm_Data.h"
#include "../../../inc/Dem_Rc_UdmMng.h"

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
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
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>



/****************************************************************************/
/* Function Name | Dem_UdmData_GetDTCStatus                                 */
/* Description   | Gets the UDS DTC status byte corresponding to specified  */
/*               |  event ID.                                               */
/* Preconditions | The specified event index corresponding to the event ID  */
/*               |  has been already retrieved.                             */
/* Parameters    | [in] UdmEventIndex :                                     */
/*               |        The event index corresponding to the Udm event ID.*/
/*               | [out] DTCStatusPtr :                                     */
/*               |        The UDS DTC status byte which has been retrieved- */
/*               |        .                                                 */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : The UDS DTC status byte retrieving - */
/*               |        is successful.                                    */
/*               |        DEM_IRT_NG : The UDS DTC status byte retrieving - */
/*               |        is failed.                                        */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_GetDTCStatus
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
)
{
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) eventConfigureNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) result;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) statusOfDTC;
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInfoTableIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;

    /* Initializes the return value to OK. */
    retVal = DEM_IRT_OK;

    statusOfDTC = DEM_DTCSTATUS_BYTE_ALL_OFF;
    eventConfigureNum = Dem_UdmEventConfigureNum;
    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;

    if( UdmEventIndex < eventConfigureNum )         /* [GUD:if]UdmEventIndex */
    {
        /* Get udm group index. */
        udmInfoTableIndex = Dem_CfgInfoUdm_GetMemoryDestination( UdmEventIndex );                                               /* [GUD]UdmEventIndex *//* [GUD:RET:IF_GUARDED: UdmEventIndex ]udmInfoTableIndex */
        udmGroupKindIndex = Dem_CfgInfoUdm_GetUserDefinedMemoryGroupKindIndexByEventIndex( udmInfoTableIndex, UdmEventIndex );  /* [GUD]UdmEventIndex */

        if( udmGroupKindIndex < userDefinedMemoryNum )  /* [GUD:if]udmGroupKindIndex */
        {
#ifndef JGXSTACK
            /* Starts exclusion. */
            Dem_UdmExcFncTable[udmGroupKindIndex].ExclusiveEnterFnc();                                                          /* [GUD]udmGroupKindIndex */
#else   /* JGXSTACK */
            Dem_UdmExcEnterFnc_ForStack();
#endif  /* JGXSTACK */

            /* Gets the status of DTC of the event record corresponding to the specified event index. */
            result = Dem_UdmEventMngC_GetER_StatusOfDTC( UdmEventIndex, &statusOfDTC );                                         /* [GUD]UdmEventIndex */

#ifndef JGXSTACK
            /* Finishes exclusion. */
            Dem_UdmExcFncTable[udmGroupKindIndex].ExclusiveExitFnc();                                                           /* [GUD]udmGroupKindIndex */
#else   /* JGXSTACK */
            Dem_UdmExcExitFnc_ForStack();
#endif  /* JGXSTACK */

            /* Checks the result of retrieving the event record. */
            if( result == DEM_IRT_OK )
            {
                /* Retrieving the event record is successful. */

                /* Stores StatusOfDTC of the event memory entry of temporary area to the specified parameter. */
                *DTCStatusPtr = statusOfDTC;
            }
            else
            {
                /* Retrieving the event record is failed. */

                /* Sets result of retrievng the event record to the return value. */
                retVal = result;
            }
        }
        else
        {
            retVal = DEM_IRT_NG;
        }
    }
    else
    {
        retVal = DEM_IRT_NG;
    }

    /* Returns with the result. */
    return retVal;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )      */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
