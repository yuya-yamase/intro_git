/* Dem_MisfireMngVld_c(v5-10-0)                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/MisfireMngVld/CODE                                    */
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

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
#include "../../../../inc/Dem_Rc_DataMng.h"
#include "../../../../inc/Dem_Rc_RecMngCmn.h"
#include "../../../../inc/Dem_Rc_RecMngCmn_Table.h"
#include "../../../../cfg/Dem_Misfire_Cfg.h"
#include "../../../../inc/Dem_Rc_MisfireMng.h"
#include "../../../../inc/Dem_Rc_SimilarMng.h"
#include "../../../../inc/Dem_Rc_ClrInfoMng.h"

#include "Dem_MisfireMng_local.h"
#include "../Dem_DataMng_local.h"
#include "../SimilarMng/Dem_SimilarMng_local.h"

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
static FUNC( void, DEM_CODE ) Dem_MisfireMng_VerifyEvent
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex,
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) ClearID,
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) ClrInfoNvmReadResult,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ClearEventFlgPtr
);
static FUNC( void, DEM_CODE ) Dem_MisfireMng_VerifyFault
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ClearEventFlgPtr
);
static FUNC( void, DEM_CODE ) Dem_MisfireMng_VerifyFFD
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
static FUNC( boolean, DEM_CODE ) Dem_MisfireMng_FactoryCheckMisfireEvent
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex
);
static FUNC( boolean, DEM_CODE ) Dem_MisfireMng_ClearIdCheckMisfireEvent
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex,
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) ClearID
);
static FUNC( boolean, DEM_CODE ) Dem_MisfireMng_ConsistencyCheckMisfireEvent
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex,
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex
);
static FUNC( boolean, DEM_CODE ) Dem_MisfireMng_ConsistencyCheckMisfireWithoutFault
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex
);
static FUNC( void, DEM_CODE ) Dem_MisfireMng_NvMClearMisfireEvent
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex
);
static FUNC( void, DEM_CODE ) Dem_MisfireMng_ConsistencyUpdateMisfireEvent
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex
);

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
#if ( DEM_OBDONUDS_SUPPORT == STD_ON )
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
static FUNC( void, DEM_CODE ) Dem_MisfireMng_CorrectMisfireOBDFFDLink
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndexBase,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndexPair
);
#endif /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )    */
#endif /* ( DEM_OBDONUDS_SUPPORT == STD_ON )                */
#endif /* ( DEM_OBDFFD_SUPPORT == STD_ON )                  */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/



/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>


/****************************************************************************/
/* Function Name | Dem_MisfireMng_DataVerify                                */
/* Description   | verify misfire event data.                               */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the specific ev- */
/*               |        ent record.                                       */
/*               | [in] ClearID                                             */
/*               | [in] ClrInfoNvmReadResult                                */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |          DEM_IRT_OK      : DataVerify completed.         */
/*               |          DEM_IRT_PENDING : Continue DataVerify.          */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-9-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MisfireMng_DataVerify
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,        /* [PRMCHK:CALLER] */
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) ClearID,
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) ClrInfoNvmReadResult
)
{
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) misfirePairEventStrgIndex;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) pairMisfireIndex;
#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )           */
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndex;
    VAR( boolean, AUTOMATIC ) clearEventFlg;

    clearEventFlg = (boolean)FALSE;

    misfireIndex = DEM_MISFIRE_STRGINDEX_INVALID;

    /*  verify misfire event( related event and fault record ) : emission.      */
    (void)Dem_CfgInfoPm_CnvEventStrgIndexToMisfireStrgIndex( EventStrgIndex, &misfireIndex ); /* no return check required */    /* [GUDCHK:CALLER]EventStrgIndex */
    Dem_MisfireMng_VerifyEvent( EventStrgIndex, misfireIndex, ClearID, ClrInfoNvmReadResult, &clearEventFlg );                  /* [GUDCHK:CALLER]EventStrgIndex */

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    /* verify misfire event( related event and fault record ) : CAT      */
    /* get eventindex of CAT */
    misfirePairEventStrgIndex = Dem_CfgInfoPm_GetEventStrgIndex_MisfireCAT();                                                   /* [GUD:RET:AllValue] misfirePairEventStrgIndex */

    pairMisfireIndex = DEM_MISFIRE_STRGINDEX_INVALID;
    (void)Dem_CfgInfoPm_CnvEventStrgIndexToMisfireStrgIndex( misfirePairEventStrgIndex, &pairMisfireIndex ); /* no return check required */ /* [GUD] misfirePairEventStrgIndex */

    /* No process if clear flag is TRUE in emission process */
    if( clearEventFlg == (boolean)FALSE )
    {
        Dem_MisfireMng_VerifyEvent( misfirePairEventStrgIndex, pairMisfireIndex, ClearID, ClrInfoNvmReadResult, &clearEventFlg );           /* [GUD] misfirePairEventStrgIndex */
    }

#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )           */

    if( clearEventFlg == (boolean)FALSE )
    {
        /*  verify misfire event( related FFD ) : Emission.      */
        Dem_MisfireMng_VerifyFFD( EventStrgIndex );                                                                             /* [GUDCHK:CALLER]EventStrgIndex */

        if( Dem_EventNvMStatus[ EventStrgIndex ] == DEM_RECMNGCMN_NVM_STS_NOT_VERIFIED )                                        /* [GUDCHK:CALLER]EventStrgIndex */
        {
            Dem_EventNvMStatus[ EventStrgIndex ] = DEM_RECMNGCMN_NVM_STS_NON_TARGET;                                            /* [GUDCHK:CALLER]EventStrgIndex */
        }

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
        /*  verify misfire event( related FFD ) : CAT.      */
        Dem_MisfireMng_VerifyFFD( misfirePairEventStrgIndex );                                                                  /* [GUD] misfirePairEventStrgIndex */

        if( Dem_EventNvMStatus[ misfirePairEventStrgIndex ] == DEM_RECMNGCMN_NVM_STS_NOT_VERIFIED )                             /* [GUD] misfirePairEventStrgIndex */
        {
            Dem_EventNvMStatus[ misfirePairEventStrgIndex ] = DEM_RECMNGCMN_NVM_STS_NON_TARGET;                                 /* [GUD] misfirePairEventStrgIndex */
        }

#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
#if ( DEM_OBDONUDS_SUPPORT == STD_ON )  /*  [FuncSw]    */
        Dem_MisfireMng_CorrectMisfireOBDFFDLink( EventStrgIndex, misfirePairEventStrgIndex );
#endif  /* ( DEM_OBDONUDS_SUPPORT == STD_ON )           */
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */

#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )           */
    }
    else
    {
        Dem_MisfireMng_NvMClearMisfireEvent( EventStrgIndex, misfireIndex );
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
        Dem_MisfireMng_NvMClearMisfireEvent( misfirePairEventStrgIndex, pairMisfireIndex );                                     /* [GUD] misfirePairEventStrgIndex */
#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )           */
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_MisfireMng_VerifyEvent                               */
/* Description   | verify misfire event data.                               */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in] MisfireIndex                                        */
/*               | [in] ClearID                                             */
/*               | [in] ClrInfoNvmReadResult                                */
/*               | [in/out] ClearEventFlgPtr                                */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_MisfireMng_VerifyEvent
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex,
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) ClearID,
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) ClrInfoNvmReadResult,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ClearEventFlgPtr
)
{
    VAR( boolean, AUTOMATIC ) resultOfFactoryCheck;
    VAR( boolean, AUTOMATIC ) resultOfCleaIdCheck;

    resultOfFactoryCheck = Dem_MisfireMng_FactoryCheckMisfireEvent( EventStrgIndex, MisfireIndex );
    if( resultOfFactoryCheck == (boolean)FALSE )
    {
        if( ClrInfoNvmReadResult != DEM_IRT_NG )
        {
            resultOfCleaIdCheck  = Dem_MisfireMng_ClearIdCheckMisfireEvent( EventStrgIndex, MisfireIndex, ClearID );
            if( resultOfCleaIdCheck == (boolean)TRUE )
            {
                Dem_MisfireMng_VerifyFault( EventStrgIndex, MisfireIndex, ClearEventFlgPtr );
            }
            else
            {
                *ClearEventFlgPtr = (boolean)TRUE;
            }
        }
        else
        {
            *ClearEventFlgPtr = (boolean)TRUE;
        }
    }
    else
    {
        *ClearEventFlgPtr = (boolean)TRUE;
    }

    return;
}



/****************************************************************************/
/* Function Name | Dem_MisfireMng_VerifyFault                               */
/* Description   | verify misfire event data.                               */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in] MisfireIndex                                        */
/*               | [in/out] ClearEventFlgPtr                                */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_MisfireMng_VerifyFault
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ClearEventFlgPtr
)
{
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetEventIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndexOfFaultRecord;
    VAR( boolean, AUTOMATIC ) resultOfConsistencyCheck;

    faultIndex = DEM_FAULTINDEX_INITIAL;
    (void)Dem_DataMngC_GetER_FaultIndex( EventStrgIndex, &faultIndex ); /* no return check required */          /* [GUD:RET:DEM_IRT_OK] EventStrgIndex */
    resultOfGetEventIndex = Dem_DataMngC_GetFR_EventStrgIndex( faultIndex, &eventStrgIndexOfFaultRecord );
    if( resultOfGetEventIndex == DEM_IRT_OK )
    {
        if( EventStrgIndex == eventStrgIndexOfFaultRecord )
        {
            resultOfConsistencyCheck = Dem_MisfireMng_ConsistencyCheckMisfireEvent( EventStrgIndex, MisfireIndex, faultIndex );
            if( resultOfConsistencyCheck == (boolean)FALSE)
            {
                *ClearEventFlgPtr = (boolean)TRUE;
            }
        }
        else
        {
            *ClearEventFlgPtr = (boolean)TRUE;
        }
    }
    else
    {
        if( faultIndex != DEM_FAULTINDEX_INITIAL )
        {
            *ClearEventFlgPtr = (boolean)TRUE;
        }
        else
        {
            resultOfConsistencyCheck = Dem_MisfireMng_ConsistencyCheckMisfireWithoutFault( EventStrgIndex, MisfireIndex );
            if( resultOfConsistencyCheck == (boolean)FALSE )
            {
                *ClearEventFlgPtr = (boolean)TRUE;
            }
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_MisfireMng_VerifyFFD                                 */
/* Description   | verify misfire event data.                               */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_MisfireMng_VerifyFFD
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFaultRec;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_FaultRecordType, AUTOMATIC ) faultRecord;
    VAR( boolean, AUTOMATIC ) consistencyIdUpdateFlg;

    faultIndex = DEM_FAULTINDEX_INITIAL;

    (void)Dem_DataMngC_GetER_FaultIndex( EventStrgIndex, &faultIndex ); /* no return check required */  /* [GUD:RET:DEM_IRT_OK] EventStrgIndex */
    resultOfGetFaultRec = Dem_DataMngC_GetFaultRecord( faultIndex, &faultRecord );                      /* [GUD:RET:DEM_IRT_OK] faultIndex *//* [GUD:IF_GUARDED faultIndex ]EventStrgIndex */

    if( resultOfGetFaultRec == DEM_IRT_OK )
    {
        consistencyIdUpdateFlg = (boolean)FALSE;

        Dem_FFDMng_Verified( EventStrgIndex, faultIndex, &consistencyIdUpdateFlg );             /* [GUD] EventStrgIndex *//* [GUD] faultIndex */
#if ( DEM_TSFF_PM_SUPPORT == STD_ON ) /*  [FuncSw]    */
        Dem_TSFFDMng_Verified( EventStrgIndex, faultIndex );                                    /* [GUD] faultIndex */
#endif /* (DEM_TSFF_PM_SUPPORT == STD_ON) */

#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
        Dem_ObdFFDMng_Verified( EventStrgIndex, faultIndex, &consistencyIdUpdateFlg );          /* [GUD] faultIndex */
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */

        if( consistencyIdUpdateFlg == (boolean)TRUE )
        {
            Dem_MisfireMng_ConsistencyUpdateMisfireEvent( EventStrgIndex, faultIndex );         /* [GUD] faultIndex */
        }

        Dem_DataMng_VerifyTrigger( EventStrgIndex, faultIndex );                                /* [GUD] faultIndex */

        if( Dem_FaultNvMStatus[ faultIndex ] == DEM_RECMNGCMN_NVM_STS_NOT_VERIFIED )            /* [GUD] faultIndex */
        {
            Dem_FaultNvMStatus[ faultIndex ] = DEM_RECMNGCMN_NVM_STS_NON_TARGET;                /* [GUD] faultIndex */
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_MisfireMng_FactoryCheckMisfireEvent                  */
/* Description   | verify misfire event data.                               */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the specific ev- */
/*               |        ent record.                                       */
/*               | [in] MisfireIndex :                                      */
/* Return Value  | boolean                                                  */
/*               |          TRUE      : Factory default                     */
/*               |          FALSE     : Non Factory default                 */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_MisfireMng_FactoryCheckMisfireEvent
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex
)
{
    VAR( boolean, AUTOMATIC ) resultOfFactoryCheck;
    VAR( boolean, AUTOMATIC ) resultOfFactoryCheckEventRecord;
    VAR( boolean, AUTOMATIC ) resultOfFactoryCheckMisfireRecord;
    VAR( boolean, AUTOMATIC ) resultOfFactoryCheckMisfireComRecord;
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON ) /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) resultOfFactoryCheckSimilarRecord;
#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )   */

    resultOfFactoryCheck = (boolean)FALSE;

    resultOfFactoryCheckEventRecord = Dem_DataMng_GetFactoryCheckResultOfEventRecord( EventStrgIndex );

    if( resultOfFactoryCheckEventRecord == (boolean)TRUE )
    {
        resultOfFactoryCheck = (boolean)TRUE;
    }
    else
    {
        resultOfFactoryCheckMisfireRecord = Dem_MisfireMng_GetFactoryCheckResultOfMisfireRecord( MisfireIndex );

        if( resultOfFactoryCheckMisfireRecord == (boolean)TRUE )
        {
            resultOfFactoryCheck = (boolean)TRUE;
        }
        else
        {
            resultOfFactoryCheckMisfireComRecord = Dem_MisfireMng_GetFactoryCheckResultOfMisfireComRecord();
            if( resultOfFactoryCheckMisfireComRecord == (boolean)TRUE )
            {
                resultOfFactoryCheck = (boolean)TRUE;
            }
            else
            {
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON ) /*  [FuncSw]    */
                resultOfFactoryCheckSimilarRecord = Dem_SimilarMng_GetFactoryCheckResult_EventStrgIndex( EventStrgIndex );
                if( resultOfFactoryCheckSimilarRecord == (boolean)TRUE )
                {
                    resultOfFactoryCheck = (boolean)TRUE;
                }
#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )   */
            }
        }
    }

    return resultOfFactoryCheck;
}


/****************************************************************************/
/* Function Name | Dem_MisfireMng_ClearIdCheckMisfireEvent                  */
/* Description   | verify misfire event data.                               */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in] MisfireIndex                                        */
/*               | [in] ClearID                                             */
/* Return Value  | boolean                                                  */
/*               |          TRUE      : ClearId check OK                    */
/*               |          FALSE     : ClearId check NG                    */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_MisfireMng_ClearIdCheckMisfireEvent
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex,
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) ClearID
)
{
    VAR( boolean, AUTOMATIC ) resultOfClearIdCheck;
    VAR( boolean, AUTOMATIC ) resultOfClearIdCheckEventRecord;
    VAR( boolean, AUTOMATIC ) resultOfClearIdCheckMisfireRecord;
    VAR( boolean, AUTOMATIC ) resultOfClearIdCheckMisfireComRecord;
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON ) /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) resultOfClearIdCheckSimilarRecord;
#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )   */

    resultOfClearIdCheck = (boolean)TRUE;

    resultOfClearIdCheckEventRecord = Dem_DataMng_CheckClearIDOfEventRecord( EventStrgIndex, ClearID );
    if( resultOfClearIdCheckEventRecord == (boolean)FALSE )
    {
        resultOfClearIdCheck = (boolean)FALSE;
    }
    else
    {
        resultOfClearIdCheckMisfireRecord = Dem_MisfireMng_CheckClearIdOfMisfireRecord( MisfireIndex, ClearID );

        if( resultOfClearIdCheckMisfireRecord == (boolean)FALSE )
        {
            resultOfClearIdCheck = (boolean)FALSE;
        }
        else
        {
            resultOfClearIdCheckMisfireComRecord = Dem_MisfireMng_CheckClearIdOfMisfireComRecord( ClearID );
            if( resultOfClearIdCheckMisfireComRecord == (boolean)FALSE )
            {
                resultOfClearIdCheck = (boolean)FALSE;
            }
            else
            {
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON ) /*  [FuncSw]    */
                resultOfClearIdCheckSimilarRecord = Dem_SimilarMng_CheckClearId_EventStrgIndex( EventStrgIndex, ClearID );
                if( resultOfClearIdCheckSimilarRecord == (boolean)FALSE )
                {
                    resultOfClearIdCheck = (boolean)FALSE;
                }
#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )   */
            }
        }
    }

    return resultOfClearIdCheck;
}


/****************************************************************************/
/* Function Name | Dem_MisfireMng_ConsistencyCheckMisfireEvent              */
/* Description   | verify misfire event data.                               */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the specific ev- */
/*               |        ent record.                                       */
/*               | [in] MisfireIndex                                        */
/*               | [in] FaultIndex                                          */
/* Return Value  | boolean                                                  */
/*               |          TRUE      : ConisistencyId check OK             */
/*               |          FALSE     : ConisistencyId check NG             */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_MisfireMng_ConsistencyCheckMisfireEvent
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex,
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex
)
{
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) consistencyId;
    VAR( boolean, AUTOMATIC ) resultOfConsistencyCheck;
    VAR( boolean, AUTOMATIC ) resultOfConsistencyCheckEventRecord;
    VAR( boolean, AUTOMATIC ) resultOfConsistencyCheckMisfireRecord;
    VAR( boolean, AUTOMATIC ) resultOfConsistencyCheckMisfireComRecord;
    VAR( Dem_EventKindType, AUTOMATIC ) eventKind;
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON ) /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) resultOfConsistencyCheckSimilarRecord;
#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )   */

    resultOfConsistencyCheck = (boolean)TRUE;

    (void)Dem_DataMng_GetFaultRecordConsistencyId( FaultIndex, &consistencyId); /* no return check required */

    resultOfConsistencyCheckEventRecord = Dem_DataMng_CheckConsistencyIdOfEventRecord( EventStrgIndex, consistencyId );

    if( resultOfConsistencyCheckEventRecord == (boolean)FALSE )
    {
        resultOfConsistencyCheck = (boolean)FALSE;
    }
    else
    {
        resultOfConsistencyCheckMisfireRecord = Dem_MisfireMng_CheckConsistencyIdOfMisfireRecord( MisfireIndex, consistencyId );

        if( resultOfConsistencyCheckMisfireRecord == (boolean)FALSE )
        {
            resultOfConsistencyCheck = (boolean)FALSE;
        }
        else
        {
            eventKind = Dem_CfgInfoPm_GetEventKindOfMisfire_InEvtStrgGrp( EventStrgIndex );         /* [GUD:RET:Not DEM_EVTKIND_TYPE_NON_OBD_EVENT] EventStrgIndex  */
            resultOfConsistencyCheckMisfireComRecord = Dem_MisfireMng_CheckConsistencyIdOfMisfireComRecord( eventKind, consistencyId );
            if( resultOfConsistencyCheckMisfireComRecord == (boolean)FALSE )
            {
                resultOfConsistencyCheck = (boolean)FALSE;
            }
            else
            {
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON ) /*  [FuncSw]    */
                resultOfConsistencyCheckSimilarRecord = Dem_SimilarMng_CheckConsistencyId_EventStrgIndex( EventStrgIndex, consistencyId );
                if( resultOfConsistencyCheckSimilarRecord == (boolean)FALSE )
                {
                    resultOfConsistencyCheck = (boolean)FALSE;
                }
#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )   */
            }
        }
    }

    return resultOfConsistencyCheck;
}


/****************************************************************************/
/* Function Name | Dem_MisfireMng_ConsistencyCheckMisfireWithoutFault       */
/* Description   | verify misfire event data.                               */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the specific ev- */
/*               |        ent record.                                       */
/*               | [in] MisfireIndex                                        */
/* Return Value  | boolean                                                  */
/*               |          TRUE      : ConisistencyId check OK             */
/*               |          FALSE     : ConisistencyId check NG             */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_MisfireMng_ConsistencyCheckMisfireWithoutFault
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex
)
{
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) consistencyId;
    VAR( boolean, AUTOMATIC ) resultOfConsistencyCheck;
    VAR( boolean, AUTOMATIC ) resultOfConsistencyCheckMisfireRecord;
    VAR( boolean, AUTOMATIC ) resultOfConsistencyCheckMisfireComRecord;
    VAR( Dem_EventKindType, AUTOMATIC ) eventKind;
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON ) /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) resultOfConsistencyCheckSimilarRecord;
#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )   */

    resultOfConsistencyCheck = (boolean)TRUE;

    Dem_DataMng_GetEventRecordConsistencyId( EventStrgIndex, &consistencyId); /* no return check required */

    resultOfConsistencyCheckMisfireRecord = Dem_MisfireMng_CheckConsistencyIdOfMisfireRecord( MisfireIndex, consistencyId );

    if( resultOfConsistencyCheckMisfireRecord == (boolean)FALSE )
    {
        resultOfConsistencyCheck = (boolean)FALSE;
    }
    else
    {
        eventKind = Dem_CfgInfoPm_GetEventKindOfMisfire_InEvtStrgGrp( EventStrgIndex );         /* [GUD:RET:Not DEM_EVTKIND_TYPE_NON_OBD_EVENT] EventStrgIndex  */
        resultOfConsistencyCheckMisfireComRecord = Dem_MisfireMng_CheckConsistencyIdOfMisfireComRecord( eventKind, consistencyId );
        if( resultOfConsistencyCheckMisfireComRecord == (boolean)FALSE )
        {
            resultOfConsistencyCheck = (boolean)FALSE;
        }
        else
        {
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON ) /*  [FuncSw]    */
            resultOfConsistencyCheckSimilarRecord = Dem_SimilarMng_CheckConsistencyId_EventStrgIndex( EventStrgIndex, consistencyId );
            if( resultOfConsistencyCheckSimilarRecord == (boolean)FALSE )
            {
                resultOfConsistencyCheck = (boolean)FALSE;
            }
#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )   */
        }
    }

    return resultOfConsistencyCheck;
}


/****************************************************************************/
/* Function Name | Dem_MisfireMng_NvMClearMisfireEvent                      */
/* Description   | clear misfire event data.                                */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in] MisfireIndex                                        */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_MisfireMng_NvMClearMisfireEvent
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex
)
{
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindEvent;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireEventNum;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindMisfire;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindMisfireCom;

    misfireEventNum = Dem_MisfireEventNum;

    Dem_DataMngM_InitEventRecord( EventStrgIndex );
    recMngCmnKindEvent = Dem_RecMngCmnKindEvent;
    Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindEvent, ( Dem_u16_RecordIndexType )EventStrgIndex );

    if( MisfireIndex < misfireEventNum )
    {
        Dem_MisfireMng_ClearMisfireRecordList( MisfireIndex );
        recMngCmnKindMisfire = Dem_RecMngCmnKindMisfire;
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindMisfire, ( Dem_u16_RecordIndexType )MisfireIndex );
    }

    Dem_MisfireMng_ClearMisfireComRecord();
    recMngCmnKindMisfireCom = Dem_RecMngCmnKindMisfireCom;
    Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindMisfireCom, ( Dem_u16_RecordIndexType )0U );

#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON ) /*  [FuncSw]    */
    Dem_SimilarMng_NvMClearSimilarRecord_EventStrgIndex( EventStrgIndex );
#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )   */

    return;
}

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_MisfireMng_UpdateObdFFDInfoByInitRecordNumberIndex   */
/* Description   | Update ffd data of misfire by to initialize RecordNumber-*/
/*               | Index of Fault record.                                   */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in] ObdFreezeFrameRecordIndex                           */
/*               | [in/out] ConsistencyIdUpdateFlgPtr                       */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/*   v5-10-0     | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MisfireMng_UpdateObdFFDInfoByInitRecordNumberIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) ObdFreezeFrameRecordIndex,    /* [PRMCHK:CALLER] */
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ConsistencyIdUpdateFlgPtr
)
{
    P2CONST( AB_83_ConstV Dem_FreezeFrameRecNumClassType, AUTOMATIC, DEM_CONFIG_DATA ) freezeFrameRecNumClassPtr;
    VAR( Dem_u16_FFClassIndexType, AUTOMATIC ) obdFreezeFrameClassRef;
    VAR( Dem_u16_FFRecNumClassIndexType, AUTOMATIC ) obdFreezeframeRecNumClassRef;
    VAR( Dem_u08_FFRecordClassIndexType, AUTOMATIC ) freezeFrameRecordClassIndex;
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) trigger;
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) misfireObdFFDCylIndexNum;
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) misfireObdFFDCylIndex;
    VAR( Dem_EventKindType, AUTOMATIC ) eventKind;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvId;
    VAR( Dem_u08_MisfireKindType, AUTOMATIC ) misfireType;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) misfirePairEventStrgIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultGetMisfirePairEvent;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvIdPairEvent;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) pairMisfireIndex;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) misfirePairObdFFDCyl;

    misfireObdFFDCylIndexNum = Dem_MisfireObdFFDCylIndexNum;

    eventKind = Dem_CfgInfoPm_GetEventKindOfMisfire_InEvtStrgGrp( EventStrgIndex );         /* [GUD:RET:Not DEM_EVTKIND_TYPE_NON_OBD_EVENT] EventStrgIndex  */
    if( ( eventKind & DEM_EVTKIND_TYPE_MISFIRE_EVENT ) == DEM_EVTKIND_TYPE_MISFIRE_EVENT )
    {
        Dem_CfgInfoPm_GetOBDFreezeFrameAndRecNumClass( EventStrgIndex, &obdFreezeFrameClassRef, &obdFreezeframeRecNumClassRef );        /* [GUD]EventStrgIndex *//* [GUD:OUT:IF_GUARDED: EventStrgIndex] obdFreezeFrameClassRef *//* [GUD:OUT:IF_GUARDED: EventStrgIndex] obdFreezeframeRecNumClassRef */

        freezeFrameRecNumClassPtr = &Dem_FreezeFrameRecNumClassTable[obdFreezeframeRecNumClassRef];                                     /* [GUD]obdFreezeframeRecNumClassRef *//* [GUD:CFG:IF_GUARDED: obdFreezeframeRecNumClassRef] freezeFrameRecNumClassPtr */
        freezeFrameRecordClassIndex = freezeFrameRecNumClassPtr->DemFreezeFrameRecordClassRef[ObdFreezeFrameRecordIndex];               /* [GUD]freezeFrameRecNumClassPtr    *//* [GUDCHK:CALLER]ObdFreezeFrameRecordIndex    *//* [GUD:CFG:IF_GUARDED: freezeFrameRecNumClassPtr/ObdFreezeFrameRecordIndex] freezeFrameRecordClassIndex *//* [ARYCHK] DEM_FF_RECORD_CLASS_REF_MAX_NUM / 1 / ObdFreezeFrameRecordIndex */

        trigger =   Dem_CfgInfoPm_GetFreezeFrameRecordTriggerType( freezeFrameRecordClassIndex );                                       /* [GUDCHK:CALLER]ObdFreezeFrameRecordIndex */

        retCnvId = Dem_CfgInfoPm_CnvEventStrgIndexToMisfireStrgIndex( EventStrgIndex, &misfireIndex );                                  /* [GUD]EventStrgIndex */
        if( retCnvId == DEM_IRT_OK )
        {
            misfireObdFFDCylIndex = Dem_CfgInfoPm_GetObdFFDCylIndexOfMisfire( trigger );

            if( misfireObdFFDCylIndex < misfireObdFFDCylIndexNum )
            {
                /* Clear ObdFFDCyl */
                Dem_MisfireMng_InitObdFFDCyl( misfireIndex, misfireObdFFDCylIndex );

                *ConsistencyIdUpdateFlgPtr = (boolean)TRUE;

                resultGetMisfirePairEvent = Dem_CfgInfoPm_GetMisfirePairEventStrgIndexByStrgIndex( EventStrgIndex, &misfirePairEventStrgIndex );    /* [GUD]EventStrgIndex */
                if( resultGetMisfirePairEvent == DEM_IRT_OK )
                {
                    retCnvIdPairEvent = Dem_CfgInfoPm_CnvEventStrgIndexToMisfireStrgIndex( misfirePairEventStrgIndex, &pairMisfireIndex );
                    if( retCnvIdPairEvent == DEM_IRT_OK )
                    {
                        misfirePairObdFFDCyl = Dem_MisfireMng_GetObdFFDCyl( pairMisfireIndex, misfireObdFFDCylIndex );
                        if( misfirePairObdFFDCyl == DEM_MISFIRE_CYLINDER_NON )
                        {
                            /* Clear MisfireKindOfObdFFD, if ObdFFDCyl of paired events is Non */
                            Dem_MisfireMng_InitMisfireKindOfObdFFD( misfireObdFFDCylIndex );
                        }
                        else
                        {
                            /* Set kind of a another event to MisfireKindOfObdFFD, if ObdFFDCyl of the another event is not Non */
                            if( ( eventKind & DEM_EVTKIND_TYPE_MISFIRE_CAT_EVENT ) == DEM_EVTKIND_TYPE_MISFIRE_CAT_EVENT )
                            {
                                misfireType = DEM_MISFIRE_KIND_EMISSION;
                            }
                            else
                            {
                                misfireType = DEM_MISFIRE_KIND_CAT;
                            }
                            Dem_MisfireMng_SetMisfireKindOfObdFFD( misfireObdFFDCylIndex, misfireType );

                        }
                    }
                }
                else
                {
                    Dem_MisfireMng_InitMisfireKindOfObdFFD( misfireObdFFDCylIndex );
                }
            }
        }
    }

    return;
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */


/****************************************************************************/
/* Function Name | Dem_MisfireMng_UpdateFFDInfoByInitRecordNumberIndex      */
/* Description   | Update ffd data of misfire by to initialize RecordNumber-*/
/*               | Index of Fault record.                                   */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in] FreezeFrameRecordIndex                              */
/*               | [in/out] ConsistencyIdUpdateFlgPtr                       */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/*   v5-10-0     | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MisfireMng_UpdateFFDInfoByInitRecordNumberIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordIndex,       /* [PRMCHK:CALLER] */
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ConsistencyIdUpdateFlgPtr
)
{

    P2CONST( AB_83_ConstV Dem_FreezeFrameRecNumClassType, AUTOMATIC, DEM_CONFIG_DATA ) freezeFrameRecNumClassPtr;
    VAR( Dem_u16_FFClassIndexType, AUTOMATIC ) freezeFrameClassRef;
    VAR( Dem_u16_FFRecNumClassIndexType, AUTOMATIC ) freezeframeRecNumClassRef;
    VAR( Dem_u08_FFRecordClassIndexType, AUTOMATIC ) freezeFrameRecordClassIndex;
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) trigger;
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) misfireFFDCylIndexNum;
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) misfireFFDCylIndex;
    VAR( Dem_EventKindType, AUTOMATIC ) eventKind;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvId;
    VAR( Dem_u08_MisfireKindType, AUTOMATIC ) misfireType;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) misfirePairEventStrgIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultGetMisfirePairEvent;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvIdPairEvent;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) pairMisfireIndex;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) misfirePairFFDCyl;

    misfireFFDCylIndexNum = Dem_MisfireFFDCylIndexNum;

    eventKind = Dem_CfgInfoPm_GetEventKindOfMisfire_InEvtStrgGrp( EventStrgIndex );         /* [GUD:RET:Not DEM_EVTKIND_TYPE_NON_OBD_EVENT] EventStrgIndex  */
    if( ( eventKind & DEM_EVTKIND_TYPE_MISFIRE_EVENT ) == DEM_EVTKIND_TYPE_MISFIRE_EVENT )
    {
        Dem_CfgInfoPm_GetFreezeFrameAndRecNumClass( EventStrgIndex, &freezeFrameClassRef, &freezeframeRecNumClassRef ); /* [GUD:OUT:IF_GUARDED: EventStrgIndex] freezeFrameClassRef *//* [GUD:OUT:IF_GUARDED: EventStrgIndex] freezeframeRecNumClassRef */

        freezeFrameRecNumClassPtr = &Dem_FreezeFrameRecNumClassTable[freezeframeRecNumClassRef];                        /* [GUD]freezeframeRecNumClassRef *//* [GUD:CFG:IF_GUARDED: freezeframeRecNumClassRef] freezeFrameRecNumClassPtr */
        freezeFrameRecordClassIndex = freezeFrameRecNumClassPtr->DemFreezeFrameRecordClassRef[FreezeFrameRecordIndex];  /* [GUD]freezeFrameRecNumClassPtr *//* [GUDCHK:CALLER]FreezeFrameRecordIndex    *//* [GUD:CFG:IF_GUARDED: freezeFrameRecNumClassPtr/FreezeFrameRecordIndex] freezeFrameRecordClassIndex *//* [ARYCHK] DEM_FF_RECORD_CLASS_REF_MAX_NUM / 1 / FreezeFrameRecordIndex */

        trigger =   Dem_CfgInfoPm_GetFreezeFrameRecordTriggerType( freezeFrameRecordClassIndex );                       /* [GUDCHK:CALLER]FreezeFrameRecordIndex */

        retCnvId = Dem_CfgInfoPm_CnvEventStrgIndexToMisfireStrgIndex( EventStrgIndex, &misfireIndex );
        if( retCnvId == DEM_IRT_OK )
        {
            misfireFFDCylIndex = Dem_CfgInfoPm_GetFFDCylIndexOfMisfire( trigger );

            if( misfireFFDCylIndex < misfireFFDCylIndexNum )
            {
                /* Clear FFDCyl */
                Dem_MisfireMng_InitFFDCyl( misfireIndex, misfireFFDCylIndex );

                *ConsistencyIdUpdateFlgPtr = (boolean)TRUE;

                resultGetMisfirePairEvent = Dem_CfgInfoPm_GetMisfirePairEventStrgIndexByStrgIndex( EventStrgIndex, &misfirePairEventStrgIndex );
                if( resultGetMisfirePairEvent == DEM_IRT_OK )
                {
                    retCnvIdPairEvent = Dem_CfgInfoPm_CnvEventStrgIndexToMisfireStrgIndex( misfirePairEventStrgIndex, &pairMisfireIndex );
                    if( retCnvIdPairEvent == DEM_IRT_OK )
                    {
                        misfirePairFFDCyl = Dem_MisfireMng_GetFFDCyl( pairMisfireIndex, misfireFFDCylIndex );
                        if( misfirePairFFDCyl == DEM_MISFIRE_CYLINDER_NON )
                        {
                            /* Clear MisfireKindOfFFD, if FFDCyl of paired events is Non */
                            Dem_MisfireMng_InitMisfireKindOfFFD( misfireFFDCylIndex );
                        }
                        else
                        {
                            /* Set kind of a another event to MisfireKindOfFFD, if FFDCyl of the another event is not Non */
                            if( ( eventKind & DEM_EVTKIND_TYPE_MISFIRE_CAT_EVENT ) == DEM_EVTKIND_TYPE_MISFIRE_CAT_EVENT )
                            {
                                misfireType = DEM_MISFIRE_KIND_EMISSION;
                            }
                            else
                            {
                                misfireType = DEM_MISFIRE_KIND_CAT;
                            }
                            Dem_MisfireMng_SetMisfireKindOfFFD( misfireFFDCylIndex, misfireType );

                        }
                    }
                }
                else
                {
                    Dem_MisfireMng_InitMisfireKindOfFFD( misfireFFDCylIndex );
                }
            }
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_MisfireMng_ConsistencyUpdateMisfireEvent             */
/* Description   | update consistencyId of misfire event.                   */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in] FaultIndex :                                        */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_MisfireMng_ConsistencyUpdateMisfireEvent
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex
)
{
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndex;
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) consistencyId;
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON ) /*  [FuncSw]    */
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) similarStrgIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvId;
#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )   */
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( Dem_EventKindType, AUTOMATIC ) eventKind;
#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )           */

    consistencyId = DEM_CONSISTENCY_INITIAL;

    Dem_DataMng_UpdateFaultRecordConsistencyId_Misfire( FaultIndex, &consistencyId );

    Dem_DataMng_SetEventRecordConsistencyId( EventStrgIndex, consistencyId );

    (void)Dem_CfgInfoPm_CnvEventStrgIndexToMisfireStrgIndex( EventStrgIndex, &misfireIndex ); /* no return check required */

    Dem_MisfireMng_SetConsistencyIdOfMisfireRecord( misfireIndex, consistencyId );

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    eventKind = Dem_CfgInfoPm_GetEventKindOfMisfire_InEvtStrgGrp( EventStrgIndex );         /* [GUD:RET:Not DEM_EVTKIND_TYPE_NON_OBD_EVENT] EventStrgIndex  */

    if( ( eventKind & DEM_EVTKIND_TYPE_MISFIRE_CAT_EVENT ) == DEM_EVTKIND_TYPE_MISFIRE_CAT_EVENT )
    {
        Dem_MisfireMng_SetConsistencyIdOfMisfireComForCAT( consistencyId );
    }
    else
#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )           */
    {
        Dem_MisfireMng_SetConsistencyIdOfMisfireComForEmission( consistencyId );
    }

#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON ) /*  [FuncSw]    */
    retCnvId = Dem_CfgInfoPm_CnvEventStrgIndexToSimilarStrgIndex( EventStrgIndex, &similarStrgIndex );

    if ( retCnvId == DEM_IRT_OK )
    {
        Dem_SimilarMng_SetConsistencyId( similarStrgIndex, consistencyId );
    }
#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )   */

    return;
}

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
#if ( DEM_OBDONUDS_SUPPORT == STD_ON )
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
/****************************************************************************/
/* Function Name | Dem_MisfireMng_CorrectMisfireOBDFFDLink                  */
/* Description   | correct Misfire OBDFFD link.                             */
/* Preconditions |                                                          */
/* Parameters    | [in]  EventStrgIndexBase : event index.                  */
/*               | [in]  EventStrgIndexPair : event index.                  */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-9-0      | new created.                                             */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_MisfireMng_CorrectMisfireOBDFFDLink
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndexBase,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndexPair
)
{
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndexDest;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndexSrc;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndexDest;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndexSrc;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) statusOfDTC_Dest;

    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndexBase;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndexPair;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndexSrc;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndexDest;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;

    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) misfireObdFFDCylIndex;
    VAR( Dem_u08_MisfireKindType, AUTOMATIC ) misfireKindOfFFD;

    VAR( boolean, AUTOMATIC ) existOBDFFDBase;
    VAR( boolean, AUTOMATIC ) existOBDFFDPair;
    VAR( boolean, AUTOMATIC ) compareResult;

    VAR( boolean, AUTOMATIC ) updateCorrectOBDFFDFlag;

    failRecordNum = Dem_FailRecordNum;

    /*  get faultIndex.             */
    (void)Dem_DataMngC_GetER_FaultIndex( EventStrgIndexBase, &faultIndexBase );     /* no return check required */
    (void)Dem_DataMngC_GetER_FaultIndex( EventStrgIndexPair, &faultIndexPair );     /* no return check required */

    /*  Check EventStrgIndexBase and EventStrgIndexPair have fault records.         */
    /*  If only one side has a fault record, the process ends without any action.   */
    if (( faultIndexBase < failRecordNum ) && ( faultIndexPair < failRecordNum ))
    {
        /*  copy OBDFFD flag : FALSE.           */
        updateCorrectOBDFFDFlag =   (boolean)FALSE;

        /*  Check if both have OBD FFDs or if both do not have OBD FFDs.            */
        existOBDFFDBase =   Dem_DataMngC_GetFR_CheckExistOBDFFD( faultIndexBase );
        existOBDFFDPair =   Dem_DataMngC_GetFR_CheckExistOBDFFD( faultIndexPair );

        /*  If only one side has OBD FFD        */
        if ( existOBDFFDBase != existOBDFFDPair )
        {
            /*  Copy OBDFFD index : have OBD FFD side to don't have OBDFFD side.    */
            if ( existOBDFFDBase == (boolean)TRUE )
            {
                /*  have OBD FFD side : faultIndexBase   */
                faultIndexSrc       =   faultIndexBase;
                eventStrgIndexSrc   =   EventStrgIndexBase;

                faultIndexDest      =   faultIndexPair;
                eventStrgIndexDest  =   EventStrgIndexPair;
            }
            else
            {
                /*  have OBD FFD side : faultIndexPair   */
                faultIndexSrc       =   faultIndexPair;
                eventStrgIndexSrc   =   EventStrgIndexPair;

                faultIndexDest      =   faultIndexBase;
                eventStrgIndexDest  =   EventStrgIndexBase;
            }

            /*  check CopyDest's statusOfDTC.            */
            (void)Dem_DataMngC_GetER_StatusOfDTC( eventStrgIndexDest, &statusOfDTC_Dest );  /* no return check required */
            if (( statusOfDTC_Dest & ( DEM_UDS_STATUS_PDTC | DEM_UDS_STATUS_CDTC ) ) == DEM_DTCSTATUS_BYTE_ALL_OFF )
            {
                /*  CopyDest fault record not have fault information.       */
                /*  no action.                                              */
            }
            else
            {
                /*  copy OBDFFD index.                  */
                /*  copy OBDFFD flag : TRUE.            */
                updateCorrectOBDFFDFlag =   (boolean)TRUE;
            }
        }
        else
        {
            if ( existOBDFFDBase == (boolean)TRUE )
            {
                /*----------------------------------------------*/
                /*  Both misfire events have OBD FFDs.          */
                /*----------------------------------------------*/
                /*  Compare OBD FFD indexes.                    */
                compareResult   =   Dem_DataMngC_CompareFR_ObdRecordNumberIndex( faultIndexBase, faultIndexPair );
                if ( compareResult == (boolean)TRUE )
                {
                    /*------------------------------------------*/
                    /*  same OBDFFDs. no update.                */
                    /*------------------------------------------*/
                }
                else
                {
                    /*------------------------------------------*/
                    /*  different OBDFFDs.                      */
                    /*------------------------------------------*/
                    /*  check correct MisfireInfo from Dem_MisfireComRecord.MisfireKindOfOBDFFD[].  */
                    misfireObdFFDCylIndex   =   Dem_CfgInfoPm_GetObdFFDCylIndexOfMisfire( DEM_TRIGGER_ON_TEST_FAILED_THIS_OPERATION_CYCLE );
                    misfireKindOfFFD        =   Dem_MisfireMng_GetMisfireKindOfObdFFD( misfireObdFFDCylIndex );

                    if ( misfireKindOfFFD != DEM_MISFIRE_KIND_INVALID )
                    {
                        if ( misfireKindOfFFD == DEM_MISFIRE_KIND_EMISSION )
                        {
                            /*  correct Misfire : Emission(faultIndexBase). */
                            faultIndexSrc       =   faultIndexBase;
                            eventStrgIndexSrc   =   EventStrgIndexBase;

                            faultIndexDest      =   faultIndexPair;
                            eventStrgIndexDest  =   EventStrgIndexPair;
                        }
                        else
                        {
                            /*  correct Misfire : CAT(faultIndexPair).      */
                            faultIndexSrc       =   faultIndexPair;
                            eventStrgIndexSrc   =   EventStrgIndexPair;

                            faultIndexDest      =   faultIndexBase;
                            eventStrgIndexDest  =   EventStrgIndexBase;
                        }

                        /*  copy OBDFFD index.                  */
                        updateCorrectOBDFFDFlag =   (boolean)TRUE;
                    }
                    else
                    {
                        /*  There's no OBD FFD information in MisfireCom record.    */
                        /*  Because after verified, it's impossible for a fault record's OBD FFD are exist but no MisfireCom record's OBD FFD are not exist.    */
                        /*  no update.                                              */
                    }
                }
            }
            else
            {
                /*----------------------------------------------*/
                /*  Both misfire events don't have OBD FFDs.    */
                /*  no update.                                  */
                /*----------------------------------------------*/
            }
        }

        /*  update OBD FFD information from correct Misfire event's information.    */
        if ( updateCorrectOBDFFDFlag == (boolean)TRUE )
        {
            /*  get MisfireRecord index.        */
            (void)Dem_CfgInfoPm_CnvEventStrgIndexToMisfireStrgIndex( eventStrgIndexDest, &misfireIndexDest );   /* no return check required */
            (void)Dem_CfgInfoPm_CnvEventStrgIndexToMisfireStrgIndex( eventStrgIndexSrc, &misfireIndexSrc );     /* no return check required */

            /*  set to NotVerified status to illegal OBD FFDs.  */
            Dem_ObdFFDMng_SetVerifiedStatus_ObdFreezeFrameRecord( faultIndexDest, faultIndexSrc );

            /*  Copy OBDFFD index.                              */
            Dem_DataMngC_CopyFR_AllObdRecordNumberIndex( faultIndexDest, faultIndexSrc );

            /*  Copy MisfireRecord.OBDFFDCyl[].                 */
            Dem_MisfireMng_CopyAllObdFFDCyl( misfireIndexDest, misfireIndexSrc );

            /*  update consistencyId to Misfire event's EventRecord/FaultRecord/MisfireRecord/MisfireComRecord. */
            /*  because update FaultRecord and MisfireRecord, always update consistencyId.                      */
            Dem_MisfireMng_ConsistencyUpdateMisfireEvent( eventStrgIndexDest, faultIndexDest );         /* [GUD] faultIndexDest */
        }
    }
    return;
}
#endif /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )    */
#endif /* ( DEM_OBDONUDS_SUPPORT == STD_ON )                */
#endif /* ( DEM_OBDFFD_SUPPORT == STD_ON )                  */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
