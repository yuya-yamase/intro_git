/* 2.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  OEM eXtention of CAN                                                                                                             */
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
#include "int_handler.h"
#include "can_rscf4_cfg.h"  /* CAN_CFG_RX_PROCESSING_x defined in can_rscf4_cfg.h */

#include "Cdd_Canic.h"

#include "veh_opemd.h"
#include "can_lpr.h"

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
    (U1)5U,     /* CAN Physical Channel =  5 ch. */
    (U1)3U,     /* CAN Physical Channel =  3 ch. */
    (U1)U1_MAX, /* CAN Virtual Channel  =  0 ch. */
    (U1)7U      /* CAN Physical Channel =  7 ch. */
};

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
    Cdd_Canic_Init();
#ifdef CAN_LPR_H
    vd_g_CANLpRInit();
#endif /* #ifdef CAN_LPR_H */

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
    Cdd_Canic_Init();
#ifdef CAN_LPR_H
    vd_g_CANLpRInit();
#endif /* #ifdef CAN_LPR_H */

    vd_s_oXCANCfgEI();                /* vd_s_oXCANCfgEI shall be called at end                      */
}
/*===================================================================================================================================*/
/*  void    vd_g_oXCANCfgVomEvhk(const U4 u4_a_SYSBIT_LAST, const U4 u4_a_SYSBIT_NEXT)                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANCfgVomEvhk(const U4 u4_a_SYSBIT_LAST, const U4 u4_a_SYSBIT_NEXT)
{
}
/*===================================================================================================================================*/
/*  void    vd_g_oXCANCfgPreTask(const U4 u4_a_SYSBIT)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANCfgPreTask(const U4 u4_a_SYSBIT)
{
#ifdef CAN_LPR_H
    vd_g_CANLpRMainTask();
#endif /* #ifdef CAN_LPR_H */
}
/*===================================================================================================================================*/
/*  void    vd_g_oXCANCfgPosTask(const U4 u4_a_SYSBIT, const U2 u2_a_FATAL)                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANCfgPosTask(const U4 u4_a_SYSBIT, const U2 u2_a_FATAL)
{
    /* ------------------------------------------------------------------------------------------------- */
    /* Attention :                                                                                       */
    /* ------------------------------------------------------------------------------------------------- */
    /* Modify which fatal conditions should be tested in order to trigger MCU reset based on ISO26262    */
    /* requiuremet for ECU.                                                                              */
    /*                                                                                                   */
    /* #define OXCAN_FATAL_AUB_GIC                      (0x0001U)             Global Interrupt Control   */
    /* #define OXCAN_FATAL_AUB_COM                      (0x0002U)             Aubist/Com                 */
    /*                                                                                                   */
    /* Aubist/CAN : Register Check and/or CAN Controller Initialization Failure                          */
    /* #define OXCAN_FATAL_AUB_CAN_0                    (0x0100U)             CAN Controller 0           */
    /* #define OXCAN_FATAL_AUB_CAN_1                    (0x0200U)             CAN Controller 1           */
    /* #define OXCAN_FATAL_AUB_CAN_2                    (0x0400U)             CAN Controller 2           */
    /*                                                                                                   */
    /* ------------------------------------------------------------------------------------------------- */
    U4                 u4_t_trcvic_no;
    U2                 u2_t_res_run;

    u2_t_res_run = u2_a_FATAL & (U2)OXCAN_FATAL_AUB_COM;
    if(u2_t_res_run != (U2)0U){
/*-------------------------------------------------------------------------------------*/
/*        vd_g_EcuMTriggerSwReset((U1)ECU_M_SWRST_TYPE_SOFT, (U1)ECU_M_SWRST_BY_OXCAN);*/
/*-------------------------------------------------------------------------------------*/
    }

    for(u4_t_trcvic_no = (U4)0U;u4_t_trcvic_no < (U4)CDD_CANIC_CFG_IC_NUM; u4_t_trcvic_no++){
        Cdd_Canic_Idle((U1)u4_t_trcvic_no);
    }

    vd_s_oXCANCfgEI();
}
/*===================================================================================================================================*/
/*  void    vd_g_oXCANCfgShtdwn(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANCfgShtdwn(void)
{
    vd_s_oXCANCfgDI();               /* vd_s_oXCANCfgDI shall be called at 1st                     */
    Cdd_Canic_Shutdown();
}
/*===================================================================================================================================*/
/*  U4      u4_g_oXCANCfgSyschk(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4      u4_g_oXCANCfgSyschk(void)
{
#if ((OXCAN_SYS_ACC != VEH_OPEMD_MDBIT_ACC ) || \
     (OXCAN_SYS_IGP != VEH_OPEMD_MDBIT_IG_P) || \
     (OXCAN_SYS_PBA != VEH_OPEMD_MDBIT_PBA ) || \
     (OXCAN_SYS_IGR != VEH_OPEMD_MDBIT_IG_R))
#error "oxcan_cfg.c : OXCAN_SYS_XXX shall be equal to VEH_OPEMD_MDBIT_XXX."    
    return((U4)0U);
#else
    /* #define ComMConf_ComMChannel_CANFD_G2M_1_BUS                (0U) */
    /* #define ComMConf_ComMChannel_CANFD_G2M_2_BUS                (1U) */
    /* #define ComMConf_ComMChannel_CDC_VCAN_BUS                   (2U) */
    /* #define ComMConf_ComMChannel_CANFD_G5M_BUS                  (3U) */
    const U1           u1_sp_OXCAN_CFG_PNC[OXCAN_SYS_NUM_PNC] = {
        (U1)16,
        (U1)40,
        (U1)43,
        (U1)44
    };

    U4                 u4_t_sys_chk;
    U4                 u4_t_bit;
    U4                 u4_t_lpcnt;
    U1                 u1_t_net_chk;
    U1                 u1_t_pnc_chk;

    u4_t_sys_chk = u4_g_VehopemdMdfield() & ((U4)OXCAN_SYS_ACC |
                                             (U4)OXCAN_SYS_IGP |
                                             (U4)OXCAN_SYS_PBA |
                                             (U4)OXCAN_SYS_IGR);

    /* #define COMM_NO_COM_NO_PENDING_REQUEST          (BSW_COMM_NO_COM_NO_PENDING_REQUEST)  */
    /* #define COMM_NO_COM_REQUEST_PENDING             (BSW_COMM_NO_COM_REQUEST_PENDING)     */
    /* #define COMM_FULL_COM_NETWORK_REQUESTED         (BSW_COMM_FULL_COM_NETWORK_REQUESTED) */
    /* #define COMM_FULL_COM_READY_SLEEP               (BSW_COMM_FULL_COM_READY_SLEEP)       */
    /* #define COMM_SILENT_COM                         (BSW_COMM_SILENT_COM)                 */
    /* #define COMM_INVALID_COM                        (BSW_COMM_INVALID_COM)                */
    /* #define BSW_COMM_NO_COM_NO_PENDING_REQUEST      (0U)                                  */
    /* #define BSW_COMM_NO_COM_REQUEST_PENDING         (1U)                                  */
    /* #define BSW_COMM_FULL_COM_NETWORK_REQUESTED     (2U)                                  */
    /* #define BSW_COMM_FULL_COM_READY_SLEEP           (3U)                                  */
    /* #define BSW_COMM_SILENT_COM                     (4U)                                  */
    /* #define BSW_COMM_INVALID_COM                    (5U)                                  */
    /*                                                                                       */
    /* Std_ReturnType ComM_GetState(NetworkHandleType Channel, ComM_StateType* State )       */
    /*                                                                                       */
    /* comm/bsw_comm_public.h 446:typedef uint8               Bsw_ComM_StateType;            */
    /* ComM.h                 369:#define ComM_StateType      Bsw_ComM_StateType             */
    /* ComStack_Types.h        83:typedef uint8               NetworkHandleType;             */
    /*                                                                                       */
    u4_t_bit = (U4)OXCAN_SYS_G2M_1;
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)OXCAN_SYS_NUM_NET; u4_t_lpcnt++){

        u1_t_net_chk = (U1)BSW_COMM_INVALID_COM;
        (void)ComM_GetState((U1)u4_t_lpcnt, &u1_t_net_chk);
        if((u1_t_net_chk == (U1)COMM_FULL_COM_NETWORK_REQUESTED) ||
           (u1_t_net_chk == (U1)COMM_FULL_COM_READY_SLEEP      )){

            u4_t_sys_chk |= u4_t_bit;
        }
        u4_t_bit <<= 1U;
    }

    /* #define COMM_PNC_REQUESTED                      (BSW_COMM_PNC_REQUESTED)              */
    /* #define COMM_PNC_READY_SLEEP                    (BSW_COMM_PNC_READY_SLEEP)            */
    /* #define COMM_PNC_PREPARE_SLEEP                  (BSW_COMM_PNC_PREPARE_SLEEP)          */
    /* #define COMM_PNC_NO_COMMUNICATION               (BSW_COMM_PNC_NO_COMMUNICATION)       */
    /* #define BSW_COMM_PNC_REQUESTED                      (0U)                              */
    /* #define BSW_COMM_PNC_READY_SLEEP                    (1U)                              */
    /* #define BSW_COMM_PNC_PREPARE_SLEEP                  (2U)                              */
    /* #define BSW_COMM_PNC_NO_COMMUNICATION               (3U)                              */
    /*                                                                                       */
    /* Std_ReturnType ComM_GetChPncMode( NetworkHandleType Channel, PNCHandleType PNC,       */
    /*                                                     ComM_PncModeType* RequestedMode ) */
    /*                                                                                       */
    /* ComStack_Types.h        55:typedef uint8                PNCHandleType;                */
    /* comm/bsw_comm_public.h 450:typedef uint8                Bsw_ComM_PncModeType;         */
    /* ComM.h                 376:#define ComM_PncModeType     Bsw_ComM_PncModeType          */
    /*                                                                                       */
    u4_t_bit = (U4)OXCAN_SYS_PNC_16;
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)OXCAN_SYS_NUM_PNC; u4_t_lpcnt++){

        u1_t_pnc_chk = (U1)COMM_PNC_NO_COMMUNICATION;
        (void)ComM_GetChPncMode((U1)ComMConf_ComMChannel_CDC_VCAN_BUS,
                                u1_sp_OXCAN_CFG_PNC[u4_t_lpcnt], &u1_t_pnc_chk);
        if((u1_t_pnc_chk == (U1)COMM_PNC_REQUESTED  ) ||
           (u1_t_pnc_chk == (U1)COMM_PNC_READY_SLEEP)){

            u4_t_sys_chk |= u4_t_bit;
        }
        u4_t_bit <<= 1U;
    }

    return(u4_t_sys_chk | (U4)OXCAN_SYS_BAT);
#endif
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
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  2.0.0     2/25/2025  TN       oxcan v1.4.0 -> v2.0.0.                                                                            */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, DENSO                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
