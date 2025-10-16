/* can_rscf2_rx_log_c_v3-0-0                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CAN/RSCF2/RX/LOGICAL/CODE                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <can/common/can_cm_log.h>
#include <can/common/can_syscfg_ext.h>

#include <Can.h>
#include <CanIf_Cbk.h>
#include "../../cfg/common/can_cv_cfg.h"
#include "../../cfg/rscf2/can_rscf2_cfg_ext.h"
#include "../../cfg/rscf2/can_rscf2_cfg.h"

#include <can/common/can_cv_can.h>
#include <can/common/can_cv_cbk.h>
#include <can/common/can_memmap.h>
#include <can/rscf2/can_rscf2.h>

#if (CAN_CFG_CAN == CAN_USE)
#include <can/rscf2/can_rscf2_tb_log.h>
#include <can/rscf2/can_rscf2_st.h>
#include <can/rscf2/can_rscf2_rx.h>


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Can_MainFunction_Read                                    */
/* Description   | 受信定期処理                                             */
/* Preconditions | -                                                        */
/* Parameters    | なし                                                     */
/* Return Value  | なし                                                     */
/* Notes         | ・受信機能が未使用の場合は空関数とする。                 */
/*               | ・CanRxProcessingがINTERRUPTであってもMBOX単位でPOLLING  */
/*               |   を設定した場合は本APIで確認する。                      */
/*               | ・本APIはCANIFから呼び出されるため、CANIFの状態によって  */
/*               |   必ずしも定期的に呼び出されない。そのため、厳密な時間   */
/*               |   監視処理は実施しない。                                 */
/****************************************************************************/
void
Can_MainFunction_Read( void )
{
#if (CAN_CFG_RECEIVE == CAN_USE)
    uint16  u2ControllerStatus;     /* コントローラ状態 */
    uint8   u1Controller;           /* コントローラID   */
    uint8   u1ControllerNumMax;     /* コントローラ数   */

    u1ControllerNumMax = Can_tb_u1ControllerNumMax;
    for ( u1Controller = (uint8)0U; u1Controller < u1ControllerNumMax; u1Controller++ )
    {
        /* CANコントローラの開始チェック */
        u2ControllerStatus = Can_st_u2ControllerStatus[ u1Controller ];
        if ( u2ControllerStatus == (uint16)CAN_ST_CTRL_STARTED )
        {
            /* 制御対象CAN かつ 使用するコントローラに対し                  */
            /* 受信完了をチェックする。                                     */

            /* 制御対象CAN かつ 使用するコントローラか否かは                */
            /* コントローラ状態変数から判断する。                           */
            /* ※ 非制御対象CANの場合、Can_Init後 CAN_ST_CTRL_UNINIT で固定 */
            /*    制御対象CAN かつ 使用しないコントローラの場合は           */
            /*    Can_Init後、CAN_ST_CTRL_INIT で固定されるため             */
            /*    コンフィグ設定のチェックは不要。                          */

            /* 受信完了確認の実施 */
            /* 戻り値は不正割り込みチェック用であり、ポーリング受信の場合確認しない。 */
            (void)Can_rx_ChkRxFinMbox( u1Controller, (uint8)CAN_POLLING ); /* MISRA DEVIATION: no return check required */
        }
    }
#endif /* (CAN_CFG_RECEIVE == CAN_USE) */
}


/****************************************************************************/
/* Function Name | Can_rx_RxIndMbox                                         */
/* Description   | MBOX受信完了通知                                         */
/* Preconditions | -                                                        */
/* Parameters    | uint8 u1Controller     : CANコントローラ番号             */
/*               | uint8 u1Mbox           : 受信完了MBOX番号                */
/*               | CanConstR CanMsgType* ptMsg : 受信メッセージ             */
/*               |   uint8* ptData        : 受信データへのポインタ          */
/*               |   uint32 u4Id          : CAN ID                          */
/*               |   uint8  u1Length      : データ長                        */
/* Return Value  | なし                                                     */
/* Notes         | ・受信機能が未使用にコンフィグされている場合、本APIは    */
/*               |   提供しない                                             */
/*               | ・受信用MBOXでのみ通知される前提とする                   */
/****************************************************************************/
#if (CAN_CFG_RECEIVE == CAN_USE)
void
Can_rx_RxIndMbox( uint8 u1Controller, uint8 u1Mbox, CanConstR CanMsgType* ptMsg )
{
    CanConst CanTbHohMbAllocType *  ptHohMbAlloc;       /* HOH-MBOX配置情報テーブルへのポインタ */
    uint8 *                         ptCanSdu;           /* CANデータ領域へのポインタ            */
    uint32                          u4IdVal;            /* CAN ID                               */
    uint16                          u2Hoh;              /* HOH番号                              */
    uint16                          u2HrhOfs;           /* コントローラ毎HRH開始位置(HOH番号)   */
    uint8                           u1HrhMbOfs;         /* HRH用MBOX開始位置(MBOX番号)          */
    uint8                           u1DataLength;       /* 受信データ長                         */
#if (CAN_CFG_USER_RX_HOOK == CAN_USE)
    uint8                           u1URxIndResult;     /* ユーザ受信通知の応答(CANIF配信有無)  */
#endif /* (CAN_CFG_USER_RX_HOOK == CAN_USE) */

    /* 受信メッセージがある場合は             */
    /* コントローラモード状態によらず通知する */

    /* HOH配置情報取得 */
    ptHohMbAlloc = &( Can_tb_stHohMbAlloc[ u1Controller ] );
    u2HrhOfs     = ptHohMbAlloc->u2HrhOffset;
    u1HrhMbOfs   = ptHohMbAlloc->u1HrhMbOffset;

    /* MBOX→HOH変換 */
    u2Hoh = ( ( (uint16)u1Mbox - (uint16)u1HrhMbOfs ) + u2HrhOfs );

#if (CAN_CFG_USER_RX_HOOK == CAN_USE)
    /* ユーザ受信完了通知 */
    u1URxIndResult = Can_URxIndication( u1Controller, u1Mbox, ptMsg );
    if ( u1URxIndResult == (uint8)CAN_PROC_OK )
#endif /* (CAN_CFG_USER_RX_HOOK == CAN_USE) */
    {
        /* CANIFに対する受信完了を通知 */
        ptCanSdu     = ptMsg->ptData;
        u4IdVal      = ptMsg->u4Id;
        u1DataLength = ptMsg->u1Length;
        CanIf_RxIndication( u2Hoh, u4IdVal, u1DataLength, ptCanSdu );
    }
}
#endif /* (CAN_CFG_RECEIVE == CAN_USE) */


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


#endif /* (CAN_CFG_CAN == CAN_USE) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2017/02/22                                              */
/*  v2-0-1         :2017/04/24                                              */
/*  v2-2-0         :2020/02/26                                              */
/*  v3-0-0         :2025/02/13                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
