/* 2.4.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Meter Customize                                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define MCST_C_MAJOR                             (2)
#define MCST_C_MINOR                             (4)
#define MCST_C_PATCH                             (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "mcst_cfg_private.h"
#include "mcst_bf.h"
#include "memfill_u4.h"
#include "memcpy_u4.h"
#include "vardef.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((MCST_C_MAJOR != MCST_H_MAJOR) || \
     (MCST_C_MINOR != MCST_H_MINOR) || \
     (MCST_C_PATCH != MCST_H_PATCH))
#error "mcst.c and mcst.h : source and header files are inconsistent!"
#endif

#if ((MCST_C_MAJOR != MCST_CFG_H_MAJOR) || \
     (MCST_C_MINOR != MCST_CFG_H_MINOR) || \
     (MCST_C_PATCH != MCST_CFG_H_PATCH))
#error "mcst.c and mcst_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define MCST_RES_CSTM_INIT                          (0U)
#define MCST_RES_PRSL_DEL                           (1U)
#define MCST_MEM_UPDT_NUM                           (3U)
#define MCST_MEM_UPDT_SIZE                          (32U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4           u4_sp_mcst_mem_updt[MCST_MEM_UPDT_NUM];

static U1           u1_s_mcst_nickname_updt;

static U2           u2_s_mcst_res_tocnt;
static U1           u1_s_mcst_res_ctrl;
static U1           u1_s_mcst_res_flg;

static U1           u1_s_mcst_user;
static U1           u1_s_mcst_user_pre;
static U1           u1_s_mcst_del_user;

static U1           u1_s_mcst_del_req;
static U1           u1_s_mcst_pseu;

static U4           u4_sp_mcst_note_bfword[MCST_NUM_WORD_USER];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void    vd_s_McstUsrNameBonInit(void);
static void    vd_s_McstUsrNameRstWkupInit(void);

static void    vd_s_McstNickNameInit(void);

static void    vd_s_McstBfInit(void);
static void    vd_s_McstBfReset(void);
static void    vd_s_McstBfInitUser(const U1 u1_a_USER);

static U1      u1_s_McstMemInit(void);
static U1      u1_s_McstMemInitUser(const U1 u1_a_USER);

static void    vd_s_McstMemUpdt(void);
static void    vd_s_McstNvmReschk(const U1 u1_a_RES_CHK);

static void    vd_s_McstUpdateActiveUser(void);
static void    vd_s_McstUpdateActiveUserMem(const U1 u1_a_USER_PRE);
static void    vd_s_McstInitUser(void);

static void    vd_s_McstUsrNameRimWrite(void);
static void    vd_s_McstFuncSet(void);
static void    vd_s_McstUnknownUserInit(const U1 u1_a_USER_PRE);

static void    vd_s_McstNickNameNvmcWrite(void);
static void    vd_s_McstNickNameDel(const U1 u1_a_USRNUM);
static void    vd_s_McstSR_DNAMEDel(const U1 u1_a_USRNUM);

static U1      u1_s_McstCmpInit(U4 *u4_ap_rdata);
static U1      u1_s_McstDtfCmnInit(const U2 u2_a_nvmid);
static U1      u1_s_McstDtfUsrInit(const U2 u2_a_nvmid);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_McstBonInit(void)                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_McstBonInit(void)
{
    U4                  u4_t_loop;
    U2                  u2_t_mem_mid;
    U1                  u1_t_mem_chk;
    U4                  u4_t_loop_bf;

    vd_s_McstBfInit();
    vd_s_McstUsrNameBonInit();
    vd_s_McstNickNameInit();

    for(u4_t_loop = (U4)0U; u4_t_loop < (U4)MCST_NUM_NVM; u4_t_loop++){ /*NVM Area Num*/
        u2_t_mem_mid = u2_sp_MCST_NVMID[u4_t_loop];

        u4_t_loop_bf = u4_t_loop * (U4)MCST_NUM_4BYTE; /*start Nvm read Area*/
        u1_t_mem_chk  = u1_g_Nvmc_ReadOthrwithSts(u2_t_mem_mid, (U2)MCST_NVM_SIZE, (U1 *)&u4_gp_mcst_bfword[u4_t_loop_bf]);
        if(u1_t_mem_chk != (U1)NVMC_STATUS_KIND_OK){
            vd_g_MemfillU4(&u4_gp_mcst_bfword[u4_t_loop_bf], (U4)MCST_BF_INI, (U4)MCST_NUM_4BYTE); /* when read abnomal initualize */
        }
    }

    for(u4_t_loop = (U4)0U; u4_t_loop < (U4)u1_g_MCST_FUNC_NUM; u4_t_loop++){
        u1_gp_mcst_func[u4_t_loop] = (U1)0U;
    }

    u1_s_mcst_user      = (U1)MCST_USR_GUEST;
    u1_s_mcst_user_pre  = (U1)MCST_USR_GUEST;
    vd_s_McstUnknownUserInit(u1_s_mcst_user);

    for(u4_t_loop = (U4)0U; u4_t_loop < (U4)MCST_MEM_UPDT_NUM; u4_t_loop++){
        u4_sp_mcst_mem_updt[u4_t_loop] = (U4)0U;
    }
    u1_s_mcst_nickname_updt  = (U1)0U;

    u2_s_mcst_res_tocnt = (U2)U2_MAX;
    u1_s_mcst_res_ctrl  = (U1)MCST_RES_UNK;
    u1_s_mcst_res_flg   = (U1)MCST_RES_CSTM_INIT;

    u1_s_mcst_del_req  = (U1)MCST_PSER_NON;
    u1_s_mcst_pseu     = (U1)MCST_PSEU_NON;
    u1_s_mcst_del_user = (U1)MCST_USR_NON;
}

/*===================================================================================================================================*/
/*  static void    vd_s_McstUsrNameBonInit(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void      vd_s_McstUsrNameBonInit(void)
{
    U4  u4_t_loopdat;
    U4  u4_t_loopusr;

    for(u4_t_loopusr = (U4)MCST_USR_USER1 ; u4_t_loopusr < (U4)u1_g_MCST_USR_NUM ; u4_t_loopusr++){

        u4_gp_mcst_usrname[u4_t_loopusr][MCST_USRNAME_UPDTNUM_POS] = (U4)MCST_USRNAME_UPDTNUM_INI;
        for(u4_t_loopdat = (U4)1U ; u4_t_loopdat < (U4)u1_g_MCST_USRDAT_NUM ; u4_t_loopdat++){
            u4_gp_mcst_usrname[u4_t_loopusr][u4_t_loopdat] = (U4)0U;
        }
    }

    vd_s_McstUsrNameRimWrite();

}

/*===================================================================================================================================*/
/*  static void    vd_s_McstNickNameInit(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void      vd_s_McstNickNameInit(void)
{
    U1  u1_t_sts;
    U2  u2_t_nvmcid;
    U2  u2_t_data;
    U4  u4_t_loopdat;
    U4  u4_t_loopusr;

    for(u4_t_loopusr = (U4)MCST_USR_USER1 ; u4_t_loopusr < (U4)u1_g_MCST_USR_NUM ; u4_t_loopusr++){

        for(u4_t_loopdat = (U4)0U ; u4_t_loopdat < (U4)u1_g_MCST_NICKNAME_NUM ; u4_t_loopdat++){
            u2_gp_mcst_nickname[u4_t_loopusr][u4_t_loopdat] = (U2)0U;
        }
    }

    for(u4_t_loopusr = (U4)MCST_USR_USER1 ; u4_t_loopusr < (U4)u1_g_MCST_USR_NUM ; u4_t_loopusr++){

        for(u4_t_loopdat = (U4)0U ; u4_t_loopdat < (U4)u1_g_MCST_NICKNAME_NUM ; u4_t_loopdat++){

            u2_t_data = (U2)0U;
            u2_t_nvmcid = u2_gp2_MCST_NICKNAME_NVMCID[u4_t_loopusr][u4_t_loopdat];
            u1_t_sts = u1_g_Nvmc_ReadU2withSts(u2_t_nvmcid, &u2_t_data);

            if((u1_t_sts >= (U1)NVMC_STATUS_KIND_NG ) ||
               (u1_t_sts == (U1)NVMC_STATUS_ERRCOMP ) ||
               (u1_t_sts == (U1)NVMC_STATUS_CACHE_NG)){
                /* Do Nothing */
            }
            else{
                u2_gp_mcst_nickname[u4_t_loopusr][u4_t_loopdat] = u2_t_data;
            }
        }
    }

}

/*===================================================================================================================================*/
/*  void    vd_g_McstRstwkInit(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_McstRstwkInit(void)
{
    U4                  u4_t_loop;
    U2                  u2_t_mem_mid;
    U4                  u4_t_loop_bf;

    U1                  u1_t_sts;
    U1                  u1_t_current_user;
    U1                  u1_t_mem_chk;

    u1_t_current_user = (U1)MCST_USR_GUEST;

    vd_s_McstBfInit();
    vd_s_McstUsrNameRstWkupInit();
    vd_s_McstNickNameInit();

    for(u4_t_loop = (U4)0U; u4_t_loop < (U4)MCST_NUM_NVM; u4_t_loop++){

        u2_t_mem_mid = u2_sp_MCST_NVMID[u4_t_loop];
        u4_t_loop_bf = u4_t_loop * (U4)MCST_NUM_4BYTE; /*start Nvm read Area*/
        u1_t_mem_chk  = u1_g_Nvmc_ReadOthrwithSts(u2_t_mem_mid, (U2)MCST_NVM_SIZE, (U1 *)&u4_gp_mcst_bfword[u4_t_loop_bf]);
        if(u1_t_mem_chk != (U1)NVMC_STATUS_KIND_OK){           
            vd_g_MemfillU4(&u4_gp_mcst_bfword[u4_t_loop_bf], (U4)MCST_BF_INI, (U4)MCST_NUM_4BYTE); /* when read abnomal initualize */
        }

    }

    u1_s_mcst_user      = (U1)MCST_USR_GUEST;
    u1_s_mcst_user_pre  = (U1)MCST_USR_GUEST;
    u1_t_sts = u1_g_Rim_ReadU1withStatus(u2_g_MCST_RIMID_USER, &u1_t_current_user);
    if(((u1_t_sts & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK) &&
        (u1_t_current_user                    != (U1)MCST_USR_GUEST    )) {
        vd_s_McstUpdateActiveUserMem(u1_t_current_user);
    }

    for(u4_t_loop = (U4)0U; u4_t_loop < (U4)u1_g_MCST_FUNC_NUM; u4_t_loop++){
        u1_gp_mcst_func[u4_t_loop] = (U1)0U;
    }

    vd_s_McstUnknownUserInit(u1_s_mcst_user);

    for(u4_t_loop = (U4)0U; u4_t_loop < (U4)MCST_MEM_UPDT_NUM; u4_t_loop++){
        u4_sp_mcst_mem_updt[u4_t_loop] = (U4)0U;
    }

    u1_s_mcst_nickname_updt  = (U1)0U;

    u2_s_mcst_res_tocnt = (U2)U2_MAX;
    u1_s_mcst_res_ctrl  = (U1)MCST_RES_UNK;
    u1_s_mcst_res_flg   = (U1)MCST_RES_CSTM_INIT;

    u1_s_mcst_del_req  = (U1)MCST_PSER_NON;
    u1_s_mcst_pseu     = (U1)MCST_PSEU_NON;
    u1_s_mcst_del_user = (U1)MCST_USR_NON;
}

/*===================================================================================================================================*/
/*  static void    vd_s_McstUsrNameRstWkupInit(void)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void      vd_s_McstUsrNameRstWkupInit(void)
{
    U1  u1_t_sts;
    U2  u2_t_rimid;
    U4  u4_t_data;
    U4  u4_t_loopdat;
    U4  u4_t_loopusr;

    for(u4_t_loopusr = (U4)MCST_USR_USER1 ; u4_t_loopusr < (U4)u1_g_MCST_USR_NUM ; u4_t_loopusr++){

        u4_gp_mcst_usrname[u4_t_loopusr][MCST_USRNAME_UPDTNUM_POS] = (U4)MCST_USRNAME_UPDTNUM_INI;
        for(u4_t_loopdat = (U4)1U ; u4_t_loopdat < (U4)u1_g_MCST_USRDAT_NUM ; u4_t_loopdat++){

            u4_t_data = (U4)0U;
            u2_t_rimid = u2_gp2_MCST_USRNAME_DAT[u4_t_loopusr][u4_t_loopdat];
            u1_t_sts = u1_g_Rim_ReadU4withStatus(u2_t_rimid, &u4_t_data);

            if((u1_t_sts & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK) {
                u4_gp_mcst_usrname[u4_t_loopusr][u4_t_loopdat] = u4_t_data;
            }
            else{
                u4_gp_mcst_usrname[u4_t_loopusr][u4_t_loopdat] = (U4)0U;
            }
        }
    }
}

/*===================================================================================================================================*/
/*  void    vd_g_McstMainTask(void)                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_McstMainTask(void)
{
    U1                  u1_t_esi_chk;
    U1                  u1_t_res_chk;
    U1                  u1_t_mem_updt;
    U4                  u4_t_loop;
    U1                  u1_t_bfidx;

    u1_t_esi_chk = u1_g_McstCfgEsichk() & ((U1)MCST_ESI_NUO_DI | (U1)MCST_ESI_SI_ACT);

    vd_s_McstFuncSet();
    vd_s_McstUsrNameRimWrite();

    vd_s_McstUpdateActiveUser();
    vd_s_McstInitUser();

    u1_t_res_chk        = u1_s_mcst_res_ctrl;

    u1_t_mem_updt = (U1)FALSE;
    for(u4_t_loop = (U4)0U; u4_t_loop < (U4)MCST_MEM_UPDT_NUM; u4_t_loop++){
        if(u4_sp_mcst_mem_updt[u4_t_loop] != (U4)0U){
            u1_t_mem_updt =(U1)TRUE;
            break;
        }
    }

    if(u1_t_esi_chk       == (U1)0U){
        if(u1_t_res_chk   == (U1)MCST_RES_RUN){
            if(u1_s_mcst_res_flg == (U1)MCST_RES_CSTM_INIT){
                u1_t_res_chk = u1_s_McstMemInit();
            }
            else if((u1_s_mcst_res_flg  == (U1)MCST_RES_PRSL_DEL) &&
                    (u1_s_mcst_del_user  < (U1)MCST_USR_UNKNOWN )){
                u1_t_res_chk       = u1_s_McstMemInitUser(u1_s_mcst_del_user);
                u1_s_mcst_del_user = (U1)MCST_USR_NON;
            }
            else{
                /* Do Nothing */
            }
        }
        else if(u1_t_mem_updt == (U1)TRUE){
            vd_s_McstMemUpdt();
        }
        else{
            /* Do Nothing */
        }
        if(u1_s_mcst_nickname_updt != (U1)0U){
            vd_s_McstNickNameNvmcWrite();
        }
        else{
            /* Do Nothing */
        }
    }
    else{
        /* Do Nothing */
    }
    /* Set initial value for XSPI */ 
    vd_g_MemfillU4(&u4_sp_mcst_note_bfword[0], (U4)0U, (U4)MCST_NUM_WORD_USER);
    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)MCST_NUM_BF; u4_t_loop++) {
        u1_t_bfidx = st_gp_MCST_BF[u4_t_loop].u1_wid;
        u4_sp_mcst_note_bfword[u1_t_bfidx] |= (((U4)u1_g_McstBf(st_gp_MCST_INI[u4_t_loop].u1_id)
            & st_gp_MCST_BF[u4_t_loop].u4_bit)
            << st_gp_MCST_BF[u4_t_loop].u1_lsb);
    }
    vd_g_McstCfgGetLeftFuelEco(&u4_sp_mcst_note_bfword[0]);

    vd_s_McstNvmReschk(u1_t_res_chk);
    for(u4_t_loop = (U4)0U; u4_t_loop < (U4)MCST_MEM_UPDT_NUM; u4_t_loop++){
        u4_sp_mcst_mem_updt[u4_t_loop] = (U4)0U;
    }
    u1_s_mcst_nickname_updt = (U1)0U;
}
/*===================================================================================================================================*/
/*  U1      u1_g_McstBf(const U1 u1_a_BFI)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_McstBf(const U1 u1_a_BFI)
{
    U1                  u1_t_wid;
    U1                  u1_t_lsb;
    U4                  u4_t_bit;
    U1                  u1_t_mcst;
    U1                  u1_t_sup;

    u4_t_bit  = (U4)0U;
    u1_t_sup  = st_gp_MCST_BF[u1_a_BFI].u1_sup;

    if((u1_a_BFI  < u1_g_MCST_NUM_BF) &&
       (u1_t_sup == (U1)TRUE        )){

        u1_t_wid  = st_gp_MCST_BF[u1_a_BFI].u1_wid;
        u1_t_lsb  = st_gp_MCST_BF[u1_a_BFI].u1_lsb;
        u4_t_bit  = st_gp_MCST_BF[u1_a_BFI].u4_bit;

        if(u1_s_mcst_user != (U1)MCST_USR_UNKNOWN){

            if(u1_t_wid >= (U1)MCST_NUM_WORD_COMMON){
                u1_t_wid  = u1_t_wid + st_gp_MCST_OFFSET[u1_s_mcst_user].u1_offset;
            }

            if(u1_t_wid < (U1)MCST_NUM_WORD){
                u1_t_mcst = (U1)(u4_gp_mcst_bfword[u1_t_wid] >> u1_t_lsb) & (U1)u4_t_bit;
            }
            else{
                u1_t_mcst = (U1)MCST_BF_UNK;
            }
        }
        else {
            u1_t_mcst = (U1)(u4_gp_mcst_bfword_unk[u1_t_wid] >> u1_t_lsb) & (U1)u4_t_bit;
        }

    }
    else{
        u1_t_mcst = (U1)MCST_BF_UNK;
    }

    if(u1_t_mcst == (U1)u4_t_bit){
        u1_t_mcst = (U1)u4_g_McstCfgInit(u1_a_BFI);
    }

    u1_t_mcst = u1_g_McstCfgReplaceCustomize(u1_a_BFI, u1_t_mcst);

    if(u1_a_BFI == (U1)MCST_BFI_HUD_ROT){
        u1_t_mcst = (U1)u4_g_McstBfU4((U1)MCST_BFI_HUD_ROT);
    }

    return(u1_t_mcst);
}

/*===================================================================================================================================*/
/*  void    vd_g_McstBfPut(const U1 u1_a_BFI, const U1 u1_a_NEXT)                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_McstBfPut(const U1 u1_a_BFI, const U1 u1_a_NEXT)
{
    U4                  u4_t_mask;
    U1                  u1_t_wid;
    U1                  u1_t_lsb;
    U4                  u4_t_bit;
    U1                  u1_t_las;
    U1                  u1_t_sup;
    U1                  u1_t_updt_byte;
    U1                  u1_t_updt_bit;
    U1                  u1_t_bfi;

    u1_t_bfi = u1_g_McstCfgGetBfIf(u1_a_BFI);

    u1_t_sup  = st_gp_MCST_BF[u1_t_bfi].u1_sup;

    if(u1_t_bfi == (U1)MCST_BFI_HUD_ROT){
        vd_g_McstBfPutU4(u1_t_bfi, u1_a_NEXT);
        u1_t_sup = (U1)FALSE;
    }

    if((u1_s_mcst_res_ctrl > (U1)MCST_RES_RUN) &&
       (u1_t_bfi           < u1_g_MCST_NUM_BF) &&
       (u1_t_sup          == (U1)TRUE        )){

        u1_t_wid = st_gp_MCST_BF[u1_t_bfi].u1_wid;
        u1_t_lsb = st_gp_MCST_BF[u1_t_bfi].u1_lsb;
        u4_t_bit = st_gp_MCST_BF[u1_t_bfi].u4_bit;

        if(u1_s_mcst_user != (U1)MCST_USR_UNKNOWN){

            if (u1_t_wid >= (U1)MCST_NUM_WORD_COMMON){
                u1_t_wid  = u1_t_wid + st_gp_MCST_OFFSET[u1_s_mcst_user].u1_offset;
            }

            if(u1_t_wid < (U1)MCST_NUM_WORD){
                u1_t_las = (U1)(u4_gp_mcst_bfword[u1_t_wid] >> u1_t_lsb) & (U1)u4_t_bit;
            }
            else{
                u1_t_las = (U1)MCST_BF_UNK;
            }

            if((u1_a_NEXT <= (U1)u4_t_bit ) &&
               (u1_t_las  != u1_a_NEXT    )){

                u4_t_mask                            = (U4)U4_MAX ^ (u4_t_bit << u1_t_lsb);
                u4_gp_mcst_bfword[u1_t_wid]         &= u4_t_mask;
                u4_gp_mcst_bfword[u1_t_wid]         |= ((U4)u1_a_NEXT << u1_t_lsb);

                u1_t_updt_byte                       = u1_t_wid / (U1)MCST_MEM_UPDT_SIZE;
                u1_t_updt_bit                        = u1_t_wid % (U1)MCST_MEM_UPDT_SIZE;
                u4_sp_mcst_mem_updt[u1_t_updt_byte] |= ((U4)0x00000001U << u1_t_updt_bit);
            }
        }
        else{
            if(u1_a_NEXT <= (U1)u4_t_bit){

                u4_t_mask                    = (U4)U4_MAX ^ (u4_t_bit << u1_t_lsb);
                u4_gp_mcst_bfword_unk[u1_t_wid] &= u4_t_mask;
                u4_gp_mcst_bfword_unk[u1_t_wid] |= ((U4)u1_a_NEXT << u1_t_lsb);

            }
        }
    }
}

/*===================================================================================================================================*/
/*  static void    vd_s_McstBfInit(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_McstBfInit(void)
{
    U4                  u4_t_loop;

    for(u4_t_loop = (U4)0U; u4_t_loop < (U4)u1_g_MCST_NWORD; u4_t_loop++){
        u4_gp_mcst_bfword[u4_t_loop] = (U4)MCST_BF_INI;
    }
    vd_g_MemfillU4(&u4_sp_mcst_note_bfword[0], (U4)0U, (U4)MCST_NUM_WORD_USER);
}

/*===================================================================================================================================*/
/*  U1      u1_g_McstReset(const U1 u1_a_RUN)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_McstReset(const U1 u1_a_RUN)
{
    if((u1_a_RUN           == (U1)TRUE        ) &&
       (u1_s_mcst_res_ctrl >  (U1)MCST_RES_RUN)){

        vd_s_McstBfReset();
        vd_g_McstCfgCstmInitHook();

        u2_s_mcst_res_tocnt = (U2)0U;
        u1_s_mcst_res_ctrl  = (U1)MCST_RES_RUN;
        u1_s_mcst_res_flg   = (U1)MCST_RES_CSTM_INIT;
    }

    return(u1_s_mcst_res_ctrl);
}
/*===================================================================================================================================*/
/*  static void    vd_s_McstBfReset(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_McstBfReset(void)
{
    switch(u1_s_mcst_user){
        case (U1)MCST_USR_GUEST:
            vd_g_MemfillU4(&u4_gp_mcst_bfword[0], (U4)MCST_BF_INI, (U4)MCST_CMNINIT_SIZE);
            vd_g_MemfillU4(&u4_gp_mcst_bfword[MCST_BF_OFFSET_GUEST_INI], (U4)MCST_BF_INI, (U4)MCST_USERINIT_SIZE);
            break;
        case (U1)MCST_USR_USER1:
            vd_g_MemfillU4(&u4_gp_mcst_bfword[0], (U4)MCST_BF_INI, (U4)MCST_CMNINIT_SIZE);
            vd_g_MemfillU4(&u4_gp_mcst_bfword[MCST_BF_OFFSET_USER1_INI], (U4)MCST_BF_INI, (U4)MCST_USERINIT_SIZE);
            break;
        case (U1)MCST_USR_USER2:
            vd_g_MemfillU4(&u4_gp_mcst_bfword[0], (U4)MCST_BF_INI, (U4)MCST_CMNINIT_SIZE);
            vd_g_MemfillU4(&u4_gp_mcst_bfword[MCST_BF_OFFSET_USER2_INI], (U4)MCST_BF_INI, (U4)MCST_USERINIT_SIZE);
            break;
        case (U1)MCST_USR_USER3:
            vd_g_MemfillU4(&u4_gp_mcst_bfword[0], (U4)MCST_BF_INI, (U4)MCST_CMNINIT_SIZE);
            vd_g_MemfillU4(&u4_gp_mcst_bfword[MCST_BF_OFFSET_USER3_INI], (U4)MCST_BF_INI, (U4)MCST_USERINIT_SIZE);
            break;
        default:
            vd_g_MemfillU4(&u4_gp_mcst_bfword_unk[0], (U4)MCST_BF_INI, (U4)MCST_CMNINIT_SIZE);
            vd_g_MemfillU4(&u4_gp_mcst_bfword_unk[MCST_BF_OFFSET_GUEST_INI], (U4)MCST_BF_INI, (U4)MCST_USERINIT_SIZE);
            break;
    }
}

/*===================================================================================================================================*/
/*  static void    vd_s_McstBfInitUser(const U1 u1_a_USER)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_McstBfInitUser(const U1 u1_a_USER)
{
    U4                  u4_t_loop;
    U1                  u1_t_offsetini;
    U1                  u1_t_offsetmax;

    u1_t_offsetini = st_gp_MCST_OFFSET[u1_a_USER].u1_offset_ini;
    u1_t_offsetmax = st_gp_MCST_OFFSET[u1_a_USER].u1_offset_max;

    for(u4_t_loop = (U4)u1_t_offsetini; u4_t_loop < (U4)u1_t_offsetmax; u4_t_loop++){
        u4_gp_mcst_bfword[u4_t_loop] = (U4)MCST_BF_INI;
    }
}

/*===================================================================================================================================*/
/*  static U1      u1_s_McstMemInit(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_McstMemInit(void)
{
    U1                  u1_t_res_chk;
    U1                  u1_t_res_cmnchk;
    U1                  u1_t_res_usrchk1;
    U1                  u1_t_res_usrchk2;

    u1_t_res_chk = (U1)MCST_RES_SUC;

    u1_t_res_cmnchk = u1_s_McstDtfCmnInit((U2)NVMCID_OTR_MCST_IDX_COMMON);
        
    switch(u1_s_mcst_user){
        case (U1)MCST_USR_GUEST:
            u1_t_res_usrchk1 = u1_s_McstDtfUsrInit((U2)NVMCID_OTR_MCST_IDX_GUEST_1);
            u1_t_res_usrchk2 = u1_s_McstDtfUsrInit((U2)NVMCID_OTR_MCST_IDX_GUEST_2);
            break;
        case (U1)MCST_USR_USER1:
            u1_t_res_usrchk1 = u1_s_McstDtfUsrInit((U2)NVMCID_OTR_MCST_IDX_USER1_1);
            u1_t_res_usrchk2 = u1_s_McstDtfUsrInit((U2)NVMCID_OTR_MCST_IDX_USER1_2);
            break;
        case (U1)MCST_USR_USER2:
            u1_t_res_usrchk1 = u1_s_McstDtfUsrInit((U2)NVMCID_OTR_MCST_IDX_USER2_1);
            u1_t_res_usrchk2 = u1_s_McstDtfUsrInit((U2)NVMCID_OTR_MCST_IDX_USER2_1);
            break;
        case (U1)MCST_USR_USER3:
            u1_t_res_usrchk1 = u1_s_McstDtfUsrInit((U2)NVMCID_OTR_MCST_IDX_USER3_1); 
            u1_t_res_usrchk2 = u1_s_McstDtfUsrInit((U2)NVMCID_OTR_MCST_IDX_USER3_2);
            break;
        default:
            u1_t_res_usrchk1 = (U1)MCST_RES_SUC;
            u1_t_res_usrchk2 = (U1)MCST_RES_SUC;
            break;
    }

    if((u1_t_res_cmnchk == (U1)MCST_RES_RUN) ||
       (u1_t_res_usrchk1 == (U1)MCST_RES_RUN) ||
       (u1_t_res_usrchk2 == (U1)MCST_RES_RUN)) {
        u1_t_res_chk = (U1)MCST_RES_RUN;
    }

    return(u1_t_res_chk);
}

/*===================================================================================================================================*/
/*  static U1      u1_s_McstMemInitUser(const U1 u1_a_USER)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_McstMemInitUser(const U1 u1_a_USER)
{
    U4                  u4_t_loop;

    U2                  u2_t_mem_mid;

    U1                  u1_t_nvm_chk;
    U1                  u1_t_res_chk;

    U1                  u1_t_offsetini;
    U1                  u1_t_offsetmax;
    U4                  u4_tp_rdata[MCST_NUM_4BYTE];
    U4                  u4_tp_wdata[MCST_NUM_4BYTE];
    U1                  u1_t_cmpchk;


    u1_t_offsetini = (st_gp_MCST_OFFSET[u1_a_USER].u1_offset_ini / (U1)MCST_NUM_4BYTE); /* start userX NVM area */
    u1_t_offsetmax = (st_gp_MCST_OFFSET[u1_a_USER].u1_offset_max / (U1)MCST_NUM_4BYTE); /* end usrX NVM area    */

    vd_g_MemfillU4(&u4_tp_rdata[0], (U4)MCST_BF_INI, (U4)MCST_NUM_4BYTE);
    vd_g_MemfillU4(&u4_tp_wdata[0], (U4)MCST_BF_INI, (U4)MCST_NUM_4BYTE);

    u1_t_res_chk = (U1)MCST_RES_SUC;
    for(u4_t_loop = (U4)u1_t_offsetini; u4_t_loop < (U4)u1_t_offsetmax; u4_t_loop++){
        u2_t_mem_mid = u2_sp_MCST_NVMID[u4_t_loop];
        u1_t_nvm_chk  = u1_g_Nvmc_ReadOthrwithSts(u2_t_mem_mid, (U2)MCST_NVM_SIZE, (U1 *)&u4_tp_rdata[0]);
        u1_t_cmpchk = u1_s_McstCmpInit(&u4_tp_rdata[0]);
        if((u1_t_cmpchk == (U1)FALSE                 ) ||
           (u1_t_nvm_chk  >= (U1)NVMC_STATUS_KIND_NG ) ||
           (u1_t_nvm_chk  == (U1)NVMC_STATUS_ERRCOMP ) ||
           (u1_t_nvm_chk  == (U1)NVMC_STATUS_CACHE_NG)){
            vd_g_Nvmc_ClearShtdwnTimer();
            vd_g_Nvmc_WriteOthr(u2_t_mem_mid, (U2)MCST_NVM_SIZE, (U1 *)&u4_tp_wdata[0]);
            u1_t_res_chk = (U1)MCST_RES_RUN;
        }
        else if(u1_t_nvm_chk == (U1)NVMC_STATUS_WRITING){
            u1_t_res_chk = (U1)MCST_RES_RUN;
        }
        else{
            /* Do Nothing */
        }
    }

    return(u1_t_res_chk);
}

/*===================================================================================================================================*/
/*  static void    vd_s_McstMemUpdt(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_McstMemUpdt(void)
{
    U4                  u4_t_loop;
    U4                  u4_t_updt;
    U2                  u2_t_mem_mid;
    U4                  u4_t_loop_bf;
    U4                  u4_t_loop_max;
    U4                  u4_t_updt_byte;
    U4                  u4_t_updt_bit;
    U4                  u4_t_strt_idx;

    for(u4_t_loop = (U4)0U; u4_t_loop < (U4)MCST_NUM_NVM; u4_t_loop++){
        u2_t_mem_mid   = u2_sp_MCST_NVMID[u4_t_loop];
        u4_t_updt = (U4)0U;
        u4_t_loop_bf = u4_t_loop * (U4)MCST_NUM_4BYTE;
        u4_t_loop_max = u4_t_loop_bf + (U4)MCST_NUM_4BYTE;
        for(; u4_t_loop_bf < u4_t_loop_max; u4_t_loop_bf++){
            u4_t_updt_byte = u4_t_loop_bf / (U4)MCST_MEM_UPDT_SIZE;
            u4_t_updt_bit  = u4_t_loop_bf % (U4)MCST_MEM_UPDT_SIZE;
            u4_t_updt     |= (u4_sp_mcst_mem_updt[u4_t_updt_byte] & ((U4)0x00000001U << u4_t_updt_bit));
        }
        if(u4_t_updt != (U4)0U){
            u4_t_strt_idx = u4_t_loop * (U4)MCST_NUM_4BYTE;
            vd_g_Nvmc_ClearShtdwnTimer();
            vd_g_Nvmc_WriteOthr(u2_t_mem_mid, (U2)MCST_NVM_SIZE, (U1 *)&u4_gp_mcst_bfword[u4_t_strt_idx]);
        }
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_McstNvmReschk(const U1 u1_a_RES_CHK)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_McstNvmReschk(const U1 u1_a_RES_CHK)
{
    if(u2_s_mcst_res_tocnt < (U2)U2_MAX){
        u2_s_mcst_res_tocnt++;
    }

    if(u1_s_mcst_res_ctrl > (U1)MCST_RES_RUN){
     /* u1_s_mcst_res_ctrl = keep last;        */
    }
    else if(u1_a_RES_CHK == (U1)MCST_RES_SUC){
        u1_s_mcst_res_ctrl = (U1)MCST_RES_SUC;
    }
    else if(u2_s_mcst_res_tocnt >= u2_g_MCST_RES_TOUT){
        u1_s_mcst_res_ctrl = (U1)MCST_RES_FAI;
    }
    else{
     /* u1_s_mcst_res_ctrl = (U1)MCST_RES_RUN; */
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_McstUpdateActiveUser(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_McstUpdateActiveUser(void)
{
    U1  u1_t_msgsts;
    U1  u1_t_psun_d;
    U1  u1_t_updt_user;

    u1_t_psun_d    = (U1)0U;

    u1_t_msgsts = u1_g_McstCfgRcvSgnlPSUN_D(&u1_t_psun_d);

    if(u1_t_msgsts == (U1)0U){

        if(u1_t_psun_d < (U1)MCST_PSUND_NUM){
            u1_t_updt_user = u1_gp_MCST_PSUND_TABLE[u1_t_psun_d];
        }
        else{
            u1_t_updt_user = (U1)MCST_USR_GUEST;
        }

        if(u1_t_updt_user != u1_s_mcst_user){
            if(u1_t_updt_user == (U1)MCST_USR_GUEST){
                vd_g_Rim_WriteU1(u2_g_MCST_RIMID_USER, u1_t_updt_user);
                vd_s_McstUpdateActiveUserMem(u1_s_mcst_user);
            }
            else if(u1_t_updt_user == (U1)MCST_USR_UNKNOWN){
                vd_s_McstUnknownUserInit(u1_s_mcst_user);
            }
            else {
                vd_g_Rim_WriteU1(u2_g_MCST_RIMID_USER, u1_t_updt_user);
            }
            u1_s_mcst_user_pre = u1_s_mcst_user;
            u1_s_mcst_user     = u1_t_updt_user;
            vd_g_McstCfgUserChgHook();
        }
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_McstUpdateActiveUserMem(const U1 u1_a_USER_PRE)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_McstUpdateActiveUserMem(const U1 u1_a_USER_PRE)
{
    U4  u4_t_loop;
    U4  u4_t_offsetidx;
    U4  u4_t_updt_byte;
    U4  u4_t_updt_bit;

    if(u1_a_USER_PRE < (U1)MCST_USR_UNKNOWN){
        /* update guest area (index6-index21) */
        for(u4_t_loop = (U4)u1_g_MCST_OFFSET_GUEST_INI; u4_t_loop < (U4)u1_g_MCST_OFFSET_GUEST_MAX; u4_t_loop++){
            u4_t_offsetidx = u4_t_loop + (U4)(st_gp_MCST_OFFSET[u1_a_USER_PRE].u1_offset);

            if(u4_t_offsetidx < (U4)u1_g_MCST_NWORD){
                u4_t_updt_byte                       = u4_t_loop / (U4)MCST_MEM_UPDT_SIZE;
                u4_t_updt_bit                        = u4_t_loop % (U4)MCST_MEM_UPDT_SIZE;
                u4_gp_mcst_bfword[u4_t_loop]         = u4_gp_mcst_bfword[u4_t_offsetidx];
                u4_sp_mcst_mem_updt[u4_t_updt_byte] |= ((U4)0x00000001U << u4_t_updt_bit);
            }
        }
        vd_s_McstMemUpdt();
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_McstInitUser(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_McstInitUser(void)
{
    U1 u1_t_igon;
    U1 u1_t_msgsts;
    U1 u1_t_del_req;
    U1 u1_t_pseu;
    U1 u1_t_del_user;
    U1 u1_t_init_jdg;

    u1_t_del_req   = (U1)0U;
    u1_t_pseu      = (U1)0U;
    u1_t_init_jdg  = (U1)FALSE;

    u1_t_igon = u1_g_VehopemdIgnOn();
    u1_t_msgsts  = u1_g_McstCfgRcvSgnlPSER(&u1_t_del_req);
    u1_t_msgsts |= u1_g_McstCfgRcvSgnlPSEU(&u1_t_pseu);

    if(u1_t_msgsts != (U1)0U){
        u1_t_del_req = (U1)MCST_PSER_NON;
        u1_t_pseu    = (U1)MCST_PSEU_NON;
    }

    if((u1_t_igon == (U1)TRUE) &&
       (u1_t_msgsts == (U1)0U)){
        if((u1_t_del_req  == (U1)MCST_PSER_DEL) &&
           (u1_t_pseu      < (U1)MCST_PSEU_NUM)){
            u1_t_del_user = u1_gp_MCST_PSEU_TABLE[u1_t_pseu];
        }
        else {
            u1_t_del_user = (U1)MCST_USR_NON;
        }
        if(u1_t_del_user != (U1)MCST_USR_NON){
            if(u1_s_mcst_del_req == (U1)MCST_PSER_NON){
                u1_t_init_jdg = (U1)TRUE;
            }
            else if((u1_s_mcst_pseu != u1_t_pseu        ) &&
                    (u1_s_mcst_pseu  < (U1)MCST_PSEU_NUM)){
                u1_t_init_jdg = u1_gp_MCST_PSEU_CHG_TABLE[u1_s_mcst_pseu][u1_t_pseu];
            }
            else{
                u1_t_init_jdg = (U1)FALSE;
            }
        }
        else {
            u1_t_init_jdg = (U1)FALSE;
        }
        if((u1_t_init_jdg     == (U1)TRUE        ) &&
           (u1_s_mcst_res_ctrl > (U1)MCST_RES_RUN)){
            vd_s_McstSR_DNAMEDel(u1_t_del_user);
            vd_s_McstMemUpdt();
            vd_s_McstNickNameDel(u1_t_del_user);
            vd_s_McstBfInitUser(u1_t_del_user);
            vd_g_McstCfgUserCstmInitHook();
            u1_s_mcst_res_ctrl  = (U1)MCST_RES_RUN;
            u1_s_mcst_res_flg   = (U1)MCST_RES_PRSL_DEL;
            u1_s_mcst_del_user  = u1_t_del_user;
        }
    }
    u1_s_mcst_del_req = u1_t_del_req;
    u1_s_mcst_pseu    = u1_t_pseu;
}
/*===================================================================================================================================*/
/*  void    vd_g_McstUsrNamePut(const U4 * u4_ap_USRDAT , const U1 u1_a_USRNUM)                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_McstUsrNamePut(const U4 * u4_ap_USRDAT , const U1 u1_a_USRNUM)
{
    U4  u4_t_loop;

    if((u1_a_USRNUM != (U1)MCST_USR_GUEST) &&
       (u1_a_USRNUM  < u1_g_MCST_USR_NUM ))   {

        for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)u1_g_MCST_USRDAT_NUM ; u4_t_loop++){
            u4_gp_mcst_usrname[u1_a_USRNUM][u4_t_loop] = u4_ap_USRDAT[u4_t_loop];
        }
    }
}

/*===================================================================================================================================*/
/*  U1      u1_g_McstReadUsrName( U4 * u4_ap_mcst_usrdat , const U1 u1_a_SIZE , const U1 u1_a_USRNUM)                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_McstReadUsrName( U4 * u4_ap_mcst_usrdat , const U1 u1_a_SIZE , const U1 u1_a_USRNUM)
{
    U1  u1_t_result;
    U4  u4_t_loop;
    U1  u1_t_sig;
    U1  u1_t_msgsts;

    u1_t_msgsts = u1_g_McstCfgRcvSgnlPSUN_D(&u1_t_sig);

    if((u4_ap_mcst_usrdat != vdp_PTR_NA          ) &&
       (u1_a_SIZE         >= u1_g_MCST_USRDAT_NUM) &&
       (u1_t_msgsts       == (U1)0U              )){

        for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)u1_g_MCST_USRDAT_NUM ; u4_t_loop++){
            u4_ap_mcst_usrdat[u4_t_loop] = (U4)0U;
        }

        switch (u1_a_USRNUM){
            case (U1)MCST_USR_USER1:                 /* Fall Through */
            case (U1)MCST_USR_USER2:
            case (U1)MCST_USR_USER3:

                for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)u1_g_MCST_USRDAT_NUM ; u4_t_loop++){
                    u4_ap_mcst_usrdat[u4_t_loop] = u4_gp_mcst_usrname[u1_a_USRNUM][u4_t_loop];
                }

                u1_t_result = (U1)MCST_VALID;
                break;
            case (U1)MCST_USR_CURRENT:

                if((u1_s_mcst_user != (U1)MCST_USR_GUEST  ) &&
                   (u1_s_mcst_user != (U1)MCST_USR_UNKNOWN)){

                    for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)u1_g_MCST_USRDAT_NUM ; u4_t_loop++){
                        u4_ap_mcst_usrdat[u4_t_loop] = u4_gp_mcst_usrname[u1_s_mcst_user][u4_t_loop];
                    }
                    u1_t_result = (U1)MCST_VALID;
                }
                else {
                    u1_t_result = (U1)MCST_INVALID;
                }

                break;
            /* case (U1)MCST_USR_GUEST: */           /* Fall Through */
            default:
                u1_t_result = (U1)MCST_INVALID;
                break;
        }
    } else if((u4_ap_mcst_usrdat != vdp_PTR_NA          ) &&
              (u1_a_SIZE         >= u1_g_MCST_USRDAT_NUM) &&
              (u1_t_msgsts       != (U1)0U              )){
            for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)u1_g_MCST_USRDAT_NUM ; u4_t_loop++){
                u4_ap_mcst_usrdat[u4_t_loop] = (U4)0U;
            }
            u1_t_result = (U1)MCST_VALID;
    }
    else {
        u1_t_result = (U1)MCST_INVALID;
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  static void    vd_s_McstUsrNameRimWrite(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void      vd_s_McstUsrNameRimWrite(void)
{
    U2  u2_t_rimid;
    U4  u4_t_data;
    U4  u4_t_loopdat;
    U4  u4_t_loopusr;

    for(u4_t_loopusr = (U4)MCST_USR_USER1 ; u4_t_loopusr < (U4)u1_g_MCST_USR_NUM ; u4_t_loopusr++){

        for(u4_t_loopdat = (U4)1U ; u4_t_loopdat < (U4)u1_g_MCST_USRDAT_NUM ; u4_t_loopdat++){
            u2_t_rimid = u2_gp2_MCST_USRNAME_DAT[u4_t_loopusr][u4_t_loopdat];
            u4_t_data  = u4_gp_mcst_usrname[u4_t_loopusr][u4_t_loopdat];
            vd_g_Rim_WriteU4(u2_t_rimid, u4_t_data);
        }
    }
}

/*===================================================================================================================================*/
/*  static void    vd_s_McstFuncSet(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void      vd_s_McstFuncSet(void)
{
    U4  u4_t_loop;

    for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)u1_g_MCST_FUNC_NUM ; u4_t_loop++){
        u1_gp_mcst_func[u4_t_loop] = (fp_gp_u1_MCST_GETFUNC[u4_t_loop])();
    }

    vd_g_McstCfgSR_DNAMESend();
}

#if ((defined(MCST_12INCH_SUPPORT)) && (MCST_12INCH_SUPPORT == 1))
/*===================================================================================================================================*/
/*  U1         u1_g_McstFunc(const U1 u1_a_FUNCID)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1            u1_g_McstFunc(const U1 u1_a_FUNCID)
{
    U1  u1_t_func;

    if(u1_a_FUNCID < u1_g_MCST_FUNC_NUM){
        u1_t_func = u1_gp_mcst_func[u1_a_FUNCID];
    }
    else {
        u1_t_func = (U1)MCST_INVALID;
    }

    return(u1_t_func);
}
#endif

/*===================================================================================================================================*/
/*  static void    vd_s_McstUnknownUserInit(const U1 u1_a_USER_PRE)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void      vd_s_McstUnknownUserInit(const U1 u1_a_USER_PRE)
{
    U4  u4_t_loop;
    U4  u4_t_offsetidx;

    for(u4_t_loop = (U4)0U; u4_t_loop < (U4)u1_g_MCST_NUM_WORD_COMMON; u4_t_loop++){
        u4_gp_mcst_bfword_unk[u4_t_loop] = u4_gp_mcst_bfword[u4_t_loop];
    }

    if(u1_a_USER_PRE < (U1)MCST_USR_UNKNOWN){
        for(u4_t_loop = (U4)u1_g_MCST_OFFSET_GUEST_INI; u4_t_loop < (U4)u1_g_MCST_OFFSET_GUEST_MAX; u4_t_loop++){
            u4_t_offsetidx = u4_t_loop + (U4)(st_gp_MCST_OFFSET[u1_a_USER_PRE].u1_offset);

            if(u4_t_offsetidx < (U4)u1_g_MCST_NWORD){
                u4_gp_mcst_bfword_unk[u4_t_loop] = u4_gp_mcst_bfword[u4_t_offsetidx];
            }
        }
    }
}

/*===================================================================================================================================*/
/*  U4      u4_g_McstBfU4(const U1 u1_a_BFI)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4      u4_g_McstBfU4(const U1 u1_a_BFI)
{
    U1                  u1_t_wid;
    U1                  u1_t_lsb;
    U4                  u4_t_bit;
    U4                  u4_t_mcst;
    U1                  u1_t_sup;

    u4_t_bit  = (U4)0U;
    u1_t_sup  = st_gp_MCST_BF[u1_a_BFI].u1_sup;

    if((u1_a_BFI  < u1_g_MCST_NUM_BF) &&
       (u1_t_sup == (U1)TRUE        )){

        u1_t_wid  = st_gp_MCST_BF[u1_a_BFI].u1_wid;
        u1_t_lsb  = st_gp_MCST_BF[u1_a_BFI].u1_lsb;
        u4_t_bit  = st_gp_MCST_BF[u1_a_BFI].u4_bit;

        if(u1_s_mcst_user != (U1)MCST_USR_UNKNOWN){

            if(u1_t_wid >= (U1)MCST_NUM_WORD_COMMON){
                u1_t_wid  = u1_t_wid + st_gp_MCST_OFFSET[u1_s_mcst_user].u1_offset;
            }

            if(u1_t_wid < (U1)MCST_NUM_WORD){
                u4_t_mcst = (u4_gp_mcst_bfword[u1_t_wid] >> u1_t_lsb) & u4_t_bit;
            }
            else{
                u4_t_mcst = (U4)MCST_BF_UNK_U4;
            }
        }
        else {
            u4_t_mcst = (u4_gp_mcst_bfword_unk[u1_t_wid] >> u1_t_lsb) & u4_t_bit;
        }

    }
    else{
        u4_t_mcst = (U4)MCST_BF_UNK_U4;
    }

    if(u4_t_mcst == u4_t_bit){
        u4_t_mcst = u4_g_McstCfgInit(u1_a_BFI);
    }

    u4_t_mcst = u4_g_McstCfgU4ReplaceCustomize(u1_a_BFI, u4_t_mcst);

    return(u4_t_mcst);
}

/*===================================================================================================================================*/
/*  void    vd_g_McstBfPutU4(const U1 u1_a_BFI, const U4 u4_a_NEXT)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_McstBfPutU4(const U1 u1_a_BFI, const U4 u4_a_NEXT)
{
    U4                  u4_t_mask;
    U1                  u1_t_wid;
    U1                  u1_t_lsb;
    U4                  u4_t_bit;
    U4                  u4_t_las;
    U1                  u1_t_sup;
    U1                  u1_t_updt_byte;
    U1                  u1_t_updt_bit;

    u1_t_sup  = st_gp_MCST_BF[u1_a_BFI].u1_sup;

    if((u1_s_mcst_res_ctrl > (U1)MCST_RES_RUN) &&
       (u1_a_BFI           < u1_g_MCST_NUM_BF) &&
       (u1_t_sup          == (U1)TRUE        )){

        u1_t_wid = st_gp_MCST_BF[u1_a_BFI].u1_wid;
        u1_t_lsb = st_gp_MCST_BF[u1_a_BFI].u1_lsb;
        u4_t_bit = st_gp_MCST_BF[u1_a_BFI].u4_bit;

        if(u1_s_mcst_user != (U1)MCST_USR_UNKNOWN){

            if (u1_t_wid >= (U1)MCST_NUM_WORD_COMMON){
                u1_t_wid  = u1_t_wid + st_gp_MCST_OFFSET[u1_s_mcst_user].u1_offset;
            }

            if(u1_t_wid < (U1)MCST_NUM_WORD){
                u4_t_las = (u4_gp_mcst_bfword[u1_t_wid] >> u1_t_lsb) & u4_t_bit;
            }
            else{
                u4_t_las = (U4)MCST_BF_UNK_U4;
            }

            if((u4_a_NEXT <= u4_t_bit ) &&
               (u4_t_las  != u4_a_NEXT)){

                u4_t_mask                    = (U4)U4_MAX ^ (u4_t_bit << u1_t_lsb);
                u4_gp_mcst_bfword[u1_t_wid] &= u4_t_mask;
                u4_gp_mcst_bfword[u1_t_wid] |= (u4_a_NEXT << u1_t_lsb);

                u1_t_updt_byte                       = u1_t_wid / (U1)MCST_MEM_UPDT_SIZE;
                u1_t_updt_bit                        = u1_t_wid % (U1)MCST_MEM_UPDT_SIZE;
                u4_sp_mcst_mem_updt[u1_t_updt_byte] |= ((U4)0x00000001U << u1_t_updt_bit);
            }
        }
        else{
            u4_t_las = (u4_gp_mcst_bfword_unk[u1_t_wid] >> u1_t_lsb) & u4_t_bit;

            if((u4_a_NEXT <= u4_t_bit ) &&
               (u4_t_las  != u4_a_NEXT)){

                u4_t_mask                    = (U4)U4_MAX ^ (u4_t_bit << u1_t_lsb);
                u4_gp_mcst_bfword_unk[u1_t_wid] &= u4_t_mask;
                u4_gp_mcst_bfword_unk[u1_t_wid] |= (u4_a_NEXT << u1_t_lsb);

            }
        }
    }
}

/*===================================================================================================================================*/
/*  void    vd_g_McstBfPutPreUser(const U1 u1_a_BFI, const U4 u4_a_PRESET)                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_McstBfPutPreUser(const U1 u1_a_BFI, const U4 u4_a_PRESET)
{
    U4                  u4_t_mask;

    U1                  u1_t_wid;
    U1                  u1_t_lsb;
    U4                  u4_t_bit;
    U4                  u4_t_las;
    U1                  u1_t_wid_gst;
    U4                  u4_t_las_gst;
    U1                  u1_t_updt_byte;
    U1                  u1_t_updt_bit;

    if((u1_s_mcst_res_ctrl > (U1)MCST_RES_RUN) &&
       (u1_a_BFI           < u1_g_MCST_NUM_BF)){

        u1_t_wid     = st_gp_MCST_BF[u1_a_BFI].u1_wid;
        u1_t_lsb     = st_gp_MCST_BF[u1_a_BFI].u1_lsb;
        u4_t_bit     = st_gp_MCST_BF[u1_a_BFI].u4_bit;

        if(u1_t_wid >= (U1)MCST_NUM_WORD_COMMON){
            if(u1_s_mcst_user_pre != (U1)MCST_USR_UNKNOWN){

                u1_t_wid_gst  = u1_t_wid + st_gp_MCST_OFFSET[MCST_USR_GUEST].u1_offset;
                u1_t_wid      = u1_t_wid + st_gp_MCST_OFFSET[u1_s_mcst_user_pre].u1_offset;

                if(u1_t_wid < (U1)MCST_NUM_WORD){
                    u4_t_las     = (u4_gp_mcst_bfword[u1_t_wid]     >> u1_t_lsb) & u4_t_bit;
                }
                else{
                    u4_t_las     = (U4)MCST_BF_UNK_U4;
                }

                if(u1_t_wid_gst < (U1)MCST_NUM_WORD){
                    u4_t_las_gst = (u4_gp_mcst_bfword[u1_t_wid_gst] >> u1_t_lsb) & u4_t_bit;
                }
                else{
                    u4_t_las_gst = (U4)MCST_BF_UNK_U4;
                }

                if((u4_a_PRESET <= u4_t_bit    ) &&
                   (u4_t_las    != u4_a_PRESET)){

                    u4_t_mask                            = (U4)U4_MAX ^ (u4_t_bit << u1_t_lsb);
                    u4_gp_mcst_bfword[u1_t_wid]         &= u4_t_mask;
                    u4_gp_mcst_bfword[u1_t_wid]         |= (u4_a_PRESET << u1_t_lsb);

                    u1_t_updt_byte                       = u1_t_wid / (U1)MCST_MEM_UPDT_SIZE;
                    u1_t_updt_bit                        = u1_t_wid % (U1)MCST_MEM_UPDT_SIZE;
                    u4_sp_mcst_mem_updt[u1_t_updt_byte] |= ((U4)0x00000001U << u1_t_updt_bit);
                }

                if((u4_a_PRESET    <= u4_t_bit          ) &&
                   (u4_t_las_gst   != u4_a_PRESET       ) &&
                   (u1_s_mcst_user == (U1)MCST_USR_GUEST)){

                    u4_t_mask                       = (U4)U4_MAX ^ (u4_t_bit << u1_t_lsb);
                    u4_gp_mcst_bfword[u1_t_wid_gst] &= u4_t_mask;
                    u4_gp_mcst_bfword[u1_t_wid_gst] |= (u4_a_PRESET << u1_t_lsb);

                    u1_t_updt_byte                       = u1_t_wid_gst / (U1)MCST_MEM_UPDT_SIZE;
                    u1_t_updt_bit                        = u1_t_wid_gst % (U1)MCST_MEM_UPDT_SIZE;
                    u4_sp_mcst_mem_updt[u1_t_updt_byte] |= ((U4)0x00000001U << u1_t_updt_bit);
                }
            }
            else{
                u4_t_las = (u4_gp_mcst_bfword_unk[u1_t_wid] >> u1_t_lsb) & u4_t_bit;

                if((u4_a_PRESET <= u4_t_bit ) &&
                (u4_t_las    != u4_a_PRESET)){

                    u4_t_mask                    = (U4)U4_MAX ^ (u4_t_bit << u1_t_lsb);
                    u4_gp_mcst_bfword_unk[u1_t_wid] &= u4_t_mask;
                    u4_gp_mcst_bfword_unk[u1_t_wid] |= (u4_a_PRESET << u1_t_lsb);

                }
            }
        }
    }
}

/*===================================================================================================================================*/
/*  void    vd_g_McstNickNamePut(const U2 * u2_ap_nickname , const U1 u1_a_USRNUM)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_McstNickNamePut(const U2 * u2_ap_nickname , const U1 u1_a_USRNUM)
{
    U4  u4_t_loop;
    U2  u2_t_las;

    if((u1_a_USRNUM    != (U1)MCST_USR_GUEST) &&
       (u1_a_USRNUM     < u1_g_MCST_USR_NUM ) &&
       (u2_ap_nickname != vdp_PTR_NA       ))   {

        for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)u1_g_MCST_NICKNAME_NUM ; u4_t_loop++){
            u2_t_las = u2_gp_mcst_nickname[u1_a_USRNUM][u4_t_loop];

            if(u2_t_las != u2_ap_nickname[u4_t_loop]){
                u2_gp_mcst_nickname[u1_a_USRNUM][u4_t_loop] = u2_ap_nickname[u4_t_loop];
                u1_s_mcst_nickname_updt |= (U1)((U1)0x01U << u1_a_USRNUM);
            }
        }
    }
}

/*===================================================================================================================================*/
/*  U1      u1_g_McstReadNickName( U2 * u2_ap_nickname , const U1 u1_a_USRNUM)                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_McstReadNickName( U2 * u2_ap_nickname ,const U1 u1_a_USRNUM)
{
    U1  u1_t_result;
    U4  u4_t_loop;

    u1_t_result = (U1)MCST_INVALID;

    if((u1_a_USRNUM    != (U1)MCST_USR_GUEST) &&
       (u1_a_USRNUM     < u1_g_MCST_USR_NUM ) &&
       (u2_ap_nickname != vdp_PTR_NA       )){

        for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)u1_g_MCST_NICKNAME_NUM ; u4_t_loop++){
            u2_ap_nickname[u4_t_loop] = u2_gp_mcst_nickname[u1_a_USRNUM][u4_t_loop];
        }

        u1_t_result = (U1)MCST_VALID;
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  static void    vd_s_McstNickNameNvmcWrite(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void      vd_s_McstNickNameNvmcWrite(void)
{
    U2  u2_t_nvmcid;
    U2  u2_t_data;
    U4  u4_t_loopdat;
    U4  u4_t_loopusr;
    U1  u1_t_requsr;
    U1  u1_t_updt;

    u1_t_requsr = (U1)MCST_NICKNAME_UPDT_FLAG;

    for(u4_t_loopusr = (U4)MCST_USR_USER1 ; u4_t_loopusr < (U4)u1_g_MCST_USR_NUM ; u4_t_loopusr++){
        u1_t_updt     = u1_s_mcst_nickname_updt & u1_t_requsr;
        if(u1_t_updt != (U1)0U){
            for(u4_t_loopdat = (U4)0U ; u4_t_loopdat < (U4)u1_g_MCST_NICKNAME_NUM ; u4_t_loopdat++){
                u2_t_nvmcid = u2_gp2_MCST_NICKNAME_NVMCID[u4_t_loopusr][u4_t_loopdat];
                u2_t_data   = u2_gp_mcst_nickname[u4_t_loopusr][u4_t_loopdat];
                vd_g_Nvmc_WriteU2(u2_t_nvmcid, u2_t_data);
            }
        }

        u1_t_requsr <<= (U1)1U;
    }
}

/*===================================================================================================================================*/
/*  static void    vd_s_McstNickNameDel(const U1 u1_a_USRNUM)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void      vd_s_McstNickNameDel(const U1 u1_a_USRNUM)
{
    U4  u4_t_loopdat;


    if((u1_a_USRNUM != (U1)MCST_USR_GUEST) &&
       (u1_a_USRNUM  < u1_g_MCST_USR_NUM )){
        for(u4_t_loopdat = (U4)0U ; u4_t_loopdat < (U4)u1_g_MCST_NICKNAME_NUM ; u4_t_loopdat++){

        u2_gp_mcst_nickname[u1_a_USRNUM][u4_t_loopdat] = (U2)0U;

        }
    }
    u1_s_mcst_nickname_updt |= (U1)((U1)0x01U << u1_a_USRNUM);

    vd_g_McstCfgNickNameInitHook(u1_a_USRNUM);
}

/*===================================================================================================================================*/
/*  static void    vd_s_McstSR_DNAMEDel(const U1 u1_a_USRNUM)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void      vd_s_McstSR_DNAMEDel(const U1 u1_a_USRNUM)
{
    switch (u1_a_USRNUM){
        case (U1)MCST_USR_USER1:
            vd_g_McstBfPut(u1_g_MCST_BFI_NAME_DRV1,(U1)0U);
            break;
        case (U1)MCST_USR_USER2:
            vd_g_McstBfPut(u1_g_MCST_BFI_NAME_DRV2,(U1)0U);
            break;
        case (U1)MCST_USR_USER3:
            vd_g_McstBfPut(u1_g_MCST_BFI_NAME_DRV3,(U1)0U);
            break;
        default:
            /* Do Nothing */
            break;
    }
}

/*===================================================================================================================================*/
/*  U1      u1_g_McstDiag(const U1 u1_a_ITEM)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_McstDiag(const U1 u1_a_ITEM)
{
    U1  u1_t_diag_prm;

    u1_t_diag_prm = (U1)MCST_DIAG_UNK;

    if(u1_a_ITEM < (U1)MCST_DIAG_NUM){
        u1_t_diag_prm = (fp_gp_u1_MCST_GETDIAG[u1_a_ITEM])();
    }

    return(u1_t_diag_prm);
}

/*===================================================================================================================================*/
/*  static U1 u1_s_McstCmp(U4 *u4_ap_rdata)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1 u1_s_McstCmpInit(U4 *u4_ap_rdata)
{
    U1    u1_t_loop;
    U1    u1_t_sts;
    u1_t_sts = (U1)TRUE;
    for(u1_t_loop =(U1)0U; u1_t_loop < (U1)MCST_NUM_4BYTE; u1_t_loop++){
        if(u4_ap_rdata[u1_t_loop] != (U4)MCST_BF_INI){
            u1_t_sts = (U1)FALSE;
        }
    }
    
    return(u1_t_sts);
}

/*===================================================================================================================================*/
/*  static U1 u1_s_Mcst_DtfCmnInit(U2 u2_a_nvmid);                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1 u1_s_McstDtfCmnInit(const U2 u2_a_nvmid)
{
    U1                  u1_t_nvm_chk;
    U1                  u1_t_res_chk;
    U1                  u1_t_loop;
    U4                  u4_tp_rdata[MCST_NUM_4BYTE];
    U4                  u4_tp_wdata[MCST_NUM_4BYTE];
    U1                  u1_t_cmp_chk;

    u1_t_res_chk = (U1)MCST_RES_SUC;
    u1_t_cmp_chk = (U1)TRUE;
    vd_g_MemfillU4(&u4_tp_rdata[0], (U4)MCST_BF_INI, (U4)MCST_NUM_4BYTE);
    u1_t_nvm_chk  = u1_g_Nvmc_ReadOthrwithSts(u2_a_nvmid, (U2)MCST_NVM_SIZE, (U1 *)&u4_tp_rdata[0]);
    for(u1_t_loop = (U1)0U; u1_t_loop < (U1)MCST_CMNINIT_SIZE; u1_t_loop++){
        u4_tp_wdata[u1_t_loop] = (U4)MCST_BF_INI;
        if(u4_tp_rdata[u1_t_loop] != (U4)MCST_BF_INI){
            u1_t_cmp_chk = (U1)FALSE;
        }
    }
    if((u1_t_cmp_chk  == (U1)FALSE ) ||
       (u1_t_nvm_chk  >= (U1)NVMC_STATUS_KIND_NG ) ||
       (u1_t_nvm_chk  == (U1)NVMC_STATUS_ERRCOMP ) ||
       (u1_t_nvm_chk  == (U1)NVMC_STATUS_CACHE_NG)){
        u4_tp_wdata[MCST_CMNINIT_SIZE] = u4_gp_mcst_bfword[MCST_CMNINIT_SIZE];
        vd_g_Nvmc_ClearShtdwnTimer();
        vd_g_Nvmc_WriteOthr(u2_a_nvmid, (U2)MCST_NVM_SIZE, (U1 *)&u4_tp_wdata[0]);
        u1_t_res_chk = (U1)MCST_RES_RUN;
    }
    else if(u1_t_nvm_chk == (U1)NVMC_STATUS_WRITING){
        u1_t_res_chk = (U1)MCST_RES_RUN;
    }
    else{
        /* Do Nothing */
    }
    return(u1_t_res_chk);
}

/*===================================================================================================================================*/
/*  static U1 u1_s_Mcst_DtfUsrInit(U2 u2_a_nvmid);                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1 u1_s_McstDtfUsrInit(const U2 u2_a_nvmid)
{
    U1                  u1_t_nvm_chk;
    U1                  u1_t_res_chk;
    U4                  u4_tp_rdata[MCST_NUM_4BYTE];
    U4                  u4_tp_wdata[MCST_NUM_4BYTE];
    U1                  u1_t_cmp_chk;

    u1_t_res_chk = (U1)MCST_RES_SUC;
    u1_t_cmp_chk = (U1)TRUE;
    vd_g_MemfillU4(&u4_tp_rdata[0], (U4)MCST_BF_INI, (U4)MCST_NUM_4BYTE);
    vd_g_MemfillU4(&u4_tp_wdata[0], (U4)MCST_BF_INI, (U4)MCST_NUM_4BYTE);
    u1_t_nvm_chk  = u1_g_Nvmc_ReadOthrwithSts(u2_a_nvmid, (U2)MCST_NVM_SIZE, (U1 *)&u4_tp_rdata[0]);
    u1_t_cmp_chk = u1_s_McstCmpInit(&u4_tp_rdata[0]);
    if((u1_t_cmp_chk  == (U1)FALSE ) ||
       (u1_t_nvm_chk  >= (U1)NVMC_STATUS_KIND_NG ) ||
       (u1_t_nvm_chk  == (U1)NVMC_STATUS_ERRCOMP ) ||
       (u1_t_nvm_chk  == (U1)NVMC_STATUS_CACHE_NG)){

         vd_g_Nvmc_ClearShtdwnTimer();
         vd_g_Nvmc_WriteOthr(u2_a_nvmid, (U2)MCST_NVM_SIZE, (U1 *)&u4_tp_wdata[0]);
         u1_t_res_chk = (U1)MCST_RES_RUN;
    }
    else if(u1_t_nvm_chk == (U1)NVMC_STATUS_WRITING){
        u1_t_res_chk = (U1)MCST_RES_RUN;
    }
    else{
        /* Do Nothing */
    }
    return(u1_t_res_chk);
}

/*===================================================================================================================================*/
/*  void        vd_g_McstBfAll(U4 * u4_ap_bf)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void        vd_g_McstSetAllBf(U4 * u4_ap_bf)
{
    if(u4_ap_bf != vdp_PTR_NA){
        vd_g_MemcpyU4(&u4_ap_bf[0], &u4_sp_mcst_note_bfword[0], (U4)MCST_NUM_WORD_USER);
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
/*  1.0.0    11/30/2018  TA       New.                                                                                               */
/*  1.1.0     3/10/2020  TN       Re-designed.                                                                                       */
/*  2.0.0     9/22/2020  TM       Personalized customization support.                                                                */
/*  2.1.0     1/13/2021  TM       Add previous user customized memory, Customizations to U4 for offset time                          */
/*  2.1.1     4/ 9/2021  TM       Solving the issues of MET032D -2619, MET032D -2620                                                 */
/*  2.1.2     8/ 2/2021  SI       Solving the issues of MET032D-2764, 24FGM22-2704                                                   */
/*  2.1.3     8/ 2/2021  SI       Solving the issues of MET032D-5418                                                                 */
/*  2.1.4    12/27/2021  SI       Solving the issues of 24FGM22-9076                                                                 */
/*  2.2.0    02/06/2022  SI       Add Conversion IF for Diagnostics.                                                                 */
/*  2.3.0    09/04/2022  SI       Extend u4_gp_mcst_bfword                                                                           */
/*  2.4.0    09/23/2022  TX       Add Output of NVM Error Status                                                                     */
/*  2.3.0    05/14/2024  SK       Change Custmize DTF read/write process                                                             */
/*  2.4.0    06/21/2024  SW       Add switching process for Left content Fuel Economy                                                */
/*                                                                                                                                   */
/*  * TA   = Teruyuki Anjima, Denso                                                                                                  */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*  * TM   = Takuya Mitsui, Denso Techno                                                                                             */
/*  * SI   = Shugo Ichinose, Denso Techno                                                                                            */
/*  * TX   = Tong Xinyuan, DNST                                                                                                      */
/*  * SK   = Shintaro Kano, DENSO TECHNO                                                                                             */
/*  * SW   = Shun Watanabe,   Denso Techno                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/
