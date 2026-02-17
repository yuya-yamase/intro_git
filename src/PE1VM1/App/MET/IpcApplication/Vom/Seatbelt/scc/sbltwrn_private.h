/* 3.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Seatbelt reminder warning                                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef SBLTWRN_PRIVATE_H
#define SBLTWRN_PRIVATE_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define SBLTWRN_PRIVATE_H_MAJOR                 (3)
#define SBLTWRN_PRIVATE_H_MINOR                 (1)
#define SBLTWRN_PRIVATE_H_PATCH                 (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "sbltwrn_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define     SBLTWRN_NUM_SEATTYP                 (5U)            /* A number of seat type */
#define     SBLTWRN_SEATTYP_UNDEF               (0U)            /* Undefined */
#define     SBLTWRN_SEATTYP_DS                  (1U)            /* D-Seat */
#define     SBLTWRN_SEATTYP_PS                  (2U)            /* P-Seat */
#define     SBLTWRN_SEATTYP_RS_SNSR             (3U)            /* Rr-Seat (with occupant detection sensor) */
#define     SBLTWRN_SEATTYP_RS_NOSN             (4U)            /* Rr-Seat (without occupant detection sensor) */

#define     SBLTWRN_SEATTYPBIT_DS               (0x02U)
#define     SBLTWRN_SEATTYPBIT_PS               (0x04U)
#define     SBLTWRN_SEATTYPBIT_FR_ALL           (SBLTWRN_SEATTYPBIT_DS | SBLTWRN_SEATTYPBIT_PS)
#define     SBLTWRN_SEATTYPBIT_RS_SNSR          (0x08U)
#define     SBLTWRN_SEATTYPBIT_RS_NOSN          (0x10U)
#define     SBLTWRN_SEATTYPBIT_RS_ALL           (SBLTWRN_SEATTYPBIT_RS_SNSR | SBLTWRN_SEATTYPBIT_RS_NOSN)

#define     SBLTWRN_CTLOPT_NON                  (0x00000000U)   /* No ctlopt */
#define     SBLTWRN_CTLOPT_PRKWRN               (0x00000001U)   /* Continue a seatbelt warning when the vehicle is parked */

#define     SBLTWRN_CMNOPT_NON                  (0x00000000U)   /* No cmnopt */
#define     SBLTWRN_CMNOPT_TTBKLEDG_ENA         (0x00000001U)   /* Rear TT turns on when other rear belt is buckled */
#define     SBLTWRN_CMNOPT_SNSR_L2CMP_ON        (0x00000002U)   /* Rear TT turns on when rear warn state is L2CMP (w/i seatsnsr) */
#define     SBLTWRN_CMNOPT_NOSN_L2CMP_ON        (0x00000004U)   /* Rear TT turns on when rear warn state is L2CMP (w/o seatsnsr) */

#define     SBLTWRN_NUM_TIM                     (12U)            /* A number of definition of time */
#define     SBLTWRN_TIM_LGLST                   (0U)
#define     SBLTWRN_TIM_LGLTO                   (1U)
#define     SBLTWRN_TIM_GP                      (2U)
#define     SBLTWRN_TIM_LV1                     (3U)
#define     SBLTWRN_TIM_LV2                     (4U)
#define     SBLTWRN_TIM_IGON                    (5U)
#define     SBLTWRN_TIM_DOOR                    (6U)
#define     SBLTWRN_TIM_TTON                    (7U)
#define     SBLTWRN_TIM_TTBKLEDG                (8U)
#define     SBLTWRN_TIM_INITIAL                 (9U)
#define     SBLTWRN_TIM_UNBCKL                  (10U)
#define     SBLTWRN_TIM_LV2CNT                  (11U)

#define     SBLTWRN_TT_IGONTM_OFST              (500U/SBLTWRN_TICK)     /* Additional time to guarantee IG-ON Telltale keeps turning on 66 sec */

#define     SBLTWRN_CHM_SYNCCND_CHK             (0x8000U)       /* Sync status with other seats (for chime)    */
#define     SBLTWRN_TT_SYNCCND_CHK              (0x80000000U)   /* Sync status with other seats (for telltale) */

#define     SBLTWRN_SBRBIT_IDX_ALL              (2U)
#define     SBLTWRN_SBRBIT_IDX0                 (0U)
#define     SBLTWRN_SBRBIT_IDX1                 (1U)

#define     SBLTWRN_NUM_3ROWSEAT                (9U)
#define     SBLTWRN_DRV_SEAT_BIT_IDX_ALL        (0xFFU)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* 'Per-Seat' parameter */
typedef struct {
    U4          u4_ctlopt;  /* SBLTWRN_CTLOPT_xxx */
    U2          u2p_tim[SBLTWRN_NUM_TIM];
} ST_SBLTWRN_WRNPRM;

/* Common parameter */
typedef struct {
    U4          u4_cmnopt;  /* SBLTWRN_CMNOPT_xxx */
    U2          u2p_spd[SBLTWRN_NUM_SPD];
} ST_SBLTWRN_VCLPRM;

typedef struct {
    const ST_SBLTWRN_WRNPRM     *stp_wrnprm;    /* WRNPRM array pointer (ordered by seattyp) */
    const ST_SBLTWRN_VCLPRM     *stp_vclprm;    /* VCLPRM pointer */
    U4                          u4_vclsts;      /* vehicle status (SBLTWRN_VCLSTS_xxx) */
    U2                          u2_igontm;      /* the time after IG-ON */
    U2                          u2_bkledgtmr;   /* the time after some rear seats are buckled */
    U1                          u1p_bklsts[SBLTWRN_NUM_ALLSEAT]; /* buckle status (SBLTWRN_BKLSTS_xxx) */
} ST_SBLTWRN_VCLST;

typedef U4 ( * SBLTWRN_CHMTYP)(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U2 u2_a_SYNC_TRGT);
typedef U4 SBLTWRN_TTSTM(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS, const U4 u4_a_SYNC_TRGT);

typedef struct {
    const SBLTWRN_CHMTYP *      fp_u4_CHMTYP;     /* State Transition Judgement */
    const U1                    u1_NUM_CHMTYP;
} ST_SBLTWRN_CHMTYP;

typedef struct {
    const SBLTWRN_TTSTM *       fp_u4_STM;     /* State Transition Judgement */
    const U1                    u1_TYPMSK;      /* Seattype Mask              */
} ST_SBLTWRN_TT_STM;

typedef struct {
    const ST_SBLTWRN_TT_STM *   st_TTSTM;     /* State Transition Judgement */
    const U1                    u1_NUM_TTTYP;
} ST_SBLTWRN_TTTYP;

typedef struct{
    U1  u1_idx;
    U1  u1_wrtbit;
} ST_SBLTWRN_STSTBL;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void    vd_g_SbltwrnInit_FM(void);
void    vd_g_SbltwrnTrans_FM(const U1 u1_a_DSTTYP);
U1      u1_g_SbltwrnChmStmVldChk(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS);
U1      u1_g_SbltwrnDrchk(const U4 u4_a_VCLSTS, const U1 u1_a_SEATTYP, const U1 u1_a_ANYDR);
U1      u1_g_SbltwrnSeatTyp(const U1 u1_a_SEATID);
void    vd_g_SbltwrnSeatsts(const U4 u4_a_VCLSTS, const U1 *u1_ap_MSGSTS, U1 *u1_ap_bklsts);
void    vd_g_SbltwrnMsgsts(const U1 u1_a_IGON, U1 *u1_ap_msgsts);
void    vd_g_SbltwrnTmcnt(U2* u2p_a_timer);
void    vd_g_SbltwrnGetCalibSupd(void);
void    vd_g_GetSbltwrnSbrbit(U1 *u1_ap_sbrbit);
void    vd_g_SetSbltwrnSbrbit(U1 *u1_ap_sbrbit);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern const ST_SBLTWRN_WRNPRM * const st_gp_SBLTWRN_WRNPRM[];
extern const ST_SBLTWRN_VCLPRM st_gp_SBLTWRN_VCLPRM[];
extern const ST_SBLTWRN_STSTBL st_gp_SBLTWRN_SBR_STSTBL[];

#endif /* SBLTWRN_PRIVATE_H */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  sbltwrn.c                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/
