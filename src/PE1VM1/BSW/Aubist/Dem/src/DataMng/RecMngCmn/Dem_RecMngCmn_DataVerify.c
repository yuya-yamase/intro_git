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
#include "../../../usr/Dem_SavedZone_Callout.h"

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

static VAR( Dem_u16_RecordKindIndexType, DEM_VAR_NO_INIT ) Dem_RecMngCmnRecIndex;

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_RecMngCmn_DataVerify                                 */
/* Description   |                                                          */
/* Preconditions | Nv Block read completed.                                 */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_RecMngCmn_InitDataVerify
( void )
{
    /*  start of verify record.                 */
    Dem_RecMngCmnRecIndex   =   (Dem_u16_RecordKindIndexType)0U;

    return ;
}

/****************************************************************************/
/* Function Name | Dem_RecMngCmn_DataVerify                                 */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |          DEM_IRT_OK      : DataVerify completed.         */
/*               |          DEM_IRT_PENDING : Continue DataVerify.          */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_RecMngCmn_DataVerify
( void )
{
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnRecIndex;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindMax;
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) recordFieldIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retval;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVerifyFnc;

    recMngCmnKindMax = Dem_RecMngCmnKindMax;
    retval  =   DEM_IRT_OK;

    /*--------------------------------------*/
    /*  notify SAVED_ZONE update - start.   */
    Dem_NotifySavedZoneUpdate_Enter();      /*  notify start :  savedzone area will be update.  */
    /*--------------------------------------*/

    /* DataVerify record. */
    for( recMngCmnRecIndex = Dem_RecMngCmnRecIndex; recMngCmnRecIndex < recMngCmnKindMax; recMngCmnRecIndex++ ) /* [GUD:for]recMngCmnRecIndex */
    {
        recordFieldIndex = Dem_RecordFieldIndexTableForMemSyncFunc[recMngCmnRecIndex];  /* [GUD]recMngCmnRecIndex */

#ifndef JGXSTACK
        /*  call record DataVerify function.        */
        retVerifyFnc = Dem_RecordInitFuncTable[recMngCmnRecIndex].DataVerifyFnc( recordFieldIndex );    /* [GUD]recMngCmnRecIndex */
#else   /* JGXSTACK */
        retVerifyFnc = Dem_RecMngCmnDataVerifyFnc_ForStack( recordFieldIndex );
#endif  /* JGXSTACK */

        /*  continute DataVerify mode or not.   */
        if ( retVerifyFnc == DEM_IRT_PENDING )
        {
            /*  continue DataVerify mode.       */
            retval  =   DEM_IRT_PENDING;

            /*  update verify record index.     */
            Dem_RecMngCmnRecIndex   =   recMngCmnRecIndex;

            /*  continue to next cycle.         */
            break;
        }
    }
    /*--------------------------------------*/
    /*  notify SAVED_ZONE update - end.     */
    Dem_NotifySavedZoneUpdate_Exit();       /*  notify end :  savedzone area will be update.    */
    /*--------------------------------------*/

    return retval;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
