/* Dem_EDR_CheckRecNumSupport_c(v5-5-0)                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/EDR_CheckRecNumSupport/CODE                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../inc/Dem_Pm_EDR.h"
#include "../../../cfg/Dem_EDR_Cfg.h"
#include "Dem_EDR_FilEDR_local.h"

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

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CONST
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_CONST
#include <Dem_MemMap.h>
/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_EDR_CheckExtendedDataNumberSupportByRange            */
/* Description   | check recordnumber support by range.                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :  EventStrgIndex                    */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : support.                                  */
/*               |        FALSE : not support.                              */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_EDR_CheckExtendedDataNumberSupportByRange
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_u08_EDRNumberSupBmpIndexType, AUTOMATIC )  edrSupportMin;
    VAR( Dem_u08_EDRNumberSupBmpIndexType, AUTOMATIC )  edrSupportMax;
    VAR( Dem_u08_EDRNumberSupBmpIndexType, AUTOMATIC )  edrSupportSearchIdx;
    VAR( Dem_u08_EDRSupDTCBmpIndexType, AUTOMATIC )     edrSupportPos;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC )        dtcBitmapTablePos;
    VAR( uint32, AUTOMATIC )                            searchDTCBitmapTable;
    VAR( uint32, AUTOMATIC )                            tableCheck;
    VAR( boolean, AUTOMATIC )                           retVal;

    /*  default : not supported.    */
    retVal = (boolean)FALSE;

    edrSupportMin = Dem_EDRSupportObdRecordNumberPos;                   /* [GUD:CFG]edrSupportMin */
    edrSupportMax = Dem_EDRSupportEndOfBehaviorAt0xFERecordNumberPos;   /* [GUD:CFG]edrSupportMax */

    if( edrSupportMin != DEM_EDRNUMBERSUPBMPINDEX_INVALID )
    {
        edrSupportPos           = (Dem_u08_EDRSupDTCBmpIndexType)( EventStrgIndex >> DEM_FILEDR_BITSHIFT_5 );   /* [GUD:CFG]edrSupportPos */
        dtcBitmapTablePos       = (Dem_u16_EventStrgIndexType)EventStrgIndex & DEM_FILEDR_INDEX_MASK_1F;
        tableCheck              = ( (uint32)0x00000001U << dtcBitmapTablePos );

        for( edrSupportSearchIdx = edrSupportMin; edrSupportSearchIdx <= edrSupportMax; edrSupportSearchIdx++)  /* [GUD:if]edrSupportSearchIdx */
        {
            searchDTCBitmapTable    = Dem_EDRNumberSupportBitmapTable[edrSupportSearchIdx].SupportDTCBitmapTable[edrSupportPos];    /* [GUD]edrSupportSearchIdx *//* [GUD]edrSupportSearchIdx */

            if( (searchDTCBitmapTable & tableCheck ) == tableCheck )
            {
                retVal=(boolean)TRUE;
                break;
            }
        }
    }

    return retVal;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
