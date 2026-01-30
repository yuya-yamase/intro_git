/* Dem_UdmControl_EventInfo_c(v5-7-0)                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/UdmControl_EventInfo/CODE                             */
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
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_Control.h"
#include "../../../inc/Dem_Udm_Control.h"
#include "../../../inc/Dem_Udm_DataAvl.h"
#include "../../../inc/Dem_Udm_Data.h"

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
#include "../../../inc/Dem_Udm_ExternalMem.h"
#include "../../../inc/Dem_Rc_UdmMngTable.h"    /*  for Dem_UdmExcFncTable[]    */

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
/* Function Name | Dem_UdmControl_GetStatusOfDTC                            */
/* Description   | Gets status of DTC by DTC from event record.             */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCValue :                                          */
/*               |        Diagnostic Trouble Code in UDS format             */
/*               | [in] DTCOrigin :                                         */
/*               |        select the source memory the DTCs shall be read - */
/*               |        from                                              */
/*               | [out] DTCStatusPtr :                                     */
/*               |        the status information of the requested DTC       */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Status of DTC is OK                  */
/*               |        DEM_IRT_WRONG_DTC : DTC value not existing (in t- */
/*               |        his format)                                       */
/*               |        DEM_IRT_WRONG_DTCORIGIN : Wrong DTC origin        */
/*               |        DEM_IRT_NG : DTC failed                           */
/*               |                                                          */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-7-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmControl_GetStatusOfDTC
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retAvailMask;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultGetEvent;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventIndex;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventConfigureNum;
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInfoTableIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;
    VAR( Dem_u08_UserDefinedMemoryType, AUTOMATIC ) memType;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) dtcStatusAvailabilityMask;

    retVal = DEM_IRT_WRONG_DTCORIGIN;
    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;
    udmEventConfigureNum = Dem_UdmEventConfigureNum;

    /*  get availability mask.      */
    retAvailMask    =   Dem_CfgInfoUdm_GetDTCStatusAvailabilityMask_ByDTCOrigin( &dtcStatusAvailabilityMask, DTCOrigin );

    if ( retAvailMask == DEM_IRT_OK )
    {
        retTempVal = Dem_UdmControl_CheckDisableDTCInfo( DTCValue, DTCOrigin, &memType, &udmGroupKindIndex );   /* [GUD:RET:DEM_IRT_OK]memType, udmGroupKindIndex */
        if( retTempVal == DEM_IRT_OK )
        {
            if ( memType == DEM_MEMORYTYPE_INVALID )
            {
                /*  illegal DTC origin.     */
                /* No process */
            }
            else if ( memType == DEM_MEMORYTYPE_EXTERNAL )
            {
                /*  mirror memory.          */
                retVal  =   Dem_UdmExternal_GetStatusOfDTC( DTCValue, DTCOrigin, dtcStatusAvailabilityMask, DTCStatusPtr );
            }
            else
            {
                /*--------------------------------------------------------------------------*/
                /* Need to get exclusive [SchM_Enter_Dem_Udm_<ShortName>_EventMemory].      */
                /* These are the reasons why this function needs to get exclusive.          */
                /*  - This function call [DataMng] function directory.                      */
                /*  - This function called from SW-C/Dcm context.                           */
                /*  Waits to finish the exclusive section in the Dem_MainFunction context.  */
#ifndef JGXSTACK
                Dem_UdmExcFncTable[udmGroupKindIndex].ExclusiveEnterFnc();  /* [GUD]udmGroupKindIndex *//* waits completion of updating Diag record data by Dem_MainFunction.      */
                Dem_UdmExcFncTable[udmGroupKindIndex].ExclusiveExitFnc();   /* [GUD]udmGroupKindIndex */
#else   /* JGXSTACK */
                Dem_UdmExcEnterFnc_ForStack();
                Dem_UdmExcExitFnc_ForStack();
#endif  /* JGXSTACK */
                /*--------------------------------------------------------------------------*/

                /* When specified DTC is in update disable status */
                udmEventIndex = Dem_UdmControl_GetDisableDTCRecordEvent();

                if( udmEventIndex < udmEventConfigureNum )                 /* [GUD:if]udmEventIndex */
                {
                    Dem_UdmDTC_GetDTCStatusOfDisabledRecord( udmEventIndex, dtcStatusAvailabilityMask, DTCStatusPtr );  /* [GUD]udmEventIndex */
                    retVal = DEM_IRT_OK;
                }
            }
        }
        else
        {
            /* get UDM info index and memory type by DTCOrigin. */
            memType = Dem_CfgInfoUdm_GetUserDefinedMemoryTypeByDTCOrigin( DTCOrigin, &udmInfoTableIndex ); /* [GUD:RET:Not DEM_MEMORYTYPE_INVALID] udmInfoTableIndex */

            if( memType == DEM_MEMORYTYPE_INVALID )
            {
                /* No process */
            }
            else if ( memType == DEM_MEMORYTYPE_EXTERNAL )
            {
                /*  mirror memory.          */
                retVal  =   Dem_UdmExternal_GetStatusOfDTC( DTCValue, DTCOrigin, dtcStatusAvailabilityMask, DTCStatusPtr );
            }
            else
            {
                /* Get udm event index by DTCValue. */
                resultGetEvent = Dem_UdmDataAvl_GetUdmEventIndexByDTC( DTCValue, udmInfoTableIndex, &udmEventIndex );                           /* [GUD]udmInfoTableIndex *//* [GUD:RET:DEM_IRT_OK]udmEventIndex */

                if( resultGetEvent == DEM_IRT_OK )
                {
                    /* Get udm group index by event index. */
                    udmGroupKindIndex = Dem_CfgInfoUdm_GetUserDefinedMemoryGroupKindIndexByEventIndex( udmInfoTableIndex, udmEventIndex );      /* [GUD]udmInfoTableIndex *//* [GUD]udmEventIndex */

                    if( udmGroupKindIndex < userDefinedMemoryNum )  /* [GUD:if]udmGroupKindIndex */
                    {
                        /*--------------------------------------------------------------------------*/
                        /* Need to get exclusive [SchM_Enter_Dem_Udm_<ShortName>_EventMemory].      */
                        /* These are the reasons why this function needs to get exclusive.          */
                        /*  - This function call [DataMng] function directory.                      */
                        /*  - This function called from SW-C/Dcm context.                           */
                        /*  Waits to finish the exclusive section in the Dem_MainFunction context.  */
#ifndef JGXSTACK
                        Dem_UdmExcFncTable[udmGroupKindIndex].ExclusiveEnterFnc();  /* [GUD]udmGroupKindIndex *//* waits completion of updating Diag record data by Dem_MainFunction.      */
                        Dem_UdmExcFncTable[udmGroupKindIndex].ExclusiveExitFnc();   /* [GUD]udmGroupKindIndex */
#else   /* JGXSTACK */
                        Dem_UdmExcEnterFnc_ForStack();
                        Dem_UdmExcExitFnc_ForStack();
#endif  /* JGXSTACK */
                        /*--------------------------------------------------------------------------*/

                        Dem_UdmDTC_GetDTCStatus( udmEventIndex, dtcStatusAvailabilityMask, DTCStatusPtr );  /* [GUD]udmEventIndex */
                        retVal = DEM_IRT_OK;
                    }
                    else
                    {
                        /* When udmGroupKindIndex is invalid */
                        /* Return when Dem_Dcm unit returned error code, return DEM_IRT_WRONG_DTC */
                        retVal = DEM_IRT_WRONG_DTC;
                    }
                }
                else
                {
                    /* Getting of EventIndex corresponding to DTC failed */
                    retVal = DEM_IRT_WRONG_DTC;
                }
            }
        }
    }
    else
    {
        /* DTCOrigin Error */
        /* No process */
    }
    return retVal;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )      */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
