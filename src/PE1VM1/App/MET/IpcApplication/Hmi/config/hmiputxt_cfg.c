/* 1.6.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Hmiputxt                                                                                                                         */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define HMIPUTXT_CFG_C_MAJOR                     (1)
#define HMIPUTXT_CFG_C_MINOR                     (6)
#define HMIPUTXT_CFG_C_PATCH                     (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "hmiputxt_cfg_private.h"
#include "hmiputxt_if_cfg.h"

#include "oxcan.h"
#if 0   /* BEV BSW provisionally */
#else
#include "Com_Cfg_STUB.h"
#include "oxcan_channel_STUB.h"
#endif
#include "alert.h"
#if 0   /* BEV BSW provisionally */
#include "fuelvol_tau.h"
#endif
#include "ambtmp.h"
#include "oilmil.h"
#include "odo_om_rst_if.h"
#include "vptran_sel_typ.h"
#include "veh_opemd.h"
#include "vardef.h"
#include "rim_ctl.h"
#if 0   /* BEV BSW provisionally */
#else
#include "rim_ctl_cfg_STUB.h"
#endif
#include "calibration.h"
#if (HMIPUTXT_TIMCHG_JDG == HMIPUTXT_JDG_ON)
#include "evschg.h"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((HMIPUTXT_CFG_C_MAJOR != HMIPUTXT_H_MAJOR) || \
     (HMIPUTXT_CFG_C_MINOR != HMIPUTXT_H_MINOR) || \
     (HMIPUTXT_CFG_C_PATCH != HMIPUTXT_H_PATCH))
#error "hmiputxt_cfg.c and hmiputxt.h : source and header files are inconsistent!"
#endif

#if ((HMIPUTXT_CFG_C_MAJOR != HMIPUTXT_CFG_H_MAJOR) || \
     (HMIPUTXT_CFG_C_MINOR != HMIPUTXT_CFG_H_MINOR) || \
     (HMIPUTXT_CFG_C_PATCH != HMIPUTXT_CFG_H_PATCH))
#error "hmiputxt_cfg.c and hmiputxt_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define HMIPUTXT_IDX_SFT                    (5U)
#define HMIPUTXT_REM_MSK                    (0x1FU)
#define HMIPUTXT_ON_BIT                     (0x00000001U)

#define HMIPUTXT_FUEL_IDX                   (465U)
#define HMIPUTXT_ICEWRN_IDX                 (427U)
#define HMIPUTXT_OILMILRST_OK               (181U)
#define HMIPUTXT_OILMILRST_NG               (180U)
#define HMIPUTXT_TIMCHG_IDX                 (542U)
#define HMIPUTXT_FCTAHUD_IDX                (1087U)
#define HMIPUTXT_SFTALT_IDX                 (1266U)

#define HMIPUTXT_TASK_TIME                  (10U)
#define HMIPUTXT_HID_CNT_MAX                (6000U / HMIPUTXT_TASK_TIME)
#define HMIPUTXT_REQ_INIT                   (ALERT_REQ_UNKNOWN)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define HMIPUTXT_IDX_SFT                    (5U)

#define HMIPUTXT_REQBIT                     (1U)
#define HMIPUTXT_1BIT_SHIFT                 (1U)
#define HMIPUTXT_2BIT_SHIFT                 (2U)
#define HMIPUTXT_3BIT_SHIFT                 (3U)
#define HMIPUTXT_4BIT_SHIFT                 (4U)
#define HMIPUTXT_5BIT_SHIFT                 (5U)
#define HMIPUTXT_6BIT_SHIFT                 (6U)
#define HMIPUTXT_7BIT_SHIFT                 (7U)
#define HMIPUTXT_8BIT_SHIFT                 (8U)
#define HMIPUTXT_9BIT_SHIFT                 (9U)
#define HMIPUTXT_10BIT_SHIFT                (10U)
#define HMIPUTXT_11BIT_SHIFT                (11U)
#define HMIPUTXT_12BIT_SHIFT                (12U)

#define HMIPUTXT_TIMCHG_REQ_ON              (1U)
#define HMIPUTXT_FCTAHUD_REQ_ON             (1U)
#define HMIPUTXT_SFTALT_REQ_ON              (0U)

#define HMIPUTXT_TIMCHG_P_NCDSP_PLANINFO    (0x01U)
#define HMIPUTXT_TIMCHG_P_NCDSP_CHGNG       (0x02U)
#define HMIPUTXT_TIMCHG_P_NCDSP_CHGSTART    (0x03U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U2  u2_idx;
    U2  u2_chid;
    U1  u1_req;
    U2  u2_eso_ch;
}ST_HMIPUTXT_REQ_W_ESOPT;

typedef struct{
    U2                          u2_id;
    U2                          u2_eso_ch;
}ST_HMIPUTXT_ESOPT;

typedef struct{
    U2                          u2_id;
    U1                          u1_eso_result;
}ST_HMIPUTXT_DI_ESOPT;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_HmiPuTxtIdx2Mask(const U2 u2_a_PUTXTIDX , U1 * u1p_a_bufpos);
#if (HMIPUTXT_EVM_JDG == HMIPUTXT_JDG_ON)
static U2      u2_s_hmiputxt_evmod_cnt;
static U1      u1_s_hmiputxt_evmod_prereq;
#endif
#if (HMIPUTXT_THEVM_JDG == HMIPUTXT_JDG_ON)
static U2      u2_s_hmiputxt_thevm_cnt;
static U1      u1_s_hmiputxt_thevm_prereq;
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void           vd_s_HmiPuTxtCfgIGOffInit(void);
static void           vd_s_HmiPutTxtCfgSysmalMask(U4* u4_ap_varmask);
static void           vd_s_HmiPutTxtCfgGpfMidMask(U4* u4_ap_varmask);
static U1             u1_s_HmiPuTxtCfgTimchgReq(void);
static U1             u1_s_HmiPuTxtCfgFctahudReq(void);
static void           vd_s_HmiPuTxtCfgEvmReq(U4* u4_ap_req);
static U1             u1_s_HmiPuTxtCfgSftaltReq(void);
static void           vd_s_HmiPutTxtCfgLbwMask(U4* u4_ap_varmask);
/*===================================================================================================================================*/
/*  void    vd_g_HmiPuTxtCfgInit(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiPuTxtCfgInit(void)
{
#if (HMIPUTXT_EVM_JDG == HMIPUTXT_JDG_ON)
    u2_s_hmiputxt_evmod_cnt       = (U2)U2_MAX;
    u1_s_hmiputxt_evmod_prereq = (U1)HMIPUTXT_REQ_INIT;
#endif
#if (HMIPUTXT_THEVM_JDG == HMIPUTXT_JDG_ON)
    u2_s_hmiputxt_thevm_cnt       = (U2)U2_MAX;
    u1_s_hmiputxt_thevm_prereq = (U1)HMIPUTXT_REQ_INIT;
#endif

}
/*===================================================================================================================================*/
/*  static void    vd_s_HmiPuTxtCfgIGoffInit(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_HmiPuTxtCfgIGOffInit(void)
{
#if (HMIPUTXT_EVM_JDG == HMIPUTXT_JDG_ON)
    u2_s_hmiputxt_evmod_cnt       = (U2)U2_MAX;
    u1_s_hmiputxt_evmod_prereq = (U1)HMIPUTXT_REQ_INIT;
#endif
#if (HMIPUTXT_THEVM_JDG == HMIPUTXT_JDG_ON)
    u2_s_hmiputxt_thevm_cnt       = (U2)U2_MAX;
    u1_s_hmiputxt_thevm_prereq = (U1)HMIPUTXT_REQ_INIT;
#endif

}
/*===================================================================================================================================*/
/*  void    vd_g_HmiPuTxtCfgReq(U4 * u4_ap_req)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiPuTxtCfgReq(U4 * u4_ap_req)
{
    static const ST_HMIPUTXT_REQ_W_ESOPT   st_sp_HMIPUTXT_REQ_W_ESOPT[] = {
        /*  u2_idx    u2_chid                      u1_req                                   u2_eso_ch             */
        {   (U2)331U, (U2)ALERT_CH_S_ADAFRO_PD,    (U1)ALERT_REQ_S_ADAFRO_PD_MLFNC,         (U2)U2_MAX           }     /* WARNING_ID_331 */
    };

    static const ST_HMIPUTXT_REQ_W_ESOPT   st_sp_HMIPUTXT_REQ_W_ESOPT_WNG0786[] = {
        /*  u2_idx    u2_chid                      u1_req                                   u2_eso_ch             */
        {   (U2)786U, (U2)ALERT_CH_B_LEDHEA,       (U1)ALERT_REQ_B_LEDHEA_MALFUNC,          (U2)U2_MAX           },    /* WARNING_ID_786 */
        {   (U2)786U, (U2)ALERT_CH_S_HEALEV_PD,    (U1)ALERT_REQ_S_HEALEV_PD_MALFUNC,       (U2)U2_MAX           },    /* WARNING_ID_786 */
        {   (U2)786U, (U2)ALERT_CH_S_MWL_PD,       (U1)ALERT_REQ_S_MWL_PD_MALFUNC,          (U2)VDF_ESO_CH_MWL   }     /* WARNING_ID_786 */
    };

    U2              u2_t_num_reqbit;
    U4              u4_t_loop;
    U1              u1_t_sts;
    U2              u2_t_blkpos;
    U2              u2_t_bitpos;
    U4              u4_t_num_tbl;
    U2              u2_t_chid;
    U1              u1_t_req;
    U1              u1_t_exist;
    U1              u1_t_icewrn;
    U1              u1_t_oilrststs;
    U1              u1_t_timchg;
    U1              u1_t_fctahud;
    U1              u1_t_sftalt;

    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)HMIPUTXT_NWORD; u4_t_loop++ ){
        u4_ap_req[u4_t_loop] = (U4)0U;
    }

    /* Alert */
    u2_t_num_reqbit = u2_g_HmiputxtSizeReqbit();
    vd_g_AlertReqToBit(st_gp_HMIPUTXTREQBIT, u2_t_num_reqbit, u4_ap_req, (U1)HMIPUTXT_NWORD);

    /*  LoFuel  */
#if 0   /* BEV BSW provisionally */
    u1_t_sts = u1_g_FuelvolTauLwAct();
#else
    u1_t_sts = (U1)FALSE;
#endif
    if(u1_t_sts == (U1)TRUE){
        u2_t_blkpos             = (U2)HMIPUTXT_FUEL_IDX >> HMIPUTXT_IDX_SFT;
        u2_t_bitpos             = (U2)HMIPUTXT_FUEL_IDX &  (U2)HMIPUTXT_REM_MSK;
        u4_ap_req[u2_t_blkpos] |= ((U4)HMIPUTXT_ON_BIT << u2_t_bitpos);
    }

    /* IceWrn */
    u1_t_icewrn = u1_g_AmbtmpIcyraWrnAct();
    if(u1_t_icewrn == (U1)TRUE){
        u2_t_blkpos             = (U2)HMIPUTXT_ICEWRN_IDX >> HMIPUTXT_IDX_SFT;
        u2_t_bitpos             = (U2)HMIPUTXT_ICEWRN_IDX &  (U2)HMIPUTXT_REM_MSK;
        u4_ap_req[u2_t_blkpos] |= ((U4)HMIPUTXT_ON_BIT << u2_t_bitpos);
    }

    /* Oilmil */
    u1_t_oilrststs = u1_g_OilmilGetRstSts();
    if(u1_t_oilrststs == (U1)OILMIL_RSTSTS_COMP) {
        u2_t_blkpos = (U2)HMIPUTXT_OILMILRST_OK >> HMIPUTXT_IDX_SFT;
        u2_t_bitpos = (U2)HMIPUTXT_OILMILRST_OK & (U2)HMIPUTXT_REM_MSK;
        u4_ap_req[u2_t_blkpos] |= ((U4)HMIPUTXT_ON_BIT << u2_t_bitpos);
    }
    else if (u1_t_oilrststs == (U1)OILMIL_RSTSTS_FAIL) {
        u2_t_blkpos = (U2)HMIPUTXT_OILMILRST_NG >> HMIPUTXT_IDX_SFT;
        u2_t_bitpos = (U2)HMIPUTXT_OILMILRST_NG & (U2)HMIPUTXT_REM_MSK;
        u4_ap_req[u2_t_blkpos] |= ((U4)HMIPUTXT_ON_BIT << u2_t_bitpos);
    }
    else {
        /* Do Nothing */
    }

    /* Timchg */
    u1_t_timchg = u1_s_HmiPuTxtCfgTimchgReq();
    if(u1_t_timchg == (U1)TRUE){
        u2_t_blkpos             = (U2)HMIPUTXT_TIMCHG_IDX >> HMIPUTXT_IDX_SFT;
        u2_t_bitpos             = (U2)HMIPUTXT_TIMCHG_IDX &  (U2)HMIPUTXT_REM_MSK;
        u4_ap_req[u2_t_blkpos] |= ((U4)HMIPUTXT_ON_BIT << u2_t_bitpos);
    }

    /* FCTA(HUD) */
    u1_t_fctahud = u1_s_HmiPuTxtCfgFctahudReq();
    if(u1_t_fctahud == (U1)TRUE){
        u2_t_blkpos             = (U2)HMIPUTXT_FCTAHUD_IDX >> HMIPUTXT_IDX_SFT;
        u2_t_bitpos             = (U2)HMIPUTXT_FCTAHUD_IDX &  (U2)HMIPUTXT_REM_MSK;
        u4_ap_req[u2_t_blkpos] |= ((U4)HMIPUTXT_ON_BIT << u2_t_bitpos);
    }

    /* Sftalt */
    u1_t_sftalt = u1_s_HmiPuTxtCfgSftaltReq();
    if (u1_t_sftalt == (U1)TRUE){
        u2_t_blkpos             = (U2)HMIPUTXT_SFTALT_IDX >> HMIPUTXT_IDX_SFT;
        u2_t_bitpos             = (U2)HMIPUTXT_SFTALT_IDX &  (U2)HMIPUTXT_REM_MSK;
        u4_ap_req[u2_t_blkpos] |= ((U4)HMIPUTXT_ON_BIT << u2_t_bitpos);
    }

    /* Evmod */
    vd_s_HmiPuTxtCfgEvmReq(&u4_ap_req[0]);

    u4_t_num_tbl = sizeof(st_sp_HMIPUTXT_REQ_W_ESOPT) / sizeof(st_sp_HMIPUTXT_REQ_W_ESOPT[0]);
    for(u4_t_loop = (U4)0U; u4_t_loop < u4_t_num_tbl; u4_t_loop++){
        u1_t_exist = (U1)TRUE;
        if(st_sp_HMIPUTXT_REQ_W_ESOPT[u4_t_loop].u2_eso_ch < (U2)VDF_ESO_NUM_CH){
            u1_t_exist = u1_g_VardefEsOptAvaByCh(st_sp_HMIPUTXT_REQ_W_ESOPT[u4_t_loop].u2_eso_ch);
        }
        if(u1_t_exist == (U1)TRUE){
            u2_t_chid  = st_sp_HMIPUTXT_REQ_W_ESOPT[u4_t_loop].u2_chid;
            u1_t_req    = u1_g_AlertReqByCh(u2_t_chid);
            if(u1_t_req == st_sp_HMIPUTXT_REQ_W_ESOPT[u4_t_loop].u1_req){
                u2_t_blkpos = (U2)(st_sp_HMIPUTXT_REQ_W_ESOPT[u4_t_loop].u2_idx >>     HMIPUTXT_IDX_SFT);
                u2_t_bitpos = (U2)(st_sp_HMIPUTXT_REQ_W_ESOPT[u4_t_loop].u2_idx &  (U2)HMIPUTXT_REM_MSK);
                if(u2_t_blkpos < (U2)HMIPUTXT_NWORD){
                    u4_ap_req[u2_t_blkpos] |= ((U4)HMIPUTXT_ON_BIT << u2_t_bitpos);
                }
            }
        }
    }

    /* WARNING_ID_786 */
    u4_t_num_tbl = sizeof(st_sp_HMIPUTXT_REQ_W_ESOPT_WNG0786) / sizeof(st_sp_HMIPUTXT_REQ_W_ESOPT_WNG0786[0]);
    for (u4_t_loop = (U4)0U; u4_t_loop < u4_t_num_tbl; u4_t_loop++) {
        u1_t_exist = (U1)TRUE;
        if (st_sp_HMIPUTXT_REQ_W_ESOPT_WNG0786[u4_t_loop].u2_eso_ch < (U2)VDF_ESO_NUM_CH) {
            u1_t_exist = u1_g_VardefEsOptAvaByCh(st_sp_HMIPUTXT_REQ_W_ESOPT_WNG0786[u4_t_loop].u2_eso_ch);
        }
        if (u1_t_exist == (U1)TRUE) {
            u2_t_chid = st_sp_HMIPUTXT_REQ_W_ESOPT_WNG0786[u4_t_loop].u2_chid;
            u1_t_req = u1_g_AlertReqByCh(u2_t_chid);
            if (u1_t_req == st_sp_HMIPUTXT_REQ_W_ESOPT_WNG0786[u4_t_loop].u1_req) {
                u2_t_blkpos = (U2)(st_sp_HMIPUTXT_REQ_W_ESOPT_WNG0786[u4_t_loop].u2_idx >> HMIPUTXT_IDX_SFT);
                u2_t_bitpos = (U2)(st_sp_HMIPUTXT_REQ_W_ESOPT_WNG0786[u4_t_loop].u2_idx & (U2)HMIPUTXT_REM_MSK);
                if (u2_t_blkpos < (U2)HMIPUTXT_NWORD) {
                    u4_ap_req[u2_t_blkpos] |= ((U4)HMIPUTXT_ON_BIT << u2_t_bitpos);
                }
            }
        }
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_HmiPuTxtCfgDetail(U2 * u2_ap_detail)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiPuTxtCfgDetail(U2 * u2_ap_detail)
{
#if (HMIPUTXT_SYSMAL_JDG == HMIPUTXT_JDG_ON)
    U1 u1_t_sysmal_req;    /* sysmal request */
    U2 u2_t_reqpos;        /* request position */

    u1_t_sysmal_req = (U1)0U;
    u2_t_reqpos = (U2)0U;
    u1_t_sysmal_req = u1_g_AlertReqByCh((U2)ALERT_CH_H_SYSMAL_PD1);

    switch (u1_t_sysmal_req) {
        case (U1)ALERT_REQ_H_SYSMAL_PD1_MALPAT1:
            u2_t_reqpos = (U2)HMIPUTXT_REQBIT;
            break;
        case (U1)ALERT_REQ_H_SYSMAL_PD1_MALPAT3:
            u2_t_reqpos = (U2)HMIPUTXT_REQBIT << HMIPUTXT_2BIT_SHIFT;
            break;
        case (U1)ALERT_REQ_H_SYSMAL_PD1_MALPAT4:
            u2_t_reqpos = (U2)HMIPUTXT_REQBIT << HMIPUTXT_3BIT_SHIFT;
            break;
        case (U1)ALERT_REQ_H_SYSMAL_PD1_MALPAT5:
            u2_t_reqpos = (U2)HMIPUTXT_REQBIT << HMIPUTXT_4BIT_SHIFT;
            break;
        case (U1)ALERT_REQ_H_SYSMAL_PD1_MALPAT6:
            u2_t_reqpos = (U2)HMIPUTXT_REQBIT << HMIPUTXT_5BIT_SHIFT;
            break;
        case (U1)ALERT_REQ_H_SYSMAL_PD1_MALPAT7:
            u2_t_reqpos = (U2)HMIPUTXT_REQBIT << HMIPUTXT_6BIT_SHIFT;
            break;
        case (U1)ALERT_REQ_H_SYSMAL_PD1_MALPAT8:
            u2_t_reqpos = (U2)HMIPUTXT_REQBIT << HMIPUTXT_7BIT_SHIFT;
            break;
        case (U1)ALERT_REQ_H_SYSMAL_PD1_MALPAT9:
            u2_t_reqpos = (U2)HMIPUTXT_REQBIT << HMIPUTXT_8BIT_SHIFT;
            break;
        case (U1)ALERT_REQ_H_SYSMAL_PD1_MALPAT10:
            u2_t_reqpos = (U2)HMIPUTXT_REQBIT << HMIPUTXT_9BIT_SHIFT;
            break;
        case (U1)ALERT_REQ_H_SYSMAL_PD1_MALPAT11:
            u2_t_reqpos = (U2)HMIPUTXT_REQBIT << HMIPUTXT_10BIT_SHIFT;
            break;
        case (U1)ALERT_REQ_H_SYSMAL_PD1_MALPAT12:
            u2_t_reqpos = (U2)HMIPUTXT_REQBIT << HMIPUTXT_11BIT_SHIFT;
            break;
        case (U1)ALERT_REQ_H_SYSMAL_PD1_MALPAT13:
            u2_t_reqpos = (U2)HMIPUTXT_REQBIT << HMIPUTXT_12BIT_SHIFT;
            break;
        default:
            /* Do Nothing */
            break;
    }

    u2_ap_detail[0] = u2_t_reqpos;
#else
    u2_ap_detail[0] = (U2)0U;
#endif

}

/*===================================================================================================================================*/
/*  void    vd_g_HmiPuTxtCfgVarmask(U4 * u4_ap_varmask)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiPuTxtCfgVarmask(U4 * u4_ap_varmask)
{
    static const ST_HMIPUTXT_ESOPT st_sp_HMIPUTXT_ESOPT[] = {
        {    (U2)52U,     (U2)VDF_ESO_CH_EPB      },
        {    (U2)70U,     (U2)VDF_ESO_CH_ECB      },
        {    (U2)278U,    (U2)VDF_ESO_CH_SBW      },
        {    (U2)308U,    (U2)VDF_ESO_CH_DSC      },
        {    (U2)314U,    (U2)VDF_ESO_CH_AUTOP    },
        {    (U2)394U,    (U2)VDF_ESO_CH_OILMNT   },
        {    (U2)539U,    (U2)VDF_ESO_CH_OILMNT   },
        {    (U2)597U,    (U2)VDF_ESO_CH_AVSEXT   },
        {    (U2)678U,    (U2)VDF_ESO_CH_BRPADW   },
        {    (U2)685U,    (U2)VDF_ESO_CH_AVSEXT   },
        {    (U2)1025U,   (U2)VDF_ESO_CH_PEDPRO   },
        {    (U2)1179U,   (U2)VDF_ESO_CH_DRS      }
    };

    static const U2 u2_s_HMIPUTXT_ID_T120 = (U2)306U;
    static const U2 u2_s_HMIPUTXT_ID_TMNT_15 = (U2)486U;
    static const U2 u2_s_HMIPUTXT_ID_TMNT_16 = (U2)386U;
    static const U2 u2_s_HMIPUTXT_ID_PKBWAR = (U2)1107U;

    U1              u1_t_dest;
    U1              u1_t_bufpos;
    U4              u4_t_mask;
    U4              u4_t_loop;
    U4              u4_t_num;
    U1              u1_t_exist;
    U1              u1_t_tmnt;
    U1              u1_t_pkbwar;

    /* Esopt*/  
    u4_t_num = (U4)(sizeof(st_sp_HMIPUTXT_ESOPT) / sizeof(st_sp_HMIPUTXT_ESOPT[0]));
    for(u4_t_loop = (U4)0U ; u4_t_loop < u4_t_num ; u4_t_loop++){
        u1_t_exist = u1_g_VardefEsOptAvaByCh(st_sp_HMIPUTXT_ESOPT[u4_t_loop].u2_eso_ch);
        if(u1_t_exist == (U1)0U){
            u1_t_bufpos = (U1)0U;
            u4_t_mask   = u4_s_HmiPuTxtIdx2Mask(st_sp_HMIPUTXT_ESOPT[u4_t_loop].u2_id , &u1_t_bufpos);
            u4_ap_varmask[u1_t_bufpos] &= u4_t_mask;
        }
    }

    /* PKBWAR */
     u1_t_pkbwar = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_EPB);
        if(u1_t_pkbwar == (U1)TRUE){
        u1_t_bufpos = (U1)0U;
        u4_t_mask   = u4_s_HmiPuTxtIdx2Mask(u2_s_HMIPUTXT_ID_PKBWAR, &u1_t_bufpos);
        u4_ap_varmask[u1_t_bufpos] &= u4_t_mask;
    }

    /* T120 */
    u1_t_dest = u1_g_VardefMdlLEstWrnByPid();
    if(u1_t_dest == (U1)FALSE){
        u1_t_bufpos = (U1)0U;
        u4_t_mask   = u4_s_HmiPuTxtIdx2Mask(u2_s_HMIPUTXT_ID_T120, &u1_t_bufpos);
        u4_ap_varmask[u1_t_bufpos] &= u4_t_mask;
    }

    /* TMNT */
    u1_t_tmnt = u1_g_VardefTmntOpt();
    if(u1_t_tmnt == (U1)FALSE){
        u1_t_bufpos = (U1)0U;
        u4_t_mask   = u4_s_HmiPuTxtIdx2Mask(u2_s_HMIPUTXT_ID_TMNT_15, &u1_t_bufpos);
        u4_ap_varmask[u1_t_bufpos] &= u4_t_mask;

        u1_t_bufpos = (U1)0U;
        u4_t_mask   = u4_s_HmiPuTxtIdx2Mask(u2_s_HMIPUTXT_ID_TMNT_16, &u1_t_bufpos);
        u4_ap_varmask[u1_t_bufpos] &= u4_t_mask;
    }

    /* SYSMAL */
    vd_s_HmiPutTxtCfgSysmalMask(&u4_ap_varmask[0]);
    /* GPF(MID) */
    vd_s_HmiPutTxtCfgGpfMidMask(&u4_ap_varmask[0]);
    /* LBW */
    vd_s_HmiPutTxtCfgLbwMask(&u4_ap_varmask[0]);

}

/*===================================================================================================================================*/
/*  static U4     u4_s_HmiPuTxtIdx2Mask(const U2 u2_a_PUTXTIDX , U1 * u1p_a_bufpos)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4     u4_s_HmiPuTxtIdx2Mask(const U2 u2_a_PUTXTIDX , U1 * u1p_a_bufpos)
{
    U2   u2_t_bufpos;
    U2   u2_t_bitpos;
    U4   u4_t_mask;

    u2_t_bufpos = (U2)(u2_a_PUTXTIDX >> HMIPUTXT_IDX_SFT);
    if(u2_t_bufpos < (U2)HMIPUTXT_NUM){
        *u1p_a_bufpos = (U1)u2_t_bufpos;
        u2_t_bitpos   = (U2)(u2_a_PUTXTIDX &  (U2)HMIPUTXT_REM_MSK);
        u4_t_mask     = (U4)U4_MAX ^ ((U4)HMIPUTXT_ON_BIT << u2_t_bitpos);
    }
    else{
        *u1p_a_bufpos = (U1)0U;
        u4_t_mask     = (U4)U4_MAX;
    }
    return(u4_t_mask);
}

/*===================================================================================================================================*/
/*  static void    vd_s_HmiPutTxtCfgSysmalMask(U4 * u4_ap_varmask)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      * u4_ap_varmask : mask array                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_HmiPutTxtCfgSysmalMask(U4* u4_ap_varmask) {
#if (HMIPUTXT_SYSMAL_JDG == HMIPUTXT_JDG_ON)
    static const U2 u2_sp_HMIPUTXT_SYSMAL[] = {
        (U2)95U,
        (U2)96U,
        (U2)97U,
        (U2)101U,
        (U2)104U,
        (U2)105U,
        (U2)144U,
        (U2)293U,
        (U2)296U,
        (U2)297U,
        (U2)298U,
        (U2)299U,
        (U2)300U,
        (U2)301U,
        (U2)343U,
        (U2)358U,
        (U2)376U
    };

    U4              u4_t_num;
    U1              u1_t_bufpos;
    U4              u4_t_mask;
    U4              u4_t_loop;
    U1              u1_t_sysmal_req;

    u4_t_num = (U4)(sizeof(u2_sp_HMIPUTXT_SYSMAL) / sizeof(u2_sp_HMIPUTXT_SYSMAL[0]));
    u1_t_sysmal_req = u1_g_AlertReqByCh((U2)ALERT_CH_H_SYSMAL_PD1);

    if (u1_t_sysmal_req == (U1)HMIPUTXT_REQ_INIT) {
        for (u4_t_loop = (U4)0U; u4_t_loop < u4_t_num; u4_t_loop++) {
            u1_t_bufpos = (U1)0U;
            u4_t_mask = u4_s_HmiPuTxtIdx2Mask(u2_sp_HMIPUTXT_SYSMAL[u4_t_loop], &u1_t_bufpos);
            u4_ap_varmask[u1_t_bufpos] &= u4_t_mask;
        }
    }
#endif
}

/*===================================================================================================================================*/
/*===================================================================================================================================*/
/*  static void    vd_s_HmiPutTxtCfgGpfMidMask(U4 * u4_ap_varmask)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      * u4_ap_varmask : mask array                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_HmiPutTxtCfgGpfMidMask(U4* u4_ap_varmask) {
    static const U2 u2_sp_HMIPUTXT_GPFMID[] = {
        (U2)1112U,
        (U2)1175U,
        (U2)1193U,
        (U2)1195U
    };

    U4              u4_t_num;
    U1              u1_t_bufpos;
    U4              u4_t_mask;
    U4              u4_t_loop;
    U1              u1_t_exist;

    u4_t_num = (U4)(sizeof(u2_sp_HMIPUTXT_GPFMID) / sizeof(u2_sp_HMIPUTXT_GPFMID[0]));
    u1_t_exist = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_GPF);

    if (u1_t_exist == (U1)TRUE) {
        for (u4_t_loop = (U4)0U; u4_t_loop < u4_t_num; u4_t_loop++) {
            u1_t_bufpos = (U1)0U;
            u4_t_mask = u4_s_HmiPuTxtIdx2Mask(u2_sp_HMIPUTXT_GPFMID[u4_t_loop], &u1_t_bufpos);
            u4_ap_varmask[u1_t_bufpos] &= u4_t_mask;
        }
    }
}

/*===================================================================================================================================*/
/*  static void    vd_s_HmiPuTxtCfgEvmReq(U4 * u4_ap_req)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      * u4_ap_req : mask array                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_HmiPuTxtCfgEvmReq(U4 * u4_ap_req)
{
#if (HMIPUTXT_EVM_JDG == HMIPUTXT_JDG_ON)
    static const U2 u2_sp_HMIPUTXT_EVMOD[] = {
        (U2)521U,
        (U2)522U,
        (U2)523U,
        (U2)524U,
        (U2)525U,
        (U2)526U,
        (U2)527U,
        (U2)528U,
        (U2)529U
    };

    U4              u4_t_num;
    U1              u1_t_evmod_reqid;
    U1              u1_t_igsts;
    U2              u2_t_blkpos;
    U2              u2_t_bitpos;
    U4              u4_t_loop;

    u1_t_igsts = u1_g_VehopemdIgnOn();
    if(u1_t_igsts == (U1)TRUE) {

        if(u2_s_hmiputxt_evmod_cnt < (U2)U2_MAX) {
            u2_s_hmiputxt_evmod_cnt++;
        }

        u4_t_num = (U4)(sizeof(u2_sp_HMIPUTXT_EVMOD) / sizeof(u2_sp_HMIPUTXT_EVMOD[0]));
        u1_t_evmod_reqid = u1_g_AlertReqByCh((U2)ALERT_CH_H_EVMOD_PD);

        if(u1_t_evmod_reqid != (U1)HMIPUTXT_REQ_INIT){
            if(u1_t_evmod_reqid != u1_s_hmiputxt_evmod_prereq){
                u2_s_hmiputxt_evmod_cnt = (U2)0U;
            }
            u1_s_hmiputxt_evmod_prereq = u1_t_evmod_reqid;
        }

        if((u2_s_hmiputxt_evmod_cnt <= (U2)HMIPUTXT_HID_CNT_MAX) && 
            (u1_t_evmod_reqid != (U1)ALERT_REQ_H_EVMOD_PD_OFF) &&
            (u1_s_hmiputxt_evmod_prereq < (U1)u4_t_num)) {
                u2_t_blkpos             = u2_sp_HMIPUTXT_EVMOD[u1_s_hmiputxt_evmod_prereq] >> HMIPUTXT_IDX_SFT;
                u2_t_bitpos             = u2_sp_HMIPUTXT_EVMOD[u1_s_hmiputxt_evmod_prereq] &  (U2)HMIPUTXT_REM_MSK;
                u4_ap_req[u2_t_blkpos] |= ((U4)HMIPUTXT_ON_BIT << u2_t_bitpos);
        }
        else {
            if(u1_t_evmod_reqid == (U1)HMIPUTXT_REQ_INIT) {
                u1_s_hmiputxt_evmod_prereq = u1_t_evmod_reqid;
            }
            u2_s_hmiputxt_evmod_cnt = (U2)U2_MAX;

            for (u4_t_loop = (U4)0U; u4_t_loop < u4_t_num; u4_t_loop++){
                u2_t_blkpos             = u2_sp_HMIPUTXT_EVMOD[u4_t_loop] >> HMIPUTXT_IDX_SFT;
                u2_t_bitpos             = u2_sp_HMIPUTXT_EVMOD[u4_t_loop] &  (U2)HMIPUTXT_REM_MSK;
                u4_ap_req[u2_t_blkpos]  &= ~((U4)HMIPUTXT_ON_BIT << u2_t_bitpos);
            }
        }

    }else{
        vd_s_HmiPuTxtCfgIGOffInit();
    }

#else
    /* Do Nothing */
#endif

}

/*===================================================================================================================================*/
/*  void    vd_g_HmiPuTxtCfgThevmHidmask(U4 * u4_ap_varmask)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      * u4_ap_varmask : mask array                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiPuTxtCfgThevmHidmask(U4 * u4_ap_varmask)
{
#if (HMIPUTXT_THEVM_JDG == HMIPUTXT_JDG_ON)
    static const U2 u2_sp_HMIPUTXT_THEVM[] = {
        (U2)166U,
        (U2)202U,
        (U2)205U,
        (U2)206U,
        (U2)207U
    };

    U1              u1_t_bufpos;
    U4              u4_t_mask;
    U4              u4_t_loop;
    U4              u4_t_num;
    U1              u1_t_thevm_reqid;
    U1              u1_t_igsts;

    u1_t_igsts = u1_g_VehopemdIgnOn();
    if (u1_t_igsts == (U1)TRUE) {

        if (u2_s_hmiputxt_thevm_cnt < (U2)U2_MAX) {
            u2_s_hmiputxt_thevm_cnt++;
        }

        u4_t_num = (U4)(sizeof(u2_sp_HMIPUTXT_THEVM) / sizeof(u2_sp_HMIPUTXT_THEVM[0]));
        u1_t_thevm_reqid = u1_g_AlertReqByCh((U2)ALERT_CH_H_THEVM_PD);

        if(u1_t_thevm_reqid != (U1)HMIPUTXT_REQ_INIT){
            if(u1_t_thevm_reqid != u1_s_hmiputxt_thevm_prereq) {
                u2_s_hmiputxt_thevm_cnt = (U2)0U;
            }
        }

        if((u2_s_hmiputxt_thevm_cnt > (U2)HMIPUTXT_HID_CNT_MAX)  ||
           (u1_t_thevm_reqid == (U1)ALERT_REQ_H_THEVM_PD_OFF  )) {
            for(u4_t_loop = (U4)0U ; u4_t_loop < u4_t_num ; u4_t_loop++){
                u1_t_bufpos = (U1)0U;
                u4_t_mask   = u4_s_HmiPuTxtIdx2Mask(u2_sp_HMIPUTXT_THEVM[u4_t_loop], &u1_t_bufpos);
                u4_ap_varmask[u1_t_bufpos] &= u4_t_mask;
            }
            u2_s_hmiputxt_thevm_cnt = (U2)U2_MAX;
        }
        u1_s_hmiputxt_thevm_prereq = u1_t_thevm_reqid;

    }
    else {
        vd_s_HmiPuTxtCfgIGOffInit();
    }

#else
    /* Do Nothing */
#endif

}

/*===================================================================================================================================*/
/*  static U1 u1_s_HmiPuTxtCfgTimchgReq(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         Request (TRUE / FALSE)                                                                                           */
/*===================================================================================================================================*/
static U1 u1_s_HmiPuTxtCfgTimchgReq(void)
{
#if (HMIPUTXT_TIMCHG_JDG == HMIPUTXT_JDG_ON)
    U1 u1_t_ret;             /* Requeset       */
    U1 u1_t_igon;            /* IG-ON State    */
    U1 u1_t_baon;            /* BA-ON State    */
    U1 u1_t_msgsts;          /* Message State  */
    U1 u1_t_signal;          /* Signal Varlue  */
    U1 u1_t_timchg_pncdsp;   /* P_NCDSPVarlue  */

    u1_t_igon = u1_g_VehopemdIgnOn();
    u1_t_baon = u1_g_VehopemdPbaOn();
    u1_t_timchg_pncdsp = (U1)0U;

    u1_t_msgsts = (U1)Com_GetIPDUStatus(MSG_PLG1G10_RXCH0);
    u1_t_msgsts &= (U1)(COM_TIMEOUT | COM_NO_RX);
    u1_t_signal = (U1)0U;
    if(u1_t_msgsts == (U1)0x00U){
        (void)Com_ReceiveSignal(ComConf_ComSignal_PSDSPRQ, &u1_t_signal);
    }

    u1_t_timchg_pncdsp = (U1)u2_g_EvschgGetSignal((U1)EVSCHG_ID_P_NCDSP);

    u1_t_ret = (U1)FALSE;
    if((u1_t_igon == (U1)FALSE) &&
       (u1_t_baon == (U1)TRUE ))  {
        if(u1_t_signal == (U1)HMIPUTXT_TIMCHG_REQ_ON){
            switch(u1_t_timchg_pncdsp)
            {
                case (U1)HMIPUTXT_TIMCHG_P_NCDSP_PLANINFO:                        /* P_NCDSP=01b */
                case (U1)HMIPUTXT_TIMCHG_P_NCDSP_CHGSTART:                        /* P_NCDSP=11b */
                    u1_t_ret = (U1)TRUE;
                    break;
                default:
                    /* Do Nothing */
                    break;
            }
        }
    }

    return(u1_t_ret);
#else
    return((U1)FALSE);
#endif
}
/*===================================================================================================================================*/
/*  static U1 u1_s_HmiPuTxtCfgFctahudReq(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         Request (TRUE / FALSE)                                                                                           */
/*===================================================================================================================================*/
static U1 u1_s_HmiPuTxtCfgFctahudReq(void)
{
    U1 u1_t_ret;             /* Requeset       */
    U1 u1_t_igon;            /* IG-ON State    */
    U1 u1_t_msgsts;          /* Message State  */
    U1 u1_t_ctahr_sig;       /* Signal Varlue  */
    U1 u1_t_ctahl_sig;       /* Signal Varlue  */

    u1_t_igon = u1_g_VehopemdIgnOn();
    u1_t_ctahr_sig = (U1)0U;
    u1_t_ctahl_sig = (U1)0U;

    u1_t_msgsts = (U1)Com_GetIPDUStatus(MSG_DS11S40_RXCH0);
    u1_t_msgsts &= (U1)(COM_TIMEOUT | COM_NO_RX);

    if(u1_t_msgsts == (U1)0x00U){
        (void)Com_ReceiveSignal(ComConf_ComSignal_CTAHR, &u1_t_ctahr_sig);
        (void)Com_ReceiveSignal(ComConf_ComSignal_CTAHL, &u1_t_ctahl_sig);
    }

    u1_t_ret = (U1)FALSE;
    if(u1_t_igon == (U1)TRUE){
        if((u1_t_ctahr_sig == (U1)HMIPUTXT_FCTAHUD_REQ_ON) ||
           (u1_t_ctahl_sig == (U1)HMIPUTXT_FCTAHUD_REQ_ON)) {
            u1_t_ret = (U1)TRUE;
        }
    }

    return(u1_t_ret);

}

/*===================================================================================================================================*/
/*  static U1 u1_s_HmiPuTxtCfgSftaltReq(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         Request (TRUE / FALSE)                                                                                           */
/*===================================================================================================================================*/
static U1 u1_s_HmiPuTxtCfgSftaltReq(void)
{
    U1 u1_t_ret;             /* Request       */
    U1 u1_t_igon;            /* IG-ON State    */
    U1 u1_t_calib_jdg;       /* Calib Value   */

    u1_t_igon = u1_g_VehopemdIgnOn();

    u1_t_ret = (U1)FALSE;
    if(u1_t_igon == (U1)TRUE){
        u1_t_calib_jdg = u1_CALIB_MCUID0797_CNST_WRITEFLG;
        if(u1_t_calib_jdg == (U1)HMIPUTXT_SFTALT_REQ_ON){
            u1_t_ret = (U1)TRUE;
        }
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  void    vd_g_HmiPuTxtCfgCstmask(U4 * u4_ap_varmask)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      * u4_ap_varmask : mask array                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiPuTxtCfgCstmask(U4 * u4_ap_varmask)
{
}
/*===================================================================================================================================*/
/*  static  void    vd_s_HmiPuTxtCfgLbwMask(U4 * u4_ap_req)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_HmiPutTxtCfgLbwMask(U4* u4_ap_varmask)
{
    U1  u1_t_ptsys;
    U1  u1_t_bufpos;
    U4  u4_t_mask;

    static const U2 u2_s_HMIPUTXT_ID_LBW = (U2)873U;

    u1_t_ptsys = u1_g_VardefPtsRxRim();
    if (
           (u1_t_ptsys == (U1)VDF_PTS_RX_05_ELE_BAT) ||
           (u1_t_ptsys == (U1)VDF_PTS_RX_1F_NRX)
        )

    {
        /* Do nothing*/
    }
    else
    {
        u1_t_bufpos = (U1)0U; 
        u4_t_mask = u4_s_HmiPuTxtIdx2Mask(u2_s_HMIPUTXT_ID_LBW, &u1_t_bufpos);
        u4_ap_varmask[u1_t_bufpos] &= u4_t_mask;
    }
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    07/16/2017  TA       New.                                                                                               */
/*  1.1.0    04/21/2020  TH       Setting for 800B CV.                                                                               */
/*  1.2.0    09/09/2020  TH       Setting for 800B CV-R.                                                                             */
/*  1.3.0    01/06/2021  TH       Setting for 800B 1A.                                                                               */
/*  1.4.0    06/04/2021  TH       Setting for 22-24FGM CV.                                                                           */
/*  1.6.0    10/25/2024  RS       Setting for BEV System_Consideration_1                                                             */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/*  19PFv3-1 02/14/2024  DR       Update for 19PFv3 TIMCHG                                                                           */
/*  19PFv3-2 02/26/2024  DR       Update TMNT function presence interface                                                            */
/*  19PFv3-3 04/23/2024  TR       Deleted Icon Varation Mask Function of PSSDI, RSRDI and FCMDI                                      */
/*                                Deleted ADAHIG and AUTHIG function presence config for WARNING_ID_331                              */
/*  19PFv3-4 05/15/2024  KH       Added SFTALT function                                                                              */
/*  19PFv3-5 05/17/2024  PG       Deleted PROSRV process                                                                             */
/*  19PFv3-6 06/21/2024  JMH      Added LBW Mask Function                                                                            */
/*  19PFv3-7 07/04/2024  TN       Delete Calibration Guard Process.                                                                  */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*  * TA   = Teruyuki Anjima, Denso                                                                                                  */
/*  * TH   = Takahiro Hirano, Denso Techno                                                                                           */
/*  * DR   = Dyan Reyes, DTPH                                                                                                        */
/*  * TR   = Tebs Ramos, DTPH                                                                                                        */
/*  * KH   = Kiko Huerte, DTPH                                                                                                       */
/*  * PG   = Patrick Garcia, DTPH                                                                                                    */
/*  * JMH  = James Michael D. Hilarion, DTPH                                                                                         */
/*  * TN   = Tetsushi Nakano, Denso Techno                                                                                           */
/*  * RS   = Ryuki Sako,      Denso Techno                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/
