/* bsw_com_config_c_v2-2-0                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/COM/CONFIG/CODE                                       */
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

#include <bswm_cs/bsw_bswm_cs_com.h>
#include <com/bsw_com.h>

#include "../cfg/Com_Cfg.h"
#include "../inc/bsw_com_config.h"
#include "../inc/bsw_com_st.h"
#include "../inc/bsw_com_tx.h"
#include "../inc/bsw_com_rx.h"
#include "../inc/bsw_com_fs.h"
#include "../inc/bsw_com_data.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#if (BSW_COM_TX_TIMEOUT_USE == BSW_USE)
#define BSW_COM_INITALLTXREQST_FUNC    (&bsw_com_tx_InitAllTxReqSt)
#define BSW_COM_INITTXREQST_FUNC       (&bsw_com_tx_InitTxReqStat)
#define BSW_COM_SETTXREQST_FUNC        (&bsw_com_tx_SetTxReqStat)
#define BSW_COM_GETTXREQST_FUNC        (&bsw_com_tx_GetTxReqStat)
#define BSW_COM_TRANSCFM_FUNC          (&bsw_com_tx_TransmitCfm)
#define BSW_COM_TXTIMEOUT_FUNC         (&bsw_com_tx_TxTimeout)
#else
#define BSW_COM_INITALLTXREQST_FUNC    (&bsw_com_tx_InitAllTxReqStNone)
#define BSW_COM_INITTXREQST_FUNC       (&bsw_com_tx_InitTxReqStatNone)
#define BSW_COM_SETTXREQST_FUNC        (&bsw_com_tx_SetTxReqStatNone)
#define BSW_COM_GETTXREQST_FUNC        (&bsw_com_tx_GetTxReqStatNone)
#define BSW_COM_TRANSCFM_FUNC          (&bsw_com_tx_TransmitCfmNone)
#define BSW_COM_TXTIMEOUT_FUNC         (&bsw_com_tx_TxTimeoutNone)
#endif

#define BSW_COM_ALIVECOUNTER_PTN_CH(ch)    (BSW_COM_ALIVECOUNTER_PTN_CH##ch)

#define BSW_COM_ALIVECOUNTER_FUNC_TX(ch)   BSW_COM_ALVCNTPTNTX_PTN0_USE(ch)
#define BSW_COM_ALVCNTPTNTX_PTN0_USE(ch)   ((BSW_COM_ALIVECOUNTER_PTN_CH(ch) == BSW_COM_ALIVECOUNTER_PTN0) ? &bsw_com_fs_AliveCounterTx0 : BSW_COM_ALVCNTPTNTX_PTN1_USE(ch))
#define BSW_COM_ALVCNTPTNTX_PTN1_USE(ch)   ((BSW_COM_ALIVECOUNTER_PTN_CH(ch) == BSW_COM_ALIVECOUNTER_PTN1) ? &bsw_com_fs_AliveCounterTx1 : BSW_COM_ALVCNTPTNTX_PTN2_USE(ch))
#define BSW_COM_ALVCNTPTNTX_PTN2_USE(ch)   ((BSW_COM_ALIVECOUNTER_PTN_CH(ch) == BSW_COM_ALIVECOUNTER_PTN2) ? &bsw_com_fs_AliveCounterTx2 : BSW_COM_ALVCNTPTNTX_PTN3_USE(ch))
#define BSW_COM_ALVCNTPTNTX_PTN3_USE(ch)   ((BSW_COM_ALIVECOUNTER_PTN_CH(ch) == BSW_COM_ALIVECOUNTER_PTN3) ? &bsw_com_fs_AliveCounterTx3 : &bsw_com_fs_AliveCounterTxNone)

#define BSW_COM_ALIVECOUNTER_FUNC_RX(ch)   BSW_COM_ALVCNTPTNRX_PTN0_USE(ch)
#define BSW_COM_ALVCNTPTNRX_PTN0_USE(ch)   ((BSW_COM_ALIVECOUNTER_PTN_CH(ch) == BSW_COM_ALIVECOUNTER_PTN0) ? &bsw_com_fs_AliveCounterRx0 : BSW_COM_ALVCNTPTNRX_PTN1_USE(ch))
#define BSW_COM_ALVCNTPTNRX_PTN1_USE(ch)   ((BSW_COM_ALIVECOUNTER_PTN_CH(ch) == BSW_COM_ALIVECOUNTER_PTN1) ? &bsw_com_fs_AliveCounterRx1 : BSW_COM_ALVCNTPTNRX_PTN2_USE(ch))
#define BSW_COM_ALVCNTPTNRX_PTN2_USE(ch)   ((BSW_COM_ALIVECOUNTER_PTN_CH(ch) == BSW_COM_ALIVECOUNTER_PTN2) ? &bsw_com_fs_AliveCounterRx2 : BSW_COM_ALVCNTPTNRX_PTN3_USE(ch))
#define BSW_COM_ALVCNTPTNRX_PTN3_USE(ch)   ((BSW_COM_ALIVECOUNTER_PTN_CH(ch) == BSW_COM_ALIVECOUNTER_PTN3) ? &bsw_com_fs_AliveCounterRx3 : &bsw_com_fs_AliveCounterRxNone)

#define BSW_COM_ALIVECOUNTER_FUNC_POS(ch)  BSW_COM_ALVCNTPTNPOS_PTN0_USE(ch)
#define BSW_COM_ALVCNTPTNPOS_PTN0_USE(ch)  ((BSW_COM_ALIVECOUNTER_PTN_CH(ch) == BSW_COM_ALIVECOUNTER_PTN0) ? &bsw_com_fs_AliveCounterPosTx0 : BSW_COM_ALVCNTPTNPOS_PTN1_USE(ch))
#define BSW_COM_ALVCNTPTNPOS_PTN1_USE(ch)  ((BSW_COM_ALIVECOUNTER_PTN_CH(ch) == BSW_COM_ALIVECOUNTER_PTN1) ? &bsw_com_fs_AliveCounterPosTx1 : BSW_COM_ALVCNTPTNPOS_PTN2_USE(ch))
#define BSW_COM_ALVCNTPTNPOS_PTN2_USE(ch)  ((BSW_COM_ALIVECOUNTER_PTN_CH(ch) == BSW_COM_ALIVECOUNTER_PTN2) ? &bsw_com_fs_AliveCounterPosTx2 : BSW_COM_ALVCNTPTNPOS_PTN3_USE(ch))
#define BSW_COM_ALVCNTPTNPOS_PTN3_USE(ch)  ((BSW_COM_ALIVECOUNTER_PTN_CH(ch) == BSW_COM_ALIVECOUNTER_PTN3) ? &bsw_com_fs_AliveCounterPosTx3 : &bsw_com_fs_AlvCntPosTxNone)

#if (BSW_COM_CFG_SENDNTIMES_MSG_NUM > 0U)
#define BSW_COM_SENDNTIMESCNT_FUNC     (&bsw_com_tx_SendNTimesCnt)
#define BSW_COM_CHGPERITONTIM_FUNC     (&bsw_com_tx_ChgPeriToNTimes)
#define BSW_COM_SENDNTIMESMSG_FUNC     (&bsw_com_tx_SendNTimesMsg)
#define BSW_COM_SETTXREQNTIMTIMER_FUNC (&bsw_com_tx_SetTxReqNTimTimer)
#define BSW_COM_SETTXFINNTIMTIMER_FUNC (&bsw_com_tx_SetTxFinNTimTimer)
#define BSW_COM_CLRSENDNTIMESCH_FUNC   (&bsw_com_tx_ClearSendNTimesCh)
#define BSW_COM_CLRSENDNTIMESMSG_FUNC  (&bsw_com_tx_ClearSendNTimesMsg)
#define BSW_COM_INITSENDNTIMES_FUNC    (&bsw_com_tx_InitSendNTimes)
#else
#define BSW_COM_SENDNTIMESCNT_FUNC     (&bsw_com_tx_SendNTimesCntNone)
#define BSW_COM_CHGPERITONTIM_FUNC     (&bsw_com_tx_ChgPeriToNTimesNone)
#define BSW_COM_SENDNTIMESMSG_FUNC     (&bsw_com_tx_SendNTimesMsgNone)
#define BSW_COM_SETTXREQNTIMTIMER_FUNC (&bsw_com_tx_SetTxReqNTimerNone)
#define BSW_COM_SETTXFINNTIMTIMER_FUNC (&bsw_com_tx_SetTxFinNTimerNone)
#define BSW_COM_CLRSENDNTIMESCH_FUNC   (&bsw_com_tx_ClrSndNTimesChNone)
#define BSW_COM_CLRSENDNTIMESMSG_FUNC  (&bsw_com_tx_ClrSndNTimesMsgNone)
#define BSW_COM_INITSENDNTIMES_FUNC    (&bsw_com_tx_InitSndNTimesNone)
#endif /* BSW_COM_CFG_SENDNTIMES_MSG_NUM > 0U */

#if (BSW_COM_CFG_CHGPERIOD_MSG_NUM > 0U)
#define BSW_COM_CHGPRDCNT_FUNC         (&bsw_com_tx_ChgPrdIpduCnt)
#define BSW_COM_SETTXREQCHGPRD_FUNC    (&bsw_com_tx_SetTxReqChgPrdTimer)
#define BSW_COM_SETTXFINCHGPRD_FUNC    (&bsw_com_tx_SetTxFinChgPrdTimer)
#define BSW_COM_INITCHGPRD_FUNC        (&bsw_com_tx_InitChgPrdIpdu)
#define BSW_COM_GETCHGPRDSTAT_FUNC     (&bsw_com_tx_GetChgPrdIpduStat)
#else
#define BSW_COM_CHGPRDCNT_FUNC         (&bsw_com_tx_ChgPrdIpduCntNone)
#define BSW_COM_SETTXREQCHGPRD_FUNC    (&bsw_com_tx_SetTxReqChgPrdTmrNn)
#define BSW_COM_SETTXFINCHGPRD_FUNC    (&bsw_com_tx_SetTxFinChgPrdTmrNn)
#define BSW_COM_INITCHGPRD_FUNC        (&bsw_com_tx_InitChgPrdIpduNone)
#define BSW_COM_GETCHGPRDSTAT_FUNC     (&bsw_com_tx_GetChgPrdIpduStNone)
#endif /* BSW_COM_CFG_CHGPERIOD_MSG_NUM > 0U */

#if (BSW_COM_EVENTAWAKE_USE == BSW_USE)
#define BSW_COM_SETEVENTAWAKE_FUNC     (&BswM_CS_SetEventAwake)
#else
#define BSW_COM_SETEVENTAWAKE_FUNC     (&bsw_com_tx_SetEventAwakeNone)
#endif

#if (BSW_COM_EVENTWAKEUPFRAME_USE == BSW_USE)
#define BSW_COM_TXWAKEUPEVENT_FUNC     (&BswM_CS_TransmitWakeupEvent)
#else
#define BSW_COM_TXWAKEUPEVENT_FUNC     (&bsw_com_tx_TxWakeupEventNone)
#endif


#if ( BSW_COM_FUNC_PNCIPDU == BSW_USE )
#define BSW_COM_CHKCHPNCUSE_FUNC       (&bsw_com_data_ChkChPncUse)
#define BSW_COM_INITPNCTXSTAT_FUNC     (&bsw_com_tx_InitPncTxStat)
#define BSW_COM_SHUTDOWNPNCTXSTAT_FUNC (&bsw_com_tx_ShutdownPncTxSt)
#define BSW_COM_GETPNCCHTXST_FUNC      (&bsw_com_tx_GetPncChTxSt)
#define BSW_COM_GETPNCCHTXENST_FUNC    (&bsw_com_tx_GetPncChTxEnSt)
#define BSW_COM_CHKPNCIPDUTXST_FUNC    (&bsw_com_tx_ChkPncIpduTxSt)
#define BSW_COM_SETPNCCHTXST_FUNC      (&bsw_com_tx_SetPncChTxSt)
#define BSW_COM_SETPNCCHTXENST_FUNC    (&bsw_com_tx_SetPncChTxEnSt)
#define BSW_COM_SETPNCTXIPDUTXSTS_FUNC (&bsw_com_tx_SetPncIpduTxEnSt)
#define BSW_COM_GETPNCIPDUTXENST_FUNC  (&bsw_com_tx_GetPncIpduTxEnSt)
#define BSW_COM_GETPNCIPDUPERIOFS_FUNC (&bsw_com_tx_GetPncIpduPeriOfsSt)
#define BSW_COM_SETPNCIPDUPROFSON_FUNC (&bsw_com_tx_SetPncIpduPeriOfsOn)
#define BSW_COM_GETPNCCHNUMBER_FUNC    (&bsw_com_tx_GetPncChNumber)
#define BSW_COM_SETPNCIPDUFSTDLY_FUNC  (&bsw_com_tx_SetPncIpduFstDly)
#define BSW_COM_GETPNCIPDUTXST_FUNC    (&bsw_com_tx_GetPncIpduTxSt)
#define BSW_COM_JUDGEPNCTXSTPROC_FUNC  (&bsw_com_tx_JudgePncIpduTxStProc)
#define BSW_COM_INITPNCRXSTAT_FUNC     (&bsw_com_rx_InitPncRxStat)
#define BSW_COM_SHUTDOWNPNCRXSTAT_FUNC (&bsw_com_rx_ShutdownPncRxSt)
#define BSW_COM_GETPNCCHRXDMST_FUNC    (&bsw_com_rx_GetPncChRxDMSt)
#define BSW_COM_SETPNCIPDURXDMST_FUNC  (&bsw_com_rx_SetPncIpduRxDMSt)
#define BSW_COM_GETPNCIPDURXDMST_FUNC  (&bsw_com_rx_GetPncIpduRxDMSt)
#define BSW_COM_GETPNCCHRXST_FUNC      (&bsw_com_rx_GetPncChRxSt)
#define BSW_COM_CHKPNCIPDURXDMST_FUNC  (&bsw_com_rx_ChkPncIpduRxDMSt)
#define BSW_COM_CHKPNCIPDURXST_FUNC    (&bsw_com_rx_ChkPncIpduRxSt)
#define BSW_COM_SETPNCCHRXST_FUNC      (&bsw_com_rx_SetPncChRxSt)
#define BSW_COM_GETPNCIPDURXST_FUNC    (&bsw_com_rx_GetPncIpduRxSt)
#define BSW_COM_GETPNCONMSKTIME_FUNC   (&bsw_com_rx_GetPnconMskTime)
#define BSW_COM_JUDGEPNCRXSTPROC_FUNC  (&bsw_com_rx_JudgePncIpduRxStProc)
#else
#define BSW_COM_CHKCHPNCUSE_FUNC       (&bsw_com_data_ChkChPncUseNone)
#define BSW_COM_INITPNCTXSTAT_FUNC     (&bsw_com_tx_InitPncTxStatNone)
#define BSW_COM_SHUTDOWNPNCTXSTAT_FUNC (&bsw_com_tx_ShutdownPncTxStNone)
#define BSW_COM_GETPNCCHTXST_FUNC      (&bsw_com_tx_GetPncChTxStNone)
#define BSW_COM_GETPNCCHTXENST_FUNC    (&bsw_com_tx_GetPncChTxEnStNone)
#define BSW_COM_CHKPNCIPDUTXST_FUNC    (&bsw_com_tx_ChkPncIpduTxStNone)
#define BSW_COM_SETPNCCHTXST_FUNC      (&bsw_com_tx_SetPncChTxStNone)
#define BSW_COM_SETPNCCHTXENST_FUNC    (&bsw_com_tx_SetPncChTxEnStNone)
#define BSW_COM_SETPNCTXIPDUTXSTS_FUNC (&bsw_com_tx_SetPncIpduTxEnStNone)
#define BSW_COM_GETPNCIPDUTXENST_FUNC  (&bsw_com_tx_GetPncIpduTxEnStNone)
#define BSW_COM_GETPNCIPDUPERIOFS_FUNC (&bsw_com_tx_GetPncIpduPrOfsNone)
#define BSW_COM_SETPNCIPDUPROFSON_FUNC (&bsw_com_tx_SetPncIpdPrOfsOnNone)
#define BSW_COM_GETPNCCHNUMBER_FUNC    (&bsw_com_tx_GetPncChNumberNone)
#define BSW_COM_SETPNCIPDUFSTDLY_FUNC  (&bsw_com_tx_SetIpduFstDly)
#define BSW_COM_GETPNCIPDUTXST_FUNC    (&bsw_com_tx_GetPncIpduTxStNone)
#define BSW_COM_JUDGEPNCTXSTPROC_FUNC  (&bsw_com_tx_JudgeIpduTxStProc)
#define BSW_COM_INITPNCRXSTAT_FUNC     (&bsw_com_rx_InitPncRxStatNone)
#define BSW_COM_SHUTDOWNPNCRXSTAT_FUNC (&bsw_com_rx_ShutdownPncRxStNone)
#define BSW_COM_GETPNCCHRXDMST_FUNC    (&bsw_com_rx_GetPncChRxDMStNone)
#define BSW_COM_SETPNCIPDURXDMST_FUNC  (&bsw_com_rx_SetPncIpduRxDMStNone)
#define BSW_COM_GETPNCIPDURXDMST_FUNC  (&bsw_com_rx_GetPncIpduRxDMStNone)
#define BSW_COM_GETPNCCHRXST_FUNC      (&bsw_com_rx_GetPncChRxStNone)
#define BSW_COM_CHKPNCIPDURXDMST_FUNC  (&bsw_com_rx_ChkPncIpduRxDMStNone)
#define BSW_COM_CHKPNCIPDURXST_FUNC    (&bsw_com_rx_ChkPncIpduRxStNone)
#define BSW_COM_SETPNCCHRXST_FUNC      (&bsw_com_rx_SetPncChRxStNone)
#define BSW_COM_GETPNCIPDURXST_FUNC    (&bsw_com_rx_GetPncIpduRxStNone)
#define BSW_COM_GETPNCONMSKTIME_FUNC   (&bsw_com_rx_GetPnconMskTimeNone)
#define BSW_COM_JUDGEPNCRXSTPROC_FUNC  (&bsw_com_rx_JudgeIpduRxStProc)
#endif

#define BSW_COM_FIRE_HANDLER_NUM       (BSW_COM_RX_MSG_NUM)

#define BSW_COM_BITIND_CH00_TOP        (0U)
#define BSW_COM_BITIND_CH01_TOP        (BSW_COM_BITIND_CH00_TOP + ((BSW_COM_CFG_CH00_TX_NUM + BSW_COM_BITIND_ROUNDUP_VALUE) >> BSW_COM_BITIND_BYTEPOS_SHIFT) )
#define BSW_COM_BITIND_CH02_TOP        (BSW_COM_BITIND_CH01_TOP + ((BSW_COM_CFG_CH01_TX_NUM + BSW_COM_BITIND_ROUNDUP_VALUE) >> BSW_COM_BITIND_BYTEPOS_SHIFT) )
#define BSW_COM_BITIND_CH03_TOP        (BSW_COM_BITIND_CH02_TOP + ((BSW_COM_CFG_CH02_TX_NUM + BSW_COM_BITIND_ROUNDUP_VALUE) >> BSW_COM_BITIND_BYTEPOS_SHIFT) )
#define BSW_COM_BITIND_CH04_TOP        (BSW_COM_BITIND_CH03_TOP + ((BSW_COM_CFG_CH03_TX_NUM + BSW_COM_BITIND_ROUNDUP_VALUE) >> BSW_COM_BITIND_BYTEPOS_SHIFT) )
#define BSW_COM_BITIND_CH05_TOP        (BSW_COM_BITIND_CH04_TOP + ((BSW_COM_CFG_CH04_TX_NUM + BSW_COM_BITIND_ROUNDUP_VALUE) >> BSW_COM_BITIND_BYTEPOS_SHIFT) )
#define BSW_COM_BITIND_CH06_TOP        (BSW_COM_BITIND_CH05_TOP + ((BSW_COM_CFG_CH05_TX_NUM + BSW_COM_BITIND_ROUNDUP_VALUE) >> BSW_COM_BITIND_BYTEPOS_SHIFT) )
#define BSW_COM_BITIND_CH07_TOP        (BSW_COM_BITIND_CH06_TOP + ((BSW_COM_CFG_CH06_TX_NUM + BSW_COM_BITIND_ROUNDUP_VALUE) >> BSW_COM_BITIND_BYTEPOS_SHIFT) )
#define BSW_COM_BITIND_CH08_TOP        (BSW_COM_BITIND_CH07_TOP + ((BSW_COM_CFG_CH07_TX_NUM + BSW_COM_BITIND_ROUNDUP_VALUE) >> BSW_COM_BITIND_BYTEPOS_SHIFT) )
#define BSW_COM_BITIND_CH09_TOP        (BSW_COM_BITIND_CH08_TOP + ((BSW_COM_CFG_CH08_TX_NUM + BSW_COM_BITIND_ROUNDUP_VALUE) >> BSW_COM_BITIND_BYTEPOS_SHIFT) )
#define BSW_COM_BITIND_CH10_TOP        (BSW_COM_BITIND_CH09_TOP + ((BSW_COM_CFG_CH09_TX_NUM + BSW_COM_BITIND_ROUNDUP_VALUE) >> BSW_COM_BITIND_BYTEPOS_SHIFT) )
#define BSW_COM_BITIND_CH11_TOP        (BSW_COM_BITIND_CH10_TOP + ((BSW_COM_CFG_CH10_TX_NUM + BSW_COM_BITIND_ROUNDUP_VALUE) >> BSW_COM_BITIND_BYTEPOS_SHIFT) )
#define BSW_COM_BITIND_CH12_TOP        (BSW_COM_BITIND_CH11_TOP + ((BSW_COM_CFG_CH11_TX_NUM + BSW_COM_BITIND_ROUNDUP_VALUE) >> BSW_COM_BITIND_BYTEPOS_SHIFT) )
#define BSW_COM_BITIND_CH13_TOP        (BSW_COM_BITIND_CH12_TOP + ((BSW_COM_CFG_CH12_TX_NUM + BSW_COM_BITIND_ROUNDUP_VALUE) >> BSW_COM_BITIND_BYTEPOS_SHIFT) )
#define BSW_COM_BITIND_CH14_TOP        (BSW_COM_BITIND_CH13_TOP + ((BSW_COM_CFG_CH13_TX_NUM + BSW_COM_BITIND_ROUNDUP_VALUE) >> BSW_COM_BITIND_BYTEPOS_SHIFT) )
#define BSW_COM_BITIND_CH15_TOP        (BSW_COM_BITIND_CH14_TOP + ((BSW_COM_CFG_CH14_TX_NUM + BSW_COM_BITIND_ROUNDUP_VALUE) >> BSW_COM_BITIND_BYTEPOS_SHIFT) )
#define BSW_COM_BITIND_CH16_TOP        (BSW_COM_BITIND_CH15_TOP + ((BSW_COM_CFG_CH15_TX_NUM + BSW_COM_BITIND_ROUNDUP_VALUE) >> BSW_COM_BITIND_BYTEPOS_SHIFT) )
#define BSW_COM_BITIND_CH17_TOP        (BSW_COM_BITIND_CH16_TOP + ((BSW_COM_CFG_CH16_TX_NUM + BSW_COM_BITIND_ROUNDUP_VALUE) >> BSW_COM_BITIND_BYTEPOS_SHIFT) )
#define BSW_COM_BITIND_CH18_TOP        (BSW_COM_BITIND_CH17_TOP + ((BSW_COM_CFG_CH17_TX_NUM + BSW_COM_BITIND_ROUNDUP_VALUE) >> BSW_COM_BITIND_BYTEPOS_SHIFT) )
#define BSW_COM_BITIND_CH19_TOP        (BSW_COM_BITIND_CH18_TOP + ((BSW_COM_CFG_CH18_TX_NUM + BSW_COM_BITIND_ROUNDUP_VALUE) >> BSW_COM_BITIND_BYTEPOS_SHIFT) )
#define BSW_COM_BITIND_CH20_TOP        (BSW_COM_BITIND_CH19_TOP + ((BSW_COM_CFG_CH19_TX_NUM + BSW_COM_BITIND_ROUNDUP_VALUE) >> BSW_COM_BITIND_BYTEPOS_SHIFT) )
#define BSW_COM_BITIND_CH21_TOP        (BSW_COM_BITIND_CH20_TOP + ((BSW_COM_CFG_CH20_TX_NUM + BSW_COM_BITIND_ROUNDUP_VALUE) >> BSW_COM_BITIND_BYTEPOS_SHIFT) )
#define BSW_COM_BITIND_CH22_TOP        (BSW_COM_BITIND_CH21_TOP + ((BSW_COM_CFG_CH21_TX_NUM + BSW_COM_BITIND_ROUNDUP_VALUE) >> BSW_COM_BITIND_BYTEPOS_SHIFT) )
#define BSW_COM_BITIND_CH23_TOP        (BSW_COM_BITIND_CH22_TOP + ((BSW_COM_CFG_CH22_TX_NUM + BSW_COM_BITIND_ROUNDUP_VALUE) >> BSW_COM_BITIND_BYTEPOS_SHIFT) )
#define BSW_COM_BITIND_CH24_TOP        (BSW_COM_BITIND_CH23_TOP + ((BSW_COM_CFG_CH23_TX_NUM + BSW_COM_BITIND_ROUNDUP_VALUE) >> BSW_COM_BITIND_BYTEPOS_SHIFT) )
#define BSW_COM_BITIND_CH25_TOP        (BSW_COM_BITIND_CH24_TOP + ((BSW_COM_CFG_CH24_TX_NUM + BSW_COM_BITIND_ROUNDUP_VALUE) >> BSW_COM_BITIND_BYTEPOS_SHIFT) )
#define BSW_COM_BITIND_CH26_TOP        (BSW_COM_BITIND_CH25_TOP + ((BSW_COM_CFG_CH25_TX_NUM + BSW_COM_BITIND_ROUNDUP_VALUE) >> BSW_COM_BITIND_BYTEPOS_SHIFT) )
#define BSW_COM_BITIND_CH27_TOP        (BSW_COM_BITIND_CH26_TOP + ((BSW_COM_CFG_CH26_TX_NUM + BSW_COM_BITIND_ROUNDUP_VALUE) >> BSW_COM_BITIND_BYTEPOS_SHIFT) )
#define BSW_COM_BITIND_CH28_TOP        (BSW_COM_BITIND_CH27_TOP + ((BSW_COM_CFG_CH27_TX_NUM + BSW_COM_BITIND_ROUNDUP_VALUE) >> BSW_COM_BITIND_BYTEPOS_SHIFT) )
#define BSW_COM_BITIND_CH29_TOP        (BSW_COM_BITIND_CH28_TOP + ((BSW_COM_CFG_CH28_TX_NUM + BSW_COM_BITIND_ROUNDUP_VALUE) >> BSW_COM_BITIND_BYTEPOS_SHIFT) )
#define BSW_COM_BITIND_CH30_TOP        (BSW_COM_BITIND_CH29_TOP + ((BSW_COM_CFG_CH29_TX_NUM + BSW_COM_BITIND_ROUNDUP_VALUE) >> BSW_COM_BITIND_BYTEPOS_SHIFT) )
#define BSW_COM_BITIND_CH31_TOP        (BSW_COM_BITIND_CH30_TOP + ((BSW_COM_CFG_CH30_TX_NUM + BSW_COM_BITIND_ROUNDUP_VALUE) >> BSW_COM_BITIND_BYTEPOS_SHIFT) )
#define BSW_COM_BITIND_SIZE            (BSW_COM_BITIND_CH31_TOP + ((BSW_COM_CFG_CH31_TX_NUM + BSW_COM_BITIND_ROUNDUP_VALUE) >> BSW_COM_BITIND_BYTEPOS_SHIFT) )

#define BSW_COM_CPU_BYTE_ORDER_TYPE    (CPU_BYTE_ORDER)


/* Number of PNC and PNC tables per channel */
#if ( BSW_COM_NETWORK_NUM > 0U )
#define BSW_COM_CH_PNCNUM_00           (BSW_COMM_CH_PNCNUM_0)
#endif
#if ( BSW_COM_NETWORK_NUM > 1U )
#define BSW_COM_CH_PNCNUM_01           (BSW_COMM_CH_PNCNUM_1)
#endif
#if ( BSW_COM_NETWORK_NUM > 2U )
#define BSW_COM_CH_PNCNUM_02           (BSW_COMM_CH_PNCNUM_2)
#endif
#if ( BSW_COM_NETWORK_NUM > 3U )
#define BSW_COM_CH_PNCNUM_03           (BSW_COMM_CH_PNCNUM_3)
#endif
#if ( BSW_COM_NETWORK_NUM > 4U )
#define BSW_COM_CH_PNCNUM_04           (BSW_COMM_CH_PNCNUM_4)
#endif
#if ( BSW_COM_NETWORK_NUM > 5U )
#define BSW_COM_CH_PNCNUM_05           (BSW_COMM_CH_PNCNUM_5)
#endif
#if ( BSW_COM_NETWORK_NUM > 6U )
#define BSW_COM_CH_PNCNUM_06           (BSW_COMM_CH_PNCNUM_6)
#endif
#if ( BSW_COM_NETWORK_NUM > 7U )
#define BSW_COM_CH_PNCNUM_07           (BSW_COMM_CH_PNCNUM_7)
#endif
#if ( BSW_COM_NETWORK_NUM > 8U )
#define BSW_COM_CH_PNCNUM_08           (BSW_COMM_CH_PNCNUM_8)
#endif
#if ( BSW_COM_NETWORK_NUM > 9U )
#define BSW_COM_CH_PNCNUM_09           (BSW_COMM_CH_PNCNUM_9)
#endif
#if ( BSW_COM_NETWORK_NUM > 10U )
#define BSW_COM_CH_PNCNUM_10           (BSW_COMM_CH_PNCNUM_10)
#endif
#if ( BSW_COM_NETWORK_NUM > 11U )
#define BSW_COM_CH_PNCNUM_11           (BSW_COMM_CH_PNCNUM_11)
#endif
#if ( BSW_COM_NETWORK_NUM > 12U )
#define BSW_COM_CH_PNCNUM_12           (BSW_COMM_CH_PNCNUM_12)
#endif
#if ( BSW_COM_NETWORK_NUM > 13U )
#define BSW_COM_CH_PNCNUM_13           (BSW_COMM_CH_PNCNUM_13)
#endif
#if ( BSW_COM_NETWORK_NUM > 14U )
#define BSW_COM_CH_PNCNUM_14           (BSW_COMM_CH_PNCNUM_14)
#endif
#if ( BSW_COM_NETWORK_NUM > 15U )
#define BSW_COM_CH_PNCNUM_15           (BSW_COMM_CH_PNCNUM_15)
#endif
#if ( BSW_COM_NETWORK_NUM > 16U )
#define BSW_COM_CH_PNCNUM_16           (BSW_COMM_CH_PNCNUM_16)
#endif
#if ( BSW_COM_NETWORK_NUM > 17U )
#define BSW_COM_CH_PNCNUM_17           (BSW_COMM_CH_PNCNUM_17)
#endif
#if ( BSW_COM_NETWORK_NUM > 18U )
#define BSW_COM_CH_PNCNUM_18           (BSW_COMM_CH_PNCNUM_18)
#endif
#if ( BSW_COM_NETWORK_NUM > 19U )
#define BSW_COM_CH_PNCNUM_19           (BSW_COMM_CH_PNCNUM_19)
#endif
#if ( BSW_COM_NETWORK_NUM > 20U )
#define BSW_COM_CH_PNCNUM_20           (BSW_COMM_CH_PNCNUM_20)
#endif
#if ( BSW_COM_NETWORK_NUM > 21U )
#define BSW_COM_CH_PNCNUM_21           (BSW_COMM_CH_PNCNUM_21)
#endif
#if ( BSW_COM_NETWORK_NUM > 22U )
#define BSW_COM_CH_PNCNUM_22           (BSW_COMM_CH_PNCNUM_22)
#endif
#if ( BSW_COM_NETWORK_NUM > 23U )
#define BSW_COM_CH_PNCNUM_23           (BSW_COMM_CH_PNCNUM_23)
#endif
#if ( BSW_COM_NETWORK_NUM > 24U )
#define BSW_COM_CH_PNCNUM_24           (BSW_COMM_CH_PNCNUM_24)
#endif
#if ( BSW_COM_NETWORK_NUM > 25U )
#define BSW_COM_CH_PNCNUM_25           (BSW_COMM_CH_PNCNUM_25)
#endif
#if ( BSW_COM_NETWORK_NUM > 26U )
#define BSW_COM_CH_PNCNUM_26           (BSW_COMM_CH_PNCNUM_26)
#endif
#if ( BSW_COM_NETWORK_NUM > 27U )
#define BSW_COM_CH_PNCNUM_27           (BSW_COMM_CH_PNCNUM_27)
#endif
#if ( BSW_COM_NETWORK_NUM > 28U )
#define BSW_COM_CH_PNCNUM_28           (BSW_COMM_CH_PNCNUM_28)
#endif
#if ( BSW_COM_NETWORK_NUM > 29U )
#define BSW_COM_CH_PNCNUM_29           (BSW_COMM_CH_PNCNUM_29)
#endif
#if ( BSW_COM_NETWORK_NUM > 30U )
#define BSW_COM_CH_PNCNUM_30           (BSW_COMM_CH_PNCNUM_30)
#endif
#if ( BSW_COM_NETWORK_NUM > 31U )
#define BSW_COM_CH_PNCNUM_31           (BSW_COMM_CH_PNCNUM_31)
#endif

#if ( BSW_COM_FUNC_PNCIPDU == BSW_USE )
/* PNC Periodic Transmission Offset Time */
#define BSW_COM_PNC_PERIODIC_OFFSET(channel)        ( (BSW_BSWM_CS_ENABLE_PERI_PNC(channel) > BSW_BSWM_CS_SND_START_PNC(channel)) ? \
                                                      (BSW_BSWM_CS_ENABLE_PERI_PNC(channel) - BSW_BSWM_CS_SND_START_PNC(channel)) : (0U) )
#endif

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
/*------------------------------------*/
/* Transmission unit (TX)             */
/*------------------------------------*/
/* For periodic transmission timer */
#if (BSW_COM_TX_MSG_NUM > 0U)
BswU2       bsw_com_tx_u2Tx[BSW_COM_TX_MSG_NUM];                    /* Periodic transmission timer                   */
#else /* upper:BSW_COM_TX_MSG_NUM > 0  lower:BSW_COM_TX_MSG_NUM == 0 */
BswU2       bsw_com_tx_u2Tx[BSW_COM_DUMMY_SIZE];                    /* Periodic transmission timer                   */
#endif  /* BSW_COM_TX_MSG_NUM == 0 */

/* For waiting transmission delay */
#if (BSW_COM_TX_MSG_NUM > 0U)
BswU2       bsw_com_tx_u2Delay[BSW_COM_TX_MSG_NUM];                 /* Transmission delay timer                   */
#else /* upper:BSW_COM_TX_MSG_NUM > 0  lower:BSW_COM_TX_MSG_NUM == 0 */
BswU2       bsw_com_tx_u2Delay[BSW_COM_DUMMY_SIZE];                 /* Transmission delay timer                   */
#endif  /* BSW_COM_TX_MSG_NUM == 0 */

/* Current transmission mode                     */
Bsw_Com_TxModeType bsw_com_tx_CurrentTxMode[BSW_COM_NETWORK_NUM];   /* Current transmission mode                     */

/* RAM for transmission message stop semaphore */
#if (BSW_COM_TX_MSG_NUM > 0U)
BswU1       bsw_com_tx_u1TxStop[BSW_COM_BITIND_SIZE];               /* Stop transmitting information                     */
BswU1       bsw_com_tx_u1TxStopMrr[BSW_COM_BITIND_SIZE];            /* Stop transmitting information(mirror)             */
#else /* upper:BSW_COM_TX_MSG_NUM > 0  lower:BSW_COM_TX_MSG_NUM == 0 */
BswU1       bsw_com_tx_u1TxStop[BSW_COM_DUMMY_SIZE];                /* Stop transmitting information                     */
BswU1       bsw_com_tx_u1TxStopMrr[BSW_COM_DUMMY_SIZE];             /* Stop transmitting information(mirror)             */
#endif /* BSW_COM_TX_MSG_NUM == 0 */

#if ((BSW_COM_TX_MSG_NUM > 0U) && (BSW_COM_TX_TIMEOUT_USE == BSW_USE))
BswU1       bsw_com_tx_u1TxReqStat[BSW_COM_TX_MSG_NUM];             /* Send request status to PDUR             */
#elif ((BSW_COM_TX_MSG_NUM == 0U) && (BSW_COM_TX_TIMEOUT_USE == BSW_USE))
BswU1       bsw_com_tx_u1TxReqStat[BSW_COM_DUMMY_SIZE];
#else
/* No need to define as bsw_com_tx_u1TxReqStat[] is not used */
#endif

/* For N times transmission */
#if (BSW_COM_SENDNTIMES_MSG_NUM > 0U)
BswU2       bsw_com_tx_u2NTimesIntv[BSW_COM_SENDNTIMES_MSG_NUM];    /* Timer for N times transmission                  */
BswU1       bsw_com_tx_u1NTimesCnt[BSW_COM_SENDNTIMES_MSG_NUM];     /* Count transmission count                 */
#else /* upper:BSW_COM_SENDNTIMES_MSG_NUM >0 lower:BSW_COM_SENDNTIMES_MSG_NUM == 0 */
BswU2       bsw_com_tx_u2NTimesIntv[BSW_COM_DUMMY_SIZE];            /* Timer for N times transmission                  */
BswU1       bsw_com_tx_u1NTimesCnt[BSW_COM_DUMMY_SIZE];             /* Count transmission count                 */
#endif /* BSW_COM_SENDNTIMES_MSG_NUM == 0U */

#if (BSW_COM_TX_CHGPERIOD_USE == BSW_USE )
BswU1       bsw_com_tx_u1ChgPrdStat[BSW_COM_NETWORK_NUM];           /* Per-channel periodic switching state     */
#else
BswU1       bsw_com_tx_u1ChgPrdStat[BSW_COM_DUMMY_SIZE];
#endif

/* For switching the period per-message */
#if (BSW_COM_CHGPERIOD_MSG_NUM > 0U)
BswU2       bsw_com_tx_u2ChgPrdIpduTime[BSW_COM_CHGPERIOD_MSG_NUM]; /* Timer for periodic switching transmission         */
BswU1       bsw_com_tx_u1ChgPrdIpduCnt[BSW_COM_CHGPERIOD_MSG_NUM];  /* Count transmission count at the end of switching */
#else /* upper:BSW_COM_CHGPERIOD_MSG_NUM >0 lower:BSW_COM_CHGPERIOD_MSG_NUM == 0 */
BswU2       bsw_com_tx_u2ChgPrdIpduTime[BSW_COM_DUMMY_SIZE];        /* Timer for periodic switching transmission         */
BswU1       bsw_com_tx_u1ChgPrdIpduCnt[BSW_COM_DUMMY_SIZE];         /* Count transmission count at the end of switching */
#endif /* BSW_COM_CHGPERIOD_MSG_NUM == 0U */

/* Bit indicator */
#if (BSW_COM_TX_MSG_NUM > 0U)
BswU1       bsw_com_tx_u1BitIndPrd[BSW_COM_BITIND_SIZE];            /* Periodic transmit queue                 */
BswU1       bsw_com_tx_u1BitIndEv[BSW_COM_BITIND_SIZE];             /* Queue for event transmission            */
#else /* upper:BSW_COM_TX_MSG_NUM > 0  lower:BSW_COM_TX_MSG_NUM == 0 */
BswU1       bsw_com_tx_u1BitIndPrd[BSW_COM_DUMMY_SIZE];             /* Periodic transmit queue                 */
BswU1       bsw_com_tx_u1BitIndEv[BSW_COM_DUMMY_SIZE];              /* Queue for event transmission            */
#endif /* BSW_COM_TX_MSG_NUM == 0 */

/* RAM for stop transmission retry */
#if (BSW_COM_TX_MSG_NUM > 0U)
BswU1       bsw_com_tx_u1TxRtyStop[BSW_COM_BITIND_SIZE];
#else /* upper:BSW_COM_TX_MSG_NUM > 0  lower:BSW_COM_TX_MSG_NUM == 0 */
BswU1       bsw_com_tx_u1TxRtyStop[BSW_COM_DUMMY_SIZE];
#endif /* BSW_COM_TX_MSG_NUM == 0 */

BswU1       bsw_com_tx_u1TxIpduGrpReqStat[BSW_COM_NETWORK_NUM];     /* The transmit I-PDU group state (Request)      */
BswU1       bsw_com_tx_u1TxIpduGrpStat[BSW_COM_NETWORK_NUM];        /* The transmit I-PDU group state            */
BswU1       bsw_com_tx_u1EvTxStat[BSW_COM_NETWORK_NUM];             /* Event transmission availability                 */
BswU1       bsw_com_tx_u1PrdTxStat[BSW_COM_NETWORK_NUM];            /* Enable/disable state of periodic transmission                     */
BswU1       bsw_com_tx_u1PeriTxResetReq[BSW_COM_NETWORK_NUM];       /* Request a periodic transmission reset             */
BswU2       bsw_com_tx_u2PeriTxOffset[BSW_COM_NETWORK_NUM];         /* Periodic transmission offset time           */
BswU1       bsw_com_tx_u1FirstTxSetReq[BSW_COM_NETWORK_NUM];        /* Request first transmission setting */

#if ( BSW_COM_FUNC_PNCIPDU == BSW_USE )
BswU4       bsw_com_tx_u4PncTxIpduGrReqStat[BSW_COM_NETWORK_NUM][BSW_COM_PNC_REQNUM];   /* PNC transmit I-PDU group state (Request)  */
BswU4       bsw_com_tx_u4PncTxIpduGrStat[BSW_COM_NETWORK_NUM][BSW_COM_PNC_REQNUM];      /* PNC transmit I-PDU group state            */
BswU4       bsw_com_tx_u4PncTxEnableReqStat[BSW_COM_NETWORK_NUM][BSW_COM_PNC_REQNUM];   /* PNC transmit Tx Enable/Disable state (Request) */
BswU4       bsw_com_tx_u4PncTxEnableStat[BSW_COM_NETWORK_NUM][BSW_COM_PNC_REQNUM];      /* PNC transmit Tx Enable/Disable state      */

#if (BSW_COM_TX_MSG_NUM > 0U)
Bsw_Com_PncIpduTxInfoType   bsw_com_tx_stPncIpduTxInfo[BSW_COM_TX_MSG_NUM];             /* PNC I-PDU Tx Info */
#else /* upper:BSW_COM_TX_MSG_NUM > 0  lower:BSW_COM_TX_MSG_NUM == 0 */
Bsw_Com_PncIpduTxInfoType   bsw_com_tx_stPncIpduTxInfo[BSW_COM_DUMMY_SIZE];             /* PNC I-PDU Tx Info */
#endif /* BSW_COM_TX_MSG_NUM == 0 */
#endif /* ( BSW_COM_FUNC_PNCIPDU == BSW_USE ) */

/* For notification before tansmission */
#if (BSW_COM_PRETX_MAX_MSGSIZE != 0U)
BswU1 bsw_com_tx_u1PreTxMsgBuf[BSW_COM_PRETX_MAX_MSGSIZE];          /* Temporary buffer for notification before tansmission         */
#else
BswU1 bsw_com_tx_u1PreTxMsgBuf[BSW_COM_DUMMY_SIZE];          /* Temporary buffer for notification before tansmission         */
#endif /* (BSW_COM_PRETX_MAX_MSGSIZE != 0U) */

/*------------------------------------*/
/* Receiving unit (RX)                */
/*------------------------------------*/
#if (BSW_COM_FIRE_HANDLER_NUM > 0U)
PduIdType   bsw_com_rx_u2FireHandler[BSW_COM_FIRE_HANDLER_NUM];     /* Periodic transmission/timeout time elapsed message ID */
#else /* upper:BSW_COM_FIRE_HANDLER_NUM > 0 lower:BSW_COM_FIRE_HANDLER_NUM == 0 */
PduIdType   bsw_com_rx_u2FireHandler[BSW_COM_DUMMY_SIZE];           /* Periodic transmission/timeout time elapsed message ID */
#endif /* BSW_COM_FIRE_HANDLER_NUM == 0 */

/* For timeout timer */
#if (BSW_COM_RX_MSG_NUM > 0U)
BswU2       bsw_com_rx_u2DLine[BSW_COM_RX_MSG_NUM];                 /* Timeout timer               */
#else /* upper:BSW_COM_RX_MSG_NUM > 0  lower:BSW_COM_RX_MSG_NUM == 0 */
BswU2       bsw_com_rx_u2DLine[BSW_COM_DUMMY_SIZE];                 /* Timeout timer               */
#endif /* BSW_COM_RX_MSG_NUM == 0 */

BswU1       bsw_com_rx_u1RxIpduGrpReqStat[BSW_COM_NETWORK_NUM];     /* Receive I-PDU group state (Request)      */
BswU1       bsw_com_rx_u1RxIpduGrpStat[BSW_COM_NETWORK_NUM];        /* Receive I-PDU group state            */
BswU1       bsw_com_rx_u1RxDmReqStat[BSW_COM_NETWORK_NUM];          /* Receive disconnection monitoring state (Request)           */
BswU1       bsw_com_rx_u1RxDmStat[BSW_COM_NETWORK_NUM];             /* Receive disconnection monitoring state                 */
BswU1       bsw_com_rx_u1WkupMskSetReqStat[BSW_COM_NETWORK_NUM];    /* WAKEUP_MASK setting state(request)        */
BswU1       bsw_com_rx_u1WkupMskSetStat[BSW_COM_NETWORK_NUM];       /* WAKEUP_MASK setting state              */

#if ( BSW_COM_FUNC_PNCIPDU == BSW_USE )
BswU4       bsw_com_rx_u4PncRxIpduGrReqStat[BSW_COM_NETWORK_NUM][BSW_COM_PNC_REQNUM];   /* PNC receive I-PDU group state (Request)  */
BswU4       bsw_com_rx_u4PncRxIpduGrStat[BSW_COM_NETWORK_NUM][BSW_COM_PNC_REQNUM];      /* PNC receive I-PDU group state            */
BswU4       bsw_com_rx_u4PncRxDmReqStat[BSW_COM_NETWORK_NUM][BSW_COM_PNC_REQNUM];       /* PNC Receive disconnection monitoring state (Request) */
BswU4       bsw_com_rx_u4PncRxDmStat[BSW_COM_NETWORK_NUM][BSW_COM_PNC_REQNUM];          /* PNC Receive disconnection monitoring state           */
#endif

/*------------------------------------*/
/* Fail safe unit (FS)                */
/*------------------------------------*/
BswU1       bsw_com_fs_u1FailChk;                                   /* Failure detection flag                   */

/*------------------------------------*/
/* Data management unit (DATA)        */
/*------------------------------------*/
BswU1       bsw_com_data_u1MsgStat[BSW_COM_MSG_NUM];                /* Message status             */


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
/*------------------------------------*/
/* State management unit (ST)         */
/*------------------------------------*/
/* ROM table for constant reference */
BswConst       BswU2  bsw_com_rom_u2MSGNUM               = (BswU2)BSW_COM_MSG_NUM;
BswConst       BswU2  bsw_com_rom_u2TXMSGNUM             = (BswU2)BSW_COM_TX_MSG_NUM;
BswConst       BswU1  bsw_com_rom_u1NETWORKNUM           = (BswU1)BSW_COM_NETWORK_NUM;
BswConst       BswU1  bsw_com_rom_u1CHGPERIODUSE         = (BswU1)BSW_COM_TX_CHGPERIOD_USE;

#if (BSW_COM_TX_CHGPERIOD_USE == BSW_USE )
BswConst       BswU2  bsw_com_rom_u2CHGPRDCH[BSW_COM_NETWORK_NUM] =
{
                             BSW_COM_u2MILSEC(BSW_COM_CHGPRDCH_CH00)
#if (BSW_COM_NETWORK_NUM > 1U)
                            ,BSW_COM_u2MILSEC(BSW_COM_CHGPRDCH_CH01)
#endif
#if (BSW_COM_NETWORK_NUM > 2U)
                            ,BSW_COM_u2MILSEC(BSW_COM_CHGPRDCH_CH02)
#endif
#if (BSW_COM_NETWORK_NUM > 3U)
                            ,BSW_COM_u2MILSEC(BSW_COM_CHGPRDCH_CH03)
#endif
#if (BSW_COM_NETWORK_NUM > 4U)
                            ,BSW_COM_u2MILSEC(BSW_COM_CHGPRDCH_CH04)
#endif
#if (BSW_COM_NETWORK_NUM > 5U)
                            ,BSW_COM_u2MILSEC(BSW_COM_CHGPRDCH_CH05)
#endif
#if (BSW_COM_NETWORK_NUM > 6U)
                            ,BSW_COM_u2MILSEC(BSW_COM_CHGPRDCH_CH06)
#endif
#if (BSW_COM_NETWORK_NUM > 7U)
                            ,BSW_COM_u2MILSEC(BSW_COM_CHGPRDCH_CH07)
#endif
#if (BSW_COM_NETWORK_NUM > 8U)
                            ,BSW_COM_u2MILSEC(BSW_COM_CHGPRDCH_CH08)
#endif
#if (BSW_COM_NETWORK_NUM > 9U)
                            ,BSW_COM_u2MILSEC(BSW_COM_CHGPRDCH_CH09)
#endif
#if (BSW_COM_NETWORK_NUM > 10U)
                            ,BSW_COM_u2MILSEC(BSW_COM_CHGPRDCH_CH10)
#endif
#if (BSW_COM_NETWORK_NUM > 11U)
                            ,BSW_COM_u2MILSEC(BSW_COM_CHGPRDCH_CH11)
#endif
#if (BSW_COM_NETWORK_NUM > 12U)
                            ,BSW_COM_u2MILSEC(BSW_COM_CHGPRDCH_CH12)
#endif
#if (BSW_COM_NETWORK_NUM > 13U)
                            ,BSW_COM_u2MILSEC(BSW_COM_CHGPRDCH_CH13)
#endif
#if (BSW_COM_NETWORK_NUM > 14U)
                            ,BSW_COM_u2MILSEC(BSW_COM_CHGPRDCH_CH14)
#endif
#if (BSW_COM_NETWORK_NUM > 15U)
                            ,BSW_COM_u2MILSEC(BSW_COM_CHGPRDCH_CH15)
#endif
#if (BSW_COM_NETWORK_NUM > 16U)
                            ,BSW_COM_u2MILSEC(BSW_COM_CHGPRDCH_CH16)
#endif
#if (BSW_COM_NETWORK_NUM > 17U)
                            ,BSW_COM_u2MILSEC(BSW_COM_CHGPRDCH_CH17)
#endif
#if (BSW_COM_NETWORK_NUM > 18U)
                            ,BSW_COM_u2MILSEC(BSW_COM_CHGPRDCH_CH18)
#endif
#if (BSW_COM_NETWORK_NUM > 19U)
                            ,BSW_COM_u2MILSEC(BSW_COM_CHGPRDCH_CH19)
#endif
#if (BSW_COM_NETWORK_NUM > 20U)
                            ,BSW_COM_u2MILSEC(BSW_COM_CHGPRDCH_CH20)
#endif
#if (BSW_COM_NETWORK_NUM > 21U)
                            ,BSW_COM_u2MILSEC(BSW_COM_CHGPRDCH_CH21)
#endif
#if (BSW_COM_NETWORK_NUM > 22U)
                            ,BSW_COM_u2MILSEC(BSW_COM_CHGPRDCH_CH22)
#endif
#if (BSW_COM_NETWORK_NUM > 23U)
                            ,BSW_COM_u2MILSEC(BSW_COM_CHGPRDCH_CH23)
#endif
#if (BSW_COM_NETWORK_NUM > 24U)
                            ,BSW_COM_u2MILSEC(BSW_COM_CHGPRDCH_CH24)
#endif
#if (BSW_COM_NETWORK_NUM > 25U)
                            ,BSW_COM_u2MILSEC(BSW_COM_CHGPRDCH_CH25)
#endif
#if (BSW_COM_NETWORK_NUM > 26U)
                            ,BSW_COM_u2MILSEC(BSW_COM_CHGPRDCH_CH26)
#endif
#if (BSW_COM_NETWORK_NUM > 27U)
                            ,BSW_COM_u2MILSEC(BSW_COM_CHGPRDCH_CH27)
#endif
#if (BSW_COM_NETWORK_NUM > 28U)
                            ,BSW_COM_u2MILSEC(BSW_COM_CHGPRDCH_CH28)
#endif
#if (BSW_COM_NETWORK_NUM > 29U)
                            ,BSW_COM_u2MILSEC(BSW_COM_CHGPRDCH_CH29)
#endif
#if (BSW_COM_NETWORK_NUM > 30U)
                            ,BSW_COM_u2MILSEC(BSW_COM_CHGPRDCH_CH30)
#endif
#if (BSW_COM_NETWORK_NUM > 31U)
                            ,BSW_COM_u2MILSEC(BSW_COM_CHGPRDCH_CH31)
#endif
};
#else
BswConst        BswU2  bsw_com_rom_u2CHGPRDCH[BSW_COM_DUMMY_SIZE] = { (BswU2)0U };
#endif /* (BSW_COM_TX_CHGPERIOD_USE == BSW_USE ) */

#if ( BSW_COM_FUNC_PNCIPDU == BSW_USE )
/* Target PNC count for control */
BswConst BswU1 bsw_com_rom_u1PncNum[BSW_COM_NETWORK_NUM] = 
{
     (BswU1)BSW_COM_CH_PNCNUM_00
#if ( BSW_COM_NETWORK_NUM > 1U )
    ,(BswU1)BSW_COM_CH_PNCNUM_01
#endif
#if ( BSW_COM_NETWORK_NUM > 2U )
    ,(BswU1)BSW_COM_CH_PNCNUM_02
#endif
#if ( BSW_COM_NETWORK_NUM > 3U )
    ,(BswU1)BSW_COM_CH_PNCNUM_03
#endif
#if ( BSW_COM_NETWORK_NUM > 4U )
    ,(BswU1)BSW_COM_CH_PNCNUM_04
#endif
#if ( BSW_COM_NETWORK_NUM > 5U )
    ,(BswU1)BSW_COM_CH_PNCNUM_05
#endif
#if ( BSW_COM_NETWORK_NUM > 6U )
    ,(BswU1)BSW_COM_CH_PNCNUM_06
#endif
#if ( BSW_COM_NETWORK_NUM > 7U )
    ,(BswU1)BSW_COM_CH_PNCNUM_07
#endif
#if ( BSW_COM_NETWORK_NUM > 8U )
    ,(BswU1)BSW_COM_CH_PNCNUM_08
#endif
#if ( BSW_COM_NETWORK_NUM > 9U )
    ,(BswU1)BSW_COM_CH_PNCNUM_09
#endif
#if ( BSW_COM_NETWORK_NUM > 10U )
    ,(BswU1)BSW_COM_CH_PNCNUM_10
#endif
#if ( BSW_COM_NETWORK_NUM > 11U )
    ,(BswU1)BSW_COM_CH_PNCNUM_11
#endif
#if ( BSW_COM_NETWORK_NUM > 12U )
    ,(BswU1)BSW_COM_CH_PNCNUM_12
#endif
#if ( BSW_COM_NETWORK_NUM > 13U )
    ,(BswU1)BSW_COM_CH_PNCNUM_13
#endif
#if ( BSW_COM_NETWORK_NUM > 14U )
    ,(BswU1)BSW_COM_CH_PNCNUM_14
#endif
#if ( BSW_COM_NETWORK_NUM > 15U )
    ,(BswU1)BSW_COM_CH_PNCNUM_15
#endif
#if ( BSW_COM_NETWORK_NUM > 16U )
    ,(BswU1)BSW_COM_CH_PNCNUM_16
#endif
#if ( BSW_COM_NETWORK_NUM > 17U )
    ,(BswU1)BSW_COM_CH_PNCNUM_17
#endif
#if ( BSW_COM_NETWORK_NUM > 18U )
    ,(BswU1)BSW_COM_CH_PNCNUM_18
#endif
#if ( BSW_COM_NETWORK_NUM > 19U )
    ,(BswU1)BSW_COM_CH_PNCNUM_19
#endif
#if ( BSW_COM_NETWORK_NUM > 20U )
    ,(BswU1)BSW_COM_CH_PNCNUM_20
#endif
#if ( BSW_COM_NETWORK_NUM > 21U )
    ,(BswU1)BSW_COM_CH_PNCNUM_21
#endif
#if ( BSW_COM_NETWORK_NUM > 22U )
    ,(BswU1)BSW_COM_CH_PNCNUM_22
#endif
#if ( BSW_COM_NETWORK_NUM > 23U )
    ,(BswU1)BSW_COM_CH_PNCNUM_23
#endif
#if ( BSW_COM_NETWORK_NUM > 24U )
    ,(BswU1)BSW_COM_CH_PNCNUM_24
#endif
#if ( BSW_COM_NETWORK_NUM > 25U )
    ,(BswU1)BSW_COM_CH_PNCNUM_25
#endif
#if ( BSW_COM_NETWORK_NUM > 26U )
    ,(BswU1)BSW_COM_CH_PNCNUM_26
#endif
#if ( BSW_COM_NETWORK_NUM > 27U )
    ,(BswU1)BSW_COM_CH_PNCNUM_27
#endif
#if ( BSW_COM_NETWORK_NUM > 28U )
    ,(BswU1)BSW_COM_CH_PNCNUM_28
#endif
#if ( BSW_COM_NETWORK_NUM > 29U )
    ,(BswU1)BSW_COM_CH_PNCNUM_29
#endif
#if ( BSW_COM_NETWORK_NUM > 30U )
    ,(BswU1)BSW_COM_CH_PNCNUM_30
#endif
#if ( BSW_COM_NETWORK_NUM > 31U )
    ,(BswU1)BSW_COM_CH_PNCNUM_31
#endif
};
#endif  /* ( BSW_COM_FUNC_PNCIPDU == BSW_USE ) */

BswConst BswU1  bsw_com_rom_u1NonAwakePwonWait[BSW_COM_NETWORK_NUM] =
{
    (BswU1)BSW_COM_CH00_NONAWKPWON_WT
#if (BSW_COM_NETWORK_NUM > 1U)
   ,(BswU1)BSW_COM_CH01_NONAWKPWON_WT
#endif
#if (BSW_COM_NETWORK_NUM > 2U)
   ,(BswU1)BSW_COM_CH02_NONAWKPWON_WT
#endif
#if (BSW_COM_NETWORK_NUM > 3U)
   ,(BswU1)BSW_COM_CH03_NONAWKPWON_WT
#endif
#if (BSW_COM_NETWORK_NUM > 4U)
   ,(BswU1)BSW_COM_CH04_NONAWKPWON_WT
#endif
#if (BSW_COM_NETWORK_NUM > 5U)
   ,(BswU1)BSW_COM_CH05_NONAWKPWON_WT
#endif
#if (BSW_COM_NETWORK_NUM > 6U)
   ,(BswU1)BSW_COM_CH06_NONAWKPWON_WT
#endif
#if (BSW_COM_NETWORK_NUM > 7U)
   ,(BswU1)BSW_COM_CH07_NONAWKPWON_WT
#endif
#if (BSW_COM_NETWORK_NUM > 8U)
   ,(BswU1)BSW_COM_CH08_NONAWKPWON_WT
#endif
#if (BSW_COM_NETWORK_NUM > 9U)
   ,(BswU1)BSW_COM_CH09_NONAWKPWON_WT
#endif
#if (BSW_COM_NETWORK_NUM > 10U)
   ,(BswU1)BSW_COM_CH10_NONAWKPWON_WT
#endif
#if (BSW_COM_NETWORK_NUM > 11U)
   ,(BswU1)BSW_COM_CH11_NONAWKPWON_WT
#endif
#if (BSW_COM_NETWORK_NUM > 12U)
   ,(BswU1)BSW_COM_CH12_NONAWKPWON_WT
#endif
#if (BSW_COM_NETWORK_NUM > 13U)
   ,(BswU1)BSW_COM_CH13_NONAWKPWON_WT
#endif
#if (BSW_COM_NETWORK_NUM > 14U)
   ,(BswU1)BSW_COM_CH14_NONAWKPWON_WT
#endif
#if (BSW_COM_NETWORK_NUM > 15U)
   ,(BswU1)BSW_COM_CH15_NONAWKPWON_WT
#endif
#if (BSW_COM_NETWORK_NUM > 16U)
   ,(BswU1)BSW_COM_CH16_NONAWKPWON_WT
#endif
#if (BSW_COM_NETWORK_NUM > 17U)
   ,(BswU1)BSW_COM_CH17_NONAWKPWON_WT
#endif
#if (BSW_COM_NETWORK_NUM > 18U)
   ,(BswU1)BSW_COM_CH18_NONAWKPWON_WT
#endif
#if (BSW_COM_NETWORK_NUM > 19U)
   ,(BswU1)BSW_COM_CH19_NONAWKPWON_WT
#endif
#if (BSW_COM_NETWORK_NUM > 20U)
   ,(BswU1)BSW_COM_CH20_NONAWKPWON_WT
#endif
#if (BSW_COM_NETWORK_NUM > 21U)
   ,(BswU1)BSW_COM_CH21_NONAWKPWON_WT
#endif
#if (BSW_COM_NETWORK_NUM > 22U)
   ,(BswU1)BSW_COM_CH22_NONAWKPWON_WT
#endif
#if (BSW_COM_NETWORK_NUM > 23U)
   ,(BswU1)BSW_COM_CH23_NONAWKPWON_WT
#endif
#if (BSW_COM_NETWORK_NUM > 24U)
   ,(BswU1)BSW_COM_CH24_NONAWKPWON_WT
#endif
#if (BSW_COM_NETWORK_NUM > 25U)
   ,(BswU1)BSW_COM_CH25_NONAWKPWON_WT
#endif
#if (BSW_COM_NETWORK_NUM > 26U)
   ,(BswU1)BSW_COM_CH26_NONAWKPWON_WT
#endif
#if (BSW_COM_NETWORK_NUM > 27U)
   ,(BswU1)BSW_COM_CH27_NONAWKPWON_WT
#endif
#if (BSW_COM_NETWORK_NUM > 28U)
   ,(BswU1)BSW_COM_CH28_NONAWKPWON_WT
#endif
#if (BSW_COM_NETWORK_NUM > 29U)
   ,(BswU1)BSW_COM_CH29_NONAWKPWON_WT
#endif
#if (BSW_COM_NETWORK_NUM > 30U)
   ,(BswU1)BSW_COM_CH30_NONAWKPWON_WT
#endif
#if (BSW_COM_NETWORK_NUM > 31U)
   ,(BswU1)BSW_COM_CH31_NONAWKPWON_WT
#endif
};

void (* BswConst bsw_com_rom_ptInitAllTxReqFunc)( void ) = BSW_COM_INITALLTXREQST_FUNC;
void (* BswConst bsw_com_rom_ptInitSndNTimFunc)( void ) = BSW_COM_INITSENDNTIMES_FUNC;
void (* BswConst bsw_com_rom_ptInitChgPrdFunc)( void ) = BSW_COM_INITCHGPRD_FUNC;

/*------------------------------------*/
/* Transmission unit (TX)             */
/*------------------------------------*/
/* ROM table for constant reference */
BswConst        BswU2  bsw_com_rom_u2BITINDNUM            = (BswU2)BSW_COM_BITIND_SIZE;
BswConst        BswU1  bsw_com_rom_u1DLYRTRGPRD           = (BswU1)BSW_COM_TX_DLYRTRGPRD_USE;
BswConst        BswU1  bsw_com_rom_u1TXDLYBYMSG           = (BswU1)BSW_COM_TX_DLYBYMSG_USE;
BswConst        BswU1  bsw_com_rom_u1TXDLYSW              = (BswU1)BSW_COM_TX_DLYSW_USE;
BswConst        BswU1  bsw_com_rom_u1TXTIMEOUT            = (BswU1)BSW_COM_TX_TIMEOUT_USE;
BswConst        BswU1  bsw_com_rom_u1EVTAWAKEFUNC         = (BswU1)BSW_COM_EVENTAWAKE_USE;
BswConst        BswU2  bsw_com_rom_u2EVDELAYTIME = BSW_COM_u2MILSEC_RUP(BSW_COM_EVMSG_DELAY_TIME);

BswConst        BswU1  bsw_com_rom_u1RETRIGGER[BSW_COM_NETWORK_NUM] =
{
                             (BswU1)BSW_COM_CH00_TIMER_RETRIGGER
#if (BSW_COM_NETWORK_NUM > 1U)
                            ,(BswU1)BSW_COM_CH01_TIMER_RETRIGGER
#endif
#if (BSW_COM_NETWORK_NUM > 2U)
                            ,(BswU1)BSW_COM_CH02_TIMER_RETRIGGER
#endif
#if (BSW_COM_NETWORK_NUM > 3U)
                            ,(BswU1)BSW_COM_CH03_TIMER_RETRIGGER
#endif
#if (BSW_COM_NETWORK_NUM > 4U)
                            ,(BswU1)BSW_COM_CH04_TIMER_RETRIGGER
#endif
#if (BSW_COM_NETWORK_NUM > 5U)
                            ,(BswU1)BSW_COM_CH05_TIMER_RETRIGGER
#endif
#if (BSW_COM_NETWORK_NUM > 6U)
                            ,(BswU1)BSW_COM_CH06_TIMER_RETRIGGER
#endif
#if (BSW_COM_NETWORK_NUM > 7U)
                            ,(BswU1)BSW_COM_CH07_TIMER_RETRIGGER
#endif
#if (BSW_COM_NETWORK_NUM > 8U)
                            ,(BswU1)BSW_COM_CH08_TIMER_RETRIGGER
#endif
#if (BSW_COM_NETWORK_NUM > 9U)
                            ,(BswU1)BSW_COM_CH09_TIMER_RETRIGGER
#endif
#if (BSW_COM_NETWORK_NUM > 10U)
                            ,(BswU1)BSW_COM_CH10_TIMER_RETRIGGER
#endif
#if (BSW_COM_NETWORK_NUM > 11U)
                            ,(BswU1)BSW_COM_CH11_TIMER_RETRIGGER
#endif
#if (BSW_COM_NETWORK_NUM > 12U)
                            ,(BswU1)BSW_COM_CH12_TIMER_RETRIGGER
#endif
#if (BSW_COM_NETWORK_NUM > 13U)
                            ,(BswU1)BSW_COM_CH13_TIMER_RETRIGGER
#endif
#if (BSW_COM_NETWORK_NUM > 14U)
                            ,(BswU1)BSW_COM_CH14_TIMER_RETRIGGER
#endif
#if (BSW_COM_NETWORK_NUM > 15U)
                            ,(BswU1)BSW_COM_CH15_TIMER_RETRIGGER
#endif
#if (BSW_COM_NETWORK_NUM > 16U)
                            ,(BswU1)BSW_COM_CH16_TIMER_RETRIGGER
#endif
#if (BSW_COM_NETWORK_NUM > 17U)
                            ,(BswU1)BSW_COM_CH17_TIMER_RETRIGGER
#endif
#if (BSW_COM_NETWORK_NUM > 18U)
                            ,(BswU1)BSW_COM_CH18_TIMER_RETRIGGER
#endif
#if (BSW_COM_NETWORK_NUM > 19U)
                            ,(BswU1)BSW_COM_CH19_TIMER_RETRIGGER
#endif
#if (BSW_COM_NETWORK_NUM > 20U)
                            ,(BswU1)BSW_COM_CH20_TIMER_RETRIGGER
#endif
#if (BSW_COM_NETWORK_NUM > 21U)
                            ,(BswU1)BSW_COM_CH21_TIMER_RETRIGGER
#endif
#if (BSW_COM_NETWORK_NUM > 22U)
                            ,(BswU1)BSW_COM_CH22_TIMER_RETRIGGER
#endif
#if (BSW_COM_NETWORK_NUM > 23U)
                            ,(BswU1)BSW_COM_CH23_TIMER_RETRIGGER
#endif
#if (BSW_COM_NETWORK_NUM > 24U)
                            ,(BswU1)BSW_COM_CH24_TIMER_RETRIGGER
#endif
#if (BSW_COM_NETWORK_NUM > 25U)
                            ,(BswU1)BSW_COM_CH25_TIMER_RETRIGGER
#endif
#if (BSW_COM_NETWORK_NUM > 26U)
                            ,(BswU1)BSW_COM_CH26_TIMER_RETRIGGER
#endif
#if (BSW_COM_NETWORK_NUM > 27U)
                            ,(BswU1)BSW_COM_CH27_TIMER_RETRIGGER
#endif
#if (BSW_COM_NETWORK_NUM > 28U)
                            ,(BswU1)BSW_COM_CH28_TIMER_RETRIGGER
#endif
#if (BSW_COM_NETWORK_NUM > 29U)
                            ,(BswU1)BSW_COM_CH29_TIMER_RETRIGGER
#endif
#if (BSW_COM_NETWORK_NUM > 30U)
                            ,(BswU1)BSW_COM_CH30_TIMER_RETRIGGER
#endif
#if (BSW_COM_NETWORK_NUM > 31U)
                            ,(BswU1)BSW_COM_CH31_TIMER_RETRIGGER
#endif
};

BswConst        BswU1  bsw_com_rom_u1TXDLY[BSW_COM_NETWORK_NUM] =
{
                             (BswU1)BSW_COM_CH00_TX_DLYMODE
#if (BSW_COM_NETWORK_NUM > 1U)
                            ,(BswU1)BSW_COM_CH01_TX_DLYMODE
#endif
#if (BSW_COM_NETWORK_NUM > 2U)
                            ,(BswU1)BSW_COM_CH02_TX_DLYMODE
#endif
#if (BSW_COM_NETWORK_NUM > 3U)
                            ,(BswU1)BSW_COM_CH03_TX_DLYMODE
#endif
#if (BSW_COM_NETWORK_NUM > 4U)
                            ,(BswU1)BSW_COM_CH04_TX_DLYMODE
#endif
#if (BSW_COM_NETWORK_NUM > 5U)
                            ,(BswU1)BSW_COM_CH05_TX_DLYMODE
#endif
#if (BSW_COM_NETWORK_NUM > 6U)
                            ,(BswU1)BSW_COM_CH06_TX_DLYMODE
#endif
#if (BSW_COM_NETWORK_NUM > 7U)
                            ,(BswU1)BSW_COM_CH07_TX_DLYMODE
#endif
#if (BSW_COM_NETWORK_NUM > 8U)
                            ,(BswU1)BSW_COM_CH08_TX_DLYMODE
#endif
#if (BSW_COM_NETWORK_NUM > 9U)
                            ,(BswU1)BSW_COM_CH09_TX_DLYMODE
#endif
#if (BSW_COM_NETWORK_NUM > 10U)
                            ,(BswU1)BSW_COM_CH10_TX_DLYMODE
#endif
#if (BSW_COM_NETWORK_NUM > 11U)
                            ,(BswU1)BSW_COM_CH11_TX_DLYMODE
#endif
#if (BSW_COM_NETWORK_NUM > 12U)
                            ,(BswU1)BSW_COM_CH12_TX_DLYMODE
#endif
#if (BSW_COM_NETWORK_NUM > 13U)
                            ,(BswU1)BSW_COM_CH13_TX_DLYMODE
#endif
#if (BSW_COM_NETWORK_NUM > 14U)
                            ,(BswU1)BSW_COM_CH14_TX_DLYMODE
#endif
#if (BSW_COM_NETWORK_NUM > 15U)
                            ,(BswU1)BSW_COM_CH15_TX_DLYMODE
#endif
#if (BSW_COM_NETWORK_NUM > 16U)
                            ,(BswU1)BSW_COM_CH16_TX_DLYMODE
#endif
#if (BSW_COM_NETWORK_NUM > 17U)
                            ,(BswU1)BSW_COM_CH17_TX_DLYMODE
#endif
#if (BSW_COM_NETWORK_NUM > 18U)
                            ,(BswU1)BSW_COM_CH18_TX_DLYMODE
#endif
#if (BSW_COM_NETWORK_NUM > 19U)
                            ,(BswU1)BSW_COM_CH19_TX_DLYMODE
#endif
#if (BSW_COM_NETWORK_NUM > 20U)
                            ,(BswU1)BSW_COM_CH20_TX_DLYMODE
#endif
#if (BSW_COM_NETWORK_NUM > 21U)
                            ,(BswU1)BSW_COM_CH21_TX_DLYMODE
#endif
#if (BSW_COM_NETWORK_NUM > 22U)
                            ,(BswU1)BSW_COM_CH22_TX_DLYMODE
#endif
#if (BSW_COM_NETWORK_NUM > 23U)
                            ,(BswU1)BSW_COM_CH23_TX_DLYMODE
#endif
#if (BSW_COM_NETWORK_NUM > 24U)
                            ,(BswU1)BSW_COM_CH24_TX_DLYMODE
#endif
#if (BSW_COM_NETWORK_NUM > 25U)
                            ,(BswU1)BSW_COM_CH25_TX_DLYMODE
#endif
#if (BSW_COM_NETWORK_NUM > 26U)
                            ,(BswU1)BSW_COM_CH26_TX_DLYMODE
#endif
#if (BSW_COM_NETWORK_NUM > 27U)
                            ,(BswU1)BSW_COM_CH27_TX_DLYMODE
#endif
#if (BSW_COM_NETWORK_NUM > 28U)
                            ,(BswU1)BSW_COM_CH28_TX_DLYMODE
#endif
#if (BSW_COM_NETWORK_NUM > 29U)
                            ,(BswU1)BSW_COM_CH29_TX_DLYMODE
#endif
#if (BSW_COM_NETWORK_NUM > 30U)
                            ,(BswU1)BSW_COM_CH30_TX_DLYMODE
#endif
#if (BSW_COM_NETWORK_NUM > 31U)
                            ,(BswU1)BSW_COM_CH31_TX_DLYMODE
#endif
};

BswConst        BswU1  bsw_com_rom_u1EVTRTRG[BSW_COM_NETWORK_NUM] =
{
                             (BswU1)BSW_COM_CH00_TX_EVTRTRGMODE
#if (BSW_COM_NETWORK_NUM > 1U)
                            ,(BswU1)BSW_COM_CH01_TX_EVTRTRGMODE
#endif
#if (BSW_COM_NETWORK_NUM > 2U)
                            ,(BswU1)BSW_COM_CH02_TX_EVTRTRGMODE
#endif
#if (BSW_COM_NETWORK_NUM > 3U)
                            ,(BswU1)BSW_COM_CH03_TX_EVTRTRGMODE
#endif
#if (BSW_COM_NETWORK_NUM > 4U)
                            ,(BswU1)BSW_COM_CH04_TX_EVTRTRGMODE
#endif
#if (BSW_COM_NETWORK_NUM > 5U)
                            ,(BswU1)BSW_COM_CH05_TX_EVTRTRGMODE
#endif
#if (BSW_COM_NETWORK_NUM > 6U)
                            ,(BswU1)BSW_COM_CH06_TX_EVTRTRGMODE
#endif
#if (BSW_COM_NETWORK_NUM > 7U)
                            ,(BswU1)BSW_COM_CH07_TX_EVTRTRGMODE
#endif
#if (BSW_COM_NETWORK_NUM > 8U)
                            ,(BswU1)BSW_COM_CH08_TX_EVTRTRGMODE
#endif
#if (BSW_COM_NETWORK_NUM > 9U)
                            ,(BswU1)BSW_COM_CH09_TX_EVTRTRGMODE
#endif
#if (BSW_COM_NETWORK_NUM > 10U)
                            ,(BswU1)BSW_COM_CH10_TX_EVTRTRGMODE
#endif
#if (BSW_COM_NETWORK_NUM > 11U)
                            ,(BswU1)BSW_COM_CH11_TX_EVTRTRGMODE
#endif
#if (BSW_COM_NETWORK_NUM > 12U)
                            ,(BswU1)BSW_COM_CH12_TX_EVTRTRGMODE
#endif
#if (BSW_COM_NETWORK_NUM > 13U)
                            ,(BswU1)BSW_COM_CH13_TX_EVTRTRGMODE
#endif
#if (BSW_COM_NETWORK_NUM > 14U)
                            ,(BswU1)BSW_COM_CH14_TX_EVTRTRGMODE
#endif
#if (BSW_COM_NETWORK_NUM > 15U)
                            ,(BswU1)BSW_COM_CH15_TX_EVTRTRGMODE
#endif
#if (BSW_COM_NETWORK_NUM > 16U)
                            ,(BswU1)BSW_COM_CH16_TX_EVTRTRGMODE
#endif
#if (BSW_COM_NETWORK_NUM > 17U)
                            ,(BswU1)BSW_COM_CH17_TX_EVTRTRGMODE
#endif
#if (BSW_COM_NETWORK_NUM > 18U)
                            ,(BswU1)BSW_COM_CH18_TX_EVTRTRGMODE
#endif
#if (BSW_COM_NETWORK_NUM > 19U)
                            ,(BswU1)BSW_COM_CH19_TX_EVTRTRGMODE
#endif
#if (BSW_COM_NETWORK_NUM > 20U)
                            ,(BswU1)BSW_COM_CH20_TX_EVTRTRGMODE
#endif
#if (BSW_COM_NETWORK_NUM > 21U)
                            ,(BswU1)BSW_COM_CH21_TX_EVTRTRGMODE
#endif
#if (BSW_COM_NETWORK_NUM > 22U)
                            ,(BswU1)BSW_COM_CH22_TX_EVTRTRGMODE
#endif
#if (BSW_COM_NETWORK_NUM > 23U)
                            ,(BswU1)BSW_COM_CH23_TX_EVTRTRGMODE
#endif
#if (BSW_COM_NETWORK_NUM > 24U)
                            ,(BswU1)BSW_COM_CH24_TX_EVTRTRGMODE
#endif
#if (BSW_COM_NETWORK_NUM > 25U)
                            ,(BswU1)BSW_COM_CH25_TX_EVTRTRGMODE
#endif
#if (BSW_COM_NETWORK_NUM > 26U)
                            ,(BswU1)BSW_COM_CH26_TX_EVTRTRGMODE
#endif
#if (BSW_COM_NETWORK_NUM > 27U)
                            ,(BswU1)BSW_COM_CH27_TX_EVTRTRGMODE
#endif
#if (BSW_COM_NETWORK_NUM > 28U)
                            ,(BswU1)BSW_COM_CH28_TX_EVTRTRGMODE
#endif
#if (BSW_COM_NETWORK_NUM > 29U)
                            ,(BswU1)BSW_COM_CH29_TX_EVTRTRGMODE
#endif
#if (BSW_COM_NETWORK_NUM > 30U)
                            ,(BswU1)BSW_COM_CH30_TX_EVTRTRGMODE
#endif
#if (BSW_COM_NETWORK_NUM > 31U)
                            ,(BswU1)BSW_COM_CH31_TX_EVTRTRGMODE
#endif
};

BswConst        BswU2  bsw_com_rom_u2SENDSTART[BSW_COM_NETWORK_NUM] =
{
                            BSW_COM_u2MILSEC_RUP(BSW_BSWM_CS_SND_START_PW_DIRECT(0))
#if (BSW_COM_NETWORK_NUM > 1U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_BSWM_CS_SND_START_PW_DIRECT(1))
#endif
#if (BSW_COM_NETWORK_NUM > 2U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_BSWM_CS_SND_START_PW_DIRECT(2))
#endif
#if (BSW_COM_NETWORK_NUM > 3U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_BSWM_CS_SND_START_PW_DIRECT(3))
#endif
#if (BSW_COM_NETWORK_NUM > 4U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_BSWM_CS_SND_START_PW_DIRECT(4))
#endif
#if (BSW_COM_NETWORK_NUM > 5U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_BSWM_CS_SND_START_PW_DIRECT(5))
#endif
#if (BSW_COM_NETWORK_NUM > 6U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_BSWM_CS_SND_START_PW_DIRECT(6))
#endif
#if (BSW_COM_NETWORK_NUM > 7U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_BSWM_CS_SND_START_PW_DIRECT(7))
#endif
#if (BSW_COM_NETWORK_NUM > 8U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_BSWM_CS_SND_START_PW_DIRECT(8))
#endif
#if (BSW_COM_NETWORK_NUM > 9U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_BSWM_CS_SND_START_PW_DIRECT(9))
#endif
#if (BSW_COM_NETWORK_NUM > 10U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_BSWM_CS_SND_START_PW_DIRECT(10))
#endif
#if (BSW_COM_NETWORK_NUM > 11U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_BSWM_CS_SND_START_PW_DIRECT(11))
#endif
#if (BSW_COM_NETWORK_NUM > 12U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_BSWM_CS_SND_START_PW_DIRECT(12))
#endif
#if (BSW_COM_NETWORK_NUM > 13U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_BSWM_CS_SND_START_PW_DIRECT(13))
#endif
#if (BSW_COM_NETWORK_NUM > 14U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_BSWM_CS_SND_START_PW_DIRECT(14))
#endif
#if (BSW_COM_NETWORK_NUM > 15U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_BSWM_CS_SND_START_PW_DIRECT(15))
#endif
#if (BSW_COM_NETWORK_NUM > 16U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_BSWM_CS_SND_START_PW_DIRECT(16))
#endif
#if (BSW_COM_NETWORK_NUM > 17U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_BSWM_CS_SND_START_PW_DIRECT(17))
#endif
#if (BSW_COM_NETWORK_NUM > 18U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_BSWM_CS_SND_START_PW_DIRECT(18))
#endif
#if (BSW_COM_NETWORK_NUM > 19U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_BSWM_CS_SND_START_PW_DIRECT(19))
#endif
#if (BSW_COM_NETWORK_NUM > 20U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_BSWM_CS_SND_START_PW_DIRECT(20))
#endif
#if (BSW_COM_NETWORK_NUM > 21U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_BSWM_CS_SND_START_PW_DIRECT(21))
#endif
#if (BSW_COM_NETWORK_NUM > 22U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_BSWM_CS_SND_START_PW_DIRECT(22))
#endif
#if (BSW_COM_NETWORK_NUM > 23U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_BSWM_CS_SND_START_PW_DIRECT(23))
#endif
#if (BSW_COM_NETWORK_NUM > 24U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_BSWM_CS_SND_START_PW_DIRECT(24))
#endif
#if (BSW_COM_NETWORK_NUM > 25U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_BSWM_CS_SND_START_PW_DIRECT(25))
#endif
#if (BSW_COM_NETWORK_NUM > 26U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_BSWM_CS_SND_START_PW_DIRECT(26))
#endif
#if (BSW_COM_NETWORK_NUM > 27U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_BSWM_CS_SND_START_PW_DIRECT(27))
#endif
#if (BSW_COM_NETWORK_NUM > 28U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_BSWM_CS_SND_START_PW_DIRECT(28))
#endif
#if (BSW_COM_NETWORK_NUM > 29U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_BSWM_CS_SND_START_PW_DIRECT(29))
#endif
#if (BSW_COM_NETWORK_NUM > 30U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_BSWM_CS_SND_START_PW_DIRECT(30))
#endif
#if (BSW_COM_NETWORK_NUM > 31U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_BSWM_CS_SND_START_PW_DIRECT(31))
#endif
};

BswConst        BswU2  bsw_com_rom_u2TXLIM[BSW_COM_NETWORK_NUM] =
{
                             (BswU2)BSW_COM_CH00_TXTIMESLIMIT
#if (BSW_COM_NETWORK_NUM > 1U)
                            ,(BswU2)BSW_COM_CH01_TXTIMESLIMIT
#endif
#if (BSW_COM_NETWORK_NUM > 2U)
                            ,(BswU2)BSW_COM_CH02_TXTIMESLIMIT
#endif
#if (BSW_COM_NETWORK_NUM > 3U)
                            ,(BswU2)BSW_COM_CH03_TXTIMESLIMIT
#endif
#if (BSW_COM_NETWORK_NUM > 4U)
                            ,(BswU2)BSW_COM_CH04_TXTIMESLIMIT
#endif
#if (BSW_COM_NETWORK_NUM > 5U)
                            ,(BswU2)BSW_COM_CH05_TXTIMESLIMIT
#endif
#if (BSW_COM_NETWORK_NUM > 6U)
                            ,(BswU2)BSW_COM_CH06_TXTIMESLIMIT
#endif
#if (BSW_COM_NETWORK_NUM > 7U)
                            ,(BswU2)BSW_COM_CH07_TXTIMESLIMIT
#endif
#if (BSW_COM_NETWORK_NUM > 8U)
                            ,(BswU2)BSW_COM_CH08_TXTIMESLIMIT
#endif
#if (BSW_COM_NETWORK_NUM > 9U)
                            ,(BswU2)BSW_COM_CH09_TXTIMESLIMIT
#endif
#if (BSW_COM_NETWORK_NUM > 10U)
                            ,(BswU2)BSW_COM_CH10_TXTIMESLIMIT
#endif
#if (BSW_COM_NETWORK_NUM > 11U)
                            ,(BswU2)BSW_COM_CH11_TXTIMESLIMIT
#endif
#if (BSW_COM_NETWORK_NUM > 12U)
                            ,(BswU2)BSW_COM_CH12_TXTIMESLIMIT
#endif
#if (BSW_COM_NETWORK_NUM > 13U)
                            ,(BswU2)BSW_COM_CH13_TXTIMESLIMIT
#endif
#if (BSW_COM_NETWORK_NUM > 14U)
                            ,(BswU2)BSW_COM_CH14_TXTIMESLIMIT
#endif
#if (BSW_COM_NETWORK_NUM > 15U)
                            ,(BswU2)BSW_COM_CH15_TXTIMESLIMIT
#endif
#if (BSW_COM_NETWORK_NUM > 16U)
                            ,(BswU2)BSW_COM_CH16_TXTIMESLIMIT
#endif
#if (BSW_COM_NETWORK_NUM > 17U)
                            ,(BswU2)BSW_COM_CH17_TXTIMESLIMIT
#endif
#if (BSW_COM_NETWORK_NUM > 18U)
                            ,(BswU2)BSW_COM_CH18_TXTIMESLIMIT
#endif
#if (BSW_COM_NETWORK_NUM > 19U)
                            ,(BswU2)BSW_COM_CH19_TXTIMESLIMIT
#endif
#if (BSW_COM_NETWORK_NUM > 20U)
                            ,(BswU2)BSW_COM_CH20_TXTIMESLIMIT
#endif
#if (BSW_COM_NETWORK_NUM > 21U)
                            ,(BswU2)BSW_COM_CH21_TXTIMESLIMIT
#endif
#if (BSW_COM_NETWORK_NUM > 22U)
                            ,(BswU2)BSW_COM_CH22_TXTIMESLIMIT
#endif
#if (BSW_COM_NETWORK_NUM > 23U)
                            ,(BswU2)BSW_COM_CH23_TXTIMESLIMIT
#endif
#if (BSW_COM_NETWORK_NUM > 24U)
                            ,(BswU2)BSW_COM_CH24_TXTIMESLIMIT
#endif
#if (BSW_COM_NETWORK_NUM > 25U)
                            ,(BswU2)BSW_COM_CH25_TXTIMESLIMIT
#endif
#if (BSW_COM_NETWORK_NUM > 26U)
                            ,(BswU2)BSW_COM_CH26_TXTIMESLIMIT
#endif
#if (BSW_COM_NETWORK_NUM > 27U)
                            ,(BswU2)BSW_COM_CH27_TXTIMESLIMIT
#endif
#if (BSW_COM_NETWORK_NUM > 28U)
                            ,(BswU2)BSW_COM_CH28_TXTIMESLIMIT
#endif
#if (BSW_COM_NETWORK_NUM > 29U)
                            ,(BswU2)BSW_COM_CH29_TXTIMESLIMIT
#endif
#if (BSW_COM_NETWORK_NUM > 30U)
                            ,(BswU2)BSW_COM_CH30_TXTIMESLIMIT
#endif
#if (BSW_COM_NETWORK_NUM > 31U)
                            ,(BswU2)BSW_COM_CH31_TXTIMESLIMIT
#endif
};

BswConst        BswU2  bsw_com_rom_u2BITINDCHTOP[BSW_COM_NETWORK_NUM] =
{
                             (BswU2)BSW_COM_BITIND_CH00_TOP
#if (BSW_COM_NETWORK_NUM > 1U)
                            ,(BswU2)BSW_COM_BITIND_CH01_TOP
#endif
#if (BSW_COM_NETWORK_NUM > 2U)
                            ,(BswU2)BSW_COM_BITIND_CH02_TOP
#endif
#if (BSW_COM_NETWORK_NUM > 3U)
                            ,(BswU2)BSW_COM_BITIND_CH03_TOP
#endif
#if (BSW_COM_NETWORK_NUM > 4U)
                            ,(BswU2)BSW_COM_BITIND_CH04_TOP
#endif
#if (BSW_COM_NETWORK_NUM > 5U)
                            ,(BswU2)BSW_COM_BITIND_CH05_TOP
#endif
#if (BSW_COM_NETWORK_NUM > 6U)
                            ,(BswU2)BSW_COM_BITIND_CH06_TOP
#endif
#if (BSW_COM_NETWORK_NUM > 7U)
                            ,(BswU2)BSW_COM_BITIND_CH07_TOP
#endif
#if (BSW_COM_NETWORK_NUM > 8U)
                            ,(BswU2)BSW_COM_BITIND_CH08_TOP
#endif
#if (BSW_COM_NETWORK_NUM > 9U)
                            ,(BswU2)BSW_COM_BITIND_CH09_TOP
#endif
#if (BSW_COM_NETWORK_NUM > 10U)
                            ,(BswU2)BSW_COM_BITIND_CH10_TOP
#endif
#if (BSW_COM_NETWORK_NUM > 11U)
                            ,(BswU2)BSW_COM_BITIND_CH11_TOP
#endif
#if (BSW_COM_NETWORK_NUM > 12U)
                            ,(BswU2)BSW_COM_BITIND_CH12_TOP
#endif
#if (BSW_COM_NETWORK_NUM > 13U)
                            ,(BswU2)BSW_COM_BITIND_CH13_TOP
#endif
#if (BSW_COM_NETWORK_NUM > 14U)
                            ,(BswU2)BSW_COM_BITIND_CH14_TOP
#endif
#if (BSW_COM_NETWORK_NUM > 15U)
                            ,(BswU2)BSW_COM_BITIND_CH15_TOP
#endif
#if (BSW_COM_NETWORK_NUM > 16U)
                            ,(BswU2)BSW_COM_BITIND_CH16_TOP
#endif
#if (BSW_COM_NETWORK_NUM > 17U)
                            ,(BswU2)BSW_COM_BITIND_CH17_TOP
#endif
#if (BSW_COM_NETWORK_NUM > 18U)
                            ,(BswU2)BSW_COM_BITIND_CH18_TOP
#endif
#if (BSW_COM_NETWORK_NUM > 19U)
                            ,(BswU2)BSW_COM_BITIND_CH19_TOP
#endif
#if (BSW_COM_NETWORK_NUM > 20U)
                            ,(BswU2)BSW_COM_BITIND_CH20_TOP
#endif
#if (BSW_COM_NETWORK_NUM > 21U)
                            ,(BswU2)BSW_COM_BITIND_CH21_TOP
#endif
#if (BSW_COM_NETWORK_NUM > 22U)
                            ,(BswU2)BSW_COM_BITIND_CH22_TOP
#endif
#if (BSW_COM_NETWORK_NUM > 23U)
                            ,(BswU2)BSW_COM_BITIND_CH23_TOP
#endif
#if (BSW_COM_NETWORK_NUM > 24U)
                            ,(BswU2)BSW_COM_BITIND_CH24_TOP
#endif
#if (BSW_COM_NETWORK_NUM > 25U)
                            ,(BswU2)BSW_COM_BITIND_CH25_TOP
#endif
#if (BSW_COM_NETWORK_NUM > 26U)
                            ,(BswU2)BSW_COM_BITIND_CH26_TOP
#endif
#if (BSW_COM_NETWORK_NUM > 27U)
                            ,(BswU2)BSW_COM_BITIND_CH27_TOP
#endif
#if (BSW_COM_NETWORK_NUM > 28U)
                            ,(BswU2)BSW_COM_BITIND_CH28_TOP
#endif
#if (BSW_COM_NETWORK_NUM > 29U)
                            ,(BswU2)BSW_COM_BITIND_CH29_TOP
#endif
#if (BSW_COM_NETWORK_NUM > 30U)
                            ,(BswU2)BSW_COM_BITIND_CH30_TOP
#endif
#if (BSW_COM_NETWORK_NUM > 31U)
                            ,(BswU2)BSW_COM_BITIND_CH31_TOP
#endif
};

void (* BswConst bsw_com_rom_ptAlvCntrFuncTx[BSW_COM_NETWORK_NUM])( PduIdType u2PduId, BswConstR PduInfoType *ptCanTrsMsg ) =
{
    BSW_COM_ALIVECOUNTER_FUNC_TX(00)
#if (BSW_COM_NETWORK_NUM > 1U)
   ,BSW_COM_ALIVECOUNTER_FUNC_TX(01)
#endif
#if (BSW_COM_NETWORK_NUM > 2U)
   ,BSW_COM_ALIVECOUNTER_FUNC_TX(02)
#endif
#if (BSW_COM_NETWORK_NUM > 3U)
   ,BSW_COM_ALIVECOUNTER_FUNC_TX(03)
#endif
#if (BSW_COM_NETWORK_NUM > 4U)
   ,BSW_COM_ALIVECOUNTER_FUNC_TX(04)
#endif
#if (BSW_COM_NETWORK_NUM > 5U)
   ,BSW_COM_ALIVECOUNTER_FUNC_TX(05)
#endif
#if (BSW_COM_NETWORK_NUM > 6U)
   ,BSW_COM_ALIVECOUNTER_FUNC_TX(06)
#endif
#if (BSW_COM_NETWORK_NUM > 7U)
   ,BSW_COM_ALIVECOUNTER_FUNC_TX(07)
#endif
#if (BSW_COM_NETWORK_NUM > 8U)
   ,BSW_COM_ALIVECOUNTER_FUNC_TX(08)
#endif
#if (BSW_COM_NETWORK_NUM > 9U)
   ,BSW_COM_ALIVECOUNTER_FUNC_TX(09)
#endif
#if (BSW_COM_NETWORK_NUM > 10U)
   ,BSW_COM_ALIVECOUNTER_FUNC_TX(10)
#endif
#if (BSW_COM_NETWORK_NUM > 11U)
   ,BSW_COM_ALIVECOUNTER_FUNC_TX(11)
#endif
#if (BSW_COM_NETWORK_NUM > 12U)
   ,BSW_COM_ALIVECOUNTER_FUNC_TX(12)
#endif
#if (BSW_COM_NETWORK_NUM > 13U)
   ,BSW_COM_ALIVECOUNTER_FUNC_TX(13)
#endif
#if (BSW_COM_NETWORK_NUM > 14U)
   ,BSW_COM_ALIVECOUNTER_FUNC_TX(14)
#endif
#if (BSW_COM_NETWORK_NUM > 15U)
   ,BSW_COM_ALIVECOUNTER_FUNC_TX(15)
#endif
#if (BSW_COM_NETWORK_NUM > 16U)
   ,BSW_COM_ALIVECOUNTER_FUNC_TX(16)
#endif
#if (BSW_COM_NETWORK_NUM > 17U)
   ,BSW_COM_ALIVECOUNTER_FUNC_TX(17)
#endif
#if (BSW_COM_NETWORK_NUM > 18U)
   ,BSW_COM_ALIVECOUNTER_FUNC_TX(18)
#endif
#if (BSW_COM_NETWORK_NUM > 19U)
   ,BSW_COM_ALIVECOUNTER_FUNC_TX(19)
#endif
#if (BSW_COM_NETWORK_NUM > 20U)
   ,BSW_COM_ALIVECOUNTER_FUNC_TX(20)
#endif
#if (BSW_COM_NETWORK_NUM > 21U)
   ,BSW_COM_ALIVECOUNTER_FUNC_TX(21)
#endif
#if (BSW_COM_NETWORK_NUM > 22U)
   ,BSW_COM_ALIVECOUNTER_FUNC_TX(22)
#endif
#if (BSW_COM_NETWORK_NUM > 23U)
   ,BSW_COM_ALIVECOUNTER_FUNC_TX(23)
#endif
#if (BSW_COM_NETWORK_NUM > 24U)
   ,BSW_COM_ALIVECOUNTER_FUNC_TX(24)
#endif
#if (BSW_COM_NETWORK_NUM > 25U)
   ,BSW_COM_ALIVECOUNTER_FUNC_TX(25)
#endif
#if (BSW_COM_NETWORK_NUM > 26U)
   ,BSW_COM_ALIVECOUNTER_FUNC_TX(26)
#endif
#if (BSW_COM_NETWORK_NUM > 27U)
   ,BSW_COM_ALIVECOUNTER_FUNC_TX(27)
#endif
#if (BSW_COM_NETWORK_NUM > 28U)
   ,BSW_COM_ALIVECOUNTER_FUNC_TX(28)
#endif
#if (BSW_COM_NETWORK_NUM > 29U)
   ,BSW_COM_ALIVECOUNTER_FUNC_TX(29)
#endif
#if (BSW_COM_NETWORK_NUM > 30U)
   ,BSW_COM_ALIVECOUNTER_FUNC_TX(30)
#endif
#if (BSW_COM_NETWORK_NUM > 31U)
   ,BSW_COM_ALIVECOUNTER_FUNC_TX(31)
#endif
};

BswConst    BswU1   bsw_com_rom_u1TXTIMEOUTMODE[BSW_COM_NETWORK_NUM] =
{
                             (BswU1)BSW_COM_CH00_TX_TIMEOUTMODE
#if (BSW_COM_NETWORK_NUM > 1U)
                            ,(BswU1)BSW_COM_CH01_TX_TIMEOUTMODE
#endif
#if (BSW_COM_NETWORK_NUM > 2U)
                            ,(BswU1)BSW_COM_CH02_TX_TIMEOUTMODE
#endif
#if (BSW_COM_NETWORK_NUM > 3U)
                            ,(BswU1)BSW_COM_CH03_TX_TIMEOUTMODE
#endif
#if (BSW_COM_NETWORK_NUM > 4U)
                            ,(BswU1)BSW_COM_CH04_TX_TIMEOUTMODE
#endif
#if (BSW_COM_NETWORK_NUM > 5U)
                            ,(BswU1)BSW_COM_CH05_TX_TIMEOUTMODE
#endif
#if (BSW_COM_NETWORK_NUM > 6U)
                            ,(BswU1)BSW_COM_CH06_TX_TIMEOUTMODE
#endif
#if (BSW_COM_NETWORK_NUM > 7U)
                            ,(BswU1)BSW_COM_CH07_TX_TIMEOUTMODE
#endif
#if (BSW_COM_NETWORK_NUM > 8U)
                            ,(BswU1)BSW_COM_CH08_TX_TIMEOUTMODE
#endif
#if (BSW_COM_NETWORK_NUM > 9U)
                            ,(BswU1)BSW_COM_CH09_TX_TIMEOUTMODE
#endif
#if (BSW_COM_NETWORK_NUM > 10U)
                            ,(BswU1)BSW_COM_CH10_TX_TIMEOUTMODE
#endif
#if (BSW_COM_NETWORK_NUM > 11U)
                            ,(BswU1)BSW_COM_CH11_TX_TIMEOUTMODE
#endif
#if (BSW_COM_NETWORK_NUM > 12U)
                            ,(BswU1)BSW_COM_CH12_TX_TIMEOUTMODE
#endif
#if (BSW_COM_NETWORK_NUM > 13U)
                            ,(BswU1)BSW_COM_CH13_TX_TIMEOUTMODE
#endif
#if (BSW_COM_NETWORK_NUM > 14U)
                            ,(BswU1)BSW_COM_CH14_TX_TIMEOUTMODE
#endif
#if (BSW_COM_NETWORK_NUM > 15U)
                            ,(BswU1)BSW_COM_CH15_TX_TIMEOUTMODE
#endif
#if (BSW_COM_NETWORK_NUM > 16U)
                            ,(BswU1)BSW_COM_CH16_TX_TIMEOUTMODE
#endif
#if (BSW_COM_NETWORK_NUM > 17U)
                            ,(BswU1)BSW_COM_CH17_TX_TIMEOUTMODE
#endif
#if (BSW_COM_NETWORK_NUM > 18U)
                            ,(BswU1)BSW_COM_CH18_TX_TIMEOUTMODE
#endif
#if (BSW_COM_NETWORK_NUM > 19U)
                            ,(BswU1)BSW_COM_CH19_TX_TIMEOUTMODE
#endif
#if (BSW_COM_NETWORK_NUM > 20U)
                            ,(BswU1)BSW_COM_CH20_TX_TIMEOUTMODE
#endif
#if (BSW_COM_NETWORK_NUM > 21U)
                            ,(BswU1)BSW_COM_CH21_TX_TIMEOUTMODE
#endif
#if (BSW_COM_NETWORK_NUM > 22U)
                            ,(BswU1)BSW_COM_CH22_TX_TIMEOUTMODE
#endif
#if (BSW_COM_NETWORK_NUM > 23U)
                            ,(BswU1)BSW_COM_CH23_TX_TIMEOUTMODE
#endif
#if (BSW_COM_NETWORK_NUM > 24U)
                            ,(BswU1)BSW_COM_CH24_TX_TIMEOUTMODE
#endif
#if (BSW_COM_NETWORK_NUM > 25U)
                            ,(BswU1)BSW_COM_CH25_TX_TIMEOUTMODE
#endif
#if (BSW_COM_NETWORK_NUM > 26U)
                            ,(BswU1)BSW_COM_CH26_TX_TIMEOUTMODE
#endif
#if (BSW_COM_NETWORK_NUM > 27U)
                            ,(BswU1)BSW_COM_CH27_TX_TIMEOUTMODE
#endif
#if (BSW_COM_NETWORK_NUM > 28U)
                            ,(BswU1)BSW_COM_CH28_TX_TIMEOUTMODE
#endif
#if (BSW_COM_NETWORK_NUM > 29U)
                            ,(BswU1)BSW_COM_CH29_TX_TIMEOUTMODE
#endif
#if (BSW_COM_NETWORK_NUM > 30U)
                            ,(BswU1)BSW_COM_CH30_TX_TIMEOUTMODE
#endif
#if (BSW_COM_NETWORK_NUM > 31U)
                            ,(BswU1)BSW_COM_CH31_TX_TIMEOUTMODE
#endif
};

BswConst    BswU1   bsw_com_rom_u1TXREQCONTINUE[BSW_COM_NETWORK_NUM] =
{
                             (BswU1)BSW_COM_CH00_TXREQ_CONTINUE
#if (BSW_COM_NETWORK_NUM > 1U)
                            ,(BswU1)BSW_COM_CH01_TXREQ_CONTINUE
#endif
#if (BSW_COM_NETWORK_NUM > 2U)
                            ,(BswU1)BSW_COM_CH02_TXREQ_CONTINUE
#endif
#if (BSW_COM_NETWORK_NUM > 3U)
                            ,(BswU1)BSW_COM_CH03_TXREQ_CONTINUE
#endif
#if (BSW_COM_NETWORK_NUM > 4U)
                            ,(BswU1)BSW_COM_CH04_TXREQ_CONTINUE
#endif
#if (BSW_COM_NETWORK_NUM > 5U)
                            ,(BswU1)BSW_COM_CH05_TXREQ_CONTINUE
#endif
#if (BSW_COM_NETWORK_NUM > 6U)
                            ,(BswU1)BSW_COM_CH06_TXREQ_CONTINUE
#endif
#if (BSW_COM_NETWORK_NUM > 7U)
                            ,(BswU1)BSW_COM_CH07_TXREQ_CONTINUE
#endif
#if (BSW_COM_NETWORK_NUM > 8U)
                            ,(BswU1)BSW_COM_CH08_TXREQ_CONTINUE
#endif
#if (BSW_COM_NETWORK_NUM > 9U)
                            ,(BswU1)BSW_COM_CH09_TXREQ_CONTINUE
#endif
#if (BSW_COM_NETWORK_NUM > 10U)
                            ,(BswU1)BSW_COM_CH10_TXREQ_CONTINUE
#endif
#if (BSW_COM_NETWORK_NUM > 11U)
                            ,(BswU1)BSW_COM_CH11_TXREQ_CONTINUE
#endif
#if (BSW_COM_NETWORK_NUM > 12U)
                            ,(BswU1)BSW_COM_CH12_TXREQ_CONTINUE
#endif
#if (BSW_COM_NETWORK_NUM > 13U)
                            ,(BswU1)BSW_COM_CH13_TXREQ_CONTINUE
#endif
#if (BSW_COM_NETWORK_NUM > 14U)
                            ,(BswU1)BSW_COM_CH14_TXREQ_CONTINUE
#endif
#if (BSW_COM_NETWORK_NUM > 15U)
                            ,(BswU1)BSW_COM_CH15_TXREQ_CONTINUE
#endif
#if (BSW_COM_NETWORK_NUM > 16U)
                            ,(BswU1)BSW_COM_CH16_TXREQ_CONTINUE
#endif
#if (BSW_COM_NETWORK_NUM > 17U)
                            ,(BswU1)BSW_COM_CH17_TXREQ_CONTINUE
#endif
#if (BSW_COM_NETWORK_NUM > 18U)
                            ,(BswU1)BSW_COM_CH18_TXREQ_CONTINUE
#endif
#if (BSW_COM_NETWORK_NUM > 19U)
                            ,(BswU1)BSW_COM_CH19_TXREQ_CONTINUE
#endif
#if (BSW_COM_NETWORK_NUM > 20U)
                            ,(BswU1)BSW_COM_CH20_TXREQ_CONTINUE
#endif
#if (BSW_COM_NETWORK_NUM > 21U)
                            ,(BswU1)BSW_COM_CH21_TXREQ_CONTINUE
#endif
#if (BSW_COM_NETWORK_NUM > 22U)
                            ,(BswU1)BSW_COM_CH22_TXREQ_CONTINUE
#endif
#if (BSW_COM_NETWORK_NUM > 23U)
                            ,(BswU1)BSW_COM_CH23_TXREQ_CONTINUE
#endif
#if (BSW_COM_NETWORK_NUM > 24U)
                            ,(BswU1)BSW_COM_CH24_TXREQ_CONTINUE
#endif
#if (BSW_COM_NETWORK_NUM > 25U)
                            ,(BswU1)BSW_COM_CH25_TXREQ_CONTINUE
#endif
#if (BSW_COM_NETWORK_NUM > 26U)
                            ,(BswU1)BSW_COM_CH26_TXREQ_CONTINUE
#endif
#if (BSW_COM_NETWORK_NUM > 27U)
                            ,(BswU1)BSW_COM_CH27_TXREQ_CONTINUE
#endif
#if (BSW_COM_NETWORK_NUM > 28U)
                            ,(BswU1)BSW_COM_CH28_TXREQ_CONTINUE
#endif
#if (BSW_COM_NETWORK_NUM > 29U)
                            ,(BswU1)BSW_COM_CH29_TXREQ_CONTINUE
#endif
#if (BSW_COM_NETWORK_NUM > 30U)
                            ,(BswU1)BSW_COM_CH30_TXREQ_CONTINUE
#endif
#if (BSW_COM_NETWORK_NUM > 31U)
                            ,(BswU1)BSW_COM_CH31_TXREQ_CONTINUE
#endif
};

#if ( BSW_COM_FUNC_PNCIPDU == BSW_USE )
/* PNC Periodic Transmission Offset Time */
BswConst        BswU2  bsw_com_rom_u2PncPeriodicOffset[BSW_COM_NETWORK_NUM] =
{
                            BSW_COM_u2MILSEC_RUP(BSW_COM_PNC_PERIODIC_OFFSET(0))
#if (BSW_COM_NETWORK_NUM > 1U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_COM_PNC_PERIODIC_OFFSET(1))
#endif
#if (BSW_COM_NETWORK_NUM > 2U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_COM_PNC_PERIODIC_OFFSET(2))
#endif
#if (BSW_COM_NETWORK_NUM > 3U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_COM_PNC_PERIODIC_OFFSET(3))
#endif
#if (BSW_COM_NETWORK_NUM > 4U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_COM_PNC_PERIODIC_OFFSET(4))
#endif
#if (BSW_COM_NETWORK_NUM > 5U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_COM_PNC_PERIODIC_OFFSET(5))
#endif
#if (BSW_COM_NETWORK_NUM > 6U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_COM_PNC_PERIODIC_OFFSET(6))
#endif
#if (BSW_COM_NETWORK_NUM > 7U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_COM_PNC_PERIODIC_OFFSET(7))
#endif
#if (BSW_COM_NETWORK_NUM > 8U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_COM_PNC_PERIODIC_OFFSET(8))
#endif
#if (BSW_COM_NETWORK_NUM > 9U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_COM_PNC_PERIODIC_OFFSET(9))
#endif
#if (BSW_COM_NETWORK_NUM > 10U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_COM_PNC_PERIODIC_OFFSET(10))
#endif
#if (BSW_COM_NETWORK_NUM > 11U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_COM_PNC_PERIODIC_OFFSET(11))
#endif
#if (BSW_COM_NETWORK_NUM > 12U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_COM_PNC_PERIODIC_OFFSET(12))
#endif
#if (BSW_COM_NETWORK_NUM > 13U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_COM_PNC_PERIODIC_OFFSET(13))
#endif
#if (BSW_COM_NETWORK_NUM > 14U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_COM_PNC_PERIODIC_OFFSET(14))
#endif
#if (BSW_COM_NETWORK_NUM > 15U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_COM_PNC_PERIODIC_OFFSET(15))
#endif
#if (BSW_COM_NETWORK_NUM > 16U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_COM_PNC_PERIODIC_OFFSET(16))
#endif
#if (BSW_COM_NETWORK_NUM > 17U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_COM_PNC_PERIODIC_OFFSET(17))
#endif
#if (BSW_COM_NETWORK_NUM > 18U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_COM_PNC_PERIODIC_OFFSET(18))
#endif
#if (BSW_COM_NETWORK_NUM > 19U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_COM_PNC_PERIODIC_OFFSET(19))
#endif
#if (BSW_COM_NETWORK_NUM > 20U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_COM_PNC_PERIODIC_OFFSET(20))
#endif
#if (BSW_COM_NETWORK_NUM > 21U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_COM_PNC_PERIODIC_OFFSET(21))
#endif
#if (BSW_COM_NETWORK_NUM > 22U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_COM_PNC_PERIODIC_OFFSET(22))
#endif
#if (BSW_COM_NETWORK_NUM > 23U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_COM_PNC_PERIODIC_OFFSET(23))
#endif
#if (BSW_COM_NETWORK_NUM > 24U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_COM_PNC_PERIODIC_OFFSET(24))
#endif
#if (BSW_COM_NETWORK_NUM > 25U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_COM_PNC_PERIODIC_OFFSET(25))
#endif
#if (BSW_COM_NETWORK_NUM > 26U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_COM_PNC_PERIODIC_OFFSET(26))
#endif
#if (BSW_COM_NETWORK_NUM > 27U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_COM_PNC_PERIODIC_OFFSET(27))
#endif
#if (BSW_COM_NETWORK_NUM > 28U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_COM_PNC_PERIODIC_OFFSET(28))
#endif
#if (BSW_COM_NETWORK_NUM > 29U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_COM_PNC_PERIODIC_OFFSET(29))
#endif
#if (BSW_COM_NETWORK_NUM > 30U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_COM_PNC_PERIODIC_OFFSET(30))
#endif
#if (BSW_COM_NETWORK_NUM > 31U)
                           ,BSW_COM_u2MILSEC_RUP(BSW_COM_PNC_PERIODIC_OFFSET(31))
#endif
};
#endif

void  (* BswConst bsw_com_rom_ptInitTxReqStFunc)( PduIdType u2PduId ) = BSW_COM_INITTXREQST_FUNC;
void  (* BswConst bsw_com_rom_ptSetTxReqStFunc)( PduIdType u2PduId, Bsw_Com_TxModeType u1TxMode ) = BSW_COM_SETTXREQST_FUNC;
BswU1 (* BswConst bsw_com_rom_ptGetTxReqStFunc)( PduIdType u2PduId ) = BSW_COM_GETTXREQST_FUNC;
void  (* BswConst bsw_com_rom_ptTransCfmFunc)( PduIdType u2PduId ) = BSW_COM_TRANSCFM_FUNC;
BswU2 (* BswConst bsw_com_rom_ptTxTimeoutFunc)( PduIdType u2PduId ) = BSW_COM_TXTIMEOUT_FUNC;
void  (* BswConst bsw_com_rom_ptSndNTimCntFunc)( void ) = BSW_COM_SENDNTIMESCNT_FUNC;
Bsw_Com_RetStatusType (* BswConst bsw_com_rom_ptChgPeriToNTimFunc)( PduIdType u2PduId, Bsw_Com_RetStatusType s1QueExist ) = BSW_COM_CHGPERITONTIM_FUNC;
void  (* BswConst bsw_com_rom_ptSndNTimMsgFunc)( PduIdType u2PduId ) = BSW_COM_SENDNTIMESMSG_FUNC;
void  (* BswConst bsw_com_rom_ptSetTxReqNTimFunc)( PduIdType u2PduId, Bsw_Com_TxModeType u1TxMode ) = BSW_COM_SETTXREQNTIMTIMER_FUNC;
void  (* BswConst bsw_com_rom_ptSetTxFinNTimFunc)( PduIdType u2PduId, Bsw_Com_TxModeType u1TxMode ) = BSW_COM_SETTXFINNTIMTIMER_FUNC;
void  (* BswConst bsw_com_rom_ptClrSndNTimChFunc)( Bsw_Com_NetworkType u1Network ) = BSW_COM_CLRSENDNTIMESCH_FUNC;
void  (* BswConst bsw_com_rom_ptClrSndNTimMsgFunc)( PduIdType u2PduId ) = BSW_COM_CLRSENDNTIMESMSG_FUNC;
void  (* BswConst bsw_com_rom_ptChgPrdCntFunc)( void ) = BSW_COM_CHGPRDCNT_FUNC;
void  (* BswConst bsw_com_rom_ptTxReqChgPrdFunc)( PduIdType u2PduId, Bsw_Com_TxModeType u1TxMode ) = BSW_COM_SETTXREQCHGPRD_FUNC;
void  (* BswConst bsw_com_rom_ptTxFinChgPrdFunc)( PduIdType u2PduId, Bsw_Com_TxModeType u1TxMode ) = BSW_COM_SETTXFINCHGPRD_FUNC;
Bsw_Com_RetStatusType (* BswConst bsw_com_rom_ptGetChgPrdStatFunc)( PduIdType u2PduId ) = BSW_COM_GETCHGPRDSTAT_FUNC;
void  (* BswConst bsw_com_tx_ptSetEventAwake)( NetworkHandleType Network ) = BSW_COM_SETEVENTAWAKE_FUNC;
BswU1 (* BswConst bsw_com_tx_ptTxWakeupEvent)( NetworkHandleType Network, PduIdType PduId ) = BSW_COM_TXWAKEUPEVENT_FUNC;
void  (* BswConst bsw_com_rom_ptInitPncTxStatFunc)( void ) = BSW_COM_INITPNCTXSTAT_FUNC;
void  (* BswConst bsw_com_rom_ptDeInitPncTxStFunc)( void ) = BSW_COM_SHUTDOWNPNCTXSTAT_FUNC;
void  (* BswConst bsw_com_rom_ptGetPncChTxStFunc)( NetworkHandleType Network, BswU4* ptPrevStat, BswU4* ptReqStat, BswU1* ptStatChg, BswU1* ptPncNum, BswU2* ptPncPeriOffset ) = BSW_COM_GETPNCCHTXST_FUNC;
void  (* BswConst bsw_com_rom_ptGetPncChTxEnStFunc)( NetworkHandleType Network, BswU1 u1PncNum, BswU4* ptReqStat, BswU1* ptStatChg ) = BSW_COM_GETPNCCHTXENST_FUNC;
BswU1 (* BswConst bsw_com_rom_ptChkPncIpduTxStFunc)( PduIdType u2PduId, BswU1 u1PncNum, BswConstR BswU4* ptPrevStat, BswConstR BswU4* ptReqStat ) = BSW_COM_CHKPNCIPDUTXST_FUNC;
void  (* BswConst bsw_com_rom_ptSetPncChTxStFunc)( NetworkHandleType Network, BswConstR BswU4* ptReqStat ) = BSW_COM_SETPNCCHTXST_FUNC;
void  (* BswConst bsw_com_rom_ptSetPncChTxEnStFunc)( NetworkHandleType Network, BswConstR BswU4* ptReqStat ) = BSW_COM_SETPNCCHTXENST_FUNC;
void  (* BswConst bsw_com_rom_ptSetPncIpduTxEnStFunc)( PduIdType u2PduId, BswU1 u1PncNum, BswConstR BswU4* ptIpduGrpStat, BswConstR BswU4* ptTxStat, BswU2 u2PncPeriOffset ) = BSW_COM_SETPNCTXIPDUTXSTS_FUNC;
BswU1 (* BswConst bsw_com_rom_ptGetPncIpduTxEnStFunc)( PduIdType u2PduId ) = BSW_COM_GETPNCIPDUTXENST_FUNC;
BswU1 (* BswConst bsw_com_rom_ptGetPncIpduPeriOfsFunc)( PduIdType u2PduId ) = BSW_COM_GETPNCIPDUPERIOFS_FUNC;
void  (* BswConst bsw_com_rom_ptSetPncIpduPrOfsOnFunc)( PduIdType u2PduId ) = BSW_COM_SETPNCIPDUPROFSON_FUNC;
BswU1 (* BswConst bsw_com_rom_ptGetPncChNumberFunc)( NetworkHandleType Network ) = BSW_COM_GETPNCCHNUMBER_FUNC;
void  (* BswConst bsw_com_rom_ptSetPncIpduFstDlyFunc)( PduIdType u2PduId, BswU1 u1PncNum ) = BSW_COM_SETPNCIPDUFSTDLY_FUNC;
BswU1 (* BswConst bsw_com_rom_ptGetPncIpduTxStFunc)( NetworkHandleType Network, PduIdType u2PduId ) = BSW_COM_GETPNCIPDUTXST_FUNC;
void  (* BswConst bsw_com_rom_ptJdgPncTxStProcFunc)( BswU1 u1PncNum, BswU1 u1IpduChgSts, BswU1 u1PncIpduChgSts, BswU1* ptIpduProc, BswU1* ptIpduSubProc ) = BSW_COM_JUDGEPNCTXSTPROC_FUNC;

/* Dummy definition when no transmission message */
#if (BSW_COM_TX_MSG_NUM == 0U)
BswConst Bsw_Com_TickTimeType bsw_com_u2TxDelayTbl[BSW_COM_DUMMY_SIZE] = {0U};
#endif /* BSW_COM_TX_MSG_NUM == 0 */

/* Dummy definition when not using per-message transmission delay */
#if ( (BSW_COM_TX_DLYBYMSG_USE != BSW_USE) || (BSW_COM_TX_MSG_NUM == 0U) )
BswConst Bsw_Com_TickTimeType bsw_com_u2DelayTbl[BSW_COM_DUMMY_SIZE] = {(BswU2)0U};
#endif /* (BSW_COM_TX_DLYBYMSG_USE != BSW_USE) || (BSW_COM_TX_MSG_NUM == 0U) */

/* Dummy definition when transmission delay time switching is disabled */
#if ( (BSW_COM_TX_DLYBYMSG_USE != BSW_USE) || (BSW_COM_TX_DLYSW_USE != BSW_USE) || (BSW_COM_TX_MSG_NUM == 0U) )
BswConst Bsw_Com_TickTimeType bsw_com_u2PrdDelayTbl[BSW_COM_DUMMY_SIZE] = {(BswU2)0U};
#endif /* (BSW_COM_CFG_TX_DLYBYMSG_USE != BSW_USE) || (BSW_COM_CFG_TX_DLYSW_USE != BSW_USE) || (BSW_COM_TX_MSG_NUM == 0U) */

/* Dummy definition when the transmission timeout function is disabled */
#if ( (BSW_COM_TX_TIMEOUT_USE != BSW_USE) || (BSW_COM_TX_MSG_NUM == 0U) )
BswConst Bsw_Com_TickTimeType bsw_com_u2TxTimeoutTbl[BSW_COM_DUMMY_SIZE] = {(BswU2)0U};
#endif /* (BSW_COM_TX_TIMEOUT_USE != BSW_USE) || (BSW_COM_TX_MSG_NUM == 0U) */

#if ( (BSW_COM_TX_TIMEOUT_USE != BSW_USE) || (BSW_COM_TX_MSG_NUM == 0U) || (BSW_COM_FIRSTTXTIMEOUT_USE != BSW_USE) )
BswConst Bsw_Com_TickTimeType bsw_com_u2FirstTxTimeoutTbl[BSW_COM_DUMMY_SIZE] = {(BswU2)0U};
#endif /* (BSW_COM_TX_TIMEOUT_USE != BSW_USE) || (BSW_COM_TX_MSG_NUM == 0U) || (BSW_COM_FIRSTTXTIMEOUT_USE != BSW_USE) */

/*------------------------------------*/
/* Receiving unit (RX)                */
/*------------------------------------*/
Std_ReturnType (* BswConst bsw_com_rom_ptAlvCntrFuncRx[BSW_COM_NETWORK_NUM])( PduIdType u2PduId, BswConstR PduInfoType *ptCanRcvMsg, BswU1 *ptPreviousCounter, BswU1 *ptReceivedCounter ) =
{
    BSW_COM_ALIVECOUNTER_FUNC_RX(00)
#if (BSW_COM_NETWORK_NUM > 1U)
   ,BSW_COM_ALIVECOUNTER_FUNC_RX(01)
#endif
#if (BSW_COM_NETWORK_NUM > 2U)
   ,BSW_COM_ALIVECOUNTER_FUNC_RX(02)
#endif
#if (BSW_COM_NETWORK_NUM > 3U)
   ,BSW_COM_ALIVECOUNTER_FUNC_RX(03)
#endif
#if (BSW_COM_NETWORK_NUM > 4U)
   ,BSW_COM_ALIVECOUNTER_FUNC_RX(04)
#endif
#if (BSW_COM_NETWORK_NUM > 5U)
   ,BSW_COM_ALIVECOUNTER_FUNC_RX(05)
#endif
#if (BSW_COM_NETWORK_NUM > 6U)
   ,BSW_COM_ALIVECOUNTER_FUNC_RX(06)
#endif
#if (BSW_COM_NETWORK_NUM > 7U)
   ,BSW_COM_ALIVECOUNTER_FUNC_RX(07)
#endif
#if (BSW_COM_NETWORK_NUM > 8U)
   ,BSW_COM_ALIVECOUNTER_FUNC_RX(08)
#endif
#if (BSW_COM_NETWORK_NUM > 9U)
   ,BSW_COM_ALIVECOUNTER_FUNC_RX(09)
#endif
#if (BSW_COM_NETWORK_NUM > 10U)
   ,BSW_COM_ALIVECOUNTER_FUNC_RX(10)
#endif
#if (BSW_COM_NETWORK_NUM > 11U)
   ,BSW_COM_ALIVECOUNTER_FUNC_RX(11)
#endif
#if (BSW_COM_NETWORK_NUM > 12U)
   ,BSW_COM_ALIVECOUNTER_FUNC_RX(12)
#endif
#if (BSW_COM_NETWORK_NUM > 13U)
   ,BSW_COM_ALIVECOUNTER_FUNC_RX(13)
#endif
#if (BSW_COM_NETWORK_NUM > 14U)
   ,BSW_COM_ALIVECOUNTER_FUNC_RX(14)
#endif
#if (BSW_COM_NETWORK_NUM > 15U)
   ,BSW_COM_ALIVECOUNTER_FUNC_RX(15)
#endif
#if (BSW_COM_NETWORK_NUM > 16U)
   ,BSW_COM_ALIVECOUNTER_FUNC_RX(16)
#endif
#if (BSW_COM_NETWORK_NUM > 17U)
   ,BSW_COM_ALIVECOUNTER_FUNC_RX(17)
#endif
#if (BSW_COM_NETWORK_NUM > 18U)
   ,BSW_COM_ALIVECOUNTER_FUNC_RX(18)
#endif
#if (BSW_COM_NETWORK_NUM > 19U)
   ,BSW_COM_ALIVECOUNTER_FUNC_RX(19)
#endif
#if (BSW_COM_NETWORK_NUM > 20U)
   ,BSW_COM_ALIVECOUNTER_FUNC_RX(20)
#endif
#if (BSW_COM_NETWORK_NUM > 21U)
   ,BSW_COM_ALIVECOUNTER_FUNC_RX(21)
#endif
#if (BSW_COM_NETWORK_NUM > 22U)
   ,BSW_COM_ALIVECOUNTER_FUNC_RX(22)
#endif
#if (BSW_COM_NETWORK_NUM > 23U)
   ,BSW_COM_ALIVECOUNTER_FUNC_RX(23)
#endif
#if (BSW_COM_NETWORK_NUM > 24U)
   ,BSW_COM_ALIVECOUNTER_FUNC_RX(24)
#endif
#if (BSW_COM_NETWORK_NUM > 25U)
   ,BSW_COM_ALIVECOUNTER_FUNC_RX(25)
#endif
#if (BSW_COM_NETWORK_NUM > 26U)
   ,BSW_COM_ALIVECOUNTER_FUNC_RX(26)
#endif
#if (BSW_COM_NETWORK_NUM > 27U)
   ,BSW_COM_ALIVECOUNTER_FUNC_RX(27)
#endif
#if (BSW_COM_NETWORK_NUM > 28U)
   ,BSW_COM_ALIVECOUNTER_FUNC_RX(28)
#endif
#if (BSW_COM_NETWORK_NUM > 29U)
   ,BSW_COM_ALIVECOUNTER_FUNC_RX(29)
#endif
#if (BSW_COM_NETWORK_NUM > 30U)
   ,BSW_COM_ALIVECOUNTER_FUNC_RX(30)
#endif
#if (BSW_COM_NETWORK_NUM > 31U)
   ,BSW_COM_ALIVECOUNTER_FUNC_RX(31)
#endif
};

BswConst BswU1  bsw_com_rom_u1RxTimeOutMskStop[BSW_COM_NETWORK_NUM] =
{
    (BswU1)BSW_COM_CH00_RXTOUTMSKSTOP
#if (BSW_COM_NETWORK_NUM > 1U)
   ,(BswU1)BSW_COM_CH01_RXTOUTMSKSTOP
#endif
#if (BSW_COM_NETWORK_NUM > 2U)
   ,(BswU1)BSW_COM_CH02_RXTOUTMSKSTOP
#endif
#if (BSW_COM_NETWORK_NUM > 3U)
   ,(BswU1)BSW_COM_CH03_RXTOUTMSKSTOP
#endif
#if (BSW_COM_NETWORK_NUM > 4U)
   ,(BswU1)BSW_COM_CH04_RXTOUTMSKSTOP
#endif
#if (BSW_COM_NETWORK_NUM > 5U)
   ,(BswU1)BSW_COM_CH05_RXTOUTMSKSTOP
#endif
#if (BSW_COM_NETWORK_NUM > 6U)
   ,(BswU1)BSW_COM_CH06_RXTOUTMSKSTOP
#endif
#if (BSW_COM_NETWORK_NUM > 7U)
   ,(BswU1)BSW_COM_CH07_RXTOUTMSKSTOP
#endif
#if (BSW_COM_NETWORK_NUM > 8U)
   ,(BswU1)BSW_COM_CH08_RXTOUTMSKSTOP
#endif
#if (BSW_COM_NETWORK_NUM > 9U)
   ,(BswU1)BSW_COM_CH09_RXTOUTMSKSTOP
#endif
#if (BSW_COM_NETWORK_NUM > 10U)
   ,(BswU1)BSW_COM_CH10_RXTOUTMSKSTOP
#endif
#if (BSW_COM_NETWORK_NUM > 11U)
   ,(BswU1)BSW_COM_CH11_RXTOUTMSKSTOP
#endif
#if (BSW_COM_NETWORK_NUM > 12U)
   ,(BswU1)BSW_COM_CH12_RXTOUTMSKSTOP
#endif
#if (BSW_COM_NETWORK_NUM > 13U)
   ,(BswU1)BSW_COM_CH13_RXTOUTMSKSTOP
#endif
#if (BSW_COM_NETWORK_NUM > 14U)
   ,(BswU1)BSW_COM_CH14_RXTOUTMSKSTOP
#endif
#if (BSW_COM_NETWORK_NUM > 15U)
   ,(BswU1)BSW_COM_CH15_RXTOUTMSKSTOP
#endif
#if (BSW_COM_NETWORK_NUM > 16U)
   ,(BswU1)BSW_COM_CH16_RXTOUTMSKSTOP
#endif
#if (BSW_COM_NETWORK_NUM > 17U)
   ,(BswU1)BSW_COM_CH17_RXTOUTMSKSTOP
#endif
#if (BSW_COM_NETWORK_NUM > 18U)
   ,(BswU1)BSW_COM_CH18_RXTOUTMSKSTOP
#endif
#if (BSW_COM_NETWORK_NUM > 19U)
   ,(BswU1)BSW_COM_CH19_RXTOUTMSKSTOP
#endif
#if (BSW_COM_NETWORK_NUM > 20U)
   ,(BswU1)BSW_COM_CH20_RXTOUTMSKSTOP
#endif
#if (BSW_COM_NETWORK_NUM > 21U)
   ,(BswU1)BSW_COM_CH21_RXTOUTMSKSTOP
#endif
#if (BSW_COM_NETWORK_NUM > 22U)
   ,(BswU1)BSW_COM_CH22_RXTOUTMSKSTOP
#endif
#if (BSW_COM_NETWORK_NUM > 23U)
   ,(BswU1)BSW_COM_CH23_RXTOUTMSKSTOP
#endif
#if (BSW_COM_NETWORK_NUM > 24U)
   ,(BswU1)BSW_COM_CH24_RXTOUTMSKSTOP
#endif
#if (BSW_COM_NETWORK_NUM > 25U)
   ,(BswU1)BSW_COM_CH25_RXTOUTMSKSTOP
#endif
#if (BSW_COM_NETWORK_NUM > 26U)
   ,(BswU1)BSW_COM_CH26_RXTOUTMSKSTOP
#endif
#if (BSW_COM_NETWORK_NUM > 27U)
   ,(BswU1)BSW_COM_CH27_RXTOUTMSKSTOP
#endif
#if (BSW_COM_NETWORK_NUM > 28U)
   ,(BswU1)BSW_COM_CH28_RXTOUTMSKSTOP
#endif
#if (BSW_COM_NETWORK_NUM > 29U)
   ,(BswU1)BSW_COM_CH29_RXTOUTMSKSTOP
#endif
#if (BSW_COM_NETWORK_NUM > 30U)
   ,(BswU1)BSW_COM_CH30_RXTOUTMSKSTOP
#endif
#if (BSW_COM_NETWORK_NUM > 31U)
   ,(BswU1)BSW_COM_CH31_RXTOUTMSKSTOP
#endif
};

#if (BSW_COM_RX_MSG_NUM == 0U)
BswConst Bsw_Com_TickTimeType bsw_com_u2PwonMsk[BSW_COM_DUMMY_SIZE] = { (Bsw_Com_TickTimeType)0U };
BswConst Bsw_Com_TickTimeType bsw_com_u2WakeupMsk[BSW_COM_DUMMY_SIZE] = { (Bsw_Com_TickTimeType)0U };
#if ( BSW_COM_FUNC_PNCIPDU == BSW_USE )
BswConst Bsw_Com_TickTimeType bsw_com_u2PnconMsk[BSW_COM_DUMMY_SIZE] = { (Bsw_Com_TickTimeType)0U };
#endif /* ( BSW_COM_FUNC_PNCIPDU != BSW_USE ) */
#endif /* (BSW_COM_RX_MSG_NUM == 0U) */

void  (* BswConst bsw_com_rom_ptInitPncRxStatFunc)( void ) = BSW_COM_INITPNCRXSTAT_FUNC;
void  (* BswConst bsw_com_rom_ptDeInitPncRxStFunc)( void ) = BSW_COM_SHUTDOWNPNCRXSTAT_FUNC;
void  (* BswConst bsw_com_rom_ptGetPncChRxDMStFunc)( NetworkHandleType Network, BswU1 u1PncNum, BswU4* ptPrevStat, BswU4* ptReqStat, BswU1* ptStatChg ) = BSW_COM_GETPNCCHRXDMST_FUNC;
void  (* BswConst bsw_com_rom_ptSetPncIpduRxDMStFunc)( NetworkHandleType Network, BswConstR BswU4* ptReqStat ) = BSW_COM_SETPNCIPDURXDMST_FUNC;
BswU1 (* BswConst bsw_com_rom_ptGetPncIpduRxDMStFunc)( NetworkHandleType Network, PduIdType u2PduId ) = BSW_COM_GETPNCIPDURXDMST_FUNC;
void  (* BswConst bsw_com_rom_ptGetPncChRxStFunc)( NetworkHandleType Network, BswU4* ptPrevStat, BswU4* ptReqStat, BswU1* ptStatChg, BswU1* ptPncNum ) = BSW_COM_GETPNCCHRXST_FUNC;
BswU1 (* BswConst bsw_com_rom_ptChkPncIpduRxDMStFunc)( PduIdType u2PduId, BswU1 u1PncNum, BswConstR BswU4* ptPrevStat, BswConstR BswU4* ptReqStat ) = BSW_COM_CHKPNCIPDURXDMST_FUNC;
BswU1 (* BswConst bsw_com_rom_ptChkPncIpduRxStFunc)( PduIdType u2PduId, BswU1 u1PncNum, BswConstR BswU4* ptPrevStat, BswConstR BswU4* ptReqStat ) = BSW_COM_CHKPNCIPDURXST_FUNC;
void  (* BswConst bsw_com_rom_ptSetPncChRxStFunc)( NetworkHandleType Network, BswConstR BswU4* ptReqStat ) = BSW_COM_SETPNCCHRXST_FUNC;
BswU1 (* BswConst bsw_com_rom_ptGetPncIpduRxStFunc)( NetworkHandleType Network, PduIdType u2PduId ) = BSW_COM_GETPNCIPDURXST_FUNC;
BswU2 (* BswConst bsw_com_rom_ptGetPncMskTimFunc)( BswU2 u2RxMsgIdx ) = BSW_COM_GETPNCONMSKTIME_FUNC;
BswU1 (* BswConst bsw_com_rom_ptJdgPncRxStProcFunc)( BswU1 u1PncNum, BswU1 u1IpduChgSts, BswU1 u1PncIpduChgSts ) = BSW_COM_JUDGEPNCRXSTPROC_FUNC;

/*------------------------------------*/
/* Data management unit (DATA)        */
/*------------------------------------*/
/* ROM table for constant reference */
BswConst       BswU2  bsw_com_rom_u2FAILSIZE             = (BswU2)BSW_COM_FAILSAFE_SIZE;
BswConst       BswU2  bsw_com_rom_u2MSGBUFSIZE           = (BswU2)BSW_COM_MSGBUF_SIZE;
BswConst       BswU2  bsw_com_rom_u2SENDNTIMESMSGNUM     = (BswU2)BSW_COM_SENDNTIMES_MSG_NUM;
BswConst       BswU2  bsw_com_rom_u2CHGPERIODMSGNUM      = (BswU2)BSW_COM_CHGPERIOD_MSG_NUM;
BswConst       BswU1  bsw_com_rom_u1CPUBYTEORDERTYPE     = (BswU1)BSW_COM_CPU_BYTE_ORDER_TYPE;

#if (BSW_COM_CFG_BACKUPPDU_USE == BSW_USE)
BswConst       BswU2  bsw_com_rom_u2BACKUPPDUNUM         = (BswU2)BSW_COM_CFG_BACKUPPDU_NUM;
#endif /* (BSW_COM_CFG_BACKUPPDU_USE == BSW_USE) */

void (* BswConst bsw_com_rom_ptAlvCntFuncPosTx[BSW_COM_NETWORK_NUM])( PduIdType u2PduId, Bsw_Com_AlvCntPosType *ptAlvCntPos ) =
{
    BSW_COM_ALIVECOUNTER_FUNC_POS(00)
#if (BSW_COM_NETWORK_NUM > 1U)
   ,BSW_COM_ALIVECOUNTER_FUNC_POS(01)
#endif
#if (BSW_COM_NETWORK_NUM > 2U)
   ,BSW_COM_ALIVECOUNTER_FUNC_POS(02)
#endif
#if (BSW_COM_NETWORK_NUM > 3U)
   ,BSW_COM_ALIVECOUNTER_FUNC_POS(03)
#endif
#if (BSW_COM_NETWORK_NUM > 4U)
   ,BSW_COM_ALIVECOUNTER_FUNC_POS(04)
#endif
#if (BSW_COM_NETWORK_NUM > 5U)
   ,BSW_COM_ALIVECOUNTER_FUNC_POS(05)
#endif
#if (BSW_COM_NETWORK_NUM > 6U)
   ,BSW_COM_ALIVECOUNTER_FUNC_POS(06)
#endif
#if (BSW_COM_NETWORK_NUM > 7U)
   ,BSW_COM_ALIVECOUNTER_FUNC_POS(07)
#endif
#if (BSW_COM_NETWORK_NUM > 8U)
   ,BSW_COM_ALIVECOUNTER_FUNC_POS(08)
#endif
#if (BSW_COM_NETWORK_NUM > 9U)
   ,BSW_COM_ALIVECOUNTER_FUNC_POS(09)
#endif
#if (BSW_COM_NETWORK_NUM > 10U)
   ,BSW_COM_ALIVECOUNTER_FUNC_POS(10)
#endif
#if (BSW_COM_NETWORK_NUM > 11U)
   ,BSW_COM_ALIVECOUNTER_FUNC_POS(11)
#endif
#if (BSW_COM_NETWORK_NUM > 12U)
   ,BSW_COM_ALIVECOUNTER_FUNC_POS(12)
#endif
#if (BSW_COM_NETWORK_NUM > 13U)
   ,BSW_COM_ALIVECOUNTER_FUNC_POS(13)
#endif
#if (BSW_COM_NETWORK_NUM > 14U)
   ,BSW_COM_ALIVECOUNTER_FUNC_POS(14)
#endif
#if (BSW_COM_NETWORK_NUM > 15U)
   ,BSW_COM_ALIVECOUNTER_FUNC_POS(15)
#endif
#if (BSW_COM_NETWORK_NUM > 16U)
   ,BSW_COM_ALIVECOUNTER_FUNC_POS(16)
#endif
#if (BSW_COM_NETWORK_NUM > 17U)
   ,BSW_COM_ALIVECOUNTER_FUNC_POS(17)
#endif
#if (BSW_COM_NETWORK_NUM > 18U)
   ,BSW_COM_ALIVECOUNTER_FUNC_POS(18)
#endif
#if (BSW_COM_NETWORK_NUM > 19U)
   ,BSW_COM_ALIVECOUNTER_FUNC_POS(19)
#endif
#if (BSW_COM_NETWORK_NUM > 20U)
   ,BSW_COM_ALIVECOUNTER_FUNC_POS(20)
#endif
#if (BSW_COM_NETWORK_NUM > 21U)
   ,BSW_COM_ALIVECOUNTER_FUNC_POS(21)
#endif
#if (BSW_COM_NETWORK_NUM > 22U)
   ,BSW_COM_ALIVECOUNTER_FUNC_POS(22)
#endif
#if (BSW_COM_NETWORK_NUM > 23U)
   ,BSW_COM_ALIVECOUNTER_FUNC_POS(23)
#endif
#if (BSW_COM_NETWORK_NUM > 24U)
   ,BSW_COM_ALIVECOUNTER_FUNC_POS(24)
#endif
#if (BSW_COM_NETWORK_NUM > 25U)
   ,BSW_COM_ALIVECOUNTER_FUNC_POS(25)
#endif
#if (BSW_COM_NETWORK_NUM > 26U)
   ,BSW_COM_ALIVECOUNTER_FUNC_POS(26)
#endif
#if (BSW_COM_NETWORK_NUM > 27U)
   ,BSW_COM_ALIVECOUNTER_FUNC_POS(27)
#endif
#if (BSW_COM_NETWORK_NUM > 28U)
   ,BSW_COM_ALIVECOUNTER_FUNC_POS(28)
#endif
#if (BSW_COM_NETWORK_NUM > 29U)
   ,BSW_COM_ALIVECOUNTER_FUNC_POS(29)
#endif
#if (BSW_COM_NETWORK_NUM > 30U)
   ,BSW_COM_ALIVECOUNTER_FUNC_POS(30)
#endif
#if (BSW_COM_NETWORK_NUM > 31U)
   ,BSW_COM_ALIVECOUNTER_FUNC_POS(31)
#endif
};

/* Dummy definition when there is no fail information */
#if (BSW_COM_FAILSAFE_SIZE == 0U)
BswConst         BswU1 bsw_com_data_u1MsgBufFail[BSW_COM_DUMMY_SIZE] = {0U};
BswConst         BswU1 bsw_com_data_u1FailMskTbl[BSW_COM_DUMMY_SIZE] = {0U};
#endif  /* BSW_COM_FAILSAFE_SIZE == 0 */

BswU1 (* BswConst bsw_com_rom_ptChkChPncUseFunc)( NetworkHandleType Network ) = BSW_COM_CHKCHPNCUSE_FUNC;

/*------------------------------------*/
/* Fail safe unit (FS)                */
/*------------------------------------*/
/* Dummy definition when the counter value storage position table is not used */
#if (BSW_COM_ALIVECOUNTER_PTN2_USE == BSW_USE)
#if (BSW_COM_TX_ALVCNTMSG_NUM == 0U)
BswConst Bsw_Com_AliveInfoType bsw_com_AlvCnt2TxInfo[BSW_COM_DUMMY_SIZE] = {{ (uint16)0U, (uint8)0U, (uint8)0U}};
#endif /* BSW_COM_TX_ALVCNTMSG_NUM == 0U */
#if (BSW_COM_RX_ALVCNTMSG_NUM == 0U)
BswConst Bsw_Com_AliveInfoType bsw_com_AlvCnt2RxInfo[BSW_COM_DUMMY_SIZE] = {{ (uint16)0U, (uint8)0U, (uint8)0U}};
#endif /* BSW_COM_RX_ALVCNTMSG_NUM == 0U */
#endif /* BSW_COM_CFG_CHx_ALVCNTR_PTN != BSW_COM_ALIVECOUNTER_PTN2 */

/* Dummy definition when Alive Counter Pattern 3 Information Table is not used */
#if (BSW_COM_ALIVECOUNTER_PTN3_USE == BSW_USE)
#if (BSW_COM_TX_ALVCNT3MSG_NUM == 0U)
BswConst Bsw_Com_AlvCnt3TxInfoType bsw_com_AlvCnt3TxInfo[BSW_COM_DUMMY_SIZE] = {{ (uint16)0U, (uint8)0U, (uint8)0U, (uint8)BSW_COM_ENDIAN_BIG, (uint8)0U}};
#endif /* BSW_COM_TX_ALVCNT3MSG_NUM == 0U */
#if (BSW_COM_RX_ALVCNT3MSG_NUM == 0U)
BswConst Bsw_Com_AlvCnt3RxInfoType bsw_com_AlvCnt3RxInfo[BSW_COM_DUMMY_SIZE] = {{ (uint16)0U, (uint8)0U, (uint8)0U, (uint8)BSW_COM_ENDIAN_BIG, (uint8)1U, (uint8)BSW_NOUSE, (uint8)0U}};
#endif /* BSW_COM_RX_ALVCNT3MSG_NUM == 0U */
#endif /* BSW_COM_CFG_CHx_ALVCNTR_PTN != BSW_COM_ALIVECOUNTER_PTN3 */


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
/*  v1-0-0          :2017/06/30                                             */
/*  v1-0-1          :2018/04/04                                             */
/*  v1-1-0          :2018/12/12                                             */
/*  v1-2-0          :2019/10/01                                             */
/*  v2-0-0          :2022/02/21                                             */
/*  v2-1-0          :2022/11/18                                             */
/*  v2-2-0          :2023/07/06                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
