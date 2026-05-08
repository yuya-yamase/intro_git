/* Dem_ConfigInfo_PriMem_IUMPR_c(v5-10-0)                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/ConfigInfo_PriMem_IUMPR/CODE                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>

#if ( DEM_IUMPR_SUPPORT == STD_ON )
#include "../../../cfg/Dem_Obd_Cfg.h"
#include "../../../cfg/Dem_IUMPR_Cfg.h"
#include "../../../usr/Dem_IUMPR_NODI_Callout.h"
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

#if ( DEM_IUMPR_NODI_SELECT_BY_CALLOUT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetNODIInfo                                */
/* Description   | Get IUMPR NODI Info.                                     */
/* Preconditions | none                                                     */
/* Parameters    | [out] NODIValuePtr :                                     */
/*               |        Pointer to the area to get NODI Value.            */
/*               | [out] NODIGroupNumPtr :                                  */
/*               |        Pointer to the area to get NODI GroupNum.         */
/*               | [out] NODIOutputSizePtr :                                */
/*               |        Pointer to the area to get NODI OutputSize.       */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-10-0     | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_CfgInfoPm_GetNODIInfo
(
    P2VAR( Dem_u08_IUMPRNODIValueType, AUTOMATIC, AUTOMATIC ) NODIValuePtr,
    P2VAR( Dem_u08_IUMPRGroupIndexType, AUTOMATIC, AUTOMATIC ) NODIGroupNumPtr,
    P2VAR( Dem_u08_IUMPRNODIOutputSizeType, AUTOMATIC, AUTOMATIC ) NODIOutputSizePtr
)
{
    VAR( Dem_u08_OBDEngineType, AUTOMATIC ) engineType;
    VAR( Dem_u08_IUMPRNODIType, AUTOMATIC ) nodiByCallout;
    VAR( Dem_u08_IUMPRNODIValueType, AUTOMATIC ) tempNODIValue;
    VAR( Dem_u08_IUMPRGroupIndexType, AUTOMATIC ) tempNODIGroupNum;

    engineType = Dem_OBDEngineType;

    nodiByCallout = Dem_IUMPR_SelectNODIValue( engineType );

    if( engineType == (Dem_u08_OBDEngineType)DEM_IGNITION_SPARK )
    {
        switch( nodiByCallout )
        {
            case DEM_IUMPRNODI_SPARK_1C:
            case DEM_IUMPRNODI_SPARK_14:
            case DEM_IUMPRNODI_SPARK_10:
                /* No process */
                break;
            default:
                nodiByCallout = DEM_IUMPRNODI_SPARK_1C;
                break;
        }
    }
    else
    {
        switch( nodiByCallout )
        {
            case DEM_IUMPRNODI_COMPRESSION_12:
            case DEM_IUMPRNODI_COMPRESSION_10:
                /* No process */
                break;
            default:
                nodiByCallout = DEM_IUMPRNODI_COMPRESSION_12;
                break;
        }
    }

    tempNODIValue      = (Dem_u08_IUMPRNODIValueType)nodiByCallout;
    *NODIValuePtr      = tempNODIValue;

    tempNODIGroupNum   = ( tempNODIValue - (Dem_u08_IUMPRGroupIndexType)1U );
    *NODIGroupNumPtr   = ( tempNODIGroupNum >> (Dem_u08_IUMPRGroupIndexType)1U );     /* Divide By Two */

    *NODIOutputSizePtr = ( tempNODIValue << (Dem_u08_IUMPRNODIOutputSizeType)1U );    /* Multiply By Two */

    return;
}
#endif  /* ( DEM_IUMPR_NODI_SELECT_BY_CALLOUT_SUPPORT == STD_ON )  */

#if ( DEM_IUMPR_NODI_SELECT_BY_CALLOUT_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetNODIInfo                                */
/* Description   | Get IUMPR NODI Info.                                     */
/* Preconditions | none                                                     */
/* Parameters    | [out] NODIValuePtr :                                     */
/*               |        Pointer to the area to get NODI Value.            */
/*               | [out] NODIGroupNumPtr :                                  */
/*               |        Pointer to the area to get NODI GroupNum.         */
/*               | [out] NODIOutputSizePtr :                                */
/*               |        Pointer to the area to get NODI OutputSize.       */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-10-0     | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_CfgInfoPm_GetNODIInfo
(
    P2VAR( Dem_u08_IUMPRNODIValueType, AUTOMATIC, AUTOMATIC ) NODIValuePtr,
    P2VAR( Dem_u08_IUMPRGroupIndexType, AUTOMATIC, AUTOMATIC ) NODIGroupNumPtr,
    P2VAR( Dem_u08_IUMPRNODIOutputSizeType, AUTOMATIC, AUTOMATIC ) NODIOutputSizePtr
)
{
    *NODIValuePtr      = Dem_IUMPR_NODI_Value;
    *NODIGroupNumPtr   = Dem_IUMPR_NODI_GroupNum;
    *NODIOutputSizePtr = Dem_IUMPR_NODI_OutputSize;

    return;
}
#endif  /* ( DEM_IUMPR_NODI_SELECT_BY_CALLOUT_SUPPORT == STD_OFF )  */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_IUMPR_SUPPORT == STD_ON )   */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
