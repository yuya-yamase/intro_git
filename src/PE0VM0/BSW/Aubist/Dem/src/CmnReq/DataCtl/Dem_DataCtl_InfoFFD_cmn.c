/* Dem_DataCtl_InfoFFRecConfig_c(v5-5-0)                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataCtl_InfoFFRecConfig/CODE                          */
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
#include "../../../inc/Dem_CmnLib_DataCtl_FFDOutputJudge.h"
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
/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

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
/* Function Name | Dem_Data_GetFreezeFrameRecordClassByRecordNumber         */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] FreezeFrameRecNumClassPtr :                         */
/*               |                                                          */
/*               | [in] RecordNumber :                                      */
/*               |                                                          */
/*               | [out] FreezeFrameRecordClassPPtr :                       */
/*               |                                                          */
/*               | [out] FreezeFrameRecordClassIndexPtr :                   */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:DEM_IRT_OK] FreezeFrameRecordClassPPtr          */
/* VariableGuard | [GUD:RET:DEM_IRT_OK] FreezeFrameRecordClassIndexPtr      */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetFreezeFrameRecordClassByRecordNumber
(
    P2CONST( AB_83_ConstV Dem_FreezeFrameRecNumClassType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameRecNumClassPtr,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    P2CONST( AB_83_ConstV Dem_FreezeFrameRecordClassType, AUTOMATIC, AUTOMATIC ) *FreezeFrameRecordClassPPtr,
    P2VAR( Dem_u08_FFListIndexType, AUTOMATIC, AUTOMATIC ) FreezeFrameRecordClassIndexPtr,
    P2VAR( Dem_u08_StorageTriggerType, AUTOMATIC, AUTOMATIC ) FreezeFrameRecordTriggerPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) freezeFrameRecordClassRefIndex;
    VAR( Dem_u08_FFRecordClassIndexType, AUTOMATIC ) freezeFrameRecordClassIndex;
    VAR( Dem_u08_FFRecordClassIndexType, AUTOMATIC ) ffrRecordClassConfigureNum;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) ffRecordClassRefMaxNum;

    P2CONST( AB_83_ConstV Dem_FreezeFrameRecordClassType, AUTOMATIC, DEM_CONFIG_DATA ) freezeFrameRecordClassPtr;

    retVal = DEM_IRT_NG;

    ffrRecordClassConfigureNum    = Dem_FFRRecordClassConfigureNum;
    ffRecordClassRefMaxNum = Dem_FFRecordClassRefMaxNum;

    for( freezeFrameRecordClassRefIndex = (Dem_u08_FFListIndexType)0U; freezeFrameRecordClassRefIndex < ffRecordClassRefMaxNum; freezeFrameRecordClassRefIndex++ )  /* [GUD:for]freezeFrameRecordClassRefIndex */
    {
        freezeFrameRecordClassIndex = FreezeFrameRecNumClassPtr->DemFreezeFrameRecordClassRef[freezeFrameRecordClassRefIndex];                                      /* [GUD]freezeFrameRecordClassRefIndex */

        if( freezeFrameRecordClassIndex < ffrRecordClassConfigureNum )                                                                                              /* [GUD:if]freezeFrameRecordClassIndex */
        {
            freezeFrameRecordClassPtr = &Dem_FreezeFrameRecordClassTable[freezeFrameRecordClassIndex];                                                              /* [GUD]freezeFrameRecordClassIndex *//* [GUD:CFG:IF_GUARDED: freezeFrameRecordClassIndex ]freezeFrameRecordClassPtr */

            if( freezeFrameRecordClassPtr->DemFreezeFrameRecordNumber == RecordNumber )                                                                             /* [GUD]freezeFrameRecordClassPtr */
            {
                *FreezeFrameRecordClassPPtr = freezeFrameRecordClassPtr;                                            /* [GUD]freezeFrameRecordClassPtr */

                *FreezeFrameRecordClassIndexPtr = freezeFrameRecordClassRefIndex;                                   /* [GUD]freezeFrameRecordClassRefIndex */
                *FreezeFrameRecordTriggerPtr = freezeFrameRecordClassPtr->DemFreezeFrameRecordTrigger;              /* [GUD]freezeFrameRecordClassPtr */

                retVal = DEM_IRT_OK;
                break;
            }
            else
            {
                /* No Process */
            }
        }
    }
    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Data_EditFreezeFrameRecord                           */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] RecordNumber :                                      */
/*               |                                                          */
/*               | [in] FreezeFrameGetInfoType :                            */
/*               |                                                          */
/*               | [in] CapturedDatarPtr :                                  */
/*               |                                                          */
/*               | [in] FreezeFrameClassPtr :                               */
/*               |                                                          */
/*               | [out] DataPtr :                                          */
/*               |                                                          */
/*               | [in/out] DataSizePtr :                                   */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_WRONG_BUFFERSIZE :                        */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_EditFreezeFrameRecord /* MISRA DEVIATION */
(
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    VAR( Dem_u08_FFDGetInfoType, AUTOMATIC ) FreezeFrameGetInfoType,
    P2CONST( uint8, AUTOMATIC, AUTOMATIC ) CapturedDataPtr,
    P2CONST( AB_83_ConstV Dem_FreezeFrameClassType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameClassPtr,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DataPtr,
    P2VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC, AUTOMATIC ) DataSizePtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_DIDClassPerFFIndexType, AUTOMATIC ) didClassRefIndex;
    VAR( boolean, AUTOMATIC ) ffdOutputAllow;
    VAR( uint8, AUTOMATIC ) numOfStoredDids;

    VAR( Dem_u32_DIDClassIndexType, AUTOMATIC ) didClassIndex;

    VAR( Dem_u32_FFDStoredIndexType, AUTOMATIC ) dataIndex;
    VAR( Dem_u32_FFDStoredIndexType, AUTOMATIC ) dataCalcIndex;
    VAR( Dem_u32_FFDStoredIndexType, AUTOMATIC ) dataCheckSize;
    VAR( Dem_u32_FFDStoredIndexType, AUTOMATIC ) didDataSize;

    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) capturedIndex;
    VAR( Dem_u16_DIDNumberType, AUTOMATIC ) didIdentifier;
    VAR( boolean, AUTOMATIC ) loopEnd;

    retVal = DEM_IRT_OK;

    dataIndex       = (Dem_u32_FFDStoredIndexType)0U;
    dataCheckSize   = (Dem_u32_FFDStoredIndexType)*DataSizePtr;
    capturedIndex   = (Dem_u16_FFDStoredIndexType)0U;

    numOfStoredDids = 0U;

    if ( FreezeFrameGetInfoType == DEM_FFDGETTYPE_DATA )
    {
        DataPtr[dataIndex] = RecordNumber;
    }
    dataIndex = DEM_DC_FFRLEN_RECORDNUM + DEM_DC_FFRLEN_NUMOFDIDS;

    loopEnd =   (boolean)FALSE;
    for( didClassRefIndex = (Dem_u08_DIDClassPerFFIndexType)0U; didClassRefIndex < FreezeFrameClassPtr->DemDidClassNum; didClassRefIndex++ )    /* [GUD:for]didClassRefIndex */
    {
        didClassIndex = FreezeFrameClassPtr->DemDidClassRef[didClassRefIndex];                                                                  /* [GUD]didClassRefIndex *//* [GUD:CFG:IF_GUARDED: didClassRefIndex ]didClassIndex */

        didIdentifier   = Dem_DIDClassTable[didClassIndex].DemDidIdentifier;                                                                    /* [GUD]didClassIndex */
        didDataSize     = (Dem_u32_FFDStoredIndexType)Dem_DIDClassTable[didClassIndex].DemDidDataSize;                                                                      /* [GUD]didClassIndex */

        ffdOutputAllow = Dem_Data_GetFFDOutputAllow( didClassIndex, CapturedDataPtr[capturedIndex], &capturedIndex );                           /* [GUD]capturedIndex */
        if( ffdOutputAllow == (boolean)TRUE )
        {
            if ( FreezeFrameGetInfoType == DEM_FFDGETTYPE_DATA )
            {
                /*------------------------------*/
                /*  get data.                   */
                /*------------------------------*/
                dataCalcIndex   =   ( dataIndex + didDataSize + DEM_DC_FFRLEN_DID );    /* no wrap around */
                if( dataCheckSize >= dataCalcIndex )                                                           /* [GUD:if]didDataSize(capturedIndex,dataIndex) */
                {
                    DataPtr[dataIndex] = (uint8)( didIdentifier >> DEM_DC_DIDIDENTIFIER_SHIFT );                                                /* [GUD]dataIndex */
                    dataIndex = dataIndex + DEM_DC_FFRLEN_DID_MSB;                      /* no wrap around */

                    DataPtr[dataIndex] = (uint8)( didIdentifier & DEM_DC_DIDIDENTIFIER_MASK );                                                  /* [GUD]dataIndex */
                    dataIndex = dataIndex + DEM_DC_FFRLEN_DID_LSB;                      /* no wrap around */

                    Dem_UtlMem_CopyMemory( &DataPtr[dataIndex], &CapturedDataPtr[capturedIndex], (uint16)didDataSize );                         /* [GUD]dataIndex *//* [GUD]capturedIndex */

                    dataIndex = dataIndex + didDataSize;                                /* no wrap around */

                    numOfStoredDids = numOfStoredDids + (uint8)1U;                      /* no wrap around */
                }
                else
                {
                    /*  overflow.       */
                    loopEnd = (boolean)TRUE;
                }
            }
            else
            {
                /*------------------------------*/
                /*  get size.                   */
                /*------------------------------*/
                dataIndex = dataIndex + DEM_DC_FFRLEN_DID_MSB;                          /* no wrap around */
                dataIndex = dataIndex + DEM_DC_FFRLEN_DID_LSB;                          /* no wrap around */

                dataIndex = dataIndex + didDataSize;                                    /* no wrap around */
                if ( dataIndex > DEM_FFDSTOREDINDEX_SIZEMAX )
                {
                    /*  uint16 bitwidth overflow.       */
                    loopEnd = (boolean)TRUE;
                }
            }

            if ( loopEnd == (boolean)TRUE )
            {
                break;
            }
        }

        capturedIndex = capturedIndex + (Dem_u16_FFDStoredIndexType)didDataSize;
    }

    if ( FreezeFrameGetInfoType == DEM_FFDGETTYPE_DATA )
    {
        if( didClassRefIndex < FreezeFrameClassPtr->DemDidClassNum )
        {
            retVal = DEM_IRT_WRONG_BUFFERSIZE;
        }
        else
        {
            *DataSizePtr = (Dem_u16_FFDStoredIndexType)dataIndex;
            DataPtr[DEM_DC_FFRLEN_RECORDNUM] = numOfStoredDids;
        }
    }
    else
    {
        if ( dataIndex <= DEM_FFDSTOREDINDEX_SIZEMAX )
        {
            *DataSizePtr = (Dem_u16_FFDStoredIndexType)dataIndex;
        }
        else
        {
            /*  uint16 bitwidth overflow.       */
            *DataSizePtr = (Dem_u16_FFDStoredIndexType)DEM_FFDSTOREDINDEX_SIZEMAX;
        }
    }

    return retVal;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
