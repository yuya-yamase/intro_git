/* 1.0.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/* Power Indicator                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define DRVIND_PWR_PCT_CFG_C_MAJOR                (1)
#define DRVIND_PWR_PCT_CFG_C_MINOR                (0)
#define DRVIND_PWR_PCT_CFG_C_PATCH                (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "drvind_pwr_pct_cfg_private.h"

#include "oxcan.h"
#if 0   /* BEV BSW provisionally */
#else
#include "Com_Cfg_STUB.h"
#include "oxcan_channel_STUB.h"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((DRVIND_PWR_PCT_CFG_C_MAJOR != DRVIND_PWR_PCT_CFG_H_MAJOR) || \
     (DRVIND_PWR_PCT_CFG_C_MINOR != DRVIND_PWR_PCT_CFG_H_MINOR) || \
     (DRVIND_PWR_PCT_CFG_C_PATCH != DRVIND_PWR_PCT_CFG_H_PATCH))
#error "drvind_pwr_pct_cfg.c and drvind_pwr_pct_cfg_private.h : source and header files are inconsistent!"
#endif

#if ((DRVIND_PWR_PCT_CFG_C_MAJOR != DRVIND_PWR_PCT_H_MAJOR) || \
     (DRVIND_PWR_PCT_CFG_C_MINOR != DRVIND_PWR_PCT_H_MINOR) || \
     (DRVIND_PWR_PCT_CFG_C_PATCH != DRVIND_PWR_PCT_H_PATCH))
#error "drvind_pwr_pct_cfg.c and drvind_pwr_pct.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define DRVIND_PWR_FLTR_MVAVGTIMS                 (32U)                         /* Moving Average Number                             */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((DRVIND_PWR_STSBIT_UNKNOWN != COM_NO_RX  ) || \
     (DRVIND_PWR_STSBIT_INVALID != COM_TIMEOUT))
#error "DRVIND_PWR_STSBIT_UNKNOWN shall be equal to COM_NO_RX and DRVIND_PWR_STSBIT_INVALID shall be equal to COM_TIMEOUT."
#endif

#define DRVIND_PWR_PMEVCR                         (1)                           /* [PMEVCR]  Apply                                   */
#define DRVIND_PWR_PMCHGTH                        (1)                           /* [PMCHGTH] Apply                                   */
#define DRVIND_PWR_PMPWRTH                        (1)                           /* [PMPWRTH] Apply                                   */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
S2          s2_gp_drvind_pwr_pct_smpl[DRVIND_PWR_FLTR_MVAVGTIMS];               /* Moving Average Sample                             */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U1    u1_g_DRVIND_PWR_FLTR_MVAVGTIMS = (U1)DRVIND_PWR_FLTR_MVAVGTIMS;     /* Moving Average Number                             */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  U1      u1_g_DrvIndPwrCfgComRxPMEVCR(S2 * const s2p_a_pct)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      S2 * const s2p_a_pct : Receiving Value                                                                           */
/*  Return:         U1         u1_t_sts  : Receiving Status                                                                          */
/*===================================================================================================================================*/
U1      u1_g_DrvIndPwrCfgComRxPMEVCR(S2 * const s2p_a_pct)
{
#if ((defined(DRVIND_PWR_PMEVCR)) && (DRVIND_PWR_PMEVCR == 1))
    U1                  u1_t_sts;                                               /* Receiving Status                                  */

    (void)Com_ReceiveSignal(ComConf_ComSignal_PMEVCR_2, s2p_a_pct);
    u1_t_sts = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_EHV2G02_RXCH0,
                               ((U2)OXCAN_RX_SYS_NRX_IGP |
                                (U2)OXCAN_RX_SYS_NRX_IGR |
                                (U2)OXCAN_RX_SYS_TOE_IGP |
                                (U2)OXCAN_RX_SYS_TOE_IGR),
                                u2_OXCAN_RXTO_THRSH(3600U)) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    if(*s2p_a_pct == (S2)DRVIND_PWR_PCT_INIT){
        u1_t_sts = (U1)DRVIND_PWR_STSBIT_INVALID;
    }
    return(u1_t_sts);
#else
    return((U1)DRVIND_PWR_STSBIT_UNKNOWN);
#endif /* ((defined(DRVIND_PWR_PMEVCR)) && (DRVIND_PWR_PMEVCR == 1)) */
}

/*===================================================================================================================================*/
/*  U1      u1_g_DrvIndPwrCfgComRxPMCHGTH(S1 * const s1p_a_pct)                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      S1 * const s1p_a_pct : Receiving Value                                                                           */
/*  Return:         U1         u1_t_sts  : Receiving Status                                                                          */
/*===================================================================================================================================*/
U1      u1_g_DrvIndPwrCfgComRxPMCHGTH(S1 * const s1p_a_pct)
{
#if ((defined(DRVIND_PWR_PMCHGTH)) && (DRVIND_PWR_PMCHGTH == 1))
    U1                  u1_t_sts;                                               /* Receiving Status                                  */

    (void)Com_ReceiveSignal(ComConf_ComSignal_PMCHGTH_2, s1p_a_pct);
    u1_t_sts = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_EHV2G02_RXCH0,
                               ((U2)OXCAN_RX_SYS_NRX_IGP |
                                (U2)OXCAN_RX_SYS_NRX_IGR |
                                (U2)OXCAN_RX_SYS_TOE_IGP |
                                (U2)OXCAN_RX_SYS_TOE_IGR),
                                u2_OXCAN_RXTO_THRSH(3600U)) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    return(u1_t_sts);
#else
    return((U1)DRVIND_PWR_STSBIT_UNKNOWN);
#endif /* ((defined(DRVIND_PWR_PMCHGTH)) && (DRVIND_PWR_PMCHGTH == 1)) */
}

/*===================================================================================================================================*/
/*  U1      u1_g_DrvIndPwrCfgComRxPMPWRTH(U2 * const u2p_a_pct)                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U2 * const u2p_a_pct : Receiving Value                                                                           */
/*  Return:         U1         u1_t_sts  : Receiving Status                                                                          */
/*===================================================================================================================================*/
U1      u1_g_DrvIndPwrCfgComRxPMPWRTH(U2 * const u2p_a_pct)
{
#if ((defined(DRVIND_PWR_PMPWRTH)) && (DRVIND_PWR_PMPWRTH == 1))
    U1                  u1_t_sts;                                               /* Receiving Status                                  */

    (void)Com_ReceiveSignal(ComConf_ComSignal_PMPWRTH_2, u2p_a_pct);
    u1_t_sts = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_EHV2G02_RXCH0,
                               ((U2)OXCAN_RX_SYS_NRX_IGP |
                                (U2)OXCAN_RX_SYS_NRX_IGR |
                                (U2)OXCAN_RX_SYS_TOE_IGP |
                                (U2)OXCAN_RX_SYS_TOE_IGR),
                                u2_OXCAN_RXTO_THRSH(3600U)) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    return(u1_t_sts);
#else
    return((U1)DRVIND_PWR_STSBIT_UNKNOWN);
#endif /* ((defined(DRVIND_PWR_PMPWRTH)) && (DRVIND_PWR_PMPWRTH == 1)) */
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version           Date          Author    Change Description                                                                     */
/*  --------------    ----------    ------    -------------------------------------------------------------------------------------  */
/*  1.0.0             2021.02.16    TA        New.                                                                                   */
/*  1.0.1             2022.02.01    TA        Change the definition of the null pointer used.(BSW v115_r008).                        */
/*                                                                                                                                   */
/*  Revision          Date          Author    Change Description                                                                     */
/*  --------------    ----------    ------    -------------------------------------------------------------------------------------  */
/*  050D-1            2021.09.16    TA        Changed for 050D CVRepro (EV)                                                          */
/*  050D-2            2022.02.17    TA        Changed for 050D 1A (EV)                                                               */
/*  19PF-1            2024.06.25    TR        Changed for 19PFV3 (Ported from 050D)                                                  */
/*                                                                                                                                   */
/*  * TA = Tsubasa Aki, Denso Techno                                                                                                 */
/*  * TR = Tebs Ramos, DTPH                                                                                                          */
/*                                                                                                                                   */
/*===================================================================================================================================*/
