/* 2.2.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Seatbelt reminder warning                                                                                                        */
/*  D/P/R seat information                                                                                                           */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define SBLT_SEAT_C_MAJOR                       (2)
#define SBLT_SEAT_C_MINOR                       (2)
#define SBLT_SEAT_C_PATCH                       (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "sblt_seat_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((SBLT_SEAT_C_MAJOR != SBLT_SEAT_H_MAJOR) || \
     (SBLT_SEAT_C_MINOR != SBLT_SEAT_H_MINOR) || \
     (SBLT_SEAT_C_PATCH != SBLT_SEAT_H_PATCH))
#error "sblt_seat.c and sblt_seat.h : source and header files are inconsistent!"
#endif

#if ((SBLT_SEAT_C_MAJOR != SBLT_SEAT_CFG_PRIVATE_H_MAJOR) || \
     (SBLT_SEAT_C_MINOR != SBLT_SEAT_CFG_PRIVATE_H_MINOR) || \
     (SBLT_SEAT_C_PATCH != SBLT_SEAT_CFG_PRIVATE_H_PATCH))
#error "sblt_seat.c and sblt_seat_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define SBLT_SEAT_SIGRANGE                      (0x03U)

#define SBLT_SEAT_TX_XBKLMET_BCKL               (0x00U)     /* *BKL_MET value: Buckled          */
#define SBLT_SEAT_TX_XBKLMET_UNBCKL             (0x01U)     /* *BKL_MET value: Unbuckled        */
#define SBLT_SEAT_TX_XBKLMET_UNKNWN             (0x02U)     /* *BKL_MET value: Unknown status   */
#define SBLT_SEAT_TX_XBKLMET_MALFNC             (0x03U)     /* *BKL_MET value: Malfunction      */

#define SBLT_SEAT_SNSR_UNBCKL                   (SBLTWRN_BKLSTS_UNBCKL | SBLTWRN_BKLSTS_UNBCKLFLG)

#define SBLTSEAT_DLYLST_NUM                     (10U)       /* A number of delay-list     */
#define SBLTSEAT_DLYLST_IDX_POSW                (0U)        /* Delay idx of POSW          */
#define SBLTSEAT_DLYLST_IDX_CFOSW               (1U)        /* Delay idx of CFOSW         */
#define SBLTSEAT_DLYLST_IDX_PBKLPDC             (2U)        /* Delay idx of PBKLPDC       */
#define SBLTSEAT_DLYLST_IDX_CFBCKL              (3U)        /* Delay idx of CFBCKL        */
#define SBLTSEAT_DLYLST_IDX_RXBKLPDC            (4U)        /* Delay idx of R*BKLPDC (An occupant SW exists) */
#define SBLTSEAT_DLYLST_IDX_RXOSW               (5U)        /* Delay idx of R*OSW         */
#define SBLTSEAT_DLYLST_IDX_XRXBKL              (6U)        /* Delay idx of *R*BKL (An occupant SW exists) */
#define SBLTSEAT_DLYLST_IDX_RXXOSW              (7U)        /* Delay idx of R**OSW        */
#define SBLTSEAT_DLYLST_IDX_RXBKLPDC_NOSN       (8U)        /* Delay idx of R*BKLPDC (An occupant SW doesn't exist) */
#define SBLTSEAT_DLYLST_IDX_XRXBKL_NOSN         (9U)        /* Delay idx of *R*BKL (An occupant SW doesn't exist) */

#define SBLT_SEAT_DBSWSTS_BUCKLED               (0x00U)     /* DBSW state: Buckled      */
#define SBLT_SEAT_DBSWSTS_UNBUCKLED             (0x01U)     /* DBSW state: Unbucked     */
#define SBLT_SEAT_DBSWSTS_UNKNOWN               (0x02U)     /* DBSW state: Unknown      */

#define SBLT_SEAT_PBKLPDCSTS_BUCKLED            (0x00U)     /* PBKL_PDC state: Buckled      */
#define SBLT_SEAT_PBKLPDCSTS_UNBUCKLED          (0x01U)     /* PBKL_PDC state: Unbuckled    */
#define SBLT_SEAT_PBKLPDCSTS_UNKNOWN            (0x02U)     /* PBKL_PDC state: Undetermined */
#define SBLT_SEAT_PBKLPDCSTS_UNDEFINED          (0x03U)     /* PBKL_PDC state: Undefined    */

#define SBLT_SEAT_CFBCKLSTS_BUCKLED             (0x00U)     /* CFBCKL  state: Buckled      */
#define SBLT_SEAT_CFBCKLSTS_UNBUCKLED           (0x01U)     /* CFBCKL  state: Unbuckled    */
#define SBLT_SEAT_CFBCKLSTS_UNKNOWN             (0x02U)     /* CFBCKL  state: Undetermined */
#define SBLT_SEAT_CFBCKLSTS_UNDEFINED           (0x03U)     /* CFBCKL  state: Undefined    */

#define SBLT_SEAT_RXBKLPDCSTS_BUCKLED           (0x00U)     /* R*BKLPDC state: Buckled      */
#define SBLT_SEAT_RXBKLPDCSTS_UNBUCKLED         (0x01U)     /* R*BKLPDC state: Unbuckled    */
#define SBLT_SEAT_RXBKLPDCSTS_UNKNOWN           (0x02U)     /* R*BKLPDC state: Undetermined */
#define SBLT_SEAT_RXBKLPDCSTS_UNDEFINED         (0x03U)     /* R*BKLPDC state: Undefined    */

#define SBLT_SEAT_XRXBKLSTS_BUCKLED             (0x00U)     /* *R*BKL state: Buckled        */
#define SBLT_SEAT_XRXBKLSTS_UNBUCKLED           (0x01U)     /* *R*BKL state: Unbuckled      */
#define SBLT_SEAT_XRXBKLSTS_UNKNOWN             (0x02U)     /* *R*BKL state: Undetermined   */
#define SBLT_SEAT_XRXBKLSTS_UNDEFINED           (0x03U)     /* *R*BKL state: Undefined      */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct {
    U2  u2_cnt;         /* A Buckle state determination delay counter   */
    U2  u2_osw_cnt;     /* An occupant detection state delay counter    */
    U1  u1_msksig;      /* A Buckle state set during delaying           */
    U1  u1_mskoswsig;   /* An occupant state set during delaying        */
    U1  u1_prvsig;      /* A previous value of buckle signal            */
    U1  u1_prvoswsig;   /* An occupant value of buckle signal           */
    U1  u1_prvsts;      /* A previous state                             */
    U1  u1_defined;     /* The flag a buckle state has determinated since IG-ON (for non-snsr seat) */
} ST_SBLT_SEAT;

typedef struct {
    U1  u1_jdgval;      /* judgement value   */
    U2  u2_dlycnt;      /* delay time        */
} ST_SBLTSEAT_DLYCFG;

typedef struct {
    U1  u1_bltwrn;      /* For unbuckle warning (Telltale/Buzzer)   */
    U1  u1_cantx;       /* For Buckle SW Signal (*BKL_PDC)          */
} ST_SBLTSEAT_INPTSIG;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  ST_SBLT_SEAT                    st_sp_sblt_seat[SBLTWRN_NUM_ALLSEAT];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  void    vd_s_SbltSeatStsInit(ST_SBLT_SEAT *st_ap_sblt_seat);
static  U1      u1_s_SbltRsBklstsJdg(const U4 u4_a_SEATID, const U1 u1_a_BKLINPT, const U1 u1_a_OSWSTS, const U1 u1_a_RRSNSRTYP);
static  U1      u1_s_SbltRsXBklstsJdg(const U4 u4_a_SEATID, const U1 u1_a_BKLINPT, const U1 u1_a_OSWSTS, const U1 u1_a_RRSNSRTYP);
static  U1      u1_s_SbltRsUnbkleFlg(const U4 u4_a_SEATID);
static  U1      u1_s_SbltRsCAN(const U1 * u1_ap_MSGSTS, const U4 u4_a_SEATID, const U4 u4_a_VCLSTS, const U1 u1_a_SNSR);
static  U1      u1_s_SbltRsXCAN(const U1 * u1_ap_MSGSTS, const U4 u4_a_SEATID, const U4 u4_a_VCLSTS, const U1 u1_a_SNSR);
static  void    vd_s_SbltGetCanSgnl(U1 * u1p_a_sgnl, const U1 u1_a_MSGSTS);
static  void    vd_s_SbltInptDly(U1 *u1p_a_sgnl, U1 *u1p_a_prvsgnl, U2 *u2p_a_cnt, U1 u1_a_dlyidx);
static  U1      u1_s_SbltRsNosnBklEdg(const U4 u4_a_SEATID);
static  U1      u1_s_SbltRsSnsrBklEdg(const U4 u4_a_SEATID, const U1 u1_a_BKLINPT, const U1 u1_a_OSWSTS);
static  U1      u1_s_SbltRsXSnsrBklEdg(const U4 u4_a_SEATID, const U1 u1_a_BKLINPT, const U1 u1_a_OSWSTS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  U1      ( * const               fp_sp_u1_SBLT_SEATSIG_RXBKLPDC[SBLTWRN_NUM_ALLSEAT])(void) = {  /* Receive a R*BKLPDC signal */
    vdp_PTR_NA,                  vdp_PTR_NA,                  vdp_PTR_NA,
    &u1_g_SbltRsCfgGetRLBKLPDC,  &u1_g_SbltRsCfgGetRCBKLPDC,  &u1_g_SbltRsCfgGetRRBKLPDC,
    &u1_g_SbltRsCfgGetLR2BCKL,   &u1_g_SbltRsCfgGetCR2BCKL,   &u1_g_SbltRsCfgGetRR2BCKL,
    &u1_g_SbltRsCfgGetLR3BCKL,   &u1_g_SbltRsCfgGetCR3BCKL,   &u1_g_SbltRsCfgGetRR3BCKL
};
static  U1      ( * const               fp_sp_u1_SBLT_SEATSIG_RXOSW[SBLTWRN_NUM_ALLSEAT])(void) = {     /* Receive a R*OSW signal */
    vdp_PTR_NA,                  vdp_PTR_NA,                  vdp_PTR_NA,
    &u1_g_SbltRsCfgGetRLOSW,     &u1_g_SbltRsCfgGetRCOSW,     &u1_g_SbltRsCfgGetRROSW,
    &u1_g_SbltRsCfgGetRL2OSW,    &u1_g_SbltRsCfgGetRC2OSW,    &u1_g_SbltRsCfgGetRR2OSW,
    &u1_g_SbltRsCfgGetRL3OSW,    &u1_g_SbltRsCfgGetRC3OSW,    &u1_g_SbltRsCfgGetRR3OSW
};
static  void    ( * const               fp_sp_vd_SBLT_SEATSIG_RXBKLMET[SBLTWRN_NUM_ALLSEAT])(const U1 u1_a_sig, const U1 u1_a_EVENT_SEND) = {  /* Transmit a R*BKLMET signal */
    vdp_PTR_NA,                  vdp_PTR_NA,                  vdp_PTR_NA,
    &vd_g_SbltRsCfgTxRLBKLMET,   &vd_g_SbltRsCfgTxRCBKLMET,   &vd_g_SbltRsCfgTxRRBKLMET,
    &vd_g_SbltRsCfgTxBKL3LMET,   &vd_g_SbltRsCfgTxBKL3CMET,   &vd_g_SbltRsCfgTxBKL3RMET,
    vdp_PTR_NA,                  vdp_PTR_NA,                  vdp_PTR_NA
};


static const ST_SBLTSEAT_DLYCFG       st_s_SBLTSEAT_DLY_POSW[] = {          /* A delay-time definition of POSW (P-Seat Occupant SW) signal  */
   /* u1_jdgval         u2_dlycnt          */
   { (U1)0x01U,   (U2)((800U/SBLTWRN_TICK)+1U)   }   /*  [T31]   */
};

static const ST_SBLTSEAT_DLYCFG       st_s_SBLTSEAT_DLY_CFOSW[] = {         /* A delay-time definition of CFOSW (FC-Seat Occupant SW) signal */
   /* u1_jdgval         u2_dlycnt          */
   { (U1)0x01U,   (U2)((800U/SBLTWRN_TICK)+1U)   }   /*  [T31]   */
};

static const ST_SBLTSEAT_DLYCFG       st_s_SBLTSEAT_DLY_PBKLPDC[] = {       /* A delay-time definition of PBKL_PDC (P-Seat Bkl SW) signal   */
   /* u1_jdgval         u2_dlycnt          */
   { (U1)0x01U,   (U2)((400U/SBLTWRN_TICK)+1U)   }   /*  [T30]   */
};

static const ST_SBLTSEAT_DLYCFG       st_s_SBLTSEAT_DLY_CFBCKL[] = {        /* A delay-time definition of CFBCKL (FC-Seat Bkl SW) signal    */
   /* u1_jdgval         u2_dlycnt          */
   { (U1)0x01U,   (U2)((400U/SBLTWRN_TICK)+1U)   }   /*  [T30]   */
};

static const ST_SBLTSEAT_DLYCFG       st_s_SBLTSEAT_DLY_RXBKLPDC[] = {      /* A delay-time definition of R*BKLPDC (R-Seat Bkl SW) signal   */
   /* u1_jdgval         u2_dlycnt          */
   { (U1)0x01U,   (U2)((400U/SBLTWRN_TICK)+1U)   }   /*  [T32]   */
};

static const ST_SBLTSEAT_DLYCFG       st_s_SBLTSEAT_DLY_RXOSW[] = {         /* A delay-time definition of R*OSW (R-Seat Occupant SW) signal  */
   /* u1_jdgval         u2_dlycnt          */
   { (U1)0x01U,   (U2)((800U/SBLTWRN_TICK)+1U)   }   /*  [T33]   */
};

static const ST_SBLTSEAT_DLYCFG       st_s_SBLTSEAT_DLY_XRXBKL[] = {        /* A delay-time definition of *R*BKL (R-Seat Bkl SW) signal      */
   /* u1_jdgval         u2_dlycnt          */
   { (U1)0x01U,   (U2)((400U/SBLTWRN_TICK)+1U)   }   /*  [T32]   */
};

static const ST_SBLTSEAT_DLYCFG       st_s_SBLTSEAT_DLY_RXXOSW[] = {        /* A delay-time definition of R**OSW (R-Seat Occupant SW) signal */
   /* u1_jdgval         u2_dlycnt          */
   { (U1)0x01U,   (U2)((800U/SBLTWRN_TICK)+1U)   }   /*  [T33]   */
};

static const ST_SBLTSEAT_DLYCFG       st_s_SBLTSEAT_DLY_RXBKLPDC_NOSN[] = { /* A delay-time definition of R*BKLPDC (R-Seat Bkl SW [without OSW]) signal  */
   /* u1_jdgval         u2_dlycnt          */
   { (U1)0x00U,   (U2)((1500U/SBLTWRN_TICK)+1U)  },  /*  [T34]   */
   { (U1)0x01U,   (U2)((400U/SBLTWRN_TICK)+1U)   }   /*  [T9]    */
};

static const ST_SBLTSEAT_DLYCFG       st_s_SBLTSEAT_DLY_XRXBKL_NOSN[] = {   /* A delay-time definition of *R*BKL (R-Seat Bkl SW [without OSW]) signal  */
   /* u1_jdgval         u2_dlycnt          */
   { (U1)0x00U,   (U2)((1500U/SBLTWRN_TICK)+1U)  }   /*  [T34]   */
};

static const ST_SBLTSEAT_DLYCFG * const      st_gp_SBLTSEAT_DLYLST[SBLTSEAT_DLYLST_NUM] = {         /* A list of delay-time constant */
    &st_s_SBLTSEAT_DLY_POSW[0],              /*   SBLTSEAT_DLYLST_IDX_POSW          */
    &st_s_SBLTSEAT_DLY_CFOSW[0],             /*   SBLTSEAT_DLYLST_IDX_CFOSW         */
    &st_s_SBLTSEAT_DLY_PBKLPDC[0],           /*   SBLTSEAT_DLYLST_IDX_PBKLPDC       */
    &st_s_SBLTSEAT_DLY_CFBCKL[0],            /*   SBLTSEAT_DLYLST_IDX_CFBCKL        */
    &st_s_SBLTSEAT_DLY_RXBKLPDC[0],          /*   SBLTSEAT_DLYLST_IDX_RXBKLPDC      */
    &st_s_SBLTSEAT_DLY_RXOSW[0],             /*   SBLTSEAT_DLYLST_IDX_RXOSW         */
    &st_s_SBLTSEAT_DLY_XRXBKL[0],            /*   SBLTSEAT_DLYLST_IDX_XRXBKL        */
    &st_s_SBLTSEAT_DLY_RXXOSW[0],            /*   SBLTSEAT_DLYLST_IDX_RXXOSW        */
    &st_s_SBLTSEAT_DLY_RXBKLPDC_NOSN[0],     /*   SBLTSEAT_DLYLST_IDX_RXBKLPDC_NOSN */
    &st_s_SBLTSEAT_DLY_XRXBKL_NOSN[0]        /*   SBLTSEAT_DLYLST_IDX_XRXBKL_NOSN   */
};

static const U1                              st_gp_SBLTSEAT_DLYLST_DLYNUM[SBLTSEAT_DLYLST_NUM] = {  /* A number of delay-time list   */
    (U1)1U,
    (U1)1U,
    (U1)1U,
    (U1)1U,
    (U1)1U,
    (U1)1U,
    (U1)1U,
    (U1)1U,
    (U1)2U,
    (U1)1U
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/* void            vd_g_SbltSeatInfoInit(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_SbltSeatInfoInit(void)
{
    U4                  u4_t_loop;
    
    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)SBLTWRN_NUM_ALLSEAT; u4_t_loop++) {
        vd_s_SbltSeatStsInit(&st_sp_sblt_seat[u4_t_loop]);
    }
    
    vd_g_SbltDsCfgTxDBKL_MET((U1)SBLT_SEAT_TX_XBKLMET_UNKNWN, (U1)FALSE);
    vd_g_SbltPsCfgTxPBKL_MET((U1)SBLT_SEAT_TX_XBKLMET_UNKNWN, (U1)FALSE);
    vd_g_SbltRsCfgTxRRBKLMET((U1)SBLT_SEAT_TX_XBKLMET_UNKNWN, (U1)FALSE);
    vd_g_SbltRsCfgTxRCBKLMET((U1)SBLT_SEAT_TX_XBKLMET_UNKNWN, (U1)FALSE);
    vd_g_SbltRsCfgTxRLBKLMET((U1)SBLT_SEAT_TX_XBKLMET_UNKNWN, (U1)FALSE);
    vd_g_SbltRsCfgTxBKL3LMET((U1)SBLT_SEAT_TX_XBKLMET_UNKNWN, (U1)FALSE);
    vd_g_SbltRsCfgTxBKL3CMET((U1)SBLT_SEAT_TX_XBKLMET_UNKNWN, (U1)FALSE);
    vd_g_SbltRsCfgTxBKL3RMET((U1)SBLT_SEAT_TX_XBKLMET_UNKNWN, (U1)FALSE);

    vd_g_SbltDsCfgInit();

}

/*===================================================================================================================================*/
/*  Seat info struct initialization                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      ST_SBLT_SEAT * : A pointer to init                                                                               */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_SbltSeatStsInit(ST_SBLT_SEAT *st_ap_sblt_seat)
{
    st_ap_sblt_seat->u2_cnt       = (U2)U2_MAX;
    st_ap_sblt_seat->u2_osw_cnt   = (U2)U2_MAX;
    st_ap_sblt_seat->u1_msksig    = (U1)SBLTWRN_BKLSIG_UNKNOWN;
    st_ap_sblt_seat->u1_mskoswsig = (U1)SBLTWRN_BKLSIG_UNKNOWN;
    st_ap_sblt_seat->u1_prvsig    = (U1)SBLTWRN_BKLSIG_UNKNOWN;
    st_ap_sblt_seat->u1_prvoswsig = (U1)SBLTWRN_BKLSIG_UNKNOWN;
    st_ap_sblt_seat->u1_defined   = (U1)FALSE;
    st_ap_sblt_seat->u1_prvsts    = (U1)SBLTWRN_BKLSTS_BCKL;
}

/*===================================================================================================================================*/
/*  Driver Seat status judgement                                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_ap_MSGSTS: CAN Frame status,                                                                                  */
/*                  u4_a_SEATID:  Seat idx,                                                                                          */
/*                  u4_a_VCLSTS:  Vehicle status bit                                                                                 */
/*  Return:         D-Seat buckle status                                                                                             */
/*===================================================================================================================================*/
U1              u1_g_SbltDs(const U1 * u1_ap_MSGSTS, const U4 u4_a_SEATID, const U4 u4_a_VCLSTS)
{
    ST_SBLTSEAT_INPTSIG st_t_dbkl;          /* D-Seat Buckle Signal     */
    U1                  u1_t_bklsts;        /* Buckle status            */
    U1                  u1_t_dbklab;        /* DBKLAB send value        */
    U1                  u1_t_dbklsw;        /* DBKLSW send value        */
    U1                  u1_t_dbkl_met;      /* DBKL_MET send value      */
    U1                  u1_t_abgsup;        /* Receiving signal via ABG ECU */
    const U1 *          u1_tp_dsout;        /* D-Seat Output Table      */
    const U1 *          u1_tp_dssigout;     /* DSWN/DBKL_MET Output Table   */
    static const U1     u1_sp_DSOUT_DBKLAB[SBLTWRN_BKLSIG_NUM] = {
        (U1)SBLTWRN_BKLSTS_BCKL,        /* DBKLAB = 00b        */
        (U1)SBLT_SEAT_SNSR_UNBCKL,      /* DBKLAB = 01b        */
        (U1)SBLTWRN_BKLSTS_BCKL,        /* DBKLAB = 10b        */
        (U1)SBLT_SEAT_SNSR_UNBCKL,      /* DBKLAB = 11b        */
        (U1)SBLTWRN_BKLSTS_COMFAIL      /* DBKLAB = <COMFAIL>  */
    };
    static const U1     u1_sp_DSOUT_DBKLSW[SBLTWRN_BKLSIG_NUM] = {
        (U1)SBLTWRN_BKLSTS_BCKL,        /* DBKLSW = 00b        */
        (U1)SBLT_SEAT_SNSR_UNBCKL,      /* DBKLSW = 01b        */
        (U1)SBLTWRN_BKLSTS_BCKL,        /* DBKLSW = 10b        */
        (U1)SBLT_SEAT_SNSR_UNBCKL,      /* DBKLSW = 11b        */
        (U1)SBLTWRN_BKLSTS_COMFAIL      /* DBKLSW = <COMFAIL>  */
    };
    static const U1     u1_sp_DSSIGOUT_DBKLAB[SBLTWRN_BKLSIG_NUM] = {
        (U1)SBLT_SEAT_TX_XBKLMET_BCKL,      /* DBKLAB = 00b        */
        (U1)SBLT_SEAT_TX_XBKLMET_UNBCKL,    /* DBKLAB = 01b        */
        (U1)SBLT_SEAT_TX_XBKLMET_UNKNWN,    /* DBKLAB = 10b        */
        (U1)SBLT_SEAT_TX_XBKLMET_MALFNC,    /* DBKLAB = 11b        */
        (U1)SBLT_SEAT_TX_XBKLMET_UNKNWN     /* DBKLAB = <COMFAIL>  */
    };
    static const U1     u1_sp_DSSIGOUT_DBKLSW[SBLTWRN_BKLSIG_NUM] = {
        (U1)SBLT_SEAT_TX_XBKLMET_BCKL,      /* DBKLSW = 00b        */
        (U1)SBLT_SEAT_TX_XBKLMET_UNBCKL,    /* DBKLSW = 01b        */
        (U1)SBLT_SEAT_TX_XBKLMET_UNKNWN,    /* DBKLSW = 10b        */
        (U1)SBLT_SEAT_TX_XBKLMET_UNKNWN,    /* DBKLSW = 11b        */
        (U1)SBLT_SEAT_TX_XBKLMET_UNKNWN     /* DBKLSW = <COMFAIL>  */
    };
    
    
    /* Input signals */
    u1_t_abgsup = u1_g_SbltDsCfgABGSupd();
    u1_t_dbklab = u1_g_SbltDsCfgGetDBKLAB();
    u1_t_dbklsw = u1_g_SbltDsCfgGetDBKLSW();
    
    vd_s_SbltGetCanSgnl(&u1_t_dbklab, u1_ap_MSGSTS[SBLTWRN_MSG_ABG1S01]);
    vd_s_SbltGetCanSgnl(&u1_t_dbklsw, u1_ap_MSGSTS[SBLTWRN_MSG_ZN11S26]);
    
    if (u1_t_abgsup == (U1)TRUE) {  /* via ABG ECU (Use DBKLAB)       */
        st_t_dbkl.u1_bltwrn = u1_t_dbklab;
        st_t_dbkl.u1_cantx  = u1_t_dbklab;
        u1_tp_dsout         = u1_sp_DSOUT_DBKLAB;
        u1_tp_dssigout      = u1_sp_DSSIGOUT_DBKLAB;
        st_sp_sblt_seat[u4_a_SEATID].u1_msksig = (U1)SBLT_SEAT_DBSWSTS_UNKNOWN;
        st_sp_sblt_seat[u4_a_SEATID].u2_cnt = (U2)U2_MAX;
    } else {                        /* via ZN1 ECU (Use DBKLSW)       */
        st_t_dbkl.u1_bltwrn = u1_t_dbklsw;
        st_t_dbkl.u1_cantx  = u1_t_dbklsw;
        u1_tp_dsout         = u1_sp_DSOUT_DBKLSW;
        u1_tp_dssigout      = u1_sp_DSSIGOUT_DBKLSW;
        st_sp_sblt_seat[u4_a_SEATID].u1_msksig = (U1)SBLT_SEAT_DBSWSTS_UNKNOWN;
        st_sp_sblt_seat[u4_a_SEATID].u2_cnt = (U2)U2_MAX;
    }
    
    /* Judge output values */
    if ((u4_a_VCLSTS & (U4)SBLTWRN_VCLSTS_IG_ONSTS) == (U4)0U) {    /* IG-OFF */
        vd_s_SbltSeatStsInit(&st_sp_sblt_seat[u4_a_SEATID]);
        u1_t_bklsts   = (U1)SBLTWRN_BKLSTS_BCKL;
        u1_t_dbkl_met = (U1)SBLT_SEAT_TX_XBKLMET_UNKNWN;
    } else {
        u1_t_bklsts   =  u1_tp_dsout[st_t_dbkl.u1_bltwrn];
        u1_t_dbkl_met = u1_tp_dssigout[st_t_dbkl.u1_cantx];
    }

    if (((u1_t_bklsts ^ st_sp_sblt_seat[u4_a_SEATID].u1_prvsts) & ((U1)SBLTWRN_BKLSTS_COMFAIL & st_sp_sblt_seat[u4_a_SEATID].u1_prvsts)) != (U1)0U) {
        u1_t_bklsts  |= (U1)SBLTWRN_BKLSTS_FAILRSTEDG;
    }
    st_sp_sblt_seat[u4_a_SEATID].u1_prvsts = u1_t_bklsts;
    
    /* Transmit CAN signals */
    vd_g_SbltDsCfgTxDBKL_MET(u1_t_dbkl_met, (U1)TRUE);
    
    return (u1_t_bklsts);
}

/*===================================================================================================================================*/
/*  Passenger Seat status judgement                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_ap_MSGSTS: CAN Frame status,                                                                                  */
/*                  u4_a_SEATID:  Seat idx,                                                                                          */
/*                  u4_a_VCLSTS:  Vehicle status bit                                                                                 */
/*  Return:         P-Seat buckle status                                                                                             */
/*===================================================================================================================================*/
U1              u1_g_SbltPs(const U1 * u1_ap_MSGSTS, const U4 u4_a_SEATID, const U4 u4_a_VCLSTS)
{
    ST_SBLTSEAT_INPTSIG st_t_pbkl;                              /* P-Seat Buckle Signal             */
    U1                  u1_t_bklsts;                            /* Buckle status                    */
    U1                  u1_t_pbklpdc;                           /* PBKL_PDC raw value               */
    U1                  u1_t_pbklab;                            /* PBKLAB raw value                 */
    U1                  u1_t_pbkl_met;                          /* PBKL_MET value                   */
    U1                  u1_t_posw;                              /* POSW value                       */
    U1                  u1_t_abgsup;                            /* Receiving signal via ABG ECU     */
    const U1 (*         u1_tp_psout)[SBLTWRN_SEATSIG_NUM];      /* P-Seat Output Table              */
    const U1 *          u1_tp_pbklmetout;                       /* PBKL_PDC Output Table            */
    static const U1     u1_sp_PSOUT_PBKLAB[SBLTWRN_BKLSIG_NUM][SBLTWRN_SEATSIG_NUM] = {
        { (U1)SBLTWRN_BKLSTS_BCKL   , (U1)SBLTWRN_BKLSTS_BCKL   , (U1)SBLTWRN_BKLSTS_BCKL   , (U1)SBLT_SEAT_SNSR_UNBCKL, (U1)SBLTWRN_BKLSTS_COMFAIL },    /* PBKLAB = 00b         */
        { (U1)SBLTWRN_BKLSTS_BCKL   , (U1)SBLT_SEAT_SNSR_UNBCKL , (U1)SBLTWRN_BKLSTS_BCKL   , (U1)SBLT_SEAT_SNSR_UNBCKL, (U1)SBLTWRN_BKLSTS_COMFAIL },    /* PBKLAB = 01b         */
        { (U1)SBLTWRN_BKLSTS_BCKL   , (U1)SBLTWRN_BKLSTS_BCKL   , (U1)SBLTWRN_BKLSTS_BCKL   , (U1)SBLT_SEAT_SNSR_UNBCKL, (U1)SBLTWRN_BKLSTS_COMFAIL },    /* PBKLAB = 10b         */
        { (U1)SBLT_SEAT_SNSR_UNBCKL , (U1)SBLT_SEAT_SNSR_UNBCKL , (U1)SBLT_SEAT_SNSR_UNBCKL , (U1)SBLT_SEAT_SNSR_UNBCKL, (U1)SBLT_SEAT_SNSR_UNBCKL  },    /* PBKLAB = 11b         */
        { (U1)SBLTWRN_BKLSTS_COMFAIL, (U1)SBLTWRN_BKLSTS_COMFAIL, (U1)SBLTWRN_BKLSTS_COMFAIL, (U1)SBLT_SEAT_SNSR_UNBCKL, (U1)SBLTWRN_BKLSTS_COMFAIL }     /* PBKLAB = <COMFAIL>   */
    };
    static const U1     u1_sp_PSOUT_PBKLPDC[SBLTWRN_BKLSIG_NUM][SBLTWRN_SEATSIG_NUM] = {
        { (U1)SBLTWRN_BKLSTS_BCKL   , (U1)SBLTWRN_BKLSTS_BCKL   , (U1)SBLTWRN_BKLSTS_BCKL   , (U1)SBLT_SEAT_SNSR_UNBCKL, (U1)SBLTWRN_BKLSTS_COMFAIL },    /* PBKL_PDC = 00b       */
        { (U1)SBLTWRN_BKLSTS_BCKL   , (U1)SBLT_SEAT_SNSR_UNBCKL , (U1)SBLTWRN_BKLSTS_BCKL   , (U1)SBLT_SEAT_SNSR_UNBCKL, (U1)SBLTWRN_BKLSTS_COMFAIL },    /* PBKL_PDC = 01b       */
        { (U1)SBLTWRN_BKLSTS_BCKL   , (U1)SBLTWRN_BKLSTS_BCKL   , (U1)SBLTWRN_BKLSTS_BCKL   , (U1)SBLT_SEAT_SNSR_UNBCKL, (U1)SBLTWRN_BKLSTS_COMFAIL },    /* PBKL_PDC = 10b       */
        { (U1)SBLTWRN_BKLSTS_BCKL   , (U1)SBLTWRN_BKLSTS_BCKL   , (U1)SBLTWRN_BKLSTS_BCKL   , (U1)SBLT_SEAT_SNSR_UNBCKL, (U1)SBLTWRN_BKLSTS_COMFAIL },    /* PBKL_PDC = 11b       */
        { (U1)SBLTWRN_BKLSTS_COMFAIL, (U1)SBLTWRN_BKLSTS_COMFAIL, (U1)SBLTWRN_BKLSTS_COMFAIL, (U1)SBLT_SEAT_SNSR_UNBCKL, (U1)SBLTWRN_BKLSTS_COMFAIL }     /* PBKL_PDC = <COMFAIL> */
    };
    static const U1     u1_sp_PBKLMETOUT_PBKLAB[SBLTWRN_BKLSIG_NUM] = {
        (U1)SBLT_SEAT_TX_XBKLMET_BCKL,          /* PBKLAB = 00b         */
        (U1)SBLT_SEAT_TX_XBKLMET_UNBCKL,        /* PBKLAB = 01b         */
        (U1)SBLT_SEAT_TX_XBKLMET_UNKNWN,        /* PBKLAB = 10b         */
        (U1)SBLT_SEAT_TX_XBKLMET_MALFNC,        /* PBKLAB = 11b         */
        (U1)SBLT_SEAT_TX_XBKLMET_UNKNWN         /* PBKLAB = <COMFAIL>   */
    };
    static const U1     u1_sp_PBKLMETOUT_PBKLPDC[SBLTWRN_BKLSIG_NUM] = {
        (U1)SBLT_SEAT_TX_XBKLMET_BCKL,          /* PBKL_PDC = 00b       */
        (U1)SBLT_SEAT_TX_XBKLMET_UNBCKL,        /* PBKL_PDC = 01b       */
        (U1)SBLT_SEAT_TX_XBKLMET_UNKNWN,        /* PBKL_PDC = 10b       */
        (U1)SBLT_SEAT_TX_XBKLMET_UNKNWN,        /* PBKL_PDC = 11b       */
        (U1)SBLT_SEAT_TX_XBKLMET_UNKNWN         /* PBKL_PDC = <COMFAIL> */
    };
    
    
    /* Input signals */
    u1_t_abgsup  = u1_g_SbltPsCfgABGSupd();
    u1_t_pbklab  = u1_g_SbltPsCfgGetPBKLAB();
    u1_t_pbklpdc = u1_g_SbltPsCfgGetPBKLPDC();
    u1_t_posw    = u1_g_SbltPsCfgGetPOSW();
    
    vd_s_SbltGetCanSgnl(&u1_t_pbklab, u1_ap_MSGSTS[SBLTWRN_MSG_ABG1S01]);
    vd_s_SbltGetCanSgnl(&u1_t_pbklpdc, u1_ap_MSGSTS[SBLTWRN_MSG_PDC1G02]);
    vd_s_SbltGetCanSgnl(&u1_t_posw, u1_ap_MSGSTS[SBLTWRN_MSG_BDB1S01]);
    
    if (u1_t_abgsup == (U1)TRUE) {  /* via ABG ECU (Use PBKLAB and POSW)        */
        st_t_pbkl.u1_bltwrn = u1_t_pbklab;
        st_t_pbkl.u1_cantx  = u1_t_pbklab;
        u1_tp_psout         = u1_sp_PSOUT_PBKLAB;
        u1_tp_pbklmetout    = u1_sp_PBKLMETOUT_PBKLAB;
        st_sp_sblt_seat[u4_a_SEATID].u1_msksig = (U1)SBLT_SEAT_PBKLPDCSTS_UNKNOWN;
        st_sp_sblt_seat[u4_a_SEATID].u1_prvsig = (U1)SBLT_SEAT_PBKLPDCSTS_UNKNOWN;
        st_sp_sblt_seat[u4_a_SEATID].u2_cnt = (U2)U2_MAX;
    } else {                        /* via PDC ECU (Use PBKL_PDC and POSW)      */
        st_t_pbkl.u1_cantx  = u1_t_pbklpdc;
        u1_tp_psout         = u1_sp_PSOUT_PBKLPDC;
        u1_tp_pbklmetout    = u1_sp_PBKLMETOUT_PBKLPDC;
        vd_s_SbltInptDly(&u1_t_pbklpdc, &(st_sp_sblt_seat[u4_a_SEATID].u1_msksig), &(st_sp_sblt_seat[u4_a_SEATID].u2_cnt), (U1)SBLTSEAT_DLYLST_IDX_PBKLPDC);
        
        /* Hold PBKL_PDC a previous value when received value is 11b. */
        if (u1_t_pbklpdc == (U1)SBLT_SEAT_PBKLPDCSTS_UNDEFINED) {
            st_t_pbkl.u1_bltwrn = st_sp_sblt_seat[u4_a_SEATID].u1_prvsig;
        } else {
            st_t_pbkl.u1_bltwrn = u1_t_pbklpdc;
        }
    }
    st_sp_sblt_seat[u4_a_SEATID].u1_prvsig = st_t_pbkl.u1_bltwrn;
    
    vd_s_SbltInptDly(&u1_t_posw, &(st_sp_sblt_seat[u4_a_SEATID].u1_mskoswsig), &(st_sp_sblt_seat[u4_a_SEATID].u2_osw_cnt), (U1)SBLTSEAT_DLYLST_IDX_POSW);
    
    /* Judge output values */
    if ((u4_a_VCLSTS & (U4)SBLTWRN_VCLSTS_IG_ONSTS) == (U4)0U) {
        vd_s_SbltSeatStsInit(&st_sp_sblt_seat[u4_a_SEATID]);
        u1_t_bklsts   = (U1)SBLTWRN_BKLSTS_BCKL;
        u1_t_pbkl_met = (U1)SBLT_SEAT_TX_XBKLMET_UNKNWN;
    } else {
        u1_t_bklsts   = u1_tp_psout[st_t_pbkl.u1_bltwrn][u1_t_posw];
        u1_t_pbkl_met = u1_tp_pbklmetout[st_t_pbkl.u1_cantx];
    }

    if (((u1_t_bklsts ^ st_sp_sblt_seat[u4_a_SEATID].u1_prvsts) & ((U1)SBLTWRN_BKLSTS_COMFAIL & st_sp_sblt_seat[u4_a_SEATID].u1_prvsts)) != (U1)0U) {
        u1_t_bklsts  |= (U1)SBLTWRN_BKLSTS_FAILRSTEDG;
    }
    st_sp_sblt_seat[u4_a_SEATID].u1_prvsts = u1_t_bklsts;

    /* Transmit CAN signals */
    vd_g_SbltPsCfgTxPBKL_MET(u1_t_pbkl_met, (U1)TRUE);

    return (u1_t_bklsts);
}

/*===================================================================================================================================*/
/*  Front Center status judgement                                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_ap_MSGSTS: CAN Frame status,                                                                                  */
/*                  u4_a_SEATID:  Seat idx,                                                                                          */
/*                  u4_a_VCLSTS:  Vehicle status bit                                                                                 */
/*  Return:         FC-Seat buckle status                                                                                            */
/*===================================================================================================================================*/
U1              u1_g_SbltFc(const U1 * u1_ap_MSGSTS, const U4 u4_a_SEATID, const U4 u4_a_VCLSTS)
{
    ST_SBLTSEAT_INPTSIG st_t_cbkl;                              /* FC-Seat Buckle Signal            */
    ST_SBLTSEAT_INPTSIG st_t_cosw;                              /* FC-Seat Sensor Signal            */
    U1                  u1_t_bklsts;                            /* Buckle status                    */
    U1                  u1_t_cfbckl;                            /* CFBCKL raw value                 */
    U1                  u1_t_cfosw;                             /* CFOSW value                      */
    const U1 (*         u1_tp_fcout)[SBLTWRN_SEATSIG_NUM];      /* FC-Seat Output Table             */
    static const U1     u1_sp_FCOUT_CFBCKL[SBLTWRN_BKLSIG_NUM][SBLTWRN_SEATSIG_NUM] = {
        { (U1)SBLTWRN_BKLSTS_BCKL   , (U1)SBLTWRN_BKLSTS_BCKL   , (U1)SBLTWRN_BKLSTS_BCKL   , (U1)SBLTWRN_BKLSTS_BCKL,   (U1)SBLTWRN_BKLSTS_COMFAIL },    /* CFBCKL = 00b        */
        { (U1)SBLTWRN_BKLSTS_BCKL   , (U1)SBLT_SEAT_SNSR_UNBCKL , (U1)SBLTWRN_BKLSTS_BCKL   , (U1)SBLTWRN_BKLSTS_BCKL,   (U1)SBLTWRN_BKLSTS_COMFAIL },    /* CFBCKL = 01b        */
        { (U1)SBLTWRN_BKLSTS_BCKL   , (U1)SBLTWRN_BKLSTS_BCKL   , (U1)SBLTWRN_BKLSTS_BCKL   , (U1)SBLTWRN_BKLSTS_BCKL,   (U1)SBLTWRN_BKLSTS_COMFAIL },    /* CFBCKL = 10b        */
        { (U1)SBLTWRN_BKLSTS_BCKL   , (U1)SBLTWRN_BKLSTS_BCKL   , (U1)SBLTWRN_BKLSTS_BCKL   , (U1)SBLTWRN_BKLSTS_BCKL,   (U1)SBLTWRN_BKLSTS_COMFAIL },    /* CFBCKL = 11b        */
        { (U1)SBLTWRN_BKLSTS_COMFAIL, (U1)SBLTWRN_BKLSTS_COMFAIL, (U1)SBLTWRN_BKLSTS_COMFAIL, (U1)SBLTWRN_BKLSTS_COMFAIL,(U1)SBLTWRN_BKLSTS_COMFAIL }     /* CFBCKL = <COMFAIL>  */
    };

    /* Input signals */
    u1_t_cfbckl = u1_g_SbltFcCfgGetCFBCKL();
    u1_t_cfosw  = u1_g_SbltFcCfgGetCFOSW();

    vd_s_SbltGetCanSgnl(&u1_t_cfbckl, u1_ap_MSGSTS[SBLTWRN_MSG_ZN11S26]);
    vd_s_SbltGetCanSgnl(&u1_t_cfosw,  u1_ap_MSGSTS[SBLTWRN_MSG_ZN11S19]);

    u1_tp_fcout         = u1_sp_FCOUT_CFBCKL;
    vd_s_SbltInptDly(&u1_t_cfbckl, &(st_sp_sblt_seat[u4_a_SEATID].u1_msksig), &(st_sp_sblt_seat[u4_a_SEATID].u2_cnt), (U1)SBLTSEAT_DLYLST_IDX_CFBCKL);

    /* Hold CFBCKL a previous value when received value is 11b. */
    if (u1_t_cfbckl == (U1)SBLT_SEAT_CFBCKLSTS_UNDEFINED) {
        st_t_cbkl.u1_bltwrn = st_sp_sblt_seat[u4_a_SEATID].u1_prvsig;
    } else {
        st_t_cbkl.u1_bltwrn = u1_t_cfbckl;
    }
    st_sp_sblt_seat[u4_a_SEATID].u1_prvsig = st_t_cbkl.u1_bltwrn;
    
    vd_s_SbltInptDly(&u1_t_cfosw, &(st_sp_sblt_seat[u4_a_SEATID].u1_mskoswsig), &(st_sp_sblt_seat[u4_a_SEATID].u2_osw_cnt), (U1)SBLTSEAT_DLYLST_IDX_CFOSW);

    /* Hold CFOSW a previous value when received value is 11b. */
    if (u1_t_cfosw == (U1)SBLT_SEAT_CFBCKLSTS_UNDEFINED) {
        st_t_cosw.u1_bltwrn = st_sp_sblt_seat[u4_a_SEATID].u1_prvoswsig;
    } else {
        st_t_cosw.u1_bltwrn = u1_t_cfosw;
    }
    st_sp_sblt_seat[u4_a_SEATID].u1_prvoswsig = st_t_cosw.u1_bltwrn;

    /* Judge output values */
    if ((u4_a_VCLSTS & (U4)SBLTWRN_VCLSTS_IG_ONSTS) == (U4)0U) {
        vd_s_SbltSeatStsInit(&st_sp_sblt_seat[u4_a_SEATID]);
        u1_t_bklsts   = (U1)SBLTWRN_BKLSTS_BCKL;
    } else {
        u1_t_bklsts   = u1_tp_fcout[st_t_cbkl.u1_bltwrn][st_t_cosw.u1_bltwrn];
    }

    if (((u1_t_bklsts ^ st_sp_sblt_seat[u4_a_SEATID].u1_prvsts) & ((U1)SBLTWRN_BKLSTS_COMFAIL & st_sp_sblt_seat[u4_a_SEATID].u1_prvsts)) != (U1)0U) {
        u1_t_bklsts  |= (U1)SBLTWRN_BKLSTS_FAILRSTEDG;
    }
    st_sp_sblt_seat[u4_a_SEATID].u1_prvsts = u1_t_bklsts;

    return (u1_t_bklsts);
}

/*===================================================================================================================================*/
/* U1              u1_g_SbltRsRxbklpdc_Rxosw(const U1 * u1_ap_MSGSTS, const U4 u4_a_SEATID, const U4 u4_a_VCLSTS)                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_SbltRsRxbklpdc_Rxosw(const U1 * u1_ap_MSGSTS, const U4 u4_a_SEATID, const U4 u4_a_VCLSTS)
{
    U1  u1_t_bklsts;
    
    u1_t_bklsts = u1_s_SbltRsCAN(u1_ap_MSGSTS, u4_a_SEATID, u4_a_VCLSTS, (U1)SBLT_SEAT_RR_RXOSW);
    return (u1_t_bklsts);
}

/*===================================================================================================================================*/
/* U1              u1_g_SbltRsRxbklpdc(const U1 * u1_ap_MSGSTS, const U4 u4_a_SEATID, const U4 u4_a_VCLSTS)                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_SbltRsRxbklpdc(const U1 * u1_ap_MSGSTS, const U4 u4_a_SEATID, const U4 u4_a_VCLSTS)
{
    U1  u1_t_bklsts;
    
    u1_t_bklsts = u1_s_SbltRsCAN(u1_ap_MSGSTS, u4_a_SEATID, u4_a_VCLSTS, (U1)SBLT_SEAT_RR_NOSN);
    return (u1_t_bklsts);
}

/*===================================================================================================================================*/
/*  Rear-Seat (CAN inpt) status judgement                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_ap_MSGSTS: CAN Frame status,                                                                                  */
/*                  u4_a_SEATID:  Seat idx,                                                                                          */
/*                  u4_a_VCLSTS:  Vehicle status bit                                                                                 */
/*  Return:         Rr-Seat buckle status                                                                                            */
/*===================================================================================================================================*/
static U1       u1_s_SbltRsCAN(const U1 * u1_ap_MSGSTS, const U4 u4_a_SEATID, const U4 u4_a_VCLSTS, const U1 u1_a_SNSR)
{
    ST_SBLTSEAT_INPTSIG st_t_bklsig;        /* Buckle signal                */
    U1                  u1_t_bklsts;        /* Buckle State */
    U1                  u1_t_rxbklpdc;      /* Rr2-Seat buckle sw           */
    U1                  u1_t_rxbklmet;      /* R*BKLMET value               */
    U1                  u1_t_rxosw;         /* Occupant Detection Signal    */
    U1                  u1_t_oswsts;        /* Occupant Detection Status    */
    static const U1     u1_sp_SBLT_SEAT_RR2DLYJDG[SBLT_SEAT_RR2TYPNUM] = {
        (U1)SBLTSEAT_DLYLST_IDX_RXBKLPDC_NOSN,  /* SBLT_SEAT_RR_NOSN        */
        (U1)SBLTSEAT_DLYLST_IDX_RXBKLPDC        /* SBLT_SEAT_RR_RXOSW       */
    };
    static const U1     u1_sp_RXBKLMETOUT[SBLTWRN_BKLSIG_NUM] = {
        (U1)SBLT_SEAT_TX_XBKLMET_BCKL,          /* R*BKLPDC = 00b       */
        (U1)SBLT_SEAT_TX_XBKLMET_UNBCKL,        /* R*BKLPDC = 01b       */
        (U1)SBLT_SEAT_TX_XBKLMET_UNKNWN,        /* R*BKLPDC = 10b       */
        (U1)SBLT_SEAT_TX_XBKLMET_MALFNC,        /* R*BKLPDC = 11b       */
        (U1)SBLT_SEAT_TX_XBKLMET_UNKNWN         /* R*BKLPDC = <COMFAIL> */
    };

    /* Receive a buckle signal      */
    if (fp_sp_u1_SBLT_SEATSIG_RXBKLPDC[u4_a_SEATID] != vdp_PTR_NA) {
        u1_t_rxbklpdc = fp_sp_u1_SBLT_SEATSIG_RXBKLPDC[u4_a_SEATID]();              /* Receive R*BKLPDC value */
        vd_s_SbltGetCanSgnl(&u1_t_rxbklpdc, u1_ap_MSGSTS[SBLTWRN_MSG_PDC1G02]);
    } else {
        u1_t_rxbklpdc = (U1)SBLTWRN_BKLSIG_UNKNOWN;
    }
    if (fp_sp_u1_SBLT_SEATSIG_RXOSW[u4_a_SEATID] != vdp_PTR_NA) {
        u1_t_rxosw = fp_sp_u1_SBLT_SEATSIG_RXOSW[u4_a_SEATID]();                    /* Receive R*OSW value    */
        vd_s_SbltGetCanSgnl(&u1_t_rxosw, u1_ap_MSGSTS[SBLTWRN_MSG_BDB1S01]);
    } else {
        u1_t_rxosw = (U1)SBLTWRN_BKLSIG_UNKNOWN;
    }
    
    /* Signal hold and delay procedure  */
    st_t_bklsig.u1_cantx  = u1_t_rxbklpdc;
    u1_t_oswsts           = u1_t_rxosw;
    if (u1_t_rxbklpdc == (U1)SBLT_SEAT_RXBKLPDCSTS_UNDEFINED) {     /* Hold a previous signal when R*BKLPDC signal is 11b. */
        st_t_bklsig.u1_bltwrn = st_sp_sblt_seat[u4_a_SEATID].u1_prvsig;
    } else {
        st_t_bklsig.u1_bltwrn = u1_t_rxbklpdc;
    }
    vd_s_SbltInptDly(&(st_t_bklsig.u1_bltwrn), &(st_sp_sblt_seat[u4_a_SEATID].u1_msksig), &(st_sp_sblt_seat[u4_a_SEATID].u2_cnt), u1_sp_SBLT_SEAT_RR2DLYJDG[u1_a_SNSR]);
    vd_s_SbltInptDly(&u1_t_oswsts, &(st_sp_sblt_seat[u4_a_SEATID].u1_mskoswsig), &(st_sp_sblt_seat[u4_a_SEATID].u2_osw_cnt), (U1)SBLTSEAT_DLYLST_IDX_RXOSW);
    
    /* Judge a buckle status and Tx signal */
    if ((u4_a_VCLSTS & (U4)SBLTWRN_VCLSTS_IG_ONSTS) == (U4)0U) {
        vd_s_SbltSeatStsInit(&st_sp_sblt_seat[u4_a_SEATID]);
        u1_t_bklsts   = (U1)SBLTWRN_BKLSTS_BCKL;
        u1_t_rxbklmet = (U1)SBLT_SEAT_TX_XBKLMET_UNKNWN;
    } else {
        u1_t_bklsts   = u1_s_SbltRsBklstsJdg(u4_a_SEATID, st_t_bklsig.u1_bltwrn, u1_t_oswsts, u1_a_SNSR);
        u1_t_rxbklmet = u1_sp_RXBKLMETOUT[st_t_bklsig.u1_cantx];
    }
    
    if (((u1_t_bklsts ^ st_sp_sblt_seat[u4_a_SEATID].u1_prvsts) & ((U1)SBLTWRN_BKLSTS_COMFAIL & st_sp_sblt_seat[u4_a_SEATID].u1_prvsts)) != (U1)0U) {
        u1_t_bklsts  |= (U1)SBLTWRN_BKLSTS_FAILRSTEDG;
    }
    st_sp_sblt_seat[u4_a_SEATID].u1_prvsts = u1_t_bklsts;

    /* Transmit CAN Signal 'R*BKLMET' */
    if (fp_sp_vd_SBLT_SEATSIG_RXBKLMET[u4_a_SEATID] != vdp_PTR_NA) {
        fp_sp_vd_SBLT_SEATSIG_RXBKLMET[u4_a_SEATID](u1_t_rxbklmet, (U1)TRUE);
    }
    
    return (u1_t_bklsts);
}

/*===================================================================================================================================*/
/*  Buckle status judgment procedure                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u4_a_SEATID:        Seat idx                                                                                     */
/*                  u1_a_BKLINPT:       Buckle input signal                                                                          */
/*                  u1_a_OSWSTS:        Occupant signal                                                                              */
/*                  u1_a_RRSNSRTYP:     Occupant detection support                                                                   */
/*  Return:         Buckle Status                                                                                                    */
/*===================================================================================================================================*/
static U1     u1_s_SbltRsBklstsJdg(const U4 u4_a_SEATID, const U1 u1_a_BKLINPT, const U1 u1_a_OSWSTS, const U1 u1_a_RRSNSRTYP)
{
    U1  u1_t_bklsts;        /* Buckle Status     */
    
    if (u1_a_RRSNSRTYP == (U1)SBLT_SEAT_RR_RXOSW) {     /* Occupant Detection supported     */
        u1_t_bklsts = u1_s_SbltRsSnsrBklEdg(u4_a_SEATID, u1_a_BKLINPT, u1_a_OSWSTS);
    } else {                                            /* Occupant Detection not supported */
        if (u1_a_BKLINPT == (U1)SBLTWRN_BKLSIG_UNBUCKLED) {
            u1_t_bklsts = u1_s_SbltRsUnbkleFlg(u4_a_SEATID);
        } else {
            u1_t_bklsts = u1_s_SbltRsNosnBklEdg(u4_a_SEATID);
        }
    }
    if (u1_a_BKLINPT != (U1)SBLTWRN_BKLSIG_UNKNOWN) {
        st_sp_sblt_seat[u4_a_SEATID].u1_defined = (U1)TRUE;
    }
    st_sp_sblt_seat[u4_a_SEATID].u1_prvsig = u1_a_BKLINPT;
    
    return (u1_t_bklsts);
}

/*===================================================================================================================================*/
/* static  U1      u1_s_SbltRsSnsrBklEdg(const U4 u4_a_SEATID)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_SbltRsSnsrBklEdg(const U4 u4_a_SEATID, const U1 u1_a_BKLINPT, const U1 u1_a_OSWSTS)
{
    static const U1     u1_sp_SBLT_SEAT_RR2STSJDG[SBLTWRN_BKLSIG_NUM][SBLTWRN_SEATSIG_NUM] = {
        /* R*OSW = 00b             */ /* R*OSW = 01b           */ /* R*OSW = 10b           */ /* R*OSW = 11b           */ /* R*OSW = <COMFAIL>       */
        { (U1)SBLTWRN_BKLSTS_BCKL,      (U1)SBLTWRN_BKLSTS_BCKL,    (U1)SBLTWRN_BKLSTS_BCKL,    (U1)SBLT_SEAT_SNSR_UNBCKL,  (U1)SBLTWRN_BKLSTS_COMFAIL  },  /* R*BKLPDC = 00b       */
        { (U1)SBLTWRN_BKLSTS_BCKL,      (U1)SBLT_SEAT_SNSR_UNBCKL,  (U1)SBLTWRN_BKLSTS_BCKL,    (U1)SBLT_SEAT_SNSR_UNBCKL,  (U1)SBLTWRN_BKLSTS_COMFAIL  },  /* R*BKLPDC = 01b       */
        { (U1)SBLTWRN_BKLSTS_BCKL,      (U1)SBLTWRN_BKLSTS_BCKL,    (U1)SBLTWRN_BKLSTS_BCKL,    (U1)SBLT_SEAT_SNSR_UNBCKL,  (U1)SBLTWRN_BKLSTS_COMFAIL  },  /* R*BKLPDC = 10b       */
        { (U1)SBLTWRN_BKLSTS_BCKL,      (U1)SBLTWRN_BKLSTS_BCKL,    (U1)SBLTWRN_BKLSTS_BCKL,    (U1)SBLT_SEAT_SNSR_UNBCKL,  (U1)SBLTWRN_BKLSTS_COMFAIL  },  /* R*BKLPDC = 11b       */
        { (U1)SBLTWRN_BKLSTS_COMFAIL,   (U1)SBLTWRN_BKLSTS_COMFAIL, (U1)SBLTWRN_BKLSTS_COMFAIL, (U1)SBLT_SEAT_SNSR_UNBCKL,  (U1)SBLTWRN_BKLSTS_COMFAIL  }   /* R*BKLPDC = <COMFAIL> */
    };
    U1  u1_t_bklsts;

    u1_t_bklsts = u1_sp_SBLT_SEAT_RR2STSJDG[u1_a_BKLINPT][u1_a_OSWSTS];

    return (u1_t_bklsts);
}

/*===================================================================================================================================*/
/* U1              u1_g_SbltRsXrxbkl_Rxxosw(const U1 * u1_ap_MSGSTS, const U4 u4_a_SEATID, const U4 u4_a_VCLSTS)                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_SbltRsXrxbkl_Rxxosw(const U1 * u1_ap_MSGSTS, const U4 u4_a_SEATID, const U4 u4_a_VCLSTS)
{
    U1  u1_t_bklsts;
    
    u1_t_bklsts = u1_s_SbltRsXCAN(u1_ap_MSGSTS, u4_a_SEATID, u4_a_VCLSTS, (U1)SBLT_SEAT_RR_RXOSW);
    return (u1_t_bklsts);
}

/*===================================================================================================================================*/
/* U1              u1_g_SbltRsXrxbkl(const U1 * u1_ap_MSGSTS, const U4 u4_a_SEATID, const U4 u4_a_VCLSTS)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_SbltRsXrxbkl(const U1 * u1_ap_MSGSTS, const U4 u4_a_SEATID, const U4 u4_a_VCLSTS)
{
    U1  u1_t_bklsts;
    
    u1_t_bklsts = u1_s_SbltRsXCAN(u1_ap_MSGSTS, u4_a_SEATID, u4_a_VCLSTS, (U1)SBLT_SEAT_RR_NOSN);
    return (u1_t_bklsts);
}

/*===================================================================================================================================*/
/*  Rear-Seat(2nd-) (CAN inpt) status judgement                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_ap_MSGSTS: CAN Frame status,                                                                                  */
/*                  u4_a_SEATID:  Seat idx,                                                                                          */
/*                  u4_a_VCLSTS:  Vehicle status bit                                                                                 */
/*  Return:         Rr-Seat(2nd-) buckle status                                                                                      */
/*===================================================================================================================================*/
static U1       u1_s_SbltRsXCAN(const U1 * u1_ap_MSGSTS, const U4 u4_a_SEATID, const U4 u4_a_VCLSTS, const U1 u1_a_SNSR)
{
    ST_SBLTSEAT_INPTSIG st_t_bklsig;        /* Buckle signal                */
    ST_SBLTSEAT_INPTSIG st_t_oswsig;        /* Sensor signal                */
    U1                  u1_t_bklsts;        /* Buckle State */
    U1                  u1_t_xrxbkl;        /* Rr2-Seat buckle sw           */
    U1                  u1_t_bklxxmet;      /* BKL**MET value               */
    U1                  u1_t_rxxosw;        /* Occupant Detection Signal    */
    static const U1     u1_sp_SBLT_SEAT_RRXDLYJDG[SBLT_SEAT_RR2TYPNUM] = {
        (U1)SBLTSEAT_DLYLST_IDX_XRXBKL_NOSN,/* SBLT_SEAT_RR_NOSN        */
        (U1)SBLTSEAT_DLYLST_IDX_XRXBKL      /* SBLT_SEAT_RR_RXOSW       */
    };
    static const U1     u1_sp_RXBKLMETOUT[SBLTWRN_BKLSIG_NUM] = {
        (U1)SBLT_SEAT_TX_XBKLMET_BCKL,          /* *R*BKL = 00b         */
        (U1)SBLT_SEAT_TX_XBKLMET_UNBCKL,        /* *R*BKL = 01b         */
        (U1)SBLT_SEAT_TX_XBKLMET_UNKNWN,        /* *R*BKL = 10b         */
        (U1)SBLT_SEAT_TX_XBKLMET_MALFNC,        /* *R*BKL = 11b         */
        (U1)SBLT_SEAT_TX_XBKLMET_UNKNWN         /* *R*BKL = <COMFAIL>   */
    };

    /* Receive a buckle signal      */
    if (fp_sp_u1_SBLT_SEATSIG_RXBKLPDC[u4_a_SEATID] != vdp_PTR_NA) {
        u1_t_xrxbkl = fp_sp_u1_SBLT_SEATSIG_RXBKLPDC[u4_a_SEATID]();                /* Receive *R*BKL value   */
        vd_s_SbltGetCanSgnl(&u1_t_xrxbkl, u1_ap_MSGSTS[SBLTWRN_MSG_ZN11S26]);
    } else {
        u1_t_xrxbkl = (U1)SBLTWRN_BKLSIG_UNKNOWN;
    }
    if (fp_sp_u1_SBLT_SEATSIG_RXOSW[u4_a_SEATID] != vdp_PTR_NA) {
        u1_t_rxxosw = fp_sp_u1_SBLT_SEATSIG_RXOSW[u4_a_SEATID]();                   /* Receive R**OSW value   */
        vd_s_SbltGetCanSgnl(&u1_t_rxxosw, u1_ap_MSGSTS[SBLTWRN_MSG_ZN11S19]);
    } else {
        u1_t_rxxosw = (U1)SBLTWRN_BKLSIG_UNKNOWN;
    }
    
    /* Signal hold and delay procedure  */
    st_t_bklsig.u1_cantx  = u1_t_xrxbkl;
    if (u1_t_xrxbkl == (U1)SBLT_SEAT_XRXBKLSTS_UNDEFINED) {         /* Hold a previous signal when *R*BKL signal is 11b. */
        st_t_bklsig.u1_bltwrn = st_sp_sblt_seat[u4_a_SEATID].u1_prvsig;
    } else {
        st_t_bklsig.u1_bltwrn = u1_t_xrxbkl;
    }
    if (u1_t_rxxosw == (U1)SBLT_SEAT_XRXBKLSTS_UNDEFINED) {         /* Hold a previous signal when R**OSW signal is 11b. */
        st_t_oswsig.u1_bltwrn = st_sp_sblt_seat[u4_a_SEATID].u1_prvoswsig;
    } else {
        st_t_oswsig.u1_bltwrn = u1_t_rxxosw;
    }
    vd_s_SbltInptDly(&(st_t_bklsig.u1_bltwrn), &(st_sp_sblt_seat[u4_a_SEATID].u1_msksig), &(st_sp_sblt_seat[u4_a_SEATID].u2_cnt), u1_sp_SBLT_SEAT_RRXDLYJDG[u1_a_SNSR]);
    vd_s_SbltInptDly(&(st_t_oswsig.u1_bltwrn), &(st_sp_sblt_seat[u4_a_SEATID].u1_mskoswsig), &(st_sp_sblt_seat[u4_a_SEATID].u2_osw_cnt), (U1)SBLTSEAT_DLYLST_IDX_RXXOSW);
    
    /* Judge a buckle status and Tx signal */
    if ((u4_a_VCLSTS & (U4)SBLTWRN_VCLSTS_IG_ONSTS) == (U4)0U) {
        vd_s_SbltSeatStsInit(&st_sp_sblt_seat[u4_a_SEATID]);
        u1_t_bklsts   = (U1)SBLTWRN_BKLSTS_BCKL;
        u1_t_bklxxmet = (U1)SBLT_SEAT_TX_XBKLMET_UNKNWN;
    } else {
        u1_t_bklsts   = u1_s_SbltRsXBklstsJdg(u4_a_SEATID, st_t_bklsig.u1_bltwrn, st_t_oswsig.u1_bltwrn, u1_a_SNSR);
        u1_t_bklxxmet = u1_sp_RXBKLMETOUT[st_t_bklsig.u1_cantx];
    }
    
    if (((u1_t_bklsts ^ st_sp_sblt_seat[u4_a_SEATID].u1_prvsts) & ((U1)SBLTWRN_BKLSTS_COMFAIL & st_sp_sblt_seat[u4_a_SEATID].u1_prvsts)) != (U1)0U) {
        u1_t_bklsts  |= (U1)SBLTWRN_BKLSTS_FAILRSTEDG;
    }
    st_sp_sblt_seat[u4_a_SEATID].u1_prvsts = u1_t_bklsts;

    /* Transmit CAN Signal BKL**MET' */
    if (fp_sp_vd_SBLT_SEATSIG_RXBKLMET[u4_a_SEATID] != vdp_PTR_NA) {
        fp_sp_vd_SBLT_SEATSIG_RXBKLMET[u4_a_SEATID](u1_t_bklxxmet, (U1)TRUE);
    }
    
    return (u1_t_bklsts);
}

/*===================================================================================================================================*/
/*  Buckle status judgment procedure                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u4_a_SEATID:        Seat idx                                                                                     */
/*                  u1_a_BKLINPT:       Buckle input signal                                                                          */
/*                  u1_a_OSWSTS:        Occupant signal                                                                              */
/*                  u1_a_RRSNSRTYP:     Occupant detection support                                                                   */
/*  Return:         Buckle Status                                                                                                    */
/*===================================================================================================================================*/
static U1     u1_s_SbltRsXBklstsJdg(const U4 u4_a_SEATID, const U1 u1_a_BKLINPT, const U1 u1_a_OSWSTS, const U1 u1_a_RRSNSRTYP)
{
    U1  u1_t_bklsts;        /* Buckle Status     */
    
    if (u1_a_RRSNSRTYP == (U1)SBLT_SEAT_RR_RXOSW) {     /* Occupant Detection supported     */
        u1_t_bklsts = u1_s_SbltRsXSnsrBklEdg(u4_a_SEATID, u1_a_BKLINPT, u1_a_OSWSTS);
    } else {                                            /* Occupant Detection not supported */
        if (u1_a_BKLINPT == (U1)SBLTWRN_BKLSIG_UNBUCKLED) {
            u1_t_bklsts = u1_s_SbltRsUnbkleFlg(u4_a_SEATID);
        } else {
            u1_t_bklsts = u1_s_SbltRsNosnBklEdg(u4_a_SEATID);
        }
    }
    if (u1_a_BKLINPT != (U1)SBLTWRN_BKLSIG_UNKNOWN) {
        st_sp_sblt_seat[u4_a_SEATID].u1_defined = (U1)TRUE;
    }
    st_sp_sblt_seat[u4_a_SEATID].u1_prvsig    = u1_a_BKLINPT;
    st_sp_sblt_seat[u4_a_SEATID].u1_prvoswsig = u1_a_OSWSTS;
    
    return (u1_t_bklsts);
}

/*===================================================================================================================================*/
/* static  U1      u1_s_SbltRsXSnsrBklEdg(const U4 u4_a_SEATID)                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_SbltRsXSnsrBklEdg(const U4 u4_a_SEATID, const U1 u1_a_BKLINPT, const U1 u1_a_OSWSTS)
{
    static const U1     u1_sp_SBLT_SEAT_RRXSTSJDG[SBLTWRN_BKLSIG_NUM][SBLTWRN_SEATSIG_NUM] = {
        /* R**OSW = 00b            */ /* R**OSW = 01b          */ /* R**OSW = 10b          */ /* R**OSW = 11b          */ /* R**OSW = <COMFAIL>      */
        { (U1)SBLTWRN_BKLSTS_BCKL,      (U1)SBLTWRN_BKLSTS_BCKL,    (U1)SBLTWRN_BKLSTS_BCKL,    (U1)SBLTWRN_BKLSTS_BCKL,    (U1)SBLTWRN_BKLSTS_COMFAIL  },  /* *R*BKL = 00b         */
        { (U1)SBLTWRN_BKLSTS_BCKL,      (U1)SBLT_SEAT_SNSR_UNBCKL,  (U1)SBLTWRN_BKLSTS_BCKL,    (U1)SBLTWRN_BKLSTS_BCKL,    (U1)SBLTWRN_BKLSTS_COMFAIL  },  /* *R*BKL = 01b         */
        { (U1)SBLTWRN_BKLSTS_BCKL,      (U1)SBLTWRN_BKLSTS_BCKL,    (U1)SBLTWRN_BKLSTS_BCKL,    (U1)SBLTWRN_BKLSTS_BCKL,    (U1)SBLTWRN_BKLSTS_COMFAIL  },  /* *R*BKL = 10b         */
        { (U1)SBLTWRN_BKLSTS_BCKL,      (U1)SBLTWRN_BKLSTS_BCKL,    (U1)SBLTWRN_BKLSTS_BCKL,    (U1)SBLTWRN_BKLSTS_BCKL,    (U1)SBLTWRN_BKLSTS_COMFAIL  },  /* *R*BKL = 11b         */
        { (U1)SBLTWRN_BKLSTS_COMFAIL,   (U1)SBLTWRN_BKLSTS_COMFAIL, (U1)SBLTWRN_BKLSTS_COMFAIL, (U1)SBLTWRN_BKLSTS_COMFAIL, (U1)SBLTWRN_BKLSTS_COMFAIL  }   /* *R*BKL = <COMFAIL>   */
    };
    U1  u1_t_bklsts;

    u1_t_bklsts = u1_sp_SBLT_SEAT_RRXSTSJDG[u1_a_BKLINPT][u1_a_OSWSTS];

    return (u1_t_bklsts);
}

/*===================================================================================================================================*/
/* static  U1      u1_s_SbltRsNosnBklEdg(const U4 u4_a_SEATID)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_SbltRsNosnBklEdg(const U4 u4_a_SEATID)
{
    U1  u1_t_bklsts;

    u1_t_bklsts = (U1)SBLTWRN_BKLSTS_BCKL;
    if (st_sp_sblt_seat[u4_a_SEATID].u1_prvsig == (U1)SBLTWRN_BKLSIG_UNBUCKLED) {
        u1_t_bklsts |= (U1)SBLTWRN_BKLSTS_BCKLEDG;
    }

    return (u1_t_bklsts);
}

/*===================================================================================================================================*/
/*  Unbuckle flag / edge judgment procedure                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u4_a_SEATID:  Seat idx                                                                                           */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1        u1_s_SbltRsUnbkleFlg(const U4 u4_a_SEATID)
{
    U1      u1_a_bklsts;    /* Buckle Status     */
    
    u1_a_bklsts = (U1)SBLTWRN_BKLSTS_UNBCKL;    /* The buckle status is fixed to 'unbuckled' under condition this function is called */
    
    switch (st_sp_sblt_seat[u4_a_SEATID].u1_prvsig) {
        case SBLTWRN_BKLSIG_BUCKLED:
            u1_a_bklsts |= (U1)SBLTWRN_BKLSTS_UNBCKLEDG;
            break;
        case SBLTWRN_BKLSIG_UNKNOWN:
            if (st_sp_sblt_seat[u4_a_SEATID].u1_defined == (U1)FALSE) {
                u1_a_bklsts |= (U1)SBLTWRN_BKLSTS_FIXUNBKL;
            }
            break;
        default:
            /* Do nothing */
            break;
    }
    
    return (u1_a_bklsts);
}

/*===================================================================================================================================*/
/* static  void    vd_s_SbltGetCanSgnl(U1 * u1p_a_sgnl, const U1 u1_a_MSGSTS)                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1p_a_sgnl:  CAN signal                                                                                          */
/*                  u1_a_MSGSTS: CAN Frame Status                                                                                    */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_SbltGetCanSgnl(U1 * u1p_a_sgnl, const U1 u1_a_MSGSTS)
{
    switch (u1_a_MSGSTS) {
        case SBLTWRN_VALID:
            (*u1p_a_sgnl) &= (U1)SBLT_SEAT_SIGRANGE;
            break;
        case SBLTWRN_INVALID:
            (*u1p_a_sgnl) = (U1)SBLTWRN_BKLSIG_COMFAIL;
            break;
        /* case SBLTWRN_UNKNOWN: */
        default:
            (*u1p_a_sgnl) = (U1)SBLTWRN_BKLSIG_UNKNOWN;
            break;
    }
}

/*===================================================================================================================================*/
/*  Delay an input signal                                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1p_a_sgnl:     Delayed input signal                                                                             */
/*                  u1p_a_prvsgnl:  Previous signal                                                                                  */
/*                  u2p_a_cnt:      Delay-time Counter                                                                               */
/*                  u1_a_dlyidx:    An index value of delay-time definition                                                          */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_SbltInptDly(U1 *u1p_a_sgnl, U1 *u1p_a_prvsgnl, U2 *u2p_a_cnt, U1 u1_a_dlyidx)
{
    const ST_SBLTSEAT_DLYCFG *  st_tp_dlycfg;   /* Delay-time definition  */
    U2                          u2_t_dly;       /* Delay-time             */
    U1                          u1_t_cnt;       /* loop counter           */
    U1                          u1_t_dlynum;    /* a number of delay-time */
    
    st_tp_dlycfg = st_gp_SBLTSEAT_DLYLST[u1_a_dlyidx];
    u2_t_dly     = (U2)0U;
    u1_t_dlynum  = st_gp_SBLTSEAT_DLYLST_DLYNUM[u1_a_dlyidx];
    
    for (u1_t_cnt = (U1)0U; u1_t_cnt < u1_t_dlynum; u1_t_cnt++) {
        if (*u1p_a_sgnl == st_tp_dlycfg[u1_t_cnt].u1_jdgval) {   /* if an input signal equals to u1_jdgval */
            u2_t_dly = st_tp_dlycfg[u1_t_cnt].u2_dlycnt;         /* Set a delay-time                       */
        }
    }
    
    /* Counting Starts when first edge is detected */
    if ((*u1p_a_sgnl != *u1p_a_prvsgnl) && (*u2p_a_cnt == (U2)U2_MAX)) {
        *u2p_a_cnt = (U2)0U;
    }
    
    if (*u2p_a_cnt < u2_t_dly) {        /* if a value of delay counter is less than a delay-time   */
        *u1p_a_sgnl = *u1p_a_prvsgnl;   /* Overwrite an input signal to prev. signal               */
        (*u2p_a_cnt)++;
    } else {
        *u1p_a_prvsgnl = *u1p_a_sgnl;   /* Refresh a prev. signal                    */
        *u2p_a_cnt = (U2)U2_MAX;
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
/*  1.0.0    04/12/2018  HY       New.                                                                                               */
/*  1.1.0    06/03/2019  YI       Add rear seat buckled delay logic.                                                                 */
/*  1.1.1    09/23/2019  YI       Fix static analysis comment.                                                                       */
/*  2.0.0    10/08/2020  KK       MET-B_SEAREM-CSTD-1-03-A-C2                                                                        */
/*  2.1.0    01/12/2021  TN       MET-B_SEAREM-CSTD-1-06-A-C4                                                                        */
/*  2.1.1    10/18/2021  TA(M)    Change the definition of the null pointer used.(BSW v115_r007)                                     */
/*  2.1.2    06/13/2022  TK       Fixed 24FGM22-11011.                                                                               */
/*  2.2.0    02/28/2024  TH       for 19PFv3                                                                                         */
/*  2.2.1    06/02/2025  TH       Fixed : Keep State if Occupied SW signal = 11b                                                     */
/*                                                                                                                                   */
/*  * HY   = Hidefumi Yoshida, Denso                                                                                                 */
/*  * YI   = Yoshiki  Iwata,   Denso                                                                                                 */
/*  * KK   = Kohei Kato,       Denso Techno                                                                                          */
/*  * TN   = Tetsu Naruse,     Denso Techno                                                                                          */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*  * TK   = Takanori Kuno,    Denso Techno                                                                                          */
/*  * TH   = Taisuke Hirakawa, KSE                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
