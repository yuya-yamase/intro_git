/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Eelectric Vehicle System Charging                                                                                                */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define EVSCHG_CFG_C_MAJOR                  (1)
#define EVSCHG_CFG_C_MINOR                  (0)
#define EVSCHG_CFG_C_PATCH                  (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "evschg_cfg_private.h"

#include "veh_opemd.h"
#if 0   /* BEV BSW provisionally */
#else
#include "veh_opemd_xmode_STUB.h"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((EVSCHG_CFG_C_MAJOR != EVSCHG_CFG_H_MAJOR) ||\
     (EVSCHG_CFG_C_MINOR != EVSCHG_CFG_H_MINOR) ||\
     (EVSCHG_CFG_C_PATCH != EVSCHG_CFG_H_PATCH))
#error "evschg_cfg.c and evschg_cfg_private.h : source and header files are inconsistent!"
#endif

#if ((EVSCHG_CFG_C_MAJOR != EVSCHG_H_MAJOR) ||\
     (EVSCHG_CFG_C_MINOR != EVSCHG_H_MINOR) ||\
     (EVSCHG_CFG_C_PATCH != EVSCHG_H_PATCH))
#error "evschg_cfg.c and evschg.h : source and header files are inconsistent!"
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
static void             vd_s_EvschgCfgTimchg(ST_EVSCHG_SGNL * st_ap_sig);
static void             vd_s_EvschgCfgTimchgSchd(ST_EVSCHG_SGNL * st_ap_schd_sig);
static void             vd_s_EvschgCfgSwquichg(ST_EVSCHG_SGNL * st_ap_sig);
static void             vd_s_EvschgCfgSendM_SETSTM(const U2 u2_a_RXDATA);
static void             vd_s_EvschgCfgSendM_SETFTM(const U2 u2_a_RXDATA);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const   ST_EVSCHG_RX        st_gp_EVSCHG_RX_CFG[EVSCHG_ID_RX_NUM] = {
    /* TIMCHG-CSTD-2 */
    {   (U1)EVSCHG_RIMSIZE_U1,      (U2)RIMID_U1_EVSCHG_P_NCTYP,        (U1)EVSCHG_TOUT_BHOLD   },  /*  00 EVSCHG_ID_P_NCTYP        */
    {   (U1)EVSCHG_RIMSIZE_U1,      (U2)RIMID_U1_EVSCHG_P_NCWKD,        (U1)EVSCHG_TOUT_BHOLD   },  /*  01 EVSCHG_ID_P_NCWKD        */
    {   (U1)EVSCHG_RIMSIZE_U2,      (U2)RIMID_U2_EVSCHG_P_NCSTM,        (U1)EVSCHG_TOUT_BHOLD   },  /*  02 EVSCHG_ID_P_NCSTM        */
    {   (U1)EVSCHG_RIMSIZE_U2,      (U2)RIMID_U2_EVSCHG_P_NCFTM,        (U1)EVSCHG_TOUT_BHOLD   },  /*  03 EVSCHG_ID_P_NCFTM        */
    {   (U1)EVSCHG_RIMSIZE_U1,      (U2)RIMID_U1_EVSCHG_P_ADDDSP,       (U1)EVSCHG_TOUT_BHOLD   },  /*  04 EVSCHG_ID_P_ADDDSP       */
    {   (U1)EVSCHG_RIMSIZE_U1,      (U2)RIMID_U1_EVSCHG_PCNOWDSP,       (U1)EVSCHG_TOUT_BHOLD   },  /*  05 EVSCHG_ID_PCNOWDSP       */
    {   (U1)EVSCHG_RIMSIZE_U1,      (U2)RIMID_U1_EVSCHG_P_NCDSP,        (U1)EVSCHG_TOUT_INIT    },  /*  06 EVSCHG_ID_P_NCDSP        */
    {   (U1)EVSCHG_RIMSIZE_U1,      (U2)RIMID_U1_EVSCHG_P_TMPID,        (U1)EVSCHG_TOUT_INIT    },  /*  07 EVSCHG_ID_P_TMPID        */
    {   (U1)EVSCHG_RIMSIZE_U1,      (U2)RIMID_U1_EVSCHG_P_TMPTYP,       (U1)EVSCHG_TOUT_INIT    },  /*  08 EVSCHG_ID_P_TMPTYP       */
    {   (U1)0xFFU,                  (U2)0xFFFFU,                        (U1)0xFFU               },  /*  09 EVSCHG_ID_P_TMPACD       */
    {   (U1)0xFFU,                  (U2)0xFFFFU,                        (U1)0xFFU               },  /*  10 EVSCHG_ID_P_TMPACN       */
    {   (U1)EVSCHG_RIMSIZE_U2,      (U2)RIMID_U2_EVSCHG_P_TMPSTM,       (U1)EVSCHG_TOUT_INIT    },  /*  11 EVSCHG_ID_P_TMPSTM       */
    {   (U1)EVSCHG_RIMSIZE_U2,      (U2)RIMID_U2_EVSCHG_P_TMPFTM,       (U1)EVSCHG_TOUT_INIT    },  /*  12 EVSCHG_ID_P_TMPFTM       */
    {   (U1)EVSCHG_RIMSIZE_U1,      (U2)RIMID_U1_EVSCHG_P_TMPSWK,       (U1)EVSCHG_TOUT_INIT    },  /*  13 EVSCHG_ID_P_TMPSWK       */
    {   (U1)EVSCHG_RIMSIZE_U1,      (U2)RIMID_U1_EVSCHG_P_TMPNWK,       (U1)EVSCHG_TOUT_INIT    },  /*  14 EVSCHG_ID_P_TMPNWK       */
    {   (U1)EVSCHG_RIMSIZE_U1,      (U2)RIMID_U1_EVSCHG_PARK_S,         (U1)EVSCHG_TOUT_BHOLD   },  /*  15 EVSCHG_ID_PARK_S         */
    /* SWQUICHA-CSTD-2 */
    {   (U1)0xFFU,                  (U2)0xFFFFU,                        (U1)0xFFU               },  /*  16 EVSCHG_ID_P_CURDSP       */
    {   (U1)EVSCHG_RIMSIZE_U1,      (U2)RIMID_U1_EVSCHG_P_CUR200,       (U1)EVSCHG_TOUT_BHOLD   },  /*  17 EVSCHG_ID_P_CUR200       */
    {   (U1)0xFFU,                  (U2)0xFFFFU,                        (U1)0xFFU               },  /*  18 EVSCHG_ID_P_CURSEL       */
    {   (U1)0xFFU,                  (U2)0xFFFFU,                        (U1)0xFFU               },  /*  19 EVSCHG_ID_CBLC_AVA       */
    {   (U1)EVSCHG_RIMSIZE_U1,      (U2)RIMID_U1_EVSCHG_CBLOCKSU,       (U1)EVSCHG_TOUT_BHOLD   },  /*  20 EVSCHG_ID_CBLOCKSU       */
    {   (U1)0xFFU,                  (U2)0xFFFFU,                        (U1)0xFFU               },  /*  21 EVSCHG_ID_P_LMTDSP       */
    {   (U1)EVSCHG_RIMSIZE_U1,      (U2)RIMID_U1_EVSCHG_P_CURAVA,       (U1)EVSCHG_TOUT_INIT    },  /*  22 EVSCHG_ID_P_CURAVA       */
    {   (U1)EVSCHG_RIMSIZE_U1,      (U2)RIMID_U1_EVSCHG_P_CLCAVA,       (U1)EVSCHG_TOUT_INIT    },  /*  23 EVSCHG_ID_P_CLCAVA       */
    {   (U1)EVSCHG_RIMSIZE_U1,      (U2)RIMID_U1_EVSCHG_P_LMTAVA,       (U1)EVSCHG_TOUT_INIT    },  /*  24 EVSCHG_ID_P_LMTAVA       */
    {   (U1)EVSCHG_RIMSIZE_U1,      (U2)RIMID_U1_EVSCHG_P_LMTNOW,       (U1)EVSCHG_TOUT_BHOLD   },  /*  25 EVSCHG_ID_P_LMTNOW       */
    {   (U1)EVSCHG_RIMSIZE_U1,      (U2)RIMID_U1_EVSCHG_P_LMTSEL,       (U1)EVSCHG_TOUT_BHOLD   },  /*  26 EVSCHG_ID_P_LMTSEL       */
    {   (U1)EVSCHG_RIMSIZE_U1,      (U2)RIMID_U1_EVSCHG_P_DPWAVA,       (U1)EVSCHG_TOUT_INIT    },  /*  27 EVSCHG_ID_P_DPWAVA       */
    {   (U1)EVSCHG_RIMSIZE_U1,      (U2)RIMID_U1_EVSCHG_P_DPW,          (U1)EVSCHG_TOUT_BHOLD   },  /*  28 EVSCHG_ID_P_DPW          */
    {   (U1)EVSCHG_RIMSIZE_U1,      (U2)RIMID_U1_EVSCHG_P_DPWSL0,       (U1)EVSCHG_TOUT_BHOLD   },  /*  29 EVSCHG_ID_P_DPWSL0       */
    {   (U1)EVSCHG_RIMSIZE_U1,      (U2)RIMID_U1_EVSCHG_P_DPWSL1,       (U1)EVSCHG_TOUT_BHOLD   },  /*  30 EVSCHG_ID_P_DPWSL1       */
    {   (U1)EVSCHG_RIMSIZE_U1,      (U2)RIMID_U1_EVSCHG_P_DPWSL2,       (U1)EVSCHG_TOUT_BHOLD   },  /*  31 EVSCHG_ID_P_DPWSL2       */
    {   (U1)EVSCHG_RIMSIZE_U1,      (U2)RIMID_U1_EVSCHG_P_DPWSL3,       (U1)EVSCHG_TOUT_BHOLD   },  /*  32 EVSCHG_ID_P_DPWSL3       */
    {   (U1)EVSCHG_RIMSIZE_U1,      (U2)RIMID_U1_EVSCHG_P_DPWSL4,       (U1)EVSCHG_TOUT_BHOLD   },  /*  33 EVSCHG_ID_P_DPWSL4       */
    {   (U1)EVSCHG_RIMSIZE_U1,      (U2)RIMID_U1_EVSCHG_P_DPWSL5,       (U1)EVSCHG_TOUT_BHOLD   },  /*  34 EVSCHG_ID_P_DPWSL5       */
    {   (U1)EVSCHG_RIMSIZE_U1,      (U2)RIMID_U1_EVSCHG_P_DPWSL6,       (U1)EVSCHG_TOUT_BHOLD   },  /*  35 EVSCHG_ID_P_DPWSL6       */
    {   (U1)EVSCHG_RIMSIZE_U1,      (U2)RIMID_U1_EVSCHG_P_DPWSL7,       (U1)EVSCHG_TOUT_BHOLD   },  /*  36 EVSCHG_ID_P_DPWSL7       */
    {   (U1)EVSCHG_RIMSIZE_U1,      (U2)RIMID_U1_EVSCHG_P_DPWSL8,       (U1)EVSCHG_TOUT_BHOLD   },  /*  37 EVSCHG_ID_P_DPWSL8       */
    {   (U1)EVSCHG_RIMSIZE_U1,      (U2)RIMID_U1_EVSCHG_P_DPWSL9,       (U1)EVSCHG_TOUT_BHOLD   },  /*  38 EVSCHG_ID_P_DPWSL9       */
    {   (U1)EVSCHG_RIMSIZE_U1,      (U2)RIMID_U1_EVSCHG_P_TMRAVA,       (U1)EVSCHG_TOUT_INIT    },  /*  39 EVSCHG_ID_P_TMRAVA       */
    {   (U1)EVSCHG_RIMSIZE_U1,      (U2)RIMID_U1_EVSCHG_P_SLMAVA,       (U1)EVSCHG_TOUT_INIT    },  /*  40 EVSCHG_ID_P_SLMAVA       */
    {   (U1)EVSCHG_RIMSIZE_U1,      (U2)RIMID_U1_EVSCHG_P_CURSL1,       (U1)EVSCHG_TOUT_BHOLD   },  /*  41 EVSCHG_ID_P_CURSL1       */
    {   (U1)EVSCHG_RIMSIZE_U1,      (U2)RIMID_U1_EVSCHG_P_CURSL2,       (U1)EVSCHG_TOUT_BHOLD   },  /*  42 EVSCHG_ID_P_CURSL2       */
    {   (U1)EVSCHG_RIMSIZE_U1,      (U2)RIMID_U1_EVSCHG_P_CURSL3,       (U1)EVSCHG_TOUT_BHOLD   },  /*  43 EVSCHG_ID_P_CURSL3       */
    {   (U1)EVSCHG_RIMSIZE_U1,      (U2)RIMID_U1_EVSCHG_P_CURSL4,       (U1)EVSCHG_TOUT_BHOLD   }   /*  44 EVSCHG_ID_P_CURSL4       */
};

const   U2                  u2_gp_EVSCHG_RIMID_P_SETID[EVSCHG_TIMCHG_SCHDINFO_SIZE] = {
    (U2)RIMID_U1_EVSCHG_P_SETID_00,
    (U2)RIMID_U1_EVSCHG_P_SETID_01,
    (U2)RIMID_U1_EVSCHG_P_SETID_02,
    (U2)RIMID_U1_EVSCHG_P_SETID_03,
    (U2)RIMID_U1_EVSCHG_P_SETID_04,
    (U2)RIMID_U1_EVSCHG_P_SETID_05,
    (U2)RIMID_U1_EVSCHG_P_SETID_06,
    (U2)RIMID_U1_EVSCHG_P_SETID_07,
    (U2)RIMID_U1_EVSCHG_P_SETID_08,
    (U2)RIMID_U1_EVSCHG_P_SETID_09,
    (U2)RIMID_U1_EVSCHG_P_SETID_10,
    (U2)RIMID_U1_EVSCHG_P_SETID_11,
    (U2)RIMID_U1_EVSCHG_P_SETID_12,
    (U2)RIMID_U1_EVSCHG_P_SETID_13,
    (U2)RIMID_U1_EVSCHG_P_SETID_14,
    (U2)RIMID_U1_EVSCHG_P_SETID_15
};

const   U2                  u2_gp_EVSCHG_RIMID_P_SETON[EVSCHG_TIMCHG_SCHDINFO_SIZE] = {
    (U2)RIMID_U1_EVSCHG_P_SETON_00,
    (U2)RIMID_U1_EVSCHG_P_SETON_01,
    (U2)RIMID_U1_EVSCHG_P_SETON_02,
    (U2)RIMID_U1_EVSCHG_P_SETON_03,
    (U2)RIMID_U1_EVSCHG_P_SETON_04,
    (U2)RIMID_U1_EVSCHG_P_SETON_05,
    (U2)RIMID_U1_EVSCHG_P_SETON_06,
    (U2)RIMID_U1_EVSCHG_P_SETON_07,
    (U2)RIMID_U1_EVSCHG_P_SETON_08,
    (U2)RIMID_U1_EVSCHG_P_SETON_09,
    (U2)RIMID_U1_EVSCHG_P_SETON_10,
    (U2)RIMID_U1_EVSCHG_P_SETON_11,
    (U2)RIMID_U1_EVSCHG_P_SETON_12,
    (U2)RIMID_U1_EVSCHG_P_SETON_13,
    (U2)RIMID_U1_EVSCHG_P_SETON_14,
    (U2)RIMID_U1_EVSCHG_P_SETON_15
};

const   U2                  u2_gp_EVSCHG_RIMID_P_SETTYP[EVSCHG_TIMCHG_SCHDINFO_SIZE] = {
    (U2)RIMID_U1_EVSCHG_P_SETTYP_00,
    (U2)RIMID_U1_EVSCHG_P_SETTYP_01,
    (U2)RIMID_U1_EVSCHG_P_SETTYP_02,
    (U2)RIMID_U1_EVSCHG_P_SETTYP_03,
    (U2)RIMID_U1_EVSCHG_P_SETTYP_04,
    (U2)RIMID_U1_EVSCHG_P_SETTYP_05,
    (U2)RIMID_U1_EVSCHG_P_SETTYP_06,
    (U2)RIMID_U1_EVSCHG_P_SETTYP_07,
    (U2)RIMID_U1_EVSCHG_P_SETTYP_08,
    (U2)RIMID_U1_EVSCHG_P_SETTYP_09,
    (U2)RIMID_U1_EVSCHG_P_SETTYP_10,
    (U2)RIMID_U1_EVSCHG_P_SETTYP_11,
    (U2)RIMID_U1_EVSCHG_P_SETTYP_12,
    (U2)RIMID_U1_EVSCHG_P_SETTYP_13,
    (U2)RIMID_U1_EVSCHG_P_SETTYP_14,
    (U2)RIMID_U1_EVSCHG_P_SETTYP_15
};

const   U2                  u2_gp_EVSCHG_RIMID_P_SETSTM[EVSCHG_TIMCHG_SCHDINFO_SIZE] = {
    (U2)RIMID_U2_EVSCHG_P_SETSTM_00,
    (U2)RIMID_U2_EVSCHG_P_SETSTM_01,
    (U2)RIMID_U2_EVSCHG_P_SETSTM_02,
    (U2)RIMID_U2_EVSCHG_P_SETSTM_03,
    (U2)RIMID_U2_EVSCHG_P_SETSTM_04,
    (U2)RIMID_U2_EVSCHG_P_SETSTM_05,
    (U2)RIMID_U2_EVSCHG_P_SETSTM_06,
    (U2)RIMID_U2_EVSCHG_P_SETSTM_07,
    (U2)RIMID_U2_EVSCHG_P_SETSTM_08,
    (U2)RIMID_U2_EVSCHG_P_SETSTM_09,
    (U2)RIMID_U2_EVSCHG_P_SETSTM_10,
    (U2)RIMID_U2_EVSCHG_P_SETSTM_11,
    (U2)RIMID_U2_EVSCHG_P_SETSTM_12,
    (U2)RIMID_U2_EVSCHG_P_SETSTM_13,
    (U2)RIMID_U2_EVSCHG_P_SETSTM_14,
    (U2)RIMID_U2_EVSCHG_P_SETSTM_15
};

const   U2                  u2_gp_EVSCHG_RIMID_P_SETFTM[EVSCHG_TIMCHG_SCHDINFO_SIZE] = {
    (U2)RIMID_U2_EVSCHG_P_SETFTM_00,
    (U2)RIMID_U2_EVSCHG_P_SETFTM_01,
    (U2)RIMID_U2_EVSCHG_P_SETFTM_02,
    (U2)RIMID_U2_EVSCHG_P_SETFTM_03,
    (U2)RIMID_U2_EVSCHG_P_SETFTM_04,
    (U2)RIMID_U2_EVSCHG_P_SETFTM_05,
    (U2)RIMID_U2_EVSCHG_P_SETFTM_06,
    (U2)RIMID_U2_EVSCHG_P_SETFTM_07,
    (U2)RIMID_U2_EVSCHG_P_SETFTM_08,
    (U2)RIMID_U2_EVSCHG_P_SETFTM_09,
    (U2)RIMID_U2_EVSCHG_P_SETFTM_10,
    (U2)RIMID_U2_EVSCHG_P_SETFTM_11,
    (U2)RIMID_U2_EVSCHG_P_SETFTM_12,
    (U2)RIMID_U2_EVSCHG_P_SETFTM_13,
    (U2)RIMID_U2_EVSCHG_P_SETFTM_14,
    (U2)RIMID_U2_EVSCHG_P_SETFTM_15
};

const   U2                  u2_gp_EVSCHG_RIMID_P_SETWKD[EVSCHG_TIMCHG_SCHDINFO_SIZE] = {
    (U2)RIMID_U1_EVSCHG_P_SETWKD_00,
    (U2)RIMID_U1_EVSCHG_P_SETWKD_01,
    (U2)RIMID_U1_EVSCHG_P_SETWKD_02,
    (U2)RIMID_U1_EVSCHG_P_SETWKD_03,
    (U2)RIMID_U1_EVSCHG_P_SETWKD_04,
    (U2)RIMID_U1_EVSCHG_P_SETWKD_05,
    (U2)RIMID_U1_EVSCHG_P_SETWKD_06,
    (U2)RIMID_U1_EVSCHG_P_SETWKD_07,
    (U2)RIMID_U1_EVSCHG_P_SETWKD_08,
    (U2)RIMID_U1_EVSCHG_P_SETWKD_09,
    (U2)RIMID_U1_EVSCHG_P_SETWKD_10,
    (U2)RIMID_U1_EVSCHG_P_SETWKD_11,
    (U2)RIMID_U1_EVSCHG_P_SETWKD_12,
    (U2)RIMID_U1_EVSCHG_P_SETWKD_13,
    (U2)RIMID_U1_EVSCHG_P_SETWKD_14,
    (U2)RIMID_U1_EVSCHG_P_SETWKD_15
};

const   U2                  u2_gp_EVSCHG_RIMID_P_SETNXT[EVSCHG_TIMCHG_SCHDINFO_SIZE] = {
    (U2)RIMID_U1_EVSCHG_P_SETNXT_00,
    (U2)RIMID_U1_EVSCHG_P_SETNXT_01,
    (U2)RIMID_U1_EVSCHG_P_SETNXT_02,
    (U2)RIMID_U1_EVSCHG_P_SETNXT_03,
    (U2)RIMID_U1_EVSCHG_P_SETNXT_04,
    (U2)RIMID_U1_EVSCHG_P_SETNXT_05,
    (U2)RIMID_U1_EVSCHG_P_SETNXT_06,
    (U2)RIMID_U1_EVSCHG_P_SETNXT_07,
    (U2)RIMID_U1_EVSCHG_P_SETNXT_08,
    (U2)RIMID_U1_EVSCHG_P_SETNXT_09,
    (U2)RIMID_U1_EVSCHG_P_SETNXT_10,
    (U2)RIMID_U1_EVSCHG_P_SETNXT_11,
    (U2)RIMID_U1_EVSCHG_P_SETNXT_12,
    (U2)RIMID_U1_EVSCHG_P_SETNXT_13,
    (U2)RIMID_U1_EVSCHG_P_SETNXT_14,
    (U2)RIMID_U1_EVSCHG_P_SETNXT_15
};

void    (* const            fp_gp_vd_EVSCHG_TX[EVSCHG_ID_TX_NUM])(const U2 u2_a_RXDATA) = {
        vdp_PTR_NA,                                   /*   EVSCHG_ID_M_SETACN            */
        &vd_s_EvschgCfgSendM_SETSTM,                  /*   EVSCHG_ID_M_SETSTM            */
        &vd_s_EvschgCfgSendM_SETFTM                   /*   EVSCHG_ID_M_SETFTM            */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((EVSCHG_STSBIT_UNKNOWN != COM_NO_RX  ) || \
     (EVSCHG_STSBIT_INVALID != COM_TIMEOUT))
#error "evschg status bit and com status bit are inconsistent!"
#endif

/*===================================================================================================================================*/
/* void                    vd_g_EvschgCfgBonInit(void)                                                                               */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  -                                                                                                                    */
/*===================================================================================================================================*/
void                    vd_g_EvschgCfgBonInit(void)
{
}

/*===================================================================================================================================*/
/* void                    vd_g_EvschgCfgBonTxInit(void)                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  -                                                                                                                    */
/*===================================================================================================================================*/
void                    vd_g_EvschgCfgBonTxInit(void)
{
    U1                          u1_t_snddata;
    U2                          u2_t_snddata;

    /* M_SETSTS */
    u1_t_snddata = (U1)EVSCHG_M_SETSTS_INIT;
    (void)Com_SendSignal(ComConf_ComSignal_M_SETSTS, &u1_t_snddata);
    /* M_SETID */
    u1_t_snddata = (U1)EVSCHG_M_SETID_INIT;
    (void)Com_SendSignal(ComConf_ComSignal_M_SETID, &u1_t_snddata);
    /* M_SETTYP */
    u1_t_snddata = (U1)EVSCHG_M_SETTYP_INIT;
    (void)Com_SendSignal(ComConf_ComSignal_M_SETTYP, &u1_t_snddata);
    /* M_SETWKD */
    u1_t_snddata = (U1)EVSCHG_M_SETWKD_INIT;
    (void)Com_SendSignal(ComConf_ComSignal_M_SETWKD, &u1_t_snddata);
    /* M_SETSTM */
    u2_t_snddata = (U2)EVSCHG_M_SETSTM_INIT;
    (void)Com_SendSignal(ComConf_ComSignal_M_SETSTM, &u2_t_snddata);
    /* M_SETFTM */
    u2_t_snddata = (U2)EVSCHG_M_SETFTM_INIT;
    (void)Com_SendSignal(ComConf_ComSignal_M_SETFTM, &u2_t_snddata);
    /* M_SETNXT */
    u1_t_snddata = (U1)EVSCHG_M_SETNXT_INIT;
    (void)Com_SendSignal(ComConf_ComSignal_M_SETNXT, &u1_t_snddata);

    /* M_CUR200 */
    u1_t_snddata = (U1)EVSCHG_M_CUR200_INIT;
    (void)Com_SendSignal(ComConf_ComSignal_M_CUR200, &u1_t_snddata);
    /* CLOCK_SU */
    u1_t_snddata = (U1)EVSCHG_CLOCK_SU_INIT;
    (void)Com_SendSignal(ComConf_ComSignal_CLOCK_SU, &u1_t_snddata);
    /* M_LMTREQ */
    u1_t_snddata = (U1)EVSCHG_M_LMTREQ_INIT;
    (void)Com_SendSignal(ComConf_ComSignal_M_LMTREQ, &u1_t_snddata);
    /* M_DPWREQ */
    u1_t_snddata = (U1)EVSCHG_M_DPWREQ_INIT;
    (void)Com_SendSignal(ComConf_ComSignal_M_DPWREQ, &u1_t_snddata);

    /* M_PNCSW */
    u1_t_snddata = (U1)EVSCHG_M_PNCSW_INIT;
    (void)Com_SendSignal(ComConf_ComSignal_M_PNCSW, &u1_t_snddata);
}

/*===================================================================================================================================*/
/* void                    vd_g_EvschgCfgRstwkInit(void)                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  -                                                                                                                    */
/*===================================================================================================================================*/
void                    vd_g_EvschgCfgRstwkInit(void)
{
}

/*===================================================================================================================================*/
/* void                    vd_g_EvschgCfgMainTask(void)                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  -                                                                                                                    */
/*===================================================================================================================================*/
void                    vd_g_EvschgCfgMainTask(void)
{
}

/*===================================================================================================================================*/
/* void                    vd_g_EvschgCfgSgnlInst(ST_EVSCHG_SGNL * st_ap_sig, ST_EVSCHG_SGNL * st_ap_schd_sig)                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  -                                                                                                                    */
/*===================================================================================================================================*/
void                    vd_g_EvschgCfgSgnlInst(ST_EVSCHG_SGNL * st_ap_sig, ST_EVSCHG_SGNL * st_ap_schd_sig)
{
    /* TIMCHG-CSTD */
    vd_s_EvschgCfgTimchg(st_ap_sig);
    vd_s_EvschgCfgTimchgSchd(st_ap_schd_sig);

    /* SWQUICHA-CSTD */
    vd_s_EvschgCfgSwquichg(st_ap_sig);
}

/*===================================================================================================================================*/
/* U2                      u2_g_EvschgCfgToutSp(U4 u4_a_ID, U2 u2_a_sig)                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  -                                                                                                                    */
/*===================================================================================================================================*/
U2                      u2_g_EvschgCfgToutSp(U4 u4_a_ID, U2 u2_a_sig)
{
    return((U2)0U);
}

/*===================================================================================================================================*/
/* static void             vd_s_EvschgCfgTimchg(ST_EVSCHG_SGNL * st_ap_sig)                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  -                                                                                                                    */
/*===================================================================================================================================*/
static void             vd_s_EvschgCfgTimchg(ST_EVSCHG_SGNL * st_ap_sig)
{
    U1                          u1_t_sig;
    U2                          u2_t_sig;
    U1                          u1_t_sts_plg1g11;
    U1                          u1_t_sts_plg1g13;
    U1                          u1_t_sts_scn1s02;

    u1_t_sts_plg1g11 = (U1)Com_GetIPDUStatus(MSG_PLG1G11_RXCH0) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    u1_t_sts_plg1g13 = (U1)Com_GetIPDUStatus(MSG_PLG1G13_RXCH0) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    u1_t_sts_scn1s02 = (U1)Com_GetIPDUStatus(MSG_SCN1S02_RXCH0) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    /* P_NCTYP */
    st_ap_sig[EVSCHG_ID_P_NCTYP].u1_sts = u1_t_sts_plg1g11;
    u1_t_sig = (U1)EVSCHG_P_NCTYP_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_P_NCTYP, &u1_t_sig);
    st_ap_sig[EVSCHG_ID_P_NCTYP].u2_sig = (U2)u1_t_sig;

    /* P_NCWKD */
    st_ap_sig[EVSCHG_ID_P_NCWKD].u1_sts = u1_t_sts_plg1g11;
    u1_t_sig = (U1)EVSCHG_P_NCWKD_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_P_NCWKD, &u1_t_sig);
    st_ap_sig[EVSCHG_ID_P_NCWKD].u2_sig = (U2)u1_t_sig;

    /* P_NCSTM */
    st_ap_sig[EVSCHG_ID_P_NCSTM].u1_sts = u1_t_sts_plg1g11;
    u2_t_sig = (U2)EVSCHG_P_NCSTM_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_P_NCSTM, &u2_t_sig);
    st_ap_sig[EVSCHG_ID_P_NCSTM].u2_sig = u2_t_sig;

    /* P_NCFTM */
    st_ap_sig[EVSCHG_ID_P_NCFTM].u1_sts = u1_t_sts_plg1g11;
    u2_t_sig = (U2)EVSCHG_P_NCFTM_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_P_NCFTM, &u2_t_sig);
    st_ap_sig[EVSCHG_ID_P_NCFTM].u2_sig = u2_t_sig;

    /* P_ADDDSP */
    st_ap_sig[EVSCHG_ID_P_ADDDSP].u1_sts = u1_t_sts_plg1g13;
    u1_t_sig = (U1)EVSCHG_P_ADDDSP_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_P_ADDDSP, &u1_t_sig);
    st_ap_sig[EVSCHG_ID_P_ADDDSP].u2_sig = (U2)u1_t_sig;

    /* PCNOWDSP */
    st_ap_sig[EVSCHG_ID_PCNOWDSP].u1_sts = u1_t_sts_plg1g13;
    u1_t_sig = (U1)EVSCHG_PCNOWDSP_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_PCNOWDSP, &u1_t_sig);
    st_ap_sig[EVSCHG_ID_PCNOWDSP].u2_sig = (U2)u1_t_sig;

    /* P_NCDSP */
    st_ap_sig[EVSCHG_ID_P_NCDSP].u1_sts = u1_t_sts_plg1g11;
    u1_t_sig = (U1)EVSCHG_P_NCDSP_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_P_NCDSP, &u1_t_sig);
    st_ap_sig[EVSCHG_ID_P_NCDSP].u2_sig = (U2)u1_t_sig;

    /* P_TMPID */
    st_ap_sig[EVSCHG_ID_P_TMPID].u1_sts = u1_t_sts_plg1g13;
    u1_t_sig = (U1)EVSCHG_P_TMPID_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_P_TMPID, &u1_t_sig);
    st_ap_sig[EVSCHG_ID_P_TMPID].u2_sig = (U2)u1_t_sig;

    /* P_TMPTYP */
    st_ap_sig[EVSCHG_ID_P_TMPTYP].u1_sts = u1_t_sts_plg1g13;
    u1_t_sig = (U1)EVSCHG_P_TMPTYP_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_P_TMPTYP, &u1_t_sig);
    st_ap_sig[EVSCHG_ID_P_TMPTYP].u2_sig = (U2)u1_t_sig;

    /* P_TMPSTM */
    st_ap_sig[EVSCHG_ID_P_TMPSTM].u1_sts = u1_t_sts_plg1g13;
    u2_t_sig = (U2)EVSCHG_P_TMPSTM_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_P_TMPSTM, &u2_t_sig);
    st_ap_sig[EVSCHG_ID_P_TMPSTM].u2_sig = u2_t_sig;

    /* P_TMPFTM */
    st_ap_sig[EVSCHG_ID_P_TMPFTM].u1_sts = u1_t_sts_plg1g13;
    u2_t_sig = (U2)EVSCHG_P_TMPFTM_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_P_TMPFTM, &u2_t_sig);
    st_ap_sig[EVSCHG_ID_P_TMPFTM].u2_sig = u2_t_sig;

    /* P_TMPSWK */
    st_ap_sig[EVSCHG_ID_P_TMPSWK].u1_sts = u1_t_sts_plg1g13;
    u1_t_sig = (U1)EVSCHG_P_TMPSWK_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_P_TMPSWK, &u1_t_sig);
    st_ap_sig[EVSCHG_ID_P_TMPSWK].u2_sig = (U2)u1_t_sig;

    /* P_TMPNWK */
    st_ap_sig[EVSCHG_ID_P_TMPNWK].u1_sts = u1_t_sts_plg1g13;
    u1_t_sig = (U1)EVSCHG_P_TMPNWK_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_P_TMPNWK, &u1_t_sig);
    st_ap_sig[EVSCHG_ID_P_TMPNWK].u2_sig = (U2)u1_t_sig;

    /* PARK_S */
    st_ap_sig[EVSCHG_ID_PARK_S].u1_sts = u1_t_sts_scn1s02;
    u1_t_sig = (U1)EVSCHG_PARK_S_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_PARK_S, &u1_t_sig);
    st_ap_sig[EVSCHG_ID_PARK_S].u2_sig = (U2)u1_t_sig;
}

/*===================================================================================================================================*/
/* static void             vd_s_EvschgCfgTimchgSchd(ST_EVSCHG_SGNL * st_ap_schd_sig)                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  -                                                                                                                    */
/*===================================================================================================================================*/
static void             vd_s_EvschgCfgTimchgSchd(ST_EVSCHG_SGNL * st_ap_schd_sig)
{
    U1                          u1_t_sig;
    U2                          u2_t_sig;
    U1                          u1_t_sts_plg1g12;

    u1_t_sts_plg1g12 = (U1)Com_GetIPDUStatus(MSG_PLG1G12_RXCH0) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    /* P_SETID */
    st_ap_schd_sig[EVSCHG_ID_P_SETID].u1_sts = u1_t_sts_plg1g12;
    u1_t_sig = (U1)EVSCHG_P_SETID_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_P_SETID, &u1_t_sig);
    st_ap_schd_sig[EVSCHG_ID_P_SETID].u2_sig = (U2)u1_t_sig;

    /* P_SETON */
    st_ap_schd_sig[EVSCHG_ID_P_SETON].u1_sts = u1_t_sts_plg1g12;
    u1_t_sig = (U1)EVSCHG_P_SETON_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_P_SETON, &u1_t_sig);
    st_ap_schd_sig[EVSCHG_ID_P_SETON].u2_sig = (U2)u1_t_sig;

    /* P_SETTYP */
    st_ap_schd_sig[EVSCHG_ID_P_SETTYP].u1_sts = u1_t_sts_plg1g12;
    u1_t_sig = (U1)EVSCHG_P_SETTYP_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_P_SETTYP, &u1_t_sig);
    st_ap_schd_sig[EVSCHG_ID_P_SETTYP].u2_sig = (U2)u1_t_sig;

    /* P_SETSTM */
    st_ap_schd_sig[EVSCHG_ID_P_SETSTM].u1_sts = u1_t_sts_plg1g12;
    u2_t_sig = (U2)EVSCHG_P_SETSTM_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_P_SETSTM, &u2_t_sig);
    st_ap_schd_sig[EVSCHG_ID_P_SETSTM].u2_sig = u2_t_sig;

    /* P_SETFTM */
    st_ap_schd_sig[EVSCHG_ID_P_SETFTM].u1_sts = u1_t_sts_plg1g12;
    u2_t_sig = (U2)EVSCHG_P_SETFTM_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_P_SETFTM, &u2_t_sig);
    st_ap_schd_sig[EVSCHG_ID_P_SETFTM].u2_sig = u2_t_sig;

    /* P_SETWKD */
    st_ap_schd_sig[EVSCHG_ID_P_SETWKD].u1_sts = u1_t_sts_plg1g12;
    u1_t_sig = (U1)EVSCHG_P_SETWKD_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_P_SETWKD, &u1_t_sig);
    st_ap_schd_sig[EVSCHG_ID_P_SETWKD].u2_sig = (U2)u1_t_sig;

    /* P_SETNXT */
    st_ap_schd_sig[EVSCHG_ID_P_SETNXT].u1_sts = u1_t_sts_plg1g12;
    u1_t_sig = (U1)EVSCHG_P_SETNXT_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_P_SETNXT, &u1_t_sig);
    st_ap_schd_sig[EVSCHG_ID_P_SETNXT].u2_sig = (U2)u1_t_sig;
}

/*===================================================================================================================================*/
/* static void             vd_s_EvschgCfgSwquichg(ST_EVSCHG_SGNL * st_ap_sig)                                                        */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  -                                                                                                                    */
/*===================================================================================================================================*/
static void             vd_s_EvschgCfgSwquichg(ST_EVSCHG_SGNL * st_ap_sig)
{
    U1                          u1_t_sig;
    U1                          u1_t_sts_plg1s01;
    U1                          u1_t_sts_plg1g10;
    U1                          u1_t_sts_plg1g14;
    U1                          u1_t_sts_plg1g17;

    u1_t_sts_plg1s01 = (U1)Com_GetIPDUStatus(MSG_PLG1S01_RXCH0) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    u1_t_sts_plg1g10 = (U1)Com_GetIPDUStatus(MSG_PLG1G10_RXCH0) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    u1_t_sts_plg1g14 = (U1)Com_GetIPDUStatus(MSG_PLG1G14_RXCH0) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    u1_t_sts_plg1g17 = (U1)Com_GetIPDUStatus(MSG_PLG1G17_RXCH0) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    /* P_CUR200 */
    st_ap_sig[EVSCHG_ID_P_CUR200].u1_sts = u1_t_sts_plg1s01;
    u1_t_sig = (U1)EVSCHG_P_CUR200_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_P_CUR200, &u1_t_sig);
    st_ap_sig[EVSCHG_ID_P_CUR200].u2_sig = (U2)u1_t_sig;

    /* CBLOCKSU */
    st_ap_sig[EVSCHG_ID_CBLOCKSU].u1_sts = u1_t_sts_plg1s01;
    u1_t_sig = (U1)EVSCHG_CBLOCKSU_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_CBLOCKSU, &u1_t_sig);
    st_ap_sig[EVSCHG_ID_CBLOCKSU].u2_sig = (U2)u1_t_sig;

    /* P_CURAVA */
    st_ap_sig[EVSCHG_ID_P_CURAVA].u1_sts = u1_t_sts_plg1g17;
    u1_t_sig = (U1)EVSCHG_P_CURAVA_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_P_CURAVA, &u1_t_sig);
    st_ap_sig[EVSCHG_ID_P_CURAVA].u2_sig = (U2)u1_t_sig;

    /* P_CLCAVA */
    st_ap_sig[EVSCHG_ID_P_CLCAVA].u1_sts = u1_t_sts_plg1g17;
    u1_t_sig = (U1)EVSCHG_P_CLCAVA_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_P_CLCAVA, &u1_t_sig);
    st_ap_sig[EVSCHG_ID_P_CLCAVA].u2_sig = (U2)u1_t_sig;

    /* P_LMTAVA */
    st_ap_sig[EVSCHG_ID_P_LMTAVA].u1_sts = u1_t_sts_plg1g17;
    u1_t_sig = (U1)EVSCHG_P_LMTAVA_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_P_LMTAVA, &u1_t_sig);
    st_ap_sig[EVSCHG_ID_P_LMTAVA].u2_sig = (U2)u1_t_sig;

    /* P_LMTNOW */
    st_ap_sig[EVSCHG_ID_P_LMTNOW].u1_sts = u1_t_sts_plg1g17;
    u1_t_sig = (U1)EVSCHG_P_LMTNOW_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_P_LMTNOW, &u1_t_sig);
    st_ap_sig[EVSCHG_ID_P_LMTNOW].u2_sig = (U2)u1_t_sig;

    /* P_LMTSEL */
    st_ap_sig[EVSCHG_ID_P_LMTSEL].u1_sts = u1_t_sts_plg1g17;
    u1_t_sig = (U1)EVSCHG_P_LMTSEL_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_P_LMTSEL, &u1_t_sig);
    st_ap_sig[EVSCHG_ID_P_LMTSEL].u2_sig = (U2)u1_t_sig;

    /* P_DPWAVA */
    st_ap_sig[EVSCHG_ID_P_DPWAVA].u1_sts = u1_t_sts_plg1g14;
    u1_t_sig = (U1)EVSCHG_P_DPWAVA_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_P_DPWAVA, &u1_t_sig);
    st_ap_sig[EVSCHG_ID_P_DPWAVA].u2_sig = (U2)u1_t_sig;

    /* P_DPW */
    st_ap_sig[EVSCHG_ID_P_DPW].u1_sts = u1_t_sts_plg1g10;
    u1_t_sig = (U1)EVSCHG_P_DPW_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_P_DPW, &u1_t_sig);
    st_ap_sig[EVSCHG_ID_P_DPW].u2_sig = (U2)u1_t_sig;

    /* P_DPWSL0 */
    st_ap_sig[EVSCHG_ID_P_DPWSL0].u1_sts = u1_t_sts_plg1g14;
    u1_t_sig = (U1)EVSCHG_P_DPWSL0_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_P_DPWSL0, &u1_t_sig);
    st_ap_sig[EVSCHG_ID_P_DPWSL0].u2_sig = (U2)u1_t_sig;

    /* P_DPWSL1 */
    st_ap_sig[EVSCHG_ID_P_DPWSL1].u1_sts = u1_t_sts_plg1g14;
    u1_t_sig = (U1)EVSCHG_P_DPWSL1_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_P_DPWSL1, &u1_t_sig);
    st_ap_sig[EVSCHG_ID_P_DPWSL1].u2_sig = (U2)u1_t_sig;

    /* P_DPWSL2 */
    st_ap_sig[EVSCHG_ID_P_DPWSL2].u1_sts = u1_t_sts_plg1g14;
    u1_t_sig = (U1)EVSCHG_P_DPWSL2_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_P_DPWSL2, &u1_t_sig);
    st_ap_sig[EVSCHG_ID_P_DPWSL2].u2_sig = (U2)u1_t_sig;

    /* P_DPWSL3 */
    st_ap_sig[EVSCHG_ID_P_DPWSL3].u1_sts = u1_t_sts_plg1g14;
    u1_t_sig = (U1)EVSCHG_P_DPWSL3_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_P_DPWSL3, &u1_t_sig);
    st_ap_sig[EVSCHG_ID_P_DPWSL3].u2_sig = (U2)u1_t_sig;

    /* P_DPWSL4 */
    st_ap_sig[EVSCHG_ID_P_DPWSL4].u1_sts = u1_t_sts_plg1g14;
    u1_t_sig = (U1)EVSCHG_P_DPWSL4_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_P_DPWSL4, &u1_t_sig);
    st_ap_sig[EVSCHG_ID_P_DPWSL4].u2_sig = (U2)u1_t_sig;

    /* P_DPWSL5 */
    st_ap_sig[EVSCHG_ID_P_DPWSL5].u1_sts = u1_t_sts_plg1g14;
    u1_t_sig = (U1)EVSCHG_P_DPWSL5_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_P_DPWSL5, &u1_t_sig);
    st_ap_sig[EVSCHG_ID_P_DPWSL5].u2_sig = (U2)u1_t_sig;

    /* P_DPWSL6 */
    st_ap_sig[EVSCHG_ID_P_DPWSL6].u1_sts = u1_t_sts_plg1g14;
    u1_t_sig = (U1)EVSCHG_P_DPWSL6_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_P_DPWSL6, &u1_t_sig);
    st_ap_sig[EVSCHG_ID_P_DPWSL6].u2_sig = (U2)u1_t_sig;

    /* P_DPWSL7 */
    st_ap_sig[EVSCHG_ID_P_DPWSL7].u1_sts = u1_t_sts_plg1g14;
    u1_t_sig = (U1)EVSCHG_P_DPWSL7_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_P_DPWSL7, &u1_t_sig);
    st_ap_sig[EVSCHG_ID_P_DPWSL7].u2_sig = (U2)u1_t_sig;

    /* P_DPWSL8 */
    st_ap_sig[EVSCHG_ID_P_DPWSL8].u1_sts = u1_t_sts_plg1g14;
    u1_t_sig = (U1)EVSCHG_P_DPWSL8_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_P_DPWSL8, &u1_t_sig);
    st_ap_sig[EVSCHG_ID_P_DPWSL8].u2_sig = (U2)u1_t_sig;

    /* P_DPWSL9 */
    st_ap_sig[EVSCHG_ID_P_DPWSL9].u1_sts = u1_t_sts_plg1g14;
    u1_t_sig = (U1)EVSCHG_P_DPWSL9_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_P_DPWSL9, &u1_t_sig);
    st_ap_sig[EVSCHG_ID_P_DPWSL9].u2_sig = (U2)u1_t_sig;

    /* P_TMRAVA */
    st_ap_sig[EVSCHG_ID_P_TMRAVA].u1_sts = u1_t_sts_plg1g17;
    u1_t_sig = (U1)EVSCHG_P_TMRAVA_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_P_TMRAVA, &u1_t_sig);
    st_ap_sig[EVSCHG_ID_P_TMRAVA].u2_sig = (U2)u1_t_sig;

    /* P_SLMAVA */
    st_ap_sig[EVSCHG_ID_P_SLMAVA].u1_sts = u1_t_sts_plg1g17;
    u1_t_sig = (U1)EVSCHG_P_SLMAVA_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_P_SLMAVA, &u1_t_sig);
    st_ap_sig[EVSCHG_ID_P_SLMAVA].u2_sig = (U2)u1_t_sig;

    /* P_CURSL1 */
    st_ap_sig[EVSCHG_ID_P_CURSL1].u1_sts = u1_t_sts_plg1s01;
    u1_t_sig = (U1)EVSCHG_P_CURSL1_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_P_CURSL1, &u1_t_sig);
    st_ap_sig[EVSCHG_ID_P_CURSL1].u2_sig = (U2)u1_t_sig;

    /* P_CURSL2 */
    st_ap_sig[EVSCHG_ID_P_CURSL2].u1_sts = u1_t_sts_plg1s01;
    u1_t_sig = (U1)EVSCHG_P_CURSL2_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_P_CURSL2, &u1_t_sig);
    st_ap_sig[EVSCHG_ID_P_CURSL2].u2_sig = (U2)u1_t_sig;

    /* P_CURSL3 */
    st_ap_sig[EVSCHG_ID_P_CURSL3].u1_sts = u1_t_sts_plg1s01;
    u1_t_sig = (U1)EVSCHG_P_CURSL3_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_P_CURSL3, &u1_t_sig);
    st_ap_sig[EVSCHG_ID_P_CURSL3].u2_sig = (U2)u1_t_sig;

    /* P_CURSL4 */
    st_ap_sig[EVSCHG_ID_P_CURSL4].u1_sts = u1_t_sts_plg1s01;
    u1_t_sig = (U1)EVSCHG_P_CURSL4_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_P_CURSL4, &u1_t_sig);
    st_ap_sig[EVSCHG_ID_P_CURSL4].u2_sig = (U2)u1_t_sig;
}

/*===================================================================================================================================*/
/* static void             vd_s_EvschgCfgSendM_SETSTM(const U2 u2_a_RXDATA)                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  -                                                                                                                    */
/*===================================================================================================================================*/
static void             vd_s_EvschgCfgSendM_SETSTM(const U2 u2_a_RXDATA)
{
    U2                          u2_t_tx;
    U2                          u2_t_pre_tx;

    if ((u2_a_RXDATA <= (U2)EVSCHG_M_SETSTM_MAX ) ||
        (u2_a_RXDATA == (U2)EVSCHG_M_SETSTM_INIT)) {
        u2_t_tx = u2_a_RXDATA;
    }
    else {
        u2_t_tx = (U2)EVSCHG_M_SETSTM_INIT;
    }

    u2_t_pre_tx = (U2)EVSCHG_M_SETSTM_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_M_SETSTM, &u2_t_pre_tx);
    (void)Com_SendSignal(ComConf_ComSignal_M_SETSTM, &u2_t_tx);

    if(u2_t_pre_tx != u2_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S61_TXCH0);
    }
}

/*===================================================================================================================================*/
/* static void             vd_s_EvschgCfgSendM_SETFTM(const U2 u2_a_RXDATA)                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  -                                                                                                                    */
/*===================================================================================================================================*/
static void             vd_s_EvschgCfgSendM_SETFTM(const U2 u2_a_RXDATA)
{
    U2                          u2_t_tx;
    U2                          u2_t_pre_tx;

    if ((u2_a_RXDATA <= (U2)EVSCHG_M_SETFTM_MAX ) ||
        (u2_a_RXDATA == (U2)EVSCHG_M_SETFTM_INIT)) {
        u2_t_tx = u2_a_RXDATA;
    }
    else {
        u2_t_tx = (U2)EVSCHG_M_SETFTM_INIT;
    }

    u2_t_pre_tx = (U2)EVSCHG_M_SETFTM_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_M_SETFTM, &u2_t_pre_tx);
    (void)Com_SendSignal(ComConf_ComSignal_M_SETFTM, &u2_t_tx);

    if(u2_t_pre_tx != u2_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S61_TXCH0);
    }
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version         Date        Author  Change Description                                                                           */
/* ---------------  ----------  ------  ---------------------------------------------------------------------------------------------*/
/*  1.0.0           2022.11.15  ToK     New                                                                                          */
/*                                                                                                                                   */
/*  * ToK = Toru Kamishina, Denso Techno                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
