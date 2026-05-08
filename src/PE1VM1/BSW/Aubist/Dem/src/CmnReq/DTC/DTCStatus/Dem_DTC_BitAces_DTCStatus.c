/* Dem_DTC_BitAces_DTCStatus_c(v5-3-0)                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/


/****************************************************************************/
/* Object Name  | Dem/DTC_BitAces_DTCStatus/CODE                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../../cfg/Dem_Cfg.h"
#include "../../../../inc/Dem_CmnLib_DTC_DTCStatus.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* status of DTC bit ON mask */
#define DEM_DTCSTATUS_BIT0_ON_MASK               (DEM_UDS_STATUS_TF)      /* 0x01 */
#define DEM_DTCSTATUS_BIT1_ON_MASK               (DEM_UDS_STATUS_TFTOC)   /* 0x02 */
#define DEM_DTCSTATUS_BIT2_ON_MASK               (DEM_UDS_STATUS_PDTC)    /* 0x04 */
#define DEM_DTCSTATUS_BIT3_ON_MASK               (DEM_UDS_STATUS_CDTC)    /* 0x08 */
#define DEM_DTCSTATUS_BIT4_ON_MASK               (DEM_UDS_STATUS_TNCSLC)  /* 0x10 */
#define DEM_DTCSTATUS_BIT5_ON_MASK               (DEM_UDS_STATUS_TFSLC)   /* 0x20 */
#define DEM_DTCSTATUS_BIT6_ON_MASK               (DEM_UDS_STATUS_TNCTOC)  /* 0x40 */
#define DEM_DTCSTATUS_BIT7_ON_MASK               (DEM_UDS_STATUS_WIR)     /* 0x80 */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

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
/* Internal Functions                                                       */
/****************************************************************************/
#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DTC_CheckDTCStatus                                   */
/* Description   | Judge a state of each bit of DTC Status.                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCStatus : DTC status.                             */
/*               | [in] DTCStatusBitOnMask : Mask value for each bit        */
/*               |                           judgment of the DTC status.    */
/* Return Value  | boolean                                                  */
/*               |        TRUE : Event registration processing              */
/*               |                     enforcement.                         */
/*               |        FALSE : Event registration processing             */
/*               |                     non-enforcement.                     */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_DTC_CheckDTCStatus
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusBitOnMask
)
{
    VAR( boolean, AUTOMATIC ) retVal;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) dtcStatus;

    dtcStatus = DTCStatus;

    dtcStatus &= DTCStatusBitOnMask;

    if( dtcStatus == DTCStatusBitOnMask )
    {
        retVal = (boolean)TRUE;
    }
    else
    {
        retVal = (boolean)FALSE;
    }

    return retVal;
}
#endif  /* ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )     */


/****************************************************************************/
/* Function Name | Dem_DTC_SetNormalizeDTCStatus                            */
/* Description   | bit0,1,2,3,4,(5),6,7 of statusOfDTC are set to 0.        */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCStatus : DTC status before the change.           */
/* Return Value  | Dem_UdsStatusByteType                                    */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( Dem_UdsStatusByteType, DEM_CODE ) Dem_DTC_SetNormalizeDTCStatus
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus
)
{
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) newDTCStatus;
    VAR( Dem_u08_DTCStatusBitHandlingType, AUTOMATIC ) resetTestFailedSinceLastClearBit;

    resetTestFailedSinceLastClearBit    =   Dem_StatusBitHandlingTestFailedSinceLastClear;

    if ( resetTestFailedSinceLastClearBit == DEM_STATUS_BIT_AGING_AND_DISPLACEMENT )
    {
        /*------------------------------------------------------------------------------*/
        /*  bit5 OFF at Aging.                                                          */
        /*------------------------------------------------------------------------------*/
        /*  resetTestFailedSinceLastClearBit == DEM_STATUS_BIT_AGING_AND_DISPLACEMENT   */
        /*------------------------------------------------------------------------------*/
        /*  OFF : all bit. ( bit0,1,2,3,4,5,6,7 )               */
        /*  = & ~( DEM_DTCSTATUS_BIT0_ON_MASK | DEM_DTCSTATUS_BIT1_ON_MASK | DEM_DTCSTATUS_BIT2_ON_MASK | DEM_DTCSTATUS_BIT3_ON_MASK | DEM_DTCSTATUS_BIT4_ON_MASK | DEM_DTCSTATUS_BIT5_ON_MASK | DEM_DTCSTATUS_BIT6_ON_MASK | DEM_DTCSTATUS_BIT7_ON_MASK )  */
        newDTCStatus = DEM_DTCSTATUS_BYTE_ALL_OFF;
    }
    else
    {
        /*----------------------------------------------------------------------*/
        /*  resetTestFailedSinceLastClearBit == DEM_STATUS_BIT_NORMAL           */
        /*  resetTestFailedSinceLastClearBit == DEM_STATUS_BIT_DISPLACEMENT     */
        /*----------------------------------------------------------------------*/
        /*  OFF : other than bit5. ( bit0,1,2,3,4,6,7 )         */
        /*  = & ~( DEM_DTCSTATUS_BIT0_ON_MASK | DEM_DTCSTATUS_BIT1_ON_MASK | DEM_DTCSTATUS_BIT2_ON_MASK | DEM_DTCSTATUS_BIT3_ON_MASK | DEM_DTCSTATUS_BIT4_ON_MASK | DEM_DTCSTATUS_BIT6_ON_MASK | DEM_DTCSTATUS_BIT7_ON_MASK )   */
        newDTCStatus = ( DTCStatus & (Dem_UdsStatusByteType)DEM_DTCSTATUS_BIT5_ON_MASK );
    }

    return newDTCStatus;
}


/****************************************************************************/
/* Function Name | Dem_DTC_SetPassedDTCStatus                               */
/* Description   | set statusOfDTC : OFF : bit0,4,6                         */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCStatus : DTC status before the change.           */
/* Return Value  | Dem_UdsStatusByteType                                    */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( Dem_UdsStatusByteType, DEM_CODE ) Dem_DTC_SetPassedDTCStatus
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus
)
{
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) newDTCStatus;

    /*  OFF : bit0,4,6      */
    newDTCStatus    =   DTCStatus    & ((Dem_UdsStatusByteType)~( DEM_DTCSTATUS_BIT0_ON_MASK | DEM_DTCSTATUS_BIT4_ON_MASK | DEM_DTCSTATUS_BIT6_ON_MASK ));

    return newDTCStatus;
}


/****************************************************************************/
/* Function Name | Dem_DTC_SetFailedDTCStatus                               */
/* Description   | set statusOfDTC : OFF : bit4,6  ON : bit0,1,2,5          */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCStatus : DTC status before the change.           */
/* Return Value  | Dem_UdsStatusByteType                                    */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( Dem_UdsStatusByteType, DEM_CODE ) Dem_DTC_SetFailedDTCStatus
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus
)
{
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) newDTCStatus;

    /*  OFF : bit4, 6       */
    newDTCStatus    =   DTCStatus    & ((Dem_UdsStatusByteType)~( DEM_DTCSTATUS_BIT4_ON_MASK | DEM_DTCSTATUS_BIT6_ON_MASK ));

    /*  ON  : bit0,1,2,5    */
    newDTCStatus    =   newDTCStatus | ((Dem_UdsStatusByteType)( DEM_DTCSTATUS_BIT0_ON_MASK | DEM_DTCSTATUS_BIT1_ON_MASK | DEM_DTCSTATUS_BIT2_ON_MASK | DEM_DTCSTATUS_BIT5_ON_MASK ));

    return newDTCStatus;
}

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DTC_SetFailedDTCStatusForSyncEventEntry              */
/* Description   | set statusOfDTC : OFF : bit0,4,6  ON : bit1,2,3,5        */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_UdsStatusByteType                                    */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( Dem_UdsStatusByteType, DEM_CODE ) Dem_DTC_SetFailedDTCStatusForSyncEventEntry
( void )
{
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) newDTCStatus;

    /*  ON : bit1,2,3,5     OFF : bit0,4,6,7    */
    newDTCStatus = ((Dem_UdsStatusByteType)( DEM_DTCSTATUS_BIT1_ON_MASK | DEM_DTCSTATUS_BIT2_ON_MASK | DEM_DTCSTATUS_BIT3_ON_MASK | DEM_DTCSTATUS_BIT5_ON_MASK ));

    return newDTCStatus;
}
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )  */

/****************************************************************************/
/* Function Name | Dem_DTC_ResetAllConfirmedDTCStatus_OnOverflow            */
/* Description   | set statusOfDTC : OFF : bit2,3,7,(5)                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCStatus : DTC status before the change.           */
/* Return Value  | Dem_UdsStatusByteType                                    */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_UdsStatusByteType, DEM_CODE ) Dem_DTC_ResetAllConfirmedDTCStatus_OnOverflow
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus
)
{
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) newDTCStatus;
    VAR( Dem_u08_DTCStatusBitHandlingType, AUTOMATIC ) resetTestFailedSinceLastClearBit;
    VAR( Dem_u08_ResetConfirmedBitOnOverflowType, AUTOMATIC ) resetConfirmedBitOnOverflow;


    newDTCStatus    =   DTCStatus;

    /*  get configure value.            */
    resetConfirmedBitOnOverflow         =   Dem_ResetConfirmedBitOnOverflow;
    resetTestFailedSinceLastClearBit    =   Dem_StatusBitHandlingTestFailedSinceLastClear;

    if( resetConfirmedBitOnOverflow == DEM_STATUS_BIT_RESET_CDTC_WITH_PDTC )
    {
        /*------------------------------------------------------------------------------------------*/
        /*  resetConfirmedBitOnOverflow == DEM_STATUS_BIT_RESET_CDTC_WITH_PDTC : reset bit 2/3/7    */
        /*------------------------------------------------------------------------------------------*/

        if (( resetTestFailedSinceLastClearBit == DEM_STATUS_BIT_AGING_AND_DISPLACEMENT )
         || ( resetTestFailedSinceLastClearBit == DEM_STATUS_BIT_DISPLACEMENT ))
        {
            /*------------------------------------------------------------------------------*/
            /*  bit5 OFF on Overflow.                                                       */
            /*------------------------------------------------------------------------------*/
            /*  resetTestFailedSinceLastClearBit == DEM_STATUS_BIT_AGING_AND_DISPLACEMENT   */
            /*  resetTestFailedSinceLastClearBit == DEM_STATUS_BIT_DISPLACEMENT             */
            /*------------------------------------------------------------------------------*/
            /*  OFF : bit2,3,5,7        */
            newDTCStatus = ( DTCStatus & (Dem_UdsStatusByteType)~( DEM_DTCSTATUS_BIT2_ON_MASK | DEM_DTCSTATUS_BIT3_ON_MASK | DEM_DTCSTATUS_BIT5_ON_MASK | DEM_DTCSTATUS_BIT7_ON_MASK ) );
        }
        else
        {
            /*----------------------------------------------------------------------*/
            /*  resetTestFailedSinceLastClearBit == DEM_STATUS_BIT_NORMAL           */
            /*----------------------------------------------------------------------*/
            /*  OFF : bit2,3,7      */
            newDTCStatus = ( DTCStatus & (Dem_UdsStatusByteType)~( DEM_DTCSTATUS_BIT2_ON_MASK | DEM_DTCSTATUS_BIT3_ON_MASK | DEM_DTCSTATUS_BIT7_ON_MASK ) );
        }
    }
    else
    {
        /*----------------------------------------------------------------------*/
        /*  resetConfirmedBitOnOverflow == DEM_STATUS_BIT_NO_RESET              */
        /*----------------------------------------------------------------------*/
        /*  no process.     */
    }

    return newDTCStatus;
}

/****************************************************************************/
/* Function Name | Dem_DTC_ResetConfirmedDTCAndWIRStatus_AtAging            */
/* Description   | set statusOfDTC : OFF : bit3,7,(5)                       */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCStatus : DTC status before the change.           */
/* Return Value  | Dem_UdsStatusByteType                                    */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_UdsStatusByteType, DEM_CODE ) Dem_DTC_ResetConfirmedDTCAndWIRStatus_AtAging
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus
)
{
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) newDTCStatus;
    VAR( Dem_u08_DTCStatusBitHandlingType, AUTOMATIC ) resetTestFailedSinceLastClearBit;

    resetTestFailedSinceLastClearBit    =   Dem_StatusBitHandlingTestFailedSinceLastClear;

    if ( resetTestFailedSinceLastClearBit == DEM_STATUS_BIT_AGING_AND_DISPLACEMENT )
    {
        /*------------------------------------------------------------------------------*/
        /*  bit5 OFF at Aging.                                                          */
        /*------------------------------------------------------------------------------*/
        /*  resetTestFailedSinceLastClearBit == DEM_STATUS_BIT_AGING_AND_DISPLACEMENT   */
        /*------------------------------------------------------------------------------*/
        /*  OFF : bit3,5,7        */
        newDTCStatus = ( DTCStatus & (Dem_UdsStatusByteType)~( DEM_DTCSTATUS_BIT3_ON_MASK | DEM_DTCSTATUS_BIT5_ON_MASK | DEM_DTCSTATUS_BIT7_ON_MASK ) );
    }
    else
    {
        /*----------------------------------------------------------------------*/
        /*  resetTestFailedSinceLastClearBit == DEM_STATUS_BIT_NORMAL           */
        /*  resetTestFailedSinceLastClearBit == DEM_STATUS_BIT_DISPLACEMENT     */
        /*----------------------------------------------------------------------*/
        /*  OFF : bit3,7      */
        newDTCStatus = ( DTCStatus & (Dem_UdsStatusByteType)~( DEM_DTCSTATUS_BIT3_ON_MASK | DEM_DTCSTATUS_BIT7_ON_MASK ) );
    }

    return newDTCStatus;
}

/****************************************************************************/
/* Function Name | Dem_DTC_ResetConfirmedDTCAndPendingDTCStatus_AtAging     */
/* Description   | set statusOfDTC : OFF : bit2,3,(5)                       */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCStatus : DTC status before the change.           */
/* Return Value  | Dem_UdsStatusByteType                                    */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_UdsStatusByteType, DEM_CODE ) Dem_DTC_ResetConfirmedDTCAndPendingDTCStatus_AtAging
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus
)
{
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) newDTCStatus;
    VAR( Dem_u08_DTCStatusBitHandlingType, AUTOMATIC ) resetTestFailedSinceLastClearBit;

    resetTestFailedSinceLastClearBit    =   Dem_StatusBitHandlingTestFailedSinceLastClear;

    if ( resetTestFailedSinceLastClearBit == DEM_STATUS_BIT_AGING_AND_DISPLACEMENT )
    {
        /*------------------------------------------------------------------------------*/
        /*  bit5 OFF at Aging.                                                          */
        /*------------------------------------------------------------------------------*/
        /*  resetTestFailedSinceLastClearBit == DEM_STATUS_BIT_AGING_AND_DISPLACEMENT   */
        /*------------------------------------------------------------------------------*/
        /*  OFF : bit2,3,5        */
        newDTCStatus = ( DTCStatus & (Dem_UdsStatusByteType)~( DEM_DTCSTATUS_BIT2_ON_MASK | DEM_DTCSTATUS_BIT3_ON_MASK | DEM_DTCSTATUS_BIT5_ON_MASK ) );
    }
    else
    {
        /*----------------------------------------------------------------------*/
        /*  resetTestFailedSinceLastClearBit == DEM_STATUS_BIT_NORMAL           */
        /*  resetTestFailedSinceLastClearBit == DEM_STATUS_BIT_DISPLACEMENT     */
        /*----------------------------------------------------------------------*/
        /*  OFF : bit2,3          */
        newDTCStatus = ( DTCStatus & (Dem_UdsStatusByteType)~( DEM_DTCSTATUS_BIT2_ON_MASK | DEM_DTCSTATUS_BIT3_ON_MASK ) );
    }

    return newDTCStatus;
}


#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DTC_ResetConfirmedDTCStatus_AtAging                  */
/* Description   | set statusOfDTC : OFF : bit3,(5)                         */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCStatus : DTC status before the change.           */
/* Return Value  | Dem_UdsStatusByteType                                    */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_UdsStatusByteType, DEM_CODE ) Dem_DTC_ResetConfirmedDTCStatus_AtAging
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus
)
{
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) newDTCStatus;
    VAR( Dem_u08_DTCStatusBitHandlingType, AUTOMATIC ) resetTestFailedSinceLastClearBit;

    resetTestFailedSinceLastClearBit    =   Dem_StatusBitHandlingTestFailedSinceLastClear;

    if ( resetTestFailedSinceLastClearBit == DEM_STATUS_BIT_AGING_AND_DISPLACEMENT )
    {
        /*------------------------------------------------------------------------------*/
        /*  bit5 OFF at Aging.                                                          */
        /*------------------------------------------------------------------------------*/
        /*  resetTestFailedSinceLastClearBit == DEM_STATUS_BIT_AGING_AND_DISPLACEMENT   */
        /*------------------------------------------------------------------------------*/
        /*  OFF : bit3,5        */
        newDTCStatus = ( DTCStatus & (Dem_UdsStatusByteType)~( DEM_DTCSTATUS_BIT3_ON_MASK | DEM_DTCSTATUS_BIT5_ON_MASK ) );
    }
    else
    {
        /*----------------------------------------------------------------------*/
        /*  resetTestFailedSinceLastClearBit == DEM_STATUS_BIT_NORMAL           */
        /*  resetTestFailedSinceLastClearBit == DEM_STATUS_BIT_DISPLACEMENT     */
        /*----------------------------------------------------------------------*/
        /*  OFF : bit3          */
        newDTCStatus = ( DTCStatus & (Dem_UdsStatusByteType)~( DEM_DTCSTATUS_BIT3_ON_MASK ) );
    }

    return newDTCStatus;
}
#endif  /*  ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )    */


/****************************************************************************/
/* Function Name | Dem_DTC_RestartOperationCycleDTCStatus                   */
/* Description   | set statusOfDTC : bit1(,0) : OFF, bit6 : ON              */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCStatus : DTC status before the change.           */
/*               | [in] FailureCycleFlag : DTC status change mode.          */
/* Return Value  | Dem_UdsStatusByteType                                    */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_UdsStatusByteType, DEM_CODE ) Dem_DTC_RestartOperationCycleDTCStatus
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus,
    VAR( Dem_u08_OpcycUpdateFailureCycleType, AUTOMATIC ) FailureCycleFlag
)
{
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) newDTCStatus;
    VAR( boolean, AUTOMATIC ) resetTestFailedBit;

    /*  set value.          */
    newDTCStatus = DTCStatus;

    /*  check bit0 update.      */
    if (( FailureCycleFlag & DEM_OPCYCUPD_FLCYC_UPDSTATUS_TF ) == DEM_OPCYCUPD_FLCYC_UPDSTATUS_TF )
    {
        /* Resets DTC status bit0 */
        resetTestFailedBit  =   Dem_ResetTestFailedAtOpCycRestart;
        if ( resetTestFailedBit == (boolean)TRUE )
        {
            /*  OFF : bit0    */
            newDTCStatus = ( DTCStatus & (Dem_UdsStatusByteType)~( DEM_DTCSTATUS_BIT0_ON_MASK ) );
        }
    }
    /*  check bit1 update.      */
    if (( FailureCycleFlag & DEM_OPCYCUPD_FLCYC_UPDSTATUS_TFTOC ) == DEM_OPCYCUPD_FLCYC_UPDSTATUS_TFTOC )
    {
        /*  OFF : bit1  */
        newDTCStatus = ( newDTCStatus & (Dem_UdsStatusByteType)~( DEM_DTCSTATUS_BIT1_ON_MASK ) );
    }

    /*  check bit6 update.      */
    if (( FailureCycleFlag & DEM_OPCYCUPD_FLCYC_UPDSTATUS_TNCTOC ) == DEM_OPCYCUPD_FLCYC_UPDSTATUS_TNCTOC )
    {
        /*  ON  : bit6      */
        newDTCStatus = ( newDTCStatus | (Dem_UdsStatusByteType)DEM_DTCSTATUS_BIT6_ON_MASK );
    }

    return newDTCStatus;
}


/****************************************************************************/
/* Function Name | Dem_DTC_ResetPendingDTCBit                               */
/* Description   | DTC status bit2(PendingDTC) initialization               */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCStatus : DTC status before the change.           */
/* Return Value  | Dem_UdsStatusByteType                                    */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_UdsStatusByteType, DEM_CODE ) Dem_DTC_ResetPendingDTCBit
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus
)
{
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) newDTCStatus;

    /* Resets DTC status bit2 */
    newDTCStatus = ( DTCStatus & (Dem_UdsStatusByteType)~DEM_DTCSTATUS_BIT2_ON_MASK );

    return newDTCStatus;
}

/****************************************************************************/
/* Function Name | Dem_DTC_SetConfirmedDTCBit                               */
/* Description   | Turn on DTC status bit3(ConfirmedDTC)                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCStatus : DTC status before the change.           */
/* Return Value  | Dem_UdsStatusByteType                                    */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_UdsStatusByteType, DEM_CODE ) Dem_DTC_SetConfirmedDTCBit
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus
)
{
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) newDTCStatus;

    /* Turns on DTC status bit3 */
    newDTCStatus = ( DTCStatus | (Dem_UdsStatusByteType)DEM_DTCSTATUS_BIT3_ON_MASK );

    return newDTCStatus;
}


/****************************************************************************/
/* Function Name | Dem_DTC_SetWIRStatusBit                                  */
/* Description   | set DTC status bit7(WIRStatus) .                         */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCStatus : DTC status before the change.           */
/* Return Value  | Dem_UdsStatusByteType                                    */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_UdsStatusByteType, DEM_CODE ) Dem_DTC_SetWIRStatusBit
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus
)
{
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) newDTCStatus;

    /* Turns on DTC status bit7 */
    newDTCStatus = (DTCStatus | (Dem_UdsStatusByteType)DEM_DTCSTATUS_BIT7_ON_MASK );

    return newDTCStatus;
}

#if ( DEM_INDICATOR_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DTC_ResetWIRStatusBit                                */
/* Description   | DTC status bit7(WIRStatus) initialization                */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCStatus : DTC status before the change.           */
/* Return Value  | Dem_UdsStatusByteType                                    */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_UdsStatusByteType, DEM_CODE ) Dem_DTC_ResetWIRStatusBit
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus
)
{
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) newDTCStatus;

    /* Resets DTC status bit7 */
    newDTCStatus = (DTCStatus & (Dem_UdsStatusByteType)~DEM_DTCSTATUS_BIT7_ON_MASK );

    return newDTCStatus;
}
#endif  /*   ( DEM_INDICATOR_USE == STD_ON )        */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
