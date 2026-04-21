/* 1.0.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Diagnosis on Can for Toyota MET/HUD based on AUBIST/DEM, DCM                                                                     */
/*  SID 0x22/0x2E/0x2F/0x31 DataIdentifer and Routine Identifer                                                                      */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDOCAN_XID_CFG_C_MAJOR                  (1U)
#define OXDOCAN_XID_CFG_C_MINOR                  (0U)
#define OXDOCAN_XID_CFG_C_PATCH                  (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oxdocan_cfg_private.h"
#include "oxdocan_xid_cfg_private.h"

/* #include "nvmc_mgr.h"             nvmc_mgr.h is included in oxdocan_cfg_private.h              */
/* #include "oxcan.h"                oxcan.h is included in oxdocan_cfg_private.h                 */

#include "tydocan_xid_ma_cfg_private.h"

/* Application Headers */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (OXDOCAN_XID_CFG_C_MAJOR != OXDOCAN_CFG_H_MAJOR)
#error "oxdocan_xid_cfg.c and oxdocan_cfg_private.h : source and header files are inconsistent!"
#endif

#if ((OXDOCAN_XID_CFG_C_MAJOR != OXDOCAN_XID_CFG_H_MAJOR) || \
     (OXDOCAN_XID_CFG_C_MINOR != OXDOCAN_XID_CFG_H_MINOR) || \
     (OXDOCAN_XID_CFG_C_PATCH != OXDOCAN_XID_CFG_H_PATCH))
#error "oxdocan_xid_cfg.c and oxdocan_xid_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
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
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U2                        u2_g_OXDC_XID_SUP_LP_LMT   = (U2)50U;  /* 50 times loop executable to check if XID is supported */
const U2                        u2_g_OXDC_IOC_RDBK_DLY_MAX = (U2)20U / (U2)OXDC_MAIN_TICK; /* 20 milliseconds */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_OXDC_IOC_IF            st_gp_OXDC_IOC_IF[] = {
/*   fp_u1_CSM_CHK                  fp_vd_ACT                       fp_vd_DEACT                    u2_sec     */
    {vdp_PTR_NA,                    vdp_PTR_NA,                     vdp_PTR_NA,                    (U2)0xFFFFU}
};
const U2                        u2_g_OXDC_NUM_IOC = (U2)(sizeof(st_gp_OXDC_IOC_IF) / sizeof(ST_OXDC_IOC_IF));

const ST_OXDC_XID               st_gp_OXDC_DATA_XID[] = {
/*   fp_u1_SUP                      u2_xid          u2_rd_ses          u2_rd_sec           u2_wr_ses          u2_wr_sec */
    {vdp_PTR_NA,                    (U2)0xA001U,    (U2)0x0005U,       (U2)0xFFFFU,       (U2)0x0000U,        (U2)0xFFFFU},
    {vdp_PTR_NA,                    (U2)0xA002U,    (U2)0x0005U,       (U2)0xFFFFU,       (U2)0x0000U,        (U2)0xFFFFU},
    {vdp_PTR_NA,                    (U2)0xA003U,    (U2)0x0005U,       (U2)0xFFFFU,       (U2)0x0000U,        (U2)0xFFFFU},
    {vdp_PTR_NA,                    (U2)0xA005U,    (U2)0x000DU,       (U2)0xFFFFU,       (U2)0x0000U,        (U2)0xFFFFU},
    {vdp_PTR_NA,                    (U2)0xA006U,    (U2)0x000DU,       (U2)0xFFFFU,       (U2)0x0000U,        (U2)0xFFFFU},
    {vdp_PTR_NA,                    (U2)0xA100U,    (U2)0x000DU,       (U2)0xFFFFU,       (U2)0x0000U,        (U2)0xFFFFU},
    {vdp_PTR_NA,                    (U2)0xA1A0U,    (U2)0x000DU,       (U2)0xFFFFU,       (U2)0x0000U,        (U2)0xFFFFU},
    {vdp_PTR_NA,                    (U2)0xA1A1U,    (U2)0x000DU,       (U2)0xFFFFU,       (U2)0x0000U,        (U2)0xFFFFU},
    {vdp_PTR_NA,                    (U2)0xA1A8U,    (U2)0x000DU,       (U2)0xFFFFU,       (U2)0x0000U,        (U2)0xFFFFU},
    {vdp_PTR_NA,                    (U2)0xA1A9U,    (U2)0x000DU,       (U2)0xFFFFU,       (U2)0x0000U,        (U2)0xFFFFU},
    {vdp_PTR_NA,                    (U2)0xA1F1U,    (U2)0x000DU,       (U2)0xFFFFU,       (U2)0x0000U,        (U2)0xFFFFU},
    {vdp_PTR_NA,                    (U2)0xA800U,    (U2)0x0005U,       (U2)0xFFFFU,       (U2)0x0000U,        (U2)0xFFFFU},
    {vdp_PTR_NA,                    (U2)0xA901U,    (U2)0x000DU,       (U2)0xFFFFU,       (U2)0x0000U,        (U2)0xFFFFU},
    {vdp_PTR_NA,                    (U2)0xF186U,    (U2)0x0005U,       (U2)0xFFFFU,       (U2)0x0000U,        (U2)0xFFFFU},
    {vdp_PTR_NA,                    (U2)0xF188U,    (U2)0x000DU,       (U2)0xFFFFU,       (U2)0x0000U,        (U2)0xFFFFU},
    {vdp_PTR_NA,                    (U2)0xF191U,    (U2)0x000DU,       (U2)0xFFFFU,       (U2)0x0000U,        (U2)0xFFFFU}
};

const ST_OXDC_XID_ML            st_gp_OXDC_DATA_XID_ML[] = {
/*   u2_req_nbyte                   u2_ans_nbyte */
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_A001},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_A002},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_A003},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_A005},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_A006},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_A100},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_A1XX},     /* DID:0xA1A0 */
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_A1XX},     /* DID:0xA1A1 */
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_A1XX},     /* DID:0xA1A8 */
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_A1XX},     /* DID:0xA1A9 */
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_A1XX},     /* DID:0xA1F1 */
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_A800},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_A901},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_F186},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_F188},
    {(U2)0U,                        (U2)OXDC_DATA_REA_ANS_NB_F191}
};

const ST_OXDC_DATA_IF           st_gp_OXDC_DATA_CFG[] = {
/*   fp_u1_READ                     fp_u1_WRITE                     stp_IOC */
    {&u1_g_oXDoCANRebyId_A001,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xA001 */
    {&u1_g_oXDoCANRebyId_A002,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xA002 */
    {&u1_g_oXDoCANRebyId_A003,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xA003 */
    {&u1_g_oXDoCANRebyId_A005,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xA005 */
    {&u1_g_oXDoCANRebyId_A006,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xA006 */
    {&u1_g_oXDoCANRebyId_A100,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xA100 */
    {&u1_g_oXDoCANRebyId_A1XX,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xA1A0 */
    {&u1_g_oXDoCANRebyId_A1XX,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xA1A1 */
    {&u1_g_oXDoCANRebyId_A1XX,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xA1A8 */
    {&u1_g_oXDoCANRebyId_A1XX,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xA1A9 */
    {&u1_g_oXDoCANRebyId_A1XX,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xA1F1 */
    {&u1_g_oXDoCANRebyId_A800,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xA800 */
    {&u1_g_oXDoCANRebyId_A901,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xA901 */
    {&u1_g_oXDoCANRebyId_F186,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xF186 */
    {&u1_g_oXDoCANRebyId_F188,      vdp_PTR_NA,                     vdp_PTR_NA                    },    /* DID:0xF188 */
    {&u1_g_oXDoCANRebyId_F191,      vdp_PTR_NA,                     vdp_PTR_NA                    }     /* DID:0xF191 */
};

const U2                        u2_g_OXDC_DATA_NUM_XID = (U2)(sizeof(st_gp_OXDC_DATA_XID) / sizeof(ST_OXDC_XID));

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_OXDC_XID               st_gp_OXDC_ROUT_XID[] = {
/*   fp_u1_SUP                 u2_xid          u2_rd_ses         u2_rd_sec           u2_wr_ses          u2_wr_sec */
    {vdp_PTR_NA,               (U2)0xD000U,    (U2)0x0005U,     (U2)0xFFFFU,         (U2)0x0000U,       (U2)0xFFFFU},
    {vdp_PTR_NA,               (U2)0xD001U,    (U2)0x0005U,     (U2)0xFFFFU,         (U2)0x0000U,       (U2)0xFFFFU},
    {vdp_PTR_NA,               (U2)0xD100U,    (U2)0x000DU,     (U2)0xFFFFU,         (U2)0x0000U,       (U2)0xFFFFU},
    {vdp_PTR_NA,               (U2)0xD1D0U,    (U2)0x000DU,     (U2)0xFFFFU,         (U2)0x0000U,       (U2)0xFFFFU},
    {vdp_PTR_NA,               (U2)0xD1D1U,    (U2)0x000DU,     (U2)0xFFFFU,         (U2)0x0000U,       (U2)0xFFFFU},
    {vdp_PTR_NA,               (U2)0xD1D9U,    (U2)0x000DU,     (U2)0xFFFFU,         (U2)0x0000U,       (U2)0xFFFFU},
    {vdp_PTR_NA,               (U2)0xD902U,    (U2)0x000DU,     (U2)0xFFFFU,         (U2)0x0000U,       (U2)0xFFFFU},
    {vdp_PTR_NA,               (U2)0xD903U,    (U2)0x000DU,     (U2)0xFFFFU,         (U2)0x0000U,       (U2)0xFFFFU},
    {vdp_PTR_NA,               (U2)0xD904U,    (U2)0x000DU,     (U2)0xFFFFU,         (U2)0x0000U,       (U2)0xFFFFU}
};

const ST_OXDC_XID_ML            st_gp_OXDC_ROUT_XID_ML_SF_01[] = {
/*   u2_req_nbyte                   u2_ans_nbyte */
    {(U2)OXDC_ROUT_STA_REQ_NB_D000, (U2)OXDC_ROUT_STA_ANS_NB_D000},     /* RID:0xD000 */
    {(U2)OXDC_ROUT_STA_REQ_NB_D001, (U2)OXDC_ROUT_STA_ANS_NB_D001},     /* RID:0xD001 */
    {(U2)OXDC_ROUT_STA_REQ_NB_D100, (U2)OXDC_ROUT_STA_ANS_NB_D100},     /* RID:0xD100 */
    {(U2)OXDC_ROUT_STA_REQ_NB_D1XX, (U2)OXDC_ROUT_STA_ANS_NB_D1XX},     /* RID:0xD1D0 */
    {(U2)OXDC_ROUT_STA_REQ_NB_D1XX, (U2)OXDC_ROUT_STA_ANS_NB_D1XX},     /* RID:0xD1D1 */
    {(U2)OXDC_ROUT_STA_REQ_NB_D1XX, (U2)OXDC_ROUT_STA_ANS_NB_D1XX},     /* RID:0xD1D9 */
    {(U2)OXDC_ROUT_STA_REQ_NB_D902, (U2)OXDC_ROUT_STA_ANS_NB_D902},     /* RID:0xD902 */
    {(U2)OXDC_ROUT_STA_REQ_NB_D903, (U2)OXDC_ROUT_STA_ANS_NB_D903},     /* RID:0xD903 */
    {(U2)OXDC_ROUT_STA_REQ_NB_D904, (U2)OXDC_ROUT_STA_ANS_NB_D904}      /* RID:0xD904 */
};

const ST_OXDC_XID_ML            st_gp_OXDC_ROUT_XID_ML_SF_02[] = {
/*   u2_req_nbyte                   u2_ans_nbyte */
    {(U2)0U,                        (U2)0U                       },     /* RID:0xD000 */
    {(U2)0U,                        (U2)0U                       },     /* RID:0xD001 */
    {(U2)0U,                        (U2)0U                       },     /* RID:0xD100 */
    {(U2)0U,                        (U2)0U                       },     /* RID:0xD1D0 */
    {(U2)0U,                        (U2)0U                       },     /* RID:0xD1D1 */
    {(U2)0U,                        (U2)0U                       },     /* RID:0xD1D9 */
    {(U2)0U,                        (U2)0U                       },     /* RID:0xD902 */
    {(U2)0U,                        (U2)0U                       },     /* RID:0xD903 */
    {(U2)0U,                        (U2)0U                       }      /* RID:0xD904 */
};

const ST_OXDC_XID_ML            st_gp_OXDC_ROUT_XID_ML_SF_03[] = {
/*   u2_req_nbyte                   u2_ans_nbyte */
    {(U2)0U,                        (U2)0U                       },     /* RID:0xD000 */
    {(U2)OXDC_ROUT_RES_REQ_NB_D001, (U2)OXDC_ROUT_RES_ANS_NB_D001},     /* RID:0xD001 */
    {(U2)0U,                        (U2)0U                       },     /* RID:0xD100 */
    {(U2)0U,                        (U2)0U                       },     /* RID:0xD1D0 */
    {(U2)0U,                        (U2)0U                       },     /* RID:0xD1D1 */
    {(U2)0U,                        (U2)0U                       },     /* RID:0xD1D9 */
    {(U2)0U,                        (U2)0U                       },     /* RID:0xD902 */
    {(U2)0U,                        (U2)0U                       },     /* RID:0xD903 */
    {(U2)OXDC_ROUT_RES_REQ_NB_D904, (U2)OXDC_ROUT_RES_ANS_NB_D904}      /* RID:0xD904 */
};

const ST_OXDC_ROUT_IF           st_gp_OXDC_ROUT_CFG[] = {
/*   fp_u1_COR_CHK                  fp_u1_START                         fp_u1_STOP                    fp_u1_RESULT */
    {&u1_g_oXDoCANRoutCorchk_D000,  &u1_g_oXDoCANRoutStart_D000,        vdp_PTR_NA,                   vdp_PTR_NA                     },   /* RID:0xD000 */
    {vdp_PTR_NA,                    &u1_g_oXDoCANRoutStart_D001,        vdp_PTR_NA,                   &u1_g_oXDoCANRoutRslt_D001     },   /* RID:0xD001 */
    {vdp_PTR_NA,                    &u1_g_oXDoCANRoutStart_D100,        vdp_PTR_NA,                   vdp_PTR_NA                     },   /* RID:0xD100 */
    {vdp_PTR_NA,                    &u1_g_oXDoCANRoutStart_D1XX,        vdp_PTR_NA,                   vdp_PTR_NA                     },   /* RID:0xD1D0 */
    {vdp_PTR_NA,                    &u1_g_oXDoCANRoutStart_D1XX,        vdp_PTR_NA,                   vdp_PTR_NA                     },   /* RID:0xD1D1 */
    {vdp_PTR_NA,                    &u1_g_oXDoCANRoutStart_D1XX,        vdp_PTR_NA,                   vdp_PTR_NA                     },   /* RID:0xD1D9 */
    {vdp_PTR_NA,                    &u1_g_oXDoCANRoutStart_D902,        vdp_PTR_NA,                   vdp_PTR_NA                     },   /* RID:0xD902 */
    {vdp_PTR_NA,                    &u1_g_oXDoCANRoutStart_D903,        vdp_PTR_NA,                   vdp_PTR_NA                     },   /* RID:0xD903 */
    {&u1_g_oXDoCANRoutCorchk_D904,  &u1_g_oXDoCANRoutStart_D904,        vdp_PTR_NA,                   &u1_g_oXDoCANRoutRslt_D904     }    /* RID:0xD904 */
};

const U2                        u2_g_OXDC_ROUT_NUM_XID = (U2)(sizeof(st_gp_OXDC_ROUT_XID) / sizeof(ST_OXDC_XID));

static const U1         u1_sp_TYDC_KZK_RX_D902[] = {                        /* oxdocan_xid_ma_cfg_private.h */
    (U1)TYDC_KZK_RX_PDU_1      /* MSG_BDC1S52_RXCH0 (0U) */
};
static const U1         u1_sp_TYDC_KZK_RX_D903[] = {                        /* oxdocan_xid_ma_cfg_private.h */
    (U1)TYDC_KZK_RX_PDU_IUV    /* MSG_BDC1S60_RXCH0 (1U) */
};
const ST_TYDC_KZK_RX    st_gp_TYDC_KZK_RX[TYDC_KZK_NUM_RX] = {              /* oxdocan_xid_ma_cfg_private.h */
/*   u1p_KZK_RX                     u2_pdu_min                      u2_pdu_max */
     {&u1_sp_TYDC_KZK_RX_D902[0],    (U2)MSG_BDC1S52_RXCH0,         (U2)MSG_BDC1S52_RXCH0     },
     {&u1_sp_TYDC_KZK_RX_D903[0],    (U2)MSG_BDC1S60_RXCH0,         (U2)MSG_BDC1S60_RXCH0     }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  U1      u1_g_TyDoCANXidMaCfgSafeKeyNum(U1 * u1_ap_skn)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_TyDoCANXidMaCfgSafeKeyNum(U1 * u1_ap_skn)
{
    /* ----------------------------------------------------------------- */
    /* Attention :                                                       */
    /* ----------------------------------------------------------------- */
    /* The array size of u1_ap_skn = OXDC_DATA_REA_ANS_NB_A901 and it's  */
    /* tested in oxdocan_rebyid.c                                        */
    /* ----------------------------------------------------------------- */

    /* sample start : Notify fixed values */
    static const U1 u1_sp_SKEY_NUMBER[OXDC_DATA_REA_ANS_NB_A901] = {
        0x00U,0x11U,0x22U,0x33U,
        0x44U,0x55U,0x66U,0x77U,
        0x88U,0x99U,0xaaU,0xbbU,
        0xccU,0xddU,0xeeU,0xffU
    };

    vd_g_MemcpyU1(u1_ap_skn, &u1_sp_SKEY_NUMBER[0], (U4)OXDC_DATA_REA_ANS_NB_A901);
    /* sample end */

    return((U1)TRUE);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     7/25/2022  II       New.                                                                                               */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*  * II = Itsuki Ito, DENSO                                                                                                         */
/*                                                                                                                                   */
/*===================================================================================================================================*/
