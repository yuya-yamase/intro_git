/* 2.7.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Trip Computer                                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef TRIPCOM_CFG_H
#define TRIPCOM_CFG_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TRIPCOM_CFG_H_MAJOR                     (2)
#define TRIPCOM_CFG_H_MINOR                     (7)
#define TRIPCOM_CFG_H_PATCH                     (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "fpcall_vd_fvd.h"

#include "avggrph.h"
#include "tripcom.h"
#include "tripsnsr.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TRIPCOM_NUM_APPL                        (7U)
#define TRIPCOM_APPL_AVGEE                      (0U)            /*  Average Electric Economy                                         */
#define TRIPCOM_APPL_INSTEE                     (1U)            /*  Instantaneous Electric Economy                                   */
#define TRIPCOM_APPL_EVDTE                      (2U)            /*  EV Distance To Empty                                             */
#define TRIPCOM_APPL_AVGVEHSPD                  (3U)            /*  Average Vehicle Speed                                            */
#define TRIPCOM_APPL_PTSRUNTM                   (4U)            /*  Powertrain System Run Time                                       */
#define TRIPCOM_APPL_PTSRUNDIST                 (5U)            /*  Powertrain System Run Distance                                   */
#define TRIPCOM_APPL_DTE_ED                     (6U)            /*  Distance To Empty for Electric Delay                             */

#define TRIPCOM_NUM_CNTTS                       (21U)

#define TRIPCOM_NUM_CANTXUNIT                   (3U)
#define TRIPCOM_CANTXUNIT_SPEED                 (0U)
#define TRIPCOM_CANTXUNIT_DIST                  (1U)
#define TRIPCOM_CANTXUNIT_EECON                 (2U)

#define TRIPCOM_VAR_INIT                        (0x00000000U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct {
    void    (* const                            fp_vd_CONDCHK)(const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD);
    U1      (* const                            fp_u1_CALCTRNST)(const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD);
    void    (* const                            fp_vd_ACCMLT)(const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD, const U4 * u4_ap_DELTA);
    void    (* const                            fp_vd_UPDT)(const U1 u1_a_CNTTID);
    void    (* const                            fp_vd_GRPHUPDT)(const U1 u1_a_CNTTID);
    void    (* const                            fp_vd_RSTIMMW)(const U1 u1_a_ACTV, const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD);
} ST_TRIPCOM_IF;

typedef struct {
    U2      (* const                            fp_u2_CALCTXVAL)(const U1 u1_a_CNTTID, const U1 u1_a_UNIT);
    U1                                          u1_unittype;
} ST_TRIPCOM_CALCTX;

typedef struct {
    U1                                          u1_applid;
    U1                                          u1_cnttid;
    U2                                          u2_varbit;
} ST_TRIPCOM_CNTT;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void            vd_g_TripcomCfgTxBonInit(void);
void            vd_g_TripcomCfgTxWkupInit(void);
void            vd_g_TripcomCfgApplInit(void);

U2              u2_g_TripcomCfgGetVariation(void);
void            vd_g_TripcomCfgSetTxValHk(const U1 u1_a_CNTTID, const U2 u2_a_TXVAL);
void            vd_g_TripcomCfgGetUnit(U1 * u1_ap_unittype);

U1              u1_g_TripcomCfgGetPIEVSTS(U1 * u1p_a_pievsts);

void            vd_g_TripcomCfgSmoothingTask(void);

void            vd_s_TripomCfgPostAppTask(void);

void            vd_g_TripcomCfgNvmSyncCmplt(void);

U4              u4_g_TripcomCfgVarAvaJdg(const U2 u2_a_VARBIT);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern  void    (* const                        fp_gp_TRIPCOM_CALC_APPL_TASK[])(const U2 * u2_ap_STSFIELD);
extern  const   U1                              u1_g_TRIPCOM_NUM_CALC_APPL_TASK;
extern  const   ST_TRIPCOM_IF                   st_gp_TRIPCOM_IF_CFG[];
extern  const   ST_TRIPCOM_CALCTX               st_gp_TRIPCOM_CALCTX_CFG[];
extern  const   ST_TRIPCOM_CNTT                 st_gp_TRIPCOM_CNTTS_CFG[];
extern  const   U2                              u2_gp_TRIPCOM_GRPH_RSTBIT[];

#endif      /* TRIPCOM_CFG_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  tripcom.c                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/
