/* 0.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  DtcCtl                                                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "DtcCtl.h"
#include "x_spi_ivi_sub1_diag.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define DTCCTL_CNT_INI              (0xFFU)
#define DTCCTL_CNT_STA              (0U)
#define DTCCTL_CNT_1S               (100U)  /* LSB:10ms */

#define DTCCTL_REQ_INI              (0xFFU)

#define DTCCTL_DTCCODE_KIND         (2U)
#define DTCCTL_DTCCODE_CTG          (0U)
#define DTCCTL_DTCCODE_DIAG         (1U)

#define DTCCTL_CTG_NAVI             (0x58U)
#define DTCCTL_CTG_VOL              (0x74U)
#define DTCCTL_CTG_CAN              (0x01U)

#define DTCCTL_DIAG_GYR_ERR         (0x10U)
#define DTCCTL_DIAG_GSNS_ERR        (0x18U)
#define DTCCTL_DIAG_GNSS_LOW        (0x41U)
#define DTCCTL_DIAG_GNSS_OPEN       (0x40U)
#define DTCCTL_DIAG_PWR_SHCT        (0x40U)
#define DTCCTL_DIAG_PWR_SHCT_DC     (0x41U)
#define DTCCTL_DIAG_PWR_UNCN_RF     (0x50U)
#define DTCCTL_DIAG_PWR_UNCN_LF     (0x51U)
#define DTCCTL_DIAG_PWR_UNCN_RBD    (0x52U)
#define DTCCTL_DIAG_PWR_UNCN_LBD    (0x53U)
#define DTCCTL_DIAG_CAN_2M1_REGERR  (0x41U)
#define DTCCTL_DIAG_CAN_2M1_BUSOFF  (0x43U)
#define DTCCTL_DIAG_CAN_2M1_LOCK    (0x42U)
#define DTCCTL_DIAG_CAN_5M_REGERR   (0x44U)
#define DTCCTL_DIAG_CAN_5M_BUSOFF   (0x46U)
#define DTCCTL_DIAG_CAN_5M_LOCK     (0x45U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct {
    U1  u1_category_code;
    U1  u1_diag_code;
    U1  u1_dtcsts;
} ST_DTCCTL_DTCCODE;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1                   u1_s_dtcctl_timecnt_10ms[DTCCTL_DTCID_NUM];
static ST_DTCCTL_DTCCODE    st_s_dtcctl_dtcreq[DTCCTL_DTCID_NUM];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void    vd_s_DtcCtl_ChkSend(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1 u1_s_DTCCTL_DTCLIST[DTCCTL_DTCID_NUM][DTCCTL_DTCCODE_KIND] = {
        {(U1)DTCCTL_CTG_NAVI, (U1)DTCCTL_DIAG_GYR_ERR     }, /* DTCCTL_DTCID_GYR_ERR      */
        {(U1)DTCCTL_CTG_NAVI, (U1)DTCCTL_DIAG_GSNS_ERR    }, /* DTCCTL_DTCID_GSNS_ERR     */
        {(U1)DTCCTL_CTG_NAVI, (U1)DTCCTL_DIAG_GNSS_LOW    }, /* DTCCTL_DTCID_GNSS_LOW     */
        {(U1)DTCCTL_CTG_NAVI, (U1)DTCCTL_DIAG_GNSS_OPEN   }, /* DTCCTL_DTCID_GNSS_OPEN    */
        {(U1)DTCCTL_CTG_VOL,  (U1)DTCCTL_DIAG_PWR_SHCT    }, /* DTCCTL_DTCID_PWR_SHCT     */
        {(U1)DTCCTL_CTG_VOL,  (U1)DTCCTL_DIAG_PWR_SHCT_DC }, /* DTCCTL_DTCID_PWR_SHCT_DC  */
        {(U1)DTCCTL_CTG_VOL,  (U1)DTCCTL_DIAG_PWR_UNCN_RF }, /* DTCCTL_DTCID_PWR_UNCN_RF  */
        {(U1)DTCCTL_CTG_VOL,  (U1)DTCCTL_DIAG_PWR_UNCN_LF }, /* DTCCTL_DTCID_PWR_UNCN_LF  */
        {(U1)DTCCTL_CTG_VOL,  (U1)DTCCTL_DIAG_PWR_UNCN_RBD}, /* DTCCTL_DTCID_PWR_UNCN_RBD */
        {(U1)DTCCTL_CTG_VOL,  (U1)DTCCTL_DIAG_PWR_UNCN_LBD},  /* DTCCTL_DTCID_PWR_UNCN_LBD */
        {(U1)DTCCTL_CTG_CAN,  (U1)DTCCTL_DIAG_CAN_2M1_REGERR},  /*  */
        {(U1)DTCCTL_CTG_CAN,  (U1)DTCCTL_DIAG_CAN_2M1_BUSOFF},  /*  */
        {(U1)DTCCTL_CTG_CAN,  (U1)DTCCTL_DIAG_CAN_2M1_LOCK},  /*  */
        {(U1)DTCCTL_CTG_CAN,  (U1)DTCCTL_DIAG_CAN_5M_REGERR},  /*  */
        {(U1)DTCCTL_CTG_CAN,  (U1)DTCCTL_DIAG_CAN_5M_REGERR},  /*  */
        {(U1)DTCCTL_CTG_CAN,  (U1)DTCCTL_DIAG_CAN_5M_REGERR}  /*  */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_DtcCtl_Init(void)                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_DtcCtl_Init(void)
{
    U1 u1_t_cnt;

    for(u1_t_cnt = (U1)0U; u1_t_cnt < (U1)DTCCTL_DTCID_NUM; u1_t_cnt++){
        st_s_dtcctl_dtcreq[u1_t_cnt].u1_category_code = (U1)DTCCTL_REQ_INI;
        st_s_dtcctl_dtcreq[u1_t_cnt].u1_diag_code = (U1)DTCCTL_REQ_INI;
        st_s_dtcctl_dtcreq[u1_t_cnt].u1_dtcsts = (U1)DTCCTL_REQ_INI;
        u1_s_dtcctl_timecnt_10ms[u1_t_cnt] = (U1)DTCCTL_CNT_INI;
    }
}

/*===================================================================================================================================*/
/*  void    vd_g_DtcCtl_MainTask(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_DtcCtl_MainTask(void)
{
    U1 u1_t_cnt;

    for(u1_t_cnt = (U1)0U; u1_t_cnt < (U1)DTCCTL_DTCID_NUM; u1_t_cnt++){
        if(u1_s_dtcctl_timecnt_10ms[u1_t_cnt] < (U1)U1_MAX){
            u1_s_dtcctl_timecnt_10ms[u1_t_cnt]++;
        }
    }
    vd_s_DtcCtl_ChkSend();
}

/*===================================================================================================================================*/
/*  static void    vd_s_DtcCtl_ChkSend(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_DtcCtl_ChkSend(void)
{
    U1 u1_t_cnt;

    for(u1_t_cnt = (U1)0U; u1_t_cnt < (U1)DTCCTL_DTCID_NUM; u1_t_cnt++){
        if((u1_s_dtcctl_timecnt_10ms[u1_t_cnt] != (U1)DTCCTL_CNT_INI) &&
           (u1_s_dtcctl_timecnt_10ms[u1_t_cnt] >= (U1)DTCCTL_CNT_1S)){
            vd_g_XspiIviSub1_DiagDtcrecSend(st_s_dtcctl_dtcreq[u1_t_cnt].u1_category_code,
                                            st_s_dtcctl_dtcreq[u1_t_cnt].u1_diag_code,
                                            st_s_dtcctl_dtcreq[u1_t_cnt].u1_dtcsts);
            u1_s_dtcctl_timecnt_10ms[u1_t_cnt] = (U1)DTCCTL_CNT_STA;
            break;
        }
    }
}

/*===================================================================================================================================*/
/*  void    vd_g_DtcCtl_SetDtcId(const U1 u1_a_DTCID, const U1 u1_a_STATUS)                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_DtcCtl_SetDtcId(const U1 u1_a_DTCID, const U1 u1_a_STATUS)
{
    st_s_dtcctl_dtcreq[u1_a_DTCID].u1_category_code = u1_s_DTCCTL_DTCLIST[u1_a_DTCID][DTCCTL_DTCCODE_CTG];
    st_s_dtcctl_dtcreq[u1_a_DTCID].u1_diag_code = u1_s_DTCCTL_DTCLIST[u1_a_DTCID][DTCCTL_DTCCODE_DIAG];
    st_s_dtcctl_dtcreq[u1_a_DTCID].u1_dtcsts = u1_a_STATUS;
    u1_s_dtcctl_timecnt_10ms[u1_a_DTCID] = (U1)DTCCTL_CNT_1S;
}

/*===================================================================================================================================*/
/*  void    vd_g_DtcCtl_RecDtc(const U1 u1_a_DTC1, const U1 u1_a_DTC2, const U1 u1_a_STATUS)                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_DtcCtl_RecDtc(const U1 u1_a_DTC1, const U1 u1_a_DTC2, const U1 u1_a_STATUS)
{
    U1 u1_t_ctgcode;
    U1 u1_t_diagcode;
    U1 u1_t_status;
    U1 u1_t_cnt;

    for(u1_t_cnt = (U1)0U; u1_t_cnt < (U1)DTCCTL_DTCID_NUM; u1_t_cnt++){
        u1_t_ctgcode = st_s_dtcctl_dtcreq[u1_t_cnt].u1_category_code;
        u1_t_diagcode = st_s_dtcctl_dtcreq[u1_t_cnt].u1_diag_code;
        u1_t_status = st_s_dtcctl_dtcreq[u1_t_cnt].u1_dtcsts;
        if(((u1_t_ctgcode == u1_a_DTC1) && (u1_t_diagcode == u1_a_DTC2)) && (u1_t_status == u1_a_STATUS)){
            st_s_dtcctl_dtcreq[u1_t_cnt].u1_category_code = (U1)DTCCTL_REQ_INI;
            st_s_dtcctl_dtcreq[u1_t_cnt].u1_diag_code = (U1)DTCCTL_REQ_INI;
            st_s_dtcctl_dtcreq[u1_t_cnt].u1_dtcsts = (U1)DTCCTL_REQ_INI;
            u1_s_dtcctl_timecnt_10ms[u1_t_cnt] = (U1)DTCCTL_CNT_INI;
        break;
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
/*  0.0.0    05/26/2025  TN       New.                                                                                               */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*  * TN   = Tatsuya Niimi, KSE                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/
