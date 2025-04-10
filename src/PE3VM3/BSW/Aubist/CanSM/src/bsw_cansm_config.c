/* bsw_cansm_config_c_v3-0-0                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANSM/CONFIG/CODE                                     */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/


/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>
#include "../inc/bsw_cansm_MemMap.h"
#include <ComStack_Types.h>
#include <canif/bsw_can_generaltypes.h>

#include <bswm_cs/bsw_bswm_cs.h>
#include <comm/bsw_comm.h>
#include "../../ComM/inc/bsw_comm_config.h"
#include "../../BswM_CS/inc/bsw_bswm_cs_config.h"
#if( BSW_BSWM_CS_FUNC_CANSM == BSW_USE )

#include <cansm/bsw_cansm.h>
#include "../inc/bsw_cansm_st.h"
#include "../inc/bsw_cansm_fs.h"
#include "../inc/bsw_cansm_trx.h"
#include "../inc/bsw_cansm_config.h"
#include "../cfg/CanSM_Cfg.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define BSW_CANSM_CHNUM          (BSW_COMM_BUS_TYPE_CHNUM(CAN))

#define BSW_CANSM_CH_OFFSET      (BSW_COMM_BUS_TYPE_OFFSET(CAN))

#define BSW_CANSM_CHKCTRLERR_FUNC(ch)  ((BSW_CANSM_CFG_BUSOFF_RECOVERY_##ch == BSW_CANSM_BUSOFF_RESET) ? &bsw_cansm_fs_ChkCtrlErrNone : &bsw_cansm_fs_ChkCtrlErr)

/* Transceiver mode transition waiting time (ms) */
#if ( BSW_CANSM_TRCV_WAITTIME_0 > BSW_CANSM_TRCV_WAITTIME_1 )
#define BSW_CANSM_MAX_TRCV_WAIT_0_1    (BSW_CANSM_TRCV_WAITTIME_0)
#else
#define BSW_CANSM_MAX_TRCV_WAIT_0_1    (BSW_CANSM_TRCV_WAITTIME_1)
#endif /* ( BSW_CANSM_TRCV_WAITTIME_0 > BSW_CANSM_TRCV_WAITTIME_1 ) */

#if ( BSW_CANSM_TRCV_WAITTIME_2 > BSW_CANSM_TRCV_WAITTIME_3 )
#define BSW_CANSM_MAX_TRCV_WAIT_2_3    (BSW_CANSM_TRCV_WAITTIME_2)
#else
#define BSW_CANSM_MAX_TRCV_WAIT_2_3    (BSW_CANSM_TRCV_WAITTIME_3)
#endif /* ( BSW_CANSM_TRCV_WAITTIME_2 > BSW_CANSM_TRCV_WAITTIME_3 ) */

#if ( BSW_CANSM_TRCV_WAITTIME_4 > BSW_CANSM_TRCV_WAITTIME_5 )
#define BSW_CANSM_MAX_TRCV_WAIT_4_5    (BSW_CANSM_TRCV_WAITTIME_4)
#else
#define BSW_CANSM_MAX_TRCV_WAIT_4_5    (BSW_CANSM_TRCV_WAITTIME_5)
#endif /* ( BSW_CANSM_TRCV_WAITTIME_4 > BSW_CANSM_TRCV_WAITTIME_5 ) */

#if ( BSW_CANSM_TRCV_WAITTIME_6 > BSW_CANSM_TRCV_WAITTIME_7 )
#define BSW_CANSM_MAX_TRCV_WAIT_6_7    (BSW_CANSM_TRCV_WAITTIME_6)
#else
#define BSW_CANSM_MAX_TRCV_WAIT_6_7    (BSW_CANSM_TRCV_WAITTIME_7)
#endif /* ( BSW_CANSM_TRCV_WAITTIME_6 > BSW_CANSM_TRCV_WAITTIME_7 ) */

#if ( BSW_CANSM_TRCV_WAITTIME_8 > BSW_CANSM_TRCV_WAITTIME_9 )
#define BSW_CANSM_MAX_TRCV_WAIT_8_9    (BSW_CANSM_TRCV_WAITTIME_8)
#else
#define BSW_CANSM_MAX_TRCV_WAIT_8_9    (BSW_CANSM_TRCV_WAITTIME_9)
#endif /* ( BSW_CANSM_TRCV_WAITTIME_8 > BSW_CANSM_TRCV_WAITTIME_9 ) */

#if ( BSW_CANSM_TRCV_WAITTIME_10 > BSW_CANSM_TRCV_WAITTIME_11 )
#define BSW_CANSM_MAX_TRCV_WAIT_10_11  (BSW_CANSM_TRCV_WAITTIME_10)
#else
#define BSW_CANSM_MAX_TRCV_WAIT_10_11  (BSW_CANSM_TRCV_WAITTIME_11)
#endif /* ( BSW_CANSM_TRCV_WAITTIME_10 > BSW_CANSM_TRCV_WAITTIME_11 ) */

#if ( BSW_CANSM_TRCV_WAITTIME_12 > BSW_CANSM_TRCV_WAITTIME_13 )
#define BSW_CANSM_MAX_TRCV_WAIT_12_13  (BSW_CANSM_TRCV_WAITTIME_12)
#else
#define BSW_CANSM_MAX_TRCV_WAIT_12_13  (BSW_CANSM_TRCV_WAITTIME_13)
#endif /* ( BSW_CANSM_TRCV_WAITTIME_12 > BSW_CANSM_TRCV_WAITTIME_13 ) */

#if ( BSW_CANSM_TRCV_WAITTIME_14 > BSW_CANSM_TRCV_WAITTIME_15 )
#define BSW_CANSM_MAX_TRCV_WAIT_14_15  (BSW_CANSM_TRCV_WAITTIME_14)
#else
#define BSW_CANSM_MAX_TRCV_WAIT_14_15  (BSW_CANSM_TRCV_WAITTIME_15)
#endif /* ( BSW_CANSM_TRCV_WAITTIME_14 > BSW_CANSM_TRCV_WAITTIME_15 ) */

#if ( BSW_CANSM_TRCV_WAITTIME_16 > BSW_CANSM_TRCV_WAITTIME_17 )
#define BSW_CANSM_MAX_TRCV_WAIT_16_17  (BSW_CANSM_TRCV_WAITTIME_16)
#else
#define BSW_CANSM_MAX_TRCV_WAIT_16_17  (BSW_CANSM_TRCV_WAITTIME_17)
#endif /* ( BSW_CANSM_TRCV_WAITTIME_16 > BSW_CANSM_TRCV_WAITTIME_17 ) */

#if ( BSW_CANSM_TRCV_WAITTIME_18 > BSW_CANSM_TRCV_WAITTIME_19 )
#define BSW_CANSM_MAX_TRCV_WAIT_18_19  (BSW_CANSM_TRCV_WAITTIME_18)
#else
#define BSW_CANSM_MAX_TRCV_WAIT_18_19  (BSW_CANSM_TRCV_WAITTIME_19)
#endif /* ( BSW_CANSM_TRCV_WAITTIME_18 > BSW_CANSM_TRCV_WAITTIME_19 ) */

#if ( BSW_CANSM_TRCV_WAITTIME_20 > BSW_CANSM_TRCV_WAITTIME_21 )
#define BSW_CANSM_MAX_TRCV_WAIT_20_21  (BSW_CANSM_TRCV_WAITTIME_20)
#else
#define BSW_CANSM_MAX_TRCV_WAIT_20_21  (BSW_CANSM_TRCV_WAITTIME_21)
#endif /* ( BSW_CANSM_TRCV_WAITTIME_20 > BSW_CANSM_TRCV_WAITTIME_21 ) */

#if ( BSW_CANSM_TRCV_WAITTIME_22 > BSW_CANSM_TRCV_WAITTIME_23 )
#define BSW_CANSM_MAX_TRCV_WAIT_22_23  (BSW_CANSM_TRCV_WAITTIME_22)
#else
#define BSW_CANSM_MAX_TRCV_WAIT_22_23  (BSW_CANSM_TRCV_WAITTIME_23)
#endif /* ( BSW_CANSM_TRCV_WAITTIME_22 > BSW_CANSM_TRCV_WAITTIME_23 ) */

#if ( BSW_CANSM_TRCV_WAITTIME_24 > BSW_CANSM_TRCV_WAITTIME_25 )
#define BSW_CANSM_MAX_TRCV_WAIT_24_25  (BSW_CANSM_TRCV_WAITTIME_24)
#else
#define BSW_CANSM_MAX_TRCV_WAIT_24_25  (BSW_CANSM_TRCV_WAITTIME_25)
#endif /* ( BSW_CANSM_TRCV_WAITTIME_24 > BSW_CANSM_TRCV_WAITTIME_25 ) */

#if ( BSW_CANSM_TRCV_WAITTIME_26 > BSW_CANSM_TRCV_WAITTIME_27 )
#define BSW_CANSM_MAX_TRCV_WAIT_26_27  (BSW_CANSM_TRCV_WAITTIME_26)
#else
#define BSW_CANSM_MAX_TRCV_WAIT_26_27  (BSW_CANSM_TRCV_WAITTIME_27)
#endif /* ( BSW_CANSM_TRCV_WAITTIME_26 > BSW_CANSM_TRCV_WAITTIME_27 ) */

#if ( BSW_CANSM_TRCV_WAITTIME_28 > BSW_CANSM_TRCV_WAITTIME_29 )
#define BSW_CANSM_MAX_TRCV_WAIT_28_29  (BSW_CANSM_TRCV_WAITTIME_28)
#else
#define BSW_CANSM_MAX_TRCV_WAIT_28_29  (BSW_CANSM_TRCV_WAITTIME_29)
#endif /* ( BSW_CANSM_TRCV_WAITTIME_28 > BSW_CANSM_TRCV_WAITTIME_29 ) */

#if ( BSW_CANSM_TRCV_WAITTIME_30 > BSW_CANSM_TRCV_WAITTIME_31 )
#define BSW_CANSM_MAX_TRCV_WAIT_30_31  (BSW_CANSM_TRCV_WAITTIME_30)
#else
#define BSW_CANSM_MAX_TRCV_WAIT_30_31  (BSW_CANSM_TRCV_WAITTIME_31)
#endif /* ( BSW_CANSM_TRCV_WAITTIME_30 > BSW_CANSM_TRCV_WAITTIME_31 ) */

#if ( BSW_CANSM_MAX_TRCV_WAIT_0_1 > BSW_CANSM_MAX_TRCV_WAIT_2_3 )
#define BSW_CANSM_MAX_TRCV_WAIT_0_3    (BSW_CANSM_MAX_TRCV_WAIT_0_1)
#else
#define BSW_CANSM_MAX_TRCV_WAIT_0_3    (BSW_CANSM_MAX_TRCV_WAIT_2_3)
#endif /* ( BSW_CANSM_MAX_TRCV_WAIT_0_1 > BSW_CANSM_MAX_TRCV_WAIT_2_3 ) */

#if ( BSW_CANSM_MAX_TRCV_WAIT_4_5 > BSW_CANSM_MAX_TRCV_WAIT_6_7 )
#define BSW_CANSM_MAX_TRCV_WAIT_4_7    (BSW_CANSM_MAX_TRCV_WAIT_4_5)
#else
#define BSW_CANSM_MAX_TRCV_WAIT_4_7    (BSW_CANSM_MAX_TRCV_WAIT_6_7)
#endif /* ( BSW_CANSM_MAX_TRCV_WAIT_4_5 > BSW_CANSM_MAX_TRCV_WAIT_6_7 ) */

#if ( BSW_CANSM_MAX_TRCV_WAIT_8_9 > BSW_CANSM_MAX_TRCV_WAIT_10_11 )
#define BSW_CANSM_MAX_TRCV_WAIT_8_11   (BSW_CANSM_MAX_TRCV_WAIT_8_9)
#else
#define BSW_CANSM_MAX_TRCV_WAIT_8_11   (BSW_CANSM_MAX_TRCV_WAIT_10_11)
#endif /* ( BSW_CANSM_MAX_TRCV_WAIT_8_9 > BSW_CANSM_MAX_TRCV_WAIT_10_11 ) */

#if ( BSW_CANSM_MAX_TRCV_WAIT_12_13 > BSW_CANSM_MAX_TRCV_WAIT_14_15 )
#define BSW_CANSM_MAX_TRCV_WAIT_12_15  (BSW_CANSM_MAX_TRCV_WAIT_12_13)
#else
#define BSW_CANSM_MAX_TRCV_WAIT_12_15  (BSW_CANSM_MAX_TRCV_WAIT_14_15)
#endif /* ( BSW_CANSM_MAX_TRCV_WAIT_12_13 > BSW_CANSM_MAX_TRCV_WAIT_14_15 ) */

#if ( BSW_CANSM_MAX_TRCV_WAIT_16_17 > BSW_CANSM_MAX_TRCV_WAIT_18_19 )
#define BSW_CANSM_MAX_TRCV_WAIT_16_19  (BSW_CANSM_MAX_TRCV_WAIT_16_17)
#else
#define BSW_CANSM_MAX_TRCV_WAIT_16_19  (BSW_CANSM_MAX_TRCV_WAIT_18_19)
#endif /* ( BSW_CANSM_MAX_TRCV_WAIT_16_17 > BSW_CANSM_MAX_TRCV_WAIT_18_19 ) */

#if ( BSW_CANSM_MAX_TRCV_WAIT_20_21 > BSW_CANSM_MAX_TRCV_WAIT_22_23 )
#define BSW_CANSM_MAX_TRCV_WAIT_20_23  (BSW_CANSM_MAX_TRCV_WAIT_20_21)
#else
#define BSW_CANSM_MAX_TRCV_WAIT_20_23  (BSW_CANSM_MAX_TRCV_WAIT_22_23)
#endif /* ( BSW_CANSM_MAX_TRCV_WAIT_20_21 > BSW_CANSM_MAX_TRCV_WAIT_22_23 ) */

#if ( BSW_CANSM_MAX_TRCV_WAIT_24_25 > BSW_CANSM_MAX_TRCV_WAIT_26_27 )
#define BSW_CANSM_MAX_TRCV_WAIT_24_27  (BSW_CANSM_MAX_TRCV_WAIT_24_25)
#else
#define BSW_CANSM_MAX_TRCV_WAIT_24_27  (BSW_CANSM_MAX_TRCV_WAIT_26_27)
#endif /* ( BSW_CANSM_MAX_TRCV_WAIT_24_25 > BSW_CANSM_MAX_TRCV_WAIT_26_27 ) */

#if ( BSW_CANSM_MAX_TRCV_WAIT_28_29 > BSW_CANSM_MAX_TRCV_WAIT_30_31 )
#define BSW_CANSM_MAX_TRCV_WAIT_28_31  (BSW_CANSM_MAX_TRCV_WAIT_28_29)
#else
#define BSW_CANSM_MAX_TRCV_WAIT_28_31  (BSW_CANSM_MAX_TRCV_WAIT_30_31)
#endif /* ( BSW_CANSM_MAX_TRCV_WAIT_28_29 > BSW_CANSM_MAX_TRCV_WAIT_30_31 ) */

#if ( BSW_CANSM_MAX_TRCV_WAIT_0_3 > BSW_CANSM_MAX_TRCV_WAIT_4_7 )
#define BSW_CANSM_MAX_TRCV_WAIT_0_7    (BSW_CANSM_MAX_TRCV_WAIT_0_3)
#else
#define BSW_CANSM_MAX_TRCV_WAIT_0_7    (BSW_CANSM_MAX_TRCV_WAIT_4_7)
#endif /* ( BSW_CANSM_MAX_TRCV_WAIT_0_3 > BSW_CANSM_MAX_TRCV_WAIT_4_7 ) */

#if ( BSW_CANSM_MAX_TRCV_WAIT_8_11 > BSW_CANSM_MAX_TRCV_WAIT_12_15 )
#define BSW_CANSM_MAX_TRCV_WAIT_8_15   (BSW_CANSM_MAX_TRCV_WAIT_8_11)
#else
#define BSW_CANSM_MAX_TRCV_WAIT_8_15   (BSW_CANSM_MAX_TRCV_WAIT_12_15)
#endif /* ( BSW_CANSM_MAX_TRCV_WAIT_8_11 > BSW_CANSM_MAX_TRCV_WAIT_12_15 ) */

#if ( BSW_CANSM_MAX_TRCV_WAIT_16_19 > BSW_CANSM_MAX_TRCV_WAIT_20_23 )
#define BSW_CANSM_MAX_TRCV_WAIT_16_23  (BSW_CANSM_MAX_TRCV_WAIT_16_19)
#else
#define BSW_CANSM_MAX_TRCV_WAIT_16_23  (BSW_CANSM_MAX_TRCV_WAIT_20_23)
#endif /* ( BSW_CANSM_MAX_TRCV_WAIT_16_19 > BSW_CANSM_MAX_TRCV_WAIT_20_23 ) */

#if ( BSW_CANSM_MAX_TRCV_WAIT_24_27 > BSW_CANSM_MAX_TRCV_WAIT_28_31 )
#define BSW_CANSM_MAX_TRCV_WAIT_24_31  (BSW_CANSM_MAX_TRCV_WAIT_24_27)
#else
#define BSW_CANSM_MAX_TRCV_WAIT_24_31  (BSW_CANSM_MAX_TRCV_WAIT_28_31)
#endif /* ( BSW_CANSM_MAX_TRCV_WAIT_24_27 > BSW_CANSM_MAX_TRCV_WAIT_28_31 ) */

#if ( BSW_CANSM_MAX_TRCV_WAIT_0_7 > BSW_CANSM_MAX_TRCV_WAIT_8_15 )
#define BSW_CANSM_MAX_TRCV_WAIT_0_15   (BSW_CANSM_MAX_TRCV_WAIT_0_7)
#else
#define BSW_CANSM_MAX_TRCV_WAIT_0_15   (BSW_CANSM_MAX_TRCV_WAIT_8_15)
#endif /* ( BSW_CANSM_MAX_TRCV_WAIT_0_7 > BSW_CANSM_MAX_TRCV_WAIT_8_15 ) */

#if ( BSW_CANSM_MAX_TRCV_WAIT_16_23 > BSW_CANSM_MAX_TRCV_WAIT_24_31 )
#define BSW_CANSM_MAX_TRCV_WAIT_16_31  (BSW_CANSM_MAX_TRCV_WAIT_16_23)
#else
#define BSW_CANSM_MAX_TRCV_WAIT_16_31  (BSW_CANSM_MAX_TRCV_WAIT_24_31)
#endif /* ( BSW_CANSM_MAX_TRCV_WAIT_16_23 > BSW_CANSM_MAX_TRCV_WAIT_24_31 ) */

#if ( BSW_CANSM_MAX_TRCV_WAIT_0_15 > BSW_CANSM_MAX_TRCV_WAIT_16_31 )
#define BSW_CANSM_MAX_TRCV_WAIT        (BSW_CANSM_MAX_TRCV_WAIT_0_15)
#else
#define BSW_CANSM_MAX_TRCV_WAIT        (BSW_CANSM_MAX_TRCV_WAIT_16_31)
#endif /* ( BSW_CANSM_MAX_TRCV_WAIT_0_15 > BSW_CANSM_MAX_TRCV_WAIT_16_31 ) */

/* Transceiver mode transition waiting time (Tick) */
#define BSW_CANSM_u1MAX_TRCV_WAIT       ( (BswU1)(BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANSM_MAX_TRCV_WAIT )) )

/* Macro for determining the maximum value of each timer */
#define BSW_CANSM_u1CHK_STATE_TIME      ( (BSW_CANSM_u1MAX_TRCV_WAIT     > BSW_CANSM_u1DRVSTOP_TIMEOUT    ) ? BSW_CANSM_u1MAX_TRCV_WAIT     : BSW_CANSM_u1DRVSTOP_TIMEOUT )

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
Bsw_CanSM_ChStsType               bsw_cansm_st_stChSts[BSW_CANSM_CHNUM];

/*------------------------------------------*/
/* Unit:Manage fail safe             */
/*------------------------------------------*/
Bsw_CanSM_FsStsType               bsw_cansm_fs_stFsSts[BSW_CANSM_CHNUM];

/*------------------------------------------*/
/* Unit:Manage transmission/receiving log                 */
/*------------------------------------------*/
#if( BSW_CANSM_CFG_TXRX_INDSTATE == BSW_USE )
Bsw_CanSM_NotifStatusType         bsw_cansm_trx_u1TxState[BSW_CANSM_CHNUM];
Bsw_CanSM_NotifStatusType         bsw_cansm_trx_u1RxState[BSW_CANSM_CHNUM];
#endif /* #if( BSW_CANSM_CFG_TXRX_INDSTATE == BSW_USE ) */

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
/*------------------------------------------*/
/* Unit:State management                       */
/*------------------------------------------*/
/* Number of CAN protocol channels */
BswConst BswU1 bsw_cansm_st_u1ChNum    = (BswU1)BSW_CANSM_CHNUM;

/* Number of CAN protocol offsets */
BswConst BswU1 bsw_cansm_st_u1ChOffset = (BswU1)BSW_CANSM_CH_OFFSET;

#if( BSW_BSWM_CS_FUNC_CANTX == BSW_USE )
void (* BswConst bsw_cansm_st_ptDetectNmTxToutFn)(BswU1 u1ChId, BswU2 u2Fail) = &bsw_cansm_st_DetectNmTxTout;
#else
void (* BswConst bsw_cansm_st_ptDetectNmTxToutFn)(BswU1 u1ChId, BswU2 u2Fail) = &bsw_cansm_st_DetectNmTxToutNone;
#endif /* #if( BSW_BSWM_CS_FUNC_CANTX == BSW_USE ) */

/*------------------------------------------*/
/* Unit:Manage fail safe             */
/*------------------------------------------*/
/* Transmission starting delay time table for at bus off */
BswConst BswS2 bsw_cansm_fs_s2BorTimeL1[BSW_CANSM_CHNUM] = 
{
    (BswS2)BSW_CANSM_CFG_BOR_TIME_L1_0
#if( BSW_CANSM_CHNUM > 1U )
   , (BswS2)BSW_CANSM_CFG_BOR_TIME_L1_1
#endif /* #if( BSW_CANSM_CHNUM > 1U ) */
#if( BSW_CANSM_CHNUM > 2U )
   , (BswS2)BSW_CANSM_CFG_BOR_TIME_L1_2
#endif /* #if( BSW_CANSM_CHNUM > 2U ) */
#if( BSW_CANSM_CHNUM > 3U )
   , (BswS2)BSW_CANSM_CFG_BOR_TIME_L1_3
#endif /* #if( BSW_CANSM_CHNUM > 3U ) */
#if( BSW_CANSM_CHNUM > 4U )
   , (BswS2)BSW_CANSM_CFG_BOR_TIME_L1_4
#endif /* #if( BSW_CANSM_CHNUM > 4U ) */
#if( BSW_CANSM_CHNUM > 5U )
   , (BswS2)BSW_CANSM_CFG_BOR_TIME_L1_5
#endif /* #if( BSW_CANSM_CHNUM > 5U ) */
#if( BSW_CANSM_CHNUM > 6U )
   , (BswS2)BSW_CANSM_CFG_BOR_TIME_L1_6
#endif /* #if( BSW_CANSM_CHNUM > 6U ) */
#if( BSW_CANSM_CHNUM > 7U )
   , (BswS2)BSW_CANSM_CFG_BOR_TIME_L1_7
#endif /* #if( BSW_CANSM_CHNUM > 7U ) */
#if( BSW_CANSM_CHNUM > 8U )
   , (BswS2)BSW_CANSM_CFG_BOR_TIME_L1_8
#endif /* #if( BSW_CANSM_CHNUM > 8U ) */
#if( BSW_CANSM_CHNUM > 9U )
   , (BswS2)BSW_CANSM_CFG_BOR_TIME_L1_9
#endif /* #if( BSW_CANSM_CHNUM > 9U ) */
#if( BSW_CANSM_CHNUM > 10U )
   , (BswS2)BSW_CANSM_CFG_BOR_TIME_L1_10
#endif /* #if( BSW_CANSM_CHNUM > 10U ) */
#if( BSW_CANSM_CHNUM > 11U )
   , (BswS2)BSW_CANSM_CFG_BOR_TIME_L1_11
#endif /* #if( BSW_CANSM_CHNUM > 11U ) */
#if( BSW_CANSM_CHNUM > 12U )
   , (BswS2)BSW_CANSM_CFG_BOR_TIME_L1_12
#endif /* #if( BSW_CANSM_CHNUM > 12U ) */
#if( BSW_CANSM_CHNUM > 13U )
   , (BswS2)BSW_CANSM_CFG_BOR_TIME_L1_13
#endif /* #if( BSW_CANSM_CHNUM > 13U ) */
#if( BSW_CANSM_CHNUM > 14U )
   , (BswS2)BSW_CANSM_CFG_BOR_TIME_L1_14
#endif /* #if( BSW_CANSM_CHNUM > 14U ) */
#if( BSW_CANSM_CHNUM > 15U )
   , (BswS2)BSW_CANSM_CFG_BOR_TIME_L1_15
#endif /* #if( BSW_CANSM_CHNUM > 15U ) */
#if( BSW_CANSM_CHNUM > 16U )
   , (BswS2)BSW_CANSM_CFG_BOR_TIME_L1_16
#endif /* #if( BSW_CANSM_CHNUM > 16U ) */
#if( BSW_CANSM_CHNUM > 17U )
   , (BswS2)BSW_CANSM_CFG_BOR_TIME_L1_17
#endif /* #if( BSW_CANSM_CHNUM > 17U ) */
#if( BSW_CANSM_CHNUM > 18U )
   , (BswS2)BSW_CANSM_CFG_BOR_TIME_L1_18
#endif /* #if( BSW_CANSM_CHNUM > 18U ) */
#if( BSW_CANSM_CHNUM > 19U )
   , (BswS2)BSW_CANSM_CFG_BOR_TIME_L1_19
#endif /* #if( BSW_CANSM_CHNUM > 19U ) */
#if( BSW_CANSM_CHNUM > 20U )
   , (BswS2)BSW_CANSM_CFG_BOR_TIME_L1_20
#endif /* #if( BSW_CANSM_CHNUM > 20U ) */
#if( BSW_CANSM_CHNUM > 21U )
   , (BswS2)BSW_CANSM_CFG_BOR_TIME_L1_21
#endif /* #if( BSW_CANSM_CHNUM > 21U ) */
#if( BSW_CANSM_CHNUM > 22U )
   , (BswS2)BSW_CANSM_CFG_BOR_TIME_L1_22
#endif /* #if( BSW_CANSM_CHNUM > 22U ) */
#if( BSW_CANSM_CHNUM > 23U )
   , (BswS2)BSW_CANSM_CFG_BOR_TIME_L1_23
#endif /* #if( BSW_CANSM_CHNUM > 23U ) */
#if( BSW_CANSM_CHNUM > 24U )
   , (BswS2)BSW_CANSM_CFG_BOR_TIME_L1_24
#endif /* #if( BSW_CANSM_CHNUM > 24U ) */
#if( BSW_CANSM_CHNUM > 25U )
   , (BswS2)BSW_CANSM_CFG_BOR_TIME_L1_25
#endif /* #if( BSW_CANSM_CHNUM > 25U ) */
#if( BSW_CANSM_CHNUM > 26U )
   , (BswS2)BSW_CANSM_CFG_BOR_TIME_L1_26
#endif /* #if( BSW_CANSM_CHNUM > 26U ) */
#if( BSW_CANSM_CHNUM > 27U )
   , (BswS2)BSW_CANSM_CFG_BOR_TIME_L1_27
#endif /* #if( BSW_CANSM_CHNUM > 27U ) */
#if( BSW_CANSM_CHNUM > 28U )
   , (BswS2)BSW_CANSM_CFG_BOR_TIME_L1_28
#endif /* #if( BSW_CANSM_CHNUM > 28U ) */
#if( BSW_CANSM_CHNUM > 29U )
   , (BswS2)BSW_CANSM_CFG_BOR_TIME_L1_29
#endif /* #if( BSW_CANSM_CHNUM > 29U ) */
#if( BSW_CANSM_CHNUM > 30U )
   , (BswS2)BSW_CANSM_CFG_BOR_TIME_L1_30
#endif /* #if( BSW_CANSM_CHNUM > 30U ) */
#if( BSW_CANSM_CHNUM > 31U )
   , (BswS2)BSW_CANSM_CFG_BOR_TIME_L1_31
#endif /* #if( BSW_CANSM_CHNUM > 31U ) */
};

/* Transmission start delay time table when transmission lock */
BswConst BswS2  bsw_cansm_fs_s2SndRockRestart[BSW_CANSM_CHNUM] = 
{
    (BswS2)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_CFG_SNDLCK_RESTART_0)
#if( BSW_CANSM_CHNUM > 1U )
   , (BswS2)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_CFG_SNDLCK_RESTART_1)
#endif /* #if( BSW_CANSM_CHNUM > 1U ) */
#if( BSW_CANSM_CHNUM > 2U )
   , (BswS2)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_CFG_SNDLCK_RESTART_2)
#endif /* #if( BSW_CANSM_CHNUM > 2U ) */
#if( BSW_CANSM_CHNUM > 3U )
   , (BswS2)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_CFG_SNDLCK_RESTART_3)
#endif /* #if( BSW_CANSM_CHNUM > 3U ) */
#if( BSW_CANSM_CHNUM > 4U )
   , (BswS2)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_CFG_SNDLCK_RESTART_4)
#endif /* #if( BSW_CANSM_CHNUM > 4U ) */
#if( BSW_CANSM_CHNUM > 5U )
   , (BswS2)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_CFG_SNDLCK_RESTART_5)
#endif /* #if( BSW_CANSM_CHNUM > 5U ) */
#if( BSW_CANSM_CHNUM > 6U )
   , (BswS2)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_CFG_SNDLCK_RESTART_6)
#endif /* #if( BSW_CANSM_CHNUM > 6U ) */
#if( BSW_CANSM_CHNUM > 7U )
   , (BswS2)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_CFG_SNDLCK_RESTART_7)
#endif /* #if( BSW_CANSM_CHNUM > 7U ) */
#if( BSW_CANSM_CHNUM > 8U )
   , (BswS2)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_CFG_SNDLCK_RESTART_8)
#endif /* #if( BSW_CANSM_CHNUM > 8U ) */
#if( BSW_CANSM_CHNUM > 9U )
   , (BswS2)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_CFG_SNDLCK_RESTART_9)
#endif /* #if( BSW_CANSM_CHNUM > 9U ) */
#if( BSW_CANSM_CHNUM > 10U )
   , (BswS2)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_CFG_SNDLCK_RESTART_10)
#endif /* #if( BSW_CANSM_CHNUM > 10U ) */
#if( BSW_CANSM_CHNUM > 11U )
   , (BswS2)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_CFG_SNDLCK_RESTART_11)
#endif /* #if( BSW_CANSM_CHNUM > 11U ) */
#if( BSW_CANSM_CHNUM > 12U )
   , (BswS2)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_CFG_SNDLCK_RESTART_12)
#endif /* #if( BSW_CANSM_CHNUM > 12U ) */
#if( BSW_CANSM_CHNUM > 13U )
   , (BswS2)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_CFG_SNDLCK_RESTART_13)
#endif /* #if( BSW_CANSM_CHNUM > 13U ) */
#if( BSW_CANSM_CHNUM > 14U )
   , (BswS2)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_CFG_SNDLCK_RESTART_14)
#endif /* #if( BSW_CANSM_CHNUM > 14U ) */
#if( BSW_CANSM_CHNUM > 15U )
   , (BswS2)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_CFG_SNDLCK_RESTART_15)
#endif /* #if( BSW_CANSM_CHNUM > 15U ) */
#if( BSW_CANSM_CHNUM > 16U )
   , (BswS2)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_CFG_SNDLCK_RESTART_16)
#endif /* #if( BSW_CANSM_CHNUM > 16U ) */
#if( BSW_CANSM_CHNUM > 17U )
   , (BswS2)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_CFG_SNDLCK_RESTART_17)
#endif /* #if( BSW_CANSM_CHNUM > 17U ) */
#if( BSW_CANSM_CHNUM > 18U )
   , (BswS2)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_CFG_SNDLCK_RESTART_18)
#endif /* #if( BSW_CANSM_CHNUM > 18U ) */
#if( BSW_CANSM_CHNUM > 19U )
   , (BswS2)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_CFG_SNDLCK_RESTART_19)
#endif /* #if( BSW_CANSM_CHNUM > 19U ) */
#if( BSW_CANSM_CHNUM > 20U )
   , (BswS2)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_CFG_SNDLCK_RESTART_20)
#endif /* #if( BSW_CANSM_CHNUM > 20U ) */
#if( BSW_CANSM_CHNUM > 21U )
   , (BswS2)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_CFG_SNDLCK_RESTART_21)
#endif /* #if( BSW_CANSM_CHNUM > 21U ) */
#if( BSW_CANSM_CHNUM > 22U )
   , (BswS2)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_CFG_SNDLCK_RESTART_22)
#endif /* #if( BSW_CANSM_CHNUM > 22U ) */
#if( BSW_CANSM_CHNUM > 23U )
   , (BswS2)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_CFG_SNDLCK_RESTART_23)
#endif /* #if( BSW_CANSM_CHNUM > 23U ) */
#if( BSW_CANSM_CHNUM > 24U )
   , (BswS2)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_CFG_SNDLCK_RESTART_24)
#endif /* #if( BSW_CANSM_CHNUM > 24U ) */
#if( BSW_CANSM_CHNUM > 25U )
   , (BswS2)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_CFG_SNDLCK_RESTART_25)
#endif /* #if( BSW_CANSM_CHNUM > 25U ) */
#if( BSW_CANSM_CHNUM > 26U )
   , (BswS2)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_CFG_SNDLCK_RESTART_26)
#endif /* #if( BSW_CANSM_CHNUM > 26U ) */
#if( BSW_CANSM_CHNUM > 27U )
   , (BswS2)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_CFG_SNDLCK_RESTART_27)
#endif /* #if( BSW_CANSM_CHNUM > 27U ) */
#if( BSW_CANSM_CHNUM > 28U )
   , (BswS2)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_CFG_SNDLCK_RESTART_28)
#endif /* #if( BSW_CANSM_CHNUM > 28U ) */
#if( BSW_CANSM_CHNUM > 29U )
   , (BswS2)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_CFG_SNDLCK_RESTART_29)
#endif /* #if( BSW_CANSM_CHNUM > 29U ) */
#if( BSW_CANSM_CHNUM > 30U )
   , (BswS2)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_CFG_SNDLCK_RESTART_30)
#endif /* #if( BSW_CANSM_CHNUM > 30U ) */
#if( BSW_CANSM_CHNUM > 31U )
   , (BswS2)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_CFG_SNDLCK_RESTART_31)
#endif /* #if( BSW_CANSM_CHNUM > 31U ) */
};

/* Controller Error Acquisition Function Table */
BswU1 (* BswConst bsw_cansm_fs_ptChkCtrlErrFunc[BSW_CANSM_CHNUM])( BswU1 u1ChId, BswU2 u2FailState ) =
{
    BSW_CANSM_CHKCTRLERR_FUNC(0)
#if( BSW_CANSM_CHNUM > 1U )
   , BSW_CANSM_CHKCTRLERR_FUNC(1)
#endif /* #if( BSW_CANSM_CHNUM > 1U ) */
#if( BSW_CANSM_CHNUM > 2U )
   , BSW_CANSM_CHKCTRLERR_FUNC(2)
#endif /* #if( BSW_CANSM_CHNUM > 2U ) */
#if( BSW_CANSM_CHNUM > 3U )
   , BSW_CANSM_CHKCTRLERR_FUNC(3)
#endif /* #if( BSW_CANSM_CHNUM > 3U ) */
#if( BSW_CANSM_CHNUM > 4U )
   , BSW_CANSM_CHKCTRLERR_FUNC(4)
#endif /* #if( BSW_CANSM_CHNUM > 4U ) */
#if( BSW_CANSM_CHNUM > 5U )
   , BSW_CANSM_CHKCTRLERR_FUNC(5)
#endif /* #if( BSW_CANSM_CHNUM > 5U ) */
#if( BSW_CANSM_CHNUM > 6U )
   , BSW_CANSM_CHKCTRLERR_FUNC(6)
#endif /* #if( BSW_CANSM_CHNUM > 6U ) */
#if( BSW_CANSM_CHNUM > 7U )
   , BSW_CANSM_CHKCTRLERR_FUNC(7)
#endif /* #if( BSW_CANSM_CHNUM > 7U ) */
#if( BSW_CANSM_CHNUM > 8U )
   , BSW_CANSM_CHKCTRLERR_FUNC(8)
#endif /* #if( BSW_CANSM_CHNUM > 8U ) */
#if( BSW_CANSM_CHNUM > 9U )
   , BSW_CANSM_CHKCTRLERR_FUNC(9)
#endif /* #if( BSW_CANSM_CHNUM > 9U ) */
#if( BSW_CANSM_CHNUM > 10U )
   , BSW_CANSM_CHKCTRLERR_FUNC(10)
#endif /* #if( BSW_CANSM_CHNUM > 10U ) */
#if( BSW_CANSM_CHNUM > 11U )
   , BSW_CANSM_CHKCTRLERR_FUNC(11)
#endif /* #if( BSW_CANSM_CHNUM > 11U ) */
#if( BSW_CANSM_CHNUM > 12U )
   , BSW_CANSM_CHKCTRLERR_FUNC(12)
#endif /* #if( BSW_CANSM_CHNUM > 12U ) */
#if( BSW_CANSM_CHNUM > 13U )
   , BSW_CANSM_CHKCTRLERR_FUNC(13)
#endif /* #if( BSW_CANSM_CHNUM > 13U ) */
#if( BSW_CANSM_CHNUM > 14U )
   , BSW_CANSM_CHKCTRLERR_FUNC(14)
#endif /* #if( BSW_CANSM_CHNUM > 14U ) */
#if( BSW_CANSM_CHNUM > 15U )
   , BSW_CANSM_CHKCTRLERR_FUNC(15)
#endif /* #if( BSW_CANSM_CHNUM > 15U ) */
#if( BSW_CANSM_CHNUM > 16U )
   , BSW_CANSM_CHKCTRLERR_FUNC(16)
#endif /* #if( BSW_CANSM_CHNUM > 16U ) */
#if( BSW_CANSM_CHNUM > 17U )
   , BSW_CANSM_CHKCTRLERR_FUNC(17)
#endif /* #if( BSW_CANSM_CHNUM > 17U ) */
#if( BSW_CANSM_CHNUM > 18U )
   , BSW_CANSM_CHKCTRLERR_FUNC(18)
#endif /* #if( BSW_CANSM_CHNUM > 18U ) */
#if( BSW_CANSM_CHNUM > 19U )
   , BSW_CANSM_CHKCTRLERR_FUNC(19)
#endif /* #if( BSW_CANSM_CHNUM > 19U ) */
#if( BSW_CANSM_CHNUM > 20U )
   , BSW_CANSM_CHKCTRLERR_FUNC(20)
#endif /* #if( BSW_CANSM_CHNUM > 20U ) */
#if( BSW_CANSM_CHNUM > 21U )
   , BSW_CANSM_CHKCTRLERR_FUNC(21)
#endif /* #if( BSW_CANSM_CHNUM > 21U ) */
#if( BSW_CANSM_CHNUM > 22U )
   , BSW_CANSM_CHKCTRLERR_FUNC(22)
#endif /* #if( BSW_CANSM_CHNUM > 22U ) */
#if( BSW_CANSM_CHNUM > 23U )
   , BSW_CANSM_CHKCTRLERR_FUNC(23)
#endif /* #if( BSW_CANSM_CHNUM > 23U ) */
#if( BSW_CANSM_CHNUM > 24U )
   , BSW_CANSM_CHKCTRLERR_FUNC(24)
#endif /* #if( BSW_CANSM_CHNUM > 24U ) */
#if( BSW_CANSM_CHNUM > 25U )
   , BSW_CANSM_CHKCTRLERR_FUNC(25)
#endif /* #if( BSW_CANSM_CHNUM > 25U ) */
#if( BSW_CANSM_CHNUM > 26U )
   , BSW_CANSM_CHKCTRLERR_FUNC(26)
#endif /* #if( BSW_CANSM_CHNUM > 26U ) */
#if( BSW_CANSM_CHNUM > 27U )
   , BSW_CANSM_CHKCTRLERR_FUNC(27)
#endif /* #if( BSW_CANSM_CHNUM > 27U ) */
#if( BSW_CANSM_CHNUM > 28U )
   , BSW_CANSM_CHKCTRLERR_FUNC(28)
#endif /* #if( BSW_CANSM_CHNUM > 28U ) */
#if( BSW_CANSM_CHNUM > 29U )
   , BSW_CANSM_CHKCTRLERR_FUNC(29)
#endif /* #if( BSW_CANSM_CHNUM > 29U ) */
#if( BSW_CANSM_CHNUM > 30U )
   , BSW_CANSM_CHKCTRLERR_FUNC(30)
#endif /* #if( BSW_CANSM_CHNUM > 30U ) */
#if( BSW_CANSM_CHNUM > 31U )
   , BSW_CANSM_CHKCTRLERR_FUNC(31)
#endif /* #if( BSW_CANSM_CHNUM > 31U ) */
};

/* Transceiver mode transition waiting time table */
BswConst BswU1  bsw_cansm_st_u1TrcvWaitTime[BSW_CANSM_CHNUM] = 
{
    (BswU1)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_TRCV_WAITTIME_0)
#if( BSW_CANSM_CHNUM > 1U )
   , (BswU1)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_TRCV_WAITTIME_1)
#endif /* #if( BSW_CANSM_CHNUM > 1U ) */
#if( BSW_CANSM_CHNUM > 2U )
   , (BswU1)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_TRCV_WAITTIME_2)
#endif /* #if( BSW_CANSM_CHNUM > 2U ) */
#if( BSW_CANSM_CHNUM > 3U )
   , (BswU1)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_TRCV_WAITTIME_3)
#endif /* #if( BSW_CANSM_CHNUM > 3U ) */
#if( BSW_CANSM_CHNUM > 4U )
   , (BswU1)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_TRCV_WAITTIME_4)
#endif /* #if( BSW_CANSM_CHNUM > 4U ) */
#if( BSW_CANSM_CHNUM > 5U )
   , (BswU1)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_TRCV_WAITTIME_5)
#endif /* #if( BSW_CANSM_CHNUM > 5U ) */
#if( BSW_CANSM_CHNUM > 6U )
   , (BswU1)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_TRCV_WAITTIME_6)
#endif /* #if( BSW_CANSM_CHNUM > 6U ) */
#if( BSW_CANSM_CHNUM > 7U )
   , (BswU1)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_TRCV_WAITTIME_7)
#endif /* #if( BSW_CANSM_CHNUM > 7U ) */
#if( BSW_CANSM_CHNUM > 8U )
   , (BswU1)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_TRCV_WAITTIME_8)
#endif /* #if( BSW_CANSM_CHNUM > 8U ) */
#if( BSW_CANSM_CHNUM > 9U )
   , (BswU1)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_TRCV_WAITTIME_9)
#endif /* #if( BSW_CANSM_CHNUM > 9U ) */
#if( BSW_CANSM_CHNUM > 10U )
   , (BswU1)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_TRCV_WAITTIME_10)
#endif /* #if( BSW_CANSM_CHNUM > 10U ) */
#if( BSW_CANSM_CHNUM > 11U )
   , (BswU1)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_TRCV_WAITTIME_11)
#endif /* #if( BSW_CANSM_CHNUM > 11U ) */
#if( BSW_CANSM_CHNUM > 12U )
   , (BswU1)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_TRCV_WAITTIME_12)
#endif /* #if( BSW_CANSM_CHNUM > 12U ) */
#if( BSW_CANSM_CHNUM > 13U )
   , (BswU1)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_TRCV_WAITTIME_13)
#endif /* #if( BSW_CANSM_CHNUM > 13U ) */
#if( BSW_CANSM_CHNUM > 14U )
   , (BswU1)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_TRCV_WAITTIME_14)
#endif /* #if( BSW_CANSM_CHNUM > 14U ) */
#if( BSW_CANSM_CHNUM > 15U )
   , (BswU1)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_TRCV_WAITTIME_15)
#endif /* #if( BSW_CANSM_CHNUM > 15U ) */
#if( BSW_CANSM_CHNUM > 16U )
   , (BswU1)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_TRCV_WAITTIME_16)
#endif /* #if( BSW_CANSM_CHNUM > 16U ) */
#if( BSW_CANSM_CHNUM > 17U )
   , (BswU1)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_TRCV_WAITTIME_17)
#endif /* #if( BSW_CANSM_CHNUM > 17U ) */
#if( BSW_CANSM_CHNUM > 18U )
   , (BswU1)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_TRCV_WAITTIME_18)
#endif /* #if( BSW_CANSM_CHNUM > 18U ) */
#if( BSW_CANSM_CHNUM > 19U )
   , (BswU1)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_TRCV_WAITTIME_19)
#endif /* #if( BSW_CANSM_CHNUM > 19U ) */
#if( BSW_CANSM_CHNUM > 20U )
   , (BswU1)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_TRCV_WAITTIME_20)
#endif /* #if( BSW_CANSM_CHNUM > 20U ) */
#if( BSW_CANSM_CHNUM > 21U )
   , (BswU1)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_TRCV_WAITTIME_21)
#endif /* #if( BSW_CANSM_CHNUM > 21U ) */
#if( BSW_CANSM_CHNUM > 22U )
   , (BswU1)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_TRCV_WAITTIME_22)
#endif /* #if( BSW_CANSM_CHNUM > 22U ) */
#if( BSW_CANSM_CHNUM > 23U )
   , (BswU1)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_TRCV_WAITTIME_23)
#endif /* #if( BSW_CANSM_CHNUM > 23U ) */
#if( BSW_CANSM_CHNUM > 24U )
   , (BswU1)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_TRCV_WAITTIME_24)
#endif /* #if( BSW_CANSM_CHNUM > 24U ) */
#if( BSW_CANSM_CHNUM > 25U )
   , (BswU1)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_TRCV_WAITTIME_25)
#endif /* #if( BSW_CANSM_CHNUM > 25U ) */
#if( BSW_CANSM_CHNUM > 26U )
   , (BswU1)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_TRCV_WAITTIME_26)
#endif /* #if( BSW_CANSM_CHNUM > 26U ) */
#if( BSW_CANSM_CHNUM > 27U )
   , (BswU1)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_TRCV_WAITTIME_27)
#endif /* #if( BSW_CANSM_CHNUM > 27U ) */
#if( BSW_CANSM_CHNUM > 28U )
   , (BswU1)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_TRCV_WAITTIME_28)
#endif /* #if( BSW_CANSM_CHNUM > 28U ) */
#if( BSW_CANSM_CHNUM > 29U )
   , (BswU1)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_TRCV_WAITTIME_29)
#endif /* #if( BSW_CANSM_CHNUM > 29U ) */
#if( BSW_CANSM_CHNUM > 30U )
   , (BswU1)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_TRCV_WAITTIME_30)
#endif /* #if( BSW_CANSM_CHNUM > 30U ) */
#if( BSW_CANSM_CHNUM > 31U )
   , (BswU1)BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANSM_TRCV_WAITTIME_31)
#endif /* #if( BSW_CANSM_CHNUM > 31U ) */
};

/* Maximum value of CANSM state transition waiting time */
BswConst BswU1  bsw_cansm_st_u1MaxWaitTime = BSW_CANSM_u1CHK_STATE_TIME;

/* CAN controller start wait table */
BswConst BswU1 bsw_cansm_fs_u1CtrlStartWait[BSW_CANSM_CHNUM] = 
{
     (BswU1)BSW_CANSM_CFG_CTRLSTART_WAIT_0
#if( BSW_CANSM_CHNUM > 1U )
   , (BswU1)BSW_CANSM_CFG_CTRLSTART_WAIT_1
#endif /* #if( BSW_CANSM_CHNUM > 1U ) */
#if( BSW_CANSM_CHNUM > 2U )
   , (BswU1)BSW_CANSM_CFG_CTRLSTART_WAIT_2
#endif /* #if( BSW_CANSM_CHNUM > 2U ) */
#if( BSW_CANSM_CHNUM > 3U )
   , (BswU1)BSW_CANSM_CFG_CTRLSTART_WAIT_3
#endif /* #if( BSW_CANSM_CHNUM > 3U ) */
#if( BSW_CANSM_CHNUM > 4U )
   , (BswU1)BSW_CANSM_CFG_CTRLSTART_WAIT_4
#endif /* #if( BSW_CANSM_CHNUM > 4U ) */
#if( BSW_CANSM_CHNUM > 5U )
   , (BswU1)BSW_CANSM_CFG_CTRLSTART_WAIT_5
#endif /* #if( BSW_CANSM_CHNUM > 5U ) */
#if( BSW_CANSM_CHNUM > 6U )
   , (BswU1)BSW_CANSM_CFG_CTRLSTART_WAIT_6
#endif /* #if( BSW_CANSM_CHNUM > 6U ) */
#if( BSW_CANSM_CHNUM > 7U )
   , (BswU1)BSW_CANSM_CFG_CTRLSTART_WAIT_7
#endif /* #if( BSW_CANSM_CHNUM > 7U ) */
#if( BSW_CANSM_CHNUM > 8U )
   , (BswU1)BSW_CANSM_CFG_CTRLSTART_WAIT_8
#endif /* #if( BSW_CANSM_CHNUM > 8U ) */
#if( BSW_CANSM_CHNUM > 9U )
   , (BswU1)BSW_CANSM_CFG_CTRLSTART_WAIT_9
#endif /* #if( BSW_CANSM_CHNUM > 9U ) */
#if( BSW_CANSM_CHNUM > 10U )
   , (BswU1)BSW_CANSM_CFG_CTRLSTART_WAIT_10
#endif /* #if( BSW_CANSM_CHNUM > 10U ) */
#if( BSW_CANSM_CHNUM > 11U )
   , (BswU1)BSW_CANSM_CFG_CTRLSTART_WAIT_11
#endif /* #if( BSW_CANSM_CHNUM > 11U ) */
#if( BSW_CANSM_CHNUM > 12U )
   , (BswU1)BSW_CANSM_CFG_CTRLSTART_WAIT_12
#endif /* #if( BSW_CANSM_CHNUM > 12U ) */
#if( BSW_CANSM_CHNUM > 13U )
   , (BswU1)BSW_CANSM_CFG_CTRLSTART_WAIT_13
#endif /* #if( BSW_CANSM_CHNUM > 13U ) */
#if( BSW_CANSM_CHNUM > 14U )
   , (BswU1)BSW_CANSM_CFG_CTRLSTART_WAIT_14
#endif /* #if( BSW_CANSM_CHNUM > 14U ) */
#if( BSW_CANSM_CHNUM > 15U )
   , (BswU1)BSW_CANSM_CFG_CTRLSTART_WAIT_15
#endif /* #if( BSW_CANSM_CHNUM > 15U ) */
#if( BSW_CANSM_CHNUM > 16U )
   , (BswU1)BSW_CANSM_CFG_CTRLSTART_WAIT_16
#endif /* #if( BSW_CANSM_CHNUM > 16U ) */
#if( BSW_CANSM_CHNUM > 17U )
   , (BswU1)BSW_CANSM_CFG_CTRLSTART_WAIT_17
#endif /* #if( BSW_CANSM_CHNUM > 17U ) */
#if( BSW_CANSM_CHNUM > 18U )
   , (BswU1)BSW_CANSM_CFG_CTRLSTART_WAIT_18
#endif /* #if( BSW_CANSM_CHNUM > 18U ) */
#if( BSW_CANSM_CHNUM > 19U )
   , (BswU1)BSW_CANSM_CFG_CTRLSTART_WAIT_19
#endif /* #if( BSW_CANSM_CHNUM > 19U ) */
#if( BSW_CANSM_CHNUM > 20U )
   , (BswU1)BSW_CANSM_CFG_CTRLSTART_WAIT_20
#endif /* #if( BSW_CANSM_CHNUM > 20U ) */
#if( BSW_CANSM_CHNUM > 21U )
   , (BswU1)BSW_CANSM_CFG_CTRLSTART_WAIT_21
#endif /* #if( BSW_CANSM_CHNUM > 21U ) */
#if( BSW_CANSM_CHNUM > 22U )
   , (BswU1)BSW_CANSM_CFG_CTRLSTART_WAIT_22
#endif /* #if( BSW_CANSM_CHNUM > 22U ) */
#if( BSW_CANSM_CHNUM > 23U )
   , (BswU1)BSW_CANSM_CFG_CTRLSTART_WAIT_23
#endif /* #if( BSW_CANSM_CHNUM > 23U ) */
#if( BSW_CANSM_CHNUM > 24U )
   , (BswU1)BSW_CANSM_CFG_CTRLSTART_WAIT_24
#endif /* #if( BSW_CANSM_CHNUM > 24U ) */
#if( BSW_CANSM_CHNUM > 25U )
   , (BswU1)BSW_CANSM_CFG_CTRLSTART_WAIT_25
#endif /* #if( BSW_CANSM_CHNUM > 25U ) */
#if( BSW_CANSM_CHNUM > 26U )
   , (BswU1)BSW_CANSM_CFG_CTRLSTART_WAIT_26
#endif /* #if( BSW_CANSM_CHNUM > 26U ) */
#if( BSW_CANSM_CHNUM > 27U )
   , (BswU1)BSW_CANSM_CFG_CTRLSTART_WAIT_27
#endif /* #if( BSW_CANSM_CHNUM > 27U ) */
#if( BSW_CANSM_CHNUM > 28U )
   , (BswU1)BSW_CANSM_CFG_CTRLSTART_WAIT_28
#endif /* #if( BSW_CANSM_CHNUM > 28U ) */
#if( BSW_CANSM_CHNUM > 29U )
   , (BswU1)BSW_CANSM_CFG_CTRLSTART_WAIT_29
#endif /* #if( BSW_CANSM_CHNUM > 29U ) */
#if( BSW_CANSM_CHNUM > 30U )
   , (BswU1)BSW_CANSM_CFG_CTRLSTART_WAIT_30
#endif /* #if( BSW_CANSM_CHNUM > 30U ) */
#if( BSW_CANSM_CHNUM > 31U )
   , (BswU1)BSW_CANSM_CFG_CTRLSTART_WAIT_31
#endif /* #if( BSW_CANSM_CHNUM > 31U ) */
};

/*------------------------------------------*/
/* Unit:Manage transmission/receiving log                 */
/*------------------------------------------*/
#if( BSW_CANSM_CFG_TXRX_INDSTATE == BSW_USE )
void (* BswConst bsw_cansm_trx_ptClrTRxIndStFunc)( void )  = &bsw_cansm_trx_ClrTRxIndSt;
void (* BswConst bsw_cansm_trx_ptUpdtTRxIndFunc)( void )   = &bsw_cansm_trx_UpdtTRxIndSt;
#else
void (* BswConst bsw_cansm_trx_ptClrTRxIndStFunc)( void )  = &bsw_cansm_trx_ClrTRxIndStNone;
void (* BswConst bsw_cansm_trx_ptUpdtTRxIndFunc)( void )   = &bsw_cansm_trx_UpdtTRxIndStNone;
#endif /* #if( BSW_CANSM_CFG_TXRX_INDSTATE == BSW_USE ) */

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#endif /* #if( BSW_BSWM_CS_FUNC_CANSM == BSW_USE ) */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/12/20                                             */
/*  v1-1-0          :2018/12/12                                             */
/*  v2-0-0          :2021/12/02                                             */
/*  v2-1-0          :2022/09/01                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
