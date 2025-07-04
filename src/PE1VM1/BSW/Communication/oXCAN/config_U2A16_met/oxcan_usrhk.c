/* 2.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Oem eXtention of CAN User Hooks                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_USRHK_C_MAJOR                      (2U)
#define OXCAN_USRHK_C_MINOR                      (0U)
#define OXCAN_USRHK_C_PATCH                      (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "oxcan.h"
#include "oxcan_usrhk.h"

#include "can_rscf4_cfg.h"      /* CAN_CFG_CONTROLLERNUM_MAX is defined in can_rscf4_cfg.h */


#include "illumi_comtx.h"
#include "drec_tx.h"
#include "mulmed_mulfr.h"
#include "mulmed_color.h"
#include "fspomgr.h"
#include "mmappctrl.h"
#include "xspi_met_can.h"

#if (CAN_CFG_CONTROLLERNUM_MAX > 0U)
#include "icu_drv_wk.h"
#include "Dio.h"
#include "Cdd_Canic.h"
#endif

/* #include "can_lpr_test.h" */

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
#define OXCAN_TRCV_SPI                           (0xfffeU)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U4    u4_wrq;
    U1    u1_ch;
}ST_OXCAN_ICU_RX;

#if 0   /* BEV BSW provisionally */
typedef struct{
    U2               u2_msg;
    void (* const    fp_vd_HOOK)(const U2 u2_a_MSG);
}ST_OXCAN_USRHK_MMAPP;
#else
#endif
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void vd_s_oXCANUsrhkMmappRxMsg(const U2 u2_a_MSG);
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (CAN_CFG_CONTROLLERNUM_MAX > 0U)
static const ST_OXCAN_ICU_RX      st_sp_OXCAN_ICU_RX_BY_CTRL[CAN_CFG_CONTROLLERNUM_MAX] = {
    {
        (U4)0x00000000U,               /* u4_wrq */
        (U1)U1_MAX                     /* u1_ch  */
    },
    {
        (U4)0x00000000U,               /* u4_wrq */
        (U1)U1_MAX                     /* u1_ch  */
    },
    {
        (U4)0x00000000U,               /* u4_wrq */
        (U1)U1_MAX                     /* u1_ch  */
    },
    {
        (U4)0x00000000U,               /* u4_wrq */
        (U1)U1_MAX                     /* u1_ch  */
    },
    {
        (U4)0x00000000U,               /* u4_wrq */
        (U1)U1_MAX                     /* u1_ch  */
    },
    {
        (U4)0x00000000U,               /* u4_wrq */
        (U1)U1_MAX                     /* u1_ch  */
    },
    {
        (U4)0x00000000U,               /* u4_wrq */
        (U1)U1_MAX                     /* u1_ch  */
    },
    {
        (U4)0x00000000U,               /* u4_wrq */
        (U1)U1_MAX                     /* u1_ch  */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U2               u2_sp_OXCAN_TRCV_BY_CH[BSW_COM_CFG_CHNUM] = {
    (U2)U2_MAX                  /* Virtual CAN      */
};
#endif /* #if (CAN_CFG_CONTROLLERNUM_MAX > 0U) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_oXCANUsrhkWRQDet(const U1 u1_a_CTRLR, const U1 u1_a_ENA)                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANUsrhkWRQDet(const U1 u1_a_CTRLR, const U1 u1_a_ENA)     /* called from oxcan_aubif.c :: Can_UEdgeEnableDetect  */
                                                                          /* called from oxcan_aubif.c :: Can_UEdgeDisableDetect */
{
#if (CAN_CFG_CONTROLLERNUM_MAX > 0U)
    if(u1_a_CTRLR >= (U1)CAN_CFG_CONTROLLERNUM_MAX){
        /* do nothing */
    }
    else if(u1_a_ENA == (U1)TRUE){
        vd_g_IcuWkSetCh(st_sp_OXCAN_ICU_RX_BY_CTRL[u1_a_CTRLR].u1_ch, ((U1)ICU_WK_CFGBIT_ELC_FA | (U1)ICU_WK_CFGBIT_WRQ_ENA));
    }
    else{
        vd_g_IcuWkSetCh(st_sp_OXCAN_ICU_RX_BY_CTRL[u1_a_CTRLR].u1_ch,  (U1)ICU_WK_CFGBIT_ELC_FA                             );
    }
#endif /* #if (CAN_CFG_CONTROLLERNUM_MAX > 0U) */
}
/*===================================================================================================================================*/
/*  U4      u4_g_oXCANUsrhkWRQst(const U1 u1_a_CTRLR, const U1 u1_a_W_CLR)                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4      u4_g_oXCANUsrhkWRQst(const U1 u1_a_CTRLR, const U1 u1_a_W_CLR)    /* called from oxcan_aubif.c :: Can_UEdgeClearStatus   */
                                                                          /* called from oxcan_aubif.c :: Can_UEdgeGetStatus     */
{
#if (CAN_CFG_CONTROLLERNUM_MAX > 0U)
    U4          u4_t_wrqbit;

    if(u1_a_CTRLR >= (U1)CAN_CFG_CONTROLLERNUM_MAX){
        u4_t_wrqbit  = (U4)0U;
    }
    else if(u1_a_W_CLR == (U1)TRUE){
        u4_t_wrqbit  = u4_g_IcuWkRQst((U1)ICU_WK_GR_A0, st_sp_OXCAN_ICU_RX_BY_CTRL[u1_a_CTRLR].u4_wrq, (U1)TRUE);
    }
    else{
        u4_t_wrqbit  = u4_g_IcuWkRQst((U1)ICU_WK_GR_A0, st_sp_OXCAN_ICU_RX_BY_CTRL[u1_a_CTRLR].u4_wrq, (U1)FALSE);
        u4_t_wrqbit &= u4_g_IcuWkRQenabled((U1)ICU_WK_GR_A0);
    }

    return(u4_t_wrqbit);
#else
    return((U4)0U);
#endif /* #if (CAN_CFG_CONTROLLERNUM_MAX != 0U) */
}
/*===================================================================================================================================*/
/*  void    vd_g_oXCANUsrhkTrcvToAct(const U1 u1_a_CH)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANUsrhkTrcvToAct(const U1 u1_a_CH)
{
#if (CAN_CFG_CONTROLLERNUM_MAX > 0U)
    if(u1_a_CH >= (U1)BSW_COM_CFG_CHNUM){
        /* Do Nothing */
    }
    else if(u2_sp_OXCAN_TRCV_BY_CH[u1_a_CH] == (U2)OXCAN_TRCV_SPI){
        Cdd_Canic_SetControlMode(u1_a_CH, u1CDD_CANIC_MC_NORMAL);
    }
    else if(u2_sp_OXCAN_TRCV_BY_CH[u1_a_CH] <= (U2)DIO_ASSIGN_ID_CH_MAX){
        Dio_WriteChannel(u2_sp_OXCAN_TRCV_BY_CH[u1_a_CH], (U1)STD_LOW);
    }
    else{
        /* Do Nothing */
    }
#endif
}
/*===================================================================================================================================*/
/*  void    vd_g_oXCANUsrhkTrcvToIna(const U1 u1_a_CH)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANUsrhkTrcvToIna(const U1 u1_a_CH)
{
#if (CAN_CFG_CONTROLLERNUM_MAX > 0U)
    if(u1_a_CH >= (U1)BSW_COM_CFG_CHNUM){
        /* Do Nothing */
    }
    else if(u2_sp_OXCAN_TRCV_BY_CH[u1_a_CH] == (U2)OXCAN_TRCV_SPI){
        Cdd_Canic_SetControlMode(u1_a_CH, u1CDD_CANIC_MC_SLEEP);
    }
    else if(u2_sp_OXCAN_TRCV_BY_CH[u1_a_CH] <= (U2)DIO_ASSIGN_ID_CH_MAX){
        Dio_WriteChannel(u2_sp_OXCAN_TRCV_BY_CH[u1_a_CH], (U1)STD_HIGH);
    }
    else{
        /* Do Nothing */
    }
#endif
}
/*===================================================================================================================================*/
/*  void    vd_g_oXCANUsrhkTraReq(const U1 u1_a_CH, const U2 u2_a_IPDU_TX, const U1 u1_a_TXMODE)                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_IPDU_TX     : u2_a_IPDU_TX is defined as MSG_[IPDU_NAME]_TXCH[n] in Aubist/Com/../Com_Cfg.h             */
/*                  --> u1_a_CH          : Subnet Channel                                                                            */
/*                  --> u1_a_TXMODE      : Tx Mode                                                                                   */
/*                          COM_TX_MODE_EVENT                                                                                        */
/*                          COM_TX_MODE_PERIODIC                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANUsrhkTraReq(const U1 u1_a_CH, const U2 u2_a_IPDU_TX, const U1 u1_a_TXMODE)
{
    /* -------------------------------------------------------------------------------------------------- */
    /* WARNING :                                                                                          */
    /* -------------------------------------------------------------------------------------------------- */
    /* 1. vd_g_oXCANUsrhkTraReq notifies the timing when the transmission request of the message from COM */
    /*    layer to the DRIVER layer.                                                                      */
    /*                                                                                                    */
    /* 2. vd_g_oXCANUsrhkTraReq is called from BswM_CS_MainFunctionMiddle or BswM_CS_MainFunctionHigh     */
    /*    depending on following configuration :                                                          */
    /*                                                                                                    */
    /*    BswM_CS\cfg\BswM_CS_Cfg.h                                                                       */
    /*    #define BSW_BSWM_CS_CFG_MSGDELIVER                                                              */
    /*                                                                                                    */
    /*    If BSW_BSWM_CS_CFG_MSGDELIVER is configured with BSWM_CS_MSGDELIVER_HIGH,                       */
    /*    vd_g_oXCANUsrhkTraReq could be called from interrupts service routine.                          */
    /*    Therefore, user shall verify if RAM sharing issue will not be caused.                           */
    /* -------------------------------------------------------------------------------------------------- */

    /* Users Configuration */

#ifdef CAN_LPR_TEST_H
    vd_g_CANLpRTestTxAck(u2_a_IPDU_TX);
#endif /* #ifdef CAN_LPR_TEST_H */

    /* Sample Code */
/*  switch(u2_a_IPDU_TX)                    */
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
/*  void    vd_g_oXCANUsrhkTraAck(const U2 u2_a_IPDU_TX)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_IPDU_TX     : u2_a_IPDU_TX is defined as MSG_[IPDU_NAME]_TXCH[n] in Aubist/Com/../Com_Cfg.h             */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANUsrhkTraAck(const U2 u2_a_IPDU_TX)
{
    /* -------------------------------------------------------------------------------------------------- */
    /* WARNING :                                                                                          */
    /* -------------------------------------------------------------------------------------------------- */
    /* 1. vd_g_oXCANUsrhkTraAck notifies the timing when the transmission request of the message from     */
    /*    the COM layer to the DRIVER layer.                                                              */
    /*                                                                                                    */
    /* 2. vd_g_oXCANUsrhkTraAck is called from BswM_CS_MainFunctionMiddle or BswM_CS_MainFunctionHigh     */
    /*    depending on following configuration :                                                          */
    /*                                                                                                    */
    /*    BswM_CS\cfg\BswM_CS_Cfg.h                                                                       */
    /*    #define BSW_BSWM_CS_CFG_MSGDELIVER                                                              */
    /*                                                                                                    */
    /*    If BSW_BSWM_CS_CFG_MSGDELIVER is configured with BSWM_CS_MSGDELIVER_HIGH,                       */
    /*    vd_g_oXCANUsrhkTraAck could be called from interrupts service routine.                          */
    /*    Therefore, user shall verify if RAM sharing issue will not be caused.                           */
    /* -------------------------------------------------------------------------------------------------- */

    /* Users Configuration */

    /* Sample Code */
/*  switch(u2_a_IPDU_TX)                    */
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

    switch (u2_a_IPDU_TX) {
        case (U2)MSG_MET1S01_TXCH0:
            vd_g_IllumiRheoTxAck();
            break;
        default:
            /* Do nothing */
            break;
    }

    vd_g_DrectxTxAck(u2_a_IPDU_TX);
    vd_g_MulmedColorTxHk(u2_a_IPDU_TX);
}
/*===================================================================================================================================*/
/*  void    vd_g_oXCANUsrhkRecAck(const U2 u2_a_IPDU_RX)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_IPDU_RX     : u2_a_IPDU_RX is defined as MSG_[IPDU_NAME]_RXCH[n] in Aubist/Com/../Com_Cfg.h             */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANUsrhkRecAck(const U2 u2_a_IPDU_RX)
{
    /* ---------------------------------------------------------------------------------------------------- */
    /* WARNING :                                                                                            */
    /* ---------------------------------------------------------------------------------------------------- */
    /* vd_g_oXCANUsrhkRecAck is called from BswM_CS_MainFunctionMiddle or BswM_CS_MainFunctionHigh          */
    /* depending on following configuration :                                                               */
    /*                                                                                                      */
    /* BswM_CS\cfg\BswM_CS_Cfg.h                                                                            */
    /* #define BSW_BSWM_CS_CFG_MSGDELIVER                                                                   */
    /*                                                                                                      */
    /* If BSW_BSWM_CS_CFG_MSGDELIVER is configured with BSWM_CS_MSGDELIVER_HIGH, vd_g_oXCANUsrhkRecAck      */
    /* could be called from interrupts service routine. Therefore, user shall verify if RAM sharing issue   */
    /* will not be caused.                                                                                  */
    /* ---------------------------------------------------------------------------------------------------- */

    /* Users Configuration */

#ifdef CAN_LPR_TEST_H
    vd_g_CANLpRTestRxAck(u2_a_IPDU_RX);
#endif /* #ifdef CAN_LPR_TEST_H */

    /* Sample Code */
/*  switch(u2_a_IPDU_RX)                                    */
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

    switch (u2_a_IPDU_RX) {
#if 0   /* BEV BSW provisionally */
        case (U2)MSG_AVN1S30_RXCH0:
            vd_g_DateSITimCanRxHk();
            break;
#else
#endif
        case (U2)MSG_ENG1G17_RXCH0:
            vd_g_FsposnsrCanRxEng1g17();
            break;
#if 0   /* BEV BSW provisionally */
        case (U2)MSG_ENG1S98_RXCH0:
            vd_g_FsposnsrCanRxEng1s98();
            break;
#else
#endif
        case (U2)MSG_VSC1G12_RXCH0:
            vd_g_FsposnsrCanRxVsc1g12();
            break;
#if 0   /* BEV BSW provisionally */
        case (U2)MSG_VSC1G30_RXCH0:
            vd_g_FsposnsrCanRxVsc1g30();
            break;
#else
#endif
        default:
            /* Do nothing */
            break;
    }
    
    vd_s_oXCANUsrhkMmappRxMsg(u2_a_IPDU_RX);
    
    vd_g_MulmedMulfrRxTxtHk(u2_a_IPDU_RX);
    vd_g_XSpiMETCANGWPushPDU(u2_a_IPDU_RX);
}
/*===================================================================================================================================*/
/*  static void    vd_s_oXCANUsrhkMmappRxMsg(const U2 u2_a_MSG)                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_MSG : Message Handler                                                                                   */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_oXCANUsrhkMmappRxMsg(const U2 u2_a_IPDU_RX)
{
#if 0   /* BEV BSW provisionally */
    static const ST_OXCAN_USRHK_MMAPP st_sp_OXCAN_USRHK_MMAPP[] = {
        {(U2)MSG_AVNMS72_RXCH1,    &vd_g_MMAppCtrlNotifyRcvTextMsg  }
    };
    static const U4 u4_s_OXCAN_USRHK_MMAPP = ((U4)sizeof(st_sp_OXCAN_USRHK_MMAPP) / (U4)sizeof(ST_OXCAN_USRHK_MMAPP));

    U4 u4_t_lpcnt;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < u4_s_OXCAN_USRHK_MMAPP; u4_t_lpcnt++){
        if(u2_a_IPDU_RX == st_sp_OXCAN_USRHK_MMAPP[u4_t_lpcnt].u2_msg){
            if(st_sp_OXCAN_USRHK_MMAPP[u4_t_lpcnt].fp_vd_HOOK != vdp_PTR_NA){
                st_sp_OXCAN_USRHK_MMAPP[u4_t_lpcnt].fp_vd_HOOK(u2_a_IPDU_RX);
            }
        }
    }
#else
#endif
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  2.0.0     2/27/2025  TN       oxcan_usrhk.c v.1.0.5 -> v2.0.0.                                                                   */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, DENSO                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
