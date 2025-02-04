/* 3.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  oilmil.c                                                                                                                         */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OILMIL_C_MAJOR                        (3)
#define OILMIL_C_MINOR                        (0)
#define OILMIL_C_PATCH                        (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oilmil_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((OILMIL_C_MAJOR != OILMIL_H_MAJOR) ||\
     (OILMIL_C_MINOR != OILMIL_H_MINOR) ||\
     (OILMIL_C_PATCH != OILMIL_H_PATCH))
#error "source and header files are inconsistent!"
#endif

#if ((OILMIL_C_MAJOR != OILMIL_CFG_H_MAJOR) ||\
     (OILMIL_C_MINOR != OILMIL_CFG_H_MINOR) ||\
     (OILMIL_C_PATCH != OILMIL_CFG_H_PATCH))
#error "source and private header files are inconsistent!"
#endif
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/* Communication Control State Definitions                                   */
/*---------------------------------------------------------------------------*/
#define OILMIL_TXCMPLTD         (0U)        /* reset complete                           */
#define OILMIL_TX1ST            (1U)        /* initial transmission                     */
#define OILMIL_CHKRX            (2U)        /* Waiting for the reset to complete        */

/*---------------------------------------------------------------------------*/
/* Communication Control Parameters                                          */
/*---------------------------------------------------------------------------*/
#define OILMIL_RSTREQINTVL      (2U)    /* Reset request event transmission interval    */
                                        /*                  100ms:LSB=50ms              */
#define OILMIL_RSTREQRTRY       (3U)    /* Event transmission retry count               */
#define OILMIL_RSTTOUT          (60U)   /* Reset request transmission time              */
                                        /*                  3s:LSB=50ms                 */
#define OILMIL_NONRST           (0x00U)
#define OILMIL_RSTCMP           (0x03U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U1  u1_comsts;                          /* Transmission / reception control status  */
    U1  u1_retry;                           /* Transmission retry counter               */
    U1  u1_txintvl;                         /* Transmission interval counter            */
    U1  u1_rstfail;                         /* Receive timeout counter                  */
}ST_OILMIL_CANCTL;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  ST_OILMIL_CANCTL    st_s_oilmil_canctl;         /* Oil Mileage Reset Status     */

static  U1                  u1_s_oilmil_unit;           /* Service Mileage Unit         */
static  S2                  s2_s_oilmil_val;            /* Service Mileage              */
static  U1                  u1_s_oilmil_inv;            /* Inverted Display Req         */
static  U1                  u1_s_oilmil_rst_sts;        /* Reset Status                 */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1   u1_s_OilmilRxOMWI2(void);
static void vd_s_OilmilRstTx(void);         /* Send oil suit reset request                            */
static void vd_s_OilmilDspJdg(void);        /* Determine what is displayed on the oil mileage display */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_OilmilInit(void)                                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_OilmilInit(void)
{
    st_s_oilmil_canctl.u1_comsts  = (U1)OILMIL_TXCMPLTD;
    st_s_oilmil_canctl.u1_retry   = (U1)0U;
    st_s_oilmil_canctl.u1_txintvl = (U1)0U;
    st_s_oilmil_canctl.u1_rstfail = (U1)0U;

    u1_s_oilmil_unit    = (U1)OILMIL_UNT_BLANK;                /* Service Mileage Unit          */
    s2_s_oilmil_val     = (S2)OILMIL_NONINDVAL1;               /* Service Mileage               */
    u1_s_oilmil_inv     = (U1)FALSE;                           /* Inverted Display Req          */
    u1_s_oilmil_rst_sts = (U1)OILMIL_RSTSTS_NON;               /* Reset Status                  */
}

/*===================================================================================================================================*/
/*  void    vd_g_OilmilMainTask(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_OilmilMainTask(void)
{
    U1  u1_t_igon;
    U1  u1_t_fncsts;

    u1_t_igon   = u1_g_VehopemdIgnOn();
    u1_t_fncsts = u1_g_OilmilFncRet();
    if((u1_t_igon   == (U1)TRUE) &&
       (u1_t_fncsts == (U1)TRUE)){
        vd_s_OilmilRstTx();
        vd_s_OilmilDspJdg();
    }
    else {
        vd_g_OilmilTxRstSig((U1)FALSE, (U1)FALSE);
        vd_g_OilmilInit();
    }
}

/*===================================================================================================================================*/
/*  void    vd_g_OilmilRstReq(void)                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_OilmilRstReq(void)
{
    if((st_s_oilmil_canctl.u1_comsts != (U1)OILMIL_TX1ST) &&
       (st_s_oilmil_canctl.u1_comsts != (U1)OILMIL_CHKRX)) {
        st_s_oilmil_canctl.u1_comsts = (U1)OILMIL_TX1ST;        /* No requests will be accepted during the reset process. */
        u1_s_oilmil_rst_sts          = (U1)OILMIL_RSTSTS_NON;
    }
}

/*===================================================================================================================================*/
/*  U1      u1_g_OilmilGetRstSts(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_OilmilGetRstSts(void)
{
    return(u1_s_oilmil_rst_sts);
}

/*===================================================================================================================================*/
/*  U1      u1_g_OilmilGetUnit(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:  -                                                                                                                    */
/*  Return:     u1_s_oilmil_unit : Oil Mileage Display Unit                                                                          */
/*===================================================================================================================================*/
U1      u1_g_OilmilGetUnit(void)
{
    return(u1_s_oilmil_unit);
}

/*===================================================================================================================================*/
/*  S2      s2_g_OilmilGetVal(void)                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:  -                                                                                                                    */
/*  Return:     s2_s_oilmil_val : Oil Mileage Display Value                                                                          */
/*===================================================================================================================================*/
S2      s2_g_OilmilGetVal(void)
{
    return(s2_s_oilmil_val);
}

/*===================================================================================================================================*/
/*  U1      u1_g_OilmilGetInv(void)                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:  -                                                                                                                    */
/*  Return:     u1_s_oilmil_inv : Oil Mileage Display Invert                                                                         */
/*===================================================================================================================================*/
U1      u1_g_OilmilGetInv(void)
{
    return(u1_s_oilmil_inv);
}


/*===================================================================================================================================*/
/*  vd_s_OilmilRstTx                                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_OilmilRstTx(void)
{
    U1  u1_t_omwi2;                                         /* OMWI Info                        */

    u1_t_omwi2 = u1_s_OilmilRxOMWI2();

    if(st_s_oilmil_canctl.u1_txintvl >= (U1)U1_MAX) {
        st_s_oilmil_canctl.u1_txintvl = (U1)U1_MAX;
    } else {
        st_s_oilmil_canctl.u1_txintvl++; /* QAC over-detection */
    }

    if(st_s_oilmil_canctl.u1_rstfail >= (U1)U1_MAX) {
        st_s_oilmil_canctl.u1_rstfail = (U1)U1_MAX;
    } else {
        st_s_oilmil_canctl.u1_rstfail++; /* QAC over-detection */
    }

    switch(st_s_oilmil_canctl.u1_comsts){
        case (U1)OILMIL_TX1ST:
            st_s_oilmil_canctl.u1_txintvl = (U1)0U;
            st_s_oilmil_canctl.u1_rstfail = (U1)0U;
            vd_g_OilmilTxRstSig((U1)TRUE, (U1)TRUE);
            st_s_oilmil_canctl.u1_retry   = (U1)1U;
            st_s_oilmil_canctl.u1_comsts  = (U1)OILMIL_CHKRX;
            break;
        case (U1)OILMIL_CHKRX:
            if((st_s_oilmil_canctl.u1_retry   <  (U1)OILMIL_RSTREQRTRY ) &&
               (st_s_oilmil_canctl.u1_txintvl >= (U1)OILMIL_RSTREQINTVL)){
                vd_g_OilmilTxRstSig((U1)TRUE, (U1)TRUE);
                st_s_oilmil_canctl.u1_txintvl = (U1)0U;
                st_s_oilmil_canctl.u1_retry ++;
            }
            if(u1_t_omwi2 == (U1)OILMIL_RSTCMP){
                vd_g_OilmilTxRstSig((U1)FALSE, (U1)FALSE);
                st_s_oilmil_canctl.u1_comsts = (U1)OILMIL_TXCMPLTD;
                u1_s_oilmil_rst_sts          = (U1)OILMIL_RSTSTS_COMP;
            }
            else if(st_s_oilmil_canctl.u1_rstfail > (U1)OILMIL_RSTTOUT){
                vd_g_OilmilTxRstSig((U1)FALSE, (U1)FALSE);
                st_s_oilmil_canctl.u1_comsts = (U1)OILMIL_TXCMPLTD;
                u1_s_oilmil_rst_sts          = (U1)OILMIL_RSTSTS_FAIL;
            }
            else{
                vd_g_OilmilTxRstSig((U1)TRUE, (U1)FALSE);
                st_s_oilmil_canctl.u1_comsts = (U1)OILMIL_CHKRX;
            }
            break;
        case (U1)OILMIL_TXCMPLTD:
        default:
            vd_g_OilmilTxRstSig((U1)FALSE, (U1)FALSE);
            st_s_oilmil_canctl.u1_comsts  = (U1)OILMIL_TXCMPLTD;
            st_s_oilmil_canctl.u1_retry   = (U1)0U;
            st_s_oilmil_canctl.u1_txintvl = (U1)0U;
            st_s_oilmil_canctl.u1_rstfail = (U1)0U;
            break;
    }
}
/*===================================================================================================================================*/
/*  static U1   u1_s_OilmilRxOMWI2(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1   u1_s_OilmilRxOMWI2(void)
{
    U1  u1_t_sts;
    U1  u1_t_omwi2;

    u1_t_omwi2  = (U1)0U;
    u1_t_sts    = u1_g_OilmilRxRstSig(&u1_t_omwi2);
    u1_t_sts   &= (U1)((U1)OILMIL_NO_RX | (U1)OILMIL_TIMEOUT);

    if(u1_t_sts != (U1)0U){
        u1_t_omwi2 = (U1)0U;
    }
    return(u1_t_omwi2);
}

/*===================================================================================================================================*/
/*  vd_s_OilmilDspJdg                                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_OilmilDspJdg(void)
{
    static const U1 u1_sp_OILMIL_UNIT[OILMIL_UNT_NUM] = {       /* Unit display table                                       */
        (U1)OILMIL_UNT_KM,
        (U1)OILMIL_UNT_MILE
    };

    U1      u1_t_msgsts;                                        /* Message state                                            */
    U1      u1_t_unitid;                                        /* Unit information                                         */

    u1_t_unitid = (U1)0U;
    u1_t_msgsts = u1_g_OilmilRxDspSig(&u1_t_unitid, &s2_s_oilmil_val, &u1_s_oilmil_inv);

    if((u1_t_msgsts & (U1)OILMIL_TIMEOUT) != (U1)0U){
        s2_s_oilmil_val = (S2)OILMIL_ABNVAL;                    /* u1_s_oilmil_inv & u1_s_oilmil_unit hold the final value  */
    }
    else if((u1_t_msgsts & (U1)OILMIL_NO_RX) != (U1)0U){
        u1_s_oilmil_unit = (U1)OILMIL_UNT_BLANK;
        s2_s_oilmil_val  = (S2)OILMIL_NONINDVAL1;
        u1_s_oilmil_inv  = (U1)FALSE;
    }
    else{
        if((s2_s_oilmil_val == (S2)OILMIL_NONINDVAL1) ||
           (s2_s_oilmil_val == (S2)OILMIL_NONINDVAL2)) {
            u1_s_oilmil_unit = (U1)OILMIL_UNT_BLANK;
        } else {
            if((s2_s_oilmil_val == (S2)OILMIL_BARVAL          ) ||        /* No invert when the bar or abnormal blank is displayed.  */
               ((s2_s_oilmil_val >= (S2)OILMIL_ABNVAL        ) && 
                (s2_s_oilmil_val <  (S2)OILMIL_GENERALVAL_MIN))) {
                u1_s_oilmil_inv  = (U1)FALSE;
            }

            if(u1_t_unitid < (U1)OILMIL_UNT_NUM){
                u1_s_oilmil_unit = u1_sp_OILMIL_UNIT[u1_t_unitid];
            }
            else{
                u1_s_oilmil_unit = (U1)OILMIL_UNT_BLANK;
            }
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
/*  1.0.0    07/01/2020  YN       New                                                                                                */
/*  2.0.1    10/25/2021  TA(M)    Changed to comply with secure coding rules, and refactoring                                        */
/*  2.1.0    01/24/2022  TA(M)    Change u1_g_OilmilRxRstSig                                                                         */
/*  3.0.0    02/02/2024  SN       Change for 19PFv3 PreCV                                                                            */
/*                                                                                                                                   */
/*  * YN   = Yasuhiro Nakamura, Denso Techno                                                                                         */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*  * SN   = Shota Nakano,    NTT Data MSE                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/
