/* Dem_PID_Readiness_c(v5-5-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/PID_Readiness/CODE                                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_NvM_Cfg.h"
#include "../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../inc/Dem_CmnLib_DTC_DTCStatus.h"
#include "../../../inc/Dem_Pm_PID.h"
#include "../../../inc/Dem_Pm_DataAvl.h"
#include "../../../inc/Dem_Pm_DTC.h"
#include "../../../inc/Dem_Rc_PIDMng.h"
#include "../../../inc/Dem_Rc_DataMng.h"
#include "Dem_PID_local.h"

#if ( DEM_PID_READINESS_SUPPORT == STD_ON )
#include "../../../cfg/Dem_Obd_Cfg.h"
#include "../../../cfg/Dem_Readiness_Cfg.h"
#include "../../../cfg/Dem_OpCycle_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_Rc_OpCycleMng.h"
#include "../../../usr/Dem_Readiness_Callout.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_PID_DATA_NUM_PID01       ((uint8)2U)
#define DEM_PID_DATA_NUM_PID41       ((uint8)2U)
#define DEM_PID_DATA_NUM_PIDF501     ((uint8)5U)

#define DEM_PID_DATA_BITSHIFT_8      ((uint8)0x08U)
#define DEM_PID_DATA_BITSHIFT_16     ((uint8)0x10U)
#define DEM_PID_DATA_BITSHIFT_24     ((uint8)0x18U)
#define DEM_PID_EXINFO_INITVALUE     ((Dem_u08_ReadinessCondType)0x00U)
#define DEM_PID_PASSEDHISTORY_CHKENABLE_INITVALUE     ((Dem_u08_ReadinessCondType)0xFFU)

#define DEM_PID_COMPLETE_POS0 ((uint8)0U)
#define DEM_PID_COMPLETE_POS1 ((uint8)1U)
#define DEM_PID_COMPLETE_POS2 ((uint8)2U)
#define DEM_PID_COMPLETE_POS3 ((uint8)3U)
#define DEM_PID_COMPLETE_POS4 ((uint8)4U)

#define DEM_PID41_BYTE_A             ((uint8)0x00U)

#define DEM_PID_BITON  ((uint8)0x01U)
#define DEM_PID_BYTE_B_SPARK       ((uint8)0x00U)
#define DEM_PID_BYTE_B_COMPRESSION ((uint8)0x08U)
#define DEM_PID_BYTE_DATA_COMMON   ((uint8)0x00U)


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

static FUNC( void, DEM_CODE ) Dem_PID_CalcReadinessData
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) ReadinessDataPtr,
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC )   Supportinfo,
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC )   Completeinfo,
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC )   PassedHistoryCheckEnableInfo,
    VAR( Dem_u08_ReadinessDataPositionIndexType, AUTOMATIC )    CalcType
);
static FUNC( void, DEM_CODE ) Dem_PID_CalcInitReadinessData
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) ReadinessDataPtr,
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC )   Supportinfo,
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC )   Completeinfo,
    VAR( Dem_u08_ReadinessDataPositionIndexType, AUTOMATIC )    CalcType
);

static FUNC( void, DEM_CODE ) Dem_PID_CalcReadinessInfoPID01AndPIDF501
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) RSupBytePtr,
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) RStsBytePtr,
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC )   Supportinfo,
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC )   Completeinfo,
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC )   PassedHistoryCheckEnableInfo,
    VAR( uint8, AUTOMATIC )                       StatusSetPos,
    VAR( Dem_u08_ReadinessGroupIndexType, AUTOMATIC )   ReadinessGrpCount,
    VAR( Dem_u08_ReadinessDataPositionIndexType, AUTOMATIC )    CalcType
);
static FUNC( void, DEM_CODE ) Dem_PID_CalcInitReadinessInfo
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) RStsBytePtr,
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC )   Supportinfo,
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC )   Completeinfo,
    VAR( uint8, AUTOMATIC )                       StatusSetPos,
    VAR( Dem_u08_ReadinessGroupIndexType, AUTOMATIC )   ReadinessGrpCount,
    VAR( Dem_u08_ReadinessDataPositionIndexType, AUTOMATIC )    CalcType
);
static FUNC( void, DEM_CODE ) Dem_PID_CalcReadinessStatusPID01AndPIDF501
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA )      RStsBytePtr,
    VAR( uint8, AUTOMATIC )                            GroupTargetBit,
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC )        PassedHistoryCheckEnableInfo,
    VAR( uint8, AUTOMATIC )                            StatusSetPos,
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC )       EventCtrlIndex,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC )             NextEvtChkPtr
);
static FUNC( void, DEM_CODE ) Dem_PID_CalcReadinessInfoPID41
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA )      REnaBytePtr,
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA )      RStsBytePtr,
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC )        Supportinfo,
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC )        Completeinfo,
    VAR( uint8, AUTOMATIC )                            StatusSetPos,
    VAR( Dem_u08_ReadinessGroupIndexType, AUTOMATIC )  ReadinessGrpCount,
    VAR( Dem_u08_ReadinessDataPositionIndexType, AUTOMATIC )    CalcType
);
static FUNC( void, DEM_CODE ) Dem_PID_CalcReadinessStatusPID41
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA )      RStsBytePtr,
    VAR( uint8, AUTOMATIC )                            GroupTargetBit,
    VAR( uint8, AUTOMATIC )                            StatusSetPos,
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC )       EventCtrlIndex,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC )             ConfirmCalcStsPtr
);
static FUNC( boolean, DEM_CODE ) Dem_PID_GetEventDisable
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex
);
#if ( DEM_CALIBRATION_BY_CALLOUT_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_PID_CalcInitReadinessCompleteInfo
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) RSupBytePtr,
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) RStsBytePtr,
    VAR( uint8, AUTOMATIC )                       StatusSetPos,
    VAR( Dem_u08_ReadinessGroupIndexType, AUTOMATIC )   ReadinessGrpCount,
    VAR( Dem_u08_ReadinessDataPositionIndexType, AUTOMATIC )    CalcType
);
#endif  /* ( DEM_CALIBRATION_BY_CALLOUT_SUPPORT == STD_ON ) */
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
/*   v5-5-0      | rename from Dem_PID_ReadDataOfPID01AndPIDF501(v5-3-0).   */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PID_ReadReadinessDataOfPID01AndPIDF501
(
    VAR( Dem_u08_ReadinessKindType, AUTOMATIC ) ReadinessCaller,
    VAR( Dem_u08_ReadinessKindType, AUTOMATIC ) ReadinessDataKind,
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) ReadinessDataPtr
)
{
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC ) supportinfoB;
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC ) supportinfoC;
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC ) supportinfoD;
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC ) supportinfoE;
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC ) supportinfoF;

    VAR( Dem_u08_ReadinessCondType, AUTOMATIC ) extreaminfoB;
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC ) extreaminfoC;
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC ) extreaminfoD;
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC ) extreaminfoE;
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC ) extreaminfoF;
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC ) completeinfoB;
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC ) completeinfo[DEM_PID_DATA_NUM_PIDF501];
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC ) supportinfo[DEM_PID_DATA_NUM_PIDF501];
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC ) passedHistoryCheckEnableInfo[DEM_PID_DATA_NUM_PIDF501];
    VAR( uint8, AUTOMATIC ) numberOfReadinesData;
    VAR( Dem_u08_ReadinessDataPositionIndexType, AUTOMATIC ) dataByteKind;
    VAR( uint8, AUTOMATIC ) loopCount;
    VAR( Dem_u08_ReadinessKindType, AUTOMATIC ) readinessKind;
#if ( DEM_OBD_MASTER_SUPPORT == STD_ON )   /*  [FuncSw]     */
    VAR( Dem_u08_CycleQualifiedIndexType, AUTOMATIC ) engine4000rpmOccurredIndex;
    VAR( Dem_OperationCycleStateType, AUTOMATIC ) cycleState;
#endif  /*   ( DEM_OBD_MASTER_SUPPORT == STD_ON )           */

    extreaminfoB   = DEM_PID_EXINFO_INITVALUE;
    extreaminfoC   = DEM_PID_EXINFO_INITVALUE;
    extreaminfoD   = DEM_PID_EXINFO_INITVALUE;
    extreaminfoE   = DEM_PID_EXINFO_INITVALUE;
    extreaminfoF   = DEM_PID_EXINFO_INITVALUE;
    completeinfoB  = DEM_PID_EXINFO_INITVALUE;

    supportinfoB   = DEM_READINESS_SUPPORTCOND_ALL;
    supportinfoC   = DEM_READINESS_SUPPORTCOND_ALL;
    supportinfoD   = DEM_READINESS_SUPPORTCOND_ALL;
    supportinfoE   = DEM_READINESS_SUPPORTCOND_ALL;
    supportinfoF   = DEM_READINESS_SUPPORTCOND_ALL;

    passedHistoryCheckEnableInfo[DEM_PID_COMPLETE_POS0] = DEM_PID_PASSEDHISTORY_CHKENABLE_INITVALUE;
    passedHistoryCheckEnableInfo[DEM_PID_COMPLETE_POS1] = DEM_PID_PASSEDHISTORY_CHKENABLE_INITVALUE;
    passedHistoryCheckEnableInfo[DEM_PID_COMPLETE_POS2] = DEM_PID_PASSEDHISTORY_CHKENABLE_INITVALUE;
    passedHistoryCheckEnableInfo[DEM_PID_COMPLETE_POS3] = DEM_PID_PASSEDHISTORY_CHKENABLE_INITVALUE;
    passedHistoryCheckEnableInfo[DEM_PID_COMPLETE_POS4] = DEM_PID_PASSEDHISTORY_CHKENABLE_INITVALUE;

    readinessKind   =   ReadinessCaller + ReadinessDataKind;
#if ( DEM_READINESSSUPPORT_BY_CALLOUT_SUPPORT == STD_ON )   /*  [FuncSw]    */
    Dem_JudgeReadinessSupported( readinessKind, &supportinfoB, &supportinfoC, &supportinfoD, &supportinfoE, &supportinfoF );
#endif  /* ( DEM_READINESSSUPPORT_BY_CALLOUT_SUPPORT == STD_ON )            */
    Dem_JudgeReadinessConditions( readinessKind, &extreaminfoB, &extreaminfoC, &extreaminfoD, &extreaminfoE, &extreaminfoF, &completeinfoB );

    completeinfo[DEM_PID_COMPLETE_POS0] = completeinfoB | extreaminfoB;
    supportinfo[DEM_PID_COMPLETE_POS0]  = supportinfoB;

    if( ReadinessDataKind == DEM_READINESS_PIDF401 )
    {
        Dem_PID_SetInitFixedValue( ReadinessDataPtr );
        numberOfReadinesData = DEM_PID_DATA_NUM_PID01;
        dataByteKind = DEM_PID_CALC_PID01_TYPEB;
        completeinfo[DEM_PID_COMPLETE_POS1] = extreaminfoD;
        supportinfo[DEM_PID_COMPLETE_POS1]  = supportinfoC;
    }
    else
    {
        Dem_PID_SetInitFixedValueOfPIDF501( ReadinessDataPtr );
        numberOfReadinesData = DEM_PID_DATA_NUM_PIDF501;
        dataByteKind = DEM_PID_CALC_PIDF501_TYPEB;
        completeinfo[DEM_PID_COMPLETE_POS1] = extreaminfoC;
        completeinfo[DEM_PID_COMPLETE_POS2] = extreaminfoD;
        completeinfo[DEM_PID_COMPLETE_POS3] = extreaminfoE;
        completeinfo[DEM_PID_COMPLETE_POS4] = extreaminfoF;

        supportinfo[DEM_PID_COMPLETE_POS1]  = supportinfoC;
        supportinfo[DEM_PID_COMPLETE_POS2]  = supportinfoD;
        supportinfo[DEM_PID_COMPLETE_POS3]  = supportinfoE;
        supportinfo[DEM_PID_COMPLETE_POS4]  = supportinfoF;

#if ( DEM_OBD_MASTER_SUPPORT == STD_ON )    /*  [FuncSw]    */
        engine4000rpmOccurredIndex  =   Dem_ConfDemOperationCycleEngine4000RPMOccurred;
        cycleState  =    Dem_OpCycleMng_GetCycleState( engine4000rpmOccurredIndex );

        /*  engine 4000prm occurred ?               */
        if ( cycleState != DEM_CYCLE_NOTIFY_START )
        {
            /*  engine 4000prm is not occurred.     */
            /*  OFF the passed history check enable flag(DEM_PIDF5XX_EXTREMEBIT_MISF).  */
            passedHistoryCheckEnableInfo[DEM_PID_COMPLETE_POS0] = DEM_PID_PASSEDHISTORY_CHKENABLE_INITVALUE & ~DEM_PIDF5XX_EXTREMEBIT_MISF;
        }
#endif  /* ( DEM_OBD_MASTER_SUPPORT == STD_ON )             */
    }

    /* Caluculate Readiness Info */
    for( loopCount = (uint8)0U; loopCount < numberOfReadinesData; loopCount++ )
    {
        Dem_PID_CalcReadinessData( ReadinessDataPtr, supportinfo[loopCount], completeinfo[loopCount], passedHistoryCheckEnableInfo[loopCount], dataByteKind );
        dataByteKind = dataByteKind + (Dem_u08_ReadinessDataPositionIndexType)1U;
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_PID_ReadReadinessDataOfPID41                         */
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
/*   v5-5-0      | rename from Dem_PID_ReadDataOfPID41(v5-3-0).             */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PID_ReadReadinessDataOfPID41
(
    VAR( Dem_u08_ReadinessKindType, AUTOMATIC ) ReadinessCaller,
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID41value
)
{
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC ) supportinfoB;
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC ) supportinfoC;
#if ( DEM_READINESSSUPPORT_BY_CALLOUT_SUPPORT == STD_ON )   /*  [FuncSw]    */
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC ) supportinfoD;
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC ) supportinfoE;
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC ) supportinfoF;
#endif  /* ( DEM_READINESSSUPPORT_BY_CALLOUT_SUPPORT == STD_ON )            */

    VAR( Dem_u08_ReadinessCondType, AUTOMATIC ) extreaminfoB;
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC ) extreaminfoC;
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC ) extreaminfoD;
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC ) extreaminfoE;
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC ) extreaminfoF;
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC ) completeinfoB;
    VAR( Dem_u08_ReadinessKindType, AUTOMATIC ) readinessKind;

    extreaminfoB   = DEM_PID_EXINFO_INITVALUE;
    extreaminfoC   = DEM_PID_EXINFO_INITVALUE;
    extreaminfoD   = DEM_PID_EXINFO_INITVALUE;
    extreaminfoE   = DEM_PID_EXINFO_INITVALUE;
    extreaminfoF   = DEM_PID_EXINFO_INITVALUE;
    completeinfoB  = DEM_PID_EXINFO_INITVALUE;

    supportinfoB   = DEM_READINESS_SUPPORTCOND_ALL;
    supportinfoC   = DEM_READINESS_SUPPORTCOND_ALL;
#if ( DEM_READINESSSUPPORT_BY_CALLOUT_SUPPORT == STD_ON )   /*  [FuncSw]    */
    supportinfoD   = DEM_READINESS_SUPPORTCOND_ALL;
    supportinfoE   = DEM_READINESS_SUPPORTCOND_ALL;
    supportinfoF   = DEM_READINESS_SUPPORTCOND_ALL;
#endif  /* ( DEM_READINESSSUPPORT_BY_CALLOUT_SUPPORT == STD_ON )            */

    PID41value[DEM_PID_POS0] = DEM_PID41_BYTE_A;

    readinessKind   =   ReadinessCaller + DEM_READINESS_PIDF441;
#if ( DEM_READINESSSUPPORT_BY_CALLOUT_SUPPORT == STD_ON )   /*  [FuncSw]    */
    Dem_JudgeReadinessSupported( readinessKind, &supportinfoB, &supportinfoC, &supportinfoD, &supportinfoE, &supportinfoF );
#endif  /* ( DEM_READINESSSUPPORT_BY_CALLOUT_SUPPORT == STD_ON )            */
    Dem_JudgeReadinessConditions( readinessKind, &extreaminfoB, &extreaminfoC, &extreaminfoD, &extreaminfoE, &extreaminfoF, &completeinfoB );

    completeinfoB |= extreaminfoB;

    Dem_PID_SetInitFixedValue( PID41value );

    /* Caluculate PID41 Readiness Info */
    Dem_PID_CalcReadinessData( PID41value, supportinfoB, completeinfoB, DEM_PID_PASSEDHISTORY_CHKENABLE_INITVALUE, DEM_PID_CALC_PID41_TYPEB );
    Dem_PID_CalcReadinessData( PID41value, supportinfoC, extreaminfoD, DEM_PID_PASSEDHISTORY_CHKENABLE_INITVALUE, DEM_PID_CALC_PID41_TYPECD );

    return;
}


/****************************************************************************/
/* Function Name | Dem_PID_SetInitFixedValue                                */
/* Description   | Set the Init Fixed value of PIDs                         */
/* Preconditions | none                                                     */
/* Parameters    | [out] PIDvalue :                                         */
/*               |        Buffer containing the contents of PID computed    */
/*               |        by the Dem.                                       */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PID_SetInitFixedValue
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PIDvalue
)
{
    VAR( Dem_u08_OBDEngineType, AUTOMATIC ) obdEngineType;

    obdEngineType = Dem_OBDEngineType;

    if( obdEngineType == (Dem_u08_OBDEngineType)DEM_IGNITION_SPARK )
    {
        PIDvalue[DEM_PID_POS1] = DEM_PID_BYTE_B_SPARK;
    }
    else
    {
        PIDvalue[DEM_PID_POS1] = DEM_PID_BYTE_B_COMPRESSION;
    }
    PIDvalue[DEM_PID_POS2] = DEM_PID_BYTE_DATA_COMMON;
    PIDvalue[DEM_PID_POS3] = DEM_PID_BYTE_DATA_COMMON;

    return;
}

/****************************************************************************/
/* Function Name | Dem_PID_SetEngType                                       */
/* Description   | Set the Init Fixed value of PIDs                         */
/* Preconditions | none                                                     */
/* Parameters    | [out] PIDvalue :                                         */
/*               |        Buffer containing the contents of PID computed    */
/*               |        by the Dem.                                       */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PID_SetEngType
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PIDvalue
)
{
    VAR( uint8, AUTOMATIC ) obdEngineType;

    obdEngineType = Dem_OBDEngineType;

    if( obdEngineType == (Dem_u08_OBDEngineType)DEM_IGNITION_SPARK )
    {
        /* do nothing, because DEM_PID_BYTE_B_SPARK(0x00) */
    }
    else
    {
        PIDvalue[DEM_PID_POS1] |= DEM_PID_BYTE_B_COMPRESSION;
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_PID_SetInitFixedValueOfPIDF501                       */
/* Description   | Set the Init Fixed value of PIDF501                      */
/* Preconditions | none                                                     */
/* Parameters    | [out] PIDvalue :                                         */
/*               |        Buffer containing the contents of PID computed    */
/*               |        by the Dem.                                       */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PID_SetInitFixedValueOfPIDF501
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PIDvalue
)
{
    PIDvalue[DEM_PID_POS1] = DEM_PID_BYTE_DATA_COMMON;
    PIDvalue[DEM_PID_POS2] = DEM_PID_BYTE_DATA_COMMON;
    PIDvalue[DEM_PID_POS3] = DEM_PID_BYTE_DATA_COMMON;
    PIDvalue[DEM_PID_POS4] = DEM_PID_BYTE_DATA_COMMON;
    PIDvalue[DEM_PID_POS5] = DEM_PID_BYTE_DATA_COMMON;

    return;
}


/****************************************************************************/
/* Function Name | Dem_PID_CalcReadinessData                                */
/* Description   | Calclate the value of PID01,41,F501                      */
/* Preconditions | Need to get exclusive [SchM_Enter_Dem_EventMemory].      */
/* Parameters    | [in/out] PIDvalue :                                      */
/*               |        Buffer containing the contents of PID             */
/*               |        computed by the Dem.                              */
/*               | [in]  Supportinfo :                                      */
/*               |        Support Condition                                 */
/*               | [in]  Completeinfo :                                     */
/*               |        Complete Condition                                */
/*               | [in]  PassedHistoryCheckEnableInfo :                     */
/*               |        PassedHistory check enable Condition              */
/*               | [in]  CalcType :                                         */
/*               |        Calclation Target Type.                           */
/* Return Value  | void                                                     */
/* Notes         | These are the reasons why this function needs to get     */
/*               | exclusive [SchM_Enter_Dem_EventMemory] before called.    */
/*               |  - Dem_PID_CalcReadinessInfoPID01AndPIDF501 needs exclusive [SchM_Enter_Dem_EventMemory].  */
/*               |  - Dem_PID_CalcReadinessInfoPID41 needs exclusive [SchM_Enter_Dem_EventMemory].  */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_PID_CalcReadinessData
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) ReadinessDataPtr,
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC )   Supportinfo,
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC )   Completeinfo,
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC )   PassedHistoryCheckEnableInfo,
    VAR( Dem_u08_ReadinessDataPositionIndexType, AUTOMATIC )    CalcType        /* [PRMCHK:CALLER] */
)
{
    VAR( uint8, AUTOMATIC )   supportByte;
    VAR( uint8, AUTOMATIC )   readinessStsByte;
    VAR( uint8, AUTOMATIC )   statusSetPos;
    VAR( Dem_u08_ReadinessGroupIndexType, AUTOMATIC )   readinessGrpNum;

    supportByte = Dem_ReadinessDataPositionTable[CalcType].SupportByte;                 /* [GUDCHK:CALLER]CalcType *//* [GUD:CFG:IF_GUARDED: CalcType ]supportByte */
    readinessStsByte = Dem_ReadinessDataPositionTable[CalcType].ReadinessStsByte;       /* [GUDCHK:CALLER]CalcType *//* [GUD:CFG:IF_GUARDED: CalcType ]readinessStsByte */
    statusSetPos = Dem_ReadinessDataPositionTable[CalcType].StatusSetPos;               /* [GUDCHK:CALLER]CalcType *//* [GUD:CFG:IF_GUARDED: CalcType ]statusSetPos */
    readinessGrpNum = Dem_ReadinessDataPositionTable[CalcType].ReadinessGrpNum;         /* [GUDCHK:CALLER]CalcType *//* [GUD:CFG:IF_GUARDED: CalcType ]readinessGrpNum */

    if( ( CalcType == DEM_PID_CALC_PID41_TYPEB ) || ( CalcType == DEM_PID_CALC_PID41_TYPECD ) )
    {
        Dem_PID_CalcReadinessInfoPID41(  &ReadinessDataPtr[supportByte], &ReadinessDataPtr[readinessStsByte], Supportinfo, Completeinfo, statusSetPos, readinessGrpNum, CalcType );                                         /* [GUDCHK:CALLER]CalcType */
    }
    else
    {
        Dem_PID_CalcReadinessInfoPID01AndPIDF501(  &ReadinessDataPtr[supportByte], &ReadinessDataPtr[readinessStsByte], Supportinfo, Completeinfo, PassedHistoryCheckEnableInfo, statusSetPos, readinessGrpNum, CalcType ); /* [GUDCHK:CALLER]CalcType */
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_PID_CalcInitReadinessData                            */
/* Description   | Calclate the value of PID01,41,F501                      */
/* Preconditions | Need to get exclusive [SchM_Enter_Dem_EventMemory].      */
/* Parameters    | [in/out] PIDvalue :                                      */
/*               |        Buffer containing the contents of PID             */
/*               |        computed by the Dem.                              */
/*               | [in]  Supportinfo :                                      */
/*               |        Support Condition                                 */
/*               | [in]  Completeinfo :                                     */
/*               |        Complete Condition                                */
/*               | [in]  CalcType :                                         */
/*               |        Calclation Target Type.                           */
/* Return Value  | void                                                     */
/* Notes         | These are the reasons why this function needs to get     */
/*               | exclusive [SchM_Enter_Dem_EventMemory] before called.    */
/*               |  - Dem_PID_CalcReadinessInfoPID01AndPIDF501 needs exclusive [SchM_Enter_Dem_EventMemory].  */
/*               |  - Dem_PID_CalcReadinessInfoPID41 needs exclusive [SchM_Enter_Dem_EventMemory].  */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_PID_CalcInitReadinessData
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) ReadinessDataPtr,
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC )   Supportinfo,
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC )   Completeinfo,
    VAR( Dem_u08_ReadinessDataPositionIndexType, AUTOMATIC )    CalcType        /* [PRMCHK:CALLER] */
)
{
    VAR( uint8, AUTOMATIC )   readinessStsByte;
    VAR( uint8, AUTOMATIC )   statusSetPos;
    VAR( Dem_u08_ReadinessGroupIndexType, AUTOMATIC )   readinessGrpNum;

    readinessStsByte = Dem_ReadinessDataPositionTable[CalcType].ReadinessStsByte;       /* [GUDCHK:CALLER]CalcType *//* [GUD:CFG:IF_GUARDED: CalcType ]readinessStsByte */
    statusSetPos = Dem_ReadinessDataPositionTable[CalcType].StatusSetPos;               /* [GUDCHK:CALLER]CalcType *//* [GUD:CFG:IF_GUARDED: CalcType ]statusSetPos */
    readinessGrpNum = Dem_ReadinessDataPositionTable[CalcType].ReadinessGrpNum;         /* [GUDCHK:CALLER]CalcType *//* [GUD:CFG:IF_GUARDED: CalcType ]readinessGrpNum */

    Dem_PID_CalcInitReadinessInfo( &ReadinessDataPtr[readinessStsByte], Supportinfo, Completeinfo, statusSetPos, readinessGrpNum, CalcType );   /* [GUDCHK:CALLER]CalcType */

    return;
}

/****************************************************************************/
/* Function Name | Dem_PID_CalcInitReadinessInfo                            */
/* Description   | Calculate the readiness information of PID01 And PIDF501.*/
/* Preconditions | Need to get exclusive [SchM_Enter_Dem_EventMemory].      */
/* Parameters    | [in/out] RStsBytePtr :                                   */
/*               |           Readiness Status Byte Buffer                   */
/*               | [in]  Supportinfo :                                      */
/*               |        Support Condition                                 */
/*               | [in]     Completeinfo :                                  */
/*               |           Complete conditions                            */
/*               | [in]     StatusSetPos :                                  */
/*               |           Readiness Status Set Start Position            */
/*               | [in]     ReadinessGrpCount :                             */
/*               |           Number of readiness groups in the target Byte. */
/*               | [in]     CalcType :                                      */
/*               |           Calclation Target Type.                        */
/* Return Value  | void                                                     */
/* Notes         | These are the reasons why this function needs to get     */
/*               | exclusive [SchM_Enter_Dem_EventMemory] before called.    */
/*               |  - Dem_PID_CalcReadinessStatusPID01ndPIDF501 needs exclusive [SchM_Enter_Dem_EventMemory] . */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_PID_CalcInitReadinessInfo
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) RStsBytePtr,
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC )   Supportinfo,
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC )   Completeinfo,
    VAR( uint8, AUTOMATIC )                       StatusSetPos,
    VAR( Dem_u08_ReadinessGroupIndexType, AUTOMATIC )   ReadinessGrpCount,
    VAR( Dem_u08_ReadinessDataPositionIndexType, AUTOMATIC )    CalcType
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC )       eventListNum;
    VAR( Dem_u08_ReadinessGroupIndexType, AUTOMATIC )  groupCount;
    VAR( uint8, AUTOMATIC )                            groupTargetBit;

    for( groupCount = (Dem_u08_ReadinessGroupIndexType)0U; groupCount < ReadinessGrpCount; groupCount++ )
    {
        groupTargetBit = ( uint8 )( DEM_PID_BITON  << groupCount );

        if( ( Supportinfo & groupTargetBit ) == groupTargetBit )
        {
            eventListNum = Dem_CfgInfoPm_GetEventNumberOfReadinessGroup( CalcType, groupCount );
            if( eventListNum != (Dem_u16_EventCtrlIndexType)0U )
            {
                if( ( Completeinfo & groupTargetBit ) == groupTargetBit )
                {
                    /* Always compleate flag is True. */
                    /* Readiness status is set to complete.*/
                    *RStsBytePtr &= (uint8)(~(uint8)( groupTargetBit << StatusSetPos ));

                }
            }
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_PID_CalcReadinessInfoPID01AndPIDF501                 */
/* Description   | Calculate the readiness information of PID01 And PIDF501.*/
/* Preconditions | Need to get exclusive [SchM_Enter_Dem_EventMemory].      */
/* Parameters    | [in/out] RSupBytePtr :                                   */
/*               |           Readiness Support Byte Buffer                  */
/*               | [in/out] RStsBytePtr :                                   */
/*               |           Readiness Status Byte Buffer                   */
/*               | [in]  Supportinfo :                                      */
/*               |        Support Condition                                 */
/*               | [in]     Completeinfo :                                  */
/*               |           Complete conditions                            */
/*               | [in]     PassedHistoryCheckEnableInfo :                  */
/*               |           PassedHistory check enable Condition           */
/*               | [in]     StatusSetPos :                                  */
/*               |           Readiness Status Set Start Position            */
/*               | [in]     ReadinessGrpCount :                             */
/*               |           Number of readiness groups in the target Byte. */
/*               | [in]     CalcType :                                      */
/*               |           Calclation Target Type.                        */
/* Return Value  | void                                                     */
/* Notes         | These are the reasons why this function needs to get     */
/*               | exclusive [SchM_Enter_Dem_EventMemory] before called.    */
/*               |  - Dem_PID_CalcReadinessStatusPID01ndPIDF501 needs exclusive [SchM_Enter_Dem_EventMemory] . */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_PID_CalcReadinessInfoPID01AndPIDF501
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) RSupBytePtr,
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) RStsBytePtr,
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC )   Supportinfo,
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC )   Completeinfo,
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC )   PassedHistoryCheckEnableInfo,
    VAR( uint8, AUTOMATIC )                       StatusSetPos,
    VAR( Dem_u08_ReadinessGroupIndexType, AUTOMATIC )   ReadinessGrpCount,
    VAR( Dem_u08_ReadinessDataPositionIndexType, AUTOMATIC )    CalcType
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC )       eventConfigureNum;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC )       eventListNum;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC )       eventCtrlIndex;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC )       eventCtrlIndexWithCompMask;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC )       loopCount;
    VAR( Dem_u08_ReadinessGroupIndexType, AUTOMATIC )  groupCount;
    VAR( uint8, AUTOMATIC )                            groupTargetBit;
    VAR( boolean, AUTOMATIC )                          availableStatus;
    VAR( boolean, AUTOMATIC )                          nextEvtChk;
    VAR( boolean, AUTOMATIC )                          eventOBDKind;

    eventConfigureNum = Dem_PrimaryMemEventConfigureNum;

    for( groupCount = (Dem_u08_ReadinessGroupIndexType)0U; groupCount < ReadinessGrpCount; groupCount++ )
    {
        groupTargetBit = ( uint8 )( DEM_PID_BITON  << groupCount );
        if( ( Supportinfo & groupTargetBit ) == groupTargetBit )
        {
            eventListNum = Dem_CfgInfoPm_GetEventNumberOfReadinessGroup( CalcType, groupCount );
            if( eventListNum != (Dem_u16_EventCtrlIndexType)0U )
            {
                nextEvtChk = (boolean)TRUE;
                for( loopCount = (Dem_u16_EventCtrlIndexType)0U; loopCount < eventListNum ; loopCount++ )
                {
                    eventCtrlIndexWithCompMask = Dem_CfgInfoPm_GetEventCtrlIndexOfReadinessGroup( CalcType, groupCount, loopCount );
                    eventCtrlIndex  =   eventCtrlIndexWithCompMask & ~DEM_READINESS_EVT_ALWAYS_COMPLETE;

                    if ( eventCtrlIndex < eventConfigureNum )       /* [GUD:if]eventCtrlIndex */
                    {
                        /* Gets event available status */
                        availableStatus = Dem_DataAvl_GetEvtAvl( eventCtrlIndex );      /* [GUD]eventCtrlIndex */
                        if( availableStatus == (boolean)TRUE )
                        {
                            eventOBDKind    =   Dem_CfgInfoPm_CheckEventKindOfOBD_ByEvtCtrlIdx( eventCtrlIndex );   /* [GUD]eventCtrlIndex */
                            if( eventOBDKind == (boolean)TRUE ) /*  OBD     */
                            {
                                *RSupBytePtr |= groupTargetBit;

                                if (( eventCtrlIndexWithCompMask & DEM_READINESS_EVT_ALWAYS_COMPLETE ) == ( Dem_u16_EventCtrlIndexType )0U )
                                {
                                    /* Calculate readiness status */
                                    if( ( Completeinfo & groupTargetBit ) != groupTargetBit )
                                    {
                                        /* Calculate readiness status */
                                        Dem_PID_CalcReadinessStatusPID01AndPIDF501( RStsBytePtr, groupTargetBit, PassedHistoryCheckEnableInfo, StatusSetPos, eventCtrlIndex, &nextEvtChk ); /* [GUD]eventCtrlIndex */
                                    }
                                    else
                                    {
                                        /* Always compleate flag is True. */
                                        /* Readiness status is set to complete.*/
                                        nextEvtChk = (boolean)FALSE;
                                    }
                                }
                                else
                                {
                                    /*--------------------------------------------------*/
                                    /*  always complete.                                */
                                    /*--------------------------------------------------*/
                                    /*  do nothing. only support bit is ON.             */
                                }

                                if( nextEvtChk == (boolean)FALSE )
                                {
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_PID_CalcReadinessStatusPID01AndPIDF501               */
/* Description   | Calculate the readiness Status of PID01 And PIDF501.     */
/* Preconditions | Need to get exclusive [SchM_Enter_Dem_EventMemory].      */
/* Parameters    | [in/out]  RStsBytePtr :                                  */
/*               |            Readiness Status Byte Buffer                  */
/*               | [in]      GroupTargetBit :                               */
/*               |            Bit position in the target Readiness Group.   */
/*               | [in]      PassedHistoryCheckEnableInfo :                 */
/*               |            PassedHistory check enable Condition          */
/*               | [in]      StatusSetPos :                                 */
/*               |            Readiness Status Set Start Position           */
/*               | [in]      EventCtrlIndex :                               */
/*               |            Identification of an event by assigned        */
/*               |            EventCtrlIndex.                               */
/*               | [out]     NextEvtChkPtr :                                */
/*               |            Judgment of checking the next event.          */
/* Return Value  | void                                                     */
/* Notes         | These are the reasons why this function needs to get     */
/*               | exclusive [SchM_Enter_Dem_EventMemory] before called.    */
/*               |  - This function call [DataMng] function directory.      */
/*               |  - This function called from SW-C/Dcm context.           */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_PID_CalcReadinessStatusPID01AndPIDF501
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA )      RStsBytePtr,
    VAR( uint8, AUTOMATIC )                            GroupTargetBit,
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC )        PassedHistoryCheckEnableInfo,
    VAR( uint8, AUTOMATIC )                            StatusSetPos,
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC )       EventCtrlIndex,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC )             NextEvtChkPtr
)
{
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC )                 extendStatusOfDTC;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )                 result;
    VAR( boolean, AUTOMATIC )               nextEvtChk;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;

    nextEvtChk = (boolean)FALSE;

    /* Get ExtendStatusOfDTC, StatusOfDTC From Event Record */
    eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( EventCtrlIndex );                /* [GUD:RET:IF_GUARDED: EventCtrlIndex ]eventStrgIndex */
    result = Dem_DataMngC_GetER_ExtendDTCStatus( eventStrgIndex, &extendStatusOfDTC );

    /* Checks the result of retrieving the event record. */
    if( result == DEM_IRT_OK )
    {
        if( (Dem_u08_DTCStatusExType)( extendStatusOfDTC & DEM_UDS_STATUS_HISTORY_CDTC ) != DEM_UDS_STATUS_HISTORY_CDTC )
        {
            /*------------------------------------------*/
            /*  enable passed history check ?           */
            /*------------------------------------------*/
            if( ( PassedHistoryCheckEnableInfo & GroupTargetBit ) == GroupTargetBit )
            {
                /* Enable passed history check.         */
                /* No confirmed DTC history */
                if( (Dem_u08_DTCStatusExType)( extendStatusOfDTC & DEM_UDS_STATUS_HISTORY_PASSED ) == DEM_UDS_STATUS_HISTORY_PASSED )
                {
                    /* There is a passed history */
                    /* Confirmation of readiness status for the next event */
                    nextEvtChk = (boolean)TRUE;
                }
                else
                {
                    /* No passed history */
                    /* Set not complete to readiness state */
                    *RStsBytePtr |= (uint8)( GroupTargetBit << StatusSetPos );
                    /* Confirmation of readiness status for the next event */
                    nextEvtChk = (boolean)TRUE;
                }
            }
            else
            {
                /* Set not complete to readiness state */
                *RStsBytePtr |= (uint8)( GroupTargetBit << StatusSetPos );

                /* Confirmation of readiness status for the next event */
                nextEvtChk = (boolean)TRUE;
            }
        }
        else
        {
            /* There is a confirmed DTC history */
            /* Set complete to readiness state */
            *RStsBytePtr &= (uint8)(~(uint8)( GroupTargetBit << StatusSetPos ));
        }
    }

    *NextEvtChkPtr = nextEvtChk;

    return;
}

/****************************************************************************/
/* Function Name | Dem_PID_CalcReadinessInfoPID41                           */
/* Description   | Calculate the readiness information of PID41.            */
/* Preconditions | Need to get exclusive [SchM_Enter_Dem_EventMemory].      */
/* Parameters    | [in/out] REnaBytePtr :                                   */
/*               |           Readiness Enable Byte Buffer                   */
/*               | [in/out] RStsBytePtr :                                   */
/*               |           Readiness Status Byte Buffer                   */
/*               | [in]  Supportinfo :                                      */
/*               |        Support Condition                                 */
/*               | [in]     Completeinfo :                                  */
/*               |           Complete conditions                            */
/*               | [in]     StatusSetPos :                                  */
/*               |           Readiness Status Set Start Position            */
/*               | [in]     ReadinessGrpCount :                             */
/*               |           Number of readiness groups in the target Byte. */
/*               | [in]     CalcType :                                      */
/*               |           Calclation Target Type.                        */
/* Return Value  | void                                                     */
/* Notes         | These are the reasons why this function needs to get     */
/*               | exclusive [SchM_Enter_Dem_EventMemory] before called.    */
/*               |  - Dem_PID_CalcReadinessStatusPID41 needs exclusive [SchM_Enter_Dem_EventMemory] .   */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_PID_CalcReadinessInfoPID41
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) REnaBytePtr,
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) RStsBytePtr,
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC )   Supportinfo,
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC )   Completeinfo,
    VAR( uint8, AUTOMATIC )                       StatusSetPos,
    VAR( Dem_u08_ReadinessGroupIndexType, AUTOMATIC )   ReadinessGrpCount,
    VAR( Dem_u08_ReadinessDataPositionIndexType, AUTOMATIC )    CalcType
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC )       eventConfigureNum;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC )       eventListNum;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC )       eventCtrlIndex;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC )       eventCtrlIndexWithCompMask;
    VAR( Dem_u08_ReadinessGroupIndexType, AUTOMATIC )  groupCount;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC )       loopCount;
    VAR( uint8, AUTOMATIC )                            groupTargetBit;
    VAR( boolean, AUTOMATIC )                          availableStatus;
    VAR( boolean, AUTOMATIC )                          disableStatus;
    VAR( boolean, AUTOMATIC )                          confirmCalcEna;
    VAR( boolean, AUTOMATIC )                          confirmCalcSts;
    VAR( boolean, AUTOMATIC )                          eventOBDKind;

    eventConfigureNum = Dem_PrimaryMemEventConfigureNum;

    for( groupCount = (Dem_u08_ReadinessGroupIndexType)0U; groupCount < ReadinessGrpCount; groupCount++ )
    {
        groupTargetBit = ( uint8 )( DEM_PID_BITON  << groupCount );
        if( ( Supportinfo & groupTargetBit ) == groupTargetBit )
        {
            eventListNum = Dem_CfgInfoPm_GetEventNumberOfReadinessGroup( CalcType, groupCount );
            if( eventListNum != (Dem_u16_EventCtrlIndexType)0U )
            {
                confirmCalcEna = (boolean)FALSE;
                confirmCalcSts = (boolean)FALSE;

                for( loopCount = (Dem_u16_EventCtrlIndexType)0U; loopCount < eventListNum ; loopCount++ )
                {
                    eventCtrlIndexWithCompMask = Dem_CfgInfoPm_GetEventCtrlIndexOfReadinessGroup( CalcType, groupCount, loopCount );
                    eventCtrlIndex  =   eventCtrlIndexWithCompMask & ~DEM_READINESS_EVT_ALWAYS_COMPLETE;

                    if ( eventCtrlIndex < eventConfigureNum )       /* [GUD:if]eventCtrlIndex */
                    {
                        /* Gets event available status */
                        availableStatus = Dem_DataAvl_GetEvtAvl( eventCtrlIndex );      /* [GUD]eventCtrlIndex */
                        if( availableStatus == (boolean)TRUE )
                        {
                            eventOBDKind    =   Dem_CfgInfoPm_CheckEventKindOfOBD_ByEvtCtrlIdx( eventCtrlIndex );       /* [GUD]eventCtrlIndex */
                            if( eventOBDKind == (boolean)TRUE ) /*  OBD     */
                            {
                                if (( eventCtrlIndexWithCompMask & DEM_READINESS_EVT_ALWAYS_COMPLETE ) == ( Dem_u16_EventCtrlIndexType )0U )
                                {
                                    /* Calculate readiness status */
                                    /* Available Status is TRUE. The event is Available. */
                                    disableStatus = Dem_PID_GetEventDisable( eventCtrlIndex );      /* [GUD]eventCtrlIndex */
                                    if( disableStatus == ( boolean )FALSE)
                                    {
                                        /* Disable status is false. The event is a diagnostic permission status */
                                        if( confirmCalcEna == (boolean)FALSE )
                                        {
                                            *REnaBytePtr |= groupTargetBit;
                                        }
                                    }
                                    else
                                    {
                                        *REnaBytePtr &= (uint8)~groupTargetBit;
                                        confirmCalcEna = (boolean)TRUE;
                                    }

                                    if( confirmCalcSts == (boolean)FALSE )
                                    {
                                        if( ( Completeinfo & groupTargetBit ) != groupTargetBit )
                                        {
                                            /* Calculate readiness status */
                                            Dem_PID_CalcReadinessStatusPID41( RStsBytePtr, groupTargetBit, StatusSetPos, eventCtrlIndex, &confirmCalcSts );     /* [GUD]eventCtrlIndex */
                                        }
                                        else
                                        {
                                            /* Always compleate flag is True. */
                                            /* Readiness status is set to complete.*/
                                            confirmCalcSts = (boolean)TRUE;
                                        }
                                    }
                                }
                                else
                                {
                                    /*--------------------------------------------------*/
                                    /*  always complete.                                */
                                    /*--------------------------------------------------*/
                                    if( confirmCalcEna == (boolean)FALSE )
                                    {
                                        *REnaBytePtr |= groupTargetBit;
                                    }
                                }

                                if(( confirmCalcEna == (boolean)TRUE ) && ( confirmCalcSts == (boolean)TRUE ))
                                {
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_PID_CalcReadinessStatusPID41                         */
/* Description   | Calculate the readiness Status of PID41.                 */
/* Preconditions | Need to get exclusive [SchM_Enter_Dem_EventMemory].      */
/* Parameters    | [in/out]  RStsBytePtr :                                  */
/*               |            Readiness Status Byte Buffer                  */
/*               | [in]      GroupTargetBit :                               */
/*               |            Bit position in the target Readiness Group.   */
/*               | [in]      StatusSetPos :                                 */
/*               |            Readiness Status Set Start Position           */
/*               | [in]      EventCtrlIndex :                               */
/*               |            Identification of an event by assigned        */
/*               |            EventCtrlIndex.                               */
/*               | [out]     ConfirmStsPtr :                                */
/*               |            Confirmed state of readiness status.          */
/* Return Value  | void                                                     */
/* Notes         | These are the reasons why this function needs to get     */
/*               | exclusive [SchM_Enter_Dem_EventMemory] before called.    */
/*               |  - This function call [DataMng] function directory.      */
/*               |  - This function called from SW-C/Dcm context.           */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_PID_CalcReadinessStatusPID41
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA )      RStsBytePtr,
    VAR( uint8, AUTOMATIC )                            GroupTargetBit,
    VAR( uint8, AUTOMATIC )                            StatusSetPos,
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC )       EventCtrlIndex,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC )             ConfirmCalcStsPtr
)
{
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC ) extendDTCStatus;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )                 result;
    VAR( boolean, AUTOMATIC )               confirmCalcSts;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;

    confirmCalcSts = (boolean)TRUE;

    /* Get ExtendStatusOfDTC, StatusOfDTC From Event Record */
    extendDTCStatus = DEM_DTCSTATUSEX_BYTE_ALL_OFF;

    eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( EventCtrlIndex );                /* [GUD:RET:IF_GUARDED: EventCtrlIndex ]eventStrgIndex */
    result = Dem_DataMngC_GetER_ExtendDTCStatus( eventStrgIndex, &extendDTCStatus );

    /* Checks the result of retrieving the event record. */
    if( result == DEM_IRT_OK )
    {
        if( ( extendDTCStatus & DEM_DTCSTATUSEX_STATUS_TNCTOC_IN_HEALINGCYCLE ) != DEM_DTCSTATUSEX_STATUS_TNCTOC_IN_HEALINGCYCLE  )     /*  TestNotCompletedThisHealingCycle  */
        {
            /* Test completed in this operation cycle */
            if( ( extendDTCStatus & DEM_DTCSTATUSEX_STATUS_TFTOC_IN_HEALINGCYCLE ) != DEM_DTCSTATUSEX_STATUS_TFTOC_IN_HEALINGCYCLE )    /*  TestFailedThisHealingCycle      */
            {
                /* Test not failed in this operation cycle */
                /* Confirmation of readiness status for the next event */
                confirmCalcSts = (boolean)FALSE;
            }
            else
            {
                /* Test failed in this operation cycle */
                /* Set complete to readiness state */
                *RStsBytePtr &= (uint8)(~(uint8)( GroupTargetBit << StatusSetPos ));
            }
        }
        else
        {
            /* Test not completed in this operation cycle */
            /* Set not complete to readiness state */
            *RStsBytePtr |= (uint8)( GroupTargetBit << StatusSetPos );
            /* Confirmation of readiness status for the next event */
            confirmCalcSts = (boolean)FALSE;
        }
    }

    *ConfirmCalcStsPtr = confirmCalcSts;

    return;
}

/****************************************************************************/
/* Function Name | Dem_PID_SetEventDisable                                  */
/* Description   | Set the disable status of a specific Event.              */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventCtrlIndex :                                    */
/*               |        Identification of an event.                       */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PID_SetEventDisable
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex
)
{
    /* Set diagnostic prohibition. */
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) extendDTCStatus2;

    eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( EventCtrlIndex );                /* [GUD:RET:IF_GUARDED: EventCtrlIndex ]eventStrgIndex */

    extendDTCStatus2    =   DEM_DTCSTATUSEX2_BYTE_ALL_OFF;
    (void)Dem_DataMngC_GetER_ExtendDTCStatus2( eventStrgIndex, &extendDTCStatus2 );     /* no return check required */

    /*  set event disable.          */
    extendDTCStatus2    =   Dem_DTC_ExDTC2_SetEventDisable( extendDTCStatus2 );
    (void)Dem_DataMngC_SetER_ExtendDTCStatus2( eventStrgIndex, extendDTCStatus2 );      /* no return check required */

    return;
}

/****************************************************************************/
/* Function Name | Dem_PID_GetEventDisable                                  */
/* Description   | Get the disable status of a specific Event.              */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventCtrlIndex :                                    */
/*               |        Identification of an event.                       */
/* Return Value  | boolean                                                  */
/*               |        TRUE : Event is disable.                          */
/*               |        FALSE : Event is not disable.                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_PID_GetEventDisable
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex
)
{
    VAR( boolean, AUTOMATIC ) retVal;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) extendDTCStatus2;

    eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( EventCtrlIndex );                /* [GUD:RET:IF_GUARDED: EventCtrlIndex ]eventStrgIndex */

    extendDTCStatus2    =   DEM_DTCSTATUSEX2_BYTE_ALL_OFF;
    (void)Dem_DataMngC_GetER_ExtendDTCStatus2( eventStrgIndex, &extendDTCStatus2 );     /* no return check required */

    if(( extendDTCStatus2 & DEM_DTCSTATUSEX2_STATUS_EVENTDISABLE ) == DEM_DTCSTATUSEX2_STATUS_EVENTDISABLE )
    {
        retVal = (boolean)TRUE;
    }
    else
    {
        retVal = (boolean)FALSE;
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_PID_ClearAllEventDisable                             */
/* Description   | initialize the disable Status.                           */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PID_ClearAllEventDisable
( void )
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) extendDTCStatus2;

    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    for( eventStrgIndex = (Dem_u16_EventStrgIndexType)0U; eventStrgIndex < eventStorageNum; eventStrgIndex++ )
    {
        (void)Dem_DataMngC_GetER_ExtendDTCStatus2( eventStrgIndex, &extendDTCStatus2 );     /* no return check required */

        /*  clear event disable.            */
        extendDTCStatus2    =   Dem_DTC_ExDTC2_ClearEventDisable( extendDTCStatus2 );
        (void)Dem_DataMngC_SetER_ExtendDTCStatus2( eventStrgIndex, extendDTCStatus2 );      /* no return check required */
    }

    return;
}

#if ( DEM_CALIBRATION_BY_CALLOUT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_PID_CalcInitReadinessBaseSupportAndCompleteData      */
/* Description   | Calculate the readiness complete information .           */
/* Preconditions | Need to get exclusive [SchM_Enter_Dem_EventMemory].      */
/* Parameters    | [in/out] ReadinessDataPtr :                              */
/*               |        Buffer containing the contents of PID             */
/*               |        computed by the Dem.                              */
/*               | [in]  CalcType :                                         */
/*               |        Calclation Target Type.                           */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PID_CalcInitReadinessBaseSupportAndCompleteData
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) ReadinessDataPtr,
    VAR( Dem_u08_ReadinessDataPositionIndexType, AUTOMATIC )    CalcType        /* [PRMCHK:CALLER] */
)
{
    VAR( uint8, AUTOMATIC )   supportByte;
    VAR( uint8, AUTOMATIC )   readinessStsByte;
    VAR( uint8, AUTOMATIC )   statusSetPos;
    VAR( Dem_u08_ReadinessGroupIndexType, AUTOMATIC )   readinessGrpNum;

    supportByte = Dem_ReadinessDataPositionTable[CalcType].SupportByte;             /* [GUDCHK:CALLER]CalcType *//* [GUD:CFG:IF_GUARDED: CalcType ]supportByte */
    readinessStsByte = Dem_ReadinessDataPositionTable[CalcType].ReadinessStsByte;   /* [GUDCHK:CALLER]CalcType *//* [GUD:CFG:IF_GUARDED: CalcType ]readinessStsByte */
    statusSetPos = Dem_ReadinessDataPositionTable[CalcType].StatusSetPos;           /* [GUDCHK:CALLER]CalcType *//* [GUD:CFG:IF_GUARDED: CalcType ]statusSetPos */
    readinessGrpNum = Dem_ReadinessDataPositionTable[CalcType].ReadinessGrpNum;     /* [GUDCHK:CALLER]CalcType *//* [GUD:CFG:IF_GUARDED: CalcType ]readinessGrpNum */

    ReadinessDataPtr[supportByte]       =   (uint8)0U;  /*  initialize  */          /* [GUDCHK:CALLER]CalcType */
    ReadinessDataPtr[readinessStsByte]  =   (uint8)0U;  /*  initialize  */          /* [GUDCHK:CALLER]CalcType */
    Dem_PID_CalcInitReadinessCompleteInfo(  &ReadinessDataPtr[supportByte], &ReadinessDataPtr[readinessStsByte],  statusSetPos,  readinessGrpNum,  CalcType );  /* [GUDCHK:CALLER]CalcType */

    return;
}

/****************************************************************************/
/* Function Name | Dem_PID_CalcInitReadinessCompleteInfo                    */
/* Description   | Calculate the readiness complete information .           */
/* Preconditions |                                                          */
/* Parameters    | [in/out] RSupBytePtr :                                   */
/*               |           Readiness Status Byte Buffer                   */
/*               | [in]     ReadinessGrpCount :                             */
/*               |           Number of readiness groups in the target Byte. */
/*               | [in]     CalcType :                                      */
/*               |           Calclation Target Type.                        */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_PID_CalcInitReadinessCompleteInfo
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) RSupBytePtr,
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) RStsBytePtr,
    VAR( uint8, AUTOMATIC )                       StatusSetPos,
    VAR( Dem_u08_ReadinessGroupIndexType, AUTOMATIC )   ReadinessGrpCount,
    VAR( Dem_u08_ReadinessDataPositionIndexType, AUTOMATIC )    CalcType        /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC )       eventListNum;
    VAR( Dem_u08_ReadinessGroupIndexType, AUTOMATIC )  groupCount;
    VAR( uint8, AUTOMATIC )                            groupTargetBit;

    for( groupCount = (Dem_u08_ReadinessGroupIndexType)0U; groupCount < ReadinessGrpCount; groupCount++ )   /* [GUD:for]groupCount */
    {
        groupTargetBit = ( uint8 )( DEM_PID_BITON  << groupCount );

        eventListNum = Dem_CfgInfoPm_GetEventNumberOfReadinessGroup( CalcType, groupCount );                /* [GUDCHK:CALLER]CalcType *//* [GUD]groupCount */
        if( eventListNum != (Dem_u16_EventCtrlIndexType)0U )
        {
            *RSupBytePtr |= groupTargetBit;
            *RStsBytePtr |= (uint8)( groupTargetBit << StatusSetPos );
        }
    }

    return;
}

#endif  /* ( DEM_CALIBRATION_BY_CALLOUT_SUPPORT == STD_ON ) */

#if ( DEM_CALIBRATION_BY_CALLOUT_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_PID_GetInitDataOfReadinessBaseSupportAndComplete     */
/* Description   | get readiness initialize data.(completion)               */
/* Preconditions |                                                          */
/* Parameters    | [in] ReadinessDataKind :                                 */
/*               |        DataKind of Caller Readiness.                     */
/* Parameters    | [out] ReadinessDataPtr :                                 */
/*               |        Buffer containing the contents of PID01 And       */
/*               |        PIDF501 computed by the Dem. The buffer is provi- */
/*               |        ded by the Dcm or SWC with the appropriate size.  */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PID_GetInitDataOfReadinessBaseSupportAndComplete
(
    VAR( Dem_u08_ReadinessKindType, AUTOMATIC ) ReadinessDataKind,
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) ReadinessDataPtr
)
{
    VAR( uint32, AUTOMATIC ) initNoCmpData0;
    VAR( uint32, AUTOMATIC ) initNoCmpData1;

    VAR( Dem_u08_ReadinessKindType, AUTOMATIC ) readinessKind;
    readinessKind   =   ReadinessDataKind;

    if ( readinessKind == DEM_READINESS_PIDF401 )
    {
        initNoCmpData0 = Dem_InitNoCompletePID01Data;

        ReadinessDataPtr[DEM_PID_POS0] = (uint8)( initNoCmpData0 >> DEM_PID_DATA_BITSHIFT_24 );
        ReadinessDataPtr[DEM_PID_POS1] = (uint8)( initNoCmpData0 >> DEM_PID_DATA_BITSHIFT_16 );
        ReadinessDataPtr[DEM_PID_POS2] = (uint8)( initNoCmpData0 >> DEM_PID_DATA_BITSHIFT_8 );
        ReadinessDataPtr[DEM_PID_POS3] = (uint8)( initNoCmpData0 );
    }
    else if ( readinessKind == DEM_READINESS_PIDF441 )
    {
        initNoCmpData0 = Dem_InitNoCompletePID41Data;

        ReadinessDataPtr[DEM_PID_POS0] = (uint8)( initNoCmpData0 >> DEM_PID_DATA_BITSHIFT_24 );
        ReadinessDataPtr[DEM_PID_POS1] = (uint8)( initNoCmpData0 >> DEM_PID_DATA_BITSHIFT_16 );
        ReadinessDataPtr[DEM_PID_POS2] = (uint8)( initNoCmpData0 >> DEM_PID_DATA_BITSHIFT_8 );
        ReadinessDataPtr[DEM_PID_POS3] = (uint8)( initNoCmpData0 );
    }
    else
    {
        /*  readinessKind == DEM_READINESS_PIDF501 */
        initNoCmpData0 = Dem_InitNoCompletePIDF501Data0;
        initNoCmpData1 = Dem_InitNoCompletePIDF501Data1;

        ReadinessDataPtr[DEM_PID_POS0] = (uint8)( initNoCmpData0 >> DEM_PID_DATA_BITSHIFT_24 );
        ReadinessDataPtr[DEM_PID_POS1] = (uint8)( initNoCmpData0 >> DEM_PID_DATA_BITSHIFT_16 );
        ReadinessDataPtr[DEM_PID_POS2] = (uint8)( initNoCmpData0 >> DEM_PID_DATA_BITSHIFT_8 );
        ReadinessDataPtr[DEM_PID_POS3] = (uint8)( initNoCmpData0 );
        ReadinessDataPtr[DEM_PID_POS4] = (uint8)( initNoCmpData1 >> DEM_PID_DATA_BITSHIFT_24 );
        ReadinessDataPtr[DEM_PID_POS5] = (uint8)( initNoCmpData1 >> DEM_PID_DATA_BITSHIFT_16 );
    }

    return;
}
#endif  /* ( DEM_CALIBRATION_BY_CALLOUT_SUPPORT == STD_OFF )    */

#if ( DEM_CALIBRATION_BY_CALLOUT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_PID_GetInitDataOfReadinessBaseSupportAndComplete     */
/* Description   | get readiness initialize data.(completion)               */
/* Preconditions |                                                          */
/* Parameters    | [in] ReadinessDataKind :                                 */
/*               |        DataKind of Caller Readiness.                     */
/* Parameters    | [out] ReadinessDataPtr :                                 */
/*               |        Buffer containing the contents of PID01 And       */
/*               |        PIDF501 computed by the Dem. The buffer is provi- */
/*               |        ded by the Dcm or SWC with the appropriate size.  */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PID_GetInitDataOfReadinessBaseSupportAndComplete
(
    VAR( Dem_u08_ReadinessKindType, AUTOMATIC ) ReadinessDataKind,
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) ReadinessDataPtr
)
{
    VAR( uint8, AUTOMATIC ) loopCount;
    VAR( uint8, AUTOMATIC ) numberOfReadinesData;
    VAR( Dem_u08_ReadinessDataPositionIndexType, AUTOMATIC ) dataByteKind;

    VAR( Dem_u08_ReadinessKindType, AUTOMATIC ) readinessKind;
    readinessKind   =   ReadinessDataKind;

    if( readinessKind == DEM_READINESS_PIDF401 )
    {
        numberOfReadinesData = DEM_PID_DATA_NUM_PID01;
        dataByteKind = DEM_PID_CALC_PID01_TYPEB;

        ReadinessDataPtr[DEM_PID_POS0] = (uint8)0U;
        ReadinessDataPtr[DEM_PID_POS1] = (uint8)0U;
        ReadinessDataPtr[DEM_PID_POS2] = (uint8)0U;
        ReadinessDataPtr[DEM_PID_POS3] = (uint8)0U;

    }
    else if( readinessKind == DEM_READINESS_PIDF441 )
    {
        numberOfReadinesData = DEM_PID_DATA_NUM_PID41;
        dataByteKind = DEM_PID_CALC_PID41_TYPEB;

        ReadinessDataPtr[DEM_PID_POS0] = (uint8)0U;
        ReadinessDataPtr[DEM_PID_POS1] = (uint8)0U;
        ReadinessDataPtr[DEM_PID_POS2] = (uint8)0U;
        ReadinessDataPtr[DEM_PID_POS3] = (uint8)0U;
    }
    else
    {
        numberOfReadinesData = DEM_PID_DATA_NUM_PIDF501;
        dataByteKind = DEM_PID_CALC_PIDF501_TYPEB;

        ReadinessDataPtr[DEM_PID_POS0] = (uint8)0U;
        ReadinessDataPtr[DEM_PID_POS1] = (uint8)0U;
        ReadinessDataPtr[DEM_PID_POS2] = (uint8)0U;
        ReadinessDataPtr[DEM_PID_POS3] = (uint8)0U;
        ReadinessDataPtr[DEM_PID_POS4] = (uint8)0U;
        ReadinessDataPtr[DEM_PID_POS5] = (uint8)0U;
    }

    /* Caluculate Readiness Info */
    for( loopCount = (uint8)0U; loopCount < numberOfReadinesData; loopCount++ )
    {
        Dem_PID_CalcInitReadinessBaseSupportAndCompleteData( ReadinessDataPtr, dataByteKind );
        dataByteKind = dataByteKind + (Dem_u08_ReadinessDataPositionIndexType)1U;
    }

    return;
}
#endif  /* ( DEM_CALIBRATION_BY_CALLOUT_SUPPORT == STD_ON ) */

/****************************************************************************/
/* Function Name | Dem_PID_InitReadReadinessData                            */
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
/*   v5-5-0      | rename from Dem_PID_InitReadData(v5-3-0).                */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PID_InitReadReadinessData
(
    VAR( Dem_u08_ReadinessKindType, AUTOMATIC ) ReadinessCaller,
    VAR( Dem_u08_ReadinessKindType, AUTOMATIC ) ReadinessDataKind,
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) ReadinessDataPtr
)
{
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC ) supportinfoB;
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC ) supportinfoC;
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC ) supportinfoD;
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC ) supportinfoE;
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC ) supportinfoF;

    VAR( Dem_u08_ReadinessCondType, AUTOMATIC ) extreaminfoB;
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC ) extreaminfoC;
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC ) extreaminfoD;
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC ) extreaminfoE;
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC ) extreaminfoF;
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC ) completeinfoB;
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC ) completeinfo[DEM_PID_DATA_NUM_PIDF501];
    VAR( Dem_u08_ReadinessCondType, AUTOMATIC ) supportinfo[DEM_PID_DATA_NUM_PIDF501];
    VAR( uint8, AUTOMATIC ) numberOfReadinesData;
    VAR( Dem_u08_ReadinessDataPositionIndexType, AUTOMATIC ) dataByteKind;
    VAR( uint8, AUTOMATIC ) loopCount;
    VAR( Dem_u08_ReadinessKindType, AUTOMATIC ) readinessKind;

    extreaminfoB   = DEM_PID_EXINFO_INITVALUE;
    extreaminfoC   = DEM_PID_EXINFO_INITVALUE;
    extreaminfoD   = DEM_PID_EXINFO_INITVALUE;
    extreaminfoE   = DEM_PID_EXINFO_INITVALUE;
    extreaminfoF   = DEM_PID_EXINFO_INITVALUE;
    completeinfoB  = DEM_PID_EXINFO_INITVALUE;

    supportinfoB   = DEM_READINESS_SUPPORTCOND_ALL;
    supportinfoC   = DEM_READINESS_SUPPORTCOND_ALL;
    supportinfoD   = DEM_READINESS_SUPPORTCOND_ALL;
    supportinfoE   = DEM_READINESS_SUPPORTCOND_ALL;
    supportinfoF   = DEM_READINESS_SUPPORTCOND_ALL;

    readinessKind   =   ReadinessCaller + ReadinessDataKind;
#if ( DEM_READINESSSUPPORT_BY_CALLOUT_SUPPORT == STD_ON )   /*  [FuncSw]    */
    Dem_JudgeReadinessSupported( readinessKind, &supportinfoB, &supportinfoC, &supportinfoD, &supportinfoE, &supportinfoF );
#endif  /* ( DEM_READINESSSUPPORT_BY_CALLOUT_SUPPORT == STD_ON )            */
    Dem_JudgeReadinessConditions( readinessKind, &extreaminfoB, &extreaminfoC, &extreaminfoD, &extreaminfoE, &extreaminfoF, &completeinfoB );

    completeinfo[DEM_PID_COMPLETE_POS0] = completeinfoB | extreaminfoB;
    supportinfo[DEM_PID_COMPLETE_POS0]  = supportinfoB;

    if( ReadinessDataKind == DEM_READINESS_PIDF401 )
    {
        Dem_PID_SetEngType( ReadinessDataPtr );
        numberOfReadinesData = DEM_PID_DATA_NUM_PID01;
        dataByteKind = DEM_PID_CALC_PID01_TYPEB;
        completeinfo[DEM_PID_COMPLETE_POS1] = extreaminfoD;
        supportinfo[DEM_PID_COMPLETE_POS1]  = supportinfoC;
    }
    else if( ReadinessDataKind == DEM_READINESS_PIDF441 )
    {
        Dem_PID_SetEngType( ReadinessDataPtr );
        numberOfReadinesData = DEM_PID_DATA_NUM_PID41;
        dataByteKind = DEM_PID_CALC_PID41_TYPEB;
        completeinfo[DEM_PID_COMPLETE_POS1] = extreaminfoD;
        supportinfo[DEM_PID_COMPLETE_POS1]  = supportinfoC;
    }
    else
    {
        numberOfReadinesData = DEM_PID_DATA_NUM_PIDF501;
        dataByteKind = DEM_PID_CALC_PIDF501_TYPEB;
        completeinfo[DEM_PID_COMPLETE_POS1] = extreaminfoC;
        completeinfo[DEM_PID_COMPLETE_POS2] = extreaminfoD;
        completeinfo[DEM_PID_COMPLETE_POS3] = extreaminfoE;
        completeinfo[DEM_PID_COMPLETE_POS4] = extreaminfoF;

        supportinfo[DEM_PID_COMPLETE_POS1]  = supportinfoC;
        supportinfo[DEM_PID_COMPLETE_POS2]  = supportinfoD;
        supportinfo[DEM_PID_COMPLETE_POS3]  = supportinfoE;
        supportinfo[DEM_PID_COMPLETE_POS4]  = supportinfoF;
    }

    /* Caluculate Readiness Info */
    for( loopCount = (uint8)0U; loopCount < numberOfReadinesData; loopCount++ )
    {
        Dem_PID_CalcInitReadinessData( ReadinessDataPtr, supportinfo[loopCount], completeinfo[loopCount], dataByteKind );
        dataByteKind = dataByteKind + (Dem_u08_ReadinessDataPositionIndexType)1U;
    }

    return;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_PID_READINESS_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
