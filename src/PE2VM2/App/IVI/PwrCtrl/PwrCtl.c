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
/* Power Mode Transition Event */
#define POWER_MODE_EVENT_NUM                (7U)
#define POWER_MODE_EVENT_BOOT_H             (0U)
#define POWER_MODE_EVENT_OTA                (1U)
#define POWER_MODE_EVENT_STATE_PARK         (2U)
#define POWER_MODE_EVENT_STATE_APPOFF       (3U)
#define POWER_MODE_EVENT_STATE_APPON        (4U)
#define POWER_MODE_EVENT_STATE_EDS          (5U)
#define POWER_MODE_EVENT_ELSE               (6U)

/* Can Date VPSIFOS Juge Value */
#define POWER_VPSINFOS_OTA                  (0x02U)

/* Can Date PWRERRST Juge Value */
#define POWER_PWRERRST_DCDCFAIL1            (0x09U)
#define POWER_PWRERRST_DCDCFAIL3            (0x0BU)
#define POWER_PWRERRST_LIBFAIL1             (0x11U)
#define POWER_PWRERRST_LIBFAIL3             (0x13U)
#define POWER_PWRERRST_PISFAIL1             (0x19U)
#define POWER_PWRERRST_PISFAIL3             (0x1BU)

/* Veopemd Vehicle Power Status Juge Value */
#define POWER_VEHOPE_STS_PARK               (0x0008U)   /* Veopemd:Parking */
#define POWER_VEHOPE_STS_RIDEON             (0x006AU)   /* Veopemd:Ride On */
#define POWER_VEHOPE_STS_POWERON            (0x007EU)   /* Veopemd:Power On Normal */
#define POWER_VEHOPE_STS_POWERON_STOP       (0x007AU)   /* Veopemd:Power On Emergency Stop */
#define POWER_VEHOPE_STS_PARK_HI_PRE        (0x0028U)   /* Veopemd:Parking High Pressure */
#define POWER_VEHOPE_STS_PARK_TEMP_CON      (0x0068U)   /* Veopemd:Parking High Pressure Temp Control */

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
        POWER_MODE_STATE_APPOFF,
        POWER_MODE_STATE_APPON,
        POWER_MODE_STATE_PARK,
        POWER_MODE_STATE_PARK
    },
    /* POWER_MODE_STATE_APPOFF */
    {
        POWER_MODE_STATE_APPON,
        POWER_MODE_STATE_APPON,
        POWER_MODE_STATE_PARK,
        POWER_MODE_STATE_APPOFF,
        POWER_MODE_STATE_APPON,
        POWER_MODE_STATE_APPOFF,
        POWER_MODE_STATE_APPOFF
    },
    /* POWER_MODE_STATE_APPON */
    {
        POWER_MODE_STATE_APPON,
        POWER_MODE_STATE_APPON,
        POWER_MODE_STATE_PARK,
        POWER_MODE_STATE_APPOFF,
        POWER_MODE_STATE_APPON,
        POWER_MODE_STATE_EDS,
        POWER_MODE_STATE_APPON
    },
    /* POWER_MODE_STATE_EDS */
    {
        POWER_MODE_STATE_APPON,
        POWER_MODE_STATE_APPON,
        POWER_MODE_STATE_PARK,
        POWER_MODE_STATE_APPOFF,
        POWER_MODE_STATE_APPON,
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
    U1  u1_t_vpsinfos;                          /* VPSINFOS Data */
    U1  u1_t_apofrq;                            /* APOFRQ Data */
    U1  u1_t_pwrerrst;                          /* PWRERRST Data */
    U1  u1_t_boot;                              /* BOOT Port Data *//* 暫定 量産時削除 */
    U4  u4_t_power_sts;                         /* Vehicle Power Status */

    /* Get Input Can Data */
    vd_POWER_GET_VPSINFOS(&u1_t_vpsinfos);
    vd_POWER_GET_APOFRQ(&u1_t_apofrq);
    vd_POWER_GET_PWRERRST(&u1_t_pwrerrst);

    /* Get BOOT Port Status *//* 暫定 量産時削除 */
    u1_t_boot = u1_POWER_GET_BOOT();

    /* Event Check */
    if(u1_t_boot == (U1)U1_EXTSIGCTRL_SIG_STS_ON){         /* BOOT = H *//* 暫定 量産時削除 */
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
    else{
        u4_t_power_sts = u4_POWER_GET_VEHOPE_STS();
        switch(u4_t_power_sts) {
            case POWER_VEHOPE_STS_PARK:
            case POWER_VEHOPE_STS_PARK_HI_PRE:
            case POWER_VEHOPE_STS_PARK_TEMP_CON:
                u1_t_evt  = (U1)POWER_MODE_EVENT_STATE_PARK;
                break;
            case POWER_VEHOPE_STS_RIDEON:
                if(u1_t_apofrq == (U1)0U){
                    u1_t_evt = (U1)POWER_MODE_EVENT_STATE_APPON;
                }
                else{
                    u1_t_evt = (U1)POWER_MODE_EVENT_STATE_APPOFF;
                }
                break;
            case POWER_VEHOPE_STS_POWERON:
            case POWER_VEHOPE_STS_POWERON_STOP:
                u1_t_evt = (U1)POWER_MODE_EVENT_STATE_APPON;
                break;
            default:
                u1_t_evt = (U1)POWER_MODE_EVENT_ELSE;
                break;
        }
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
