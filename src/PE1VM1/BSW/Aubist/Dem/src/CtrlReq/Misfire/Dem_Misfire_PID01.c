/* Dem_Misfire_PID01_c(v5-5-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Misfire_PID01/CODE                                    */
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
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_Pm_DataAvl.h"
#include "../../../inc/Dem_Pm_Misfire.h"
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
#include "Dem_Misfire_local.h"

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

#if ( DEM_WWH_OBD_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_Misfire_GetNumOfConfirmedCylAndMIL                   */
/* Description   | Get confirmed cylinder number and MIL status of misfire. */
/* Preconditions | none                                                     */
/* Parameters    | [out] DTCNumPtr :                                        */
/*               |       Number of misfire confirmed cylinder DTC           */
/*               | [out] MILStatusPtr :                                     */
/*               |       Misfire MIL status                                 */
/* Return Value  | void :                                                   */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_GetNumOfConfirmedCylAndMIL
(
    P2VAR( Dem_MisfireCylinderNumberType, AUTOMATIC, AUTOMATIC ) DTCNumPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) MILStatusPtr
)
{
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) bit3OnCyl;
    VAR( Dem_u08_MisfireIndStatusType, AUTOMATIC ) retGetMILStatus;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) numOfOnCylinderBit;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) loopCnt;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireCylinderNum;
    VAR( boolean, AUTOMATIC ) retDTCClerTarget;
    VAR( Dem_u08_MisfireKindBitType, AUTOMATIC ) availableMisfireKind;
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )   /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) setPID01MILStatusAtIndicatorBlinking;
#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )            */

    retDTCClerTarget = Dem_Misfire_JudgeDTCClearTarget();
    if( retDTCClerTarget == (boolean)FALSE )
    {
        numOfOnCylinderBit = (Dem_MisfireCylinderNumberType)0x00U;
        misfireCylinderNum = Dem_MisfireCylinderNum;

        availableMisfireKind    =   Dem_DataAvl_GetMisfireCylDTCAvailable();
        bit3OnCyl = Dem_Misfire_GetBit3Cylinder( availableMisfireKind );

        for( loopCnt = (Dem_MisfireCylinderNumberType)0U; loopCnt < misfireCylinderNum; loopCnt++ )
        {
            if( ( bit3OnCyl & (Dem_MisfireCylinderType)(DEM_MISFIRE_CHECK_CYLINDER_BIT << loopCnt) ) != DEM_MISFIRE_CYLINDER_NON )
            {
                numOfOnCylinderBit = numOfOnCylinderBit + (Dem_MisfireCylinderNumberType)1U;
            }
        }

        *DTCNumPtr = numOfOnCylinderBit;

        retGetMILStatus = Dem_Misfire_GetMILStatus( availableMisfireKind );
        if( ( retGetMILStatus & DEM_MISFIRE_IND_CONTINUOUS ) == DEM_MISFIRE_IND_CONTINUOUS )
        {
            *MILStatusPtr = (boolean)TRUE;
        }
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )   /*  [FuncSw]    */
        else if( ( retGetMILStatus & DEM_MISFIRE_IND_BLINKING ) == DEM_MISFIRE_IND_BLINKING )
        {
            setPID01MILStatusAtIndicatorBlinking    =   Dem_SetPID01MILStatusAtIndicatorBlinking;
            if ( setPID01MILStatusAtIndicatorBlinking == (boolean)TRUE )
            {
                *MILStatusPtr = (boolean)TRUE;
            }
            else
            {
                *MILStatusPtr = (boolean)FALSE;
            }
        }
#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )            */
        else
        {
            *MILStatusPtr = (boolean)FALSE;
        }
    }
    else
    {
        /* While clearing, it is judged that the number of confirmed failures is 0 and there is no MIL lighting. */
        /* Since it is not called from Dem_PID_ConfirmedDTCClear during clearing, it is a process that passes only when PID1 is acquired. */
        *DTCNumPtr = (Dem_MisfireCylinderNumberType)0x00U;
        *MILStatusPtr = (boolean)FALSE;
    }

    return;
}
#endif  /* ( DEM_WWH_OBD_SUPPORT == STD_OFF )   */

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
