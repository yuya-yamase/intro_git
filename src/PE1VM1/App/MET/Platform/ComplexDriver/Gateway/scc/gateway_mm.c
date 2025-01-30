/* 1.6.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Multi Media Gateway                                                                                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GATEWAY_MM_C_MAJOR                         (1)
#define GATEWAY_MM_C_MINOR                         (6)
#define GATEWAY_MM_C_PATCH                         (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "gateway_mm_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((GATEWAY_MM_C_MAJOR != GATEWAY_MM_H_MAJOR) || \
     (GATEWAY_MM_C_MINOR != GATEWAY_MM_H_MINOR) || \
     (GATEWAY_MM_C_PATCH != GATEWAY_MM_H_PATCH))
#error "gateway_mm.c and gateway_mm.h : source and header files are inconsistent!"
#endif

#if ((GATEWAY_MM_C_MAJOR != GATEWAY_MM_CFG_PRIVATE_H_MAJOR) || \
     (GATEWAY_MM_C_MINOR != GATEWAY_MM_CFG_PRIVATE_H_MINOR) || \
     (GATEWAY_MM_C_PATCH != GATEWAY_MM_CFG_PRIVATE_H_PATCH))
#error "gateway_mm.c and gateway_mm_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GWMM_PWRSTS_BA_BITPOS                   (1U)                       /*  Power Status BA  bit_position  */
#define GWMM_PWRSTS_ACC_BITPOS                  (2U)                       /*  Power Status ACC bit_position  */
#define GWMM_PWRSTS_IGR_BITPOS                  (3U)                       /*  Power Status IGR bit_position  */
#define GWMM_PWRSTS_IGP_BITPOS                  (4U)                       /*  Power Status IGP bit_position  */

#define GWMM_MSG_NO_RX                          (0x01U)                    /*  Message No Receive             */

#define GWMM_MSGBUFINIT                         (0x00000000U)              /*  Message Buf Initial Value      */
#define GWMM_MSGSTSINIT                         (GWMM_MSG_NO_RX)           /*  Message Status Initial Value   */
#define GWMM_DRVMDBUFINIT                       (0x00U)                    /*  DriveMode Buf Initial Value    */
#define GWMM_SWCNTINIT                          (0xFFU)                    /*  Sw Count Initial Value         */

#define GWMM_SWCNTRST                           (0x00U)                    /*  Sw Count Initial Value         */

#define GWMM_SWOFF                              (0x00U)                    /*  Sw OFF                         */

#define GWMM_MAIN_TICK                          (10U)                      /*  Gatewat_mm task 10ms           */
#define GWMM_SW_HOLDTIME                        (150U / GWMM_MAIN_TICK)    /*  Sw Hold Time 150ms             */

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
static void    vd_s_GwmmLCanGTW(const U1 u1_a_PWRSTS , const U1 u1_a_SIG_IDX , const U1 u1_a_GLOBAL_CAN);
static void    vd_s_GwmmStrSwGTW(const U1 u1_a_PWRSTS , const U1 u1_a_SIG_IDX , const U1 u1_a_GLOBAL_CAN);
static void    vd_s_GwmmLCanPwrJdg(const U1 u1_a_PWRSTS , const U1 u1_a_SIG_IDX , const U1 u1_a_GLOBAL_CAN);
static void    vd_s_GwmmGCanGTW(const U1 u1_a_PWRSTS , const U1 u1_a_SIG_IDX , const U1 u1_a_LOCAL_CAN);
static void    vd_s_GwmmLCanGTW_TMNSSW(const U1 u1_a_PWRSTS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_GatewaymmInit(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_GatewaymmInit(void)
{
    U4    u4_t_lpcnt;        /*  Loop Counter  */

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_GWMM_MSGBUF_NUM; u4_t_lpcnt++){
        u4_gp_gwmm_msgbuf[u4_t_lpcnt] = (U4)GWMM_MSGBUFINIT;
    }

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_GWMM_DRVMD_NUM; u4_t_lpcnt++){
        u1_gp_gwmm_strsw_drvmd[u4_t_lpcnt] = (U1)GWMM_DRVMDBUFINIT;
    }

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_GWMM_DRVMD_NUM; u4_t_lpcnt++){
        u1_gp_gwmm_strsw_cnt[u4_t_lpcnt] = (U1)GWMM_SWCNTINIT;
    }

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_GWMM_TMM_MSGBUF_NUM; u4_t_lpcnt++){
        u4_gp_gwmm_tmm_msgbuf[u4_t_lpcnt] = (U4)GWMM_MSGBUFINIT;
    }

    u1_g_gwmm_tmnssw_sigbak = (U1)0U;
}
/*===================================================================================================================================*/
/*  void    vd_g_GatewaymmMainTask(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_GatewaymmMainTask(void)
{
    U1    u1_t_pwrsts;        /*  Power Status              */
    U1    u1_t_baon;          /*  BA ON Status              */
    U1    u1_t_accon;         /*  ACC ON Status             */
    U1    u1_t_igron;         /*  IGR ON Status             */
    U1    u1_t_igpon;         /*  IGP ON Status             */
    U4    u4_t_lpcnt;         /*  Loop Counter              */
    U1    u1_t_global_can;    /*  Global-CAN                */
    U1    u1_t_local_can;     /*  Local-CAN                 */
    U1    u1_t_sup;           /*  Support Check             */

    vd_g_GwmmCfgPreTask();

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_GWMM_DRVMD_NUM; u4_t_lpcnt++){
        if(u1_gp_gwmm_strsw_cnt[u4_t_lpcnt] < (U1)U1_MAX){
            u1_gp_gwmm_strsw_cnt[u4_t_lpcnt]++;
        }
    }

    u1_t_baon  = u1_g_VehopemdPbaOn();
    u1_t_accon = u1_g_VehopemdAccOn();
    u1_t_igron = u1_g_VehopemdIgnOn();
    u1_t_igpon = u1_g_VehopemdIgnpOn();

    u1_t_pwrsts  = (U1)GWMM_PWRSTS_B;
    u1_t_pwrsts |= (U1)(u1_t_baon << GWMM_PWRSTS_BA_BITPOS);
    u1_t_pwrsts |= (U1)(u1_t_accon << GWMM_PWRSTS_ACC_BITPOS);
    u1_t_pwrsts |= (U1)(u1_t_igron << GWMM_PWRSTS_IGR_BITPOS);
    u1_t_pwrsts |= (U1)(u1_t_igpon << GWMM_PWRSTS_IGP_BITPOS);

    u1_t_sup = u1_g_GwmmCfgGetMMGTWEsOpt();
    if(u1_t_sup == (U1)TRUE){
        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_GWMM_SIG_NUM; u4_t_lpcnt++){
            if((st_gp_GWMM_COMIF[u4_t_lpcnt].fp_vd_send != vdp_PTR_NA) &&
               (st_gp_GWMM_COMIF[u4_t_lpcnt].fp_u1_read != vdp_PTR_NA)){
                u1_t_global_can = st_gp_GWMM_COMIF[u4_t_lpcnt].fp_u1_read();
                if(st_gp_GWMM_SIGCONF[u4_t_lpcnt].u1_drvmd_idx < u1_g_GWMM_DRVMD_NUM){
                    if(u1_gp_gwmm_strsw_drvmd[st_gp_GWMM_SIGCONF[u4_t_lpcnt].u1_drvmd_idx] != (U1)GWMM_SWOFF){
                        vd_s_GwmmStrSwGTW(u1_t_pwrsts, (U1)u4_t_lpcnt, u1_t_global_can);
                    }
                    else if(u1_gp_gwmm_strsw_cnt[st_gp_GWMM_SIGCONF[u4_t_lpcnt].u1_drvmd_idx] <= (U1)GWMM_SW_HOLDTIME){
                        /* Do Nothing */
                    }
                    else{
                        vd_s_GwmmLCanPwrJdg(u1_t_pwrsts, (U1)u4_t_lpcnt, u1_t_global_can);
                    }
                }
                else{
                    vd_s_GwmmLCanGTW(u1_t_pwrsts, (U1)u4_t_lpcnt, u1_t_global_can);
                }
            }
        }
        vd_s_GwmmLCanGTW_TMNSSW(u1_t_pwrsts);
        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_GWMM_TMM_SIG_NUM; u4_t_lpcnt++){
            if((st_gp_GWMM_TMM_COMIF[u4_t_lpcnt].fp_vd_send != vdp_PTR_NA)
            && (st_gp_GWMM_TMM_COMIF[u4_t_lpcnt].fp_u1_read != vdp_PTR_NA)){
                u1_t_local_can = st_gp_GWMM_TMM_COMIF[u4_t_lpcnt].fp_u1_read();
                vd_s_GwmmGCanGTW(u1_t_pwrsts, (U1)u4_t_lpcnt, u1_t_local_can);
            }
        }
    }
    vd_g_GwmmCfgSend_MMCKPT(u1_t_pwrsts);
    vd_g_GwmmCfgSend_L_TBC_FUNC(u1_t_pwrsts);
}
/*===================================================================================================================================*/
/*  void    vd_g_GatewaymmDataPut(const U1 u1_a_IDX , const U4 u4_a_DATA)                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_IDX  : Message Data Buf IDX                                                                                 */
/*                  u4_a_DATA : Message Data                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_GatewaymmDataPut(const U1 u1_a_IDX , const U4 u4_a_DATA)
{
    if(u1_a_IDX < u1_g_GWMM_MSGBUF_NUM){
        u4_gp_gwmm_msgbuf[u1_a_IDX] = u4_a_DATA;
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_GatewaymmDrvmdPut(const U1 u1_a_IDX , const U1 u1_a_DATA)                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_IDX  : DriveMode Data Buf IDX                                                                               */
/*                  u1_a_DATA : DriveMode Data                                                                                       */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_GatewaymmDrvmdPut(const U1 u1_a_IDX , const U1 u1_a_DATA)
{
    if(u1_a_IDX < u1_g_GWMM_DRVMD_NUM){
        if((u1_a_DATA                        != (U1)GWMM_SWOFF)
        && (u1_gp_gwmm_strsw_drvmd[u1_a_IDX] != u1_a_DATA    )){
            u1_gp_gwmm_strsw_cnt[u1_a_IDX] = (U1)GWMM_SWCNTRST;
        }
        u1_gp_gwmm_strsw_drvmd[u1_a_IDX] = u1_a_DATA;
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_GatewaymmTMMDataPut(const U1 u1_a_IDX , const U4 u4_a_DATA)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_IDX  : Message Data Buf IDX                                                                                 */
/*                  u4_a_DATA : Message Data                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_GatewaymmTMMDataPut(const U1 u1_a_IDX , const U4 u4_a_DATA)
{
    if(u1_a_IDX < u1_g_GWMM_TMM_MSGBUF_NUM){
        u4_gp_gwmm_tmm_msgbuf[u1_a_IDX] = u4_a_DATA;
    }
}

/*===================================================================================================================================*/
/*  static void    vd_s_GwmmLCanGTW(const U1 u1_a_PWRSTS , const U1 u1_a_SIG_IDX , const U1 u1_a_GLOBAL_CAN)                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_PWRSTS     : Power Status                                                                                   */
/*                  u1_a_SIG_IDX    : Signal IDX                                                                                     */
/*                  u1_a_GLOBAL_CAN : Global-CAN                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_GwmmLCanGTW(const U1 u1_a_PWRSTS , const U1 u1_a_SIG_IDX , const U1 u1_a_GLOBAL_CAN)
{
    U1    u1_t_pwrsts_jdg;    /*  Power Status Judge        */
    U1    u1_t_msgsts_idx;    /*  Message Status IDX        */
    U1    u1_t_msg_idx;       /*  Message IDX               */
    U1    u1_t_sftbit;        /*  Shift Bit                 */
    U1    u1_t_local_can;     /*  Local-CAN                 */
    U1    u1_t_msg_num;       /*  Message Number            */
    U4    u4_t_msg_mask;      /*  Message Mask              */

    if(u1_a_SIG_IDX < u1_g_GWMM_SIG_NUM){
        u1_t_pwrsts_jdg = u1_a_PWRSTS & st_gp_GWMM_SIGCONF[u1_a_SIG_IDX].u1_pwrsts;
        u1_t_msgsts_idx = st_gp_GWMM_SIGCONF[u1_a_SIG_IDX].u1_mm_msgsts_idx;
        u1_t_msg_num    = u1_g_GWMM_MSG_MM_NUM;
        u1_t_msg_idx    = st_gp_GWMM_MSGCOMVERT[u1_a_SIG_IDX].u1_idx;
        u1_t_sftbit     = st_gp_GWMM_MSGCOMVERT[u1_a_SIG_IDX].u1_bit;
        u4_t_msg_mask   = st_gp_GWMM_MSGCOMVERT[u1_a_SIG_IDX].u4_mask;
        if(u1_t_msg_idx < u1_g_GWMM_MSGBUF_NUM){
            u1_t_local_can = (U1)((U4)(u4_gp_gwmm_msgbuf[u1_t_msg_idx] >> u1_t_sftbit) & u4_t_msg_mask);
            if(u1_t_msgsts_idx < u1_t_msg_num){

                if((u1_t_pwrsts_jdg != (U1)0U) &&
                   (u1_t_local_can <= st_gp_GWMM_SIGCONF[u1_a_SIG_IDX].u1_sigmax) &&
                   (u1_t_local_can != u1_a_GLOBAL_CAN)){
                    st_gp_GWMM_COMIF[u1_a_SIG_IDX].fp_vd_send(u1_t_local_can);
                }
            }
        }
    }

}
/*===================================================================================================================================*/
/*  static void    vd_s_GwmmLCanGTW_TMNSSW(const U1 u1_a_PWRSTS)                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_PWRSTS     : Power Status                                                                                   */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_GwmmLCanGTW_TMNSSW(const U1 u1_a_PWRSTS)
{
    U1    u1_t_pwrsts_jdg;    /*  Power Status Judge        */
    U1    u1_t_local_can;     /*  Local-CAN                 */
    U1    u1_t_global_can;    /*  Global-CAN                */

    u1_t_pwrsts_jdg = u1_a_PWRSTS & (U1)GWMM_PWRSTS_IGR;
    u1_t_local_can  = u1_g_GwmmCfgRead_L_TMNSSW();
    u1_t_global_can = u1_g_GwmmCfgRead_TMNSSW();
    if((u1_t_pwrsts_jdg != (U1)0U) &&
       (u1_t_local_can <= (U1)7U) &&
       (u1_t_local_can != u1_t_global_can)){
        vd_g_GwmmCfgSend_TMNSSW(u1_t_local_can);
    }
}

/*===================================================================================================================================*/
/*  static void    vd_s_GwmmStrSwGTW(const U1 u1_a_PWRSTS , const U1 u1_a_SIG_IDX , const U1 u1_a_GLOBAL_CAN)                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_PWRSTS     : Power Status                                                                                   */
/*                  u1_a_SIG_IDX    : Signal IDX                                                                                     */
/*                  u1_a_GLOBAL_CAN : Global-CAN                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_GwmmStrSwGTW(const U1 u1_a_PWRSTS , const U1 u1_a_SIG_IDX , const U1 u1_a_GLOBAL_CAN)
{
    U1    u1_t_pwrsts_jdg;    /*  Power Status Judge        */
    U1    u1_t_drvmd_idx;     /*  Drive Mode IDX            */

    if(u1_a_SIG_IDX < u1_g_GWMM_SIG_NUM){
        u1_t_drvmd_idx = st_gp_GWMM_SIGCONF[u1_a_SIG_IDX].u1_drvmd_idx;
        if(u1_t_drvmd_idx < u1_g_GWMM_DRVMD_NUM){
            u1_t_pwrsts_jdg = u1_a_PWRSTS & u1_gp_GWMM_DRVMDPWCONF[u1_t_drvmd_idx];
            if((u1_t_pwrsts_jdg                              != (U1)0U         ) &&
               (u1_gp_gwmm_strsw_drvmd[u1_t_drvmd_idx] != u1_a_GLOBAL_CAN)){
                st_gp_GWMM_COMIF[u1_a_SIG_IDX].fp_vd_send(u1_gp_gwmm_strsw_drvmd[u1_t_drvmd_idx]);
            }
        }
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_GwmmLCanPwrJdg(const U1 u1_a_PWRSTS , const U1 u1_a_SIG_IDX , const U1 u1_a_GLOBAL_CAN)                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_PWRSTS     : Power Status                                                                                   */
/*                  u1_a_SIG_IDX    : Signal IDX                                                                                     */
/*                  u1_a_GLOBAL_CAN : Global-CAN                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_GwmmLCanPwrJdg(const U1 u1_a_PWRSTS , const U1 u1_a_SIG_IDX , const U1 u1_a_GLOBAL_CAN)
{
    U1    u1_t_pwrsts_jdg;    /*  Power Status Judge        */

    if(u1_a_SIG_IDX < u1_g_GWMM_SIG_NUM){
        u1_t_pwrsts_jdg = u1_a_PWRSTS & st_gp_GWMM_SIGCONF[u1_a_SIG_IDX].u1_pwrsts;
        if(u1_t_pwrsts_jdg != (U1)0U){
            vd_s_GwmmLCanGTW(u1_a_PWRSTS, u1_a_SIG_IDX, u1_a_GLOBAL_CAN);
        }
        else{
            vd_s_GwmmStrSwGTW(u1_a_PWRSTS, u1_a_SIG_IDX, u1_a_GLOBAL_CAN);
        }
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_GwmmGCanGTW(const U1 u1_a_PWRSTS , const U1 u1_a_SIG_IDX , const U1 u1_a_LOCAL_CAN)                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_PWRSTS     : Power Status                                                                                   */
/*                  u1_a_SIG_IDX    : Signal IDX                                                                                     */
/*                  u1_a_LOCAL_CAN  : Local-CAN                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_GwmmGCanGTW(const U1 u1_a_PWRSTS , const U1 u1_a_SIG_IDX , const U1 u1_a_LOCAL_CAN)
{
    U1    u1_t_pwrsts_jdg;    /*  Power Status Judge        */
    U1    u1_t_msgsts_idx;    /*  Message Status IDX        */
    U1    u1_t_msg_idx;       /*  Message IDX               */
    U1    u1_t_sftbit;        /*  Shift Bit                 */
    U1    u1_t_global_can;    /*  Global-CAN                */
    U1    u1_t_msg_num;       /*  Message Number            */
    U4    u4_t_msg_mask;      /*  Message Mask              */

    if(u1_a_SIG_IDX < u1_g_GWMM_TMM_SIG_NUM){
        u1_t_pwrsts_jdg = u1_a_PWRSTS & st_gp_GWMM_TMM_SIGCONF[u1_a_SIG_IDX].u1_pwrsts;
        u1_t_msgsts_idx = st_gp_GWMM_TMM_SIGCONF[u1_a_SIG_IDX].u1_mm_msgsts_idx;
        u1_t_msg_num    = u1_g_GWMM_TMM_MSG_MM_NUM;
        u1_t_msg_idx    = st_gp_GWMM_TMM_MSGCOMVERT[u1_a_SIG_IDX].u1_idx;
        u1_t_sftbit     = st_gp_GWMM_TMM_MSGCOMVERT[u1_a_SIG_IDX].u1_bit;
        u4_t_msg_mask   = st_gp_GWMM_TMM_MSGCOMVERT[u1_a_SIG_IDX].u4_mask;
        if(u1_t_msg_idx < u1_g_GWMM_TMM_MSGBUF_NUM){
            u1_t_global_can = (U1)((U4)(u4_gp_gwmm_tmm_msgbuf[u1_t_msg_idx] >> u1_t_sftbit) & u4_t_msg_mask);
            if(u1_t_msgsts_idx < u1_t_msg_num){
                if((u1_t_pwrsts_jdg != (U1)0U) &&
                   (u1_t_global_can <= st_gp_GWMM_TMM_SIGCONF[u1_a_SIG_IDX].u1_sigmax) &&
                   (u1_t_global_can != u1_a_LOCAL_CAN)){
                    st_gp_GWMM_TMM_COMIF[u1_a_SIG_IDX].fp_vd_send(u1_t_global_can);
                }
            }
        }
    }
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     3/19/2020  RS       New.                                                                                               */
/*  1.1.0    10/ 5/2020  RS       Improvement : Add Comment. Gateway I/F Name Changed. Add SW Arbitration.                           */
/*  1.2.0     8/30/2021  SK       Change : MMCKPT Send I/F Add. HOFDIOPE SW Arbitration.                                             */
/*  1.3.0    12/14/2021  RS       Bug fix : When IGOFF, the SW operation is not reflected in the signal. Add Power Condition Branch. */
/*  1.4.0    11/19/2022  NT       Change : Combine Ehter and MM-SUB-BUS logic.                                                       */
/*  1.5.0     1/22/2024  TH       Delete Ether & Add Global to Local-CAN.                                                            */
/*  1.6.0     3/26/2024  SW       Delete transmission process for drive mode when MM is invalid(for arbitration with VdsCI).         */
/*                                                                                                                                   */
/*  * RS   = Ryosuke Sato, KSE                                                                                                       */
/*  * SK   = Shinichi Kato, KSE                                                                                                      */
/*  * NT   = Noriaki Takashima, DT                                                                                                   */
/*  * TH   = Taisuke Hirakawa, KSE                                                                                                   */
/*  * SW   = Shun Watanabe, Denso Techno                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
