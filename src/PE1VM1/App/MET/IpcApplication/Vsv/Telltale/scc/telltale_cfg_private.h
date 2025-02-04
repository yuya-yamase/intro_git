/* 5.5.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Telltale                                                                                                                         */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef TELLTALE_CFG_H
#define TELLTALE_CFG_H
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TELLTALE_CFG_H_MAJOR                     (5)
#define TELLTALE_CFG_H_MINOR                     (5)
#define TELLTALE_CFG_H_PATCH                     (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "telltale.h"
#include "telltale_blinkid.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TT_MAINTICK                         (10U)
#define TT_OPD_HOLD                         (U2_MAX)
#define TT_BLINK_ELAPS_MAX                  (0xfffeU)        /* TT_OPD_HOLD - 1 */

#define TT_DID_BPOS                         (8U)
#define TT_IOR_BITMASK                      (0x00ffU)

#define TT_OW_TOC_MAX                       (0xfffeU)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define u1_TT_ID2DID(u2_id)    (U1)(((u2_id) >> TT_DID_BPOS) & (U2)U1_MAX)
#define u4_TT_ID2BIT(u2_id)    ((U4)1U << (((u2_id)  & (U2)U1_MAX)))

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U1                          u1_blink;
    U1                          u1_act;
    U1                          u1_step_cnt;
    U1                          u1_cycl_cnt;
    U2                          u2_elapstim;
}ST_TT_CTLSTS;

typedef struct{
    U1                          u1_act;                     /* TRUE:Light on, FALSE:Light off                               */
    U2                          u2_dur;                     /* Duration of the state of u1_act                              */
                                                            /* !! Do not configure u2_dur to 0. Must be 1 or more !!        */
}ST_TT_OPD;

typedef struct{
    const  ST_TT_OPD * const    stp_OPD;                    /* Output Pulse Duratoin                                        */
    U1                          u1_num_opd;                 /* Number of stp_OPD                                            */
                                                            /* !! Do not configure u1_num_opd to 0. Must be 1 or more !!    */
    U1                          u1_min_cycl;                /* Minimum number of sequence playback. If u1_min_cycl=0,       */
                                                            /* Switch immediately without completing the sequence           */
    U1                          u1_swc_cycl;                /* Switch at the timing of the end of the cycle                 */
                                                            /* TRUE:Even if there is a request to turn off while blinking,  */
                                                            /*      it continues until the end of the cycle                 */
}ST_TT_BLINK;

typedef struct{
    U2                          u2_ior;                                         /* I/O Request                  */
    U1    (* const              fp_u1_REQ)(const U1 u1_a_LAS , U1 * u1p_rtrg);  /* vdp_PTR_NA : Always Light Off      */
    U1    (* const              fp_u1_SUP)(void);                               /* vdp_PTR_NA : Always Support        */
}ST_TT_REQ;

typedef struct{
    U4                          u4_light;
    U4                          u4_sup;
    U4                          u4_unlock;
    U4                          u4_ow_act;
    U4                          u4_ow_ch;
    U2                          u2_tout;
}ST_TT;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern  ST_TT_CTLSTS    st_gp_tt_ctlsts[];
extern  ST_TT           st_gp_tt[];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void    vd_g_TelltaleCfgInit(void);
void    vd_g_TelltaleCfgMainStart(void);
void    vd_g_TelltaleCfgMainFinish(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern const U1             u1_g_TT_NUM_SYM;
extern const U1             u1_g_TT_NUM_BLINK;
extern const U2             u2_g_TT_OW_TOUT;

extern const ST_TT_REQ      st_gp_TT_REQ[];
extern const ST_TT_BLINK    st_gp_TT_BLINK[];

extern const U1             u1_g_TT_NUM_DID;
extern const U2             u2_g_TT_IOR_D2981_B06_7_ALLON;
#endif    /* TELLTALE_CFG_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  telltale.c                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
