/* Dem_Misfire_FilRecord_c(v5-9-0)                                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Misfire_FilRecord/CODE                                */
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
#include "../../../inc/Dem_Pm_Misfire.h"
#include "../../../inc/Dem_Rc_MisfireMng.h"
#include "../../../inc/Dem_Rc_DataMng.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
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

#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_OFF )
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
static FUNC( boolean, DEM_CODE ) Dem_Misfire_GetOutputFilteredObdFFDCylinderNumber
(
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) MisfireObdFFDCyl,
    P2VAR( Dem_MisfireCylinderNumberType, AUTOMATIC, AUTOMATIC ) MisfireCylinderNumberOutputPtr
);

#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )                     */
#endif  /* ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )  */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_OFF )
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
#if ( DEM_MISFIRE_OUTPUT_UDSOBDFFD_MULTIPLE_FAILED_CYL_SUPPORT == STD_ON )
static VAR( Dem_MisfireCylinderNumberType, DEM_VAR_NO_INIT ) Dem_MisfireFilRecOutputOBDFFDCylNum;
#endif  /* ( DEM_MISFIRE_OUTPUT_UDSOBDFFD_MULTIPLE_FAILED_CYL_SUPPORT == STD_ON )   */
static VAR( Dem_MisfireCylinderType, DEM_VAR_NO_INIT )  Dem_MisfireFilRecOBDFFDCyl[DEM_MISFIRE_OBD_FFDCYL_INDEX_NUM];
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */
static VAR( Dem_MisfireCylinderType, DEM_VAR_NO_INIT )  Dem_MisfireFilRecFFDCyl[DEM_MISFIRE_FFDCYL_INDEX_NUM];

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
static VAR( Dem_u16_MisfireStrgIndexType, DEM_VAR_NO_INIT )  Dem_MisfireFilRecMisfireStrgIndexOfOBDFFD[DEM_MISFIRE_OBD_FFDCYL_INDEX_NUM];
#endif  /*   ( DEM_OBDFFD_SUPPORT == STD_ON )       */
static VAR( Dem_u16_MisfireStrgIndexType, DEM_VAR_NO_INIT )  Dem_MisfireFilRecMisfireStrgIndexOfFFD[DEM_MISFIRE_FFDCYL_INDEX_NUM];
#endif  /* ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_OFF ) */


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>



/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Misfire_PrepareFilteredRecord                        */
/* Description   | Prepare for the misfire freeze frame record filter.      */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | new coreated.                                            */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_PrepareFilteredRecord
( void )
{
    /*  no process.     */
    return ;
}
#endif  /* ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )  */

#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_Misfire_PrepareFilteredRecord                        */
/* Description   | Prepare for the misfire freeze frame record filter.      */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-9-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_PrepareFilteredRecord
( void )
{
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndex;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireEventNum;
#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) misfireObdFFDCylIndex;
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) misfireObdFFDCylIndexNum;
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) misfireFFDCylIndex;
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) misfireFFDCylIndexNum;

    misfireEventNum = Dem_MisfireEventNum;

#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
    misfireObdFFDCylIndexNum = Dem_MisfireObdFFDCylIndexNum;
    for( misfireObdFFDCylIndex = (Dem_u08_MisfireObdFFDCylIndexType)0U; misfireObdFFDCylIndex < misfireObdFFDCylIndexNum; misfireObdFFDCylIndex++ )     /* [GUD:for]misfireObdFFDCylIndex */
    {
        misfireIndex = Dem_Misfire_GetMisfireStrgIndexOfStoredObdFFD( misfireObdFFDCylIndex );                                                          /* [GUD]misfireObdFFDCylIndex */
        if( misfireIndex < misfireEventNum )                                                                                                            /* [GUD:if]misfireIndex */
        {
            Dem_MisfireFilRecOBDFFDCyl[ misfireObdFFDCylIndex ] = Dem_Misfire_GetOutputObdFFDCyl( misfireIndex, misfireObdFFDCylIndex );                /* [GUD]misfireObdFFDCylIndex */
        }
        else
        {
            Dem_MisfireFilRecOBDFFDCyl[ misfireObdFFDCylIndex ] = DEM_MISFIRE_CYLINDER_NON;                                                             /* [GUD]misfireObdFFDCylIndex */
        }
        Dem_MisfireFilRecMisfireStrgIndexOfOBDFFD[ misfireObdFFDCylIndex ] = misfireIndex;                                                              /* [GUD]misfireObdFFDCylIndex */
    }

#if ( DEM_MISFIRE_OUTPUT_UDSOBDFFD_MULTIPLE_FAILED_CYL_SUPPORT == STD_ON )  /*  [FuncSw]    */
    Dem_MisfireFilRecOutputOBDFFDCylNum = DEM_MISFIRE_CYL_NUM_RM;
#endif  /* ( DEM_MISFIRE_OUTPUT_UDSOBDFFD_MULTIPLE_FAILED_CYL_SUPPORT == STD_ON )   */

#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */

    misfireFFDCylIndexNum = Dem_MisfireFFDCylIndexNum;
    for( misfireFFDCylIndex = (Dem_u08_MisfireFFDCylIndexType)0U; misfireFFDCylIndex < misfireFFDCylIndexNum; misfireFFDCylIndex++ )                    /* [GUD:for]misfireFFDCylIndex */
    {
        misfireIndex = Dem_Misfire_GetMisfireStrgIndexOfStoredFFD( misfireFFDCylIndex );                                                                /* [GUD]misfireFFDCylIndex */
        if( misfireIndex < misfireEventNum )                                                                                                            /* [GUD:if]misfireIndex */
        {
            Dem_MisfireFilRecFFDCyl[ misfireFFDCylIndex ] = Dem_MisfireMng_GetFFDCyl( misfireIndex, misfireFFDCylIndex );                               /* [GUD]misfireFFDCylIndex */
        }
        else
        {
            Dem_MisfireFilRecFFDCyl[ misfireFFDCylIndex ] = DEM_MISFIRE_CYLINDER_NON;                                                                   /* [GUD]misfireFFDCylIndex */
        }
        Dem_MisfireFilRecMisfireStrgIndexOfFFD[ misfireFFDCylIndex ]    =   misfireIndex;                                                               /* [GUD]misfireFFDCylIndex */
    }

    return;
}

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Misfire_CheckOutputFilteredObdFFD                    */
/* Description   | Check if OBD freeze frame record is the output target.   */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        Identification of an event by assigned EventId.   */
/*               | [in] Trigger :                                           */
/*               |        Specify the save trigger of misfire OBD freeze f- */
/*               |        rame record.                                      */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : Output target                             */
/*               |        FALSE : Not output target                         */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | refactor function.                                       */
/*   v5-9-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_Misfire_CheckOutputFilteredObdFFD
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) Trigger,
    P2VAR( Dem_MisfireCylinderNumberType, AUTOMATIC, AUTOMATIC ) MisfireCylinderNumberOutputPtr
)
{
    VAR( boolean, AUTOMATIC ) retVal;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndex;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndexObdFFDConfig;
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) misfireObdFFDCylIndexNum;
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) misfireObdFFDCylIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvId;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) misfireObdFFDCyl;

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
            misfireIndexObdFFDConfig = Dem_MisfireFilRecMisfireStrgIndexOfOBDFFD[ misfireObdFFDCylIndex ];          /* [GUD]misfireObdFFDCylIndex */

            if( misfireIndexObdFFDConfig == misfireIndex )
            {
                misfireObdFFDCyl =  Dem_MisfireFilRecOBDFFDCyl[ misfireObdFFDCylIndex ];                            /* [GUD]misfireObdFFDCylIndex */

                retVal = Dem_Misfire_GetOutputFilteredObdFFDCylinderNumber( misfireObdFFDCyl, MisfireCylinderNumberOutputPtr );
            }
        }
    }
    return retVal;
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */


/****************************************************************************/
/* Function Name | Dem_Misfire_CheckOutputFilteredFFD                       */
/* Description   | Check if freeze frame record is the output target.       */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        Identification of an event by assigned EventId.   */
/*               | [in] Trigger :                                           */
/*               |        Specify the save trigger of misfire freeze frame- */
/*               |         record.                                          */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : Output target                             */
/*               |        FALSE : Not output target                         */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | refactor function.                                       */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_Misfire_CheckOutputFilteredFFD
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) Trigger,
    P2VAR( Dem_MisfireCylinderNumberType, AUTOMATIC, AUTOMATIC ) MisfireCylinderNumberOutputPtr
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
            misfireIndexFFDConfig   = Dem_MisfireFilRecMisfireStrgIndexOfFFD[ misfireFFDCylIndex ];         /* [GUD]misfireFFDCylIndex */

            if( misfireIndexFFDConfig == misfireIndex )
            {
                /*  output target record information        */
                misfireFFDCyl = Dem_MisfireFilRecFFDCyl[ misfireFFDCylIndex ];                              /* [GUD]misfireFFDCylIndex */

                *MisfireCylinderNumberOutputPtr =   Dem_CfgInfoPm_GetMisfireCylinderNumberFromCylBit( misfireFFDCyl );

                retVal = (boolean)TRUE;
            }
        }
    }

    return retVal;
}


#if ( DEM_OBDFFD_SUPPORT == STD_ON )
#if ( DEM_MISFIRE_OUTPUT_UDSOBDFFD_MULTIPLE_FAILED_CYL_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_Misfire_GetOutputMisfireCylinderNumber               */
/* Description   | Get Output MisfireCylinderNumber.                        */
/* Preconditions |                                                          */
/* Parameters    | [in] MisfireObdFFDCyl :                                  */
/*               |        OBD FFD Cylinder Index.                           */
/* Parameters    | [in] MisfireCylinderNumberOutputPtr :                    */
/*               |        Output MisfireCylinderNumber.                     */
/* Return Value  | boolean                                                  */
/*               |          TRUE  : Output.                                 */
/*               |          FALSE : No Output cylinder number.              */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-9-0      | new created.                                             */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_Misfire_GetOutputFilteredObdFFDCylinderNumber
(
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) MisfireObdFFDCyl,
    P2VAR( Dem_MisfireCylinderNumberType, AUTOMATIC, AUTOMATIC ) MisfireCylinderNumberOutputPtr
)
{
    *MisfireCylinderNumberOutputPtr =   Dem_CfgInfoPm_GetMisfireCylinderNumberFromCylBit( MisfireObdFFDCyl );

    return (boolean)TRUE;
}
#endif  /* ( DEM_MISFIRE_OUTPUT_UDSOBDFFD_MULTIPLE_FAILED_CYL_SUPPORT == STD_OFF )  */

#if ( DEM_MISFIRE_OUTPUT_UDSOBDFFD_MULTIPLE_FAILED_CYL_SUPPORT == STD_ON )

/****************************************************************************/
/* Function Name | Dem_Misfire_GetOutputMisfireCylinderNumber               */
/* Description   | Get Output MisfireCylinderNumber.                        */
/* Preconditions |                                                          */
/* Parameters    | [in] MisfireObdFFDCyl :                                  */
/*               |        OBD FFD Cylinder Index.                           */
/* Parameters    | [in] MisfireCylinderNumberOutputPtr :                    */
/*               |        Output MisfireCylinderNumber.                     */
/* Return Value  | boolean                                                  */
/*               |          TRUE  : Output.                                 */
/*               |          FALSE : No Output cylinder number.              */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-9-0      | new created.                                             */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_Misfire_GetOutputFilteredObdFFDCylinderNumber
(
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) MisfireObdFFDCyl,
    P2VAR( Dem_MisfireCylinderNumberType, AUTOMATIC, AUTOMATIC ) MisfireCylinderNumberOutputPtr
)
{
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireCylinderCnt;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireCylinderNum;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireCylinderStart;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) misfireCylinderBitCheck;
    VAR( boolean, AUTOMATIC ) retVal;

    retVal      =   (boolean)FALSE;

    misfireCylinderNum      = Dem_MisfireCylinderNum;
    misfireCylinderStart    = Dem_MisfireFilRecOutputOBDFFDCylNum;

    for( misfireCylinderCnt = misfireCylinderStart; misfireCylinderCnt < misfireCylinderNum; misfireCylinderCnt++ )
    {
        misfireCylinderBitCheck =   MisfireObdFFDCyl & (Dem_MisfireCylinderType)( DEM_MISFIRE_CHECK_CYLINDER_BIT << misfireCylinderCnt );
        if( misfireCylinderBitCheck != DEM_MISFIRE_CYLINDER_NON )
        {
            /*  get output cylinder number.             */
            *MisfireCylinderNumberOutputPtr     = misfireCylinderCnt;

            /*  latch next search cylinder number.      */
            Dem_MisfireFilRecOutputOBDFFDCylNum = misfireCylinderCnt + (Dem_MisfireCylinderNumberType)1U;   /* no wrap around */

            /*  output cylinder number.                 */
            retVal = (boolean)TRUE;
            break;
        }
    }
    if ( retVal == (boolean)FALSE )
    {
        /*  reset latched cylinder number.      */
        Dem_MisfireFilRecOutputOBDFFDCylNum = DEM_MISFIRE_CYL_NUM_RM;
    }

    return retVal;
}

#endif  /* ( DEM_MISFIRE_OUTPUT_UDSOBDFFD_MULTIPLE_FAILED_CYL_SUPPORT == STD_ON ) */
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */

#endif  /* ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_OFF ) */

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
/*  v5-6-0         :2024-01-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
