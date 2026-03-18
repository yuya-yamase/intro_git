/* 3.0.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Meter Customize                                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef MCST_CFG_H
#define MCST_CFG_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define MCST_CFG_H_MAJOR                         (3)
#define MCST_CFG_H_MINOR                         (0)
#define MCST_CFG_H_PATCH                         (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "nvmc_mgr.h"
#include "rim_ctl.h"
#include "mcst.h"
#include "veh_opemd.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define MCST_MAIN_TICK                           (20U)        /* 20 milliseconds */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define MCST_USR_NON                             (U1_MAX)

#define MCST_PSEU_NON                            (0U)
#define MCST_PSEU_USR_GUEST                      (7U)
#define MCST_PSEU_USR_USER1                      (1U)
#define MCST_PSEU_USR_USER2                      (2U)
#define MCST_PSEU_USR_USER3                      (3U)
#define MCST_PSEU_NUM                            (8U)

#define MCST_PSUND_NUM                           (8U)

#define MCST_NUM_4BYTE                           (4U)
#define MCST_USERINIT_SIZE                       (8U) /*initial target of user area*/
#define MCST_NVM_SIZE                            (16U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct {
    U1         u1_sup;             /* index support          */
    U1         u1_wid;             /* word index             */
    U1         u1_lsb;             /* lowest significant bit */
    U4         u4_bit;             /* bit                    */
}ST_MCST_BF;

typedef struct {
    U1         u1_id;              /* mcst id                */
    U4         u4_ini;             /* init parameter         */
}ST_MCST_INI;

typedef struct {
    U1         u1_offset;          /* offset for each user */
    U1         u1_offset_ini;      /* Initial value offset for each user init */
    U1         u1_offset_max;      /* Max     value offset for each user init */
}ST_MCST_OFFSET;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern U4                      u4_gp_mcst_bfword[];
extern U4                      u4_gp_mcst_bfword_unk[];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_g_McstCfgRcvSgnlPSUN_D(U1 * u1p_a_sgnl);
U1      u1_g_McstCfgRcvSgnlPSEU(U1 * u1p_a_sgnl);
U4      u4_g_McstCfgInit(const U1 u1_a_BFI);
void    vd_g_McstCfgUserChgHook(void);
void    vd_g_McstCfgUserCstmInitHook(void);
void    vd_g_McstCfgCstmInitHook(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern const U2                u2_sp_MCST_NVMID[];

extern const U1                u1_g_MCST_NWORD;
extern const U1                u1_g_MCST_NUM_WORD_USER;

extern const ST_MCST_BF        st_gp_MCST_BF[];
extern const ST_MCST_INI       st_gp_MCST_INI[];
extern const U1                u1_g_MCST_NUM_BF;

extern const ST_MCST_OFFSET    st_gp_MCST_OFFSET[];

extern const U2                u2_g_MCST_RES_TOUT;

extern const U2                u2_g_MCST_RIMID_USER;

extern const U1                u1_g_MCST_OFFSET_GUEST_INI;
extern const U1                u1_g_MCST_OFFSET_GUEST_MAX;

extern const U1                u1_gp_MCST_PSUND_TABLE[MCST_PSUND_NUM];
extern const U1                u1_gp_MCST_PSEU_TABLE[MCST_PSEU_NUM];

#endif      /* MCST_CFG_H */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  mcst.c                                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
