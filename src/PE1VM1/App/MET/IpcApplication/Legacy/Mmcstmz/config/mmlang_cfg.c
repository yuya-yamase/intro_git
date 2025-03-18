/* 1.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Mmcstmz : mmlang                                                                                                                 */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define MMLANG_CFG_C_MAJOR                       (1)
#define MMLANG_CFG_C_MINOR                       (1)
#define MMLANG_CFG_C_PATCH                       (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "mmlang_cfg_private.h"

#include "oxcan.h"
#if 0   /* BEV BSW provisionally */
#else
#include "Com_Cfg_STUB.h"
#include "oxcan_channel_STUB.h"
#endif
#include "veh_opemd.h"
#if 0   /* BEV BSW provisionally */
#else
#include "veh_opemd_xmode_STUB.h"
#endif
#include "rim_ctl.h"
#if 0   /* BEV BSW provisionally */
#else
#include "rim_ctl_cfg_STUB.h"
#endif
#include "nvmc_mgr_cfg.h"
#if 0   /* BEV BSW provisionally */
#include "es_inspect.h"
#else
#include "nvmc_mgr_cfg_STUB.h"
#include "es_inspect_STUB.h"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((MMLANG_CFG_C_MAJOR != MMLANG_H_MAJOR) || \
     (MMLANG_CFG_C_MINOR != MMLANG_H_MINOR) || \
     (MMLANG_CFG_C_PATCH != MMLANG_H_PATCH))
#error "mmlang_cfg.c and mmlang.h : source and header files are inconsistent!"
#endif

#if ((MMLANG_CFG_C_MAJOR != MMLANG_CFG_H_MAJOR) || \
     (MMLANG_CFG_C_MINOR != MMLANG_CFG_H_MINOR) || \
     (MMLANG_CFG_C_PATCH != MMLANG_CFG_H_PATCH))
#error "mmlang_cfg.c and mmlang_cfg_private.h : source and header files are inconsistent!"
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
const U2                u2_g_MMLANG_A_LNG_ST_RIM_U1   = (U2)RIMID_U1_A_LNG_ST;
const U2                u2_g_MMLANG_A_LANG_RIM_U1     = (U2)RIMID_U1_A_LANG;
const U2                u2_g_MMLANG_M_LANG_RIM_U1     = (U2)RIMID_U1_M_LANG;
const U2                u2_g_MMLANG_M_LANG_OLD_RIM_U1 = (U2)RIMID_U1_M_LANG_OLD;

const U2 u2_gp_MMLANG_RIMID_A_LNGDB[MMLANG_LNGDB_NUM] = {
    (U2)RIMID_U1_A_LNGDB_1,
    (U2)RIMID_U1_A_LNGDB_2,
    (U2)RIMID_U1_A_LNGDB_3,
    (U2)RIMID_U1_A_LNGDB_4,
    (U2)RIMID_U1_A_LNGDB_5,
    (U2)RIMID_U1_A_LNGDB_6,
    (U2)RIMID_U1_A_LNGDB_7
};

const U2 u2_gp_MMLANG_RIMID_M_LNGDB[MMLANG_LNGDB_NUM] = {
    (U2)RIMID_U1_M_LNGDB_1,
    (U2)RIMID_U1_M_LNGDB_2,
    (U2)RIMID_U1_M_LNGDB_3,
    (U2)RIMID_U1_M_LNGDB_4,
    (U2)RIMID_U1_M_LNGDB_5,
    (U2)RIMID_U1_M_LNGDB_6,
    (U2)RIMID_U1_M_LNGDB_7
};

const U2                u2_g_MMLANG_FONT_RIM_U1       = (U2)RIMID_U1_FONT;

const U2                u2_g_MMLANG_M_LNG_ST_NVMC_U1  = (U2)NVMCID_U1_M_LNG_ST;

const U1                u1_g_MMLANG_LNGDB_TYPENUM     = (U1)VDF_NUM_LNGDBTYPE;
const U1                u1_g_MMLANG_LNGDB_TYPEDEF     = (U1)VDF_LNGDBTYPE_TYPE1;

const U1 u1_gp_MMLANG_LNGDB_TBL[VDF_NUM_LNGDBTYPE][MMLANG_LNGDB_NUM] = {
  /* M_LNGDB1 M_LNGDB2 M_LNGDB3 M_LNGDB4 M_LNGDB5 M_LNGDB6 M_LNGDB7 */
    {(U1)0xFFU,(U1)0xFFU,(U1)0xFFU,(U1)0xFFU,(U1)0xE7U,(U1)0xA2U,(U1)0x80U},    /*    Type1    */
    {(U1)0xFFU,(U1)0xFFU,(U1)0xFFU,(U1)0xFFU,(U1)0xE7U,(U1)0xA2U,(U1)0x80U},    /*    Type2    */
    {(U1)0xFFU,(U1)0xFFU,(U1)0xFFU,(U1)0xFFU,(U1)0xE7U,(U1)0xA2U,(U1)0x80U},    /*    Type3    */
    {(U1)0xFFU,(U1)0xFFU,(U1)0xFFU,(U1)0xFFU,(U1)0xE7U,(U1)0xA2U,(U1)0x80U},    /*    Type4    */
    {(U1)0xFFU,(U1)0xFFU,(U1)0xFFU,(U1)0xFFU,(U1)0xE7U,(U1)0xA2U,(U1)0x80U},    /*    Type5    */
    {(U1)0xFFU,(U1)0xFFU,(U1)0xFFU,(U1)0xFFU,(U1)0xE7U,(U1)0xA2U,(U1)0x80U},    /*    Type6    */
    {(U1)0xFFU,(U1)0xFFU,(U1)0xFFU,(U1)0xFFU,(U1)0xE7U,(U1)0xA2U,(U1)0x80U},    /*    Type7    */
    {(U1)0xFFU,(U1)0xFFU,(U1)0xFFU,(U1)0xFFU,(U1)0xE7U,(U1)0xA2U,(U1)0x80U},    /*    Type8    */
    {(U1)0xFFU,(U1)0xFFU,(U1)0xFFU,(U1)0xFFU,(U1)0xE7U,(U1)0xA2U,(U1)0x80U},    /*    Type9    */
    {(U1)0xFFU,(U1)0xFFU,(U1)0xFFU,(U1)0xFFU,(U1)0xE7U,(U1)0xA2U,(U1)0x80U},    /*    Type10   */
    {(U1)0xFFU,(U1)0xFFU,(U1)0xFFU,(U1)0xFFU,(U1)0xE7U,(U1)0xA2U,(U1)0x80U}     /*    Type11   */
};

const U1 u1_gp_MMLANG_FONT_TBL[MMLANG_A_LANG_NUM] = {
    (U1)MMLANG_FONT_MRSW,                            /*   Japanese                   */
    (U1)MMLANG_FONT_LXS_LEFT,                        /*   American English           */
    (U1)MMLANG_FONT_LXS_LEFT,                        /*   British. English           */
    (U1)MMLANG_FONT_LXS_LEFT,                        /*   French                     */
    (U1)MMLANG_FONT_LXS_LEFT,                        /*   German                     */
    (U1)MMLANG_FONT_LXS_LEFT,                        /*   Italian                    */
    (U1)MMLANG_FONT_LXS_LEFT,                        /*   Dutch                      */
    (U1)MMLANG_FONT_LXS_LEFT,                        /*   Spanish                    */
    (U1)MMLANG_FONT_LXS_LEFT,                        /*   Swedish                    */
    (U1)MMLANG_FONT_LXS_LEFT,                        /*   Danish                     */
    (U1)MMLANG_FONT_LXS_LEFT,                        /*   Norwegian                  */
    (U1)MMLANG_FONT_LXS_LEFT,                        /*   Portuguese                 */
    (U1)MMLANG_FONT_LXS_LEFT,                        /*   Russian                    */
    (U1)MMLANG_FONT_LXS_LEFT,                        /*   Greek                      */
    (U1)MMLANG_FONT_LXS_LEFT,                        /*   Polish                     */
    (U1)MMLANG_FONT_LXS_LEFT,                        /*   Finnish                    */
    (U1)MMLANG_FONT_CHN_SMP,                         /*   Simplified Chinese         */
    (U1)MMLANG_FONT_CHN_TRA,                         /*   Traditional Chinese        */
    (U1)MMLANG_FONT_KOR,                             /*   Korean                     */
    (U1)MMLANG_FONT_LXS_LEFT,                        /*   Ukrainian                  */
    (U1)MMLANG_FONT_LXS_LEFT,                        /*   Turkish                    */
    (U1)MMLANG_FONT_LXS_LEFT,                        /*   Hungarian                  */
    (U1)MMLANG_FONT_LXS_LEFT,                        /*   Czech                      */
    (U1)MMLANG_FONT_LXS_LEFT,                        /*   Slovak                     */
    (U1)MMLANG_FONT_LXS_LEFT,                        /*   Roman                      */
    (U1)MMLANG_FONT_ARAB,                            /*   Arabia                     */
    (U1)MMLANG_FONT_THAI,                            /*   Thai                       */
    (U1)MMLANG_FONT_LXS_LEFT,                        /*   Portuguese South America   */
    (U1)MMLANG_FONT_LXS_LEFT,                        /*   Spanish South America      */
    (U1)MMLANG_FONT_LXS_LEFT,                        /*   ME English                 */
    (U1)MMLANG_FONT_LXS_LEFT,                        /*   American English           */
    (U1)MMLANG_FONT_LXS_LEFT,                        /*   Canadian French            */
    (U1)MMLANG_FONT_LXS_LEFT,                        /*   Neutral Spanish            */
    (U1)MMLANG_FONT_LXS_LEFT,                        /*   Malayan                    */
    (U1)MMLANG_FONT_LXS_LEFT,                        /*   Indonesian                 */
    (U1)MMLANG_FONT_LXS_LEFT,                        /*   Basque                     */
    (U1)MMLANG_FONT_LXS_LEFT,                        /*   Bulgarian                  */
    (U1)MMLANG_FONT_LXS_LEFT,                        /*   Flemish                    */
    (U1)MMLANG_FONT_LXS_LEFT,                        /*   Australian English         */
    (U1)MMLANG_FONT_CHN_TRA,                         /*   Taiwanese                  */
    (U1)MMLANG_FONT_LXS_LEFT,                        /*   Indian English             */
    (U1)MMLANG_FONT_LXS_LEFT,                        /*   Hindi                      */
    (U1)MMLANG_FONT_VETNAM,                          /*   Vietnamese                 */
    (U1)MMLANG_FONT_LXS_LEFT,                        /*   Filipino                   */
    (U1)MMLANG_FONT_LXS_LEFT,                        /*   Tamil                      */
    (U1)MMLANG_FONT_LXS_RIGHT,                       /*   Persian                    */
    (U1)MMLANG_FONT_LXS_RIGHT,                       /*   Hebrew                     */
    (U1)MMLANG_FONT_LXS_RIGHT,                       /*   Israeli                    */
    (U1)MMLANG_FONT_LXS_LEFT,                        /*   Slovenian                  */
    (U1)MMLANG_FONT_UNDEF,                           /*   invalid                    */
    (U1)MMLANG_FONT_UNDEF,                           /*   invalid                    */
    (U1)MMLANG_FONT_UNDEF,                           /*   invalid                    */
    (U1)MMLANG_FONT_UNDEF,                           /*   invalid                    */
    (U1)MMLANG_FONT_UNDEF,                           /*   invalid                    */
    (U1)MMLANG_FONT_UNDEF,                           /*   invalid                    */
    (U1)MMLANG_FONT_UNDEF,                           /*   invalid                    */
    (U1)MMLANG_FONT_UNDEF,                           /*   invalid                    */
    (U1)MMLANG_FONT_UNDEF,                           /*   invalid                    */
    (U1)MMLANG_FONT_UNDEF,                           /*   invalid                    */
    (U1)MMLANG_FONT_UNDEF,                           /*   invalid                    */
    (U1)MMLANG_FONT_UNDEF,                           /*   invalid                    */
    (U1)MMLANG_FONT_UNDEF,                           /*   invalid                    */
    (U1)MMLANG_FONT_UNDEF,                           /*   invalid                    */
    (U1)MMLANG_FONT_UNDEF                            /*   invalid                    */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  U1  u1_g_MmlangCfgAccchk(void)                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1  u1_g_MmlangCfgAccchk(void)
{
    return(u1_g_VehopemdAccOn());
}
/*===================================================================================================================================*/
/*  U1      u1_g_MmlangCfgEsichk(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_MmlangCfgEsichk(void)
{
#if 0   /* BEV BSW provisionally */
    return(u1_g_ESInspectMdBfield());
#else
    return((U1)0U);
#endif
}
/*===================================================================================================================================*/
/*  U1      u1_g_MmlangCfgPts(void)                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_MmlangCfgPts(void)
{
    return(u1_g_VehopemdPtsOn((U1)VEH_OPEMD_PTS_INV_LAS));
}
/*===================================================================================================================================*/
/*  U1      u1_g_MmlangCfgLangDBType(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_MmlangCfgLangDBType(void)
{
    return(u1_g_VardefLngDBTypeByPid());
}
/*===================================================================================================================================*/
/*  U1  u1_g_MmlangCfgMsgsts(void)                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1  u1_g_MmlangCfgMsgsts(void)
{
    static const U2 u2_s_MMLANG_AVN1S20_TOTIM = ((U2)10000U / (U2)OXCAN_MAIN_TICK); /*    Resolution:[ms]    */

    U1  u1_t_msg_sts;

    u1_t_msg_sts = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_AVN1S20,
                                         (U2)OXCAN_RX_SYS_NRX_ACC | (U2)OXCAN_RX_SYS_TOE_ACC,
                                         u2_s_MMLANG_AVN1S20_TOTIM) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    return(u1_t_msg_sts);
}
/*===================================================================================================================================*/
/*  U1  u1_g_MmlangCfgGetA_LNGCHG(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_MmlangCfgGetA_LNGCHG(void)
{
    U1          u1_t_sgnl;

    u1_t_sgnl = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_A_LNGCHG, &u1_t_sgnl);
    return (u1_t_sgnl);
}
/*===================================================================================================================================*/
/*  U1  u1_g_MmlangCfgGetA_LNG_ST(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_MmlangCfgGetA_LNG_ST(void)
{
    U1          u1_t_sgnl;

    u1_t_sgnl = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_A_LNG_ST, &u1_t_sgnl);
    return (u1_t_sgnl);
}
/*===================================================================================================================================*/
/*  U1  u1_g_MmlangCfgGetA_LANG(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_MmlangCfgGetA_LANG(void)
{
    U1          u1_t_sgnl;

    u1_t_sgnl = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_A_LANG, &u1_t_sgnl);
    return (u1_t_sgnl);
}
/*===================================================================================================================================*/
/*  U1  u1_g_MmlangCfgGetA_LNGDB1(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_MmlangCfgGetA_LNGDB1(void)
{
    U1          u1_t_sgnl;

    u1_t_sgnl = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_A_LNGDB1, &u1_t_sgnl);
    return (u1_t_sgnl);
}
/*===================================================================================================================================*/
/*  U1  u1_g_MmlangCfgGetA_LNGDB2(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_MmlangCfgGetA_LNGDB2(void)
{
    U1          u1_t_sgnl;

    u1_t_sgnl = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_A_LNGDB2, &u1_t_sgnl);
    return (u1_t_sgnl);
}
/*===================================================================================================================================*/
/*  U1  u1_g_MmlangCfgGetA_LNGDB3(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_MmlangCfgGetA_LNGDB3(void)
{
    U1          u1_t_sgnl;

    u1_t_sgnl = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_A_LNGDB3, &u1_t_sgnl);
    return (u1_t_sgnl);
}
/*===================================================================================================================================*/
/*  U1  u1_g_MmlangCfgGetA_LNGDB4(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_MmlangCfgGetA_LNGDB4(void)
{
    U1          u1_t_sgnl;

    u1_t_sgnl = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_A_LNGDB4, &u1_t_sgnl);
    return (u1_t_sgnl);
}
/*===================================================================================================================================*/
/*  U1  u1_g_MmlangCfgGetA_LNGDB5(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_MmlangCfgGetA_LNGDB5(void)
{
    U1          u1_t_sgnl;

    u1_t_sgnl = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_A_LNGDB5, &u1_t_sgnl);
    return (u1_t_sgnl);
}
/*===================================================================================================================================*/
/*  U1  u1_g_MmlangCfgGetA_LNGDB6(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_MmlangCfgGetA_LNGDB6(void)
{
    U1          u1_t_sgnl;

    u1_t_sgnl = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_A_LNGDB6, &u1_t_sgnl);
    return (u1_t_sgnl);
}
/*===================================================================================================================================*/
/*  U1  u1_g_MmlangCfgGetA_LNGDB7(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_MmlangCfgGetA_LNGDB7(void)
{
    U1          u1_t_sgnl;

    u1_t_sgnl = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_A_LNGDB7, &u1_t_sgnl);
    return (u1_t_sgnl);
}
/*===================================================================================================================================*/
/* void            vd_g_MmlangCfgTxM_LNG_ST(const U1 u1_a_SIG)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_MmlangCfgTxM_LNG_ST(const U1 u1_a_SIG)
{
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_M_LNG_ST, &u1_a_SIG);    /* COM Tx STUB delete */
#endif
}
/*===================================================================================================================================*/
/* void            vd_g_MmlangCfgTxM_LANG(const U1 u1_a_SIG)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_MmlangCfgTxM_LANG(const U1 u1_a_SIG)
{
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_M_LANG, &u1_a_SIG);    /* COM Tx STUB delete */
#endif
}
/*===================================================================================================================================*/
/* void            vd_g_MmlangCfgTxM_LNGDB1(const U1 u1_a_SIG)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_MmlangCfgTxM_LNGDB1(const U1 u1_a_SIG)
{
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_M_LNGDB1, &u1_a_SIG);    /* COM Tx STUB delete */
#endif
}
/*===================================================================================================================================*/
/* void            vd_g_MmlangCfgTxM_LNGDB2(const U1 u1_a_SIG)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_MmlangCfgTxM_LNGDB2(const U1 u1_a_SIG)
{
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_M_LNGDB2, &u1_a_SIG);    /* COM Tx STUB delete */
#endif
}
/*===================================================================================================================================*/
/* void            vd_g_MmlangCfgTxM_LNGDB3(const U1 u1_a_SIG)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_MmlangCfgTxM_LNGDB3(const U1 u1_a_SIG)
{
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_M_LNGDB3, &u1_a_SIG);    /* COM Tx STUB delete */
#endif
}
/*===================================================================================================================================*/
/* void            vd_g_MmlangCfgTxM_LNGDB4(const U1 u1_a_SIG)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_MmlangCfgTxM_LNGDB4(const U1 u1_a_SIG)
{
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_M_LNGDB4, &u1_a_SIG);    /* COM Tx STUB delete */
#endif
}
/*===================================================================================================================================*/
/* void            vd_g_MmlangCfgTxM_LNGDB5(const U1 u1_a_SIG)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_MmlangCfgTxM_LNGDB5(const U1 u1_a_SIG)
{
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_M_LNGDB5, &u1_a_SIG);    /* COM Tx STUB delete */
#endif
}
/*===================================================================================================================================*/
/* void            vd_g_MmlangCfgTxM_LNGDB6(const U1 u1_a_SIG)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_MmlangCfgTxM_LNGDB6(const U1 u1_a_SIG)
{
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_M_LNGDB6, &u1_a_SIG);    /* COM Tx STUB delete */
#endif
}
/*===================================================================================================================================*/
/* void            vd_g_MmlangCfgTxM_LNGDB7(const U1 u1_a_SIG)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_MmlangCfgTxM_LNGDB7(const U1 u1_a_SIG)
{
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_M_LNGDB7, &u1_a_SIG);    /* COM Tx STUB delete */
#endif
}
/*===================================================================================================================================*/
/* void            vd_g_MmlangCfgMLangEvtTx(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_MmlangCfgMLangEvtTx(void)
{
    (void)Com_TriggerIPDUSend(MSG_MET1S18_TXCH0);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    11/23/2020  SF       New.                                                                                               */
/*  1.1.0     4/15/2021  SF       Add M_LANG Event Tx with ENG-ON.                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/*  800B-1    1/25/2021  SF       Change config for 800B 1A                                                                          */
/*  840B-1    4/26/2021  SF       Change config for 840B CV                                                                          */
/*  893B-1   11/08/2021  TT       Change config for 893B 1A                                                                          */
/*  025D182D-1 4/14/2022 SK       Change config for 025D182D 1A                                                                      */
/*  296D235D 11/28/2022  TX       Add Type18 and Type19 into u1_gp_MMLANG_LNGDB_TBL                                                  */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*  * SF   = Seiya Fukutome, DensoTechno                                                                                             */
/*  * TT   = Tatsunori Takada, KSE                                                                                                   */
/*  * SK   = Shotaro Kitayama, PRD                                                                                                   */
/*  * TX   = Xinyuan Tong, DNST                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/
