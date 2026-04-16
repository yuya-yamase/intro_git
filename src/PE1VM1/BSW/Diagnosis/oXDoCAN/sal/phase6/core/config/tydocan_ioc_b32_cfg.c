/* 2.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  TyDoCAN I/O Control / Request Message Bitfield Max 32 Bits                                                                       */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDOCAN_IOC_B32_CFG_C_MAJOR              (2)
#define TYDOCAN_IOC_B32_CFG_C_MINOR              (0)
#define TYDOCAN_IOC_B32_CFG_C_PATCH              (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "tydocan_ioc_b32_cfg_private.h"
#include "oxdocan_saif.h"

#include "unitconvrt.h"

#include "sound_cri_mgr.h"

#include "locale.h"
#include "vehspd_kmph.h"
#include "xspi_met_dsal.h"

#include "vardef.h"
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((TYDOCAN_IOC_B32_CFG_C_MAJOR != TYDOCAN_IOC_B32_CFG_H_MAJOR) || \
     (TYDOCAN_IOC_B32_CFG_C_MINOR != TYDOCAN_IOC_B32_CFG_H_MINOR) || \
     (TYDOCAN_IOC_B32_CFG_C_PATCH != TYDOCAN_IOC_B32_CFG_H_PATCH))
#error "tydocan_ioc_b32_cfg.c and tydocan_ioc_b32_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_SPKSF_NUM_BY_DID                    (32U)
#define TYDC_VSI_NUM_XMPH                        (16U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U4                         u4_gp_tydc_ioc_r32[TYDC_IOC_R32_NWORD * TYDC_IOC_B32_NUM_DID];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_TydcIocB32Sup_Mid(const U2 u2_a_GR);
static void    vd_s_TydcIocB32Act_Mid(const U2 u2_a_GR, const U4 * u4_ap_R32);
static void    vd_s_TydcIocB32Dea_Mid(const U2 u2_a_GR);

static U4      u4_s_TydcIocB32Sup_Vsi(const U2 u2_a_GR);
static void    vd_s_TydcIocB32Act_Vsi(const U2 u2_a_GR, const U4 * u4_ap_R32);
static void    vd_s_TydcIocB32Dea_Vsi(const U2 u2_a_GR);

static U4      u4_s_TydcIocB32Sup_Spksf(const U2 u2_a_GR);
static void    vd_s_TydcIocB32Act_Spksf(const U2 u2_a_GR, const U4 * u4_ap_R32);
static void    vd_s_TydcIocB32Dea_Spksf(const U2 u2_a_GR);
static U4      u4_s_TydcIocB32Sup_Hud(const U2 u2_a_GR);
static void    vd_s_TydcIocB32Act_Hud(const U2 u2_a_GR, const U4 * u4_ap_R32);
static void    vd_s_TydcIocB32Dea_Hud(const U2 u2_a_GR);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_IOC_IF_SPKSF                        (0U)
#define TYDC_IOC_IF_MID                          (1U)
#define TYDC_IOC_IF_VSI                          (2U)
#define TYDC_IOC_IF_HUD                          (3U)
static const ST_TYDC_IOC_B32_IF   st_sp_TYDC_IOC_B32_IF[] = {
    {
        &u4_s_TydcIocB32Sup_Spksf,                     /* fp_u4_SUP */
        vdp_PTR_NA,                                    /* fp_u4_LAS */
        &vd_s_TydcIocB32Act_Spksf,                     /* fp_vd_ACT */
        &vd_s_TydcIocB32Dea_Spksf                      /* fp_vd_DEA */
    },
    {
        &u4_s_TydcIocB32Sup_Mid,                       /* fp_u4_SUP */
        vdp_PTR_NA,                                    /* fp_u4_LAS */
        &vd_s_TydcIocB32Act_Mid,                       /* fp_vd_ACT */
        &vd_s_TydcIocB32Dea_Mid                        /* fp_vd_DEA */
    },
    {
        &u4_s_TydcIocB32Sup_Vsi,                       /* fp_u4_SUP */
        vdp_PTR_NA,                                    /* fp_u4_LAS */
        &vd_s_TydcIocB32Act_Vsi,                       /* fp_vd_ACT */
        &vd_s_TydcIocB32Dea_Vsi                        /* fp_vd_DEA */
    },
    {
        &u4_s_TydcIocB32Sup_Hud,                       /* fp_u4_SUP */
        vdp_PTR_NA,                                    /* fp_u4_LAS */
        &vd_s_TydcIocB32Act_Hud,                       /* fp_vd_ACT */
        &vd_s_TydcIocB32Dea_Hud                        /* fp_vd_DEA */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_TYDC_IOC_B32             st_gp_TYDC_IOC_B32[TYDC_IOC_B32_NUM_DID] = {
  /* stp_IF,                                     u2_gr,                     u1_sb_chk,  u1_nbyte */
    /* 280B/280C                 */
    /* Not Use st_gp_TYDC_IOC_B32*/

    /* Speaker Sound file        */
    {&st_sp_TYDC_IOC_B32_IF[TYDC_IOC_IF_SPKSF],  (U2)U2_MAX,                (U1)TRUE,   (U1)OXDC_DATA_IOC_REQ_NB_2829},

    /* Multi-Information Display */
    {&st_sp_TYDC_IOC_B32_IF[TYDC_IOC_IF_MID],    (U2)U2_MAX,                (U1)TRUE,   (U1)OXDC_DATA_IOC_REQ_NB_2831},

    {&st_sp_TYDC_IOC_B32_IF[TYDC_IOC_IF_VSI],    (U2)U2_MAX,                (U1)TRUE,   (U1)OXDC_DATA_IOC_REQ_NB_2A01},

    {&st_sp_TYDC_IOC_B32_IF[TYDC_IOC_IF_HUD],    (U2)U2_MAX,                (U1)TRUE,   (U1)OXDC_DATA_IOC_REQ_NB_2B01}
};
const U2                          u2_g_TYDC_IOC_B32_NUM_DID = (U2)TYDC_IOC_B32_NUM_DID;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_TydcIocB32Sup_Mid(const U2 u2_a_GR)                                                                          */
/*  static void    vd_s_TydcIocB32Act_Mid(const U2 u2_a_GR, const U4 * u4_ap_R32)                                                    */
/*  static void    vd_s_TydcIocB32Dea_Mid(const U2 u2_a_GR)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_TydcIocB32Sup_Mid(const U2 u2_a_GR)
{
    return((U4)0x000000c0U);
}
/* --------------------------------------------------------------------------------------------------------------------------------- */
static void    vd_s_TydcIocB32Act_Mid(const U2 u2_a_GR, const U4 * u4_ap_R32)
{
    U4                      u4_t_req_tx;

    u4_t_req_tx = (U4)0x00000001U << u4_ap_R32[TYDC_IOC_R32_CST];
    vd_g_XSpiDsrUnlock((U4)XSPI_DSR_UNLOCK);
    vd_g_XSpiDsrTx((U1)XSPI_DSR_2F_MID, u4_t_req_tx);
}
/* --------------------------------------------------------------------------------------------------------------------------------- */
static void    vd_s_TydcIocB32Dea_Mid(const U2 u2_a_GR)
{
    vd_g_XSpiDsrUnlock((U4)XSPI_DSR_UNLOCK);
    vd_g_XSpiDsrTx((U1)XSPI_DSR_2F_MID, (U4)0U);
}
/*===================================================================================================================================*/
/*  static U4      u4_s_TydcIocB32Sup_Vsi(const U2 u2_a_GR)                                                                          */
/*  static void    vd_s_TydcIocB32Act_Vsi(const U2 u2_a_GR, const U4 * u4_ap_R32)                                                    */
/*  static void    vd_s_TydcIocB32Dea_Vsi(const U2 u2_a_GR)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_TydcIocB32Sup_Vsi(const U2 u2_a_GR)
{
    return((U4)0x0000e0ffU);
}
/* --------------------------------------------------------------------------------------------------------------------------------- */
static void    vd_s_TydcIocB32Act_Vsi(const U2 u2_a_GR, const U4 * u4_ap_R32)
{
    static const U2         u2_sp_TYDC_IOC_VSI_KMPH[TYDC_VSI_NUM_XMPH] = {
        /* u1_ap_CSM[1] */
        (U2)280U * (U2)VEHSPD_1_KMPH,   /* b0 */
        (U2)240U * (U2)VEHSPD_1_KMPH,   /* b1 */
        (U2)200U * (U2)VEHSPD_1_KMPH,   /* b2 */
        (U2)160U * (U2)VEHSPD_1_KMPH,   /* b3 */
        (U2)120U * (U2)VEHSPD_1_KMPH,   /* b4 */
        (U2)80U  * (U2)VEHSPD_1_KMPH,   /* b5 */
        (U2)40U  * (U2)VEHSPD_1_KMPH,   /* b6 */
        (U2)0U   * (U2)VEHSPD_1_KMPH,   /* b7 */

        /* u1_ap_CSM[3] */
        (U2)0U,                         /* b0 */
        (U2)0U,                         /* b1 */
        (U2)0U,                         /* b2 */
        (U2)0U,                         /* b3 */
        (U2)0U,                         /* b4 */
        (U2)400U * (U2)VEHSPD_1_KMPH,   /* b5 */
        (U2)360U * (U2)VEHSPD_1_KMPH,   /* b6 */
        (U2)320U * (U2)VEHSPD_1_KMPH    /* b7 */
    };

    U4                      u4_t_kmph;
    U1                      u1_t_unit;

    u4_t_kmph = u4_ap_R32[TYDC_IOC_R32_CST];
    if(u4_t_kmph < (U4)TYDC_VSI_NUM_XMPH){

        u4_t_kmph = (U4)u2_sp_TYDC_IOC_VSI_KMPH[u4_t_kmph];
        u1_t_unit = u1_g_Unit((U1)UNIT_IDX_SPEED);
        if(u1_t_unit == (U1)UNIT_VAL_SPEED_MPH){
            u4_t_kmph = u4_g_UnitconvtrMitoKm(u4_t_kmph);
            if(u4_t_kmph > (U4)U2_MAX){
                u4_t_kmph = (U4)U2_MAX;
            }
        }
        vd_g_VehspdKmphOwUnlock((U4)VEHSPD_OW_UNLOCK);
        vd_g_VehspdKmphOwAct((U2)u4_t_kmph);
    }
}
/* --------------------------------------------------------------------------------------------------------------------------------- */
static void    vd_s_TydcIocB32Dea_Vsi(const U2 u2_a_GR)
{
    vd_g_VehspdKmphOwDeAct();
}
/*===================================================================================================================================*/
/*  static U4      u4_s_TydcIocB32Sup_Spksf(const U2 u2_a_GR)                                                                        */
/*  static void    vd_s_TydcIocB32Act_Spksf(const U2 u2_a_GR, const U4 * u4_ap_R32)                                                  */
/*  static void    vd_s_TydcIocB32Dea_Spksf(const U2 u2_a_GR)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_TydcIocB32Sup_Spksf(const U2 u2_a_GR)
{
    return((U4)0xE0FCF0FFU);
}
/* --------------------------------------------------------------------------------------------------------------------------------- */
static void    vd_s_TydcIocB32Act_Spksf(const U2 u2_a_GR, const U4 * u4_ap_R32)
{
    static const U1         u1_sp_TYDC_IOC_SPKSF[] = {
        /* #6 */
        (U1)SOUND_AT_CLESON_RRF,            /* #6 bit 0 Clearance sonar Rr detection (Farthest distance)                    */
        (U1)SOUND_AT_CLESON_RRL,            /* #6 bit 1 Clearance sonar Rr detection (Long distance)                        */
        (U1)SOUND_AT_CLESON_RRM,            /* #6 bit 2 Clearance sonar Rr detection (Medium distance)                      */
        (U1)SOUND_AT_CLESON_RRS,            /* #6 bit 3 Clearance sonar Rr detection (Closest approach/Short distance)      */
        (U1)SOUND_AT_CLESON_FRF,            /* #6 bit 4 Clearance sonar Fr detection (Farthest distance)                    */
        (U1)SOUND_AT_CLESON_FRL,            /* #6 bit 5 Clearance sonar Fr detection (Long distance)                        */
        (U1)SOUND_AT_CLESON_FRM,            /* #6 bit 6 Clearance sonar Fr detection (Medium distance)                      */
        (U1)SOUND_AT_CLESON_FRS,            /* #6 bit 7 Clearance sonar Fr detection (Closest approach/Short distance)      */

        /* #8 */
        (U1)U1_MAX,                         /* #8 bit 0 undefine                                                            */
        (U1)U1_MAX,                         /* #8 bit 1 undefine                                                            */
        (U1)U1_MAX,                         /* #8 bit 2 undefine                                                            */
        (U1)U1_MAX,                         /* #8 bit 3 undefine                                                            */
        (U1)SOUND_AT_CLESON_FRRRF,          /* #8 bit 4 Clearance sonar Fr & Rr detection (Farthest distance)               */
        (U1)SOUND_AT_CLESON_FRRRL,          /* #8 bit 5 Clearance sonar Fr & Rr detection (Long distance)                   */
        (U1)SOUND_AT_CLESON_FRRRM,          /* #8 bit 6 Clearance sonar Fr & Rr detection (Medium distance)                 */
        (U1)SOUND_AT_CLESON_FRRRS,          /* #8 bit 7 Clearance sonar Fr & Rr detection (Closest approach/Short distance) */

        /* #10 */
        (U1)U1_MAX,                         /* #10 bit 0 undefine                                                           */
        (U1)U1_MAX,                         /* #10 bit 1 undefine                                                           */
        (U1)SOUND_AT_SEAREM_SI,             /* #10 bit 2 Unbuckle notification buzzer                                       */
        (U1)SOUND_AT_SEAREM_LV1,            /* #10 bit 3 Seatbelt reminder buzzer (Level 1)                                 */
        (U1)SOUND_AT_SEAREM_LV2,            /* #10 bit 4 Seatbelt reminder buzzer (Level 2)                                 */
        (U1)SOUND_AT_SEAREM_FMV,            /* #10 bit 5 Seatbelt reminder buzzer (Regulation intermittence)                */
        (U1)SOUND_AT_SBW_REVERSE_IN,        /* #10 bit 6 SBW reverse buzzer                                                 */
        (U1)U1_MAX,    /* BEV Diag provisionally */         /* #10 bit 7 A/T reverse buzzer                                                 */

        /* #12 */
        (U1)U1_MAX,                         /* #12 bit 0 undefine                                                           */
        (U1)U1_MAX,                         /* #12 bit 1 undefine                                                           */
        (U1)U1_MAX,                         /* #12 bit 2 undefine                                                           */
        (U1)U1_MAX,                         /* #12 bit 3 undefine                                                           */
        (U1)U1_MAX,                         /* #12 bit 4 undefine                                                           */
        (U1)SOUND_AT_MMTURHAZ_FIN,          /* #12 bit 5 Flasher operating sound (End of lighting)                          */
        (U1)SOUND_AT_MMTURHAZ_STA,          /* #12 bit 6 Flasher operating sound (Start of lighting)                        */
        (U1)U1_MAX    /* BEV Diag provisionally */                  /* #12 bit 7 Master caution buzzer                                              */
    };

    U4                      u4_t_idx;        

    if(u4_ap_R32[TYDC_IOC_R32_CST] < (U4)TYDC_SPKSF_NUM_BY_DID){

        u4_t_idx = u4_ap_R32[TYDC_IOC_R32_CST];
        vd_g_SoundCriMgrOwUnlock((U4)SOUND_CRI_MNG_OW_UNLOCK);
        vd_g_SoundCriMgrOwAct((U1)SOUND_CH_00, u1_sp_TYDC_IOC_SPKSF[u4_t_idx]);
    }
}
/* --------------------------------------------------------------------------------------------------------------------------------- */
static void    vd_s_TydcIocB32Dea_Spksf(const U2 u2_a_GR)
{
    vd_g_SoundCriMgrOwDeAct((U1)SOUND_CH_00);
}
/*===================================================================================================================================*/
/*  static U4      u4_s_TydcIocB32Sup_Hud(const U2 u2_a_GR)                                                                          */
/*  static void    vd_s_TydcIocB32Act_Hud(const U2 u2_a_GR, const U4 * u4_ap_R32)                                                    */
/*  static void    vd_s_TydcIocB32Dea_Hud(const U2 u2_a_GR)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_TydcIocB32Sup_Hud(const U2 u2_a_GR)
{
    U1 u1_t_hud;
    U4 u4_t_sup;

    u1_t_hud = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_GVIF2);
    if(u1_t_hud == (U1)TRUE){
        u4_t_sup = (U4)0x000000feU;
    }
    else{
        u4_t_sup = (U4)0U;
    }

    return(u4_t_sup);
}
/* --------------------------------------------------------------------------------------------------------------------------------- */
static void    vd_s_TydcIocB32Act_Hud(const U2 u2_a_GR, const U4 * u4_ap_R32)
{
    static const U1         u1_sp_TYDC_IOC_HUD[] =  {
        (U1)0x00U,                   /* 0 */
        (U1)XSPI_HUD_ADJ,        /* 1 */
        (U1)XSPI_HUD_COL,        /* 2 */
        (U1)XSPI_HUD_BLU,        /* 3 */
        (U1)XSPI_HUD_GRE,        /* 4 */
        (U1)XSPI_HUD_RED,        /* 5 */
        (U1)XSPI_HUD_WHI,        /* 6 */
        (U1)XSPI_HUD_BLA         /* 7 */
    };
    static const U1         u1_s_TYDC_IOC_NUM_HUD = (U1)sizeof(u1_sp_TYDC_IOC_HUD);
    U4                      u4_t_req_tx;

    u4_t_req_tx = u4_ap_R32[TYDC_IOC_R32_CST];
    if(u4_t_req_tx < (U4)u1_s_TYDC_IOC_NUM_HUD){
        vd_g_XSpiDsrUnlock((U4)XSPI_DSR_UNLOCK);
        vd_g_XSpiDsrTx((U1)XSPI_DSR_2F_HUD, (U4)u1_sp_TYDC_IOC_HUD[u4_t_req_tx]);
    }
}
/* --------------------------------------------------------------------------------------------------------------------------------- */
static void    vd_s_TydcIocB32Dea_Hud(const U2 u2_a_GR)
{
    vd_g_XSpiDsrUnlock((U4)XSPI_DSR_UNLOCK);
    vd_g_XSpiDsrTx((U1)XSPI_DSR_2F_HUD, (U4)0U);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     3/20/2020  TN       New.                                                                                               */
/*  2.0.0     6/20/2024  TK       Abolition ControlEnableMask for 19PFv3 Phase6Diag                                                  */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  800B-1   10/06/2020  AS       Configured for 800B                                                                                */
/*  19PFv3-1 08/02/2024  TK       Configured for 19PFv3 R1.3                                                                         */
/*  BEV-1    12/09/2025  SI       Delete DID-2821/2822/2823/2824/2825/2827/2A21/2A22                                                 */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*  * AS   = Atsunori Sugita, DENSO-TECHNO                                                                                           */
/*  * TK   = Toru Kamishina,  Denso Techno                                                                                           */
/*  * SI   = Shugo Ichinose,  Denso Techno                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/
