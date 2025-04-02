/* 5.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert S_MAPACC                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_S_MAPACC_C_MAJOR                      (5)
#define ALERT_S_MAPACC_C_MINOR                      (0)
#define ALERT_S_MAPACC_C_PATCH                      (0)

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
#if (ALERT_S_MAPACC_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_S_MAPACC.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_S_MAPACC_NUM_DST                   (35U)

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
static U4      u4_s_AlertS_mapaccSrcchk (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_S_MAPACC_DST[ALERT_S_MAPACC_NUM_DST] = {
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
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 20 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 21 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 22 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 23 UNKNOWN                                         */
    (U1)ALERT_REQ_S_MAPACC_BRAKE,                                              /* 24 BRAKE                                           */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 25 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 26 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 27 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 28 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 29 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 30 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 31 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 32 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 33 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 34 UNKNOWN                                         */
};

static const U4  u4_sp_ALERT_S_MAPACC_CRIT[ALERT_S_MAPACC_NUM_DST] = {
    (U4)0x00000000U,                                                           /* 00 UNKNOWN                                         */
    (U4)0x00000001U,                                                           /* 01 UNKNOWN                                         */
    (U4)0x00000002U,                                                           /* 02 UNKNOWN                                         */
    (U4)0x00000003U,                                                           /* 03 UNKNOWN                                         */
    (U4)0x00000004U,                                                           /* 04 UNKNOWN                                         */
    (U4)0x00000005U,                                                           /* 05 UNKNOWN                                         */
    (U4)0x00000006U,                                                           /* 06 UNKNOWN                                         */
    (U4)0x00000007U,                                                           /* 07 UNKNOWN                                         */
    (U4)0x00000008U,                                                           /* 08 UNKNOWN                                         */
    (U4)0x00000009U,                                                           /* 09 UNKNOWN                                         */
    (U4)0x0000000AU,                                                           /* 10 UNKNOWN                                         */
    (U4)0x0000000BU,                                                           /* 11 UNKNOWN                                         */
    (U4)0x0000000CU,                                                           /* 12 UNKNOWN                                         */
    (U4)0x0000000DU,                                                           /* 13 UNKNOWN                                         */
    (U4)0x0000000EU,                                                           /* 14 UNKNOWN                                         */
    (U4)0x0000000FU,                                                           /* 15 UNKNOWN                                         */
    (U4)0x00000010U,                                                           /* 16 UNKNOWN                                         */
    (U4)0x00000011U,                                                           /* 17 UNKNOWN                                         */
    (U4)0x00000012U,                                                           /* 18 UNKNOWN                                         */
    (U4)0x00000013U,                                                           /* 19 UNKNOWN                                         */
    (U4)0x00000014U,                                                           /* 20 UNKNOWN                                         */
    (U4)0x00000015U,                                                           /* 21 UNKNOWN                                         */
    (U4)0x00000016U,                                                           /* 22 UNKNOWN                                         */
    (U4)0x00000017U,                                                           /* 23 UNKNOWN                                         */
    (U4)0x00000018U,                                                           /* 24 BRAKE                                           */
    (U4)0x00000019U,                                                           /* 25 UNKNOWN                                         */
    (U4)0x0000001AU,                                                           /* 26 UNKNOWN                                         */
    (U4)0x0000001BU,                                                           /* 27 UNKNOWN                                         */
    (U4)0x0000001CU,                                                           /* 28 UNKNOWN                                         */
    (U4)0x0000001DU,                                                           /* 29 UNKNOWN                                         */
    (U4)0x0000001EU,                                                           /* 30 UNKNOWN                                         */
    (U4)0x0000001FU,                                                           /* 31 UNKNOWN                                         */
    (U4)0x00000020U,                                                           /* 32 UNKNOWN                                         */
    (U4)0x00000040U,                                                           /* 33 UNKNOWN                                         */
    (U4)0x00000060U                                                            /* 34 UNKNOWN                                         */
};

static const U4  u4_sp_ALERT_S_MAPACC_MASK[ALERT_S_MAPACC_NUM_DST] = {
    (U4)0x0000007FU,                                                           /* 00 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 01 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 02 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 03 UNKNOWN                                         */
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
    (U4)0x0000007FU,                                                           /* 17 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 18 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 19 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 20 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 21 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 22 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 23 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 24 BRAKE                                           */
    (U4)0x0000007FU,                                                           /* 25 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 26 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 27 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 28 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 29 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 30 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 31 UNKNOWN                                         */
    (U4)0x00000060U,                                                           /* 32 UNKNOWN                                         */
    (U4)0x00000060U,                                                           /* 33 UNKNOWN                                         */
    (U4)0x00000060U                                                            /* 34 UNKNOWN                                         */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_S_MAPACC_MTRX[1] = {
    {
        &u4_s_AlertS_mapaccSrcchk,                                             /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        &u4_sp_ALERT_S_MAPACC_MASK[0],                                         /* u4p_MASK                                           */
        &u4_sp_ALERT_S_MAPACC_CRIT[0],                                         /* u4p_CRIT                                           */

        &u1_sp_ALERT_S_MAPACC_DST[0],                                          /* u1p_DST                                            */
        (U2)ALERT_S_MAPACC_NUM_DST,                                            /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertS_mapaccSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertS_mapaccSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{

    static const U2 u2_s_ALERT_ACCMSG3_TO_THRESH  = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_ACCMSG3_LSB_MSGSTS = (U1)5U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_FCM1S40_RXCH0,
                                     (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                     u2_s_ALERT_ACCMSG3_TO_THRESH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_ACCMSG3, &u1_t_sgnl);

    u4_t_src_chk  = (U4)u1_t_sgnl;
    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_ACCMSG3_LSB_MSGSTS);

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
/*  5.0.0    01/15/2024  RO       New.                                                                                               */
/*                                                                                                                                   */
/*  * RO   = Ryo Oohashi, KSE                                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
