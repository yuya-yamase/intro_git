/* 5.5.2 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert H_ACCHOL                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_H_ACCHOL_C_MAJOR                   (5)
#define ALERT_H_ACCHOL_C_MINOR                   (5)
#define ALERT_H_ACCHOL_C_PATCH                   (2)

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
#if (ALERT_H_ACCHOL_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_H_ACCHOL.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_H_ACCHOL_NUM_DST                   (7U)

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
static U4      u4_s_AlertH_accholSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U4  u4_sp_ALERT_H_ACCHOL_CRIT[ALERT_H_ACCHOL_NUM_DST] = {
    (U4)0x10000080U,                                                           /* 00 HVSYSOVHT                                       */
    (U4)0x1000008CU,                                                           /* 01 HVSYSOVHT                                       */
    (U4)0x10000090U,                                                           /* 02 HVSYSOVHT                                       */
    (U4)0x10000094U,                                                           /* 03 EVSYSOVHT                                       */
    (U4)0x1000009CU,                                                           /* 04 FCVSYSOVHT                                      */
    (U4)0x100000FCU,                                                           /* 05 HVSYSOVHT                                       */
    (U4)0x10000080U                                                            /* 06 MALFUNC                                         */
};
static const U4  u4_sp_ALERT_H_ACCHOL_MASK[ALERT_H_ACCHOL_NUM_DST] = {
    (U4)0x100000FFU,                                                           /* 00 HVSYSOVHT                                       */
    (U4)0x100000FFU,                                                           /* 01 HVSYSOVHT                                       */
    (U4)0x100000F7U,                                                           /* 02 HVSYSOVHT                                       */
    (U4)0x100000FFU,                                                           /* 03 EVSYSOVHT                                       */
    (U4)0x100000FFU,                                                           /* 04 FCVSYSOVHT                                      */
    (U4)0x100000FFU,                                                           /* 05 HVSYSOVHT                                       */
    (U4)0x10000083U                                                            /* 06 MALFUNC                                         */
};
static const U1  u1_sp_ALERT_H_ACCHOL_DST[ALERT_H_ACCHOL_NUM_DST] = {
    (U1)ALERT_REQ_H_ACCHOL_HVSYSOVHT,                                          /* 00 HVSYSOVHT                                       */
    (U1)ALERT_REQ_H_ACCHOL_HVSYSOVHT,                                          /* 01 HVSYSOVHT                                       */
    (U1)ALERT_REQ_H_ACCHOL_HVSYSOVHT,                                          /* 02 HVSYSOVHT                                       */
    (U1)ALERT_REQ_H_ACCHOL_EVSYSOVHT,                                          /* 03 EVSYSOVHT                                       */
    (U1)ALERT_REQ_H_ACCHOL_FCVSYSOVHT,                                         /* 04 FCVSYSOVHT                                      */
    (U1)ALERT_REQ_H_ACCHOL_HVSYSOVHT,                                          /* 05 HVSYSOVHT                                       */
    (U1)ALERT_REQ_H_ACCHOL_MALFUNC                                             /* 06 MALFUNC                                         */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_H_ACCHOL_MTRX[1] = {
    {
        &u4_s_AlertH_accholSrcchk,                                             /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        &u4_sp_ALERT_H_ACCHOL_MASK[0],                                         /* u4p_MASK                                           */
        &u4_sp_ALERT_H_ACCHOL_CRIT[0],                                         /* u4p_CRIT                                           */

        &u1_sp_ALERT_H_ACCHOL_DST[0],                                          /* u1p_DST                                            */
        (U2)ALERT_H_ACCHOL_NUM_DST,                                            /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertH_accholSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertH_accholSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U1 u1_s_ALERT_H_ACCHOL_LSB_ACCHCAU = (U1)7U;
#if defined(OXCAN_RXD_PDU_CAN_EHV1S94_CH0)
    static const U2 u2_s_ALERT_H_ACCHOL_TO_EHV1S94  = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
#endif /* defined(OXCAN_RXD_PDU_CAN_EHV1S94_CH0) */ /* 840B_CAN */
    static const U1 u1_s_ALERT_H_ACCHOL_LSB_PTSYS   = (U1)2U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

#if defined(OXCAN_RXD_PDU_CAN_EHV1S94_CH0)
    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_EHV1S94_CH0,
                                          (U4)OXCAN_SYS_IGP,
                                          u2_s_ALERT_H_ACCHOL_TO_EHV1S94) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
#else
    u1_t_msgsts   = (U1)COM_NO_RX;
#endif /* defined(OXCAN_RXD_PDU_CAN_EHV1S94_CH0) */ /* 840B_CAN */
    u4_t_src_chk  = (U4)u1_t_msgsts;

    u1_t_sgnl     = u1_g_AlertPtsys();
    if(u1_t_sgnl > (U1)ALERT_PTSYS_1F_NRX){
        u1_t_sgnl = (U1)ALERT_PTSYS_0F_UNK;
    }

    u4_t_src_chk |= ((U4)u1_t_sgnl << u1_s_ALERT_H_ACCHOL_LSB_PTSYS);

    u1_t_sgnl     = (U1)0U;
#ifdef ComConf_ComSignal_ACCHCAU
    (void)Com_ReceiveSignal(ComConf_ComSignal_ACCHCAU, &u1_t_sgnl);
#endif /* ComConf_ComSignal_ACCHCAU */ /* 840B_CAN */
    u4_t_src_chk |= ((U4)u1_t_sgnl << u1_s_ALERT_H_ACCHOL_LSB_ACCHCAU);

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
/*  5.0.0     2/21/2019  SN       New.                                                                                               */
/*  5.0.1     4/ 2/2019  NS       Update Alert Version 5.1.0(Update VOM bit assign).                                                 */
/*  5.0.2    10/08/2019  DS       Add compile switch.                                                                                */
/*  5.1.0     2/ 7/2020  ZS       Modify not to get the communication status of ENG1F03.                                             */
/*  5.2.0     4/ 1/2020  ZS       Change module name to 800B spec.                                                                   */
/*  5.2.1     9/ 4/2020  MO       Renamed file.                                                                                      */
/*  5.3.0     9/10/2020  MY       Fix PTSYS initial value when no receive.                                                           */
/*  5.4.0     9/23/2020  MY       Fix receive logic when PTSYS is out of range.                                                      */
/*  5.5.0    12/ 8/2020  TN       Update for 800B 1A(Version update).                                                                */
/*  5.5.1     3/26/2021  TN       Update for 840B CV(Version update).                                                                */
/*  5.5.2     5/14/2021  TN       Fix 800B Bug.                                                                                      */
/*                                                                                                                                   */
/*  * SN   = Shinichiro Naito, NTTD MSE                                                                                              */
/*  * NS   = Naoki Sano, NTTD MSE                                                                                                    */
/*  * DS   = Daisuke Suzuki, NTTD MSE                                                                                                */
/*  * ZS   = Zenjiro Shamoto, NTTD MSE                                                                                               */
/*  * MO   = Masaya Ozawa, NTTD MSE                                                                                                  */
/*  * MY   = Masaki Yoshizawa, NTTD MSE                                                                                              */
/*  * TN   = Toshiaki Nagashima, NTTD MSE                                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/
