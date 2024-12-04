/* bsw_cannm_z_config_c_v2-0-0                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANNM/Z/CONFIG/CODE                                   */
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
#if ( BSW_CANNM_NM_TYPE_USE_Z == BSW_USE )

#include <canif/bsw_canif.h>
#include "../../inc/z/bsw_cannm_z_ctrl.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define BSW_CANNM_Z_USE(ch)         ((BSW_CANNM_NM_TYPE(ch) == BSW_CANNM_NMTYPE_Z) ? BSW_USE : BSW_NOUSE)
#define BSW_CANNM_Z_CAN_CH_NUM      (BSW_COMM_BUS_TYPE_CHNUM(CAN))

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
Bsw_CanNmZ_ChStsType bsw_cannm_z_ctrl_stChSts[BSW_CANNM_Z_CAN_CH_NUM];

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
/* Maximum number of channels      */
BswConst BswU1                     bsw_cannm_z_ctrl_u1MaxCh = (BswU1)BSW_CANNM_Z_CAN_CH_NUM;

/* Channel offset  */
BswConst BswU1                     bsw_cannm_z_ctrl_u1ChOffset = (BswU1)BSW_COMM_BUS_TYPE_OFFSET(CAN);

/* Channel used/not used table */
BswConst BswU1 bsw_cannm_z_ctrl_u1Channel[BSW_CANNM_Z_CAN_CH_NUM] =
{
    (BswU1)BSW_CANNM_Z_USE(0)
#if (BSW_CANNM_Z_CAN_CH_NUM > 1U)
   ,(BswU1)BSW_CANNM_Z_USE(1)
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 2U)
   ,(BswU1)BSW_CANNM_Z_USE(2)
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 3U)
   ,(BswU1)BSW_CANNM_Z_USE(3)
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 4U)
   ,(BswU1)BSW_CANNM_Z_USE(4)
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 5U)
   ,(BswU1)BSW_CANNM_Z_USE(5)
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 6U)
   ,(BswU1)BSW_CANNM_Z_USE(6)
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 7U)
   ,(BswU1)BSW_CANNM_Z_USE(7)
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 8U)
   ,(BswU1)BSW_CANNM_Z_USE(8)
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 9U)
   ,(BswU1)BSW_CANNM_Z_USE(9)
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 10U)
   ,(BswU1)BSW_CANNM_Z_USE(10)
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 11U)
   ,(BswU1)BSW_CANNM_Z_USE(11)
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 12U)
   ,(BswU1)BSW_CANNM_Z_USE(12)
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 13U)
   ,(BswU1)BSW_CANNM_Z_USE(13)
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 14U)
   ,(BswU1)BSW_CANNM_Z_USE(14)
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 15U)
   ,(BswU1)BSW_CANNM_Z_USE(15)
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 16U)
   ,(BswU1)BSW_CANNM_Z_USE(16)
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 17U)
   ,(BswU1)BSW_CANNM_Z_USE(17)
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 18U)
   ,(BswU1)BSW_CANNM_Z_USE(18)
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 19U)
   ,(BswU1)BSW_CANNM_Z_USE(19)
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 20U)
   ,(BswU1)BSW_CANNM_Z_USE(20)
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 21U)
   ,(BswU1)BSW_CANNM_Z_USE(21)
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 22U)
   ,(BswU1)BSW_CANNM_Z_USE(22)
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 23U)
   ,(BswU1)BSW_CANNM_Z_USE(23)
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 24U)
   ,(BswU1)BSW_CANNM_Z_USE(24)
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 25U)
   ,(BswU1)BSW_CANNM_Z_USE(25)
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 26U)
   ,(BswU1)BSW_CANNM_Z_USE(26)
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 27U)
   ,(BswU1)BSW_CANNM_Z_USE(27)
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 28U)
   ,(BswU1)BSW_CANNM_Z_USE(28)
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 29U)
   ,(BswU1)BSW_CANNM_Z_USE(29)
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 30U)
   ,(BswU1)BSW_CANNM_Z_USE(30)
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 31U)
   ,(BswU1)BSW_CANNM_Z_USE(31)
#endif
};

/* Control message transmission enable time  */
BswConst BswU2                     bsw_cannm_z_ctrl_u2SndStrt[BSW_CANNM_Z_CAN_CH_NUM] = 
{
     BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_SEND_START_PW(CAN, 0U))
#if (BSW_CANNM_Z_CAN_CH_NUM > 1U)
   , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_SEND_START_PW(CAN, 1U))
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 2U)
   , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_SEND_START_PW(CAN, 2U))
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 3U)
   , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_SEND_START_PW(CAN, 3U))
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 4U)
   , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_SEND_START_PW(CAN, 4U))
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 5U)
   , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_SEND_START_PW(CAN, 5U))
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 6U)
   , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_SEND_START_PW(CAN, 6U))
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 7U)
   , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_SEND_START_PW(CAN, 7U))
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 8U)
   , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_SEND_START_PW(CAN, 8U))
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 9U)
   , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_SEND_START_PW(CAN, 9U))
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 10U)
   , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_SEND_START_PW(CAN, 10U))
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 11U)
   , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_SEND_START_PW(CAN, 11U))
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 12U)
   , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_SEND_START_PW(CAN, 12U))
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 13U)
   , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_SEND_START_PW(CAN, 13U))
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 14U)
   , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_SEND_START_PW(CAN, 14U))
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 15U)
   , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_SEND_START_PW(CAN, 15U))
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 16U)
   , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_SEND_START_PW(CAN, 16U))
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 17U)
   , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_SEND_START_PW(CAN, 17U))
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 18U)
   , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_SEND_START_PW(CAN, 18U))
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 19U)
   , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_SEND_START_PW(CAN, 19U))
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 20U)
   , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_SEND_START_PW(CAN, 20U))
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 21U)
   , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_SEND_START_PW(CAN, 21U))
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 22U)
   , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_SEND_START_PW(CAN, 22U))
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 23U)
   , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_SEND_START_PW(CAN, 23U))
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 24U)
   , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_SEND_START_PW(CAN, 24U))
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 25U)
   , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_SEND_START_PW(CAN, 25U))
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 26U)
   , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_SEND_START_PW(CAN, 26U))
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 27U)
   , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_SEND_START_PW(CAN, 27U))
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 28U)
   , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_SEND_START_PW(CAN, 28U))
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 29U)
   , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_SEND_START_PW(CAN, 29U))
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 30U)
   , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_SEND_START_PW(CAN, 30U))
#endif
#if (BSW_CANNM_Z_CAN_CH_NUM > 31U)
   , BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_CS_SEND_START_PW(CAN, 31U))
#endif
};

#endif /* ( BSW_CANNM_NM_TYPE_USE_Z == BSW_USE ) */
#endif /* ( BSW_BSWM_CS_FUNC_CANNM == BSW_USE ) */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/10/16                                             */
/*  v1-1-0          :2018/12/14                                             */
/*  v2-0-0          :2021/12/02                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
