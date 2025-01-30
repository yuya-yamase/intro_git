/* 1.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Mmcstmz : mmlang                                                                                                                 */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef MMLANG_CFG_H
#define MMLANG_CFG_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define MMLANG_CFG_H_MAJOR                       (1)
#define MMLANG_CFG_H_MINOR                       (1)
#define MMLANG_CFG_H_PATCH                       (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "nvmc_mgr.h"
#include "rim_ctl.h"
#include "vardef.h"
#include "locale.h"
#include "mmlang.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define MMLANG_MAIN_TICK               (20U)

#define MMLANG_A_LANG_NUM              (64U)
#define MMLANG_LANG_NUM_VAL            (LANG_NUM_VAL)

#define MMLANG_LNGDB_NUM               (7U)                                                   /* M_LNGDB*,A_LNGDB*                   */
#define MMLANG_LNGDB_1                 (0U)                                                   /* M_LNGDB1,A_LNGDB1                   */
#define MMLANG_LNGDB_2                 (1U)                                                   /* M_LNGDB2,A_LNGDB2                   */
#define MMLANG_LNGDB_3                 (2U)                                                   /* M_LNGDB3,A_LNGDB3                   */
#define MMLANG_LNGDB_4                 (3U)                                                   /* M_LNGDB4,A_LNGDB4                   */
#define MMLANG_LNGDB_5                 (4U)                                                   /* M_LNGDB5,A_LNGDB5                   */
#define MMLANG_LNGDB_6                 (5U)                                                   /* M_LNGDB6,A_LNGDB6                   */
#define MMLANG_LNGDB_7                 (6U)                                                   /* M_LNGDB7,A_LNGDB7                   */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_g_MmlangCfgAccchk(void);
U1      u1_g_MmlangCfgEsichk(void);

U1      u1_g_MmlangCfgPts(void);

U1      u1_g_MmlangCfgLangDBType(void);

U1      u1_g_MmlangCfgMsgsts(void);

U1      u1_g_MmlangCfgGetA_LNGCHG(void);
U1      u1_g_MmlangCfgGetA_LNG_ST(void);
U1      u1_g_MmlangCfgGetA_LANG(void);
U1      u1_g_MmlangCfgGetA_LNGDB1(void);
U1      u1_g_MmlangCfgGetA_LNGDB2(void);
U1      u1_g_MmlangCfgGetA_LNGDB3(void);
U1      u1_g_MmlangCfgGetA_LNGDB4(void);
U1      u1_g_MmlangCfgGetA_LNGDB5(void);
U1      u1_g_MmlangCfgGetA_LNGDB6(void);
U1      u1_g_MmlangCfgGetA_LNGDB7(void);

void    vd_g_MmlangCfgTxM_LNG_ST(const U1 u1_a_SIG);
void    vd_g_MmlangCfgTxM_LANG(const U1 u1_a_SIG);
void    vd_g_MmlangCfgTxM_LNGDB1(const U1 u1_a_SIG);
void    vd_g_MmlangCfgTxM_LNGDB2(const U1 u1_a_SIG);
void    vd_g_MmlangCfgTxM_LNGDB3(const U1 u1_a_SIG);
void    vd_g_MmlangCfgTxM_LNGDB4(const U1 u1_a_SIG);
void    vd_g_MmlangCfgTxM_LNGDB5(const U1 u1_a_SIG);
void    vd_g_MmlangCfgTxM_LNGDB6(const U1 u1_a_SIG);
void    vd_g_MmlangCfgTxM_LNGDB7(const U1 u1_a_SIG);

void    vd_g_MmlangCfgMLangEvtTx(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern const U2                u2_g_MMLANG_A_LNG_ST_RIM_U1;
extern const U2                u2_g_MMLANG_A_LANG_RIM_U1;
extern const U2                u2_g_MMLANG_M_LANG_RIM_U1;
extern const U2                u2_g_MMLANG_M_LANG_OLD_RIM_U1;
extern const U2                u2_gp_MMLANG_RIMID_A_LNGDB[MMLANG_LNGDB_NUM];
extern const U2                u2_gp_MMLANG_RIMID_M_LNGDB[MMLANG_LNGDB_NUM];

extern const U2                u2_g_MMLANG_FONT_RIM_U1;

extern const U2                u2_g_MMLANG_M_LNG_ST_NVMC_U1;

extern const U1                u1_g_MMLANG_LNGDB_TYPENUM;
extern const U1                u1_g_MMLANG_LNGDB_TYPEDEF;

extern const U1                u1_gp_MMLANG_LNGDB_TBL[][MMLANG_LNGDB_NUM];

extern const U1                u1_gp_MMLANG_FONT_TBL[MMLANG_A_LANG_NUM];

#endif /* #ifndef MMLANG_CFG_H */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  mmlang.c                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/
