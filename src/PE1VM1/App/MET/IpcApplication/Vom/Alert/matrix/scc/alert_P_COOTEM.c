/* 5.7.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert P_COOTEM                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_P_COOTEM_C_MAJOR                   (5)
#define ALERT_P_COOTEM_C_MINOR                   (7)
#define ALERT_P_COOTEM_C_PATCH                   (0)

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
#if (ALERT_P_COOTEM_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_P_COOTEM.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_P_COOTEM_TT_BC_NUM_DST             (32U)
#define ALERT_P_COOTEM_TT_PD_NUM_DST             (16U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U2      u2_s_alert_p_cootem_ttbc_tempprv;
static U2      u2_s_alert_p_cootem_ttpd_tempprv;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_AlertP_cootemTtBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertP_cootemTtPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static void    vd_s_AlertP_cootemTtPdRwTx  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_P_COOTEM_TT_BC_DST[ALERT_P_COOTEM_TT_BC_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 01 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 08 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 09 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 10 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 11 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 13 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 14 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 15 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 16 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 17 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 18 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 19 UNKNOWN                                         */
    (U1)ALERT_REQ_P_COOTEM_TT_BC_PREWRN,                                       /* 20 PREWRN                                          */
    (U1)ALERT_REQ_P_COOTEM_TT_BC_PREWRN,                                       /* 21 PREWRN                                          */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 22 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 23 UNKNOWN                                         */
    (U1)ALERT_REQ_P_COOTEM_TT_BC_PREWRN,                                       /* 24 PREWRN                                          */
    (U1)ALERT_REQ_P_COOTEM_TT_BC_PREWRN,                                       /* 25 PREWRN                                          */
    (U1)ALERT_REQ_P_COOTEM_TT_BC_PREWRN,                                       /* 26 PREWRN                                          */
    (U1)ALERT_REQ_P_COOTEM_TT_BC_PREWRN,                                       /* 27 PREWRN                                          */
    (U1)ALERT_REQ_P_COOTEM_TT_BC_WRN,                                          /* 28 WRN                                             */
    (U1)ALERT_REQ_P_COOTEM_TT_BC_WRN,                                          /* 29 WRN                                             */
    (U1)ALERT_REQ_P_COOTEM_TT_BC_WRN,                                          /* 30 WRN                                             */
    (U1)ALERT_REQ_P_COOTEM_TT_BC_WRN                                           /* 31 WRN                                             */
};
static const U1  u1_sp_ALERT_P_COOTEM_TT_PD_DST[ALERT_P_COOTEM_TT_PD_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 01 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 08 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 09 UNKNOWN                                         */
    (U1)ALERT_REQ_P_COOTEM_TT_PD_WRN,                                          /* 10 WRN                                             */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 11 UNKNOWN                                         */
    (U1)ALERT_REQ_P_COOTEM_TT_PD_WRN,                                          /* 12 WRN                                             */
    (U1)ALERT_REQ_P_COOTEM_TT_PD_WRN,                                          /* 13 WRN                                             */
    (U1)ALERT_REQ_P_COOTEM_TT_PD_WRN,                                          /* 14 WRN                                             */
    (U1)ALERT_REQ_P_COOTEM_TT_PD_WRN                                           /* 15 WRN                                             */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_P_COOTEM_MTRX[2] = {
    {
        &u4_s_AlertP_cootemTtBcSrcchk,                                         /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_P_COOTEM_TT_BC_DST[0],                                    /* u1p_DST                                            */
        (U2)ALERT_P_COOTEM_TT_BC_NUM_DST,                                      /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertP_cootemTtPdSrcchk,                                         /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertP_cootemTtPdRwTx,                                           /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_P_COOTEM_TT_PD_DST[0],                                    /* u1p_DST                                            */
        (U2)ALERT_P_COOTEM_TT_PD_NUM_DST,                                      /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_AlertP_cootemInit(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AlertP_cootemInit(void)
{
    u2_s_alert_p_cootem_ttbc_tempprv = (U2)0U;
    u2_s_alert_p_cootem_ttpd_tempprv = (U2)0U;
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertP_cootemTtBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertP_cootemTtBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_P_COOTEM_TTBC_HI_TRSH = (U2)12000U;       /* 120 degrees celsius (LSB:0.01) */
    static const U2 u2_s_ALERT_P_COOTEM_TTBC_MD_TRSH = (U2)11700U;       /* 117 degrees celsius (LSB:0.01) */
    static const U2 u2_s_ALERT_P_COOTEM_TTBC_LO_TRSH = (U2)11500U;       /* 115 degrees celsius (LSB:0.01) */
    static const U4 u4_s_ALERT_P_COOTEM_TTBC_MSK_LAS = (U4)0x00000003U;
    static const U4 u4_s_ALERT_P_COOTEM_TTBC_LMD_TMP = (U4)0x00000004U;
    static const U4 u4_s_ALERT_P_COOTEM_TTBC_HMD_TMP = (U4)0x00000008U;
    static const U4 u4_s_ALERT_P_COOTEM_TTBC_HI_TMP  = (U4)0x0000000CU;
    static const U4 u4_s_ALERT_P_COOTEM_TTBC_IGN_ON  = (U4)0x00000010U;
    U1              u1_t_tmpret;
    U2              u2_t_cel;
    U4              u4_t_src_chk;

    u4_t_src_chk = (U4)u1_a_LAS & u4_s_ALERT_P_COOTEM_TTBC_MSK_LAS;

    u2_t_cel     = (U2)0U;
    u1_t_tmpret  = (u1_g_AlertCfgPtsctmpCelFltrd(&u2_t_cel) & ((U1)ALERT_PTSCTMP_STSBIT_UNKNOWN | (U1)ALERT_PTSCTMP_STSBIT_INVALID));

    if((u1_t_tmpret & (U1)ALERT_PTSCTMP_STSBIT_INVALID) != (U1)0U){
        u2_t_cel = u2_s_alert_p_cootem_ttbc_tempprv;
    }

    if(u1_t_tmpret != (U1)ALERT_PTSCTMP_STSBIT_UNKNOWN){
        if(u2_t_cel >= u2_s_ALERT_P_COOTEM_TTBC_HI_TRSH){
            u4_t_src_chk |= u4_s_ALERT_P_COOTEM_TTBC_HI_TMP;
        }
        else if(u2_t_cel >= u2_s_ALERT_P_COOTEM_TTBC_MD_TRSH){
            u4_t_src_chk |= u4_s_ALERT_P_COOTEM_TTBC_HMD_TMP;
        }
        else if(u2_t_cel > u2_s_ALERT_P_COOTEM_TTBC_LO_TRSH){
            u4_t_src_chk |= u4_s_ALERT_P_COOTEM_TTBC_LMD_TMP;
        }
        else{
            /* Do nothing */
        }
    }
    if((u1_a_VOM & (U1)ALERT_VOM_IGN_ON) != (U1)0U){
        u4_t_src_chk |= u4_s_ALERT_P_COOTEM_TTBC_IGN_ON;
    }

    u2_s_alert_p_cootem_ttbc_tempprv = u2_t_cel;

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertP_cootemTtPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertP_cootemTtPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_P_COOTEM_TTPD_HI_TRSH = (U2)12000U;       /* 120 degrees celsius (LSB:0.01) */
    static const U2 u2_s_ALERT_P_COOTEM_TTPD_LO_TRSH = (U2)11500U;       /* 115 degrees celsius (LSB:0.01) */
    static const U4 u4_s_ALERT_P_COOTEM_TTPD_IGN_ON  = (U4)0x00000008U;
    static const U4 u4_s_ALERT_P_COOTEM_TTPD_HI_TMP  = (U4)0x00000004U;
    static const U4 u4_s_ALERT_P_COOTEM_TTPD_LO_TMP  = (U4)0x00000002U;
    static const U4 u4_s_ALERT_P_COOTEM_TTPD_MSK_LAS = (U4)0x00000001U;
    U4              u4_t_src_chk;
    U2              u2_t_cel;
    U1              u1_t_tmpret;

    u4_t_src_chk = (U4)u1_a_LAS & u4_s_ALERT_P_COOTEM_TTPD_MSK_LAS;

    u2_t_cel     = (U2)0U;
    u1_t_tmpret  = (u1_g_AlertCfgPtsctmpCelFltrd(&u2_t_cel) & ((U1)ALERT_PTSCTMP_STSBIT_UNKNOWN | (U1)ALERT_PTSCTMP_STSBIT_INVALID));

    if((u1_t_tmpret & (U1)ALERT_PTSCTMP_STSBIT_INVALID) != (U1)0U){
        u2_t_cel = u2_s_alert_p_cootem_ttpd_tempprv;
    }

    if(u1_t_tmpret != (U1)ALERT_PTSCTMP_STSBIT_UNKNOWN){
        if(u2_t_cel >= u2_s_ALERT_P_COOTEM_TTPD_HI_TRSH){
            u4_t_src_chk |= u4_s_ALERT_P_COOTEM_TTPD_HI_TMP;
        }
        if(u2_t_cel > u2_s_ALERT_P_COOTEM_TTPD_LO_TRSH){
            u4_t_src_chk |= u4_s_ALERT_P_COOTEM_TTPD_LO_TMP;
        }
    }
    if((u1_a_VOM & (U1)ALERT_VOM_IGN_ON) != (U1)0U){
        u4_t_src_chk |= u4_s_ALERT_P_COOTEM_TTPD_IGN_ON;
    }

    u2_s_alert_p_cootem_ttpd_tempprv = u2_t_cel;

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static void    vd_s_AlertP_cootemTtPdRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertP_cootemTtPdRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)
{
#ifdef ComConf_ComSignal_WTPW /* 130D_CAN */
    U1              u1_t_sgnl;
    U1              u1_t_rwtx_enbl;
#ifdef ALERT_CH_P_TMPIND_TT_PD
#if (ALERT_CH_P_TMPIND_TT_PD < ALERT_NUM_CH)
    U1              u1_t_req;
#endif /* (ALERT_CH_P_TMPIND_TT_PD < ALERT_NUM_CH) */
#endif /* ALERT_CH_P_TMPIND_TT_PD */

    u1_t_rwtx_enbl = (U1)FALSE;
#ifdef ALERT_CH_P_TMPIND_TT_PD
#if (ALERT_CH_P_TMPIND_TT_PD < ALERT_NUM_CH)
    u1_t_req       = u1_g_AlertReqByCh((U2)ALERT_CH_P_TMPIND_TT_PD);
    if(u1_t_req == (U1)ALERT_REQ_P_TMPIND_TT_PD_ACT){
        u1_t_rwtx_enbl = (U1)TRUE;
    }
#endif /* (ALERT_CH_P_TMPIND_TT_PD < ALERT_NUM_CH) */
#endif /* ALERT_CH_P_TMPIND_TT_PD */

    if(u1_a_DST       == (U1)ALERT_REQ_P_COOTEM_TT_PD_WRN){
        u1_t_rwtx_enbl = (U1)TRUE;
    }

    if(((u1_a_VOM & (U1)ALERT_VOM_RWT_EN) != (U1)0U  ) &&
       (u1_t_rwtx_enbl                    == (U1)TRUE)){
        u1_t_sgnl      = (U1)ALERT_RW_SGNL_ON;
    }
    else{
        u1_t_sgnl      = (U1)ALERT_RW_SGNL_OFF;
    }

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_WTPW, &u1_t_sgnl);    /* COM Tx STUB delete */
#endif
#endif /* ComConf_ComSignal_WTPW */ /* 130D_CAN */
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  5.0.0     3/23/2020  FN       New.                                                                                               */
/*  5.1.0     4/28/2020  DS       Modify ptsctmp handling(Add offset).                                                               */
/*  5.1.1     9/15/2020  ZS       Add ConfigIF for get ptsctmp and remove handling to offset.                                        */
/*  5.2.0    12/ 3/2020  MO       Update for 800B 1A(Version update).                                                                */
/*  5.2.1     2/24/2021  ZS       Add ptsctmp sts mask.                                                                              */
/*  5.3.0     4/ 2/2021  TN       Change generic module -> individual module.                                                        */
/*  5.4.0     9/ 2/2021  KT       Fix WTPW send conditions.                                                                          */
/*  5.5.0     8/31/2022  TM       Update for 840B#2 1A(Version update).                                                              */
/*  5.6.0    12/ 7/2023  PG       Update for 19PFv3                                                                                  */
/*  5.7.0     3/26/2024  KH       Add function presence logic.                                                                       */
/*                                                                                                                                   */
/*  * FN   = Farah Niwa, NTTD MSE                                                                                                    */
/*  * DS   = Daisuke Suzuki, NTTD MSE                                                                                                */
/*  * ZS   = Zenjiro Shamoto, NTTD MSE                                                                                               */
/*  * MO   = Masayuki Oofuji, NTTD MSE                                                                                               */
/*  * TN   = Toshiaki Nagashima, NTTD MSE                                                                                            */
/*  * KT   = Kenichi Takahashi, NTTD MSE                                                                                             */
/*  * TM   = Tatsuya Mori, NTTD MSE                                                                                                  */
/*  * PG   = Patrick Garcia, DTPH                                                                                                    */
/*  * KH   = Kiko Huerte, DTPH                                                                                                       */
/*                                                                                                                                   */
/*===================================================================================================================================*/
