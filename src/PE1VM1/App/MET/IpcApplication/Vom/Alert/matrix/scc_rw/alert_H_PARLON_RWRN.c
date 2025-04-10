/* 5.0.0*/
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert H_PARLON_RWRN                                                                                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_H_PARLON_C_MAJOR                   (5)
#define ALERT_H_PARLON_C_MINOR                   (0)
#define ALERT_H_PARLON_C_PATCH                   (0)

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
#if (ALERT_H_PARLON_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_H_PARLON_RWRN.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_H_PARLON_RWRN_NUM_DST              (16U)

#define ALERT_H_PARLON_HVMALPAT_NUM_TBL          (8U)
#define ALERT_H_PARLON_HVIND_NUM_TBL             (16U)

#define ALERT_H_PARLON_PTSYS_OTHER               (0x00U)
#define ALERT_H_PARLON_PTSYS_FCV                 (0x08U)
#define ALERT_H_PARLON_HVMALPAT_RW_OFF           (0x00U)
#define ALERT_H_PARLON_HVMALPAT_RW_ON            (0x04U)
#define ALERT_H_PARLON_HVIND_RW_OFF              (0x00U)
#define ALERT_H_PARLON_HVIND_RW_FCW1             (0x01U)
#define ALERT_H_PARLON_HVIND_RW_FCW2             (0x02U)

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
static U4      u4_s_AlertH_parlon_rwrnSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static void    vd_s_AlertH_parlon_rwrnRwTx  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_H_PARLON_RWRN_DST[ALERT_H_PARLON_RWRN_NUM_DST] = {
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
    (U1)ALERT_REQ_H_PARLON_RWRN_FCW1REQ,                                       /* 13 FCW1REQ                                         */
    (U1)ALERT_REQ_H_PARLON_RWRN_FCW2REQ,                                       /* 14 FCW2REQ                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 15 UNKNOWN                                         */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_H_PARLON_RWRN_MTRX[1] = {
    {
        &u4_s_AlertH_parlon_rwrnSrcchk,                                        /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertH_parlon_rwrnRwTx,                                          /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_H_PARLON_RWRN_DST[0],                                     /* u1p_DST                                            */
        (U2)ALERT_H_PARLON_RWRN_NUM_DST,                                       /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertH_parlon_rwrnSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertH_parlon_rwrnSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U1 u1_sp_ALERT_H_PARLONRW_MLPT_JDG[ALERT_H_PARLON_HVMALPAT_NUM_TBL] = {
        (U1)ALERT_H_PARLON_HVMALPAT_RW_OFF,
        (U1)ALERT_H_PARLON_HVMALPAT_RW_ON,
        (U1)ALERT_H_PARLON_HVMALPAT_RW_ON,
        (U1)ALERT_H_PARLON_HVMALPAT_RW_ON,
        (U1)ALERT_H_PARLON_HVMALPAT_RW_ON,
        (U1)ALERT_H_PARLON_HVMALPAT_RW_OFF,
        (U1)ALERT_H_PARLON_HVMALPAT_RW_ON,
        (U1)ALERT_H_PARLON_HVMALPAT_RW_OFF
    };
    static const U1 u1_sp_ALERT_H_PARLONRW_HVIND_JDG[ALERT_H_PARLON_HVIND_NUM_TBL] = {
        (U1)ALERT_H_PARLON_HVIND_RW_OFF,
        (U1)ALERT_H_PARLON_HVIND_RW_FCW1,
        (U1)ALERT_H_PARLON_HVIND_RW_FCW2,
        (U1)ALERT_H_PARLON_HVIND_RW_FCW1,
        (U1)ALERT_H_PARLON_HVIND_RW_FCW2,
        (U1)ALERT_H_PARLON_HVIND_RW_FCW2,
        (U1)ALERT_H_PARLON_HVIND_RW_FCW2,
        (U1)ALERT_H_PARLON_HVIND_RW_FCW2,
        (U1)ALERT_H_PARLON_HVIND_RW_FCW2,
        (U1)ALERT_H_PARLON_HVIND_RW_FCW2,
        (U1)ALERT_H_PARLON_HVIND_RW_FCW2,
        (U1)ALERT_H_PARLON_HVIND_RW_FCW1,
        (U1)ALERT_H_PARLON_HVIND_RW_FCW1,
        (U1)ALERT_H_PARLON_HVIND_RW_FCW2,
        (U1)ALERT_H_PARLON_HVIND_RW_FCW2,
        (U1)ALERT_H_PARLON_HVIND_RW_FCW2
    };
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;
    U4              u4_t_ptsys_jdg;
    U4              u4_t_mlpt_jdg;
    U4              u4_t_hvind_jdg;

    u1_t_sgnl          = u1_g_AlertPtsys();
    if(u1_t_sgnl == (U1)ALERT_PARLON_VD_PTSYS_FCV){
        u4_t_ptsys_jdg = (U4)ALERT_H_PARLON_PTSYS_FCV;
    }
    else{
        u4_t_ptsys_jdg = (U4)ALERT_H_PARLON_PTSYS_OTHER;
    }

    u4_t_src_chk       = u4_t_ptsys_jdg;

    u1_t_msgsts        = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_EHV1S26_RXCH0,
                                          (U2)OXCAN_RX_SYS_NRX_IGR,
                                          (U2)U2_MAX) & (U1)COM_NO_RX;

    u1_t_sgnl          = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_HVMALPAT, &u1_t_sgnl);
    if(((u1_t_msgsts & (U1)COM_NO_RX) != (U1)0U                             ) ||
       (u1_t_sgnl                     >= (U1)ALERT_H_PARLON_HVMALPAT_NUM_TBL)){
        u4_t_mlpt_jdg  = (U4)ALERT_H_PARLON_HVMALPAT_RW_OFF;
    }
    else{
        u4_t_mlpt_jdg  = (U4)u1_sp_ALERT_H_PARLONRW_MLPT_JDG[u1_t_sgnl];
    }

    u4_t_src_chk       |= u4_t_mlpt_jdg;

    u1_t_sgnl          = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_HVIND, &u1_t_sgnl);
    if(((u1_t_msgsts & (U1)COM_NO_RX) != (U1)0U                          ) ||
       (u1_t_sgnl                     >= (U1)ALERT_H_PARLON_HVIND_NUM_TBL)){
        u4_t_hvind_jdg = (U4)ALERT_H_PARLON_HVIND_RW_OFF;
    }
    else{
        u4_t_hvind_jdg = (U4)u1_sp_ALERT_H_PARLONRW_HVIND_JDG[u1_t_sgnl];
    }

    u4_t_src_chk       |= u4_t_hvind_jdg;

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static void    vd_s_AlertH_parlon_rwrnRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertH_parlon_rwrnRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)
{
    U1              u1_t_sgnl_fcw1;
    U1              u1_t_sgnl_fcw2;

    if (((u1_a_VOM & (U1)ALERT_VOM_RWT_EN) != (U1)0U                             ) &&
        (u1_a_DST                          == (U1)ALERT_REQ_H_PARLON_RWRN_FCW1REQ)) {
        u1_t_sgnl_fcw1 = (U1)ALERT_RW_SGNL_ON;
    }
    else {
        u1_t_sgnl_fcw1 = (U1)ALERT_RW_SGNL_OFF;
    }

    if (((u1_a_VOM & (U1)ALERT_VOM_IGN_ON) != (U1)0U                             ) &&
        (u1_a_DST                          == (U1)ALERT_REQ_H_PARLON_RWRN_FCW2REQ)) {
        u1_t_sgnl_fcw2 = (U1)ALERT_RW_SGNL_ON;
    }
    else {
        u1_t_sgnl_fcw2 = (U1)ALERT_RW_SGNL_OFF;
    }

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_FCW1, &u1_t_sgnl_fcw1);    /* COM Tx STUB delete */
    (void)Com_SendSignal(ComConf_ComSignal_FCW2, &u1_t_sgnl_fcw2);    /* COM Tx STUB delete */
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
/*  5.0.0     4/30/2024  PG       New. (19PFv3 Remote warning implementation)                                                        */
/*                                                                                                                                   */
/*  * PG   = Patrick Garcia, DTPH                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
