/* Dem_MM_c(v5-3-0)                                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/MM/CODE                                               */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../inc/Dem_Mm_MM.h"
#include "../../../inc/Dem_Mm_MemSync.h"
#include "../../../cfg/Dem_Data_Cfg.h"
#include "../../../cfg/Dem_MM_Cfg.h"
#include "Dem_MM_local.h"


#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
#include "../../../usr/Dem_NvM_MultiBlockState_Callout.h"

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Status of Unit */
typedef uint8       Dem_u08_MMStatusType;   /*  MM status type      */

#define DEM_MM_STS_IDLE                    ((Dem_u08_MMStatusType)0x00U)
#define DEM_MM_STS_PROCESSING              ((Dem_u08_MMStatusType)0x11U)

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

static FUNC( Dem_u08_MMWriteExecType, DEM_CODE ) Dem_MM_WriteStartProcess
( void );
static FUNC( Dem_u08_MMWriteExecType, DEM_CODE ) Dem_MM_WriteProcess
( void );


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/* Status of Dem_MM unit */
static VAR( volatile Dem_u08_MMStatusType, DEM_VAR_NO_INIT ) Dem_MM_UnitStatus;

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_MM_Init                                              */
/* Description   | Initialize of Dem_MM-internal state and volatile RAM.    */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MM_Init
( void )
{
    /* Init of management data */
    Dem_MM_InitBlockReadStatus();
    Dem_MM_InitBlockWriteStatus();

    Dem_DmSnc_Init();

    /*  complete MM initialize process.     */
    Dem_MM_UnitStatus = DEM_MM_STS_IDLE;

    return ;
}


/****************************************************************************/
/* Function Name | Dem_MM_CheckExecReadAll                                  */
/* Description   | Check ReadNvM executed or not..                          */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | boolean                                                  */
/*               |        TRUE   : ReadAll was executed.                    */
/*               |        FALSE  : ReadAll was not executed.                */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_MM_CheckExecReadAll
( void )
{
    VAR( boolean, AUTOMATIC ) retExecReadAll;

    retExecReadAll = Dem_NvM_GetReadAllExecState();

    return retExecReadAll;
}

/****************************************************************************/
/* Function Name | Dem_MM_InitProcess                                       */
/* Description   | reading confirmation of non-volatilization memory        */
/* Preconditions | Not complete Nv read by Dem_MM_Init.                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Non-volatilization reading success.  */
/*               |        DEM_IRT_PENDING : Non-volatilization reading pen- */
/*               |        ding.                                             */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MM_InitProcess
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultCheckNvBlockStatus;

    retVal = DEM_IRT_OK;

    /*  wait readall confirmed.             */
    resultCheckNvBlockStatus = Dem_MM_CheckNvBlockStatus();
    if( resultCheckNvBlockStatus == DEM_IRT_PENDING )
    {
        retVal = DEM_IRT_PENDING;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_MM_Process                                           */
/* Description   | synchronization of non-volatile RAM and volatile RAM.    */
/* Preconditions | Completes initialize and Nv read.                        */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MM_Process
( void )
{
    VAR( Dem_u08_MMWriteExecType, AUTOMATIC ) retExecWrite;
    VAR( Dem_u08_MMStatusType, AUTOMATIC ) unitStatus;

    unitStatus  =   Dem_MM_UnitStatus;
    if ( unitStatus == DEM_MM_STS_IDLE )
    {
        retExecWrite    =   Dem_MM_WriteStartProcess();
        if ( retExecWrite == DEM_MM_WRITEEXEC_PROCESSING )
        {
            (void)Dem_MM_WriteProcess();        /* no return check required */
        }
    }
    else if ( unitStatus == DEM_MM_STS_PROCESSING )
    {
        retExecWrite    =   Dem_MM_WriteProcess();
        if ( retExecWrite == DEM_MM_WRITEEXEC_COMPLETE )
        {
            retExecWrite    =   Dem_MM_WriteStartProcess();
            if ( retExecWrite == DEM_MM_WRITEEXEC_PROCESSING )
            {
                (void)Dem_MM_WriteProcess();        /* no return check required */
            }
        }
    }
    else
    {
        /*  error.      */
        Dem_MM_UnitStatus   =   DEM_MM_STS_IDLE;
    }
    return ;
}


/****************************************************************************/
/* Function Name | Dem_MM_WriteProcess                                      */
/* Description   | Write process                                            */
/* Preconditions | Completes initialize and Nv read.                        */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_MMWriteExecType                                  */
/*               |  DEM_MM_WRITEEXEC_IDLE       :   not write.              */
/*               |  DEM_MM_WRITEEXEC_PROCESSING :   write process execute.  */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( Dem_u08_MMWriteExecType, DEM_CODE ) Dem_MM_WriteStartProcess
( void )
{
    VAR( Dem_u08_MMWriteExecType, AUTOMATIC ) retExecWrite;
    VAR( Dem_u08_MMWriteExecType, AUTOMATIC ) resultWriteStartStatus;

    retExecWrite            =   DEM_MM_WRITEEXEC_IDLE;
    resultWriteStartStatus  =   Dem_MM_ProcessIdle();

    if ( resultWriteStartStatus == DEM_MM_WRITEEXEC_PROCESSING )
    {
        Dem_MM_UnitStatus   =   DEM_MM_STS_PROCESSING;
        retExecWrite        =   DEM_MM_WRITEEXEC_PROCESSING;
    }

    return retExecWrite;
}


/****************************************************************************/
/* Function Name | Dem_MM_WriteProcess                                      */
/* Description   | Write process                                            */
/* Preconditions | Completes initialize and Nv read.                        */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_MMWriteExecType                                  */
/*               |  DEM_MM_WRITEEXEC_PROCESSING :   write process execute.  */
/*               |  DEM_MM_WRITEEXEC_COMPLETE   :   complete write process. */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( Dem_u08_MMWriteExecType, DEM_CODE ) Dem_MM_WriteProcess
( void )
{
    VAR( Dem_u08_MMWriteExecType, AUTOMATIC ) retExecWrite;
    VAR( Dem_u08_MMWriteExecType, AUTOMATIC ) resultWriteCompStatus;

    retExecWrite    =   DEM_MM_WRITEEXEC_PROCESSING;

    resultWriteCompStatus   =   Dem_MM_ProcessRequest();
    if ( resultWriteCompStatus != DEM_MM_STS_PROCESSING )
    {
        Dem_MM_UnitStatus   =   DEM_MM_STS_IDLE;
        retExecWrite        =   DEM_MM_WRITEEXEC_COMPLETE;
    }
    return retExecWrite;
}


/****************************************************************************/
/* Function Name | Dem_MM_JudgmentErrorStatus                               */
/* Description   | Converts Nv block status to data for Dem_MM unit.        */
/* Preconditions | none                                                     */
/* Parameters    | [in] ErrorStatus :                                       */
/*               |        error status                                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_PENDING : pending                         */
/*               |        DEM_IRT_NG : failed                               */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MM_JudgmentErrorStatus
(
    VAR( Dem_NvM_RequestResultType, AUTOMATIC ) ErrorStatus
)
{
    /* Auto variable definition */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    /* Classification of status */
    switch( ErrorStatus )
    {
        case DEM_NVM_REQ_OK:
            retVal = DEM_IRT_OK;
            break;
        case DEM_NVM_REQ_BLOCK_SKIPPED:
            retVal = DEM_IRT_OK;
            break;
        case DEM_NVM_REQ_PENDING:
            retVal = DEM_IRT_PENDING;
            break;
        case DEM_NVM_REQ_NOT_OK:
            retVal = DEM_IRT_NG;
            break;
        case DEM_NVM_REQ_INTEGRITY_FAILED:
            retVal = DEM_IRT_NG;
            break;
        case DEM_NVM_REQ_NV_INVALIDATED:
            retVal = DEM_IRT_NG;
            break;
        case DEM_NVM_REQ_CANCELED:
            retVal = DEM_IRT_NG;
            break;
        case DEM_NVM_REQ_RESTORED_FROM_ROM:
            retVal = DEM_IRT_NG;
            break;
        default:
            retVal = DEM_IRT_NG;
            break;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_MM_RefreshRAM                                        */
/* Description   | Refresh RAM  - MM                                        */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | Called from Dem_MainFunction                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MM_RefreshRAM
( void )
{
    VAR( volatile Dem_u08_MMStatusType, AUTOMATIC )                      u8_dummy;      /*  for store GlobalVariable data    */
    P2VAR( volatile Dem_u08_MMStatusType, AUTOMATIC, DEM_VAR_NO_INIT )   u8_dummyPtr;   /*  for GlobalVariable address       */

    /*  set GlobalVariable pointer  */
    u8_dummyPtr      = &Dem_MM_UnitStatus;

    /* Exclusion is not necessary   */
    u8_dummy         = *u8_dummyPtr;          /*  read GlobalVariable data    */
    *u8_dummyPtr     = u8_dummy;              /*  rewrite GlobalVariable data */

    Dem_DmSnc_RefreshRAM();

    return;
}
#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif /* DEM_NVM_SYNC_PROCESS_ENABLE  -STD_ON- */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v2-0-0         :2019-03-27                                              */
/*  v3-0-0         :2019-09-26                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
