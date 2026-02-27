/* Dem_RecMngCmn_c(v5-5-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/RecMngCmn/CODE                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/



/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../cfg/Dem_NvM_Cfg.h"
#include "../../../inc/Dem_Md_ModeMng.h"
#include "../../../inc/Dem_Rc_RecMngCmn.h"
#include "../../../inc/Dem_Rc_RecMngCmn_Table.h"

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_OFF )
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
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_RecMngCmn_SetNvMWriteStatus                          */
/* Description   | Change the value of NvMWriteStatus.                      */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordKind :                                        */
/*               | [in] RecordIndex :                                       */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_RecMngCmn_SetNvMWriteStatus
(
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) RecordKind,    /* MISRA DEVIATION */
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) RecordIndex    /* MISRA DEVIATION */
)
{
    /*  This is empty function for funtion switching.       */
    return;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_OFF- */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
