/* 5.5.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert B_WASLEV                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_B_WASLEV_C_MAJOR                   (5)
#define ALERT_B_WASLEV_C_MINOR                   (5)
#define ALERT_B_WASLEV_C_PATCH                   (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_mtrx_cfg_private.h"

#include "oxcan.h"
#if 0   /* BEV BSW provisionally */
#else
#include "Com_Cfg_STUB.h"
#include "oxcan_channel_STUB.h"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (ALERT_B_WASLEV_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_B_WASLEV.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_B_WASLEV_NUM_DST                   (32U)

#define ALERT_B_WASLEV_WASHLVSW_SGNL_LOW         (0x00U)
#define ALERT_B_WASLEV_WASHLVSW_SGNL_HI          (0x01U)
#define ALERT_B_WASLEV_WASHLVSW_SGNL_HLD         (0x02U)
#define ALERT_B_WASLEV_DLY_CNT_INIT              (0U)
#define ALERT_B_WASLEV_DLY_CNT_RESET             (1U)
#define ALERT_B_WASLEV_JDG_OFF                   (0x00U)
#define ALERT_B_WASLEV_JDG_ON                    (0x01U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_alert_b_waslev_dlycnt;
static U4      u4_s_alert_waslev_wlvl_dlycnt;
static U1      u1_s_alert_b_waslev_washlvsw_lst;
static U1      u1_s_alert_b_waslev_wlvl_lst;
static U1      u1_s_alert_b_waslev_can_jdg_lst;
static U1      u1_s_alert_b_waslev_hw_jdg_lst;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_AlertB_waslevSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static void    vd_s_AlertB_waslevRwTx  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST);
static U1      u1_s_AlertB_waslevCanJdg(const U1 u1_a_VOM);
static U1      u1_s_AlertB_waslevHwJdg (const U1 u1_a_VOM);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_B_WASLEV_DST[ALERT_B_WASLEV_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_B_WASLEV_PRMRYCHK,                                           /* 01 PRMRYCHK                                        */
    (U1)ALERT_REQ_B_WASLEV_PD_ON,                                              /* 02 PD_ON                                           */
    (U1)ALERT_REQ_B_WASLEV_TT_PD_ON,                                           /* 03 TT_PD_ON                                        */
    (U1)ALERT_REQ_B_WASLEV_PD_ON,                                              /* 04 PD_ON                                           */
    (U1)ALERT_REQ_B_WASLEV_TT_PD_ON,                                           /* 05 TT_PD_ON                                        */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_B_WASLEV_PRMRYCHK,                                           /* 07 PRMRYCHK                                        */
    (U1)ALERT_REQ_B_WASLEV_TT_PD_ON,                                           /* 08 TT_PD_ON                                        */
    (U1)ALERT_REQ_B_WASLEV_TT_PD_ON,                                           /* 09 TT_PD_ON                                        */
    (U1)ALERT_REQ_B_WASLEV_TT_PD_ON,                                           /* 10 TT_PD_ON                                        */
    (U1)ALERT_REQ_B_WASLEV_TT_PD_ON,                                           /* 11 TT_PD_ON                                        */
    (U1)ALERT_REQ_B_WASLEV_TT_PD_ON,                                           /* 12 TT_PD_ON                                        */
    (U1)ALERT_REQ_B_WASLEV_TT_PD_ON,                                           /* 13 TT_PD_ON                                        */
    (U1)ALERT_REQ_B_WASLEV_TT_PD_ON,                                           /* 14 TT_PD_ON                                        */
    (U1)ALERT_REQ_B_WASLEV_TT_PD_ON,                                           /* 15 TT_PD_ON                                        */
    (U1)ALERT_REQ_B_WASLEV_TT_PD_ON,                                           /* 16 TT_PD_ON                                        */
    (U1)ALERT_REQ_B_WASLEV_TT_PD_ON,                                           /* 17 TT_PD_ON                                        */
    (U1)ALERT_REQ_B_WASLEV_TT_PD_ON,                                           /* 18 TT_PD_ON                                        */
    (U1)ALERT_REQ_B_WASLEV_TT_PD_ON,                                           /* 19 TT_PD_ON                                        */
    (U1)ALERT_REQ_B_WASLEV_TT_PD_ON,                                           /* 20 TT_PD_ON                                        */
    (U1)ALERT_REQ_B_WASLEV_TT_PD_ON,                                           /* 21 TT_PD_ON                                        */
    (U1)ALERT_REQ_B_WASLEV_TT_PD_ON,                                           /* 22 TT_PD_ON                                        */
    (U1)ALERT_REQ_B_WASLEV_TT_PD_ON,                                           /* 23 TT_PD_ON                                        */
    (U1)ALERT_REQ_B_WASLEV_TT_PD_ON,                                           /* 24 TT_PD_ON                                        */
    (U1)ALERT_REQ_B_WASLEV_TT_PD_ON,                                           /* 25 TT_PD_ON                                        */
    (U1)ALERT_REQ_B_WASLEV_TT_PD_ON,                                           /* 26 TT_PD_ON                                        */
    (U1)ALERT_REQ_B_WASLEV_TT_PD_ON,                                           /* 27 TT_PD_ON                                        */
    (U1)ALERT_REQ_B_WASLEV_TT_PD_ON,                                           /* 28 TT_PD_ON                                        */
    (U1)ALERT_REQ_B_WASLEV_TT_PD_ON,                                           /* 29 TT_PD_ON                                        */
    (U1)ALERT_REQ_B_WASLEV_TT_PD_ON,                                           /* 30 TT_PD_ON                                        */
    (U1)ALERT_REQ_B_WASLEV_TT_PD_ON                                            /* 31 TT_PD_ON                                        */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_B_WASLEV_MTRX[1] = {
    {
        &u4_s_AlertB_waslevSrcchk,                                             /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertB_waslevRwTx,                                               /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_B_WASLEV_DST[0],                                          /* u1p_DST                                            */
        (U2)ALERT_B_WASLEV_NUM_DST,                                            /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_AlertB_waslevInit(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AlertB_waslevInit(void)
{
    u4_s_alert_b_waslev_dlycnt       = (U4)ALERT_B_WASLEV_DLY_CNT_INIT;
    u4_s_alert_waslev_wlvl_dlycnt    = (U4)ALERT_B_WASLEV_DLY_CNT_INIT;
    u1_s_alert_b_waslev_washlvsw_lst = (U1)ALERT_B_WASLEV_WASHLVSW_SGNL_HI;
    u1_s_alert_b_waslev_wlvl_lst     = (U1)IOHW_DIFLT_SWITCH_UNKNWN;
    u1_s_alert_b_waslev_can_jdg_lst  = (U1)ALERT_B_WASLEV_JDG_OFF;
    u1_s_alert_b_waslev_hw_jdg_lst   = (U1)ALERT_B_WASLEV_JDG_OFF;
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertB_waslevSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertB_waslevSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U4 u4_s_ALERT_B_WASLEV_TIM_PRMRYCHK = ((U4)3000U / (U4)ALERT_MAIN_TICK);
    static const U4 u4_s_ALERT_B_WASLEV_BIT_PRMRYCHK = (U4)0x00000001U;
    static const U4 u4_s_ALERT_B_WASLEV_BIT_REQ_UNKN = (U4)0x00000006U;
    static const U4 u4_s_ALERT_B_WASLEV_MASK_LAS     = (U4)0x00000003U;
    static const U1 u1_s_ALERT_B_WASLEV_LSB_LAS_REQ  = (U1)1U;
    static const U1 u1_s_ALERT_B_WASLEV_LSB_CAN_JDG  = (U1)3U;
    static const U1 u1_s_ALERT_B_WASLEV_LSB_HW_JDG   = (U1)4U;
    U4              u4_t_src_chk;
    U1              u1_t_can_jdg;
    U1              u1_t_hw_jdg;

    u1_t_can_jdg  = u1_s_AlertB_waslevCanJdg(u1_a_VOM);
    u4_t_src_chk  = (U4)((U4)u1_t_can_jdg << u1_s_ALERT_B_WASLEV_LSB_CAN_JDG);

    u1_t_hw_jdg   = u1_s_AlertB_waslevHwJdg(u1_a_VOM);
    u4_t_src_chk |= (U4)((U4)u1_t_hw_jdg  << u1_s_ALERT_B_WASLEV_LSB_HW_JDG);

    if((u1_a_VOM & (U1)ALERT_VOM_IGN_ON) != (U1)0U){
        if(u4_a_IGN_TM < u4_s_ALERT_B_WASLEV_TIM_PRMRYCHK){
            u4_t_src_chk |= u4_s_ALERT_B_WASLEV_BIT_PRMRYCHK;
        }
        u4_t_src_chk |= (U4)(((U4)u1_a_LAS & u4_s_ALERT_B_WASLEV_MASK_LAS) << u1_s_ALERT_B_WASLEV_LSB_LAS_REQ);
    }
    else{
        u4_t_src_chk |= u4_s_ALERT_B_WASLEV_BIT_REQ_UNKN;
    }

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static void    vd_s_AlertB_waslevRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertB_waslevRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)
{
#ifdef ComConf_ComSignal_WASH /* 460B_CAN */
    static const U1 u1_s_ALERT_B_WASLEV_RWTX_CRT = ((U1)((U1)1U << ALERT_REQ_B_WASLEV_TT_PD_ON)
                                                 |  (U1)((U1)1U << ALERT_REQ_B_WASLEV_PD_ON   ));
    static const U1 u1_s_ALERT_B_WASLEV_RWTX_MSK = (U1)0x03U;
    U1              u1_t_sgnl;
    U1              u1_t_rw;

    u1_t_rw = (U1)((U1)1U << (u1_a_DST & u1_s_ALERT_B_WASLEV_RWTX_MSK));
    if(((u1_a_VOM & (U1)ALERT_VOM_RWT_EN)         != (U1)0U) &&
       ((u1_t_rw  & u1_s_ALERT_B_WASLEV_RWTX_CRT) != (U1)0U)){
        u1_t_sgnl = (U1)ALERT_RW_SGNL_ON;
    }
    else{
        u1_t_sgnl = (U1)ALERT_RW_SGNL_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_WASH, &u1_t_sgnl);
#endif /* ComConf_ComSignal_WASH */
}

/*===================================================================================================================================*/
/*  static U1      u1_s_AlertB_waslevCanJdg(const U1 u1_a_VOM)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_AlertB_waslevCanJdg(const U1 u1_a_VOM)
{
    static const U4 u4_s_ALERT_B_WASLEV_CAN_TIM_DLY = ((U4)10000U / (U4)ALERT_CH_TICK);
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;
    U1              u1_t_retval;

    u1_t_retval                     = (U1)ALERT_B_WASLEV_JDG_OFF;

    if((u1_a_VOM & (U1)ALERT_VOM_IGN_ON) != (U1)0U){
        u1_t_sgnl   = (U1)ALERT_B_WASLEV_WASHLVSW_SGNL_HI;

        u1_t_msgsts = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_PDC1G02_RXCH0,
                                            (U2)OXCAN_RX_SYS_NRX_IGR,
                                            (U2)U2_MAX) & (U1)COM_NO_RX;

        if(u1_t_msgsts != (U1)COM_NO_RX){
            (void)Com_ReceiveSignal(ComConf_ComSignal_WASHLVSW, &u1_t_sgnl);
        }

        if(u1_t_sgnl == (U1)ALERT_B_WASLEV_WASHLVSW_SGNL_HLD){
            u1_t_sgnl = u1_s_alert_b_waslev_washlvsw_lst;
        }

        if(u1_t_sgnl                       != u1_s_alert_b_waslev_washlvsw_lst){
            u4_s_alert_b_waslev_dlycnt = (U4)ALERT_B_WASLEV_DLY_CNT_RESET;
        }
        else if(u4_s_alert_b_waslev_dlycnt >= u4_s_ALERT_B_WASLEV_CAN_TIM_DLY){
            u4_s_alert_b_waslev_dlycnt = u4_s_ALERT_B_WASLEV_CAN_TIM_DLY;
        }
        else{
            u4_s_alert_b_waslev_dlycnt++;
        }

        if(u4_s_alert_b_waslev_dlycnt >= u4_s_ALERT_B_WASLEV_CAN_TIM_DLY){
            if(u1_t_sgnl == (U1)ALERT_B_WASLEV_WASHLVSW_SGNL_LOW){
                u1_t_retval = (U1)ALERT_B_WASLEV_JDG_ON;
            }
        }
        else{
            if(u1_s_alert_b_waslev_can_jdg_lst == (U1)ALERT_B_WASLEV_JDG_ON){
                u1_t_retval = (U1)ALERT_B_WASLEV_JDG_ON;
            }
        }

        u1_s_alert_b_waslev_washlvsw_lst = u1_t_sgnl;
    }
    else{
        u4_s_alert_b_waslev_dlycnt       = (U4)ALERT_B_WASLEV_DLY_CNT_INIT;
        u1_s_alert_b_waslev_washlvsw_lst = (U1)ALERT_B_WASLEV_WASHLVSW_SGNL_HI;
    }
    u1_s_alert_b_waslev_can_jdg_lst = u1_t_retval;

    return(u1_t_retval);
}

/*===================================================================================================================================*/
/*  static U1      u1_s_AlertB_waslevHwJdg(const U1 u1_a_VOM)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_AlertB_waslevHwJdg(const U1 u1_a_VOM)
{
    static const U4 u4_s_ALERT_B_WASLEV_HW_TIM_DLY = ((U4)10000U / (U4)ALERT_CH_TICK);
    U1              u1_t_difltsw;
    U1              u1_t_wlvl;
    U1              u1_t_retval;

    u1_t_retval                    = (U1)ALERT_B_WASLEV_JDG_OFF;
    u1_t_wlvl                      = (U1)ALERT_B_WASLEV_JDG_OFF;

    if((u1_a_VOM & (U1)ALERT_VOM_IGN_ON) != (U1)0U){
        u1_t_difltsw                  = u1_g_IoHwDifltSwitch((U2)ALERT_HW_ID_B_WASLEV_WLVL);
        if(u1_t_difltsw == (U1)IOHW_DIFLT_SWITCH_ACT){
            u1_t_wlvl                     = (U1)ALERT_B_WASLEV_JDG_ON;
        }

        if(u1_t_wlvl                          != u1_s_alert_b_waslev_wlvl_lst){
            u4_s_alert_waslev_wlvl_dlycnt = (U4)ALERT_B_WASLEV_DLY_CNT_RESET;
        }
        else if(u4_s_alert_waslev_wlvl_dlycnt >= u4_s_ALERT_B_WASLEV_HW_TIM_DLY){
            u4_s_alert_waslev_wlvl_dlycnt = u4_s_ALERT_B_WASLEV_HW_TIM_DLY;
        }
        else{
            u4_s_alert_waslev_wlvl_dlycnt++;
        }

        if(u4_s_alert_waslev_wlvl_dlycnt >= u4_s_ALERT_B_WASLEV_HW_TIM_DLY){
            u1_t_retval = u1_t_wlvl;
        }
        else{
            u1_t_retval = u1_s_alert_b_waslev_hw_jdg_lst;
        }
    }
    else{
        u4_s_alert_waslev_wlvl_dlycnt = (U4)ALERT_B_WASLEV_DLY_CNT_INIT;
    }
    u1_s_alert_b_waslev_wlvl_lst   = u1_t_wlvl;
    u1_s_alert_b_waslev_hw_jdg_lst = u1_t_retval;

    return(u1_t_retval);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  5.0.0     3/24/2020  ZS       New.                                                                                               */
/*  5.1.0     6/10/2020  ZS       Fix valve check time 3050ms -> 3000ms.                                                             */
/*  5.2.0     6/26/2020  ZS       Add IG-OFF to timer reset timing.                                                                  */
/*  5.3.0     7/22/2020  ZS       Fix timer reset timing and value.                                                                  */
/*  5.4.0    12/21/2020  ZS       No ReceiveSignal when msgsts is COM_NO_RX.                                                         */
/*  5.5.0    11/04/2021  KT       Add WLVL control.                                                                                  */
/*  5.5.1     8/05/2022  RN       Update for 840B#2 1A(Version update).                                                              */
/*                                                                                                                                   */
/*  * ZS   = Zenjiro Shamoto, NTTD MSE                                                                                               */
/*  * KT   = Kenichi Takahashi, NTTD MSE                                                                                             */
/*  * RN   = Ryuga Nakanishi, NTTD MSE                                                                                               */
/*                                                                                                                                   */
/*===================================================================================================================================*/
