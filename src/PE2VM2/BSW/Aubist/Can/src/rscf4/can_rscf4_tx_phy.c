/* can_rscf4_tx_phy_c_m10700_v3-0-0                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CAN/RSCF4/TX/PHYSICAL/CODE                                */
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
#include "../../cfg/rscf4/can_rscf4_cfg_ext.h"
#include "../../cfg/rscf4/can_rscf4_cfg.h"

#include <can/common/can_cv_can.h>
#include <can/common/can_memmap.h>
#include <can/rscf4/can_rscf4.h>
#include <can/rscf4/can_rscf4_cm_phy.h>

#if (CAN_CFG_CAN == CAN_USE)
#if (CAN_CFG_TRANSMIT == CAN_USE)
#include <can/rscf4/can_rscf4_tb_phy.h>
#include <can/rscf4/can_rscf4_tx.h>
#include <can/rscf4/can_rscf4_fs.h>
#include <can/rscf4/can_rscf4_st.h>


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define CAN_TX_CAN_DATA_SIZE            (  8U )

#define CAN_TX_CAN_DATA_WR_SIZE         (  2U )

#define CAN_TX_DLC_TBL_NUM              ( 65U )


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct
{
    uint32* ptTxData;
    uint32  u4Id;
    uint32  u4FrameInfo;
    uint8   u1Dlc;
} CanTxMsgInfoType;

typedef union
{
    uint32 u4Data[CAN_DATA_ARYSIZE_4BYTE];
    uint8  u1Data[CAN_DATA_ARYSIZE_1BYTE];
} CanTxDataType;


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
static void Can_tx_SetTxReg( uint8 u1Controller, uint8 u1Mbox, uint8 u1DataWriteSize, CanConstR CanTxMsgInfoType* ptTxMsgInfo );
#if (CAN_TX_TXFINISH_ANYCH_USE == CAN_USE)
static void Can_tx_TxFinish( uint8 u1Controller );
#endif /* (CAN_TX_TXFINISH_ANYCH_USE == CAN_USE) */


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
static CanConst uint8 Can_tx_u1DlcVal[ CAN_TX_DLC_TBL_NUM ]      = { (uint8)0x00U
                                                                    ,(uint8)0x01U ,(uint8)0x02U ,(uint8)0x03U ,(uint8)0x04U ,(uint8)0x05U ,(uint8)0x06U ,(uint8)0x07U ,(uint8)0x08U
                                                                    ,(uint8)0x09U ,(uint8)0x09U ,(uint8)0x09U ,(uint8)0x09U ,(uint8)0x0AU ,(uint8)0x0AU ,(uint8)0x0AU ,(uint8)0x0AU
                                                                    ,(uint8)0x0BU ,(uint8)0x0BU ,(uint8)0x0BU ,(uint8)0x0BU ,(uint8)0x0CU ,(uint8)0x0CU ,(uint8)0x0CU ,(uint8)0x0CU
                                                                    ,(uint8)0x0DU ,(uint8)0x0DU ,(uint8)0x0DU ,(uint8)0x0DU ,(uint8)0x0DU ,(uint8)0x0DU ,(uint8)0x0DU ,(uint8)0x0DU
                                                                    ,(uint8)0x0EU ,(uint8)0x0EU ,(uint8)0x0EU ,(uint8)0x0EU ,(uint8)0x0EU ,(uint8)0x0EU ,(uint8)0x0EU ,(uint8)0x0EU
                                                                    ,(uint8)0x0EU ,(uint8)0x0EU ,(uint8)0x0EU ,(uint8)0x0EU ,(uint8)0x0EU ,(uint8)0x0EU ,(uint8)0x0EU ,(uint8)0x0EU
                                                                    ,(uint8)0x0FU ,(uint8)0x0FU ,(uint8)0x0FU ,(uint8)0x0FU ,(uint8)0x0FU ,(uint8)0x0FU ,(uint8)0x0FU ,(uint8)0x0FU
                                                                    ,(uint8)0x0FU ,(uint8)0x0FU ,(uint8)0x0FU ,(uint8)0x0FU ,(uint8)0x0FU ,(uint8)0x0FU ,(uint8)0x0FU ,(uint8)0x0FU };

static CanConst uint8 Can_tx_u1DataSize[ CAN_TX_DLC_TBL_NUM ]    = { (uint8)0U
                                                                    ,(uint8)4U    ,(uint8)4U    ,(uint8)4U    ,(uint8)4U    ,(uint8)8U    ,(uint8)8U    ,(uint8)8U    ,(uint8)8U
                                                                    ,(uint8)12U   ,(uint8)12U   ,(uint8)12U   ,(uint8)12U   ,(uint8)16U   ,(uint8)16U   ,(uint8)16U   ,(uint8)16U
                                                                    ,(uint8)20U   ,(uint8)20U   ,(uint8)20U   ,(uint8)20U   ,(uint8)24U   ,(uint8)24U   ,(uint8)24U   ,(uint8)24U
                                                                    ,(uint8)28U   ,(uint8)28U   ,(uint8)28U   ,(uint8)28U   ,(uint8)32U   ,(uint8)32U   ,(uint8)32U   ,(uint8)32U
                                                                    ,(uint8)36U   ,(uint8)36U   ,(uint8)36U   ,(uint8)36U   ,(uint8)40U   ,(uint8)40U   ,(uint8)40U   ,(uint8)40U
                                                                    ,(uint8)44U   ,(uint8)44U   ,(uint8)44U   ,(uint8)44U   ,(uint8)48U   ,(uint8)48U   ,(uint8)48U   ,(uint8)48U
                                                                    ,(uint8)52U   ,(uint8)52U   ,(uint8)52U   ,(uint8)52U   ,(uint8)56U   ,(uint8)56U   ,(uint8)56U   ,(uint8)56U
                                                                    ,(uint8)60U   ,(uint8)60U   ,(uint8)60U   ,(uint8)60U   ,(uint8)64U   ,(uint8)64U   ,(uint8)64U   ,(uint8)64U   };


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Can_tx_TxReq_CanFrame                                    */
/* Description   | Classical Can Frame Transmission Request                 */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 u1Controller                                       */
/*               | uint8 u1Mbox                                             */
/*               | CanConstR CanMsgType* ptMsg                              */
/*               |   uint8* ptData                                          */
/*               |   uint32 u4Id;                                           */
/*               |   uint8  u1Length                                        */
/* Return Value  | uint8                                                    */
/*               |   CAN_PROC_OK                                            */
/*               |   CAN_PROC_BUSY                                          */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
uint8
Can_tx_TxReq_CanFrame( uint8 u1Controller, uint8 u1Mbox, CanConstR CanMsgType* ptMsg )
{
    CanTxMsgInfoType                  stTxMsgInfo;
    CanConst CanTbChRegType *         ptChReg;
    CanTxDataType                     unDataAry;
    uint32                            u4IdVal;
    uint32                            u4FrameInfoVal;
    uint8                             u1DataWriteSize;
    uint8                             u1DataSize;
    uint8                             u1TMSTSp;
    uint8                             u1DataIdx;
    uint8                             u1Ret;

    u1Ret = (uint8)CAN_PROC_BUSY;

    ptChReg = &( Can_tb_stChReg[ u1Controller ] );

    u1TMSTSp = ptChReg->ptu1TMSTSp[ u1Mbox ];

    if ( ( u1TMSTSp & CAN_u1TMSTSP_REQ_RES_MSK ) == CAN_u1TMSTSP_TXFREE )
    {
        u4IdVal = ptMsg->u4Id;
        if ( ( u4IdVal & CAN_u4BIT31 ) == CAN_u4BIT_NONE )
        {
            u4IdVal &= CAN_u4TMIDP_SID_MSK;
        }
        else
        {
            u4IdVal &= CAN_u4TMIDP_EID_MSK;
        }

        u1DataSize = (uint8)CAN_TX_CAN_DATA_SIZE;
        for ( u1DataIdx = (uint8)0U; u1DataIdx < u1DataSize; u1DataIdx++ )
        {
            unDataAry.u1Data[ u1DataIdx ] = ptMsg->ptData[ u1DataIdx ];
        }

        u4FrameInfoVal = CAN_u4TMFDCTRP_FDF_CAN | CAN_u4TMFDCTRP_BRS_OFF | CAN_u4TMFDCTRP_ESI_E_ACT;

        u1DataWriteSize = (uint8)CAN_TX_CAN_DATA_WR_SIZE;

        stTxMsgInfo.ptTxData    = &(unDataAry.u4Data[ CAN_IDX0 ]);
        stTxMsgInfo.u4Id        = u4IdVal;
        stTxMsgInfo.u4FrameInfo = u4FrameInfoVal;
        stTxMsgInfo.u1Dlc       = ptMsg->u1Length;

        Can_tx_SetTxReg( u1Controller, u1Mbox, u1DataWriteSize ,&stTxMsgInfo );

        u1Ret = (uint8)CAN_PROC_OK;
    }

    return ( u1Ret );
}


/****************************************************************************/
/* Function Name | Can_tx_TxReq_CanFdFrame                                  */
/* Description   | Can FD Frame Transmission Request                        */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 u1Controller                                       */
/*               | uint8 u1Mbox                                             */
/*               | CanConstR CanMsgType* ptMsg                              */
/*               |   uint8* ptData                                          */
/*               |   uint32 u4Id;                                           */
/*               |   uint8  u1Length                                        */
/* Return Value  | uint8                                                    */
/*               |   CAN_PROC_OK                                            */
/*               |   CAN_PROC_NG                                            */
/*               |   CAN_PROC_BUSY                                          */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
uint8
Can_tx_TxReq_CanFdFrame( uint8 u1Controller, uint8 u1Mbox, CanConstR CanMsgType* ptMsg )
{
    CanTxMsgInfoType                  stTxMsgInfo;
    CanConst CanTbChRegType *         ptChReg;
    CanTxDataType                     unDataAry;
    uint32                            u4IdVal;
    uint32                            u4FrameInfoVal;
    uint8                             u1DlcVal;
    uint8                             u1CheckData;
    uint8                             u1CheckDataLo;
    uint8                             u1CheckDataHi;
    uint8                             u1BRSUse;
    uint8                             u1DataLength;
    uint8                             u1DataWriteSize;
    uint8                             u1DataSize;
    uint8                             u1TMSTSp;
    uint8                             u1DataIdx;
    uint8                             u1Ret;

    u1Ret = (uint8)CAN_PROC_NG;

    if ( Can_tb_stCtrlInfo[ u1Controller ].u1CtrlOpeMode == (uint8)CAN_OPEMODE_CANFD )
    {
        ptChReg = &( Can_tb_stChReg[ u1Controller ] );

        u1BRSUse    = Can_st_u1BRSUse[ u1Controller ];
        u1CheckDataLo = (uint8)( u1BRSUse & (uint8)CAN_RAMCHK_MASK_LOWERHALFBYTE );
        u1CheckDataHi = (uint8)( u1BRSUse >> CAN_SFT_4 );
        u1CheckData = u1CheckDataLo + u1CheckDataHi;
        if( u1CheckData == (uint8)CAN_RAMCHK_VALUE_LOWERHALFBYTE )
        {
            u1Ret = (uint8)CAN_PROC_BUSY;

            u1TMSTSp = ptChReg->ptu1TMSTSp[ u1Mbox ];

            if ( ( u1TMSTSp & CAN_u1TMSTSP_REQ_RES_MSK ) == CAN_u1TMSTSP_TXFREE )
            {
                u4IdVal = ptMsg->u4Id;
                if ( ( u4IdVal & CAN_u4BIT31 ) == CAN_u4BIT_NONE )
                {
                    u4IdVal &= CAN_u4TMIDP_SID_MSK;
                }
                else
                {
                    u4IdVal &= CAN_u4TMIDP_EID_MSK;
                }

                u1DataLength = ptMsg->u1Length;

                u1DlcVal = Can_tx_u1DlcVal[ u1DataLength ];

                u1DataSize = Can_tx_u1DataSize[ u1DataLength ];
                for ( u1DataIdx = (uint8)0U; u1DataIdx < u1DataSize; u1DataIdx++ )
                {
                    unDataAry.u1Data[ u1DataIdx ] = ptMsg->ptData[ u1DataIdx ];
                }

                if ( u1BRSUse == (uint8)CAN_ST_BRS_USE )
                {
                    u4FrameInfoVal = CAN_u4TMFDCTRP_FDF_CANFD | CAN_u4TMFDCTRP_BRS_ON | Can_tb_stSetRSCANReg[ u1Controller ].u4TMFDCTRpConf;
                }
                else
                {
                    u4FrameInfoVal = CAN_u4TMFDCTRP_FDF_CANFD | CAN_u4TMFDCTRP_BRS_OFF | Can_tb_stSetRSCANReg[ u1Controller ].u4TMFDCTRpConf;
                }

                u1DataWriteSize = u1DataSize >> CAN_SFT_2;

                stTxMsgInfo.ptTxData    = &( unDataAry.u4Data[ CAN_IDX0 ] );
                stTxMsgInfo.u4Id        = u4IdVal;
                stTxMsgInfo.u4FrameInfo = u4FrameInfoVal;
                stTxMsgInfo.u1Dlc       = u1DlcVal;

                Can_tx_SetTxReg( u1Controller, u1Mbox, u1DataWriteSize ,&stTxMsgInfo );

                u1Ret = (uint8)CAN_PROC_OK;
            }
        }
    }

    return ( u1Ret );
}


/****************************************************************************/
/* Function Name | Can_tx_TxAbt                                             */
/* Description   | MBOX Transmission Abort Request                          */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 u1Controller                                       */
/*               | uint8 u1Mbox                                             */
/* Return Value  | uint8                                                    */
/*               |   CAN_PROC_OK                                            */
/*               |   CAN_PROC_BUSY                                          */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
#if (CAN_CFG_ABORTSEND == CAN_USE)
uint8
Can_tx_TxAbt( uint8 u1Controller, uint8 u1Mbox )
{
    CanConst CanTbChRegType *       ptChReg;
    uint8                           u1TMSTSp;
    uint8                           u1Ret;

    u1Ret = (uint8)CAN_PROC_BUSY;

    ptChReg = &( Can_tb_stChReg[ u1Controller ] );

    ptChReg->ptu1TMCp[ u1Mbox ] = CAN_u1TMCP_TMTAR_SET;

    u1TMSTSp = ptChReg->ptu1TMSTSp[ u1Mbox ];

    if ( ( u1TMSTSp & CAN_u1TMSTSP_REQ_RES_MSK ) == CAN_u1TMSTSP_ABORTED )
    {
        ptChReg->ptu1TMSTSp[ u1Mbox ] = CAN_u1TMSTSP_TMTRF_CLR;

        u1Ret = (uint8)CAN_PROC_OK;
    }

    return ( u1Ret );
}
#endif /* (CAN_CFG_ABORTSEND == CAN_USE) */


/****************************************************************************/
/* Function Name | Can_tx_TxAbtAll                                          */
/* Description   | All MBOX Transmission Abort Request                      */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 u1Controller                                       */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
void
Can_tx_TxAbtAll( uint8 u1Controller )
{
    CanConst CanTbChRegType *       ptChReg;
    uint8                           u1MboxNum;
    uint8                           u1Mbox;

    ptChReg = &Can_tb_stChReg[ u1Controller ];

    u1MboxNum = Can_tb_stMbNum[ u1Controller ].u1TxMbNum;

    for ( u1Mbox = (uint8)0U; u1Mbox < u1MboxNum; u1Mbox++ )
    {
#if (CAN_CFG_TXBUF_NUM == 48U)
        if ( ( u1Mbox < (uint8)CAN_MB016 )
        ||   ( u1Mbox > (uint8)CAN_MB031 ) )
#endif /* (CAN_CFG_TXBUF_NUM == 48U) */
        {
            ptChReg->ptu1TMCp[ u1Mbox ] = CAN_u1TMCP_TMTAR_SET;
        }
    }
}


/****************************************************************************/
/* Function Name | Can_TxFinish_0                                           */
/* Description   | Transmission Completion Interrupt                        */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
#if (CAN_TX_TXFINISH_USE_0 == CAN_USE)
void
Can_TxFinish_0( void )
{
    Can_tx_TxFinish( (uint8)CAN_CONTROLLER_0 );
}
#endif /* (CAN_TX_TXFINISH_USE_0 == CAN_USE) */


/****************************************************************************/
/* Function Name | Can_TxFinish_1                                           */
/* Description   | Transmission Completion Interrupt                        */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
#if (CAN_TX_TXFINISH_USE_1 == CAN_USE)
void
Can_TxFinish_1( void )
{
    Can_tx_TxFinish( (uint8)CAN_CONTROLLER_1 );
}
#endif /* (CAN_TX_TXFINISH_USE_1 == CAN_USE) */


/****************************************************************************/
/* Function Name | Can_TxFinish_2                                           */
/* Description   | Transmission Completion Interrupt                        */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
#if (CAN_TX_TXFINISH_USE_2 == CAN_USE)
void
Can_TxFinish_2( void )
{
    Can_tx_TxFinish( (uint8)CAN_CONTROLLER_2 );
}
#endif /* (CAN_TX_TXFINISH_USE_2 == CAN_USE) */


/****************************************************************************/
/* Function Name | Can_TxFinish_3                                           */
/* Description   | Transmission Completion Interrupt                        */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
#if (CAN_TX_TXFINISH_USE_3 == CAN_USE)
void
Can_TxFinish_3( void )
{
    Can_tx_TxFinish( (uint8)CAN_CONTROLLER_3 );
}
#endif /* (CAN_TX_TXFINISH_USE_3 == CAN_USE) */


/****************************************************************************/
/* Function Name | Can_TxFinish_4                                           */
/* Description   | Transmission Completion Interrupt                        */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
#if (CAN_TX_TXFINISH_USE_4 == CAN_USE)
void
Can_TxFinish_4( void )
{
    Can_tx_TxFinish( (uint8)CAN_CONTROLLER_4 );
}
#endif /* (CAN_TX_TXFINISH_USE_4 == CAN_USE) */


/****************************************************************************/
/* Function Name | Can_TxFinish_5                                           */
/* Description   | Transmission Completion Interrupt                        */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
#if (CAN_TX_TXFINISH_USE_5 == CAN_USE)
void
Can_TxFinish_5( void )
{
    Can_tx_TxFinish( (uint8)CAN_CONTROLLER_5 );
}
#endif /* (CAN_TX_TXFINISH_USE_5 == CAN_USE) */


/****************************************************************************/
/* Function Name | Can_TxFinish_6                                           */
/* Description   | Transmission Completion Interrupt                        */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
#if (CAN_TX_TXFINISH_USE_6 == CAN_USE)
void
Can_TxFinish_6( void )
{
    Can_tx_TxFinish( (uint8)CAN_CONTROLLER_6 );
}
#endif /* (CAN_TX_TXFINISH_USE_6 == CAN_USE) */


/****************************************************************************/
/* Function Name | Can_TxFinish_7                                           */
/* Description   | Transmission Completion Interrupt                        */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
#if (CAN_TX_TXFINISH_USE_7 == CAN_USE)
void
Can_TxFinish_7( void )
{
    Can_tx_TxFinish( (uint8)CAN_CONTROLLER_7 );
}
#endif /* (CAN_TX_TXFINISH_USE_7 == CAN_USE) */


/****************************************************************************/
/* Function Name | Can_tx_ChkTxFinMbox                                      */
/* Description   | MBOX Transmission Completion Confirmation                */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 u1Controller                                       */
/*               | uint8 u1Kind                                             */
/* Return Value  | uint8                                                    */
/*               |   CAN_EXIST                                              */
/*               |   CAN_NONE                                               */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
uint8
Can_tx_ChkTxFinMbox( uint8 u1Controller, uint8 u1Kind )
{
    CanConst CanTbChRegType *       ptChReg;
    uint32                          u4TMTCSTSyLo;
    uint32                          u4TMTCSTSyHi;
    uint32                          u4TmpTxFinFlag;
    uint32                          u4TmpTxFinFlagLo;
    uint32                          u4TmpTxFinFlagHi;
    uint32                          u4MboxBit;
    uint32                          u4TxBitLo;
    uint32                          u4TxBitHi;
    uint8                           u1MboxNum;
    uint8                           u1Mbox;
    uint8                           u1Ret;

    u1Ret = (uint8)CAN_NONE;

    ptChReg = &( Can_tb_stChReg[ u1Controller ] );

    if ( u1Kind == (uint8)CAN_INTERRUPT )
    {
        u4TxBitLo = Can_tb_stTxMbBit[ u1Controller ].u4TxIntrBit[CAN_IDX0];
        u4TxBitHi = Can_tb_stTxMbBit[ u1Controller ].u4TxIntrBit[CAN_IDX1];
    }
    else
    {
        u4TxBitLo = Can_tb_stTxMbBit[ u1Controller ].u4TxPollBit[CAN_IDX0];
        u4TxBitHi = Can_tb_stTxMbBit[ u1Controller ].u4TxPollBit[CAN_IDX1];
    }

    u4TMTCSTSyLo = ptChReg->ptu4TMTCSTSy[CAN_IDX0];
    u4TMTCSTSyHi = ptChReg->ptu4TMTCSTSy[CAN_IDX1];

    u4TmpTxFinFlagLo = u4TMTCSTSyLo & u4TxBitLo;
    u4TmpTxFinFlagHi = u4TMTCSTSyHi & u4TxBitHi;

    if ( ( u4TmpTxFinFlagLo != CAN_u4BIT_NONE )
    ||   ( u4TmpTxFinFlagHi != CAN_u4BIT_NONE ) )
    {
        u1Ret = (uint8)CAN_EXIST;

        u1MboxNum = Can_tb_stMbNum[ u1Controller ].u1TxMbNum;

        for ( u1Mbox = (uint8)0U; u1Mbox < u1MboxNum; u1Mbox++ )
        {
            if ( u1Mbox < (uint8)CAN_NUM_BUF_SND_PER_REG )
            {
                u4TmpTxFinFlag = u4TmpTxFinFlagLo;
            }
            else
            {
                u4TmpTxFinFlag = u4TmpTxFinFlagHi;
            }

            u4MboxBit = (uint32)(CAN_u4BIT0 << ( u1Mbox & (uint8)CAN_MBSFT_MSK ));

            if ( ( u4TmpTxFinFlag & u4MboxBit ) != CAN_u4BIT_NONE )
            {
                ptChReg->ptu1TMSTSp[ u1Mbox ] = CAN_u1TMSTSP_TMTRF_CLR;

                Can_tx_TxConfMbox( u1Controller, u1Mbox );
            }
        }
    }

    return ( u1Ret );
}


/****************************************************************************/
/* Function Name | Can_tx_ChkTxAbtMbox                                      */
/* Description   | MBOX Transmission Abort Completion Confirmation          */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 u1Controller                                       */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
#if (CAN_CFG_ABORTSEND == CAN_USE)
void
Can_tx_ChkTxAbtMbox( uint8 u1Controller )
{
    CanConst CanTbChRegType *       ptChReg;
    uint32                          u4TMTASTSyLo;
    uint32                          u4TMTASTSyHi;
    uint32                          u4TmpTxAbtFlag;
    uint32                          u4TmpTxAbtFlagLo;
    uint32                          u4TmpTxAbtFlagHi;
    uint32                          u4MboxBit;
    uint32                          u4TxBitLo;
    uint32                          u4TxBitHi;
    uint8                           u1MboxNum;
    uint8                           u1Mbox;

    ptChReg = &( Can_tb_stChReg[ u1Controller ] );

    u4TxBitLo = ( Can_tb_stTxMbBit[ u1Controller ].u4TxIntrBit[CAN_IDX0]
                | Can_tb_stTxMbBit[ u1Controller ].u4TxPollBit[CAN_IDX0] );

    u4TxBitHi = ( Can_tb_stTxMbBit[ u1Controller ].u4TxIntrBit[CAN_IDX1]
                | Can_tb_stTxMbBit[ u1Controller ].u4TxPollBit[CAN_IDX1] );

    u4TMTASTSyLo = ptChReg->ptu4TMTASTSy[CAN_IDX0];
    u4TMTASTSyHi = ptChReg->ptu4TMTASTSy[CAN_IDX1];

    u4TmpTxAbtFlagLo = u4TMTASTSyLo & u4TxBitLo;
    u4TmpTxAbtFlagHi = u4TMTASTSyHi & u4TxBitHi;

    if ( ( u4TmpTxAbtFlagLo != CAN_u4BIT_NONE )
    ||   ( u4TmpTxAbtFlagHi != CAN_u4BIT_NONE ) )
    {
        u1MboxNum = Can_tb_stMbNum[ u1Controller ].u1TxMbNum;

        for ( u1Mbox = (uint8)0U; u1Mbox < u1MboxNum; u1Mbox++ )
        {
            if ( u1Mbox < (uint8)CAN_NUM_BUF_SND_PER_REG )
            {
                u4TmpTxAbtFlag = u4TmpTxAbtFlagLo;
            }
            else
            {
                u4TmpTxAbtFlag = u4TmpTxAbtFlagHi;
            }

            u4MboxBit = (uint32)(CAN_u4BIT0 << ( u1Mbox & (uint8)CAN_MBSFT_MSK ));

            if ( ( u4TmpTxAbtFlag & u4MboxBit ) != CAN_u4BIT_NONE )
            {
                ptChReg->ptu1TMSTSp[ u1Mbox ] = CAN_u1TMSTSP_TMTRF_CLR;

                Can_tx_TxConfMbox( u1Controller, u1Mbox );
            }
        }
    }
}
#endif /* (CAN_CFG_ABORTSEND == CAN_USE) */


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Can_tx_SetTxReg                                          */
/* Description   | Transmission Buffer Register Set                         */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 u1Controller                                       */
/*               | uint8 u1Mbox                                             */
/*               | uint8 u1DataWriteSize                                    */
/*               | CanConstR CanTxMsgInfoType* ptTxMsgInfo                  */
/*               |   uint32* ptTxData                                       */
/*               |   uint32  u4Id;                                          */
/*               |   uint32  u4FrameInfo                                    */
/*               |   uint8   u1Dlc;                                         */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
static void
Can_tx_SetTxReg( uint8 u1Controller, uint8 u1Mbox, uint8 u1DataWriteSize, CanConstR CanTxMsgInfoType* ptTxMsgInfo )
{
    CanConst CanTbChRegType *         ptChReg;
    volatile CanTbRegCANTMType *      ptMb;
    uint8                             u1Idx;

    ptChReg = &( Can_tb_stChReg[ u1Controller ] );

    ptMb = &( ptChReg->ptstTM[ u1Mbox ] );

    ptMb->u4IDReg    = ptTxMsgInfo->u4Id;

    ptMb->u4PTRReg   = (uint32)ptTxMsgInfo->u1Dlc << CAN_SFT_28;

    ptMb->u4FDCTRReg = ptTxMsgInfo->u4FrameInfo;

    for ( u1Idx = (uint8)0U; u1Idx < u1DataWriteSize; u1Idx++ )
    {
        ptMb->u4DFReg[ u1Idx ] = ptTxMsgInfo->ptTxData[ u1Idx ];
    }

    ptChReg->ptu1TMCp[ u1Mbox ] = CAN_u1TMCP_TMTR_SET;
}


/****************************************************************************/
/* Function Name | Can_tx_TxFinish                                          */
/* Description   | Transmission Completion Interrupt Common Process         */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 u1Controller                                       */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
#if (CAN_TX_TXFINISH_ANYCH_USE == CAN_USE)
static void
Can_tx_TxFinish( uint8 u1Controller )
{
    CanConst CanTbChRegType *      ptChReg;
    volatile uint32                u4DummyRead;
    uint32                         u4CmSTS;
    uint8                          u1TxResult;

    ptChReg = &( Can_tb_stChReg[ u1Controller ] );

    u4CmSTS = *( ptChReg->ptu4CmSTS );

    if( ( ( u4CmSTS & CAN_u4CMSTS_MODEALL_MSK ) == CAN_u4CMSTS_CMODE_COMM ) || ( ( *(ptChReg->ptu4CmERFL) & CAN_u4CMERFL_BOEF_MSK ) == CAN_u4CMERFL_BOEF_BUSOFF ) )
    {
        u1TxResult = Can_tx_ChkTxFinMbox( u1Controller, (uint8)CAN_INTERRUPT );

        if ( u1TxResult != (uint8)CAN_EXIST )
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
#endif /* (CAN_TX_TXFINISH_ANYCH_USE == CAN_USE) */


#endif /* (CAN_CFG_TRANSMIT == CAN_USE) */
#endif /* (CAN_CFG_CAN == CAN_USE) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-2-0         :2021/12/14                                              */
/*  v2-2-1         :2022/12/05                                              */
/*  v3-0-0         :2025/02/13                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
