/* Dem_Rc_RecMngCmn_Table_h(v5-5-0)                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
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
#define DEM_RECMNGCMN_KIND_UDM_RKDEMUDM_OCCURRENCE1_FFD         ((Dem_u16_RecordKindIndexType)4U)
#define DEM_RECMNGCMN_KIND_UDM_RKDEMUDM_OCCURRENCE2_FFD         ((Dem_u16_RecordKindIndexType)5U)
#define DEM_RECMNGCMN_KIND_UDM_RKDEMUDM_OCCURRENCE2_NM_FFD         ((Dem_u16_RecordKindIndexType)6U)
#define DEM_RECMNGCMN_KIND_UDM_RKDEMUDM_OCCURRENCE3_NM_FFD         ((Dem_u16_RecordKindIndexType)7U)
#define DEM_RECMNGCMN_KIND_UDM_RKDEMUDM_OCCURRENCE7_NM_FFD         ((Dem_u16_RecordKindIndexType)8U)
#define DEM_RECMNGCMN_KIND_UDM_RKDEMUDM_MAINTENANCE1_FFD         ((Dem_u16_RecordKindIndexType)9U)
#define DEM_RECMNGCMN_KIND_UDM_RKDEMUDM_SYSTEMOPERATION2_FFD         ((Dem_u16_RecordKindIndexType)10U)
#define DEM_RECMNGCMN_KIND_UDM_RKDEMUDM_OCCURRENCE1_FAULT       ((Dem_u16_RecordKindIndexType)11U)
#define DEM_RECMNGCMN_KIND_UDM_RKDEMUDM_OCCURRENCE2_FAULT       ((Dem_u16_RecordKindIndexType)12U)
#define DEM_RECMNGCMN_KIND_UDM_RKDEMUDM_OCCURRENCE2_NM_FAULT       ((Dem_u16_RecordKindIndexType)13U)
#define DEM_RECMNGCMN_KIND_UDM_RKDEMUDM_OCCURRENCE3_NM_FAULT       ((Dem_u16_RecordKindIndexType)14U)
#define DEM_RECMNGCMN_KIND_UDM_RKDEMUDM_OCCURRENCE7_NM_FAULT       ((Dem_u16_RecordKindIndexType)15U)
#define DEM_RECMNGCMN_KIND_UDM_RKDEMUDM_MAINTENANCE1_FAULT       ((Dem_u16_RecordKindIndexType)16U)
#define DEM_RECMNGCMN_KIND_UDM_RKDEMUDM_SYSTEMOPERATION2_FAULT       ((Dem_u16_RecordKindIndexType)17U)
#define DEM_RECMNGCMN_KIND_UDM_RKDEMUDM_OCCURRENCE1_EVENT       ((Dem_u16_RecordKindIndexType)18U)
#define DEM_RECMNGCMN_KIND_UDM_RKDEMUDM_OCCURRENCE2_EVENT       ((Dem_u16_RecordKindIndexType)19U)
#define DEM_RECMNGCMN_KIND_UDM_RKDEMUDM_OCCURRENCE2_NM_EVENT       ((Dem_u16_RecordKindIndexType)20U)
#define DEM_RECMNGCMN_KIND_UDM_RKDEMUDM_OCCURRENCE3_NM_EVENT       ((Dem_u16_RecordKindIndexType)21U)
#define DEM_RECMNGCMN_KIND_UDM_RKDEMUDM_OCCURRENCE7_NM_EVENT       ((Dem_u16_RecordKindIndexType)22U)
#define DEM_RECMNGCMN_KIND_UDM_RKDEMUDM_MAINTENANCE1_EVENT       ((Dem_u16_RecordKindIndexType)23U)
#define DEM_RECMNGCMN_KIND_UDM_RKDEMUDM_SYSTEMOPERATION2_EVENT       ((Dem_u16_RecordKindIndexType)24U)

#define DEM_RECMNGCMN_KIND_MAX              ((Dem_u16_RecordKindIndexType)25U)

#define DEM_RECMNGCMN_CLRRECKIND_NUM        ((Dem_u16_RecordKindIndexType)3U)
#define DEM_UDMRECMNGCMN_CLRRECKIND_NUM     ((Dem_u16_RecordKindIndexType)21U)


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

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmRecMngClrNotVerifiedRecordFunc_ForStack
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
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
extern CONST( AB_83_ConstV Dem_u16_RecordFieldIndexType   ,DEM_CONFIG_DATA )  Dem_RecordFieldIndexTableForUdmClrNotVerifiedRecordFunc[ DEM_UDMRECMNGCMN_CLRRECKIND_NUM ];

extern CONST( AB_83_ConstV Dem_u16_RecordKindIndexType    ,DEM_CONFIG_DATA )  Dem_RecMngCmnKindClrInfo;
extern CONST( AB_83_ConstV Dem_u16_RecordKindIndexType    ,DEM_CONFIG_DATA )  Dem_RecMngCmnKindFFD;
extern CONST( AB_83_ConstV Dem_u16_RecordKindIndexType    ,DEM_CONFIG_DATA )  Dem_RecMngCmnKindFault;
extern CONST( AB_83_ConstV Dem_u16_RecordKindIndexType    ,DEM_CONFIG_DATA )  Dem_RecMngCmnKindEvent;

extern CONST( AB_83_ConstV Dem_u16_RecordKindIndexType    ,DEM_CONFIG_DATA )  Dem_RecMngCmnKindMax;

extern CONST( AB_83_ConstV DemClrNotVerifiedRecordFuncPtr    ,DEM_CONFIG_DATA ) Dem_ClrNotVerifiedRecordFuncTable[ DEM_RECMNGCMN_CLRRECKIND_NUM ];
extern CONST( AB_83_ConstV DemUdmClrNotVerifiedRecordFuncPtr ,DEM_CONFIG_DATA ) Dem_UdmClrNotVerifiedRecordFuncTable[ DEM_UDMRECMNGCMN_CLRRECKIND_NUM ];

extern CONST( AB_83_ConstV Dem_u16_RecordKindIndexType       ,DEM_CONFIG_DATA ) Dem_RecMngCmnClrRecKindNum;
extern CONST( AB_83_ConstV Dem_u16_RecordKindIndexType       ,DEM_CONFIG_DATA ) Dem_UdmRecMngCmnClrRecKindNum;

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
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-10-0                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
