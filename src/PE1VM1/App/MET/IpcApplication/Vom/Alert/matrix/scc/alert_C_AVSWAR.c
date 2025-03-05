/* 5.0.0*/
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert C_AVSWAR                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_C_AVSWAR_C_MAJOR                   (5)
#define ALERT_C_AVSWAR_C_MINOR                   (0)
#define ALERT_C_AVSWAR_C_PATCH                   (0)

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
#if (ALERT_C_AVSWAR_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_C_AVSWAR.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_C_AVSWAR_NUM_DST                   (32U)

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
static U4      u4_s_AlertC_avswarSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static void    vd_s_AlertC_avswarRwTx  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_C_AVSWAR_DST[ALERT_C_AVSWAR_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_C_AVSWAR_MALFUNC_RW,                                         /* 01 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_AVSWAR_MALFUNC,                                            /* 02 MALFUNC                                         */
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
    (U1)ALERT_REQ_C_AVSWAR_MALFUNC_RW,                                         /* 16 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_AVSWAR_MALFUNC_RW,                                         /* 17 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_AVSWAR_MALFUNC_RW,                                         /* 18 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_AVSWAR_MALFUNC_RW,                                         /* 19 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_AVSWAR_MALFUNC_RW,                                         /* 20 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_AVSWAR_MALFUNC_RW,                                         /* 21 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_AVSWAR_MALFUNC_RW,                                         /* 22 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_AVSWAR_MALFUNC_RW,                                         /* 23 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_AVSWAR_MALFUNC_RW,                                         /* 24 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_AVSWAR_MALFUNC_RW,                                         /* 25 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_AVSWAR_MALFUNC_RW,                                         /* 26 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_AVSWAR_MALFUNC_RW,                                         /* 27 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_AVSWAR_MALFUNC_RW,                                         /* 28 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_AVSWAR_MALFUNC_RW,                                         /* 29 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_AVSWAR_MALFUNC_RW,                                         /* 30 MALFUNC_RW                                      */
    (U1)ALERT_REQ_C_AVSWAR_MALFUNC_RW                                          /* 31 MALFUNC_RW                                      */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_C_AVSWAR_MTRX[1] = {
    {
        &u4_s_AlertC_avswarSrcchk,                                             /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertC_avswarRwTx,                                               /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_C_AVSWAR_DST[0],                                          /* u1p_DST                                            */
        (U2)ALERT_C_AVSWAR_NUM_DST,                                            /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertC_avswarSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertC_avswarSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_u2_s_ALERT_CH_C_AVSWAR_TO_THRSH = ((U2)10000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_CH_C_AVSWAR_LSB_STS = (U1)3U;
    U4              u4_t_src_chk;
    U1              u1_t_sgnl;
    U1              u1_t_msgsts;

    u1_t_msgsts = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_SCS1S90,
                                   (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                   u2_s_u2_s_ALERT_CH_C_AVSWAR_TO_THRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_sgnl = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_AVSMINF, &u1_t_sgnl);

    u4_t_src_chk = (U4)u1_t_sgnl;
    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_CH_C_AVSWAR_LSB_STS);

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static void    vd_s_AlertC_sdmPdRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertC_avswarRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)
{
    static const U4 u4_s_ALERT_C_AVSWAR_TIM_RW_ENBL = ((U4)15000U / (U4)ALERT_MAIN_TICK);
    U1              u1_t_sgnl;
    U1              u1_t_esopt_stb;

    u1_t_esopt_stb = u1_g_AlertEsOptAvailable((U2)ALERT_OPT_ID_C_AVSWAR_AVSEXT);

    if(((u1_a_VOM & (U1)ALERT_VOM_IGN_ON) != (U1)0U                           ) &&
       (u4_a_IGN_TM                       >= u4_s_ALERT_C_AVSWAR_TIM_RW_ENBL  ) &&
       (u1_t_esopt_stb                    == (U1)TRUE                         ) &&
       (u1_a_DST                          == (U1)ALERT_REQ_C_AVSWAR_MALFUNC_RW)){
        u1_t_sgnl = (U1)ALERT_RW_SGNL_ON;
    }
    else{
        u1_t_sgnl = (U1)ALERT_RW_SGNL_OFF;
    }
    (void)Com_SendSignal(ComConf_ComSignal_AVSW, &u1_t_sgnl);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  5.0.0    12/18/2023  AA       New.                                                                                               */
/*                                                                                                                                   */
/*  * AA   = Anna Asuncion, DT                                                                                                       */
/*                                                                                                                                   */
/*===================================================================================================================================*/
