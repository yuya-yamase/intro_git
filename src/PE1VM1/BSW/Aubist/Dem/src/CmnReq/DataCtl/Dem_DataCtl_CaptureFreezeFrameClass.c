/* Dem_DataCtl_CaptureFreezeFrameClass_c(v5-7-0)                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Dem_DataCtl_CaptureFreezeFrameClass/CODE              */
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
#include "../../../inc/Dem_CmnLib_DataCtl.h"
#include "../../../inc/Dem_CmnLib_DataCtl_CaptureFreezeFrameClass.h"
#include "../../../inc/Dem_CmnLib_DataCtl_FFDOutputJudge.h"
#include "../../../inc/Dem_CmnLib_DataElement.h"
#include "../../../inc/Dem_Utl.h"

#ifndef DEM_SIT_RANGE_CHECK
#else   /* DEM_SIT_RANGE_CHECK */
#include <Dem_SIT_RangeCheck.h>
#endif /* DEM_SIT_RANGE_CHECK */

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
/* Function Name | Dem_Data_CaptureFreezeFrameClass                         */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] EventCtrlIndex :                                    */
/*               |                                                          */
/*               | [in] FreezeFrameClassPtr :                               */
/*               |                                                          */
/*               | [out] FFDataPtr :                                        */
/*               |         The pointer which to store freeze frame data.    */
/*               | [in] monitorData0 :                                      */
/*               |         Monitor test result                              */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-6-0      | branch changed.                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_CaptureFreezeFrameClass /* MISRA DEVIATION */
(
#ifndef DEM_SIT_RANGE_CHECK
#else   /* DEM_SIT_RANGE_CHECK */
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) FFDataSize,
#endif  /* DEM_SIT_RANGE_CHECK */
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    P2CONST( AB_83_ConstV Dem_FreezeFrameClassType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameClassPtr,
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) FFDataPtr,
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData0
)
{
    VAR( boolean, AUTOMATIC ) ffdOutputAllow;
    VAR( Std_ReturnType, AUTOMATIC ) resultOfCallback;
    VAR( Dem_u08_DtElNumPerDIDIndexType, AUTOMATIC ) dataElementClassRefIndex;
    VAR( Dem_u08_DtElNumPerDIDIndexType, AUTOMATIC ) dataElementClassNum;
    VAR( Dem_u16_DIDClassPerFFIndexType, AUTOMATIC ) didClassRefIndex;

    VAR( Dem_u32_FFDStoredIndexType, AUTOMATIC ) freezeFrameDataOffset;
    VAR( Dem_u16_DataElementClassIndexType, AUTOMATIC ) dataElementClassIndex;
    VAR( Dem_u32_DIDClassIndexType, AUTOMATIC ) didClassIndex;

    P2CONST( AB_83_ConstV Dem_DataElementClassType, AUTOMATIC, DEM_CONFIG_DATA ) dataElementClassPtr;
    P2CONST( AB_83_ConstV Dem_DidClassType, AUTOMATIC, DEM_CONFIG_DATA ) didClassPtr;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) demDataElementSize;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) demDidDataSize;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) demDidClassSize;
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;

    if( FreezeFrameClassPtr->DemFreezeFrameReadFnc != NULL_PTR )
    {
        eventId = Dem_CfgInfoCmn_CnvEventCtrlIndexToEventId( EventCtrlIndex );
        demDidClassSize = FreezeFrameClassPtr->DemDidClassSize;

#ifndef JGXSTACK
        resultOfCallback = FreezeFrameClassPtr->DemFreezeFrameReadFnc( eventId, &FFDataPtr[0U], ( uint16 )demDidClassSize );/* [ARYCHK] FFDataSize / 1 / 0U */
#else /* JGXSTACK */
        /* user-defined */
        resultOfCallback = E_OK;
#endif /* JGXSTACK */
        if( resultOfCallback != (Std_ReturnType)E_OK )
        {
            Dem_UtlMem_SetMemory( &FFDataPtr[0U], DEM_DC_FFR_PADDING_DATA, demDidClassSize );/* [ARYCHK] FFDataSize / 1 / 0U */
        }
    }
    else
    {
        freezeFrameDataOffset = (Dem_u32_FFDStoredIndexType)0U;

        for( didClassRefIndex = (Dem_u16_DIDClassPerFFIndexType)0U; didClassRefIndex < FreezeFrameClassPtr->DemDidClassNum; didClassRefIndex++ )    /* [GUD:for]didClassRefIndex */
        {
            didClassIndex = FreezeFrameClassPtr->DemDidClassRef[didClassRefIndex];                                  /* [GUD]didClassRefIndex *//* [GUD:CFG:IF_GUARDED: didClassRefIndex ]didClassIndex *//* [ARYCHK] DEM_DID_NUM_PER_FRAME_MAX_NUM / 1 / didClassRefIndex */
            didClassPtr = &Dem_DIDClassTable[didClassIndex];                                                        /* [GUD]didClassIndex *//* [GUD:CFG:IF_GUARDED: didClassIndex ]didClassPtr */

#ifndef DEM_SIT_RANGE_CHECK
            ffdOutputAllow = Dem_Data_SetFFDOutputJudge( didClassPtr, FFDataPtr, &freezeFrameDataOffset );          /* [GUD]didClassPtr */
#else   /* DEM_SIT_RANGE_CHECK */
            ffdOutputAllow = Dem_Data_SetFFDOutputJudge( FFDataSize, didClassPtr, FFDataPtr, &freezeFrameDataOffset );          /* [GUD]didClassPtr */
#endif  /* DEM_SIT_RANGE_CHECK */

            if( ffdOutputAllow == (boolean)TRUE )
            {
                dataElementClassNum = didClassPtr->DemDataElementClassNum;                                              /* [GUD]didClassPtr */

                for( dataElementClassRefIndex = (Dem_u08_DtElNumPerDIDIndexType)0U; dataElementClassRefIndex < dataElementClassNum; dataElementClassRefIndex++ )    /* [GUD:for]dataElementClassRefIndex */
                {
                    dataElementClassIndex = didClassPtr->DemDataElementClassRef[dataElementClassRefIndex];              /* [GUD]didClassPtr *//* [GUD]dataElementClassRefIndex *//* [GUD:CFG:IF_GUARDED: didClassPtr,dataElementClassRefIndex ]dataElementClassIndex *//* [ARYCHK] DEM_DATAELEMENT_NUM_PER_DID_MAX_NUM / 1 / dataElementClassRefIndex */
                    dataElementClassPtr = &Dem_DataElementClassTable[dataElementClassIndex];                            /* [GUD]dataElementClassIndex *//* [GUD:CFG:IF_GUARDED: dataElementClassIndex ]dataElementClassPtr */
                    demDataElementSize = (Dem_u16_FFDStoredIndexType)dataElementClassPtr->DemDataElementSize;           /* [GUD:CFG]demDataElementSize */

                    resultOfCallback = Dem_DataElement_ReadData( dataElementClassPtr, &FFDataPtr[freezeFrameDataOffset], monitorData0 );            /* [GUD]freezeFrameDataOffset *//* [ARYCHK] FFDataSize / 1 / freezeFrameDataOffset */
                    if( resultOfCallback != (Std_ReturnType)E_OK )
                    {
                        Dem_UtlMem_SetMemory( &FFDataPtr[freezeFrameDataOffset], DEM_DC_FFR_PADDING_DATA, demDataElementSize );                     /* [GUD]freezeFrameDataOffset *//* [ARYCHK] FFDataSize / 1 / freezeFrameDataOffset */
                    }

                    freezeFrameDataOffset = freezeFrameDataOffset + demDataElementSize;                                 /* no wrap around *//* [GUD:CFG:demDidDataSize]demDataElementSize */
                }
            }
            else
            {
                demDidDataSize = (Dem_u16_FFDStoredIndexType)didClassPtr->DemDidDataSize;                               /* [GUD]didClassPtr *//* [GUD:CFG:IF_GUARDED: didClassPtr ]demDidDataSize */
                Dem_UtlMem_SetMemory( &FFDataPtr[freezeFrameDataOffset], DEM_DC_FFR_PADDING_DATA, demDidDataSize );                                 /* [GUD]freezeFrameDataOffset *//* [ARYCHK] FFDataSize / 1 / freezeFrameDataOffset */
                freezeFrameDataOffset = freezeFrameDataOffset + demDidDataSize;                                         /* no wrap around *//* [GUD:CFG:demDidDataSize]freezeFrameDataOffset */
            }
        }
    }

    return;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/*  v5-7-0         :2024-05-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
