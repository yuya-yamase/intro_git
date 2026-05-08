/* Dem_OdrLst_local_c(v5-3-0)                                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/OdrLst_local/HEADER                                   */
/*--------------------------------------------------------------------------*/
/* Notes       |                                                            */
/****************************************************************************/

#ifndef DEM_ODRLST_LOCAL_H
#define DEM_ODRLST_LOCAL_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../../../cfg/Dem_NvM_Cfg.h"
#include "../../../inc/Dem_Rc_OdrLst.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* Structure for FaultOrderList */
typedef struct{
    Dem_u08_FaultIndexType FaultIndex;
}Dem_FaultOrderType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

extern  VAR( Dem_FaultRegistType, DEM_VAR_NO_INIT ) Dem_OdrLst_TmpFaultOrderList[DEM_FAIL_RECORD_NUM];

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/*  Sort function       */
FUNC( void, DEM_CODE ) Dem_OdrLst_SortFaultOrderList
(
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) NumOfFaultOrderItemsToSort,
    P2VAR( Dem_FaultRegistType, AUTOMATIC, DEM_VAR_NO_INIT ) DataPtr
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif /* DEM_ODRLST_LOCAL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-0-0         :2019-07-29                                              */
/*  v4-0-0         :2020-03-19                                              */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
