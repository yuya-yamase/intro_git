/* bsw_cantp_st_c_v3-0-0                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANTP/ST/CODE                                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>
#include "../inc/bsw_cantp_MemMap.h"

#include <bswm_cs/bsw_bswm_cs.h>
#include <comm/bsw_comm.h>
#include "../../ComM/inc/bsw_comm_config.h"
#include "../../BswM_CS/inc/bsw_bswm_cs_config.h"

#if( BSW_BSWM_CS_FUNC_CANTP == BSW_USE )
#include <cantp/bsw_cantp.h>
#include <pdur/bsw_pdur.h>

#include "../cfg/CanTp_Cfg.h"
#include "../inc/bsw_cantp_cmn.h"

#include "../inc/bsw_cantp_config.h"

#include "../inc/bsw_cantp_st.h"
#include "../inc/bsw_cantp_rx.h"
#include "../inc/bsw_cantp_snd.h"

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
/* Function Name | bsw_cantp_st_MainFunction_Mode                           */
/* Description   | CANTP timer control                                      */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_cantp_st_MainFunction_Mode( void )
{
    BswConst Bsw_CanTp_CfgType *       pt_CfgTbl;             /* Pointer to CanTp configuration             */
    Bsw_CanTp_st_ReceiverStatType *    pt_ReceiverStatTbl;    /* Pointer to receiver status info            */
    Bsw_CanTp_st_SenderStatType *      pt_SenderStatTbl;      /* Pointer to sender status info              */
    uint16                             u2_ReceiverCycle;      /* MainFunction cycle count value of receiver */
    uint16                             u2_SenderCycle;        /* MainFunction cycle count value of sender   */
    uint16                             u2_TimerCycleMax;      /* MainFunction cycle count max value         */
    uint8                              u1_ChNum;              /* Number of Channels                         */
    uint8                              u1_ChId;               /* Channel ID                                 */

    /* Acquisition of pointer to configuration data structure */
    pt_CfgTbl = bsw_cantp_cmn_GetConfigTbl();
    if( pt_CfgTbl != NULL_PTR )
    {
        u1_ChNum = pt_CfgTbl->u1ChNum;

        u2_TimerCycleMax = bsw_cantp_u2TimerCycleMax;

        for( u1_ChId = (uint8)0U; u1_ChId < u1_ChNum; u1_ChId++ )
        {
            pt_ReceiverStatTbl = &(bsw_cantp_st_stChStatTbl[u1_ChId].stReceiverStatTbl);
            pt_SenderStatTbl = &(bsw_cantp_st_stChStatTbl[u1_ChId].stSenderStatTbl);

            /********************************************/
            /*******  Start of exclusive section  *******/

            /*--------------*/
            /* Timer Update */
            /*--------------*/
            u2_ReceiverCycle = pt_ReceiverStatTbl->u2ReceiverCycle;
            u2_SenderCycle   = pt_SenderStatTbl->u2SenderCycle;

            if( u2_ReceiverCycle > u2_TimerCycleMax )
            {   /* RAM broken */
                bsw_cantp_cmn_u1ErrState = BSW_CANTP_u1RAMERR;
                u2_ReceiverCycle = (uint16)0U;
            }
            else
            {
                if( u2_ReceiverCycle > (uint16)0U )
                {
                    u2_ReceiverCycle--;
                }
            }

            if( u2_SenderCycle > u2_TimerCycleMax )
            {   /* RAM broken */
                /* Note: If timer is in measuring STmin, CF Transmission may be hasty temporarily. */
                bsw_cantp_cmn_u1ErrState = BSW_CANTP_u1RAMERR;
                u2_SenderCycle = (uint16)0U;
            }
            else
            {
                if( u2_SenderCycle > (uint16)0U )
                {
                    u2_SenderCycle--;
                }
            }

            pt_ReceiverStatTbl->u2ReceiverCycle = u2_ReceiverCycle;
            pt_SenderStatTbl->u2SenderCycle     = u2_SenderCycle;

            /*******   End of exclusive section   *******/
            /********************************************/
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | bsw_cantp_st_InitCore                                    */
/* Description   | Initialize CANTP component core procedure                */
/* Preconditions | None                                                     */
/* Parameters    | ptCfgTbl : pointer to CanTp configuration                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_cantp_st_InitCore( BswConst Bsw_CanTp_CfgType * ptCfgTbl )
{
    Bsw_CanTp_st_ReceiverStatType *        pt_ReceiverStatTbl; /* Pointer to receiver status info  */
    Bsw_CanTp_st_SenderStatType *          pt_SenderStatTbl;   /* Pointer to sender status info    */
#if( BSW_CANTP_CFG_CHANGE_RXPARAM == BSW_USE )
    BswConst Bsw_CanTp_RxNSduCfgType *     pt_RxNSduCfgTbl;    /* Pointer to RxNSdu configuration  */
    uint16                                 u2_MaxRxNSduNum;    /* Number of Max RxNSdus            */
    uint16                                 u2_RxNSduIdx;       /* Index of RxNSdus                 */
    uint16                                 u2_BS;              /* Block size                       */
    uint16                                 u2_STmin;           /* Separation Time Minimum          */
#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
    uint16                                 u2_RxNSduNum;       /* Number of RxNSdus                */
    uint8                                  u1_ChNum;           /* Number of Channels               */
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
    BswConst Bsw_CanTp_RxNSduCfgType *     pt_FirstRxNSduCfg;  /* Pointer to First RxNSdu Cfg      */
    uint8                                  u1_RxParamPtn;      /* Rx Parameter Pattern             */
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */
#endif /* BSW_CANTP_CFG_CHANGE_RXPARAM == BSW_USE */
    uint8                                  u1_ChId;            /* Channel ID                       */
    uint8                                  u1_MaxChCnt;        /* Number of Max Channels           */
    uint8                                  u1_Loop;            /* Loop counter                     */

    /*---------------------------------------------------------------*/
    /* Initialization of the RAM according to the connection channel */
    /*---------------------------------------------------------------*/
    u1_MaxChCnt = bsw_cantp_u1MaxChCnt;
    for( u1_ChId = (uint8)0U; u1_ChId < u1_MaxChCnt; u1_ChId++ )
    {
        pt_SenderStatTbl                                 = &(bsw_cantp_st_stChStatTbl[u1_ChId].stSenderStatTbl);
        pt_SenderStatTbl->u4SenderRemainNSduLen          = 0UL;
        pt_SenderStatTbl->u2SenderNSduId                 = BSW_CANTP_u2NSDUID_NA;
        pt_SenderStatTbl->u2SenderCycle                  = (uint16)0U;
        pt_SenderStatTbl->u1SenderStat                   = BSW_CANTP_ST_u1STS_IDLE;
        pt_SenderStatTbl->u1SenderSN                     = BSW_CANTP_u1SN_INIT;
        pt_SenderStatTbl->u1SenderCFNum                  = (uint8)0U;
        pt_SenderStatTbl->u1SenderBS                     = (uint8)0U;
        pt_SenderStatTbl->u1SenderSTminCycle             = (uint8)0U;
        pt_SenderStatTbl->u1Padding[BSW_CANTP_OFFSET0]   = (uint8)0U;
        pt_SenderStatTbl->u1Padding[BSW_CANTP_OFFSET1]   = (uint8)0U;
        pt_SenderStatTbl->u1Padding[BSW_CANTP_OFFSET2]   = (uint8)0U;
        pt_ReceiverStatTbl                               = &(bsw_cantp_st_stChStatTbl[u1_ChId].stReceiverStatTbl);
        pt_ReceiverStatTbl->u4ReceiverRemainNSduLen      = 0UL;
        pt_ReceiverStatTbl->u2ReceiverNSduId             = BSW_CANTP_u2NSDUID_NA;
        pt_ReceiverStatTbl->u2ReceiverCycle              = (uint16)0U;
        pt_ReceiverStatTbl->u2ReceiverFCWaitCnt          = (uint16)0U;
        pt_ReceiverStatTbl->u1ReceiverStat               = BSW_CANTP_ST_u1STS_IDLE;
        pt_ReceiverStatTbl->u1ReceiverRXDL               = (uint8)0U;
        pt_ReceiverStatTbl->u1ReceiverSN                 = BSW_CANTP_u1SN_INIT;
        pt_ReceiverStatTbl->u1ReceiverCFNum              = (uint8)0U;
        pt_ReceiverStatTbl->u1ReceiverFS                 = BSW_CANTP_u1FS_RECEIVER_CTS;
        pt_ReceiverStatTbl->u1ReceiverAcceptedReqCnt     = (uint8)0U;
    }
    /*-----------------------------------------------*/
    /* Initialization of the RAM according to RxNSdu */
    /*-----------------------------------------------*/
#if( BSW_CANTP_CFG_CHANGE_RXPARAM == BSW_USE )
    /* Clear all the RAM according to RxNSdu */
    u2_MaxRxNSduNum = bsw_cantp_u2MaxRxNSduNum;
    for( u2_RxNSduIdx = (uint16)0U; u2_RxNSduIdx < u2_MaxRxNSduNum; u2_RxNSduIdx++ )
    {
        bsw_cantp_stBSSTminTbl[u2_RxNSduIdx].u2BS    = (uint16)0U;
        bsw_cantp_stBSSTminTbl[u2_RxNSduIdx].u2STmin = (uint16)0U;
    }
#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
    /* Initialization all the RAM according to using RxNSdu by config value */
    u1_ChNum = ptCfgTbl->u1ChNum;
    for( u1_ChId = (uint8)0U; u1_ChId < u1_ChNum; u1_ChId++ )
    {
        u2_RxNSduNum = ptCfgTbl->ptChCfgTbl[u1_ChId].u2RxNSduNum;

        for( u2_RxNSduIdx = (uint16)0U; u2_RxNSduIdx < u2_RxNSduNum; u2_RxNSduIdx++ )
        {
            pt_RxNSduCfgTbl = &(ptCfgTbl->ptChCfgTbl[u1_ChId].ptRxNSduCfgTbl[u2_RxNSduIdx]);

            u2_BS = (uint16)(pt_RxNSduCfgTbl->u1BlockSize);
            u2_STmin = (uint16)(pt_RxNSduCfgTbl->u1STmin);

            bsw_cantp_rx_ChangeParamBS( pt_RxNSduCfgTbl, u2_BS );
            bsw_cantp_rx_ChangeParamSTmin( pt_RxNSduCfgTbl, u2_STmin );
        }
    }
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
    /* Note: In order to get the start address of the NSdu configuration table, refer to 0CH and the 0th NSdu.                          */
    /*       To access NSdu configuration table using NSduId as a key, the start address of the NSdu configuration table is required.   */
    pt_FirstRxNSduCfg = &(ptCfgTbl->ptChCfgTbl[0U].ptRxNSduCfgTbl[0U]);
    for( u2_RxNSduIdx = (uint16)0U; u2_RxNSduIdx < u2_MaxRxNSduNum; u2_RxNSduIdx++ )
    {
        pt_RxNSduCfgTbl = &(pt_FirstRxNSduCfg[u2_RxNSduIdx]);
        u1_RxParamPtn = pt_RxNSduCfgTbl->u1RxParamPtn;
        u2_BS = (uint16)(bsw_cantp_stRxNSduParamTbl[u1_RxParamPtn].u1BlockSize);
        u2_STmin = (uint16)(bsw_cantp_stRxNSduParamTbl[u1_RxParamPtn].u1STmin);

        bsw_cantp_rx_ChangeParamBSByIdx( u2_RxNSduIdx, u2_BS );
        bsw_cantp_rx_ChgParamSTminByIdx( u2_RxNSduIdx, u2_STmin );
    }
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */
#endif /* BSW_CANTP_CFG_CHANGE_RXPARAM == BSW_USE */

    /*------------------------------------------------*/
    /* Initialization of the SF/FF/CF/FC frame buffer */
    /*------------------------------------------------*/
    for( u1_Loop = (uint8)0U; u1_Loop < BSW_CANTP_u1CAN_DL_64; u1_Loop++ )
    {
        bsw_cantp_cmn_u1TxBuffer[u1_Loop] = (uint8)0U;
    }

    /*--------------------------------------------------------*/
    /* Initialization of the RAM according to the Error State */
    /*--------------------------------------------------------*/
    bsw_cantp_cmn_u1ErrState = BSW_CANTP_u1ERRNONE;

    /*--------------------------------------------------------*/
    /* Initialization of the  RAM holding Latest Rx NSdu ID   */
    /*--------------------------------------------------------*/
#if( BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE )
    bsw_cantp_cmn_u2LatestRxNSduId = BSW_CANTP_u2NSDUID_NA;
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */

    /*--------------------------------*/
    /* Initialization of Send Control */
    /*--------------------------------*/
    bsw_cantp_snd_InitSnd();

    return;
}


/****************************************************************************/
/* Function Name | bsw_cantp_st_ShutdownCore                                */
/* Description   | Shutdown CANTP component core procedure                  */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_cantp_st_ShutdownCore( void )
{
    bsw_cantp_cmn_u1ErrState = BSW_CANTP_u1ERRNONE;

    return;
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#endif /* BSW_BSWM_CS_FUNC_CANTP == BSW_USE */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/09/25                                             */
/*  v1-1-0          :2019/02/25                                             */
/*  v1-2-0          :2020/02/03                                             */
/*  v2-0-0          :2021/09/09                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
