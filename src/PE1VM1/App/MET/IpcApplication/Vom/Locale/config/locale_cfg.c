/* 2.0.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Locale                                                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define LOCALE_CFG_C_MAJOR                     (2)
#define LOCALE_CFG_C_MINOR                     (0)
#define LOCALE_CFG_C_PATCH                     (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "locale_cfg_private.h"
#include "vardef.h"
#include "oxcan.h"
#include "rim_ctl.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((LOCALE_CFG_C_MAJOR != LOCALE_H_MAJOR) || \
     (LOCALE_CFG_C_MINOR != LOCALE_H_MINOR) || \
     (LOCALE_CFG_C_PATCH != LOCALE_H_PATCH))
#error "locale_cfg.c and locale.h : source and header files are inconsistent!"
#endif

#if ((LOCALE_CFG_C_MAJOR != LOCALE_CFG_H_MAJOR) || \
     (LOCALE_CFG_C_MINOR != LOCALE_CFG_H_MINOR) || \
     (LOCALE_CFG_C_PATCH != LOCALE_CFG_H_PATCH))
#error "locale_cfg.c and locale_cfg_private.h : source and header files are inconsistent!"
#endif

#if ((LOCALE_LANG_H_MAJOR != LOCALE_H_MAJOR) || \
     (LOCALE_LANG_H_MINOR != LOCALE_H_MINOR) || \
     (LOCALE_LANG_H_PATCH != LOCALE_H_PATCH))
#error "locale_lang.h and locale.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define LOCALE_UNIT_CH2_KM  (1U)
#define LOCALE_UNIT_CH2_MI  (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct {
    U1  u1_mcst_id;
    U1  u1_vdf_id;
}ST_UNITIDX;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U1 u1_g_LANG_NUM = (U1)LANG_NUM_VAL;

static const ST_UNITIDX st_sp_LOCALE_UNITIDX[UNIT_NUM_IDX] = {
#if 0   /* BEV Rebase provisionally */
    { (U1)MCST_BFI_DIST,   (U1)VDF_DEST_DBF_DEFUNIT_SPD    }, /*   UNIT_IDX_DIST                       (0U) */
    { (U1)MCST_BFI_SPEED,  (U1)VDF_DEST_DBF_DEFUNIT_SPD    }, /*   UNIT_IDX_SPEED                      (1U) */
    { (U1)MCST_BFI_FUECO,  (U1)VDF_DEST_DBF_DEFUNIT_FUECO  }, /*   UNIT_IDX_FUECO                      (2U) */
    { (U1)MCST_BFI_ELECO,  (U1)VDF_DEST_DBF_DEFUNIT_ELECO  }, /*   UNIT_IDX_ELECO                      (3U) */
    { (U1)MCST_BFI_AMBTMP, (U1)VDF_DEST_DBF_AMBTMP         }  /*   UNIT_IDX_AMBTMP                     (4U) */
#else   /* BEV Rebase provisionally */
    { (U1)U1_MAX,          (U1)VDF_DEST_DBF_DEFUNIT_SPD    }, /*   UNIT_IDX_DIST                       (0U) */
    { (U1)U1_MAX,          (U1)VDF_DEST_DBF_DEFUNIT_SPD    }, /*   UNIT_IDX_SPEED                      (1U) */
    { (U1)U1_MAX,          (U1)VDF_DEST_DBF_DEFUNIT_FUECO  }, /*   UNIT_IDX_FUECO                      (2U) */
    { (U1)U1_MAX,          (U1)VDF_DEST_DBF_DEFUNIT_ELECO  }, /*   UNIT_IDX_ELECO                      (3U) */
    { (U1)U1_MAX,          (U1)VDF_DEST_DBF_AMBTMP         }  /*   UNIT_IDX_AMBTMP                     (4U) */
#endif   /* BEV Rebase provisionally */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1 u1_sp_LOCALE_COMTX_UNIT_CH2[UNIT_NUM_VAL_FUECO] = {
    (U1)LOCALE_UNIT_CH2_KM, /* UNIT_VAL_FUECO_KMPL                 (0U) */
    (U1)LOCALE_UNIT_CH2_KM, /* UNIT_VAL_FUECO_LP100KM              (1U) */
    (U1)LOCALE_UNIT_CH2_MI, /* UNIT_VAL_FUECO_MPG_USA              (2U) */
    (U1)LOCALE_UNIT_CH2_MI, /* UNIT_VAL_FUECO_MPG_UK               (3U) */
    (U1)LOCALE_UNIT_CH2_MI, /* UNIT_VAL_FUECO_MPG_E                (4U) */
    (U1)LOCALE_UNIT_CH2_KM, /* UNIT_VAL_FUECO_KMPKG                (5U) */
    (U1)LOCALE_UNIT_CH2_KM  /* UNIT_VAL_FUECO_KGP100KM             (6U) */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1 u1_sp_LOCALE_LNGDB_TBL[VDF_NUM_LNGDBTYPE][LOCALE_LNGDB_NUM] = {
  /* LNGDB1     LNGDB2    LNGDB3    LNGDB4    LNGDB5    LNGDB6   LNGDB7 */
    {(U1)0xFFU,(U1)0xFFU,(U1)0xFFU,(U1)0xF9U,(U1)0x67U,(U1)0x22U,(U1)0x80U},    /*    Type1    */
    {(U1)0xFFU,(U1)0xFFU,(U1)0xFFU,(U1)0xF9U,(U1)0x67U,(U1)0x22U,(U1)0x80U},    /*    Type2    */
    {(U1)0xFFU,(U1)0xFFU,(U1)0xFFU,(U1)0xF9U,(U1)0x67U,(U1)0x22U,(U1)0x80U},    /*    Type3    */
    {(U1)0xFFU,(U1)0xFFU,(U1)0xFFU,(U1)0xF9U,(U1)0x67U,(U1)0x22U,(U1)0x80U},    /*    Type4    */
    {(U1)0xFFU,(U1)0xFFU,(U1)0xFFU,(U1)0xF9U,(U1)0x67U,(U1)0x22U,(U1)0x80U},    /*    Type5    */
    {(U1)0xFFU,(U1)0xFFU,(U1)0xFFU,(U1)0xF9U,(U1)0x67U,(U1)0x22U,(U1)0x80U},    /*    Type6    */
    {(U1)0xFFU,(U1)0xFFU,(U1)0xFFU,(U1)0xF9U,(U1)0x67U,(U1)0x22U,(U1)0x80U},    /*    Type7    */
    {(U1)0xFFU,(U1)0xFFU,(U1)0xFFU,(U1)0xF9U,(U1)0x67U,(U1)0x22U,(U1)0x80U},    /*    Type8    */
    {(U1)0xFFU,(U1)0xFFU,(U1)0xFFU,(U1)0xF9U,(U1)0x67U,(U1)0x22U,(U1)0x80U},    /*    Type9    */
    {(U1)0xFFU,(U1)0xFFU,(U1)0xFFU,(U1)0xF9U,(U1)0x67U,(U1)0x22U,(U1)0x80U},    /*    Type10   */
    {(U1)0xFFU,(U1)0xFFU,(U1)0xFFU,(U1)0xF9U,(U1)0x67U,(U1)0x22U,(U1)0x80U}     /*    Type11   */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1   u1_sp_LOCALE_ENGDB[LOCALE_LNGDB_NUM] = {
    (U1)0x60U,    /*  AmericanEnglish / British.English       */
    (U1)0x00U,    /*  Non                                     */
    (U1)0x00U,    /*  Non                                     */
    (U1)0x06U,    /*  MEEnglish / JapaneseEnglish             */
    (U1)0x02U,    /*  AustralianEnglish                       */
    (U1)0x80U,    /*  IndianEnglish                           */
    (U1)0x00U     /*  Non                                     */
    };

static const U1   u1_sp_LOCALE_FRADB[LOCALE_LNGDB_NUM] = {
    (U1)0x10U,    /*  French                                  */
    (U1)0x00U,    /*  Non                                     */
    (U1)0x00U,    /*  Non                                     */
    (U1)0x01U,    /*  CanadianFrench                          */
    (U1)0x00U,    /*  Non                                     */
    (U1)0x00U,    /*  Non                                     */
    (U1)0x00U     /*  Non                                     */
    };

static const U1   u1_sp_LOCALE_SPADB[LOCALE_LNGDB_NUM] = {
    (U1)0x01U,    /*  Spanish                                 */
    (U1)0x00U,    /*  Non                                     */
    (U1)0x00U,    /*  Non                                     */
    (U1)0x08U,    /*  SpanishSouthAmerica                     */
    (U1)0x80U,    /*  NeutralSpanish                          */
    (U1)0x00U,    /*  Non                                     */
    (U1)0x00U     /*  Non                                     */
    };

static const U1   u1_sp_LOCALE_PORDB[LOCALE_LNGDB_NUM] = {
    (U1)0x00U,    /*  Non                                     */
    (U1)0x10U,    /*  Portuguese                              */
    (U1)0x00U,    /*  Non                                     */
    (U1)0x10U,    /*  PortugueseSouthAmerica                  */
    (U1)0x00U,    /*  Non                                     */
    (U1)0x00U,    /*  Non                                     */
    (U1)0x00U     /*  Non                                     */
    };

static const U1   u1_sp_LOCALE_CHN_TRA_DB[LOCALE_LNGDB_NUM] = {
    (U1)0x00U,    /*  Non                                     */
    (U1)0x00U,    /*  Non                                     */
    (U1)0x40U,    /*  TraditionalChinese                      */
    (U1)0x00U,    /*  Non                                     */
    (U1)0x01U,    /*  Taiwanese                               */
    (U1)0x00U,    /*  Non                                     */
    (U1)0x00U     /*  Non                                     */
    };

static const U1 u1_sp_LOCALE_LNGDB_DEFENG[VDF_NUM_LNGDBTYPE] = {
    (U1)LANG_VAL______USA_ENG,    /*    Type1    */
    (U1)LANG_VAL______BRI_ENG,    /*    Type2    */
    (U1)LANG_VAL______USA_ENG,    /*    Type3    */
    (U1)LANG_VAL______BRI_ENG,    /*    Type4    */
    (U1)LANG_VAL______BRI_ENG,    /*    Type5    */
    (U1)LANG_VAL______USA_ENG,    /*    Type6    */
    (U1)LANG_VAL______BRI_ENG,    /*    Type7    */
    (U1)LANG_VAL______USA_ENG,    /*    Type8    */
    (U1)LANG_VAL______BRI_ENG,    /*    Type9    */
    (U1)LANG_VAL_______AU_ENG,    /*    Type10   */
    (U1)LANG_VAL______BRI_ENG     /*    Type11   */
};

static const U1 u1_sp_LOCALE_LNGDB_DEFFRA[VDF_NUM_LNGDBTYPE] = {
    (U1)LANG_VAL_______FRENCH,    /*    Type1    */
    (U1)LANG_VAL_______FRENCH,    /*    Type2    */
    (U1)LANG_VAL_______FRENCH,    /*    Type3    */
    (U1)LANG_VAL_______FRENCH,    /*    Type4    */
    (U1)LANG_VAL_______FRENCH,    /*    Type5    */
    (U1)LANG_VAL_______FRENCH,    /*    Type6    */
    (U1)LANG_VAL_______FRENCH,    /*    Type7    */
    (U1)LANG_VAL___CAN_FRENCH,    /*    Type8    */
    (U1)LANG_VAL_______FRENCH,    /*    Type9    */
    (U1)LANG_VAL_______FRENCH,    /*    Type10   */
    (U1)LANG_VAL_______FRENCH     /*    Type11   */
};

static const U1 u1_sp_LOCALE_LNGDB_DEFSPA[VDF_NUM_LNGDBTYPE] = {
    (U1)LANG_VAL______SPANISH,    /*    Type1    */
    (U1)LANG_VAL______SPANISH,    /*    Type2    */
    (U1)LANG_VAL______SPANISH,    /*    Type3    */
    (U1)LANG_VAL______SPANISH,    /*    Type4    */
    (U1)LANG_VAL______SPANISH,    /*    Type5    */
    (U1)LANG_VAL______SPANISH,    /*    Type6    */
    (U1)LANG_VAL______SPANISH,    /*    Type7    */
    (U1)LANG_VAL___SA_SPANISH,    /*    Type8    */
    (U1)LANG_VAL______SPANISH,    /*    Type9    */
    (U1)LANG_VAL______SPANISH,    /*    Type10   */
    (U1)LANG_VAL______SPANISH     /*    Type11   */
};

static const U1 u1_sp_LOCALE_LNGDB_DEFPOR[VDF_NUM_LNGDBTYPE] = {
    (U1)LANG_VAL__BRA_PORTUGU,    /*    Type1    */
    (U1)LANG_VAL__BRA_PORTUGU,    /*    Type2    */
    (U1)LANG_VAL__BRA_PORTUGU,    /*    Type3    */
    (U1)LANG_VAL__BRA_PORTUGU,    /*    Type4    */
    (U1)LANG_VAL__BRA_PORTUGU,    /*    Type5    */
    (U1)LANG_VAL__BRA_PORTUGU,    /*    Type6    */
    (U1)LANG_VAL___PORTUGUESE,    /*    Type7    */
    (U1)LANG_VAL__BRA_PORTUGU,    /*    Type8    */
    (U1)LANG_VAL__BRA_PORTUGU,    /*    Type9    */
    (U1)LANG_VAL__BRA_PORTUGU,    /*    Type10   */
    (U1)LANG_VAL__BRA_PORTUGU     /*    Type11   */
};

static const U1 u1_sp_LOCALE_LNGDB_DEFCHN_TRA[VDF_NUM_LNGDBTYPE] = {
    (U1)LANG_VAL______CHN_SMP,    /*    Type1    */
    (U1)LANG_VAL____TAIWANESE,    /*    Type2    */
    (U1)LANG_VAL______CHN_SMP,    /*    Type3    */
    (U1)LANG_VAL____TAIWANESE,    /*    Type4    */
    (U1)LANG_VAL____TAIWANESE,    /*    Type5    */
    (U1)LANG_VAL____TAIWANESE,    /*    Type6    */
    (U1)LANG_VAL____TAIWANESE,    /*    Type7    */
    (U1)LANG_VAL____TAIWANESE,    /*    Type8    */
    (U1)LANG_VAL____TAIWANESE,    /*    Type9    */
    (U1)LANG_VAL____TAIWANESE,    /*    Type10   */
    (U1)LANG_VAL____TAIWANESE     /*    Type11   */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1 u1_sp_LOCALE_LNGDB_DEFLANG[VDF_NUM_LNGDBTYPE] = {
    (U1)LANG_VAL__________JPN,    /*    Type1    */
    (U1)LANG_VAL______BRI_ENG,    /*    Type2    */
    (U1)LANG_VAL______CHN_SMP,    /*    Type3    */
    (U1)LANG_VAL______BRI_ENG,    /*    Type4    */
    (U1)LANG_VAL_______ARABIC,    /*    Type5    */
    (U1)LANG_VAL______SPANISH,    /*    Type6    */
    (U1)LANG_VAL______TURKISH,    /*    Type7    */
    (U1)LANG_VAL______USA_ENG,    /*    Type8    */
    (U1)LANG_VAL______BRI_ENG,    /*    Type9    */
    (U1)LANG_VAL_______AU_ENG,    /*    Type10   */
    (U1)LANG_VAL______BRI_ENG     /*    Type11   */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void  vd_g_LocaleComTxInit(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void  vd_g_LocaleComTxInit(void)
{
    U1  u1_t_unit_fueco;
    U1  u1_t_unit_ch2;

    u1_t_unit_ch2   = (U1)LOCALE_UNIT_CH2_KM;
    u1_t_unit_fueco = u1_g_Unit((U1)UNIT_IDX_FUECO);
    if(u1_t_unit_fueco < (U1)UNIT_NUM_VAL_FUECO){
        u1_t_unit_ch2 = u1_sp_LOCALE_COMTX_UNIT_CH2[u1_t_unit_fueco];
    }
#if 0   /* BEV Rebase provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_UNIT_CH2 , &u1_t_unit_ch2);
#endif   /* BEV Rebase provisionally */
}
/*===================================================================================================================================*/
/*  void  vd_g_LocaleComTxTask(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void  vd_g_LocaleComTxTask(void)
{
    U1  u1_t_unit_fueco;
    U1  u1_t_pre_unit_ch2;
    U1  u1_t_unit_ch2;

#if 0   /* BEV Rebase provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_UNIT_CH2 , &u1_t_pre_unit_ch2);
#endif   /* BEV Rebase provisionally */

    u1_t_unit_ch2   = (U1)LOCALE_UNIT_CH2_KM;
    u1_t_unit_fueco = u1_g_Unit((U1)UNIT_IDX_FUECO);
    if(u1_t_unit_fueco < (U1)UNIT_NUM_VAL_FUECO){
        u1_t_unit_ch2 = u1_sp_LOCALE_COMTX_UNIT_CH2[u1_t_unit_fueco];
    }

#if 0   /* BEV Rebase provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_UNIT_CH2 , &u1_t_unit_ch2);
    if(u1_t_pre_unit_ch2 != u1_t_unit_ch2){
        (void)Com_TriggerIPDUSend(MSG_MET1S11_TXCH0);
    }
#endif   /* BEV Rebase provisionally */
}
/*===================================================================================================================================*/
/*  U1  u1_g_LocaleCfgLangDef(void)                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1  u1_g_LocaleCfgLangDef(void)
{
    U1    u1_t_lang;
    U1    u1_t_langdb_type;
    U1    u1_t_lngdbpos;
    U1    u1_t_lngdbbit;
    U1    u1_t_langsup;

    u1_t_lang = u1_g_VardefDefLangByPid();

    u1_t_langdb_type = u1_g_VardefLngDBTypeByPid();

    u1_t_lngdbpos = u1_t_lang / (U1)LOCALE_CHKLNGDBPOS;
    u1_t_lngdbbit = (U1)LOCALE_LNGDB_BITPOS >> (u1_t_lang % (U1)LOCALE_CHKLNGDBPOS);

    if(u1_t_lngdbpos >= (U1)LOCALE_LNGDB_NUM){
        u1_t_lngdbpos = (U1)LOCALE_CHKLNGDBPOSDEF;
    }
    u1_t_langsup = u1_sp_LOCALE_LNGDB_TBL[u1_t_langdb_type][u1_t_lngdbpos] & u1_t_lngdbbit;

    if(u1_t_langsup == (U1)0U){
        u1_t_lang = u1_sp_LOCALE_LNGDB_DEFLANG[u1_t_langdb_type];
    }

    return(u1_t_lang);
}
/*===================================================================================================================================*/
/*  U1 u1_g_LocaleCfgMmLangChk(const U1 u1_a_LANG)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1 u1_g_LocaleCfgMmLangChk(const U1 u1_a_LANG)
{
    U1  u1_t_lang;
    U1  u1_t_langdb_type;
    U1  u1_t_lngdbpos;
    U1  u1_t_lngdbbit;
    U1  u1_t_langsup;
    U1  u1_t_langsup_eng;
    U1  u1_t_langsup_fra;
    U1  u1_t_langsup_spa;
    U1  u1_t_langsup_por;
    U1  u1_t_langsup_chntra;

    u1_t_lang = u1_a_LANG;

    u1_t_langdb_type = u1_g_VardefLngDBTypeByPid();
    u1_t_lngdbpos = u1_t_lang / (U1)LOCALE_CHKLNGDBPOS;
    u1_t_lngdbbit = (U1)LOCALE_LNGDB_BITPOS >> (u1_t_lang % (U1)LOCALE_CHKLNGDBPOS);

    if(u1_t_lngdbpos >= (U1)LOCALE_LNGDB_NUM){
        u1_t_lngdbpos = (U1)LOCALE_CHKLNGDBPOSDEF;
    }
    u1_t_langsup = u1_sp_LOCALE_LNGDB_TBL[u1_t_langdb_type][u1_t_lngdbpos] & u1_t_lngdbbit;

    if(u1_t_langsup == (U1)0U){
        u1_t_langsup_eng    = u1_sp_LOCALE_ENGDB[u1_t_lngdbpos] & u1_t_lngdbbit;
        u1_t_langsup_fra    = u1_sp_LOCALE_FRADB[u1_t_lngdbpos] & u1_t_lngdbbit;
        u1_t_langsup_spa    = u1_sp_LOCALE_SPADB[u1_t_lngdbpos] & u1_t_lngdbbit;
        u1_t_langsup_por    = u1_sp_LOCALE_PORDB[u1_t_lngdbpos] & u1_t_lngdbbit;
        u1_t_langsup_chntra = u1_sp_LOCALE_CHN_TRA_DB[u1_t_lngdbpos] & u1_t_lngdbbit;

        if(u1_t_langsup_eng != (U1)0U)
        {
            u1_t_lang = u1_sp_LOCALE_LNGDB_DEFENG[u1_t_langdb_type];
        }
        else if(u1_t_langsup_fra != (U1)0U){
            u1_t_lang = u1_sp_LOCALE_LNGDB_DEFFRA[u1_t_langdb_type];
        }
        else if(u1_t_langsup_spa != (U1)0U){
            u1_t_lang = u1_sp_LOCALE_LNGDB_DEFSPA[u1_t_langdb_type];
        }
        else if(u1_t_langsup_por != (U1)0U){
            u1_t_lang = u1_sp_LOCALE_LNGDB_DEFPOR[u1_t_langdb_type];
        }
        else if(u1_t_langsup_chntra != (U1)0U){
            u1_t_lang = u1_sp_LOCALE_LNGDB_DEFCHN_TRA[u1_t_langdb_type];
        }
        else{
            u1_t_lang = u1_g_LanguageDef();
        }
    }

    return(u1_t_lang);
}
/*===================================================================================================================================*/
/*  U1  u1_g_LocaleCfgTimeFormatDef(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1  u1_g_LocaleCfgTimeFormatDef(void)
{
    return(u1_g_VardefDefTmFmtByPid());
}
/*===================================================================================================================================*/
/*  U1  u1_g_LocaleCfgSubSpd(const U1 u1_a_UNIT)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1  u1_g_LocaleCfgSubSpd(const U1 u1_a_UNIT)
{
    U1 u1_t_var_subspd;
    U1 u1_t_unit_subspd;

    u1_t_var_subspd = u1_g_VardefSubDigSpdByPid();

    if(( u1_a_UNIT       == (U1)UNIT_VAL_SPEED_KMPH) &&
       ((u1_t_var_subspd == (U1)VDF_SUBDIGSPD_MPH ) ||
        (u1_t_var_subspd == (U1)VDF_SUBDIGSPD_BOTH))){
        u1_t_unit_subspd = (U1)UNIT_SUB_SPD_MPH;
    }
    else if(( u1_a_UNIT       == (U1)UNIT_VAL_SPEED_MPH ) &&
            ((u1_t_var_subspd == (U1)VDF_SUBDIGSPD_KMPH) ||
             (u1_t_var_subspd == (U1)VDF_SUBDIGSPD_BOTH))){
        u1_t_unit_subspd = (U1)UNIT_SUB_SPD_KMPH;
    }
    else{
        u1_t_unit_subspd = (U1)UNIT_SUB_SPD_NON;
    }

    return(u1_t_unit_subspd);
}
/*===================================================================================================================================*/
/*  U1      u1_g_LocaleCfgLang(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_LocaleCfgLang(void)
{
#if 0   /* BEV Rebase provisionally */
    return(u1_g_McstBf((U1)MCST_BFI_LANG));
#else   /* BEV Rebase provisionally */
    return((U1)U1_MAX);
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*  void    vd_g_LocaleCfgLangPut(const U1 u1_a_LANG)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_LocaleCfgLangPut(const U1 u1_a_LANG)
{
#if 0   /* BEV Rebase provisionally */
    vd_g_McstBfPut((U1)MCST_BFI_LANG, u1_a_LANG);
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*  U1      u1_g_LocaleCfgUnit(const U1 u1_a_UNITIDX)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_LocaleCfgUnit(const U1 u1_a_UNITIDX)
{
    U1  u1_t_idx;
    U1  u1_t_unit;

    u1_t_idx   = st_sp_LOCALE_UNITIDX[u1_a_UNITIDX].u1_mcst_id;
#if 0   /* BEV Rebase provisionally */
    u1_t_unit  = u1_g_McstBf(u1_t_idx);
#else   /* BEV Rebase provisionally */
    u1_t_unit = (U1)U1_MAX;
#endif   /* BEV Rebase provisionally */
    return(u1_t_unit);
}

/*===================================================================================================================================*/
/*  void    vd_g_LocaleCfgUnitPut(const U1 u1_a_UNITIDX, const U1 u1_a_VAL)                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_LocaleCfgUnitPut(const U1 u1_a_UNITIDX, const U1 u1_a_VAL)
{
    U1  u1_t_idx;
    u1_t_idx   = st_sp_LOCALE_UNITIDX[u1_a_UNITIDX].u1_mcst_id;
#if 0   /* BEV Rebase provisionally */
    vd_g_McstBfPut(u1_t_idx , u1_a_VAL);
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*  void    vd_g_LocaleCfgTfmPut(const U1 u1_a_FRMT)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_LocaleCfgTfmPut(const U1 u1_a_FRMT)
{
#if 0   /* BEV Rebase provisionally */
    vd_g_McstBfPut((U1)MCST_BFI_TIMEFMT, u1_a_FRMT);
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*  void    vd_g_LocaleCfgTfmPut(const U1 u1_a_FRMT)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_LocaleCfgTfm(void)
{
#if 0   /* BEV Rebase provisionally */
    return(u1_g_McstBf((U1)MCST_BFI_TIMEFMT));
#else   /* BEV Rebase provisionally */
    return((U1)U1_MAX);
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*  void    vd_g_LocaleCfgTfmPut(const U1 u1_a_FRMT)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_LocaleCfgUnitdef(const U1 u1_a_UNITIDX)
{
    U1  u1_t_idx;
    U1  u1_t_unit;

    u1_t_idx  = st_sp_LOCALE_UNITIDX[u1_a_UNITIDX].u1_vdf_id;
    u1_t_unit  = u1_g_VardefDestDbfByPid(u1_t_idx);
    return(u1_t_unit);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    12/15/2017  TN       New.                                                                                               */
/*  1.1.0    01/24/2019  TA       See locale.c v1.1.0                                                                                */
/*  1.2.0    08/01/2019  TA       See locale.c v1.2.0                                                                                */
/*  1.3.0    04/29/2020  SF       See locale.c v1.3.0                                                                                */
/*  1.4.0    09/28/2020  SF       See locale.c v1.4.0                                                                                */
/*  1.5.0    01/25/2021  SF       See locale.c v1.5.0                                                                                */
/*  2.0.0    07/09/2021  TA       See locale.c v2.0.0.                                                                               */
/*  2.0.1    12/08/2022  TA(M)    See locale.c v2.0.1                                                                                */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  800B-1   02/24/2020  SF       Add Variation config for 800B CV.                                                                  */
/*  800B-2   09/28/2020  SF       Change config for 800B CV-R.                                                                       */
/*  800B-1   01/25/2021  SF       Change config for 800B 1A.                                                                         */
/*  840B-1   04/14/2021  AT       Change config for 840B CV                                                                          */
/*  893B-1   11/09/2021  RO       Change config for 893B 1A                                                                          */
/*  840B-2    1/24/2022  RO       Change config for 840B MPT                                                                         */
/*  025D182D-1 4/14/2022 SK       Change config for 025D182D 1A                                                                      */
/*  296D235D 11/28/2022  TX       Add Lang Type18 and Type19                                                                         */
/*  19PFv3-1 08/21/2023  SH       config merge                                                                                       */
/*  19PFv3-2 04/24/2025  SF       Bug fixing for MET19PFV3-43718                                                                     */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*  * SF   = Seiya Fukutome, DensoTechno                                                                                             */
/*  * AT   = Ayano Tomimoto                                                                                                          */
/*  * RO   = Reiya Okuda, KSE                                                                                                        */
/*  * SK   = Shotaro Kitayama, PRD                                                                                                   */
/*  * TX   = Xinyuan Tong, DNST                                                                                                      */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*  * SH   = Sae Hirose, Denso Techno                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/
