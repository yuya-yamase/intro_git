/* 5.3.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert H_EVMOD                                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_H_EVMOD_C_MAJOR                    (5)
#define ALERT_H_EVMOD_C_MINOR                    (3)
#define ALERT_H_EVMOD_C_PATCH                    (0)

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
#if (ALERT_H_EVMOD_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_H_EVMOD.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_H_EVMOD_TT_NUM_DST                 (5U)
#define ALERT_H_EVMOD_PD_NUM_DST                 (10U)
#define ALERT_H_EVMOD_BC_NUM_DST                 (9U)

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
static U4      u4_s_AlertH_evmodTtSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertH_evmodPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertH_evmodBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U4  u4_sp_ALERT_H_EVMOD_TT_CRIT[ALERT_H_EVMOD_TT_NUM_DST] = {
    (U4)0x00000067U,                                                           /* 00 FLS_LOWBT_V                                     */
    (U4)0x00000068U,                                                           /* 01 FLS_SPD_V                                       */
    (U4)0x00000069U,                                                           /* 02 FLS_ACCL_V                                      */
    (U4)0x0000006AU,                                                           /* 03 FLS_OTHER_V                                     */
    (U4)0x0000006BU                                                            /* 04 ON                                              */
};
static const U4  u4_sp_ALERT_H_EVMOD_TT_MASK[ALERT_H_EVMOD_TT_NUM_DST] = {
    (U4)0x000001FFU,                                                           /* 00 FLS_LOWBT_V                                     */
    (U4)0x000001FFU,                                                           /* 01 FLS_SPD_V                                       */
    (U4)0x000001FFU,                                                           /* 02 FLS_ACCL_V                                      */
    (U4)0x000001FFU,                                                           /* 03 FLS_OTHER_V                                     */
    (U4)0x000001FFU                                                            /* 04 ON                                              */
};
static const U1  u1_sp_ALERT_H_EVMOD_TT_DST[ALERT_H_EVMOD_TT_NUM_DST] = {
    (U1)ALERT_REQ_H_EVMOD_TT_FLS_LOWBT_V,                                      /* 00 FLS_LOWBT_V                                     */
    (U1)ALERT_REQ_H_EVMOD_TT_FLS_SPD_V,                                        /* 01 FLS_SPD_V                                       */
    (U1)ALERT_REQ_H_EVMOD_TT_FLS_ACCL_V,                                       /* 02 FLS_ACCL_V                                      */
    (U1)ALERT_REQ_H_EVMOD_TT_FLS_OTHER_V,                                      /* 03 FLS_OTHER_V                                     */
    (U1)ALERT_REQ_H_EVMOD_TT_ON                                                /* 04 ON                                              */
};
static const U4  u4_sp_ALERT_H_EVMOD_PD_CRIT[ALERT_H_EVMOD_PD_NUM_DST] = {
    (U4)0x00000061U,                                                           /* 00 UNAVE_WRMUP                                     */
    (U4)0x00000062U,                                                           /* 01 UNAVE_LOWBT                                     */
    (U4)0x00000063U,                                                           /* 02 UNAVE_SPD                                       */
    (U4)0x00000064U,                                                           /* 03 UNAVE_ACCL                                      */
    (U4)0x00000065U,                                                           /* 04 UNAVE                                           */
    (U4)0x00000067U,                                                           /* 05 DETCT_LOWBT                                     */
    (U4)0x00000068U,                                                           /* 06 DETCT_SPD                                       */
    (U4)0x00000069U,                                                           /* 07 DETCT_ACCL                                      */
    (U4)0x0000006AU,                                                           /* 08 DETCT                                           */
    (U4)0x0000006BU                                                            /* 09 OFF                                             */
};
static const U4  u4_sp_ALERT_H_EVMOD_PD_MASK[ALERT_H_EVMOD_PD_NUM_DST] = {
    (U4)0x000001FFU,                                                           /* 00 UNAVE_WRMUP                                     */
    (U4)0x000001FFU,                                                           /* 01 UNAVE_LOWBT                                     */
    (U4)0x000001FFU,                                                           /* 02 UNAVE_SPD                                       */
    (U4)0x000001FFU,                                                           /* 03 UNAVE_ACCL                                      */
    (U4)0x000001FFU,                                                           /* 04 UNAVE                                           */
    (U4)0x000001FFU,                                                           /* 05 DETCT_LOWBT                                     */
    (U4)0x000001FFU,                                                           /* 06 DETCT_SPD                                       */
    (U4)0x000001FFU,                                                           /* 07 DETCT_ACCL                                      */
    (U4)0x000001FFU,                                                           /* 08 DETCT                                           */
    (U4)0x000001FFU                                                            /* 09 OFF                                             */
};
static const U1  u1_sp_ALERT_H_EVMOD_PD_DST[ALERT_H_EVMOD_PD_NUM_DST] = {
    (U1)ALERT_REQ_H_EVMOD_PD_UNAVE_WRMUP,                                      /* 00 UNAVE_WRMUP                                     */
    (U1)ALERT_REQ_H_EVMOD_PD_UNAVE_LOWBT,                                      /* 01 UNAVE_LOWBT                                     */
    (U1)ALERT_REQ_H_EVMOD_PD_UNAVE_SPD,                                        /* 02 UNAVE_SPD                                       */
    (U1)ALERT_REQ_H_EVMOD_PD_UNAVE_ACCL,                                       /* 03 UNAVE_ACCL                                      */
    (U1)ALERT_REQ_H_EVMOD_PD_UNAVE,                                            /* 04 UNAVE                                           */
    (U1)ALERT_REQ_H_EVMOD_PD_DETCT_LOWBT,                                      /* 05 DETCT_LOWBT                                     */
    (U1)ALERT_REQ_H_EVMOD_PD_DETCT_SPD,                                        /* 06 DETCT_SPD                                       */
    (U1)ALERT_REQ_H_EVMOD_PD_DETCT_ACCL,                                       /* 07 DETCT_ACCL                                      */
    (U1)ALERT_REQ_H_EVMOD_PD_DETCT,                                            /* 08 DETCT                                           */
    (U1)ALERT_REQ_H_EVMOD_PD_OFF                                               /* 09 OFF                                             */
};
static const U4  u4_sp_ALERT_H_EVMOD_BC_CRIT[ALERT_H_EVMOD_BC_NUM_DST] = {
    (U4)0x00000061U,                                                           /* 00 UNVE_WMUP_V                                     */
    (U4)0x00000062U,                                                           /* 01 UNVE_LWBT_V                                     */
    (U4)0x00000063U,                                                           /* 02 UNVE_SPD_V                                      */
    (U4)0x00000064U,                                                           /* 03 UNVE_ACCL_V                                     */
    (U4)0x00000065U,                                                           /* 04 UNAVE_V                                         */
    (U4)0x00000067U,                                                           /* 05 DTCT_LWBT_V                                     */
    (U4)0x00000068U,                                                           /* 06 DTCT_SPD_V                                      */
    (U4)0x00000069U,                                                           /* 07 DTCT_ACCL_V                                     */
    (U4)0x0000006AU                                                            /* 08 DETCT_V                                         */
};
static const U4  u4_sp_ALERT_H_EVMOD_BC_MASK[ALERT_H_EVMOD_BC_NUM_DST] = {
    (U4)0x000001FFU,                                                           /* 00 UNVE_WMUP_V                                     */
    (U4)0x000001FFU,                                                           /* 01 UNVE_LWBT_V                                     */
    (U4)0x000001FFU,                                                           /* 02 UNVE_SPD_V                                      */
    (U4)0x000001FFU,                                                           /* 03 UNVE_ACCL_V                                     */
    (U4)0x000001FFU,                                                           /* 04 UNAVE_V                                         */
    (U4)0x000001FFU,                                                           /* 05 DTCT_LWBT_V                                     */
    (U4)0x000001FFU,                                                           /* 06 DTCT_SPD_V                                      */
    (U4)0x000001FFU,                                                           /* 07 DTCT_ACCL_V                                     */
    (U4)0x000001FFU                                                            /* 08 DETCT_V                                         */
};
static const U1  u1_sp_ALERT_H_EVMOD_BC_DST[ALERT_H_EVMOD_BC_NUM_DST] = {
    (U1)ALERT_REQ_H_EVMOD_BC_UNVE_WMUP_V,                                      /* 00 UNVE_WMUP_V                                     */
    (U1)ALERT_REQ_H_EVMOD_BC_UNVE_LWBT_V,                                      /* 01 UNVE_LWBT_V                                     */
    (U1)ALERT_REQ_H_EVMOD_BC_UNVE_SPD_V,                                       /* 02 UNVE_SPD_V                                      */
    (U1)ALERT_REQ_H_EVMOD_BC_UNVE_ACCL_V,                                      /* 03 UNVE_ACCL_V                                     */
    (U1)ALERT_REQ_H_EVMOD_BC_UNAVE_V,                                          /* 04 UNAVE_V                                         */
    (U1)ALERT_REQ_H_EVMOD_BC_DTCT_LWBT_V,                                      /* 05 DTCT_LWBT_V                                     */
    (U1)ALERT_REQ_H_EVMOD_BC_DTCT_SPD_V,                                       /* 06 DTCT_SPD_V                                      */
    (U1)ALERT_REQ_H_EVMOD_BC_DTCT_ACCL_V,                                      /* 07 DTCT_ACCL_V                                     */
    (U1)ALERT_REQ_H_EVMOD_BC_DETCT_V                                           /* 08 DETCT_V                                         */
};
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_H_EVMOD_MTRX[3] = {
    {
        &u4_s_AlertH_evmodTtSrcchk,                                            /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        &u4_sp_ALERT_H_EVMOD_TT_MASK[0],                                       /* u4p_MASK                                           */
        &u4_sp_ALERT_H_EVMOD_TT_CRIT[0],                                       /* u4p_CRIT                                           */

        &u1_sp_ALERT_H_EVMOD_TT_DST[0],                                        /* u1p_DST                                            */
        (U2)ALERT_H_EVMOD_TT_NUM_DST,                                          /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertH_evmodPdSrcchk,                                            /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        &u4_sp_ALERT_H_EVMOD_PD_MASK[0],                                       /* u4p_MASK                                           */
        &u4_sp_ALERT_H_EVMOD_PD_CRIT[0],                                       /* u4p_CRIT                                           */

        &u1_sp_ALERT_H_EVMOD_PD_DST[0],                                        /* u1p_DST                                            */
        (U2)ALERT_H_EVMOD_PD_NUM_DST,                                          /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertH_evmodBcSrcchk,                                            /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        &u4_sp_ALERT_H_EVMOD_BC_MASK[0],                                       /* u4p_MASK                                           */
        &u4_sp_ALERT_H_EVMOD_BC_CRIT[0],                                       /* u4p_CRIT                                           */

        &u1_sp_ALERT_H_EVMOD_BC_DST[0],                                        /* u1p_DST                                            */
        (U2)ALERT_H_EVMOD_BC_NUM_DST,                                          /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertH_evmodTtSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertH_evmodTtSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U1 u1_s_ALERT_HEVMODETT_LSB_EHV1F04_MSGSTS = (U1)4U;
    static const U1 u1_s_ALERT_HEVMODETT_LSB_PTSYS_SIGSTS   = (U1)5U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_sgnl = u1_g_AlertPtsys();

    u4_t_src_chk = (U4)u1_t_sgnl << u1_s_ALERT_HEVMODETT_LSB_PTSYS_SIGSTS;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_EHV1F04_RXCH0,
                                     (U2)OXCAN_RX_SYS_NRX_IGR,
                                     (U2)U2_MAX) & (U1)COM_NO_RX;

    (void)Com_ReceiveSignal(ComConf_ComSignal_EVM_MSG, &u1_t_sgnl);

    u4_t_src_chk |= (U4)u1_t_sgnl;
    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_HEVMODETT_LSB_EHV1F04_MSGSTS);

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertH_evmodPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertH_evmodPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U1 u1_s_ALERT_HEVMODEPD_LSB_EHV1F04_MSGSTS = (U1)4U;
    static const U1 u1_s_ALERT_HEVMODEPD_LSB_PTSYS_SIGSTS   = (U1)5U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_sgnl = u1_g_AlertPtsys();

    u4_t_src_chk = (U4)u1_t_sgnl << u1_s_ALERT_HEVMODEPD_LSB_PTSYS_SIGSTS;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_EHV1F04_RXCH0,
                                     (U2)OXCAN_RX_SYS_NRX_IGR,
                                     (U2)U2_MAX) & (U1)COM_NO_RX;

    (void)Com_ReceiveSignal(ComConf_ComSignal_EVM_MSG, &u1_t_sgnl);

    u4_t_src_chk |= (U4)u1_t_sgnl;
    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_HEVMODEPD_LSB_EHV1F04_MSGSTS);

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertH_evmodBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertH_evmodBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U1 u1_s_ALERT_HEVMODEBC_LSB_EHV1F04_MSGSTS = (U1)4U;
    static const U1 u1_s_ALERT_HEVMODEBC_LSB_PTSYS_SIGSTS   = (U1)5U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_sgnl = u1_g_AlertPtsys();

    u4_t_src_chk = (U4)u1_t_sgnl << u1_s_ALERT_HEVMODEBC_LSB_PTSYS_SIGSTS;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_EHV1F04_RXCH0,
                                     (U2)OXCAN_RX_SYS_NRX_IGR,
                                     (U2)U2_MAX) & (U1)COM_NO_RX;

    (void)Com_ReceiveSignal(ComConf_ComSignal_EVM_MSG, &u1_t_sgnl);

    u4_t_src_chk |= (U4)u1_t_sgnl;
    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_HEVMODEBC_LSB_EHV1F04_MSGSTS);

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
/*  5.0.0     4/ 9/2020  TH       New.                                                                                               */
/*  5.1.0     5/13/2020  ZS       Added u4_s_AlertH_evmodBcSrcchk for buzzer.                                                        */
/*  5.1.1     9/02/2020  TI       Filename Change.                                                                                   */
/*  5.1.2    10/12/2022  SM       Update for 345D CV(Version update).                                                                */
/*  5.2.0     1/19/2024  SW       Update for 19PFv3 CVInternalMarge#2.                                                               */
/*  5.3.0     5/22/2024  YR       Update for 19PFv3 CV(PTSYS data source update)                                                     */
/*                                                                                                                                   */
/*  * TH   = Takuya Hiraide, NTTD MSE                                                                                                */
/*  * ZS   = Zenjiro Shamoto, NTTD MSE                                                                                               */
/*  * TI   = Takuro Iwanaga, NTTD MSE                                                                                                */
/*  * SM   = Shingo Miyamoto, NTTD MSE                                                                                               */
/*  * SW   = Shun Watanabe, Denso Techno                                                                                             */
/*  * YR   = Yhana Regalario, DTPH                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
