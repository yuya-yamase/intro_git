/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "GNSSCtl.h"

#include "ivdsh.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GNSS_TASK_TIME                  (1U)

#define GNSS_SEQ_IDLE                   (0U)
#define GNSS_SEQ_CYC                    (1U)
#define GNSS_SEQ_RESTART_WAIT           (2U)
#define GNSS_SEQ_RESTART                (3U)
#define GNSS_SEQ_STOP_WAIT              (4U)
#define GNSS_SEQ_STOP                   (5U)

#define GNSS_PMONI_FAILSAFE_CNT         (2U)

#define GNSS_VMCOM_WORD_1     (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1 u1_s_gnss_state;                                  /* GNSS State */

static U2 u2_s_gnss_cycchk_timer;                           /* GNSS Cycle Check Poling Timer */

static U4 u4_s_gnss_vmcom_rcv_gps_sts;                      /* GNSS VM Communication Receive Data "GPS Status" */
static U1 u1_s_gnss_pmoni_fail_cnt;                         /* GNSS P-MONI = L Fail Counter */
static U1 u1_s_gnss_oscmd_gps_req_rcv_flg;                  /* GNSS OS Command "GPS Request" Receive Flag */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1 u1_s_Gnss_TimChk(const U2 u2_a_tim_cnt, const U2 u2_a_wait_tim);
static void vd_s_Gnss_PmoniChk(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*===================================================================================================================================*/
/*  void    vd_g_Gnss_Init(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Gnss_Init(void)
{
    U4  u4_t_vmcom_gps_req;                                                     /* VM Communication Send Data "GPS Request" */

    u1_s_gnss_state = (U1)GNSS_SEQ_IDLE;
    u2_s_gnss_cycchk_timer = (U2)0;
    u4_s_gnss_vmcom_rcv_gps_sts = (U4)GNSS_VMCOM_GPS_STS_STOP;
    u1_s_gnss_pmoni_fail_cnt = (U1)0;
    u1_s_gnss_oscmd_gps_req_rcv_flg = (U1)FALSE;

    /* VM Communication Send Data "GPS Request" Initialize */
    u4_t_vmcom_gps_req = (U4)GNSS_VMCOM_GPS_REQ_NON;
    vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_GPS_REQ, &u4_t_vmcom_gps_req, (U2)GNSS_VMCOM_WORD_1);  /* GPS Request : Non */
}

/*===================================================================================================================================*/
/*  void    vd_g_Gnss_Routine(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Gnss_Routine(void)
{
    static const U2 GNSS_CYCCHK_POLING = (U2)(10U / GNSS_TASK_TIME);            /* GPS-PMONI Poling Check Time */

    U1  u1_t_v33_peri_on_sts;                                                   /* V33-Peri-On Port Status */
    U1  u1_t_vmcom_sts;                                                         /* VM Communication Receive Status */
    U4  u4_t_vmcom_gps_req;                                                     /* VM Communication Send Data "GPS Request" */
    U1  u1_t_cyc_time_chk_flg;

    u1_t_v33_peri_on_sts = u1_GNSS_GET_V33_PERI_ON();
    if(u1_t_v33_peri_on_sts == (U1)GNSS_IO_STS_LOW){
        /* P-MONI Fail Safe Counter Clear */
        u1_s_gnss_pmoni_fail_cnt = (U1)0;
    }

    switch (u1_s_gnss_state){
        case GNSS_SEQ_IDLE:                                                     /* IDLE */
            /* Poling Start Check */
            u1_t_vmcom_sts = u1_g_iVDshReabyDid((U2)IVDSH_DID_REA_GPS_STS, &u4_s_gnss_vmcom_rcv_gps_sts, (U2)GNSS_VMCOM_WORD_1);
            if(u1_t_vmcom_sts != (U1)IVDSH_NO_REA){
                if(u4_s_gnss_vmcom_rcv_gps_sts == (U4)GNSS_VMCOM_GPS_STS_PRE_STARTUP){  /* GPS Status : Pre-Startup */
                    /* Timer Clear */
                    u2_s_gnss_cycchk_timer = (U2)0;
                    /* State Update */
                    u1_s_gnss_state = (U1)GNSS_SEQ_CYC;
                }
            }
            break;
        case GNSS_SEQ_CYC:                                                      /* CYCLIC */
            u1_t_cyc_time_chk_flg = u1_s_Gnss_TimChk(u2_s_gnss_cycchk_timer, GNSS_CYCCHK_POLING);
            if(u1_t_cyc_time_chk_flg == (U1)TRUE){
                /* Timer Clear */
                u2_s_gnss_cycchk_timer = (U2)0;
                /* P-MONI Check */
                vd_s_Gnss_PmoniChk();
            }
            break;
        case GNSS_SEQ_RESTART_WAIT:                                             /* RESTART_WAIT */
            /* GPS Status Check */
            u1_t_vmcom_sts = u1_g_iVDshReabyDid((U2)IVDSH_DID_REA_GPS_STS, &u4_s_gnss_vmcom_rcv_gps_sts, (U2)GNSS_VMCOM_WORD_1);
            if(u1_t_vmcom_sts != (U1)IVDSH_NO_REA){
                if(u4_s_gnss_vmcom_rcv_gps_sts == (U4)GNSS_VMCOM_GPS_STS_PRE_STARTUP){  /* GPS Status : Pre-Startup */
                    /* VM Communication : "GPS Request" */
                    u4_t_vmcom_gps_req = (U4)GNSS_VMCOM_GPS_REQ_NON;
                    vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_GPS_REQ, &u4_t_vmcom_gps_req, (U2)GNSS_VMCOM_WORD_1);  /* GPS Request : Non */
                    /* State Update */
                    u1_s_gnss_state = (U1)GNSS_SEQ_RESTART;
                }
            }
            break;
        case GNSS_SEQ_RESTART:                                                  /* RESTART */
            /* GPS Status Check */
            u1_t_vmcom_sts = u1_g_iVDshReabyDid((U2)IVDSH_DID_REA_GPS_STS, &u4_s_gnss_vmcom_rcv_gps_sts, (U2)GNSS_VMCOM_WORD_1);
            if(u1_t_vmcom_sts != (U1)IVDSH_NO_REA){
                if(u4_s_gnss_vmcom_rcv_gps_sts != (U4)GNSS_VMCOM_GPS_STS_PRE_STARTUP){  /* GPS Status : Normal or Stop */
                    if(u1_s_gnss_oscmd_gps_req_rcv_flg == (U1)TRUE){                /* SoC -> MCU Request */
                        /* Flag Clear */
                        u1_s_gnss_oscmd_gps_req_rcv_flg = (U1)FALSE;
                        /* OS Command :GPS Status Notification */
                        u1_GNSS_OSCMD_GPS_STS_NOTIF((U1)GNSS_OSCMD_NOTIF_STANDBY);  /* GPS Status Notification : Standby */
                        /* OS Command : GPS Respons */
                        u1_GNSS_OSCMD_GPS_RES((U1)GNSS_OSCMD_RESTART);              /* GPS Respons : Restart */
                    }
                    /* Timer Clear */
                    u2_s_gnss_cycchk_timer = (U2)0;
                    /* State Update */
                    u1_s_gnss_state = (U1)GNSS_SEQ_CYC;
                }
            }
            break;
        case GNSS_SEQ_STOP_WAIT:                                                /* STOP WAIT */
            /* GPS Status Check */
            u1_t_vmcom_sts = u1_g_iVDshReabyDid((U2)IVDSH_DID_REA_GPS_STS, &u4_s_gnss_vmcom_rcv_gps_sts, (U2)GNSS_VMCOM_WORD_1);
            if(u1_t_vmcom_sts != (U1)IVDSH_NO_REA){
                if(u4_s_gnss_vmcom_rcv_gps_sts == (U4)GNSS_VMCOM_GPS_STS_STOP){     /* GPS Status : Stop */
                    if(u1_s_gnss_oscmd_gps_req_rcv_flg == (U1)TRUE){                /* SoC -> MCU Request */
                        /* Flag Clear */
                        u1_s_gnss_oscmd_gps_req_rcv_flg = (U1)FALSE;
                        /* OS Command :GPS Status Notification */
                        u1_GNSS_OSCMD_GPS_STS_NOTIF((U1)GNSS_OSCMD_NOTIF_STANDBY);  /* GPS Status Notification : Standby */
                        /* OS Command : GPS Respons */
                        u1_GNSS_OSCMD_GPS_RES((U1)GNSS_OSCMD_STOP);                 /* GPS Respons : Stop */
                    }
                    /* VM Communication : "GPS Request" */
                    u4_t_vmcom_gps_req = (U4)GNSS_VMCOM_GPS_REQ_NON;
                    vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_GPS_REQ, &u4_t_vmcom_gps_req, (U2)GNSS_VMCOM_WORD_1);  /* GPS Request : Non */
                    /* Timer Clear */
                    u2_s_gnss_cycchk_timer = (U2)0;
                    /* State Update */
                    u1_s_gnss_state = (U1)GNSS_SEQ_STOP;
                }
            }
            break;
        case GNSS_SEQ_STOP:                                                     /* STOP */
            u1_t_cyc_time_chk_flg = u1_s_Gnss_TimChk(u2_s_gnss_cycchk_timer, GNSS_CYCCHK_POLING);
            if(u1_t_cyc_time_chk_flg == (U1)TRUE){
                /* Timer Clear */
                u2_s_gnss_cycchk_timer = (U2)0;
                /* OS Command : GPS Respons */
                u1_GNSS_OSCMD_GPS_STS_NOTIF((U1)GNSS_OSCMD_NOTIF_STANDBY);  /* GPS Status Notification : Standby */
            }
            break;
        default:                                                                /* FAIL */
            vd_g_Gnss_Init();
            break;
    }

    if(u2_s_gnss_cycchk_timer < (U2)U2_MAX){
        u2_s_gnss_cycchk_timer++;
    }
}

/*===================================================================================================================================*/
/*  U1    u1_s_Gnss_TimChk(void)                                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u2_a_tim_cnt  :  Timer Count /  u2_a_wait_tim  :  Wait Time                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1 u1_s_Gnss_TimChk(const U2 u2_a_tim_cnt, const U2 u2_a_wait_tim)
{
    U1  u1_t_ret;

    u1_t_ret = (U1)FALSE;
    if(u2_a_tim_cnt >= u2_a_wait_tim){
        u1_t_ret = (U1)TRUE;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  void    vd_s_Gnss_PmoniChk(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Gnss_PmoniChk(void)
{
    U1  u1_t_pmoni_sts;                                                         /* GPS-PMONI Port Status */
    U1  u1_t_vmcom_sts;                                                         /* VM Communication Receive Status */
    U4  u4_t_vmcom_gps_req;                                                     /* VM Communication Send Data "GPS Request" */

    u1_t_pmoni_sts = u1_GNSS_GET_GPS_PMONI();

    if(u1_t_pmoni_sts == (U1)GNSS_IO_STS_LOW){
        /* OS Command :GPS Status Notification */
        u1_GNSS_OSCMD_GPS_STS_NOTIF((U1)GNSS_OSCMD_NOTIF_STANDBY);  /* GPS Status Notification : Standby */
        /* GPS Status Check */
        u1_t_vmcom_sts = u1_g_iVDshReabyDid((U2)IVDSH_DID_REA_GPS_STS, &u4_s_gnss_vmcom_rcv_gps_sts, (U2)GNSS_VMCOM_WORD_1);
        if(u1_t_vmcom_sts != (U1)IVDSH_NO_REA){
            if(u4_s_gnss_vmcom_rcv_gps_sts == (U4)GNSS_VMCOM_GPS_STS_NORMAL){   /* GPS Status : Normal */
                if(u1_s_gnss_pmoni_fail_cnt < (U1)U1_MAX){
                    u1_s_gnss_pmoni_fail_cnt++;
                }
                if(u1_s_gnss_pmoni_fail_cnt >= GNSS_PMONI_FAILSAFE_CNT){
                    /* VM Communication : "GPS Request" */
                    u4_t_vmcom_gps_req = (U4)GNSS_VMCOM_GPS_REQ_STOP;
                    vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_GPS_REQ, &u4_t_vmcom_gps_req, (U2)GNSS_VMCOM_WORD_1);  /* GPS Request : Stop */
                    /* State Update */
                    u1_s_gnss_state = (U1)GNSS_SEQ_STOP_WAIT;
                }
                else{
                    /* VM Communication : "GPS Request" */
                    u4_t_vmcom_gps_req = (U4)GNSS_VMCOM_GPS_REQ_RESTART;
                    vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_GPS_REQ, &u4_t_vmcom_gps_req, (U2)GNSS_VMCOM_WORD_1);  /* GPS Request : Restart */
                    /* State Update */
                    u1_s_gnss_state = (U1)GNSS_SEQ_RESTART_WAIT;
                }
            }
        }
    }
    else{
        /* OS Command :GPS Status Notification */
        u1_GNSS_OSCMD_GPS_STS_NOTIF((U1)GNSS_OSCMD_NOTIF_NORMAL);   /* GPS Status Notification : Normal */
    }

}

/*===================================================================================================================================*/
/*  void    vd_g_Gnss_GpsReq(void)                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_gpsreq  :  GPS Device Restart(0) / GPS Device Stop(1)                                                       */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Gnss_GpsReq(U1 u1_a_gpsreq)
{
    U4  u4_t_vmcom_gps_req;                                                     /* VM Communication Send Data "GPS Request" */

    if(u1_a_gpsreq == (U1)GNSS_OSCMD_RESTART){                          /* GPS Request : Restart */
        /* Receive Flag Update */
        u1_s_gnss_oscmd_gps_req_rcv_flg = (U1)TRUE;
        /* VM Communication : "GPS Request" */
        u4_t_vmcom_gps_req = (U4)GNSS_VMCOM_GPS_REQ_RESTART;
        vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_GPS_REQ, &u4_t_vmcom_gps_req, (U2)GNSS_VMCOM_WORD_1);  /* GPS Request : Restart */
        /* State Update */
        u1_s_gnss_state = (U1)GNSS_SEQ_RESTART_WAIT;
    }
    else if(u1_a_gpsreq == (U1)GNSS_OSCMD_STOP){                        /* GPS Request : Stop */
        /* Receive Flag Update */
        u1_s_gnss_oscmd_gps_req_rcv_flg = (U1)TRUE;
        /* VM Communication : "GPS Request" */
        u4_t_vmcom_gps_req = (U4)GNSS_VMCOM_GPS_REQ_STOP;
        vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_GPS_REQ, &u4_t_vmcom_gps_req, (U2)GNSS_VMCOM_WORD_1);  /* GPS Request : Stop */
        /* State Update */
        u1_s_gnss_state = (U1)GNSS_SEQ_STOP_WAIT;
    }
    else{                                                               /* GPS Respons : Invalid Value */
        /* Noting */
    }
}
