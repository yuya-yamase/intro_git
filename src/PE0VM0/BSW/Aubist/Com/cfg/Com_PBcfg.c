/* com_pbcfg_c_v3-0-0                                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | COM/PBCFG/CODE                                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>
#include "../inc/bsw_com_MemMap.h"
#include <ComStack_Types.h>

#include <bswm_cs/bsw_bswm_cs.h>
#include <comm/bsw_comm.h>
#include "../../ComM/inc/bsw_comm_config.h"
#include "../../BswM_CS/inc/bsw_bswm_cs_config.h"
#if (BSW_BSWM_CS_FUNC_COM == BSW_USE)

#include <com/bsw_com.h>
#include "Com_Cfg.h"
#include "../inc/bsw_com_st.h"
#include "../inc/bsw_com_tx.h"
#include "../inc/bsw_com_rx.h"
#include "../inc/bsw_com_fs.h"
#include "../inc/bsw_com_data.h"
#include "../inc/bsw_com_config.h"


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
BswU1 bsw_com_data_u1MsgBuf[BSW_COM_MSGBUF_SIZE];


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
BswConst BswU1 bsw_com_data_u1MsgBufInit[BSW_COM_MSGBUF_SIZE] = {
     (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [0] MSG_BDC1S81_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U                                                                        /* Padding Area */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [1] MSG_BDC1S91_RXCH1 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U                                                                        /* Padding Area */
};

#if (BSW_COM_CFG_FAILSAFE_SIZE != 0U)
BswConst BswU1 bsw_com_data_u1MsgBufFail[BSW_COM_FAILSAFE_SIZE] = {
};
#endif /* (BSW_COM_CFG_FAILSAFE_SIZE != 0U) */

#if (BSW_COM_CFG_FAILSAFE_SIZE != 0U)
BswConst BswU1 bsw_com_data_u1FailMskTbl[BSW_COM_FAILSAFE_SIZE] = {
};
#endif /* (BSW_COM_CFG_FAILSAFE_SIZE != 0U) */

BswConst Bsw_Com_DataInfoType bsw_com_stDataInfoTbl[BSW_COM_HANDLE_NUM] = {
     BSW_COM_u1EVCOND_NONE                                                                                       /* [0] ComConf_ComSignal_E_CRC1E3_0 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1] ComConf_ComSignal_E_CNT1E3_0 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [2] ComConf_ComSignal_VPSINFO7_0 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [3] ComConf_ComSignal_VPSINFO6_0 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [4] ComConf_ComSignal_VPSINFO5_0 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [5] ComConf_ComSignal_VPSINFO4_0 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [6] ComConf_ComSignal_VPSINFO3_0 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [7] ComConf_ComSignal_VPSINFO2_0 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [8] ComConf_ComSignal_VPSINFO1_0 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [9] ComConf_ComSignal_VPSINFOS_0 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [10] ComConf_ComSignal_VPSCNG_0 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [11] ComConf_ComSignal_VPSISOTA_0 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [12] ComConf_ComSignal_APOFRQ_0 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [13] ComConf_ComSignal_FV1E3_D_0 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [14] ComConf_ComSignal_KZK1E3_D_0 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [15] ComConf_ComSignal_E_CRC1E4_2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [16] ComConf_ComSignal_E_CNT1E4_2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [17] ComConf_ComSignal_VPSINF7S_2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [18] ComConf_ComSignal_VPSINF6S_2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [19] ComConf_ComSignal_VPSINF5S_2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [20] ComConf_ComSignal_VPSINF4S_2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [21] ComConf_ComSignal_VPSINF3S_2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [22] ComConf_ComSignal_VPSINF2S_2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [23] ComConf_ComSignal_VPSINF1S_2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [24] ComConf_ComSignal_VPSINFSS_2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [25] ComConf_ComSignal_VPSOTAS_2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [26] ComConf_ComSignal_APOFRQS_2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [27] ComConf_ComSignal_FV1E4_D_2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [28] ComConf_ComSignal_KZK1E4_D_2 */
};

BswConst PduIdType bsw_com_u2DataHdl2MsgHdl[BSW_COM_HANDLE_NUM] = {
     (BswU2)0U                                                                                                   /* [0] ComConf_ComSignal_E_CRC1E3_0 */
    ,(BswU2)0U                                                                                                   /* [1] ComConf_ComSignal_E_CNT1E3_0 */
    ,(BswU2)0U                                                                                                   /* [2] ComConf_ComSignal_VPSINFO7_0 */
    ,(BswU2)0U                                                                                                   /* [3] ComConf_ComSignal_VPSINFO6_0 */
    ,(BswU2)0U                                                                                                   /* [4] ComConf_ComSignal_VPSINFO5_0 */
    ,(BswU2)0U                                                                                                   /* [5] ComConf_ComSignal_VPSINFO4_0 */
    ,(BswU2)0U                                                                                                   /* [6] ComConf_ComSignal_VPSINFO3_0 */
    ,(BswU2)0U                                                                                                   /* [7] ComConf_ComSignal_VPSINFO2_0 */
    ,(BswU2)0U                                                                                                   /* [8] ComConf_ComSignal_VPSINFO1_0 */
    ,(BswU2)0U                                                                                                   /* [9] ComConf_ComSignal_VPSINFOS_0 */
    ,(BswU2)0U                                                                                                   /* [10] ComConf_ComSignal_VPSCNG_0 */
    ,(BswU2)0U                                                                                                   /* [11] ComConf_ComSignal_VPSISOTA_0 */
    ,(BswU2)0U                                                                                                   /* [12] ComConf_ComSignal_APOFRQ_0 */
    ,(BswU2)0U                                                                                                   /* [13] ComConf_ComSignal_FV1E3_D_0 */
    ,(BswU2)0U                                                                                                   /* [14] ComConf_ComSignal_KZK1E3_D_0 */
    ,(BswU2)1U                                                                                                   /* [15] ComConf_ComSignal_E_CRC1E4_2 */
    ,(BswU2)1U                                                                                                   /* [16] ComConf_ComSignal_E_CNT1E4_2 */
    ,(BswU2)1U                                                                                                   /* [17] ComConf_ComSignal_VPSINF7S_2 */
    ,(BswU2)1U                                                                                                   /* [18] ComConf_ComSignal_VPSINF6S_2 */
    ,(BswU2)1U                                                                                                   /* [19] ComConf_ComSignal_VPSINF5S_2 */
    ,(BswU2)1U                                                                                                   /* [20] ComConf_ComSignal_VPSINF4S_2 */
    ,(BswU2)1U                                                                                                   /* [21] ComConf_ComSignal_VPSINF3S_2 */
    ,(BswU2)1U                                                                                                   /* [22] ComConf_ComSignal_VPSINF2S_2 */
    ,(BswU2)1U                                                                                                   /* [23] ComConf_ComSignal_VPSINF1S_2 */
    ,(BswU2)1U                                                                                                   /* [24] ComConf_ComSignal_VPSINFSS_2 */
    ,(BswU2)1U                                                                                                   /* [25] ComConf_ComSignal_VPSOTAS_2 */
    ,(BswU2)1U                                                                                                   /* [26] ComConf_ComSignal_APOFRQS_2 */
    ,(BswU2)1U                                                                                                   /* [27] ComConf_ComSignal_FV1E4_D_2 */
    ,(BswU2)1U                                                                                                   /* [28] ComConf_ComSignal_KZK1E4_D_2 */
};

BswConst Bsw_Com_MsgInfoType bsw_com_stMsgInfoTbl[BSW_COM_MSG_NUM] = {
     { BSW_COM_u2MILSEC( 3000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [0] MSG_BDC1S81_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(  900U), BSW_COM_u1CH01, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [1] MSG_BDC1S91_RXCH1 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
};

BswConst BswU4 bsw_com_u4SysStatTbl[BSW_COM_MSG_NUM][BSW_COM_SYSSTATTBLNUM] =
{
     {    /* [0] MSG_BDC1S81_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_BAT|BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_PBA|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [1] MSG_BDC1S91_RXCH1 */
          ( BSW_COM_u4IPDUGROUP_BAT|BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_PBA|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
};

#if (BSW_COM_TX_MSG_NUM != 0U)
BswConst Bsw_Com_TickTimeType bsw_com_u2TxDelayTbl[BSW_COM_TX_MSG_NUM] = {
};
#endif /* (BSW_COM_TX_MSG_NUM != 0U) */

BswConst Bsw_Com_MsgOffsetType bsw_com_u2MsgOffsTbl[BSW_COM_MSG_NUM] = {
     (BswU2)0U                                                                                                   /* [0] MSG_BDC1S81_RXCH0 */
    ,(BswU2)35U                                                                                                  /* [1] MSG_BDC1S91_RXCH1 */
};

#if( BSW_COM_CFG_METADATA_USE == BSW_USE )
BswConst BswU1 bsw_com_u1MetaDataSizeTbl[BSW_COM_MSG_NUM] = {
};
#endif /* BSW_COM_CFG_METADATA_USE == BSW_USE */

BswConst Bsw_Com_NetInfoType bsw_com_stNetInfoTxMsgTbl[BSW_COM_NETWORK_NUM] = {
     { (BswU2)0U,   (BswU2)0U   }                                                                                /* [0] CH0  */
    ,{ (BswU2)0U,   (BswU2)0U   }                                                                                /* [1] CH1  */
    ,{ (BswU2)0U,   (BswU2)0U   }                                                                                /* [2] CH2  */
    ,{ (BswU2)0U,   (BswU2)0U   }                                                                                /* [3] CH3  */
    ,{ (BswU2)0U,   (BswU2)0U   }                                                                                /* [4] CH4  */
};

BswConst Bsw_Com_NetInfoType bsw_com_stNetInfoRxMsgTbl[BSW_COM_NETWORK_NUM] = {
     { (BswU2)0U,   (BswU2)1U   }                                                                                /* [0] CH0 CANFD_G2M_1_BUS */
    ,{ (BswU2)1U,   (BswU2)1U   }                                                                                /* [1] CH1 CANFD_G2M_2_BUS */
    ,{ (BswU2)0U,   (BswU2)0U   }                                                                                /* [2] CH2  */
    ,{ (BswU2)0U,   (BswU2)0U   }                                                                                /* [3] CH3  */
    ,{ (BswU2)0U,   (BswU2)0U   }                                                                                /* [4] CH4  */
};

#if (BSW_COM_CFG_TX_DLYBYMSG_USE == BSW_USE)
#if (BSW_COM_TX_MSG_NUM != 0U)
BswConst Bsw_Com_TickTimeType bsw_com_u2DelayTbl[BSW_COM_TX_MSG_NUM] = {
};
#endif /* (BSW_COM_TX_MSG_NUM != 0U) */
#endif /* BSW_COM_CFG_TX_DLYBYMSG_USE == BSW_USE */

#if ( (BSW_COM_CFG_TX_DLYBYMSG_USE == BSW_USE) && (BSW_COM_CFG_TX_DLYSW_USE == BSW_USE) )
#if (BSW_COM_TX_MSG_NUM != 0U)
BswConst Bsw_Com_TickTimeType bsw_com_u2PrdDelayTbl[BSW_COM_TX_MSG_NUM] = {
};
#endif /* (BSW_COM_TX_MSG_NUM != 0U) */
#endif /* (BSW_COM_CFG_TX_DLYBYMSG_USE == BSW_USE) && (BSW_COM_CFG_TX_DLYSW_USE == BSW_USE) */

#if (BSW_COM_CFG_TX_TIMEOUT_USE == BSW_USE)
#if (BSW_COM_TX_MSG_NUM != 0U)
BswConst Bsw_Com_TickTimeType bsw_com_u2TxTimeoutTbl[BSW_COM_TX_MSG_NUM] = {
};
#endif /* (BSW_COM_TX_MSG_NUM != 0U) */
#if ( (BSW_COM_TX_MSG_NUM != 0U) && (BSW_COM_FIRSTTXTIMEOUT_USE == BSW_USE) )
BswConst Bsw_Com_TickTimeType bsw_com_u2FirstTxTimeoutTbl[BSW_COM_TX_MSG_NUM] = {
};
#endif /* (BSW_COM_TX_MSG_NUM != 0U) && (BSW_COM_FIRSTTXTIMEOUT_USE == BSW_USE) */
#endif /* BSW_COM_CFG_TX_TIMEOUT_USE == BSW_USE */

#if (BSW_COM_ALIVECOUNTER_PTN2_USE == BSW_USE)
#if (BSW_COM_TX_ALVCNTMSG_NUM != 0U)
BswConst Bsw_Com_AliveInfoType bsw_com_AlvCnt2TxInfo[BSW_COM_TX_MSG_NUM] =
{
};
#endif /* (BSW_COM_TX_ALVCNTMSG_NUM != 0U) */
#if (BSW_COM_RX_ALVCNTMSG_NUM != 0U)
BswConst Bsw_Com_AliveInfoType bsw_com_AlvCnt2RxInfo[BSW_COM_RX_MSG_NUM] =
{
};
#endif /* (BSW_COM_RX_ALVCNTMSG_NUM != 0U) */
#endif /* (BSW_COM_CFG_CHx_ALVCNTR_PTN == BSW_COM_ALIVECOUNTER_PTN2) */

#if (BSW_COM_ALIVECOUNTER_PTN3_USE == BSW_USE)
#if (BSW_COM_TX_ALVCNT3MSG_NUM != 0U)
BswConst Bsw_Com_AlvCnt3TxInfoType bsw_com_AlvCnt3TxInfo[BSW_COM_TX_MSG_NUM] =
{
};
#endif /* (BSW_COM_TX_ALVCNT3MSG_NUM != 0U) */
#if (BSW_COM_RX_ALVCNT3MSG_NUM != 0U)
BswConst Bsw_Com_AlvCnt3RxInfoType bsw_com_AlvCnt3RxInfo[BSW_COM_RX_MSG_NUM] =
{
};
#endif /* (BSW_COM_RX_ALVCNT3MSG_NUM != 0U) */
#endif /* (BSW_COM_CFG_CHx_ALVCNTR_PTN == BSW_COM_ALIVECOUNTER_PTN3) */

#if (BSW_COM_RX_MSG_NUM != 0U)
BswConst Bsw_Com_TickTimeType bsw_com_u2PwonMsk[BSW_COM_RX_MSG_NUM] = {

     BSW_COM_u2MILSEC(3000U)                                                    /* [0] MSG_BDC1S81_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [1] MSG_BDC1S91_RXCH1 */
};

BswConst Bsw_Com_TickTimeType bsw_com_u2WakeupMsk[BSW_COM_RX_MSG_NUM] = {

     BSW_COM_u2MILSEC(3000U)                                                    /* [0] MSG_BDC1S81_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [1] MSG_BDC1S91_RXCH1 */
};
#endif /* (BSW_COM_RX_MSG_NUM != 0U) */

/* Send N Times Information (MessageID, Interval, Send-Times, Extend) */
#if (BSW_COM_CFG_SENDNTIMES_MSG_NUM != 0U)
BswConst Bsw_Com_NTimesInfoType bsw_com_tx_stSendNTimesInfo[BSW_COM_CFG_SENDNTIMES_MSG_NUM] =
{
};
#endif /* (BSW_COM_CFG_SENDNTIMES_MSG_NUM != 0U) */

/* Change Period Information (MessageID, Changing Interval, Send-Times, Off ImmSend, TimerRetrigger, Extend) */
#if (BSW_COM_CFG_CHGPERIOD_MSG_NUM != 0U)
BswConst Bsw_Com_ChgPrdInfoType bsw_com_tx_stChgPeriodIpduInfo[BSW_COM_CFG_CHGPERIOD_MSG_NUM] =
{
};
#endif /* (BSW_COM_CFG_CHGPERIOD_MSG_NUM != 0U) */

#if (BSW_COM_CFG_BACKUPPDU_USE == BSW_USE)
BswConst PduIdType bsw_com_data_u2BackupPduId[BSW_COM_CFG_BACKUPPDU_NUM] =
{
};
#endif /* (BSW_COM_CFG_BACKUPPDU_USE == BSW_USE) */

#if ( BSW_COM_FUNC_PNCIPDU == BSW_USE )
BswConst BswU4 bsw_com_u4PncStatTbl[BSW_COM_MSG_NUM][BSW_COM_PNC_REQNUM] = 
{
     {    /* [0] MSG_BDC1S81_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_44 )
     }
    ,{    /* [1] MSG_BDC1S91_RXCH1 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_44 )
     }
};

#if (BSW_COM_RX_MSG_NUM != 0U)
BswConst Bsw_Com_TickTimeType bsw_com_u2PnconMsk[BSW_COM_RX_MSG_NUM] = {

     BSW_COM_u2MILSEC(3000U)                                                    /* [0] MSG_BDC1S81_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [1] MSG_BDC1S91_RXCH1 */
};
#endif /* (BSW_COM_RX_MSG_NUM != 0U) */
#endif /* ( BSW_COM_FUNC_PNCIPDU == BSW_USE ) */

#if (BSW_COM_TX_DISTIMBYMSG == BSW_USE)
#if (BSW_COM_TX_MSG_NUM != 0U)
BswConst Bsw_Com_TickTimeType bsw_com_u2SendStartPwTbl[BSW_COM_TX_MSG_NUM] = {
};

BswConst Bsw_Com_TickTimeType bsw_com_u2DisableSendTbl[BSW_COM_TX_MSG_NUM] = {
};

BswConst Bsw_Com_TickTimeType bsw_com_u2EnablePeriodicTbl[BSW_COM_TX_MSG_NUM] = {
};
#endif /* (BSW_COM_TX_MSG_NUM != 0U) */
#endif /* BSW_COM_TX_DISTIMBYMSG == BSW_USE */

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


#endif /* (BSW_BSWM_CS_FUNC_COM == BSW_USE) */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/10/16                                             */
/*  v1-1-0          :2018/12/17                                             */
/*  v1-2-0          :2019/12/06                                             */
/*  v2-0-0          :2021/12/09                                             */
/*  v2-1-0          :2022/06/17                                             */
/*  v2-2-0          :2023/05/23                                             */
/*  v3-0-0          :2024/11/11                                             */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v3-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
