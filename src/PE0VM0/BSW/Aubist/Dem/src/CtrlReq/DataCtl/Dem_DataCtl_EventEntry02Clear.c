/* Dem_DataCtl_EventEntry02Clear_c(v5-5-0)                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataCtl_EventEntry02Clear/CODE                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_Pm_DTC.h"
#include "../../../inc/Dem_Pm_Misfire.h"
#include "../../../inc/Dem_Pm_Similar.h"
#include "Dem_DataCtl_local.h"
#include "Dem_DataCtl_EventEntry_local.h"
#include "Dem_DataCtl_TSFFD_local.h"

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

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_Data_ClearTargetObdFFRecord
(
    P2CONST( Dem_FFListRecordForClrType, AUTOMATIC, AUTOMATIC ) ClearFFListRecordPtr,
    P2CONST( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr,
    P2VAR( Dem_EventMemoryRecordType, AUTOMATIC, AUTOMATIC ) EventMemoryRecordPtr
);
#endif  /*   ( DEM_OBDFFD_SUPPORT == STD_ON )      */

static FUNC( void, DEM_CODE ) Dem_Data_ClearTargetFFRecord
(
    P2CONST( Dem_FFListRecordForClrType, AUTOMATIC, AUTOMATIC ) ClearFFListRecordPtr,
    P2CONST( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr,
    P2VAR( Dem_EventMemoryRecordType, AUTOMATIC, AUTOMATIC ) EventMemoryRecordPtr
);
#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_Data_ClearTargetTSFFListRecord
(
    P2CONST( Dem_FFListRecordForClrType, AUTOMATIC, AUTOMATIC ) ClearFFListRecordPtr,
    P2CONST( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr
);
#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON )   */

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
static FUNC( Dem_u08_FFDIndexType, DEM_CODE ) Dem_Data_ClearTargetObdRecordNumberIndexArray
(
    P2CONST( Dem_FFListRecordForClrType, AUTOMATIC, AUTOMATIC ) ClearFFListRecordPtr,
    P2VAR( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr
);
#endif  /*   ( DEM_OBDFFD_SUPPORT == STD_ON )      */

static FUNC( Dem_u08_FFDIndexType, DEM_CODE ) Dem_Data_ClearTargetRecordNumberIndexArray
(
    P2CONST( Dem_FFListRecordForClrType, AUTOMATIC, AUTOMATIC ) ClearFFListRecordPtr,
    P2VAR( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr
);

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_Data_ClearTargetTSFFListIndexArray
(
    P2CONST( Dem_FFListRecordForClrType, AUTOMATIC, AUTOMATIC ) ClearFFListRecordPtr,
    P2VAR( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr
);
#endif  /*   ( DEM_TSFF_PM_SUPPORT == STD_ON ) */

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
/* Function Name | Dem_Data_ClearEventRecord                                */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_ClearEventRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_EventRecordForCtlType, AUTOMATIC ) eventRecord;

    Dem_DataMngC_InitEventCtlRecordData( &eventRecord );

    (void)Dem_DataMngC_SetEventRecord( EventStrgIndex, &eventRecord );  /* no return check required */

    return ;
}


/****************************************************************************/
/* Function Name | Dem_Data_ClearFaultRecord                                */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] FaultIndex :                                        */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | none.                                                    */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_ClearFaultRecord
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfSetFaultRec;

    retVal = DEM_IRT_NG;

    if( FaultIndex != DEM_FAULTINDEX_INITIAL )
    {
        resultOfSetFaultRec = Dem_DataMngC_ClearFaultRecord( FaultIndex );
        if( resultOfSetFaultRec == DEM_IRT_OK )
        {
            retVal = DEM_IRT_OK;
        }
        else
        {
            /* No Process */
        }
    }
    else
    {
        /* No Process */
    }

    return retVal;
}


#if ( DEM_OBDFFD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_ClearObdFreezeFrameRecord                       */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] FaultRecordPtr :                                    */
/*               |                                                          */
/*               | [in/out] EventMemoryRecordPtr :                          */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_ClearObdFreezeFrameRecord
(
    P2CONST( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr,
    P2VAR( Dem_EventMemoryRecordType, AUTOMATIC, AUTOMATIC ) EventMemoryRecordPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfSetFFRec;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) freezeFrameRecordIndex;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) obdFFRClassPerDTCMaxNum;

    /* Initializes the return value to OK. */
    obdFFRClassPerDTCMaxNum = Dem_OBDFFRClassPerDTCMaxNum;

    for( freezeFrameRecordIndex = (Dem_u08_FFListIndexType)0U; freezeFrameRecordIndex < obdFFRClassPerDTCMaxNum; freezeFrameRecordIndex++ )     /* [GUD:for]freezeFrameRecordIndex */
    {
        /* Checks the record number index corresponding to the loop counter of retrieved the freeze frame list.  */
        if( FaultRecordPtr->ObdRecordNumberIndex[freezeFrameRecordIndex] != DEM_FFRECINDEX_INITIAL )                                            /* [GUD]freezeFrameRecordIndex */
        {
            /* The record number index corresponding to the loop counter is valid. */

            /* Initialize the freeze frame record corresponding to the record number index. */
            resultOfSetFFRec = Dem_DataMngC_ClearObdFreezeFrameRecord( FaultRecordPtr->ObdRecordNumberIndex[freezeFrameRecordIndex] );          /* [GUD]freezeFrameRecordIndex */

            /* Checks the result of set to Dem_DataMng. */
            if( resultOfSetFFRec == DEM_IRT_OK )
            {
                /* The result means succeeded. */

                /* Decrements the number of freeze frame record. */
                if( EventMemoryRecordPtr->NumberOfObdFreezeFrameRecords > (uint16)0U )
                {
                    /* Decrement the number of freeze frame records. */
                    EventMemoryRecordPtr->NumberOfObdFreezeFrameRecords--;
                }
            }
        }
    }

    return ;
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */

/****************************************************************************/
/* Function Name | Dem_Data_ClearFreezeFrameRecord                          */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] FaultRecordPtr :                                    */
/*               |                                                          */
/*               | [in/out] EventMemoryRecordPtr :                          */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_ClearFreezeFrameRecord
(
    P2CONST( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr,
    P2VAR( Dem_EventMemoryRecordType, AUTOMATIC, AUTOMATIC ) EventMemoryRecordPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfSetFFRec;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) freezeFrameRecordIndex;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) nonOBDFFRClassPerDTCMaxNum;

    /* Initializes the return value to OK. */
    nonOBDFFRClassPerDTCMaxNum = Dem_NonOBDFFRClassPerDTCMaxNum;

    for( freezeFrameRecordIndex = (Dem_u08_FFListIndexType)0U; freezeFrameRecordIndex < nonOBDFFRClassPerDTCMaxNum; freezeFrameRecordIndex++ )      /* [GUD:for]freezeFrameRecordIndex */
    {
        /* Checks the record number index corresponding to the loop counter of retrieved the freeze frame list.  */
        if( FaultRecordPtr->RecordNumberIndex[freezeFrameRecordIndex] != DEM_FFRECINDEX_INITIAL )                                                   /* [GUD]freezeFrameRecordIndex */
        {
            /* The record number index corresponding to the loop counter is valid. */

            /* Initialize the freeze frame record corresponding to the record number index. */
            resultOfSetFFRec = Dem_DataMngC_ClearFreezeFrameRecord( FaultRecordPtr->RecordNumberIndex[freezeFrameRecordIndex] );                    /* [GUD]freezeFrameRecordIndex */

            /* Checks the result of set to Dem_DataMng. */
            if( resultOfSetFFRec == DEM_IRT_OK )
            {
                /* The result means succeeded. */

                /* Decrements the number of freeze frame record. */
                if( EventMemoryRecordPtr->NumberOfFreezeFrameRecords > (uint16)0U )
                {
                    /* Decrement the number of freeze frame records. */
                    EventMemoryRecordPtr->NumberOfFreezeFrameRecords--;
                }
            }
        }
    }

    return ;
}

/****************************************************************************/
/* Function Name | Dem_Data_ClearTargetFFListRecord                         */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] ClearFFListRecordPtr :                              */
/*               | [out] FaultRecordPtr                                     */
/* Return Value  | Dem_u08_FFDIndexType     :   remain triggerFFD count.    */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_FFDIndexType, DEM_CODE ) Dem_Data_ClearTargetFFListRecord
(
    P2CONST( Dem_FFListRecordForClrType, AUTOMATIC, AUTOMATIC ) ClearFFListRecordPtr,
    P2VAR( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr
)
{
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) remainFFDCnt;
#if ( DEM_OBDFFD_SUPPORT == STD_ON )   /*  [FuncSw]    */
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) remainOBDFFDCnt;
#endif  /*   ( DEM_OBDFFD_SUPPORT == STD_ON )          */

    remainFFDCnt    =   Dem_Data_ClearTargetRecordNumberIndexArray( ClearFFListRecordPtr, FaultRecordPtr );

#if ( DEM_OBDFFD_SUPPORT == STD_ON )   /*  [FuncSw]    */
    remainOBDFFDCnt =   Dem_Data_ClearTargetObdRecordNumberIndexArray( ClearFFListRecordPtr, FaultRecordPtr );
    remainFFDCnt    =   remainFFDCnt + remainOBDFFDCnt;

#endif  /*   ( DEM_OBDFFD_SUPPORT == STD_ON )          */

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )  /*  [FuncSw]    */
    Dem_Data_ClearTargetTSFFListIndexArray( ClearFFListRecordPtr, FaultRecordPtr );
#endif  /*   ( DEM_TSFF_PM_SUPPORT == STD_ON )         */

    return remainFFDCnt;
}


/****************************************************************************/
/* Function Name | Dem_Data_ClearTargetFFRecordInFaultRecord                */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] ClearFFListRecordPtr :                              */
/*               | [out] FaultRecordPtr                                     */
/*               | [in/out] EventMemoryRecordPtr                            */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_ClearTargetFFRecordInFaultRecord
(
    P2CONST( Dem_FFListRecordForClrType, AUTOMATIC, AUTOMATIC ) ClearFFListRecordPtr,
    P2CONST( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr,
    P2VAR( Dem_EventMemoryRecordType, AUTOMATIC, AUTOMATIC ) EventMemoryRecordPtr
)
{
#if ( DEM_TSFF_PM_SUPPORT == STD_ON )    /* [FuncSw] */
    Dem_Data_ClearTargetTSFFListRecord( ClearFFListRecordPtr, FaultRecordPtr );
#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON )   */

    Dem_Data_ClearTargetFFRecord( ClearFFListRecordPtr, FaultRecordPtr, EventMemoryRecordPtr );

#if ( DEM_OBDFFD_SUPPORT == STD_ON )   /*  [FuncSw]    */
    Dem_Data_ClearTargetObdFFRecord( ClearFFListRecordPtr, FaultRecordPtr, EventMemoryRecordPtr );
#endif  /*   ( DEM_OBDFFD_SUPPORT == STD_ON )          */

    return ;
}

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_ClearTargetObdFFRecord                          */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] ClearFFListRecordPtr :                              */
/*               | [out] FaultRecordPtr                                     */
/*               | [in/out] EventMemoryRecordPtr                            */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_ClearTargetObdFFRecord
(
    P2CONST( Dem_FFListRecordForClrType, AUTOMATIC, AUTOMATIC ) ClearFFListRecordPtr,
    P2CONST( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr,
    P2VAR( Dem_EventMemoryRecordType, AUTOMATIC, AUTOMATIC ) EventMemoryRecordPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfSetFFRec;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) freezeFrameRecordIndex;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) obdFFRClassPerDTCMaxNum;

    obdFFRClassPerDTCMaxNum = Dem_OBDFFRClassPerDTCMaxNum;

    /* Initializes the return value to OK. */

    for( freezeFrameRecordIndex = (Dem_u08_FFListIndexType)0U; freezeFrameRecordIndex < obdFFRClassPerDTCMaxNum; freezeFrameRecordIndex++ )     /* [GUD:for]freezeFrameRecordIndex */
    {
        /* Checks the record number index corresponding to the loop counter of retrieved the freeze frame list.  */
        if( FaultRecordPtr->ObdRecordNumberIndex[freezeFrameRecordIndex] != DEM_FFRECINDEX_INITIAL  )                                           /* [GUD]freezeFrameRecordIndex */
        {
            if( ClearFFListRecordPtr->ObdFFRClrFlg[freezeFrameRecordIndex] == (boolean)TRUE )                                                   /* [GUD]freezeFrameRecordIndex */
            {
                /* The record number index corresponding to the loop counter is valid. */

                /* Initializes the freeze frame record corresponding to the record number index. */
                resultOfSetFFRec = Dem_DataMngC_ClearObdFreezeFrameRecord( FaultRecordPtr->ObdRecordNumberIndex[freezeFrameRecordIndex] );      /* [GUD]freezeFrameRecordIndex */

                /* Checks the result of set to Dem_DataMng. */
                if( resultOfSetFFRec == DEM_IRT_OK )
                {
                    /* The result means succeeded. */

                    Dem_Data_SetResultOfCmpObdFFRecordToTmp( freezeFrameRecordIndex, DEM_IRT_NG );                                              /* [GUD]freezeFrameRecordIndex */

                    /* Decrements the number of freeze frame record. */
                    if( EventMemoryRecordPtr->NumberOfObdFreezeFrameRecords > (uint16)0U )
                    {
                        /* The number of freeze frame records is over 0. */

                        /* Decrement the number of freeze frame records. */
                        EventMemoryRecordPtr->NumberOfObdFreezeFrameRecords--;
                    }
                    else
                    {
                        /* The number of freeze frame records is 0 or less. */

                        /* no processing. */
                    }
                }
                else
                {
                    /* The result had not been succeeded. */
                }
            }
        }
        else
        {
            /* The record number index corresponding to the loop counter is invalid. */
            /* no processing, because the fault without freeze frame. */
        }
    }

    return ;
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */

/****************************************************************************/
/* Function Name | Dem_Data_ClearTargetFFRecord                             */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] ClearFFListRecordPtr :                              */
/*               | [out] FaultRecordPtr                                     */
/*               | [in/out] EventMemoryRecordPtr                            */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_ClearTargetFFRecord
(
    P2CONST( Dem_FFListRecordForClrType, AUTOMATIC, AUTOMATIC ) ClearFFListRecordPtr,
    P2CONST( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr,
    P2VAR( Dem_EventMemoryRecordType, AUTOMATIC, AUTOMATIC ) EventMemoryRecordPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfSetFFRec;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) freezeFrameRecordIndex;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) nonOBDFFRClassPerDTCMaxNum;

    nonOBDFFRClassPerDTCMaxNum = Dem_NonOBDFFRClassPerDTCMaxNum;

    /* Initializes the return value to OK. */
    for( freezeFrameRecordIndex = (Dem_u08_FFListIndexType)0U; freezeFrameRecordIndex < nonOBDFFRClassPerDTCMaxNum; freezeFrameRecordIndex++ )      /* [GUD:for]freezeFrameRecordIndex */
    {
        /* Checks the record number index corresponding to the loop counter of retrieved the freeze frame list.  */
        if( FaultRecordPtr->RecordNumberIndex[freezeFrameRecordIndex] != DEM_FFRECINDEX_INITIAL  )                                                  /* [GUD]freezeFrameRecordIndex */
        {
            if( ClearFFListRecordPtr->FFRClrFlg[freezeFrameRecordIndex] == (boolean)TRUE )                                                          /* [GUD]freezeFrameRecordIndex */
            {
                /* The record number index corresponding to the loop counter is valid. */

                /* Initializes the freeze frame record corresponding to the record number index. */
                resultOfSetFFRec = Dem_DataMngC_ClearFreezeFrameRecord( FaultRecordPtr->RecordNumberIndex[freezeFrameRecordIndex] );                /* [GUD]freezeFrameRecordIndex */

                /* Checks the result of set to Dem_DataMng. */
                if( resultOfSetFFRec == DEM_IRT_OK )
                {
                    /* The result means succeeded. */

                    Dem_Data_SetResultOfCmpFFRecordToTmp( freezeFrameRecordIndex, DEM_IRT_NG );                                                     /* [GUD]freezeFrameRecordIndex */

                    /* Decrements the number of freeze frame record. */
                    if( EventMemoryRecordPtr->NumberOfFreezeFrameRecords > (uint16)0U )
                    {
                        /* The number of freeze frame records is over 0. */

                        /* Decrement the number of freeze frame records. */
                        EventMemoryRecordPtr->NumberOfFreezeFrameRecords--;
                    }
                    else
                    {
                        /* The number of freeze frame records is 0 or less. */

                        /* no processing. */
                    }
                }
                else
                {
                    /* The result had not been succeeded. */
                }
            }
        }
        else
        {
            /* The record number index corresponding to the loop counter is invalid. */
            /* no processing, because the fault without freeze frame. */
        }
    }

    return ;
}

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_ClearTargetTSFFListRecord                       */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] ClearFFListRecordPtr :                              */
/*               | [in] FaultRecordPtr :                                    */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_ClearTargetTSFFListRecord
(
    P2CONST( Dem_FFListRecordForClrType, AUTOMATIC, AUTOMATIC ) ClearFFListRecordPtr,
    P2CONST( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr
)
{
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) indexOfTSFFListIndex;
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) tsffRecordClassNumPerDTCMaxNum;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsFFListRecIndex;

    tsffRecordClassNumPerDTCMaxNum = Dem_TSFFRecordClassNumPerDTCMaxNum;

    for( indexOfTSFFListIndex = (Dem_u08_TSFFListPerDTCIndexType)0U; indexOfTSFFListIndex < tsffRecordClassNumPerDTCMaxNum; indexOfTSFFListIndex++ )        /* [GUD:for]indexOfTSFFListIndex */
    {
        tsFFListRecIndex = FaultRecordPtr->TimeSeriesFreezeFrameListIndex[indexOfTSFFListIndex];                    /* [GUD]indexOfTSFFListIndex */

        if( tsFFListRecIndex != DEM_INVALID_TSFF_RECORD_INDEX )                                                     /* [GUD:if]tsFFListRecIndex */
        {
            if( ClearFFListRecordPtr->TSFFLClrFlg[indexOfTSFFListIndex] == (boolean)TRUE )                          /* [GUD]indexOfTSFFListIndex */
            {
                Dem_Data_ClearTSFFRecord( tsFFListRecIndex );                                                       /* [GUD:if]tsFFListRecIndex */
            }
        }
        else
        {
            /* No process */
        }
    }

    return;
}
#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON )   */


/****************************************************************************/
/* Function Name | Dem_Data_SubtractOneFromNumOfEventMemoryEntries          */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in/out] EventMemoryRecordPtr :                          */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_SubtractOneFromNumOfEventMemoryEntries
(
    P2VAR( Dem_EventMemoryRecordType, AUTOMATIC, AUTOMATIC ) EventMemoryRecordPtr
)
{
    /* Decrements the number of event memory entry because the fault is occurring in this event. */

    if( EventMemoryRecordPtr->NumberOfEventMemoryEntries > (Dem_u08_OrderIndexType)0U )
    {
        /* The number of event memory entries is over 0. */

        /* Decrement the number of event memory entries. */
        EventMemoryRecordPtr->NumberOfEventMemoryEntries--;
    }
    else
    {
        /* The number of event memory entries is 0 or less. */

        /* no processing. */
    }

    /* Sets the event memory record. */
    Dem_DataMngC_SetEventMemoryRecord( EventMemoryRecordPtr );


    return;
}


/****************************************************************************/
/* Function Name | Dem_Data_ClearSearchFFDIndex                             */
/* Description   | Set SearchFFDIndex At Diag Clear                         */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_ClearSearchFFDIndex
( void )
{
    Dem_DataMng_ClearSearchFFDIndex();
    return;
}


/****************************************************************************/
/* Function Name | Dem_Data_ClearTargetObdRecordNumberIndexArray            */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] ClearFFListRecordPtr :                              */
/*               | [out] FaultRecordPtr                                     */
/* Return Value  | Dem_u08_FFDIndexType     :   remain triggerFFD count.    */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
static FUNC( Dem_u08_FFDIndexType, DEM_CODE ) Dem_Data_ClearTargetObdRecordNumberIndexArray
(
    P2CONST( Dem_FFListRecordForClrType, AUTOMATIC, AUTOMATIC ) ClearFFListRecordPtr,
    P2VAR( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr
)
{
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) ffrIndex;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) obdFFRClassPerDTCMaxNum;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) remainFFDCnt;

    obdFFRClassPerDTCMaxNum = Dem_OBDFFRClassPerDTCMaxNum;
    remainFFDCnt    =   (Dem_u08_FFDIndexType)0U;

    for( ffrIndex = (Dem_u08_FFListIndexType)0U; ffrIndex < obdFFRClassPerDTCMaxNum; ffrIndex++ )       /* [GUD:for]ffrIndex */
    {
        if( ClearFFListRecordPtr->ObdFFRClrFlg[ffrIndex] == (boolean)TRUE )                             /* [GUD]ffrIndex */
        {
            FaultRecordPtr->ObdRecordNumberIndex[ffrIndex] = DEM_FFRECINDEX_INITIAL;                    /* [GUD]ffrIndex */
        }

        if ( FaultRecordPtr->ObdRecordNumberIndex[ffrIndex] != DEM_FFRECINDEX_INITIAL )                 /* [GUD]ffrIndex */
        {
            remainFFDCnt    =   remainFFDCnt + (Dem_u08_FFDIndexType)1U;
        }
    }

    return remainFFDCnt;
}
#endif  /* (DEM_OBDFFD_SUPPORT == STD_ON) */


/****************************************************************************/
/* Function Name | Dem_Data_ClearTargetRecordNumberIndexArray               */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] ClearFFListRecordPtr :                              */
/*               | [out] FaultRecordPtr                                     */
/* Return Value  | Dem_u08_FFDIndexType     :   remain triggerFFD count.    */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_FFDIndexType, DEM_CODE ) Dem_Data_ClearTargetRecordNumberIndexArray
(
    P2CONST( Dem_FFListRecordForClrType, AUTOMATIC, AUTOMATIC ) ClearFFListRecordPtr,
    P2VAR( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr
)
{
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) ffrIndex;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) nonOBDFFRClassPerDTCMaxNum;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) remainFFDCnt;

    nonOBDFFRClassPerDTCMaxNum = Dem_NonOBDFFRClassPerDTCMaxNum;
    remainFFDCnt    =   (Dem_u08_FFDIndexType)0U;

    for( ffrIndex = (Dem_u08_FFListIndexType)0U; ffrIndex < nonOBDFFRClassPerDTCMaxNum; ffrIndex++ )        /* [GUD:for]ffrIndex */
    {
        if( ClearFFListRecordPtr->FFRClrFlg[ffrIndex] == (boolean)TRUE )                                    /* [GUD]ffrIndex */
        {
            FaultRecordPtr->RecordNumberIndex[ffrIndex] = DEM_FFRECINDEX_INITIAL;                           /* [GUD]ffrIndex */
        }

        if ( FaultRecordPtr->RecordNumberIndex[ffrIndex] != DEM_FFRECINDEX_INITIAL )                        /* [GUD]ffrIndex */
        {
            remainFFDCnt    =   remainFFDCnt + (Dem_u08_FFDIndexType)1U;
        }
    }

    return remainFFDCnt;
}

/****************************************************************************/
/* Function Name | Dem_Data_ClearTargetTSFFListIndexArray                   */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] ClearFFListRecordPtr :                              */
/*               | [out] FaultRecordPtr                                     */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_Data_ClearTargetTSFFListIndexArray
(
    P2CONST( Dem_FFListRecordForClrType, AUTOMATIC, AUTOMATIC ) ClearFFListRecordPtr,
    P2VAR( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr
)
{
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) tsffrIndex;
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) tsffRecordClassNumPerDTCMaxNum;

    tsffRecordClassNumPerDTCMaxNum = Dem_TSFFRecordClassNumPerDTCMaxNum;

    for( tsffrIndex = (Dem_u08_TSFFListPerDTCIndexType)0U; tsffrIndex < tsffRecordClassNumPerDTCMaxNum; tsffrIndex++ )      /* [GUD:for]tsffrIndex */
    {
        if( ClearFFListRecordPtr->TSFFLClrFlg[tsffrIndex] == (boolean)TRUE )                                                /* [GUD]tsffrIndex */
        {
            FaultRecordPtr->TimeSeriesFreezeFrameListIndex[tsffrIndex] = DEM_INVALID_VACANT_TSFFLIST_INDEX;                 /* [GUD]tsffrIndex */
        }
    }

    return;
}
#endif  /* (DEM_TSFF_PM_SUPPORT == STD_ON) */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-0-0         :2019-05-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
