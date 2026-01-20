/* 2.2.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Vardef / Destination                                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef VARDEF_DEST_CFG_H
#define VARDEF_DEST_CFG_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VARDEF_DEST_CFG_H_MAJOR                 (2)
#define VARDEF_DEST_CFG_H_MINOR                 (2)
#define VARDEF_DEST_CFG_H_PATCH                 (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "vardef.h"

#include "calibration.h"
/* #include "vardef_dest.h" */ /* vardef_dest.h is included in vardef_dbf.h" */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U2          u2_dest_bdb_val;
    U2          u2_dest_bdb_mask;
}ST_VDF_DST_DEST_BDB_JDGIDX;

typedef struct {
    U2          u2_t_c_code;
    U1          u1_t_c_code_idx;
}ST_VDF_DST_C_CODE;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void    vd_g_VardefDestBonInit(void);
void    vd_g_VardefDestRstwkInit(void);
void    vd_g_VardefDestMainTask(void);

U1      u1_g_VardefDestCfg(U2 * u2p_a_c_code, U1 * u1p_a_dest_bdb, U1 * u1p_a_strg_whl);
U1      u1_g_VardefDestCfgDBSup(const U1 u1_a_DBF, const U1 u1_a_C_CODE_IDX, const U1 u1_a_DEST_BDB_IDX);
U1      u1_g_VardefLangDestCfgDBSup(const U1 u1_a_DBF, const U1 u1_a_C_CODE_IDX, const U1 u1_a_DEST_BDB_IDX);
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern const U2                            u2_g_VDF_DST_C_CODE_RIM_U2;
extern const U2                            u2_g_VDF_DST_DEST_BDB_RIM_U1;
extern const U2                            u2_g_VDF_DST_STRG_WHL_RIM_U1;
extern const U2                            u2_g_VDF_DST_IDX_RIM_U1;
extern const U2                            u2_g_VDF_LANG_DST_IDX_RIM_U1;

extern const U1                            u1_g_VDF_DST_RXEV_CNT_INIT;

extern const U1                            u1_g_VDF_DST_C_CODE_IDX_DEF;
extern const U1                            u1_g_VDF_DST_DEST_BDB_IDX_DEF;
extern const U1                            u1_g_VDF_LANG_DST_IDX_DEF;
extern const U1                            u1_g_VDF_DST_IDX_DEF;

extern const U1                            u1_g_VDF_DST_HDSIDE_DEF;

extern const U1                            u1_g_VDF_DST_NUM_C_CODE;
extern const U1                            u1_g_VDF_DST_NUM_DEST_BDB;
extern const ST_VDF_DST_C_CODE             st_gp_VDF_DST_C_CODE[];
extern const ST_VDF_DST_DEST_BDB_JDGIDX    st_gp_VDF_DST_DEST_BDB_JDGIDX[];
extern const U1                            u1_g_VDF_LANG_DST_NUM_C_CODE;
extern const U1                            u1_g_VDF_LANG_DST_NUM_DEST_BDB;
extern const U2                            u2_gp_VDF_LANG_DST_C_CODE[];
extern const ST_VDF_DST_DEST_BDB_JDGIDX    st_gp_VDF_LANG_DST_DEST_BDB_JDGIDX[];

extern const U1                            u1_g_VDF_DST_NUM_C_CODE_REG;
extern const U1                            u1_g_VDF_DST_C_CODE_KOR;
extern const U1                            u1_g_VDF_DST_C_CODE_MEX;
extern const U1                            u1_g_VDF_DST_C_CODE_KOR_FMVSS;
extern const U1                            u1_g_VDF_DST_C_CODE_MEX_FMVSS;

#endif /* VARDEF_DEST_CFG_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  vardef_dest.c                                                                                                 */
/*                                                                                                                                   */
/*===================================================================================================================================*/
