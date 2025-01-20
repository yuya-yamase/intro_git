/* Dem_DataCtl_CaptureFreezeFrameClass_c(v5-5-0)                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
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
/* Parameters    | [in] FreezeFrameClassPtr :                               */
/*               |                                                          */
/*               | [out] FFDataPtr :                                        */
/*               |         The pointer which to store freeze frame data.    */
/*               | [in] monitorData0 :                                      */
/*               |         Monitor test result                              */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_CaptureFreezeFrameClass /* MISRA DEVIATION */
(
    P2CONST( AB_83_ConstV Dem_FreezeFrameClassType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameClassPtr,
    P2VAR( uint8, AUTOMATIC, DEM_VAR_NO_INIT ) FFDataPtr,
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData0
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) ffdOutputAllow;
    VAR( Std_ReturnType, AUTOMATIC ) resultOfCallback;
    VAR( Dem_u08_DtElNumPerDIDIndexType, AUTOMATIC ) dataElementClassRefIndex;
    VAR( Dem_u08_DtElNumPerDIDIndexType, AUTOMATIC ) dataElementClassNum;
    VAR( Dem_u08_DIDClassPerFFIndexType, AUTOMATIC ) didClassRefIndex;

    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) freezeFrameDataOffset;
    VAR( Dem_u16_DataElementClassIndexType, AUTOMATIC ) dataElementClassIndex;
    VAR( Dem_u32_DIDClassIndexType, AUTOMATIC ) didClassIndex;

    P2CONST( AB_83_ConstV Dem_DataElementClassType, AUTOMATIC, DEM_CONFIG_DATA ) dataElementClassPtr;
    P2CONST( AB_83_ConstV Dem_DidClassType, AUTOMATIC, DEM_CONFIG_DATA ) didClassPtr;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) demDataElementSize;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) demDidDataSize;

    retVal = DEM_IRT_NG;

    freezeFrameDataOffset = (Dem_u16_FFDStoredIndexType)0U;

    for( didClassRefIndex = (Dem_u08_DIDClassPerFFIndexType)0U; didClassRefIndex < FreezeFrameClassPtr->DemDidClassNum; didClassRefIndex++ )    /* [GUD:for]didClassRefIndex */
    {
        didClassIndex = FreezeFrameClassPtr->DemDidClassRef[didClassRefIndex];                                  /* [GUD]didClassRefIndex *//* [GUD:CFG:IF_GUARDED: didClassRefIndex ]didClassIndex */
        didClassPtr = &Dem_DIDClassTable[didClassIndex];                                                        /* [GUD]didClassIndex *//* [GUD:CFG:IF_GUARDED: didClassIndex ]didClassPtr */

        ffdOutputAllow = Dem_Data_SetFFDOutputJudge( didClassIndex, FFDataPtr, &freezeFrameDataOffset );
        if( ffdOutputAllow == (boolean)TRUE )
        {
            dataElementClassNum = didClassPtr->DemDataElementClassNum;                                              /* [GUD]didClassPtr */

            for( dataElementClassRefIndex = (Dem_u08_DtElNumPerDIDIndexType)0U; dataElementClassRefIndex < dataElementClassNum; dataElementClassRefIndex++ )    /* [GUD:for]dataElementClassRefIndex */
            {
                dataElementClassIndex = didClassPtr->DemDataElementClassRef[dataElementClassRefIndex];              /* [GUD]didClassPtr *//* [GUD]dataElementClassRefIndex *//* [GUD:CFG:IF_GUARDED: didClassPtr,dataElementClassRefIndex ]dataElementClassIndex */
                dataElementClassPtr = &Dem_DataElementClassTable[dataElementClassIndex];                            /* [GUD]dataElementClassIndex *//* [GUD:CFG:IF_GUARDED: dataElementClassIndex ]dataElementClassPtr */
                demDataElementSize = (Dem_u16_FFDStoredIndexType)dataElementClassPtr->DemDataElementSize;           /* [GUD:CFG]demDataElementSize */

                resultOfCallback = Dem_DataElement_ReadData( dataElementClassPtr, &FFDataPtr[freezeFrameDataOffset], monitorData0 );            /* [GUD]freezeFrameDataOffset */
                if( resultOfCallback != (Std_ReturnType)E_OK )
                {
                    Dem_UtlMem_SetMemory( &FFDataPtr[freezeFrameDataOffset], DEM_DC_FFR_PADDING_DATA, demDataElementSize );                     /* [GUD]freezeFrameDataOffset */
                }
                else
                {
                    retVal = DEM_IRT_OK;
                }

                freezeFrameDataOffset = freezeFrameDataOffset + demDataElementSize;                                 /* [GUD:CFG:demDidDataSize]demDataElementSize */
            }
        }
        else
        {
            demDidDataSize = (Dem_u16_FFDStoredIndexType)didClassPtr->DemDidDataSize;                               /* [GUD]didClassPtr *//* [GUD:CFG:IF_GUARDED: didClassPtr ]demDidDataSize */
            Dem_UtlMem_SetMemory( &FFDataPtr[freezeFrameDataOffset], DEM_DC_FFR_PADDING_DATA, demDidDataSize );                                 /* [GUD]freezeFrameDataOffset */
            freezeFrameDataOffset = freezeFrameDataOffset + demDidDataSize;                                         /* [GUD:CFG:demDidDataSize]freezeFrameDataOffset */
        }
    }

    return retVal;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
