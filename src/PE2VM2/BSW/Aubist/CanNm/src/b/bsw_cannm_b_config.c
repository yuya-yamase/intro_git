/* bsw_cannm_b_config_c_v2-0-0                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANNM/B/CONFIG/CODE                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>
#include "../../inc/bsw_cannm_MemMap.h"
#include <ComStack_Types.h>

#include <bswm_cs/bsw_bswm_cs.h>
#include <comm/bsw_comm.h>
#include "../../../ComM/inc/bsw_comm_config.h"
#include "../../../BswM_CS/inc/bsw_bswm_cs_config.h"
#if( BSW_BSWM_CS_FUNC_CANNM == BSW_USE )

#include <cannm/bsw_cannm.h>
#include "../../inc/bsw_cannm_config.h"
#if ((BSW_CANNM_NM_TYPE_USE_B == BSW_USE) || (BSW_CANNM_COMIF_USE == BSW_USE))

#include <canif/bsw_canif.h>
#include <nm/bsw_nm.h>
#include <nm/bsw_nm_cbk.h>
#include "../../inc/b/bsw_cannm_b_ctrl.h"

#include "../../../Nm/inc/bsw_nm_config.h"
#include "../../inc/b/bsw_cannm_b_config.h"
#include "../../cfg/b/CanNm_B_Cfg.h"

#if( BSW_BSWM_CS_FUNC_COM == BSW_USE )
#include "../../../Com/inc/bsw_com_config.h"
#endif

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#if ( BSW_CANNM_NM_TYPE_USE_B == BSW_USE )
#define BSW_CANNM_B_USE(ch)          ((BSW_CANNM_NM_TYPE(ch) == BSW_CANNM_NMTYPE_B) ? BSW_USE : BSW_NOUSE)

/* Transmission start wait time at power-on */
#define BSW_CANNM_B_TPWON_CH0        (BSW_BSWM_CS_SEND_START_PW(CAN, 0U))
#define BSW_CANNM_B_TPWON_CH1        (BSW_BSWM_CS_SEND_START_PW(CAN, 1U))
#define BSW_CANNM_B_TPWON_CH2        (BSW_BSWM_CS_SEND_START_PW(CAN, 2U))
#define BSW_CANNM_B_TPWON_CH3        (BSW_BSWM_CS_SEND_START_PW(CAN, 3U))
#define BSW_CANNM_B_TPWON_CH4        (BSW_BSWM_CS_SEND_START_PW(CAN, 4U))
#define BSW_CANNM_B_TPWON_CH5        (BSW_BSWM_CS_SEND_START_PW(CAN, 5U))
#define BSW_CANNM_B_TPWON_CH6        (BSW_BSWM_CS_SEND_START_PW(CAN, 6U))
#define BSW_CANNM_B_TPWON_CH7        (BSW_BSWM_CS_SEND_START_PW(CAN, 7U))
#define BSW_CANNM_B_TPWON_CH8        (BSW_BSWM_CS_SEND_START_PW(CAN, 8U))
#define BSW_CANNM_B_TPWON_CH9        (BSW_BSWM_CS_SEND_START_PW(CAN, 9U))
#define BSW_CANNM_B_TPWON_CH10       (BSW_BSWM_CS_SEND_START_PW(CAN, 10U))
#define BSW_CANNM_B_TPWON_CH11       (BSW_BSWM_CS_SEND_START_PW(CAN, 11U))
#define BSW_CANNM_B_TPWON_CH12       (BSW_BSWM_CS_SEND_START_PW(CAN, 12U))
#define BSW_CANNM_B_TPWON_CH13       (BSW_BSWM_CS_SEND_START_PW(CAN, 13U))
#define BSW_CANNM_B_TPWON_CH14       (BSW_BSWM_CS_SEND_START_PW(CAN, 14U))
#define BSW_CANNM_B_TPWON_CH15       (BSW_BSWM_CS_SEND_START_PW(CAN, 15U))
#define BSW_CANNM_B_TPWON_CH16       (BSW_BSWM_CS_SEND_START_PW(CAN, 16U))
#define BSW_CANNM_B_TPWON_CH17       (BSW_BSWM_CS_SEND_START_PW(CAN, 17U))
#define BSW_CANNM_B_TPWON_CH18       (BSW_BSWM_CS_SEND_START_PW(CAN, 18U))
#define BSW_CANNM_B_TPWON_CH19       (BSW_BSWM_CS_SEND_START_PW(CAN, 19U))
#define BSW_CANNM_B_TPWON_CH20       (BSW_BSWM_CS_SEND_START_PW(CAN, 20U))
#define BSW_CANNM_B_TPWON_CH21       (BSW_BSWM_CS_SEND_START_PW(CAN, 21U))
#define BSW_CANNM_B_TPWON_CH22       (BSW_BSWM_CS_SEND_START_PW(CAN, 22U))
#define BSW_CANNM_B_TPWON_CH23       (BSW_BSWM_CS_SEND_START_PW(CAN, 23U))
#define BSW_CANNM_B_TPWON_CH24       (BSW_BSWM_CS_SEND_START_PW(CAN, 24U))
#define BSW_CANNM_B_TPWON_CH25       (BSW_BSWM_CS_SEND_START_PW(CAN, 25U))
#define BSW_CANNM_B_TPWON_CH26       (BSW_BSWM_CS_SEND_START_PW(CAN, 26U))
#define BSW_CANNM_B_TPWON_CH27       (BSW_BSWM_CS_SEND_START_PW(CAN, 27U))
#define BSW_CANNM_B_TPWON_CH28       (BSW_BSWM_CS_SEND_START_PW(CAN, 28U))
#define BSW_CANNM_B_TPWON_CH29       (BSW_BSWM_CS_SEND_START_PW(CAN, 29U))
#define BSW_CANNM_B_TPWON_CH30       (BSW_BSWM_CS_SEND_START_PW(CAN, 30U))
#define BSW_CANNM_B_TPWON_CH31       (BSW_BSWM_CS_SEND_START_PW(CAN, 31U))

#define BSW_CANNM_B_CH_TPWON(ch)     (BSW_CANNM_B_TPWON_CH##ch)

/* Maximum transmission start wait time at power-on */
#if ( BSW_CANNM_B_TPWON_CH0 > BSW_CANNM_B_TPWON_CH1 )
#define BSW_CANNM_B_MAX_TPWON_0_1     BSW_CANNM_B_TPWON_CH0
#else
#define BSW_CANNM_B_MAX_TPWON_0_1     BSW_CANNM_B_TPWON_CH1
#endif

#if ( BSW_CANNM_B_TPWON_CH2 > BSW_CANNM_B_TPWON_CH3 )
#define BSW_CANNM_B_MAX_TPWON_2_3     BSW_CANNM_B_TPWON_CH2
#else
#define BSW_CANNM_B_MAX_TPWON_2_3     BSW_CANNM_B_TPWON_CH3
#endif

#if ( BSW_CANNM_B_TPWON_CH4 > BSW_CANNM_B_TPWON_CH5 )
#define BSW_CANNM_B_MAX_TPWON_4_5     BSW_CANNM_B_TPWON_CH4
#else
#define BSW_CANNM_B_MAX_TPWON_4_5     BSW_CANNM_B_TPWON_CH5
#endif

#if ( BSW_CANNM_B_TPWON_CH6 > BSW_CANNM_B_TPWON_CH7 )
#define BSW_CANNM_B_MAX_TPWON_6_7     BSW_CANNM_B_TPWON_CH6
#else
#define BSW_CANNM_B_MAX_TPWON_6_7     BSW_CANNM_B_TPWON_CH7
#endif

#if ( BSW_CANNM_B_TPWON_CH8 > BSW_CANNM_B_TPWON_CH9 )
#define BSW_CANNM_B_MAX_TPWON_8_9     BSW_CANNM_B_TPWON_CH8
#else
#define BSW_CANNM_B_MAX_TPWON_8_9     BSW_CANNM_B_TPWON_CH9
#endif

#if ( BSW_CANNM_B_TPWON_CH10 > BSW_CANNM_B_TPWON_CH11 )
#define BSW_CANNM_B_MAX_TPWON_10_11   BSW_CANNM_B_TPWON_CH10
#else
#define BSW_CANNM_B_MAX_TPWON_10_11   BSW_CANNM_B_TPWON_CH11
#endif

#if ( BSW_CANNM_B_TPWON_CH12 > BSW_CANNM_B_TPWON_CH13 )
#define BSW_CANNM_B_MAX_TPWON_12_13   BSW_CANNM_B_TPWON_CH12
#else
#define BSW_CANNM_B_MAX_TPWON_12_13   BSW_CANNM_B_TPWON_CH13
#endif

#if ( BSW_CANNM_B_TPWON_CH14 > BSW_CANNM_B_TPWON_CH15 )
#define BSW_CANNM_B_MAX_TPWON_14_15   BSW_CANNM_B_TPWON_CH14
#else
#define BSW_CANNM_B_MAX_TPWON_14_15   BSW_CANNM_B_TPWON_CH15
#endif

#if ( BSW_CANNM_B_TPWON_CH16 > BSW_CANNM_B_TPWON_CH17 )
#define BSW_CANNM_B_MAX_TPWON_16_17   BSW_CANNM_B_TPWON_CH16
#else
#define BSW_CANNM_B_MAX_TPWON_16_17   BSW_CANNM_B_TPWON_CH17
#endif

#if ( BSW_CANNM_B_TPWON_CH18 > BSW_CANNM_B_TPWON_CH19 )
#define BSW_CANNM_B_MAX_TPWON_18_19   BSW_CANNM_B_TPWON_CH18
#else
#define BSW_CANNM_B_MAX_TPWON_18_19   BSW_CANNM_B_TPWON_CH19
#endif

#if ( BSW_CANNM_B_TPWON_CH20 > BSW_CANNM_B_TPWON_CH21 )
#define BSW_CANNM_B_MAX_TPWON_20_21   BSW_CANNM_B_TPWON_CH20
#else
#define BSW_CANNM_B_MAX_TPWON_20_21   BSW_CANNM_B_TPWON_CH21
#endif

#if ( BSW_CANNM_B_TPWON_CH22 > BSW_CANNM_B_TPWON_CH23 )
#define BSW_CANNM_B_MAX_TPWON_22_23   BSW_CANNM_B_TPWON_CH22
#else
#define BSW_CANNM_B_MAX_TPWON_22_23   BSW_CANNM_B_TPWON_CH23
#endif

#if ( BSW_CANNM_B_TPWON_CH24 > BSW_CANNM_B_TPWON_CH25 )
#define BSW_CANNM_B_MAX_TPWON_24_25   BSW_CANNM_B_TPWON_CH24
#else
#define BSW_CANNM_B_MAX_TPWON_24_25   BSW_CANNM_B_TPWON_CH25
#endif

#if ( BSW_CANNM_B_TPWON_CH26 > BSW_CANNM_B_TPWON_CH27 )
#define BSW_CANNM_B_MAX_TPWON_26_27   BSW_CANNM_B_TPWON_CH26
#else
#define BSW_CANNM_B_MAX_TPWON_26_27   BSW_CANNM_B_TPWON_CH27
#endif

#if ( BSW_CANNM_B_TPWON_CH28 > BSW_CANNM_B_TPWON_CH29 )
#define BSW_CANNM_B_MAX_TPWON_28_29   BSW_CANNM_B_TPWON_CH28
#else
#define BSW_CANNM_B_MAX_TPWON_28_29   BSW_CANNM_B_TPWON_CH29
#endif

#if ( BSW_CANNM_B_TPWON_CH30 > BSW_CANNM_B_TPWON_CH31 )
#define BSW_CANNM_B_MAX_TPWON_30_31   BSW_CANNM_B_TPWON_CH30
#else
#define BSW_CANNM_B_MAX_TPWON_30_31   BSW_CANNM_B_TPWON_CH31
#endif

#if ( BSW_CANNM_B_MAX_TPWON_0_1 > BSW_CANNM_B_MAX_TPWON_2_3 )
#define BSW_CANNM_B_MAX_TPWON_0_3     BSW_CANNM_B_MAX_TPWON_0_1
#else
#define BSW_CANNM_B_MAX_TPWON_0_3     BSW_CANNM_B_MAX_TPWON_2_3
#endif

#if ( BSW_CANNM_B_MAX_TPWON_4_5 > BSW_CANNM_B_MAX_TPWON_6_7 )
#define BSW_CANNM_B_MAX_TPWON_4_7     BSW_CANNM_B_MAX_TPWON_4_5
#else
#define BSW_CANNM_B_MAX_TPWON_4_7     BSW_CANNM_B_MAX_TPWON_6_7
#endif

#if ( BSW_CANNM_B_MAX_TPWON_8_9 > BSW_CANNM_B_MAX_TPWON_10_11 )
#define BSW_CANNM_B_MAX_TPWON_8_11    BSW_CANNM_B_MAX_TPWON_8_9
#else
#define BSW_CANNM_B_MAX_TPWON_8_11    BSW_CANNM_B_MAX_TPWON_10_11
#endif

#if ( BSW_CANNM_B_MAX_TPWON_12_13 > BSW_CANNM_B_MAX_TPWON_14_15 )
#define BSW_CANNM_B_MAX_TPWON_12_15   BSW_CANNM_B_MAX_TPWON_12_13
#else
#define BSW_CANNM_B_MAX_TPWON_12_15   BSW_CANNM_B_MAX_TPWON_14_15
#endif

#if ( BSW_CANNM_B_MAX_TPWON_16_17 > BSW_CANNM_B_MAX_TPWON_18_19 )
#define BSW_CANNM_B_MAX_TPWON_16_19   BSW_CANNM_B_MAX_TPWON_16_17
#else
#define BSW_CANNM_B_MAX_TPWON_16_19   BSW_CANNM_B_MAX_TPWON_18_19
#endif

#if ( BSW_CANNM_B_MAX_TPWON_20_21 > BSW_CANNM_B_MAX_TPWON_22_23 )
#define BSW_CANNM_B_MAX_TPWON_20_23   BSW_CANNM_B_MAX_TPWON_20_21
#else
#define BSW_CANNM_B_MAX_TPWON_20_23   BSW_CANNM_B_MAX_TPWON_22_23
#endif

#if ( BSW_CANNM_B_MAX_TPWON_24_25 > BSW_CANNM_B_MAX_TPWON_26_27 )
#define BSW_CANNM_B_MAX_TPWON_24_27   BSW_CANNM_B_MAX_TPWON_24_25
#else
#define BSW_CANNM_B_MAX_TPWON_24_27   BSW_CANNM_B_MAX_TPWON_26_27
#endif

#if ( BSW_CANNM_B_MAX_TPWON_28_29 > BSW_CANNM_B_MAX_TPWON_30_31 )
#define BSW_CANNM_B_MAX_TPWON_28_31   BSW_CANNM_B_MAX_TPWON_28_29
#else
#define BSW_CANNM_B_MAX_TPWON_28_31   BSW_CANNM_B_MAX_TPWON_30_31
#endif

#if ( BSW_CANNM_B_MAX_TPWON_0_3 > BSW_CANNM_B_MAX_TPWON_4_7 )
#define BSW_CANNM_B_MAX_TPWON_0_7     BSW_CANNM_B_MAX_TPWON_0_3
#else
#define BSW_CANNM_B_MAX_TPWON_0_7     BSW_CANNM_B_MAX_TPWON_4_7
#endif

#if ( BSW_CANNM_B_MAX_TPWON_8_11 > BSW_CANNM_B_MAX_TPWON_12_15 )
#define BSW_CANNM_B_MAX_TPWON_8_15    BSW_CANNM_B_MAX_TPWON_8_11
#else
#define BSW_CANNM_B_MAX_TPWON_8_15    BSW_CANNM_B_MAX_TPWON_12_15
#endif

#if ( BSW_CANNM_B_MAX_TPWON_16_19 > BSW_CANNM_B_MAX_TPWON_20_23 )
#define BSW_CANNM_B_MAX_TPWON_16_23   BSW_CANNM_B_MAX_TPWON_16_19
#else
#define BSW_CANNM_B_MAX_TPWON_16_23   BSW_CANNM_B_MAX_TPWON_20_23
#endif

#if ( BSW_CANNM_B_MAX_TPWON_24_27 > BSW_CANNM_B_MAX_TPWON_28_31 )
#define BSW_CANNM_B_MAX_TPWON_24_31   BSW_CANNM_B_MAX_TPWON_24_27
#else
#define BSW_CANNM_B_MAX_TPWON_24_31   BSW_CANNM_B_MAX_TPWON_28_31
#endif

#if ( BSW_CANNM_B_MAX_TPWON_0_7 > BSW_CANNM_B_MAX_TPWON_8_15 )
#define BSW_CANNM_B_MAX_TPWON_0_15    BSW_CANNM_B_MAX_TPWON_0_7
#else
#define BSW_CANNM_B_MAX_TPWON_0_15    BSW_CANNM_B_MAX_TPWON_8_15
#endif

#if ( BSW_CANNM_B_MAX_TPWON_16_23 > BSW_CANNM_B_MAX_TPWON_24_31 )
#define BSW_CANNM_B_MAX_TPWON_16_31   BSW_CANNM_B_MAX_TPWON_16_23
#else
#define BSW_CANNM_B_MAX_TPWON_16_31   BSW_CANNM_B_MAX_TPWON_24_31
#endif

#if ( BSW_CANNM_B_MAX_TPWON_0_15 > BSW_CANNM_B_MAX_TPWON_16_31 )
#define BSW_CANNM_B_MAX_TPWON         BSW_CANNM_B_MAX_TPWON_0_15
#else
#define BSW_CANNM_B_MAX_TPWON         BSW_CANNM_B_MAX_TPWON_16_31
#endif


#if (BSW_CANNM_B_MAX_TPWON > BSW_CANNM_B_CFG_TWUW)
#define BSW_CANNM_B_SNDSTRT_FAIL      (BSW_CANNM_B_MAX_TPWON)
#else
#define BSW_CANNM_B_SNDSTRT_FAIL      (BSW_CANNM_B_CFG_TWUW)
#endif /* (BSW_CANNM_B_MAX_TPWON > BSW_CANNM_B_CFG_TWUW) */

#if( BSW_BSWM_CS_FUNC_COM == BSW_USE )
#define BSW_CANNM_B_EVTWAKEUPFRAME_USE        (BSW_COM_EVENTWAKEUPFRAME_USE)
#else
#define BSW_CANNM_B_EVTWAKEUPFRAME_USE        (BSW_NOUSE)
#endif

#define BSW_CANNM_B_u2EVDISABLE_TIME          ((BswU2)15U)       /* Event transmission disable time */

#define BSW_CANNM_B_COM_CONTROL               (BSW_NM_COM_CONTROL)

#if ( BSW_CANNM_COMIF_USE == BSW_USE )
#define BSW_CANNM_B_TRWKUPFRM_FUNC    (&bsw_cannm_b_ctrl_TransWkupCtrl)
#else
#define BSW_CANNM_B_TRWKUPFRM_FUNC    (&bsw_cannm_b_ctrl_TransWkupNn)
#endif /* ( BSW_CANNM_COMIF_USE == BSW_USE ) */

#if (BSW_CANNM_B_EVTWAKEUPFRAME_USE == BSW_USE)
#define BSW_CANNM_B_EVTWKUP_INIT_FUNC           (&bsw_cannm_b_ctrl_InitEvtWkup)
#define BSW_CANNM_B_EVTWKUP_CLR_FUNC            (&bsw_cannm_b_ctrl_ClrEvtWkupReq)
#define BSW_CANNM_B_EVTWKUP_TX_FUNC             (&bsw_cannm_b_ctrl_TxEvtWkupFr)
#define BSW_CANNM_B_EVTTXCONF_FUNC              (&Nm_EvtWakeupTxConfirmation)
#else
#define BSW_CANNM_B_EVTWKUP_INIT_FUNC           (&bsw_cannm_b_ctrl_InitEvtWkupNn)
#define BSW_CANNM_B_EVTWKUP_CLR_FUNC            (&bsw_cannm_b_ctrl_ClrEvWkupRqNn)
#define BSW_CANNM_B_EVTWKUP_TX_FUNC             (&bsw_cannm_b_ctrl_TxEvtWkupFrNn)
#define BSW_CANNM_B_EVTTXCONF_FUNC              (&bsw_cannm_b_ctrl_EvWkCnfNotInd)
#endif /* (BSW_CANNM_B_EVTWAKEUPFRAME_USE == BSW_USE) */

#if (BSW_CANNM_B_COM_CONTROL == BSW_USE)
#define BSW_CANNM_B_COMCTRL_INIT_FUNC           (&bsw_cannm_b_ctrl_InitComCtrl)
#define BSW_CANNM_B_COM_GETCOMSTS_FUNC          (&bsw_cannm_b_ctrl_GetComCtrlSts)
#else
#define BSW_CANNM_B_COMCTRL_INIT_FUNC           (&bsw_cannm_b_ctrl_InitComCtrlNn)
#define BSW_CANNM_B_COM_GETCOMSTS_FUNC          (&bsw_cannm_b_ctrl_GetCmCtrlStsNn)
#endif /* (BSW_CANNM_B_COM_CONTROL == BSW_USE) */

#endif /* ( BSW_CANNM_NM_TYPE_USE_B == BSW_USE ) */

#if ( BSW_CANNM_NM_TYPE_USE_B == BSW_USE )
#define BSW_CANNM_B_RXCOMREQ_FUNC     (&bsw_cannm_b_ctrl_RxComReq)
#define BSW_CANNM_B_SETCOMREQ_FUNC    (&bsw_cannm_b_ctrl_SetComReq)
#else
#define BSW_CANNM_B_RXCOMREQ_FUNC     (&bsw_cannm_b_ctrl_RxComReqNone)
#define BSW_CANNM_B_SETCOMREQ_FUNC    (&bsw_cannm_b_ctrl_SetComReqNone)
#endif /* ( BSW_CANNM_NM_TYPE_USE_B == BSW_USE ) */

#define BSW_CANNM_B_TASK_JITTER       (1U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/* Network management unit */

#if ( BSW_CANNM_NM_TYPE_USE_B == BSW_USE )

/* By Channel CanNm state */
Bsw_CanNmB_ChStsType         bsw_cannm_b_stChSts[BSW_CANNM_B_CAN_CH_NUM];

/* Event wake-up frame transmission request or not */
#if (BSW_CANNM_B_EVTWAKEUPFRAME_USE == BSW_USE)
BswU1                      bsw_cannm_b_ctrl_u1EvtWkupReq[BSW_CANNM_B_CAN_CH_NUM];
#endif

/* Exist/none of communication restriction request */
#if ( BSW_NM_COM_CONTROL == BSW_USE )
BswU1                      bsw_cannm_b_ctrl_u1ComCtrlReq[BSW_CANNM_B_CAN_CH_NUM];
#endif

#endif /* ( BSW_CANNM_NM_TYPE_USE_B == BSW_USE ) */

#if (( BSW_CANNM_COMIF_USE == BSW_USE ) || ( BSW_CANNM_NM_TYPE_USE_B == BSW_USE ))

/* By Channel Event information */
Bsw_CanNmB_ChEvtType         bsw_cannm_b_stChEvt[BSW_CANNM_B_CAN_CH_NUM];
/* For temporary storage of indexes of NM messages */
BswU2 bsw_cannm_b_u2RxNmMsgIndex[BSW_CANNM_B_CAN_CH_NUM];

#endif /* ( BSW_CANNM_COMIF_USE == BSW_USE ) || ( BSW_CANNM_NM_TYPE_USE_B == BSW_USE ) */


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#if ( BSW_CANNM_NM_TYPE_USE_B == BSW_USE )

/* Maximum number of channels */
BswConst BswU1 bsw_cannm_b_ctrl_u1MaxCh = (BswU1)BSW_CANNM_B_CAN_CH_NUM;

/* Channel offset */
BswConst BswU1  bsw_cannm_b_ctrl_u1ChOffset = (BswU1)BSW_COMM_BUS_TYPE_OFFSET(CAN);

/* Channel used/not used table */
BswConst BswU1 bsw_cannm_b_ctrl_u1Channel[BSW_CANNM_B_CAN_CH_NUM] =
{
    (BswU1)BSW_CANNM_B_USE(0)
#if (BSW_CANNM_B_CAN_CH_NUM > 1U)
   ,(BswU1)BSW_CANNM_B_USE(1)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 2U)
   ,(BswU1)BSW_CANNM_B_USE(2)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 3U)
   ,(BswU1)BSW_CANNM_B_USE(3)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 4U)
   ,(BswU1)BSW_CANNM_B_USE(4)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 5U)
   ,(BswU1)BSW_CANNM_B_USE(5)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 6U)
   ,(BswU1)BSW_CANNM_B_USE(6)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 7U)
   ,(BswU1)BSW_CANNM_B_USE(7)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 8U)
   ,(BswU1)BSW_CANNM_B_USE(8)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 9U)
   ,(BswU1)BSW_CANNM_B_USE(9)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 10U)
   ,(BswU1)BSW_CANNM_B_USE(10)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 11U)
   ,(BswU1)BSW_CANNM_B_USE(11)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 12U)
   ,(BswU1)BSW_CANNM_B_USE(12)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 13U)
   ,(BswU1)BSW_CANNM_B_USE(13)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 14U)
   ,(BswU1)BSW_CANNM_B_USE(14)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 15U)
   ,(BswU1)BSW_CANNM_B_USE(15)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 16U)
   ,(BswU1)BSW_CANNM_B_USE(16)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 17U)
   ,(BswU1)BSW_CANNM_B_USE(17)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 18U)
   ,(BswU1)BSW_CANNM_B_USE(18)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 19U)
   ,(BswU1)BSW_CANNM_B_USE(19)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 20U)
   ,(BswU1)BSW_CANNM_B_USE(20)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 21U)
   ,(BswU1)BSW_CANNM_B_USE(21)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 22U)
   ,(BswU1)BSW_CANNM_B_USE(22)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 23U)
   ,(BswU1)BSW_CANNM_B_USE(23)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 24U)
   ,(BswU1)BSW_CANNM_B_USE(24)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 25U)
   ,(BswU1)BSW_CANNM_B_USE(25)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 26U)
   ,(BswU1)BSW_CANNM_B_USE(26)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 27U)
   ,(BswU1)BSW_CANNM_B_USE(27)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 28U)
   ,(BswU1)BSW_CANNM_B_USE(28)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 29U)
   ,(BswU1)BSW_CANNM_B_USE(29)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 30U)
   ,(BswU1)BSW_CANNM_B_USE(30)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 31U)
   ,(BswU1)BSW_CANNM_B_USE(31)
#endif
};

/* Table to judge whether bus-sleep is used or not */
BswConst BswU1 bsw_cannm_b_ctrl_u1BusSleepTbl[BSW_CANNM_B_CAN_CH_NUM] =
{
    (BswU1)BSW_CANNM_BUSSLEEP_USE(0U)
#if (BSW_CANNM_B_CAN_CH_NUM > 1U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(1U)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 2U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(2U)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 3U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(3U)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 4U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(4U)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 5U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(5U)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 6U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(6U)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 7U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(7U)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 8U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(8U)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 9U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(9U)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 10U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(10U)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 11U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(11U)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 12U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(12U)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 13U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(13U)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 14U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(14U)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 15U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(15U)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 16U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(16U)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 17U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(17U)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 18U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(18U)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 19U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(19U)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 20U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(20U)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 21U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(21U)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 22U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(22U)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 23U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(23U)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 24U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(24U)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 25U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(25U)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 26U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(26U)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 27U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(27U)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 28U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(28U)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 29U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(29U)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 30U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(30U)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 31U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(31U)
#endif
};

/* Use/Unuse table for NM message notification */
BswConst BswU1 bsw_cannm_b_ctrl_u1ComIf[BSW_CANNM_B_CAN_CH_NUM] =
{
    (BswU1)BSW_CANNM_CFG_COMIF_CH0
#if (BSW_CANNM_B_CAN_CH_NUM > 1U)
   ,(BswU1)BSW_CANNM_CFG_COMIF_CH1
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 2U)
   ,(BswU1)BSW_CANNM_CFG_COMIF_CH2
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 3U)
   ,(BswU1)BSW_CANNM_CFG_COMIF_CH3
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 4U)
   ,(BswU1)BSW_CANNM_CFG_COMIF_CH4
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 5U)
   ,(BswU1)BSW_CANNM_CFG_COMIF_CH5
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 6U)
   ,(BswU1)BSW_CANNM_CFG_COMIF_CH6
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 7U)
   ,(BswU1)BSW_CANNM_CFG_COMIF_CH7
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 8U)
   ,(BswU1)BSW_CANNM_CFG_COMIF_CH8
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 9U)
   ,(BswU1)BSW_CANNM_CFG_COMIF_CH9
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 10U)
   ,(BswU1)BSW_CANNM_CFG_COMIF_CH10
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 11U)
   ,(BswU1)BSW_CANNM_CFG_COMIF_CH11
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 12U)
   ,(BswU1)BSW_CANNM_CFG_COMIF_CH12
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 13U)
   ,(BswU1)BSW_CANNM_CFG_COMIF_CH13
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 14U)
   ,(BswU1)BSW_CANNM_CFG_COMIF_CH14
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 15U)
   ,(BswU1)BSW_CANNM_CFG_COMIF_CH15
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 16U)
   ,(BswU1)BSW_CANNM_CFG_COMIF_CH16
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 17U)
   ,(BswU1)BSW_CANNM_CFG_COMIF_CH17
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 18U)
   ,(BswU1)BSW_CANNM_CFG_COMIF_CH18
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 19U)
   ,(BswU1)BSW_CANNM_CFG_COMIF_CH19
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 20U)
   ,(BswU1)BSW_CANNM_CFG_COMIF_CH20
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 21U)
   ,(BswU1)BSW_CANNM_CFG_COMIF_CH21
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 22U)
   ,(BswU1)BSW_CANNM_CFG_COMIF_CH22
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 23U)
   ,(BswU1)BSW_CANNM_CFG_COMIF_CH23
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 24U)
   ,(BswU1)BSW_CANNM_CFG_COMIF_CH24
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 25U)
   ,(BswU1)BSW_CANNM_CFG_COMIF_CH25
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 26U)
   ,(BswU1)BSW_CANNM_CFG_COMIF_CH26
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 27U)
   ,(BswU1)BSW_CANNM_CFG_COMIF_CH27
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 28U)
   ,(BswU1)BSW_CANNM_CFG_COMIF_CH28
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 29U)
   ,(BswU1)BSW_CANNM_CFG_COMIF_CH29
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 30U)
   ,(BswU1)BSW_CANNM_CFG_COMIF_CH30
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 31U)
   ,(BswU1)BSW_CANNM_CFG_COMIF_CH31
#endif
};

/* Transmission start wait time at power-on */
BswConst BswU2 bsw_cannm_b_ctrl_u2SndStrtDrv[BSW_CANNM_B_CAN_CH_NUM] =
{
      BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANNM_B_CH_TPWON(0))
#if (BSW_CANNM_B_CAN_CH_NUM > 1U)
    , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANNM_B_CH_TPWON(1))
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 2U)
    , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANNM_B_CH_TPWON(2))
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 3U)
    , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANNM_B_CH_TPWON(3))
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 4U)
    , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANNM_B_CH_TPWON(4))
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 5U)
    , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANNM_B_CH_TPWON(5))
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 6U)
    , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANNM_B_CH_TPWON(6))
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 7U)
    , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANNM_B_CH_TPWON(7))
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 8U)
    , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANNM_B_CH_TPWON(8))
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 9U)
    , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANNM_B_CH_TPWON(9))
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 10U)
    , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANNM_B_CH_TPWON(10))
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 11U)
    , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANNM_B_CH_TPWON(11))
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 12U)
    , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANNM_B_CH_TPWON(12))
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 13U)
    , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANNM_B_CH_TPWON(13))
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 14U)
    , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANNM_B_CH_TPWON(14))
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 15U)
    , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANNM_B_CH_TPWON(15))
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 16U)
    , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANNM_B_CH_TPWON(16))
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 17U)
    , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANNM_B_CH_TPWON(17))
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 18U)
    , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANNM_B_CH_TPWON(18))
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 19U)
    , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANNM_B_CH_TPWON(19))
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 20U)
    , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANNM_B_CH_TPWON(20))
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 21U)
    , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANNM_B_CH_TPWON(21))
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 22U)
    , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANNM_B_CH_TPWON(22))
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 23U)
    , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANNM_B_CH_TPWON(23))
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 24U)
    , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANNM_B_CH_TPWON(24))
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 25U)
    , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANNM_B_CH_TPWON(25))
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 26U)
    , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANNM_B_CH_TPWON(26))
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 27U)
    , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANNM_B_CH_TPWON(27))
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 28U)
    , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANNM_B_CH_TPWON(28))
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 29U)
    , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANNM_B_CH_TPWON(29))
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 30U)
    , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANNM_B_CH_TPWON(30))
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 31U)
    , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANNM_B_CH_TPWON(31))
#endif
};

/* Transmission starting wait time at bus wake-up */
#if ( BSW_CANNM_B_CFG_TWUW == 0U )
BswConst BswU2 bsw_cannm_b_ctrl_u2SndStrtWkup = (BswU2)0U;
#else
BswConst BswU2 bsw_cannm_b_ctrl_u2SndStrtWkup = (BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANNM_B_CFG_TWUW) + (BswU2)BSW_CANNM_B_TASK_JITTER);
#endif

/* Fail-safe time of transmission start waiting timer */
BswConst BswU2 bsw_cannm_b_ctrl_u2SndStrtFail = BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANNM_B_SNDSTRT_FAIL);

/* WKUP frame transmission completion wait time */
BswConst BswU2 bsw_cannm_b_ctrl_u2TxToutWuFrm = (BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANNM_B_CFG_SNDWKUP_WTTIME) + (BswU2)BSW_CANNM_B_TASK_JITTER);

/* Sleep transition waiting time */
BswConst BswU2 bsw_cannm_b_ctrl_u2SlpWaitTime = BSW_BSWM_CS_u2MILSEC2TICK_MID(5000U);

/* Event transmission disable time */
BswConst BswU2  bsw_cannm_b_ctrl_u2DisableTime = BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANNM_B_u2EVDISABLE_TIME);

/* Function for sending wake-up frames */
void (* BswConst bsw_cannm_b_ctrl_ptTrnsWkupFunc)( BswU1 u1NetID ) = BSW_CANNM_B_TRWKUPFRM_FUNC;

/* Event wake-up frame transmission function */
void    (* BswConst bsw_cannm_b_ctrl_InitEvWkupFunc)( void ) = BSW_CANNM_B_EVTWKUP_INIT_FUNC;
void    (* BswConst bsw_cannm_b_ctrl_ClrEvWkReqFunc)( BswU1 u1NetID ) = BSW_CANNM_B_EVTWKUP_CLR_FUNC;
void    (* BswConst bsw_cannm_b_ctrl_TxEvWkReqFunc)( BswU1 u1NetID, BswU1 u1BusAwake ) = BSW_CANNM_B_EVTWKUP_TX_FUNC;
void    (* BswConst bsw_cannm_b_ctrl_EvWkCnfIndFunc)( NetworkHandleType nmNetworkHandle, uint16 DisableTime ) = BSW_CANNM_B_EVTTXCONF_FUNC;

/* Switch the communication restriction function */
void    (* BswConst bsw_cannm_b_ctrl_InitComFunc)( void ) = BSW_CANNM_B_COMCTRL_INIT_FUNC;
BswU1   (* BswConst bsw_cannm_b_ctrl_GetCmCtStsFunc)(  BswU1 u1NetID  ) = BSW_CANNM_B_COM_GETCOMSTS_FUNC;

/* NM message transmission interval */
BswConst BswU2 bsw_cannm_b_ctrl_u2NmTxTime[BSW_CANNM_B_CAN_CH_NUM] =
{
      BSW_BSWM_CS_u2MILSEC2TICK_MID(BSW_CANNM_B_CFG_TX_MSG_TIME_CH0)
#if (BSW_CANNM_B_CAN_CH_NUM > 1U)
    , BSW_BSWM_CS_u2MILSEC2TICK_MID(BSW_CANNM_B_CFG_TX_MSG_TIME_CH1)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 2U)
    , BSW_BSWM_CS_u2MILSEC2TICK_MID(BSW_CANNM_B_CFG_TX_MSG_TIME_CH2)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 3U)
    , BSW_BSWM_CS_u2MILSEC2TICK_MID(BSW_CANNM_B_CFG_TX_MSG_TIME_CH3)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 4U)
    , BSW_BSWM_CS_u2MILSEC2TICK_MID(BSW_CANNM_B_CFG_TX_MSG_TIME_CH4)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 5U)
    , BSW_BSWM_CS_u2MILSEC2TICK_MID(BSW_CANNM_B_CFG_TX_MSG_TIME_CH5)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 6U)
    , BSW_BSWM_CS_u2MILSEC2TICK_MID(BSW_CANNM_B_CFG_TX_MSG_TIME_CH6)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 7U)
    , BSW_BSWM_CS_u2MILSEC2TICK_MID(BSW_CANNM_B_CFG_TX_MSG_TIME_CH7)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 8U)
    , BSW_BSWM_CS_u2MILSEC2TICK_MID(BSW_CANNM_B_CFG_TX_MSG_TIME_CH8)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 9U)
    , BSW_BSWM_CS_u2MILSEC2TICK_MID(BSW_CANNM_B_CFG_TX_MSG_TIME_CH9)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 10U)
    , BSW_BSWM_CS_u2MILSEC2TICK_MID(BSW_CANNM_B_CFG_TX_MSG_TIME_CH10)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 11U)
    , BSW_BSWM_CS_u2MILSEC2TICK_MID(BSW_CANNM_B_CFG_TX_MSG_TIME_CH11)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 12U)
    , BSW_BSWM_CS_u2MILSEC2TICK_MID(BSW_CANNM_B_CFG_TX_MSG_TIME_CH12)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 13U)
    , BSW_BSWM_CS_u2MILSEC2TICK_MID(BSW_CANNM_B_CFG_TX_MSG_TIME_CH13)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 14U)
    , BSW_BSWM_CS_u2MILSEC2TICK_MID(BSW_CANNM_B_CFG_TX_MSG_TIME_CH14)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 15U)
    , BSW_BSWM_CS_u2MILSEC2TICK_MID(BSW_CANNM_B_CFG_TX_MSG_TIME_CH15)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 16U)
    , BSW_BSWM_CS_u2MILSEC2TICK_MID(BSW_CANNM_B_CFG_TX_MSG_TIME_CH16)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 17U)
    , BSW_BSWM_CS_u2MILSEC2TICK_MID(BSW_CANNM_B_CFG_TX_MSG_TIME_CH17)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 18U)
    , BSW_BSWM_CS_u2MILSEC2TICK_MID(BSW_CANNM_B_CFG_TX_MSG_TIME_CH18)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 19U)
    , BSW_BSWM_CS_u2MILSEC2TICK_MID(BSW_CANNM_B_CFG_TX_MSG_TIME_CH19)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 20U)
    , BSW_BSWM_CS_u2MILSEC2TICK_MID(BSW_CANNM_B_CFG_TX_MSG_TIME_CH20)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 21U)
    , BSW_BSWM_CS_u2MILSEC2TICK_MID(BSW_CANNM_B_CFG_TX_MSG_TIME_CH21)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 22U)
    , BSW_BSWM_CS_u2MILSEC2TICK_MID(BSW_CANNM_B_CFG_TX_MSG_TIME_CH22)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 23U)
    , BSW_BSWM_CS_u2MILSEC2TICK_MID(BSW_CANNM_B_CFG_TX_MSG_TIME_CH23)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 24U)
    , BSW_BSWM_CS_u2MILSEC2TICK_MID(BSW_CANNM_B_CFG_TX_MSG_TIME_CH24)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 25U)
    , BSW_BSWM_CS_u2MILSEC2TICK_MID(BSW_CANNM_B_CFG_TX_MSG_TIME_CH25)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 26U)
    , BSW_BSWM_CS_u2MILSEC2TICK_MID(BSW_CANNM_B_CFG_TX_MSG_TIME_CH26)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 27U)
    , BSW_BSWM_CS_u2MILSEC2TICK_MID(BSW_CANNM_B_CFG_TX_MSG_TIME_CH27)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 28U)
    , BSW_BSWM_CS_u2MILSEC2TICK_MID(BSW_CANNM_B_CFG_TX_MSG_TIME_CH28)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 29U)
    , BSW_BSWM_CS_u2MILSEC2TICK_MID(BSW_CANNM_B_CFG_TX_MSG_TIME_CH29)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 30U)
    , BSW_BSWM_CS_u2MILSEC2TICK_MID(BSW_CANNM_B_CFG_TX_MSG_TIME_CH30)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 31U)
    , BSW_BSWM_CS_u2MILSEC2TICK_MID(BSW_CANNM_B_CFG_TX_MSG_TIME_CH31)
#endif
};

#endif /* ( BSW_CANNM_NM_TYPE_USE_B == BSW_USE ) */

#if ( BSW_CANNM_COMIF_USE == BSW_USE )

/* Switching CanIf callback function */
void (* BswConst bsw_cannm_b_ctrl_ptRxComReqFunc)( BswU1 u1NetID, BswU4 u4RxCanID, BswU1 u1Len, BswConstR BswU1* ptDat ) = BSW_CANNM_B_RXCOMREQ_FUNC;
void (* BswConst bsw_cannm_b_ctrl_ptSetComReqFn)( BswU1 u1NetID, BswU1 u1Len, BswU1* ptDat ) = BSW_CANNM_B_SETCOMREQ_FUNC;


#define BSW_CANNM_B_RXMSG_IDX_CH_0_1    (BSW_CANNM_B_CFG_RXMSG_NMNUM_CH0 + BSW_CANNM_B_CFG_RXMSG_NMNUM_CH1)
#define BSW_CANNM_B_RXMSG_IDX_CH_0_2    (BSW_CANNM_B_RXMSG_IDX_CH_0_1 + BSW_CANNM_B_CFG_RXMSG_NMNUM_CH2)
#define BSW_CANNM_B_RXMSG_IDX_CH_0_3    (BSW_CANNM_B_RXMSG_IDX_CH_0_2 + BSW_CANNM_B_CFG_RXMSG_NMNUM_CH3)
#define BSW_CANNM_B_RXMSG_IDX_CH_0_4    (BSW_CANNM_B_RXMSG_IDX_CH_0_3 + BSW_CANNM_B_CFG_RXMSG_NMNUM_CH4)
#define BSW_CANNM_B_RXMSG_IDX_CH_0_5    (BSW_CANNM_B_RXMSG_IDX_CH_0_4 + BSW_CANNM_B_CFG_RXMSG_NMNUM_CH5)
#define BSW_CANNM_B_RXMSG_IDX_CH_0_6    (BSW_CANNM_B_RXMSG_IDX_CH_0_5 + BSW_CANNM_B_CFG_RXMSG_NMNUM_CH6)
#define BSW_CANNM_B_RXMSG_IDX_CH_0_7    (BSW_CANNM_B_RXMSG_IDX_CH_0_6 + BSW_CANNM_B_CFG_RXMSG_NMNUM_CH7)
#define BSW_CANNM_B_RXMSG_IDX_CH_0_8    (BSW_CANNM_B_RXMSG_IDX_CH_0_7 + BSW_CANNM_B_CFG_RXMSG_NMNUM_CH8)
#define BSW_CANNM_B_RXMSG_IDX_CH_0_9    (BSW_CANNM_B_RXMSG_IDX_CH_0_8 + BSW_CANNM_B_CFG_RXMSG_NMNUM_CH9)
#define BSW_CANNM_B_RXMSG_IDX_CH_0_10   (BSW_CANNM_B_RXMSG_IDX_CH_0_9 + BSW_CANNM_B_CFG_RXMSG_NMNUM_CH10)
#define BSW_CANNM_B_RXMSG_IDX_CH_0_11   (BSW_CANNM_B_RXMSG_IDX_CH_0_10 + BSW_CANNM_B_CFG_RXMSG_NMNUM_CH11)
#define BSW_CANNM_B_RXMSG_IDX_CH_0_12   (BSW_CANNM_B_RXMSG_IDX_CH_0_11 + BSW_CANNM_B_CFG_RXMSG_NMNUM_CH12)
#define BSW_CANNM_B_RXMSG_IDX_CH_0_13   (BSW_CANNM_B_RXMSG_IDX_CH_0_12 + BSW_CANNM_B_CFG_RXMSG_NMNUM_CH13)
#define BSW_CANNM_B_RXMSG_IDX_CH_0_14   (BSW_CANNM_B_RXMSG_IDX_CH_0_13 + BSW_CANNM_B_CFG_RXMSG_NMNUM_CH14)
#define BSW_CANNM_B_RXMSG_IDX_CH_0_15   (BSW_CANNM_B_RXMSG_IDX_CH_0_14 + BSW_CANNM_B_CFG_RXMSG_NMNUM_CH15)
#define BSW_CANNM_B_RXMSG_IDX_CH_0_16   (BSW_CANNM_B_RXMSG_IDX_CH_0_15 + BSW_CANNM_B_CFG_RXMSG_NMNUM_CH16)
#define BSW_CANNM_B_RXMSG_IDX_CH_0_17   (BSW_CANNM_B_RXMSG_IDX_CH_0_16 + BSW_CANNM_B_CFG_RXMSG_NMNUM_CH17)
#define BSW_CANNM_B_RXMSG_IDX_CH_0_18   (BSW_CANNM_B_RXMSG_IDX_CH_0_17 + BSW_CANNM_B_CFG_RXMSG_NMNUM_CH18)
#define BSW_CANNM_B_RXMSG_IDX_CH_0_19   (BSW_CANNM_B_RXMSG_IDX_CH_0_18 + BSW_CANNM_B_CFG_RXMSG_NMNUM_CH19)
#define BSW_CANNM_B_RXMSG_IDX_CH_0_20   (BSW_CANNM_B_RXMSG_IDX_CH_0_19 + BSW_CANNM_B_CFG_RXMSG_NMNUM_CH20)
#define BSW_CANNM_B_RXMSG_IDX_CH_0_21   (BSW_CANNM_B_RXMSG_IDX_CH_0_20 + BSW_CANNM_B_CFG_RXMSG_NMNUM_CH21)
#define BSW_CANNM_B_RXMSG_IDX_CH_0_22   (BSW_CANNM_B_RXMSG_IDX_CH_0_21 + BSW_CANNM_B_CFG_RXMSG_NMNUM_CH22)
#define BSW_CANNM_B_RXMSG_IDX_CH_0_23   (BSW_CANNM_B_RXMSG_IDX_CH_0_22 + BSW_CANNM_B_CFG_RXMSG_NMNUM_CH23)
#define BSW_CANNM_B_RXMSG_IDX_CH_0_24   (BSW_CANNM_B_RXMSG_IDX_CH_0_23 + BSW_CANNM_B_CFG_RXMSG_NMNUM_CH24)
#define BSW_CANNM_B_RXMSG_IDX_CH_0_25   (BSW_CANNM_B_RXMSG_IDX_CH_0_24 + BSW_CANNM_B_CFG_RXMSG_NMNUM_CH25)
#define BSW_CANNM_B_RXMSG_IDX_CH_0_26   (BSW_CANNM_B_RXMSG_IDX_CH_0_25 + BSW_CANNM_B_CFG_RXMSG_NMNUM_CH26)
#define BSW_CANNM_B_RXMSG_IDX_CH_0_27   (BSW_CANNM_B_RXMSG_IDX_CH_0_26 + BSW_CANNM_B_CFG_RXMSG_NMNUM_CH27)
#define BSW_CANNM_B_RXMSG_IDX_CH_0_28   (BSW_CANNM_B_RXMSG_IDX_CH_0_27 + BSW_CANNM_B_CFG_RXMSG_NMNUM_CH28)
#define BSW_CANNM_B_RXMSG_IDX_CH_0_29   (BSW_CANNM_B_RXMSG_IDX_CH_0_28 + BSW_CANNM_B_CFG_RXMSG_NMNUM_CH29)
#define BSW_CANNM_B_RXMSG_IDX_CH_0_30   (BSW_CANNM_B_RXMSG_IDX_CH_0_29 + BSW_CANNM_B_CFG_RXMSG_NMNUM_CH30)
#define BSW_CANNM_B_RXMSG_IDX_CH_0_31   (BSW_CANNM_B_RXMSG_IDX_CH_0_30 + BSW_CANNM_B_CFG_RXMSG_NMNUM_CH31)

/* Location information for received NM message definitions */
BswConst BswU2 bsw_cannm_b_ctrl_u2RxMsgIndex[BSW_CANNM_B_CAN_CH_NUM + 1U] =
{
    (BswU2)0U
   ,(BswU2)(BSW_CANNM_B_CFG_RXMSG_NMNUM_CH0)
#if (BSW_CANNM_B_CAN_CH_NUM > 1U)
   ,(BswU2)(BSW_CANNM_B_RXMSG_IDX_CH_0_1)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 2U)
   ,(BswU2)(BSW_CANNM_B_RXMSG_IDX_CH_0_2)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 3U)
   ,(BswU2)(BSW_CANNM_B_RXMSG_IDX_CH_0_3)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 4U)
   ,(BswU2)(BSW_CANNM_B_RXMSG_IDX_CH_0_4)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 5U)
   ,(BswU2)(BSW_CANNM_B_RXMSG_IDX_CH_0_5)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 6U)
   ,(BswU2)(BSW_CANNM_B_RXMSG_IDX_CH_0_6)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 7U)
   ,(BswU2)(BSW_CANNM_B_RXMSG_IDX_CH_0_7)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 8U)
   ,(BswU2)(BSW_CANNM_B_RXMSG_IDX_CH_0_8)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 9U)
   ,(BswU2)(BSW_CANNM_B_RXMSG_IDX_CH_0_9)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 10U)
   ,(BswU2)(BSW_CANNM_B_RXMSG_IDX_CH_0_10)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 11U)
   ,(BswU2)(BSW_CANNM_B_RXMSG_IDX_CH_0_11)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 12U)
   ,(BswU2)(BSW_CANNM_B_RXMSG_IDX_CH_0_12)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 13U)
   ,(BswU2)(BSW_CANNM_B_RXMSG_IDX_CH_0_13)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 14U)
   ,(BswU2)(BSW_CANNM_B_RXMSG_IDX_CH_0_14)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 15U)
   ,(BswU2)(BSW_CANNM_B_RXMSG_IDX_CH_0_15)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 16U)
   ,(BswU2)(BSW_CANNM_B_RXMSG_IDX_CH_0_16)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 17U)
   ,(BswU2)(BSW_CANNM_B_RXMSG_IDX_CH_0_17)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 18U)
   ,(BswU2)(BSW_CANNM_B_RXMSG_IDX_CH_0_18)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 19U)
   ,(BswU2)(BSW_CANNM_B_RXMSG_IDX_CH_0_19)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 20U)
   ,(BswU2)(BSW_CANNM_B_RXMSG_IDX_CH_0_20)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 21U)
   ,(BswU2)(BSW_CANNM_B_RXMSG_IDX_CH_0_21)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 22U)
   ,(BswU2)(BSW_CANNM_B_RXMSG_IDX_CH_0_22)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 23U)
   ,(BswU2)(BSW_CANNM_B_RXMSG_IDX_CH_0_23)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 24U)
   ,(BswU2)(BSW_CANNM_B_RXMSG_IDX_CH_0_24)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 25U)
   ,(BswU2)(BSW_CANNM_B_RXMSG_IDX_CH_0_25)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 26U)
   ,(BswU2)(BSW_CANNM_B_RXMSG_IDX_CH_0_26)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 27U)
   ,(BswU2)(BSW_CANNM_B_RXMSG_IDX_CH_0_27)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 28U)
   ,(BswU2)(BSW_CANNM_B_RXMSG_IDX_CH_0_28)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 29U)
   ,(BswU2)(BSW_CANNM_B_RXMSG_IDX_CH_0_29)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 30U)
   ,(BswU2)(BSW_CANNM_B_RXMSG_IDX_CH_0_30)
#endif
#if (BSW_CANNM_B_CAN_CH_NUM > 31U)
   ,(BswU2)(BSW_CANNM_B_RXMSG_IDX_CH_0_31)
#endif
};

#endif /* ( BSW_CANNM_COMIF_USE == BSW_USE ) */
#endif /* ((BSW_CANNM_NM_TYPE_USE_B == BSW_USE) || (BSW_CANNM_COMIF_USE == BSW_USE)) */
#endif /* ( BSW_BSWM_CS_FUNC_CANNM == BSW_USE ) */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/10/16                                             */
/*  v1-1-0          :2018/12/14                                             */
/*  v2-0-0          :2021/12/02                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
