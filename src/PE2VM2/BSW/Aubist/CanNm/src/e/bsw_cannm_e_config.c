/* bsw_cannm_e_config_c_v3-0-0                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANNM/E/CONFIG/CODE                                   */
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
#include "../../../CanNm/inc/bsw_cannm_config.h"
#if ( BSW_CANNM_NM_TYPE_USE_E == BSW_USE )

#include <nm/bsw_nm_cbk.h>

#include "../../../Nm/inc/bsw_nm_config.h"
#include "../../inc/e/bsw_cannm_e_config.h"
#include "../../cfg/e/CanNm_E_Cfg.h"
#include "../../inc/e/bsw_cannm_e_ctrl.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/*----------------------------*/
/* CTRL Unit               */
/*----------------------------*/
#define BSW_CANNM_E_CH_OFFSET                 ( BSW_COMM_BUS_TYPE_OFFSET(CAN) )

#define BSW_CANNM_E_USE(ch)                   ( (BSW_CANNM_NM_TYPE(ch) == BSW_CANNM_NMTYPE_E) ? BSW_USE : BSW_NOUSE )

#define BSW_CANNM_E_u1TASK_JITTER             ( (BswU1)1U )

#if (BSW_BSWM_CS_MSG_DELIVER == BSW_BSWM_CS_MSGDELIVER_HIGH)
#define BSW_CANNM_E_u2MS2COMTICK_RUP(msTime)    BSW_BSWM_CS_u2MS2TICK_RUP_HIGH(msTime)
#else
#define BSW_CANNM_E_u2MS2COMTICK_RUP(msTime)    BSW_BSWM_CS_u2MS2TICK_RUP_MID(msTime)
#endif

#define BSW_CANNM_E_SNDSLPTIME_SLV            ( 0U )  /* Slave Send_Sleep timer:There is no Send_Sleep timer in Slave, so it is not configurable and fixed to 0 */

#define BSW_CANNM_E_MAXTIME_NMSTATE           ( 4000U )

#define BSW_CANNM_E_RMSG_NMINDEX_CH0          ( 0U )
#define BSW_CANNM_E_RMSG_NMINDEX_CH1          ( BSW_CANNM_E_CFG_RMSG_NMNUM_CH0 )
#define BSW_CANNM_E_RMSG_NMINDEX_CH2          ( BSW_CANNM_E_CFG_RMSG_NMNUM_CH1 + BSW_CANNM_E_RMSG_NMINDEX_CH1 )
#define BSW_CANNM_E_RMSG_NMINDEX_CH3          ( BSW_CANNM_E_CFG_RMSG_NMNUM_CH2 + BSW_CANNM_E_RMSG_NMINDEX_CH2 )
#define BSW_CANNM_E_RMSG_NMINDEX_CH4          ( BSW_CANNM_E_CFG_RMSG_NMNUM_CH3 + BSW_CANNM_E_RMSG_NMINDEX_CH3 )
#define BSW_CANNM_E_RMSG_NMINDEX_CH5          ( BSW_CANNM_E_CFG_RMSG_NMNUM_CH4 + BSW_CANNM_E_RMSG_NMINDEX_CH4 )
#define BSW_CANNM_E_RMSG_NMINDEX_CH6          ( BSW_CANNM_E_CFG_RMSG_NMNUM_CH5 + BSW_CANNM_E_RMSG_NMINDEX_CH5 )
#define BSW_CANNM_E_RMSG_NMINDEX_CH7          ( BSW_CANNM_E_CFG_RMSG_NMNUM_CH6 + BSW_CANNM_E_RMSG_NMINDEX_CH6 )
#define BSW_CANNM_E_RMSG_NMINDEX_CH8          ( BSW_CANNM_E_CFG_RMSG_NMNUM_CH7 + BSW_CANNM_E_RMSG_NMINDEX_CH7 )
#define BSW_CANNM_E_RMSG_NMINDEX_CH9          ( BSW_CANNM_E_CFG_RMSG_NMNUM_CH8 + BSW_CANNM_E_RMSG_NMINDEX_CH8 )
#define BSW_CANNM_E_RMSG_NMINDEX_CH10         ( BSW_CANNM_E_CFG_RMSG_NMNUM_CH9 + BSW_CANNM_E_RMSG_NMINDEX_CH9 )
#define BSW_CANNM_E_RMSG_NMINDEX_CH11         ( BSW_CANNM_E_CFG_RMSG_NMNUM_CH10 + BSW_CANNM_E_RMSG_NMINDEX_CH10 )
#define BSW_CANNM_E_RMSG_NMINDEX_CH12         ( BSW_CANNM_E_CFG_RMSG_NMNUM_CH11 + BSW_CANNM_E_RMSG_NMINDEX_CH11 )
#define BSW_CANNM_E_RMSG_NMINDEX_CH13         ( BSW_CANNM_E_CFG_RMSG_NMNUM_CH12 + BSW_CANNM_E_RMSG_NMINDEX_CH12 )
#define BSW_CANNM_E_RMSG_NMINDEX_CH14         ( BSW_CANNM_E_CFG_RMSG_NMNUM_CH13 + BSW_CANNM_E_RMSG_NMINDEX_CH13 )
#define BSW_CANNM_E_RMSG_NMINDEX_CH15         ( BSW_CANNM_E_CFG_RMSG_NMNUM_CH14 + BSW_CANNM_E_RMSG_NMINDEX_CH14 )
#define BSW_CANNM_E_RMSG_NMINDEX_CH16         ( BSW_CANNM_E_CFG_RMSG_NMNUM_CH15 + BSW_CANNM_E_RMSG_NMINDEX_CH15 )
#define BSW_CANNM_E_RMSG_NMINDEX_CH17         ( BSW_CANNM_E_CFG_RMSG_NMNUM_CH16 + BSW_CANNM_E_RMSG_NMINDEX_CH16 )
#define BSW_CANNM_E_RMSG_NMINDEX_CH18         ( BSW_CANNM_E_CFG_RMSG_NMNUM_CH17 + BSW_CANNM_E_RMSG_NMINDEX_CH17 )
#define BSW_CANNM_E_RMSG_NMINDEX_CH19         ( BSW_CANNM_E_CFG_RMSG_NMNUM_CH18 + BSW_CANNM_E_RMSG_NMINDEX_CH18 )
#define BSW_CANNM_E_RMSG_NMINDEX_CH20         ( BSW_CANNM_E_CFG_RMSG_NMNUM_CH19 + BSW_CANNM_E_RMSG_NMINDEX_CH19 )
#define BSW_CANNM_E_RMSG_NMINDEX_CH21         ( BSW_CANNM_E_CFG_RMSG_NMNUM_CH20 + BSW_CANNM_E_RMSG_NMINDEX_CH20 )
#define BSW_CANNM_E_RMSG_NMINDEX_CH22         ( BSW_CANNM_E_CFG_RMSG_NMNUM_CH21 + BSW_CANNM_E_RMSG_NMINDEX_CH21 )
#define BSW_CANNM_E_RMSG_NMINDEX_CH23         ( BSW_CANNM_E_CFG_RMSG_NMNUM_CH22 + BSW_CANNM_E_RMSG_NMINDEX_CH22 )
#define BSW_CANNM_E_RMSG_NMINDEX_CH24         ( BSW_CANNM_E_CFG_RMSG_NMNUM_CH23 + BSW_CANNM_E_RMSG_NMINDEX_CH23 )
#define BSW_CANNM_E_RMSG_NMINDEX_CH25         ( BSW_CANNM_E_CFG_RMSG_NMNUM_CH24 + BSW_CANNM_E_RMSG_NMINDEX_CH24 )
#define BSW_CANNM_E_RMSG_NMINDEX_CH26         ( BSW_CANNM_E_CFG_RMSG_NMNUM_CH25 + BSW_CANNM_E_RMSG_NMINDEX_CH25 )
#define BSW_CANNM_E_RMSG_NMINDEX_CH27         ( BSW_CANNM_E_CFG_RMSG_NMNUM_CH26 + BSW_CANNM_E_RMSG_NMINDEX_CH26 )
#define BSW_CANNM_E_RMSG_NMINDEX_CH28         ( BSW_CANNM_E_CFG_RMSG_NMNUM_CH27 + BSW_CANNM_E_RMSG_NMINDEX_CH27 )
#define BSW_CANNM_E_RMSG_NMINDEX_CH29         ( BSW_CANNM_E_CFG_RMSG_NMNUM_CH28 + BSW_CANNM_E_RMSG_NMINDEX_CH28 )
#define BSW_CANNM_E_RMSG_NMINDEX_CH30         ( BSW_CANNM_E_CFG_RMSG_NMNUM_CH29 + BSW_CANNM_E_RMSG_NMINDEX_CH29 )
#define BSW_CANNM_E_RMSG_NMINDEX_CH31         ( BSW_CANNM_E_CFG_RMSG_NMNUM_CH30 + BSW_CANNM_E_RMSG_NMINDEX_CH30 )
#define BSW_CANNM_E_RMSG_NMINDEX_END          ( BSW_CANNM_E_CFG_RMSG_NMNUM_CH31 + BSW_CANNM_E_RMSG_NMINDEX_CH31 )

#define BSW_CANNM_E_NODE_MODEL(ch)            ( BSW_CANNM_E_CFG_CTRL_TYPE_CH##ch )
#define BSW_CANNM_E_u1NODE_TYPE(ch)           ( (BSW_CANNM_E_NODE_MODEL(ch) == BSW_CANNM_E_CONTROL_TYPE_MC) ? BSW_CANNM_E_u1TYPE_MASTER : BSW_CANNM_E_u1NODE_TYPE_0(ch) )
#define BSW_CANNM_E_u1NODE_TYPE_0(ch)         ( (BSW_CANNM_E_NODE_MODEL(ch) == BSW_CANNM_E_CONTROL_TYPE_MS) ? BSW_CANNM_E_u1TYPE_MASTER : BSW_CANNM_E_u1NODE_TYPE_1(ch) )
#define BSW_CANNM_E_u1NODE_TYPE_1(ch)         ( (BSW_CANNM_E_NODE_MODEL(ch) == BSW_CANNM_E_CONTROL_TYPE_SC) ? BSW_CANNM_E_u1TYPE_SLAVE  : BSW_CANNM_E_u1NODE_TYPE_2(ch) )
#define BSW_CANNM_E_u1NODE_TYPE_2(ch)         ( (BSW_CANNM_E_NODE_MODEL(ch) == BSW_CANNM_E_CONTROL_TYPE_SS) ? BSW_CANNM_E_u1TYPE_SLAVE  : BSW_CANNM_E_u1NODE_TYPE_3(ch) )
#define BSW_CANNM_E_u1NODE_TYPE_3(ch)         ( (BSW_CANNM_E_NODE_MODEL(ch) == BSW_CANNM_E_CONTROL_TYPE_SE) ? BSW_CANNM_E_u1TYPE_SLAVE  : BSW_CANNM_E_u1TYPE_SLAVE )

#define BSW_CANNM_E_u2WAKEUPTIME(ch)          ( (BswU2)((BSW_CANNM_E_u1NODE_TYPE(ch) == BSW_CANNM_E_u1TYPE_MASTER) ? BSW_CANNM_E_CFG_WAKEUPTIME_MST : BSW_CANNM_E_CFG_WAKEUPTIME_SLV) )
#define BSW_CANNM_E_u2APPTIME(ch)             ( BSW_BSWM_CS_u2MS2TICK_RUP_MID((BSW_CANNM_E_u1NODE_TYPE(ch) == BSW_CANNM_E_u1TYPE_MASTER) ? BSW_CANNM_E_CFG_APPTIME_MST : BSW_CANNM_E_CFG_APPTIME_SLV) )
#define BSW_CANNM_E_u2APPCOMTICK(ch)          ( BSW_CANNM_E_u2MS2COMTICK_RUP((BSW_CANNM_E_u1NODE_TYPE(ch) == BSW_CANNM_E_u1TYPE_MASTER) ? BSW_CANNM_E_CFG_APPTIME_MST : BSW_CANNM_E_CFG_APPTIME_SLV) )
#define BSW_CANNM_E_u2SLEEPTIME(ch)           ( BSW_BSWM_CS_u2MS2TICK_RUP_MID((BSW_CANNM_E_u1NODE_TYPE(ch) == BSW_CANNM_E_u1TYPE_MASTER) ? BSW_CANNM_E_CFG_SLEEPTIME_MST : BSW_CANNM_E_CFG_SLEEPTIME_SLV) )
#define BSW_CANNM_E_u2SNDSLPTIME(ch)          ( BSW_BSWM_CS_u2MS2TICK_RUP_MID((BSW_CANNM_E_u1NODE_TYPE(ch) == BSW_CANNM_E_u1TYPE_MASTER) ? BSW_CANNM_E_CFG_SNDSLPTIME_MST : BSW_CANNM_E_SNDSLPTIME_SLV) )
#define BSW_CANNM_E_u2RX_TIMEOUT(ch)          ( BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANNM_E_CFG_RX_TIMEOUT_CH##ch) + BSW_CANNM_E_u1TASK_JITTER )

#define BSW_CANNM_E_WKUPFLM_USE(ch)           ( (BSW_CANNM_E_NODE_MODEL(ch) == BSW_CANNM_E_CONTROL_TYPE_MC) ? BSW_USE : BSW_CANNM_E_WKUPFLM_USE_0(ch) )
#define BSW_CANNM_E_WKUPFLM_USE_0(ch)         ( (BSW_CANNM_E_NODE_MODEL(ch) == BSW_CANNM_E_CONTROL_TYPE_MS) ? BSW_USE : BSW_CANNM_E_WKUPFLM_USE_1(ch) )
#define BSW_CANNM_E_WKUPFLM_USE_1(ch)         ( (BSW_CANNM_E_NODE_MODEL(ch) == BSW_CANNM_E_CONTROL_TYPE_SC) ? BSW_USE : BSW_NOUSE )

#define BSW_CANNM_E_SENDWKUPFLMFN(ch)         ( (BSW_CANNM_E_WKUPFLM_USE(ch) == BSW_USE) ? &bsw_cannm_e_ctrl_SendWakeUpFrm : &bsw_cannm_e_ctrl_SndWkUpFrmNone )
#define BSW_CANNM_E_ABRTWKUPFLMFN(ch)         ( (BSW_CANNM_E_WKUPFLM_USE(ch) == BSW_USE) ? &bsw_cannm_e_ctrl_AbortWakeUpFrm : &bsw_cannm_e_ctrl_AbtWkUpFrmNone )

#define BSW_CANNM_E_MASTER_USE                ( BSW_CANNM_E_MASTER_USE_0 )
#define BSW_CANNM_E_MASTER_USE_0              ( (BSW_CANNM_E_u1NODE_TYPE(0) == BSW_CANNM_E_u1TYPE_MASTER) ? BSW_USE : BSW_CANNM_E_MASTER_USE_1 )
#define BSW_CANNM_E_MASTER_USE_1              ( (BSW_CANNM_E_u1NODE_TYPE(1) == BSW_CANNM_E_u1TYPE_MASTER) ? BSW_USE : BSW_CANNM_E_MASTER_USE_2 )
#define BSW_CANNM_E_MASTER_USE_2              ( (BSW_CANNM_E_u1NODE_TYPE(2) == BSW_CANNM_E_u1TYPE_MASTER) ? BSW_USE : BSW_CANNM_E_MASTER_USE_3 )
#define BSW_CANNM_E_MASTER_USE_3              ( (BSW_CANNM_E_u1NODE_TYPE(3) == BSW_CANNM_E_u1TYPE_MASTER) ? BSW_USE : BSW_CANNM_E_MASTER_USE_4 )
#define BSW_CANNM_E_MASTER_USE_4              ( (BSW_CANNM_E_u1NODE_TYPE(4) == BSW_CANNM_E_u1TYPE_MASTER) ? BSW_USE : BSW_CANNM_E_MASTER_USE_5 )
#define BSW_CANNM_E_MASTER_USE_5              ( (BSW_CANNM_E_u1NODE_TYPE(5) == BSW_CANNM_E_u1TYPE_MASTER) ? BSW_USE : BSW_CANNM_E_MASTER_USE_6 )
#define BSW_CANNM_E_MASTER_USE_6              ( (BSW_CANNM_E_u1NODE_TYPE(6) == BSW_CANNM_E_u1TYPE_MASTER) ? BSW_USE : BSW_CANNM_E_MASTER_USE_7 )
#define BSW_CANNM_E_MASTER_USE_7              ( (BSW_CANNM_E_u1NODE_TYPE(7) == BSW_CANNM_E_u1TYPE_MASTER) ? BSW_USE : BSW_CANNM_E_MASTER_USE_8 )
#define BSW_CANNM_E_MASTER_USE_8              ( (BSW_CANNM_E_u1NODE_TYPE(8) == BSW_CANNM_E_u1TYPE_MASTER) ? BSW_USE : BSW_CANNM_E_MASTER_USE_9 )
#define BSW_CANNM_E_MASTER_USE_9              ( (BSW_CANNM_E_u1NODE_TYPE(9) == BSW_CANNM_E_u1TYPE_MASTER) ? BSW_USE : BSW_CANNM_E_MASTER_USE_10 )
#define BSW_CANNM_E_MASTER_USE_10             ( (BSW_CANNM_E_u1NODE_TYPE(10) == BSW_CANNM_E_u1TYPE_MASTER) ? BSW_USE : BSW_CANNM_E_MASTER_USE_11 )
#define BSW_CANNM_E_MASTER_USE_11             ( (BSW_CANNM_E_u1NODE_TYPE(11) == BSW_CANNM_E_u1TYPE_MASTER) ? BSW_USE : BSW_CANNM_E_MASTER_USE_12 )
#define BSW_CANNM_E_MASTER_USE_12             ( (BSW_CANNM_E_u1NODE_TYPE(12) == BSW_CANNM_E_u1TYPE_MASTER) ? BSW_USE : BSW_CANNM_E_MASTER_USE_13 )
#define BSW_CANNM_E_MASTER_USE_13             ( (BSW_CANNM_E_u1NODE_TYPE(13) == BSW_CANNM_E_u1TYPE_MASTER) ? BSW_USE : BSW_CANNM_E_MASTER_USE_14 )
#define BSW_CANNM_E_MASTER_USE_14             ( (BSW_CANNM_E_u1NODE_TYPE(14) == BSW_CANNM_E_u1TYPE_MASTER) ? BSW_USE : BSW_CANNM_E_MASTER_USE_15 )
#define BSW_CANNM_E_MASTER_USE_15             ( (BSW_CANNM_E_u1NODE_TYPE(15) == BSW_CANNM_E_u1TYPE_MASTER) ? BSW_USE : BSW_CANNM_E_MASTER_USE_16 )
#define BSW_CANNM_E_MASTER_USE_16             ( (BSW_CANNM_E_u1NODE_TYPE(16) == BSW_CANNM_E_u1TYPE_MASTER) ? BSW_USE : BSW_CANNM_E_MASTER_USE_17 )
#define BSW_CANNM_E_MASTER_USE_17             ( (BSW_CANNM_E_u1NODE_TYPE(17) == BSW_CANNM_E_u1TYPE_MASTER) ? BSW_USE : BSW_CANNM_E_MASTER_USE_18 )
#define BSW_CANNM_E_MASTER_USE_18             ( (BSW_CANNM_E_u1NODE_TYPE(18) == BSW_CANNM_E_u1TYPE_MASTER) ? BSW_USE : BSW_CANNM_E_MASTER_USE_19 )
#define BSW_CANNM_E_MASTER_USE_19             ( (BSW_CANNM_E_u1NODE_TYPE(19) == BSW_CANNM_E_u1TYPE_MASTER) ? BSW_USE : BSW_CANNM_E_MASTER_USE_20 )
#define BSW_CANNM_E_MASTER_USE_20             ( (BSW_CANNM_E_u1NODE_TYPE(20) == BSW_CANNM_E_u1TYPE_MASTER) ? BSW_USE : BSW_CANNM_E_MASTER_USE_21 )
#define BSW_CANNM_E_MASTER_USE_21             ( (BSW_CANNM_E_u1NODE_TYPE(21) == BSW_CANNM_E_u1TYPE_MASTER) ? BSW_USE : BSW_CANNM_E_MASTER_USE_22 )
#define BSW_CANNM_E_MASTER_USE_22             ( (BSW_CANNM_E_u1NODE_TYPE(22) == BSW_CANNM_E_u1TYPE_MASTER) ? BSW_USE : BSW_CANNM_E_MASTER_USE_23 )
#define BSW_CANNM_E_MASTER_USE_23             ( (BSW_CANNM_E_u1NODE_TYPE(23) == BSW_CANNM_E_u1TYPE_MASTER) ? BSW_USE : BSW_CANNM_E_MASTER_USE_24 )
#define BSW_CANNM_E_MASTER_USE_24             ( (BSW_CANNM_E_u1NODE_TYPE(24) == BSW_CANNM_E_u1TYPE_MASTER) ? BSW_USE : BSW_CANNM_E_MASTER_USE_25 )
#define BSW_CANNM_E_MASTER_USE_25             ( (BSW_CANNM_E_u1NODE_TYPE(25) == BSW_CANNM_E_u1TYPE_MASTER) ? BSW_USE : BSW_CANNM_E_MASTER_USE_26 )
#define BSW_CANNM_E_MASTER_USE_26             ( (BSW_CANNM_E_u1NODE_TYPE(26) == BSW_CANNM_E_u1TYPE_MASTER) ? BSW_USE : BSW_CANNM_E_MASTER_USE_27 )
#define BSW_CANNM_E_MASTER_USE_27             ( (BSW_CANNM_E_u1NODE_TYPE(27) == BSW_CANNM_E_u1TYPE_MASTER) ? BSW_USE : BSW_CANNM_E_MASTER_USE_28 )
#define BSW_CANNM_E_MASTER_USE_28             ( (BSW_CANNM_E_u1NODE_TYPE(28) == BSW_CANNM_E_u1TYPE_MASTER) ? BSW_USE : BSW_CANNM_E_MASTER_USE_29 )
#define BSW_CANNM_E_MASTER_USE_29             ( (BSW_CANNM_E_u1NODE_TYPE(29) == BSW_CANNM_E_u1TYPE_MASTER) ? BSW_USE : BSW_CANNM_E_MASTER_USE_30 )
#define BSW_CANNM_E_MASTER_USE_30             ( (BSW_CANNM_E_u1NODE_TYPE(30) == BSW_CANNM_E_u1TYPE_MASTER) ? BSW_USE : BSW_CANNM_E_MASTER_USE_31 )
#define BSW_CANNM_E_MASTER_USE_31             ( (BSW_CANNM_E_u1NODE_TYPE(31) == BSW_CANNM_E_u1TYPE_MASTER) ? BSW_USE : BSW_NOUSE )

#define BSW_CANNM_E_READYSLEEPFN              ( (BSW_CANNM_E_MASTER_USE == BSW_USE) ? &bsw_cannm_e_ctrl_RdySlpMst : &bsw_cannm_e_ctrl_RdySlpMstNone )
#define BSW_CANNM_E_POWERONWAITFN             ( (BSW_CANNM_E_MASTER_USE == BSW_USE) ? &bsw_cannm_e_ctrl_POWaitMst : &bsw_cannm_e_ctrl_POWaitMstNone )
#define BSW_CANNM_E_PREPWAKEUPFFN             ( (BSW_CANNM_E_MASTER_USE == BSW_USE) ? &bsw_cannm_e_ctrl_PrpWkUpMst : &bsw_cannm_e_ctrl_PrpWkUpMstNone )
#define BSW_CANNM_E_NORMALOPEFN               ( (BSW_CANNM_E_MASTER_USE == BSW_USE) ? &bsw_cannm_e_ctrl_NrmlOpeMst : &bsw_cannm_e_ctrl_NrmlOpeMstNone )

#define BSW_CANNM_E_COM_CONTROL               ( BSW_NM_COM_CONTROL )
#define BSW_CANNM_E_COM_CTRLINIT_FUNC         ( (BSW_CANNM_E_COM_CONTROL == BSW_USE) ? &bsw_cannm_e_ctrl_InitComCtrl : &bsw_cannm_e_ctrl_InitComCtrlNn )
#define BSW_CANNM_E_COM_GETCOMSTS_FUNC        ( (BSW_CANNM_E_COM_CONTROL == BSW_USE) ? &bsw_cannm_e_ctrl_GetComCtrlSts : &bsw_cannm_e_ctrl_GetCmCtrlStsNn )

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
/*----------------------------*/
/* CTRL Unit               */
/*----------------------------*/
Bsw_CanNmE_ChStsType     bsw_cannm_e_ctrl_stChSts[BSW_CANNM_E_CHNUM];           /* State by channel                       */
Bsw_CanNmE_RxMsgStsType  bsw_cannm_e_ctrl_stRxMsgSts[BSW_CANNM_E_RX_MSG_NUM];   /* Receive state for each frame                   */

/* Exist/none of communication restriction request */
#if ( BSW_CANNM_E_COM_CONTROL == BSW_USE )
BswU1                   bsw_cannm_e_ctrl_u1ComCtrlReq[BSW_CANNM_E_CHNUM];
#endif

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
/*----------------------------*/
/* CTRL Unit               */
/*----------------------------*/
BswConst BswU1 bsw_cannm_e_ctrl_u1ChNum       = (BswU1)BSW_CANNM_E_CHNUM;                               /* Maximum number of channels */
BswConst BswU1 bsw_cannm_e_ctrl_u1ChOffset    = (BswU1)BSW_CANNM_E_CH_OFFSET;                           /* Channel offset */
BswConst BswU2 bsw_cannm_e_ctrl_u2PwOnWaitTim = BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANNM_E_CFG_PWON_WAIT);   /* CPU awake holding time at power-on */
BswConst BswU2 bsw_cannm_e_ctrl_u2NmStateTim  = BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANNM_E_MAXTIME_NMSTATE); /* NM state transition timer maximum value        */

/* Connection of prepare bus-sleep state processing functions */
void (* BswConst bsw_cannm_e_ctrl_ptProcRdySlpFn )( BswU1 u1NetID, BswU1 u1RxStatus ) = BSW_CANNM_E_READYSLEEPFN;

/* Connection of bus sleep state processing function at power-on */
void (* BswConst bsw_cannm_e_ctrl_ptProcPOWaitFn )( BswU1 u1NetID, BswU1 u1RxStatus ) = BSW_CANNM_E_POWERONWAITFN;

/* Connect the bus wake-up wait state processing function */
void (* BswConst bsw_cannm_e_ctrl_ptProcPrpWupFn )( BswU1 u1NetID, BswU1 u1RxStatus ) = BSW_CANNM_E_PREPWAKEUPFFN;

/* Connection of normal operation state processing function */
void (* BswConst bsw_cannm_e_ctrl_ptProcNmlOpeFn )( BswU1 u1NetID, BswU1 u1RxStatus ) = BSW_CANNM_E_NORMALOPEFN;

/* Switch the communication restriction function */
void    (* BswConst bsw_cannm_e_ctrl_ptInitComFunc)( void )             = BSW_CANNM_E_COM_CTRLINIT_FUNC;
BswU1   (* BswConst bsw_cannm_e_ctrl_ptGtCmCtStFunc)(  BswU1 u1NetID  ) = BSW_CANNM_E_COM_GETCOMSTS_FUNC;

/* Channel used/not used table */
BswConst BswU1 bsw_cannm_e_ctrl_u1Channel[BSW_CANNM_E_CHNUM] =
{
     (BswU1)BSW_CANNM_E_USE(0)
#if ( BSW_CANNM_E_CHNUM > 1U )
    ,(BswU1)BSW_CANNM_E_USE(1)
#endif /* ( BSW_CANNM_E_CHNUM > 1U ) */
#if ( BSW_CANNM_E_CHNUM > 2U )
    ,(BswU1)BSW_CANNM_E_USE(2)
#endif /* ( BSW_CANNM_E_CHNUM > 2U ) */
#if ( BSW_CANNM_E_CHNUM > 3U )
    ,(BswU1)BSW_CANNM_E_USE(3)
#endif /* ( BSW_CANNM_E_CHNUM > 3U ) */
#if ( BSW_CANNM_E_CHNUM > 4U )
    ,(BswU1)BSW_CANNM_E_USE(4)
#endif /* ( BSW_CANNM_E_CHNUM > 4U ) */
#if ( BSW_CANNM_E_CHNUM > 5U )
    ,(BswU1)BSW_CANNM_E_USE(5)
#endif /* ( BSW_CANNM_E_CHNUM > 5U ) */
#if ( BSW_CANNM_E_CHNUM > 6U )
    ,(BswU1)BSW_CANNM_E_USE(6)
#endif /* ( BSW_CANNM_E_CHNUM > 6U ) */
#if ( BSW_CANNM_E_CHNUM > 7U )
    ,(BswU1)BSW_CANNM_E_USE(7)
#endif /* ( BSW_CANNM_E_CHNUM > 7U ) */
#if ( BSW_CANNM_E_CHNUM > 8U )
    ,(BswU1)BSW_CANNM_E_USE(8)
#endif /* ( BSW_CANNM_E_CHNUM > 8U ) */
#if ( BSW_CANNM_E_CHNUM > 9U )
    ,(BswU1)BSW_CANNM_E_USE(9)
#endif /* ( BSW_CANNM_E_CHNUM > 9U ) */
#if ( BSW_CANNM_E_CHNUM > 10U )
    ,(BswU1)BSW_CANNM_E_USE(10)
#endif /* ( BSW_CANNM_E_CHNUM > 10U ) */
#if ( BSW_CANNM_E_CHNUM > 11U )
    ,(BswU1)BSW_CANNM_E_USE(11)
#endif /* ( BSW_CANNM_E_CHNUM > 11U ) */
#if ( BSW_CANNM_E_CHNUM > 12U )
    ,(BswU1)BSW_CANNM_E_USE(12)
#endif /* ( BSW_CANNM_E_CHNUM > 12U ) */
#if ( BSW_CANNM_E_CHNUM > 13U )
    ,(BswU1)BSW_CANNM_E_USE(13)
#endif /* ( BSW_CANNM_E_CHNUM > 13U ) */
#if ( BSW_CANNM_E_CHNUM > 14U )
    ,(BswU1)BSW_CANNM_E_USE(14)
#endif /* ( BSW_CANNM_E_CHNUM > 14U ) */
#if ( BSW_CANNM_E_CHNUM > 15U )
    ,(BswU1)BSW_CANNM_E_USE(15)
#endif /* ( BSW_CANNM_E_CHNUM > 15U ) */
#if ( BSW_CANNM_E_CHNUM > 16U )
    ,(BswU1)BSW_CANNM_E_USE(16)
#endif /* ( BSW_CANNM_E_CHNUM > 16U ) */
#if ( BSW_CANNM_E_CHNUM > 17U )
    ,(BswU1)BSW_CANNM_E_USE(17)
#endif /* ( BSW_CANNM_E_CHNUM > 17U ) */
#if ( BSW_CANNM_E_CHNUM > 18U )
    ,(BswU1)BSW_CANNM_E_USE(18)
#endif /* ( BSW_CANNM_E_CHNUM > 18U ) */
#if ( BSW_CANNM_E_CHNUM > 19U )
    ,(BswU1)BSW_CANNM_E_USE(19)
#endif /* ( BSW_CANNM_E_CHNUM > 19U ) */
#if ( BSW_CANNM_E_CHNUM > 20U )
    ,(BswU1)BSW_CANNM_E_USE(20)
#endif /* ( BSW_CANNM_E_CHNUM > 20U ) */
#if ( BSW_CANNM_E_CHNUM > 21U )
    ,(BswU1)BSW_CANNM_E_USE(21)
#endif /* ( BSW_CANNM_E_CHNUM > 21U ) */
#if ( BSW_CANNM_E_CHNUM > 22U )
    ,(BswU1)BSW_CANNM_E_USE(22)
#endif /* ( BSW_CANNM_E_CHNUM > 22U ) */
#if ( BSW_CANNM_E_CHNUM > 23U )
    ,(BswU1)BSW_CANNM_E_USE(23)
#endif /* ( BSW_CANNM_E_CHNUM > 23U ) */
#if ( BSW_CANNM_E_CHNUM > 24U )
    ,(BswU1)BSW_CANNM_E_USE(24)
#endif /* ( BSW_CANNM_E_CHNUM > 24U ) */
#if ( BSW_CANNM_E_CHNUM > 25U )
    ,(BswU1)BSW_CANNM_E_USE(25)
#endif /* ( BSW_CANNM_E_CHNUM > 25U ) */
#if ( BSW_CANNM_E_CHNUM > 26U )
    ,(BswU1)BSW_CANNM_E_USE(26)
#endif /* ( BSW_CANNM_E_CHNUM > 26U ) */
#if ( BSW_CANNM_E_CHNUM > 27U )
    ,(BswU1)BSW_CANNM_E_USE(27)
#endif /* ( BSW_CANNM_E_CHNUM > 27U ) */
#if ( BSW_CANNM_E_CHNUM > 28U )
    ,(BswU1)BSW_CANNM_E_USE(28)
#endif /* ( BSW_CANNM_E_CHNUM > 28U ) */
#if ( BSW_CANNM_E_CHNUM > 29U )
    ,(BswU1)BSW_CANNM_E_USE(29)
#endif /* ( BSW_CANNM_E_CHNUM > 29U ) */
#if ( BSW_CANNM_E_CHNUM > 30U )
    ,(BswU1)BSW_CANNM_E_USE(30)
#endif /* ( BSW_CANNM_E_CHNUM > 30U ) */
#if ( BSW_CANNM_E_CHNUM > 31U )
    ,(BswU1)BSW_CANNM_E_USE(31)
#endif /* ( BSW_CANNM_E_CHNUM > 31U ) */
};

/* Table to judge whether bus-sleep is used or not */
BswConst BswU1 bsw_cannm_e_ctrl_u1BusSleepTbl[BSW_CANNM_E_CHNUM] =
{
     (BswU1)BSW_CANNM_BUSSLEEP_USE(0U)
#if ( BSW_CANNM_E_CHNUM > 1U )
    ,(BswU1)BSW_CANNM_BUSSLEEP_USE(1U)
#endif /* ( BSW_CANNM_E_CHNUM > 1U ) */
#if ( BSW_CANNM_E_CHNUM > 2U )
    ,(BswU1)BSW_CANNM_BUSSLEEP_USE(2U)
#endif /* ( BSW_CANNM_E_CHNUM > 2U ) */
#if ( BSW_CANNM_E_CHNUM > 3U )
    ,(BswU1)BSW_CANNM_BUSSLEEP_USE(3U)
#endif /* ( BSW_CANNM_E_CHNUM > 3U ) */
#if ( BSW_CANNM_E_CHNUM > 4U )
    ,(BswU1)BSW_CANNM_BUSSLEEP_USE(4U)
#endif /* ( BSW_CANNM_E_CHNUM > 4U ) */
#if ( BSW_CANNM_E_CHNUM > 5U )
    ,(BswU1)BSW_CANNM_BUSSLEEP_USE(5U)
#endif /* ( BSW_CANNM_E_CHNUM > 5U ) */
#if ( BSW_CANNM_E_CHNUM > 6U )
    ,(BswU1)BSW_CANNM_BUSSLEEP_USE(6U)
#endif /* ( BSW_CANNM_E_CHNUM > 6U ) */
#if ( BSW_CANNM_E_CHNUM > 7U )
    ,(BswU1)BSW_CANNM_BUSSLEEP_USE(7U)
#endif /* ( BSW_CANNM_E_CHNUM > 7U ) */
#if ( BSW_CANNM_E_CHNUM > 8U )
    ,(BswU1)BSW_CANNM_BUSSLEEP_USE(8U)
#endif /* ( BSW_CANNM_E_CHNUM > 8U ) */
#if ( BSW_CANNM_E_CHNUM > 9U )
    ,(BswU1)BSW_CANNM_BUSSLEEP_USE(9U)
#endif /* ( BSW_CANNM_E_CHNUM > 9U ) */
#if ( BSW_CANNM_E_CHNUM > 10U )
    ,(BswU1)BSW_CANNM_BUSSLEEP_USE(10U)
#endif /* ( BSW_CANNM_E_CHNUM > 10U ) */
#if ( BSW_CANNM_E_CHNUM > 11U )
    ,(BswU1)BSW_CANNM_BUSSLEEP_USE(11U)
#endif /* ( BSW_CANNM_E_CHNUM > 11U ) */
#if ( BSW_CANNM_E_CHNUM > 12U )
    ,(BswU1)BSW_CANNM_BUSSLEEP_USE(12U)
#endif /* ( BSW_CANNM_E_CHNUM > 12U ) */
#if ( BSW_CANNM_E_CHNUM > 13U )
    ,(BswU1)BSW_CANNM_BUSSLEEP_USE(13U)
#endif /* ( BSW_CANNM_E_CHNUM > 13U ) */
#if ( BSW_CANNM_E_CHNUM > 14U )
    ,(BswU1)BSW_CANNM_BUSSLEEP_USE(14U)
#endif /* ( BSW_CANNM_E_CHNUM > 14U ) */
#if ( BSW_CANNM_E_CHNUM > 15U )
    ,(BswU1)BSW_CANNM_BUSSLEEP_USE(15U)
#endif /* ( BSW_CANNM_E_CHNUM > 15U ) */
#if ( BSW_CANNM_E_CHNUM > 16U )
    ,(BswU1)BSW_CANNM_BUSSLEEP_USE(16U)
#endif /* ( BSW_CANNM_E_CHNUM > 16U ) */
#if ( BSW_CANNM_E_CHNUM > 17U )
    ,(BswU1)BSW_CANNM_BUSSLEEP_USE(17U)
#endif /* ( BSW_CANNM_E_CHNUM > 17U ) */
#if ( BSW_CANNM_E_CHNUM > 18U )
    ,(BswU1)BSW_CANNM_BUSSLEEP_USE(18U)
#endif /* ( BSW_CANNM_E_CHNUM > 18U ) */
#if ( BSW_CANNM_E_CHNUM > 19U )
    ,(BswU1)BSW_CANNM_BUSSLEEP_USE(19U)
#endif /* ( BSW_CANNM_E_CHNUM > 19U ) */
#if ( BSW_CANNM_E_CHNUM > 20U )
    ,(BswU1)BSW_CANNM_BUSSLEEP_USE(20U)
#endif /* ( BSW_CANNM_E_CHNUM > 20U ) */
#if ( BSW_CANNM_E_CHNUM > 21U )
    ,(BswU1)BSW_CANNM_BUSSLEEP_USE(21U)
#endif /* ( BSW_CANNM_E_CHNUM > 21U ) */
#if ( BSW_CANNM_E_CHNUM > 22U )
    ,(BswU1)BSW_CANNM_BUSSLEEP_USE(22U)
#endif /* ( BSW_CANNM_E_CHNUM > 22U ) */
#if ( BSW_CANNM_E_CHNUM > 23U )
    ,(BswU1)BSW_CANNM_BUSSLEEP_USE(23U)
#endif /* ( BSW_CANNM_E_CHNUM > 23U ) */
#if ( BSW_CANNM_E_CHNUM > 24U )
    ,(BswU1)BSW_CANNM_BUSSLEEP_USE(24U)
#endif /* ( BSW_CANNM_E_CHNUM > 24U ) */
#if ( BSW_CANNM_E_CHNUM > 25U )
    ,(BswU1)BSW_CANNM_BUSSLEEP_USE(25U)
#endif /* ( BSW_CANNM_E_CHNUM > 25U ) */
#if ( BSW_CANNM_E_CHNUM > 26U )
    ,(BswU1)BSW_CANNM_BUSSLEEP_USE(26U)
#endif /* ( BSW_CANNM_E_CHNUM > 26U ) */
#if ( BSW_CANNM_E_CHNUM > 27U )
    ,(BswU1)BSW_CANNM_BUSSLEEP_USE(27U)
#endif /* ( BSW_CANNM_E_CHNUM > 27U ) */
#if ( BSW_CANNM_E_CHNUM > 28U )
    ,(BswU1)BSW_CANNM_BUSSLEEP_USE(28U)
#endif /* ( BSW_CANNM_E_CHNUM > 28U ) */
#if ( BSW_CANNM_E_CHNUM > 29U )
    ,(BswU1)BSW_CANNM_BUSSLEEP_USE(29U)
#endif /* ( BSW_CANNM_E_CHNUM > 29U ) */
#if ( BSW_CANNM_E_CHNUM > 30U )
    ,(BswU1)BSW_CANNM_BUSSLEEP_USE(30U)
#endif /* ( BSW_CANNM_E_CHNUM > 30U ) */
#if ( BSW_CANNM_E_CHNUM > 31U )
    ,(BswU1)BSW_CANNM_BUSSLEEP_USE(31U)
#endif /* ( BSW_CANNM_E_CHNUM > 31U ) */
};

/* Select master/slave */
BswConst BswU1 bsw_cannm_e_ctrl_u1CtrlTypeTbl[BSW_CANNM_E_CHNUM] =
{
     BSW_CANNM_E_u1NODE_TYPE(0)
#if( BSW_CANNM_E_CHNUM > 1U )
    ,BSW_CANNM_E_u1NODE_TYPE(1)
#endif /* ( BSW_CANNM_E_CHNUM > 1U ) */
#if( BSW_CANNM_E_CHNUM > 2U )
    ,BSW_CANNM_E_u1NODE_TYPE(2)
#endif /* ( BSW_CANNM_E_CHNUM > 2U ) */
#if( BSW_CANNM_E_CHNUM > 3U )
    ,BSW_CANNM_E_u1NODE_TYPE(3)
#endif /* ( BSW_CANNM_E_CHNUM > 3U ) */
#if( BSW_CANNM_E_CHNUM > 4U )
    ,BSW_CANNM_E_u1NODE_TYPE(4)
#endif /* ( BSW_CANNM_E_CHNUM > 4U ) */
#if( BSW_CANNM_E_CHNUM > 5U )
    ,BSW_CANNM_E_u1NODE_TYPE(5)
#endif /* ( BSW_CANNM_E_CHNUM > 5U ) */
#if( BSW_CANNM_E_CHNUM > 6U )
    ,BSW_CANNM_E_u1NODE_TYPE(6)
#endif /* ( BSW_CANNM_E_CHNUM > 6U ) */
#if( BSW_CANNM_E_CHNUM > 7U )
    ,BSW_CANNM_E_u1NODE_TYPE(7)
#endif /* ( BSW_CANNM_E_CHNUM > 7U ) */
#if( BSW_CANNM_E_CHNUM > 8U )
    ,BSW_CANNM_E_u1NODE_TYPE(8)
#endif /* ( BSW_CANNM_E_CHNUM > 8U ) */
#if( BSW_CANNM_E_CHNUM > 9U )
    ,BSW_CANNM_E_u1NODE_TYPE(9)
#endif /* ( BSW_CANNM_E_CHNUM > 9U ) */
#if( BSW_CANNM_E_CHNUM > 10U )
    ,BSW_CANNM_E_u1NODE_TYPE(10)
#endif /* ( BSW_CANNM_E_CHNUM > 10U ) */
#if( BSW_CANNM_E_CHNUM > 11U )
    ,BSW_CANNM_E_u1NODE_TYPE(11)
#endif /* ( BSW_CANNM_E_CHNUM > 11U ) */
#if( BSW_CANNM_E_CHNUM > 12U )
    ,BSW_CANNM_E_u1NODE_TYPE(12)
#endif /* ( BSW_CANNM_E_CHNUM > 12U ) */
#if( BSW_CANNM_E_CHNUM > 13U )
    ,BSW_CANNM_E_u1NODE_TYPE(13)
#endif /* ( BSW_CANNM_E_CHNUM > 13U ) */
#if( BSW_CANNM_E_CHNUM > 14U )
    ,BSW_CANNM_E_u1NODE_TYPE(14)
#endif /* ( BSW_CANNM_E_CHNUM > 14U ) */
#if( BSW_CANNM_E_CHNUM > 15U )
    ,BSW_CANNM_E_u1NODE_TYPE(15)
#endif /* ( BSW_CANNM_E_CHNUM > 15U ) */
#if ( BSW_CANNM_E_CHNUM > 16U )
    ,BSW_CANNM_E_u1NODE_TYPE(16)
#endif /* ( BSW_CANNM_E_CHNUM > 16U ) */
#if ( BSW_CANNM_E_CHNUM > 17U )
    ,BSW_CANNM_E_u1NODE_TYPE(17)
#endif /* ( BSW_CANNM_E_CHNUM > 17U ) */
#if ( BSW_CANNM_E_CHNUM > 18U )
    ,BSW_CANNM_E_u1NODE_TYPE(18)
#endif /* ( BSW_CANNM_E_CHNUM > 18U ) */
#if ( BSW_CANNM_E_CHNUM > 19U )
    ,BSW_CANNM_E_u1NODE_TYPE(19)
#endif /* ( BSW_CANNM_E_CHNUM > 19U ) */
#if ( BSW_CANNM_E_CHNUM > 20U )
    ,BSW_CANNM_E_u1NODE_TYPE(20)
#endif /* ( BSW_CANNM_E_CHNUM > 20U ) */
#if ( BSW_CANNM_E_CHNUM > 21U )
    ,BSW_CANNM_E_u1NODE_TYPE(21)
#endif /* ( BSW_CANNM_E_CHNUM > 21U ) */
#if ( BSW_CANNM_E_CHNUM > 22U )
    ,BSW_CANNM_E_u1NODE_TYPE(22)
#endif /* ( BSW_CANNM_E_CHNUM > 22U ) */
#if ( BSW_CANNM_E_CHNUM > 23U )
    ,BSW_CANNM_E_u1NODE_TYPE(23)
#endif /* ( BSW_CANNM_E_CHNUM > 23U ) */
#if ( BSW_CANNM_E_CHNUM > 24U )
    ,BSW_CANNM_E_u1NODE_TYPE(24)
#endif /* ( BSW_CANNM_E_CHNUM > 24U ) */
#if ( BSW_CANNM_E_CHNUM > 25U )
    ,BSW_CANNM_E_u1NODE_TYPE(25)
#endif /* ( BSW_CANNM_E_CHNUM > 25U ) */
#if ( BSW_CANNM_E_CHNUM > 26U )
    ,BSW_CANNM_E_u1NODE_TYPE(26)
#endif /* ( BSW_CANNM_E_CHNUM > 26U ) */
#if ( BSW_CANNM_E_CHNUM > 27U )
    ,BSW_CANNM_E_u1NODE_TYPE(27)
#endif /* ( BSW_CANNM_E_CHNUM > 27U ) */
#if ( BSW_CANNM_E_CHNUM > 28U )
    ,BSW_CANNM_E_u1NODE_TYPE(28)
#endif /* ( BSW_CANNM_E_CHNUM > 28U ) */
#if ( BSW_CANNM_E_CHNUM > 29U )
    ,BSW_CANNM_E_u1NODE_TYPE(29)
#endif /* ( BSW_CANNM_E_CHNUM > 29U ) */
#if ( BSW_CANNM_E_CHNUM > 30U )
    ,BSW_CANNM_E_u1NODE_TYPE(30)
#endif /* ( BSW_CANNM_E_CHNUM > 30U ) */
#if ( BSW_CANNM_E_CHNUM > 31U )
    ,BSW_CANNM_E_u1NODE_TYPE(31)
#endif /* ( BSW_CANNM_E_CHNUM > 31U ) */
};

/* Wake-up wait time */
BswConst BswU2 bsw_cannm_e_ctrl_u2WakeUpMsTim[BSW_CANNM_E_CHNUM] = 
{
     BSW_CANNM_E_u2WAKEUPTIME(0)
#if( BSW_CANNM_E_CHNUM > 1U )
    ,BSW_CANNM_E_u2WAKEUPTIME(1)
#endif /* ( BSW_CANNM_E_CHNUM > 1U ) */
#if( BSW_CANNM_E_CHNUM > 2U )
    ,BSW_CANNM_E_u2WAKEUPTIME(2)
#endif /* ( BSW_CANNM_E_CHNUM > 2U ) */
#if( BSW_CANNM_E_CHNUM > 3U )
    ,BSW_CANNM_E_u2WAKEUPTIME(3)
#endif /* ( BSW_CANNM_E_CHNUM > 3U ) */
#if( BSW_CANNM_E_CHNUM > 4U )
    ,BSW_CANNM_E_u2WAKEUPTIME(4)
#endif /* ( BSW_CANNM_E_CHNUM > 4U ) */
#if( BSW_CANNM_E_CHNUM > 5U )
    ,BSW_CANNM_E_u2WAKEUPTIME(5)
#endif /* ( BSW_CANNM_E_CHNUM > 5U ) */
#if( BSW_CANNM_E_CHNUM > 6U )
    ,BSW_CANNM_E_u2WAKEUPTIME(6)
#endif /* ( BSW_CANNM_E_CHNUM > 6U ) */
#if( BSW_CANNM_E_CHNUM > 7U )
    ,BSW_CANNM_E_u2WAKEUPTIME(7)
#endif /* ( BSW_CANNM_E_CHNUM > 7U ) */
#if( BSW_CANNM_E_CHNUM > 8U )
    ,BSW_CANNM_E_u2WAKEUPTIME(8)
#endif /* ( BSW_CANNM_E_CHNUM > 8U ) */
#if( BSW_CANNM_E_CHNUM > 9U )
    ,BSW_CANNM_E_u2WAKEUPTIME(9)
#endif /* ( BSW_CANNM_E_CHNUM > 9U ) */
#if( BSW_CANNM_E_CHNUM > 10U )
    ,BSW_CANNM_E_u2WAKEUPTIME(10)
#endif /* ( BSW_CANNM_E_CHNUM > 10U ) */
#if( BSW_CANNM_E_CHNUM > 11U )
    ,BSW_CANNM_E_u2WAKEUPTIME(11)
#endif /* ( BSW_CANNM_E_CHNUM > 11U ) */
#if( BSW_CANNM_E_CHNUM > 12U )
    ,BSW_CANNM_E_u2WAKEUPTIME(12)
#endif /* ( BSW_CANNM_E_CHNUM > 12U ) */
#if( BSW_CANNM_E_CHNUM > 13U )
    ,BSW_CANNM_E_u2WAKEUPTIME(13)
#endif /* ( BSW_CANNM_E_CHNUM > 13U ) */
#if( BSW_CANNM_E_CHNUM > 14U )
    ,BSW_CANNM_E_u2WAKEUPTIME(14)
#endif /* ( BSW_CANNM_E_CHNUM > 14U ) */
#if( BSW_CANNM_E_CHNUM > 15U )
    ,BSW_CANNM_E_u2WAKEUPTIME(15)
#endif /* ( BSW_CANNM_E_CHNUM > 15U ) */
#if( BSW_CANNM_E_CHNUM > 16U )
    ,BSW_CANNM_E_u2WAKEUPTIME(16)
#endif /* ( BSW_CANNM_E_CHNUM > 16U ) */
#if( BSW_CANNM_E_CHNUM > 17U )
    ,BSW_CANNM_E_u2WAKEUPTIME(17)
#endif /* ( BSW_CANNM_E_CHNUM > 17U ) */
#if( BSW_CANNM_E_CHNUM > 18U )
    ,BSW_CANNM_E_u2WAKEUPTIME(18)
#endif /* ( BSW_CANNM_E_CHNUM > 18U ) */
#if( BSW_CANNM_E_CHNUM > 19U )
    ,BSW_CANNM_E_u2WAKEUPTIME(19)
#endif /* ( BSW_CANNM_E_CHNUM > 19U ) */
#if( BSW_CANNM_E_CHNUM > 20U )
    ,BSW_CANNM_E_u2WAKEUPTIME(20)
#endif /* ( BSW_CANNM_E_CHNUM > 20U ) */
#if( BSW_CANNM_E_CHNUM > 21U )
    ,BSW_CANNM_E_u2WAKEUPTIME(21)
#endif /* ( BSW_CANNM_E_CHNUM > 21U ) */
#if( BSW_CANNM_E_CHNUM > 22U )
    ,BSW_CANNM_E_u2WAKEUPTIME(22)
#endif /* ( BSW_CANNM_E_CHNUM > 22U ) */
#if( BSW_CANNM_E_CHNUM > 23U )
    ,BSW_CANNM_E_u2WAKEUPTIME(23)
#endif /* ( BSW_CANNM_E_CHNUM > 23U ) */
#if( BSW_CANNM_E_CHNUM > 24U )
    ,BSW_CANNM_E_u2WAKEUPTIME(24)
#endif /* ( BSW_CANNM_E_CHNUM > 24U ) */
#if( BSW_CANNM_E_CHNUM > 25U )
    ,BSW_CANNM_E_u2WAKEUPTIME(25)
#endif /* ( BSW_CANNM_E_CHNUM > 25U ) */
#if( BSW_CANNM_E_CHNUM > 26U )
    ,BSW_CANNM_E_u2WAKEUPTIME(26)
#endif /* ( BSW_CANNM_E_CHNUM > 26U ) */
#if( BSW_CANNM_E_CHNUM > 27U )
    ,BSW_CANNM_E_u2WAKEUPTIME(27)
#endif /* ( BSW_CANNM_E_CHNUM > 27U ) */
#if( BSW_CANNM_E_CHNUM > 28U )
    ,BSW_CANNM_E_u2WAKEUPTIME(28)
#endif /* ( BSW_CANNM_E_CHNUM > 28U ) */
#if( BSW_CANNM_E_CHNUM > 29U )
    ,BSW_CANNM_E_u2WAKEUPTIME(29)
#endif /* ( BSW_CANNM_E_CHNUM > 29U ) */
#if( BSW_CANNM_E_CHNUM > 30U )
    ,BSW_CANNM_E_u2WAKEUPTIME(30)
#endif /* ( BSW_CANNM_E_CHNUM > 30U ) */
#if( BSW_CANNM_E_CHNUM > 31U )
    ,BSW_CANNM_E_u2WAKEUPTIME(31)
#endif /* ( BSW_CANNM_E_CHNUM > 31U ) */
};

/* Repeat message state maintenance period */
BswConst BswU2 bsw_cannm_e_ctrl_u2AppTim[BSW_CANNM_E_CHNUM] = 
{
     BSW_CANNM_E_u2APPTIME(0)
#if( BSW_CANNM_E_CHNUM > 1U )
    ,BSW_CANNM_E_u2APPTIME(1)
#endif /* ( BSW_CANNM_E_CHNUM > 1U ) */
#if( BSW_CANNM_E_CHNUM > 2U )
    ,BSW_CANNM_E_u2APPTIME(2)
#endif /* ( BSW_CANNM_E_CHNUM > 2U ) */
#if( BSW_CANNM_E_CHNUM > 3U )
    ,BSW_CANNM_E_u2APPTIME(3)
#endif /* ( BSW_CANNM_E_CHNUM > 3U ) */
#if( BSW_CANNM_E_CHNUM > 4U )
    ,BSW_CANNM_E_u2APPTIME(4)
#endif /* ( BSW_CANNM_E_CHNUM > 4U ) */
#if( BSW_CANNM_E_CHNUM > 5U )
    ,BSW_CANNM_E_u2APPTIME(5)
#endif /* ( BSW_CANNM_E_CHNUM > 5U ) */
#if( BSW_CANNM_E_CHNUM > 6U )
    ,BSW_CANNM_E_u2APPTIME(6)
#endif /* ( BSW_CANNM_E_CHNUM > 6U ) */
#if( BSW_CANNM_E_CHNUM > 7U )
    ,BSW_CANNM_E_u2APPTIME(7)
#endif /* ( BSW_CANNM_E_CHNUM > 7U ) */
#if( BSW_CANNM_E_CHNUM > 8U )
    ,BSW_CANNM_E_u2APPTIME(8)
#endif /* ( BSW_CANNM_E_CHNUM > 8U ) */
#if( BSW_CANNM_E_CHNUM > 9U )
    ,BSW_CANNM_E_u2APPTIME(9)
#endif /* ( BSW_CANNM_E_CHNUM > 9U ) */
#if( BSW_CANNM_E_CHNUM > 10U )
    ,BSW_CANNM_E_u2APPTIME(10)
#endif /* ( BSW_CANNM_E_CHNUM > 10U ) */
#if( BSW_CANNM_E_CHNUM > 11U )
    ,BSW_CANNM_E_u2APPTIME(11)
#endif /* ( BSW_CANNM_E_CHNUM > 11U ) */
#if( BSW_CANNM_E_CHNUM > 12U )
    ,BSW_CANNM_E_u2APPTIME(12)
#endif /* ( BSW_CANNM_E_CHNUM > 12U ) */
#if( BSW_CANNM_E_CHNUM > 13U )
    ,BSW_CANNM_E_u2APPTIME(13)
#endif /* ( BSW_CANNM_E_CHNUM > 13U ) */
#if( BSW_CANNM_E_CHNUM > 14U )
    ,BSW_CANNM_E_u2APPTIME(14)
#endif /* ( BSW_CANNM_E_CHNUM > 14U ) */
#if( BSW_CANNM_E_CHNUM > 15U )
    ,BSW_CANNM_E_u2APPTIME(15)
#endif /* ( BSW_CANNM_E_CHNUM > 15U ) */
#if( BSW_CANNM_E_CHNUM > 16U )
    ,BSW_CANNM_E_u2APPTIME(16)
#endif /* ( BSW_CANNM_E_CHNUM > 16U ) */
#if( BSW_CANNM_E_CHNUM > 17U )
    ,BSW_CANNM_E_u2APPTIME(17)
#endif /* ( BSW_CANNM_E_CHNUM > 17U ) */
#if( BSW_CANNM_E_CHNUM > 18U )
    ,BSW_CANNM_E_u2APPTIME(18)
#endif /* ( BSW_CANNM_E_CHNUM > 18U ) */
#if( BSW_CANNM_E_CHNUM > 19U )
    ,BSW_CANNM_E_u2APPTIME(19)
#endif /* ( BSW_CANNM_E_CHNUM > 19U ) */
#if( BSW_CANNM_E_CHNUM > 20U )
    ,BSW_CANNM_E_u2APPTIME(20)
#endif /* ( BSW_CANNM_E_CHNUM > 20U ) */
#if( BSW_CANNM_E_CHNUM > 21U )
    ,BSW_CANNM_E_u2APPTIME(21)
#endif /* ( BSW_CANNM_E_CHNUM > 21U ) */
#if( BSW_CANNM_E_CHNUM > 22U )
    ,BSW_CANNM_E_u2APPTIME(22)
#endif /* ( BSW_CANNM_E_CHNUM > 22U ) */
#if( BSW_CANNM_E_CHNUM > 23U )
    ,BSW_CANNM_E_u2APPTIME(23)
#endif /* ( BSW_CANNM_E_CHNUM > 23U ) */
#if( BSW_CANNM_E_CHNUM > 24U )
    ,BSW_CANNM_E_u2APPTIME(24)
#endif /* ( BSW_CANNM_E_CHNUM > 24U ) */
#if( BSW_CANNM_E_CHNUM > 25U )
    ,BSW_CANNM_E_u2APPTIME(25)
#endif /* ( BSW_CANNM_E_CHNUM > 25U ) */
#if( BSW_CANNM_E_CHNUM > 26U )
    ,BSW_CANNM_E_u2APPTIME(26)
#endif /* ( BSW_CANNM_E_CHNUM > 26U ) */
#if( BSW_CANNM_E_CHNUM > 27U )
    ,BSW_CANNM_E_u2APPTIME(27)
#endif /* ( BSW_CANNM_E_CHNUM > 27U ) */
#if( BSW_CANNM_E_CHNUM > 28U )
    ,BSW_CANNM_E_u2APPTIME(28)
#endif /* ( BSW_CANNM_E_CHNUM > 28U ) */
#if( BSW_CANNM_E_CHNUM > 29U )
    ,BSW_CANNM_E_u2APPTIME(29)
#endif /* ( BSW_CANNM_E_CHNUM > 29U ) */
#if( BSW_CANNM_E_CHNUM > 30U )
    ,BSW_CANNM_E_u2APPTIME(30)
#endif /* ( BSW_CANNM_E_CHNUM > 30U ) */
#if( BSW_CANNM_E_CHNUM > 31U )
    ,BSW_CANNM_E_u2APPTIME(31)
#endif /* ( BSW_CANNM_E_CHNUM > 31U ) */
};

/* Repeat message state maintenance period(Com tick) */
BswConst BswU2 bsw_cannm_e_ctrl_u2AppComTick[BSW_CANNM_E_CHNUM] = 
{
     BSW_CANNM_E_u2APPCOMTICK(0)
#if( BSW_CANNM_E_CHNUM > 1U )
    ,BSW_CANNM_E_u2APPCOMTICK(1)
#endif /* ( BSW_CANNM_E_CHNUM > 1U ) */
#if( BSW_CANNM_E_CHNUM > 2U )
    ,BSW_CANNM_E_u2APPCOMTICK(2)
#endif /* ( BSW_CANNM_E_CHNUM > 2U ) */
#if( BSW_CANNM_E_CHNUM > 3U )
    ,BSW_CANNM_E_u2APPCOMTICK(3)
#endif /* ( BSW_CANNM_E_CHNUM > 3U ) */
#if( BSW_CANNM_E_CHNUM > 4U )
    ,BSW_CANNM_E_u2APPCOMTICK(4)
#endif /* ( BSW_CANNM_E_CHNUM > 4U ) */
#if( BSW_CANNM_E_CHNUM > 5U )
    ,BSW_CANNM_E_u2APPCOMTICK(5)
#endif /* ( BSW_CANNM_E_CHNUM > 5U ) */
#if( BSW_CANNM_E_CHNUM > 6U )
    ,BSW_CANNM_E_u2APPCOMTICK(6)
#endif /* ( BSW_CANNM_E_CHNUM > 6U ) */
#if( BSW_CANNM_E_CHNUM > 7U )
    ,BSW_CANNM_E_u2APPCOMTICK(7)
#endif /* ( BSW_CANNM_E_CHNUM > 7U ) */
#if( BSW_CANNM_E_CHNUM > 8U )
    ,BSW_CANNM_E_u2APPCOMTICK(8)
#endif /* ( BSW_CANNM_E_CHNUM > 8U ) */
#if( BSW_CANNM_E_CHNUM > 9U )
    ,BSW_CANNM_E_u2APPCOMTICK(9)
#endif /* ( BSW_CANNM_E_CHNUM > 9U ) */
#if( BSW_CANNM_E_CHNUM > 10U )
    ,BSW_CANNM_E_u2APPCOMTICK(10)
#endif /* ( BSW_CANNM_E_CHNUM > 10U ) */
#if( BSW_CANNM_E_CHNUM > 11U )
    ,BSW_CANNM_E_u2APPCOMTICK(11)
#endif /* ( BSW_CANNM_E_CHNUM > 11U ) */
#if( BSW_CANNM_E_CHNUM > 12U )
    ,BSW_CANNM_E_u2APPCOMTICK(12)
#endif /* ( BSW_CANNM_E_CHNUM > 12U ) */
#if( BSW_CANNM_E_CHNUM > 13U )
    ,BSW_CANNM_E_u2APPCOMTICK(13)
#endif /* ( BSW_CANNM_E_CHNUM > 13U ) */
#if( BSW_CANNM_E_CHNUM > 14U )
    ,BSW_CANNM_E_u2APPCOMTICK(14)
#endif /* ( BSW_CANNM_E_CHNUM > 14U ) */
#if( BSW_CANNM_E_CHNUM > 15U )
    ,BSW_CANNM_E_u2APPCOMTICK(15)
#endif /* ( BSW_CANNM_E_CHNUM > 15U ) */
#if( BSW_CANNM_E_CHNUM > 16U )
    ,BSW_CANNM_E_u2APPCOMTICK(16)
#endif /* ( BSW_CANNM_E_CHNUM > 16U ) */
#if( BSW_CANNM_E_CHNUM > 17U )
    ,BSW_CANNM_E_u2APPCOMTICK(17)
#endif /* ( BSW_CANNM_E_CHNUM > 17U ) */
#if( BSW_CANNM_E_CHNUM > 18U )
    ,BSW_CANNM_E_u2APPCOMTICK(18)
#endif /* ( BSW_CANNM_E_CHNUM > 18U ) */
#if( BSW_CANNM_E_CHNUM > 19U )
    ,BSW_CANNM_E_u2APPCOMTICK(19)
#endif /* ( BSW_CANNM_E_CHNUM > 19U ) */
#if( BSW_CANNM_E_CHNUM > 20U )
    ,BSW_CANNM_E_u2APPCOMTICK(20)
#endif /* ( BSW_CANNM_E_CHNUM > 20U ) */
#if( BSW_CANNM_E_CHNUM > 21U )
    ,BSW_CANNM_E_u2APPCOMTICK(21)
#endif /* ( BSW_CANNM_E_CHNUM > 21U ) */
#if( BSW_CANNM_E_CHNUM > 22U )
    ,BSW_CANNM_E_u2APPCOMTICK(22)
#endif /* ( BSW_CANNM_E_CHNUM > 22U ) */
#if( BSW_CANNM_E_CHNUM > 23U )
    ,BSW_CANNM_E_u2APPCOMTICK(23)
#endif /* ( BSW_CANNM_E_CHNUM > 23U ) */
#if( BSW_CANNM_E_CHNUM > 24U )
    ,BSW_CANNM_E_u2APPCOMTICK(24)
#endif /* ( BSW_CANNM_E_CHNUM > 24U ) */
#if( BSW_CANNM_E_CHNUM > 25U )
    ,BSW_CANNM_E_u2APPCOMTICK(25)
#endif /* ( BSW_CANNM_E_CHNUM > 25U ) */
#if( BSW_CANNM_E_CHNUM > 26U )
    ,BSW_CANNM_E_u2APPCOMTICK(26)
#endif /* ( BSW_CANNM_E_CHNUM > 26U ) */
#if( BSW_CANNM_E_CHNUM > 27U )
    ,BSW_CANNM_E_u2APPCOMTICK(27)
#endif /* ( BSW_CANNM_E_CHNUM > 27U ) */
#if( BSW_CANNM_E_CHNUM > 28U )
    ,BSW_CANNM_E_u2APPCOMTICK(28)
#endif /* ( BSW_CANNM_E_CHNUM > 28U ) */
#if( BSW_CANNM_E_CHNUM > 29U )
    ,BSW_CANNM_E_u2APPCOMTICK(29)
#endif /* ( BSW_CANNM_E_CHNUM > 29U ) */
#if( BSW_CANNM_E_CHNUM > 30U )
    ,BSW_CANNM_E_u2APPCOMTICK(30)
#endif /* ( BSW_CANNM_E_CHNUM > 30U ) */
#if( BSW_CANNM_E_CHNUM > 31U )
    ,BSW_CANNM_E_u2APPCOMTICK(31)
#endif /* ( BSW_CANNM_E_CHNUM > 31U ) */
};

/* Sleep transition waiting time */
BswConst BswU2 bsw_cannm_e_ctrl_u2WaitSlpTim[BSW_CANNM_E_CHNUM] = 
{
     BSW_CANNM_E_u2SLEEPTIME(0)
#if( BSW_CANNM_E_CHNUM > 1U )
    ,BSW_CANNM_E_u2SLEEPTIME(1)
#endif /* ( BSW_CANNM_E_CHNUM > 1U ) */
#if( BSW_CANNM_E_CHNUM > 2U )
    ,BSW_CANNM_E_u2SLEEPTIME(2)
#endif /* ( BSW_CANNM_E_CHNUM > 2U ) */
#if( BSW_CANNM_E_CHNUM > 3U )
    ,BSW_CANNM_E_u2SLEEPTIME(3)
#endif /* ( BSW_CANNM_E_CHNUM > 3U ) */
#if( BSW_CANNM_E_CHNUM > 4U )
    ,BSW_CANNM_E_u2SLEEPTIME(4)
#endif /* ( BSW_CANNM_E_CHNUM > 4U ) */
#if( BSW_CANNM_E_CHNUM > 5U )
    ,BSW_CANNM_E_u2SLEEPTIME(5)
#endif /* ( BSW_CANNM_E_CHNUM > 5U ) */
#if( BSW_CANNM_E_CHNUM > 6U )
    ,BSW_CANNM_E_u2SLEEPTIME(6)
#endif /* ( BSW_CANNM_E_CHNUM > 6U ) */
#if( BSW_CANNM_E_CHNUM > 7U )
    ,BSW_CANNM_E_u2SLEEPTIME(7)
#endif /* ( BSW_CANNM_E_CHNUM > 7U ) */
#if( BSW_CANNM_E_CHNUM > 8U )
    ,BSW_CANNM_E_u2SLEEPTIME(8)
#endif /* ( BSW_CANNM_E_CHNUM > 8U ) */
#if( BSW_CANNM_E_CHNUM > 9U )
    ,BSW_CANNM_E_u2SLEEPTIME(9)
#endif /* ( BSW_CANNM_E_CHNUM > 9U ) */
#if( BSW_CANNM_E_CHNUM > 10U )
    ,BSW_CANNM_E_u2SLEEPTIME(10)
#endif /* ( BSW_CANNM_E_CHNUM > 10U ) */
#if( BSW_CANNM_E_CHNUM > 11U )
    ,BSW_CANNM_E_u2SLEEPTIME(11)
#endif /* ( BSW_CANNM_E_CHNUM > 11U ) */
#if( BSW_CANNM_E_CHNUM > 12U )
    ,BSW_CANNM_E_u2SLEEPTIME(12)
#endif /* ( BSW_CANNM_E_CHNUM > 12U ) */
#if( BSW_CANNM_E_CHNUM > 13U )
    ,BSW_CANNM_E_u2SLEEPTIME(13)
#endif /* ( BSW_CANNM_E_CHNUM > 13U ) */
#if( BSW_CANNM_E_CHNUM > 14U )
    ,BSW_CANNM_E_u2SLEEPTIME(14)
#endif /* ( BSW_CANNM_E_CHNUM > 14U ) */
#if( BSW_CANNM_E_CHNUM > 15U )
    ,BSW_CANNM_E_u2SLEEPTIME(15)
#endif /* ( BSW_CANNM_E_CHNUM > 15U ) */
#if( BSW_CANNM_E_CHNUM > 16U )
    ,BSW_CANNM_E_u2SLEEPTIME(16)
#endif /* ( BSW_CANNM_E_CHNUM > 16U ) */
#if( BSW_CANNM_E_CHNUM > 17U )
    ,BSW_CANNM_E_u2SLEEPTIME(17)
#endif /* ( BSW_CANNM_E_CHNUM > 17U ) */
#if( BSW_CANNM_E_CHNUM > 18U )
    ,BSW_CANNM_E_u2SLEEPTIME(18)
#endif /* ( BSW_CANNM_E_CHNUM > 18U ) */
#if( BSW_CANNM_E_CHNUM > 19U )
    ,BSW_CANNM_E_u2SLEEPTIME(19)
#endif /* ( BSW_CANNM_E_CHNUM > 19U ) */
#if( BSW_CANNM_E_CHNUM > 20U )
    ,BSW_CANNM_E_u2SLEEPTIME(20)
#endif /* ( BSW_CANNM_E_CHNUM > 20U ) */
#if( BSW_CANNM_E_CHNUM > 21U )
    ,BSW_CANNM_E_u2SLEEPTIME(21)
#endif /* ( BSW_CANNM_E_CHNUM > 21U ) */
#if( BSW_CANNM_E_CHNUM > 22U )
    ,BSW_CANNM_E_u2SLEEPTIME(22)
#endif /* ( BSW_CANNM_E_CHNUM > 22U ) */
#if( BSW_CANNM_E_CHNUM > 23U )
    ,BSW_CANNM_E_u2SLEEPTIME(23)
#endif /* ( BSW_CANNM_E_CHNUM > 23U ) */
#if( BSW_CANNM_E_CHNUM > 24U )
    ,BSW_CANNM_E_u2SLEEPTIME(24)
#endif /* ( BSW_CANNM_E_CHNUM > 24U ) */
#if( BSW_CANNM_E_CHNUM > 25U )
    ,BSW_CANNM_E_u2SLEEPTIME(25)
#endif /* ( BSW_CANNM_E_CHNUM > 25U ) */
#if( BSW_CANNM_E_CHNUM > 26U )
    ,BSW_CANNM_E_u2SLEEPTIME(26)
#endif /* ( BSW_CANNM_E_CHNUM > 26U ) */
#if( BSW_CANNM_E_CHNUM > 27U )
    ,BSW_CANNM_E_u2SLEEPTIME(27)
#endif /* ( BSW_CANNM_E_CHNUM > 27U ) */
#if( BSW_CANNM_E_CHNUM > 28U )
    ,BSW_CANNM_E_u2SLEEPTIME(28)
#endif /* ( BSW_CANNM_E_CHNUM > 28U ) */
#if( BSW_CANNM_E_CHNUM > 29U )
    ,BSW_CANNM_E_u2SLEEPTIME(29)
#endif /* ( BSW_CANNM_E_CHNUM > 29U ) */
#if( BSW_CANNM_E_CHNUM > 30U )
    ,BSW_CANNM_E_u2SLEEPTIME(30)
#endif /* ( BSW_CANNM_E_CHNUM > 30U ) */
#if( BSW_CANNM_E_CHNUM > 31U )
    ,BSW_CANNM_E_u2SLEEPTIME(31)
#endif /* ( BSW_CANNM_E_CHNUM > 31U ) */
};

/* Transmission stop wait time during bus sleep transition */
BswConst BswU2 bsw_cannm_e_ctrl_u2SndSlpTim[BSW_CANNM_E_CHNUM] = 
{
     BSW_CANNM_E_u2SNDSLPTIME(0)
#if( BSW_CANNM_E_CHNUM > 1U )
    ,BSW_CANNM_E_u2SNDSLPTIME(1)
#endif /* ( BSW_CANNM_E_CHNUM > 1U ) */
#if( BSW_CANNM_E_CHNUM > 2U )
    ,BSW_CANNM_E_u2SNDSLPTIME(2)
#endif /* ( BSW_CANNM_E_CHNUM > 2U ) */
#if( BSW_CANNM_E_CHNUM > 3U )
    ,BSW_CANNM_E_u2SNDSLPTIME(3)
#endif /* ( BSW_CANNM_E_CHNUM > 3U ) */
#if( BSW_CANNM_E_CHNUM > 4U )
    ,BSW_CANNM_E_u2SNDSLPTIME(4)
#endif /* ( BSW_CANNM_E_CHNUM > 4U ) */
#if( BSW_CANNM_E_CHNUM > 5U )
    ,BSW_CANNM_E_u2SNDSLPTIME(5)
#endif /* ( BSW_CANNM_E_CHNUM > 5U ) */
#if( BSW_CANNM_E_CHNUM > 6U )
    ,BSW_CANNM_E_u2SNDSLPTIME(6)
#endif /* ( BSW_CANNM_E_CHNUM > 6U ) */
#if( BSW_CANNM_E_CHNUM > 7U )
    ,BSW_CANNM_E_u2SNDSLPTIME(7)
#endif /* ( BSW_CANNM_E_CHNUM > 7U ) */
#if( BSW_CANNM_E_CHNUM > 8U )
    ,BSW_CANNM_E_u2SNDSLPTIME(8)
#endif /* ( BSW_CANNM_E_CHNUM > 8U ) */
#if( BSW_CANNM_E_CHNUM > 9U )
    ,BSW_CANNM_E_u2SNDSLPTIME(9)
#endif /* ( BSW_CANNM_E_CHNUM > 9U ) */
#if( BSW_CANNM_E_CHNUM > 10U )
    ,BSW_CANNM_E_u2SNDSLPTIME(10)
#endif /* ( BSW_CANNM_E_CHNUM > 10U ) */
#if( BSW_CANNM_E_CHNUM > 11U )
    ,BSW_CANNM_E_u2SNDSLPTIME(11)
#endif /* ( BSW_CANNM_E_CHNUM > 11U ) */
#if( BSW_CANNM_E_CHNUM > 12U )
    ,BSW_CANNM_E_u2SNDSLPTIME(12)
#endif /* ( BSW_CANNM_E_CHNUM > 12U ) */
#if( BSW_CANNM_E_CHNUM > 13U )
    ,BSW_CANNM_E_u2SNDSLPTIME(13)
#endif /* ( BSW_CANNM_E_CHNUM > 13U ) */
#if( BSW_CANNM_E_CHNUM > 14U )
    ,BSW_CANNM_E_u2SNDSLPTIME(14)
#endif /* ( BSW_CANNM_E_CHNUM > 14U ) */
#if( BSW_CANNM_E_CHNUM > 15U )
    ,BSW_CANNM_E_u2SNDSLPTIME(15)
#endif /* ( BSW_CANNM_E_CHNUM > 15U ) */
#if( BSW_CANNM_E_CHNUM > 16U )
    ,BSW_CANNM_E_u2SNDSLPTIME(16)
#endif /* ( BSW_CANNM_E_CHNUM > 16U ) */
#if( BSW_CANNM_E_CHNUM > 17U )
    ,BSW_CANNM_E_u2SNDSLPTIME(17)
#endif /* ( BSW_CANNM_E_CHNUM > 17U ) */
#if( BSW_CANNM_E_CHNUM > 18U )
    ,BSW_CANNM_E_u2SNDSLPTIME(18)
#endif /* ( BSW_CANNM_E_CHNUM > 18U ) */
#if( BSW_CANNM_E_CHNUM > 19U )
    ,BSW_CANNM_E_u2SNDSLPTIME(19)
#endif /* ( BSW_CANNM_E_CHNUM > 19U ) */
#if( BSW_CANNM_E_CHNUM > 20U )
    ,BSW_CANNM_E_u2SNDSLPTIME(20)
#endif /* ( BSW_CANNM_E_CHNUM > 20U ) */
#if( BSW_CANNM_E_CHNUM > 21U )
    ,BSW_CANNM_E_u2SNDSLPTIME(21)
#endif /* ( BSW_CANNM_E_CHNUM > 21U ) */
#if( BSW_CANNM_E_CHNUM > 22U )
    ,BSW_CANNM_E_u2SNDSLPTIME(22)
#endif /* ( BSW_CANNM_E_CHNUM > 22U ) */
#if( BSW_CANNM_E_CHNUM > 23U )
    ,BSW_CANNM_E_u2SNDSLPTIME(23)
#endif /* ( BSW_CANNM_E_CHNUM > 23U ) */
#if( BSW_CANNM_E_CHNUM > 24U )
    ,BSW_CANNM_E_u2SNDSLPTIME(24)
#endif /* ( BSW_CANNM_E_CHNUM > 24U ) */
#if( BSW_CANNM_E_CHNUM > 25U )
    ,BSW_CANNM_E_u2SNDSLPTIME(25)
#endif /* ( BSW_CANNM_E_CHNUM > 25U ) */
#if( BSW_CANNM_E_CHNUM > 26U )
    ,BSW_CANNM_E_u2SNDSLPTIME(26)
#endif /* ( BSW_CANNM_E_CHNUM > 26U ) */
#if( BSW_CANNM_E_CHNUM > 27U )
    ,BSW_CANNM_E_u2SNDSLPTIME(27)
#endif /* ( BSW_CANNM_E_CHNUM > 27U ) */
#if( BSW_CANNM_E_CHNUM > 28U )
    ,BSW_CANNM_E_u2SNDSLPTIME(28)
#endif /* ( BSW_CANNM_E_CHNUM > 28U ) */
#if( BSW_CANNM_E_CHNUM > 29U )
    ,BSW_CANNM_E_u2SNDSLPTIME(29)
#endif /* ( BSW_CANNM_E_CHNUM > 29U ) */
#if( BSW_CANNM_E_CHNUM > 30U )
    ,BSW_CANNM_E_u2SNDSLPTIME(30)
#endif /* ( BSW_CANNM_E_CHNUM > 30U ) */
#if( BSW_CANNM_E_CHNUM > 31U )
    ,BSW_CANNM_E_u2SNDSLPTIME(31)
#endif /* ( BSW_CANNM_E_CHNUM > 31U ) */
};

/* NM frame receiving monitoring time (To set it before the timer count of the same period, jitter is given.) */
BswConst BswU2 bsw_cannm_e_ctrl_u2RxTimeOut[BSW_CANNM_E_CHNUM] = 
{
     BSW_CANNM_E_u2RX_TIMEOUT(0)
#if( BSW_CANNM_E_CHNUM > 1U )
    ,BSW_CANNM_E_u2RX_TIMEOUT(1)
#endif /* ( BSW_CANNM_E_CHNUM > 1U ) */
#if( BSW_CANNM_E_CHNUM > 2U )
    ,BSW_CANNM_E_u2RX_TIMEOUT(2)
#endif /* ( BSW_CANNM_E_CHNUM > 2U ) */
#if( BSW_CANNM_E_CHNUM > 3U )
    ,BSW_CANNM_E_u2RX_TIMEOUT(3)
#endif /* ( BSW_CANNM_E_CHNUM > 3U ) */
#if( BSW_CANNM_E_CHNUM > 4U )
    ,BSW_CANNM_E_u2RX_TIMEOUT(4)
#endif /* ( BSW_CANNM_E_CHNUM > 4U ) */
#if( BSW_CANNM_E_CHNUM > 5U )
    ,BSW_CANNM_E_u2RX_TIMEOUT(5)
#endif /* ( BSW_CANNM_E_CHNUM > 5U ) */
#if( BSW_CANNM_E_CHNUM > 6U )
    ,BSW_CANNM_E_u2RX_TIMEOUT(6)
#endif /* ( BSW_CANNM_E_CHNUM > 6U ) */
#if( BSW_CANNM_E_CHNUM > 7U )
    ,BSW_CANNM_E_u2RX_TIMEOUT(7)
#endif /* ( BSW_CANNM_E_CHNUM > 7U ) */
#if( BSW_CANNM_E_CHNUM > 8U )
    ,BSW_CANNM_E_u2RX_TIMEOUT(8)
#endif /* ( BSW_CANNM_E_CHNUM > 8U ) */
#if( BSW_CANNM_E_CHNUM > 9U )
    ,BSW_CANNM_E_u2RX_TIMEOUT(9)
#endif /* ( BSW_CANNM_E_CHNUM > 9U ) */
#if( BSW_CANNM_E_CHNUM > 10U )
    ,BSW_CANNM_E_u2RX_TIMEOUT(10)
#endif /* ( BSW_CANNM_E_CHNUM > 10U ) */
#if( BSW_CANNM_E_CHNUM > 11U )
    ,BSW_CANNM_E_u2RX_TIMEOUT(11)
#endif /* ( BSW_CANNM_E_CHNUM > 11U ) */
#if( BSW_CANNM_E_CHNUM > 12U )
    ,BSW_CANNM_E_u2RX_TIMEOUT(12)
#endif /* ( BSW_CANNM_E_CHNUM > 12U ) */
#if( BSW_CANNM_E_CHNUM > 13U )
    ,BSW_CANNM_E_u2RX_TIMEOUT(13)
#endif /* ( BSW_CANNM_E_CHNUM > 13U ) */
#if( BSW_CANNM_E_CHNUM > 14U )
    ,BSW_CANNM_E_u2RX_TIMEOUT(14)
#endif /* ( BSW_CANNM_E_CHNUM > 14U ) */
#if( BSW_CANNM_E_CHNUM > 15U )
    ,BSW_CANNM_E_u2RX_TIMEOUT(15)
#endif /* ( BSW_CANNM_E_CHNUM > 15U ) */
#if( BSW_CANNM_E_CHNUM > 16U )
    ,BSW_CANNM_E_u2RX_TIMEOUT(16)
#endif /* ( BSW_CANNM_E_CHNUM > 16U ) */
#if( BSW_CANNM_E_CHNUM > 17U )
    ,BSW_CANNM_E_u2RX_TIMEOUT(17)
#endif /* ( BSW_CANNM_E_CHNUM > 17U ) */
#if( BSW_CANNM_E_CHNUM > 18U )
    ,BSW_CANNM_E_u2RX_TIMEOUT(18)
#endif /* ( BSW_CANNM_E_CHNUM > 18U ) */
#if( BSW_CANNM_E_CHNUM > 19U )
    ,BSW_CANNM_E_u2RX_TIMEOUT(19)
#endif /* ( BSW_CANNM_E_CHNUM > 19U ) */
#if( BSW_CANNM_E_CHNUM > 20U )
    ,BSW_CANNM_E_u2RX_TIMEOUT(20)
#endif /* ( BSW_CANNM_E_CHNUM > 20U ) */
#if( BSW_CANNM_E_CHNUM > 21U )
    ,BSW_CANNM_E_u2RX_TIMEOUT(21)
#endif /* ( BSW_CANNM_E_CHNUM > 21U ) */
#if( BSW_CANNM_E_CHNUM > 22U )
    ,BSW_CANNM_E_u2RX_TIMEOUT(22)
#endif /* ( BSW_CANNM_E_CHNUM > 22U ) */
#if( BSW_CANNM_E_CHNUM > 23U )
    ,BSW_CANNM_E_u2RX_TIMEOUT(23)
#endif /* ( BSW_CANNM_E_CHNUM > 23U ) */
#if( BSW_CANNM_E_CHNUM > 24U )
    ,BSW_CANNM_E_u2RX_TIMEOUT(24)
#endif /* ( BSW_CANNM_E_CHNUM > 24U ) */
#if( BSW_CANNM_E_CHNUM > 25U )
    ,BSW_CANNM_E_u2RX_TIMEOUT(25)
#endif /* ( BSW_CANNM_E_CHNUM > 25U ) */
#if( BSW_CANNM_E_CHNUM > 26U )
    ,BSW_CANNM_E_u2RX_TIMEOUT(26)
#endif /* ( BSW_CANNM_E_CHNUM > 26U ) */
#if( BSW_CANNM_E_CHNUM > 27U )
    ,BSW_CANNM_E_u2RX_TIMEOUT(27)
#endif /* ( BSW_CANNM_E_CHNUM > 27U ) */
#if( BSW_CANNM_E_CHNUM > 28U )
    ,BSW_CANNM_E_u2RX_TIMEOUT(28)
#endif /* ( BSW_CANNM_E_CHNUM > 28U ) */
#if( BSW_CANNM_E_CHNUM > 29U )
    ,BSW_CANNM_E_u2RX_TIMEOUT(29)
#endif /* ( BSW_CANNM_E_CHNUM > 29U ) */
#if( BSW_CANNM_E_CHNUM > 30U )
    ,BSW_CANNM_E_u2RX_TIMEOUT(30)
#endif /* ( BSW_CANNM_E_CHNUM > 30U ) */
#if( BSW_CANNM_E_CHNUM > 31U )
    ,BSW_CANNM_E_u2RX_TIMEOUT(31)
#endif /* ( BSW_CANNM_E_CHNUM > 31U ) */
};

/* Location information for received NM message definitions */
BswConst BswU2 bsw_cannm_e_ctrl_u2RxMsgIndex[BSW_CANNM_E_CHNUM + 1U] =
{
     (BswU2)(BSW_CANNM_E_RMSG_NMINDEX_CH0)
    ,(BswU2)(BSW_CANNM_E_RMSG_NMINDEX_CH1)
#if (BSW_CANNM_E_CHNUM > 1U)
    ,(BswU2)(BSW_CANNM_E_RMSG_NMINDEX_CH2)
#endif
#if (BSW_CANNM_E_CHNUM > 2U)
    ,(BswU2)(BSW_CANNM_E_RMSG_NMINDEX_CH3)
#endif
#if (BSW_CANNM_E_CHNUM > 3U)
    ,(BswU2)(BSW_CANNM_E_RMSG_NMINDEX_CH4)
#endif
#if (BSW_CANNM_E_CHNUM > 4U)
    ,(BswU2)(BSW_CANNM_E_RMSG_NMINDEX_CH5)
#endif
#if (BSW_CANNM_E_CHNUM > 5U)
    ,(BswU2)(BSW_CANNM_E_RMSG_NMINDEX_CH6)
#endif
#if (BSW_CANNM_E_CHNUM > 6U)
    ,(BswU2)(BSW_CANNM_E_RMSG_NMINDEX_CH7)
#endif
#if (BSW_CANNM_E_CHNUM > 7U)
    ,(BswU2)(BSW_CANNM_E_RMSG_NMINDEX_CH8)
#endif
#if (BSW_CANNM_E_CHNUM > 8U)
    ,(BswU2)(BSW_CANNM_E_RMSG_NMINDEX_CH9)
#endif
#if (BSW_CANNM_E_CHNUM > 9U)
    ,(BswU2)(BSW_CANNM_E_RMSG_NMINDEX_CH10)
#endif
#if (BSW_CANNM_E_CHNUM > 10U)
    ,(BswU2)(BSW_CANNM_E_RMSG_NMINDEX_CH11)
#endif
#if (BSW_CANNM_E_CHNUM > 11U)
    ,(BswU2)(BSW_CANNM_E_RMSG_NMINDEX_CH12)
#endif
#if (BSW_CANNM_E_CHNUM > 12U)
    ,(BswU2)(BSW_CANNM_E_RMSG_NMINDEX_CH13)
#endif
#if (BSW_CANNM_E_CHNUM > 13U)
    ,(BswU2)(BSW_CANNM_E_RMSG_NMINDEX_CH14)
#endif
#if (BSW_CANNM_E_CHNUM > 14U)
    ,(BswU2)(BSW_CANNM_E_RMSG_NMINDEX_CH15)
#endif
#if (BSW_CANNM_E_CHNUM > 15U)
    ,(BswU2)(BSW_CANNM_E_RMSG_NMINDEX_CH16)
#endif
#if (BSW_CANNM_E_CHNUM > 16U)
    ,(BswU2)(BSW_CANNM_E_RMSG_NMINDEX_CH17)
#endif
#if (BSW_CANNM_E_CHNUM > 17U)
    ,(BswU2)(BSW_CANNM_E_RMSG_NMINDEX_CH18)
#endif
#if (BSW_CANNM_E_CHNUM > 18U)
    ,(BswU2)(BSW_CANNM_E_RMSG_NMINDEX_CH19)
#endif
#if (BSW_CANNM_E_CHNUM > 19U)
    ,(BswU2)(BSW_CANNM_E_RMSG_NMINDEX_CH20)
#endif
#if (BSW_CANNM_E_CHNUM > 20U)
    ,(BswU2)(BSW_CANNM_E_RMSG_NMINDEX_CH21)
#endif
#if (BSW_CANNM_E_CHNUM > 21U)
    ,(BswU2)(BSW_CANNM_E_RMSG_NMINDEX_CH22)
#endif
#if (BSW_CANNM_E_CHNUM > 22U)
    ,(BswU2)(BSW_CANNM_E_RMSG_NMINDEX_CH23)
#endif
#if (BSW_CANNM_E_CHNUM > 23U)
    ,(BswU2)(BSW_CANNM_E_RMSG_NMINDEX_CH24)
#endif
#if (BSW_CANNM_E_CHNUM > 24U)
    ,(BswU2)(BSW_CANNM_E_RMSG_NMINDEX_CH25)
#endif
#if (BSW_CANNM_E_CHNUM > 25U)
    ,(BswU2)(BSW_CANNM_E_RMSG_NMINDEX_CH26)
#endif
#if (BSW_CANNM_E_CHNUM > 26U)
    ,(BswU2)(BSW_CANNM_E_RMSG_NMINDEX_CH27)
#endif
#if (BSW_CANNM_E_CHNUM > 27U)
    ,(BswU2)(BSW_CANNM_E_RMSG_NMINDEX_CH28)
#endif
#if (BSW_CANNM_E_CHNUM > 28U)
    ,(BswU2)(BSW_CANNM_E_RMSG_NMINDEX_CH29)
#endif
#if (BSW_CANNM_E_CHNUM > 29U)
    ,(BswU2)(BSW_CANNM_E_RMSG_NMINDEX_CH30)
#endif
#if (BSW_CANNM_E_CHNUM > 30U)
    ,(BswU2)(BSW_CANNM_E_RMSG_NMINDEX_CH31)
#endif
#if (BSW_CANNM_E_CHNUM > 31U)
    ,(BswU2)(BSW_CANNM_E_RMSG_NMINDEX_END)
#endif
};

/* Length of wake-up frame */
BswConst BswU1 bsw_cannm_e_ctrl_u1WkupFrmLen[BSW_CANNM_E_CHNUM] =
{
     (BswU1)BSW_CANNM_E_CFG_WKUP_LEN_CH0
#if( BSW_CANNM_E_CHNUM > 1U )
    ,(BswU1)BSW_CANNM_E_CFG_WKUP_LEN_CH1
#endif /* ( BSW_CANNM_E_CHNUM > 1U ) */
#if( BSW_CANNM_E_CHNUM > 2U )
    ,(BswU1)BSW_CANNM_E_CFG_WKUP_LEN_CH2
#endif /* ( BSW_CANNM_E_CHNUM > 2U ) */
#if( BSW_CANNM_E_CHNUM > 3U )
    ,(BswU1)BSW_CANNM_E_CFG_WKUP_LEN_CH3
#endif /* ( BSW_CANNM_E_CHNUM > 3U ) */
#if( BSW_CANNM_E_CHNUM > 4U )
    ,(BswU1)BSW_CANNM_E_CFG_WKUP_LEN_CH4
#endif /* ( BSW_CANNM_E_CHNUM > 4U ) */
#if( BSW_CANNM_E_CHNUM > 5U )
    ,(BswU1)BSW_CANNM_E_CFG_WKUP_LEN_CH5
#endif /* ( BSW_CANNM_E_CHNUM > 5U ) */
#if( BSW_CANNM_E_CHNUM > 6U )
    ,(BswU1)BSW_CANNM_E_CFG_WKUP_LEN_CH6
#endif /* ( BSW_CANNM_E_CHNUM > 6U ) */
#if( BSW_CANNM_E_CHNUM > 7U )
    ,(BswU1)BSW_CANNM_E_CFG_WKUP_LEN_CH7
#endif /* ( BSW_CANNM_E_CHNUM > 7U ) */
#if( BSW_CANNM_E_CHNUM > 8U )
    ,(BswU1)BSW_CANNM_E_CFG_WKUP_LEN_CH8
#endif /* ( BSW_CANNM_E_CHNUM > 8U ) */
#if( BSW_CANNM_E_CHNUM > 9U )
    ,(BswU1)BSW_CANNM_E_CFG_WKUP_LEN_CH9
#endif /* ( BSW_CANNM_E_CHNUM > 9U ) */
#if( BSW_CANNM_E_CHNUM > 10U )
    ,(BswU1)BSW_CANNM_E_CFG_WKUP_LEN_CH10
#endif /* ( BSW_CANNM_E_CHNUM > 10U ) */
#if( BSW_CANNM_E_CHNUM > 11U )
    ,(BswU1)BSW_CANNM_E_CFG_WKUP_LEN_CH11
#endif /* ( BSW_CANNM_E_CHNUM > 11U ) */
#if( BSW_CANNM_E_CHNUM > 12U )
    ,(BswU1)BSW_CANNM_E_CFG_WKUP_LEN_CH12
#endif /* ( BSW_CANNM_E_CHNUM > 12U ) */
#if( BSW_CANNM_E_CHNUM > 13U )
    ,(BswU1)BSW_CANNM_E_CFG_WKUP_LEN_CH13
#endif /* ( BSW_CANNM_E_CHNUM > 13U ) */
#if( BSW_CANNM_E_CHNUM > 14U )
    ,(BswU1)BSW_CANNM_E_CFG_WKUP_LEN_CH14
#endif /* ( BSW_CANNM_E_CHNUM > 14U ) */
#if( BSW_CANNM_E_CHNUM > 15U )
    ,(BswU1)BSW_CANNM_E_CFG_WKUP_LEN_CH15
#endif /* ( BSW_CANNM_E_CHNUM > 15U ) */
#if( BSW_CANNM_E_CHNUM > 16U )
    ,(BswU1)BSW_CANNM_E_CFG_WKUP_LEN_CH16
#endif /* ( BSW_CANNM_E_CHNUM > 16U ) */
#if( BSW_CANNM_E_CHNUM > 17U )
    ,(BswU1)BSW_CANNM_E_CFG_WKUP_LEN_CH17
#endif /* ( BSW_CANNM_E_CHNUM > 17U ) */
#if( BSW_CANNM_E_CHNUM > 18U )
    ,(BswU1)BSW_CANNM_E_CFG_WKUP_LEN_CH18
#endif /* ( BSW_CANNM_E_CHNUM > 18U ) */
#if( BSW_CANNM_E_CHNUM > 19U )
    ,(BswU1)BSW_CANNM_E_CFG_WKUP_LEN_CH19
#endif /* ( BSW_CANNM_E_CHNUM > 19U ) */
#if( BSW_CANNM_E_CHNUM > 20U )
    ,(BswU1)BSW_CANNM_E_CFG_WKUP_LEN_CH20
#endif /* ( BSW_CANNM_E_CHNUM > 20U ) */
#if( BSW_CANNM_E_CHNUM > 21U )
    ,(BswU1)BSW_CANNM_E_CFG_WKUP_LEN_CH21
#endif /* ( BSW_CANNM_E_CHNUM > 21U ) */
#if( BSW_CANNM_E_CHNUM > 22U )
    ,(BswU1)BSW_CANNM_E_CFG_WKUP_LEN_CH22
#endif /* ( BSW_CANNM_E_CHNUM > 22U ) */
#if( BSW_CANNM_E_CHNUM > 23U )
    ,(BswU1)BSW_CANNM_E_CFG_WKUP_LEN_CH23
#endif /* ( BSW_CANNM_E_CHNUM > 23U ) */
#if( BSW_CANNM_E_CHNUM > 24U )
    ,(BswU1)BSW_CANNM_E_CFG_WKUP_LEN_CH24
#endif /* ( BSW_CANNM_E_CHNUM > 24U ) */
#if( BSW_CANNM_E_CHNUM > 25U )
    ,(BswU1)BSW_CANNM_E_CFG_WKUP_LEN_CH25
#endif /* ( BSW_CANNM_E_CHNUM > 25U ) */
#if( BSW_CANNM_E_CHNUM > 26U )
    ,(BswU1)BSW_CANNM_E_CFG_WKUP_LEN_CH26
#endif /* ( BSW_CANNM_E_CHNUM > 26U ) */
#if( BSW_CANNM_E_CHNUM > 27U )
    ,(BswU1)BSW_CANNM_E_CFG_WKUP_LEN_CH27
#endif /* ( BSW_CANNM_E_CHNUM > 27U ) */
#if( BSW_CANNM_E_CHNUM > 28U )
    ,(BswU1)BSW_CANNM_E_CFG_WKUP_LEN_CH28
#endif /* ( BSW_CANNM_E_CHNUM > 28U ) */
#if( BSW_CANNM_E_CHNUM > 29U )
    ,(BswU1)BSW_CANNM_E_CFG_WKUP_LEN_CH29
#endif /* ( BSW_CANNM_E_CHNUM > 29U ) */
#if( BSW_CANNM_E_CHNUM > 30U )
    ,(BswU1)BSW_CANNM_E_CFG_WKUP_LEN_CH30
#endif /* ( BSW_CANNM_E_CHNUM > 30U ) */
#if( BSW_CANNM_E_CHNUM > 31U )
    ,(BswU1)BSW_CANNM_E_CFG_WKUP_LEN_CH31
#endif /* ( BSW_CANNM_E_CHNUM > 31U ) */
};

/* Connection of the wake-up frame transmission function */
void (* BswConst bsw_cannm_e_ctrl_ptSndWkUpFrmFn[BSW_CANNM_E_CHNUM] )( BswU1 u1NetID ) =
{
     BSW_CANNM_E_SENDWKUPFLMFN(0)
#if( BSW_CANNM_E_CHNUM > 1U )
    ,BSW_CANNM_E_SENDWKUPFLMFN(1)
#endif /* ( BSW_CANNM_E_CHNUM > 1U ) */
#if( BSW_CANNM_E_CHNUM > 2U )
    ,BSW_CANNM_E_SENDWKUPFLMFN(2)
#endif /* ( BSW_CANNM_E_CHNUM > 2U ) */
#if( BSW_CANNM_E_CHNUM > 3U )
    ,BSW_CANNM_E_SENDWKUPFLMFN(3)
#endif /* ( BSW_CANNM_E_CHNUM > 3U ) */
#if( BSW_CANNM_E_CHNUM > 4U )
    ,BSW_CANNM_E_SENDWKUPFLMFN(4)
#endif /* ( BSW_CANNM_E_CHNUM > 4U ) */
#if( BSW_CANNM_E_CHNUM > 5U )
    ,BSW_CANNM_E_SENDWKUPFLMFN(5)
#endif /* ( BSW_CANNM_E_CHNUM > 5U ) */
#if( BSW_CANNM_E_CHNUM > 6U )
    ,BSW_CANNM_E_SENDWKUPFLMFN(6)
#endif /* ( BSW_CANNM_E_CHNUM > 6U ) */
#if( BSW_CANNM_E_CHNUM > 7U )
    ,BSW_CANNM_E_SENDWKUPFLMFN(7)
#endif /* ( BSW_CANNM_E_CHNUM > 7U ) */
#if( BSW_CANNM_E_CHNUM > 8U )
    ,BSW_CANNM_E_SENDWKUPFLMFN(8)
#endif /* ( BSW_CANNM_E_CHNUM > 8U ) */
#if( BSW_CANNM_E_CHNUM > 9U )
    ,BSW_CANNM_E_SENDWKUPFLMFN(9)
#endif /* ( BSW_CANNM_E_CHNUM > 9U ) */
#if( BSW_CANNM_E_CHNUM > 10U )
    ,BSW_CANNM_E_SENDWKUPFLMFN(10)
#endif /* ( BSW_CANNM_E_CHNUM > 10U ) */
#if( BSW_CANNM_E_CHNUM > 11U )
    ,BSW_CANNM_E_SENDWKUPFLMFN(11)
#endif /* ( BSW_CANNM_E_CHNUM > 11U ) */
#if( BSW_CANNM_E_CHNUM > 12U )
    ,BSW_CANNM_E_SENDWKUPFLMFN(12)
#endif /* ( BSW_CANNM_E_CHNUM > 12U ) */
#if( BSW_CANNM_E_CHNUM > 13U )
    ,BSW_CANNM_E_SENDWKUPFLMFN(13)
#endif /* ( BSW_CANNM_E_CHNUM > 13U ) */
#if( BSW_CANNM_E_CHNUM > 14U )
    ,BSW_CANNM_E_SENDWKUPFLMFN(14)
#endif /* ( BSW_CANNM_E_CHNUM > 14U ) */
#if( BSW_CANNM_E_CHNUM > 15U )
    ,BSW_CANNM_E_SENDWKUPFLMFN(15)
#endif /* ( BSW_CANNM_E_CHNUM > 15U ) */
#if( BSW_CANNM_E_CHNUM > 16U )
    ,BSW_CANNM_E_SENDWKUPFLMFN(16)
#endif /* ( BSW_CANNM_E_CHNUM > 16U ) */
#if( BSW_CANNM_E_CHNUM > 17U )
    ,BSW_CANNM_E_SENDWKUPFLMFN(17)
#endif /* ( BSW_CANNM_E_CHNUM > 17U ) */
#if( BSW_CANNM_E_CHNUM > 18U )
    ,BSW_CANNM_E_SENDWKUPFLMFN(18)
#endif /* ( BSW_CANNM_E_CHNUM > 18U ) */
#if( BSW_CANNM_E_CHNUM > 19U )
    ,BSW_CANNM_E_SENDWKUPFLMFN(19)
#endif /* ( BSW_CANNM_E_CHNUM > 19U ) */
#if( BSW_CANNM_E_CHNUM > 20U )
    ,BSW_CANNM_E_SENDWKUPFLMFN(20)
#endif /* ( BSW_CANNM_E_CHNUM > 20U ) */
#if( BSW_CANNM_E_CHNUM > 21U )
    ,BSW_CANNM_E_SENDWKUPFLMFN(21)
#endif /* ( BSW_CANNM_E_CHNUM > 21U ) */
#if( BSW_CANNM_E_CHNUM > 22U )
    ,BSW_CANNM_E_SENDWKUPFLMFN(22)
#endif /* ( BSW_CANNM_E_CHNUM > 22U ) */
#if( BSW_CANNM_E_CHNUM > 23U )
    ,BSW_CANNM_E_SENDWKUPFLMFN(23)
#endif /* ( BSW_CANNM_E_CHNUM > 23U ) */
#if( BSW_CANNM_E_CHNUM > 24U )
    ,BSW_CANNM_E_SENDWKUPFLMFN(24)
#endif /* ( BSW_CANNM_E_CHNUM > 24U ) */
#if( BSW_CANNM_E_CHNUM > 25U )
    ,BSW_CANNM_E_SENDWKUPFLMFN(25)
#endif /* ( BSW_CANNM_E_CHNUM > 25U ) */
#if( BSW_CANNM_E_CHNUM > 26U )
    ,BSW_CANNM_E_SENDWKUPFLMFN(26)
#endif /* ( BSW_CANNM_E_CHNUM > 26U ) */
#if( BSW_CANNM_E_CHNUM > 27U )
    ,BSW_CANNM_E_SENDWKUPFLMFN(27)
#endif /* ( BSW_CANNM_E_CHNUM > 27U ) */
#if( BSW_CANNM_E_CHNUM > 28U )
    ,BSW_CANNM_E_SENDWKUPFLMFN(28)
#endif /* ( BSW_CANNM_E_CHNUM > 28U ) */
#if( BSW_CANNM_E_CHNUM > 29U )
    ,BSW_CANNM_E_SENDWKUPFLMFN(29)
#endif /* ( BSW_CANNM_E_CHNUM > 29U ) */
#if( BSW_CANNM_E_CHNUM > 30U )
    ,BSW_CANNM_E_SENDWKUPFLMFN(30)
#endif /* ( BSW_CANNM_E_CHNUM > 30U ) */
#if( BSW_CANNM_E_CHNUM > 31U )
    ,BSW_CANNM_E_SENDWKUPFLMFN(31)
#endif /* ( BSW_CANNM_E_CHNUM > 31U ) */
};

/* Connection of the wake-up frame transmission cancellation function */
void (* BswConst bsw_cannm_e_ctrl_ptAbtWkUpFrmFn[BSW_CANNM_E_CHNUM] )( BswU1 u1NetID ) =
{
     BSW_CANNM_E_ABRTWKUPFLMFN(0)
#if( BSW_CANNM_E_CHNUM > 1U )
    ,BSW_CANNM_E_ABRTWKUPFLMFN(1)
#endif /* ( BSW_CANNM_E_CHNUM > 1U ) */
#if( BSW_CANNM_E_CHNUM > 2U )
    ,BSW_CANNM_E_ABRTWKUPFLMFN(2)
#endif /* ( BSW_CANNM_E_CHNUM > 2U ) */
#if( BSW_CANNM_E_CHNUM > 3U )
    ,BSW_CANNM_E_ABRTWKUPFLMFN(3)
#endif /* ( BSW_CANNM_E_CHNUM > 3U ) */
#if( BSW_CANNM_E_CHNUM > 4U )
    ,BSW_CANNM_E_ABRTWKUPFLMFN(4)
#endif /* ( BSW_CANNM_E_CHNUM > 4U ) */
#if( BSW_CANNM_E_CHNUM > 5U )
    ,BSW_CANNM_E_ABRTWKUPFLMFN(5)
#endif /* ( BSW_CANNM_E_CHNUM > 5U ) */
#if( BSW_CANNM_E_CHNUM > 6U )
    ,BSW_CANNM_E_ABRTWKUPFLMFN(6)
#endif /* ( BSW_CANNM_E_CHNUM > 6U ) */
#if( BSW_CANNM_E_CHNUM > 7U )
    ,BSW_CANNM_E_ABRTWKUPFLMFN(7)
#endif /* ( BSW_CANNM_E_CHNUM > 7U ) */
#if( BSW_CANNM_E_CHNUM > 8U )
    ,BSW_CANNM_E_ABRTWKUPFLMFN(8)
#endif /* ( BSW_CANNM_E_CHNUM > 8U ) */
#if( BSW_CANNM_E_CHNUM > 9U )
    ,BSW_CANNM_E_ABRTWKUPFLMFN(9)
#endif /* ( BSW_CANNM_E_CHNUM > 9U ) */
#if( BSW_CANNM_E_CHNUM > 10U )
    ,BSW_CANNM_E_ABRTWKUPFLMFN(10)
#endif /* ( BSW_CANNM_E_CHNUM > 10U ) */
#if( BSW_CANNM_E_CHNUM > 11U )
    ,BSW_CANNM_E_ABRTWKUPFLMFN(11)
#endif /* ( BSW_CANNM_E_CHNUM > 11U ) */
#if( BSW_CANNM_E_CHNUM > 12U )
    ,BSW_CANNM_E_ABRTWKUPFLMFN(12)
#endif /* ( BSW_CANNM_E_CHNUM > 12U ) */
#if( BSW_CANNM_E_CHNUM > 13U )
    ,BSW_CANNM_E_ABRTWKUPFLMFN(13)
#endif /* ( BSW_CANNM_E_CHNUM > 13U ) */
#if( BSW_CANNM_E_CHNUM > 14U )
    ,BSW_CANNM_E_ABRTWKUPFLMFN(14)
#endif /* ( BSW_CANNM_E_CHNUM > 14U ) */
#if( BSW_CANNM_E_CHNUM > 15U )
    ,BSW_CANNM_E_ABRTWKUPFLMFN(15)
#endif /* ( BSW_CANNM_E_CHNUM > 15U ) */
#if( BSW_CANNM_E_CHNUM > 16U )
    ,BSW_CANNM_E_ABRTWKUPFLMFN(16)
#endif /* ( BSW_CANNM_E_CHNUM > 16U ) */
#if( BSW_CANNM_E_CHNUM > 17U )
    ,BSW_CANNM_E_ABRTWKUPFLMFN(17)
#endif /* ( BSW_CANNM_E_CHNUM > 17U ) */
#if( BSW_CANNM_E_CHNUM > 18U )
    ,BSW_CANNM_E_ABRTWKUPFLMFN(18)
#endif /* ( BSW_CANNM_E_CHNUM > 18U ) */
#if( BSW_CANNM_E_CHNUM > 19U )
    ,BSW_CANNM_E_ABRTWKUPFLMFN(19)
#endif /* ( BSW_CANNM_E_CHNUM > 19U ) */
#if( BSW_CANNM_E_CHNUM > 20U )
    ,BSW_CANNM_E_ABRTWKUPFLMFN(20)
#endif /* ( BSW_CANNM_E_CHNUM > 20U ) */
#if( BSW_CANNM_E_CHNUM > 21U )
    ,BSW_CANNM_E_ABRTWKUPFLMFN(21)
#endif /* ( BSW_CANNM_E_CHNUM > 21U ) */
#if( BSW_CANNM_E_CHNUM > 22U )
    ,BSW_CANNM_E_ABRTWKUPFLMFN(22)
#endif /* ( BSW_CANNM_E_CHNUM > 22U ) */
#if( BSW_CANNM_E_CHNUM > 23U )
    ,BSW_CANNM_E_ABRTWKUPFLMFN(23)
#endif /* ( BSW_CANNM_E_CHNUM > 23U ) */
#if( BSW_CANNM_E_CHNUM > 24U )
    ,BSW_CANNM_E_ABRTWKUPFLMFN(24)
#endif /* ( BSW_CANNM_E_CHNUM > 24U ) */
#if( BSW_CANNM_E_CHNUM > 25U )
    ,BSW_CANNM_E_ABRTWKUPFLMFN(25)
#endif /* ( BSW_CANNM_E_CHNUM > 25U ) */
#if( BSW_CANNM_E_CHNUM > 26U )
    ,BSW_CANNM_E_ABRTWKUPFLMFN(26)
#endif /* ( BSW_CANNM_E_CHNUM > 26U ) */
#if( BSW_CANNM_E_CHNUM > 27U )
    ,BSW_CANNM_E_ABRTWKUPFLMFN(27)
#endif /* ( BSW_CANNM_E_CHNUM > 27U ) */
#if( BSW_CANNM_E_CHNUM > 28U )
    ,BSW_CANNM_E_ABRTWKUPFLMFN(28)
#endif /* ( BSW_CANNM_E_CHNUM > 28U ) */
#if( BSW_CANNM_E_CHNUM > 29U )
    ,BSW_CANNM_E_ABRTWKUPFLMFN(29)
#endif /* ( BSW_CANNM_E_CHNUM > 29U ) */
#if( BSW_CANNM_E_CHNUM > 30U )
    ,BSW_CANNM_E_ABRTWKUPFLMFN(30)
#endif /* ( BSW_CANNM_E_CHNUM > 30U ) */
#if( BSW_CANNM_E_CHNUM > 31U )
    ,BSW_CANNM_E_ABRTWKUPFLMFN(31)
#endif /* ( BSW_CANNM_E_CHNUM > 31U ) */
};

#endif /* ( BSW_CANNM_NM_TYPE_USE_E == BSW_USE ) */
#endif /* ( BSW_BSWM_CS_FUNC_CANNM == BSW_USE ) */
/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2019/02/15                                             */
/*  v2-0-0          :2021/12/02                                             */
/*  v3-0-0          :2025/01/17                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
