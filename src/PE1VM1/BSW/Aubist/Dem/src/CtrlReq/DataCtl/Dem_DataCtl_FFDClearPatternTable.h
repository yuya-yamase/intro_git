/* Dem_DataCtl_FFDClearPatternTable_h(v5-5-0)                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataCtl_FFDClearPatternTable/HEADER                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_DATACTL_FFDCLEARPATTERNTABLE_H
#define DEM_DATACTL_FFDCLEARPATTERNTABLE_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "Dem_DataCtl_local.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
typedef     uint8   Dem_u08_ClearPtnAtDTCStatusType;
#define     DEM_CLRPTN_CLR_BOTHON                   ((Dem_u08_ClearPtnAtDTCStatusType)0x08U)       /*  bxxxx11xx   */
#define     DEM_CLRPTN_CLR_CDTCON                   ((Dem_u08_ClearPtnAtDTCStatusType)0x04U)       /*  bxxxx10xx   */
#define     DEM_CLRPTN_CLR_PDTCON                   ((Dem_u08_ClearPtnAtDTCStatusType)0x02U)       /*  bxxxx01xx   */
#define     DEM_CLRPTN_CLR_BOTHOFF                  ((Dem_u08_ClearPtnAtDTCStatusType)0x01U)       /*  bxxxx00xx   */

#define     DEM_CLRPTN_STY_BOTHON                   ((Dem_u08_ClearPtnAtDTCStatusType)0x00U)       /*  bxxxx11xx   */
#define     DEM_CLRPTN_STY_CDTCON                   ((Dem_u08_ClearPtnAtDTCStatusType)0x00U)       /*  bxxxx10xx   */
#define     DEM_CLRPTN_STY_PDTCON                   ((Dem_u08_ClearPtnAtDTCStatusType)0x00U)       /*  bxxxx01xx   */
#define     DEM_CLRPTN_STY_BOTHOFF                  ((Dem_u08_ClearPtnAtDTCStatusType)0x00U)       /*  bxxxx00xx   */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct
{
    Dem_u08_ClearPtnAtDTCStatusType     RecoveryTypeArray[ DEM_RECOVERYTYPE_MAX ];

} Dem_FFDClearPtnAtTriggerType;

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


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CONST_CONFIG
#include <Dem_MemMap.h>

extern CONST( AB_83_ConstV Dem_u08_ClearPtnAtDTCStatusType,  DEM_CONFIG_DATA ) Dem_FaultClearPattenTable[ DEM_RECOVERYTYPE_MAX ];
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
extern CONST( AB_83_ConstV Dem_FFDClearPtnAtTriggerType,  DEM_CONFIG_DATA ) Dem_FFDClearPatten_OBDFFD_Table[ DEM_FFDTRIGGER_IDX_MAX ];
#endif  /*   ( DEM_OBDFFD_SUPPORT == STD_ON )      */
extern CONST( AB_83_ConstV Dem_FFDClearPtnAtTriggerType,  DEM_CONFIG_DATA ) Dem_FFDClearPatten_NonOBDFFD_Table[ DEM_FFDTRIGGER_IDX_MAX ];


#define DEM_STOP_SEC_CONST_CONFIG
#include <Dem_MemMap.h>

#endif /* DEM_DATACTL_FFDCLEARPATTERNTABLE_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
