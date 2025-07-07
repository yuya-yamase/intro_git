/* Dem_CmnLib_AsyncReqTable_h(v5-5-0)                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DEM/CmnLib_AsyncReqTable/HEADER                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_CMNLIB_ASYNCREQTABLE_H
#define DEM_CMNLIB_ASYNCREQTABLE_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../cfg/Dem_Cfg.h"
#include "Dem_CmnLib_AsyncReq.h"


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Async Request Kind */
#define DEM_ASYNCREQ_EVENT                          ((Dem_u08_AsyncReqTableIndexType)0U)
#define DEM_ASYNCREQ_RESTART_OPCYCLE                ((Dem_u08_AsyncReqTableIndexType)1U)
#define DEM_ASYNCREQ_INITILIZE_EVENT_STATUS         ((Dem_u08_AsyncReqTableIndexType)2U)
#define DEM_ASYNCREQ_AGING_EVENT_STATUS             ((Dem_u08_AsyncReqTableIndexType)3U)
#define DEM_ASYNCREQ_NORMALIZE_EVENT_STATUS         ((Dem_u08_AsyncReqTableIndexType)4U)

/* Async Request Table Num */
#define DEM_ASYNCREQ_NUM                            ((Dem_u08_AsyncReqTableIndexType)5U)


/* Data Queue Item Size Max */
#define DEM_ASYNCDATAQUE_ITEMSIZE_MAX               ((Dem_u08_AsyncDataQueItemSizeType)28U)


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
FUNC( Dem_u08_AsyncExecReturnType, DEM_CODE ) Dem_AsyncReqFnc_ForStack
(
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC )                Index,
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC )                Status,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC )    DataBuffPtr
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

extern CONST( AB_83_ConstV Dem_AsyncReqTableType                 ,DEM_CONFIG_DATA ) Dem_ExecAsyncReqTable[ DEM_ASYNCREQ_NUM ];

extern CONST( AB_83_ConstV Dem_u08_AsyncReqTableIndexType        ,DEM_CONFIG_DATA ) Dem_AsyncReqNum;

#define DEM_STOP_SEC_CONST_CONFIG
#include <Dem_MemMap.h>


#endif /* DEM_CMNLIB_ASYNCREQTABLE_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-3-z0003                                        */
/*  BSW plug-in        :v5-5-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
