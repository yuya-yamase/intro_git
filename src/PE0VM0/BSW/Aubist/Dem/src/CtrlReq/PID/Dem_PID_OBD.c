/* Dem_PID_OBD_c(v5-7-0)                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/PID_OBD/CODE                                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>

#if ( DEM_PID_SUPPORT == STD_ON )
#include "../../../cfg/Dem_Data_Cfg.h"
#include "../../../inc/Dem_Pm_PID.h"
#include "../../../inc/Dem_Rc_PIDMng.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_Pm_DataCtl_OBD.h"
#include "../../../inc/Dem_Pm_Misfire.h"
#include "../../../usr/Dem_UserDTC_OBD_Callout.h"
#include "../../../usr/Dem_Readiness_Callout.h"

#include "Dem_PID_local.h"

#include "../../../cfg/Dem_PBcfg.h"
#include "../../../cfg/Dem_Obd_Cfg.h"

#ifndef DEM_SIT_RANGE_CHECK
#else   /* DEM_SIT_RANGE_CHECK */
#include <Dem_SIT_RangeCheck.h>
#endif  /* DEM_SIT_RANGE_CHECK */

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_PID_BYTE_A_INITVALUE     ((uint8)0x00U)
#define DEM_PID_BYTE_B_INITVALUE     ((uint8)0x00U)
#define DEM_PID_BYTE_A_DTC_MAX       ((uint8)0x7FU)
#define DEM_PID_BYTE_A_MIL_ON        ((uint8)0x80U)

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

static FUNC( void, DEM_CODE ) Dem_PID_ReadDataOfPID01AndPIDF501_DataA
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DataPtr
);
#if ( DEM_WWH_OBD_SUPPORT == STD_OFF )
static FUNC( void, DEM_CODE ) Dem_PID_GetActiveStatus_MILAndConfirmedDTC
(
    P2VAR( boolean, AUTOMATIC, AUTOMATIC )  IsActiveMILPtr,
    P2VAR( Dem_u16_EventNumType, AUTOMATIC, AUTOMATIC )  NumOfConfirmedDTCPtr
);
#endif  /* ( DEM_WWH_OBD_SUPPORT == STD_OFF )   */

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

#if ( DEM_PID_CALC_DEMINTERNALPID_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_PID_Init                                             */
/* Description   | Initializes the value of PIDs                            */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PID_Init
( void )
{
    return;
}

/****************************************************************************/
/* Function Name | Dem_PID_Clear                                            */
/* Description   | Clear the value of PIDs                                  */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PID_Clear
( void )
{
    Dem_PIDMngC_ClearDataOfPID30();
    Dem_PID_ClearAllEventDisable();

    return;
}
#endif  /* ( DEM_PID_CALC_DEMINTERNALPID_SUPPORT == STD_OFF )    */

/****************************************************************************/
/* Function Name | Dem_PID_ReadInitDataOfPID01                              */
/* Description   | Service to report the value of PID01                     */
/* Preconditions | none                                                     */
/* Parameters    | [out] PID01value:                                        */
/*               |        Buffer containing the contents of PID01           */
/*               |        computed by the Dem. The buffer is provided       */
/*               |        by the Dcm or SWC with the appropriate size.      */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PID_ReadInitDataOfPID01
(
    VAR( Dem_u08_ReadinessKindType, AUTOMATIC ) ReadinessCaller,
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID01value
)
{
    Dem_PID_GetInitDataOfReadinessBaseSupportAndComplete( DEM_READINESS_PIDF401, PID01value );
    Dem_PID_InitReadReadinessData( ReadinessCaller, DEM_READINESS_PIDF401, PID01value );

    return;
}

/****************************************************************************/
/* Function Name | Dem_PID_ReadInitDataOfPID21                              */
/* Description   | Service to report the value of PID21                     */
/* Preconditions | none                                                     */
/* Parameters    | [out] PID21value:                                        */
/*               |        Buffer containing the contents of PID21           */
/*               |        computed by the Dem. The buffer is provided       */
/*               |        by the Dcm or SWC with the appropriate size.      */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PID_ReadInitDataOfPID21
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID21value
)
{
    PID21value[DEM_PID_POS0] = DEM_PID_BYTE_A_INITVALUE;/* [ARYCHK] DEM_PID21_SIZE/1/DEM_PID_POS0 */
    PID21value[DEM_PID_POS1] = DEM_PID_BYTE_B_INITVALUE;/* [ARYCHK] DEM_PID21_SIZE/1/DEM_PID_POS1 */

    return;
}

/****************************************************************************/
/* Function Name | Dem_PID_ReadInitDataOfPID30                              */
/* Description   | Service to report the value of PID30                     */
/* Preconditions | none                                                     */
/* Parameters    | [out] PID30value :                                       */
/*               |        Buffer containing the contents of PID30           */
/*               |        computed by the Dem. The buffer is provided by    */
/*               |        the Dcm or SWC with the appropriate size.         */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PID_ReadInitDataOfPID30
(
    CONSTP2VAR( uint8, AUTOMATIC, AUTOMATIC ) PID30value
)
{
    *PID30value = DEM_PID_BYTE_A_INITVALUE;

    return;
}

/****************************************************************************/
/* Function Name | Dem_PID_ReadInitDataOfPID31                              */
/* Description   | Service to report the value of PID31                     */
/* Preconditions | none                                                     */
/* Parameters    | [out] PID31value :                                       */
/*               |        Buffer containing the contents of PID31 computed  */
/*               |        by the Dem. The buffer is provided by the Dcm or  */
/*               |        SWC with the appropriate size.                    */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PID_ReadInitDataOfPID31
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID31value
)
{
    PID31value[DEM_PID_POS0] = DEM_PID_BYTE_A_INITVALUE;/* [ARYCHK] DEM_PID31_SIZE/1/DEM_PID_POS0 */
    PID31value[DEM_PID_POS1] = DEM_PID_BYTE_B_INITVALUE;/* [ARYCHK] DEM_PID31_SIZE/1/DEM_PID_POS1 */

    return;
}

/****************************************************************************/
/* Function Name | Dem_PID_ReadInitDataOfPID41                              */
/* Description   | Service to report the value of PID41                     */
/* Preconditions | none                                                     */
/* Parameters    | [out] PID41value:                                        */
/*               |        Buffer containing the contents of PID41           */
/*               |        computed by the Dem. The buffer is provided       */
/*               |        by the Dcm or SWC with the appropriate size.      */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PID_ReadInitDataOfPID41
(
    VAR( Dem_u08_ReadinessKindType, AUTOMATIC ) ReadinessCaller,
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID41value
)
{
    Dem_PID_GetInitDataOfReadinessBaseSupportAndComplete( DEM_READINESS_PIDF441, PID41value );
    Dem_PID_InitReadReadinessData( ReadinessCaller, DEM_READINESS_PIDF441, PID41value );

    return;
}

/****************************************************************************/
/* Function Name | Dem_PID_ReadInitDataOfPID4D                              */
/* Description   | Service to report the value of PID4D                     */
/* Preconditions | none                                                     */
/* Parameters    | [out] PID4Dvalue :                                       */
/*               |        Buffer containing the contents of PID4D computed  */
/*               |        by the Dem. The buffer is provided by the Dcm or  */
/*               |        SWC with the appropriate size.                    */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PID_ReadInitDataOfPID4D
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID4Dvalue
)
{
    PID4Dvalue[DEM_PID_POS0] = DEM_PID_BYTE_A_INITVALUE;/* [ARYCHK] DEM_PID4D_SIZE/1/DEM_PID_POS0 */
    PID4Dvalue[DEM_PID_POS1] = DEM_PID_BYTE_B_INITVALUE;/* [ARYCHK] DEM_PID4D_SIZE/1/DEM_PID_POS1 */

    return;
}

/****************************************************************************/
/* Function Name | Dem_PID_ReadInitDataOfPID4E                              */
/* Description   | Service to report the value of PID4E                     */
/* Preconditions | none                                                     */
/* Parameters    | [out] PID4Evalue :                                       */
/*               |        Buffer containing the contents of PID4E computed  */
/*               |        by the Dem. The buffer is provided by the Dcm or  */
/*               |        SWC with the appropriate size.                    */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PID_ReadInitDataOfPID4E
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID4Evalue
)
{
    PID4Evalue[DEM_PID_POS0] = DEM_PID_BYTE_A_INITVALUE;/* [ARYCHK] DEM_PID4E_SIZE/1/DEM_PID_POS0 */
    PID4Evalue[DEM_PID_POS1] = DEM_PID_BYTE_B_INITVALUE;/* [ARYCHK] DEM_PID4E_SIZE/1/DEM_PID_POS1 */

    return;
}


/****************************************************************************/
/* Function Name | Dem_PID_ReadInitDataOfPIDF501                            */
/* Description   | Service to report the value of PIDF501                   */
/* Preconditions | none                                                     */
/* Parameters    | [out] PIDF501value:                                      */
/*               |        Buffer containing the contents of PIDF501         */
/*               |        computed by the Dem. The buffer is provided       */
/*               |        by the Dcm or SWC with the appropriate size.      */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PID_ReadInitDataOfPIDF501
(
    VAR( Dem_u08_ReadinessKindType, AUTOMATIC ) ReadinessCaller,
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PIDF501value
)
{
    Dem_PID_GetInitDataOfReadinessBaseSupportAndComplete( DEM_READINESS_PIDF501, PIDF501value );
    Dem_PID_InitReadReadinessData( ReadinessCaller, DEM_READINESS_PIDF501, PIDF501value );

    return;
}


/****************************************************************************/
/* Function Name | Dem_PID_ReadDataOfPID01AndPIDF501                        */
/* Description   | Service to report the value of PID01 And PIDF501         */
/* Preconditions | none                                                     */
/* Parameters    | [in] ReadinessDataKind :                                 */
/*               |        DataKind of Caller PID01 or PIDF501               */
/* Parameters    | [out] ReadinessDataPtr :                                 */
/*               |        Buffer containing the contents of PID01 And       */
/*               |        PIDF501 computed by the Dem. The buffer is provi- */
/*               |        ded by the Dcm or SWC with the appropriate size.  */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | refactor function.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PID_ReadDataOfPID01AndPIDF501
(
    VAR( Dem_u08_ReadinessKindType, AUTOMATIC ) ReadinessCaller,
    VAR( Dem_u08_ReadinessKindType, AUTOMATIC ) ReadinessDataKind,
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) ReadinessDataPtr
)
{
    /*--------------------------------------------------------------------------*/
    /*  Dem_PID_CalcReadinessData needs exclusive [SchM_Enter_Dem_EventMemory]. */
    /* Waits to finish the exclusive section in the Dem_MainFunction context.   */
    SchM_Enter_Dem_EventMemory();    /* waits completion of updating Diag record data by Dem_MainFunction.      */
    SchM_Exit_Dem_EventMemory();

    /*  set dataA.                      */
    Dem_PID_ReadDataOfPID01AndPIDF501_DataA( ReadinessDataPtr );

    /*  set dataB~(ReadinessData).      */
    Dem_PID_ReadReadinessDataOfPID01AndPIDF501( ReadinessCaller, ReadinessDataKind, ReadinessDataPtr );

    return;
}

#if ( DEM_WWH_OBD_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_PID_ReadDataOfPID01AndPIDF501_DataA                  */
/* Description   | Service to report the value of PID01 And PIDF501         */
/* Preconditions | none                                                     */
/* Parameters    | [in] ReadinessDataKind :                                 */
/*               |        DataKind of Caller PID01 or PIDF501               */
/* Parameters    | [out] ReadinessDataPtr :                                 */
/*               |        Buffer containing the contents of PID01 And       */
/*               |        PIDF501 computed by the Dem. The buffer is provi- */
/*               |        ded by the Dcm or SWC with the appropriate size.  */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | rename from Dem_PID_ReadDataOfPID01AndPIDF501(v5-3-0).   */
/*   v5-5-0      | branch changed.                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_PID_ReadDataOfPID01AndPIDF501_DataA
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DataPtr
)
{
    VAR( Dem_u16_EventNumType, AUTOMATIC ) numberOfConfirmedOBDDTC;
    VAR( boolean, AUTOMATIC )  isActiveMIL;

    /*  get MIL status and confirmedDTC number.         */
    Dem_PID_GetActiveStatus_MILAndConfirmedDTC( &isActiveMIL, &numberOfConfirmedOBDDTC );

    if( numberOfConfirmedOBDDTC > DEM_PID_BYTE_A_DTC_MAX )
    {
        DataPtr[DEM_PID_POS0] = DEM_PID_BYTE_A_DTC_MAX;/* [ARYCHK] DEM_SIT_R_CHK_PID01_SIZE / 1 / DEM_PID_POS0 */
    }
    else
    {
        DataPtr[DEM_PID_POS0] = (uint8)( numberOfConfirmedOBDDTC );/* [ARYCHK] DEM_SIT_R_CHK_PID01_SIZE / 1 / DEM_PID_POS0 */
    }

    if ( isActiveMIL == (boolean)TRUE )
    {
        DataPtr[DEM_PID_POS0] |= DEM_PID_BYTE_A_MIL_ON;/* [ARYCHK] DEM_SIT_R_CHK_PID01_SIZE / 1 / DEM_PID_POS0 */
    }

    return;
}
#endif  /*   ( DEM_WWH_OBD_SUPPORT == STD_OFF )     */

#if ( DEM_WWH_OBD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_PID_ReadDataOfPID01AndPIDF501_DataA                  */
/* Description   | Service to report the value of PID01 And PIDF501         */
/* Preconditions | none                                                     */
/* Parameters    | [out] DataPtr :                                          */
/*               |        Buffer containing the contents of PID01 And       */
/*               |        PIDF501 computed by the Dem. The buffer is provi- */
/*               |        ded by the Dcm or SWC with the appropriate size.  */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_PID_ReadDataOfPID01AndPIDF501_DataA
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DataPtr
)
{
    DataPtr[DEM_PID_POS0]   =   DEM_PID_BYTE_A_INITVALUE;/* [ARYCHK] DEM_SIT_R_CHK_PID01_SIZE / 1 / DEM_PID_POS0 */

    return;
}
#endif  /*   ( DEM_WWH_OBD_SUPPORT == STD_ON )     */


/****************************************************************************/
/* Function Name | Dem_PID_ReadDataOfPID1C                                  */
/* Description   | Service to report the value of PID1C                     */
/* Preconditions | none                                                     */
/* Parameters    | [out] PID1Cvalue :                                       */
/*               |        Buffer containing the contents of PID1C           */
/*               |        computed by the Dem. The buffer is provided by    */
/*               |        the Dcm or SWC with the appropriate size.         */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PID_ReadDataOfPID1C
(
    CONSTP2VAR( uint8, AUTOMATIC, AUTOMATIC ) PID1Cvalue
)
{
    *PID1Cvalue = Dem_PB_OBDCompliancy;

    return;
}


/****************************************************************************/
/* Function Name | Dem_PID_ReadDataOfPID21                                  */
/* Description   | Service to report the value of PID21                     */
/* Preconditions | none                                                     */
/* Parameters    | [out] PID21value:                                        */
/*               |        Buffer containing the contents of PID21           */
/*               |        computed by the Dem. The buffer is provided       */
/*               |        by the Dcm or SWC with the appropriate size.      */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PID_ReadDataOfPID21
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID21value
)
{
    Dem_PIDMngC_ReadDataOfPID21(PID21value);

    return;
}


#if ( DEM_PID_WARMUPCYC_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_PID_ReadDataOfPID30                                  */
/* Description   | Service to report the value of PID30                     */
/* Preconditions | none                                                     */
/* Parameters    | [out] PID30value :                                       */
/*               |        Buffer containing the contents of PID30           */
/*               |        computed by the Dem. The buffer is provided by    */
/*               |        the Dcm or SWC with the appropriate size.         */
/* Return Value  | void                                                     */
/* Notes         | This function is in [SchM_Enter_Dem_PID] exclusive area. */
/*               | [SchM_Enter_Dem_PID] exclusion is called in              */
/*               | [Dem_Control_ReadDataOfPID30] function.                  */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PID_ReadDataOfPID30
(
    CONSTP2VAR( uint8, AUTOMATIC, AUTOMATIC ) PID30value
)
{
    /*--------------------------------------------------------------*/
    /*  This function is in [SchM_Enter_Dem_PID] exclusive area.    */
    /*--------------------------------------------------------------*/
    *PID30value = Dem_PIDMngC_ReadDataOfPID30();

    return;
}
#endif  /* ( DEM_PID_WARMUPCYC_SUPPORT == STD_ON )      */

/****************************************************************************/
/* Function Name | Dem_PID_ReadDataOfPID31                                  */
/* Description   | Service to report the value of PID31                     */
/* Preconditions | none                                                     */
/* Parameters    | [out] PID31value :                                       */
/*               |        Buffer containing the contents of PID31 computed  */
/*               |        by the Dem. The buffer is provided by the Dcm or  */
/*               |        SWC with the appropriate size.                    */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PID_ReadDataOfPID31
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID31value
)
{
    Dem_PIDMngC_ReadDataOfPID31( PID31value );

    return;
}

/****************************************************************************/
/* Function Name | Dem_PID_ReadDataOfPID41                                  */
/* Description   | Service to report the value of PID41                     */
/* Preconditions | none                                                     */
/* Parameters    | [out] PID41value :                                       */
/*               |        Buffer containing the contents of PID41           */
/*               |        computed by the Dem. The buffer is provided by    */
/*               |        the Dcm or SWC with the appropriate size.         */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | refactor function.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PID_ReadDataOfPID41
(
    VAR( Dem_u08_ReadinessKindType, AUTOMATIC ) ReadinessCaller,
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID41value
)
{
    /*--------------------------------------------------------------------------*/
    /*  Dem_PID_CalcReadinessData needs exclusive [SchM_Enter_Dem_EventMemory]. */
    /*--------------------------------------------------------------------------*/
    /* Waits to finish the exclusive section in the Dem_MainFunction context.   */
    SchM_Enter_Dem_EventMemory();    /* waits completion of updating Diag record data by Dem_MainFunction.      */
    SchM_Exit_Dem_EventMemory();
    /*--------------------------------------------------------------------------*/

    Dem_PID_ReadReadinessDataOfPID41( ReadinessCaller, PID41value );

    return;
}

/****************************************************************************/
/* Function Name | Dem_PID_ReadDataOfPID4D                                  */
/* Description   | Service to report the value of PID4D                     */
/* Preconditions | none                                                     */
/* Parameters    | [out] PID4Dvalue :                                       */
/*               |        Buffer containing the contents of PID4D computed  */
/*               |        by the Dem. The buffer is provided by the Dcm or  */
/*               |        SWC with the appropriate size.                    */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PID_ReadDataOfPID4D
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID4Dvalue
)
{
    Dem_PIDMngC_ReadDataOfPID4D( PID4Dvalue );

    return;
}

/****************************************************************************/
/* Function Name | Dem_PID_ReadDataOfPID4E                                  */
/* Description   | Service to report the value of PID4E                     */
/* Preconditions | none                                                     */
/* Parameters    | [out] PID4Evalue :                                       */
/*               |        Buffer containing the contents of PID4E computed  */
/*               |        by the Dem. The buffer is provided by the Dcm or  */
/*               |        SWC with the appropriate size.                    */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PID_ReadDataOfPID4E
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID4Evalue
)
{
    Dem_PIDMngC_ReadDataOfPID4E( PID4Evalue );

    return;
}

#if ( DEM_PID_WARMUPCYC_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_PID_UpdateDataOfPID30                                */
/* Description   | Update the value of PID30                                */
/* Preconditions | none                                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | This function is in [SchM_Enter_Dem_PID] exclusive area. */
/*               | [SchM_Enter_Dem_PID] exclusion is called in              */
/*               | [Dem_Control_EndOperationCycleUpdate] function.          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PID_UpdateDataOfPID30
( void )
{
    /*--------------------------------------------------------------*/
    /*  This function is in [SchM_Enter_Dem_PID] exclusive area.    */
    /*--------------------------------------------------------------*/
    Dem_PIDMngC_UpdateDataOfPID30();

    return;
}
#endif  /* ( DEM_PID_WARMUPCYC_SUPPORT == STD_ON )  */

/****************************************************************************/
/* Function Name | Dem_PID_SetDataOfPID21                                   */
/* Description   | Service to set the value of PID21                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] PID21value :                                        */
/*               |        Buffer containing the contents of PID21. The      */
/*               |        buffer is provided by the SWC with the            */
/*               |        appropriate size.                                 */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PID_SetDataOfPID21
(
    CONSTP2CONST( uint8, AUTOMATIC, DEM_APPL_DATA ) PID21value
)
{
    Dem_PIDMngC_SetDataOfPID21( PID21value );

    return;
}

/****************************************************************************/
/* Function Name | Dem_PID_SetDataOfPID31                                   */
/* Description   | Service to set the value of PID31                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] PID31value :                                        */
/*               |        Buffer containing the contents of PID31. The      */
/*               |        buffer is provided by the SWC with the            */
/*               |        appropriate size.                                 */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PID_SetDataOfPID31
(
    CONSTP2CONST( uint8, AUTOMATIC, DEM_APPL_DATA ) PID31value
)
{
    Dem_PIDMngC_SetDataOfPID31( PID31value );

    return;
}

/****************************************************************************/
/* Function Name | Dem_PID_SetDataOfPID4D                                   */
/* Description   | Service to set the value of PID4D                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] PID4Dvalue :                                        */
/*               |        Buffer containing the contents of PID4D. The      */
/*               |        buffer is provided by the SWC with the appropria- */
/*               |        te size.                                          */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PID_SetDataOfPID4D
(
    CONSTP2CONST( uint8, AUTOMATIC, DEM_APPL_DATA ) PID4Dvalue
)
{
    Dem_PIDMngC_SetDataOfPID4D( PID4Dvalue );

    return;
}

/****************************************************************************/
/* Function Name | Dem_PID_SetDataOfPID4E                                   */
/* Description   | Service to set the value of PID4E                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] PID4Evalue :                                        */
/*               |        Buffer containing the contents of PID4E. The      */
/*               |        buffer is provided by the SWC with the appropria- */
/*               |        te size.                                          */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PID_SetDataOfPID4E
(
    CONSTP2CONST( uint8, AUTOMATIC, DEM_APPL_DATA ) PID4Evalue
)
{
    Dem_PIDMngC_SetDataOfPID4E( PID4Evalue );

    return;
}

#if ( DEM_WWH_OBD_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_PID_GetActiveStatus_MILAndConfirmedDTC               */
/* Description   | get MIL status is active or not.                         */
/* Preconditions | none                                                     */
/* Parameters    | [out] IsActiveMILPtr                                     */
/*               |          TRUE    :   MIL is active.                      */
/*               |          FALSE   :   MIL is not active.                  */
/*               | [out] NumOfConfirmedDTCPtr                               */
/*               |                      number of ConfirmedDTC.             */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.based on Dem_PID_GetActiveStatus_MILAndConfirmedDTC_AtClearPID.*/
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_PID_GetActiveStatus_MILAndConfirmedDTC
(
    P2VAR( boolean, AUTOMATIC, AUTOMATIC )  IsActiveMILPtr,
    P2VAR( Dem_u16_EventNumType, AUTOMATIC, AUTOMATIC )  NumOfConfirmedDTCPtr
)
{
    VAR( boolean, AUTOMATIC )  isActiveMIL;
    VAR( Dem_u16_EventNumType, AUTOMATIC )  numberOfConfirmedOBDDTC;
    VAR( Dem_u16_EventNumType, AUTOMATIC )  numberOfMIL;
    VAR( Dem_u08_UserDTCNumType, AUTOMATIC )   numberOfUserOBDDTC;

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )      /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) misfireMilStatus;
    VAR( uint8, AUTOMATIC ) misfireNumOfConfirmedOBDDTC;
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )             */

    numberOfUserOBDDTC = (Dem_u08_UserDTCNumType)0U;
    numberOfConfirmedOBDDTC = (Dem_u16_EventNumType)0U;
    numberOfMIL = (Dem_u16_EventNumType)0U;

    Dem_Data_GetNumberOfOBDDTCByDTCStatus_forPIDDataA( &numberOfConfirmedOBDDTC, &numberOfMIL );
    Dem_GetNumberOfUserDTC(DEM_DTC_KIND_EMISSION_REL_DTCS, &numberOfUserOBDDTC );

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )      /*  [FuncSw]    */
    misfireNumOfConfirmedOBDDTC = (uint8)0U;
    misfireMilStatus = (boolean)FALSE;
    Dem_Misfire_GetNumOfConfirmedCylAndMIL( &misfireNumOfConfirmedOBDDTC, &misfireMilStatus );

    numberOfConfirmedOBDDTC =   numberOfConfirmedOBDDTC + (Dem_u16_EventNumType)misfireNumOfConfirmedOBDDTC;
    if ( misfireMilStatus == ( boolean )TRUE )
    {
        numberOfMIL =   numberOfMIL + (Dem_u16_EventNumType)1U;
    }
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )             */

    *NumOfConfirmedDTCPtr   =   (Dem_u16_EventNumType)((Dem_u32_PIDCalcValueType)numberOfConfirmedOBDDTC + (Dem_u32_PIDCalcValueType)numberOfUserOBDDTC);   /*  no wrap around      */

    isActiveMIL         =   (boolean)FALSE;
    if ( numberOfMIL > ( Dem_u16_EventNumType )0U )
    {
        isActiveMIL =   (boolean)TRUE;
    }
    *IsActiveMILPtr =   isActiveMIL;

    return ;
}
#endif  /* ( DEM_WWH_OBD_SUPPORT == STD_OFF )   */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_PID_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2019-03-27                                              */
/*  v3-0-0         :2019-07-29                                              */
/*  v3-0-1         :2019-10-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
