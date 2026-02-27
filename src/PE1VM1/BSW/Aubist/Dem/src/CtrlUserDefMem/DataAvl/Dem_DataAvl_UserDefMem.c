/* Dem_DataAvl_UserDefMem_c(v5-5-0)                                         */
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
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )

#include "../../../cfg/Dem_UserDefMem_Cfg.h"
#include "../../../inc/Dem_Udm_DataAvl.h"

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

#if ( DEM_EVENT_AVAILABILITY_SUPPORT == STD_ON )
static VAR( boolean, DEM_VAR_NO_INIT ) Dem_UdmDataAvl_EvtAvlData[DEM_UDMEVENT_CONFIGURE_NUM];
#endif /* DEM_EVENT_AVAILABILITY_SUPPORT == STD_ON */

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


/****************************************************************************/
/* External Functions(PreInit section)                                      */
/****************************************************************************/
#define DEM_START_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>

#if ( DEM_EVENT_AVAILABILITY_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_UdmData_PreInitForAvl                                */
/* Description   | Pre-initializes Dem_DataAvl.                             */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE_TRUST ) Dem_UdmData_PreInitForAvl       /*  PreInit section     */
( void )
{
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventIndex;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventConfigureNum;

    udmEventConfigureNum = Dem_UdmEventConfigureNum;

    for( udmEventIndex = (Dem_u16_UdmEventIndexType)0U; udmEventIndex < udmEventConfigureNum; udmEventIndex++ ) /* [GUD:for]udmEventIndex */
    {
        Dem_UdmDataAvl_EvtAvlData[ udmEventIndex ] = Dem_CfgInfoUdm_GetEventAvailable( udmEventIndex );         /* [GUD]udmEventIndex */
    }

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

#if ( DEM_EVENT_AVAILABILITY_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_UdmDataAvl_SetEvtAvl                                 */
/* Description   | Set the available status of a specific Event.            */
/* Preconditions | none                                                     */
/* Parameters    | [in] UdmEventIndex :                                     */
/*               |        Identification of an event.                       */
/*               | [in] AvailableStatus :                                   */
/*               |        This parameter specifies whether the respective   */
/*               |        Event shall be available (TRUE) or not (FALSE).   */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Setting event available is           */
/*               |                     supported.                           */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmDataAvl_SetEvtAvl
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( boolean, AUTOMATIC ) AvailableStatus
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventConfigureNum;

    retVal  =   DEM_IRT_NG;
    udmEventConfigureNum = Dem_UdmEventConfigureNum;

    if ( UdmEventIndex < udmEventConfigureNum )                             /* [GUD:if]UdmEventIndex */
    {
        Dem_UdmDataAvl_EvtAvlData[ UdmEventIndex ] = AvailableStatus;       /* [GUD]UdmEventIndex */
        retVal  =   DEM_IRT_OK;
    }
    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_UdmDataAvl_GetEvtAvl                                 */
/* Description   | Get the available status of a specific Event.            */
/* Preconditions | The specified event ID has been already registered.      */
/* Parameters    | [in] UdmEventIndex :                                     */
/*               |        Identification of an event.                       */
/* Return Value  | boolean                                                  */
/*               |        TRUE : Event is available.                        */
/*               |        FALSE : Event is not available.                   */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_UdmDataAvl_GetEvtAvl
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex
)
{
    VAR( boolean, AUTOMATIC ) retVal;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventConfigureNum;

    retVal = (boolean)FALSE;

    udmEventConfigureNum = Dem_UdmEventConfigureNum;

    if ( UdmEventIndex < udmEventConfigureNum )                                 /* [GUD:if]UdmEventIndex */
    {
        if( Dem_UdmDataAvl_EvtAvlData[ UdmEventIndex ] != (boolean)FALSE )      /* [GUD]UdmEventIndex */
        {
            retVal = (boolean)TRUE;
        }
    }

    return retVal;
}
#endif /* DEM_EVENT_AVAILABILITY_SUPPORT == STD_ON */

#if ( DEM_EVENT_AVAILABILITY_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_UdmDataAvl_GetEvtAvl                                 */
/* Description   | Get the available status of a specific Event.            */
/* Preconditions | The specified event ID has been already registered.      */
/* Parameters    | [in] UdmEventIndex :                                     */
/*               |        Identification of an event.                       */
/* Return Value  | boolean                                                  */
/*               |        TRUE : Event is available.                        */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_UdmDataAvl_GetEvtAvl
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex             /* MISRA DEVIATION */
)
{
    /*  This is empty function for function switching.  */

    return (boolean)TRUE;
}
#endif /* DEM_EVENT_AVAILABILITY_SUPPORT == STD_OFF */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
