/* 5.3.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert H_QUICHA                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_H_QUICHA_C_MAJOR                   (5)
#define ALERT_H_QUICHA_C_MINOR                   (3)
#define ALERT_H_QUICHA_C_PATCH                   (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_mtrx_cfg_private.h"
#include "alert_brx.h"

#include "oxcan.h"
#if 0   /* BEV BSW provisionally */
#else
#include "Com_Cfg_STUB.h"
#include "oxcan_channel_STUB.h"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (ALERT_H_QUICHA_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_H_QUICHA.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_H_QUICHA_CHG_NUM_DST               (29U)
#define ALERT_H_QUICHA_LID_NUM_DST               (8U)
#define ALERT_H_QUICHA_TT_NUM_DST                (64U)
#define ALERT_H_QUICHA_DCHG_NUM_DST              (32U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1      u1_s_alert_h_quicha_msgsts_lid;
static U1      u1_s_alert_h_quicha_msgsts_lpg10;
static U1      u1_s_alert_h_quicha_msgsts_lpg11;
static U1      u1_s_alert_h_quicha_msgsts_tt;
static U4      u4_s_alert_h_quicha_igoff_dspcnt;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_AlertH_quichaChgSrcchk (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertH_quichaLidSrcchk (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertH_quichaTtSrcchk  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertH_quichaDchgSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U4  u4_sp_ALERT_H_QUICHA_CHG_CRIT[ALERT_H_QUICHA_CHG_NUM_DST] = {
    (U4)0x02000920U,                                                           /* 00 BAT_TMP                                         */
    (U4)0x02000CE0U,                                                           /* 01 BAT_TMP                                         */
    (U4)0x02000A20U,                                                           /* 02 CHK_AC                                          */
    (U4)0x02000A60U,                                                           /* 03 CHK_FAC                                         */
    (U4)0x020009E0U,                                                           /* 04 CHK_PLG                                         */
    (U4)0x02000EA0U,                                                           /* 05 CHK_VHCL                                        */
    (U4)0x02000860U,                                                           /* 06 CMP                                             */
    (U4)0x02000861U,                                                           /* 07 CMPLMT                                          */
    (U4)0x02000862U,                                                           /* 08 CMPLMT                                          */
    (U4)0x02000863U,                                                           /* 09 CMPLMT                                          */
    (U4)0x02000864U,                                                           /* 10 CMPLMT                                          */
    (U4)0x02000865U,                                                           /* 11 CMPLMT                                          */
    (U4)0x02000866U,                                                           /* 12 CMPLMT                                          */
    (U4)0x02000867U,                                                           /* 13 CMP                                             */
    (U4)0x02000868U,                                                           /* 14 CMP                                             */
    (U4)0x02000870U,                                                           /* 15 CMP                                             */
    (U4)0x02000960U,                                                           /* 16 HI_ENRGY                                        */
    (U4)0x020008E0U,                                                           /* 17 MLFNC                                           */
    (U4)0x02000AE0U,                                                           /* 18 PARTS                                           */
    (U4)0x020009A0U,                                                           /* 19 PULLD                                           */
    (U4)0x02000E20U,                                                           /* 20 TM_LMT                                          */
    (U4)0x02000AA0U,                                                           /* 21 TMP_LOW                                         */
    (U4)0x02000B20U,                                                           /* 22 UNLK_CHG                                        */
    (U4)0x02000B60U,                                                           /* 23 PLUG_CHG                                        */
    (U4)0x02000EE0U,                                                           /* 24 PLUG_CHG                                        */
    (U4)0x02001460U,                                                           /* 25 LOW_TEMP                                        */
    (U4)0x020014A0U,                                                           /* 26 VEH_PRTCT                                       */
    (U4)0x02001860U,                                                           /* 27 LOW_TEMP                                        */
    (U4)0x020018A0U                                                            /* 28 VEH_PRTCT                                       */
};
static const U4  u4_sp_ALERT_H_QUICHA_CHG_MASK[ALERT_H_QUICHA_CHG_NUM_DST] = {
    (U4)0x0200FFE0U,                                                           /* 00 BAT_TMP                                         */
    (U4)0x0200FFE0U,                                                           /* 01 BAT_TMP                                         */
    (U4)0x0200FFE0U,                                                           /* 02 CHK_AC                                          */
    (U4)0x0200FBE0U,                                                           /* 03 CHK_FAC                                         */
    (U4)0x0200FFE0U,                                                           /* 04 CHK_PLG                                         */
    (U4)0x0200FFE0U,                                                           /* 05 CHK_VHCL                                        */
    (U4)0x0200FBFFU,                                                           /* 06 CMP                                             */
    (U4)0x0200FBFFU,                                                           /* 07 CMPLMT                                          */
    (U4)0x0200FBFFU,                                                           /* 08 CMPLMT                                          */
    (U4)0x0200FBFFU,                                                           /* 09 CMPLMT                                          */
    (U4)0x0200FBFFU,                                                           /* 10 CMPLMT                                          */
    (U4)0x0200FBFFU,                                                           /* 11 CMPLMT                                          */
    (U4)0x0200FBFFU,                                                           /* 12 CMPLMT                                          */
    (U4)0x0200FBFFU,                                                           /* 13 CMP                                             */
    (U4)0x0200FBF8U,                                                           /* 14 CMP                                             */
    (U4)0x0200FBF0U,                                                           /* 15 CMP                                             */
    (U4)0x0200FFE0U,                                                           /* 16 HI_ENRGY                                        */
    (U4)0x0200FFE0U,                                                           /* 17 MLFNC                                           */
    (U4)0x0200FFE0U,                                                           /* 18 PARTS                                           */
    (U4)0x0200FFE0U,                                                           /* 19 PULLD                                           */
    (U4)0x0200FFE0U,                                                           /* 20 TM_LMT                                          */
    (U4)0x0200FFE0U,                                                           /* 21 TMP_LOW                                         */
    (U4)0x0200FFE0U,                                                           /* 22 UNLK_CHG                                        */
    (U4)0x0200FFE0U,                                                           /* 23 PLUG_CHG                                        */
    (U4)0x0200FFE0U,                                                           /* 24 PLUG_CHG                                        */
    (U4)0x0200FFE0U,                                                           /* 25 LOW_TEMP                                        */
    (U4)0x0200FFE0U,                                                           /* 26 VEH_PRTCT                                       */
    (U4)0x0200FFE0U,                                                           /* 27 LOW_TEMP                                        */
    (U4)0x0200FFE0U                                                            /* 28 VEH_PRTCT                                       */
};
static const U1  u1_sp_ALERT_H_QUICHA_CHG_DST[ALERT_H_QUICHA_CHG_NUM_DST] = {
    (U1)ALERT_REQ_H_QUICHA_CHG_BAT_TMP,                                        /* 00 BAT_TMP                                         */
    (U1)ALERT_REQ_H_QUICHA_CHG_BAT_TMP,                                        /* 01 BAT_TMP                                         */
    (U1)ALERT_REQ_H_QUICHA_CHG_CHK_AC,                                         /* 02 CHK_AC                                          */
    (U1)ALERT_REQ_H_QUICHA_CHG_CHK_FAC,                                        /* 03 CHK_FAC                                         */
    (U1)ALERT_REQ_H_QUICHA_CHG_CHK_PLG,                                        /* 04 CHK_PLG                                         */
    (U1)ALERT_REQ_H_QUICHA_CHG_CHK_VHCL,                                       /* 05 CHK_VHCL                                        */
    (U1)ALERT_REQ_H_QUICHA_CHG_CMP,                                            /* 06 CMP                                             */
    (U1)ALERT_REQ_H_QUICHA_CHG_CMPLMT,                                         /* 07 CMPLMT                                          */
    (U1)ALERT_REQ_H_QUICHA_CHG_CMPLMT,                                         /* 08 CMPLMT                                          */
    (U1)ALERT_REQ_H_QUICHA_CHG_CMPLMT,                                         /* 09 CMPLMT                                          */
    (U1)ALERT_REQ_H_QUICHA_CHG_CMPLMT,                                         /* 10 CMPLMT                                          */
    (U1)ALERT_REQ_H_QUICHA_CHG_CMPLMT,                                         /* 11 CMPLMT                                          */
    (U1)ALERT_REQ_H_QUICHA_CHG_CMPLMT,                                         /* 12 CMPLMT                                          */
    (U1)ALERT_REQ_H_QUICHA_CHG_CMP,                                            /* 13 CMP                                             */
    (U1)ALERT_REQ_H_QUICHA_CHG_CMP,                                            /* 14 CMP                                             */
    (U1)ALERT_REQ_H_QUICHA_CHG_CMP,                                            /* 15 CMP                                             */
    (U1)ALERT_REQ_H_QUICHA_CHG_HI_ENRGY,                                       /* 16 HI_ENRGY                                        */
    (U1)ALERT_REQ_H_QUICHA_CHG_MLFNC,                                          /* 17 MLFNC                                           */
    (U1)ALERT_REQ_H_QUICHA_CHG_PARTS,                                          /* 18 PARTS                                           */
    (U1)ALERT_REQ_H_QUICHA_CHG_PULLD,                                          /* 19 PULLD                                           */
    (U1)ALERT_REQ_H_QUICHA_CHG_TM_LMT,                                         /* 20 TM_LMT                                          */
    (U1)ALERT_REQ_H_QUICHA_CHG_TMP_LOW,                                        /* 21 TMP_LOW                                         */
    (U1)ALERT_REQ_H_QUICHA_CHG_UNLK_CHG,                                       /* 22 UNLK_CHG                                        */
    (U1)ALERT_REQ_H_QUICHA_CHG_PLUG_CHG,                                       /* 23 PLUG_CHG                                        */
    (U1)ALERT_REQ_H_QUICHA_CHG_PLUG_CHG,                                       /* 24 PLUG_CHG                                        */
    (U1)ALERT_REQ_H_QUICHA_CHG_LOW_TEMP,                                       /* 25 LOW_TEMP                                        */
    (U1)ALERT_REQ_H_QUICHA_CHG_VEH_PRTCT,                                      /* 26 VEH_PRTCT                                       */
    (U1)ALERT_REQ_H_QUICHA_CHG_LOW_TEMP,                                       /* 27 LOW_TEMP                                        */
    (U1)ALERT_REQ_H_QUICHA_CHG_VEH_PRTCT                                       /* 28 VEH_PRTCT                                       */
};
static const U1  u1_sp_ALERT_H_QUICHA_LID_DST[ALERT_H_QUICHA_LID_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 01 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_H_QUICHA_LID_OPEN,                                           /* 05 OPEN                                            */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 07 UNKNOWN                                         */
};
static const U1  u1_sp_ALERT_H_QUICHA_TT_DST[ALERT_H_QUICHA_TT_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 01 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 08 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 09 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 10 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 11 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 13 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 14 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 15 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 16 UNKNOWN                                         */
    (U1)ALERT_REQ_H_QUICHA_TT_ON,                                              /* 17 ON                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 18 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 19 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 20 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 21 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 22 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 23 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 24 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 25 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 26 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 27 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 28 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 29 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 30 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 31 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 32 UNKNOWN                                         */
    (U1)ALERT_REQ_H_QUICHA_TT_ON,                                              /* 33 ON                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 34 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 35 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 36 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 37 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 38 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 39 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 40 UNKNOWN                                         */
    (U1)ALERT_REQ_H_QUICHA_TT_ON,                                              /* 41 ON                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 42 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 43 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 44 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 45 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 46 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 47 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 48 UNKNOWN                                         */
    (U1)ALERT_REQ_H_QUICHA_TT_ON,                                              /* 49 ON                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 50 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 51 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 52 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 53 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 54 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 55 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 56 UNKNOWN                                         */
    (U1)ALERT_REQ_H_QUICHA_TT_ON,                                              /* 57 ON                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 58 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 59 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 60 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 61 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 62 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 63 UNKNOWN                                         */
};
static const U1  u1_sp_ALERT_H_QUICHA_DCHG_DST[ALERT_H_QUICHA_DCHG_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_H_QUICHA_DCHG_CCS_CON,                                       /* 01 CCS_CON                                         */
    (U1)ALERT_REQ_H_QUICHA_DCHG_CCS,                                           /* 02 CCS                                             */
    (U1)ALERT_REQ_H_QUICHA_DCHG_CCS_END,                                       /* 03 CCS_END                                         */
    (U1)ALERT_REQ_H_QUICHA_DCHG_CCS_CMP,                                       /* 04 CCS_CMP                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 08 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 09 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 10 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 11 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 13 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 14 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 15 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 16 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 17 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 18 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 19 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 20 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 21 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 22 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 23 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 24 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 25 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 26 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 27 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 28 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 29 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 30 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 31 UNKNOWN                                         */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_H_QUICHA_MTRX[4] = {
    {
        &u4_s_AlertH_quichaChgSrcchk,                                          /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        &u4_sp_ALERT_H_QUICHA_CHG_MASK[0],                                     /* u4p_MASK                                           */
        &u4_sp_ALERT_H_QUICHA_CHG_CRIT[0],                                     /* u4p_CRIT                                           */

        &u1_sp_ALERT_H_QUICHA_CHG_DST[0],                                      /* u1p_DST                                            */
        (U2)ALERT_H_QUICHA_CHG_NUM_DST,                                        /* u2_num_srch                                        */
        (U1)ALERT_VOM_BAT_WT                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertH_quichaLidSrcchk,                                          /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_H_QUICHA_LID_DST[0],                                      /* u1p_DST                                            */
        (U2)ALERT_H_QUICHA_LID_NUM_DST,                                        /* u2_num_srch                                        */
        (U1)ALERT_VOM_BAT_WT                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertH_quichaTtSrcchk,                                           /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_H_QUICHA_TT_DST[0],                                       /* u1p_DST                                            */
        (U2)ALERT_H_QUICHA_TT_NUM_DST,                                         /* u2_num_srch                                        */
        (U1)ALERT_VOM_BAT_WT                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertH_quichaDchgSrcchk,                                         /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_H_QUICHA_DCHG_DST[0],                                     /* u1p_DST                                            */
        (U2)ALERT_H_QUICHA_DCHG_NUM_DST,                                       /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_AlertH_quichaInit(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AlertH_quichaInit(void)
{
    u1_s_alert_h_quicha_msgsts_lpg10 = (U1)COM_NO_RX;
    u1_s_alert_h_quicha_msgsts_lpg11 = (U1)COM_NO_RX;
    u1_s_alert_h_quicha_msgsts_lid   = (U1)COM_NO_RX;
    u1_s_alert_h_quicha_msgsts_tt    = (U1)COM_NO_RX;
    u4_s_alert_h_quicha_igoff_dspcnt = (U4)0U;
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertH_quichaChgSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertH_quichaChgSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U1 u1_s_ALERT_H_QUICHA_CHG_LSB_PL10 = (U1)14U;
    static const U1 u1_s_ALERT_H_QUICHA_CHG_LSB_PID8 = (U1)6U;
    static const U1 u1_s_ALERT_H_QUICHA_CHG_LSB_PIDS = (U1)5U;
    static const U1 u1_s_ALERT_H_QUICHA_CHG_LSB_PL11 = (U1)3U;
    static const U2 u2_s_ALERT_H_QUICHA_CHG_TRSH_P10 = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U2 u2_s_ALERT_H_QUICHA_CHG_TRSH_P11 = ((U2)5000U / (U2)OXCAN_MAIN_TICK);

    U4              u4_t_src_chk;
    U1              u1_t_sgnl;
    U1              u1_t_msgsts;
    U1              u1_t_isenable;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_PLG1G10,
                                     (U2)OXCAN_RX_SYS_NRX_BAT | (U2)OXCAN_RX_SYS_TOE_BAT,
                                     u2_s_ALERT_H_QUICHA_CHG_TRSH_P10) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);


    vd_g_AlertBRxTrnsSts(&u1_s_alert_h_quicha_msgsts_lpg10, u1_t_msgsts);
    u4_t_src_chk  = ((U4)u1_s_alert_h_quicha_msgsts_lpg10 << u1_s_ALERT_H_QUICHA_CHG_LSB_PL10);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_PIINFD08, &u1_t_sgnl);

    u4_t_src_chk |= ((U4)u1_t_sgnl                        << u1_s_ALERT_H_QUICHA_CHG_LSB_PID8);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_PIINFDSP, &u1_t_sgnl);

    u4_t_src_chk |= ((U4)u1_t_sgnl                        << u1_s_ALERT_H_QUICHA_CHG_LSB_PIDS);

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_PLG1G11,
                                     (U2)OXCAN_RX_SYS_NRX_BAT | (U2)OXCAN_RX_SYS_TOE_BAT,
                                     u2_s_ALERT_H_QUICHA_CHG_TRSH_P11) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    vd_g_AlertBRxTrnsSts(&u1_s_alert_h_quicha_msgsts_lpg11, u1_t_msgsts);

    u4_t_src_chk |= ((U4)u1_s_alert_h_quicha_msgsts_lpg11 << u1_s_ALERT_H_QUICHA_CHG_LSB_PL11);

    u1_t_isenable = u1_g_AlertCfgNCLMTIsEnable();

    u1_t_sgnl     = (U1)0U;
    if(u1_t_isenable == (U1)TRUE){
        (void)Com_ReceiveSignal(ComConf_ComSignal_P_NCLMT, &u1_t_sgnl);
    }

    u4_t_src_chk |= (U4)u1_t_sgnl;

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertH_quichaLidSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertH_quichaLidSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_H_QUICHA_LID_TO_THRSH = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_H_QUICHA_LID_LSB_PLG  = (U1)1U;
    static const U4 u4_s_ALERT_H_QUICHA_LID_BAT_WT   = (U4)0x00000004U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_PLG1G10,
                                     (U2)OXCAN_RX_SYS_NRX_BAT | (U2)OXCAN_RX_SYS_TOE_BAT,
                                     u2_s_ALERT_H_QUICHA_LID_TO_THRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    if((u1_a_VOM & (U1)ALERT_VOM_IGN_ON) == (U1)0U){
        u1_t_msgsts  |= (U1)ALERT_BRX_FACT_NO_RX;
    }
    vd_g_AlertBRxTrnsSts(&u1_s_alert_h_quicha_msgsts_lid, u1_t_msgsts);

    u4_t_src_chk  = ((U4)u1_s_alert_h_quicha_msgsts_lid & (U4)COM_NO_RX) << u1_s_ALERT_H_QUICHA_LID_LSB_PLG;

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_PLID_DSP, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl;

    if((u1_a_VOM & (U1)ALERT_VOM_BAT_WT) != (U1)0U){
        u4_t_src_chk |= u4_s_ALERT_H_QUICHA_LID_BAT_WT;
    }

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertH_quichaTtSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertH_quichaTtSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_H_QUICHA_TT_TO_THRSH  = ((U2)5000U    / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_H_QUICHA_TT_LSB_PLG   = (U1)1U;
    static const U4 u4_s_ALERT_H_QUICHA_TT_DSPTM     = ((U4)1200000U / (U4)ALERT_CH_TICK);
    static const U4 u4_s_ALERT_H_QUICHA_TT_BIT_DSP   = (U4)0x00000008U;
    static const U4 u4_s_ALERT_H_QUICHA_TT_BIT_OFFWT = (U4)0x00000010U;
    static const U4 u4_s_ALERT_H_QUICHA_TT_BIT_IGON  = (U4)0x00000020U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_PLG1S01_RXCH0,
                                     (U2)OXCAN_RX_SYS_NRX_BAT | (U2)OXCAN_RX_SYS_TOE_BAT,
                                     u2_s_ALERT_H_QUICHA_TT_TO_THRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    vd_g_AlertBRxTrnsSts(&u1_s_alert_h_quicha_msgsts_tt, u1_t_msgsts);

    u4_t_src_chk  = ((U4)u1_s_alert_h_quicha_msgsts_tt << u1_s_ALERT_H_QUICHA_TT_LSB_PLG);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_PCNCTIND, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl;

    if(((u1_a_VOM & (U1)ALERT_VOM_IGN_ON)                                   != (U1)0U) ||
       ((u1_s_alert_h_quicha_msgsts_tt & ((U1)COM_TIMEOUT | (U1)COM_NO_RX)) != (U1)0U) ||
        (u1_t_sgnl                                                          == (U1)0U)){
        u4_s_alert_h_quicha_igoff_dspcnt = (U4)0U;
    }
    else if(u4_s_ALERT_H_QUICHA_TT_DSPTM <= u4_s_alert_h_quicha_igoff_dspcnt){
        u4_t_src_chk                    |= u4_s_ALERT_H_QUICHA_TT_BIT_DSP;
        u4_s_alert_h_quicha_igoff_dspcnt = u4_s_ALERT_H_QUICHA_TT_DSPTM;
    }
    else{
        u4_s_alert_h_quicha_igoff_dspcnt++;
    }

    if((u1_a_VOM & (U1)ALERT_VOM_IGN_OFF_WT) != (U1)0U){
        u4_t_src_chk |= u4_s_ALERT_H_QUICHA_TT_BIT_OFFWT;
    }

    if((u1_a_VOM & (U1)ALERT_VOM_IGN_ON) != (U1)0U){
        u4_t_src_chk |= u4_s_ALERT_H_QUICHA_TT_BIT_IGON;
    }

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertH_quichaDchgSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertH_quichaDchgSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_H_QUICHA_DCHG_TRSH_PL = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_H_QUICHA_DCHG_LSB_PLG = (U1)3U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;
    U1              u1_t_isenable;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_PLG1G10,
                                     (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                     u2_s_ALERT_H_QUICHA_DCHG_TRSH_PL) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u4_t_src_chk  = ((U4)u1_t_msgsts << u1_s_ALERT_H_QUICHA_DCHG_LSB_PLG);

    u1_t_isenable = u1_g_AlertCfgDCRCKDSPIsEnable();

    u1_t_sgnl     = (U1)0U;
    if(u1_t_isenable == (U1)TRUE){
        (void)Com_ReceiveSignal(ComConf_ComSignal_DCRCKDSP, &u1_t_sgnl);
    }

    u4_t_src_chk |= (U4)u1_t_sgnl;

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
/*  5.0.0    10/26/2020  MO       New.                                                                                               */
/*  5.0.1     2/ 8/2021  RI       Modified variable name.                                                                            */
/*  5.1.0     4/ 9/2021  SO       Change matrix table for CHG/TT, and change power state and srcchk logic for TT.                    */
/*  5.1.1     6/30/2021  MO       Update for 050D CV(Version update).                                                                */
/*  5.2.0     7/13/2022  SAO      Change Constant definition config for P_NCLMT/DCRCKDSP.                                            */
/*  5.3.0     3/26/2024  GM       Update for 19PFv3: Add 4 Request ID for MID.                                                       */
/*                                                                                                                                   */
/*  * MO   = Masayuki Oofuji, NTTD MSE                                                                                               */
/*  * RI   = Ren Itou, NTTD MSE                                                                                                      */
/*  * SO   = Syuhei Ooshima, NTTD MSE                                                                                                */
/*  * SAO  = Sachiko Oono, NTTD MSE                                                                                                  */
/*  * GM   = Glen Monteposo, DTPH                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
