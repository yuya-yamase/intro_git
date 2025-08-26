/* Dem_RecMngCmn_Table_c(v5-5-0)                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DEM/RecMngCmn_Table/CODE                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../../../inc/Dem_Rc_RecMngCmn_Table.h"


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CONST_CONFIG
#include <Dem_MemMap.h>

CONST( AB_83_ConstV Dem_RecordInitInfoType         ,DEM_CONFIG_DATA )  Dem_RecordInitFuncTable[DEM_RECMNGCMN_KIND_MAX] =
{
    {  &Dem_ClrInfoMng_Init,     &Dem_ClrInfoMng_InitSavedZone,     &Dem_ClrInfoMng_DataVerify      },
    {  &Dem_FFDMng_Init,         &Dem_FFDMng_InitSavedZone,         &Dem_FFDMng_DataVerify          },
    {  &Dem_FaultMng_Init,       &Dem_FaultMng_InitSavedZone,       &Dem_FaultMng_DataVerify        },
    {  &Dem_EventMng_Init,       &Dem_EventMng_InitSavedZone,       &Dem_EventMng_DataVerify        }
};

/* Data type processing function table */
CONST( AB_83_ConstV Dem_NvMWriteInfoType           ,DEM_CONFIG_DATA )  Dem_NvMWriteInfo[DEM_RECMNGCMN_KIND_MAX] =
{
    {    &Dem_ClrInfoMng_SetRecordMirror,           &Dem_RecMngCmn_ExclusiveDummy,       &Dem_RecMngCmn_ExclusiveDummy,      &Dem_ClrInfoNvMStatus,       1U,                          DEM_CLRINFO_RECORD_NVBLOCK_SIZE,  1U,                                  DEM_MM_NVM_REC_KIND_CLRINFO     },
    {    &Dem_FFDMng_SetRecordMirror,               &Dem_RecMngCmn_ExclusiveDummy,       &Dem_RecMngCmn_ExclusiveDummy,      &Dem_FFDNvMStatus[0],        DEM_FFD_RECORD_LIST_NUM,     DEM_FFD_RECORD_NVBLOCK_SIZE,      DEM_FREEZE_FRAME_DATA_BLOCK_NUM,     DEM_MM_NVM_REC_KIND_FFD         },
    {    &Dem_FaultMng_SetRecordMirror,             &Dem_RecMngCmn_ExclusiveDummy,       &Dem_RecMngCmn_ExclusiveDummy,      &Dem_FaultNvMStatus[0],      DEM_FAIL_RECORD_LIST_NUM,    DEM_FAIL_RECORD_NVBLOCK_SIZE,     1U,                                  DEM_MM_NVM_REC_KIND_FLT         },
    {    &Dem_EventMng_SetRecordMirror,             &Dem_RecMngCmn_ExclusiveDummy,       &Dem_RecMngCmn_ExclusiveDummy,      &Dem_EventNvMStatus[0],      DEM_EVENT_RECORD_LIST_NUM,   DEM_EVENT_RECORD_NVBLOCK_SIZE,    1U,                                  DEM_MM_NVM_REC_KIND_EVT         }
};

CONST( AB_83_ConstV Dem_u16_RecordFieldIndexType   ,DEM_CONFIG_DATA )  Dem_RecordFieldIndexTableForMemSyncFunc[ DEM_RECMNGCMN_KIND_MAX ] =
{
    DEM_RECORD_ONE_FIELD,
    DEM_RECORD_ONE_FIELD,
    DEM_RECORD_ONE_FIELD,
    DEM_RECORD_ONE_FIELD
};

CONST( AB_83_ConstV Dem_u16_RecordKindIndexType    ,DEM_CONFIG_DATA )  Dem_RecMngCmnKindClrInfo = DEM_RECMNGCMN_KIND_CLRINFO;
CONST( AB_83_ConstV Dem_u16_RecordKindIndexType    ,DEM_CONFIG_DATA )  Dem_RecMngCmnKindFFD     = DEM_RECMNGCMN_KIND_FFD;
CONST( AB_83_ConstV Dem_u16_RecordKindIndexType    ,DEM_CONFIG_DATA )  Dem_RecMngCmnKindFault   = DEM_RECMNGCMN_KIND_FAULT;
CONST( AB_83_ConstV Dem_u16_RecordKindIndexType    ,DEM_CONFIG_DATA )  Dem_RecMngCmnKindEvent   = DEM_RECMNGCMN_KIND_EVENT;

CONST( AB_83_ConstV Dem_u16_RecordKindIndexType    ,DEM_CONFIG_DATA )  Dem_RecMngCmnKindMax     = DEM_RECMNGCMN_KIND_MAX;

CONST( AB_83_ConstV DemClrNotVerifiedRecordFuncPtr    ,DEM_CONFIG_DATA ) Dem_ClrNotVerifiedRecordFuncTable[ DEM_RECMNGCMN_CLRRECKIND_NUM ] =
{
    &Dem_FFDMng_ClearAllNotVerifiedRecord,
    &Dem_FaultMng_ClearAllNotVerifiedRecord,
    &Dem_EventMng_ClearAllNotVerifiedRecord
};

CONST( AB_83_ConstV Dem_u16_RecordKindIndexType       ,DEM_CONFIG_DATA ) Dem_RecMngCmnClrRecKindNum    = DEM_RECMNGCMN_CLRRECKIND_NUM;

#define DEM_STOP_SEC_CONST_CONFIG
#include <Dem_MemMap.h>


#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/

#ifndef JGXSTACK
#else /* JGXSTACK */
/****************************************************************************/
/* Function Name | Dem_RecMngCmnInitFnc_ForStack                            */
/* Description   | DemRecMngCmnInitFncForStack for measuring stack size.    */
/* Preconditions | none                                                     */
/* Parameters    | [in]  RecordFieldIndex :                                 */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_RecMngCmnInitFnc_ForStack
( 
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
)
{
    Dem_ClrInfoMng_Init( RecordFieldIndex );
    Dem_FFDMng_Init( RecordFieldIndex );
    Dem_FaultMng_Init( RecordFieldIndex );
    Dem_EventMng_Init( RecordFieldIndex );

    return;
}

/****************************************************************************/
/* Function Name | Dem_RecMngCmnInitSavedZoneFnc_ForStack                   */
/* Description   | -                                                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex                                    */
/*               | [in] InitType                                            */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_RecMngCmnInitSavedZoneFnc_ForStack
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( uint8, AUTOMATIC ) InitType
)
{
    Dem_ClrInfoMng_InitSavedZone( RecordFieldIndex, InitType );
    Dem_FFDMng_InitSavedZone( RecordFieldIndex, InitType );
    Dem_FaultMng_InitSavedZone( RecordFieldIndex, InitType );
    Dem_EventMng_InitSavedZone( RecordFieldIndex, InitType );

    return;
}

/****************************************************************************/
/* Function Name | Dem_RecMngCmnDataVerifyFnc_ForStack                      */
/* Description   | DemRecMngCmnDataVerifyFncForStack for measuring stack    */
/*               | size.                                                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex                                    */
/* Return Value  | DEM_IRT_OK                                               */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_RecMngCmnDataVerifyFnc_ForStack
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = Dem_ClrInfoMng_DataVerify( RecordFieldIndex );
    retVal = Dem_FFDMng_DataVerify( RecordFieldIndex );
    retVal = Dem_FaultMng_DataVerify( RecordFieldIndex );
    retVal = Dem_EventMng_DataVerify( RecordFieldIndex );

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_RecMngCmnSetMirrorDataFnc_ForStack                   */
/* Description   | DemRecMngCmnSetMirrorDataFnc for measuring stack size.   */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               | [in/out] BlockMirrorPtr :                                */
/*               |        Nonvolatile synchronous data information.         */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_RecMngCmnSetMirrorDataFnc_ForStack
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
)
{
    Dem_ClrInfoMng_SetRecordMirror( RecordFieldIndex, BlockMirrorPtr );
    Dem_FFDMng_SetRecordMirror( RecordFieldIndex, BlockMirrorPtr );
    Dem_FaultMng_SetRecordMirror( RecordFieldIndex, BlockMirrorPtr );
    Dem_EventMng_SetRecordMirror( RecordFieldIndex, BlockMirrorPtr );

    return;
}

/****************************************************************************/
/* Function Name | Dem_RecMngCmnExcEnterFnc_ForStack                        */
/* Description   | DemRecMngCmnExcEnterFnc for measuring stack size.        */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_RecMngCmnExcEnterFnc_ForStack
(
    void
)
{
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();

    return;
}

/****************************************************************************/
/* Function Name | Dem_RecMngCmnExcExitFnc_ForStack                         */
/* Description   | DemRecMngCmnExcExitFnc for measuring stack size.         */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_RecMngCmnExcExitFnc_ForStack
(
    void
)
{
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();

    return;
}

/****************************************************************************/
/* Function Name | Dem_RecMngClrNotVerifiedRecordFunc_ForStack              */
/* Description   | -                                                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] ClearRecordIndexPtr                                 */
/*               | [out] RestOfProcessableNumPtr                            */
/* Return Value  | DEM_IRT_OK                                               */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_RecMngClrNotVerifiedRecordFunc_ForStack
(
    P2VAR( Dem_u16_RecordIndexType, AUTOMATIC, AUTOMATIC ) ClearRecordIndexPtr,
    P2VAR( Dem_u32_TotalRecordNumType, AUTOMATIC, AUTOMATIC ) RestOfProcessableNumPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = Dem_FFDMng_ClearAllNotVerifiedRecord( ClearRecordIndexPtr, RestOfProcessableNumPtr );
    retVal = Dem_FaultMng_ClearAllNotVerifiedRecord( ClearRecordIndexPtr, RestOfProcessableNumPtr );
    retVal = Dem_EventMng_ClearAllNotVerifiedRecord( ClearRecordIndexPtr, RestOfProcessableNumPtr );

    return retVal;
}

#endif /* JGXSTACK */

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

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
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-3-z0003                                        */
/*  BSW plug-in        :v5-5-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
