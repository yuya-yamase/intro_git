/* 5.2.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert B_BKEY                                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_B_BKEY_C_MAJOR                     (5)
#define ALERT_B_BKEY_C_MINOR                     (2)
#define ALERT_B_BKEY_C_PATCH                     (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_mtrx_cfg_private.h"
#include "alert_brx.h"

#include "oxcan.h"
#if 0   /* BEV BSW provisionally */
#else
#include "Com_Cfg_STUB.h"
#include "oxcan_channel_STUB.h"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (ALERT_B_BKEY_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_B_BKEY.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_B_BKEY_NUM_DST                     (64U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1      u1_s_alert_b_bkey_msgsts;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_AlertB_bkeySrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_B_BKEY_DST[ALERT_B_BKEY_NUM_DST] = {
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
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 24 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 25 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 26 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 27 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 28 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 29 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 30 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 31 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 32 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 33 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 34 UNKNOWN                                         */
    (U1)ALERT_REQ_B_BKEY_KEYREM,                                               /* 35 KEYREM                                          */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 36 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 37 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 38 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 39 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 40 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 41 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 42 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 43 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 44 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 45 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 46 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 47 UNKNOWN                                         */
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
const ST_ALERT_MTRX st_gp_ALERT_B_BKEY_MTRX[1] = {
    {
        &u4_s_AlertB_bkeySrcchk,                                               /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_B_BKEY_DST[0],                                            /* u1p_DST                                            */
        (U2)ALERT_B_BKEY_NUM_DST,                                              /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_OFF_WT                                               /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_AlertB_bkeyInit(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AlertB_bkeyInit(void)
{
    u1_s_alert_b_bkey_msgsts = (U1)COM_NO_RX;
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertB_bkeySrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertB_bkeySrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_B_BKEY_TO_THRESH     = ((U2)3600U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_B_BKEY_LSB_MSGSTS    = (U1)2U;
    static const U1 u1_s_ALERT_B_BKEY_LSB_SKSW      = (U1)1U;
    static const U4 u4_s_ALERT_B_BKEY_BIT_IGOFF_3P8 = (U4)0x00000010U;
    static const U4 u4_s_ALERT_B_BKEY_BIT_IGOFF_WT  = (U4)0x00000020U;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;
    U1              u1_t_ign_3p8v;
    U4              u4_t_src_chk;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_BDB1S01_RXCH0,
                                     (U2)OXCAN_RX_SYS_NRX_PBA | (U2)OXCAN_RX_SYS_TOE_PBA,
                                     u2_s_ALERT_B_BKEY_TO_THRESH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    vd_g_AlertBRxTrnsSts(&u1_s_alert_b_bkey_msgsts, u1_t_msgsts);
    u4_t_src_chk  = ((U4)u1_s_alert_b_bkey_msgsts << u1_s_ALERT_B_BKEY_LSB_MSGSTS);

    u1_t_sgnl     = (U1)0U;
#if defined(ComConf_ComSignal_SKSW)
    (void)Com_ReceiveSignal(ComConf_ComSignal_SKSW, &u1_t_sgnl);
#endif /* defined(ComConf_ComSignal_SKSW) */
    u4_t_src_chk |= ((U4)u1_t_sgnl << u1_s_ALERT_B_BKEY_LSB_SKSW);

    u1_t_sgnl     = (U1)0U;
#if defined(ComConf_ComSignal_DCTY)
    (void)Com_ReceiveSignal(ComConf_ComSignal_DCTY, &u1_t_sgnl);
#endif /* defined(ComConf_ComSignal_DCTY) */
    u4_t_src_chk |= (U4)u1_t_sgnl;

    u1_t_ign_3p8v = u1_g_IoHwDifltSwitch((U2)ALERT_HW_ID_B_BKEY_IGN__3P8V);
    if(u1_t_ign_3p8v == (U1)IOHW_DIFLT_SWITCH_ACT){
        u4_t_src_chk |= u4_s_ALERT_B_BKEY_BIT_IGOFF_3P8;
    }

    if((u1_a_VOM & (U1)ALERT_VOM_IGN_OFF_WT) != (U1)0U){
        u4_t_src_chk |= u4_s_ALERT_B_BKEY_BIT_IGOFF_WT;
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
/*  5.0.0     3/18/2021  SO       New.                                                                                               */
/*  5.1.0     6/ 7/2021  TM       Add voltage threshold to IG-OFF.                                                                   */
/*  5.1.1     8/23/2021  TM       Add Compile switch.                                                                                */
/*  5.2.0     8/23/2023  JMH      Update for 19Pfv3                                                                                  */
/*                                                                                                                                   */
/*  * SO   = Syuhei Ooshima, NTTD MSE                                                                                                */
/*  * TM   = Tatsuya Mori, NTTD MSE                                                                                                  */
/*  * JMH  = James Michael Hilarion, DTPH                                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/
