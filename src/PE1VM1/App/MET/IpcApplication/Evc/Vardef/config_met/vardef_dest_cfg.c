/* 2.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Vardef / Destination                                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VARDEF_DEST_CFG_C_MAJOR                 (2)
#define VARDEF_DEST_CFG_C_MINOR                 (1)
#define VARDEF_DEST_CFG_C_PATCH                 (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "vardef_dest_cfg_private.h"

#include "locale.h"

#include "oxcan.h"

#include "rim_ctl.h"
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((VARDEF_DEST_CFG_C_MAJOR != VARDEF_DEST_CFG_H_MAJOR) || \
     (VARDEF_DEST_CFG_C_MINOR != VARDEF_DEST_CFG_H_MINOR) || \
     (VARDEF_DEST_CFG_C_PATCH != VARDEF_DEST_CFG_H_PATCH))
#error "vardef_dest_cfg.c and vardef_dest_cfg_private.h : source and header files are inconsistent!"
#endif

#if ((VARDEF_DEST_CFG_C_MAJOR != VARDEF_DEST_DBF_H_MAJOR) || \
     (VARDEF_DEST_CFG_C_MINOR != VARDEF_DEST_DBF_H_MINOR) || \
     (VARDEF_DEST_CFG_C_PATCH != VARDEF_DEST_DBF_H_PATCH))
#error "vardef_dest_cfg.c and vardef_dest_dbf.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VDF_DST_NUM_C_CODE                  (21U)

#define VDF_DST_NUM_C_CODE_REG              (23U)
#define VDF_DST_C_CODE_CAN                  (0U)
#define VDF_DST_C_CODE_KOR                  (1U)
#define VDF_DST_C_CODE_GBR                  (2U)
#define VDF_DST_C_CODE_MEX                  (3U)
#define VDF_DST_C_CODE_ZAF                  (4U)
#define VDF_DST_C_CODE_IND                  (5U)
#define VDF_DST_C_CODE_CHN                  (6U)
#define VDF_DST_C_CODE_BHR                  (7U)
#define VDF_DST_C_CODE_QAT                  (8U)
#define VDF_DST_C_CODE_KWT                  (9U)
#define VDF_DST_C_CODE_UAE                  (10U)
#define VDF_DST_C_CODE_SAU                  (11U)
#define VDF_DST_C_CODE_OMN                  (12U)
#define VDF_DST_C_CODE_HKG                  (13U)
#define VDF_DST_C_CODE_MAC                  (14U)
#define VDF_DST_C_CODE_AUS                  (15U)
#define VDF_DST_C_CODE_PNG                  (16U)
#define VDF_DST_C_CODE_NZL                  (17U)
#define VDF_DST_C_CODE_SLB                  (18U)
#define VDF_DST_C_CODE_TWN                  (19U)
#define VDF_DST_C_CODE_SGP                  (20U)
#define VDF_DST_C_CODE_KOR_FMVSS            (21U)
#define VDF_DST_C_CODE_MEX_FMVSS            (22U)

#define VDF_LANG_DST_NUM_C_CODE             (63U)
#define VDF_LANG_DST_C_CODE_CAN             (0U)
#define VDF_LANG_DST_C_CODE_KOR             (1U)
#define VDF_LANG_DST_C_CODE_MEX             (2U)
#define VDF_LANG_DST_C_CODE_ZAF             (3U)
#define VDF_LANG_DST_C_CODE_IND             (4U)
#define VDF_LANG_DST_C_CODE_CHN             (5U)
#define VDF_LANG_DST_C_CODE_BHR             (6U)
#define VDF_LANG_DST_C_CODE_QAT             (7U)
#define VDF_LANG_DST_C_CODE_KWT             (8U)
#define VDF_LANG_DST_C_CODE_UAE             (9U)
#define VDF_LANG_DST_C_CODE_SAU             (10U)
#define VDF_LANG_DST_C_CODE_OMN             (11U)
#define VDF_LANG_DST_C_CODE_HKG             (12U)
#define VDF_LANG_DST_C_CODE_MAC             (13U)
#define VDF_LANG_DST_C_CODE_AUS             (14U)
#define VDF_LANG_DST_C_CODE_PNG             (15U)
#define VDF_LANG_DST_C_CODE_NZL             (16U)
#define VDF_LANG_DST_C_CODE_SLB             (17U)
#define VDF_LANG_DST_C_CODE_TWN             (18U)
#define VDF_LANG_DST_C_CODE_BRZ             (19U)
#define VDF_LANG_DST_C_CODE_ARG             (20U)
#define VDF_LANG_DST_C_CODE_BOL             (21U)
#define VDF_LANG_DST_C_CODE_COL             (22U)
#define VDF_LANG_DST_C_CODE_ECU             (23U)
#define VDF_LANG_DST_C_CODE_PRY             (24U)
#define VDF_LANG_DST_C_CODE_PER             (25U)
#define VDF_LANG_DST_C_CODE_URY             (26U)
#define VDF_LANG_DST_C_CODE_VEN             (27U)
#define VDF_LANG_DST_C_CODE_TUR             (28U)
#define VDF_LANG_DST_C_CODE_RUS             (29U)
#define VDF_LANG_DST_C_CODE_BLR             (30U)
#define VDF_LANG_DST_C_CODE_AZR             (31U)
#define VDF_LANG_DST_C_CODE_ARM             (32U)
#define VDF_LANG_DST_C_CODE_UZB             (33U)
#define VDF_LANG_DST_C_CODE_KAZ             (34U)
#define VDF_LANG_DST_C_CODE_KGZ             (35U)
#define VDF_LANG_DST_C_CODE_TJK             (36U)
#define VDF_LANG_DST_C_CODE_BRN             (37U)
#define VDF_LANG_DST_C_CODE_MMR             (38U)
#define VDF_LANG_DST_C_CODE_KHM             (39U)
#define VDF_LANG_DST_C_CODE_PRK             (40U)
#define VDF_LANG_DST_C_CODE_LAO             (41U)
#define VDF_LANG_DST_C_CODE_VNM             (42U)
#define VDF_LANG_DST_C_CODE_SGP             (43U)
#define VDF_LANG_DST_C_CODE_THA             (44U)
#define VDF_LANG_DST_C_CODE_MNG             (45U)
#define VDF_LANG_DST_C_CODE_MDV             (46U)
#define VDF_LANG_DST_C_CODE_IDN             (47U)
#define VDF_LANG_DST_C_CODE_TLS             (48U)
#define VDF_LANG_DST_C_CODE_PHL             (49U)
#define VDF_LANG_DST_C_CODE_MYS             (50U)
#define VDF_LANG_DST_C_CODE_VUT             (51U)
#define VDF_LANG_DST_C_CODE_NRU             (52U)
#define VDF_LANG_DST_C_CODE_FJI             (53U)
#define VDF_LANG_DST_C_CODE_TON             (54U)
#define VDF_LANG_DST_C_CODE_WSM             (55U)
#define VDF_LANG_DST_C_CODE_NCL             (56U)
#define VDF_LANG_DST_C_CODE_FSM             (57U)
#define VDF_LANG_DST_C_CODE_PYF             (58U)
#define VDF_LANG_DST_C_CODE_COK             (59U)
#define VDF_LANG_DST_C_CODE_KIR             (60U)
#define VDF_LANG_DST_C_CODE_NFK             (61U)
#define VDF_LANG_DST_C_CODE_PLW             (62U)

#define VDF_DST_NUM_DEST_BDB                (12U)
#define VDF_DST_DEST_BDB_A_USA              (0U)
#define VDF_DST_DEST_BDB_B_TUR              (1U)
#define VDF_DST_DEST_BDB_C_CHN              (2U)
#define VDF_DST_DEST_BDB_N_ZAF              (3U)
#define VDF_DST_DEST_BDB_Q_AUS              (4U)
#define VDF_DST_DEST_BDB_V_MDE              (5U)
#define VDF_DST_DEST_BDB_W_EU               (6U)
#define VDF_DST_DEST_BDB_X_RUS              (7U)
#define VDF_DST_DEST_BDB_Z_NZL              (8U)
#define VDF_DST_DEST_BDB_B_JPN              (9U)
#define VDF_DST_DEST_BDB_B_GNR_L            (10U)
#define VDF_DST_DEST_BDB_B_GNR_R            (11U)

#define VDF_LANG_DST_NUM_DEST_BDB           (11U)
#define VDF_LANG_DST_DEST_BDB_A_USA         (0U)
#define VDF_LANG_DST_DEST_BDB_B_TUR         (1U)
#define VDF_LANG_DST_DEST_BDB_C_CHN         (2U)
#define VDF_LANG_DST_DEST_BDB_Q_AUS         (3U)
#define VDF_LANG_DST_DEST_BDB_V_MDE         (4U)
#define VDF_LANG_DST_DEST_BDB_W_EU          (5U)
#define VDF_LANG_DST_DEST_BDB_X_RUS         (6U)
#define VDF_LANG_DST_DEST_BDB_Z_NZL         (7U)
#define VDF_LANG_DST_DEST_BDB_B_JPN         (8U)
#define VDF_LANG_DST_DEST_BDB_B_GNR_L       (9U)
#define VDF_LANG_DST_DEST_BDB_B_GNR_R       (10U)

#define VDF_NUM_PTSYS                       (16U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static inline U1    u1_s_VardefDestCfgCalibU1NumChk(const U1 u1_a_CALIBID, const U1 u1_a_NUM, const U1 u1_a_DEF);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if 0   /* BEV Rebase provisionally */
const U2        u2_g_VDF_DST_C_CODE_RIM_U2      = (U2)RIMID_U2_VDF_C_CODE;
const U2        u2_g_VDF_DST_DEST_BDB_RIM_U1    = (U2)RIMID_U1_VDF_DEST_BDB;
const U2        u2_g_VDF_DST_STRG_WHL_RIM_U1    = (U2)RIMID_U1_VDF_STRG_WHL;
const U2        u2_g_VDF_DST_IDX_RIM_U1         = (U2)RIMID_U1_VDF_DST_IDX;
const U2        u2_g_VDF_LANG_DST_IDX_RIM_U1    = (U2)RIMID_U1_VDF_LANG_DST_IDX;
#else   /* BEV Rebase provisionally */
const U2        u2_g_VDF_DST_C_CODE_RIM_U2      = U2_MAX;
const U2        u2_g_VDF_DST_DEST_BDB_RIM_U1    = U2_MAX;
const U2        u2_g_VDF_DST_STRG_WHL_RIM_U1    = U2_MAX;
const U2        u2_g_VDF_DST_IDX_RIM_U1         = U2_MAX;
const U2        u2_g_VDF_LANG_DST_IDX_RIM_U1    = U2_MAX;
#endif   /* BEV Rebase provisionally */

#if 0   /* BEV Rebase provisionally */
const U1        u1_g_VDF_DST_RXEV_CNT_INIT      = (U1)OXCAN_RX_RXEV_CNT_UNK;
#else   /* BEV Rebase provisionally */
const U1        u1_g_VDF_DST_RXEV_CNT_INIT      = (U1)OXCAN_RXD_EVC_UNK;
#endif   /* BEV Rebase provisionally */

const U1        u1_g_VDF_DST_C_CODE_IDX_DEF     = (U1)U1_MAX;
const U1        u1_g_VDF_DST_DEST_BDB_IDX_DEF   = (U1)VDF_DST_DEST_BDB_B_GNR_L;
const U1        u1_g_VDF_LANG_DST_IDX_DEF       = (U1)VDF_LANG_DST_DEST_BDB_B_GNR_L;
const U1        u1_g_VDF_DST_IDX_DEF            = (U1)U1_MAX;

const U1        u1_g_VDF_DST_HDSIDE_DEF         = (U1)VDF_HDSIDE_LHD;

const U1        u1_g_VDF_DST_NUM_C_CODE         = (U1)VDF_DST_NUM_C_CODE;
const U1        u1_g_VDF_DST_NUM_DEST_BDB       = (U1)VDF_DST_NUM_DEST_BDB;

const U1        u1_g_VDF_LANG_DST_NUM_C_CODE    = (U1)VDF_LANG_DST_NUM_C_CODE;
const U1        u1_g_VDF_LANG_DST_NUM_DEST_BDB  = (U1)VDF_LANG_DST_NUM_DEST_BDB;

const U1        u1_g_VDF_DST_NUM_C_CODE_REG     = (U1)VDF_DST_NUM_C_CODE_REG;
const U1        u1_g_VDF_DST_C_CODE_KOR         = (U1)VDF_DST_C_CODE_KOR;
const U1        u1_g_VDF_DST_C_CODE_MEX         = (U1)VDF_DST_C_CODE_MEX;
const U1        u1_g_VDF_DST_C_CODE_KOR_FMVSS   = (U1)VDF_DST_C_CODE_KOR_FMVSS;
const U1        u1_g_VDF_DST_C_CODE_MEX_FMVSS   = (U1)VDF_DST_C_CODE_MEX_FMVSS;

const ST_VDF_DST_C_CODE    st_gp_VDF_DST_C_CODE[VDF_DST_NUM_C_CODE] = {
/*  u2_t_c_code         u1_t_c_code_idx                                                 */
    { (U2)0x0102U     , (U1)VDF_DST_C_CODE_CAN },           /* Canada                   */
    { (U2)0x0719U     , (U1)VDF_DST_C_CODE_KOR },           /* Rep of Korea             */
    { (U2)0x0408U     , (U1)VDF_DST_C_CODE_GBR },           /* United Kingdom           */
    { (U2)0x0209U     , (U1)VDF_DST_C_CODE_MEX },           /* Mexico                   */
    { (U2)0x0537U     , (U1)VDF_DST_C_CODE_ZAF },           /* South Africa             */
    { (U2)0x0709U     , (U1)VDF_DST_C_CODE_IND },           /* India                    */
    { (U2)0x0707U     , (U1)VDF_DST_C_CODE_CHN },           /* China                    */
    { (U2)0x0611U     , (U1)VDF_DST_C_CODE_BHR },           /* Bahrain                  */
    { (U2)0x0612U     , (U1)VDF_DST_C_CODE_QAT },           /* Qatar                    */
    { (U2)0x0613U     , (U1)VDF_DST_C_CODE_KWT },           /* Kuwait                   */
    { (U2)0x0615U     , (U1)VDF_DST_C_CODE_UAE },           /* UAE                      */
    { (U2)0x0618U     , (U1)VDF_DST_C_CODE_SAU },           /* Saudi Arabia             */
    { (U2)0x0620U     , (U1)VDF_DST_C_CODE_OMN },           /* Oman                     */
    { (U2)0x0708U     , (U1)VDF_DST_C_CODE_HKG },           /* Hong Kong                */
    { (U2)0x0726U     , (U1)VDF_DST_C_CODE_MAC },           /* Macao                    */
    { (U2)0x0801U     , (U1)VDF_DST_C_CODE_AUS },           /* Australia                */
    { (U2)0x0808U     , (U1)VDF_DST_C_CODE_PNG },           /* Papua New Guinea         */
    { (U2)0x0809U     , (U1)VDF_DST_C_CODE_NZL },           /* New Zealand              */
    { (U2)0x0813U     , (U1)VDF_DST_C_CODE_SLB },           /* Solomon Islands          */
    { (U2)0x0721U     , (U1)VDF_DST_C_CODE_TWN },           /* Taiwan                   */
    { (U2)0x0718U     , (U1)VDF_DST_C_CODE_SGP }            /* Singapore                */
};

const U2    u2_gp_VDF_LANG_DST_C_CODE[VDF_LANG_DST_NUM_C_CODE] = {
    (U2)0x0102U,             /* Canada                   */
    (U2)0x0719U,             /* Rep of Korea             */
    (U2)0x0209U,             /* Mexico                   */
    (U2)0x0537U,             /* South Africa             */
    (U2)0x0709U,             /* India                    */
    (U2)0x0707U,             /* China                    */
    (U2)0x0611U,             /* Bahrain                  */
    (U2)0x0612U,             /* Qatar                    */
    (U2)0x0613U,             /* Kuwait                   */
    (U2)0x0615U,             /* UAE                      */
    (U2)0x0618U,             /* Saudi Arabia             */
    (U2)0x0620U,             /* Oman                     */
    (U2)0x0708U,             /* Hong Kong                */
    (U2)0x0726U,             /* Macao                    */
    (U2)0x0801U,             /* Australia                */
    (U2)0x0808U,             /* Papua New Guinea         */
    (U2)0x0809U,             /* New Zealand              */
    (U2)0x0813U,             /* Solomon Islands          */
    (U2)0x0721U,             /* Taiwan                   */
    (U2)0x0303U,             /* Brazil                   */
    (U2)0x0301U,             /* Argentina                */
    (U2)0x0302U,             /* Bolivia                  */
    (U2)0x0306U,             /* Colombia                 */
    (U2)0x0307U,             /* Ecuador                  */
    (U2)0x0313U,             /* Paraguay                 */
    (U2)0x0314U,             /* Peru                     */
    (U2)0x0315U,             /* Uruguay                  */
    (U2)0x0316U,             /* Venezuela                */
    (U2)0x0616U,             /* Turkey                   */
    (U2)0x0465U,             /* Russian Federation       */
    (U2)0x0444U,             /* Belarus                  */
    (U2)0x0446U,             /* Azerbaijan               */
    (U2)0x0447U,             /* Armenia                  */
    (U2)0x0460U,             /* Uzbekistan               */
    (U2)0x0461U,             /* Kazakhstan               */
    (U2)0x0462U,             /* Kyrgyzstan               */
    (U2)0x0463U,             /* Tajikistan               */
    (U2)0x0703U,             /* Brunei Darussalam        */
    (U2)0x0704U,             /* Myanmar                  */
    (U2)0x0705U,             /* Cambodia                 */
    (U2)0x0710U,             /* North Korea              */
    (U2)0x0711U,             /* Laos                     */
    (U2)0x0715U,             /* VietNam                  */
    (U2)0x0718U,             /* Singapore                */
    (U2)0x0722U,             /* Thailand                 */
    (U2)0x0725U,             /* Mongolia                 */
    (U2)0x0727U,             /* Maldives                 */
    (U2)0x0807U,             /* Indonesia                */
    (U2)0x0810U,             /* Timor Leste              */
    (U2)0x0811U,             /* Philippines              */
    (U2)0x0812U,             /* Malaysia                 */
    (U2)0x0805U,             /* Vanuatu                  */
    (U2)0x0803U,             /* Nauru                    */
    (U2)0x0804U,             /* Fiji                     */
    (U2)0x0814U,             /* Tonga                    */
    (U2)0x0816U,             /* Samoa                    */
    (U2)0x0817U,             /* New Caledonia            */
    (U2)0x0818U,             /* Micronesia               */
    (U2)0x0824U,             /* Tahiti                   */
    (U2)0x0826U,             /* Cook Islands             */
    (U2)0x0828U,             /* Kiribati                 */
    (U2)0x0829U,             /* Norfolk Island           */
    (U2)0x0833U              /* Palau                    */
};

const ST_VDF_DST_DEST_BDB_JDGIDX st_gp_VDF_DST_DEST_BDB_JDGIDX[VDF_DST_NUM_DEST_BDB] = {
/*  u2_dest_bdb_val  u2_dest_bdb_mask             */
    {(U2)0x0041U    ,(U2)0x00ffU },    /* A_USA   */
    {(U2)0x0042U    ,(U2)0x00ffU },    /* B_TUR   */
    {(U2)0x0043U    ,(U2)0x00ffU },    /* C_CHN   */
    {(U2)0x004EU    ,(U2)0x00ffU },    /* N_ZAF   */
    {(U2)0x0051U    ,(U2)0x00ffU },    /* Q_AUS   */
    {(U2)0x0056U    ,(U2)0x00ffU },    /* V_MDE   */
    {(U2)0x0057U    ,(U2)0x00ffU },    /* W_EU    */
    {(U2)0x0058U    ,(U2)0x00ffU },    /* X_RUS   */
    {(U2)0x005AU    ,(U2)0x00ffU },    /* Z_NZL   */
    {(U2)0x0000U    ,(U2)0x03ffU },    /* B_JPN   */
    {(U2)0x0100U    ,(U2)0x03ffU },    /* B_GNR_L */
    {(U2)0x0200U    ,(U2)0x03ffU }     /* B_GNR_R */
};

const ST_VDF_DST_DEST_BDB_JDGIDX st_gp_VDF_LANG_DST_DEST_BDB_JDGIDX[VDF_LANG_DST_NUM_DEST_BDB] = {
/*  u2_dest_bdb_val  u2_dest_bdb_mask             */
    {(U2)0x0041U    ,(U2)0x00ffU },    /* A_USA   */
    {(U2)0x0042U    ,(U2)0x00ffU },    /* B_TUR   */
    {(U2)0x0043U    ,(U2)0x00ffU },    /* C_CHN   */
    {(U2)0x0051U    ,(U2)0x00ffU },    /* Q_AUS   */
    {(U2)0x0056U    ,(U2)0x00ffU },    /* V_MDE   */
    {(U2)0x0057U    ,(U2)0x00ffU },    /* W_EU    */
    {(U2)0x0058U    ,(U2)0x00ffU },    /* X_RUS   */
    {(U2)0x005AU    ,(U2)0x00ffU },    /* Z_NZL   */
    {(U2)0x0000U    ,(U2)0x03ffU },    /* B_JPN   */
    {(U2)0x0100U    ,(U2)0x03ffU },    /* B_GNR_L */
    {(U2)0x0200U    ,(U2)0x03ffU }     /* B_GNR_R */
};

static const U1    u1_sp2_VDF_DST_CCODESUP[VDF_DST_NUM_C_CODE_REG][VDF_DEST_DBF_NBYTE] = {
     /* DEFUNIT_SPD               DEFUNIT_DST              DEFUNIT_FUECO                DEFUNIT_ELECO                  UNITSLCT_FUECO                                                                                                                     UNITSLCT_DEST           TIMEFMT               4WDSYS               CALDSPTYP                    SMASTAMID                 TEMPCHR               FUGAUGE              ENGUNT                EUSPDSCALE               TTTRCOFF                 TTVSCEXP                BZ_SBW_SUP            ECOJUDGE    MDLEST_WRN   BZ_REV_DST           SEATBLT_CONST               SUBDIGSPD                SPDTLRNC                   CHN_REQ     TTBRAKE               TTABS               TTEPBPKB                TTTAILHEAD                TTCHECKEG               TMNT        STPIND     UNIT_AMBTMP               PRESSUNIT                    */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)UNIT_VAL_FUECO_LP100KM , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM | (U1)VDF_UNIT_FUECO_BIT_MPG_USA | (U1)VDF_UNIT_FUECO_BIT_MPG_UKIMP , (U1)VDF_UNIT_TYPE_NA  , (U1)TIMEFMT_VAL_12H , (U1)VDF_4WDSYS_AWD , (U1)VDF_CALDSPTYP_DDMMYYYY , (U1)VDF_SMASTAMID_NA    , (U1)VDF_TEMP_NML    , (U1)VDF_FUGAUGE_EF , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO155 , (U1)VDF_TT_VSCEXPERT1 , (U1)VDF_BZ_SBW_WITH , (U1)TRUE  , (U1)FALSE  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0603 , (U1)VDF_SUBDIGSPD_KMPH , (U1)VDF_SPDTLRNC_USA_CAN , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 , (U1)VDF_TTCHECKEG_NO1 , (U1)TRUE  , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL , (U1)VDF_PRESSUNIT_PSI },      /* Canada            */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)UNIT_VAL_FUECO_KMPL    , (U1)UNIT_VAL_ELECO_KMPKWH    , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     , (U1)VDF_UNIT_TYPE_JPN , (U1)TIMEFMT_VAL_12H , (U1)VDF_4WDSYS_AWD , (U1)VDF_CALDSPTYP_YYYYMMDD , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_TEMP_NML    , (U1)VDF_FUGAUGE_EF , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)VDF_BZ_SBW_WITH , (U1)FALSE , (U1)FALSE  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0606 , (U1)VDF_SUBDIGSPD_NON  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 , (U1)VDF_TTCHECKEG_NO1 , (U1)FALSE , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL , (U1)VDF_PRESSUNIT_KPA },      /* Rep of Korea_UNR  */
      { (U1)UNIT_VAL_SPEED_MPH  , (U1)UNIT_VAL_DIST_MILE , (U1)UNIT_VAL_FUECO_MPG_UK  , (U1)UNIT_VAL_ELECO_MILEPKWH  , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM | (U1)VDF_UNIT_FUECO_BIT_MPG_UK                                     , (U1)VDF_UNIT_TYPE_UK  , (U1)TIMEFMT_VAL_12H , (U1)VDF_4WDSYS_AWD , (U1)VDF_CALDSPTYP_DDMMYYYY , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_TEMP_NML    , (U1)VDF_FUGAUGE_1R , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_EU  , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)VDF_BZ_SBW_WITH , (U1)FALSE , (U1)FALSE  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0605 , (U1)VDF_SUBDIGSPD_MPH  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 , (U1)VDF_TTCHECKEG_NO1 , (U1)FALSE , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL , (U1)VDF_PRESSUNIT_BAR },      /* United Kingdom    */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)UNIT_VAL_FUECO_LP100KM , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM | (U1)VDF_UNIT_FUECO_BIT_MPG_USA | (U1)VDF_UNIT_FUECO_BIT_MPG_UKIMP , (U1)VDF_UNIT_TYPE_NA  , (U1)TIMEFMT_VAL_12H , (U1)VDF_4WDSYS_AWD , (U1)VDF_CALDSPTYP_DDMMYYYY , (U1)VDF_SMASTAMID_NA    , (U1)VDF_TEMP_NML    , (U1)VDF_FUGAUGE_EF , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO155 , (U1)VDF_TT_VSCEXPERT1 , (U1)VDF_BZ_SBW_WITH , (U1)FALSE , (U1)FALSE  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0604 , (U1)VDF_SUBDIGSPD_BOTH , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 , (U1)VDF_TTCHECKEG_NO1 , (U1)FALSE , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL , (U1)VDF_PRESSUNIT_PSI },      /* Mexico_UNR        */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)UNIT_VAL_FUECO_LP100KM , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     , (U1)VDF_UNIT_TYPE_EU  , (U1)TIMEFMT_VAL_12H , (U1)VDF_4WDSYS_AWD , (U1)VDF_CALDSPTYP_DDMMYYYY , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_TEMP_NML    , (U1)VDF_FUGAUGE_EF , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)VDF_BZ_SBW_WITH , (U1)FALSE , (U1)FALSE  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0605 , (U1)VDF_SUBDIGSPD_NON  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 , (U1)VDF_TTCHECKEG_NO1 , (U1)FALSE , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL , (U1)VDF_PRESSUNIT_KPA },      /* South Africa      */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)UNIT_VAL_FUECO_LP100KM , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     , (U1)VDF_UNIT_TYPE_EU  , (U1)TIMEFMT_VAL_12H , (U1)VDF_4WDSYS_4WD , (U1)VDF_CALDSPTYP_DDMMYYYY , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_TEMP_NML    , (U1)VDF_FUGAUGE_EF , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)VDF_BZ_SBW_WITH , (U1)FALSE , (U1)FALSE  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0605 , (U1)VDF_SUBDIGSPD_NON  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 , (U1)VDF_TTCHECKEG_NO1 , (U1)FALSE , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL , (U1)VDF_PRESSUNIT_KPA },      /* India             */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)UNIT_VAL_FUECO_LP100KM , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     , (U1)VDF_UNIT_TYPE_EU  , (U1)TIMEFMT_VAL_12H , (U1)VDF_4WDSYS_AWD , (U1)VDF_CALDSPTYP_YYYYMMDD , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_TEMP_NML    , (U1)VDF_FUGAUGE_EF , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)VDF_BZ_SBW_WITH , (U1)FALSE , (U1)FALSE  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0607 , (U1)VDF_SUBDIGSPD_NON  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)TRUE  , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 , (U1)VDF_TTCHECKEG_NO1 , (U1)FALSE , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL , (U1)VDF_PRESSUNIT_KPA },      /* China             */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)UNIT_VAL_FUECO_LP100KM , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     , (U1)VDF_UNIT_TYPE_EU  , (U1)TIMEFMT_VAL_12H , (U1)VDF_4WDSYS_4WD , (U1)VDF_CALDSPTYP_DDMMYYYY , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_TEMP_MDLEST , (U1)VDF_FUGAUGE_EF , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)VDF_BZ_SBW_WITH , (U1)FALSE , (U1)TRUE   , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0603 , (U1)VDF_SUBDIGSPD_NON  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 , (U1)VDF_TTCHECKEG_NO1 , (U1)FALSE , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL , (U1)VDF_PRESSUNIT_KPA },      /* Bahrain           */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)UNIT_VAL_FUECO_LP100KM , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     , (U1)VDF_UNIT_TYPE_EU  , (U1)TIMEFMT_VAL_12H , (U1)VDF_4WDSYS_4WD , (U1)VDF_CALDSPTYP_DDMMYYYY , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_TEMP_MDLEST , (U1)VDF_FUGAUGE_EF , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)VDF_BZ_SBW_WITH , (U1)FALSE , (U1)TRUE   , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0603 , (U1)VDF_SUBDIGSPD_NON  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 , (U1)VDF_TTCHECKEG_NO1 , (U1)FALSE , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL , (U1)VDF_PRESSUNIT_KPA },      /* Qatar             */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)UNIT_VAL_FUECO_LP100KM , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     , (U1)VDF_UNIT_TYPE_EU  , (U1)TIMEFMT_VAL_12H , (U1)VDF_4WDSYS_4WD , (U1)VDF_CALDSPTYP_DDMMYYYY , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_TEMP_MDLEST , (U1)VDF_FUGAUGE_EF , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)VDF_BZ_SBW_WITH , (U1)FALSE , (U1)TRUE   , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0603 , (U1)VDF_SUBDIGSPD_NON  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 , (U1)VDF_TTCHECKEG_NO1 , (U1)FALSE , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL , (U1)VDF_PRESSUNIT_KPA },      /* Kuwait            */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)UNIT_VAL_FUECO_LP100KM , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     , (U1)VDF_UNIT_TYPE_EU  , (U1)TIMEFMT_VAL_12H , (U1)VDF_4WDSYS_4WD , (U1)VDF_CALDSPTYP_DDMMYYYY , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_TEMP_MDLEST , (U1)VDF_FUGAUGE_EF , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)VDF_BZ_SBW_WITH , (U1)FALSE , (U1)TRUE   , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0603 , (U1)VDF_SUBDIGSPD_NON  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 , (U1)VDF_TTCHECKEG_NO1 , (U1)FALSE , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL , (U1)VDF_PRESSUNIT_KPA },      /* UAE               */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)UNIT_VAL_FUECO_LP100KM , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     , (U1)VDF_UNIT_TYPE_EU  , (U1)TIMEFMT_VAL_12H , (U1)VDF_4WDSYS_4WD , (U1)VDF_CALDSPTYP_DDMMYYYY , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_TEMP_MDLEST , (U1)VDF_FUGAUGE_EF , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)VDF_BZ_SBW_WITH , (U1)FALSE , (U1)TRUE   , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0603 , (U1)VDF_SUBDIGSPD_NON  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 , (U1)VDF_TTCHECKEG_NO1 , (U1)FALSE , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL , (U1)VDF_PRESSUNIT_KPA },      /* Saudi Arabia      */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)UNIT_VAL_FUECO_LP100KM , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     , (U1)VDF_UNIT_TYPE_EU  , (U1)TIMEFMT_VAL_12H , (U1)VDF_4WDSYS_4WD , (U1)VDF_CALDSPTYP_DDMMYYYY , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_TEMP_MDLEST , (U1)VDF_FUGAUGE_EF , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)VDF_BZ_SBW_WITH , (U1)FALSE , (U1)TRUE   , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0603 , (U1)VDF_SUBDIGSPD_NON  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 , (U1)VDF_TTCHECKEG_NO1 , (U1)FALSE , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL , (U1)VDF_PRESSUNIT_KPA },      /* Oman              */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)UNIT_VAL_FUECO_LP100KM , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     , (U1)VDF_UNIT_TYPE_EU  , (U1)TIMEFMT_VAL_12H , (U1)VDF_4WDSYS_4WD , (U1)VDF_CALDSPTYP_YYYYMMDD , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_TEMP_NML    , (U1)VDF_FUGAUGE_EF , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)VDF_BZ_SBW_WITH , (U1)FALSE , (U1)FALSE  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0605 , (U1)VDF_SUBDIGSPD_NON  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 , (U1)VDF_TTCHECKEG_NO1 , (U1)FALSE , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL , (U1)VDF_PRESSUNIT_KPA },      /* Hong Kong         */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)UNIT_VAL_FUECO_LP100KM , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     , (U1)VDF_UNIT_TYPE_EU  , (U1)TIMEFMT_VAL_12H , (U1)VDF_4WDSYS_4WD , (U1)VDF_CALDSPTYP_YYYYMMDD , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_TEMP_NML    , (U1)VDF_FUGAUGE_EF , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)VDF_BZ_SBW_WITH , (U1)FALSE , (U1)FALSE  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0605 , (U1)VDF_SUBDIGSPD_NON  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 , (U1)VDF_TTCHECKEG_NO1 , (U1)FALSE , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL , (U1)VDF_PRESSUNIT_KPA },      /* Macau             */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)UNIT_VAL_FUECO_LP100KM , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     , (U1)VDF_UNIT_TYPE_EU  , (U1)TIMEFMT_VAL_12H , (U1)VDF_4WDSYS_AWD , (U1)VDF_CALDSPTYP_DDMMYYYY , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_TEMP_NML    , (U1)VDF_FUGAUGE_EF , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)VDF_BZ_SBW_WITH , (U1)FALSE , (U1)FALSE  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0605 , (U1)VDF_SUBDIGSPD_NON  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 , (U1)VDF_TTCHECKEG_NO1 , (U1)FALSE , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL , (U1)VDF_PRESSUNIT_KPA },      /* Australia         */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)UNIT_VAL_FUECO_LP100KM , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     , (U1)VDF_UNIT_TYPE_EU  , (U1)TIMEFMT_VAL_12H , (U1)VDF_4WDSYS_AWD , (U1)VDF_CALDSPTYP_DDMMYYYY , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_TEMP_NML    , (U1)VDF_FUGAUGE_EF , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)VDF_BZ_SBW_WITH , (U1)FALSE , (U1)FALSE  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0605 , (U1)VDF_SUBDIGSPD_NON  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 , (U1)VDF_TTCHECKEG_NO1 , (U1)FALSE , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL , (U1)VDF_PRESSUNIT_KPA },      /* Papua New Guinea  */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)UNIT_VAL_FUECO_LP100KM , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     , (U1)VDF_UNIT_TYPE_EU  , (U1)TIMEFMT_VAL_12H , (U1)VDF_4WDSYS_AWD , (U1)VDF_CALDSPTYP_DDMMYYYY , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_TEMP_NML    , (U1)VDF_FUGAUGE_EF , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)VDF_BZ_SBW_WITH , (U1)FALSE , (U1)FALSE  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0605 , (U1)VDF_SUBDIGSPD_NON  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 , (U1)VDF_TTCHECKEG_NO1 , (U1)FALSE , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL , (U1)VDF_PRESSUNIT_KPA },      /* New Zealand       */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)UNIT_VAL_FUECO_LP100KM , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     , (U1)VDF_UNIT_TYPE_EU  , (U1)TIMEFMT_VAL_12H , (U1)VDF_4WDSYS_AWD , (U1)VDF_CALDSPTYP_DDMMYYYY , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_TEMP_NML    , (U1)VDF_FUGAUGE_EF , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)VDF_BZ_SBW_WITH , (U1)FALSE , (U1)FALSE  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0605 , (U1)VDF_SUBDIGSPD_NON  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 , (U1)VDF_TTCHECKEG_NO1 , (U1)FALSE , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL , (U1)VDF_PRESSUNIT_KPA },      /* Solomon Islands   */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)UNIT_VAL_FUECO_LP100KM , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     , (U1)VDF_UNIT_TYPE_EU  , (U1)TIMEFMT_VAL_12H , (U1)VDF_4WDSYS_4WD , (U1)VDF_CALDSPTYP_YYYYMMDD , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_TEMP_NML    , (U1)VDF_FUGAUGE_EF , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)VDF_BZ_SBW_WITH , (U1)FALSE , (U1)FALSE  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0605 , (U1)VDF_SUBDIGSPD_NON  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 , (U1)VDF_TTCHECKEG_NO1 , (U1)FALSE , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL , (U1)VDF_PRESSUNIT_KPA },      /* Taiwan            */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)UNIT_VAL_FUECO_LP100KM , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     , (U1)VDF_UNIT_TYPE_EU  , (U1)TIMEFMT_VAL_12H , (U1)VDF_4WDSYS_4WD , (U1)VDF_CALDSPTYP_YYYYMMDD , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_TEMP_NML    , (U1)VDF_FUGAUGE_EF , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)VDF_BZ_SBW_WITH , (U1)FALSE , (U1)FALSE  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0605 , (U1)VDF_SUBDIGSPD_NON  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 , (U1)VDF_TTCHECKEG_NO1 , (U1)FALSE , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL , (U1)VDF_PRESSUNIT_KPA },      /* Singapore         */
      { (U1)UNIT_VAL_SPEED_MPH  , (U1)UNIT_VAL_DIST_MILE , (U1)UNIT_VAL_FUECO_MPG_USA , (U1)UNIT_VAL_ELECO_MILEPKWH  , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM | (U1)VDF_UNIT_FUECO_BIT_MPG_USA | (U1)VDF_UNIT_FUECO_BIT_MPG_UKIMP , (U1)VDF_UNIT_TYPE_NA  , (U1)TIMEFMT_VAL_12H , (U1)VDF_4WDSYS_AWD , (U1)VDF_CALDSPTYP_YYYYMMDD , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_TEMP_NML    , (U1)VDF_FUGAUGE_EF , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)VDF_BZ_SBW_WITH , (U1)FALSE , (U1)FALSE  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0606 , (U1)VDF_SUBDIGSPD_MPH  , (U1)VDF_SPDTLRNC_USA_CAN , (U1)FALSE , (U1)VDF_TTBRAKE_NO4 , (U1)VDF_TTABS_NO6 , (U1)VDF_TTEPBPKB_NO10 , (U1)VDF_TTTAILHEAD_NO12 , (U1)VDF_TTCHECKEG_NO2 , (U1)FALSE , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL , (U1)VDF_PRESSUNIT_KPA },      /* Rep of Korea_FMVSS*/
      { (U1)UNIT_VAL_SPEED_MPH  , (U1)UNIT_VAL_DIST_MILE , (U1)UNIT_VAL_FUECO_MPG_USA , (U1)UNIT_VAL_ELECO_MILEPKWH  , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM | (U1)VDF_UNIT_FUECO_BIT_MPG_USA | (U1)VDF_UNIT_FUECO_BIT_MPG_UKIMP , (U1)VDF_UNIT_TYPE_NA  , (U1)TIMEFMT_VAL_12H , (U1)VDF_4WDSYS_AWD , (U1)VDF_CALDSPTYP_DDMMYYYY , (U1)VDF_SMASTAMID_NA    , (U1)VDF_TEMP_NML    , (U1)VDF_FUGAUGE_EF , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO155 , (U1)VDF_TT_VSCEXPERT1 , (U1)VDF_BZ_SBW_WITH , (U1)FALSE , (U1)FALSE  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0604 , (U1)VDF_SUBDIGSPD_BOTH , (U1)VDF_SPDTLRNC_USA_CAN , (U1)FALSE , (U1)VDF_TTBRAKE_NO4 , (U1)VDF_TTABS_NO6 , (U1)VDF_TTEPBPKB_NO10 , (U1)VDF_TTTAILHEAD_NO12 , (U1)VDF_TTCHECKEG_NO2 , (U1)FALSE , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL , (U1)VDF_PRESSUNIT_PSI }       /* Mexico_FMVSS      */
};

static const U1    u1_sp2_VDF_DST_DESTBDBSUP[VDF_DST_NUM_DEST_BDB][VDF_DEST_DBF_NBYTE] = {
     /* DEFUNIT_SPD               DEFUNIT_DST              DEFUNIT_FUECO                DEFUNIT_ELECO                  UNITSLCT_FUECO                                                                                                                     UNITSLCT_DEST           TIMEFMT               4WDSYS               CALDSPTYP                    SMASTAMID                 TEMPCHR               FUGAUGE              ENGUNT                EUSPDSCALE               TTTRCOFF                 TTVSCEXP                BZ_SBW_SUP            ECOJUDGE    MDLEST_WRN   BZ_REV_DST           SEATBLT_CONST               SUBDIGSPD                SPDTLRNC                   CHN_REQ     TTBRAKE               TTABS               TTEPBPKB                TTTAILHEAD                TTCHECKEG               TMNT        STPIND     UNIT_AMBTMP               PRESSUNIT                    */
      { (U1)UNIT_VAL_SPEED_MPH  , (U1)UNIT_VAL_DIST_MILE , (U1)UNIT_VAL_FUECO_MPG_USA , (U1)UNIT_VAL_ELECO_MILEPKWH  , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM | (U1)VDF_UNIT_FUECO_BIT_MPG_USA | (U1)VDF_UNIT_FUECO_BIT_MPG_UKIMP , (U1)VDF_UNIT_TYPE_NA  , (U1)TIMEFMT_VAL_12H , (U1)VDF_4WDSYS_AWD , (U1)VDF_CALDSPTYP_MMDDYYYY , (U1)VDF_SMASTAMID_NA    , (U1)VDF_TEMP_NML    , (U1)VDF_FUGAUGE_EF , (U1)VDF_ENGUNT_RPM  , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO155 , (U1)VDF_TT_VSCEXPERT1 , (U1)VDF_BZ_SBW_WITH , (U1)TRUE  , (U1)FALSE  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0603 , (U1)VDF_SUBDIGSPD_MPH  , (U1)VDF_SPDTLRNC_USA_CAN , (U1)FALSE , (U1)VDF_TTBRAKE_NO4 , (U1)VDF_TTABS_NO6 , (U1)VDF_TTEPBPKB_NO10 , (U1)VDF_TTTAILHEAD_NO12 , (U1)VDF_TTCHECKEG_NO2 , (U1)TRUE  , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_FAH , (U1)VDF_PRESSUNIT_PSI },      /* America           */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)UNIT_VAL_FUECO_LP100KM , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM | (U1)VDF_UNIT_FUECO_BIT_MPG_UK                                     , (U1)VDF_UNIT_TYPE_UK  , (U1)TIMEFMT_VAL_12H , (U1)VDF_4WDSYS_AWD , (U1)VDF_CALDSPTYP_DDMMYYYY , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_TEMP_NML    , (U1)VDF_FUGAUGE_1R , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_EU  , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)VDF_BZ_SBW_WITH , (U1)FALSE , (U1)FALSE  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0605 , (U1)VDF_SUBDIGSPD_KMPH , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 , (U1)VDF_TTCHECKEG_NO1 , (U1)FALSE , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL , (U1)VDF_PRESSUNIT_BAR },      /* Turkey            */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)UNIT_VAL_FUECO_LP100KM , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     , (U1)VDF_UNIT_TYPE_EU  , (U1)TIMEFMT_VAL_12H , (U1)VDF_4WDSYS_AWD , (U1)VDF_CALDSPTYP_YYYYMMDD , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_TEMP_NML    , (U1)VDF_FUGAUGE_EF , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)VDF_BZ_SBW_WITH , (U1)FALSE , (U1)FALSE  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0607 , (U1)VDF_SUBDIGSPD_NON  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)TRUE  , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 , (U1)VDF_TTCHECKEG_NO1 , (U1)FALSE , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL , (U1)VDF_PRESSUNIT_KPA },      /* China             */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)UNIT_VAL_FUECO_LP100KM , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     , (U1)VDF_UNIT_TYPE_EU  , (U1)TIMEFMT_VAL_12H , (U1)VDF_4WDSYS_AWD , (U1)VDF_CALDSPTYP_DDMMYYYY , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_TEMP_NML    , (U1)VDF_FUGAUGE_EF , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)VDF_BZ_SBW_WITH , (U1)FALSE , (U1)FALSE  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0605 , (U1)VDF_SUBDIGSPD_NON  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 , (U1)VDF_TTCHECKEG_NO1 , (U1)FALSE , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL , (U1)VDF_PRESSUNIT_KPA },      /* South Africa      */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)UNIT_VAL_FUECO_LP100KM , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     , (U1)VDF_UNIT_TYPE_EU  , (U1)TIMEFMT_VAL_12H , (U1)VDF_4WDSYS_AWD , (U1)VDF_CALDSPTYP_DDMMYYYY , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_TEMP_NML    , (U1)VDF_FUGAUGE_EF , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)VDF_BZ_SBW_WITH , (U1)FALSE , (U1)FALSE  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0605 , (U1)VDF_SUBDIGSPD_NON  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 , (U1)VDF_TTCHECKEG_NO1 , (U1)FALSE , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL , (U1)VDF_PRESSUNIT_KPA },      /* Australia         */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)UNIT_VAL_FUECO_LP100KM , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     , (U1)VDF_UNIT_TYPE_EU  , (U1)TIMEFMT_VAL_12H , (U1)VDF_4WDSYS_4WD , (U1)VDF_CALDSPTYP_DDMMYYYY , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_TEMP_MDLEST , (U1)VDF_FUGAUGE_EF , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)VDF_BZ_SBW_WITH , (U1)FALSE , (U1)TRUE   , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0603 , (U1)VDF_SUBDIGSPD_NON  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 , (U1)VDF_TTCHECKEG_NO1 , (U1)FALSE , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL , (U1)VDF_PRESSUNIT_KPA },      /* MDE               */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)UNIT_VAL_FUECO_LP100KM , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM | (U1)VDF_UNIT_FUECO_BIT_MPG_UK                                     , (U1)VDF_UNIT_TYPE_UK  , (U1)TIMEFMT_VAL_12H , (U1)VDF_4WDSYS_AWD , (U1)VDF_CALDSPTYP_DDMMYYYY , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_TEMP_NML    , (U1)VDF_FUGAUGE_1R , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_EU  , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)VDF_BZ_SBW_WITH , (U1)FALSE , (U1)FALSE  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0605 , (U1)VDF_SUBDIGSPD_KMPH , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 , (U1)VDF_TTCHECKEG_NO1 , (U1)FALSE , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL , (U1)VDF_PRESSUNIT_BAR },      /* Europe            */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)UNIT_VAL_FUECO_LP100KM , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM | (U1)VDF_UNIT_FUECO_BIT_MPG_UK                                     , (U1)VDF_UNIT_TYPE_UK  , (U1)TIMEFMT_VAL_12H , (U1)VDF_4WDSYS_AWD , (U1)VDF_CALDSPTYP_DDMMYYYY , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_TEMP_NML    , (U1)VDF_FUGAUGE_1R , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_EU  , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)VDF_BZ_SBW_WITH , (U1)FALSE , (U1)FALSE  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0605 , (U1)VDF_SUBDIGSPD_KMPH , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 , (U1)VDF_TTCHECKEG_NO1 , (U1)FALSE , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL , (U1)VDF_PRESSUNIT_BAR },      /* Russia            */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)UNIT_VAL_FUECO_LP100KM , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     , (U1)VDF_UNIT_TYPE_EU  , (U1)TIMEFMT_VAL_12H , (U1)VDF_4WDSYS_AWD , (U1)VDF_CALDSPTYP_DDMMYYYY , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_TEMP_NML    , (U1)VDF_FUGAUGE_EF , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)VDF_BZ_SBW_WITH , (U1)FALSE , (U1)FALSE  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0605 , (U1)VDF_SUBDIGSPD_NON  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 , (U1)VDF_TTCHECKEG_NO1 , (U1)FALSE , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL , (U1)VDF_PRESSUNIT_KPA },      /* New Zealand       */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)UNIT_VAL_FUECO_KMPL    , (U1)UNIT_VAL_ELECO_KMPKWH    , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     , (U1)VDF_UNIT_TYPE_JPN , (U1)TIMEFMT_VAL_12H , (U1)VDF_4WDSYS_4WD , (U1)VDF_CALDSPTYP_YYYYMMDD , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_TEMP_NML    , (U1)VDF_FUGAUGE_EF , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)VDF_BZ_SBW_NON  , (U1)FALSE , (U1)FALSE  , (U1)VDF_BZ_REV_JPN , (U1)VDF_SEATBLT_MCUID0605 , (U1)VDF_SUBDIGSPD_NON  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 , (U1)VDF_TTCHECKEG_NO1 , (U1)FALSE , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL , (U1)VDF_PRESSUNIT_KPA },      /* Japan             */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)UNIT_VAL_FUECO_LP100KM , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     , (U1)VDF_UNIT_TYPE_EU  , (U1)TIMEFMT_VAL_12H , (U1)VDF_4WDSYS_4WD , (U1)VDF_CALDSPTYP_DDMMYYYY , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_TEMP_NML    , (U1)VDF_FUGAUGE_EF , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)VDF_BZ_SBW_WITH , (U1)FALSE , (U1)FALSE  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0605 , (U1)VDF_SUBDIGSPD_NON  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 , (U1)VDF_TTCHECKEG_NO1 , (U1)FALSE , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL , (U1)VDF_PRESSUNIT_KPA },      /* GNR_L             */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)UNIT_VAL_FUECO_LP100KM , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     , (U1)VDF_UNIT_TYPE_EU  , (U1)TIMEFMT_VAL_12H , (U1)VDF_4WDSYS_4WD , (U1)VDF_CALDSPTYP_DDMMYYYY , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_TEMP_NML    , (U1)VDF_FUGAUGE_EF , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)VDF_BZ_SBW_WITH , (U1)FALSE , (U1)FALSE  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0605 , (U1)VDF_SUBDIGSPD_NON  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 , (U1)VDF_TTCHECKEG_NO1 , (U1)FALSE , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL , (U1)VDF_PRESSUNIT_KPA }       /* GNR_R             */
};

static const U1    u1_sp2_VDF_LANG_DST_CCODESUP[VDF_LANG_DST_NUM_C_CODE][VDF_LANG_DEST_DBF_NBYTE] = {
     /* DEFLANG                     LANGDBTYPE                      */
      { (U1)LANG_VAL______USA_ENG , (U1)VDF_LNGDBTYPE_TYPE8  },      /* Canada            */
      { (U1)LANG_VAL_______KOREAN , (U1)VDF_LNGDBTYPE_TYPE4  },      /* Rep of Korea      */
      { (U1)LANG_VAL______USA_ENG , (U1)VDF_LNGDBTYPE_TYPE8  },      /* Mexico            */
      { (U1)LANG_VAL______BRI_ENG , (U1)VDF_LNGDBTYPE_TYPE9  },      /* South Africa      */
      { (U1)LANG_VAL______BRI_ENG , (U1)VDF_LNGDBTYPE_TYPE4  },      /* India             */
      { (U1)LANG_VAL______CHN_SMP , (U1)VDF_LNGDBTYPE_TYPE3  },      /* China             */
      { (U1)LANG_VAL_______ARABIC , (U1)VDF_LNGDBTYPE_TYPE5  },      /* Bahrain           */
      { (U1)LANG_VAL_______ARABIC , (U1)VDF_LNGDBTYPE_TYPE5  },      /* Qatar             */
      { (U1)LANG_VAL_______ARABIC , (U1)VDF_LNGDBTYPE_TYPE5  },      /* Kuwait            */
      { (U1)LANG_VAL_______ARABIC , (U1)VDF_LNGDBTYPE_TYPE5  },      /* UAE               */
      { (U1)LANG_VAL______BRI_ENG , (U1)VDF_LNGDBTYPE_TYPE5  },      /* Saudi Arabia      */
      { (U1)LANG_VAL_______ARABIC , (U1)VDF_LNGDBTYPE_TYPE5  },      /* Oman              */
      { (U1)LANG_VAL______BRI_ENG , (U1)VDF_LNGDBTYPE_TYPE2  },      /* Hong Kong         */
      { (U1)LANG_VAL______BRI_ENG , (U1)VDF_LNGDBTYPE_TYPE2  },      /* Macau             */
      { (U1)LANG_VAL_______AU_ENG , (U1)VDF_LNGDBTYPE_TYPE10 },      /* Australia         */
      { (U1)LANG_VAL______BRI_ENG , (U1)VDF_LNGDBTYPE_TYPE9  },      /* Papua New Guinea  */
      { (U1)LANG_VAL_______AU_ENG , (U1)VDF_LNGDBTYPE_TYPE10 },      /* New Zealand       */
      { (U1)LANG_VAL______BRI_ENG , (U1)VDF_LNGDBTYPE_TYPE9  },      /* Solomon Islands   */
      { (U1)LANG_VAL____TAIWANESE , (U1)VDF_LNGDBTYPE_TYPE4  },      /* Taiwan            */
      { (U1)LANG_VAL__BRA_PORTUGU , (U1)VDF_LNGDBTYPE_TYPE6  },      /* Brazil            */
      { (U1)LANG_VAL______SPANISH , (U1)VDF_LNGDBTYPE_TYPE6  },      /* Argentina         */
      { (U1)LANG_VAL______SPANISH , (U1)VDF_LNGDBTYPE_TYPE6  },      /* Bolivia           */
      { (U1)LANG_VAL______SPANISH , (U1)VDF_LNGDBTYPE_TYPE6  },      /* Colombia          */
      { (U1)LANG_VAL______SPANISH , (U1)VDF_LNGDBTYPE_TYPE6  },      /* Ecuador           */
      { (U1)LANG_VAL______SPANISH , (U1)VDF_LNGDBTYPE_TYPE6  },      /* Paraguay          */
      { (U1)LANG_VAL______SPANISH , (U1)VDF_LNGDBTYPE_TYPE6  },      /* Peru              */
      { (U1)LANG_VAL______SPANISH , (U1)VDF_LNGDBTYPE_TYPE6  },      /* Uruguay           */
      { (U1)LANG_VAL______SPANISH , (U1)VDF_LNGDBTYPE_TYPE6  },      /* Venezuela         */
      { (U1)LANG_VAL______TURKISH , (U1)VDF_LNGDBTYPE_TYPE7  },      /* Turkey            */
      { (U1)LANG_VAL______RUSSIAN , (U1)VDF_LNGDBTYPE_TYPE7  },      /* Russia            */
      { (U1)LANG_VAL______RUSSIAN , (U1)VDF_LNGDBTYPE_TYPE7  },      /* Belarus           */
      { (U1)LANG_VAL______RUSSIAN , (U1)VDF_LNGDBTYPE_TYPE7  },      /* Azerbaijan        */
      { (U1)LANG_VAL______RUSSIAN , (U1)VDF_LNGDBTYPE_TYPE7  },      /* Armenia           */
      { (U1)LANG_VAL______RUSSIAN , (U1)VDF_LNGDBTYPE_TYPE7  },      /* Uzbekistan        */
      { (U1)LANG_VAL______RUSSIAN , (U1)VDF_LNGDBTYPE_TYPE7  },      /* Kazakhstan        */
      { (U1)LANG_VAL______RUSSIAN , (U1)VDF_LNGDBTYPE_TYPE7  },      /* Kyrgyzstan        */
      { (U1)LANG_VAL______RUSSIAN , (U1)VDF_LNGDBTYPE_TYPE7  },      /* Tajikistan        */
      { (U1)LANG_VAL______BRI_ENG , (U1)VDF_LNGDBTYPE_TYPE4  },      /* Brunei            */
      { (U1)LANG_VAL______BRI_ENG , (U1)VDF_LNGDBTYPE_TYPE4  },      /* Myanmar           */
      { (U1)LANG_VAL______BRI_ENG , (U1)VDF_LNGDBTYPE_TYPE4  },      /* Cambodia          */
      { (U1)LANG_VAL______BRI_ENG , (U1)VDF_LNGDBTYPE_TYPE4  },      /* North Korea       */
      { (U1)LANG_VAL______BRI_ENG , (U1)VDF_LNGDBTYPE_TYPE4  },      /* Laos              */
      { (U1)LANG_VAL______BRI_ENG , (U1)VDF_LNGDBTYPE_TYPE4  },      /* Vietnam           */
      { (U1)LANG_VAL______BRI_ENG , (U1)VDF_LNGDBTYPE_TYPE4  },      /* Singapore         */
      { (U1)LANG_VAL______BRI_ENG , (U1)VDF_LNGDBTYPE_TYPE4  },      /* Thailand          */
      { (U1)LANG_VAL______BRI_ENG , (U1)VDF_LNGDBTYPE_TYPE4  },      /* Mongolia          */
      { (U1)LANG_VAL______BRI_ENG , (U1)VDF_LNGDBTYPE_TYPE4  },      /* Maldives          */
      { (U1)LANG_VAL______BRI_ENG , (U1)VDF_LNGDBTYPE_TYPE4  },      /* Indonesia         */
      { (U1)LANG_VAL______BRI_ENG , (U1)VDF_LNGDBTYPE_TYPE4  },      /* East Timor        */
      { (U1)LANG_VAL______BRI_ENG , (U1)VDF_LNGDBTYPE_TYPE4  },      /* Philippines       */
      { (U1)LANG_VAL______BRI_ENG , (U1)VDF_LNGDBTYPE_TYPE4  },      /* Malaysia          */
      { (U1)LANG_VAL______BRI_ENG , (U1)VDF_LNGDBTYPE_TYPE9  },      /* Vanuatu           */
      { (U1)LANG_VAL______BRI_ENG , (U1)VDF_LNGDBTYPE_TYPE9  },      /* Nauru             */
      { (U1)LANG_VAL______BRI_ENG , (U1)VDF_LNGDBTYPE_TYPE9  },      /* Fiji              */
      { (U1)LANG_VAL______BRI_ENG , (U1)VDF_LNGDBTYPE_TYPE9  },      /* Tonga             */
      { (U1)LANG_VAL______BRI_ENG , (U1)VDF_LNGDBTYPE_TYPE9  },      /* W Samoa           */
      { (U1)LANG_VAL______BRI_ENG , (U1)VDF_LNGDBTYPE_TYPE9  },      /* New Caledonia     */
      { (U1)LANG_VAL______BRI_ENG , (U1)VDF_LNGDBTYPE_TYPE9  },      /* Micronesia        */
      { (U1)LANG_VAL______BRI_ENG , (U1)VDF_LNGDBTYPE_TYPE9  },      /* Tahiti            */
      { (U1)LANG_VAL______BRI_ENG , (U1)VDF_LNGDBTYPE_TYPE9  },      /* Cook Islands      */
      { (U1)LANG_VAL______BRI_ENG , (U1)VDF_LNGDBTYPE_TYPE9  },      /* Kiribati          */
      { (U1)LANG_VAL______BRI_ENG , (U1)VDF_LNGDBTYPE_TYPE9  },      /* Norfolk           */
      { (U1)LANG_VAL______BRI_ENG , (U1)VDF_LNGDBTYPE_TYPE9  }       /* Palau             */
};

static const U1    u1_sp2_VDF_LANG_DST_DESTBDBSUP[VDF_LANG_DST_NUM_DEST_BDB][VDF_LANG_DEST_DBF_NBYTE] = {
     /* DEFLANG                     LANGDBTYPE                      */
      { (U1)LANG_VAL______USA_ENG , (U1)VDF_LNGDBTYPE_TYPE8  },      /* America           */
      { (U1)LANG_VAL______TURKISH , (U1)VDF_LNGDBTYPE_TYPE7  },      /* Turkey            */
      { (U1)LANG_VAL______CHN_SMP , (U1)VDF_LNGDBTYPE_TYPE3  },      /* China             */
      { (U1)LANG_VAL______BRI_ENG , (U1)VDF_LNGDBTYPE_TYPE9  },      /* Australia         */
      { (U1)LANG_VAL______BRI_ENG , (U1)VDF_LNGDBTYPE_TYPE5  },      /* MDE               */
      { (U1)LANG_VAL______BRI_ENG , (U1)VDF_LNGDBTYPE_TYPE7  },      /* Europe            */
      { (U1)LANG_VAL______RUSSIAN , (U1)VDF_LNGDBTYPE_TYPE7  },      /* Russia            */
      { (U1)LANG_VAL______BRI_ENG , (U1)VDF_LNGDBTYPE_TYPE9  },      /* New Zealand       */
      { (U1)LANG_VAL__________JPN , (U1)VDF_LNGDBTYPE_TYPE1  },      /* Japan             */
      { (U1)LANG_VAL______BRI_ENG , (U1)VDF_LNGDBTYPE_TYPE11 },      /* GNR_L             */
      { (U1)LANG_VAL______BRI_ENG , (U1)VDF_LNGDBTYPE_TYPE11 }       /* GNR_R             */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  U1      u1_g_VardefDestCfg(U2 * u2p_a_c_code, U1 * u1p_a_dest_bdb, U1 * u1p_a_strg_whl)                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefDestCfg(U2 * u2p_a_c_code, U1 * u1p_a_dest_bdb, U1 * u1p_a_strg_whl)
{
    static const U2 u2_s_VDF_DST_C_CODE_MSK  = (U2)0x000FU;
    static const U1 u1_s_VDF_DST_C_CODE1_BIT = (U1)8U;
    static const U1 u1_s_VDF_DST_C_CODE2_BIT = (U1)4U;
    U1  u1_t_rxcnt;
    U1  u1_t_c_code;

    u1_t_c_code = (U1)0U;
#if 0   /* BEV Rebase provisionally */
    u1_t_rxcnt = u1_g_oXCANRxEvcnt((U2)OXCAN_PDU_RX_CAN_BDB1S08);
#else   /* BEV Rebase provisionally */
    u1_t_rxcnt = (U1)OXCAN_RXD_EVC_UNK;
#endif   /* BEV Rebase provisionally */

#if 0   /* BEV Rebase provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_C_CODE1, &u1_t_c_code);
#endif   /* BEV Rebase provisionally */
    *u2p_a_c_code =  ((U2)u1_t_c_code & u2_s_VDF_DST_C_CODE_MSK) << u1_s_VDF_DST_C_CODE1_BIT;

#if 0   /* BEV Rebase provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_C_CODE2, &u1_t_c_code);
#endif   /* BEV Rebase provisionally */
    *u2p_a_c_code |= (U2)(((U2)u1_t_c_code & u2_s_VDF_DST_C_CODE_MSK) << u1_s_VDF_DST_C_CODE2_BIT);

#if 0   /* BEV Rebase provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_C_CODE3, &u1_t_c_code);
#endif   /* BEV Rebase provisionally */
    *u2p_a_c_code |= ((U2)u1_t_c_code & u2_s_VDF_DST_C_CODE_MSK);

#if 0   /* BEV Rebase provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_DEST_BDB, u1p_a_dest_bdb);
    (void)Com_ReceiveSignal(ComConf_ComSignal_STRG_WHL, u1p_a_strg_whl);
#else   /* BEV Rebase provisionally */
    (*u1p_a_dest_bdb) = (U1)0U;
    (*u1p_a_strg_whl) = (U1)0U;
#endif   /* BEV Rebase provisionally */

    return(u1_t_rxcnt);
}
/*===================================================================================================================================*/
/*  U1      u1_g_VardefDestCfgDBSup(const U1 u1_a_DBF, const U1 u1_a_C_CODE_IDX, const U1 u1_a_DEST_BDB_IDX)                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefDestCfgDBSup(const U1 u1_a_DBF, const U1 u1_a_C_CODE_IDX, const U1 u1_a_DEST_BDB_IDX)
{
    U1  u1_t_sup;

    u1_t_sup = (U1)0U;

    if(u1_a_DBF < (U1)VDF_DEST_DBF_NBYTE){
        if(u1_a_C_CODE_IDX < (U1)VDF_DST_NUM_C_CODE_REG){
            u1_t_sup = u1_sp2_VDF_DST_CCODESUP[u1_a_C_CODE_IDX][u1_a_DBF];
        }
        else{
            u1_t_sup = (U1)U1_MAX;
        }

        if(u1_t_sup == (U1)U1_MAX){
            if(u1_a_DEST_BDB_IDX < (U1)VDF_DST_NUM_DEST_BDB){
                u1_t_sup = u1_sp2_VDF_DST_DESTBDBSUP[u1_a_DEST_BDB_IDX][u1_a_DBF];
            }
            else{
                u1_t_sup = u1_sp2_VDF_DST_DESTBDBSUP[u1_g_VDF_DST_DEST_BDB_IDX_DEF][u1_a_DBF];
            }
        }
    }

    return(u1_t_sup);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VardefLangDestCfgDBSup(const U1 u1_a_DBF, const U1 u1_a_C_CODE_IDX, const U1 u1_a_DEST_BDB_IDX)                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefLangDestCfgDBSup(const U1 u1_a_DBF, const U1 u1_a_C_CODE_IDX, const U1 u1_a_DEST_BDB_IDX)
{
    U1  u1_t_sup;

    u1_t_sup = (U1)0U;

    if(u1_a_DBF < (U1)VDF_LANG_DEST_DBF_NBYTE){
        if(u1_a_C_CODE_IDX < (U1)VDF_LANG_DST_NUM_C_CODE){
            u1_t_sup = u1_sp2_VDF_LANG_DST_CCODESUP[u1_a_C_CODE_IDX][u1_a_DBF];
        }
        else{
            u1_t_sup = (U1)U1_MAX;
        }

        if(u1_t_sup == (U1)U1_MAX){
            if(u1_a_DEST_BDB_IDX < (U1)VDF_LANG_DST_NUM_DEST_BDB){
                u1_t_sup = u1_sp2_VDF_LANG_DST_DESTBDBSUP[u1_a_DEST_BDB_IDX][u1_a_DBF];
            }
            else{
                u1_t_sup = u1_sp2_VDF_LANG_DST_DESTBDBSUP[u1_g_VDF_LANG_DST_IDX_DEF][u1_a_DBF];
            }
        }
    }

    return(u1_t_sup);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VardefCfgUnitType(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefCfgUnitType(void)
{
    static const U1 u1_s_UNITTYPE_TBL[VDF_NUM_PTSYS][VDF_NUM_UNIT_TYPE_DEST] = {
        /* VDF_UNIT_TYPE_NA  , VDF_UNIT_TYPE_UK    , VDF_UNIT_TYPE_EU    , VDF_UNIT_TYPE_JPN    */
        { (U1)VDF_UNIT_TYPE_C, (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_C },    /* UNK       */
        { (U1)VDF_UNIT_TYPE_A, (U1)VDF_UNIT_TYPE_B , (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_C },    /* GAS       */
        { (U1)VDF_UNIT_TYPE_A, (U1)VDF_UNIT_TYPE_B , (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_C },    /* GAS_ISS   */
        { (U1)VDF_UNIT_TYPE_A, (U1)VDF_UNIT_TYPE_B , (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_C },    /* HYB       */
        { (U1)VDF_UNIT_TYPE_D, (U1)VDF_UNIT_TYPE_E , (U1)VDF_UNIT_TYPE_F , (U1)VDF_UNIT_TYPE_F },    /* HYB_PLU   */
        { (U1)VDF_UNIT_TYPE_H, (U1)VDF_UNIT_TYPE_H , (U1)VDF_UNIT_TYPE_G , (U1)VDF_UNIT_TYPE_G },    /* ELE_BAT   */
        { (U1)VDF_UNIT_TYPE_A, (U1)VDF_UNIT_TYPE_B , (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_C },    /* HYB_MOT   */
        { (U1)VDF_UNIT_TYPE_I, (U1)VDF_UNIT_TYPE_J , (U1)VDF_UNIT_TYPE_K , (U1)VDF_UNIT_TYPE_L },    /* ELE_HYD   */
        { (U1)VDF_UNIT_TYPE_A, (U1)VDF_UNIT_TYPE_B , (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_C },    /* 48V       */
        { (U1)VDF_UNIT_TYPE_C, (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_C },    /* UNK       */
        { (U1)VDF_UNIT_TYPE_C, (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_C },    /* UNK       */
        { (U1)VDF_UNIT_TYPE_C, (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_C },    /* UNK       */
        { (U1)VDF_UNIT_TYPE_C, (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_C },    /* UNK       */
        { (U1)VDF_UNIT_TYPE_C, (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_C },    /* UNK       */
        { (U1)VDF_UNIT_TYPE_C, (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_C },    /* UNK       */
        { (U1)VDF_UNIT_TYPE_C, (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_C }     /* UNK       */
    };

    U1 u1_t_unit_dest;
    U1 u1_t_unit_type;
    U1 u1_t_ptsys;

    u1_t_unit_type = (U1)VDF_UNIT_TYPE_C;
    u1_t_unit_dest = u1_g_VardefDestDbfByPid((U1)VDF_DEST_DBF_UNITSLCT_DEST);
    u1_t_ptsys     = u1_g_VardefPtsRx();

    if((u1_t_unit_dest < (U1)VDF_NUM_UNIT_TYPE_DEST) &&
       (u1_t_ptsys     < (U1)VDF_NUM_PTSYS)){
        u1_t_unit_type = u1_s_UNITTYPE_TBL[u1_t_ptsys][u1_t_unit_dest];
    }

    return(u1_t_unit_type);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VardefCfgBltDst(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefCfgBltDst(void)
{
    static const U1    u1_s_BLTDST_TBL[CALIB_MCUID0604_TO_MCUID0607_NUM] = {
        (U1)VDF_SEATBLT_DEST_USA,          /* CALIB_MCUID0604_TO_MCUID0607_USA         (0) */
        (U1)VDF_SEATBLT_DEST_EU,           /* CALIB_MCUID0604_TO_MCUID0607_AUS         (1) */
        (U1)VDF_SEATBLT_DEST_CHN           /* CALIB_MCUID0604_TO_MCUID0607_CHN         (2) */
    };

    U1 u1_t_blt_const;
    U1 u1_t_blt_dst;
    U1 u1_t_blt_calib;

    u1_t_blt_dst   = (U1)VDF_SEATBLT_DEST_USA;
    u1_t_blt_const = u1_g_VardefDestDbfByPid((U1)VDF_DEST_DBF_SEATBLT_CONST);

	switch(u1_t_blt_const){
        case (U1)VDF_SEATBLT_MCUID0603:
#if 0   /* BEV Rebase provisionally */
            u1_t_blt_calib = u1_s_VardefDestCfgCalibU1NumChk(u1_CALIB_MCUID0603_SBELT_USA, (U1)CALIB_MCUID0604_TO_MCUID0607_NUM,
                                                             (U1)CALIB_MCUID0603_DEF);
#else   /* BEV Rebase provisionally */
            u1_t_blt_calib = (U1)0U;
#endif   /* BEV Rebase provisionally */
            break;
        case (U1)VDF_SEATBLT_MCUID0604:
            u1_t_blt_calib = u1_s_VardefDestCfgCalibU1NumChk(u1_CALIB_MCUID0604_SBELT_MEXICO, (U1)CALIB_MCUID0604_TO_MCUID0607_NUM,
                                                             (U1)CALIB_MCUID0604_DEF);
            break;
        case (U1)VDF_SEATBLT_MCUID0605:
            u1_t_blt_calib = u1_s_VardefDestCfgCalibU1NumChk(u1_CALIB_MCUID0605_SBELT_EU, (U1)CALIB_MCUID0604_TO_MCUID0607_NUM,
                                                             (U1)CALIB_MCUID0605_DEF);
            break;
        case (U1)VDF_SEATBLT_MCUID0606:
            u1_t_blt_calib = u1_s_VardefDestCfgCalibU1NumChk(u1_CALIB_MCUID0606_SBELT_KOREA, (U1)CALIB_MCUID0604_TO_MCUID0607_NUM,
                                                             (U1)CALIB_MCUID0606_DEF);
            break;
        case (U1)VDF_SEATBLT_MCUID0607:
            u1_t_blt_calib = u1_s_VardefDestCfgCalibU1NumChk(u1_CALIB_MCUID0607_SBELT_CHINA, (U1)CALIB_MCUID0604_TO_MCUID0607_NUM,
                                                             (U1)CALIB_MCUID0607_DEF);
            break;
        default:
            u1_t_blt_calib = u1_s_VardefDestCfgCalibU1NumChk(u1_CALIB_MCUID0605_SBELT_EU, (U1)CALIB_MCUID0604_TO_MCUID0607_NUM,
                                                             (U1)CALIB_MCUID0605_DEF);
            break;
    }

    u1_t_blt_dst = u1_s_BLTDST_TBL[u1_t_blt_calib];

    return(u1_t_blt_dst);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VardefCfg4wdSys(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefCfg4wdSys(void)
{
    U1 u1_t_brand;
    U1 u1_t_4wdsys;

    u1_t_brand   = u1_s_VardefDestCfgCalibU1NumChk(u1_CALIB_MCUID0024_BRAND, (U1)CALIB_MCUID0024_NUM, (U1)CALIB_MCUID0024_DEF);
    u1_t_4wdsys  = u1_g_VardefDestDbfByPid((U1)VDF_DEST_DBF_4WDSYS);

    if((u1_t_brand == (U1)CALIB_MCUID0024_LEXUS)  ||
       (u1_t_brand == (U1)CALIB_MCUID0024_SUBARU)){
        u1_t_4wdsys = (U1)VDF_4WDSYS_AWD;
    }

    return(u1_t_4wdsys);
}

/*===================================================================================================================================*/
/*  static inline U1    u1_s_VardefDestCfgCalibU1NumChk(const U1 u1_a_CALIBID, const U1 u1_a_NUM, const U1 u1_a_DEF)                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      const U1 u1_a_CALIBID                                                                                            */
/*                  const U1 u1_a_NUM                                                                                                */
/*                  const U1 u1_a_DEF                                                                                                */
/*  Return:         U1 u1_t_ret                                                                                                      */
/*===================================================================================================================================*/
static inline U1    u1_s_VardefDestCfgCalibU1NumChk(const U1 u1_a_CALIBID, const U1 u1_a_NUM, const U1 u1_a_DEF)
{
    U1 u1_t_ret;

    u1_t_ret = u1_a_CALIBID;
    if(u1_t_ret >= u1_a_NUM){
        u1_t_ret = u1_a_DEF;
    }

    return(u1_t_ret);
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
/*  2.0.0     1/24/2024  HF       19PFv3.                                                                                            */
/*  2.1.0    10/28/2024  AA       M_DESTVARI-CSTD-A0-07 spec update                                                                  */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  032D-1    1/25/2021  SF       Change config for 032D CV                                                                          */
/*  840B-1    4/14/2021  AT       Change config for 840B CV                                                                          */
/*  893B-1    6/14/2021  RO       Change config for 893B CV                                                                          */
/*  178D-1    7/19/2021  SF       Change config for 178D CV                                                                          */
/*  300D-1    8/02/2021  RO       Change config for 300D CV                                                                          */
/*  460B-1    9/27/2021  RO       Change config for 460B CV                                                                          */
/*  893B-2   11/18/2021  RO       Change config for 893B 1A                                                                          */
/*  840B-2   12/20/2021  RO       Change config for 840B 1A                                                                          */
/*  840B-3    1/24/2022  RO       Change config for 840B MPT                                                                         */
/*  300D-2    2/14/2022  SK       Change config for 300D ECI                                                                         */
/*  175D-1    3/31/2022  HA       Change config for 175D/177D/227D 1A                                                                */
/*  178D-2    4/04/2022  RO       Change config for 178D MPT                                                                         */
/*  460B-2    4/15/2022  RO       Change config for 178D MPT                                                                         */
/*  025D182D-1 4/14/2022 SK       Change config for 025D182D 1A                                                                      */
/*  200D-1    6/08/2022  RO       Change config for 200D Certified Car                                                               */
/*  200D-2    7/01/2022  RO       Change config for 200D 970B Pre1A                                                                  */
/*  220D-1    7/14/2022  RO       Change config for 220D Pre1A                                                                       */
/*  115D117D-1 8/24/2022 RO       Change config for 115D117D 1A                                                                      */
/*  115D117D-2 8/31/2022 RO       Change config for 115D117D 1A                                                                      */
/*  200D-3    9/05/2022  RO       Change config for 200D 1A                                                                          */
/*  296D-1    9/02/2022  HA       Change config for 296D CV                                                                          */
/*  960B-1     9/13/2022 SK       Change config for 960B Pre1A                                                                       */
/*  115D117D-4 10/31/2022 RO      Change config for 115D117D MPT                                                                     */
/*  448D-1    12/05/2022 SK       Change config for 448D CV                                                                          */
/*  458D-1     2/01/2023 HA       Change config for 458D Certified Car                                                               */
/*  539D-1    2/16/2023  HA       Change config for 539D CV-R                                                                        */
/*  396D-1    2/21/2023  HA       Change config for 396D Certified Car                                                               */
/*  234D-1    3/14/2023  HA       Change config for 234D239D Certified Car                                                           */
/*  458D-2    4/18/2023  RO       Change config for 448D539D396D234D239D458D 1A                                                      */
/*  960B-2    5/08/2023  RO       Change config for 960B 1A                                                                          */
/*  234D-1    5/22/2023  RO       Change config for 234D239D458D 1A                                                                  */
/*  587D588D-1 6/01/2023 HA       Change config for 587D588D CV                                                                      */
/*  19PFv3-1  1/19/2024  HF       Change config for 19PFv3 CV                                                                        */
/*  19PFv3-2  2/23/2024  DR       Added config for TMNT                                                                              */
/*  19PFv3-3  4/12/2024  SH       Add calibration guard                                                                              */
/*  19PFv3-4  5/16/2024  SH       Add calibration guard(MCUID0603toMCUID0607)                                                        */
/*  19PFv3-5  6/06/2024  SM       Change config for 19PFv3 R1(MET-M_DESTVARI-CSTD-A0-04)                                             */
/*  19PFv3-6  7/05/2024  TN       Delete Calibration Guard Process except for out of array references.                               */
/*  19PFv3-7  7/09/2024  KH       Change config for 19PFv3 R1.2 (BSTPR -> PRESSUNIT)                 .                               */
/*  19PFv3-8  7/12/2024  TN       Add Calibration Guard to Unify Vehicle Operation.                                                  */
/*  19PFv3-9 12/03/2024  AA       Deleted Colombia control parameter              .                                                  */
/*  19PFv3-10 1/16/2025  SN       Change DEFUNIT_FUECO United Kingdom parameter             .                                        */
/*  19PFv3-11 4/10/2025  TR       Deletion of TMNT function presence judgement function             .                                */
/*                                                                                                                                   */
/*  * SF   = Seiya Fukutome, DENSO TECHNO                                                                                            */
/*  * AT   = Ayano Tomimoto, KSE                                                                                                     */
/*  * RO   = Reiya Okuda, KSE                                                                                                        */
/*  * SK   = Shotaro Kitayama, PRD                                                                                                   */
/*  * HA   = Hiroki Asano, PRD                                                                                                       */
/*  * HF   = Hinari Fukamachi, KSE                                                                                                   */
/*  * DR   = Dyan Reyes, DTPH                                                                                                        */
/*  * SH   = Sae Hirose, Denso Techno                                                                                                */
/*  * SM   = Shota Maegawa, Denso Techno                                                                                             */
/*  * TN   = Tetsushi Nakano, Denso Techno                                                                                           */
/*  * KH   = Kiko Huerte, DTPH                                                                                                       */
/*  * AA   = Anna Asuncion, DTPH                                                                                                     */
/*  * SN   = Shimon Nambu, Denso Techno                                                                                              */
/*  * TR   = Tebs Ramos, DTPH                                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
