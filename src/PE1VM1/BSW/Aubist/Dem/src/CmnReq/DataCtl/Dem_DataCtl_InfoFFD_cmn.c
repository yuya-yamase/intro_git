/* Dem_DataCtl_InfoFFRecConfig_c(v5-10-0)                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
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
/* Parameters    | [in] Caller :                                            */
/*               |                                                          */
/*               | [in] FreezeFrameRecNumClassPtr :                         */
/*               |                                                          */
/*               | [in] RecordNumber :                                      */
/*               |                                                          */
/*               | [out] FreezeFrameRecordClassIndexPtr :                   */
/*               |                                                          */
/*               | [out] FreezeFrameRecordTriggerPtr :                      */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:DEM_IRT_OK] FreezeFrameRecordClassIndexPtr      */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-7-0      | no object changed.                                       */
/*   v5-8-0      | no branch changed.                                       */
/*   v5-9-0      | branch changed.                                          */
/*   v5-10-0     | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetFreezeFrameRecordClassByRecordNumber
(
    VAR( Dem_u08_RequestCallerType, AUTOMATIC ) Caller,
    P2CONST( AB_83_ConstV Dem_FreezeFrameRecNumClassType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameRecNumClassPtr,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( Dem_u08_FFListIndexType, AUTOMATIC, AUTOMATIC ) FreezeFrameRecordClassIndexPtr,
    P2VAR( Dem_u08_StorageTriggerType, AUTOMATIC, AUTOMATIC ) FreezeFrameRecordTriggerPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) freezeFrameRecordClassRefIndex;
    VAR( Dem_u08_FFRecordClassIndexType, AUTOMATIC ) freezeFrameRecordClassIndex;
    VAR( Dem_u08_FFRecordClassIndexType, AUTOMATIC ) ffrRecordClassConfigureNum;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) ffRecordClassRefMaxNum;
    VAR( boolean, AUTOMATIC ) checkOutputConfig;
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC )        freezeFrameRecordNumber;
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC )        freezeFrameRecordTrigger;
    VAR( boolean, AUTOMATIC )                           freezeFrameRecordToDcm;

    retVal = DEM_IRT_NG;

    ffrRecordClassConfigureNum    = Dem_FFRRecordClassConfigureNum;
    ffRecordClassRefMaxNum = Dem_FFRecordClassRefMaxNum;

    for( freezeFrameRecordClassRefIndex = (Dem_u08_FFListIndexType)0U; freezeFrameRecordClassRefIndex < ffRecordClassRefMaxNum; freezeFrameRecordClassRefIndex++ )  /* [GUD:for]freezeFrameRecordClassRefIndex */
    {
        freezeFrameRecordClassIndex = FreezeFrameRecNumClassPtr->DemFreezeFrameRecordClassRef[freezeFrameRecordClassRefIndex];                                      /* [GUD]freezeFrameRecordClassRefIndex *//* [ARYCHK] DEM_FF_RECORD_CLASS_REF_MAX_NUM / 1 / freezeFrameRecordClassRefIndex */

        if( freezeFrameRecordClassIndex < ffrRecordClassConfigureNum )                                                                                              /* [GUD:if]freezeFrameRecordClassIndex */
        {
            Dem_CfgInfoPm_GetFreezeFrameRecordInfo_forOutput( freezeFrameRecordClassIndex, &freezeFrameRecordNumber, &freezeFrameRecordTrigger, &freezeFrameRecordToDcm );  /* [GUD] freezeFrameRecordClassIndex */

            if( freezeFrameRecordNumber == RecordNumber )
            {
                /*------------------------------------------*/
                /*  Check whether the data can be output.   */
                /*------------------------------------------*/
                checkOutputConfig   =   (boolean)TRUE;
                if ( Caller == DEM_CALLER_DCM )
                {
                    if ( freezeFrameRecordToDcm == (boolean)FALSE )
                    {
                        /*  like to no configured data.     */
                        checkOutputConfig   =   (boolean)FALSE;
                    }
                }

                if ( checkOutputConfig == (boolean)TRUE )
                {
                    *FreezeFrameRecordClassIndexPtr = freezeFrameRecordClassRefIndex;                                   /* [GUD]freezeFrameRecordClassRefIndex */
                    *FreezeFrameRecordTriggerPtr = freezeFrameRecordTrigger;

                    retVal = DEM_IRT_OK;
                    break;
                }
                else
                {
                    /* No Process */
                }
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
/*   v5-6-0      | branch changed.                                          */
/*   v5-7-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_EditFreezeFrameRecord /* MISRA DEVIATION */
(
#ifndef DEM_SIT_RANGE_CHECK
#else   /* DEM_SIT_RANGE_CHECK */
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) CapturedDataSize,
#endif  /* DEM_SIT_RANGE_CHECK */
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    VAR( Dem_u08_FFDGetInfoType, AUTOMATIC ) FreezeFrameGetInfoType,
    P2CONST( uint8, AUTOMATIC, AUTOMATIC ) CapturedDataPtr,
    P2CONST( AB_83_ConstV Dem_FreezeFrameClassType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameClassPtr,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DataPtr,
    P2VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC, AUTOMATIC ) DataSizePtr
)
{
    VAR( Dem_u16_DIDClassPerFFIndexType, AUTOMATIC ) didClassRefIndex;
    VAR( Dem_u16_DIDClassPerFFIndexType, AUTOMATIC ) numOfStoredDids;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) ffdOutputAllow;

    VAR( Dem_u32_DIDClassIndexType, AUTOMATIC ) didClassIndex;

    VAR( Dem_u32_FFDStoredIndexType, AUTOMATIC ) dataIndex;
    VAR( Dem_u32_FFDStoredIndexType, AUTOMATIC ) dataCalcIndex;
    VAR( Dem_u32_FFDStoredIndexType, AUTOMATIC ) dataCheckSize;
    VAR( Dem_u32_FFDStoredIndexType, AUTOMATIC ) didDataSize;

    VAR( Dem_u32_FFDStoredIndexType, AUTOMATIC ) capturedIndex;
    VAR( Dem_u16_DIDNumberType, AUTOMATIC ) didIdentifier;
    VAR( boolean, AUTOMATIC ) loopEnd;

    retVal = DEM_IRT_OK;

    dataIndex       = (Dem_u32_FFDStoredIndexType)0U;
    dataCheckSize   = (Dem_u32_FFDStoredIndexType)*DataSizePtr;
    capturedIndex   = (Dem_u32_FFDStoredIndexType)0U;

    numOfStoredDids = (Dem_u16_DIDClassPerFFIndexType)0U;

    if ( FreezeFrameGetInfoType == DEM_FFDGETTYPE_DATA )
    {
        DataPtr[dataIndex] = RecordNumber;/* [ARYCHK] *DataSizePtr / 1 / dataIndex */
    }
    dataIndex = DEM_DC_FFRLEN_RECORDNUM + DEM_DC_FFRLEN_NUMOFDIDS;

    loopEnd =   (boolean)FALSE;
    for( didClassRefIndex = (Dem_u16_DIDClassPerFFIndexType)0U; didClassRefIndex < FreezeFrameClassPtr->DemDidClassNum; didClassRefIndex++ )    /* [GUD:for]didClassRefIndex */
    {
        didClassIndex = FreezeFrameClassPtr->DemDidClassRef[didClassRefIndex];                                                                  /* [GUD]didClassRefIndex *//* [GUD:CFG:IF_GUARDED: didClassRefIndex ]didClassIndex *//* [ARYCHK] DEM_DID_NUM_PER_FRAME_MAX_NUM / 1 / didClassRefIndex */

        didIdentifier   = Dem_DIDClassTable[didClassIndex].DemDidIdentifier;                                                                    /* [GUD]didClassIndex */
        didDataSize     = (Dem_u32_FFDStoredIndexType)Dem_DIDClassTable[didClassIndex].DemDidDataSize;                                                                      /* [GUD]didClassIndex */

        ffdOutputAllow = Dem_Data_GetFFDOutputAllow( didClassIndex, CapturedDataPtr[capturedIndex], &capturedIndex );                           /* [GUD]capturedIndex *//* [ARYCHK] CapturedDataSize / 1 / capturedIndex */
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
                    DataPtr[dataIndex] = (uint8)( didIdentifier >> DEM_DC_DIDIDENTIFIER_SHIFT );                                                /* [GUD]dataIndex *//* [ARYCHK] *DataSizePtr / 1 / dataIndex */
                    dataIndex = dataIndex + DEM_DC_FFRLEN_DID_MSB;                      /* no wrap around */

                    DataPtr[dataIndex] = (uint8)( didIdentifier & DEM_DC_DIDIDENTIFIER_MASK );                                                  /* [GUD]dataIndex *//* [ARYCHK] *DataSizePtr / 1 / dataIndex */
                    dataIndex = dataIndex + DEM_DC_FFRLEN_DID_LSB;                      /* no wrap around */

                    Dem_UtlMem_CopyMemory( &DataPtr[dataIndex], &CapturedDataPtr[capturedIndex], (uint16)didDataSize );                         /* [GUD]dataIndex *//* [GUD]capturedIndex *//* [ARYCHK] *DataSizePtr / 1 / dataIndex *//* [ARYCHK] CapturedDataSize / 1 / capturedIndex */

                    dataIndex = dataIndex + didDataSize;                                /* no wrap around */

                    numOfStoredDids = numOfStoredDids + (Dem_u16_DIDClassPerFFIndexType)1U;                      /* no wrap around */
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
        }
        if ( loopEnd == (boolean)TRUE )
        {
            break;
        }

        capturedIndex = capturedIndex + (Dem_u32_FFDStoredIndexType)didDataSize;        /* no wrap around */

    }

    if ( FreezeFrameGetInfoType == DEM_FFDGETTYPE_DATA )
    {
        if( didClassRefIndex < FreezeFrameClassPtr->DemDidClassNum )
        {
            retVal = DEM_IRT_WRONG_BUFFERSIZE;
        }
        else
        {
            if ( numOfStoredDids <= DEM_OUTPUT_DIDNUMVAL_MAX )
            {
                DataPtr[DEM_DC_FFRLEN_RECORDNUM] = (uint8)numOfStoredDids; /* [ARYCHK] *DataSizePtr/ 1 /DEM_DC_FFRLEN_RECORDNUM */
            }
            else
            {
                DataPtr[DEM_DC_FFRLEN_RECORDNUM] = DEM_OUTPUT_DIDNUMVAL_OVRFLW; /* [ARYCHK] *DataSizePtr/ 1 /DEM_DC_FFRLEN_RECORDNUM */
            }
            *DataSizePtr = (Dem_u16_FFDStoredIndexType)dataIndex;
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
/*  v5-6-0         :2024-01-29                                              */
/*  v5-7-0         :2024-05-29                                              */
/*  v5-8-0         :2024-10-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
