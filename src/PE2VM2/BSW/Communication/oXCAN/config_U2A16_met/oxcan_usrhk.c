/* 1.0.5 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Oem eXtention of CAN User Hooks                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_USRHK_C_MAJOR                      (1U)
#define OXCAN_USRHK_C_MINOR                      (0U)
#define OXCAN_USRHK_C_PATCH                      (5U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"

#include "Dio.h"
/*#include "icu_drv_wk.h"*/

/*#include "gpt_busywait.h"*/

#include "oxcan.h"
#include "oxcan_usrhk.h"
#include "can_rscf4_cfg.h"      /* CAN_CFG_CONTROLLERNUM_MAX is defined in can_rscf4_cfg.h */

/*#include "tydocan_dtc_nmgbl.h"  *//* NM Diag  Detection of abnormal global-ecu */

#include "oxcan_lib.h"

#include "x_spi_ivi_sub4.h"

#if (OXCAN_IC_TJA1145_USE == 1U)
#include "Cdd_Canic.h"
#endif /* #if (OXCAN_IC_TJA1145_USE == 1U) */

#include "PictCtl.h"

#include "l3r_test.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((OXCAN_USRHK_C_MAJOR != OXCAN_USRHK_H_MAJOR) || \
     (OXCAN_USRHK_C_MINOR != OXCAN_USRHK_H_MINOR) || \
     (OXCAN_USRHK_C_PATCH != OXCAN_USRHK_H_PATCH))
#error "oxcan_usrhk.c and oxcan_usrhk.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_AUBCS_STB_BUSY_WAIT                (12U)                    /* 12 [us] */
#define OXCAN_AUBCS_NUM_CTRLR                    (CAN_CFG_CONTROLLERNUM_MAX)
#if (OXCAN_NMDIAG_GBL_SUP == 1U)
#define OXCAN_AUBCS_CANIF_MSK_CANID              (0x1FFFFFFFUL)           /* BSW_CANIF_u4MSK_CAN29BITID */
#endif  /* #if (OXCAN_NMDIAG_GBL_SUP == 1U) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U4    u4_iext_chbit;
    U1    u1_iext_ch;
}ST_OXCAN_AUBCS_IEXT;

typedef struct{
    U1    u1_selective_use;
    U2    u2_dio_ch;
}ST_OXCAN_AUBCS_TRCV;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (CAN_CFG_CONTROLLERNUM_MAX != 0U)
static const ST_OXCAN_AUBCS_IEXT    st_sp_OXCAN_AUBCS_IEXT_CH[OXCAN_AUBCS_NUM_CTRLR] = {
    {
        (U4)0x00000000U,               /* u4_iext_chbit */
        (U1)U1_MAX                     /* u1_iext_ch    */
    },
    {
        (U4)0x00000000U,               /* u4_iext_chbit */
        (U1)U1_MAX                     /* u1_iext_ch    */
    },
    {
        (U4)0x00000000U,               /* u4_iext_chbit */
        (U1)U1_MAX                     /* u1_iext_ch    */
    },
    {
        (U4)0x00000000U,               /* u4_iext_chbit */
        (U1)U1_MAX                     /* u1_iext_ch    */
    },
    {
        (U4)0x00000000U,               /* u4_iext_chbit */
        (U1)U1_MAX                     /* u1_iext_ch    */
    },
    {
        (U4)0x00000000U,              /* u4_iext_chbit */
        (U1)U1_MAX                    /* u1_iext_ch    */
    },
    {
        (U4)0x00000000U,               /* u4_iext_chbit */
        (U1)U1_MAX                     /* u1_iext_ch    */
    },
    {
        (U4)0x00000000U,               /* u4_iext_chbit */
        (U1)U1_MAX                     /* u1_iext_ch    */
    }
};
#endif /* #if (CAN_CFG_CONTROLLERNUM_MAX != 0U) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const ST_OXCAN_AUBCS_TRCV     st_sp_OXCAN_AUBCS_TRCV_INFO[BSW_COM_CFG_CHNUM] = {
    /* u1_selective_use      u2_dio_ch                        */
    { (U1)FALSE,             (U2)U2_MAX                       }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_oXCANUsrhkExirEnaCh(const U1 u1_a_CTRLR)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANUsrhkExirEnaCh(const U1 u1_a_CTRLR)
{
#if (CAN_CFG_CONTROLLERNUM_MAX != 0U)
    if(u1_a_CTRLR < (U1)OXCAN_AUBCS_NUM_CTRLR){
        vd_g_IcuWkSetCh(st_sp_OXCAN_AUBCS_IEXT_CH[u1_a_CTRLR].u1_iext_ch,
                           ((U1)ICU_WK_CFGBIT_ELC_FA | (U1)ICU_WK_CFGBIT_WRQ_ENA));
    }
#endif /* #if (CAN_CFG_CONTROLLERNUM_MAX != 0U) */
}
/*===================================================================================================================================*/
/*  void    vd_g_oXCANUsrhkExirDisCh(const U1 u1_a_CTRLR)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANUsrhkExirDisCh(const U1 u1_a_CTRLR)
{
#if (CAN_CFG_CONTROLLERNUM_MAX != 0U)
    if(u1_a_CTRLR < (U1)OXCAN_AUBCS_NUM_CTRLR){
        vd_g_IcuWkSetCh(st_sp_OXCAN_AUBCS_IEXT_CH[u1_a_CTRLR].u1_iext_ch, (U1)ICU_WK_CFGBIT_ELC_FA);
    }
#endif /* #if (CAN_CFG_CONTROLLERNUM_MAX != 0U) */
}
/*===================================================================================================================================*/
/*  void    vd_g_oXCANUsrhkExirClrIRQst(const U1 u1_a_CTRLR)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANUsrhkExirClrIRQst(const U1 u1_a_CTRLR)
{
#if (CAN_CFG_CONTROLLERNUM_MAX != 0U)
    if(u1_a_CTRLR < (U1)OXCAN_AUBCS_NUM_CTRLR){
        (void)u4_g_IcuWkRQst((U1)ICU_WK_GR_A0,st_sp_OXCAN_AUBCS_IEXT_CH[u1_a_CTRLR].u4_iext_chbit, (U1)TRUE);
    }
#endif /* #if (CAN_CFG_CONTROLLERNUM_MAX != 0U) */
}
/*===================================================================================================================================*/
/*  U4      u4_g_oXCANUsrhkExirIRQst(const U1 u1_a_CTRLR)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4      u4_g_oXCANUsrhkExirIRQst(const U1 u1_a_CTRLR)
{
    U4          u4_t_irqbit;
#if (CAN_CFG_CONTROLLERNUM_MAX != 0U)
    if(u1_a_CTRLR < (U1)OXCAN_AUBCS_NUM_CTRLR){
        u4_t_irqbit  = u4_g_IcuWkRQst((U1)ICU_WK_GR_A0,st_sp_OXCAN_AUBCS_IEXT_CH[u1_a_CTRLR].u4_iext_chbit, (U1)FALSE);
        u4_t_irqbit &= u4_g_IcuWkRQenabled((U1)ICU_WK_GR_A0);
        u4_t_irqbit  = (U4)0U;
    }
    else{
        u4_t_irqbit  = (U4)0U;
    }
#else
    u4_t_irqbit = (U4)0U;
#endif /* #if (CAN_CFG_CONTROLLERNUM_MAX != 0U) */

    return(u4_t_irqbit);
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXCANUsrhkPwonBusAwake(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXCANUsrhkPwonBusAwake(void)
{
    return((U1)E_OK);
}
/*===================================================================================================================================*/
/*  void    vd_g_oXCANUsrhkTrcvToAct(const U1 u1_a_CH)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANUsrhkTrcvToAct(const U1 u1_a_CH)
{
    if(u1_a_CH                             <  (U1)BSW_COM_CFG_CHNUM){
#if (OXCAN_IC_TJA1145_USE == 1U)
        if(st_sp_OXCAN_AUBCS_TRCV_INFO[u1_a_CH].u1_selective_use == (U1)TRUE){
            Cdd_Canic_SetControlMode(u1_a_CH, u1CDD_CANIC_MC_NORMAL);
        } else {
            /* Do Nothing */
        }
#endif /* #if (OXCAN_IC_TJA1145_USE == 1U) */
        if(st_sp_OXCAN_AUBCS_TRCV_INFO[u1_a_CH].u2_dio_ch <= (U2)DIO_ASSIGN_ID_CH_MAX    ){
            Dio_WriteChannel(st_sp_OXCAN_AUBCS_TRCV_INFO[u1_a_CH].u2_dio_ch, (U1)STD_LOW);
/*------------------------------------------------------------------------------------*/
/*        vd_g_Gpt_BusyWait((U2)OXCAN_AUBCS_STB_BUSY_WAIT * (U2)GPT_BUSY_WAIT_1_US);*/
/*------------------------------------------------------------------------------------*/
        } else {
            /* Do Nothing */
        }
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_oXCANUsrhkTrcvToInact(const U1 u1_a_CH)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANUsrhkTrcvToInact(const U1 u1_a_CH)
{
    if(u1_a_CH                             <  (U1)BSW_COM_CFG_CHNUM){
#if (OXCAN_IC_TJA1145_USE == 1U)
        if(st_sp_OXCAN_AUBCS_TRCV_INFO[u1_a_CH].u1_selective_use == (U1)TRUE){
            Cdd_Canic_SetControlMode(u1_a_CH, u1CDD_CANIC_MC_SLEEP);
        } else {
            /* Do Nothing */
        }
#endif /* #if (OXCAN_IC_TJA1145_USE == 1U) */
        if(st_sp_OXCAN_AUBCS_TRCV_INFO[u1_a_CH].u2_dio_ch <= (U2)DIO_ASSIGN_ID_CH_MAX    ){

            Dio_WriteChannel(st_sp_OXCAN_AUBCS_TRCV_INFO[u1_a_CH].u2_dio_ch, (U1)STD_HIGH);
/*------------------------------------------------------------------------------------*/
/*        vd_g_Gpt_BusyWait((U2)OXCAN_AUBCS_STB_BUSY_WAIT * (U2)GPT_BUSY_WAIT_1_US);*/
/*------------------------------------------------------------------------------------*/
        } else {
            /* Do Nothing */
        }
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_oXCANUsrhkEvtxReqed(const U2 u2_a_MSG)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_MSG         : Message Handler                                                                           */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANUsrhkEvtxReqed(const U2 u2_a_MSG)
{
    /* -------------------------------------------------------------------------------------------------- */
    /*  Attention :                                                                                       */
    /* -------------------------------------------------------------------------------------------------- */
    /* vd_g_oXCANUsrhkEvtxReqed is invoked at Com_SendSignal(...) and/or Com_TriggerIPDUSend(...).        */
    /* -------------------------------------------------------------------------------------------------- */
}
/*===================================================================================================================================*/
/*  void    vd_g_oXCANUsrhkTxConfirm(const U2 u2_a_MSG, const U1 u1_a_CH, const U1 u1_a_TXMODE)                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_MSG         : Message Handler                                                                           */
/*                  --> u1_a_CH          : Subnet Channel                                                                            */
/*                  --> u1_a_TXMODE      : Tx Mode                                                                                   */
/*                          COM_TX_MODE_EVENT                                                                                        */
/*                          COM_TX_MODE_PERIODIC                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANUsrhkTxConfirm(const U2 u2_a_MSG, const U1 u1_a_CH, const U1 u1_a_TXMODE)
{
    /* -------------------------------------------------------------------------------------------------- */
    /* WARNING :                                                                                          */
    /* -------------------------------------------------------------------------------------------------- */
    /* 1. vd_g_oXCANUsrhkTxAck notifies the timing when the transmission of the message to the bus is     */
    /*    completed.                                                                                      */
    /*    vd_g_oXCANUsrhkTxConfirm notifies the timing when the transmission request of the message       */
    /*    from the COM layer to the DRIVER layer.                                                         */
    /*    vd_g_oXCANUsrhkEvtTxCallout notifies the timing when the event tx request is accepted the COM   */ 
    /*    layer.                                                                                          */
    /*                                                                                                    */
    /* 2. vd_g_oXCANUsrhkTxConfirm is called from BswM_CS_MainFunctionMiddle or BswM_CS_MainFunctionHigh  */
    /*    depending on following configuration :                                                          */
    /*                                                                                                    */
    /*    BswM_CS\cfg\BswM_CS_Cfg.h                                                                       */
    /*    #define BSW_BSWM_CS_CFG_MSGDELIVER                                                              */
    /*                                                                                                    */
    /*    If BSW_BSWM_CS_CFG_MSGDELIVER is configured with BSWM_CS_MSGDELIVER_HIGH,                       */
    /*    vd_g_oXCANUsrhkTxConfirm could be called from interrupts service routine. Therefore, user shall */
    /*    verify if RAM sharing issue will not be caused.                                                 */
    /* -------------------------------------------------------------------------------------------------- */

    /* Users Configuration */

    vd_g_L3rTestTxAck(u2_a_MSG);

    /* Sample Code */
/*  switch(u2_a_MSG)                        */
/*  {                                       */
/*      case MSG_MET1S01_Tx_CH0:            */
/*          vd_g_DimRheoPostTxRheoHook();   */
/*          break;                          */
/*      case MSG_MET1S19_Tx_CH0:            */
/*          vd_g_VardefMmColorPostTxHook(); */
/*          break;                          */
/*      default:                            */
/*          break;                          */
/*  }                                       */
}
/*===================================================================================================================================*/
/*  void    vd_g_oXCANUsrhkTxAck(const U2 u2_a_MSG)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_MSG         : Message Handler                                                                           */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANUsrhkTxAck(const U2 u2_a_MSG)
{
    /* -------------------------------------------------------------------------------------------------- */
    /* WARNING :                                                                                          */
    /* -------------------------------------------------------------------------------------------------- */
    /* 1. vd_g_oXCANUsrhkTxAck notifies the timing when the transmission of the message to the bus is     */
    /*    completed.                                                                                      */
    /*    vd_g_oXCANUsrhkTxConfirm notifies the timing when the transmission request of the message       */
    /*    from the COM layer to the DRIVER layer.                                                         */
    /*    vd_g_oXCANUsrhkEvtTxCallout notifies the timing when the event tx request is accepted the COM   */ 
    /*    layer.                                                                                          */
    /*                                                                                                    */
    /* 2. vd_g_oXCANUsrhkTxAck is called from BswM_CS_MainFunctionMiddle or BswM_CS_MainFunctionHigh      */
    /*    depending on following configuration :                                                          */
    /*                                                                                                    */
    /*    BswM_CS\cfg\BswM_CS_Cfg.h                                                                       */
    /*    #define BSW_BSWM_CS_CFG_MSGDELIVER                                                              */
    /*                                                                                                    */
    /*    If BSW_BSWM_CS_CFG_MSGDELIVER is configured with BSWM_CS_MSGDELIVER_HIGH, vd_g_oXCANUsrhkTxAck  */
    /*    could be called from interrupts service routine. Therefore, user shall verify if RAM sharing    */
    /*    issue will not be caused.                                                                       */
    /* -------------------------------------------------------------------------------------------------- */

    /* Users Configuration */

    /* Sample Code */
/*  switch(u2_a_MSG)                        */
/*  {                                       */
/*      case MSG_MET1S01_Tx_CH0:            */
/*          vd_g_DimRheoPostTxRheoHook();   */
/*          break;                          */
/*      case MSG_MET1S19_Tx_CH0:            */
/*          vd_g_VardefMmColorPostTxHook(); */
/*          break;                          */
/*      default:                            */
/*          break;                          */
/*  }                                       */
}
/*===================================================================================================================================*/
/*  void    vd_g_oXCANUsrhkRxMsg(const U2 u2_a_MSG)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_MSG : Message Handler                                                                                   */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANUsrhkRxMsg(const U2 u2_a_MSG)
{
    /* ---------------------------------------------------------------------------------------------------- */
    /* WARNING :                                                                                            */
    /* ---------------------------------------------------------------------------------------------------- */
    /* vd_g_oXCANUsrhkRxMsg is called from BswM_CS_MainFunctionMiddle or BswM_CS_MainFunctionHigh           */
    /* depending on following configuration :                                                               */
    /*                                                                                                      */
    /* BswM_CS\cfg\BswM_CS_Cfg.h                                                                            */
    /* #define BSW_BSWM_CS_CFG_MSGDELIVER                                                                   */
    /*                                                                                                      */
    /* If BSW_BSWM_CS_CFG_MSGDELIVER is configured with BSWM_CS_MSGDELIVER_HIGH, vd_g_oXCANUsrhkRxMsg       */
    /* could be called from interrupts service routine. Therefore, user shall verify if RAM sharing issue   */
    /* will not be caused.                                                                                  */
    /* ---------------------------------------------------------------------------------------------------- */

    /* Users Configuration */

    vd_g_L3rTestRxAck(u2_a_MSG);

    /* Sample Code */
/*  switch(u2_a_MSG)                                        */
/*  {                                                       */
/*      case MSG_EPS1S90_Rx_CH0:                            */
/*          vd_g_BzEpsRxSnglbzer();                         */
/*          vd_g_WrnEpsRx();                                */
/*          vd_g_TtEpsRxEpsWlmp();                          */
/*          JdgEpsRxHook();                                 */
/*          vd_g_BzEpsRxIntbzer();                          */
/*          vd_g_RmtRxCntClrHook((U1)RMTDTSGNL_EPS_METD);   */
/*          break;                                          */
/*      case MSG_CSR1S04_Rx_CH0:                            */
/*          vd_g_VardefIcsRxChk();                          */
/*          break;                                          */
/*      default:                                            */
/*          break;                                          */
/*  }                                                       */

    vd_g_XspiIviCANGWPushPDU(u2_a_MSG);

	switch(u2_a_MSG)
	{
	    case MSG_BCC1S05_RXCH0:
	        vd_g_PictCtl_RcvBCC1S05();
	        break;
	    default:
	        break;
	}
}
/*===================================================================================================================================*/
/*  void    vd_g_oXCANUsrhkNwToAct(const U1 u1_a_CH)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANUsrhkNwToAct(const U1 u1_a_CH)
{
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXCANUsrhkCntChk(const U2 u2_a_MSG, const U1 u1_a_CHKRST, const U1 u1_a_PREV, const U1 u1_a_NEXT)                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXCANUsrhkCntChk(const U2 u2_a_MSG, const U1 u1_a_CHKRST, const U1 u1_a_PREV, const U1 u1_a_NEXT)
{
    return((U1)TRUE);
}
/*===================================================================================================================================*/
/*  void    vd_g_oXCANUsrhkSumErr(const U2 u2_a_PDUID)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANUsrhkSumErr(const U2 u2_a_PDUID)
{
}
/*===================================================================================================================================*/
/*  void    vd_g_oXCANUsrhkDlcErr(const U2 u2_a_PDUID)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANUsrhkDlcErr(const U2 u2_a_PDUID)
{
}
#if (OXCAN_NMDIAG_GBL_SUP == 1U)
/*===================================================================================================================================*/
/*  void    vd_g_oXCANUsrhkPreStoreMsg(const U1 u1_a_CH, const U4 u4_a_CANID)                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u1_a_CH         : Channel                                                                                    */
/*                  --> u4_a_CANID      : CAN ID                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANUsrhkPreStoreMsg(const U1 u1_a_CH, const U4 u4_a_CANID)
{
    U4  u4_t_canid;

    u4_t_canid = u4_a_CANID & (U4)OXCAN_AUBCS_CANIF_MSK_CANID;
    vd_g_TyDoCANDtcNmGblPreStoreMsg(u1_a_CH, u4_t_canid);
}
#endif  /* #if (OXCAN_NMDIAG_GBL_SUP == 1U) */
/*===================================================================================================================================*/
/*  void    vd_g_oXCANUsrhkTxTOut(const U2 u2_a_MSG)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_MSG         : Message Handler                                                                           */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANUsrhkTxTOut(const U2 u2_a_MSG)
{
}
/*===================================================================================================================================*/
/*  void    vd_g_oXCANUsrhkDetectBusoff(const U1 u1_a_NW)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u1_a_NW         : Network Handler                                                                            */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANUsrhkDetectBusoff(const U1 u1_a_NW)
{
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     2/22/2022  HU       ty19epf_ren_d1x_v220_r009 -> ox25epf_ren_d1x_v100_r000.                                            */
/*  1.0.1     9/27/2022  TM       vd_g_oXCANUsrhkDetectBusoff and u1_g_oXCANUsrhkPwonBusAwake were implemented.                      */
/*  1.0.2    10/26/2022  HU       vd_g_oXCANUsrhkSumErr was implemented.                                                             */
/*                                u1_g_oXCANUsrhkCnterr -> u1_g_oXCANUsrhkCntChk                                                     */
/*  1.0.3     2/07/2022  TM       vd_g_oXCANUsrhkDlcErr was implemented.                                                             */
/*  1.0.4    12/27/2023  ST       vd_g_oXCANUsrhkSumErr/vd_g_oXCANUsrhkDlcErr changed the argument name.                             */
/*  1.0.5     1/10/2024  TI       vd_g_oXCANUsrhkPreStoreMsg was implemented.                                                        */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*  * HU   = Hayato Usui, DENSO                                                                                                      */
/*  * TM   = Takanori Maruyama, DENSO                                                                                                */
/*  * ST   = Satoshi Tanaka, DENSO                                                                                                   */
/*  * TI   = Tomoko Inuzuka, DENSO                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
