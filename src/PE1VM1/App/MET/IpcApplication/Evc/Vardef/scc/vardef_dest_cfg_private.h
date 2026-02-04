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

typedef struct{
    U2          u2_dest_bdb_val;
    U2          u2_dest_bdb_mask;
    U1          u1_t_dest_bdb_idx;
}ST_VDF_DST_LAW_DEST_BDB_JDGIDX;

typedef struct {
    U2          u2_t_c_code;
    U1          u1_t_c_code_idx;
}ST_VDF_DST_LAW_C_CODE;

typedef struct {
    volatile const U2          *u2p_t_C_CODE;
    volatile const U1          *u1p_t_C_CODE_IDX;
}ST_VDF_DST_SPEC_C_CODE;

typedef struct {
    U2          u1_t_sub_spd_cfg; /* Subspeed Configuration Table (Result after Bit Operations) */
    U1          u1_t_sub_dig_spd; /* Final Output Result */
}ST_VDF_DST_SUB_VEHSPD;

typedef struct{
    U1          u1_t_law_if_name; /* Regulation Project Inquiry Interface Name */
    U1          u1_t_law_destid;  /* Regulation Project DestID */
}ST_VDF_DST_LAW_IFID_IDX;

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
U1      u1_g_VardefDestSpecCfgDBSup(const U1 u1_a_LAW_DBF, const U1 u1_a_SPEC_C_CODE_IDX);
U1      u1_g_VardefDestLawCfgDBSup(const U1 u1_a_LAW_DBF, const U1 u1_a_SPEC_C_CODE_IDX, const U1 u1_a_LAW_C_CODE_IDX, const U1 u1_a_LAW_DEST_BDB_IDX);
U1      u1_g_VardefDestLawCfgBdbDefJdg(void);
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern const U2                                u2_g_VDF_DST_C_CODE_RIM_U2;
extern const U2                                u2_g_VDF_DST_DEST_BDB_RIM_U1;
extern const U2                                u2_g_VDF_DST_STRG_WHL_RIM_U1;
extern const U2                                u2_g_VDF_DST_IDX_RIM_U1;
extern const U2                                u2_g_VDF_DST_LAW_IDX_RIM_U1;

extern const U1                                u1_g_VDF_DST_RXEV_CNT_INIT;

extern const U1                                u1_g_VDF_DST_C_CODE_IDX_DEF;
extern const U1                                u1_g_VDF_DST_DEST_BDB_IDX_DEF;
extern const U1                                u1_g_VDF_DST_IDX_DEF;

extern const U1                                u1_g_VDF_DST_HDSIDE_DEF;

extern const U1                                u1_g_VDF_DST_NUM_C_CODE;
extern const U1                                u1_g_VDF_DST_NUM_DEST_BDB;
extern const U2                                u2_gp_VDF_DST_C_CODE[];
extern const ST_VDF_DST_DEST_BDB_JDGIDX        st_gp_VDF_DST_DEST_BDB_JDGIDX[];

extern const U1                                u1_g_VDF_DST_LAW_C_CODE_IDX_DEF;
extern const U1                                u1_g_VDF_DST_LAW_IDX_DEF;

extern const U1                                u1_g_VDF_DST_LAW_NUM_C_CODE;
extern const U1                                u1_g_VDF_DST_LAW_NUM_DEST_BDB;
extern const ST_VDF_DST_LAW_C_CODE             st_gp_VDF_DST_LAW_C_CODE[];
extern const ST_VDF_DST_LAW_DEST_BDB_JDGIDX    st_gp_VDF_DST_LAW_DEST_BDB_JDGIDX[];

extern const U1                                u1_g_VDF_DST_LAW_NUM_C_CODE_REG;
extern const U1                                u1_g_VDF_DST_LAW_C_CODE_KOR;
extern const U1                                u1_g_VDF_DST_LAW_C_CODE_MEX;
extern const U1                                u1_g_VDF_DST_LAW_KOR_FMVSS;
extern const U1                                u1_g_VDF_DST_LAW_MEX_FMVSS;

extern const ST_VDF_DST_SPEC_C_CODE            st_gp_VDF_DST_SPEC_C_CODE[];
/* sepcial contry judge */
extern const U1                                u1_g_VDF_DST_SPEC_NUM_C_CODE;
extern const U1                                u1_g_VDF_DST_LAW_SPEC_IDX_DEF;

extern const U1                                u1_g_VDF_DST_LAW_BDB_IDX_DEF_FMVSS;
extern const U1                                u1_g_VDF_DST_LAW_NUM_DEST_BDB_REG;
extern const U1                                u1_g_VDF_DST_LAW_DEST_BDB_B_GNR_L;
extern const U1                                u1_g_VDF_DST_LAW_DEST_BDB_B_GNR_R;
extern const U1                                u1_g_VDF_DST_LAW_DEST_BDB_B_GNR_FMVSS;
#endif /* VARDEF_DEST_CFG_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  vardef_dest.c                                                                                                 */
/*                                                                                                                                   */
/*===================================================================================================================================*/
