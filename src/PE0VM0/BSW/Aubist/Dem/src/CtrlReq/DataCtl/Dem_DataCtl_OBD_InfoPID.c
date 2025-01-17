/* Dem_DataCtl_OBD_InfoPID_c(v5-5-0)                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataCtl_OBD_InfoPID/CODE                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_Utl.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "Dem_DataCtl_local.h"

#if ( DEM_OBDONEDS_SUPPORT == STD_ON )
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

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetDidClassByPID
(
    VAR( Dem_u08_PIDNumberType, AUTOMATIC ) PID,
    VAR( Dem_u16_FFClassIndexType, AUTOMATIC ) ObdFreezeFrameClassRef,
    P2VAR( Dem_u32_DIDClassIndexType, AUTOMATIC, AUTOMATIC ) DidClassIndexPtr
);
static FUNC( Dem_u08_InternalReturnType, DEM_CODE) Dem_Data_GetObdFFRecordByDidClass
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassIndex,
    VAR( Dem_u32_DIDClassIndexType, AUTOMATIC ) DidClassIndex,
    VAR( Dem_u08_DtElNumPerDIDIndexType, AUTOMATIC ) DataElementIndexOfDID,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC, AUTOMATIC ) BufSizePtr
);


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
/* Function Name | Dem_Data_GetFFRecordByPidData                            */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] PID :                                               */
/*               |        This parameter is an identifier for a PID as      */
/*               |        defined in ISO15031-5.                            */
/*               | [in] EventStrgIndex                                      */
/*               |        The event ID for retrieving.                      */
/*               | [in] RecordNumber                                        */
/*               | [in] DataElementIndexOfPID :                             */
/*               |        Data element index of this PID according to the   */
/*               |        Dcm configuration of service 02. It is zero-bas-  */
/*               |        ed and consecutive, and ordered by the data       */
/*               |        element positions (configured in Dcm, refer to    */
/*               |        SWS_Dem_00597).                                   */
/*               | [out] DestBuffer :                                       */
/*               |        This parameter contains a byte pointer that poin- */
/*               |        ts to the buffer, to which the data element of    */
/*               |        the PID shall be written to. The format is raw    */
/*               |        hexadecimal values and contains no header-inform- */
/*               |        ation.                                            */
/*               | [out] BufSize :                                          */
/*               |        When the function is called this parameter conta- */
/*               |        ins the maximum number of data bytes that can be  */
/*               |        written to the buffer. The function returns the   */
/*               |        actual number of written data bytes in this       */
/*               |        parameter.                                        */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NODATAAVAILABLE :                         */
/*               |        DEM_IRT_WRONG_DIDNUMBER :                         */
/*               |        DEM_IRT_WRONG_BUFFERSIZE :                        */
/*               |        DEM_IRT_WRONG_RECORDNUMBER :                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE) Dem_Data_GetFFRecordByPidData
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    VAR( Dem_u08_PIDNumberType, AUTOMATIC ) PID,
    VAR( Dem_u08_DtElNumPerDIDIndexType, AUTOMATIC ) DataElementIndexOfPID,     /* [PRMCHK:CALLER] */
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC, AUTOMATIC ) BufSizePtr
)
{
    VAR( Dem_u16_FFRecNumClassIndexType, AUTOMATIC ) obdFreezeframeRecNumClassRef;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )  retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )  retGetDidClass;
    VAR( Dem_u16_FFClassIndexType, AUTOMATIC ) obdFreezeFrameClassRef;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC )  freezeFrameRecNumIndex;
    VAR( Dem_u08_FFRecordClassIndexType, AUTOMATIC )  freezeFrameRecordClassIndex;
    VAR( Dem_u08_FFRecordClassIndexType, AUTOMATIC )  ffrRecordClassConfigureNum;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC )  obdFFRClassPerDTCMaxNum;
    VAR( Dem_u32_DIDClassIndexType, AUTOMATIC ) didClassIndex;

    P2CONST( AB_83_ConstV Dem_FreezeFrameRecNumClassType, AUTOMATIC, DEM_CONFIG_DATA ) freezeFrameRecNumClassPtr;
    P2CONST( AB_83_ConstV Dem_FreezeFrameRecordClassType, AUTOMATIC, DEM_CONFIG_DATA ) freezeFrameRecordClassPtr;

    retVal = DEM_IRT_WRONG_RECORDNUMBER;

    /* Checks the reference of freeze frame record number class. */
    Dem_CfgInfoPm_GetOBDFreezeFrameAndRecNumClass( EventStrgIndex, &obdFreezeFrameClassRef, &obdFreezeframeRecNumClassRef );        /* [GUD:OUT:Not DEM_FFCLASSINDEX_INVALID] obdFreezeFrameClassRef *//* [GUD:OUT:Not DEM_FFRECNUMCLASSINDEX_INVALID] obdFreezeframeRecNumClassRef */
    Dem_CfgInfoPm_GetNumOfOBDFreezeFrameRecordClass( &ffrRecordClassConfigureNum, &obdFFRClassPerDTCMaxNum );

    if( obdFreezeframeRecNumClassRef != DEM_FFRECNUMCLASSINDEX_INVALID )                                                                            /* [GUD:if] obdFreezeframeRecNumClassRef */
    {
        freezeFrameRecNumClassPtr = &Dem_FreezeFrameRecNumClassTable[ obdFreezeframeRecNumClassRef ];                                               /* [GUD] obdFreezeframeRecNumClassRef */

        for( freezeFrameRecNumIndex = (Dem_u08_FFListIndexType)0U; freezeFrameRecNumIndex < obdFFRClassPerDTCMaxNum; freezeFrameRecNumIndex++ )     /* [GUD:for] freezeFrameRecNumIndex */
        {
            freezeFrameRecordClassIndex = freezeFrameRecNumClassPtr->DemFreezeFrameRecordClassRef[freezeFrameRecNumIndex];                          /* [GUD] freezeFrameRecNumIndex */
            if( freezeFrameRecordClassIndex < ffrRecordClassConfigureNum )                                                                          /* [GUD:if] freezeFrameRecordClassIndex */
            {
                freezeFrameRecordClassPtr = &Dem_FreezeFrameRecordClassTable[freezeFrameRecordClassIndex];                                          /* [GUD] freezeFrameRecordClassIndex *//* [GUD:CFG:IF_GUARDED: freezeFrameRecordClassIndex ]freezeFrameRecordClassPtr */
                if( freezeFrameRecordClassPtr->DemFreezeFrameRecordNumber == RecordNumber )                                                         /* [GUD] freezeFrameRecordClassPtr */
                {
                    retGetDidClass = Dem_Data_GetDidClassByPID(PID, obdFreezeFrameClassRef, &didClassIndex );                                       /* [GUD:RET:DEM_IRT_OK]didClassIndex */
                    if( retGetDidClass == DEM_IRT_OK )
                    {
                        retVal = Dem_Data_GetObdFFRecordByDidClass( EventStrgIndex, freezeFrameRecNumIndex, didClassIndex, DataElementIndexOfPID, DestBufferPtr, BufSizePtr);   /* [GUD]didClassIndex *//* [GUDCHK:CALLER]DataElementIndexOfPID */
                    }
                    else
                    {
                        retVal = DEM_IRT_WRONG_DIDNUMBER;
                    }
                    break;
                }
            }
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Data_GetDidClassByPID                                */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] PID :                                               */
/*               |        This parameter is an identifier for a PID as      */
/*               |        defined in ISO15031-5.                            */
/*               | [in] ObdFreezeFrameClassRef :                            */
/*               |        The reference for OBD to DemFreezeFrameClass.     */
/*               | [out] DidClassPtr :                                      */
/*               |        Stores the DIDClass of the specified PID.         */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |           Successful acquisition of PidClass.            */
/*               |        DEM_IRT_NG :                                      */
/*               |           Failed to acquire PidClass.                    */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:DEM_IRT_OK] DidClassIndexPtr                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetDidClassByPID
(
    VAR( Dem_u08_PIDNumberType, AUTOMATIC ) PID,
    VAR( Dem_u16_FFClassIndexType, AUTOMATIC ) ObdFreezeFrameClassRef,
    P2VAR( Dem_u32_DIDClassIndexType, AUTOMATIC, AUTOMATIC ) DidClassIndexPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_DIDClassPerFFIndexType, AUTOMATIC ) didClassNum;
    VAR( Dem_u08_DIDClassPerFFIndexType, AUTOMATIC ) didClassRefIndex;
    VAR( Dem_u32_DIDClassIndexType, AUTOMATIC ) didClassIndex;

    P2CONST( AB_83_ConstV Dem_FreezeFrameClassType, AUTOMATIC, DEM_CONFIG_DATA ) obdFreezeFrameClassTablePtr;

    retVal = DEM_IRT_NG;

    if( ObdFreezeFrameClassRef != DEM_FFCLASSINDEX_INVALID )                                    /* [GUD:if]ObdFreezeFrameClassRef */
    {
        obdFreezeFrameClassTablePtr = &Dem_FreezeFrameClassTable[ObdFreezeFrameClassRef];       /* [GUD]ObdFreezeFrameClassRef *//* [GUD:CFG:IF_GUARDED: ObdFreezeFrameClassRef ]obdFreezeFrameClassTablePtr */
        didClassNum = obdFreezeFrameClassTablePtr->DemDidClassNum;                              /* [GUD]obdFreezeFrameClassTablePtr */

        for( didClassRefIndex = (Dem_u08_DIDClassPerFFIndexType)0U; didClassRefIndex < didClassNum; didClassRefIndex++ )    /* [GUD:for]didClassRefIndex */
        {
            didClassIndex = obdFreezeFrameClassTablePtr->DemDidClassRef[didClassRefIndex];      /* [GUD]obdFreezeFrameClassTablePtr *//* [GUD]didClassRefIndex *//* [GUD:CFG:IF_GUARDED: didClassRefIndex ]didClassIndex */

            if( Dem_DIDClassTable[didClassIndex].DemPidIdentifier == PID )                      /* [GUD]didClassIndex */
            {
                *DidClassIndexPtr   =   didClassIndex;

                retVal = DEM_IRT_OK;
                break;
            }
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Data_GetObdFFRecordByDidClass                        */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |                                                          */
/*               | [in] FreezeFrameRecordClassIndex :                       */
/*               |                                                          */
/*               | [in] DidDataElementListRef :                             */
/*               |                                                          */
/*               | [in] DataElementIndexOfDID :                             */
/*               |                                                          */
/*               | [out] DestBufferPtr :                                    */
/*               |                                                          */
/*               | [out] BufSizePtr :                                       */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NODATAAVAILABLE :                         */
/*               |        DEM_IRT_WRONG_BUFFERSIZE :                        */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE) Dem_Data_GetObdFFRecordByDidClass
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassIndex,
    VAR( Dem_u32_DIDClassIndexType, AUTOMATIC ) DidClassIndex,                  /* [PRMCHK:CALLER] */
    VAR( Dem_u08_DtElNumPerDIDIndexType, AUTOMATIC ) DataElementIndexOfDID,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC, AUTOMATIC ) BufSizePtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetRecordNumberIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFFRec;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) dataElementSize;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u16_DataElementClassIndexType, AUTOMATIC ) dataElementIndex;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) pidDataOffset;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) obdRecordNumberIndex;
    VAR( Dem_FreezeFrameRecordMngType, AUTOMATIC ) obdFreezeFrameRecord;
    VAR( Dem_u08_DtElNumPerDIDIndexType, AUTOMATIC ) dataElementClassNum;

    retVal = DEM_IRT_OK;
    resultOfGetFFRec = DEM_IRT_NG;

    dataElementClassNum     =   Dem_DIDClassTable[DidClassIndex].DemDataElementClassNum;                                        /* [GUDCHK:CALLER]DidClassIndex */

    if ( DataElementIndexOfDID < dataElementClassNum )                                                                          /* [GUD:if]DataElementIndexOfDID */
    {
        dataElementIndex    =   Dem_DIDClassTable[DidClassIndex].DemDataElementClassRef[DataElementIndexOfDID];                 /* [GUDCHK:CALLER]DidClassIndex *//* [GUD]DataElementIndexOfDID *//* [GUD:CFG:IF_GUARDED: DidClassIndex,DataElementIndexOfDID ]dataElementIndex */
        dataElementSize     =   (Dem_u16_FFDStoredIndexType)Dem_DataElementClassTable[dataElementIndex].DemDataElementSize;     /* [GUD:CFG:IF_GUARDED: dataElementIndex ]dataElementSize */
        if( dataElementSize <= *BufSizePtr )                                                                                    /* [GUD:if]dataElementSize */
        {
            SchM_Enter_Dem_EventMemory();

            faultIndex = DEM_FAULTINDEX_INITIAL;
            (void)Dem_DataMngC_GetER_FaultIndex( EventStrgIndex, &faultIndex );/* no return check required */                   /* [GUD:RET:DEM_IRT_OK] EventStrgIndex */
            resultOfGetRecordNumberIndex = Dem_DataMngC_GetFR_ObdFreezeFrameIndex( faultIndex, FreezeFrameRecordClassIndex, &obdRecordNumberIndex );

            if( resultOfGetRecordNumberIndex == DEM_IRT_OK )
            {
                resultOfGetFFRec = Dem_DataMngC_GetObdFreezeFrameRecord( obdRecordNumberIndex, &obdFreezeFrameRecord );
            }

            SchM_Exit_Dem_EventMemory();

            if( resultOfGetFFRec == DEM_IRT_OK )
            {
                pidDataOffset = Dem_DIDClassTable[DidClassIndex].DemPidPos;                                                     /* [GUDCHK:CALLER]DidClassIndex *//* [GUD:CFG:IF_GUARDED: DidClassIndex ]pidDataOffset */
                Dem_UtlMem_CopyMemory( DestBufferPtr, &obdFreezeFrameRecord.DataPtr[pidDataOffset], dataElementSize );          /* [GUDCHK:CALLER]DidClassIndex */
                *BufSizePtr = dataElementSize;
            }
            else
            {
                retVal = DEM_IRT_NODATAAVAILABLE;
            }
        }
        else
        {
            retVal = DEM_IRT_WRONG_BUFFERSIZE;
        }
    }

    return retVal;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_OBDONEDS_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-0-0         :2019-05-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
