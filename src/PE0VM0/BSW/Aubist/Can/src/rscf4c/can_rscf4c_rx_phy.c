/* can_rscf4c_rx_phy_c_m10700_v3-0-0                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CAN/RSCF4C/RX/PHYSICAL/CODE                               */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <can/common/can_cm_log.h>
#include <can/common/can_syscfg_ext.h>

#include <Can.h>
#include "../../cfg/common/can_cv_cfg.h"
#include "../../cfg/rscf4c/can_rscf4c_cfg_ext.h"
#include "../../cfg/rscf4c/can_rscf4c_cfg.h"

#include <can/common/can_cv_can.h>
#include <can/common/can_memmap.h>
#include <can/rscf4c/can_rscf4c.h>
#include <can/rscf4c/can_rscf4c_cm_phy.h>

#if (CAN_CFG_CAN == CAN_USE)
#if (CAN_CFG_RECEIVE == CAN_USE)
#include <can/rscf4c/can_rscf4c_tb_phy.h>
#include <can/rscf4c/can_rscf4c_rx.h>
#include <can/rscf4c/can_rscf4c_fs.h>


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define CAN_RX_DLC_NUM                  ( 16U )
#define CAN_RX_ID_FDF_CANFD             ( 0x40000000UL )


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#if (CAN_RX_RXFINISH_ANYCH_USE == CAN_USE)
static void Can_rx_RxFinish( uint8 u1Controller );
#endif /* (CAN_RX_RXFINISH_ANYCH_USE == CAN_USE) */


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
static CanConst uint8 Can_rx_u1DataLengthVal[CAN_RX_DLC_NUM] = { (uint8)0U ,(uint8)1U  ,(uint8)2U  ,(uint8)3U  ,(uint8)4U  ,(uint8)5U  ,(uint8)6U  ,(uint8)7U
                                                                ,(uint8)8U ,(uint8)12U ,(uint8)16U ,(uint8)20U ,(uint8)24U ,(uint8)32U ,(uint8)48U ,(uint8)64U };


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Can_RxFinish_0                                           */
/* Description   | Reception Completion Interrupt                           */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
#if (CAN_RX_RXFINISH_USE_0 == CAN_USE)
void
Can_RxFinish_0( void )
{
    Can_rx_RxFinish( (uint8)CAN_CONTROLLER_0 );
}
#endif /* (CAN_RX_RXFINISH_USE_0 == CAN_USE) */


/****************************************************************************/
/* Function Name | Can_RxFinish_1                                           */
/* Description   | Reception Completion Interrupt                           */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
#if (CAN_RX_RXFINISH_USE_1 == CAN_USE)
void
Can_RxFinish_1( void )
{
    Can_rx_RxFinish( (uint8)CAN_CONTROLLER_1 );
}
#endif /* (CAN_RX_RXFINISH_USE_1 == CAN_USE) */


/****************************************************************************/
/* Function Name | Can_RxFinish_2                                           */
/* Description   | Reception Completion Interrupt                           */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
#if (CAN_RX_RXFINISH_USE_2 == CAN_USE)
void
Can_RxFinish_2( void )
{
    Can_rx_RxFinish( (uint8)CAN_CONTROLLER_2 );
}
#endif /* (CAN_RX_RXFINISH_USE_2 == CAN_USE) */


/****************************************************************************/
/* Function Name | Can_RxFinish_3                                           */
/* Description   | Reception Completion Interrupt                           */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
#if (CAN_RX_RXFINISH_USE_3 == CAN_USE)
void
Can_RxFinish_3( void )
{
    Can_rx_RxFinish( (uint8)CAN_CONTROLLER_3 );
}
#endif /* (CAN_RX_RXFINISH_USE_3 == CAN_USE) */


/****************************************************************************/
/* Function Name | Can_RxFinish_4                                           */
/* Description   | Reception Completion Interrupt                           */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
#if (CAN_RX_RXFINISH_USE_4 == CAN_USE)
void
Can_RxFinish_4( void )
{
    Can_rx_RxFinish( (uint8)CAN_CONTROLLER_4 );
}
#endif /* (CAN_RX_RXFINISH_USE_4 == CAN_USE) */


/****************************************************************************/
/* Function Name | Can_RxFinish_5                                           */
/* Description   | Reception Completion Interrupt                           */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
#if (CAN_RX_RXFINISH_USE_5 == CAN_USE)
void
Can_RxFinish_5( void )
{
    Can_rx_RxFinish( (uint8)CAN_CONTROLLER_5 );
}
#endif /* (CAN_RX_RXFINISH_USE_5 == CAN_USE) */


/****************************************************************************/
/* Function Name | Can_RxFinish_6                                           */
/* Description   | Reception Completion Interrupt                           */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
#if (CAN_RX_RXFINISH_USE_6 == CAN_USE)
void
Can_RxFinish_6( void )
{
    Can_rx_RxFinish( (uint8)CAN_CONTROLLER_6 );
}
#endif /* (CAN_RX_RXFINISH_USE_6 == CAN_USE) */


/****************************************************************************/
/* Function Name | Can_RxFinish_7                                           */
/* Description   | Reception Completion Interrupt                           */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
#if (CAN_RX_RXFINISH_USE_7 == CAN_USE)
void
Can_RxFinish_7( void )
{
    Can_rx_RxFinish( (uint8)CAN_CONTROLLER_7 );
}
#endif /* (CAN_RX_RXFINISH_USE_7 == CAN_USE) */


/****************************************************************************/
/* Function Name | Can_rx_ChkRxFinMbox                                      */
/* Description   | MBOX Reception Completion Confirmation                   */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 u1Controller                                       */
/*               | uint8 u1Kind                                             */
/* Return Value  | uint8                                                    */
/*               |   CAN_EXIST                                              */
/*               |   CAN_NONE                                               */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
uint8
Can_rx_ChkRxFinMbox( uint8 u1Controller, uint8 u1Kind )
{
    CanMsgType                      stMsg;
    volatile CanTbRegCANCFType *    ptMb;
    CanConst CanTbChRegType*        ptChReg;
    uint32                          u4Data[ CAN_DATA_ARYSIZE_4BYTE ];
    uint32                          u4IdVal;
    uint32                          u4CFSTSk;
    uint32                          u4CFIDk;
    uint32                          u4CFPTRk;
    uint32                          u4FDCSTSk;
    uint8                           u1Dlc;
    uint8                           u1Idx;
    uint8                           u1DataLength;
    uint8                           u1TRxFifoIdx;
    uint8                           u1MsgNum;
    uint8                           u1Count;
    uint8                           u1Mbox;
    uint8                           u1Ret;

    u1Ret = (uint8)CAN_NONE;

    ptChReg = &(Can_tb_stChReg[ u1Controller ]);

    if ( u1Kind == (uint8)CAN_INTERRUPT )
    {
        u1TRxFifoIdx = (uint8)CAN_CFTYPE_RX_INT;
    }
    else
    {
        u1TRxFifoIdx = (uint8)CAN_CFTYPE_RX_POLL;
    }

    ptChReg->ptu4CFSTSk[ u1TRxFifoIdx ] = CAN_u4CFSTSK_CFRXIF_CLR;

    u4CFSTSk = ptChReg->ptu4CFSTSk[ u1TRxFifoIdx ];

    u1MsgNum = (uint8)( ( u4CFSTSk & CAN_u4CFSTSK_CFMC_MSK ) >> CAN_SFT_8 );

    ptMb = &( ptChReg->ptstCF[ u1TRxFifoIdx ] );

    stMsg.ptData = (uint8 *)&( u4Data[ CAN_IDX0 ] );

    for ( u1Count = (uint8)0U; u1Count < u1MsgNum; u1Count++ )
    {
        u4CFIDk   = ptMb->u4IDReg;
        u4CFPTRk  = ptMb->u4PTRReg;
        u4FDCSTSk = ptMb->u4FDCSTSReg;

        if ( ( u4FDCSTSk & CAN_u4CFFDCSTSK_CFFDF_MSK ) == CAN_u4CFFDCSTSK_CFFDF_CANFD )
        {
            for ( u1Idx = (uint8)0U; u1Idx < (uint8)CAN_DATA_ARYSIZE_4BYTE; u1Idx++ )
            {
                u4Data[ u1Idx ] = ptMb->u4DFReg[ u1Idx ];
            }

            ptChReg->ptu4CFPCTRk[ u1TRxFifoIdx ] = CAN_u4CFPCTRK_CFPC_SET;

            u4IdVal      = ( ( u4CFIDk & CAN_u4CFIDK_EID_MSK ) | CAN_RX_ID_FDF_CANFD );

            u1Dlc        = (uint8)( ( u4CFPTRk & CAN_u4CFPTRK_CFDLC_MSK ) >> CAN_SFT_28 );

            u1DataLength = Can_rx_u1DataLengthVal[ u1Dlc ];
        }
        else
        {
            u4Data[ CAN_IDX0 ] = ptMb->u4DFReg[ CAN_IDX0 ];
            u4Data[ CAN_IDX1 ] = ptMb->u4DFReg[ CAN_IDX1 ];

            ptChReg->ptu4CFPCTRk[ u1TRxFifoIdx ] = CAN_u4CFPCTRK_CFPC_SET;

            u4IdVal      = u4CFIDk & CAN_u4CFIDK_EID_MSK;

            u1DataLength = (uint8)( ( u4CFPTRk & CAN_u4CFPTRK_CFDLC_MSK ) >> CAN_SFT_28 );
        }

        stMsg.u4Id     = u4IdVal;
        stMsg.u1Length = u1DataLength;

        u1Mbox = (uint8)( ( u4FDCSTSk & CAN_u4CFFDCSTSK_CFPTR_MSK ) >> CAN_SFT_16 );

        Can_rx_RxIndMbox( u1Controller, u1Mbox, &stMsg );

        u1Ret = (uint8)CAN_EXIST;
    }

    return ( u1Ret );
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Can_rx_RxFinish                                          */
/* Description   | Reception Completion Interrupt Common Process            */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 u1Controller                                       */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
#if (CAN_RX_RXFINISH_ANYCH_USE == CAN_USE)
static void
Can_rx_RxFinish( uint8 u1Controller )
{
    CanConst CanTbChRegType *      ptChReg;
    volatile uint32                u4DummyRead;
    uint32                         u4CmSTS;
    uint8                          u1RxResult;

    ptChReg = &( Can_tb_stChReg[ u1Controller ] );

    u4CmSTS = *( ptChReg->ptu4CmSTS );

    if( ( ( u4CmSTS & CAN_u4CMSTS_MODEALL_MSK ) == CAN_u4CMSTS_CMODE_COMM ) || ( ( *(ptChReg->ptu4CmERFL) & CAN_u4CMERFL_BOEF_MSK ) == CAN_u4CMERFL_BOEF_BUSOFF ) )
    {
        u1RxResult = Can_rx_ChkRxFinMbox( u1Controller, (uint8)CAN_INTERRUPT );

        if ( u1RxResult != (uint8)CAN_EXIST )
        {
            Can_fs_ResetInterrupt( u1Controller );
        }
    }
    else
    {
        Can_fs_DisableInterrupt( u1Controller );
    }

    u4DummyRead = *( Can_tb_stGlobalReg.ptu4GSTS );
    Can_tb_SYNCP();
}
#endif /* (CAN_RX_RXFINISH_ANYCH_USE == CAN_USE) */


#endif /* (CAN_CFG_RECEIVE == CAN_USE) */
#endif /* (CAN_CFG_CAN == CAN_USE) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-2-0         :2021/12/14                                              */
/*  v2-2-1         :2022/12/05                                              */
/*  v3-0-0         :2025/02/13                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
