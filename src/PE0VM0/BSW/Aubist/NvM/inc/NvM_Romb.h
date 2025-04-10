/* NvM_Romb.h v1-0-0                                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | NVM/ROMB/HEADER                                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     NVM_ROMB_H
#define     NVM_ROMB_H

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

#define NVM_START_SEC_CODE
#include <NvM_MemMap.h>

FUNC( void, NVM_CODE )
NvM_Romb_Init( void );

FUNC( Std_ReturnType, NVM_CODE )
NvM_Romb_GetRomData(
    NvM_BlockIdType BlockId,
    P2VAR( uint8, AUTOMATIC, TYPEDEF ) DstData
);

FUNC( boolean, NVM_CODE )
NvM_Romb_IsExistingRomBlock(
    NvM_BlockIdType BlockId
);

#define NVM_STOP_SEC_CODE
#include <NvM_MemMap.h>

#endif  /* NVM_ROMB_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
