/* 3.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Meter Customize                                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define MCST_CFG_C_MAJOR                     (3)
#define MCST_CFG_C_MINOR                     (0)
#define MCST_CFG_C_PATCH                     (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "mcst_cfg_private.h"
#include "rim_ctl.h"
#include "oxcan.h"
#include "vardef.h"
#include "dimmer.h"
#include "hmimcst.h"
#include "mcst_bf.h"
#include "calibration.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((MCST_CFG_C_MAJOR != MCST_H_MAJOR) || \
     (MCST_CFG_C_MINOR != MCST_H_MINOR) || \
     (MCST_CFG_C_PATCH != MCST_H_PATCH))
#error "mcst_cfg.c and mcst.h : source and header files are inconsistent!"
#endif

#if ((MCST_CFG_C_MAJOR != MCST_CFG_H_MAJOR) || \
     (MCST_CFG_C_MINOR != MCST_CFG_H_MINOR) || \
     (MCST_CFG_C_PATCH != MCST_CFG_H_PATCH))
#error "mcst_cfg.c and mcst_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define MCST_USRDAT_NUM                          (16U)
#define MCST_USR_NUM                             (4U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct {
    U1         u1_id;                                /* mcst id            */
    U4         ( * fp_u4_cfgini)(const U1 u1_a_id);  /* init cfg parameter */
}ST_MCST_CFG_INI;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U4                      u4_gp_mcst_bfword[MCST_NUM_WORD];
U4                      u4_gp_mcst_bfword_unk[MCST_NUM_WORD_USER];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static        U4      u4_s_McstCfgRheoNightInit(const U1 u1_a_id);
static inline U1      u1_s_McstCfgCalibU1MaxChk(const U1 u1_a_CALIBID, const U1 u1_a_MAX, const U1 u1_a_DEF);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U2 u2_sp_MCST_NVMID[MCST_NUM_NVM] = {
    (U2)NVMCID_OTR_MCST_IDX_GUEST_1,
    (U2)NVMCID_OTR_MCST_IDX_GUEST_2,
    (U2)NVMCID_OTR_MCST_IDX_USER1_1,
    (U2)NVMCID_OTR_MCST_IDX_USER1_2,
    (U2)NVMCID_OTR_MCST_IDX_USER2_1,
    (U2)NVMCID_OTR_MCST_IDX_USER2_2,
    (U2)NVMCID_OTR_MCST_IDX_USER3_1,
    (U2)NVMCID_OTR_MCST_IDX_USER3_2
};

const ST_MCST_BF        st_gp_MCST_BF[MCST_NUM_BF] = {
    /* u1_sup,                    u1_wid,    u1_lsb,     u4_bit            */
    {(U1)MCST_SUP_SPEED,          (U1)0U,    (U1)0U,     (U4)0x00000003U    },    /* MCST_BFI_SPEED                           */
    {(U1)MCST_SUP_DIST,           (U1)0U,    (U1)4U,     (U4)0x00000003U    },    /* MCST_BFI_DIST                            */
    {(U1)MCST_SUP_ELECO,          (U1)0U,    (U1)8U,     (U4)0x00000007U    },    /* MCST_BFI_ELECO                           */
    {(U1)MCST_SUP_TIMEFMT,        (U1)0U,    (U1)16U,    (U4)0x00000003U    },    /* MCST_BFI_TIMEFMT                         */
    {(U1)MCST_SUP_RHEO_DAY,       (U1)1U,    (U1)8U,     (U4)0x0000001FU    },    /* MCST_BFI_RHEO_DAY                        */
    {(U1)MCST_SUP_RHEO_NIGHT,     (U1)1U,    (U1)0U,     (U4)0x0000001FU    },    /* MCST_BFI_RHEO_NIGHT                      */
    {(U1)MCST_SUP_METWRNCSTM,     (U1)1U,    (U1)16U,    (U4)0x00000007U    },    /* MCST_BFI_METWRNCSTM                      */
    {(U1)MCST_SUP_HUD,            (U1)2U,    (U1)0U,     (U4)0x00000003U    },    /* MCST_BFI_HUD                             */
    {(U1)MCST_SUP_HUDILL,         (U1)2U,    (U1)8U,     (U4)0x0000003FU    },    /* MCST_BFI_HUDILL                          */
    {(U1)MCST_SUP_HUD_ROT,        (U1)2U,    (U1)16U,    (U4)0x000001FFU    }     /* MCST_BFI_HUD_ROT                         */
};

const ST_MCST_INI        st_gp_MCST_INI[MCST_NUM_BF] = {
    /* u1_id,                            u1_ini                                 */
    {(U1)MCST_BFI_SPEED,                 (U4)MCST_INI_SPEED                      },
    {(U1)MCST_BFI_DIST,                  (U4)MCST_INI_DIST                       },
    {(U1)MCST_BFI_ELECO,                 (U4)MCST_INI_ELECO                      },
    {(U1)MCST_BFI_TIMEFMT,               (U4)MCST_INI_TIMEFMT                    },
    {(U1)MCST_BFI_RHEO_DAY,              (U4)MCST_INI_RHEO_DAY                   },
    {(U1)MCST_BFI_RHEO_NIGHT,            (U4)MCST_INI_RHEO_NIGHT                 },
    {(U1)MCST_BFI_METWRNCSTM,            (U4)MCST_INI_METWRNCSTM                 },
    {(U1)MCST_BFI_HUD,                   (U4)MCST_INI_HUD                        },
    {(U1)MCST_BFI_HUDILL,                (U4)MCST_INI_HUDILL                     },
    {(U1)MCST_BFI_HUD_ROT,               (U4)MCST_INI_HUD_ROT                    }
};

const ST_MCST_OFFSET st_gp_MCST_OFFSET[MCST_USR_NUM] =
{
    /* u1_offset                   u1_offset_ini,                  u1_offset_max             */
    {(U1)MCST_BF_OFFSET_GUEST,    (U1)MCST_BF_OFFSET_GUEST_INI,   (U1)MCST_BF_OFFSET_GUEST_MAX},
    {(U1)MCST_BF_OFFSET_USER1,    (U1)MCST_BF_OFFSET_USER1_INI,   (U1)MCST_BF_OFFSET_USER1_MAX},
    {(U1)MCST_BF_OFFSET_USER2,    (U1)MCST_BF_OFFSET_USER2_INI,   (U1)MCST_BF_OFFSET_USER2_MAX},
    {(U1)MCST_BF_OFFSET_USER3,    (U1)MCST_BF_OFFSET_USER3_INI,   (U1)MCST_BF_OFFSET_USER3_MAX}
};

const U1 u1_gp_MCST_PSUND_TABLE[MCST_PSUND_NUM] =
{
    (U1)MCST_USR_UNKNOWN,
    (U1)MCST_USR_USER1,
    (U1)MCST_USR_USER2,
    (U1)MCST_USR_USER3,
    (U1)MCST_USR_UNKNOWN,
    (U1)MCST_USR_UNKNOWN,
    (U1)MCST_USR_UNKNOWN,
    (U1)MCST_USR_GUEST
};

const U1 u1_gp_MCST_PSEU_TABLE[MCST_PSEU_NUM] =
{
    (U1)MCST_USR_NON,
    (U1)MCST_USR_USER1,
    (U1)MCST_USR_USER2,
    (U1)MCST_USR_USER3,
    (U1)MCST_USR_NON,
    (U1)MCST_USR_NON,
    (U1)MCST_USR_NON,
    (U1)MCST_USR_GUEST
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U1                u1_g_MCST_NWORD               = (U1)MCST_NUM_WORD;
const U1                u1_g_MCST_NUM_WORD_USER       = (U1)MCST_NUM_WORD_USER;
const U1                u1_g_MCST_NUM_BF              = (U1)MCST_NUM_BF;
const U1                u1_g_MCST_USRDAT_NUM          = (U1)MCST_USRDAT_NUM;
const U1                u1_g_MCST_USR_NUM             = (U1)MCST_USR_NUM;
const U1                u1_g_MCST_OFFSET_GUEST_INI    = (U1)MCST_BF_OFFSET_GUEST_INI;
const U1                u1_g_MCST_OFFSET_GUEST_MAX    = (U1)MCST_BF_OFFSET_GUEST_MAX;
const U2                u2_g_MCST_RES_TOUT            = (U2)5000U / (U2)MCST_MAIN_TICK;
const U2                u2_g_MCST_RIMID_USER          = (U2)RIMID_U1_MCST_USRNUM_D;
const U1                u1_g_MCST_BFI_HUD             = (U1)MCST_BFI_HUD;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/* U1    u1_g_McstCfgRcvSgnlPSUN_D(U1 * u1p_a_sgnl)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1    u1_g_McstCfgRcvSgnlPSUN_D(U1 * u1p_a_sgnl)
{
    U1  u1_t_sts;

    u1_t_sts = (U1)Com_GetIPDUStatus(MSG_BDB1S27_RXCH0);
    u1_t_sts &= ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    (void)Com_ReceiveSignal(ComConf_ComSignal_PSUN_D, u1p_a_sgnl);

    return(u1_t_sts);
}

/*===================================================================================================================================*/
/* U1    u1_g_McstCfgRcvSgnlPSEU(U1 * u1p_a_sgnl)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1    u1_g_McstCfgRcvSgnlPSEU(U1 * u1p_a_sgnl)
{
    U1  u1_t_sts;

    u1_t_sts = (U1)Com_GetIPDUStatus(MSG_BDB1S28_RXCH0);
    u1_t_sts &= ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    (void)Com_ReceiveSignal(ComConf_ComSignal_PSEU, u1p_a_sgnl);

    return(u1_t_sts);
}

/*===================================================================================================================================*/
/*  U4    u4_g_McstCfgInit(const U1 u1_a_BFI){                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4    u4_g_McstCfgInit(const U1 u1_a_BFI){
    static const ST_MCST_CFG_INI     st_sp_MCST_CFG_INI[] = {
        /* u1_id,                            fp_u4_cfgini                           */
        {(U1)MCST_BFI_SPEED,                 vdp_PTR_NA                              },
        {(U1)MCST_BFI_DIST,                  vdp_PTR_NA                              },
        {(U1)MCST_BFI_ELECO,                 vdp_PTR_NA                              },
        {(U1)MCST_BFI_RHEO_NIGHT,            &u4_s_McstCfgRheoNightInit              },
        {(U1)MCST_BFI_HUDILL,                vdp_PTR_NA                              },
        {(U1)MCST_BFI_HUD,                   vdp_PTR_NA                              },
        {(U1)MCST_BFI_HUD_ROT,               vdp_PTR_NA                              },
        {(U1)MCST_BFI_RHEO_DAY,              vdp_PTR_NA                              },
        {(U1)MCST_BFI_TIMEFMT,               vdp_PTR_NA                              },
        {(U1)MCST_BFI_METWRNCSTM,            vdp_PTR_NA                              }
    };

    U4      u4_t_result;

    u4_t_result = (U4)MCST_BF_UNK_U4;
    if(u1_a_BFI < (U1)MCST_NUM_BF){
        u4_t_result = st_gp_MCST_INI[u1_a_BFI].u4_ini;

        if(st_sp_MCST_CFG_INI[u1_a_BFI].fp_u4_cfgini != vdp_PTR_NA){
            u4_t_result = st_sp_MCST_CFG_INI[u1_a_BFI].fp_u4_cfgini(st_sp_MCST_CFG_INI[u1_a_BFI].u1_id);
        }
    }

    return(u4_t_result);
}

/*===================================================================================================================================*/
/*  void    vd_g_McstCfgUserChgHook(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_McstCfgUserChgHook(void){

    vd_g_DimMcstReadHook();

}

/*===================================================================================================================================*/
/*  void    vd_g_McstCfgUserCstmInitHook(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_McstCfgUserCstmInitHook(void){

    vd_g_DimMcstDataResetHook();

}

/*===================================================================================================================================*/
/*  void    vd_g_McstCfgCstmInitHook(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_McstCfgCstmInitHook(void){
}

/*===================================================================================================================================*/
/*  static U4      u4_s_McstCfgRheoNightInit(const U1 u1_a_id)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u4_t_result                                                                                                      */
/*===================================================================================================================================*/
static  U4      u4_s_McstCfgRheoNightInit(const U1 u1_a_id)
{
    U1      u1_t_rheo_pos;

    u1_t_rheo_pos = u1_s_McstCfgCalibU1MaxChk(u1_CALIB_MCUID0340_RHEOPOS_NIGHT, (U1)CALIB_MCUID0340_MAX, (U1)CALIB_MCUID0340_DEF);

    return((U4)u1_t_rheo_pos);
}

/*===================================================================================================================================*/
/*  static inline U1      u1_s_McstCfgCalibU1MaxChk(const U1 u1_a_CALIBID, const U1 u1_a_MAX, const U1 u1_a_DEF)                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      const U1 u1_a_CALIBID                                                                                            */
/*                  const U1 u1_a_MAX                                                                                                */
/*                  const U1 u1_a_DEF                                                                                                */
/*  Return:         U1 u1_t_ret                                                                                                      */
/*===================================================================================================================================*/
static inline U1      u1_s_McstCfgCalibU1MaxChk(const U1 u1_a_CALIBID, const U1 u1_a_MAX, const U1 u1_a_DEF)
{
    U1 u1_t_ret;

    u1_t_ret = u1_a_CALIBID;
    if(u1_t_ret > u1_a_MAX){
        u1_t_ret = u1_a_DEF;
    }

    return(u1_t_ret);
}


/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    12/07/2018  TA       New.                                                                                               */
/*  1.1.0     3/16/2020  TN       mcst.c v1.0.0 -> v1.1.0.                                                                           */
/*  2.0.0     9/22/2020  TM       mcst.c v1.1.0 -> v2.0.0.                                                                           */
/*  2.1.0     1/13/2021  TM       mcst.c v2.0.0 -> v2.1.0.                                                                           */
/*  2.1.1     4/ 9/2021  TM       mcst.c v2.1.0 -> v2.1.1.                                                                           */
/*  2.1.2     8/ 2/2021  SI       mcst.c v2.1.1 -> v2.1.2.                                                                           */
/*  2.1.3    11/16/2021  SI       mcst.c v2.1.2 -> v2.1.3.                                                                           */
/*  2.1.4    12/27/2021  SI       mcst.c v2.1.3 -> v2.1.4.                                                                           */
/*  2.2.0    02/06/2022  SI       mcst.c v2.1.4 -> v2.2.0.                                                                           */
/*  2.4.0    06/21/2024  SW       mcst.c v2.3.0 -> v2.4.0.                                                                           */
/*  2.5.0    09/11/2024  SW       mcst.c v2.4.0 -> v2.5.0.                                                                           */
/*  2.5.1    02/18/2025  MaO(M)   mcst.c v2.5.0 -> v2.5.1.                                                                           */
/*  2.6.0    05/26/2025  SW       mcst.c v2.5.2 -> v2.6.0.                                                                           */
/*  3.0.0    01/30/2026  SN       mcst.c v2.6.0 -> v3.0.0.                                                                           */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  BEV-1    01/30/2026  SN       Change B_PERMEM for BEV                                                                            */
/*                                                                                                                                   */
/*  * TA   = Teruyuki Anjima, Denso                                                                                                  */
/*  * TM   = Takuya Mitsui,   Denso Techno                                                                                           */
/*  * SI   = Shugo Ichinose,  Denso Techno                                                                                           */
/*  * SW   = Shun Watanabe,   Denso Techno                                                                                           */
/*  * TN   = Tetsushi Nakano, Denso Techno                                                                                           */
/*  * MaO(M) = Masayuki Okada, NTT Data MSE                                                                                          */
/*  * SN   = Shimon Nambu, Denso Techno                                                                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/
