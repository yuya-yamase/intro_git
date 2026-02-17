/* 2.2.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Odo Non-Volatile Memory Interface                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ODO_NVMIF_UTIL_C_MAJOR                   (2)
#define ODO_NVMIF_UTIL_C_MINOR                   (2)
#define ODO_NVMIF_UTIL_C_PATCH                   (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "odo_nvmif_cfg_private.h"
#include "odo_nvmif_util.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((ODO_NVMIF_UTIL_C_MAJOR != ODO_NVMIF_UTIL_H_MAJOR) || \
     (ODO_NVMIF_UTIL_C_MINOR != ODO_NVMIF_UTIL_H_MINOR) || \
     (ODO_NVMIF_UTIL_C_PATCH != ODO_NVMIF_UTIL_H_PATCH))
#error "odo_nvmif_util.c and odo_nvmif_util.h : source and header files are inconsistent!"
#endif

#if ((ODO_NVMIF_UTIL_C_MAJOR != ODO_NVMIF_CFG_H_MAJOR) || \
     (ODO_NVMIF_UTIL_C_MINOR != ODO_NVMIF_CFG_H_MINOR) || \
     (ODO_NVMIF_UTIL_C_PATCH != ODO_NVMIF_CFG_H_PATCH))
#error "odo_nvmif_util.c and odo_nvmif_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  U1      u1_g_OdoNvmIfFifoPosIn(ST_ODO_NVMIF_FIFO_CTRL * st_ap_ctrl, const U1 u1_a_MAX)                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_OdoNvmIfFifoPosIn(ST_ODO_NVMIF_FIFO_CTRL * st_ap_ctrl, const U1 u1_a_MAX)
{
    U2                      u2_t_fifo_len;
    U1                      u1_t_fifo_in;
    U1                      u1_t_fifo_out;
    U1                      u1_t_fifo_next;

    u2_t_fifo_len = st_ap_ctrl->u2_len;
    u1_t_fifo_in  = st_ap_ctrl->u1_pos_in;
    u1_t_fifo_out = st_ap_ctrl->u1_pos_out;

    if((u2_t_fifo_len                   == (U2)0U                         ) ||
       (u2_t_fifo_len                   >  (U2)u1_a_MAX                   ) ||
       ((u2_t_fifo_len == (U2)u1_a_MAX) && (u1_t_fifo_out != u1_t_fifo_in)) ||
       (u1_t_fifo_in                    >= u1_a_MAX                       )){

        u2_t_fifo_len = (U2)0U;
        u1_t_fifo_in  = (U1)0U;
        u1_t_fifo_out = (U1)0U;
    }

    if(u2_t_fifo_len < (U2)u1_a_MAX){

        u1_t_fifo_next = u1_t_fifo_in + (U1)1U;
        if(u1_t_fifo_next >= u1_a_MAX){
            u1_t_fifo_next = (U1)0U;
        }
        u2_t_fifo_len++;

        st_ap_ctrl->u2_len     = u2_t_fifo_len; 
        st_ap_ctrl->u1_pos_in  = u1_t_fifo_next;
        st_ap_ctrl->u1_pos_out = u1_t_fifo_out;
    }
    else{
        u1_t_fifo_in = (U1)U1_MAX;
    }

    return(u1_t_fifo_in);
}
/*===================================================================================================================================*/
/*  U1      u1_g_OdoNvmIfFifoPosOut(ST_ODO_NVMIF_FIFO_CTRL * st_ap_ctrl, const U1 u1_a_MAX)                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_OdoNvmIfFifoPosOut(ST_ODO_NVMIF_FIFO_CTRL * st_ap_ctrl, const U1 u1_a_MAX)
{
    U2                      u2_t_fifo_len;
    U1                      u1_t_fifo_in;
    U1                      u1_t_fifo_out;
    U1                      u1_t_fifo_next;

    u2_t_fifo_len = st_ap_ctrl->u2_len;
    u1_t_fifo_in  = st_ap_ctrl->u1_pos_in;
    u1_t_fifo_out = st_ap_ctrl->u1_pos_out;

    if((u2_t_fifo_len                   == (U2)0U                         ) ||
       (u2_t_fifo_len                   >  (U2)u1_a_MAX                   ) ||
       ((u2_t_fifo_len == (U2)u1_a_MAX) && (u1_t_fifo_out != u1_t_fifo_in)) ||
       (u1_t_fifo_out                   >= u1_a_MAX                       )){

        st_ap_ctrl->u2_len     = (U2)0U; 
        st_ap_ctrl->u1_pos_in  = (U1)0U;
        st_ap_ctrl->u1_pos_out = (U1)0U;

        u1_t_fifo_out          = (U1)U1_MAX;
    }
    else{

        u1_t_fifo_next = u1_t_fifo_out + (U1)1U;
        if(u1_t_fifo_next >= u1_a_MAX){
            u1_t_fifo_next = (U1)0U;
        }
        u2_t_fifo_len--;

        st_ap_ctrl->u2_len     = u2_t_fifo_len;
        st_ap_ctrl->u1_pos_out = u1_t_fifo_next;
    }

    return(u1_t_fifo_out);
}
/*===================================================================================================================================*/
/*  void    vd_g_OdoNvmIfWriKmBlock(const ST_ODO_NVMIF_REC_KM * st_ap_REC_KM,                                                        */
/*                                  const ST_ODO_NVMIF_RW_CTRL * st_ap_CTRL,                                                         */
/*                                  const U1 * u1_ap_KM)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_OdoNvmIfWriKmBlock(const ST_ODO_NVMIF_REC_KM * st_ap_REC_KM,
                                const ST_ODO_NVMIF_RW_CTRL * st_ap_CTRL,
                                const U1 * u1_ap_KM)
{
    const U2 *              u2_tp_BLOCK;
    U2                      u2_t_blo_next;
    U2                      u2_t_src_offset;

    u2_tp_BLOCK     = st_ap_REC_KM->u2p_BLOCK;
    u2_t_blo_next   = ((U2)st_ap_CTRL->u1_rec_idx * (U2)st_ap_REC_KM->u1_rec_nblock) + (U2)st_ap_CTRL->u1_blo_cnt;
    u2_t_src_offset = (U2)st_ap_CTRL->u1_blo_cnt * (U2)st_ap_REC_KM->u1_blo_nbyte;
    vd_g_OdoNvmIfWriteBlock(st_ap_REC_KM->u1_dev_idx,
                            u2_tp_BLOCK[u2_t_blo_next],
                            &u1_ap_KM[u2_t_src_offset],
                            (U2)st_ap_REC_KM->u1_blo_nbyte);
}
/*===================================================================================================================================*/
/*  void    vd_g_OdoNvmIfReaKmBlock(const ST_ODO_NVMIF_REC_KM * st_ap_REC_KM,                                                        */
/*                                  const ST_ODO_NVMIF_RW_CTRL * st_ap_CTRL)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_OdoNvmIfReaKmBlock(const ST_ODO_NVMIF_REC_KM * st_ap_REC_KM,
                                const ST_ODO_NVMIF_RW_CTRL * st_ap_CTRL)
{
    const U2 *              u2_tp_BLOCK;
    U2                      u2_t_blo_next;

    u2_tp_BLOCK   = st_ap_REC_KM->u2p_BLOCK;
    u2_t_blo_next = ((U2)st_ap_CTRL->u1_rec_idx * (U2)st_ap_REC_KM->u1_rec_nblock) + (U2)st_ap_CTRL->u1_blo_cnt;
    vd_g_OdoNvmIfReadBlock(st_ap_REC_KM->u1_dev_idx, u2_tp_BLOCK[u2_t_blo_next]);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     9/18/2018  TN       New.                                                                                               */
/*  1.1.0     5/27/2019  TN       vd_g_OdoNvmIfRWDInit, vd_g_OdoNvmIfRWDTimCnt, vd_g_OdoNvmIfRWDUnlock, vd_g_OdoNvmIfRWDLock and     */
/*                                vd_g_OdoNvmIfRWDTimStart were implemented.                                                         */
/*  1.2.0    12/20/2019  TN       odo_nvmif_odo_km.c v1.1.0 -> v1.2.0.                                                               */
/*  1.2.1    05/14/2020  YN       odo_nvmif_odo_km.c & odo_nvmif_trip_km.c v1.2.0 -> v1.2.1.                                         */
/*  1.3.0     8/20/2020  TN       odo_km.c v1.2.0 -> v1.3.0.                                                                         */
/*  1.3.1    07/27/2020  YN       odo_km.c & odo_nvmif_odo_km.c v1.2.1 -> v1.3.1.                                                    */
/*  1.3.2    08/18/2020  YN       odo_nvmif_km.c v1.3.1 -> v1.3.2                                                                    */
/*  2.0.1    10/18/2021  TA(M)    odo_nvmif_km.c v1.3.2 -> v2.0.1                                                                    */
/*  2.1.0    01/21/2025  RS       Change for BEV System_Consideration_1 (odo_km.c v2.0.1 -> v2.1.0)                                  */
/*  2.2.0    02/10/2026  RS       Add Odo Inherit function for BEV FF2 (odo_km.c v2.1.0 -> v2.2.0)                                   */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*  * YN   = Yasuhiro Nakamura, Denso Techno                                                                                         */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*  * RS   = Ryuki Sako, Denso Techno                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/
