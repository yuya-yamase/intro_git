/* 2.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Vehicle Status Viewer / Toyota IPC/MET Coolant Temperature Gauge - Segment                                                       */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GAGDST_TEMPSEG_C_MAJOR                        (2)
#define GAGDST_TEMPSEG_C_MINOR                        (1)
#define GAGDST_TEMPSEG_C_PATCH                        (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "gagdst_tempseg_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((GAGDST_TEMPSEG_C_MAJOR != GAGDST_TEMPSEG_H_MAJOR) || \
     (GAGDST_TEMPSEG_C_MINOR != GAGDST_TEMPSEG_H_MINOR) || \
     (GAGDST_TEMPSEG_C_PATCH != GAGDST_TEMPSEG_H_PATCH))
#error "gagdst_tempseg.c and gagdst_tempseg.h : source and header files are inconsistent!"
#endif

#if ((GAGDST_TEMPSEG_C_MAJOR != GAGDST_TEMPSEG_CFG_H_MAJOR) || \
     (GAGDST_TEMPSEG_C_MINOR != GAGDST_TEMPSEG_CFG_H_MINOR) || \
     (GAGDST_TEMPSEG_C_PATCH != GAGDST_TEMPSEG_CFG_H_PATCH))
#error "gagdst_tempseg.c and gagdst_tempseg_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GAGDST_TEMPSEG_SEG_UNK      (255U)

#define GAGDST_TEMPSEG_BLINK_FREQ   (600U / 20U)
#define GAGDST_TEMPSEG_BLINK_DUTY   (300U / 20U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U1          u1_num;
    const U2 *  u2p_n2b;
}ST_GAGDST_TEMPSEG_N2B;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1       u1_s_gagdst_tempseg_num;                            /* Number of temp segment lighting  */
static U2       u2_s_gagdst_tempseg_bit;
static U1       u1_s_gagdst_tempseg_num_ow;                         /* Number of temp segment lighting  */
static U2       u2_s_gagdst_tempseg_bit_ow;
static U1       u1_s_gagdst_tempseg_blnkcnt;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void     vd_s_GagdstTempSegAct(const U2 u2_a_TRGT, U1 * u1p_a_segnum, U2 * u2_a_segbit, const ST_GAGDST_TEMPCFG * stp_a_TEMPCFG);
static U2       u2_s_GagdstTempSegBlnkMsk(const ST_GAGDST_TEMPCFG * stp_a_TEMPCFG);
static void     vd_s_GagdstTempOw(const U1 u1_a_ESI, const U2 u2_a_OW, const ST_GAGDST_TEMPCFG * stp_a_TEMPCFG);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_GagdstTempSegInit(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_GagdstTempSegInit(void)
{
    u1_s_gagdst_tempseg_num     = (U1)GAGDST_TEMPSEG_SEG_UNK;
    u2_s_gagdst_tempseg_bit     = (U2)0U;
    u1_s_gagdst_tempseg_num_ow  = (U1)GAGDST_TEMPSEG_SEG_UNK;
    u2_s_gagdst_tempseg_bit_ow  = (U2)0U;
    u1_s_gagdst_tempseg_blnkcnt = (U1)U1_MAX;
}
/*===================================================================================================================================*/
/*  void    vd_g_GagdstTempSegOpemdEvhk(const U4 u4_a_EVTBIT)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_GagdstTempSegOpemdEvhk(const U4 u4_a_EVTBIT)
{
    U4  u4_t_evtchk;

    u4_t_evtchk = u4_a_EVTBIT & (U4)(VEH_OPEMD_EVTBIT_IGN_TO_ON | VEH_OPEMD_EVTBIT_IGN_TO_OFF);
    if(u4_t_evtchk != (U4)0U){
        u1_s_gagdst_tempseg_num     = (U1)GAGDST_TEMPSEG_SEG_UNK;
        u2_s_gagdst_tempseg_bit     = (U2)0U;
        u1_s_gagdst_tempseg_num_ow  = (U1)GAGDST_TEMPSEG_SEG_UNK;
        u2_s_gagdst_tempseg_bit_ow  = (U2)0U;
        u1_s_gagdst_tempseg_blnkcnt = (U1)U1_MAX;
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_GagdstTempSegUpdt(const U2 u2_a_SRC_CHK, const U2 u2_a_TRGT, const U2 u2_a_OW, const U1 u1_a_ESI)                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_GagdstTempSegUpdt(const U2 u2_a_SRC_CHK, const U2 u2_a_TRGT, const U2 u2_a_OW, const U1 u1_a_ESI)
{
    U1                          u1_t_idx;
    U2                          u2_t_src_chk;
    const ST_GAGDST_TEMPCFG *   stp_t_tempcfg;

    u1_t_idx     = u1_g_GagdstTempRng();
    if(u1_t_idx >= u1_g_GAGDST_TEMPSEG_NUM_CFG){
        u1_s_gagdst_tempseg_num     = (U1)GAGDST_TEMPSEG_SEG_UNK;
        u2_s_gagdst_tempseg_bit     = (U2)0U;
        u1_s_gagdst_tempseg_num_ow  = (U1)GAGDST_TEMPSEG_SEG_UNK;
        u2_s_gagdst_tempseg_bit_ow  = (U2)0U;
        u1_s_gagdst_tempseg_blnkcnt = (U1)U1_MAX;
    }
    else {
        stp_t_tempcfg = &st_gp_GAGDST_TEMPSEGCFG[u1_t_idx];

        if ((u2_a_SRC_CHK & (U2)GAUGE_SRC_CHK_IGN_ON) == (U2)0U) {     /* IGN-OFF */
            u1_s_gagdst_tempseg_num     = (U1)GAGDST_TEMPSEG_SEG_UNK;
            u2_s_gagdst_tempseg_bit     = (U2)0U;
            u1_s_gagdst_tempseg_num_ow  = (U1)GAGDST_TEMPSEG_SEG_UNK;
            u2_s_gagdst_tempseg_bit_ow  = (U2)0U;
            u1_s_gagdst_tempseg_blnkcnt = (U1)U1_MAX;
        }
        else {                           /* IGN-ON  */
            u2_t_src_chk = u2_a_SRC_CHK & u2_g_GAGDST_TEMPSEG_SRC_CHK;
            if ((u2_t_src_chk & u2_g_GAGDST_TEMPSEG_WTSW_HI) == u2_g_GAGDST_TEMPSEG_WTSW_HI) {    /* Source Signal WT_SW=HI           */
                vd_s_GagdstTempSegAct((U2)U2_MAX, &u1_s_gagdst_tempseg_num, &u2_s_gagdst_tempseg_bit, stp_t_tempcfg);
            }
            else if ((u2_t_src_chk & (u2_g_GAGDST_TEMPSEG_SRC_INV | u2_g_GAGDST_TEMPSEG_SRC_UNK)) != (U1)0U) {
                u1_s_gagdst_tempseg_num     = (U1)GAGDST_TEMPSEG_SEG_UNK;
                u2_s_gagdst_tempseg_bit     = (U2)0U;
                u1_s_gagdst_tempseg_blnkcnt = (U1)U1_MAX;
            }
            else {
                vd_s_GagdstTempSegAct(u2_a_TRGT, &u1_s_gagdst_tempseg_num, &u2_s_gagdst_tempseg_bit, stp_t_tempcfg);
            }

            u2_s_gagdst_tempseg_bit &= u2_s_GagdstTempSegBlnkMsk(stp_t_tempcfg);
        }
        vd_s_GagdstTempOw(u1_a_ESI, u2_a_OW, stp_t_tempcfg);
    }
}
/*===================================================================================================================================*/
/*  static void     vd_s_GagdstTempSegAct(const U2 u2_a_TRGT, U1 * u1p_a_segnum,                                                     */
/*                                           U2 * u2_a_segbit, const ST_GAGDST_TEMPCFG * stp_a_TEMPCFG)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GagdstTempSegAct(const U2 u2_a_TRGT, U1 * u1p_a_segnum, U2 * u2_a_segbit, const ST_GAGDST_TEMPCFG * stp_a_TEMPCFG)
{
    static const U2 u2_s_GAGDST_TEMPSEG_N2B_CSTD_SEG8[GAGDST_TEMPSEG_NUM_RNG_CSTD] = {
        /*       0            1            2            3            4            5            6            7            8   */
        (U2)0x0000U, (U2)0x0001U, (U2)0x0003U, (U2)0x0007U, (U2)0x000FU, (U2)0x001FU, (U2)0x003FU, (U2)0x007FU, (U2)0x00FFU
    };
    static const ST_GAGDST_TEMPSEG_N2B st_sp_GAGDST_TEMPSEG_N2B[GAGDST_TEMPSEG_NUM_TYPE] = {
        {   (U1)GAGDST_TEMPSEG_NUM_RNG_CSTD, &u2_s_GAGDST_TEMPSEG_N2B_CSTD_SEG8[0] }    /* GAGDST_TEMPSEG_TYPE_CSTD_SEG8   (0U) */
    };
    U1                  u1_t_segmax;
    const U2 *          u2_tp_n2b;

    (*u2_a_segbit)  = (U2)0U;
    if(stp_a_TEMPCFG->u1_type < (U1)GAGDST_TEMPSEG_NUM_TYPE){
        u1_t_segmax = st_sp_GAGDST_TEMPSEG_N2B[stp_a_TEMPCFG->u1_type].u1_num;
        u2_tp_n2b   = st_sp_GAGDST_TEMPSEG_N2B[stp_a_TEMPCFG->u1_type].u2p_n2b;
        if((*u1p_a_segnum) >= (U1)u1_t_segmax){
            (*u1p_a_segnum) = (U1)0U;
        }
        (*u1p_a_segnum) = (U1)u2_g_RngCmprU2((U2)(*u1p_a_segnum), u2_a_TRGT, stp_a_TEMPCFG->stp_cmpr_u2);
        if((*u1p_a_segnum) < (U1)u1_t_segmax){
            (*u2_a_segbit) = u2_tp_n2b[(*u1p_a_segnum)];
        }
    }
}
/*===================================================================================================================================*/
/*  U1      u1_g_GagdstTempSeg(const U1 u1_a_SEGPOS, const U1 u1_a_OW_EN)                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_GagdstTempSeg(const U1 u1_a_SEGPOS, const U1 u1_a_OW_EN)
{
    U1  u1_t_ltsts;
    U2  u2_t_segbit;
    U2  u2_t_chkbit;

    if(u1_a_OW_EN == (U1)TRUE){
        u2_t_segbit = u2_s_gagdst_tempseg_bit_ow;
    }
    else{
        u2_t_segbit = u2_s_gagdst_tempseg_bit;
    }

    u1_t_ltsts = (U1)FALSE;
    if(u1_a_SEGPOS < (U1)GAGDST_TEMPSEG_NUM_SEG){
        u2_t_chkbit = (U2)((U2)TRUE << u1_a_SEGPOS);
        if((u2_t_segbit & u2_t_chkbit) != (U2)0U){
            u1_t_ltsts = (U1)TRUE;
        }
    }

    return(u1_t_ltsts);
}
/*===================================================================================================================================*/
/*  U2      u2_g_GagdstTempSegBit(const U1 u1_a_OW_EN)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2      u2_g_GagdstTempSegBit(const U1 u1_a_OW_EN)
{
    U2  u2_t_ret;

    u2_t_ret = u2_s_gagdst_tempseg_bit;
    if(u1_a_OW_EN == (U1)TRUE){
        u2_t_ret = u2_s_gagdst_tempseg_bit_ow;
    }
    return(u2_t_ret);
}
/*===================================================================================================================================*/
/*  U2      u2_g_GagdstTempSegBit(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_GagdstTempSegBitPack(const ST_GAG_BITPACK * st_ap_PACK, U4 * u4_ap_buf, const U1 u1_a_NWORD, const U1 u1_a_OW_EN)
{
    U4                          u4_t_loop;
    U1                          u1_t_srcid;
    U2                          u2_t_dstpos;
    U2                          u2_t_storeidx;
    U4                          u4_t_dstbit;
    U2                          u2_t_srcbit;
    U2                          u2_t_tempseg_bit;

    if((st_ap_PACK != vdp_PTR_NA) && (u4_ap_buf != vdp_PTR_NA)){
        for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)st_ap_PACK->u1_NUM ; u4_t_loop++){
            u1_t_srcid    = (st_ap_PACK->stp_SRC2DST[u4_t_loop]).u1_srcid;
            u2_t_dstpos   = (st_ap_PACK->stp_SRC2DST[u4_t_loop]).u2_dstpos;
            u2_t_storeidx = (U2)(u2_t_dstpos >> GAGDST_PACK_BUFIDX_SHIFT);
            if((u1_t_srcid    < (U1)GAGDST_TEMPSEG_NUM_SEG) &&
               (u2_t_storeidx < (U2)u1_a_NWORD )    ){
                u2_t_tempseg_bit = u2_s_gagdst_tempseg_bit;
                if(u1_a_OW_EN == (U1)TRUE){
                    u2_t_tempseg_bit = u2_s_gagdst_tempseg_bit_ow;
                }
                u2_t_srcbit   = u2_t_tempseg_bit & (U2)((U2)TRUE << u1_t_srcid);
                u4_t_dstbit   = (U4)TRUE << (u2_t_dstpos & (U2)GAGDST_PACK_BITPOS_MASK);
                if(u2_t_srcbit != (U2)0U){
                    u4_ap_buf[u2_t_storeidx] |= u4_t_dstbit;
                }else{
                    u4_ap_buf[u2_t_storeidx] &= ((U4)U4_MAX ^ u4_t_dstbit);
                }
            }
        }
    }
}

/*===================================================================================================================================*/
/*  static U2       u2_s_GagdstTempSegBlnkMsk(const ST_GAGDST_TEMPCFG * stp_a_TEMPCFG)                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U2       u2_s_GagdstTempSegBlnkMsk(const ST_GAGDST_TEMPCFG * stp_a_TEMPCFG)
{
    static const U2 u2_s_GAGDST_TEMPSEG_MASK[GAGDST_TEMPSEG_NUM_TYPE] = {
        ((U2)U2_MAX ^ ((U2)TRUE << GAGDST_TEMPSEG_SEG8))     /* GAGDST_TEMPSEG_TYPE_CSTD_SEG8   (0U) */
    };
    static const U1 u1_s_GAGDST_TEMPSEG_TOPSEG_MAX[GAGDST_TEMPSEG_NUM_TYPE] = {
        (U1)GAGDST_TEMPSEG_SEG8     /* GAGDST_TEMPSEG_TYPE_CSTD_SEG8   (0U) */
    };
    U1  u1_t_top;
    U2  u2_t_mask;

    u1_t_top  = (U1)U1_MAX;
    u2_t_mask = (U2)U2_MAX;
    if(stp_a_TEMPCFG->u1_type < (U1)GAGDST_TEMPSEG_NUM_TYPE){
        u1_t_top  = u1_s_GAGDST_TEMPSEG_TOPSEG_MAX[stp_a_TEMPCFG->u1_type];
        u2_t_mask = u2_s_GAGDST_TEMPSEG_MASK[stp_a_TEMPCFG->u1_type];
    }
    if((u1_s_gagdst_tempseg_num >= u1_t_top) &&
       (u1_s_gagdst_tempseg_num != (U1)GAGDST_TEMPSEG_SEG_UNK)){
        if(u1_s_gagdst_tempseg_blnkcnt >= (U1)U1_MAX){
            u1_s_gagdst_tempseg_blnkcnt = (U1)0U;
        }
        else if(u1_s_gagdst_tempseg_blnkcnt < (U1)GAGDST_TEMPSEG_BLINK_FREQ){
            u1_s_gagdst_tempseg_blnkcnt++;
        }
        else{
            u1_s_gagdst_tempseg_blnkcnt = (U1)0U;
        }
    }
    else{
        u1_s_gagdst_tempseg_blnkcnt = (U1)U1_MAX;
    }

    if((u1_s_gagdst_tempseg_blnkcnt == (U1)U1_MAX                   ) ||
       (u1_s_gagdst_tempseg_blnkcnt <  (U1)GAGDST_TEMPSEG_BLINK_DUTY)){
        u2_t_mask = (U2)U2_MAX;
    }
    return(u2_t_mask);
}

/*===================================================================================================================================*/
/*  static void     vd_s_GagdstTempOw(const U1 u1_a_ESI, const U2 u2_a_OW)                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_GagdstTempOw(const U1 u1_a_ESI, const U2 u2_a_OW, const ST_GAGDST_TEMPCFG * stp_a_TEMPCFG)
{
    U2  u2_t_trgt;

    if(u1_a_ESI == (U1)TRUE){
        u2_s_gagdst_tempseg_bit_ow  = u2_a_OW;
        u1_s_gagdst_tempseg_num_ow  = (U1)GAGDST_TEMPSEG_SEG_UNK;
        u1_s_gagdst_tempseg_blnkcnt = (U1)U1_MAX;
    }
    else if(u2_a_OW != (U2)GAUGE_OW_INA){
        u2_t_trgt = (U2)0U;
        if(u2_a_OW < (U2)GAGDST_TEMP_SEG_NUM_IOC){
            u2_t_trgt = u2_gp_GAGDST_TEMPSEG_OWACT[u2_a_OW];
        }
        u1_s_gagdst_tempseg_num_ow = (U1)0U;
        vd_s_GagdstTempSegAct(u2_t_trgt, &u1_s_gagdst_tempseg_num_ow, &u2_s_gagdst_tempseg_bit_ow, stp_a_TEMPCFG);
        u1_s_gagdst_tempseg_blnkcnt = (U1)U1_MAX;
    }
    else{
        u1_s_gagdst_tempseg_num_ow  = u1_s_gagdst_tempseg_num;
        u2_s_gagdst_tempseg_bit_ow  = u2_s_gagdst_tempseg_bit;
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
/*  2.0.0    06/03/2021  TA       New.                                                                                               */
/*  2.0.1    10/18/2021  TK       Change the definition of the null pointer used.(BSW v115_r007)                                     */
/*  2.0.2    10/25/2021  TK       QAC supported.                                                                                     */
/*  2.1.0    11/11/2021  TA(M)    CSTD or CORG.                                                                                      */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  19PFv3-1 02/01/2024  KH       Apply 19PFv3 configuration                                                                         */
/*                                                                                                                                   */
/*  * TA   = Teruyuki Anjima, Denso                                                                                                  */
/*  * TK   = Takanori Kuno, DensoTechno                                                                                              */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*  * KH   = Kiko Huerte, DTPH                                                                                                       */
/*                                                                                                                                   */
/*===================================================================================================================================*/
