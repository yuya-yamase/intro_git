/* Dem_MemSync_c(v5-5-0)                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/MemSync/CODE                                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_MM_Cfg.h"
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_Md_ModeMng.h"
#include "../../../inc/Dem_Mm_MemSync.h"
#include "../../../inc/Dem_Rc_RecMngCmn.h"
#include "../../../inc/Dem_Rc_RecMngCmn_Table.h"
#include "Dem_MemSync_local.h"
#include "Dem_MemSync_RecordKindIndexTable.h"


#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )

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


static FUNC( void, DEM_CODE ) Dem_DmSnc_UnitStatusTransition
(
    VAR( uint8, AUTOMATIC ) Trigger
);

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DmSnc_ProcessIdle
(
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>
/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/* Global management variable in Dem_DataMM_Snc unit. */
static VAR( Dem_u16_RecordKindIndexType, DEM_VAR_NO_INIT ) Dem_DmSnc_DataKindIndex;      /* MISRA DEVIATION */
static VAR( volatile uint8, DEM_VAR_NO_INIT ) Dem_DmSnc_UnitStatus;

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_DmSnc_Init                                           */
/* Description   | Initialize of Synchronizer sub unit.                     */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DmSnc_Init
( void )
{
    /* Global management variable Initialization */
    Dem_DmSnc_UnitStatus    =   DEM_DMSNC_STS_01_IDLE;
    Dem_DmSnc_DataKindIndex      = DEM_DMSNC_DATAKIND_INDEX_INITIAL;

    return;
}


/****************************************************************************/
/* Function Name | Dem_DmSnc_GetNvMWriteData                                */
/* Description   | Acquire nonvolatile synchronous data.                    */
/* Preconditions | none                                                     */
/* Parameters    | [out] BlockMirrorPtr :                                   */
/*               |        Nonvolatile synchronous data information.         */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_NO_MATCHING_ELEMENT : No relevant data    */
/*               |        DEM_IRT_NG : failed                               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DmSnc_GetNvMWriteData
(
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
)
{
    /* Auto variable definition */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )  retVal;
    VAR( uint8, AUTOMATIC )  unitStatus;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC )  recordKindIndex;

    /* Confirmation of unit status */
    unitStatus = Dem_DmSnc_UnitStatus;

    /* Processing according to state */
    switch( unitStatus )
    {
        case DEM_DMSNC_STS_01_IDLE:
            retVal = Dem_DmSnc_ProcessIdle( BlockMirrorPtr );
            break;

        case DEM_DMSNC_STS_02_SYNCING:
            /* Get record kind index. */
            recordKindIndex = Dem_DmSnc_RecordKindIndexTable[Dem_DmSnc_DataKindIndex];  /* [GUDCHK:SETVAL]Dem_DmSnc_DataKindIndex */

            /* Target data acquisition request */
            (void)Dem_RecMngCmn_GetNvMWriteData( recordKindIndex, BlockMirrorPtr ); /* no return check required */
            retVal = DEM_IRT_OK;
            break;

        default:
            retVal = DEM_IRT_NG;
            break;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_DmSnc_CompleteWrite                                  */
/* Description   | Notify of completion of NvM write processing.            */
/* Preconditions | none                                                     */
/* Parameters    | [in]  Result :                                           */
/*               |        Processing result.                                */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DmSnc_CompleteWrite
(
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) Result
)
{
    /* Auto variable definition */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCompleteNvMWrite;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC )  recordKindIndex;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC )  recMngCmnKindClrInfo;

    recMngCmnKindClrInfo = Dem_RecMngCmnKindClrInfo;
    /* Get record kind index. */
    recordKindIndex = Dem_DmSnc_RecordKindIndexTable[Dem_DmSnc_DataKindIndex];  /* [GUDCHK:SETVAL]Dem_DmSnc_DataKindIndex */

    if( recordKindIndex == recMngCmnKindClrInfo )
    {
        Dem_ClrInfoMng_SetNvClearResult( Result );
    }

    /* Write processing completion notification */
    retCompleteNvMWrite = Dem_RecMngCmn_NotifyCompleteNvMWrite( recordKindIndex, Result );

    if( retCompleteNvMWrite != DEM_IRT_PENDING )
    {
        /* DEM_IRT_OK */
        /* State transition processing */
        Dem_DmSnc_UnitStatusTransition( DEM_DMSNC_TRG_02_SYNC_COMPLETE );

        /* Target data Index initialize */
        Dem_DmSnc_DataKindIndex = DEM_DMSNC_DATAKIND_INDEX_INITIAL;
    }

    return;
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Dem_DmSnc_UnitStatusTransition                           */
/* Description   | Changes status for Synchronizer sub unit.                */
/* Preconditions | none                                                     */
/* Parameters    | [in] Trigger :                                           */
/*               |        Types of Triggers                                 */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_DmSnc_UnitStatusTransition
(
    VAR( uint8, AUTOMATIC ) Trigger
)
{
    /* Auto variable definition */
    VAR( uint8, AUTOMATIC )  unitStatus;

    /* Confirmation of unit status */
    unitStatus = Dem_DmSnc_UnitStatus;

    /* Processing according to state */
    switch( unitStatus )
    {
        case DEM_DMSNC_STS_01_IDLE:
            if ( Trigger == DEM_DMSNC_TRG_01_GET_SYNCDATA )
            {
                Dem_DmSnc_UnitStatus    =   DEM_DMSNC_STS_02_SYNCING;
            }
            break;

        case DEM_DMSNC_STS_02_SYNCING:
            if ( Trigger == DEM_DMSNC_TRG_02_SYNC_COMPLETE )
            {
                Dem_DmSnc_UnitStatus    =   DEM_DMSNC_STS_01_IDLE;
            }
            break;

        default:
            /* No process */
            break;
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_DmSnc_ProcessIdle                                    */
/* Description   | Processing when the unit status is [S01_IDLE].           */
/* Preconditions | none                                                     */
/* Parameters    | [out] BlockMirrorPtr :                                   */
/*               |        Nonvolatile synchronous data information.         */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_NO_MATCHING_ELEMENT : No relevant data    */
/*               |        DEM_IRT_NG : failed                               */
/*               |        DEM_IRT_PENDING : Process pending                 */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DmSnc_ProcessIdle
(
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
)
{
    /* Auto variable definition */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )  retVal;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC )  dataKindIndex;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC )  demMemSyncRecKindMax;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC )  recordKindIndex;
    VAR( boolean, AUTOMATIC )  request;

    /* Variable initialization */
    retVal = DEM_IRT_NO_MATCHING_ELEMENT;

    /*  Exec NvM Write Request. Reset request flag. */
    SchM_Enter_Dem_NvMRecordAccess();
    Dem_RecMngCmn_ResetRequestOfNvMWrite();
    SchM_Exit_Dem_NvMRecordAccess();

    demMemSyncRecKindMax = Dem_RecMngCmnKindMax;

    /* Confirm nonvolatile storage target data */
    for( dataKindIndex = (Dem_u16_RecordKindIndexType)0U; dataKindIndex < demMemSyncRecKindMax; dataKindIndex++ )   /* [GUD:for]dataKindIndex */
    {
        /* Get record kind index. */
        recordKindIndex = Dem_DmSnc_RecordKindIndexTable[dataKindIndex];    /* [GUD]dataKindIndex */

        /* Target data acquisition request */
        retVal = Dem_RecMngCmn_GetNvMWriteData( recordKindIndex, BlockMirrorPtr );

        if( retVal == DEM_IRT_OK )
        {
            /* State transition processing */
            Dem_DmSnc_UnitStatusTransition( DEM_DMSNC_TRG_01_GET_SYNCDATA );

            /* Save processing target data type information */
            Dem_DmSnc_DataKindIndex = dataKindIndex;

            break;
        }
    }

    if( retVal != DEM_IRT_OK )
    {
        /*  When DEM_IRT_NO_MATCHING_ELEMENT is returned for all types. */

        /*  Clear mode :  DEM_MODE_SYNCING_NVRAM    */
        SchM_Enter_Dem_NvMRecordAccess();

        /*  Check new request(from upper level context task) registed or not.   */
        request = Dem_RecMngCmn_GetRequestOfNvMWrite();
        if ( request == (boolean)FALSE )
        {
            /*  There is no requested data.             */
            Dem_ModeMng_ClearMode( DEM_MODE_SYNCING_NVRAM );
        }
        SchM_Exit_Dem_NvMRecordAccess();
    }


    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_DmSnc_RefreshRAM                                     */
/* Description   | Refresh RAM  - DmSnc                                     */
/* Preconditions | None                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | Called from Dem_MainFunction                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DmSnc_RefreshRAM
( void )
{
    VAR( volatile uint8, AUTOMATIC )                      u8_dummy;      /*  for store GlobalVariable data    */
    P2VAR( volatile uint8, AUTOMATIC, DEM_VAR_NO_INIT )   u8_dummyPtr;   /*  for GlobalVariable address       */

    /*  set GlobalVariable pointer  */
    u8_dummyPtr     = &Dem_DmSnc_UnitStatus;

    /* Exclusion is not necessary   */
    u8_dummy        = *u8_dummyPtr;         /*  read GlobalVariable data    */
    *u8_dummyPtr    = u8_dummy;             /*  rewrite GlobalVariable data */

    Dem_RecMngCmn_RefreshRAM();

    return ;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v2-0-0         :2019-03-27                                              */
/*  v2-0-1         :2019-04-24                                              */
/*  v3-0-0         :2019-07-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
