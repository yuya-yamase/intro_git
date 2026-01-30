/* Dem_UdmDTC_FilDTC_c(v5-7-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/UdmDTC_FilDTC/CODE                                    */
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
#include "../../../../inc/Dem_Udm_DataAvl.h"
#include "../../../../inc/Dem_Udm_Data.h"
#include "../../../../inc/Dem_Udm_ExternalMem.h"
#include "../../../../inc/Dem_Rc_UdmMngTable.h"
#include "../../../../cfg/Dem_UserDefMem_Cfg.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
#define DEM_DTC_FILDTC_SEARCHUDMEVENTCOUNT_INVALID  ((Dem_u16_FilDTCSearchNumType)0xFFFFU)

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmDTC_CheckDTCForFilter
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusMask,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusAvailabilityMask,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
);

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmDTC_CheckDTCStatusForFilter
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusMask,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

static VAR( Dem_u16_UdmEventIndexType, DEM_VAR_NO_INIT )  Dem_UdmFilteredDTCSearchEventIndex;
static VAR( Dem_u16_UdmEventIndexType, DEM_VAR_NO_INIT )  Dem_UdmFilteredDTCSearchEventIndexEnd;
static VAR( Dem_u16_FilDTCSearchNumType, DEM_VAR_NO_INIT )  Dem_UdmEventSearchCnt;
static VAR( Dem_UdsStatusByteType, DEM_VAR_NO_INIT ) Dem_UdmDTCStatusAvailabilityMask;
static VAR( Dem_u08_UdmMemoryInfoTableIndexType, DEM_VAR_NO_INIT ) Dem_UdmFilteredMemoryInfoTableIndex;
static VAR( Dem_u16_UdmDemMemKindIndexType, DEM_VAR_NO_INIT ) Dem_UdmFilteredMemoryGroupKindIndex;
static VAR( Dem_u16_UdmDemMemKindIndexType, DEM_VAR_NO_INIT ) Dem_UdmFilteredMemoryGroupKindIndexEnd;

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>


/****************************************************************************/
/* Function Name | Dem_UdmDTC_SetFilteredDTC                                */
/* Description   | The function set the DTC filter.                         */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCStatusMask :                                     */
/*               | [in] DTCOrigin :                                         */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Filter was accepted                  */
/*               |        DEM_IRT_NG : Wrong filter selected                */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmDTC_SetFilteredDTC
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusMask,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_UserDefinedMemoryType, AUTOMATIC ) memType;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) dtcStatusAvailabilityMask;
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInfoTableIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndexStart;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndexNum;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventIndexStart;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventIndexNum;

    /* Set initilal value */
    Dem_UdmFilteredDTCSearchEventIndex  = DEM_UDMEVENTINDEX_INVALID;
    Dem_UdmFilteredDTCSearchEventIndexEnd    = ( Dem_u16_UdmDemMemKindIndexType )0U;
    Dem_UdmEventSearchCnt                    = DEM_DTC_FILDTC_SEARCHUDMEVENTCOUNT_INVALID;
    Dem_UdmFilteredMemoryInfoTableIndex      = DEM_UDMINFOTABLEINDEX_INVALID;
    Dem_UdmFilteredMemoryGroupKindIndex = DEM_UDMTABLEINDEX_INVALID;
    Dem_UdmFilteredMemoryGroupKindIndexEnd   = ( Dem_u16_UdmDemMemKindIndexType )0U;
    Dem_UdmDTCStatusAvailabilityMask         = DEM_DTCSTATUS_BYTE_ALL_OFF;

    retVal = DEM_IRT_NG;

    /* get udm info index and memory type by DTCOrigin. */
    memType = Dem_CfgInfoUdm_GetUserDefinedMemoryTypeByDTCOrigin( DTCOrigin, &udmInfoTableIndex ); /* [GUD:RET:Not DEM_MEMORYTYPE_INVALID] udmInfoTableIndex */

    if( memType != DEM_MEMORYTYPE_INVALID )
    {
        /*  get availability mask.      */
        dtcStatusAvailabilityMask        = Dem_CfgInfoUdm_GetDTCStatusAvailabilityMask( udmInfoTableIndex );                                /* [GUD]udmInfoTableIndex */
        Dem_UdmDTCStatusAvailabilityMask = dtcStatusAvailabilityMask;

        if ( memType == DEM_MEMORYTYPE_EXTERNAL )
        {
            /*  mirror memory.      */
            retVal = Dem_UdmExternal_SetFilteredDTC( DTCOrigin, DTCStatusMask, dtcStatusAvailabilityMask );
        }
        else
        {
            /* get udm group index. */
            Dem_CfgInfoUdm_GetUserDefinedMemoryGroupKindIndex( udmInfoTableIndex, &udmGroupKindIndexStart, &udmGroupKindIndexNum );         /* [GUD]udmInfoTableIndex */

            /* get event index start and num in udm group. */
            udmEventIndexStart  = Dem_CfgInfoUdm_GetStartUdmEventIndex_InMemory( udmGroupKindIndexStart );
            udmEventIndexNum    = Dem_CfgInfoUdm_GetConfigureNumOfUdmEventIndex_InMemory( udmGroupKindIndexStart );

            /* latch data */
            Dem_UdmFilteredDTCSearchEventIndex  = udmEventIndexStart;
            Dem_UdmFilteredDTCSearchEventIndexEnd    = udmEventIndexStart + udmEventIndexNum;
            Dem_UdmFilteredMemoryGroupKindIndex = udmGroupKindIndexStart;
            Dem_UdmFilteredMemoryGroupKindIndexEnd   = udmGroupKindIndexStart + udmGroupKindIndexNum;

            Dem_UdmEventSearchCnt                    = ( Dem_u16_UdmDemMemKindIndexType )0U;

            retVal  =   DEM_IRT_OK;
        }

        Dem_UdmFilteredMemoryInfoTableIndex = udmInfoTableIndex;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_UdmDTC_SearchFilteredDTC                             */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCStatusMask :                                     */
/*               | [in] DTCOrigin :                                         */
/*               | [out] DTCValuePtr :                                      */
/*               | [out] DTCStatusPtr :                                     */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_PENDING :                                 */
/*               |        DEM_IRT_NO_MATCHING_ELEMENT :                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmDTC_SearchFilteredDTC
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusMask,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
)
{
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) searchUdmEventIndex;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) filteredDTCSearchUdmEventIndexStart;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) filteredDTCSearchUdmEventIndexNum;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) filteredDTCSearchUdmEventIndexEnd;
    VAR( Dem_u16_FilDTCSearchNumType, AUTOMATIC ) searchLoopNumByCycle;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupLoopEnd;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) retChkEventAvailable;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retChkDTC;
    VAR( boolean, AUTOMATIC ) loopEndFlag;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmFilteredMemoryGroupKindIndex;

    VAR( Dem_u08_UserDefinedMemoryType, AUTOMATIC ) memType;
    memType =   Dem_CfgInfoUdm_GetUserDefinedMemoryTypeByMemKind( Dem_UdmFilteredMemoryInfoTableIndex );

    if ( memType == DEM_MEMORYTYPE_EXTERNAL )
    {
        /*  mirror memory.      */
        retVal  =   Dem_UdmExternal_GetNextFilteredDTC( DTCOrigin, DTCStatusMask, Dem_UdmDTCStatusAvailabilityMask, DTCValuePtr, DTCStatusPtr );
    }
    else
    {
        retVal = DEM_IRT_NO_MATCHING_ELEMENT;
        udmGroupLoopEnd = Dem_UdmFilteredMemoryGroupKindIndexEnd;   /* Set udm group num. */

        /* Loop by udm group */
        for( udmFilteredMemoryGroupKindIndex = Dem_UdmFilteredMemoryGroupKindIndex; udmFilteredMemoryGroupKindIndex < udmGroupLoopEnd; udmFilteredMemoryGroupKindIndex++ ) /* [GUD:for]udmFilteredMemoryGroupKindIndex */
        {
            filteredDTCSearchUdmEventIndexStart = Dem_UdmFilteredDTCSearchEventIndex;
            filteredDTCSearchUdmEventIndexEnd   = Dem_UdmFilteredDTCSearchEventIndexEnd;

            searchLoopNumByCycle = Dem_FilDTCSearchLoopNumByCycle;
            loopEndFlag = (boolean)FALSE;

            /*--------------------------------------------------------------------------*/
            /* Need to get exclusive [SchM_Enter_Dem_Udm_<ShortName>_EventMemory].      */
            /* These are the reasons why this function needs to get exclusive.          */
            /*  - This function call [DataMng] function directory.                      */
            /*  - This function called from SW-C/Dcm context.                           */
            /*  Waits to finish the exclusive section in the Dem_MainFunction context.  */
#ifndef JGXSTACK
            Dem_UdmExcFncTable[udmFilteredMemoryGroupKindIndex].ExclusiveEnterFnc();    /* [GUD]udmFilteredMemoryGroupKindIndex *//* waits completion of updating Diag record data by Dem_MainFunction.      */
            Dem_UdmExcFncTable[udmFilteredMemoryGroupKindIndex].ExclusiveExitFnc();     /* [GUD]udmFilteredMemoryGroupKindIndex */
#else   /* JGXSTACK */
            Dem_UdmExcEnterFnc_ForStack();
            Dem_UdmExcExitFnc_ForStack();
#endif  /* JGXSTACK */
            /*--------------------------------------------------------------------------*/

            /* Loop by event num included udm group */
            for( searchUdmEventIndex = filteredDTCSearchUdmEventIndexStart; searchUdmEventIndex < filteredDTCSearchUdmEventIndexEnd; searchUdmEventIndex++ )    /* [GUD:for]searchUdmEventIndex */
            {
                /* return pending, if search count exceed configuration value */
                if( Dem_UdmEventSearchCnt < searchLoopNumByCycle )  /* [GUD:if]Dem_UdmEventSearchCnt */
                {
                    retChkEventAvailable = Dem_UdmDataAvl_GetEvtAvl( searchUdmEventIndex );
                    if( retChkEventAvailable == (boolean) TRUE )
                    {
                        /* check DTCStatus */
                        retChkDTC = Dem_UdmDTC_CheckDTCForFilter( searchUdmEventIndex, DTCStatusMask, Dem_UdmDTCStatusAvailabilityMask, DTCValuePtr, DTCStatusPtr );    /* [GUD]searchUdmEventIndex *//* [GUD:RET:DEM_IRT_OK]DTCValuePtr, DTCStatusPtr */

                        if( retChkDTC == DEM_IRT_OK )
                        {
                            /* Set next search event index. */
                            Dem_UdmFilteredDTCSearchEventIndex = searchUdmEventIndex + ( Dem_u16_UdmDemMemKindIndexType )1U;
                            retVal = DEM_IRT_OK;
                            loopEndFlag =  (boolean)TRUE;

                            /*======================================================*/
                            /*  No reset of Dem_UdmEventSearchCnt this timing.      */
                            /*  next call of this function, only return pending.    */
                            /*  Dem_UdmEventSearchCnt is reset at return of pending.*/
                            /*======================================================*/
                        }
                    }
                    Dem_UdmEventSearchCnt++;    /* Count total event num        */
                }
                else
                {
                    /* reset search counter for return pending */
                    Dem_UdmEventSearchCnt = ( Dem_u16_UdmDemMemKindIndexType )0U;
                    /* Set next search event index. */
                    Dem_UdmFilteredDTCSearchEventIndex = searchUdmEventIndex;
                    /* Set ExecFlg TRUE */
                    retVal = DEM_IRT_PENDING;
                    loopEndFlag = (boolean)TRUE;
                }

                if( loopEndFlag == (boolean)TRUE )
                {
                    break;
                }
            }

            if( loopEndFlag == (boolean)TRUE )
            {
                /* When search event is completed, or search count exceed configuration value. */
                break;
            }
            else
            {
                /* DEM_IRT_NO_MATCHING_ELEMENT */
                if( ( Dem_UdmFilteredMemoryGroupKindIndex + ( Dem_u16_UdmDemMemKindIndexType )1U ) < Dem_UdmFilteredMemoryGroupKindIndexEnd )  /* [GUD:if]Dem_UdmFilteredMemoryGroupKindIndex */
                {
                    /* Search udm group is finish, set next udm group index. */
                    /* Set next udm group index */
                    Dem_UdmFilteredMemoryGroupKindIndex     = Dem_UdmFilteredMemoryGroupKindIndex + ( Dem_u16_UdmDemMemKindIndexType )1U;
                    Dem_UdmFilteredDTCSearchEventIndex      = Dem_CfgInfoUdm_GetStartUdmEventIndex_InMemory( Dem_UdmFilteredMemoryGroupKindIndex );   /* Get event index in next udm group */
                    filteredDTCSearchUdmEventIndexNum       = Dem_CfgInfoUdm_GetConfigureNumOfUdmEventIndex_InMemory( Dem_UdmFilteredMemoryGroupKindIndex ); /* Get num of next event index */
                    Dem_UdmFilteredDTCSearchEventIndexEnd   = Dem_UdmFilteredDTCSearchEventIndex + filteredDTCSearchUdmEventIndexNum; /* Get end index in next udm group */
                }
                else
                {
                    /* All udm group is competed */
                    /* No process */
                }
            }
        }
    }

    return retVal;
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Dem_UdmDTC_CheckDTCForFilter                             */
/* Description   | check the filter and get is DTC and its severity         */
/* Preconditions | Dem_DTC_SetDTCFilter being executed.                     */
/* Parameters    | [in] UdmEventIndex :                                     */
/*               |        The event index corresponding to the Udm event ID.*/
/*               | [in] DTCStatusMask :                                     */
/*               | [out] DTCValuePtr :                                      */
/*               |        Receives the DTC value in respective format of t- */
/*               |        he filter returned by this function.If the retur- */
/*               |        n value of the function is other than DEM_FILTER- */
/*               |        ED_OK this parameter does not contain valid data. */
/*               | [out] DTCStatusPtr :                                     */
/*               |        This parameter receives the status information o- */
/*               |        f the requested DTC.If the return value of the f- */
/*               |        unction call is other than DEM_STATUS_OK this pa- */
/*               |        rameter does not contain valid data.0x00...0xFF - */
/*               |        match DTCStatusMask as defined in ISO14229-1.     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : find matching element                */
/*               |        DEM_IRT_NG : not find matching element            */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmDTC_CheckDTCForFilter
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,      /* [PRMCHK:CALLER] */
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusMask,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusAvailabilityMask,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetDTCAndStatus;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retChkDTCStatus;

    retVal = DEM_IRT_NG;

    retGetDTCAndStatus = Dem_UdmDTC_GetDTCAndStatus( UdmEventIndex, DTCStatusAvailabilityMask, DTCValuePtr, DTCStatusPtr ); /* [GUDCHK:CALLER]UdmEventIndex */

    if( retGetDTCAndStatus == DEM_IRT_OK )
    {
        retChkDTCStatus = Dem_UdmDTC_CheckDTCStatusForFilter( DTCStatusMask, DTCStatusPtr );

        if( retChkDTCStatus == DEM_IRT_OK )
        {
            retVal = DEM_IRT_OK;
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_UdmDTC_CheckDTCStatusForFilter                       */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCStatusMask :                                     */
/*               |                                                          */
/*               | [in/out] DTCStatusPtr :                                  */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmDTC_CheckDTCStatusForFilter
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusMask,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) maskedStatus;

    retVal = DEM_IRT_OK;

    /* check use DTC Mask */
    if( DTCStatusMask != DEM_DTCSTATUS_BYTE_ALL_OFF )
    {
        /* Mask the status Of DTC */
        maskedStatus = ( (*DTCStatusPtr) & DTCStatusMask );

        if( maskedStatus != DEM_DTCSTATUS_BYTE_ALL_OFF )
        {
            /* DTCStatus which fits it in a mask condition. */
            /* No Process */
        }
        else
        {
            /* DTCStatus which does not fit it in a mask condition. */
            retVal = DEM_IRT_NG;
        }
    }
    else
    {
        /* Consider DTCStatus to agree in a mask condition. */
        /* No Process */
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
