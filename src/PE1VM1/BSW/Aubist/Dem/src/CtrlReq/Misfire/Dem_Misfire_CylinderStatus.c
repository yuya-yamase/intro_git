/* Dem_Misfire_CylinderStatus_c(v5-5-0)                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Misfire_CylinderStatus/CODE                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )

#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_DTC_DTCStatus.h"
#include "../../../inc/Dem_Pm_DataAvl.h"
#include "../../../inc/Dem_Pm_Misfire.h"
#include "../../../inc/Dem_Rc_MisfireMng.h"
#include "../../../inc/Dem_Rc_DataMng.h"
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

static FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_Misfire_GetBit4Cylinder_Emission
( void );
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
static FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_Misfire_GetBit4Cylinder_CAT
( void );
static FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_Misfire_GetBit4Cylinder_Both
( void );
#endif  /*  ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  */

static FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_Misfire_GetBit6Cylinder_Emission
( void );
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
static FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_Misfire_GetBit6Cylinder_CAT
( void );
static FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_Misfire_GetBit6Cylinder_Both
( void );
#endif  /*  ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  */

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
/* Function Name | Dem_Misfire_GetBit0Cylinder                              */
/* Description   | Get Cylinder with StatusOfDTC Bit0 standing              */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_MisfireCylinderType                                  */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_Misfire_GetBit0Cylinder
(
    VAR( Dem_u08_MisfireKindBitType, AUTOMATIC ) availableMisfireKind
)
{
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndex;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireEventNum;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) retCylinder;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) getCylinder;
    VAR( Dem_u08_MisfireKindBitType, AUTOMATIC ) availCheck;

    /*----------------------------------------------------------------------------------*/
    /*  xx Available check. xxx                                                         */
    /*  DEM_MISFIRE_KINDBIT_FIRST : search start bit.(== DEM_MISFIRE_KINDBIT_EMISSION)  */
    /*      misfireIndex == 0U : DEM_MISFIRE_KINDBIT_EMISSION(0x01)                     */
    /*      misfireIndex == 1U : DEM_MISFIRE_KINDBIT_CAT     (0x02)                     */
    /*  so, check bit(availCheck) is left shifted.                                      */
    /*----------------------------------------------------------------------------------*/

    availCheck      =   DEM_MISFIRE_KINDBIT_FIRST;
    retCylinder = DEM_MISFIRE_CYLINDER_NON;
    misfireEventNum = Dem_MisfireEventNum;

    for( misfireIndex = (Dem_u16_MisfireStrgIndexType)0U; misfireIndex < misfireEventNum; misfireIndex++ )
    {
        if (( availCheck & availableMisfireKind ) == availCheck )
        {
            getCylinder = Dem_MisfireMng_GetFailedCyl( misfireIndex );
            retCylinder = retCylinder | getCylinder;
        }
        availCheck  =   availCheck << (Dem_u08_MisfireKindBitType)1U;
    }

    retCylinder = Dem_CfgInfoPm_MergeMultipleCylinderBit( retCylinder );

    return retCylinder;
}

/****************************************************************************/
/* Function Name | Dem_Misfire_GetBit1Cylinder                              */
/* Description   | Get Cylinder with StatusOfDTC Bit1 standing              */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_MisfireCylinderType                                  */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_Misfire_GetBit1Cylinder
(
    VAR( Dem_u08_MisfireKindBitType, AUTOMATIC ) availableMisfireKind
)
{
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndex;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireEventNum;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) retCylinder;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) getCylinder;
    VAR( Dem_u08_MisfireKindBitType, AUTOMATIC ) availCheck;

    /*----------------------------------------------------------------------------------*/
    /*  xx Available check. xxx                                                         */
    /*  DEM_MISFIRE_KINDBIT_FIRST : search start bit.(== DEM_MISFIRE_KINDBIT_EMISSION)  */
    /*      misfireIndex == 0U : DEM_MISFIRE_KINDBIT_EMISSION(0x01)                     */
    /*      misfireIndex == 1U : DEM_MISFIRE_KINDBIT_CAT     (0x02)                     */
    /*  so, check bit(availCheck) is left shifted.                                      */
    /*----------------------------------------------------------------------------------*/

    availCheck      =   DEM_MISFIRE_KINDBIT_FIRST;
    retCylinder = DEM_MISFIRE_CYLINDER_NON;
    misfireEventNum = Dem_MisfireEventNum;

    for( misfireIndex = (Dem_u16_MisfireStrgIndexType)0U; misfireIndex < misfireEventNum; misfireIndex++ )
    {
        if (( availCheck & availableMisfireKind ) == availCheck )
        {
            getCylinder = Dem_MisfireMng_GetAFCylThisOC( misfireIndex );
            retCylinder = retCylinder | getCylinder;
        }
        availCheck  =   availCheck << (Dem_u08_MisfireKindBitType)1U;
    }

    retCylinder = Dem_CfgInfoPm_MergeMultipleCylinderBit( retCylinder );

    return retCylinder;
}

/****************************************************************************/
/* Function Name | Dem_Misfire_GetBit2Cylinder                              */
/* Description   | Get Cylinder with StatusOfDTC Bit2 standing              */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_MisfireCylinderType                                  */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_Misfire_GetBit2Cylinder
(
    VAR( Dem_u08_MisfireKindBitType, AUTOMATIC ) availableMisfireKind
)
{
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndex;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireEventNum;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) retCylinder;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) getCylinder;
    VAR( Dem_u08_MisfireKindBitType, AUTOMATIC ) availCheck;

    /*----------------------------------------------------------------------------------*/
    /*  xx Available check. xxx                                                         */
    /*  DEM_MISFIRE_KINDBIT_FIRST : search start bit.(== DEM_MISFIRE_KINDBIT_EMISSION)  */
    /*      misfireIndex == 0U : DEM_MISFIRE_KINDBIT_EMISSION(0x01)                     */
    /*      misfireIndex == 1U : DEM_MISFIRE_KINDBIT_CAT     (0x02)                     */
    /*  so, check bit(availCheck) is left shifted.                                      */
    /*----------------------------------------------------------------------------------*/

    availCheck      =   DEM_MISFIRE_KINDBIT_FIRST;
    retCylinder = DEM_MISFIRE_CYLINDER_NON;
    misfireEventNum = Dem_MisfireEventNum;

    for( misfireIndex = (Dem_u16_MisfireStrgIndexType)0U; misfireIndex < misfireEventNum; misfireIndex++ )
    {
        if (( availCheck & availableMisfireKind ) == availCheck )
        {
            getCylinder = Dem_MisfireMng_GetAccumPendingCyl( misfireIndex );
            retCylinder = retCylinder | getCylinder;
        }
        availCheck  =   availCheck << (Dem_u08_MisfireKindBitType)1U;
    }

    retCylinder = Dem_CfgInfoPm_MergeMultipleCylinderBit( retCylinder );

    return retCylinder;
}

/****************************************************************************/
/* Function Name | Dem_Misfire_GetBit3Cylinder                              */
/* Description   | Get Cylinder with StatusOfDTC Bit3 standing              */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_MisfireCylinderType                                  */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_Misfire_GetBit3Cylinder
(
    VAR( Dem_u08_MisfireKindBitType, AUTOMATIC ) availableMisfireKind
)
{
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndex;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireEventNum;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) retCylinder;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) getCylinder;
    VAR( Dem_u08_MisfireKindBitType, AUTOMATIC ) availCheck;

    /*----------------------------------------------------------------------------------*/
    /*  xx Available check. xxx                                                         */
    /*  DEM_MISFIRE_KINDBIT_FIRST : search start bit.(== DEM_MISFIRE_KINDBIT_EMISSION)  */
    /*      misfireIndex == 0U : DEM_MISFIRE_KINDBIT_EMISSION(0x01)                     */
    /*      misfireIndex == 1U : DEM_MISFIRE_KINDBIT_CAT     (0x02)                     */
    /*  so, check bit(availCheck) is left shifted.                                      */
    /*----------------------------------------------------------------------------------*/

    availCheck      =   DEM_MISFIRE_KINDBIT_FIRST;
    retCylinder = DEM_MISFIRE_CYLINDER_ALLBITOFF;
    misfireEventNum = Dem_MisfireEventNum;

    for( misfireIndex = (Dem_u16_MisfireStrgIndexType)0U; misfireIndex < misfireEventNum; misfireIndex++ )
    {
        if (( availCheck & availableMisfireKind ) == availCheck )
        {
            getCylinder = Dem_MisfireMng_GetAccumConfirmedCyl( misfireIndex );
            retCylinder = retCylinder | getCylinder;
        }
        availCheck  =   availCheck << (Dem_u08_MisfireKindBitType)1U;
    }

    retCylinder = Dem_CfgInfoPm_MergeMultipleCylinderBit( retCylinder );

    return retCylinder;
}

/****************************************************************************/
/* Function Name | Dem_Misfire_GetBit4Cylinder                              */
/* Description   | Get Cylinder with StatusOfDTC Bit4 standing              */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_MisfireCylinderType                                  */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_Misfire_GetBit4Cylinder
(
    VAR( Dem_u08_MisfireKindBitType, AUTOMATIC ) availableMisfireKind
)
{
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) retCylinder;
    retCylinder = DEM_MISFIRE_CYLINDER_ALLBITON;

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    if (( availableMisfireKind & DEM_MISFIRE_KINDBIT_BOTH ) == DEM_MISFIRE_KINDBIT_BOTH )
    {
        retCylinder =   Dem_Misfire_GetBit4Cylinder_Both();
    }
    else
    if (( availableMisfireKind & DEM_MISFIRE_KINDBIT_CAT ) == DEM_MISFIRE_KINDBIT_CAT )
    {
        retCylinder =   Dem_Misfire_GetBit4Cylinder_CAT();
    }
    else
#endif  /*  ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  */
    if (( availableMisfireKind & DEM_MISFIRE_KINDBIT_EMISSION ) == DEM_MISFIRE_KINDBIT_EMISSION )
    {
        retCylinder =   Dem_Misfire_GetBit4Cylinder_Emission();
    }
    else
    {
        /*  no process.     */
    }
    return retCylinder;
}

/****************************************************************************/
/* Function Name | Dem_Misfire_GetBit4Cylinder_Emission                     */
/* Description   | Get Cylinder with StatusOfDTC Bit4 standing              */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_MisfireCylinderType                                  */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | rename from Dem_Misfire_GetBit4Cylinder(DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_OFF)(v5-3-0). */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_Misfire_GetBit4Cylinder_Emission
( void )
{
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) getStatusOfDTCEmission;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) retCylinder;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) misfireEmissionEventStrgIndex;

    retCylinder = DEM_MISFIRE_CYLINDER_ALLBITOFF;

    misfireEmissionEventStrgIndex = Dem_CfgInfoPm_GetEventStrgIndex_MisfireEmission();
    getStatusOfDTCEmission = DEM_DTCSTATUS_BYTE_ALL_OFF;

    (void)Dem_DataMngC_GetER_StatusOfDTC( misfireEmissionEventStrgIndex, &getStatusOfDTCEmission );   /* no return check required */

    /* When only EMISSION is configured */
    if( ( getStatusOfDTCEmission & DEM_UDS_STATUS_TNCSLC ) == DEM_UDS_STATUS_TNCSLC )   /*  statusOfDTC : bit4  */
    {
        retCylinder = DEM_MISFIRE_CYLINDER_ALLBITON;
    }

    return retCylinder;
}

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Misfire_GetBit4Cylinder_CAT                          */
/* Description   | Get Cylinder with StatusOfDTC Bit4 standing              */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_MisfireCylinderType                                  */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_Misfire_GetBit4Cylinder_Emission. */
/****************************************************************************/
static FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_Misfire_GetBit4Cylinder_CAT
( void )
{
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) getStatusOfDTCCAT;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) retCylinder;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) misfireCATEventStrgIndex;

    retCylinder = DEM_MISFIRE_CYLINDER_ALLBITOFF;

    misfireCATEventStrgIndex = Dem_CfgInfoPm_GetEventStrgIndex_MisfireCAT();
    getStatusOfDTCCAT = DEM_DTCSTATUS_BYTE_ALL_OFF;

    (void)Dem_DataMngC_GetER_StatusOfDTC( misfireCATEventStrgIndex, &getStatusOfDTCCAT );   /* no return check required */

    /* When only EMISSION is configured */
    if( ( getStatusOfDTCCAT & DEM_UDS_STATUS_TNCSLC ) == DEM_UDS_STATUS_TNCSLC )   /*  statusOfDTC : bit4  */
    {
        retCylinder = DEM_MISFIRE_CYLINDER_ALLBITON;
    }

    return retCylinder;
}

/****************************************************************************/
/* Function Name | Dem_Misfire_GetBit4Cylinder                              */
/* Description   | Get Cylinder with StatusOfDTC Bit4 standing              */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_MisfireCylinderType                                  */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | rename from Dem_Misfire_GetBit4Cylinder( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )(v5-3-0). */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_Misfire_GetBit4Cylinder_Both
( void )
{
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) getStatusOfDTCCAT;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) getStatusOfDTCEmission;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) retCylinder;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) misfireCATEventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) misfireEmissionEventStrgIndex;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireCATMisfireStrgIndex;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireEmissionMisfireStrgIndex;

    misfireCATEventStrgIndex            = Dem_CfgInfoPm_GetEventStrgIndex_MisfireCAT();
    misfireEmissionEventStrgIndex       = Dem_CfgInfoPm_GetEventStrgIndex_MisfireEmission();
    misfireCATMisfireStrgIndex          = Dem_CfgInfoPm_GetMisfireStrgIndex_MisfireCAT();
    misfireEmissionMisfireStrgIndex     = Dem_CfgInfoPm_GetMisfireStrgIndex_MisfireEmission();

    retCylinder = DEM_MISFIRE_CYLINDER_ALLBITOFF;
    getStatusOfDTCEmission = DEM_DTCSTATUS_BYTE_ALL_OFF;

    (void)Dem_DataMngC_GetER_StatusOfDTC( misfireEmissionEventStrgIndex, &getStatusOfDTCEmission );   /* no return check required */

    getStatusOfDTCCAT = DEM_DTCSTATUS_BYTE_ALL_OFF;
    /* When EMISSION and CAT are configured */
    (void)Dem_DataMngC_GetER_StatusOfDTC( misfireCATEventStrgIndex, &getStatusOfDTCCAT );    /* no return check required */

    if( ( getStatusOfDTCEmission & DEM_UDS_STATUS_TNCSLC ) == DEM_UDS_STATUS_TNCSLC )       /*  statusOfDTC : bit4  */
    {
        /* When Bit4 of EMISSION is standing */
        if( ( getStatusOfDTCCAT & DEM_UDS_STATUS_TNCSLC ) == DEM_UDS_STATUS_TNCSLC )        /*  statusOfDTC : bit4  */
        {
            /* When Bit4 of CAT is also standing */
            retCylinder = DEM_MISFIRE_CYLINDER_ALLBITON;
        }
        else
        {
            /* When Bit4 of CAT is not standing */
            retCylinder = Dem_MisfireMng_GetATNCCySinceClear( misfireCATMisfireStrgIndex );
            retCylinder = Dem_CfgInfoPm_MergeMultipleCylinderBit( retCylinder );
            /* After bit inversion, drop the bit that is out of the valid range. */
            retCylinder = ((Dem_MisfireCylinderType)(~retCylinder)) & Dem_MisfireAvailableCylinder;
        }
    }
    else
    {
        /* When Bit4 of EMISSION is not standing */
        if( ( getStatusOfDTCCAT & DEM_UDS_STATUS_TNCSLC ) == DEM_UDS_STATUS_TNCSLC )        /*  statusOfDTC : bit4  */
        {
            /* When Bit4 of CAT is standing */
            retCylinder = Dem_MisfireMng_GetATNCCySinceClear( misfireEmissionMisfireStrgIndex );
            retCylinder = Dem_CfgInfoPm_MergeMultipleCylinderBit( retCylinder );
            /* After bit inversion, drop the bit that is out of the valid range. */
            retCylinder = ((Dem_MisfireCylinderType)(~retCylinder)) & Dem_MisfireAvailableCylinder;
        }
    }

    return retCylinder;
}
#endif  /*  ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  */

/****************************************************************************/
/* Function Name | Dem_Misfire_GetBit5Cylinder                              */
/* Description   | Get Cylinder with StatusOfDTC Bit5 standing              */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_MisfireCylinderType                                  */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_Misfire_GetBit5Cylinder
(
    VAR( Dem_u08_MisfireKindBitType, AUTOMATIC ) availableMisfireKind
)
{
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndex;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireEventNum;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) retCylinder;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) getCylinder;
    VAR( Dem_u08_MisfireKindBitType, AUTOMATIC ) availCheck;

    /*----------------------------------------------------------------------------------*/
    /*  xx Available check. xxx                                                         */
    /*  DEM_MISFIRE_KINDBIT_FIRST : search start bit.(== DEM_MISFIRE_KINDBIT_EMISSION)  */
    /*      misfireIndex == 0U : DEM_MISFIRE_KINDBIT_EMISSION(0x01)                     */
    /*      misfireIndex == 1U : DEM_MISFIRE_KINDBIT_CAT     (0x02)                     */
    /*  so, check bit(availCheck) is left shifted.                                      */
    /*----------------------------------------------------------------------------------*/

    availCheck      =   DEM_MISFIRE_KINDBIT_FIRST;
    retCylinder = DEM_MISFIRE_CYLINDER_ALLBITOFF;
    misfireEventNum = Dem_MisfireEventNum;

    for( misfireIndex = (Dem_u16_MisfireStrgIndexType)0U; misfireIndex < misfireEventNum; misfireIndex++ )
    {
        if (( availCheck & availableMisfireKind ) == availCheck )
        {
            getCylinder = Dem_MisfireMng_GetAFCySinceClear( misfireIndex );
            retCylinder = retCylinder | getCylinder;
        }
        availCheck  =   availCheck << (Dem_u08_MisfireKindBitType)1U;
    }

    retCylinder = Dem_CfgInfoPm_MergeMultipleCylinderBit( retCylinder );

    return retCylinder;
}

/****************************************************************************/
/* Function Name | Dem_Misfire_GetBit6Cylinder                              */
/* Description   | Get Cylinder with StatusOfDTC Bit6 standing              */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_MisfireCylinderType                                  */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.based on Dem_Misfire_GetBit4Cylinder.        */
/****************************************************************************/
FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_Misfire_GetBit6Cylinder
(
    VAR( Dem_u08_MisfireKindBitType, AUTOMATIC ) availableMisfireKind
)
{
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) retCylinder;
    retCylinder = DEM_MISFIRE_CYLINDER_ALLBITON;

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    if (( availableMisfireKind & DEM_MISFIRE_KINDBIT_BOTH ) == DEM_MISFIRE_KINDBIT_BOTH )
    {
        retCylinder =   Dem_Misfire_GetBit6Cylinder_Both();
    }
    else
    if (( availableMisfireKind & DEM_MISFIRE_KINDBIT_CAT ) == DEM_MISFIRE_KINDBIT_CAT )
    {
        retCylinder =   Dem_Misfire_GetBit6Cylinder_CAT();
    }
    else
#endif  /*  ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  */
    if (( availableMisfireKind & DEM_MISFIRE_KINDBIT_EMISSION ) == DEM_MISFIRE_KINDBIT_EMISSION )
    {
        retCylinder =   Dem_Misfire_GetBit6Cylinder_Emission();
    }
    else
    {
        /*  no process      */
    }
    return retCylinder;
}

/****************************************************************************/
/* Function Name | Dem_Misfire_GetBit6Cylinder_Emission                     */
/* Description   | Get Cylinder with StatusOfDTC Bit6 standing              */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_MisfireCylinderType                                  */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | rename from Dem_Misfire_GetBit6Cylinder( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_OFF )(v5-3-0).   */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_Misfire_GetBit6Cylinder_Emission
( void )
{
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) getStatusOfDTCEmission;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) retCylinder;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) misfireEmissionEventStrgIndex;

    retCylinder = DEM_MISFIRE_CYLINDER_ALLBITOFF;

    misfireEmissionEventStrgIndex = Dem_CfgInfoPm_GetEventStrgIndex_MisfireEmission();

    getStatusOfDTCEmission = DEM_DTCSTATUS_BYTE_ALL_OFF;
    (void)Dem_DataMngC_GetER_StatusOfDTC( misfireEmissionEventStrgIndex, &getStatusOfDTCEmission );   /* no return check required */

    /* When only EMISSION is configured */
    if(( getStatusOfDTCEmission & DEM_UDS_STATUS_TNCTOC ) == DEM_UDS_STATUS_TNCTOC )        /*  statusOfDTC : bit6  */
    {
        retCylinder = DEM_MISFIRE_CYLINDER_ALLBITON;
    }
    return retCylinder;
}

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Misfire_GetBit6Cylinder_CAT                          */
/* Description   | Get Cylinder with StatusOfDTC Bit6 standing              */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_MisfireCylinderType                                  */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_Misfire_GetBit6Cylinder_Emission. */
/****************************************************************************/
static FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_Misfire_GetBit6Cylinder_CAT
( void )
{
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) getStatusOfDTCCAT;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) retCylinder;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) misfireCATEventStrgIndex;

    retCylinder = DEM_MISFIRE_CYLINDER_ALLBITOFF;

    misfireCATEventStrgIndex = Dem_CfgInfoPm_GetEventStrgIndex_MisfireCAT();

    getStatusOfDTCCAT = DEM_DTCSTATUS_BYTE_ALL_OFF;
    (void)Dem_DataMngC_GetER_StatusOfDTC( misfireCATEventStrgIndex, &getStatusOfDTCCAT );   /* no return check required */

    /* CAT */
    if(( getStatusOfDTCCAT & DEM_UDS_STATUS_TNCTOC ) == DEM_UDS_STATUS_TNCTOC )        /*  statusOfDTC : bit6  */
    {
        retCylinder = DEM_MISFIRE_CYLINDER_ALLBITON;
    }
    return retCylinder;
}


/****************************************************************************/
/* Function Name | Dem_Misfire_GetBit6Cylinder_Both                         */
/* Description   | Get Cylinder with StatusOfDTC Bit6 standing              */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_MisfireCylinderType                                  */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | rename from Dem_Misfire_GetBit6Cylinder( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )(v5-3-0).   */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_Misfire_GetBit6Cylinder_Both
( void )
{
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) getStatusOfDTCCAT;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) getStatusOfDTCEmission;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) retCylinder;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) misfireCATEventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) misfireEmissionEventStrgIndex;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireCATMisfireStrgIndex;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireEmissionMisfireStrgIndex;

    misfireCATEventStrgIndex      = Dem_CfgInfoPm_GetEventStrgIndex_MisfireCAT();
    misfireEmissionEventStrgIndex = Dem_CfgInfoPm_GetEventStrgIndex_MisfireEmission();
    misfireCATMisfireStrgIndex    = Dem_CfgInfoPm_GetMisfireStrgIndex_MisfireCAT();
    misfireEmissionMisfireStrgIndex     = Dem_CfgInfoPm_GetMisfireStrgIndex_MisfireEmission();

    retCylinder = DEM_MISFIRE_CYLINDER_ALLBITOFF;

    getStatusOfDTCEmission = DEM_DTCSTATUS_BYTE_ALL_OFF;
    (void)Dem_DataMngC_GetER_StatusOfDTC( misfireEmissionEventStrgIndex, &getStatusOfDTCEmission );   /* no return check required */

    getStatusOfDTCCAT = DEM_DTCSTATUS_BYTE_ALL_OFF;

    /* When EMISSION and CAT are configured */
    (void)Dem_DataMngC_GetER_StatusOfDTC( misfireCATEventStrgIndex, &getStatusOfDTCCAT );    /* no return check required */
    if(( getStatusOfDTCEmission & DEM_UDS_STATUS_TNCTOC ) == DEM_UDS_STATUS_TNCTOC )        /*  statusOfDTC : bit6  */
    {
        /* When Bit6 of EMISSION is standing */
        if(( getStatusOfDTCCAT & DEM_UDS_STATUS_TNCTOC ) == DEM_UDS_STATUS_TNCTOC )         /*  statusOfDTC : bit6  */
        {
            /* When Bit6 of CAT is also standing */
            retCylinder = DEM_MISFIRE_CYLINDER_ALLBITON;
        }
        else
        {
            /* When Bit6 of CAT is not standing */
            retCylinder = Dem_MisfireMng_GetAFCylThisOC( misfireCATMisfireStrgIndex );
            retCylinder = Dem_CfgInfoPm_MergeMultipleCylinderBit( retCylinder );
            /* After bit inversion, drop the bit that is out of the valid range. */
            retCylinder = ((Dem_MisfireCylinderType)(~retCylinder)) & Dem_MisfireAvailableCylinder;
        }
    }
    else
    {
        /* When Bit6 of EMISSION is not standing */
        if(( getStatusOfDTCCAT & DEM_UDS_STATUS_TNCTOC ) == DEM_UDS_STATUS_TNCTOC )         /*  statusOfDTC : bit6  */
        {
            /* When Bit6 of CAT is standing */
            retCylinder = Dem_MisfireMng_GetAFCylThisOC( misfireEmissionMisfireStrgIndex );
            retCylinder = Dem_CfgInfoPm_MergeMultipleCylinderBit( retCylinder );
            /* After bit inversion, drop the bit that is out of the valid range. */
            retCylinder = ((Dem_MisfireCylinderType)(~retCylinder)) & Dem_MisfireAvailableCylinder;
        }
    }

    return retCylinder;
}
#endif  /*  ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  */


/****************************************************************************/
/* Function Name | Dem_Misfire_GetBit7Cylinder                              */
/* Description   | Get Cylinder with StatusOfDTC Bit6 standing              */
/* Preconditions | none                                                     */
/* Parameters    | Bit3Cylinder : Bit3 of Cylinde                           */
/* Return Value  | Dem_MisfireCylinderType                                  */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_Misfire_GetBit7Cylinder
(
    VAR( Dem_u08_MisfireKindBitType, AUTOMATIC ) availableMisfireKind,
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) Bit3Cylinder
)
{
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) retCylinder;
    VAR( Dem_u08_MisfireIndStatusType, AUTOMATIC ) getIndicatorStatus;

    retCylinder = DEM_MISFIRE_CYLINDER_ALLBITOFF;
    getIndicatorStatus = Dem_Misfire_GetMILStatus( availableMisfireKind );

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )   /*  [FuncSw]    */
    getIndicatorStatus = getIndicatorStatus & DEM_MISFIRE_IND_CONTINUOUS;
#endif  /*  ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )          */
    if( getIndicatorStatus == DEM_MISFIRE_IND_CONTINUOUS )
    {
        retCylinder = Bit3Cylinder;
    }

    return retCylinder;
}

/****************************************************************************/
/* Function Name | Dem_Misfire_GetCylinderDTCStatus                         */
/* Description   | Get misfire cylinder DTC status                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] MisfireCylinderNum :                                */
/*               |        Specify Cylinder of StatusOfDTC to get            */
/* Return Value  | Dem_UdsStatusByteType                                    */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_UdsStatusByteType, DEM_CODE ) Dem_Misfire_GetCylinderDTCStatus
(
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) MisfireCylinderNum
)
{
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) checkCylinderMask;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) retStatusOfDTC;

    VAR( Dem_MisfireCylinderType, AUTOMATIC ) bit0Cylinder;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) bit1Cylinder;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) bit2Cylinder;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) bit3Cylinder;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) bit4Cylinder;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) bit5Cylinder;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) bit6Cylinder;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) bit7Cylinder;
    VAR( Dem_u08_MisfireKindBitType, AUTOMATIC ) availableMisfireKind;

    availableMisfireKind    =   Dem_DataAvl_GetMisfireCylDTCAvailable();

    retStatusOfDTC = DEM_DTCSTATUS_BYTE_ALL_OFF;
    checkCylinderMask   =   DEM_MISFIRE_CHECK_CYLINDER_BIT << MisfireCylinderNum;

    bit0Cylinder = Dem_Misfire_GetBit0Cylinder( availableMisfireKind );
    if(( bit0Cylinder & checkCylinderMask ) == checkCylinderMask )
    {
        retStatusOfDTC = DEM_UDS_STATUS_TF;                         /*  statusOfDTC : bit0  */
    }

    bit1Cylinder = Dem_Misfire_GetBit1Cylinder( availableMisfireKind );
    if(( bit1Cylinder & checkCylinderMask ) == checkCylinderMask )
    {
        retStatusOfDTC = retStatusOfDTC | DEM_UDS_STATUS_TFTOC;     /*  statusOfDTC : bit1  */
    }

    bit2Cylinder = Dem_Misfire_GetBit2Cylinder( availableMisfireKind );
    if(( bit2Cylinder & checkCylinderMask ) == checkCylinderMask )
    {
        retStatusOfDTC = retStatusOfDTC | DEM_UDS_STATUS_PDTC;      /*  statusOfDTC : bit2  */
    }

    bit3Cylinder = Dem_Misfire_GetBit3Cylinder( availableMisfireKind );
    if(( bit3Cylinder & checkCylinderMask ) == checkCylinderMask )
    {
        retStatusOfDTC = retStatusOfDTC | DEM_UDS_STATUS_CDTC;      /*  statusOfDTC : bit3  */
    }

    bit4Cylinder = Dem_Misfire_GetBit4Cylinder( availableMisfireKind );
    if(( bit4Cylinder & checkCylinderMask ) == checkCylinderMask )
    {
        retStatusOfDTC = retStatusOfDTC | DEM_UDS_STATUS_TNCSLC;    /*  statusOfDTC : bit4  */
    }

    bit5Cylinder = Dem_Misfire_GetBit5Cylinder( availableMisfireKind );
    if(( bit5Cylinder & checkCylinderMask ) == checkCylinderMask )
    {
        retStatusOfDTC = retStatusOfDTC | DEM_UDS_STATUS_TFSLC;     /*  statusOfDTC : bit5  */
    }

    bit6Cylinder = Dem_Misfire_GetBit6Cylinder( availableMisfireKind );
    if(( bit6Cylinder & checkCylinderMask ) == checkCylinderMask )
    {
        retStatusOfDTC = retStatusOfDTC | DEM_UDS_STATUS_TNCTOC;    /*  statusOfDTC : bit6  */
    }

    bit7Cylinder = Dem_Misfire_GetBit7Cylinder( availableMisfireKind, bit3Cylinder );
    if(( bit7Cylinder & checkCylinderMask ) == checkCylinderMask )
    {
        retStatusOfDTC = retStatusOfDTC | DEM_UDS_STATUS_WIR;       /*  statusOfDTC : bit7  */
    }

    return retStatusOfDTC;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
