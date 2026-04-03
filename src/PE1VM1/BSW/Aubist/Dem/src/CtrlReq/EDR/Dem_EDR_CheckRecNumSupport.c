/* Dem_EDR_CheckRecNumSupport_c(v5-8-0)                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
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
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_Pm_EDR.h"
#include "../../../cfg/Dem_Misfire_Cfg.h"
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

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
static FUNC( boolean, DEM_CODE ) Dem_EDR_JudgeSupportSpecExtendedDataNumber
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_u08_EDRRecordNumberType, AUTOMATIC ) ExtendedDataNumber
);
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  */

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
/*               | [in] DTCValue :                                          */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : support.                                  */
/*               |        FALSE : not support.                              */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-8-0      | branch changed.                                          */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_EDR_CheckExtendedDataNumberSupportByRange
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue             /* MISRA DEVIATION */
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
    VAR( boolean, AUTOMATIC )                           eventOBDKind;
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC )                           retJudgeSupportNumber;
    VAR( Dem_u08_EDRRecordNumberType, AUTOMATIC )       extendedDataNumber;
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )           */

    /*  default : not supported.    */
    retVal = (boolean)FALSE;

    /*----------------------------------------------------------*/
    /*  Check if the event can have a OBD record number.        */
    /*----------------------------------------------------------*/
    eventOBDKind = Dem_CfgInfoPm_CheckEventKindOfOBD_InEvtStrgGrp( EventStrgIndex );
    if ( eventOBDKind == (boolean)TRUE )
    {
        /*----------------------------------------------------------*/
        /*  Check support OBD record number.                        */
        /*----------------------------------------------------------*/
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

                if( ( searchDTCBitmapTable & tableCheck ) == tableCheck )
                {
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
                    /*----------------------------------------------------------*/
                    /*  Check if the event can have a Specific record number.   */
                    /*----------------------------------------------------------*/
                    extendedDataNumber      =   Dem_EDRNumberSupportBitmapTable[edrSupportSearchIdx].ExtendDataRecordNumber;            /* [GUD]edrSupportSearchIdx */
                    retJudgeSupportNumber   =   Dem_EDR_JudgeSupportSpecExtendedDataNumber( EventStrgIndex, DTCValue, extendedDataNumber );

                    if ( retJudgeSupportNumber == (boolean)TRUE )
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )           */
                    {
                        retVal = (boolean)TRUE;
                        break;
                    }
                }
            }
        }
    }

    return retVal;
}

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
/****************************************************************************/
/* Function Name | Dem_EDR_JudgeSupportSpecExtendedDataNumber               */
/* Description   | judgee support recordnumber                              */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in] DTCValue :                                          */
/*               | [in] ExtendedDataNumber :                                */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : support.                                  */
/*               |        FALSE : not support.                              */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-8-0      | new created.                                             */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_EDR_JudgeSupportSpecExtendedDataNumber
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_u08_EDRRecordNumberType, AUTOMATIC ) ExtendedDataNumber
)
{
    VAR( boolean, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) misfireEventKind;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireCylinder;
    VAR( Dem_u08_MisfireFilteredEDRType, AUTOMATIC ) misfireFilteredEDRN92;

    retVal  =   (boolean)TRUE;

    if( ExtendedDataNumber == DEM_EDR_RECNUM_92 )
    {
        /*----------------------------------*/
        /*  ExtendedDataNumber == 0x92      */
        /*----------------------------------*/
        misfireEventKind    =   Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( EventStrgIndex );
        if ( misfireEventKind == (boolean)TRUE )
        {
            /*----------------------------------*/
            /*  It's Misfire event.             */
            /*----------------------------------*/
            misfireCylinder =   Dem_CfgInfoPm_GetMisfireCylinderNumberByUdsDTC( DTCValue );
            if ( misfireCylinder == DEM_MISFIRE_CYL_NUM_RM )
            {
                /*----------------------------------*/
                /*  It's Randam Cylinder number.    */
                /*----------------------------------*/
                misfireFilteredEDRN92 = Dem_MisfireFilteredEDRN92;
                if( misfireFilteredEDRN92 == DEM_MF_RM_CYL_NOT_OUTPUT )
                {
                    /*----------------------------------*/
                    /*  NOT_OUTPUT == not support.      */
                    /*----------------------------------*/
                    retVal  =   (boolean)FALSE;
                }
            }
        }
    }

    return retVal;
}
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-8-0         :2024-10-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
