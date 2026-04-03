/* Dem_ClrInfoMng_UserDefMem_c(v5-5-0)                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/ClrInfoMng_UserDefMem/CODE                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../cfg/Dem_UserDefMem_Cfg.h"
#include "../../../cfg/Dem_NvM_Cfg.h"
#include "../../../inc/Dem_Rc_ClrInfoMng.h"
#include "../../../inc/Dem_Rc_RecMngCmn.h"
#include "../../../inc/Dem_Rc_RecMngCmn_Table.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "Dem_ClrInfoMng_local.h"

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
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

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


#define DEM_START_SEC_VAR_SAVED_ZONE
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_VAR_SAVED_ZONE
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_ClrInfoMng_Init_AfterNvBlockReadComplete             */
/* Description   | Initialize data function.                                */
/* Preconditions | After Nv Block read complete.                            */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_ClrInfoMng_Init_AfterNvBlockReadComplete_UserDefMem
(
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) ClrInfoNvmReadResult
)
{
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInternalInfoTableIndex;
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInternalInfoTableIndexMax;

    udmInternalInfoTableIndexMax   =   Dem_UserDefinedMemoryInternalInfoNum;

    if ( ClrInfoNvmReadResult == DEM_IRT_OK )
    {
        for ( udmInternalInfoTableIndex = (Dem_u08_UdmMemoryInfoTableIndexType)0U; udmInternalInfoTableIndex < udmInternalInfoTableIndexMax; udmInternalInfoTableIndex++ )  /* [GUD:for]udmInternalInfoTableIndex */
        {
            Dem_ClrInfoRecordVarNoInit.UdmClearID[ udmInternalInfoTableIndex ]    = Dem_ClrInfoRecord.UdmClearID[ udmInternalInfoTableIndex ];                              /* [GUD]udmInternalInfoTableIndex */
        }
    }
    else
    {
        for ( udmInternalInfoTableIndex = (Dem_u08_UdmMemoryInfoTableIndexType)0U; udmInternalInfoTableIndex < udmInternalInfoTableIndexMax; udmInternalInfoTableIndex++ )  /* [GUD:for]udmInternalInfoTableIndex */
        {
            Dem_ClrInfoRecordVarNoInit.UdmClearID[ udmInternalInfoTableIndex ]    = DEM_CLRINFO_RECORD_INITIAL;                                                             /* [GUD]udmInternalInfoTableIndex */
        }
    }
    return;
}

/****************************************************************************/
/* Function Name | Dem_ClrInfoMng_ClearRecord_UserDefMem                    */
/* Description   | Initialize data function.                                */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_ClrInfoMng_ClearRecord_UserDefMem
( void )
{
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInternalInfoTableIndex;
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInternalInfoTableIndexMax;

    udmInternalInfoTableIndexMax   =   Dem_UserDefinedMemoryInternalInfoNum;

    /*  initialize SavedZone area.          */
    for ( udmInternalInfoTableIndex = (Dem_u08_UdmMemoryInfoTableIndexType)0U; udmInternalInfoTableIndex < udmInternalInfoTableIndexMax; udmInternalInfoTableIndex++ )  /* [GUD:for]udmInternalInfoTableIndex */
    {
        Dem_ClrInfoRecord.UdmClearID[ udmInternalInfoTableIndex ]    = DEM_CLRINFO_RECORD_INITIAL;                                                      /* [GUD]udmInternalInfoTableIndex */
        Dem_ClrInfoRecordVarNoInit.UdmClearID[ udmInternalInfoTableIndex ] = DEM_CLRINFO_RECORD_INITIAL;                                                /* [GUD]udmInternalInfoTableIndex */
    }
    return;
}


#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_ClrInfoMng_InitMirrorMemory_UserDefMem               */
/* Description   | Initialize the Mirror Memory.                            */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_ClrInfoMng_InitMirrorMemory_UserDefMem
( void )
{
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInternalInfoTableIndex;
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInternalInfoTableIndexMax;

    udmInternalInfoTableIndexMax   =   Dem_UserDefinedMemoryInternalInfoNum;
    for ( udmInternalInfoTableIndex = (Dem_u08_UdmMemoryInfoTableIndexType)0U; udmInternalInfoTableIndex < udmInternalInfoTableIndexMax; udmInternalInfoTableIndex++ )  /* [GUD:for]udmInternalInfoTableIndex */
    {
        Dem_ClrInfoMirror.UdmClearID[ udmInternalInfoTableIndex ]    = DEM_CLRINFO_RECORD_INITIAL;                                      /* [GUD]udmInternalInfoTableIndex */
    }
    return ;
}

/****************************************************************************/
/* Function Name | Dem_ClrInfoMng_StartClearDTC_UserDefMem                  */
/* Description   | Initializes the value of ClrInfo.                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCGroup :                                          */
/*               |        DTCValue specified at the time of Clear.          */
/*               | [in] DTCOrigin :                                         */
/*               |        DEM_DTC_ORIGIN_PRIMARY_MEMORY                     */
/*               |        DEM_DTC_ORIGIN_OBD_RELEVANT_MEMORY                */
/* Return Value  | boolean                                                  */
/*               |              TRUE  : update.                             */
/*               |              FALSE : not update.                         */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_ClrInfoMng_StartClearDTC_UserDefMem
(
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
)
{
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInternalInfoTableIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) update;

    update = (boolean)FALSE;

    /*  get udmInternalInfoTableIndex from DTCOrigin. */
    retVal = Dem_CfgInfoUdm_CnvDTCOriginToInternalInfoTableIndex( DTCOrigin, &udmInternalInfoTableIndex );      /* [GUD:RET:DEM_IRT_OK] udmInternalInfoTableIndex */

    if ( retVal == DEM_IRT_OK )
    {

        if( Dem_ClrInfoMirror.UdmClearID[ udmInternalInfoTableIndex ] == (Dem_u08_ClearIdType)0U )              /* [GUD]udmInternalInfoTableIndex */
        {
            Dem_ClrInfoMirror.UdmClearID[ udmInternalInfoTableIndex ] = DEM_CLRINFO_RECORD_MAX_VALUE;           /* [GUD]udmInternalInfoTableIndex */
        }
        else
        {
            Dem_ClrInfoMirror.UdmClearID[ udmInternalInfoTableIndex ] = Dem_ClrInfoMirror.UdmClearID[ udmInternalInfoTableIndex ] - (Dem_u08_ClearIdType)1U;        /* [GUD]udmInternalInfoTableIndex */
        }

        update  =   (boolean)TRUE;
    }

    return update;
}


/****************************************************************************/
/* Function Name | Dem_ClrInfoMng_UpdateClearID                             */
/* Description   | Update ClearID Value                                     */
/* Preconditions | None                                                     */
/* Parameters    | [in] DTCGroup :                                          */
/*               |        DTCValue specified at the time of Clear.          */
/*               | [in] DTCOrigin :                                         */
/*               |        DEM_DTC_ORIGIN_PRIMARY_MEMORY                     */
/*               |        DEM_DTC_ORIGIN_OBD_RELEVANT_MEMORY                */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_ClrInfoMng_UpdateClearID_UserDefMem
(
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
)
{
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInternalInfoTableIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    /*  get udmInternalInfoTableIndex from DTCOrigin. */
    retVal = Dem_CfgInfoUdm_CnvDTCOriginToInternalInfoTableIndex( DTCOrigin, &udmInternalInfoTableIndex);       /* [GUD:RET:DEM_IRT_OK] udmInternalInfoTableIndex */

    if ( retVal == DEM_IRT_OK )
    {
        Dem_ClrInfoRecordVarNoInit.UdmClearID[ udmInternalInfoTableIndex ]   = Dem_ClrInfoMirror.UdmClearID[ udmInternalInfoTableIndex ];       /* [GUD]udmInternalInfoTableIndex */
        Dem_ClrInfoRecord.UdmClearID[ udmInternalInfoTableIndex ]            = Dem_ClrInfoMirror.UdmClearID[ udmInternalInfoTableIndex ];       /* [GUD]udmInternalInfoTableIndex */
    }

    return ;
}

/****************************************************************************/
/* Function Name | Dem_ClrInfoMng_WriteClearIDtoMirror_UserDefMem           */
/* Description   |                                                          */
/* Preconditions | None                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_ClrInfoMng_WriteClearIDtoMirror_UserDefMem
( void )
{
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInternalInfoTableIndex;
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInternalInfoTableIndexMax;

    udmInternalInfoTableIndexMax   =   Dem_UserDefinedMemoryInternalInfoNum;

    for ( udmInternalInfoTableIndex = (Dem_u08_UdmMemoryInfoTableIndexType)0U; udmInternalInfoTableIndex < udmInternalInfoTableIndexMax; udmInternalInfoTableIndex++ )  /* [GUD:for]udmInternalInfoTableIndex */
    {
        /*  set UdmClearID  */
        Dem_ClrInfoMirror.UdmClearID[ udmInternalInfoTableIndex ] = Dem_ClrInfoRecordVarNoInit.UdmClearID[ udmInternalInfoTableIndex ];     /* [GUD]udmInternalInfoTableIndex */

    }
    return ;
}

#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_ClrInfoMng_UpdateClearID                             */
/* Description   | Update ClearID Value                                     */
/* Preconditions | None                                                     */
/* Parameters    | [in] DTCOrigin :                                         */
/*               |        DEM_DTC_ORIGIN_OBD_RELEVANT_MEMORY                */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_ClrInfoMng_UpdateClearID_UserDefMem
(
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
)
{
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInternalInfoTableIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    /*  get udmInternalInfoTableIndex from DTCOrigin. */
    retVal = Dem_CfgInfoUdm_CnvDTCOriginToInternalInfoTableIndex( DTCOrigin, &udmInternalInfoTableIndex );      /* [GUD:RET:DEM_IRT_OK] udmInternalInfoTableIndex */

    if  ( retVal == DEM_IRT_OK )
    {
        if( Dem_ClrInfoRecordVarNoInit.UdmClearID[ udmInternalInfoTableIndex ] == (Dem_u08_ClearIdType)0U )             /* [GUD]udmInternalInfoTableIndex */
        {
            Dem_ClrInfoRecordVarNoInit.UdmClearID[ udmInternalInfoTableIndex ] = DEM_CLRINFO_RECORD_MAX_VALUE;          /* [GUD]udmInternalInfoTableIndex */
        }
        else
        {
            Dem_ClrInfoRecordVarNoInit.UdmClearID[ udmInternalInfoTableIndex ] = Dem_ClrInfoRecordVarNoInit.UdmClearID[ udmInternalInfoTableIndex ] - (Dem_u08_ClearIdType)1U;      /* [GUD]udmInternalInfoTableIndex */
        }

        /*  update Dem_ClrInfoRecord(SAVED_ZONE) area.      */
        Dem_ClrInfoRecord.UdmClearID[ udmInternalInfoTableIndex ]    =   Dem_ClrInfoRecordVarNoInit.UdmClearID[ udmInternalInfoTableIndex ];        /* [GUD]udmInternalInfoTableIndex */
    }

    return ;
}
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_OFF- */


/****************************************************************************/
/* Function Name | Dem_ClrInfoMng_GetUdmClearID                             */
/* Description   | Get ClearID Value                                        */
/* Preconditions | None                                                     */
/* Parameters    | [in] udmInternalInfoTableIndex :                         */
/*               |        The index for Dem_UserDefinedMemoryInfoTable[].   */
/* Return Value  | Dem_u08_ClearIdType  ClearID                             */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_ClearIdType, DEM_CODE ) Dem_ClrInfoMng_GetUdmClearID
(
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) UdmInternalInfoTableIndex         /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) clearId;

    clearId =   Dem_ClrInfoRecordVarNoInit.UdmClearID[ UdmInternalInfoTableIndex ];     /* [GUDCHK:CALLER]UdmInternalInfoTableIndex */

    return clearId;
}


/****************************************************************************/
/* Function Name | Dem_ClrInfoMng_RefreshRAM_UserDefMem                     */
/* Description   | Refresh RAM  - ClrInfoMng                                */
/* Preconditions | None                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | Called from Dem_MainFunction                             */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_ClrInfoMng_RefreshRAM_UserDefMem
( void )
{
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInternalInfoTableIndex;
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInternalInfoTableIndexMax;
    VAR( volatile Dem_u08_ClearIdType, AUTOMATIC )                      u8_dummy;      /*  for store GlobalVariable data    */
    P2VAR( volatile Dem_u08_ClearIdType, AUTOMATIC, DEM_VAR_NO_INIT )   u8_dummyPtr;   /*  for GlobalVariable address       */

    udmInternalInfoTableIndexMax   =   Dem_UserDefinedMemoryInternalInfoNum;
    for ( udmInternalInfoTableIndex = (Dem_u08_UdmMemoryInfoTableIndexType)0U; udmInternalInfoTableIndex < udmInternalInfoTableIndexMax; udmInternalInfoTableIndex++ )  /* [GUD:for]udmInternalInfoTableIndex */
    {
        /*  set GlobalVariable pointer  */
        u8_dummyPtr      = &Dem_ClrInfoRecordVarNoInit.UdmClearID[ udmInternalInfoTableIndex ];     /* [GUD]udmInternalInfoTableIndex *//* [GUD]u8_dummyPtr */

        /* Exclusion is not necessary   */
        u8_dummy         = *u8_dummyPtr;          /*  read GlobalVariable data    */                /* [GUD]u8_dummyPtr */
        *u8_dummyPtr     = u8_dummy;              /*  rewrite GlobalVariable data */
    }
    return ;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )  */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
