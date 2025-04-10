/* bsw_bswm_can_config_c_v3-0-0                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/BSWM/CAN/CONFIG/CODE                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>
#include "../inc/bsw_bswm_can_MemMap.h"
#include <ComStack_Types.h>

#include <bswm_cs/bsw_bswm_cs.h>
#include <comm/bsw_comm.h>
#include "../../ComM/inc/bsw_comm_config.h"
#include "../../BswM_CS/inc/bsw_bswm_cs_config.h"
#if ( BSW_BSWM_CS_FUNC_BSWMCAN == BSW_USE )

#include <bswm_can/bsw_bswm_can.h>
#include <cannm/bsw_cannm.h>
#include <vcan/bsw_vcan.h>

#include "../inc/bsw_bswm_can_ctrl.h"
#include "../inc/bsw_bswm_can_connector.h"
#include "../inc/bsw_bswm_can_status.h"
#include "../inc/bsw_bswm_can_config.h"

#include "../cfg/BswM_Can_Cfg.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define BSW_BSWM_CAN_CHNUM                     (BSW_COMM_BUS_TYPE_CHNUM(CAN))
#define BSW_BSWM_CAN_CHOFFSET                  (BSW_COMM_BUS_TYPE_OFFSET(CAN))
#define BSW_BSWM_CAN_TXCTRL_CH_NUM             (BSW_BSWM_CAN_CHNUM)
#define BSW_BSWM_CAN_CHRST_CH_NUM              (BSW_BSWM_CAN_CHNUM)
#define BSW_BSWM_CAN_DM_CH_NUM                 (BSW_BSWM_CAN_CHNUM)

#if ( BSW_BSWM_CS_TXCTRL_FUNC == BSW_USE )
#define BSW_BSWM_CAN_FUNC_INTTXSTCTRL         (&bsw_bswm_can_ctrl_InitTxCtrl)
#define BSW_BSWM_CAN_FUNC_UPDTXSTCTRL         (&bsw_bswm_can_ctrl_UpdateTxCtrl)
#define BSW_BSWM_CAN_FUNC_CNTTIMTXCTRL        (&bsw_bswm_can_ctrl_CntTimTxCtrl)
#else
#define BSW_BSWM_CAN_FUNC_INTTXSTCTRL         (&bsw_bswm_can_ctrl_IntTxCtrlNone)
#define BSW_BSWM_CAN_FUNC_UPDTXSTCTRL         (&bsw_bswm_can_ctrl_UpdTxCtrlNone)
#define BSW_BSWM_CAN_FUNC_CNTTIMTXCTRL        (&bsw_bswm_can_ctrl_CtTmTxCtrNone)
#endif

#if ( BSW_BSWM_CS_CHRSTCTRL_FUNC == BSW_USE )
#define BSW_BSWM_CAN_FUNC_INTRSTCHCTRL         (&bsw_bswm_can_ctrl_InitRstCh)
#else
#define BSW_BSWM_CAN_FUNC_INTRSTCHCTRL         (&bsw_bswm_can_ctrl_InitRstChNone)
#endif

#if ( BSW_BSWM_CS_DMCTRL_FUNC == BSW_USE )
#define BSW_BSWM_CAN_FUNC_INTDMCTRL            (&bsw_bswm_can_ctrl_InitDMCtrl)
#define BSW_BSWM_CAN_FUNC_UPDDMCTRL            (&bsw_bswm_can_ctrl_UpdateDmCtrl)
#else
#define BSW_BSWM_CAN_FUNC_INTDMCTRL            (&bsw_bswm_can_ctrl_IntDMCtrlNone)
#define BSW_BSWM_CAN_FUNC_UPDDMCTRL            (&bsw_bswm_can_ctrl_UpdDmCtrlNone)
#endif

#if ( BSW_BSWM_CS_ECU_FAIL == BSW_NOUSE )
#if ( BSW_BSWM_CS_FUNC_CANTP == BSW_USE )
#define BSW_BSWM_CAN_FUNC_CHECKRAM             (&bsw_bswm_can_CanTpCheckRam)
#else
#define BSW_BSWM_CAN_FUNC_CHECKRAM             (&bsw_bswm_can_st_TPChkRamNone)
#endif
#endif

#if ( BSW_BSWM_CS_FUNC_CANTP == BSW_USE )
#define BSW_BSWM_CAN_FUNC_TPENABLETX           (&bsw_bswm_can_CanTpEnableTx)
#define BSW_BSWM_CAN_FUNC_TPDISABLETX          (&bsw_bswm_can_CanTpDisableTx)
#else
#define BSW_BSWM_CAN_FUNC_TPENABLETX           (&bsw_bswm_can_ctrl_TpEnTxNone)
#define BSW_BSWM_CAN_FUNC_TPDISABLETX          (&bsw_bswm_can_ctrl_TpDisTxNone)
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
/*------------------------------------------*/
/* Unit:State management                       */
/*------------------------------------------*/

/*------------------------------------------*/
/* Unit:Channel control                   */
/*------------------------------------------*/
Bsw_BswMCan_ChStatType   bsw_bswm_can_ctrl_stChStat[BSW_BSWM_CAN_CHNUM];

#if ( BSW_BSWM_CS_TXCTRL_FUNC == BSW_USE )
Bsw_BswMCan_TxCtrlType   bsw_bswm_can_ctrl_stTxStat[BSW_BSWM_CAN_TXCTRL_CH_NUM];
#endif

#if ( BSW_BSWM_CS_CHRSTCTRL_FUNC == BSW_USE )
BswU1                   bsw_bswm_can_ctrl_u1ChRstReq[BSW_BSWM_CAN_CHRST_CH_NUM];
#endif

#if ( BSW_BSWM_CS_DMCTRL_FUNC == BSW_USE )
BswU1                   bsw_bswm_can_ctrl_u1DmReq[BSW_BSWM_CAN_DM_CH_NUM];
#endif


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
/*------------------------------------------*/
/* Unit:Channel control                   */
/*------------------------------------------*/
BswConst BswU1 bsw_bswm_can_ctrl_u1ChNum           = (BswU1)BSW_BSWM_CAN_CHNUM;
BswConst BswU1 bsw_bswm_can_ctrl_u1ChOffset        = (BswU1)BSW_BSWM_CAN_CHOFFSET;

/* Reception deadline monitoring period setting table */
BswConst BswU1 bsw_bswm_can_ctrl_u1DMPeriodTbl[BSW_BSWM_CAN_CHNUM] = 
{
    (BswU1)BSW_BSWM_CAN_CFG_CH_DMPRD_0
#if( BSW_BSWM_CAN_CHNUM > 1U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMPRD_1
#endif /* #if( BSW_BSWM_CAN_CHNUM > 1U ) */
#if( BSW_BSWM_CAN_CHNUM > 2U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMPRD_2
#endif /* #if( BSW_BSWM_CAN_CHNUM > 2U ) */
#if( BSW_BSWM_CAN_CHNUM > 3U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMPRD_3
#endif /* #if( BSW_BSWM_CAN_CHNUM > 3U ) */
#if( BSW_BSWM_CAN_CHNUM > 4U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMPRD_4
#endif /* #if( BSW_BSWM_CAN_CHNUM > 4U ) */
#if( BSW_BSWM_CAN_CHNUM > 5U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMPRD_5
#endif /* #if( BSW_BSWM_CAN_CHNUM > 5U ) */
#if( BSW_BSWM_CAN_CHNUM > 6U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMPRD_6
#endif /* #if( BSW_BSWM_CAN_CHNUM > 6U ) */
#if( BSW_BSWM_CAN_CHNUM > 7U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMPRD_7
#endif /* #if( BSW_BSWM_CAN_CHNUM > 7U ) */
#if( BSW_BSWM_CAN_CHNUM > 8U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMPRD_8
#endif /* #if( BSW_BSWM_CAN_CHNUM > 8U ) */
#if( BSW_BSWM_CAN_CHNUM > 9U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMPRD_9
#endif /* #if( BSW_BSWM_CAN_CHNUM > 9U ) */
#if( BSW_BSWM_CAN_CHNUM > 10U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMPRD_10
#endif /* #if( BSW_BSWM_CAN_CHNUM > 10U ) */
#if( BSW_BSWM_CAN_CHNUM > 11U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMPRD_11
#endif /* #if( BSW_BSWM_CAN_CHNUM > 11U ) */
#if( BSW_BSWM_CAN_CHNUM > 12U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMPRD_12
#endif /* #if( BSW_BSWM_CAN_CHNUM > 12U ) */
#if( BSW_BSWM_CAN_CHNUM > 13U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMPRD_13
#endif /* #if( BSW_BSWM_CAN_CHNUM > 13U ) */
#if( BSW_BSWM_CAN_CHNUM > 14U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMPRD_14
#endif /* #if( BSW_BSWM_CAN_CHNUM > 14U ) */
#if( BSW_BSWM_CAN_CHNUM > 15U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMPRD_15
#endif /* #if( BSW_BSWM_CAN_CHNUM > 15U ) */
#if( BSW_BSWM_CAN_CHNUM > 16U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMPRD_16
#endif /* #if( BSW_BSWM_CAN_CHNUM > 16U ) */
#if( BSW_BSWM_CAN_CHNUM > 17U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMPRD_17
#endif /* #if( BSW_BSWM_CAN_CHNUM > 17U ) */
#if( BSW_BSWM_CAN_CHNUM > 18U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMPRD_18
#endif /* #if( BSW_BSWM_CAN_CHNUM > 18U ) */
#if( BSW_BSWM_CAN_CHNUM > 19U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMPRD_19
#endif /* #if( BSW_BSWM_CAN_CHNUM > 19U ) */
#if( BSW_BSWM_CAN_CHNUM > 20U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMPRD_20
#endif /* #if( BSW_BSWM_CAN_CHNUM > 20U ) */
#if( BSW_BSWM_CAN_CHNUM > 21U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMPRD_21
#endif /* #if( BSW_BSWM_CAN_CHNUM > 21U ) */
#if( BSW_BSWM_CAN_CHNUM > 22U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMPRD_22
#endif /* #if( BSW_BSWM_CAN_CHNUM > 22U ) */
#if( BSW_BSWM_CAN_CHNUM > 23U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMPRD_23
#endif /* #if( BSW_BSWM_CAN_CHNUM > 23U ) */
#if( BSW_BSWM_CAN_CHNUM > 24U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMPRD_24
#endif /* #if( BSW_BSWM_CAN_CHNUM > 24U ) */
#if( BSW_BSWM_CAN_CHNUM > 25U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMPRD_25
#endif /* #if( BSW_BSWM_CAN_CHNUM > 25U ) */
#if( BSW_BSWM_CAN_CHNUM > 26U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMPRD_26
#endif /* #if( BSW_BSWM_CAN_CHNUM > 26U ) */
#if( BSW_BSWM_CAN_CHNUM > 27U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMPRD_27
#endif /* #if( BSW_BSWM_CAN_CHNUM > 27U ) */
#if( BSW_BSWM_CAN_CHNUM > 28U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMPRD_28
#endif /* #if( BSW_BSWM_CAN_CHNUM > 28U ) */
#if( BSW_BSWM_CAN_CHNUM > 29U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMPRD_29
#endif /* #if( BSW_BSWM_CAN_CHNUM > 29U ) */
#if( BSW_BSWM_CAN_CHNUM > 30U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMPRD_30
#endif /* #if( BSW_BSWM_CAN_CHNUM > 30U ) */
#if( BSW_BSWM_CAN_CHNUM > 31U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMPRD_31
#endif /* #if( BSW_BSWM_CAN_CHNUM > 31U ) */
};

/* Setting of the reception deadline monitoring function            */
/* when communication startup state only with cooperative bus Awake */
BswConst BswU1 bsw_bswm_can_ctrl_u1DMCoAwkTbl[BSW_BSWM_CAN_CHNUM] = 
{
    (BswU1)BSW_BSWM_CAN_CFG_CH_DMCOAWK_0
#if( BSW_BSWM_CAN_CHNUM > 1U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMCOAWK_1
#endif /* #if( BSW_BSWM_CAN_CHNUM > 1U ) */
#if( BSW_BSWM_CAN_CHNUM > 2U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMCOAWK_2
#endif /* #if( BSW_BSWM_CAN_CHNUM > 2U ) */
#if( BSW_BSWM_CAN_CHNUM > 3U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMCOAWK_3
#endif /* #if( BSW_BSWM_CAN_CHNUM > 3U ) */
#if( BSW_BSWM_CAN_CHNUM > 4U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMCOAWK_4
#endif /* #if( BSW_BSWM_CAN_CHNUM > 4U ) */
#if( BSW_BSWM_CAN_CHNUM > 5U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMCOAWK_5
#endif /* #if( BSW_BSWM_CAN_CHNUM > 5U ) */
#if( BSW_BSWM_CAN_CHNUM > 6U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMCOAWK_6
#endif /* #if( BSW_BSWM_CAN_CHNUM > 6U ) */
#if( BSW_BSWM_CAN_CHNUM > 7U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMCOAWK_7
#endif /* #if( BSW_BSWM_CAN_CHNUM > 7U ) */
#if( BSW_BSWM_CAN_CHNUM > 8U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMCOAWK_8
#endif /* #if( BSW_BSWM_CAN_CHNUM > 8U ) */
#if( BSW_BSWM_CAN_CHNUM > 9U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMCOAWK_9
#endif /* #if( BSW_BSWM_CAN_CHNUM > 9U ) */
#if( BSW_BSWM_CAN_CHNUM > 10U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMCOAWK_10
#endif /* #if( BSW_BSWM_CAN_CHNUM > 10U ) */
#if( BSW_BSWM_CAN_CHNUM > 11U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMCOAWK_11
#endif /* #if( BSW_BSWM_CAN_CHNUM > 11U ) */
#if( BSW_BSWM_CAN_CHNUM > 12U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMCOAWK_12
#endif /* #if( BSW_BSWM_CAN_CHNUM > 12U ) */
#if( BSW_BSWM_CAN_CHNUM > 13U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMCOAWK_13
#endif /* #if( BSW_BSWM_CAN_CHNUM > 13U ) */
#if( BSW_BSWM_CAN_CHNUM > 14U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMCOAWK_14
#endif /* #if( BSW_BSWM_CAN_CHNUM > 14U ) */
#if( BSW_BSWM_CAN_CHNUM > 15U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMCOAWK_15
#endif /* #if( BSW_BSWM_CAN_CHNUM > 15U ) */
#if( BSW_BSWM_CAN_CHNUM > 16U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMCOAWK_16
#endif /* #if( BSW_BSWM_CAN_CHNUM > 16U ) */
#if( BSW_BSWM_CAN_CHNUM > 17U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMCOAWK_17
#endif /* #if( BSW_BSWM_CAN_CHNUM > 17U ) */
#if( BSW_BSWM_CAN_CHNUM > 18U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMCOAWK_18
#endif /* #if( BSW_BSWM_CAN_CHNUM > 18U ) */
#if( BSW_BSWM_CAN_CHNUM > 19U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMCOAWK_19
#endif /* #if( BSW_BSWM_CAN_CHNUM > 19U ) */
#if( BSW_BSWM_CAN_CHNUM > 20U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMCOAWK_20
#endif /* #if( BSW_BSWM_CAN_CHNUM > 20U ) */
#if( BSW_BSWM_CAN_CHNUM > 21U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMCOAWK_21
#endif /* #if( BSW_BSWM_CAN_CHNUM > 21U ) */
#if( BSW_BSWM_CAN_CHNUM > 22U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMCOAWK_22
#endif /* #if( BSW_BSWM_CAN_CHNUM > 22U ) */
#if( BSW_BSWM_CAN_CHNUM > 23U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMCOAWK_23
#endif /* #if( BSW_BSWM_CAN_CHNUM > 23U ) */
#if( BSW_BSWM_CAN_CHNUM > 24U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMCOAWK_24
#endif /* #if( BSW_BSWM_CAN_CHNUM > 24U ) */
#if( BSW_BSWM_CAN_CHNUM > 25U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMCOAWK_25
#endif /* #if( BSW_BSWM_CAN_CHNUM > 25U ) */
#if( BSW_BSWM_CAN_CHNUM > 26U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMCOAWK_26
#endif /* #if( BSW_BSWM_CAN_CHNUM > 26U ) */
#if( BSW_BSWM_CAN_CHNUM > 27U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMCOAWK_27
#endif /* #if( BSW_BSWM_CAN_CHNUM > 27U ) */
#if( BSW_BSWM_CAN_CHNUM > 28U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMCOAWK_28
#endif /* #if( BSW_BSWM_CAN_CHNUM > 28U ) */
#if( BSW_BSWM_CAN_CHNUM > 29U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMCOAWK_29
#endif /* #if( BSW_BSWM_CAN_CHNUM > 29U ) */
#if( BSW_BSWM_CAN_CHNUM > 30U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMCOAWK_30
#endif /* #if( BSW_BSWM_CAN_CHNUM > 30U ) */
#if( BSW_BSWM_CAN_CHNUM > 31U )
   ,(BswU1)BSW_BSWM_CAN_CFG_CH_DMCOAWK_31
#endif /* #if( BSW_BSWM_CAN_CHNUM > 31U ) */
};

/* bus sleep enable/disable for each channel  */
BswConst BswU1 bsw_bswm_can_ctrl_u1BsSlpUseTbl[BSW_BSWM_CAN_CHNUM] = 
{
    (BswU1)BSW_BSWM_CAN_BUSSLEEP_USE(0U)
#if( BSW_BSWM_CAN_CHNUM > 1U )
   ,(BswU1)BSW_BSWM_CAN_BUSSLEEP_USE(1U)
#endif /* #if( BSW_BSWM_CAN_CHNUM > 1U ) */
#if( BSW_BSWM_CAN_CHNUM > 2U )
   ,(BswU1)BSW_BSWM_CAN_BUSSLEEP_USE(2U)
#endif /* #if( BSW_BSWM_CAN_CHNUM > 2U ) */
#if( BSW_BSWM_CAN_CHNUM > 3U )
   ,(BswU1)BSW_BSWM_CAN_BUSSLEEP_USE(3U)
#endif /* #if( BSW_BSWM_CAN_CHNUM > 3U ) */
#if( BSW_BSWM_CAN_CHNUM > 4U )
   ,(BswU1)BSW_BSWM_CAN_BUSSLEEP_USE(4U)
#endif /* #if( BSW_BSWM_CAN_CHNUM > 4U ) */
#if( BSW_BSWM_CAN_CHNUM > 5U )
   ,(BswU1)BSW_BSWM_CAN_BUSSLEEP_USE(5U)
#endif /* #if( BSW_BSWM_CAN_CHNUM > 5U ) */
#if( BSW_BSWM_CAN_CHNUM > 6U )
   ,(BswU1)BSW_BSWM_CAN_BUSSLEEP_USE(6U)
#endif /* #if( BSW_BSWM_CAN_CHNUM > 6U ) */
#if( BSW_BSWM_CAN_CHNUM > 7U )
   ,(BswU1)BSW_BSWM_CAN_BUSSLEEP_USE(7U)
#endif /* #if( BSW_BSWM_CAN_CHNUM > 7U ) */
#if( BSW_BSWM_CAN_CHNUM > 8U )
   ,(BswU1)BSW_BSWM_CAN_BUSSLEEP_USE(8U)
#endif /* #if( BSW_BSWM_CAN_CHNUM > 8U ) */
#if( BSW_BSWM_CAN_CHNUM > 9U )
   ,(BswU1)BSW_BSWM_CAN_BUSSLEEP_USE(9U)
#endif /* #if( BSW_BSWM_CAN_CHNUM > 9U ) */
#if( BSW_BSWM_CAN_CHNUM > 10U )
   ,(BswU1)BSW_BSWM_CAN_BUSSLEEP_USE(10U)
#endif /* #if( BSW_BSWM_CAN_CHNUM > 10U ) */
#if( BSW_BSWM_CAN_CHNUM > 11U )
   ,(BswU1)BSW_BSWM_CAN_BUSSLEEP_USE(11U)
#endif /* #if( BSW_BSWM_CAN_CHNUM > 11U ) */
#if( BSW_BSWM_CAN_CHNUM > 12U )
   ,(BswU1)BSW_BSWM_CAN_BUSSLEEP_USE(12U)
#endif /* #if( BSW_BSWM_CAN_CHNUM > 12U ) */
#if( BSW_BSWM_CAN_CHNUM > 13U )
   ,(BswU1)BSW_BSWM_CAN_BUSSLEEP_USE(13U)
#endif /* #if( BSW_BSWM_CAN_CHNUM > 13U ) */
#if( BSW_BSWM_CAN_CHNUM > 14U )
   ,(BswU1)BSW_BSWM_CAN_BUSSLEEP_USE(14U)
#endif /* #if( BSW_BSWM_CAN_CHNUM > 14U ) */
#if( BSW_BSWM_CAN_CHNUM > 15U )
   ,(BswU1)BSW_BSWM_CAN_BUSSLEEP_USE(15U)
#endif /* #if( BSW_BSWM_CAN_CHNUM > 15U ) */
#if( BSW_BSWM_CAN_CHNUM > 16U )
   ,(BswU1)BSW_BSWM_CAN_BUSSLEEP_USE(16U)
#endif /* #if( BSW_BSWM_CAN_CHNUM > 16U ) */
#if( BSW_BSWM_CAN_CHNUM > 17U )
   ,(BswU1)BSW_BSWM_CAN_BUSSLEEP_USE(17U)
#endif /* #if( BSW_BSWM_CAN_CHNUM > 17U ) */
#if( BSW_BSWM_CAN_CHNUM > 18U )
   ,(BswU1)BSW_BSWM_CAN_BUSSLEEP_USE(18U)
#endif /* #if( BSW_BSWM_CAN_CHNUM > 18U ) */
#if( BSW_BSWM_CAN_CHNUM > 19U )
   ,(BswU1)BSW_BSWM_CAN_BUSSLEEP_USE(19U)
#endif /* #if( BSW_BSWM_CAN_CHNUM > 19U ) */
#if( BSW_BSWM_CAN_CHNUM > 20U )
   ,(BswU1)BSW_BSWM_CAN_BUSSLEEP_USE(20U)
#endif /* #if( BSW_BSWM_CAN_CHNUM > 20U ) */
#if( BSW_BSWM_CAN_CHNUM > 21U )
   ,(BswU1)BSW_BSWM_CAN_BUSSLEEP_USE(21U)
#endif /* #if( BSW_BSWM_CAN_CHNUM > 21U ) */
#if( BSW_BSWM_CAN_CHNUM > 22U )
   ,(BswU1)BSW_BSWM_CAN_BUSSLEEP_USE(22U)
#endif /* #if( BSW_BSWM_CAN_CHNUM > 22U ) */
#if( BSW_BSWM_CAN_CHNUM > 23U )
   ,(BswU1)BSW_BSWM_CAN_BUSSLEEP_USE(23U)
#endif /* #if( BSW_BSWM_CAN_CHNUM > 23U ) */
#if( BSW_BSWM_CAN_CHNUM > 24U )
   ,(BswU1)BSW_BSWM_CAN_BUSSLEEP_USE(24U)
#endif /* #if( BSW_BSWM_CAN_CHNUM > 24U ) */
#if( BSW_BSWM_CAN_CHNUM > 25U )
   ,(BswU1)BSW_BSWM_CAN_BUSSLEEP_USE(25U)
#endif /* #if( BSW_BSWM_CAN_CHNUM > 25U ) */
#if( BSW_BSWM_CAN_CHNUM > 26U )
   ,(BswU1)BSW_BSWM_CAN_BUSSLEEP_USE(26U)
#endif /* #if( BSW_BSWM_CAN_CHNUM > 26U ) */
#if( BSW_BSWM_CAN_CHNUM > 27U )
   ,(BswU1)BSW_BSWM_CAN_BUSSLEEP_USE(27U)
#endif /* #if( BSW_BSWM_CAN_CHNUM > 27U ) */
#if( BSW_BSWM_CAN_CHNUM > 28U )
   ,(BswU1)BSW_BSWM_CAN_BUSSLEEP_USE(28U)
#endif /* #if( BSW_BSWM_CAN_CHNUM > 28U ) */
#if( BSW_BSWM_CAN_CHNUM > 29U )
   ,(BswU1)BSW_BSWM_CAN_BUSSLEEP_USE(29U)
#endif /* #if( BSW_BSWM_CAN_CHNUM > 29U ) */
#if( BSW_BSWM_CAN_CHNUM > 30U )
   ,(BswU1)BSW_BSWM_CAN_BUSSLEEP_USE(30U)
#endif /* #if( BSW_BSWM_CAN_CHNUM > 30U ) */
#if( BSW_BSWM_CAN_CHNUM > 31U )
   ,(BswU1)BSW_BSWM_CAN_BUSSLEEP_USE(31U)
#endif /* #if( BSW_BSWM_CAN_CHNUM > 31U ) */
};

/* Setting to enable/disable register sticking check */
BswConst       BswU1 bsw_bswm_can_ctrl_u1RegChk = (BswU1)BSW_BSWM_CAN_CFG_RGSTCHK;

/* Setting to register sticking check start timing at wake-up */
BswConst       BswU1 bsw_bswm_can_ctrl_u1WpRgCkStart = (BswU1)BSW_BSWM_CAN_CFG_WURGSTCHKSTART;

/* Transmission limitation function */
void (* BswConst bsw_bswm_can_ctrl_ptIntTxCtrFnc)( void ) = BSW_BSWM_CAN_FUNC_INTTXSTCTRL;
BswU1 (* BswConst bsw_bswm_can_ctrl_ptUpdTxCtrFnc)( BswU1 u1Channel, BswU1 u1PeriReset ) = BSW_BSWM_CAN_FUNC_UPDTXSTCTRL;
void (* BswConst bsw_bswm_can_ctrl_ptCntTmTxFnc)( BswU1 u1Channel ) = BSW_BSWM_CAN_FUNC_CNTTIMTXCTRL;

/* Channel Restart Function */
void (* BswConst bsw_bswm_can_ctrl_ptIntRstChFnc)( void ) = BSW_BSWM_CAN_FUNC_INTRSTCHCTRL;

/* Receive disconnection monitoring function */
void (* BswConst bsw_bswm_can_ctrl_ptIntDmCtrFnc)( void ) = BSW_BSWM_CAN_FUNC_INTDMCTRL;
void (* BswConst bsw_bswm_can_ctrl_ptUpdDmCtrFnc)( BswU1 u1Channel, BswU4* u4DmGroup ) = BSW_BSWM_CAN_FUNC_UPDDMCTRL;

/* Disable diagnostic transmission frame transmission enable */
void (* BswConst bsw_bswm_can_ctrl_ptTPEnTxFunc)( NetworkHandleType Network ) = BSW_BSWM_CAN_FUNC_TPENABLETX;
void (* BswConst bsw_bswm_can_ctrl_ptTPDisTxFunc)( NetworkHandleType Network ) = BSW_BSWM_CAN_FUNC_TPDISABLETX;

/*------------------------------------------*/
/* Unit:State management                       */
/*------------------------------------------*/
#if ( BSW_BSWM_CS_ECU_FAIL == BSW_NOUSE )
void (* BswConst bsw_bswm_can_st_ptTPChkRamFunc)( void ) = BSW_BSWM_CAN_FUNC_CHECKRAM;
#endif

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#endif /* ( BSW_BSWM_CS_FUNC_BSWMCAN == BSW_USE ) */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/04/28                                             */
/*  v1-1-0          :2018/12/14                                             */
/*  v2-0-0          :2021/12/02                                             */
/*  v2-1-0          :2022/05/24                                             */
/*  v3-0-0          :2024/11/13                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
