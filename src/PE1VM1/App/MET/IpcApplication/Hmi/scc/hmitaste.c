/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  HmiTaste                                                                                                                         */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define HMITASTE_C_MAJOR                         (1)
#define HMITASTE_C_MINOR                         (0)
#define HMITASTE_C_PATCH                         (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "hmiproxy_cfg_private.h"

#include "hmitaste.h"
#include "mmtexttx.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((HMITASTE_C_MAJOR != HMITASTE_H_MAJOR) || \
     (HMITASTE_C_MINOR != HMITASTE_H_MINOR) || \
     (HMITASTE_C_PATCH != HMITASTE_H_PATCH))
#error "hmitaste.c and hmitaste.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define HMI_TASTE_CHGNUM             (1U)
#define HMI_TASTE_NUM                (6U)
#define HMI_TASTE_BUFNUM             (15U)

#define HMI_TASTE_TXT_MAX            (30U)

#define HMI_TASTE_CHGNUM_INIT        (0xFU)
#define HMI_TASTE_TXT_INIT           (0xFFFFU)

#define HMI_TASTE_TXT_NG             (1U)
#define HMI_TASTE_TXT_OK             (0U)

#define HMI_TASTE_CAL_ONE            (1U)
#define HMI_TASTE_CAL_TWO            (2U)
#define HMI_TASTE_TXT_MASK           (0xFFFFU)
#define HMI_TASTE_TXT_LSB            (16U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1   u1_s_hmitaste_chgnum;
static U2   u2_s_hmitaste_to;
static U1   u1_s_hmitaste_chgnum_pre;

static ST_MMTEXTTX_TASTE_TXTDATA st_sp_hmitaste;
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void    vd_s_HmiTaste(void);
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_HmiTasteInit(void)                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiTasteInit(void)
{
    U4 u4_t_loop_txt;

    u2_s_hmitaste_to = (U2)HMIPROXY_TOC_MAX;
    u1_s_hmitaste_chgnum = (U1)HMI_TASTE_CHGNUM_INIT;
    u1_s_hmitaste_chgnum_pre = (U1)HMI_TASTE_CHGNUM_INIT;

    for (u4_t_loop_txt = (U4)0U ; u4_t_loop_txt < (U4)HMI_TASTE_TXT_MAX ; u4_t_loop_txt++) {
        st_sp_hmitaste.u2_TXT_DAT01[u4_t_loop_txt] = (U2)U2_MAX;
        st_sp_hmitaste.u2_TXT_DAT02[u4_t_loop_txt] = (U2)U2_MAX;
        st_sp_hmitaste.u2_TXT_DAT03[u4_t_loop_txt] = (U2)U2_MAX;
        st_sp_hmitaste.u2_TXT_DAT04[u4_t_loop_txt] = (U2)U2_MAX;
        st_sp_hmitaste.u2_TXT_DAT05[u4_t_loop_txt] = (U2)U2_MAX;
        st_sp_hmitaste.u2_TXT_DAT06[u4_t_loop_txt] = (U2)U2_MAX;
    }
}

/*===================================================================================================================================*/
/*  void    vd_g_HmiTasteMainTask(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiTasteMainTask(void)
{
    static const U2 u2_s_HMITASTE_TO = (U2)1000U / (U2)50U;
    U1              u1_t_to;

    u1_t_to = u1_g_HmiProxyToc(&u2_s_hmitaste_to, u2_s_HMITASTE_TO);

    if((u1_t_to == (U1)FALSE) && 
       (u1_s_hmitaste_chgnum != (U1)HMI_TASTE_CHGNUM_INIT) &&
       (u1_s_hmitaste_chgnum != u1_s_hmitaste_chgnum_pre)) {
       vd_s_HmiTaste();
    }

    u1_s_hmitaste_chgnum_pre = u1_s_hmitaste_chgnum;
}

/*===================================================================================================================================*/
/*  static void    vd_s_HmiTaste(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_HmiTaste(void)
{
    U4 u4_t_loop_txt;
    U1 u1_t_init_chk;

    u1_t_init_chk = (U1)HMI_TASTE_TXT_NG;

    for(u4_t_loop_txt = (U4)0U ; u4_t_loop_txt < (U4)HMI_TASTE_TXT_MAX ; u4_t_loop_txt++){
        if(st_sp_hmitaste.u2_TXT_DAT01[u4_t_loop_txt] != (U2)HMI_TASTE_TXT_INIT){
            u1_t_init_chk &= (U1)HMI_TASTE_TXT_OK;
        }
        if(st_sp_hmitaste.u2_TXT_DAT02[u4_t_loop_txt] != (U2)HMI_TASTE_TXT_INIT){
            u1_t_init_chk &= (U1)HMI_TASTE_TXT_OK;
        }
        if(st_sp_hmitaste.u2_TXT_DAT03[u4_t_loop_txt] != (U2)HMI_TASTE_TXT_INIT){
            u1_t_init_chk &= (U1)HMI_TASTE_TXT_OK;
        }
        if(st_sp_hmitaste.u2_TXT_DAT04[u4_t_loop_txt] != (U2)HMI_TASTE_TXT_INIT){
            u1_t_init_chk &= (U1)HMI_TASTE_TXT_OK;
        }
        if(st_sp_hmitaste.u2_TXT_DAT05[u4_t_loop_txt] != (U2)HMI_TASTE_TXT_INIT){
            u1_t_init_chk &= (U1)HMI_TASTE_TXT_OK;
        }
        if(st_sp_hmitaste.u2_TXT_DAT06[u4_t_loop_txt] != (U2)HMI_TASTE_TXT_INIT){
            u1_t_init_chk &= (U1)HMI_TASTE_TXT_OK;
        }
    }

    if(u1_t_init_chk == HMI_TASTE_TXT_OK) {
        vd_g_MMTextTx_TasteInfo((U1)HMI_TASTE_NUM,u1_s_hmitaste_chgnum,&st_sp_hmitaste);
    }
}

/*===================================================================================================================================*/
/*  void    vd_g_HmiTaste1Put(const U4 * u4_ap_REQ)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiTaste1Put(const U4 * u4_ap_REQ)
{
    U4 u4_t_loop;
    U4 u4_t_idx_lo;
    U4 u4_t_idx_hi;
    U2 u2_t_txt_lo;
    U2 u2_t_txt_hi;

    if(u4_ap_REQ != vdp_PTR_NA) {
        for (u4_t_loop = (U4)0U ; u4_t_loop < (U4)HMI_TASTE_BUFNUM ; u4_t_loop++){
            u4_t_idx_lo = u4_t_loop * (U4)HMI_TASTE_CAL_TWO;
            u4_t_idx_hi = (u4_t_loop * (U4)HMI_TASTE_CAL_TWO) + (U4)HMI_TASTE_CAL_ONE;

            u2_t_txt_lo = (U2)(u4_ap_REQ[u4_t_loop] & (U2)HMI_TASTE_TXT_MASK);
            u2_t_txt_hi = (U2)((u4_ap_REQ[u4_t_loop] >> HMI_TASTE_TXT_LSB) & (U2)HMI_TASTE_TXT_MASK);

            st_sp_hmitaste.u2_TXT_DAT01[u4_t_idx_lo] = u2_t_txt_lo;
            st_sp_hmitaste.u2_TXT_DAT01[u4_t_idx_hi] = u2_t_txt_hi;
        }
    }

    u2_s_hmitaste_to = (U2)HMIPROXY_TOC_INI;
}

/*===================================================================================================================================*/
/*  void    vd_g_HmiTaste2Put(const U4 * u4_ap_REQ)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiTaste2Put(const U4 * u4_ap_REQ)
{
    U4 u4_t_loop;
    U4 u4_t_idx_lo;
    U4 u4_t_idx_hi;
    U2 u2_t_txt_lo;
    U2 u2_t_txt_hi;

    if(u4_ap_REQ != vdp_PTR_NA) {
        for (u4_t_loop = (U4)0U ; u4_t_loop < (U4)HMI_TASTE_BUFNUM ; u4_t_loop++){
            u4_t_idx_lo = u4_t_loop * (U4)HMI_TASTE_CAL_TWO;
            u4_t_idx_hi = (u4_t_loop * (U4)HMI_TASTE_CAL_TWO) + (U4)HMI_TASTE_CAL_ONE;

            u2_t_txt_lo = (U2)(u4_ap_REQ[u4_t_loop] & (U2)HMI_TASTE_TXT_MASK);
            u2_t_txt_hi = (U2)((u4_ap_REQ[u4_t_loop] >> HMI_TASTE_TXT_LSB) & (U2)HMI_TASTE_TXT_MASK);

            st_sp_hmitaste.u2_TXT_DAT02[u4_t_idx_lo] = u2_t_txt_lo;
            st_sp_hmitaste.u2_TXT_DAT02[u4_t_idx_hi] = u2_t_txt_hi;
        }
    }

    u2_s_hmitaste_to = (U2)HMIPROXY_TOC_INI;
}

/*===================================================================================================================================*/
/*  void    vd_g_HmiTaste3Put(const U4 * u4_ap_REQ)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiTaste3Put(const U4 * u4_ap_REQ)
{
    U4 u4_t_loop;
    U4 u4_t_idx_lo;
    U4 u4_t_idx_hi;
    U2 u2_t_txt_lo;
    U2 u2_t_txt_hi;

    if(u4_ap_REQ != vdp_PTR_NA) {
        for (u4_t_loop = (U4)0U ; u4_t_loop < (U4)HMI_TASTE_BUFNUM ; u4_t_loop++){
            u4_t_idx_lo = u4_t_loop * (U4)HMI_TASTE_CAL_TWO;
            u4_t_idx_hi = (u4_t_loop * (U4)HMI_TASTE_CAL_TWO) + (U4)HMI_TASTE_CAL_ONE;

            u2_t_txt_lo = (U2)(u4_ap_REQ[u4_t_loop] & (U2)HMI_TASTE_TXT_MASK);
            u2_t_txt_hi = (U2)((u4_ap_REQ[u4_t_loop] >> HMI_TASTE_TXT_LSB) & (U2)HMI_TASTE_TXT_MASK);

            st_sp_hmitaste.u2_TXT_DAT03[u4_t_idx_lo] = u2_t_txt_lo;
            st_sp_hmitaste.u2_TXT_DAT03[u4_t_idx_hi] = u2_t_txt_hi;
        }
    }

    u2_s_hmitaste_to = (U2)HMIPROXY_TOC_INI;
}

/*===================================================================================================================================*/
/*  void    vd_g_HmiTaste4Put(const U4 * u4_ap_REQ)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiTaste4Put(const U4 * u4_ap_REQ)
{
    U4 u4_t_loop;
    U4 u4_t_idx_lo;
    U4 u4_t_idx_hi;
    U2 u2_t_txt_lo;
    U2 u2_t_txt_hi;

    if(u4_ap_REQ != vdp_PTR_NA) {
        for (u4_t_loop = (U4)0U ; u4_t_loop < (U4)HMI_TASTE_BUFNUM ; u4_t_loop++){
            u4_t_idx_lo = u4_t_loop * (U4)HMI_TASTE_CAL_TWO;
            u4_t_idx_hi = (u4_t_loop * (U4)HMI_TASTE_CAL_TWO) + (U4)HMI_TASTE_CAL_ONE;

            u2_t_txt_lo = (U2)(u4_ap_REQ[u4_t_loop] & (U2)HMI_TASTE_TXT_MASK);
            u2_t_txt_hi = (U2)((u4_ap_REQ[u4_t_loop] >> HMI_TASTE_TXT_LSB) & (U2)HMI_TASTE_TXT_MASK);

            st_sp_hmitaste.u2_TXT_DAT04[u4_t_idx_lo] = u2_t_txt_lo;
            st_sp_hmitaste.u2_TXT_DAT04[u4_t_idx_hi] = u2_t_txt_hi;
        }
    }

    u2_s_hmitaste_to = (U2)HMIPROXY_TOC_INI;
}

/*===================================================================================================================================*/
/*  void    vd_g_HmiTaste5Put(const U4 * u4_ap_REQ)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiTaste5Put(const U4 * u4_ap_REQ)
{
    U4 u4_t_loop;
    U4 u4_t_idx_lo;
    U4 u4_t_idx_hi;
    U2 u2_t_txt_lo;
    U2 u2_t_txt_hi;

    if(u4_ap_REQ != vdp_PTR_NA) {
        for (u4_t_loop = (U4)0U ; u4_t_loop < (U4)HMI_TASTE_BUFNUM ; u4_t_loop++){
            u4_t_idx_lo = u4_t_loop * (U4)HMI_TASTE_CAL_TWO;
            u4_t_idx_hi = (u4_t_loop * (U4)HMI_TASTE_CAL_TWO) + (U4)HMI_TASTE_CAL_ONE;

            u2_t_txt_lo = (U2)(u4_ap_REQ[u4_t_loop] & (U2)HMI_TASTE_TXT_MASK);
            u2_t_txt_hi = (U2)((u4_ap_REQ[u4_t_loop] >> HMI_TASTE_TXT_LSB) & (U2)HMI_TASTE_TXT_MASK);

            st_sp_hmitaste.u2_TXT_DAT05[u4_t_idx_lo] = u2_t_txt_lo;
            st_sp_hmitaste.u2_TXT_DAT05[u4_t_idx_hi] = u2_t_txt_hi;
        }
    }

    u2_s_hmitaste_to = (U2)HMIPROXY_TOC_INI;
}

/*===================================================================================================================================*/
/*  void    vd_g_HmiTaste6Put(const U4 * u4_ap_REQ)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiTaste6Put(const U4 * u4_ap_REQ)
{
    U4 u4_t_loop;
    U4 u4_t_idx_lo;
    U4 u4_t_idx_hi;
    U2 u2_t_txt_lo;
    U2 u2_t_txt_hi;

    if(u4_ap_REQ != vdp_PTR_NA) {
        for (u4_t_loop = (U4)0U ; u4_t_loop < (U4)HMI_TASTE_BUFNUM ; u4_t_loop++){
            u4_t_idx_lo = u4_t_loop * (U4)HMI_TASTE_CAL_TWO;
            u4_t_idx_hi = (u4_t_loop * (U4)HMI_TASTE_CAL_TWO) + (U4)HMI_TASTE_CAL_ONE;

            u2_t_txt_lo = (U2)(u4_ap_REQ[u4_t_loop] & (U2)HMI_TASTE_TXT_MASK);
            u2_t_txt_hi = (U2)((u4_ap_REQ[u4_t_loop] >> HMI_TASTE_TXT_LSB) & (U2)HMI_TASTE_TXT_MASK);

            st_sp_hmitaste.u2_TXT_DAT06[u4_t_idx_lo] = u2_t_txt_lo;
            st_sp_hmitaste.u2_TXT_DAT06[u4_t_idx_hi] = u2_t_txt_hi;
        }
    }

    u2_s_hmitaste_to = (U2)HMIPROXY_TOC_INI;
}

/*===================================================================================================================================*/
/*  void    vd_g_HmiTaste1Put(const U4 * u4_ap_REQ)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiTasteChgnumPut(const U4 * u4_ap_REQ)
{
    U4 u4_t_loop;

    if(u4_ap_REQ != vdp_PTR_NA) {
        for (u4_t_loop = (U4)0U ; u4_t_loop < (U4)HMI_TASTE_CHGNUM ; u4_t_loop++){
            u1_s_hmitaste_chgnum = (U1)(u4_ap_REQ[u4_t_loop] & (U4)0x0FU);
        }
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
/*  1.0.0    01/24/2023  KT       New.                                                                                               */
/*                                                                                                                                   */
/*  * KT   = Kenta Takaji, Denso Techno                                                                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/
