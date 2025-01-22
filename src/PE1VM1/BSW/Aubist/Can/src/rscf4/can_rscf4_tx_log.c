/* can_rscf4_tx_log_c_v2-2-0                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CAN/RSCF4/TX/LOGICAL/CODE                                 */
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
#include "../../cfg/rscf4/can_rscf4_cfg_ext.h"
#include "../../cfg/rscf4/can_rscf4_cfg.h"

#include <can/common/can_cv_can.h>
#include <can/common/can_cv_cbk.h>
#include <can/common/can_memmap.h>
#include <can/rscf4/can_rscf4.h>

#if (CAN_CFG_CAN == CAN_USE)
#include <can/rscf4/can_rscf4_tb_log.h>
#include <can/rscf4/can_rscf4_st.h>
#include <can/rscf4/can_rscf4_tx.h>


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define CAN_TX_PDUID_INIT               ( 0xFFFFU )
#define CAN_TX_DL_MAX_CAN               ( 15U )
#define CAN_TX_DL_MAX_CANFD             ( 64U )
#define CAN_TX_ID_FDF_MSK               ( 0x40000000UL )
#define CAN_TX_ID_FDF_CANFD             ( 0x40000000UL )


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#if (CAN_CFG_TRANSMIT == CAN_USE)
static PduIdType Can_tx_u2TxPduId[ CAN_TB_HTHNUM_MAX ];
#endif /* (CAN_CFG_TRANSMIT == CAN_USE) */


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Can_tx_Init                                              */
/* Description   | Transmission Function Initialization                     */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
void
Can_tx_Init( void )
{
#if (CAN_CFG_TRANSMIT == CAN_USE)
    uint16  u2HthIdx;
    uint16  u2HthNumMax;

    /* RAM initialization process */
    u2HthNumMax = Can_tb_u2HthNumMax;
    for ( u2HthIdx = (uint16)0U; u2HthIdx < u2HthNumMax; u2HthIdx++ )
    {
        Can_tx_u2TxPduId[ u2HthIdx ] = (uint16)CAN_TX_PDUID_INIT;
    }
#endif /* (CAN_CFG_TRANSMIT == CAN_USE) */
}


/****************************************************************************/
/* Function Name | Can_tx_ClearTxInf                                        */
/* Description   | Transmission Information Clear                           */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 u1Controller                                       */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
void
Can_tx_ClearTxInf( uint8 u1Controller )
{
#if (CAN_CFG_TRANSMIT == CAN_USE)
    CanConst CanTbHohMbAllocType *  ptHohMbAlloc;
    uint16                          u2HthIdx;
    uint16                          u2HthStart;
    uint16                          u2HthEnd;

    ptHohMbAlloc = &( Can_tb_stHohMbAlloc[ u1Controller ] );
    u2HthStart   = ptHohMbAlloc->u2HthOffset - Can_tb_u2HrhNumMax;
    u2HthEnd     = u2HthStart + (uint16)ptHohMbAlloc->u1HthNum;

    /* PDU ID initialization process */
    for ( u2HthIdx = u2HthStart; u2HthIdx < u2HthEnd; u2HthIdx++ )
    {
        Can_tx_u2TxPduId[ u2HthIdx ] = (uint16)CAN_TX_PDUID_INIT;
    }
#endif /* (CAN_CFG_TRANSMIT == CAN_USE) */
}


/****************************************************************************/
/* Function Name | Can_Write                                                */
/* Description   | Transmission Request                                     */
/* Preconditions | See Design Documents                                     */
/* Parameters    | Can_HwHandleType Hth                                     */
/*               | CanConstR Can_PduType* PduInfo                           */
/*               |   PduIdType  swPduHandle                                 */
/*               |   uint8      length                                      */
/*               |   Can_IdType id                                          */
/*               |   uint8*     sdu                                         */
/* Return Value  | Can_ReturnType                                           */
/*               |   CAN_OK                                                 */
/*               |   CAN_NOT_OK                                             */
/*               |   CAN_BUSY                                               */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
#if (CAN_CFG_TRANSMIT == CAN_USE)
Can_ReturnType
Can_Write( Can_HwHandleType Hth, CanConstR Can_PduType* PduInfo )
{
    CanConst CanHohCfgType *  ptHohTbl;
    CanMsgType                stMsg;
    uint32                    u4IdVal;
    uint16                    u2ControllerStatus;
    uint16                    u2HthIdx;
    uint8                     u1Controller;
    uint8                     u1Mbox;
    uint8                     u1DataLength;
    uint8                     u1TxRet;
    uint8                     u1Ret;

    u1Ret = (uint8)CAN_NOT_OK;

    ptHohTbl = &( Can_tb_ptHohCfgTbl[ CAN_IDX0 ] );
    u1Controller = ptHohTbl[ Hth ].u1ControllerID;

    u2ControllerStatus = Can_st_u2ControllerStatus[ u1Controller ];
    if ( u2ControllerStatus == (uint16)CAN_ST_CTRL_STARTED )
    {
        Can_DI()

        u1DataLength = PduInfo->length;
        u4IdVal      = PduInfo->id;
        stMsg.ptData = PduInfo->sdu;

        if ( ( u4IdVal & CAN_TX_ID_FDF_MSK ) == CAN_TX_ID_FDF_CANFD )
        {
            if ( u1DataLength > (uint8)CAN_TX_DL_MAX_CANFD )
            {
                u1DataLength = (uint8)CAN_TX_DL_MAX_CANFD;
            }
            stMsg.u1Length = u1DataLength;
            stMsg.u4Id     = u4IdVal;

            u1Mbox = ptHohTbl[ Hth ].u1MboxNo;

            /* Transmission request process */
            u1TxRet = Can_tx_TxReq_CanFdFrame( u1Controller, u1Mbox, &stMsg );
        }
        else
        {
            if ( u1DataLength > (uint8)CAN_TX_DL_MAX_CAN )
            {
                u1DataLength = (uint8)CAN_TX_DL_MAX_CAN;
            }
            stMsg.u1Length = u1DataLength;
            stMsg.u4Id     = u4IdVal;

            u1Mbox = ptHohTbl[ Hth ].u1MboxNo;

            /* Transmission request process */
            u1TxRet = Can_tx_TxReq_CanFrame( u1Controller, u1Mbox, &stMsg );
        }

        if ( u1TxRet == (uint8)CAN_PROC_OK )
        {
            u2HthIdx  = (uint16)( Hth - Can_tb_u2HrhNumMax );
            Can_tx_u2TxPduId[ u2HthIdx ] = PduInfo->swPduHandle;
            u1Ret = (uint8)CAN_OK;
        }
        else if ( u1TxRet == (uint8)CAN_PROC_BUSY )
        {
            u1Ret = (uint8)CAN_BUSY;
        }
        else /* MISRA DEVIATION: no process */
        {
            /* If u1TxRet is CAN_PROC_NG, respond CAN_NOT_OK */
        }

        Can_EI()
    }

    return (u1Ret);
}
#endif /* (CAN_CFG_TRANSMIT == CAN_USE) */


/****************************************************************************/
/* Function Name | Can_MainFunction_Write                                   */
/* Description   | Transmission Periodic Process                            */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
#if (CAN_CFG_TRANSMIT == CAN_USE)
void
Can_MainFunction_Write( void )
{
    uint16  u2ControllerStatus;
    uint8   u1Controller;
    uint8   u1ControllerNumMax;

    u1ControllerNumMax = Can_tb_u1ControllerNumMax;
    for ( u1Controller = (uint8)0U; u1Controller < u1ControllerNumMax; u1Controller++ )
    {
        u2ControllerStatus = Can_st_u2ControllerStatus[ u1Controller ];
        if ( u2ControllerStatus == (uint16)CAN_ST_CTRL_STARTED )
        {
            /* Transmission completion confirmation process */
            (void)Can_tx_ChkTxFinMbox( u1Controller, (uint8)CAN_POLLING ); /* MISRA DEVIATION: no return check required */

#if (CAN_CFG_ABORTSEND == CAN_USE)
            /* Transmission abort completion confirmation process */
            Can_tx_ChkTxAbtMbox( u1Controller );

#endif /* (CAN_CFG_ABORTSEND == CAN_USE) */
        }
    }
}
#endif /* (CAN_CFG_TRANSMIT == CAN_USE) */


/****************************************************************************/
/* Function Name | Can_AbortSend                                            */
/* Description   | Transmission Abort Request                               */
/* Preconditions | See Design Documents                                     */
/* Parameters    | Can_HwHandleType Hth                                     */
/* Return Value  | Can_ReturnType                                           */
/*               |   CAN_OK                                                 */
/*               |   CAN_NOT_OK                                             */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
#if (CAN_CFG_TRANSMIT == CAN_USE)
Can_ReturnType
Can_AbortSend( Can_HwHandleType Hth )
{
#if (CAN_CFG_ABORTSEND == CAN_USE)
    CanConst CanHohCfgType *  ptHohTbl;
    uint16                    u2ControllerStatus;
    uint16                    u2HthIdx;
    uint16                    u2TxPduId;
    uint8                     u1AbtRet;
    uint8                     u1Controller;
    uint8                     u1Mbox;
    uint8                     u1Ret;

    u1Ret = (uint8)CAN_NOT_OK;

    ptHohTbl = &( Can_tb_ptHohCfgTbl[ CAN_IDX0 ] );
    u1Controller = ptHohTbl[ Hth ].u1ControllerID;

    u2ControllerStatus = Can_st_u2ControllerStatus[ u1Controller ];
    if ( u2ControllerStatus == (uint16)CAN_ST_CTRL_STARTED )
    {
        u1Mbox = ptHohTbl[ Hth ].u1MboxNo;

        /* Transmission abort process */
        u1AbtRet = Can_tx_TxAbt( u1Controller, u1Mbox );
        if ( u1AbtRet == (uint8)CAN_PROC_OK )
        {
            u2HthIdx  = (uint16)( Hth - Can_tb_u2HrhNumMax );

            u2TxPduId = Can_tx_u2TxPduId[ u2HthIdx ];

            Can_tx_u2TxPduId[ u2HthIdx ] = (uint16)CAN_TX_PDUID_INIT;

            CanIf_TxConfirmation( u2TxPduId );
        }

        u1Ret = (uint8)CAN_OK;
    }

    return ( u1Ret );
#else /* (CAN_CFG_ABORTSEND != CAN_USE) */
    return ( (uint8)CAN_NOT_OK );
#endif /* (CAN_CFG_ABORTSEND) */
}
#endif /* (CAN_CFG_TRANSMIT == CAN_USE) */


/****************************************************************************/
/* Function Name | Can_TxReq                                                */
/* Description   | User Transmission Request                                */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8  u1Controller                                      */
/*               | uint8  u1MsgBuffer                                       */
/*               | CanMsgType* ptMsg                                        */
/*               |   uint8* ptData                                          */
/*               |   uint32 u4Id                                            */
/*               |   uint8  u1Length                                        */
/* Return Value  | uint8                                                    */
/*               |   CAN_PROC_OK                                            */
/*               |   CAN_PROC_NG                                            */
/*               |   CAN_PROC_BUSY                                          */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
#if (CAN_CFG_TRANSMIT == CAN_USE)
#if (CAN_CFG_USER_TRANSMIT == CAN_USE)
uint8
Can_TxReq( uint8 u1Controller, uint8 u1MsgBuffer, CanMsgType* ptMsg )
{
    uint16  u2ControllerStatus;
    uint8   u1DataLength;
    uint8   u1Ret;

    u1Ret = (uint8)CAN_PROC_NG;

    u2ControllerStatus = Can_st_u2ControllerStatus[ u1Controller ];
    if ( u2ControllerStatus == (uint16)CAN_ST_CTRL_STARTED )
    {
        u1DataLength = ptMsg->u1Length;

        if ( ( ptMsg->u4Id & CAN_TX_ID_FDF_MSK ) == CAN_TX_ID_FDF_CANFD )
        {
            if ( u1DataLength > (uint8)CAN_TX_DL_MAX_CANFD )
            {
                u1DataLength = (uint8)CAN_TX_DL_MAX_CANFD;
            }
            ptMsg->u1Length = u1DataLength;

            /* Transmission request process */
            u1Ret = Can_tx_TxReq_CanFdFrame( u1Controller, u1MsgBuffer, ptMsg );
        }
        else
        {
            if ( u1DataLength > (uint8)CAN_TX_DL_MAX_CAN )
            {
                u1DataLength = (uint8)CAN_TX_DL_MAX_CAN;
            }
            ptMsg->u1Length = u1DataLength;

            /* Transmission request process */
            u1Ret = Can_tx_TxReq_CanFrame( u1Controller, u1MsgBuffer, ptMsg );
        }
    }

    return ( u1Ret );
}
#endif /* (CAN_CFG_USER_TRANSMIT == CAN_USE) */
#endif /* (CAN_CFG_TRANSMIT == CAN_USE) */


/****************************************************************************/
/* Function Name | Can_tx_TxConfMbox                                        */
/* Description   | MBOX Transmission Completion Notification                */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 u1Controller                                       */
/*               | uint8 u1Mbox                                             */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
#if (CAN_CFG_TRANSMIT == CAN_USE)
void
Can_tx_TxConfMbox( uint8 u1Controller, uint8 u1Mbox )
{
    CanConst CanTbHohMbAllocType *  ptHohMbAlloc;
#if (CAN_CFG_USER_TRANSMIT == CAN_USE)
    CanConst CanTbUTxMbAllocType *  ptUTxMbAlloc;
#endif /* (CAN_CFG_USER_TRANSMIT == CAN_USE) */
    uint16                          u2Hoh;
    uint16                          u2HthOfs;
    uint16                          u2HthIdx;
    uint16                          u2TxPduId;
    uint8                           u1HthMbOfs;
    uint8                           u1HthMbEnd;
#if (CAN_CFG_USER_TRANSMIT == CAN_USE)
    uint8                           u1UTxMbOfs;
    uint8                           u1UTxMbEnd;
#endif /* (CAN_CFG_USER_TRANSMIT == CAN_USE) */

    ptHohMbAlloc = &( Can_tb_stHohMbAlloc[ u1Controller ] );
    u2HthOfs     = ptHohMbAlloc->u2HthOffset;
    u1HthMbOfs   = ptHohMbAlloc->u1HthMbOffset;
    u1HthMbEnd   = u1HthMbOfs + ptHohMbAlloc->u1HthNum;

#if (CAN_CFG_USER_TRANSMIT == CAN_USE)
    ptUTxMbAlloc = &( Can_tb_stUTxMbAlloc[ u1Controller ] );
    u1UTxMbOfs   = ptUTxMbAlloc->u1UTxMbOffset;
    u1UTxMbEnd   = u1UTxMbOfs + ptUTxMbAlloc->u1UTxMbNum;
#endif /* (CAN_CFG_USER_TRANSMIT == CAN_USE) */

    if ( ( u1Mbox >= u1HthMbOfs ) && ( u1Mbox < u1HthMbEnd ) )
    {
        u2Hoh = ( ((uint16)u1Mbox - (uint16)u1HthMbOfs) + u2HthOfs );

        u2HthIdx  = (uint16)( u2Hoh - Can_tb_u2HrhNumMax );

        u2TxPduId = Can_tx_u2TxPduId[ u2HthIdx ];

        Can_tx_u2TxPduId[ u2HthIdx ] = (uint16)CAN_TX_PDUID_INIT;

        /* Notification of transmission completion for CANIF */
        CanIf_TxConfirmation( u2TxPduId );
    }
#if (CAN_CFG_USER_TRANSMIT == CAN_USE)
    else if ( ( u1Mbox >= u1UTxMbOfs ) && ( u1Mbox < u1UTxMbEnd ) )
    {
        /* Notification of transmission completion for user */
        Can_UTxConfirmation( u1Controller, u1Mbox );
    }
    else /* MISRA DEVIATION: no process */
    {
        /* This case discard due to an unintended transmission completion notification. */
    }
#endif /* (CAN_CFG_USER_TRANSMIT == CAN_USE) */
}
#endif /* (CAN_CFG_TRANSMIT == CAN_USE) */


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


#endif /* (CAN_CFG_CAN == CAN_USE) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-2-0         :2021/12/14                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
