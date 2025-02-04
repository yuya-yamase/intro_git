/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "GNSSCtl.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GNSS_TASK_TIME        (1U)

#define GNSS_SEQ_IDLE         (0U)
#define GNSS_SEQ_INI          (1U)
#define GNSS_SEQ_CYC          (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1 u1_s_gnss_state;                                  /* GNSS State */

static U2 u2_s_gnss_pmoni_inichk_timer;                     /* GNSS GPS-PMONI Initial Check Timer */
static U2 u2_s_gnss_cycchk_timer;                           /* GNSS Cycle Check Poling Timer */

static U1 u1_s_gnss_pre_rst_sts;                            /* Previous /GPS-RST Port Status */
static U1 u1_s_gnss_gps_stop_flg;                           /* "GPS Request : Stop" Receive Flag */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1 u1_s_Gnss_TimChk(const U2 u2_a_tim_cnt, const U2 u2_a_wait_tim);

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
    u1_s_gnss_state = (U1)GNSS_SEQ_IDLE;
    u2_s_gnss_pmoni_inichk_timer = (U1)0;
    u2_s_gnss_cycchk_timer = (U1)0;
    u1_s_gnss_gps_stop_flg = (U1)FALSE;
}

/*===================================================================================================================================*/
/*  void    vd_g_Gnss_Routine(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Gnss_Routine(void)
{
    static const U2 GNSS_CYCCHK_POLING = (U2)(10U / GNSS_TASK_TIME);            /* GPS-PMONI Poling Check Time *//* 暫定 xspiの定期に合わせる */

    U1  u1_t_gnss_rst_sts;                                                      /* /GPS-RST Port Status */
    U1  u1_t_pmoni_sts;                                                         /* GPS-PMONI Port Status */
    U1  u1_t_cyc_time_chk_flg;

    switch (u1_s_gnss_state){
        case GNSS_SEQ_IDLE:                                                     /* IDLE */
            /* Timer Clear */
            u2_s_gnss_cycchk_timer = (U2)0;

            /* Poling Start Check */
            /* /GPS-RST = L -> H */
            u1_t_gnss_rst_sts = u1_GNSS_GET_GPS_RST(); 
            if((u1_t_gnss_rst_sts == (U1)GNSS_IO_STS_HIGH)
            && (u1_s_gnss_pre_rst_sts == (U1)GNSS_IO_STS_LOW)){
                /* State Update */
                u1_s_gnss_state = (U1)GNSS_SEQ_INI;
                /* Initial Check Timer Start */
                u2_s_gnss_pmoni_inichk_timer++;
            }
            break;
        case GNSS_SEQ_INI:                                                      /* INI */
            u1_t_cyc_time_chk_flg = u1_s_Gnss_TimChk(u2_s_gnss_pmoni_inichk_timer, GNSS_CYCCHK_POLING);
            if(u1_t_cyc_time_chk_flg == (U1)TRUE){
                u1_t_pmoni_sts = u1_GNSS_GET_GPS_PMONI();
                /* OS Command : GPS Status Notification */
                if(u1_t_pmoni_sts == (U1)GNSS_IO_STS_LOW){
                    u1_GNSS_OSCMD_GPS_STS_NOTIF((U1)GNSS_OSCMD_NOTIF_STANDBY);  /* GPS Status Notification : Standby */
                }
                else{
                    u1_GNSS_OSCMD_GPS_STS_NOTIF((U1)GNSS_OSCMD_NOTIF_NORMAL);   /* GPS Status Notification : Normal */
                }
                /* State Update */
                u1_s_gnss_state = (U1)GNSS_SEQ_CYC;
                /*  Poling Check Timer Start */
                u2_s_gnss_cycchk_timer++;
            }
            else{
                u2_s_gnss_pmoni_inichk_timer++;
            }
            break;
        case GNSS_SEQ_CYC:                                                      /* CYCLIC */
            u1_t_cyc_time_chk_flg = u1_s_Gnss_TimChk(u2_s_gnss_cycchk_timer, GNSS_CYCCHK_POLING);
            if(u1_t_cyc_time_chk_flg == (U1)TRUE){
                /* Timer Clear */
                u2_s_gnss_cycchk_timer = (U2)0;
                /* OS Command : GPS Status Notification */
                if(u1_s_gnss_gps_stop_flg == (U1)TRUE){                         /* "GPS Request : Stop" Received */
                    u1_GNSS_OSCMD_GPS_STS_NOTIF((U1)GNSS_OSCMD_NOTIF_STANDBY);  /* GPS Status Notification : Standby */
                }
                else{
                    if(u1_t_pmoni_sts == (U1)GNSS_IO_STS_LOW){
                        u1_GNSS_OSCMD_GPS_STS_NOTIF((U1)GNSS_OSCMD_NOTIF_STANDBY);  /* GPS Status Notification : Standby */
                    }
                    else{
                        u1_GNSS_OSCMD_GPS_STS_NOTIF((U1)GNSS_OSCMD_NOTIF_NORMAL);   /* GPS Status Notification : Normal */
                    }
                }
            }
            else{
                u2_s_gnss_cycchk_timer++;
            }
            break;
        default:                                                                /* FAIL */
            vd_g_Gnss_Init();
            break;
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
/*  void    vd_g_Gnss_GpsReq(void)                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_gpsreq  :  GPS Device Restart(0) / GPS Device Stop(0)                                                       */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Gnss_GpsReq(U1 u1_a_gpsreq)
{
    if(u1_a_gpsreq == (U1)GNSS_OSCMD_RESET){                            /* GPS Request : Reset */
        u1_GNSS_SET_GPS_RST_L();                                        /* /GPS-RST = L */

        /* OS Command : GPS Respons */
        u1_GNSS_OSCMD_GPS_RES((U1)GNSS_OSCMD_RESET);                    /* GPS Respons : Reset */
        /* OS Command : GPS Status Notification */
        u1_GNSS_OSCMD_GPS_STS_NOTIF((U1)GNSS_OSCMD_NOTIF_STANDBY);      /* GPS Status Notification : Standby */
    }
    else if(u1_a_gpsreq == (U1)GNSS_OSCMD_STOP){                        /* GPS Request : Stop */
        u1_GNSS_SET_GPS_RST_L();                                        /* /GPS-RST = L */

        /* OS Command : GPS Respons */
        u1_GNSS_OSCMD_GPS_RES((U1)GNSS_OSCMD_STOP);                     /* GPS Respons : Reset */
        /* OS Command : GPS Status Notification */
        u1_GNSS_OSCMD_GPS_STS_NOTIF((U1)GNSS_OSCMD_NOTIF_STANDBY);      /* GPS Status Notification : Standby */
        
        u1_s_gnss_gps_stop_flg = (U1)TRUE;                              /* "GPS Request : Stop" Received */
    }
    else{                                                               /* GPS Respons : Invalid Value */
        /* Noting */
    }
}
