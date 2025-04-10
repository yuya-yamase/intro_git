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
#define MMLANG_C_MAJOR                         (1)
#define MMLANG_C_MINOR                         (1)
#define MMLANG_C_PATCH                         (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "mmlang_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((MMLANG_C_MAJOR != MMLANG_H_MAJOR) ||\
     (MMLANG_C_MINOR != MMLANG_H_MINOR) ||\
     (MMLANG_C_PATCH != MMLANG_H_PATCH))
#error "mmlang.c and mmlang.h : source and header files are inconsistent!"
#endif

#if ((MMLANG_C_MAJOR != MMLANG_CFG_H_MAJOR) ||\
     (MMLANG_C_MINOR != MMLANG_CFG_H_MINOR) ||\
     (MMLANG_C_PATCH != MMLANG_CFG_H_PATCH))
#error "mmlang.c and mmlang_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define MMLANG_LANG_UNDEF               (0x3FU)                                               /* M_LANG,A_LANG:Inval                 */

#define MMLANG_LNGST_UNDEF              (0U)                                                  /* M_LNG_ST,A_LNG_ST:Unknown           */
#define MMLANG_LNGST_COORDINATION       (1U)                                                  /* M_LNG_ST,A_LNG_ST:Coordination      */
#define MMLANG_LNGST_NOTCOORDINATION    (2U)                                                  /* M_LNG_ST,A_LNG_ST:Not Coordination  */
#define MMLANG_LNGST_DEFAULT            (3U)                                                  /* M_LNG_ST,A_LNG_ST:Default           */

#define MMLANG_LNGDB_INIT               (0U)                                                  /* M_LNGDB*,A_LNGDB* initial val       */
#define MMLANG_LNGDB_BITPOS             (0x80U)
#define MMLANG_LNGDB_BIT                (1U)

#define MMLANG_CHKLNGDBPOS              (8U)

#define MMLANG_LANGGR_NUM               (5U)
#define MMLANG_LANGGR_ENG               (0U)
#define MMLANG_LANGGR_FRA               (1U)
#define MMLANG_LANGGR_SPA               (2U)
#define MMLANG_LANGGR_POR               (3U)
#define MMLANG_LANGGR_CHNTRA            (4U)

#define MMLANG_ENGGRBIT                 (0x01U)
#define MMLANG_FRAGRBIT                 (0x02U)
#define MMLANG_SPAGRBIT                 (0x04U)
#define MMLANG_PORGRBIT                 (0x08U)
#define MMLANG_CHNTRAGRBIT              (0x10U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    const U1 *          u1_db;
    U1                  u1_bit;
}ST_MMLANG_LANGGR;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1 u1_s_mmlang_alngst;                                                               /* A_LNG_ST                              */
static U1 u1_s_mmlang_alang;                                                                /* A_LANG                                */
static U1 u1_s_mmlang_alngdb[MMLANG_LNGDB_NUM];                                             /* A_LNGDB                               */
static U1 u1_s_mmlang_alngchg;                                                              /* A_LNGCHG                              */
static U1 u1_s_mmlang_mlngst;                                                               /* M_LNG_ST                              */
static U1 u1_s_mmlang_mlngst_nvm;                                                           /* M_LNG_ST NVM                          */
static U1 u1_s_mmlang_mlang;                                                                /* M_LANG                                */
static U1 u1_s_mmlang_mlang_old;                                                            /* M_LANG_OLD                            */
static U1 u1_s_mmlang_mlngdb[MMLANG_LNGDB_NUM];                                             /* M_LNGDB                               */
static U1 u1_s_mmlang_font;                                                                 /* FONT                                  */
static U2 u2_s_mmlang_ptson_elpsd;                                                          /* PTS ON COUNT                          */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void vd_s_MmLangGetMmsig(void);
static void vd_s_MmLangJudeStateTrans(void);
static void vd_s_MmLangJudgMmChgSts(void);
static void vd_s_MmLangJudgMetChgSts(void);
static void vd_s_MmLangWrite(void);
static void vd_s_MmLangSetAltLang(void);
static void vd_s_MmLangMLangEvtTx(void);
static U1   u1_s_MmLangJudgLangGr(const U1 u1_a_LNGDBPOS, const U1 u1_a_LNGDBBIT);
static U1   u1_s_MmLangJudgAltLang(const U1 u1_a_LNGGRSUP);
static U1   u1_s_MmLangSrchAltLang(const U1 u1_a_LNGDBPOS , const U1 u1_a_ALTLANGDBSUP);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1   u1_sp_MMLANG_ENGDB[MMLANG_LNGDB_NUM] = {
    (U1)0x60U,    /*  AmericanEnglish / British.English       */
    (U1)0x00U,    /*  Non                                     */
    (U1)0x00U,    /*  Non                                     */
    (U1)0x06U,    /*  MEEnglish / JapaneseEnglish             */
    (U1)0x02U,    /*  AustralianEnglish                       */
    (U1)0x80U,    /*  IndianEnglish                           */
    (U1)0x00U     /*  Non                                     */
    };

static const U1   u1_sp_MMLANG_FRADB[MMLANG_LNGDB_NUM] = {
    (U1)0x10U,    /*  French                                  */
    (U1)0x00U,    /*  Non                                     */
    (U1)0x00U,    /*  Non                                     */
    (U1)0x01U,    /*  CanadianFrench                          */
    (U1)0x00U,    /*  Non                                     */
    (U1)0x00U,    /*  Non                                     */
    (U1)0x00U     /*  Non                                     */
    };

static const U1   u1_sp_MMLANG_SPADB[MMLANG_LNGDB_NUM] = {
    (U1)0x01U,    /*  Spanish                                 */
    (U1)0x00U,    /*  Non                                     */
    (U1)0x00U,    /*  Non                                     */
    (U1)0x08U,    /*  SpanishSouthAmerica                     */
    (U1)0x80U,    /*  NeutralSpanish                          */
    (U1)0x00U,    /*  Non                                     */
    (U1)0x00U     /*  Non                                     */
    };

static const U1   u1_sp_MMLANG_PORDB[MMLANG_LNGDB_NUM] = {
    (U1)0x00U,    /*  Non                                     */
    (U1)0x10U,    /*  Portuguese                              */
    (U1)0x00U,    /*  Non                                     */
    (U1)0x10U,    /*  PortugueseSouthAmerica                  */
    (U1)0x00U,    /*  Non                                     */
    (U1)0x00U,    /*  Non                                     */
    (U1)0x00U     /*  Non                                     */
    };

static const U1   u1_sp_MMLANG_CHN_TRA_DB[MMLANG_LNGDB_NUM] = {
    (U1)0x00U,    /*  Non                                     */
    (U1)0x00U,    /*  Non                                     */
    (U1)0x40U,    /*  TraditionalChinese                      */
    (U1)0x00U,    /*  Non                                     */
    (U1)0x01U,    /*  Taiwanese                               */
    (U1)0x00U,    /*  Non                                     */
    (U1)0x00U     /*  Non                                     */
    };

static const ST_MMLANG_LANGGR    st_sp_MMLANG_LANGGR[MMLANG_LANGGR_NUM] = {
    {
        &u1_sp_MMLANG_ENGDB[0],
        (U1)MMLANG_ENGGRBIT
    },
    {
        &u1_sp_MMLANG_FRADB[0],
        (U1)MMLANG_FRAGRBIT
    },
    {
        &u1_sp_MMLANG_SPADB[0],
        (U1)MMLANG_SPAGRBIT
    },
    {
        &u1_sp_MMLANG_PORDB[0],
        (U1)MMLANG_PORGRBIT
    },
    {
        &u1_sp_MMLANG_CHN_TRA_DB[0],
        (U1)MMLANG_CHNTRAGRBIT
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_MmLangBonInit(void)                                                                                                 */
/*                                                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_MmLangBonInit(void)
{
    U1  u1_t_sts;
    U1  u1_t_data;
    U1  u1_t_loop;

    u1_t_data = (U1)0U;

    u1_s_mmlang_alngst = (U1)MMLANG_LNGST_UNDEF;
    vd_g_Rim_WriteU1(u2_g_MMLANG_A_LNG_ST_RIM_U1, u1_s_mmlang_alngst);

    u1_s_mmlang_alang = (U1)MMLANG_LANG_UNDEF;
    vd_g_Rim_WriteU1(u2_g_MMLANG_A_LANG_RIM_U1, u1_s_mmlang_alang);

    u1_s_mmlang_alngchg = (U1)FALSE;

    u1_t_sts = u1_g_Nvmc_ReadU1withSts(u2_g_MMLANG_M_LNG_ST_NVMC_U1, &u1_t_data);
    if((u1_t_sts & (U1)NVMC_STATUS_KIND_MASK) == (U1)NVMC_STATUS_KIND_OK){
        u1_s_mmlang_mlngst     = u1_t_data;
        u1_s_mmlang_mlngst_nvm = u1_t_data;
    }
    else{
        u1_s_mmlang_mlngst     = (U1)MMLANG_LNGST_UNDEF;
        u1_s_mmlang_mlngst_nvm = (U1)MMLANG_LNGST_UNDEF;
    }

    u1_s_mmlang_mlang     = u1_g_Language((U1)FALSE);
    u1_s_mmlang_mlang_old = u1_s_mmlang_mlang;

    vd_g_Rim_WriteU1(u2_g_MMLANG_M_LANG_RIM_U1, u1_s_mmlang_mlang);
    vd_g_Rim_WriteU1(u2_g_MMLANG_M_LANG_OLD_RIM_U1, u1_s_mmlang_mlang_old);

    for(u1_t_loop = (U1)0U; u1_t_loop < (U1)MMLANG_LNGDB_NUM; u1_t_loop++){
        u1_s_mmlang_alngdb[u1_t_loop] = (U1)MMLANG_LNGDB_INIT;
        u1_s_mmlang_mlngdb[u1_t_loop] = (U1)MMLANG_LNGDB_INIT;
        vd_g_Rim_WriteU1(u2_gp_MMLANG_RIMID_A_LNGDB[u1_t_loop], u1_s_mmlang_alngdb[u1_t_loop]);
        vd_g_Rim_WriteU1(u2_gp_MMLANG_RIMID_M_LNGDB[u1_t_loop], u1_s_mmlang_mlngdb[u1_t_loop]);
    }

    u1_s_mmlang_font = (U1)MMLANG_FONT_UNDEF;
    vd_g_Rim_WriteU1(u2_g_MMLANG_FONT_RIM_U1, u1_s_mmlang_font);

    u2_s_mmlang_ptson_elpsd = (U2)0U;
}

/*===================================================================================================================================*/
/*  void    vd_g_MmLangWkupInit(void)                                                                                                */
/*                                                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_MmLangWkupInit(void)
{
    U1  u1_t_sts;
    U1  u1_t_data;
    U1  u1_t_loop;

    u1_t_data = (U1)0U;

    u1_t_sts = u1_g_Rim_ReadU1withStatus(u2_g_MMLANG_A_LNG_ST_RIM_U1, &u1_t_data);
    if ((u1_t_sts & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK){
        u1_s_mmlang_alngst = u1_t_data;
    }
    else{
        u1_s_mmlang_alngst = (U1)MMLANG_LNGST_UNDEF;
    }

    u1_t_sts = u1_g_Rim_ReadU1withStatus(u2_g_MMLANG_A_LANG_RIM_U1, &u1_t_data);
    if ((u1_t_sts & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK){
        u1_s_mmlang_alang = u1_t_data;
    }
    else{
        u1_s_mmlang_alang = (U1)MMLANG_LANG_UNDEF;
    }

    u1_s_mmlang_alngchg = (U1)FALSE;

    u1_t_sts = u1_g_Nvmc_ReadU1withSts(u2_g_MMLANG_M_LNG_ST_NVMC_U1, &u1_t_data);
    if((u1_t_sts & (U1)NVMC_STATUS_KIND_MASK) == (U1)NVMC_STATUS_KIND_OK){
        u1_s_mmlang_mlngst     = u1_t_data;
        u1_s_mmlang_mlngst_nvm = u1_t_data;
    }
    else{
        u1_s_mmlang_mlngst     = (U1)MMLANG_LNGST_UNDEF;
        u1_s_mmlang_mlngst_nvm = (U1)MMLANG_LNGST_UNDEF;
    }

    u1_t_sts = u1_g_Rim_ReadU1withStatus(u2_g_MMLANG_M_LANG_RIM_U1, &u1_t_data);
    if ((u1_t_sts & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK){
        u1_s_mmlang_mlang = u1_t_data;
    }
    else{
        u1_s_mmlang_mlang = (U1)MMLANG_LANG_UNDEF;
    }

    u1_t_sts = u1_g_Rim_ReadU1withStatus(u2_g_MMLANG_M_LANG_OLD_RIM_U1, &u1_t_data);
    if ((u1_t_sts & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK){
        u1_s_mmlang_mlang_old = u1_t_data;
    }
    else{
        u1_s_mmlang_mlang_old = (U1)MMLANG_LANG_UNDEF;
    }

    for(u1_t_loop = (U1)0U; u1_t_loop < (U1)MMLANG_LNGDB_NUM; u1_t_loop++){
        u1_t_sts = u1_g_Rim_ReadU1withStatus(u2_gp_MMLANG_RIMID_A_LNGDB[u1_t_loop], &u1_t_data);
        if ((u1_t_sts & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK){
            u1_s_mmlang_alngdb[u1_t_loop] = u1_t_data;
        }
        else{
            u1_s_mmlang_alngdb[u1_t_loop] = (U1)MMLANG_LNGDB_INIT;
        }

        u1_t_sts = u1_g_Rim_ReadU1withStatus(u2_gp_MMLANG_RIMID_M_LNGDB[u1_t_loop], &u1_t_data);
        if ((u1_t_sts & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK){
            u1_s_mmlang_mlngdb[u1_t_loop] = u1_t_data;
        }
        else{
            u1_s_mmlang_mlngdb[u1_t_loop] = (U1)MMLANG_LNGDB_INIT;
        }
    }

    u1_t_sts = u1_g_Rim_ReadU1withStatus(u2_g_MMLANG_FONT_RIM_U1, &u1_t_data);
    if ((u1_t_sts & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK){
        u1_s_mmlang_font = u1_t_data;
    }
    else{
        u1_s_mmlang_font = (U1)MMLANG_FONT_UNDEF;
    }

    u2_s_mmlang_ptson_elpsd = (U2)0U;
}

/*===================================================================================================================================*/
/*  void    vd_g_MmLangCstmzTask(void)                                                                                               */
/*                                                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_MmLangCstmzTask(void)
{
    U1  u1_t_accon;
    U1  u1_t_loop;
    U1  u1_t_esi_chk;
    U1  u1_t_langdb_type;

    u1_t_accon = u1_g_MmlangCfgAccchk();
    if(u1_t_accon == (U1)TRUE){
        vd_s_MmLangGetMmsig();

        u1_t_langdb_type = u1_g_MmlangCfgLangDBType();
        if(u1_t_langdb_type >= u1_g_MMLANG_LNGDB_TYPENUM){
            u1_t_langdb_type = u1_g_MMLANG_LNGDB_TYPEDEF;
        }
        for(u1_t_loop = (U1)0U; u1_t_loop < (U1)MMLANG_LNGDB_NUM; u1_t_loop++){
            u1_s_mmlang_mlngdb[u1_t_loop] = u1_gp_MMLANG_LNGDB_TBL[u1_t_langdb_type][u1_t_loop];
        }

        u1_s_mmlang_mlang = u1_g_Language((U1)FALSE);

        if((u1_s_mmlang_alngchg == (U1)TRUE              ) &&
           (u1_s_mmlang_mlang   == u1_s_mmlang_mlang_old)){
            vd_s_MmLangJudgMmChgSts();
        }
        else{
            vd_s_MmLangJudeStateTrans();
        }

        u1_s_mmlang_mlang_old = u1_s_mmlang_mlang;

        vd_s_MmLangSetAltLang();

        vd_g_Rim_WriteU1(u2_g_MMLANG_M_LANG_RIM_U1, u1_s_mmlang_mlang);
        vd_g_Rim_WriteU1(u2_g_MMLANG_M_LANG_OLD_RIM_U1, u1_s_mmlang_mlang_old);
        for(u1_t_loop = (U1)0U; u1_t_loop < (U1)MMLANG_LNGDB_NUM; u1_t_loop++){
            vd_g_Rim_WriteU1(u2_gp_MMLANG_RIMID_M_LNGDB[u1_t_loop], u1_s_mmlang_mlngdb[u1_t_loop]);
        }

        vd_s_MmLangWrite();
    }
    else{
        u1_s_mmlang_alngchg = (U1)FALSE;
        u2_s_mmlang_ptson_elpsd = (U2)0U;
        u1_t_esi_chk        = u1_g_MmlangCfgEsichk();

        if((u1_s_mmlang_mlngst_nvm != u1_s_mmlang_mlngst) &&
           (u1_t_esi_chk           == (U1)0U            ) ){
            u1_s_mmlang_mlngst_nvm = u1_s_mmlang_mlngst;
            vd_g_Nvmc_WriteU1(u2_g_MMLANG_M_LNG_ST_NVMC_U1,u1_s_mmlang_mlngst_nvm);
        }
    }
}

/*===================================================================================================================================*/
/*  static void  vd_s_MmLangGetMmsig(void)                                                                                           */
/*                                                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void  vd_s_MmLangGetMmsig(void)
{
    U1  u1_t_msg_sts;
    U1  u1_t_loop;

    u1_t_msg_sts = u1_g_MmlangCfgMsgsts();

    if(u1_t_msg_sts == (U1)0U){
        u1_s_mmlang_alngchg                = u1_g_MmlangCfgGetA_LNGCHG();
        u1_s_mmlang_alngst                 = u1_g_MmlangCfgGetA_LNG_ST();
        u1_s_mmlang_alang                  = u1_g_MmlangCfgGetA_LANG();
        u1_s_mmlang_alngdb[MMLANG_LNGDB_1] = u1_g_MmlangCfgGetA_LNGDB1();
        u1_s_mmlang_alngdb[MMLANG_LNGDB_2] = u1_g_MmlangCfgGetA_LNGDB2();
        u1_s_mmlang_alngdb[MMLANG_LNGDB_3] = u1_g_MmlangCfgGetA_LNGDB3();
        u1_s_mmlang_alngdb[MMLANG_LNGDB_4] = u1_g_MmlangCfgGetA_LNGDB4();
        u1_s_mmlang_alngdb[MMLANG_LNGDB_5] = u1_g_MmlangCfgGetA_LNGDB5();
        u1_s_mmlang_alngdb[MMLANG_LNGDB_6] = u1_g_MmlangCfgGetA_LNGDB6();
        u1_s_mmlang_alngdb[MMLANG_LNGDB_7] = u1_g_MmlangCfgGetA_LNGDB7();
		u1_s_mmlang_alngdb[MMLANG_LNGDB_7] = u1_s_mmlang_alngdb[MMLANG_LNGDB_7] << (U1)MMLANG_LNGDB_BIT;  /* DMS:Slovenia 1000000 */

        if(u1_s_mmlang_alang >= (U1)MMLANG_A_LANG_NUM){
            u1_s_mmlang_alang = (U1)MMLANG_LANG_UNDEF;
        }

        u1_s_mmlang_font = u1_gp_MMLANG_FONT_TBL[u1_s_mmlang_alang];

        vd_g_Rim_WriteU1(u2_g_MMLANG_A_LNG_ST_RIM_U1, u1_s_mmlang_alngst);
        vd_g_Rim_WriteU1(u2_g_MMLANG_A_LANG_RIM_U1, u1_s_mmlang_alang);
        for(u1_t_loop = (U1)0U; u1_t_loop < (U1)MMLANG_LNGDB_NUM; u1_t_loop++){
            vd_g_Rim_WriteU1(u2_gp_MMLANG_RIMID_A_LNGDB[u1_t_loop], u1_s_mmlang_alngdb[u1_t_loop]);
        }
    }
    else{
        u1_s_mmlang_alngchg = (U1)FALSE;
        u1_s_mmlang_font    = (U1)MMLANG_FONT_UNDEF;
    }
    vd_g_Rim_WriteU1(u2_g_MMLANG_FONT_RIM_U1, u1_s_mmlang_font);
}

/*===================================================================================================================================*/
/*  static void  vd_s_MmLangJudeStateTrans(void)                                                                                     */
/*                                                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void  vd_s_MmLangJudeStateTrans(void)
{
    switch(u1_s_mmlang_mlngst){
        case (U1)MMLANG_LNGST_UNDEF:
            u1_s_mmlang_mlngst = (U1)MMLANG_LNGST_DEFAULT;
            break;
        case (U1)MMLANG_LNGST_DEFAULT:
            if(u1_s_mmlang_alngchg == (U1)TRUE){
                if(u1_s_mmlang_alngst == (U1)MMLANG_LNGST_COORDINATION){
                    u1_s_mmlang_mlngst = (U1)MMLANG_LNGST_COORDINATION;
                }
                else if(u1_s_mmlang_alngst == (U1)MMLANG_LNGST_NOTCOORDINATION){
                    u1_s_mmlang_mlngst = (U1)MMLANG_LNGST_NOTCOORDINATION;
                }
                else{
                    /* Nothing to do */
                }
            }
            break;
        case (U1)MMLANG_LNGST_COORDINATION:
        case (U1)MMLANG_LNGST_NOTCOORDINATION:
            if(u1_s_mmlang_mlang != u1_s_mmlang_mlang_old){
                vd_s_MmLangJudgMetChgSts();
            }
            break;
        default:
            u1_s_mmlang_mlngst = (U1)MMLANG_LNGST_UNDEF;
            break;
    }
}

/*===================================================================================================================================*/
/*  static void  vd_s_MmLangJudgMmChgSts(void)                                                                                       */
/*                                                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void  vd_s_MmLangJudgMmChgSts(void)
{
    U1  u1_t_lngdbpos;
    U1  u1_t_lngdbbit;
    U1  u1_t_lang_metsup;

    u1_t_lngdbpos = u1_s_mmlang_alang / (U1)MMLANG_CHKLNGDBPOS;
    u1_t_lngdbbit = (U1)MMLANG_LNGDB_BITPOS >> (u1_s_mmlang_alang % (U1)MMLANG_CHKLNGDBPOS);

    if(u1_s_mmlang_alang >= (U1)MMLANG_LANG_NUM_VAL){
        u1_t_lang_metsup = (U1)0U;
    }
    else{
        u1_t_lang_metsup = u1_s_mmlang_mlngdb[u1_t_lngdbpos] & u1_t_lngdbbit;
    }

    if(u1_s_mmlang_alngst == (U1)MMLANG_LNGST_COORDINATION){
        if(u1_t_lang_metsup != (U1)0U){
            u1_s_mmlang_mlang  = u1_s_mmlang_alang;
            u1_s_mmlang_mlngst = (U1)MMLANG_LNGST_COORDINATION;
            vd_g_LanguagePut(u1_s_mmlang_alang);
        }
        else{
            u1_s_mmlang_mlngst = (U1)MMLANG_LNGST_NOTCOORDINATION;
        }
    }
    else if(u1_s_mmlang_alngst == (U1)MMLANG_LNGST_NOTCOORDINATION){
        u1_s_mmlang_mlngst = (U1)MMLANG_LNGST_NOTCOORDINATION;
    }
    else{
        /* Nothing to do */
    }
}

/*===================================================================================================================================*/
/*  static void  vd_s_MmLangJudgMetChgSts(void)                                                                                      */
/*                                                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void  vd_s_MmLangJudgMetChgSts(void)
{
    U1  u1_t_lngdbpos;
    U1  u1_t_lngdbbit;
    U1  u1_t_lang_mmsup;
    U1  u1_t_langgrsup;
    U1  u1_t_altlang;

    u1_t_lngdbpos = u1_s_mmlang_mlang / (U1)MMLANG_CHKLNGDBPOS;
    u1_t_lngdbbit = (U1)MMLANG_LNGDB_BITPOS >> (u1_s_mmlang_mlang % (U1)MMLANG_CHKLNGDBPOS);

    if(u1_s_mmlang_mlang >= (U1)MMLANG_LANG_NUM_VAL){
        u1_t_lang_mmsup = (U1)0U;
    }
	else{
        u1_t_lang_mmsup = u1_s_mmlang_alngdb[u1_t_lngdbpos] & u1_t_lngdbbit;
	}

    if(u1_t_lang_mmsup != (U1)0U){
        u1_s_mmlang_mlngst = (U1)MMLANG_LNGST_COORDINATION;
    }
    else{
        u1_t_langgrsup = u1_s_MmLangJudgLangGr(u1_t_lngdbpos, u1_t_lngdbbit);
        if(u1_t_langgrsup != (U1)0U){
            u1_t_altlang = u1_s_MmLangJudgAltLang(u1_t_langgrsup);
            if(u1_t_altlang != (U1)MMLANG_LANG_UNDEF){
                u1_s_mmlang_mlngst = (U1)MMLANG_LNGST_COORDINATION;
            }
            else{
                u1_s_mmlang_mlngst = (U1)MMLANG_LNGST_NOTCOORDINATION;
            }
        }
        else{
            u1_s_mmlang_mlngst = (U1)MMLANG_LNGST_NOTCOORDINATION;
        }
    }
}

/*===================================================================================================================================*/
/*  static void  vd_s_MmLangWrite(void)                                                                                              */
/*                                                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void  vd_s_MmLangWrite(void)
{
    U1  u1_t_tx;

    u1_t_tx = u1_s_mmlang_mlngst;
    vd_g_MmlangCfgTxM_LNG_ST(u1_t_tx);

    u1_t_tx = u1_s_mmlang_mlang;
    vd_g_MmlangCfgTxM_LANG(u1_t_tx);

    u1_t_tx = u1_s_mmlang_mlngdb[MMLANG_LNGDB_1];
    vd_g_MmlangCfgTxM_LNGDB1(u1_t_tx);

    u1_t_tx = u1_s_mmlang_mlngdb[MMLANG_LNGDB_2];
    vd_g_MmlangCfgTxM_LNGDB2(u1_t_tx);

    u1_t_tx = u1_s_mmlang_mlngdb[MMLANG_LNGDB_3];
    vd_g_MmlangCfgTxM_LNGDB3(u1_t_tx);

    u1_t_tx = u1_s_mmlang_mlngdb[MMLANG_LNGDB_4];
    vd_g_MmlangCfgTxM_LNGDB4(u1_t_tx);

    u1_t_tx = u1_s_mmlang_mlngdb[MMLANG_LNGDB_5];
    vd_g_MmlangCfgTxM_LNGDB5(u1_t_tx);

    u1_t_tx = u1_s_mmlang_mlngdb[MMLANG_LNGDB_6];
    vd_g_MmlangCfgTxM_LNGDB6(u1_t_tx);

    u1_t_tx = u1_s_mmlang_mlngdb[MMLANG_LNGDB_7];
    u1_t_tx = u1_t_tx >> (U1)MMLANG_LNGDB_BIT;      /* DMS:Slovenia 1000000 */
    vd_g_MmlangCfgTxM_LNGDB7(u1_t_tx);

    vd_s_MmLangMLangEvtTx();
}

/*===================================================================================================================================*/
/*  static void   vd_s_MmLangSetAltLang(void)                                                                                        */
/*                                                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void   vd_s_MmLangSetAltLang(void)
{
    U1  u1_t_lngdbpos;
    U1  u1_t_lngdbbit;
    U1  u1_t_lang_mmsup;
    U1  u1_t_langgrsup;
    U1  u1_t_altlang;

    u1_t_lngdbpos = u1_s_mmlang_mlang / (U1)MMLANG_CHKLNGDBPOS;
    u1_t_lngdbbit = (U1)MMLANG_LNGDB_BITPOS >> (u1_s_mmlang_mlang % (U1)MMLANG_CHKLNGDBPOS);

    if(u1_s_mmlang_mlang >= (U1)MMLANG_LANG_NUM_VAL){
        u1_t_lang_mmsup = (U1)0U;
    }
	else{
        u1_t_lang_mmsup = u1_s_mmlang_alngdb[u1_t_lngdbpos] & u1_t_lngdbbit;
	}

    if(u1_t_lang_mmsup == (U1)0U){
        u1_t_langgrsup = u1_s_MmLangJudgLangGr(u1_t_lngdbpos, u1_t_lngdbbit);
        if(u1_t_langgrsup != (U1)0U){
            u1_t_altlang = u1_s_MmLangJudgAltLang(u1_t_langgrsup);
            if(u1_t_altlang != (U1)MMLANG_LANG_UNDEF){
                u1_s_mmlang_mlang = u1_t_altlang;
            }
        }
    }
}

/*===================================================================================================================================*/
/*  static U1   u1_s_MmLangJudgLangGr(const U1 u1_a_LNGDBPOS, const U1 u1_a_LNGDBBIT)                                                */
/*                                                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1   u1_s_MmLangJudgLangGr(const U1 u1_a_LNGDBPOS, const U1 u1_a_LNGDBBIT)
{
    U4 u4_t_loop;
    U1 u1_t_langgrsup;
    U1 u1_t_langsup;

    u1_t_langsup = (U1)0U;

    for(u4_t_loop = (U4)0U; u4_t_loop < (U4)MMLANG_LANGGR_NUM; u4_t_loop++){
        u1_t_langgrsup = st_sp_MMLANG_LANGGR[u4_t_loop].u1_db[u1_a_LNGDBPOS] & u1_a_LNGDBBIT;
        if(u1_t_langgrsup != (U1)0U){
            u1_t_langsup |= st_sp_MMLANG_LANGGR[u4_t_loop].u1_bit;
        }
    };

    return(u1_t_langsup);
}

/*===================================================================================================================================*/
/*  static U1   u1_s_MmLangJudgAltLang(const U1 u1_a_LNGGRSUP)                                                                       */
/*                                                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1   u1_s_MmLangJudgAltLang(const U1 u1_a_LNGGRSUP)
{
    U4 u4_t_loop;
    U1 u1_t_lang;
    U1 u1_t_langgrsup;
    U1 u1_t_lngdbpos;
    U1 u1_t_altlangdbsup;

    u1_t_lang = (U1)MMLANG_LANG_UNDEF;

    for(u4_t_loop = (U4)0U; u4_t_loop < (U4)MMLANG_LANGGR_NUM; u4_t_loop++){
        u1_t_langgrsup = u1_a_LNGGRSUP & st_sp_MMLANG_LANGGR[u4_t_loop].u1_bit;
        if(u1_t_langgrsup != (U1)0U){
            u1_t_lngdbpos = (U1)0U;
            while((u1_t_lang == (U1)MMLANG_LANG_UNDEF)&&
                  (u1_t_lngdbpos < (U1)MMLANG_LNGDB_NUM)){
                    u1_t_altlangdbsup = u1_s_mmlang_alngdb[u1_t_lngdbpos] & st_sp_MMLANG_LANGGR[u4_t_loop].u1_db[u1_t_lngdbpos];
                    if(u1_t_altlangdbsup != (U1)0U){
                        u1_t_lang = u1_s_MmLangSrchAltLang(u1_t_lngdbpos, u1_t_altlangdbsup);
                    }
                    u1_t_lngdbpos++;
            }
        }
    };

    return(u1_t_lang);
}

/*===================================================================================================================================*/
/*  static U1   u1_s_MmLangSrchAltLang(const U1 u1_a_LNGDBPOS , const U1 u1_a_ALTLANGDBSUP)                                          */
/*                                                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1   u1_s_MmLangSrchAltLang(const U1 u1_a_LNGDBPOS , const U1 u1_a_ALTLANGDBSUP)
{
    U1 u1_t_lang;
    U1 u1_t_langsup;
    U4 u4_t_loop;

    u1_t_lang = (U1)MMLANG_LANG_UNDEF;

    for(u4_t_loop = (U4)0U; u4_t_loop < (U4)MMLANG_CHKLNGDBPOS; u4_t_loop++){
        u1_t_langsup = u1_a_ALTLANGDBSUP & ((U1)MMLANG_LNGDB_BITPOS >> u4_t_loop);
        if(u1_t_langsup != (U1)0U){
            u1_t_lang = ((U1)MMLANG_CHKLNGDBPOS * u1_a_LNGDBPOS) + (U1)u4_t_loop;
        }
    }

    return(u1_t_lang);
}

/*===================================================================================================================================*/
/*  static void vd_s_MmLangMLangEvtTx(void)                                                                                          */
/*                                                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_MmLangMLangEvtTx(void)
{
    static const U2    u2_s_MMLANG_COMTX_PTSON = ((U2)250U / (U2)MMLANG_MAIN_TICK) + (U2)1U;
    U1 u1_t_pts;

    u1_t_pts = u1_g_MmlangCfgPts();

    if(u1_t_pts == (U1)TRUE){
        if(u2_s_mmlang_ptson_elpsd < (U2)U2_MAX){
            u2_s_mmlang_ptson_elpsd++;
        }
    }
    else{
        u2_s_mmlang_ptson_elpsd = (U2)0U;
    }

    if(u2_s_mmlang_ptson_elpsd == u2_s_MMLANG_COMTX_PTSON){
        vd_g_MmlangCfgMLangEvtTx();
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
/*  1.0.0    11/23/2020  SF       New.                                                                                               */
/*  1.1.0     4/15/2021  SF       Add M_LANG Event Tx with ENG-ON.                                                                   */
/*                                                                                                                                   */
/*  * SF   = Seiya Fukutome, DensoTechno                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
