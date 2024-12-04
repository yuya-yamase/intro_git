/* Fee_Dfc.h v2-0-0                                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/DFC/HEADER                                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef FEE_DFC_H
#define FEE_DFC_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
/* MHA[データFlash]ヘッダ */
#include "Fee_Common.h"
#include <Mscd_Common.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define FEE_DFC_STATUS_OK           ((uint32)0x00000000L)   /* 正常終了                */
#define FEE_DFC_STATUS_BUSY         ((uint32)0x000000fdL)   /* BUSY                    */
#define FEE_DFC_STATUS_ERROR        ((uint32)0x000000ffL)   /* エラー                  */

#define FEE_DFC_ADDRESS_INVALID     ((uint32)0xFFFFFFFFUL)  /* アドレス無効値 */

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define FEE_START_SEC_CODE
#include <Fee_MemMap.h>

FUNC( Std_ReturnType, FEE_CODE )
Fee_Dfc_CheckRAM( void );

FUNC( void, FEE_CODE )
Fee_Dfc_SetRAMSub( void );

FUNC(void, FEE_CODE) Fee_Dfc_Write(const uint32 Address, P2CONST(uint8, AUTOMATIC, TYPEDEF) ptu1Data, const uint16 u2Len);
FUNC(void, FEE_CODE) Fee_Dfc_Erase( const uint32 Address );
FUNC( void, FEE_CODE )
Fee_Dfc_BlankCheck(
    const uint32 StartTailAddress,
    const uint32 EndTopAddress,
    uint32 MaxBlankCheckNum
);

#if ( MSCD_FREESPACE_USE == STD_ON )
FUNC( uint32, FEE_CODE )
Fee_Dfc_GetBlankCheckResult(
    P2VAR( uint32, AUTOMATIC, TYPEDEF ) WriteAddr
);
#endif /*( MSCD_FREESPACE_USE == STD_ON )*/

FUNC(uint32 , FEE_CODE) Fee_Dfc_ExecFlsMainFunction( void );
FUNC(uint32 , FEE_CODE) Fee_Dfc_ExecBlankCheck( void );
FUNC(void, FEE_CODE) Fee_Dfc_End( void );

FUNC( void, FEE_CODE )
Fee_Dfc_Init( void );

FUNC( void, FEE_CODE )
Fee_Dfc_Cancel( void );

FUNC(uint32 , FEE_CODE) Fee_Dfc_GetFLAP( void );
FUNC(MemIf_StatusType, FEE_CODE) Fee_Dfc_GetStatus(void);

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

#endif /* FEE_DFC_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/*  1-1-0          :2019/08/19                                              */
/*  2-0-0          :2022/08/24                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

