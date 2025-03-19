/* 5.1.0*/
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert H_ZMILRQ                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_H_ZMILRQ_C_MAJOR                   (5)
#define ALERT_H_ZMILRQ_C_MINOR                   (1)
#define ALERT_H_ZMILRQ_C_PATCH                   (0)

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
#if (ALERT_H_ZMILRQ_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_H_ZMILRQ.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_H_ZMILRQ_RWRN_NUM_DST              (4U)

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
static U4      u4_s_AlertH_zmilrqRwrnSrcchk (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static void    vd_s_AlertH_zmilrqRwrnRwTx   (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_H_ZMILRQ_RWRN_DST[ALERT_H_ZMILRQ_RWRN_NUM_DST] = {
    (U1)ALERT_REQ_H_ZMILRQ_RWRN_ZESWREQ,                                       /* 00 ZESWREQ                                         */
    (U1)ALERT_REQ_H_ZMILRQ_RWRN_ZESWREQ,                                       /* 01 ZESWREQ                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_H_ZMILRQ_RWRN_ZESWREQ                                        /* 03 ZESWREQ                                         */
};

static const U4  u4_sp_ALERT_H_ZMILRQ_RWRN_CRIT[ALERT_H_ZMILRQ_RWRN_NUM_DST] = {
    (U4)0x00000002U,                                                           /* 00 ZESWREQ                                         */
    (U4)0x00000020U,                                                           /* 01 ZESWREQ                                         */
    (U4)0x00000100U,                                                           /* 02 UNKNOWN                                         */
    (U4)0x00000200U                                                            /* 03 ZESWREQ                                         */
};

static const U4  u4_sp_ALERT_H_ZMILRQ_RWRN_MASK[ALERT_H_ZMILRQ_RWRN_NUM_DST] = {
    (U4)0x0000030FU,                                                           /* 00 ZESWREQ                                         */
    (U4)0x000003F0U,                                                           /* 01 ZESWREQ                                         */
    (U4)0x00000300U,                                                           /* 02 UNKNOWN                                         */
    (U4)0x00000200U                                                            /* 03 ZESWREQ                                         */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_H_ZMILRQ_MTRX[1] = {
    {
        &u4_s_AlertH_zmilrqRwrnSrcchk,                                         /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertH_zmilrqRwrnRwTx,                                           /* fp_vd_XDST                                         */

        &u4_sp_ALERT_H_ZMILRQ_RWRN_MASK[0],                                    /* u4p_MASK                                           */
        &u4_sp_ALERT_H_ZMILRQ_RWRN_CRIT[0],                                    /* u4p_CRIT                                           */

        &u1_sp_ALERT_H_ZMILRQ_RWRN_DST[0],                                     /* u1p_DST                                            */
        (U2)ALERT_H_ZMILRQ_RWRN_NUM_DST,                                       /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertH_zmilrqRwrnSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertH_zmilrqRwrnSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_H_ZMILRQ_RWRN_TO_THRSH  = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_H_ZMILRQ_RWRN_LSB_AMBER = (U1)4U;
    static const U1 u1_s_ALERT_H_ZMILRQ_RWRN_LSB_MSG   = (U1)8U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl_amber;
    U1              u1_t_sgnl_red;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_EHV1S99_RXCH0,
                                     (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                     u2_s_ALERT_H_ZMILRQ_RWRN_TO_THRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    u1_t_sgnl_red = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_EVMILRQR, &u1_t_sgnl_red);

    u1_t_sgnl_amber = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_EVMILRQA, &u1_t_sgnl_amber);

    u4_t_src_chk  = (U4)u1_t_sgnl_red;
    u4_t_src_chk  |= ((U4)u1_t_sgnl_amber << u1_s_ALERT_H_ZMILRQ_RWRN_LSB_AMBER);
    u4_t_src_chk  |= ((U4)u1_t_msgsts << u1_s_ALERT_H_ZMILRQ_RWRN_LSB_MSG);

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static void    vd_s_AlertH_zmilrqRwrnRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertH_zmilrqRwrnRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)
{
    static const U4 u4_s_ALERT_H_ZMILRQ_TIM_RW_ENBL = ((U4)15000U / (U4)ALERT_MAIN_TICK);
    U1              u1_t_sgnl;
    U1              u1_t_milreq_ava;

    if(((u1_a_VOM & (U1)ALERT_VOM_IGN_ON) != (U1)0U                             ) &&
       (u4_a_IGN_TM                       >= u4_s_ALERT_H_ZMILRQ_TIM_RW_ENBL    ) &&
       (u1_a_DST                          == (U1)ALERT_REQ_H_ZMILRQ_RWRN_ZESWREQ)){
        u1_t_sgnl = (U1)ALERT_RW_SGNL_ON;
    }
    else{
        u1_t_sgnl = (U1)ALERT_RW_SGNL_OFF;
    }

    /*MILREQ TT and ZMILRQ TT is exclusive*/
    /*When MILREQ is Available, ZMILRQ will be Not Available*/
    u1_t_milreq_ava = u1_g_AlertEsOptAvailable(ALERT_OPT_ID_P_MILREQ_PTSYS);
    if(u1_t_milreq_ava == (U1)TRUE){
        u1_t_sgnl = (U1)ALERT_RW_SGNL_OFF;
    }

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_ZESW, &u1_t_sgnl);    /* COM Tx STUB delete */
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
/*  5.0.0     7/ 8/2024  PG       Newly created for 19PFv3                                                                           */
/*  5.1.0     12/23/2024 KO       Change for BEV System_Consideration_1.                                                             */
/*                                                                                                                                   */
/*  * PG   = Patrick Garcia, DTPH                                                                                                    */
/*  * KO   = Kazuto Oishi,  Denso Techno                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
