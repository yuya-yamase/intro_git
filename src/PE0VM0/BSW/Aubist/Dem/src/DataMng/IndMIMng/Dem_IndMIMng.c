/* Dem_IndMIMng_c(v5-10-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/IndMIMng/CODE                                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>

#if ( DEM_WWH_OBD_SUPPORT == STD_ON )

#include "../../../cfg/Dem_Cfg.h"
#include "../../../cfg/Dem_NvM_Cfg.h"
#include "../../../cfg/Dem_WWHObd_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../inc/Dem_CmnLib_Control.h"
#include "../../../inc/Dem_Rc_RecMngCmn.h"
#include "../../../inc/Dem_Rc_RecMngCmn_Table.h"
#include "../../../inc/Dem_Pm_DataAvl.h"

#include "../../../inc/Dem_Rc_IndMIMng.h"

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

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
static FUNC( void, DEM_CODE ) Dem_IndMIMng_InitMirrorMemory
( void );

#if ( DEM_INDMI_RECORD_PADDING_EXIST == STD_ON )
static FUNC( void, DEM_CODE ) Dem_IndMIMng_InitPadding
(
    P2VAR( Dem_IndMIB1CounterRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) IndMIRecordPtr
);
#endif  /* ( DEM_INDMI_RECORD_PADDING_EXIST == STD_ON ) */
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

static VAR( Dem_u16_IndMIIndexType, DEM_VAR_NO_INIT ) Dem_IndMIMng_IndMIIndexForVerify;

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
VAR( Dem_u08_RecMngMtxStsType, DEM_VAR_NO_INIT ) Dem_IndMINvMStatus[ DEM_INDMIB1COUNTER_RECORD_NUM ];
VAR( Dem_IndMIB1CounterRecordType, DEM_VAR_NO_INIT ) Dem_TmpIndMIB1CounterMirror;
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data(SAVED_ZONE)                                                         */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_SAVED_ZONE
#include <Dem_MemMap.h>

VAR( Dem_IndMIB1CounterRecordType, DEM_VAR_SAVED_ZONE ) Dem_IndMIB1CounterRecord[ DEM_INDMIB1COUNTER_RECORD_NUM ];

#define DEM_STOP_SEC_VAR_SAVED_ZONE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Functions(set to RecMngCmn function table.)                              */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_IndMIMng_Init                                        */
/* Description   | initialize function.                                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based from Dem_AltIUMPRMng_Init.            */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_IndMIMng_Init
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex     /* MISRA DEVIATION */
)
{
    Dem_IndMIMng_IndMIIndexForVerify = (Dem_u16_IndMIIndexType)0U;
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    /* [FuncSw] */
    Dem_IndMIMng_InitMirrorMemory();
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */
    return;
}

/****************************************************************************/
/* Function Name | Dem_IndMIMng_InitSavedZone                               */
/* Description   | Initialize savedzone process .                           */
/* Preconditions |                                                          */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/*               | [in] InitType :                                          */
/*               |       Initialize savedzone type                          */
/*               |          DEM_SZINITTYPE_INITIALIZE_ALL                   */
/*               |          DEM_SZINITTYPE_INITIALIZE_WITHOUT_PFC           */
/*               |          DEM_SZINITTYPE_INITIALIZE_WITHOUT_PFC_AND_IUMPR */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_IndMIMng_InitSavedZone
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    VAR( Dem_SavedZoneInitializeType, AUTOMATIC ) InitType  /* MISRA DEVIATION */
)
{
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) indMIIndex;
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) indMIMaxNumberOfClassB1Event;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindIndMI;

    recMngCmnKindIndMI = Dem_RecMngCmnKindIndMI;
    indMIMaxNumberOfClassB1Event = Dem_WWHOBDMaxNumberOfClassB1Event;

    for( indMIIndex = (Dem_u16_IndMIIndexType)0U; indMIIndex < indMIMaxNumberOfClassB1Event; indMIIndex++ )     /* [GUD:for]indMIIndex */
    {
        Dem_IndMIB1CounterRecord[ indMIIndex ].B1Counter            =   DEM_B1COUNTER_FACTORY_DEFAULT;              /* [GUD]indMIIndex */
        Dem_IndMIB1CounterRecord[ indMIIndex ].EventStrgIndex       =   DEM_EVENTSTRGINDEX_INVALID;                 /* [GUD]indMIIndex */
        Dem_IndMIB1CounterRecord[ indMIIndex ].B1ClearCycleCounter  =   DEM_B1CLEARCYCLECOUNTER_FACTORY_DEFAULT;    /* [GUD]indMIIndex */
        Dem_IndMIB1CounterRecord[ indMIIndex ].ClearID              =   DEM_CLRINFO_RECORD_INITIAL;                 /* [GUD]indMIIndex */

        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindIndMI, (Dem_u16_RecordIndexType)indMIIndex );
    }
    return;
}

/****************************************************************************/
/* Function Name | Dem_IndMIMng_DataVerify                                  */
/* Description   | verify record data.                                      */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |          DEM_IRT_OK      : DataVerify completed.         */
/*               |          DEM_IRT_PENDING : Continue DataVerify.          */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/*   v5-8-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IndMIMng_DataVerify
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex     /* MISRA DEVIATION */
)
{
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) indMIIndex;
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) indMIMaxNumberOfClassB1Event;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindIndMI;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndexRecord;
    VAR( boolean, AUTOMATIC ) useB1Counter;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( boolean, AUTOMATIC ) b1RecordClearFlag;
    VAR( Dem_u08_InternalReturnType,AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) availableStatus;
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) processCount;
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) verifyLoopNumByCycle;
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) obdClearId;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) clrInfoNvmReadResult;
    VAR( Dem_u32_B1CounterType, AUTOMATIC )  b1CounterHold;
    VAR( Dem_u32_B1CounterType, AUTOMATIC )  b1CounterThreshold;
    VAR( boolean, AUTOMATIC ) clearAllowed;
#if ( DEM_CLEAR_EVENT_ALLOWED_BY_CALLOUT_SUPPORT == STD_ON )
    VAR( boolean, AUTOMATIC ) clearAllowedByCallout;
#endif  /* ( DEM_CLEAR_EVENT_ALLOWED_BY_CALLOUT_SUPPORT == STD_ON ) */

    eventStorageNum = Dem_PrimaryMemEventStorageNum;
    recMngCmnKindIndMI = Dem_RecMngCmnKindIndMI;
    indMIMaxNumberOfClassB1Event = Dem_WWHOBDMaxNumberOfClassB1Event;
    processCount = (Dem_u16_IndMIIndexType)0U;

    clrInfoNvmReadResult = Dem_ClrInfoMng_GetNvmReadResult();
    obdClearId = Dem_ClrInfoMng_GetObdClearID();
    b1CounterHold = Dem_CfgInfoPm_GetB1CounterHold();
    b1CounterThreshold = Dem_CfgInfoPm_GetB1CounterThreshold();

    verifyLoopNumByCycle = Dem_IndMIRecordNumForVerifyByCycle;

    retVal = DEM_IRT_OK;

    for( indMIIndex = Dem_IndMIMng_IndMIIndexForVerify; indMIIndex < indMIMaxNumberOfClassB1Event; indMIIndex++ )       /* [GUD:for]indMIIndex */
    {
        if ( processCount < verifyLoopNumByCycle )
        {
            b1RecordClearFlag = (boolean)TRUE;
            eventStrgIndexRecord = Dem_IndMIB1CounterRecord[ indMIIndex ].EventStrgIndex;                               /* [GUD]indMIIndex */

            if ( eventStrgIndexRecord != DEM_EVENTSTRGINDEX_INVALID )
            {
                if ( eventStrgIndexRecord < eventStorageNum )                                           /* [GUD:if]eventStrgIndexRecord */
                {
                    useB1Counter  =   Dem_CfgInfoPm_ChkDTCCls_UseB1Counter( eventStrgIndexRecord );     /* [GUD]eventStrgIndexRecord */
                    if( useB1Counter == (boolean)TRUE )
                    {
                        availableStatus = Dem_DataAvl_GetEvtAvl_InEvtStrgGrp( eventStrgIndexRecord );   /* [GUD]eventStrgIndexRecord */
                        if ( availableStatus == (boolean)TRUE )
                        {
                            b1RecordClearFlag = (boolean)FALSE;
                        }
                    }
                }

                if ( b1RecordClearFlag == (boolean)TRUE )
                {
                    Dem_IndMIB1CounterRecord[ indMIIndex ].B1Counter            =   (Dem_u32_B1CounterType)0U;              /* [GUD]indMIIndex */
                    Dem_IndMIB1CounterRecord[ indMIIndex ].EventStrgIndex       =   DEM_EVENTSTRGINDEX_INVALID;             /* [GUD]indMIIndex */
                    Dem_IndMIB1CounterRecord[ indMIIndex ].B1ClearCycleCounter  =   (Dem_u08_B1ClearCycleCounterType)0U;    /* [GUD]indMIIndex */
                    Dem_IndMIB1CounterRecord[ indMIIndex ].ClearID              =   DEM_CLRINFO_RECORD_INITIAL;             /* [GUD]indMIIndex */

                    Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindIndMI, (Dem_u16_RecordIndexType)indMIIndex );             /* [GUD]indMIIndex */
                }
                else
                {
                    clearAllowed = Dem_CfgInfoPm_ClearAllowedByConfig_InEvtStrgGrp( eventStrgIndexRecord );     /* [GUD]eventStrgIndexRecord */
                    if ( clearAllowed == (boolean)TRUE )
                    {
                        if ( clrInfoNvmReadResult != DEM_IRT_OK )
                        {
                            if ( Dem_IndMIB1CounterRecord[ indMIIndex ].B1Counter >= b1CounterThreshold )                   /* [GUD]indMIIndex */
                            {
                                Dem_IndMIB1CounterRecord[ indMIIndex ].B1Counter  =  b1CounterHold;                         /* [GUD]indMIIndex */
                            }

                            Dem_IndMIB1CounterRecord[ indMIIndex ].ClearID    =  obdClearId;                                /* [GUD]indMIIndex */
                            Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindIndMI, (Dem_u16_RecordIndexType)indMIIndex );
                        }
                        else
                        {
                            if ( obdClearId != Dem_IndMIB1CounterRecord[ indMIIndex ].ClearID )                             /* [GUD]indMIIndex */
                            {
#if ( DEM_CLEAR_EVENT_ALLOWED_BY_CALLOUT_SUPPORT == STD_ON )
                                /*  check clear allowed from callout function.  */
                                clearAllowedByCallout   =   Dem_CfgInfoPm_JudgeClearAllowedByCallout( eventStrgIndexRecord );  /* [GUD]eventStrgIndexRecord */

                                if ( clearAllowedByCallout == (boolean)TRUE )
#endif  /* ( DEM_CLEAR_EVENT_ALLOWED_BY_CALLOUT_SUPPORT == STD_ON ) */
                                {
                                    if ( Dem_IndMIB1CounterRecord[ indMIIndex ].B1Counter >= b1CounterThreshold )               /* [GUD]indMIIndex */
                                    {
                                        Dem_IndMIB1CounterRecord[ indMIIndex ].B1Counter  =  b1CounterHold;                     /* [GUD]indMIIndex */
                                    }

                                    Dem_IndMIB1CounterRecord[ indMIIndex ].ClearID    =  obdClearId;                            /* [GUD]indMIIndex */
                                }
                            }
                        }
                    }
                }
            }
            processCount = processCount + (Dem_u16_IndMIIndexType)1U;
        }
        else
        {
            retVal = DEM_IRT_PENDING;
            Dem_IndMIMng_IndMIIndexForVerify = indMIIndex;
            break;
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_IndMIMng_GetEmptyRecordIndex                         */
/* Description   | Get empty B1Record index.                                */
/* Preconditions | none                                                     */
/* Parameters    | [out] IndMIIndexPtr                                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |          DEM_IRT_OK : Empty record exists                */
/*               |          DEM_IRT_NG : Empty redord don't exist.          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IndMIMng_GetEmptyRecordIndex
(
    P2VAR( Dem_u16_IndMIIndexType, AUTOMATIC, AUTOMATIC ) IndMIIndexPtr
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndexRecord;
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) indMIIndex;
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) indMIMaxNumberOfClassB1Event;
    VAR( Dem_u08_InternalReturnType,AUTOMATIC ) retVal;
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) retIndMIIndex;

    indMIMaxNumberOfClassB1Event = Dem_WWHOBDMaxNumberOfClassB1Event;
    retVal = DEM_IRT_NG;
    retIndMIIndex = DEM_INDMIINDEX_INVALID;

    for( indMIIndex = (Dem_u16_IndMIIndexType)0U; indMIIndex < indMIMaxNumberOfClassB1Event; indMIIndex++ )     /* [GUD:for]indMIIndex */
    {
        eventStrgIndexRecord    =   Dem_IndMIB1CounterRecord[ indMIIndex ].EventStrgIndex;                      /* [GUD]indMIIndex */

        if ( eventStrgIndexRecord == DEM_EVENTSTRGINDEX_INVALID )
        {
            /* this is empty record.  */
            retIndMIIndex = indMIIndex;
            retVal = DEM_IRT_OK;
            break;
        }
    }

    *IndMIIndexPtr = retIndMIIndex;

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_IndMIMng_GetNextEmptyRecordIndex                     */
/* Description   | Get next empty B1Record index.                           */
/* Preconditions | none                                                     */
/* Parameters    | [in]  StartIndex                                         */
/*               | [out] IndMIIndexPtr                                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |          DEM_IRT_OK : Empty record exists                */
/*               |          DEM_IRT_NG : Empty redord don't exist.          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IndMIMng_GetNextEmptyRecordIndex
(
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) StartIndex,
    P2VAR( Dem_u16_IndMIIndexType, AUTOMATIC, AUTOMATIC ) IndMIIndexPtr
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndexRecord;
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) indMIIndex;
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) indMIMaxNumberOfClassB1Event;
    VAR( Dem_u08_InternalReturnType,AUTOMATIC ) retVal;
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) retIndMIIndex;

    indMIMaxNumberOfClassB1Event = Dem_WWHOBDMaxNumberOfClassB1Event;
    retVal = DEM_IRT_NG;
    retIndMIIndex = DEM_INDMIINDEX_INVALID;

    for( indMIIndex = StartIndex; indMIIndex < indMIMaxNumberOfClassB1Event; indMIIndex++ )     /* [GUD:for]indMIIndex */
    {
        eventStrgIndexRecord    =   Dem_IndMIB1CounterRecord[ indMIIndex ].EventStrgIndex;                      /* [GUD]indMIIndex */

        if ( eventStrgIndexRecord == DEM_EVENTSTRGINDEX_INVALID )
        {
            /* this is empty record.  */
            retIndMIIndex = indMIIndex;
            retVal = DEM_IRT_OK;
            break;
        }
    }

    *IndMIIndexPtr = retIndMIIndex;

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_IndMIMng_RegistB1CounterRecord                       */
/* Description   | regist B1Record counter.                                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] IndMIIndex                                          */
/*               | [in] EventStrgIndex                                      */
/* Return Value  | void                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_IndMIMng_RegistB1CounterRecord
(
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) IndMIIndex,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) indMIMaxNumberOfClassB1Event;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindIndMI;
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) obdClearId;

    indMIMaxNumberOfClassB1Event = Dem_WWHOBDMaxNumberOfClassB1Event;

    if ( IndMIIndex < indMIMaxNumberOfClassB1Event )                                                    /* [GUD:if]indMIIndex */
    {
        obdClearId = Dem_ClrInfoMng_GetObdClearID();

        SchM_Enter_Dem_IndMI();
        Dem_IndMIB1CounterRecord[ IndMIIndex ].B1Counter = (Dem_u32_B1CounterType)0x00000000U;                  /* [GUD]indMIIndex */
        Dem_IndMIB1CounterRecord[ IndMIIndex ].EventStrgIndex = EventStrgIndex;                                 /* [GUD]indMIIndex */
        Dem_IndMIB1CounterRecord[ IndMIIndex ].B1ClearCycleCounter = (Dem_u08_B1ClearCycleCounterType)0x00U;    /* [GUD]indMIIndex */
        Dem_IndMIB1CounterRecord[ IndMIIndex ].ClearID = obdClearId;                                            /* [GUD]indMIIndex */
        SchM_Exit_Dem_IndMI();
        recMngCmnKindIndMI = Dem_RecMngCmnKindIndMI;
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindIndMI, ( Dem_u16_RecordIndexType )IndMIIndex );           /* [GUD]indMIIndex */
    }
    return;
}

/****************************************************************************/
/* Function Name | Dem_IndMIMng_ClearB1CounterRecord                        */
/* Description   | Clear B1 Counter.                                        */
/* Preconditions | none                                                     */
/* Parameters    | [in]  IndMIIndex : IndMIIndex.                           */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_IndMIMng_ClearB1CounterRecord
(
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) IndMIIndex
)
{
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) indMIMaxNumberOfClassB1Event;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindIndMI;
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) obdClearId;

    indMIMaxNumberOfClassB1Event = Dem_WWHOBDMaxNumberOfClassB1Event;

    if ( IndMIIndex < indMIMaxNumberOfClassB1Event )                                                    /* [GUD:if]indMIIndex */
    {
        obdClearId = Dem_ClrInfoMng_GetObdClearID();

        SchM_Enter_Dem_IndMI();
        Dem_IndMIB1CounterRecord[ IndMIIndex ].B1Counter = (Dem_u32_B1CounterType)0x00000000U;                  /* [GUD]indMIIndex */
        Dem_IndMIB1CounterRecord[ IndMIIndex ].EventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;                     /* [GUD]indMIIndex */
        Dem_IndMIB1CounterRecord[ IndMIIndex ].B1ClearCycleCounter = (Dem_u08_B1ClearCycleCounterType)0x00U;    /* [GUD]indMIIndex */
        Dem_IndMIB1CounterRecord[ IndMIIndex ].ClearID = obdClearId;                                            /* [GUD]indMIIndex */
        SchM_Exit_Dem_IndMI();

        recMngCmnKindIndMI = Dem_RecMngCmnKindIndMI;
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindIndMI, ( Dem_u16_RecordIndexType )IndMIIndex );           /* [GUD]indMIIndex */
    }
    return;
}

/****************************************************************************/
/* Function Name | Dem_IndMIMng_HoldB1Counter                               */
/* Description   | Hold B1 Counter.                                         */
/* Preconditions | none                                                     */
/* Parameters    | [in]  IndMIIndex : IndMIIndex.                           */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_IndMIMng_HoldB1Counter
(
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) IndMIIndex
)
{
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) indMIMaxNumberOfClassB1Event;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindIndMI;
    VAR( Dem_u32_B1CounterType, AUTOMATIC )  b1CounterHold;
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) obdClearId;

    indMIMaxNumberOfClassB1Event = Dem_WWHOBDMaxNumberOfClassB1Event;
    if ( IndMIIndex < indMIMaxNumberOfClassB1Event )                                                /* [GUD:if]indMIIndex */
    {
        obdClearId = Dem_ClrInfoMng_GetObdClearID();
        b1CounterHold = Dem_CfgInfoPm_GetB1CounterHold();

        SchM_Enter_Dem_IndMI();
        Dem_IndMIB1CounterRecord[ IndMIIndex ].B1Counter = b1CounterHold;                           /* [GUD]indMIIndex */
        Dem_IndMIB1CounterRecord[ IndMIIndex ].ClearID = obdClearId;                                /* [GUD]indMIIndex */
        SchM_Exit_Dem_IndMI();

        recMngCmnKindIndMI = Dem_RecMngCmnKindIndMI;
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindIndMI, ( Dem_u16_RecordIndexType )IndMIIndex );   /* [GUD]indMIIndex */
    }
    return;
}

/****************************************************************************/
/* Function Name | Dem_IndMIMng_UpdateClearId                               */
/* Description   | Update Clear ID.                                         */
/* Preconditions | none                                                     */
/* Parameters    | [in]  IndMIIndex : IndMIIndex.                           */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_IndMIMng_UpdateClearId
(
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) IndMIIndex
)
{
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) indMIMaxNumberOfClassB1Event;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindIndMI;
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) obdClearId;

    indMIMaxNumberOfClassB1Event = Dem_WWHOBDMaxNumberOfClassB1Event;
    if ( IndMIIndex < indMIMaxNumberOfClassB1Event )                                            /* [GUD:if]indMIIndex */
    {
        obdClearId = Dem_ClrInfoMng_GetObdClearID();

        SchM_Enter_Dem_IndMI();
        Dem_IndMIB1CounterRecord[ IndMIIndex ].ClearID = obdClearId;                                    /* [GUD]indMIIndex */
        SchM_Exit_Dem_IndMI();

        recMngCmnKindIndMI = Dem_RecMngCmnKindIndMI;
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindIndMI, ( Dem_u16_RecordIndexType )IndMIIndex );   /* [GUD]indMIIndex */
    }
    return;
}

/****************************************************************************/
/* Function Name | Dem_IndMIMng_GetB1ClearCycleCounter                      */
/* Description   | Increment B1ClearCycleCounter.                           */
/* Preconditions | none                                                     */
/* Parameters    | [in]  IndMIIndex                                         */
/*               | [out] B1ClearCycleCounterPtr                             */
/* Return Value  | Dem_u08_InternalReturnType                               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IndMIMng_GetB1ClearCycleCounter
(
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) IndMIIndex,
    P2VAR( Dem_u08_B1ClearCycleCounterType, AUTOMATIC, AUTOMATIC ) B1ClearCycleCounterPtr
)
{
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) indMIMaxNumberOfClassB1Event;
    VAR( Dem_u08_B1ClearCycleCounterType, AUTOMATIC ) retB1ClearCycleCounter;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;
    retB1ClearCycleCounter = (Dem_u08_B1ClearCycleCounterType)0U;
    indMIMaxNumberOfClassB1Event = Dem_WWHOBDMaxNumberOfClassB1Event;

    if ( IndMIIndex < indMIMaxNumberOfClassB1Event )                                                /* [GUD:if]indMIIndex */
    {
        retB1ClearCycleCounter = Dem_IndMIB1CounterRecord[ IndMIIndex ].B1ClearCycleCounter;            /* [GUD]indMIIndex */
        retVal = DEM_IRT_OK;
    }

    *B1ClearCycleCounterPtr = retB1ClearCycleCounter;
    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_IndMIMng_SetB1ClearCycleCounter                      */
/* Description   | Increment B1ClearCycleCounter.                           */
/* Preconditions | none                                                     */
/* Parameters    | [in] IndMIIndex                                          */
/*               | [in] B1ClearCycleCounter                                 */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_IndMIMng_SetB1ClearCycleCounter
(
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) IndMIIndex,
    VAR( Dem_u08_B1ClearCycleCounterType, AUTOMATIC ) B1ClearCycleCounter
)
{
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) indMIMaxNumberOfClassB1Event;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindIndMI;

    indMIMaxNumberOfClassB1Event = Dem_WWHOBDMaxNumberOfClassB1Event;

    if ( IndMIIndex < indMIMaxNumberOfClassB1Event )                                            /* [GUD:if]indMIIndex */
    {
        Dem_IndMIB1CounterRecord[ IndMIIndex ].B1ClearCycleCounter = B1ClearCycleCounter;           /* [GUD]indMIIndex */
        Dem_IndMIB1CounterRecord[ IndMIIndex ].ClearID = Dem_ClrInfoMng_GetObdClearID();            /* [GUD]indMIIndex */
        recMngCmnKindIndMI = Dem_RecMngCmnKindIndMI;
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindIndMI, ( Dem_u16_RecordIndexType )IndMIIndex );   /* [GUD]indMIIndex */
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_IndMIMng_ClearB1ClearCycleCounter                    */
/* Description   | Increment B1ClearCycleCounter.                           */
/* Preconditions | none                                                     */
/* Parameters    | [in]  IndMIIndex : IndMIIndex.                           */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_IndMIMng_ClearB1ClearCycleCounter
(
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) IndMIIndex
)
{
    VAR( Dem_u08_B1ClearCycleCounterType, AUTOMATIC ) b1ClearCycleCounter;
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) indMIMaxNumberOfClassB1Event;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindIndMI;

    indMIMaxNumberOfClassB1Event = Dem_WWHOBDMaxNumberOfClassB1Event;

    if ( IndMIIndex < indMIMaxNumberOfClassB1Event )                                            /* [GUD:if]indMIIndex */
    {
        b1ClearCycleCounter = Dem_IndMIB1CounterRecord[ IndMIIndex ].B1ClearCycleCounter;           /* [GUD]indMIIndex */

        if ( b1ClearCycleCounter > (Dem_u08_B1ClearCycleCounterType)0U )
        {
            Dem_IndMIB1CounterRecord[ IndMIIndex ].B1ClearCycleCounter = (Dem_u08_B1ClearCycleCounterType)0U;       /* [GUD]indMIIndex */
            Dem_IndMIB1CounterRecord[ IndMIIndex ].ClearID = Dem_ClrInfoMng_GetObdClearID();                        /* [GUD]indMIIndex */
            recMngCmnKindIndMI = Dem_RecMngCmnKindIndMI;
            Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindIndMI, ( Dem_u16_RecordIndexType )IndMIIndex );           /* [GUD]indMIIndex */
        }
    }
    return;
}

/****************************************************************************/
/* Function Name | Dem_IndMIMng_SetB1Counter                                */
/* Description   | Set B1 Countger.                                         */
/* Preconditions | none                                                     */
/* Parameters    | [in] IndMIIndex :                                        */
/*               | [in] B1Counter :                                         */
/* Return Value  | Dem_u08_InternalReturnType                               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/*   v5-10-0     | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IndMIMng_SetB1Counter
(
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) IndMIIndex,
    VAR( Dem_u32_B1CounterType, AUTOMATIC ) B1Counter
)
{
    VAR( Dem_u32_B1CounterType, AUTOMATIC ) b1Counter_base;
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) indMIMaxNumberOfClassB1Event;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindIndMI;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal      =   DEM_IRT_NG;

    indMIMaxNumberOfClassB1Event = Dem_WWHOBDMaxNumberOfClassB1Event;

    if ( IndMIIndex < indMIMaxNumberOfClassB1Event )                                                        /* [GUD:if]indMIIndex */
    {
        b1Counter_base      =   Dem_IndMIB1CounterRecord[ IndMIIndex ].B1Counter;                           /* [GUD]indMIIndex */
        if ( b1Counter_base != B1Counter )
        {
            SchM_Enter_Dem_IndMI();
            Dem_IndMIB1CounterRecord[ IndMIIndex ].B1Counter  =   B1Counter;                                /* [GUD]indMIIndex */
            SchM_Exit_Dem_IndMI();

            Dem_IndMIB1CounterRecord[ IndMIIndex ].ClearID = Dem_ClrInfoMng_GetObdClearID();                /* [GUD]indMIIndex */
            recMngCmnKindIndMI = Dem_RecMngCmnKindIndMI;
            Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindIndMI, ( Dem_u16_RecordIndexType )IndMIIndex );   /* [GUD]indMIIndex */
        }
        retVal  =   DEM_IRT_OK;
    }
    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_IndMIMng_GetB1Counter                                */
/* Description   | Get B1 Countger.                                         */
/* Preconditions | none                                                     */
/* Parameters    | [in] IndMIIndex :                                        */
/*               | [out] B1CounterPtr :                                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IndMIMng_GetB1Counter
(
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) IndMIIndex,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr,
    P2VAR( Dem_u32_B1CounterType, AUTOMATIC, AUTOMATIC ) B1CounterPtr
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) indMIMaxNumberOfClassB1Event;
    VAR( Dem_u32_B1CounterType, AUTOMATIC ) b1Counter;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal  =   DEM_IRT_NG;

    eventStrgIndex  =   DEM_EVENTSTRGINDEX_INVALID;
    eventStorageNum =   Dem_PrimaryMemEventStorageNum;
    indMIMaxNumberOfClassB1Event = Dem_WWHOBDMaxNumberOfClassB1Event;
    b1Counter = (Dem_u32_B1CounterType)0U;

    if ( IndMIIndex < indMIMaxNumberOfClassB1Event )                                                /* [GUD:if]indMIIndex */
    {
        retVal  =   DEM_IRT_OK;
        eventStrgIndex  =   Dem_IndMIB1CounterRecord[ IndMIIndex ].EventStrgIndex;                  /* [GUD]indMIIndex */
        if ( eventStrgIndex < eventStorageNum )
        {
            b1Counter   =   Dem_IndMIB1CounterRecord[ IndMIIndex ].B1Counter;                       /* [GUD]indMIIndex */
        }
        else
        {
            eventStrgIndex  =   DEM_EVENTSTRGINDEX_INVALID;
        }
    }
    *EventStrgIndexPtr  =   eventStrgIndex;
    *B1CounterPtr       =   b1Counter;

    return retVal;
}

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_IndMIMng_SetRecordMirror                             */
/* Description   | Copy to the Mirror Memory.                               */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/*               | [in/out] BlockMirrorPtr :                                */
/*               |        Nonvolatile synchronous data information.         */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based from Dem_AltIUMPRMng_SetRecordMirror. */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_IndMIMng_SetRecordMirror
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
)
{
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) indMIIndex;
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) indMIMaxNumberOfClassB1Event;

    indMIIndex                   = (Dem_u16_IndMIIndexType)(BlockMirrorPtr->RecordIndex);
    indMIMaxNumberOfClassB1Event = Dem_WWHOBDMaxNumberOfClassB1Event;

    if ( indMIIndex < indMIMaxNumberOfClassB1Event )                                                    /* [GUD:if]indMIIndex */
    {
        Dem_TmpIndMIB1CounterMirror.B1Counter           =   Dem_IndMIB1CounterRecord[ indMIIndex ].B1Counter;               /* [GUD]indMIIndex */
        Dem_TmpIndMIB1CounterMirror.EventStrgIndex      =   Dem_IndMIB1CounterRecord[ indMIIndex ].EventStrgIndex;          /* [GUD]indMIIndex */
        Dem_TmpIndMIB1CounterMirror.B1ClearCycleCounter =   Dem_IndMIB1CounterRecord[ indMIIndex ].B1ClearCycleCounter;     /* [GUD]indMIIndex */
        Dem_TmpIndMIB1CounterMirror.ClearID             =   Dem_IndMIB1CounterRecord[ indMIIndex ].ClearID;                 /* [GUD]indMIIndex */
    }

    BlockMirrorPtr->MirrorPtr = &Dem_TmpIndMIB1CounterMirror;

    return;
}

/****************************************************************************/
/* Function Name | Dem_IndMIMng_GetEventIdFromRecordData                    */
/* Description   | get event id from record data                            */
/* Preconditions | none                                                     */
/* Parameters    | [in]  RecordFieldIndex :                                 */
/*               | [in]  RecordIndex :                                      */
/*               | [out] EventIdPtr  :                                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_NG : failed                               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based from Dem_AltIUMPRMng_GetEventIdFromRecordData. */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IndMIMng_GetEventIdFromRecordData
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) RecordIndex,      /* MISRA DEVIATION */
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr   /* MISRA DEVIATION */
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) indMIIndex;
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) indMIMaxNumberOfClassB1Event;

    retVal  =   DEM_IRT_NG;
    indMIIndex          =   ( Dem_u16_IndMIIndexType )RecordIndex;
    indMIMaxNumberOfClassB1Event = Dem_WWHOBDMaxNumberOfClassB1Event;

    if( indMIIndex < indMIMaxNumberOfClassB1Event )                                                     /* [GUD:if]indMIIndex */
    {
        eventStrgIndex      =   Dem_IndMIB1CounterRecord[ indMIIndex ].EventStrgIndex;                  /* [GUD]indMIIndex */
        retVal  =   Dem_CfgInfoPm_CnvEventStrgIndexToEventId( eventStrgIndex, EventIdPtr );
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_IndMIMng_InitMirrorMemory                            */
/* Description   | Initialize the Mirror Memory.                            */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based from Dem_AltIUMPRMng_InitMirrorMemory.*/
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_IndMIMng_InitMirrorMemory
( void )
{
    Dem_TmpIndMIB1CounterMirror.B1Counter           =   (Dem_u32_B1CounterType)0U;
    Dem_TmpIndMIB1CounterMirror.EventStrgIndex      =   DEM_EVENTSTRGINDEX_INVALID;
    Dem_TmpIndMIB1CounterMirror.B1ClearCycleCounter =   (Dem_u08_B1ClearCycleCounterType)0U;
    Dem_TmpIndMIB1CounterMirror.ClearID             =   DEM_CLRINFO_RECORD_INITIAL;

#if ( DEM_INDMI_RECORD_PADDING_EXIST == STD_ON ) /*  [FuncSw]    */
    Dem_IndMIMng_InitPadding( &Dem_TmpIndMIB1CounterMirror );
#endif  /* ( DEM_ALTIUMPR_RECORD_PADDING_EXIST == STD_ON )          */

    return;
}

#if ( DEM_INDMI_RECORD_PADDING_EXIST == STD_ON )
/****************************************************************************/
/* Function Name | Dem_IndMIMng_InitPadding                                 */
/* Description   | Initializes the IndMI record padding data.               */
/* Preconditions | none                                                     */
/* Parameters    | [in] IndMIRecordPtr    :                                 */
/*               |       The pointer of the operation cycle record.         */
/*               |       &Dem_IndMIB1CounterRecord -DEM_VAR_SAVED_ZONE-     */
/*               |       &Dem_TmpIndMIB1CounterMirror -DEM_VAR_NO_INIT-     */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based from Dem_AltIUMPRMng_InitPadding.     */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_IndMIMng_InitPadding
(
    P2VAR( Dem_IndMIB1CounterRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) IndMIRecordPtr
)
{
    VAR( Dem_u16_PaddingIndexType, AUTOMATIC ) paddingSize;
    VAR( Dem_u16_PaddingIndexType, AUTOMATIC ) paddingIndex;

    paddingSize = Dem_IndMIRecordBlockPaddingSize;

    for( paddingIndex = (Dem_u16_PaddingIndexType)0U; paddingIndex < paddingSize; paddingIndex++ )      /* [GUD:for]paddingIndex */
    {
        IndMIRecordPtr->Reserve[paddingIndex] = (uint8)0U;                                           /* [GUD]paddingIndex *//* [ARYCHK] DEM_INDMI_RECORD_PADDINGSIZE_TO_BLOCKSIZE / 1 / paddingIndex */
    }

    return;
}
#endif  /* ( DEM_ALTIUMPR_RECORD_PADDING_EXIST == STD_ON )  */
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_WWH_OBD_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/*  v5-8-0         :2024-10-29                                              */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
