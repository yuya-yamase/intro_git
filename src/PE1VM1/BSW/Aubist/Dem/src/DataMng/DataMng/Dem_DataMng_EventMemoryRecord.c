/* Dem_DataMng_EventMemoryRecord_c(v5-10-0)                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Dem_DataMng_EventMemoryRecord_c/CODE                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_Rc_DataMng.h"
#include "../../../inc/Dem_Utl.h"
#include "Dem_DataMng_local.h"

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


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

VAR( volatile Dem_EventMemoryRecordType, DEM_VAR_NO_INIT ) Dem_EventMemoryRecordList;

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_DataMngC_InitEvtMemRecData                           */
/* Description   | Initializes the specified record of event memory record  */
/*               | list.                                                    */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataMngC_InitEvtMemRecData
(
    P2VAR( Dem_EventMemoryRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) EventMemoryRecordPtr
)
{
    /* Sets initial values to the specified event memory record. */
    EventMemoryRecordPtr->NumberOfFreezeFrameRecords    = DEM_NUMOFFFREC_INITIAL;
#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
    EventMemoryRecordPtr->NumberOfObdFreezeFrameRecords = DEM_NUMOFFFREC_INITIAL;
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */
    EventMemoryRecordPtr->NumberOfEventMemoryEntries    = DEM_NUMOFEVTMEMENT_INITIAL;
    EventMemoryRecordPtr->NumberOfConfirmedDTCs         = DEM_NUMOFEVTMEMENT_INITIAL;
    EventMemoryRecordPtr->NumberOfObdMILDTCs            = DEM_NUMOFEVTMEMENT_INITIAL;

    return;
}


/****************************************************************************/
/* Function Name | Dem_DataMngC_GetEventMemoryRecord                        */
/* Description   | Gets the EventMemory record from the EventMemory record- */
/*               |  list                                                    */
/*               |  (for Dem_DataCtl subunit)                               */
/* Preconditions | none                                                     */
/* Parameters    | [out] EventMemoryRecordPtr :                             */
/*               |        The pointer of the EventMemory record             */
/*               |         &Dem_TmpEventMemoryEntry.EventMemoryRecordList   */
/*               |         AUTOMATIC                                        */
/* Return Value  | void                                                     */
/*               |                                                          */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataMngC_GetEventMemoryRecord
(
    P2VAR( Dem_EventMemoryRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) EventMemoryRecordPtr
)
{
    EventMemoryRecordPtr->NumberOfFreezeFrameRecords    = Dem_EventMemoryRecordList.NumberOfFreezeFrameRecords;
#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
    EventMemoryRecordPtr->NumberOfObdFreezeFrameRecords = Dem_EventMemoryRecordList.NumberOfObdFreezeFrameRecords;
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */
    EventMemoryRecordPtr->NumberOfEventMemoryEntries    = Dem_EventMemoryRecordList.NumberOfEventMemoryEntries;
    EventMemoryRecordPtr->NumberOfConfirmedDTCs         = Dem_EventMemoryRecordList.NumberOfConfirmedDTCs;
    EventMemoryRecordPtr->NumberOfObdMILDTCs            = Dem_EventMemoryRecordList.NumberOfObdMILDTCs;

    return ;
}

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
#if ( DEM_DTCSTOREDDATA_DEMINTERNAL_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DataMngC_GetNumberOfConfirmedDTCs                    */
/* Description   | Gets NumberOfConfirmedDTCs                               */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_OrderIndexType                                   */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_OrderIndexType, DEM_CODE ) Dem_DataMngC_GetNumberOfConfirmedDTCs
( void )
{
    return Dem_EventMemoryRecordList.NumberOfConfirmedDTCs;
}
#endif  /* ( DEM_DTCSTOREDDATA_DEMINTERNAL_SUPPORT == STD_ON )     */
#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON )     */

#if ( DEM_WWH_OBD_SUPPORT == STD_ON )
#if ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DataMngC_GetNumberOfObdMILDTCs                       */
/* Description   | Gets NumberOfObdMILDTCs                                  */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_OrderIndexType                                   */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_DataMngC_GetNumberOfConfirmedDTCs. */
/****************************************************************************/
FUNC( Dem_u08_OrderIndexType, DEM_CODE ) Dem_DataMngC_GetNumberOfObdMILDTCs
( void )
{
    return Dem_EventMemoryRecordList.NumberOfObdMILDTCs;
}

/****************************************************************************/
/* Function Name | Dem_DataMngC_IncrementNumberOfObdMILDTCs                 */
/* Description   | Gets NumberOfObdMILDTCs                                  */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_OrderIndexType                                   */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataMngC_IncrementNumberOfObdMILDTCs
( void )
{
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) numberOfObdMILDTCs;

    numberOfObdMILDTCs  =   Dem_EventMemoryRecordList.NumberOfObdMILDTCs;
    Dem_EventMemoryRecordList.NumberOfObdMILDTCs    =   numberOfObdMILDTCs + (Dem_u08_OrderIndexType)1U;

    return ;
}
#endif  /* ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )     */
#endif  /* ( DEM_WWH_OBD_SUPPORT == STD_ON )     */

/****************************************************************************/
/* Function Name | Dem_DataMngC_SetEventMemoryRecord                        */
/* Description   | Sets the EventMemory record to the EventMemory record l- */
/*               | ist (for Dem_DataCtl subunit)                            */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventMemoryRecordPtr :                              */
/*               |        The pointer of the EventMemory record             */
/*               |         &Dem_TmpEventMemoryEntry.EventMemoryRecordList   */
/*               |         AUTOMATIC                                        */
/* Return Value  | void                                                     */
/*               |                                                          */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataMngC_SetEventMemoryRecord
(
    P2CONST( Dem_EventMemoryRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) EventMemoryRecordPtr
)
{
    Dem_EventMemoryRecordList.NumberOfFreezeFrameRecords    = EventMemoryRecordPtr->NumberOfFreezeFrameRecords;
#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
    Dem_EventMemoryRecordList.NumberOfObdFreezeFrameRecords = EventMemoryRecordPtr->NumberOfObdFreezeFrameRecords;
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */
    Dem_EventMemoryRecordList.NumberOfEventMemoryEntries    = EventMemoryRecordPtr->NumberOfEventMemoryEntries;
    Dem_EventMemoryRecordList.NumberOfConfirmedDTCs         = EventMemoryRecordPtr->NumberOfConfirmedDTCs;
    Dem_EventMemoryRecordList.NumberOfObdMILDTCs            = EventMemoryRecordPtr->NumberOfObdMILDTCs;

    return ;
}

/****************************************************************************/
/* Function Name | Dem_DataMngC_CopyEventMemoryRecord                       */
/* Description   | copy the specified event record.                         */
/* Preconditions | none                                                     */
/* Parameters    | [out] DestEventMemoryRecordPtr :                         */
/*               | [in]  SrcEventMemoryRecordPtr :                          */
/* Return Value  | void                                                     */
/*               |                                                          */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-7-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataMngC_CopyEventMemoryRecord
(
    P2VAR( Dem_EventMemoryRecordType, AUTOMATIC, AUTOMATIC ) DestEventMemoryRecordPtr,
    P2CONST( Dem_EventMemoryRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) SrcEventMemoryRecordPtr
)
{
    DestEventMemoryRecordPtr->NumberOfFreezeFrameRecords    = SrcEventMemoryRecordPtr->NumberOfFreezeFrameRecords;
#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
    DestEventMemoryRecordPtr->NumberOfObdFreezeFrameRecords = SrcEventMemoryRecordPtr->NumberOfObdFreezeFrameRecords;
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */
    DestEventMemoryRecordPtr->NumberOfEventMemoryEntries    = SrcEventMemoryRecordPtr->NumberOfEventMemoryEntries;
    DestEventMemoryRecordPtr->NumberOfConfirmedDTCs         = SrcEventMemoryRecordPtr->NumberOfConfirmedDTCs;
    DestEventMemoryRecordPtr->NumberOfObdMILDTCs            = SrcEventMemoryRecordPtr->NumberOfObdMILDTCs;

    return ;
}


/****************************************************************************/
/* Function Name | Dem_DataMng_RefreshRAM                                   */
/* Description   | Refresh RAM  - DataMng                                   */
/* Preconditions | None                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | Called from Dem_MainFunction                             */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataMng_RefreshRAM
( void )
{
    VAR( volatile Dem_u08_FFDIndexType, AUTOMATIC )                     ffd_dummy;     /*  for store GlobalVariable data    */
    P2VAR( volatile Dem_u08_FFDIndexType, AUTOMATIC, DEM_VAR_NO_INIT )  ffd_dummyPtr;  /*  for GlobalVariable address       */
    VAR( volatile Dem_u08_OrderIndexType, AUTOMATIC )                      order_dummy;      /*  for store GlobalVariable data    */
    P2VAR( volatile Dem_u08_OrderIndexType, AUTOMATIC, DEM_VAR_NO_INIT )   order_dummyPtr;   /*  for GlobalVariable address       */

    /*  set GlobalVariable pointer  */
    ffd_dummyPtr     = &Dem_EventMemoryRecordList.NumberOfFreezeFrameRecords;

    /* Exclusion is not necessary   */
    ffd_dummy        = *ffd_dummyPtr; /*  read GlobalVariable data    */
    *ffd_dummyPtr    = ffd_dummy;     /*  rewrite GlobalVariable data */

#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
    /*  set GlobalVariable pointer  */
    ffd_dummyPtr     = &Dem_EventMemoryRecordList.NumberOfObdFreezeFrameRecords;

    /* Exclusion is not necessary   */
    ffd_dummy        = *ffd_dummyPtr; /*  read GlobalVariable data    */
    *ffd_dummyPtr    = ffd_dummy;     /*  rewrite GlobalVariable data */
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */

    /*  set GlobalVariable pointer  */
    order_dummyPtr     = &Dem_EventMemoryRecordList.NumberOfEventMemoryEntries;

    /* Exclusion is not necessary   */
    order_dummy        = *order_dummyPtr; /*  read GlobalVariable data    */
    *order_dummyPtr    = order_dummy;     /*  rewrite GlobalVariable data */

    /*  set GlobalVariable pointer  */
    order_dummyPtr     = &Dem_EventMemoryRecordList.NumberOfConfirmedDTCs;

    /* Exclusion is not necessary   */
    order_dummy        = *order_dummyPtr; /*  read GlobalVariable data    */
    *order_dummyPtr    = order_dummy;     /*  rewrite GlobalVariable data */

    /*  set GlobalVariable pointer  */
    order_dummyPtr     = &Dem_EventMemoryRecordList.NumberOfObdMILDTCs;

    /* Exclusion is not necessary   */
    order_dummy        = *order_dummyPtr; /*  read GlobalVariable data    */
    *order_dummyPtr    = order_dummy;     /*  rewrite GlobalVariable data */

    return ;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-03-19                                              */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/*  v5-7-0         :2024-05-29                                              */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
