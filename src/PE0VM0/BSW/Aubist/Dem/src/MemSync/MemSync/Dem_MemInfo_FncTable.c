/* Dem_MemInfo_FncTable_c(v5-6-0)                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DEM/MemInfo_FncTable/CODE                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "Dem_MemInfo_FncTable.h"


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

/* Data type processing function table */
CONST( AB_83_ConstV Dem_MemInfoRecordDataType, DEM_CONFIG_DATA ) Dem_MemBlockRecordInfo_FuncTable[DEM_MM_NVM_REC_KIND_NUM] =
{
    {   &Dem_EventMng_GetEventIdFromRecordData                                        },
    {   &Dem_FaultMng_GetEventIdFromRecordData                                        },
    {   &Dem_FFDMng_GetEventIdFromRecordData                                          },
    {   &Dem_ClrInfoMng_GetEventIdFromRecordData                                      }
};

CONST( AB_83_ConstV Dem_u16_RecordFieldIndexType  ,DEM_CONFIG_DATA )  Dem_RecordFieldIndexTableForMemBlockRecordInfoFunc[ DEM_MM_NVM_REC_KIND_NUM ] =
{
    DEM_RECORD_ONE_FIELD,
    DEM_RECORD_ONE_FIELD,
    DEM_RECORD_ONE_FIELD,
    DEM_RECORD_ONE_FIELD
};

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
/* Function Name | Dem_GetEventIdFromRecordDataFnc_ForStack                 */
/* Description   | DemGetEventIdFromRecordDataFnc for measuring stack size. */
/* Preconditions | none                                                     */
/* Parameters    | [in]  RecordFieldIndex :                                 */
/*               | [in]  RecordIndex  :                                     */
/*               | [in]  EventIdPtr  :                                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_GetEventIdFromRecordDataFnc_ForStack
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) RecordIndex,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = Dem_EventMng_GetEventIdFromRecordData( RecordFieldIndex, RecordIndex, EventIdPtr );
    retVal = Dem_FaultMng_GetEventIdFromRecordData( RecordFieldIndex, RecordIndex, EventIdPtr );
    retVal = Dem_FFDMng_GetEventIdFromRecordData( RecordFieldIndex, RecordIndex, EventIdPtr );
    retVal = Dem_ClrInfoMng_GetEventIdFromRecordData( RecordFieldIndex, RecordIndex, EventIdPtr );

    return retVal;
}
#endif /* JGXSTACK */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-10-0                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
