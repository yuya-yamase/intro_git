/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  CAN L-PDU FIFO/Queue                                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define CAN_LPFQ_C_MAJOR                         (1)
#define CAN_LPFQ_C_MINOR                         (0)
#define CAN_LPFQ_C_PATCH                         (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "can_lpfq_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((CAN_LPFQ_C_MAJOR != CAN_LPFQ_H_MAJOR) || \
     (CAN_LPFQ_C_MINOR != CAN_LPFQ_H_MINOR) || \
     (CAN_LPFQ_C_PATCH != CAN_LPFQ_H_PATCH))
#error "can_lpfq.c and can_lpfq.h : source and header files are inconsistent!"
#endif

#if ((CAN_LPFQ_C_MAJOR != CAN_LPFQ_CFG_H_MAJOR) || \
     (CAN_LPFQ_C_MINOR != CAN_LPFQ_CFG_H_MINOR) || \
     (CAN_LPFQ_C_PATCH != CAN_LPFQ_CFG_H_PATCH))
#error "can_lpfq.c and can_lpfq_cfg_private.h : source and config files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define CAN_LPFQ_RWCT_UNK                         (0xffffU)
#define CAN_LPFQ_RWCT_WO_0                        (0U)
#define CAN_LPFQ_RWCT_WO_1                        (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define u4_CAN_LPFQ_NW_ENQ(nby)                   (((nby) + (U4)3U) >> 2U)
#define u4_CAN_LPFQ_NW_DEQ(nby)                   (((nby) + (U4)11U) >> 2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static inline U1      u1_s_CANLpFqRwctOk(const U4 u4_a_NQUE, ST_CAN_LPFQ_RWCT * st_ap_rwct);
static inline U1      u1_s_CANLpFqFull(const U4 u4_a_NW_CAN, const ST_CAN_LPFQ_CH * st_ap_CH, ST_CAN_LPFQ_RWCT * st_ap_rwct);

static inline void    vd_s_CANLpFqCpyWord(U4 * u4_ap_dst, const U4 * u4_ap_SRC, const U4 u4_a_NWORD);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_CANLpFqInit(void)                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_CANLpFqInit(void)
{
    volatile U4 *                        u4_tp_rwct_w;
    U4                                   u4_t_ch;
    U4                                   u4_t_gli;

    for(u4_t_ch = (U4)0U; u4_t_ch < (U4)u2_g_CAN_LPFQ_NUM_CH; u4_t_ch++){

        u4_tp_rwct_w = (volatile U4 *)&st_gp_can_lpfq_rwct[u4_t_ch];

        /* --------------------------------------------------------------- */
        u4_t_gli = u4_g_CANLpFq_IRQ_DI();
        /* --------------------------------------------------------------- */

     /* st_tp_rwct->u2_rea = (U2)0U; */
     /* st_tp_rwct->u2_wri = (U2)0U; */
     /* st_tp_rwct->u2_enq = (U2)0U; */
        u4_tp_rwct_w[CAN_LPFQ_RWCT_WO_0] = (U4)0U;
        u4_tp_rwct_w[CAN_LPFQ_RWCT_WO_1] = (U4)0U;

        /* --------------------------------------------------------------- */
        vd_g_CANLpFq_IRQ_EI(u4_t_gli);
        /* --------------------------------------------------------------- */
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_CANLpFqResCh(const uint16 u2_a_FQ_CH)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_CANLpFqResCh(const uint16 u2_a_FQ_CH)
{
    volatile U4 *                        u4_tp_rwct_w;
    U4                                   u4_t_gli;

    if(u2_a_FQ_CH < u2_g_CAN_LPFQ_NUM_CH){

        u4_tp_rwct_w = (volatile U4 *)&st_gp_can_lpfq_rwct[u2_a_FQ_CH];

        /* --------------------------------------------------------------- */
        u4_t_gli = u4_g_CANLpFq_IRQ_DI();
        /* --------------------------------------------------------------- */

     /* st_tp_rwct->u2_rea = (U2)0U; */
     /* st_tp_rwct->u2_wri = (U2)0U; */
     /* st_tp_rwct->u2_enq = (U2)0U; */
        u4_tp_rwct_w[CAN_LPFQ_RWCT_WO_0] = (U4)0U;
        u4_tp_rwct_w[CAN_LPFQ_RWCT_WO_1] = (U4)0U;

        /* --------------------------------------------------------------- */
        vd_g_CANLpFq_IRQ_EI(u4_t_gli);
        /* --------------------------------------------------------------- */
    }
}
/*===================================================================================================================================*/
/*  uint8   u1_g_CANLpFqEnqCh(const uint16 u2_a_FQ_CH, const uint32 * u4_ap_CAN)                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
uint8   u1_g_CANLpFqEnqCh(const uint16 u2_a_FQ_CH, const uint32 * u4_ap_CAN)
{
    const ST_CAN_LPFQ_CH *               st_tp_CH;
    const U4 *                           u4_tp_SRC;

    ST_CAN_LPFQ_RWCT *                   st_tp_rwct;
    U4 *                                 u4_tp_que;
    U4 *                                 u4_tp_dst;

    U4                                   u4_t_gli;

    U4                                   u4_t_nque;
    U4                                   u4_t_wri;
    U4                                   u4_t_nb_sdu;
    U4                                   u4_t_nw_can;
    U4                                   u4_t_empt;

    U1                                   u1_t_eas;

    u1_t_eas = (U1)CAN_LPFQ_EAS_REQ_RJCT;

    if((u2_a_FQ_CH <  u2_g_CAN_LPFQ_NUM_CH) &&
       (u4_ap_CAN  != NULL_PTR            )){

        st_tp_CH    = &st_gp_CAN_LPFQ_CH[u2_a_FQ_CH];
        u4_t_nque   = (U4)st_tp_CH->u2_nque;

        u4_t_nb_sdu = u4_ap_CAN[CAN_LPFQ_WO_HEAD] & (U4)CAN_LPFQ_HD_BIT_NB_SDU;
        u4_t_nw_can = u4_CAN_LPFQ_NW_ENQ(u4_t_nb_sdu) + (U4)CAN_LPFQ_WO_SDU_B0;
        if((u4_t_nb_sdu <= (U4)CAN_LPFQ_SDU_NB_MAX) &&
           (u4_t_nw_can <= u4_t_nque              )){

            st_tp_rwct = &st_gp_can_lpfq_rwct[u2_a_FQ_CH];
            u4_tp_que  = st_tp_CH->u4p_QUE;

            /* --------------------------------------------------------------- */
            u4_t_gli = u4_g_CANLpFq_IRQ_DI();
            /* --------------------------------------------------------------- */

            u1_t_eas  = u1_s_CANLpFqRwctOk(u4_t_nque, st_tp_rwct);
            u1_t_eas |= u1_s_CANLpFqFull(u4_t_nw_can, st_tp_CH, st_tp_rwct);
            if(u1_t_eas < (U1)CAN_LPFQ_EAS_REQ_RJCT){

                u4_t_wri  = (U4)st_tp_rwct->u2_wri;
                u4_tp_dst = &u4_tp_que[u4_t_wri];
                u4_t_empt = u4_t_nque - u4_t_wri;
                if(u4_t_empt >= u4_t_nw_can){
                    vd_s_CANLpFqCpyWord(u4_tp_dst, u4_ap_CAN, u4_t_nw_can);
                }
                else{
                    vd_s_CANLpFqCpyWord(u4_tp_dst, u4_ap_CAN, u4_t_empt);
                    u4_tp_SRC = &u4_ap_CAN[u4_t_empt];
                    u4_t_empt = u4_t_nw_can - u4_t_empt;
                    vd_s_CANLpFqCpyWord(u4_tp_que, u4_tp_SRC, u4_t_empt);
                }

                u4_t_wri += u4_t_nw_can;
                if(u4_t_wri >= u4_t_nque){
                    u4_t_wri -= u4_t_nque;
                }
                st_tp_rwct->u2_wri = (U2)u4_t_wri;
            }

            /* --------------------------------------------------------------- */
            vd_g_CANLpFq_IRQ_EI(u4_t_gli);
            /* --------------------------------------------------------------- */
        }
    }

    return(u1_t_eas);
}
/*===================================================================================================================================*/
/*  uint8   u1_g_CANLpFqDeqCh(const uint16 u2_a_FQ_CH, uint32 * u4_ap_can, const uint16 u2_a_NWORD)                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
uint8   u1_g_CANLpFqDeqCh(const uint16 u2_a_FQ_CH, uint32 * u4_ap_can, const uint16 u2_a_NWORD)
{
    const ST_CAN_LPFQ_CH *               st_tp_CH;
    const U4 *                           u4_tp_QUE;
    const U4 *                           u4_tp_SRC;

    ST_CAN_LPFQ_RWCT *                   st_tp_rwct;
    volatile U4 *                        u4_tp_rwct_w;
    U4 *                                 u4_tp_dst;

    U4                                   u4_t_gli;

    U4                                   u4_t_nque;
    U4                                   u4_t_rea;
    U4                                   u4_t_enq;
    U4                                   u4_t_nb_sdu;
    U4                                   u4_t_deq;
    U4                                   u4_t_full;

    U1                                   u1_t_eas;

    u1_t_eas = (U1)CAN_LPFQ_EAS_REQ_RJCT;

    if((u2_a_FQ_CH <  u2_g_CAN_LPFQ_NUM_CH) &&
       (u4_ap_can  != NULL_PTR            )){

        st_tp_CH   = &st_gp_CAN_LPFQ_CH[u2_a_FQ_CH];
        u4_tp_QUE  = st_tp_CH->u4p_QUE;
        u4_t_nque  = (U4)st_tp_CH->u2_nque;

        st_tp_rwct = &st_gp_can_lpfq_rwct[u2_a_FQ_CH];

        /* --------------------------------------------------------------- */
        u4_t_gli = u4_g_CANLpFq_IRQ_DI();
        /* --------------------------------------------------------------- */

        u1_t_eas = u1_s_CANLpFqRwctOk(u4_t_nque, st_tp_rwct);
        u4_t_enq = (U4)st_tp_rwct->u2_enq;
        if(u4_t_enq == (U4)0U){

            u1_t_eas |= ((U1)CAN_LPFQ_EAS_QUE_EMPT | (U1)CAN_LPFQ_EAS_REQ_RJCT);
        }
        else{

            u4_t_rea    = (U4)st_tp_rwct->u2_rea;
            u4_tp_SRC   = &u4_tp_QUE[u4_t_rea];
            u4_t_nb_sdu = u4_tp_SRC[0U] & (U4)CAN_LPFQ_HD_BIT_NB_SDU;
            u4_t_deq    = u4_CAN_LPFQ_NW_DEQ(u4_t_nb_sdu);
            if(u4_t_deq > (U4)u2_a_NWORD){

                u1_t_eas = (U1)CAN_LPFQ_EAS_REQ_RJCT;
            }
            else if(u4_t_nb_sdu > (U4)CAN_LPFQ_SDU_NB_MAX){

                u1_t_eas = ((U1)CAN_LPFQ_EAS_REQ_RJCT |
                            (U1)CAN_LPFQ_EAS_FER_NBSD |
                            (U1)CAN_LPFQ_EAS_QUE_EMPT);

             /* st_tp_rwct->u2_rea = (U2)0U; */
             /* st_tp_rwct->u2_wri = (U2)0U; */
             /* st_tp_rwct->u2_enq = (U2)0U; */
                u4_tp_rwct_w = (volatile U4 *)st_tp_rwct;
                u4_tp_rwct_w[CAN_LPFQ_RWCT_WO_0] = (U4)0U;
                u4_tp_rwct_w[CAN_LPFQ_RWCT_WO_1] = (U4)0U;
            }
            else if(u4_t_enq < u4_t_deq){

                u1_t_eas = ((U1)CAN_LPFQ_EAS_REQ_RJCT |
                            (U1)CAN_LPFQ_EAS_FER_RWCT |
                            (U1)CAN_LPFQ_EAS_FER_NBSD |
                            (U1)CAN_LPFQ_EAS_QUE_EMPT);

             /* st_tp_rwct->u2_rea = (U2)0U; */
             /* st_tp_rwct->u2_wri = (U2)0U; */
             /* st_tp_rwct->u2_enq = (U2)0U; */
                u4_tp_rwct_w = (volatile U4 *)st_tp_rwct;
                u4_tp_rwct_w[CAN_LPFQ_RWCT_WO_0] = (U4)0U;
                u4_tp_rwct_w[CAN_LPFQ_RWCT_WO_1] = (U4)0U;
            }
            else{

                u4_t_full = u4_t_nque - u4_t_rea;
                if(u4_t_full >= u4_t_deq){
                    vd_s_CANLpFqCpyWord(u4_ap_can, u4_tp_SRC, u4_t_deq);
                }
                else{
                    vd_s_CANLpFqCpyWord(u4_ap_can, u4_tp_SRC, u4_t_full);
                    u4_tp_dst = &u4_ap_can[u4_t_full];
                    u4_t_full = u4_t_deq - u4_t_full;
                    vd_s_CANLpFqCpyWord(u4_tp_dst, u4_tp_QUE, u4_t_full);
                }

                if(u4_t_enq == u4_t_deq){

                 /* st_tp_rwct->u2_rea = (U2)0U; */
                 /* st_tp_rwct->u2_wri = (U2)0U; */
                 /* st_tp_rwct->u2_enq = (U2)0U; */
                    u4_tp_rwct_w = (volatile U4 *)st_tp_rwct;
                    u4_tp_rwct_w[CAN_LPFQ_RWCT_WO_0] = (U4)0U;
                    u4_tp_rwct_w[CAN_LPFQ_RWCT_WO_1] = (U4)0U;
                }
                else{

                    u4_t_rea += u4_t_deq;
                    if(u4_t_rea >= u4_t_nque){
                        u4_t_rea -= u4_t_nque;
                    }
                    st_tp_rwct->u2_rea = (U2)u4_t_rea;
                    st_tp_rwct->u2_enq = (U2)(u4_t_enq - u4_t_deq);
                }
            }
        }

        /* --------------------------------------------------------------- */
        vd_g_CANLpFq_IRQ_EI(u4_t_gli);
        /* --------------------------------------------------------------- */
    }

    return(u1_t_eas);
}
/*===================================================================================================================================*/
/*  uint8   u1_g_CANLpFqEnqCAN(const uint16 u2_a_FQ_CH, const uint16 u2_a_PDU_ID, const CanMsgType * const st_ap_CAN)                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
uint8   u1_g_CANLpFqEnqCAN(const uint16 u2_a_FQ_CH, const uint16 u2_a_PDU_ID, const CanMsgType * const st_ap_CAN)
{
    const ST_CAN_LPFQ_CH *               st_tp_CH;
    const U4 *                           u4_tp_SRC;

    ST_CAN_LPFQ_RWCT *                   st_tp_rwct;
    U4 *                                 u4_tp_que;
    U4 *                                 u4_tp_dst;

    U4                                   u4_t_gli;

    U4                                   u4_t_align;
    U4                                   u4_t_head;
    U4                                   u4_t_nw_sdu;
    U4                                   u4_t_nw_can;
    U4                                   u4_t_can_id;

    U4                                   u4_t_nque;
    U4                                   u4_t_wri;
    U4                                   u4_t_empt;

    U1                                   u1_t_eas;

    u1_t_eas = (U1)CAN_LPFQ_EAS_REQ_RJCT;

    if((u2_a_FQ_CH <  u2_g_CAN_LPFQ_NUM_CH) &&
       (st_ap_CAN  != NULL_PTR            )){

        st_tp_CH    = &st_gp_CAN_LPFQ_CH[u2_a_FQ_CH];
        u4_t_nque   = (U4)st_tp_CH->u2_nque;

        u4_t_align  = (U4)st_ap_CAN->ptData & (U4)0x00000003U;   /* Intentional Statement "U1 * " cast to "U4" */ 
        u4_t_head   = (U4)st_ap_CAN->u1Length;
        u4_t_nw_sdu = u4_CAN_LPFQ_NW_ENQ(u4_t_head);
        u4_t_nw_can = u4_t_nw_sdu + (U4)CAN_LPFQ_WO_SDU_B0;
        if((u4_t_align  == (U4)0U                 ) &&
           (u4_t_head   <= (U4)CAN_LPFQ_SDU_NB_MAX) &&
           (u4_t_nw_can <= u4_t_nque              )){

            u4_tp_SRC    = (const U4 * )st_ap_CAN->ptData;

            u4_t_can_id  = st_ap_CAN->u4Id;
            u4_t_head   |= ((U4)u2_a_PDU_ID << CAN_LPFQ_HD_LSB_PDU_ID);
            st_tp_rwct   = &st_gp_can_lpfq_rwct[u2_a_FQ_CH];
            u4_tp_que    = st_tp_CH->u4p_QUE;

            /* --------------------------------------------------------------- */
            u4_t_gli = u4_g_CANLpFq_IRQ_DI();
            /* --------------------------------------------------------------- */

            u1_t_eas  = u1_s_CANLpFqRwctOk(u4_t_nque, st_tp_rwct);
            u1_t_eas |= u1_s_CANLpFqFull(u4_t_nw_can, st_tp_CH, st_tp_rwct);
            if(u1_t_eas < (U1)CAN_LPFQ_EAS_REQ_RJCT){

                u4_t_wri  = (U4)st_tp_rwct->u2_wri;
                u4_tp_dst = &u4_tp_que[u4_t_wri];
                u4_t_empt = u4_t_nque - u4_t_wri;
                if(u4_t_empt >= u4_t_nw_can){
                    u4_tp_dst[CAN_LPFQ_WO_HEAD]   = u4_t_head;
                    u4_tp_dst[CAN_LPFQ_WO_CAN_ID] = u4_t_can_id;
                    vd_s_CANLpFqCpyWord(&u4_tp_dst[CAN_LPFQ_WO_SDU_B0], u4_tp_SRC, u4_t_nw_sdu);
                }
                else if(u4_t_empt > (U4)CAN_LPFQ_WO_SDU_B0){
                    u4_tp_dst[CAN_LPFQ_WO_HEAD]   = u4_t_head;
                    u4_tp_dst[CAN_LPFQ_WO_CAN_ID] = u4_t_can_id;
                    u4_t_empt                     = u4_t_empt - (U4)CAN_LPFQ_WO_SDU_B0;
                    vd_s_CANLpFqCpyWord(&u4_tp_dst[CAN_LPFQ_WO_SDU_B0], u4_tp_SRC, u4_t_empt);
                    u4_tp_SRC                     = &u4_tp_SRC[u4_t_empt];
                    u4_t_empt                     = u4_t_nw_sdu - u4_t_empt;
                    vd_s_CANLpFqCpyWord(u4_tp_que, u4_tp_SRC, u4_t_empt);
                }
                else if(u4_t_empt >= (U4)CAN_LPFQ_WO_SDU_B0){
                    u4_tp_dst[CAN_LPFQ_WO_HEAD]   = u4_t_head;
                    u4_tp_dst[CAN_LPFQ_WO_CAN_ID] = u4_t_can_id;
                    vd_s_CANLpFqCpyWord(u4_tp_que, u4_tp_SRC, u4_t_nw_sdu);
                }
                else{
                    u4_tp_dst[CAN_LPFQ_WO_HEAD]   = u4_t_head;
                    u4_tp_que[0U]                 = u4_t_can_id;
                    vd_s_CANLpFqCpyWord(&u4_tp_que[1U], u4_tp_SRC, u4_t_nw_sdu);
                }

                u4_t_wri += u4_t_nw_can;
                if(u4_t_wri >= u4_t_nque){
                    u4_t_wri -= u4_t_nque;
                }
                st_tp_rwct->u2_wri = (U2)u4_t_wri;
            }

            /* --------------------------------------------------------------- */
            vd_g_CANLpFq_IRQ_EI(u4_t_gli);
            /* --------------------------------------------------------------- */
        }
    }

    return(u1_t_eas);
}
/*===================================================================================================================================*/
/*  static inline U1      u1_s_CANLpFqRwctOk(const U4 u4_a_NQUE, ST_CAN_LPFQ_RWCT * st_ap_rwct)                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline U1      u1_s_CANLpFqRwctOk(const U4 u4_a_NQUE, ST_CAN_LPFQ_RWCT * st_ap_rwct)
{
    volatile U4 *                        u4_tp_rwct_w;

    U4                                   u4_t_rea;
    U4                                   u4_t_wri;
    U4                                   u4_t_enq;
    U4                                   u4_t_cmpr;
    U1                                   u1_t_eas;

    u4_t_rea  = (U4)st_ap_rwct->u2_rea;
    u4_t_wri  = (U4)st_ap_rwct->u2_wri;
    u4_t_enq  = (U4)st_ap_rwct->u2_enq;

    u4_t_cmpr = u4_t_rea + u4_t_enq;
    if(u4_t_cmpr >= u4_a_NQUE){
        u4_t_cmpr -= u4_a_NQUE;
    }
    if((u4_t_rea  <  u4_a_NQUE) &&
       (u4_t_wri  <  u4_a_NQUE) &&
       (u4_t_enq  <= u4_a_NQUE) &&
       (u4_t_cmpr == u4_t_wri )){

        u1_t_eas = (U1)CAN_LPFQ_EAS_REQ_ACPT;
    }
    else{
        u1_t_eas = (U1)CAN_LPFQ_EAS_FER_RWCT;

     /* st_ap_rwct->u2_rea = (U2)0U; */
     /* st_ap_rwct->u2_wri = (U2)0U; */
     /* st_ap_rwct->u2_enq = (U2)0U; */
        u4_tp_rwct_w = (volatile U4 *)st_ap_rwct;
        u4_tp_rwct_w[CAN_LPFQ_RWCT_WO_0] = (U4)0U;
        u4_tp_rwct_w[CAN_LPFQ_RWCT_WO_1] = (U4)0U;
    }

    return(u1_t_eas);
}
/*===================================================================================================================================*/
/*  static inline U1      u1_s_CANLpFqFull(const U4 u4_a_NW_CAN, const ST_CAN_LPFQ_CH * st_ap_CH, ST_CAN_LPFQ_RWCT * st_ap_rwct)     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline U1      u1_s_CANLpFqFull(const U4 u4_a_NW_CAN, const ST_CAN_LPFQ_CH * st_ap_CH, ST_CAN_LPFQ_RWCT * st_ap_rwct)
{
    const U4 *                           u4_tp_QUE;

    U4                                   u4_t_nque;
    U4                                   u4_t_last;
    U4                                   u4_t_next;
    U4                                   u4_t_rea;
    U4                                   u4_t_deq;
    U4                                   u4_t_min;
    U4                                   u4_t_nb;
    U4                                   u4_t_nw;
    U1                                   u1_t_eas;

    u4_t_nque = (U4)st_ap_CH->u2_nque;
    u4_t_last = (U4)st_ap_rwct->u2_enq; 
    u4_t_next = u4_t_last + u4_a_NW_CAN;
    if(u4_t_next <= u4_t_nque){

        st_ap_rwct->u2_enq = (U2)u4_t_next;
        u1_t_eas = (U1)CAN_LPFQ_EAS_REQ_ACPT;
    }
    else if(st_ap_CH->u2_ovwr != (U2)CAN_LPFQ_OVWR_EN){

        u1_t_eas = (U1)CAN_LPFQ_EAS_REQ_RJCT | (U1)CAN_LPFQ_EAS_QUE_FULL;
    }
    else{

        u4_tp_QUE = st_ap_CH->u4p_QUE;
        u4_t_rea  = (U4)st_ap_rwct->u2_rea;
        u4_t_deq  = 0U;
        u4_t_min  = u4_t_next - u4_t_nque;
        do{
            u4_t_nb = u4_tp_QUE[u4_t_rea] & (U4)CAN_LPFQ_HD_BIT_NB_SDU;
            if(u4_t_nb > (U4)CAN_LPFQ_SDU_NB_MAX){
                u4_t_deq = (U4)CAN_LPFQ_RWCT_UNK;
            }
            else{
                u4_t_nw   = u4_CAN_LPFQ_NW_DEQ(u4_t_nb);
                u4_t_deq += u4_t_nw;
                u4_t_rea += u4_t_nw;
                if(u4_t_rea >= u4_t_nque){
                    u4_t_rea -= u4_t_nque;
                }
            }
        }
        while(u4_t_deq < u4_t_min);

        if(u4_t_deq >= u4_t_last){
            st_ap_rwct->u2_rea = (U2)0U;
            st_ap_rwct->u2_wri = (U2)0U;
            st_ap_rwct->u2_enq = (U2)u4_a_NW_CAN;
        }
        else{
            st_ap_rwct->u2_rea = (U2)u4_t_rea;
            st_ap_rwct->u2_enq = (U2)(u4_t_next - u4_t_deq);
        }

        u1_t_eas = (U1)CAN_LPFQ_EAS_QUE_OVWR;
    }

    return(u1_t_eas);
}
/*===================================================================================================================================*/
/*  static inline void    vd_s_CANLpFqCpyWord(U4 * u4_ap_dst, const U4 * u4_ap_SRC, const U4 u4_a_NWORD)                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_CANLpFqCpyWord(U4 * u4_ap_dst, const U4 * u4_ap_SRC, const U4 u4_a_NWORD)
{
    U4                                   u4_t_lpcnt;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < u4_a_NWORD; u4_t_lpcnt++){
        u4_ap_dst[u4_t_lpcnt] = u4_ap_SRC[u4_t_lpcnt];
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
/*  1.0.0     3/18/2025  TN       New.                                                                                               */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
