/* can_rscf41_st_phy_c_m10700_v2-2-2                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CAN/RSCF41/ST/PHYSICAL/CODE                               */
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
#include "../../cfg/rscf41/can_rscf41_cfg_ext.h"
#include "../../cfg/rscf41/can_rscf41_cfg.h"

#include <can/common/can_cv_can.h>

#if (CAN_CFG_CAN == CAN_USE)
#include <can/rscf41/can_rscf41.h>
#include <can/rscf41/can_rscf41_cm_phy.h>
#include <can/common/can_memmap.h>
#include <can/rscf41/can_rscf41_tb_phy.h>
#include <can/rscf41/can_rscf41_fs.h>
#include <can/rscf41/can_rscf41_st.h>

#if (CAN_CFG_TRANSMIT == CAN_USE)
#include <can/rscf41/can_rscf41_tx.h>
#endif /* (CAN_CFG_TRANSMIT == CAN_USE) */


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
static void  Can_st_GlobalMode_Reset2Stop( void );
static void  Can_st_GlobalMode_Reset2Comm( void );
static void  Can_st_ChannelMode_Any2Reset( uint8 u1Controller );
static void  Can_st_ChannelMode_Reset2Stop( uint8 u1Controller );
static void  Can_st_ChannelMode_Reset2Comm( uint8 u1Controller );
static uint8 Can_st_GlobalRegCheck( uint8 u1Controller );
static void  Can_st_InitGlobalReg( void );
static void  Can_st_InitChannelReg( uint8 u1Controller );
static void  Can_st_SetGlobalReg( void );
static void  Can_st_SetChannelReg( uint8 u1Controller );
static void  Can_st_StopGlobal( void );
static uint8 Can_st_StopChannel( uint8 u1Controller );
static void  Can_st_StartGlobal( void );
static uint8 Can_st_StartChannel( uint8 u1Controller );
static uint8 Can_st_ResetGlobal( void );
static uint8 Can_st_ResetChannel( uint8 u1Controller );
static void  Can_st_SetRxRule( void );
static void  Can_st_PhyInit( void );


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
uint8 Can_st_u1BRSUse[ CAN_CFG_CONTROLLERNUM_MAX ];


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Can_st_InitReg                                           */
/* Description   | Can Register Set for Initialization                      */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | uint8                                                    */
/*               |   CAN_PROC_OK                                            */
/*               |   CAN_PROC_BUSY                                          */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
uint8
Can_st_InitReg( void )
{
    CanConst CanTbChRegType *           ptChReg;
    uint32                              u4GSTS;
    uint32                              u4WaitCount;
    uint32                              u4InitCycleMax;
    uint8                               u1Controller;
    uint8                               u1ControllerUse;
    uint8                               u1CtrlNum;
    uint8                               u1Ret;

    u1Ret = (uint8)CAN_PROC_BUSY;

    Can_fs_PhyInit();
    Can_st_PhyInit();

    u4GSTS         = CAN_u4GSTS_GRAMINIT;
    u4InitCycleMax = Can_tb_u4RAMInitCycleMax;
    for ( u4WaitCount = 0UL; ( u4WaitCount < u4InitCycleMax ) && ( ( u4GSTS & CAN_u4GSTS_GRAMINIT_MSK ) == CAN_u4GSTS_GRAMINIT ); u4WaitCount++ )
    {
        u4GSTS = *(Can_tb_stGlobalReg.ptu4GSTS);
    }

    if ( ( u4GSTS & CAN_u4GSTS_GRAMINIT_MSK ) == CAN_u4BIT_NONE )
    {
        Can_st_GlobalMode_Any2Reset();

        u4GSTS = *(Can_tb_stGlobalReg.ptu4GSTS);
        if ( ( u4GSTS & CAN_u4GSTS_MODEALL_MSK ) == CAN_u4GSTS_GMODE_RESET )
        {
            Can_st_InitGlobalReg();

            u1CtrlNum = Can_tb_u1CtrlNum;
            for ( u1Controller = (uint8)0U; u1Controller < u1CtrlNum; u1Controller++ )
            {
                if ( Can_tb_stCtrlInfo[ u1Controller ].u1CtrlAct == (uint8)CAN_TRUE )
                {
                    Can_st_ChannelMode_Any2Reset( u1Controller );

                    ptChReg = &Can_tb_stChReg[ u1Controller ];
                    if ( ( *(ptChReg->ptu4CmSTS) & CAN_u4CMSTS_MODEALL_MSK ) == CAN_u4CMSTS_CMODE_RESET )
                    {
                        Can_st_InitChannelReg( u1Controller );
                    }

                    u1ControllerUse = Can_tb_stCtrlInfo[ u1Controller ].u1CtrlUse;
                    if ( u1ControllerUse != (uint8)CAN_USE )
                    {
                        Can_st_ChannelMode_Reset2Stop( u1Controller );
                    }
                }
            }

            Can_st_SetGlobalReg();

            u1Ret = (uint8)CAN_PROC_OK;
        }
    }

    return ( u1Ret );
}


/****************************************************************************/
/* Function Name | Can_st_SetControl                                        */
/* Description   | Controller Individual Register Set                       */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 u1Controller                                       */
/* Return Value  | uint8                                                    */
/*               |   CAN_PROC_OK                                            */
/*               |   CAN_PROC_BUSY                                          */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
uint8
Can_st_SetControl( uint8 u1Controller )
{
    CanConst CanTbChRegType *           ptChReg;
    uint32                              u4GSTS;
    uint8                               u1Ret;

    u1Ret = (uint8)CAN_PROC_BUSY;

    u4GSTS = *(Can_tb_stGlobalReg.ptu4GSTS);
    if ( ( ( u4GSTS & CAN_u4GSTS_MODEALL_MSK ) == CAN_u4GSTS_GMODE_RESET )
    ||   ( ( u4GSTS & CAN_u4GSTS_MODEALL_MSK ) == CAN_u4GSTS_GMODE_COMM  ) )
    {
        ptChReg = &Can_tb_stChReg[ u1Controller ];
        if ( ( *(ptChReg->ptu4CmSTS) & CAN_u4CMSTS_MODEALL_MSK ) == CAN_u4CMSTS_CMODE_RESET )
        {
            Can_st_u1BRSUse[ u1Controller ] = Can_tb_u1BRSInitConf[ u1Controller ];

            Can_st_SetChannelReg( u1Controller );

            u1Ret = (uint8)CAN_PROC_OK;
        }
    }

    return ( u1Ret );
}


/****************************************************************************/
/* Function Name | Can_st_Start                                             */
/* Description   | Controller Communication Start                           */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 u1Controller                                       */
/* Return Value  | uint8                                                    */
/*               |   CAN_PROC_OK                                            */
/*               |   CAN_PROC_BUSY                                          */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
uint8
Can_st_Start( uint8 u1Controller )
{
    uint32    u4GSTS;
    uint8     u1Ret;

    u1Ret = (uint8)CAN_PROC_BUSY;

    u4GSTS = *(Can_tb_stGlobalReg.ptu4GSTS);
    if ( ( u4GSTS & CAN_u4GSTS_MODEALL_MSK ) == CAN_u4GSTS_GMODE_RESET )
    {
        Can_st_StartGlobal();
    }

    u4GSTS = *(Can_tb_stGlobalReg.ptu4GSTS);
    if ( ( u4GSTS & CAN_u4GSTS_MODEALL_MSK ) == CAN_u4GSTS_GMODE_COMM )
    {
        u1Ret = Can_st_StartChannel( u1Controller );
    }

    return ( u1Ret );
}


/****************************************************************************/
/* Function Name | Can_st_Stop                                              */
/* Description   | Controller Communication Stop                            */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 u1Controller                                       */
/* Return Value  | uint8                                                    */
/*               |   CAN_PROC_OK                                            */
/*               |   CAN_PROC_BUSY                                          */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
uint8
Can_st_Stop( uint8 u1Controller )
{
#if (CAN_CFG_TRANSMIT == CAN_USE)
    CanConst CanTbChRegType *           ptChReg;
    CanConst CanTbSetRSCANRegType *     ptSetRSCANReg;
    CanConst CanTbTxMbBitType *         ptTxMbBit;
    uint32                              u4TxMbUseBitMaskLo;
    uint32                              u4TxMbUseBitMaskHi;
    uint32                              u4TMTRSTSLo;
    uint32                              u4TMTRSTSHi;
#endif /* (CAN_CFG_TRANSMIT == CAN_USE) */
    uint8                               u1Ret;

#if (CAN_CFG_TRANSMIT == CAN_USE)
    u1Ret = (uint8)CAN_PROC_BUSY;

    ptChReg = &Can_tb_stChReg[ u1Controller ];
    if ( ( *(ptChReg->ptu4CmSTS) & CAN_u4CMSTS_MODEALL_MSK ) == CAN_u4CMSTS_CMODE_COMM )
    {
        Can_tx_TxAbtAll( u1Controller );

        ptTxMbBit          = &Can_tb_stTxMbBit[ u1Controller ];
        u4TxMbUseBitMaskLo = ( ptTxMbBit->u4TxIntrBit[CAN_IDX0] | ptTxMbBit->u4TxPollBit[CAN_IDX0] );
        u4TxMbUseBitMaskHi = ( ptTxMbBit->u4TxIntrBit[CAN_IDX1] | ptTxMbBit->u4TxPollBit[CAN_IDX1] );
        u4TMTRSTSLo        = ptChReg->ptu4TMTRSTS[CAN_IDX0];
        u4TMTRSTSHi        = ptChReg->ptu4TMTRSTS[CAN_IDX1];
        if ( ( ( u4TMTRSTSLo & u4TxMbUseBitMaskLo ) == CAN_u4BIT_NONE )
        &&   ( ( u4TMTRSTSHi & u4TxMbUseBitMaskHi ) == CAN_u4BIT_NONE ) )
        {
            u1Ret = Can_st_StopChannel( u1Controller );
        }
        else
        {
            ptSetRSCANReg = &Can_tb_stSetRSCANReg[ u1Controller ];

            ptChReg->ptu4CFCC[ CAN_TRX_FIFO_0 ] = ptSetRSCANReg->u4CFCC0Conf & CAN_u4CFCC_CFE_NOUSE;
            ptChReg->ptu4CFCC[ CAN_TRX_FIFO_1 ] = ptSetRSCANReg->u4CFCC1Conf & CAN_u4CFCC_CFE_NOUSE;
            ptChReg->ptu4CFCC[ CAN_TRX_FIFO_0 ] = ptSetRSCANReg->u4CFCC0Conf & CAN_u4CFCC_CFRXIE_DIS & CAN_u4CFCC_CFE_NOUSE;
            ptChReg->ptu4CFCC[ CAN_TRX_FIFO_1 ] = ptSetRSCANReg->u4CFCC1Conf & CAN_u4CFCC_CFRXIE_DIS & CAN_u4CFCC_CFE_NOUSE;

            ptChReg->ptu4CFSTS[ CAN_TRX_FIFO_0 ] = CAN_u4CFSTS_CLEARALL;
            ptChReg->ptu4CFSTS[ CAN_TRX_FIFO_1 ] = CAN_u4CFSTS_CLEARALL;
        }
    }
    else
    {
        u1Ret = Can_st_StopChannel( u1Controller );
    }
#else /* (CAN_CFG_TRANSMIT != CAN_USE) */
    u1Ret = Can_st_StopChannel( u1Controller );
#endif /* (CAN_CFG_TRANSMIT) */

    return ( u1Ret );
}


/****************************************************************************/
/* Function Name | Can_st_Reset                                             */
/* Description   | Controller Reinitialization                              */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 u1Controller                                       */
/* Return Value  | uint8                                                    */
/*               |   CAN_PROC_OK                                            */
/*               |   CAN_PROC_BUSY                                          */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
uint8
Can_st_Reset( uint8 u1Controller )
{
    uint8    u1Ctrl;
    uint8    u1CtrlNum;
    uint8    u1Result;
    uint8    u1Ret;

    u1Ret = (uint8)CAN_PROC_BUSY;

    u1Result = Can_st_GlobalRegCheck( u1Controller );

    if ( u1Result == (uint8)CAN_PROC_OK )
    {
        u1Ret = Can_st_ResetChannel( u1Controller );
    }
    else
    {
        u1CtrlNum = Can_tb_u1CtrlNum;
        for ( u1Ctrl = (uint8)0U; u1Ctrl < u1CtrlNum; u1Ctrl++ )
        {
            if ( u1Ctrl != u1Controller )
            {
                Can_st_StopInd( u1Ctrl );

                Can_fs_MpuFailInd( u1Ctrl );
            }
        }

        u1Result = Can_st_ResetGlobal();

        if ( u1Result == (uint8)CAN_PROC_OK )
        {
            u1Ret = Can_st_ResetChannel( u1Controller );
        }
    }

    return ( u1Ret );
}


/****************************************************************************/
/* Function Name | Can_st_ChkStart                                          */
/* Description   | Controller Communication Start Check                     */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 u1Controller                                       */
/* Return Value  | uint8                                                    */
/*               |   CAN_PROC_OK                                            */
/*               |   CAN_PROC_BUSY                                          */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
uint8
Can_st_ChkStart( uint8 u1Controller )
{
    uint32    u4GSTS;
    uint8     u1Ret;

    u1Ret = (uint8)CAN_PROC_BUSY;

    u4GSTS = *(Can_tb_stGlobalReg.ptu4GSTS);
    if ( ( u4GSTS & CAN_u4GSTS_MODEALL_MSK ) == CAN_u4GSTS_GMODE_RESET )
    {
        Can_st_StartGlobal();
    }

    u4GSTS = *(Can_tb_stGlobalReg.ptu4GSTS);
    if ( ( u4GSTS & CAN_u4GSTS_MODEALL_MSK ) == CAN_u4GSTS_GMODE_COMM )
    {
        u1Ret = Can_st_StartChannel( u1Controller );
    }

    return ( u1Ret );
}


/****************************************************************************/
/* Function Name | Can_st_ChkStop                                           */
/* Description   | Controller Communication Stop Check                      */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 u1Controller                                       */
/* Return Value  | uint8                                                    */
/*               |   CAN_PROC_OK                                            */
/*               |   CAN_PROC_BUSY                                          */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
uint8
Can_st_ChkStop( uint8 u1Controller )
{
#if (CAN_CFG_TRANSMIT == CAN_USE)
    CanConst CanTbChRegType *           ptChReg;
    CanConst CanTbTxMbBitType *         ptTxMbBit;
    uint32                              u4TxMbUseBitMaskLo;
    uint32                              u4TxMbUseBitMaskHi;
    uint32                              u4TMTRSTSLo;
    uint32                              u4TMTRSTSHi;
#endif /* (CAN_CFG_TRANSMIT == CAN_USE) */
    uint8                               u1Ret;

#if (CAN_CFG_TRANSMIT == CAN_USE)
    u1Ret = (uint8)CAN_PROC_BUSY;

    ptTxMbBit          = &Can_tb_stTxMbBit[ u1Controller ];
    u4TxMbUseBitMaskLo = ( ptTxMbBit->u4TxIntrBit[CAN_IDX0] | ptTxMbBit->u4TxPollBit[CAN_IDX0] );
    u4TxMbUseBitMaskHi = ( ptTxMbBit->u4TxIntrBit[CAN_IDX1] | ptTxMbBit->u4TxPollBit[CAN_IDX1] );
    ptChReg            = &Can_tb_stChReg[ u1Controller ];
    u4TMTRSTSLo        = ptChReg->ptu4TMTRSTS[CAN_IDX0];
    u4TMTRSTSHi        = ptChReg->ptu4TMTRSTS[CAN_IDX1];
    if ( ( ( u4TMTRSTSLo & u4TxMbUseBitMaskLo ) == CAN_u4BIT_NONE )
    &&   ( ( u4TMTRSTSHi & u4TxMbUseBitMaskHi ) == CAN_u4BIT_NONE ) )
    {
        u1Ret = Can_st_StopChannel( u1Controller );
    }

#else /* (CAN_CFG_TRANSMIT != CAN_USE) */
    u1Ret = Can_st_StopChannel( u1Controller );
#endif /* (CAN_CFG_TRANSMIT) */

    return ( u1Ret );
}


/****************************************************************************/
/* Function Name | Can_st_ChkReset                                          */
/* Description   | Controller Reinitialization Check                        */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 u1Controller                                       */
/* Return Value  | uint8                                                    */
/*               |   CAN_PROC_OK                                            */
/*               |   CAN_PROC_BUSY                                          */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
uint8
Can_st_ChkReset( uint8 u1Controller )
{
    uint8    u1Ctrl;
    uint8    u1CtrlNum;
    uint8    u1Result;
    uint8    u1Ret;

    u1Ret = (uint8)CAN_PROC_BUSY;

    u1CtrlNum = Can_tb_u1CtrlNum;
    for ( u1Ctrl = (uint8)0U; u1Ctrl < u1CtrlNum; u1Ctrl++ )
    {
        if ( u1Ctrl != u1Controller )
        {
            Can_st_StopInd( u1Ctrl );

            Can_fs_MpuFailInd( u1Ctrl );
        }
    }

    u1Result = Can_st_ResetGlobal();

    if ( u1Result == (uint8)CAN_PROC_OK )
    {
        u1Ret = Can_st_ResetChannel( u1Controller );
    }

    return ( u1Ret );
}


/****************************************************************************/
/* Function Name | Can_st_ShutdownReg                                       */
/* Description   | Can Register Set for Shutdown                            */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
void
Can_st_ShutdownReg( void )
{
    uint32    u4GSTS;
    uint8     u1Controller;
    uint8     u1CtrlNum;

    u4GSTS = *(Can_tb_stGlobalReg.ptu4GSTS);
    if ( ( u4GSTS & CAN_u4GSTS_GRAMINIT_MSK ) == CAN_u4BIT_NONE )
    {
        if ( ( u4GSTS & CAN_u4GSTS_MODEALL_MSK ) != CAN_u4GSTS_GMODE_STOP )
        {
            Can_st_GlobalMode_Any2Reset();

            u4GSTS = *(Can_tb_stGlobalReg.ptu4GSTS);
            if ( ( u4GSTS & CAN_u4GSTS_MODEALL_MSK ) == CAN_u4GSTS_GMODE_RESET )
            {
                Can_st_StopGlobal();

                u1CtrlNum = Can_tb_u1CtrlNum;
                for ( u1Controller = (uint8)0U; u1Controller < u1CtrlNum; u1Controller++ )
                {
                    if ( Can_tb_stCtrlInfo[ u1Controller ].u1CtrlAct == (uint8)CAN_TRUE )
                    {
                        (void)Can_st_StopChannel( u1Controller ); /* MISRA DEVIATION: no return check required */
                    }
                }

                Can_st_GlobalMode_Reset2Stop();
            }
        }
    }
}


/****************************************************************************/
/* Function Name | Can_st_SetConfigMbox                                     */
/* Description   | MBOX Configuration Set                                   */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 u1Controller                                       */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
void
Can_st_SetConfigMbox( uint8 u1Controller )
{
    uint32    u4GSTS;
    uint32    u4GAFLCFG0Conf;
#if (CAN_CFG_CONTROLLERNUM_MAX > 2U)
    uint32    u4GAFLCFG1Conf;
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 2U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 4U)
    uint32    u4GAFLCFG2Conf;
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 4U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 6U)
    uint32    u4GAFLCFG3Conf;
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 6U) */

    u4GSTS = *(Can_tb_stGlobalReg.ptu4GSTS);
    u4GAFLCFG0Conf = Can_tb_u4GAFLCFG0Conf;
#if (CAN_CFG_CONTROLLERNUM_MAX > 2U)
    u4GAFLCFG1Conf = Can_tb_u4GAFLCFG1Conf;
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 2U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 4U)
    u4GAFLCFG2Conf = Can_tb_u4GAFLCFG2Conf;
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 4U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 6U)
    u4GAFLCFG3Conf = Can_tb_u4GAFLCFG3Conf;
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 6U) */

    if ( ( ( u4GSTS & CAN_u4GSTS_MODEALL_MSK )          == CAN_u4GSTS_GMODE_RESET )
    &&   ( ( Can_tb_stGlobalReg.ptu4GAFLCFG[ CAN_IDX0 ] != u4GAFLCFG0Conf         )
#if (CAN_CFG_CONTROLLERNUM_MAX > 2U)
        || ( Can_tb_stGlobalReg.ptu4GAFLCFG[ CAN_IDX1 ] != u4GAFLCFG1Conf         )
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 2U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 4U)
        || ( Can_tb_stGlobalReg.ptu4GAFLCFG[ CAN_IDX2 ] != u4GAFLCFG2Conf         )
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 4U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 6U)
        || ( Can_tb_stGlobalReg.ptu4GAFLCFG[ CAN_IDX3 ] != u4GAFLCFG3Conf         )
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 6U) */
    ) )
    {
        Can_st_SetRxRule();
    }
}


/****************************************************************************/
/* Function Name | Can_st_SetBaudrate                                       */
/* Description   | Baud Rate Register Set                                   */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8  u1Controller                                      */
/*               | uint16 u2BaudRateConfigID                                */
/* Return Value  | uint8                                                    */
/*               |   CAN_PROC_OK                                            */
/*               |   CAN_PROC_BUSY                                          */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
uint8
Can_st_SetBaudrate( uint8 u1Controller, uint16 u2BaudRateConfigID )
{
    CanConst CanTbChRegType *          ptChReg;
    CanConst CanBaudrateSwtCfgType *   ptBaudrateSwtCfg;
    CanConst CanTbSetRSCANRegType *    ptSetRSCANReg;
    uint32                             u4BRSUse;
    uint32                             u4TDCO;
    uint8                              u1BRSwtCfgTbl_ARYSIZE;
    uint8                              u1Ret;

    u1Ret = (uint8)CAN_PROC_BUSY;

    u1BRSwtCfgTbl_ARYSIZE = *(Can_tb_ptBRSwtCfgTbl_ARYSIZE);
    if ( u2BaudRateConfigID < u1BRSwtCfgTbl_ARYSIZE )
    {
        ptChReg = &Can_tb_stChReg[ u1Controller ];

        ptBaudrateSwtCfg = &(Can_tb_ptBaudrateSwtCfgTbl[ u2BaudRateConfigID ]);

        *(ptChReg->ptu4CmNCFG) = ptBaudrateSwtCfg->u4Baudrate;

        if ( Can_tb_stCtrlInfo[ u1Controller ].u1CtrlOpeMode == (uint8)CAN_OPEMODE_CANFD )
        {
            *(ptChReg->ptu4CmDCFG) = ptBaudrateSwtCfg->u4DataBaudrate;

            ptSetRSCANReg = &Can_tb_stSetRSCANReg[ u1Controller ];
            u4BRSUse = ptBaudrateSwtCfg->u4BaudrateInfo_2;
            if ( u4BRSUse == (uint32)CAN_USE )
            {
                u4TDCO = ptBaudrateSwtCfg->u4BaudrateInfo_1;
                *(ptChReg->ptu4CmFDCFG) = ( (ptSetRSCANReg->u4CmFDCFGConf & ~CAN_u4CMFDCFG_TDCO_MSK) | (u4TDCO & CAN_u4CMFDCFG_TDCO_MSK) ) | CAN_u4CMFDCFG_TDCE_SET;

                Can_st_u1BRSUse[ u1Controller ] = (uint8)CAN_ST_BRS_USE;
            }
            else
            {
                u4TDCO = CAN_u4BIT_NONE;
                *(ptChReg->ptu4CmFDCFG) = ( (ptSetRSCANReg->u4CmFDCFGConf & ~CAN_u4CMFDCFG_TDCO_MSK) | (u4TDCO & CAN_u4CMFDCFG_TDCO_MSK) ) & CAN_u4CMFDCFG_TDCE_CLR;

                Can_st_u1BRSUse[ u1Controller ] = (uint8)CAN_ST_BRS_NOUSE;
            }
        }

        u1Ret = (uint8)CAN_PROC_OK;
    }

    return ( u1Ret );
}


/****************************************************************************/
/* Function Name | Can_st_GlobalMode_Reset2Test                             */
/* Description   | Global Mode Switch(Reset Mode to Test Mode)              */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
void
Can_st_GlobalMode_Reset2Test( void )
{
    volatile uint32     u4GSTS;
    uint16              u2WaitCount;

    u4GSTS = CAN_u4GSTS_GMODE_RESET;

    *(Can_tb_stGlobalReg.ptu4GCTR) = CAN_u4GCTR_INIT | CAN_u4GCTR_GMDC_TEST_SET;

    for ( u2WaitCount = (uint16)0U; ( u2WaitCount < (uint16)CAN_GMODE_RST2TST_CYCLE ) && ( ( u4GSTS & CAN_u4GSTS_MODEALL_MSK ) != CAN_u4GSTS_GMODE_TEST ); u2WaitCount++ )
    {
        u4GSTS = *(Can_tb_stGlobalReg.ptu4GSTS);
    }
}


/****************************************************************************/
/* Function Name | Can_st_GlobalMode_Any2Reset                              */
/* Description   | Global Mode Switch(Any Mode to Reset Mode)               */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
void
Can_st_GlobalMode_Any2Reset( void )
{
    volatile uint32     u4GSTS;
    uint16              u2WaitCount;
    uint16              u2ClockCount;

    u4GSTS = ~CAN_u4GSTS_GMODE_RESET;

    u2ClockCount = Can_tb_u2GmodeAny2RstWaitCnt;

    Can_DI()

    *(Can_tb_stGlobalReg.ptu4GCTR) = CAN_u4GCTR_INIT | CAN_u4GCTR_GMDC_RESET_SET;

    for ( u2WaitCount = (uint16)0U; ( u2WaitCount < u2ClockCount ) && ( ( u4GSTS & CAN_u4GSTS_MODEALL_MSK ) != CAN_u4GSTS_GMODE_RESET ); u2WaitCount++ )
    {
        u4GSTS = *(Can_tb_stGlobalReg.ptu4GSTS);
    }

    Can_EI()
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Can_st_GlobalMode_Reset2Stop                             */
/* Description   | Global Mode Switch(Reset Mode to Stop Mode)              */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
static void
Can_st_GlobalMode_Reset2Stop( void )
{
    volatile uint32     u4GSTS;
    uint16              u2WaitCount;

    u4GSTS = CAN_u4GSTS_GMODE_RESET;

    *(Can_tb_stGlobalReg.ptu4GCTR) = CAN_u4GCTR_INIT | CAN_u4GCTR_GSLPR_STOP_SET | CAN_u4GCTR_GMDC_RESET_SET;

    for ( u2WaitCount = (uint16)0U; ( u2WaitCount < (uint16)CAN_GMODE_RST2STP_CYCLE ) && ( ( u4GSTS & CAN_u4GSTS_MODEALL_MSK ) != CAN_u4GSTS_GMODE_STOP ); u2WaitCount++ )
    {
        u4GSTS = *(Can_tb_stGlobalReg.ptu4GSTS);
    }
}


/****************************************************************************/
/* Function Name | Can_st_GlobalMode_Reset2Comm                             */
/* Description   | Global Mode Switch(Reset Mode to Operation Mode)         */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
static void
Can_st_GlobalMode_Reset2Comm( void )
{
    volatile uint32     u4GSTS;
    uint16              u2WaitCount;

    u4GSTS = CAN_u4GSTS_GMODE_RESET;

    *(Can_tb_stGlobalReg.ptu4GCTR) = CAN_u4GCTR_INIT | CAN_u4GCTR_GMDC_COMM_SET;

    for ( u2WaitCount = (uint16)0U; ( u2WaitCount < (uint16)CAN_GMODE_RST2COM_CYCLE ) && ( ( u4GSTS & CAN_u4GSTS_MODEALL_MSK ) != CAN_u4GSTS_GMODE_COMM ); u2WaitCount++ )
    {
        u4GSTS = *(Can_tb_stGlobalReg.ptu4GSTS);
    }
}


/****************************************************************************/
/* Function Name | Can_st_ChannelMode_Any2Reset                             */
/* Description   | Channel Mode Switch(Any Mode to Reset Mode)              */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 u1Controller                                       */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
static void
Can_st_ChannelMode_Any2Reset( uint8 u1Controller )
{
    CanConst CanTbChRegType *           ptChReg;
    volatile uint32                     u4CmSTS;
    uint16                              u2WaitCount;
    uint16                              u2ClockCount;

    u4CmSTS = ~CAN_u4CMSTS_CMODE_RESET;

    ptChReg = &Can_tb_stChReg[ u1Controller ];

    u2ClockCount = Can_tb_u2CmodeAny2RstWaitCnt;

    Can_DI()

    *(ptChReg->ptu4CmCTR) = ( *(ptChReg->ptu4CmCTR) & ~CAN_u4CMCTR_MODEALL_MSK ) | CAN_u4CMCTR_CHMDC_RESET_SET;

    for ( u2WaitCount = (uint16)0U; ( u2WaitCount < u2ClockCount ) && ( ( u4CmSTS & CAN_u4CMSTS_MODEALL_MSK ) != CAN_u4CMSTS_CMODE_RESET ); u2WaitCount++ )
    {
        u4CmSTS = *(ptChReg->ptu4CmSTS);
    }

    Can_EI()
}


/****************************************************************************/
/* Function Name | Can_st_ChannelMode_Reset2Stop                            */
/* Description   | Channel Mode Switch(Reset Mode to Stop Mode)             */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 u1Controller                                       */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
static void
Can_st_ChannelMode_Reset2Stop( uint8 u1Controller )
{
    CanConst CanTbChRegType *           ptChReg;
    CanConst CanTbSetRSCANRegType *     ptSetRSCANReg;
    volatile uint32                     u4CmSTS;
    uint16                              u2WaitCount;

    u4CmSTS = CAN_u4CMSTS_CMODE_RESET;

    ptChReg       = &Can_tb_stChReg[ u1Controller ];
    ptSetRSCANReg = &Can_tb_stSetRSCANReg[ u1Controller ];

    *(ptChReg->ptu4CmCTR) = ptSetRSCANReg->u4CmCTRConf | CAN_u4CMCTR_CSLPR_STOP_SET | CAN_u4CMCTR_CHMDC_RESET_SET;

    for ( u2WaitCount = (uint16)0U; ( u2WaitCount < (uint16)CAN_CMODE_RST2STP_CYCLE ) && ( ( u4CmSTS & CAN_u4CMSTS_MODEALL_MSK ) != CAN_u4CMSTS_CMODE_STOP ); u2WaitCount++ )
    {
        u4CmSTS = *(ptChReg->ptu4CmSTS);
    }
}


/****************************************************************************/
/* Function Name | Can_st_ChannelMode_Reset2Comm                            */
/* Description   | Channel Mode Switch(Reset Mode to Communication Mode)    */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 u1Controller                                       */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
static void
Can_st_ChannelMode_Reset2Comm( uint8 u1Controller )
{
    CanConst CanTbChRegType *           ptChReg;
    CanConst CanTbSetRSCANRegType *     ptSetRSCANReg;
    volatile uint32                     u4CmSTS;
    uint16                              u2ClockCount;
    uint16                              u2WaitCount;

    u4CmSTS = CAN_u4CMSTS_CMODE_RESET;

    ptChReg       = &Can_tb_stChReg[ u1Controller ];
    ptSetRSCANReg = &Can_tb_stSetRSCANReg[ u1Controller ];

    *(ptChReg->ptu4CmCTR) = ptSetRSCANReg->u4CmCTRConf | CAN_u4CMCTR_CHMDC_COMM_SET;

    u2ClockCount = Can_tb_u2CmodeRst2ComWaitCnt;
    for ( u2WaitCount = (uint16)0U; ( u2WaitCount < u2ClockCount ) && ( ( u4CmSTS & CAN_u4CMSTS_MODEALL_MSK ) != CAN_u4CMSTS_CMODE_COMM ); u2WaitCount++ )
    {
        u4CmSTS = *(ptChReg->ptu4CmSTS);
    }
}


/****************************************************************************/
/* Function Name | Can_st_GlobalRegCheck                                    */
/* Description   | Global Register Garbled Check                            */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 u1Controller                                       */
/* Return Value  | uint8                                                    */
/*               |   CAN_PROC_OK                                            */
/*               |   CAN_PROC_NG                                            */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
static uint8
Can_st_GlobalRegCheck( uint8 u1Controller )
{
    CanConst CanTbChRegType *           ptChReg;
    CanConst CanTbCtrlInfoType *        ptCtrlCfg;
    CanConst CanTbSetRSCANRegType *     ptSetRSCANReg;
    uint32                              u4Page;
    uint32                              u4FlMask;
    uint32                              u4GCFGConf;
    uint32                              u4GFDCFGConf;
    uint32                              u4GAFLCFG0Conf;
#if (CAN_CFG_CONTROLLERNUM_MAX > 2U)
    uint32                              u4GAFLCFG1Conf;
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 2U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 4U)
    uint32                              u4GAFLCFG2Conf;
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 4U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 6U)
    uint32                              u4GAFLCFG3Conf;
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 6U) */
    uint16                              u2RxRuleNo;
    uint16                              u2RxRuleNum;
    uint8                               u1RuleRegNo;
    uint8                               u1MskIdx;
    uint8                               u1RxFifo;
    uint8                               u1Ret;

    u1Ret = (uint8)CAN_PROC_OK;

    ptChReg = &Can_tb_stChReg[ u1Controller ];
    ptSetRSCANReg = &Can_tb_stSetRSCANReg[ u1Controller ];

    u4GCFGConf = Can_tb_u4GCFGConf;
    u4GFDCFGConf = Can_tb_u4GFDCFGConf;
    if ( ( ( *( Can_tb_stGlobalReg.ptu4GCFG )        & CAN_u4GCFG_USEDBIT_MSK )       != ( u4GCFGConf & CAN_u4GCFG_USEDBIT_MSK ) )
    ||   ( ( *( Can_tb_stGlobalReg.ptu4GCTR )        & CAN_u4GCTR_USEDBIT_MSK )       != ( CAN_u4GCTR_INIT | CAN_u4GCTR_GMDC_COMM_SET ) )
    ||   ( ( *( Can_tb_stGlobalReg.ptu4RMNB )        & CAN_u4RMNB_USEDBIT_MSK )       != CAN_u4RMNB_CLEARALL       )
    ||   ( ( *( Can_tb_stGlobalReg.ptu4GAFLECTR )    & CAN_u4GAFLECTR_USEDBIT_MSK )   != CAN_u4GAFLECTR_AFLDAE_DIS )
    ||   ( ( ptChReg->ptu4CFCC[ CAN_TRX_FIFO_0 ]     & CAN_u4CFCC_GCHKBIT_MSK )       != ( ptSetRSCANReg->u4CFCC0Conf & CAN_u4CFCC_GCHKBIT_MSK ) )
    ||   ( ( ptChReg->ptu4CFCC[ CAN_TRX_FIFO_1 ]     & CAN_u4CFCC_GCHKBIT_MSK )       != ( ptSetRSCANReg->u4CFCC1Conf & CAN_u4CFCC_GCHKBIT_MSK ) )
    ||   ( ( ptChReg->ptu4CFCC[ CAN_TRX_FIFO_2 ]     & CAN_u4CFCC_GCHKBIT_MSK )       != ( ptSetRSCANReg->u4CFCC2Conf & CAN_u4CFCC_GCHKBIT_MSK ) )
    ||   ( ( *( Can_tb_stGlobalReg.ptu4GTSTCFG )     & CAN_u4GTSTCFG_USEDBIT_MSK )    != CAN_u4GTSTCFG_ICBCE_DIS   )
    ||   ( ( *( Can_tb_stGlobalReg.ptu4GTSTCTR )     & CAN_u4GTSTCTR_USEDBIT_MSK )    != ( CAN_u4GTSTCTR_RTME_DIS | CAN_u4GTSTCTR_ICBCTME_DIS ) )
    ||   ( ( *( Can_tb_stGlobalReg.ptu4CDTCT )       & CAN_u4CDTCT_USEDBIT_MSK )      != CAN_u4CDTCT_INIT          )
    ||   ( ( *( Can_tb_stGlobalReg.ptu4GFDCFG )      & CAN_u4GFDCFG_USEDBIT_MSK )     != ( u4GFDCFGConf & CAN_u4GFDCFG_USEDBIT_MSK ) )
    ||   ( ( *( Can_tb_stGlobalReg.ptu4CDTTCT )      & CAN_u4CDTTCT_USEDBIT_MSK )     != CAN_u4CDTTCT_INIT         )
    ||   ( ( *( Can_tb_stGlobalReg.ptu4GRSTC )       & CAN_u4GRSTC_USEDBIT_MSK )      != ( CAN_u4GRSTC_INIT & CAN_u4GRSTC_USEDBIT_MSK ) )
    ||   ( ( *( Can_tb_stGlobalReg.ptu4GFCMC )       & CAN_u4GFCMC_USEDBIT_MSK )      != CAN_u4GFCMC_INIT          )
    ||   ( ( *( Can_tb_stGlobalReg.ptu4GFTBAC )      & CAN_u4GFTBAC_USEDBIT_MSK )     != CAN_u4GFTBAC_INIT         )
    ||   ( ( *( Can_tb_stGlobalReg.ptu4GPFLECTR )    & CAN_u4GPFLECTR_USEDBIT_MSK )   != ( CAN_u4GPFLECTR_INIT & CAN_u4GPFLECTR_USEDBIT_MSK ) ) )
    {
        u1Ret = (uint8)CAN_PROC_NG;
    }

    if ( u1Ret == (uint8)CAN_PROC_OK )
    {
        for ( u1RxFifo = (uint8)0U; ( u1RxFifo < (uint8)CAN_NUM_FIFO_RCV ) && ( u1Ret == (uint8)CAN_PROC_OK ); u1RxFifo++ )
        {
            if ( Can_tb_stGlobalReg.ptu4RFCC[ u1RxFifo ] != CAN_u4RFCC_INIT )
            {
                u1Ret = (uint8)CAN_PROC_NG;
            }
        }
    }

    if ( u1Ret == (uint8)CAN_PROC_OK )
    {
        u4GAFLCFG0Conf = Can_tb_u4GAFLCFG0Conf;
        if ( Can_tb_stGlobalReg.ptu4GAFLCFG[ CAN_IDX0 ] != u4GAFLCFG0Conf )
        {
            u1Ret = (uint8)CAN_PROC_NG;
        }

#if (CAN_CFG_CONTROLLERNUM_MAX > 2U)
        u4GAFLCFG1Conf = Can_tb_u4GAFLCFG1Conf;
        if ( Can_tb_stGlobalReg.ptu4GAFLCFG[ CAN_IDX1 ] != u4GAFLCFG1Conf )
        {
            u1Ret = (uint8)CAN_PROC_NG;
        }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 2U) */

#if (CAN_CFG_CONTROLLERNUM_MAX > 4U)
        u4GAFLCFG2Conf = Can_tb_u4GAFLCFG2Conf;
        if ( Can_tb_stGlobalReg.ptu4GAFLCFG[ CAN_IDX2 ] != u4GAFLCFG2Conf )
        {
            u1Ret = (uint8)CAN_PROC_NG;
        }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 4U) */

#if (CAN_CFG_CONTROLLERNUM_MAX > 6U)
        u4GAFLCFG3Conf = Can_tb_u4GAFLCFG3Conf;
        if ( Can_tb_stGlobalReg.ptu4GAFLCFG[ CAN_IDX3 ] != u4GAFLCFG3Conf )
        {
            u1Ret = (uint8)CAN_PROC_NG;
        }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 6U) */

        ptCtrlCfg   = &Can_tb_stCtrlInfo[ u1Controller ];
        u2RxRuleNum = ptCtrlCfg->u2RxRuleOffSetId + (uint16)(ptCtrlCfg->u1RxRuleUseNum);

        for ( u2RxRuleNo = (uint16)ptCtrlCfg->u2RxRuleOffSetId; ( u2RxRuleNo < u2RxRuleNum ) && ( u1Ret == (uint8)CAN_PROC_OK ); u2RxRuleNo++ )
        {
            u4Page = ( (uint32)u2RxRuleNo >> CAN_NUM_RULETABLE_PER_PAGE_SFT ) & CAN_u4GAFLECTR_AFLPN_MSK;

            u1RuleRegNo = (uint8)( u2RxRuleNo & (uint16)CAN_NUM_RULETABLE_PER_PAGE_MSK );

            *(Can_tb_stGlobalReg.ptu4GAFLECTR) = ( CAN_u4GAFLECTR_AFLDAE_DIS | u4Page );

            u1MskIdx = Can_tb_stRxRuleSetting[ u2RxRuleNo ].u1RxMaskRef;
            u4FlMask = Can_tb_u4RxMask[ u1MskIdx ];
            if ( ( Can_tb_stGlobalReg.ptstGAFL[ u1RuleRegNo ].u4GAFLID != Can_tb_stRxRuleSetting[ u2RxRuleNo ].u4GAFLIDConf )
            ||   ( Can_tb_stGlobalReg.ptstGAFL[ u1RuleRegNo ].u4GAFLM  != u4FlMask                                          )
            ||   ( Can_tb_stGlobalReg.ptstGAFL[ u1RuleRegNo ].u4GAFLP0 != Can_tb_stRxRuleSetting[ u2RxRuleNo ].u4GAFLP0Conf )
            ||   ( Can_tb_stGlobalReg.ptstGAFL[ u1RuleRegNo ].u4GAFLP1 != Can_tb_stRxRuleSetting[ u2RxRuleNo ].u4GAFLP1Conf ) )
            {
                u1Ret = (uint8)CAN_PROC_NG;
            }
        }
    }

    return ( u1Ret );
}


/****************************************************************************/
/* Function Name | Can_st_InitGlobalReg                                     */
/* Description   | Global Register Initialization                           */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
static void
Can_st_InitGlobalReg( void )
{
    CanConst CanTbChRegType *           ptChReg;
    uint8                               u1Controller;
    uint8                               u1RxRulePageNum;
    uint8                               u1CtrlNum;
    uint8                               u1PageCnt;
    uint8                               u1RxFifo;
    uint8                               u1RuleRegNo;

    *(Can_tb_stGlobalReg.ptu4GRSTC) = CAN_u4GRSTC_INIT;

    *(Can_tb_stGlobalReg.ptu4GCTR) = CAN_u4GCTR_INIT | CAN_u4GCTR_GMDC_RESET_SET;

    *(Can_tb_stGlobalReg.ptu4GFDCFG) = CAN_u4GFDCFG_INIT;

    *(Can_tb_stGlobalReg.ptu4GFCMC)    = CAN_u4GFCMC_INIT;

    *(Can_tb_stGlobalReg.ptu4GFTBAC)   = CAN_u4GFTBAC_INIT;

    Can_tb_stGlobalReg.ptu4GAFLCFG[ CAN_IDX0 ] = CAN_u4GAFLCFG_INIT;
#if (CAN_CFG_CONTROLLERNUM_MAX > 2U)
    Can_tb_stGlobalReg.ptu4GAFLCFG[ CAN_IDX1 ] = CAN_u4GAFLCFG_INIT;
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 2U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 4U)
    Can_tb_stGlobalReg.ptu4GAFLCFG[ CAN_IDX2 ] = CAN_u4GAFLCFG_INIT;
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 4U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 6U)
    Can_tb_stGlobalReg.ptu4GAFLCFG[ CAN_IDX3 ] = CAN_u4GAFLCFG_INIT;
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 6U) */

    u1RxRulePageNum = Can_tb_u1RxRulePageNum;
    for ( u1PageCnt = (uint8)0U; u1PageCnt < u1RxRulePageNum; u1PageCnt++ )
    {
        *(Can_tb_stGlobalReg.ptu4GAFLECTR) = ((uint32)u1PageCnt | CAN_u4GAFLECTR_AFLDAE_ENA);

        for ( u1RuleRegNo = (uint8)0U; u1RuleRegNo < (uint8)CAN_NUM_RULETABLE_PER_PAGE; u1RuleRegNo++ )
        {
            Can_tb_stGlobalReg.ptstGAFL[ u1RuleRegNo ].u4GAFLID = CAN_u4GAFLID_INIT;
            Can_tb_stGlobalReg.ptstGAFL[ u1RuleRegNo ].u4GAFLM  = CAN_u4GAFLM_INIT;
            Can_tb_stGlobalReg.ptstGAFL[ u1RuleRegNo ].u4GAFLP0 = CAN_u4GAFLP0_INIT;
            Can_tb_stGlobalReg.ptstGAFL[ u1RuleRegNo ].u4GAFLP1 = CAN_u4GAFLP1_INIT;
        }
    }
    *(Can_tb_stGlobalReg.ptu4GAFLECTR) = CAN_u4GAFLECTR_AFLDAE_DIS;

    *(Can_tb_stGlobalReg.ptu4GCFG)     = CAN_u4GCFG_INIT;

    *(Can_tb_stGlobalReg.ptu4RMNB)     = CAN_u4RMNB_INIT;

    for ( u1RxFifo = (uint8)0U; u1RxFifo < (uint8)CAN_NUM_FIFO_RCV; u1RxFifo++ )
    {
        Can_tb_stGlobalReg.ptu4RFCC[ u1RxFifo ] = CAN_u4RFCC_INIT;
    }

    u1CtrlNum = Can_tb_u1CtrlNum;
    for ( u1Controller = (uint8)0U; u1Controller < u1CtrlNum; u1Controller++ )
    {
        if ( Can_tb_stCtrlInfo[ u1Controller ].u1CtrlAct == (uint8)CAN_TRUE )
        {
            ptChReg = &Can_tb_stChReg[ u1Controller ];

            ptChReg->ptu4CFCC[ CAN_TRX_FIFO_0 ] = CAN_u4CFCC_INIT;
            ptChReg->ptu4CFCC[ CAN_TRX_FIFO_1 ] = CAN_u4CFCC_INIT;
            ptChReg->ptu4CFCC[ CAN_TRX_FIFO_2 ] = CAN_u4CFCC_INIT;

            ptChReg->ptu4CFCCE[ CAN_TRX_FIFO_0 ] = CAN_u4CFCCE_INIT;
            ptChReg->ptu4CFCCE[ CAN_TRX_FIFO_1 ] = CAN_u4CFCCE_INIT;
            ptChReg->ptu4CFCCE[ CAN_TRX_FIFO_2 ] = CAN_u4CFCCE_INIT;
        }
    }

    *(Can_tb_stGlobalReg.ptu4GPFLECTR) = CAN_u4GPFLECTR_INIT;

    Can_tb_stGlobalReg.ptu4GPFLCFG[ CAN_IDX0 ] = CAN_u4GPFLCFG_INIT;
#if (CAN_CFG_CONTROLLERNUM_MAX > 4U)
    Can_tb_stGlobalReg.ptu4GPFLCFG[ CAN_IDX1 ] = CAN_u4GPFLCFG_INIT;
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 4U) */
}


/****************************************************************************/
/* Function Name | Can_st_InitChannelReg                                    */
/* Description   | Channel Register Initialization                          */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 u1Controller                                       */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
static void
Can_st_InitChannelReg( uint8 u1Controller )
{
    CanConst CanTbChRegType *           ptChReg;
    uint8                               u1MBox;
    uint8                               u1Data;

    ptChReg = &Can_tb_stChReg[ u1Controller ];

    *(ptChReg->ptu4CmNCFG) = CAN_u4CMNCFG_INIT;

    *(ptChReg->ptu4CmCTR) = CAN_u4CMCTR_INIT;

    *(ptChReg->ptu4CmDCFG) = CAN_u4CMDCFG_INIT;

    *(ptChReg->ptu4CmFDCFG) = CAN_u4CMFDCFG_INIT;

    for ( u1MBox = (uint8)0U; u1MBox < (uint8)CAN_NUM_BUF_SND_PER_CH; u1MBox++ )
    {
#if (CAN_CFG_TXBUF_NUM == 48U)
        if ( ( u1MBox < (uint8)CAN_MB016 )
        ||   ( u1MBox > (uint8)CAN_MB031 ) )
#endif /* (CAN_CFG_TXBUF_NUM == 48U) */
        {
            ptChReg->ptstTM[ u1MBox ].u4IDReg = CAN_u4TMID_INIT;

            ptChReg->ptstTM[ u1MBox ].u4PTRReg = CAN_u4TMPTR_CLEARALL;

            ptChReg->ptstTM[ u1MBox ].u4FDCTRReg = CAN_u4TMFDCTR_CLEARALL;

            for ( u1Data = (uint8)0U; u1Data < (uint8)CAN_DATA_ARYSIZE_4BYTE; u1Data++ )
            {
                ptChReg->ptstTM[ u1MBox ].u4DFReg[ u1Data ] = CAN_u4TMDF_CLEARALL;
            }
        }
    }

    ptChReg->ptu4TMIEC[CAN_IDX0] = CAN_u4TMIEC_INIT;
    ptChReg->ptu4TMIEC[CAN_IDX1] = CAN_u4TMIEC_INIT;

    *(ptChReg->ptu4TXQCC0) = CAN_u4TXQCC0_INIT;
    *(ptChReg->ptu4TXQCC1) = CAN_u4TXQCC1_INIT;
    *(ptChReg->ptu4TXQCC2) = CAN_u4TXQCC2_INIT;
    *(ptChReg->ptu4TXQCC3) = CAN_u4TXQCC3_INIT;

    *(ptChReg->ptu4THLCC)   = CAN_u4THLCC_INIT;
}


/****************************************************************************/
/* Function Name | Can_st_SetGlobalReg                                      */
/* Description   | Global Register Use Set                                  */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
static void
Can_st_SetGlobalReg( void )
{
    CanConst CanTbChRegType *           ptChReg;
    CanConst CanTbSetRSCANRegType *     ptSetRSCANReg;
    uint8                               u1Controller;
    uint8                               u1CtrlNum;
    uint8                               u1RxFifo;

    *(Can_tb_stGlobalReg.ptu4GFDCFG) = Can_tb_u4GFDCFGConf;

    *(Can_tb_stGlobalReg.ptu4GCFG) = Can_tb_u4GCFGConf;

    *(Can_tb_stGlobalReg.ptu4GCTR) = CAN_u4GCTR_INIT | CAN_u4GCTR_GMDC_RESET_SET;

    for ( u1RxFifo = (uint8)0U; u1RxFifo < (uint8)CAN_NUM_FIFO_RCV; u1RxFifo++ )
    {
        Can_tb_stGlobalReg.ptu4RFCC[ u1RxFifo ] = CAN_u4RFCC_INIT;
    }

    u1CtrlNum = Can_tb_u1CtrlNum;
    for ( u1Controller = (uint8)0U; u1Controller < u1CtrlNum; u1Controller++ )
    {
        if ( Can_tb_stCtrlInfo[ u1Controller ].u1CtrlAct == (uint8)CAN_TRUE )
        {
            ptChReg       = &Can_tb_stChReg[ u1Controller ];
            ptSetRSCANReg = &Can_tb_stSetRSCANReg[ u1Controller ];

            ptChReg->ptu4CFCC[ CAN_TRX_FIFO_0 ] = ptSetRSCANReg->u4CFCC0Conf & CAN_u4CFCC_CFRXIE_DIS & CAN_u4CFCC_CFE_NOUSE;
            ptChReg->ptu4CFCC[ CAN_TRX_FIFO_1 ] = ptSetRSCANReg->u4CFCC1Conf & CAN_u4CFCC_CFRXIE_DIS & CAN_u4CFCC_CFE_NOUSE;
            ptChReg->ptu4CFCC[ CAN_TRX_FIFO_2 ] = ptSetRSCANReg->u4CFCC2Conf & CAN_u4CFCC_CFRXIE_DIS & CAN_u4CFCC_CFE_NOUSE;

            ptChReg->ptu4CFCCE[ CAN_TRX_FIFO_0 ] = CAN_u4CFCCE_INIT;
            ptChReg->ptu4CFCCE[ CAN_TRX_FIFO_1 ] = CAN_u4CFCCE_INIT;
            ptChReg->ptu4CFCCE[ CAN_TRX_FIFO_2 ] = CAN_u4CFCCE_INIT;
        }
    }

    *(Can_tb_stGlobalReg.ptu4RMNB) = CAN_u4RMNB_INIT;

    *(Can_tb_stGlobalReg.ptu4GRSTC) = CAN_u4GRSTC_INIT;

    *(Can_tb_stGlobalReg.ptu4GFCMC) = CAN_u4GFCMC_INIT;

    *(Can_tb_stGlobalReg.ptu4GFTBAC) = CAN_u4GFTBAC_INIT;

    *(Can_tb_stGlobalReg.ptu4GPFLECTR) = CAN_u4GPFLECTR_INIT;
}


/****************************************************************************/
/* Function Name | Can_st_SetChannelReg                                     */
/* Description   | Channel Register Use Set                                 */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 u1Controller                                       */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
static void
Can_st_SetChannelReg( uint8 u1Controller )
{
    CanConst CanTbChRegType *           ptChReg;
    CanConst CanTbSetRSCANRegType *     ptSetRSCANReg;
    uint32                              u4GSTS;

    u4GSTS = *(Can_tb_stGlobalReg.ptu4GSTS);
    if ( ( u4GSTS & CAN_u4GSTS_MODEALL_MSK ) == CAN_u4GSTS_GMODE_RESET )
    {
        *(Can_tb_stGlobalReg.ptu4GCFG) = Can_tb_u4GCFGConf;
    }

    ptChReg       = &Can_tb_stChReg[ u1Controller ];
    ptSetRSCANReg = &Can_tb_stSetRSCANReg[ u1Controller ];

    *(ptChReg->ptu4CmFDCFG) = ptSetRSCANReg->u4CmFDCFGConf;

    *(ptChReg->ptu4CmNCFG) = ptSetRSCANReg->u4CmNCFGConf;

    *(ptChReg->ptu4CmDCFG) = ptSetRSCANReg->u4CmDCFGConf;

    *(ptChReg->ptu4CmCTR) = ptSetRSCANReg->u4CmCTRConf | CAN_u4CMCTR_CHMDC_RESET_SET;

    ptChReg->ptu4TMIEC[CAN_IDX0] = CAN_u4TMIEC_INIT;
    ptChReg->ptu4TMIEC[CAN_IDX1] = CAN_u4TMIEC_INIT;

    *(ptChReg->ptu4TXQCC0) = CAN_u4TXQCC0_INIT;
    *(ptChReg->ptu4TXQCC1) = CAN_u4TXQCC1_INIT;
    *(ptChReg->ptu4TXQCC2) = CAN_u4TXQCC2_INIT;
    *(ptChReg->ptu4TXQCC3) = CAN_u4TXQCC3_INIT;

    *(ptChReg->ptu4THLCC) = CAN_u4THLCC_INIT;

    *(Can_tb_stGlobalReg.ptu4GERFL) = CAN_u4GERFL_CLEARALL;
}


/****************************************************************************/
/* Function Name | Can_st_StopGlobal                                        */
/* Description   | Global Register Stop Set                                 */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
static void
Can_st_StopGlobal( void )
{
    uint8    u1RxFifo;

    *(Can_tb_stGlobalReg.ptu4GCTR) = CAN_u4GCTR_INIT | CAN_u4GCTR_GMDC_RESET_SET;

    for ( u1RxFifo = (uint8)0U; u1RxFifo < (uint8)CAN_NUM_FIFO_RCV; u1RxFifo++ )
    {
        Can_tb_stGlobalReg.ptu4RFCC[ u1RxFifo ] = CAN_u4RFCC_INIT;
    }
}


/****************************************************************************/
/* Function Name | Can_st_StopChannel                                       */
/* Description   | Channel Communication Stop                               */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 u1Controller                                       */
/* Return Value  | uint8                                                    */
/*               |   CAN_PROC_OK                                            */
/*               |   CAN_PROC_BUSY                                          */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
static uint8
Can_st_StopChannel( uint8 u1Controller )
{
    CanConst CanTbChRegType *           ptChReg;
    CanConst CanTbSetRSCANRegType *     ptSetRSCANReg;
    uint8                               u1Ret;

    u1Ret = (uint8)CAN_PROC_BUSY;

    ptChReg       = &Can_tb_stChReg[ u1Controller ];
    ptSetRSCANReg = &Can_tb_stSetRSCANReg[ u1Controller ];

    ptChReg->ptu4CFCC[ CAN_TRX_FIFO_0 ] = ptSetRSCANReg->u4CFCC0Conf & CAN_u4CFCC_CFE_NOUSE;
    ptChReg->ptu4CFCC[ CAN_TRX_FIFO_1 ] = ptSetRSCANReg->u4CFCC1Conf & CAN_u4CFCC_CFE_NOUSE;
    ptChReg->ptu4CFCC[ CAN_TRX_FIFO_0 ] = ptSetRSCANReg->u4CFCC0Conf & CAN_u4CFCC_CFRXIE_DIS & CAN_u4CFCC_CFE_NOUSE;
    ptChReg->ptu4CFCC[ CAN_TRX_FIFO_1 ] = ptSetRSCANReg->u4CFCC1Conf & CAN_u4CFCC_CFRXIE_DIS & CAN_u4CFCC_CFE_NOUSE;

    ptChReg->ptu4CFCC[ CAN_TRX_FIFO_2 ] = ptSetRSCANReg->u4CFCC2Conf;

    ptChReg->ptu4CFCCE[ CAN_TRX_FIFO_0 ] = CAN_u4CFCCE_INIT;
    ptChReg->ptu4CFCCE[ CAN_TRX_FIFO_1 ] = CAN_u4CFCCE_INIT;
    ptChReg->ptu4CFCCE[ CAN_TRX_FIFO_2 ] = CAN_u4CFCCE_INIT;

    ptChReg->ptu4CFSTS[ CAN_TRX_FIFO_0 ] = CAN_u4CFSTS_CLEARALL;
    ptChReg->ptu4CFSTS[ CAN_TRX_FIFO_1 ] = CAN_u4CFSTS_CLEARALL;
    ptChReg->ptu4CFSTS[ CAN_TRX_FIFO_2 ] = CAN_u4CFSTS_CLEARALL;

    Can_st_ChannelMode_Any2Reset( u1Controller );

    if ( ( *(ptChReg->ptu4CmSTS) & CAN_u4CMSTS_MODEALL_MSK ) == CAN_u4CMSTS_CMODE_RESET )
    {
        ptChReg->ptu4TMIEC[CAN_IDX0] = CAN_u4TMIEC_INIT;
        ptChReg->ptu4TMIEC[CAN_IDX1] = CAN_u4TMIEC_INIT;

        *(ptChReg->ptu4TXQCC0) = CAN_u4TXQCC0_INIT;
        *(ptChReg->ptu4TXQCC1) = CAN_u4TXQCC1_INIT;
        *(ptChReg->ptu4TXQCC2) = CAN_u4TXQCC2_INIT;
        *(ptChReg->ptu4TXQCC3) = CAN_u4TXQCC3_INIT;

        *(ptChReg->ptu4THLCC)  = CAN_u4THLCC_INIT;

        u1Ret = (uint8)CAN_PROC_OK;
    }

    return ( u1Ret );
}


/****************************************************************************/
/* Function Name | Can_st_StartGlobal                                       */
/* Description   | Global Register Start Set                                */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
static void
Can_st_StartGlobal( void )
{
    Can_st_SetGlobalReg();

    Can_st_SetRxRule();

    Can_st_GlobalMode_Reset2Comm();
}


/****************************************************************************/
/* Function Name | Can_st_StartChannel                                      */
/* Description   | Channel Communication Start                              */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 u1Controller                                       */
/* Return Value  | uint8                                                    */
/*               |   CAN_PROC_OK                                            */
/*               |   CAN_PROC_BUSY                                          */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
static uint8
Can_st_StartChannel( uint8 u1Controller )
{
    CanConst CanTbChRegType *           ptChReg;
    CanConst CanTbSetRSCANRegType *     ptSetRSCANReg;
#if (CAN_CFG_TRANSMIT == CAN_USE)
    CanConst CanTbTxMbBitType *         ptTxMbBit;
    uint32                              u4TxMbUseBitMaskLo;
    uint32                              u4TxMbUseBitMaskHi;
    uint32                              u4TMTRSTSLo;
    uint32                              u4TMTRSTSHi;
#endif /* (CAN_CFG_TRANSMIT == CAN_USE) */
    uint8                               u1MBox;
    uint8                               u1Data;
    uint8                               u1Ret;

    u1Ret = (uint8)CAN_PROC_BUSY;

    ptChReg       = &Can_tb_stChReg[ u1Controller ];
    ptSetRSCANReg = &Can_tb_stSetRSCANReg[ u1Controller ];

#if (CAN_CFG_TRANSMIT == CAN_USE)
    ptTxMbBit          = &Can_tb_stTxMbBit[ u1Controller ];
    u4TxMbUseBitMaskLo = ( ptTxMbBit->u4TxIntrBit[CAN_IDX0] | ptTxMbBit->u4TxPollBit[CAN_IDX0] );
    u4TxMbUseBitMaskHi = ( ptTxMbBit->u4TxIntrBit[CAN_IDX1] | ptTxMbBit->u4TxPollBit[CAN_IDX1] );
    u4TMTRSTSLo        = ptChReg->ptu4TMTRSTS[CAN_IDX0];
    u4TMTRSTSHi        = ptChReg->ptu4TMTRSTS[CAN_IDX1];
    if ( ( ( u4TMTRSTSLo & u4TxMbUseBitMaskLo ) == CAN_u4BIT_NONE )
    &&   ( ( u4TMTRSTSHi & u4TxMbUseBitMaskHi ) == CAN_u4BIT_NONE ) )
#endif /* (CAN_CFG_TRANSMIT == CAN_USE) */
    {
        Can_st_ChannelMode_Any2Reset( u1Controller );
    }

    if ( ( *(ptChReg->ptu4CmSTS) & CAN_u4CMSTS_MODEALL_MSK ) == CAN_u4CMSTS_CMODE_RESET )
    {
        *(ptChReg->ptu4CmCTR)    = ptSetRSCANReg->u4CmCTRConf | CAN_u4CMCTR_CHMDC_RESET_SET;

        ptChReg->ptu4CFSTS[ CAN_TRX_FIFO_0 ] = CAN_u4CFSTS_CLEARALL;
        ptChReg->ptu4CFSTS[ CAN_TRX_FIFO_1 ] = CAN_u4CFSTS_CLEARALL;
        ptChReg->ptu4CFSTS[ CAN_TRX_FIFO_2 ] = CAN_u4CFSTS_CLEARALL;

        ptChReg->ptu4CFCCE[ CAN_TRX_FIFO_0 ] = CAN_u4CFCCE_INIT;
        ptChReg->ptu4CFCCE[ CAN_TRX_FIFO_1 ] = CAN_u4CFCCE_INIT;
        ptChReg->ptu4CFCCE[ CAN_TRX_FIFO_2 ] = CAN_u4CFCCE_INIT;

        ptChReg->ptu4CFCC[ CAN_TRX_FIFO_0 ] = ptSetRSCANReg->u4CFCC0Conf & CAN_u4CFCC_CFE_NOUSE;
        ptChReg->ptu4CFCC[ CAN_TRX_FIFO_1 ] = ptSetRSCANReg->u4CFCC1Conf & CAN_u4CFCC_CFE_NOUSE;
        ptChReg->ptu4CFCC[ CAN_TRX_FIFO_0 ] = ptSetRSCANReg->u4CFCC0Conf;
        ptChReg->ptu4CFCC[ CAN_TRX_FIFO_1 ] = ptSetRSCANReg->u4CFCC1Conf;

        ptChReg->ptu4CFCC[ CAN_TRX_FIFO_2 ] = ptSetRSCANReg->u4CFCC2Conf;

        for ( u1MBox = (uint8)0U; u1MBox < (uint8)CAN_NUM_BUF_SND_PER_CH; u1MBox++ )
        {
#if (CAN_CFG_TXBUF_NUM == 48U)
            if ( ( u1MBox < (uint8)CAN_MB016 )
            ||   ( u1MBox > (uint8)CAN_MB031 ) )
#endif /* (CAN_CFG_TXBUF_NUM == 48U) */
            {
                ptChReg->ptstTM[ u1MBox ].u4IDReg  = CAN_u4TMID_INIT;
                ptChReg->ptstTM[ u1MBox ].u4PTRReg = CAN_u4TMPTR_CLEARALL;

                ptChReg->ptstTM[ u1MBox ].u4FDCTRReg = CAN_u4TMFDCTR_CLEARALL;

                for ( u1Data = (uint8)0U; u1Data < (uint8)CAN_DATA_ARYSIZE_4BYTE; u1Data++ )
                {
                    ptChReg->ptstTM[ u1MBox ].u4DFReg[ u1Data ] = CAN_u4TMDF_CLEARALL;
                }
            }
        }

        ptChReg->ptu4TMIEC[CAN_IDX0] = Can_tb_stTxMbBit[ u1Controller ].u4TxIntrBit[CAN_IDX0];
        ptChReg->ptu4TMIEC[CAN_IDX1] = Can_tb_stTxMbBit[ u1Controller ].u4TxIntrBit[CAN_IDX1];

        *(ptChReg->ptu4TXQCC0) = CAN_u4TXQCC0_INIT;
        *(ptChReg->ptu4TXQCC1) = CAN_u4TXQCC1_INIT;
        *(ptChReg->ptu4TXQCC2) = CAN_u4TXQCC2_INIT;
        *(ptChReg->ptu4TXQCC3) = CAN_u4TXQCC3_INIT;

        *(ptChReg->ptu4THLCC)  = CAN_u4THLCC_INIT;

        Can_st_PreStart( u1Controller );

        Can_st_ChannelMode_Reset2Comm( u1Controller );
        if ( ( *(ptChReg->ptu4CmSTS) & CAN_u4CMSTS_MODEALL_MSK ) == CAN_u4CMSTS_CMODE_COMM )
        {
            u1Ret = (uint8)CAN_PROC_OK;
        }
    }

    return ( u1Ret );
}


/****************************************************************************/
/* Function Name | Can_st_ResetGlobal                                       */
/* Description   | Global Register Reinitialization                         */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | uint8                                                    */
/*               |   CAN_PROC_OK                                            */
/*               |   CAN_PROC_BUSY                                          */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
static uint8
Can_st_ResetGlobal( void )
{
    uint32    u4GSTS;
    uint8     u1Ret;

    u1Ret = (uint8)CAN_PROC_BUSY;

    *(Can_tb_stGlobalReg.ptu4GRSTC) = CAN_u4GRSTC_INIT;

    Can_st_GlobalMode_Any2Reset();

    u4GSTS = *(Can_tb_stGlobalReg.ptu4GSTS);
    if ( ( u4GSTS & CAN_u4GSTS_MODEALL_MSK ) == CAN_u4GSTS_GMODE_RESET )
    {
        Can_st_SetGlobalReg();

        Can_st_SetRxRule();

        u1Ret = (uint8)CAN_PROC_OK;
    }

    return ( u1Ret );
}


/****************************************************************************/
/* Function Name | Can_st_ResetChannel                                      */
/* Description   | Channel Reinitialization                                 */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 u1Controller                                       */
/* Return Value  | uint8                                                    */
/*               |   CAN_PROC_OK                                            */
/*               |   CAN_PROC_BUSY                                          */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
static uint8
Can_st_ResetChannel( uint8 u1Controller )
{
    uint8    u1Result;
    uint8    u1Ret;

    u1Ret = (uint8)CAN_PROC_BUSY;

    u1Result = Can_st_StopChannel( u1Controller );
    if ( u1Result == (uint8)CAN_PROC_OK )
    {
        Can_st_u1BRSUse[ u1Controller ] = Can_tb_u1BRSInitConf[ u1Controller ];

        Can_st_SetChannelReg( u1Controller );

        u1Ret = (uint8)CAN_PROC_OK;
    }

    return ( u1Ret );
}


/****************************************************************************/
/* Function Name | Can_st_SetRxRule                                         */
/* Description   | Register Set for Reception Rule                          */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
static void
Can_st_SetRxRule( void )
{
    uint32    u4Page;
    uint32    u4FlMask;
    uint16    u2MaxNumRxRule;
    uint16    u2RxRuleNo;
    uint8     u1RuleRegNo;
    uint8     u1MskIdx;

    Can_tb_stGlobalReg.ptu4GAFLCFG[ CAN_IDX0 ] = Can_tb_u4GAFLCFG0Conf;
#if (CAN_CFG_CONTROLLERNUM_MAX > 2U)
    Can_tb_stGlobalReg.ptu4GAFLCFG[ CAN_IDX1 ] = Can_tb_u4GAFLCFG1Conf;
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 2U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 4U)
    Can_tb_stGlobalReg.ptu4GAFLCFG[ CAN_IDX2 ] = Can_tb_u4GAFLCFG2Conf;
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 4U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 6U)
    Can_tb_stGlobalReg.ptu4GAFLCFG[ CAN_IDX3 ] = Can_tb_u4GAFLCFG3Conf;
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 6U) */

    u2MaxNumRxRule = Can_tb_u2MaxNumRxRule;
    for ( u2RxRuleNo = (uint16)0U; u2RxRuleNo < u2MaxNumRxRule; u2RxRuleNo++ )
    {
        u4Page = ( (uint32)( (uint32)u2RxRuleNo >> CAN_NUM_RULETABLE_PER_PAGE_SFT ) & CAN_u4GAFLECTR_AFLPN_MSK );

        u1RuleRegNo = (uint8)( u2RxRuleNo & (uint16)CAN_NUM_RULETABLE_PER_PAGE_MSK );

        *(Can_tb_stGlobalReg.ptu4GAFLECTR) = ( CAN_u4GAFLECTR_AFLDAE_ENA | u4Page );

        u1MskIdx = Can_tb_stRxRuleSetting[ u2RxRuleNo ].u1RxMaskRef;
        u4FlMask = Can_tb_u4RxMask[ u1MskIdx ];
        Can_tb_stGlobalReg.ptstGAFL[ u1RuleRegNo ].u4GAFLID = Can_tb_stRxRuleSetting[ u2RxRuleNo ].u4GAFLIDConf;
        Can_tb_stGlobalReg.ptstGAFL[ u1RuleRegNo ].u4GAFLM  = u4FlMask;
        Can_tb_stGlobalReg.ptstGAFL[ u1RuleRegNo ].u4GAFLP0 = Can_tb_stRxRuleSetting[ u2RxRuleNo ].u4GAFLP0Conf;
        Can_tb_stGlobalReg.ptstGAFL[ u1RuleRegNo ].u4GAFLP1 = Can_tb_stRxRuleSetting[ u2RxRuleNo ].u4GAFLP1Conf;
    }

    *(Can_tb_stGlobalReg.ptu4GAFLECTR) = CAN_u4GAFLECTR_AFLDAE_DIS;
}


/****************************************************************************/
/* Function Name | Can_st_PhyInit                                           */
/* Description   | State Management Function(MPU Reliance) Initialization   */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
static void
Can_st_PhyInit( void )
{
    uint8    u1Controller;
    uint8    u1CtrlNum;

    u1CtrlNum = Can_tb_u1CtrlNum;
    for ( u1Controller = (uint8)0U; u1Controller < u1CtrlNum; u1Controller++ )
    {
        Can_st_u1BRSUse[ u1Controller ] = Can_tb_u1BRSInitConf[ u1Controller ];
    }
}


#endif /* (CAN_CFG_CAN == CAN_USE) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-2-1         :2022/09/19                                              */
/*  v2-2-2         :2023/04/24                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
