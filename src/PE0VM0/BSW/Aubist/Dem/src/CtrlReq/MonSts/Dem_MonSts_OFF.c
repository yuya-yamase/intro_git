/* Dem_MonSts_c(v5-3-0)                                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/MonSts/CODE                                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#if ( DEM_TRIGGER_FIM_REPORTS == STD_OFF )
#include <Dem/Dem_Common.h>
#include "../../../inc/Dem_Pm_MonSts.h"

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
/* Function Name | Dem_MonSts_ReCalcStart                                   */
/* Description   | pretreatment for recalculation                           */
/* Preconditions | none                                                     */
/* Parameters    | [in]  ReCalcFlg                                          */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MonSts_ReCalcStart
(
    VAR( boolean, AUTOMATIC ) ReCalcFlg                         /* MISRA DEVIATION */
)
{
    /* This is empty function . */
    /* No process */

    return;
}


/****************************************************************************/
/* Function Name | Dem_MonSts_ReCalcProc                                    */
/* Description   | recalculation                                            */
/* Preconditions | none                                                     */
/* Parameters    | [in] InitType                                            */
/* Return Value  | Dem_u08_InternalReturnType DEM_IRT_OK                    */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MonSts_ReCalcProc
(
    VAR( Dem_u08_MonStsReCalcType, AUTOMATIC ) InitType                            /* MISRA DEVIATION */
)
{
    /* This is empty function . */
    /* No process */

    return DEM_IRT_OK;
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif  /* ( DEM_TRIGGER_FIM_REPORTS == STD_OFF ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
