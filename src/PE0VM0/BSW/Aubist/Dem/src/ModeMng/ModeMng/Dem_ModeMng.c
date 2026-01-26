/* Dem_ModeMng_c(v5-3-0)                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/ModeMng/CODE                                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_Md_ModeMng.h"
#include "../../../usr/Dem_BswM_Connector.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#if ( DEM_TRIGGER_FIM_REPORTS == STD_OFF )
#define DEM_MODE_INIT_VALUE               ((Dem_ModeType)0x0000U)
#endif
#if ( DEM_TRIGGER_FIM_REPORTS == STD_ON )
#define DEM_MODE_INIT_VALUE               (DEM_MODE_UPDATE_ALL_MONITORSTATUS)
#endif

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

static FUNC( void, DEM_CODE ) Dem_ModeMng_NotifyMode
(
    VAR( Dem_ModeType, AUTOMATIC ) Mode
);


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>
/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

static VAR( volatile Dem_ModeType, DEM_VAR_NO_INIT )      Dem_Mode;

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE_TRUST          /*  PreInit section                     */
#include <Dem_MemMap.h>


/****************************************************************************/
/* Function Name | Dem_ModeMng_PreInit                                      */
/* Description   | Pre-initializes Dem_ModeMng.                             */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE_TRUST ) Dem_ModeMng_PreInit    /*  PreInit section           */
( void )
{
    Dem_Mode = DEM_MODE_INIT_VALUE;

    return;
}

#define DEM_STOP_SEC_CODE_TRUST           /*  PreInit section                     */
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_ModeMng_Init                                         */
/* Description   | Full-initializes Dem_ModeMng.                            */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_ModeMng_Init
( void )
{
    VAR( Dem_ModeType, AUTOMATIC ) tmpDemMode;

    SchM_Enter_Dem_ModeAccess();
    tmpDemMode  =   (Dem_ModeType)( Dem_Mode & (Dem_ModeType)~(DEM_MODE_INITIALIZE_MODE_MASK) );
    tmpDemMode  =   (Dem_ModeType)( tmpDemMode | DEM_MODE_INITIALIZING );       /*  DEM_MODE_INITIALIZING   */
    Dem_Mode    =   tmpDemMode;
    SchM_Exit_Dem_ModeAccess();

    /*  notify mode     */
    Dem_ModeMng_NotifyMode( tmpDemMode );

    return;
}


/****************************************************************************/
/* Function Name | Dem_ModeMng_InitComplete                                 */
/* Description   | Full-initialize complete Dem_ModeMng.                    */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_ModeMng_InitComplete
( void )
{
    VAR( Dem_ModeType, AUTOMATIC ) tmpDemMode;

    SchM_Enter_Dem_ModeAccess();

    tmpDemMode  =   (Dem_ModeType)( Dem_Mode & (Dem_ModeType)~(DEM_MODE_INITIALIZE_MODE_MASK) );
    tmpDemMode  =   (Dem_ModeType)( tmpDemMode | DEM_MODE_INITIALIZED );        /*  DEM_MODE_INITIALIZED    */
    Dem_Mode    =   tmpDemMode;

    SchM_Exit_Dem_ModeAccess();

    /*  notify mode     */
    Dem_ModeMng_NotifyMode( tmpDemMode );

    return;
}

/****************************************************************************/
/* Function Name | Dem_ModeMng_Shutdown                                     */
/* Description   | Shuts down Dem_ModeMng.                                  */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_ModeMng_Shutdown
( void )
{
    VAR( Dem_ModeType, AUTOMATIC ) tmpDemMode;

    SchM_Enter_Dem_ModeAccess();

    tmpDemMode  = (Dem_ModeType)( Dem_Mode & (Dem_ModeType)~(DEM_MODE_INITIALIZE_MODE_MASK) );
    Dem_Mode    = tmpDemMode;

    SchM_Exit_Dem_ModeAccess();

    /*  notify mode     */
    Dem_ModeMng_NotifyMode( tmpDemMode );

    return;
}


/****************************************************************************/
/* Function Name | Dem_ModeMng_SetMode                                      */
/* Description   | Sets mode of Dem.                                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] Mode :                                              */
/*               |        The Dem-mode to set.                              */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_ModeMng_SetMode
(
    VAR( Dem_ModeType, AUTOMATIC ) Mode
)
{
    VAR( Dem_ModeType, AUTOMATIC ) tmpDemMode;
    VAR( Dem_ModeType, AUTOMATIC ) tmpBeforeDemMode;

    SchM_Enter_Dem_ModeAccess();
    tmpBeforeDemMode    = Dem_Mode;
    tmpDemMode          = (Dem_ModeType)( tmpBeforeDemMode | Mode );
    Dem_Mode            = tmpDemMode;

    SchM_Exit_Dem_ModeAccess();

    /*  Notify mode timing is DEM_MODE_INITIALIZING == ON or DEM_MODE_INITIALIZED == ON.  */
    if( tmpBeforeDemMode != tmpDemMode )
    {
        if (( tmpDemMode & DEM_MODE_INITIALIZE_MODE_MASK ) != (Dem_ModeType)0U )
        {
            Dem_ModeMng_NotifyMode( tmpDemMode );
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_ModeMng_ClearMode                                    */
/* Description   | Clears mode of Dem.                                      */
/* Preconditions | none                                                     */
/* Parameters    | [in] Mode :                                              */
/*               |        The Dem-mode to clear.                            */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_ModeMng_ClearMode
(
    VAR( Dem_ModeType, AUTOMATIC ) Mode
)
{
    VAR( Dem_ModeType, AUTOMATIC ) tmpDemMode;
    VAR( Dem_ModeType, AUTOMATIC ) tmpBeforeDemMode;

    SchM_Enter_Dem_ModeAccess();

    tmpBeforeDemMode        = Dem_Mode;
    tmpDemMode              = (Dem_ModeType)( tmpBeforeDemMode & (Dem_ModeType)~Mode );
    Dem_Mode                = tmpDemMode;

    SchM_Exit_Dem_ModeAccess();

    /*  Notify mode timing is DEM_MODE _INITIALIZING == ON or DEM_MODE_INITIALIZED == ON.  */
    if( tmpBeforeDemMode != tmpDemMode )
    {
        if (( tmpDemMode & DEM_MODE_INITIALIZE_MODE_MASK ) != (Dem_ModeType)0U )
        {
            Dem_ModeMng_NotifyMode( tmpDemMode );
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_ModeMng_GetMode                                      */
/* Description   | Gets mode of Dem.                                        */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_ModeType                                             */
/*               |        0x0000-0xFFFF : Current Dem-mode.                 */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_ModeType, DEM_CODE ) Dem_ModeMng_GetMode
( void )
{
    VAR( Dem_ModeType, AUTOMATIC ) tmpDemMode;

    SchM_Enter_Dem_ModeAccess();
    tmpDemMode = Dem_Mode;
    SchM_Exit_Dem_ModeAccess();

    /*  check Busy      */
    if( ( tmpDemMode & DEM_MODE_BUSY_DETAIL ) != (Dem_ModeType)0U )
    {
        tmpDemMode = (Dem_ModeType)( tmpDemMode | (Dem_ModeType)DEM_MODE_BUSY );
    }

    return tmpDemMode;
}

/****************************************************************************/
/* Function Name | Dem_ModeMng_NotifyMode                                   */
/* Description   | Notify mode of Dem.                                      */
/* Preconditions | none                                                     */
/* Parameters    | [in] Mode :                                              */
/*               |        The Dem-mode to set.                              */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_ModeMng_NotifyMode
(
    VAR( Dem_ModeType, AUTOMATIC ) Mode
)
{
    VAR( Dem_ModeType, AUTOMATIC ) tmpDemMode;
    VAR( Dem_ModeType, AUTOMATIC ) notifyDemModeMask;

    notifyDemModeMask   =   Dem_NotifyDemModeMask;

    /*  check Busy      */
    tmpDemMode  =   Mode;
    if( ( Mode & DEM_MODE_BUSY_DETAIL ) != (Dem_ModeType)0U )
    {
        tmpDemMode = (Dem_ModeType)( Mode | (Dem_ModeType)DEM_MODE_BUSY );
    }

    /*  check Mask      */
    if (( tmpDemMode & notifyDemModeMask ) != (Dem_ModeType)0U )
    {
        /*  notify mode     */
        Dem_BswM_RequestMode( tmpDemMode );
    }
    return ;
}

/****************************************************************************/
/* Function Name | Dem_ModeMng_RefreshRAM                                   */
/* Description   | Refresh RAM  - ModeMng                                   */
/* Preconditions | None                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | Called from Dem_MainFunction                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_ModeMng_RefreshRAM
( void )
{
    VAR( volatile Dem_ModeType, AUTOMATIC )                      u16_dummy;      /*  for store GlobalVariable data    */
    P2VAR( volatile Dem_ModeType, AUTOMATIC, DEM_VAR_NO_INIT )   u16_dummyPtr;   /*  for GlobalVariable address       */

    /* Exclusion is necessary   */
    SchM_Enter_Dem_ModeAccess();
        u16_dummyPtr   = &Dem_Mode;         /*  set GlobalVariable pointer  */
        u16_dummy      = *u16_dummyPtr;     /*  read GlobalVariable data    */
        *u16_dummyPtr  = u16_dummy;         /*  rewrite GlobalVariable data */
    SchM_Exit_Dem_ModeAccess();

    return ;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v2-0-0         :2019-03-27                                              */
/*  v3-0-0         :2019-07-29                                              */
/*  v4-0-0         :2020-03-19                                              */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
