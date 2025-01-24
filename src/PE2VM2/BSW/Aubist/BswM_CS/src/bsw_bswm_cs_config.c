/* bsw_bswm_cs_config_c_v3-0-0                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/BSWM/CS/CONFIG/CODE                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>
#include <cs/bsw_cs_system_memmap_pre.h>
#include <ComStack_Types.h>

#include <bswm_cs/bsw_bswm_cs.h>
#include <comm/bsw_comm.h>
#include "../../ComM/inc/bsw_comm_config.h"
#include "../inc/bsw_bswm_cs_config.h"
#include <cs/bsw_cs_system_memmap_post.h>

#if ( BSW_BSWM_CS_FUNC_BSWMCS == BSW_USE )

#include <cs/bsw_cs_system_memmap_pre.h>

#include <nm/bsw_nm.h>
#include <com/bsw_com.h>

#include "../inc/bsw_bswm_cs_status.h"
#include "../inc/bsw_bswm_cs_ctrl.h"
#include "../inc/bsw_bswm_cs_sysstat.h"
#include "../inc/bsw_bswm_cs_system.h"
#include "../inc/bsw_bswm_cs_fail.h"
#include "../inc/bsw_bswm_cs_connector.h"

#include "../cfg/BswM_CS_Cfg.h"

#if ( BSW_BSWM_CS_FUNC_COM == BSW_USE )
#include "../../Com/inc/bsw_com_config.h"
#endif

#if ( BSW_BSWM_CS_FUNC_BSWMCAN == BSW_USE )
#include <bswm_can/bsw_bswm_can.h>
#endif

#include <cs/bsw_cs_system_memmap_post.h>

#if ( BSW_BSWM_CS_FUNC_BSWMETH == BSW_USE )
#include <bswm_eth/bsw_bswm_eth.h>
#endif

#if ( BSW_BSWM_CS_FUNC_BSWM_VPS == BSW_USE )
#include <bswm_vps/bsw_bswm_vps.h>
#endif

#include <cs/bsw_cs_system_memmap_pre.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define BSW_BSWM_CS_CHNUM               (BSW_COMM_CHNUM)
#define BSW_BSWM_CS_IPDUGRPVCT_SIZE     (BSW_COMM_CHNUM << 1U)
#define BSW_BSWM_CS_PWIPDUGRPVCT_SIZE   (BSW_BSWM_CS_IPDUGRPVCT_SIZE << 1U)
#define BSW_BSWM_CS_PNCIPDUGRPVCT_SIZE  (BSW_BSWM_CS_IPDUGRPVCT_SIZE * BSW_BSWM_CS_PNC_REQNUM)

/* Protocol Index, Public function table size (Editing is required when adding protocols) */
#define BSW_BSWM_CS_FUNCTBL_NONE           (0U)
#define BSW_BSWM_CS_FUNCTBL_CAN            (1U)
#define BSW_BSWM_CS_FUNCTBL_LIN            (2U)
#define BSW_BSWM_CS_FUNCTBL_ETH            (3U)
#define BSW_BSWM_CS_FUNCTBL_SIZE           (4U)

/* Channel to Protocol Index Conversion (Editing is required when adding protocols) */
#define BSW_BSWM_CS_IDX_CONV(ch)           (BSW_BSWM_CS_IDX_CONV_CAN(ch))
#define BSW_BSWM_CS_IDX_CONV_CAN(ch)       ((BSW_COMM_BUSTYPE(ch) == BSW_COMM_BUS_TYPE_CAN)  ? BSW_BSWM_CS_FUNCTBL_CAN  : BSW_BSWM_CS_IDX_CONV_LIN(ch))
#define BSW_BSWM_CS_IDX_CONV_LIN(ch)       ((BSW_COMM_BUSTYPE(ch) == BSW_COMM_BUS_TYPE_LIN)  ? BSW_BSWM_CS_FUNCTBL_LIN  : BSW_BSWM_CS_IDX_CONV_ETH(ch))
#define BSW_BSWM_CS_IDX_CONV_ETH(ch)       ((BSW_COMM_BUSTYPE(ch) == BSW_COMM_BUS_TYPE_ETH)  ? BSW_BSWM_CS_FUNCTBL_ETH  : BSW_BSWM_CS_FUNCTBL_NONE)

#if ( BSW_BSWM_CS_FUNC_COM == BSW_USE )
/* Maximum number of event Awake hold messages by channel */
#define BSW_BSWM_CS_EVAWAKE_MSG_NUM_0            (BSW_COM_CH00_EVTWAKEUPNUM)
#define BSW_BSWM_CS_EVAWAKE_MSG_NUM_1            (BSW_COM_CH01_EVTWAKEUPNUM)
#define BSW_BSWM_CS_EVAWAKE_MSG_NUM_2            (BSW_COM_CH02_EVTWAKEUPNUM)
#define BSW_BSWM_CS_EVAWAKE_MSG_NUM_3            (BSW_COM_CH03_EVTWAKEUPNUM)
#define BSW_BSWM_CS_EVAWAKE_MSG_NUM_4            (BSW_COM_CH04_EVTWAKEUPNUM)
#define BSW_BSWM_CS_EVAWAKE_MSG_NUM_5            (BSW_COM_CH05_EVTWAKEUPNUM)
#define BSW_BSWM_CS_EVAWAKE_MSG_NUM_6            (BSW_COM_CH06_EVTWAKEUPNUM)
#define BSW_BSWM_CS_EVAWAKE_MSG_NUM_7            (BSW_COM_CH07_EVTWAKEUPNUM)
#define BSW_BSWM_CS_EVAWAKE_MSG_NUM_8            (BSW_COM_CH08_EVTWAKEUPNUM)
#define BSW_BSWM_CS_EVAWAKE_MSG_NUM_9            (BSW_COM_CH09_EVTWAKEUPNUM)
#define BSW_BSWM_CS_EVAWAKE_MSG_NUM_10           (BSW_COM_CH10_EVTWAKEUPNUM)
#define BSW_BSWM_CS_EVAWAKE_MSG_NUM_11           (BSW_COM_CH11_EVTWAKEUPNUM)
#define BSW_BSWM_CS_EVAWAKE_MSG_NUM_12           (BSW_COM_CH12_EVTWAKEUPNUM)
#define BSW_BSWM_CS_EVAWAKE_MSG_NUM_13           (BSW_COM_CH13_EVTWAKEUPNUM)
#define BSW_BSWM_CS_EVAWAKE_MSG_NUM_14           (BSW_COM_CH14_EVTWAKEUPNUM)
#define BSW_BSWM_CS_EVAWAKE_MSG_NUM_15           (BSW_COM_CH15_EVTWAKEUPNUM)
#define BSW_BSWM_CS_EVAWAKE_MSG_NUM_16           (BSW_COM_CH16_EVTWAKEUPNUM)
#define BSW_BSWM_CS_EVAWAKE_MSG_NUM_17           (BSW_COM_CH17_EVTWAKEUPNUM)
#define BSW_BSWM_CS_EVAWAKE_MSG_NUM_18           (BSW_COM_CH18_EVTWAKEUPNUM)
#define BSW_BSWM_CS_EVAWAKE_MSG_NUM_19           (BSW_COM_CH19_EVTWAKEUPNUM)
#define BSW_BSWM_CS_EVAWAKE_MSG_NUM_20           (BSW_COM_CH20_EVTWAKEUPNUM)
#define BSW_BSWM_CS_EVAWAKE_MSG_NUM_21           (BSW_COM_CH21_EVTWAKEUPNUM)
#define BSW_BSWM_CS_EVAWAKE_MSG_NUM_22           (BSW_COM_CH22_EVTWAKEUPNUM)
#define BSW_BSWM_CS_EVAWAKE_MSG_NUM_23           (BSW_COM_CH23_EVTWAKEUPNUM)
#define BSW_BSWM_CS_EVAWAKE_MSG_NUM_24           (BSW_COM_CH24_EVTWAKEUPNUM)
#define BSW_BSWM_CS_EVAWAKE_MSG_NUM_25           (BSW_COM_CH25_EVTWAKEUPNUM)
#define BSW_BSWM_CS_EVAWAKE_MSG_NUM_26           (BSW_COM_CH26_EVTWAKEUPNUM)
#define BSW_BSWM_CS_EVAWAKE_MSG_NUM_27           (BSW_COM_CH27_EVTWAKEUPNUM)
#define BSW_BSWM_CS_EVAWAKE_MSG_NUM_28           (BSW_COM_CH28_EVTWAKEUPNUM)
#define BSW_BSWM_CS_EVAWAKE_MSG_NUM_29           (BSW_COM_CH29_EVTWAKEUPNUM)
#define BSW_BSWM_CS_EVAWAKE_MSG_NUM_30           (BSW_COM_CH30_EVTWAKEUPNUM)
#define BSW_BSWM_CS_EVAWAKE_MSG_NUM_31           (BSW_COM_CH31_EVTWAKEUPNUM)
#endif

#define BSW_BSWM_CS_TBL_DUMMY_SIZE               (1U)
#define BSW_BSWM_CS_TBL_EVAW_MSGNUM(num)         (BSW_BSWM_CS_EVAWAKE_MSG_NUM_##num)
#define BSW_BSWM_CS_TBL_SIZE_EVAWARY( num )    \
  (( BSW_BSWM_CS_EVAWAKE_MSG_NUM_##num == 0U) ? BSW_BSWM_CS_TBL_DUMMY_SIZE : BSW_BSWM_CS_TBL_EVAW_MSGNUM(num) )

#define BSW_BSWM_CS_TXCTRL_CH_NUM            (BSW_BSWM_CS_CHNUM)

#define BSW_BSWM_CS_PDUTXCTRL_USE(ch)         BSW_BSWM_CS_PDUTXCTRL_USE_CAN(ch)
#define BSW_BSWM_CS_PDUTXCTRL_USE_CAN(ch)     \
        ((BSW_COMM_BUSTYPE(ch) == BSW_COMM_BUS_TYPE_CAN)  ? (BswU1)BSW_USE                     : BSW_BSWM_CS_PDUTXCTRL_USE_LIN(ch))
#define BSW_BSWM_CS_PDUTXCTRL_USE_LIN(ch)     \
        ((BSW_COMM_BUSTYPE(ch) == BSW_COMM_BUS_TYPE_LIN)  ? (BswU1)BSW_NOUSE                   : BSW_BSWM_CS_PDUTXCTRL_USE_ETH(ch))
#define BSW_BSWM_CS_PDUTXCTRL_USE_ETH(ch)     \
        ((BSW_COMM_BUSTYPE(ch) == BSW_COMM_BUS_TYPE_ETH)  ? (BswU1)BSW_USE                     : (BswU1)BSW_NOUSE)

#if ( (BSW_BSWM_CS_FUNC_PDUR == BSW_USE) && (BSW_BSWM_CS_FUNC_CANTX == BSW_USE) )
#define BSW_BSWM_CS_FUNC_GETTXCHCAN         (&bsw_bswm_cs_ctrl_GetTxChCan)
#else
#define BSW_BSWM_CS_FUNC_GETTXCHCAN         (&bsw_bswm_cs_ctrl_GetTxChCan_dmy)
#endif

#if ( (BSW_BSWM_CS_FUNC_PDUR == BSW_USE) && (BSW_BSWM_CS_FUNC_CANRX == BSW_USE) )
#define BSW_BSWM_CS_FUNC_GETRXCHCAN         (&bsw_bswm_cs_ctrl_GetRxChCan)
#else
#define BSW_BSWM_CS_FUNC_GETRXCHCAN         (&bsw_bswm_cs_ctrl_GetRxChCan_dmy)
#endif

#if ( BSW_BSWM_CS_MSG_DELIVER == BSW_BSWM_CS_MSGDELIVER_HIGH )
#define BSW_BSWM_CS_FUNC_CNVMSTKRUP         (&bsw_bswm_cs_system_ms2HTickRup)
#else
#define BSW_BSWM_CS_FUNC_CNVMSTKRUP         (&bsw_bswm_cs_system_ms2MTickRup)
#endif

#if (BSW_BSWM_CS_FUNC_BSWM_VPS == BSW_USE)
#define BSW_BSWM_CS_SETSYSSTAT_FUNC            ( &BswM_VPS_SetSystemStatusCS )
#define BSW_BSWM_CS_GETSYSSTAT_FUNC            ( &BswM_VPS_GetWuSystemStatusCS )
#else
#define BSW_BSWM_CS_SETSYSSTAT_FUNC            ( &bsw_bswm_cs_sysst_SetSystemStatus_dummy )
#define BSW_BSWM_CS_GETSYSSTAT_FUNC            ( &bsw_bswm_cs_sysst_GetWuSystemStatus )
#endif /* (BSW_BSWM_CS_FUNC_BSWM_VPS == BSW_USE) */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
/*------------------------------------------*/
/* Unit:State management                       */
/*------------------------------------------*/
BswU4      bsw_bswm_cs_st_u4IpduGrpVect[BSW_BSWM_CS_PWIPDUGRPVCT_SIZE];
BswU4      bsw_bswm_cs_st_u4DmIpduGrpVect[BSW_BSWM_CS_PWIPDUGRPVCT_SIZE];
BswU4      bsw_bswm_cs_st_u4WkupIpduGrVct[BSW_BSWM_CS_PWIPDUGRPVCT_SIZE];

#if ( BSW_BSWM_CS_FUNC_PNCIPDU == BSW_USE )
BswU4      bsw_bswm_cs_st_u4PncIpduGrpVect[BSW_BSWM_CS_PNCIPDUGRPVCT_SIZE];
BswU4      bsw_bswm_cs_st_u4PncDmIpduGrVct[BSW_BSWM_CS_PNCIPDUGRPVCT_SIZE];
BswU4      bsw_bswm_cs_st_u4PncTxStatusVct[BSW_BSWM_CS_PNCIPDUGRPVCT_SIZE];
#endif /* ( BSW_BSWM_CS_FUNC_PNCIPDU == BSW_USE ) */

/*------------------------------------------*/
/* Unit:Channel control                   */
/*------------------------------------------*/
BswU1      bsw_bswm_cs_ctrl_u1TRXStatus[BSW_BSWM_CS_CHNUM];

#if ( BSW_BSWM_CS_FUNC_COM == BSW_USE )
#if (BSW_COM_EVENTAWAKE_USE == BSW_USE)
BswU2      bsw_bswm_cs_ctrl_u2EvAwakeTimer[BSW_BSWM_CS_CHNUM];
#endif /* (BSW_COM_EVENTAWAKE_USE == BSW_USE) */

#if (BSW_COM_EVENTWAKEUPFRAME_USE == BSW_USE)
BswU2                bsw_bswm_cs_ctrl_u2EvTxDlyTimer[BSW_BSWM_CS_CHNUM];    /* Event transmission delay timer            */
Bsw_BswMCS_EvPduType bsw_bswm_cs_ctrl_stEvPduIndex[BSW_BSWM_CS_CHNUM];      /* Structure for managing event transmission PDU by channel */

/* Array for holding PDU for event transmission by channel */
static PduIdType bsw_bswm_cs_ctrl_u2EvPdu0[ BSW_BSWM_CS_TBL_SIZE_EVAWARY( 0 ) ];
#if (BSW_BSWM_CS_CHNUM > 1U)
static PduIdType bsw_bswm_cs_ctrl_u2EvPdu1[ BSW_BSWM_CS_TBL_SIZE_EVAWARY( 1 ) ];
#endif
#if (BSW_BSWM_CS_CHNUM > 2U)
static PduIdType bsw_bswm_cs_ctrl_u2EvPdu2[ BSW_BSWM_CS_TBL_SIZE_EVAWARY( 2 ) ];
#endif
#if (BSW_BSWM_CS_CHNUM > 3U)
static PduIdType bsw_bswm_cs_ctrl_u2EvPdu3[ BSW_BSWM_CS_TBL_SIZE_EVAWARY( 3 ) ];
#endif
#if (BSW_BSWM_CS_CHNUM > 4U)
static PduIdType bsw_bswm_cs_ctrl_u2EvPdu4[ BSW_BSWM_CS_TBL_SIZE_EVAWARY( 4 ) ];
#endif
#if (BSW_BSWM_CS_CHNUM > 5U)
static PduIdType bsw_bswm_cs_ctrl_u2EvPdu5[ BSW_BSWM_CS_TBL_SIZE_EVAWARY( 5 ) ];
#endif
#if (BSW_BSWM_CS_CHNUM > 6U)
static PduIdType bsw_bswm_cs_ctrl_u2EvPdu6[ BSW_BSWM_CS_TBL_SIZE_EVAWARY( 6 ) ];
#endif
#if (BSW_BSWM_CS_CHNUM > 7U)
static PduIdType bsw_bswm_cs_ctrl_u2EvPdu7[ BSW_BSWM_CS_TBL_SIZE_EVAWARY( 7 ) ];
#endif
#if (BSW_BSWM_CS_CHNUM > 8U)
static PduIdType bsw_bswm_cs_ctrl_u2EvPdu8[ BSW_BSWM_CS_TBL_SIZE_EVAWARY( 8 ) ];
#endif
#if (BSW_BSWM_CS_CHNUM > 9U)
static PduIdType bsw_bswm_cs_ctrl_u2EvPdu9[ BSW_BSWM_CS_TBL_SIZE_EVAWARY( 9 ) ];
#endif
#if (BSW_BSWM_CS_CHNUM > 10U)
static PduIdType bsw_bswm_cs_ctrl_u2EvPdu10[ BSW_BSWM_CS_TBL_SIZE_EVAWARY( 10 ) ];
#endif
#if (BSW_BSWM_CS_CHNUM > 11U)
static PduIdType bsw_bswm_cs_ctrl_u2EvPdu11[ BSW_BSWM_CS_TBL_SIZE_EVAWARY( 11 ) ];
#endif
#if (BSW_BSWM_CS_CHNUM > 12U)
static PduIdType bsw_bswm_cs_ctrl_u2EvPdu12[ BSW_BSWM_CS_TBL_SIZE_EVAWARY( 12 ) ];
#endif
#if (BSW_BSWM_CS_CHNUM > 13U)
static PduIdType bsw_bswm_cs_ctrl_u2EvPdu13[ BSW_BSWM_CS_TBL_SIZE_EVAWARY( 13 ) ];
#endif
#if (BSW_BSWM_CS_CHNUM > 14U)
static PduIdType bsw_bswm_cs_ctrl_u2EvPdu14[ BSW_BSWM_CS_TBL_SIZE_EVAWARY( 14 ) ];
#endif
#if (BSW_BSWM_CS_CHNUM > 15U)
static PduIdType bsw_bswm_cs_ctrl_u2EvPdu15[ BSW_BSWM_CS_TBL_SIZE_EVAWARY( 15 ) ];
#endif
#if (BSW_BSWM_CS_CHNUM > 16U)
static PduIdType bsw_bswm_cs_ctrl_u2EvPdu16[ BSW_BSWM_CS_TBL_SIZE_EVAWARY( 16 ) ];
#endif
#if (BSW_BSWM_CS_CHNUM > 17U)
static PduIdType bsw_bswm_cs_ctrl_u2EvPdu17[ BSW_BSWM_CS_TBL_SIZE_EVAWARY( 17 ) ];
#endif
#if (BSW_BSWM_CS_CHNUM > 18U)
static PduIdType bsw_bswm_cs_ctrl_u2EvPdu18[ BSW_BSWM_CS_TBL_SIZE_EVAWARY( 18 ) ];
#endif
#if (BSW_BSWM_CS_CHNUM > 19U)
static PduIdType bsw_bswm_cs_ctrl_u2EvPdu19[ BSW_BSWM_CS_TBL_SIZE_EVAWARY( 19 ) ];
#endif
#if (BSW_BSWM_CS_CHNUM > 20U)
static PduIdType bsw_bswm_cs_ctrl_u2EvPdu20[ BSW_BSWM_CS_TBL_SIZE_EVAWARY( 20 ) ];
#endif
#if (BSW_BSWM_CS_CHNUM > 21U)
static PduIdType bsw_bswm_cs_ctrl_u2EvPdu21[ BSW_BSWM_CS_TBL_SIZE_EVAWARY( 21 ) ];
#endif
#if (BSW_BSWM_CS_CHNUM > 22U)
static PduIdType bsw_bswm_cs_ctrl_u2EvPdu22[ BSW_BSWM_CS_TBL_SIZE_EVAWARY( 22 ) ];
#endif
#if (BSW_BSWM_CS_CHNUM > 23U)
static PduIdType bsw_bswm_cs_ctrl_u2EvPdu23[ BSW_BSWM_CS_TBL_SIZE_EVAWARY( 23 ) ];
#endif
#if (BSW_BSWM_CS_CHNUM > 24U)
static PduIdType bsw_bswm_cs_ctrl_u2EvPdu24[ BSW_BSWM_CS_TBL_SIZE_EVAWARY( 24 ) ];
#endif
#if (BSW_BSWM_CS_CHNUM > 25U)
static PduIdType bsw_bswm_cs_ctrl_u2EvPdu25[ BSW_BSWM_CS_TBL_SIZE_EVAWARY( 25 ) ];
#endif
#if (BSW_BSWM_CS_CHNUM > 26U)
static PduIdType bsw_bswm_cs_ctrl_u2EvPdu26[ BSW_BSWM_CS_TBL_SIZE_EVAWARY( 26 ) ];
#endif
#if (BSW_BSWM_CS_CHNUM > 27U)
static PduIdType bsw_bswm_cs_ctrl_u2EvPdu27[ BSW_BSWM_CS_TBL_SIZE_EVAWARY( 27 ) ];
#endif
#if (BSW_BSWM_CS_CHNUM > 28U)
static PduIdType bsw_bswm_cs_ctrl_u2EvPdu28[ BSW_BSWM_CS_TBL_SIZE_EVAWARY( 28 ) ];
#endif
#if (BSW_BSWM_CS_CHNUM > 29U)
static PduIdType bsw_bswm_cs_ctrl_u2EvPdu29[ BSW_BSWM_CS_TBL_SIZE_EVAWARY( 29 ) ];
#endif
#if (BSW_BSWM_CS_CHNUM > 30U)
static PduIdType bsw_bswm_cs_ctrl_u2EvPdu30[ BSW_BSWM_CS_TBL_SIZE_EVAWARY( 30 ) ];
#endif
#if (BSW_BSWM_CS_CHNUM > 31U)
static PduIdType bsw_bswm_cs_ctrl_u2EvPdu31[ BSW_BSWM_CS_TBL_SIZE_EVAWARY( 31 ) ];
#endif


#endif /* (BSW_COM_EVENTWAKEUPFRAME_USE == BSW_USE) */
#endif /* ( BSW_BSWM_CS_FUNC_COM == BSW_USE ) */

#if ( BSW_BSWM_CS_ECU_SLEEP == BSW_USE )
Bsw_BswMCS_ChPowerType bsw_bswm_cs_ctrl_stChPw[BSW_BSWM_CS_CHNUM];    /* Channel power state */
#endif

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
/*------------------------------------------*/
/* Unit:State management                       */
/*------------------------------------------*/
BswConst BswU1 bsw_bswm_cs_st_u1IpduGrpVctSz = (BswU1)BSW_BSWM_CS_IPDUGRPVCT_SIZE;

#if ( BSW_BSWM_CS_FUNC_PNCIPDU == BSW_USE )
/* Receive enable type table of PNC I-PDU control */
BswConst BswU1 bsw_bswm_cs_st_u1PncIpduRx[BSW_BSWM_CS_CHNUM] =
{
    (BswU1)BSW_BSWM_CS_PNCIPDU_RX(0)
#if (BSW_BSWM_CS_CHNUM > 1U)
   ,(BswU1)BSW_BSWM_CS_PNCIPDU_RX(1)
#endif
#if (BSW_BSWM_CS_CHNUM > 2U)
   ,(BswU1)BSW_BSWM_CS_PNCIPDU_RX(2)
#endif
#if (BSW_BSWM_CS_CHNUM > 3U)
   ,(BswU1)BSW_BSWM_CS_PNCIPDU_RX(3)
#endif
#if (BSW_BSWM_CS_CHNUM > 4U)
   ,(BswU1)BSW_BSWM_CS_PNCIPDU_RX(4)
#endif
#if (BSW_BSWM_CS_CHNUM > 5U)
   ,(BswU1)BSW_BSWM_CS_PNCIPDU_RX(5)
#endif
#if (BSW_BSWM_CS_CHNUM > 6U)
   ,(BswU1)BSW_BSWM_CS_PNCIPDU_RX(6)
#endif
#if (BSW_BSWM_CS_CHNUM > 7U)
   ,(BswU1)BSW_BSWM_CS_PNCIPDU_RX(7)
#endif
#if (BSW_BSWM_CS_CHNUM > 8U)
   ,(BswU1)BSW_BSWM_CS_PNCIPDU_RX(8)
#endif
#if (BSW_BSWM_CS_CHNUM > 9U)
   ,(BswU1)BSW_BSWM_CS_PNCIPDU_RX(9)
#endif
#if (BSW_BSWM_CS_CHNUM > 10U)
   ,(BswU1)BSW_BSWM_CS_PNCIPDU_RX(10)
#endif
#if (BSW_BSWM_CS_CHNUM > 11U)
   ,(BswU1)BSW_BSWM_CS_PNCIPDU_RX(11)
#endif
#if (BSW_BSWM_CS_CHNUM > 12U)
   ,(BswU1)BSW_BSWM_CS_PNCIPDU_RX(12)
#endif
#if (BSW_BSWM_CS_CHNUM > 13U)
   ,(BswU1)BSW_BSWM_CS_PNCIPDU_RX(13)
#endif
#if (BSW_BSWM_CS_CHNUM > 14U)
   ,(BswU1)BSW_BSWM_CS_PNCIPDU_RX(14)
#endif
#if (BSW_BSWM_CS_CHNUM > 15U)
   ,(BswU1)BSW_BSWM_CS_PNCIPDU_RX(15)
#endif
#if (BSW_BSWM_CS_CHNUM > 16U)
   ,(BswU1)BSW_BSWM_CS_PNCIPDU_RX(16)
#endif
#if (BSW_BSWM_CS_CHNUM > 17U)
   ,(BswU1)BSW_BSWM_CS_PNCIPDU_RX(17)
#endif
#if (BSW_BSWM_CS_CHNUM > 18U)
   ,(BswU1)BSW_BSWM_CS_PNCIPDU_RX(18)
#endif
#if (BSW_BSWM_CS_CHNUM > 19U)
   ,(BswU1)BSW_BSWM_CS_PNCIPDU_RX(19)
#endif
#if (BSW_BSWM_CS_CHNUM > 20U)
   ,(BswU1)BSW_BSWM_CS_PNCIPDU_RX(20)
#endif
#if (BSW_BSWM_CS_CHNUM > 21U)
   ,(BswU1)BSW_BSWM_CS_PNCIPDU_RX(21)
#endif
#if (BSW_BSWM_CS_CHNUM > 22U)
   ,(BswU1)BSW_BSWM_CS_PNCIPDU_RX(22)
#endif
#if (BSW_BSWM_CS_CHNUM > 23U)
   ,(BswU1)BSW_BSWM_CS_PNCIPDU_RX(23)
#endif
#if (BSW_BSWM_CS_CHNUM > 24U)
   ,(BswU1)BSW_BSWM_CS_PNCIPDU_RX(24)
#endif
#if (BSW_BSWM_CS_CHNUM > 25U)
   ,(BswU1)BSW_BSWM_CS_PNCIPDU_RX(25)
#endif
#if (BSW_BSWM_CS_CHNUM > 26U)
   ,(BswU1)BSW_BSWM_CS_PNCIPDU_RX(26)
#endif
#if (BSW_BSWM_CS_CHNUM > 27U)
   ,(BswU1)BSW_BSWM_CS_PNCIPDU_RX(27)
#endif
#if (BSW_BSWM_CS_CHNUM > 28U)
   ,(BswU1)BSW_BSWM_CS_PNCIPDU_RX(28)
#endif
#if (BSW_BSWM_CS_CHNUM > 29U)
   ,(BswU1)BSW_BSWM_CS_PNCIPDU_RX(29)
#endif
#if (BSW_BSWM_CS_CHNUM > 30U)
   ,(BswU1)BSW_BSWM_CS_PNCIPDU_RX(30)
#endif
#if (BSW_BSWM_CS_CHNUM > 31U)
   ,(BswU1)BSW_BSWM_CS_PNCIPDU_RX(31)
#endif
};
#endif /* ( BSW_BSWM_CS_FUNC_PNCIPDU == BSW_USE ) */

/*------------------------------------------*/
/* Unit:Channel control                   */
/*------------------------------------------*/
BswConst BswU1 bsw_bswm_cs_ctrl_u1ChNum        = (BswU1)BSW_BSWM_CS_CHNUM;

BswConst BswU2 bsw_bswm_cs_system_u2MidTickTm  = (BswU2)((BswU4)BSW_BSWM_CS_MPU_TICKTIME * (BswU4)BSW_BSWM_CS_TICKTIME_MID);
BswConst BswU2 bsw_bswm_cs_system_u2HighTickTm = (BswU2)((BswU4)BSW_BSWM_CS_MPU_TICKTIME * (BswU4)BSW_BSWM_CS_TICKTIME_HIGH);

/* Tick conversion function */
uint16 (* BswConst bsw_bswm_cs_ctrl_ptCnvMsTkRpFnc)( uint16 msTime ) = BSW_BSWM_CS_FUNC_CNVMSTKRUP;

/* Channel number getting function */
BswU1 (* BswConst bsw_bswm_cs_ctrl_ptGetChCanFnc)( BswU2 u2CompId, PduIdType u2PduId ) = BSW_BSWM_CS_FUNC_GETTXCHCAN;
BswU1 (* BswConst bsw_bswm_cs_ctrl_ptGetRxChCanFn)( BswU2 u2CompId, PduIdType u2PduId ) = BSW_BSWM_CS_FUNC_GETRXCHCAN;

/* Channel number -> Function table index conversion */
BswConst BswU1 bsw_bswm_cs_ctrl_u1ChToIdxTbl[BSW_BSWM_CS_CHNUM] = {
    (BswU1)BSW_BSWM_CS_IDX_CONV(0)
#if ( BSW_BSWM_CS_CHNUM > 1U )
   ,(BswU1)BSW_BSWM_CS_IDX_CONV(1)
#endif
#if ( BSW_BSWM_CS_CHNUM > 2U )
   ,(BswU1)BSW_BSWM_CS_IDX_CONV(2)
#endif
#if ( BSW_BSWM_CS_CHNUM > 3U )
   ,(BswU1)BSW_BSWM_CS_IDX_CONV(3)
#endif
#if ( BSW_BSWM_CS_CHNUM > 4U )
   ,(BswU1)BSW_BSWM_CS_IDX_CONV(4)
#endif
#if ( BSW_BSWM_CS_CHNUM > 5U )
   ,(BswU1)BSW_BSWM_CS_IDX_CONV(5)
#endif
#if ( BSW_BSWM_CS_CHNUM > 6U )
   ,(BswU1)BSW_BSWM_CS_IDX_CONV(6)
#endif
#if ( BSW_BSWM_CS_CHNUM > 7U )
   ,(BswU1)BSW_BSWM_CS_IDX_CONV(7)
#endif
#if ( BSW_BSWM_CS_CHNUM > 8U )
   ,(BswU1)BSW_BSWM_CS_IDX_CONV(8)
#endif
#if ( BSW_BSWM_CS_CHNUM > 9U )
   ,(BswU1)BSW_BSWM_CS_IDX_CONV(9)
#endif
#if ( BSW_BSWM_CS_CHNUM > 10U )
   ,(BswU1)BSW_BSWM_CS_IDX_CONV(10)
#endif
#if ( BSW_BSWM_CS_CHNUM > 11U )
   ,(BswU1)BSW_BSWM_CS_IDX_CONV(11)
#endif
#if ( BSW_BSWM_CS_CHNUM > 12U )
   ,(BswU1)BSW_BSWM_CS_IDX_CONV(12)
#endif
#if ( BSW_BSWM_CS_CHNUM > 13U )
   ,(BswU1)BSW_BSWM_CS_IDX_CONV(13)
#endif
#if ( BSW_BSWM_CS_CHNUM > 14U )
   ,(BswU1)BSW_BSWM_CS_IDX_CONV(14)
#endif
#if ( BSW_BSWM_CS_CHNUM > 15U )
   ,(BswU1)BSW_BSWM_CS_IDX_CONV(15)
#endif
#if ( BSW_BSWM_CS_CHNUM > 16U )
   ,(BswU1)BSW_BSWM_CS_IDX_CONV(16)
#endif
#if ( BSW_BSWM_CS_CHNUM > 17U )
   ,(BswU1)BSW_BSWM_CS_IDX_CONV(17)
#endif
#if ( BSW_BSWM_CS_CHNUM > 18U )
   ,(BswU1)BSW_BSWM_CS_IDX_CONV(18)
#endif
#if ( BSW_BSWM_CS_CHNUM > 19U )
   ,(BswU1)BSW_BSWM_CS_IDX_CONV(19)
#endif
#if ( BSW_BSWM_CS_CHNUM > 20U )
   ,(BswU1)BSW_BSWM_CS_IDX_CONV(20)
#endif
#if ( BSW_BSWM_CS_CHNUM > 21U )
   ,(BswU1)BSW_BSWM_CS_IDX_CONV(21)
#endif
#if ( BSW_BSWM_CS_CHNUM > 22U )
   ,(BswU1)BSW_BSWM_CS_IDX_CONV(22)
#endif
#if ( BSW_BSWM_CS_CHNUM > 23U )
   ,(BswU1)BSW_BSWM_CS_IDX_CONV(23)
#endif
#if ( BSW_BSWM_CS_CHNUM > 24U )
   ,(BswU1)BSW_BSWM_CS_IDX_CONV(24)
#endif
#if ( BSW_BSWM_CS_CHNUM > 25U )
   ,(BswU1)BSW_BSWM_CS_IDX_CONV(25)
#endif
#if ( BSW_BSWM_CS_CHNUM > 26U )
   ,(BswU1)BSW_BSWM_CS_IDX_CONV(26)
#endif
#if ( BSW_BSWM_CS_CHNUM > 27U )
   ,(BswU1)BSW_BSWM_CS_IDX_CONV(27)
#endif
#if ( BSW_BSWM_CS_CHNUM > 28U )
   ,(BswU1)BSW_BSWM_CS_IDX_CONV(28)
#endif
#if ( BSW_BSWM_CS_CHNUM > 29U )
   ,(BswU1)BSW_BSWM_CS_IDX_CONV(29)
#endif
#if ( BSW_BSWM_CS_CHNUM > 30U )
   ,(BswU1)BSW_BSWM_CS_IDX_CONV(30)
#endif
#if ( BSW_BSWM_CS_CHNUM > 31U )
   ,(BswU1)BSW_BSWM_CS_IDX_CONV(31)
#endif
};

#if ( BSW_BSWM_CS_FUNC_COM == BSW_USE )
BswConst BswU1 bsw_bswm_cs_ctrl_u1PduTxCtrlUse[BSW_BSWM_CS_CHNUM] =
{
    (BswU1)BSW_BSWM_CS_PDUTXCTRL_USE(0)
#if (BSW_BSWM_CS_CHNUM > 1U)
   ,(BswU1)BSW_BSWM_CS_PDUTXCTRL_USE(1)
#endif
#if (BSW_BSWM_CS_CHNUM > 2U)
   ,(BswU1)BSW_BSWM_CS_PDUTXCTRL_USE(2)
#endif
#if (BSW_BSWM_CS_CHNUM > 3U)
   ,(BswU1)BSW_BSWM_CS_PDUTXCTRL_USE(3)
#endif
#if (BSW_BSWM_CS_CHNUM > 4U)
   ,(BswU1)BSW_BSWM_CS_PDUTXCTRL_USE(4)
#endif
#if (BSW_BSWM_CS_CHNUM > 5U)
   ,(BswU1)BSW_BSWM_CS_PDUTXCTRL_USE(5)
#endif
#if (BSW_BSWM_CS_CHNUM > 6U)
   ,(BswU1)BSW_BSWM_CS_PDUTXCTRL_USE(6)
#endif
#if (BSW_BSWM_CS_CHNUM > 7U)
   ,(BswU1)BSW_BSWM_CS_PDUTXCTRL_USE(7)
#endif
#if (BSW_BSWM_CS_CHNUM > 8U)
   ,(BswU1)BSW_BSWM_CS_PDUTXCTRL_USE(8)
#endif
#if (BSW_BSWM_CS_CHNUM > 9U)
   ,(BswU1)BSW_BSWM_CS_PDUTXCTRL_USE(9)
#endif
#if (BSW_BSWM_CS_CHNUM > 10U)
   ,(BswU1)BSW_BSWM_CS_PDUTXCTRL_USE(10)
#endif
#if (BSW_BSWM_CS_CHNUM > 11U)
   ,(BswU1)BSW_BSWM_CS_PDUTXCTRL_USE(11)
#endif
#if (BSW_BSWM_CS_CHNUM > 12U)
   ,(BswU1)BSW_BSWM_CS_PDUTXCTRL_USE(12)
#endif
#if (BSW_BSWM_CS_CHNUM > 13U)
   ,(BswU1)BSW_BSWM_CS_PDUTXCTRL_USE(13)
#endif
#if (BSW_BSWM_CS_CHNUM > 14U)
   ,(BswU1)BSW_BSWM_CS_PDUTXCTRL_USE(14)
#endif
#if (BSW_BSWM_CS_CHNUM > 15U)
   ,(BswU1)BSW_BSWM_CS_PDUTXCTRL_USE(15)
#endif
#if (BSW_BSWM_CS_CHNUM > 16U)
   ,(BswU1)BSW_BSWM_CS_PDUTXCTRL_USE(16)
#endif
#if (BSW_BSWM_CS_CHNUM > 17U)
   ,(BswU1)BSW_BSWM_CS_PDUTXCTRL_USE(17)
#endif
#if (BSW_BSWM_CS_CHNUM > 18U)
   ,(BswU1)BSW_BSWM_CS_PDUTXCTRL_USE(18)
#endif
#if (BSW_BSWM_CS_CHNUM > 19U)
   ,(BswU1)BSW_BSWM_CS_PDUTXCTRL_USE(19)
#endif
#if (BSW_BSWM_CS_CHNUM > 20U)
   ,(BswU1)BSW_BSWM_CS_PDUTXCTRL_USE(20)
#endif
#if (BSW_BSWM_CS_CHNUM > 21U)
   ,(BswU1)BSW_BSWM_CS_PDUTXCTRL_USE(21)
#endif
#if (BSW_BSWM_CS_CHNUM > 22U)
   ,(BswU1)BSW_BSWM_CS_PDUTXCTRL_USE(22)
#endif
#if (BSW_BSWM_CS_CHNUM > 23U)
   ,(BswU1)BSW_BSWM_CS_PDUTXCTRL_USE(23)
#endif
#if (BSW_BSWM_CS_CHNUM > 24U)
   ,(BswU1)BSW_BSWM_CS_PDUTXCTRL_USE(24)
#endif
#if (BSW_BSWM_CS_CHNUM > 25U)
   ,(BswU1)BSW_BSWM_CS_PDUTXCTRL_USE(25)
#endif
#if (BSW_BSWM_CS_CHNUM > 26U)
   ,(BswU1)BSW_BSWM_CS_PDUTXCTRL_USE(26)
#endif
#if (BSW_BSWM_CS_CHNUM > 27U)
   ,(BswU1)BSW_BSWM_CS_PDUTXCTRL_USE(27)
#endif
#if (BSW_BSWM_CS_CHNUM > 28U)
   ,(BswU1)BSW_BSWM_CS_PDUTXCTRL_USE(28)
#endif
#if (BSW_BSWM_CS_CHNUM > 29U)
   ,(BswU1)BSW_BSWM_CS_PDUTXCTRL_USE(29)
#endif
#if (BSW_BSWM_CS_CHNUM > 30U)
   ,(BswU1)BSW_BSWM_CS_PDUTXCTRL_USE(30)
#endif
#if (BSW_BSWM_CS_CHNUM > 31U)
   ,(BswU1)BSW_BSWM_CS_PDUTXCTRL_USE(31)
#endif
};

#if (BSW_COM_EVENTAWAKE_USE == BSW_USE)
/* Event Awake Holding Time Table */
BswConst BswU2 bsw_bswm_cs_ctrl_u2EvAwakeTime[BSW_BSWM_CS_CHNUM] = {
    BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_CFG_EVTAWAKE_0) + BSW_BSWM_CS_u2IMM_COUNT
#if (BSW_BSWM_CS_CHNUM > 1U)
    ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_CFG_EVTAWAKE_1) + BSW_BSWM_CS_u2IMM_COUNT
#endif
#if (BSW_BSWM_CS_CHNUM > 2U)
    ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_CFG_EVTAWAKE_2) + BSW_BSWM_CS_u2IMM_COUNT
#endif
#if (BSW_BSWM_CS_CHNUM > 3U)
    ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_CFG_EVTAWAKE_3) + BSW_BSWM_CS_u2IMM_COUNT
#endif
#if (BSW_BSWM_CS_CHNUM > 4U)
    ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_CFG_EVTAWAKE_4) + BSW_BSWM_CS_u2IMM_COUNT
#endif
#if (BSW_BSWM_CS_CHNUM > 5U)
    ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_CFG_EVTAWAKE_5) + BSW_BSWM_CS_u2IMM_COUNT
#endif
#if (BSW_BSWM_CS_CHNUM > 6U)
    ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_CFG_EVTAWAKE_6) + BSW_BSWM_CS_u2IMM_COUNT
#endif
#if (BSW_BSWM_CS_CHNUM > 7U)
    ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_CFG_EVTAWAKE_7) + BSW_BSWM_CS_u2IMM_COUNT
#endif
#if (BSW_BSWM_CS_CHNUM > 8U)
    ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_CFG_EVTAWAKE_8) + BSW_BSWM_CS_u2IMM_COUNT
#endif
#if (BSW_BSWM_CS_CHNUM > 9U)
    ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_CFG_EVTAWAKE_9) + BSW_BSWM_CS_u2IMM_COUNT
#endif
#if (BSW_BSWM_CS_CHNUM > 10U)
    ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_CFG_EVTAWAKE_10) + BSW_BSWM_CS_u2IMM_COUNT
#endif
#if (BSW_BSWM_CS_CHNUM > 11U)
    ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_CFG_EVTAWAKE_11) + BSW_BSWM_CS_u2IMM_COUNT
#endif
#if (BSW_BSWM_CS_CHNUM > 12U)
    ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_CFG_EVTAWAKE_12) + BSW_BSWM_CS_u2IMM_COUNT
#endif
#if (BSW_BSWM_CS_CHNUM > 13U)
    ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_CFG_EVTAWAKE_13) + BSW_BSWM_CS_u2IMM_COUNT
#endif
#if (BSW_BSWM_CS_CHNUM > 14U)
    ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_CFG_EVTAWAKE_14) + BSW_BSWM_CS_u2IMM_COUNT
#endif
#if (BSW_BSWM_CS_CHNUM > 15U)
    ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_CFG_EVTAWAKE_15) + BSW_BSWM_CS_u2IMM_COUNT
#endif
#if (BSW_BSWM_CS_CHNUM > 16U)
    ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_CFG_EVTAWAKE_16) + BSW_BSWM_CS_u2IMM_COUNT
#endif
#if (BSW_BSWM_CS_CHNUM > 17U)
    ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_CFG_EVTAWAKE_17) + BSW_BSWM_CS_u2IMM_COUNT
#endif
#if (BSW_BSWM_CS_CHNUM > 18U)
    ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_CFG_EVTAWAKE_18) + BSW_BSWM_CS_u2IMM_COUNT
#endif
#if (BSW_BSWM_CS_CHNUM > 19U)
    ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_CFG_EVTAWAKE_19) + BSW_BSWM_CS_u2IMM_COUNT
#endif
#if (BSW_BSWM_CS_CHNUM > 20U)
    ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_CFG_EVTAWAKE_20) + BSW_BSWM_CS_u2IMM_COUNT
#endif
#if (BSW_BSWM_CS_CHNUM > 21U)
    ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_CFG_EVTAWAKE_21) + BSW_BSWM_CS_u2IMM_COUNT
#endif
#if (BSW_BSWM_CS_CHNUM > 22U)
    ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_CFG_EVTAWAKE_22) + BSW_BSWM_CS_u2IMM_COUNT
#endif
#if (BSW_BSWM_CS_CHNUM > 23U)
    ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_CFG_EVTAWAKE_23) + BSW_BSWM_CS_u2IMM_COUNT
#endif
#if (BSW_BSWM_CS_CHNUM > 24U)
    ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_CFG_EVTAWAKE_24) + BSW_BSWM_CS_u2IMM_COUNT
#endif
#if (BSW_BSWM_CS_CHNUM > 25U)
    ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_CFG_EVTAWAKE_25) + BSW_BSWM_CS_u2IMM_COUNT
#endif
#if (BSW_BSWM_CS_CHNUM > 26U)
    ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_CFG_EVTAWAKE_26) + BSW_BSWM_CS_u2IMM_COUNT
#endif
#if (BSW_BSWM_CS_CHNUM > 27U)
    ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_CFG_EVTAWAKE_27) + BSW_BSWM_CS_u2IMM_COUNT
#endif
#if (BSW_BSWM_CS_CHNUM > 28U)
    ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_CFG_EVTAWAKE_28) + BSW_BSWM_CS_u2IMM_COUNT
#endif
#if (BSW_BSWM_CS_CHNUM > 29U)
    ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_CFG_EVTAWAKE_29) + BSW_BSWM_CS_u2IMM_COUNT
#endif
#if (BSW_BSWM_CS_CHNUM > 30U)
    ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_CFG_EVTAWAKE_30) + BSW_BSWM_CS_u2IMM_COUNT
#endif
#if (BSW_BSWM_CS_CHNUM > 31U)
    ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_CFG_EVTAWAKE_31) + BSW_BSWM_CS_u2IMM_COUNT
#endif
};
#endif /* (BSW_COM_EVENTAWAKE_USE == BSW_USE) */

#if (BSW_COM_EVENTWAKEUPFRAME_USE == BSW_USE)
/* Maximum number of pending PDUs for event transmission */
BswConst BswU2 bsw_bswm_cs_ctrl_u2EvPduNum[BSW_BSWM_CS_CHNUM] =
{
     (BswU2)BSW_BSWM_CS_EVAWAKE_MSG_NUM_0
#if (BSW_BSWM_CS_CHNUM > 1U)
    ,(BswU2)BSW_BSWM_CS_EVAWAKE_MSG_NUM_1
#endif
#if (BSW_BSWM_CS_CHNUM > 2U)
    ,(BswU2)BSW_BSWM_CS_EVAWAKE_MSG_NUM_2
#endif
#if (BSW_BSWM_CS_CHNUM > 3U)
    ,(BswU2)BSW_BSWM_CS_EVAWAKE_MSG_NUM_3
#endif
#if (BSW_BSWM_CS_CHNUM > 4U)
    ,(BswU2)BSW_BSWM_CS_EVAWAKE_MSG_NUM_4
#endif
#if (BSW_BSWM_CS_CHNUM > 5U)
    ,(BswU2)BSW_BSWM_CS_EVAWAKE_MSG_NUM_5
#endif
#if (BSW_BSWM_CS_CHNUM > 6U)
    ,(BswU2)BSW_BSWM_CS_EVAWAKE_MSG_NUM_6
#endif
#if (BSW_BSWM_CS_CHNUM > 7U)
    ,(BswU2)BSW_BSWM_CS_EVAWAKE_MSG_NUM_7
#endif
#if (BSW_BSWM_CS_CHNUM > 8U)
    ,(BswU2)BSW_BSWM_CS_EVAWAKE_MSG_NUM_8
#endif
#if (BSW_BSWM_CS_CHNUM > 9U)
    ,(BswU2)BSW_BSWM_CS_EVAWAKE_MSG_NUM_9
#endif
#if (BSW_BSWM_CS_CHNUM > 10U)
    ,(BswU2)BSW_BSWM_CS_EVAWAKE_MSG_NUM_10
#endif
#if (BSW_BSWM_CS_CHNUM > 11U)
    ,(BswU2)BSW_BSWM_CS_EVAWAKE_MSG_NUM_11
#endif
#if (BSW_BSWM_CS_CHNUM > 12U)
    ,(BswU2)BSW_BSWM_CS_EVAWAKE_MSG_NUM_12
#endif
#if (BSW_BSWM_CS_CHNUM > 13U)
    ,(BswU2)BSW_BSWM_CS_EVAWAKE_MSG_NUM_13
#endif
#if (BSW_BSWM_CS_CHNUM > 14U)
    ,(BswU2)BSW_BSWM_CS_EVAWAKE_MSG_NUM_14
#endif
#if (BSW_BSWM_CS_CHNUM > 15U)
    ,(BswU2)BSW_BSWM_CS_EVAWAKE_MSG_NUM_15
#endif
#if (BSW_BSWM_CS_CHNUM > 16U)
    ,(BswU2)BSW_BSWM_CS_EVAWAKE_MSG_NUM_16
#endif
#if (BSW_BSWM_CS_CHNUM > 17U)
    ,(BswU2)BSW_BSWM_CS_EVAWAKE_MSG_NUM_17
#endif
#if (BSW_BSWM_CS_CHNUM > 18U)
    ,(BswU2)BSW_BSWM_CS_EVAWAKE_MSG_NUM_18
#endif
#if (BSW_BSWM_CS_CHNUM > 19U)
    ,(BswU2)BSW_BSWM_CS_EVAWAKE_MSG_NUM_19
#endif
#if (BSW_BSWM_CS_CHNUM > 20U)
    ,(BswU2)BSW_BSWM_CS_EVAWAKE_MSG_NUM_20
#endif
#if (BSW_BSWM_CS_CHNUM > 21U)
    ,(BswU2)BSW_BSWM_CS_EVAWAKE_MSG_NUM_21
#endif
#if (BSW_BSWM_CS_CHNUM > 22U)
    ,(BswU2)BSW_BSWM_CS_EVAWAKE_MSG_NUM_22
#endif
#if (BSW_BSWM_CS_CHNUM > 23U)
    ,(BswU2)BSW_BSWM_CS_EVAWAKE_MSG_NUM_23
#endif
#if (BSW_BSWM_CS_CHNUM > 24U)
    ,(BswU2)BSW_BSWM_CS_EVAWAKE_MSG_NUM_24
#endif
#if (BSW_BSWM_CS_CHNUM > 25U)
    ,(BswU2)BSW_BSWM_CS_EVAWAKE_MSG_NUM_25
#endif
#if (BSW_BSWM_CS_CHNUM > 26U)
    ,(BswU2)BSW_BSWM_CS_EVAWAKE_MSG_NUM_26
#endif
#if (BSW_BSWM_CS_CHNUM > 27U)
    ,(BswU2)BSW_BSWM_CS_EVAWAKE_MSG_NUM_27
#endif
#if (BSW_BSWM_CS_CHNUM > 28U)
    ,(BswU2)BSW_BSWM_CS_EVAWAKE_MSG_NUM_28
#endif
#if (BSW_BSWM_CS_CHNUM > 29U)
    ,(BswU2)BSW_BSWM_CS_EVAWAKE_MSG_NUM_29
#endif
#if (BSW_BSWM_CS_CHNUM > 30U)
    ,(BswU2)BSW_BSWM_CS_EVAWAKE_MSG_NUM_30
#endif
#if (BSW_BSWM_CS_CHNUM > 31U)
    ,(BswU2)BSW_BSWM_CS_EVAWAKE_MSG_NUM_31
#endif
};

/* Event transmission pending PDU queue */
PduIdType* BswConst bsw_bswm_cs_ctrl_ptEvPduQue[ BSW_BSWM_CS_CHNUM ] =
{
    &bsw_bswm_cs_ctrl_u2EvPdu0[0]
#if (BSW_BSWM_CS_CHNUM > 1U)
   ,&bsw_bswm_cs_ctrl_u2EvPdu1[0]
#endif
#if (BSW_BSWM_CS_CHNUM > 2U)
   ,&bsw_bswm_cs_ctrl_u2EvPdu2[0]
#endif
#if (BSW_BSWM_CS_CHNUM > 3U)
   ,&bsw_bswm_cs_ctrl_u2EvPdu3[0]
#endif
#if (BSW_BSWM_CS_CHNUM > 4U)
   ,&bsw_bswm_cs_ctrl_u2EvPdu4[0]
#endif
#if (BSW_BSWM_CS_CHNUM > 5U)
   ,&bsw_bswm_cs_ctrl_u2EvPdu5[0]
#endif
#if (BSW_BSWM_CS_CHNUM > 6U)
   ,&bsw_bswm_cs_ctrl_u2EvPdu6[0]
#endif
#if (BSW_BSWM_CS_CHNUM > 7U)
   ,&bsw_bswm_cs_ctrl_u2EvPdu7[0]
#endif
#if (BSW_BSWM_CS_CHNUM > 8U)
   ,&bsw_bswm_cs_ctrl_u2EvPdu8[0]
#endif
#if (BSW_BSWM_CS_CHNUM > 9U)
   ,&bsw_bswm_cs_ctrl_u2EvPdu9[0]
#endif
#if (BSW_BSWM_CS_CHNUM > 10U)
   ,&bsw_bswm_cs_ctrl_u2EvPdu10[0]
#endif
#if (BSW_BSWM_CS_CHNUM > 11U)
   ,&bsw_bswm_cs_ctrl_u2EvPdu11[0]
#endif
#if (BSW_BSWM_CS_CHNUM > 12U)
   ,&bsw_bswm_cs_ctrl_u2EvPdu12[0]
#endif
#if (BSW_BSWM_CS_CHNUM > 13U)
   ,&bsw_bswm_cs_ctrl_u2EvPdu13[0]
#endif
#if (BSW_BSWM_CS_CHNUM > 14U)
   ,&bsw_bswm_cs_ctrl_u2EvPdu14[0]
#endif
#if (BSW_BSWM_CS_CHNUM > 15U)
   ,&bsw_bswm_cs_ctrl_u2EvPdu15[0]
#endif
#if (BSW_BSWM_CS_CHNUM > 16U)
   ,&bsw_bswm_cs_ctrl_u2EvPdu16[0]
#endif
#if (BSW_BSWM_CS_CHNUM > 17U)
   ,&bsw_bswm_cs_ctrl_u2EvPdu17[0]
#endif
#if (BSW_BSWM_CS_CHNUM > 18U)
   ,&bsw_bswm_cs_ctrl_u2EvPdu18[0]
#endif
#if (BSW_BSWM_CS_CHNUM > 19U)
   ,&bsw_bswm_cs_ctrl_u2EvPdu19[0]
#endif
#if (BSW_BSWM_CS_CHNUM > 20U)
   ,&bsw_bswm_cs_ctrl_u2EvPdu20[0]
#endif
#if (BSW_BSWM_CS_CHNUM > 21U)
   ,&bsw_bswm_cs_ctrl_u2EvPdu21[0]
#endif
#if (BSW_BSWM_CS_CHNUM > 22U)
   ,&bsw_bswm_cs_ctrl_u2EvPdu22[0]
#endif
#if (BSW_BSWM_CS_CHNUM > 23U)
   ,&bsw_bswm_cs_ctrl_u2EvPdu23[0]
#endif
#if (BSW_BSWM_CS_CHNUM > 24U)
   ,&bsw_bswm_cs_ctrl_u2EvPdu24[0]
#endif
#if (BSW_BSWM_CS_CHNUM > 25U)
   ,&bsw_bswm_cs_ctrl_u2EvPdu25[0]
#endif
#if (BSW_BSWM_CS_CHNUM > 26U)
   ,&bsw_bswm_cs_ctrl_u2EvPdu26[0]
#endif
#if (BSW_BSWM_CS_CHNUM > 27U)
   ,&bsw_bswm_cs_ctrl_u2EvPdu27[0]
#endif
#if (BSW_BSWM_CS_CHNUM > 28U)
   ,&bsw_bswm_cs_ctrl_u2EvPdu28[0]
#endif
#if (BSW_BSWM_CS_CHNUM > 29U)
   ,&bsw_bswm_cs_ctrl_u2EvPdu29[0]
#endif
#if (BSW_BSWM_CS_CHNUM > 30U)
   ,&bsw_bswm_cs_ctrl_u2EvPdu30[0]
#endif
#if (BSW_BSWM_CS_CHNUM > 31U)
   ,&bsw_bswm_cs_ctrl_u2EvPdu31[0]
#endif
};
#endif /* (BSW_COM_EVENTWAKEUPFRAME_USE == BSW_USE) */
#endif /* ( BSW_BSWM_CS_FUNC_COM == BSW_USE ) */

#if ( BSW_BSWM_CS_TXCTRL_FUNC == BSW_USE )
/* Bus type:Invalid transmission control function table */
static BswConst Bsw_BswmCS_BusTxFuncTblType bsw_bswm_cs_ctrl_ptDmyTxFunc = {
    &bsw_bswm_cs_ctrl_StopTxPdu_dmy
    ,&bsw_bswm_cs_ctrl_RsmTxPdu_dmy
};

#if ( BSW_BSWM_CS_FUNC_CAN == BSW_USE )
/* Bus type:CAN Transmission control function table */
static BswConst Bsw_BswmCS_BusTxFuncTblType bsw_bswm_cs_ctrl_ptCanTxFunc = {
    &BswM_Can_StopTxPdu
    ,&BswM_Can_ResumeTxPdu
};
#endif

#if ( BSW_BSWM_CS_FUNC_ETH == BSW_USE )
/* Bus type:ETH Transmission control function table */
static BswConst Bsw_BswmCS_BusTxFuncTblType bsw_bswm_cs_ctrl_ptEthTxFunc = {
    &BswM_Eth_StopTxPdu
    ,&BswM_Eth_ResumeTxPdu
};
#endif

/* Channel number -> Function table conversion by protocol         */
/* Function table of transmission restriction function (Editing is required when adding protocols) */
BswConst Bsw_BswmCS_BusTxFuncTblType* BswConst bsw_bswm_cs_ctrl_ptBusTxFuncTbl[BSW_BSWM_CS_FUNCTBL_SIZE] = {
     &bsw_bswm_cs_ctrl_ptDmyTxFunc
#if ( BSW_BSWM_CS_FUNC_CAN == BSW_USE )
    ,&bsw_bswm_cs_ctrl_ptCanTxFunc
#else
    ,&bsw_bswm_cs_ctrl_ptDmyTxFunc
#endif
    ,&bsw_bswm_cs_ctrl_ptDmyTxFunc
#if ( BSW_BSWM_CS_FUNC_ETH == BSW_USE )
    ,&bsw_bswm_cs_ctrl_ptEthTxFunc
#else
    ,&bsw_bswm_cs_ctrl_ptDmyTxFunc
#endif
};

/* How to control the transmission stop/resume function */
BswConst         BswU1  bsw_bswm_cs_ctrl_u1TxCtrlType[BSW_BSWM_CS_TXCTRL_CH_NUM] =
{
    (BswU1)BSW_BSWM_CS_CFG_TXCTRL_TYPE_0
#if (BSW_BSWM_CS_TXCTRL_CH_NUM > 1U)
   ,(BswU1)BSW_BSWM_CS_CFG_TXCTRL_TYPE_1
#endif
#if (BSW_BSWM_CS_TXCTRL_CH_NUM > 2U)
   ,(BswU1)BSW_BSWM_CS_CFG_TXCTRL_TYPE_2
#endif
#if (BSW_BSWM_CS_TXCTRL_CH_NUM > 3U)
   ,(BswU1)BSW_BSWM_CS_CFG_TXCTRL_TYPE_3
#endif
#if (BSW_BSWM_CS_TXCTRL_CH_NUM > 4U)
   ,(BswU1)BSW_BSWM_CS_CFG_TXCTRL_TYPE_4
#endif
#if (BSW_BSWM_CS_TXCTRL_CH_NUM > 5U)
   ,(BswU1)BSW_BSWM_CS_CFG_TXCTRL_TYPE_5
#endif
#if (BSW_BSWM_CS_TXCTRL_CH_NUM > 6U)
   ,(BswU1)BSW_BSWM_CS_CFG_TXCTRL_TYPE_6
#endif
#if (BSW_BSWM_CS_TXCTRL_CH_NUM > 7U)
   ,(BswU1)BSW_BSWM_CS_CFG_TXCTRL_TYPE_7
#endif
#if (BSW_BSWM_CS_TXCTRL_CH_NUM > 8U)
   ,(BswU1)BSW_BSWM_CS_CFG_TXCTRL_TYPE_8
#endif
#if (BSW_BSWM_CS_TXCTRL_CH_NUM > 9U)
   ,(BswU1)BSW_BSWM_CS_CFG_TXCTRL_TYPE_9
#endif
#if (BSW_BSWM_CS_TXCTRL_CH_NUM > 10U)
   ,(BswU1)BSW_BSWM_CS_CFG_TXCTRL_TYPE_10
#endif
#if (BSW_BSWM_CS_TXCTRL_CH_NUM > 11U)
   ,(BswU1)BSW_BSWM_CS_CFG_TXCTRL_TYPE_11
#endif
#if (BSW_BSWM_CS_TXCTRL_CH_NUM > 12U)
   ,(BswU1)BSW_BSWM_CS_CFG_TXCTRL_TYPE_12
#endif
#if (BSW_BSWM_CS_TXCTRL_CH_NUM > 13U)
   ,(BswU1)BSW_BSWM_CS_CFG_TXCTRL_TYPE_13
#endif
#if (BSW_BSWM_CS_TXCTRL_CH_NUM > 14U)
   ,(BswU1)BSW_BSWM_CS_CFG_TXCTRL_TYPE_14
#endif
#if (BSW_BSWM_CS_TXCTRL_CH_NUM > 15U)
   ,(BswU1)BSW_BSWM_CS_CFG_TXCTRL_TYPE_15
#endif
#if (BSW_BSWM_CS_TXCTRL_CH_NUM > 16U)
   ,(BswU1)BSW_BSWM_CS_CFG_TXCTRL_TYPE_16
#endif
#if (BSW_BSWM_CS_TXCTRL_CH_NUM > 17U)
   ,(BswU1)BSW_BSWM_CS_CFG_TXCTRL_TYPE_17
#endif
#if (BSW_BSWM_CS_TXCTRL_CH_NUM > 18U)
   ,(BswU1)BSW_BSWM_CS_CFG_TXCTRL_TYPE_18
#endif
#if (BSW_BSWM_CS_TXCTRL_CH_NUM > 19U)
   ,(BswU1)BSW_BSWM_CS_CFG_TXCTRL_TYPE_19
#endif
#if (BSW_BSWM_CS_TXCTRL_CH_NUM > 20U)
   ,(BswU1)BSW_BSWM_CS_CFG_TXCTRL_TYPE_20
#endif
#if (BSW_BSWM_CS_TXCTRL_CH_NUM > 21U)
   ,(BswU1)BSW_BSWM_CS_CFG_TXCTRL_TYPE_21
#endif
#if (BSW_BSWM_CS_TXCTRL_CH_NUM > 22U)
   ,(BswU1)BSW_BSWM_CS_CFG_TXCTRL_TYPE_22
#endif
#if (BSW_BSWM_CS_TXCTRL_CH_NUM > 23U)
   ,(BswU1)BSW_BSWM_CS_CFG_TXCTRL_TYPE_23
#endif
#if (BSW_BSWM_CS_TXCTRL_CH_NUM > 24U)
   ,(BswU1)BSW_BSWM_CS_CFG_TXCTRL_TYPE_24
#endif
#if (BSW_BSWM_CS_TXCTRL_CH_NUM > 25U)
   ,(BswU1)BSW_BSWM_CS_CFG_TXCTRL_TYPE_25
#endif
#if (BSW_BSWM_CS_TXCTRL_CH_NUM > 26U)
   ,(BswU1)BSW_BSWM_CS_CFG_TXCTRL_TYPE_26
#endif
#if (BSW_BSWM_CS_TXCTRL_CH_NUM > 27U)
   ,(BswU1)BSW_BSWM_CS_CFG_TXCTRL_TYPE_27
#endif
#if (BSW_BSWM_CS_TXCTRL_CH_NUM > 28U)
   ,(BswU1)BSW_BSWM_CS_CFG_TXCTRL_TYPE_28
#endif
#if (BSW_BSWM_CS_TXCTRL_CH_NUM > 29U)
   ,(BswU1)BSW_BSWM_CS_CFG_TXCTRL_TYPE_29
#endif
#if (BSW_BSWM_CS_TXCTRL_CH_NUM > 30U)
   ,(BswU1)BSW_BSWM_CS_CFG_TXCTRL_TYPE_30
#endif
#if (BSW_BSWM_CS_TXCTRL_CH_NUM > 31U)
   ,(BswU1)BSW_BSWM_CS_CFG_TXCTRL_TYPE_31
#endif
};
#endif /* ( BSW_BSWM_CS_TXCTRL_FUNC == BSW_USE ) */

#if ( BSW_BSWM_CS_CHRSTCTRL_FUNC == BSW_USE )
/* Channel number -> Function table conversion by protocol           */
/* Function table for channel restart (Editing is required when adding protocols) */
void (* BswConst bsw_bswm_cs_ptBusChRstFuncTbl[BSW_BSWM_CS_FUNCTBL_SIZE])( NetworkHandleType Network ) = {
     &bsw_bswm_cs_ctrl_RestartCh_dmy
#if ( BSW_BSWM_CS_FUNC_CAN == BSW_USE )
    ,&BswM_Can_RestartChCtrl
#else
    ,&bsw_bswm_cs_ctrl_RestartCh_dmy
#endif
    ,&bsw_bswm_cs_ctrl_RestartCh_dmy
    ,&bsw_bswm_cs_ctrl_RestartCh_dmy
};
#endif /*  ( BSW_BSWM_CS_CHRSTCTRL_FUNC == BSW_USE ) */


#if ( BSW_BSWM_CS_DMCTRL_FUNC == BSW_USE )
/* Bus type : Disable receive disconnection limit control function table */
static BswConst Bsw_BswmCS_BusDmFuncTblType bsw_bswm_cs_ctrl_ptDmyDmFunc = {
    &bsw_bswm_cs_ctrl_StopDMCtrl_dmy
    ,&bsw_bswm_cs_ctrl_RsmDMCtrl_dmy
};

#if ( BSW_BSWM_CS_FUNC_CAN == BSW_USE )
/* Bus type : CAN receive disconnection limit control function table */
static BswConst Bsw_BswmCS_BusDmFuncTblType bsw_bswm_cs_ctrl_ptCanDmFunc = {
    &BswM_Can_StopDMControl
    ,&BswM_Can_ResumeDMControl
};
#endif

#if ( BSW_BSWM_CS_FUNC_ETH == BSW_USE )
/* Bus type : ETH receive disconnection limit control function table */
static BswConst Bsw_BswmCS_BusDmFuncTblType bsw_bswm_cs_ctrl_ptEthDmFunc = {
    &BswM_Eth_StopDMControl
    ,&BswM_Eth_ResumeDMControl
};
#endif

/* Channel number -> Function table conversion by protocol           */
/* Receiving disconnection control function table (Editing is required when adding protocols)   */
BswConst Bsw_BswmCS_BusDmFuncTblType* BswConst bsw_bswm_cs_ctrl_ptBusDmFuncTbl[BSW_BSWM_CS_FUNCTBL_SIZE] = { 
     &bsw_bswm_cs_ctrl_ptDmyDmFunc
#if ( BSW_BSWM_CS_FUNC_CAN == BSW_USE )
    ,&bsw_bswm_cs_ctrl_ptCanDmFunc
#else
    ,&bsw_bswm_cs_ctrl_ptDmyDmFunc
#endif
    ,&bsw_bswm_cs_ctrl_ptDmyDmFunc
#if ( BSW_BSWM_CS_FUNC_ETH == BSW_USE )
    ,&bsw_bswm_cs_ctrl_ptEthDmFunc
#else
    ,&bsw_bswm_cs_ctrl_ptDmyDmFunc
#endif
};
#endif /* ( BSW_BSWM_CS_DMCTRL_FUNC == BSW_USE ) */

void    (* BswConst bsw_bswm_cs_st_ptSetSysStatFn)( uint32* Mask, uint32* SysStatus ) = BSW_BSWM_CS_SETSYSSTAT_FUNC;
void    (* BswConst bsw_bswm_cs_st_ptGetSysStatFn)( uint32* SysStatus )               = BSW_BSWM_CS_GETSYSSTAT_FUNC;

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#include <cs/bsw_cs_system_memmap_post.h>

#endif /* ( BSW_BSWM_CS_FUNC_BSWMCS == BSW_USE ) */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/10/17                                             */
/*  v1-1-0          :2019/01/16                                             */
/*  v2-0-0          :2021/12/09                                             */
/*  v2-1-0          :2023/02/03                                             */
/*  v2-2-0          :2023/05/09                                             */
/*  v3-0-0          :2024/11/15                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
