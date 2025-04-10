/* Fee_Record_Pos_Tbl.h v1-1-0                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/RECORD/POS/TBL/HEADER                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef FEE_RECORD_POS_TBL_H
#define FEE_RECORD_POS_TBL_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
/* MHA[データFlash]ライブラリヘッダ */
#include "Fee_Common.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* 有効レコード位置TBL設定値 */
#define FEE_IDNONE              ((uint16)0xAAAAU)   /* データ未登録 */
#define FEE_ID_MRR_NONE         ((uint16)0x5555U)   /* データ未登録(ミラー) */

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define FEE_START_SEC_CODE
#include <Fee_MemMap.h>

/* Clear */
FUNC( void, FEE_CODE )
Fee_RecordPosTbl_ClearPosArea(
    uint8 u1AreaNum
);

FUNC( void, FEE_CODE )
Fee_RecordPosTbl_ClearPosAll( void );

/* Ready */
FUNC( uint32, FEE_CODE )
Fee_RecordPosTbl_ReadyPosArea(
    uint8 u1AreaNum,
    uint8 u1BlockNum,
    uint32 u4SrchAddress
);

/* Get */
FUNC( uint32, FEE_CODE )
Fee_RecordPosTbl_GetPos(
    uint8 u1AreaNum,
    uint16 u2DataNum,
    P2VAR(uint16, AUTOMATIC, TYPEDEF) ptu2RecordPos
);

/* Set */
FUNC( void, FEE_CODE )
Fee_RecordPosTbl_SetPos(
    uint8 u1AreaNum,
    uint16 u2DataNum,
    uint16 u2RecordPos
);

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>


#endif /* FEE_RECORD_POS_TBL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/*  1-1-0          :2019/07/09                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
