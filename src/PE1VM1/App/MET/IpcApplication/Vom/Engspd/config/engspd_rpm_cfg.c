/* 2.0.2 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Toyota IPC/MET :Engine Rotation Speed                                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ENGSPD_RPM_CFG_C_MAJOR                   (2)
#define ENGSPD_RPM_CFG_C_MINOR                   (0)
#define ENGSPD_RPM_CFG_C_PATCH                   (2)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "engspd_rpm_cfg_private.h"

#include "oxcan.h"
#if 0   /* BEV BSW provisionally */
#else
#include "oxcan_channel_STUB.h"
#endif

#include "vardef.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((ENGSPD_RPM_CFG_C_MAJOR != ENGSPD_RPM_CFG_H_MAJOR) || \
     (ENGSPD_RPM_CFG_C_MINOR != ENGSPD_RPM_CFG_H_MINOR) || \
     (ENGSPD_RPM_CFG_C_PATCH != ENGSPD_RPM_CFG_H_PATCH))
#error "engspd_rpm_cfg.c and engspd_rpm_cfg_private.h : source and header files are inconsistent!"
#endif

#if ((ENGSPD_RPM_CFG_C_MAJOR != ENGSPD_RPM_H_MAJOR) || \
     (ENGSPD_RPM_CFG_C_MINOR != ENGSPD_RPM_H_MINOR) || \
     (ENGSPD_RPM_CFG_C_PATCH != ENGSPD_RPM_H_PATCH))
#error "engspd_rpm_cfg.c and engspd_rpm.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define u2_ENGSPD_RPM_RXTO_THRSH                 u2_OXCAN_RXTO_THRSH(120U)  /* RX Timeout Threshold 120ms */

#define ENGSPD_SIG_TYPE_NUM                      (3U)
#define ENGSPD_SIG_TYPE_HV_NE                    (0U)
#define ENGSPD_SIG_TYPE_NE_MET                   (1U)
#define ENGSPD_SIG_TYPE_NE1                      (2U)

#define ENGSPD_NE_MET_INVALID                    (0x8000U)

#define ENGSPD_NE_RXCFCNT                        (50U)               /* 12800/256                                            */
#define ENGSPD_NE_ROUND                          (32U)               /* 64 * 0.5 (For rounding off when divided by 64)       */
#define ENGSPD_NE_LSR_CFCNT                      (6U)                /* /64  (For right shft operation, instead of division) */

#define ENGSPD_NOT_ACCEPT                        (0U)
#define ENGSPD_ACCEPT                            (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((ENGSPD_STSBIT_UNKNOWN != COM_NO_RX  ) || \
     (ENGSPD_STSBIT_INVALID != COM_TIMEOUT))
#error "ENGSPD_STSBIT_UNKNOWN shall be equal to COM_NO_RX and ENGSPD_STSBIT_INVALID shall be equal to COM_TIMEOUT."
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1      u1_s_EngspdRpmCfgSigType(void);
static U1      u1_s_EngspdRpmCanNeMetComRx(U2 * u2p_a_ne, U1 * u1p_a_stsbit);
static U1      u1_s_EngspdRpmCanHvNeComRx(U2 * u2p_a_ne, U1 * u1p_a_stsbit);
static U1      u1_s_EngspdRpmCanNe1ComRx(U2 * u2p_a_ne, U1 * u1p_a_stsbit);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U1 u1_g_ENGSPD_CALIB_N1_DEF       = (U1)CALIB_MCUID0639_DEF;
const U1 u1_g_ENGSPD_CALIB_N2_DEF       = (U1)CALIB_MCUID0640_DEF;
const U1 u1_g_ENGSPD_CALIB_N1_MIN       = (U1)CALIB_MCUID0639_MIN;
const U1 u1_g_ENGSPD_CALIB_N2_MIN       = (U1)CALIB_MCUID0640_MIN;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  U1      u1_g_EngspdRpmCfgRpmInst(U2 * u2p_a_ne)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_EngspdRpmCfgRpmInst(U2 * u2p_a_ne)
{
    static U1 (* const fp_sp_u1_ENGSPD_CANCOMRX[ENGSPD_SIG_TYPE_NUM])(U2 * u2p_a_ne, U1 * u1p_a_stsbit) = { /* Functions by SIG_TYPE */
        &u1_s_EngspdRpmCanHvNeComRx,      /*  ENGSPD_SIG_TYPE_HV_NE   */
        &u1_s_EngspdRpmCanNeMetComRx,     /*  ENGSPD_SIG_TYPE_NE_MET  */
        &u1_s_EngspdRpmCanNe1ComRx        /*  ENGSPD_SIG_TYPE_NE1     */
    };

    U1 u1_t_sigtype;
    U1 u1_t_stsbit;
    U1 u1_t_rxresult;

    (*u2p_a_ne)   = (U2)0U;
    u1_t_stsbit   = (U1)ENGSPD_STSBIT_UNKNOWN;

    u1_t_sigtype  = u1_s_EngspdRpmCfgSigType();

    u1_t_rxresult = (fp_sp_u1_ENGSPD_CANCOMRX[u1_t_sigtype])(u2p_a_ne, &u1_t_stsbit);

    if(u1_t_rxresult != (U1)ENGSPD_ACCEPT){
        (void)(fp_sp_u1_ENGSPD_CANCOMRX[ENGSPD_SIG_TYPE_NE1])(u2p_a_ne, &u1_t_stsbit);
    }

    return(u1_t_stsbit);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_EngspdRpmCfgSigType(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_EngspdRpmCfgSigType(void)
{
    U1 u1_t_ne_met_available;
    U1 u1_t_hv_ne_available;
    U1 u1_t_sigtype;

    u1_t_sigtype = (U1)ENGSPD_SIG_TYPE_NE1;

    u1_t_ne_met_available = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_NE_MET);

    if(u1_t_ne_met_available == (U1)TRUE){
        u1_t_sigtype = (U1)ENGSPD_SIG_TYPE_NE_MET;
    }
    else{
        u1_t_hv_ne_available  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_HV_NE);
        if(u1_t_hv_ne_available == (U1)TRUE){
            u1_t_sigtype = (U1)ENGSPD_SIG_TYPE_HV_NE;
        }
    }

    return(u1_t_sigtype);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_EngspdRpmCanNeMetComRx(U2 * u2p_a_ne, U1 * u1p_a_stsbit)                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_EngspdRpmCanNeMetComRx(U2 * u2p_a_ne, U1 * u1p_a_stsbit)
{
#if (defined(OXCAN_PDU_RX_CAN_ENG1S98) && defined(ComConf_ComSignal_NE_MET))
    S2 s2_t_ne;
    U1 u1_t_rxresult;
    U4 u4_t_inst;

    u1_t_rxresult = (U1)ENGSPD_NOT_ACCEPT;
    s2_t_ne       = (S2)0;
    u4_t_inst     = (U4)0U;

    (*u1p_a_stsbit)  = u1_g_oXCANRxdStat((U2)OXCAN_PDU_RX_CAN_ENG1S98, ((U4)OXCAN_SYS_IGR), u2_ENGSPD_RPM_RXTO_THRSH);
    (*u1p_a_stsbit) &= ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    if((*u1p_a_stsbit) == (U1)0U){
#if 0   /* BEV BSW provisionally */
        (void)Com_ReceiveSignal(ComConf_ComSignal_NE_MET, &s2_t_ne);
#endif

        if((U2)s2_t_ne != (U2)ENGSPD_NE_MET_INVALID){ /* NE_MET signal validity check */

            if(s2_t_ne > (S2)0){
                u4_t_inst = (U4)((S4)s2_t_ne);
            }
            u4_t_inst = u4_t_inst * (U4)ENGSPD_NE_RXCFCNT;
            u4_t_inst = (u4_t_inst + (U4)ENGSPD_NE_ROUND) >> (U4)ENGSPD_NE_LSR_CFCNT;  /* LSB:(12800/256/64)rpm -> 1rpm */

            u1_t_rxresult = (U1)ENGSPD_ACCEPT;
        }
    }
    else if(((*u1p_a_stsbit) & (U1)COM_TIMEOUT) == (U1)COM_TIMEOUT) {
        /* u4_t_inst = (U4)0U; */
        /* u1_t_rxresult = (U1)ENGSPD_NOT_ACCEPT; */
    }
    else{ /* COM_NO_RX case */
        /* u4_t_inst = (U4)0U; */
        u1_t_rxresult = (U1)ENGSPD_ACCEPT;
    }

    (*u2p_a_ne) = (U2)u4_t_inst;

    return(u1_t_rxresult);
#else
    (*u2p_a_ne)     = (U2)0U;
    (*u1p_a_stsbit) = (U1)ENGSPD_STSBIT_UNKNOWN;

    return((U1)ENGSPD_NOT_ACCEPT);
#endif
}
/*===================================================================================================================================*/
/*  static U1      u1_s_EngspdRpmCanHvNeComRx(U2 * u2p_a_ne, U1 * u1p_a_stsbit)                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_EngspdRpmCanHvNeComRx(U2 * u2p_a_ne, U1 * u1p_a_stsbit)
{
#if (defined(OXCAN_RXD_PDU_CAN_EHV1F04_CH0) && defined(ComConf_ComSignal_HV_NE))
    S2 s2_t_ne;
    U1 u1_t_rxresult;
    U4 u4_t_inst;

    u1_t_rxresult = (U1)ENGSPD_NOT_ACCEPT;
    s2_t_ne       = (S2)0;
    u4_t_inst     = (U4)0U;

    (*u1p_a_stsbit)  = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_EHV1F04_CH0, ((U4)OXCAN_SYS_IGR), u2_ENGSPD_RPM_RXTO_THRSH);
    (*u1p_a_stsbit) &= ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    if((*u1p_a_stsbit) == (U1)0U){
        (void)Com_ReceiveSignal(ComConf_ComSignal_HV_NE, &s2_t_ne);

        if(s2_t_ne > (S2)0){
            u4_t_inst = (U4)s2_t_ne;
        }
        u4_t_inst = u4_t_inst * (U4)ENGSPD_NE_RXCFCNT;
        u4_t_inst = (u4_t_inst + (U4)ENGSPD_NE_ROUND) >> (U4)ENGSPD_NE_LSR_CFCNT;  /* LSB:(12800/256/64)rpm -> 1rpm */

        u1_t_rxresult = (U1)ENGSPD_ACCEPT;
    }
    else if(((*u1p_a_stsbit) & (U1)COM_TIMEOUT) == (U1)COM_TIMEOUT) {
        /* u4_t_inst = (U4)0U; */
        /* u1_t_rxresult = (U1)ENGSPD_NOT_ACCEPT; */
    }
    else{ /* COM_NO_RX case */
        /* u4_t_inst = (U4)0U; */
        u1_t_rxresult = (U1)ENGSPD_ACCEPT;
    }

    (*u2p_a_ne) = (U2)u4_t_inst;

    return(u1_t_rxresult);
#else
    (*u2p_a_ne)     = (U2)0U;
    (*u1p_a_stsbit) = (U1)ENGSPD_STSBIT_UNKNOWN;

    return((U1)ENGSPD_NOT_ACCEPT);
#endif
}
/*===================================================================================================================================*/
/*  static U1      u1_s_EngspdRpmCanNe1ComRx(U2 * u2p_a_ne, U1 * u1p_a_stsbit)                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_EngspdRpmCanNe1ComRx(U2 * u2p_a_ne, U1 * u1p_a_stsbit)
{
    S2 s2_t_ne;
    U4 u4_t_inst;

    s2_t_ne       = (S2)0;
    u4_t_inst     = (U4)0U;

    (*u1p_a_stsbit)  = u1_g_oXCANRxdStat((U2)OXCAN_PDU_RX_CAN_ENG1G02, ((U4)OXCAN_SYS_IGR), u2_ENGSPD_RPM_RXTO_THRSH);
    (*u1p_a_stsbit) &= ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    if((*u1p_a_stsbit) == (U1)0U){
#if 0   /* BEV BSW provisionally */
        (void)Com_ReceiveSignal(ComConf_ComSignal_NE1, &s2_t_ne);
#endif

        if(s2_t_ne > (S2)0){
            u4_t_inst = (U4)s2_t_ne;
        }
        u4_t_inst = u4_t_inst * (U4)ENGSPD_NE_RXCFCNT;
        u4_t_inst = (u4_t_inst + (U4)ENGSPD_NE_ROUND) >> (U4)ENGSPD_NE_LSR_CFCNT;  /* LSB:(12800/256/64)rpm -> 1rpm */

    }
    else{ /* COM_NO_RX/COM_TIMEOUT case */
        /* u4_t_inst = (U4)0U; */
    }

    (*u2p_a_ne) = (U2)u4_t_inst;

    return((U1)ENGSPD_ACCEPT);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    06/07/2018  AK       New.                                                                                               */
/*  1.1.0     2/28/2019  TN       engspd_rpm. v1.0.0 -> v1.1.0.                                                                      */
/*  1.2.0     6/ 6/2019  TN       engspd_rpm. v1.1.0 -> v1.2.0.                                                                      */
/*  1.3.0     3/11/2020  HY       engspd_rpm. v1.2.0 -> v1.3.0.                                                                      */
/*  1.4.0     7/16/2020  HY       engspd_rpm. v1.3.0 -> v1.4.0.                                                                      */
/*  2.0.0    06/08/2021  TK       engspd_rpm. v1.4.0 -> v2.0.0.                                                                      */
/*  2.0.1    07/28/2021  TK       engspd_rpm. v2.0.0 -> v2.0.1.                                                                      */
/*  2.0.2    10/18/2021  TA(M)    engspd_rpm. v2.0.1 -> v2.0.2.                                                                      */
/*                                                                                                                                   */
/*  Revision    Date        Author   Change Description                                                                              */
/* ------------ ----------  -------  ------------------------------------------------------------------------------------------------*/
/* 22-24FGM-1   11/24/2021  MK       Apply 22-24FGM 1A configlation.                                                                 */
/* 19PFv3-1     12/13/2023  SH       Delete vd_g_EngspdRpmCfgWghtAveNum                                                              */
/*                                                                                                                                   */
/*  * AK   = Aiko Kishino, Denso                                                                                                     */
/*  * TN   = Takashi Nagai, DENSO                                                                                                    */
/*  * HY   = Hiroshige Yanase, DensoTechno                                                                                           */
/*  * TK   = Takanori Kuno, DensoTechno                                                                                              */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*  * MK   = Mitsuhiro Kato, DensoTechno                                                                                             */
/*  * SH   = Sae Hirose, Denso Techno                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/
