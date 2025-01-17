/* NvM_WdtExt.h v1-0-0                                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | NVM/WDTEXT/HEADER                                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     NVM_WDTEXT_H
#define     NVM_WDTEXT_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

#define NVM_WDTEXT_ID_NUM        ( 1U )

#define NVM_WDTEXT_ID_NVM           ( 0U )

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

typedef uint16      NvM_WdtExt_WdtIdType;

typedef P2FUNC ( void, NVM_CODE, NvM_WdtExt_WdtFuncPtrType ) ( NvM_WdtExt_WdtIdType Id );

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

#define NVM_START_SEC_CODE
#include <NvM_MemMap.h>

FUNC( void, NVM_CODE )
NvM_WdtExt_Init( void );

FUNC( void, NVM_CODE )
NvM_WdtExt_MainFunction( void );

FUNC( void, NVM_CODE )
NvM_WdtExt_WatchDogStart(
    NvM_WdtExt_WdtIdType Id,
    uint32 TimeoutValue
);

FUNC( void, NVM_CODE )
NvM_WdtExt_WatchDogEnd(
    NvM_WdtExt_WdtIdType Id
);

#define NVM_STOP_SEC_CODE
#include <NvM_MemMap.h>

#endif  /* NVM_WDTEXT_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
