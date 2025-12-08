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
#define OXCAN_CFG_C_MAJOR                        (2U)
#define OXCAN_CFG_C_MINOR                        (0U)
#define OXCAN_CFG_C_PATCH                        (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oxcan_cfg_private.h"
#include "int_handler.h"
#include "veh_opemd.h"
/* #include "can_lpr_test.h" */

#include "can_qsev_rx.h"

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
#define OXCAN_CFG_NUM_IRQ_EN        (0U)        /* ref. u2_sp_OXCAN_IRQ_CH[] */
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
#if (OXCAN_CFG_NUM_IRQ_EN != 0U)
static void    vd_s_oXCANCfgEI(void);
static void    vd_s_oXCANCfgDI(void);
#endif /* (OXCAN_CFG_NUM_IRQ_EN != 0U) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U1         u1_gp_OXCAN_CTRLR_BY_CH[BSW_COM_CFG_CHNUM] = {
    (U1)U1_MAX  /* CAN Virtual Channel  =  0 ch. */
};

#if (OXCAN_CFG_NUM_IRQ_EN != 0U)
    /*---------------------------------------------------------------------------------------------------------------*/
    /* Define the IRQ channels to enable CAN transmit/receive interrupts with reference to the following.            */
    /*---------------------------------------------------------------------------------------------------------------*/
    /* For controllers 0-7:                                                                                          */
    /*   configure by referencing "CAN_CFG_RX_PROCESSING_x"/"CAN_CFG_TX_PROCESSING_x" in can_rscf4_cfg.h             */
    /* For controllers 8-15:                                                                                         */
    /*   configure by referencing "CAN_CFG_RX_PROCESSING_x"/"CAN_CFG_TX_PROCESSING_x" in can_rscf4c_cfg.h            */
    /*---------------------------------------------------------------------------------------------------------------*/
static const U2    u2_sp_OXCAN_IRQ_CH[OXCAN_CFG_NUM_IRQ_EN] = {
    /*(U2)299U,       */ /* Controller  0 Rx   */
    /*(U2)300U,       */ /* Controller  0 Tx   */
    /*(U2)302U,       */ /* Controller  1 Rx   */
    /*(U2)303U,       */ /* Controller  1 Tx   */
    /*(U2)305U,       */ /* Controller  2 Rx   */
    /*(U2)306U,       */ /* Controller  2 Tx   */
    /*(U2)308U,       */ /* Controller  3 Rx   */
    /*(U2)309U,       */ /* Controller  3 Tx   */
    /*(U2)311U,       */ /* Controller  4 Rx   */
    /*(U2)312U,       */ /* Controller  4 Tx   */
    /*(U2)314U,       */ /* Controller  5 Rx   */
    /*(U2)315U,       */ /* Controller  5 Tx   */
    /*(U2)317U,       */ /* Controller  6 Rx   */
    /*(U2)318U,       */ /* Controller  6 Tx   */
    /*(U2)320U,       */ /* Controller  7 Rx   */
    /*(U2)321U,       */ /* Controller  7 Tx   */
    /*(U2)325U,       */ /* Controller  8 Rx    */
    /*(U2)326U,       */ /* Controller  8 Tx    */
    /*(U2)328U,       */ /* Controller  9 Rx    */
    /*(U2)329U,       */ /* Controller  9 Tx    */
    /*(U2)331U,       */ /* Controller 10 Rx    */
    /*(U2)332U,       */ /* Controller 10 Tx    */
    /*(U2)334U,       */ /* Controller 11 Rx    */
    /*(U2)335U,       */ /* Controller 11 Tx    */
    /*(U2)337U,       */ /* Controller 12 Rx    */
    /*(U2)338U,       */ /* Controller 12 Tx    */
    /*(U2)340U,       */ /* Controller 13 Rx    */
    /*(U2)341U,       */ /* Controller 13 Tx    */
    /*(U2)343U,       */ /* Controller 14 Rx    */
    /*(U2)344U,       */ /* Controller 14 Tx    */
    /*(U2)346U,       */ /* Controller 15 Rx    */
    /*(U2)347U,       */ /* Controller 15 Tx    */
};
#endif /* (OXCAN_CFG_NUM_IRQ_EN != 0U) */

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
#ifdef CAN_LPR_TEST_H
    vd_g_CANLpRTestInit();
#endif /* #ifdef CAN_LPR_TEST_H */

#ifdef CAN_QSEV_RX_H
    vd_g_CANQSEvRxInit();
#endif /* #ifdef CAN_QSEV_RX_H */

#if (OXCAN_CFG_NUM_IRQ_EN != 0U)
    vd_s_oXCANCfgEI();                 /* vd_s_oXCANCfgEI shall be called at end                      */
#endif /* (OXCAN_CFG_NUM_IRQ_EN != 0U) */
}
/*===================================================================================================================================*/
/*  void    vd_g_oXCANCfgWkupInit(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANCfgWkupInit(void)
{
#ifdef CAN_LPR_TEST_H
    vd_g_CANLpRTestInit();
#endif /* #ifdef CAN_LPR_TEST_H */

#ifdef CAN_QSEV_RX_H
    vd_g_CANQSEvRxInit();
#endif /* #ifdef CAN_QSEV_RX_H */

#if (OXCAN_CFG_NUM_IRQ_EN != 0U)
    vd_s_oXCANCfgEI();                /* vd_s_oXCANCfgEI shall be called at end                      */
#endif /* (OXCAN_CFG_NUM_IRQ_EN != 0U) */
}
/*===================================================================================================================================*/
/*  void    vd_g_oXCANCfgVomEvhk(const U4 u4_a_SYSBIT_LAST, const U4 u4_a_SYSBIT_NEXT)                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANCfgVomEvhk(const U4 u4_a_SYSBIT_LAST, const U4 u4_a_SYSBIT_NEXT)
{
#ifdef CAN_LPR_TEST_H
    vd_g_CANLpRTestLogStart();
#endif /* #ifdef CAN_LPR_TEST_H */
}
/*===================================================================================================================================*/
/*  void    vd_g_oXCANCfgPreTask(const U4 u4_a_SYSBIT)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANCfgPreTask(const U4 u4_a_SYSBIT)
{
#ifdef CAN_LPR_TEST_H
    vd_g_CANLpRTestMainTask();
#endif /* #ifdef CAN_LPR_TEST_H */
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
    U2                 u2_t_res_run;

    u2_t_res_run = u2_a_FATAL & (U2)OXCAN_FATAL_AUB_COM;
    if(u2_t_res_run != (U2)0U){
/*-------------------------------------------------------------------------------------*/
/*        vd_g_EcuMTriggerSwReset((U1)ECU_M_SWRST_TYPE_SOFT, (U1)ECU_M_SWRST_BY_OXCAN);*/
/*-------------------------------------------------------------------------------------*/
    }

#if (OXCAN_CFG_NUM_IRQ_EN != 0U)
    vd_s_oXCANCfgEI();
#endif /* (OXCAN_CFG_NUM_IRQ_EN != 0U) */

#ifdef CAN_QSEV_RX_H
    vd_g_CANQSEvRxMainTask();
#endif /* #ifdef CAN_QSEV_RX_H */
}
/*===================================================================================================================================*/
/*  void    vd_g_oXCANCfgShtdwn(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANCfgShtdwn(void)
{
#if (OXCAN_CFG_NUM_IRQ_EN != 0U)
    vd_s_oXCANCfgDI();               /* vd_s_oXCANCfgDI shall be called at 1st                     */
#endif /* (OXCAN_CFG_NUM_IRQ_EN != 0U) */
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
    /* #define ComMConf_ComMChannel_CDC_VCAN_BUS                   (0U) */
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
    u1_t_net_chk = (U1)BSW_COMM_INVALID_COM;
    (void)ComM_GetState((U1)0U, &u1_t_net_chk);
    if((u1_t_net_chk == (U1)COMM_FULL_COM_NETWORK_REQUESTED) ||
       (u1_t_net_chk == (U1)COMM_FULL_COM_READY_SLEEP      )){

       u4_t_sys_chk |= (U4)OXCAN_SYS_VIR_0;
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
#if (OXCAN_CFG_NUM_IRQ_EN != 0U)
/*===================================================================================================================================*/
/*  static void    vd_s_oXCANCfgEI(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_oXCANCfgEI(void)
{
    U4    u4_t_lpcnt;
    
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)OXCAN_CFG_NUM_IRQ_EN; u4_t_lpcnt++){
        vd_g_IntHndlrIRQCtrlCh(u2_sp_OXCAN_IRQ_CH[u4_t_lpcnt], (U1)INT_HNDLR_IRQ_CTRL_CH_ENA);
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_oXCANCfgDI(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_oXCANCfgDI(void)
{

    U4    u4_t_lpcnt;
    
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)OXCAN_CFG_NUM_IRQ_EN; u4_t_lpcnt++){
        vd_g_IntHndlrIRQCtrlCh(u2_sp_OXCAN_IRQ_CH[u4_t_lpcnt], (U1)0U);
    }
}
#endif /* (OXCAN_CFG_NUM_IRQ_EN != 0U) */
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
