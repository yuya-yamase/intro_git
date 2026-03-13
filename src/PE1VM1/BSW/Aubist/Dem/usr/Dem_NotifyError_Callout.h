/* Dem_NotifyError_Callout_h(v5-3-0)                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/NotifyError_Callout/HEADER                            */
/*--------------------------------------------------------------------------*/
/* Notes |                                                                  */
/****************************************************************************/

#ifndef DEM_NOTIFYERROR_CALLOUT_H
#define DEM_NOTIFYERROR_CALLOUT_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef uint16   Dem_ErrorStatusType;               /* ErrorStatus          */

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_ERROR_NVM_READALL_READ_FAILED           ((Dem_ErrorStatusType)(0x0010u))
#define DEM_ERROR_NVM_READALL_TIMEOUT               ((Dem_ErrorStatusType)(0x0011u))
#define DEM_ERROR_NVM_WRITE_TIMEOUT                 ((Dem_ErrorStatusType)(0x0013u))
#define DEM_ERROR_NVM_CANCEL_FAILED                 ((Dem_ErrorStatusType)(0x0014u))

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE_CALLOUT
#include <Dem_MemMap.h>

FUNC( void, DEM_CODE_CALLOUT ) Dem_NotifyErrorStatus
(
    VAR( Dem_BlockIdType, AUTOMATIC ) BlockId,
    VAR( Dem_ErrorStatusType, AUTOMATIC ) ErrorStatus
);

#define DEM_STOP_SEC_CODE_CALLOUT
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CONST
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_CONST
#include <Dem_MemMap.h>


#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

#endif /* DEM_NOTIFYERROR_CALLOUT_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v4-0-0         :2020-03-19                                              */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
