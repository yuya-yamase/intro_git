/* 5.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert H_LBW                                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_H_LBW_C_MAJOR                      (5)
#define ALERT_H_LBW_C_MINOR                      (1)
#define ALERT_H_LBW_C_PATCH                      (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_mtrx_cfg_private.h"

#include "oxcan.h"
#if 0   /* BEV BSW provisionally */
#else
#include "oxcan_channel_STUB.h"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (ALERT_H_LBW_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_H_LBW.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_H_LBW_NUM_DST                      (32U)

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
static U4      u4_s_AlertH_lbwSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_H_LBW_DST[ALERT_H_LBW_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_H_LBW_PRMRYCHK,                                              /* 01 PRMRYCHK                                        */
    (U1)ALERT_REQ_H_LBW_LOWBATNOTE,                                            /* 02 LOWBATNOTE                                      */
    (U1)ALERT_REQ_H_LBW_LOWBATWNG,                                             /* 03 LOWBATWNG                                       */
    (U1)ALERT_REQ_H_LBW_BATTEMPWNG,                                            /* 04 BATTEMPWNG                                      */
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
    (U1)ALERT_REQ_H_LBW_LOWBATNOTE,                                            /* 16 LOWBATNOTE                                      */
    (U1)ALERT_REQ_H_LBW_LOWBATNOTE,                                            /* 17 LOWBATNOTE                                      */
    (U1)ALERT_REQ_H_LBW_LOWBATNOTE,                                            /* 18 LOWBATNOTE                                      */
    (U1)ALERT_REQ_H_LBW_LOWBATNOTE,                                            /* 19 LOWBATNOTE                                      */
    (U1)ALERT_REQ_H_LBW_LOWBATNOTE,                                            /* 20 LOWBATNOTE                                      */
    (U1)ALERT_REQ_H_LBW_LOWBATNOTE,                                            /* 21 LOWBATNOTE                                      */
    (U1)ALERT_REQ_H_LBW_LOWBATNOTE,                                            /* 22 LOWBATNOTE                                      */
    (U1)ALERT_REQ_H_LBW_LOWBATNOTE,                                            /* 23 LOWBATNOTE                                      */
    (U1)ALERT_REQ_H_LBW_LOWBATNOTE,                                            /* 24 LOWBATNOTE                                      */
    (U1)ALERT_REQ_H_LBW_LOWBATNOTE,                                            /* 25 LOWBATNOTE                                      */
    (U1)ALERT_REQ_H_LBW_LOWBATNOTE,                                            /* 26 LOWBATNOTE                                      */
    (U1)ALERT_REQ_H_LBW_LOWBATNOTE,                                            /* 27 LOWBATNOTE                                      */
    (U1)ALERT_REQ_H_LBW_LOWBATNOTE,                                            /* 28 LOWBATNOTE                                      */
    (U1)ALERT_REQ_H_LBW_LOWBATNOTE,                                            /* 29 LOWBATNOTE                                      */
    (U1)ALERT_REQ_H_LBW_LOWBATNOTE,                                            /* 30 LOWBATNOTE                                      */
    (U1)ALERT_REQ_H_LBW_LOWBATNOTE                                             /* 31 LOWBATNOTE                                      */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_H_LBW_MTRX[1] = {
    {
        &u4_s_AlertH_lbwSrcchk,                                                /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_H_LBW_DST[0],                                             /* u1p_DST                                            */
        (U2)ALERT_H_LBW_NUM_DST,                                               /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertH_lbwSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertH_lbwSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_H_LBW_TRSH_EHV1S26 = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_H_LBW_LSB_EHV1S26  = (U1)3U;

    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_EHV1S26_CH0,
                                     (U4)OXCAN_SYS_IGP,
                                     u2_s_ALERT_H_LBW_TRSH_EHV1S26) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    u4_t_src_chk  = ((U4)u1_t_msgsts << u1_s_ALERT_H_LBW_LSB_EHV1S26);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_EVBATLO, &u1_t_sgnl);
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
/*  5.0.0    12/10/2020  KT       New.                                                                                               */
/*  5.1.0    06/20/2024  JMH      Updated for 19PFv3.                                                                                */
/*                                                                                                                                   */
/*  * KT   = Kenichi Takahashi, NTTD MSE                                                                                             */
/*  * JMH  = James Michael D. Hilarion, DTPH                                                                                         */
/*                                                                                                                                   */
/*===================================================================================================================================*/
