/* 1.0.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Diagnosis on Can for MET/HUD based on AUBIST/DEM, DCM                                                                            */
/*  SID 0x22/0x2E/0x2F/0x31 DataIdentifer and Routine Identifer                                                                      */
/*===================================================================================================================================*/

#ifndef OXDOCAN_XID_CFG_H
#define OXDOCAN_XID_CFG_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDOCAN_XID_CFG_H_MAJOR                  (1U)
#define OXDOCAN_XID_CFG_H_MINOR                  (0U)
#define OXDOCAN_XID_CFG_H_PATCH                  (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
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
    U1   ( * const          fp_u1_SUP)(void);                                              /* Return : OXDC_XID_SUP_XXX          */
    U2                      u2_xid;
    U2                      u2_rd_ses;                                                     /* Read  Session                      */
    U1   ( * const          fp_u1_RDSEC_CHK)(const U1 u1_a_LVL);                           /* Return : OXDC_SAL_PROC_XXX         */
    U2                      u2_wr_ses;                                                     /* Write Session                      */
    U1   ( * const          fp_u1_WRSEC_CHK)(const U1 u1_a_LVL);                           /* Return : OXDC_SAL_PROC_XXX         */
}ST_OXDC_DID;

typedef struct{
    U1   ( * const          fp_u1_SUP)(void);                                              /* Return : OXDC_XID_SUP_XXX          */
    U2                      u2_xid;
    U2                      u2_ses;
    U1   ( * const          fp_u1_SEC_CHK)(const U1 u1_a_LVL);                             /* Return : OXDC_SAL_PROC_XXX         */
}ST_OXDC_XID;

typedef struct{
    U2                      u2_req_nbyte;
    U2                      u2_ans_nbyte;
}ST_OXDC_XID_ML;   /* Message Length */

typedef struct{
    U2                      u2_sta_idx;
    U2                      u2_end_idx;
}ST_OXDC_XID_XGR;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U1   ( * const          fp_u1_CSM_CHK)(const U1 u1_a_PRM, const U1 * u1_ap_CSM);       /* Return : OXDC_SAL_PROC_RUN or Not  */
    void ( * const          fp_vd_ACT)(void);
    void ( * const          fp_vd_DEACT)(void);
    U1   ( * const          fp_u1_SEC_CHK)(const U1 u1_a_LVL);                             /* Return : OXDC_SAL_PROC_XXX         */
}ST_OXDC_IOC_IF;

typedef struct{
    U1   ( * const          fp_u1_READ)(U1 * u1_ap_ans, const U2 u2_a_ELPSD);              /* Return : OXDC_SAL_PROC_XXX         */
    U1   ( * const          fp_u1_WRITE)(const U1 * u1_ap_REQ, const U2 u2_a_ELPSD);       /* Return : OXDC_SAL_PROC_XXX         */
    const ST_OXDC_IOC_IF *  stp_IOC;
}ST_OXDC_DATA_IF;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U1   ( * const          fp_u1_COR_CHK)(const U1 u1_a_SUBF, const U1 * u1_ap_COR);      /* Return : OXDC_SAL_PROC_RUN or Not  */
    U1   ( * const          fp_u1_START)(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte);    /* Return : OXDC_SAL_PROC_XXX    */
    U1   ( * const          fp_u1_STOP)(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte);     /* Return : OXDC_SAL_PROC_XXX    */
    U1   ( * const          fp_u1_RESULT)(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte);   /* Return : OXDC_SAL_PROC_XXX    */
}ST_OXDC_ROUT_IF;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern U2                   u2_gp_oxdc_rebyid_xidlist[OXDC_REBYID_NUMOFDID_MAX];
extern U1                   u1_g_oxdc_rebyid_xidcnt;

extern U2                   u2_g_oxdc_rout_xid;

#if(OXDC_SID2F_USE == OXDC_USE)
extern U2                   u2_g_oxdc_ioc_xid;
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U2      u2_g_oXDoCANXidSearchDid(const U2 u2_a_DID, const ST_OXDC_DID st_ap_CFG[], const U2 u2_a_NUM_CFG);
U2      u2_g_oXDoCANXidSearchRid(const U2 u2_a_RID, const ST_OXDC_XID st_ap_CFG[], const U2 u2_a_NUM_CFG);

void    vd_g_oXDoCANXidSupInit(const U2 u2_a_LP_BEGIN, U1 * u1_ap_sup);
void    vd_g_oXDoCANDidSupInit(const U2 u2_a_LP_BEGIN, U1 * u1_ap_sup);
void    vd_g_oXDoCANRidSupInit(const U2 u2_a_LP_BEGIN, U1 * u1_ap_sup);
U1      u1_g_oXDoCANXidSupchk(const ST_OXDC_DID * st_ap_DID, const U2 u2_a_NUM_DID, U1 * u1_ap_sup);
U1      u1_g_oXDoCANRidSupchk(const ST_OXDC_XID * st_ap_RID, const U2 u2_a_NUM_RID, U1 * u1_ap_sup);
U1      u1_g_oXDoCANXgrSupchk(const ST_OXDC_DID * st_ap_DID, const U2 u2_a_NUM_XID, U1 * u1_ap_sup);
U1      u1_g_oXDoCANRgrSupchk(const ST_OXDC_XID * st_ap_RID, const U2 u2_a_NUM_XID, U1 * u1_ap_sup);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern const U2                        u2_g_OXDC_XID_SUP_LP_LMT;
extern const U2                        u2_g_OXDC_IOC_RDBK_DLY_MAX;

extern const ST_OXDC_IOC_IF            st_gp_OXDC_IOC_IF[];
extern const U2                        u2_g_OXDC_NUM_IOC;

extern const ST_OXDC_DID               st_gp_OXDC_DATA_XID[];
extern const ST_OXDC_XID_ML            st_gp_OXDC_DATA_XID_ML[];
extern const ST_OXDC_DATA_IF           st_gp_OXDC_DATA_CFG[];
extern const U2                        u2_g_OXDC_DATA_NUM_XID;

extern const ST_OXDC_XID               st_gp_OXDC_ROUT_XID[];
extern const ST_OXDC_XID_ML            st_gp_OXDC_ROUT_XID_ML_SF_01[]; /* subfunction "StartRoutine"          */
extern const ST_OXDC_XID_ML            st_gp_OXDC_ROUT_XID_ML_SF_02[]; /* subfunction "StopRoutine"           */
extern const ST_OXDC_XID_ML            st_gp_OXDC_ROUT_XID_ML_SF_03[]; /* subfunction "RequestRoutineResults" */
extern const ST_OXDC_ROUT_IF           st_gp_OXDC_ROUT_CFG[];
extern const U2                        u2_g_OXDC_ROUT_NUM_XID;

#endif      /* OXDOCAN_XID_CFG_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see oxdocan_xid.c                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
