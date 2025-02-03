/* 1.2.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  DENSO ICT1 Coding Style Standard Hmimm2c118n                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define HMIMM2C118N_CFG_C_MAJOR                         (1)
#define HMIMM2C118N_CFG_C_MINOR                         (2)
#define HMIMM2C118N_CFG_C_PATCH                         (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "hmiproxy_cfg_private.h"
#include "hmimm2c118n_cfg_private.h"

#include "hmimcst.h"
#include "hmimaint.h"
#include "hmioilmaint.h"
#include "hmivardef.h"
#include "hmihud.h"
#include "hmidiag.h"
#include "hmilcom.h"
#include "vardef.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((HMIMM2C118N_CFG_C_MAJOR != HMIMM2C118N_H_MAJOR) || \
     (HMIMM2C118N_CFG_C_MINOR != HMIMM2C118N_H_MINOR) || \
     (HMIMM2C118N_CFG_C_PATCH != HMIMM2C118N_H_PATCH))
#error "hmimm2c118n.c and hmimm2c118n.h : source and header files are inconsistent!"
#endif

#if ((HMIMM2C118N_CFG_C_MAJOR != HMIMM2C118N_CFG_H_MAJOR) || \
     (HMIMM2C118N_CFG_C_MINOR != HMIMM2C118N_CFG_H_MINOR) || \
     (HMIMM2C118N_CFG_C_PATCH != HMIMM2C118N_CFG_H_PATCH))
#error "hmimm2c118n.c and hmimm2c118n_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define  HMIMM2C118N_1BIT_MAX                           (1U)
#define  HMIMM2C118N_2BIT_MAX                           (3U)
#define  HMIMM2C118N_3BIT_MAX                           (7U)
#define  HMIMM2C118N_4BIT_MAX                           (15U)
#define  HMIMM2C118N_5BIT_MAX                           (31U)
#define  HMIMM2C118N_REVSET_MAX                         (100U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U1 u1_g_HMIMM2C118N_SIG_NUM     = (U1)HMIMM2C118N_SIG_NUM;
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1   u1_s_Mm2c118nReadSig(const U1 u1_a_SIG_IDX, const U4 * u4_ap_REQ);
static void vd_s_Mm2c118nSendMaintere(const U1 u1_a_SIG);
static void vd_s_Mm2c118nSendOmrs2(const U1 u1_a_SIG);
static void vd_s_Mm2c118nSendMmckpt(const U1 u1_a_SIG);
static void vd_s_Mm2c118nSendContc(const U1 u1_a_SIG);
static void vd_s_Mm2c118nSendTachosw(const U1 u1_a_SIG);
static void vd_s_Mm2c118nSendRevind(const U1 u1_a_SIG);
static void vd_s_Mm2c118nSendRvpk(const U1 u1_a_SIG);
static void vd_s_Mm2c118nSendRevset(const U1 u1_a_SIG);
static void vd_s_Mm2c118nSendgrvsw(const U1 u1_a_SIG);
static void vd_s_Mm2c118nSendHudsw(const U1 u1_a_SIG);
static void vd_s_Mm2c118nSendHudmsw(const U1 u1_a_SIG);
static void vd_s_Mm2c118nSendStswlh(const U1 u1_a_SIG);
static void vd_s_Mm2c118nSendStswrh(const U1 u1_a_SIG);
static void vd_s_Mm2c118nSendHudrtcw(const U1 u1_a_SIG);
static void vd_s_Mm2c118nSendHudrtccw(const U1 u1_a_SIG);
static void vd_s_Mm2c118nSendStswlhcstm1up(const U1 u1_a_SIG);
static void vd_s_Mm2c118nSendStswlhcstm2down(const U1 u1_a_SIG);
static void vd_s_Mm2c118nSendStswlhcstm3left(const U1 u1_a_SIG);
static void vd_s_Mm2c118nSendStswlhcstm4right(const U1 u1_a_SIG);
static void vd_s_Mm2c118nSendStswrhcstm1up(const U1 u1_a_SIG);
static void vd_s_Mm2c118nSendStswrhcstm2down(const U1 u1_a_SIG);
static void vd_s_Mm2c118nSendStswrhcstm3left(const U1 u1_a_SIG);
static void vd_s_Mm2c118nSendStswrhcstm4right(const U1 u1_a_SIG);
static void vd_s_Mm2c118nSendEcoind(const U1 u1_a_SIG);
static void vd_s_Mm2c118nSendEvind(const U1 u1_a_SIG);
static void vd_s_Mm2c118nSendResetm(const U1 u1_a_SIG);
static void vd_s_Mm2c118nSendViposdn(const U1 u1_a_SIG);
static void vd_s_Mm2c118nSendViposup(const U1 u1_a_SIG);
static void vd_s_Mm2c118nSendMettypc(const U1 u1_a_SIG);
static void vd_s_Mm2c118nSendRheosw(const U1 u1_a_SIG);
static void vd_s_Mm2c118nSendArsw(const U1 u1_a_SIG);
static void vd_s_Mm2c118nSendHudscsw(const U1 u1_a_SIG);
static void vd_s_Mm2c118nSendMettstc(const U1 u1_a_SIG);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_MM2C118N_ETHCOMVERT st_gp_MM2C118N_ETHCOMVERT[HMIMM2C118N_SIG_NUM] = {
/*  u4_buf     u1_bit     u1_bitmask                   */
    {(U4)14U,  (U1)27U,   (U1)0x01U},   /* L_MAINTE_RE */
    {(U4)16U,  (U1)30U,   (U1)0x01U},   /* L_OMRS_2    */
    {(U4)15U,  (U1)7U,    (U1)0x01U},   /* L_MMCKPT  */
    {(U4)14U,  (U1)6U,    (U1)0x03U},   /* L_CONT_C  */
    {(U4)15U,  (U1)5U,    (U1)0x03U},   /* L_TACHO_SW  */
    {(U4)14U,  (U1)28U,   (U1)0x01U},   /* L_REV_IND_A */
    {(U4)14U,  (U1)16U,   (U1)0x01U},   /* L_RV_PK_A */
    {(U4)14U,  (U1)17U,   (U1)0x7FU},   /* L_REV_SET_A */
    {(U4)20U,  (U1)0U,    (U1)0x01U},   /* L_GRV_SW */
    {(U4)14U,  (U1)1U,    (U1)0x03U},   /* L_HUD_SW */
    {(U4)14U,  (U1)29U,   (U1)0x03U},   /* L_HUD_MSW */
    {(U4)20U,  (U1)4U,    (U1)0x03U},   /* L_STSWLH_A */
    {(U4)21U,  (U1)4U,    (U1)0x03U},   /* L_STSWRH_A */
    {(U4)14U,  (U1)0U,    (U1)0x01U},   /* L_HUDRTCW */
    {(U4)14U,  (U1)8U,    (U1)0x01U},   /* L_HUDRTCCW */
    {(U4)22U,  (U1)0U,    (U1)0x0FU},   /* L_STSWLHCSTM1_UP */
    {(U4)22U,  (U1)8U,    (U1)0x0FU},   /* L_STSWLHCSTM2_DOWN */
    {(U4)22U,  (U1)16U,   (U1)0x0FU},   /* L_STSWLHCSTM3_LEFT */
    {(U4)22U,  (U1)24U,   (U1)0x0FU},   /* L_STSWLHCSTM4_RIGHT */
    {(U4)24U,  (U1)0U,    (U1)0x1FU},   /* L_STSWRHCSTM1_UP */
    {(U4)24U,  (U1)8U,    (U1)0x1FU},   /* L_STSWRHCSTM2_DOWN */
    {(U4)24U,  (U1)16U,   (U1)0x1FU},   /* L_STSWRHCSTM3_LEFT */
    {(U4)24U,  (U1)24U,   (U1)0x1FU},   /* L_STSWRHCSTM4_RIGHT */
    {(U4)14U,  (U1)5U,    (U1)0x01U},   /* L_ECO_IND_A */
    {(U4)14U,  (U1)4U,    (U1)0x01U},   /* L_EV_IND_A */
    {(U4)14U,  (U1)3U,    (U1)0x01U},   /* L_RESET_M */
    {(U4)14U,  (U1)14U,   (U1)0x01U},   /* L_VIPOS_DN */
    {(U4)14U,  (U1)15U,   (U1)0x01U},   /* L_VIPOS_UP */
    {(U4)14U,  (U1)10U,   (U1)0x03U},   /* L_MET_TYP_C */
    {(U4)15U,  (U1)0U,    (U1)0x1FU},   /* L_RHEOSW */
    {(U4)14U,  (U1)31U,   (U1)0x01U},   /* L_AR_SW */
    {(U4)14U,  (U1)30U,   (U1)0x01U},   /* L_HUD_SC_SW */
    {(U4)14U,  (U1)24U,   (U1)0x07U}    /* L_MET_TST_C */
};

const ST_MM2C118N_SIGIF st_gp_MM2C118N_SIGIF[HMIMM2C118N_SIG_NUM] = {
/*  fp_vd_send                            fp_u1_read           */
    {&vd_s_Mm2c118nSendMaintere,          &u1_s_Mm2c118nReadSig},
    {&vd_s_Mm2c118nSendOmrs2,             &u1_s_Mm2c118nReadSig},
    {&vd_s_Mm2c118nSendMmckpt,            &u1_s_Mm2c118nReadSig},
    {&vd_s_Mm2c118nSendContc,             &u1_s_Mm2c118nReadSig},
    {&vd_s_Mm2c118nSendTachosw,           &u1_s_Mm2c118nReadSig},
    {&vd_s_Mm2c118nSendRevind,            &u1_s_Mm2c118nReadSig},
    {&vd_s_Mm2c118nSendRvpk,              &u1_s_Mm2c118nReadSig},
    {&vd_s_Mm2c118nSendRevset,            &u1_s_Mm2c118nReadSig},
    {&vd_s_Mm2c118nSendgrvsw,             &u1_s_Mm2c118nReadSig},
    {&vd_s_Mm2c118nSendHudsw,             &u1_s_Mm2c118nReadSig},
    {&vd_s_Mm2c118nSendHudmsw,            &u1_s_Mm2c118nReadSig},
    {&vd_s_Mm2c118nSendStswlh,            &u1_s_Mm2c118nReadSig},
    {&vd_s_Mm2c118nSendStswrh,            &u1_s_Mm2c118nReadSig},
    {&vd_s_Mm2c118nSendHudrtcw,           &u1_s_Mm2c118nReadSig},
    {&vd_s_Mm2c118nSendHudrtccw,          &u1_s_Mm2c118nReadSig},
    {&vd_s_Mm2c118nSendStswlhcstm1up,     &u1_s_Mm2c118nReadSig},
    {&vd_s_Mm2c118nSendStswlhcstm2down,   &u1_s_Mm2c118nReadSig},
    {&vd_s_Mm2c118nSendStswlhcstm3left,   &u1_s_Mm2c118nReadSig},
    {&vd_s_Mm2c118nSendStswlhcstm4right,  &u1_s_Mm2c118nReadSig},
    {&vd_s_Mm2c118nSendStswrhcstm1up,     &u1_s_Mm2c118nReadSig},
    {&vd_s_Mm2c118nSendStswrhcstm2down,   &u1_s_Mm2c118nReadSig},
    {&vd_s_Mm2c118nSendStswrhcstm3left,   &u1_s_Mm2c118nReadSig},
    {&vd_s_Mm2c118nSendStswrhcstm4right,  &u1_s_Mm2c118nReadSig},
    {&vd_s_Mm2c118nSendEcoind,            &u1_s_Mm2c118nReadSig},
    {&vd_s_Mm2c118nSendEvind,             &u1_s_Mm2c118nReadSig},
    {&vd_s_Mm2c118nSendResetm,            &u1_s_Mm2c118nReadSig},
    {&vd_s_Mm2c118nSendViposdn,           &u1_s_Mm2c118nReadSig},
    {&vd_s_Mm2c118nSendViposup,           &u1_s_Mm2c118nReadSig},
    {&vd_s_Mm2c118nSendMettypc,           &u1_s_Mm2c118nReadSig},
    {&vd_s_Mm2c118nSendRheosw,            &u1_s_Mm2c118nReadSig},
    {&vd_s_Mm2c118nSendArsw,              &u1_s_Mm2c118nReadSig},
    {&vd_s_Mm2c118nSendHudscsw,           &u1_s_Mm2c118nReadSig},
    {&vd_s_Mm2c118nSendMettstc,           &u1_s_Mm2c118nReadSig}
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static void u1_s_Mm2c118nReadSig(const U1 u1_a_SIG_IDX, const U4 * u4_ap_REQ)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG_IDX  :  signal index number                                                                             */
/*                  u4_ap_REQ     :  ethernet data buffer                                                                            */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1 u1_s_Mm2c118nReadSig(const U1 u1_a_SIG_IDX, const U4 * u4_ap_REQ)
{
    U1    u1_t_sig;       /* recieve signal */
    U4    u4_t_buf;       /* MM Sub-Bus buffer */
    U1    u1_t_bitpos;    /* bit position */
    U1    u1_t_bitmask;   /* bit mask */

    u4_t_buf      = u4_ap_REQ[st_gp_MM2C118N_ETHCOMVERT[u1_a_SIG_IDX].u4_buf];
    u1_t_bitpos   = st_gp_MM2C118N_ETHCOMVERT[u1_a_SIG_IDX].u1_bitpos;
    u1_t_bitmask  = st_gp_MM2C118N_ETHCOMVERT[u1_a_SIG_IDX].u1_bitmask;

    u1_t_sig      = (U1)((u4_t_buf >> u1_t_bitpos) & (U4)u1_t_bitmask);

    return(u1_t_sig);
}

/*===================================================================================================================================*/
/*  static void vd_s_Mm2c118nSendMaintere(const U1 u1_a_SIG)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG  :  recieve signal                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Mm2c118nSendMaintere(const U1 u1_a_SIG)
{
    U1 u1_t_mmmthd;
    u1_t_mmmthd = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_AISETH);
    if(u1_t_mmmthd == (U1)TRUE){
        vd_g_HmiMaintPut(u1_a_SIG);
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_Mm2c118nSendOmrs2(const U1 u1_a_SIG)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG  :  recieve signal                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Mm2c118nSendOmrs2(const U1 u1_a_SIG)
{
    U1 u1_t_mmmthd;
    u1_t_mmmthd = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_AISETH);
    if(u1_t_mmmthd == (U1)TRUE){
        vd_g_HmiOilmaintPut(u1_a_SIG);
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_Mm2c118nSendMmckpt(const U1 u1_a_SIG)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG  :  recieve signal                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Mm2c118nSendMmckpt(const U1 u1_a_SIG)
{
    vd_g_HmiVardefPut(u1_a_SIG, (U1)HMIVARDEF_SIG_L_MMCKPT);
}

/*===================================================================================================================================*/
/*  static void vd_s_Mm2c118nSendContc(const U1 u1_a_SIG)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG  :  recieve signal                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Mm2c118nSendContc(const U1 u1_a_SIG)
{
    U1 u1_t_mmmthd;
    u1_t_mmmthd = u1_g_VardefMmMthd();
    if(u1_a_SIG <= (U1)HMIMM2C118N_2BIT_MAX){
        if(u1_t_mmmthd == (U1)VDF_ESO_METHOD_ETHER){
            vd_g_HmiMcstPut((U1)HMIMCST_L_CONT_C, u1_a_SIG);
            vd_g_HmiLcomPut(u1_a_SIG, (U1)HMILCOM_L_CONT_C);
        }
    }else{
        /* Do Nothing */
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_Mm2c118nSendTachosw(const U1 u1_a_SIG)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG  :  recieve signal                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Mm2c118nSendTachosw(const U1 u1_a_SIG)
{
    if(u1_a_SIG <= (U1)HMIMM2C118N_2BIT_MAX){
        vd_g_HmiMcstPut((U1)HMIMCST_L_TACHO_SW, u1_a_SIG);
    }else{
        /* Do Nothing */
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_Mm2c118nSendRevind(const U1 u1_a_SIG)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG  :  recieve signal                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Mm2c118nSendRevind(const U1 u1_a_SIG)
{
    if(u1_a_SIG <= (U1)HMIMM2C118N_1BIT_MAX){
        vd_g_HmiMcstPut((U1)HMIMCST_L_REV_IND_A, u1_a_SIG);
    }else{
        /* Do Nothing */
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_Mm2c118nSendRvpk(const U1 u1_a_SIG)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG  :  recieve signal                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Mm2c118nSendRvpk(const U1 u1_a_SIG)
{
    if(u1_a_SIG <= (U1)HMIMM2C118N_1BIT_MAX){
        vd_g_HmiMcstPut((U1)HMIMCST_L_RV_PK_A, u1_a_SIG);
    }else{
        /* Do Nothing */
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_Mm2c118nSendRevset(const U1 u1_a_SIG)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG  :  recieve signal                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Mm2c118nSendRevset(const U1 u1_a_SIG)
{
    if(u1_a_SIG <= (U1)HMIMM2C118N_REVSET_MAX){
        vd_g_HmiMcstPut((U1)HMIMCST_L_REV_SET_A, u1_a_SIG);
    }else{
        /* Do Nothing */
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_Mm2c118nSendgrvsw(const U1 u1_a_SIG)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG  :  recieve signal                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Mm2c118nSendgrvsw(const U1 u1_a_SIG)
{
    if(u1_a_SIG <= (U1)HMIMM2C118N_1BIT_MAX){
        vd_g_HmiMcstPut((U1)HMIMCST_L_GRV_SW, u1_a_SIG);
    }else{
        /* Do Nothing */
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_Mm2c118nSendHudsw(const U1 u1_a_SIG)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG  :  recieve signal                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Mm2c118nSendHudsw(const U1 u1_a_SIG)
{
    if(u1_a_SIG <= (U1)HMIMM2C118N_2BIT_MAX){
        vd_g_HmiMcstPut((U1)HMIMCST_L_HUD_SW, u1_a_SIG);
    }else{
        /* Do Nothing */
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_Mm2c118nSendHudmsw(const U1 u1_a_SIG)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG  :  recieve signal                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Mm2c118nSendHudmsw(const U1 u1_a_SIG)
{
    U1 u1_t_mmmthd;
    u1_t_mmmthd = u1_g_VardefMmMthd();
    if(u1_a_SIG <= (U1)HMIMM2C118N_1BIT_MAX){
        if(u1_t_mmmthd == (U1)VDF_ESO_METHOD_ETHER){
            vd_g_HmiMcstPut((U1)HMIMCST_L_HUD_MSW, u1_a_SIG);
            vd_g_HmiDiagPut(u1_a_SIG, (U1)HMIDIAG_HUD_MSW);
        }
    }else{
        /* Do Nothing */
    }
}
/*===================================================================================================================================*/
/*  static void vd_s_Mm2c118nSendStswlh(const U1 u1_a_SIG)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG  :  recieve signal                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Mm2c118nSendStswlh(const U1 u1_a_SIG)
{
    if(u1_a_SIG <= (U1)HMIMM2C118N_2BIT_MAX){
        vd_g_HmiMcstPut((U1)HMIMCST_L_STSWLH_A, u1_a_SIG);
    }else{
        /* Do Nothing */
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_Mm2c118nSendStswrh(const U1 u1_a_SIG)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG  :  recieve signal                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Mm2c118nSendStswrh(const U1 u1_a_SIG)
{
    if(u1_a_SIG <= (U1)HMIMM2C118N_2BIT_MAX){
        vd_g_HmiMcstPut((U1)HMIMCST_L_STSWRH_A, u1_a_SIG);
    }else{
        /* Do Nothing */
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_Mm2c118nSendHudrtcw(const U1 u1_a_SIG)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG  :  recieve signal                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Mm2c118nSendHudrtcw(const U1 u1_a_SIG)
{
    if(u1_a_SIG <= (U1)HMIMM2C118N_1BIT_MAX){
        vd_g_HmiMcstPut((U1)HMIMCST_L_HUDRTCW, u1_a_SIG);
    }else{
        /* Do Nothing */
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_Mm2c118nSendHudrtccw(const U1 u1_a_SIG)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG  :  recieve signal                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Mm2c118nSendHudrtccw(const U1 u1_a_SIG)
{
    if(u1_a_SIG <= (U1)HMIMM2C118N_1BIT_MAX){
        vd_g_HmiMcstPut((U1)HMIMCST_L_HUDRTCCW, u1_a_SIG);
    }else{
        /* Do Nothing */
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_Mm2c118nSendStswlhcstm1up(const U1 u1_a_SIG)                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG  :  recieve signal                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Mm2c118nSendStswlhcstm1up(const U1 u1_a_SIG)
{
    if(u1_a_SIG <= (U1)HMIMM2C118N_4BIT_MAX){
        vd_g_HmiMcstPut((U1)HMIMCST_L_STSWLHCSTM1_UP, u1_a_SIG);
    }else{
        /* Do Nothing */
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_Mm2c118nSendStswlhcstm2down(const U1 u1_a_SIG)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG  :  recieve signal                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Mm2c118nSendStswlhcstm2down(const U1 u1_a_SIG)
{
    if(u1_a_SIG <= (U1)HMIMM2C118N_4BIT_MAX){
        vd_g_HmiMcstPut((U1)HMIMCST_L_STSWLHCSTM2_DOWN, u1_a_SIG);
    }else{
        /* Do Nothing */
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_Mm2c118nSendStswlhcstm3left(const U1 u1_a_SIG)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG  :  recieve signal                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Mm2c118nSendStswlhcstm3left(const U1 u1_a_SIG)
{
    if(u1_a_SIG <= (U1)HMIMM2C118N_4BIT_MAX){
        vd_g_HmiMcstPut((U1)HMIMCST_L_STSWLHCSTM3_LEFT, u1_a_SIG);
    }else{
        /* Do Nothing */
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_Mm2c118nSendStswlhcstm4right(const U1 u1_a_SIG)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG  :  recieve signal                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Mm2c118nSendStswlhcstm4right(const U1 u1_a_SIG)
{
    if(u1_a_SIG <= (U1)HMIMM2C118N_4BIT_MAX){
        vd_g_HmiMcstPut((U1)HMIMCST_L_STSWLHCSTM4_RIGHT, u1_a_SIG);
    }else{
        /* Do Nothing */
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_Mm2c118nSendStswrhcstm1up(const U1 u1_a_SIG)                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG  :  recieve signal                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Mm2c118nSendStswrhcstm1up(const U1 u1_a_SIG)
{
    if(u1_a_SIG <= (U1)HMIMM2C118N_5BIT_MAX){
        vd_g_HmiMcstPut((U1)HMIMCST_L_STSWRHCSTM1_UP, u1_a_SIG);
    }else{
        /* Do Nothing */
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_Mm2c118nSendStswrhcstm2down(const U1 u1_a_SIG)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG  :  recieve signal                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Mm2c118nSendStswrhcstm2down(const U1 u1_a_SIG)
{
    if(u1_a_SIG <= (U1)HMIMM2C118N_5BIT_MAX){
        vd_g_HmiMcstPut((U1)HMIMCST_L_STSWRHCSTM2_DOWN, u1_a_SIG);
    }else{
        /* Do Nothing */
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_Mm2c118nSendStswrhcstm3left(const U1 u1_a_SIG)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG  :  recieve signal                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Mm2c118nSendStswrhcstm3left(const U1 u1_a_SIG)
{
    if(u1_a_SIG <= (U1)HMIMM2C118N_5BIT_MAX){
        vd_g_HmiMcstPut((U1)HMIMCST_L_STSWRHCSTM3_LEFT, u1_a_SIG);
    }else{
        /* Do Nothing */
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_Mm2c118nSendStswrhcstm4right(const U1 u1_a_SIG)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG  :  recieve signal                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Mm2c118nSendStswrhcstm4right(const U1 u1_a_SIG)
{
    if(u1_a_SIG <= (U1)HMIMM2C118N_5BIT_MAX){
        vd_g_HmiMcstPut((U1)HMIMCST_L_STSWRHCSTM4_RIGHT, u1_a_SIG);
    }else{
        /* Do Nothing */
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_Mm2c118nSendEcoind(const U1 u1_a_SIG)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG  :  recieve signal                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Mm2c118nSendEcoind(const U1 u1_a_SIG)
{
    if(u1_a_SIG <= (U1)HMIMM2C118N_1BIT_MAX){
        vd_g_HmiMcstPut((U1)HMIMCST_L_ECO_IND_A, u1_a_SIG);
    }else{
        /* Do Nothing */
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_Mm2c118nSendEvind(const U1 u1_a_SIG)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG  :  recieve signal                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Mm2c118nSendEvind(const U1 u1_a_SIG)
{
    if(u1_a_SIG <= (U1)HMIMM2C118N_1BIT_MAX){
        vd_g_HmiMcstPut((U1)HMIMCST_L_EV_IND_A, u1_a_SIG);
    }else{
        /* Do Nothing */
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_Mm2c118nSendResetm(const U1 u1_a_SIG)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG  :  recieve signal                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Mm2c118nSendResetm(const U1 u1_a_SIG)
{
    if(u1_a_SIG <= (U1)HMIMM2C118N_1BIT_MAX){
        vd_g_HmiMcstPut((U1)HMIMCST_L_RESET_M, u1_a_SIG);
    }else{
        /* Do Nothing */
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_Mm2c118nSendViposdn(const U1 u1_a_SIG)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG  :  recieve signal                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Mm2c118nSendViposdn(const U1 u1_a_SIG)
{
    U1 u1_t_mmmthd;
    u1_t_mmmthd = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_AISETH);
    if(u1_a_SIG <= (U1)HMIMM2C118N_1BIT_MAX){
        if(u1_t_mmmthd == (U1)TRUE){
            vd_g_HmiHudSigPut(u1_a_SIG, (U1)HMIHUD_SIGDAT_VIPOS_DN);
            vd_g_HmiDiagPut(u1_a_SIG, (U1)HMIDIAG_VIPOS_DN);
        }
    }else{
        /* Do Nothing */
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_Mm2c118nSendViposup(const U1 u1_a_SIG)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG  :  recieve signal                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Mm2c118nSendViposup(const U1 u1_a_SIG)
{
    U1 u1_t_mmmthd;
    u1_t_mmmthd = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_AISETH);
    if(u1_a_SIG <= (U1)HMIMM2C118N_1BIT_MAX){
        if(u1_t_mmmthd == (U1)TRUE){
            vd_g_HmiHudSigPut(u1_a_SIG, (U1)HMIHUD_SIGDAT_VIPOS_UP);
            vd_g_HmiDiagPut(u1_a_SIG, (U1)HMIDIAG_VIPOS_UP);
        }
    }else{
        /* Do Nothing */
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_Mm2c118nSendMettypc(const U1 u1_a_SIG)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG  :  recieve signal                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Mm2c118nSendMettypc(const U1 u1_a_SIG)
{
    if (u1_a_SIG <= (U1)HMIMM2C118N_2BIT_MAX) {
        vd_g_HmiMcstPut((U1)HMIMCST_L_MET_TYP_C, u1_a_SIG);
    }
    else {
        /* Do Nothing */
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_Mm2c118nSendRheosw(const U1 u1_a_SIG)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG  :  recieve signal                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Mm2c118nSendRheosw(const U1 u1_a_SIG)
{
    /* unused for 800B */
}

/*===================================================================================================================================*/
/*  static void vd_s_Mm2c118nSendArsw(const U1 u1_a_SIG)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG  :  recieve signal                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Mm2c118nSendArsw(const U1 u1_a_SIG)
{
    if (u1_a_SIG <= (U1)HMIMM2C118N_1BIT_MAX) {
        vd_g_HmiMcstPut((U1)HMIMCST_L_AR_SW, u1_a_SIG);
    }
    else {
        /* Do Nothing */
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_Mm2c118nSendHudscsw(const U1 u1_a_SIG)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG  :  recieve signal                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Mm2c118nSendHudscsw(const U1 u1_a_SIG)
{
    if (u1_a_SIG <= (U1)HMIMM2C118N_1BIT_MAX) {
        vd_g_HmiMcstPut((U1)HMIMCST_L_HUD_SC_SW, u1_a_SIG);
    }
    else {
        /* Do Nothing */
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_Mm2c118nSendMettstc(const U1 u1_a_SIG)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG  :  recieve signal                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Mm2c118nSendMettstc(const U1 u1_a_SIG)
{
    if(u1_a_SIG <= (U1)HMIMM2C118N_3BIT_MAX){
        vd_g_HmiMcstPut((U1)HMIMCST_L_MET_TST_C, u1_a_SIG);
    }else{
        /* Do Nothing */
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
/*  1.0.0    03/16/2020  TH       New.                                                                                               */
/*  1.1.0    10/07/2020  TH       Change config for 800B CV-R.                                                                       */
/*  1.2.0    01/06/2021  TH       See hmimm2c118n.c                                                                                  */
/*                                                                                                                                   */
/*  * TH   = Takahiro Hirano, Denso Techno                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/
