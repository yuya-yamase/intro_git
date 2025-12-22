/* Dem_UdmMng_GetRecordData_c(v5-5-0)                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataMng_GetRecordData/CODE                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_Rc_UdmMng.h"
#include "Dem_UdmMng_GetRecordData.h"

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )

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
/* Internal Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_UdmMng_GetEventIdFromUdmEventIndex                   */
/* Description   | get event id from record data                            */
/* Preconditions | none                                                     */
/* Parameters    | [in]  UdmEventIndex  :                                   */
/*               | [out] EventIdPtr  :                                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_NG : failed                               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmMng_GetEventIdFromUdmEventIndex
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) eventConfigureNum;

    retVal  =   DEM_IRT_NG;
    eventConfigureNum = Dem_UdmEventConfigureNum;

    if ( UdmEventIndex < eventConfigureNum )            /* [GUD:if]UdmEventIndex */
    {
        retVal  =   Dem_CfgInfoUdm_CnvUdmEventIndexToEventId( UdmEventIndex, EventIdPtr );  /* [GUD]UdmEventIndex */
    }
    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_UdmMng_GetUdmEventIndexFromFaultRecord               */
/* Description   | get event id from record data                            */
/* Preconditions | none                                                     */
/* Parameters    | [in]  UdmGroupKindIndex :                                */
/*               | [in]  UdmFaultIndex  :                                   */
/*               | [out] UdmEventIndexPtr  :                                */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_NG : failed                               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmMng_GetUdmEventIndexFromUdmFaultRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmFaultIndex,
    P2VAR( Dem_u16_UdmEventIndexType, AUTOMATIC, AUTOMATIC ) UdmEventIndexPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;
    VAR( Dem_UdmFaultRecordType, AUTOMATIC ) udmFaultRecord;

    retVal  =   DEM_IRT_NG;
    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;
    if( UdmGroupKindIndex < userDefinedMemoryNum )                                          /* [GUD:if]UdmGroupKindIndex */
    {
        retVal  =   Dem_UdmFaultMngC_GetRecord( UdmGroupKindIndex, UdmFaultIndex, &udmFaultRecord );    /* [GUD]UdmGroupKindIndex */
        if ( retVal == DEM_IRT_OK )
        {
            *UdmEventIndexPtr   =   udmFaultRecord.UdmEventIndex;
        }
    }
    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_UdmMng_GetUdmEventIndexFromUdmFFDRecord              */
/* Description   | get event id from record data                            */
/* Preconditions | none                                                     */
/* Parameters    | [in]  UdmGroupKindIndex :                                */
/*               | [in]  UdmFreezeFrameIndex  :                             */
/*               | [out] UdmEventIndexPtr  :                                */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_NG : failed                               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmMng_GetUdmEventIndexFromUdmFFDRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) UdmFreezeFrameIndex,
    P2VAR( Dem_u16_UdmEventIndexType, AUTOMATIC, AUTOMATIC ) UdmEventIndexPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retRecord;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;
    VAR( Dem_UdmFreezeFrameRecordForCtlType, AUTOMATIC ) freezeFrameRecord;

    retVal = DEM_IRT_NG;

    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;
    if( UdmGroupKindIndex < userDefinedMemoryNum )                                          /* [GUD:if]UdmGroupKindIndex */
    {
        retRecord   =   Dem_UdmFFDMng_GetFFR_MngInfo( UdmGroupKindIndex, UdmFreezeFrameIndex, &freezeFrameRecord ); /* [GUD]UdmGroupKindIndex */
        if ( retRecord == DEM_IRT_OK )
        {
            if ( freezeFrameRecord.RecordStatus == DEM_FFD_STORED )
            {
                *UdmEventIndexPtr  =   freezeFrameRecord.UdmEventIndex;
                retVal = DEM_IRT_OK;
            }
        }
    }

    return retVal;
}

#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_UdmMng_GetUdmEventIndexFromUdmTSFFDRecord            */
/* Description   | get event id from record data                            */
/* Preconditions | none                                                     */
/* Parameters    | [in]  TimeSeriesFreezeFrameIndex :                       */
/*               | [in]  UdmEventIndexPtr  :                                */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_NG : failed                               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmMng_GetUdmEventIndexFromUdmTSFFDRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex,
    P2VAR( Dem_u16_UdmEventIndexType, AUTOMATIC, AUTOMATIC ) UdmEventIndexPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retRecord;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;
    VAR( Dem_UdmFreezeFrameRecordForCtlType, AUTOMATIC ) timeSeriesFreezeFrameRecord;

    retVal = DEM_IRT_NG;

    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;
    if( UdmGroupKindIndex < userDefinedMemoryNum )                                          /* [GUD:if]UdmGroupKindIndex */
    {
        retRecord   =   Dem_UdmTSFFDMng_GetFFR_MngInfo( UdmGroupKindIndex, TimeSeriesFreezeFrameIndex, &timeSeriesFreezeFrameRecord );  /* [GUD]UdmGroupKindIndex */
        if ( retRecord == DEM_IRT_OK )
        {
            if ( timeSeriesFreezeFrameRecord.RecordStatus == DEM_FFD_STORED )
            {
                *UdmEventIndexPtr  =   timeSeriesFreezeFrameRecord.UdmEventIndex;
                retVal = DEM_IRT_OK;
            }
        }
    }

    return retVal;
}
#endif  /* ( DEM_TSFF_UDM_SUPPORT == STD_ON )   */
#endif  /*   ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )  */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
