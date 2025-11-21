/* 1.9.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  DENSO ICT1 Coding Style Standard Template                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define HMITT_CFG_C_MAJOR                     (1)
#define HMITT_CFG_C_MINOR                     (9)
#define HMITT_CFG_C_PATCH                     (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "hmitt_cfg_private.h"
#include "hmitt_if_cfg.h"

#include "alert.h"
#include "thblnkr.h"
#include "ambtmp.h"
#include "sbltsync.h"

#include "vardef.h"
#include "vardef_dest_dbf.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((HMITT_CFG_C_MAJOR != HMITT_H_MAJOR) || \
     (HMITT_CFG_C_MINOR != HMITT_H_MINOR) || \
     (HMITT_CFG_C_PATCH != HMITT_H_PATCH))
#error "hmitt_cfg.c and hmitt.h : source and header files are inconsistent!"
#endif

#if ((HMITT_CFG_C_MAJOR != HMITT_CFG_H_MAJOR) || \
     (HMITT_CFG_C_MINOR != HMITT_CFG_H_MINOR) || \
     (HMITT_CFG_C_PATCH != HMITT_CFG_H_PATCH))
#error "hmitt_cfg.c and hmitt_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define HMITT_4BIT_SHIFT                          (4U)
#define HMITT_8BIT_SHIFT                          (8U)
#define HMITT_12BIT_SHIFT                         (12U)
#define HMITT_16BIT_SHIFT                         (16U)
#define HMITT_20BIT_SHIFT                         (20U)
#define HMITT_28BIT_SHIFT                         (28U)

#define HMITT_VAR_MASK                            (0x0000000FU)

#define HMITT_SBLT_R2L_DATPOS                     (10U)
#define HMITT_SBLT_R2C_DATPOS                     (10U)
#define HMITT_SBLT_R2R_DATPOS                     (10U)
#define HMITT_SBLT_R3L_DATPOS                     (15U)
#define HMITT_SBLT_R3C_DATPOS                     (15U)
#define HMITT_SBLT_R3R_DATPOS                     (15U)
#define HMITT_SBLT_R4L_DATPOS                     (23U)
#define HMITT_SBLT_R4C_DATPOS                     (23U)
#define HMITT_SBLT_R4R_DATPOS                     (23U)
#define HMITT_SBLT_FR_DATPOS                      (12U)
#define HMITT_ICEWRN_DATPOS                       (9U)
#define HMITT_REARBLT_DATPOS                      (10U)
#define HMITT_STPIND_DATPOS                       (1U)
#define HMITT_TURN_DATPOS                         (1U)
#define HMITT_HEAD_DATPOS                         (12U)
#define HMITT_TAIL_DATPOS                         (0U)
#define HMITT_TECBLP2_DATPOS                      (9U)

#define HMITT_SBLT_R2L_SFT                        (3U)
#define HMITT_SBLT_R2C_SFT                        (4U)
#define HMITT_SBLT_R2R_SFT                        (5U)
#define HMITT_SBLT_R3L_SFT                        (6U)
#define HMITT_SBLT_R3C_SFT                        (7U)
#define HMITT_SBLT_R3R_SFT                        (8U)
#define HMITT_SBLT_R4L_SFT                        (9U)
#define HMITT_SBLT_R4C_SFT                        (10U)
#define HMITT_SBLT_R4R_SFT                        (11U)
#define HMITT_SBLT_FR_SFT                         (0U)

#define HMITT_TURN_R_SFT                          (4U)
#define HMITT_TURN_L_SFT                          (5U)
#define HMITT_TURN_ACT_SFT                        (6U)

#define HMITT_STPIND_BITPOS                       (8U)
#define HMITT_HEAD_BITPOS                         (0U)
#define HMITT_TAIL_BITPOS                         (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U1                          u1_idx;
    U1                          u1_strtpos;
    U2                          u2_esopt;
    U2                          u2_chid;
    U1                          u1_req;
}ST_HMITT_ESOPT;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void    vd_s_HmiTtTurn(U4 * u4_ap_req);
static void    vd_s_HmiTtTECOLP2(U4* u4_ap_req);
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_HmiTtCfgInit(void)                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiTtCfgInit(void)
{
}
/*===================================================================================================================================*/
/*  void    vd_g_HmiTtCfgReq(U4 * u4_ap_req)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiTtCfgReq(U4 * u4_ap_req)
{

    U4  u4_t_loop;
    U4  u4_t_onoff;
    U2  u2_t_num_reqbit;
    U2  u2_t_belt_tt;
    U1  u1_t_icewrn;
    U1  u1_t_rearbelt_tt;

    for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)HMITT_NUM ; u4_t_loop++){
        u4_ap_req[u4_t_loop] = (U4)0U;
    }

    u2_t_num_reqbit = u2_g_HmittSizeReqbit();
    vd_g_AlertReqToBit( st_gp_HMITTREQBIT, u2_t_num_reqbit, u4_ap_req, (U1)HMITT_NUM);

    u1_t_icewrn = u1_g_AmbtmpIceWrnAct();
    if(u1_t_icewrn == (U1)TRUE){
        u4_ap_req[HMITT_ICEWRN_DATPOS] |= u4_HMITT_HB0(HMITT_BLINK_SI_1P00HZ__50P_10TIMS_E__ON);
    }

    u2_t_belt_tt  = u2_g_SbltsyncReqTt();
    u4_t_onoff    = (((U4)u2_t_belt_tt & (U4)SBLTSYNC_TT_REQ_R2L) >> HMITT_SBLT_R2L_SFT);
    u4_ap_req[HMITT_SBLT_R2L_DATPOS] |= (u4_t_onoff << HMITT_8BIT_SHIFT);
    u4_t_onoff    = (((U4)u2_t_belt_tt & (U4)SBLTSYNC_TT_REQ_R2C) >> HMITT_SBLT_R2C_SFT);
    u4_ap_req[HMITT_SBLT_R2C_DATPOS] |= (u4_t_onoff <<  HMITT_12BIT_SHIFT);
    u4_t_onoff    = (((U4)u2_t_belt_tt & (U4)SBLTSYNC_TT_REQ_R2R) >> HMITT_SBLT_R2R_SFT);
    u4_ap_req[HMITT_SBLT_R2R_DATPOS] |= (u4_t_onoff <<  HMITT_4BIT_SHIFT);
    u4_t_onoff    = (((U4)u2_t_belt_tt & (U4)SBLTSYNC_TT_REQ_R3L) >> HMITT_SBLT_R3L_SFT);
    u4_ap_req[HMITT_SBLT_R3L_DATPOS] |= (u4_t_onoff << HMITT_16BIT_SHIFT);
    u4_t_onoff    = (((U4)u2_t_belt_tt & (U4)SBLTSYNC_TT_REQ_R3C) >> HMITT_SBLT_R3C_SFT);
    u4_ap_req[HMITT_SBLT_R3C_DATPOS] |= (u4_t_onoff <<  HMITT_12BIT_SHIFT);
    u4_t_onoff    = (((U4)u2_t_belt_tt & (U4)SBLTSYNC_TT_REQ_R3R) >> HMITT_SBLT_R3R_SFT);
    u4_ap_req[HMITT_SBLT_R3R_DATPOS] |= (u4_t_onoff <<  HMITT_20BIT_SHIFT);
    u4_t_onoff    = (((U4)u2_t_belt_tt & (U4)SBLTSYNC_TT_REQ_R4L) >> HMITT_SBLT_R4L_SFT);
    u4_ap_req[HMITT_SBLT_R4L_DATPOS] |= (u4_t_onoff <<   HMITT_8BIT_SHIFT);
    u4_t_onoff    = (((U4)u2_t_belt_tt & (U4)SBLTSYNC_TT_REQ_R4C) >> HMITT_SBLT_R4C_SFT);
    u4_ap_req[HMITT_SBLT_R4C_DATPOS] |= (u4_t_onoff <<  HMITT_12BIT_SHIFT);
    u4_t_onoff    = (((U4)u2_t_belt_tt & (U4)SBLTSYNC_TT_REQ_R4R) >> HMITT_SBLT_R4R_SFT);
    u4_ap_req[HMITT_SBLT_R4R_DATPOS] |= (u4_t_onoff <<   HMITT_4BIT_SHIFT);
    u4_t_onoff    = (((U4)u2_t_belt_tt & (U4)SBLTSYNC_TT_REQ_FR) >> HMITT_SBLT_FR_SFT);
    u4_ap_req[HMITT_SBLT_FR_DATPOS] |= (u4_t_onoff <<  HMITT_20BIT_SHIFT);

    u1_t_rearbelt_tt = u1_g_SbltsyncActTt();
    if (u1_t_rearbelt_tt == (U1)TRUE) {
        u4_ap_req[HMITT_REARBLT_DATPOS] |= u4_HMITT_HB4(HMITT_BLINK_CO_ON_____100P);
    }

    vd_s_HmiTtTurn(u4_ap_req);
    vd_s_HmiTtTECOLP2(u4_ap_req);
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_HmiTtTurn(U4 * u4_ap_req)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_HmiTtTurn(U4 * u4_ap_req)
{
    U1  u1_t_turn;
    U1  u1_t_turn_act;

    u1_t_turn = u1_g_ThblnkrIndAct();
    if((u1_t_turn & (U1)THBLNKR_BIT_INDLEFT) != (U1)0U){
        u4_ap_req[HMITT_TURN_DATPOS] |= ((U4)TRUE << HMITT_TURN_L_SFT);
    }
    if((u1_t_turn & (U1)THBLNKR_BIT_INDRIGHT) != (U1)0U){
        u4_ap_req[HMITT_TURN_DATPOS] |= ((U4)TRUE << HMITT_TURN_R_SFT);
    }
    u1_t_turn_act = u1_g_ThblnkrActiveJdg();
    if(u1_t_turn_act == (U1)TRUE){
        u4_ap_req[HMITT_TURN_DATPOS] |= ((U4)TRUE << HMITT_TURN_ACT_SFT);
    }
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_HmiTtTECOLP2(U4 * u4_ap_req)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_HmiTtTECOLP2(U4* u4_ap_req)
{
    U1  u1_t_ptsys;

    u1_t_ptsys = u1_g_VardefPtsRx();
   if((u1_t_ptsys == (U1)VDF_PTS_RX_01_GAS      ) ||
       (u1_t_ptsys == (U1)VDF_PTS_RX_02_GAS_ISS)) {
      /* Do Nothing */
   }
   else{
        u4_ap_req[HMITT_TECBLP2_DATPOS] &= (~((U4)HMITT_VAR_MASK << HMITT_16BIT_SHIFT));
    }
}

/*===================================================================================================================================*/
/*  void    vd_g_HmiTtCfgVarmask(U4 * u4_ap_varmask)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiTtCfgVarmask(U4 * u4_ap_varmask)
{
    static const ST_HMITT_ESOPT st_sp_HMITT_ESOPT[] = {
    /* u1_idx     u1_strtpos   u2_esopt                       u2_chid                           u1_req                                       */
        {  (U1)0U,    (U1)16U,    (U2)VDF_ESO_CH_PEDPRO,        (U2)ALERT_CH_B_PEDPRO,             (U1)ALERT_REQ_B_PEDPRO_DIAGDTRMN             },
        {  (U1)1U,    (U1)12U,    (U2)VDF_ESO_CH_VSC,           (U2)ALERT_CH_C_SLIP,               (U1)ALERT_REQ_C_SLIP_MALFUNC                 },
        {  (U1)1U,    (U1)12U,    (U2)VDF_ESO_CH_VSC,           (U2)ALERT_CH_C_SLIP,               (U1)ALERT_REQ_C_SLIP_MALFUNC_RW              },
        {  (U1)2U,    (U1)28U,    (U2)VDF_ESO_CH_BRPADW,        (U2)ALERT_CH_C_BRPADW,             (U1)ALERT_REQ_C_BRPADW_MALFUNC               },
        {  (U1)3U,    (U1)4U,     (U2)VDF_ESO_CH_BRKHLD,        (U2)ALERT_CH_C_BRKHLD_HLD,         (U1)ALERT_REQ_C_BRKHLD_HLD_FLASH             }
    };

    U4  u4_t_loop;
    U4  u4_t_num;
    U1  u1_t_exist;
    U1  u1_t_bufpos;
    U2  u2_t_chid;
    U1  u1_t_req;

    u4_t_num = (U4)(sizeof(st_sp_HMITT_ESOPT) / sizeof(st_sp_HMITT_ESOPT[0]));
    for(u4_t_loop = (U4)0U ; u4_t_loop < u4_t_num ; u4_t_loop++){
        u1_t_exist = u1_g_VardefEsOptAvaByCh(st_sp_HMITT_ESOPT[u4_t_loop].u2_esopt);
        u2_t_chid  = st_sp_HMITT_ESOPT[u4_t_loop].u2_chid;
        u1_t_req   = u1_g_AlertReqByCh(u2_t_chid);
        if((u1_t_exist == (U1)0U) &&
           (u1_t_req   == st_sp_HMITT_ESOPT[u4_t_loop].u1_req)){
            u1_t_bufpos = st_sp_HMITT_ESOPT[u4_t_loop].u1_idx;
            u4_ap_varmask[u1_t_bufpos] &= (~((U4)HMITT_VAR_MASK << st_sp_HMITT_ESOPT[u4_t_loop].u1_strtpos));
        }
    }
}

/*===================================================================================================================================*/
/*  void    vd_g_HmiTtCfgDestmask(U4 * u4_ap_varmask)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiTtCfgDestmask(U4* u4_ap_varmask)
{
    U1  u1_t_dest;

    u1_t_dest = u1_g_VardefTtTailHead();
    if (u1_t_dest == (U1)VDF_TTTAILHEAD_NO12) {
        u4_ap_varmask[HMITT_TAIL_DATPOS] &= (~((U4)HMITT_VAR_MASK << HMITT_TAIL_BITPOS));
    }
    else {
        u4_ap_varmask[HMITT_HEAD_DATPOS] &= (~((U4)HMITT_VAR_MASK << HMITT_HEAD_BITPOS));
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
/*  1.1.0    04/18/2020  TH       Setting for 800B CV.                                                                               */
/*  1.2.0    09/07/2020  TH       Setting for 800B CV-R.                                                                             */
/*  1.3.0    01/06/2021  TH       Setting for 800B 1A.                                                                               */
/*  1.4.0    06/02/2021  TH       Setting for 22-24FGM CV.                                                                           */
/*  1.5.0    11/10/2023  HF       Setting for 19PFv3 CV.                                                                             */
/*  1.6.0    02/02/2024  DR       Setting for 19PFv3 (add ECOLP2)                                                                    */
/*  1.7.0    06/21/2024  JMH      Setting for 19PFv3 (add LBW)                                                                       */
/*  1.8.0    10/15/2024  KO       hmitt_if_cfg.c v1.6.0 -> v1.8.0. (Setting for BEV System_Consideration_1.)                         */
/*  1.9.0    06/23/2025  HY       hmitt_if_cfg.c v1.8.0 -> v1.9.0. (Setting for BEV System_Consideration_2.)                         */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  19PFv3-1 02/20/2024  GM       Change config for 19PFv3 CV                                                                        */
/*  19PFv3-2 07/08/2024  PG       Add mask process for H_ZMILRQ for 19PFv3 R1.2                                                      */
/*  19PFv3-3 08/23/2024  AA       Add awake status of turn hazard                                                                    */
/*  19PFv3-4 09/17/2024  KH       Change variable name and function call name in vd_s_HmiTtTurn                                      */
/*  BEV-1    10/31/2025  MA       Change for BEV rebase                                                                              */
/*  BEV-2    11/25/2024  KO       Change for BEV System_Consideration_1.(MET-C_ECB-CSTD-1-00-A-C0 / MET-C_EPB-CSTD-1-00-A-C0)        */
/*  BEV-3    12/23/2024  KO       Change for BEV System_Consideration_1.(MET-H_ZMILREQ-CSTD-1-00-A-C0)                               */
/*  BEV-4    02/10/2025  RO       Change for BEV System_Consideration_1.(MET-S_ADTT-CSTD-0-)                                         */
/*  BEV-5    02/10/2025  SF       Change for BEV System_Consideration_1.(MET-M_ONOFF-CSTD-1-02-A-C0)                                 */
/*  BEV-6    06/23/2025  HY       Change for BEV System_Consideration_2.(MET-S_ADMID-CSTD-0-02-A-C0 / MET-S_ADTT-CSTD-0-02-A-C0)     */
/*                                                                                                                                   */
/*  * TA   = Teruyuki Anjima, Denso                                                                                                  */
/*  * TH   = Takahiro Hirano, Denso Techno                                                                                           */
/*  * HF   = Hinari Fukamachi, KSE                                                                                                   */
/*  * DR   = Dyan Reyes, DTPH                                                                                                        */
/*  * GM   = Glen Monteposo, DTPH                                                                                                    */
/*  * JMH  = James Michael D. Hilarion, DTPH                                                                                         */
/*  * PG   = Patrick Garcia, DTPH                                                                                                    */
/*  * AA   = Anna Asuncion, Denso Techno                                                                                             */
/*  * KH   = Kiko Huerte, DTPH                                                                                                       */
/*  * MA   = Misaki Aiki,  Denso Techno                                                                                              */
/*  * KO   = Kazuto Oishi,  Denso Techno                                                                                             */
/*  * RO   = Ryo Oohashi, KSE                                                                                                        */
/*  * SF   = Shiro Furui, Denso Techno                                                                                               */
/*  * HY   = Haruki Yagi, KSE                                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
