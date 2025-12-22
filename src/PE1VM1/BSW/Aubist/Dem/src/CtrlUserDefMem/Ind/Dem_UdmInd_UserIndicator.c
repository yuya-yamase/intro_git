/* Dem_UdmInd_UserIndicator_c(v5-5-0)                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/UdInd_UserIndicator/CODE                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../inc/Dem_Rc_UdmMng.h"
#include "../../../inc/Dem_Udm_Ind.h"

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
#if ( DEM_USER_DEFINED_INDICATOR_SUPPORT == STD_ON )
#include "../../../inc/Dem_Rc_UdmMngTable.h"

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
/* Function Name | Dem_UdmInd_GetUserDefinedIndicator_UserDefMem            */
/* Description   | Get UserDefined Indicator Id Check Result                */
/* Preconditions | none                                                     */
/* Parameters    | [in] UdmEventIndex :                                     */
/*               |        Event index.                                      */
/*               | [out] IndicatorStatusPtr                                 */
/*               |          DEM_INDICATOR_OFF        : Indicator Off        */
/*               |          DEM_INDICATOR_CONTINUOUS : Indicator On         */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Success.                             */
/*               |        DEM_IRT_NG : Failed.                              */
/* Notes         |                                                          */
/*               |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmInd_GetUserDefinedIndicator_UserDefMem
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,      /* [PRMCHK:CALLER] */
    P2VAR( Dem_IndicatorStatusType, AUTOMATIC, AUTOMATIC ) IndicatorStatusPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) statusOfDTC;
    VAR( boolean, AUTOMATIC ) isWIRIndicator;
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInfoTableIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;

    retVal = DEM_IRT_NG;
    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;

    /* Get udm group index. */
    udmInfoTableIndex = Dem_CfgInfoUdm_GetMemoryDestination( UdmEventIndex );               /* [GUDCHK:CALLER]UdmEventIndex *//* [GUD:RET:IF_GUARDED: UdmEventIndex ]udmInfoTableIndex */
    udmGroupKindIndex = Dem_CfgInfoUdm_GetUserDefinedMemoryGroupKindIndexByEventIndex( udmInfoTableIndex, UdmEventIndex );

    if( udmGroupKindIndex < userDefinedMemoryNum )  /* [GUD:if]udmGroupKindIndex */
    {
#ifndef JGXSTACK
        Dem_UdmExcFncTable[udmGroupKindIndex].ExclusiveEnterFnc();      /* [GUD]udmGroupKindIndex */    /* waits completion of updating Diag record data by Dem_MainFunction.      */
        Dem_UdmExcFncTable[udmGroupKindIndex].ExclusiveExitFnc();       /* [GUD]udmGroupKindIndex */
#else   /* JGXSTACK */
        Dem_UdmExcEnterFnc_ForStack();
        Dem_UdmExcExitFnc_ForStack();
#endif  /* JGXSTACK */

        /* Attribute Indicator Use Check */
        isWIRIndicator  =   Dem_CfgInfoUdm_GetIsWIRIndicator( UdmEventIndex );
        if( isWIRIndicator == (boolean)TRUE )
        {
            retVal = DEM_IRT_OK;

            /* StatuOfDTC bit7 check */
            (void)Dem_UdmEventMngC_GetER_StatusOfDTC( UdmEventIndex, &statusOfDTC );   /* no return check required */
            if( ( statusOfDTC & DEM_UDS_STATUS_WIR ) != DEM_DTCSTATUS_BYTE_ALL_OFF )
            {
                *IndicatorStatusPtr = DEM_INDICATOR_CONTINUOUS;
            }
        }
    }

    return retVal;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_USER_DEFINED_INDICATOR_SUPPORT == STD_ON )   */
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )   */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
