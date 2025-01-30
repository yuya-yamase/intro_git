/* 1.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Multi-media rx multi frame message                                                                                               */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define MULMED_MULFR_C_MAJOR                    (1)
#define MULMED_MULFR_C_MINOR                    (1)
#define MULMED_MULFR_C_PATCH                    (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "mulmed_mulfr_cfg_private.h"
#include "memfill_u2.h"
#include "memfill_u1.h"
#include "memcpy_u2.h"
#include "memcpy_u1.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((MULMED_MULFR_C_MAJOR != MULMED_MULFR_H_MAJOR) || \
     (MULMED_MULFR_C_MINOR != MULMED_MULFR_H_MINOR) || \
     (MULMED_MULFR_C_PATCH != MULMED_MULFR_H_PATCH))
#error "mulmed_mulfr.c and mulmed_mulfr.h : source and header files are inconsistent!"
#endif

#if ((MULMED_MULFR_C_MAJOR != MULMED_MULFR_CFG_H_MAJOR) || \
     (MULMED_MULFR_C_MINOR != MULMED_MULFR_CFG_H_MINOR) || \
     (MULMED_MULFR_C_PATCH != MULMED_MULFR_CFG_H_PATCH))
#error "mulmed_mulfr.c and mulmed_mulfr_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define MULMED_MULFR_NUM_CHAR                   (3U)

#define MULMED_MULFR_ID_BITPOS                  (4U)
#define MULMED_MULFR_HCHAR_BITPOS               (8U)

#define MULMED_MULFR_ASS_CNTR                   (0U)
#define MULMED_MULFR_ASS_MODEID                 (1U)
#define MULMED_MULFR_ASS_SYNCID                 (2U)
#define MULMED_MULFR_ASS_TEXT                   (2U)

#define MULMED_MULFR_CNTR_ERR                   (0x00U)
#define MULMED_MULFR_CNTR_LST                   (0xFFU)
#define MULMED_MULFR_CNTR_MOD_LST               (0x00U)
#define MULMED_MULFR_CNTR_MOD_HDR               (0x01U)
#define MULMED_MULFR_CNTR_OFFSET                (2U)

#define MULMED_MULFR_IFDATA_NUM_SIDE            (2U)
#define MULMED_MULFR_IFDATA_SIDE_MSK            (0x01U)

#define MULMED_MULFR_MAXFR_PERLINE              ((MULMED_MULFR_MAX_TXTSIZE / MULMED_MULFR_NUM_CHAR) + 1U)       /* 1U : Header frame */

#define MULMED_MULFR_NUM_MLTLINE                (89U)
#define MULMED_MULFR_AVNMS24_OFS                (79U)

#define MULMED_MULFR_HDRFR                      (0x01U) /* Header frame         */
#define MULMED_MULFR_EOLFR                      (0x04U) /* End of line frame    */
#define MULMED_MULFR_LSTFR                      (0x06U) /* Last frame           */
#define MULMED_MULFR_CONFR                      (0x08U) /* Consecutive frame    */

#define MULMED_MULFR_VLDSYN                     (0x10U) /* Valid sync id        */
#define MULMED_MULFR_VLDSEQ                     (0x20U) /* Valid sequence       */

#define MULMED_MULFR_VLDHDRFR                   (MULMED_MULFR_HDRFR | MULMED_MULFR_VLDSYN)
#define MULMED_MULFR_VLDEOLFR                   (MULMED_MULFR_EOLFR | MULMED_MULFR_VLDSEQ)
#define MULMED_MULFR_VLDLSTFR                   (MULMED_MULFR_LSTFR | MULMED_MULFR_VLDSEQ)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct {
    U2                                          u2_txtbuf[MULMED_MULFR_IFDATA_NUM_SIDE][MULMED_MULFR_MAX_TXTSIZE];
    U1                                          u1_modeid[MULMED_MULFR_IFDATA_NUM_SIDE];
    U1                                          u1_option[MULMED_MULFR_IFDATA_NUM_SIDE][MULMED_MULFR_NUM_OPT];
    U1                                          u1_lineno[MULMED_MULFR_IFDATA_NUM_SIDE];
    U1                                          u1_charidx;
    U1                                          u1_vldseq;
    U1                                          u1_vldside;
    U1                                          u1_txsyncid;
} ST_MULMED_MULFR_IFDATA;

typedef struct {
    U2                                          u2_linbuf[MULMED_MULFR_MAX_TXTSIZE];
    U1                                          u1_option[MULMED_MULFR_NUM_OPT];
    U1                                          u1_modeid;
} ST_MULMED_MULFR_LINES;

typedef struct {
    U1                                          u1_modeidpos;
    U1                                          u1_cleartxt;
    U1                                          u1_linebufidx;
} ST_MULMED_MULFR_MODEID_INF;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  ST_MULMED_MULFR_IFDATA                  st_sp_mulmed_mulfr_ifdat[MULMED_MULFR_NUM_FR];
static  ST_MULMED_MULFR_LINES                   st_sp_mulmed_mulfr_lines[MULMED_MULFR_NUM_MLTLINE];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  void    vd_s_MulmedMulfrDataInit(ST_MULMED_MULFR_IFDATA * stp_a_ifdat);
static  void    vd_s_MulmedMulfrParseMsg(ST_MULMED_MULFR_IFDATA * stp_a_ifdat, const U1 * u1_ap_BUFF, const U1 u1_a_MODEID);
static  void    vd_s_MulmedMulfrJoinText(ST_MULMED_MULFR_IFDATA * stp_a_ifdat, const U1 * u1_ap_SGNL);
static  U1      u1_s_MulmedMulfrJoinAct(const U1 u1_a_VALID, const U1 * u1_ap_SGNL);
static  void    vd_s_MulmedMulfrGetTextData(U2 * u2_ap_txtbuf, const U1 * u1_ap_SGNL, const U1 u1_a_CHARIDX);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/* void            vd_g_MulmedMulfrInit(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_MulmedMulfrInit(void)
{
    ST_MULMED_MULFR_IFDATA *                    stp_t_ifdat;
    ST_MULMED_MULFR_LINES *                     stp_t_lines;
    U4                                          u4_t_loop;


    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)MULMED_MULFR_NUM_FR; u4_t_loop++) {
        stp_t_ifdat = &st_sp_mulmed_mulfr_ifdat[u4_t_loop];

        vd_s_MulmedMulfrDataInit(stp_t_ifdat);
    }

    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)MULMED_MULFR_NUM_MLTLINE; u4_t_loop++) {
        stp_t_lines = &st_sp_mulmed_mulfr_lines[u4_t_loop];

        vd_g_MemfillU2(stp_t_lines->u2_linbuf, (U2)0U, (U4)MULMED_MULFR_MAX_TXTSIZE);
        vd_g_MemfillU1(stp_t_lines->u1_option, (U1)0U, (U4)MULMED_MULFR_NUM_OPT    );
        stp_t_lines->u1_modeid = (U1)0U;
    }


    vd_g_MulmedMulfrCfgInit();
}

/*===================================================================================================================================*/
/* void            vd_g_MulmedMulfrMainTask(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_MulmedMulfrMainTask(void)
{
    static  const   ST_MULMED_MULFR_MODEID_INF  st_sp_MODEID_INF[MULMED_MULFR_NUM_FR]                   = {
        {   (U1)MULMED_MULFR_ID_BITPOS,         (U1)TRUE,       (U1)U1_MAX                          },  /* MSG_AVNMS01_RXCH1 */
        {   (U1)MULMED_MULFR_ID_BITPOS,         (U1)TRUE,       (U1)U1_MAX                          },  /* MSG_AVNMS02_RXCH1 */
        {   (U1)MULMED_MULFR_ID_BITPOS,         (U1)TRUE,       (U1)U1_MAX                          },  /* MSG_AVNMS03_RXCH1 */
        {   (U1)0U,                             (U1)FALSE,      (U1)U1_MAX                          },  /* MSG_AVNMS04_RXCH1 */
        {   (U1)0U,                             (U1)FALSE,      (U1)U1_MAX                          },  /* MSG_AVNMS05_RXCH1 */
        {   (U1)0U,                             (U1)TRUE,       (U1)U1_MAX                          },  /* MSG_AVNMS06_RXCH1 */
        {   (U1)0U,                             (U1)TRUE,       (U1)U1_MAX                          },  /* MSG_AVNMS07_RXCH1 */
        {   (U1)0U,                             (U1)TRUE,       (U1)U1_MAX                          },  /* MSG_AVNMS08_RXCH1 */
        {   (U1)0U,                             (U1)TRUE,       (U1)U1_MAX                          },  /* MSG_AVNMS09_RXCH1 */
        {   (U1)0U,                             (U1)TRUE,       (U1)U1_MAX                          },  /* MSG_AVNMS10_RXCH1 */
        {   (U1)0U,                             (U1)FALSE,      (U1)0U                              },  /* MSG_AVNMS13_RXCH1 */
        {   (U1)0U,                             (U1)FALSE,      (U1)6U                              },  /* MSG_AVNMS14_RXCH1 */
        {   (U1)0U,                             (U1)FALSE,      (U1)12U                             },  /* MSG_AVNMS15_RXCH1 */
        {   (U1)0U,                             (U1)FALSE,      (U1)18U                             },  /* MSG_AVNMS16_RXCH1 */
        {   (U1)0U,                             (U1)FALSE,      (U1)24U                             },  /* MSG_AVNMS18_RXCH1 */
        {   (U1)0U,                             (U1)FALSE,      (U1)30U                             },  /* MSG_AVNMS19_RXCH1 */
        {   (U1)0U,                             (U1)FALSE,      (U1)36U                             },  /* MSG_AVNMS20_RXCH1 */
        {   (U1)0U,                             (U1)FALSE,      (U1)59U                             },  /* MSG_AVNMS21_RXCH1 */
        {   (U1)0U,                             (U1)FALSE,      (U1)64U                             },  /* MSG_AVNMS22_RXCH1 */
        {   (U1)0U,                             (U1)FALSE,      (U1)69U                             },  /* MSG_AVNMS23_RXCH1 */
        {   (U1)0U,                             (U1)FALSE,      (U1)U1_MAX                          },  /* MSG_AVNMS24_RXCH1 */
        {   (U1)0U,                             (U1)FALSE,      (U1)U1_MAX                          },  /* MSG_AVNMS25_RXCH1 */
        {   (U1)0U,                             (U1)FALSE,      (U1)U1_MAX                          },  /* MSG_AVNMS26_RXCH1 */
        {   (U1)MULMED_MULFR_ID_BITPOS,         (U1)TRUE,       (U1)U1_MAX                          }   /* MSG_AVNMS79_RXCH1 */
    };
    ST_MULMED_MULFR_IFDATA *                    stp_t_ifdat;
    ST_MULMED_MULFR_LINES *                     stp_t_lines;
    U4                                          u4_t_loop;
    U1                                          u1_t_accon;
    U1                                          u1_t_sts_status;
    U1                                          u1_t_sts_modeid;
    U1                                          u1_tp_rxbuff[MULMED_MULFR_CAN_BUFF_SIZE];
    U1                                          u1_t_updtsd;
    U1                                          u1_t_linebufidx;


    u1_t_accon = u1_g_MulmedMulfrAccOn();
    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)MULMED_MULFR_NUM_FR; u4_t_loop++) {
        stp_t_ifdat = &st_sp_mulmed_mulfr_ifdat[u4_t_loop];

        u1_t_sts_modeid = (U1)0U;
        u1_t_sts_status = u1_g_MulmedMulfrCfgRxTxtSts(u4_t_loop, &u1_t_sts_modeid);
        vd_g_MulmedMulfrCfgGetTxtDat(u4_t_loop, &u1_tp_rxbuff[0]);

        if (u1_t_sts_status == (U1)MULMED_MULFR_STSBIT_VALID) {
            if ((u1_t_sts_modeid != stp_t_ifdat->u1_modeid[stp_t_ifdat->u1_vldside]) &&
                (st_sp_MODEID_INF[u4_t_loop].u1_cleartxt == (U1)TRUE               )) {

                vd_g_MemfillU2(stp_t_ifdat->u2_txtbuf[stp_t_ifdat->u1_vldside], (U2)0U, (U4)MULMED_MULFR_MAX_TXTSIZE);
                vd_g_MemfillU1(stp_t_ifdat->u1_option[stp_t_ifdat->u1_vldside], (U1)0U, (U4)MULMED_MULFR_NUM_OPT    );
            }
            u1_t_updtsd = stp_t_ifdat->u1_vldside ^ (U1)MULMED_MULFR_IFDATA_SIDE_MSK;
            stp_t_ifdat->u1_modeid[u1_t_updtsd] = u1_t_sts_modeid;

            u1_t_sts_modeid <<= st_sp_MODEID_INF[u4_t_loop].u1_modeidpos;
            vd_s_MulmedMulfrParseMsg(stp_t_ifdat, u1_tp_rxbuff, u1_t_sts_modeid);
        }
        else{
            stp_t_ifdat->u1_modeid[stp_t_ifdat->u1_vldside] = u1_t_sts_modeid;
        }

        if (u1_t_accon != (U1)TRUE) {
            vd_s_MulmedMulfrDataInit(stp_t_ifdat);
        }
        else {
            vd_g_MulmedMulfrCfgTxSyncID(u4_t_loop, stp_t_ifdat->u1_txsyncid);
        }

        /* Multiline text */
        if ((st_sp_MODEID_INF[u4_t_loop].u1_linebufidx       != (U1)U1_MAX) &&
            (stp_t_ifdat->u1_lineno[stp_t_ifdat->u1_vldside] != (U1)U1_MAX)) {

            u1_t_linebufidx = st_sp_MODEID_INF[u4_t_loop].u1_linebufidx + stp_t_ifdat->u1_lineno[stp_t_ifdat->u1_vldside];
            stp_t_lines     = &st_sp_mulmed_mulfr_lines[u1_t_linebufidx];

            vd_g_MemcpyU2(stp_t_lines->u2_linbuf, stp_t_ifdat->u2_txtbuf[stp_t_ifdat->u1_vldside], (U4)MULMED_MULFR_MAX_TXTSIZE);
            vd_g_MemcpyU1(stp_t_lines->u1_option, stp_t_ifdat->u1_option[stp_t_ifdat->u1_vldside], (U4)MULMED_MULFR_NUM_OPT    );
            stp_t_lines->u1_modeid = stp_t_ifdat->u1_modeid[stp_t_ifdat->u1_vldside];
        }
    }
}

/*===================================================================================================================================*/
/* void            vd_g_MulmedTextMsg(const U1 u1_a_LINEID, U1 * u1p_a_modeid, U1 * u1_ap_options, U2 * u2_ap_rxtext)                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_MulmedTextMsg(const U1 u1_a_LINEID, U1 * u1p_a_modeid, U1 * u1_ap_options, U2 * u2_ap_rxtext)
{
    ST_MULMED_MULFR_IFDATA *                    stp_t_ifdat;
    ST_MULMED_MULFR_LINES *                     stp_t_lines;


    if ((u1p_a_modeid  != vdp_PTR_NA                 ) &&
        (u1_ap_options != vdp_PTR_NA                 ) &&
        (u2_ap_rxtext  != vdp_PTR_NA                 )) {

        if ((u1_a_LINEID >= (U1)MULMED_MULFR_AVNMS13_L01) &&
            (u1_a_LINEID <= (U1)MULMED_MULFR_AVNMS23_L20)) {

            stp_t_lines     = &st_sp_mulmed_mulfr_lines[u1_a_LINEID - (U1)MULMED_MULFR_AVNMS13_L01];
            (*u1p_a_modeid) = stp_t_lines->u1_modeid;
            vd_g_MemcpyU2(u2_ap_rxtext,  stp_t_lines->u2_linbuf, (U4)MULMED_MULFR_MAX_TXTSIZE);
            vd_g_MemcpyU1(u1_ap_options, stp_t_lines->u1_option, (U4)MULMED_MULFR_NUM_OPT    );
        }
        else if (u1_a_LINEID  < (U1)MULMED_MULFR_NUM_LINES) {
            if (u1_a_LINEID <=  (U1)MULMED_MULFR_AVNMS10_L01) {
                stp_t_ifdat = &st_sp_mulmed_mulfr_ifdat[u1_a_LINEID];
            }
            else {
                stp_t_ifdat = &st_sp_mulmed_mulfr_ifdat[u1_a_LINEID - (U1)MULMED_MULFR_AVNMS24_OFS];
            }
            (*u1p_a_modeid) = stp_t_ifdat->u1_modeid[stp_t_ifdat->u1_vldside];
            vd_g_MemcpyU2(u2_ap_rxtext,  stp_t_ifdat->u2_txtbuf[stp_t_ifdat->u1_vldside], (U4)MULMED_MULFR_MAX_TXTSIZE);
            vd_g_MemcpyU1(u1_ap_options, stp_t_ifdat->u1_option[stp_t_ifdat->u1_vldside], (U4)MULMED_MULFR_NUM_OPT    );
        }
        else {
            /* Do nothing */
        }
    }
}

/*===================================================================================================================================*/
/* void            vd_g_MulmedMulfrRxTxtHk(const U2 u2_a_MSG)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_MulmedMulfrRxTxtHk(const U2 u2_a_MSG)
{
    if ((u2_a_MSG <= u2_g_MULMED_MULFR_AUB_MAX) &&
        (u2_a_MSG >= u2_g_MULMED_MULFR_AUB_MIN)) {

        vd_g_MulmedMulfrCfgRxTxtHk(u2_a_MSG);
    }
}

/*===================================================================================================================================*/
/* static  void    vd_s_MulmedMulfrDataInit(ST_MULMED_MULFR_IFDATA * stp_a_ifdat)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_MulmedMulfrDataInit(ST_MULMED_MULFR_IFDATA * stp_a_ifdat)
{
    U4          u4_t_loop;


    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)MULMED_MULFR_IFDATA_NUM_SIDE; u4_t_loop++) {
        vd_g_MemfillU2(stp_a_ifdat->u2_txtbuf[u4_t_loop], (U2)0U, (U4)MULMED_MULFR_MAX_TXTSIZE);
        vd_g_MemfillU1(stp_a_ifdat->u1_option[u4_t_loop], (U1)0U, (U4)MULMED_MULFR_NUM_OPT    );
        stp_a_ifdat->u1_modeid[u4_t_loop] = (U1)0U;
        stp_a_ifdat->u1_lineno[u4_t_loop] = (U1)U1_MAX;
    }
    stp_a_ifdat->u1_charidx  = (U1)U1_MAX;
    stp_a_ifdat->u1_vldseq   = (U1)FALSE;
    stp_a_ifdat->u1_vldside  = (U1)0U;
    stp_a_ifdat->u1_txsyncid = (U1)MULMED_MULFR_SYNCID_INIT;
}

/*===================================================================================================================================*/
/* static  void    vd_s_MulmedMulfrParseMsg(ST_MULMED_MULFR_IFDATA * stp_a_ifdat, const U1 * u1_ap_BUFF, const U1 u1_a_MODEID)       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_MulmedMulfrParseMsg(ST_MULMED_MULFR_IFDATA * stp_a_ifdat, const U1 * u1_ap_BUFF, const U1 u1_a_MODEID)
{
    U4          u4_t_loop;
    U4          u4_t_buffidx;


    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)MULMED_MULFR_NUM_TXT_MSG; u4_t_loop++) {
        u4_t_buffidx = u4_t_loop * (U4)MULMED_MULFR_CAN_DLC;
        if ((u1_a_MODEID               == u1_ap_BUFF[u4_t_buffidx + (U4)MULMED_MULFR_ASS_MODEID]) &&
            ((U1)MULMED_MULFR_CNTR_ERR != u1_ap_BUFF[u4_t_buffidx]                              )) {

            vd_s_MulmedMulfrJoinText(stp_a_ifdat, &u1_ap_BUFF[u4_t_buffidx]);
        }
    }
}

/*===================================================================================================================================*/
/* static  void    vd_s_MulmedMulfrJoinText(ST_MULMED_MULFR_IFDATA * stp_a_ifdat, const U1 * u1_ap_SGNL)                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_MulmedMulfrJoinText(ST_MULMED_MULFR_IFDATA * stp_a_ifdat, const U1 * u1_ap_SGNL)
{
    U1          u1_t_updtsd;
    U1          u1_t_chrpos;
    U1          u1_t_act;


    u1_t_updtsd = stp_a_ifdat->u1_vldside ^ (U1)MULMED_MULFR_IFDATA_SIDE_MSK;
    u1_t_chrpos = u1_ap_SGNL[MULMED_MULFR_ASS_CNTR] % (U1)MULMED_MULFR_MAXFR_PERLINE;
    u1_t_act    = u1_s_MulmedMulfrJoinAct(stp_a_ifdat->u1_vldseq, u1_ap_SGNL);

    if ((u1_t_act & (U1)MULMED_MULFR_VLDHDRFR) == (U1)MULMED_MULFR_VLDHDRFR ) {
        vd_g_MemcpyU1(stp_a_ifdat->u1_option[u1_t_updtsd], &u1_ap_SGNL[MULMED_MULFR_ASS_SYNCID], (U4)MULMED_MULFR_NUM_OPT);
        stp_a_ifdat->u1_vldseq = (U1)TRUE;
    }
    if ((u1_t_act & (U1)MULMED_MULFR_HDRFR)    == (U1)MULMED_MULFR_HDRFR    ) {
        stp_a_ifdat->u1_charidx             = (U1)U1_MAX;
        stp_a_ifdat->u1_lineno[u1_t_updtsd] = u1_ap_SGNL[MULMED_MULFR_ASS_CNTR] / (U1)MULMED_MULFR_MAXFR_PERLINE;
        vd_g_MemfillU2(stp_a_ifdat->u2_txtbuf[u1_t_updtsd], (U2)0U, (U4)MULMED_MULFR_MAX_TXTSIZE);
    }
    if ((u1_t_act & (U1)MULMED_MULFR_VLDEOLFR) == (U1)MULMED_MULFR_VLDEOLFR ) {
        if (stp_a_ifdat->u1_charidx != (U1)U1_MAX) {
            stp_a_ifdat->u1_charidx++;
        }
        else {
            stp_a_ifdat->u1_charidx = (U1)0U;
        }
        vd_s_MulmedMulfrGetTextData(stp_a_ifdat->u2_txtbuf[u1_t_updtsd], u1_ap_SGNL, stp_a_ifdat->u1_charidx);
        stp_a_ifdat->u1_vldside = u1_t_updtsd;
        stp_a_ifdat->u1_vldseq = (U1)FALSE;
    }
    if ((u1_t_act & (U1)MULMED_MULFR_VLDLSTFR) == (U1)MULMED_MULFR_VLDLSTFR ) {
        stp_a_ifdat->u1_txsyncid = stp_a_ifdat->u1_option[u1_t_updtsd][0] >> MULMED_MULFR_ID_BITPOS;
    }
    if ((u1_t_act & (U1)MULMED_MULFR_CONFR)    == (U1)MULMED_MULFR_CONFR    ) {
        stp_a_ifdat->u1_charidx = u1_t_chrpos - (U1)MULMED_MULFR_CNTR_OFFSET;
        vd_s_MulmedMulfrGetTextData(stp_a_ifdat->u2_txtbuf[u1_t_updtsd], u1_ap_SGNL, stp_a_ifdat->u1_charidx);
    }
}

/*===================================================================================================================================*/
/* static  U1      u1_s_MulmedMulfrJoinAct(const U1 u1_a_VALID, const U1 * u1_ap_SGNL)                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_MulmedMulfrJoinAct(const U1 u1_a_VALID, const U1 * u1_ap_SGNL)
{
    U1          u1_t_hdrchk;
    U1          u1_t_dat_syncid;
    U1          u1_t_act;


    u1_t_hdrchk     = u1_ap_SGNL[MULMED_MULFR_ASS_CNTR] % (U1)MULMED_MULFR_MAXFR_PERLINE;
    u1_t_dat_syncid = u1_ap_SGNL[MULMED_MULFR_ASS_SYNCID] >> MULMED_MULFR_ID_BITPOS;
    u1_t_act        = (U1)0U;

    if (u1_t_hdrchk                            == (U1)MULMED_MULFR_CNTR_MOD_HDR) {
        u1_t_act  = (U1)MULMED_MULFR_HDRFR;
    }
    else if (u1_ap_SGNL[MULMED_MULFR_ASS_CNTR] == (U1)MULMED_MULFR_CNTR_LST    ) {
        u1_t_act |= (U1)MULMED_MULFR_LSTFR;
    }
    else if (u1_t_hdrchk                       == (U1)MULMED_MULFR_CNTR_MOD_LST) {
        u1_t_act |= (U1)MULMED_MULFR_EOLFR;
    }
    else {
        u1_t_act |= (U1)MULMED_MULFR_CONFR;
    }

    if ((u1_t_dat_syncid != (U1)MULMED_MULFR_SYNCID_INIT   ) &&
        (u1_t_dat_syncid != (U1)MULMED_MULFR_SYNCID_INVALID)) {

        u1_t_act |= (U1)MULMED_MULFR_VLDSYN;
    }
    if (u1_a_VALID == (U1)TRUE) {
        u1_t_act |= (U1)MULMED_MULFR_VLDSEQ;
    }

    return (u1_t_act);
}

/*===================================================================================================================================*/
/* static  void    vd_s_MulmedMulfrGetTextData(U2 * u2_ap_txtbuf, const U1 * u1_ap_SGNL, const U1 u1_a_CHARIDX)                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_MulmedMulfrGetTextData(U2 * u2_ap_txtbuf, const U1 * u1_ap_SGNL, const U1 u1_a_CHARIDX)
{
    U4          u4_t_loop;
    U4          u4_t_dstidx;
    U4          u4_t_charidx;


    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)MULMED_MULFR_NUM_CHAR; u4_t_loop++) {
        u4_t_dstidx  = ((U4)u1_a_CHARIDX * (U4)MULMED_MULFR_NUM_CHAR) + u4_t_loop;
        u4_t_charidx = (U4)MULMED_MULFR_ASS_TEXT + (U4)(u4_t_loop << 1);

        if (u4_t_dstidx < (U4)MULMED_MULFR_MAX_TXTSIZE){
            u2_ap_txtbuf[u4_t_dstidx]  = (U2)((U2)u1_ap_SGNL[u4_t_charidx] << MULMED_MULFR_HCHAR_BITPOS);
            u4_t_charidx++;
            u2_ap_txtbuf[u4_t_dstidx] |= (U2)u1_ap_SGNL[u4_t_charidx];
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
/*  1.0.0    12/03/2018  HY       New.                                                                                               */
/*  1.1.0    10/14/2021  KT       config for 22-24FGM.                                                                               */
/*                                                                                                                                   */
/*  * HY   = Hidefumi Yoshida, Denso                                                                                                 */
/*  * KT   = Kou Tsujii, Denso Techno                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/
