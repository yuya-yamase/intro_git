/* Dem_PIDMng_PIDCalc_c(v5-5-0)                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Dem_PIDMng_PIDCalc/CODE                               */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_NvM_Cfg.h"
#include "../../../inc/Dem_Rc_PIDMng.h"
#include "../../../inc/Dem_Rc_ClrInfoMng.h"
#include "../../../inc/Dem_Rc_RecMngCmn.h"
#include "../../../inc/Dem_Rc_RecMngCmn_Table.h"
#include "Dem_PIDMng_local.h"

#if ( DEM_PID_CALC_DEMINTERNALPID_SUPPORT == STD_ON )

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
/* Function Name | Dem_PIDMngC_ClearDataOfPID21                             */
/* Description   | clear the value of PID21                                 */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PIDMngC_ClearDataOfPID21
( void )
{
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindPID;

    /* Starts exclusion. */
    SchM_Enter_Dem_PID();

    Dem_PIDRecord.PID21[DEM_PID_POS0] = DEM_PIDMNG_PIDDATA_INITVALUE;
    Dem_PIDRecord.PID21[DEM_PID_POS1] = DEM_PIDMNG_PIDDATA_INITVALUE;

    Dem_PIDRecord.StoreNvmPID21 = DEM_PID_STORE_NVM;

    Dem_PIDRecord.ClearID = Dem_ClrInfoMng_GetObdClearID();

    recMngCmnKindPID = Dem_RecMngCmnKindPID;
    Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindPID, ( Dem_u16_RecordIndexType )0U );

    /* Finishes exclusion. */
    SchM_Exit_Dem_PID();

    return;
}

/****************************************************************************/
/* Function Name | Dem_PIDMngC_ClearDataOfPID31                             */
/* Description   | clear the value of PID31                                 */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PIDMngC_ClearDataOfPID31
( void )
{
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindPID;
    /* Starts exclusion. */
    SchM_Enter_Dem_PID();

    Dem_PIDRecord.PID31[DEM_PID_POS0] = DEM_PIDMNG_PIDDATA_INITVALUE;
    Dem_PIDRecord.PID31[DEM_PID_POS1] = DEM_PIDMNG_PIDDATA_INITVALUE;

    Dem_PIDRecord.StoreNvmPID31 = DEM_PID_STORE_NVM;

    Dem_PIDRecord.ClearID = Dem_ClrInfoMng_GetObdClearID();

    recMngCmnKindPID = Dem_RecMngCmnKindPID;
    Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindPID, ( Dem_u16_RecordIndexType )0U );

    /* Finishes exclusion. */
    SchM_Exit_Dem_PID();

    return;
}

/****************************************************************************/
/* Function Name | Dem_PIDMngC_ClearDataOfPID4D                             */
/* Description   | clear the value of PID4D                                 */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PIDMngC_ClearDataOfPID4D
( void )
{
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindPID;

    /* Starts exclusion. */
    SchM_Enter_Dem_PID();

    Dem_PIDRecord.PID4D[DEM_PID_POS0] = DEM_PIDMNG_PIDDATA_INITVALUE;
    Dem_PIDRecord.PID4D[DEM_PID_POS1] = DEM_PIDMNG_PIDDATA_INITVALUE;

    Dem_PIDRecord.StoreNvmPID4D = DEM_PID_STORE_NVM;

    Dem_PIDRecord.ClearID = Dem_ClrInfoMng_GetObdClearID();

    recMngCmnKindPID = Dem_RecMngCmnKindPID;
    Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindPID, ( Dem_u16_RecordIndexType )0U );

    /* Finishes exclusion. */
    SchM_Exit_Dem_PID();

    return;
}

/****************************************************************************/
/* Function Name | Dem_PIDMngC_ClearDataOfPID4E                             */
/* Description   | clear the value of PID4E                                 */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PIDMngC_ClearDataOfPID4E
( void )
{
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindPID;

    /* Starts exclusion. */
    SchM_Enter_Dem_PID();

    Dem_PIDRecord.PID4E[DEM_PID_POS0] = DEM_PIDMNG_PIDDATA_INITVALUE;
    Dem_PIDRecord.PID4E[DEM_PID_POS1] = DEM_PIDMNG_PIDDATA_INITVALUE;

    Dem_PIDRecord.StoreNvmPID4E = DEM_PID_STORE_NVM;

    Dem_PIDRecord.ClearID = Dem_ClrInfoMng_GetObdClearID();

    recMngCmnKindPID = Dem_RecMngCmnKindPID;
    Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindPID, ( Dem_u16_RecordIndexType )0U );

    /* Finishes exclusion. */
    SchM_Exit_Dem_PID();

    return;
}

/****************************************************************************/
/* Function Name | Dem_PIDMng_InitCalcTargetPIDRecord                       */
/* Description   | Initialize calculation target PID record                 */
/* Preconditions | none                                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PIDMng_InitCalcTargetPIDRecord
( void )
{
    /*  initialize PID record.      */
    Dem_PIDRecord.PID21[DEM_PID_POS0] = DEM_PIDMNG_PIDDATA_INITVALUE;
    Dem_PIDRecord.PID21[DEM_PID_POS1] = DEM_PIDMNG_PIDDATA_INITVALUE;
    Dem_PIDRecord.PID31[DEM_PID_POS0] = DEM_PIDMNG_PIDDATA_INITVALUE;
    Dem_PIDRecord.PID31[DEM_PID_POS1] = DEM_PIDMNG_PIDDATA_INITVALUE;
    Dem_PIDRecord.PID4D[DEM_PID_POS0] = DEM_PIDMNG_PIDDATA_INITVALUE;
    Dem_PIDRecord.PID4D[DEM_PID_POS1] = DEM_PIDMNG_PIDDATA_INITVALUE;
    Dem_PIDRecord.PID4E[DEM_PID_POS0] = DEM_PIDMNG_PIDDATA_INITVALUE;
    Dem_PIDRecord.PID4E[DEM_PID_POS1] = DEM_PIDMNG_PIDDATA_INITVALUE;
    Dem_PIDRecord.StoreNvmPID21 = DEM_PID_STORE_NVM;
    Dem_PIDRecord.StoreNvmPID31 = DEM_PID_STORE_NVM;
    Dem_PIDRecord.StoreNvmPID4D = DEM_PID_STORE_NVM;
    Dem_PIDRecord.StoreNvmPID4E = DEM_PID_STORE_NVM;

    return;
}

/****************************************************************************/
/* Function Name | Dem_PIDMngC_ClearDataOfPIDCalcTarget                     */
/* Description   | Clears the PID value of the calculation target.          */
/* Preconditions | none                                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PIDMngC_ClearDataOfPIDCalcTarget
( void )
{
    Dem_PIDMngC_ClearDataOfPID21();
    Dem_PIDMngC_ClearDataOfPID31();
    Dem_PIDMngC_ClearDataOfPID4D();
    Dem_PIDMngC_ClearDataOfPID4E();

    return;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_PID_CALC_DEMINTERNALPID_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
