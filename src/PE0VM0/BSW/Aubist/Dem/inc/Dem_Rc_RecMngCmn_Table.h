/* Dem_Rc_RecMngCmn_Table_h(v5-5-0)                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DEM/Rc_RecMngCmn_Table/HEADER                             */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_RC_RECMNGCMN_TABLE_H
#define DEM_RC_RECMNGCMN_TABLE_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "./Dem_Rc_RecMngCmn.h"
#include "./Dem_Rc_RecMngCmn_rc.h"


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Record kinds sorted by non-volatile write priority */
#define DEM_RECMNGCMN_KIND_CLRINFO          ((Dem_u16_RecordKindIndexType)0U)
#define DEM_RECMNGCMN_KIND_FFD              ((Dem_u16_RecordKindIndexType)1U)
#define DEM_RECMNGCMN_KIND_FAULT            ((Dem_u16_RecordKindIndexType)2U)
#define DEM_RECMNGCMN_KIND_EVENT            ((Dem_u16_RecordKindIndexType)3U)

#define DEM_RECMNGCMN_KIND_MAX              ((Dem_u16_RecordKindIndexType)4U)

#define DEM_RECMNGCMN_CLRRECKIND_NUM        ((Dem_u16_RecordKindIndexType)3U)


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#ifndef JGXSTACK
#else /* JGXSTACK */
FUNC( void, DEM_CODE ) Dem_RecMngCmnInitFnc_ForStack
(
   VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
);

FUNC( void, DEM_CODE ) Dem_RecMngCmnInitSavedZoneFnc_ForStack
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( uint8, AUTOMATIC ) InitType
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_RecMngCmnDataVerifyFnc_ForStack
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
);

FUNC( void, DEM_CODE ) Dem_RecMngCmnSetMirrorDataFnc_ForStack
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
);

FUNC( void, DEM_CODE ) Dem_RecMngCmnExcEnterFnc_ForStack
( void );

FUNC( void, DEM_CODE ) Dem_RecMngCmnExcExitFnc_ForStack
( void );

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_RecMngClrNotVerifiedRecordFunc_ForStack
(
    P2VAR( Dem_u16_RecordIndexType, AUTOMATIC, AUTOMATIC ) ClearRecordIndexPtr,
    P2VAR( Dem_u32_TotalRecordNumType, AUTOMATIC, AUTOMATIC ) RestOfProcessableNumPtr
);
#endif /* JGXSTACK */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CONST_CONFIG
#include <Dem_MemMap.h>

extern CONST( AB_83_ConstV Dem_RecordInitInfoType         ,DEM_CONFIG_DATA )  Dem_RecordInitFuncTable[DEM_RECMNGCMN_KIND_MAX];
extern CONST( AB_83_ConstV Dem_NvMWriteInfoType           ,DEM_CONFIG_DATA )  Dem_NvMWriteInfo[DEM_RECMNGCMN_KIND_MAX];
extern CONST( AB_83_ConstV Dem_u16_RecordFieldIndexType   ,DEM_CONFIG_DATA )  Dem_RecordFieldIndexTableForMemSyncFunc[ DEM_RECMNGCMN_KIND_MAX ];

extern CONST( AB_83_ConstV Dem_u16_RecordKindIndexType    ,DEM_CONFIG_DATA )  Dem_RecMngCmnKindClrInfo;
extern CONST( AB_83_ConstV Dem_u16_RecordKindIndexType    ,DEM_CONFIG_DATA )  Dem_RecMngCmnKindFFD;
extern CONST( AB_83_ConstV Dem_u16_RecordKindIndexType    ,DEM_CONFIG_DATA )  Dem_RecMngCmnKindFault;
extern CONST( AB_83_ConstV Dem_u16_RecordKindIndexType    ,DEM_CONFIG_DATA )  Dem_RecMngCmnKindEvent;

extern CONST( AB_83_ConstV Dem_u16_RecordKindIndexType    ,DEM_CONFIG_DATA )  Dem_RecMngCmnKindMax;

extern CONST( AB_83_ConstV DemClrNotVerifiedRecordFuncPtr    ,DEM_CONFIG_DATA ) Dem_ClrNotVerifiedRecordFuncTable[ DEM_RECMNGCMN_CLRRECKIND_NUM ];

extern CONST( AB_83_ConstV Dem_u16_RecordKindIndexType       ,DEM_CONFIG_DATA ) Dem_RecMngCmnClrRecKindNum;

#define DEM_STOP_SEC_CONST_CONFIG
#include <Dem_MemMap.h>


#endif /* DEM_RC_RECMNGCMN_TABLE_H */

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
/*  Framework          :v2-0-2                                              */
/*  BSW plug-in        :v5-5-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
