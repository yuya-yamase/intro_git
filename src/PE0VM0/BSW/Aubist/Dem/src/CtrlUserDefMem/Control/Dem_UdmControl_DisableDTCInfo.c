/* Dem_UdmControl_DisableDTCInfo_c(v5-10-0)                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/UdmControl_DisableDTCInfo/CODE                        */
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

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
#include "../../../inc/Dem_Udm_ExternalMem.h"
#include "../../../inc/Dem_Rc_UdmMngTable.h"    /*  for Dem_UdmExcFncTable[]    */
#include "Dem_Udm_Control_local.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct {
    Dem_u32_DTCValueType                DTCValue;
    Dem_DTCOriginType                   DTCOrigin;
    Dem_u16_UdmEventIndexType           UdmEventIndex;
    Dem_u08_UserDefinedMemoryType       UdmMemoryType;
    Dem_u16_UdmDemMemKindIndexType      UdmGroupKindIndex;
} Dem_UdmCtlDisableDTCInfoType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmControl_DisableDTCRecUpdateFirstRequest
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
);

static FUNC( void, DEM_CODE ) Dem_UdmControl_SetDisableDTCInfo
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u08_UserDefinedMemoryType, AUTOMATIC ) UdmMemoryType,
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex
);

static FUNC( void, DEM_CODE ) Dem_UdmControl_SetDTCRecordUpdateStatus
(
    VAR( Dem_u08_DTCRecordUpdateStatusType, AUTOMATIC ) DTCRecordUpdateStatus
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

static VAR( Dem_UdmCtlDisableDTCInfoType, DEM_VAR_NO_INIT )    Dem_UdmCtlDisableDTCInfo;
static VAR( Dem_u08_DTCRecordUpdateStatusType, DEM_VAR_NO_INIT )    Dem_UdmCtlDTCRecordUpdateStatus;

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
/* Function Name | Dem_UdmControl_DisableDTCRecordUpdate                    */
/* Description   | Disables the specific-DTC's record update                */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCValue :                                          */
/*               |        Selects the DTC in UDS format for which DTC reco- */
/*               |        rd update shall be disabled                       */
/*               | [in] DTCOrigin :                                         */
/*               |        select the source memory for which DTC record up- */
/*               |        date shall be disabled                            */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Event memory update of DTC successf- */
/*               |        ully disabled                                     */
/*               |        DEM_IRT_WRONG_DTC : DTC value not existing (in U- */
/*               |        DS format)                                        */
/*               |        DEM_IRT_WRONG_DTCORIGIN : Wrong DTC origin        */
/*               |        DEM_IRT_PENDING : Disabling is currently not pos- */
/*               |        sible. The caller can retry later.                */
/* Notes         | This function is in DCM main process.                    */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmControl_DisableDTCRecordUpdate
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) firstDisableUpdate;
    VAR( Dem_u08_DTCRecordUpdateStatusType, AUTOMATIC ) updateStatus;

    firstDisableUpdate = (boolean)FALSE;

    /*--------------------------------------------------*/
    /*  start of exclusive [Dem_UdmGetEventMemory].     */
    SchM_Enter_Dem_UdmGetEventMemory();

    /* When not in clear processing */
    updateStatus = Dem_UdmControl_GetDTCRecordUpdateStatus();
    if( updateStatus == DEM_CTL_STS_DTC_UPDATE_ENABLE )
    {
        /* Update enable state */
        /* For shortening exclusive duration, once as update disable status */
        /* When it didn't become update disable, return update enable status */
        Dem_UdmControl_SetDTCRecordUpdateStatus( DEM_CTL_STS_DTC_UPDATE_DISABLE );
        firstDisableUpdate = (boolean)TRUE;
    }
    else
    {
        retVal = DEM_IRT_PENDING;
    }

    /*  end of exclusive [Dem_UdmGetEventMemory].       */
    SchM_Exit_Dem_UdmGetEventMemory();
    /*--------------------------------------------------*/

    /* The first update disable processing */
    if( firstDisableUpdate == (boolean)TRUE )
    {
        retVal = Dem_UdmControl_DisableDTCRecUpdateFirstRequest( DTCValue, DTCOrigin );
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_UdmControl_GetDTCRecordUpdateStatus                  */
/* Description   | Gets DTC record update status.                           */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_DTCRecordUpdateStatusType                        */
/*               |        DEM_CTL_STS_DTC_UPDATE_ENABLE : Update status is  */
/*               |         enable.                                          */
/*               |        DEM_CTL_STS_DTC_UPDATE_DISABLE : Update status i- */
/*               |        s disable.                                        */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_DTCRecordUpdateStatusType, DEM_CODE) Dem_UdmControl_GetDTCRecordUpdateStatus
( void )
{

    return Dem_UdmCtlDTCRecordUpdateStatus;
}


/****************************************************************************/
/* Function Name | Dem_UdmControl_EnableDTCRecordUpdate                     */
/* Description   | Enables the specific-DTC's record update                 */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-10-0     | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmControl_EnableDTCRecordUpdate
( void )
{
    VAR( Dem_u08_UserDefinedMemoryType, AUTOMATIC ) memType;

    /*  mirror memory.  */
    memType =   Dem_UdmCtlDisableDTCInfo.UdmMemoryType;
    if ( memType == DEM_MEMORYTYPE_EXTERNAL )
    {
        Dem_UdmExternal_EnableDTCRecUpdate( Dem_UdmCtlDisableDTCInfo.DTCValue, Dem_UdmCtlDisableDTCInfo.DTCOrigin );
    }

    /* When update is disabled, discard the data held by Dem_Data */
    Dem_UdmData_ClearDisabledRecord();

    /*--------------------------------------------------*/
    /*  start of exclusive [Dem_UdmGetEventMemory].     */
    SchM_Enter_Dem_UdmGetEventMemory();

    /* Initialize the information used in DTC update status management */
    Dem_UdmControl_InitDTCRecordUpdateInfo();

    /*  end of exclusive [Dem_UdmGetEventMemory].       */
    SchM_Exit_Dem_UdmGetEventMemory();
    /*--------------------------------------------------*/

    return ;
}


/****************************************************************************/
/* Function Name | Dem_UdmControl_InitDTCRecordUpdateInfo                   */
/* Description   | Initializes DTC record update info.                      */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmControl_InitDTCRecordUpdateInfo
( void )
{
    /* Initialize update disable information */
    Dem_UdmCtlDisableDTCInfo.DTCValue = (Dem_u32_DTCValueType)0U;
    Dem_UdmCtlDisableDTCInfo.DTCOrigin = (Dem_DTCOriginType)0U;
    Dem_UdmCtlDisableDTCInfo.UdmEventIndex = DEM_UDMEVENTINDEX_INVALID;
    Dem_UdmCtlDisableDTCInfo.UdmMemoryType = DEM_MEMORYTYPE_INVALID;
    Dem_UdmCtlDisableDTCInfo.UdmGroupKindIndex = DEM_UDMTABLEINDEX_INVALID;

    /* Initialize update status */
    Dem_UdmCtlDTCRecordUpdateStatus = DEM_CTL_STS_DTC_UPDATE_ENABLE;

    return;
}


/****************************************************************************/
/* Function Name | Dem_UdmControl_GetDisableDTCRecordEvent                  */
/* Description   | Get disable DTC record event index.                      */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u16_UdmEventIndexType                                */
/*               |        UdmEventIndex                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u16_UdmEventIndexType, DEM_CODE ) Dem_UdmControl_GetDisableDTCRecordEvent
( void )
{
    return Dem_UdmCtlDisableDTCInfo.UdmEventIndex;
}

/****************************************************************************/
/* Function Name | Dem_UdmControl_CheckDisableDTCInfo                       */
/* Description   | Checks disable DTC.                                      */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCValue :                                          */
/*               |        Diagnostic Trouble Code in UDS format             */
/*               | [in] DTCOrigin :                                         */
/*               |        select the source memory the DTCs shall be read - */
/*               |        from                                              */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Target DTC is disable update status- */
/*               |        .                                                 */
/*               |        DEM_IRT_NG : Target DTC is enable update status.  */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmControl_CheckDisableDTCInfo
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    P2VAR( Dem_u08_UserDefinedMemoryType, AUTOMATIC, AUTOMATIC ) UdmMemoryTypePtr,
    P2VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC, AUTOMATIC ) UdmGroupKindIndexPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal = DEM_IRT_NG;

    VAR( Dem_u08_DTCRecordUpdateStatusType, AUTOMATIC ) updateStatus;

    updateStatus = Dem_UdmControl_GetDTCRecordUpdateStatus();
    if( updateStatus == DEM_CTL_STS_DTC_UPDATE_DISABLE )
    {
        /* Update disable status */
        /* Check update disable target */
        if( Dem_UdmCtlDisableDTCInfo.DTCValue == DTCValue )
        {
            if( Dem_UdmCtlDisableDTCInfo.DTCOrigin == DTCOrigin )
            {
                /* When the DTC specified by argument is in update disable status */
                *UdmMemoryTypePtr     = Dem_UdmCtlDisableDTCInfo.UdmMemoryType;
                *UdmGroupKindIndexPtr = Dem_UdmCtlDisableDTCInfo.UdmGroupKindIndex;
                retVal = DEM_IRT_OK;
            }
            else
            {
                /* When the other DTC except one specified by argument is in update disable status */
                /* No process */
            }
        }
        else
        {
            /* When the other DTC except one specified by argument is in update disable status */
            /* No process */
        }
    }
    else
    {
        /* Update enable state */
        /* No process */
    }


    return retVal;
}


/*--------------------------------------------------------------------------*/
/* Unit Internal functions(data)                                            */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* Function Name | Dem_UdmControl_DisableDTCRecUpdateFirstRequest           */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCValue :                                          */
/*               | [in] DTCOrigin :                                         */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_WRONG_DTC :                               */
/*               |        DEM_IRT_WRONG_DTCORIGIN :                         */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmControl_DisableDTCRecUpdateFirstRequest
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetEventIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retSaveDisabledRecord;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventIndex;
    VAR( Dem_u08_UserDefinedMemoryType, AUTOMATIC ) memType;
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInfoTableIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;

    retVal = DEM_IRT_WRONG_DTCORIGIN;
    udmEventIndex = DEM_UDMEVENTINDEX_INVALID;
    udmGroupKindIndex = DEM_UDMTABLEINDEX_INVALID;
    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;

    /* get UDM info index and memory type by DTCOrigin. */
    memType = Dem_CfgInfoUdm_GetUserDefinedMemoryTypeByDTCOrigin( DTCOrigin, &udmInfoTableIndex ); /* [GUD:RET:Not DEM_MEMORYTYPE_INVALID] udmInfoTableIndex */

    if( memType == DEM_MEMORYTYPE_INVALID )
    {
        /* No process */
    }
    else if ( memType == DEM_MEMORYTYPE_EXTERNAL )
    {
        /*  mirror memory.          */
        retVal  =   Dem_UdmExternal_DisableDTCRecUpdate( DTCValue, DTCOrigin );
        if ( retVal == DEM_IRT_OK )
        {
            /* Hold update disable information */
            Dem_UdmControl_SetDisableDTCInfo( DTCValue, DTCOrigin, udmEventIndex, memType, udmGroupKindIndex );
        }
    }
    else
    {
        /* Get udm event index by DTCValue. */
        retGetEventIndex = Dem_UdmDataAvl_GetUdmEventIndexByDTC( DTCValue, udmInfoTableIndex, &udmEventIndex );                         /* [GUD]udmInfoTableIndex *//* [GUD:RET:DEM_IRT_OK]udmEventIndex */

        if( retGetEventIndex == DEM_IRT_OK )    /* [GUD:RET:DEM_IRT_OK]udmEventIndex */
        {
            /* Get udm group index by udm event index. */
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

                retSaveDisabledRecord = Dem_UdmData_SaveDisabledRecord( udmEventIndex );    /* [GUD]udmEventIndex *//* [GUD]udmEventIndex */
                if( retSaveDisabledRecord == DEM_IRT_OK )   /* [GUD:RET:DEM_IRT_OK]udmEventIndex */
                {
                    /* Hold update disable information */
                    Dem_UdmControl_SetDisableDTCInfo( DTCValue, DTCOrigin, udmEventIndex, memType, udmGroupKindIndex ); /* [GUD]udmGroupKindIndex *//* [GUD]udmEventIndex */

                    retVal = DEM_IRT_OK;
                }
                else
                {
                    /* When storing the records except FreezeFrame records related to eventIndex is failure */
                    /* Return when Dem_Dcm unit returned error code, return DEM_IRT_WRONG_DTC */
                    retVal = DEM_IRT_WRONG_DTC;
                }
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
            retVal = DEM_IRT_WRONG_DTC;
        }
    }

    if( retVal != DEM_IRT_OK )
    {
        /* At the first update disable processing, when update disable processing cannot be done */
        /* Because it is as update disable status within exclusive duration, return update enable status */
        Dem_UdmControl_SetDTCRecordUpdateStatus( DEM_CTL_STS_DTC_UPDATE_ENABLE );
    }
    else
    {
        /* No process */
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_UdmControl_SetDisableDTCInfo                         */
/* Description   | Sets disable DTC info.                                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCValue :                                          */
/*               |        Diagnostic Trouble Code in UDS format             */
/*               | [in] DTCOrigin :                                         */
/*               |        select the source memory the DTCs shall be read - */
/*               |        from                                              */
/*               | [in] UdmEventIndex :                                     */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-8-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_UdmControl_SetDisableDTCInfo
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u08_UserDefinedMemoryType, AUTOMATIC ) UdmMemoryType,
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex
)
{
    Dem_UdmCtlDisableDTCInfo.DTCValue = DTCValue;
    Dem_UdmCtlDisableDTCInfo.DTCOrigin = DTCOrigin;
    Dem_UdmCtlDisableDTCInfo.UdmEventIndex = UdmEventIndex;
    Dem_UdmCtlDisableDTCInfo.UdmMemoryType = UdmMemoryType;
    Dem_UdmCtlDisableDTCInfo.UdmGroupKindIndex = UdmGroupKindIndex;

    Dem_UdmControl_SetDisableRecordUpdateInfoForEDR();

    return;
}


/****************************************************************************/
/* Function Name | Dem_UdmControl_SetDTCRecordUpdateStatus                  */
/* Description   | Sets DTC record update status.                           */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCRecordUpdateStatus :                             */
/*               |        DTC record update status.                         */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_UdmControl_SetDTCRecordUpdateStatus
(
    VAR( Dem_u08_DTCRecordUpdateStatusType, AUTOMATIC ) DTCRecordUpdateStatus
)
{

    Dem_UdmCtlDTCRecordUpdateStatus = DTCRecordUpdateStatus;

    return;
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
/*  v5-8-0         :2024-10-29                                              */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
