/* 0.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  CXD4984ERCtl                                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "CXD4984ERCtl.h"

#include "PictCtl.h"
#include "Dio.h"
#include "gpi2c_ma.h"
#include "Mcu_I2c_Ctrl_private.h"
#include "Mcu_Sys_Pwr_Gvif3Rx.h"
#include "gvif3rx.h"
#include "pictic.h"
#include "SysEcDrc.h"
#include "RobCtl.h"
#include "PwrCtl.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GVIF3RX_CHKTIME                         (50U)
#define GVIF3RX_CNT_CLR                         (0U)

#define GVIF3RX_MAINTASK_STEP1                  (1U)
#define GVIF3RX_MAINTASK_STEP2                  (2U)
#define GVIF3RX_MAINTASK_STEP3                  (3U)

#define GVIF3RX_PERIMONI_STEP1                  (1U)
#define GVIF3RX_PERIMONI_STEP2                  (2U)
#define GVIF3RX_PERIMONI_STEP3                  (3U)
#define GVIF3RX_PERIMONI_STEP4                  (4U)
#define GVIF3RX_PERIMONI_STEP5                  (5U)
#define GVIF3RX_PERIMONI_STEP6                  (6U)
#define GVIF3RX_PERIMONI_STEP7                  (7U)
#define GVIF3RX_PERIMONI_STEP8                  (8U)
#define GVIF3RX_PERIMONI_STEP9                  (9U)
#define GVIF3RX_PERIMONI_STEP10                 (10U)
#define GVIF3RX_PERIMONI_STEP11                 (11U)
#define GVIF3RX_PERIMONI_STEP12                 (12U)
#define GVIF3RX_PERIMONI_STEP13                 (13U)
#define GVIF3RX_PERIMONI_STEP14                 (14U)
#define GVIF3RX_PERIMONI_STEP15                 (15U)
#define GVIF3RX_PERIMONI_STEP16                 (16U)
#define GVIF3RX_PERIMONI_STEP17                 (17U)
#define GVIF3RX_PERIMONI_STEP18                 (18U)
#define GVIF3RX_PERIMONI_STEP_FIN               (19U)

#define GVIF3RX_MIPI_STEP1                      (1U)
#define GVIF3RX_MIPI_STEP2                      (2U)

#define GVIF3RX_DEVERR_STEP1                    (1U)
#define GVIF3RX_DEVERR_STEP2                    (2U)

#define GVIF3RX_SIPERR_STEP1                    (1U)
#define GVIF3RX_SIPERR_STEP2                    (2U)

#define GVIF3RX_LINK_STEP1                      (1U)
#define GVIF3RX_LINK_STEP2                      (2U)

#define GVIF3RX_ERROR1_STEP1                    (1U)
#define GVIF3RX_ERROR1_STEP2                    (2U)

#define GVIF3RX_ERROR2_STEP1                    (1U)
#define GVIF3RX_ERROR2_STEP2                    (2U)

#define GVIF3RX_ERROR3_STEP1                    (1U)
#define GVIF3RX_ERROR3_STEP2                    (2U)

#define GVIF3RX_ERROR4_STEP1                    (1U)
#define GVIF3RX_ERROR4_STEP2                    (2U)

#define GVIF3RX_ERROR5_STEP1                    (1U)
#define GVIF3RX_ERROR5_STEP2                    (2U)

#define GVIF3RX_ERROR6_STEP1                    (1U)
#define GVIF3RX_ERROR6_STEP2                    (2U)

#define GVIF3RX_ERROR7_STEP1                    (1U)
#define GVIF3RX_ERROR7_STEP2                    (2U)

#define GVIF3RX_ERROR8_STEP1                    (1U)
#define GVIF3RX_ERROR8_STEP2                    (2U)

#define GVIF3RX_ERROR9_STEP1                    (1U)
#define GVIF3RX_ERROR9_STEP2                    (2U)

#define GVIF3RX_ERROR10_STEP1                   (1U)
#define GVIF3RX_ERROR10_STEP2                   (2U)

#define GVIF3RX_ERRCLR_STEP1                    (1U)
#define GVIF3RX_ERRCLR_STEP2                    (2U)

#define GVIF3RX_ERRCLRRLS_STEP1                 (1U)
#define GVIF3RX_ERRCLRRLS_STEP2                 (2U)

#define GVIF3RX_CAMKIND_STEP1                   (1U)
#define GVIF3RX_CAMKIND_STEP2                   (2U)
#define GVIF3RX_CAMKIND_STEP3                   (3U)
#define GVIF3RX_CAMKIND_STEP4                   (4U)
#define GVIF3RX_CAMKIND_STEP5                   (5U)
#define GVIF3RX_CAMKIND_STEP6                   (6U)
#define GVIF3RX_CAMKIND_STEP7                   (7U)
#define GVIF3RX_CAMKIND_STEP8                   (8U)
#define GVIF3RX_CAMKIND_STEP9                   (9U)
#define GVIF3RX_CAMKIND_STEP10                  (10U)

#define GVIF3RX_MIPIRESET_STEP1                 (1U)
#define GVIF3RX_MIPIRESET_STEP2                 (2U)

#define GVIF3RX_UNL0SET2_STEP1                  (1U)
#define GVIF3RX_UNL0SET2_STEP2                  (2U)

#define GVIF3RX_UNL1SET2_STEP1                  (1U)
#define GVIF3RX_UNL1SET2_STEP2                  (2U)

#define GVIF3RX_UNL2SET2_STEP1                  (1U)
#define GVIF3RX_UNL2SET2_STEP2                  (2U)

#define GVIF3RX_UNL3SET2_STEP1                  (1U)
#define GVIF3RX_UNL3SET2_STEP2                  (2U)

#define GVIF3RX_UNL4SET2_STEP1                  (1U)
#define GVIF3RX_UNL4SET2_STEP2                  (2U)

#define GVIF3RX_UNL5SET2_STEP1                  (1U)
#define GVIF3RX_UNL5SET2_STEP2                  (2U)

#define GVIF3RX_GPIOSET_STEP1                   (1U)
#define GVIF3RX_GPIOSET_STEP2                   (2U)

/* キャプチャ準備状態検知処理レジスタ設定値 */
#define GVIF3RX_VIDEO_OUTPUT_NON                (0x00U)
#define GVIF3RX_VIDEO_OUTPUT_ENABLE_0           (0x01U)
#define GVIF3RX_VIDEO_OUTPUT_ENABLE_1           (0x02U)

/* デバイス異常検知 */
#define GVIF3RX_GETREG_DEV_NORMAL               (0x20U)
#define GVIF3RX_DEVERR_FLGON                    (1U)
#define GVIF3RX_DEVERR_FLGOFF                   (0U)
#define GVIF3RX_DEVERR_CHK                      (0U)
#define GVIF3RX_DEVERR_NON                      (1U)
#define GVIF3RX_DEVERR_RST                      (2U)

/* 再起動フラグ */
#define GVIF3RX_RESTART_FLGON                   (1U)
#define GVIF3RX_RESTART_FLGOFF                  (0U)
#define GVIF3RX_RESTART_WAIT                    (5U)

/* カメラシステム種別(カメラ有/カメラ無) */
#define GVIF3RX_CAMKIND_NUM                     (2U)
#define GVIF3RX_KIND_CAM_NONE                   (0U)
#define GVIF3RX_KIND_DOMECON_EXIST              (1U)

/* 未接続検知 */
#define GVIF3RX_UNCON_CNT_CNF                   (24U)
#define GVIF3RX_UNCON_IDLE                      (0x00U)
#define GVIF3RX_RX0_UNCON_MASK                  (0x10U)
#define GVIF3RX_RX1_UNCON_MASK                  (0x80U)
#define GVIF3RX_UNCON_FLGON                     (1U)
#define GVIF3RX_UNCON_FLGOFF                    (0U)

/* ダイレコ記憶回数 */
#define GVIF3RX_ERROR_MAXLOGCNT                 (3U)
#define GVIF3RX_ERRORCHK_NON                    (0x00U)
#define GVIF3RX_ERRORCHK_MASK                   (0x80U)

#define GVIF3RX_RDTBL_NUM                       (2U)
#define GVIF3RX_WRTBL_NUM                       (1U)
#define GVIF3RX_MIPIWRTBL_NUM                   (4U)
#define GVIF3RX_CAMKINDWRTBL_NUM                (2U)
#define GVIF3RX_REG_RWC_BYTE2                   (2U)
#define GVIF3RX_REG_RWC_BYTE3                   (3U)
#define GVIF3RX_SLAVEADR_WR                     (0x46U)
#define GVIF3RX_SLAVEADR_RD                     (0x47U)
#define GVIF3RX_OUTSET_WRINUM                   (1U)
#define GVIF3RX_CANKINDSET_WRINUM               (9U)

#define GVIF3RX_PROC_REQNUM                     (10U)

#define GVIF3RX_PROC_NON                        (0x00000000U)
#define GVIF3RX_PROC_BANK0                      (0x00000001U)
#define GVIF3RX_PROC_BANK2                      (0x00000002U)
#define GVIF3RX_PROC_BANK3                      (0x00000004U)
#define GVIF3RX_PROC_MIPITX                     (0x00000008U)
#define GVIF3RX_PROC_DEVERRCHK                  (0x00000010U)
#define GVIF3RX_PROC_LINKCHK                    (0x00000020U)
#define GVIF3RX_PROC_ERROR1CHK                  (0x00000040U)
#define GVIF3RX_PROC_ERROR2CHK                  (0x00000080U)
#define GVIF3RX_PROC_ERROR3CHK                  (0x00000100U)
#define GVIF3RX_PROC_ERROR4CHK                  (0x00000200U)
#define GVIF3RX_PROC_ERROR5CHK                  (0x00000400U)
#define GVIF3RX_PROC_ERROR6CHK                  (0x00000800U)
#define GVIF3RX_PROC_ERROR7CHK                  (0x00001000U)
#define GVIF3RX_PROC_ERROR8CHK                  (0x00002000U)
#define GVIF3RX_PROC_ERROR9CHK                  (0x00004000U)
#define GVIF3RX_PROC_ERROR10CHK                 (0x00008000U)
#define GVIF3RX_PROC_ERRCLRSET                  (0x00010000U)
#define GVIF3RX_PROC_ERRCLRRLS                  (0x00020000U)
#define GVIF3RX_PROC_SIPERRORMIPISET            (0x00040000U)
#define GVIF3RX_PROC_UNL0SET2_SET               (0x00080000U)
#define GVIF3RX_PROC_UNL1SET2_SET               (0x00100000U)
#define GVIF3RX_PROC_UNL2SET2_SET               (0x00200000U)
#define GVIF3RX_PROC_UNL3SET2_SET               (0x00400000U)
#define GVIF3RX_PROC_UNL4SET2_SET               (0x00800000U)
#define GVIF3RX_PROC_UNL5SET2_SET               (0x01000000U)
#define GVIF3RX_PROC_GPIOSET_SET                (0x02000000U)
#define GVIF3RX_PROC_RESERVE                    (0xFC000000U)

#define GVIF3RX_BANK0                           (0U)
#define GVIF3RX_BANK1                           (1U)
#define GVIF3RX_BANK2                           (2U)
#define GVIF3RX_BANK3                           (3U)
#define GVIF3RX_BANK_UNKNOWN                    (0xFFU)

#define GVIF3RX_SIPERR_NON                      (0U)
#define GVIF3RX_SIPERR_REQ                      (1U)
#define GVIF3RX_SIPERR_COMP                     (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GVIF3RX_PORT_CAM_RST                    (DIO_ID_PORT10_CH6)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1    u1_s_gvif3rxstby3sts;
static U1    u1_s_gvif3rxcamkind_now;
static U1    u1_s_gvifcamKind_last;
static U1    u1_s_gvif3rxstartflg;
static U1    u1_s_gvif3rxsipfailflg;
static U1    u1_s_gvif3rxchkflg;
static U1    u1_s_gvif3rxchk_cnt;
static U1    u1_s_gvif3rxrestartcnt;
static U1    u1_s_gvif3rxdeverrflg;
static U1    u1_s_gvif3rx0unconflg;
static U1    u1_s_gvif3rx1unconflg;
static U1    u1_s_gvif3rxrestartflg;
static U1    u1_s_gvif3rx0unconcnt;
static U1    u1_s_gvif3rx1unconcnt;
static U1    u1_s_gvif3rxerror1chkcnt;
static U1    u1_s_gvif3rxerror2chkcnt;
static U1    u1_s_gvif3rxerror3chkcnt;
static U1    u1_s_gvif3rxerror4chkcnt;
static U4    u4_s_gcif3acktime;
static U1    u1_s_gvif3maintask_step;
static U1    u1_s_gvif3perimoni_step;
static U1    u1_s_gvif3mipi_step;
static U1    u1_s_gvif3rxdeverr_step;
static U1    u1_s_gvif3siperr_step;
static U1    u1_s_gvif3link_step;
static U1    u1_s_gvif3error1_step;
static U1    u1_s_gvif3error2_step;
static U1    u1_s_gvif3error3_step;
static U1    u1_s_gvif3error4_step;
static U1    u1_s_gvif3rxerror5_step;
static U1    u1_s_gvif3rxerror6_step;
static U1    u1_s_gvif3rxerror7_step;
static U1    u1_s_gvif3rxerror8_step;
static U1    u1_s_gvif3rxerror9_step;
static U1    u1_s_gvif3rxerror10_step;
static U1    u1_s_gvif3rxerrclr_step;
static U1    u1_s_gvif3rxerrclrrls_step;
static U1    u1_s_gvif3rxcamkind_step;
static U1    u1_s_gvif3mipireset_step;
static U1    u1_s_gvif3rxunl0set2_step;
static U1    u1_s_gvif3rxunl1set2_step;
static U1    u1_s_gvif3rxunl2set2_step;
static U1    u1_s_gvif3rxunl3set2_step;
static U1    u1_s_gvif3rxunl4set2_step;
static U1    u1_s_gvif3rxunl5set2_step;
static U1    u1_s_gvif3rxgpioset_step;
static U2    u2_s_gvif3rx_regstep;
static U2    u2_s_gvif3rxregset_betwaittime_stub;
static U1    u1_s_gvif3rxmipitx_date;
static U1    u1_s_gvif3rxmipitx_send;
static U1    u1_s_gvif3rxsiperr_date;
static U4    u4_sp_gvif3rxprocque[GVIF3RX_PROC_REQNUM];
static U4    u4_s_gvif3rxproccond_met_flg;
static U1    u1_s_gvif3rxprocque_cnt;
static U1    u1_s_gvif3rxprocexe_cnt;
static U1    u1_s_gvif3rxmipitxset_flg;
static U1    u1_s_gvif3rxdeverrchk_flg;
static U1    u1_s_gvif3rxlinkchk_flg;
static U1    u1_s_gvif3rxerr1chk_flg;
static U1    u1_s_gvif3rxerr2chk_flg;
static U1    u1_s_gvif3rxerr3chk_flg;
static U1    u1_s_gvif3rxerr4chk_flg;
static U1    u1_s_gvif3rxerr5chk_flg;
static U1    u1_s_gvif3rxerr6chk_flg;
static U1    u1_s_gvif3rxerr7chk_flg;
static U1    u1_s_gvif3rxerr8chk_flg;
static U1    u1_s_gvif3rxerr9chk_flg;
static U1    u1_s_gvif3rxerr10chk_flg;
static U1    u1_s_gvif3rxerrclr_flg;
static U1    u1_s_gvif3rxerrclrrls_flg;
static U1    u1_s_gvif3rxsiperrmipiset_flg;
static U1    u1_s_gvif3rxunl0set2_flg;
static U1    u1_s_gvif3rxunl1set2_flg;
static U1    u1_s_gvif3rxunl2set2_flg;
static U1    u1_s_gvif3rxunl3set2_flg;
static U1    u1_s_gvif3rxunl4set2_flg;
static U1    u1_s_gvif3rxunl5set2_flg;
static U1    u1_s_gvif3rxgpioset_flg;
static U1    u1_s_gvif3rxregacc_flg;
static U1    u1_s_gvif3rxbank_last;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void   vd_s_Gvif3RxReset(void);
static void   vd_s_Gvif3RxReadDateInit(void);
static void   vd_s_Gvif3RxProcessMng(const U4 u4_a_proc_que);
static void   vd_s_Gvif3RxProcessInit(void);
static void   vd_s_Gvif3RxProcessChk(void);
static void   vd_s_Gvif3RxCycChk(void);
static void   vd_s_Gvif3RxCamKindGet(void);
static U1     u1_s_Gvif3RxCamKindDat(void);
static U1     u1_s_Gvif3MipiReset(void);
static U1     u1_s_Gvif3RxUnl0Set2(void);
static U1     u1_s_Gvif3RxUnl0Set2SetReq(void);
static U1     u1_s_Gvif3RxUnl0Set2RegSet(void);
static U1     u1_s_Gvif3RxUnl1Set2(void);
static U1     u1_s_Gvif3RxUnl1Set2SetReq(void);
static U1     u1_s_Gvif3RxUnl1Set2RegSet(void);
static U1     u1_s_Gvif3RxUnl2Set2(void);
static U1     u1_s_Gvif3RxUnl2Set2SetReq(void);
static U1     u1_s_Gvif3RxUnl2Set2RegSet(void);
static U1     u1_s_Gvif3RxUnl3Set2(void);
static U1     u1_s_Gvif3RxUnl3Set2SetReq(void);
static U1     u1_s_Gvif3RxUnl3Set2RegSet(void);
static U1     u1_s_Gvif3RxUnl4Set2(void);
static U1     u1_s_Gvif3RxUnl4Set2SetReq(void);
static U1     u1_s_Gvif3RxUnl4Set2RegSet(void);
static U1     u1_s_Gvif3RxUnl5Set2(void);
static U1     u1_s_Gvif3RxUnl5Set2SetReq(void);
static U1     u1_s_Gvif3RxUnl5Set2RegSet(void);
static U1     u1_s_Gvif3RxGpioSet(void);
static U1     u1_s_Gvif3RxGpioSetReq(void);
static U1     u1_s_Gvif3RxGpioSetRegSet(void);
static U1     u1_s_Gvif3Mipijdg(void);
static void   vd_s_Gvif3RxMipiOutputJdg(void);
static U1     u1_s_Gvif3RxMipitxSetReq(void);
static U1     u1_s_Gvif3RxMipitxRegSet(void);
static U1     u1_s_Gvif3DevErrChk(void);
static U1     u1_s_Gvif3DevErrGetReq(void);
static U1     u1_s_Gvif3DevErrStsGet(void);
static U1     u1_s_Gvif3SipFailTask(void);
static U1     u1_s_Gvif3RxSiPErrMipiSetReq(void);
static U1     u1_s_Gvif3SipErrMipiRegSet(void);
static void   vd_s_Gvif3Restart(void);
static U1     u1_s_Gvif3LinkChk(void);
static void   vd_s_Gvif3RxLinkRx0Log(void);
static void   vd_s_Gvif3RxLinkRx1Log(void);
static U1     u1_s_Gvif3LinkStsGetReq(void);
static U1     u1_s_Gvif3LinkStsGet(void);
static U1     u1_s_Gvif3Error1Chk(void);
static U1     u1_s_Gvif3RxErr1StsGetReq(void);
static U1     u1_s_Gvif3Error1StsGet(void);
static U1     u1_s_Gvif3Error2Chk(void);
static U1     u1_s_Gvif3RxErr2StsGetReq(void);
static U1     u1_s_Gvif3Error2StsGet(void);
static U1     u1_s_Gvif3Error3Chk(void);
static U1     u1_s_Gvif3RxErr3StsGetReq(void);
static U1     u1_s_Gvif3Error3StsGet(void);
static U1     u1_s_Gvif3Error4Chk(void);
static U1     u1_s_Gvif3RxErr4StsGetReq(void);
static U1     u1_s_Gvif3Error4StsGet(void);
static U1     u1_s_Gvif3Error5Chk(void);
static U1     u1_s_Gvif3RxErr5StsGetReq(void);
static U1     u1_s_Gvif3Error5StsGet(void);
static U1     u1_s_Gvif3Error6Chk(void);
static U1     u1_s_Gvif3RxErr6StsGetReq(void);
static U1     u1_s_Gvif3Error6StsGet(void);
static U1     u1_s_Gvif3Error7Chk(void);
static U1     u1_s_Gvif3RxErr7StsGetReq(void);
static U1     u1_s_Gvif3Error7StsGet(void);
static U1     u1_s_Gvif3Error8Chk(void);
static U1     u1_s_Gvif3RxErr8StsGetReq(void);
static U1     u1_s_Gvif3Error8StsGet(void);
static U1     u1_s_Gvif3Error9Chk(void);
static U1     u1_s_Gvif3RxErr9StsGetReq(void);
static U1     u1_s_Gvif3Error9StsGet(void);
static U1     u1_s_Gvif3Error10Chk(void);
static U1     u1_s_Gvif3RxErr10StsGetReq(void);
static U1     u1_s_Gvif3Error10StsGet(void);
static U1     u1_s_Gvif3RxErrClr(void);
static U1     u1_s_Gvif3RxErrClrStsGetReq(void);
static U1     u1_s_Gvif3RxErrClrRegSet(void);
static U1     u1_s_Gvif3RxErrClrRls(void);
static U1     u1_s_Gvif3RxErrClrRlsStsGetReq(void);
static U1     u1_s_Gvif3RxErrClrRlsRegSet(void);
static void   vd_s_Gvif3RxBank0Chk(void);
static U1     u1_s_Gvif3Bank0Chg(void);
static void   vd_s_Gvif3RxBank2Chk(void);
static U1     u1_s_Gvif3Bank2Chg(void);
static void   vd_s_Gvif3RxBank3Chk(void);
static U1     u1_s_Gvif3Bank3Chg(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_REG_WRI_REQ st_sp_GVIFRX_OUTSET[GVIF3RX_OUTSET_WRINUM] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};

const U1 u1_sp_GVIF3RX_REG_DEVERROR_RD_PDU1[GVIF3RX_REG_RWC_BYTE2] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x97U     /* Write Address */
};

U1 u1_sp_GVIF3RX_REG_DEVERROR_RD_PDU2[GVIF3RX_REG_RWC_BYTE2];

const U1 u1_sp_GVIF3RX_REG_MIPITX_0OFF_1OFF[GVIF3RX_REG_RWC_BYTE3] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x9CU,    /* Write Address */
    (U1)0xCCU     /* Write Data */
};

const U1 u1_sp_GVIF3RX_REG_MIPITX_0ON_1OFF[GVIF3RX_REG_RWC_BYTE3] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x9CU,    /* Write Address */
    (U1)0xCDU     /* Write Data */
};

const U1 u1_sp_GVIF3RX_REG_MIPITX_0OFF_1ON[GVIF3RX_REG_RWC_BYTE3] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x9CU,    /* Write Address */
    (U1)0xCEU     /* Write Data */
};

const U1 u1_sp_GVIF3RX_REG_MIPITX_0ON_1ON[GVIF3RX_REG_RWC_BYTE3] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x9CU,    /* Write Address */
    (U1)0xCFU     /* Write Data */
};

const U1 u1_sp_GVIF3RX_REG_LINKCHK_RD_PDU1[GVIF3RX_REG_RWC_BYTE2] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x00U     /* Write Address */
};

U1 u1_sp_GVIF3RX_REG_LINKCHK_RD_PDU2[GVIF3RX_REG_RWC_BYTE2];

const U1 u1_sp_GVIF3RX_REG_EERROR1CHK_RD_PDU1[GVIF3RX_REG_RWC_BYTE2] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x12U     /* Write Address */
};

U1 u1_sp_GVIF3RX_REG_EERROR1CHK_RD_PDU2[GVIF3RX_REG_RWC_BYTE2];

const U1 u1_sp_GVIF3RX_REG_EERROR2CHK_RD_PDU1[GVIF3RX_REG_RWC_BYTE2] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x10U     /* Write Address */
};

U1 u1_sp_GVIF3RX_REG_EERROR2CHK_RD_PDU2[GVIF3RX_REG_RWC_BYTE2];

const U1 u1_sp_GVIF3RX_REG_EERROR3CHK_RD_PDU1[GVIF3RX_REG_RWC_BYTE2] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x13U     /* Write Address */
};

U1 u1_sp_GVIF3RX_REG_EERROR3CHK_RD_PDU2[GVIF3RX_REG_RWC_BYTE2];

const U1 u1_sp_GVIF3RX_REG_EERROR4CHK_RD_PDU1[GVIF3RX_REG_RWC_BYTE2] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1CU     /* Write Address */
};

U1 u1_sp_GVIF3RX_REG_EERROR4CHK_RD_PDU2[GVIF3RX_REG_RWC_BYTE2];

const U1 u1_sp_GVIF3RX_REG_EERROR5CHK_RD_PDU1[GVIF3RX_REG_RWC_BYTE2] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA0U     /* Write Address */
};

U1 u1_sp_GVIF3RX_REG_EERROR5CHK_RD_PDU2[GVIF3RX_REG_RWC_BYTE2];

const U1 u1_sp_GVIF3RX_REG_EERROR6CHK_RD_PDU1[GVIF3RX_REG_RWC_BYTE2] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA9U     /* Write Address */
};

U1 u1_sp_GVIF3RX_REG_EERROR6CHK_RD_PDU2[GVIF3RX_REG_RWC_BYTE2];

const U1 u1_sp_GVIF3RX_REG_EERROR7CHK_RD_PDU1[GVIF3RX_REG_RWC_BYTE2] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA0U     /* Write Address */
};

U1 u1_sp_GVIF3RX_REG_EERROR7CHK_RD_PDU2[GVIF3RX_REG_RWC_BYTE2];

const U1 u1_sp_GVIF3RX_REG_EERROR8CHK_RD_PDU1[GVIF3RX_REG_RWC_BYTE2] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA9U     /* Write Address */
};

U1 u1_sp_GVIF3RX_REG_EERROR8CHK_RD_PDU2[GVIF3RX_REG_RWC_BYTE2];

const U1 u1_sp_GVIF3RX_REG_EERROR9CHK_RD_PDU1[GVIF3RX_REG_RWC_BYTE2] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA9U     /* Write Address */
};

U1 u1_sp_GVIF3RX_REG_EERROR9CHK_RD_PDU2[GVIF3RX_REG_RWC_BYTE2];

const U1 u1_sp_GVIF3RX_REG_EERROR10CHK_RD_PDU1[GVIF3RX_REG_RWC_BYTE2] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xB2U     /* Write Address */
};

U1 u1_sp_GVIF3RX_REG_EERROR10CHK_RD_PDU2[GVIF3RX_REG_RWC_BYTE2];

const U1 u1_sp_GVIF3RX_REG_ERRCLRSET[GVIF3RX_REG_RWC_BYTE3] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x2EU,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_GVIF3RX_REG_ERRCLRRLS[GVIF3RX_REG_RWC_BYTE3] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x2EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_GVIF3RX_REG_BANK0[GVIF3RX_REG_RWC_BYTE3] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_GVIF3RX_REG_BANK1[GVIF3RX_REG_RWC_BYTE3] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_GVIF3RX_REG_BANK2[GVIF3RX_REG_RWC_BYTE3] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_GVIF3RX_REG_BANK3[GVIF3RX_REG_RWC_BYTE3] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x03U     /* Write Data */
};

const U1 u1_sp_GVIF3RX_REG_UNLD0_2_CAMNON[GVIF3RX_REG_RWC_BYTE3] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x9FU,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_GVIF3RX_REG_UNLD0_2_DOMCON[GVIF3RX_REG_RWC_BYTE3] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x9FU,    /* Write Address */
    (U1)0x03U     /* Write Data */
};

const U1 u1_sp_GVIF3RX_REG_UNLD1_2_CAMNON[GVIF3RX_REG_RWC_BYTE3] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA8U,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_GVIF3RX_REG_UNLD1_2_DOMCON[GVIF3RX_REG_RWC_BYTE3] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA8U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_GVIF3RX_REG_UNLD2_2_CAMNON[GVIF3RX_REG_RWC_BYTE3] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x9FU,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_GVIF3RX_REG_UNLD2_2_DOMCON[GVIF3RX_REG_RWC_BYTE3] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x9FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_GVIF3RX_REG_UNLD3_2_CAMNON[GVIF3RX_REG_RWC_BYTE3] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA8U,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_GVIF3RX_REG_UNLD3_2_DOMCON[GVIF3RX_REG_RWC_BYTE3] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA8U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_GVIF3RX_REG_UNLD4_2_CAMNON[GVIF3RX_REG_RWC_BYTE3] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA8U,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_GVIF3RX_REG_UNLD4_2_DOMCON[GVIF3RX_REG_RWC_BYTE3] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA8U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_GVIF3RX_REG_UNLD5_2_CAMNON[GVIF3RX_REG_RWC_BYTE3] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xB1U,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_GVIF3RX_REG_UNLD5_2_DOMCON[GVIF3RX_REG_RWC_BYTE3] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xB1U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_GVIF3RX_REG_GPIO3_CAMNON[GVIF3RX_REG_RWC_BYTE3] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF0U,    /* Write Address */
    (U1)0x30U     /* Write Data */
};

const U1 u1_sp_GVIF3RX_REG_GPIO3_DOMCON[GVIF3RX_REG_RWC_BYTE3] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF0U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const ST_GP_I2C_MA_REQ st_sp_GVIF3RX_REG_DEVERROR[GVIF3RX_RDTBL_NUM] = {
    {
        (U1 *)&u1_sp_GVIF3RX_REG_DEVERROR_RD_PDU1[0],
        (U4)0x20000002U
    },
    {
        (U1 *)&u1_sp_GVIF3RX_REG_DEVERROR_RD_PDU2[0],
        (U4)0x20000002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GVIF3RX_REG_MIPI_WR[GVIF3RX_MIPIWRTBL_NUM] = {
    {
        (U1 *)&u1_sp_GVIF3RX_REG_MIPITX_0OFF_1OFF[0],
        (U4)0x20000003U
    },
    {
        (U1 *)&u1_sp_GVIF3RX_REG_MIPITX_0ON_1OFF[0],
        (U4)0x20000003U
    },
    {
        (U1 *)&u1_sp_GVIF3RX_REG_MIPITX_0OFF_1ON[0],
        (U4)0x20000003U
    },
    {
        (U1 *)&u1_sp_GVIF3RX_REG_MIPITX_0ON_1ON[0],
        (U4)0x20000003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GVIF3RX_REG_LINKCHK[GVIF3RX_RDTBL_NUM] = {
    {
        (U1 *)&u1_sp_GVIF3RX_REG_LINKCHK_RD_PDU1[0],
        (U4)0x20000002U
    },
    {
        (U1 *)&u1_sp_GVIF3RX_REG_LINKCHK_RD_PDU2[0],
        (U4)0x20000002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GVIF3RX_REG_EERROR1CHK[GVIF3RX_RDTBL_NUM] = {
    {
        (U1 *)&u1_sp_GVIF3RX_REG_EERROR1CHK_RD_PDU1[0],
        (U4)0x20000002U
    },
    {
        (U1 *)&u1_sp_GVIF3RX_REG_EERROR1CHK_RD_PDU2[0],
        (U4)0x20000002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GVIF3RX_REG_EERROR2CHK[GVIF3RX_RDTBL_NUM] = {
    {
        (U1 *)&u1_sp_GVIF3RX_REG_EERROR2CHK_RD_PDU1[0],
        (U4)0x20000002U
    },
    {
        (U1 *)&u1_sp_GVIF3RX_REG_EERROR2CHK_RD_PDU2[0],
        (U4)0x20000002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GVIF3RX_REG_EERROR3CHK[GVIF3RX_RDTBL_NUM] = {
    {
        (U1 *)&u1_sp_GVIF3RX_REG_EERROR3CHK_RD_PDU1[0],
        (U4)0x20000002U
    },
    {
        (U1 *)&u1_sp_GVIF3RX_REG_EERROR3CHK_RD_PDU2[0],
        (U4)0x20000002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GVIF3RX_REG_EERROR4CHK[GVIF3RX_RDTBL_NUM] = {
    {
        (U1 *)&u1_sp_GVIF3RX_REG_EERROR4CHK_RD_PDU1[0],
        (U4)0x20000002U
    },
    {
        (U1 *)&u1_sp_GVIF3RX_REG_EERROR4CHK_RD_PDU2[0],
        (U4)0x20000002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GVIF3RX_REG_EERROR5CHK[GVIF3RX_RDTBL_NUM] = {
    {
        (U1 *)&u1_sp_GVIF3RX_REG_EERROR5CHK_RD_PDU1[0],
        (U4)0x20000002U
    },
    {
        (U1 *)&u1_sp_GVIF3RX_REG_EERROR5CHK_RD_PDU2[0],
        (U4)0x20000002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GVIF3RX_REG_EERROR6CHK[GVIF3RX_RDTBL_NUM] = {
    {
        (U1 *)&u1_sp_GVIF3RX_REG_EERROR6CHK_RD_PDU1[0],
        (U4)0x20000002U
    },
    {
        (U1 *)&u1_sp_GVIF3RX_REG_EERROR6CHK_RD_PDU2[0],
        (U4)0x20000002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GVIF3RX_REG_EERROR7CHK[GVIF3RX_RDTBL_NUM] = {
    {
        (U1 *)&u1_sp_GVIF3RX_REG_EERROR7CHK_RD_PDU1[0],
        (U4)0x20000002U
    },
    {
        (U1 *)&u1_sp_GVIF3RX_REG_EERROR7CHK_RD_PDU2[0],
        (U4)0x20000002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GVIF3RX_REG_EERROR8CHK[GVIF3RX_RDTBL_NUM] = {
    {
        (U1 *)&u1_sp_GVIF3RX_REG_EERROR8CHK_RD_PDU1[0],
        (U4)0x20000002U
    },
    {
        (U1 *)&u1_sp_GVIF3RX_REG_EERROR8CHK_RD_PDU2[0],
        (U4)0x20000002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GVIF3RX_REG_EERROR9CHK[GVIF3RX_RDTBL_NUM] = {
    {
        (U1 *)&u1_sp_GVIF3RX_REG_EERROR9CHK_RD_PDU1[0],
        (U4)0x20000002U
    },
    {
        (U1 *)&u1_sp_GVIF3RX_REG_EERROR9CHK_RD_PDU2[0],
        (U4)0x20000002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GVIF3RX_REG_EERROR10CHK[GVIF3RX_RDTBL_NUM] = {
    {
        (U1 *)&u1_sp_GVIF3RX_REG_EERROR10CHK_RD_PDU1[0],
        (U4)0x20000002U
    },
    {
        (U1 *)&u1_sp_GVIF3RX_REG_EERROR10CHK_RD_PDU2[0],
        (U4)0x20000002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GVIF3RX_REG_ERRCLRSET[GVIF3RX_WRTBL_NUM] = {
    {
        (U1 *)&u1_sp_GVIF3RX_REG_ERRCLRSET[0],
        (U4)0x20000003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GVIF3RX_REG_ERRCLRRLS[GVIF3RX_WRTBL_NUM] = {
    {
        (U1 *)&u1_sp_GVIF3RX_REG_ERRCLRRLS[0],
        (U4)0x20000003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GVIF3RX_REG_BANK0[GVIF3RX_WRTBL_NUM] = {
    {
        (U1 *)&u1_sp_GVIF3RX_REG_BANK0[0],
        (U4)0x20000003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GVIF3RX_REG_BANK1[GVIF3RX_WRTBL_NUM] = {
    {
        (U1 *)&u1_sp_GVIF3RX_REG_BANK1[0],
        (U4)0x20000003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GVIF3RX_REG_BANK2[GVIF3RX_WRTBL_NUM] = {
    {
        (U1 *)&u1_sp_GVIF3RX_REG_BANK2[0],
        (U4)0x20000003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GVIF3RX_REG_BANK3[GVIF3RX_WRTBL_NUM] = {
    {
        (U1 *)&u1_sp_GVIF3RX_REG_BANK3[0],
        (U4)0x20000003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GVIF3RX_REG_UNLD0_2_WR[GVIF3RX_CAMKINDWRTBL_NUM] = {
    {
        (U1 *)&u1_sp_GVIF3RX_REG_UNLD0_2_CAMNON[0],
        (U4)0x20000003U
    },
    {
        (U1 *)&u1_sp_GVIF3RX_REG_UNLD0_2_DOMCON[0],
        (U4)0x20000003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GVIF3RX_REG_UNLD1_2_WR[GVIF3RX_CAMKINDWRTBL_NUM] = {
    {
        (U1 *)&u1_sp_GVIF3RX_REG_UNLD1_2_CAMNON[0],
        (U4)0x20000003U
    },
    {
        (U1 *)&u1_sp_GVIF3RX_REG_UNLD1_2_DOMCON[0],
        (U4)0x20000003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GVIF3RX_REG_UNLD2_2_WR[GVIF3RX_CAMKINDWRTBL_NUM] = {
    {
        (U1 *)&u1_sp_GVIF3RX_REG_UNLD2_2_CAMNON[0],
        (U4)0x20000003U
    },
    {
        (U1 *)&u1_sp_GVIF3RX_REG_UNLD2_2_DOMCON[0],
        (U4)0x20000003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GVIF3RX_REG_UNLD3_2_WR[GVIF3RX_CAMKINDWRTBL_NUM] = {
    {
        (U1 *)&u1_sp_GVIF3RX_REG_UNLD3_2_CAMNON[0],
        (U4)0x20000003U
    },
    {
        (U1 *)&u1_sp_GVIF3RX_REG_UNLD3_2_DOMCON[0],
        (U4)0x20000003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GVIF3RX_REG_UNLD4_2_WR[GVIF3RX_CAMKINDWRTBL_NUM] = {
    {
        (U1 *)&u1_sp_GVIF3RX_REG_UNLD4_2_CAMNON[0],
        (U4)0x20000003U
    },
    {
        (U1 *)&u1_sp_GVIF3RX_REG_UNLD4_2_DOMCON[0],
        (U4)0x20000003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GVIF3RX_REG_UNLD5_2_WR[GVIF3RX_CAMKINDWRTBL_NUM] = {
    {
        (U1 *)&u1_sp_GVIF3RX_REG_UNLD5_2_CAMNON[0],
        (U4)0x20000003U
    },
    {
        (U1 *)&u1_sp_GVIF3RX_REG_UNLD5_2_DOMCON[0],
        (U4)0x20000003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GVIF3RX_REG_GPIO3_WR[GVIF3RX_CAMKINDWRTBL_NUM] = {
    {
        (U1 *)&u1_sp_GVIF3RX_REG_GPIO3_CAMNON[0],
        (U4)0x20000003U
    },
    {
        (U1 *)&u1_sp_GVIF3RX_REG_GPIO3_DOMCON[0],
        (U4)0x20000003U
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_Gvif3RxInit(void)                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Gvif3RxInit(void)
{
    u1_s_gvif3rxstby3sts = (U1)FALSE;
    u1_s_gvif3rxcamkind_now = (U1)GVIF3RX_KIND_CAM_NONE; /* DTF読み出し値(暫定) */
    u1_s_gvifcamKind_last = (U1)GVIF3RX_KIND_CAM_NONE;   /* DTF読み出し値(暫定) */
    u1_s_gvif3rxchk_cnt = (U1)GVIF3RX_CNT_CLR;
    u1_s_gvif3rxdeverrflg = (U1)GVIF3RX_DEVERR_FLGOFF;
    u1_s_gvif3rx0unconflg = (U1)GVIF3RX_UNCON_FLGOFF;
    u1_s_gvif3rx1unconflg = (U1)GVIF3RX_UNCON_FLGOFF;
    u1_s_gvif3rxerror1chkcnt = (U1)GVIF3RX_CNT_CLR;
    u1_s_gvif3rxerror2chkcnt = (U1)GVIF3RX_CNT_CLR;
    u1_s_gvif3rxerror3chkcnt = (U1)GVIF3RX_CNT_CLR;
    u1_s_gvif3rxerror4chkcnt = (U1)GVIF3RX_CNT_CLR;
    vd_s_Gvif3RxReset();
}

/*===================================================================================================================================*/
/*  static void    vd_s_Gvif3RxReset(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_Gvif3RxReset(void)
{
    u1_s_gvif3rxstartflg = (U1)FALSE;
    u1_s_gvif3rxsipfailflg = (U1)GVIF3RX_SIPERR_NON;
    u1_s_gvif3rxchkflg = (U1)FALSE;
    u1_s_gvif3rxrestartcnt = (U1)GVIF3RX_CNT_CLR;
    u1_s_gvif3rx0unconcnt = (U1)GVIF3RX_CNT_CLR;
    u1_s_gvif3rx1unconcnt = (U1)GVIF3RX_CNT_CLR;
    u1_s_gvif3rxrestartflg = (U1)GVIF3RX_RESTART_FLGOFF;
    u4_s_gcif3acktime = (U1)GVIF3RX_CNT_CLR;
    u1_s_gvif3maintask_step = (U1)GVIF3RX_MAINTASK_STEP1;
    u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP1;
    u1_s_gvif3mipi_step = (U1)GVIF3RX_MIPI_STEP1;
    u1_s_gvif3rxdeverr_step = (U1)GVIF3RX_DEVERR_STEP1;
    u1_s_gvif3siperr_step = (U1)GVIF3RX_SIPERR_STEP1;
    u1_s_gvif3link_step = (U1)GVIF3RX_LINK_STEP1;
    u1_s_gvif3error1_step = (U1)GVIF3RX_ERROR1_STEP1;
    u1_s_gvif3error2_step = (U1)GVIF3RX_ERROR2_STEP1;
    u1_s_gvif3error3_step = (U1)GVIF3RX_ERROR3_STEP1;
    u1_s_gvif3error4_step = (U1)GVIF3RX_ERROR4_STEP1;
    u1_s_gvif3rxerror5_step = (U1)GVIF3RX_ERROR5_STEP1;
    u1_s_gvif3rxerror6_step = (U1)GVIF3RX_ERROR6_STEP1;
    u1_s_gvif3rxerror7_step = (U1)GVIF3RX_ERROR7_STEP1;
    u1_s_gvif3rxerror8_step = (U1)GVIF3RX_ERROR8_STEP1;
    u1_s_gvif3rxerror9_step = (U1)GVIF3RX_ERROR9_STEP1;
    u1_s_gvif3rxerror10_step = (U1)GVIF3RX_ERROR10_STEP1;
    u1_s_gvif3rxerrclr_step = (U1)GVIF3RX_ERRCLR_STEP1;
    u1_s_gvif3rxerrclrrls_step = (U1)GVIF3RX_ERRCLRRLS_STEP1;
    u1_s_gvif3rxcamkind_step = (U1)GVIF3RX_CAMKIND_STEP1;
    u1_s_gvif3mipireset_step = (U1)GVIF3RX_MIPIRESET_STEP1;
    u1_s_gvif3rxunl0set2_step = (U1)GVIF3RX_UNL0SET2_STEP1;
    u1_s_gvif3rxunl1set2_step = (U1)GVIF3RX_UNL1SET2_STEP1;
    u1_s_gvif3rxunl2set2_step = (U1)GVIF3RX_UNL2SET2_STEP1;
    u1_s_gvif3rxunl3set2_step = (U1)GVIF3RX_UNL3SET2_STEP1;
    u1_s_gvif3rxunl4set2_step = (U1)GVIF3RX_UNL4SET2_STEP1;
    u1_s_gvif3rxunl5set2_step = (U1)GVIF3RX_UNL5SET2_STEP1;
    u1_s_gvif3rxgpioset_step = (U1)GVIF3RX_GPIOSET_STEP1;
    u2_s_gvif3rx_regstep = (U2)0U;
    u2_s_gvif3rxregset_betwaittime_stub = (U2)0xFFFFU;
    u1_s_gvif3rxmipitx_date = (U1)GVIF3RX_VIDEO_OUTPUT_NON;
    u1_s_gvif3rxmipitx_send = (U1)GVIF3RX_MIPIOUTPUT_OFF;
    vd_s_Gvif3RxReadDateInit();
    vd_s_Gvif3RxProcessInit();
    u1_s_gvif3rxmipitxset_flg = (U1)FALSE;
    u1_s_gvif3rxdeverrchk_flg = (U1)FALSE;
    u1_s_gvif3rxlinkchk_flg = (U1)FALSE;
    u1_s_gvif3rxerr1chk_flg = (U1)FALSE;
    u1_s_gvif3rxerr2chk_flg = (U1)FALSE;
    u1_s_gvif3rxerr3chk_flg = (U1)FALSE;
    u1_s_gvif3rxerr4chk_flg = (U1)FALSE;
    u1_s_gvif3rxerr5chk_flg = (U1)FALSE;
    u1_s_gvif3rxerr6chk_flg = (U1)FALSE;
    u1_s_gvif3rxerr7chk_flg = (U1)FALSE;
    u1_s_gvif3rxerr8chk_flg = (U1)FALSE;
    u1_s_gvif3rxerr9chk_flg = (U1)FALSE;
    u1_s_gvif3rxerr10chk_flg = (U1)FALSE;
    u1_s_gvif3rxerrclr_flg = (U1)FALSE;
    u1_s_gvif3rxerrclrrls_flg = (U1)FALSE;
    u1_s_gvif3rxsiperrmipiset_flg = (U1)FALSE;
    u1_s_gvif3rxunl0set2_flg = (U1)FALSE;
    u1_s_gvif3rxunl1set2_flg = (U1)FALSE;
    u1_s_gvif3rxunl2set2_flg = (U1)FALSE;
    u1_s_gvif3rxunl3set2_flg = (U1)FALSE;
    u1_s_gvif3rxunl4set2_flg = (U1)FALSE;
    u1_s_gvif3rxunl5set2_flg = (U1)FALSE;
    u1_s_gvif3rxgpioset_flg = (U1)FALSE;
    u1_s_gvif3rxregacc_flg = (U1)FALSE;
    u1_s_gvif3rxbank_last = (U1)GVIF3RX_BANK_UNKNOWN;
}

/*===================================================================================================================================*/
/*  static void    vd_s_Gvif3RxReadDateInit(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_Gvif3RxReadDateInit(void)
{
    /*  データリード用テーブル初期化 */
    u1_sp_GVIF3RX_REG_DEVERROR_RD_PDU2[0] = (U1)GVIF3RX_SLAVEADR_RD;    /* Slave Address */
    u1_sp_GVIF3RX_REG_DEVERROR_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_GVIF3RX_REG_LINKCHK_RD_PDU2[0] = (U1)GVIF3RX_SLAVEADR_RD;    /* Slave Address */
    u1_sp_GVIF3RX_REG_LINKCHK_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_GVIF3RX_REG_EERROR1CHK_RD_PDU2[0] = (U1)GVIF3RX_SLAVEADR_RD;    /* Slave Address */
    u1_sp_GVIF3RX_REG_EERROR1CHK_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_GVIF3RX_REG_EERROR2CHK_RD_PDU2[0] = (U1)GVIF3RX_SLAVEADR_RD;    /* Slave Address */
    u1_sp_GVIF3RX_REG_EERROR2CHK_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_GVIF3RX_REG_EERROR3CHK_RD_PDU2[0] = (U1)GVIF3RX_SLAVEADR_RD;    /* Slave Address */
    u1_sp_GVIF3RX_REG_EERROR3CHK_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_GVIF3RX_REG_EERROR4CHK_RD_PDU2[0] = (U1)GVIF3RX_SLAVEADR_RD;    /* Slave Address */
    u1_sp_GVIF3RX_REG_EERROR4CHK_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_GVIF3RX_REG_EERROR5CHK_RD_PDU2[0] = (U1)GVIF3RX_SLAVEADR_RD;    /* Slave Address */
    u1_sp_GVIF3RX_REG_EERROR5CHK_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_GVIF3RX_REG_EERROR6CHK_RD_PDU2[0] = (U1)GVIF3RX_SLAVEADR_RD;    /* Slave Address */
    u1_sp_GVIF3RX_REG_EERROR6CHK_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_GVIF3RX_REG_EERROR7CHK_RD_PDU2[0] = (U1)GVIF3RX_SLAVEADR_RD;    /* Slave Address */
    u1_sp_GVIF3RX_REG_EERROR7CHK_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_GVIF3RX_REG_EERROR8CHK_RD_PDU2[0] = (U1)GVIF3RX_SLAVEADR_RD;    /* Slave Address */
    u1_sp_GVIF3RX_REG_EERROR8CHK_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_GVIF3RX_REG_EERROR9CHK_RD_PDU2[0] = (U1)GVIF3RX_SLAVEADR_RD;    /* Slave Address */
    u1_sp_GVIF3RX_REG_EERROR9CHK_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_GVIF3RX_REG_EERROR10CHK_RD_PDU2[0] = (U1)GVIF3RX_SLAVEADR_RD;    /* Slave Address */
    u1_sp_GVIF3RX_REG_EERROR10CHK_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

}

/*===================================================================================================================================*/
/*  void    vd_g_Gvif3RxMainTask(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Gvif3RxMainTask(void)
{
    /* Ackタイムアウト用カウンタインクリメント */
    if(u4_s_gcif3acktime < (U4)U4_MAX){
        u4_s_gcif3acktime++;
    }
    /* 定期監視ポーリング周期カウント(50ms) */
    if(u1_s_gvif3rxchk_cnt < (U1)U1_MAX){
        u1_s_gvif3rxchk_cnt++;
    }

    switch (u1_s_gvif3maintask_step)
    {
        case GVIF3RX_MAINTASK_STEP1:
            if(Mcu_OnStep_GVIF3RX_OVRALL == (uint8)MCU_STEP_GVIF3RX_OVERALL_FIN){ /* 初期化完了待ち */
                u1_s_gvif3maintask_step = (U1)GVIF3RX_MAINTASK_STEP2;
            }
        break;
    
        case GVIF3RX_MAINTASK_STEP2:
            u1_s_gvif3rxstartflg = (U1)TRUE;
            u1_s_gvif3rxchkflg = (U1)TRUE;
            u1_s_gvif3rxchk_cnt = (U1)GVIF3RX_CNT_CLR;
            u1_s_gvif3maintask_step = (U1)GVIF3RX_MAINTASK_STEP3;
            break;
    
        case GVIF3RX_MAINTASK_STEP3:
            if(u1_s_gvif3rxchk_cnt >= (U1)GVIF3RX_CHKTIME){
                u1_s_gvif3rxchkflg = (U1)TRUE;
                u1_s_gvif3rxchk_cnt = (U1)GVIF3RX_CNT_CLR;
            }
            break;
    
        default:
            u1_s_gvif3maintask_step = (U1)GVIF3RX_MAINTASK_STEP1;
            break;
    }

    
    vd_s_Gvif3RxProcessChk();

    if(u1_s_gvif3rxsipfailflg == (U1)GVIF3RX_SIPERR_REQ){
        u1_s_Gvif3SipFailTask();
    }

    if((u1_s_gvif3rxchkflg == (U1)TRUE) &&
      ((u1_s_gvif3rxsipfailflg != (U1)GVIF3RX_SIPERR_REQ) || (u1_s_gvif3rxregacc_flg == (U1)TRUE))){
        vd_s_Gvif3RxCycChk();
    }
    
    vd_s_Gvif3RxProcessChk();
    
    if(u1_s_gvif3rxstartflg == (U1)TRUE){
        vd_s_Gvif3Restart();
    }
}

/*===================================================================================================================================*/
/*  U1    vd_s_Gvif3RxProcessMng(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u4_a_proc_que                                                                                                    */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Gvif3RxProcessMng(const U4 u4_a_proc_que)
{
    U4  u4_t_que_chk;

    u4_t_que_chk = u4_s_gvif3rxproccond_met_flg & u4_a_proc_que;
    if(u4_t_que_chk == (U4)0){
        u4_s_gvif3rxproccond_met_flg |= u4_a_proc_que;
        if(u1_s_gvif3rxprocque_cnt < (U1)GVIF3RX_PROC_REQNUM){
            u4_sp_gvif3rxprocque[u1_s_gvif3rxprocque_cnt] = u4_a_proc_que;
            u1_s_gvif3rxprocque_cnt++;
            if(u1_s_gvif3rxprocque_cnt >= (U1)GVIF3RX_PROC_REQNUM){
                u1_s_gvif3rxprocque_cnt = (U1)0;
            }
        }
        else{
            vd_s_Gvif3RxProcessInit();
        }
        if(u4_a_proc_que == (U1)GVIF3RX_PROC_BANK0){
            u1_s_gvif3rxbank_last = (U1)GVIF3RX_BANK0;
        }
        else if(u4_a_proc_que == (U1)GVIF3RX_PROC_BANK2){
            u1_s_gvif3rxbank_last = (U1)GVIF3RX_BANK2;
        }
        else if(u4_a_proc_que == (U1)GVIF3RX_PROC_BANK3){
            u1_s_gvif3rxbank_last = (U1)GVIF3RX_BANK3;
        }
        else{
            /* do nothing */
        }
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_Gvif3RxProcessInit(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Gvif3RxProcessInit(void)
{
    U1 u1_t_cnt;

    u4_s_gvif3rxproccond_met_flg = (U4)GVIF3RX_PROC_NON;
    for(u1_t_cnt =0; u1_t_cnt < (U1)GVIF3RX_PROC_REQNUM; u1_t_cnt++){
        u4_sp_gvif3rxprocque[u1_t_cnt] = (U4)0U;
    }
    u1_s_gvif3rxprocque_cnt = (U1)0;
    u1_s_gvif3rxprocexe_cnt = (U1)0;
}

/*===================================================================================================================================*/
/*  static void    vd_s_Gvif3RxProcessChk(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_Gvif3RxProcessChk(void)
{
    U1 u1_t_func_sts;
    U4 u4_t_cond_met_flg_tmp;
    U4 u4_t_proc_que_tmp;

    u4_t_cond_met_flg_tmp = u4_s_gvif3rxproccond_met_flg & (U4)GVIF3RX_PROC_RESERVE;

    if((u1_s_gvif3rxprocexe_cnt < (U1)GVIF3RX_PROC_REQNUM)
    && (u4_s_gvif3rxproccond_met_flg != (U4)GVIF3RX_PROC_NON)
    && (u4_t_cond_met_flg_tmp == (U4)0)){
        switch (u4_sp_gvif3rxprocque[u1_s_gvif3rxprocexe_cnt]){
            case GVIF3RX_PROC_BANK0:
                u1_t_func_sts = u1_s_Gvif3Bank0Chg();
                break;
            case GVIF3RX_PROC_BANK2:
                u1_t_func_sts = u1_s_Gvif3Bank2Chg();
                break;
            case GVIF3RX_PROC_BANK3:
                u1_t_func_sts = u1_s_Gvif3Bank3Chg();
                break;
            case GVIF3RX_PROC_MIPITX:
                u1_t_func_sts = u1_s_Gvif3RxMipitxRegSet();
                if(u1_t_func_sts == (U1)TRUE){
                    /* Excuted Flag ON */
                    u1_s_gvif3rxmipitxset_flg = (U1)TRUE;
                }
                break;
            case GVIF3RX_PROC_DEVERRCHK:
                u1_t_func_sts = u1_s_Gvif3DevErrStsGet();
                if(u1_t_func_sts == (U1)TRUE){
                    /* Excuted Flag ON */
                    u1_s_gvif3rxdeverrchk_flg = (U1)TRUE;
                }
                break;
            case GVIF3RX_PROC_LINKCHK:
                u1_t_func_sts = u1_s_Gvif3LinkStsGet();
                if(u1_t_func_sts == (U1)TRUE){
                    /* Excuted Flag ON */
                    u1_s_gvif3rxlinkchk_flg = (U1)TRUE;
                }
                break;
            case GVIF3RX_PROC_ERROR1CHK:
                u1_t_func_sts = u1_s_Gvif3Error1StsGet();
                if(u1_t_func_sts == (U1)TRUE){
                    /* Excuted Flag ON */
                    u1_s_gvif3rxerr1chk_flg = (U1)TRUE;
                }
                break;
            case GVIF3RX_PROC_ERROR2CHK:
                u1_t_func_sts = u1_s_Gvif3Error2StsGet();
                if(u1_t_func_sts == (U1)TRUE){
                    /* Excuted Flag ON */
                    u1_s_gvif3rxerr2chk_flg = (U1)TRUE;
                }
                break;
            case GVIF3RX_PROC_ERROR3CHK:
                u1_t_func_sts = u1_s_Gvif3Error3StsGet();
                if(u1_t_func_sts == (U1)TRUE){
                    /* Excuted Flag ON */
                    u1_s_gvif3rxerr3chk_flg = (U1)TRUE;
                }
                break;
            case GVIF3RX_PROC_ERROR4CHK:
                u1_t_func_sts = u1_s_Gvif3Error4StsGet();
                if(u1_t_func_sts == (U1)TRUE){
                    /* Excuted Flag ON */
                    u1_s_gvif3rxerr4chk_flg = (U1)TRUE;
                }
                break;
            case GVIF3RX_PROC_ERROR5CHK:
                u1_t_func_sts = u1_s_Gvif3Error5StsGet();
                if(u1_t_func_sts == (U1)TRUE){
                    /* Excuted Flag ON */
                    u1_s_gvif3rxerr5chk_flg = (U1)TRUE;
                }
                break;
            case GVIF3RX_PROC_ERROR6CHK:
                u1_t_func_sts = u1_s_Gvif3Error6StsGet();
                if(u1_t_func_sts == (U1)TRUE){
                    /* Excuted Flag ON */
                    u1_s_gvif3rxerr6chk_flg = (U1)TRUE;
                }
                break;
            case GVIF3RX_PROC_ERROR7CHK:
                u1_t_func_sts = u1_s_Gvif3Error7StsGet();
                if(u1_t_func_sts == (U1)TRUE){
                    /* Excuted Flag ON */
                    u1_s_gvif3rxerr7chk_flg = (U1)TRUE;
                }
                break;
            case GVIF3RX_PROC_ERROR8CHK:
                u1_t_func_sts = u1_s_Gvif3Error8StsGet();
                if(u1_t_func_sts == (U1)TRUE){
                    /* Excuted Flag ON */
                    u1_s_gvif3rxerr8chk_flg = (U1)TRUE;
                }
                break;
            case GVIF3RX_PROC_ERROR9CHK:
                u1_t_func_sts = u1_s_Gvif3Error9StsGet();
                if(u1_t_func_sts == (U1)TRUE){
                    /* Excuted Flag ON */
                    u1_s_gvif3rxerr9chk_flg = (U1)TRUE;
                }
                break;
            case GVIF3RX_PROC_ERROR10CHK:
                u1_t_func_sts = u1_s_Gvif3Error10StsGet();
                if(u1_t_func_sts == (U1)TRUE){
                    /* Excuted Flag ON */
                    u1_s_gvif3rxerr10chk_flg = (U1)TRUE;
                }
                break;
            case GVIF3RX_PROC_ERRCLRSET:
                u1_t_func_sts = u1_s_Gvif3RxErrClrRegSet();
                if(u1_t_func_sts == (U1)TRUE){
                    /* Excuted Flag ON */
                    u1_s_gvif3rxerrclr_flg = (U1)TRUE;
                }
                break;
            case GVIF3RX_PROC_ERRCLRRLS:
                u1_t_func_sts = u1_s_Gvif3RxErrClrRlsRegSet();
                if(u1_t_func_sts == (U1)TRUE){
                    /* Excuted Flag ON */
                    u1_s_gvif3rxerrclrrls_flg = (U1)TRUE;
                }
                break;
            case GVIF3RX_PROC_SIPERRORMIPISET:
                u1_t_func_sts = u1_s_Gvif3SipErrMipiRegSet();
                if(u1_t_func_sts == (U1)TRUE){
                    /* Excuted Flag ON */
                    u1_s_gvif3rxsiperrmipiset_flg = (U1)TRUE;
                }
                break;
            case GVIF3RX_PROC_UNL0SET2_SET:
                u1_t_func_sts = u1_s_Gvif3RxUnl0Set2RegSet();
                if(u1_t_func_sts == (U1)TRUE){
                    /* Excuted Flag ON */
                    u1_s_gvif3rxunl0set2_flg = (U1)TRUE;
                }
                break;
            case GVIF3RX_PROC_UNL1SET2_SET:
                u1_t_func_sts = u1_s_Gvif3RxUnl1Set2RegSet();
                if(u1_t_func_sts == (U1)TRUE){
                    /* Excuted Flag ON */
                    u1_s_gvif3rxunl1set2_flg = (U1)TRUE;
                }
                break;
            case GVIF3RX_PROC_UNL2SET2_SET:
                u1_t_func_sts = u1_s_Gvif3RxUnl2Set2RegSet();
                if(u1_t_func_sts == (U1)TRUE){
                    /* Excuted Flag ON */
                    u1_s_gvif3rxunl2set2_flg = (U1)TRUE;
                }
                break;
            case GVIF3RX_PROC_UNL3SET2_SET:
                u1_t_func_sts = u1_s_Gvif3RxUnl3Set2RegSet();
                if(u1_t_func_sts == (U1)TRUE){
                    /* Excuted Flag ON */
                    u1_s_gvif3rxunl3set2_flg = (U1)TRUE;
                }
                break;
            case GVIF3RX_PROC_UNL4SET2_SET:
                u1_t_func_sts = u1_s_Gvif3RxUnl4Set2RegSet();
                if(u1_t_func_sts == (U1)TRUE){
                    /* Excuted Flag ON */
                    u1_s_gvif3rxunl4set2_flg = (U1)TRUE;
                }
                break;
            case GVIF3RX_PROC_UNL5SET2_SET:
                u1_t_func_sts = u1_s_Gvif3RxUnl5Set2RegSet();
                if(u1_t_func_sts == (U1)TRUE){
                    /* Excuted Flag ON */
                    u1_s_gvif3rxunl5set2_flg = (U1)TRUE;
                }
                break;
            case GVIF3RX_PROC_GPIOSET_SET:
                u1_t_func_sts = u1_s_Gvif3RxGpioSetRegSet();
                if(u1_t_func_sts == (U1)TRUE){
                    /* Excuted Flag ON */
                    u1_s_gvif3rxgpioset_flg = (U1)TRUE;
                }
                break;
            case GVIF3RX_PROC_NON:
                /* 何もしない */
                /* do noting */
                break;
            default:
                vd_s_Gvif3RxProcessInit();
                break;
        }

        if(u1_t_func_sts == (U1)TRUE){
            /* Process Condition Met Flag Clear */
            u4_t_proc_que_tmp = u4_sp_gvif3rxprocque[u1_s_gvif3rxprocexe_cnt];
            u4_s_gvif3rxproccond_met_flg &= ~u4_t_proc_que_tmp;
            /* Process Queue Clear */
            u4_sp_gvif3rxprocque[u1_s_gvif3rxprocexe_cnt] = (U4)0U;
            /* Counter Update */
            if(u1_s_gvif3rxprocexe_cnt == (U1)((U1)GVIF3RX_PROC_REQNUM - (U1)1U)){
                u1_s_gvif3rxprocexe_cnt = (U1)0;
            }
            else{
                u1_s_gvif3rxprocexe_cnt++;
            }
        }
    }
    else{
        vd_s_Gvif3RxProcessInit();
    }
}

/*===================================================================================================================================*/
/*  static void    vd_s_Gvif3RxCycChk(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_Gvif3RxCycChk(void)
{
    U1 u1_t_stasts;
    U1 u1_t_jdg;
    
    u1_t_stasts = u1_g_Power_ModeState();
    u1_t_jdg = (U1)FALSE;

    vd_s_Gvif3RxCamKindGet();

    switch (u1_s_gvif3perimoni_step)
    {
        case GVIF3RX_PERIMONI_STEP1:
            if(u1_s_gvifcamKind_last != u1_s_gvif3rxcamkind_now){
                u1_s_gvifcamKind_last = u1_s_gvif3rxcamkind_now;
                u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP2;
            }
            else{
                u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP3;
            }
            break;
        case GVIF3RX_PERIMONI_STEP2:
            u1_t_jdg = u1_s_Gvif3RxCamKindDat();
            if(u1_t_jdg == (U1)TRUE){
                u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP3;
            }
            break;
        case GVIF3RX_PERIMONI_STEP3:
            if(u1_s_gvif3rxcamkind_now != (U1)GVIF3RX_KIND_CAM_NONE){
                u1_t_jdg = u1_s_Gvif3Mipijdg();
                if(u1_t_jdg == (U1)TRUE){
                    u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP4;
                }
            }
            else{
                u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP11;/* カメラ有無共通のSTEPへ */
            }
            break;
    
        case GVIF3RX_PERIMONI_STEP4:
            u1_t_jdg = u1_s_Gvif3DevErrChk();
            if(u1_t_jdg == (U1)GVIF3RX_DEVERR_NON){
                u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP5;
            }
            else if(u1_t_jdg == (U1)GVIF3RX_DEVERR_RST){
                u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP_FIN; /* 定期終了 */
            }
            else{
                /* do nothing */
            }
            break;
    
        case GVIF3RX_PERIMONI_STEP5:
            if(u1_t_stasts == (U1)POWER_MODE_STATE_APPON){/* 見た目オン起動 */
                u1_t_jdg = u1_s_Gvif3LinkChk();
                if(u1_t_jdg == (U1)TRUE){
                    u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP6;
                }
            }
            else{
                u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP6;
            }
            break;
    
        case GVIF3RX_PERIMONI_STEP6:
            if(u1_s_gvif3rx0unconflg == (U1)GVIF3RX_UNCON_FLGOFF){
                u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP7;
            }
            else{
                u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP9;
            }
            break;
    
        case GVIF3RX_PERIMONI_STEP7:
            u1_t_jdg = u1_s_Gvif3Error1Chk();
            if(u1_t_jdg == (U1)TRUE){
                u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP8;
            }
            break;
    
        case GVIF3RX_PERIMONI_STEP8:
            u1_t_jdg = u1_s_Gvif3Error3Chk();
            if(u1_t_jdg == (U1)TRUE){
                u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP9;
            }
            break;
    
        case GVIF3RX_PERIMONI_STEP9:
            if(u1_s_gvif3rx1unconflg == (U1)GVIF3RX_UNCON_FLGOFF){
                u1_t_jdg = u1_s_Gvif3Error2Chk();
                if(u1_t_jdg == (U1)TRUE){
                    u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP10;
                }
            }
            else{
                u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP10;
            }
            break;
    
        case GVIF3RX_PERIMONI_STEP10:
            if((u1_s_gvif3rx0unconflg == (U1)GVIF3RX_UNCON_FLGOFF) && (u1_s_gvif3rx1unconflg == (U1)GVIF3RX_UNCON_FLGOFF)){
                u1_t_jdg = u1_s_Gvif3Error4Chk();
                if(u1_t_jdg == (U1)TRUE){
                    u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP11;
                }
            }
            else{
                u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP11;
            }
            break;
    
        case GVIF3RX_PERIMONI_STEP11:
            u1_t_jdg = u1_s_Gvif3Error5Chk();
            if(u1_t_jdg == (U1)TRUE){
                u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP12;
            }
            break;
    
        case GVIF3RX_PERIMONI_STEP12:
            u1_t_jdg = u1_s_Gvif3Error6Chk();
            if(u1_t_jdg == (U1)TRUE){
                u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP13;
            }
            break;
    
        case GVIF3RX_PERIMONI_STEP13:
            u1_t_jdg = u1_s_Gvif3Error7Chk();
            if(u1_t_jdg == (U1)TRUE){
                u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP14;
            }
            break;
    
        case GVIF3RX_PERIMONI_STEP14:
            u1_t_jdg = u1_s_Gvif3Error8Chk();
            if(u1_t_jdg == (U1)TRUE){
                u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP15;
            }
            break;
    
        case GVIF3RX_PERIMONI_STEP15:
            u1_t_jdg = u1_s_Gvif3Error9Chk();
            if(u1_t_jdg == (U1)TRUE){
                u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP16;
            }
            break;
    
        case GVIF3RX_PERIMONI_STEP16:
            u1_t_jdg = u1_s_Gvif3Error10Chk();
            if(u1_t_jdg == (U1)TRUE){
                u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP17;
            }
            break;
    
        case GVIF3RX_PERIMONI_STEP17:
            u1_t_jdg = u1_s_Gvif3RxErrClr();
            if(u1_t_jdg == (U1)TRUE){
                u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP18;
            }
            break;
    
        case GVIF3RX_PERIMONI_STEP18:
            u1_t_jdg = u1_s_Gvif3RxErrClrRls();
            if(u1_t_jdg == (U1)TRUE){
                u1_s_gvif3rxchkflg = (U1)FALSE;
                u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP1;
            }
            break;
    
        case GVIF3RX_PERIMONI_STEP_FIN:
            /* 何もしない */
            break;
    
        default:
            u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP1;
            break;
    }
}

/*===================================================================================================================================*/
/*  static void    vd_s_Gvif3RxCamKindGet(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_Gvif3RxCamKindGet(void)
{
    U1 u1_t_camexist;

    u1_t_camexist = u1_g_PictCtl_GvifCamKindSts();

    if(u1_t_camexist == (U1)PICT_KIND_DOMECON_EXIST){
        u1_s_gvif3rxcamkind_now = (U1)GVIF3RX_KIND_DOMECON_EXIST;
    }
    else{
        u1_s_gvif3rxcamkind_now = (U1)GVIF3RX_KIND_CAM_NONE;
    }
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3RxCamKindDat(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3RxCamKindDat(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;

    u1_t_return = (U1)FALSE;
    u1_t_sts = (U1)FALSE;
    
    switch (u1_s_gvif3rxcamkind_step)
    {
        case GVIF3RX_CAMKIND_STEP1:
            u1_t_sts = u1_s_Gvif3MipiReset();
            if(u1_t_sts == (U1)TRUE){
                u1_s_gvif3rxcamkind_step = (U1)GVIF3RX_CAMKIND_STEP2;
            }
            break;

        case GVIF3RX_CAMKIND_STEP2:
            u1_t_sts = u1_s_Gvif3RxUnl0Set2();
            if(u1_t_sts == (U1)TRUE){
                u1_s_gvif3rxcamkind_step = (U1)GVIF3RX_CAMKIND_STEP3;
            }
            break;

        case GVIF3RX_CAMKIND_STEP3:
            u1_t_sts = u1_s_Gvif3RxUnl1Set2();
            if(u1_t_sts == (U1)TRUE){
                u1_s_gvif3rxcamkind_step = (U1)GVIF3RX_CAMKIND_STEP4;
            }
            break;

        case GVIF3RX_CAMKIND_STEP4:
            u1_t_sts = u1_s_Gvif3RxUnl2Set2();
            if(u1_t_sts == (U1)TRUE){
                u1_s_gvif3rxcamkind_step = (U1)GVIF3RX_CAMKIND_STEP5;
            }
            break;

        case GVIF3RX_CAMKIND_STEP5:
            u1_t_sts = u1_s_Gvif3RxUnl3Set2();
            if(u1_t_sts == (U1)TRUE){
                u1_s_gvif3rxcamkind_step = (U1)GVIF3RX_CAMKIND_STEP6;
            }
            break;

        case GVIF3RX_CAMKIND_STEP6:
            u1_t_sts = u1_s_Gvif3RxUnl4Set2();
            if(u1_t_sts == (U1)TRUE){
                u1_s_gvif3rxcamkind_step = (U1)GVIF3RX_CAMKIND_STEP7;
            }
            break;

        case GVIF3RX_CAMKIND_STEP7:
            u1_t_sts = u1_s_Gvif3RxUnl5Set2();
            if(u1_t_sts == (U1)TRUE){
                u1_s_gvif3rxcamkind_step = (U1)GVIF3RX_CAMKIND_STEP8;
            }
            break;
    
        case GVIF3RX_CAMKIND_STEP8:
            u1_t_sts = u1_s_Gvif3RxGpioSet();
            if(u1_t_sts == (U1)TRUE){
                u1_s_gvif3rxcamkind_step = (U1)GVIF3RX_CAMKIND_STEP9;
            }
            break;
    
        case GVIF3RX_CAMKIND_STEP9:
            u1_t_sts = u1_s_Gvif3RxErrClr();
            if(u1_t_sts == (U1)TRUE){
                u1_s_gvif3rxcamkind_step = (U1)GVIF3RX_CAMKIND_STEP10;
            }
            break;
    
        case GVIF3RX_CAMKIND_STEP10:
            u1_t_sts = u1_s_Gvif3RxErrClrRls();
            if(u1_t_sts == (U1)TRUE){
                u1_s_gvif3rxcamkind_step = (U1)GVIF3RX_CAMKIND_STEP1;
                u1_t_return = (U1)TRUE;
            }
            break;
    
        default:
            u1_s_gvif3rxcamkind_step = (U1)GVIF3RX_CAMKIND_STEP1;
        
            break;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3MipiReset(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3MipiReset(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;

    u1_t_return = (U1)FALSE;
    u1_t_sts = (U1)FALSE;
    
    switch (u1_s_gvif3mipireset_step)
    {
        case GVIF3RX_MIPIRESET_STEP1:
            vd_s_Gvif3RxBank0Chk();
            if(u1_s_gvif3rxbank_last == (U1)GVIF3RX_BANK0){
                u1_s_gvif3rxmipitx_date = (U1)GVIF3RX_VIDEO_OUTPUT_NON;
                (void)u1_s_Gvif3RxMipitxSetReq();
                u1_s_gvif3rxregacc_flg = (U1)TRUE;
                u1_s_gvif3mipireset_step = (U1)GVIF3RX_MIPIRESET_STEP2;
            }
            break;

        case GVIF3RX_MIPIRESET_STEP2:
            u1_t_sts = u1_s_Gvif3RxMipitxSetReq();
            if(u1_t_sts == (U1)TRUE){
                vd_s_Gvif3RxMipiOutputJdg();
                u1_t_return = (U1)TRUE;
                u1_s_gvif3rxregacc_flg = (U1)FALSE;
                u1_s_gvif3mipireset_step = (U1)GVIF3RX_MIPIRESET_STEP1;
            }
            break;

        default:
            u1_s_gvif3mipireset_step = (U1)GVIF3RX_MIPIRESET_STEP1;
            break;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3RxUnl0Set2(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3RxUnl0Set2(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;

    u1_t_return = (U1)FALSE;
    u1_t_sts = (U1)FALSE;
    
    switch (u1_s_gvif3rxunl0set2_step)
    {
        case GVIF3RX_UNL0SET2_STEP1:
            vd_s_Gvif3RxBank0Chk();
            if(u1_s_gvif3rxbank_last == (U1)GVIF3RX_BANK0){
                (void)u1_s_Gvif3RxUnl0Set2SetReq();
                u1_s_gvif3rxregacc_flg = (U1)TRUE;
                u1_s_gvif3rxunl0set2_step = (U1)GVIF3RX_UNL0SET2_STEP2;
            }
            break;

        case GVIF3RX_UNL0SET2_STEP2:
            u1_t_sts = u1_s_Gvif3RxUnl0Set2SetReq();
            if(u1_t_sts == (U1)TRUE){
                u1_t_return = (U1)TRUE;
                u1_s_gvif3rxregacc_flg = (U1)FALSE;
                u1_s_gvif3rxunl0set2_step = (U1)GVIF3RX_UNL0SET2_STEP1;
            }
            break;
    
        default:
            u1_s_gvif3rxunl0set2_step = (U1)GVIF3RX_UNL0SET2_STEP1;
        
            break;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_Gvif3RxUnl0Set2SetReq(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         TRUE (Function Completion) / FALSE (Function Incompletion)                                                       */
/*===================================================================================================================================*/
static U1    u1_s_Gvif3RxUnl0Set2SetReq(void)
{
    U1      u1_t_ret;                                               /* Function Completion Status  */

    if(u1_s_gvif3rxunl0set2_flg == (U1)TRUE){                     /* Register Set Complete */
        u1_t_ret = (U1)TRUE;
        u1_s_gvif3rxunl0set2_flg = (U1)FALSE;                     /* Flag Clear */
    }
    else{
        u1_t_ret = (U1)FALSE;
        vd_s_Gvif3RxProcessMng((U4)GVIF3RX_PROC_UNL0SET2_SET);
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3RxUnl0Set2RegSet(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3RxUnl0Set2RegSet(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;

    u1_t_return = (U1)FALSE;
    
    if(u1_s_gvifcamKind_last >= (U1)GVIF3RX_CAMKIND_NUM){
        u1_s_gvifcamKind_last = (U1)GVIF3RX_KIND_CAM_NONE;
    }
    
    u1_t_sts = (U1)Mcu_Dev_I2c_Ctrl_RegSet((U1)MCU_I2C_ACK_GVIF_RX, &u2_s_gvif3rx_regstep, (U2)GVIF3RX_OUTSET_WRINUM,
                                           (U1)GP_I2C_MA_SLA_2_GVIF_RX, st_sp_GVIFRX_OUTSET, &u4_s_gcif3acktime,
                                            &st_sp_GVIF3RX_REG_UNLD0_2_WR[u1_s_gvifcamKind_last], &u2_s_gvif3rxregset_betwaittime_stub);
    if(u1_t_sts == (U1)TRUE){
        u1_t_return = (U1)TRUE;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3RxUnl1Set2(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3RxUnl1Set2(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;

    u1_t_return = (U1)FALSE;
    u1_t_sts = (U1)FALSE;
    
    switch (u1_s_gvif3rxunl1set2_step)
    {
        case GVIF3RX_UNL1SET2_STEP1:
            vd_s_Gvif3RxBank0Chk();
            if(u1_s_gvif3rxbank_last == (U1)GVIF3RX_BANK0){
                (void)u1_s_Gvif3RxUnl1Set2SetReq();
                u1_s_gvif3rxregacc_flg = (U1)TRUE;
                u1_s_gvif3rxunl1set2_step = (U1)GVIF3RX_UNL1SET2_STEP2;
            }
            break;

        case GVIF3RX_UNL1SET2_STEP2:
            u1_t_sts = u1_s_Gvif3RxUnl1Set2SetReq();
            if(u1_t_sts == (U1)TRUE){
                u1_t_return = (U1)TRUE;
                u1_s_gvif3rxregacc_flg = (U1)FALSE;
                u1_s_gvif3rxunl1set2_step = (U1)GVIF3RX_UNL1SET2_STEP1;
            }
            break;
    
        default:
            u1_s_gvif3rxunl1set2_step = (U1)GVIF3RX_UNL1SET2_STEP1;
        
            break;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_Gvif3RxUnl1Set2SetReq(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         TRUE (Function Completion) / FALSE (Function Incompletion)                                                       */
/*===================================================================================================================================*/
static U1    u1_s_Gvif3RxUnl1Set2SetReq(void)
{
    U1      u1_t_ret;                                               /* Function Completion Status  */

    if(u1_s_gvif3rxunl1set2_flg == (U1)TRUE){                     /* Register Set Complete */
        u1_t_ret = (U1)TRUE;
        u1_s_gvif3rxunl1set2_flg = (U1)FALSE;                     /* Flag Clear */
    }
    else{
        u1_t_ret = (U1)FALSE;
        vd_s_Gvif3RxProcessMng((U4)GVIF3RX_PROC_UNL1SET2_SET);
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3RxUnl1Set2RegSet(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3RxUnl1Set2RegSet(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;

    u1_t_return = (U1)FALSE;
    
    if(u1_s_gvifcamKind_last >= (U1)GVIF3RX_CAMKIND_NUM){
        u1_s_gvifcamKind_last = (U1)GVIF3RX_KIND_CAM_NONE;
    }
    
    u1_t_sts = (U1)Mcu_Dev_I2c_Ctrl_RegSet((U1)MCU_I2C_ACK_GVIF_RX, &u2_s_gvif3rx_regstep, (U2)GVIF3RX_OUTSET_WRINUM,
                                           (U1)GP_I2C_MA_SLA_2_GVIF_RX, st_sp_GVIFRX_OUTSET, &u4_s_gcif3acktime,
                                            &st_sp_GVIF3RX_REG_UNLD1_2_WR[u1_s_gvifcamKind_last], &u2_s_gvif3rxregset_betwaittime_stub);
    if(u1_t_sts == (U1)TRUE){
        u1_t_return = (U1)TRUE;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3RxUnl2Set2(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3RxUnl2Set2(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;

    u1_t_return = (U1)FALSE;
    u1_t_sts = (U1)FALSE;
    
    switch (u1_s_gvif3rxunl2set2_step)
    {
        case GVIF3RX_UNL2SET2_STEP1:
            vd_s_Gvif3RxBank2Chk();
            if(u1_s_gvif3rxbank_last == (U1)GVIF3RX_BANK2){
                (void)u1_s_Gvif3RxUnl2Set2SetReq();
                u1_s_gvif3rxregacc_flg = (U1)TRUE;
                u1_s_gvif3rxunl2set2_step = (U1)GVIF3RX_UNL2SET2_STEP2;
            }
            break;

        case GVIF3RX_UNL2SET2_STEP2:
            u1_t_sts = u1_s_Gvif3RxUnl2Set2SetReq();
            if(u1_t_sts == (U1)TRUE){
                u1_t_return = (U1)TRUE;
                u1_s_gvif3rxregacc_flg = (U1)FALSE;
                u1_s_gvif3rxunl2set2_step = (U1)GVIF3RX_UNL2SET2_STEP1;
            }
            break;
    
        default:
            u1_s_gvif3rxunl2set2_step = (U1)GVIF3RX_UNL2SET2_STEP1;
        
            break;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_Gvif3RxUnl2Set2SetReq(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         TRUE (Function Completion) / FALSE (Function Incompletion)                                                       */
/*===================================================================================================================================*/
static U1    u1_s_Gvif3RxUnl2Set2SetReq(void)
{
    U1      u1_t_ret;                                               /* Function Completion Status  */

    if(u1_s_gvif3rxunl2set2_flg == (U1)TRUE){                     /* Register Set Complete */
        u1_t_ret = (U1)TRUE;
        u1_s_gvif3rxunl2set2_flg = (U1)FALSE;                     /* Flag Clear */
    }
    else{
        u1_t_ret = (U1)FALSE;
        vd_s_Gvif3RxProcessMng((U4)GVIF3RX_PROC_UNL2SET2_SET);
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3RxUnl2Set2RegSet(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3RxUnl2Set2RegSet(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;

    u1_t_return = (U1)FALSE;
    
    if(u1_s_gvifcamKind_last >= (U1)GVIF3RX_CAMKIND_NUM){
        u1_s_gvifcamKind_last = (U1)GVIF3RX_KIND_CAM_NONE;
    }
    
    u1_t_sts = (U1)Mcu_Dev_I2c_Ctrl_RegSet((U1)MCU_I2C_ACK_GVIF_RX, &u2_s_gvif3rx_regstep, (U2)GVIF3RX_OUTSET_WRINUM,
                                           (U1)GP_I2C_MA_SLA_2_GVIF_RX, st_sp_GVIFRX_OUTSET, &u4_s_gcif3acktime,
                                            &st_sp_GVIF3RX_REG_UNLD2_2_WR[u1_s_gvifcamKind_last], &u2_s_gvif3rxregset_betwaittime_stub);
    if(u1_t_sts == (U1)TRUE){
        u1_t_return = (U1)TRUE;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3RxUnl3Set2(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3RxUnl3Set2(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;

    u1_t_return = (U1)FALSE;
    u1_t_sts = (U1)FALSE;
    
    switch (u1_s_gvif3rxunl3set2_step)
    {
        case GVIF3RX_UNL3SET2_STEP1:
            vd_s_Gvif3RxBank2Chk();
            if(u1_s_gvif3rxbank_last == (U1)GVIF3RX_BANK2){
                (void)u1_s_Gvif3RxUnl3Set2SetReq();
                u1_s_gvif3rxregacc_flg = (U1)TRUE;
                u1_s_gvif3rxunl3set2_step = (U1)GVIF3RX_UNL3SET2_STEP2;
            }
            break;

        case GVIF3RX_UNL3SET2_STEP2:
            u1_t_sts = u1_s_Gvif3RxUnl3Set2SetReq();
            if(u1_t_sts == (U1)TRUE){
                u1_t_return = (U1)TRUE;
                u1_s_gvif3rxregacc_flg = (U1)FALSE;
                u1_s_gvif3rxunl3set2_step = (U1)GVIF3RX_UNL3SET2_STEP1;
            }
            break;
    
        default:
            u1_s_gvif3rxunl3set2_step = (U1)GVIF3RX_UNL3SET2_STEP1;
        
            break;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_Gvif3RxUnl3Set2SetReq(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         TRUE (Function Completion) / FALSE (Function Incompletion)                                                       */
/*===================================================================================================================================*/
static U1    u1_s_Gvif3RxUnl3Set2SetReq(void)
{
    U1      u1_t_ret;                                               /* Function Completion Status  */

    if(u1_s_gvif3rxunl3set2_flg == (U1)TRUE){                     /* Register Set Complete */
        u1_t_ret = (U1)TRUE;
        u1_s_gvif3rxunl3set2_flg = (U1)FALSE;                     /* Flag Clear */
    }
    else{
        u1_t_ret = (U1)FALSE;
        vd_s_Gvif3RxProcessMng((U4)GVIF3RX_PROC_UNL3SET2_SET);
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3RxUnl3Set2RegSet(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3RxUnl3Set2RegSet(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;

    u1_t_return = (U1)FALSE;
    
    if(u1_s_gvifcamKind_last >= (U1)GVIF3RX_CAMKIND_NUM){
        u1_s_gvifcamKind_last = (U1)GVIF3RX_KIND_CAM_NONE;
    }
    
    u1_t_sts = (U1)Mcu_Dev_I2c_Ctrl_RegSet((U1)MCU_I2C_ACK_GVIF_RX, &u2_s_gvif3rx_regstep, (U2)GVIF3RX_OUTSET_WRINUM,
                                           (U1)GP_I2C_MA_SLA_2_GVIF_RX, st_sp_GVIFRX_OUTSET, &u4_s_gcif3acktime,
                                            &st_sp_GVIF3RX_REG_UNLD3_2_WR[u1_s_gvifcamKind_last], &u2_s_gvif3rxregset_betwaittime_stub);
    if(u1_t_sts == (U1)TRUE){
        u1_t_return = (U1)TRUE;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3RxUnl4Set2(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3RxUnl4Set2(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;

    u1_t_return = (U1)FALSE;
    u1_t_sts = (U1)FALSE;
    
    switch (u1_s_gvif3rxunl4set2_step)
    {
        case GVIF3RX_UNL4SET2_STEP1:
            vd_s_Gvif3RxBank3Chk();
            if(u1_s_gvif3rxbank_last == (U1)GVIF3RX_BANK3){
                (void)u1_s_Gvif3RxUnl4Set2SetReq();
                u1_s_gvif3rxregacc_flg = (U1)TRUE;
                u1_s_gvif3rxunl4set2_step = (U1)GVIF3RX_UNL4SET2_STEP2;
            }
            break;

        case GVIF3RX_UNL4SET2_STEP2:
            u1_t_sts = u1_s_Gvif3RxUnl4Set2SetReq();
            if(u1_t_sts == (U1)TRUE){
                u1_t_return = (U1)TRUE;
                u1_s_gvif3rxunl4set2_step = (U1)GVIF3RX_UNL4SET2_STEP1;
                u1_s_gvif3rxregacc_flg = (U1)FALSE;
            }
            break;
    
        default:
            u1_s_gvif3rxunl4set2_step = (U1)GVIF3RX_UNL4SET2_STEP1;
        
            break;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_Gvif3RxUnl4Set2SetReq(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         TRUE (Function Completion) / FALSE (Function Incompletion)                                                       */
/*===================================================================================================================================*/
static U1    u1_s_Gvif3RxUnl4Set2SetReq(void)
{
    U1      u1_t_ret;                                               /* Function Completion Status  */

    if(u1_s_gvif3rxunl4set2_flg == (U1)TRUE){                     /* Register Set Complete */
        u1_t_ret = (U1)TRUE;
        u1_s_gvif3rxunl4set2_flg = (U1)FALSE;                     /* Flag Clear */
    }
    else{
        u1_t_ret = (U1)FALSE;
        vd_s_Gvif3RxProcessMng((U4)GVIF3RX_PROC_UNL4SET2_SET);
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3RxUnl4Set2RegSet(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3RxUnl4Set2RegSet(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;

    u1_t_return = (U1)FALSE;
    
    if(u1_s_gvifcamKind_last >= (U1)GVIF3RX_CAMKIND_NUM){
        u1_s_gvifcamKind_last = (U1)GVIF3RX_KIND_CAM_NONE;
    }
    
    u1_t_sts = (U1)Mcu_Dev_I2c_Ctrl_RegSet((U1)MCU_I2C_ACK_GVIF_RX, &u2_s_gvif3rx_regstep, (U2)GVIF3RX_OUTSET_WRINUM,
                                           (U1)GP_I2C_MA_SLA_2_GVIF_RX, st_sp_GVIFRX_OUTSET, &u4_s_gcif3acktime,
                                            &st_sp_GVIF3RX_REG_UNLD4_2_WR[u1_s_gvifcamKind_last], &u2_s_gvif3rxregset_betwaittime_stub);
    if(u1_t_sts == (U1)TRUE){
        u1_t_return = (U1)TRUE;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3RxUnl5Set2(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3RxUnl5Set2(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;

    u1_t_return = (U1)FALSE;
    u1_t_sts = (U1)FALSE;
    
    switch (u1_s_gvif3rxunl5set2_step)
    {
        case GVIF3RX_UNL5SET2_STEP1:
            vd_s_Gvif3RxBank3Chk();
            if(u1_s_gvif3rxbank_last == (U1)GVIF3RX_BANK3){
                (void)u1_s_Gvif3RxUnl5Set2SetReq();
                u1_s_gvif3rxregacc_flg = (U1)TRUE;
                u1_s_gvif3rxunl5set2_step = (U1)GVIF3RX_UNL5SET2_STEP2;
            }
            break;

        case GVIF3RX_UNL5SET2_STEP2:
            u1_t_sts = u1_s_Gvif3RxUnl5Set2SetReq();
            if(u1_t_sts == (U1)TRUE){
                u1_t_return = (U1)TRUE;
                u1_s_gvif3rxregacc_flg = (U1)FALSE;
                u1_s_gvif3rxunl5set2_step = (U1)GVIF3RX_UNL5SET2_STEP1;
            }
            break;
    
        default:
            u1_s_gvif3rxunl5set2_step = (U1)GVIF3RX_UNL5SET2_STEP1;
        
            break;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_Gvif3RxUnl5Set2SetReq(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         TRUE (Function Completion) / FALSE (Function Incompletion)                                                       */
/*===================================================================================================================================*/
static U1    u1_s_Gvif3RxUnl5Set2SetReq(void)
{
    U1      u1_t_ret;                                               /* Function Completion Status  */

    if(u1_s_gvif3rxunl5set2_flg == (U1)TRUE){                     /* Register Set Complete */
        u1_t_ret = (U1)TRUE;
        u1_s_gvif3rxunl5set2_flg = (U1)FALSE;                     /* Flag Clear */
    }
    else{
        u1_t_ret = (U1)FALSE;
        vd_s_Gvif3RxProcessMng((U4)GVIF3RX_PROC_UNL5SET2_SET);
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3RxUnl5Set2RegSet(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3RxUnl5Set2RegSet(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;

    u1_t_return = (U1)FALSE;
    
    if(u1_s_gvifcamKind_last >= (U1)GVIF3RX_CAMKIND_NUM){
        u1_s_gvifcamKind_last = (U1)GVIF3RX_KIND_CAM_NONE;
    }
    
    u1_t_sts = (U1)Mcu_Dev_I2c_Ctrl_RegSet((U1)MCU_I2C_ACK_GVIF_RX, &u2_s_gvif3rx_regstep, (U2)GVIF3RX_OUTSET_WRINUM,
                                           (U1)GP_I2C_MA_SLA_2_GVIF_RX, st_sp_GVIFRX_OUTSET, &u4_s_gcif3acktime,
                                            &st_sp_GVIF3RX_REG_UNLD5_2_WR[u1_s_gvifcamKind_last], &u2_s_gvif3rxregset_betwaittime_stub);
    if(u1_t_sts == (U1)TRUE){
        u1_t_return = (U1)TRUE;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3RxGpioSet(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3RxGpioSet(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;

    u1_t_return = (U1)FALSE;
    u1_t_sts = (U1)FALSE;
    
    switch (u1_s_gvif3rxgpioset_step)
    {
        case GVIF3RX_GPIOSET_STEP1:
            vd_s_Gvif3RxBank0Chk();
            if(u1_s_gvif3rxbank_last == (U1)GVIF3RX_BANK0){
                (void)u1_s_Gvif3RxGpioSetReq();
                u1_s_gvif3rxregacc_flg = (U1)TRUE;
                u1_s_gvif3rxgpioset_step = (U1)GVIF3RX_GPIOSET_STEP2;
            }
            break;

        case GVIF3RX_GPIOSET_STEP2:
            u1_t_sts = u1_s_Gvif3RxGpioSetReq();
            if(u1_t_sts == (U1)TRUE){
                u1_t_return = (U1)TRUE;
                u1_s_gvif3rxregacc_flg = (U1)FALSE;
                u1_s_gvif3rxgpioset_step = (U1)GVIF3RX_GPIOSET_STEP1;
            }
            break;
    
        default:
            u1_s_gvif3rxgpioset_step = (U1)GVIF3RX_GPIOSET_STEP1;
        
            break;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_Gvif3RxGpioSetReq(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         TRUE (Function Completion) / FALSE (Function Incompletion)                                                       */
/*===================================================================================================================================*/
static U1    u1_s_Gvif3RxGpioSetReq(void)
{
    U1      u1_t_ret;                                               /* Function Completion Status  */

    if(u1_s_gvif3rxgpioset_flg == (U1)TRUE){                     /* Register Set Complete */
        u1_t_ret = (U1)TRUE;
        u1_s_gvif3rxgpioset_flg = (U1)FALSE;                     /* Flag Clear */
    }
    else{
        u1_t_ret = (U1)FALSE;
        vd_s_Gvif3RxProcessMng((U4)GVIF3RX_PROC_GPIOSET_SET);
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3RxGpioSetRegSet(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3RxGpioSetRegSet(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;

    u1_t_return = (U1)FALSE;
    
    if(u1_s_gvifcamKind_last >= (U1)GVIF3RX_CAMKIND_NUM){
        u1_s_gvifcamKind_last = (U1)GVIF3RX_KIND_CAM_NONE;
    }
    
    u1_t_sts = (U1)Mcu_Dev_I2c_Ctrl_RegSet((U1)MCU_I2C_ACK_GVIF_RX, &u2_s_gvif3rx_regstep, (U2)GVIF3RX_OUTSET_WRINUM,
                                           (U1)GP_I2C_MA_SLA_2_GVIF_RX, st_sp_GVIFRX_OUTSET, &u4_s_gcif3acktime,
                                            &st_sp_GVIF3RX_REG_GPIO3_WR[u1_s_gvifcamKind_last], &u2_s_gvif3rxregset_betwaittime_stub);
    if(u1_t_sts == (U1)TRUE){
        u1_t_return = (U1)TRUE;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  void    vd_g_Gvif3RxStby3StsSet(U1 u1_a_stby3sts)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Gvif3RxStby3StsSet(U1 u1_a_stby3sts)
{
    u1_s_gvif3rxstby3sts = u1_a_stby3sts;
}

/*===================================================================================================================================*/
/*  U1      u1_g_Gvif3RxMipiOutputSts(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_Gvif3RxMipiOutputSts(void)
{
    return(u1_s_gvif3rxmipitx_send);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3Mipijdg(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3Mipijdg(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;
    U1 u1_t_writedate;
    
    u1_t_return = (U1)FALSE;
    u1_t_sts = (U1)FALSE;
    u1_t_writedate = (U1)0U;

    switch (u1_s_gvif3mipi_step)
    {
        case GVIF3RX_MIPI_STEP1:
            if(Mcu_OnStep_EIZOIC_OVRALL == (uint8)MCU_STEP_EIZOIC_OVERALL_FIN){ /* 映像IC初期化済み(暫定) */
                u1_t_writedate |= (U1)GVIF3RX_VIDEO_OUTPUT_ENABLE_0;
            }
            if(u1_s_gvif3rxstby3sts == (U1)TRUE){
                u1_t_writedate |= (U1)GVIF3RX_VIDEO_OUTPUT_ENABLE_1;
            }
            u1_s_gvif3rxmipitx_date = u1_t_writedate;
            vd_s_Gvif3RxBank0Chk();
            if(u1_s_gvif3rxbank_last == (U1)GVIF3RX_BANK0){
                (void)u1_s_Gvif3RxMipitxSetReq();
                u1_s_gvif3rxregacc_flg = (U1)TRUE;
                u1_s_gvif3mipi_step = (U1)GVIF3RX_MIPI_STEP2;
            }
            break;

        case GVIF3RX_MIPI_STEP2:
            u1_t_sts = u1_s_Gvif3RxMipitxSetReq();
            if(u1_t_sts == (U1)TRUE){
                vd_s_Gvif3RxMipiOutputJdg();
                u1_t_return = (U1)TRUE;
                u1_s_gvif3rxregacc_flg = (U1)FALSE;
                u1_s_gvif3mipi_step = (U1)GVIF3RX_MIPI_STEP1;
            }

            break;
    
        default:
            u1_s_gvif3mipi_step = (U1)GVIF3RX_MIPI_STEP1;
        
            break;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static void    vd_s_Gvif3RxMipiOutputJdg(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_Gvif3RxMipiOutputJdg(void)
{
    U1 u1_t_writedate;
    
    u1_t_writedate = u1_s_gvif3rxmipitx_date & (U1)GVIF3RX_VIDEO_OUTPUT_ENABLE_1;
    if(u1_t_writedate == (U1)GVIF3RX_VIDEO_OUTPUT_ENABLE_1){
        u1_s_gvif3rxmipitx_send = (U1)GVIF3RX_MIPIOUTPUT_ON;
    }
    else{
        u1_s_gvif3rxmipitx_send = (U1)GVIF3RX_MIPIOUTPUT_OFF;
    }
}

/*===================================================================================================================================*/
/*  static U1    u1_s_Gvif3RxMipitxSetReq(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         TRUE (Function Completion) / FALSE (Function Incompletion)                                                       */
/*===================================================================================================================================*/
static U1    u1_s_Gvif3RxMipitxSetReq(void)
{
    U1      u1_t_ret;                                               /* Function Completion Status  */

    if(u1_s_gvif3rxmipitxset_flg == (U1)TRUE){                     /* Register Set Complete */
        u1_t_ret = (U1)TRUE;
        u1_s_gvif3rxmipitxset_flg = (U1)FALSE;                     /* Flag Clear */
    }
    else{
        u1_t_ret = (U1)FALSE;
        vd_s_Gvif3RxProcessMng((U4)GVIF3RX_PROC_MIPITX);
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_Gvif3RxMipitxRegSet(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         TRUE (Function Completion) / FALSE (Function Incompletion)                                                       */
/*===================================================================================================================================*/
static U1    u1_s_Gvif3RxMipitxRegSet(void)
{
    U1      u1_t_ret;                                               /* Function Completion Status  */
    U1      u1_t_reg_req_sts;

    u1_t_ret = (U1)FALSE;

    u1_t_reg_req_sts = (U1)Mcu_Dev_I2c_Ctrl_RegSet((U1)MCU_I2C_ACK_GVIF_RX, &u2_s_gvif3rx_regstep, (U2)GVIF3RX_OUTSET_WRINUM,
                                                   (U1)GP_I2C_MA_SLA_2_GVIF_RX, st_sp_GVIFRX_OUTSET, &u4_s_gcif3acktime,
                                                   &st_sp_GVIF3RX_REG_MIPI_WR[u1_s_gvif3rxmipitx_date], &u2_s_gvif3rxregset_betwaittime_stub);
    if(u1_t_reg_req_sts == (U1)TRUE){
        /* Function Completion */
        u1_t_ret = (U1)TRUE;
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3DevErrChk(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3DevErrChk(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;
    U1 u1_t_jdg;
    U1 u1_t_req;

    u1_t_return = (U1)GVIF3RX_DEVERR_CHK;
    u1_t_sts = (U1)0U;
    u1_t_jdg = (U1)0U;
    u1_t_req = (U1)FALSE;

    switch (u1_s_gvif3rxdeverr_step)
    {
        case GVIF3RX_DEVERR_STEP1:
            vd_s_Gvif3RxBank0Chk();
            if(u1_s_gvif3rxbank_last == (U1)GVIF3RX_BANK0){
                (void)u1_s_Gvif3DevErrGetReq();
                u1_s_gvif3rxregacc_flg = (U1)TRUE;
                u1_s_gvif3rxdeverr_step = (U1)GVIF3RX_DEVERR_STEP2;
            }
            break;

        case GVIF3RX_DEVERR_STEP2:
            u1_t_sts = u1_s_Gvif3DevErrGetReq();
            if(u1_t_sts == (U1)TRUE){
                u1_t_jdg = (U1)st_sp_GVIF3RX_REG_DEVERROR[1].u1p_pdu[1];
                if(u1_t_jdg != (U1)GVIF3RX_GETREG_DEV_NORMAL){
                    u1_t_req = (U1)TRUE;
                    u1_s_gvif3rxrestartflg = (U1)GVIF3RX_RESTART_FLGON;
                    u1_t_return = (U1)GVIF3RX_DEVERR_RST; /* 定期終了 */
                }
                else{
                    u1_t_return = (U1)GVIF3RX_DEVERR_NON;
                }
                u1_s_gvif3rxregacc_flg = (U1)FALSE;
                u1_s_gvif3rxdeverr_step = (U1)GVIF3RX_DEVERR_STEP1;
            }
            break;

        default:
            u1_s_gvif3rxdeverr_step = (U1)GVIF3RX_DEVERR_STEP1;
            break;
    }
    
    if((u1_s_gvif3rxdeverrflg == (U1)GVIF3RX_DEVERR_FLGOFF) && (u1_t_req == (U1)TRUE)){
        /* ダイレコ 再起動要求 */
        vd_g_SysEcDrc_Drec((U1)SYSECDRC_DREC_CAT_GVIFRX, (U1)SYSECDRC_DREC_ID_1, (U1)0x00U, (U1)0x00U);
        u1_s_gvif3rxdeverrflg = (U1)GVIF3RX_DEVERR_FLGON;
    }
    
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_Gvif3DevErrGetReq(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         TRUE (Function Completion) / FALSE (Function Incompletion)                                                       */
/*===================================================================================================================================*/
static U1    u1_s_Gvif3DevErrGetReq(void)
{
    U1      u1_t_ret;                                               /* Function Completion Status  */

    if(u1_s_gvif3rxdeverrchk_flg == (U1)TRUE){                     /* Register Set Complete */
        u1_t_ret = (U1)TRUE;
        u1_s_gvif3rxdeverrchk_flg = (U1)FALSE;                     /* Flag Clear */
    }
    else{
        u1_t_ret = (U1)FALSE;
        vd_s_Gvif3RxProcessMng((U4)GVIF3RX_PROC_DEVERRCHK);
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3DevErrStsGet(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3DevErrStsGet(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;

    u1_t_return = (U1)FALSE;

    u1_t_sts = (U1)Mcu_Dev_I2c_Ctrl_RegRead((uint8)MCU_I2C_ACK_GVIF_RX, &u2_s_gvif3rx_regstep, (uint8)GP_I2C_MA_SLA_2_GVIF_RX,
                                            &u4_s_gcif3acktime, st_sp_GVIF3RX_REG_DEVERROR, &u2_s_gvif3rxregset_betwaittime_stub, (U1)MCU_I2C_WAIT_NON);
    if(u1_t_sts == (U1)TRUE){
        u1_t_return = (U1)TRUE;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  U1      u1_g_Gvif3SipFail(void)                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_Gvif3SipFail(void)
{
    U1 u1_t_return;

    u1_t_return = (U1)FALSE;
    
    if(u1_s_gvif3rxsipfailflg == (U1)GVIF3RX_SIPERR_COMP){
        u1_t_return = (U1)TRUE;
        u1_s_gvif3rxsipfailflg = (U1)GVIF3RX_SIPERR_NON;
    }
    else if(u1_s_gvif3rxsipfailflg == (U1)GVIF3RX_SIPERR_NON){
        u1_s_gvif3rxsipfailflg = (U1)GVIF3RX_SIPERR_REQ;
    }
    else{
        /* do nothing */
    }

    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3SipFailTask(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3SipFailTask(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;
    
    u1_t_return = (U1)FALSE;
    u1_t_sts = (U1)FALSE;

    switch (u1_s_gvif3siperr_step)
    {
        case GVIF3RX_SIPERR_STEP1:
            vd_s_Gvif3RxBank0Chk();
            if(u1_s_gvif3rxbank_last == (U1)GVIF3RX_BANK0){
                u1_s_gvif3rxsiperr_date = u1_s_gvif3rxmipitx_date & (U1)GVIF3RX_VIDEO_OUTPUT_ENABLE_0;
                (void)u1_s_Gvif3RxSiPErrMipiSetReq();
                u1_s_gvif3siperr_step = (U1)GVIF3RX_SIPERR_STEP2;
            }
            break;

        case GVIF3RX_SIPERR_STEP2:
            u1_t_sts = u1_s_Gvif3RxSiPErrMipiSetReq();
            if(u1_t_sts == (U1)TRUE){
                u1_s_gvif3rxmipitx_send = (U1)GVIF3RX_MIPIOUTPUT_OFF;
                u1_t_return = (U1)TRUE;
                u1_s_gvif3rxsipfailflg = (U1)GVIF3RX_SIPERR_COMP;
                u1_s_gvif3siperr_step = (U1)GVIF3RX_SIPERR_STEP1;
            }
            break;
    
        default:
            u1_s_gvif3siperr_step = (U1)GVIF3RX_SIPERR_STEP1;
            break;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_Gvif3RxSiPErrMipiSetReq(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         TRUE (Function Completion) / FALSE (Function Incompletion)                                                       */
/*===================================================================================================================================*/
static U1    u1_s_Gvif3RxSiPErrMipiSetReq(void)
{
    U1      u1_t_ret;                                               /* Function Completion Status  */

    if(u1_s_gvif3rxsiperrmipiset_flg == (U1)TRUE){                     /* Register Set Complete */
        u1_t_ret = (U1)TRUE;
        u1_s_gvif3rxsiperrmipiset_flg = (U1)FALSE;                     /* Flag Clear */
    }
    else{
        u1_t_ret = (U1)FALSE;
        vd_s_Gvif3RxProcessMng((U4)GVIF3RX_PROC_SIPERRORMIPISET);
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3SipErrMipiRegSet(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3SipErrMipiRegSet(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;

    u1_t_return = (U1)FALSE;

    u1_t_sts = (U1)Mcu_Dev_I2c_Ctrl_RegSet((U1)MCU_I2C_ACK_GVIF_RX, &u2_s_gvif3rx_regstep, (U2)GVIF3RX_OUTSET_WRINUM,
                                           (U1)GP_I2C_MA_SLA_2_GVIF_RX, st_sp_GVIFRX_OUTSET, &u4_s_gcif3acktime,
                                            &st_sp_GVIF3RX_REG_MIPI_WR[u1_s_gvif3rxsiperr_date], &u2_s_gvif3rxregset_betwaittime_stub);
    if(u1_t_sts == (U1)TRUE){
        u1_t_return = (U1)TRUE;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static void    vd_s_Gvif3Restar(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_Gvif3Restart(void)
{
    U1 u1_t_sts;
    
    u1_t_sts = (U1)Dio_ReadChannel(GVIF3RX_PORT_CAM_RST);
    if(u1_s_gvif3rxrestartcnt < (U1)U1_MAX){
        u1_s_gvif3rxrestartcnt++;
    }
    
    if(u1_s_gvif3rxrestartflg == (U1)GVIF3RX_RESTART_FLGON){
        if(u1_t_sts == (U1)TRUE){
            Dio_WriteChannel(GVIF3RX_PORT_CAM_RST, (Dio_LevelType)FALSE);
            u1_s_gvif3rxrestartcnt = (U1)GVIF3RX_CNT_CLR;
        }
        if(u1_s_gvif3rxrestartcnt >= (U1)GVIF3RX_RESTART_WAIT){
            Dio_WriteChannel(GVIF3RX_PORT_CAM_RST, (Dio_LevelType)TRUE);
            vd_s_Gvif3RxReset();
        }
    }
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3LinkChk(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3LinkChk(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;
    U1 u1_t_jdg;

    u1_t_return = (U1)FALSE;
    u1_t_sts = (U1)0U;
    u1_t_jdg = (U1)0U;

    switch (u1_s_gvif3link_step)
    {
        case GVIF3RX_LINK_STEP1:
            vd_s_Gvif3RxBank0Chk();
            if(u1_s_gvif3rxbank_last == (U1)GVIF3RX_BANK0){
                (void)u1_s_Gvif3LinkStsGetReq();
                u1_s_gvif3rxregacc_flg = (U1)TRUE;
                u1_s_gvif3link_step = (U1)GVIF3RX_LINK_STEP2;
            }
            break;

        case GVIF3RX_LINK_STEP2:
            u1_t_sts = u1_s_Gvif3LinkStsGetReq();
            if(u1_t_sts == (U1)TRUE){
                u1_t_jdg = (U1)st_sp_GVIF3RX_REG_LINKCHK[1].u1p_pdu[1] & (U1)GVIF3RX_RX0_UNCON_MASK;
                if(u1_t_jdg == (U1)GVIF3RX_UNCON_IDLE){
                    vd_s_Gvif3RxLinkRx0Log();
                }
                else{
                    u1_s_gvif3rx0unconcnt = (U1)GVIF3RX_CNT_CLR;
                }
                u1_t_jdg = (U1)st_sp_GVIF3RX_REG_LINKCHK[1].u1p_pdu[1] & (U1)GVIF3RX_RX1_UNCON_MASK;
                if(u1_t_jdg == (U1)GVIF3RX_UNCON_IDLE){
                    vd_s_Gvif3RxLinkRx1Log();
                }
                else{
                    u1_s_gvif3rx1unconcnt = (U1)GVIF3RX_CNT_CLR;
                }
                u1_t_return = (U1)TRUE;
                u1_s_gvif3rxregacc_flg = (U1)FALSE;
                u1_s_gvif3link_step = (U1)GVIF3RX_LINK_STEP1;
            }
            break;

        default:
            u1_s_gvif3link_step = (U1)GVIF3RX_LINK_STEP1;
            break;
    }
    
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static void   vd_s_Gvif3RxLinkRx0Log(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         TRUE (Function Completion) / FALSE (Function Incompletion)                                                       */
/*===================================================================================================================================*/
static void   vd_s_Gvif3RxLinkRx0Log(void)
{
    if(u1_s_gvif3rx0unconcnt < (U1)U1_MAX){
        u1_s_gvif3rx0unconcnt++;
    }
    if((u1_s_gvif3rx0unconcnt >= (U1)GVIF3RX_UNCON_CNT_CNF) &&
       (u1_s_gvif3rx0unconflg == (U1)GVIF3RX_UNCON_FLGOFF)){
        /* ダイレコ Rob① */
        vd_g_SysEcDrc_Drec((U1)SYSECDRC_DREC_CAT_GVIFRX, (U1)SYSECDRC_DREC_ID_2, (U1)0x00U, (U1)0x00U);
        vd_g_RobCtl_SetRobId((U1)ROBCTL_ROBID_GVIFRX0_ERR);
        u1_s_gvif3rx0unconflg = (U1)GVIF3RX_UNCON_FLGON;
    }
}

/*===================================================================================================================================*/
/*  static void   vd_s_Gvif3RxLinkRx1Log(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         TRUE (Function Completion) / FALSE (Function Incompletion)                                                       */
/*===================================================================================================================================*/
static void   vd_s_Gvif3RxLinkRx1Log(void)
{
    if(u1_s_gvif3rx1unconcnt < (U1)U1_MAX){
        u1_s_gvif3rx1unconcnt++;
    }
    if((u1_s_gvif3rx1unconcnt >= (U1)GVIF3RX_UNCON_CNT_CNF) && 
       (u1_s_gvif3rx1unconflg == (U1)GVIF3RX_UNCON_FLGOFF)){
        /* ダイレコ Rob② */
        vd_g_SysEcDrc_Drec((U1)SYSECDRC_DREC_CAT_GVIFRX, (U1)SYSECDRC_DREC_ID_3, (U1)0x00U, (U1)0x00U);
        vd_g_RobCtl_SetRobId((U1)ROBCTL_ROBID_GVIFRX1_ERR);
        u1_s_gvif3rx1unconflg = (U1)GVIF3RX_UNCON_FLGON;
    }
}

/*===================================================================================================================================*/
/*  static U1    u1_s_Gvif3LinkStsGetReq(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         TRUE (Function Completion) / FALSE (Function Incompletion)                                                       */
/*===================================================================================================================================*/
static U1    u1_s_Gvif3LinkStsGetReq(void)
{
    U1      u1_t_ret;                                               /* Function Completion Status  */

    if(u1_s_gvif3rxlinkchk_flg == (U1)TRUE){                     /* Register Set Complete */
        u1_t_ret = (U1)TRUE;
        u1_s_gvif3rxlinkchk_flg = (U1)FALSE;                     /* Flag Clear */
    }
    else{
        u1_t_ret = (U1)FALSE;
        vd_s_Gvif3RxProcessMng((U4)GVIF3RX_PROC_LINKCHK);
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3LinkStsGet(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3LinkStsGet(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;

    u1_t_return = (U1)FALSE;

    u1_t_sts = (U1)Mcu_Dev_I2c_Ctrl_RegRead((uint8)MCU_I2C_ACK_GVIF_RX, &u2_s_gvif3rx_regstep, (uint8)GP_I2C_MA_SLA_2_GVIF_RX,
                                             &u4_s_gcif3acktime, st_sp_GVIF3RX_REG_LINKCHK, &u2_s_gvif3rxregset_betwaittime_stub, (U1)MCU_I2C_WAIT_NON);
    if(u1_t_sts == (U1)TRUE){
        u1_t_return = (U1)TRUE;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3Error1Chk(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3Error1Chk(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;
    U1 u1_t_jdg;
    U1 u1_t_req;

    u1_t_return = (U1)FALSE;
    u1_t_sts = (U1)0U;
    u1_t_jdg = (U1)0U;
    u1_t_req = (U1)FALSE;

    switch (u1_s_gvif3error1_step)
    {
        case GVIF3RX_ERROR1_STEP1:
            vd_s_Gvif3RxBank0Chk();
            if(u1_s_gvif3rxbank_last == (U1)GVIF3RX_BANK0){
                (void)u1_s_Gvif3RxErr1StsGetReq();
                u1_s_gvif3rxregacc_flg = (U1)TRUE;
                u1_s_gvif3error1_step = (U1)GVIF3RX_ERROR1_STEP2;
            }
            break;

        case GVIF3RX_ERROR1_STEP2:
            u1_t_sts = u1_s_Gvif3RxErr1StsGetReq();
            if(u1_t_sts == (U1)TRUE){
                u1_t_jdg = (U1)st_sp_GVIF3RX_REG_EERROR1CHK[1].u1p_pdu[1] & (U1)GVIF3RX_ERRORCHK_MASK;
                if(u1_t_jdg != (U1)GVIF3RX_ERRORCHK_NON){
                    u1_t_req = (U1)TRUE;
                }
                u1_t_return = (U1)TRUE;
                u1_s_gvif3rxregacc_flg = (U1)FALSE;
                u1_s_gvif3error1_step = (U1)GVIF3RX_ERROR1_STEP1;
            }
            break;

        default:
            u1_s_gvif3error1_step = (U1)GVIF3RX_ERROR1_STEP1;
            break;
    }
    
    if((u1_s_gvif3rxerror1chkcnt < (U1)GVIF3RX_ERROR_MAXLOGCNT) && (u1_t_req == (U1)TRUE)){
        /* ダイレコ */
        u1_s_gvif3rxerror1chkcnt++;
        vd_g_SysEcDrc_Drec((U1)SYSECDRC_DREC_CAT_GVIFRX,
                           (U1)SYSECDRC_DREC_ID_4,
                           (U1)u1_s_gvif3rxerror1chkcnt,
                           (U1)st_sp_GVIF3RX_REG_EERROR1CHK[1].u1p_pdu[1]);
    }
    
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_Gvif3RxErr1StsGetReq(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         TRUE (Function Completion) / FALSE (Function Incompletion)                                                       */
/*===================================================================================================================================*/
static U1    u1_s_Gvif3RxErr1StsGetReq(void)
{
    U1      u1_t_ret;                                               /* Function Completion Status  */

    if(u1_s_gvif3rxerr1chk_flg == (U1)TRUE){                     /* Register Set Complete */
        u1_t_ret = (U1)TRUE;
        u1_s_gvif3rxerr1chk_flg = (U1)FALSE;                     /* Flag Clear */
    }
    else{
        u1_t_ret = (U1)FALSE;
        vd_s_Gvif3RxProcessMng((U4)GVIF3RX_PROC_ERROR1CHK);
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3Error1StsGet(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3Error1StsGet(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;

    u1_t_return = (U1)FALSE;

    u1_t_sts = (U1)Mcu_Dev_I2c_Ctrl_RegRead((uint8)MCU_I2C_ACK_GVIF_RX, &u2_s_gvif3rx_regstep, (uint8)GP_I2C_MA_SLA_2_GVIF_RX,
                                             &u4_s_gcif3acktime, st_sp_GVIF3RX_REG_EERROR1CHK, &u2_s_gvif3rxregset_betwaittime_stub, (U1)MCU_I2C_WAIT_NON);
    if(u1_t_sts == (U1)TRUE){
        u1_t_return = (U1)TRUE;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3Error2Chk(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3Error2Chk(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;
    U1 u1_t_jdg;
    U1 u1_t_req;

    u1_t_return = (U1)FALSE;
    u1_t_sts = (U1)0U;
    u1_t_jdg = (U1)0U;
    u1_t_req = (U1)FALSE;

    switch (u1_s_gvif3error2_step)
    {
        case GVIF3RX_ERROR2_STEP1:
            vd_s_Gvif3RxBank0Chk();
            if(u1_s_gvif3rxbank_last == (U1)GVIF3RX_BANK0){
                (void)u1_s_Gvif3RxErr2StsGetReq();
                u1_s_gvif3rxregacc_flg = (U1)TRUE;
                u1_s_gvif3error2_step = (U1)GVIF3RX_ERROR2_STEP2;
            }
            break;

        case GVIF3RX_ERROR2_STEP2:
            u1_t_sts = u1_s_Gvif3RxErr2StsGetReq();
            if(u1_t_sts == (U1)TRUE){
                u1_t_jdg = (U1)st_sp_GVIF3RX_REG_EERROR2CHK[1].u1p_pdu[1] & (U1)GVIF3RX_ERRORCHK_MASK;
                if(u1_t_jdg != (U1)GVIF3RX_ERRORCHK_NON){
                    u1_t_req = (U1)TRUE;
                }
                u1_t_return = (U1)TRUE;
                u1_s_gvif3rxregacc_flg = (U1)FALSE;
                u1_s_gvif3error2_step = (U1)GVIF3RX_ERROR2_STEP1;
            }
            break;

        default:
            u1_s_gvif3error2_step = (U1)GVIF3RX_ERROR2_STEP1;
            break;
    }

    if((u1_s_gvif3rxerror2chkcnt < (U1)GVIF3RX_ERROR_MAXLOGCNT) && (u1_t_req == (U1)TRUE)){
        /* ダイレコ */
        u1_s_gvif3rxerror2chkcnt++;
        vd_g_SysEcDrc_Drec((U1)SYSECDRC_DREC_CAT_GVIFRX,
                           (U1)SYSECDRC_DREC_ID_5,
                           u1_s_gvif3rxerror2chkcnt,
                           (U1)st_sp_GVIF3RX_REG_EERROR2CHK[1].u1p_pdu[1]);
    }

    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_Gvif3RxErr2StsGetReq(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         TRUE (Function Completion) / FALSE (Function Incompletion)                                                       */
/*===================================================================================================================================*/
static U1    u1_s_Gvif3RxErr2StsGetReq(void)
{
    U1      u1_t_ret;                                               /* Function Completion Status  */

    if(u1_s_gvif3rxerr2chk_flg == (U1)TRUE){                     /* Register Set Complete */
        u1_t_ret = (U1)TRUE;
        u1_s_gvif3rxerr2chk_flg = (U1)FALSE;                     /* Flag Clear */
    }
    else{
        u1_t_ret = (U1)FALSE;
        vd_s_Gvif3RxProcessMng((U4)GVIF3RX_PROC_ERROR2CHK);
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3Error2StsGet(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3Error2StsGet(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;

    u1_t_return = (U1)FALSE;

    u1_t_sts = (U1)Mcu_Dev_I2c_Ctrl_RegRead((uint8)MCU_I2C_ACK_GVIF_RX, &u2_s_gvif3rx_regstep, (uint8)GP_I2C_MA_SLA_2_GVIF_RX,
                                            &u4_s_gcif3acktime, st_sp_GVIF3RX_REG_EERROR2CHK, &u2_s_gvif3rxregset_betwaittime_stub, (U1)MCU_I2C_WAIT_NON);
    if(u1_t_sts == (U1)TRUE){
        u1_t_return = (U1)TRUE;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3Error3Chk(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3Error3Chk(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;
    U1 u1_t_jdg;
    U1 u1_t_req;

    u1_t_return = (U1)FALSE;
    u1_t_sts = (U1)0U;
    u1_t_jdg = (U1)0U;
    u1_t_req = (U1)FALSE;

    switch (u1_s_gvif3error3_step)
    {
        case GVIF3RX_ERROR3_STEP1:
            vd_s_Gvif3RxBank0Chk();
            if(u1_s_gvif3rxbank_last == (U1)GVIF3RX_BANK0){
                (void)u1_s_Gvif3RxErr3StsGetReq();
                u1_s_gvif3rxregacc_flg = (U1)TRUE;
                u1_s_gvif3error3_step = (U1)GVIF3RX_ERROR3_STEP2;
            }
            break;

        case GVIF3RX_ERROR3_STEP2:
            u1_t_sts = u1_s_Gvif3RxErr3StsGetReq();
            if(u1_t_sts == (U1)TRUE){
                u1_t_jdg = (U1)st_sp_GVIF3RX_REG_EERROR3CHK[1].u1p_pdu[1] & (U1)GVIF3RX_ERRORCHK_MASK;
                if(u1_t_jdg != (U1)GVIF3RX_ERRORCHK_NON){
                    u1_t_req = (U1)TRUE;
                }
                u1_t_return = (U1)TRUE;
                u1_s_gvif3rxregacc_flg = (U1)FALSE;
                u1_s_gvif3error3_step = (U1)GVIF3RX_ERROR3_STEP1;
            }
            break;

        default:
            u1_s_gvif3error3_step = (U1)GVIF3RX_ERROR3_STEP1;
            break;
    }

    if((u1_s_gvif3rxerror3chkcnt < (U1)GVIF3RX_ERROR_MAXLOGCNT) && (u1_t_req == (U1)TRUE)){
        /* ダイレコ */
        u1_s_gvif3rxerror3chkcnt++;
        vd_g_SysEcDrc_Drec((U1)SYSECDRC_DREC_CAT_GVIFRX,
                           (U1)SYSECDRC_DREC_ID_6,
                           u1_s_gvif3rxerror3chkcnt,
                           (U1)st_sp_GVIF3RX_REG_EERROR3CHK[1].u1p_pdu[1]);
    }

    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_Gvif3RxErr3StsGetReq(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         TRUE (Function Completion) / FALSE (Function Incompletion)                                                       */
/*===================================================================================================================================*/
static U1    u1_s_Gvif3RxErr3StsGetReq(void)
{
    U1      u1_t_ret;                                               /* Function Completion Status  */

    if(u1_s_gvif3rxerr3chk_flg == (U1)TRUE){                     /* Register Set Complete */
        u1_t_ret = (U1)TRUE;
        u1_s_gvif3rxerr3chk_flg = (U1)FALSE;                     /* Flag Clear */
    }
    else{
        u1_t_ret = (U1)FALSE;
        vd_s_Gvif3RxProcessMng((U4)GVIF3RX_PROC_ERROR3CHK);
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3Error3StsGet(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3Error3StsGet(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;

    u1_t_return = (U1)FALSE;

    u1_t_sts = (U1)Mcu_Dev_I2c_Ctrl_RegRead((uint8)MCU_I2C_ACK_GVIF_RX, &u2_s_gvif3rx_regstep, (uint8)GP_I2C_MA_SLA_2_GVIF_RX,
                                            &u4_s_gcif3acktime, st_sp_GVIF3RX_REG_EERROR3CHK, &u2_s_gvif3rxregset_betwaittime_stub, (U1)MCU_I2C_WAIT_NON);
    if(u1_t_sts == (U1)TRUE){
        u1_t_return = (U1)TRUE;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3Error4Chk(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3Error4Chk(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;
    U1 u1_t_jdg;
    U1 u1_t_req;

    u1_t_return = (U1)FALSE;
    u1_t_sts = (U1)0U;
    u1_t_jdg = (U1)0U;
    u1_t_req = (U1)FALSE;

    switch (u1_s_gvif3error4_step)
    {
        case GVIF3RX_ERROR4_STEP1:
            vd_s_Gvif3RxBank0Chk();
            if(u1_s_gvif3rxbank_last == (U1)GVIF3RX_BANK0){
                (void)u1_s_Gvif3RxErr4StsGetReq();
                u1_s_gvif3rxregacc_flg = (U1)TRUE;
                u1_s_gvif3error4_step = (U1)GVIF3RX_ERROR4_STEP2;
            }
            break;

        case GVIF3RX_ERROR4_STEP2:
            u1_t_sts = u1_s_Gvif3RxErr4StsGetReq();
            if(u1_t_sts == (U1)TRUE){
                u1_t_jdg = (U1)st_sp_GVIF3RX_REG_EERROR4CHK[1].u1p_pdu[1] & (U1)GVIF3RX_ERRORCHK_MASK;
                if(u1_t_jdg != (U1)GVIF3RX_ERRORCHK_NON){
                    u1_t_req = (U1)TRUE;
                }
                u1_t_return = (U1)TRUE;
                u1_s_gvif3rxregacc_flg = (U1)FALSE;
                u1_s_gvif3error4_step = (U1)GVIF3RX_ERROR4_STEP1;
            }
            break;

        default:
            u1_s_gvif3error4_step = (U1)GVIF3RX_ERROR4_STEP1;
            break;
    }

    if((u1_s_gvif3rxerror4chkcnt < (U1)GVIF3RX_ERROR_MAXLOGCNT) && (u1_t_req == (U1)TRUE)){
        /* ダイレコ */
        u1_s_gvif3rxerror4chkcnt++;
        vd_g_SysEcDrc_Drec((U1)SYSECDRC_DREC_CAT_GVIFRX,
                           (U1)SYSECDRC_DREC_ID_7,
                           u1_s_gvif3rxerror4chkcnt,
                           (U1)st_sp_GVIF3RX_REG_EERROR4CHK[1].u1p_pdu[1]);
    }

    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_Gvif3RxErr4StsGetReq(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         TRUE (Function Completion) / FALSE (Function Incompletion)                                                       */
/*===================================================================================================================================*/
static U1    u1_s_Gvif3RxErr4StsGetReq(void)
{
    U1      u1_t_ret;                                               /* Function Completion Status  */

    if(u1_s_gvif3rxerr4chk_flg == (U1)TRUE){                     /* Register Set Complete */
        u1_t_ret = (U1)TRUE;
        u1_s_gvif3rxerr4chk_flg = (U1)FALSE;                     /* Flag Clear */
    }
    else{
        u1_t_ret = (U1)FALSE;
        vd_s_Gvif3RxProcessMng((U4)GVIF3RX_PROC_ERROR4CHK);
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3Error4StsGet(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3Error4StsGet(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;

    u1_t_return = (U1)FALSE;

    u1_t_sts = (U1)Mcu_Dev_I2c_Ctrl_RegRead((uint8)MCU_I2C_ACK_GVIF_RX, &u2_s_gvif3rx_regstep, (uint8)GP_I2C_MA_SLA_2_GVIF_RX,
                                            &u4_s_gcif3acktime, st_sp_GVIF3RX_REG_EERROR4CHK, &u2_s_gvif3rxregset_betwaittime_stub, (U1)MCU_I2C_WAIT_NON);
    if(u1_t_sts == (U1)TRUE){
        u1_t_return = (U1)TRUE;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3Error5Chk(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3Error5Chk(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;

    u1_t_return = (U1)FALSE;
    u1_t_sts = (U1)0U;

    switch (u1_s_gvif3rxerror5_step)
    {
        case GVIF3RX_ERROR5_STEP1:
            vd_s_Gvif3RxBank0Chk();
            if(u1_s_gvif3rxbank_last == (U1)GVIF3RX_BANK0){
                (void)u1_s_Gvif3RxErr5StsGetReq();
                u1_s_gvif3rxregacc_flg = (U1)TRUE;
                u1_s_gvif3rxerror5_step = (U1)GVIF3RX_ERROR5_STEP2;
            }
            break;

        case GVIF3RX_ERROR5_STEP2:
            u1_t_sts = u1_s_Gvif3RxErr5StsGetReq();
            if(u1_t_sts == (U1)TRUE){
                u1_t_return = (U1)TRUE;
                u1_s_gvif3rxregacc_flg = (U1)FALSE;
                u1_s_gvif3rxerror5_step = (U1)GVIF3RX_ERROR5_STEP1;
            }
            break;

        default:
            u1_s_gvif3rxerror5_step = (U1)GVIF3RX_ERROR5_STEP1;
            break;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_Gvif3RxErr5StsGetReq(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         TRUE (Function Completion) / FALSE (Function Incompletion)                                                       */
/*===================================================================================================================================*/
static U1    u1_s_Gvif3RxErr5StsGetReq(void)
{
    U1      u1_t_ret;                                               /* Function Completion Status  */

    if(u1_s_gvif3rxerr5chk_flg == (U1)TRUE){                     /* Register Set Complete */
        u1_t_ret = (U1)TRUE;
        u1_s_gvif3rxerr5chk_flg = (U1)FALSE;                     /* Flag Clear */
    }
    else{
        u1_t_ret = (U1)FALSE;
        vd_s_Gvif3RxProcessMng((U4)GVIF3RX_PROC_ERROR5CHK);
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3Error5StsGet(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3Error5StsGet(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;

    u1_t_return = (U1)FALSE;

    u1_t_sts = (U1)Mcu_Dev_I2c_Ctrl_RegRead((uint8)MCU_I2C_ACK_GVIF_RX, &u2_s_gvif3rx_regstep, (uint8)GP_I2C_MA_SLA_2_GVIF_RX,
                                            &u4_s_gcif3acktime, st_sp_GVIF3RX_REG_EERROR5CHK, &u2_s_gvif3rxregset_betwaittime_stub, (U1)MCU_I2C_WAIT_NON);
    if(u1_t_sts == (U1)TRUE){
        u1_t_return = (U1)TRUE;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3Error6Chk(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3Error6Chk(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;

    u1_t_return = (U1)FALSE;
    u1_t_sts = (U1)0U;

    switch (u1_s_gvif3rxerror6_step)
    {
        case GVIF3RX_ERROR6_STEP1:
            vd_s_Gvif3RxBank0Chk();
            if(u1_s_gvif3rxbank_last == (U1)GVIF3RX_BANK0){
                (void)u1_s_Gvif3RxErr6StsGetReq();
                u1_s_gvif3rxregacc_flg = (U1)TRUE;
                u1_s_gvif3rxerror6_step = (U1)GVIF3RX_ERROR6_STEP2;
            }
            break;

        case GVIF3RX_ERROR6_STEP2:
            u1_t_sts = u1_s_Gvif3RxErr6StsGetReq();
            if(u1_t_sts == (U1)TRUE){
                u1_t_return = (U1)TRUE;
                u1_s_gvif3rxregacc_flg = (U1)FALSE;
                u1_s_gvif3rxerror6_step = (U1)GVIF3RX_ERROR6_STEP1;
            }
            break;

        default:
            u1_s_gvif3rxerror6_step = (U1)GVIF3RX_ERROR6_STEP1;
            break;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_Gvif3RxErr6StsGetReq(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         TRUE (Function Completion) / FALSE (Function Incompletion)                                                       */
/*===================================================================================================================================*/
static U1    u1_s_Gvif3RxErr6StsGetReq(void)
{
    U1      u1_t_ret;                                               /* Function Completion Status  */

    if(u1_s_gvif3rxerr6chk_flg == (U1)TRUE){                     /* Register Set Complete */
        u1_t_ret = (U1)TRUE;
        u1_s_gvif3rxerr6chk_flg = (U1)FALSE;                     /* Flag Clear */
    }
    else{
        u1_t_ret = (U1)FALSE;
        vd_s_Gvif3RxProcessMng((U4)GVIF3RX_PROC_ERROR6CHK);
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3Error6StsGet(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3Error6StsGet(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;

    u1_t_return = (U1)FALSE;

    u1_t_sts = (U1)Mcu_Dev_I2c_Ctrl_RegRead((uint8)MCU_I2C_ACK_GVIF_RX, &u2_s_gvif3rx_regstep, (uint8)GP_I2C_MA_SLA_2_GVIF_RX,
                                            &u4_s_gcif3acktime, st_sp_GVIF3RX_REG_EERROR6CHK, &u2_s_gvif3rxregset_betwaittime_stub, (U1)MCU_I2C_WAIT_NON);
    if(u1_t_sts == (U1)TRUE){
        u1_t_return = (U1)TRUE;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3Error7Chk(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3Error7Chk(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;

    u1_t_return = (U1)FALSE;
    u1_t_sts = (U1)0U;

    switch (u1_s_gvif3rxerror7_step)
    {
        case GVIF3RX_ERROR7_STEP1:
            vd_s_Gvif3RxBank2Chk();
            if(u1_s_gvif3rxbank_last == (U1)GVIF3RX_BANK2){
                (void)u1_s_Gvif3RxErr7StsGetReq();
                u1_s_gvif3rxregacc_flg = (U1)TRUE;
                u1_s_gvif3rxerror7_step = (U1)GVIF3RX_ERROR7_STEP2;
            }
            break;

        case GVIF3RX_ERROR7_STEP2:
            u1_t_sts = u1_s_Gvif3RxErr7StsGetReq();
            if(u1_t_sts == (U1)TRUE){
                u1_t_return = (U1)TRUE;
                u1_s_gvif3rxregacc_flg = (U1)FALSE;
                u1_s_gvif3rxerror7_step = (U1)GVIF3RX_ERROR7_STEP1;
            }
            break;

        default:
            u1_s_gvif3rxerror7_step = (U1)GVIF3RX_ERROR7_STEP1;
            break;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_Gvif3RxErr7StsGetReq(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         TRUE (Function Completion) / FALSE (Function Incompletion)                                                       */
/*===================================================================================================================================*/
static U1    u1_s_Gvif3RxErr7StsGetReq(void)
{
    U1      u1_t_ret;                                               /* Function Completion Status  */

    if(u1_s_gvif3rxerr7chk_flg == (U1)TRUE){                     /* Register Set Complete */
        u1_t_ret = (U1)TRUE;
        u1_s_gvif3rxerr7chk_flg = (U1)FALSE;                     /* Flag Clear */
    }
    else{
        u1_t_ret = (U1)FALSE;
        vd_s_Gvif3RxProcessMng((U4)GVIF3RX_PROC_ERROR7CHK);
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3Error7StsGet(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3Error7StsGet(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;

    u1_t_return = (U1)FALSE;

    u1_t_sts = (U1)Mcu_Dev_I2c_Ctrl_RegRead((uint8)MCU_I2C_ACK_GVIF_RX, &u2_s_gvif3rx_regstep, (uint8)GP_I2C_MA_SLA_2_GVIF_RX,
                                            &u4_s_gcif3acktime, st_sp_GVIF3RX_REG_EERROR7CHK, &u2_s_gvif3rxregset_betwaittime_stub, (U1)MCU_I2C_WAIT_NON);
    if(u1_t_sts == (U1)TRUE){
        u1_t_return = (U1)TRUE;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3Error8Chk(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3Error8Chk(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;

    u1_t_return = (U1)FALSE;
    u1_t_sts = (U1)0U;

    switch (u1_s_gvif3rxerror8_step)
    {
        case GVIF3RX_ERROR8_STEP1:
            vd_s_Gvif3RxBank2Chk();
            if(u1_s_gvif3rxbank_last == (U1)GVIF3RX_BANK2){
                (void)u1_s_Gvif3RxErr8StsGetReq();
                u1_s_gvif3rxregacc_flg = (U1)TRUE;
                u1_s_gvif3rxerror8_step = (U1)GVIF3RX_ERROR8_STEP2;
            }
            break;

        case GVIF3RX_ERROR8_STEP2:
            u1_t_sts = u1_s_Gvif3RxErr8StsGetReq();
            if(u1_t_sts == (U1)TRUE){
                u1_t_return = (U1)TRUE;
                u1_s_gvif3rxregacc_flg = (U1)FALSE;
                u1_s_gvif3rxerror8_step = (U1)GVIF3RX_ERROR8_STEP1;
            }
            break;

        default:
            u1_s_gvif3rxerror8_step = (U1)GVIF3RX_ERROR8_STEP1;
            break;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_Gvif3RxErr8StsGetReq(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         TRUE (Function Completion) / FALSE (Function Incompletion)                                                       */
/*===================================================================================================================================*/
static U1    u1_s_Gvif3RxErr8StsGetReq(void)
{
    U1      u1_t_ret;                                               /* Function Completion Status  */

    if(u1_s_gvif3rxerr8chk_flg == (U1)TRUE){                     /* Register Set Complete */
        u1_t_ret = (U1)TRUE;
        u1_s_gvif3rxerr8chk_flg = (U1)FALSE;                     /* Flag Clear */
    }
    else{
        u1_t_ret = (U1)FALSE;
        vd_s_Gvif3RxProcessMng((U4)GVIF3RX_PROC_ERROR8CHK);
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3Error8StsGet(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3Error8StsGet(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;

    u1_t_return = (U1)FALSE;

    u1_t_sts = (U1)Mcu_Dev_I2c_Ctrl_RegRead((uint8)MCU_I2C_ACK_GVIF_RX, &u2_s_gvif3rx_regstep, (uint8)GP_I2C_MA_SLA_2_GVIF_RX,
                                            &u4_s_gcif3acktime, st_sp_GVIF3RX_REG_EERROR8CHK, &u2_s_gvif3rxregset_betwaittime_stub, (U1)MCU_I2C_WAIT_NON);
    if(u1_t_sts == (U1)TRUE){
        u1_t_return = (U1)TRUE;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3Error9Chk(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3Error9Chk(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;

    u1_t_return = (U1)FALSE;
    u1_t_sts = (U1)0U;

    switch (u1_s_gvif3rxerror9_step)
    {
        case GVIF3RX_ERROR9_STEP1:
            vd_s_Gvif3RxBank3Chk();
            if(u1_s_gvif3rxbank_last == (U1)GVIF3RX_BANK3){
                (void)u1_s_Gvif3RxErr9StsGetReq();
                u1_s_gvif3rxregacc_flg = (U1)TRUE;
                u1_s_gvif3rxerror9_step = (U1)GVIF3RX_ERROR9_STEP2;
            }
            break;

        case GVIF3RX_ERROR9_STEP2:
            u1_t_sts = u1_s_Gvif3RxErr9StsGetReq();
            if(u1_t_sts == (U1)TRUE){
                u1_t_return = (U1)TRUE;
                u1_s_gvif3rxregacc_flg = (U1)FALSE;
                u1_s_gvif3rxerror9_step = (U1)GVIF3RX_ERROR9_STEP1;
            }
            break;

        default:
            u1_s_gvif3rxerror9_step = (U1)GVIF3RX_ERROR9_STEP1;
            break;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_Gvif3RxErr9StsGetReq(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         TRUE (Function Completion) / FALSE (Function Incompletion)                                                       */
/*===================================================================================================================================*/
static U1    u1_s_Gvif3RxErr9StsGetReq(void)
{
    U1      u1_t_ret;                                               /* Function Completion Status  */

    if(u1_s_gvif3rxerr9chk_flg == (U1)TRUE){                     /* Register Set Complete */
        u1_t_ret = (U1)TRUE;
        u1_s_gvif3rxerr9chk_flg = (U1)FALSE;                     /* Flag Clear */
    }
    else{
        u1_t_ret = (U1)FALSE;
        vd_s_Gvif3RxProcessMng((U4)GVIF3RX_PROC_ERROR9CHK);
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3Error9StsGet(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3Error9StsGet(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;

    u1_t_return = (U1)FALSE;

    u1_t_sts = (U1)Mcu_Dev_I2c_Ctrl_RegRead((uint8)MCU_I2C_ACK_GVIF_RX, &u2_s_gvif3rx_regstep, (uint8)GP_I2C_MA_SLA_2_GVIF_RX,
                                            &u4_s_gcif3acktime, st_sp_GVIF3RX_REG_EERROR9CHK, &u2_s_gvif3rxregset_betwaittime_stub, (U1)MCU_I2C_WAIT_NON);
    if(u1_t_sts == (U1)TRUE){
        u1_t_return = (U1)TRUE;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3Error10Chk(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3Error10Chk(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;

    u1_t_return = (U1)FALSE;
    u1_t_sts = (U1)0U;

    switch (u1_s_gvif3rxerror10_step)
    {
        case GVIF3RX_ERROR10_STEP1:
            vd_s_Gvif3RxBank3Chk();
            if(u1_s_gvif3rxbank_last == (U1)GVIF3RX_BANK3){
                (void)u1_s_Gvif3RxErr10StsGetReq();
                u1_s_gvif3rxregacc_flg = (U1)TRUE;
                u1_s_gvif3rxerror10_step = (U1)GVIF3RX_ERROR10_STEP2;
            }
            break;

        case GVIF3RX_ERROR10_STEP2:
            u1_t_sts = u1_s_Gvif3RxErr10StsGetReq();
            if(u1_t_sts == (U1)TRUE){
                u1_t_return = (U1)TRUE;
                u1_s_gvif3rxregacc_flg = (U1)FALSE;
                u1_s_gvif3rxerror10_step = (U1)GVIF3RX_ERROR10_STEP1;
            }
            break;

        default:
            u1_s_gvif3rxerror10_step = (U1)GVIF3RX_ERROR10_STEP1;
            break;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_Gvif3RxErr10StsGetReq(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         TRUE (Function Completion) / FALSE (Function Incompletion)                                                       */
/*===================================================================================================================================*/
static U1    u1_s_Gvif3RxErr10StsGetReq(void)
{
    U1      u1_t_ret;                                               /* Function Completion Status  */

    if(u1_s_gvif3rxerr10chk_flg == (U1)TRUE){                     /* Register Set Complete */
        u1_t_ret = (U1)TRUE;
        u1_s_gvif3rxerr10chk_flg = (U1)FALSE;                     /* Flag Clear */
    }
    else{
        u1_t_ret = (U1)FALSE;
        vd_s_Gvif3RxProcessMng((U4)GVIF3RX_PROC_ERROR10CHK);
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3Error10StsGet(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3Error10StsGet(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;

    u1_t_return = (U1)FALSE;

    u1_t_sts = (U1)Mcu_Dev_I2c_Ctrl_RegRead((uint8)MCU_I2C_ACK_GVIF_RX, &u2_s_gvif3rx_regstep, (uint8)GP_I2C_MA_SLA_2_GVIF_RX,
                                            &u4_s_gcif3acktime, st_sp_GVIF3RX_REG_EERROR10CHK, &u2_s_gvif3rxregset_betwaittime_stub, (U1)MCU_I2C_WAIT_NON);
    if(u1_t_sts == (U1)TRUE){
        u1_t_return = (U1)TRUE;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3RxErrClr(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3RxErrClr(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;

    u1_t_return = (U1)FALSE;
    u1_t_sts = (U1)0U;

    switch (u1_s_gvif3rxerrclr_step)
    {
        case GVIF3RX_ERRCLR_STEP1:
            vd_s_Gvif3RxBank0Chk();
            if(u1_s_gvif3rxbank_last == (U1)GVIF3RX_BANK0){
                (void)u1_s_Gvif3RxErrClrStsGetReq();
                u1_s_gvif3rxregacc_flg = (U1)TRUE;
                u1_s_gvif3rxerrclr_step = (U1)GVIF3RX_ERRCLR_STEP2;
            }
            break;

        case GVIF3RX_ERRCLR_STEP2:
            u1_t_sts = u1_s_Gvif3RxErrClrStsGetReq();
            if(u1_t_sts == (U1)TRUE){
                u1_t_return = (U1)TRUE;
                u1_s_gvif3rxregacc_flg = (U1)FALSE;
                u1_s_gvif3rxerrclr_step = (U1)GVIF3RX_ERRCLR_STEP1;
            }
            break;

        default:
            u1_s_gvif3rxerrclr_step = (U1)GVIF3RX_ERRCLR_STEP1;
            break;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_Gvif3RxErrClrStsGetReq(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         TRUE (Function Completion) / FALSE (Function Incompletion)                                                       */
/*===================================================================================================================================*/
static U1    u1_s_Gvif3RxErrClrStsGetReq(void)
{
    U1      u1_t_ret;                                               /* Function Completion Status  */

    if(u1_s_gvif3rxerrclr_flg == (U1)TRUE){                     /* Register Set Complete */
        u1_t_ret = (U1)TRUE;
        u1_s_gvif3rxerrclr_flg = (U1)FALSE;                     /* Flag Clear */
    }
    else{
        u1_t_ret = (U1)FALSE;
        vd_s_Gvif3RxProcessMng((U4)GVIF3RX_PROC_ERRCLRSET);
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3RxErrClrRegSet(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3RxErrClrRegSet(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;

    u1_t_return = (U1)FALSE;

    u1_t_sts = (U1)Mcu_Dev_I2c_Ctrl_RegSet((U1)MCU_I2C_ACK_GVIF_RX, &u2_s_gvif3rx_regstep, (U2)GVIF3RX_OUTSET_WRINUM,
                                           (U1)GP_I2C_MA_SLA_2_GVIF_RX, st_sp_GVIFRX_OUTSET, &u4_s_gcif3acktime,
                                           st_sp_GVIF3RX_REG_ERRCLRSET, &u2_s_gvif3rxregset_betwaittime_stub);
    if(u1_t_sts == (U1)TRUE){
        u1_t_return = (U1)TRUE;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3RxErrClrRls(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3RxErrClrRls(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;

    u1_t_return = (U1)FALSE;
    u1_t_sts = (U1)0U;

    switch (u1_s_gvif3rxerrclrrls_step)
    {
        case GVIF3RX_ERRCLRRLS_STEP1:
            vd_s_Gvif3RxBank0Chk();
            if(u1_s_gvif3rxbank_last == (U1)GVIF3RX_BANK0){
                (void)u1_s_Gvif3RxErrClrRlsStsGetReq();
                u1_s_gvif3rxregacc_flg = (U1)TRUE;
                u1_s_gvif3rxerrclrrls_step = (U1)GVIF3RX_ERRCLRRLS_STEP2;
            }
            break;

        case GVIF3RX_ERRCLRRLS_STEP2:
            u1_t_sts = u1_s_Gvif3RxErrClrRlsStsGetReq();
            if(u1_t_sts == (U1)TRUE){
                u1_t_return = (U1)TRUE;
                u1_s_gvif3rxregacc_flg = (U1)FALSE;
                u1_s_gvif3rxerrclrrls_step = (U1)GVIF3RX_ERRCLRRLS_STEP1;
            }
            break;

        default:
            u1_s_gvif3rxerrclrrls_step = (U1)GVIF3RX_ERRCLRRLS_STEP1;
            break;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_Gvif3RxErrClrRlsStsGetReq(void)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         TRUE (Function Completion) / FALSE (Function Incompletion)                                                       */
/*===================================================================================================================================*/
static U1    u1_s_Gvif3RxErrClrRlsStsGetReq(void)
{
    U1      u1_t_ret;                                               /* Function Completion Status  */

    if(u1_s_gvif3rxerrclrrls_flg == (U1)TRUE){                     /* Register Set Complete */
        u1_t_ret = (U1)TRUE;
        u1_s_gvif3rxerrclrrls_flg = (U1)FALSE;                     /* Flag Clear */
    }
    else{
        u1_t_ret = (U1)FALSE;
        vd_s_Gvif3RxProcessMng((U4)GVIF3RX_PROC_ERRCLRRLS);
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3RxErrClrRlsRegSet(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3RxErrClrRlsRegSet(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;

    u1_t_return = (U1)FALSE;

    u1_t_sts = (U1)Mcu_Dev_I2c_Ctrl_RegSet((U1)MCU_I2C_ACK_GVIF_RX, &u2_s_gvif3rx_regstep, (U2)GVIF3RX_OUTSET_WRINUM,
                                           (U1)GP_I2C_MA_SLA_2_GVIF_RX, st_sp_GVIFRX_OUTSET, &u4_s_gcif3acktime,
                                           st_sp_GVIF3RX_REG_ERRCLRRLS, &u2_s_gvif3rxregset_betwaittime_stub);
    if(u1_t_sts == (U1)TRUE){
        u1_t_return = (U1)TRUE;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static void    vd_s_Gvif3RxBank0Chk(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         TRUE (Function Completion) / FALSE (Function Incompletion)                                                       */
/*===================================================================================================================================*/
static void    vd_s_Gvif3RxBank0Chk(void)
{
    if(u1_s_gvif3rxbank_last != (U1)GVIF3RX_BANK0){
        vd_s_Gvif3RxProcessMng((U4)GVIF3RX_PROC_BANK0);
    }
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3Bank0Chg(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3Bank0Chg(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;
    
    u1_t_return = (U1)FALSE;
    u1_t_sts = (U1)FALSE;

    u1_t_sts = (U1)Mcu_Dev_I2c_Ctrl_RegSet((U1)MCU_I2C_ACK_GVIF_RX, &u2_s_gvif3rx_regstep, (U2)GVIF3RX_OUTSET_WRINUM,
                                           (U1)GP_I2C_MA_SLA_2_GVIF_RX, st_sp_GVIFRX_OUTSET, &u4_s_gcif3acktime,
                                           st_sp_GVIF3RX_REG_BANK0, &u2_s_gvif3rxregset_betwaittime_stub);
    if(u1_t_sts == (U1)TRUE){
        u1_t_return = (U1)TRUE;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static void    vd_s_Gvif3RxBank2Chk(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         TRUE (Function Completion) / FALSE (Function Incompletion)                                                       */
/*===================================================================================================================================*/
static void    vd_s_Gvif3RxBank2Chk(void)
{
    if(u1_s_gvif3rxbank_last != (U1)GVIF3RX_BANK2){
        vd_s_Gvif3RxProcessMng((U4)GVIF3RX_PROC_BANK2);
    }
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3Bank2Chg(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3Bank2Chg(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;
    
    u1_t_return = (U1)FALSE;
    u1_t_sts = (U1)FALSE;

    u1_t_sts = (U1)Mcu_Dev_I2c_Ctrl_RegSet((U1)MCU_I2C_ACK_GVIF_RX, &u2_s_gvif3rx_regstep, (U2)GVIF3RX_OUTSET_WRINUM,
                                           (U1)GP_I2C_MA_SLA_2_GVIF_RX, st_sp_GVIFRX_OUTSET, &u4_s_gcif3acktime,
                                           st_sp_GVIF3RX_REG_BANK2, &u2_s_gvif3rxregset_betwaittime_stub);
    if(u1_t_sts == (U1)TRUE){
        u1_t_return = (U1)TRUE;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static void    vd_s_Gvif3RxBank3Chk(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         TRUE (Function Completion) / FALSE (Function Incompletion)                                                       */
/*===================================================================================================================================*/
static void    vd_s_Gvif3RxBank3Chk(void)
{
    if(u1_s_gvif3rxbank_last != (U1)GVIF3RX_BANK3){
        vd_s_Gvif3RxProcessMng((U4)GVIF3RX_PROC_BANK3);
    }
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3Bank3Chg(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3Bank3Chg(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;
    
    u1_t_return = (U1)FALSE;
    u1_t_sts = (U1)FALSE;

    u1_t_sts = (U1)Mcu_Dev_I2c_Ctrl_RegSet((U1)MCU_I2C_ACK_GVIF_RX, &u2_s_gvif3rx_regstep, (U2)GVIF3RX_OUTSET_WRINUM,
                                           (U1)GP_I2C_MA_SLA_2_GVIF_RX, st_sp_GVIFRX_OUTSET, &u4_s_gcif3acktime,
                                           st_sp_GVIF3RX_REG_BANK3, &u2_s_gvif3rxregset_betwaittime_stub);
    if(u1_t_sts == (U1)TRUE){
        u1_t_return = (U1)TRUE;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  0.0.0    01/28/2025  TN       New.                                                                                               */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*  * TN   = Tatsuya Niimi, KSE                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/
