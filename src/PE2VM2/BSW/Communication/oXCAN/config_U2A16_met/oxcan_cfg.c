/* 2.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Oem eXtention of CAN                                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_CFG_C_MAJOR                 (2U)
#define OXCAN_CFG_C_MINOR                 (0U)
#define OXCAN_CFG_C_PATCH                 (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oxcan_cfg_private.h"

/*#include "ecu_m.h"*/

#include "int_handler.h"
/*#include "icu_drv_wk.h"*/
/*#include "Port.h"*/
/* #include "dio_drv.h" */

#include "can_rscf4_cfg.h"  /* CAN_CFG_RX_PROCESSING_x defined in can_rscf4_cfg.h */

#if ((OXCAN_IC_TJA1145_USE == 1U) && (OXCAN_IC_TJA1145_REFRESH == 1U))
#include "Cdd_Canic.h"
#endif /* #if ((OXCAN_IC_TJA1145_USE == 1U) && (OXCAN_IC_TJA1145_REFRESH == 1U)) */

#include "l3r_test.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((OXCAN_CFG_C_MAJOR != OXCAN_CFG_H_MAJOR) || \
     (OXCAN_CFG_C_MINOR != OXCAN_CFG_H_MINOR) || \
     (OXCAN_CFG_C_PATCH != OXCAN_CFG_H_PATCH))
#error "oxcan_cfg.c and oxcan_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_IRQ_CH_RX0                  (299U)
#define OXCAN_IRQ_CH_TX0                  (300U)
#define OXCAN_IRQ_CH_RX1                  (302U)
#define OXCAN_IRQ_CH_TX1                  (303U)
#define OXCAN_IRQ_CH_RX2                  (305U)
#define OXCAN_IRQ_CH_TX2                  (306U)
#define OXCAN_IRQ_CH_RX3                  (308U)
#define OXCAN_IRQ_CH_TX3                  (309U)
#define OXCAN_IRQ_CH_RX4                  (311U)
#define OXCAN_IRQ_CH_TX4                  (312U)
#define OXCAN_IRQ_CH_RX5                  (314U)
#define OXCAN_IRQ_CH_TX5                  (315U)
#define OXCAN_IRQ_CH_RX6                  (317U)
#define OXCAN_IRQ_CH_TX6                  (318U)
#define OXCAN_IRQ_CH_RX7                  (320U)
#define OXCAN_IRQ_CH_TX7                  (321U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (defined(PORT_DRV_H) && defined(DIO_DRV_H))
static void    vd_s_oXCANIocfgchk(void);
#endif /* #if (defined(PORT_DRV_H) && defined(DIO_DRV_H)) */

static void    vd_s_oXCANCfgEI(void);
static void    vd_s_oXCANCfgDI(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* ------------------------------------------------------------------------------------------ */
/* Attention :                                                                                */
/* ------------------------------------------------------------------------------------------ */
/* BSW_CANIF_CFG_WAKEUPSRC_CTRLx is defined in CanIf_Cfg.h                                    */
/* CanIf_Cfg.h is included in CS_Can_Cfg.h                                                    */
/* CS_Can_Cfg.h is included in oxcan.h                                                        */
/*                                                                                            */
/* u4_g_OXCAN_WKSRC_CHK shall be configured based on how many physical CAN channel are        */
/* available. Since RH850/D1x has 3 CAN channels, 3 wakeup sources are configured.            */
/* ------------------------------------------------------------------------------------------ */
const U4         u4_g_OXCAN_WKSRC_CHK = (BSW_CANIF_CFG_WAKEUPSRC_CTRL0 |
                                         BSW_CANIF_CFG_WAKEUPSRC_CTRL1 |
                                         BSW_CANIF_CFG_WAKEUPSRC_CTRL2 |
                                         BSW_CANIF_CFG_WAKEUPSRC_CTRL3 |
                                         BSW_CANIF_CFG_WAKEUPSRC_CTRL4 |
                                         BSW_CANIF_CFG_WAKEUPSRC_CTRL5 |
                                         BSW_CANIF_CFG_WAKEUPSRC_CTRL6 |
                                         BSW_CANIF_CFG_WAKEUPSRC_CTRL7 );

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U1         u1_gp_OXCAN_CTRLR_BY_CH[BSW_COM_CFG_CHNUM] = {
    (U1)U1_MAX  /* CAN Virtual Channel  =  0 ch. */
};
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U4         u4_g_OXCAN_SYS_POWER = ((U4)OXCAN_SYS_PAR      |
                                         (U4)OXCAN_SYS_RID      |
                                         (U4)OXCAN_SYS_PON      |
                                         (U4)OXCAN_SYS_POE      |
                                         (U4)OXCAN_SYS_PAR_HV   |
                                         (U4)OXCAN_SYS_PAR_HVHC |
                                         (U4)OXCAN_SYS_CHK      |
                                         (U4)OXCAN_SYS_PDM      |
                                         (U4)OXCAN_SYS_OTA1     |
                                         (U4)OXCAN_SYS_OTA2     |
                                         (U4)OXCAN_SYS_OTA3     |
                                         (U4)OXCAN_SYS_OTA4     |
                                         (U4)OXCAN_SYS_WRP      |
                                         (U4)OXCAN_SYS_EDS      );
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if OXCAN_TX_STOP_SUP
const U1         u1_g_OXCAN_TXRX_NUM_ID    = (U1)OXCAN_TXRX_NUM_ID;
const U1         u1_g_OXCAN_TXRX_NUM_CH    = (U1)OXCAN_COMCONT_NUM_CH;

const U2         u2_gp_OXCAN_PDU_REQ_BY_ID_RIMID[OXCAN_COMCONT_NUM_CH][OXCAN_TXRX_NUM_ID] = {
    {(U2)RIMID_U1_OXCAN_PDU_REQ_BY_ID_000}
};
const U2         u2_gp_OXCAN_PDU_STAT_BY_CH_RIMID[OXCAN_COMCONT_NUM_CH] = {
    (U2)RIMID_U1_OXCAN_PDU_STAT_BY_CH_000
};
#if (OXCAN_NM_TX_STOP_EN == 1U)
const U2         u2_gp_OXCAN_NM_REQ_BY_ID_RIMID[OXCAN_COMCONT_NUM_CH][OXCAN_TXRX_NUM_ID] = {
};
#endif /* #if (OXCAN_NM_TX_STOP_EN == 1U) */
#endif /* OXCAN_TX_STOP_SUP */

#if (OXCAN_AUB_E2E_SUP == 1U)
#if (OXCAN_E2E_NUM_CHECK_MSG != 0U)
const U2         u2_gp_OXCAN_E2E_CHECK_MSG[OXCAN_E2E_NUM_CHECK_MSG] = {
        /* No messages to check */
};
const U4         u4_g_OXCAN_E2E_NUM_CHECK_MSG = (U4)OXCAN_E2E_NUM_CHECK_MSG;
#endif /* #if (OXCAN_E2E_NUM_CHECK_MSG != 0U)  */

#if (OXCAN_E2E_NUM_PROTECT_MSG != 0U)
const U2         u2_gp_OXCAN_E2E_PROTECT_MSG[OXCAN_E2E_NUM_PROTECT_MSG] = {
    /* No protected messages */
};
const U4         u4_g_OXCAN_E2E_NUM_PROTECT_MSG = (U4)OXCAN_E2E_NUM_PROTECT_MSG;
#endif /* #if (OXCAN_E2E_NUM_PROTECT_MSG != 0U)  */
#endif /* #if (OXCAN_AUB_E2E_SUP == 1U) */

/*--------------------------------------------------------------------------------*/
#if (defined(PORT_DRV_H))
#define OXCAN_CHKPIN_NUM            (17U)

const U2         u2_gp_OXCAN_CHKPIN[OXCAN_CHKPIN_NUM] = {
    (U2)PORT_ID_PORT11_PIN1,   /* CAN(G2M-1)-RXD     */
    (U2)PORT_ID_PORT11_PIN0,   /* CAN(G2M-1)-CLK     */
    (U2)PORT_ID_PORT2_PIN4,    /* CAN(G2M-2)-DRV-CTX */
    (U2)PORT_ID_PORT11_PIN3,   /* CAN(G2M-1)-CS      */
    (U2)PORT_ID_PORT11_PIN2,   /* CAN(G2M-1)-TXD     */
    (U2)PORT_ID_PORT2_PIN5,    /* CAN(G2M-2)-DRV-CRX */
    (U2)PORT_ID_PORT11_PIN9,   /* CAN(G2M-2)-RXD     */
    (U2)PORT_ID_PORT11_PIN8,   /* CAN(G2M-2)-CLK     */
    (U2)PORT_ID_PORT11_PIN11,  /* CAN(G2M-2)-CS      */
    (U2)PORT_ID_PORT11_PIN10,  /* CAN(G2M-2)-TXD     */
    (U2)PORT_ID_APORT2_PIN9,   /* CAN-5V-MONITOR     */
    (U2)PORT_ID_PORT4_PIN11,   /* CAN(G2M-1)-DRV-CTX */
    (U2)PORT_ID_PORT4_PIN12,   /* CAN(G2M-1)-DRV-CRX */
    (U2)PORT_ID_PORT3_PIN5,    /* CAN(G5M)-DRV-CRX   */
    (U2)PORT_ID_APORT5_PIN2,   /* CAN(G2M-1)-WAKE    */
    (U2)PORT_ID_PORT3_PIN4,    /* CAN(G5M)-DRV-CTX   */
    (U2)PORT_ID_APORT5_PIN3    /* CAN(G5M)-STBY      */
};
#endif /* #if (defined(PORT_DRV_H)) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_oXCANCfgRstInit(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANCfgRstInit(void)
{
    vd_g_L3rTestInit();
    vd_s_oXCANCfgEI();                 /* vd_s_oXCANCfgEI shall be called at end                      */
}
/*===================================================================================================================================*/
/*  void    vd_g_oXCANCfgWkupInit(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANCfgWkupInit(void)
{
    vd_g_L3rTestInit();
    vd_s_oXCANCfgEI();                /* vd_s_oXCANCfgEI shall be called at end                      */
}
/*===================================================================================================================================*/
/*  void    vd_g_oXCANCfgOpemdEvthk(const U4 u4_a_SYSBIT_PREV, const U4 u4_a_SYSBIT_NEXT)                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANCfgOpemdEvthk(const U4 u4_a_SYSBIT_PREV, const U4 u4_a_SYSBIT_NEXT)
{
    vd_g_L3rTestStart();
}
/*===================================================================================================================================*/
/*  void    vd_g_oXCANCfgPreTask(const U4 u4_a_SYSBIT)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANCfgPreTask(const U4 u4_a_SYSBIT)
{
    vd_g_L3rTestMainTask();
}
/*===================================================================================================================================*/
/*  void    vd_g_oXCANCfgPostTask(const U1 u4_a_SYSBIT, const U2 u2_a_FATAL)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANCfgPostTask(const U4 u4_a_SYSBIT, const U2 u2_a_FATAL)
{
    /* ------------------------------------------------------------------------------------------------- */
    /* Attention :                                                                                       */
    /* ------------------------------------------------------------------------------------------------- */
    /* Modify which fatal conditions should be tested in order to trigger MCU reset based on ISO26262    */
    /* requiuremet for ECU.                                                                              */
    /*                                                                                                   */
    /* #define OXCAN_FATAL_AUB_GIC                      (0x0001U)             Global Interrupt Control   */
    /* #define OXCAN_FATAL_AUB_COM                      (0x0002U)             Aubist/Com                 */
    /* #define OXCAN_FATAL_AUB_SEC                      (0x0004U)             Aubist/SecOC, Csm          */
    /*                                                                                                   */
    /* Aubist/CAN : Register Check and/or CAN Controller Initialization Failure                          */
    /* #define OXCAN_FATAL_AUB_CAN_0                    (0x0100U)             CAN Controller 0           */
    /* #define OXCAN_FATAL_AUB_CAN_1                    (0x0200U)             CAN Controller 1           */
    /* #define OXCAN_FATAL_AUB_CAN_2                    (0x0400U)             CAN Controller 2           */
    /*                                                                                                   */
    /* ------------------------------------------------------------------------------------------------- */
#if ((OXCAN_IC_TJA1145_USE == 1U) && (OXCAN_IC_TJA1145_REFRESH == 1U))
    U4          u4_t_trcvic_no;
#endif  /* #if ((OXCAN_IC_TJA1145_USE == 1U) && (OXCAN_IC_TJA1145_REFRESH == 1U)) */
    U2          u2_t_res_run;

    u2_t_res_run = u2_a_FATAL & ((U2)OXCAN_FATAL_AUB_GIC |
                                 (U2)OXCAN_FATAL_AUB_COM);
    if(u2_t_res_run != (U2)0U){
/*-------------------------------------------------------------------------------------*/
/*        vd_g_EcuMTriggerSwReset((U1)ECU_M_SWRST_TYPE_SOFT, (U1)ECU_M_SWRST_BY_OXCAN);*/
/*-------------------------------------------------------------------------------------*/
    }

#if (defined(PORT_DRV_H))
    vd_s_oXCANIocfgchk();
#endif /* #if (defined(PORT_DRV_H)) */

#if ((OXCAN_IC_TJA1145_USE == 1U) && (OXCAN_IC_TJA1145_REFRESH == 1U))
    for(u4_t_trcvic_no = (U4)0U;u4_t_trcvic_no < (U4)CDD_CANIC_CFG_IC_NUM;u4_t_trcvic_no++){
        Cdd_Canic_Idle((U1)u4_t_trcvic_no);
    }
#endif  /* #if ((OXCAN_IC_TJA1145_USE == 1U) && (OXCAN_IC_TJA1145_REFRESH == 1U)) */

    vd_s_oXCANCfgEI();
}
/*===================================================================================================================================*/
/*  void    vd_g_oXCANCfgShutdown(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANCfgShutdown(void)
{
    vd_s_oXCANCfgDI();               /* vd_s_oXCANCfgDI shall be called at 1st                     */
}
/*===================================================================================================================================*/
/*  static void    vd_s_oXCANCfgEI(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_oXCANCfgEI(void)
{
#if (CAN_CFG_RX_PROCESSING_0 == CAN_INTERRUPT)
    vd_g_IntHndlrIRQCtrlCh((U2)OXCAN_IRQ_CH_RX0, (U1)INT_HNDLR_IRQ_CTRL_CH_ENA);
#endif

#if (CAN_CFG_TX_PROCESSING_0 == CAN_INTERRUPT)
    vd_g_IntHndlrIRQCtrlCh((U2)OXCAN_IRQ_CH_TX0, (U1)INT_HNDLR_IRQ_CTRL_CH_ENA);
#endif

#if (CAN_CFG_RX_PROCESSING_1 == CAN_INTERRUPT)
    vd_g_IntHndlrIRQCtrlCh((U2)OXCAN_IRQ_CH_RX1, (U1)INT_HNDLR_IRQ_CTRL_CH_ENA);
#endif

#if (CAN_CFG_TX_PROCESSING_1 == CAN_INTERRUPT)
    vd_g_IntHndlrIRQCtrlCh((U2)OXCAN_IRQ_CH_TX1, (U1)INT_HNDLR_IRQ_CTRL_CH_ENA);
#endif

#if (CAN_CFG_RX_PROCESSING_2 == CAN_INTERRUPT)
    vd_g_IntHndlrIRQCtrlCh((U2)OXCAN_IRQ_CH_RX2, (U1)INT_HNDLR_IRQ_CTRL_CH_ENA);
#endif

#if (CAN_CFG_TX_PROCESSING_2 == CAN_INTERRUPT)
    vd_g_IntHndlrIRQCtrlCh((U2)OXCAN_IRQ_CH_TX2, (U1)INT_HNDLR_IRQ_CTRL_CH_ENA);
#endif

#if (CAN_CFG_RX_PROCESSING_3 == CAN_INTERRUPT)
    vd_g_IntHndlrIRQCtrlCh((U2)OXCAN_IRQ_CH_RX3, (U1)INT_HNDLR_IRQ_CTRL_CH_ENA);
#endif

#if (CAN_CFG_TX_PROCESSING_3 == CAN_INTERRUPT)
    vd_g_IntHndlrIRQCtrlCh((U2)OXCAN_IRQ_CH_TX3, (U1)INT_HNDLR_IRQ_CTRL_CH_ENA);
#endif

#if (CAN_CFG_RX_PROCESSING_4 == CAN_INTERRUPT)
    vd_g_IntHndlrIRQCtrlCh((U2)OXCAN_IRQ_CH_RX4, (U1)INT_HNDLR_IRQ_CTRL_CH_ENA);
#endif

#if (CAN_CFG_TX_PROCESSING_4 == CAN_INTERRUPT)
    vd_g_IntHndlrIRQCtrlCh((U2)OXCAN_IRQ_CH_TX4, (U1)INT_HNDLR_IRQ_CTRL_CH_ENA);
#endif

#if (CAN_CFG_RX_PROCESSING_5 == CAN_INTERRUPT)
    vd_g_IntHndlrIRQCtrlCh((U2)OXCAN_IRQ_CH_RX5, (U1)INT_HNDLR_IRQ_CTRL_CH_ENA);
#endif

#if (CAN_CFG_TX_PROCESSING_5 == CAN_INTERRUPT)
    vd_g_IntHndlrIRQCtrlCh((U2)OXCAN_IRQ_CH_TX5, (U1)INT_HNDLR_IRQ_CTRL_CH_ENA);
#endif

#if (CAN_CFG_RX_PROCESSING_6 == CAN_INTERRUPT)
    vd_g_IntHndlrIRQCtrlCh((U2)OXCAN_IRQ_CH_RX6, (U1)INT_HNDLR_IRQ_CTRL_CH_ENA);
#endif

#if (CAN_CFG_TX_PROCESSING_6 == CAN_INTERRUPT)
    vd_g_IntHndlrIRQCtrlCh((U2)OXCAN_IRQ_CH_TX6, (U1)INT_HNDLR_IRQ_CTRL_CH_ENA);
#endif

#if (CAN_CFG_RX_PROCESSING_7 == CAN_INTERRUPT)
    vd_g_IntHndlrIRQCtrlCh((U2)OXCAN_IRQ_CH_RX7, (U1)INT_HNDLR_IRQ_CTRL_CH_ENA);
#endif

#if (CAN_CFG_TX_PROCESSING_7 == CAN_INTERRUPT)
    vd_g_IntHndlrIRQCtrlCh((U2)OXCAN_IRQ_CH_TX7, (U1)INT_HNDLR_IRQ_CTRL_CH_ENA);
#endif
}
/*===================================================================================================================================*/
/*  static void    vd_s_oXCANCfgDI(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_oXCANCfgDI(void)
{
#if (CAN_CFG_RX_PROCESSING_0 == CAN_INTERRUPT)
    vd_g_IntHndlrIRQCtrlCh((U2)OXCAN_IRQ_CH_RX0, (U1)0U);
#endif

#if (CAN_CFG_TX_PROCESSING_0 == CAN_INTERRUPT)
    vd_g_IntHndlrIRQCtrlCh((U2)OXCAN_IRQ_CH_TX0, (U1)0U);
#endif

#if (CAN_CFG_RX_PROCESSING_1 == CAN_INTERRUPT)
    vd_g_IntHndlrIRQCtrlCh((U2)OXCAN_IRQ_CH_RX1, (U1)0U);
#endif

#if (CAN_CFG_TX_PROCESSING_1 == CAN_INTERRUPT)
    vd_g_IntHndlrIRQCtrlCh((U2)OXCAN_IRQ_CH_TX1, (U1)0U);
#endif

#if (CAN_CFG_RX_PROCESSING_2 == CAN_INTERRUPT)
    vd_g_IntHndlrIRQCtrlCh((U2)OXCAN_IRQ_CH_RX2, (U1)0U);
#endif

#if (CAN_CFG_TX_PROCESSING_2 == CAN_INTERRUPT)
    vd_g_IntHndlrIRQCtrlCh((U2)OXCAN_IRQ_CH_TX2, (U1)0U);
#endif

#if (CAN_CFG_RX_PROCESSING_3 == CAN_INTERRUPT)
    vd_g_IntHndlrIRQCtrlCh((U2)OXCAN_IRQ_CH_RX3, (U1)0U);
#endif

#if (CAN_CFG_TX_PROCESSING_3 == CAN_INTERRUPT)
    vd_g_IntHndlrIRQCtrlCh((U2)OXCAN_IRQ_CH_TX3, (U1)0U);
#endif

#if (CAN_CFG_RX_PROCESSING_4 == CAN_INTERRUPT)
    vd_g_IntHndlrIRQCtrlCh((U2)OXCAN_IRQ_CH_RX4, (U1)0U);
#endif

#if (CAN_CFG_TX_PROCESSING_4 == CAN_INTERRUPT)
    vd_g_IntHndlrIRQCtrlCh((U2)OXCAN_IRQ_CH_TX4, (U1)0U);
#endif

#if (CAN_CFG_RX_PROCESSING_5 == CAN_INTERRUPT)
    vd_g_IntHndlrIRQCtrlCh((U2)OXCAN_IRQ_CH_RX5, (U1)0U);
#endif

#if (CAN_CFG_TX_PROCESSING_5 == CAN_INTERRUPT)
    vd_g_IntHndlrIRQCtrlCh((U2)OXCAN_IRQ_CH_TX5, (U1)0U);
#endif

#if (CAN_CFG_RX_PROCESSING_6 == CAN_INTERRUPT)
    vd_g_IntHndlrIRQCtrlCh((U2)OXCAN_IRQ_CH_RX6, (U1)0U);
#endif

#if (CAN_CFG_TX_PROCESSING_6 == CAN_INTERRUPT)
    vd_g_IntHndlrIRQCtrlCh((U2)OXCAN_IRQ_CH_TX6, (U1)0U);
#endif

#if (CAN_CFG_RX_PROCESSING_7 == CAN_INTERRUPT)
    vd_g_IntHndlrIRQCtrlCh((U2)OXCAN_IRQ_CH_RX7, (U1)0U);
#endif

#if (CAN_CFG_TX_PROCESSING_7 == CAN_INTERRUPT)
    vd_g_IntHndlrIRQCtrlCh((U2)OXCAN_IRQ_CH_TX7, (U1)0U);
#endif
}
/* --------------------------------------------------------------------------------------------------------------------------------- */


#if (defined(PORT_H))

/*===================================================================================================================================*/
/*  static void    vd_s_oXCANIocfgchk(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_oXCANIocfgchk(void)
{
    /* ------------------------------------------------------------------------------------------------- */
    /* NOTE :                                                                                            */
    /* Depending on ISO26262 requiuremet for ECU, Pin configurations might have to be monitered since    */
    /* CAN communication can not be recovered automatically if they are corrupted.                       */
    /* ------------------------------------------------------------------------------------------------- */

    U4          u4_t_pm_chk;
    U1          u1_t_nw_chk;
    U1          u1_t_chkpin;
#ifdef CXPICDD_H
    U1          u1_t_cxpi_nw_chk;
    U1          u1_t_cxpi_pm_chk;
#endif

    u1_t_nw_chk = u1_g_oXCANRxEnabled((U1)OXCAN_CH_0_CAN);
    if(u1_t_nw_chk == (U1)TRUE){
        u4_t_pm_chk = (U4)PORT_REGCHK_OK;
        for(u1_t_chkpin = (U1)0U;u1_t_chkpin < (U1)OXCAN_CHKPIN_NUM;u1_t_chkpin++){
            u4_t_pm_chk |= (U4)Port_Regchk_Pin(u2_gp_OXCAN_CHKPIN[u1_t_chkpin]);
        }

        if(u4_t_pm_chk != (U4)PORT_REGCHK_OK){
#warning "oxcan_cfg.c : DESIGN AND IMPLEMENT AN APPROPIRATE METHOD IF I/O PORT CONFIGURATION SHALL BE RECOVERD."
        }
    }
    
#ifdef CXPICDD_H
    u1_t_cxpi_nw_chk = u1_g_oXCANRxEnabled((U1)OXCAN_CH_1_CXPI);
    if(u1_t_cxpi_nw_chk == (U1)TRUE){

        u1_t_cxpi_pm_chk  = u1_g_Dio_ReadChannel((U2)DIO_CH_CXPI_NSLP) ^ (U1)DIO_LVL_LOW;
        u1_t_cxpi_pm_chk &= u1_g_Port_PinModeAct((U2)PORT_PIN_MODE_P0_03_RLIN32_RX);
        u1_t_cxpi_pm_chk &= u1_g_Port_PinModeAct((U2)PORT_PIN_MODE_P0_02_RLIN32_TX);
        u1_t_cxpi_pm_chk &= u1_g_Port_PinModeAct((U2)PORT_PIN_MODE_P42_9_DO_HI);

        if(u1_t_cxpi_pm_chk != (U1)TRUE){
#warning "oxcan_cfg.c : DESIGN AND IMPLEMENT AN APPROPIRATE METHOD IF I/O PORT CONFIGURATION SHALL BE RECOVERD."
        }
    }
#endif

}
/* --------------------------------------------------------------------------------------------------------------------------------- */


#endif /* #if (defined(PORT_H) */


/* --------------------------------------------------------------------------------------------------------------------------------- */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     2/22/2022  HU       ty19epf_ren_d1x_v220_r009 -> ox25epf_ren_d1x_v100_r000.                                            */
/*  1.0.1     9/27/2022  TM       oxcan v1.0.0 -> v1.0.1.                                                                            */
/*  1.0.2    10/14/2022  HU       oxcan v1.0.1 -> v1.0.2.                                                                            */
/*  1.0.3    10/20/2022  HU       oxcan v1.0.2 -> v1.0.3.                                                                            */
/*  1.0.4    10/26/2022  HU       oxcan v1.0.3 -> v1.0.4.                                                                            */
/*  1.1.0    11/29/2022  SY       oxcan v1.0.4 -> v1.1.0.                                                                            */
/*  1.1.1    12/13/2022  TM       oxcan v1.1.0 -> v1.1.1.                                                                            */
/*  1.1.2     1/25/2023  TM       oxcan v1.1.1 -> v1.1.2.                                                                            */
/*  1.1.3     5/10/2023  SY       oxcan v1.1.2 -> v1.1.3.                                                                            */
/*  1.1.4     6/08/2023  MI       oxcan v1.1.3 -> v1.1.4.                                                                            */
/*  1.2.0    12/20/2023  TM       oxcan v1.1.4 -> v1.2.0.                                                                            */
/*  1.2.1     1/31/2024  TI       oxcan v1.2.0 -> v1.2.1.                                                                            */
/*  1.3.0     2/22/2024  MI       oxcan v1.2.1 -> v1.3.0.                                                                            */
/*  1.4.0     5/23/2024  HU       oxcan v1.3.0 -> v1.4.0.                                                                            */
/*  2.0.0     2/ 3/2025  ST       Support BevStep3                                                                                   */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*  * HU   = Hayato Usui, DENSO                                                                                                      */
/*  * TM   = Takanori Maruyama, DENSO                                                                                                */
/*  * SY   = Satoshi Yamada, DENSO                                                                                                   */
/*  * TI   = Tomoko Inuzuka, DENSO                                                                                                   */
/*  * MI   = Masahiko Izumi, DENSO                                                                                                   */
/*  * ST   = Satoshi Tanaka, DENSO                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
