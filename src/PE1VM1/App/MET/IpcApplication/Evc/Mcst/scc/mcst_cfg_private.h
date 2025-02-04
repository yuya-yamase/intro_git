/* 2.4.0 */
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
#define MCST_CFG_H_MAJOR                         (2)
#define MCST_CFG_H_MINOR                         (4)
#define MCST_CFG_H_PATCH                         (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "nvmc_mgr.h"
#if 0   /* BEV BSW provisionally */
#else
#include "nvmc_mgr_cfg_STUB.h"
#endif
#include "rim_ctl.h"
#if 0   /* BEV BSW provisionally */
#else
#include "rim_ctl_cfg_STUB.h"
#endif
#include "mcst.h"
#include "veh_opemd.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define MCST_MAIN_TICK                           (20U)        /* 20 milliseconds */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define MCST_MEM_DID_N_A                         (0xffffU)

#define MCST_MEM_NUM_DEV                         (2U)
#define MCST_MEM_DEV_NVM                         (0U)
#define MCST_MEM_DEV_BRA                         (1U)
#define MCST_MEM_DEV_N_A                         (0xffffU)

#define MCST_GUEST_WRITE                         (0x1FFU)

#define MCST_USR_NON                             (U1_MAX)

#define MCST_PSER_NON                            (0U)
#define MCST_PSER_DEL                            (1U)
#define MCST_PSEU_NON                            (0U)
#define MCST_PSUND_NUM                           (8U)
#define MCST_PSEU_NUM                            (8U)

#define MCST_USRNAME_UPDTNUM_POS                 (0U)
#define MCST_USRNAME_UPDTNUM_INI                 (0x0FU)

#define MCST_SR_DNAME_NUM                        (3U)

#define MCST_NICKNAME_UPDT_FLAG                  (0x02U)

#define MCST_NUM_4BYTE                           (4U)
#define MCST_CMNINIT_SIZE                        (3U) /*initial target of common area*/
#define MCST_USERINIT_SIZE                       (8U) /*initial target of user area*/
#define MCST_NVM_SIZE                            (16U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define MCST_ESI_SI_ACT                          (0x01U)
#define MCST_ESI_NUO_DI                          (0x02U)

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

typedef struct {
    U1                          u1_func;
    U2                          u2_esopt_id;
}ST_MCST_FUNC;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern U4                      u4_gp_mcst_bfword[];
extern U4                      u4_gp_mcst_bfword_unk[];
extern U1                      u1_gp_mcst_func[];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_g_McstCfgEsichk(void);                               /* Return : MCST_ESI_XXX */
U1      u1_g_McstCfgRcvSgnlPSUN_D(U1 * u1p_a_sgnl);
U1      u1_g_McstCfgRcvSgnlPSER(U1 * u1p_a_sgnl);
U1      u1_g_McstCfgRcvSgnlPSEU(U1 * u1p_a_sgnl);
U1      u1_g_McstCfgJdgHUDFail(const U1 u1_a_NOW);
U1      u1_g_McstCfgReplaceCustomize(const U1 u1_a_BFI, const U1 u1_a_mcst);
U4      u4_g_McstCfgU4ReplaceCustomize(const U1 u1_a_BFI, const U4 u4_a_mcst);
U4      u4_g_McstCfgInit(const U1 u1_a_BFI);
void    vd_g_McstCfgUserChgHook(void);
void    vd_g_McstCfgUserCstmInitHook(void);
void    vd_g_McstCfgCstmInitHook(void);
void    vd_g_McstCfgSR_DNAMESend(void);
void    vd_g_McstCfgNickNameInitHook(const U1 u1_a_USER);
U1      u1_g_McstCfgGetBfIf(const U1 u1_a_BFI);
U1      u1_g_McstCfgGetFuelEcoVari(void);
void    vd_g_McstCfgGetLeftFuelEco(U4 * u4_ap_bf);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern U4              * const u4_gp_mcst_usrname[];
extern U2              * const u2_gp_mcst_nickname[];
extern U1              (* const fp_gp_u1_MCST_GETFUNC[])(void);
extern U1              (* const fp_gp_u1_MCST_GETDIAG[])(void);

extern const U2                u2_sp_MCST_NVMID[];

extern const U1                u1_g_MCST_NWORD;
extern const U1                u1_g_MCST_NUM_WORD_USER;
extern const U1                u1_g_MCST_NUM_WORD_COMMON;

extern const ST_MCST_BF        st_gp_MCST_BF[];
extern const ST_MCST_INI       st_gp_MCST_INI[];
extern const U1                u1_g_MCST_NUM_BF;

extern const U1                u1_g_MCST_FUNC_NUM;

extern const ST_MCST_OFFSET    st_gp_MCST_OFFSET[];

extern const U2                u2_g_MCST_RES_TOUT;

extern const U2                u2_g_MCST_RIMID_USER;

extern const U1                u1_g_MCST_USRDAT_NUM;
extern const U1                u1_g_MCST_USR_NUM;

extern const U1                u1_g_MCST_OFFSET_GUEST_INI;
extern const U1                u1_g_MCST_OFFSET_GUEST_MAX;

extern const U1                u1_gp_MCST_PSUND_TABLE[MCST_PSUND_NUM];
extern const U1                u1_gp_MCST_PSEU_TABLE[MCST_PSEU_NUM];
extern const U2                * const u2_gp2_MCST_USRNAME_DAT[];
extern const U2                * const u2_gp2_MCST_NICKNAME_NVMCID[];

extern const U1                u1_g_MCST_BFI_REV_ST;
extern const U1                u1_g_MCST_BFI_HUD;
extern const U1                u1_g_MCST_REV_ST_MIN;

extern const U1                u1_gp_MCST_PSEU_CHG_TABLE[MCST_PSEU_NUM][MCST_PSEU_NUM];

extern const U1                u1_g_MCST_NICKNAME_NUM;
extern const U1                u1_g_MCST_BFI_NAME_DRV1;
extern const U1                u1_g_MCST_BFI_NAME_DRV2;
extern const U1                u1_g_MCST_BFI_NAME_DRV3;

#endif      /* MCST_CFG_H */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  mcst.c                                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
