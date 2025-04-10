/* 2.2.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Vehicle Power Transmission                                                                                                       */
/*  Shift by wire                                                                                                                    */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VPTRAN_BYW_C_MAJOR                      (2)
#define VPTRAN_BYW_C_MINOR                      (2)
#define VPTRAN_BYW_C_PATCH                      (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "vptran_byw_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((VPTRAN_BYW_C_MAJOR != VPTRAN_BYW_H_MAJOR) || \
     (VPTRAN_BYW_C_MINOR != VPTRAN_BYW_H_MINOR) || \
     (VPTRAN_BYW_C_PATCH != VPTRAN_BYW_H_PATCH))
#error "vptran_byw.c and vptran_byw.h : source and header files are inconsistent!"
#endif

#if ((VPTRAN_BYW_C_MAJOR != VPTRAN_BYW_CFG_PRIVATE_H_MAJOR) || \
     (VPTRAN_BYW_C_MINOR != VPTRAN_BYW_CFG_PRIVATE_H_MINOR) || \
     (VPTRAN_BYW_C_PATCH != VPTRAN_BYW_CFG_PRIVATE_H_PATCH))
#error "vptran_byw.c and vptran_byw_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VPTRAN_BYW_GEAR_MSK                     (0x000FU)
#define VPTRAN_BYW_NUM_RNG                      (9U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  U2                                      u2_sp_vptran_byw_val[VPTRAN_NUM_APP];
static  U1                                      u1_s_vptran_byw_rng_sts;
static  U1                                      u1_s_vptran_byw_ger_sts;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  void    vd_s_VptranBywGetSgnl(U1 * const u1_ap_signal);
static  U2      u2_s_VptranBywGetSftRng(const U1 u1_a_SIG, const U1 u1_a_SFTBLKS_STS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/* void            vd_g_VptranBywInit(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_VptranBywInit(void)
{
    U4          u4_t_loop;


    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)VPTRAN_NUM_APP; u4_t_loop++) {
        u2_sp_vptran_byw_val[u4_t_loop] = (U2)VPTRAN_OFF;
    }
    u1_s_vptran_byw_rng_sts   = (U1)VPTRAN_UNKNOWN;
    u1_s_vptran_byw_ger_sts   = (U1)VPTRAN_UNKNOWN;
}

/*===================================================================================================================================*/
/* void            vd_g_VptranByw(const U4 u4_a_PWRSTS)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_VptranByw(const U4 u4_a_PWRSTS)
{
    U4                                          u4_t_loop;
    U1                                          u1_tp_signal[VPTRAN_NUM_APP];
    U1                                          u1_t_sft_blks_sts;


    /*  Signal  */
    u1_s_vptran_byw_rng_sts   = u1_g_VptranBywCfgGetMsgStsRNG();
    u1_s_vptran_byw_ger_sts   = u1_g_VptranBywCfgGetMsgStsGR();
    u1_t_sft_blks_sts         = u1_g_VptranBywCfgGetMsgStsSftBlks();

    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)VPTRAN_NUM_APP; u4_t_loop++ ) {
        u2_sp_vptran_byw_val[u4_t_loop] = (U2)VPTRAN_OFF;
    }
    vd_s_VptranBywGetSgnl(&u1_tp_signal[0]);

    /*  Range  */
    u2_sp_vptran_byw_val[VPTRAN_APP_RNG] = u2_s_VptranBywGetSftRng(u1_tp_signal[VPTRAN_APP_RNG], u1_t_sft_blks_sts);

    if ((u4_a_PWRSTS & (U4)VPTRAN_PWRSTSBIT_IGON) != (U4)0U) {
        /*  Gear & Gsi */
        u2_sp_vptran_byw_val[VPTRAN_APP_GR]  = (U2)u1_tp_signal[VPTRAN_APP_GR] & (U2)VPTRAN_BYW_GEAR_MSK;
        u2_sp_vptran_byw_val[VPTRAN_APP_GSI] = (U2)u1_tp_signal[VPTRAN_APP_GSI];
    }
}

/*===================================================================================================================================*/
/* U1              u1_g_VptranBywGetSts(const U1 u1_a_APPID, U2 * const u2_ap_value)                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_VptranBywGetSts(const U1 u1_a_APPID, U2 * const u2_ap_value)
{
    U1          u1_t_status;

    u1_t_status = (U1)VPTRAN_UNKNOWN;
    if((u1_a_APPID   < (U1)VPTRAN_NUM_APP) &&
       (u2_ap_value != vdp_PTR_NA        )){
        (*u2_ap_value) = u2_sp_vptran_byw_val[u1_a_APPID];

        switch (u1_a_APPID) {
            case (U1)VPTRAN_APP_GSI:
            case (U1)VPTRAN_APP_GR:    /* fall through */
                u1_t_status = u1_s_vptran_byw_ger_sts;
                break;
            default:        /* case VPTRAN_APP_RNG */
                u1_t_status = u1_s_vptran_byw_rng_sts;
                break;
        }
    }

    return (u1_t_status);
}

/*===================================================================================================================================*/
/* static  void    vd_s_VptranBywGetSgnl(U1 * const u1_ap_signal)                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_VptranBywGetSgnl(U1 * const u1_ap_signal)
{
    static  const  U1     u1_s_RNG_MSK       = (U1)0x0FU;
    static  const  U1     u1_s_GSI_MSK       = (U1)0x03U;
    static  const  U1     u1_s_GSI_SFT       = (U1)1U;
    static  const  U1     u1_s_BGEARS_MSK    = (U1)0x0FU;
    static  const  U1     u1_s_SFTBLKS_MSK   = (U1)0x03U;
    static  const  U1     u1_s_SFTBLKS_SFT   = (U1)6U;

    u1_ap_signal[VPTRAN_APP_RNG]    = u1_g_VptranBywCfgGetSFTMETS();
    u1_ap_signal[VPTRAN_APP_RNG]   &= u1_s_RNG_MSK;
    u1_ap_signal[VPTRAN_APP_RNG]   |= (U1)((u1_g_VptranBywCfgGetSFTBLKS() & u1_s_SFTBLKS_MSK) << u1_s_SFTBLKS_SFT);

    u1_ap_signal[VPTRAN_APP_GSI]    = u1_g_VptranBywCfgGetBSLUPS();
    u1_ap_signal[VPTRAN_APP_GSI]   |= (U1)(u1_g_VptranBywCfgGetBSLDNS() << u1_s_GSI_SFT);
    u1_ap_signal[VPTRAN_APP_GSI]   &= u1_s_GSI_MSK;

    u1_ap_signal[VPTRAN_APP_GR]     = u1_g_VptranBywCfgGetBGEARS();
    u1_ap_signal[VPTRAN_APP_GR]    &= u1_s_BGEARS_MSK;
}

/*===================================================================================================================================*/
/* static  U2      u2_s_VptranBywGetSftRng(const U1 u1_a_SIG, const U1 u1_a_SFTBLKS_STS)                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U2      u2_s_VptranBywGetSftRng(const U1 u1_a_SIG, const U1 u1_a_SFTBLKS_STS)
{
    static const    U2          u2_sp_SFTMET_TBL[VPTRAN_BYW_NUM_RNG] = {
        (U2)VPTRAN_OFF,         /* SFT_METS = 0000b */
        (U2)VPTRAN_RNG_P_ON,    /* SFT_METS = 0001b */
        (U2)VPTRAN_RNG_R_ON,    /* SFT_METS = 0010b */
        (U2)VPTRAN_RNG_N_ON,    /* SFT_METS = 0011b */
        (U2)VPTRAN_RNG_D_ON,    /* SFT_METS = 0100b */
        (U2)VPTRAN_RNG_B_ON,    /* SFT_METS = 0101b */
        (U2)VPTRAN_RNG_M_ON,    /* SFT_METS = 0110b */
        (U2)VPTRAN_RNG_S_ON,    /* SFT_METS = 0111b */
        (U2)VPTRAN_RNG_SD_ON    /* SFT_METS = 1000b */
                                /* SFT_METS = Other than above: VPTRAN_OFF */
    };
    static const    U1          u1_s_SIG_MSK            = (U1)0x0FU;
    static const    U1          u1_s_STS_BLKS_MSK       = (U1)0xC0U;
    static const    U1          u1_s_STS_DBL_PARK       = (U1)0x80U;


    U2      u2_t_rng;
    U1      u1_t_sft;
    U1      u1_t_sftmet;

    u1_t_sftmet = (u1_a_SIG & u1_s_SIG_MSK);
    if (u1_t_sftmet < (U1)VPTRAN_BYW_NUM_RNG) {
        u2_t_rng = u2_sp_SFTMET_TBL[u1_t_sftmet];
    } else {
        u2_t_rng = (U2)VPTRAN_OFF;
    }

    u1_t_sft = (U1)0U;


    if (u1_a_SFTBLKS_STS == (U1)0U) {
        u1_t_sft |= (U1)(u1_a_SIG & u1_s_STS_BLKS_MSK);
    }
    

    if ((u1_t_sft & u1_s_STS_BLKS_MSK) == u1_s_STS_DBL_PARK){
        u2_t_rng |= (U2)VPTRAN_STS_DBL_PARK;
    }

    return (u2_t_rng);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    02/13/2018  HY       New.                                                                                               */
/*  1.1.0    10/08/2019  YI       Add B Range Condition to u2_s_GRMSK                                                                */
/*  1.2.0    02/24/2020  KK       MET-D_SBW-CSTD-1-00-A-C0 (Simplified Shift Indicator)                                              */
/*  1.3.0    10/08/2020  KK       MET-D_SFTEXI-CSTD-0-02-A-C3                                                                        */
/*  1.4.0    01/21/2021  TN       Add: Deceleration level support (DCLDSP-CSTD-0-00-A-C0)                                           */
/*  2.0.1    10/18/2021  TA(M)    Change the definition of the null pointer used.(BSW v115_r007)                                     */
/*  2.1.0    12/19/2023  GM       19PFv3 CV Change                                                                                   */
/*  2.2.0    02/10/2025  HF       Change config for BEV System_Consideration_1.(MET-D_SFTPOS-CSTD-1-)                                */
/*                                                                                                                                   */
/*  * HY   = Hidefumi Yoshida, Denso                                                                                                 */
/*  * KK   = Kohei Kato,       Denso Techno                                                                                          */
/*  * TN   = Tetsu Naruse,     Denso Techno                                                                                          */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*  * GM   = Glen Monteposo  , DTPH                                                                                                  */
/*  * HF   = Hinari Fukamachi,KSE                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
