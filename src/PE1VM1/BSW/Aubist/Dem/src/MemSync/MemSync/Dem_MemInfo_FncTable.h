/* Dem_MemInfo_FncTable_h(v5-5-0)                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DEM/MemInfo_FncTable/HEADER                               */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_MEMINFO_FNCTABLE_H
#define DEM_MEMINFO_FNCTABLE_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../inc/Dem_Rc_RecMngCmn_rc.h"
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
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#ifndef JGXSTACK
#else /* JGXSTACK */
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_GetEventIdFromRecordDataFnc_ForStack
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) RecordIndex,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr
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

extern CONST( AB_83_ConstV Dem_MemInfoRecordDataType     ,DEM_CONFIG_DATA )  Dem_MemBlockRecordInfo_FuncTable[DEM_MM_NVM_REC_KIND_NUM];
extern CONST( AB_83_ConstV Dem_u16_RecordFieldIndexType  ,DEM_CONFIG_DATA )  Dem_RecordFieldIndexTableForMemBlockRecordInfoFunc[ DEM_MM_NVM_REC_KIND_NUM ];

#define DEM_STOP_SEC_CONST_CONFIG
#include <Dem_MemMap.h>


#endif /* DEM_MEMINFO_FNCTABLE_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-10-0                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
