/* Dem_PIDMng_c(v5-7-0)                                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/PIDMng/CODE                                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../cfg/Dem_NvM_Cfg.h"
#include "../../../inc/Dem_Rc_PIDMng.h"
#include "../../../inc/Dem_Rc_ClrInfoMng.h"
#include "../../../inc/Dem_Rc_RecMngCmn.h"
#include "../../../inc/Dem_Rc_RecMngCmn_Table.h"
#include "Dem_PIDMng_local.h"

#if ( DEM_PID_SUPPORT == STD_ON )

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

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
static FUNC( void, DEM_CODE ) Dem_PIDMng_InitMirrorMemory
( void );
#endif  /*  ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )   */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
VAR( Dem_u08_RecMngMtxStsType, DEM_VAR_NO_INIT ) Dem_PidMng_NvMWriteStatus;
VAR( Dem_PIDRecordType, DEM_VAR_NO_INIT ) Dem_PIDRecordTmp;
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


#define DEM_START_SEC_VAR_SAVED_ZONE
#include <Dem_MemMap.h>

VAR( Dem_PIDRecordType, DEM_VAR_SAVED_ZONE ) Dem_PIDRecord;

#define DEM_STOP_SEC_VAR_SAVED_ZONE
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_PIDMng_Init                                          */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PIDMng_Init
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex     /* MISRA DEVIATION */
)
{
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    /* [FuncSw] */
    Dem_PIDMng_InitMirrorMemory();
#endif  /*  ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )   */
    return;
}

/****************************************************************************/
/* Function Name | Dem_PIDMng_InitSavedZone                                 */
/* Description   | Initialize savedzone process of PID.                     */
/* Preconditions |                                                          */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/*               | [in] InitType :                                          */
/*               |          Initialize savedzone type                       */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PIDMng_InitSavedZone
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    VAR( Dem_SavedZoneInitializeType, AUTOMATIC ) InitType      /* MISRA DEVIATION */
)
{
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindPID;

    Dem_PIDRecord.ClearID = DEM_CLRINFO_RECORD_INITIAL;

    Dem_PIDRecord.PID21[DEM_PID_POS0] = DEM_PIDMNG_PIDDATA_PREINITVALUE;
    Dem_PIDRecord.PID21[DEM_PID_POS1] = DEM_PIDMNG_PIDDATA_PREINITVALUE;
    Dem_PIDRecord.StoreNvmPID21 = DEM_PIDMNG_PIDDATA_PREINITVALUE;

    Dem_PIDRecord.PID30 = DEM_PIDMNG_PIDDATA_PREINITVALUE;
    Dem_PIDRecord.StoreNvmPID30 = DEM_PIDMNG_PIDDATA_PREINITVALUE;

    Dem_PIDRecord.PID31[DEM_PID_POS0] = DEM_PIDMNG_PIDDATA_PREINITVALUE;
    Dem_PIDRecord.PID31[DEM_PID_POS1] = DEM_PIDMNG_PIDDATA_PREINITVALUE;
    Dem_PIDRecord.StoreNvmPID31 = DEM_PIDMNG_PIDDATA_PREINITVALUE;

    Dem_PIDRecord.PID4D[DEM_PID_POS0] = DEM_PIDMNG_PIDDATA_PREINITVALUE;
    Dem_PIDRecord.PID4D[DEM_PID_POS1] = DEM_PIDMNG_PIDDATA_PREINITVALUE;
    Dem_PIDRecord.StoreNvmPID4D = DEM_PIDMNG_PIDDATA_PREINITVALUE;

    Dem_PIDRecord.PID4E[DEM_PID_POS0] = DEM_PIDMNG_PIDDATA_PREINITVALUE;
    Dem_PIDRecord.PID4E[DEM_PID_POS1] = DEM_PIDMNG_PIDDATA_PREINITVALUE;
    Dem_PIDRecord.StoreNvmPID4E = DEM_PIDMNG_PIDDATA_PREINITVALUE;

    recMngCmnKindPID = Dem_RecMngCmnKindPID;
    Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindPID, ( Dem_u16_RecordIndexType )0U );

    return;
}

/****************************************************************************/
/* Function Name | Dem_PIDMngC_ClearDataOfPID30                             */
/* Description   | clear the value of PID30                                 */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PIDMngC_ClearDataOfPID30
( void )
{
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindPID;

    /* Starts exclusion. */
    SchM_Enter_Dem_PID();

    Dem_PIDRecord.PID30 = DEM_PIDMNG_PIDDATA_INITVALUE;

    Dem_PIDRecord.StoreNvmPID30 = DEM_PID_STORE_NVM;

    Dem_PIDRecord.ClearID = Dem_ClrInfoMng_GetObdClearID();

    recMngCmnKindPID = Dem_RecMngCmnKindPID;
    Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindPID, ( Dem_u16_RecordIndexType )0U );

    /* Finishes exclusion. */
    SchM_Exit_Dem_PID();

    return;
}

/****************************************************************************/
/* Function Name | Dem_PIDMngC_ReadDataOfPID21                              */
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
FUNC( void , DEM_CODE ) Dem_PIDMngC_ReadDataOfPID21
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID21value
)
{
    /* Starts exclusion. */
    SchM_Enter_Dem_PID();

    PID21value[DEM_PID_POS0] = Dem_PIDRecord.PID21[DEM_PID_POS0];/* [ARYCHK] DEM_PID21_SIZE / 1 / DEM_PID_POS0 */
    PID21value[DEM_PID_POS1] = Dem_PIDRecord.PID21[DEM_PID_POS1];/* [ARYCHK] DEM_PID21_SIZE / 1 / DEM_PID_POS1 */

    /* Finishes exclusion. */
    SchM_Exit_Dem_PID();

    return;
}

#if ( DEM_PID_WARMUPCYC_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_PIDMngC_ReadDataOfPID30                              */
/* Description   | Service to report the value of PID30                     */
/* Preconditions | none                                                     */
/* Parameters    | void                                                     */
/* Return Value  | Dem_u08_PIDByteValueType                                 */
/*               |        0x00 - 0xFF : the value of PID30                  */
/* Notes         | This function is in [SchM_Enter_Dem_PID] exclusive area. */
/*               | [SchM_Enter_Dem_PID] exclusion is called in              */
/*               | [Dem_Control_ReadDataOfPID30] function.                  */
/****************************************************************************/
FUNC( Dem_u08_PIDByteValueType, DEM_CODE ) Dem_PIDMngC_ReadDataOfPID30
( void )
{
    /*--------------------------------------------------------------*/
    /*  This function is in [SchM_Enter_Dem_PID] exclusive area.    */
    /*--------------------------------------------------------------*/
    return Dem_PIDRecord.PID30;
}
#endif  /* ( DEM_PID_WARMUPCYC_SUPPORT == STD_ON )      */

/****************************************************************************/
/* Function Name | Dem_PIDMngC_ReadDataOfPID31                              */
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
FUNC( void, DEM_CODE ) Dem_PIDMngC_ReadDataOfPID31
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID31value
)
{
    /* Starts exclusion. */
    SchM_Enter_Dem_PID();

    PID31value[DEM_PID_POS0] = Dem_PIDRecord.PID31[DEM_PID_POS0];/* [ARYCHK] DEM_PID31_SIZE / 1 / DEM_PID_POS0 */
    PID31value[DEM_PID_POS1] = Dem_PIDRecord.PID31[DEM_PID_POS1];/* [ARYCHK] DEM_PID31_SIZE / 1 / DEM_PID_POS1 */

    /* Finishes exclusion. */
    SchM_Exit_Dem_PID();

    return;
}


/****************************************************************************/
/* Function Name | Dem_PIDMngC_ReadDataOfPID4D                              */
/* Description   | Service to report the value of PID4D                     */
/* Preconditions | none                                                     */
/* Parameters    | [out] PID4Dvalue                                         */
/*               |        Buffer containing the contents of PID4D computed  */
/*               |        by the Dem. The buffer is provided by the Dcm or  */
/*               |        SWC with the appropriate size.                    */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PIDMngC_ReadDataOfPID4D
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID4Dvalue
)
{
    /* Starts exclusion. */
    SchM_Enter_Dem_PID();

    PID4Dvalue[DEM_PID_POS0] = Dem_PIDRecord.PID4D[DEM_PID_POS0];/* [ARYCHK] DEM_PID4D_SIZE / 1 / DEM_PID_POS0 */
    PID4Dvalue[DEM_PID_POS1] = Dem_PIDRecord.PID4D[DEM_PID_POS1];/* [ARYCHK] DEM_PID4D_SIZE / 1 / DEM_PID_POS1 */

    /* Finishes exclusion. */
    SchM_Exit_Dem_PID();

    return;
}


/****************************************************************************/
/* Function Name | Dem_PIDMngC_ReadDataOfPID4E                              */
/* Description   | Service to report the value of PID4E                     */
/* Preconditions | none                                                     */
/* Parameters    | void                                                     */
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
FUNC( void, DEM_CODE ) Dem_PIDMngC_ReadDataOfPID4E
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID4Evalue
)
{
    /* Starts exclusion. */
    SchM_Enter_Dem_PID();

    PID4Evalue[DEM_PID_POS0] = Dem_PIDRecord.PID4E[DEM_PID_POS0];/* [ARYCHK] DEM_PID4E_SIZE / 1 / DEM_PID_POS0 */
    PID4Evalue[DEM_PID_POS1] = Dem_PIDRecord.PID4E[DEM_PID_POS1];/* [ARYCHK] DEM_PID4E_SIZE / 1 / DEM_PID_POS1 */

    /* Finishes exclusion. */
    SchM_Exit_Dem_PID();

    return;
}


/****************************************************************************/
/* Function Name | Dem_PIDMngC_SetDataOfPID21                               */
/* Description   | Service to set the value of PID21                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] PID21value :                                        */
/*               |        Buffer containing the contents of PID21. The      */
/*               |        buffer is provided by the SWC with the            */
/*               |        appropriate size.                                 */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PIDMngC_SetDataOfPID21
(
    CONSTP2CONST( uint8, AUTOMATIC, DEM_APPL_DATA ) PID21value
)
{
    VAR( boolean, AUTOMATIC ) nvmWrite;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindPID;

    nvmWrite = (boolean)FALSE;

    /* Starts exclusion. */
    SchM_Enter_Dem_PID();

    if (Dem_PIDRecord.StoreNvmPID21 == DEM_PID_NOT_STORE_NVM)
    {
        nvmWrite = (boolean)TRUE;
    }
    else
    {
        if( (Dem_PIDRecord.PID21[DEM_PID_POS0] != PID21value[DEM_PID_POS0]) ||/* [ARYCHK] DEM_PID21_SIZE / 1 / DEM_PID_POS0 */
            (Dem_PIDRecord.PID21[DEM_PID_POS1] != PID21value[DEM_PID_POS1]) )/* [ARYCHK] DEM_PID21_SIZE / 1 / DEM_PID_POS1 */
        {
            nvmWrite = (boolean)TRUE;
        }
    }

    if (nvmWrite == (boolean)TRUE)
    {
        Dem_PIDRecord.PID21[DEM_PID_POS0] = PID21value[DEM_PID_POS0];/* [ARYCHK] DEM_PID21_SIZE / 1 / DEM_PID_POS0 */
        Dem_PIDRecord.PID21[DEM_PID_POS1] = PID21value[DEM_PID_POS1];/* [ARYCHK] DEM_PID21_SIZE / 1 / DEM_PID_POS1 */

        Dem_PIDRecord.ClearID = Dem_ClrInfoMng_GetObdClearID();

        Dem_PIDRecord.StoreNvmPID21 = DEM_PID_STORE_NVM;

        recMngCmnKindPID = Dem_RecMngCmnKindPID;
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindPID, ( Dem_u16_RecordIndexType )0U );
    }

    /* Finishes exclusion. */
    SchM_Exit_Dem_PID();

    return;
}


/****************************************************************************/
/* Function Name | Dem_PIDMngC_SetDataOfPID31                               */
/* Description   | Service to set the value of PID31                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] PID31value :                                        */
/*               |        Buffer containing the contents of PID31. The      */
/*               |        buffer is provided by the SWC with the            */
/*               |        appropriate size.                                 */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PIDMngC_SetDataOfPID31
(
    CONSTP2CONST( uint8, AUTOMATIC, DEM_APPL_DATA ) PID31value
)
{
    VAR( boolean, AUTOMATIC ) nvmWrite;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindPID;

    nvmWrite = (boolean)FALSE;

    /* Starts exclusion. */
    SchM_Enter_Dem_PID();

    if (Dem_PIDRecord.StoreNvmPID31 == DEM_PID_NOT_STORE_NVM)
    {
        nvmWrite = (boolean)TRUE;
    }
    else
    {
        if( (Dem_PIDRecord.PID31[DEM_PID_POS0] != PID31value[DEM_PID_POS0]) ||/* [ARYCHK] DEM_PID31_SIZE / 1 / DEM_PID_POS0 */
            (Dem_PIDRecord.PID31[DEM_PID_POS1] != PID31value[DEM_PID_POS1]) )/* [ARYCHK] DEM_PID31_SIZE / 1 / DEM_PID_POS1 */
        {
            nvmWrite = (boolean)TRUE;
        }
    }

    if (nvmWrite == (boolean)TRUE)
    {
        Dem_PIDRecord.PID31[DEM_PID_POS0] = PID31value[DEM_PID_POS0];/* [ARYCHK] DEM_PID31_SIZE / 1 / DEM_PID_POS0 */
        Dem_PIDRecord.PID31[DEM_PID_POS1] = PID31value[DEM_PID_POS1];/* [ARYCHK] DEM_PID31_SIZE / 1 / DEM_PID_POS1 */

        Dem_PIDRecord.ClearID = Dem_ClrInfoMng_GetObdClearID();

        Dem_PIDRecord.StoreNvmPID31 = DEM_PID_STORE_NVM;

        recMngCmnKindPID = Dem_RecMngCmnKindPID;
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindPID, ( Dem_u16_RecordIndexType )0U );
    }

    /* Finishes exclusion. */
    SchM_Exit_Dem_PID();

    return;
}


/****************************************************************************/
/* Function Name | Dem_PIDMngC_SetDataOfPID4D                               */
/* Description   | Service to set the value of PID4D                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] PID4Dvalue :                                        */
/*               |        Buffer containing the contents of PID4D. The      */
/*               |        buffer is provided by the SWC with the appropria- */
/*               |        te size.                                          */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PIDMngC_SetDataOfPID4D
(
    CONSTP2CONST( uint8, AUTOMATIC, DEM_APPL_DATA ) PID4Dvalue
)
{
    VAR( boolean, AUTOMATIC ) nvmWrite;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindPID;

    nvmWrite = (boolean)FALSE;

    /* Starts exclusion. */
    SchM_Enter_Dem_PID();

    if (Dem_PIDRecord.StoreNvmPID4D == DEM_PID_NOT_STORE_NVM)
    {
        nvmWrite = (boolean)TRUE;
    }
    else
    {
        if( (Dem_PIDRecord.PID4D[DEM_PID_POS0] != PID4Dvalue[DEM_PID_POS0]) ||/* [ARYCHK] DEM_PID4D_SIZE / 1 / DEM_PID_POS0 */
            (Dem_PIDRecord.PID4D[DEM_PID_POS1] != PID4Dvalue[DEM_PID_POS1]) )/* [ARYCHK] DEM_PID4D_SIZE / 1 / DEM_PID_POS1 */
        {
            nvmWrite = (boolean)TRUE;
        }
    }

    if (nvmWrite == (boolean)TRUE)
    {
        Dem_PIDRecord.PID4D[DEM_PID_POS0] = PID4Dvalue[DEM_PID_POS0];/* [ARYCHK] DEM_PID4D_SIZE / 1 / DEM_PID_POS0 */
        Dem_PIDRecord.PID4D[DEM_PID_POS1] = PID4Dvalue[DEM_PID_POS1];/* [ARYCHK] DEM_PID4D_SIZE / 1 / DEM_PID_POS1 */

        Dem_PIDRecord.ClearID = Dem_ClrInfoMng_GetObdClearID();

        Dem_PIDRecord.StoreNvmPID4D = DEM_PID_STORE_NVM;

        recMngCmnKindPID = Dem_RecMngCmnKindPID;
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindPID, ( Dem_u16_RecordIndexType )0U );
    }

    /* Finishes exclusion. */
    SchM_Exit_Dem_PID();

    return;
}


/****************************************************************************/
/* Function Name | Dem_PIDMngC_SetDataOfPID4E                               */
/* Description   | Service to set the value of PID4E                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] PID4Evalue :                                        */
/*               |        Buffer containing the contents of PID4E. The      */
/*               |        buffer is provided by the SWC with the appropria- */
/*               |        te size.                                          */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PIDMngC_SetDataOfPID4E
(
    CONSTP2CONST( uint8, AUTOMATIC, DEM_APPL_DATA ) PID4Evalue
)
{
    VAR( boolean, AUTOMATIC ) nvmWrite;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindPID;

    nvmWrite = (boolean)FALSE;

    /* Starts exclusion. */
    SchM_Enter_Dem_PID();

    if (Dem_PIDRecord.StoreNvmPID4E == DEM_PID_NOT_STORE_NVM)
    {
        nvmWrite = (boolean)TRUE;
    }
    else
    {
        if( (Dem_PIDRecord.PID4E[DEM_PID_POS0] != PID4Evalue[DEM_PID_POS0]) ||/* [ARYCHK] DEM_PID4E_SIZE / 1 / DEM_PID_POS0 */
            (Dem_PIDRecord.PID4E[DEM_PID_POS1] != PID4Evalue[DEM_PID_POS1]) )/* [ARYCHK] DEM_PID4E_SIZE / 1 / DEM_PID_POS1 */
        {
            nvmWrite = (boolean)TRUE;
        }
    }

    if (nvmWrite == (boolean)TRUE)
    {
        Dem_PIDRecord.PID4E[DEM_PID_POS0] = PID4Evalue[DEM_PID_POS0];/* [ARYCHK] DEM_PID4E_SIZE / 1 / DEM_PID_POS0 */
        Dem_PIDRecord.PID4E[DEM_PID_POS1] = PID4Evalue[DEM_PID_POS1];/* [ARYCHK] DEM_PID4E_SIZE / 1 / DEM_PID_POS1 */

        Dem_PIDRecord.ClearID = Dem_ClrInfoMng_GetObdClearID();

        Dem_PIDRecord.StoreNvmPID4E = DEM_PID_STORE_NVM;

        recMngCmnKindPID = Dem_RecMngCmnKindPID;
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindPID, ( Dem_u16_RecordIndexType )0U );
    }

    /* Finishes exclusion. */
    SchM_Exit_Dem_PID();

    return;
}

#if ( DEM_PID_WARMUPCYC_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_PIDMngC_UpdateDataOfPID30                            */
/* Description   | Update the value of PID30                                */
/* Preconditions | none                                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | This function is in [SchM_Enter_Dem_PID] exclusive area. */
/*               | [SchM_Enter_Dem_PID] exclusion is called in              */
/*               | [Dem_Control_EndOperationCycleUpdate] function.          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PIDMngC_UpdateDataOfPID30
( void )
{
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindPID;

    /*--------------------------------------------------------------*/
    /*  This function is in [SchM_Enter_Dem_PID] exclusive area.    */
    /*--------------------------------------------------------------*/
    if( Dem_PIDRecord.PID30 < DEM_PID_WUCCNT_MAX )
    {
        Dem_PIDRecord.PID30++;

        Dem_PIDRecord.ClearID = Dem_ClrInfoMng_GetObdClearID();

        Dem_PIDRecord.StoreNvmPID30 = DEM_PID_STORE_NVM;

        recMngCmnKindPID = Dem_RecMngCmnKindPID;
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindPID, ( Dem_u16_RecordIndexType )0U );
    }
    else
    {
        /* No process */
    }

    return;
}
#endif  /* ( DEM_PID_WARMUPCYC_SUPPORT == STD_ON )      */

/****************************************************************************/
/* Function Name | Dem_PIDMng_DataVerify                                    */
/* Description   | Data confirmation start demand.                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |          DEM_IRT_OK      : DataVerify completed.         */
/*               |          DEM_IRT_PENDING : Continue DataVerify.          */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PIDMng_DataVerify
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex     /* MISRA DEVIATION */
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) clrInfoNvmReadResult;
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) clrInfoRecValue;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindPID;
    VAR( boolean, AUTOMATIC ) setNvMWriteFlg;

    setNvMWriteFlg = (boolean)FALSE;

    clrInfoNvmReadResult = Dem_ClrInfoMng_GetNvmReadResult();
    clrInfoRecValue  = Dem_ClrInfoMng_GetObdClearID();

    /* Check ClrInfo Recored */
    if( clrInfoNvmReadResult == DEM_IRT_OK )
    {
        if( Dem_PIDRecord.ClearID != clrInfoRecValue )
        {
            /*  initialize OpCycle record.      */
            Dem_PIDRecord.PID30 = DEM_PIDMNG_PIDDATA_INITVALUE;
            Dem_PIDRecord.StoreNvmPID30 = DEM_PID_STORE_NVM;
            Dem_PIDRecord.ClearID   =   clrInfoRecValue;

#if ( DEM_PID_CALC_DEMINTERNALPID_SUPPORT == STD_ON )    /*  [FuncSw]    */
            Dem_PIDMng_InitCalcTargetPIDRecord();
#endif  /*   ( DEM_PID_CALC_DEMINTERNALPID_SUPPORT == STD_ON )           */
        }
    }
    else
    {
        Dem_PIDMngC_ClearDataOfPID30();
#if ( DEM_PID_CALC_DEMINTERNALPID_SUPPORT == STD_ON )    /*  [FuncSw]    */
        Dem_PIDMngC_ClearDataOfPIDCalcTarget();
#endif  /*   ( DEM_PID_CALC_DEMINTERNALPID_SUPPORT == STD_ON )           */
    }

    if (Dem_PIDRecord.StoreNvmPID21 == DEM_PID_NOT_STORE_NVM)
    {
        Dem_PIDRecord.PID21[DEM_PID_POS0] = DEM_PIDMNG_PIDDATA_INITVALUE;
        Dem_PIDRecord.PID21[DEM_PID_POS1] = DEM_PIDMNG_PIDDATA_INITVALUE;
        Dem_PIDRecord.StoreNvmPID21 = DEM_PID_STORE_NVM;
        setNvMWriteFlg = (boolean)TRUE;
    }

    if (Dem_PIDRecord.StoreNvmPID30 == DEM_PID_NOT_STORE_NVM)
    {
        Dem_PIDRecord.PID30 = DEM_PIDMNG_PIDDATA_INITVALUE;
        Dem_PIDRecord.StoreNvmPID30 = DEM_PID_STORE_NVM;
        setNvMWriteFlg = (boolean)TRUE;
    }

    if (Dem_PIDRecord.StoreNvmPID31 == DEM_PID_NOT_STORE_NVM)
    {
        Dem_PIDRecord.PID31[DEM_PID_POS0] = DEM_PIDMNG_PIDDATA_INITVALUE;
        Dem_PIDRecord.PID31[DEM_PID_POS1] = DEM_PIDMNG_PIDDATA_INITVALUE;
        Dem_PIDRecord.StoreNvmPID31 = DEM_PID_STORE_NVM;
        setNvMWriteFlg = (boolean)TRUE;
    }

    if (Dem_PIDRecord.StoreNvmPID4D == DEM_PID_NOT_STORE_NVM)
    {
        Dem_PIDRecord.PID4D[DEM_PID_POS0] = DEM_PIDMNG_PIDDATA_INITVALUE;
        Dem_PIDRecord.PID4D[DEM_PID_POS1] = DEM_PIDMNG_PIDDATA_INITVALUE;
        Dem_PIDRecord.StoreNvmPID4D = DEM_PID_STORE_NVM;
        setNvMWriteFlg = (boolean)TRUE;
    }

    if (Dem_PIDRecord.StoreNvmPID4E == DEM_PID_NOT_STORE_NVM)
    {
        Dem_PIDRecord.PID4E[DEM_PID_POS0] = DEM_PIDMNG_PIDDATA_INITVALUE;
        Dem_PIDRecord.PID4E[DEM_PID_POS1] = DEM_PIDMNG_PIDDATA_INITVALUE;
        Dem_PIDRecord.StoreNvmPID4E = DEM_PID_STORE_NVM;
        setNvMWriteFlg = (boolean)TRUE;
    }

    if( setNvMWriteFlg == (boolean)TRUE )
    {
        recMngCmnKindPID = Dem_RecMngCmnKindPID;
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindPID, ( Dem_u16_RecordIndexType )0U );
    }

    return DEM_IRT_OK;
}

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_PidMng_DeployPIDRecordToMirror                       */
/* Description   | Deploy PID records to mirror data.                       */
/* Preconditions | None                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/*               | [in/out] BlockMirrorPtr :                                */
/*               |        Nonvolatile synchronous data information.         */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PidMng_DeployPIDRecordToMirror
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
)
{
    /* Data copy to temporary. */
    Dem_PIDRecordTmp.PID21[DEM_PID_POS0]    = Dem_PIDRecord.PID21[DEM_PID_POS0];
    Dem_PIDRecordTmp.PID21[DEM_PID_POS1]    = Dem_PIDRecord.PID21[DEM_PID_POS1];
    Dem_PIDRecordTmp.StoreNvmPID21          = Dem_PIDRecord.StoreNvmPID21;

    Dem_PIDRecordTmp.PID30                  = Dem_PIDRecord.PID30;
    Dem_PIDRecordTmp.StoreNvmPID30          = Dem_PIDRecord.StoreNvmPID30;

    Dem_PIDRecordTmp.PID31[DEM_PID_POS0]    = Dem_PIDRecord.PID31[DEM_PID_POS0];
    Dem_PIDRecordTmp.PID31[DEM_PID_POS1]    = Dem_PIDRecord.PID31[DEM_PID_POS1];
    Dem_PIDRecordTmp.StoreNvmPID31          = Dem_PIDRecord.StoreNvmPID31;

    Dem_PIDRecordTmp.PID4D[DEM_PID_POS0]    = Dem_PIDRecord.PID4D[DEM_PID_POS0];
    Dem_PIDRecordTmp.PID4D[DEM_PID_POS1]    = Dem_PIDRecord.PID4D[DEM_PID_POS1];
    Dem_PIDRecordTmp.StoreNvmPID4D          = Dem_PIDRecord.StoreNvmPID4D;

    Dem_PIDRecordTmp.PID4E[DEM_PID_POS0]    = Dem_PIDRecord.PID4E[DEM_PID_POS0];
    Dem_PIDRecordTmp.PID4E[DEM_PID_POS1]    = Dem_PIDRecord.PID4E[DEM_PID_POS1];
    Dem_PIDRecordTmp.StoreNvmPID4E          = Dem_PIDRecord.StoreNvmPID4E;

    Dem_PIDRecordTmp.ClearID                = Dem_PIDRecord.ClearID;

    BlockMirrorPtr->MirrorPtr = &Dem_PIDRecordTmp;

    return;
}

/****************************************************************************/
/* Function Name | Dem_PIDMng_InitMirrorMemory                              */
/* Description   | Initializes the value of PIDRecord.                      */
/* Preconditions | none                                                     */
/* Parameters    | none.                                                    */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_PIDMng_InitMirrorMemory
( void )
{
    VAR( Dem_u16_PaddingIndexType, AUTOMATIC ) pidRecordBlockPaddingSize;
    VAR( Dem_u16_PaddingIndexType, AUTOMATIC ) paddingIndex;

    /* Initialize temporary PID Record. */
    Dem_PIDRecordTmp.PID21[DEM_PID_POS0] = DEM_PIDMNG_PIDDATA_PREINITVALUE;
    Dem_PIDRecordTmp.PID21[DEM_PID_POS1] = DEM_PIDMNG_PIDDATA_PREINITVALUE;
    Dem_PIDRecordTmp.StoreNvmPID21 = DEM_PIDMNG_PIDDATA_PREINITVALUE;

    Dem_PIDRecordTmp.PID30 = DEM_PIDMNG_PIDDATA_PREINITVALUE;
    Dem_PIDRecordTmp.StoreNvmPID30 = DEM_PIDMNG_PIDDATA_PREINITVALUE;

    Dem_PIDRecordTmp.PID31[DEM_PID_POS0] = DEM_PIDMNG_PIDDATA_PREINITVALUE;
    Dem_PIDRecordTmp.PID31[DEM_PID_POS1] = DEM_PIDMNG_PIDDATA_PREINITVALUE;
    Dem_PIDRecordTmp.StoreNvmPID31 = DEM_PIDMNG_PIDDATA_PREINITVALUE;

    Dem_PIDRecordTmp.PID4D[DEM_PID_POS0] = DEM_PIDMNG_PIDDATA_PREINITVALUE;
    Dem_PIDRecordTmp.PID4D[DEM_PID_POS1] = DEM_PIDMNG_PIDDATA_PREINITVALUE;
    Dem_PIDRecordTmp.StoreNvmPID4D = DEM_PIDMNG_PIDDATA_PREINITVALUE;

    Dem_PIDRecordTmp.PID4E[DEM_PID_POS0] = DEM_PIDMNG_PIDDATA_PREINITVALUE;
    Dem_PIDRecordTmp.PID4E[DEM_PID_POS1] = DEM_PIDMNG_PIDDATA_PREINITVALUE;
    Dem_PIDRecordTmp.StoreNvmPID4E = DEM_PIDMNG_PIDDATA_PREINITVALUE;

    Dem_PIDRecordTmp.ClearID = DEM_CLRINFO_RECORD_INITIAL;

    pidRecordBlockPaddingSize   =   Dem_PIDRecordBlockPaddingSize;
    for( paddingIndex = (Dem_u16_PaddingIndexType)0U; paddingIndex < pidRecordBlockPaddingSize; paddingIndex++ )    /* [GUD:for]paddingIndex */
    {
        Dem_PIDRecordTmp.Reserve[paddingIndex] = DEM_PIDMNG_PIDDATA_PREINITVALUE;   /* [GUD]paddingIndex */
    }

    return;
}


#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_PIDMng_GetEventIdFromRecordData                      */
/* Description   | get event id from record data                            */
/* Preconditions | none                                                     */
/* Parameters    | [in]  RecordFieldIndex :                                 */
/*               | [in]  RecordIndex :                                      */
/*               | [out] EventIdPtr  :                                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_NG : failed                               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PIDMng_GetEventIdFromRecordData
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) RecordIndex,      /* MISRA DEVIATION */
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr   /* MISRA DEVIATION */
)
{
    /*  this record has no event id.        */
    return DEM_IRT_NG;
}
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_PID_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2019-03-27                                              */
/*  v3-0-0         :2019-07-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
