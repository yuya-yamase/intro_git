/* Dem_UdmMngVld_c(v5-7-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/UdmMngVld/CODE                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

#include "../../../cfg/Dem_UserDefMem_Cfg.h"
#include "../../../inc/Dem_Rc_UdmMng.h"
#include "../../../inc/Dem_Rc_ClrInfoMng.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_Rc_RecMngCmn.h"
#include "../../../inc/Dem_Rc_RecMngCmn_Table.h"
#include "../../../inc/Dem_Rc_UdmMng_rc.h"
#include "../../../inc/Dem_Rc_UdmEventRecordTable.h"
#include "../../../inc/Dem_Rc_UdmFaultRecordTable.h"
#include "Dem_UdmMng_local.h"

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

static FUNC( void, DEM_CODE ) Dem_UdmMngVld_VerifyEvent
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmEventStrgIndexType, AUTOMATIC ) UdmEventStrgIndex,
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) ClrInfoNvmReadResult
);
static FUNC( void, DEM_CODE ) Dem_UdmMngVld_VerifiedDiagData
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmEventStrgIndexType, AUTOMATIC ) UdmEventStrgIndex,
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmFaultIndex,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyIdOfUdmEvent
);

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmMngVld_ClearAllNotVerifiedRecord
( void );

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>
/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

static VAR( Dem_u16_UdmEventStrgIndexType,DEM_VAR_NO_INIT ) Dem_UdmMngVld_VerifyLoopCount;
static VAR( Dem_u16_UdmEventStrgIndexType, DEM_VAR_NO_INIT ) Dem_UdmMngVld_UdmEvtIndexForVerify;

static VAR( Dem_u16_RecordKindIndexType, DEM_VAR_NO_INIT ) Dem_UdmMngVld_ClearRecordKind;
static VAR( Dem_u16_RecordIndexType, DEM_VAR_NO_INIT ) Dem_UdmMngVld_ClearRecordIndex;

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_UdmMngVld_DataInit                                   */
/* Description   | Init Udm Diag data for Verification                      */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmMngVld_DataInit
( void )
{
    Dem_UdmMngVld_VerifyLoopCount = (Dem_u16_UdmEventStrgIndexType)0U;
    Dem_UdmMngVld_UdmEvtIndexForVerify = (Dem_u16_UdmEventIndexType)0U;
    Dem_UdmMngVld_ClearRecordKind = (Dem_u16_RecordKindIndexType)0U;
    Dem_UdmMngVld_ClearRecordIndex = (Dem_u16_RecordIndexType)0U;

    return;
}

/****************************************************************************/
/* Function Name | Dem_UdmMngVld_DataVerify                                 */
/* Description   | Verifies Udm Diag data.                                  */
/* Preconditions | none                                                     */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        The index for Dem_UserDefinedMemoryTable[].       */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |          DEM_IRT_OK      : DataVerify completed.         */
/*               |          DEM_IRT_PENDING : Continue DataVerify.          */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmMngVld_DataVerify
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex
)
{
    VAR( Dem_u16_UdmEventStrgIndexType, AUTOMATIC ) udmEventStrgIndex;
    VAR( Dem_u16_UdmEventStrgIndexType, AUTOMATIC ) udmEventRecordNum;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;

    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) clrInfoNvmReadResult;
    VAR( Dem_u16_UdmEventStrgIndexType,AUTOMATIC ) verifyLoopNumByCycle;
    VAR( Dem_u08_InternalReturnType,AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType,AUTOMATIC ) retClrRecord;

    verifyLoopNumByCycle = Dem_UdmEventNumForVerifyByCycle;
    retVal = DEM_IRT_OK;

    clrInfoNvmReadResult = Dem_ClrInfoMng_GetNvmReadResult();

    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;
    if( UdmGroupKindIndex < userDefinedMemoryNum )                                          /* [GUD:if]UdmGroupKindIndex */
    {
        udmEventRecordNum = Dem_UdmEventRecordTable[UdmGroupKindIndex].DemEventRecordNum;           /* [GUD]UdmGroupKindIndex */
        for( udmEventStrgIndex = (Dem_u16_UdmEventStrgIndexType)Dem_UdmMngVld_UdmEvtIndexForVerify; udmEventStrgIndex < udmEventRecordNum; udmEventStrgIndex++ )    /* [GUD:for]udmEventStrgIndex */
        {
            if( Dem_UdmMngVld_VerifyLoopCount < verifyLoopNumByCycle )
            {
                Dem_UdmMngVld_VerifyEvent( UdmGroupKindIndex, udmEventStrgIndex, clrInfoNvmReadResult );                /* [GUD]UdmGroupKindIndex *//* [GUD]udmEventStrgIndex */
                Dem_UdmMngVld_VerifyLoopCount = Dem_UdmMngVld_VerifyLoopCount + (Dem_u16_UdmEventStrgIndexType)1U;
            }
            else
            {
                Dem_UdmMngVld_UdmEvtIndexForVerify = udmEventStrgIndex;
                Dem_UdmMngVld_VerifyLoopCount = (Dem_u16_UdmEventStrgIndexType)0U;
                retVal = DEM_IRT_PENDING;
                break;
            }
        }

        if( udmEventStrgIndex >= udmEventRecordNum )
        {
            /* When finished processing one UDM kind records */
            if( UdmGroupKindIndex >= ( userDefinedMemoryNum - (Dem_u16_UdmDemMemKindIndexType)1U ) )
            {
                /* If the last UDM kind has been processed */
                Dem_UdmMngVld_UdmEvtIndexForVerify = udmEventStrgIndex;

                /* Clear not verrified record */
                retClrRecord = Dem_UdmMngVld_ClearAllNotVerifiedRecord();
                if( retClrRecord == DEM_IRT_PENDING )
                {
                    retVal = DEM_IRT_PENDING;
                }
            }
            else
            {
                /* If there is UDM kind after that, initialize Index */
                Dem_UdmMngVld_UdmEvtIndexForVerify = (Dem_u16_UdmEventIndexType)0U;
            }
        }
    }

    return retVal;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Dem_UdmMngVld_VerifyEvent                                */
/* Description   | Verifies Udm Diag Event data.                            */
/* Preconditions | none                                                     */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        The index for Dem_UserDefinedMemoryTable[].       */
/*               | [in] UdmEventStrgIndex :                                 */
/*               |        The udm event index corresponding to the specific */
/*               |         udm event record.                                */
/*               | [in] ClrInfoNvmReadResult :                              */
/*               |        ClearInfo non-volatile memory read result         */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_UdmMngVld_VerifyEvent
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,     /* [PRMCHK:CALLER] */
    VAR( Dem_u16_UdmEventStrgIndexType, AUTOMATIC ) UdmEventStrgIndex,      /* [PRMCHK:CALLER] */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) ClrInfoNvmReadResult
)
{
    P2CONST( Dem_UdmEventRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) udmEventRecordPtr;
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) udmClearId;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindUdmEvent;
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInfoTableIndex;

    recMngCmnKindUdmEvent = Dem_UdmEventNvMStatus[ UdmGroupKindIndex ].DemRecMngCmnKindUdmEvent;    /* [GUDCHK:CALLER]UdmGroupKindIndex */

    udmEventRecordPtr = ( P2CONST( Dem_UdmEventRecordType, TYPEDEF, DEM_VAR_SAVED_ZONE ) )Dem_UdmEventMng_GetEventRecordPtr( UdmGroupKindIndex, UdmEventStrgIndex );    /* [GUDCHK:CALLER]UdmGroupKindIndex *//* [GUDCHK:CALLER]UdmEventStrgIndex */
    /* Check factory default */
    if( udmEventRecordPtr->StatusOfDTC != (Dem_UdsStatusByteType)DEM_DATA_INITIAL_VALUE )
    {
        if( ClrInfoNvmReadResult != DEM_IRT_NG )
        {
            /* Get udm info table index. */
            udmInfoTableIndex = Dem_CfgInfoUdm_GetDemUserDefinedMemoryInfoTableIndex( UdmGroupKindIndex );  /* [GUDCHK:CALLER]UdmGroupKindIndex */

            udmClearId = Dem_ClrInfoMng_GetUdmClearID( udmInfoTableIndex );
            /* Check UdmClearID */
            if( udmEventRecordPtr->UdmClearID == udmClearId )
            {
                Dem_UdmMngVld_VerifiedDiagData( UdmGroupKindIndex, UdmEventStrgIndex, udmEventRecordPtr->UdmFaultIndex, udmEventRecordPtr->ConsistencyIdForFault ); /* [GUDCHK:CALLER]UdmGroupKindIndex *//* [GUDCHK:CALLER]UdmEventStrgIndex */
            }
        }
        else
        {
            /* Resets the status of DTC with default value. */
            Dem_UdmEventMng_InitRecord( UdmGroupKindIndex, UdmEventStrgIndex );
            /* Change Dem_UdmEventNvMStatus */
            Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindUdmEvent, ( Dem_u16_RecordIndexType )UdmEventStrgIndex );
        }
    }
    else
    {
        Dem_UdmEventMng_InitRecord( UdmGroupKindIndex, UdmEventStrgIndex );
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindUdmEvent, ( Dem_u16_RecordIndexType )UdmEventStrgIndex );
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_UdmMngVld_VerifiedDiagData                           */
/* Description   | Make Udm Diag Data verified.                             */
/* Preconditions | none                                                     */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        The index for Dem_UserDefinedMemoryTable[].       */
/*               | [in] UdmEventStrgIndex :                                 */
/*               |        The udm event index corresponding to the specific */
/*               |         udm event record.                                */
/*               | [in] UdmFaultIndex :                                     */
/*               |        The udm fault index corresponding to the specific */
/*               |         udm fault record.                                */
/* Parameters    | [in] ConsistencyIdOfUdmEvent :                           */
/*               |        Consistency id of udm event record.               */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_UdmMngVld_VerifiedDiagData
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,     /* [PRMCHK:CALLER] */
    VAR( Dem_u16_UdmEventStrgIndexType, AUTOMATIC ) UdmEventStrgIndex,      /* [PRMCHK:CALLER] */
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmFaultIndex,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyIdOfUdmEvent
)
{
    VAR( Dem_UdmFaultRecordType, AUTOMATIC ) udmFaultRecord;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFaultRec;
    VAR( boolean, AUTOMATIC ) eventRecordClearFlg;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindUdmEvent;

    eventRecordClearFlg = (boolean)TRUE;

    resultOfGetFaultRec = Dem_UdmFaultMngC_GetRecord( UdmGroupKindIndex, UdmFaultIndex, &udmFaultRecord );              /* [GUDCHK:CALLER]UdmGroupKindIndex *//* [GUD:RET:DEM_IRT_OK] UdmFaultIndex */

    if( resultOfGetFaultRec == DEM_IRT_OK )
    {
        udmEventIndex = Dem_CfgInfoUdm_CnvUdmEventStrgIndexToUdmEventIndex( UdmGroupKindIndex, UdmEventStrgIndex );     /* [GUDCHK:CALLER]UdmGroupKindIndex */

        /* check reration of EventRecord and FaultRecord */
        if( udmEventIndex == udmFaultRecord.UdmEventIndex )
        {
            /* check consistencyId of EventRecord and FaultRecord */
            if( ConsistencyIdOfUdmEvent == udmFaultRecord.ConsistencyIdForFault )
            {
                eventRecordClearFlg = (boolean)FALSE;

                Dem_UdmFFDMng_Verified( udmEventIndex, UdmFaultIndex, UdmGroupKindIndex );              /* [GUDCHK:CALLER]UdmGroupKindIndex *//* [GUD]UdmFaultIndex */

#if ( DEM_TSFF_UDM_SUPPORT == STD_ON ) /*  [FuncSw]    */
                Dem_UdmTSFFDMng_Verified( udmEventIndex, UdmFaultIndex, UdmGroupKindIndex );            /* [GUDCHK:CALLER]UdmGroupKindIndex *//* [GUD]UdmFaultIndex */
#endif /* (DEM_TSFF_UDM_SUPPORT == STD_ON) */
                if( Dem_UdmFaultNvMStatus[ UdmGroupKindIndex ].DemUdmFaultNvMStatusPtr[ UdmFaultIndex ] == DEM_RECMNGCMN_NVM_STS_NOT_VERIFIED ) /* [GUDCHK:CALLER]UdmGroupKindIndex *//* [GUD]UdmFaultIndex *//* [ARYCHK] Dem_UdmFaultRecordTable[UdmGroupKindIndex].DemFaultRecordNum / 1 / UdmFaultIndex *//* [ARYDESC] The registered data size of Dem_UdmFaultNvMStatus[ UdmGroupKindIndex ].DemUdmFaultNvMStatusPtr is the same as Dem_UdmFaultRecordTable[UdmGroupKindIndex].DemFaultRecordNum */
                {
                    Dem_UdmFaultNvMStatus[ UdmGroupKindIndex ].DemUdmFaultNvMStatusPtr[ UdmFaultIndex ] = DEM_RECMNGCMN_NVM_STS_NON_TARGET;     /* [GUDCHK:CALLER]UdmGroupKindIndex *//* [GUD]UdmFaultIndex *//* [ARYCHK] Dem_UdmFaultRecordTable[UdmGroupKindIndex].DemFaultRecordNum / 1 / UdmFaultIndex *//* [ARYDESC] The registered data size of Dem_UdmFaultNvMStatus[ UdmGroupKindIndex ].DemUdmFaultNvMStatusPtr is the same as Dem_UdmFaultRecordTable[UdmGroupKindIndex].DemFaultRecordNum */
                }
            }
        }
    }
    else
    {
        if( UdmFaultIndex == DEM_UDMFAULTINDEX_INITIAL )
        {
            eventRecordClearFlg = (boolean)FALSE;
        }
    }

    if( eventRecordClearFlg == (boolean)TRUE)
    {
        /* Resets the status of DTC with default value. */
        Dem_UdmEventMng_InitRecord( UdmGroupKindIndex, UdmEventStrgIndex );                                         /* [GUDCHK:CALLER]UdmGroupKindIndex */
        /* Change Dem_EventNvMStatus */
        recMngCmnKindUdmEvent = Dem_UdmEventNvMStatus[ UdmGroupKindIndex ].DemRecMngCmnKindUdmEvent;                /* [GUDCHK:CALLER]UdmGroupKindIndex */
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindUdmEvent, ( Dem_u16_RecordIndexType )UdmEventStrgIndex );
    }

    if( Dem_UdmEventNvMStatus[ UdmGroupKindIndex ].DemUdmEventNvMStatusPtr[ UdmEventStrgIndex ] == DEM_RECMNGCMN_NVM_STS_NOT_VERIFIED ) /* [GUDCHK:CALLER]UdmGroupKindIndex *//* [GUDCHK:CALLER]UdmEventStrgIndex *//* [ARYCHK] Dem_UdmEventRecordTable[UdmGroupKindIndex].DemEventRecordNum / 1 / UdmEventStrgIndex *//* [ARYDESC] The registered data size of Dem_UdmEventNvMStatus[ UdmGroupKindIndex ].DemUdmEventNvMStatusPtr is the same as Dem_UdmEventRecordTable[UdmGroupKindIndex].DemEventRecordNum */
    {
        Dem_UdmEventNvMStatus[ UdmGroupKindIndex ].DemUdmEventNvMStatusPtr[ UdmEventStrgIndex ] = DEM_RECMNGCMN_NVM_STS_NON_TARGET;     /* [GUDCHK:CALLER]UdmGroupKindIndex *//* [GUDCHK:CALLER]UdmEventStrgIndex *//* [ARYCHK] Dem_UdmEventRecordTable[UdmGroupKindIndex].DemEventRecordNum / 1 / UdmEventStrgIndex *//* [ARYDESC] The registered data size of Dem_UdmEventNvMStatus[ UdmGroupKindIndex ].DemUdmEventNvMStatusPtr is the same as Dem_UdmEventRecordTable[UdmGroupKindIndex].DemEventRecordNum */
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_UdmMngVld_ClearAllNotVerifiedRecord                  */
/* Description   | Clear not verrified record.                              */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |          DEM_IRT_OK      : Completed.                    */
/*               |          DEM_IRT_PENDING : Continue.                     */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmMngVld_ClearAllNotVerifiedRecord
( void )
{
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) clearRecordKindIndex;
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) clearRecordIndex;
    VAR( Dem_u32_TotalRecordNumType, AUTOMATIC ) restOfProcessableNum;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) clearRecordKindIndexNum;
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) recordFieldIndex;
    VAR( boolean,AUTOMATIC ) loopEnd;
    VAR( Dem_u08_InternalReturnType,AUTOMATIC ) retClearFnc;
    VAR( Dem_u08_InternalReturnType,AUTOMATIC ) retVal;

    clearRecordKindIndex = Dem_UdmMngVld_ClearRecordKind;
    clearRecordIndex = Dem_UdmMngVld_ClearRecordIndex;
    clearRecordKindIndexNum = Dem_UdmRecMngCmnClrRecKindNum;
    restOfProcessableNum = Dem_RecordNumForVerifyByCycle;
    loopEnd = (boolean)FALSE;
    retVal = DEM_IRT_PENDING;

    while( loopEnd == (boolean)FALSE )
    {
        recordFieldIndex = Dem_RecordFieldIndexTableForUdmClrNotVerifiedRecordFunc[clearRecordKindIndex];   /* [GUD]clearRecordKindIndex */
        /*  call clear no verified record function.        */
#ifndef JGXSTACK
        retClearFnc = Dem_UdmClrNotVerifiedRecordFuncTable[clearRecordKindIndex]( recordFieldIndex, &clearRecordIndex, &restOfProcessableNum ); /* [GUD]clearRecordKindIndex */
#else   /* JGXSTACK */
        retClearFnc = Dem_UdmRecMngClrNotVerifiedRecordFunc_ForStack( recordFieldIndex, &clearRecordIndex, &restOfProcessableNum );
#endif  /* JGXSTACK */
        if( retClearFnc == DEM_IRT_OK )
        {
            clearRecordKindIndex = clearRecordKindIndex + (Dem_u16_RecordKindIndexType)1U;
            if( clearRecordKindIndex < clearRecordKindIndexNum )
            {
                clearRecordIndex = (Dem_u16_RecordIndexType)0U;
                if( restOfProcessableNum == (Dem_u32_TotalRecordNumType)0U )
                {
                      Dem_UdmMngVld_ClearRecordKind  =  clearRecordKindIndex;
                      Dem_UdmMngVld_ClearRecordIndex  =  clearRecordIndex;
                      loopEnd = (boolean)TRUE;
                }
            }
            else
            {
                loopEnd = (boolean)TRUE;
                retVal = DEM_IRT_OK;
            }
        }
        /*  continute DataVerify mode or not.   */
        else /* retClearFnc == DEM_IRT_PENDING ) */
        {
            Dem_UdmMngVld_ClearRecordKind  =  clearRecordKindIndex;
            Dem_UdmMngVld_ClearRecordIndex  =  clearRecordIndex;
            loopEnd = (boolean)TRUE;
        }
    }

    return retVal;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
