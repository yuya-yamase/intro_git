/* Dem_ClrInfoMng_c(v5-5-0)                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/ClrInfoMng/CODE                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../cfg/Dem_NvM_Cfg.h"
#include "../../../inc/Dem_Rc_ClrInfoMng.h"
#include "../../../inc/Dem_Rc_RecMngCmn.h"
#include "../../../inc/Dem_Rc_RecMngCmn_Table.h"
#include "Dem_ClrInfoMng_local.h"

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

static FUNC( void, DEM_CODE ) Dem_ClrInfoMng_ClearRecord
( void );
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
static FUNC( boolean, DEM_CODE ) Dem_ClrInfoMng_StartClearDTC_PrimaryMemory
(
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup
);
static FUNC( void, DEM_CODE ) Dem_ClrInfoMng_InitMirrorMemory
( void );
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

#if ( DEM_CLRINFO_RECORD_PADDING_EXIST == STD_ON )
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
static FUNC( void, DEM_CODE ) Dem_ClrInfoMng_InitPadding
(
    P2VAR( Dem_ClrInfoRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) ClrInfoRecordPtr
);
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */
static FUNC( void, DEM_CODE ) Dem_ClrInfoMng_InitPaddingVolatile
(
    P2VAR( volatile Dem_ClrInfoRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) ClrInfoRecordPtr
);
#endif  /* ( DEM_CLRINFO_RECORD_PADDING_EXIST == STD_ON )   */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
VAR( Dem_u08_RecMngMtxStsType, DEM_VAR_NO_INIT ) Dem_ClrInfoNvMStatus;
VAR( Dem_ClrInfoRecordType, DEM_VAR_NO_INIT ) Dem_ClrInfoMirror;

static VAR( Dem_u08_InternalReturnType, DEM_VAR_NO_INIT ) Dem_ClrInfoMng_ClearResult;

#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */
static VAR( Dem_u08_InternalReturnType, DEM_VAR_NO_INIT ) Dem_ClrInfoMng_NvMReadResult;

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_OFF )
static VAR( volatile Dem_ClrInfoRecordType,    DEM_VAR_NO_INIT ) Dem_ClrInfoRecordVarNoInit;
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_OFF )  */
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
VAR( volatile Dem_ClrInfoRecordType,    DEM_VAR_NO_INIT ) Dem_ClrInfoRecordVarNoInit;
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )  */


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


#define DEM_START_SEC_VAR_SAVED_ZONE
#include <Dem_MemMap.h>

VAR( Dem_ClrInfoRecordType,    DEM_VAR_SAVED_ZONE ) Dem_ClrInfoRecord;

#define DEM_STOP_SEC_VAR_SAVED_ZONE
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_ClrInfoMng_Init                                      */
/* Description   | Get ClearID Value                                        */
/* Preconditions | None                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_ClrInfoMng_Init
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex     /* MISRA DEVIATION */
)
{
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    /* [FuncSw] */
    Dem_ClrInfoMng_InitMirrorMemory();
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */

    Dem_ClrInfoMng_NvMReadResult = DEM_IRT_OK;

    return;
}

/****************************************************************************/
/* Function Name | Dem_ClrInfoMng_InitSavedZone                             */
/* Description   | Initialize savedzone process of ClrInfo.                 */
/* Preconditions |                                                          */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/*               | [in] InitType :                                          */
/*               |          Initialize savedzone type                       */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_ClrInfoMng_InitSavedZone
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    VAR( Dem_SavedZoneInitializeType, AUTOMATIC ) InitType      /* MISRA DEVIATION */
)
{
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindClrInfo;

    Dem_ClrInfoMng_ClearRecord();

    recMngCmnKindClrInfo = Dem_RecMngCmnKindClrInfo;
    Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindClrInfo, (uint16)0U );

    return;
}

/****************************************************************************/
/* Function Name | Dem_ClrInfoMng_Init_AfterNvBlockReadComplete             */
/* Description   | Initialize data function.                                */
/* Preconditions | After Nv Block read complete.                            */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_ClrInfoMng_Init_AfterNvBlockReadComplete
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) clrInfoNvmReadResult;

    /* get read block status.        */
    clrInfoNvmReadResult = Dem_ClrInfoMng_GetNvmReadResult();

    if( clrInfoNvmReadResult == DEM_IRT_OK )
    {
        /*  set VarNoInit data from block data.     */
        Dem_ClrInfoRecordVarNoInit.ClearID      = Dem_ClrInfoRecord.ClearID;
        Dem_ClrInfoRecordVarNoInit.ObdClearID   = Dem_ClrInfoRecord.ObdClearID;
    }
    else
    {
        /*  set VarNoInit data by initial data.     */
        Dem_ClrInfoRecordVarNoInit.ClearID      = DEM_CLRINFO_RECORD_INITIAL;
        Dem_ClrInfoRecordVarNoInit.ObdClearID   = DEM_CLRINFO_RECORD_INITIAL;
    }

#if ( DEM_CLRINFO_RECORD_PADDING_EXIST == STD_ON )  /*  [FuncSw]    */
    /*  initialie padding area.     */
    Dem_ClrInfoMng_InitPaddingVolatile( &Dem_ClrInfoRecordVarNoInit );
#endif  /* ( DEM_CLRINFO_RECORD_PADDING_EXIST == STD_ON )           */

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
    Dem_ClrInfoMng_Init_AfterNvBlockReadComplete_UserDefMem( clrInfoNvmReadResult );
#endif  /*   ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )        */

    return;
}


/****************************************************************************/
/* Function Name | Dem_ClrInfoMng_DataVerify                                */
/* Description   | Data verify function.                                    */
/* Preconditions |                                                          */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |          DEM_IRT_OK      : DataVerify completed.         */
/*               |          DEM_IRT_PENDING : Continue DataVerify.          */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_ClrInfoMng_DataVerify
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex     /* MISRA DEVIATION */
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) clrInfoNvmReadResult;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindClrInfo;

    /* get read block status.        */
    clrInfoNvmReadResult = Dem_ClrInfoMng_GetNvmReadResult();

    if( clrInfoNvmReadResult != DEM_IRT_OK )
    {
        Dem_ClrInfoMng_ClearRecord();

        recMngCmnKindClrInfo = Dem_RecMngCmnKindClrInfo;
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindClrInfo, (Dem_u16_RecordIndexType)0U );
    }
    return DEM_IRT_OK;
}

/****************************************************************************/
/* Function Name | Dem_ClrInfoMng_NvMReadError                              */
/* Description   | Set NvMReadBlock status : Error.                         */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_ClrInfoMng_NvMReadError
( void )
{
    Dem_ClrInfoMng_NvMReadResult = DEM_IRT_NG;

    return;
}


#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_ClrInfoMng_StartClearDTC                             */
/* Description   | Initializes the value of ClrInfo.                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCGroup :                                          */
/*               |        DTCValue specified at the time of Clear.          */
/*               | [in] DTCOrigin :                                         */
/*               |        DEM_DTC_ORIGIN_PRIMARY_MEMORY                     */
/*               |        DEM_DTC_ORIGIN_OBD_RELEVANT_MEMORY                */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_ClrInfoMng_StartClearDTC
(
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
)
{
    VAR( boolean, AUTOMATIC ) update;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindClrInfo;

    Dem_ClrInfoMirror.ClearID = Dem_ClrInfoRecordVarNoInit.ClearID;
    Dem_ClrInfoMirror.ObdClearID = Dem_ClrInfoRecordVarNoInit.ObdClearID;
    Dem_ClrInfoMng_WriteClearIDtoMirror_UserDefMem();

    /* ClearID : Initial 0xFF */
    /*         : MAX     0xFE */
    /*         : MIN     0x00 */
    if ( DTCOrigin == DEM_DTC_ORIGIN_PRIMARY_MEMORY )
    {
        update  =   Dem_ClrInfoMng_StartClearDTC_PrimaryMemory( DTCGroup );
    }
    else
    {
        /*  user defined memory.            */
        update  =   Dem_ClrInfoMng_StartClearDTC_UserDefMem( DTCOrigin );
    }

    /*  NvM Write request.      */
    if ( update == (boolean)TRUE )
    {
        Dem_ClrInfoMng_SetNvClearResult( DEM_IRT_PENDING );

        recMngCmnKindClrInfo = Dem_RecMngCmnKindClrInfo;
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindClrInfo, (Dem_u16_RecordIndexType)0U );
    }
    else
    {
        Dem_ClrInfoMng_ClearResult  =   DEM_IRT_NG; /*  if there's no update request, end of update NvM.        */
    }
    return;
}
#endif  /*   ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )        */
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_ClrInfoMng_StartClearDTC                             */
/* Description   | Initializes the value of ClrInfo.                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCGroup :                                          */
/*               |        DTCValue specified at the time of Clear.          */
/*               | [in] DTCOrigin :                                         */
/*               |        DEM_DTC_ORIGIN_PRIMARY_MEMORY                     */
/*               |        DEM_DTC_ORIGIN_OBD_RELEVANT_MEMORY                */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_ClrInfoMng_StartClearDTC
(
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
)
{
    VAR( boolean, AUTOMATIC ) update;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindClrInfo;

    Dem_ClrInfoMirror.ClearID = Dem_ClrInfoRecordVarNoInit.ClearID;
    Dem_ClrInfoMirror.ObdClearID = Dem_ClrInfoRecordVarNoInit.ObdClearID;

    /* ClearID : Initial 0xFF */
    /*         : MAX     0xFE */
    /*         : MIN     0x00 */
    if ( DTCOrigin == DEM_DTC_ORIGIN_PRIMARY_MEMORY )
    {
        update  =   Dem_ClrInfoMng_StartClearDTC_PrimaryMemory( DTCGroup );
        /*  NvM Write request.      */
        if ( update == (boolean)TRUE )
        {
            Dem_ClrInfoMng_SetNvClearResult( DEM_IRT_PENDING );

            recMngCmnKindClrInfo = Dem_RecMngCmnKindClrInfo;
            Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindClrInfo, (Dem_u16_RecordIndexType)0U );
        }
        else
        {
            Dem_ClrInfoMng_ClearResult  =   DEM_IRT_NG; /*  if there's no update request, end of update NvM.        */
        }
    }

    return;
}
#endif  /*   ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_OFF )        */

/****************************************************************************/
/* Function Name | Dem_ClrInfoMng_StartClearDTC_PrimaryMemory               */
/* Description   | Initializes the value of ClrInfo.                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCGroup :                                          */
/*               |        DTCValue specified at the time of Clear.          */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_ClrInfoMng_StartClearDTC_PrimaryMemory
(
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup
)
{
    VAR( boolean, AUTOMATIC ) update;

    /* ClearID : Initial 0xFF */
    /*         : MAX     0xFE */
    /*         : MIN     0x00 */

    /*  primary memory.                 */
    if( DTCGroup == DEM_DTC_GROUP_ALL_DTCS )
    {
        if( Dem_ClrInfoMirror.ClearID == (Dem_u08_ClearIdType)0U )
        {
            Dem_ClrInfoMirror.ClearID = DEM_CLRINFO_RECORD_MAX_VALUE;
        }
        else
        {
            Dem_ClrInfoMirror.ClearID = Dem_ClrInfoMirror.ClearID - (Dem_u08_ClearIdType)1U;
        }

        if( Dem_ClrInfoMirror.ObdClearID == (Dem_u08_ClearIdType)0U )
        {
            Dem_ClrInfoMirror.ObdClearID = DEM_CLRINFO_RECORD_MAX_VALUE;
        }
        else
        {
            Dem_ClrInfoMirror.ObdClearID = Dem_ClrInfoMirror.ObdClearID - (Dem_u08_ClearIdType)1U;
        }
        update  =   (boolean)TRUE;
    }
    else if( DTCGroup == DEM_DTC_GROUP_EMISSION_REL_DTCS )
    {
        if( Dem_ClrInfoMirror.ObdClearID == (Dem_u08_ClearIdType)0U )
        {
            Dem_ClrInfoMirror.ObdClearID = DEM_CLRINFO_RECORD_MAX_VALUE;
        }
        else
        {
            Dem_ClrInfoMirror.ObdClearID = Dem_ClrInfoMirror.ObdClearID - (Dem_u08_ClearIdType)1U;
        }
        update  =   (boolean)TRUE;
    }
    else
    {
        update  =   (boolean)FALSE;
    }
    return update;
}


/****************************************************************************/
/* Function Name | Dem_ClrInfoMng_SetRecordMirror                           */
/* Description   | Set the Writing RamData.                                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/*               | [in/out] BlockMirrorPtr :                                */
/*               |        Nonvolatile synchronous data information.         */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_ClrInfoMng_SetRecordMirror
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
)
{
    /* Setting to Mirror has already been performed at Dem_ClrInfoMng_StartClearDTC() */
    BlockMirrorPtr->MirrorPtr = &Dem_ClrInfoMirror;

    return;
}


/****************************************************************************/
/* Function Name | Dem_ClrInfoMng_SetNvClearResult                          */
/* Description   | Set Write Status                                         */
/* Preconditions | None                                                     */
/* Parameters    | [in]  Result :                                           */
/*               |        Processing result.                                */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_ClrInfoMng_SetNvClearResult
(
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) Result
)
{
    Dem_ClrInfoMng_ClearResult  =   Result;
    return ;
}


/****************************************************************************/
/* Function Name | Dem_ClrInfoMng_GetNvClearResult                          */
/* Description   | Get Write Status                                         */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK       NvClear OK                       */
/*               |        DEM_IRT_NG       NvClear NG                       */
/*               |        DEM_IRT_PENDING  In NvClear                       */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_ClrInfoMng_GetNvClearResult
( void )
{
    return Dem_ClrInfoMng_ClearResult;
}


/****************************************************************************/
/* Function Name | Dem_ClrInfoMng_UpdateClearID                             */
/* Description   | Update ClearID Value                                     */
/* Preconditions | None                                                     */
/* Parameters    | [in] DTCGroup :                                          */
/*               |        DTCValue specified at the time of Clear.          */
/*               | [in] DTCOrigin :                                         */
/*               |        DEM_DTC_ORIGIN_PRIMARY_MEMORY                     */
/*               |        DEM_DTC_ORIGIN_OBD_RELEVANT_MEMORY                */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_ClrInfoMng_UpdateClearID
(
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
)
{
    if ( DTCOrigin == DEM_DTC_ORIGIN_PRIMARY_MEMORY )
    {
        /*  primary memory.                 */
        if( DTCGroup == DEM_DTC_GROUP_ALL_DTCS )
        {
            Dem_ClrInfoRecordVarNoInit.ClearID  = Dem_ClrInfoMirror.ClearID;
            Dem_ClrInfoRecord.ClearID           = Dem_ClrInfoMirror.ClearID;
        }

        Dem_ClrInfoRecordVarNoInit.ObdClearID   = Dem_ClrInfoMirror.ObdClearID;
        Dem_ClrInfoRecord.ObdClearID            = Dem_ClrInfoMirror.ObdClearID;
    }
    else
    {
        /*  user defined memory.            */
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
        Dem_ClrInfoMng_UpdateClearID_UserDefMem( DTCOrigin );
#endif  /*   ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )        */
    }

    return;
}
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_ClrInfoMng_GetNvClearResult                          */
/* Description   | Get Write Status                                         */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK       NvClear OK                       */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_ClrInfoMng_GetNvClearResult
( void )
{
    return DEM_IRT_OK;
}

/****************************************************************************/
/* Function Name | Dem_ClrInfoMng_UpdateClearID                             */
/* Description   | Update ClearID Value                                     */
/* Preconditions | None                                                     */
/* Parameters    | [in] DTCGroup :                                          */
/*               |        DTCValue specified at the time of Clear.          */
/*               | [in] DTCOrigin :                                         */
/*               |        DEM_DTC_ORIGIN_PRIMARY_MEMORY                     */
/*               |        DEM_DTC_ORIGIN_OBD_RELEVANT_MEMORY                */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_ClrInfoMng_UpdateClearID
(
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
)
{
    /* ClearID : Initial 0xFF */
    /*         : MAX     0xFE */
    /*         : MIN     0x00 */

    if ( DTCOrigin == DEM_DTC_ORIGIN_PRIMARY_MEMORY )
    {
        if( DTCGroup == DEM_DTC_GROUP_ALL_DTCS )
        {
            if( Dem_ClrInfoRecordVarNoInit.ClearID == (Dem_u08_ClearIdType)0U )
            {
                Dem_ClrInfoRecordVarNoInit.ClearID = DEM_CLRINFO_RECORD_MAX_VALUE;
            }
            else
            {
                Dem_ClrInfoRecordVarNoInit.ClearID = Dem_ClrInfoRecordVarNoInit.ClearID - (Dem_u08_ClearIdType)1U;
            }
        }

        if( Dem_ClrInfoRecordVarNoInit.ObdClearID == (Dem_u08_ClearIdType)0U )
        {
            Dem_ClrInfoRecordVarNoInit.ObdClearID = DEM_CLRINFO_RECORD_MAX_VALUE;
        }
        else
        {
            Dem_ClrInfoRecordVarNoInit.ObdClearID = Dem_ClrInfoRecordVarNoInit.ObdClearID - (Dem_u08_ClearIdType)1U;
        }

        /*  update Dem_ClrInfoRecord(SAVED_ZONE) area.      */
        Dem_ClrInfoRecord.ClearID       =   Dem_ClrInfoRecordVarNoInit.ClearID;
        Dem_ClrInfoRecord.ObdClearID    =   Dem_ClrInfoRecordVarNoInit.ObdClearID;
    }
    else
    {
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
        Dem_ClrInfoMng_UpdateClearID_UserDefMem( DTCOrigin );
#endif  /*   ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )        */
    }
    return;
}

#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_OFF- */

/****************************************************************************/
/* Function Name | Dem_ClrInfoMng_GetClearID                                */
/* Description   | Get ClearID Value                                        */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Dem_u08_ClearIdType  ClearID                             */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_ClearIdType, DEM_CODE ) Dem_ClrInfoMng_GetClearID
( void )
{
    return Dem_ClrInfoRecordVarNoInit.ClearID;
}

/****************************************************************************/
/* Function Name | Dem_ClrInfoMng_GetObdClearID                             */
/* Description   | Get ClearID Value                                        */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Dem_u08_ClearIdType  ClearID                             */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_ClearIdType, DEM_CODE ) Dem_ClrInfoMng_GetObdClearID
( void )
{
    return Dem_ClrInfoRecordVarNoInit.ObdClearID;
}

/****************************************************************************/
/* Function Name | Dem_ClrInfoMng_GetNvmReadResult                          */
/* Description   | Get ClearID Value                                        */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Dem_u08_InternalReturnType  ClrInfo Record Check Result  */
/*               |        DEM_IRT_OK       NvMRead OK                       */
/*               |        DEM_IRT_NG       NvMRead NG                       */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_ClrInfoMng_GetNvmReadResult
( void )
{
    return Dem_ClrInfoMng_NvMReadResult;
}


/****************************************************************************/
/* Function Name | Dem_ClrInfoMng_ClearRecord                               */
/* Description   | Initialize data function.                                */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_ClrInfoMng_ClearRecord
( void )
{
    Dem_ClrInfoRecord.ClearID = DEM_CLRINFO_RECORD_INITIAL;
    Dem_ClrInfoRecord.ObdClearID = DEM_CLRINFO_RECORD_INITIAL;

    Dem_ClrInfoRecordVarNoInit.ClearID      = DEM_CLRINFO_RECORD_INITIAL;
    Dem_ClrInfoRecordVarNoInit.ObdClearID   = DEM_CLRINFO_RECORD_INITIAL;

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
    Dem_ClrInfoMng_ClearRecord_UserDefMem();
#endif  /*   ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )        */

    return;
}


#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_ClrInfoMng_InitMirrorMemory                          */
/* Description   | Initialize the Mirror Memory.                            */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_ClrInfoMng_InitMirrorMemory
( void )
{

    /* Initializes the temporary permanent memory. */
    Dem_ClrInfoMirror.ClearID       = DEM_CLRINFO_RECORD_INITIAL;
    Dem_ClrInfoMirror.ObdClearID    = DEM_CLRINFO_RECORD_INITIAL;

#if ( DEM_CLRINFO_RECORD_PADDING_EXIST == STD_ON )  /*  [FuncSw]    */
    Dem_ClrInfoMng_InitPadding( &Dem_ClrInfoMirror );
#endif  /* ( DEM_CLRINFO_RECORD_PADDING_EXIST == STD_ON )           */

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
    Dem_ClrInfoMng_InitMirrorMemory_UserDefMem();
#endif  /*   ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )        */

    return;
}

#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */

#if ( DEM_CLRINFO_RECORD_PADDING_EXIST == STD_ON )
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_ClrInfoMng_InitPadding                               */
/* Description   | Initializes the record padding data.                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] DtrRecordPtr    :                                   */
/*               |       The pointer of the record.                         */
/*               |          &Dem_ClrInfoMirror -DEM_VAR_NO_INIT-            */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_ClrInfoMng_InitPadding
(
    P2VAR( Dem_ClrInfoRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) ClrInfoRecordPtr
)
{
    VAR( Dem_u16_PaddingIndexType, AUTOMATIC ) paddingSize;
    VAR( Dem_u16_PaddingIndexType, AUTOMATIC ) paddingIndex;

    paddingSize = Dem_ClrInfoRecordBlockPaddingSize;

    for( paddingIndex = (Dem_u16_PaddingIndexType)0U; paddingIndex < paddingSize; paddingIndex++ )  /* [GUD:for]paddingIndex */
    {
        ClrInfoRecordPtr->Reserve[paddingIndex] = (uint8)0U;                                        /* [GUD]paddingIndex */
    }
    return ;
}
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */

/****************************************************************************/
/* Function Name | Dem_ClrInfoMng_InitPaddingVolatile                       */
/* Description   | Initializes the record padding data.                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] DtrRecordPtr    :                                   */
/*               |       The pointer of the record.                         */
/*               |          &Dem_ClrInfoRecordVarNoInit -DEM_VAR_NO_INIT-   */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_ClrInfoMng_InitPaddingVolatile
(
    P2VAR( volatile Dem_ClrInfoRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) ClrInfoRecordPtr
)
{
    VAR( Dem_u16_PaddingIndexType, AUTOMATIC ) paddingSize;
    VAR( Dem_u16_PaddingIndexType, AUTOMATIC ) paddingIndex;

    paddingSize = Dem_ClrInfoRecordBlockPaddingSize;

    for( paddingIndex = (Dem_u16_PaddingIndexType)0U; paddingIndex < paddingSize; paddingIndex++ )  /* [GUD:for]paddingIndex */
    {
        ClrInfoRecordPtr->Reserve[paddingIndex] = (uint8)0U;                                        /* [GUD]paddingIndex */
    }
    return ;
}
#endif  /* ( DEM_CLRINFO_RECORD_PADDING_EXIST == STD_ON )   */

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_ClrInfoMng_GetEventIdFromRecordData                  */
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
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_ClrInfoMng_GetEventIdFromRecordData
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) RecordIndex,      /* MISRA DEVIATION */
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr   /* MISRA DEVIATION */
)
{
    /*  this record has no event id.        */
    return DEM_IRT_NG;
}
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */

/****************************************************************************/
/* Function Name | Dem_ClrInfoMng_RefreshRAM                                */
/* Description   | Refresh RAM  - ClrInfoMng                                */
/* Preconditions | None                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | Called from Dem_MainFunction                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_ClrInfoMng_RefreshRAM
( void )
{
    VAR( volatile Dem_u08_ClearIdType, AUTOMATIC )                      u8_dummy;      /*  for store GlobalVariable data    */
    P2VAR( volatile Dem_u08_ClearIdType, AUTOMATIC, DEM_VAR_NO_INIT )   u8_dummyPtr;   /*  for GlobalVariable address       */

    /*  set GlobalVariable pointer  */
    u8_dummyPtr      = &Dem_ClrInfoRecordVarNoInit.ClearID;

    /* Exclusion is not necessary   */
    u8_dummy         = *u8_dummyPtr;          /*  read GlobalVariable data    */
    *u8_dummyPtr     = u8_dummy;              /*  rewrite GlobalVariable data */

    /*  set GlobalVariable pointer  */
    u8_dummyPtr      = &Dem_ClrInfoRecordVarNoInit.ObdClearID;

    /* Exclusion is not necessary   */
    u8_dummy         = *u8_dummyPtr;          /*  read GlobalVariable data    */
    *u8_dummyPtr     = u8_dummy;              /*  rewrite GlobalVariable data */

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
    Dem_ClrInfoMng_RefreshRAM_UserDefMem();
#endif  /*   ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )        */

    return ;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
