/* Dem_OpCycle_CycleKindTable_c(v5-5-0)                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Dem_OpCycle_CheckCycleKind/CODE                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "Dem_OpCycle_CycleKindTable.h"

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

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CONST_CONFIG
#include <Dem_MemMap.h>

#if ( DEM_ENGINETYPE_COMPRESSION_SUPPORT == STD_OFF )
CONST( AB_83_ConstV Dem_u08_OpcycUpdateFailureCycleType,  DEM_CONFIG_DATA ) Dem_OpCycleUpdateFailureCycleTable[ DEM_OPCYCKIND_CFGCYCLE_MAX ][ DEM_OPCYCKIND_THISCYCLE_MAX ] =
{                           /*  ThisCycle                                                       */
                            /*  other                               IG                                                                      DCY                                                                         WARMUP                              4hDCY                               */
    /*  ConfigureCycle  */
    /*  other           */  {   DEM_OPCYCUPD_FLCYC_UPDATE_ALL,      DEM_OPCYCUPD_FLCYC_INITIALVALUE,                                        DEM_OPCYCUPD_FLCYC_INITIALVALUE,                                            DEM_OPCYCUPD_FLCYC_INITIALVALUE,    DEM_OPCYCUPD_FLCYC_INITIALVALUE     },
    /*  IG              */  {   DEM_OPCYCUPD_FLCYC_INITIALVALUE,    DEM_OPCYCUPD_FLCYC_UPDATE_ALL,                                          DEM_OPCYCUPD_FLCYC_UPDATE_ALL,                                              DEM_OPCYCUPD_FLCYC_UPDATE_ALL,      DEM_OPCYCUPD_FLCYC_INITIALVALUE     },
    /*  DCY             */  {   DEM_OPCYCUPD_FLCYC_INITIALVALUE,    DEM_OPCYCUPD_FLCYC_INITIALVALUE,                                        DEM_OPCYCUPD_FLCYC_UPDATE_ALL,                                              DEM_OPCYCUPD_FLCYC_UPDATE_ALL,      DEM_OPCYCUPD_FLCYC_UPDATE_ALL       }
};

CONST( AB_83_ConstV Dem_u08_OpcycUpdateHealingAgingCycleType,  DEM_CONFIG_DATA ) Dem_OpCycleUpdateHealingAgingCycleTable[ DEM_OPCYCKIND_CFGCYCLE_MAX ][ DEM_OPCYCKIND_THISCYCLE_MAX ] =
{                           /*  ThisCycle                                                       */
                            /*  other                               IG                                                                      DCY                                                                         WARMUP                              4hDCY                               */
    /*  ConfigureCycle  */
    /*  other           */  {   DEM_OPCYCUPD_HACYC_UPDATE_ALL,      DEM_OPCYCUPD_HACYC_INITIALVALUE,                                        DEM_OPCYCUPD_HACYC_INITIALVALUE,                                            DEM_OPCYCUPD_HACYC_INITIALVALUE,    DEM_OPCYCUPD_HACYC_INITIALVALUE         },
    /*  IG              */  {   DEM_OPCYCUPD_HACYC_INITIALVALUE,    DEM_OPCYCUPD_HACYC_UPDATE_ALL,                                          DEM_OPCYCUPD_HACYC_UPDATE_ALL,                                              DEM_OPCYCUPD_HACYC_UPDATE_ALL,      DEM_OPCYCUPD_HACYC_INITIALVALUE         },
    /*  DCY             */  {   DEM_OPCYCUPD_HACYC_INITIALVALUE,    DEM_OPCYCUPD_HACYC_INITIALVALUE,                                        DEM_OPCYCUPD_HACYC_UPDATE_HEALINGCYC | DEM_OPCYCUPD_HACYC_UPDATE_AGINGCYC,  DEM_OPCYCUPD_HACYC_UPDATE_ALL,      DEM_OPCYCUPD_HACYC_UPDATE_HEALINGCYC    }
};
#endif  /*   ( DEM_ENGINETYPE_COMPRESSION_SUPPORT == STD_OFF )      */

#if ( DEM_ENGINETYPE_COMPRESSION_SUPPORT == STD_ON )
CONST( AB_83_ConstV Dem_u08_OpcycUpdateFailureCycleType,  DEM_CONFIG_DATA ) Dem_OpCycleUpdateFailureCycleTable[ DEM_OPCYCKIND_CFGCYCLE_MAX ][ DEM_OPCYCKIND_THISCYCLE_MAX ] =
{                           /*  ThisCycle                                                       */
                            /*  other                               IG                                                                      DCY                                                                         WARMUP                              4hDCY                               */
    /*  ConfigureCycle  */
    /*  other           */  {   DEM_OPCYCUPD_FLCYC_UPDATE_ALL,      DEM_OPCYCUPD_FLCYC_INITIALVALUE,                                        DEM_OPCYCUPD_FLCYC_INITIALVALUE,                                            DEM_OPCYCUPD_FLCYC_INITIALVALUE,    DEM_OPCYCUPD_FLCYC_INITIALVALUE     },
    /*  IG              */  {   DEM_OPCYCUPD_FLCYC_INITIALVALUE,    ( DEM_OPCYCUPD_FLCYC_UPDSTATUS_TF | DEM_OPCYCUPD_FLCYC_UPDATE_FCCYC ),  DEM_OPCYCUPD_FLCYC_UPDATE_ALL,                                              DEM_OPCYCUPD_FLCYC_UPDATE_ALL,      ( DEM_OPCYCUPD_FLCYC_UPDSTATUS_TFTOC | DEM_OPCYCUPD_FLCYC_UPDSTATUS_TNCTOC | DEM_OPCYCUPD_FLCYC_UPDATE_FCCYC )      },
    /*  DCY             */  {   DEM_OPCYCUPD_FLCYC_INITIALVALUE,    ( DEM_OPCYCUPD_FLCYC_UPDSTATUS_TF ),                                    DEM_OPCYCUPD_FLCYC_UPDATE_ALL,                                              DEM_OPCYCUPD_FLCYC_UPDATE_ALL,      ( DEM_OPCYCUPD_FLCYC_UPDSTATUS_TFTOC | DEM_OPCYCUPD_FLCYC_UPDSTATUS_TNCTOC | DEM_OPCYCUPD_FLCYC_UPDATE_FCCYC )      }
};
#if ( DEM_WWH_OBD_SUPPORT == STD_OFF )
CONST( AB_83_ConstV Dem_u08_OpcycUpdateHealingAgingCycleType,  DEM_CONFIG_DATA ) Dem_OpCycleUpdateHealingAgingCycleTable[ DEM_OPCYCKIND_CFGCYCLE_MAX ][ DEM_OPCYCKIND_THISCYCLE_MAX ] =
{                           /*  ThisCycle                                                       */
                            /*  other                               IG                                                                      DCY                                                                         WARMUP                              4hDCY                               */
    /*  ConfigureCycle  */
    /*  other           */  {   DEM_OPCYCUPD_HACYC_UPDATE_ALL,      DEM_OPCYCUPD_HACYC_INITIALVALUE,                                        DEM_OPCYCUPD_HACYC_INITIALVALUE,                                            DEM_OPCYCUPD_HACYC_INITIALVALUE,    DEM_OPCYCUPD_HACYC_INITIALVALUE         },
    /*  IG              */  {   DEM_OPCYCUPD_HACYC_INITIALVALUE,    DEM_OPCYCUPD_HACYC_UPDATE_ALL,                                          DEM_OPCYCUPD_HACYC_UPDATE_ALL,                                              DEM_OPCYCUPD_HACYC_UPDATE_ALL,      DEM_OPCYCUPD_HACYC_INITIALVALUE         },
    /*  DCY             */  {   DEM_OPCYCUPD_HACYC_INITIALVALUE,    DEM_OPCYCUPD_HACYC_INITIALVALUE,                                        DEM_OPCYCUPD_HACYC_UPDATE_HEALINGCYC | DEM_OPCYCUPD_HACYC_UPDATE_AGINGCYC,  DEM_OPCYCUPD_HACYC_UPDATE_ALL,      DEM_OPCYCUPD_HACYC_UPDATE_HEALINGCYC    }
};
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_OFF ) */
#if ( DEM_WWH_OBD_SUPPORT == STD_ON )
CONST( AB_83_ConstV Dem_u08_OpcycUpdateHealingAgingCycleType,  DEM_CONFIG_DATA ) Dem_OpCycleUpdateHealingAgingCycleTable[ DEM_OPCYCKIND_CFGCYCLE_MAX ][ DEM_OPCYCKIND_THISCYCLE_MAX ] =
{                           /*  ThisCycle                                                       */
                            /*  other                               IG                                                                          DCY                                                                                                                                                             WARMUP                                                                                                              4hDCY                              */
    /*  ConfigureCycle  */
    /*  other           */  {   DEM_OPCYCUPD_HACYC_UPDATE_ALL,      DEM_OPCYCUPD_HACYC_INITIALVALUE,                                            DEM_OPCYCUPD_HACYC_INITIALVALUE,                                                                                                                                DEM_OPCYCUPD_HACYC_INITIALVALUE,                                                                                    DEM_OPCYCUPD_HACYC_INITIALVALUE     },
    /*  IG              */  {   DEM_OPCYCUPD_HACYC_INITIALVALUE,    DEM_OPCYCUPD_HACYC_UPDATE_ALL | DEM_OPCYCUPD_HACYC_UPDATE_TIME_AGINGCYC,    DEM_OPCYCUPD_HACYC_UPDATE_ALL | DEM_OPCYCUPD_HACYC_UPDATE_TIME_AGINGCYC,                                                                                        DEM_OPCYCUPD_HACYC_UPDATE_ALL | DEM_OPCYCUPD_HACYC_UPDATE_TIME_AGINGCYC,                                            DEM_OPCYCUPD_HACYC_INITIALVALUE     },
    /*  DCY             */  {   DEM_OPCYCUPD_HACYC_INITIALVALUE,    DEM_OPCYCUPD_HACYC_INITIALVALUE,                                            DEM_OPCYCUPD_HACYC_UPDATE_HEALINGCYC | DEM_OPCYCUPD_HACYC_UPDATE_AGINGCYC | DEM_OPCYCUPD_HACYC_UPDATE_TIME_AGINGCYC | DEM_OPCYCUPD_HACYC_EXEC_WWHOBD_AGING,     DEM_OPCYCUPD_HACYC_UPDATE_ALL | DEM_OPCYCUPD_HACYC_UPDATE_TIME_AGINGCYC | DEM_OPCYCUPD_HACYC_EXEC_WWHOBD_AGING,     DEM_OPCYCUPD_HACYC_INITIALVALUE     }
};
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */
#endif  /*   ( DEM_ENGINETYPE_COMPRESSION_SUPPORT == STD_OFF )      */

#define DEM_STOP_SEC_CONST_CONFIG
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
