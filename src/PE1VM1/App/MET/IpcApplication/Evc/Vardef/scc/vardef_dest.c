/* 3.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Vardef / Destination                                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VARDEF_DEST_C_MAJOR                     (3)
#define VARDEF_DEST_C_MINOR                     (0)
#define VARDEF_DEST_C_PATCH                     (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "vardef_dest_cfg_private.h"

#include "rim_ctl.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((VARDEF_DEST_C_MAJOR != VARDEF_DEST_H_MAJOR) || \
     (VARDEF_DEST_C_MINOR != VARDEF_DEST_H_MINOR) || \
     (VARDEF_DEST_C_PATCH != VARDEF_DEST_H_PATCH))
#error "vardef_dest.c and vardef_dest.h : source and header files are inconsistent!"
#endif

#if ((VARDEF_DEST_C_MAJOR != VARDEF_DEST_CFG_H_MAJOR) || \
     (VARDEF_DEST_C_MINOR != VARDEF_DEST_CFG_H_MINOR) || \
     (VARDEF_DEST_C_PATCH != VARDEF_DEST_CFG_H_PATCH))
#error "vardef_dest.c and vardef_dest_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VDF_DST_C_CODE_DEF              (0x0fffU)
#define VDF_DST_DEST_BDB_DEF            (0xffU)
#define VDF_DST_STRG_WHL_DEF            (0x03U)
#define VDF_DST_SPEC_C_CODE_INV         (0U)

#define VDF_DST_CANRX_STRGWHL_00        (0x00U)                                                        /* STRG_WHL:00                */
#define VDF_DST_CANRX_STRGWHL_01        (0x01U)                                                        /* STRG_WHL:01                */
#define VDF_DST_CANRX_STRGWHL_10        (0x02U)                                                        /* STRG_WHL:10                */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U2           u2_s_vdf_dst_c_code;
static U2           u2_s_vdf_dst_c_code_pre;
static U1           u1_s_vdf_dst_dest_bdb;
static U1           u1_s_vdf_dst_dest_bdb_pre;
static U1           u1_s_vdf_dst_strg_whl;
static U1           u1_s_vdf_dst_strg_whl_pre;

static U1           u1_s_vdf_dst_rxcnt;
static U2           u2_s_vdf_dst_intvl;

static U1           u1_s_vdf_dst_c_code_idx;
static U1           u1_s_vdf_dst_dest_bdb_idx;
static U1           u1_s_vdf_dst_idx;

static U1           u1_s_vdf_dst_law_spec_ccode_idx;
static U1           u1_s_vdf_dst_law_c_code_idx;
static U1           u1_s_vdf_dst_law_dest_bdb_idx;
static U1           u1_s_vdf_dst_law_idx;

static U1           u1_s_vdf_dst_hdlside;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void         vd_s_VardefDestDBIdxJdg(void);
static void         vd_s_VardefDestHdlJdg(const U1 u1_a_STRG_WHL);
/* Determination Process for Regulatory Projects */
static void         vd_s_VardefDestLawDBIdxJdg(void);
/* C_CODE signal value hexadecimal to decimal conversion */
static U2           u2_s_VardefDestCCodeHexToDec(const U2 u2_a_HEX_C_CODE);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_VardefDestBonInit(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_VardefDestBonInit(void)
{
    u2_s_vdf_dst_c_code            = (U2)VDF_DST_C_CODE_DEF;
    u2_s_vdf_dst_c_code_pre        = (U2)VDF_DST_C_CODE_DEF;
    vd_g_Rim_WriteU2(u2_g_VDF_DST_C_CODE_RIM_U2, u2_s_vdf_dst_c_code);

    u1_s_vdf_dst_dest_bdb          = (U1)VDF_DST_DEST_BDB_DEF;
    u1_s_vdf_dst_dest_bdb_pre      = (U1)VDF_DST_DEST_BDB_DEF;
    vd_g_Rim_WriteU1(u2_g_VDF_DST_DEST_BDB_RIM_U1, u1_s_vdf_dst_dest_bdb);

    u1_s_vdf_dst_strg_whl          = (U1)VDF_DST_STRG_WHL_DEF;
    u1_s_vdf_dst_strg_whl_pre      = (U1)VDF_DST_STRG_WHL_DEF;
    vd_g_Rim_WriteU1(u2_g_VDF_DST_STRG_WHL_RIM_U1, u1_s_vdf_dst_strg_whl);

    u1_s_vdf_dst_rxcnt             = u1_g_VDF_DST_RXEV_CNT_INIT;
    u2_s_vdf_dst_intvl             = (U2)0U;
    u1_s_vdf_dst_c_code_idx        = u1_g_VDF_DST_C_CODE_IDX_DEF;
    u1_s_vdf_dst_dest_bdb_idx      = u1_g_VDF_DST_DEST_BDB_IDX_DEF;
    u1_s_vdf_dst_law_spec_ccode_idx = u1_g_VDF_DST_LAW_SPEC_IDX_DEF;
    u1_s_vdf_dst_law_c_code_idx    = u1_g_VDF_DST_LAW_C_CODE_IDX_DEF;
    u1_s_vdf_dst_law_dest_bdb_idx  = u1_g_VardefDestLawCfgBdbDefJdg();

    u1_s_vdf_dst_law_idx            = u1_g_VDF_DST_IDX_DEF;
    vd_g_Rim_WriteU1(u2_g_VDF_DST_LAW_IDX_RIM_U1, u1_s_vdf_dst_law_idx);

    u1_s_vdf_dst_idx               = u1_g_VDF_DST_IDX_DEF;
    vd_g_Rim_WriteU1(u2_g_VDF_DST_IDX_RIM_U1, u1_s_vdf_dst_idx);

    u1_s_vdf_dst_hdlside           = (U1)VDF_HDSIDE_LHD;
}
/*===================================================================================================================================*/
/*  void    vd_g_VardefDestRstwkInit(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_VardefDestRstwkInit(void)
{
    U1  u1_t_sts;
    U2  u2_t_data;
    U1  u1_t_data;

    u2_t_data = (U2)0U;
    u1_t_data = (U1)0U;

    u1_t_sts    = u1_g_Rim_ReadU2withStatus(u2_g_VDF_DST_C_CODE_RIM_U2, &u2_t_data);
    if ((u1_t_sts & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK){
        u2_s_vdf_dst_c_code         = u2_t_data;
        u2_s_vdf_dst_c_code_pre     = u2_t_data;
    }
    else{
        u2_s_vdf_dst_c_code         = (U2)VDF_DST_C_CODE_DEF;
        u2_s_vdf_dst_c_code_pre     = (U2)VDF_DST_C_CODE_DEF;
    }

    u1_t_sts    = u1_g_Rim_ReadU1withStatus(u2_g_VDF_DST_DEST_BDB_RIM_U1, &u1_t_data);
    if ((u1_t_sts & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK){
        u1_s_vdf_dst_dest_bdb       = u1_t_data;
        u1_s_vdf_dst_dest_bdb_pre   = u1_t_data;
    }
    else{
        u1_s_vdf_dst_dest_bdb       = (U1)VDF_DST_DEST_BDB_DEF;
        u1_s_vdf_dst_dest_bdb_pre   = (U1)VDF_DST_DEST_BDB_DEF;
    }

    u1_t_sts    = u1_g_Rim_ReadU1withStatus(u2_g_VDF_DST_STRG_WHL_RIM_U1, &u1_t_data);
    if ((u1_t_sts & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK){
        u1_s_vdf_dst_strg_whl       = u1_t_data;
        u1_s_vdf_dst_strg_whl_pre   = u1_t_data;
    }
    else{
        u1_s_vdf_dst_strg_whl       = (U1)VDF_DST_STRG_WHL_DEF;
        u1_s_vdf_dst_strg_whl_pre   = (U1)VDF_DST_STRG_WHL_DEF;
    }

    u1_s_vdf_dst_rxcnt        = u1_g_VDF_DST_RXEV_CNT_INIT;
    u2_s_vdf_dst_intvl        = (U2)0U;
    u1_t_sts    = u1_g_Rim_ReadU1withStatus(u2_g_VDF_DST_IDX_RIM_U1, &u1_t_data);
    if ((u1_t_sts & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK){
        u1_s_vdf_dst_idx            = u1_t_data;
    }
    else{
        u1_s_vdf_dst_idx            = u1_g_VDF_DST_IDX_DEF;
    }

    u1_t_sts    = u1_g_Rim_ReadU1withStatus(u2_g_VDF_DST_LAW_IDX_RIM_U1, &u1_t_data);
    if ((u1_t_sts & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK){
        u1_s_vdf_dst_law_idx       = u1_t_data;
    }
    else{
        u1_s_vdf_dst_law_idx       = u1_g_VDF_DST_LAW_IDX_DEF;
    }

    vd_s_VardefDestLawDBIdxJdg();
    vd_s_VardefDestDBIdxJdg();
    u1_s_vdf_dst_hdlside      = (U1)VDF_HDSIDE_LHD;
}
/*===================================================================================================================================*/
/*  void    vd_g_VardefDestMainTask(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_VardefDestMainTask(void)
{
    static const U2     u2_s_VDF_DST_RXINTVL = ((U2)2100U/ ((U2)VDF_MAIN_TICK * (U2)VDF_NUM_TSLOT));
    U1                  u1_t_rxcnt;
    U2                  u2_t_c_code;
    U1                  u1_t_dest_bdb;
    U1                  u1_t_strg_whl;

    u2_t_c_code   = (U2)VDF_DST_C_CODE_DEF;
    u1_t_dest_bdb = (U1)VDF_DST_DEST_BDB_DEF;
    u1_t_strg_whl = (U1)VDF_DST_STRG_WHL_DEF;
    u1_t_rxcnt = u1_g_VardefDestCfg(&u2_t_c_code, &u1_t_dest_bdb, &u1_t_strg_whl);

    if(u2_s_vdf_dst_intvl < (U2)U2_MAX){
        u2_s_vdf_dst_intvl++;
    }

    if(u1_s_vdf_dst_rxcnt != u1_t_rxcnt){
        if(u2_s_vdf_dst_intvl <= u2_s_VDF_DST_RXINTVL ){
            if(u2_s_vdf_dst_c_code_pre == u2_t_c_code){
                u2_s_vdf_dst_c_code = u2_t_c_code;
                vd_g_Rim_WriteU2(u2_g_VDF_DST_C_CODE_RIM_U2, u2_s_vdf_dst_c_code);
            }
            if(u1_s_vdf_dst_dest_bdb_pre == u1_t_dest_bdb){
                u1_s_vdf_dst_dest_bdb = u1_t_dest_bdb;
                vd_g_Rim_WriteU1(u2_g_VDF_DST_DEST_BDB_RIM_U1, u1_s_vdf_dst_dest_bdb);
            }
            if(u1_s_vdf_dst_strg_whl_pre == u1_t_strg_whl){
                u1_s_vdf_dst_strg_whl = u1_t_strg_whl;
                vd_g_Rim_WriteU1(u2_g_VDF_DST_STRG_WHL_RIM_U1, u1_s_vdf_dst_strg_whl);
            }
        }
        u2_s_vdf_dst_intvl = (U2)0U;
    }

    u1_s_vdf_dst_rxcnt        = u1_t_rxcnt;
    u2_s_vdf_dst_c_code_pre   = u2_t_c_code;
    u1_s_vdf_dst_dest_bdb_pre = u1_t_dest_bdb;
    u1_s_vdf_dst_strg_whl_pre = u1_t_strg_whl;

    vd_s_VardefDestLawDBIdxJdg();
    vd_s_VardefDestDBIdxJdg();
    vd_s_VardefDestHdlJdg(u1_s_vdf_dst_strg_whl);
}
/*===================================================================================================================================*/
/*  U1      u1_g_VardefDestLawDbfByPid(const U1 u1_a_LAW_DBF)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefDestLawDbfByPid(const U1 u1_a_LAW_DBF)
{
    return(u1_g_VardefDestLawCfgDBSup(u1_a_LAW_DBF, u1_s_vdf_dst_law_spec_ccode_idx, u1_s_vdf_dst_law_c_code_idx, u1_s_vdf_dst_law_dest_bdb_idx));
}
/*===================================================================================================================================*/
/*  U1      u1_g_VardefDestDbfByPid(const U1 u1_a_DBF)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefDestDbfByPid(const U1 u1_a_DBF)
{
    return(u1_g_VardefDestCfgDBSup(u1_a_DBF, u1_s_vdf_dst_c_code_idx, u1_s_vdf_dst_dest_bdb_idx));
}
/*===================================================================================================================================*/
/*  U1      u1_g_VardefStrng(void)                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefStrng(void)
{
    return(u1_s_vdf_dst_hdlside);
}
/*===================================================================================================================================*/
/*  U1      u1_g_VardefLawIdx(void)                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefLawIdx(void)
{
    return(u1_s_vdf_dst_law_spec_ccode_idx);
}
/*===================================================================================================================================*/
/*  static U2    u2_s_VardefDestCCodeHexToDec(const U2 u2_a_HEX_C_CODE);                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U2    u2_s_VardefDestCCodeHexToDec(const U2 u2_a_HEX_C_CODE)
{
    static const U1 u1_s_VDF_DST_C_CODE_MSK  = (U1)0x0FU;
    static const U1 u1_s_VDF_DST_C_CODE_MAX  = (U1)0x09U;
    static const U1 u1_s_VDF_DST_C_CODE1_BIT = (U1)8U;
    static const U1 u1_s_VDF_DST_C_CODE2_BIT = (U1)4U;
    static const U1 u1_s_VDF_DST_HUNDREDS    = (U1)100U;
    static const U1 u1_s_VDF_DST_TENS        = (U1)10U;

    U2 u2_t_dec_ccode;
    U1 u1_t_hundreds_place;
    U1 u1_t_tens_place;
    U1 u1_t_ones_place;

    u2_t_dec_ccode      = (U2)0U;
    u1_t_hundreds_place = (U1)0U;
    u1_t_tens_place     = (U1)0U;
    u1_t_ones_place     = (U1)0U;

    /* Find the digit in each place */
    u1_t_hundreds_place = (U1)((u2_a_HEX_C_CODE >> u1_s_VDF_DST_C_CODE1_BIT) & u1_s_VDF_DST_C_CODE_MSK);
    u1_t_tens_place     = (U1)((u2_a_HEX_C_CODE >> u1_s_VDF_DST_C_CODE2_BIT) & u1_s_VDF_DST_C_CODE_MSK);
    u1_t_ones_place     = (U1)( u2_a_HEX_C_CODE & u1_s_VDF_DST_C_CODE_MSK );

    if ((u1_s_VDF_DST_C_CODE_MAX >= u1_t_hundreds_place) && \
        (u1_s_VDF_DST_C_CODE_MAX >= u1_t_tens_place) && \
        (u1_s_VDF_DST_C_CODE_MAX >= u1_t_ones_place)) {
        /* Convert to decimal */
        u2_t_dec_ccode = (U2)((U2)u1_t_hundreds_place * (U2)u1_s_VDF_DST_HUNDREDS);
        u2_t_dec_ccode = (U2)(u2_t_dec_ccode + (U2)((U2)u1_t_tens_place * (U2)u1_s_VDF_DST_TENS));
        u2_t_dec_ccode = (U2)(u2_t_dec_ccode + (U2)u1_t_ones_place);
    }
    else {
        /* u2_t_dec_ccode = (U2)0U */
    }
    return(u2_t_dec_ccode);
}
/*===================================================================================================================================*/
/*  static void    vd_s_VardefDestLawDBIdxJdg(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VardefDestLawDBIdxJdg(void)
{
    static const U1 u1_s_VDF_DST_STRG_WHL_BIT = (U1)8U;
    U1    u1_t_idx_loop;
    U2    u2_t_dec_ccode;
    U1    u1_t_spec_ccode_idx;
    U1    u1_t_law_ccode_idx;
    U1    u1_t_law_destbdb_idx;
    U2    u2_t_dest_bdb_val;
    U1    u1_t_mcuid0809;
    U1    u1_t_mcuid0810;
    U1    u1_t_mcuid3020;

    u2_t_dest_bdb_val = ((U2)u1_s_vdf_dst_dest_bdb | (U2)((U2)u1_s_vdf_dst_strg_whl << u1_s_VDF_DST_STRG_WHL_BIT));

    u1_t_spec_ccode_idx = (U1)U1_MAX;
    u2_t_dec_ccode = u2_s_VardefDestCCodeHexToDec(u2_s_vdf_dst_c_code);
    for (u1_t_idx_loop = (U1)0U; u1_t_idx_loop < u1_g_VDF_DST_SPEC_NUM_C_CODE; u1_t_idx_loop++) {
        if ((*(st_gp_VDF_DST_SPEC_C_CODE[u1_t_idx_loop].u2p_t_C_CODE) == u2_t_dec_ccode) && \
            (*(st_gp_VDF_DST_SPEC_C_CODE[u1_t_idx_loop].u2p_t_C_CODE) != (U2)VDF_DST_SPEC_C_CODE_INV)) {
            u1_t_spec_ccode_idx = *(st_gp_VDF_DST_SPEC_C_CODE[u1_t_idx_loop].u1p_t_C_CODE_IDX);
        }
        else {
            /* u1_t_spec_ccode_idx = (U1)U1_MAX; */
        }
    }

    u1_t_law_ccode_idx = (U1)U1_MAX;
    for (u1_t_idx_loop = (U1)0U; u1_t_idx_loop < u1_g_VDF_DST_LAW_NUM_C_CODE; u1_t_idx_loop++) {
        if (u2_s_vdf_dst_c_code == st_gp_VDF_DST_LAW_C_CODE[u1_t_idx_loop].u2_t_c_code) {
            u1_t_law_ccode_idx = st_gp_VDF_DST_LAW_C_CODE[u1_t_idx_loop].u1_t_c_code_idx;
        }
        else {
            /* u1_t_law_ccode_idx = (U1)U1_MAX; */
        }
    }

    u1_t_mcuid0809 = u1_g_VardefOmusMCUID0809();
    u1_t_mcuid0810 = u1_g_VardefOmusMCUID0810();
    if ((u1_t_law_ccode_idx == u1_g_VDF_DST_LAW_C_CODE_KOR) &&
        (u1_t_mcuid0810     == (U1)CALIB_MCUID0810_FMVSS)) {
        u1_t_law_ccode_idx = u1_g_VDF_DST_LAW_KOR_FMVSS;
    }
    else if ((u1_t_law_ccode_idx == u1_g_VDF_DST_LAW_C_CODE_MEX) &&
             (u1_t_mcuid0809     == (U1)CALIB_MCUID0809_FMVSS)) {
        u1_t_law_ccode_idx = u1_g_VDF_DST_LAW_MEX_FMVSS;
    }
    else {
        /* Do Nothing */
    }

    u1_t_law_destbdb_idx = (U1)U1_MAX;
    for (u1_t_idx_loop = (U1)0U; u1_t_idx_loop < u1_g_VDF_DST_LAW_NUM_DEST_BDB; u1_t_idx_loop++) {
        if ((u2_t_dest_bdb_val & st_gp_VDF_DST_LAW_DEST_BDB_JDGIDX[u1_t_idx_loop].u2_dest_bdb_mask) == st_gp_VDF_DST_LAW_DEST_BDB_JDGIDX[u1_t_idx_loop].u2_dest_bdb_val) {
            u1_t_law_destbdb_idx = st_gp_VDF_DST_LAW_DEST_BDB_JDGIDX[u1_t_idx_loop].u1_t_dest_bdb_idx;
        }
        else {
            /* Do Nothing */
        }
    }

    u1_t_mcuid3020 = u1_g_VardefOmusMCUID3020();
    if (((u1_t_law_destbdb_idx == u1_g_VDF_DST_LAW_DEST_BDB_B_GNR_L) ||
         (u1_t_law_destbdb_idx == u1_g_VDF_DST_LAW_DEST_BDB_B_GNR_R)) &&
         (u1_t_mcuid3020       == (U1)CALIB_MCUID3020_FMVSS)) {
        u1_t_law_destbdb_idx = u1_g_VDF_DST_LAW_DEST_BDB_B_GNR_FMVSS;
    }

    if (u1_t_spec_ccode_idx < u1_g_VDF_DST_SPEC_NUM_C_CODE) {
        u1_s_vdf_dst_law_spec_ccode_idx = u1_t_spec_ccode_idx;
        u1_s_vdf_dst_law_c_code_idx = u1_g_VDF_DST_LAW_C_CODE_IDX_DEF;
        u1_s_vdf_dst_law_dest_bdb_idx = u1_g_VardefDestLawCfgBdbDefJdg();
        u1_s_vdf_dst_law_idx = u1_s_vdf_dst_law_spec_ccode_idx;
    }
    else if (u1_t_law_ccode_idx < u1_g_VDF_DST_LAW_NUM_C_CODE_REG) {
        u1_s_vdf_dst_law_spec_ccode_idx = u1_g_VDF_DST_LAW_SPEC_IDX_DEF;
        u1_s_vdf_dst_law_c_code_idx = u1_t_law_ccode_idx;
        u1_s_vdf_dst_law_dest_bdb_idx = u1_g_VardefDestLawCfgBdbDefJdg();
        u1_s_vdf_dst_law_idx = u1_s_vdf_dst_law_c_code_idx + u1_g_VDF_DST_SPEC_NUM_C_CODE;
    }
    else if (u1_t_law_destbdb_idx < u1_g_VDF_DST_LAW_NUM_DEST_BDB_REG) {
        u1_s_vdf_dst_law_spec_ccode_idx = u1_g_VDF_DST_LAW_SPEC_IDX_DEF;
        u1_s_vdf_dst_law_c_code_idx = u1_g_VDF_DST_LAW_C_CODE_IDX_DEF;
        u1_s_vdf_dst_law_dest_bdb_idx = u1_t_law_destbdb_idx;
        u1_s_vdf_dst_law_idx = (U1)(u1_s_vdf_dst_law_dest_bdb_idx + u1_g_VDF_DST_SPEC_NUM_C_CODE + u1_g_VDF_DST_LAW_NUM_C_CODE_REG);
    }
    else if (u1_s_vdf_dst_law_idx < u1_g_VDF_DST_SPEC_NUM_C_CODE) {
        u1_s_vdf_dst_law_spec_ccode_idx = u1_s_vdf_dst_law_idx;
        u1_s_vdf_dst_law_c_code_idx = u1_g_VDF_DST_LAW_C_CODE_IDX_DEF;
        u1_s_vdf_dst_law_dest_bdb_idx = u1_g_VardefDestLawCfgBdbDefJdg();
    }
    else if (u1_s_vdf_dst_law_idx < (U1)(u1_g_VDF_DST_SPEC_NUM_C_CODE + u1_g_VDF_DST_LAW_NUM_C_CODE_REG)) {
        u1_s_vdf_dst_law_spec_ccode_idx = u1_g_VDF_DST_LAW_SPEC_IDX_DEF;
        u1_s_vdf_dst_law_c_code_idx = (U1)(u1_s_vdf_dst_law_idx - u1_g_VDF_DST_SPEC_NUM_C_CODE);
        u1_s_vdf_dst_law_dest_bdb_idx = u1_g_VardefDestLawCfgBdbDefJdg();
    }
    else if (u1_s_vdf_dst_law_idx < (U1)(u1_g_VDF_DST_SPEC_NUM_C_CODE + u1_g_VDF_DST_LAW_NUM_C_CODE_REG + u1_g_VDF_DST_LAW_NUM_DEST_BDB_REG)) {
        u1_s_vdf_dst_law_spec_ccode_idx = u1_g_VDF_DST_LAW_SPEC_IDX_DEF;
        u1_s_vdf_dst_law_c_code_idx = u1_g_VDF_DST_LAW_C_CODE_IDX_DEF;
        u1_s_vdf_dst_law_dest_bdb_idx = (U1)(u1_s_vdf_dst_law_idx - u1_g_VDF_DST_SPEC_NUM_C_CODE - u1_g_VDF_DST_LAW_NUM_C_CODE_REG);
    }
    else {
        u1_s_vdf_dst_law_spec_ccode_idx = u1_g_VDF_DST_LAW_SPEC_IDX_DEF;
        u1_s_vdf_dst_law_c_code_idx = u1_g_VDF_DST_LAW_C_CODE_IDX_DEF;
        u1_s_vdf_dst_law_dest_bdb_idx = u1_g_VardefDestLawCfgBdbDefJdg();
        u1_s_vdf_dst_law_idx = u1_g_VDF_DST_LAW_IDX_DEF;
    }
    vd_g_Rim_WriteU1(u2_g_VDF_DST_LAW_IDX_RIM_U1, u1_s_vdf_dst_law_idx);
}
/*===================================================================================================================================*/
/*  static void    vd_s_VardefDestDBIdxJdg(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VardefDestDBIdxJdg(void)
{
    static const U1 u1_s_VDF_DST_STRG_WHL_BIT = (U1)8U;
    U1    u1_t_idx_loop;
    U1    u1_t_ccode_idx;
    U1    u1_t_destbdb_idx;
    U2    u2_t_dest_bdb_val;

    u2_t_dest_bdb_val = ((U2)u1_s_vdf_dst_dest_bdb | (U2)((U2)u1_s_vdf_dst_strg_whl << u1_s_VDF_DST_STRG_WHL_BIT));

    u1_t_ccode_idx = (U1)U1_MAX;
    for(u1_t_idx_loop = (U1)0U; u1_t_idx_loop < u1_g_VDF_DST_NUM_C_CODE; u1_t_idx_loop++){
        if(u2_s_vdf_dst_c_code ==  u2_gp_VDF_DST_C_CODE[u1_t_idx_loop]){
            u1_t_ccode_idx = u1_t_idx_loop;
        }
    }

    u1_t_destbdb_idx = (U1)U1_MAX;
    for(u1_t_idx_loop = (U1)0U; u1_t_idx_loop < u1_g_VDF_DST_NUM_DEST_BDB; u1_t_idx_loop++){
        if((u2_t_dest_bdb_val & st_gp_VDF_DST_DEST_BDB_JDGIDX[u1_t_idx_loop].u2_dest_bdb_mask) == st_gp_VDF_DST_DEST_BDB_JDGIDX[u1_t_idx_loop].u2_dest_bdb_val){
            u1_t_destbdb_idx = u1_t_idx_loop;
        }
    }

    if(u1_t_ccode_idx < u1_g_VDF_DST_NUM_C_CODE){
        u1_s_vdf_dst_c_code_idx   = u1_t_ccode_idx;
        u1_s_vdf_dst_dest_bdb_idx = u1_g_VDF_DST_DEST_BDB_IDX_DEF;
        u1_s_vdf_dst_idx          = u1_s_vdf_dst_c_code_idx;
    }
    else if(u1_t_destbdb_idx < u1_g_VDF_DST_NUM_DEST_BDB){
        u1_s_vdf_dst_c_code_idx   = u1_g_VDF_DST_C_CODE_IDX_DEF;
        u1_s_vdf_dst_dest_bdb_idx = u1_t_destbdb_idx;
        u1_s_vdf_dst_idx          = (U1)(u1_s_vdf_dst_dest_bdb_idx + u1_g_VDF_DST_NUM_C_CODE);
    }
    else if(u1_s_vdf_dst_idx < u1_g_VDF_DST_NUM_C_CODE){
        u1_s_vdf_dst_c_code_idx   = u1_s_vdf_dst_idx;
        u1_s_vdf_dst_dest_bdb_idx = u1_g_VDF_DST_DEST_BDB_IDX_DEF;
    }
    else if(u1_s_vdf_dst_idx < (U1)(u1_g_VDF_DST_NUM_C_CODE + u1_g_VDF_DST_NUM_DEST_BDB)){
        u1_s_vdf_dst_c_code_idx   = u1_g_VDF_DST_C_CODE_IDX_DEF;
        u1_s_vdf_dst_dest_bdb_idx = (U1)(u1_s_vdf_dst_idx - u1_g_VDF_DST_NUM_C_CODE);
    }
    else{
        u1_s_vdf_dst_c_code_idx   = u1_g_VDF_DST_C_CODE_IDX_DEF;
        u1_s_vdf_dst_dest_bdb_idx = u1_g_VDF_DST_DEST_BDB_IDX_DEF;
        u1_s_vdf_dst_idx          = u1_g_VDF_DST_IDX_DEF;
    }
    vd_g_Rim_WriteU1(u2_g_VDF_DST_IDX_RIM_U1, u1_s_vdf_dst_idx);
}
/*===================================================================================================================================*/
/*  static void    vd_s_VardefDestHdlJdg(const U1 u1_a_STRG_WHL)                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VardefDestHdlJdg(const U1 u1_a_STRG_WHL)
{
    switch(u1_a_STRG_WHL)
    {
        case VDF_DST_CANRX_STRGWHL_00:
            u1_s_vdf_dst_hdlside = (U1)VDF_HDSIDE_RHD;
            break;
        case VDF_DST_CANRX_STRGWHL_01:
            u1_s_vdf_dst_hdlside = (U1)VDF_HDSIDE_LHD;
            break;
        case VDF_DST_CANRX_STRGWHL_10:
            u1_s_vdf_dst_hdlside = (U1)VDF_HDSIDE_RHD;
            break;
        default:
            u1_s_vdf_dst_hdlside = u1_g_VDF_DST_HDSIDE_DEF;
            break;
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
/*  1.0.0     1/25/2021  SF       New.                                                                                               */
/*  2.0.0     1/19/2024  HF       for 19PFv3.                                                                                        */
/*  2.1.0    10/28/2024  AA       M_DESTVARI-CSTD-A0-07 spec update                                                                  */
/*  2.2.0     6/27/2025  SN       for BEV System_Consideration_2.(MET-M_DESTVARI-CSTD-A0-06)                                         */
/*  3.0.0     1/20/2026  YN       for BEV FF2.(MET-M_DESTVARI-CSTD-0-01)                                                             */
/*                                                                                                                                   */
/*  * SF = Seiya Fukutome, DENSO-TECHNO                                                                                              */
/*  * HF = Hinari Fukamachi, KSE                                                                                                     */
/*  * AA = Anna Asuncion, DTPH                                                                                                       */
/*  * SN = Shizuka Nakajima, KSE                                                                                                     */
/*  * YN = Yujiro Nagaya, Denso Techno                                                                                               */
/*                                                                                                                                   */
/*===================================================================================================================================*/
