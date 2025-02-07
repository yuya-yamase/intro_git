/* 5.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert C_VSCEXP                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_C_VSCEXP_C_MAJOR                   (5)
#define ALERT_C_VSCEXP_C_MINOR                   (1)
#define ALERT_C_VSCEXP_C_PATCH                   (0)

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
#if (ALERT_C_VSCEXP_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_C_VSCEXP.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_C_VSCEXP_NOSTEP_NUM_DST            (8U)
#define ALERT_C_VSCEXP_WDSTEP_NUM_DST            (20U)

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
static U4      u4_s_AlertC_vscexpNostepSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertC_vscexpWdstepSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_C_VSCEXP_NOSTEP_DST[ALERT_C_VSCEXP_NOSTEP_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_C_VSCEXP_NOSTEP_ON,                                          /* 01 ON                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 07 UNKNOWN                                         */
};

static const U4  u4_sp_ALERT_C_VSCEXP_WDSTEP_CRIT[ALERT_C_VSCEXP_WDSTEP_NUM_DST] = {
    (U4)0x00000000U,                                                           /* 00 UNKNOWN                                         */
    (U4)0x00000020U,                                                           /* 01 UNKNOWN                                         */
    (U4)0x00000028U,                                                           /* 02 UNKNOWN                                         */
    (U4)0x00000029U,                                                           /* 03 3ST_1                                           */
    (U4)0x0000002AU,                                                           /* 04 3ST_2                                           */
    (U4)0x0000002BU,                                                           /* 05 3ST_3                                           */
    (U4)0x0000002CU,                                                           /* 06 UNKNOWN                                         */
    (U4)0x0000002DU,                                                           /* 07 UNKNOWN                                         */
    (U4)0x0000002EU,                                                           /* 08 3ST_0                                           */
    (U4)0x0000002FU,                                                           /* 09 UNKNOWN                                         */
    (U4)0x00000030U,                                                           /* 10 UNKNOWN                                         */
    (U4)0x00000031U,                                                           /* 11 5ST_1                                           */
    (U4)0x00000032U,                                                           /* 12 5ST_2                                           */
    (U4)0x00000033U,                                                           /* 13 5ST_3                                           */
    (U4)0x00000034U,                                                           /* 14 5ST_4                                           */
    (U4)0x00000035U,                                                           /* 15 5ST_5                                           */
    (U4)0x00000036U,                                                           /* 16 5ST_0                                           */
    (U4)0x00000037U,                                                           /* 17 UNKNOWN                                         */
    (U4)0x00000038U,                                                           /* 18 UNKNOWN                                         */
    (U4)0x00000040U                                                            /* 19 UNKNOWN                                         */
};

static const U4  u4_sp_ALERT_C_VSCEXP_WDSTEP_MASK[ALERT_C_VSCEXP_WDSTEP_NUM_DST] = {
    (U4)0x00000060U,                                                           /* 00 UNKNOWN                                         */
    (U4)0x00000078U,                                                           /* 01 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 02 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 03 3ST_1                                           */
    (U4)0x0000007FU,                                                           /* 04 3ST_2                                           */
    (U4)0x0000007FU,                                                           /* 05 3ST_3                                           */
    (U4)0x0000007FU,                                                           /* 06 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 07 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 08 3ST_0                                           */
    (U4)0x0000007FU,                                                           /* 09 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 10 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 11 5ST_1                                           */
    (U4)0x0000007FU,                                                           /* 12 5ST_2                                           */
    (U4)0x0000007FU,                                                           /* 13 5ST_3                                           */
    (U4)0x0000007FU,                                                           /* 14 5ST_4                                           */
    (U4)0x0000007FU,                                                           /* 15 5ST_5                                           */
    (U4)0x0000007FU,                                                           /* 16 5ST_0                                           */
    (U4)0x0000007FU,                                                           /* 17 UNKNOWN                                         */
    (U4)0x00000078U,                                                           /* 18 UNKNOWN                                         */
    (U4)0x00000040U                                                            /* 19 UNKNOWN                                         */
};

static const U1  u1_sp_ALERT_C_VSCEXP_WDSTEP_DST[ALERT_C_VSCEXP_WDSTEP_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 01 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_C_VSCEXP_WDSTEP_3ST_1,                                       /* 03 3ST_1                                           */
    (U1)ALERT_REQ_C_VSCEXP_WDSTEP_3ST_2,                                       /* 04 3ST_2                                           */
    (U1)ALERT_REQ_C_VSCEXP_WDSTEP_3ST_3,                                       /* 05 3ST_3                                           */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_C_VSCEXP_WDSTEP_3ST_0,                                       /* 08 3ST_0                                           */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 09 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 10 UNKNOWN                                         */
    (U1)ALERT_REQ_C_VSCEXP_WDSTEP_5ST_1,                                       /* 11 5ST_1                                           */
    (U1)ALERT_REQ_C_VSCEXP_WDSTEP_5ST_2,                                       /* 12 5ST_2                                           */
    (U1)ALERT_REQ_C_VSCEXP_WDSTEP_5ST_3,                                       /* 13 5ST_3                                           */
    (U1)ALERT_REQ_C_VSCEXP_WDSTEP_5ST_4,                                       /* 14 5ST_4                                           */
    (U1)ALERT_REQ_C_VSCEXP_WDSTEP_5ST_5,                                       /* 15 5ST_5                                           */
    (U1)ALERT_REQ_C_VSCEXP_WDSTEP_5ST_0,                                       /* 16 5ST_0                                           */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 17 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 18 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 19 UNKNOWN                                         */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_C_VSCEXP_MTRX[2] = {
    {
        &u4_s_AlertC_vscexpNostepSrcchk,                                       /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_C_VSCEXP_NOSTEP_DST[0],                                   /* u1p_DST                                            */
        (U2)ALERT_C_VSCEXP_NOSTEP_NUM_DST,                                     /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertC_vscexpWdstepSrcchk,                                       /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        &u4_sp_ALERT_C_VSCEXP_WDSTEP_MASK[0],                                  /* u4p_MASK                                           */
        &u4_sp_ALERT_C_VSCEXP_WDSTEP_CRIT[0],                                  /* u4p_CRIT                                           */

        &u1_sp_ALERT_C_VSCEXP_WDSTEP_DST[0],                                   /* u1p_DST                                            */
        (U2)ALERT_C_VSCEXP_WDSTEP_NUM_DST,                                     /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertC_vscexpNostepSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertC_vscexpNostepSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U1 u1_s_ALERT_C_VSCEXP_LSB_MSGSTS   = (U1)2U;
    static const U1 u1_s_ALERT_C_VSCEXP_LSB_EXPTPLUS = (U1)1U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_VSC1S96,
                                     (U2)OXCAN_RX_SYS_NRX_POE,
                                     (U2)U2_MAX) & (U1)COM_NO_RX;
    u4_t_src_chk  = ((U4)u1_t_msgsts << u1_s_ALERT_C_VSCEXP_LSB_MSGSTS);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_EXPTPLUS, &u1_t_sgnl);
    u4_t_src_chk |= ((U4)u1_t_sgnl << u1_s_ALERT_C_VSCEXP_LSB_EXPTPLUS);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_VSCEXPRT, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl;

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertC_vscexpWdstepSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertC_vscexpWdstepSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U1 u1_s_ALERT_C_VSCEXP_LSB_MSGSTS   = (U1)6U;
    static const U1 u1_s_ALERT_C_VSCEXP_LSB_EXPTPLUS = (U1)5U;
    static const U1 u1_s_ALERT_C_VSCEXP_LSB_EXPTCNFG = (U1)3U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_VSC1S96,
                                     (U2)OXCAN_RX_SYS_NRX_POE,
                                     (U2)U2_MAX) & (U1)COM_NO_RX;
    u4_t_src_chk  = ((U4)u1_t_msgsts << u1_s_ALERT_C_VSCEXP_LSB_MSGSTS);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_EXPTPLUS, &u1_t_sgnl);
    u4_t_src_chk |= ((U4)u1_t_sgnl << u1_s_ALERT_C_VSCEXP_LSB_EXPTPLUS);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_EXPTCNFG, &u1_t_sgnl);
    u4_t_src_chk |= ((U4)u1_t_sgnl << u1_s_ALERT_C_VSCEXP_LSB_EXPTCNFG);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_EXPTLVL, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl;

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  5.0.0    10/27/2021  HU       New.                                                                                               */
/*  5.1.0    03/15/2024  GM       19PFv3 Add Expert Mode.                                                                            */
/*                                                                                                                                   */
/*  * HU   = Hidekazu Usui, NTTD MSE                                                                                                 */
/*  * GM   = Glen Monteposo, DTPH                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
