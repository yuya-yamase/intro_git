/* Dem_Misfire_GetCylinder_c(v5-9-0)                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Misfire_GetCylinder/CODE                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_Pm_DataAvl.h"
#include "../../../inc/Dem_Pm_Misfire.h"
#include "../../../inc/Dem_Rc_MisfireMng.h"
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

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
static FUNC( Dem_u16_MisfireStrgIndexType, DEM_CODE ) Dem_Misfire_CheckStoredObdFFDCyl
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex,
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) MisfireObdFFDCylIndex
);
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )     */
static FUNC( Dem_u16_MisfireStrgIndexType, DEM_CODE ) Dem_Misfire_CheckStoredFFDCyl
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex,
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) MisfireFFDCylIndex
);
#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )   */

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

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Misfire_GetMisfireStrgIndexOfStoredObdFFD            */
/* Description   | Get EventStrgIndex of Stored OBD FFD.                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] MisfireObdFFDCylIndex :                             */
/* Return Value  | Dem_u16_MisfireStrgIndexType                             */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | refactor function.                                       */
/****************************************************************************/
FUNC( Dem_u16_MisfireStrgIndexType, DEM_CODE ) Dem_Misfire_GetMisfireStrgIndexOfStoredObdFFD
(
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) MisfireObdFFDCylIndex
)
{
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndex;
    VAR( Dem_u08_MisfireKindType, AUTOMATIC ) misfireKindOfFFD;

    misfireKindOfFFD    = Dem_MisfireMng_GetMisfireKindOfObdFFD( MisfireObdFFDCylIndex );
    misfireIndex        = Dem_Misfire_JudgeMisfireStrgIndexOfStoredObdFFD( MisfireObdFFDCylIndex, misfireKindOfFFD );

    return misfireIndex;
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )     */

/****************************************************************************/
/* Function Name | Dem_Misfire_GetMisfireStrgIndexOfStoredFFD               */
/* Description   | Get EventStrgIndex of Stored FFD.                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] MisfireFFDCylIndex :                                */
/* Return Value  | Dem_u16_MisfireStrgIndexType                             */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | refactor function.                                       */
/****************************************************************************/
FUNC( Dem_u16_MisfireStrgIndexType, DEM_CODE ) Dem_Misfire_GetMisfireStrgIndexOfStoredFFD
(
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) MisfireFFDCylIndex
)
{
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndex;
    VAR( Dem_u08_MisfireKindType, AUTOMATIC ) misfireKindOfFFD;

    misfireKindOfFFD    = Dem_MisfireMng_GetMisfireKindOfFFD( MisfireFFDCylIndex );
    misfireIndex        = Dem_Misfire_JudgeMisfireStrgIndexOfStoredFFD( MisfireFFDCylIndex, misfireKindOfFFD );

    return misfireIndex;
}

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Misfire_JudgeMisfireStrgIndexOfStoredObdFFD          */
/* Description   | Get EventStrgIndex of Stored OBD FFD.                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] MisfireObdFFDCylIndex :                             */
/*               | [in] MisfireKindOfFFD :                                  */
/* Return Value  | Dem_u16_MisfireStrgIndexType                             */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u16_MisfireStrgIndexType, DEM_CODE ) Dem_Misfire_JudgeMisfireStrgIndexOfStoredObdFFD
(
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) MisfireObdFFDCylIndex,  /* MISRA DEVIATION */
    VAR( Dem_u08_MisfireKindType, AUTOMATIC ) MisfireKindOfFFD
)
{
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndex;
    VAR( Dem_u08_MisfireKindBitType, AUTOMATIC ) availableMisfireKind;

    availableMisfireKind = Dem_DataAvl_GetMisfireCylDTCAvailable();

    if( MisfireKindOfFFD == DEM_MISFIRE_KIND_EMISSION )
    {
        if( ( availableMisfireKind & DEM_MISFIRE_KINDBIT_EMISSION ) == DEM_MISFIRE_KINDBIT_EMISSION )
        {
            misfireIndex = Dem_CfgInfoPm_GetMisfireStrgIndex_MisfireEmission();
        }
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
        else if( ( availableMisfireKind & DEM_MISFIRE_KINDBIT_CAT ) == DEM_MISFIRE_KINDBIT_CAT )
        {
            misfireIndex = Dem_CfgInfoPm_GetMisfireStrgIndex_MisfireCAT();
            /*  same stored cylinder freezeframe.       */
            misfireIndex = Dem_Misfire_CheckStoredObdFFDCyl( misfireIndex, MisfireObdFFDCylIndex );
        }
#endif  /*   ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )         */
        else
        {
            misfireIndex = DEM_MISFIRE_STRGINDEX_INVALID;
        }
    }
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    else if( MisfireKindOfFFD == DEM_MISFIRE_KIND_CAT )
    {
        if( ( availableMisfireKind & DEM_MISFIRE_KINDBIT_CAT ) == DEM_MISFIRE_KINDBIT_CAT )
        {
            misfireIndex = Dem_CfgInfoPm_GetMisfireStrgIndex_MisfireCAT();
        }
        else if( ( availableMisfireKind & DEM_MISFIRE_KINDBIT_EMISSION ) == DEM_MISFIRE_KINDBIT_EMISSION )
        {
            misfireIndex = Dem_CfgInfoPm_GetMisfireStrgIndex_MisfireEmission();
            /*  same stored cylinder freezeframe.       */
            misfireIndex = Dem_Misfire_CheckStoredObdFFDCyl( misfireIndex, MisfireObdFFDCylIndex );
        }
        else
        {
            misfireIndex = DEM_MISFIRE_STRGINDEX_INVALID;
        }
    }
#endif  /*   ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )         */
    else
    {
        misfireIndex = DEM_MISFIRE_STRGINDEX_INVALID;
    }

    return misfireIndex;
}
#endif /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */

/****************************************************************************/
/* Function Name | Dem_Misfire_GetMisfireStrgIndexOfStoredFFD               */
/* Description   | Get EventStrgIndex of Stored FFD.                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] MisfireFFDCylIndex :                                */
/*               | [in] MisfireKindOfFFD :                                  */
/* Return Value  | Dem_u16_MisfireStrgIndexType                             */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u16_MisfireStrgIndexType, DEM_CODE ) Dem_Misfire_JudgeMisfireStrgIndexOfStoredFFD
(
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) MisfireFFDCylIndex,    /* MISRA DEVIATION */
    VAR( Dem_u08_MisfireKindType, AUTOMATIC ) MisfireKindOfFFD
)
{
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndex;
    VAR( Dem_u08_MisfireKindBitType, AUTOMATIC ) availableMisfireKind;

    availableMisfireKind = Dem_DataAvl_GetMisfireCylDTCAvailable();

    if( MisfireKindOfFFD == DEM_MISFIRE_KIND_EMISSION )
    {
        if( ( availableMisfireKind & DEM_MISFIRE_KINDBIT_EMISSION ) == DEM_MISFIRE_KINDBIT_EMISSION )
        {
            misfireIndex = Dem_CfgInfoPm_GetMisfireStrgIndex_MisfireEmission();
        }
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
        else if( ( availableMisfireKind & DEM_MISFIRE_KINDBIT_CAT ) == DEM_MISFIRE_KINDBIT_CAT )
        {
            misfireIndex = Dem_CfgInfoPm_GetMisfireStrgIndex_MisfireCAT();
            /*  same stored cylinder freezeframe.       */
            misfireIndex = Dem_Misfire_CheckStoredFFDCyl( misfireIndex, MisfireFFDCylIndex );
        }
#endif  /*   ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )         */
        else
        {
            misfireIndex = DEM_MISFIRE_STRGINDEX_INVALID;
        }
    }
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    else if( MisfireKindOfFFD == DEM_MISFIRE_KIND_CAT )
    {
        if( ( availableMisfireKind & DEM_MISFIRE_KINDBIT_CAT ) == DEM_MISFIRE_KINDBIT_CAT )
        {
            misfireIndex = Dem_CfgInfoPm_GetMisfireStrgIndex_MisfireCAT();
        }
        else if( ( availableMisfireKind & DEM_MISFIRE_KINDBIT_EMISSION ) == DEM_MISFIRE_KINDBIT_EMISSION )
        {
            misfireIndex = Dem_CfgInfoPm_GetMisfireStrgIndex_MisfireEmission();
            /*  same stored cylinder freezeframe.       */
            misfireIndex = Dem_Misfire_CheckStoredFFDCyl( misfireIndex, MisfireFFDCylIndex );
        }
        else
        {
            misfireIndex = DEM_MISFIRE_STRGINDEX_INVALID;
        }
    }
#endif  /*   ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )         */
    else
    {
        misfireIndex = DEM_MISFIRE_STRGINDEX_INVALID;
    }

    return misfireIndex;
}

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Misfire_CheckStoredObdFFDCyl                         */
/* Description   | check stored freezeframe.                                */
/* Preconditions | none                                                     */
/* Parameters    | [in] MisfireIndex : Misfire index.                       */
/* Parameters    | [in] MisfireObdFFDCylIndex :                             */
/* Return Value  | Dem_u16_MisfireStrgIndexType                             */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
static FUNC( Dem_u16_MisfireStrgIndexType, DEM_CODE ) Dem_Misfire_CheckStoredObdFFDCyl
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex,
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) MisfireObdFFDCylIndex
)
{
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndexStoredObdFFDCyl;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) misfireObdFFDCyl;

    misfireIndexStoredObdFFDCyl    =   DEM_MISFIRE_STRGINDEX_INVALID;

    /*  same stored cylinder freezeframe.       */
    misfireObdFFDCyl    =   Dem_MisfireMng_GetObdFFDCyl( MisfireIndex, MisfireObdFFDCylIndex );

    /*  stored freezeframe cylinder             */
    if ( misfireObdFFDCyl != DEM_MISFIRE_CYLINDER_NON )
    {
        misfireIndexStoredObdFFDCyl = MisfireIndex;
    }

    return misfireIndexStoredObdFFDCyl;
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )     */

/****************************************************************************/
/* Function Name | Dem_Misfire_CheckStoredFFDCyl                            */
/* Description   | check stored freezeframe.                                */
/* Preconditions | none                                                     */
/* Parameters    | [in] MisfireIndex : Misfire index.                       */
/* Parameters    | [in] MisfireFFDCylIndex :                                */
/* Return Value  | Dem_u16_MisfireStrgIndexType                             */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.based on Dem_Misfire_CheckStoredObdFFDCyl.   */
/****************************************************************************/
static FUNC( Dem_u16_MisfireStrgIndexType, DEM_CODE ) Dem_Misfire_CheckStoredFFDCyl
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex,
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) MisfireFFDCylIndex
)
{
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndexStoredFFDCyl;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) misfireFFDCyl;

    misfireIndexStoredFFDCyl    =   DEM_MISFIRE_STRGINDEX_INVALID;

    /*  same stored cylinder freezeframe.       */
    misfireFFDCyl    =   Dem_MisfireMng_GetFFDCyl( MisfireIndex, MisfireFFDCylIndex );

    /*  stored freezeframe cylinder             */
    if ( misfireFFDCyl != DEM_MISFIRE_CYLINDER_NON )
    {
        misfireIndexStoredFFDCyl = MisfireIndex;
    }

    return misfireIndexStoredFFDCyl;
}
#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )   */

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Misfire_CheckOutputOBDFFDConditionByTrigger          */
/* Description   | Check if OBD FFD of the corresponding trigger is the ou- */
/*               | tput target.                                             */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex : Event index.                       */
/*               | [in] Trigger : Trigger that saved OBD FFD                */
/*               | [out] MisfireIndexPtr :                                  */
/*               |                  output cylinder information.            */
/*               | [out] MisfireObdFFDCylIndexPtr :                         */
/*               |                  output cylinder information.            */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : Output target                             */
/*               |        FALSE : Not output target                         */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/*   v5-9-0      | branch changed.                                          */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_Misfire_CheckOutputOBDFFDConditionByTrigger
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) Trigger,
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) MisfireCylinderNumber
)
{
    VAR( boolean, AUTOMATIC ) retVal;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndex;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndexObdFFDConfig;
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) misfireObdFFDCylIndexNum;
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) misfireObdFFDCylIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvId;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) misfireObdFFDCyl;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) misfireCylinderBitCheck;

    retVal      =   (boolean)FALSE;

    /*  convert id.     */
    retCnvId    =   Dem_CfgInfoPm_CnvEventStrgIndexToMisfireStrgIndex( EventStrgIndex, &misfireIndex );         /* [GUD:RET:DEM_IRT_OK]misfireIndex */

    if( retCnvId == DEM_IRT_OK )
    {
        /*  check output trigger    */
        misfireObdFFDCylIndexNum    = Dem_MisfireObdFFDCylIndexNum;
        misfireObdFFDCylIndex       = Dem_CfgInfoPm_GetObdFFDCylIndexOfMisfire( Trigger );

        if( misfireObdFFDCylIndex < misfireObdFFDCylIndexNum )                                                  /* [GUD:if]misfireObdFFDCylIndex */
        {
            misfireIndexObdFFDConfig = Dem_Misfire_GetMisfireStrgIndexOfStoredObdFFD( misfireObdFFDCylIndex );  /* [GUD]misfireObdFFDCylIndex */

            if( misfireIndexObdFFDConfig == misfireIndex )
            {
                /*  output target record information        */
                misfireObdFFDCyl = Dem_Misfire_GetOutputObdFFDCyl( misfireIndex, misfireObdFFDCylIndex );       /* [GUD]misfireIndex *//* [GUD]misfireObdFFDCylIndex */

                misfireCylinderBitCheck = misfireObdFFDCyl & (Dem_MisfireCylinderType)(DEM_MISFIRE_CHECK_CYLINDER_BIT << MisfireCylinderNumber);
                if( misfireCylinderBitCheck != DEM_MISFIRE_CYLINDER_NON )
                {
                    /*  match cylinder number.  */
                    retVal = (boolean)TRUE;
                }

            }
        }
    }

    return retVal;
}

#if ( DEM_MISFIRE_OUTPUT_UDSOBDFFD_MULTIPLE_FAILED_CYL_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_Misfire_GetOutputObdFFDCyl                           */
/* Description   | Get Output OBDFFDCyl.                                    */
/* Preconditions |                                                          */
/* Parameters    | [in] MisfireIndex :                                      */
/*               |        Identification of an event by assigned EventId.   */
/* Parameters    | [in] MisfireObdFFDCylIndex :                             */
/*               |        OBD FFD Cylinder Index.                           */
/* Return Value  | Dem_MisfireCylinderType                                  */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-9-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_Misfire_GetOutputObdFFDCyl
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex,
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) MisfireObdFFDCylIndex
)
{
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) misfireOutputObdFFDCyl;

    misfireOutputObdFFDCyl = Dem_MisfireMng_GetObdFFDCyl( MisfireIndex, MisfireObdFFDCylIndex );

    return misfireOutputObdFFDCyl;
}
#endif  /* ( DEM_MISFIRE_OUTPUT_UDSOBDFFD_MULTIPLE_FAILED_CYL_SUPPORT == STD_OFF )  */

#if ( DEM_MISFIRE_OUTPUT_UDSOBDFFD_MULTIPLE_FAILED_CYL_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Misfire_GetOutputObdFFDCyl                           */
/* Description   | Get Output OBDFFDCyl.                                    */
/* Preconditions |                                                          */
/* Parameters    | [in] MisfireIndex :                                      */
/*               |        Identification of an event by assigned EventId.   */
/* Parameters    | [in] MisfireObdFFDCylIndex :                             */
/*               |        OBD FFD Cylinder Index.                           */
/* Return Value  | Dem_MisfireCylinderType                                  */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-9-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_Misfire_GetOutputObdFFDCyl
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex,                /* MISRA DEVIATION */
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) MisfireObdFFDCylIndex   /* MISRA DEVIATION */
)
{
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) misfireOutputObdFFDCyl;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) bit2Cylinder;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) bit3Cylinder;
    VAR( Dem_u08_MisfireKindBitType, AUTOMATIC ) availableMisfireKind;

    availableMisfireKind    =   Dem_DataAvl_GetMisfireCylDTCAvailable();

    /*  get bit2 ON cylinder.                           */
    bit2Cylinder = Dem_Misfire_GetBit2Cylinder( availableMisfireKind );

    /*  get bit3 ON cylinder.                           */
    bit3Cylinder = Dem_Misfire_GetBit3Cylinder( availableMisfireKind );

    /*  output cylinder : bit2 or bit3 ON cylinder.     */
    misfireOutputObdFFDCyl = bit2Cylinder | bit3Cylinder;

    return misfireOutputObdFFDCyl;
}
#endif  /* ( DEM_MISFIRE_OUTPUT_UDSOBDFFD_MULTIPLE_FAILED_CYL_SUPPORT == STD_ON ) */

#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */

/****************************************************************************/
/* Function Name | Dem_Misfire_CheckOutputFFDConditionByTrigger             */
/* Description   | Check if non OBD FFD of the corresponding trigger is th- */
/*               | e output target.                                         */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex : Event index.                       */
/*               | [in] Trigger : Trigger that saved FFD                    */
/*               | [out] MisfireIndexPtr :                                  */
/*               |                  output cylinder information.            */
/*               | [out] MisfireFFDCylIndexPtr :                            */
/*               |                  output cylinder information.            */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : Output target                             */
/*               |        FALSE : Not output target                         */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_Misfire_CheckOutputFFDConditionByTrigger
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) Trigger,
    P2VAR( Dem_MisfireCylinderNumberType, AUTOMATIC, AUTOMATIC ) MisfireCylinderNumberTypePtr
)
{
    VAR( boolean, AUTOMATIC ) retVal;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndex;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndexFFDConfig;
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) misfireFFDCylIndexNum;
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) misfireFFDCylIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvId;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) misfireFFDCyl;

    retVal      =   (boolean)FALSE;

    /*  convert id.     */
    retCnvId    =   Dem_CfgInfoPm_CnvEventStrgIndexToMisfireStrgIndex( EventStrgIndex, &misfireIndex ); /* [GUD:RET:DEM_IRT_OK]misfireIndex */

    if( retCnvId == DEM_IRT_OK )
    {
        /*  check output trigger    */
        misfireFFDCylIndexNum   = Dem_MisfireFFDCylIndexNum;
        misfireFFDCylIndex      = Dem_CfgInfoPm_GetFFDCylIndexOfMisfire( Trigger );

        if( misfireFFDCylIndex < misfireFFDCylIndexNum )                                                /* [GUD:if]misfireFFDCylIndex */
        {
            misfireIndexFFDConfig = Dem_Misfire_GetMisfireStrgIndexOfStoredFFD( misfireFFDCylIndex );   /* [GUD]misfireFFDCylIndex */

            if( misfireIndexFFDConfig == misfireIndex )
            {
                /*  output target record information        */
                misfireFFDCyl = Dem_MisfireMng_GetFFDCyl( misfireIndex, misfireFFDCylIndex );           /* [GUD]misfireIndex *//* [GUD]misfireFFDCylIndex */

                *MisfireCylinderNumberTypePtr =   Dem_CfgInfoPm_GetMisfireCylinderNumberFromCylBit( misfireFFDCyl );

                retVal = (boolean)TRUE;
            }
        }
    }

    return retVal;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

