/* Dem_DataMng_RecDt_TSFFList_OFF_c(v5-3-0)                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Dem_DataMng_RecDt_FFList_c/CODE                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>

#if ( DEM_TSFF_PM_SUPPORT == STD_OFF )
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


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>



/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_Data_CompareFreezeFrameListRecord                    */
/* Description   | compare data.                                            */
/* Preconditions |                                                          */
/* Parameters    | [in] FaultIndex :                                        */
/*               | [in] CheckFaultRecordPtr :                               */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK  : same.                               */
/*               |        DEM_IRT_NG  : different.                          */
/*               |                                                          */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMng_CmpWithTSFFListRecord
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,                                /* MISRA DEVIATION */
    P2CONST( Dem_FaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) CheckFaultRecordPtr      /* MISRA DEVIATION */
)
{
    /*  This is empty function for function switching.  */
    return DEM_IRT_OK;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif  /* (DEM_TSFF_PM_SUPPORT == STD_OFF)    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
