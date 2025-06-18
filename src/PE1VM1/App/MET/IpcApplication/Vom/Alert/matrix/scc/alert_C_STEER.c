/* 5.3.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert C_STEER                                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_C_STEER_C_MAJOR                      (5)
#define ALERT_C_STEER_C_MINOR                      (3)
#define ALERT_C_STEER_C_PATCH                      (0)

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
#if (ALERT_C_STEER_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_C_STEER.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_C_STEER_TT_NUM_DST                 (32U)
#define ALERT_C_STEER_BC_NUM_DST                 (16U)
#define ALERT_C_STEER_PD_NUM_DST                 (37U)
#define ALERT_C_STEER_RWRN_NUM_DST               (8U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if defined(OXCAN_PDU_RX_CAN_EPS1S90_RXCH0) && defined(ComConf_ComSignal_EPS_MINF)
static U1      u1_s_alert_c_steerpd_msgsts;
#endif /* defined(OXCAN_PDU_RX_CAN_EPS1S90_RXCH0) && defined(ComConf_ComSignal_EPS_MINF) */
#if defined(OXCAN_PDU_RX_CAN_EPS1S90_RXCH0) && defined(ComConf_ComSignal_EPS_REMT)
static U1      u1_s_alert_c_steerrw_msgsts;
#endif /* defined(OXCAN_PDU_RX_CAN_EPS1S90_RXCH0) && defined(ComConf_ComSignal_EPS_REMT) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_AlertC_steerTtSrcchk  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertC_steerBcSrcchk  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertC_steerPdSrcchk  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertC_steerRwrnSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static void    vd_s_AlertC_steerRwrnRwTx  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_C_STEER_TT_DST[ALERT_C_STEER_TT_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 01 UNKNOWN                                         */
    (U1)ALERT_REQ_C_STEER_TT_FLASH_4HZ,                                        /* 02 FLASH_4HZ                                       */
    (U1)ALERT_REQ_C_STEER_TT_ON_R,                                             /* 03 ON_R                                            */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_C_STEER_TT_ON_A,                                             /* 07 ON_A                                            */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 08 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 09 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 10 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 11 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 13 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 14 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 15 UNKNOWN                                         */
    (U1)ALERT_REQ_C_STEER_TT_ON_R,                                             /* 16 ON_R                                            */
    (U1)ALERT_REQ_C_STEER_TT_ON_R,                                             /* 17 ON_R                                            */
    (U1)ALERT_REQ_C_STEER_TT_ON_R,                                             /* 18 ON_R                                            */
    (U1)ALERT_REQ_C_STEER_TT_ON_R,                                             /* 19 ON_R                                            */
    (U1)ALERT_REQ_C_STEER_TT_ON_R,                                             /* 20 ON_R                                            */
    (U1)ALERT_REQ_C_STEER_TT_ON_R,                                             /* 21 ON_R                                            */
    (U1)ALERT_REQ_C_STEER_TT_ON_R,                                             /* 22 ON_R                                            */
    (U1)ALERT_REQ_C_STEER_TT_ON_R,                                             /* 23 ON_R                                            */
    (U1)ALERT_REQ_C_STEER_TT_ON_R,                                             /* 24 ON_R                                            */
    (U1)ALERT_REQ_C_STEER_TT_ON_R,                                             /* 25 ON_R                                            */
    (U1)ALERT_REQ_C_STEER_TT_ON_R,                                             /* 26 ON_R                                            */
    (U1)ALERT_REQ_C_STEER_TT_ON_R,                                             /* 27 ON_R                                            */
    (U1)ALERT_REQ_C_STEER_TT_ON_R,                                             /* 28 ON_R                                            */
    (U1)ALERT_REQ_C_STEER_TT_ON_R,                                             /* 29 ON_R                                            */
    (U1)ALERT_REQ_C_STEER_TT_ON_R,                                             /* 30 ON_R                                            */
    (U1)ALERT_REQ_C_STEER_TT_ON_R                                              /* 31 ON_R                                            */
};
static const U1  u1_sp_ALERT_C_STEER_BC_DST[ALERT_C_STEER_BC_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_C_STEER_BC_SINGLE,                                           /* 01 SINGLE                                          */
    (U1)ALERT_REQ_C_STEER_BC_CYCL,                                             /* 02 CYCL                                            */
    (U1)ALERT_REQ_C_STEER_BC_CYCL_UNDRVE,                                      /* 03 CYCL_UNDRVE                                     */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_C_STEER_BC_SINGLE,                                           /* 08 SINGLE                                          */
    (U1)ALERT_REQ_C_STEER_BC_SINGLE,                                           /* 09 SINGLE                                          */
    (U1)ALERT_REQ_C_STEER_BC_SINGLE,                                           /* 10 SINGLE                                          */
    (U1)ALERT_REQ_C_STEER_BC_SINGLE,                                           /* 11 SINGLE                                          */
    (U1)ALERT_REQ_C_STEER_BC_SINGLE,                                           /* 12 SINGLE                                          */
    (U1)ALERT_REQ_C_STEER_BC_SINGLE,                                           /* 13 SINGLE                                          */
    (U1)ALERT_REQ_C_STEER_BC_SINGLE,                                           /* 14 SINGLE                                          */
    (U1)ALERT_REQ_C_STEER_BC_SINGLE                                            /* 15 SINGLE                                          */
};
static const U4  u4_sp_ALERT_C_STEER_PD_CRIT[ALERT_C_STEER_PD_NUM_DST] = {
    (U4)0x00000000U,                                                           /* 00 UNKNOWN                                         */
    (U4)0x00000001U,                                                           /* 01 ASSIST_LMT                                      */
    (U4)0x00000002U,                                                           /* 02 ASSIST_STOP                                     */
    (U4)0x00000003U,                                                           /* 03 POWSTOP                                         */
    (U4)0x00000004U,                                                           /* 04 ASSIST_CONTI                                    */
    (U4)0x00000005U,                                                           /* 05 ENGSTOP                                         */
    (U4)0x00000006U,                                                           /* 06 HV_STOP                                         */
    (U4)0x00000086U,                                                           /* 07 EV_STOP                                         */
    (U4)0x00000106U,                                                           /* 08 FCV_STOP                                        */
    (U4)0x00000186U,                                                           /* 09 UNKNOWN                                         */
    (U4)0x00000007U,                                                           /* 10 POWLIMIT                                        */
    (U4)0x00000008U,                                                           /* 11 CAR_STOP                                        */
    (U4)0x00000009U,                                                           /* 12 CALL_DEALER                                     */
    (U4)0x0000000AU,                                                           /* 13 LMT_SPD                                         */
    (U4)0x0000000BU,                                                           /* 14 UNKNOWN                                         */
    (U4)0x0000000CU,                                                           /* 15 UNKNOWN                                         */
    (U4)0x0000000DU,                                                           /* 16 SPD_SNS_ERR                                     */
    (U4)0x0000000EU,                                                           /* 17 CANT_SFT                                        */
    (U4)0x0000000FU,                                                           /* 18 OVRHEAT                                         */
    (U4)0x00000010U,                                                           /* 19 SRT_UP_FAIL                                     */
    (U4)0x00000011U,                                                           /* 20 RMV_HAND                                        */
    (U4)0x00000012U,                                                           /* 21 COMM_ERR                                        */
    (U4)0x00000013U,                                                           /* 22 NONSYNC_MOD                                     */
    (U4)0x00000014U,                                                           /* 23 SELF_CALIB                                      */
    (U4)0x00000015U,                                                           /* 24 RDY_DRIVE                                       */
    (U4)0x00000016U,                                                           /* 25 UNKNOWN                                         */
    (U4)0x00000017U,                                                           /* 26 UNKNOWN                                         */
    (U4)0x00000018U,                                                           /* 27 UNKNOWN                                         */
    (U4)0x00000019U,                                                           /* 28 UNKNOWN                                         */
    (U4)0x0000001AU,                                                           /* 29 UNKNOWN                                         */
    (U4)0x0000001BU,                                                           /* 30 UNKNOWN                                         */
    (U4)0x0000001CU,                                                           /* 31 UNKNOWN                                         */
    (U4)0x0000001DU,                                                           /* 32 UNKNOWN                                         */
    (U4)0x0000001EU,                                                           /* 33 UNKNOWN                                         */
    (U4)0x0000001FU,                                                           /* 34 UNKNOWN                                         */
    (U4)0x00000020U,                                                           /* 35 UNKNOWN                                         */
    (U4)0x00000040U                                                            /* 36 ASSIST_CONTI                                    */
};
static const U4  u4_sp_ALERT_C_STEER_PD_MASK[ALERT_C_STEER_PD_NUM_DST] = {
    (U4)0x0000007FU,                                                           /* 00 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 01 ASSIST_LMT                                      */
    (U4)0x0000007FU,                                                           /* 02 ASSIST_STOP                                     */
    (U4)0x0000007FU,                                                           /* 03 POWSTOP                                         */
    (U4)0x0000007FU,                                                           /* 04 ASSIST_CONTI                                    */
    (U4)0x0000007FU,                                                           /* 05 ENGSTOP                                         */
    (U4)0x000001FFU,                                                           /* 06 HV_STOP                                         */
    (U4)0x000001FFU,                                                           /* 07 EV_STOP                                         */
    (U4)0x000001FFU,                                                           /* 08 FCV_STOP                                        */
    (U4)0x000001FFU,                                                           /* 09 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 10 POWLIMIT                                        */
    (U4)0x0000007FU,                                                           /* 11 CAR_STOP                                        */
    (U4)0x0000007FU,                                                           /* 12 CALL_DEALER                                     */
    (U4)0x0000007FU,                                                           /* 13 LMT_SPD                                         */
    (U4)0x0000007FU,                                                           /* 14 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 15 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 16 SPD_SNS_ERR                                     */
    (U4)0x0000007FU,                                                           /* 17 CANT_SFT                                        */
    (U4)0x0000007FU,                                                           /* 18 OVRHEAT                                         */
    (U4)0x0000007FU,                                                           /* 19 SRT_UP_FAIL                                     */
    (U4)0x0000007FU,                                                           /* 20 RMV_HAND                                        */
    (U4)0x0000007FU,                                                           /* 21 COMM_ERR                                        */
    (U4)0x0000007FU,                                                           /* 22 NONSYNC_MOD                                     */
    (U4)0x0000007FU,                                                           /* 23 SELF_CALIB                                      */
    (U4)0x0000007FU,                                                           /* 24 RDY_DRIVE                                       */
    (U4)0x0000007FU,                                                           /* 25 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 26 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 27 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 28 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 29 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 30 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 31 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 32 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 33 UNKNOWN                                         */
    (U4)0x0000007FU,                                                           /* 34 UNKNOWN                                         */
    (U4)0x00000060U,                                                           /* 35 UNKNOWN                                         */
    (U4)0x00000040U                                                            /* 36 ASSIST_CONTI                                    */
};
static const U1  u1_sp_ALERT_C_STEER_PD_DST[ALERT_C_STEER_PD_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_C_STEER_PD_ASSIST_LMT,                                       /* 01 ASSIST_LMT                                      */
    (U1)ALERT_REQ_C_STEER_PD_ASSIST_STOP,                                      /* 02 ASSIST_STOP                                     */
    (U1)ALERT_REQ_C_STEER_PD_POWSTOP,                                          /* 03 POWSTOP                                         */
    (U1)ALERT_REQ_C_STEER_PD_ASSIST_CNTI,                                      /* 04 ASSIST_CNTI                                     */
    (U1)ALERT_REQ_C_STEER_PD_ENGSTOP,                                          /* 05 ENGSTOP                                         */
    (U1)ALERT_REQ_C_STEER_PD_HV_STOP,                                          /* 06 HV_STOP                                         */
    (U1)ALERT_REQ_C_STEER_PD_EV_STOP,                                          /* 07 EV_STOP                                         */
    (U1)ALERT_REQ_C_STEER_PD_FCV_STOP,                                         /* 08 FCV_STOP                                        */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 09 UNKNOWN                                         */
    (U1)ALERT_REQ_C_STEER_PD_POWLIMIT,                                         /* 10 POWLIMIT                                        */
    (U1)ALERT_REQ_C_STEER_PD_CAR_STOP,                                         /* 11 CAR_STOP                                        */
    (U1)ALERT_REQ_C_STEER_PD_CALL_DEALER,                                      /* 12 CALL_DEALER                                     */
    (U1)ALERT_REQ_C_STEER_PD_LMT_SPD,                                          /* 13 LMT_SPD                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 14 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 15 UNKNOWN                                         */
    (U1)ALERT_REQ_C_STEER_PD_SPD_SNS_ERR,                                      /* 16 SPD_SNS_ERR                                     */
    (U1)ALERT_REQ_C_STEER_PD_CANT_SFT,                                         /* 17 CANT_SFT                                        */
    (U1)ALERT_REQ_C_STEER_PD_OVRHEAT,                                          /* 18 OVRHEAT                                         */
    (U1)ALERT_REQ_C_STEER_PD_SRT_UP_FAIL,                                      /* 19 SRT_UP_FAIL                                     */
    (U1)ALERT_REQ_C_STEER_PD_RMV_HAND,                                         /* 20 RMV_HAND                                        */
    (U1)ALERT_REQ_C_STEER_PD_COMM_ERR,                                         /* 21 COMM_ERR                                        */
    (U1)ALERT_REQ_C_STEER_PD_NONSYNC_MOD,                                      /* 22 NONSYNC_MOD                                     */
    (U1)ALERT_REQ_C_STEER_PD_SELF_CALIB,                                       /* 23 SELF_CALIB                                      */
    (U1)ALERT_REQ_C_STEER_PD_RDY_DRIVE,                                        /* 24 RDY_DRIVE                                       */
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
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 35 UNKNOWN                                         */
    (U1)ALERT_REQ_C_STEER_PD_ASSIST_CNTI                                       /* 36 ASSIST_CNTI                                     */
};
static const U1  u1_sp_ALERT_C_STEER_RWRN_DST[ALERT_C_STEER_RWRN_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_C_STEER_RWRN_EPSWREQ,                                        /* 01 EPSWREQ                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_C_STEER_RWRN_EPSWREQ,                                        /* 04 EPSWREQ                                         */
    (U1)ALERT_REQ_C_STEER_RWRN_EPSWREQ,                                        /* 05 EPSWREQ                                         */
    (U1)ALERT_REQ_C_STEER_RWRN_EPSWREQ,                                        /* 06 EPSWREQ                                         */
    (U1)ALERT_REQ_C_STEER_RWRN_EPSWREQ                                         /* 07 EPSWREQ                                         */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_C_STEER_MTRX[4] = {
    {
        &u4_s_AlertC_steerTtSrcchk,                                            /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_C_STEER_TT_DST[0],                                        /* u1p_DST                                            */
        (U2)ALERT_C_STEER_TT_NUM_DST,                                          /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertC_steerBcSrcchk,                                            /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_C_STEER_BC_DST[0],                                        /* u1p_DST                                            */
        (U2)ALERT_C_STEER_BC_NUM_DST,                                          /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertC_steerPdSrcchk,                                            /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        &u4_sp_ALERT_C_STEER_PD_MASK[0],                                       /* u4p_MASK                                           */
        &u4_sp_ALERT_C_STEER_PD_CRIT[0],                                       /* u4p_CRIT                                           */

        &u1_sp_ALERT_C_STEER_PD_DST[0],                                        /* u1p_DST                                            */
        (U2)ALERT_C_STEER_PD_NUM_DST,                                          /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertC_steerRwrnSrcchk,                                          /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertC_steerRwrnRwTx,                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_C_STEER_RWRN_DST[0],                                      /* u1p_DST                                            */
        (U2)ALERT_C_STEER_RWRN_NUM_DST,                                        /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_AlertC_steerInit(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AlertC_steerInit(void)
{
#if defined(OXCAN_PDU_RX_CAN_EPS1S90_RXCH0) && defined(ComConf_ComSignal_EPS_MINF)
    u1_s_alert_c_steerpd_msgsts   = (U1)COM_NO_RX;
#endif /* defined(OXCAN_PDU_RX_CAN_EPS1S90_RXCH0) && defined(ComConf_ComSignal_EPS_MINF) */
#if defined(OXCAN_PDU_RX_CAN_EPS1S90_RXCH0) && defined(ComConf_ComSignal_EPS_REMT)
    u1_s_alert_c_steerrw_msgsts   = (U1)COM_NO_RX;
#endif /* defined(OXCAN_PDU_RX_CAN_EPS1S90_RXCH0) && defined(ComConf_ComSignal_EPS_REMT) */
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertC_steerTtSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertC_steerTtSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if defined(OXCAN_PDU_RX_CAN_EPS1S90_RXCH0) && defined(ComConf_ComSignal_EPS_WLMP)
    static const U2 u2_s_ALERT_C_STEERTT_TO_THRESH = ((U2)1000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_C_STEERTT_LSB_COMRX = (U1)3U;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;
    U4              u4_t_src_chk;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_EPS1S90_RXCH0,
                                     (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                     u2_s_ALERT_C_STEERTT_TO_THRESH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_EPS_WLMP, &u1_t_sgnl);
    
    u4_t_src_chk  = (U4)u1_t_sgnl;
    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_C_STEERTT_LSB_COMRX);

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* defined(OXCAN_PDU_RX_CAN_EPS1S90_RXCH0) && defined(ComConf_ComSignal_EPS_WLMP) */
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertC_steerBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertC_steerBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if defined(OXCAN_PDU_RX_CAN_EPS1S90_RXCH0) && defined(ComConf_ComSignal_EPS_BZER)
    static const U2 u2_s_ALERT_C_STEERBC_TO_THRESH = ((U2)1000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_C_STEERBC_LSB_COMRX = (U1)2U;

    U1              u1_t_sgnl;
    U1              u1_t_msgsts;
    U4              u4_t_src_chk;

    u1_t_msgsts = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_EPS1S90_RXCH0,
                                   (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                   u2_s_ALERT_C_STEERBC_TO_THRESH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_sgnl       = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_EPS_BZER, &u1_t_sgnl);

    u4_t_src_chk    = (U4)u1_t_sgnl;
    u4_t_src_chk   |= ((U4)u1_t_msgsts << u1_s_ALERT_C_STEERBC_LSB_COMRX);

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* defined(OXCAN_PDU_RX_CAN_EPS1S90_RXCH0) && defined(ComConf_ComSignal_EPS_BZER) */
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertC_steerPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertC_steerPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if defined(OXCAN_PDU_RX_CAN_EPS1S90_RXCH0) && defined(ComConf_ComSignal_EPS_MINF)
    static const U2 u2_s_ALERT_C_STEERPD_TO_THRESH     = ((U2)1000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_C_STEERPD_LSB_COMRX     = (U1)5U;
    static const U1 u1_s_ALERT_C_STEERPD_LSB_SIG_PTSYS = (U1)7U;
    static const U1 u1_s_ALERT_C_STEER_PTSYS_HV        = (U1)0U;
    static const U1 u1_s_ALERT_C_STEER_PTSYS_EV        = (U1)1U;
    static const U1 u1_s_ALERT_C_STEER_PTSYS_FCV       = (U1)2U;
    static const U1 u1_s_ALERT_C_STEER_PTSYS_UKN       = (U1)3U;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;
    U1              u1_t_ptsys;
    U4              u4_t_src_chk;

	u1_t_msgsts = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_EPS1S90_RXCH0,
                                   (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                   u2_s_ALERT_C_STEERPD_TO_THRESH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_s_alert_c_steerpd_msgsts = u1_t_msgsts;

    u1_t_sgnl       = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_EPS_MINF, &u1_t_sgnl);
    u4_t_src_chk    = (U4)u1_t_sgnl;
    u4_t_src_chk   |= ((U4)u1_s_alert_c_steerpd_msgsts << u1_s_ALERT_C_STEERPD_LSB_COMRX);

    u1_t_ptsys = u1_g_AlertPtsys();
    switch (u1_t_ptsys)
    {
        case (U1)ALERT_STEER_VD_PTSYS_UNDEF:
        case (U1)ALERT_STEER_VD_PTSYS_HV:
        case (U1)ALERT_STEER_VD_PTSYS_PHV:
        case (U1)ALERT_STEER_VD_PTSYS_HV_MOT:
            u1_t_ptsys = u1_s_ALERT_C_STEER_PTSYS_HV;
            break;

        case (U1)ALERT_STEER_VD_PTSYS_EV:
            u1_t_ptsys = u1_s_ALERT_C_STEER_PTSYS_EV;
            break;

        case (U1)ALERT_STEER_VD_PTSYS_FCV:
            u1_t_ptsys = u1_s_ALERT_C_STEER_PTSYS_FCV;
            break;

        default:
            u1_t_ptsys = (U1)u1_s_ALERT_C_STEER_PTSYS_UKN;
            break;
    }

    u4_t_src_chk   |= ((U4)u1_t_ptsys << u1_s_ALERT_C_STEERPD_LSB_SIG_PTSYS);

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* defined(OXCAN_PDU_RX_CAN_EPS1S90_RXCH0) && defined(ComConf_ComSignal_EPS_MINF) */
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertC_steerRwrnSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertC_steerRwrnSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if defined(OXCAN_PDU_RX_CAN_EPS1S90_RXCH0) && defined(ComConf_ComSignal_EPS_REMT)
    static const U2 u2_s_ALERT_C_STEERRW_TO_THRESH = ((U2)1000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_C_STEERRW_LSB_COMRX = (U1)1U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts__7v;
    U1              u1_t_msgsts_10v;
    U1              u1_t_sgnl;

    u1_t_msgsts__7v = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_EPS1S90_RXCH0,
                                       (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                       u2_s_ALERT_C_STEERRW_TO_THRESH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    if((u1_t_msgsts__7v & (U1)COM_TIMEOUT) == (U1)0U){
        u1_s_alert_c_steerrw_msgsts = u1_t_msgsts__7v;
    }
    else{
        u1_t_msgsts_10v = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_EPS1S90_RXCH0,
                                           (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_VDC,
                                           u2_s_ALERT_C_STEERRW_TO_THRESH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
        if((u1_t_msgsts_10v & (U1)COM_TIMEOUT) != (U1)0U){
            u1_s_alert_c_steerrw_msgsts = u1_t_msgsts_10v;
        }
    }

    u1_t_sgnl       = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_EPS_REMT, &u1_t_sgnl);
    u4_t_src_chk    = (U4)u1_t_sgnl;

    u4_t_src_chk |= ((U4)u1_s_alert_c_steerrw_msgsts << u1_s_ALERT_C_STEERRW_LSB_COMRX);

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* defined(OXCAN_PDU_RX_CAN_EPS1S90_RXCH0) && defined(ComConf_ComSignal_EPS_REMT) */
}

/*===================================================================================================================================*/
/*  static void    vd_s_AlertC_steerRwrnRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertC_steerRwrnRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)
{
    U1              u1_t_sgnl;

    if(((u1_a_VOM & (U1)ALERT_VOM_RWT_EN) != (U1)0U                            ) &&
       (u1_a_DST                          == (U1)ALERT_REQ_C_STEER_RWRN_EPSWREQ)){
        u1_t_sgnl = (U1)ALERT_RW_SGNL_ON;
    }
    else{
        u1_t_sgnl = (U1)ALERT_RW_SGNL_OFF;
    }
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_EPSW, &u1_t_sgnl);    /* COM Tx STUB delete */
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
/*  5.0.0    10/25/2023  DR       New.                                                                                               */
/*  5.1.0     4/ 1/2024  AA       Applied remote warning of EPSW                                                                     */
/*  5.2.0    04/18/2024  JMH      Updated PTSYS judgement from dedicated to ON/OFF generic                                           */
/*                                Removed Special processing                                                                         */
/*  5.3.0    10/11/2024  KO       Change for BEV System_Consideration_1.                                                             */
/*                                                                                                                                   */
/*  * DR   = Dyan Reyes, Denso Techno Philippines Inc                                                                                */
/*  * JMH  = James Michael Hilarion, Denso Techno Philippines Inc.                                                                   */
/*  * KO   = Kazuto Oishi,  Denso Techno                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
