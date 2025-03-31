/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Toyota IPC/MET :Engine Rotation Speed                                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ENGSPD_DET_RPM_CFG_C_MAJOR                  (1)
#define ENGSPD_DET_RPM_CFG_C_MINOR                  (0)
#define ENGSPD_DET_RPM_CFG_C_PATCH                  (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "engspd_det_rpm_cfg_private.h"

#include "oxcan.h"
#if 0   /* BEV BSW provisionally */
#else
#include "Com_Cfg_STUB.h"
#include "oxcan_channel_STUB.h"
#endif

#include "vardef.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((ENGSPD_DET_RPM_CFG_C_MAJOR != ENGSPD_DET_RPM_CFG_H_MAJOR) || \
     (ENGSPD_DET_RPM_CFG_C_MINOR != ENGSPD_DET_RPM_CFG_H_MINOR) || \
     (ENGSPD_DET_RPM_CFG_C_PATCH != ENGSPD_DET_RPM_CFG_H_PATCH))
#error "engspd_det_rpm_cfg.c and engspd_det_rpm_cfg_private.h : source and header files are inconsistent!"
#endif

#if ((ENGSPD_DET_RPM_CFG_C_MAJOR != ENGSPD_DET_RPM_H_MAJOR) || \
     (ENGSPD_DET_RPM_CFG_C_MINOR != ENGSPD_DET_RPM_H_MINOR) || \
     (ENGSPD_DET_RPM_CFG_C_PATCH != ENGSPD_DET_RPM_H_PATCH))
#error "engspd_det_rpm_cfg.c and engspd_det_rpm.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define u2_ENGSPD_RPM_RXTO_THRSH                    u2_OXCAN_RXTO_THRSH(120U)  /* RX Timeout Threshold 120ms */
#define u2_ENGSPD_DET_RPM_RXTO_THRSH             u2_OXCAN_RXTO_THRSH(120U)  /* RX Timeout Threshold 120ms */

#define ENGSPD_DET_SIG_TYPE_NUM                  (3U)
#define ENGSPD_DET_SIG_TYPE_HV_NE                (0U)
#define ENGSPD_DET_SIG_TYPE_NE_MET               (1U)
#define ENGSPD_DET_SIG_TYPE_NE1                  (2U)

#define ENGSPD_NE_MET_INVALID                       (0x8000U)
#define ENGSPD_DET_NE_MET_INVALID                (0x8000U)

#define ENGSPD_DET_NE_RXCFCNT                    (50U)               /* 12800/256                                            */
#define ENGSPD_DET_NE_ROUND                      (32U)               /* 64 * 0.5 (For rounding off when divided by 64)       */
#define ENGSPD_DET_NE_LSR_CFCNT                  (6U)                /* /64  (For right shft operation, instead of division) */

#define ENGSPD_NOT_ACCEPT                        (0U)
#define ENGSPD_ACCEPT                            (1U)
#define ENGSPD_DET_NOT_ACCEPT                    (0U)
#define ENGSPD_DET_ACCEPT                        (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((ENGSPD_DET_STSBIT_UNKNOWN != COM_NO_RX  ) || \
     (ENGSPD_DET_STSBIT_INVALID != COM_TIMEOUT))
#error "ENGSPD_DET_STSBIT_UNKNOWN shall be equal to COM_NO_RX and ENGSPD_DET_STSBIT_INVALID shall be equal to COM_TIMEOUT."
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
static U1      u1_s_EngspdDetRpmCfgSigType(void);
static U1      u1_s_EngspdDetRpmCanNeMetComRx(U2 * u2p_a_ne, U1 * u1p_a_stsbit);
static U1      u1_s_EngspdDetRpmCanHvNeComRx(U2 * u2p_a_ne, U1 * u1p_a_stsbit);
static U1      u1_s_EngspdDetRpmCanNe1ComRx(U2 * u2p_a_ne, U1 * u1p_a_stsbit);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  U1      u1_g_EngspdDetRpmCfgRpmInst(U2 * u2p_a_ne)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_EngspdDetRpmCfgRpmInst(U2 * u2p_a_ne)
{
    static U1 (* const fp_sp_u1_ENGSPD_DET_CANCOMRX[ENGSPD_DET_SIG_TYPE_NUM])(U2 * u2p_a_ne, U1 * u1p_a_stsbit) = { /* Functions by SIG_TYPE */
        &u1_s_EngspdDetRpmCanHvNeComRx,   /*  ENGSPD_DET_SIG_TYPE_HV_NE   */
        &u1_s_EngspdDetRpmCanNeMetComRx,  /*  ENGSPD_DET_SIG_TYPE_NE_MET  */
        &u1_s_EngspdDetRpmCanNe1ComRx     /*  ENGSPD_DET_SIG_TYPE_NE1     */
    };

    U1 u1_t_sigtype;
    U1 u1_t_stsbit;
    U1 u1_t_rxresult;

    (*u2p_a_ne)   = (U2)0U;
    u1_t_stsbit   = (U1)ENGSPD_DET_STSBIT_UNKNOWN;

    u1_t_sigtype  = u1_s_EngspdDetRpmCfgSigType();

    u1_t_rxresult = (fp_sp_u1_ENGSPD_DET_CANCOMRX[u1_t_sigtype])(u2p_a_ne, &u1_t_stsbit);

    if(u1_t_rxresult != (U1)ENGSPD_DET_ACCEPT){
        (void)(fp_sp_u1_ENGSPD_DET_CANCOMRX[ENGSPD_DET_SIG_TYPE_NE1])(u2p_a_ne, &u1_t_stsbit);
    }

    return(u1_t_stsbit);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_EngspdDetRpmCfgSigType(void)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_EngspdDetRpmCfgSigType(void)
{
    U1 u1_t_ne_met_available;
    U1 u1_t_hv_ne_available;
    U1 u1_t_sigtype;

    u1_t_sigtype = (U1)ENGSPD_DET_SIG_TYPE_NE1;

    u1_t_ne_met_available = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_NE_MET);

    if(u1_t_ne_met_available == (U1)TRUE){
        u1_t_sigtype = (U1)ENGSPD_DET_SIG_TYPE_NE_MET;
    }
    else{
        u1_t_hv_ne_available  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_HV_NE);
        if(u1_t_hv_ne_available == (U1)TRUE){
            u1_t_sigtype = (U1)ENGSPD_DET_SIG_TYPE_HV_NE;
        }
    }

    return(u1_t_sigtype);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_EngspdDetRpmCanNeMetComRx(U2 * u2p_a_ne, U1 * u1p_a_stsbit)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_EngspdDetRpmCanNeMetComRx(U2 * u2p_a_ne, U1 * u1p_a_stsbit)
{
#if (defined(OXCAN_PDU_RX_CAN_ENG1S98) && defined(ComConf_ComSignal_NE_MET))
    S2 s2_t_ne;
    U1 u1_t_rxresult;
    U4 u4_t_inst;

    u1_t_rxresult = (U1)ENGSPD_DET_NOT_ACCEPT;
    s2_t_ne       = (S2)0;
    u4_t_inst     = (U4)0U;

    (*u1p_a_stsbit)  = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ENG1S98, ((U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR), u2_ENGSPD_RPM_RXTO_THRSH);
    (*u1p_a_stsbit) &= ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    if((*u1p_a_stsbit) == (U1)0U){
#if 0   /* BEV BSW provisionally */
        (void)Com_ReceiveSignal(ComConf_ComSignal_NE_MET, &s2_t_ne);
#endif

        if((U2)s2_t_ne != (U2)ENGSPD_NE_MET_INVALID){ /* NE_MET signal validity check */

            if(s2_t_ne > (S2)0){
                u4_t_inst = (U4)((S4)s2_t_ne);
            }
            u4_t_inst = u4_t_inst * (U4)ENGSPD_DET_NE_RXCFCNT;
            u4_t_inst = (u4_t_inst + (U4)ENGSPD_DET_NE_ROUND) >> (U4)ENGSPD_DET_NE_LSR_CFCNT;  /* LSB:(12800/256/64)rpm -> 1rpm */

            u1_t_rxresult = (U1)ENGSPD_DET_ACCEPT;
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
    (*u1p_a_stsbit) = (U1)ENGSPD_DET_STSBIT_UNKNOWN;

    return((U1)ENGSPD_DET_NOT_ACCEPT);
#endif
}
/*===================================================================================================================================*/
/*  static U1      u1_s_EngspdDetRpmCanHvNeComRx(U2 * u2p_a_ne, U1 * u1p_a_stsbit)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_EngspdDetRpmCanHvNeComRx(U2 * u2p_a_ne, U1 * u1p_a_stsbit)
{
#if (defined(OXCAN_PDU_RX_CAN_EHV1F04_RXCH0) && defined(ComConf_ComSignal_HV_NE))
    S2 s2_t_ne;
    U1 u1_t_rxresult;
    U4 u4_t_inst;

    u1_t_rxresult = (U1)ENGSPD_DET_NOT_ACCEPT;
    s2_t_ne       = (S2)0;
    u4_t_inst     = (U4)0U;

    (*u1p_a_stsbit)  = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_EHV1F04_RXCH0, ((U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR), u2_ENGSPD_DET_RPM_RXTO_THRSH);
    (*u1p_a_stsbit) &= ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    if((*u1p_a_stsbit) == (U1)0U){
        (void)Com_ReceiveSignal(ComConf_ComSignal_HV_NE, &s2_t_ne);

        if(s2_t_ne > (S2)0){
            u4_t_inst = (U4)s2_t_ne;
        }
        u4_t_inst = u4_t_inst * (U4)ENGSPD_DET_NE_RXCFCNT;
        u4_t_inst = (u4_t_inst + (U4)ENGSPD_DET_NE_ROUND) >> (U4)ENGSPD_DET_NE_LSR_CFCNT;  /* LSB:(12800/256/64)rpm -> 1rpm */

        u1_t_rxresult = (U1)ENGSPD_DET_ACCEPT;
    }
    else if(((*u1p_a_stsbit) & (U1)COM_TIMEOUT) == (U1)COM_TIMEOUT) {
        /* u4_t_inst = (U4)0U; */
        /* u1_t_rxresult = (U1)ENGSPD_NOT_ACCEPT; */
    }
    else{ /* COM_NO_RX case */
        /* u4_t_inst = (U4)0U; */
        u1_t_rxresult = (U1)ENGSPD_DET_ACCEPT;
    }

    (*u2p_a_ne) = (U2)u4_t_inst;

    return(u1_t_rxresult);
#else
    (*u2p_a_ne)     = (U2)0U;
    (*u1p_a_stsbit) = (U1)ENGSPD_DET_STSBIT_UNKNOWN;

    return((U1)ENGSPD_DET_NOT_ACCEPT);
#endif
}
/*===================================================================================================================================*/
/*  static U1      u1_s_EngspdDetRpmCanNe1ComRx(U2 * u2p_a_ne, U1 * u1p_a_stsbit)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_EngspdDetRpmCanNe1ComRx(U2 * u2p_a_ne, U1 * u1p_a_stsbit)
{
    S2 s2_t_ne;
    U4 u4_t_inst;

    s2_t_ne       = (S2)0;
    u4_t_inst     = (U4)0U;

    (*u1p_a_stsbit)  = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ENG1G02, ((U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR), u2_ENGSPD_DET_RPM_RXTO_THRSH);
    (*u1p_a_stsbit) &= ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    if((*u1p_a_stsbit) == (U1)0U){
#if 0   /* BEV BSW provisionally */
        (void)Com_ReceiveSignal(ComConf_ComSignal_NE1, &s2_t_ne);
#endif

        if(s2_t_ne > (S2)0){
            u4_t_inst = (U4)s2_t_ne;
        }
        u4_t_inst = u4_t_inst * (U4)ENGSPD_DET_NE_RXCFCNT;
        u4_t_inst = (u4_t_inst + (U4)ENGSPD_DET_NE_ROUND) >> (U4)ENGSPD_DET_NE_LSR_CFCNT;  /* LSB:(12800/256/64)rpm -> 1rpm */

    }
    else{ /* COM_NO_RX/COM_TIMEOUT case */
        /* u4_t_inst = (U4)0U; */
    }

    (*u2p_a_ne) = (U2)u4_t_inst;

    return((U1)ENGSPD_DET_ACCEPT);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    02/15/2023  TX       New.                                                                                               */
/*  1.1.0    12/23/2023  TH       Update for 19PFv3                                                                                  */
/*                                                                                                                                   */
/*  * TX   = Tong Xinyuan, Dnst                                                                                                      */
/*  * TH   = Taisuke, Hirakawa, KSE                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/
