/* Dem_DataAvl_c(v5-5-0)                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataAvl/CODE                                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../inc/Dem_CmnLib_DataAvl.h"
#include "../../../inc/Dem_Pm_DataAvl.h"
#include "../../../inc/Dem_Udm_DataAvl.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"

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
/* External Functions(PreInit section)                                      */
/****************************************************************************/
#define DEM_START_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>


#if ( DEM_EVENT_AVAILABILITY_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DataAvl_PreInitForAvl                                */
/* Description   | Pre-initializes Dem_DataAvl.                             */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE_TRUST ) Dem_DataAvl_PreInitForAvl       /*  PreInit section     */
( void )
{
    Dem_DataAvl_PreInitForAvl_PriMem();

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
    /*  call UserDefinedMemory      */
    Dem_UdmData_PreInitForAvl();
#endif  /*   ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )        */

    return;
}
#endif /* DEM_EVENT_AVAILABILITY_SUPPORT == STD_ON */


#define DEM_STOP_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_DataAvl_GetEvtAvl                                    */
/* Description   | Get the available status of a specific Event.            */
/* Preconditions | The specified event ID has been already registered.      */
/* Parameters    | [in] EventCtrlIndex :                                    */
/*               |        Identification of an event.                       */
/* Return Value  | boolean                                                  */
/*               |        TRUE : Event is available.                        */
/*               |        FALSE : Event is not available.                   */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_DataAvl_GetEvtAvlCommon
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex
)
{
    VAR( boolean, AUTOMATIC ) retVal;

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvEventIndex;
    VAR( Dem_u08_MemoryKindType, AUTOMATIC ) retMemoryKind;

    retVal = (boolean)FALSE;

    /* Check Memory Kind (Primary or UserDefMem) */
    retMemoryKind = Dem_CfgInfoCmn_CheckMemoryTypeFromEventCtrlIndex( EventCtrlIndex );

    if( retMemoryKind != DEM_MEMKIND_PRIMARY )
    {
        retCnvEventIndex = Dem_CfgInfoUdm_CnvEventCtrlIndexToUdmEventIndex( EventCtrlIndex, &udmEventIndex );       /* [GUD:RET:DEM_IRT_OK] udmEventIndex */
        if ( retCnvEventIndex == DEM_IRT_OK )
        {
            retVal = Dem_UdmDataAvl_GetEvtAvl( udmEventIndex );         /* [GUD] udmEventIndex */
        }
    }
    else
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )          */
    {
        retVal  =   Dem_DataAvl_GetEvtAvl( EventCtrlIndex );
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_DataAvl_ValidateDTC                                  */
/* Description   | Check DTC value.                                         */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCValue :                                          */
/*               |        The specified DTC value.                          */
/* Return Value  | boolean                                                  */
/*               |        TRUE : DTC value is valid.                        */
/*               |        FALSE : DTC value is invalid.                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_DataAvl_ValidateDTC
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue
)
{
    VAR( boolean, AUTOMATIC ) retVal;

    retVal = (boolean)FALSE;

    if( DTCValue >= DEM_DTC_VALUE_MIN )
    {
        if( DTCValue <= DEM_DTC_VALUE_MAX )
        {
            retVal = (boolean)TRUE;
        }
        else
        {
            /* No process */
        }
    }
    else
    {
        /* No process */
    }

    return retVal;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v2-0-0         :2019-03-27                                              */
/*  v4-0-0         :2020-03-19                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
