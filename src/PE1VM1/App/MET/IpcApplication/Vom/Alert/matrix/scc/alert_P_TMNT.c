/* 5.8.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert P_TMNT                                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_P_TMNT_C_MAJOR                     (5)
#define ALERT_P_TMNT_C_MINOR                     (8)
#define ALERT_P_TMNT_C_PATCH                     (0)

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
#if (ALERT_P_TMNT_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_P_TMNT.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_P_TMNT_TT_NUM_DST                  (64U)
#define ALERT_P_TMNT_PD_NUM_DST                  (64U)

#define ALERT_P_TMNT_UNIT_NUM                    (2U)
#define ALERT_P_TMNT_TRIP_NUM                    (2U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1      u1_s_alert_p_tmntpd_bstlast;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_AlertP_tmntTtSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertP_tmntPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U1      u1_s_AlertP_tmntMSTEDG  (void);
static U1      u1_s_AlertP_tmntOILMNT  (void);
static void    vd_s_AlertP_tmntPdRwTx  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_P_TMNT_TT_DST[ALERT_P_TMNT_TT_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 01 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_P_TMNT_TT_ON,                                                /* 08 ON                                              */
    (U1)ALERT_REQ_P_TMNT_TT_FLSH,                                              /* 09 FLSH                                            */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 10 UNKNOWN                                         */
    (U1)ALERT_REQ_P_TMNT_TT_FLSH,                                              /* 11 FLSH                                            */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 13 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 14 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 15 UNKNOWN                                         */
    (U1)ALERT_REQ_P_TMNT_TT_ON,                                                /* 16 ON                                              */
    (U1)ALERT_REQ_P_TMNT_TT_ON,                                                /* 17 ON                                              */
    (U1)ALERT_REQ_P_TMNT_TT_ON,                                                /* 18 ON                                              */
    (U1)ALERT_REQ_P_TMNT_TT_ON,                                                /* 19 ON                                              */
    (U1)ALERT_REQ_P_TMNT_TT_ON,                                                /* 20 ON                                              */
    (U1)ALERT_REQ_P_TMNT_TT_ON,                                                /* 21 ON                                              */
    (U1)ALERT_REQ_P_TMNT_TT_ON,                                                /* 22 ON                                              */
    (U1)ALERT_REQ_P_TMNT_TT_ON,                                                /* 23 ON                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 24 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 25 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 26 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 27 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 28 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 29 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 30 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 31 UNKNOWN                                         */
    (U1)ALERT_REQ_P_TMNT_TT_PRMRY,                                             /* 32 PRMRY                                           */
    (U1)ALERT_REQ_P_TMNT_TT_PRMRY,                                             /* 33 PRMRY                                           */
    (U1)ALERT_REQ_P_TMNT_TT_PRMRY,                                             /* 34 PRMRY                                           */
    (U1)ALERT_REQ_P_TMNT_TT_PRMRY,                                             /* 35 PRMRY                                           */
    (U1)ALERT_REQ_P_TMNT_TT_PRMRY,                                             /* 36 PRMRY                                           */
    (U1)ALERT_REQ_P_TMNT_TT_PRMRY,                                             /* 37 PRMRY                                           */
    (U1)ALERT_REQ_P_TMNT_TT_PRMRY,                                             /* 38 PRMRY                                           */
    (U1)ALERT_REQ_P_TMNT_TT_PRMRY,                                             /* 39 PRMRY                                           */
    (U1)ALERT_REQ_P_TMNT_TT_ON,                                                /* 40 ON                                              */
    (U1)ALERT_REQ_P_TMNT_TT_PRMRY_FLSH,                                        /* 41 PRMRY_FLSH                                      */
    (U1)ALERT_REQ_P_TMNT_TT_PRMRY,                                             /* 42 PRMRY                                           */
    (U1)ALERT_REQ_P_TMNT_TT_PRMRY_FLSH,                                        /* 43 PRMRY_FLSH                                      */
    (U1)ALERT_REQ_P_TMNT_TT_PRMRY,                                             /* 44 PRMRY                                           */
    (U1)ALERT_REQ_P_TMNT_TT_PRMRY,                                             /* 45 PRMRY                                           */
    (U1)ALERT_REQ_P_TMNT_TT_PRMRY,                                             /* 46 PRMRY                                           */
    (U1)ALERT_REQ_P_TMNT_TT_PRMRY_FLSH,                                        /* 47 PRMRY_FLSH                                      */
    (U1)ALERT_REQ_P_TMNT_TT_ON,                                                /* 48 ON                                              */
    (U1)ALERT_REQ_P_TMNT_TT_ON,                                                /* 49 ON                                              */
    (U1)ALERT_REQ_P_TMNT_TT_ON,                                                /* 50 ON                                              */
    (U1)ALERT_REQ_P_TMNT_TT_ON,                                                /* 51 ON                                              */
    (U1)ALERT_REQ_P_TMNT_TT_ON,                                                /* 52 ON                                              */
    (U1)ALERT_REQ_P_TMNT_TT_ON,                                                /* 53 ON                                              */
    (U1)ALERT_REQ_P_TMNT_TT_ON,                                                /* 54 ON                                              */
    (U1)ALERT_REQ_P_TMNT_TT_ON,                                                /* 55 ON                                              */
    (U1)ALERT_REQ_P_TMNT_TT_PRMRY,                                             /* 56 PRMRY                                           */
    (U1)ALERT_REQ_P_TMNT_TT_PRMRY,                                             /* 57 PRMRY                                           */
    (U1)ALERT_REQ_P_TMNT_TT_PRMRY,                                             /* 58 PRMRY                                           */
    (U1)ALERT_REQ_P_TMNT_TT_PRMRY,                                             /* 59 PRMRY                                           */
    (U1)ALERT_REQ_P_TMNT_TT_PRMRY,                                             /* 60 PRMRY                                           */
    (U1)ALERT_REQ_P_TMNT_TT_PRMRY,                                             /* 61 PRMRY                                           */
    (U1)ALERT_REQ_P_TMNT_TT_PRMRY,                                             /* 62 PRMRY                                           */
    (U1)ALERT_REQ_P_TMNT_TT_PRMRY                                              /* 63 PRMRY                                           */
};
static const U1  u1_sp_ALERT_P_TMNT_PD_DST[ALERT_P_TMNT_PD_NUM_DST] = {
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
    (U1)ALERT_REQ_P_TMNT_PD_PREWRN_IG,                                         /* 16 PREWRN_IG                                       */
    (U1)ALERT_REQ_P_TMNT_PD_PREWRN_ST,                                         /* 17 PREWRN_ST                                       */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 18 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 19 UNKNOWN                                         */
    (U1)ALERT_REQ_P_TMNT_PD_PREWRN_ST,                                         /* 20 PREWRN_ST                                       */
    (U1)ALERT_REQ_P_TMNT_PD_PREWRN_ST,                                         /* 21 PREWRN_ST                                       */
    (U1)ALERT_REQ_P_TMNT_PD_PREWRN_ST,                                         /* 22 PREWRN_ST                                       */
    (U1)ALERT_REQ_P_TMNT_PD_PREWRN_ST,                                         /* 23 PREWRN_ST                                       */
    (U1)ALERT_REQ_P_TMNT_PD_PREWRN_IG,                                         /* 24 PREWRN_IG                                       */
    (U1)ALERT_REQ_P_TMNT_PD_PREWRN_IG,                                         /* 25 PREWRN_IG                                       */
    (U1)ALERT_REQ_P_TMNT_PD_PREWRN_IG,                                         /* 26 PREWRN_IG                                       */
    (U1)ALERT_REQ_P_TMNT_PD_PREWRN_IG,                                         /* 27 PREWRN_IG                                       */
    (U1)ALERT_REQ_P_TMNT_PD_PREWRN_ST,                                         /* 28 PREWRN_ST                                       */
    (U1)ALERT_REQ_P_TMNT_PD_PREWRN_ST,                                         /* 29 PREWRN_ST                                       */
    (U1)ALERT_REQ_P_TMNT_PD_PREWRN_ST,                                         /* 30 PREWRN_ST                                       */
    (U1)ALERT_REQ_P_TMNT_PD_PREWRN_ST,                                         /* 31 PREWRN_ST                                       */
    (U1)ALERT_REQ_P_TMNT_PD_WRN,                                               /* 32 WRN                                             */
    (U1)ALERT_REQ_P_TMNT_PD_WRN,                                               /* 33 WRN                                             */
    (U1)ALERT_REQ_P_TMNT_PD_WRN,                                               /* 34 WRN                                             */
    (U1)ALERT_REQ_P_TMNT_PD_WRN,                                               /* 35 WRN                                             */
    (U1)ALERT_REQ_P_TMNT_PD_WRN,                                               /* 36 WRN                                             */
    (U1)ALERT_REQ_P_TMNT_PD_WRN,                                               /* 37 WRN                                             */
    (U1)ALERT_REQ_P_TMNT_PD_WRN,                                               /* 38 WRN                                             */
    (U1)ALERT_REQ_P_TMNT_PD_WRN,                                               /* 39 WRN                                             */
    (U1)ALERT_REQ_P_TMNT_PD_WRN,                                               /* 40 WRN                                             */
    (U1)ALERT_REQ_P_TMNT_PD_WRN,                                               /* 41 WRN                                             */
    (U1)ALERT_REQ_P_TMNT_PD_WRN,                                               /* 42 WRN                                             */
    (U1)ALERT_REQ_P_TMNT_PD_WRN,                                               /* 43 WRN                                             */
    (U1)ALERT_REQ_P_TMNT_PD_WRN,                                               /* 44 WRN                                             */
    (U1)ALERT_REQ_P_TMNT_PD_WRN,                                               /* 45 WRN                                             */
    (U1)ALERT_REQ_P_TMNT_PD_WRN,                                               /* 46 WRN                                             */
    (U1)ALERT_REQ_P_TMNT_PD_WRN,                                               /* 47 WRN                                             */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 48 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 49 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 50 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 51 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 52 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 53 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 54 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 55 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 56 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 57 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 58 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 59 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 60 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 61 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 62 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 63 UNKNOWN                                         */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_P_TMNT_MTRX[2] = {
    {
        &u4_s_AlertP_tmntTtSrcchk,                                             /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_P_TMNT_TT_DST[0],                                         /* u1p_DST                                            */
        (U2)ALERT_P_TMNT_TT_NUM_DST,                                           /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertP_tmntPdSrcchk,                                             /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertP_tmntPdRwTx,                                               /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_P_TMNT_PD_DST[0],                                         /* u1p_DST                                            */
        (U2)ALERT_P_TMNT_PD_NUM_DST,                                           /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_AlertP_tmntInit(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AlertP_tmntInit(void)
{
    u1_s_alert_p_tmntpd_bstlast = (U1)0U;
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertP_tmntTtSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertP_tmntTtSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U4 u4_s_ALERT_P_TMNT_TT_TIM_PRMCHK = ((U4)3000U / (U4)ALERT_MAIN_TICK);
    static const U4 u4_s_ALERT_P_TMNT_TT_BIT_PRMCHK = (U4)0x00000020U;
    static const U4 u4_s_ALERT_P_TMNT_TT_MSK_LAS    = (U4)0x00000007U;
    static const U1 u1_s_ALERT_P_TMNT_TT_LSB_OILMNT = (U1)3U;

    U4              u4_t_src_chk;
    U1              u1_t_oilmnt;

    u4_t_src_chk  = ((U4)u1_a_LAS & u4_s_ALERT_P_TMNT_TT_MSK_LAS);

    if((u1_a_VOM & (U1)ALERT_VOM_IGN_ON) != (U1)0U){

        if(u4_a_IGN_TM < u4_s_ALERT_P_TMNT_TT_TIM_PRMCHK){
            u4_t_src_chk |= u4_s_ALERT_P_TMNT_TT_BIT_PRMCHK;
        }

        u1_t_oilmnt   = u1_s_AlertP_tmntOILMNT();
        u4_t_src_chk |= ((U4)u1_t_oilmnt << u1_s_ALERT_P_TMNT_TT_LSB_OILMNT);
    }

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertP_tmntPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertP_tmntPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U4 u4_s_ALERT_P_TMNT_PD_TIM_IGEDG   = ((U4)ALERT_MAIN_TICK / (U4)ALERT_MAIN_TICK);
    static const U4 u4_s_ALERT_P_TMNT_PD_BIT_IGEDG   = (U4)0x00000008U;
    static const U4 u4_s_ALERT_P_TMNT_PD_MSK_LAS     = (U4)0x00000003U;
    static const U1 u1_s_ALERT_P_TMNT_PD_LSB_OILMNT  = (U1)4U;
    static const U1 u1_s_ALERT_P_TMNT_PD_LSB_BSTEDGE = (U1)2U;

    U4              u4_t_src_chk;
    U1              u1_t_oilmnt;
    U1              u1_t_bstedge;
    U1              u1_t_sgnl;

    if((u1_a_VOM & (U1)ALERT_VOM_IGN_ON) != (U1)0U){
        u4_t_src_chk = ((U4)u1_a_LAS & u4_s_ALERT_P_TMNT_PD_MSK_LAS);

        if(u4_a_IGN_TM < u4_s_ALERT_P_TMNT_PD_TIM_IGEDG){
            u4_t_src_chk |= u4_s_ALERT_P_TMNT_PD_BIT_IGEDG;
        }

        u1_t_sgnl = u1_s_AlertP_tmntMSTEDG();

        u1_t_bstedge                = (u1_t_sgnl ^ u1_s_alert_p_tmntpd_bstlast) & (U1)(~u1_t_sgnl);
        u4_t_src_chk               |= ((U4)u1_t_bstedge << u1_s_ALERT_P_TMNT_PD_LSB_BSTEDGE);
        u1_s_alert_p_tmntpd_bstlast = u1_t_sgnl;

        u1_t_oilmnt                 = u1_s_AlertP_tmntOILMNT();
        u4_t_src_chk               |= ((U4)u1_t_oilmnt  << u1_s_ALERT_P_TMNT_PD_LSB_OILMNT);

    }
    else{
        u4_t_src_chk                = (U4)0U;
        u1_s_alert_p_tmntpd_bstlast = (U1)0U;
    }
    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U1      u1_s_AlertP_tmntMSTEDG(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_AlertP_tmntMSTEDG(void)
{
    static const U2 u2_s_ALERT_P_TMNT_PD_TO_TRSH_MST = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U2 u2_s_ALERT_P_TMNT_PD_TO_TRSH_BST = ((U2)5000U / (U2)OXCAN_MAIN_TICK);

    U1              u1_t_ecorun;
    U1              u1_t_retval;
    U1              u1_t_msgsts;

#if 0   /* BEV provisionally */
    u1_t_ecorun = u1_g_AlertEsOptAvailable((U2)ALERT_OPT_ID_P_TMNT_ECORUN);
#else
    u1_t_ecorun = (U1)FALSE;
#endif
    u1_t_retval = (U1)0U;

    if(u1_t_ecorun == (U1)TRUE){
        u1_t_msgsts = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ECO1S90,
                                       (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                       u2_s_ALERT_P_TMNT_PD_TO_TRSH_MST) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
        if(u1_t_msgsts == (U1)0U){
            (void)Com_ReceiveSignal(ComConf_ComSignal_MSTART, &u1_t_retval);
        }
    }
    else{
        u1_t_msgsts = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ENG1G92_RXCH0,
                                       (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                       u2_s_ALERT_P_TMNT_PD_TO_TRSH_BST) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
        if(u1_t_msgsts == (U1)0U){
            (void)Com_ReceiveSignal(ComConf_ComSignal_B_ST, &u1_t_retval);
        }
    }

    return(u1_t_retval);
}

/*===================================================================================================================================*/
/*  static U1      u1_s_AlertP_tmntOILMNT(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_AlertP_tmntOILMNT(void)
{
    static const U1 u1_s_ALERT_P_TMNT_OILMNT_OFF    = (U1)0U;
    static const U1 u1_s_ALERT_P_TMNT_OILMNT_PREWRN = (U1)1U;
    static const U1 u1_s_ALERT_P_TMNT_OILMNT_WRN    = (U1)2U;
    static const U1 u1_s_ALERT_P_TMNT_TRIP_PREWRN   = (U1)0U;
    static const U1 u1_s_ALERT_P_TMNT_TRIP_WRN      = (U1)1U;
    static const U1 u1_s_ALERT_P_TMNT_UNIT_KM       = (U1)0U;
    static const U1 u1_s_ALERT_P_TMNT_UNIT_MILE     = (U1)1U;
    static const U1 u1_s_ALERT_P_TMNT_UNIT_UNKNOWN  = (U1)2U;

    static const U4 u4_sp2_ALERT_P_TMNT_TRIP_THRSH[ALERT_P_TMNT_TRIP_NUM][ALERT_P_TMNT_UNIT_NUM] = {
     /* LSB: 0.001 km                  LSB: 0.001 mile */
        {  (U4)7200000U,               (U4)4500000U  },    /*  PREWRN  */
        {  (U4)8000000U,               (U4)5000000U  }     /*  WRN     */
    };

    U1              u1_t_retval;
    U1              u1_t_unit;
    U1              u1_t_unit_buf;
    U1              u1_t_trip_sts;
    U4              u4_t_trip_km;
    U4              u4_t_dst;
    U1              u1_t_odokm_sts;
    U4              u4_t_odokm_km;
    U4              u4_t_km;

    u4_t_trip_km   = (U4)0U;
    u1_t_trip_sts  = u1_g_AlertCfgP_tmntOdoTripKm(&u4_t_trip_km);
    u4_t_odokm_km  = (U4)0U;
    u1_t_odokm_sts = u1_g_AlertCfgP_tmntOdoKm(&u4_t_odokm_km);
    u1_t_unit_buf  = u1_g_AlertUnit((U1)ALERT_UNIT_IDX_DIST);

    if(u1_t_odokm_sts == (U1)ALERT_ODO_STSBIT_VALID){

        if(u1_t_trip_sts == (U1)ALERT_ODO_STSBIT_VALID){
            u4_t_km = u4_t_trip_km;
        }
        else{
            u4_t_km = u4_t_odokm_km;
        }

        if(u1_t_unit_buf == (U1)ALERT_UNIT_VAL_DIST_KM){
            u1_t_unit = u1_s_ALERT_P_TMNT_UNIT_KM;
            u4_t_dst  = u4_t_km;
        }
        else if(u1_t_unit_buf == (U1)ALERT_UNIT_VAL_DIST_MILE){
            u1_t_unit = u1_s_ALERT_P_TMNT_UNIT_MILE;
            u4_t_dst  = u4_g_AlertUnitconvtrKmtoMi(u4_t_km);
        }
        else{
            u1_t_unit = u1_s_ALERT_P_TMNT_UNIT_UNKNOWN;
        }

        if(u1_t_unit != u1_s_ALERT_P_TMNT_UNIT_UNKNOWN){
            if(u4_t_dst >= u4_sp2_ALERT_P_TMNT_TRIP_THRSH[u1_s_ALERT_P_TMNT_TRIP_WRN][u1_t_unit]){
                u1_t_retval = u1_s_ALERT_P_TMNT_OILMNT_WRN;
            }
            else if(u4_t_dst >= u4_sp2_ALERT_P_TMNT_TRIP_THRSH[u1_s_ALERT_P_TMNT_TRIP_PREWRN][u1_t_unit]){
                u1_t_retval = u1_s_ALERT_P_TMNT_OILMNT_PREWRN;
            }
            else{
                u1_t_retval = u1_s_ALERT_P_TMNT_OILMNT_OFF;
            }
        }
        else{
            u1_t_retval   = u1_s_ALERT_P_TMNT_OILMNT_OFF;
        }
    }
    else{
        u1_t_retval = u1_s_ALERT_P_TMNT_OILMNT_WRN;
    }

    return(u1_t_retval);
}

/*===================================================================================================================================*/
/*  static void    vd_s_AlertP_tmntPdRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertP_tmntPdRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)
{
    U1              u1_t_sgnl;
    U1              u1_t_tmnt;

    u1_t_tmnt = u1_g_AlertCfgTMntIsEnable();
    if(((u1_a_VOM & (U1)ALERT_VOM_RWT_EN) != (U1)0U                      ) &&
        (u1_a_DST                         == (U1)ALERT_REQ_P_TMNT_PD_WRN ) &&
        (u1_t_tmnt                        == (U1)TRUE)){
        u1_t_sgnl = (U1)ALERT_RW_SGNL_ON;
    }
    else{
        u1_t_sgnl = (U1)ALERT_RW_SGNL_OFF;
    }

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_OMRW, &u1_t_sgnl);
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
/*  5.0.0     3/12/2020  FN       New.                                                                                               */
/*  5.1.0     5/20/2020  DS       Fix bit pos for MST_EDG.                                                                           */
/*  5.2.0     8/26/2020  KT       Modify MST_EDG control of PD.                                                                      */
/*  5.2.1     2/10/2021  ZS       Fix QAC Warning.                                                                                   */
/*  5.3.0     3/22/2021  KT       Get Message Label(ENG1G92,ECT1S90,ENG1S92) of B_ST.                                                */
/*  5.3.1     5/14/2021  KT       Fix 800B Bug.                                                                                      */
/*  5.4.0    10/28/2021  HU       Update for 840B 1A(Version update).                                                                */
/*  5.5.0    11/ 4/2021  MO       Change timer thresh.                                                                               */
/*  5.6.0     5/25/2022  TM       Fix Country code support for RW.                                                                   */
/*  5.6.1     8/ 5/2022  TM       Update for 840B#2 CV(Version update).                                                              */
/*  5.7.0     9/ 6/2022  SAO      Fixed Bug.(change method of judgement when invalid status)                                         */
/*  5.8.0     2/22/2024  DR       Updated for 19PFv3                                                                                 */
/*  5.8.0-BEV-1                                                                                                                      */
/*            2/ 5/2025  SF       Setting for BEV System_Consideration_1.                                                            */
/*                                                                                                                                   */
/*  * FN   = Farah Niwa, NTTD MSE                                                                                                    */
/*  * DS   = Daisuke Suzuki, NTTD MSE                                                                                                */
/*  * KT   = Kenichi Takahashi, NTTD MSE                                                                                             */
/*  * ZS   = Zenjiro Shamoto, NTTD MSE                                                                                               */
/*  * HU   = Hidekazu Usui, NTTD MSE                                                                                                 */
/*  * MO   = Masayuki Oofuji, NTTD MSE                                                                                               */
/*  * SAO  = Sachiko Oono, NTTD MSE                                                                                                  */
/*  * DR   = Dyan Reyes, DTPH                                                                                                        */
/*  * SF   = Shiro Furui, Denso Techno                                                                                               */
/*                                                                                                                                   */
/*===================================================================================================================================*/
