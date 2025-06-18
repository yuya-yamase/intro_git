/* 5.4.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert D_SFTPOS                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_D_SFTPOS_C_MAJOR                   (5)
#define ALERT_D_SFTPOS_C_MINOR                   (4)
#define ALERT_D_SFTPOS_C_PATCH                   (0)

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
#if (ALERT_D_SFTPOS_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_D_SFTPOS.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_D_SFTPOS_B_RJTB_NUM_DST            (4U)
#define ALERT_D_SFTPOS_B_RSBW_NUM_DST            (19U)

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
static U4      u4_s_AlertD_sftposBRjtbSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertD_sftposBRsbwSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_D_SFTPOS_B_RJTB_DST[ALERT_D_SFTPOS_B_RJTB_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_D_SFTPOS_B_RJTB_DBL1,                                        /* 01 DBL1                                            */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 03 UNKNOWN                                         */
};

static const U4  u4_sp_ALERT_D_SFTPOS_B_RSBW_CRIT[ALERT_D_SFTPOS_B_RSBW_NUM_DST] = {
    (U4)0x00000000U,                                                           /* 00 UNKNOWN                                         */
    (U4)0x00000040U,                                                           /* 01 UNKNOWN                                         */
    (U4)0x00000041U,                                                           /* 02 UNKNOWN                                         */
    (U4)0x00000042U,                                                           /* 03 CYCLE                                           */
    (U4)0x00000043U,                                                           /* 04 UNKNOWN                                         */
    (U4)0x00000044U,                                                           /* 05 UNKNOWN                                         */
    (U4)0x00000045U,                                                           /* 06 UNKNOWN                                         */
    (U4)0x00000046U,                                                           /* 07 UNKNOWN                                         */
    (U4)0x00000047U,                                                           /* 08 UNKNOWN                                         */
    (U4)0x00000048U,                                                           /* 09 UNKNOWN                                         */
    (U4)0x00000049U,                                                           /* 10 UNKNOWN                                         */
    (U4)0x0000004AU,                                                           /* 11 UNKNOWN                                         */
    (U4)0x0000004BU,                                                           /* 12 UNKNOWN                                         */
    (U4)0x0000004CU,                                                           /* 13 UNKNOWN                                         */
    (U4)0x0000004DU,                                                           /* 14 UNKNOWN                                         */
    (U4)0x0000004EU,                                                           /* 15 UNKNOWN                                         */
    (U4)0x0000004FU,                                                           /* 16 UNKNOWN                                         */
    (U4)0x00000050U,                                                           /* 17 UNKNOWN                                         */
    (U4)0x00000060U                                                            /* 18 UNKNOWN                                         */
};

static const U4  u4_sp_ALERT_D_SFTPOS_B_RSBW_MASK[ALERT_D_SFTPOS_B_RSBW_NUM_DST] = {
    (U4)0x00000040U,                                                           /* 00 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 01 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 02 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 03 CYCLE                                           */
    (U4)0x0000007FU,                                                           /* 04 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 05 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 06 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 07 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 08 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 09 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 10 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 11 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 12 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 13 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 14 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 15 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 16 UNKNOWN                                         */
    (U4)0x00000070U,                                                           /* 17 UNKNOWN                                         */
    (U4)0x00000060U                                                            /* 18 UNKNOWN                                         */
};

static const U1  u1_sp_ALERT_D_SFTPOS_B_RSBW_DST[ALERT_D_SFTPOS_B_RSBW_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 01 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_D_SFTPOS_B_RSBW_CYCLE,                                       /* 03 CYCLE                                           */
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
    (U1)ALERT_REQ_UNKNOWN                                                      /* 18 UNKNOWN                                         */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_D_SFTPOS_MTRX[2] = {
    {
        &u4_s_AlertD_sftposBRjtbSrcchk,                                        /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_D_SFTPOS_B_RJTB_DST[0],                                   /* u1p_DST                                            */
        (U2)ALERT_D_SFTPOS_B_RJTB_NUM_DST,                                     /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertD_sftposBRsbwSrcchk,                                        /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        &u4_sp_ALERT_D_SFTPOS_B_RSBW_MASK[0],                                  /* u4p_MASK                                           */
        &u4_sp_ALERT_D_SFTPOS_B_RSBW_CRIT[0],                                  /* u4p_CRIT                                           */

        &u1_sp_ALERT_D_SFTPOS_B_RSBW_DST[0],                                   /* u1p_DST                                            */
        (U2)ALERT_D_SFTPOS_B_RSBW_NUM_DST,                                     /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertD_sftposBRjtbSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertD_sftposBRjtbSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U1 u1_s_ALERT_D_SFTPOS_BC_LSB_ECT   = (U1)1U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ECT1G92_RXCH0,
                                     (U2)OXCAN_RX_SYS_NRX_IGR,
                                     (U2)U2_MAX) & (U1)COM_NO_RX;

    u4_t_src_chk  = ((U4)u1_t_msgsts << u1_s_ALERT_D_SFTPOS_BC_LSB_ECT);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_B_RJTB, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl;


    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertD_sftposBRsbwSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertD_sftposBRsbwSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_D_SFTPOS_TO_THRESH        = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U4 u4_s_ALERT_D_SFTPOS_BIT_INTERMITTENT = (U4)0x00000040U;
    static const U1 u1_s_ALERT_D_SFTPOS_LSB_MSGSTS       = (U1)4U;
    U4              u4_t_src_chk;
    U1              u1_t_sgnl;
    U1              u1_t_msgsts;
    U4              u4_t_intermittent;

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_SFT_METS, &u1_t_sgnl);
    u4_t_src_chk  = (U4)u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_PCN1S01_RXCH0,
                                     (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                     u2_s_ALERT_D_SFTPOS_TO_THRESH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_D_SFTPOS_LSB_MSGSTS);

    u4_t_intermittent = u4_g_AlertRevBzrSoundType();
    if(u4_t_intermittent == (U4)ALERT_SHIFT_BZ_REV_SOUNDTYPE_IN){
        u4_t_src_chk |= u4_s_ALERT_D_SFTPOS_BIT_INTERMITTENT;
    }

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
/*  5.0.0     3/ 3/2020  SM       New.                                                                                               */
/*  5.1.0    12/ 8/2020  TN       Change The processing order of the CAN signal.                                                     */
/*  5.2.0     1/19/2022  RI       Add CH for PD.                                                                                     */
/*  5.2.1     5/26/2022  HU       Fix QAC Warning(Empty if Statement).                                                               */
/*  5.2.2     1/24/2023  SS       Update for 345D 1A(Version update).                                                                */
/*  5.3.3    12/19/2023  GM       Update for 19PFv3 CV              .                                                                */
/*  5.3.3-BEV-1                                                                                                                      */
/*            2/ 6/2025  SF       Setting for BEV System_Consideration_1.                                                            */
/*  5.4.0    03/21/2025  HF       Setting for BEV System_Consideration_1.                                                            */
/*                                                                                                                                   */
/*  * SM   = Shingo Miyamoto, NTTD MSE                                                                                               */
/*  * TN   = Toshiaki Nagashima, NTTD MSE                                                                                            */
/*  * RI   = Ren Ito, NTTD MSE                                                                                                       */
/*  * HU   = Hidekazu Usui, NTTD MSE                                                                                                 */
/*  * SS   = Shuji Suzuki, NTTD MSE                                                                                                  */
/*  * GM   = Glen Monteposo, DTPH                                                                                                    */
/*  * HF   = Hinari Fukamachi, KSE                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
