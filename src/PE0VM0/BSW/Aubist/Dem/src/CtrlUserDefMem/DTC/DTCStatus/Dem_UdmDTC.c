/* Dem_UdmDTC_c(v5-5-0)                                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/UdmDTC/CODE                                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../../cfg/Dem_Cfg.h"
#include "../../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../../inc/Dem_CmnLib_Control.h"
#include "../../../../inc/Dem_Udm_DataAvl.h"
#include "../../../../inc/Dem_Udm_Data.h"

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )

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
/* Function Name | Dem_UdmDTC_JudgeUdmDTCClearTarget                        */
/* Description   | Judge if UdmDTCinfo is a target for Clear                */
/* Preconditions | none                                                     */
/* Parameters    | [in] UdmEventIndex :                                     */
/*               |        The Udm event index                               */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : target to clear                           */
/*               |        FALSE : not target to clear                       */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_UdmDTC_JudgeUdmDTCClearTarget
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex
)
{
    VAR( boolean, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) execClearDTC;
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) getDTCGroup;
    VAR( Dem_DTCOriginType, AUTOMATIC ) getDTCOrigin;
    VAR( Dem_DTCOriginType, AUTOMATIC ) memConfigId;
    VAR( Dem_DTCOriginType, AUTOMATIC ) memCheckId;

    retVal = (boolean)FALSE;

    execClearDTC = Dem_Control_CheckExecClearDTCProcess();

    if( execClearDTC == (boolean)TRUE )
    {
        Dem_Control_GetClearType( &getDTCGroup, &getDTCOrigin);

        if( (getDTCOrigin & ( Dem_DTCOriginType )DEM_DTC_ORIGIN_USERDEFINED_MEMORY) == ( Dem_DTCOriginType )DEM_DTC_ORIGIN_USERDEFINED_MEMORY )
        {
            memCheckId  =   getDTCOrigin & ~( DEM_DTC_ORIGIN_USERDEFINED_MEMORY );
            memConfigId = ( Dem_DTCOriginType )Dem_CfgInfoUdm_GetUserDefinedMemoryIdentifier( UdmEventIndex );
            if ( memConfigId == memCheckId )
            {
                retVal = (boolean)TRUE;
            }
        }
    }

    return retVal;
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )      */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
