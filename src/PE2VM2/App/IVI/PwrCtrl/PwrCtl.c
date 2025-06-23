/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "PwrCtl.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define POWER_TASK_TIME        (1U)

/* Power Mode Transition Event */
#define POWER_MODE_EVENT_NUM                (12U)
#define POWER_MODE_EVENT_BOOT_H             (0U)
#define POWER_MODE_EVENT_OTA                (1U)
#define POWER_MODE_EVENT_STATE_UNDET        (2U)
#define POWER_MODE_EVENT_STATE_PARK         (3U)
#define POWER_MODE_EVENT_STATE_APPOFF       (4U)
#define POWER_MODE_EVENT_STATE_APPON        (5U)
#define POWER_MODE_EVENT_STATE_EMGSTOP      (6U)
#define POWER_MODE_EVENT_STATE_POWERON      (7U)
#define POWER_MODE_EVENT_STATE_HVPARK       (8U)
#define POWER_MODE_EVENT_STATE_HVACPARK     (9U)
#define POWER_MODE_EVENT_STATE_EDS          (10U)
#define POWER_MODE_EVENT_ELSE               (11U)

/* Can Date VPSIFO Juge Value */
#define POWER_VPSINFO_UNDET                 (0x40U)
#define POWER_VPSINFO_PARK                  (0x20U)
#define POWER_VPSINFO_RIDE                  (0x33U)
#define POWER_VPSINFO_EMGSTOP               (0x3BU)
#define POWER_VPSINFO_POWERON               (0x3FU)
#define POWER_VPSINFO_HVPARK                (0x22U)
#define POWER_VPSINFO_HVACPARK              (0x23U)

/* Can Date VPSIFOS Juge Value */
#define POWER_VPSINFOS_OTA                  (0x02U)

/* Can Date PWRERRST Juge Value */
#define POWER_PWRERRST_DCDCFAIL1            (0x09U)
#define POWER_PWRERRST_DCDCFAIL3            (0x0BU)
#define POWER_PWRERRST_LIBFAIL1             (0x11U)
#define POWER_PWRERRST_LIBFAIL3             (0x13U)
#define POWER_PWRERRST_PISFAIL1             (0x19U)
#define POWER_PWRERRST_PISFAIL3             (0x1BU)

/* Bit Mask */
#define POWER_BITMASK_BIT_0                 (0x01U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1 u1_s_pwr_modestate;                   /* Power Mode State */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Power Mode State Transition Table */
static const U1  u1_sp_POWER_STATETRANS_TBL[POWER_MODE_STATE_NUM][POWER_MODE_EVENT_NUM] = 
{
    /* POWER_MODE_STATE_PARK */
    {
        POWER_MODE_STATE_APPON,
        POWER_MODE_STATE_APPON,
        POWER_MODE_STATE_PARK,
        POWER_MODE_STATE_PARK,
        POWER_MODE_STATE_APPOFF,
        POWER_MODE_STATE_APPON,
        POWER_MODE_STATE_APPON,
        POWER_MODE_STATE_APPON,
        POWER_MODE_STATE_PARK,
        POWER_MODE_STATE_PARK,
        POWER_MODE_STATE_PARK,
        POWER_MODE_STATE_PARK
    },
    /* POWER_MODE_STATE_APPOFF */
    {
        POWER_MODE_STATE_APPON,
        POWER_MODE_STATE_APPON,
        POWER_MODE_STATE_APPOFF,
        POWER_MODE_STATE_PARK,
        POWER_MODE_STATE_APPOFF,
        POWER_MODE_STATE_APPON,
        POWER_MODE_STATE_APPON,
        POWER_MODE_STATE_APPON,
        POWER_MODE_STATE_PARK,
        POWER_MODE_STATE_PARK,
        POWER_MODE_STATE_APPOFF,
        POWER_MODE_STATE_APPOFF
    },
    /* POWER_MODE_STATE_APPON */
    {
        POWER_MODE_STATE_APPON,
        POWER_MODE_STATE_APPON,
        POWER_MODE_STATE_APPON,
        POWER_MODE_STATE_PARK,
        POWER_MODE_STATE_APPOFF,
        POWER_MODE_STATE_APPON,
        POWER_MODE_STATE_APPON,
        POWER_MODE_STATE_APPON,
        POWER_MODE_STATE_PARK,
        POWER_MODE_STATE_PARK,
        POWER_MODE_STATE_EDS,
        POWER_MODE_STATE_APPON
    },
    /* POWER_MODE_STATE_EDS */
    {
        POWER_MODE_STATE_APPON,
        POWER_MODE_STATE_APPON,
        POWER_MODE_STATE_EDS,
        POWER_MODE_STATE_PARK,
        POWER_MODE_STATE_APPOFF,
        POWER_MODE_STATE_APPON,
        POWER_MODE_STATE_APPON,
        POWER_MODE_STATE_APPON,
        POWER_MODE_STATE_PARK,
        POWER_MODE_STATE_PARK,
        POWER_MODE_STATE_EDS,
        POWER_MODE_STATE_EDS
    }
};

/*===================================================================================================================================*/
/*  void    vd_g_Power_BonInit(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Power_BonInit(void)
{
    u1_s_pwr_modestate = (U1)POWER_MODE_STATE_PARK;
}

/*===================================================================================================================================*/
/*  void    vd_g_Power_WkupInit(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Power_WkupInit(void)
{
    u1_s_pwr_modestate = (U1)POWER_MODE_STATE_PARK;
}

/*===================================================================================================================================*/
/*  void    vd_g_Power_Routine(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Power_Routine(void)
{
    U1  u1_t_evt;                               /* Event Judge Result */
    U1  u1_t_vpsinfo1;                          /* VPSINFO1 Data */
    U1  u1_t_vpsinfo2;                          /* VPSINFO2 Data */
    U1  u1_t_vpsinfo3;                          /* VPSINFO3 Data */
    U1  u1_t_vpsinfo4;                          /* VPSINFO4 Data */
    U1  u1_t_vpsinfo5;                          /* VPSINFO5 Data */
    U1  u1_t_vpsinfo6;                          /* VPSINFO6 Data */
    U1  u1_t_vpsinfo7;                          /* VPSINFO7 Data */
    U1  u1_t_vpsinfo;                           /* VPSINFO1-7 Summary Data */
    U1  u1_t_vpsinfos;                          /* VPSINFOS Data */
    U1  u1_t_apofrq;                            /* APOFRQ Data */
    U1  u1_t_pwrerrst;                          /* PWRERRST Data */
    U1  u1_t_boot;                              /* BOOT Port Data *//* 暫定 量産時削除 */

    /* Get Input Can Data */
    vd_POWER_GET_VPSINFO1(&u1_t_vpsinfo1);
    vd_POWER_GET_VPSINFO2(&u1_t_vpsinfo2);
    vd_POWER_GET_VPSINFO3(&u1_t_vpsinfo3);
    vd_POWER_GET_VPSINFO4(&u1_t_vpsinfo4);
    vd_POWER_GET_VPSINFO5(&u1_t_vpsinfo5);
    vd_POWER_GET_VPSINFO6(&u1_t_vpsinfo6);
    vd_POWER_GET_VPSINFO7(&u1_t_vpsinfo7);
    vd_POWER_GET_VPSINFOS(&u1_t_vpsinfos);
    vd_POWER_GET_APOFRQ(&u1_t_apofrq);
    vd_POWER_GET_PWRERRST(&u1_t_pwrerrst);

    /* Get BOOT Port Status *//* 暫定 量産時削除 */
    u1_t_boot = u1_POWER_GET_BOOT();

    u1_t_vpsinfo =  (u1_t_vpsinfo1 & (U1)POWER_BITMASK_BIT_0) << 6;     /* 6bit：CAN入力：判定中 */
    u1_t_vpsinfo |= (u1_t_vpsinfo2 & (U1)POWER_BITMASK_BIT_0) << 5;     /* 5bit：CAN入力：駐車中 */
    u1_t_vpsinfo |= (u1_t_vpsinfo3 & (U1)POWER_BITMASK_BIT_0) << 4;     /* 4bit：CAN入力：乗車中 */
    u1_t_vpsinfo |= (u1_t_vpsinfo5 & (U1)POWER_BITMASK_BIT_0) << 3;     /* 3bit：CAN入力：PowerON緊急停止 */
    u1_t_vpsinfo |= (u1_t_vpsinfo4 & (U1)POWER_BITMASK_BIT_0) << 2;     /* 2bit：CAN入力：PowerON通常 */
    u1_t_vpsinfo |= (u1_t_vpsinfo6 & (U1)POWER_BITMASK_BIT_0) << 1;     /* 1bit：CAN入力：駐車中高圧起動 */
    u1_t_vpsinfo |=  u1_t_vpsinfo7 & (U1)POWER_BITMASK_BIT_0;           /* 0bit：CAN入力：駐車中高圧・温調起動 */

    /* Event Check */
    if(u1_t_boot == (U1)POWER_IO_STS_HIGH){         /* BOOT = H *//* 暫定 量産時削除 */
        u1_t_evt  = (U1)POWER_MODE_EVENT_BOOT_H;
    }
    else if(u1_t_vpsinfos == (U1)POWER_VPSINFOS_OTA){
        u1_t_evt  = (U1)POWER_MODE_EVENT_OTA;
    }
    else if(((u1_t_pwrerrst >= (U1)POWER_PWRERRST_DCDCFAIL1) && (u1_t_pwrerrst <= (U1)POWER_PWRERRST_DCDCFAIL3))    /* DCDC Failded */
         || ((u1_t_pwrerrst >= (U1)POWER_PWRERRST_LIBFAIL1) && (u1_t_pwrerrst <= (U1)POWER_PWRERRST_LIBFAIL3))      /* LiB Failed */
         || ((u1_t_pwrerrst >= (U1)POWER_PWRERRST_PISFAIL1) && (u1_t_pwrerrst <= (U1)POWER_PWRERRST_PISFAIL3))){    /* PIS Failed */
        u1_t_evt  = (U1)POWER_MODE_EVENT_STATE_EDS;
        }
    else if(u1_t_vpsinfo == (U1)POWER_VPSINFO_UNDET){
        u1_t_evt = (U1)POWER_MODE_EVENT_STATE_UNDET;
    }
    else if(u1_t_vpsinfo == (U1)POWER_VPSINFO_PARK){
        u1_t_evt = (U1)POWER_MODE_EVENT_STATE_PARK;
    }
    else if(u1_t_vpsinfo == (U1)POWER_VPSINFO_RIDE){
        if(u1_t_apofrq == (U1)0U){
            u1_t_evt = (U1)POWER_MODE_EVENT_STATE_APPON;
        }
        else{
            u1_t_evt = (U1)POWER_MODE_EVENT_STATE_APPOFF;
        }
    }
    else if(u1_t_vpsinfo == (U1)POWER_VPSINFO_EMGSTOP){
        u1_t_evt = (U1)POWER_MODE_EVENT_STATE_EMGSTOP;
    }
    else if(u1_t_vpsinfo == (U1)POWER_VPSINFO_POWERON){
        u1_t_evt = (U1)POWER_MODE_EVENT_STATE_POWERON;
    }
    else if(u1_t_vpsinfo == (U1)POWER_VPSINFO_HVPARK){
        u1_t_evt = (U1)POWER_MODE_EVENT_STATE_HVPARK;
    }
    else if(u1_t_vpsinfo == (U1)POWER_VPSINFO_HVACPARK){
        u1_t_evt = (U1)POWER_MODE_EVENT_STATE_HVACPARK;
    }
    else{
        u1_t_evt = (U1)POWER_MODE_EVENT_ELSE;
    }

    /* State Transition */
    if((u1_s_pwr_modestate < (U1)POWER_MODE_STATE_NUM)
    && (u1_t_evt < (U1)POWER_MODE_EVENT_NUM)){
        u1_s_pwr_modestate = u1_sp_POWER_STATETRANS_TBL[u1_s_pwr_modestate][u1_t_evt];
    }
}

/*===================================================================================================================================*/
/*  U1    u1_g_Power_ModeState(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_s_pwr_modestate : Power Mode State                                                                            */
/*===================================================================================================================================*/
U1    u1_g_Power_ModeState(void)
{
    return(u1_s_pwr_modestate);
}
