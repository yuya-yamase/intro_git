/* 1.4.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Dimmer User Adjusement by Hardware Switch                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define DIM_USADJ_BY_SW_C_MAJOR                  (1)
#define DIM_USADJ_BY_SW_C_MINOR                  (4)
#define DIM_USADJ_BY_SW_C_PATCH                  (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "dim_usadjbysw_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((DIM_USADJ_BY_SW_C_MAJOR != DIM_USADJ_BY_SW_H_MAJOR) || \
     (DIM_USADJ_BY_SW_C_MINOR != DIM_USADJ_BY_SW_H_MINOR) || \
     (DIM_USADJ_BY_SW_C_PATCH != DIM_USADJ_BY_SW_H_PATCH))
#error "dim_swadjst.c and dim_swadjst.h : source and header files are inconsistent!"
#endif

#if ((DIM_USADJ_BY_SW_C_MAJOR != DIM_USADJ_BY_SW_CFG_H_MAJOR) || \
     (DIM_USADJ_BY_SW_C_MINOR != DIM_USADJ_BY_SW_CFG_H_MINOR) || \
     (DIM_USADJ_BY_SW_C_PATCH != DIM_USADJ_BY_SW_CFG_H_PATCH))
#error "dim_swadjst.c and dim_swadjst_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define DIM_USADJ_BY_SW_NUM_SWCHK                (3U)
#define DIM_USADJ_BY_SW_SWCHK_NO_PRS             (0U)  /* Nothing is pressed.     */
#define DIM_USADJ_BY_SW_SWCHK_UP_PRS             (1U)  /* Up button is pressed.   */
#define DIM_USADJ_BY_SW_SWCHK_DW_PRS             (2U)  /* Down button is pressed. */

#define DIM_USADJ_BY_SW_STSCHK_DW_ON             (DIM_USADJ_BY_SW_SWON_BIT_DW)
#define DIM_USADJ_BY_SW_STSCHK_UP_ON             (DIM_USADJ_BY_SW_SWON_BIT_UP)
#define DIM_USADJ_BY_SW_STSCHK_LP_ACT            (0x04U)
#define DIM_USADJ_BY_SW_STSCHK_LP_UPDT           (0x08U)

#define DIM_USADJ_BY_SW_ACT_BIT_NEXT             (0x03U)
#define DIM_USADJ_BY_SW_ACT_BIT_TM_UPDT          (0x0cU)
#define DIM_USADJ_BY_SW_ACT_LSB_TM_UPDT          (2U)
#define DIM_USADJ_BY_SW_NUM_TM_UPDT              (2U)
#define DIM_USADJ_BY_SW_TM_UPDT_RESTART          (0U)
#define DIM_USADJ_BY_SW_TM_UPDT_LPSTART          (1U)

#define DIM_USADJ_BY_SW_ACT_BIT_LVL_UPDT         (0x30U)
#define DIM_USADJ_BY_SW_ACT_LSB_LVL_UPDT         (4U)
#define DIM_USADJ_BY_SW_LVL_UPDT_UP              (0U)
#define DIM_USADJ_BY_SW_LVL_UPDT_DWN             (1U)
#define DIM_USADJ_BY_SW_LVL_UPDT_NOP             (2U)

#define DIM_USADJ_BY_SW_ACT_TO_NO                (0x20U)
#define DIM_USADJ_BY_SW_ACT_TO_NO_INC            (0x00U)
#define DIM_USADJ_BY_SW_ACT_TO_NO_DEC            (0x10U)
#define DIM_USADJ_BY_SW_ACT_TO_UP                (0x21U)
#define DIM_USADJ_BY_SW_ACT_TO_UP_DEC            (0x11U)
#define DIM_USADJ_BY_SW_ACT_UP                   (0x29U)
#define DIM_USADJ_BY_SW_ACT_UP_INC               (0x05U)
#define DIM_USADJ_BY_SW_ACT_TO_DW                (0x22U)
#define DIM_USADJ_BY_SW_ACT_TO_DW_INC            (0x02U)
#define DIM_USADJ_BY_SW_ACT_DW                   (0x2AU)
#define DIM_USADJ_BY_SW_ACT_DW_DEC               (0x16U)

#define DIM_USADJ_VR_AVE_INIT_NUM                (4U)
#define DIM_USADJ_VR_AVE_NML_NUM                 (4U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct {
    U2   u2_vrad_down;
    U2   u2_vrad_up;
}ST_DIM_VRADHYS;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U2         u2_s_dim_usadjbysw_nvm_updt;
static U2         u2_s_dim_usadjbysw_tmelpsd;
static U1         u1_s_dim_usadjbysw_swchk;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static        U1      u1_s_DimUsadjbySwTailOn(const U1 u1_a_IGN_ON);
static        U1      u1_s_DimUsadjbySwUpdwnchk(const U1 u1_a_ADJBL);
static        void    vd_s_DimUsadjbySwLvlUp(const U1 u1_a_TAIL_ON, const U1 u1_a_DAYNIGHT, U2 * u2_ap_lvl);
static        void    vd_s_DimUsadjbySwLvlDwn(const U1 u1_a_TAIL_ON, const U1 u1_a_DAYNIGHT, U2 * u2_ap_lvl);
static        void    vd_s_DimUsadjbySwVrchk(const U1 u1_a_ADJBL, const U1 u1_a_TAIL_ON, const U1 u1_a_DAYNIGHT, U2 * u2_ap_lvl);
static        U2      u2_s_DimUsadjbySwVrHysManualLv(const U2 u2_a_AD, const U2 u2_a_OLDSTEP);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_DimUsadjbySwInit(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_DimUsadjbySwInit(void)
{
    u2_s_dim_usadjbysw_nvm_updt = (U2)U2_MAX;

    u2_s_dim_usadjbysw_tmelpsd  = (U2)U2_MAX;
    u1_s_dim_usadjbysw_swchk    = (U1)DIM_USADJ_BY_SW_SWCHK_NO_PRS;

}
/*===================================================================================================================================*/
/*  void    vd_g_DimUsadjbySwUpdt(const U1 u1_a_DAYNIGHT, U2 * u2_ap_lvl)                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_DimUsadjbySwUpdt(const U1 u1_a_DAYNIGHT, U2 * u2_ap_lvl)
{
    U1                       u1_t_lvl_updt;
    U1                       u1_t_igon;
    U1                       u1_t_tail_on;
    U1                       u1_t_adjbl;
    U1                       u1_t_rheosw;

    u1_t_rheosw = u1_DIM_USADJ_BY_SW_CALIB_RHEOSW;

    if(u2_ap_lvl != vdp_PTR_NA){

        if(u2_s_dim_usadjbysw_nvm_updt < (U2)U2_MAX){
            u2_s_dim_usadjbysw_nvm_updt++;
        }

        u1_t_igon     = u1_g_DimUsadjbySwCfgIgnOn();
        u1_t_tail_on  = u1_s_DimUsadjbySwTailOn(u1_t_igon);
        if(u1_a_DAYNIGHT < (U1)DIM_DAYNIGHT_NUM_LVL){
            u1_t_adjbl = (u1_g_DimUsadjbySwCfgAdjstbl() & (U1)TRUE) | u1_t_igon;
            if(u1_t_tail_on == (U1)DIM_USADJ_BY_SW_TAIL_ON){
                u1_t_adjbl |= (U1)TRUE;
            }
        }
        else{
            u1_t_adjbl = (U1)FALSE;
        }
        if(u1_t_rheosw != (U1)CALIB_MCUID0430_THUMB_WHEEL){
            if((u2_ap_lvl[DIM_DAYNIGHT_LVL_DAY]   > (U2)DIM_USADJ_BY_SW_LVL_MAX) ||
               (u2_ap_lvl[DIM_DAYNIGHT_LVL_NIGHT] > (U2)DIM_USADJ_BY_SW_LVL_MAX)){

                vd_g_DimUsadjbySwCfgNvmRead(u2_ap_lvl);
            }
            u1_t_lvl_updt = u1_s_DimUsadjbySwUpdwnchk(u1_t_adjbl);
            if(u1_t_lvl_updt == (U1)DIM_USADJ_BY_SW_LVL_UPDT_UP){
                vd_s_DimUsadjbySwLvlUp(u1_t_tail_on, u1_a_DAYNIGHT, u2_ap_lvl);
            }
            else if(u1_t_lvl_updt == (U1)DIM_USADJ_BY_SW_LVL_UPDT_DWN){
                vd_s_DimUsadjbySwLvlDwn(u1_t_tail_on, u1_a_DAYNIGHT, u2_ap_lvl);
            }
            else{
                /* Do nothing */
            }
        }
        else{
            vd_s_DimUsadjbySwVrchk(u1_t_adjbl, u1_t_tail_on, u1_a_DAYNIGHT, u2_ap_lvl);
        }

        if(u2_s_dim_usadjbysw_nvm_updt == u2_g_DIM_USADJ_BY_SW_NVM_UPDT){
            vd_g_DimUsadjbySwCfgNvmWrite(u2_ap_lvl);
        }
    }
    else{
        vd_g_DimUsadjbySwInit();
    }
}
/*===================================================================================================================================*/
/*  static U1      u1_s_DimUsadjbySwUpdwnchk(const U1 u1_a_ADJBL)                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_DimUsadjbySwUpdwnchk(const U1 u1_a_ADJBL)
{
    static const U1          u1_sp_DIM_USADJ_BY_SW_ACT[] = {
        (U1)DIM_USADJ_BY_SW_ACT_TO_NO, (U1)DIM_USADJ_BY_SW_ACT_TO_NO_INC, (U1)DIM_USADJ_BY_SW_ACT_TO_NO_DEC,
        (U1)DIM_USADJ_BY_SW_ACT_TO_DW, (U1)DIM_USADJ_BY_SW_ACT_TO_DW_INC, (U1)DIM_USADJ_BY_SW_ACT_DW,
        (U1)DIM_USADJ_BY_SW_ACT_TO_UP, (U1)DIM_USADJ_BY_SW_ACT_UP,        (U1)DIM_USADJ_BY_SW_ACT_TO_UP_DEC,
        (U1)DIM_USADJ_BY_SW_ACT_TO_NO, (U1)DIM_USADJ_BY_SW_ACT_TO_NO,     (U1)DIM_USADJ_BY_SW_ACT_TO_NO,
        (U1)DIM_USADJ_BY_SW_ACT_TO_NO, (U1)DIM_USADJ_BY_SW_ACT_TO_NO,     (U1)DIM_USADJ_BY_SW_ACT_TO_NO,
        (U1)DIM_USADJ_BY_SW_ACT_TO_DW, (U1)DIM_USADJ_BY_SW_ACT_TO_DW,     (U1)DIM_USADJ_BY_SW_ACT_DW,
        (U1)DIM_USADJ_BY_SW_ACT_TO_UP, (U1)DIM_USADJ_BY_SW_ACT_UP,        (U1)DIM_USADJ_BY_SW_ACT_TO_UP,
        (U1)DIM_USADJ_BY_SW_ACT_TO_NO, (U1)DIM_USADJ_BY_SW_ACT_TO_NO,     (U1)DIM_USADJ_BY_SW_ACT_TO_NO,
        (U1)DIM_USADJ_BY_SW_ACT_TO_NO, (U1)DIM_USADJ_BY_SW_ACT_TO_NO_INC, (U1)DIM_USADJ_BY_SW_ACT_TO_NO_DEC,
        (U1)DIM_USADJ_BY_SW_ACT_TO_DW, (U1)DIM_USADJ_BY_SW_ACT_TO_DW_INC, (U1)DIM_USADJ_BY_SW_ACT_DW,
        (U1)DIM_USADJ_BY_SW_ACT_TO_UP, (U1)DIM_USADJ_BY_SW_ACT_UP,        (U1)DIM_USADJ_BY_SW_ACT_TO_UP_DEC,
        (U1)DIM_USADJ_BY_SW_ACT_TO_NO, (U1)DIM_USADJ_BY_SW_ACT_TO_NO,     (U1)DIM_USADJ_BY_SW_ACT_TO_NO,
        (U1)DIM_USADJ_BY_SW_ACT_TO_NO, (U1)DIM_USADJ_BY_SW_ACT_TO_NO,     (U1)DIM_USADJ_BY_SW_ACT_TO_NO,
        (U1)DIM_USADJ_BY_SW_ACT_TO_DW, (U1)DIM_USADJ_BY_SW_ACT_TO_DW,     (U1)DIM_USADJ_BY_SW_ACT_DW_DEC,
        (U1)DIM_USADJ_BY_SW_ACT_TO_UP, (U1)DIM_USADJ_BY_SW_ACT_UP_INC,    (U1)DIM_USADJ_BY_SW_ACT_TO_UP,
        (U1)DIM_USADJ_BY_SW_ACT_TO_NO, (U1)DIM_USADJ_BY_SW_ACT_TO_NO,     (U1)DIM_USADJ_BY_SW_ACT_TO_NO
    };

    U2                       u2_t_idx;

    U1                       u1_t_stschk;
    U1                       u1_t_act;
    U1                       u1_t_tm_updt;
    U1                       u1_t_lvl_updt;

    u1_t_stschk = u1_g_DimUsadjbySwCfgUpdwchk() & ((U1)DIM_USADJ_BY_SW_STSCHK_UP_ON | (U1)DIM_USADJ_BY_SW_STSCHK_DW_ON);

    if(u2_s_dim_usadjbysw_tmelpsd < (U2)U2_MAX){
        u2_s_dim_usadjbysw_tmelpsd++;
    }

    if(u2_s_dim_usadjbysw_tmelpsd >= u2_g_DIM_USADJ_BY_SW_LP_UPDT){
        u1_t_stschk |= ((U1)DIM_USADJ_BY_SW_STSCHK_LP_ACT | (U1)DIM_USADJ_BY_SW_STSCHK_LP_UPDT);
    }
    else if(u2_s_dim_usadjbysw_tmelpsd >= u2_g_DIM_USADJ_BY_SW_LP_ACT){
        u1_t_stschk |= (U1)DIM_USADJ_BY_SW_STSCHK_LP_ACT;
    }
    else{
        /* Do nothing */
    }

    if((u1_a_ADJBL               == (U1)TRUE                     ) &&
       (u1_s_dim_usadjbysw_swchk <  (U1)DIM_USADJ_BY_SW_NUM_SWCHK)){
        u2_t_idx = ((U2)u1_t_stschk * (U2)DIM_USADJ_BY_SW_NUM_SWCHK) + (U2)u1_s_dim_usadjbysw_swchk;
        u1_t_act = u1_sp_DIM_USADJ_BY_SW_ACT[u2_t_idx];
    }
    else{
        u1_t_act = (U1)DIM_USADJ_BY_SW_ACT_TO_NO;
    }
    u1_s_dim_usadjbysw_swchk = u1_t_act & (U1)DIM_USADJ_BY_SW_ACT_BIT_NEXT;

    u1_t_tm_updt = (u1_t_act & (U1)DIM_USADJ_BY_SW_ACT_BIT_TM_UPDT) >> DIM_USADJ_BY_SW_ACT_LSB_TM_UPDT;
    if(u1_t_tm_updt == (U1)DIM_USADJ_BY_SW_TM_UPDT_RESTART){
        u2_s_dim_usadjbysw_tmelpsd = (U2)0U;
    }
    else if(u1_t_tm_updt == (U1)DIM_USADJ_BY_SW_TM_UPDT_LPSTART){
        u2_s_dim_usadjbysw_tmelpsd = u2_g_DIM_USADJ_BY_SW_LP_ACT;
    }
    else{
        /* Do nothing */
    }
    u1_t_lvl_updt = (u1_t_act & (U1)DIM_USADJ_BY_SW_ACT_BIT_LVL_UPDT) >> DIM_USADJ_BY_SW_ACT_LSB_LVL_UPDT;

    return(u1_t_lvl_updt);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_DimUsadjbySwTailOn(const U1 u1_a_IGN_ON)                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_DimUsadjbySwTailOn(const U1 u1_a_IGN_ON)
{
    U1                       u1_t_tail;
    U1                       u1_t_rxchk;

    u1_t_tail  = (U1)DIM_USADJ_BY_SW_TAIL_OFF;
    u1_t_rxchk = u1_g_DimUsadjbySwCfgComRxTAIL(&u1_t_tail);
    if((u1_t_rxchk  != (U1)DIM_USADJ_BY_SW_COM_RX_VALID) &&
       (u1_a_IGN_ON != (U1)TRUE                        )){
        u1_t_tail = (U1)DIM_USADJ_BY_SW_TAIL_OFF;
    }

    return(u1_t_tail);
}
/*===================================================================================================================================*/
/*  static void    vd_s_DimUsadjbySwLvlUp(const U1 u1_a_TAIL_ON, const U1 u1_a_DAYNIGHT, U2 * u2_ap_lvl)                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_DimUsadjbySwLvlUp(const U1 u1_a_TAIL_ON, const U1 u1_a_DAYNIGHT, U2 * u2_ap_lvl)
{
    if(u2_ap_lvl[u1_a_DAYNIGHT] < (U2)DIM_USADJ_BY_SW_LVL_MAX){
        u2_ap_lvl[u1_a_DAYNIGHT]++;
        u2_s_dim_usadjbysw_nvm_updt = (U2)0U;
    }
    if((u1_a_TAIL_ON                      == (U1)DIM_USADJ_BY_SW_TAIL_ON) &&
       (u1_a_DAYNIGHT                     == (U1)DIM_DAYNIGHT_LVL_DAY   ) &&
       (u2_ap_lvl[DIM_DAYNIGHT_LVL_NIGHT] <  (U2)DIM_USADJ_BY_SW_LVL_MAX)){
        u2_ap_lvl[DIM_DAYNIGHT_LVL_NIGHT]++;
        u2_s_dim_usadjbysw_nvm_updt = (U2)0U;
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_DimUsadjbySwLvlDwn(const U1 u1_a_TAIL_ON, const U1 u1_a_DAYNIGHT, U2 * u2_ap_lvl)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_DimUsadjbySwLvlDwn(const U1 u1_a_TAIL_ON, const U1 u1_a_DAYNIGHT, U2 * u2_ap_lvl)
{
    if(u2_ap_lvl[u1_a_DAYNIGHT] > (U2)0U){
        u2_ap_lvl[u1_a_DAYNIGHT]--;
        u2_s_dim_usadjbysw_nvm_updt = (U2)0U;
    }
    if((u1_a_TAIL_ON                      == (U1)DIM_USADJ_BY_SW_TAIL_ON) &&
       (u1_a_DAYNIGHT                     == (U1)DIM_DAYNIGHT_LVL_DAY   ) &&
       (u2_ap_lvl[DIM_DAYNIGHT_LVL_NIGHT] >  (U2)0U                     )){
        u2_ap_lvl[DIM_DAYNIGHT_LVL_NIGHT]--;
        u2_s_dim_usadjbysw_nvm_updt = (U2)0U;
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_DimUsadjbySwVrchk(const U1 u1_a_ADJBL, const U1 u1_a_TAIL_ON, const U1 u1_a_DAYNIGHT, U2 * u2_ap_lvl)        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_DimUsadjbySwVrchk(const U1 u1_a_ADJBL, const U1 u1_a_TAIL_ON, const U1 u1_a_DAYNIGHT, U2 * u2_ap_lvl)
{
    U1                       u1_t_sts;
    U2                       u2_t_ad;

    u2_t_ad = (U2)0U;
    u1_t_sts = u1_g_DimUsadjbySwVrCfgReAd(&u2_t_ad);
    if(u1_t_sts == (U1)TRUE){
        if(u1_a_ADJBL == (U1)TRUE){
            u2_ap_lvl[u1_a_DAYNIGHT] = u2_s_DimUsadjbySwVrHysManualLv(u2_t_ad, u2_ap_lvl[u1_a_DAYNIGHT]);
            if((u1_a_TAIL_ON  == (U1)DIM_USADJ_BY_SW_TAIL_ON)
            && (u1_a_DAYNIGHT == (U1)DIM_DAYNIGHT_LVL_DAY   )){
                u2_ap_lvl[DIM_DAYNIGHT_LVL_NIGHT] = u2_s_DimUsadjbySwVrHysManualLv(u2_t_ad, u2_ap_lvl[DIM_DAYNIGHT_LVL_NIGHT]);
            }
        }
    }
    else{
        u2_s_dim_usadjbysw_nvm_updt = (U2)U2_MAX;
        u2_ap_lvl[DIM_DAYNIGHT_LVL_DAY]   = (U2)DIM_LVL_UNKNWN; 
        u2_ap_lvl[DIM_DAYNIGHT_LVL_NIGHT] = (U2)DIM_LVL_UNKNWN; 
    }
}
/*===================================================================================================================================*/
/*  static U2  u2_s_DimUsadjbySwVrHysManualLv(const U2 u2_a_AD, const U2 u2_a_OLDSTEP)                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   : --> u2_a_lv_new       : Manual Level(VR)(new data)                                                                 */
/*  Return      :     u2_t_lv           : decision value                                                                             */
/*===================================================================================================================================*/
static U2  u2_s_DimUsadjbySwVrHysManualLv(const U2 u2_a_AD, const U2 u2_a_OLDSTEP)
{
    static const ST_DIM_VRADHYS st_sp_DIM_USADJ_BY_SW_VRSTEP[DIM_USADJ_BY_SW_NUM_LVL] = {
        {(U2)10U,   (U2)10U   },
        {(U2)29U,   (U2)70U   },
        {(U2)76U,   (U2)117U  },
        {(U2)125U,  (U2)166U  },
        {(U2)172U,  (U2)213U  },
        {(U2)219U,  (U2)260U  },
        {(U2)266U,  (U2)307U  },
        {(U2)313U,  (U2)354U  },
        {(U2)360U,  (U2)401U  },
        {(U2)407U,  (U2)448U  },
        {(U2)456U,  (U2)497U  },
        {(U2)503U,  (U2)544U  },
        {(U2)550U,  (U2)591U  },
        {(U2)597U,  (U2)638U  },
        {(U2)644U,  (U2)685U  },
        {(U2)692U,  (U2)732U  },
        {(U2)739U,  (U2)780U  },
        {(U2)786U,  (U2)827U  },
        {(U2)835U,  (U2)876U  },
        {(U2)882U,  (U2)923U  },
        {(U2)929U,  (U2)970U  },
        {(U2)996U,  (U2)996U  }
    };
    U2  u2_t_newstep;
    U1  u1_t_fixed;

    if(u2_a_OLDSTEP < (U2)DIM_USADJ_BY_SW_NUM_LVL){
        u2_t_newstep = u2_a_OLDSTEP;
    }
    else{
        u2_t_newstep = (U2)0U;
    }
    u1_t_fixed = (U1)FALSE;
    while((u1_t_fixed == (U1)FALSE) && (u2_t_newstep < ((U2)DIM_USADJ_BY_SW_NUM_LVL - (U2)1U))){
        if(u2_a_AD >= st_sp_DIM_USADJ_BY_SW_VRSTEP[u2_t_newstep + (U2)1U].u2_vrad_up){
            u2_t_newstep++;
        }
        else{
            u1_t_fixed = (U1)TRUE;
        }
    }
    u1_t_fixed = (U1)FALSE;
    while((u1_t_fixed == (U1)FALSE) && (u2_t_newstep > (U2)0U)){
        if(u2_a_AD <= st_sp_DIM_USADJ_BY_SW_VRSTEP[u2_t_newstep - (U2)1U].u2_vrad_down){
            u2_t_newstep--;
        }
        else{
            u1_t_fixed = (U1)TRUE;
        }
    }
    if(u2_t_newstep != u2_a_OLDSTEP){
        u2_s_dim_usadjbysw_nvm_updt = (U2)0U;
    }

    return(u2_t_newstep);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     3/19/2018  TN       New.                                                                                               */
/*  1.1.0    10/11/2018  TN       u1_s_DimUsadjbySwTailOn was implemented.                                                           */
/*  1.2.0     2/22/2019  TN       User configuration IF name was modified.                                                           */
/*  1.3.0     3/26/2019  TN       NULL check was implemented into vd_g_DimUsadjbySwUpdt.                                             */
/*  1.3.1     1/26/2021  KM       Fixed QAC warning.(No.2013 No Comments in Else Case)                                               */
/*  1.4.0     2/15/2024  TH       for 19PFv3                                                                                         */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  19PFv3-1  4/12/2024  SH       Add calibration guard                                                                              */
/*  19PFv3-2  6/27/2024  TN(DT)   Delete Calibration Guard Process.                                                                  */
/*                                                                                                                                   */
/*  * TN     = Takashi Nagai, DENSO                                                                                                  */
/*  * KM     = Kota Matoba                                                                                                           */
/*  * TH     = Taisuke Hirakawa, KSE                                                                                                 */
/*  * SH     = Sae Hirose, Denso Techno                                                                                              */
/*  * TN(DT) = Tetsushi Nakano, Denso Techno                                                                                         */
/*                                                                                                                                   */
/*===================================================================================================================================*/
