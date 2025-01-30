/* 5.2.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert H_THEVM                                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_H_THEVM_C_MAJOR                    (5)
#define ALERT_H_THEVM_C_MINOR                    (2)
#define ALERT_H_THEVM_C_PATCH                    (0)

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
#if (ALERT_H_THEVM_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_H_THEVM.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_H_THEVM_TT_NUM_DST                 (64U)
#define ALERT_H_THEVM_PD_NUM_DST                 (64U)

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
static U4      u4_s_AlertH_thevmTtSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertH_thevmPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_H_THEVM_TT_DST[ALERT_H_THEVM_TT_NUM_DST] = {
    (U1)ALERT_REQ_H_THEVM_TT_OFF,                                              /* 00 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_TT_OFF,                                              /* 01 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_TT_OFF,                                              /* 02 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_TT_OFF,                                              /* 03 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_TT_OFF,                                              /* 04 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_TT_OFF,                                              /* 05 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_TT_OFF,                                              /* 06 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_TT_OFF,                                              /* 07 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_TT_OFF,                                              /* 08 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_TT_OFF,                                              /* 09 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_TT_OFF,                                              /* 10 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_TT_OFF,                                              /* 11 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_TT_OFF,                                              /* 12 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_TT_OFF,                                              /* 13 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_TT_OFF,                                              /* 14 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_TT_OFF,                                              /* 15 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_TT_OFF,                                              /* 16 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_TT_OFF,                                              /* 17 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_TT_OFF,                                              /* 18 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_TT_OFF,                                              /* 19 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_TT_OFF,                                              /* 20 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_TT_OFF,                                              /* 21 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_TT_OFF,                                              /* 22 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_TT_OFF,                                              /* 23 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_TT_OFF,                                              /* 24 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_TT_OFF,                                              /* 25 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_TT_OFF,                                              /* 26 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_TT_OFF,                                              /* 27 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_TT_OFF,                                              /* 28 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_TT_OFF,                                              /* 29 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_TT_OFF,                                              /* 30 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_TT_OFF,                                              /* 31 OFF                                             */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 32 UNKNOWN                                         */
    (U1)ALERT_REQ_H_THEVM_TT_EVM_ON,                                           /* 33 EVM_ON                                          */
    (U1)ALERT_REQ_H_THEVM_TT_EVM_FLS_OFF,                                      /* 34 EVM_FLS_OFF                                     */
    (U1)ALERT_REQ_H_THEVM_TT_EVM_FLS_ON,                                       /* 35 EVM_FLS_ON                                      */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 36 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 37 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 38 UNKNOWN                                         */
    (U1)ALERT_REQ_H_THEVM_TT_CHG_ON,                                           /* 39 CHG_ON                                          */
    (U1)ALERT_REQ_H_THEVM_TT_CHG_FLS_OFF,                                      /* 40 CHG_FLS_OFF                                     */
    (U1)ALERT_REQ_H_THEVM_TT_CHG_FLASH,                                        /* 41 CHG_FLASH                                       */
    (U1)ALERT_REQ_H_THEVM_TT_EVA_ON,                                           /* 42 EVA_ON                                          */
    (U1)ALERT_REQ_H_THEVM_TT_EVA_FLS_OFF,                                      /* 43 EVA_FLS_OFF                                     */
    (U1)ALERT_REQ_H_THEVM_TT_EVA_FLS_ON,                                       /* 44 EVA_FLS_ON                                      */
    (U1)ALERT_REQ_H_THEVM_TT_HVM_ON,                                           /* 45 HVM_ON                                          */
    (U1)ALERT_REQ_H_THEVM_TT_HVM_FLS_OFF,                                      /* 46 HVM_FLS_OFF                                     */
    (U1)ALERT_REQ_H_THEVM_TT_HVM_FLS_ON,                                       /* 47 HVM_FLS_ON                                      */
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
static const U1  u1_sp_ALERT_H_THEVM_PD_DST[ALERT_H_THEVM_PD_NUM_DST] = {
    (U1)ALERT_REQ_H_THEVM_PD_OFF,                                              /* 00 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_PD_OFF,                                              /* 01 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_PD_OFF,                                              /* 02 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_PD_OFF,                                              /* 03 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_PD_OFF,                                              /* 04 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_PD_OFF,                                              /* 05 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_PD_OFF,                                              /* 06 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_PD_OFF,                                              /* 07 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_PD_OFF,                                              /* 08 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_PD_OFF,                                              /* 09 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_PD_OFF,                                              /* 10 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_PD_OFF,                                              /* 11 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_PD_OFF,                                              /* 12 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_PD_OFF,                                              /* 13 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_PD_OFF,                                              /* 14 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_PD_OFF,                                              /* 15 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_PD_OFF,                                              /* 16 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_PD_OFF,                                              /* 17 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_PD_OFF,                                              /* 18 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_PD_OFF,                                              /* 19 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_PD_OFF,                                              /* 20 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_PD_OFF,                                              /* 21 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_PD_OFF,                                              /* 22 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_PD_OFF,                                              /* 23 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_PD_OFF,                                              /* 24 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_PD_OFF,                                              /* 25 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_PD_OFF,                                              /* 26 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_PD_OFF,                                              /* 27 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_PD_OFF,                                              /* 28 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_PD_OFF,                                              /* 29 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_PD_OFF,                                              /* 30 OFF                                             */
    (U1)ALERT_REQ_H_THEVM_PD_OFF,                                              /* 31 OFF                                             */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 32 UNKNOWN                                         */
    (U1)ALERT_REQ_H_THEVM_PD_EVM_LOW,                                          /* 33 EVM_LOW                                         */
    (U1)ALERT_REQ_H_THEVM_PD_EVA_LOW,                                          /* 34 EVA_LOW                                         */
    (U1)ALERT_REQ_H_THEVM_PD_CHG_DEACT,                                        /* 35 CHG_DEACT                                       */
    (U1)ALERT_REQ_H_THEVM_PD_CHG_NOT,                                          /* 36 CHG_NOT                                         */
    (U1)ALERT_REQ_H_THEVM_PD_CHG_FULL,                                         /* 37 CHG_FULL                                        */
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
const ST_ALERT_MTRX st_gp_ALERT_H_THEVM_MTRX[2] = {
    {
        &u4_s_AlertH_thevmTtSrcchk,                                            /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_H_THEVM_TT_DST[0],                                        /* u1p_DST                                            */
        (U2)ALERT_H_THEVM_TT_NUM_DST,                                          /* u2_num_srch                                        */
        (U1)ALERT_VOM_BAT_WT                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertH_thevmPdSrcchk,                                            /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_H_THEVM_PD_DST[0],                                        /* u1p_DST                                            */
        (U2)ALERT_H_THEVM_PD_NUM_DST,                                          /* u2_num_srch                                        */
        (U1)ALERT_VOM_BAT_WT                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertH_thevmTtSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertH_thevmTtSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U1 u1_s_ALERT_H_THEVM_TT_LSB_MSGSTS = (U1)4U;
    static const U4 u4_s_ALERT_H_THEVM_TT_BIT_IGN_ON = (U4)0x00000020U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_EHV1S31_RXCH0,
                                     (U2)OXCAN_RX_SYS_NRX_IGR,
                                     (U2)U2_MAX) & (U1)COM_NO_RX;

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_PHVMDIND, &u1_t_sgnl);

    u4_t_src_chk  = (U4)u1_t_sgnl;
    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_H_THEVM_TT_LSB_MSGSTS);

    if((u1_a_VOM & (U1)ALERT_VOM_IGN_ON) != (U1)0U){
        u4_t_src_chk |= u4_s_ALERT_H_THEVM_TT_BIT_IGN_ON;
    }

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertH_thevmPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertH_thevmPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U1 u1_s_ALERT_H_THEVM_PD_LSB_MSGSTS = (U1)4U;
    static const U4 u4_s_ALERT_H_THEVM_PD_BIT_IGN_ON = (U4)0x00000020U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_EHV1S31_RXCH0,
                                     (U2)OXCAN_RX_SYS_NRX_IGR,
                                     (U2)U2_MAX) & (U1)COM_NO_RX;

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_PHVMDMSG, &u1_t_sgnl);

    u4_t_src_chk  = (U4)u1_t_sgnl;
    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_H_THEVM_PD_LSB_MSGSTS);

    if((u1_a_VOM & (U1)ALERT_VOM_IGN_ON) != (U1)0U){
        u4_t_src_chk |= u4_s_ALERT_H_THEVM_PD_BIT_IGN_ON;
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
/*  5.0.0     3/11/2020  ZS       New.                                                                                               */
/*  5.0.1     9/ 2/2020  MO       Renamed file.                                                                                      */
/*  5.1.0    12/ 7/2020  MO       Update for 800B 1A(Version update).                                                                */
/*  5.1.1     7/15/2022  RN       Update for 840B#2 1A(Version update).                                                              */
/*  5.2.0     1/19/2024  SN       Update for 19Pfv3 CV Internal Merge2(Version update).                                              */
/*                                                                                                                                   */
/*  * ZS   = Zenjiro Shamoto, NTTD MSE                                                                                               */
/*  * MO   = Masaya Ozawa, NTTD MSE                                                                                                  */
/*  * MO   = Masayuki Oofuji, NTTD MSE                                                                                               */
/*  * RN   = Ryuga Nakanishi, NTTD MSE                                                                                               */
/*  * SN   = Shimon Nambu, Denso Techno                                                                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/
