/* Dem_AsyncReqData_c(v5-10-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/AsyncReqData/CODE                                     */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../../../cfg/Dem_Cfg.h"

#if ( DEM_ASYNCDATAQUE_USE == STD_ON )

#include <Dem/Dem_Common.h>
#include "../../../inc/Dem_CmnLib_AsyncReqTable.h"
#include "Dem_AsyncReq_local.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_ASYNCDATAQUE_INITIAL_DATA_EMPTYPOS          ((Dem_u08_AsyncDataQueIndexType)0x00U)
#define DEM_ASYNCDATAQUE_INITIAL_DATA_STOREDITEMNUM     ((Dem_u08_AsyncDataQueIndexType)0x00U)

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


/****************************************************************************/
/* External Functions(PreInit section)                                      */
/****************************************************************************/
#define DEM_START_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_AsyncReqData_ClearQueData                            */
/* Description   | Initialize the data queue.                               */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE_TRUST ) Dem_AsyncReqData_ClearQueData     /*  PreInit section     */
( void )
{
    VAR( Dem_u08_AsyncDataQueTableIndexType, AUTOMATIC ) asyncDataQueNum;
    VAR( Dem_u08_AsyncDataQueTableIndexType, AUTOMATIC ) asyncDataQueIndex;

    asyncDataQueNum = Dem_AsyncDataQueNum;

    for( asyncDataQueIndex = (Dem_u08_AsyncDataQueTableIndexType)0U; asyncDataQueIndex < asyncDataQueNum; asyncDataQueIndex++ )     /* [GUD:for]asyncDataQueIndex */
    {
        *Dem_ExecAsyncDataQueTable[ asyncDataQueIndex ].EmptyPosVPtr        = DEM_ASYNCDATAQUE_INITIAL_DATA_EMPTYPOS;               /* [GUD]asyncDataQueIndex */
        *Dem_ExecAsyncDataQueTable[ asyncDataQueIndex ].StoredItemNumVPtr   = DEM_ASYNCDATAQUE_INITIAL_DATA_STOREDITEMNUM;          /* [GUD]asyncDataQueIndex */
    }

    return ;
}

#define DEM_STOP_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_AsyncReqData_RefreshRAM                              */
/* Description   | Refresh the data queue.                                  */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_AsyncReqData_RefreshRAM
( void )
{
    VAR( volatile Dem_u08_AsyncDataQueIndexType, AUTOMATIC ) u8_dummy;                          /*  for store GlobalVariable data    */
    P2VAR( volatile Dem_u08_AsyncDataQueIndexType, AUTOMATIC, DEM_VAR_NO_INIT ) u8_dummyPtr;    /*  for GlobalVariable address       */

    VAR( Dem_u08_AsyncDataQueTableIndexType, AUTOMATIC ) asyncDataQueNum;
    VAR( Dem_u08_AsyncDataQueTableIndexType, AUTOMATIC ) asyncDataQueIndex;

    asyncDataQueNum = Dem_AsyncDataQueNum;

    for( asyncDataQueIndex = (Dem_u08_AsyncDataQueTableIndexType)0U; asyncDataQueIndex < asyncDataQueNum; asyncDataQueIndex++ )         /* [GUD:for]asyncDataQueIndex */
    {
        u8_dummyPtr     = Dem_ExecAsyncDataQueTable[ asyncDataQueIndex ].EmptyPosVPtr;      /*  set GlobalVariable pointer  */          /* [GUD]asyncDataQueIndex */
        u8_dummy        = *u8_dummyPtr;                                                 /*  read GlobalVariable data    */              /* [GUD]asyncDataQueIndex */
        *u8_dummyPtr    = u8_dummy;                                                     /*  rewrite GlobalVariable data */

        u8_dummyPtr     = Dem_ExecAsyncDataQueTable[ asyncDataQueIndex ].StoredItemNumVPtr; /*  set GlobalVariable pointer  */          /* [GUD]asyncDataQueIndex */
        u8_dummy        = *u8_dummyPtr;                                                 /*  read GlobalVariable data    */              /* [GUD]asyncDataQueIndex */
        *u8_dummyPtr    = u8_dummy;                                                     /*  rewrite GlobalVariable data */
    }

    return ;
}


/****************************************************************************/
/* Function Name | Dem_AsyncReqData_RegistQue                               */
/* Description   | Regist the data queue and get the data queue index.      */
/* Preconditions | none                                                     */
/* Parameters    | [in/Out] DataQueInfoPtr :                                */
/*               |        The pointer of the data queue.                    */
/*               | [Out] QueIndexPtr :                                      */
/*               |        The pointer of the queue index.                   */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_NG : failed                               */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_AsyncReqData_RegistQue
(
    VAR( Dem_u08_AsyncDataQueTableIndexType, AUTOMATIC ) AsyncDataQueIndex,         /* [PRMCHK:CALLER] */
    P2VAR( Dem_u08_AsyncDataQueIndexType, AUTOMATIC, AUTOMATIC ) QueIndexPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_AsyncDataQueIndexType, AUTOMATIC ) tmpEmptyPos;
    VAR( Dem_u08_AsyncDataQueIndexType, AUTOMATIC ) tmpStoredItemNum;
    VAR( Dem_u08_AsyncDataQueIndexType, AUTOMATIC ) itemNum;

    retVal = DEM_IRT_NG;

    itemNum             =   Dem_ExecAsyncDataQueTable[ AsyncDataQueIndex ].ItemNum;                     /* [GUDCHK:CALLER]AsyncDataQueIndex */
    tmpEmptyPos         =   *( Dem_ExecAsyncDataQueTable[ AsyncDataQueIndex ].EmptyPosVPtr );           /* [GUDCHK:CALLER]AsyncDataQueIndex */
    tmpStoredItemNum    =   *( Dem_ExecAsyncDataQueTable[ AsyncDataQueIndex ].StoredItemNumVPtr );      /* [GUDCHK:CALLER]AsyncDataQueIndex */

    if( tmpStoredItemNum < itemNum )
    {
        *QueIndexPtr = tmpEmptyPos;

        tmpEmptyPos         =   tmpEmptyPos + (Dem_u08_AsyncDataQueIndexType)1U;
        tmpStoredItemNum    =   tmpStoredItemNum + (Dem_u08_AsyncDataQueIndexType)1U;

        if( tmpEmptyPos >= itemNum )
        {
            tmpEmptyPos = DEM_ASYNCDATAQUE_INITIAL_DATA_EMPTYPOS;
        }

        retVal = DEM_IRT_OK;

        *( Dem_ExecAsyncDataQueTable[ AsyncDataQueIndex ].EmptyPosVPtr )       =   tmpEmptyPos;         /* [GUDCHK:CALLER]AsyncDataQueIndex */
        *( Dem_ExecAsyncDataQueTable[ AsyncDataQueIndex ].StoredItemNumVPtr )  =   tmpStoredItemNum;    /* [GUDCHK:CALLER]AsyncDataQueIndex */
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_AsyncReqData_SetQueData                              */
/* Description   | Set data to the data queue with specified index.         */
/* Preconditions | none                                                     */
/* Parameters    | [in/out] DataQueInfoPtr :                                */
/*               |        The pointer of the data queue.                    */
/*               | [in] QueIndex :                                          */
/*               |        Index of the data queue.                          */
/*               | [in] DataBufferPtr :                                     */
/*               |        The pointer of the data buffer.                   */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_AsyncReqData_SetQueData
(
    VAR( Dem_u08_AsyncDataQueTableIndexType, AUTOMATIC ) AsyncDataQueIndex,         /* [PRMCHK:CALLER] */
    VAR( Dem_u08_AsyncDataQueIndexType, AUTOMATIC ) QueIndex,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DataBufferPtr
)
{
    VAR( Dem_u08_AsyncDataQueItemSizeType, AUTOMATIC ) dataCnt;
    VAR( Dem_u16_AsyncDataQueBuffIndexType, AUTOMATIC ) dataStartIndex;
    VAR( Dem_u16_AsyncDataQueBuffIndexType, AUTOMATIC ) dataQueIndex;
    VAR( Dem_u08_AsyncDataQueItemSizeType, AUTOMATIC ) itemSize;
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) queBufferPtr;

    itemSize            =   Dem_ExecAsyncDataQueTable[ AsyncDataQueIndex ].ItemSize;                                        /* [GUDCHK:CALLER]AsyncDataQueIndex */
    queBufferPtr        =   Dem_ExecAsyncDataQueTable[ AsyncDataQueIndex ].BuffPtr;                                         /* [GUDCHK:CALLER]AsyncDataQueIndex */

    /* Get the index of stored data start position. */
    dataStartIndex = (Dem_u16_AsyncDataQueBuffIndexType)( (Dem_u16_AsyncDataQueBuffIndexType)itemSize * (Dem_u16_AsyncDataQueBuffIndexType)QueIndex );

    /* Set data to the data queue. */
    for( dataCnt = (Dem_u08_AsyncDataQueItemSizeType)0U; dataCnt < itemSize; dataCnt++ )                                    /* [GUD:for]dataCnt */
    {
        dataQueIndex = (Dem_u16_AsyncDataQueBuffIndexType)( dataStartIndex + (Dem_u16_AsyncDataQueBuffIndexType)dataCnt );  /* [GUD:for]dataQueIndex */
        queBufferPtr[ dataQueIndex ] = DataBufferPtr[ dataCnt ];                                                            /* [GUD]dataQueIndex *//* [GUD]dataCnt *//* [ARYCHK] itemSize+dataStartIndex / 1 / dataQueIndex *//* [ARYCHK] itemSize / 1 / dataCnt */
    }

    return ;
}


/****************************************************************************/
/* Function Name | Dem_AsyncReqData_ReleaseQue                              */
/* Description   | Get data from the data queue and release the data queue- */
/*               |  with specified index.                                   */
/* Preconditions | none                                                     */
/* Parameters    | [in/out] DataQueInfoPtr :                                */
/*               |        The pointer of the data queue.                    */
/*               | [in] QueIndex :                                          */
/*               |        Index of the data queue.                          */
/*               | [out] DataBufferPtr :                                    */
/*               |        The pointer of the data buffer.                   */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_NG : failed                               */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_AsyncReqData_ReleaseQue
(
    VAR( Dem_u08_AsyncDataQueTableIndexType, AUTOMATIC ) AsyncDataQueIndex,         /* [PRMCHK:CALLER] */
    VAR( Dem_u08_AsyncDataQueIndexType, AUTOMATIC ) QueIndex,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DataBufferPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_AsyncDataQueItemSizeType, AUTOMATIC ) dataCnt;
    VAR( Dem_u16_AsyncDataQueBuffIndexType, AUTOMATIC ) dataStartIndex;
    VAR( Dem_u16_AsyncDataQueBuffIndexType, AUTOMATIC ) dataQueIndex;
    VAR( Dem_u08_AsyncDataQueIndexType, AUTOMATIC ) tmpEmptyPos;
    VAR( Dem_u08_AsyncDataQueIndexType, AUTOMATIC ) tmpStoredItemNum;
    VAR( Dem_u08_AsyncDataQueItemSizeType, AUTOMATIC ) itemSize;
    VAR( Dem_u08_AsyncDataQueIndexType, AUTOMATIC ) itemNum;
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) queBufferPtr;

    retVal = DEM_IRT_NG;

    itemSize            =   Dem_ExecAsyncDataQueTable[ AsyncDataQueIndex ].ItemSize;                                    /* [GUDCHK:CALLER]AsyncDataQueIndex */
    itemNum             =   Dem_ExecAsyncDataQueTable[ AsyncDataQueIndex ].ItemNum;                                     /* [GUDCHK:CALLER]AsyncDataQueIndex */
    queBufferPtr        =   Dem_ExecAsyncDataQueTable[ AsyncDataQueIndex ].BuffPtr;                                     /* [GUDCHK:CALLER]AsyncDataQueIndex */

    if( QueIndex < itemNum )
    {
        tmpEmptyPos         =   *( Dem_ExecAsyncDataQueTable[ AsyncDataQueIndex ].EmptyPosVPtr );                       /* [GUDCHK:CALLER]AsyncDataQueIndex */
        tmpStoredItemNum    =   *( Dem_ExecAsyncDataQueTable[ AsyncDataQueIndex ].StoredItemNumVPtr );                  /* [GUDCHK:CALLER]AsyncDataQueIndex */

        /* Get the index of stored data start position. */
        dataStartIndex = (Dem_u16_AsyncDataQueBuffIndexType)( (Dem_u16_AsyncDataQueBuffIndexType)itemSize * (Dem_u16_AsyncDataQueBuffIndexType)QueIndex );

        /* Get data from the data queue. */
        for( dataCnt = (Dem_u08_AsyncDataQueItemSizeType)0U; dataCnt < itemSize; dataCnt++ )                                        /* [GUD:for]dataCnt */
        {
            dataQueIndex = (Dem_u16_AsyncDataQueBuffIndexType)( dataStartIndex + (Dem_u16_AsyncDataQueBuffIndexType)dataCnt );      /* [GUD:for]dataQueIndex */
            DataBufferPtr[ dataCnt ] = queBufferPtr[ dataQueIndex ];                                                                /* [GUD]dataQueIndex *//* [GUD]dataCnt *//* [ARYCHK] itemSize / 1 / dataCnt *//* [ARYCHK] itemSize+dataStartIndex / 1 / dataQueIndex */
        }

        /* Release the data queue. */
        if( tmpStoredItemNum == itemNum )
        {
            tmpEmptyPos = QueIndex;
        }
        tmpStoredItemNum    =   tmpStoredItemNum - (Dem_u08_AsyncDataQueIndexType)1U;

        retVal = DEM_IRT_OK;

        *( Dem_ExecAsyncDataQueTable[ AsyncDataQueIndex ].EmptyPosVPtr )       =   tmpEmptyPos;                         /* [GUDCHK:CALLER]AsyncDataQueIndex */
        *( Dem_ExecAsyncDataQueTable[ AsyncDataQueIndex ].StoredItemNumVPtr )  =   tmpStoredItemNum;                    /* [GUDCHK:CALLER]AsyncDataQueIndex */
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_AsyncReqData_ReleaseQueWithoutData                   */
/* Description   | Get data from the data queue and release the data queue- */
/*               |  with specified index.                                   */
/* Preconditions | none                                                     */
/* Parameters    | [in/out] DataQueInfoPtr :                                */
/*               |        The pointer of the data queue.                    */
/*               | [in] QueIndex :                                          */
/*               |        Index of the data queue.                          */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-10-0     | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_AsyncReqData_ReleaseQueWithoutData
(
    VAR( Dem_u08_AsyncDataQueTableIndexType, AUTOMATIC ) AsyncDataQueIndex,         /* [PRMCHK:CALLER] */
    VAR( Dem_u08_AsyncDataQueIndexType, AUTOMATIC ) QueIndex
)
{
    VAR( Dem_u08_AsyncDataQueIndexType, AUTOMATIC ) tmpEmptyPos;
    VAR( Dem_u08_AsyncDataQueIndexType, AUTOMATIC ) tmpStoredItemNum;
    VAR( Dem_u08_AsyncDataQueIndexType, AUTOMATIC ) itemNum;

    itemNum             =   Dem_ExecAsyncDataQueTable[ AsyncDataQueIndex ].ItemNum;                                     /* [GUDCHK:CALLER]AsyncDataQueIndex */

    if( QueIndex < itemNum )
    {
        tmpEmptyPos         =   *( Dem_ExecAsyncDataQueTable[ AsyncDataQueIndex ].EmptyPosVPtr );                       /* [GUDCHK:CALLER]AsyncDataQueIndex */
        tmpStoredItemNum    =   *( Dem_ExecAsyncDataQueTable[ AsyncDataQueIndex ].StoredItemNumVPtr );                  /* [GUDCHK:CALLER]AsyncDataQueIndex */

        if ( tmpStoredItemNum > DEM_ASYNCDATAQUE_INITIAL_DATA_STOREDITEMNUM )
        {
            /* Release the data queue. */
            if( tmpStoredItemNum == itemNum )
            {
                tmpEmptyPos = QueIndex;
            }
            tmpStoredItemNum    =   tmpStoredItemNum - (Dem_u08_AsyncDataQueIndexType)1U;

            *( Dem_ExecAsyncDataQueTable[ AsyncDataQueIndex ].EmptyPosVPtr )       =   tmpEmptyPos;                         /* [GUDCHK:CALLER]AsyncDataQueIndex */
            *( Dem_ExecAsyncDataQueTable[ AsyncDataQueIndex ].StoredItemNumVPtr )  =   tmpStoredItemNum;                    /* [GUDCHK:CALLER]AsyncDataQueIndex */
        }
    }

    return ;
}


/****************************************************************************/
/* Function Name | Dem_AsyncReqData_ReleaseQueIndex                         */
/* Description   | Release the data queue with specified index.             */
/* Preconditions | none                                                     */
/* Parameters    | [in/out] DataQueInfoPtr :                                */
/*               |        The pointer of the data queue.                    */
/*               | [in] QueIndex :                                          */
/*               |        Index of the data queue.                          */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_AsyncReqData_ReleaseQueIndex
(
    VAR( Dem_u08_AsyncDataQueTableIndexType, AUTOMATIC ) AsyncDataQueIndex,         /* [PRMCHK:CALLER] */
    VAR( Dem_u08_AsyncDataQueIndexType, AUTOMATIC ) QueIndex
)
{
    VAR( Dem_u08_AsyncDataQueIndexType, AUTOMATIC ) tmpStoredItemNum;

    /* Release the data queue. */
    *( Dem_ExecAsyncDataQueTable[ AsyncDataQueIndex ].EmptyPosVPtr ) = QueIndex;                                        /* [GUDCHK:CALLER]AsyncDataQueIndex */

    tmpStoredItemNum    =   *( Dem_ExecAsyncDataQueTable[ AsyncDataQueIndex ].StoredItemNumVPtr );                      /* [GUDCHK:CALLER]AsyncDataQueIndex */

    tmpStoredItemNum    =   tmpStoredItemNum - (Dem_u08_AsyncDataQueIndexType)1U;

    *( Dem_ExecAsyncDataQueTable[ AsyncDataQueIndex ].StoredItemNumVPtr )  =   tmpStoredItemNum;                        /* [GUDCHK:CALLER]AsyncDataQueIndex */

    return ;
}

#if ( DEM_TRIGGER_FIM_REPORTS == STD_ON )
/****************************************************************************/
/* Function Name | Dem_AsyncReqData_GetEventStatus                          */
/* Description   | Get event status by the data queue with specified index. */
/* Preconditions | none                                                     */
/* Parameters    | [in/out] DataQueInfoPtr :                                */
/*               |        The pointer of the data queue.                    */
/*               | [in] QueIndex :                                          */
/*               |        Index of the data queue.                          */
/*               | [out] EventStatusPtr :                                   */
/*               |        The pointer of the event status.                  */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_AsyncReqData_GetEventStatus
(
    VAR( Dem_u08_AsyncDataQueTableIndexType, AUTOMATIC ) AsyncDataQueIndex,         /* [PRMCHK:CALLER] */
    VAR( Dem_u08_AsyncDataQueIndexType, AUTOMATIC ) QueIndex,                       /* [PRMCHK:CALLER] */
    P2VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC, AUTOMATIC ) EventStatusPtr
)
{
    VAR( Dem_u16_AsyncDataQueBuffIndexType, AUTOMATIC ) dataStartIndex;
    VAR( Dem_u08_AsyncDataQueItemSizeType, AUTOMATIC ) itemSize;

    /* Get the index of stored data start position. */
    itemSize       =   Dem_ExecAsyncDataQueTable[ AsyncDataQueIndex ].ItemSize;                                         /* [GUDCHK:CALLER]AsyncDataQueIndex */
    dataStartIndex = (Dem_u16_AsyncDataQueBuffIndexType)( (Dem_u16_AsyncDataQueBuffIndexType)itemSize * (Dem_u16_AsyncDataQueBuffIndexType)QueIndex );

    /* Get the first data of the data queue as the event status. */
    /* The event status stored position is defined in the macro DEM_ASYNCDATAQUE_EVENTSTATUS_POS. */
    *EventStatusPtr = Dem_ExecAsyncDataQueTable[ AsyncDataQueIndex ].BuffPtr[ dataStartIndex ];                         /* [GUDCHK:CALLER]AsyncDataQueIndex *//* [GUDCHK:CALLER]dataStartIndex *//* [ARYCHK] itemSize+dataStartIndex / 1 / dataStartIndex */

    return ;
}
#endif /* DEM_TRIGGER_FIM_REPORTS -STD_ON- */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* DEM_ASYNCDATAQUE_USE -STD_ON- */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

