/* Dem_DataCtl_FFDClearPatternTable_c(v5-5-0)                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataCtl_FFDClearPattern/CODE                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "Dem_DataCtl_FFDClearPatternTable.h"
#include "Dem_DataCtl_local.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CONST_CONFIG
#include <Dem_MemMap.h>

/*----------------------------------------------------------------------*/
/*  FaultRecord ClearPattern table                                      */
/*      DEM_CLRPTN_STY_xxxx :   no clear fault record.                  */
/*      DEM_CLRPTN_CLR_xxxx :   clear fault record if all FFD deleted.  */
/*----------------------------------------------------------------------*/
CONST( AB_83_ConstV Dem_u08_ClearPtnAtDTCStatusType,  DEM_CONFIG_DATA ) Dem_FaultClearPattenTable[ DEM_RECOVERYTYPE_MAX ]   =
{
                        /*  RecoveryType    */
                        /*  PendingOFF                                                                                          Aging                                                                                               Normalize                                                                       */
    /*  PDTC    */      /*  1                       0                       1                       0                           1                       0                       1                       0                           1                       0                       1                       0       */
    /*  CDTC    */      /*  1                       1                       0                       0                           1                       1                       0                       0                           1                       1                       0                       0       */
                        ( DEM_CLRPTN_STY_BOTHON | DEM_CLRPTN_STY_CDTCON | DEM_CLRPTN_CLR_PDTCON | DEM_CLRPTN_CLR_BOTHOFF ), ( DEM_CLRPTN_STY_BOTHON | DEM_CLRPTN_CLR_CDTCON | DEM_CLRPTN_STY_PDTCON | DEM_CLRPTN_CLR_BOTHOFF ), ( DEM_CLRPTN_CLR_BOTHON | DEM_CLRPTN_CLR_CDTCON | DEM_CLRPTN_CLR_PDTCON | DEM_CLRPTN_CLR_BOTHOFF )
};

/*----------------------------------------------------------------------*/
/*  FFD ClearPattern table  :   OBD                                     */
/*----------------------------------------------------------------------*/
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
CONST( AB_83_ConstV Dem_FFDClearPtnAtTriggerType,  DEM_CONFIG_DATA ) Dem_FFDClearPatten_OBDFFD_Table[ DEM_FFDTRIGGER_IDX_MAX ] =
{
                        /*  RecoveryType    */
                        /*  PendingOFF                                                                                          Aging                                                                                               Normalize                                                                       */
    /*  PDTC    */      /*  1                       0                       1                       0                           1                       0                       1                       0                           1                       0                       1                       0       */
    /*  CDTC    */      /*  1                       1                       0                       0                           1                       1                       0                       0                           1                       1                       0                       0       */

/*  Trigger         */
/*  TFTOC           */{{ ( DEM_CLRPTN_STY_BOTHON | DEM_CLRPTN_STY_CDTCON | DEM_CLRPTN_CLR_PDTCON | DEM_CLRPTN_CLR_BOTHOFF ), ( DEM_CLRPTN_CLR_BOTHON | DEM_CLRPTN_CLR_CDTCON | DEM_CLRPTN_STY_PDTCON | DEM_CLRPTN_STY_BOTHOFF ), ( DEM_CLRPTN_CLR_BOTHON | DEM_CLRPTN_CLR_CDTCON | DEM_CLRPTN_CLR_PDTCON | DEM_CLRPTN_STY_BOTHOFF )  }},

#if ( DEM_PDTCFFD_CLRTRIGGER_TRIGGEROFF_SUPPORT == STD_ON )
/*  PDTC(TriggerOFF)*/{{ ( DEM_CLRPTN_CLR_BOTHON | DEM_CLRPTN_CLR_CDTCON | DEM_CLRPTN_CLR_PDTCON | DEM_CLRPTN_CLR_BOTHOFF ), ( DEM_CLRPTN_STY_BOTHON | DEM_CLRPTN_CLR_CDTCON | DEM_CLRPTN_STY_PDTCON | DEM_CLRPTN_CLR_BOTHOFF ), ( DEM_CLRPTN_CLR_BOTHON | DEM_CLRPTN_CLR_CDTCON | DEM_CLRPTN_CLR_PDTCON | DEM_CLRPTN_CLR_BOTHOFF )  }},
#endif  /* ( DEM_PDTCFFD_CLRTRIGGER_TRIGGEROFF_SUPPORT == STD_ON )  */
#if ( DEM_PDTCFFD_CLRTRIGGER_TRIGGEROFF_SUPPORT == STD_OFF )
/*  PDTC(NoFault)   */{{ ( DEM_CLRPTN_STY_BOTHON | DEM_CLRPTN_STY_CDTCON | DEM_CLRPTN_CLR_PDTCON | DEM_CLRPTN_CLR_BOTHOFF ), ( DEM_CLRPTN_STY_BOTHON | DEM_CLRPTN_CLR_CDTCON | DEM_CLRPTN_STY_PDTCON | DEM_CLRPTN_CLR_BOTHOFF ), ( DEM_CLRPTN_CLR_BOTHON | DEM_CLRPTN_CLR_CDTCON | DEM_CLRPTN_CLR_PDTCON | DEM_CLRPTN_CLR_BOTHOFF )  }},
#endif  /* ( DEM_PDTCFFD_CLRTRIGGER_TRIGGEROFF_SUPPORT == STD_OFF ) */

/*  CDTC            */{{ ( DEM_CLRPTN_STY_BOTHON | DEM_CLRPTN_STY_CDTCON | DEM_CLRPTN_CLR_PDTCON | DEM_CLRPTN_CLR_BOTHOFF ), ( DEM_CLRPTN_CLR_BOTHON | DEM_CLRPTN_CLR_CDTCON | DEM_CLRPTN_CLR_PDTCON | DEM_CLRPTN_CLR_BOTHOFF ), ( DEM_CLRPTN_CLR_BOTHON | DEM_CLRPTN_CLR_CDTCON | DEM_CLRPTN_CLR_PDTCON | DEM_CLRPTN_CLR_BOTHOFF )  }},
/*  FDCThreshold    */{{ ( DEM_CLRPTN_STY_BOTHON | DEM_CLRPTN_STY_CDTCON | DEM_CLRPTN_STY_PDTCON | DEM_CLRPTN_STY_BOTHOFF ), ( DEM_CLRPTN_CLR_BOTHON | DEM_CLRPTN_CLR_CDTCON | DEM_CLRPTN_STY_PDTCON | DEM_CLRPTN_STY_BOTHOFF ), ( DEM_CLRPTN_CLR_BOTHON | DEM_CLRPTN_CLR_CDTCON | DEM_CLRPTN_STY_PDTCON | DEM_CLRPTN_STY_BOTHOFF )  }}

};
#endif  /*   ( DEM_OBDFFD_SUPPORT == STD_ON )      */

/*----------------------------------------------------------------------*/
/*  FFD ClearPattern table  :   nonOBD                                  */
/*----------------------------------------------------------------------*/
/*  Pattern TMC     */
CONST( AB_83_ConstV Dem_FFDClearPtnAtTriggerType,  DEM_CONFIG_DATA ) Dem_FFDClearPatten_NonOBDFFD_Table[ DEM_FFDTRIGGER_IDX_MAX ] =
{
                        /*  RecoveryType    */
                        /*  PendingOFF                                                                                          Aging                                                                                               Normalize                                                                       */
    /*  PDTC    */      /*  1                       0                       1                       0                           1                       0                       1                       0                           1                       0                       1                       0       */
    /*  CDTC    */      /*  1                       1                       0                       0                           1                       1                       0                       0                           1                       1                       0                       0       */

/*  Trigger         */

#if ( DEM_TFTOCFFD_CLRTRIGGER_AGINGONLY_SUPPORT == STD_ON )
/*  TFTOC           */{{ ( DEM_CLRPTN_STY_BOTHON | DEM_CLRPTN_STY_CDTCON | DEM_CLRPTN_STY_PDTCON | DEM_CLRPTN_STY_BOTHOFF ), ( DEM_CLRPTN_CLR_BOTHON | DEM_CLRPTN_CLR_CDTCON | DEM_CLRPTN_STY_PDTCON | DEM_CLRPTN_STY_BOTHOFF ), ( DEM_CLRPTN_CLR_BOTHON | DEM_CLRPTN_CLR_CDTCON | DEM_CLRPTN_STY_PDTCON | DEM_CLRPTN_STY_BOTHOFF )  }},
#endif  /* ( DEM_TFTOCFFD_CLRTRIGGER_AGINGONLY_SUPPORT == STD_ON )  */
#if ( DEM_TFTOCFFD_CLRTRIGGER_AGINGONLY_SUPPORT == STD_OFF )
/*  TFTOC           */{{ ( DEM_CLRPTN_STY_BOTHON | DEM_CLRPTN_STY_CDTCON | DEM_CLRPTN_CLR_PDTCON | DEM_CLRPTN_CLR_BOTHOFF ), ( DEM_CLRPTN_CLR_BOTHON | DEM_CLRPTN_CLR_CDTCON | DEM_CLRPTN_STY_PDTCON | DEM_CLRPTN_STY_BOTHOFF ), ( DEM_CLRPTN_CLR_BOTHON | DEM_CLRPTN_CLR_CDTCON | DEM_CLRPTN_CLR_PDTCON | DEM_CLRPTN_STY_BOTHOFF )  }},
#endif  /* ( DEM_TFTOCFFD_CLRTRIGGER_AGINGONLY_SUPPORT == STD_OFF ) */


#if ( DEM_PDTCFFD_CLRTRIGGER_TRIGGEROFF_SUPPORT == STD_ON )
/*  PDTC(TriggerOFF)*/{{ ( DEM_CLRPTN_CLR_BOTHON | DEM_CLRPTN_CLR_CDTCON | DEM_CLRPTN_CLR_PDTCON | DEM_CLRPTN_CLR_BOTHOFF ), ( DEM_CLRPTN_STY_BOTHON | DEM_CLRPTN_CLR_CDTCON | DEM_CLRPTN_STY_PDTCON | DEM_CLRPTN_CLR_BOTHOFF ), ( DEM_CLRPTN_CLR_BOTHON | DEM_CLRPTN_CLR_CDTCON | DEM_CLRPTN_CLR_PDTCON | DEM_CLRPTN_CLR_BOTHOFF )  }},
#endif  /* ( DEM_PDTCFFD_CLRTRIGGER_TRIGGEROFF_SUPPORT == STD_ON )  */
#if ( DEM_PDTCFFD_CLRTRIGGER_TRIGGEROFF_SUPPORT == STD_OFF )
/*  PDTC(NoFault)   */{{ ( DEM_CLRPTN_STY_BOTHON | DEM_CLRPTN_STY_CDTCON | DEM_CLRPTN_CLR_PDTCON | DEM_CLRPTN_CLR_BOTHOFF ), ( DEM_CLRPTN_STY_BOTHON | DEM_CLRPTN_CLR_CDTCON | DEM_CLRPTN_STY_PDTCON | DEM_CLRPTN_CLR_BOTHOFF ), ( DEM_CLRPTN_CLR_BOTHON | DEM_CLRPTN_CLR_CDTCON | DEM_CLRPTN_CLR_PDTCON | DEM_CLRPTN_CLR_BOTHOFF )  }},
#endif  /* ( DEM_PDTCFFD_CLRTRIGGER_TRIGGEROFF_SUPPORT == STD_OFF ) */

/*  CDTC            */{{ ( DEM_CLRPTN_STY_BOTHON | DEM_CLRPTN_STY_CDTCON | DEM_CLRPTN_CLR_PDTCON | DEM_CLRPTN_CLR_BOTHOFF ), ( DEM_CLRPTN_CLR_BOTHON | DEM_CLRPTN_CLR_CDTCON | DEM_CLRPTN_CLR_PDTCON | DEM_CLRPTN_CLR_BOTHOFF ), ( DEM_CLRPTN_CLR_BOTHON | DEM_CLRPTN_CLR_CDTCON | DEM_CLRPTN_CLR_PDTCON | DEM_CLRPTN_CLR_BOTHOFF )  }},
/*  FDCThreshold    */{{ ( DEM_CLRPTN_STY_BOTHON | DEM_CLRPTN_STY_CDTCON | DEM_CLRPTN_STY_PDTCON | DEM_CLRPTN_STY_BOTHOFF ), ( DEM_CLRPTN_CLR_BOTHON | DEM_CLRPTN_CLR_CDTCON | DEM_CLRPTN_STY_PDTCON | DEM_CLRPTN_STY_BOTHOFF ), ( DEM_CLRPTN_CLR_BOTHON | DEM_CLRPTN_CLR_CDTCON | DEM_CLRPTN_STY_PDTCON | DEM_CLRPTN_STY_BOTHOFF )  }}

};

#define DEM_STOP_SEC_CONST_CONFIG
#include <Dem_MemMap.h>


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
